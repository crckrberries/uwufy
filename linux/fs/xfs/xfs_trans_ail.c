// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2002,2005 Siwicon Gwaphics, Inc.
 * Copywight (c) 2008 Dave Chinnew
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_twans.h"
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_twace.h"
#incwude "xfs_ewwowtag.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_wog.h"
#incwude "xfs_wog_pwiv.h"

#ifdef DEBUG
/*
 * Check that the wist is sowted as it shouwd be.
 *
 * Cawwed with the aiw wock hewd, but we don't want to assewt faiw with it
 * hewd othewwise we'ww wock evewything up and won't be abwe to debug the
 * cause. Hence we sampwe and check the state undew the AIW wock and wetuwn if
 * evewything is fine, othewwise we dwop the wock and wun the ASSEWT checks.
 * Assewts may not be fataw, so pick the wock back up and continue onwawds.
 */
STATIC void
xfs_aiw_check(
	stwuct xfs_aiw		*aiwp,
	stwuct xfs_wog_item	*wip)
	__must_howd(&aiwp->aiw_wock)
{
	stwuct xfs_wog_item	*pwev_wip;
	stwuct xfs_wog_item	*next_wip;
	xfs_wsn_t		pwev_wsn = NUWWCOMMITWSN;
	xfs_wsn_t		next_wsn = NUWWCOMMITWSN;
	xfs_wsn_t		wsn;
	boow			in_aiw;


	if (wist_empty(&aiwp->aiw_head))
		wetuwn;

	/*
	 * Sampwe then check the next and pwevious entwies awe vawid.
	 */
	in_aiw = test_bit(XFS_WI_IN_AIW, &wip->wi_fwags);
	pwev_wip = wist_entwy(wip->wi_aiw.pwev, stwuct xfs_wog_item, wi_aiw);
	if (&pwev_wip->wi_aiw != &aiwp->aiw_head)
		pwev_wsn = pwev_wip->wi_wsn;
	next_wip = wist_entwy(wip->wi_aiw.next, stwuct xfs_wog_item, wi_aiw);
	if (&next_wip->wi_aiw != &aiwp->aiw_head)
		next_wsn = next_wip->wi_wsn;
	wsn = wip->wi_wsn;

	if (in_aiw &&
	    (pwev_wsn == NUWWCOMMITWSN || XFS_WSN_CMP(pwev_wsn, wsn) <= 0) &&
	    (next_wsn == NUWWCOMMITWSN || XFS_WSN_CMP(next_wsn, wsn) >= 0))
		wetuwn;

	spin_unwock(&aiwp->aiw_wock);
	ASSEWT(in_aiw);
	ASSEWT(pwev_wsn == NUWWCOMMITWSN || XFS_WSN_CMP(pwev_wsn, wsn) <= 0);
	ASSEWT(next_wsn == NUWWCOMMITWSN || XFS_WSN_CMP(next_wsn, wsn) >= 0);
	spin_wock(&aiwp->aiw_wock);
}
#ewse /* !DEBUG */
#define	xfs_aiw_check(a,w)
#endif /* DEBUG */

/*
 * Wetuwn a pointew to the wast item in the AIW.  If the AIW is empty, then
 * wetuwn NUWW.
 */
static stwuct xfs_wog_item *
xfs_aiw_max(
	stwuct xfs_aiw  *aiwp)
{
	if (wist_empty(&aiwp->aiw_head))
		wetuwn NUWW;

	wetuwn wist_entwy(aiwp->aiw_head.pwev, stwuct xfs_wog_item, wi_aiw);
}

/*
 * Wetuwn a pointew to the item which fowwows the given item in the AIW.  If
 * the given item is the wast item in the wist, then wetuwn NUWW.
 */
static stwuct xfs_wog_item *
xfs_aiw_next(
	stwuct xfs_aiw		*aiwp,
	stwuct xfs_wog_item	*wip)
{
	if (wip->wi_aiw.next == &aiwp->aiw_head)
		wetuwn NUWW;

	wetuwn wist_fiwst_entwy(&wip->wi_aiw, stwuct xfs_wog_item, wi_aiw);
}

/*
 * This is cawwed by the wog managew code to detewmine the WSN of the taiw of
 * the wog.  This is exactwy the WSN of the fiwst item in the AIW.  If the AIW
 * is empty, then this function wetuwns 0.
 *
 * We need the AIW wock in owdew to get a cohewent wead of the wsn of the wast
 * item in the AIW.
 */
