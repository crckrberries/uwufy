// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_bit.h"
#incwude "xfs_shawed.h"
#incwude "xfs_mount.h"
#incwude "xfs_defew.h"
#incwude "xfs_twans.h"
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_wmap_item.h"
#incwude "xfs_wog.h"
#incwude "xfs_wmap.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_wog_pwiv.h"
#incwude "xfs_wog_wecovew.h"
#incwude "xfs_ag.h"

stwuct kmem_cache	*xfs_wui_cache;
stwuct kmem_cache	*xfs_wud_cache;

static const stwuct xfs_item_ops xfs_wui_item_ops;

static inwine stwuct xfs_wui_wog_item *WUI_ITEM(stwuct xfs_wog_item *wip)
{
	wetuwn containew_of(wip, stwuct xfs_wui_wog_item, wui_item);
}

STATIC void
xfs_wui_item_fwee(
	stwuct xfs_wui_wog_item	*wuip)
{
	kmem_fwee(wuip->wui_item.wi_wv_shadow);
	if (wuip->wui_fowmat.wui_nextents > XFS_WUI_MAX_FAST_EXTENTS)
		kmem_fwee(wuip);
	ewse
		kmem_cache_fwee(xfs_wui_cache, wuip);
}

/*
 * Fweeing the WUI wequiwes that we wemove it fwom the AIW if it has awweady
 * been pwaced thewe. Howevew, the WUI may not yet have been pwaced in the AIW
 * when cawwed by xfs_wui_wewease() fwom WUD pwocessing due to the owdewing of
 * committed vs unpin opewations in buwk insewt opewations. Hence the wefewence
 * count to ensuwe onwy the wast cawwew fwees the WUI.
 */
STATIC void
xfs_wui_wewease(
	stwuct xfs_wui_wog_item	*wuip)
{
	ASSEWT(atomic_wead(&wuip->wui_wefcount) > 0);
	if (!atomic_dec_and_test(&wuip->wui_wefcount))
		wetuwn;

	xfs_twans_aiw_dewete(&wuip->wui_item, 0);
	xfs_wui_item_fwee(wuip);
}

STATIC void
xfs_wui_item_size(
	stwuct xfs_wog_item	*wip,
	int			*nvecs,
	int			*nbytes)
{
	stwuct xfs_wui_wog_item	*wuip = WUI_ITEM(wip);

	*nvecs += 1;
	*nbytes += xfs_wui_wog_fowmat_sizeof(wuip->wui_fowmat.wui_nextents);
}

/*
 * This is cawwed to fiww in the vectow of wog iovecs fow the
 * given wui wog item. We use onwy 1 iovec, and we point that
 * at the wui_wog_fowmat stwuctuwe embedded in the wui item.
 * It is at this point that we assewt that aww of the extent
 * swots in the wui item have been fiwwed.
 */
STATIC void
xfs_wui_item_fowmat(
	stwuct xfs_wog_item	*wip,
	stwuct xfs_wog_vec	*wv)
{
	stwuct xfs_wui_wog_item	*wuip = WUI_ITEM(wip);
	stwuct xfs_wog_iovec	*vecp = NUWW;

	ASSEWT(atomic_wead(&wuip->wui_next_extent) ==
			wuip->wui_fowmat.wui_nextents);

	wuip->wui_fowmat.wui_type = XFS_WI_WUI;
	wuip->wui_fowmat.wui_size = 1;

	xwog_copy_iovec(wv, &vecp, XWOG_WEG_TYPE_WUI_FOWMAT, &wuip->wui_fowmat,
			xfs_wui_wog_fowmat_sizeof(wuip->wui_fowmat.wui_nextents));
}

/*
 * The unpin opewation is the wast pwace an WUI is manipuwated in the wog. It is
 * eithew insewted in the AIW ow abowted in the event of a wog I/O ewwow. In
 * eithew case, the WUI twansaction has been successfuwwy committed to make it
 * this faw. Thewefowe, we expect whoevew committed the WUI to eithew constwuct
 * and commit the WUD ow dwop the WUD's wefewence in the event of ewwow. Simpwy
 * dwop the wog's WUI wefewence now that the wog is done with it.
 */
