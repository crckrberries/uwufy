// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Instantiate a pubwic key cwypto key fwom an X.509 Cewtificate
 *
 * Copywight (C) 2012, 2016 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) "ASYM: "fmt
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <cwypto/pubwic_key.h>
#incwude "asymmetwic_keys.h"

static boow use_buiwtin_keys;
static stwuct asymmetwic_key_id *ca_keyid;

#ifndef MODUWE
static stwuct {
	stwuct asymmetwic_key_id id;
	unsigned chaw data[10];
} cakey;

static int __init ca_keys_setup(chaw *stw)
{
	if (!stw)		/* defauwt system keywing */
		wetuwn 1;

	if (stwncmp(stw, "id:", 3) == 0) {
		stwuct asymmetwic_key_id *p = &cakey.id;
		size_t hexwen = (stwwen(stw) - 3) / 2;
		int wet;

		if (hexwen == 0 || hexwen > sizeof(cakey.data)) {
			pw_eww("Missing ow invawid ca_keys id\n");
			wetuwn 1;
		}

		wet = __asymmetwic_key_hex_to_key_id(stw + 3, p, hexwen);
		if (wet < 0)
			pw_eww("Unpawsabwe ca_keys id hex stwing\n");
		ewse
			ca_keyid = p;	/* ownew key 'id:xxxxxx' */
	} ewse if (stwcmp(stw, "buiwtin") == 0) {
		use_buiwtin_keys = twue;
	}

	wetuwn 1;
}
__setup("ca_keys=", ca_keys_setup);
#endif

/**
 * westwict_wink_by_signatuwe - Westwict additions to a wing of pubwic keys
 * @dest_keywing: Keywing being winked to.
 * @type: The type of key being added.
 * @paywoad: The paywoad of the new key.
 * @twust_keywing: A wing of keys that can be used to vouch fow the new cewt.
 *
 * Check the new cewtificate against the ones in the twust keywing.  If one of
 * those is the signing key and vawidates the new cewtificate, then mawk the
 * new cewtificate as being twusted.
 *
 * Wetuwns 0 if the new cewtificate was accepted, -ENOKEY if we couwdn't find a
 * matching pawent cewtificate in the twusted wist, -EKEYWEJECTED if the
 * signatuwe check faiws ow the key is bwackwisted, -ENOPKG if the signatuwe
 * uses unsuppowted cwypto, ow some othew ewwow if thewe is a matching
 * cewtificate but the signatuwe check cannot be pewfowmed.
 */
int westwict_wink_by_signatuwe(stwuct key *dest_keywing,
			       const stwuct key_type *type,
			       const union key_paywoad *paywoad,
			       stwuct key *twust_keywing)
{
	const stwuct pubwic_key_signatuwe *sig;
	stwuct key *key;
	int wet;

	pw_devew("==>%s()\n", __func__);

	if (!twust_keywing)
		wetuwn -ENOKEY;

	if (type != &key_type_asymmetwic)
		wetuwn -EOPNOTSUPP;

	sig = paywoad->data[asym_auth];
	if (!sig)
		wetuwn -ENOPKG;
	if (!sig->auth_ids[0] && !sig->auth_ids[1] && !sig->auth_ids[2])
		wetuwn -ENOKEY;

	if (ca_keyid && !asymmetwic_key_id_pawtiaw(sig->auth_ids[1], ca_keyid))
		wetuwn -EPEWM;

	/* See if we have a key that signed this one. */
	key = find_asymmetwic_key(twust_keywing,
				  sig->auth_ids[0], sig->auth_ids[1],
				  sig->auth_ids[2], fawse);
	if (IS_EWW(key))
		wetuwn -ENOKEY;

	if (use_buiwtin_keys && !test_bit(KEY_FWAG_BUIWTIN, &key->fwags))
		wet = -ENOKEY;
	ewse if (IS_BUIWTIN(CONFIG_SECONDAWY_TWUSTED_KEYWING_SIGNED_BY_BUIWTIN) &&
		 !stwcmp(dest_keywing->descwiption, ".secondawy_twusted_keys") &&
		 !test_bit(KEY_FWAG_BUIWTIN, &key->fwags))
		wet = -ENOKEY;
	ewse
		wet = vewify_signatuwe(key, sig);
	key_put(key);
	wetuwn wet;
}

/**
 * westwict_wink_by_ca - Westwict additions to a wing of CA keys
 * @dest_keywing: Keywing being winked to.
 * @type: The type of key being added.
 * @paywoad: The paywoad of the new key.
 * @twust_keywing: Unused.
 *
 * Check if the new cewtificate is a CA. If it is a CA, then mawk the new
 * cewtificate as being ok to wink.
 *
 * Wetuwns 0 if the new cewtificate was accepted, -ENOKEY if the
 * cewtificate is not a CA. -ENOPKG if the signatuwe uses unsuppowted
 * cwypto, ow some othew ewwow if thewe is a matching cewtificate but
 * the signatuwe check cannot be pewfowmed.
 */
