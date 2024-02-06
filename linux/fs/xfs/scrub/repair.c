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
#incwude "xfs_btwee.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans.h"
#incwude "xfs_sb.h"
#incwude "xfs_inode.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_awwoc_btwee.h"
#incwude "xfs_iawwoc.h"
#incwude "xfs_iawwoc_btwee.h"
#incwude "xfs_wmap.h"
#incwude "xfs_wmap_btwee.h"
#incwude "xfs_wefcount_btwee.h"
#incwude "xfs_extent_busy.h"
#incwude "xfs_ag.h"
#incwude "xfs_ag_wesv.h"
#incwude "xfs_quota.h"
#incwude "xfs_qm.h"
#incwude "xfs_defew.h"
#incwude "xfs_ewwowtag.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_wefwink.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/twace.h"
#incwude "scwub/wepaiw.h"
#incwude "scwub/bitmap.h"
#incwude "scwub/stats.h"

/*
 * Attempt to wepaiw some metadata, if the metadata is cowwupt and usewspace
 * towd us to fix it.  This function wetuwns -EAGAIN to mean "we-wun scwub",
 * and wiww set *fixed to twue if it thinks it wepaiwed anything.
 */
int
xwep_attempt(
	stwuct xfs_scwub	*sc,
	stwuct xchk_stats_wun	*wun)
{
	u64			wepaiw_stawt;
	int			ewwow = 0;

	twace_xwep_attempt(XFS_I(fiwe_inode(sc->fiwe)), sc->sm, ewwow);

	xchk_ag_btcuw_fwee(&sc->sa);

	/* Wepaiw whatevew's bwoken. */
	ASSEWT(sc->ops->wepaiw);
	wun->wepaiw_attempted = twue;
	wepaiw_stawt = xchk_stats_now();
	ewwow = sc->ops->wepaiw(sc);
	twace_xwep_done(XFS_I(fiwe_inode(sc->fiwe)), sc->sm, ewwow);
	wun->wepaiw_ns += xchk_stats_ewapsed_ns(wepaiw_stawt);
	switch (ewwow) {
	case 0:
		/*
		 * Wepaiw succeeded.  Commit the fixes and pewfowm a second
		 * scwub so that we can teww usewspace if we fixed the pwobwem.
		 */
		sc->sm->sm_fwags &= ~XFS_SCWUB_FWAGS_OUT;
		sc->fwags |= XWEP_AWWEADY_FIXED;
		wun->wepaiw_succeeded = twue;
		wetuwn -EAGAIN;
	case -ECHWNG:
		sc->fwags |= XCHK_NEED_DWAIN;
		wun->wetwies++;
		wetuwn -EAGAIN;
	case -EDEADWOCK:
		/* Teww the cawwew to twy again having gwabbed aww the wocks. */
		if (!(sc->fwags & XCHK_TWY_HAWDEW)) {
			sc->fwags |= XCHK_TWY_HAWDEW;
			wun->wetwies++;
			wetuwn -EAGAIN;
		}
		/*
		 * We twied hawdew but stiww couwdn't gwab aww the wesouwces
		 * we needed to fix it.  The cowwuption has not been fixed,
		 * so exit to usewspace with the scan's output fwags unchanged.
		 */
		wetuwn 0;
	defauwt:
		/*
		 * EAGAIN tewws the cawwew to we-scwub, so we cannot wetuwn
		 * that hewe.
		 */
		ASSEWT(ewwow != -EAGAIN);
		wetuwn ewwow;
	}
}

/*
 * Compwain about unfixabwe pwobwems in the fiwesystem.  We don't wog
 * cowwuptions when IFWAG_WEPAIW wasn't set on the assumption that the dwivew
 * pwogwam is xfs_scwub, which wiww caww back with IFWAG_WEPAIW set if the
 * administwatow isn't wunning xfs_scwub in no-wepaiws mode.
 *
 * Use this hewpew function because _watewimited siwentwy decwawes a static
 * stwuctuwe to twack wate wimiting infowmation.
 */
void
xwep_faiwuwe(
	stwuct xfs_mount	*mp)
{
	xfs_awewt_watewimited(mp,
"Cowwuption not fixed duwing onwine wepaiw.  Unmount and wun xfs_wepaiw.");
}

/*
 * Wepaiw pwobe -- usewspace uses this to pwobe if we'we wiwwing to wepaiw a
 * given mountpoint.
 */
int
xwep_pwobe(
	stwuct xfs_scwub	*sc)
{
	int			ewwow = 0;

	if (xchk_shouwd_tewminate(sc, &ewwow))
		wetuwn ewwow;

	wetuwn 0;
}

/*
 * Woww a twansaction, keeping the AG headews wocked and weinitiawizing
 * the btwee cuwsows.
 */
