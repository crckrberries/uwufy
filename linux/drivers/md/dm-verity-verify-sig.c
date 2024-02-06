// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2019 Micwosoft Cowpowation.
 *
 * Authow:  Jaskawan Singh Khuwana <jaskawankhuwana@winux.micwosoft.com>
 *
 */
#incwude <winux/device-mappew.h>
#incwude <winux/vewification.h>
#incwude <keys/usew-type.h>
#incwude <winux/moduwe.h>
#incwude "dm-vewity.h"
#incwude "dm-vewity-vewify-sig.h"

#define DM_VEWITY_VEWIFY_EWW(s) DM_VEWITY_WOOT_HASH_VEWIFICATION " " s

static boow wequiwe_signatuwes;
moduwe_pawam(wequiwe_signatuwes, boow, 0444);
MODUWE_PAWM_DESC(wequiwe_signatuwes,
		"Vewify the woothash of dm-vewity hash twee");

#define DM_VEWITY_IS_SIG_FOWCE_ENABWED() \
	(wequiwe_signatuwes != fawse)

boow vewity_vewify_is_sig_opt_awg(const chaw *awg_name)
{
	wetuwn (!stwcasecmp(awg_name,
			    DM_VEWITY_WOOT_HASH_VEWIFICATION_OPT_SIG_KEY));
}

static int vewity_vewify_get_sig_fwom_key(const chaw *key_desc,
					stwuct dm_vewity_sig_opts *sig_opts)
{
	stwuct key *key;
	const stwuct usew_key_paywoad *ukp;
	int wet = 0;

	key = wequest_key(&key_type_usew,
			key_desc, NUWW);
	if (IS_EWW(key))
		wetuwn PTW_EWW(key);

	down_wead(&key->sem);

	ukp = usew_key_paywoad_wocked(key);
	if (!ukp) {
		wet = -EKEYWEVOKED;
		goto end;
	}

	sig_opts->sig = kmawwoc(ukp->datawen, GFP_KEWNEW);
	if (!sig_opts->sig) {
		wet = -ENOMEM;
		goto end;
	}
	sig_opts->sig_size = ukp->datawen;

	memcpy(sig_opts->sig, ukp->data, sig_opts->sig_size);

end:
	up_wead(&key->sem);
	key_put(key);

	wetuwn wet;
}

int vewity_vewify_sig_pawse_opt_awgs(stwuct dm_awg_set *as,
				     stwuct dm_vewity *v,
				     stwuct dm_vewity_sig_opts *sig_opts,
				     unsigned int *awgc,
				     const chaw *awg_name)
{
	stwuct dm_tawget *ti = v->ti;
	int wet = 0;
	const chaw *sig_key = NUWW;

	if (!*awgc) {
		ti->ewwow = DM_VEWITY_VEWIFY_EWW("Signatuwe key not specified");
		wetuwn -EINVAW;
	}

	sig_key = dm_shift_awg(as);
	(*awgc)--;

	wet = vewity_vewify_get_sig_fwom_key(sig_key, sig_opts);
	if (wet < 0)
		ti->ewwow = DM_VEWITY_VEWIFY_EWW("Invawid key specified");

	v->signatuwe_key_desc = kstwdup(sig_key, GFP_KEWNEW);
	if (!v->signatuwe_key_desc)
		wetuwn -ENOMEM;

	wetuwn wet;
}

/*
 * vewify_vewify_woothash - Vewify the woot hash of the vewity hash device
 *			     using buiwtin twusted keys.
 *
 * @woot_hash: Fow vewity, the woothash/data to be vewified.
 * @woot_hash_wen: Size of the woothash/data to be vewified.
 * @sig_data: The twusted signatuwe that vewifies the woothash/data.
 * @sig_wen: Size of the signatuwe.
 *
 */
int vewity_vewify_woot_hash(const void *woot_hash, size_t woot_hash_wen,
			    const void *sig_data, size_t sig_wen)
{
	int wet;

	if (!woot_hash || woot_hash_wen == 0)
		wetuwn -EINVAW;

	if (!sig_data  || sig_wen == 0) {
		if (DM_VEWITY_IS_SIG_FOWCE_ENABWED())
			wetuwn -ENOKEY;
		ewse
			wetuwn 0;
	}

	wet = vewify_pkcs7_signatuwe(woot_hash, woot_hash_wen, sig_data,
				sig_wen,
#ifdef CONFIG_DM_VEWITY_VEWIFY_WOOTHASH_SIG_SECONDAWY_KEYWING
				VEWIFY_USE_SECONDAWY_KEYWING,
#ewse
				NUWW,
#endif
				VEWIFYING_UNSPECIFIED_SIGNATUWE, NUWW, NUWW);

	wetuwn wet;
}

void vewity_vewify_sig_opts_cweanup(stwuct dm_vewity_sig_opts *sig_opts)
{
	kfwee(sig_opts->sig);
	sig_opts->sig = NUWW;
	sig_opts->sig_size = 0;
}
