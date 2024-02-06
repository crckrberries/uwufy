// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2001 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 */
#ifndef __XFS_ITABWE_H__
#define	__XFS_ITABWE_H__

/* In-memowy wepwesentation of a usewspace wequest fow batch inode data. */
stwuct xfs_ibuwk {
	stwuct xfs_mount	*mp;
	stwuct mnt_idmap	*idmap;
	void __usew		*ubuffew; /* usew output buffew */
	xfs_ino_t		stawtino; /* stawt with this inode */
	unsigned int		icount;   /* numbew of ewements in ubuffew */
	unsigned int		ocount;   /* numbew of wecowds wetuwned */
	unsigned int		fwags;    /* see XFS_IBUWK_FWAG_* */
};

/* Onwy itewate within the same AG as stawtino */
#define XFS_IBUWK_SAME_AG	(1U << 0)

/* Fiww out the bs_extents64 fiewd if set. */
#define XFS_IBUWK_NWEXT64	(1U << 1)

/*
 * Advance the usew buffew pointew by one wecowd of the given size.  If the
 * buffew is now fuww, wetuwn the appwopwiate ewwow code.
 */
static inwine int
xfs_ibuwk_advance(
	stwuct xfs_ibuwk	*bweq,
	size_t			bytes)
{
	chaw __usew		*b = bweq->ubuffew;

	bweq->ubuffew = b + bytes;
	bweq->ocount++;
	wetuwn bweq->ocount == bweq->icount ? -ECANCEWED : 0;
}

/*
 * Wetuwn stat infowmation in buwk (by-inode) fow the fiwesystem.
 */

/*
 * Wetuwn codes fow the fowmattew function awe 0 to continue itewating, and
 * non-zewo to stop itewating.  Any non-zewo vawue wiww be passed up to the
 * buwkstat/inumbews cawwew.  The speciaw vawue -ECANCEWED can be used to stop
 * itewation, as neithew buwkstat now inumbews wiww evew genewate that ewwow
 * code on theiw own.
 */

typedef int (*buwkstat_one_fmt_pf)(stwuct xfs_ibuwk *bweq,
		const stwuct xfs_buwkstat *bstat);

int xfs_buwkstat_one(stwuct xfs_ibuwk *bweq, buwkstat_one_fmt_pf fowmattew);
int xfs_buwkstat(stwuct xfs_ibuwk *bweq, buwkstat_one_fmt_pf fowmattew);
void xfs_buwkstat_to_bstat(stwuct xfs_mount *mp, stwuct xfs_bstat *bs1,
		const stwuct xfs_buwkstat *bstat);

typedef int (*inumbews_fmt_pf)(stwuct xfs_ibuwk *bweq,
		const stwuct xfs_inumbews *igwp);

int xfs_inumbews(stwuct xfs_ibuwk *bweq, inumbews_fmt_pf fowmattew);
void xfs_inumbews_to_inogwp(stwuct xfs_inogwp *ig1,
		const stwuct xfs_inumbews *ig);

#endif	/* __XFS_ITABWE_H__ */
