#include "config.h"
#include <bitcoin/feerate.h>
#include <bitcoin/script.h>
#include <ccan/cast/cast.h>
#include <ccan/mem/mem.h>
#include <ccan/tal/str/str.h>
#include <channeld/channeld_wiregen.h>
#include <closingd/closingd_wiregen.h>
#include <common/close_tx.h>
#include <common/closing_fee.h>
#include <common/fee_states.h>
#include <common/initial_commit_tx.h>
#include <common/json_command.h>
#include <common/json_helpers.h>
#include <common/json_tok.h>
#include <common/param.h>
#include <common/shutdown_scriptpubkey.h>
#include <common/timeout.h>
#include <common/type_to_string.h>
#include <common/utils.h>
#include <errno.h>
#include <gossipd/gossipd_wiregen.h>
#include <hsmd/capabilities.h>
#include <inttypes.h>
#include <lightningd/bitcoind.h>
#include <lightningd/chaintopology.h>
#include <lightningd/channel.h>
#include <lightningd/closing_control.h>
#include <lightningd/dual_open_control.h>
#include <lightningd/hsm_control.h>
#include <lightningd/json.h>
#include <lightningd/jsonrpc.h>
#include <lightningd/lightningd.h>
#include <lightningd/log.h>
#include <lightningd/opening_common.h>
#include <lightningd/options.h>
#include <lightningd/peer_control.h>
#include <lightningd/peer_fd.h>
#include <lightningd/subd.h>
#include <openingd/dualopend_wiregen.h>
#include <wally_bip32.h>

struct close_command {
	/* Inside struct lightningd close_commands. */
	struct list_node list;
	/* Command structure. This is the parent of the close command. */
	struct command *cmd;
	/* Channel being closed. */
	struct channel *channel;
};

/* Resolve a single close command. */
static void
resolve_one_close_command(struct close_command *cc, bool cooperative)
{
	struct json_stream *result = json_stream_success(cc->cmd);
	struct bitcoin_txid txid;

	bitcoin_txid(cc->channel->last_tx, &txid);

	json_add_tx(result, "tx", cc->channel->last_tx);
	json_add_txid(result, "txid", &txid);
	if (cooperative)
		json_add_string(result, "type", "mutual");
	else
		json_add_string(result, "type", "unilateral");

	was_pending(command_success(cc->cmd, result));
}

/* Resolve a close command for a channel that will be closed soon. */
void resolve_close_command(struct lightningd *ld, struct channel *channel,
			   bool cooperative)
{
	struct close_command *cc;
	struct close_command *n;

	list_for_each_safe(&ld->close_commands, cc, n, list) {
		if (cc->channel != channel)
			continue;
		resolve_one_close_command(cc, cooperative);
	}
}

/* Destroy the close command structure in reaction to the
 * channel being destroyed. */
static void
destroy_close_command_on_channel_destroy(struct channel *_ UNUSED,
					 struct close_command *cc)
{
	/* The cc has the command as parent, so resolving the
	 * command destroys the cc and triggers destroy_close_command.
	 * Clear the cc->channel first so that we will not try to
	 * remove a destructor. */
	cc->channel = NULL;
	was_pending(command_fail(cc->cmd, LIGHTNINGD,
				 "Channel forgotten before proper close."));
}

/* Destroy the close command structure. */
static void
destroy_close_command(struct close_command *cc)
{
	list_del(&cc->list);
	/* If destroy_close_command_on_channel_destroy was
	 * triggered beforehand, it will have cleared
	 * the channel field, preventing us from removing it
	 * from an already-destroyed channel. */
	if (!cc->channel)
		return;
	tal_del_destructor2(cc->channel,
			    &destroy_close_command_on_channel_destroy,
			    cc);
}

/* Handle timeout. */
static void
close_command_timeout(struct close_command *cc)
{
	/* This will trigger drop_to_chain, which will trigger
	 * resolution of the command and destruction of the
	 * close_command. */
	json_notify_fmt(cc->cmd, LOG_INFORM,
			"Timed out, forcing close.");
	channel_fail_permanent(cc->channel, REASON_USER,
			       "Forcibly closed by `close` command timeout");
}

