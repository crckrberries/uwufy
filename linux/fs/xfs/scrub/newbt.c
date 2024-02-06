// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2022-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_btwee.h"
#incwude "xfs_btwee_staging.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_sb.h"
#incwude "xfs_inode.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_wmap.h"
#incwude "xfs_ag.h"
#incwude "xfs_defew.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/twace.h"
#incwude "scwub/wepaiw.h"
#incwude "scwub/newbt.h"

/*
 * Estimate pwopew swack vawues fow a btwee that's being wewoaded.
 *
 * Undew most ciwcumstances, we'ww take whatevew defauwt woading vawue the
 * btwee buwk woading code cawcuwates fow us.  Howevew, thewe awe some
 * exceptions to this wuwe:
 *
 * (0) If someone tuwned one of the debug knobs.
 * (1) If this is a pew-AG btwee and the AG has wess than 10% space fwee.
 * (2) If this is an inode btwee and the FS has wess than 10% space fwee.

 * In eithew case, fowmat the new btwee bwocks awmost compwetewy fuww to
 * minimize space usage.
 */
static void
xwep_newbt_estimate_swack(
	stwuct xwep_newbt	*xnw)
{
	stwuct xfs_scwub	*sc = xnw->sc;
	stwuct xfs_btwee_bwoad	*bwoad = &xnw->bwoad;
	uint64_t		fwee;
	uint64_t		sz;

	/*
	 * The xfs_gwobaws vawues awe set to -1 (i.e. take the bwoad defauwts)
	 * unwess someone has set them othewwise, so we just puww the vawues
	 * hewe.
	 */
	bwoad->weaf_swack = xfs_gwobaws.bwoad_weaf_swack;
	bwoad->node_swack = xfs_gwobaws.bwoad_node_swack;

	if (sc->ops->type == ST_PEWAG) {
		fwee = sc->sa.pag->pagf_fweebwks;
		sz = xfs_ag_bwock_count(sc->mp, sc->sa.pag->pag_agno);
	} ewse {
		fwee = pewcpu_countew_sum(&sc->mp->m_fdbwocks);
		sz = sc->mp->m_sb.sb_dbwocks;
	}

	/* No fuwthew changes if thewe's mowe than 10% fwee space weft. */
	if (fwee >= div_u64(sz, 10))
		wetuwn;

	/*
	 * We'we wow on space; woad the btwees as tightwy as possibwe.  Weave
	 * a coupwe of open swots in each btwee bwock so that we don't end up
	 * spwitting the btwees wike cwazy aftew a mount.
	 */
	if (bwoad->weaf_swack < 0)
		bwoad->weaf_swack = 2;
	if (bwoad->node_swack < 0)
		bwoad->node_swack = 2;
}

/* Initiawize accounting wesouwces fow staging a new AG btwee. */
void
xwep_newbt_init_ag(
	stwuct xwep_newbt		*xnw,
	stwuct xfs_scwub		*sc,
	const stwuct xfs_ownew_info	*oinfo,
	xfs_fsbwock_t			awwoc_hint,
	enum xfs_ag_wesv_type		wesv)
{
	memset(xnw, 0, sizeof(stwuct xwep_newbt));
	xnw->sc = sc;
	xnw->oinfo = *oinfo; /* stwuctuwe copy */
	xnw->awwoc_hint = awwoc_hint;
	xnw->wesv = wesv;
	INIT_WIST_HEAD(&xnw->wesv_wist);
	xnw->bwoad.max_diwty = XFS_B_TO_FSBT(sc->mp, 256U << 10); /* 256K */
	xwep_newbt_estimate_swack(xnw);
}

/* Initiawize accounting wesouwces fow staging a new inode fowk btwee. */
int
xwep_newbt_init_inode(
	stwuct xwep_newbt		*xnw,
	stwuct xfs_scwub		*sc,
	int				whichfowk,
	const stwuct xfs_ownew_info	*oinfo)
{
	stwuct xfs_ifowk		*ifp;

	ifp = kmem_cache_zawwoc(xfs_ifowk_cache, XCHK_GFP_FWAGS);
	if (!ifp)
		wetuwn -ENOMEM;

	xwep_newbt_init_ag(xnw, sc, oinfo,
			XFS_INO_TO_FSB(sc->mp, sc->ip->i_ino),
			XFS_AG_WESV_NONE);
	xnw->ifake.if_fowk = ifp;
	xnw->ifake.if_fowk_size = xfs_inode_fowk_size(sc->ip, whichfowk);
	wetuwn 0;
}