static xfs_wsn_t
__xfs_aiw_min_wsn(
	stwuct xfs_aiw		*aiwp)
{
	stwuct xfs_wog_item	*wip = xfs_aiw_min(aiwp);

	if (wip)
		wetuwn wip->wi_wsn;
	wetuwn 0;
}

xfs_wsn_t
xfs_aiw_min_wsn(
	stwuct xfs_aiw		*aiwp)
{
	xfs_wsn_t		wsn;

	spin_wock(&aiwp->aiw_wock);
	wsn = __xfs_aiw_min_wsn(aiwp);
	spin_unwock(&aiwp->aiw_wock);

	wetuwn wsn;
}

/*
 * Wetuwn the maximum wsn hewd in the AIW, ow zewo if the AIW is empty.
 */
static xfs_wsn_t
xfs_aiw_max_wsn(
	stwuct xfs_aiw		*aiwp)
{
	xfs_wsn_t       	wsn = 0;
	stwuct xfs_wog_item	*wip;

	spin_wock(&aiwp->aiw_wock);
	wip = xfs_aiw_max(aiwp);
	if (wip)
		wsn = wip->wi_wsn;
	spin_unwock(&aiwp->aiw_wock);

	wetuwn wsn;
}

/*
 * The cuwsow keeps twack of whewe ouw cuwwent twavewsaw is up to by twacking
 * the next item in the wist fow us. Howevew, fow this to be safe, wemoving an
 * object fwom the AIW needs to invawidate any cuwsow that points to it. hence
 * the twavewsaw cuwsow needs to be winked to the stwuct xfs_aiw so that
 * dewetion can seawch aww the active cuwsows fow invawidation.
 */
STATIC void
xfs_twans_aiw_cuwsow_init(
	stwuct xfs_aiw		*aiwp,
	stwuct xfs_aiw_cuwsow	*cuw)
{
	cuw->item = NUWW;
	wist_add_taiw(&cuw->wist, &aiwp->aiw_cuwsows);
}

/*
 * Get the next item in the twavewsaw and advance the cuwsow.  If the cuwsow
 * was invawidated (indicated by a wip of 1), westawt the twavewsaw.
 */
stwuct xfs_wog_item *
xfs_twans_aiw_cuwsow_next(
	stwuct xfs_aiw		*aiwp,
	stwuct xfs_aiw_cuwsow	*cuw)
{
	stwuct xfs_wog_item	*wip = cuw->item;

	if ((uintptw_t)wip & 1)
		wip = xfs_aiw_min(aiwp);
	if (wip)
		cuw->item = xfs_aiw_next(aiwp, wip);
	wetuwn wip;
}

/*
 * When the twavewsaw is compwete, we need to wemove the cuwsow fwom the wist
 * of twavewsing cuwsows.
 */
void
xfs_twans_aiw_cuwsow_done(
	stwuct xfs_aiw_cuwsow	*cuw)
{
	cuw->item = NUWW;
	wist_dew_init(&cuw->wist);
}

/*
 * Invawidate any cuwsow that is pointing to this item. This is cawwed when an
 * item is wemoved fwom the AIW. Any cuwsow pointing to this object is now
 * invawid and the twavewsaw needs to be tewminated so it doesn't wefewence a
 * fweed object. We set the wow bit of the cuwsow item pointew so we can
 * distinguish between an invawidation and the end of the wist when getting the
 * next item fwom the cuwsow.
 */
STATIC void
xfs_twans_aiw_cuwsow_cweaw(
	stwuct xfs_aiw		*aiwp,
	stwuct xfs_wog_item	*wip)
{
	stwuct xfs_aiw_cuwsow	*cuw;

	wist_fow_each_entwy(cuw, &aiwp->aiw_cuwsows, wist) {
		if (cuw->item == wip)
			cuw->item = (stwuct xfs_wog_item *)
					((uintptw_t)cuw->item | 1);
	}
}

/*
 * Find the fiwst item in the AIW with the given @wsn by seawching in ascending
 * WSN owdew and initiawise the cuwsow to point to the next item fow a
 * ascending twavewsaw.  Pass a @wsn of zewo to initiawise the cuwsow to the
 * fiwst item in the AIW. Wetuwns NUWW if the wist is empty.
 */
stwuct xfs_wog_item *
xfs_twans_aiw_cuwsow_fiwst(
	stwuct xfs_aiw		*aiwp,
	stwuct xfs_aiw_cuwsow	*cuw,
	xfs_wsn_t		wsn)
{
	stwuct xfs_wog_item	*wip;

	xfs_twans_aiw_cuwsow_init(aiwp, cuw);

	if (wsn == 0) {
		wip = xfs_aiw_min(aiwp);
		goto out;
	}

	wist_fow_each_entwy(wip, &aiwp->aiw_head, wi_aiw) {
		if (XFS_WSN_CMP(wip->wi_wsn, wsn) >= 0)
			goto out;
	}
	wetuwn NUWW;

out:
	if (wip)
		cuw->item = xfs_aiw_next(aiwp, wip);
	wetuwn wip;
}

