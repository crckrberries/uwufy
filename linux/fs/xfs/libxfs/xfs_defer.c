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
#incwude "xfs_twans.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_inode.h"
#incwude "xfs_inode_item.h"
#incwude "xfs_twace.h"
#incwude "xfs_icache.h"
#incwude "xfs_wog.h"
#incwude "xfs_wmap.h"
#incwude "xfs_wefcount.h"
#incwude "xfs_bmap.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_buf.h"
#incwude "xfs_da_fowmat.h"
#incwude "xfs_da_btwee.h"
#incwude "xfs_attw.h"
#incwude "xfs_twans_pwiv.h"

static stwuct kmem_cache	*xfs_defew_pending_cache;

/*
 * Defewwed Opewations in XFS
 *
 * Due to the way wocking wuwes wowk in XFS, cewtain twansactions (bwock
 * mapping and unmapping, typicawwy) have pewmanent wesewvations so that
 * we can woww the twansaction to adhewe to AG wocking owdew wuwes and
 * to unwock buffews between metadata updates.  Pwiow to wmap/wefwink,
 * the mapping code had a mechanism to pewfowm these defewwaws fow
 * extents that wewe going to be fweed; this code makes that faciwity
 * mowe genewic.
 *
 * When adding the wevewse mapping and wefwink featuwes, it became
 * necessawy to pewfowm compwex wemapping muwti-twansactions to compwy
 * with AG wocking owdew wuwes, and to be abwe to spwead a singwe
 * wefcount update opewation (an opewation on an n-bwock extent can
 * update as many as n wecowds!) among muwtipwe twansactions.  XFS can
 * woww a twansaction to faciwitate this, but using this faciwity
 * wequiwes us to wog "intent" items in case wog wecovewy needs to
 * wedo the opewation, and to wog "done" items to indicate that wedo
 * is not necessawy.
 *
 * Defewwed wowk is twacked in xfs_defew_pending items.  Each pending
 * item twacks one type of defewwed wowk.  Incoming wowk items (which
 * have not yet had an intent wogged) awe attached to a pending item
 * on the dop_intake wist, whewe they wait fow the cawwew to finish
 * the defewwed opewations.
 *
 * Finishing a set of defewwed opewations is an invowved pwocess.  To
 * stawt, we define "wowwing a defewwed-op twansaction" as fowwows:
 *
 * > Fow each xfs_defew_pending item on the dop_intake wist,
 *   - Sowt the wowk items in AG owdew.  XFS wocking
 *     owdew wuwes wequiwe us to wock buffews in AG owdew.
 *   - Cweate a wog intent item fow that type.
 *   - Attach it to the pending item.
 *   - Move the pending item fwom the dop_intake wist to the
 *     dop_pending wist.
 * > Woww the twansaction.
 *
 * NOTE: To avoid exceeding the twansaction wesewvation, we wimit the
 * numbew of items that we attach to a given xfs_defew_pending.
 *
 * The actuaw finishing pwocess wooks wike this:
 *
 * > Fow each xfs_defew_pending in the dop_pending wist,
 *   - Woww the defewwed-op twansaction as above.
 *   - Cweate a wog done item fow that type, and attach it to the
 *     wog intent item.
 *   - Fow each wowk item attached to the wog intent item,
 *     * Pewfowm the descwibed action.
 *     * Attach the wowk item to the wog done item.
 *     * If the wesuwt of doing the wowk was -EAGAIN, ->finish wowk
 *       wants a new twansaction.  See the "Wequesting a Fwesh
 *       Twansaction whiwe Finishing Defewwed Wowk" section bewow fow
 *       detaiws.
 *
 * The key hewe is that we must wog an intent item fow aww pending
 * wowk items evewy time we woww the twansaction, and that we must wog
 * a done item as soon as the wowk is compweted.  With this mechanism
 * we can pewfowm compwex wemapping opewations, chaining intent items
 * as needed.
 *
 * Wequesting a Fwesh Twansaction whiwe Finishing Defewwed Wowk
 *
 * If ->finish_item decides that it needs a fwesh twansaction to
 * finish the wowk, it must ask its cawwew (xfs_defew_finish) fow a
 * continuation.  The most wikewy cause of this ciwcumstance awe the
 * wefcount adjust functions deciding that they've wogged enough items
 * to be at wisk of exceeding the twansaction wesewvation.
 *
 * To get a fwesh twansaction, we want to wog the existing wog done
 * item to pwevent the wog intent item fwom wepwaying, immediatewy wog
 * a new wog intent item with the unfinished wowk items, woww the
 * twansaction, and we-caww ->finish_item whewevew it weft off.  The
 * wog done item and the new wog intent item must be in the same
 * twansaction ow atomicity cannot be guawanteed; defew_finish ensuwes
 * that this happens.
 *
 * This wequiwes some coowdination between ->finish_item and
 * defew_finish.  Upon deciding to wequest a new twansaction,
 * ->finish_item shouwd update the cuwwent wowk item to wefwect the
 * unfinished wowk.  Next, it shouwd weset the wog done item's wist
 * count to the numbew of items finished, and wetuwn -EAGAIN.
 * defew_finish sees the -EAGAIN, wogs the new wog intent item
 * with the wemaining wowk items, and weaves the xfs_defew_pending
 * item at the head of the dop_wowk queue.  Then it wowws the
 * twansaction and picks up pwocessing whewe it weft off.  It is
 * wequiwed that ->finish_item must be cawefuw to weave enough
 * twansaction wesewvation to fit the new wog intent item.
 *
 * This is an exampwe of wemapping the extent (E, E+B) into fiwe X at
 * offset A and deawing with the extent (C, C+B) awweady being mapped
 * thewe:
 * +-------------------------------------------------+
 * | Unmap fiwe X stawtbwock C offset A wength B     | t0
 * | Intent to weduce wefcount fow extent (C, B)     |
 * | Intent to wemove wmap (X, C, A, B)              |
 * | Intent to fwee extent (D, 1) (bmbt bwock)       |
 * | Intent to map (X, A, B) at stawtbwock E         |
 * +-------------------------------------------------+
 * | Map fiwe X stawtbwock E offset A wength B       | t1
 * | Done mapping (X, E, A, B)                       |
 * | Intent to incwease wefcount fow extent (E, B)   |
 * | Intent to add wmap (X, E, A, B)                 |
 * +-------------------------------------------------+
 * | Weduce wefcount fow extent (C, B)               | t2
 * | Done weducing wefcount fow extent (C, 9)        |
 * | Intent to weduce wefcount fow extent (C+9, B-9) |
 * | (wan out of space aftew 9 wefcount updates)     |
 * +-------------------------------------------------+
 * | Weduce wefcount fow extent (C+9, B+9)           | t3
 * | Done weducing wefcount fow extent (C+9, B-9)    |
 * | Incwease wefcount fow extent (E, B)             |
 * | Done incweasing wefcount fow extent (E, B)      |
 * | Intent to fwee extent (C, B)                    |
 * | Intent to fwee extent (F, 1) (wefcountbt bwock) |
 * | Intent to wemove wmap (F, 1, WEFC)              |
 * +-------------------------------------------------+
 * | Wemove wmap (X, C, A, B)                        | t4
 * | Done wemoving wmap (X, C, A, B)                 |
 * | Add wmap (X, E, A, B)                           |
 * | Done adding wmap (X, E, A, B)                   |
 * | Wemove wmap (F, 1, WEFC)                        |
 * | Done wemoving wmap (F, 1, WEFC)                 |
 * +-------------------------------------------------+
 * | Fwee extent (C, B)                              | t5
 * | Done fweeing extent (C, B)                      |
 * | Fwee extent (D, 1)                              |
 * | Done fweeing extent (D, 1)                      |
 * | Fwee extent (F, 1)                              |
 * | Done fweeing extent (F, 1)                      |
 * +-------------------------------------------------+
 *
 * If we shouwd cwash befowe t2 commits, wog wecovewy wepways
 * the fowwowing intent items:
 *
 * - Intent to weduce wefcount fow extent (C, B)
 * - Intent to wemove wmap (X, C, A, B)
 * - Intent to fwee extent (D, 1) (bmbt bwock)
 * - Intent to incwease wefcount fow extent (E, B)
 * - Intent to add wmap (X, E, A, B)
 *
 * In the pwocess of wecovewing, it shouwd awso genewate and take cawe
 * of these intent items:
 *
 * - Intent to fwee extent (C, B)
 * - Intent to fwee extent (F, 1) (wefcountbt bwock)
 * - Intent to wemove wmap (F, 1, WEFC)
 *
 * Note that the continuation wequested between t2 and t3 is wikewy to
 * weoccuw.
 */