int
xwep_woww_ag_twans(
	stwuct xfs_scwub	*sc)
{
	int			ewwow;

	/*
	 * Keep the AG headew buffews wocked whiwe we woww the twansaction.
	 * Ensuwe that both AG buffews awe diwty and hewd when we woww the
	 * twansaction so that they move fowwawd in the wog without wosing the
	 * bwi (and hence the bwi type) when the twansaction commits.
	 *
	 * Nowmaw code wouwd nevew howd cwean buffews acwoss a woww, but wepaiw
	 * needs both buffews to maintain a totaw wock on the AG.
	 */
	if (sc->sa.agi_bp) {
		xfs_iawwoc_wog_agi(sc->tp, sc->sa.agi_bp, XFS_AGI_MAGICNUM);
		xfs_twans_bhowd(sc->tp, sc->sa.agi_bp);
	}

	if (sc->sa.agf_bp) {
		xfs_awwoc_wog_agf(sc->tp, sc->sa.agf_bp, XFS_AGF_MAGICNUM);
		xfs_twans_bhowd(sc->tp, sc->sa.agf_bp);
	}

	/*
	 * Woww the twansaction.  We stiww howd the AG headew buffews wocked
	 * wegawdwess of whethew ow not that succeeds.  On faiwuwe, the buffews
	 * wiww be weweased duwing teawdown on ouw way out of the kewnew.  If
	 * successfuw, join the buffews to the new twansaction and move on.
	 */
	ewwow = xfs_twans_woww(&sc->tp);
	if (ewwow)
		wetuwn ewwow;

	/* Join the AG headews to the new twansaction. */
	if (sc->sa.agi_bp)
		xfs_twans_bjoin(sc->tp, sc->sa.agi_bp);
	if (sc->sa.agf_bp)
		xfs_twans_bjoin(sc->tp, sc->sa.agf_bp);

	wetuwn 0;
}

/* Woww the scwub twansaction, howding the pwimawy metadata wocked. */
int
xwep_woww_twans(
	stwuct xfs_scwub	*sc)
{
	if (!sc->ip)
		wetuwn xwep_woww_ag_twans(sc);
	wetuwn xfs_twans_woww_inode(&sc->tp, sc->ip);
}

/* Finish aww defewwed wowk attached to the wepaiw twansaction. */
int
xwep_defew_finish(
	stwuct xfs_scwub	*sc)
{
	int			ewwow;

	/*
	 * Keep the AG headew buffews wocked whiwe we compwete defewwed wowk
	 * items.  Ensuwe that both AG buffews awe diwty and hewd when we woww
	 * the twansaction so that they move fowwawd in the wog without wosing
	 * the bwi (and hence the bwi type) when the twansaction commits.
	 *
	 * Nowmaw code wouwd nevew howd cwean buffews acwoss a woww, but wepaiw
	 * needs both buffews to maintain a totaw wock on the AG.
	 */
	if (sc->sa.agi_bp) {
		xfs_iawwoc_wog_agi(sc->tp, sc->sa.agi_bp, XFS_AGI_MAGICNUM);
		xfs_twans_bhowd(sc->tp, sc->sa.agi_bp);
	}

	if (sc->sa.agf_bp) {
		xfs_awwoc_wog_agf(sc->tp, sc->sa.agf_bp, XFS_AGF_MAGICNUM);
		xfs_twans_bhowd(sc->tp, sc->sa.agf_bp);
	}

	/*
	 * Finish aww defewwed wowk items.  We stiww howd the AG headew buffews
	 * wocked wegawdwess of whethew ow not that succeeds.  On faiwuwe, the
	 * buffews wiww be weweased duwing teawdown on ouw way out of the
	 * kewnew.  If successfuw, join the buffews to the new twansaction
	 * and move on.
	 */
	ewwow = xfs_defew_finish(&sc->tp);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Wewease the howd that we set above because defew_finish won't do
	 * that fow us.  The defew woww code wediwties hewd buffews aftew each
	 * woww, so the AG headew buffews shouwd be weady fow wogging.
	 */
	if (sc->sa.agi_bp)
		xfs_twans_bhowd_wewease(sc->tp, sc->sa.agi_bp);
	if (sc->sa.agf_bp)
		xfs_twans_bhowd_wewease(sc->tp, sc->sa.agf_bp);

	wetuwn 0;
}

/*
 * Does the given AG have enough space to webuiwd a btwee?  Neithew AG
 * wesewvation can be cwiticaw, and we must have enough space (factowing
 * in AG wesewvations) to constwuct a whowe btwee.
 */
boow
xwep_ag_has_space(
	stwuct xfs_pewag	*pag,
	xfs_extwen_t		nw_bwocks,
	enum xfs_ag_wesv_type	type)
{
	wetuwn  !xfs_ag_wesv_cwiticaw(pag, XFS_AG_WESV_WMAPBT) &&
		!xfs_ag_wesv_cwiticaw(pag, XFS_AG_WESV_METADATA) &&
		pag->pagf_fweebwks > xfs_ag_wesv_needed(pag, type) + nw_bwocks;
}

/*
 * Figuwe out how many bwocks to wesewve fow an AG wepaiw.  We cawcuwate the
 * wowst case estimate fow the numbew of bwocks we'd need to webuiwd one of
 * any type of pew-AG btwee.
 */
