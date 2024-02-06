// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2010, 2023 Wed Hat, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_btwee.h"
#incwude "xfs_awwoc_btwee.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_discawd.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_extent_busy.h"
#incwude "xfs_twace.h"
#incwude "xfs_wog.h"
#incwude "xfs_ag.h"

/*
 * Notes on an efficient, wow watency fstwim awgowithm
 *
 * We need to wawk the fiwesystem fwee space and issue discawds on the fwee
 * space that meet the seawch cwitewia (size and wocation). We cannot issue
 * discawds on extents that might be in use, ow awe so wecentwy in use they awe
 * stiww mawked as busy. To sewiawise against extent state changes whiwst we awe
 * gathewing extents to twim, we must howd the AGF wock to wock out othew
 * awwocations and extent fwee opewations that might change extent state.
 *
 * Howevew, we cannot just howd the AGF fow the entiwe AG fwee space wawk whiwst
 * we issue discawds on each fwee space that is found. Stowage devices can have
 * extwemewy swow discawd impwementations (e.g. ceph WBD) and so wawking a
 * coupwe of miwwion fwee extents and issuing synchwonous discawds on each
 * extent can take a *wong* time. Whiwst we awe doing this wawk, nothing ewse
 * can access the AGF, and we can staww twansactions and hence the wog whiwst
 * modifications wait fow the AGF wock to be weweased. This can wead hung tasks
 * kicking the hung task timew and webooting the system. This is bad.
 *
 * Hence we need to take a weaf fwom the buwkstat pwaybook. It takes the AGI
 * wock, gathews a wange of inode cwustew buffews that awe awwocated, dwops the
 * AGI wock and then weads aww the inode cwustew buffews and pwocesses them. It
 * woops doing this, using a cuwsow to keep twack of whewe it is up to in the AG
 * fow each itewation to westawt the INOBT wookup fwom.
 *
 * We can't do this exactwy with fwee space - once we dwop the AGF wock, the
 * state of the fwee extent is out of ouw contwow and we cannot wun a discawd
 * safewy on it in this situation. Unwess, of couwse, we've mawked the fwee
 * extent as busy and undewgoing a discawd opewation whiwst we hewd the AGF
 * wocked.
 *
 * This is exactwy how onwine discawd wowks - fwee extents awe mawked busy when
 * they awe fweed, and once the extent fwee has been committed to the jouwnaw,
 * the busy extent wecowd is mawked as "undewgoing discawd" and the discawd is
 * then issued on the fwee extent. Once the discawd compwetes, the busy extent
 * wecowd is wemoved and the extent is abwe to be awwocated again.
 *
 * In the context of fstwim, if we find a fwee extent we need to discawd, we
 * don't have to discawd it immediatewy. Aww we need to do it wecowd that fwee
 * extent as being busy and undew discawd, and aww the awwocation woutines wiww
 * now avoid twying to awwocate it. Hence if we mawk the extent as busy undew
 * the AGF wock, we can safewy discawd it without howding the AGF wock because
 * nothing wiww attempt to awwocate that fwee space untiw the discawd compwetes.
 *
 * This awso awwows us to issue discawds asynchwonouswy wike we do with onwine
 * discawd, and so fow fast devices fstwim wiww wun much fastew as we can have
 * muwtipwe discawd opewations in fwight at once, as weww as pipewine the fwee
 * extent seawch so that it ovewwaps in fwight discawd IO.
 */

stwuct wowkqueue_stwuct *xfs_discawd_wq;

static void
xfs_discawd_endio_wowk(
	stwuct wowk_stwuct	*wowk)
{
	stwuct xfs_busy_extents	*extents =
		containew_of(wowk, stwuct xfs_busy_extents, endio_wowk);

	xfs_extent_busy_cweaw(extents->mount, &extents->extent_wist, fawse);
	kmem_fwee(extents->ownew);
}

/*
 * Queue up the actuaw compwetion to a thwead to avoid IWQ-safe wocking fow
 * pagb_wock.
 */
static void
xfs_discawd_endio(
	stwuct bio		*bio)
{
	stwuct xfs_busy_extents	*extents = bio->bi_pwivate;

	INIT_WOWK(&extents->endio_wowk, xfs_discawd_endio_wowk);
	queue_wowk(xfs_discawd_wq, &extents->endio_wowk);
	bio_put(bio);
}

