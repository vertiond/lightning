#include "config.h"
#include "../onion_message.c"
#include "common/blindedpath.c"
#include "common/blinding.c"
#include "common/bigsize.c"
#include "common/hmac.c"
#include "common/onion.c"
#include "common/sphinx.c"
#include "wire/fromwire.c"
#if EXPERIMENTAL_FEATURES
#include "wire/peer_exp_wiregen.c"
#include "wire/onion_exp_wiregen.c"
#else
#include "wire/peer_wiregen.c"
#include "wire/onion_wiregen.c"
#endif
#include "wire/tlvstream.c"

#include <ccan/str/hex/hex.h>
#include <ccan/tal/str/str.h>
#include <common/blinding.h>
#include <common/channel_type.h>
#include <common/ecdh.h>
#include <common/json_stream.h>
#include <common/onion.h>
#include <common/onionreply.h>
#include <common/setup.h>
#include <secp256k1_ecdh.h>
#include <stdio.h>

/* AUTOGENERATED MOCKS START */
/* Generated stub for amount_asset_is_main */
bool amount_asset_is_main(struct amount_asset *asset UNNEEDED)
{ fprintf(stderr, "amount_asset_is_main called!\n"); abort(); }
/* Generated stub for amount_asset_to_sat */
struct amount_sat amount_asset_to_sat(struct amount_asset *asset UNNEEDED)
{ fprintf(stderr, "amount_asset_to_sat called!\n"); abort(); }
/* Generated stub for amount_msat */
struct amount_msat amount_msat(u64 millisatoshis UNNEEDED)
{ fprintf(stderr, "amount_msat called!\n"); abort(); }
/* Generated stub for amount_msat_eq */
bool amount_msat_eq(struct amount_msat a UNNEEDED, struct amount_msat b UNNEEDED)
{ fprintf(stderr, "amount_msat_eq called!\n"); abort(); }
/* Generated stub for amount_sat */
struct amount_sat amount_sat(u64 satoshis UNNEEDED)
{ fprintf(stderr, "amount_sat called!\n"); abort(); }
/* Generated stub for amount_sat_add */
 bool amount_sat_add(struct amount_sat *val UNNEEDED,
				       struct amount_sat a UNNEEDED,
				       struct amount_sat b UNNEEDED)
{ fprintf(stderr, "amount_sat_add called!\n"); abort(); }
/* Generated stub for amount_sat_eq */
bool amount_sat_eq(struct amount_sat a UNNEEDED, struct amount_sat b UNNEEDED)
{ fprintf(stderr, "amount_sat_eq called!\n"); abort(); }
/* Generated stub for amount_sat_greater_eq */
bool amount_sat_greater_eq(struct amount_sat a UNNEEDED, struct amount_sat b UNNEEDED)
{ fprintf(stderr, "amount_sat_greater_eq called!\n"); abort(); }
/* Generated stub for amount_sat_sub */
 bool amount_sat_sub(struct amount_sat *val UNNEEDED,
				       struct amount_sat a UNNEEDED,
				       struct amount_sat b UNNEEDED)
{ fprintf(stderr, "amount_sat_sub called!\n"); abort(); }
/* Generated stub for amount_sat_to_asset */
struct amount_asset amount_sat_to_asset(struct amount_sat *sat UNNEEDED, const u8 *asset UNNEEDED)
{ fprintf(stderr, "amount_sat_to_asset called!\n"); abort(); }
/* Generated stub for amount_tx_fee */
struct amount_sat amount_tx_fee(u32 fee_per_kw UNNEEDED, size_t weight UNNEEDED)
{ fprintf(stderr, "amount_tx_fee called!\n"); abort(); }
/* Generated stub for daemon_conn_send */
void daemon_conn_send(struct daemon_conn *dc UNNEEDED, const u8 *msg UNNEEDED)
{ fprintf(stderr, "daemon_conn_send called!\n"); abort(); }
/* Generated stub for ecdh */
void ecdh(const struct pubkey *point UNNEEDED, struct secret *ss UNNEEDED)
{ fprintf(stderr, "ecdh called!\n"); abort(); }
/* Generated stub for fromwire_amount_msat */
struct amount_msat fromwire_amount_msat(const u8 **cursor UNNEEDED, size_t *max UNNEEDED)
{ fprintf(stderr, "fromwire_amount_msat called!\n"); abort(); }
/* Generated stub for fromwire_amount_sat */
struct amount_sat fromwire_amount_sat(const u8 **cursor UNNEEDED, size_t *max UNNEEDED)
{ fprintf(stderr, "fromwire_amount_sat called!\n"); abort(); }
/* Generated stub for fromwire_channel_id */
bool fromwire_channel_id(const u8 **cursor UNNEEDED, size_t *max UNNEEDED,
			 struct channel_id *channel_id UNNEEDED)
{ fprintf(stderr, "fromwire_channel_id called!\n"); abort(); }
/* Generated stub for fromwire_connectd_send_onionmsg */
bool fromwire_connectd_send_onionmsg(const tal_t *ctx UNNEEDED, const void *p UNNEEDED, bool *obs2 UNNEEDED, struct node_id *id UNNEEDED, u8 **onion UNNEEDED, struct pubkey *blinding UNNEEDED)
{ fprintf(stderr, "fromwire_connectd_send_onionmsg called!\n"); abort(); }
/* Generated stub for fromwire_node_id */
void fromwire_node_id(const u8 **cursor UNNEEDED, size_t *max UNNEEDED, struct node_id *id UNNEEDED)
{ fprintf(stderr, "fromwire_node_id called!\n"); abort(); }
/* Generated stub for fromwire_wireaddr */
bool fromwire_wireaddr(const u8 **cursor UNNEEDED, size_t *max UNNEEDED, struct wireaddr *addr UNNEEDED)
{ fprintf(stderr, "fromwire_wireaddr called!\n"); abort(); }
/* Generated stub for inject_peer_msg */
void inject_peer_msg(struct peer *peer UNNEEDED, const u8 *msg TAKES UNNEEDED)
{ fprintf(stderr, "inject_peer_msg called!\n"); abort(); }
/* Generated stub for master_badmsg */
void master_badmsg(u32 type_expected UNNEEDED, const u8 *msg)
{ fprintf(stderr, "master_badmsg called!\n"); abort(); }
/* Generated stub for new_onionreply */
struct onionreply *new_onionreply(const tal_t *ctx UNNEEDED, const u8 *contents TAKES UNNEEDED)
{ fprintf(stderr, "new_onionreply called!\n"); abort(); }
/* Generated stub for node_id_from_pubkey */
void node_id_from_pubkey(struct node_id *id UNNEEDED, const struct pubkey *key UNNEEDED)
{ fprintf(stderr, "node_id_from_pubkey called!\n"); abort(); }
/* Generated stub for pubkey_from_node_id */
bool pubkey_from_node_id(struct pubkey *key UNNEEDED, const struct node_id *id UNNEEDED)
{ fprintf(stderr, "pubkey_from_node_id called!\n"); abort(); }
/* Generated stub for status_fmt */
void status_fmt(enum log_level level UNNEEDED,
		const struct node_id *peer UNNEEDED,
		const char *fmt UNNEEDED, ...)

