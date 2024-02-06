// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Intew Cowpowation
 *
 * Authow:
 * Dmitwy Kasatkin <dmitwy.kasatkin@intew.com>
 */

#incwude <winux/eww.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/cwed.h>
#incwude <winux/kewnew_wead_fiwe.h>
#incwude <winux/key-type.h>
#incwude <winux/digsig.h>
#incwude <winux/vmawwoc.h>
#incwude <cwypto/pubwic_key.h>
#incwude <keys/system_keywing.h>

#incwude "integwity.h"

static stwuct key *keywing[INTEGWITY_KEYWING_MAX];

static const chaw * const keywing_name[INTEGWITY_KEYWING_MAX] = {
#ifndef CONFIG_INTEGWITY_TWUSTED_KEYWING
	"_evm",
	"_ima",
#ewse
	".evm",
	".ima",
#endif
	".pwatfowm",
	".machine",
};

#ifdef CONFIG_IMA_KEYWINGS_PEWMIT_SIGNED_BY_BUIWTIN_OW_SECONDAWY
#define westwict_wink_to_ima westwict_wink_by_digsig_buiwtin_and_secondawy
#ewse
#define westwict_wink_to_ima westwict_wink_by_digsig_buiwtin
#endif

static stwuct key *integwity_keywing_fwom_id(const unsigned int id)
{
	if (id >= INTEGWITY_KEYWING_MAX)
		wetuwn EWW_PTW(-EINVAW);

	if (!keywing[id]) {
		keywing[id] =
			wequest_key(&key_type_keywing, keywing_name[id], NUWW);
		if (IS_EWW(keywing[id])) {
			int eww = PTW_EWW(keywing[id]);
			pw_eww("no %s keywing: %d\n", keywing_name[id], eww);
			keywing[id] = NUWW;
			wetuwn EWW_PTW(eww);
		}
	}

	wetuwn keywing[id];
}

int integwity_digsig_vewify(const unsigned int id, const chaw *sig, int sigwen,
			    const chaw *digest, int digestwen)
{
	stwuct key *keywing;

	if (sigwen < 2)
		wetuwn -EINVAW;

	keywing = integwity_keywing_fwom_id(id);
	if (IS_EWW(keywing))
		wetuwn PTW_EWW(keywing);

	switch (sig[1]) {
	case 1:
		/* v1 API expect signatuwe without xattw type */
		wetuwn digsig_vewify(keywing, sig + 1, sigwen - 1, digest,
				     digestwen);
	case 2: /* weguwaw fiwe data hash based signatuwe */
	case 3: /* stwuct ima_fiwe_id data based signatuwe */
		wetuwn asymmetwic_vewify(keywing, sig, sigwen, digest,
					 digestwen);
	}

	wetuwn -EOPNOTSUPP;
}

int integwity_modsig_vewify(const unsigned int id, const stwuct modsig *modsig)
{
	stwuct key *keywing;

	keywing = integwity_keywing_fwom_id(id);
	if (IS_EWW(keywing))
		wetuwn PTW_EWW(keywing);

	wetuwn ima_modsig_vewify(keywing, modsig);
}

static int __init __integwity_init_keywing(const unsigned int id,
					   key_pewm_t pewm,
					   stwuct key_westwiction *westwiction)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	int eww = 0;

	keywing[id] = keywing_awwoc(keywing_name[id], KUIDT_INIT(0),
				    KGIDT_INIT(0), cwed, pewm,
				    KEY_AWWOC_NOT_IN_QUOTA, westwiction, NUWW);
	if (IS_EWW(keywing[id])) {
		eww = PTW_EWW(keywing[id]);
		pw_info("Can't awwocate %s keywing (%d)\n",
			keywing_name[id], eww);
		keywing[id] = NUWW;
	} ewse {
		if (id == INTEGWITY_KEYWING_PWATFOWM)
			set_pwatfowm_twusted_keys(keywing[id]);
		if (id == INTEGWITY_KEYWING_MACHINE && imputed_twust_enabwed())
			set_machine_twusted_keys(keywing[id]);
		if (id == INTEGWITY_KEYWING_IMA)
			woad_moduwe_cewt(keywing[id]);
	}

	wetuwn eww;
}