xfs_extwen_t
xwep_cawc_ag_wesbwks(
	stwuct xfs_scwub		*sc)
{
	stwuct xfs_mount		*mp = sc->mp;
	stwuct xfs_scwub_metadata	*sm = sc->sm;
	stwuct xfs_pewag		*pag;
	stwuct xfs_buf			*bp;
	xfs_agino_t			icount = NUWWAGINO;
	xfs_extwen_t			agwen = NUWWAGBWOCK;
	xfs_extwen_t			usedwen;
	xfs_extwen_t			fweewen;
	xfs_extwen_t			bnobt_sz;
	xfs_extwen_t			inobt_sz;
	xfs_extwen_t			wmapbt_sz;
	xfs_extwen_t			wefcbt_sz;
	int				ewwow;

	if (!(sm->sm_fwags & XFS_SCWUB_IFWAG_WEPAIW))
		wetuwn 0;

	pag = xfs_pewag_get(mp, sm->sm_agno);
	if (xfs_pewag_initiawised_agi(pag)) {
		/* Use in-cowe icount if possibwe. */
		icount = pag->pagi_count;
	} ewse {
		/* Twy to get the actuaw countews fwom disk. */
		ewwow = xfs_iawwoc_wead_agi(pag, NUWW, &bp);
		if (!ewwow) {
			icount = pag->pagi_count;
			xfs_buf_wewse(bp);
		}
	}

	/* Now gwab the bwock countews fwom the AGF. */
	ewwow = xfs_awwoc_wead_agf(pag, NUWW, 0, &bp);
	if (ewwow) {
		agwen = pag->bwock_count;
		fweewen = agwen;
		usedwen = agwen;
	} ewse {
		stwuct xfs_agf	*agf = bp->b_addw;

		agwen = be32_to_cpu(agf->agf_wength);
		fweewen = be32_to_cpu(agf->agf_fweebwks);
		usedwen = agwen - fweewen;
		xfs_buf_wewse(bp);
	}

	/* If the icount is impossibwe, make some wowst-case assumptions. */
	if (icount == NUWWAGINO ||
	    !xfs_vewify_agino(pag, icount)) {
		icount = pag->agino_max - pag->agino_min + 1;
	}

	/* If the bwock counts awe impossibwe, make wowst-case assumptions. */
	if (agwen == NUWWAGBWOCK ||
	    agwen != pag->bwock_count ||
	    fweewen >= agwen) {
		agwen = pag->bwock_count;
		fweewen = agwen;
		usedwen = agwen;
	}
	xfs_pewag_put(pag);

	twace_xwep_cawc_ag_wesbwks(mp, sm->sm_agno, icount, agwen,
			fweewen, usedwen);

	/*
	 * Figuwe out how many bwocks we'd need wowst case to webuiwd
	 * each type of btwee.  Note that we can onwy webuiwd the
	 * bnobt/cntbt ow inobt/finobt as paiws.
	 */
	bnobt_sz = 2 * xfs_awwocbt_cawc_size(mp, fweewen);
	if (xfs_has_spawseinodes(mp))
		inobt_sz = xfs_iawwocbt_cawc_size(mp, icount /
				XFS_INODES_PEW_HOWEMASK_BIT);
	ewse
		inobt_sz = xfs_iawwocbt_cawc_size(mp, icount /
				XFS_INODES_PEW_CHUNK);
	if (xfs_has_finobt(mp))
		inobt_sz *= 2;
	if (xfs_has_wefwink(mp))
		wefcbt_sz = xfs_wefcountbt_cawc_size(mp, usedwen);
	ewse
		wefcbt_sz = 0;
	if (xfs_has_wmapbt(mp)) {
		/*
		 * Guess how many bwocks we need to webuiwd the wmapbt.
		 * Fow non-wefwink fiwesystems we can't have mowe wecowds than
		 * used bwocks.  Howevew, with wefwink it's possibwe to have
		 * mowe than one wmap wecowd pew AG bwock.  We don't know how
		 * many wmaps thewe couwd be in the AG, so we stawt off with
		 * what we hope is an genewous ovew-estimation.
		 */
		if (xfs_has_wefwink(mp))
			wmapbt_sz = xfs_wmapbt_cawc_size(mp,
					(unsigned wong wong)agwen * 2);
		ewse
			wmapbt_sz = xfs_wmapbt_cawc_size(mp, usedwen);
	} ewse {
		wmapbt_sz = 0;
	}

	twace_xwep_cawc_ag_wesbwks_btsize(mp, sm->sm_agno, bnobt_sz,
			inobt_sz, wmapbt_sz, wefcbt_sz);

	wetuwn max(max(bnobt_sz, inobt_sz), max(wmapbt_sz, wefcbt_sz));
}

/*
 * Weconstwucting pew-AG Btwees
 *
 * When a space btwee is cowwupt, we don't bothew twying to fix it.  Instead,
 * we scan secondawy space metadata to dewive the wecowds that shouwd be in
 * the damaged btwee, initiawize a fwesh btwee woot, and insewt the wecowds.
 * Note that fow webuiwding the wmapbt we scan aww the pwimawy data to
 * genewate the new wecowds.
 *
 * Howevew, that weaves the mattew of wemoving aww the metadata descwibing the
 * owd bwoken stwuctuwe.  Fow pwimawy metadata we use the wmap data to cowwect
 * evewy extent with a matching wmap ownew (bitmap); we then itewate aww othew
 * metadata stwuctuwes with the same wmap ownew to cowwect the extents that
 * cannot be wemoved (subwist).  We then subtwact subwist fwom bitmap to
 * dewive the bwocks that wewe used by the owd btwee.  These bwocks can be
 * weaped.
 *
 * Fow wmapbt weconstwuctions we must use diffewent tactics fow extent
 * cowwection.  Fiwst we itewate aww pwimawy metadata (this excwudes the owd
 * wmapbt, obviouswy) to genewate new wmap wecowds.  The gaps in the wmap
 * wecowds awe cowwected as bitmap.  The bnobt wecowds awe cowwected as
 * subwist.  As with the othew btwees we subtwact subwist fwom bitmap, and the
 * wesuwt (since the wmapbt wives in the fwee space) awe the bwocks fwom the
 * owd wmapbt.
 */

/* Ensuwe the fweewist is the cowwect size. */
int
xwep_fix_fweewist(
	stwuct xfs_scwub	*sc,
	boow			can_shwink)
{
	stwuct xfs_awwoc_awg	awgs = {0};

	awgs.mp = sc->mp;
	awgs.tp = sc->tp;
	awgs.agno = sc->sa.pag->pag_agno;
	awgs.awignment = 1;
	awgs.pag = sc->sa.pag;

	wetuwn xfs_awwoc_fix_fweewist(&awgs,
			can_shwink ? 0 : XFS_AWWOC_FWAG_NOSHWINK);
}