/* Construct a close command structure and add to ld. */
static void
register_close_command(struct lightningd *ld,
		       struct command *cmd,
		       struct channel *channel,
		       unsigned int timeout)
{
	struct close_command *cc;
	assert(channel);

	cc = tal(cmd, struct close_command);
	list_add_tail(&ld->close_commands, &cc->list);
	cc->cmd = cmd;
	cc->channel = channel;
	tal_add_destructor(cc, &destroy_close_command);
	tal_add_destructor2(channel,
			    &destroy_close_command_on_channel_destroy,
			    cc);

	if (!channel->owner) {
		char *msg = tal_strdup(tmpctx, "peer is offline, will negotiate once they reconnect");
		if (timeout)
			tal_append_fmt(&msg, " (%u seconds before unilateral close)",
				       timeout);
		json_notify_fmt(cmd, LOG_INFORM, "%s.", msg);
	}
	log_debug(ld->log, "close_command: timeout = %u", timeout);
	if (timeout)
		new_reltimer(ld->timers, cc, time_from_sec(timeout),
			     &close_command_timeout, cc);
}

static struct amount_sat calc_tx_fee(struct amount_sat sat_in,
				     const struct bitcoin_tx *tx)
{
	struct amount_asset amt;
	struct amount_sat fee = sat_in;
	const u8 *oscript;
	size_t scriptlen;
	for (size_t i = 0; i < tx->wtx->num_outputs; i++) {
		amt = bitcoin_tx_output_get_amount(tx, i);
		oscript = bitcoin_tx_output_get_script(NULL, tx, i);
		scriptlen = tal_bytelen(oscript);
		tal_free(oscript);

		if (chainparams->is_elements && scriptlen == 0)
			continue;

		/* Ignore outputs that are not denominated in our main
		 * currency. */
		if (!amount_asset_is_main(&amt))
			continue;

		if (!amount_sat_sub(&fee, fee, amount_asset_to_sat(&amt)))
			fatal("Tx spends more than input %s? %s",
			      type_to_string(tmpctx, struct amount_sat, &sat_in),
			      type_to_string(tmpctx, struct bitcoin_tx, tx));
	}
	return fee;
}

/* Assess whether a proposed closing fee is acceptable. */
static bool closing_fee_is_acceptable(struct lightningd *ld,
				      struct channel *channel,
				      const struct bitcoin_tx *tx)
{
	struct amount_sat fee, last_fee, min_fee;
	u64 weight;
	u32 min_feerate;
	bool feerate_unknown;

	/* Calculate actual fee (adds in eliminated outputs) */
	fee = calc_tx_fee(channel->funding_sats, tx);
	last_fee = calc_tx_fee(channel->funding_sats, channel->last_tx);

	/* Weight once we add in sigs. */
	assert(!tx->wtx->inputs[0].witness
	       || tx->wtx->inputs[0].witness->num_items == 0);
	weight = bitcoin_tx_weight(tx) + bitcoin_tx_2of2_input_witness_weight();

	log_debug(channel->log, "Their actual closing tx fee is %s"
		 " vs previous %s: weight is %"PRIu64,
		  type_to_string(tmpctx, struct amount_sat, &fee),
		  type_to_string(tmpctx, struct amount_sat, &last_fee),
		  weight);

	/* If we don't have a feerate estimate, this gives feerate_floor */
	min_feerate = feerate_min(ld, &feerate_unknown);

	min_fee = amount_tx_fee(min_feerate, weight);
	if (amount_sat_less(fee, min_fee)) {
		log_debug(channel->log, "... That's below our min %s"
			  " for weight %"PRIu64" at feerate %u",
			  type_to_string(tmpctx, struct amount_sat, &min_fee),
			  weight, min_feerate);
		return false;
	}

	/* Prefer new over old: this covers the preference
	 * for a mutual close over a unilateral one. */

	return true;
}

static void peer_received_closing_signature(struct channel *channel,
					    const u8 *msg)
{
	struct bitcoin_signature sig;
	struct bitcoin_tx *tx;
	struct bitcoin_txid tx_id;
	struct lightningd *ld = channel->peer->ld;
	u8 *funding_wscript;

	if (!fromwire_closingd_received_signature(msg, msg, &sig, &tx)) {
		channel_internal_error(channel,
				       "Bad closing_received_signature %s",
				       tal_hex(msg, msg));
		return;
	}
	tx->chainparams = chainparams;

	funding_wscript = bitcoin_redeem_2of2(tmpctx,
				       	      &channel->local_funding_pubkey,
				       	      &channel->channel_info.remote_fundingkey);
	if (!check_tx_sig(tx, 0, NULL, funding_wscript,
			  &channel->channel_info.remote_fundingkey, &sig)) {
		channel_internal_error(channel,
				       "Bad closing_received_signature %s",
				       tal_hex(msg, msg));
		return;
	}

	if (closing_fee_is_acceptable(ld, channel, tx)) {
		channel_set_last_tx(channel, tx, &sig, TX_CHANNEL_CLOSE);
		wallet_channel_save(ld->wallet, channel);
	}


	// Send back the txid so we can update the billboard on selection.
	bitcoin_txid(channel->last_tx, &tx_id);
	/* OK, you can continue now. */
	subd_send_msg(channel->owner,
		      take(towire_closingd_received_signature_reply(channel, &tx_id)));
}