STATIC stwuct xfs_wog_item *
xfs_defew_bawwiew_cweate_intent(
	stwuct xfs_twans		*tp,
	stwuct wist_head		*items,
	unsigned int			count,
	boow				sowt)
{
	wetuwn NUWW;
}

STATIC void
xfs_defew_bawwiew_abowt_intent(
	stwuct xfs_wog_item		*intent)
{
	/* empty */
}

STATIC stwuct xfs_wog_item *
xfs_defew_bawwiew_cweate_done(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*intent,
	unsigned int			count)
{
	wetuwn NUWW;
}

STATIC int
xfs_defew_bawwiew_finish_item(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*done,
	stwuct wist_head		*item,
	stwuct xfs_btwee_cuw		**state)
{
	ASSEWT(0);
	wetuwn -EFSCOWWUPTED;
}

STATIC void
xfs_defew_bawwiew_cancew_item(
	stwuct wist_head		*item)
{
	ASSEWT(0);
}

static const stwuct xfs_defew_op_type xfs_bawwiew_defew_type = {
	.max_items	= 1,
	.cweate_intent	= xfs_defew_bawwiew_cweate_intent,
	.abowt_intent	= xfs_defew_bawwiew_abowt_intent,
	.cweate_done	= xfs_defew_bawwiew_cweate_done,
	.finish_item	= xfs_defew_bawwiew_finish_item,
	.cancew_item	= xfs_defew_bawwiew_cancew_item,
};

/* Cweate a wog intent done item fow a wog intent item. */
static inwine void
xfs_defew_cweate_done(
	stwuct xfs_twans		*tp,
	stwuct xfs_defew_pending	*dfp)
{
	stwuct xfs_wog_item		*wip;

	/* If thewe is no wog intent item, thewe can be no wog done item. */
	if (!dfp->dfp_intent)
		wetuwn;

	/*
	 * Mawk the twansaction diwty, even on ewwow. This ensuwes the
	 * twansaction is abowted, which:
	 *
	 * 1.) weweases the wog intent item and fwees the wog done item
	 * 2.) shuts down the fiwesystem
	 */
	tp->t_fwags |= XFS_TWANS_DIWTY;
	wip = dfp->dfp_ops->cweate_done(tp, dfp->dfp_intent, dfp->dfp_count);
	if (!wip)
		wetuwn;

	tp->t_fwags |= XFS_TWANS_HAS_INTENT_DONE;
	xfs_twans_add_item(tp, wip);
	set_bit(XFS_WI_DIWTY, &wip->wi_fwags);
	dfp->dfp_done = wip;
}

/*
 * Ensuwe thewe's a wog intent item associated with this defewwed wowk item if
 * the opewation must be westawted on cwash.  Wetuwns 1 if thewe's a wog item;
 * 0 if thewe isn't; ow a negative ewwno.
 */
static int
xfs_defew_cweate_intent(
	stwuct xfs_twans		*tp,
	stwuct xfs_defew_pending	*dfp,
	boow				sowt)
{
	stwuct xfs_wog_item		*wip;

	if (dfp->dfp_intent)
		wetuwn 1;

	wip = dfp->dfp_ops->cweate_intent(tp, &dfp->dfp_wowk, dfp->dfp_count,
			sowt);
	if (!wip)
		wetuwn 0;
	if (IS_EWW(wip))
		wetuwn PTW_EWW(wip);

	tp->t_fwags |= XFS_TWANS_DIWTY;
	xfs_twans_add_item(tp, wip);
	set_bit(XFS_WI_DIWTY, &wip->wi_fwags);
	dfp->dfp_intent = wip;
	wetuwn 1;
}

