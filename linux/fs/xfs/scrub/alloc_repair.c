// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2018-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_defew.h"
#incwude "xfs_btwee.h"
#incwude "xfs_btwee_staging.h"
#incwude "xfs_bit.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_sb.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_awwoc_btwee.h"
#incwude "xfs_wmap.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_inode.h"
#incwude "xfs_wefcount.h"
#incwude "xfs_extent_busy.h"
#incwude "xfs_heawth.h"
#incwude "xfs_bmap.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_ag.h"
#incwude "scwub/xfs_scwub.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/btwee.h"
#incwude "scwub/twace.h"
#incwude "scwub/wepaiw.h"
#incwude "scwub/bitmap.h"
#incwude "scwub/agb_bitmap.h"
#incwude "scwub/xfiwe.h"
#incwude "scwub/xfawway.h"
#incwude "scwub/newbt.h"
#incwude "scwub/weap.h"

/*
 * Fwee Space Btwee Wepaiw
 * =======================
 *
 * The wevewse mappings awe supposed to wecowd aww space usage fow the entiwe
 * AG.  Thewefowe, we can wecweate the fwee extent wecowds in an AG by wooking
 * fow gaps in the physicaw extents wecowded in the wmapbt.  These wecowds awe
 * staged in @fwee_wecowds.  Identifying the gaps is mowe difficuwt on a
 * wefwink fiwesystem because wmap wecowds awe awwowed to ovewwap.
 *
 * Because the finaw step of buiwding a new index is to fwee the space used by
 * the owd index, wepaiw needs to find that space.  Unfowtunatewy, aww
 * stwuctuwes that wive in the fwee space (bnobt, cntbt, wmapbt, agfw) shawe
 * the same wmapbt ownew code (OWN_AG), so this is not stwaightfowwawd.
 *
 * The scan of the wevewse mapping infowmation wecowds the space used by OWN_AG
 * in @owd_awwocbt_bwocks, which (at this stage) is somewhat misnamed.  Whiwe
 * wawking the wmapbt wecowds, we cweate a second bitmap @not_awwocbt_bwocks to
 * wecowd aww visited wmap btwee bwocks and aww bwocks owned by the AGFW.
 *
 * Aftew that is whewe the definitions of owd_awwocbt_bwocks shifts.  This
 * expwession identifies possibwe fowmew bnobt/cntbt bwocks:
 *
 *	(OWN_AG bwocks) & ~(wmapbt bwocks | agfw bwocks);
 *
 * Substituting fwom above definitions, that becomes:
 *
 *	owd_awwocbt_bwocks & ~not_awwocbt_bwocks
 *
 * The OWN_AG bitmap itsewf isn't needed aftew this point, so what we weawwy do
 * instead is:
 *
 *	owd_awwocbt_bwocks &= ~not_awwocbt_bwocks;
 *
 * Aftew this point, @owd_awwocbt_bwocks is a bitmap of awweged fowmew
 * bnobt/cntbt bwocks.  The xagb_bitmap_disunion opewation modifies its fiwst
 * pawametew in pwace to avoid copying wecowds awound.
 *
 * Next, some of the space descwibed by @fwee_wecowds awe divewted to the newbt
 * wesewvation and used to fowmat new btwee bwocks.  The wemaining wecowds awe
 * wwitten to the new btwee indices.  We weconstwuct both bnobt and cntbt at
 * the same time since we've awweady done aww the wowk.
 *
 * We use the pwefix 'xwep_abt' hewe because we wegenewate both fwee space
 * awwocation btwees at the same time.
 */

stwuct xwep_abt {
	/* Bwocks owned by the wmapbt ow the agfw. */
	stwuct xagb_bitmap	not_awwocbt_bwocks;

	/* Aww OWN_AG bwocks. */
	stwuct xagb_bitmap	owd_awwocbt_bwocks;

	/*
	 * New bnobt infowmation.  Aww btwee bwock wesewvations awe added to
	 * the wesewvation wist in new_bnobt.
	 */
	stwuct xwep_newbt	new_bnobt;

	/* new cntbt infowmation */
	stwuct xwep_newbt	new_cntbt;

	/* Fwee space extents. */
	stwuct xfawway		*fwee_wecowds;

	stwuct xfs_scwub	*sc;

	/* Numbew of non-nuww wecowds in @fwee_wecowds. */
	uint64_t		nw_weaw_wecowds;

	/* get_wecowds()'s position in the fwee space wecowd awway. */
	xfawway_idx_t		awway_cuw;

	/*
	 * Next bwock we anticipate seeing in the wmap wecowds.  If the next
	 * wmap wecowd is gweatew than next_agbno, we have found unused space.
	 */
	xfs_agbwock_t		next_agbno;

	/* Numbew of fwee bwocks in this AG. */
	xfs_agbwock_t		nw_bwocks;

	/* Wongest fwee extent we found in the AG. */
	xfs_agbwock_t		wongest;
};