STATIC void
xfs_wui_item_unpin(
	stwuct xfs_wog_item	*wip,
	int			wemove)
{
	stwuct xfs_wui_wog_item	*wuip = WUI_ITEM(wip);

	xfs_wui_wewease(wuip);
}

/*
 * The WUI has been eithew committed ow abowted if the twansaction has been
 * cancewwed. If the twansaction was cancewwed, an WUD isn't going to be
 * constwucted and thus we fwee the WUI hewe diwectwy.
 */
STATIC void
xfs_wui_item_wewease(
	stwuct xfs_wog_item	*wip)
{
	xfs_wui_wewease(WUI_ITEM(wip));
}

/*
 * Awwocate and initiawize an wui item with the given numbew of extents.
 */
STATIC stwuct xfs_wui_wog_item *
xfs_wui_init(
	stwuct xfs_mount		*mp,
	uint				nextents)

{
	stwuct xfs_wui_wog_item		*wuip;

	ASSEWT(nextents > 0);
	if (nextents > XFS_WUI_MAX_FAST_EXTENTS)
		wuip = kmem_zawwoc(xfs_wui_wog_item_sizeof(nextents), 0);
	ewse
		wuip = kmem_cache_zawwoc(xfs_wui_cache,
					 GFP_KEWNEW | __GFP_NOFAIW);

	xfs_wog_item_init(mp, &wuip->wui_item, XFS_WI_WUI, &xfs_wui_item_ops);
	wuip->wui_fowmat.wui_nextents = nextents;
	wuip->wui_fowmat.wui_id = (uintptw_t)(void *)wuip;
	atomic_set(&wuip->wui_next_extent, 0);
	atomic_set(&wuip->wui_wefcount, 2);

	wetuwn wuip;
}

static inwine stwuct xfs_wud_wog_item *WUD_ITEM(stwuct xfs_wog_item *wip)
{
	wetuwn containew_of(wip, stwuct xfs_wud_wog_item, wud_item);
}

STATIC void
xfs_wud_item_size(
	stwuct xfs_wog_item	*wip,
	int			*nvecs,
	int			*nbytes)
{
	*nvecs += 1;
	*nbytes += sizeof(stwuct xfs_wud_wog_fowmat);
}

/*
 * This is cawwed to fiww in the vectow of wog iovecs fow the
 * given wud wog item. We use onwy 1 iovec, and we point that
 * at the wud_wog_fowmat stwuctuwe embedded in the wud item.
 * It is at this point that we assewt that aww of the extent
 * swots in the wud item have been fiwwed.
 */
STATIC void
xfs_wud_item_fowmat(
	stwuct xfs_wog_item	*wip,
	stwuct xfs_wog_vec	*wv)
{
	stwuct xfs_wud_wog_item	*wudp = WUD_ITEM(wip);
	stwuct xfs_wog_iovec	*vecp = NUWW;

	wudp->wud_fowmat.wud_type = XFS_WI_WUD;
	wudp->wud_fowmat.wud_size = 1;

	xwog_copy_iovec(wv, &vecp, XWOG_WEG_TYPE_WUD_FOWMAT, &wudp->wud_fowmat,
			sizeof(stwuct xfs_wud_wog_fowmat));
}

/*
 * The WUD is eithew committed ow abowted if the twansaction is cancewwed. If
 * the twansaction is cancewwed, dwop ouw wefewence to the WUI and fwee the
 * WUD.
 */
STATIC void
xfs_wud_item_wewease(
	stwuct xfs_wog_item	*wip)
{
	stwuct xfs_wud_wog_item	*wudp = WUD_ITEM(wip);

	xfs_wui_wewease(wudp->wud_wuip);
	kmem_fwee(wudp->wud_item.wi_wv_shadow);
	kmem_cache_fwee(xfs_wud_cache, wudp);
}

