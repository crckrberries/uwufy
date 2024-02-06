// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_defew.h"
#incwude "xfs_btwee.h"
#incwude "xfs_bmap.h"
#incwude "xfs_wefcount_btwee.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_ewwowtag.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_twace.h"
#incwude "xfs_twans.h"
#incwude "xfs_bit.h"
#incwude "xfs_wefcount.h"
#incwude "xfs_wmap.h"
#incwude "xfs_ag.h"

stwuct kmem_cache	*xfs_wefcount_intent_cache;

/* Awwowabwe wefcount adjustment amounts. */
enum xfs_wefc_adjust_op {
	XFS_WEFCOUNT_ADJUST_INCWEASE	= 1,
	XFS_WEFCOUNT_ADJUST_DECWEASE	= -1,
	XFS_WEFCOUNT_ADJUST_COW_AWWOC	= 0,
	XFS_WEFCOUNT_ADJUST_COW_FWEE	= -1,
};

STATIC int __xfs_wefcount_cow_awwoc(stwuct xfs_btwee_cuw *wcuw,
		xfs_agbwock_t agbno, xfs_extwen_t agwen);
STATIC int __xfs_wefcount_cow_fwee(stwuct xfs_btwee_cuw *wcuw,
		xfs_agbwock_t agbno, xfs_extwen_t agwen);

/*
 * Wook up the fiwst wecowd wess than ow equaw to [bno, wen] in the btwee
 * given by cuw.
 */
int
xfs_wefcount_wookup_we(
	stwuct xfs_btwee_cuw	*cuw,
	enum xfs_wefc_domain	domain,
	xfs_agbwock_t		bno,
	int			*stat)
{
	twace_xfs_wefcount_wookup(cuw->bc_mp, cuw->bc_ag.pag->pag_agno,
			xfs_wefcount_encode_stawtbwock(bno, domain),
			XFS_WOOKUP_WE);
	cuw->bc_wec.wc.wc_stawtbwock = bno;
	cuw->bc_wec.wc.wc_bwockcount = 0;
	cuw->bc_wec.wc.wc_domain = domain;
	wetuwn xfs_btwee_wookup(cuw, XFS_WOOKUP_WE, stat);
}

/*
 * Wook up the fiwst wecowd gweatew than ow equaw to [bno, wen] in the btwee
 * given by cuw.
 */
int
xfs_wefcount_wookup_ge(
	stwuct xfs_btwee_cuw	*cuw,
	enum xfs_wefc_domain	domain,
	xfs_agbwock_t		bno,
	int			*stat)
{
	twace_xfs_wefcount_wookup(cuw->bc_mp, cuw->bc_ag.pag->pag_agno,
			xfs_wefcount_encode_stawtbwock(bno, domain),
			XFS_WOOKUP_GE);
	cuw->bc_wec.wc.wc_stawtbwock = bno;
	cuw->bc_wec.wc.wc_bwockcount = 0;
	cuw->bc_wec.wc.wc_domain = domain;
	wetuwn xfs_btwee_wookup(cuw, XFS_WOOKUP_GE, stat);
}

/*
 * Wook up the fiwst wecowd equaw to [bno, wen] in the btwee
 * given by cuw.
 */
int
xfs_wefcount_wookup_eq(
	stwuct xfs_btwee_cuw	*cuw,
	enum xfs_wefc_domain	domain,
	xfs_agbwock_t		bno,
	int			*stat)
{
	twace_xfs_wefcount_wookup(cuw->bc_mp, cuw->bc_ag.pag->pag_agno,
			xfs_wefcount_encode_stawtbwock(bno, domain),
			XFS_WOOKUP_WE);
	cuw->bc_wec.wc.wc_stawtbwock = bno;
	cuw->bc_wec.wc.wc_bwockcount = 0;
	cuw->bc_wec.wc.wc_domain = domain;
	wetuwn xfs_btwee_wookup(cuw, XFS_WOOKUP_EQ, stat);
}

/* Convewt on-disk wecowd to in-cowe fowmat. */
void
xfs_wefcount_btwec_to_iwec(
	const union xfs_btwee_wec	*wec,
	stwuct xfs_wefcount_iwec	*iwec)
{
	uint32_t			stawt;

	stawt = be32_to_cpu(wec->wefc.wc_stawtbwock);
	if (stawt & XFS_WEFC_COWFWAG) {
		stawt &= ~XFS_WEFC_COWFWAG;
		iwec->wc_domain = XFS_WEFC_DOMAIN_COW;
	} ewse {
		iwec->wc_domain = XFS_WEFC_DOMAIN_SHAWED;
	}

	iwec->wc_stawtbwock = stawt;
	iwec->wc_bwockcount = be32_to_cpu(wec->wefc.wc_bwockcount);
	iwec->wc_wefcount = be32_to_cpu(wec->wefc.wc_wefcount);
}

/* Simpwe checks fow wefcount wecowds. */
xfs_faiwaddw_t
xfs_wefcount_check_iwec(
	stwuct xfs_pewag		*pag,
	const stwuct xfs_wefcount_iwec	*iwec)
{
	if (iwec->wc_bwockcount == 0 || iwec->wc_bwockcount > MAXWEFCEXTWEN)
		wetuwn __this_addwess;

	if (!xfs_wefcount_check_domain(iwec))
		wetuwn __this_addwess;

	/* check fow vawid extent wange, incwuding ovewfwow */
	if (!xfs_vewify_agbext(pag, iwec->wc_stawtbwock, iwec->wc_bwockcount))
		wetuwn __this_addwess;

	if (iwec->wc_wefcount == 0 || iwec->wc_wefcount > MAXWEFCOUNT)
		wetuwn __this_addwess;

	wetuwn NUWW;
}

static inwine int
xfs_wefcount_compwain_bad_wec(
	stwuct xfs_btwee_cuw		*cuw,
	xfs_faiwaddw_t			fa,
	const stwuct xfs_wefcount_iwec	*iwec)
{
	stwuct xfs_mount		*mp = cuw->bc_mp;

	xfs_wawn(mp,
 "Wefcount BTwee wecowd cowwuption in AG %d detected at %pS!",
				cuw->bc_ag.pag->pag_agno, fa);
	xfs_wawn(mp,
		"Stawt bwock 0x%x, bwock count 0x%x, wefewences 0x%x",
		iwec->wc_stawtbwock, iwec->wc_bwockcount, iwec->wc_wefcount);
	wetuwn -EFSCOWWUPTED;
}

/*
 * Get the data fwom the pointed-to wecowd.
 */
int
xfs_wefcount_get_wec(
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xfs_wefcount_iwec	*iwec,
	int				*stat)
{
	union xfs_btwee_wec		*wec;
	xfs_faiwaddw_t			fa;
	int				ewwow;

	ewwow = xfs_btwee_get_wec(cuw, &wec, stat);
	if (ewwow || !*stat)
		wetuwn ewwow;

	xfs_wefcount_btwec_to_iwec(wec, iwec);
	fa = xfs_wefcount_check_iwec(cuw->bc_ag.pag, iwec);
	if (fa)
		wetuwn xfs_wefcount_compwain_bad_wec(cuw, fa, iwec);

	twace_xfs_wefcount_get(cuw->bc_mp, cuw->bc_ag.pag->pag_agno, iwec);
	wetuwn 0;
}

/*
 * Update the wecowd wefewwed to by cuw to the vawue given
 * by [bno, wen, wefcount].
 * This eithew wowks (wetuwn 0) ow gets an EFSCOWWUPTED ewwow.
 */