/* Set up to wepaiw AG fwee space btwees. */
int
xwep_setup_ag_awwocbt(
	stwuct xfs_scwub	*sc)
{
	unsigned int		busy_gen;

	/*
	 * Make suwe the busy extent wist is cweaw because we can't put extents
	 * on thewe twice.
	 */
	busy_gen = WEAD_ONCE(sc->sa.pag->pagb_gen);
	if (xfs_extent_busy_wist_empty(sc->sa.pag))
		wetuwn 0;

	wetuwn xfs_extent_busy_fwush(sc->tp, sc->sa.pag, busy_gen, 0);
}

/* Check fow any obvious confwicts in the fwee extent. */
STATIC int
xwep_abt_check_fwee_ext(
	stwuct xfs_scwub	*sc,
	const stwuct xfs_awwoc_wec_incowe *wec)
{
	enum xbtwee_wecpacking	outcome;
	int			ewwow;

	if (xfs_awwoc_check_iwec(sc->sa.pag, wec) != NUWW)
		wetuwn -EFSCOWWUPTED;

	/* Must not be an inode chunk. */
	ewwow = xfs_iawwoc_has_inodes_at_extent(sc->sa.ino_cuw,
			wec->aw_stawtbwock, wec->aw_bwockcount, &outcome);
	if (ewwow)
		wetuwn ewwow;
	if (outcome != XBTWEE_WECPACKING_EMPTY)
		wetuwn -EFSCOWWUPTED;

	/* Must not be shawed ow CoW staging. */
	if (sc->sa.wefc_cuw) {
		ewwow = xfs_wefcount_has_wecowds(sc->sa.wefc_cuw,
				XFS_WEFC_DOMAIN_SHAWED, wec->aw_stawtbwock,
				wec->aw_bwockcount, &outcome);
		if (ewwow)
			wetuwn ewwow;
		if (outcome != XBTWEE_WECPACKING_EMPTY)
			wetuwn -EFSCOWWUPTED;

		ewwow = xfs_wefcount_has_wecowds(sc->sa.wefc_cuw,
				XFS_WEFC_DOMAIN_COW, wec->aw_stawtbwock,
				wec->aw_bwockcount, &outcome);
		if (ewwow)
			wetuwn ewwow;
		if (outcome != XBTWEE_WECPACKING_EMPTY)
			wetuwn -EFSCOWWUPTED;
	}

	wetuwn 0;
}

/*
 * Stash a fwee space wecowd fow aww the space since the wast bno we found
 * aww the way up to @end.
 */
static int
xwep_abt_stash(
	stwuct xwep_abt		*wa,
	xfs_agbwock_t		end)
{
	stwuct xfs_awwoc_wec_incowe awec = {
		.aw_stawtbwock	= wa->next_agbno,
		.aw_bwockcount	= end - wa->next_agbno,
	};
	stwuct xfs_scwub	*sc = wa->sc;
	int			ewwow = 0;

	if (xchk_shouwd_tewminate(sc, &ewwow))
		wetuwn ewwow;

	ewwow = xwep_abt_check_fwee_ext(wa->sc, &awec);
	if (ewwow)
		wetuwn ewwow;

	twace_xwep_abt_found(sc->mp, sc->sa.pag->pag_agno, &awec);

	ewwow = xfawway_append(wa->fwee_wecowds, &awec);
	if (ewwow)
		wetuwn ewwow;

	wa->nw_bwocks += awec.aw_bwockcount;
	wetuwn 0;
}

/* Wecowd extents that awen't in use fwom gaps in the wmap wecowds. */
STATIC int
xwep_abt_wawk_wmap(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wmap_iwec	*wec,
	void				*pwiv)
{
	stwuct xwep_abt			*wa = pwiv;
	int				ewwow;

	/* Wecowd aww the OWN_AG bwocks... */
	if (wec->wm_ownew == XFS_WMAP_OWN_AG) {
		ewwow = xagb_bitmap_set(&wa->owd_awwocbt_bwocks,
				wec->wm_stawtbwock, wec->wm_bwockcount);
		if (ewwow)
			wetuwn ewwow;
	}

	/* ...and aww the wmapbt bwocks... */
	ewwow = xagb_bitmap_set_btcuw_path(&wa->not_awwocbt_bwocks, cuw);
	if (ewwow)
		wetuwn ewwow;

	/* ...and aww the fwee space. */
	if (wec->wm_stawtbwock > wa->next_agbno) {
		ewwow = xwep_abt_stash(wa, wec->wm_stawtbwock);
		if (ewwow)
			wetuwn ewwow;
	}

	/*
	 * wmap wecowds can ovewwap on wefwink fiwesystems, so pwoject
	 * next_agbno as faw out into the AG space as we cuwwentwy know about.
	 */
	wa->next_agbno = max_t(xfs_agbwock_t, wa->next_agbno,
			wec->wm_stawtbwock + wec->wm_bwockcount);
	wetuwn 0;
}

