#ifndef LIGHTNINGD_WALLET_GEN_DB_POSTGRES
#define LIGHTNINGD_WALLET_GEN_DB_POSTGRES

#include <config.h>
#include <wallet/db_common.h>

#if HAVE_POSTGRES

struct db_query db_postgres_queries[] = {

    {
         .name = "CREATE TABLE version (version INTEGER)",
         .query = "CREATE TABLE version (version INTEGER)",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO version VALUES (1)",
         .query = "INSERT INTO version VALUES (1)",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE outputs (  prev_out_tx BLOB, prev_out_index INTEGER, value BIGINT, type INTEGER, status INTEGER, keyindex INTEGER, PRIMARY KEY (prev_out_tx, prev_out_index));",
         .query = "CREATE TABLE outputs (  prev_out_tx BYTEA, prev_out_index INTEGER, value BIGINT, type INTEGER, status INTEGER, keyindex INTEGER, PRIMARY KEY (prev_out_tx, prev_out_index));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE vars (  name VARCHAR(32), val VARCHAR(255), PRIMARY KEY (name));",
         .query = "CREATE TABLE vars (  name VARCHAR(32), val VARCHAR(255), PRIMARY KEY (name));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE shachains (  id BIGSERIAL, min_index BIGINT, num_valid BIGINT, PRIMARY KEY (id));",
         .query = "CREATE TABLE shachains (  id BIGSERIAL, min_index BIGINT, num_valid BIGINT, PRIMARY KEY (id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE shachain_known (  shachain_id BIGINT REFERENCES shachains(id) ON DELETE CASCADE, pos INTEGER, idx BIGINT, hash BLOB, PRIMARY KEY (shachain_id, pos));",
         .query = "CREATE TABLE shachain_known (  shachain_id BIGINT REFERENCES shachains(id) ON DELETE CASCADE, pos INTEGER, idx BIGINT, hash BYTEA, PRIMARY KEY (shachain_id, pos));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE peers (  id BIGSERIAL, node_id BLOB UNIQUE, address TEXT, PRIMARY KEY (id));",
         .query = "CREATE TABLE peers (  id BIGSERIAL, node_id BYTEA UNIQUE, address TEXT, PRIMARY KEY (id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE channels (  id BIGSERIAL,  peer_id BIGINT REFERENCES peers(id) ON DELETE CASCADE,  short_channel_id TEXT,  channel_config_local BIGINT,  channel_config_remote BIGINT,  state INTEGER,  funder INTEGER,  channel_flags INTEGER,  minimum_depth INTEGER,  next_index_local BIGINT,  next_index_remote BIGINT,  next_htlc_id BIGINT,  funding_tx_id BLOB,  funding_tx_outnum INTEGER,  funding_satoshi BIGINT,  funding_locked_remote INTEGER,  push_msatoshi BIGINT,  msatoshi_local BIGINT,  fundingkey_remote BLOB,  revocation_basepoint_remote BLOB,  payment_basepoint_remote BLOB,  htlc_basepoint_remote BLOB,  delayed_payment_basepoint_remote BLOB,  per_commit_remote BLOB,  old_per_commit_remote BLOB,  local_feerate_per_kw INTEGER,  remote_feerate_per_kw INTEGER,  shachain_remote_id BIGINT,  shutdown_scriptpubkey_remote BLOB,  shutdown_keyidx_local BIGINT,  last_sent_commit_state BIGINT,  last_sent_commit_id INTEGER,  last_tx BLOB,  last_sig BLOB,  closing_fee_received INTEGER,  closing_sig_received BLOB,  PRIMARY KEY (id));",
         .query = "CREATE TABLE channels (  id BIGSERIAL,  peer_id BIGINT REFERENCES peers(id) ON DELETE CASCADE,  short_channel_id TEXT,  channel_config_local BIGINT,  channel_config_remote BIGINT,  state INTEGER,  funder INTEGER,  channel_flags INTEGER,  minimum_depth INTEGER,  next_index_local BIGINT,  next_index_remote BIGINT,  next_htlc_id BIGINT,  funding_tx_id BYTEA,  funding_tx_outnum INTEGER,  funding_satoshi BIGINT,  funding_locked_remote INTEGER,  push_msatoshi BIGINT,  msatoshi_local BIGINT,  fundingkey_remote BYTEA,  revocation_basepoint_remote BYTEA,  payment_basepoint_remote BYTEA,  htlc_basepoint_remote BYTEA,  delayed_payment_basepoint_remote BYTEA,  per_commit_remote BYTEA,  old_per_commit_remote BYTEA,  local_feerate_per_kw INTEGER,  remote_feerate_per_kw INTEGER,  shachain_remote_id BIGINT,  shutdown_scriptpubkey_remote BYTEA,  shutdown_keyidx_local BIGINT,  last_sent_commit_state BIGINT,  last_sent_commit_id INTEGER,  last_tx BYTEA,  last_sig BYTEA,  closing_fee_received INTEGER,  closing_sig_received BYTEA,  PRIMARY KEY (id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE channel_configs (  id BIGSERIAL,  dust_limit_satoshis BIGINT,  max_htlc_value_in_flight_msat BIGINT,  channel_reserve_satoshis BIGINT,  htlc_minimum_msat BIGINT,  to_self_delay INTEGER,  max_accepted_htlcs INTEGER,  PRIMARY KEY (id));",
         .query = "CREATE TABLE channel_configs (  id BIGSERIAL,  dust_limit_satoshis BIGINT,  max_htlc_value_in_flight_msat BIGINT,  channel_reserve_satoshis BIGINT,  htlc_minimum_msat BIGINT,  to_self_delay INTEGER,  max_accepted_htlcs INTEGER,  PRIMARY KEY (id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE channel_htlcs (  id BIGSERIAL,  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE,  channel_htlc_id BIGINT,  direction INTEGER,  origin_htlc BIGINT,  msatoshi BIGINT,  cltv_expiry INTEGER,  payment_hash BLOB,  payment_key BLOB,  routing_onion BLOB,  failuremsg BLOB,  malformed_onion INTEGER,  hstate INTEGER,  shared_secret BLOB,  PRIMARY KEY (id),  UNIQUE (channel_id, channel_htlc_id, direction));",
         .query = "CREATE TABLE channel_htlcs (  id BIGSERIAL,  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE,  channel_htlc_id BIGINT,  direction INTEGER,  origin_htlc BIGINT,  msatoshi BIGINT,  cltv_expiry INTEGER,  payment_hash BYTEA,  payment_key BYTEA,  routing_onion BYTEA,  failuremsg BYTEA,  malformed_onion INTEGER,  hstate INTEGER,  shared_secret BYTEA,  PRIMARY KEY (id),  UNIQUE (channel_id, channel_htlc_id, direction));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE invoices (  id BIGSERIAL,  state INTEGER,  msatoshi BIGINT,  payment_hash BLOB,  payment_key BLOB,  label TEXT,  PRIMARY KEY (id),  UNIQUE (label),  UNIQUE (payment_hash));",
         .query = "CREATE TABLE invoices (  id BIGSERIAL,  state INTEGER,  msatoshi BIGINT,  payment_hash BYTEA,  payment_key BYTEA,  label TEXT,  PRIMARY KEY (id),  UNIQUE (label),  UNIQUE (payment_hash));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE payments (  id BIGSERIAL,  timestamp INTEGER,  status INTEGER,  payment_hash BLOB,  direction INTEGER,  destination BLOB,  msatoshi BIGINT,  PRIMARY KEY (id),  UNIQUE (payment_hash));",
         .query = "CREATE TABLE payments (  id BIGSERIAL,  timestamp INTEGER,  status INTEGER,  payment_hash BYTEA,  direction INTEGER,  destination BYTEA,  msatoshi BIGINT,  PRIMARY KEY (id),  UNIQUE (payment_hash));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE invoices ADD expiry_time BIGINT;",
         .query = "ALTER TABLE invoices ADD expiry_time BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE invoices SET expiry_time=9223372036854775807;",
         .query = "UPDATE invoices SET expiry_time=9223372036854775807;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE invoices ADD pay_index BIGINT;",
         .query = "ALTER TABLE invoices ADD pay_index BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE UNIQUE INDEX invoices_pay_index ON invoices(pay_index);",
         .query = "CREATE UNIQUE INDEX invoices_pay_index ON invoices(pay_index);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE invoices SET pay_index=id WHERE state=1;",
         .query = "UPDATE invoices SET pay_index=id WHERE state=1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO vars(name, val)  VALUES('next_pay_index',     COALESCE((SELECT MAX(pay_index) FROM invoices WHERE state=1), 0) + 1  );",
         .query = "INSERT INTO vars(name, val)  VALUES('next_pay_index',     COALESCE((SELECT MAX(pay_index) FROM invoices WHERE state=1), 0) + 1  );",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD first_blocknum BIGINT;",
         .query = "ALTER TABLE channels ADD first_blocknum BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET first_blocknum=1 WHERE short_channel_id IS NOT NULL;",
         .query = "UPDATE channels SET first_blocknum=1 WHERE short_channel_id IS NOT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE outputs ADD COLUMN channel_id BIGINT;",
         .query = "ALTER TABLE outputs ADD COLUMN channel_id BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE outputs ADD COLUMN peer_id BLOB;",
         .query = "ALTER TABLE outputs ADD COLUMN peer_id BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE outputs ADD COLUMN commitment_point BLOB;",
         .query = "ALTER TABLE outputs ADD COLUMN commitment_point BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE invoices ADD COLUMN msatoshi_received BIGINT;",
         .query = "ALTER TABLE invoices ADD COLUMN msatoshi_received BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE invoices SET msatoshi_received=0 WHERE state=1;",
         .query = "UPDATE invoices SET msatoshi_received=0 WHERE state=1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD COLUMN last_was_revoke INTEGER;",
         .query = "ALTER TABLE channels ADD COLUMN last_was_revoke INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments RENAME TO temp_payments;",
         .query = "ALTER TABLE payments RENAME TO temp_payments;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE payments (  id BIGSERIAL,  timestamp INTEGER,  status INTEGER,  payment_hash BLOB,  destination BLOB,  msatoshi BIGINT,  PRIMARY KEY (id),  UNIQUE (payment_hash));",
         .query = "CREATE TABLE payments (  id BIGSERIAL,  timestamp INTEGER,  status INTEGER,  payment_hash BYTEA,  destination BYTEA,  msatoshi BIGINT,  PRIMARY KEY (id),  UNIQUE (payment_hash));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO payments SELECT id, timestamp, status, payment_hash, destination, msatoshi FROM temp_payments WHERE direction=1;",
         .query = "INSERT INTO payments SELECT id, timestamp, status, payment_hash, destination, msatoshi FROM temp_payments WHERE direction=1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DROP TABLE temp_payments;",
         .query = "DROP TABLE temp_payments;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD COLUMN payment_preimage BLOB;",
         .query = "ALTER TABLE payments ADD COLUMN payment_preimage BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD COLUMN path_secrets BLOB;",
         .query = "ALTER TABLE payments ADD COLUMN path_secrets BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE invoices ADD paid_timestamp BIGINT;",
         .query = "ALTER TABLE invoices ADD paid_timestamp BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE invoices   SET paid_timestamp = CURRENT_TIMESTAMP() WHERE state = 1;",
         .query = "UPDATE invoices   SET paid_timestamp = EXTRACT(epoch FROM now()) WHERE state = 1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD COLUMN route_nodes BLOB;",
         .query = "ALTER TABLE payments ADD COLUMN route_nodes BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD COLUMN route_channels BLOB;",
         .query = "ALTER TABLE payments ADD COLUMN route_channels BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE htlc_sigs (channelid INTEGER REFERENCES channels(id) ON DELETE CASCADE, signature BLOB);",
         .query = "CREATE TABLE htlc_sigs (channelid INTEGER REFERENCES channels(id) ON DELETE CASCADE, signature BYTEA);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE INDEX channel_idx ON htlc_sigs (channelid)",
         .query = "CREATE INDEX channel_idx ON htlc_sigs (channelid)",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DELETE FROM channels WHERE state=1",
         .query = "DELETE FROM channels WHERE state=1",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE db_upgrades (upgrade_from INTEGER, lightning_version TEXT);",
         .query = "CREATE TABLE db_upgrades (upgrade_from INTEGER, lightning_version TEXT);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DELETE FROM peers WHERE id NOT IN (SELECT peer_id FROM channels);",
         .query = "DELETE FROM peers WHERE id NOT IN (SELECT peer_id FROM channels);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET STATE = 8 WHERE state > 8;",
         .query = "UPDATE channels SET STATE = 8 WHERE state > 8;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE invoices ADD bolt11 TEXT;",
         .query = "ALTER TABLE invoices ADD bolt11 TEXT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE blocks (height INT, hash BLOB, prev_hash BLOB, UNIQUE(height));",
         .query = "CREATE TABLE blocks (height INT, hash BYTEA, prev_hash BYTEA, UNIQUE(height));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE outputs ADD COLUMN confirmation_height INTEGER REFERENCES blocks(height) ON DELETE SET NULL;",
         .query = "ALTER TABLE outputs ADD COLUMN confirmation_height INTEGER REFERENCES blocks(height) ON DELETE SET NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE outputs ADD COLUMN spend_height INTEGER REFERENCES blocks(height) ON DELETE SET NULL;",
         .query = "ALTER TABLE outputs ADD COLUMN spend_height INTEGER REFERENCES blocks(height) ON DELETE SET NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE INDEX output_height_idx ON outputs (confirmation_height, spend_height);",
         .query = "CREATE INDEX output_height_idx ON outputs (confirmation_height, spend_height);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE utxoset ( txid BLOB, outnum INT, blockheight INT REFERENCES blocks(height) ON DELETE CASCADE, spendheight INT REFERENCES blocks(height) ON DELETE SET NULL, txindex INT, scriptpubkey BLOB, satoshis BIGINT, PRIMARY KEY(txid, outnum));",
         .query = "CREATE TABLE utxoset ( txid BYTEA, outnum INT, blockheight INT REFERENCES blocks(height) ON DELETE CASCADE, spendheight INT REFERENCES blocks(height) ON DELETE SET NULL, txindex INT, scriptpubkey BYTEA, satoshis BIGINT, PRIMARY KEY(txid, outnum));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE INDEX short_channel_id ON utxoset (blockheight, txindex, outnum)",
         .query = "CREATE INDEX short_channel_id ON utxoset (blockheight, txindex, outnum)",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE INDEX utxoset_spend ON utxoset (spendheight)",
         .query = "CREATE INDEX utxoset_spend ON utxoset (spendheight)",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET shutdown_keyidx_local=0 WHERE shutdown_keyidx_local = -1;",
         .query = "UPDATE channels SET shutdown_keyidx_local=0 WHERE shutdown_keyidx_local = -1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD failonionreply BLOB;",
         .query = "ALTER TABLE payments ADD failonionreply BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD faildestperm INTEGER;",
         .query = "ALTER TABLE payments ADD faildestperm INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD failindex INTEGER;",
         .query = "ALTER TABLE payments ADD failindex INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD failcode INTEGER;",
         .query = "ALTER TABLE payments ADD failcode INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD failnode BLOB;",
         .query = "ALTER TABLE payments ADD failnode BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD failchannel TEXT;",
         .query = "ALTER TABLE payments ADD failchannel TEXT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD failupdate BLOB;",
         .query = "ALTER TABLE payments ADD failupdate BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE payments   SET path_secrets = NULL     , route_nodes = NULL     , route_channels = NULL WHERE status <> 0;",
         .query = "UPDATE payments   SET path_secrets = NULL     , route_nodes = NULL     , route_channels = NULL WHERE status <> 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD in_payments_offered INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD in_payments_offered INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD in_payments_fulfilled INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD in_payments_fulfilled INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD in_msatoshi_offered BIGINT DEFAULT 0;",
         .query = "ALTER TABLE channels ADD in_msatoshi_offered BIGINT DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD in_msatoshi_fulfilled BIGINT DEFAULT 0;",
         .query = "ALTER TABLE channels ADD in_msatoshi_fulfilled BIGINT DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD out_payments_offered INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD out_payments_offered INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD out_payments_fulfilled INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD out_payments_fulfilled INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD out_msatoshi_offered BIGINT DEFAULT 0;",
         .query = "ALTER TABLE channels ADD out_msatoshi_offered BIGINT DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD out_msatoshi_fulfilled BIGINT DEFAULT 0;",
         .query = "ALTER TABLE channels ADD out_msatoshi_fulfilled BIGINT DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels   SET  in_payments_offered = 0,  in_payments_fulfilled = 0     ,  in_msatoshi_offered = 0,  in_msatoshi_fulfilled = 0     , out_payments_offered = 0, out_payments_fulfilled = 0     , out_msatoshi_offered = 0, out_msatoshi_fulfilled = 0     ;",
         .query = "UPDATE channels   SET  in_payments_offered = 0,  in_payments_fulfilled = 0     ,  in_msatoshi_offered = 0,  in_msatoshi_fulfilled = 0     , out_payments_offered = 0, out_payments_fulfilled = 0     , out_msatoshi_offered = 0, out_msatoshi_fulfilled = 0     ;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD msatoshi_sent BIGINT;",
         .query = "ALTER TABLE payments ADD msatoshi_sent BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE payments SET msatoshi_sent = msatoshi;",
         .query = "UPDATE payments SET msatoshi_sent = msatoshi;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DELETE FROM utxoset WHERE blockheight IN (  SELECT DISTINCT(blockheight)  FROM utxoset LEFT OUTER JOIN blocks on (blockheight = blocks.height)   WHERE blocks.hash IS NULL);",
         .query = "DELETE FROM utxoset WHERE blockheight IN (  SELECT DISTINCT(blockheight)  FROM utxoset LEFT OUTER JOIN blocks on (blockheight = blocks.height)   WHERE blocks.hash IS NULL);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD min_possible_feerate INTEGER;",
         .query = "ALTER TABLE channels ADD min_possible_feerate INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD max_possible_feerate INTEGER;",
         .query = "ALTER TABLE channels ADD max_possible_feerate INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET min_possible_feerate=0, max_possible_feerate=250000;",
         .query = "UPDATE channels SET min_possible_feerate=0, max_possible_feerate=250000;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD msatoshi_to_us_min BIGINT;",
         .query = "ALTER TABLE channels ADD msatoshi_to_us_min BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD msatoshi_to_us_max BIGINT;",
         .query = "ALTER TABLE channels ADD msatoshi_to_us_max BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels   SET msatoshi_to_us_min = msatoshi_local     , msatoshi_to_us_max = msatoshi_local     ;",
         .query = "UPDATE channels   SET msatoshi_to_us_min = msatoshi_local     , msatoshi_to_us_max = msatoshi_local     ;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE transactions (  id BLOB, blockheight INTEGER REFERENCES blocks(height) ON DELETE SET NULL, txindex INTEGER, rawtx BLOB, PRIMARY KEY (id));",
         .query = "CREATE TABLE transactions (  id BYTEA, blockheight INTEGER REFERENCES blocks(height) ON DELETE SET NULL, txindex INTEGER, rawtx BYTEA, PRIMARY KEY (id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD faildetail TEXT;",
         .query = "ALTER TABLE payments ADD faildetail TEXT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE payments   SET faildetail = 'unspecified payment failure reason' WHERE status = 2;",
         .query = "UPDATE payments   SET faildetail = 'unspecified payment failure reason' WHERE status = 2;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE channeltxs (  id BIGSERIAL, channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE, type INTEGER, transaction_id BLOB REFERENCES transactions(id) ON DELETE CASCADE, input_num INTEGER, blockheight INTEGER REFERENCES blocks(height) ON DELETE CASCADE, PRIMARY KEY(id));",
         .query = "CREATE TABLE channeltxs (  id BIGSERIAL, channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE, type INTEGER, transaction_id BYTEA REFERENCES transactions(id) ON DELETE CASCADE, input_num INTEGER, blockheight INTEGER REFERENCES blocks(height) ON DELETE CASCADE, PRIMARY KEY(id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DELETE FROM blocks WHERE height > (SELECT MIN(first_blocknum) FROM channels);",
         .query = "DELETE FROM blocks WHERE height > (SELECT MIN(first_blocknum) FROM channels);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO blocks (height) VALUES ((SELECT MIN(first_blocknum) FROM channels)) ON CONFLICT(height) DO NOTHING;",
         .query = "INSERT INTO blocks (height) VALUES ((SELECT MIN(first_blocknum) FROM channels)) ON CONFLICT(height) DO NOTHING;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DELETE FROM blocks WHERE height IS NULL;",
         .query = "DELETE FROM blocks WHERE height IS NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE invoices ADD description TEXT;",
         .query = "ALTER TABLE invoices ADD description TEXT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD description TEXT;",
         .query = "ALTER TABLE payments ADD description TEXT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD future_per_commitment_point BLOB;",
         .query = "ALTER TABLE channels ADD future_per_commitment_point BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD last_sent_commit BLOB;",
         .query = "ALTER TABLE channels ADD last_sent_commit BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE forwarded_payments (  in_htlc_id BIGINT REFERENCES channel_htlcs(id) ON DELETE SET NULL, out_htlc_id BIGINT REFERENCES channel_htlcs(id) ON DELETE SET NULL, in_channel_scid BIGINT, out_channel_scid BIGINT, in_msatoshi BIGINT, out_msatoshi BIGINT, state INTEGER, UNIQUE(in_htlc_id, out_htlc_id));",
         .query = "CREATE TABLE forwarded_payments (  in_htlc_id BIGINT REFERENCES channel_htlcs(id) ON DELETE SET NULL, out_htlc_id BIGINT REFERENCES channel_htlcs(id) ON DELETE SET NULL, in_channel_scid BIGINT, out_channel_scid BIGINT, in_msatoshi BIGINT, out_msatoshi BIGINT, state INTEGER, UNIQUE(in_htlc_id, out_htlc_id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD faildirection INTEGER;",
         .query = "ALTER TABLE payments ADD faildirection INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE outputs ADD scriptpubkey BLOB;",
         .query = "ALTER TABLE outputs ADD scriptpubkey BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD bolt11 TEXT;",
         .query = "ALTER TABLE payments ADD bolt11 TEXT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD feerate_base INTEGER;",
         .query = "ALTER TABLE channels ADD feerate_base INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD feerate_ppm INTEGER;",
         .query = "ALTER TABLE channels ADD feerate_ppm INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_htlcs ADD received_time BIGINT",
         .query = "ALTER TABLE channel_htlcs ADD received_time BIGINT",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE forwarded_payments ADD received_time BIGINT",
         .query = "ALTER TABLE forwarded_payments ADD received_time BIGINT",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE forwarded_payments ADD resolved_time BIGINT",
         .query = "ALTER TABLE forwarded_payments ADD resolved_time BIGINT",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD remote_upfront_shutdown_script BLOB;",
         .query = "ALTER TABLE channels ADD remote_upfront_shutdown_script BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE forwarded_payments ADD failcode INTEGER;",
         .query = "ALTER TABLE forwarded_payments ADD failcode INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD remote_ann_node_sig BLOB;",
         .query = "ALTER TABLE channels ADD remote_ann_node_sig BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD remote_ann_bitcoin_sig BLOB;",
         .query = "ALTER TABLE channels ADD remote_ann_bitcoin_sig BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE transactions ADD type BIGINT;",
         .query = "ALTER TABLE transactions ADD type BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE transactions ADD channel_id BIGINT;",
         .query = "ALTER TABLE transactions ADD channel_id BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET short_channel_id = REPLACE(short_channel_id, ':', 'x') WHERE short_channel_id IS NOT NULL;",
         .query = "UPDATE channels SET short_channel_id = REPLACE(short_channel_id, ':', 'x') WHERE short_channel_id IS NOT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE payments SET failchannel = REPLACE(failchannel, ':', 'x') WHERE failchannel IS NOT NULL;",
         .query = "UPDATE payments SET failchannel = REPLACE(failchannel, ':', 'x') WHERE failchannel IS NOT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD COLUMN option_static_remotekey INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD COLUMN option_static_remotekey INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE vars ADD COLUMN intval INTEGER",
         .query = "ALTER TABLE vars ADD COLUMN intval INTEGER",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE vars ADD COLUMN blobval BLOB",
         .query = "ALTER TABLE vars ADD COLUMN blobval BYTEA",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE vars SET intval = CAST(val AS INTEGER) WHERE name IN ('bip32_max_index', 'last_processed_block', 'next_pay_index')",
         .query = "UPDATE vars SET intval = CAST(val AS INTEGER) WHERE name IN ('bip32_max_index', 'last_processed_block', 'next_pay_index')",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE vars SET blobval = CAST(val AS BLOB) WHERE name = 'genesis_hash'",
         .query = "UPDATE vars SET blobval = CAST(val AS BYTEA) WHERE name = 'genesis_hash'",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE transaction_annotations (  txid BLOB, idx INTEGER, location INTEGER, type INTEGER, channel BIGINT REFERENCES channels(id), UNIQUE(txid, idx));",
         .query = "CREATE TABLE transaction_annotations (  txid BYTEA, idx INTEGER, location INTEGER, type INTEGER, channel BIGINT REFERENCES channels(id), UNIQUE(txid, idx));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD shutdown_scriptpubkey_local BLOB;",
         .query = "ALTER TABLE channels ADD shutdown_scriptpubkey_local BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE forwarded_payments SET received_time=0 WHERE received_time IS NULL;",
         .query = "UPDATE forwarded_payments SET received_time=0 WHERE received_time IS NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE invoices ADD COLUMN features BLOB DEFAULT '';",
         .query = "ALTER TABLE invoices ADD COLUMN features BYTEA DEFAULT '';",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE payments ( id BIGSERIAL, timestamp INTEGER, status INTEGER, payment_hash BLOB, destination BLOB, msatoshi BIGINT, payment_preimage BLOB, path_secrets BLOB, route_nodes BLOB, route_channels BLOB, failonionreply BLOB, faildestperm INTEGER, failindex INTEGER, failcode INTEGER, failnode BLOB, failchannel TEXT, failupdate BLOB, msatoshi_sent BIGINT, faildetail TEXT, description TEXT, faildirection INTEGER, bolt11 TEXT, total_msat BIGINT, partid BIGINT, PRIMARY KEY (id), UNIQUE (payment_hash, partid))",
         .query = "CREATE TABLE payments ( id BIGSERIAL, timestamp INTEGER, status INTEGER, payment_hash BYTEA, destination BYTEA, msatoshi BIGINT, payment_preimage BYTEA, path_secrets BYTEA, route_nodes BYTEA, route_channels BYTEA, failonionreply BYTEA, faildestperm INTEGER, failindex INTEGER, failcode INTEGER, failnode BYTEA, failchannel TEXT, failupdate BYTEA, msatoshi_sent BIGINT, faildetail TEXT, description TEXT, faildirection INTEGER, bolt11 TEXT, total_msat BIGINT, partid BIGINT, PRIMARY KEY (id), UNIQUE (payment_hash, partid))",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO payments (id, timestamp, status, payment_hash, destination, msatoshi, payment_preimage, path_secrets, route_nodes, route_channels, failonionreply, faildestperm, failindex, failcode, failnode, failchannel, failupdate, msatoshi_sent, faildetail, description, faildirection, bolt11)SELECT id, timestamp, status, payment_hash, destination, msatoshi, payment_preimage, path_secrets, route_nodes, route_channels, failonionreply, faildestperm, failindex, failcode, failnode, failchannel, failupdate, msatoshi_sent, faildetail, description, faildirection, bolt11 FROM temp_payments;",
         .query = "INSERT INTO payments (id, timestamp, status, payment_hash, destination, msatoshi, payment_preimage, path_secrets, route_nodes, route_channels, failonionreply, faildestperm, failindex, failcode, failnode, failchannel, failupdate, msatoshi_sent, faildetail, description, faildirection, bolt11)SELECT id, timestamp, status, payment_hash, destination, msatoshi, payment_preimage, path_secrets, route_nodes, route_channels, failonionreply, faildestperm, failindex, failcode, failnode, failchannel, failupdate, msatoshi_sent, faildetail, description, faildirection, bolt11 FROM temp_payments;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE payments SET total_msat = msatoshi;",
         .query = "UPDATE payments SET total_msat = msatoshi;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE payments SET partid = 0;",
         .query = "UPDATE payments SET partid = 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_htlcs ADD partid BIGINT;",
         .query = "ALTER TABLE channel_htlcs ADD partid BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channel_htlcs SET partid = 0;",
         .query = "UPDATE channel_htlcs SET partid = 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE channel_feerates (  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE,  hstate INTEGER,  feerate_per_kw INTEGER,  UNIQUE (channel_id, hstate));",
         .query = "CREATE TABLE channel_feerates (  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE,  hstate INTEGER,  feerate_per_kw INTEGER,  UNIQUE (channel_id, hstate));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_feerates(channel_id, hstate, feerate_per_kw) SELECT id, 4, local_feerate_per_kw FROM channels WHERE funder = 0;",
         .query = "INSERT INTO channel_feerates(channel_id, hstate, feerate_per_kw) SELECT id, 4, local_feerate_per_kw FROM channels WHERE funder = 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_feerates(channel_id, hstate, feerate_per_kw) SELECT id, 1, remote_feerate_per_kw FROM channels WHERE funder = 0 and local_feerate_per_kw != remote_feerate_per_kw;",
         .query = "INSERT INTO channel_feerates(channel_id, hstate, feerate_per_kw) SELECT id, 1, remote_feerate_per_kw FROM channels WHERE funder = 0 and local_feerate_per_kw != remote_feerate_per_kw;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_feerates(channel_id, hstate, feerate_per_kw) SELECT id, 14, remote_feerate_per_kw FROM channels WHERE funder = 1;",
         .query = "INSERT INTO channel_feerates(channel_id, hstate, feerate_per_kw) SELECT id, 14, remote_feerate_per_kw FROM channels WHERE funder = 1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_feerates(channel_id, hstate, feerate_per_kw) SELECT id, 11, local_feerate_per_kw FROM channels WHERE funder = 1 and local_feerate_per_kw != remote_feerate_per_kw;",
         .query = "INSERT INTO channel_feerates(channel_id, hstate, feerate_per_kw) SELECT id, 11, local_feerate_per_kw FROM channels WHERE funder = 1 and local_feerate_per_kw != remote_feerate_per_kw;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO vars (name, intval) VALUES ('data_version', 0);",
         .query = "INSERT INTO vars (name, intval) VALUES ('data_version', 0);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_htlcs ADD localfailmsg BLOB;",
         .query = "ALTER TABLE channel_htlcs ADD localfailmsg BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channel_htlcs SET localfailmsg=decode('2002', 'hex') WHERE malformed_onion != 0 AND direction = 1;",
         .query = "UPDATE channel_htlcs SET localfailmsg=decode('2002', 'hex') WHERE malformed_onion != 0 AND direction = 1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD our_funding_satoshi BIGINT DEFAULT 0;",
         .query = "ALTER TABLE channels ADD our_funding_satoshi BIGINT DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE penalty_bases (  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE, commitnum BIGINT, txid BLOB, outnum INTEGER, amount BIGINT, PRIMARY KEY (channel_id, commitnum));",
         .query = "CREATE TABLE penalty_bases (  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE, commitnum BIGINT, txid BYTEA, outnum INTEGER, amount BIGINT, PRIMARY KEY (channel_id, commitnum));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_htlcs ADD we_filled INTEGER;",
         .query = "ALTER TABLE channel_htlcs ADD we_filled INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO vars (name, intval) VALUES ('coin_moves_count', 0);",
         .query = "INSERT INTO vars (name, intval) VALUES ('coin_moves_count', 0);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE outputs ADD reserved_til INTEGER DEFAULT NULL;",
         .query = "ALTER TABLE outputs ADD reserved_til INTEGER DEFAULT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD COLUMN option_anchor_outputs INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD COLUMN option_anchor_outputs INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE outputs ADD option_anchor_outputs INTEGER DEFAULT 0;",
         .query = "ALTER TABLE outputs ADD option_anchor_outputs INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD full_channel_id BLOB DEFAULT NULL;",
         .query = "ALTER TABLE channels ADD full_channel_id BYTEA DEFAULT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD funding_psbt BLOB DEFAULT NULL;",
         .query = "ALTER TABLE channels ADD funding_psbt BYTEA DEFAULT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD closer INTEGER DEFAULT 2;",
         .query = "ALTER TABLE channels ADD closer INTEGER DEFAULT 2;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD state_change_reason INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD state_change_reason INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE channel_state_changes (  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE,  timestamp BIGINT,  old_state INTEGER,  new_state INTEGER,  cause INTEGER,  message TEXT);",
         .query = "CREATE TABLE channel_state_changes (  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE,  timestamp BIGINT,  old_state INTEGER,  new_state INTEGER,  cause INTEGER,  message TEXT);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE offers (  offer_id BLOB, bolt12 TEXT, label TEXT, status INTEGER, PRIMARY KEY (offer_id));",
         .query = "CREATE TABLE offers (  offer_id BYTEA, bolt12 TEXT, label TEXT, status INTEGER, PRIMARY KEY (offer_id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE invoices ADD COLUMN local_offer_id BLOB DEFAULT NULL REFERENCES offers(offer_id);",
         .query = "ALTER TABLE invoices ADD COLUMN local_offer_id BYTEA DEFAULT NULL REFERENCES offers(offer_id);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD COLUMN local_offer_id BLOB DEFAULT NULL REFERENCES offers(offer_id);",
         .query = "ALTER TABLE payments ADD COLUMN local_offer_id BYTEA DEFAULT NULL REFERENCES offers(offer_id);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD funding_tx_remote_sigs_received INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD funding_tx_remote_sigs_received INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE INDEX forwarded_payments_out_htlc_id ON forwarded_payments (out_htlc_id);",
         .query = "CREATE INDEX forwarded_payments_out_htlc_id ON forwarded_payments (out_htlc_id);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channel_htlcs SET malformed_onion = 0 WHERE malformed_onion IS NULL",
         .query = "UPDATE channel_htlcs SET malformed_onion = 0 WHERE malformed_onion IS NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE INDEX forwarded_payments_state ON forwarded_payments (state)",
         .query = "CREATE INDEX forwarded_payments_state ON forwarded_payments (state)",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE channel_funding_inflights (  channel_id BIGSERIAL REFERENCES channels(id) ON DELETE CASCADE, funding_tx_id BLOB, funding_tx_outnum INTEGER, funding_feerate INTEGER, funding_satoshi BIGINT, our_funding_satoshi BIGINT, funding_psbt BLOB, last_tx BLOB, last_sig BLOB, funding_tx_remote_sigs_received INTEGER, PRIMARY KEY (channel_id, funding_tx_id));",
         .query = "CREATE TABLE channel_funding_inflights (  channel_id BIGSERIAL REFERENCES channels(id) ON DELETE CASCADE, funding_tx_id BYTEA, funding_tx_outnum INTEGER, funding_feerate INTEGER, funding_satoshi BIGINT, our_funding_satoshi BIGINT, funding_psbt BYTEA, last_tx BYTEA, last_sig BYTEA, funding_tx_remote_sigs_received INTEGER, PRIMARY KEY (channel_id, funding_tx_id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD revocation_basepoint_local BLOB",
         .query = "ALTER TABLE channels ADD revocation_basepoint_local BYTEA",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD payment_basepoint_local BLOB",
         .query = "ALTER TABLE channels ADD payment_basepoint_local BYTEA",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD htlc_basepoint_local BLOB",
         .query = "ALTER TABLE channels ADD htlc_basepoint_local BYTEA",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD delayed_payment_basepoint_local BLOB",
         .query = "ALTER TABLE channels ADD delayed_payment_basepoint_local BYTEA",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD funding_pubkey_local BLOB",
         .query = "ALTER TABLE channels ADD funding_pubkey_local BYTEA",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD shutdown_wrong_txid BLOB DEFAULT NULL",
         .query = "ALTER TABLE channels ADD shutdown_wrong_txid BYTEA DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD shutdown_wrong_outnum INTEGER DEFAULT NULL",
         .query = "ALTER TABLE channels ADD shutdown_wrong_outnum INTEGER DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD local_static_remotekey_start BIGINT DEFAULT 0",
         .query = "ALTER TABLE channels ADD local_static_remotekey_start BIGINT DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD remote_static_remotekey_start BIGINT DEFAULT 0",
         .query = "ALTER TABLE channels ADD remote_static_remotekey_start BIGINT DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET remote_static_remotekey_start = 9223372036854775807, local_static_remotekey_start = 9223372036854775807 WHERE option_static_remotekey = 0",
         .query = "UPDATE channels SET remote_static_remotekey_start = 9223372036854775807, local_static_remotekey_start = 9223372036854775807 WHERE option_static_remotekey = 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_funding_inflights ADD lease_commit_sig BLOB DEFAULT NULL",
         .query = "ALTER TABLE channel_funding_inflights ADD lease_commit_sig BYTEA DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_funding_inflights ADD lease_chan_max_msat BIGINT DEFAULT NULL",
         .query = "ALTER TABLE channel_funding_inflights ADD lease_chan_max_msat BIGINT DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_funding_inflights ADD lease_chan_max_ppt INTEGER DEFAULT NULL",
         .query = "ALTER TABLE channel_funding_inflights ADD lease_chan_max_ppt INTEGER DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_funding_inflights ADD lease_expiry INTEGER DEFAULT 0",
         .query = "ALTER TABLE channel_funding_inflights ADD lease_expiry INTEGER DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_funding_inflights ADD lease_blockheight_start INTEGER DEFAULT 0",
         .query = "ALTER TABLE channel_funding_inflights ADD lease_blockheight_start INTEGER DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD lease_commit_sig BLOB DEFAULT NULL",
         .query = "ALTER TABLE channels ADD lease_commit_sig BYTEA DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD lease_chan_max_msat INTEGER DEFAULT NULL",
         .query = "ALTER TABLE channels ADD lease_chan_max_msat INTEGER DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD lease_chan_max_ppt INTEGER DEFAULT NULL",
         .query = "ALTER TABLE channels ADD lease_chan_max_ppt INTEGER DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD lease_expiry INTEGER DEFAULT 0",
         .query = "ALTER TABLE channels ADD lease_expiry INTEGER DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE channel_blockheights (  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE,  hstate INTEGER,  blockheight INTEGER,  UNIQUE (channel_id, hstate));",
         .query = "CREATE TABLE channel_blockheights (  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE,  hstate INTEGER,  blockheight INTEGER,  UNIQUE (channel_id, hstate));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE outputs ADD csv_lock INTEGER DEFAULT 1;",
         .query = "ALTER TABLE outputs ADD csv_lock INTEGER DEFAULT 1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE datastore (  key BLOB,  data BLOB,  generation BIGINT,  PRIMARY KEY (key));",
         .query = "CREATE TABLE datastore (  key BYTEA,  data BYTEA,  generation BIGINT,  PRIMARY KEY (key));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE INDEX channel_state_changes_channel_id ON channel_state_changes (channel_id);",
         .query = "CREATE INDEX channel_state_changes_channel_id ON channel_state_changes (channel_id);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE vars SET intval = intval + 1 WHERE name = 'data_version' AND intval = ?",
         .query = "UPDATE vars SET intval = intval + 1 WHERE name = 'data_version' AND intval = $1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "SELECT version FROM version LIMIT 1",
         .query = "SELECT version FROM version LIMIT 1",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "UPDATE version SET version=?;",
         .query = "UPDATE version SET version=$1;",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "INSERT INTO db_upgrades VALUES (?, ?);",
         .query = "INSERT INTO db_upgrades VALUES ($1, $2);",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "SELECT intval FROM vars WHERE name = 'data_version'",
         .query = "SELECT intval FROM vars WHERE name = 'data_version'",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "SELECT intval FROM vars WHERE name= ? LIMIT 1",
         .query = "SELECT intval FROM vars WHERE name= $1 LIMIT 1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "UPDATE vars SET intval=? WHERE name=?;",
         .query = "UPDATE vars SET intval=$1 WHERE name=$2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "INSERT INTO vars (name, intval) VALUES (?, ?);",
         .query = "INSERT INTO vars (name, intval) VALUES ($1, $2);",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET feerate_base = ?, feerate_ppm = ?;",
         .query = "UPDATE channels SET feerate_base = $1, feerate_ppm = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET our_funding_satoshi = funding_satoshi WHERE funder = 0;",
         .query = "UPDATE channels SET our_funding_satoshi = funding_satoshi WHERE funder = 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT type, keyindex, prev_out_tx, prev_out_index, channel_id, peer_id, commitment_point FROM outputs WHERE scriptpubkey IS NULL;",
         .query = "SELECT type, keyindex, prev_out_tx, prev_out_index, channel_id, peer_id, commitment_point FROM outputs WHERE scriptpubkey IS NULL;",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "UPDATE outputs SET scriptpubkey = ? WHERE prev_out_tx = ?    AND prev_out_index = ?",
         .query = "UPDATE outputs SET scriptpubkey = $1 WHERE prev_out_tx = $2    AND prev_out_index = $3",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "SELECT id, funding_tx_id, funding_tx_outnum FROM channels;",
         .query = "SELECT id, funding_tx_id, funding_tx_outnum FROM channels;",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "UPDATE channels SET full_channel_id = ? WHERE id = ?;",
         .query = "UPDATE channels SET full_channel_id = $1 WHERE id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "SELECT  channels.id, peers.node_id FROM  channels JOIN  peers ON (peers.id = channels.peer_id)",
         .query = "SELECT  channels.id, peers.node_id FROM  channels JOIN  peers ON (peers.id = channels.peer_id)",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "UPDATE channels SET  revocation_basepoint_local = ?, payment_basepoint_local = ?, htlc_basepoint_local = ?, delayed_payment_basepoint_local = ?, funding_pubkey_local = ? WHERE id = ?;",
         .query = "UPDATE channels SET  revocation_basepoint_local = $1, payment_basepoint_local = $2, htlc_basepoint_local = $3, delayed_payment_basepoint_local = $4, funding_pubkey_local = $5 WHERE id = $6;",
         .placeholders = 6,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_blockheights  (channel_id, hstate, blockheight) SELECT id, 4, 0 FROM channels WHERE funder = 0;",
         .query = "INSERT INTO channel_blockheights  (channel_id, hstate, blockheight) SELECT id, 4, 0 FROM channels WHERE funder = 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_blockheights  (channel_id, hstate, blockheight) SELECT id, 14, 0 FROM channels WHERE funder = 1;",
         .query = "INSERT INTO channel_blockheights  (channel_id, hstate, blockheight) SELECT id, 14, 0 FROM channels WHERE funder = 1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT   c.id, p.node_id, c.fundingkey_remote, inflight.last_tx, inflight.last_sig, inflight.funding_satoshi, inflight.funding_tx_id FROM channels c  LEFT OUTER JOIN peers p   ON p.id = c.peer_id  LEFT OUTER JOIN   channel_funding_inflights inflight   ON c.id = inflight.channel_id WHERE inflight.last_tx IS NOT NULL;",
         .query = "SELECT   c.id, p.node_id, c.fundingkey_remote, inflight.last_tx, inflight.last_sig, inflight.funding_satoshi, inflight.funding_tx_id FROM channels c  LEFT OUTER JOIN peers p   ON p.id = c.peer_id  LEFT OUTER JOIN   channel_funding_inflights inflight   ON c.id = inflight.channel_id WHERE inflight.last_tx IS NOT NULL;",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "UPDATE channel_funding_inflights SET last_tx = ? WHERE channel_id = ?   AND funding_tx_id = ?;",
         .query = "UPDATE channel_funding_inflights SET last_tx = $1 WHERE channel_id = $2   AND funding_tx_id = $3;",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "SELECT   c.id, p.node_id, c.last_tx, c.funding_satoshi, c.fundingkey_remote, c.last_sig FROM channels c  LEFT OUTER JOIN peers p  ON p.id = c.peer_id;",
         .query = "SELECT   c.id, p.node_id, c.last_tx, c.funding_satoshi, c.fundingkey_remote, c.last_sig FROM channels c  LEFT OUTER JOIN peers p  ON p.id = c.peer_id;",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "UPDATE channels SET last_tx = ? WHERE id = ?;",
         .query = "UPDATE channels SET last_tx = $1 WHERE id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "UPDATE invoices   SET state = ? WHERE state = ?   AND expiry_time <= ?;",
         .query = "UPDATE invoices   SET state = $1 WHERE state = $2   AND expiry_time <= $3;",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "SELECT id  FROM invoices WHERE state = ?   AND expiry_time <= ?",
         .query = "SELECT id  FROM invoices WHERE state = $1   AND expiry_time <= $2",
         .placeholders = 2,
         .readonly = true,
    },
    {
         .name = "SELECT MIN(expiry_time)  FROM invoices WHERE state = ?;",
         .query = "SELECT MIN(expiry_time)  FROM invoices WHERE state = $1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "INSERT INTO invoices            ( payment_hash, payment_key, state            , msatoshi, label, expiry_time            , pay_index, msatoshi_received            , paid_timestamp, bolt11, description, features, local_offer_id)     VALUES ( ?, ?, ?            , ?, ?, ?            , NULL, NULL            , NULL, ?, ?, ?, ?);",
         .query = "INSERT INTO invoices            ( payment_hash, payment_key, state            , msatoshi, label, expiry_time            , pay_index, msatoshi_received            , paid_timestamp, bolt11, description, features, local_offer_id)     VALUES ( $1, $2, $3            , $4, $5, $6            , NULL, NULL            , NULL, $7, $8, $9, $10);",
         .placeholders = 10,
         .readonly = false,
    },
    {
         .name = "SELECT id  FROM invoices WHERE label = ?;",
         .query = "SELECT id  FROM invoices WHERE label = $1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT id  FROM invoices WHERE payment_hash = ?;",
         .query = "SELECT id  FROM invoices WHERE payment_hash = $1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT id  FROM invoices WHERE payment_hash = ?   AND state = ?;",
         .query = "SELECT id  FROM invoices WHERE payment_hash = $1   AND state = $2;",
         .placeholders = 2,
         .readonly = true,
    },
    {
         .name = "DELETE FROM invoices WHERE id=?;",
         .query = "DELETE FROM invoices WHERE id=$1;",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "DELETE FROM invoices WHERE state = ?   AND expiry_time <= ?;",
         .query = "DELETE FROM invoices WHERE state = $1   AND expiry_time <= $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "SELECT  state, payment_key, payment_hash, label, msatoshi, expiry_time, pay_index, msatoshi_received, paid_timestamp, bolt11, description, features, local_offer_id FROM invoices ORDER BY id;",
         .query = "SELECT  state, payment_key, payment_hash, label, msatoshi, expiry_time, pay_index, msatoshi_received, paid_timestamp, bolt11, description, features, local_offer_id FROM invoices ORDER BY id;",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "SELECT state FROM invoices WHERE id = ?;",
         .query = "SELECT state FROM invoices WHERE id = $1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT local_offer_id FROM invoices WHERE id = ?;",
         .query = "SELECT local_offer_id FROM invoices WHERE id = $1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "UPDATE invoices   SET state=?     , pay_index=?     , msatoshi_received=?     , paid_timestamp=? WHERE id=?;",
         .query = "UPDATE invoices   SET state=$1     , pay_index=$2     , msatoshi_received=$3     , paid_timestamp=$4 WHERE id=$5;",
         .placeholders = 5,
         .readonly = false,
    },
    {
         .name = "SELECT id  FROM invoices WHERE pay_index IS NOT NULL   AND pay_index > ? ORDER BY pay_index ASC LIMIT 1;",
         .query = "SELECT id  FROM invoices WHERE pay_index IS NOT NULL   AND pay_index > $1 ORDER BY pay_index ASC LIMIT 1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT  state, payment_key, payment_hash, label, msatoshi, expiry_time, pay_index, msatoshi_received, paid_timestamp, bolt11, description, features, local_offer_id FROM invoices WHERE id = ?;",
         .query = "SELECT  state, payment_key, payment_hash, label, msatoshi, expiry_time, pay_index, msatoshi_received, paid_timestamp, bolt11, description, features, local_offer_id FROM invoices WHERE id = $1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT txid, outnum FROM utxoset WHERE spendheight is NULL",
         .query = "SELECT txid, outnum FROM utxoset WHERE spendheight is NULL",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "SELECT * from outputs WHERE prev_out_tx=? AND prev_out_index=?",
         .query = "SELECT * from outputs WHERE prev_out_tx=$1 AND prev_out_index=$2",
         .placeholders = 2,
         .readonly = true,
    },
    {
         .name = "INSERT INTO outputs (  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO outputs (  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13);",
         .placeholders = 13,
         .readonly = false,
    },
    {
         .name = "UPDATE outputs SET status=? WHERE status=? AND prev_out_tx=? AND prev_out_index=?",
         .query = "UPDATE outputs SET status=$1 WHERE status=$2 AND prev_out_tx=$3 AND prev_out_index=$4",
         .placeholders = 4,
         .readonly = false,
    },
    {
         .name = "UPDATE outputs SET status=? WHERE prev_out_tx=? AND prev_out_index=?",
         .query = "UPDATE outputs SET status=$1 WHERE prev_out_tx=$2 AND prev_out_index=$3",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey , reserved_til , csv_lock FROM outputs",
         .query = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey , reserved_til , csv_lock FROM outputs",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey , reserved_til , csv_lock FROM outputs WHERE status= ? ",
         .query = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey , reserved_til , csv_lock FROM outputs WHERE status= $1 ",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey, reserved_til, csv_lock FROM outputs WHERE channel_id IS NOT NULL AND confirmation_height IS NULL",
         .query = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey, reserved_til, csv_lock FROM outputs WHERE channel_id IS NOT NULL AND confirmation_height IS NULL",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey, reserved_til, csv_lock FROM outputs WHERE prev_out_tx = ? AND prev_out_index = ?",
         .query = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey, reserved_til, csv_lock FROM outputs WHERE prev_out_tx = $1 AND prev_out_index = $2",
         .placeholders = 2,
         .readonly = true,
    },
    {
         .name = "UPDATE outputs SET status=?, reserved_til=? WHERE prev_out_tx=? AND prev_out_index=?",
         .query = "UPDATE outputs SET status=$1, reserved_til=$2 WHERE prev_out_tx=$3 AND prev_out_index=$4",
         .placeholders = 4,
         .readonly = false,
    },
    {
         .name = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey , reserved_til, csv_lock FROM outputs WHERE status = ? OR (status = ? AND reserved_til <= ?)ORDER BY RANDOM();",
         .query = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey , reserved_til, csv_lock FROM outputs WHERE status = $1 OR (status = $2 AND reserved_til <= $3)ORDER BY RANDOM();",
         .placeholders = 3,
         .readonly = true,
    },
    {
         .name = "INSERT INTO outputs (  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey, csv_lock) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO outputs (  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey, csv_lock) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14);",
         .placeholders = 14,
         .readonly = false,
    },
    {
         .name = "INSERT INTO shachains (min_index, num_valid) VALUES (?, 0);",
         .query = "INSERT INTO shachains (min_index, num_valid) VALUES ($1, 0);",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "UPDATE shachains SET num_valid=?, min_index=? WHERE id=?",
         .query = "UPDATE shachains SET num_valid=$1, min_index=$2 WHERE id=$3",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "UPDATE shachain_known SET idx=?, hash=? WHERE shachain_id=? AND pos=?",
         .query = "UPDATE shachain_known SET idx=$1, hash=$2 WHERE shachain_id=$3 AND pos=$4",
         .placeholders = 4,
         .readonly = false,
    },
    {
         .name = "INSERT INTO shachain_known (shachain_id, pos, idx, hash) VALUES (?, ?, ?, ?);",
         .query = "INSERT INTO shachain_known (shachain_id, pos, idx, hash) VALUES ($1, $2, $3, $4);",
         .placeholders = 4,
         .readonly = false,
    },
    {
         .name = "SELECT min_index, num_valid FROM shachains WHERE id=?",
         .query = "SELECT min_index, num_valid FROM shachains WHERE id=$1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT idx, hash, pos FROM shachain_known WHERE shachain_id=?",
         .query = "SELECT idx, hash, pos FROM shachain_known WHERE shachain_id=$1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT id, node_id, address FROM peers WHERE id=?;",
         .query = "SELECT id, node_id, address FROM peers WHERE id=$1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT signature FROM htlc_sigs WHERE channelid = ?",
         .query = "SELECT signature FROM htlc_sigs WHERE channelid = $1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT remote_ann_node_sig, remote_ann_bitcoin_sig FROM channels WHERE id = ?",
         .query = "SELECT remote_ann_node_sig, remote_ann_bitcoin_sig FROM channels WHERE id = $1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT hstate, feerate_per_kw FROM channel_feerates WHERE channel_id = ?",
         .query = "SELECT hstate, feerate_per_kw FROM channel_feerates WHERE channel_id = $1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT hstate, blockheight FROM channel_blockheights WHERE channel_id = ?",
         .query = "SELECT hstate, blockheight FROM channel_blockheights WHERE channel_id = $1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "INSERT INTO channel_funding_inflights (  channel_id, funding_tx_id, funding_tx_outnum, funding_feerate, funding_satoshi, our_funding_satoshi, funding_psbt, last_tx, last_sig, lease_commit_sig, lease_chan_max_msat, lease_chan_max_ppt, lease_expiry, lease_blockheight_start) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO channel_funding_inflights (  channel_id, funding_tx_id, funding_tx_outnum, funding_feerate, funding_satoshi, our_funding_satoshi, funding_psbt, last_tx, last_sig, lease_commit_sig, lease_chan_max_msat, lease_chan_max_ppt, lease_expiry, lease_blockheight_start) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14);",
         .placeholders = 14,
         .readonly = false,
    },
    {
         .name = "UPDATE channel_funding_inflights SET  funding_psbt=?, funding_tx_remote_sigs_received=? WHERE  channel_id=? AND funding_tx_id=? AND funding_tx_outnum=?",
         .query = "UPDATE channel_funding_inflights SET  funding_psbt=$1, funding_tx_remote_sigs_received=$2 WHERE  channel_id=$3 AND funding_tx_id=$4 AND funding_tx_outnum=$5",
         .placeholders = 5,
         .readonly = false,
    },
    {
         .name = "DELETE FROM channel_funding_inflights WHERE channel_id = ?",
         .query = "DELETE FROM channel_funding_inflights WHERE channel_id = $1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "SELECT  funding_tx_id, funding_tx_outnum, funding_feerate, funding_satoshi, our_funding_satoshi, funding_psbt, last_tx, last_sig, funding_tx_remote_sigs_received, lease_expiry, lease_commit_sig, lease_chan_max_msat, lease_chan_max_ppt, lease_blockheight_start FROM channel_funding_inflights WHERE channel_id = ? ORDER BY funding_feerate",
         .query = "SELECT  funding_tx_id, funding_tx_outnum, funding_feerate, funding_satoshi, our_funding_satoshi, funding_psbt, last_tx, last_sig, funding_tx_remote_sigs_received, lease_expiry, lease_commit_sig, lease_chan_max_msat, lease_chan_max_ppt, lease_blockheight_start FROM channel_funding_inflights WHERE channel_id = $1 ORDER BY funding_feerate",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT id FROM channels ORDER BY id DESC LIMIT 1;",
         .query = "SELECT id FROM channels ORDER BY id DESC LIMIT 1;",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "SELECT  id, peer_id, short_channel_id, full_channel_id, channel_config_local, channel_config_remote, state, funder, channel_flags, minimum_depth, next_index_local, next_index_remote, next_htlc_id, funding_tx_id, funding_tx_outnum, funding_satoshi, our_funding_satoshi, funding_locked_remote, push_msatoshi, msatoshi_local, fundingkey_remote, revocation_basepoint_remote, payment_basepoint_remote, htlc_basepoint_remote, delayed_payment_basepoint_remote, per_commit_remote, old_per_commit_remote, local_feerate_per_kw, remote_feerate_per_kw, shachain_remote_id, shutdown_scriptpubkey_remote, shutdown_keyidx_local, last_sent_commit_state, last_sent_commit_id, last_tx, last_sig, last_was_revoke, first_blocknum, min_possible_feerate, max_possible_feerate, msatoshi_to_us_min, msatoshi_to_us_max, future_per_commitment_point, last_sent_commit, feerate_base, feerate_ppm, remote_upfront_shutdown_script, local_static_remotekey_start, remote_static_remotekey_start, option_anchor_outputs, shutdown_scriptpubkey_local, closer, state_change_reason, revocation_basepoint_local, payment_basepoint_local, htlc_basepoint_local, delayed_payment_basepoint_local, funding_pubkey_local, shutdown_wrong_txid, shutdown_wrong_outnum, lease_expiry, lease_commit_sig, lease_chan_max_msat, lease_chan_max_ppt FROM channels WHERE state != ?;",
         .query = "SELECT  id, peer_id, short_channel_id, full_channel_id, channel_config_local, channel_config_remote, state, funder, channel_flags, minimum_depth, next_index_local, next_index_remote, next_htlc_id, funding_tx_id, funding_tx_outnum, funding_satoshi, our_funding_satoshi, funding_locked_remote, push_msatoshi, msatoshi_local, fundingkey_remote, revocation_basepoint_remote, payment_basepoint_remote, htlc_basepoint_remote, delayed_payment_basepoint_remote, per_commit_remote, old_per_commit_remote, local_feerate_per_kw, remote_feerate_per_kw, shachain_remote_id, shutdown_scriptpubkey_remote, shutdown_keyidx_local, last_sent_commit_state, last_sent_commit_id, last_tx, last_sig, last_was_revoke, first_blocknum, min_possible_feerate, max_possible_feerate, msatoshi_to_us_min, msatoshi_to_us_max, future_per_commitment_point, last_sent_commit, feerate_base, feerate_ppm, remote_upfront_shutdown_script, local_static_remotekey_start, remote_static_remotekey_start, option_anchor_outputs, shutdown_scriptpubkey_local, closer, state_change_reason, revocation_basepoint_local, payment_basepoint_local, htlc_basepoint_local, delayed_payment_basepoint_local, funding_pubkey_local, shutdown_wrong_txid, shutdown_wrong_outnum, lease_expiry, lease_commit_sig, lease_chan_max_msat, lease_chan_max_ppt FROM channels WHERE state != $1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "UPDATE channels   SET in_payments_offered = COALESCE(in_payments_offered, 0) + 1     , in_msatoshi_offered = COALESCE(in_msatoshi_offered, 0) + ? WHERE id = ?;",
         .query = "UPDATE channels   SET in_payments_offered = COALESCE(in_payments_offered, 0) + 1     , in_msatoshi_offered = COALESCE(in_msatoshi_offered, 0) + $1 WHERE id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "UPDATE channels   SET in_payments_fulfilled = COALESCE(in_payments_fulfilled, 0) + 1     , in_msatoshi_fulfilled = COALESCE(in_msatoshi_fulfilled, 0) + ? WHERE id = ?;",
         .query = "UPDATE channels   SET in_payments_fulfilled = COALESCE(in_payments_fulfilled, 0) + 1     , in_msatoshi_fulfilled = COALESCE(in_msatoshi_fulfilled, 0) + $1 WHERE id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "UPDATE channels   SET out_payments_offered = COALESCE(out_payments_offered, 0) + 1     , out_msatoshi_offered = COALESCE(out_msatoshi_offered, 0) + ? WHERE id = ?;",
         .query = "UPDATE channels   SET out_payments_offered = COALESCE(out_payments_offered, 0) + 1     , out_msatoshi_offered = COALESCE(out_msatoshi_offered, 0) + $1 WHERE id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "UPDATE channels   SET out_payments_fulfilled = COALESCE(out_payments_fulfilled, 0) + 1     , out_msatoshi_fulfilled = COALESCE(out_msatoshi_fulfilled, 0) + ? WHERE id = ?;",
         .query = "UPDATE channels   SET out_payments_fulfilled = COALESCE(out_payments_fulfilled, 0) + 1     , out_msatoshi_fulfilled = COALESCE(out_msatoshi_fulfilled, 0) + $1 WHERE id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "SELECT   in_payments_offered,  in_payments_fulfilled,  in_msatoshi_offered,  in_msatoshi_fulfilled, out_payments_offered, out_payments_fulfilled, out_msatoshi_offered, out_msatoshi_fulfilled  FROM channels WHERE id = ?",
         .query = "SELECT   in_payments_offered,  in_payments_fulfilled,  in_msatoshi_offered,  in_msatoshi_fulfilled, out_payments_offered, out_payments_fulfilled, out_msatoshi_offered, out_msatoshi_fulfilled  FROM channels WHERE id = $1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT MIN(height), MAX(height) FROM blocks;",
         .query = "SELECT MIN(height), MAX(height) FROM blocks;",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "INSERT INTO channel_configs DEFAULT VALUES;",
         .query = "INSERT INTO channel_configs DEFAULT VALUES;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channel_configs SET  dust_limit_satoshis=?,  max_htlc_value_in_flight_msat=?,  channel_reserve_satoshis=?,  htlc_minimum_msat=?,  to_self_delay=?,  max_accepted_htlcs=? WHERE id=?;",
         .query = "UPDATE channel_configs SET  dust_limit_satoshis=$1,  max_htlc_value_in_flight_msat=$2,  channel_reserve_satoshis=$3,  htlc_minimum_msat=$4,  to_self_delay=$5,  max_accepted_htlcs=$6 WHERE id=$7;",
         .placeholders = 7,
         .readonly = false,
    },
    {
         .name = "SELECT id, dust_limit_satoshis, max_htlc_value_in_flight_msat, channel_reserve_satoshis, htlc_minimum_msat, to_self_delay, max_accepted_htlcs FROM channel_configs WHERE id= ? ;",
         .query = "SELECT id, dust_limit_satoshis, max_htlc_value_in_flight_msat, channel_reserve_satoshis, htlc_minimum_msat, to_self_delay, max_accepted_htlcs FROM channel_configs WHERE id= $1 ;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "UPDATE channels SET  remote_ann_node_sig=?,  remote_ann_bitcoin_sig=? WHERE id=?",
         .query = "UPDATE channels SET  remote_ann_node_sig=$1,  remote_ann_bitcoin_sig=$2 WHERE id=$3",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET  shachain_remote_id=?,  short_channel_id=?,  full_channel_id=?,  state=?,  funder=?,  channel_flags=?,  minimum_depth=?,  next_index_local=?,  next_index_remote=?,  next_htlc_id=?,  funding_tx_id=?,  funding_tx_outnum=?,  funding_satoshi=?,  our_funding_satoshi=?,  funding_locked_remote=?,  push_msatoshi=?,  msatoshi_local=?,  shutdown_scriptpubkey_remote=?,  shutdown_keyidx_local=?,  channel_config_local=?,  last_tx=?, last_sig=?,  last_was_revoke=?,  min_possible_feerate=?,  max_possible_feerate=?,  msatoshi_to_us_min=?,  msatoshi_to_us_max=?,  feerate_base=?,  feerate_ppm=?,  remote_upfront_shutdown_script=?,  local_static_remotekey_start=?,  remote_static_remotekey_start=?,  option_anchor_outputs=?,  shutdown_scriptpubkey_local=?,  closer=?,  state_change_reason=?,  shutdown_wrong_txid=?,  shutdown_wrong_outnum=?,  lease_expiry=?,  lease_commit_sig=?,  lease_chan_max_msat=?,  lease_chan_max_ppt=? WHERE id=?",
         .query = "UPDATE channels SET  shachain_remote_id=$1,  short_channel_id=$2,  full_channel_id=$3,  state=$4,  funder=$5,  channel_flags=$6,  minimum_depth=$7,  next_index_local=$8,  next_index_remote=$9,  next_htlc_id=$10,  funding_tx_id=$11,  funding_tx_outnum=$12,  funding_satoshi=$13,  our_funding_satoshi=$14,  funding_locked_remote=$15,  push_msatoshi=$16,  msatoshi_local=$17,  shutdown_scriptpubkey_remote=$18,  shutdown_keyidx_local=$19,  channel_config_local=$20,  last_tx=$21, last_sig=$22,  last_was_revoke=$23,  min_possible_feerate=$24,  max_possible_feerate=$25,  msatoshi_to_us_min=$26,  msatoshi_to_us_max=$27,  feerate_base=$28,  feerate_ppm=$29,  remote_upfront_shutdown_script=$30,  local_static_remotekey_start=$31,  remote_static_remotekey_start=$32,  option_anchor_outputs=$33,  shutdown_scriptpubkey_local=$34,  closer=$35,  state_change_reason=$36,  shutdown_wrong_txid=$37,  shutdown_wrong_outnum=$38,  lease_expiry=$39,  lease_commit_sig=$40,  lease_chan_max_msat=$41,  lease_chan_max_ppt=$42 WHERE id=$43",
         .placeholders = 43,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET  fundingkey_remote=?,  revocation_basepoint_remote=?,  payment_basepoint_remote=?,  htlc_basepoint_remote=?,  delayed_payment_basepoint_remote=?,  per_commit_remote=?,  old_per_commit_remote=?,  channel_config_remote=?,  future_per_commitment_point=? WHERE id=?",
         .query = "UPDATE channels SET  fundingkey_remote=$1,  revocation_basepoint_remote=$2,  payment_basepoint_remote=$3,  htlc_basepoint_remote=$4,  delayed_payment_basepoint_remote=$5,  per_commit_remote=$6,  old_per_commit_remote=$7,  channel_config_remote=$8,  future_per_commitment_point=$9 WHERE id=$10",
         .placeholders = 10,
         .readonly = false,
    },
    {
         .name = "DELETE FROM channel_feerates WHERE channel_id=?",
         .query = "DELETE FROM channel_feerates WHERE channel_id=$1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_feerates  VALUES(?, ?, ?)",
         .query = "INSERT INTO channel_feerates  VALUES($1, $2, $3)",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "DELETE FROM channel_blockheights WHERE channel_id=?",
         .query = "DELETE FROM channel_blockheights WHERE channel_id=$1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_blockheights  VALUES(?, ?, ?)",
         .query = "INSERT INTO channel_blockheights  VALUES($1, $2, $3)",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET  last_sent_commit=? WHERE id=?",
         .query = "UPDATE channels SET  last_sent_commit=$1 WHERE id=$2",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_state_changes (  channel_id, timestamp, old_state, new_state, cause, message) VALUES (?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO channel_state_changes (  channel_id, timestamp, old_state, new_state, cause, message) VALUES ($1, $2, $3, $4, $5, $6);",
         .placeholders = 6,
         .readonly = false,
    },
    {
         .name = "SELECT timestamp, old_state, new_state, cause, message FROM channel_state_changes WHERE channel_id = ? ORDER BY timestamp ASC;",
         .query = "SELECT timestamp, old_state, new_state, cause, message FROM channel_state_changes WHERE channel_id = $1 ORDER BY timestamp ASC;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT id FROM peers WHERE node_id = ?",
         .query = "SELECT id FROM peers WHERE node_id = $1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "UPDATE peers SET address = ? WHERE id = ?",
         .query = "UPDATE peers SET address = $1 WHERE id = $2",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "INSERT INTO peers (node_id, address) VALUES (?, ?);",
         .query = "INSERT INTO peers (node_id, address) VALUES ($1, $2);",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channels (  peer_id, first_blocknum, id, revocation_basepoint_local, payment_basepoint_local, htlc_basepoint_local, delayed_payment_basepoint_local, funding_pubkey_local) VALUES (?, ?, ?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO channels (  peer_id, first_blocknum, id, revocation_basepoint_local, payment_basepoint_local, htlc_basepoint_local, delayed_payment_basepoint_local, funding_pubkey_local) VALUES ($1, $2, $3, $4, $5, $6, $7, $8);",
         .placeholders = 8,
         .readonly = false,
    },
    {
         .name = "DELETE FROM channel_htlcs WHERE channel_id=?",
         .query = "DELETE FROM channel_htlcs WHERE channel_id=$1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "DELETE FROM htlc_sigs WHERE channelid=?",
         .query = "DELETE FROM htlc_sigs WHERE channelid=$1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "DELETE FROM channeltxs WHERE channel_id=?",
         .query = "DELETE FROM channeltxs WHERE channel_id=$1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "DELETE FROM channel_funding_inflights  WHERE channel_id=?",
         .query = "DELETE FROM channel_funding_inflights  WHERE channel_id=$1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "DELETE FROM shachains WHERE id IN (  SELECT shachain_remote_id   FROM channels   WHERE channels.id=?)",
         .query = "DELETE FROM shachains WHERE id IN (  SELECT shachain_remote_id   FROM channels   WHERE channels.id=$1)",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET state=?, peer_id=? WHERE channels.id=?",
         .query = "UPDATE channels SET state=$1, peer_id=$2 WHERE channels.id=$3",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "SELECT * FROM channels WHERE peer_id = ?;",
         .query = "SELECT * FROM channels WHERE peer_id = $1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "DELETE FROM peers WHERE id=?",
         .query = "DELETE FROM peers WHERE id=$1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "UPDATE outputs SET confirmation_height = ? WHERE prev_out_tx = ?",
         .query = "UPDATE outputs SET confirmation_height = $1 WHERE prev_out_tx = $2",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_htlcs ( channel_id, channel_htlc_id,  direction, msatoshi, cltv_expiry, payment_hash,  payment_key, hstate, shared_secret, routing_onion, received_time) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO channel_htlcs ( channel_id, channel_htlc_id,  direction, msatoshi, cltv_expiry, payment_hash,  payment_key, hstate, shared_secret, routing_onion, received_time) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11);",
         .placeholders = 11,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_htlcs ( channel_id, channel_htlc_id, direction, origin_htlc, msatoshi, cltv_expiry, payment_hash, payment_key, hstate, routing_onion, malformed_onion, partid) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, 0, ?);",
         .query = "INSERT INTO channel_htlcs ( channel_id, channel_htlc_id, direction, origin_htlc, msatoshi, cltv_expiry, payment_hash, payment_key, hstate, routing_onion, malformed_onion, partid) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, 0, $11);",
         .placeholders = 11,
         .readonly = false,
    },
    {
         .name = "UPDATE channel_htlcs SET hstate=?, payment_key=?, malformed_onion=?, failuremsg=?, localfailmsg=?, we_filled=? WHERE id=?",
         .query = "UPDATE channel_htlcs SET hstate=$1, payment_key=$2, malformed_onion=$3, failuremsg=$4, localfailmsg=$5, we_filled=$6 WHERE id=$7",
         .placeholders = 7,
         .readonly = false,
    },
    {
         .name = "SELECT  id, channel_htlc_id, msatoshi, cltv_expiry, hstate, payment_hash, payment_key, routing_onion, failuremsg, malformed_onion, origin_htlc, shared_secret, received_time, we_filled FROM channel_htlcs WHERE direction= ? AND channel_id= ? AND hstate != ?",
         .query = "SELECT  id, channel_htlc_id, msatoshi, cltv_expiry, hstate, payment_hash, payment_key, routing_onion, failuremsg, malformed_onion, origin_htlc, shared_secret, received_time, we_filled FROM channel_htlcs WHERE direction= $1 AND channel_id= $2 AND hstate != $3",
         .placeholders = 3,
         .readonly = true,
    },
    {
         .name = "SELECT  id, channel_htlc_id, msatoshi, cltv_expiry, hstate, payment_hash, payment_key, routing_onion, failuremsg, malformed_onion, origin_htlc, shared_secret, received_time, partid, localfailmsg FROM channel_htlcs WHERE direction = ? AND channel_id = ? AND hstate != ?",
         .query = "SELECT  id, channel_htlc_id, msatoshi, cltv_expiry, hstate, payment_hash, payment_key, routing_onion, failuremsg, malformed_onion, origin_htlc, shared_secret, received_time, partid, localfailmsg FROM channel_htlcs WHERE direction = $1 AND channel_id = $2 AND hstate != $3",
         .placeholders = 3,
         .readonly = true,
    },
    {
         .name = "SELECT channel_id, direction, cltv_expiry, channel_htlc_id, payment_hash FROM channel_htlcs WHERE channel_id = ?;",
         .query = "SELECT channel_id, direction, cltv_expiry, channel_htlc_id, payment_hash FROM channel_htlcs WHERE channel_id = $1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "DELETE FROM channel_htlcs WHERE direction = ? AND origin_htlc = ? AND payment_hash = ? AND partid = ?;",
         .query = "DELETE FROM channel_htlcs WHERE direction = $1 AND origin_htlc = $2 AND payment_hash = $3 AND partid = $4;",
         .placeholders = 4,
         .readonly = false,
    },
    {
         .name = "SELECT status FROM payments WHERE payment_hash=? AND partid = ?;",
         .query = "SELECT status FROM payments WHERE payment_hash=$1 AND partid = $2;",
         .placeholders = 2,
         .readonly = true,
    },
    {
         .name = "INSERT INTO payments (  status,  payment_hash,  destination,  msatoshi,  timestamp,  path_secrets,  route_nodes,  route_channels,  msatoshi_sent,  description,  bolt11,  total_msat,  partid,  local_offer_id) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO payments (  status,  payment_hash,  destination,  msatoshi,  timestamp,  path_secrets,  route_nodes,  route_channels,  msatoshi_sent,  description,  bolt11,  total_msat,  partid,  local_offer_id) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14);",
         .placeholders = 14,
         .readonly = false,
    },
    {
         .name = "DELETE FROM payments WHERE payment_hash = ? AND partid = ?",
         .query = "DELETE FROM payments WHERE payment_hash = $1 AND partid = $2",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "DELETE FROM payments WHERE payment_hash = ?",
         .query = "DELETE FROM payments WHERE payment_hash = $1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "SELECT  id, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, failonionreply, total_msat, partid, local_offer_id FROM payments WHERE payment_hash = ? AND partid = ?",
         .query = "SELECT  id, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, failonionreply, total_msat, partid, local_offer_id FROM payments WHERE payment_hash = $1 AND partid = $2",
         .placeholders = 2,
         .readonly = true,
    },
    {
         .name = "UPDATE payments SET status=? WHERE payment_hash=? AND partid=?",
         .query = "UPDATE payments SET status=$1 WHERE payment_hash=$2 AND partid=$3",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "UPDATE payments SET payment_preimage=? WHERE payment_hash=? AND partid=?",
         .query = "UPDATE payments SET payment_preimage=$1 WHERE payment_hash=$2 AND partid=$3",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "UPDATE payments   SET path_secrets = NULL     , route_nodes = NULL     , route_channels = NULL WHERE payment_hash = ? AND partid = ?;",
         .query = "UPDATE payments   SET path_secrets = NULL     , route_nodes = NULL     , route_channels = NULL WHERE payment_hash = $1 AND partid = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "SELECT failonionreply, faildestperm, failindex, failcode, failnode, failchannel, failupdate, faildetail, faildirection  FROM payments WHERE payment_hash=? AND partid=?;",
         .query = "SELECT failonionreply, faildestperm, failindex, failcode, failnode, failchannel, failupdate, faildetail, faildirection  FROM payments WHERE payment_hash=$1 AND partid=$2;",
         .placeholders = 2,
         .readonly = true,
    },
    {
         .name = "UPDATE payments   SET failonionreply=?     , faildestperm=?     , failindex=?     , failcode=?     , failnode=?     , failchannel=?     , failupdate=?     , faildetail=?     , faildirection=? WHERE payment_hash=? AND partid=?;",
         .query = "UPDATE payments   SET failonionreply=$1     , faildestperm=$2     , failindex=$3     , failcode=$4     , failnode=$5     , failchannel=$6     , failupdate=$7     , faildetail=$8     , faildirection=$9 WHERE payment_hash=$10 AND partid=$11;",
         .placeholders = 11,
         .readonly = false,
    },
    {
         .name = "SELECT  id, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, failonionreply, total_msat, partid, local_offer_id FROM payments WHERE payment_hash = ? AND status = ? ORDER BY id;",
         .query = "SELECT  id, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, failonionreply, total_msat, partid, local_offer_id FROM payments WHERE payment_hash = $1 AND status = $2 ORDER BY id;",
         .placeholders = 2,
         .readonly = true,
    },
    {
         .name = "SELECT  id, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, failonionreply, total_msat, partid, local_offer_id FROM payments WHERE payment_hash = ? ORDER BY id;",
         .query = "SELECT  id, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, failonionreply, total_msat, partid, local_offer_id FROM payments WHERE payment_hash = $1 ORDER BY id;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT  id, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, failonionreply, total_msat, partid, local_offer_id FROM payments WHERE status = ? ORDER BY id;",
         .query = "SELECT  id, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, failonionreply, total_msat, partid, local_offer_id FROM payments WHERE status = $1 ORDER BY id;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT  id, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, failonionreply, total_msat, partid, local_offer_id FROM payments ORDER BY id;",
         .query = "SELECT  id, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, failonionreply, total_msat, partid, local_offer_id FROM payments ORDER BY id;",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "SELECT  id, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, failonionreply, total_msat, partid, local_offer_id FROM payments WHERE local_offer_id = ?;",
         .query = "SELECT  id, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, failonionreply, total_msat, partid, local_offer_id FROM payments WHERE local_offer_id = $1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "DELETE FROM htlc_sigs WHERE channelid = ?",
         .query = "DELETE FROM htlc_sigs WHERE channelid = $1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "INSERT INTO htlc_sigs (channelid, signature) VALUES (?, ?)",
         .query = "INSERT INTO htlc_sigs (channelid, signature) VALUES ($1, $2)",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "SELECT blobval FROM vars WHERE name='genesis_hash'",
         .query = "SELECT blobval FROM vars WHERE name='genesis_hash'",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "INSERT INTO vars (name, blobval) VALUES ('genesis_hash', ?);",
         .query = "INSERT INTO vars (name, blobval) VALUES ('genesis_hash', $1);",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "SELECT txid, outnum FROM utxoset WHERE spendheight < ?",
         .query = "SELECT txid, outnum FROM utxoset WHERE spendheight < $1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "DELETE FROM utxoset WHERE spendheight < ?",
         .query = "DELETE FROM utxoset WHERE spendheight < $1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "INSERT INTO blocks (height, hash, prev_hash) VALUES (?, ?, ?);",
         .query = "INSERT INTO blocks (height, hash, prev_hash) VALUES ($1, $2, $3);",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "DELETE FROM blocks WHERE hash = ?",
         .query = "DELETE FROM blocks WHERE hash = $1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "SELECT * FROM blocks WHERE height >= ?;",
         .query = "SELECT * FROM blocks WHERE height >= $1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "DELETE FROM blocks WHERE height > ?",
         .query = "DELETE FROM blocks WHERE height > $1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "UPDATE outputs SET spend_height = ?,  status = ? WHERE prev_out_tx = ? AND prev_out_index = ?",
         .query = "UPDATE outputs SET spend_height = $1,  status = $2 WHERE prev_out_tx = $3 AND prev_out_index = $4",
         .placeholders = 4,
         .readonly = false,
    },
    {
         .name = "UPDATE utxoset SET spendheight = ? WHERE txid = ? AND outnum = ?",
         .query = "UPDATE utxoset SET spendheight = $1 WHERE txid = $2 AND outnum = $3",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "INSERT INTO utxoset ( txid, outnum, blockheight, spendheight, txindex, scriptpubkey, satoshis) VALUES(?, ?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO utxoset ( txid, outnum, blockheight, spendheight, txindex, scriptpubkey, satoshis) VALUES($1, $2, $3, $4, $5, $6, $7);",
         .placeholders = 7,
         .readonly = false,
    },
    {
         .name = "SELECT height FROM blocks WHERE height = ?",
         .query = "SELECT height FROM blocks WHERE height = $1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT txid, spendheight, scriptpubkey, satoshis FROM utxoset WHERE blockheight = ? AND txindex = ? AND outnum = ? AND spendheight IS NULL",
         .query = "SELECT txid, spendheight, scriptpubkey, satoshis FROM utxoset WHERE blockheight = $1 AND txindex = $2 AND outnum = $3 AND spendheight IS NULL",
         .placeholders = 3,
         .readonly = true,
    },
    {
         .name = "SELECT blockheight, txindex, outnum FROM utxoset WHERE spendheight = ?",
         .query = "SELECT blockheight, txindex, outnum FROM utxoset WHERE spendheight = $1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT blockheight, txindex, outnum FROM utxoset WHERE blockheight = ?",
         .query = "SELECT blockheight, txindex, outnum FROM utxoset WHERE blockheight = $1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT blockheight FROM transactions WHERE id=?",
         .query = "SELECT blockheight FROM transactions WHERE id=$1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "INSERT INTO transactions (  id, blockheight, txindex, rawtx) VALUES (?, ?, ?, ?);",
         .query = "INSERT INTO transactions (  id, blockheight, txindex, rawtx) VALUES ($1, $2, $3, $4);",
         .placeholders = 4,
         .readonly = false,
    },
    {
         .name = "UPDATE transactions SET blockheight = ?, txindex = ? WHERE id = ?",
         .query = "UPDATE transactions SET blockheight = $1, txindex = $2 WHERE id = $3",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "INSERT INTO transaction_annotations (txid, idx, location, type, channel) VALUES (?, ?, ?, ?, ?) ON CONFLICT(txid,idx) DO NOTHING;",
         .query = "INSERT INTO transaction_annotations (txid, idx, location, type, channel) VALUES ($1, $2, $3, $4, $5) ON CONFLICT(txid,idx) DO NOTHING;",
         .placeholders = 5,
         .readonly = false,
    },
    {
         .name = "SELECT type, channel_id FROM transactions WHERE id=?",
         .query = "SELECT type, channel_id FROM transactions WHERE id=$1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "UPDATE transactions SET type = ?, channel_id = ? WHERE id = ?",
         .query = "UPDATE transactions SET type = $1, channel_id = $2 WHERE id = $3",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "SELECT type FROM transactions WHERE id=?",
         .query = "SELECT type FROM transactions WHERE id=$1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT rawtx FROM transactions WHERE id=?",
         .query = "SELECT rawtx FROM transactions WHERE id=$1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT blockheight, txindex FROM transactions WHERE id=?",
         .query = "SELECT blockheight, txindex FROM transactions WHERE id=$1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT id FROM transactions WHERE blockheight=?",
         .query = "SELECT id FROM transactions WHERE blockheight=$1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "INSERT INTO channeltxs (  channel_id, type, transaction_id, input_num, blockheight) VALUES (?, ?, ?, ?, ?);",
         .query = "INSERT INTO channeltxs (  channel_id, type, transaction_id, input_num, blockheight) VALUES ($1, $2, $3, $4, $5);",
         .placeholders = 5,
         .readonly = false,
    },
    {
         .name = "SELECT DISTINCT(channel_id) FROM channeltxs WHERE type = ?;",
         .query = "SELECT DISTINCT(channel_id) FROM channeltxs WHERE type = $1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT  c.type, c.blockheight, t.rawtx, c.input_num, c.blockheight - t.blockheight + 1 AS depth, t.id as txid FROM channeltxs c JOIN transactions t ON t.id = c.transaction_id WHERE c.channel_id = ? ORDER BY c.id ASC;",
         .query = "SELECT  c.type, c.blockheight, t.rawtx, c.input_num, c.blockheight - t.blockheight + 1 AS depth, t.id as txid FROM channeltxs c JOIN transactions t ON t.id = c.transaction_id WHERE c.channel_id = $1 ORDER BY c.id ASC;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "UPDATE forwarded_payments SET  in_msatoshi=?, out_msatoshi=?, state=?, resolved_time=?, failcode=? WHERE in_htlc_id=?",
         .query = "UPDATE forwarded_payments SET  in_msatoshi=$1, out_msatoshi=$2, state=$3, resolved_time=$4, failcode=$5 WHERE in_htlc_id=$6",
         .placeholders = 6,
         .readonly = false,
    },
    {
         .name = "INSERT INTO forwarded_payments (  in_htlc_id, out_htlc_id, in_channel_scid, out_channel_scid, in_msatoshi, out_msatoshi, state, received_time, resolved_time, failcode) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO forwarded_payments (  in_htlc_id, out_htlc_id, in_channel_scid, out_channel_scid, in_msatoshi, out_msatoshi, state, received_time, resolved_time, failcode) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10);",
         .placeholders = 10,
         .readonly = false,
    },
    {
         .name = "SELECT CAST(COALESCE(SUM(in_msatoshi - out_msatoshi), 0) AS BIGINT)FROM forwarded_payments WHERE state = ?;",
         .query = "SELECT CAST(COALESCE(SUM(in_msatoshi - out_msatoshi), 0) AS BIGINT)FROM forwarded_payments WHERE state = $1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT  f.state, in_msatoshi, out_msatoshi, hin.payment_hash as payment_hash, in_channel_scid, out_channel_scid, f.received_time, f.resolved_time, f.failcode FROM forwarded_payments f LEFT JOIN channel_htlcs hin ON (f.in_htlc_id = hin.id) WHERE (1 = ? OR f.state = ?) AND (1 = ? OR f.in_channel_scid = ?) AND (1 = ? OR f.out_channel_scid = ?)",
         .query = "SELECT  f.state, in_msatoshi, out_msatoshi, hin.payment_hash as payment_hash, in_channel_scid, out_channel_scid, f.received_time, f.resolved_time, f.failcode FROM forwarded_payments f LEFT JOIN channel_htlcs hin ON (f.in_htlc_id = hin.id) WHERE (1 = $1 OR f.state = $2) AND (1 = $3 OR f.in_channel_scid = $4) AND (1 = $5 OR f.out_channel_scid = $6)",
         .placeholders = 6,
         .readonly = true,
    },
    {
         .name = "SELECT  t.id, t.rawtx, t.blockheight, t.txindex, t.type as txtype, c2.short_channel_id as txchan, a.location, a.idx as ann_idx, a.type as annotation_type, c.short_channel_id FROM  transactions t LEFT JOIN  transaction_annotations a ON (a.txid = t.id) LEFT JOIN  channels c ON (a.channel = c.id) LEFT JOIN  channels c2 ON (t.channel_id = c2.id) ORDER BY t.blockheight, t.txindex ASC",
         .query = "SELECT  t.id, t.rawtx, t.blockheight, t.txindex, t.type as txtype, c2.short_channel_id as txchan, a.location, a.idx as ann_idx, a.type as annotation_type, c.short_channel_id FROM  transactions t LEFT JOIN  transaction_annotations a ON (a.txid = t.id) LEFT JOIN  channels c ON (a.channel = c.id) LEFT JOIN  channels c2 ON (t.channel_id = c2.id) ORDER BY t.blockheight, t.txindex ASC",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "INSERT INTO penalty_bases (  channel_id, commitnum, txid, outnum, amount) VALUES (?, ?, ?, ?, ?);",
         .query = "INSERT INTO penalty_bases (  channel_id, commitnum, txid, outnum, amount) VALUES ($1, $2, $3, $4, $5);",
         .placeholders = 5,
         .readonly = false,
    },
    {
         .name = "SELECT commitnum, txid, outnum, amount FROM penalty_bases WHERE channel_id = ?",
         .query = "SELECT commitnum, txid, outnum, amount FROM penalty_bases WHERE channel_id = $1",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "DELETE FROM penalty_bases WHERE channel_id = ? AND commitnum = ?",
         .query = "DELETE FROM penalty_bases WHERE channel_id = $1 AND commitnum = $2",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "SELECT 1  FROM offers WHERE offer_id = ?;",
         .query = "SELECT 1  FROM offers WHERE offer_id = $1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "INSERT INTO offers (  offer_id, bolt12, label, status) VALUES (?, ?, ?, ?);",
         .query = "INSERT INTO offers (  offer_id, bolt12, label, status) VALUES ($1, $2, $3, $4);",
         .placeholders = 4,
         .readonly = false,
    },
    {
         .name = "SELECT bolt12, label, status  FROM offers WHERE offer_id = ?;",
         .query = "SELECT bolt12, label, status  FROM offers WHERE offer_id = $1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT offer_id FROM offers;",
         .query = "SELECT offer_id FROM offers;",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "UPDATE offers SET status=? WHERE offer_id = ?;",
         .query = "UPDATE offers SET status=$1 WHERE offer_id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "UPDATE invoices SET state=? WHERE state=? AND local_offer_id = ?;",
         .query = "UPDATE invoices SET state=$1 WHERE state=$2 AND local_offer_id = $3;",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "SELECT status  FROM offers WHERE offer_id = ?;",
         .query = "SELECT status  FROM offers WHERE offer_id = $1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "UPDATE datastore SET data=?, generation=generation+1 WHERE key=?;",
         .query = "UPDATE datastore SET data=$1, generation=generation+1 WHERE key=$2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "INSERT INTO datastore VALUES (?, ?, 0);",
         .query = "INSERT INTO datastore VALUES ($1, $2, 0);",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "DELETE FROM datastore WHERE key = ?",
         .query = "DELETE FROM datastore WHERE key = $1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "SELECT key, data, generation FROM datastore WHERE key >= ? ORDER BY key;",
         .query = "SELECT key, data, generation FROM datastore WHERE key >= $1 ORDER BY key;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "SELECT key, data, generation FROM datastore ORDER BY key;",
         .query = "SELECT key, data, generation FROM datastore ORDER BY key;",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "SELECT name FROM sqlite_master WHERE type='table';",
         .query = "SELECT name FROM sqlite_master WHERE type='table';",
         .placeholders = 0,
         .readonly = true,
    },
    {
         .name = "not a valid SQL statement",
         .query = "not a valid SQL statement",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT COUNT(1) FROM channel_funding_inflights WHERE channel_id = ?;",
         .query = "SELECT COUNT(1) FROM channel_funding_inflights WHERE channel_id = $1;",
         .placeholders = 1,
         .readonly = true,
    },
    {
         .name = "INSERT INTO channels (id) VALUES (1);",
         .query = "INSERT INTO channels (id) VALUES (1);",
         .placeholders = 0,
         .readonly = false,
    },
};