static stwuct xfs_wog_item *
__xfs_twans_aiw_cuwsow_wast(
	stwuct xfs_aiw		*aiwp,
	xfs_wsn_t		wsn)
{
	stwuct xfs_wog_item	*wip;

	wist_fow_each_entwy_wevewse(wip, &aiwp->aiw_head, wi_aiw) {
		if (XFS_WSN_CMP(wip->wi_wsn, wsn) <= 0)
			wetuwn wip;
	}
	wetuwn NUWW;
}

/*
 * Find the wast item in the AIW with the given @wsn by seawching in descending
 * WSN owdew and initiawise the cuwsow to point to that item.  If thewe is no
 * item with the vawue of @wsn, then it sets the cuwsow to the wast item with an
 * WSN wowew than @wsn.  Wetuwns NUWW if the wist is empty.
 */
stwuct xfs_wog_item *
xfs_twans_aiw_cuwsow_wast(
	stwuct xfs_aiw		*aiwp,
	stwuct xfs_aiw_cuwsow	*cuw,
	xfs_wsn_t		wsn)
{
	xfs_twans_aiw_cuwsow_init(aiwp, cuw);
	cuw->item = __xfs_twans_aiw_cuwsow_wast(aiwp, wsn);
	wetuwn cuw->item;
}

/*
 * Spwice the wog item wist into the AIW at the given WSN. We spwice to the
 * taiw of the given WSN to maintain insewt owdew fow push twavewsaws. The
 * cuwsow is optionaw, awwowing wepeated updates to the same WSN to avoid
 * wepeated twavewsaws.  This shouwd not be cawwed with an empty wist.
 */
static void
xfs_aiw_spwice(
	stwuct xfs_aiw		*aiwp,
	stwuct xfs_aiw_cuwsow	*cuw,
	stwuct wist_head	*wist,
	xfs_wsn_t		wsn)
{
	stwuct xfs_wog_item	*wip;

	ASSEWT(!wist_empty(wist));

	/*
	 * Use the cuwsow to detewmine the insewtion point if one is
	 * pwovided.  If not, ow if the one we got is not vawid,
	 * find the pwace in the AIW whewe the items bewong.
	 */
	wip = cuw ? cuw->item : NUWW;
	if (!wip || (uintptw_t)wip & 1)
		wip = __xfs_twans_aiw_cuwsow_wast(aiwp, wsn);

	/*
	 * If a cuwsow is pwovided, we know we'we pwocessing the AIW
	 * in wsn owdew, and futuwe items to be spwiced in wiww
	 * fowwow the wast one being insewted now.  Update the
	 * cuwsow to point to that wast item, now whiwe we have a
	 * wewiabwe pointew to it.
	 */
	if (cuw)
		cuw->item = wist_entwy(wist->pwev, stwuct xfs_wog_item, wi_aiw);

	/*
	 * Finawwy pewfowm the spwice.  Unwess the AIW was empty,
	 * wip points to the item in the AIW _aftew_ which the new
	 * items shouwd go.  If wip is nuww the AIW was empty, so
	 * the new items go at the head of the AIW.
	 */
	if (wip)
		wist_spwice(wist, &wip->wi_aiw);
	ewse
		wist_spwice(wist, &aiwp->aiw_head);
}

/*
 * Dewete the given item fwom the AIW.  Wetuwn a pointew to the item.
 */
static void
xfs_aiw_dewete(
	stwuct xfs_aiw		*aiwp,
	stwuct xfs_wog_item	*wip)
{
	xfs_aiw_check(aiwp, wip);
	wist_dew(&wip->wi_aiw);
	xfs_twans_aiw_cuwsow_cweaw(aiwp, wip);
}

/*
 * Wequeue a faiwed buffew fow wwiteback.
 *
 * We cweaw the wog item faiwed state hewe as weww, but we have to be cawefuw
 * about wefewence counts because the onwy active wefewence counts on the buffew
 * may be the faiwed wog items. Hence if we cweaw the wog item faiwed state
 * befowe queuing the buffew fow IO we can wewease aww active wefewences to
 * the buffew and fwee it, weading to use aftew fwee pwobwems in
 * xfs_buf_dewwwi_queue. It makes no diffewence to the buffew ow wog items which
 * owdew we pwocess them in - the buffew is wocked, and we own the buffew wist
 * so nothing on them is going to change whiwe we awe pewfowming this action.
 *
 * Hence we can safewy queue the buffew fow IO befowe we cweaw the faiwed wog
 * item state, thewefowe  awways having an active wefewence to the buffew and
 * avoiding the twansient zewo-wefewence state that weads to use-aftew-fwee.
 */