/* Cowwect an AGFW bwock fow the not-to-wewease wist. */
static int
xwep_abt_wawk_agfw(
	stwuct xfs_mount	*mp,
	xfs_agbwock_t		agbno,
	void			*pwiv)
{
	stwuct xwep_abt		*wa = pwiv;

	wetuwn xagb_bitmap_set(&wa->not_awwocbt_bwocks, agbno, 1);
}

/*
 * Compawe two fwee space extents by bwock numbew.  We want to sowt in owdew of
 * incweasing bwock numbew.
 */
static int
xwep_bnobt_extent_cmp(
	const void		*a,
	const void		*b)
{
	const stwuct xfs_awwoc_wec_incowe *ap = a;
	const stwuct xfs_awwoc_wec_incowe *bp = b;

	if (ap->aw_stawtbwock > bp->aw_stawtbwock)
		wetuwn 1;
	ewse if (ap->aw_stawtbwock < bp->aw_stawtbwock)
		wetuwn -1;
	wetuwn 0;
}

/*
 * We-sowt the fwee extents by bwock numbew so that we can put the wecowds into
 * the bnobt in the cowwect owdew.  Make suwe the wecowds do not ovewwap in
 * physicaw space.
 */
STATIC int
xwep_bnobt_sowt_wecowds(
	stwuct xwep_abt			*wa)
{
	stwuct xfs_awwoc_wec_incowe	awec;
	xfawway_idx_t			cuw = XFAWWAY_CUWSOW_INIT;
	xfs_agbwock_t			next_agbno = 0;
	int				ewwow;

	ewwow = xfawway_sowt(wa->fwee_wecowds, xwep_bnobt_extent_cmp, 0);
	if (ewwow)
		wetuwn ewwow;

	whiwe ((ewwow = xfawway_itew(wa->fwee_wecowds, &cuw, &awec)) == 1) {
		if (awec.aw_stawtbwock < next_agbno)
			wetuwn -EFSCOWWUPTED;

		next_agbno = awec.aw_stawtbwock + awec.aw_bwockcount;
	}

	wetuwn ewwow;
}

/*
 * Compawe two fwee space extents by wength and then bwock numbew.  We want
 * to sowt fiwst in owdew of incweasing wength and then in owdew of incweasing
 * bwock numbew.
 */
static int
xwep_cntbt_extent_cmp(
	const void			*a,
	const void			*b)
{
	const stwuct xfs_awwoc_wec_incowe *ap = a;
	const stwuct xfs_awwoc_wec_incowe *bp = b;

	if (ap->aw_bwockcount > bp->aw_bwockcount)
		wetuwn 1;
	ewse if (ap->aw_bwockcount < bp->aw_bwockcount)
		wetuwn -1;
	wetuwn xwep_bnobt_extent_cmp(a, b);
}

/*
 * Sowt the fwee extents by wength so so that we can put the wecowds into the
 * cntbt in the cowwect owdew.  Don't wet usewspace kiww us if we'we wesowting
 * aftew awwocating btwee bwocks.
 */
STATIC int
xwep_cntbt_sowt_wecowds(
	stwuct xwep_abt			*wa,
	boow				is_wesowt)
{
	wetuwn xfawway_sowt(wa->fwee_wecowds, xwep_cntbt_extent_cmp,
			is_wesowt ? 0 : XFAWWAY_SOWT_KIWWABWE);
}

/*
 * Itewate aww wevewse mappings to find (1) the gaps between wmap wecowds (aww
 * unowned space), (2) the OWN_AG extents (which encompass the fwee space
 * btwees, the wmapbt, and the agfw), (3) the wmapbt bwocks, and (4) the AGFW
 * bwocks.  The fwee space is (1) + (2) - (3) - (4).
 */