{ fprintf(stderr, "status_fmt called!\n"); abort(); }
/* Generated stub for towire */
void towire(u8 **pptr UNNEEDED, const void *data UNNEEDED, size_t len UNNEEDED)
{ fprintf(stderr, "towire called!\n"); abort(); }
/* Generated stub for towire_amount_msat */
void towire_amount_msat(u8 **pptr UNNEEDED, const struct amount_msat msat UNNEEDED)
{ fprintf(stderr, "towire_amount_msat called!\n"); abort(); }
/* Generated stub for towire_amount_sat */
void towire_amount_sat(u8 **pptr UNNEEDED, const struct amount_sat sat UNNEEDED)
{ fprintf(stderr, "towire_amount_sat called!\n"); abort(); }
/* Generated stub for towire_bool */
void towire_bool(u8 **pptr UNNEEDED, bool v UNNEEDED)
{ fprintf(stderr, "towire_bool called!\n"); abort(); }
/* Generated stub for towire_channel_id */
void towire_channel_id(u8 **pptr UNNEEDED, const struct channel_id *channel_id UNNEEDED)
{ fprintf(stderr, "towire_channel_id called!\n"); abort(); }
/* Generated stub for towire_connectd_got_onionmsg_to_us */
u8 *towire_connectd_got_onionmsg_to_us(const tal_t *ctx UNNEEDED, bool obs2 UNNEEDED, const struct pubkey *node_alias UNNEEDED, const struct secret *self_id UNNEEDED, const struct pubkey *reply_blinding UNNEEDED, const struct pubkey *reply_first_node UNNEEDED, const struct onionmsg_path **reply_path UNNEEDED, const u8 *rawmsg UNNEEDED)
{ fprintf(stderr, "towire_connectd_got_onionmsg_to_us called!\n"); abort(); }
/* Generated stub for towire_node_id */
void towire_node_id(u8 **pptr UNNEEDED, const struct node_id *id UNNEEDED)
{ fprintf(stderr, "towire_node_id called!\n"); abort(); }
/* Generated stub for towire_pad */
void towire_pad(u8 **pptr UNNEEDED, size_t num UNNEEDED)
{ fprintf(stderr, "towire_pad called!\n"); abort(); }
/* Generated stub for towire_secp256k1_ecdsa_signature */
void towire_secp256k1_ecdsa_signature(u8 **pptr UNNEEDED,
			      const secp256k1_ecdsa_signature *signature UNNEEDED)
{ fprintf(stderr, "towire_secp256k1_ecdsa_signature called!\n"); abort(); }
/* Generated stub for towire_sha256 */
void towire_sha256(u8 **pptr UNNEEDED, const struct sha256 *sha256 UNNEEDED)
{ fprintf(stderr, "towire_sha256 called!\n"); abort(); }
/* Generated stub for towire_tu32 */
void towire_tu32(u8 **pptr UNNEEDED, u32 v UNNEEDED)
{ fprintf(stderr, "towire_tu32 called!\n"); abort(); }
/* Generated stub for towire_tu64 */
void towire_tu64(u8 **pptr UNNEEDED, u64 v UNNEEDED)
{ fprintf(stderr, "towire_tu64 called!\n"); abort(); }
/* Generated stub for towire_u16 */
void towire_u16(u8 **pptr UNNEEDED, u16 v UNNEEDED)
{ fprintf(stderr, "towire_u16 called!\n"); abort(); }
/* Generated stub for towire_u32 */
void towire_u32(u8 **pptr UNNEEDED, u32 v UNNEEDED)
{ fprintf(stderr, "towire_u32 called!\n"); abort(); }
/* Generated stub for towire_u64 */
void towire_u64(u8 **pptr UNNEEDED, u64 v UNNEEDED)
{ fprintf(stderr, "towire_u64 called!\n"); abort(); }
/* Generated stub for towire_u8 */
void towire_u8(u8 **pptr UNNEEDED, u8 v UNNEEDED)
{ fprintf(stderr, "towire_u8 called!\n"); abort(); }
/* Generated stub for towire_u8_array */
void towire_u8_array(u8 **pptr UNNEEDED, const u8 *arr UNNEEDED, size_t num UNNEEDED)
{ fprintf(stderr, "towire_u8_array called!\n"); abort(); }
/* Generated stub for towire_warningfmt */
u8 *towire_warningfmt(const tal_t *ctx UNNEEDED,
		      const struct channel_id *channel UNNEEDED,
		      const char *fmt UNNEEDED, ...)
{ fprintf(stderr, "towire_warningfmt called!\n"); abort(); }
/* Generated stub for towire_wireaddr */
void towire_wireaddr(u8 **pptr UNNEEDED, const struct wireaddr *addr UNNEEDED)
{ fprintf(stderr, "towire_wireaddr called!\n"); abort(); }
/* AUTOGENERATED MOCKS END */

