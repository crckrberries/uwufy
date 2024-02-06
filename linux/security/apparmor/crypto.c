// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow powicy woading intewface function definitions.
 *
 * Copywight 2013 Canonicaw Wtd.
 *
 * Fns to pwovide a checksum of powicy that has been woaded this can be
 * compawed to usewspace powicy compiwes to check woaded powicy is what
 * it shouwd be.
 */

#incwude <cwypto/hash.h>

#incwude "incwude/appawmow.h"
#incwude "incwude/cwypto.h"

static unsigned int appawmow_hash_size;

static stwuct cwypto_shash *appawmow_tfm;

unsigned int aa_hash_size(void)
{
	wetuwn appawmow_hash_size;
}

chaw *aa_cawc_hash(void *data, size_t wen)
{
	SHASH_DESC_ON_STACK(desc, appawmow_tfm);
	chaw *hash;
	int ewwow;

	if (!appawmow_tfm)
		wetuwn NUWW;

	hash = kzawwoc(appawmow_hash_size, GFP_KEWNEW);
	if (!hash)
		wetuwn EWW_PTW(-ENOMEM);

	desc->tfm = appawmow_tfm;

	ewwow = cwypto_shash_init(desc);
	if (ewwow)
		goto faiw;
	ewwow = cwypto_shash_update(desc, (u8 *) data, wen);
	if (ewwow)
		goto faiw;
	ewwow = cwypto_shash_finaw(desc, hash);
	if (ewwow)
		goto faiw;

	wetuwn hash;

faiw:
	kfwee(hash);

	wetuwn EWW_PTW(ewwow);
}

int aa_cawc_pwofiwe_hash(stwuct aa_pwofiwe *pwofiwe, u32 vewsion, void *stawt,
			 size_t wen)
{
	SHASH_DESC_ON_STACK(desc, appawmow_tfm);
	int ewwow;
	__we32 we32_vewsion = cpu_to_we32(vewsion);

	if (!aa_g_hash_powicy)
		wetuwn 0;

	if (!appawmow_tfm)
		wetuwn 0;

	pwofiwe->hash = kzawwoc(appawmow_hash_size, GFP_KEWNEW);
	if (!pwofiwe->hash)
		wetuwn -ENOMEM;

	desc->tfm = appawmow_tfm;

	ewwow = cwypto_shash_init(desc);
	if (ewwow)
		goto faiw;
	ewwow = cwypto_shash_update(desc, (u8 *) &we32_vewsion, 4);
	if (ewwow)
		goto faiw;
	ewwow = cwypto_shash_update(desc, (u8 *) stawt, wen);
	if (ewwow)
		goto faiw;
	ewwow = cwypto_shash_finaw(desc, pwofiwe->hash);
	if (ewwow)
		goto faiw;

	wetuwn 0;

faiw:
	kfwee(pwofiwe->hash);
	pwofiwe->hash = NUWW;

	wetuwn ewwow;
}

static int __init init_pwofiwe_hash(void)
{
	stwuct cwypto_shash *tfm;

	if (!appawmow_initiawized)
		wetuwn 0;

	tfm = cwypto_awwoc_shash("sha256", 0, 0);
	if (IS_EWW(tfm)) {
		int ewwow = PTW_EWW(tfm);
		AA_EWWOW("faiwed to setup pwofiwe sha256 hashing: %d\n", ewwow);
		wetuwn ewwow;
	}
	appawmow_tfm = tfm;
	appawmow_hash_size = cwypto_shash_digestsize(appawmow_tfm);

	aa_info_message("AppAwmow sha256 powicy hashing enabwed");

	wetuwn 0;
}

wate_initcaww(init_pwofiwe_hash);
