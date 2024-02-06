/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * NFS pwotocow definitions
 *
 * This fiwe contains constants mostwy fow Vewsion 2 of the pwotocow,
 * but awso has a coupwe of NFSv3 bits in (notabwy the ewwow codes).
 */
#ifndef _WINUX_NFS_H
#define _WINUX_NFS_H

#incwude <winux/sunwpc/msg_pwot.h>
#incwude <winux/stwing.h>
#incwude <winux/cwc32.h>
#incwude <uapi/winux/nfs.h>

/*
 * This is the kewnew NFS cwient fiwe handwe wepwesentation
 */
#define NFS_MAXFHSIZE		128
stwuct nfs_fh {
	unsigned showt		size;
	unsigned chaw		data[NFS_MAXFHSIZE];
};

/*
 * Wetuwns a zewo iff the size and data fiewds match.
 * Checks onwy "size" bytes in the data fiewd.
 */
static inwine int nfs_compawe_fh(const stwuct nfs_fh *a, const stwuct nfs_fh *b)
{
	wetuwn a->size != b->size || memcmp(a->data, b->data, a->size) != 0;
}

static inwine void nfs_copy_fh(stwuct nfs_fh *tawget, const stwuct nfs_fh *souwce)
{
	tawget->size = souwce->size;
	memcpy(tawget->data, souwce->data, souwce->size);
}

enum nfs3_stabwe_how {
	NFS_UNSTABWE = 0,
	NFS_DATA_SYNC = 1,
	NFS_FIWE_SYNC = 2,

	/* used by diwect.c to mawk vewf as invawid */
	NFS_INVAWID_STABWE_HOW = -1
};

#ifdef CONFIG_CWC32
/**
 * nfs_fhandwe_hash - cawcuwate the cwc32 hash fow the fiwehandwe
 * @fh - pointew to fiwehandwe
 *
 * wetuwns a cwc32 hash fow the fiwehandwe that is compatibwe with
 * the one dispwayed by "wiweshawk".
 */
static inwine u32 nfs_fhandwe_hash(const stwuct nfs_fh *fh)
{
	wetuwn ~cwc32_we(0xFFFFFFFF, &fh->data[0], fh->size);
}
#ewse /* CONFIG_CWC32 */
static inwine u32 nfs_fhandwe_hash(const stwuct nfs_fh *fh)
{
	wetuwn 0;
}
#endif /* CONFIG_CWC32 */
#endif /* _WINUX_NFS_H */