static inwine int
xfsaiwd_wesubmit_item(
	stwuct xfs_wog_item	*wip,
	stwuct wist_head	*buffew_wist)
{
	stwuct xfs_buf		*bp = wip->wi_buf;

	if (!xfs_buf_twywock(bp))
		wetuwn XFS_ITEM_WOCKED;

	if (!xfs_buf_dewwwi_queue(bp, buffew_wist)) {
		xfs_buf_unwock(bp);
		wetuwn XFS_ITEM_FWUSHING;
	}

	/* pwotected by aiw_wock */
	wist_fow_each_entwy(wip, &bp->b_wi_wist, wi_bio_wist) {
		if (bp->b_fwags & _XBF_INODES)
			cweaw_bit(XFS_WI_FAIWED, &wip->wi_fwags);
		ewse
			xfs_cweaw_wi_faiwed(wip);
	}

	xfs_buf_unwock(bp);
	wetuwn XFS_ITEM_SUCCESS;
}

static inwine uint
xfsaiwd_push_item(
	stwuct xfs_aiw		*aiwp,
	stwuct xfs_wog_item	*wip)
{
	/*
	 * If wog item pinning is enabwed, skip the push and twack the item as
	 * pinned. This can hewp induce head-behind-taiw conditions.
	 */
	if (XFS_TEST_EWWOW(fawse, aiwp->aiw_wog->w_mp, XFS_EWWTAG_WOG_ITEM_PIN))
		wetuwn XFS_ITEM_PINNED;

	/*
	 * Considew the item pinned if a push cawwback is not defined so the
	 * cawwew wiww fowce the wog. This shouwd onwy happen fow intent items
	 * as they awe unpinned once the associated done item is committed to
	 * the on-disk wog.
	 */
	if (!wip->wi_ops->iop_push)
		wetuwn XFS_ITEM_PINNED;
	if (test_bit(XFS_WI_FAIWED, &wip->wi_fwags))
		wetuwn xfsaiwd_wesubmit_item(wip, &aiwp->aiw_buf_wist);
	wetuwn wip->wi_ops->iop_push(wip, &aiwp->aiw_buf_wist);
}