/* Updated each time, as we pretend to be Alice, Bob, Carol */
static const struct privkey *mykey;

static void test_ecdh(const struct pubkey *point, struct secret *ss)
{
	if (secp256k1_ecdh(secp256k1_ctx, ss->data, &point->pubkey,
			   mykey->secret.data, NULL, NULL) != 1)
		abort();
}

static void json_strfield(const char *name, const char *val)
{
	printf("\t\"%s\": \"%s\",\n", name, val);
}

static void json_onionmsg_payload(const struct tlv_obs2_onionmsg_payload *om)
{
	if (om->reply_path) {
		printf("\t\"reply_path\": {\n");
		json_strfield("first_node_id",
			      type_to_string(tmpctx, struct pubkey,
					     &om->reply_path->first_node_id));
		json_strfield("blinding",
			      type_to_string(tmpctx, struct pubkey,
					     &om->reply_path->blinding));
		printf("\t\"path\": [\n");
		for (size_t i = 0; i < tal_count(om->reply_path->path); i++) {
			json_strfield("node_id",
				      type_to_string(tmpctx, struct pubkey,
						     &om->reply_path->path[i]->node_id));
			json_strfield("encrypted_recipient_data",
				      tal_hex(tmpctx,
					      om->reply_path->path[i]->encrypted_recipient_data));
		}
		printf("]}\n");
	}
	if (om->invoice)
		json_strfield("invoice", tal_hex(tmpctx, om->invoice));
	if (om->invoice_request)
		json_strfield("invoice_request",
			      tal_hex(tmpctx, om->invoice_request));
	if (om->invoice_error)
		json_strfield("invoice_error",
			      tal_hex(tmpctx, om->invoice_error));
}