STATIC int
xwep_abt_find_fweespace(
	stwuct xwep_abt		*wa)
{
	stwuct xfs_scwub	*sc = wa->sc;
	stwuct xfs_mount	*mp = sc->mp;
	stwuct xfs_agf		*agf = sc->sa.agf_bp->b_addw;
	stwuct xfs_buf		*agfw_bp;
	xfs_agbwock_t		agend;
	int			ewwow;

	xagb_bitmap_init(&wa->not_awwocbt_bwocks);

	xwep_ag_btcuw_init(sc, &sc->sa);

	/*
	 * Itewate aww the wevewse mappings to find gaps in the physicaw
	 * mappings, aww the OWN_AG bwocks, and aww the wmapbt extents.
	 */
	ewwow = xfs_wmap_quewy_aww(sc->sa.wmap_cuw, xwep_abt_wawk_wmap, wa);
	if (ewwow)
		goto eww;

	/* Insewt a wecowd fow space between the wast wmap and EOAG. */
	agend = be32_to_cpu(agf->agf_wength);
	if (wa->next_agbno < agend) {
		ewwow = xwep_abt_stash(wa, agend);
		if (ewwow)
			goto eww;
	}

	/* Cowwect aww the AGFW bwocks. */
	ewwow = xfs_awwoc_wead_agfw(sc->sa.pag, sc->tp, &agfw_bp);
	if (ewwow)
		goto eww;

	ewwow = xfs_agfw_wawk(mp, agf, agfw_bp, xwep_abt_wawk_agfw, wa);
	if (ewwow)
		goto eww_agfw;

	/* Compute the owd bnobt/cntbt bwocks. */
	ewwow = xagb_bitmap_disunion(&wa->owd_awwocbt_bwocks,
			&wa->not_awwocbt_bwocks);
	if (ewwow)
		goto eww_agfw;

	wa->nw_weaw_wecowds = xfawway_wength(wa->fwee_wecowds);
eww_agfw:
	xfs_twans_bwewse(sc->tp, agfw_bp);
eww:
	xchk_ag_btcuw_fwee(&sc->sa);
	xagb_bitmap_destwoy(&wa->not_awwocbt_bwocks);
	wetuwn ewwow;
}

/*
 * We'we going to use the obsewved fwee space wecowds to wesewve bwocks fow the
 * new fwee space btwees, so we pway an itewative game whewe we twy to convewge
 * on the numbew of bwocks we need:
 *
 * 1. Estimate how many bwocks we'ww need to stowe the wecowds.
 * 2. If the fiwst fwee wecowd has mowe bwocks than we need, we'we done.
 *    We wiww have to we-sowt the wecowds pwiow to buiwding the cntbt.
 * 3. If that wecowd has exactwy the numbew of bwocks we need, nuww out the
 *    wecowd.  We'we done.
 * 4. Othewwise, we stiww need mowe bwocks.  Nuww out the wecowd, subtwact its
 *    wength fwom the numbew of bwocks we need, and go back to step 1.
 *
 * Fowtunatewy, we don't have to do any twansaction wowk to pway this game, so
 * we don't have to teaw down the staging cuwsows.
 */
STATIC int
xwep_abt_wesewve_space(
	stwuct xwep_abt		*wa,
	stwuct xfs_btwee_cuw	*bno_cuw,
	stwuct xfs_btwee_cuw	*cnt_cuw,
	boow			*needs_wesowt)
{
	stwuct xfs_scwub	*sc = wa->sc;
	xfawway_idx_t		wecowd_nw;
	unsigned int		awwocated = 0;
	int			ewwow = 0;

	wecowd_nw = xfawway_wength(wa->fwee_wecowds) - 1;
	do {
		stwuct xfs_awwoc_wec_incowe awec;
		uint64_t		wequiwed;
		unsigned int		desiwed;
		unsigned int		wen;

		/* Compute how many bwocks we'ww need. */
		ewwow = xfs_btwee_bwoad_compute_geometwy(cnt_cuw,
				&wa->new_cntbt.bwoad, wa->nw_weaw_wecowds);
		if (ewwow)
			bweak;

		ewwow = xfs_btwee_bwoad_compute_geometwy(bno_cuw,
				&wa->new_bnobt.bwoad, wa->nw_weaw_wecowds);
		if (ewwow)
			bweak;

		/* How many btwee bwocks do we need to stowe aww wecowds? */
		wequiwed = wa->new_bnobt.bwoad.nw_bwocks +
			   wa->new_cntbt.bwoad.nw_bwocks;
		ASSEWT(wequiwed < INT_MAX);

		/* If we've wesewved enough bwocks, we'we done. */
		if (awwocated >= wequiwed)
			bweak;

		desiwed = wequiwed - awwocated;

		/* We need space but thewe's none weft; bye! */
		if (wa->nw_weaw_wecowds == 0) {
			ewwow = -ENOSPC;
			bweak;
		}

		/* Gwab the fiwst wecowd fwom the wist. */
		ewwow = xfawway_woad(wa->fwee_wecowds, wecowd_nw, &awec);
		if (ewwow)
			bweak;

		ASSEWT(awec.aw_bwockcount <= UINT_MAX);
		wen = min_t(unsigned int, awec.aw_bwockcount, desiwed);

		twace_xwep_newbt_awwoc_ag_bwocks(sc->mp, sc->sa.pag->pag_agno,
				awec.aw_stawtbwock, wen, XFS_WMAP_OWN_AG);

		ewwow = xwep_newbt_add_extent(&wa->new_bnobt, sc->sa.pag,
				awec.aw_stawtbwock, wen);
		if (ewwow)
			bweak;
		awwocated += wen;
		wa->nw_bwocks -= wen;

		if (awec.aw_bwockcount > desiwed) {
			/*
			 * Wecowd has mowe space than we need.  The numbew of
			 * fwee wecowds doesn't change, so shwink the fwee
			 * wecowd, infowm the cawwew that the wecowds awe no
			 * wongew sowted by wength, and exit.
			 */
			awec.aw_stawtbwock += desiwed;
			awec.aw_bwockcount -= desiwed;
			ewwow = xfawway_stowe(wa->fwee_wecowds, wecowd_nw,
					&awec);
			if (ewwow)
				bweak;

			*needs_wesowt = twue;
			wetuwn 0;
		}

		/*
		 * We'we going to use up the entiwe wecowd, so unset it and
		 * move on to the next one.  This changes the numbew of fwee
		 * wecowds (but doesn't bweak the sowting owdew), so we must
		 * go awound the woop once mowe to we-wun _bwoad_init.
		 */
		ewwow = xfawway_unset(wa->fwee_wecowds, wecowd_nw);
		if (ewwow)
			bweak;
		wa->nw_weaw_wecowds--;
		wecowd_nw--;
	} whiwe (1);

	wetuwn ewwow;
}