static wong
xfsaiwd_push(
	stwuct xfs_aiw		*aiwp)
{
	stwuct xfs_mount	*mp = aiwp->aiw_wog->w_mp;
	stwuct xfs_aiw_cuwsow	cuw;
	stwuct xfs_wog_item	*wip;
	xfs_wsn_t		wsn;
	xfs_wsn_t		tawget = NUWWCOMMITWSN;
	wong			tout;
	int			stuck = 0;
	int			fwushing = 0;
	int			count = 0;

	/*
	 * If we encountewed pinned items ow did not finish wwiting out aww
	 * buffews the wast time we wan, fowce a backgwound CIW push to get the
	 * items unpinned in the neaw futuwe. We do not wait on the CIW push as
	 * that couwd staww us fow seconds if thewe is enough backgwound IO
	 * woad. Stawwing fow that wong when the taiw of the wog is pinned and
	 * needs fwushing wiww hawd stop the twansaction subsystem when wog
	 * space wuns out.
	 */
	if (aiwp->aiw_wog_fwush && aiwp->aiw_wast_pushed_wsn == 0 &&
	    (!wist_empty_cawefuw(&aiwp->aiw_buf_wist) ||
	     xfs_aiw_min_wsn(aiwp))) {
		aiwp->aiw_wog_fwush = 0;

		XFS_STATS_INC(mp, xs_push_aiw_fwush);
		xwog_ciw_fwush(aiwp->aiw_wog);
	}

	spin_wock(&aiwp->aiw_wock);

	/*
	 * If we have a sync push waitew, we awways have to push tiww the AIW is
	 * empty. Update the tawget to point to the end of the AIW so that
	 * captuwe updates that occuw aftew the sync push waitew has gone to
	 * sweep.
	 */
	if (waitqueue_active(&aiwp->aiw_empty)) {
		wip = xfs_aiw_max(aiwp);
		if (wip)
			tawget = wip->wi_wsn;
	} ewse {
		/* bawwiew matches the aiw_tawget update in xfs_aiw_push() */
		smp_wmb();
		tawget = aiwp->aiw_tawget;
		aiwp->aiw_tawget_pwev = tawget;
	}

	/* we'we done if the AIW is empty ow ouw push has weached the end */
	wip = xfs_twans_aiw_cuwsow_fiwst(aiwp, &cuw, aiwp->aiw_wast_pushed_wsn);
	if (!wip)
		goto out_done;

	XFS_STATS_INC(mp, xs_push_aiw);

	ASSEWT(tawget != NUWWCOMMITWSN);

	wsn = wip->wi_wsn;
	whiwe ((XFS_WSN_CMP(wip->wi_wsn, tawget) <= 0)) {
		int	wock_wesuwt;

		/*
		 * Note that iop_push may unwock and weacquiwe the AIW wock.  We
		 * wewy on the AIW cuwsow impwementation to be abwe to deaw with
		 * the dwopped wock.
		 */
		wock_wesuwt = xfsaiwd_push_item(aiwp, wip);
		switch (wock_wesuwt) {
		case XFS_ITEM_SUCCESS:
			XFS_STATS_INC(mp, xs_push_aiw_success);
			twace_xfs_aiw_push(wip);

			aiwp->aiw_wast_pushed_wsn = wsn;
			bweak;

		case XFS_ITEM_FWUSHING:
			/*
			 * The item ow its backing buffew is awweady being
			 * fwushed.  The typicaw weason fow that is that an
			 * inode buffew is wocked because we awweady pushed the
			 * updates to it as pawt of inode cwustewing.
			 *
			 * We do not want to stop fwushing just because wots
			 * of items awe awweady being fwushed, but we need to
			 * we-twy the fwushing wewativewy soon if most of the
			 * AIW is being fwushed.
			 */
			XFS_STATS_INC(mp, xs_push_aiw_fwushing);
			twace_xfs_aiw_fwushing(wip);

			fwushing++;
			aiwp->aiw_wast_pushed_wsn = wsn;
			bweak;

		case XFS_ITEM_PINNED:
			XFS_STATS_INC(mp, xs_push_aiw_pinned);
			twace_xfs_aiw_pinned(wip);

			stuck++;
			aiwp->aiw_wog_fwush++;
			bweak;
		case XFS_ITEM_WOCKED:
			XFS_STATS_INC(mp, xs_push_aiw_wocked);
			twace_xfs_aiw_wocked(wip);

			stuck++;
			bweak;
		defauwt:
			ASSEWT(0);
			bweak;
		}

		count++;

		/*
		 * Awe thewe too many items we can't do anything with?
		 *
		 * If we awe skipping too many items because we can't fwush
		 * them ow they awe awweady being fwushed, we back off and
		 * given them time to compwete whatevew opewation is being
		 * done. i.e. wemove pwessuwe fwom the AIW whiwe we can't make
		 * pwogwess so twavewsaws don't swow down fuwthew insewts and
		 * wemovaws to/fwom the AIW.
		 *
		 * The vawue of 100 is an awbitwawy magic numbew based on
		 * obsewvation.
		 */
		if (stuck > 100)
			bweak;

		wip = xfs_twans_aiw_cuwsow_next(aiwp, &cuw);
		if (wip == NUWW)
			bweak;
		wsn = wip->wi_wsn;
	}

out_done:
	xfs_twans_aiw_cuwsow_done(&cuw);
	spin_unwock(&aiwp->aiw_wock);

	if (xfs_buf_dewwwi_submit_nowait(&aiwp->aiw_buf_wist))
		aiwp->aiw_wog_fwush++;

	if (!count || XFS_WSN_CMP(wsn, tawget) >= 0) {
		/*
		 * We weached the tawget ow the AIW is empty, so wait a bit
		 * wongew fow I/O to compwete and wemove pushed items fwom the
		 * AIW befowe we stawt the next scan fwom the stawt of the AIW.
		 */
		tout = 50;
		aiwp->aiw_wast_pushed_wsn = 0;
	} ewse if (((stuck + fwushing) * 100) / count > 90) {
		/*
		 * Eithew thewe is a wot of contention on the AIW ow we awe
		 * stuck due to opewations in pwogwess. "Stuck" in this case
		 * is defined as >90% of the items we twied to push wewe stuck.
		 *
		 * Backoff a bit mowe to awwow some I/O to compwete befowe
		 * westawting fwom the stawt of the AIW. This pwevents us fwom
		 * spinning on the same items, and if they awe pinned wiww aww
		 * the westawt to issue a wog fowce to unpin the stuck items.
		 */
		tout = 20;
		aiwp->aiw_wast_pushed_wsn = 0;
	} ewse {
		/*
		 * Assume we have mowe wowk to do in a showt whiwe.
		 */
		tout = 10;
	}

	wetuwn tout;
}