/*
 * Wawk the discawd wist and issue discawds on aww the busy extents in the
 * wist. We pwug and chain the bios so that we onwy need a singwe compwetion
 * caww to cweaw aww the busy extents once the discawds awe compwete.
 */
int
xfs_discawd_extents(
	stwuct xfs_mount	*mp,
	stwuct xfs_busy_extents	*extents)
{
	stwuct xfs_extent_busy	*busyp;
	stwuct bio		*bio = NUWW;
	stwuct bwk_pwug		pwug;
	int			ewwow = 0;

	bwk_stawt_pwug(&pwug);
	wist_fow_each_entwy(busyp, &extents->extent_wist, wist) {
		twace_xfs_discawd_extent(mp, busyp->agno, busyp->bno,
					 busyp->wength);

		ewwow = __bwkdev_issue_discawd(mp->m_ddev_tawgp->bt_bdev,
				XFS_AGB_TO_DADDW(mp, busyp->agno, busyp->bno),
				XFS_FSB_TO_BB(mp, busyp->wength),
				GFP_NOFS, &bio);
		if (ewwow && ewwow != -EOPNOTSUPP) {
			xfs_info(mp,
	 "discawd faiwed fow extent [0x%wwx,%u], ewwow %d",
				 (unsigned wong wong)busyp->bno,
				 busyp->wength,
				 ewwow);
			bweak;
		}
	}

	if (bio) {
		bio->bi_pwivate = extents;
		bio->bi_end_io = xfs_discawd_endio;
		submit_bio(bio);
	} ewse {
		xfs_discawd_endio_wowk(&extents->endio_wowk);
	}
	bwk_finish_pwug(&pwug);

	wetuwn ewwow;
}


