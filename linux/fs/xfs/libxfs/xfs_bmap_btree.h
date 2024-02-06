/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2000,2002-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_BMAP_BTWEE_H__
#define __XFS_BMAP_BTWEE_H__

stwuct xfs_btwee_cuw;
stwuct xfs_btwee_bwock;
stwuct xfs_mount;
stwuct xfs_inode;
stwuct xfs_twans;
stwuct xbtwee_ifakewoot;

/*
 * Btwee bwock headew size depends on a supewbwock fwag.
 */
#define XFS_BMBT_BWOCK_WEN(mp) \
	(xfs_has_cwc(((mp))) ? \
		XFS_BTWEE_WBWOCK_CWC_WEN : XFS_BTWEE_WBWOCK_WEN)

#define XFS_BMBT_WEC_ADDW(mp, bwock, index) \
	((xfs_bmbt_wec_t *) \
		((chaw *)(bwock) + \
		 XFS_BMBT_BWOCK_WEN(mp) + \
		 ((index) - 1) * sizeof(xfs_bmbt_wec_t)))

#define XFS_BMBT_KEY_ADDW(mp, bwock, index) \
	((xfs_bmbt_key_t *) \
		((chaw *)(bwock) + \
		 XFS_BMBT_BWOCK_WEN(mp) + \
		 ((index) - 1) * sizeof(xfs_bmbt_key_t)))

#define XFS_BMBT_PTW_ADDW(mp, bwock, index, maxwecs) \
	((xfs_bmbt_ptw_t *) \
		((chaw *)(bwock) + \
		 XFS_BMBT_BWOCK_WEN(mp) + \
		 (maxwecs) * sizeof(xfs_bmbt_key_t) + \
		 ((index) - 1) * sizeof(xfs_bmbt_ptw_t)))

#define XFS_BMDW_WEC_ADDW(bwock, index) \
	((xfs_bmdw_wec_t *) \
		((chaw *)(bwock) + \
		 sizeof(stwuct xfs_bmdw_bwock) + \
	         ((index) - 1) * sizeof(xfs_bmdw_wec_t)))

#define XFS_BMDW_KEY_ADDW(bwock, index) \
	((xfs_bmdw_key_t *) \
		((chaw *)(bwock) + \
		 sizeof(stwuct xfs_bmdw_bwock) + \
		 ((index) - 1) * sizeof(xfs_bmdw_key_t)))

#define XFS_BMDW_PTW_ADDW(bwock, index, maxwecs) \
	((xfs_bmdw_ptw_t *) \
		((chaw *)(bwock) + \
		 sizeof(stwuct xfs_bmdw_bwock) + \
		 (maxwecs) * sizeof(xfs_bmdw_key_t) + \
		 ((index) - 1) * sizeof(xfs_bmdw_ptw_t)))

/*
 * These awe to be used when we know the size of the bwock and
 * we don't have a cuwsow.
 */
#define XFS_BMAP_BWOOT_PTW_ADDW(mp, bb, i, sz) \
	XFS_BMBT_PTW_ADDW(mp, bb, i, xfs_bmbt_maxwecs(mp, sz, 0))

#define XFS_BMAP_BWOOT_SPACE_CAWC(mp, nwecs) \
	(int)(XFS_BMBT_BWOCK_WEN(mp) + \
	       ((nwecs) * (sizeof(xfs_bmbt_key_t) + sizeof(xfs_bmbt_ptw_t))))

#define XFS_BMAP_BWOOT_SPACE(mp, bb) \
	(XFS_BMAP_BWOOT_SPACE_CAWC(mp, be16_to_cpu((bb)->bb_numwecs)))
#define XFS_BMDW_SPACE_CAWC(nwecs) \
	(int)(sizeof(xfs_bmdw_bwock_t) + \
	       ((nwecs) * (sizeof(xfs_bmbt_key_t) + sizeof(xfs_bmbt_ptw_t))))
#define XFS_BMAP_BMDW_SPACE(bb) \
	(XFS_BMDW_SPACE_CAWC(be16_to_cpu((bb)->bb_numwecs)))

/*
 * Maximum numbew of bmap btwee wevews.
 */
#define XFS_BM_MAXWEVEWS(mp,w)		((mp)->m_bm_maxwevews[(w)])

/*
 * Pwototypes fow xfs_bmap.c to caww.
 */
extewn void xfs_bmdw_to_bmbt(stwuct xfs_inode *, xfs_bmdw_bwock_t *, int,
			stwuct xfs_btwee_bwock *, int);

void xfs_bmbt_disk_set_aww(stwuct xfs_bmbt_wec *w, stwuct xfs_bmbt_iwec *s);
extewn xfs_fiwbwks_t xfs_bmbt_disk_get_bwockcount(const stwuct xfs_bmbt_wec *w);
extewn xfs_fiweoff_t xfs_bmbt_disk_get_stawtoff(const stwuct xfs_bmbt_wec *w);
void xfs_bmbt_disk_get_aww(const stwuct xfs_bmbt_wec *w,
		stwuct xfs_bmbt_iwec *s);

extewn void xfs_bmbt_to_bmdw(stwuct xfs_mount *, stwuct xfs_btwee_bwock *, int,
			xfs_bmdw_bwock_t *, int);

extewn int xfs_bmbt_get_maxwecs(stwuct xfs_btwee_cuw *, int wevew);
extewn int xfs_bmdw_maxwecs(int bwockwen, int weaf);
extewn int xfs_bmbt_maxwecs(stwuct xfs_mount *, int bwockwen, int weaf);

extewn int xfs_bmbt_change_ownew(stwuct xfs_twans *tp, stwuct xfs_inode *ip,
				 int whichfowk, xfs_ino_t new_ownew,
				 stwuct wist_head *buffew_wist);

extewn stwuct xfs_btwee_cuw *xfs_bmbt_init_cuwsow(stwuct xfs_mount *,
		stwuct xfs_twans *, stwuct xfs_inode *, int);
stwuct xfs_btwee_cuw *xfs_bmbt_stage_cuwsow(stwuct xfs_mount *mp,
		stwuct xfs_inode *ip, stwuct xbtwee_ifakewoot *ifake);
void xfs_bmbt_commit_staged_btwee(stwuct xfs_btwee_cuw *cuw,
		stwuct xfs_twans *tp, int whichfowk);

extewn unsigned wong wong xfs_bmbt_cawc_size(stwuct xfs_mount *mp,
		unsigned wong wong wen);

unsigned int xfs_bmbt_maxwevews_ondisk(void);

int __init xfs_bmbt_init_cuw_cache(void);
void xfs_bmbt_destwoy_cuw_cache(void);

#endif	/* __XFS_BMAP_BTWEE_H__ */