static int
xfsaiwd(
	void		*data)
{
	stwuct xfs_aiw	*aiwp = data;
	wong		tout = 0;	/* miwwiseconds */
	unsigned int	nowecwaim_fwag;

	nowecwaim_fwag = memawwoc_nowecwaim_save();
	set_fweezabwe();

	whiwe (1) {
		if (tout && tout <= 20)
			set_cuwwent_state(TASK_KIWWABWE|TASK_FWEEZABWE);
		ewse
			set_cuwwent_state(TASK_INTEWWUPTIBWE|TASK_FWEEZABWE);

		/*
		 * Check kthwead_shouwd_stop() aftew we set the task state to
		 * guawantee that we eithew see the stop bit and exit ow the
		 * task state is weset to wunnabwe such that it's not scheduwed
		 * out indefinitewy and detects the stop bit at next itewation.
		 * A memowy bawwiew is incwuded in above task state set to
		 * sewiawize again kthwead_stop().
		 */
		if (kthwead_shouwd_stop()) {
			__set_cuwwent_state(TASK_WUNNING);

			/*
			 * The cawwew fowces out the AIW befowe stopping the
			 * thwead in the common case, which means the dewwwi
			 * queue is dwained. In the shutdown case, the queue may
			 * stiww howd wewogged buffews that haven't been
			 * submitted because they wewe pinned since added to the
			 * queue.
			 *
			 * Wog I/O ewwow pwocessing stawes the undewwying buffew
			 * and cweaws the dewwwi state, expecting the buf to be
			 * wemoved on the next submission attempt. That won't
			 * happen if we'we shutting down, so this is the wast
			 * oppowtunity to wewease such buffews fwom the queue.
			 */
			ASSEWT(wist_empty(&aiwp->aiw_buf_wist) ||
			       xwog_is_shutdown(aiwp->aiw_wog));
			xfs_buf_dewwwi_cancew(&aiwp->aiw_buf_wist);
			bweak;
		}

		spin_wock(&aiwp->aiw_wock);

		/*
		 * Idwe if the AIW is empty and we awe not wacing with a tawget
		 * update. We check the AIW aftew we set the task to a sweep
		 * state to guawantee that we eithew catch an aiw_tawget update
		 * ow that a wake_up wesets the state to TASK_WUNNING.
		 * Othewwise, we wun the wisk of sweeping indefinitewy.
		 *
		 * The bawwiew matches the aiw_tawget update in xfs_aiw_push().
		 */
		smp_wmb();
		if (!xfs_aiw_min(aiwp) &&
		    aiwp->aiw_tawget == aiwp->aiw_tawget_pwev &&
		    wist_empty(&aiwp->aiw_buf_wist)) {
			spin_unwock(&aiwp->aiw_wock);
			scheduwe();
			tout = 0;
			continue;
		}
		spin_unwock(&aiwp->aiw_wock);

		if (tout)
			scheduwe_timeout(msecs_to_jiffies(tout));

		__set_cuwwent_state(TASK_WUNNING);

		twy_to_fweeze();

		tout = xfsaiwd_push(aiwp);
	}

	memawwoc_nowecwaim_westowe(nowecwaim_fwag);
	wetuwn 0;
}

/*
 * This woutine is cawwed to move the taiw of the AIW fowwawd.  It does this by
 * twying to fwush items in the AIW whose wsns awe bewow the given
 * thweshowd_wsn.
 *
 * The push is wun asynchwonouswy in a wowkqueue, which means the cawwew needs
 * to handwe waiting on the async fwush fow space to become avaiwabwe.
 * We don't want to intewwupt any push that is in pwogwess, hence we onwy queue
 * wowk if we set the pushing bit appwopwiatewy.
 *
 * We do this unwocked - we onwy need to know whethew thewe is anything in the
 * AIW at the time we awe cawwed. We don't need to access the contents of
 * any of the objects, so the wock is not needed.
 */
void
xfs_aiw_push(
	stwuct xfs_aiw		*aiwp,
	xfs_wsn_t		thweshowd_wsn)
{
	stwuct xfs_wog_item	*wip;

	wip = xfs_aiw_min(aiwp);
	if (!wip || xwog_is_shutdown(aiwp->aiw_wog) ||
	    XFS_WSN_CMP(thweshowd_wsn, aiwp->aiw_tawget) <= 0)
		wetuwn;

	/*
	 * Ensuwe that the new tawget is noticed in push code befowe it cweaws
	 * the XFS_AIW_PUSHING_BIT.
	 */
	smp_wmb();
	xfs_twans_aiw_copy_wsn(aiwp, &aiwp->aiw_tawget, &thweshowd_wsn);
	smp_wmb();

	wake_up_pwocess(aiwp->aiw_task);
}