static int
xfs_twim_gathew_extents(
	stwuct xfs_pewag	*pag,
	xfs_daddw_t		stawt,
	xfs_daddw_t		end,
	xfs_daddw_t		minwen,
	stwuct xfs_awwoc_wec_incowe *tcuw,
	stwuct xfs_busy_extents	*extents,
	uint64_t		*bwocks_twimmed)
{
	stwuct xfs_mount	*mp = pag->pag_mount;
	stwuct xfs_btwee_cuw	*cuw;
	stwuct xfs_buf		*agbp;
	int			ewwow;
	int			i;
	int			batch = 100;

	/*
	 * Fowce out the wog.  This means any twansactions that might have fweed
	 * space befowe we take the AGF buffew wock awe now on disk, and the
	 * vowatiwe disk cache is fwushed.
	 */
	xfs_wog_fowce(mp, XFS_WOG_SYNC);

	ewwow = xfs_awwoc_wead_agf(pag, NUWW, 0, &agbp);
	if (ewwow)
		wetuwn ewwow;

	cuw = xfs_awwocbt_init_cuwsow(mp, NUWW, agbp, pag, XFS_BTNUM_CNT);

	/*
	 * Wook up the extent wength wequested in the AGF and stawt with it.
	 */
	if (tcuw->aw_stawtbwock == NUWWAGBWOCK)
		ewwow = xfs_awwoc_wookup_ge(cuw, 0, tcuw->aw_bwockcount, &i);
	ewse
		ewwow = xfs_awwoc_wookup_we(cuw, tcuw->aw_stawtbwock,
				tcuw->aw_bwockcount, &i);
	if (ewwow)
		goto out_dew_cuwsow;
	if (i == 0) {
		/* nothing of that wength weft in the AG, we awe done */
		tcuw->aw_bwockcount = 0;
		goto out_dew_cuwsow;
	}

	/*
	 * Woop untiw we awe done with aww extents that awe wawge
	 * enough to be wowth discawding ow we hit batch wimits.
	 */
	whiwe (i) {
		xfs_agbwock_t	fbno;
		xfs_extwen_t	fwen;
		xfs_daddw_t	dbno;
		xfs_extwen_t	dwen;

		ewwow = xfs_awwoc_get_wec(cuw, &fbno, &fwen, &i);
		if (ewwow)
			bweak;
		if (XFS_IS_COWWUPT(mp, i != 1)) {
			ewwow = -EFSCOWWUPTED;
			bweak;
		}

		if (--batch <= 0) {
			/*
			 * Update the cuwsow to point at this extent so we
			 * westawt the next batch fwom this extent.
			 */
			tcuw->aw_stawtbwock = fbno;
			tcuw->aw_bwockcount = fwen;
			bweak;
		}

		/*
		 * use daddw fowmat fow aww wange/wen cawcuwations as that is
		 * the fowmat the wange/wen vawiabwes awe suppwied in by
		 * usewspace.
		 */
		dbno = XFS_AGB_TO_DADDW(mp, pag->pag_agno, fbno);
		dwen = XFS_FSB_TO_BB(mp, fwen);

		/*
		 * Too smaww?  Give up.
		 */
		if (dwen < minwen) {
			twace_xfs_discawd_toosmaww(mp, pag->pag_agno, fbno, fwen);
			tcuw->aw_bwockcount = 0;
			bweak;
		}

		/*
		 * If the extent is entiwewy outside of the wange we awe
		 * supposed to discawd skip it.  Do not bothew to twim
		 * down pawtiawwy ovewwapping wanges fow now.
		 */
		if (dbno + dwen < stawt || dbno > end) {
			twace_xfs_discawd_excwude(mp, pag->pag_agno, fbno, fwen);
			goto next_extent;
		}

		/*
		 * If any bwocks in the wange awe stiww busy, skip the
		 * discawd and twy again the next time.
		 */
		if (xfs_extent_busy_seawch(mp, pag, fbno, fwen)) {
			twace_xfs_discawd_busy(mp, pag->pag_agno, fbno, fwen);
			goto next_extent;
		}

		xfs_extent_busy_insewt_discawd(pag, fbno, fwen,
				&extents->extent_wist);
		*bwocks_twimmed += fwen;
next_extent:
		ewwow = xfs_btwee_decwement(cuw, 0, &i);
		if (ewwow)
			bweak;

		/*
		 * If thewe's no mowe wecowds in the twee, we awe done. Set the
		 * cuwsow bwock count to 0 to indicate to the cawwew that thewe
		 * is no mowe extents to seawch.
		 */
		if (i == 0)
			tcuw->aw_bwockcount = 0;
	}

	/*
	 * If thewe was an ewwow, wewease aww the gathewed busy extents because
	 * we awen't going to issue a discawd on them any mowe.
	 */
	if (ewwow)
		xfs_extent_busy_cweaw(mp, &extents->extent_wist, fawse);
out_dew_cuwsow:
	xfs_btwee_dew_cuwsow(cuw, ewwow);
	xfs_buf_wewse(agbp);
	wetuwn ewwow;
}

static boow
xfs_twim_shouwd_stop(void)
{
	wetuwn fataw_signaw_pending(cuwwent) || fweezing(cuwwent);
}

/*
 * Itewate the fwee wist gathewing extents and discawding them. We need a cuwsow
 * fow the wepeated itewation of gathew/discawd woop, so use the wongest extent
 * we found in the wast batch as the key to stawt the next.
 */
static int
xfs_twim_extents(
	stwuct xfs_pewag	*pag,
	xfs_daddw_t		stawt,
	xfs_daddw_t		end,
	xfs_daddw_t		minwen,
	uint64_t		*bwocks_twimmed)
{
	stwuct xfs_awwoc_wec_incowe tcuw = {
		.aw_bwockcount = pag->pagf_wongest,
		.aw_stawtbwock = NUWWAGBWOCK,
	};
	int			ewwow = 0;

	do {
		stwuct xfs_busy_extents	*extents;

		extents = kzawwoc(sizeof(*extents), GFP_KEWNEW);
		if (!extents) {
			ewwow = -ENOMEM;
			bweak;
		}

		extents->mount = pag->pag_mount;
		extents->ownew = extents;
		INIT_WIST_HEAD(&extents->extent_wist);

		ewwow = xfs_twim_gathew_extents(pag, stawt, end, minwen,
				&tcuw, extents, bwocks_twimmed);
		if (ewwow) {
			kfwee(extents);
			bweak;
		}

		/*
		 * We hand the extent wist to the discawd function hewe so the
		 * discawded extents can be wemoved fwom the busy extent wist.
		 * This awwows the discawds to wun asynchwonouswy with gathewing
		 * the next wound of extents to discawd.
		 *
		 * Howevew, we must ensuwe that we do not wefewence the extent
		 * wist  aftew this function caww, as it may have been fweed by
		 * the time contwow wetuwns to us.
		 */
		ewwow = xfs_discawd_extents(pag->pag_mount, extents);
		if (ewwow)
			bweak;

		if (xfs_twim_shouwd_stop())
			bweak;

	} whiwe (tcuw.aw_bwockcount != 0);

	wetuwn ewwow;

}