/* Return next onion (and updates blinding), or NULL */
static u8 *json_test(const char *testname,
		     const u8 *data,
		     const struct privkey *me,
		     const struct privkey *blinding_priv,
		     struct pubkey *blinding)
{
	struct pubkey my_id, next_node;
	struct secret ss, onion_ss;
	struct pubkey ephemeral;
	struct route_step *rs;
	const u8 *cursor;
	size_t max, maxlen;
	struct onionpacket *op;
	struct tlv_obs2_onionmsg_payload *om;

	op = parse_onionpacket(tmpctx, data, tal_bytelen(data), NULL);
	assert(op);

	pubkey_from_privkey(me, &my_id);
	printf("{");
	json_strfield("test name", testname);
	json_strfield("reader_privkey",
		      type_to_string(tmpctx, struct privkey, me));
	json_strfield("reader_id",
		      type_to_string(tmpctx, struct pubkey, &my_id));

	if (blinding_priv)
		json_strfield("blinding_privkey",
			      type_to_string(tmpctx, struct privkey,
					     blinding_priv));
	json_strfield("blinding",
		      type_to_string(tmpctx, struct pubkey, blinding));
	printf("\"onionmsg\": {\n");
	json_strfield("raw", tal_hex(tmpctx, data));
	json_strfield("version", tal_fmt(tmpctx, "%i", op->version));
	json_strfield("public_key",
		      type_to_string(tmpctx, struct pubkey, &op->ephemeralkey));
	json_strfield("hop_payloads",
		      tal_hex(tmpctx, op->routinginfo));
	json_strfield("hmac",
		      tal_hexstr(tmpctx, &op->hmac, sizeof(op->hmac)));
	printf("},\n");

	ephemeral = op->ephemeralkey;

	/* Set this for test_ecdh */
	mykey = me;
	assert(unblind_onion(blinding, test_ecdh, &ephemeral, &ss));
	json_strfield("ECDH shared secret",
		      type_to_string(tmpctx, struct secret, &ss));
	/* Reproduce internal calc from unblind_onion */
	{
		struct secret hmac;
		subkey_from_hmac("blinded_node_id", &ss, &hmac);
		json_strfield("HMAC256(\\\"blinded_node_id\\\", ss(i)) * k(i)",
			      type_to_string(tmpctx, struct secret, &hmac));
	}
	json_strfield("Tweaked onion pubkey",
		      type_to_string(tmpctx, struct pubkey, &ephemeral));

	/* Now get onion shared secret and parse it. */
	test_ecdh(&ephemeral, &onion_ss);
	json_strfield("onion shared secret",
		      type_to_string(tmpctx, struct secret, &onion_ss));
	rs = process_onionpacket(tmpctx, op, &onion_ss, NULL, 0, false);
	assert(rs);

	printf("\"onion contents\": {\n");
	json_strfield("raw", tal_hex(tmpctx, rs->raw_payload));