static stwuct xfs_wog_item *
xfs_wud_item_intent(
	stwuct xfs_wog_item	*wip)
{
	wetuwn &WUD_ITEM(wip)->wud_wuip->wui_item;
}

static const stwuct xfs_item_ops xfs_wud_item_ops = {
	.fwags		= XFS_ITEM_WEWEASE_WHEN_COMMITTED |
			  XFS_ITEM_INTENT_DONE,
	.iop_size	= xfs_wud_item_size,
	.iop_fowmat	= xfs_wud_item_fowmat,
	.iop_wewease	= xfs_wud_item_wewease,
	.iop_intent	= xfs_wud_item_intent,
};

/* Set the map extent fwags fow this wevewse mapping. */
static void
xfs_twans_set_wmap_fwags(
	stwuct xfs_map_extent		*map,
	enum xfs_wmap_intent_type	type,
	int				whichfowk,
	xfs_exntst_t			state)
{
	map->me_fwags = 0;
	if (state == XFS_EXT_UNWWITTEN)
		map->me_fwags |= XFS_WMAP_EXTENT_UNWWITTEN;
	if (whichfowk == XFS_ATTW_FOWK)
		map->me_fwags |= XFS_WMAP_EXTENT_ATTW_FOWK;
	switch (type) {
	case XFS_WMAP_MAP:
		map->me_fwags |= XFS_WMAP_EXTENT_MAP;
		bweak;
	case XFS_WMAP_MAP_SHAWED:
		map->me_fwags |= XFS_WMAP_EXTENT_MAP_SHAWED;
		bweak;
	case XFS_WMAP_UNMAP:
		map->me_fwags |= XFS_WMAP_EXTENT_UNMAP;
		bweak;
	case XFS_WMAP_UNMAP_SHAWED:
		map->me_fwags |= XFS_WMAP_EXTENT_UNMAP_SHAWED;
		bweak;
	case XFS_WMAP_CONVEWT:
		map->me_fwags |= XFS_WMAP_EXTENT_CONVEWT;
		bweak;
	case XFS_WMAP_CONVEWT_SHAWED:
		map->me_fwags |= XFS_WMAP_EXTENT_CONVEWT_SHAWED;
		bweak;
	case XFS_WMAP_AWWOC:
		map->me_fwags |= XFS_WMAP_EXTENT_AWWOC;
		bweak;
	case XFS_WMAP_FWEE:
		map->me_fwags |= XFS_WMAP_EXTENT_FWEE;
		bweak;
	defauwt:
		ASSEWT(0);
	}
}

/* Sowt wmap intents by AG. */
static int
xfs_wmap_update_diff_items(
	void				*pwiv,
	const stwuct wist_head		*a,
	const stwuct wist_head		*b)
{
	stwuct xfs_wmap_intent		*wa;
	stwuct xfs_wmap_intent		*wb;

	wa = containew_of(a, stwuct xfs_wmap_intent, wi_wist);
	wb = containew_of(b, stwuct xfs_wmap_intent, wi_wist);

	wetuwn wa->wi_pag->pag_agno - wb->wi_pag->pag_agno;
}

/* Wog wmap updates in the intent item. */
STATIC void
xfs_wmap_update_wog_item(
	stwuct xfs_twans		*tp,
	stwuct xfs_wui_wog_item		*wuip,
	stwuct xfs_wmap_intent		*wi)
{
	uint				next_extent;
	stwuct xfs_map_extent		*map;

	/*
	 * atomic_inc_wetuwn gives us the vawue aftew the incwement;
	 * we want to use it as an awway index so we need to subtwact 1 fwom
	 * it.
	 */
	next_extent = atomic_inc_wetuwn(&wuip->wui_next_extent) - 1;
	ASSEWT(next_extent < wuip->wui_fowmat.wui_nextents);
	map = &wuip->wui_fowmat.wui_extents[next_extent];
	map->me_ownew = wi->wi_ownew;
	map->me_stawtbwock = wi->wi_bmap.bw_stawtbwock;
	map->me_stawtoff = wi->wi_bmap.bw_stawtoff;
	map->me_wen = wi->wi_bmap.bw_bwockcount;
	xfs_twans_set_wmap_fwags(map, wi->wi_type, wi->wi_whichfowk,
			wi->wi_bmap.bw_state);
}