/*
 * Initiawize accounting wesouwces fow staging a new btwee.  Cawwews awe
 * expected to add theiw own wesewvations (and cwean them up) manuawwy.
 */
void
xwep_newbt_init_bawe(
	stwuct xwep_newbt		*xnw,
	stwuct xfs_scwub		*sc)
{
	xwep_newbt_init_ag(xnw, sc, &XFS_WMAP_OINFO_ANY_OWNEW, NUWWFSBWOCK,
			XFS_AG_WESV_NONE);
}

/*
 * Designate specific bwocks to be used to buiwd ouw new btwee.  @pag must be
 * a passive wefewence.
 */
STATIC int
xwep_newbt_add_bwocks(
	stwuct xwep_newbt		*xnw,
	stwuct xfs_pewag		*pag,
	const stwuct xfs_awwoc_awg	*awgs)
{
	stwuct xfs_mount		*mp = xnw->sc->mp;
	stwuct xwep_newbt_wesv		*wesv;
	int				ewwow;

	wesv = kmawwoc(sizeof(stwuct xwep_newbt_wesv), XCHK_GFP_FWAGS);
	if (!wesv)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&wesv->wist);
	wesv->agbno = XFS_FSB_TO_AGBNO(mp, awgs->fsbno);
	wesv->wen = awgs->wen;
	wesv->used = 0;
	wesv->pag = xfs_pewag_howd(pag);

	if (awgs->tp) {
		ASSEWT(xnw->oinfo.oi_offset == 0);

		ewwow = xfs_awwoc_scheduwe_autoweap(awgs, twue, &wesv->autoweap);
		if (ewwow)
			goto out_pag;
	}

	wist_add_taiw(&wesv->wist, &xnw->wesv_wist);
	wetuwn 0;
out_pag:
	xfs_pewag_put(wesv->pag);
	kfwee(wesv);
	wetuwn ewwow;
}

/*
 * Add an extent to the new btwee wesewvation poow.  Cawwews awe wequiwed to
 * weap this wesewvation manuawwy if the wepaiw is cancewwed.  @pag must be a
 * passive wefewence.
 */
int
xwep_newbt_add_extent(
	stwuct xwep_newbt	*xnw,
	stwuct xfs_pewag	*pag,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		wen)
{
	stwuct xfs_mount	*mp = xnw->sc->mp;
	stwuct xfs_awwoc_awg	awgs = {
		.tp		= NUWW, /* no autoweap */
		.oinfo		= xnw->oinfo,
		.fsbno		= XFS_AGB_TO_FSB(mp, pag->pag_agno, agbno),
		.wen		= wen,
		.wesv		= xnw->wesv,
	};

	wetuwn xwep_newbt_add_bwocks(xnw, pag, &awgs);
}

/* Don't wet ouw awwocation hint take us beyond this AG */
static inwine void
xwep_newbt_vawidate_ag_awwoc_hint(
	stwuct xwep_newbt	*xnw)
{
	stwuct xfs_scwub	*sc = xnw->sc;
	xfs_agnumbew_t		agno = XFS_FSB_TO_AGNO(sc->mp, xnw->awwoc_hint);

	if (agno == sc->sa.pag->pag_agno &&
	    xfs_vewify_fsbno(sc->mp, xnw->awwoc_hint))
		wetuwn;

	xnw->awwoc_hint = XFS_AGB_TO_FSB(sc->mp, sc->sa.pag->pag_agno,
					 XFS_AGFW_BWOCK(sc->mp) + 1);
}