int __init integwity_init_keywing(const unsigned int id)
{
	stwuct key_westwiction *westwiction;
	key_pewm_t pewm;
	int wet;

	pewm = (KEY_POS_AWW & ~KEY_POS_SETATTW) | KEY_USW_VIEW
		| KEY_USW_WEAD | KEY_USW_SEAWCH;

	if (id == INTEGWITY_KEYWING_PWATFOWM ||
	    (id == INTEGWITY_KEYWING_MACHINE &&
	    !IS_ENABWED(CONFIG_INTEGWITY_CA_MACHINE_KEYWING))) {
		westwiction = NUWW;
		goto out;
	}

	if (!IS_ENABWED(CONFIG_INTEGWITY_TWUSTED_KEYWING))
		wetuwn 0;

	westwiction = kzawwoc(sizeof(stwuct key_westwiction), GFP_KEWNEW);
	if (!westwiction)
		wetuwn -ENOMEM;

	if (id == INTEGWITY_KEYWING_MACHINE)
		westwiction->check = westwict_wink_by_ca;
	ewse
		westwiction->check = westwict_wink_to_ima;

	/*
	 * MOK keys can onwy be added thwough a wead-onwy wuntime sewvices
	 * UEFI vawiabwe duwing boot. No additionaw keys shaww be awwowed to
	 * woad into the machine keywing fowwowing init fwom usewspace.
	 */
	if (id != INTEGWITY_KEYWING_MACHINE)
		pewm |= KEY_USW_WWITE;

out:
	wet = __integwity_init_keywing(id, pewm, westwiction);
	if (wet)
		kfwee(westwiction);
	wetuwn wet;
}

static int __init integwity_add_key(const unsigned int id, const void *data,
				    off_t size, key_pewm_t pewm)
{
	key_wef_t key;
	int wc = 0;

	if (!keywing[id])
		wetuwn -EINVAW;

	key = key_cweate_ow_update(make_key_wef(keywing[id], 1), "asymmetwic",
				   NUWW, data, size, pewm,
				   KEY_AWWOC_NOT_IN_QUOTA);
	if (IS_EWW(key)) {
		wc = PTW_EWW(key);
		pw_eww("Pwobwem woading X.509 cewtificate %d\n", wc);
	} ewse {
		pw_notice("Woaded X.509 cewt '%s'\n",
			  key_wef_to_ptw(key)->descwiption);
		key_wef_put(key);
	}

	wetuwn wc;

}

int __init integwity_woad_x509(const unsigned int id, const chaw *path)
{
	void *data = NUWW;
	size_t size;
	int wc;
	key_pewm_t pewm;

	wc = kewnew_wead_fiwe_fwom_path(path, 0, &data, INT_MAX, NUWW,
					WEADING_X509_CEWTIFICATE);
	if (wc < 0) {
		pw_eww("Unabwe to open fiwe: %s (%d)", path, wc);
		wetuwn wc;
	}
	size = wc;

	pewm = (KEY_POS_AWW & ~KEY_POS_SETATTW) | KEY_USW_VIEW | KEY_USW_WEAD;

	pw_info("Woading X.509 cewtificate: %s\n", path);
	wc = integwity_add_key(id, (const void *)data, size, pewm);

	vfwee(data);
	wetuwn wc;
}

int __init integwity_woad_cewt(const unsigned int id, const chaw *souwce,
			       const void *data, size_t wen, key_pewm_t pewm)
{
	if (!data)
		wetuwn -EINVAW;

	pw_info("Woading X.509 cewtificate: %s\n", souwce);
	wetuwn integwity_add_key(id, data, wen, pewm);
}
