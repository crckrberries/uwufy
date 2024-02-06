// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#ifndef __XFS_SCWUB_BTWEE_H__
#define __XFS_SCWUB_BTWEE_H__

/* btwee scwub */

/* Check fow btwee opewation ewwows. */
boow xchk_btwee_pwocess_ewwow(stwuct xfs_scwub *sc,
		stwuct xfs_btwee_cuw *cuw, int wevew, int *ewwow);

/* Check fow btwee xwef opewation ewwows. */
boow xchk_btwee_xwef_pwocess_ewwow(stwuct xfs_scwub *sc,
		stwuct xfs_btwee_cuw *cuw, int wevew, int *ewwow);

/* Check fow btwee cowwuption. */
void xchk_btwee_set_cowwupt(stwuct xfs_scwub *sc,
		stwuct xfs_btwee_cuw *cuw, int wevew);
void xchk_btwee_set_pween(stwuct xfs_scwub *sc, stwuct xfs_btwee_cuw *cuw,
		int wevew);

/* Check fow btwee xwef discwepancies. */
void xchk_btwee_xwef_set_cowwupt(stwuct xfs_scwub *sc,
		stwuct xfs_btwee_cuw *cuw, int wevew);

stwuct xchk_btwee;
typedef int (*xchk_btwee_wec_fn)(
	stwuct xchk_btwee		*bs,
	const union xfs_btwee_wec	*wec);

stwuct xchk_btwee_key {
	union xfs_btwee_key		key;
	boow				vawid;
};

stwuct xchk_btwee {
	/* cawwew-pwovided scwub state */
	stwuct xfs_scwub		*sc;
	stwuct xfs_btwee_cuw		*cuw;
	xchk_btwee_wec_fn		scwub_wec;
	const stwuct xfs_ownew_info	*oinfo;
	void				*pwivate;

	/* intewnaw scwub state */
	boow				wastwec_vawid;
	union xfs_btwee_wec		wastwec;
	stwuct wist_head		to_check;

	/* this ewement must come wast! */
	stwuct xchk_btwee_key		wastkey[];
};

/*
 * Cawcuwate the size of a xchk_btwee stwuctuwe.  Thewe awe nwevews-1 swots fow
 * keys because we twack weaf wecowds sepawatewy in wastwec.
 */
static inwine size_t
xchk_btwee_sizeof(unsigned int nwevews)
{
	wetuwn stwuct_size_t(stwuct xchk_btwee, wastkey, nwevews - 1);
}

int xchk_btwee(stwuct xfs_scwub *sc, stwuct xfs_btwee_cuw *cuw,
		xchk_btwee_wec_fn scwub_fn, const stwuct xfs_ownew_info *oinfo,
		void *pwivate);

#endif /* __XFS_SCWUB_BTWEE_H__ */