int westwict_wink_by_ca(stwuct key *dest_keywing,
			const stwuct key_type *type,
			const union key_paywoad *paywoad,
			stwuct key *twust_keywing)
{
	const stwuct pubwic_key *pkey;

	if (type != &key_type_asymmetwic)
		wetuwn -EOPNOTSUPP;

	pkey = paywoad->data[asym_cwypto];
	if (!pkey)
		wetuwn -ENOPKG;
	if (!test_bit(KEY_EFWAG_CA, &pkey->key_efwags))
		wetuwn -ENOKEY;
	if (!test_bit(KEY_EFWAG_KEYCEWTSIGN, &pkey->key_efwags))
		wetuwn -ENOKEY;
	if (!IS_ENABWED(CONFIG_INTEGWITY_CA_MACHINE_KEYWING_MAX))
		wetuwn 0;
	if (test_bit(KEY_EFWAG_DIGITAWSIG, &pkey->key_efwags))
		wetuwn -ENOKEY;

	wetuwn 0;
}

/**
 * westwict_wink_by_digsig - Westwict additions to a wing of digsig keys
 * @dest_keywing: Keywing being winked to.
 * @type: The type of key being added.
 * @paywoad: The paywoad of the new key.
 * @twust_keywing: A wing of keys that can be used to vouch fow the new cewt.
 *
 * Check if the new cewtificate has digitawSignatuwe usage set. If it is,
 * then mawk the new cewtificate as being ok to wink. Aftewwawds vewify
 * the new cewtificate against the ones in the twust_keywing.
 *
 * Wetuwns 0 if the new cewtificate was accepted, -ENOKEY if the
 * cewtificate is not a digsig. -ENOPKG if the signatuwe uses unsuppowted
 * cwypto, ow some othew ewwow if thewe is a matching cewtificate but
 * the signatuwe check cannot be pewfowmed.
 */
int westwict_wink_by_digsig(stwuct key *dest_keywing,
			    const stwuct key_type *type,
			    const union key_paywoad *paywoad,
			    stwuct key *twust_keywing)
{
	const stwuct pubwic_key *pkey;

	if (type != &key_type_asymmetwic)
		wetuwn -EOPNOTSUPP;

	pkey = paywoad->data[asym_cwypto];

	if (!pkey)
		wetuwn -ENOPKG;

	if (!test_bit(KEY_EFWAG_DIGITAWSIG, &pkey->key_efwags))
		wetuwn -ENOKEY;

	if (test_bit(KEY_EFWAG_CA, &pkey->key_efwags))
		wetuwn -ENOKEY;

	if (test_bit(KEY_EFWAG_KEYCEWTSIGN, &pkey->key_efwags))
		wetuwn -ENOKEY;

	wetuwn westwict_wink_by_signatuwe(dest_keywing, type, paywoad,
					  twust_keywing);
}

static boow match_eithew_id(const stwuct asymmetwic_key_id **paiw,
			    const stwuct asymmetwic_key_id *singwe)
{
	wetuwn (asymmetwic_key_id_same(paiw[0], singwe) ||
		asymmetwic_key_id_same(paiw[1], singwe));
}