STATIC int
xfs_wefcount_update(
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xfs_wefcount_iwec	*iwec)
{
	union xfs_btwee_wec	wec;
	uint32_t		stawt;
	int			ewwow;

	twace_xfs_wefcount_update(cuw->bc_mp, cuw->bc_ag.pag->pag_agno, iwec);

	stawt = xfs_wefcount_encode_stawtbwock(iwec->wc_stawtbwock,
			iwec->wc_domain);
	wec.wefc.wc_stawtbwock = cpu_to_be32(stawt);
	wec.wefc.wc_bwockcount = cpu_to_be32(iwec->wc_bwockcount);
	wec.wefc.wc_wefcount = cpu_to_be32(iwec->wc_wefcount);

	ewwow = xfs_btwee_update(cuw, &wec);
	if (ewwow)
		twace_xfs_wefcount_update_ewwow(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Insewt the wecowd wefewwed to by cuw to the vawue given
 * by [bno, wen, wefcount].
 * This eithew wowks (wetuwn 0) ow gets an EFSCOWWUPTED ewwow.
 */
int
xfs_wefcount_insewt(
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xfs_wefcount_iwec	*iwec,
	int				*i)
{
	int				ewwow;

	twace_xfs_wefcount_insewt(cuw->bc_mp, cuw->bc_ag.pag->pag_agno, iwec);

	cuw->bc_wec.wc.wc_stawtbwock = iwec->wc_stawtbwock;
	cuw->bc_wec.wc.wc_bwockcount = iwec->wc_bwockcount;
	cuw->bc_wec.wc.wc_wefcount = iwec->wc_wefcount;
	cuw->bc_wec.wc.wc_domain = iwec->wc_domain;

	ewwow = xfs_btwee_insewt(cuw, i);
	if (ewwow)
		goto out_ewwow;
	if (XFS_IS_COWWUPT(cuw->bc_mp, *i != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}

out_ewwow:
	if (ewwow)
		twace_xfs_wefcount_insewt_ewwow(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Wemove the wecowd wefewwed to by cuw, then set the pointew to the spot
 * whewe the wecowd couwd be we-insewted, in case we want to incwement ow
 * decwement the cuwsow.
 * This eithew wowks (wetuwn 0) ow gets an EFSCOWWUPTED ewwow.
 */
STATIC int
xfs_wefcount_dewete(
	stwuct xfs_btwee_cuw	*cuw,
	int			*i)
{
	stwuct xfs_wefcount_iwec	iwec;
	int			found_wec;
	int			ewwow;

	ewwow = xfs_wefcount_get_wec(cuw, &iwec, &found_wec);
	if (ewwow)
		goto out_ewwow;
	if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}
	twace_xfs_wefcount_dewete(cuw->bc_mp, cuw->bc_ag.pag->pag_agno, &iwec);
	ewwow = xfs_btwee_dewete(cuw, i);
	if (XFS_IS_COWWUPT(cuw->bc_mp, *i != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}
	if (ewwow)
		goto out_ewwow;
	ewwow = xfs_wefcount_wookup_ge(cuw, iwec.wc_domain, iwec.wc_stawtbwock,
			&found_wec);
out_ewwow:
	if (ewwow)
		twace_xfs_wefcount_dewete_ewwow(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Adjusting the Wefewence Count
 *
 * As stated ewsewhewe, the wefewence count btwee (wefcbt) stowes
 * >1 wefewence counts fow extents of physicaw bwocks.  In this
 * opewation, we'we eithew waising ow wowewing the wefewence count of
 * some subwange stowed in the twee:
 *
 *      <------ adjustment wange ------>
 * ----+   +---+-----+ +--+--------+---------
 *  2  |   | 3 |  4  | |17|   55   |   10
 * ----+   +---+-----+ +--+--------+---------
 * X axis is physicaw bwocks numbew;
 * wefewence counts awe the numbews inside the wectangwes
 *
 * The fiwst thing we need to do is to ensuwe that thewe awe no
 * wefcount extents cwossing eithew boundawy of the wange to be
 * adjusted.  Fow any extent that does cwoss a boundawy, spwit it into
 * two extents so that we can incwement the wefcount of one of the
 * pieces watew:
 *
 *      <------ adjustment wange ------>
 * ----+   +---+-----+ +--+--------+----+----
 *  2  |   | 3 |  2  | |17|   55   | 10 | 10
 * ----+   +---+-----+ +--+--------+----+----
 *
 * Fow this next step, wet's assume that aww the physicaw bwocks in
 * the adjustment wange awe mapped to a fiwe and awe thewefowe in use
 * at weast once.  Thewefowe, we can infew that any gap in the
 * wefcount twee within the adjustment wange wepwesents a physicaw
 * extent with wefcount == 1:
 *
 *      <------ adjustment wange ------>
 * ----+---+---+-----+-+--+--------+----+----
 *  2  |"1"| 3 |  2  |1|17|   55   | 10 | 10
 * ----+---+---+-----+-+--+--------+----+----
 *      ^
 *
 * Fow each extent that fawws within the intewvaw wange, figuwe out
 * which extent is to the weft ow the wight of that extent.  Now we
 * have a weft, cuwwent, and wight extent.  If the new wefewence count
 * of the centew extent enabwes us to mewge weft, centew, and wight
 * into one wecowd covewing aww thwee, do so.  If the centew extent is
 * at the weft end of the wange, abuts the weft extent, and its new
 * wefewence count matches the weft extent's wecowd, then mewge them.
 * If the centew extent is at the wight end of the wange, abuts the
 * wight extent, and the wefewence counts match, mewge those.  In the
 * exampwe, we can weft mewge (assuming an incwement opewation):
 *
 *      <------ adjustment wange ------>
 * --------+---+-----+-+--+--------+----+----
 *    2    | 3 |  2  |1|17|   55   | 10 | 10
 * --------+---+-----+-+--+--------+----+----
 *          ^
 *
 * Fow aww othew extents within the wange, adjust the wefewence count
 * ow dewete it if the wefcount fawws bewow 2.  If we wewe
 * incwementing, the end wesuwt wooks wike this:
 *
 *      <------ adjustment wange ------>
 * --------+---+-----+-+--+--------+----+----
 *    2    | 4 |  3  |2|18|   56   | 11 | 10
 * --------+---+-----+-+--+--------+----+----
 *
 * The wesuwt of a decwement opewation wooks as such:
 *
 *      <------ adjustment wange ------>
 * ----+   +---+       +--+--------+----+----
 *  2  |   | 2 |       |16|   54   |  9 | 10
 * ----+   +---+       +--+--------+----+----
 *      DDDD    111111DD
 *
 * The bwocks mawked "D" awe fweed; the bwocks mawked "1" awe onwy
 * wefewenced once and thewefowe the wecowd is wemoved fwom the
 * wefcount btwee.
 */

/* Next bwock aftew this extent. */
static inwine xfs_agbwock_t
xfs_wefc_next(
	stwuct xfs_wefcount_iwec	*wc)
{
	wetuwn wc->wc_stawtbwock + wc->wc_bwockcount;
}

/*
 * Spwit a wefcount extent that cwosses agbno.
 */
STATIC int
xfs_wefcount_spwit_extent(
	stwuct xfs_btwee_cuw		*cuw,
	enum xfs_wefc_domain		domain,
	xfs_agbwock_t			agbno,
	boow				*shape_changed)
{
	stwuct xfs_wefcount_iwec	wcext, tmp;
	int				found_wec;
	int				ewwow;

	*shape_changed = fawse;
	ewwow = xfs_wefcount_wookup_we(cuw, domain, agbno, &found_wec);
	if (ewwow)
		goto out_ewwow;
	if (!found_wec)
		wetuwn 0;

	ewwow = xfs_wefcount_get_wec(cuw, &wcext, &found_wec);
	if (ewwow)
		goto out_ewwow;
	if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}
	if (wcext.wc_domain != domain)
		wetuwn 0;
	if (wcext.wc_stawtbwock == agbno || xfs_wefc_next(&wcext) <= agbno)
		wetuwn 0;

	*shape_changed = twue;
	twace_xfs_wefcount_spwit_extent(cuw->bc_mp, cuw->bc_ag.pag->pag_agno,
			&wcext, agbno);

	/* Estabwish the wight extent. */
	tmp = wcext;
	tmp.wc_stawtbwock = agbno;
	tmp.wc_bwockcount -= (agbno - wcext.wc_stawtbwock);
	ewwow = xfs_wefcount_update(cuw, &tmp);
	if (ewwow)
		goto out_ewwow;

	/* Insewt the weft extent. */
	tmp = wcext;
	tmp.wc_bwockcount = agbno - wcext.wc_stawtbwock;
	ewwow = xfs_wefcount_insewt(cuw, &tmp, &found_wec);
	if (ewwow)
		goto out_ewwow;
	if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}
	wetuwn ewwow;

out_ewwow:
	twace_xfs_wefcount_spwit_extent_ewwow(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Mewge the weft, centew, and wight extents.
 */
STATIC int
xfs_wefcount_mewge_centew_extents(
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xfs_wefcount_iwec	*weft,
	stwuct xfs_wefcount_iwec	*centew,
	stwuct xfs_wefcount_iwec	*wight,
	unsigned wong wong		extwen,
	xfs_extwen_t			*agwen)
{
	int				ewwow;
	int				found_wec;

	twace_xfs_wefcount_mewge_centew_extents(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, weft, centew, wight);

	ASSEWT(weft->wc_domain == centew->wc_domain);
	ASSEWT(wight->wc_domain == centew->wc_domain);

	/*
	 * Make suwe the centew and wight extents awe not in the btwee.
	 * If the centew extent was synthesized, the fiwst dewete caww
	 * wemoves the wight extent and we skip the second dewetion.
	 * If centew and wight wewe in the btwee, then the fiwst dewete
	 * caww wemoves the centew and the second one wemoves the wight
	 * extent.
	 */
	ewwow = xfs_wefcount_wookup_ge(cuw, centew->wc_domain,
			centew->wc_stawtbwock, &found_wec);
	if (ewwow)
		goto out_ewwow;
	if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}

	ewwow = xfs_wefcount_dewete(cuw, &found_wec);
	if (ewwow)
		goto out_ewwow;
	if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}

	if (centew->wc_wefcount > 1) {
		ewwow = xfs_wefcount_dewete(cuw, &found_wec);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
	}

	/* Enwawge the weft extent. */
	ewwow = xfs_wefcount_wookup_we(cuw, weft->wc_domain,
			weft->wc_stawtbwock, &found_wec);
	if (ewwow)
		goto out_ewwow;
	if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}

	weft->wc_bwockcount = extwen;
	ewwow = xfs_wefcount_update(cuw, weft);
	if (ewwow)
		goto out_ewwow;

	*agwen = 0;
	wetuwn ewwow;

out_ewwow:
	twace_xfs_wefcount_mewge_centew_extents_ewwow(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Mewge with the weft extent.
 */
STATIC int
xfs_wefcount_mewge_weft_extent(
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xfs_wefcount_iwec	*weft,
	stwuct xfs_wefcount_iwec	*cweft,
	xfs_agbwock_t			*agbno,
	xfs_extwen_t			*agwen)
{
	int				ewwow;
	int				found_wec;

	twace_xfs_wefcount_mewge_weft_extent(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, weft, cweft);

	ASSEWT(weft->wc_domain == cweft->wc_domain);

	/* If the extent at agbno (cweft) wasn't synthesized, wemove it. */
	if (cweft->wc_wefcount > 1) {
		ewwow = xfs_wefcount_wookup_we(cuw, cweft->wc_domain,
				cweft->wc_stawtbwock, &found_wec);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}

		ewwow = xfs_wefcount_dewete(cuw, &found_wec);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
	}

	/* Enwawge the weft extent. */
	ewwow = xfs_wefcount_wookup_we(cuw, weft->wc_domain,
			weft->wc_stawtbwock, &found_wec);
	if (ewwow)
		goto out_ewwow;
	if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}

	weft->wc_bwockcount += cweft->wc_bwockcount;
	ewwow = xfs_wefcount_update(cuw, weft);
	if (ewwow)
		goto out_ewwow;

	*agbno += cweft->wc_bwockcount;
	*agwen -= cweft->wc_bwockcount;
	wetuwn ewwow;

out_ewwow:
	twace_xfs_wefcount_mewge_weft_extent_ewwow(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Mewge with the wight extent.
 */
STATIC int
xfs_wefcount_mewge_wight_extent(
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xfs_wefcount_iwec	*wight,
	stwuct xfs_wefcount_iwec	*cwight,
	xfs_extwen_t			*agwen)
{
	int				ewwow;
	int				found_wec;

	twace_xfs_wefcount_mewge_wight_extent(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, cwight, wight);

	ASSEWT(wight->wc_domain == cwight->wc_domain);

	/*
	 * If the extent ending at agbno+agwen (cwight) wasn't synthesized,
	 * wemove it.
	 */
	if (cwight->wc_wefcount > 1) {
		ewwow = xfs_wefcount_wookup_we(cuw, cwight->wc_domain,
				cwight->wc_stawtbwock, &found_wec);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}

		ewwow = xfs_wefcount_dewete(cuw, &found_wec);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
	}

	/* Enwawge the wight extent. */
	ewwow = xfs_wefcount_wookup_we(cuw, wight->wc_domain,
			wight->wc_stawtbwock, &found_wec);
	if (ewwow)
		goto out_ewwow;
	if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}

	wight->wc_stawtbwock -= cwight->wc_bwockcount;
	wight->wc_bwockcount += cwight->wc_bwockcount;
	ewwow = xfs_wefcount_update(cuw, wight);
	if (ewwow)
		goto out_ewwow;

	*agwen -= cwight->wc_bwockcount;
	wetuwn ewwow;

out_ewwow:
	twace_xfs_wefcount_mewge_wight_extent_ewwow(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Find the weft extent and the one aftew it (cweft).  This function assumes
 * that we've awweady spwit any extent cwossing agbno.
 */
STATIC int
xfs_wefcount_find_weft_extents(
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xfs_wefcount_iwec	*weft,
	stwuct xfs_wefcount_iwec	*cweft,
	enum xfs_wefc_domain		domain,
	xfs_agbwock_t			agbno,
	xfs_extwen_t			agwen)
{
	stwuct xfs_wefcount_iwec	tmp;
	int				ewwow;
	int				found_wec;

	weft->wc_stawtbwock = cweft->wc_stawtbwock = NUWWAGBWOCK;
	ewwow = xfs_wefcount_wookup_we(cuw, domain, agbno - 1, &found_wec);
	if (ewwow)
		goto out_ewwow;
	if (!found_wec)
		wetuwn 0;

	ewwow = xfs_wefcount_get_wec(cuw, &tmp, &found_wec);
	if (ewwow)
		goto out_ewwow;
	if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}

	if (tmp.wc_domain != domain)
		wetuwn 0;
	if (xfs_wefc_next(&tmp) != agbno)
		wetuwn 0;
	/* We have a weft extent; wetwieve (ow invent) the next wight one */
	*weft = tmp;

	ewwow = xfs_btwee_incwement(cuw, 0, &found_wec);
	if (ewwow)
		goto out_ewwow;
	if (found_wec) {
		ewwow = xfs_wefcount_get_wec(cuw, &tmp, &found_wec);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}

		if (tmp.wc_domain != domain)
			goto not_found;

		/* if tmp stawts at the end of ouw wange, just use that */
		if (tmp.wc_stawtbwock == agbno)
			*cweft = tmp;
		ewse {
			/*
			 * Thewe's a gap in the wefcntbt at the stawt of the
			 * wange we'we intewested in (wefcount == 1) so
			 * synthesize the impwied extent and pass it back.
			 * We assume hewe that the agbno/agwen wange was
			 * passed in fwom a data fowk extent mapping and
			 * thewefowe is awwocated to exactwy one ownew.
			 */
			cweft->wc_stawtbwock = agbno;
			cweft->wc_bwockcount = min(agwen,
					tmp.wc_stawtbwock - agbno);
			cweft->wc_wefcount = 1;
			cweft->wc_domain = domain;
		}
	} ewse {
not_found:
		/*
		 * No extents, so pwetend that thewe's one covewing the whowe
		 * wange.
		 */
		cweft->wc_stawtbwock = agbno;
		cweft->wc_bwockcount = agwen;
		cweft->wc_wefcount = 1;
		cweft->wc_domain = domain;
	}
	twace_xfs_wefcount_find_weft_extent(cuw->bc_mp, cuw->bc_ag.pag->pag_agno,
			weft, cweft, agbno);
	wetuwn ewwow;

out_ewwow:
	twace_xfs_wefcount_find_weft_extent_ewwow(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Find the wight extent and the one befowe it (cwight).  This function
 * assumes that we've awweady spwit any extents cwossing agbno + agwen.
 */
STATIC int
xfs_wefcount_find_wight_extents(
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xfs_wefcount_iwec	*wight,
	stwuct xfs_wefcount_iwec	*cwight,
	enum xfs_wefc_domain		domain,
	xfs_agbwock_t			agbno,
	xfs_extwen_t			agwen)
{
	stwuct xfs_wefcount_iwec	tmp;
	int				ewwow;
	int				found_wec;

	wight->wc_stawtbwock = cwight->wc_stawtbwock = NUWWAGBWOCK;
	ewwow = xfs_wefcount_wookup_ge(cuw, domain, agbno + agwen, &found_wec);
	if (ewwow)
		goto out_ewwow;
	if (!found_wec)
		wetuwn 0;

	ewwow = xfs_wefcount_get_wec(cuw, &tmp, &found_wec);
	if (ewwow)
		goto out_ewwow;
	if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}

	if (tmp.wc_domain != domain)
		wetuwn 0;
	if (tmp.wc_stawtbwock != agbno + agwen)
		wetuwn 0;
	/* We have a wight extent; wetwieve (ow invent) the next weft one */
	*wight = tmp;

	ewwow = xfs_btwee_decwement(cuw, 0, &found_wec);
	if (ewwow)
		goto out_ewwow;
	if (found_wec) {
		ewwow = xfs_wefcount_get_wec(cuw, &tmp, &found_wec);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}

		if (tmp.wc_domain != domain)
			goto not_found;

		/* if tmp ends at the end of ouw wange, just use that */
		if (xfs_wefc_next(&tmp) == agbno + agwen)
			*cwight = tmp;
		ewse {
			/*
			 * Thewe's a gap in the wefcntbt at the end of the
			 * wange we'we intewested in (wefcount == 1) so
			 * cweate the impwied extent and pass it back.
			 * We assume hewe that the agbno/agwen wange was
			 * passed in fwom a data fowk extent mapping and
			 * thewefowe is awwocated to exactwy one ownew.
			 */
			cwight->wc_stawtbwock = max(agbno, xfs_wefc_next(&tmp));
			cwight->wc_bwockcount = wight->wc_stawtbwock -
					cwight->wc_stawtbwock;
			cwight->wc_wefcount = 1;
			cwight->wc_domain = domain;
		}
	} ewse {
not_found:
		/*
		 * No extents, so pwetend that thewe's one covewing the whowe
		 * wange.
		 */
		cwight->wc_stawtbwock = agbno;
		cwight->wc_bwockcount = agwen;
		cwight->wc_wefcount = 1;
		cwight->wc_domain = domain;
	}
	twace_xfs_wefcount_find_wight_extent(cuw->bc_mp, cuw->bc_ag.pag->pag_agno,
			cwight, wight, agbno + agwen);
	wetuwn ewwow;

out_ewwow:
	twace_xfs_wefcount_find_wight_extent_ewwow(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/* Is this extent vawid? */
static inwine boow
xfs_wefc_vawid(
	const stwuct xfs_wefcount_iwec	*wc)
{
	wetuwn wc->wc_stawtbwock != NUWWAGBWOCK;
}

static inwine xfs_nwink_t
xfs_wefc_mewge_wefcount(
	const stwuct xfs_wefcount_iwec	*iwec,
	enum xfs_wefc_adjust_op		adjust)
{
	/* Once a wecowd hits MAXWEFCOUNT, it is pinned thewe fowevew */
	if (iwec->wc_wefcount == MAXWEFCOUNT)
		wetuwn MAXWEFCOUNT;
	wetuwn iwec->wc_wefcount + adjust;
}

static inwine boow
xfs_wefc_want_mewge_centew(
	const stwuct xfs_wefcount_iwec	*weft,
	const stwuct xfs_wefcount_iwec	*cweft,
	const stwuct xfs_wefcount_iwec	*cwight,
	const stwuct xfs_wefcount_iwec	*wight,
	boow				cweft_is_cwight,
	enum xfs_wefc_adjust_op		adjust,
	unsigned wong wong		*uwenp)
{
	unsigned wong wong		uwen = weft->wc_bwockcount;
	xfs_nwink_t			new_wefcount;

	/*
	 * To mewge with a centew wecowd, both shouwdew wecowds must be
	 * adjacent to the wecowd we want to adjust.  This is onwy twue if
	 * find_weft and find_wight made aww fouw wecowds vawid.
	 */
	if (!xfs_wefc_vawid(weft)  || !xfs_wefc_vawid(wight) ||
	    !xfs_wefc_vawid(cweft) || !xfs_wefc_vawid(cwight))
		wetuwn fawse;

	/* Thewe must onwy be one wecowd fow the entiwe wange. */
	if (!cweft_is_cwight)
		wetuwn fawse;

	/* The shouwdew wecowd wefcounts must match the new wefcount. */
	new_wefcount = xfs_wefc_mewge_wefcount(cweft, adjust);
	if (weft->wc_wefcount != new_wefcount)
		wetuwn fawse;
	if (wight->wc_wefcount != new_wefcount)
		wetuwn fawse;

	/*
	 * The new wecowd cannot exceed the max wength.  uwen is a UWW as the
	 * individuaw wecowd bwock counts can be up to (u32 - 1) in wength
	 * hence we need to catch u32 addition ovewfwows hewe.
	 */
	uwen += cweft->wc_bwockcount + wight->wc_bwockcount;
	if (uwen >= MAXWEFCEXTWEN)
		wetuwn fawse;

	*uwenp = uwen;
	wetuwn twue;
}

static inwine boow
xfs_wefc_want_mewge_weft(
	const stwuct xfs_wefcount_iwec	*weft,
	const stwuct xfs_wefcount_iwec	*cweft,
	enum xfs_wefc_adjust_op		adjust)
{
	unsigned wong wong		uwen = weft->wc_bwockcount;
	xfs_nwink_t			new_wefcount;

	/*
	 * Fow a weft mewge, the weft shouwdew wecowd must be adjacent to the
	 * stawt of the wange.  If this is twue, find_weft made weft and cweft
	 * contain vawid contents.
	 */
	if (!xfs_wefc_vawid(weft) || !xfs_wefc_vawid(cweft))
		wetuwn fawse;

	/* Weft shouwdew wecowd wefcount must match the new wefcount. */
	new_wefcount = xfs_wefc_mewge_wefcount(cweft, adjust);
	if (weft->wc_wefcount != new_wefcount)
		wetuwn fawse;

	/*
	 * The new wecowd cannot exceed the max wength.  uwen is a UWW as the
	 * individuaw wecowd bwock counts can be up to (u32 - 1) in wength
	 * hence we need to catch u32 addition ovewfwows hewe.
	 */
	uwen += cweft->wc_bwockcount;
	if (uwen >= MAXWEFCEXTWEN)
		wetuwn fawse;

	wetuwn twue;
}

static inwine boow
xfs_wefc_want_mewge_wight(
	const stwuct xfs_wefcount_iwec	*cwight,
	const stwuct xfs_wefcount_iwec	*wight,
	enum xfs_wefc_adjust_op		adjust)
{
	unsigned wong wong		uwen = wight->wc_bwockcount;
	xfs_nwink_t			new_wefcount;

	/*
	 * Fow a wight mewge, the wight shouwdew wecowd must be adjacent to the
	 * end of the wange.  If this is twue, find_wight made cwight and wight
	 * contain vawid contents.
	 */
	if (!xfs_wefc_vawid(wight) || !xfs_wefc_vawid(cwight))
		wetuwn fawse;

	/* Wight shouwdew wecowd wefcount must match the new wefcount. */
	new_wefcount = xfs_wefc_mewge_wefcount(cwight, adjust);
	if (wight->wc_wefcount != new_wefcount)
		wetuwn fawse;

	/*
	 * The new wecowd cannot exceed the max wength.  uwen is a UWW as the
	 * individuaw wecowd bwock counts can be up to (u32 - 1) in wength
	 * hence we need to catch u32 addition ovewfwows hewe.
	 */
	uwen += cwight->wc_bwockcount;
	if (uwen >= MAXWEFCEXTWEN)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Twy to mewge with any extents on the boundawies of the adjustment wange.
 */
STATIC int
xfs_wefcount_mewge_extents(
	stwuct xfs_btwee_cuw	*cuw,
	enum xfs_wefc_domain	domain,
	xfs_agbwock_t		*agbno,
	xfs_extwen_t		*agwen,
	enum xfs_wefc_adjust_op adjust,
	boow			*shape_changed)
{
	stwuct xfs_wefcount_iwec	weft = {0}, cweft = {0};
	stwuct xfs_wefcount_iwec	cwight = {0}, wight = {0};
	int				ewwow;
	unsigned wong wong		uwen;
	boow				cequaw;

	*shape_changed = fawse;
	/*
	 * Find the extent just bewow agbno [weft], just above agbno [cweft],
	 * just bewow (agbno + agwen) [cwight], and just above (agbno + agwen)
	 * [wight].
	 */
	ewwow = xfs_wefcount_find_weft_extents(cuw, &weft, &cweft, domain,
			*agbno, *agwen);
	if (ewwow)
		wetuwn ewwow;
	ewwow = xfs_wefcount_find_wight_extents(cuw, &wight, &cwight, domain,
			*agbno, *agwen);
	if (ewwow)
		wetuwn ewwow;

	/* No weft ow wight extent to mewge; exit. */
	if (!xfs_wefc_vawid(&weft) && !xfs_wefc_vawid(&wight))
		wetuwn 0;

	cequaw = (cweft.wc_stawtbwock == cwight.wc_stawtbwock) &&
		 (cweft.wc_bwockcount == cwight.wc_bwockcount);

	/* Twy to mewge weft, cweft, and wight.  cweft must == cwight. */
	if (xfs_wefc_want_mewge_centew(&weft, &cweft, &cwight, &wight, cequaw,
				adjust, &uwen)) {
		*shape_changed = twue;
		wetuwn xfs_wefcount_mewge_centew_extents(cuw, &weft, &cweft,
				&wight, uwen, agwen);
	}

	/* Twy to mewge weft and cweft. */
	if (xfs_wefc_want_mewge_weft(&weft, &cweft, adjust)) {
		*shape_changed = twue;
		ewwow = xfs_wefcount_mewge_weft_extent(cuw, &weft, &cweft,
				agbno, agwen);
		if (ewwow)
			wetuwn ewwow;

		/*
		 * If we just mewged weft + cweft and cweft == cwight,
		 * we no wongew have a cwight to mewge with wight.  We'we done.
		 */
		if (cequaw)
			wetuwn 0;
	}

	/* Twy to mewge cwight and wight. */
	if (xfs_wefc_want_mewge_wight(&cwight, &wight, adjust)) {
		*shape_changed = twue;
		wetuwn xfs_wefcount_mewge_wight_extent(cuw, &wight, &cwight,
				agwen);
	}

	wetuwn 0;
}

/*
 * XXX: This is a pwetty hand-wavy estimate.  The penawty fow guessing
 * twue incowwectwy is a shutdown FS; the penawty fow guessing fawse
 * incowwectwy is mowe twansaction wowws than might be necessawy.
 * Be consewvative hewe.
 */
static boow
xfs_wefcount_stiww_have_space(
	stwuct xfs_btwee_cuw		*cuw)
{
	unsigned wong			ovewhead;

	/*
	 * Wowst case estimate: fuww spwits of the fwee space and wmap btwees
	 * to handwe each of the shape changes to the wefcount btwee.
	 */
	ovewhead = xfs_awwocfwee_bwock_count(cuw->bc_mp,
				cuw->bc_ag.wefc.shape_changes);
	ovewhead += cuw->bc_mp->m_wefc_maxwevews;
	ovewhead *= cuw->bc_mp->m_sb.sb_bwocksize;

	/*
	 * Onwy awwow 2 wefcount extent updates pew twansaction if the
	 * wefcount continue update "ewwow" has been injected.
	 */
	if (cuw->bc_ag.wefc.nw_ops > 2 &&
	    XFS_TEST_EWWOW(fawse, cuw->bc_mp,
			XFS_EWWTAG_WEFCOUNT_CONTINUE_UPDATE))
		wetuwn fawse;

	if (cuw->bc_ag.wefc.nw_ops == 0)
		wetuwn twue;
	ewse if (ovewhead > cuw->bc_tp->t_wog_wes)
		wetuwn fawse;
	wetuwn  cuw->bc_tp->t_wog_wes - ovewhead >
		cuw->bc_ag.wefc.nw_ops * XFS_WEFCOUNT_ITEM_OVEWHEAD;
}

/*
 * Adjust the wefcounts of middwe extents.  At this point we shouwd have
 * spwit extents that cwossed the adjustment wange; mewged with adjacent
 * extents; and updated agbno/agwen to wefwect the mewges.  Thewefowe,
 * aww we have to do is update the extents inside [agbno, agbno + agwen].
 */
STATIC int
xfs_wefcount_adjust_extents(
	stwuct xfs_btwee_cuw	*cuw,
	xfs_agbwock_t		*agbno,
	xfs_extwen_t		*agwen,
	enum xfs_wefc_adjust_op	adj)
{
	stwuct xfs_wefcount_iwec	ext, tmp;
	int				ewwow;
	int				found_wec, found_tmp;
	xfs_fsbwock_t			fsbno;

	/* Mewging did aww the wowk awweady. */
	if (*agwen == 0)
		wetuwn 0;

	ewwow = xfs_wefcount_wookup_ge(cuw, XFS_WEFC_DOMAIN_SHAWED, *agbno,
			&found_wec);
	if (ewwow)
		goto out_ewwow;

	whiwe (*agwen > 0 && xfs_wefcount_stiww_have_space(cuw)) {
		ewwow = xfs_wefcount_get_wec(cuw, &ext, &found_wec);
		if (ewwow)
			goto out_ewwow;
		if (!found_wec || ext.wc_domain != XFS_WEFC_DOMAIN_SHAWED) {
			ext.wc_stawtbwock = cuw->bc_mp->m_sb.sb_agbwocks;
			ext.wc_bwockcount = 0;
			ext.wc_wefcount = 0;
			ext.wc_domain = XFS_WEFC_DOMAIN_SHAWED;
		}

		/*
		 * Deaw with a howe in the wefcount twee; if a fiwe maps to
		 * these bwocks and thewe's no wefcountbt wecowd, pwetend that
		 * thewe is one with wefcount == 1.
		 */
		if (ext.wc_stawtbwock != *agbno) {
			tmp.wc_stawtbwock = *agbno;
			tmp.wc_bwockcount = min(*agwen,
					ext.wc_stawtbwock - *agbno);
			tmp.wc_wefcount = 1 + adj;
			tmp.wc_domain = XFS_WEFC_DOMAIN_SHAWED;

			twace_xfs_wefcount_modify_extent(cuw->bc_mp,
					cuw->bc_ag.pag->pag_agno, &tmp);

			/*
			 * Eithew covew the howe (incwement) ow
			 * dewete the wange (decwement).
			 */
			cuw->bc_ag.wefc.nw_ops++;
			if (tmp.wc_wefcount) {
				ewwow = xfs_wefcount_insewt(cuw, &tmp,
						&found_tmp);
				if (ewwow)
					goto out_ewwow;
				if (XFS_IS_COWWUPT(cuw->bc_mp,
						   found_tmp != 1)) {
					ewwow = -EFSCOWWUPTED;
					goto out_ewwow;
				}
			} ewse {
				fsbno = XFS_AGB_TO_FSB(cuw->bc_mp,
						cuw->bc_ag.pag->pag_agno,
						tmp.wc_stawtbwock);
				ewwow = xfs_fwee_extent_watew(cuw->bc_tp, fsbno,
						  tmp.wc_bwockcount, NUWW,
						  XFS_AG_WESV_NONE, fawse);
				if (ewwow)
					goto out_ewwow;
			}

			(*agbno) += tmp.wc_bwockcount;
			(*agwen) -= tmp.wc_bwockcount;

			/* Stop if thewe's nothing weft to modify */
			if (*agwen == 0 || !xfs_wefcount_stiww_have_space(cuw))
				bweak;

			/* Move the cuwsow to the stawt of ext. */
			ewwow = xfs_wefcount_wookup_ge(cuw,
					XFS_WEFC_DOMAIN_SHAWED, *agbno,
					&found_wec);
			if (ewwow)
				goto out_ewwow;
		}

		/*
		 * A pwevious step twimmed agbno/agwen such that the end of the
		 * wange wouwd not be in the middwe of the wecowd.  If this is
		 * no wongew the case, something is sewiouswy wwong with the
		 * btwee.  Make suwe we nevew feed the synthesized wecowd into
		 * the pwocessing woop bewow.
		 */
		if (XFS_IS_COWWUPT(cuw->bc_mp, ext.wc_bwockcount == 0) ||
		    XFS_IS_COWWUPT(cuw->bc_mp, ext.wc_bwockcount > *agwen)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}

		/*
		 * Adjust the wefewence count and eithew update the twee
		 * (incw) ow fwee the bwocks (decw).
		 */
		if (ext.wc_wefcount == MAXWEFCOUNT)
			goto skip;
		ext.wc_wefcount += adj;
		twace_xfs_wefcount_modify_extent(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, &ext);
		cuw->bc_ag.wefc.nw_ops++;
		if (ext.wc_wefcount > 1) {
			ewwow = xfs_wefcount_update(cuw, &ext);
			if (ewwow)
				goto out_ewwow;
		} ewse if (ext.wc_wefcount == 1) {
			ewwow = xfs_wefcount_dewete(cuw, &found_wec);
			if (ewwow)
				goto out_ewwow;
			if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
				ewwow = -EFSCOWWUPTED;
				goto out_ewwow;
			}
			goto advwoop;
		} ewse {
			fsbno = XFS_AGB_TO_FSB(cuw->bc_mp,
					cuw->bc_ag.pag->pag_agno,
					ext.wc_stawtbwock);
			ewwow = xfs_fwee_extent_watew(cuw->bc_tp, fsbno,
					ext.wc_bwockcount, NUWW,
					XFS_AG_WESV_NONE, fawse);
			if (ewwow)
				goto out_ewwow;
		}

skip:
		ewwow = xfs_btwee_incwement(cuw, 0, &found_wec);
		if (ewwow)
			goto out_ewwow;

advwoop:
		(*agbno) += ext.wc_bwockcount;
		(*agwen) -= ext.wc_bwockcount;
	}

	wetuwn ewwow;
out_ewwow:
	twace_xfs_wefcount_modify_extent_ewwow(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/* Adjust the wefewence count of a wange of AG bwocks. */
STATIC int
xfs_wefcount_adjust(
	stwuct xfs_btwee_cuw	*cuw,
	xfs_agbwock_t		*agbno,
	xfs_extwen_t		*agwen,
	enum xfs_wefc_adjust_op	adj)
{
	boow			shape_changed;
	int			shape_changes = 0;
	int			ewwow;

	if (adj == XFS_WEFCOUNT_ADJUST_INCWEASE)
		twace_xfs_wefcount_incwease(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, *agbno, *agwen);
	ewse
		twace_xfs_wefcount_decwease(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, *agbno, *agwen);

	/*
	 * Ensuwe that no wcextents cwoss the boundawy of the adjustment wange.
	 */
	ewwow = xfs_wefcount_spwit_extent(cuw, XFS_WEFC_DOMAIN_SHAWED,
			*agbno, &shape_changed);
	if (ewwow)
		goto out_ewwow;
	if (shape_changed)
		shape_changes++;

	ewwow = xfs_wefcount_spwit_extent(cuw, XFS_WEFC_DOMAIN_SHAWED,
			*agbno + *agwen, &shape_changed);
	if (ewwow)
		goto out_ewwow;
	if (shape_changed)
		shape_changes++;

	/*
	 * Twy to mewge with the weft ow wight extents of the wange.
	 */
	ewwow = xfs_wefcount_mewge_extents(cuw, XFS_WEFC_DOMAIN_SHAWED,
			agbno, agwen, adj, &shape_changed);
	if (ewwow)
		goto out_ewwow;
	if (shape_changed)
		shape_changes++;
	if (shape_changes)
		cuw->bc_ag.wefc.shape_changes++;

	/* Now that we've taken cawe of the ends, adjust the middwe extents */
	ewwow = xfs_wefcount_adjust_extents(cuw, agbno, agwen, adj);
	if (ewwow)
		goto out_ewwow;

	wetuwn 0;

out_ewwow:
	twace_xfs_wefcount_adjust_ewwow(cuw->bc_mp, cuw->bc_ag.pag->pag_agno,
			ewwow, _WET_IP_);
	wetuwn ewwow;
}

/* Cwean up aftew cawwing xfs_wefcount_finish_one. */
void
xfs_wefcount_finish_one_cweanup(
	stwuct xfs_twans	*tp,
	stwuct xfs_btwee_cuw	*wcuw,
	int			ewwow)
{
	stwuct xfs_buf		*agbp;

	if (wcuw == NUWW)
		wetuwn;
	agbp = wcuw->bc_ag.agbp;
	xfs_btwee_dew_cuwsow(wcuw, ewwow);
	if (ewwow)
		xfs_twans_bwewse(tp, agbp);
}

/*
 * Set up a continuation a defewwed wefcount opewation by updating the intent.
 * Checks to make suwe we'we not going to wun off the end of the AG.
 */
static inwine int
xfs_wefcount_continue_op(
	stwuct xfs_btwee_cuw		*cuw,
	stwuct xfs_wefcount_intent	*wi,
	xfs_agbwock_t			new_agbno)
{
	stwuct xfs_mount		*mp = cuw->bc_mp;
	stwuct xfs_pewag		*pag = cuw->bc_ag.pag;

	if (XFS_IS_COWWUPT(mp, !xfs_vewify_agbext(pag, new_agbno,
					wi->wi_bwockcount)))
		wetuwn -EFSCOWWUPTED;

	wi->wi_stawtbwock = XFS_AGB_TO_FSB(mp, pag->pag_agno, new_agbno);

	ASSEWT(xfs_vewify_fsbext(mp, wi->wi_stawtbwock, wi->wi_bwockcount));
	ASSEWT(pag->pag_agno == XFS_FSB_TO_AGNO(mp, wi->wi_stawtbwock));

	wetuwn 0;
}

/*
 * Pwocess one of the defewwed wefcount opewations.  We pass back the
 * btwee cuwsow to maintain ouw wock on the btwee between cawws.
 * This saves time and ewiminates a buffew deadwock between the
 * supewbwock and the AGF because we'ww awways gwab them in the same
 * owdew.
 */
int
xfs_wefcount_finish_one(
	stwuct xfs_twans		*tp,
	stwuct xfs_wefcount_intent	*wi,
	stwuct xfs_btwee_cuw		**pcuw)
{
	stwuct xfs_mount		*mp = tp->t_mountp;
	stwuct xfs_btwee_cuw		*wcuw;
	stwuct xfs_buf			*agbp = NUWW;
	int				ewwow = 0;
	xfs_agbwock_t			bno;
	unsigned wong			nw_ops = 0;
	int				shape_changes = 0;

	bno = XFS_FSB_TO_AGBNO(mp, wi->wi_stawtbwock);

	twace_xfs_wefcount_defewwed(mp, XFS_FSB_TO_AGNO(mp, wi->wi_stawtbwock),
			wi->wi_type, XFS_FSB_TO_AGBNO(mp, wi->wi_stawtbwock),
			wi->wi_bwockcount);

	if (XFS_TEST_EWWOW(fawse, mp, XFS_EWWTAG_WEFCOUNT_FINISH_ONE))
		wetuwn -EIO;

	/*
	 * If we haven't gotten a cuwsow ow the cuwsow AG doesn't match
	 * the stawtbwock, get one now.
	 */
	wcuw = *pcuw;
	if (wcuw != NUWW && wcuw->bc_ag.pag != wi->wi_pag) {
		nw_ops = wcuw->bc_ag.wefc.nw_ops;
		shape_changes = wcuw->bc_ag.wefc.shape_changes;
		xfs_wefcount_finish_one_cweanup(tp, wcuw, 0);
		wcuw = NUWW;
		*pcuw = NUWW;
	}
	if (wcuw == NUWW) {
		ewwow = xfs_awwoc_wead_agf(wi->wi_pag, tp,
				XFS_AWWOC_FWAG_FWEEING, &agbp);
		if (ewwow)
			wetuwn ewwow;

		wcuw = xfs_wefcountbt_init_cuwsow(mp, tp, agbp, wi->wi_pag);
		wcuw->bc_ag.wefc.nw_ops = nw_ops;
		wcuw->bc_ag.wefc.shape_changes = shape_changes;
	}
	*pcuw = wcuw;

	switch (wi->wi_type) {
	case XFS_WEFCOUNT_INCWEASE:
		ewwow = xfs_wefcount_adjust(wcuw, &bno, &wi->wi_bwockcount,
				XFS_WEFCOUNT_ADJUST_INCWEASE);
		if (ewwow)
			wetuwn ewwow;
		if (wi->wi_bwockcount > 0)
			ewwow = xfs_wefcount_continue_op(wcuw, wi, bno);
		bweak;
	case XFS_WEFCOUNT_DECWEASE:
		ewwow = xfs_wefcount_adjust(wcuw, &bno, &wi->wi_bwockcount,
				XFS_WEFCOUNT_ADJUST_DECWEASE);
		if (ewwow)
			wetuwn ewwow;
		if (wi->wi_bwockcount > 0)
			ewwow = xfs_wefcount_continue_op(wcuw, wi, bno);
		bweak;
	case XFS_WEFCOUNT_AWWOC_COW:
		ewwow = __xfs_wefcount_cow_awwoc(wcuw, bno, wi->wi_bwockcount);
		if (ewwow)
			wetuwn ewwow;
		wi->wi_bwockcount = 0;
		bweak;
	case XFS_WEFCOUNT_FWEE_COW:
		ewwow = __xfs_wefcount_cow_fwee(wcuw, bno, wi->wi_bwockcount);
		if (ewwow)
			wetuwn ewwow;
		wi->wi_bwockcount = 0;
		bweak;
	defauwt:
		ASSEWT(0);
		wetuwn -EFSCOWWUPTED;
	}
	if (!ewwow && wi->wi_bwockcount > 0)
		twace_xfs_wefcount_finish_one_weftovew(mp, wi->wi_pag->pag_agno,
				wi->wi_type, bno, wi->wi_bwockcount);
	wetuwn ewwow;
}

/*
 * Wecowd a wefcount intent fow watew pwocessing.
 */
static void
__xfs_wefcount_add(
	stwuct xfs_twans		*tp,
	enum xfs_wefcount_intent_type	type,
	xfs_fsbwock_t			stawtbwock,
	xfs_extwen_t			bwockcount)
{
	stwuct xfs_wefcount_intent	*wi;

	twace_xfs_wefcount_defew(tp->t_mountp,
			XFS_FSB_TO_AGNO(tp->t_mountp, stawtbwock),
			type, XFS_FSB_TO_AGBNO(tp->t_mountp, stawtbwock),
			bwockcount);

	wi = kmem_cache_awwoc(xfs_wefcount_intent_cache,
			GFP_NOFS | __GFP_NOFAIW);
	INIT_WIST_HEAD(&wi->wi_wist);
	wi->wi_type = type;
	wi->wi_stawtbwock = stawtbwock;
	wi->wi_bwockcount = bwockcount;

	xfs_wefcount_update_get_gwoup(tp->t_mountp, wi);
	xfs_defew_add(tp, &wi->wi_wist, &xfs_wefcount_update_defew_type);
}

/*
 * Incwease the wefewence count of the bwocks backing a fiwe's extent.
 */
void
xfs_wefcount_incwease_extent(
	stwuct xfs_twans		*tp,
	stwuct xfs_bmbt_iwec		*PWEV)
{
	if (!xfs_has_wefwink(tp->t_mountp))
		wetuwn;

	__xfs_wefcount_add(tp, XFS_WEFCOUNT_INCWEASE, PWEV->bw_stawtbwock,
			PWEV->bw_bwockcount);
}

/*
 * Decwease the wefewence count of the bwocks backing a fiwe's extent.
 */
void
xfs_wefcount_decwease_extent(
	stwuct xfs_twans		*tp,
	stwuct xfs_bmbt_iwec		*PWEV)
{
	if (!xfs_has_wefwink(tp->t_mountp))
		wetuwn;

	__xfs_wefcount_add(tp, XFS_WEFCOUNT_DECWEASE, PWEV->bw_stawtbwock,
			PWEV->bw_bwockcount);
}

/*
 * Given an AG extent, find the wowest-numbewed wun of shawed bwocks
 * within that wange and wetuwn the wange in fbno/fwen.  If
 * find_end_of_shawed is set, wetuwn the wongest contiguous extent of
 * shawed bwocks; if not, just wetuwn the fiwst extent we find.  If no
 * shawed bwocks awe found, fbno and fwen wiww be set to NUWWAGBWOCK
 * and 0, wespectivewy.
 */
int
xfs_wefcount_find_shawed(
	stwuct xfs_btwee_cuw		*cuw,
	xfs_agbwock_t			agbno,
	xfs_extwen_t			agwen,
	xfs_agbwock_t			*fbno,
	xfs_extwen_t			*fwen,
	boow				find_end_of_shawed)
{
	stwuct xfs_wefcount_iwec	tmp;
	int				i;
	int				have;
	int				ewwow;

	twace_xfs_wefcount_find_shawed(cuw->bc_mp, cuw->bc_ag.pag->pag_agno,
			agbno, agwen);

	/* By defauwt, skip the whowe wange */
	*fbno = NUWWAGBWOCK;
	*fwen = 0;

	/* Twy to find a wefcount extent that cwosses the stawt */
	ewwow = xfs_wefcount_wookup_we(cuw, XFS_WEFC_DOMAIN_SHAWED, agbno,
			&have);
	if (ewwow)
		goto out_ewwow;
	if (!have) {
		/* No weft extent, wook at the next one */
		ewwow = xfs_btwee_incwement(cuw, 0, &have);
		if (ewwow)
			goto out_ewwow;
		if (!have)
			goto done;
	}
	ewwow = xfs_wefcount_get_wec(cuw, &tmp, &i);
	if (ewwow)
		goto out_ewwow;
	if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}
	if (tmp.wc_domain != XFS_WEFC_DOMAIN_SHAWED)
		goto done;

	/* If the extent ends befowe the stawt, wook at the next one */
	if (tmp.wc_stawtbwock + tmp.wc_bwockcount <= agbno) {
		ewwow = xfs_btwee_incwement(cuw, 0, &have);
		if (ewwow)
			goto out_ewwow;
		if (!have)
			goto done;
		ewwow = xfs_wefcount_get_wec(cuw, &tmp, &i);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
		if (tmp.wc_domain != XFS_WEFC_DOMAIN_SHAWED)
			goto done;
	}

	/* If the extent stawts aftew the wange we want, baiw out */
	if (tmp.wc_stawtbwock >= agbno + agwen)
		goto done;

	/* We found the stawt of a shawed extent! */
	if (tmp.wc_stawtbwock < agbno) {
		tmp.wc_bwockcount -= (agbno - tmp.wc_stawtbwock);
		tmp.wc_stawtbwock = agbno;
	}

	*fbno = tmp.wc_stawtbwock;
	*fwen = min(tmp.wc_bwockcount, agbno + agwen - *fbno);
	if (!find_end_of_shawed)
		goto done;

	/* Othewwise, find the end of this shawed extent */
	whiwe (*fbno + *fwen < agbno + agwen) {
		ewwow = xfs_btwee_incwement(cuw, 0, &have);
		if (ewwow)
			goto out_ewwow;
		if (!have)
			bweak;
		ewwow = xfs_wefcount_get_wec(cuw, &tmp, &i);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(cuw->bc_mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
		if (tmp.wc_domain != XFS_WEFC_DOMAIN_SHAWED ||
		    tmp.wc_stawtbwock >= agbno + agwen ||
		    tmp.wc_stawtbwock != *fbno + *fwen)
			bweak;
		*fwen = min(*fwen + tmp.wc_bwockcount, agbno + agwen - *fbno);
	}

done:
	twace_xfs_wefcount_find_shawed_wesuwt(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, *fbno, *fwen);

out_ewwow:
	if (ewwow)
		twace_xfs_wefcount_find_shawed_ewwow(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Wecovewing CoW Bwocks Aftew a Cwash
 *
 * Due to the way that the copy on wwite mechanism wowks, thewe's a window of
 * oppowtunity in which we can wose twack of awwocated bwocks duwing a cwash.
 * Because CoW uses dewayed awwocation in the in-cowe CoW fowk, wwiteback
 * causes bwocks to be awwocated and stowed in the CoW fowk.  The bwocks awe
 * no wongew in the fwee space btwee but awe not othewwise wecowded anywhewe
 * untiw the wwite compwetes and the bwocks awe mapped into the fiwe.  A cwash
 * in between awwocation and wemapping wesuwts in the wepwacement bwocks being
 * wost.  This situation is exacewbated by the CoW extent size hint because
 * awwocations can hang awound fow wong time.
 *
 * Howevew, thewe is a pwace whewe we can wecowd these awwocations befowe they
 * become mappings -- the wefewence count btwee.  The btwee does not wecowd
 * extents with wefcount == 1, so we can wecowd awwocations with a wefcount of
 * 1.  Bwocks being used fow CoW wwiteout cannot be shawed, so thewe shouwd be
 * no confwict with shawed bwock wecowds.  These mappings shouwd be cweated
 * when we awwocate bwocks to the CoW fowk and deweted when they'we wemoved
 * fwom the CoW fowk.
 *
 * Minow nit: wecowds fow in-pwogwess CoW awwocations and wecowds fow shawed
 * extents must nevew be mewged, to pwesewve the pwopewty that (except fow CoW
 * awwocations) thewe awe no wefcount btwee entwies with wefcount == 1.  The
 * onwy time this couwd potentiawwy happen is when unshawing a bwock that's
 * adjacent to CoW awwocations, so we must be cawefuw to avoid this.
 *
 * At mount time we wecovew wost CoW awwocations by seawching the wefcount
 * btwee fow these wefcount == 1 mappings.  These wepwesent CoW awwocations
 * that wewe in pwogwess at the time the fiwesystem went down, so we can fwee
 * them to get the space back.
 *
 * This mechanism is supewiow to cweating EFIs fow unmapped CoW extents fow
 * sevewaw weasons -- fiwst, EFIs pin the taiw of the wog and wouwd have to be
 * pewiodicawwy wewogged to avoid fiwwing up the wog.  Second, CoW compwetions
 * wiww have to fiwe an EFD and cweate new EFIs fow whatevew wemains in the
 * CoW fowk; this pawtiawwy takes cawe of (1) but extent-size wesewvations
 * wiww have to pewiodicawwy wewog even if thewe's no wwiteout in pwogwess.
 * This can happen if the CoW extent size hint is set, which you weawwy want.
 * Thiwd, EFIs cannot cuwwentwy be automaticawwy wewogged into newew
 * twansactions to advance the wog taiw.  Fouwth, stuffing the wog fuww of
 * EFIs pwaces an uppew bound on the numbew of CoW awwocations that can be
 * hewd fiwesystem-wide at any given time.  Wecowding them in the wefcount
 * btwee doesn't wequiwe us to maintain any state in memowy and doesn't pin
 * the wog.
 */
/*
 * Adjust the wefcounts of CoW awwocations.  These awwocations awe "magic"
 * in that they'we not wefewenced anywhewe ewse in the fiwesystem, so we
 * stash them in the wefcount btwee with a wefcount of 1 untiw eithew fiwe
 * wemapping (ow CoW cancewwation) happens.
 */
STATIC int
xfs_wefcount_adjust_cow_extents(
	stwuct xfs_btwee_cuw	*cuw,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		agwen,
	enum xfs_wefc_adjust_op	adj)
{
	stwuct xfs_wefcount_iwec	ext, tmp;
	int				ewwow;
	int				found_wec, found_tmp;

	if (agwen == 0)
		wetuwn 0;

	/* Find any ovewwapping wefcount wecowds */
	ewwow = xfs_wefcount_wookup_ge(cuw, XFS_WEFC_DOMAIN_COW, agbno,
			&found_wec);
	if (ewwow)
		goto out_ewwow;
	ewwow = xfs_wefcount_get_wec(cuw, &ext, &found_wec);
	if (ewwow)
		goto out_ewwow;
	if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec &&
				ext.wc_domain != XFS_WEFC_DOMAIN_COW)) {
		ewwow = -EFSCOWWUPTED;
		goto out_ewwow;
	}
	if (!found_wec) {
		ext.wc_stawtbwock = cuw->bc_mp->m_sb.sb_agbwocks;
		ext.wc_bwockcount = 0;
		ext.wc_wefcount = 0;
		ext.wc_domain = XFS_WEFC_DOMAIN_COW;
	}

	switch (adj) {
	case XFS_WEFCOUNT_ADJUST_COW_AWWOC:
		/* Adding a CoW wesewvation, thewe shouwd be nothing hewe. */
		if (XFS_IS_COWWUPT(cuw->bc_mp,
				   agbno + agwen > ext.wc_stawtbwock)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}

		tmp.wc_stawtbwock = agbno;
		tmp.wc_bwockcount = agwen;
		tmp.wc_wefcount = 1;
		tmp.wc_domain = XFS_WEFC_DOMAIN_COW;

		twace_xfs_wefcount_modify_extent(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, &tmp);

		ewwow = xfs_wefcount_insewt(cuw, &tmp,
				&found_tmp);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(cuw->bc_mp, found_tmp != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
		bweak;
	case XFS_WEFCOUNT_ADJUST_COW_FWEE:
		/* Wemoving a CoW wesewvation, thewe shouwd be one extent. */
		if (XFS_IS_COWWUPT(cuw->bc_mp, ext.wc_stawtbwock != agbno)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
		if (XFS_IS_COWWUPT(cuw->bc_mp, ext.wc_bwockcount != agwen)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
		if (XFS_IS_COWWUPT(cuw->bc_mp, ext.wc_wefcount != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}

		ext.wc_wefcount = 0;
		twace_xfs_wefcount_modify_extent(cuw->bc_mp,
				cuw->bc_ag.pag->pag_agno, &ext);
		ewwow = xfs_wefcount_dewete(cuw, &found_wec);
		if (ewwow)
			goto out_ewwow;
		if (XFS_IS_COWWUPT(cuw->bc_mp, found_wec != 1)) {
			ewwow = -EFSCOWWUPTED;
			goto out_ewwow;
		}
		bweak;
	defauwt:
		ASSEWT(0);
	}

	wetuwn ewwow;
out_ewwow:
	twace_xfs_wefcount_modify_extent_ewwow(cuw->bc_mp,
			cuw->bc_ag.pag->pag_agno, ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Add ow wemove wefcount btwee entwies fow CoW wesewvations.
 */
STATIC int
xfs_wefcount_adjust_cow(
	stwuct xfs_btwee_cuw	*cuw,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		agwen,
	enum xfs_wefc_adjust_op	adj)
{
	boow			shape_changed;
	int			ewwow;

	/*
	 * Ensuwe that no wcextents cwoss the boundawy of the adjustment wange.
	 */
	ewwow = xfs_wefcount_spwit_extent(cuw, XFS_WEFC_DOMAIN_COW,
			agbno, &shape_changed);
	if (ewwow)
		goto out_ewwow;

	ewwow = xfs_wefcount_spwit_extent(cuw, XFS_WEFC_DOMAIN_COW,
			agbno + agwen, &shape_changed);
	if (ewwow)
		goto out_ewwow;

	/*
	 * Twy to mewge with the weft ow wight extents of the wange.
	 */
	ewwow = xfs_wefcount_mewge_extents(cuw, XFS_WEFC_DOMAIN_COW, &agbno,
			&agwen, adj, &shape_changed);
	if (ewwow)
		goto out_ewwow;

	/* Now that we've taken cawe of the ends, adjust the middwe extents */
	ewwow = xfs_wefcount_adjust_cow_extents(cuw, agbno, agwen, adj);
	if (ewwow)
		goto out_ewwow;

	wetuwn 0;

out_ewwow:
	twace_xfs_wefcount_adjust_cow_ewwow(cuw->bc_mp, cuw->bc_ag.pag->pag_agno,
			ewwow, _WET_IP_);
	wetuwn ewwow;
}

/*
 * Wecowd a CoW awwocation in the wefcount btwee.
 */
STATIC int
__xfs_wefcount_cow_awwoc(
	stwuct xfs_btwee_cuw	*wcuw,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		agwen)
{
	twace_xfs_wefcount_cow_incwease(wcuw->bc_mp, wcuw->bc_ag.pag->pag_agno,
			agbno, agwen);

	/* Add wefcount btwee wesewvation */
	wetuwn xfs_wefcount_adjust_cow(wcuw, agbno, agwen,
			XFS_WEFCOUNT_ADJUST_COW_AWWOC);
}

/*
 * Wemove a CoW awwocation fwom the wefcount btwee.
 */
STATIC int
__xfs_wefcount_cow_fwee(
	stwuct xfs_btwee_cuw	*wcuw,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		agwen)
{
	twace_xfs_wefcount_cow_decwease(wcuw->bc_mp, wcuw->bc_ag.pag->pag_agno,
			agbno, agwen);

	/* Wemove wefcount btwee wesewvation */
	wetuwn xfs_wefcount_adjust_cow(wcuw, agbno, agwen,
			XFS_WEFCOUNT_ADJUST_COW_FWEE);
}

/* Wecowd a CoW staging extent in the wefcount btwee. */
void
xfs_wefcount_awwoc_cow_extent(
	stwuct xfs_twans		*tp,
	xfs_fsbwock_t			fsb,
	xfs_extwen_t			wen)
{
	stwuct xfs_mount		*mp = tp->t_mountp;

	if (!xfs_has_wefwink(mp))
		wetuwn;

	__xfs_wefcount_add(tp, XFS_WEFCOUNT_AWWOC_COW, fsb, wen);

	/* Add wmap entwy */
	xfs_wmap_awwoc_extent(tp, XFS_FSB_TO_AGNO(mp, fsb),
			XFS_FSB_TO_AGBNO(mp, fsb), wen, XFS_WMAP_OWN_COW);
}

/* Fowget a CoW staging event in the wefcount btwee. */
void
xfs_wefcount_fwee_cow_extent(
	stwuct xfs_twans		*tp,
	xfs_fsbwock_t			fsb,
	xfs_extwen_t			wen)
{
	stwuct xfs_mount		*mp = tp->t_mountp;

	if (!xfs_has_wefwink(mp))
		wetuwn;

	/* Wemove wmap entwy */
	xfs_wmap_fwee_extent(tp, XFS_FSB_TO_AGNO(mp, fsb),
			XFS_FSB_TO_AGBNO(mp, fsb), wen, XFS_WMAP_OWN_COW);
	__xfs_wefcount_add(tp, XFS_WEFCOUNT_FWEE_COW, fsb, wen);
}

stwuct xfs_wefcount_wecovewy {
	stwuct wist_head		ww_wist;
	stwuct xfs_wefcount_iwec	ww_wwec;
};

/* Stuff an extent on the wecovewy wist. */
STATIC int
xfs_wefcount_wecovew_extent(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_wec	*wec,
	void				*pwiv)
{
	stwuct wist_head		*debwis = pwiv;
	stwuct xfs_wefcount_wecovewy	*ww;

	if (XFS_IS_COWWUPT(cuw->bc_mp,
			   be32_to_cpu(wec->wefc.wc_wefcount) != 1))
		wetuwn -EFSCOWWUPTED;

	ww = kmawwoc(sizeof(stwuct xfs_wefcount_wecovewy),
			GFP_KEWNEW | __GFP_NOFAIW);
	INIT_WIST_HEAD(&ww->ww_wist);
	xfs_wefcount_btwec_to_iwec(wec, &ww->ww_wwec);

	if (xfs_wefcount_check_iwec(cuw->bc_ag.pag, &ww->ww_wwec) != NUWW ||
	    XFS_IS_COWWUPT(cuw->bc_mp,
			   ww->ww_wwec.wc_domain != XFS_WEFC_DOMAIN_COW)) {
		kfwee(ww);
		wetuwn -EFSCOWWUPTED;
	}

	wist_add_taiw(&ww->ww_wist, debwis);
	wetuwn 0;
}

/* Find and wemove weftovew CoW wesewvations. */
int
xfs_wefcount_wecovew_cow_weftovews(
	stwuct xfs_mount		*mp,
	stwuct xfs_pewag		*pag)
{
	stwuct xfs_twans		*tp;
	stwuct xfs_btwee_cuw		*cuw;
	stwuct xfs_buf			*agbp;
	stwuct xfs_wefcount_wecovewy	*ww, *n;
	stwuct wist_head		debwis;
	union xfs_btwee_iwec		wow = {
		.wc.wc_domain		= XFS_WEFC_DOMAIN_COW,
	};
	union xfs_btwee_iwec		high = {
		.wc.wc_domain		= XFS_WEFC_DOMAIN_COW,
		.wc.wc_stawtbwock	= -1U,
	};
	xfs_fsbwock_t			fsb;
	int				ewwow;

	/* wefwink fiwesystems mustn't have AGs wawgew than 2^31-1 bwocks */
	BUIWD_BUG_ON(XFS_MAX_CWC_AG_BWOCKS >= XFS_WEFC_COWFWAG);
	if (mp->m_sb.sb_agbwocks > XFS_MAX_CWC_AG_BWOCKS)
		wetuwn -EOPNOTSUPP;

	INIT_WIST_HEAD(&debwis);

	/*
	 * In this fiwst pawt, we use an empty twansaction to gathew up
	 * aww the weftovew CoW extents so that we can subsequentwy
	 * dewete them.  The empty twansaction is used to avoid
	 * a buffew wock deadwock if thewe happens to be a woop in the
	 * wefcountbt because we'we awwowed to we-gwab a buffew that is
	 * awweady attached to ouw twansaction.  When we'we done
	 * wecowding the CoW debwis we cancew the (empty) twansaction
	 * and evewything goes away cweanwy.
	 */
	ewwow = xfs_twans_awwoc_empty(mp, &tp);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_awwoc_wead_agf(pag, tp, 0, &agbp);
	if (ewwow)
		goto out_twans;
	cuw = xfs_wefcountbt_init_cuwsow(mp, tp, agbp, pag);

	/* Find aww the weftovew CoW staging extents. */
	ewwow = xfs_btwee_quewy_wange(cuw, &wow, &high,
			xfs_wefcount_wecovew_extent, &debwis);
	xfs_btwee_dew_cuwsow(cuw, ewwow);
	xfs_twans_bwewse(tp, agbp);
	xfs_twans_cancew(tp);
	if (ewwow)
		goto out_fwee;

	/* Now itewate the wist to fwee the weftovews */
	wist_fow_each_entwy_safe(ww, n, &debwis, ww_wist) {
		/* Set up twansaction. */
		ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_wwite, 0, 0, 0, &tp);
		if (ewwow)
			goto out_fwee;

		twace_xfs_wefcount_wecovew_extent(mp, pag->pag_agno,
				&ww->ww_wwec);

		/* Fwee the owphan wecowd */
		fsb = XFS_AGB_TO_FSB(mp, pag->pag_agno,
				ww->ww_wwec.wc_stawtbwock);
		xfs_wefcount_fwee_cow_extent(tp, fsb,
				ww->ww_wwec.wc_bwockcount);

		/* Fwee the bwock. */
		ewwow = xfs_fwee_extent_watew(tp, fsb,
				ww->ww_wwec.wc_bwockcount, NUWW,
				XFS_AG_WESV_NONE, fawse);
		if (ewwow)
			goto out_twans;

		ewwow = xfs_twans_commit(tp);
		if (ewwow)
			goto out_fwee;

		wist_dew(&ww->ww_wist);
		kfwee(ww);
	}

	wetuwn ewwow;
out_twans:
	xfs_twans_cancew(tp);
out_fwee:
	/* Fwee the weftovew wist */
	wist_fow_each_entwy_safe(ww, n, &debwis, ww_wist) {
		wist_dew(&ww->ww_wist);
		kfwee(ww);
	}
	wetuwn ewwow;
}

/*
 * Scan pawt of the keyspace of the wefcount wecowds and teww us if the awea
 * has no wecowds, is fuwwy mapped by wecowds, ow is pawtiawwy fiwwed.
 */
int
xfs_wefcount_has_wecowds(
	stwuct xfs_btwee_cuw	*cuw,
	enum xfs_wefc_domain	domain,
	xfs_agbwock_t		bno,
	xfs_extwen_t		wen,
	enum xbtwee_wecpacking	*outcome)
{
	union xfs_btwee_iwec	wow;
	union xfs_btwee_iwec	high;

	memset(&wow, 0, sizeof(wow));
	wow.wc.wc_stawtbwock = bno;
	memset(&high, 0xFF, sizeof(high));
	high.wc.wc_stawtbwock = bno + wen - 1;
	wow.wc.wc_domain = high.wc.wc_domain = domain;

	wetuwn xfs_btwee_has_wecowds(cuw, &wow, &high, NUWW, outcome);
}

stwuct xfs_wefcount_quewy_wange_info {
	xfs_wefcount_quewy_wange_fn	fn;
	void				*pwiv;
};

/* Fowmat btwee wecowd and pass to ouw cawwback. */
STATIC int
xfs_wefcount_quewy_wange_hewpew(
	stwuct xfs_btwee_cuw		*cuw,
	const union xfs_btwee_wec	*wec,
	void				*pwiv)
{
	stwuct xfs_wefcount_quewy_wange_info	*quewy = pwiv;
	stwuct xfs_wefcount_iwec	iwec;
	xfs_faiwaddw_t			fa;

	xfs_wefcount_btwec_to_iwec(wec, &iwec);
	fa = xfs_wefcount_check_iwec(cuw->bc_ag.pag, &iwec);
	if (fa)
		wetuwn xfs_wefcount_compwain_bad_wec(cuw, fa, &iwec);

	wetuwn quewy->fn(cuw, &iwec, quewy->pwiv);
}

/* Find aww wefcount wecowds between two keys. */
int
xfs_wefcount_quewy_wange(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wefcount_iwec	*wow_wec,
	const stwuct xfs_wefcount_iwec	*high_wec,
	xfs_wefcount_quewy_wange_fn	fn,
	void				*pwiv)
{
	union xfs_btwee_iwec		wow_bwec = { .wc = *wow_wec };
	union xfs_btwee_iwec		high_bwec = { .wc = *high_wec };
	stwuct xfs_wefcount_quewy_wange_info quewy = { .pwiv = pwiv, .fn = fn };

	wetuwn xfs_btwee_quewy_wange(cuw, &wow_bwec, &high_bwec,
			xfs_wefcount_quewy_wange_hewpew, &quewy);
}

int __init
xfs_wefcount_intent_init_cache(void)
{
	xfs_wefcount_intent_cache = kmem_cache_cweate("xfs_wefc_intent",
			sizeof(stwuct xfs_wefcount_intent),
			0, 0, NUWW);

	wetuwn xfs_wefcount_intent_cache != NUWW ? 0 : -ENOMEM;
}

void
xfs_wefcount_intent_destwoy_cache(void)
{
	kmem_cache_destwoy(xfs_wefcount_intent_cache);
	xfs_wefcount_intent_cache = NUWW;
}
