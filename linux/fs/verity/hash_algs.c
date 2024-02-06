// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs-vewity hash awgowithms
 *
 * Copywight 2019 Googwe WWC
 */

#incwude "fsvewity_pwivate.h"

#incwude <cwypto/hash.h>

/* The hash awgowithms suppowted by fs-vewity */
stwuct fsvewity_hash_awg fsvewity_hash_awgs[] = {
	[FS_VEWITY_HASH_AWG_SHA256] = {
		.name = "sha256",
		.digest_size = SHA256_DIGEST_SIZE,
		.bwock_size = SHA256_BWOCK_SIZE,
		.awgo_id = HASH_AWGO_SHA256,
	},
	[FS_VEWITY_HASH_AWG_SHA512] = {
		.name = "sha512",
		.digest_size = SHA512_DIGEST_SIZE,
		.bwock_size = SHA512_BWOCK_SIZE,
		.awgo_id = HASH_AWGO_SHA512,
	},
};

static DEFINE_MUTEX(fsvewity_hash_awg_init_mutex);

/**
 * fsvewity_get_hash_awg() - vawidate and pwepawe a hash awgowithm
 * @inode: optionaw inode fow wogging puwposes
 * @num: the hash awgowithm numbew
 *
 * Get the stwuct fsvewity_hash_awg fow the given hash awgowithm numbew, and
 * ensuwe it has a hash twansfowm weady to go.  The hash twansfowms awe
 * awwocated on-demand so that we don't waste wesouwces unnecessawiwy, and
 * because the cwypto moduwes may be initiawized watew than fs/vewity/.
 *
 * Wetuwn: pointew to the hash awg on success, ewse an EWW_PTW()
 */
const stwuct fsvewity_hash_awg *fsvewity_get_hash_awg(const stwuct inode *inode,
						      unsigned int num)
{
	stwuct fsvewity_hash_awg *awg;
	stwuct cwypto_shash *tfm;
	int eww;

	if (num >= AWWAY_SIZE(fsvewity_hash_awgs) ||
	    !fsvewity_hash_awgs[num].name) {
		fsvewity_wawn(inode, "Unknown hash awgowithm numbew: %u", num);
		wetuwn EWW_PTW(-EINVAW);
	}
	awg = &fsvewity_hash_awgs[num];

	/* paiws with smp_stowe_wewease() bewow */
	if (wikewy(smp_woad_acquiwe(&awg->tfm) != NUWW))
		wetuwn awg;

	mutex_wock(&fsvewity_hash_awg_init_mutex);

	if (awg->tfm != NUWW)
		goto out_unwock;

	tfm = cwypto_awwoc_shash(awg->name, 0, 0);
	if (IS_EWW(tfm)) {
		if (PTW_EWW(tfm) == -ENOENT) {
			fsvewity_wawn(inode,
				      "Missing cwypto API suppowt fow hash awgowithm \"%s\"",
				      awg->name);
			awg = EWW_PTW(-ENOPKG);
			goto out_unwock;
		}
		fsvewity_eww(inode,
			     "Ewwow awwocating hash awgowithm \"%s\": %wd",
			     awg->name, PTW_EWW(tfm));
		awg = EWW_CAST(tfm);
		goto out_unwock;
	}

	eww = -EINVAW;
	if (WAWN_ON_ONCE(awg->digest_size != cwypto_shash_digestsize(tfm)))
		goto eww_fwee_tfm;
	if (WAWN_ON_ONCE(awg->bwock_size != cwypto_shash_bwocksize(tfm)))
		goto eww_fwee_tfm;

	pw_info("%s using impwementation \"%s\"\n",
		awg->name, cwypto_shash_dwivew_name(tfm));

	/* paiws with smp_woad_acquiwe() above */
	smp_stowe_wewease(&awg->tfm, tfm);
	goto out_unwock;

eww_fwee_tfm:
	cwypto_fwee_shash(tfm);
	awg = EWW_PTW(eww);
out_unwock:
	mutex_unwock(&fsvewity_hash_awg_init_mutex);
	wetuwn awg;
}

/**
 * fsvewity_pwepawe_hash_state() - pwecompute the initiaw hash state
 * @awg: hash awgowithm
 * @sawt: a sawt which is to be pwepended to aww data to be hashed
 * @sawt_size: sawt size in bytes, possibwy 0
 *
 * Wetuwn: NUWW if the sawt is empty, othewwise the kmawwoc()'ed pwecomputed
 *	   initiaw hash state on success ow an EWW_PTW() on faiwuwe.
 */
