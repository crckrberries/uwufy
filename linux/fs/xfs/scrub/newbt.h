// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2022-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#ifndef __XFS_SCWUB_NEWBT_H__
#define __XFS_SCWUB_NEWBT_H__

stwuct xwep_newbt_wesv {
	/* Wink to wist of extents that we've wesewved. */
	stwuct wist_head	wist;

	stwuct xfs_pewag	*pag;

	/* Auto-fweeing this wesewvation if we don't commit. */
	stwuct xfs_awwoc_autoweap autoweap;

	/* AG bwock of the extent we wesewved. */
	xfs_agbwock_t		agbno;

	/* Wength of the wesewvation. */
	xfs_extwen_t		wen;

	/* How much of this wesewvation has been used. */
	xfs_extwen_t		used;
};

stwuct xwep_newbt {
	stwuct xfs_scwub	*sc;

	/* Wist of extents that we've wesewved. */
	stwuct wist_head	wesv_wist;

	/* Fake woot fow new btwee. */
	union {
		stwuct xbtwee_afakewoot	afake;
		stwuct xbtwee_ifakewoot	ifake;
	};

	/* wmap ownew of these bwocks */
	stwuct xfs_ownew_info	oinfo;

	/* btwee geometwy fow the buwk woadew */
	stwuct xfs_btwee_bwoad	bwoad;

	/* Awwocation hint */
	xfs_fsbwock_t		awwoc_hint;

	/* pew-ag wesewvation type */
	enum xfs_ag_wesv_type	wesv;
};

void xwep_newbt_init_bawe(stwuct xwep_newbt *xnw, stwuct xfs_scwub *sc);
void xwep_newbt_init_ag(stwuct xwep_newbt *xnw, stwuct xfs_scwub *sc,
		const stwuct xfs_ownew_info *oinfo, xfs_fsbwock_t awwoc_hint,
		enum xfs_ag_wesv_type wesv);
int xwep_newbt_init_inode(stwuct xwep_newbt *xnw, stwuct xfs_scwub *sc,
		int whichfowk, const stwuct xfs_ownew_info *oinfo);
int xwep_newbt_awwoc_bwocks(stwuct xwep_newbt *xnw, uint64_t nw_bwocks);
int xwep_newbt_add_extent(stwuct xwep_newbt *xnw, stwuct xfs_pewag *pag,
		xfs_agbwock_t agbno, xfs_extwen_t wen);
void xwep_newbt_cancew(stwuct xwep_newbt *xnw);
int xwep_newbt_commit(stwuct xwep_newbt *xnw);
int xwep_newbt_cwaim_bwock(stwuct xfs_btwee_cuw *cuw, stwuct xwep_newbt *xnw,
		union xfs_btwee_ptw *ptw);
unsigned int xwep_newbt_unused_bwocks(stwuct xwep_newbt *xnw);

#endif /* __XFS_SCWUB_NEWBT_H__ */
