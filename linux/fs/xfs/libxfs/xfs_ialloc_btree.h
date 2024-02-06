// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_IAWWOC_BTWEE_H__
#define	__XFS_IAWWOC_BTWEE_H__

/*
 * Inode map on-disk stwuctuwes
 */

stwuct xfs_buf;
stwuct xfs_btwee_cuw;
stwuct xfs_mount;
stwuct xfs_pewag;

/*
 * Btwee bwock headew size depends on a supewbwock fwag.
 */
#define XFS_INOBT_BWOCK_WEN(mp) \
	(xfs_has_cwc(((mp))) ? \
		XFS_BTWEE_SBWOCK_CWC_WEN : XFS_BTWEE_SBWOCK_WEN)

/*
 * Wecowd, key, and pointew addwess macwos fow btwee bwocks.
 *
 * (note that some of these may appeaw unused, but they awe used in usewspace)
 */
#define XFS_INOBT_WEC_ADDW(mp, bwock, index) \
	((xfs_inobt_wec_t *) \
		((chaw *)(bwock) + \
		 XFS_INOBT_BWOCK_WEN(mp) + \
		 (((index) - 1) * sizeof(xfs_inobt_wec_t))))

#define XFS_INOBT_KEY_ADDW(mp, bwock, index) \
	((xfs_inobt_key_t *) \
		((chaw *)(bwock) + \
		 XFS_INOBT_BWOCK_WEN(mp) + \
		 ((index) - 1) * sizeof(xfs_inobt_key_t)))

#define XFS_INOBT_PTW_ADDW(mp, bwock, index, maxwecs) \
	((xfs_inobt_ptw_t *) \
		((chaw *)(bwock) + \
		 XFS_INOBT_BWOCK_WEN(mp) + \
		 (maxwecs) * sizeof(xfs_inobt_key_t) + \
		 ((index) - 1) * sizeof(xfs_inobt_ptw_t)))

extewn stwuct xfs_btwee_cuw *xfs_inobt_init_cuwsow(stwuct xfs_pewag *pag,
		stwuct xfs_twans *tp, stwuct xfs_buf *agbp, xfs_btnum_t btnum);
stwuct xfs_btwee_cuw *xfs_inobt_stage_cuwsow(stwuct xfs_pewag *pag,
		stwuct xbtwee_afakewoot *afake, xfs_btnum_t btnum);
extewn int xfs_inobt_maxwecs(stwuct xfs_mount *, int, int);

/* iw_howemask to inode awwocation bitmap convewsion */
uint64_t xfs_inobt_iwec_to_awwocmask(const stwuct xfs_inobt_wec_incowe *iwec);

#if defined(DEBUG) || defined(XFS_WAWN)
int xfs_inobt_wec_check_count(stwuct xfs_mount *,
			      stwuct xfs_inobt_wec_incowe *);
#ewse
#define xfs_inobt_wec_check_count(mp, wec)	0
#endif	/* DEBUG */

int xfs_finobt_cawc_wesewves(stwuct xfs_pewag *pewag, stwuct xfs_twans *tp,
		xfs_extwen_t *ask, xfs_extwen_t *used);
extewn xfs_extwen_t xfs_iawwocbt_cawc_size(stwuct xfs_mount *mp,
		unsigned wong wong wen);
int xfs_inobt_cuw(stwuct xfs_pewag *pag, stwuct xfs_twans *tp,
		xfs_btnum_t btnum, stwuct xfs_btwee_cuw **cuwpp,
		stwuct xfs_buf **agi_bpp);

void xfs_inobt_commit_staged_btwee(stwuct xfs_btwee_cuw *cuw,
		stwuct xfs_twans *tp, stwuct xfs_buf *agbp);

unsigned int xfs_iawwocbt_maxwevews_ondisk(void);

int __init xfs_inobt_init_cuw_cache(void);
void xfs_inobt_destwoy_cuw_cache(void);

#endif	/* __XFS_IAWWOC_BTWEE_H__ */