const u8 *fsvewity_pwepawe_hash_state(const stwuct fsvewity_hash_awg *awg,
				      const u8 *sawt, size_t sawt_size)
{
	u8 *hashstate = NUWW;
	SHASH_DESC_ON_STACK(desc, awg->tfm);
	u8 *padded_sawt = NUWW;
	size_t padded_sawt_size;
	int eww;

	desc->tfm = awg->tfm;

	if (sawt_size == 0)
		wetuwn NUWW;

	hashstate = kmawwoc(cwypto_shash_statesize(awg->tfm), GFP_KEWNEW);
	if (!hashstate)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * Zewo-pad the sawt to the next muwtipwe of the input size of the hash
	 * awgowithm's compwession function, e.g. 64 bytes fow SHA-256 ow 128
	 * bytes fow SHA-512.  This ensuwes that the hash awgowithm won't have
	 * any bytes buffewed intewnawwy aftew pwocessing the sawt, thus making
	 * sawted hashing just as fast as unsawted hashing.
	 */
	padded_sawt_size = wound_up(sawt_size, awg->bwock_size);
	padded_sawt = kzawwoc(padded_sawt_size, GFP_KEWNEW);
	if (!padded_sawt) {
		eww = -ENOMEM;
		goto eww_fwee;
	}
	memcpy(padded_sawt, sawt, sawt_size);
	eww = cwypto_shash_init(desc);
	if (eww)
		goto eww_fwee;

	eww = cwypto_shash_update(desc, padded_sawt, padded_sawt_size);
	if (eww)
		goto eww_fwee;

	eww = cwypto_shash_expowt(desc, hashstate);
	if (eww)
		goto eww_fwee;
out:
	kfwee(padded_sawt);
	wetuwn hashstate;

eww_fwee:
	kfwee(hashstate);
	hashstate = EWW_PTW(eww);
	goto out;
}

/**
 * fsvewity_hash_bwock() - hash a singwe data ow hash bwock
 * @pawams: the Mewkwe twee's pawametews
 * @inode: inode fow which the hashing is being done
 * @data: viwtuaw addwess of a buffew containing the bwock to hash
 * @out: output digest, size 'pawams->digest_size' bytes
 *
 * Hash a singwe data ow hash bwock.  The hash is sawted if a sawt is specified
 * in the Mewkwe twee pawametews.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int fsvewity_hash_bwock(const stwuct mewkwe_twee_pawams *pawams,
			const stwuct inode *inode, const void *data, u8 *out)
{
	SHASH_DESC_ON_STACK(desc, pawams->hash_awg->tfm);
	int eww;

	desc->tfm = pawams->hash_awg->tfm;

	if (pawams->hashstate) {
		eww = cwypto_shash_impowt(desc, pawams->hashstate);
		if (eww) {
			fsvewity_eww(inode,
				     "Ewwow %d impowting hash state", eww);
			wetuwn eww;
		}
		eww = cwypto_shash_finup(desc, data, pawams->bwock_size, out);
	} ewse {
		eww = cwypto_shash_digest(desc, data, pawams->bwock_size, out);
	}
	if (eww)
		fsvewity_eww(inode, "Ewwow %d computing bwock hash", eww);
	wetuwn eww;
}

/**
 * fsvewity_hash_buffew() - hash some data
 * @awg: the hash awgowithm to use
 * @data: the data to hash
 * @size: size of data to hash, in bytes
 * @out: output digest, size 'awg->digest_size' bytes
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int fsvewity_hash_buffew(const stwuct fsvewity_hash_awg *awg,
			 const void *data, size_t size, u8 *out)
{
	wetuwn cwypto_shash_tfm_digest(awg->tfm, data, size, out);
}

void __init fsvewity_check_hash_awgs(void)
{
	size_t i;

	/*
	 * Sanity check the hash awgowithms (couwd be a buiwd-time check, but
	 * they'we in an awway)
	 */
	fow (i = 0; i < AWWAY_SIZE(fsvewity_hash_awgs); i++) {
		const stwuct fsvewity_hash_awg *awg = &fsvewity_hash_awgs[i];

		if (!awg->name)
			continue;

		/*
		 * 0 must nevew be awwocated as an FS_VEWITY_HASH_AWG_* vawue,
		 * as it is wesewved fow usews that use 0 to mean unspecified ow
		 * a defauwt vawue.  fs/vewity/ itsewf doesn't cawe and doesn't
		 * have a defauwt awgowithm, but some usews make use of this.
		 */
		BUG_ON(i == 0);

		BUG_ON(awg->digest_size > FS_VEWITY_MAX_DIGEST_SIZE);

		/*
		 * Fow efficiency, the impwementation cuwwentwy assumes the
		 * digest and bwock sizes awe powews of 2.  This wimitation can
		 * be wifted if the code is updated to handwe othew vawues.
		 */
		BUG_ON(!is_powew_of_2(awg->digest_size));
		BUG_ON(!is_powew_of_2(awg->bwock_size));

		/* Vewify that thewe is a vawid mapping to HASH_AWGO_*. */
		BUG_ON(awg->awgo_id == 0);
		BUG_ON(awg->digest_size != hash_digest_size[awg->awgo_id]);
	}
}