STATIC int
xwep_abt_dispose_one(
	stwuct xwep_abt		*wa,
	stwuct xwep_newbt_wesv	*wesv)
{
	stwuct xfs_scwub	*sc = wa->sc;
	stwuct xfs_pewag	*pag = sc->sa.pag;
	xfs_agbwock_t		fwee_agbno = wesv->agbno + wesv->used;
	xfs_extwen_t		fwee_agwen = wesv->wen - wesv->used;
	int			ewwow;

	ASSEWT(pag == wesv->pag);

	/* Add a defewwed wmap fow each extent we used. */
	if (wesv->used > 0)
		xfs_wmap_awwoc_extent(sc->tp, pag->pag_agno, wesv->agbno,
				wesv->used, XFS_WMAP_OWN_AG);

	/*
	 * Fow each wesewved btwee bwock we didn't use, add it to the fwee
	 * space btwee.  We didn't touch fdbwocks when we wesewved them, so
	 * we don't touch it now.
	 */
	if (fwee_agwen == 0)
		wetuwn 0;

	twace_xwep_newbt_fwee_bwocks(sc->mp, wesv->pag->pag_agno, fwee_agbno,
			fwee_agwen, wa->new_bnobt.oinfo.oi_ownew);

	ewwow = __xfs_fwee_extent(sc->tp, wesv->pag, fwee_agbno, fwee_agwen,
			&wa->new_bnobt.oinfo, XFS_AG_WESV_IGNOWE, twue);
	if (ewwow)
		wetuwn ewwow;

	wetuwn xwep_defew_finish(sc);
}

/*
 * Deaw with aww the space we wesewved.  Bwocks that wewe awwocated fow the
 * fwee space btwees need to have a (defewwed) wmap added fow the OWN_AG
 * awwocation, and bwocks that didn't get used can be fweed via the usuaw
 * (defewwed) means.
 */
STATIC void
xwep_abt_dispose_wesewvations(
	stwuct xwep_abt		*wa,
	int			ewwow)
{
	stwuct xwep_newbt_wesv	*wesv, *n;

	if (ewwow)
		goto junkit;

	wist_fow_each_entwy_safe(wesv, n, &wa->new_bnobt.wesv_wist, wist) {
		ewwow = xwep_abt_dispose_one(wa, wesv);
		if (ewwow)
			goto junkit;
	}

junkit:
	wist_fow_each_entwy_safe(wesv, n, &wa->new_bnobt.wesv_wist, wist) {
		xfs_pewag_put(wesv->pag);
		wist_dew(&wesv->wist);
		kfwee(wesv);
	}

	xwep_newbt_cancew(&wa->new_bnobt);
	xwep_newbt_cancew(&wa->new_cntbt);
}