	cursor = rs->raw_payload;
	max = tal_bytelen(rs->raw_payload);
	maxlen = fromwire_bigsize(&cursor, &max);
	json_strfield("length", tal_fmt(tmpctx, "%zu", maxlen));
	json_strfield("rawtlv", tal_hexstr(tmpctx, cursor, maxlen));
	json_strfield("hmac", tal_hexstr(tmpctx, rs->next->hmac.bytes,
					 sizeof(rs->next->hmac.bytes)));
	om = tlv_obs2_onionmsg_payload_new(tmpctx);
	assert(fromwire_obs2_onionmsg_payload(&cursor, &maxlen, om));

	json_onionmsg_payload(om);

	/* We expect one of these. */
	assert(om->enctlv);

	printf("\t\"encrypted_data_tlv\": {\n");
	json_strfield("raw", tal_hex(tmpctx, om->enctlv));

	if (rs->nextcase == ONION_END) {
		struct secret *self_id;
		struct pubkey alias;
		assert(decrypt_obs2_final_enctlv(tmpctx,
						 blinding, &ss,
						 om->enctlv,
						 &my_id, &alias, &self_id));
		if (self_id) {
			json_strfield("self_id",
				      type_to_string(tmpctx, struct secret,
						     self_id));
		}
		printf("}\n");
		return NULL;
	} else {
		assert(decrypt_obs2_enctlv(blinding, &ss, om->enctlv, &next_node,
					   blinding));
		json_strfield("next_node",
			      type_to_string(tmpctx, struct pubkey, &next_node));
		json_strfield("next_blinding",
			      type_to_string(tmpctx, struct pubkey,
					     blinding));
		printf("}");
		printf("},\n");
		return serialize_onionpacket(tmpctx, rs->next);
	}
}