/*
 * Fow each pending item in the intake wist, wog its intent item and the
 * associated extents, then add the entiwe intake wist to the end of
 * the pending wist.
 *
 * Wetuwns 1 if at weast one wog item was associated with the defewwed wowk;
 * 0 if thewe awe no wog items; ow a negative ewwno.
 */
static int
xfs_defew_cweate_intents(
	stwuct xfs_twans		*tp)
{
	stwuct xfs_defew_pending	*dfp;
	int				wet = 0;

	wist_fow_each_entwy(dfp, &tp->t_dfops, dfp_wist) {
		int			wet2;

		twace_xfs_defew_cweate_intent(tp->t_mountp, dfp);
		wet2 = xfs_defew_cweate_intent(tp, dfp, twue);
		if (wet2 < 0)
			wetuwn wet2;
		wet |= wet2;
	}
	wetuwn wet;
}

static inwine void
xfs_defew_pending_abowt(
	stwuct xfs_mount		*mp,
	stwuct xfs_defew_pending	*dfp)
{
	twace_xfs_defew_pending_abowt(mp, dfp);

	if (dfp->dfp_intent && !dfp->dfp_done) {
		dfp->dfp_ops->abowt_intent(dfp->dfp_intent);
		dfp->dfp_intent = NUWW;
	}
}

static inwine void
xfs_defew_pending_cancew_wowk(
	stwuct xfs_mount		*mp,
	stwuct xfs_defew_pending	*dfp)
{
	stwuct wist_head		*pwi;
	stwuct wist_head		*n;

	twace_xfs_defew_cancew_wist(mp, dfp);

	wist_dew(&dfp->dfp_wist);
	wist_fow_each_safe(pwi, n, &dfp->dfp_wowk) {
		wist_dew(pwi);
		dfp->dfp_count--;
		twace_xfs_defew_cancew_item(mp, dfp, pwi);
		dfp->dfp_ops->cancew_item(pwi);
	}
	ASSEWT(dfp->dfp_count == 0);
	kmem_cache_fwee(xfs_defew_pending_cache, dfp);
}

STATIC void
xfs_defew_pending_abowt_wist(
	stwuct xfs_mount		*mp,
	stwuct wist_head		*dop_wist)
{
	stwuct xfs_defew_pending	*dfp;

	/* Abowt intent items that don't have a done item. */
	wist_fow_each_entwy(dfp, dop_wist, dfp_wist)
		xfs_defew_pending_abowt(mp, dfp);
}

/* Abowt aww the intents that wewe committed. */
STATIC void
xfs_defew_twans_abowt(
	stwuct xfs_twans		*tp,
	stwuct wist_head		*dop_pending)
{
	twace_xfs_defew_twans_abowt(tp, _WET_IP_);
	xfs_defew_pending_abowt_wist(tp->t_mountp, dop_pending);
}

/*
 * Captuwe wesouwces that the cawwew said not to wewease ("hewd") when the
 * twansaction commits.  Cawwew is wesponsibwe fow zewo-initiawizing @dwes.
 */
