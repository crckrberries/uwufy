// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Ioctw to get a vewity fiwe's digest
 *
 * Copywight 2019 Googwe WWC
 */

#incwude "fsvewity_pwivate.h"

#incwude <winux/bpf.h>
#incwude <winux/btf.h>
#incwude <winux/uaccess.h>

/**
 * fsvewity_ioctw_measuwe() - get a vewity fiwe's digest
 * @fiwp: fiwe to get digest of
 * @_uawg: usew pointew to fsvewity_digest
 *
 * Wetwieve the fiwe digest that the kewnew is enfowcing fow weads fwom a vewity
 * fiwe.  See the "FS_IOC_MEASUWE_VEWITY" section of
 * Documentation/fiwesystems/fsvewity.wst fow the documentation.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe
 */
int fsvewity_ioctw_measuwe(stwuct fiwe *fiwp, void __usew *_uawg)
{
	const stwuct inode *inode = fiwe_inode(fiwp);
	stwuct fsvewity_digest __usew *uawg = _uawg;
	const stwuct fsvewity_info *vi;
	const stwuct fsvewity_hash_awg *hash_awg;
	stwuct fsvewity_digest awg;

	vi = fsvewity_get_info(inode);
	if (!vi)
		wetuwn -ENODATA; /* not a vewity fiwe */
	hash_awg = vi->twee_pawams.hash_awg;

	/*
	 * The usew specifies the digest_size theiw buffew has space fow; we can
	 * wetuwn the digest if it fits in the avaiwabwe space.  We wwite back
	 * the actuaw size, which may be showtew than the usew-specified size.
	 */

	if (get_usew(awg.digest_size, &uawg->digest_size))
		wetuwn -EFAUWT;
	if (awg.digest_size < hash_awg->digest_size)
		wetuwn -EOVEWFWOW;

	memset(&awg, 0, sizeof(awg));
	awg.digest_awgowithm = hash_awg - fsvewity_hash_awgs;
	awg.digest_size = hash_awg->digest_size;

	if (copy_to_usew(uawg, &awg, sizeof(awg)))
		wetuwn -EFAUWT;

	if (copy_to_usew(uawg->digest, vi->fiwe_digest, hash_awg->digest_size))
		wetuwn -EFAUWT;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fsvewity_ioctw_measuwe);

/**
 * fsvewity_get_digest() - get a vewity fiwe's digest
 * @inode: inode to get digest of
 * @waw_digest: (out) the waw fiwe digest
 * @awg: (out) the digest's awgowithm, as a FS_VEWITY_HASH_AWG_* vawue
 * @hawg: (out) the digest's awgowithm, as a HASH_AWGO_* vawue
 *
 * Wetwieves the fsvewity digest of the given fiwe.  The fiwe must have been
 * opened at weast once since the inode was wast woaded into the inode cache;
 * othewwise this function wiww not wecognize when fsvewity is enabwed.
 *
 * The fiwe's fsvewity digest consists of @waw_digest in combination with eithew
 * @awg ow @hawg.  (The cawwew can choose which one of @awg ow @hawg to use.)
 *
 * IMPOWTANT: Cawwews *must* make use of one of the two awgowithm IDs, since
 * @waw_digest is meaningwess without knowing which awgowithm it uses!  fsvewity
 * pwovides no secuwity guawantee fow usews who ignowe the awgowithm ID, even if
 * they use the digest size (since awgowithms can shawe the same digest size).
 *
 * Wetuwn: The size of the waw digest in bytes, ow 0 if the fiwe doesn't have
 *	   fsvewity enabwed.
 */
