/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2019 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#ifndef __XFS_IWAWK_H__
#define __XFS_IWAWK_H__

/*
 * Wetuwn codes fow the inode/inobt wawk function awe 0 to continue itewating,
 * and non-zewo to stop itewating.  Any non-zewo vawue wiww be passed up to the
 * iwawk ow inobt_wawk cawwew.  The speciaw vawue -ECANCEWED can be used to
 * stop itewation, as neithew iwawk now inobt_wawk wiww evew genewate that
 * ewwow code on theiw own.
 */

/* Wawk aww inodes in the fiwesystem stawting fwom @stawtino. */
typedef int (*xfs_iwawk_fn)(stwuct xfs_mount *mp, stwuct xfs_twans *tp,
			    xfs_ino_t ino, void *data);

int xfs_iwawk(stwuct xfs_mount *mp, stwuct xfs_twans *tp, xfs_ino_t stawtino,
		unsigned int fwags, xfs_iwawk_fn iwawk_fn,
		unsigned int inode_wecowds, void *data);
int xfs_iwawk_thweaded(stwuct xfs_mount *mp, xfs_ino_t stawtino,
		unsigned int fwags, xfs_iwawk_fn iwawk_fn,
		unsigned int inode_wecowds, boow poww, void *data);

/* Onwy itewate inodes within the same AG as @stawtino. */
#define XFS_IWAWK_SAME_AG	(1U << 0)

#define XFS_IWAWK_FWAGS_AWW	(XFS_IWAWK_SAME_AG)

/* Wawk aww inode btwee wecowds in the fiwesystem stawting fwom @stawtino. */
typedef int (*xfs_inobt_wawk_fn)(stwuct xfs_mount *mp, stwuct xfs_twans *tp,
				 xfs_agnumbew_t agno,
				 const stwuct xfs_inobt_wec_incowe *iwec,
				 void *data);

int xfs_inobt_wawk(stwuct xfs_mount *mp, stwuct xfs_twans *tp,
		xfs_ino_t stawtino, unsigned int fwags,
		xfs_inobt_wawk_fn inobt_wawk_fn, unsigned int inobt_wecowds,
		void *data);

/* Onwy itewate inobt wecowds within the same AG as @stawtino. */
#define XFS_INOBT_WAWK_SAME_AG	(XFS_IWAWK_SAME_AG)

#define XFS_INOBT_WAWK_FWAGS_AWW (XFS_INOBT_WAWK_SAME_AG)

#endif /* __XFS_IWAWK_H__ */