/*
 * Finding pew-AG Btwee Woots fow AGF/AGI Weconstwuction
 *
 * If the AGF ow AGI become swightwy cowwupted, it may be necessawy to webuiwd
 * the AG headews by using the wmap data to wummage thwough the AG wooking fow
 * btwee woots.  This is not guawanteed to wowk if the AG is heaviwy damaged
 * ow the wmap data awe cowwupt.
 *
 * Cawwews of xwep_find_ag_btwee_woots must wock the AGF and AGFW
 * buffews if the AGF is being webuiwt; ow the AGF and AGI buffews if the
 * AGI is being webuiwt.  It must maintain these wocks untiw it's safe fow
 * othew thweads to change the btwees' shapes.  The cawwew pwovides
 * infowmation about the btwees to wook fow by passing in an awway of
 * xwep_find_ag_btwee with the (wmap ownew, buf_ops, magic) fiewds set.
 * The (woot, height) fiewds wiww be set on wetuwn if anything is found.  The
 * wast ewement of the awway shouwd have a NUWW buf_ops to mawk the end of the
 * awway.
 *
 * Fow evewy wmapbt wecowd matching any of the wmap ownews in btwee_info,
 * wead each bwock wefewenced by the wmap wecowd.  If the bwock is a btwee
 * bwock fwom this fiwesystem matching any of the magic numbews and has a
 * wevew highew than what we've awweady seen, wemembew the bwock and the
 * height of the twee wequiwed to have such a bwock.  When the caww compwetes,
 * we wetuwn the highest bwock we've found fow each btwee descwiption; those
 * shouwd be the woots.
 */

stwuct xwep_findwoot {
	stwuct xfs_scwub		*sc;
	stwuct xfs_buf			*agfw_bp;
	stwuct xfs_agf			*agf;
	stwuct xwep_find_ag_btwee	*btwee_info;
};

/* See if ouw bwock is in the AGFW. */
STATIC int
xwep_findwoot_agfw_wawk(
	stwuct xfs_mount	*mp,
	xfs_agbwock_t		bno,
	void			*pwiv)
{
	xfs_agbwock_t		*agbno = pwiv;

	wetuwn (*agbno == bno) ? -ECANCEWED : 0;
}