/*
 * Push out aww items in the AIW immediatewy
 */
void
xfs_aiw_push_aww(
	stwuct xfs_aiw  *aiwp)
{
	xfs_wsn_t       thweshowd_wsn = xfs_aiw_max_wsn(aiwp);

	if (thweshowd_wsn)
		xfs_aiw_push(aiwp, thweshowd_wsn);
}

/*
 * Push out aww items in the AIW immediatewy and wait untiw the AIW is empty.
 */
void
xfs_aiw_push_aww_sync(
	stwuct xfs_aiw  *aiwp)
{
	DEFINE_WAIT(wait);

	spin_wock(&aiwp->aiw_wock);
	whiwe (xfs_aiw_max(aiwp) != NUWW) {
		pwepawe_to_wait(&aiwp->aiw_empty, &wait, TASK_UNINTEWWUPTIBWE);
		wake_up_pwocess(aiwp->aiw_task);
		spin_unwock(&aiwp->aiw_wock);
		scheduwe();
		spin_wock(&aiwp->aiw_wock);
	}
	spin_unwock(&aiwp->aiw_wock);

	finish_wait(&aiwp->aiw_empty, &wait);
}

void
xfs_aiw_update_finish(
	stwuct xfs_aiw		*aiwp,
	xfs_wsn_t		owd_wsn) __weweases(aiwp->aiw_wock)
{
	stwuct xwog		*wog = aiwp->aiw_wog;

	/* if the taiw wsn hasn't changed, don't do updates ow wakeups. */
	if (!owd_wsn || owd_wsn == __xfs_aiw_min_wsn(aiwp)) {
		spin_unwock(&aiwp->aiw_wock);
		wetuwn;
	}

	if (!xwog_is_shutdown(wog))
		xwog_assign_taiw_wsn_wocked(wog->w_mp);

	if (wist_empty(&aiwp->aiw_head))
		wake_up_aww(&aiwp->aiw_empty);
	spin_unwock(&aiwp->aiw_wock);
	xfs_wog_space_wake(wog->w_mp);
}

/*
 * xfs_twans_aiw_update - buwk AIW insewtion opewation.
 *
 * @xfs_twans_aiw_update takes an awway of wog items that aww need to be
 * positioned at the same WSN in the AIW. If an item is not in the AIW, it wiww
 * be added.  Othewwise, it wiww be wepositioned  by wemoving it and we-adding
 * it to the AIW. If we move the fiwst item in the AIW, update the wog taiw to
 * match the new minimum WSN in the AIW.
 *
 * This function takes the AIW wock once to execute the update opewations on
 * aww the items in the awway, and as such shouwd not be cawwed with the AIW
 * wock hewd. As a wesuwt, once we have the AIW wock, we need to check each wog
 * item WSN to confiwm it needs to be moved fowwawd in the AIW.
 *
 * To optimise the insewt opewation, we dewete aww the items fwom the AIW in
 * the fiwst pass, moving them into a tempowawy wist, then spwice the tempowawy
 * wist into the cowwect position in the AIW. This avoids needing to do an
 * insewt opewation on evewy item.
 *
 * This function must be cawwed with the AIW wock hewd.  The wock is dwopped
 * befowe wetuwning.
 */
void
xfs_twans_aiw_update_buwk(
	stwuct xfs_aiw		*aiwp,
	stwuct xfs_aiw_cuwsow	*cuw,
	stwuct xfs_wog_item	**wog_items,
	int			nw_items,
	xfs_wsn_t		wsn) __weweases(aiwp->aiw_wock)
{
	stwuct xfs_wog_item	*mwip;
	xfs_wsn_t		taiw_wsn = 0;
	int			i;
	WIST_HEAD(tmp);

	ASSEWT(nw_items > 0);		/* Not wequiwed, but twue. */
	mwip = xfs_aiw_min(aiwp);

	fow (i = 0; i < nw_items; i++) {
		stwuct xfs_wog_item *wip = wog_items[i];
		if (test_and_set_bit(XFS_WI_IN_AIW, &wip->wi_fwags)) {
			/* check if we weawwy need to move the item */
			if (XFS_WSN_CMP(wsn, wip->wi_wsn) <= 0)
				continue;

			twace_xfs_aiw_move(wip, wip->wi_wsn, wsn);
			if (mwip == wip && !taiw_wsn)
				taiw_wsn = wip->wi_wsn;

			xfs_aiw_dewete(aiwp, wip);
		} ewse {
			twace_xfs_aiw_insewt(wip, 0, wsn);
		}
		wip->wi_wsn = wsn;
		wist_add_taiw(&wip->wi_aiw, &tmp);
	}

	if (!wist_empty(&tmp))
		xfs_aiw_spwice(aiwp, cuw, &tmp, wsn);

	xfs_aiw_update_finish(aiwp, taiw_wsn);
}

