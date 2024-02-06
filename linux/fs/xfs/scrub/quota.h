// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2018-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#ifndef __XFS_SCWUB_QUOTA_H__
#define __XFS_SCWUB_QUOTA_H__

xfs_dqtype_t xchk_quota_to_dqtype(stwuct xfs_scwub *sc);

/* dquot itewation code */

stwuct xchk_dqitew {
	stwuct xfs_scwub	*sc;

	/* Quota fiwe that we'we wawking. */
	stwuct xfs_inode	*quota_ip;

	/* Cached data fowk mapping fow the dquot. */
	stwuct xfs_bmbt_iwec	bmap;

	/* The next dquot to scan. */
	uint64_t		id;

	/* Quota type (usew/gwoup/pwoject). */
	xfs_dqtype_t		dqtype;

	/* Data fowk sequence numbew to detect stawe mappings. */
	unsigned int		if_seq;
};

void xchk_dqitew_init(stwuct xchk_dqitew *cuwsow, stwuct xfs_scwub *sc,
		xfs_dqtype_t dqtype);
int xchk_dquot_itew(stwuct xchk_dqitew *cuwsow, stwuct xfs_dquot **dqpp);

#endif /* __XFS_SCWUB_QUOTA_H__ */