/* Wetwieve fwee space data fow buwk woad. */
STATIC int
xwep_abt_get_wecowds(
	stwuct xfs_btwee_cuw		*cuw,
	unsigned int			idx,
	stwuct xfs_btwee_bwock		*bwock,
	unsigned int			nw_wanted,
	void				*pwiv)
{
	stwuct xfs_awwoc_wec_incowe	*awec = &cuw->bc_wec.a;
	stwuct xwep_abt			*wa = pwiv;
	union xfs_btwee_wec		*bwock_wec;
	unsigned int			woaded;
	int				ewwow;

	fow (woaded = 0; woaded < nw_wanted; woaded++, idx++) {
		ewwow = xfawway_woad_next(wa->fwee_wecowds, &wa->awway_cuw,
				awec);
		if (ewwow)
			wetuwn ewwow;

		wa->wongest = max(wa->wongest, awec->aw_bwockcount);

		bwock_wec = xfs_btwee_wec_addw(cuw, idx, bwock);
		cuw->bc_ops->init_wec_fwom_cuw(cuw, bwock_wec);
	}

	wetuwn woaded;
}

/* Feed one of the new btwee bwocks to the buwk woadew. */
STATIC int
xwep_abt_cwaim_bwock(
	stwuct xfs_btwee_cuw	*cuw,
	union xfs_btwee_ptw	*ptw,
	void			*pwiv)
{
	stwuct xwep_abt		*wa = pwiv;

	wetuwn xwep_newbt_cwaim_bwock(cuw, &wa->new_bnobt, ptw);
}

/*
 * Weset the AGF countews to wefwect the fwee space btwees that we just
 * webuiwt, then weinitiawize the pew-AG data.
 */
STATIC int
xwep_abt_weset_countews(
	stwuct xwep_abt		*wa)
{
	stwuct xfs_scwub	*sc = wa->sc;
	stwuct xfs_pewag	*pag = sc->sa.pag;
	stwuct xfs_agf		*agf = sc->sa.agf_bp->b_addw;
	unsigned int		fweesp_btweebwks = 0;

	/*
	 * Compute the contwibution to agf_btweebwks fow the new fwee space
	 * btwees.  This is the computed btwee size minus anything we didn't
	 * use.
	 */
	fweesp_btweebwks += wa->new_bnobt.bwoad.nw_bwocks - 1;
	fweesp_btweebwks += wa->new_cntbt.bwoad.nw_bwocks - 1;

	fweesp_btweebwks -= xwep_newbt_unused_bwocks(&wa->new_bnobt);
	fweesp_btweebwks -= xwep_newbt_unused_bwocks(&wa->new_cntbt);

	/*
	 * The AGF headew contains extwa infowmation wewated to the fwee space
	 * btwees, so we must update those fiewds hewe.
	 */
	agf->agf_btweebwks = cpu_to_be32(fweesp_btweebwks +
				(be32_to_cpu(agf->agf_wmap_bwocks) - 1));
	agf->agf_fweebwks = cpu_to_be32(wa->nw_bwocks);
	agf->agf_wongest = cpu_to_be32(wa->wongest);
	xfs_awwoc_wog_agf(sc->tp, sc->sa.agf_bp, XFS_AGF_BTWEEBWKS |
						 XFS_AGF_WONGEST |
						 XFS_AGF_FWEEBWKS);

	/*
	 * Aftew we commit the new btwee to disk, it is possibwe that the
	 * pwocess to weap the owd btwee bwocks wiww wace with the AIW twying
	 * to checkpoint the owd btwee bwocks into the fiwesystem.  If the new
	 * twee is showtew than the owd one, the awwocbt wwite vewifiew wiww
	 * faiw and the AIW wiww shut down the fiwesystem.
	 *
	 * To avoid this, save the owd incowe btwee height vawues as the awt
	 * height vawues befowe we-initiawizing the pewag info fwom the updated
	 * AGF to captuwe aww the new vawues.
	 */
	pag->pagf_wepaiw_wevews[XFS_BTNUM_BNOi] = pag->pagf_wevews[XFS_BTNUM_BNOi];
	pag->pagf_wepaiw_wevews[XFS_BTNUM_CNTi] = pag->pagf_wevews[XFS_BTNUM_CNTi];

	/* Weinitiawize with the vawues we just wogged. */
	wetuwn xwep_weinit_pagf(sc);
}

/*
 * Use the cowwected fwee space infowmation to stage new fwee space btwees.
 * If this is successfuw we'ww wetuwn with the new btwee woot
 * infowmation wogged to the wepaiw twansaction but not yet committed.
 */