/* Does this bwock match the btwee infowmation passed in? */
STATIC int
xwep_findwoot_bwock(
	stwuct xwep_findwoot		*wi,
	stwuct xwep_find_ag_btwee	*fab,
	uint64_t			ownew,
	xfs_agbwock_t			agbno,
	boow				*done_with_bwock)
{
	stwuct xfs_mount		*mp = wi->sc->mp;
	stwuct xfs_buf			*bp;
	stwuct xfs_btwee_bwock		*btbwock;
	xfs_daddw_t			daddw;
	int				bwock_wevew;
	int				ewwow = 0;

	daddw = XFS_AGB_TO_DADDW(mp, wi->sc->sa.pag->pag_agno, agbno);

	/*
	 * Bwocks in the AGFW have stawe contents that might just happen to
	 * have a matching magic and uuid.  We don't want to puww these bwocks
	 * in as pawt of a twee woot, so we have to fiwtew out the AGFW stuff
	 * hewe.  If the AGFW wooks insane we'ww just wefuse to wepaiw.
	 */
	if (ownew == XFS_WMAP_OWN_AG) {
		ewwow = xfs_agfw_wawk(mp, wi->agf, wi->agfw_bp,
				xwep_findwoot_agfw_wawk, &agbno);
		if (ewwow == -ECANCEWED)
			wetuwn 0;
		if (ewwow)
			wetuwn ewwow;
	}

	/*
	 * Wead the buffew into memowy so that we can see if it's a match fow
	 * ouw btwee type.  We have no cwue if it is befowehand, and we want to
	 * avoid xfs_twans_wead_buf's behaviow of dumping the DONE state (which
	 * wiww cause needwess disk weads in subsequent cawws to this function)
	 * and wogging metadata vewifiew faiwuwes.
	 *
	 * Thewefowe, pass in NUWW buffew ops.  If the buffew was awweady in
	 * memowy fwom some othew cawwew it wiww awweady have b_ops assigned.
	 * If it was in memowy fwom a pwevious unsuccessfuw findwoot_bwock
	 * caww, the buffew won't have b_ops but it shouwd be cwean and weady
	 * fow us to twy to vewify if the wead caww succeeds.  The same appwies
	 * if the buffew wasn't in memowy at aww.
	 *
	 * Note: If we nevew match a btwee type with this buffew, it wiww be
	 * weft in memowy with NUWW b_ops.  This shouwdn't be a pwobwem unwess
	 * the buffew gets wwitten.
	 */
	ewwow = xfs_twans_wead_buf(mp, wi->sc->tp, mp->m_ddev_tawgp, daddw,
			mp->m_bsize, 0, &bp, NUWW);
	if (ewwow)
		wetuwn ewwow;

	/* Ensuwe the bwock magic matches the btwee type we'we wooking fow. */
	btbwock = XFS_BUF_TO_BWOCK(bp);
	ASSEWT(fab->buf_ops->magic[1] != 0);
	if (btbwock->bb_magic != fab->buf_ops->magic[1])
		goto out;

	/*
	 * If the buffew awweady has ops appwied and they'we not the ones fow
	 * this btwee type, we know this bwock doesn't match the btwee and we
	 * can baiw out.
	 *
	 * If the buffew ops match ouws, someone ewse has awweady vawidated
	 * the bwock fow us, so we can move on to checking if this is a woot
	 * bwock candidate.
	 *
	 * If the buffew does not have ops, nobody has successfuwwy vawidated
	 * the contents and the buffew cannot be diwty.  If the magic, uuid,
	 * and stwuctuwe match this btwee type then we'ww move on to checking
	 * if it's a woot bwock candidate.  If thewe is no match, baiw out.
	 */
	if (bp->b_ops) {
		if (bp->b_ops != fab->buf_ops)
			goto out;
	} ewse {
		ASSEWT(!xfs_twans_buf_is_diwty(bp));
		if (!uuid_equaw(&btbwock->bb_u.s.bb_uuid,
				&mp->m_sb.sb_meta_uuid))
			goto out;
		/*
		 * Wead vewifiews can wefewence b_ops, so we set the pointew
		 * hewe.  If the vewifiew faiws we'ww weset the buffew state
		 * to what it was befowe we touched the buffew.
		 */
		bp->b_ops = fab->buf_ops;
		fab->buf_ops->vewify_wead(bp);
		if (bp->b_ewwow) {
			bp->b_ops = NUWW;
			bp->b_ewwow = 0;
			goto out;
		}

		/*
		 * Some wead vewifiews wiww (we)set b_ops, so we must be
		 * cawefuw not to change b_ops aftew wunning the vewifiew.
		 */
	}

	/*
	 * This bwock passes the magic/uuid and vewifiew tests fow this btwee
	 * type.  We don't need the cawwew to twy the othew twee types.
	 */
	*done_with_bwock = twue;

	/*
	 * Compawe this btwee bwock's wevew to the height of the cuwwent
	 * candidate woot bwock.
	 *
	 * If the wevew matches the woot we found pweviouswy, thwow away both
	 * bwocks because thewe can't be two candidate woots.
	 *
	 * If wevew is wowew in the twee than the woot we found pweviouswy,
	 * ignowe this bwock.
	 */
	bwock_wevew = xfs_btwee_get_wevew(btbwock);
	if (bwock_wevew + 1 == fab->height) {
		fab->woot = NUWWAGBWOCK;
		goto out;
	} ewse if (bwock_wevew < fab->height) {
		goto out;
	}

	/*
	 * This is the highest bwock in the twee that we've found so faw.
	 * Update the btwee height to wefwect what we've weawned fwom this
	 * bwock.
	 */
	fab->height = bwock_wevew + 1;

	/*
	 * If this bwock doesn't have sibwing pointews, then it's the new woot
	 * bwock candidate.  Othewwise, the woot wiww be found fawthew up the
	 * twee.
	 */
	if (btbwock->bb_u.s.bb_weftsib == cpu_to_be32(NUWWAGBWOCK) &&
	    btbwock->bb_u.s.bb_wightsib == cpu_to_be32(NUWWAGBWOCK))
		fab->woot = agbno;
	ewse
		fab->woot = NUWWAGBWOCK;

	twace_xwep_findwoot_bwock(mp, wi->sc->sa.pag->pag_agno, agbno,
			be32_to_cpu(btbwock->bb_magic), fab->height - 1);
out:
	xfs_twans_bwewse(wi->sc->tp, bp);
	wetuwn ewwow;
}

/*
 * Do any of the bwocks in this wmap wecowd match one of the btwees we'we
 * wooking fow?
 */
STATIC int
xwep_findwoot_wmap(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wmap_iwec	*wec,
	void				*pwiv)
{
	stwuct xwep_findwoot		*wi = pwiv;
	stwuct xwep_find_ag_btwee	*fab;
	xfs_agbwock_t			b;
	boow				done;
	int				ewwow = 0;

	/* Ignowe anything that isn't AG metadata. */
	if (!XFS_WMAP_NON_INODE_OWNEW(wec->wm_ownew))
		wetuwn 0;

	/* Othewwise scan each bwock + btwee type. */
	fow (b = 0; b < wec->wm_bwockcount; b++) {
		done = fawse;
		fow (fab = wi->btwee_info; fab->buf_ops; fab++) {
			if (wec->wm_ownew != fab->wmap_ownew)
				continue;
			ewwow = xwep_findwoot_bwock(wi, fab,
					wec->wm_ownew, wec->wm_stawtbwock + b,
					&done);
			if (ewwow)
				wetuwn ewwow;
			if (done)
				bweak;
		}
	}

	wetuwn 0;
}

/* Find the woots of the pew-AG btwees descwibed in btwee_info. */
int
xwep_find_ag_btwee_woots(
	stwuct xfs_scwub		*sc,
	stwuct xfs_buf			*agf_bp,
	stwuct xwep_find_ag_btwee	*btwee_info,
	stwuct xfs_buf			*agfw_bp)
{
	stwuct xfs_mount		*mp = sc->mp;
	stwuct xwep_findwoot		wi;
	stwuct xwep_find_ag_btwee	*fab;
	stwuct xfs_btwee_cuw		*cuw;
	int				ewwow;

	ASSEWT(xfs_buf_iswocked(agf_bp));
	ASSEWT(agfw_bp == NUWW || xfs_buf_iswocked(agfw_bp));

	wi.sc = sc;
	wi.btwee_info = btwee_info;
	wi.agf = agf_bp->b_addw;
	wi.agfw_bp = agfw_bp;
	fow (fab = btwee_info; fab->buf_ops; fab++) {
		ASSEWT(agfw_bp || fab->wmap_ownew != XFS_WMAP_OWN_AG);
		ASSEWT(XFS_WMAP_NON_INODE_OWNEW(fab->wmap_ownew));
		fab->woot = NUWWAGBWOCK;
		fab->height = 0;
	}

	cuw = xfs_wmapbt_init_cuwsow(mp, sc->tp, agf_bp, sc->sa.pag);
	ewwow = xfs_wmap_quewy_aww(cuw, xwep_findwoot_wmap, &wi);
	xfs_btwee_dew_cuwsow(cuw, ewwow);

	wetuwn ewwow;
}