static void peer_closing_complete(struct channel *channel, const u8 *msg)
{
	if (!fromwire_closingd_complete(msg)) {
		channel_internal_error(channel, "Bad closing_complete %s",
				       tal_hex(msg, msg));
		return;
	}

	/* Don't report spurious failure when closingd exits. */
	channel_set_owner(channel, NULL);
	/* Clear any transient negotiation messages */
	channel_set_billboard(channel, false, NULL);

	/* Retransmission only, ignore closing. */
	if (channel_closed(channel))
		return;

	/* Channel gets dropped to chain cooperatively. */
	drop_to_chain(channel->peer->ld, channel, true);
	channel_set_state(channel,
			  CLOSINGD_SIGEXCHANGE,
			  CLOSINGD_COMPLETE,
			  REASON_UNKNOWN,
			  "Closing complete");
}

static void peer_closing_notify(struct channel *channel, const u8 *msg)
{
	char *message;
	struct close_command *i;
	enum log_level level;

	if (!fromwire_closingd_notification(msg, msg, &level, &message)) {
		channel_internal_error(channel, "Bad closing_notify %s",
				       tal_hex(msg, msg));
		return;
	}

	list_for_each(&channel->peer->ld->close_commands, i, list) {
		if (i->channel != channel)
			continue;
		json_notify_fmt(i->cmd, level, "%s", message);
	}
}

static unsigned closing_msg(struct subd *sd, const u8 *msg, const int *fds UNUSED)
{
	enum closingd_wire t = fromwire_peektype(msg);

	switch (t) {
	case WIRE_CLOSINGD_RECEIVED_SIGNATURE:
		peer_received_closing_signature(sd->channel, msg);
		break;

	case WIRE_CLOSINGD_COMPLETE:
		peer_closing_complete(sd->channel, msg);
		break;

	case WIRE_CLOSINGD_NOTIFICATION:
		peer_closing_notify(sd->channel, msg);
		break;

	/* We send these, not receive them */
	case WIRE_CLOSINGD_INIT:
	case WIRE_CLOSINGD_RECEIVED_SIGNATURE_REPLY:
		break;
	}

	return 0;
}