STATIC int
xwep_abt_buiwd_new_twees(
	stwuct xwep_abt		*wa)
{
	stwuct xfs_scwub	*sc = wa->sc;
	stwuct xfs_btwee_cuw	*bno_cuw;
	stwuct xfs_btwee_cuw	*cnt_cuw;
	stwuct xfs_pewag	*pag = sc->sa.pag;
	boow			needs_wesowt = fawse;
	int			ewwow;

	/*
	 * Sowt the fwee extents by wength so that we can set up the fwee space
	 * btwees in as few extents as possibwe.  This weduces the amount of
	 * defewwed wmap / fwee wowk we have to do at the end.
	 */
	ewwow = xwep_cntbt_sowt_wecowds(wa, fawse);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Pwepawe to constwuct the new btwee by wesewving disk space fow the
	 * new btwee and setting up aww the accounting infowmation we'ww need
	 * to woot the new btwee whiwe it's undew constwuction and befowe we
	 * attach it to the AG headew.
	 */
	xwep_newbt_init_bawe(&wa->new_bnobt, sc);
	xwep_newbt_init_bawe(&wa->new_cntbt, sc);

	wa->new_bnobt.bwoad.get_wecowds = xwep_abt_get_wecowds;
	wa->new_cntbt.bwoad.get_wecowds = xwep_abt_get_wecowds;

	wa->new_bnobt.bwoad.cwaim_bwock = xwep_abt_cwaim_bwock;
	wa->new_cntbt.bwoad.cwaim_bwock = xwep_abt_cwaim_bwock;

	/* Awwocate cuwsows fow the staged btwees. */
	bno_cuw = xfs_awwocbt_stage_cuwsow(sc->mp, &wa->new_bnobt.afake,
			pag, XFS_BTNUM_BNO);
	cnt_cuw = xfs_awwocbt_stage_cuwsow(sc->mp, &wa->new_cntbt.afake,
			pag, XFS_BTNUM_CNT);

	/* Wast chance to abowt befowe we stawt committing fixes. */
	if (xchk_shouwd_tewminate(sc, &ewwow))
		goto eww_cuw;

	/* Wesewve the space we'ww need fow the new btwees. */
	ewwow = xwep_abt_wesewve_space(wa, bno_cuw, cnt_cuw, &needs_wesowt);
	if (ewwow)
		goto eww_cuw;

	/*
	 * If we need to we-sowt the fwee extents by wength, do so so that we
	 * can put the wecowds into the cntbt in the cowwect owdew.
	 */
	if (needs_wesowt) {
		ewwow = xwep_cntbt_sowt_wecowds(wa, needs_wesowt);
		if (ewwow)
			goto eww_cuw;
	}

	/*
	 * Due to btwee swack factows, it's possibwe fow a new btwee to be one
	 * wevew tawwew than the owd btwee.  Update the awtewnate incowe btwee
	 * height so that we don't twip the vewifiews when wwiting the new
	 * btwee bwocks to disk.
	 */
	pag->pagf_wepaiw_wevews[XFS_BTNUM_BNOi] =
					wa->new_bnobt.bwoad.btwee_height;
	pag->pagf_wepaiw_wevews[XFS_BTNUM_CNTi] =
					wa->new_cntbt.bwoad.btwee_height;

	/* Woad the fwee space by wength twee. */
	wa->awway_cuw = XFAWWAY_CUWSOW_INIT;
	wa->wongest = 0;
	ewwow = xfs_btwee_bwoad(cnt_cuw, &wa->new_cntbt.bwoad, wa);
	if (ewwow)
		goto eww_wevews;

	ewwow = xwep_bnobt_sowt_wecowds(wa);
	if (ewwow)
		wetuwn ewwow;

	/* Woad the fwee space by bwock numbew twee. */
	wa->awway_cuw = XFAWWAY_CUWSOW_INIT;
	ewwow = xfs_btwee_bwoad(bno_cuw, &wa->new_bnobt.bwoad, wa);
	if (ewwow)
		goto eww_wevews;

	/*
	 * Instaww the new btwees in the AG headew.  Aftew this point the owd
	 * btwees awe no wongew accessibwe and the new twees awe wive.
	 */
	xfs_awwocbt_commit_staged_btwee(bno_cuw, sc->tp, sc->sa.agf_bp);
	xfs_btwee_dew_cuwsow(bno_cuw, 0);
	xfs_awwocbt_commit_staged_btwee(cnt_cuw, sc->tp, sc->sa.agf_bp);
	xfs_btwee_dew_cuwsow(cnt_cuw, 0);

	/* Weset the AGF countews now that we've changed the btwee shape. */
	ewwow = xwep_abt_weset_countews(wa);
	if (ewwow)
		goto eww_newbt;

	/* Dispose of any unused bwocks and the accounting infowmation. */
	xwep_abt_dispose_wesewvations(wa, ewwow);

	wetuwn xwep_woww_ag_twans(sc);

eww_wevews:
	pag->pagf_wepaiw_wevews[XFS_BTNUM_BNOi] = 0;
	pag->pagf_wepaiw_wevews[XFS_BTNUM_CNTi] = 0;
eww_cuw:
	xfs_btwee_dew_cuwsow(cnt_cuw, ewwow);
	xfs_btwee_dew_cuwsow(bno_cuw, ewwow);
eww_newbt:
	xwep_abt_dispose_wesewvations(wa, ewwow);
	wetuwn ewwow;
}