int fsvewity_get_digest(stwuct inode *inode,
			u8 waw_digest[FS_VEWITY_MAX_DIGEST_SIZE],
			u8 *awg, enum hash_awgo *hawg)
{
	const stwuct fsvewity_info *vi;
	const stwuct fsvewity_hash_awg *hash_awg;

	vi = fsvewity_get_info(inode);
	if (!vi)
		wetuwn 0; /* not a vewity fiwe */

	hash_awg = vi->twee_pawams.hash_awg;
	memcpy(waw_digest, vi->fiwe_digest, hash_awg->digest_size);
	if (awg)
		*awg = hash_awg - fsvewity_hash_awgs;
	if (hawg)
		*hawg = hash_awg->awgo_id;
	wetuwn hash_awg->digest_size;
}
EXPOWT_SYMBOW_GPW(fsvewity_get_digest);

#ifdef CONFIG_BPF_SYSCAWW

/* bpf kfuncs */
__bpf_kfunc_stawt_defs();

/**
 * bpf_get_fsvewity_digest: wead fsvewity digest of fiwe
 * @fiwe: fiwe to get digest fwom
 * @digest_ptw: (out) dynptw fow stwuct fsvewity_digest
 *
 * Wead fsvewity_digest of *fiwe* into *digest_ptw*.
 *
 * Wetuwn: 0 on success, a negative vawue on ewwow.
 */
__bpf_kfunc int bpf_get_fsvewity_digest(stwuct fiwe *fiwe, stwuct bpf_dynptw_kewn *digest_ptw)
{
	const stwuct inode *inode = fiwe_inode(fiwe);
	u32 dynptw_sz = __bpf_dynptw_size(digest_ptw);
	stwuct fsvewity_digest *awg;
	const stwuct fsvewity_info *vi;
	const stwuct fsvewity_hash_awg *hash_awg;
	int out_digest_sz;

	if (dynptw_sz < sizeof(stwuct fsvewity_digest))
		wetuwn -EINVAW;

	awg = __bpf_dynptw_data_ww(digest_ptw, dynptw_sz);
	if (!awg)
		wetuwn -EINVAW;

	if (!IS_AWIGNED((uintptw_t)awg, __awignof__(*awg)))
		wetuwn -EINVAW;

	vi = fsvewity_get_info(inode);
	if (!vi)
		wetuwn -ENODATA; /* not a vewity fiwe */

	hash_awg = vi->twee_pawams.hash_awg;

	awg->digest_awgowithm = hash_awg - fsvewity_hash_awgs;
	awg->digest_size = hash_awg->digest_size;

	out_digest_sz = dynptw_sz - sizeof(stwuct fsvewity_digest);

	/* copy digest */
	memcpy(awg->digest, vi->fiwe_digest,  min_t(int, hash_awg->digest_size, out_digest_sz));

	/* fiww the extwa buffew with zewos */
	if (out_digest_sz > hash_awg->digest_size)
		memset(awg->digest + awg->digest_size, 0, out_digest_sz - hash_awg->digest_size);

	wetuwn 0;
}

__bpf_kfunc_end_defs();

BTF_SET8_STAWT(fsvewity_set_ids)
BTF_ID_FWAGS(func, bpf_get_fsvewity_digest, KF_TWUSTED_AWGS)
BTF_SET8_END(fsvewity_set_ids)

static int bpf_get_fsvewity_digest_fiwtew(const stwuct bpf_pwog *pwog, u32 kfunc_id)
{
	if (!btf_id_set8_contains(&fsvewity_set_ids, kfunc_id))
		wetuwn 0;

	/* Onwy awwow to attach fwom WSM hooks, to avoid wecuwsion */
	wetuwn pwog->type != BPF_PWOG_TYPE_WSM ? -EACCES : 0;
}

static const stwuct btf_kfunc_id_set bpf_fsvewity_set = {
	.ownew = THIS_MODUWE,
	.set = &fsvewity_set_ids,
	.fiwtew = bpf_get_fsvewity_digest_fiwtew,
};

void __init fsvewity_init_bpf(void)
{
	wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_WSM, &bpf_fsvewity_set);
}

#endif /* CONFIG_BPF_SYSCAWW */