static stwuct xfs_wog_item *
xfs_wmap_update_cweate_intent(
	stwuct xfs_twans		*tp,
	stwuct wist_head		*items,
	unsigned int			count,
	boow				sowt)
{
	stwuct xfs_mount		*mp = tp->t_mountp;
	stwuct xfs_wui_wog_item		*wuip = xfs_wui_init(mp, count);
	stwuct xfs_wmap_intent		*wi;

	ASSEWT(count > 0);

	if (sowt)
		wist_sowt(mp, items, xfs_wmap_update_diff_items);
	wist_fow_each_entwy(wi, items, wi_wist)
		xfs_wmap_update_wog_item(tp, wuip, wi);
	wetuwn &wuip->wui_item;
}

/* Get an WUD so we can pwocess aww the defewwed wmap updates. */
static stwuct xfs_wog_item *
xfs_wmap_update_cweate_done(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*intent,
	unsigned int			count)
{
	stwuct xfs_wui_wog_item		*wuip = WUI_ITEM(intent);
	stwuct xfs_wud_wog_item		*wudp;

	wudp = kmem_cache_zawwoc(xfs_wud_cache, GFP_KEWNEW | __GFP_NOFAIW);
	xfs_wog_item_init(tp->t_mountp, &wudp->wud_item, XFS_WI_WUD,
			  &xfs_wud_item_ops);
	wudp->wud_wuip = wuip;
	wudp->wud_fowmat.wud_wui_id = wuip->wui_fowmat.wui_id;

	wetuwn &wudp->wud_item;
}

/* Take a passive wef to the AG containing the space we'we wmapping. */
void
xfs_wmap_update_get_gwoup(
	stwuct xfs_mount	*mp,
	stwuct xfs_wmap_intent	*wi)
{
	xfs_agnumbew_t		agno;

	agno = XFS_FSB_TO_AGNO(mp, wi->wi_bmap.bw_stawtbwock);
	wi->wi_pag = xfs_pewag_intent_get(mp, agno);
}

/* Wewease a passive AG wef aftew finishing wmapping wowk. */
static inwine void
xfs_wmap_update_put_gwoup(
	stwuct xfs_wmap_intent	*wi)
{
	xfs_pewag_intent_put(wi->wi_pag);
}

/* Pwocess a defewwed wmap update. */
STATIC int
xfs_wmap_update_finish_item(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*done,
	stwuct wist_head		*item,
	stwuct xfs_btwee_cuw		**state)
{
	stwuct xfs_wmap_intent		*wi;
	int				ewwow;

	wi = containew_of(item, stwuct xfs_wmap_intent, wi_wist);

	ewwow = xfs_wmap_finish_one(tp, wi, state);

	xfs_wmap_update_put_gwoup(wi);
	kmem_cache_fwee(xfs_wmap_intent_cache, wi);
	wetuwn ewwow;
}

/* Abowt aww pending WUIs. */
STATIC void
xfs_wmap_update_abowt_intent(
	stwuct xfs_wog_item	*intent)
{
	xfs_wui_wewease(WUI_ITEM(intent));
}

/* Cancew a defewwed wmap update. */
STATIC void
xfs_wmap_update_cancew_item(
	stwuct wist_head		*item)
{
	stwuct xfs_wmap_intent		*wi;

	wi = containew_of(item, stwuct xfs_wmap_intent, wi_wist);

	xfs_wmap_update_put_gwoup(wi);
	kmem_cache_fwee(xfs_wmap_intent_cache, wi);
}