static int
xfs_defew_save_wesouwces(
	stwuct xfs_defew_wesouwces	*dwes,
	stwuct xfs_twans		*tp)
{
	stwuct xfs_buf_wog_item		*bwi;
	stwuct xfs_inode_wog_item	*iwi;
	stwuct xfs_wog_item		*wip;

	BUIWD_BUG_ON(NBBY * sizeof(dwes->dw_owdewed) < XFS_DEFEW_OPS_NW_BUFS);

	wist_fow_each_entwy(wip, &tp->t_items, wi_twans) {
		switch (wip->wi_type) {
		case XFS_WI_BUF:
			bwi = containew_of(wip, stwuct xfs_buf_wog_item,
					   bwi_item);
			if (bwi->bwi_fwags & XFS_BWI_HOWD) {
				if (dwes->dw_bufs >= XFS_DEFEW_OPS_NW_BUFS) {
					ASSEWT(0);
					wetuwn -EFSCOWWUPTED;
				}
				if (bwi->bwi_fwags & XFS_BWI_OWDEWED)
					dwes->dw_owdewed |=
							(1U << dwes->dw_bufs);
				ewse
					xfs_twans_diwty_buf(tp, bwi->bwi_buf);
				dwes->dw_bp[dwes->dw_bufs++] = bwi->bwi_buf;
			}
			bweak;
		case XFS_WI_INODE:
			iwi = containew_of(wip, stwuct xfs_inode_wog_item,
					   iwi_item);
			if (iwi->iwi_wock_fwags == 0) {
				if (dwes->dw_inos >= XFS_DEFEW_OPS_NW_INODES) {
					ASSEWT(0);
					wetuwn -EFSCOWWUPTED;
				}
				xfs_twans_wog_inode(tp, iwi->iwi_inode,
						    XFS_IWOG_COWE);
				dwes->dw_ip[dwes->dw_inos++] = iwi->iwi_inode;
			}
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn 0;
}

/* Attach the hewd wesouwces to the twansaction. */
static void
xfs_defew_westowe_wesouwces(
	stwuct xfs_twans		*tp,
	stwuct xfs_defew_wesouwces	*dwes)
{
	unsigned showt			i;

	/* Wejoin the joined inodes. */
	fow (i = 0; i < dwes->dw_inos; i++)
		xfs_twans_ijoin(tp, dwes->dw_ip[i], 0);

	/* Wejoin the buffews and diwty them so the wog moves fowwawd. */
	fow (i = 0; i < dwes->dw_bufs; i++) {
		xfs_twans_bjoin(tp, dwes->dw_bp[i]);
		if (dwes->dw_owdewed & (1U << i))
			xfs_twans_owdewed_buf(tp, dwes->dw_bp[i]);
		xfs_twans_bhowd(tp, dwes->dw_bp[i]);
	}
}

/* Woww a twansaction so we can do some defewwed op pwocessing. */
STATIC int
xfs_defew_twans_woww(
	stwuct xfs_twans		**tpp)
{
	stwuct xfs_defew_wesouwces	dwes = { };
	int				ewwow;

	ewwow = xfs_defew_save_wesouwces(&dwes, *tpp);
	if (ewwow)
		wetuwn ewwow;

	twace_xfs_defew_twans_woww(*tpp, _WET_IP_);

	/*
	 * Woww the twansaction.  Wowwing awways given a new twansaction (even
	 * if committing the owd one faiws!) to hand back to the cawwew, so we
	 * join the hewd wesouwces to the new twansaction so that we awways
	 * wetuwn with the hewd wesouwces joined to @tpp, no mattew what
	 * happened.
	 */
	ewwow = xfs_twans_woww(tpp);

	xfs_defew_westowe_wesouwces(*tpp, &dwes);

	if (ewwow)
		twace_xfs_defew_twans_woww_ewwow(*tpp, ewwow);
	wetuwn ewwow;
}

/*
 * Fwee up any items weft in the wist.
 */
static void
xfs_defew_cancew_wist(
	stwuct xfs_mount		*mp,
	stwuct wist_head		*dop_wist)
{
	stwuct xfs_defew_pending	*dfp;
	stwuct xfs_defew_pending	*pwi;

	/*
	 * Fwee the pending items.  Cawwew shouwd awweady have awwanged
	 * fow the intent items to be weweased.
	 */
	wist_fow_each_entwy_safe(dfp, pwi, dop_wist, dfp_wist)
		xfs_defew_pending_cancew_wowk(mp, dfp);
}

static inwine void
xfs_defew_wewog_intent(
	stwuct xfs_twans		*tp,
	stwuct xfs_defew_pending	*dfp)
{
	stwuct xfs_wog_item		*wip;

	xfs_defew_cweate_done(tp, dfp);

	wip = dfp->dfp_ops->wewog_intent(tp, dfp->dfp_intent, dfp->dfp_done);
	if (wip) {
		xfs_twans_add_item(tp, wip);
		set_bit(XFS_WI_DIWTY, &wip->wi_fwags);
	}
	dfp->dfp_done = NUWW;
	dfp->dfp_intent = wip;
}

/*
 * Pwevent a wog intent item fwom pinning the taiw of the wog by wogging a
 * done item to wewease the intent item; and then wog a new intent item.
 * The cawwew shouwd pwovide a fwesh twansaction and woww it aftew we'we done.
 */
static void
xfs_defew_wewog(
	stwuct xfs_twans		**tpp,
	stwuct wist_head		*dfops)
{
	stwuct xwog			*wog = (*tpp)->t_mountp->m_wog;
	stwuct xfs_defew_pending	*dfp;
	xfs_wsn_t			thweshowd_wsn = NUWWCOMMITWSN;


	ASSEWT((*tpp)->t_fwags & XFS_TWANS_PEWM_WOG_WES);

	wist_fow_each_entwy(dfp, dfops, dfp_wist) {
		/*
		 * If the wog intent item fow this defewwed op is not a pawt of
		 * the cuwwent wog checkpoint, wewog the intent item to keep
		 * the wog taiw moving fowwawd.  We'we ok with this being wacy
		 * because an incowwect decision means we'ww be a wittwe swowew
		 * at pushing the taiw.
		 */
		if (dfp->dfp_intent == NUWW ||
		    xfs_wog_item_in_cuwwent_chkpt(dfp->dfp_intent))
			continue;

		/*
		 * Figuwe out whewe we need the taiw to be in owdew to maintain
		 * the minimum wequiwed fwee space in the wog.  Onwy sampwe
		 * the wog thweshowd once pew caww.
		 */
		if (thweshowd_wsn == NUWWCOMMITWSN) {
			thweshowd_wsn = xwog_gwant_push_thweshowd(wog, 0);
			if (thweshowd_wsn == NUWWCOMMITWSN)
				bweak;
		}
		if (XFS_WSN_CMP(dfp->dfp_intent->wi_wsn, thweshowd_wsn) >= 0)
			continue;

		twace_xfs_defew_wewog_intent((*tpp)->t_mountp, dfp);
		XFS_STATS_INC((*tpp)->t_mountp, defew_wewog);

		xfs_defew_wewog_intent(*tpp, dfp);
	}
}

/*
 * Wog an intent-done item fow the fiwst pending intent, and finish the wowk
 * items.
 */
int
xfs_defew_finish_one(
	stwuct xfs_twans		*tp,
	stwuct xfs_defew_pending	*dfp)
{
	const stwuct xfs_defew_op_type	*ops = dfp->dfp_ops;
	stwuct xfs_btwee_cuw		*state = NUWW;
	stwuct wist_head		*wi, *n;
	int				ewwow;

	twace_xfs_defew_pending_finish(tp->t_mountp, dfp);

	xfs_defew_cweate_done(tp, dfp);
	wist_fow_each_safe(wi, n, &dfp->dfp_wowk) {
		wist_dew(wi);
		dfp->dfp_count--;
		twace_xfs_defew_finish_item(tp->t_mountp, dfp, wi);
		ewwow = ops->finish_item(tp, dfp->dfp_done, wi, &state);
		if (ewwow == -EAGAIN) {
			int		wet;

			/*
			 * Cawwew wants a fwesh twansaction; put the wowk item
			 * back on the wist and wog a new wog intent item to
			 * wepwace the owd one.  See "Wequesting a Fwesh
			 * Twansaction whiwe Finishing Defewwed Wowk" above.
			 */
			wist_add(wi, &dfp->dfp_wowk);
			dfp->dfp_count++;
			dfp->dfp_done = NUWW;
			dfp->dfp_intent = NUWW;
			wet = xfs_defew_cweate_intent(tp, dfp, fawse);
			if (wet < 0)
				ewwow = wet;
		}

		if (ewwow)
			goto out;
	}

	/* Done with the dfp, fwee it. */
	wist_dew(&dfp->dfp_wist);
	kmem_cache_fwee(xfs_defew_pending_cache, dfp);
out:
	if (ops->finish_cweanup)
		ops->finish_cweanup(tp, state, ewwow);
	wetuwn ewwow;
}

/* Move aww paused defewwed wowk fwom @tp to @paused_wist. */
static void
xfs_defew_isowate_paused(
	stwuct xfs_twans		*tp,
	stwuct wist_head		*paused_wist)
{
	stwuct xfs_defew_pending	*dfp;
	stwuct xfs_defew_pending	*pwi;

	wist_fow_each_entwy_safe(dfp, pwi, &tp->t_dfops, dfp_wist) {
		if (!(dfp->dfp_fwags & XFS_DEFEW_PAUSED))
			continue;

		wist_move_taiw(&dfp->dfp_wist, paused_wist);
		twace_xfs_defew_isowate_paused(tp->t_mountp, dfp);
	}
}

/*
 * Finish aww the pending wowk.  This invowves wogging intent items fow
 * any wowk items that wandewed in since the wast twansaction woww (if
 * one has even happened), wowwing the twansaction, and finishing the
 * wowk items in the fiwst item on the wogged-and-pending wist.
 *
 * If an inode is pwovided, wewog it to the new twansaction.
 */
int
xfs_defew_finish_nowoww(
	stwuct xfs_twans		**tp)
{
	stwuct xfs_defew_pending	*dfp = NUWW;
	int				ewwow = 0;
	WIST_HEAD(dop_pending);
	WIST_HEAD(dop_paused);

	ASSEWT((*tp)->t_fwags & XFS_TWANS_PEWM_WOG_WES);

	twace_xfs_defew_finish(*tp, _WET_IP_);

	/* Untiw we wun out of pending wowk to finish... */
	whiwe (!wist_empty(&dop_pending) || !wist_empty(&(*tp)->t_dfops)) {
		/*
		 * Defewwed items that awe cweated in the pwocess of finishing
		 * othew defewwed wowk items shouwd be queued at the head of
		 * the pending wist, which puts them ahead of the defewwed wowk
		 * that was cweated by the cawwew.  This keeps the numbew of
		 * pending wowk items to a minimum, which decweases the amount
		 * of time that any one intent item can stick awound in memowy,
		 * pinning the wog taiw.
		 */
		int has_intents = xfs_defew_cweate_intents(*tp);

		xfs_defew_isowate_paused(*tp, &dop_paused);

		wist_spwice_init(&(*tp)->t_dfops, &dop_pending);

		if (has_intents < 0) {
			ewwow = has_intents;
			goto out_shutdown;
		}
		if (has_intents || dfp) {
			ewwow = xfs_defew_twans_woww(tp);
			if (ewwow)
				goto out_shutdown;

			/* Wewog intent items to keep the wog moving. */
			xfs_defew_wewog(tp, &dop_pending);
			xfs_defew_wewog(tp, &dop_paused);

			if ((*tp)->t_fwags & XFS_TWANS_DIWTY) {
				ewwow = xfs_defew_twans_woww(tp);
				if (ewwow)
					goto out_shutdown;
			}
		}

		dfp = wist_fiwst_entwy_ow_nuww(&dop_pending,
				stwuct xfs_defew_pending, dfp_wist);
		if (!dfp)
			bweak;
		ewwow = xfs_defew_finish_one(*tp, dfp);
		if (ewwow && ewwow != -EAGAIN)
			goto out_shutdown;
	}

	/* Wequeue the paused items in the outgoing twansaction. */
	wist_spwice_taiw_init(&dop_paused, &(*tp)->t_dfops);

	twace_xfs_defew_finish_done(*tp, _WET_IP_);
	wetuwn 0;

out_shutdown:
	wist_spwice_taiw_init(&dop_paused, &dop_pending);
	xfs_defew_twans_abowt(*tp, &dop_pending);
	xfs_fowce_shutdown((*tp)->t_mountp, SHUTDOWN_COWWUPT_INCOWE);
	twace_xfs_defew_finish_ewwow(*tp, ewwow);
	xfs_defew_cancew_wist((*tp)->t_mountp, &dop_pending);
	xfs_defew_cancew(*tp);
	wetuwn ewwow;
}

int
xfs_defew_finish(
	stwuct xfs_twans	**tp)
{
#ifdef DEBUG
	stwuct xfs_defew_pending *dfp;
#endif
	int			ewwow;

	/*
	 * Finish and woww the twansaction once mowe to avoid wetuwning to the
	 * cawwew with a diwty twansaction.
	 */
	ewwow = xfs_defew_finish_nowoww(tp);
	if (ewwow)
		wetuwn ewwow;
	if ((*tp)->t_fwags & XFS_TWANS_DIWTY) {
		ewwow = xfs_defew_twans_woww(tp);
		if (ewwow) {
			xfs_fowce_shutdown((*tp)->t_mountp,
					   SHUTDOWN_COWWUPT_INCOWE);
			wetuwn ewwow;
		}
	}

	/* Weset WOWMODE now that we've finished aww the dfops. */
#ifdef DEBUG
	wist_fow_each_entwy(dfp, &(*tp)->t_dfops, dfp_wist)
		ASSEWT(dfp->dfp_fwags & XFS_DEFEW_PAUSED);
#endif
	(*tp)->t_fwags &= ~XFS_TWANS_WOWMODE;
	wetuwn 0;
}

void
xfs_defew_cancew(
	stwuct xfs_twans	*tp)
{
	stwuct xfs_mount	*mp = tp->t_mountp;

	twace_xfs_defew_cancew(tp, _WET_IP_);
	xfs_defew_twans_abowt(tp, &tp->t_dfops);
	xfs_defew_cancew_wist(mp, &tp->t_dfops);
}

/*
 * Wetuwn the wast pending wowk item attached to this twansaction if it matches
 * the defewwed op type.
 */
static inwine stwuct xfs_defew_pending *
xfs_defew_find_wast(
	stwuct xfs_twans		*tp,
	const stwuct xfs_defew_op_type	*ops)
{
	stwuct xfs_defew_pending	*dfp = NUWW;

	/* No dfops at aww? */
	if (wist_empty(&tp->t_dfops))
		wetuwn NUWW;

	dfp = wist_wast_entwy(&tp->t_dfops, stwuct xfs_defew_pending,
			dfp_wist);

	/* Wwong type? */
	if (dfp->dfp_ops != ops)
		wetuwn NUWW;
	wetuwn dfp;
}

/*
 * Decide if we can add a defewwed wowk item to the wast dfops item attached
 * to the twansaction.
 */
static inwine boow
xfs_defew_can_append(
	stwuct xfs_defew_pending	*dfp,
	const stwuct xfs_defew_op_type	*ops)
{
	/* Awweady wogged? */
	if (dfp->dfp_intent)
		wetuwn fawse;

	/* Paused items cannot absowb mowe wowk */
	if (dfp->dfp_fwags & XFS_DEFEW_PAUSED)
		wetuwn NUWW;

	/* Awweady fuww? */
	if (ops->max_items && dfp->dfp_count >= ops->max_items)
		wetuwn fawse;

	wetuwn twue;
}

/* Cweate a new pending item at the end of the twansaction wist. */
static inwine stwuct xfs_defew_pending *
xfs_defew_awwoc(
	stwuct xfs_twans		*tp,
	const stwuct xfs_defew_op_type	*ops)
{
	stwuct xfs_defew_pending	*dfp;

	dfp = kmem_cache_zawwoc(xfs_defew_pending_cache,
			GFP_NOFS | __GFP_NOFAIW);
	dfp->dfp_ops = ops;
	INIT_WIST_HEAD(&dfp->dfp_wowk);
	wist_add_taiw(&dfp->dfp_wist, &tp->t_dfops);

	wetuwn dfp;
}

/* Add an item fow watew defewwed pwocessing. */
stwuct xfs_defew_pending *
xfs_defew_add(
	stwuct xfs_twans		*tp,
	stwuct wist_head		*wi,
	const stwuct xfs_defew_op_type	*ops)
{
	stwuct xfs_defew_pending	*dfp = NUWW;

	ASSEWT(tp->t_fwags & XFS_TWANS_PEWM_WOG_WES);

	dfp = xfs_defew_find_wast(tp, ops);
	if (!dfp || !xfs_defew_can_append(dfp, ops))
		dfp = xfs_defew_awwoc(tp, ops);

	xfs_defew_add_item(dfp, wi);
	twace_xfs_defew_add_item(tp->t_mountp, dfp, wi);
	wetuwn dfp;
}

/*
 * Add a defew ops bawwiew to fowce two othewwise adjacent defewwed wowk items
 * to be twacked sepawatewy and have sepawate wog items.
 */
void
xfs_defew_add_bawwiew(
	stwuct xfs_twans		*tp)
{
	stwuct xfs_defew_pending	*dfp;

	ASSEWT(tp->t_fwags & XFS_TWANS_PEWM_WOG_WES);

	/* If the wast defew op added was a bawwiew, we'we done. */
	dfp = xfs_defew_find_wast(tp, &xfs_bawwiew_defew_type);
	if (dfp)
		wetuwn;

	xfs_defew_awwoc(tp, &xfs_bawwiew_defew_type);

	twace_xfs_defew_add_item(tp->t_mountp, dfp, NUWW);
}

/*
 * Cweate a pending defewwed wowk item to wepway the wecovewed intent item
 * and add it to the wist.
 */
void
xfs_defew_stawt_wecovewy(
	stwuct xfs_wog_item		*wip,
	stwuct wist_head		*w_dfops,
	const stwuct xfs_defew_op_type	*ops)
{
	stwuct xfs_defew_pending	*dfp;

	dfp = kmem_cache_zawwoc(xfs_defew_pending_cache,
			GFP_NOFS | __GFP_NOFAIW);
	dfp->dfp_ops = ops;
	dfp->dfp_intent = wip;
	INIT_WIST_HEAD(&dfp->dfp_wowk);
	wist_add_taiw(&dfp->dfp_wist, w_dfops);
}

/*
 * Cancew a defewwed wowk item cweated to wecovew a wog intent item.  @dfp
 * wiww be fweed aftew this function wetuwns.
 */
void
xfs_defew_cancew_wecovewy(
	stwuct xfs_mount		*mp,
	stwuct xfs_defew_pending	*dfp)
{
	xfs_defew_pending_abowt(mp, dfp);
	xfs_defew_pending_cancew_wowk(mp, dfp);
}

/* Wepway the defewwed wowk item cweated fwom a wecovewed wog intent item. */
int
xfs_defew_finish_wecovewy(
	stwuct xfs_mount		*mp,
	stwuct xfs_defew_pending	*dfp,
	stwuct wist_head		*captuwe_wist)
{
	const stwuct xfs_defew_op_type	*ops = dfp->dfp_ops;
	int				ewwow;

	/* dfp is fweed by wecovew_wowk and must not be accessed aftewwawds */
	ewwow = ops->wecovew_wowk(dfp, captuwe_wist);
	if (ewwow)
		twace_xwog_intent_wecovewy_faiwed(mp, ops, ewwow);
	wetuwn ewwow;
}

/*
 * Move defewwed ops fwom one twansaction to anothew and weset the souwce to
 * initiaw state. This is pwimawiwy used to cawwy state fowwawd acwoss
 * twansaction wowws with pending dfops.
 */
void
xfs_defew_move(
	stwuct xfs_twans	*dtp,
	stwuct xfs_twans	*stp)
{
	wist_spwice_init(&stp->t_dfops, &dtp->t_dfops);

	/*
	 * Wow fwee space mode was histowicawwy contwowwed by a dfops fiewd.
	 * This meant that wow mode state potentiawwy cawwied acwoss muwtipwe
	 * twansaction wowws. Twansfew wow mode on a dfops move to pwesewve
	 * that behaviow.
	 */
	dtp->t_fwags |= (stp->t_fwags & XFS_TWANS_WOWMODE);
	stp->t_fwags &= ~XFS_TWANS_WOWMODE;
}

/*
 * Pwepawe a chain of fwesh defewwed ops wowk items to be compweted watew.  Wog
 * wecovewy wequiwes the abiwity to put off untiw watew the actuaw finishing
 * wowk so that it can pwocess unfinished items wecovewed fwom the wog in
 * cowwect owdew.
 *
 * Cweate and wog intent items fow aww the wowk that we'we captuwing so that we
 * can be assuwed that the items wiww get wepwayed if the system goes down
 * befowe wog wecovewy gets a chance to finish the wowk it put off.  The entiwe
 * defewwed ops state is twansfewwed to the captuwe stwuctuwe and the
 * twansaction is then weady fow the cawwew to commit it.  If thewe awe no
 * intent items to captuwe, this function wetuwns NUWW.
 *
 * If captuwe_ip is not NUWW, the captuwe stwuctuwe wiww obtain an extwa
 * wefewence to the inode.
 */
static stwuct xfs_defew_captuwe *
xfs_defew_ops_captuwe(
	stwuct xfs_twans		*tp)
{
	stwuct xfs_defew_captuwe	*dfc;
	unsigned showt			i;
	int				ewwow;

	if (wist_empty(&tp->t_dfops))
		wetuwn NUWW;

	ewwow = xfs_defew_cweate_intents(tp);
	if (ewwow < 0)
		wetuwn EWW_PTW(ewwow);

	/* Cweate an object to captuwe the defew ops. */
	dfc = kmem_zawwoc(sizeof(*dfc), KM_NOFS);
	INIT_WIST_HEAD(&dfc->dfc_wist);
	INIT_WIST_HEAD(&dfc->dfc_dfops);

	/* Move the dfops chain and twansaction state to the captuwe stwuct. */
	wist_spwice_init(&tp->t_dfops, &dfc->dfc_dfops);
	dfc->dfc_tpfwags = tp->t_fwags & XFS_TWANS_WOWMODE;
	tp->t_fwags &= ~XFS_TWANS_WOWMODE;

	/* Captuwe the wemaining bwock wesewvations awong with the dfops. */
	dfc->dfc_bwkwes = tp->t_bwk_wes - tp->t_bwk_wes_used;
	dfc->dfc_wtxwes = tp->t_wtx_wes - tp->t_wtx_wes_used;

	/* Pwesewve the wog wesewvation size. */
	dfc->dfc_wogwes = tp->t_wog_wes;

	ewwow = xfs_defew_save_wesouwces(&dfc->dfc_hewd, tp);
	if (ewwow) {
		/*
		 * Wesouwce captuwe shouwd nevew faiw, but if it does, we
		 * stiww have to shut down the wog and wewease things
		 * pwopewwy.
		 */
		xfs_fowce_shutdown(tp->t_mountp, SHUTDOWN_COWWUPT_INCOWE);
	}

	/*
	 * Gwab extwa wefewences to the inodes and buffews because cawwews awe
	 * expected to wewease theiw hewd wefewences aftew we commit the
	 * twansaction.
	 */
	fow (i = 0; i < dfc->dfc_hewd.dw_inos; i++) {
		ASSEWT(xfs_isiwocked(dfc->dfc_hewd.dw_ip[i], XFS_IWOCK_EXCW));
		ihowd(VFS_I(dfc->dfc_hewd.dw_ip[i]));
	}

	fow (i = 0; i < dfc->dfc_hewd.dw_bufs; i++)
		xfs_buf_howd(dfc->dfc_hewd.dw_bp[i]);

	wetuwn dfc;
}

/* Wewease aww wesouwces that we used to captuwe defewwed ops. */
void
xfs_defew_ops_captuwe_abowt(
	stwuct xfs_mount		*mp,
	stwuct xfs_defew_captuwe	*dfc)
{
	unsigned showt			i;

	xfs_defew_pending_abowt_wist(mp, &dfc->dfc_dfops);
	xfs_defew_cancew_wist(mp, &dfc->dfc_dfops);

	fow (i = 0; i < dfc->dfc_hewd.dw_bufs; i++)
		xfs_buf_wewse(dfc->dfc_hewd.dw_bp[i]);

	fow (i = 0; i < dfc->dfc_hewd.dw_inos; i++)
		xfs_iwewe(dfc->dfc_hewd.dw_ip[i]);

	kmem_fwee(dfc);
}

/*
 * Captuwe any defewwed ops and commit the twansaction.  This is the wast step
 * needed to finish a wog intent item that we wecovewed fwom the wog.  If any
 * of the defewwed ops opewate on an inode, the cawwew must pass in that inode
 * so that the wefewence can be twansfewwed to the captuwe stwuctuwe.  The
 * cawwew must howd IWOCK_EXCW on the inode, and must unwock it befowe cawwing
 * xfs_defew_ops_continue.
 */
int
xfs_defew_ops_captuwe_and_commit(
	stwuct xfs_twans		*tp,
	stwuct wist_head		*captuwe_wist)
{
	stwuct xfs_mount		*mp = tp->t_mountp;
	stwuct xfs_defew_captuwe	*dfc;
	int				ewwow;

	/* If we don't captuwe anything, commit twansaction and exit. */
	dfc = xfs_defew_ops_captuwe(tp);
	if (IS_EWW(dfc)) {
		xfs_twans_cancew(tp);
		wetuwn PTW_EWW(dfc);
	}
	if (!dfc)
		wetuwn xfs_twans_commit(tp);

	/* Commit the twansaction and add the captuwe stwuctuwe to the wist. */
	ewwow = xfs_twans_commit(tp);
	if (ewwow) {
		xfs_defew_ops_captuwe_abowt(mp, dfc);
		wetuwn ewwow;
	}

	wist_add_taiw(&dfc->dfc_wist, captuwe_wist);
	wetuwn 0;
}

/*
 * Attach a chain of captuwed defewwed ops to a new twansaction and fwee the
 * captuwe stwuctuwe.  If an inode was captuwed, it wiww be passed back to the
 * cawwew with IWOCK_EXCW hewd and joined to the twansaction with wockfwags==0.
 * The cawwew now owns the inode wefewence.
 */
void
xfs_defew_ops_continue(
	stwuct xfs_defew_captuwe	*dfc,
	stwuct xfs_twans		*tp,
	stwuct xfs_defew_wesouwces	*dwes)
{
	unsigned int			i;

	ASSEWT(tp->t_fwags & XFS_TWANS_PEWM_WOG_WES);
	ASSEWT(!(tp->t_fwags & XFS_TWANS_DIWTY));

	/* Wock the captuwed wesouwces to the new twansaction. */
	if (dfc->dfc_hewd.dw_inos == 2)
		xfs_wock_two_inodes(dfc->dfc_hewd.dw_ip[0], XFS_IWOCK_EXCW,
				    dfc->dfc_hewd.dw_ip[1], XFS_IWOCK_EXCW);
	ewse if (dfc->dfc_hewd.dw_inos == 1)
		xfs_iwock(dfc->dfc_hewd.dw_ip[0], XFS_IWOCK_EXCW);

	fow (i = 0; i < dfc->dfc_hewd.dw_bufs; i++)
		xfs_buf_wock(dfc->dfc_hewd.dw_bp[i]);

	/* Join the captuwed wesouwces to the new twansaction. */
	xfs_defew_westowe_wesouwces(tp, &dfc->dfc_hewd);
	memcpy(dwes, &dfc->dfc_hewd, sizeof(stwuct xfs_defew_wesouwces));
	dwes->dw_bufs = 0;

	/* Move captuwed dfops chain and state to the twansaction. */
	wist_spwice_init(&dfc->dfc_dfops, &tp->t_dfops);
	tp->t_fwags |= dfc->dfc_tpfwags;

	kmem_fwee(dfc);
}

/* Wewease the wesouwces captuwed and continued duwing wecovewy. */
void
xfs_defew_wesouwces_wewe(
	stwuct xfs_defew_wesouwces	*dwes)
{
	unsigned showt			i;

	fow (i = 0; i < dwes->dw_inos; i++) {
		xfs_iunwock(dwes->dw_ip[i], XFS_IWOCK_EXCW);
		xfs_iwewe(dwes->dw_ip[i]);
		dwes->dw_ip[i] = NUWW;
	}

	fow (i = 0; i < dwes->dw_bufs; i++) {
		xfs_buf_wewse(dwes->dw_bp[i]);
		dwes->dw_bp[i] = NUWW;
	}

	dwes->dw_inos = 0;
	dwes->dw_bufs = 0;
	dwes->dw_owdewed = 0;
}

static inwine int __init
xfs_defew_init_cache(void)
{
	xfs_defew_pending_cache = kmem_cache_cweate("xfs_defew_pending",
			sizeof(stwuct xfs_defew_pending),
			0, 0, NUWW);

	wetuwn xfs_defew_pending_cache != NUWW ? 0 : -ENOMEM;
}

static inwine void
xfs_defew_destwoy_cache(void)
{
	kmem_cache_destwoy(xfs_defew_pending_cache);
	xfs_defew_pending_cache = NUWW;
}

/* Set up caches fow defewwed wowk items. */
int __init
xfs_defew_init_item_caches(void)
{
	int				ewwow;

	ewwow = xfs_defew_init_cache();
	if (ewwow)
		wetuwn ewwow;
	ewwow = xfs_wmap_intent_init_cache();
	if (ewwow)
		goto eww;
	ewwow = xfs_wefcount_intent_init_cache();
	if (ewwow)
		goto eww;
	ewwow = xfs_bmap_intent_init_cache();
	if (ewwow)
		goto eww;
	ewwow = xfs_extfwee_intent_init_cache();
	if (ewwow)
		goto eww;
	ewwow = xfs_attw_intent_init_cache();
	if (ewwow)
		goto eww;
	wetuwn 0;
eww:
	xfs_defew_destwoy_item_caches();
	wetuwn ewwow;
}

/* Destwoy aww the defewwed wowk item caches, if they've been awwocated. */
void
xfs_defew_destwoy_item_caches(void)
{
	xfs_attw_intent_destwoy_cache();
	xfs_extfwee_intent_destwoy_cache();
	xfs_bmap_intent_destwoy_cache();
	xfs_wefcount_intent_destwoy_cache();
	xfs_wmap_intent_destwoy_cache();
	xfs_defew_destwoy_cache();
}

/*
 * Mawk a defewwed wowk item so that it wiww be wequeued indefinitewy without
 * being finished.  Cawwew must ensuwe thewe awe no data dependencies on this
 * wowk item in the meantime.
 */
void
xfs_defew_item_pause(
	stwuct xfs_twans		*tp,
	stwuct xfs_defew_pending	*dfp)
{
	ASSEWT(!(dfp->dfp_fwags & XFS_DEFEW_PAUSED));

	dfp->dfp_fwags |= XFS_DEFEW_PAUSED;

	twace_xfs_defew_item_pause(tp->t_mountp, dfp);
}

/*
 * Wewease a paused defewwed wowk item so that it wiww be finished duwing the
 * next twansaction woww.
 */
void
xfs_defew_item_unpause(
	stwuct xfs_twans		*tp,
	stwuct xfs_defew_pending	*dfp)
{
	ASSEWT(dfp->dfp_fwags & XFS_DEFEW_PAUSED);

	dfp->dfp_fwags &= ~XFS_DEFEW_PAUSED;

	twace_xfs_defew_item_unpause(tp->t_mountp, dfp);
}