void peer_start_closingd(struct channel *channel, struct peer_fd *peer_fd)
{
	u8 *initmsg;
	u32 min_feerate, feerate, *max_feerate;
	struct amount_msat their_msat;
	struct amount_sat feelimit;
	int hsmfd;
	struct lightningd *ld = channel->peer->ld;
	u32 final_commit_feerate;
	bool option_anchor_outputs = channel_has(channel, OPT_ANCHOR_OUTPUTS);

	if (!channel->shutdown_scriptpubkey[REMOTE]) {
		channel_internal_error(channel,
				       "Can't start closing: no remote info");
		return;
	}

	hsmfd = hsm_get_client_fd(ld, &channel->peer->id, channel->dbid,
				  HSM_CAP_SIGN_CLOSING_TX
				  | HSM_CAP_COMMITMENT_POINT);

	channel_set_owner(channel,
			  new_channel_subd(ld,
					   "lightning_closingd",
					   channel, &channel->peer->id,
					   channel->log, true,
					   closingd_wire_name, closing_msg,
					   channel_errmsg,
					   channel_set_billboard,
					   take(&peer_fd->fd),
					   take(&hsmfd),
					   NULL));

	if (!channel->owner) {
		log_broken(channel->log, "Could not subdaemon closing: %s",
			    strerror(errno));
		channel_fail_reconnect_later(channel,
					     "Failed to subdaemon closing");
		return;
	}

	/* FIXME: This is the old BOLT 2 text, which restricted the closing
	 * fee to cap at the final commitment fee.  We still do this for now.
	 *
	 * The sending node:
	 *  - MUST set `fee_satoshis` less than or equal to the base
	 *    fee of the final commitment transaction, as calculated in
	 *    [BOLT #3](03-transactions.md#fee-calculation).
	 */
	final_commit_feerate = get_feerate(channel->fee_states,
					   channel->opener, LOCAL);
	feelimit = commit_tx_base_fee(final_commit_feerate, 0,
				      option_anchor_outputs);

	/* If we can't determine feerate, start at half unilateral feerate. */
	feerate = mutual_close_feerate(ld->topology);
	if (!feerate) {
		feerate = final_commit_feerate / 2;
		if (feerate < feerate_floor())
			feerate = feerate_floor();
	}

	/* We use a feerate if anchor_outputs, otherwise max fee is set by
	 * the final unilateral. */
	if (option_anchor_outputs) {
		max_feerate = tal(tmpctx, u32);
		/* Aim for reasonable max, but use final if we don't know. */
		*max_feerate = unilateral_feerate(ld->topology);
		if (!*max_feerate)
			*max_feerate = final_commit_feerate;
		/* No other limit on fees */
		feelimit = channel->funding_sats;
	} else
		max_feerate = NULL;

	min_feerate = feerate_min(ld, NULL);

	/* If they specified feerates in `close`, they apply now! */
	if (channel->closing_feerate_range) {
		min_feerate = channel->closing_feerate_range[0];
		max_feerate = &channel->closing_feerate_range[1];
	}

	/* BOLT #3:
	 *
	 * Each node offering a signature:
	 *  - MUST round each output down to whole satoshis.
	 */
	/* What is not ours is theirs */
	if (!amount_sat_sub_msat(&their_msat,
				 channel->funding_sats, channel->our_msat)) {
		log_broken(channel->log, "our_msat overflow funding %s minus %s",
			  type_to_string(tmpctx, struct amount_sat,
					 &channel->funding_sats),
			  type_to_string(tmpctx, struct amount_msat,
					 &channel->our_msat));
		channel_fail_permanent(channel,
				       REASON_LOCAL,
				       "our_msat overflow on closing");
		return;
	}

	// Determine the wallet index for our output or NULL if not found.
	u32 *local_wallet_index = NULL;
	struct ext_key *local_wallet_ext_key = NULL;
	u32 index_val;
	struct ext_key ext_key_val;
	bool is_p2sh;
	if (wallet_can_spend(
		    ld->wallet,
		    channel->shutdown_scriptpubkey[LOCAL],
		    &index_val,
		    &is_p2sh)) {
		if (bip32_key_from_parent(
			    ld->wallet->bip32_base,
			    index_val,
			    BIP32_FLAG_KEY_PUBLIC,
			    &ext_key_val) != WALLY_OK) {
			channel_internal_error(channel, "Could not derive ext public key");
			return;
		}
		local_wallet_index = &index_val;
		local_wallet_ext_key = &ext_key_val;
	}

	initmsg = towire_closingd_init(tmpctx,
				       chainparams,
				       &channel->cid,
				       &channel->funding,
				       channel->funding_sats,
				       &channel->local_funding_pubkey,
				       &channel->channel_info.remote_fundingkey,
				       channel->opener,
				       amount_msat_to_sat_round_down(channel->our_msat),
				       amount_msat_to_sat_round_down(their_msat),
				       channel->our_config.dust_limit,
				       min_feerate, feerate, max_feerate,
				       feelimit,
				       local_wallet_index,
				       local_wallet_ext_key,
				       channel->shutdown_scriptpubkey[LOCAL],
				       channel->shutdown_scriptpubkey[REMOTE],
				       channel->closing_fee_negotiation_step,
				       channel->closing_fee_negotiation_step_unit,
					/* Don't quickclose if they specified how to negotiate! */
				       (channel->closing_fee_negotiation_step == 50
					&& channel->closing_fee_negotiation_step_unit == CLOSING_FEE_NEGOTIATION_STEP_UNIT_PERCENTAGE)
				       /* Always use quickclose with anchors */
				       || option_anchor_outputs,
				       channel->shutdown_wrong_funding);

	/* We don't expect a response: it will give us feedback on
	 * signatures sent and received, then closing_complete. */
	subd_send_msg(channel->owner, take(initmsg));

	/* Now tell gossipd that we're closing and that neither direction should
	 * be used. */
	if (channel->scid)
		subd_send_msg(channel->peer->ld->gossip,
			      take(towire_gossipd_local_channel_close(
				  tmpctx, channel->scid)));
}