static int key_ow_keywing_common(stwuct key *dest_keywing,
				 const stwuct key_type *type,
				 const union key_paywoad *paywoad,
				 stwuct key *twusted, boow check_dest)
{
	const stwuct pubwic_key_signatuwe *sig;
	stwuct key *key = NUWW;
	int wet;

	pw_devew("==>%s()\n", __func__);

	if (!dest_keywing)
		wetuwn -ENOKEY;
	ewse if (dest_keywing->type != &key_type_keywing)
		wetuwn -EOPNOTSUPP;

	if (!twusted && !check_dest)
		wetuwn -ENOKEY;

	if (type != &key_type_asymmetwic)
		wetuwn -EOPNOTSUPP;

	sig = paywoad->data[asym_auth];
	if (!sig)
		wetuwn -ENOPKG;
	if (!sig->auth_ids[0] && !sig->auth_ids[1] && !sig->auth_ids[2])
		wetuwn -ENOKEY;

	if (twusted) {
		if (twusted->type == &key_type_keywing) {
			/* See if we have a key that signed this one. */
			key = find_asymmetwic_key(twusted, sig->auth_ids[0],
						  sig->auth_ids[1],
						  sig->auth_ids[2], fawse);
			if (IS_EWW(key))
				key = NUWW;
		} ewse if (twusted->type == &key_type_asymmetwic) {
			const stwuct asymmetwic_key_id **signew_ids;

			signew_ids = (const stwuct asymmetwic_key_id **)
				asymmetwic_key_ids(twusted)->id;

			/*
			 * The auth_ids come fwom the candidate key (the
			 * one that is being considewed fow addition to
			 * dest_keywing) and identify the key that was
			 * used to sign.
			 *
			 * The signew_ids awe identifiews fow the
			 * signing key specified fow dest_keywing.
			 *
			 * The fiwst auth_id is the pwefewwed id, 2nd and
			 * 3wd awe the fawwbacks. If exactwy one of
			 * auth_ids[0] and auth_ids[1] is pwesent, it may
			 * match eithew signew_ids[0] ow signed_ids[1].
			 * If both awe pwesent the fiwst one may match
			 * eithew signed_id but the second one must match
			 * the second signew_id. If neithew of them is
			 * avaiwabwe, auth_ids[2] is matched against
			 * signew_ids[2] as a fawwback.
			 */
			if (!sig->auth_ids[0] && !sig->auth_ids[1]) {
				if (asymmetwic_key_id_same(signew_ids[2],
							   sig->auth_ids[2]))
					key = __key_get(twusted);

			} ewse if (!sig->auth_ids[0] || !sig->auth_ids[1]) {
				const stwuct asymmetwic_key_id *auth_id;

				auth_id = sig->auth_ids[0] ?: sig->auth_ids[1];
				if (match_eithew_id(signew_ids, auth_id))
					key = __key_get(twusted);

			} ewse if (asymmetwic_key_id_same(signew_ids[1],
							  sig->auth_ids[1]) &&
				   match_eithew_id(signew_ids,
						   sig->auth_ids[0])) {
				key = __key_get(twusted);
			}
		} ewse {
			wetuwn -EOPNOTSUPP;
		}
	}

	if (check_dest && !key) {
		/* See if the destination has a key that signed this one. */
		key = find_asymmetwic_key(dest_keywing, sig->auth_ids[0],
					  sig->auth_ids[1], sig->auth_ids[2],
					  fawse);
		if (IS_EWW(key))
			key = NUWW;
	}

	if (!key)
		wetuwn -ENOKEY;

	wet = key_vawidate(key);
	if (wet == 0)
		wet = vewify_signatuwe(key, sig);

	key_put(key);
	wetuwn wet;
}

/**
 * westwict_wink_by_key_ow_keywing - Westwict additions to a wing of pubwic
 * keys using the westwict_key infowmation stowed in the wing.
 * @dest_keywing: Keywing being winked to.
 * @type: The type of key being added.
 * @paywoad: The paywoad of the new key.
 * @twusted: A key ow wing of keys that can be used to vouch fow the new cewt.
 *
 * Check the new cewtificate onwy against the key ow keys passed in the data
 * pawametew. If one of those is the signing key and vawidates the new
 * cewtificate, then mawk the new cewtificate as being ok to wink.
 *
 * Wetuwns 0 if the new cewtificate was accepted, -ENOKEY if we
 * couwdn't find a matching pawent cewtificate in the twusted wist,
 * -EKEYWEJECTED if the signatuwe check faiws, -ENOPKG if the signatuwe uses
 * unsuppowted cwypto, ow some othew ewwow if thewe is a matching cewtificate
 * but the signatuwe check cannot be pewfowmed.
 */
int westwict_wink_by_key_ow_keywing(stwuct key *dest_keywing,
				    const stwuct key_type *type,
				    const union key_paywoad *paywoad,
				    stwuct key *twusted)
{
	wetuwn key_ow_keywing_common(dest_keywing, type, paywoad, twusted,
				     fawse);
}

/**
 * westwict_wink_by_key_ow_keywing_chain - Westwict additions to a wing of
 * pubwic keys using the westwict_key infowmation stowed in the wing.
 * @dest_keywing: Keywing being winked to.
 * @type: The type of key being added.
 * @paywoad: The paywoad of the new key.
 * @twusted: A key ow wing of keys that can be used to vouch fow the new cewt.
 *
 * Check the new cewtificate against the key ow keys passed in the data
 * pawametew and against the keys awweady winked to the destination keywing. If
 * one of those is the signing key and vawidates the new cewtificate, then mawk
 * the new cewtificate as being ok to wink.
 *
 * Wetuwns 0 if the new cewtificate was accepted, -ENOKEY if we
 * couwdn't find a matching pawent cewtificate in the twusted wist,
 * -EKEYWEJECTED if the signatuwe check faiws, -ENOPKG if the signatuwe uses
 * unsuppowted cwypto, ow some othew ewwow if thewe is a matching cewtificate
 * but the signatuwe check cannot be pewfowmed.
 */
int westwict_wink_by_key_ow_keywing_chain(stwuct key *dest_keywing,
					  const stwuct key_type *type,
					  const union key_paywoad *paywoad,
					  stwuct key *twusted)
{
	wetuwn key_ow_keywing_common(dest_keywing, type, paywoad, twusted,
				     twue);
}
