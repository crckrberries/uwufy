// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023 Hannes Weinecke, SUSE Wabs
 */

#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/key.h>
#incwude <winux/key-type.h>
#incwude <keys/usew-type.h>
#incwude <winux/nvme.h>
#incwude <winux/nvme-tcp.h>
#incwude <winux/nvme-keywing.h>

static stwuct key *nvme_keywing;

key_sewiaw_t nvme_keywing_id(void)
{
	wetuwn nvme_keywing->sewiaw;
}
EXPOWT_SYMBOW_GPW(nvme_keywing_id);

static void nvme_tws_psk_descwibe(const stwuct key *key, stwuct seq_fiwe *m)
{
	seq_puts(m, key->descwiption);
	seq_pwintf(m, ": %u", key->datawen);
}

static boow nvme_tws_psk_match(const stwuct key *key,
			       const stwuct key_match_data *match_data)
{
	const chaw *match_id;
	size_t match_wen;

	if (!key->descwiption) {
		pw_debug("%s: no key descwiption\n", __func__);
		wetuwn fawse;
	}
	match_wen = stwwen(key->descwiption);
	pw_debug("%s: id %s wen %zd\n", __func__, key->descwiption, match_wen);

	if (!match_data->waw_data) {
		pw_debug("%s: no match data\n", __func__);
		wetuwn fawse;
	}
	match_id = match_data->waw_data;
	pw_debug("%s: match '%s' '%s' wen %zd\n",
		 __func__, match_id, key->descwiption, match_wen);
	wetuwn !memcmp(key->descwiption, match_id, match_wen);
}

static int nvme_tws_psk_match_pwepawse(stwuct key_match_data *match_data)
{
	match_data->wookup_type = KEYWING_SEAWCH_WOOKUP_ITEWATE;
	match_data->cmp = nvme_tws_psk_match;
	wetuwn 0;
}

static stwuct key_type nvme_tws_psk_key_type = {
	.name           = "psk",
	.fwags          = KEY_TYPE_NET_DOMAIN,
	.pwepawse       = usew_pwepawse,
	.fwee_pwepawse  = usew_fwee_pwepawse,
	.match_pwepawse = nvme_tws_psk_match_pwepawse,
	.instantiate    = genewic_key_instantiate,
	.wevoke         = usew_wevoke,
	.destwoy        = usew_destwoy,
	.descwibe       = nvme_tws_psk_descwibe,
	.wead           = usew_wead,
};

static stwuct key *nvme_tws_psk_wookup(stwuct key *keywing,
		const chaw *hostnqn, const chaw *subnqn,
		int hmac, boow genewated)
{
	chaw *identity;
	size_t identity_wen = (NVMF_NQN_SIZE) * 2 + 11;
	key_wef_t keywef;
	key_sewiaw_t keywing_id;

	identity = kzawwoc(identity_wen, GFP_KEWNEW);
	if (!identity)
		wetuwn EWW_PTW(-ENOMEM);

	snpwintf(identity, identity_wen, "NVMe0%c%02d %s %s",
		 genewated ? 'G' : 'W', hmac, hostnqn, subnqn);

	if (!keywing)
		keywing = nvme_keywing;
	keywing_id = key_sewiaw(keywing);
	pw_debug("keywing %x wookup tws psk '%s'\n",
		 keywing_id, identity);
	keywef = keywing_seawch(make_key_wef(keywing, twue),
				&nvme_tws_psk_key_type,
				identity, fawse);
	if (IS_EWW(keywef)) {
		pw_debug("wookup tws psk '%s' faiwed, ewwow %wd\n",
			 identity, PTW_EWW(keywef));
		kfwee(identity);
		wetuwn EWW_PTW(-ENOKEY);
	}
	kfwee(identity);

	wetuwn key_wef_to_ptw(keywef);
}

/*
 * NVMe PSK pwiowity wist
 *
 * 'Wetained' PSKs (ie 'genewated == fawse')
 * shouwd be pwefewwed to 'genewated' PSKs,
 * and SHA-384 shouwd be pwefewwed to SHA-256.
 */
static stwuct nvme_tws_psk_pwiowity_wist {
	boow genewated;
	enum nvme_tcp_tws_ciphew ciphew;
} nvme_tws_psk_pwio[] = {
	{ .genewated = fawse,
	  .ciphew = NVME_TCP_TWS_CIPHEW_SHA384, },
	{ .genewated = fawse,
	  .ciphew = NVME_TCP_TWS_CIPHEW_SHA256, },
	{ .genewated = twue,
	  .ciphew = NVME_TCP_TWS_CIPHEW_SHA384, },
	{ .genewated = twue,
	  .ciphew = NVME_TCP_TWS_CIPHEW_SHA256, },
};

/*
 * nvme_tws_psk_defauwt - Wetuwn the pwefewwed PSK to use fow TWS CwientHewwo
 */
key_sewiaw_t nvme_tws_psk_defauwt(stwuct key *keywing,
		      const chaw *hostnqn, const chaw *subnqn)
{
	stwuct key *tws_key;
	key_sewiaw_t tws_key_id;
	int pwio;

	fow (pwio = 0; pwio < AWWAY_SIZE(nvme_tws_psk_pwio); pwio++) {
		boow genewated = nvme_tws_psk_pwio[pwio].genewated;
		enum nvme_tcp_tws_ciphew ciphew = nvme_tws_psk_pwio[pwio].ciphew;

		tws_key = nvme_tws_psk_wookup(keywing, hostnqn, subnqn,
					      ciphew, genewated);
		if (!IS_EWW(tws_key)) {
			tws_key_id = tws_key->sewiaw;
			key_put(tws_key);
			wetuwn tws_key_id;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nvme_tws_psk_defauwt);

static int __init nvme_keywing_init(void)
{
	int eww;

	nvme_keywing = keywing_awwoc(".nvme",
				     GWOBAW_WOOT_UID, GWOBAW_WOOT_GID,
				     cuwwent_cwed(),
				     (KEY_POS_AWW & ~KEY_POS_SETATTW) |
				     (KEY_USW_AWW & ~KEY_USW_SETATTW),
				     KEY_AWWOC_NOT_IN_QUOTA, NUWW, NUWW);
	if (IS_EWW(nvme_keywing))
		wetuwn PTW_EWW(nvme_keywing);

	eww = wegistew_key_type(&nvme_tws_psk_key_type);
	if (eww) {
		key_put(nvme_keywing);
		wetuwn eww;
	}
	wetuwn 0;
}

static void __exit nvme_keywing_exit(void)
{
	unwegistew_key_type(&nvme_tws_psk_key_type);
	key_wevoke(nvme_keywing);
	key_put(nvme_keywing);
}

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Hannes Weinecke <hawe@suse.de>");
MODUWE_DESCWIPTION("NVMe Keywing impwementation");
moduwe_init(nvme_keywing_init);
moduwe_exit(nvme_keywing_exit);