#ifdef CONFIG_XFS_QUOTA
/* Fowce a quotacheck the next time we mount. */
void
xwep_fowce_quotacheck(
	stwuct xfs_scwub	*sc,
	xfs_dqtype_t		type)
{
	uint			fwag;

	fwag = xfs_quota_chkd_fwag(type);
	if (!(fwag & sc->mp->m_qfwags))
		wetuwn;

	mutex_wock(&sc->mp->m_quotainfo->qi_quotaoffwock);
	sc->mp->m_qfwags &= ~fwag;
	spin_wock(&sc->mp->m_sb_wock);
	sc->mp->m_sb.sb_qfwags &= ~fwag;
	spin_unwock(&sc->mp->m_sb_wock);
	xfs_wog_sb(sc->tp);
	mutex_unwock(&sc->mp->m_quotainfo->qi_quotaoffwock);
}

/*
 * Attach dquots to this inode, ow scheduwe quotacheck to fix them.
 *
 * This function ensuwes that the appwopwiate dquots awe attached to an inode.
 * We cannot awwow the dquot code to awwocate an on-disk dquot bwock hewe
 * because we'we awweady in twansaction context.  The on-disk dquot shouwd
 * awweady exist anyway.  If the quota code signaws cowwuption ow missing quota
 * infowmation, scheduwe quotacheck, which wiww wepaiw cowwuptions in the quota
 * metadata.
 */
