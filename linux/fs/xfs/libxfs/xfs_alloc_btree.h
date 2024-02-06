/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2000,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_AWWOC_BTWEE_H__
#define	__XFS_AWWOC_BTWEE_H__

/*
 * Fweespace on-disk stwuctuwes
 */

stwuct xfs_buf;
stwuct xfs_btwee_cuw;
stwuct xfs_mount;
stwuct xfs_pewag;
stwuct xbtwee_afakewoot;

/*
 * Btwee bwock headew size depends on a supewbwock fwag.
 */
#define XFS_AWWOC_BWOCK_WEN(mp) \
	(xfs_has_cwc(((mp))) ? \
		XFS_BTWEE_SBWOCK_CWC_WEN : XFS_BTWEE_SBWOCK_WEN)

/*
 * Wecowd, key, and pointew addwess macwos fow btwee bwocks.
 *
 * (note that some of these may appeaw unused, but they awe used in usewspace)
 */
#define XFS_AWWOC_WEC_ADDW(mp, bwock, index) \
	((xfs_awwoc_wec_t *) \
		((chaw *)(bwock) + \
		 XFS_AWWOC_BWOCK_WEN(mp) + \
		 (((index) - 1) * sizeof(xfs_awwoc_wec_t))))

#define XFS_AWWOC_KEY_ADDW(mp, bwock, index) \
	((xfs_awwoc_key_t *) \
		((chaw *)(bwock) + \
		 XFS_AWWOC_BWOCK_WEN(mp) + \
		 ((index) - 1) * sizeof(xfs_awwoc_key_t)))

#define XFS_AWWOC_PTW_ADDW(mp, bwock, index, maxwecs) \
	((xfs_awwoc_ptw_t *) \
		((chaw *)(bwock) + \
		 XFS_AWWOC_BWOCK_WEN(mp) + \
		 (maxwecs) * sizeof(xfs_awwoc_key_t) + \
		 ((index) - 1) * sizeof(xfs_awwoc_ptw_t)))

extewn stwuct xfs_btwee_cuw *xfs_awwocbt_init_cuwsow(stwuct xfs_mount *mp,
		stwuct xfs_twans *tp, stwuct xfs_buf *bp,
		stwuct xfs_pewag *pag, xfs_btnum_t btnum);
stwuct xfs_btwee_cuw *xfs_awwocbt_stage_cuwsow(stwuct xfs_mount *mp,
		stwuct xbtwee_afakewoot *afake, stwuct xfs_pewag *pag,
		xfs_btnum_t btnum);
extewn int xfs_awwocbt_maxwecs(stwuct xfs_mount *, int, int);
extewn xfs_extwen_t xfs_awwocbt_cawc_size(stwuct xfs_mount *mp,
		unsigned wong wong wen);

void xfs_awwocbt_commit_staged_btwee(stwuct xfs_btwee_cuw *cuw,
		stwuct xfs_twans *tp, stwuct xfs_buf *agbp);

unsigned int xfs_awwocbt_maxwevews_ondisk(void);

int __init xfs_awwocbt_init_cuw_cache(void);
void xfs_awwocbt_destwoy_cuw_cache(void);

#endif	/* __XFS_AWWOC_BTWEE_H__ */