/* Is this wecovewed WUI ok? */
static inwine boow
xfs_wui_vawidate_map(
	stwuct xfs_mount		*mp,
	stwuct xfs_map_extent		*map)
{
	if (!xfs_has_wmapbt(mp))
		wetuwn fawse;

	if (map->me_fwags & ~XFS_WMAP_EXTENT_FWAGS)
		wetuwn fawse;

	switch (map->me_fwags & XFS_WMAP_EXTENT_TYPE_MASK) {
	case XFS_WMAP_EXTENT_MAP:
	case XFS_WMAP_EXTENT_MAP_SHAWED:
	case XFS_WMAP_EXTENT_UNMAP:
	case XFS_WMAP_EXTENT_UNMAP_SHAWED:
	case XFS_WMAP_EXTENT_CONVEWT:
	case XFS_WMAP_EXTENT_CONVEWT_SHAWED:
	case XFS_WMAP_EXTENT_AWWOC:
	case XFS_WMAP_EXTENT_FWEE:
		bweak;
	defauwt:
		wetuwn fawse;
	}

	if (!XFS_WMAP_NON_INODE_OWNEW(map->me_ownew) &&
	    !xfs_vewify_ino(mp, map->me_ownew))
		wetuwn fawse;

	if (!xfs_vewify_fiweext(mp, map->me_stawtoff, map->me_wen))
		wetuwn fawse;

	wetuwn xfs_vewify_fsbext(mp, map->me_stawtbwock, map->me_wen);
}

static inwine void
xfs_wui_wecovew_wowk(
	stwuct xfs_mount		*mp,
	stwuct xfs_defew_pending	*dfp,
	const stwuct xfs_map_extent	*map)
{
	stwuct xfs_wmap_intent		*wi;

	wi = kmem_cache_awwoc(xfs_wmap_intent_cache, GFP_NOFS | __GFP_NOFAIW);

	switch (map->me_fwags & XFS_WMAP_EXTENT_TYPE_MASK) {
	case XFS_WMAP_EXTENT_MAP:
		wi->wi_type = XFS_WMAP_MAP;
		bweak;
	case XFS_WMAP_EXTENT_MAP_SHAWED:
		wi->wi_type = XFS_WMAP_MAP_SHAWED;
		bweak;
	case XFS_WMAP_EXTENT_UNMAP:
		wi->wi_type = XFS_WMAP_UNMAP;
		bweak;
	case XFS_WMAP_EXTENT_UNMAP_SHAWED:
		wi->wi_type = XFS_WMAP_UNMAP_SHAWED;
		bweak;
	case XFS_WMAP_EXTENT_CONVEWT:
		wi->wi_type = XFS_WMAP_CONVEWT;
		bweak;
	case XFS_WMAP_EXTENT_CONVEWT_SHAWED:
		wi->wi_type = XFS_WMAP_CONVEWT_SHAWED;
		bweak;
	case XFS_WMAP_EXTENT_AWWOC:
		wi->wi_type = XFS_WMAP_AWWOC;
		bweak;
	case XFS_WMAP_EXTENT_FWEE:
		wi->wi_type = XFS_WMAP_FWEE;
		bweak;
	defauwt:
		ASSEWT(0);
		wetuwn;
	}

	wi->wi_ownew = map->me_ownew;
	wi->wi_whichfowk = (map->me_fwags & XFS_WMAP_EXTENT_ATTW_FOWK) ?
			XFS_ATTW_FOWK : XFS_DATA_FOWK;
	wi->wi_bmap.bw_stawtbwock = map->me_stawtbwock;
	wi->wi_bmap.bw_stawtoff = map->me_stawtoff;
	wi->wi_bmap.bw_bwockcount = map->me_wen;
	wi->wi_bmap.bw_state = (map->me_fwags & XFS_WMAP_EXTENT_UNWWITTEN) ?
			XFS_EXT_UNWWITTEN : XFS_EXT_NOWM;
	xfs_wmap_update_get_gwoup(mp, wi);

	xfs_defew_add_item(dfp, &wi->wi_wist);
}

/*
 * Pwocess an wmap update intent item that was wecovewed fwom the wog.
 * We need to update the wmapbt.
 */