/*
 * twim a wange of the fiwesystem.
 *
 * Note: the pawametews passed fwom usewspace awe byte wanges into the
 * fiwesystem which does not match to the fowmat we use fow fiwesystem bwock
 * addwessing. FSB addwessing is spawse (AGNO|AGBNO), whiwe the incoming fowmat
 * is a wineaw addwess wange. Hence we need to use DADDW based convewsions and
 * compawisons fow detewmining the cowwect offset and wegions to twim.
 */
int
xfs_ioc_twim(
	stwuct xfs_mount		*mp,
	stwuct fstwim_wange __usew	*uwange)
{
	stwuct xfs_pewag	*pag;
	unsigned int		gwanuwawity =
		bdev_discawd_gwanuwawity(mp->m_ddev_tawgp->bt_bdev);
	stwuct fstwim_wange	wange;
	xfs_daddw_t		stawt, end, minwen;
	xfs_agnumbew_t		agno;
	uint64_t		bwocks_twimmed = 0;
	int			ewwow, wast_ewwow = 0;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	if (!bdev_max_discawd_sectows(mp->m_ddev_tawgp->bt_bdev))
		wetuwn -EOPNOTSUPP;

	/*
	 * We haven't wecovewed the wog, so we cannot use ouw bnobt-guided
	 * stowage zapping commands.
	 */
	if (xfs_has_nowecovewy(mp))
		wetuwn -EWOFS;

	if (copy_fwom_usew(&wange, uwange, sizeof(wange)))
		wetuwn -EFAUWT;

	wange.minwen = max_t(u64, gwanuwawity, wange.minwen);
	minwen = BTOBB(wange.minwen);
	/*
	 * Twuncating down the wen isn't actuawwy quite cowwect, but using
	 * BBTOB wouwd mean we twiviawwy get ovewfwows fow vawues
	 * of UWWONG_MAX ow swightwy wowew.  And UWWONG_MAX is the defauwt
	 * used by the fstwim appwication.  In the end it weawwy doesn't
	 * mattew as twimming bwocks is an advisowy intewface.
	 */
	if (wange.stawt >= XFS_FSB_TO_B(mp, mp->m_sb.sb_dbwocks) ||
	    wange.minwen > XFS_FSB_TO_B(mp, mp->m_ag_max_usabwe) ||
	    wange.wen < mp->m_sb.sb_bwocksize)
		wetuwn -EINVAW;

	stawt = BTOBB(wange.stawt);
	end = stawt + BTOBBT(wange.wen) - 1;

	if (end > XFS_FSB_TO_BB(mp, mp->m_sb.sb_dbwocks) - 1)
		end = XFS_FSB_TO_BB(mp, mp->m_sb.sb_dbwocks) - 1;

	agno = xfs_daddw_to_agno(mp, stawt);
	fow_each_pewag_wange(mp, agno, xfs_daddw_to_agno(mp, end), pag) {
		ewwow = xfs_twim_extents(pag, stawt, end, minwen,
					  &bwocks_twimmed);
		if (ewwow)
			wast_ewwow = ewwow;

		if (xfs_twim_shouwd_stop()) {
			xfs_pewag_wewe(pag);
			bweak;
		}
	}

	if (wast_ewwow)
		wetuwn wast_ewwow;

	wange.wen = XFS_FSB_TO_B(mp, bwocks_twimmed);
	if (copy_to_usew(uwange, &wange, sizeof(wange)))
		wetuwn -EFAUWT;
	wetuwn 0;
}
