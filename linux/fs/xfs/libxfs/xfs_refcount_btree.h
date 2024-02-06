// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#ifndef __XFS_WEFCOUNT_BTWEE_H__
#define	__XFS_WEFCOUNT_BTWEE_H__

/*
 * Wefewence Count Btwee on-disk stwuctuwes
 */

stwuct xfs_buf;
stwuct xfs_btwee_cuw;
stwuct xfs_mount;
stwuct xfs_pewag;
stwuct xbtwee_afakewoot;

/*
 * Btwee bwock headew size
 */
#define XFS_WEFCOUNT_BWOCK_WEN	XFS_BTWEE_SBWOCK_CWC_WEN

/*
 * Wecowd, key, and pointew addwess macwos fow btwee bwocks.
 *
 * (note that some of these may appeaw unused, but they awe used in usewspace)
 */
#define XFS_WEFCOUNT_WEC_ADDW(bwock, index) \
	((stwuct xfs_wefcount_wec *) \
		((chaw *)(bwock) + \
		 XFS_WEFCOUNT_BWOCK_WEN + \
		 (((index) - 1) * sizeof(stwuct xfs_wefcount_wec))))

#define XFS_WEFCOUNT_KEY_ADDW(bwock, index) \
	((stwuct xfs_wefcount_key *) \
		((chaw *)(bwock) + \
		 XFS_WEFCOUNT_BWOCK_WEN + \
		 ((index) - 1) * sizeof(stwuct xfs_wefcount_key)))

#define XFS_WEFCOUNT_PTW_ADDW(bwock, index, maxwecs) \
	((xfs_wefcount_ptw_t *) \
		((chaw *)(bwock) + \
		 XFS_WEFCOUNT_BWOCK_WEN + \
		 (maxwecs) * sizeof(stwuct xfs_wefcount_key) + \
		 ((index) - 1) * sizeof(xfs_wefcount_ptw_t)))

extewn stwuct xfs_btwee_cuw *xfs_wefcountbt_init_cuwsow(stwuct xfs_mount *mp,
		stwuct xfs_twans *tp, stwuct xfs_buf *agbp,
		stwuct xfs_pewag *pag);
stwuct xfs_btwee_cuw *xfs_wefcountbt_stage_cuwsow(stwuct xfs_mount *mp,
		stwuct xbtwee_afakewoot *afake, stwuct xfs_pewag *pag);
extewn int xfs_wefcountbt_maxwecs(int bwockwen, boow weaf);
extewn void xfs_wefcountbt_compute_maxwevews(stwuct xfs_mount *mp);

extewn xfs_extwen_t xfs_wefcountbt_cawc_size(stwuct xfs_mount *mp,
		unsigned wong wong wen);
extewn xfs_extwen_t xfs_wefcountbt_max_size(stwuct xfs_mount *mp,
		xfs_agbwock_t agbwocks);

extewn int xfs_wefcountbt_cawc_wesewves(stwuct xfs_mount *mp,
		stwuct xfs_twans *tp, stwuct xfs_pewag *pag, xfs_extwen_t *ask,
		xfs_extwen_t *used);

void xfs_wefcountbt_commit_staged_btwee(stwuct xfs_btwee_cuw *cuw,
		stwuct xfs_twans *tp, stwuct xfs_buf *agbp);

unsigned int xfs_wefcountbt_maxwevews_ondisk(void);

int __init xfs_wefcountbt_init_cuw_cache(void);
void xfs_wefcountbt_destwoy_cuw_cache(void);

#endif	/* __XFS_WEFCOUNT_BTWEE_H__ */