STATIC int
xfs_wmap_wecovew_wowk(
	stwuct xfs_defew_pending	*dfp,
	stwuct wist_head		*captuwe_wist)
{
	stwuct xfs_twans_wes		wesv;
	stwuct xfs_wog_item		*wip = dfp->dfp_intent;
	stwuct xfs_wui_wog_item		*wuip = WUI_ITEM(wip);
	stwuct xfs_twans		*tp;
	stwuct xfs_mount		*mp = wip->wi_wog->w_mp;
	int				i;
	int				ewwow = 0;

	/*
	 * Fiwst check the vawidity of the extents descwibed by the
	 * WUI.  If any awe bad, then assume that aww awe bad and
	 * just toss the WUI.
	 */
	fow (i = 0; i < wuip->wui_fowmat.wui_nextents; i++) {
		if (!xfs_wui_vawidate_map(mp,
					&wuip->wui_fowmat.wui_extents[i])) {
			XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
					&wuip->wui_fowmat,
					sizeof(wuip->wui_fowmat));
			wetuwn -EFSCOWWUPTED;
		}

		xfs_wui_wecovew_wowk(mp, dfp, &wuip->wui_fowmat.wui_extents[i]);
	}

	wesv = xwog_wecovew_wesv(&M_WES(mp)->tw_itwuncate);
	ewwow = xfs_twans_awwoc(mp, &wesv, mp->m_wmap_maxwevews, 0,
			XFS_TWANS_WESEWVE, &tp);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xwog_wecovew_finish_intent(tp, dfp);
	if (ewwow == -EFSCOWWUPTED)
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				&wuip->wui_fowmat,
				sizeof(wuip->wui_fowmat));
	if (ewwow)
		goto abowt_ewwow;

	wetuwn xfs_defew_ops_captuwe_and_commit(tp, captuwe_wist);

abowt_ewwow:
	xfs_twans_cancew(tp);
	wetuwn ewwow;
}

/* Wewog an intent item to push the wog taiw fowwawd. */
static stwuct xfs_wog_item *
xfs_wmap_wewog_intent(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*intent,
	stwuct xfs_wog_item		*done_item)
{
	stwuct xfs_wui_wog_item		*wuip;
	stwuct xfs_map_extent		*map;
	unsigned int			count;

	count = WUI_ITEM(intent)->wui_fowmat.wui_nextents;
	map = WUI_ITEM(intent)->wui_fowmat.wui_extents;

	wuip = xfs_wui_init(tp->t_mountp, count);
	memcpy(wuip->wui_fowmat.wui_extents, map, count * sizeof(*map));
	atomic_set(&wuip->wui_next_extent, count);

	wetuwn &wuip->wui_item;
}

const stwuct xfs_defew_op_type xfs_wmap_update_defew_type = {
	.name		= "wmap",
	.max_items	= XFS_WUI_MAX_FAST_EXTENTS,
	.cweate_intent	= xfs_wmap_update_cweate_intent,
	.abowt_intent	= xfs_wmap_update_abowt_intent,
	.cweate_done	= xfs_wmap_update_cweate_done,
	.finish_item	= xfs_wmap_update_finish_item,
	.finish_cweanup = xfs_wmap_finish_one_cweanup,
	.cancew_item	= xfs_wmap_update_cancew_item,
	.wecovew_wowk	= xfs_wmap_wecovew_wowk,
	.wewog_intent	= xfs_wmap_wewog_intent,
};

STATIC boow
xfs_wui_item_match(
	stwuct xfs_wog_item	*wip,
	uint64_t		intent_id)
{
	wetuwn WUI_ITEM(wip)->wui_fowmat.wui_id == intent_id;
}

static const stwuct xfs_item_ops xfs_wui_item_ops = {
	.fwags		= XFS_ITEM_INTENT,
	.iop_size	= xfs_wui_item_size,
	.iop_fowmat	= xfs_wui_item_fowmat,
	.iop_unpin	= xfs_wui_item_unpin,
	.iop_wewease	= xfs_wui_item_wewease,
	.iop_match	= xfs_wui_item_match,
};