static struct command_result *param_outpoint(struct command *cmd,
					     const char *name,
					     const char *buffer,
					     const jsmntok_t *tok,
					     struct bitcoin_outpoint **outp)
{
	*outp = tal(cmd, struct bitcoin_outpoint);
	if (json_to_outpoint(buffer, tok, *outp))
		return NULL;
	return command_fail_badparam(cmd, name, buffer, tok,
				     "should be a txid:outnum");
}

static struct command_result *param_feerate_range(struct command *cmd,
						  const char *name,
						  const char *buffer,
						  const jsmntok_t *tok,
						  u32 **feerate_range)
{
	struct command_result *ret;
	u32 *rate;

	*feerate_range = tal_arr(cmd, u32, 2);
	if (tok->type != JSMN_ARRAY || tok->size != 2)
		return command_fail_badparam(cmd, name, buffer, tok,
					     "should be an array of 2 entries");

	ret = param_feerate(cmd, name, buffer, tok+1, &rate);
	if (ret)
		return ret;
	(*feerate_range)[0] = *rate;
	ret = param_feerate(cmd, name, buffer, tok+2, &rate);
	if (ret)
		return ret;
	(*feerate_range)[1] = *rate;
	return NULL;
}

static struct command_result *json_close(struct command *cmd,
					 const char *buffer,
					 const jsmntok_t *obj UNNEEDED,
					 const jsmntok_t *params)
{
	const jsmntok_t *idtok;
	struct peer *peer;
	struct channel *channel;
	unsigned int *timeout;
	const u8 *close_to_script = NULL;
	u32 *final_index;
	u32 index_val;
	bool close_script_set, wrong_funding_changed, *force_lease_close;
	const char *fee_negotiation_step_str;
	struct bitcoin_outpoint *wrong_funding;
	u32 *feerate_range;
	char* end;
	bool anysegwit;

	if (!param(cmd, buffer, params,
		   p_req("id", param_tok, &idtok),
		   p_opt_def("unilateraltimeout", param_number, &timeout,
			     48 * 3600),
		   p_opt("destination", param_bitcoin_address, &close_to_script),
		   p_opt("fee_negotiation_step", param_string,
			 &fee_negotiation_step_str),
		   p_opt("wrong_funding", param_outpoint, &wrong_funding),
		   p_opt_def("force_lease_closed", param_bool,
			     &force_lease_close, false),
		   p_opt("feerange", param_feerate_range, &feerate_range),
		   NULL))
		return command_param_failed();

	peer = peer_from_json(cmd->ld, buffer, idtok);
	if (peer)
		channel = peer_active_channel(peer);
	else {
		struct command_result *res;
		res = command_find_channel(cmd, buffer, idtok, &channel);
		if (res)
			return res;
	}

	if (!channel && peer) {
		struct uncommitted_channel *uc = peer->uncommitted_channel;
		if (uc) {
			/* Easy case: peer can simply be forgotten. */
			kill_uncommitted_channel(uc, "close command called");
			goto discard_unopened;
		}
		if ((channel = peer_unsaved_channel(peer))) {
			channel_unsaved_close_conn(channel,
						   "close command called");
			goto discard_unopened;
		}
		return command_fail(cmd, LIGHTNINGD,
				    "Peer has no active channel");
	}

	if (!*force_lease_close && channel->opener != LOCAL
	    && get_block_height(cmd->ld->topology) < channel->lease_expiry)
		return command_fail(cmd, LIGHTNINGD,
				    "Peer leased this channel from us, we"
				    " shouldn't close until lease has expired"
				    " (lease expires block %u,"
				    " current block %u)",
				    channel->lease_expiry,
				    get_block_height(cmd->ld->topology));

	/* Set the wallet index to the default value; it is updated
	 * below if the close_to_script is found to be in the
	 * wallet. If the close_to_script is not in the wallet
	 * final_index will be set to NULL instead.*/
	assert(channel->final_key_idx <= UINT32_MAX);
	index_val = (u32) channel->final_key_idx;
	final_index = &index_val;

	/* If we've set a local shutdown script for this peer, and it's not the
	 * default upfront script, try to close to a different channel.
	 * Error is an operator error */
	if (close_to_script && channel->shutdown_scriptpubkey[LOCAL]
			&& !memeq(close_to_script,
				  tal_count(close_to_script),
				  channel->shutdown_scriptpubkey[LOCAL],
				  tal_count(channel->shutdown_scriptpubkey[LOCAL]))) {
		u8 *default_close_to = p2wpkh_for_keyidx(tmpctx, cmd->ld,
							 channel->final_key_idx);
		if (!memeq(default_close_to, tal_count(default_close_to),
			   channel->shutdown_scriptpubkey[LOCAL],
			   tal_count(channel->shutdown_scriptpubkey[LOCAL]))) {
			return command_fail(cmd, JSONRPC2_INVALID_PARAMS,
					    "Destination address %s does not match "
					    "previous shutdown script %s",
					    tal_hex(tmpctx, channel->shutdown_scriptpubkey[LOCAL]),
					    tal_hex(tmpctx, close_to_script));
		} else {
			channel->shutdown_scriptpubkey[LOCAL] =
				tal_free(channel->shutdown_scriptpubkey[LOCAL]);
			channel->shutdown_scriptpubkey[LOCAL] =
				tal_steal(channel, close_to_script);
			close_script_set = true;
		}
	} else if (close_to_script && !channel->shutdown_scriptpubkey[LOCAL]) {
		channel->shutdown_scriptpubkey[LOCAL]
			= tal_steal(channel, cast_const(u8 *, close_to_script));
		close_script_set = true;
		/* Is the close script in our wallet? */
		bool is_p2sh;
		if (wallet_can_spend(
			    cmd->ld->wallet,
			    channel->shutdown_scriptpubkey[LOCAL],
			    &index_val,
			    &is_p2sh)) {
			/* index_val has been set to the discovered wallet index */
		} else {
			final_index = NULL;
		}
	} else if (!channel->shutdown_scriptpubkey[LOCAL]) {
		channel->shutdown_scriptpubkey[LOCAL]
			= p2wpkh_for_keyidx(channel, cmd->ld, channel->final_key_idx);
		/* We don't save the default to disk */
		close_script_set = false;
	} else
		close_script_set = false;

	/* Don't send a scriptpubkey peer won't accept */
	anysegwit = feature_negotiated(cmd->ld->our_features,
				       channel->peer->their_features,
				       OPT_SHUTDOWN_ANYSEGWIT);
	if (!valid_shutdown_scriptpubkey(channel->shutdown_scriptpubkey[LOCAL],
					 anysegwit)) {
		/* Explicit check for future segwits. */
		if (!anysegwit &&
		    valid_shutdown_scriptpubkey(channel->shutdown_scriptpubkey
						[LOCAL], true)) {
			return command_fail(cmd, JSONRPC2_INVALID_PARAMS,
					    "Peer does not allow v1+ shutdown addresses");
		}

		return command_fail(cmd, JSONRPC2_INVALID_PARAMS,
				    "Invalid close destination");
	}

	if (fee_negotiation_step_str == NULL) {
		channel->closing_fee_negotiation_step = 50;
		channel->closing_fee_negotiation_step_unit =
		    CLOSING_FEE_NEGOTIATION_STEP_UNIT_PERCENTAGE;
	} else {
		channel->closing_fee_negotiation_step =
		    strtoull(fee_negotiation_step_str, &end, 10);

		if (channel->closing_fee_negotiation_step == 0)
			return command_fail(
			    cmd, JSONRPC2_INVALID_PARAMS,
			    "Wrong value given for fee_negotiation_step: "
			    "\"%s\", must be positive",
			    fee_negotiation_step_str);
		else if (*end == '%') {
			if (channel->closing_fee_negotiation_step > 100)
				return command_fail(
				    cmd, JSONRPC2_INVALID_PARAMS,
				    "Wrong value given for "
				    "fee_negotiation_step: \"%s\", the "
				    "percentage should be between 1 and 100",
				    fee_negotiation_step_str);
			channel->closing_fee_negotiation_step_unit =
			    CLOSING_FEE_NEGOTIATION_STEP_UNIT_PERCENTAGE;
		} else if (*end == '\0')
			channel->closing_fee_negotiation_step_unit =
			    CLOSING_FEE_NEGOTIATION_STEP_UNIT_SATOSHI;
		else
			return command_fail(
			    cmd, JSONRPC2_INVALID_PARAMS,
			    "Wrong value given for fee_negotiation_step: "
			    "\"%s\", should be an integer or an integer "
			    "followed by %%",
			    fee_negotiation_step_str);
	}

	if (wrong_funding) {
		if (!feature_negotiated(cmd->ld->our_features,
					channel->peer->their_features,
					OPT_SHUTDOWN_WRONG_FUNDING)) {
			return command_fail(cmd, JSONRPC2_INVALID_PARAMS,
					    "wrong_funding feature not negotiated"
					    " (we said %s, they said %s: try experimental-shutdown-wrong-funding?)",
					    feature_offered(cmd->ld->our_features
							    ->bits[INIT_FEATURE],
							    OPT_SHUTDOWN_WRONG_FUNDING)
					    ? "yes" : "no",
					    feature_offered(channel->peer->their_features,
							    OPT_SHUTDOWN_WRONG_FUNDING)
					    ? "yes" : "no");
		}

		wrong_funding_changed = true;
		channel->shutdown_wrong_funding
			= tal_steal(channel, wrong_funding);
	} else {
		if (channel->shutdown_wrong_funding) {
			channel->shutdown_wrong_funding
				= tal_free(channel->shutdown_wrong_funding);
			wrong_funding_changed = true;
		} else
			wrong_funding_changed = false;
	}

	/* May already be set by previous close cmd. */
	tal_free(channel->closing_feerate_range);

	/* Works fine if feerate_range is NULL */
	channel->closing_feerate_range = tal_steal(channel, feerate_range);

	/* Normal case.
	 * We allow states shutting down and sigexchange; a previous
	 * close command may have timed out, and this current command
	 * will continue waiting for the effects of the previous
	 * close command. */

	/* If normal or locking in, transition to shutting down
	 * state.
	 * (if already shutting down or sigexchange, just keep
	 * waiting) */
	switch (channel->state) {
		case CHANNELD_NORMAL:
		case CHANNELD_AWAITING_LOCKIN:
		case DUALOPEND_AWAITING_LOCKIN:
			channel_set_state(channel,
					  channel->state, CHANNELD_SHUTTING_DOWN,
					  REASON_USER,
					  "User or plugin invoked close command");
			/* fallthrough */
		case CHANNELD_SHUTTING_DOWN:
			if (channel->owner) {
				u8 *msg;
				if (streq(channel->owner->name, "dualopend")) {
					msg = towire_dualopend_send_shutdown(
						NULL,
						channel->shutdown_scriptpubkey[LOCAL]);
				} else {
					struct ext_key ext_key_val;
					struct ext_key *final_ext_key = NULL;
					if (final_index) {
						if (bip32_key_from_parent(
							    channel->peer->ld->wallet->bip32_base,
							    *final_index,
							    BIP32_FLAG_KEY_PUBLIC,
							    &ext_key_val) != WALLY_OK) {
							return command_fail(
								cmd, LIGHTNINGD,
								"Could not derive final_ext_key");
						}
						final_ext_key = &ext_key_val;
					}
					msg = towire_channeld_send_shutdown(
						NULL,
						final_index,
						final_ext_key,
						channel->shutdown_scriptpubkey[LOCAL],
						channel->shutdown_wrong_funding);
				}
				subd_send_msg(channel->owner, take(msg));
			}

			break;
		case CLOSINGD_SIGEXCHANGE:
			break;
		default:
			return command_fail(cmd, LIGHTNINGD, "Channel is in state %s",
					    channel_state_name(channel));
	}

	/* Register this command for later handling. */
	register_close_command(cmd->ld, cmd, channel, *timeout);

	/* If we set `channel->shutdown_scriptpubkey[LOCAL]` or
	 * changed shutdown_wrong_funding, save it. */
	if (close_script_set || wrong_funding_changed)
		wallet_channel_save(cmd->ld->wallet, channel);

	/* Wait until close drops down to chain. */
	return command_still_pending(cmd);

discard_unopened: {
	struct json_stream *result = json_stream_success(cmd);
	json_add_string(result, "type", "unopened");
	return command_success(cmd, result);
	}
}

static const struct json_command close_command = {
	"close",
	"channels",
	json_close,
	"Close the channel with {id} "
	"(either peer ID, channel ID, or short channel ID). "
	"Force a unilateral close after {unilateraltimeout} seconds (default 48h). "
	"If {destination} address is provided, will be used as output address."
};
AUTODATA(json_command, &close_command);