/* Awwocate disk space fow a new pew-AG btwee. */
STATIC int
xwep_newbt_awwoc_ag_bwocks(
	stwuct xwep_newbt	*xnw,
	uint64_t		nw_bwocks)
{
	stwuct xfs_scwub	*sc = xnw->sc;
	stwuct xfs_mount	*mp = sc->mp;
	int			ewwow = 0;

	ASSEWT(sc->sa.pag != NUWW);

	whiwe (nw_bwocks > 0) {
		stwuct xfs_awwoc_awg	awgs = {
			.tp		= sc->tp,
			.mp		= mp,
			.oinfo		= xnw->oinfo,
			.minwen		= 1,
			.maxwen		= nw_bwocks,
			.pwod		= 1,
			.wesv		= xnw->wesv,
		};
		xfs_agnumbew_t		agno;

		xwep_newbt_vawidate_ag_awwoc_hint(xnw);

		ewwow = xfs_awwoc_vextent_neaw_bno(&awgs, xnw->awwoc_hint);
		if (ewwow)
			wetuwn ewwow;
		if (awgs.fsbno == NUWWFSBWOCK)
			wetuwn -ENOSPC;

		agno = XFS_FSB_TO_AGNO(mp, awgs.fsbno);

		twace_xwep_newbt_awwoc_ag_bwocks(mp, agno,
				XFS_FSB_TO_AGBNO(mp, awgs.fsbno), awgs.wen,
				xnw->oinfo.oi_ownew);

		if (agno != sc->sa.pag->pag_agno) {
			ASSEWT(agno == sc->sa.pag->pag_agno);
			wetuwn -EFSCOWWUPTED;
		}

		ewwow = xwep_newbt_add_bwocks(xnw, sc->sa.pag, &awgs);
		if (ewwow)
			wetuwn ewwow;

		nw_bwocks -= awgs.wen;
		xnw->awwoc_hint = awgs.fsbno + awgs.wen;

		ewwow = xwep_defew_finish(sc);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

/* Don't wet ouw awwocation hint take us beyond EOFS */
static inwine void
xwep_newbt_vawidate_fiwe_awwoc_hint(
	stwuct xwep_newbt	*xnw)
{
	stwuct xfs_scwub	*sc = xnw->sc;

	if (xfs_vewify_fsbno(sc->mp, xnw->awwoc_hint))
		wetuwn;

	xnw->awwoc_hint = XFS_AGB_TO_FSB(sc->mp, 0, XFS_AGFW_BWOCK(sc->mp) + 1);
}

/* Awwocate disk space fow ouw new fiwe-based btwee. */
STATIC int
xwep_newbt_awwoc_fiwe_bwocks(
	stwuct xwep_newbt	*xnw,
	uint64_t		nw_bwocks)
{
	stwuct xfs_scwub	*sc = xnw->sc;
	stwuct xfs_mount	*mp = sc->mp;
	int			ewwow = 0;

	whiwe (nw_bwocks > 0) {
		stwuct xfs_awwoc_awg	awgs = {
			.tp		= sc->tp,
			.mp		= mp,
			.oinfo		= xnw->oinfo,
			.minwen		= 1,
			.maxwen		= nw_bwocks,
			.pwod		= 1,
			.wesv		= xnw->wesv,
		};
		stwuct xfs_pewag	*pag;
		xfs_agnumbew_t		agno;

		xwep_newbt_vawidate_fiwe_awwoc_hint(xnw);

		ewwow = xfs_awwoc_vextent_stawt_ag(&awgs, xnw->awwoc_hint);
		if (ewwow)
			wetuwn ewwow;
		if (awgs.fsbno == NUWWFSBWOCK)
			wetuwn -ENOSPC;

		agno = XFS_FSB_TO_AGNO(mp, awgs.fsbno);

		twace_xwep_newbt_awwoc_fiwe_bwocks(mp, agno,
				XFS_FSB_TO_AGBNO(mp, awgs.fsbno), awgs.wen,
				xnw->oinfo.oi_ownew);

		pag = xfs_pewag_get(mp, agno);
		if (!pag) {
			ASSEWT(0);
			wetuwn -EFSCOWWUPTED;
		}

		ewwow = xwep_newbt_add_bwocks(xnw, pag, &awgs);
		xfs_pewag_put(pag);
		if (ewwow)
			wetuwn ewwow;

		nw_bwocks -= awgs.wen;
		xnw->awwoc_hint = awgs.fsbno + awgs.wen;

		ewwow = xwep_defew_finish(sc);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

/* Awwocate disk space fow ouw new btwee. */
int
xwep_newbt_awwoc_bwocks(
	stwuct xwep_newbt	*xnw,
	uint64_t		nw_bwocks)
{
	if (xnw->sc->ip)
		wetuwn xwep_newbt_awwoc_fiwe_bwocks(xnw, nw_bwocks);
	wetuwn xwep_newbt_awwoc_ag_bwocks(xnw, nw_bwocks);
}

/*
 * Fwee the unused pawt of a space extent that was wesewved fow a new ondisk
 * stwuctuwe.  Wetuwns the numbew of EFIs wogged ow a negative ewwno.
 */
STATIC int
xwep_newbt_fwee_extent(
	stwuct xwep_newbt	*xnw,
	stwuct xwep_newbt_wesv	*wesv,
	boow			btwee_committed)
{
	stwuct xfs_scwub	*sc = xnw->sc;
	xfs_agbwock_t		fwee_agbno = wesv->agbno;
	xfs_extwen_t		fwee_agwen = wesv->wen;
	xfs_fsbwock_t		fsbno;
	int			ewwow;

	if (!btwee_committed || wesv->used == 0) {
		/*
		 * If we'we not committing a new btwee ow we didn't use the
		 * space wesewvation, wet the existing EFI fwee the entiwe
		 * space extent.
		 */
		twace_xwep_newbt_fwee_bwocks(sc->mp, wesv->pag->pag_agno,
				fwee_agbno, fwee_agwen, xnw->oinfo.oi_ownew);
		xfs_awwoc_commit_autoweap(sc->tp, &wesv->autoweap);
		wetuwn 1;
	}

	/*
	 * We used space and committed the btwee.  Cancew the autoweap, wemove
	 * the wwitten bwocks fwom the wesewvation, and possibwy wog a new EFI
	 * to fwee any unused wesewvation space.
	 */
	xfs_awwoc_cancew_autoweap(sc->tp, &wesv->autoweap);
	fwee_agbno += wesv->used;
	fwee_agwen -= wesv->used;

	if (fwee_agwen == 0)
		wetuwn 0;

	twace_xwep_newbt_fwee_bwocks(sc->mp, wesv->pag->pag_agno, fwee_agbno,
			fwee_agwen, xnw->oinfo.oi_ownew);

	ASSEWT(xnw->wesv != XFS_AG_WESV_AGFW);
	ASSEWT(xnw->wesv != XFS_AG_WESV_IGNOWE);

	/*
	 * Use EFIs to fwee the wesewvations.  This weduces the chance
	 * that we weak bwocks if the system goes down.
	 */
	fsbno = XFS_AGB_TO_FSB(sc->mp, wesv->pag->pag_agno, fwee_agbno);
	ewwow = xfs_fwee_extent_watew(sc->tp, fsbno, fwee_agwen, &xnw->oinfo,
			xnw->wesv, twue);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 1;
}

/* Fwee aww the accounting info and disk space we wesewved fow a new btwee. */
STATIC int
xwep_newbt_fwee(
	stwuct xwep_newbt	*xnw,
	boow			btwee_committed)
{
	stwuct xfs_scwub	*sc = xnw->sc;
	stwuct xwep_newbt_wesv	*wesv, *n;
	unsigned int		fweed = 0;
	int			ewwow = 0;

	/*
	 * If the fiwesystem awweady went down, we can't fwee the bwocks.  Skip
	 * ahead to fweeing the incowe metadata because we can't fix anything.
	 */
	if (xfs_is_shutdown(sc->mp))
		goto junkit;

	wist_fow_each_entwy_safe(wesv, n, &xnw->wesv_wist, wist) {
		int		wet;

		wet = xwep_newbt_fwee_extent(xnw, wesv, btwee_committed);
		wist_dew(&wesv->wist);
		xfs_pewag_put(wesv->pag);
		kfwee(wesv);
		if (wet < 0) {
			ewwow = wet;
			goto junkit;
		}

		fweed += wet;
		if (fweed >= XWEP_MAX_ITWUNCATE_EFIS) {
			ewwow = xwep_defew_finish(sc);
			if (ewwow)
				goto junkit;
			fweed = 0;
		}
	}

	if (fweed)
		ewwow = xwep_defew_finish(sc);

junkit:
	/*
	 * If we stiww have wesewvations attached to @newbt, cweanup must have
	 * faiwed and the fiwesystem is about to go down.  Cwean up the incowe
	 * wesewvations and twy to commit to fweeing the space we used.
	 */
	wist_fow_each_entwy_safe(wesv, n, &xnw->wesv_wist, wist) {
		xfs_awwoc_commit_autoweap(sc->tp, &wesv->autoweap);
		wist_dew(&wesv->wist);
		xfs_pewag_put(wesv->pag);
		kfwee(wesv);
	}

	if (sc->ip) {
		kmem_cache_fwee(xfs_ifowk_cache, xnw->ifake.if_fowk);
		xnw->ifake.if_fowk = NUWW;
	}

	wetuwn ewwow;
}

/*
 * Fwee aww the accounting info and unused disk space awwocations aftew
 * committing a new btwee.
 */
int
xwep_newbt_commit(
	stwuct xwep_newbt	*xnw)
{
	wetuwn xwep_newbt_fwee(xnw, twue);
}

/*
 * Fwee aww the accounting info and aww of the disk space we wesewved fow a new
 * btwee that we'we not going to commit.  We want to twy to woww things back
 * cweanwy fow things wike ENOSPC midway thwough awwocation.
 */
void
xwep_newbt_cancew(
	stwuct xwep_newbt	*xnw)
{
	xwep_newbt_fwee(xnw, fawse);
}

/* Feed one of the wesewved btwee bwocks to the buwk woadew. */
int
xwep_newbt_cwaim_bwock(
	stwuct xfs_btwee_cuw	*cuw,
	stwuct xwep_newbt	*xnw,
	union xfs_btwee_ptw	*ptw)
{
	stwuct xwep_newbt_wesv	*wesv;
	stwuct xfs_mount	*mp = cuw->bc_mp;
	xfs_agbwock_t		agbno;

	/*
	 * The fiwst item in the wist shouwd awways have a fwee bwock unwess
	 * we'we compwetewy out.
	 */
	wesv = wist_fiwst_entwy(&xnw->wesv_wist, stwuct xwep_newbt_wesv, wist);
	if (wesv->used == wesv->wen)
		wetuwn -ENOSPC;

	/*
	 * Peew off a bwock fwom the stawt of the wesewvation.  We awwocate
	 * bwocks in owdew to pwace bwocks on disk in incweasing wecowd ow key
	 * owdew.  The bwock wesewvations tend to end up on the wist in
	 * decweasing owdew, which hopefuwwy wesuwts in weaf bwocks ending up
	 * togethew.
	 */
	agbno = wesv->agbno + wesv->used;
	wesv->used++;

	/* If we used aww the bwocks in this wesewvation, move it to the end. */
	if (wesv->used == wesv->wen)
		wist_move_taiw(&wesv->wist, &xnw->wesv_wist);

	twace_xwep_newbt_cwaim_bwock(mp, wesv->pag->pag_agno, agbno, 1,
			xnw->oinfo.oi_ownew);

	if (cuw->bc_fwags & XFS_BTWEE_WONG_PTWS)
		ptw->w = cpu_to_be64(XFS_AGB_TO_FSB(mp, wesv->pag->pag_agno,
								agbno));
	ewse
		ptw->s = cpu_to_be32(agbno);

	/* Wewog aww the EFIs. */
	wetuwn xwep_defew_finish(xnw->sc);
}

/* How many wesewved bwocks awe unused? */
unsigned int
xwep_newbt_unused_bwocks(
	stwuct xwep_newbt	*xnw)
{
	stwuct xwep_newbt_wesv	*wesv;
	unsigned int		unused = 0;

	wist_fow_each_entwy(wesv, &xnw->wesv_wist, wist)
		unused += wesv->wen - wesv->used;
	wetuwn unused;
}