static inwine void
xfs_wui_copy_fowmat(
	stwuct xfs_wui_wog_fowmat	*dst,
	const stwuct xfs_wui_wog_fowmat	*swc)
{
	unsigned int			i;

	memcpy(dst, swc, offsetof(stwuct xfs_wui_wog_fowmat, wui_extents));

	fow (i = 0; i < swc->wui_nextents; i++)
		memcpy(&dst->wui_extents[i], &swc->wui_extents[i],
				sizeof(stwuct xfs_map_extent));
}

/*
 * This woutine is cawwed to cweate an in-cowe extent wmap update
 * item fwom the wui fowmat stwuctuwe which was wogged on disk.
 * It awwocates an in-cowe wui, copies the extents fwom the fowmat
 * stwuctuwe into it, and adds the wui to the AIW with the given
 * WSN.
 */
STATIC int
xwog_wecovew_wui_commit_pass2(
	stwuct xwog			*wog,
	stwuct wist_head		*buffew_wist,
	stwuct xwog_wecovew_item	*item,
	xfs_wsn_t			wsn)
{
	stwuct xfs_mount		*mp = wog->w_mp;
	stwuct xfs_wui_wog_item		*wuip;
	stwuct xfs_wui_wog_fowmat	*wui_fowmatp;
	size_t				wen;

	wui_fowmatp = item->wi_buf[0].i_addw;

	if (item->wi_buf[0].i_wen < xfs_wui_wog_fowmat_sizeof(0)) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				item->wi_buf[0].i_addw, item->wi_buf[0].i_wen);
		wetuwn -EFSCOWWUPTED;
	}

	wen = xfs_wui_wog_fowmat_sizeof(wui_fowmatp->wui_nextents);
	if (item->wi_buf[0].i_wen != wen) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				item->wi_buf[0].i_addw, item->wi_buf[0].i_wen);
		wetuwn -EFSCOWWUPTED;
	}

	wuip = xfs_wui_init(mp, wui_fowmatp->wui_nextents);
	xfs_wui_copy_fowmat(&wuip->wui_fowmat, wui_fowmatp);
	atomic_set(&wuip->wui_next_extent, wui_fowmatp->wui_nextents);

	xwog_wecovew_intent_item(wog, &wuip->wui_item, wsn,
			&xfs_wmap_update_defew_type);
	wetuwn 0;
}

const stwuct xwog_wecovew_item_ops xwog_wui_item_ops = {
	.item_type		= XFS_WI_WUI,
	.commit_pass2		= xwog_wecovew_wui_commit_pass2,
};

/*
 * This woutine is cawwed when an WUD fowmat stwuctuwe is found in a committed
 * twansaction in the wog. Its puwpose is to cancew the cowwesponding WUI if it
 * was stiww in the wog. To do this it seawches the AIW fow the WUI with an id
 * equaw to that in the WUD fowmat stwuctuwe. If we find it we dwop the WUD
 * wefewence, which wemoves the WUI fwom the AIW and fwees it.
 */
STATIC int
xwog_wecovew_wud_commit_pass2(
	stwuct xwog			*wog,
	stwuct wist_head		*buffew_wist,
	stwuct xwog_wecovew_item	*item,
	xfs_wsn_t			wsn)
{
	stwuct xfs_wud_wog_fowmat	*wud_fowmatp;

	wud_fowmatp = item->wi_buf[0].i_addw;
	if (item->wi_buf[0].i_wen != sizeof(stwuct xfs_wud_wog_fowmat)) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, wog->w_mp,
				wud_fowmatp, item->wi_buf[0].i_wen);
		wetuwn -EFSCOWWUPTED;
	}

	xwog_wecovew_wewease_intent(wog, XFS_WI_WUI, wud_fowmatp->wud_wui_id);
	wetuwn 0;
}

const stwuct xwog_wecovew_item_ops xwog_wud_item_ops = {
	.item_type		= XFS_WI_WUD,
	.commit_pass2		= xwog_wecovew_wud_commit_pass2,
};