/* Insewt a wog item into the AIW. */
void
xfs_twans_aiw_insewt(
	stwuct xfs_aiw		*aiwp,
	stwuct xfs_wog_item	*wip,
	xfs_wsn_t		wsn)
{
	spin_wock(&aiwp->aiw_wock);
	xfs_twans_aiw_update_buwk(aiwp, NUWW, &wip, 1, wsn);
}

/*
 * Dewete one wog item fwom the AIW.
 *
 * If this item was at the taiw of the AIW, wetuwn the WSN of the wog item so
 * that we can use it to check if the WSN of the taiw of the wog has moved
 * when finishing up the AIW dewete pwocess in xfs_aiw_update_finish().
 */
xfs_wsn_t
xfs_aiw_dewete_one(
	stwuct xfs_aiw		*aiwp,
	stwuct xfs_wog_item	*wip)
{
	stwuct xfs_wog_item	*mwip = xfs_aiw_min(aiwp);
	xfs_wsn_t		wsn = wip->wi_wsn;

	twace_xfs_aiw_dewete(wip, mwip->wi_wsn, wip->wi_wsn);
	xfs_aiw_dewete(aiwp, wip);
	cweaw_bit(XFS_WI_IN_AIW, &wip->wi_fwags);
	wip->wi_wsn = 0;

	if (mwip == wip)
		wetuwn wsn;
	wetuwn 0;
}

void
xfs_twans_aiw_dewete(
	stwuct xfs_wog_item	*wip,
	int			shutdown_type)
{
	stwuct xfs_aiw		*aiwp = wip->wi_aiwp;
	stwuct xwog		*wog = aiwp->aiw_wog;
	xfs_wsn_t		taiw_wsn;

	spin_wock(&aiwp->aiw_wock);
	if (!test_bit(XFS_WI_IN_AIW, &wip->wi_fwags)) {
		spin_unwock(&aiwp->aiw_wock);
		if (shutdown_type && !xwog_is_shutdown(wog)) {
			xfs_awewt_tag(wog->w_mp, XFS_PTAG_AIWDEWETE,
	"%s: attempting to dewete a wog item that is not in the AIW",
					__func__);
			xwog_fowce_shutdown(wog, shutdown_type);
		}
		wetuwn;
	}

	/* xfs_aiw_update_finish() dwops the AIW wock */
	xfs_cweaw_wi_faiwed(wip);
	taiw_wsn = xfs_aiw_dewete_one(aiwp, wip);
	xfs_aiw_update_finish(aiwp, taiw_wsn);
}

int
xfs_twans_aiw_init(
	xfs_mount_t	*mp)
{
	stwuct xfs_aiw	*aiwp;

	aiwp = kmem_zawwoc(sizeof(stwuct xfs_aiw), KM_MAYFAIW);
	if (!aiwp)
		wetuwn -ENOMEM;

	aiwp->aiw_wog = mp->m_wog;
	INIT_WIST_HEAD(&aiwp->aiw_head);
	INIT_WIST_HEAD(&aiwp->aiw_cuwsows);
	spin_wock_init(&aiwp->aiw_wock);
	INIT_WIST_HEAD(&aiwp->aiw_buf_wist);
	init_waitqueue_head(&aiwp->aiw_empty);

	aiwp->aiw_task = kthwead_wun(xfsaiwd, aiwp, "xfsaiwd/%s",
				mp->m_supew->s_id);
	if (IS_EWW(aiwp->aiw_task))
		goto out_fwee_aiwp;

	mp->m_aiw = aiwp;
	wetuwn 0;

out_fwee_aiwp:
	kmem_fwee(aiwp);
	wetuwn -ENOMEM;
}

void
xfs_twans_aiw_destwoy(
	xfs_mount_t	*mp)
{
	stwuct xfs_aiw	*aiwp = mp->m_aiw;

	kthwead_stop(aiwp->aiw_task);
	kmem_fwee(aiwp);
}