#define DB_POSTGRES_QUERY_COUNT 345

#endif /* HAVE_POSTGRES */

#endif /* LIGHTNINGD_WALLET_GEN_DB_POSTGRES */

<<<<<<< refs/remotes/ElementsProject/master
<<<<<<< refs/remotes/ElementsProject/master
<<<<<<< refs/remotes/ElementsProject/master
<<<<<<< refs/remotes/ElementsProject/master
// SHA256STAMP:d812809c7895cea0ed904084e48c523ea01a8cd9525e4b6be1b4e05bec2a90d1
=======
=======
>>>>>>> wallet db: Support the query on database with status and payment hash.
=======
>>>>>>> doc: Update doc with the new parameter supported
=======
>>>>>>> plugin: Adding status to the pay plugin
<<<<<<< refs/remotes/ElementsProject/master
// SHA256STAMP:e356b7327b760559f9a7c31a7ea4a09d50194c7aacc6daef6ba9fb5caf43ae83
=======
=======
>>>>>>> wallet db: Support the query on database with status and payment hash.
=======
>>>>>>> doc: Update doc with the new parameter supported
=======
>>>>>>> plugin: Adding status to the pay plugin
<<<<<<< refs/remotes/ElementsProject/master
// SHA256STAMP:a70af01d3b2f3a7003703b7feb0b2ef12359e0d2850bde1697a53780e2f5dbae
=======
=======
>>>>>>> wallet db: Support the query on database with status and payment hash.
=======
>>>>>>> doc: Update doc with the new parameter supported
=======
>>>>>>> plugin: Adding status to the pay plugin
<<<<<<< refs/remotes/ElementsProject/master
// SHA256STAMP:f929ee6db13bdf55b5e0cdf54840091948b664a61c63a4aaaef403dc7e6f23ad
=======
=======
>>>>>>> wallet db: Support the query on database with status and payment hash.
=======
>>>>>>> doc: Update doc with the new parameter supported
<<<<<<< refs/remotes/ElementsProject/master
// SHA256STAMP:219fccaaf2391eeabadd4cc15b4a3431c7ecab9d17755582e6962a34c74982c5
=======
=======
>>>>>>> wallet db: Support the query on database with status and payment hash.
=======
>>>>>>> doc: Update doc with the new parameter supported
<<<<<<< refs/remotes/ElementsProject/master
// SHA256STAMP:1808964024bcccbd2787e723881f263b1a77ea33c302ac2b6d61dae20486a7e4
=======
=======
>>>>>>> wallet db: Support the query on database with status and payment hash.
=======
>>>>>>> doc: Update doc with the new parameter supported
<<<<<<< refs/remotes/ElementsProject/master
// SHA256STAMP:411593f0957475d832c02cd75a8b0eed30b00fc6178797262ae7dd697de22383
=======
=======
>>>>>>> wallet db: Support the query on database with status and payment hash.
=======
>>>>>>> doc: Update doc with the new parameter supported
<<<<<<< refs/remotes/ElementsProject/master
// SHA256STAMP:be7e5cedcb61a9b96566d4531bb25f2db4e5a344b0d884eec3fc3adf7a4fe242
=======
=======
>>>>>>> wallet db: Support the query on database with status and payment hash.
=======
>>>>>>> doc: Update doc with the new parameter supported
<<<<<<< refs/remotes/ElementsProject/master
// SHA256STAMP:df06b800543e6bb886100ca428247ac1097f749098779dae43ba875154700f58
=======
=======
>>>>>>> wallet db: Support the query on database with status and payment hash.
=======
>>>>>>> doc: Update doc with the new parameter supported
<<<<<<< refs/remotes/ElementsProject/master
// SHA256STAMP:27a166e040e517422e91cf7ffbd12426b34337b8d75f82d7aa4c448beae5e821
=======
=======
>>>>>>> wallet db: Support the query on database with status and payment hash.
<<<<<<< refs/remotes/ElementsProject/master
// SHA256STAMP:6353b67b3e4f539da2d1f0c2564c4a8243f07d59cd0b73bc83d5552600bd67f7
=======
// SHA256STAMP:b5f4c156aa7e336af86f98eafc5e198d3653ff27b21d861a5e777645bf6d89ec
>>>>>>> rpc: Integrate the status flow in the listsendpays command
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> rpc: Integrate the status flow in the listsendpays command
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> rpc: Integrate the status flow in the listsendpays command
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> rpc: Integrate the status flow in the listsendpays command
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> rpc: Integrate the status flow in the listsendpays command
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> rpc: Integrate the status flow in the listsendpays command
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> rpc: Integrate the status flow in the listsendpays command
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> rpc: Integrate the status flow in the listsendpays command
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> rpc: Integrate the status flow in the listsendpays command
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> rpc: Integrate the status flow in the listsendpays command
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> rpc: Integrate the status flow in the listsendpays command
=======
=======
=======
=======
=======
=======
=======
=======
=======
=======
=======
// SHA256STAMP:2af9ace16d4db060e649c3e078271504fce5a7c5661a25464a551aa7cc7029d0
>>>>>>> wallet db: Support the query on database with status and payment hash.
>>>>>>> wallet db: Support the query on database with status and payment hash.
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> wallet db: Support the query on database with status and payment hash.
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> wallet db: Support the query on database with status and payment hash.
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> wallet db: Support the query on database with status and payment hash.
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> wallet db: Support the query on database with status and payment hash.
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> wallet db: Support the query on database with status and payment hash.
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> wallet db: Support the query on database with status and payment hash.
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> wallet db: Support the query on database with status and payment hash.
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> wallet db: Support the query on database with status and payment hash.
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> wallet db: Support the query on database with status and payment hash.
=======
=======
=======
=======
=======
=======
=======
=======
=======
=======
// SHA256STAMP:c08699eae7d8de418f7b197aad5682203ebbae633ce8888b9b4797a2db8ce106
>>>>>>> doc: Update doc with the new parameter supported
>>>>>>> doc: Update doc with the new parameter supported
>>>>>>> doc: Update doc with the new parameter supported
>>>>>>> doc: Update doc with the new parameter supported
>>>>>>> doc: Update doc with the new parameter supported
>>>>>>> doc: Update doc with the new parameter supported
>>>>>>> doc: Update doc with the new parameter supported
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> doc: Update doc with the new parameter supported
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> doc: Update doc with the new parameter supported
<<<<<<< refs/remotes/ElementsProject/master
>>>>>>> doc: Update doc with the new parameter supported
=======
=======
=======
=======
// SHA256STAMP:d6c1c3aced24e67abe2596259beb7599406c070622ef70f88f07d2672c4f4eb9
>>>>>>> plugin: Adding status to the pay plugin
>>>>>>> plugin: Adding status to the pay plugin
>>>>>>> plugin: Adding status to the pay plugin
>>>>>>> plugin: Adding status to the pay plugin