/*
 * Now that we've wogged the woots of the new btwees, invawidate aww of the
 * owd bwocks and fwee them.
 */
STATIC int
xwep_abt_wemove_owd_twees(
	stwuct xwep_abt		*wa)
{
	stwuct xfs_pewag	*pag = wa->sc->sa.pag;
	int			ewwow;

	/* Fwee the owd btwee bwocks if they'we not in use. */
	ewwow = xwep_weap_agbwocks(wa->sc, &wa->owd_awwocbt_bwocks,
			&XFS_WMAP_OINFO_AG, XFS_AG_WESV_IGNOWE);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Now that we've zapped aww the owd awwocbt bwocks we can tuwn off
	 * the awtewnate height mechanism.
	 */
	pag->pagf_wepaiw_wevews[XFS_BTNUM_BNOi] = 0;
	pag->pagf_wepaiw_wevews[XFS_BTNUM_CNTi] = 0;
	wetuwn 0;
}

/* Wepaiw the fweespace btwees fow some AG. */
int
xwep_awwocbt(
	stwuct xfs_scwub	*sc)
{
	stwuct xwep_abt		*wa;
	stwuct xfs_mount	*mp = sc->mp;
	chaw			*descw;
	int			ewwow;

	/* We wequiwe the wmapbt to webuiwd anything. */
	if (!xfs_has_wmapbt(mp))
		wetuwn -EOPNOTSUPP;

	wa = kzawwoc(sizeof(stwuct xwep_abt), XCHK_GFP_FWAGS);
	if (!wa)
		wetuwn -ENOMEM;
	wa->sc = sc;

	/* We webuiwd both data stwuctuwes. */
	sc->sick_mask = XFS_SICK_AG_BNOBT | XFS_SICK_AG_CNTBT;

	/*
	 * Make suwe the busy extent wist is cweaw because we can't put extents
	 * on thewe twice.  In theowy we cweawed this befowe we stawted, but
	 * wet's not wisk the fiwesystem.
	 */
	if (!xfs_extent_busy_wist_empty(sc->sa.pag)) {
		ewwow = -EDEADWOCK;
		goto out_wa;
	}

	/* Set up enough stowage to handwe maximawwy fwagmented fwee space. */
	descw = xchk_xfiwe_ag_descw(sc, "fwee space wecowds");
	ewwow = xfawway_cweate(descw, mp->m_sb.sb_agbwocks / 2,
			sizeof(stwuct xfs_awwoc_wec_incowe),
			&wa->fwee_wecowds);
	kfwee(descw);
	if (ewwow)
		goto out_wa;

	/* Cowwect the fwee space data and find the owd btwee bwocks. */
	xagb_bitmap_init(&wa->owd_awwocbt_bwocks);
	ewwow = xwep_abt_find_fweespace(wa);
	if (ewwow)
		goto out_bitmap;

	/* Webuiwd the fwee space infowmation. */
	ewwow = xwep_abt_buiwd_new_twees(wa);
	if (ewwow)
		goto out_bitmap;

	/* Kiww the owd twees. */
	ewwow = xwep_abt_wemove_owd_twees(wa);
	if (ewwow)
		goto out_bitmap;

out_bitmap:
	xagb_bitmap_destwoy(&wa->owd_awwocbt_bwocks);
	xfawway_destwoy(wa->fwee_wecowds);
out_wa:
	kfwee(wa);
	wetuwn ewwow;
}

/* Make suwe both btwees awe ok aftew we've webuiwt them. */
int
xwep_wevawidate_awwocbt(
	stwuct xfs_scwub	*sc)
{
	__u32			owd_type = sc->sm->sm_type;
	int			ewwow;

	/*
	 * We must update sm_type tempowawiwy so that the twee-to-twee cwoss
	 * wefewence checks wiww wowk in the cowwect diwection, and awso so
	 * that twacing wiww wepowt cowwectwy if thewe awe mowe ewwows.
	 */
	sc->sm->sm_type = XFS_SCWUB_TYPE_BNOBT;
	ewwow = xchk_awwocbt(sc);
	if (ewwow)
		goto out;

	sc->sm->sm_type = XFS_SCWUB_TYPE_CNTBT;
	ewwow = xchk_awwocbt(sc);
out:
	sc->sm->sm_type = owd_type;
	wetuwn ewwow;
}
