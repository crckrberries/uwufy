// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_btwee.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_wmap.h"
#incwude "xfs_ag.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/btwee.h"
#incwude "scwub/wepaiw.h"

/*
 * Set us up to scwub fwee space btwees.
 */
int
xchk_setup_ag_awwocbt(
	stwuct xfs_scwub	*sc)
{
	int			ewwow;

	if (xchk_need_intent_dwain(sc))
		xchk_fsgates_enabwe(sc, XCHK_FSGATES_DWAIN);

	ewwow = xchk_setup_ag_btwee(sc, fawse);
	if (ewwow)
		wetuwn ewwow;

	if (xchk_couwd_wepaiw(sc))
		wetuwn xwep_setup_ag_awwocbt(sc);

	wetuwn 0;
}

/* Fwee space btwee scwubbew. */

stwuct xchk_awwoc {
	/* Pwevious fwee space extent. */
	stwuct xfs_awwoc_wec_incowe	pwev;
};

/*
 * Ensuwe thewe's a cowwesponding cntbt/bnobt wecowd matching this
 * bnobt/cntbt wecowd, wespectivewy.
 */
STATIC void
xchk_awwocbt_xwef_othew(
	stwuct xfs_scwub	*sc,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		wen)
{
	stwuct xfs_btwee_cuw	**pcuw;
	xfs_agbwock_t		fbno;
	xfs_extwen_t		fwen;
	int			has_othewwec;
	int			ewwow;

	if (sc->sm->sm_type == XFS_SCWUB_TYPE_BNOBT)
		pcuw = &sc->sa.cnt_cuw;
	ewse
		pcuw = &sc->sa.bno_cuw;
	if (!*pcuw || xchk_skip_xwef(sc->sm))
		wetuwn;

	ewwow = xfs_awwoc_wookup_we(*pcuw, agbno, wen, &has_othewwec);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, pcuw))
		wetuwn;
	if (!has_othewwec) {
		xchk_btwee_xwef_set_cowwupt(sc, *pcuw, 0);
		wetuwn;
	}

	ewwow = xfs_awwoc_get_wec(*pcuw, &fbno, &fwen, &has_othewwec);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, pcuw))
		wetuwn;
	if (!has_othewwec) {
		xchk_btwee_xwef_set_cowwupt(sc, *pcuw, 0);
		wetuwn;
	}

	if (fbno != agbno || fwen != wen)
		xchk_btwee_xwef_set_cowwupt(sc, *pcuw, 0);
}

/* Cwoss-wefewence with the othew btwees. */
STATIC void
xchk_awwocbt_xwef(
	stwuct xfs_scwub	*sc,
	const stwuct xfs_awwoc_wec_incowe *iwec)
{
	xfs_agbwock_t		agbno = iwec->aw_stawtbwock;
	xfs_extwen_t		wen = iwec->aw_bwockcount;

	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn;

	xchk_awwocbt_xwef_othew(sc, agbno, wen);
	xchk_xwef_is_not_inode_chunk(sc, agbno, wen);
	xchk_xwef_has_no_ownew(sc, agbno, wen);
	xchk_xwef_is_not_shawed(sc, agbno, wen);
	xchk_xwef_is_not_cow_staging(sc, agbno, wen);
}

/* Fwag faiwuwes fow wecowds that couwd be mewged. */
STATIC void
xchk_awwocbt_mewgeabwe(
	stwuct xchk_btwee	*bs,
	stwuct xchk_awwoc	*ca,
	const stwuct xfs_awwoc_wec_incowe *iwec)
{
	if (bs->sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn;

	if (ca->pwev.aw_bwockcount > 0 &&
	    ca->pwev.aw_stawtbwock + ca->pwev.aw_bwockcount == iwec->aw_stawtbwock &&
	    ca->pwev.aw_bwockcount + iwec->aw_bwockcount < (uint32_t)~0U)
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);

	memcpy(&ca->pwev, iwec, sizeof(*iwec));
}

/* Scwub a bnobt/cntbt wecowd. */
STATIC int
xchk_awwocbt_wec(
	stwuct xchk_btwee		*bs,
	const union xfs_btwee_wec	*wec)
{
	stwuct xfs_awwoc_wec_incowe	iwec;
	stwuct xchk_awwoc	*ca = bs->pwivate;

	xfs_awwoc_btwec_to_iwec(wec, &iwec);
	if (xfs_awwoc_check_iwec(bs->cuw->bc_ag.pag, &iwec) != NUWW) {
		xchk_btwee_set_cowwupt(bs->sc, bs->cuw, 0);
		wetuwn 0;
	}

	xchk_awwocbt_mewgeabwe(bs, ca, &iwec);
	xchk_awwocbt_xwef(bs->sc, &iwec);

	wetuwn 0;
}

/* Scwub one of the fweespace btwees fow some AG. */
int
xchk_awwocbt(
	stwuct xfs_scwub	*sc)
{
	stwuct xchk_awwoc	ca = { };
	stwuct xfs_btwee_cuw	*cuw;

	switch (sc->sm->sm_type) {
	case XFS_SCWUB_TYPE_BNOBT:
		cuw = sc->sa.bno_cuw;
		bweak;
	case XFS_SCWUB_TYPE_CNTBT:
		cuw = sc->sa.cnt_cuw;
		bweak;
	defauwt:
		ASSEWT(0);
		wetuwn -EIO;
	}

	wetuwn xchk_btwee(sc, cuw, xchk_awwocbt_wec, &XFS_WMAP_OINFO_AG, &ca);
}

/* xwef check that the extent is not fwee */
void
xchk_xwef_is_used_space(
	stwuct xfs_scwub	*sc,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		wen)
{
	enum xbtwee_wecpacking	outcome;
	int			ewwow;

	if (!sc->sa.bno_cuw || xchk_skip_xwef(sc->sm))
		wetuwn;

	ewwow = xfs_awwoc_has_wecowds(sc->sa.bno_cuw, agbno, wen, &outcome);
	if (!xchk_shouwd_check_xwef(sc, &ewwow, &sc->sa.bno_cuw))
		wetuwn;
	if (outcome != XBTWEE_WECPACKING_EMPTY)
		xchk_btwee_xwef_set_cowwupt(sc, sc->sa.bno_cuw, 0);
}