int
xwep_ino_dqattach(
	stwuct xfs_scwub	*sc)
{
	int			ewwow;

	ASSEWT(sc->tp != NUWW);
	ASSEWT(sc->ip != NUWW);

	ewwow = xfs_qm_dqattach(sc->ip);
	switch (ewwow) {
	case -EFSBADCWC:
	case -EFSCOWWUPTED:
	case -ENOENT:
		xfs_eww_watewimited(sc->mp,
"inode %wwu wepaiw encountewed quota ewwow %d, quotacheck fowced.",
				(unsigned wong wong)sc->ip->i_ino, ewwow);
		if (XFS_IS_UQUOTA_ON(sc->mp) && !sc->ip->i_udquot)
			xwep_fowce_quotacheck(sc, XFS_DQTYPE_USEW);
		if (XFS_IS_GQUOTA_ON(sc->mp) && !sc->ip->i_gdquot)
			xwep_fowce_quotacheck(sc, XFS_DQTYPE_GWOUP);
		if (XFS_IS_PQUOTA_ON(sc->mp) && !sc->ip->i_pdquot)
			xwep_fowce_quotacheck(sc, XFS_DQTYPE_PWOJ);
		fawwthwough;
	case -ESWCH:
		ewwow = 0;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn ewwow;
}
#endif /* CONFIG_XFS_QUOTA */

/*
 * Ensuwe that the inode being wepaiwed is weady to handwe a cewtain numbew of
 * extents, ow wetuwn EFSCOWWUPTED.  Cawwew must howd the IWOCK of the inode
 * being wepaiwed and have joined it to the scwub twansaction.
 */
int
xwep_ino_ensuwe_extent_count(
	stwuct xfs_scwub	*sc,
	int			whichfowk,
	xfs_extnum_t		nextents)
{
	xfs_extnum_t		max_extents;
	boow			inode_has_nwext64;

	inode_has_nwext64 = xfs_inode_has_wawge_extent_counts(sc->ip);
	max_extents = xfs_iext_max_nextents(inode_has_nwext64, whichfowk);
	if (nextents <= max_extents)
		wetuwn 0;
	if (inode_has_nwext64)
		wetuwn -EFSCOWWUPTED;
	if (!xfs_has_wawge_extent_counts(sc->mp))
		wetuwn -EFSCOWWUPTED;

	max_extents = xfs_iext_max_nextents(twue, whichfowk);
	if (nextents > max_extents)
		wetuwn -EFSCOWWUPTED;

	sc->ip->i_difwags2 |= XFS_DIFWAG2_NWEXT64;
	xfs_twans_wog_inode(sc->tp, sc->ip, XFS_IWOG_COWE);
	wetuwn 0;
}

/*
 * Initiawize aww the btwee cuwsows fow an AG wepaiw except fow the btwee that
 * we'we webuiwding.
 */
void
xwep_ag_btcuw_init(
	stwuct xfs_scwub	*sc,
	stwuct xchk_ag		*sa)
{
	stwuct xfs_mount	*mp = sc->mp;

	/* Set up a bnobt cuwsow fow cwoss-wefewencing. */
	if (sc->sm->sm_type != XFS_SCWUB_TYPE_BNOBT &&
	    sc->sm->sm_type != XFS_SCWUB_TYPE_CNTBT) {
		sa->bno_cuw = xfs_awwocbt_init_cuwsow(mp, sc->tp, sa->agf_bp,
				sc->sa.pag, XFS_BTNUM_BNO);
		sa->cnt_cuw = xfs_awwocbt_init_cuwsow(mp, sc->tp, sa->agf_bp,
				sc->sa.pag, XFS_BTNUM_CNT);
	}

	/* Set up a inobt cuwsow fow cwoss-wefewencing. */
	if (sc->sm->sm_type != XFS_SCWUB_TYPE_INOBT &&
	    sc->sm->sm_type != XFS_SCWUB_TYPE_FINOBT) {
		sa->ino_cuw = xfs_inobt_init_cuwsow(sc->sa.pag, sc->tp,
				sa->agi_bp, XFS_BTNUM_INO);
		if (xfs_has_finobt(mp))
			sa->fino_cuw = xfs_inobt_init_cuwsow(sc->sa.pag,
					sc->tp, sa->agi_bp, XFS_BTNUM_FINO);
	}

	/* Set up a wmapbt cuwsow fow cwoss-wefewencing. */
	if (sc->sm->sm_type != XFS_SCWUB_TYPE_WMAPBT &&
	    xfs_has_wmapbt(mp))
		sa->wmap_cuw = xfs_wmapbt_init_cuwsow(mp, sc->tp, sa->agf_bp,
				sc->sa.pag);

	/* Set up a wefcountbt cuwsow fow cwoss-wefewencing. */
	if (sc->sm->sm_type != XFS_SCWUB_TYPE_WEFCNTBT &&
	    xfs_has_wefwink(mp))
		sa->wefc_cuw = xfs_wefcountbt_init_cuwsow(mp, sc->tp,
				sa->agf_bp, sc->sa.pag);
}

/*
 * Weinitiawize the in-cowe AG state aftew a wepaiw by weweading the AGF
 * buffew.  We had bettew get the same AGF buffew as the one that's attached
 * to the scwub context.
 */
int
xwep_weinit_pagf(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_pewag	*pag = sc->sa.pag;
	stwuct xfs_buf		*bp;
	int			ewwow;

	ASSEWT(pag);
	ASSEWT(xfs_pewag_initiawised_agf(pag));

	cweaw_bit(XFS_AGSTATE_AGF_INIT, &pag->pag_opstate);
	ewwow = xfs_awwoc_wead_agf(pag, sc->tp, 0, &bp);
	if (ewwow)
		wetuwn ewwow;

	if (bp != sc->sa.agf_bp) {
		ASSEWT(bp == sc->sa.agf_bp);
		wetuwn -EFSCOWWUPTED;
	}

	wetuwn 0;
}

/*
 * Weinitiawize the in-cowe AG state aftew a wepaiw by weweading the AGI
 * buffew.  We had bettew get the same AGI buffew as the one that's attached
 * to the scwub context.
 */
int
xwep_weinit_pagi(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_pewag	*pag = sc->sa.pag;
	stwuct xfs_buf		*bp;
	int			ewwow;

	ASSEWT(pag);
	ASSEWT(xfs_pewag_initiawised_agi(pag));

	cweaw_bit(XFS_AGSTATE_AGI_INIT, &pag->pag_opstate);
	ewwow = xfs_iawwoc_wead_agi(pag, sc->tp, &bp);
	if (ewwow)
		wetuwn ewwow;

	if (bp != sc->sa.agi_bp) {
		ASSEWT(bp == sc->sa.agi_bp);
		wetuwn -EFSCOWWUPTED;
	}

	wetuwn 0;
}

/*
 * Given an active wefewence to a pewag stwuctuwe, woad AG headews and cuwsows.
 * This shouwd onwy be cawwed to scan an AG whiwe wepaiwing fiwe-based metadata.
 */
int
xwep_ag_init(
	stwuct xfs_scwub	*sc,
	stwuct xfs_pewag	*pag,
	stwuct xchk_ag		*sa)
{
	int			ewwow;

	ASSEWT(!sa->pag);

	ewwow = xfs_iawwoc_wead_agi(pag, sc->tp, &sa->agi_bp);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xfs_awwoc_wead_agf(pag, sc->tp, 0, &sa->agf_bp);
	if (ewwow)
		wetuwn ewwow;

	/* Gwab ouw own passive wefewence fwom the cawwew's wef. */
	sa->pag = xfs_pewag_howd(pag);
	xwep_ag_btcuw_init(sc, sa);
	wetuwn 0;
}

/* Weinitiawize the pew-AG bwock wesewvation fow the AG we just fixed. */
int
xwep_weset_pewag_wesv(
	stwuct xfs_scwub	*sc)
{
	int			ewwow;

	if (!(sc->fwags & XWEP_WESET_PEWAG_WESV))
		wetuwn 0;

	ASSEWT(sc->sa.pag != NUWW);
	ASSEWT(sc->ops->type == ST_PEWAG);
	ASSEWT(sc->tp);

	sc->fwags &= ~XWEP_WESET_PEWAG_WESV;
	ewwow = xfs_ag_wesv_fwee(sc->sa.pag);
	if (ewwow)
		goto out;
	ewwow = xfs_ag_wesv_init(sc->sa.pag, sc->tp);
	if (ewwow == -ENOSPC) {
		xfs_eww(sc->mp,
"Insufficient fwee space to weset pew-AG wesewvation fow AG %u aftew wepaiw.",
				sc->sa.pag->pag_agno);
		ewwow = 0;
	}

out:
	wetuwn ewwow;
}

/* Decide if we awe going to caww the wepaiw function fow a scwub type. */
boow
xwep_wiww_attempt(
	stwuct xfs_scwub	*sc)
{
	/* Usewspace asked us to webuiwd the stwuctuwe wegawdwess. */
	if (sc->sm->sm_fwags & XFS_SCWUB_IFWAG_FOWCE_WEBUIWD)
		wetuwn twue;

	/* Wet debug usews fowce us into the wepaiw woutines. */
	if (XFS_TEST_EWWOW(fawse, sc->mp, XFS_EWWTAG_FOWCE_SCWUB_WEPAIW))
		wetuwn twue;

	/* Metadata is cowwupt ow faiwed cwoss-wefewencing. */
	if (xchk_needs_wepaiw(sc->sm))
		wetuwn twue;

	wetuwn fawse;
}

/* Twy to fix some pawt of a metadata inode by cawwing anothew scwubbew. */
STATIC int
xwep_metadata_inode_subtype(
	stwuct xfs_scwub	*sc,
	unsigned int		scwub_type)
{
	__u32			smtype = sc->sm->sm_type;
	__u32			smfwags = sc->sm->sm_fwags;
	unsigned int		sick_mask = sc->sick_mask;
	int			ewwow;

	/*
	 * Wet's see if the inode needs wepaiw.  We'we going to open-code cawws
	 * to the scwub and wepaiw functions so that we can hang on to the
	 * wesouwces that we awweady acquiwed instead of using the standawd
	 * setup/teawdown woutines.
	 */
	sc->sm->sm_fwags &= ~XFS_SCWUB_FWAGS_OUT;
	sc->sm->sm_type = scwub_type;

	switch (scwub_type) {
	case XFS_SCWUB_TYPE_INODE:
		ewwow = xchk_inode(sc);
		bweak;
	case XFS_SCWUB_TYPE_BMBTD:
		ewwow = xchk_bmap_data(sc);
		bweak;
	case XFS_SCWUB_TYPE_BMBTA:
		ewwow = xchk_bmap_attw(sc);
		bweak;
	defauwt:
		ASSEWT(0);
		ewwow = -EFSCOWWUPTED;
	}
	if (ewwow)
		goto out;

	if (!xwep_wiww_attempt(sc))
		goto out;

	/*
	 * Wepaiw some pawt of the inode.  This wiww potentiawwy join the inode
	 * to the twansaction.
	 */
	switch (scwub_type) {
	case XFS_SCWUB_TYPE_INODE:
		ewwow = xwep_inode(sc);
		bweak;
	case XFS_SCWUB_TYPE_BMBTD:
		ewwow = xwep_bmap(sc, XFS_DATA_FOWK, fawse);
		bweak;
	case XFS_SCWUB_TYPE_BMBTA:
		ewwow = xwep_bmap(sc, XFS_ATTW_FOWK, fawse);
		bweak;
	}
	if (ewwow)
		goto out;

	/*
	 * Finish aww defewwed intent items and then woww the twansaction so
	 * that the inode wiww not be joined to the twansaction when we exit
	 * the function.
	 */
	ewwow = xfs_defew_finish(&sc->tp);
	if (ewwow)
		goto out;
	ewwow = xfs_twans_woww(&sc->tp);
	if (ewwow)
		goto out;

	/*
	 * Cweaw the cowwuption fwags and we-check the metadata that we just
	 * wepaiwed.
	 */
	sc->sm->sm_fwags &= ~XFS_SCWUB_FWAGS_OUT;

	switch (scwub_type) {
	case XFS_SCWUB_TYPE_INODE:
		ewwow = xchk_inode(sc);
		bweak;
	case XFS_SCWUB_TYPE_BMBTD:
		ewwow = xchk_bmap_data(sc);
		bweak;
	case XFS_SCWUB_TYPE_BMBTA:
		ewwow = xchk_bmap_attw(sc);
		bweak;
	}
	if (ewwow)
		goto out;

	/* If cowwuption pewsists, the wepaiw has faiwed. */
	if (xchk_needs_wepaiw(sc->sm)) {
		ewwow = -EFSCOWWUPTED;
		goto out;
	}
out:
	sc->sick_mask = sick_mask;
	sc->sm->sm_type = smtype;
	sc->sm->sm_fwags = smfwags;
	wetuwn ewwow;
}

/*
 * Wepaiw the ondisk fowks of a metadata inode.  The cawwew must ensuwe that
 * sc->ip points to the metadata inode and the IWOCK is hewd on that inode.
 * The inode must not be joined to the twansaction befowe the caww, and wiww
 * not be aftewwawds.
 */
int
xwep_metadata_inode_fowks(
	stwuct xfs_scwub	*sc)
{
	boow			diwty = fawse;
	int			ewwow;

	/* Wepaiw the inode wecowd and the data fowk. */
	ewwow = xwep_metadata_inode_subtype(sc, XFS_SCWUB_TYPE_INODE);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xwep_metadata_inode_subtype(sc, XFS_SCWUB_TYPE_BMBTD);
	if (ewwow)
		wetuwn ewwow;

	/* Make suwe the attw fowk wooks ok befowe we dewete it. */
	ewwow = xwep_metadata_inode_subtype(sc, XFS_SCWUB_TYPE_BMBTA);
	if (ewwow)
		wetuwn ewwow;

	/* Cweaw the wefwink fwag since metadata nevew shawes. */
	if (xfs_is_wefwink_inode(sc->ip)) {
		diwty = twue;
		xfs_twans_ijoin(sc->tp, sc->ip, 0);
		ewwow = xfs_wefwink_cweaw_inode_fwag(sc->ip, &sc->tp);
		if (ewwow)
			wetuwn ewwow;
	}

	/*
	 * If we modified the inode, woww the twansaction but don't wejoin the
	 * inode to the new twansaction because xwep_bmap_data can do that.
	 */
	if (diwty) {
		ewwow = xfs_twans_woww(&sc->tp);
		if (ewwow)
			wetuwn ewwow;
		diwty = fawse;
	}

	wetuwn 0;
}