int main(int argc, char *argv[])
{
	struct onionpacket *op;
	u8 *data;
	struct privkey alice, bob, carol, dave, blinding_priv;
	struct pubkey alice_id, bob_id, carol_id, dave_id;
	struct pubkey blinding;

	common_setup(argv[0]);

	memset(&alice, 'A', sizeof(alice));
	memset(&bob, 'B', sizeof(bob));
	memset(&carol, 'C', sizeof(carol));
	memset(&dave, 'D', sizeof(dave));
	pubkey_from_privkey(&alice, &alice_id);
	pubkey_from_privkey(&bob, &bob_id);
	pubkey_from_privkey(&carol, &carol_id);
	pubkey_from_privkey(&dave, &dave_id);

	/* ThomasH sends via email:
	 *
	 *  {
	 *  "version":0,
	 *  "public_key":
	 *  "0256b328b30c8bf5839e24058747879408bdb36241dc9c2e7c619faa12b2920967",
	 *  "hop_payloads":
	 *  "37df67dcefdb678725cb8074d3224dfe235ba3f22f71ac8a2c9d1398b1175295b1dd3f14c02d698021e8a8856637306c6f195e01494eb8dc636b4462367533a84786b8592e580086cdf0f1c58b77eb68703a2fb82ecc2e91307a25b6d5e4045174551b1c867264d3905e4f05b2e5bcfed7e7276660bf7e956bce5afa395e7e4c15883b856bc93dd9d6a968838ef51314d38dd41e5ab84b8846dca3c61d87e55780e7a7da336a965a4652263413cdef41daa68f7bb7cd4d566c19a1c4eece369c47e604575f38e7a246a985c3441b60ae33c564395bb7a4bbe28325ccdb07503285dacf90b5e09f4e455fb42459741f9d497000298b99f1e70adc28f59a1be85a96952f27b6a6c5d6a08822b4f5cae05daa6c2ce2f8ca5fdd4e8f0df46b94791b3159fe8eace11bcf8d58be425b49ce2b47c007affefd5cea785c1996ad805f8c8c5ca79f15ab26e2bd4080b1d74328e7ce5bd2a579c71a6bd25f33f2ce475a2cfbe67ed1f4eb8fbd86920f41d573488abe059166aabbc3be187c435423ead6a5473994e0246efe76e419893aa2d7566b2645f3496d97585de9c92b8c5a5226398cc459ce84abc02fe2b45b5ecaf21961730d4a34bbe6fdfe720e71e3d81a494c01080d8039360d534c6ee5a3c47a1874e526969add9126b30d9192f85ba45bcfd7029cc7560f0e25e14b5deaa805360c4967705e85325ac055922863470f5397e8404022488caebf9204acd6cb02a11088aebf7e497b4ff1172f0a9c6bf980914cc4eb42fc78b457add549abf1134f84922b217502938b42d10b35079f44c5168d4c3e9fe7ca8094ef72ed73ef84f1d3530b6b3545f9f4f013e7e8cbcf2619f57754a7380ce6a9532ee14c55990faa43df6c09530a314b5f4ce597f5ec9b776e8597ce258ac47dac43bd3ac9e52788ff3a66b7dc07cd1bc3e6d197339d85fa8d3d6c3054dd1a5e416c714b544de6eb55209e40e3cac412a51748370160d2d73b6d97abd62f7bae70df27cd199c511fa693019c5717d471e934906b98cd974fda4dd1cb5e2d721044a0be2bdf24d0971e09f2f39488fe389fc5230699b4df7cec7447e5be4ea49bd7c3fe1a5ec7358510dc1dd9c1a8da68c0863188d80549e49f7c00f57d2009b2427b2aed1569603fc247734039469f9fdf3ddd3a22fa95c5d8066a468327a02b474c9915419af82c8edc67686984767fe7885207c6820f6c2e57cb8fd0bcb9981ebc8065c74e970a5d593c3b73ee25a0877ca096a9f7edfee6d43bd817c7d415fea9abb6f206c61aa36942df9318762a76b9da26d0d41a0ae9eee042a175f82dc134bf6f2d46a218db358d6852940e6e30df4a58ac6cb409e7ce99afe1e3f42768bd617af4d0a235d0ba0dd5075f9cc091784395d30e7e42d4e006db21bea9b45d1f122b75c051e84e2281573ef54ebad053218fff0cc28ea89a06adc218d4134f407654990592e75462f5ee4a463c1e46425222d48761162da8049613cafd7ecc52ff8024e9d58512b958e3a3d12dede84e1441247700bca0f992875349448b430683c756438fd4e91f3d44f3cf624ed21f3c63cf92615ecc201d0cd3159b1b3fccd8f29d2daba9ac5ba87b1dd2f83323a2b2d3176b803ce9c7bdc4bae615925eb22a213df1eeb2f8ff95586536caf042d565984aacf1425a120a5d8d7a9cbb70bf4852e116b89ff5b198d672220af2be4246372e7c3836cf50d732212a3e3346ff92873ace57fa687b2b1aab3e8dc6cb9f93f865d998cff0a1680d9012a9597c90a070e525f66226cc287814f4ac4157b15a0b25aa110946cd69fd404fafd5656669bfd1d9e509eabc004c5a",
	 *  "hmac": "564bb85911bea8f90d306f4acdafa1c0887619ac72606b11e6b2765734d810ac"
	 *  }
	 */
	op = tal(tmpctx, struct onionpacket);
	op->version = 0;
	assert(pubkey_from_hexstr("0256b328b30c8bf5839e24058747879408bdb36241dc9c2e7c619faa12b2920967", strlen("0256b328b30c8bf5839e24058747879408bdb36241dc9c2e7c619faa12b2920967"), &op->ephemeralkey));
	assert(hex_decode("564bb85911bea8f90d306f4acdafa1c0887619ac72606b11e6b2765734d810ac",
			  strlen("564bb85911bea8f90d306f4acdafa1c0887619ac72606b11e6b2765734d810ac"),
			  &op->hmac, sizeof(op->hmac)));
	op->routinginfo = tal_hexdata(op, "37df67dcefdb678725cb8074d3224dfe235ba3f22f71ac8a2c9d1398b1175295b1dd3f14c02d698021e8a8856637306c6f195e01494eb8dc636b4462367533a84786b8592e580086cdf0f1c58b77eb68703a2fb82ecc2e91307a25b6d5e4045174551b1c867264d3905e4f05b2e5bcfed7e7276660bf7e956bce5afa395e7e4c15883b856bc93dd9d6a968838ef51314d38dd41e5ab84b8846dca3c61d87e55780e7a7da336a965a4652263413cdef41daa68f7bb7cd4d566c19a1c4eece369c47e604575f38e7a246a985c3441b60ae33c564395bb7a4bbe28325ccdb07503285dacf90b5e09f4e455fb42459741f9d497000298b99f1e70adc28f59a1be85a96952f27b6a6c5d6a08822b4f5cae05daa6c2ce2f8ca5fdd4e8f0df46b94791b3159fe8eace11bcf8d58be425b49ce2b47c007affefd5cea785c1996ad805f8c8c5ca79f15ab26e2bd4080b1d74328e7ce5bd2a579c71a6bd25f33f2ce475a2cfbe67ed1f4eb8fbd86920f41d573488abe059166aabbc3be187c435423ead6a5473994e0246efe76e419893aa2d7566b2645f3496d97585de9c92b8c5a5226398cc459ce84abc02fe2b45b5ecaf21961730d4a34bbe6fdfe720e71e3d81a494c01080d8039360d534c6ee5a3c47a1874e526969add9126b30d9192f85ba45bcfd7029cc7560f0e25e14b5deaa805360c4967705e85325ac055922863470f5397e8404022488caebf9204acd6cb02a11088aebf7e497b4ff1172f0a9c6bf980914cc4eb42fc78b457add549abf1134f84922b217502938b42d10b35079f44c5168d4c3e9fe7ca8094ef72ed73ef84f1d3530b6b3545f9f4f013e7e8cbcf2619f57754a7380ce6a9532ee14c55990faa43df6c09530a314b5f4ce597f5ec9b776e8597ce258ac47dac43bd3ac9e52788ff3a66b7dc07cd1bc3e6d197339d85fa8d3d6c3054dd1a5e416c714b544de6eb55209e40e3cac412a51748370160d2d73b6d97abd62f7bae70df27cd199c511fa693019c5717d471e934906b98cd974fda4dd1cb5e2d721044a0be2bdf24d0971e09f2f39488fe389fc5230699b4df7cec7447e5be4ea49bd7c3fe1a5ec7358510dc1dd9c1a8da68c0863188d80549e49f7c00f57d2009b2427b2aed1569603fc247734039469f9fdf3ddd3a22fa95c5d8066a468327a02b474c9915419af82c8edc67686984767fe7885207c6820f6c2e57cb8fd0bcb9981ebc8065c74e970a5d593c3b73ee25a0877ca096a9f7edfee6d43bd817c7d415fea9abb6f206c61aa36942df9318762a76b9da26d0d41a0ae9eee042a175f82dc134bf6f2d46a218db358d6852940e6e30df4a58ac6cb409e7ce99afe1e3f42768bd617af4d0a235d0ba0dd5075f9cc091784395d30e7e42d4e006db21bea9b45d1f122b75c051e84e2281573ef54ebad053218fff0cc28ea89a06adc218d4134f407654990592e75462f5ee4a463c1e46425222d48761162da8049613cafd7ecc52ff8024e9d58512b958e3a3d12dede84e1441247700bca0f992875349448b430683c756438fd4e91f3d44f3cf624ed21f3c63cf92615ecc201d0cd3159b1b3fccd8f29d2daba9ac5ba87b1dd2f83323a2b2d3176b803ce9c7bdc4bae615925eb22a213df1eeb2f8ff95586536caf042d565984aacf1425a120a5d8d7a9cbb70bf4852e116b89ff5b198d672220af2be4246372e7c3836cf50d732212a3e3346ff92873ace57fa687b2b1aab3e8dc6cb9f93f865d998cff0a1680d9012a9597c90a070e525f66226cc287814f4ac4157b15a0b25aa110946cd69fd404fafd5656669bfd1d9e509eabc004c5a",
				     strlen("37df67dcefdb678725cb8074d3224dfe235ba3f22f71ac8a2c9d1398b1175295b1dd3f14c02d698021e8a8856637306c6f195e01494eb8dc636b4462367533a84786b8592e580086cdf0f1c58b77eb68703a2fb82ecc2e91307a25b6d5e4045174551b1c867264d3905e4f05b2e5bcfed7e7276660bf7e956bce5afa395e7e4c15883b856bc93dd9d6a968838ef51314d38dd41e5ab84b8846dca3c61d87e55780e7a7da336a965a4652263413cdef41daa68f7bb7cd4d566c19a1c4eece369c47e604575f38e7a246a985c3441b60ae33c564395bb7a4bbe28325ccdb07503285dacf90b5e09f4e455fb42459741f9d497000298b99f1e70adc28f59a1be85a96952f27b6a6c5d6a08822b4f5cae05daa6c2ce2f8ca5fdd4e8f0df46b94791b3159fe8eace11bcf8d58be425b49ce2b47c007affefd5cea785c1996ad805f8c8c5ca79f15ab26e2bd4080b1d74328e7ce5bd2a579c71a6bd25f33f2ce475a2cfbe67ed1f4eb8fbd86920f41d573488abe059166aabbc3be187c435423ead6a5473994e0246efe76e419893aa2d7566b2645f3496d97585de9c92b8c5a5226398cc459ce84abc02fe2b45b5ecaf21961730d4a34bbe6fdfe720e71e3d81a494c01080d8039360d534c6ee5a3c47a1874e526969add9126b30d9192f85ba45bcfd7029cc7560f0e25e14b5deaa805360c4967705e85325ac055922863470f5397e8404022488caebf9204acd6cb02a11088aebf7e497b4ff1172f0a9c6bf980914cc4eb42fc78b457add549abf1134f84922b217502938b42d10b35079f44c5168d4c3e9fe7ca8094ef72ed73ef84f1d3530b6b3545f9f4f013e7e8cbcf2619f57754a7380ce6a9532ee14c55990faa43df6c09530a314b5f4ce597f5ec9b776e8597ce258ac47dac43bd3ac9e52788ff3a66b7dc07cd1bc3e6d197339d85fa8d3d6c3054dd1a5e416c714b544de6eb55209e40e3cac412a51748370160d2d73b6d97abd62f7bae70df27cd199c511fa693019c5717d471e934906b98cd974fda4dd1cb5e2d721044a0be2bdf24d0971e09f2f39488fe389fc5230699b4df7cec7447e5be4ea49bd7c3fe1a5ec7358510dc1dd9c1a8da68c0863188d80549e49f7c00f57d2009b2427b2aed1569603fc247734039469f9fdf3ddd3a22fa95c5d8066a468327a02b474c9915419af82c8edc67686984767fe7885207c6820f6c2e57cb8fd0bcb9981ebc8065c74e970a5d593c3b73ee25a0877ca096a9f7edfee6d43bd817c7d415fea9abb6f206c61aa36942df9318762a76b9da26d0d41a0ae9eee042a175f82dc134bf6f2d46a218db358d6852940e6e30df4a58ac6cb409e7ce99afe1e3f42768bd617af4d0a235d0ba0dd5075f9cc091784395d30e7e42d4e006db21bea9b45d1f122b75c051e84e2281573ef54ebad053218fff0cc28ea89a06adc218d4134f407654990592e75462f5ee4a463c1e46425222d48761162da8049613cafd7ecc52ff8024e9d58512b958e3a3d12dede84e1441247700bca0f992875349448b430683c756438fd4e91f3d44f3cf624ed21f3c63cf92615ecc201d0cd3159b1b3fccd8f29d2daba9ac5ba87b1dd2f83323a2b2d3176b803ce9c7bdc4bae615925eb22a213df1eeb2f8ff95586536caf042d565984aacf1425a120a5d8d7a9cbb70bf4852e116b89ff5b198d672220af2be4246372e7c3836cf50d732212a3e3346ff92873ace57fa687b2b1aab3e8dc6cb9f93f865d998cff0a1680d9012a9597c90a070e525f66226cc287814f4ac4157b15a0b25aa110946cd69fd404fafd5656669bfd1d9e509eabc004c5a"));

	data = serialize_onionpacket(tmpctx, op);
	printf("[\n");

	memset(&blinding_priv, 5, sizeof(blinding_priv));
	pubkey_from_privkey(&blinding_priv, &blinding);

	data = json_test("onion message for Alice",
			 data,
			 &alice,
			 &blinding_priv,
			 &blinding);

	data = json_test("onion message for Bob",
			 data,
			 &bob,
			 NULL,
			 &blinding);

	data = json_test("onion message for Carol",
			 data,
			 &carol,
			 NULL,
			 &blinding);

	data = json_test("onion message for Dave",
			 data,
			 &dave,
			 NULL,
			 &blinding);

	assert(!data);
	printf("]\n");

	common_shutdown();
	return 0;
}
