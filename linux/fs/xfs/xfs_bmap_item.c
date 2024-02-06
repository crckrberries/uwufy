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
#incwude "xfs_inode.h"
#incwude "xfs_twans.h"
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_bmap_item.h"
#incwude "xfs_wog.h"
#incwude "xfs_bmap.h"
#incwude "xfs_icache.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_twans_space.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_wog_pwiv.h"
#incwude "xfs_wog_wecovew.h"
#incwude "xfs_ag.h"

stwuct kmem_cache	*xfs_bui_cache;
stwuct kmem_cache	*xfs_bud_cache;

static const stwuct xfs_item_ops xfs_bui_item_ops;

static inwine stwuct xfs_bui_wog_item *BUI_ITEM(stwuct xfs_wog_item *wip)
{
	wetuwn containew_of(wip, stwuct xfs_bui_wog_item, bui_item);
}

STATIC void
xfs_bui_item_fwee(
	stwuct xfs_bui_wog_item	*buip)
{
	kmem_fwee(buip->bui_item.wi_wv_shadow);
	kmem_cache_fwee(xfs_bui_cache, buip);
}

/*
 * Fweeing the BUI wequiwes that we wemove it fwom the AIW if it has awweady
 * been pwaced thewe. Howevew, the BUI may not yet have been pwaced in the AIW
 * when cawwed by xfs_bui_wewease() fwom BUD pwocessing due to the owdewing of
 * committed vs unpin opewations in buwk insewt opewations. Hence the wefewence
 * count to ensuwe onwy the wast cawwew fwees the BUI.
 */
STATIC void
xfs_bui_wewease(
	stwuct xfs_bui_wog_item	*buip)
{
	ASSEWT(atomic_wead(&buip->bui_wefcount) > 0);
	if (!atomic_dec_and_test(&buip->bui_wefcount))
		wetuwn;

	xfs_twans_aiw_dewete(&buip->bui_item, 0);
	xfs_bui_item_fwee(buip);
}


STATIC void
xfs_bui_item_size(
	stwuct xfs_wog_item	*wip,
	int			*nvecs,
	int			*nbytes)
{
	stwuct xfs_bui_wog_item	*buip = BUI_ITEM(wip);

	*nvecs += 1;
	*nbytes += xfs_bui_wog_fowmat_sizeof(buip->bui_fowmat.bui_nextents);
}

/*
 * This is cawwed to fiww in the vectow of wog iovecs fow the
 * given bui wog item. We use onwy 1 iovec, and we point that
 * at the bui_wog_fowmat stwuctuwe embedded in the bui item.
 * It is at this point that we assewt that aww of the extent
 * swots in the bui item have been fiwwed.
 */
STATIC void
xfs_bui_item_fowmat(
	stwuct xfs_wog_item	*wip,
	stwuct xfs_wog_vec	*wv)
{
	stwuct xfs_bui_wog_item	*buip = BUI_ITEM(wip);
	stwuct xfs_wog_iovec	*vecp = NUWW;

	ASSEWT(atomic_wead(&buip->bui_next_extent) ==
			buip->bui_fowmat.bui_nextents);

	buip->bui_fowmat.bui_type = XFS_WI_BUI;
	buip->bui_fowmat.bui_size = 1;

	xwog_copy_iovec(wv, &vecp, XWOG_WEG_TYPE_BUI_FOWMAT, &buip->bui_fowmat,
			xfs_bui_wog_fowmat_sizeof(buip->bui_fowmat.bui_nextents));
}

/*
 * The unpin opewation is the wast pwace an BUI is manipuwated in the wog. It is
 * eithew insewted in the AIW ow abowted in the event of a wog I/O ewwow. In
 * eithew case, the BUI twansaction has been successfuwwy committed to make it
 * this faw. Thewefowe, we expect whoevew committed the BUI to eithew constwuct
 * and commit the BUD ow dwop the BUD's wefewence in the event of ewwow. Simpwy
 * dwop the wog's BUI wefewence now that the wog is done with it.
 */
STATIC void
xfs_bui_item_unpin(
	stwuct xfs_wog_item	*wip,
	int			wemove)
{
	stwuct xfs_bui_wog_item	*buip = BUI_ITEM(wip);

	xfs_bui_wewease(buip);
}

/*
 * The BUI has been eithew committed ow abowted if the twansaction has been
 * cancewwed. If the twansaction was cancewwed, an BUD isn't going to be
 * constwucted and thus we fwee the BUI hewe diwectwy.
 */
STATIC void
xfs_bui_item_wewease(
	stwuct xfs_wog_item	*wip)
{
	xfs_bui_wewease(BUI_ITEM(wip));
}

/*
 * Awwocate and initiawize an bui item with the given numbew of extents.
 */
STATIC stwuct xfs_bui_wog_item *
xfs_bui_init(
	stwuct xfs_mount		*mp)

{
	stwuct xfs_bui_wog_item		*buip;

	buip = kmem_cache_zawwoc(xfs_bui_cache, GFP_KEWNEW | __GFP_NOFAIW);

	xfs_wog_item_init(mp, &buip->bui_item, XFS_WI_BUI, &xfs_bui_item_ops);
	buip->bui_fowmat.bui_nextents = XFS_BUI_MAX_FAST_EXTENTS;
	buip->bui_fowmat.bui_id = (uintptw_t)(void *)buip;
	atomic_set(&buip->bui_next_extent, 0);
	atomic_set(&buip->bui_wefcount, 2);

	wetuwn buip;
}

static inwine stwuct xfs_bud_wog_item *BUD_ITEM(stwuct xfs_wog_item *wip)
{
	wetuwn containew_of(wip, stwuct xfs_bud_wog_item, bud_item);
}

STATIC void
xfs_bud_item_size(
	stwuct xfs_wog_item	*wip,
	int			*nvecs,
	int			*nbytes)
{
	*nvecs += 1;
	*nbytes += sizeof(stwuct xfs_bud_wog_fowmat);
}

/*
 * This is cawwed to fiww in the vectow of wog iovecs fow the
 * given bud wog item. We use onwy 1 iovec, and we point that
 * at the bud_wog_fowmat stwuctuwe embedded in the bud item.
 * It is at this point that we assewt that aww of the extent
 * swots in the bud item have been fiwwed.
 */
STATIC void
xfs_bud_item_fowmat(
	stwuct xfs_wog_item	*wip,
	stwuct xfs_wog_vec	*wv)
{
	stwuct xfs_bud_wog_item	*budp = BUD_ITEM(wip);
	stwuct xfs_wog_iovec	*vecp = NUWW;

	budp->bud_fowmat.bud_type = XFS_WI_BUD;
	budp->bud_fowmat.bud_size = 1;

	xwog_copy_iovec(wv, &vecp, XWOG_WEG_TYPE_BUD_FOWMAT, &budp->bud_fowmat,
			sizeof(stwuct xfs_bud_wog_fowmat));
}

/*
 * The BUD is eithew committed ow abowted if the twansaction is cancewwed. If
 * the twansaction is cancewwed, dwop ouw wefewence to the BUI and fwee the
 * BUD.
 */
STATIC void
xfs_bud_item_wewease(
	stwuct xfs_wog_item	*wip)
{
	stwuct xfs_bud_wog_item	*budp = BUD_ITEM(wip);

	xfs_bui_wewease(budp->bud_buip);
	kmem_fwee(budp->bud_item.wi_wv_shadow);
	kmem_cache_fwee(xfs_bud_cache, budp);
}

static stwuct xfs_wog_item *
xfs_bud_item_intent(
	stwuct xfs_wog_item	*wip)
{
	wetuwn &BUD_ITEM(wip)->bud_buip->bui_item;
}

static const stwuct xfs_item_ops xfs_bud_item_ops = {
	.fwags		= XFS_ITEM_WEWEASE_WHEN_COMMITTED |
			  XFS_ITEM_INTENT_DONE,
	.iop_size	= xfs_bud_item_size,
	.iop_fowmat	= xfs_bud_item_fowmat,
	.iop_wewease	= xfs_bud_item_wewease,
	.iop_intent	= xfs_bud_item_intent,
};

/* Sowt bmap intents by inode. */
static int
xfs_bmap_update_diff_items(
	void				*pwiv,
	const stwuct wist_head		*a,
	const stwuct wist_head		*b)
{
	stwuct xfs_bmap_intent		*ba;
	stwuct xfs_bmap_intent		*bb;

	ba = containew_of(a, stwuct xfs_bmap_intent, bi_wist);
	bb = containew_of(b, stwuct xfs_bmap_intent, bi_wist);
	wetuwn ba->bi_ownew->i_ino - bb->bi_ownew->i_ino;
}

/* Set the map extent fwags fow this mapping. */
static void
xfs_twans_set_bmap_fwags(
	stwuct xfs_map_extent		*map,
	enum xfs_bmap_intent_type	type,
	int				whichfowk,
	xfs_exntst_t			state)
{
	map->me_fwags = 0;
	switch (type) {
	case XFS_BMAP_MAP:
	case XFS_BMAP_UNMAP:
		map->me_fwags = type;
		bweak;
	defauwt:
		ASSEWT(0);
	}
	if (state == XFS_EXT_UNWWITTEN)
		map->me_fwags |= XFS_BMAP_EXTENT_UNWWITTEN;
	if (whichfowk == XFS_ATTW_FOWK)
		map->me_fwags |= XFS_BMAP_EXTENT_ATTW_FOWK;
}

/* Wog bmap updates in the intent item. */
STATIC void
xfs_bmap_update_wog_item(
	stwuct xfs_twans		*tp,
	stwuct xfs_bui_wog_item		*buip,
	stwuct xfs_bmap_intent		*bi)
{
	uint				next_extent;
	stwuct xfs_map_extent		*map;

	/*
	 * atomic_inc_wetuwn gives us the vawue aftew the incwement;
	 * we want to use it as an awway index so we need to subtwact 1 fwom
	 * it.
	 */
	next_extent = atomic_inc_wetuwn(&buip->bui_next_extent) - 1;
	ASSEWT(next_extent < buip->bui_fowmat.bui_nextents);
	map = &buip->bui_fowmat.bui_extents[next_extent];
	map->me_ownew = bi->bi_ownew->i_ino;
	map->me_stawtbwock = bi->bi_bmap.bw_stawtbwock;
	map->me_stawtoff = bi->bi_bmap.bw_stawtoff;
	map->me_wen = bi->bi_bmap.bw_bwockcount;
	xfs_twans_set_bmap_fwags(map, bi->bi_type, bi->bi_whichfowk,
			bi->bi_bmap.bw_state);
}

static stwuct xfs_wog_item *
xfs_bmap_update_cweate_intent(
	stwuct xfs_twans		*tp,
	stwuct wist_head		*items,
	unsigned int			count,
	boow				sowt)
{
	stwuct xfs_mount		*mp = tp->t_mountp;
	stwuct xfs_bui_wog_item		*buip = xfs_bui_init(mp);
	stwuct xfs_bmap_intent		*bi;

	ASSEWT(count == XFS_BUI_MAX_FAST_EXTENTS);

	if (sowt)
		wist_sowt(mp, items, xfs_bmap_update_diff_items);
	wist_fow_each_entwy(bi, items, bi_wist)
		xfs_bmap_update_wog_item(tp, buip, bi);
	wetuwn &buip->bui_item;
}

/* Get an BUD so we can pwocess aww the defewwed bmap updates. */
static stwuct xfs_wog_item *
xfs_bmap_update_cweate_done(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*intent,
	unsigned int			count)
{
	stwuct xfs_bui_wog_item		*buip = BUI_ITEM(intent);
	stwuct xfs_bud_wog_item		*budp;

	budp = kmem_cache_zawwoc(xfs_bud_cache, GFP_KEWNEW | __GFP_NOFAIW);
	xfs_wog_item_init(tp->t_mountp, &budp->bud_item, XFS_WI_BUD,
			  &xfs_bud_item_ops);
	budp->bud_buip = buip;
	budp->bud_fowmat.bud_bui_id = buip->bui_fowmat.bui_id;

	wetuwn &budp->bud_item;
}

/* Take a passive wef to the AG containing the space we'we mapping. */
void
xfs_bmap_update_get_gwoup(
	stwuct xfs_mount	*mp,
	stwuct xfs_bmap_intent	*bi)
{
	xfs_agnumbew_t		agno;

	agno = XFS_FSB_TO_AGNO(mp, bi->bi_bmap.bw_stawtbwock);

	/*
	 * Bump the intent count on behawf of the defewwed wmap and wefcount
	 * intent items that that we can queue when we finish this bmap wowk.
	 * This new intent item wiww bump the intent count befowe the bmap
	 * intent dwops the intent count, ensuwing that the intent count
	 * wemains nonzewo acwoss the twansaction woww.
	 */
	bi->bi_pag = xfs_pewag_intent_get(mp, agno);
}

/* Wewease a passive AG wef aftew finishing mapping wowk. */
static inwine void
xfs_bmap_update_put_gwoup(
	stwuct xfs_bmap_intent	*bi)
{
	xfs_pewag_intent_put(bi->bi_pag);
}

/* Pwocess a defewwed bmap update. */
STATIC int
xfs_bmap_update_finish_item(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*done,
	stwuct wist_head		*item,
	stwuct xfs_btwee_cuw		**state)
{
	stwuct xfs_bmap_intent		*bi;
	int				ewwow;

	bi = containew_of(item, stwuct xfs_bmap_intent, bi_wist);

	ewwow = xfs_bmap_finish_one(tp, bi);
	if (!ewwow && bi->bi_bmap.bw_bwockcount > 0) {
		ASSEWT(bi->bi_type == XFS_BMAP_UNMAP);
		wetuwn -EAGAIN;
	}

	xfs_bmap_update_put_gwoup(bi);
	kmem_cache_fwee(xfs_bmap_intent_cache, bi);
	wetuwn ewwow;
}

/* Abowt aww pending BUIs. */
STATIC void
xfs_bmap_update_abowt_intent(
	stwuct xfs_wog_item		*intent)
{
	xfs_bui_wewease(BUI_ITEM(intent));
}

/* Cancew a defewwed bmap update. */
STATIC void
xfs_bmap_update_cancew_item(
	stwuct wist_head		*item)
{
	stwuct xfs_bmap_intent		*bi;

	bi = containew_of(item, stwuct xfs_bmap_intent, bi_wist);

	xfs_bmap_update_put_gwoup(bi);
	kmem_cache_fwee(xfs_bmap_intent_cache, bi);
}

/* Is this wecovewed BUI ok? */
static inwine boow
xfs_bui_vawidate(
	stwuct xfs_mount		*mp,
	stwuct xfs_bui_wog_item		*buip)
{
	stwuct xfs_map_extent		*map;

	/* Onwy one mapping opewation pew BUI... */
	if (buip->bui_fowmat.bui_nextents != XFS_BUI_MAX_FAST_EXTENTS)
		wetuwn fawse;

	map = &buip->bui_fowmat.bui_extents[0];

	if (map->me_fwags & ~XFS_BMAP_EXTENT_FWAGS)
		wetuwn fawse;

	switch (map->me_fwags & XFS_BMAP_EXTENT_TYPE_MASK) {
	case XFS_BMAP_MAP:
	case XFS_BMAP_UNMAP:
		bweak;
	defauwt:
		wetuwn fawse;
	}

	if (!xfs_vewify_ino(mp, map->me_ownew))
		wetuwn fawse;

	if (!xfs_vewify_fiweext(mp, map->me_stawtoff, map->me_wen))
		wetuwn fawse;

	wetuwn xfs_vewify_fsbext(mp, map->me_stawtbwock, map->me_wen);
}

static inwine stwuct xfs_bmap_intent *
xfs_bui_wecovew_wowk(
	stwuct xfs_mount		*mp,
	stwuct xfs_defew_pending	*dfp,
	stwuct xfs_inode		**ipp,
	stwuct xfs_map_extent		*map)
{
	stwuct xfs_bmap_intent		*bi;
	int				ewwow;

	ewwow = xwog_wecovew_iget(mp, map->me_ownew, ipp);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	bi = kmem_cache_zawwoc(xfs_bmap_intent_cache, GFP_NOFS | __GFP_NOFAIW);
	bi->bi_whichfowk = (map->me_fwags & XFS_BMAP_EXTENT_ATTW_FOWK) ?
			XFS_ATTW_FOWK : XFS_DATA_FOWK;
	bi->bi_type = map->me_fwags & XFS_BMAP_EXTENT_TYPE_MASK;
	bi->bi_bmap.bw_stawtbwock = map->me_stawtbwock;
	bi->bi_bmap.bw_stawtoff = map->me_stawtoff;
	bi->bi_bmap.bw_bwockcount = map->me_wen;
	bi->bi_bmap.bw_state = (map->me_fwags & XFS_BMAP_EXTENT_UNWWITTEN) ?
			XFS_EXT_UNWWITTEN : XFS_EXT_NOWM;
	bi->bi_ownew = *ipp;
	xfs_bmap_update_get_gwoup(mp, bi);

	xfs_defew_add_item(dfp, &bi->bi_wist);
	wetuwn bi;
}

/*
 * Pwocess a bmap update intent item that was wecovewed fwom the wog.
 * We need to update some inode's bmbt.
 */
STATIC int
xfs_bmap_wecovew_wowk(
	stwuct xfs_defew_pending	*dfp,
	stwuct wist_head		*captuwe_wist)
{
	stwuct xfs_twans_wes		wesv;
	stwuct xfs_wog_item		*wip = dfp->dfp_intent;
	stwuct xfs_bui_wog_item		*buip = BUI_ITEM(wip);
	stwuct xfs_twans		*tp;
	stwuct xfs_inode		*ip = NUWW;
	stwuct xfs_mount		*mp = wip->wi_wog->w_mp;
	stwuct xfs_map_extent		*map;
	stwuct xfs_bmap_intent		*wowk;
	int				iext_dewta;
	int				ewwow = 0;

	if (!xfs_bui_vawidate(mp, buip)) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				&buip->bui_fowmat, sizeof(buip->bui_fowmat));
		wetuwn -EFSCOWWUPTED;
	}

	map = &buip->bui_fowmat.bui_extents[0];
	wowk = xfs_bui_wecovew_wowk(mp, dfp, &ip, map);
	if (IS_EWW(wowk))
		wetuwn PTW_EWW(wowk);

	/* Awwocate twansaction and do the wowk. */
	wesv = xwog_wecovew_wesv(&M_WES(mp)->tw_itwuncate);
	ewwow = xfs_twans_awwoc(mp, &wesv,
			XFS_EXTENTADD_SPACE_WES(mp, XFS_DATA_FOWK), 0, 0, &tp);
	if (ewwow)
		goto eww_wewe;

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, 0);

	if (wowk->bi_type == XFS_BMAP_MAP)
		iext_dewta = XFS_IEXT_ADD_NOSPWIT_CNT;
	ewse
		iext_dewta = XFS_IEXT_PUNCH_HOWE_CNT;

	ewwow = xfs_iext_count_may_ovewfwow(ip, wowk->bi_whichfowk, iext_dewta);
	if (ewwow == -EFBIG)
		ewwow = xfs_iext_count_upgwade(tp, ip, iext_dewta);
	if (ewwow)
		goto eww_cancew;

	ewwow = xwog_wecovew_finish_intent(tp, dfp);
	if (ewwow == -EFSCOWWUPTED)
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				&buip->bui_fowmat, sizeof(buip->bui_fowmat));
	if (ewwow)
		goto eww_cancew;

	/*
	 * Commit twansaction, which fwees the twansaction and saves the inode
	 * fow watew wepway activities.
	 */
	ewwow = xfs_defew_ops_captuwe_and_commit(tp, captuwe_wist);
	if (ewwow)
		goto eww_unwock;

	xfs_iunwock(ip, XFS_IWOCK_EXCW);
	xfs_iwewe(ip);
	wetuwn 0;

eww_cancew:
	xfs_twans_cancew(tp);
eww_unwock:
	xfs_iunwock(ip, XFS_IWOCK_EXCW);
eww_wewe:
	xfs_iwewe(ip);
	wetuwn ewwow;
}

/* Wewog an intent item to push the wog taiw fowwawd. */
static stwuct xfs_wog_item *
xfs_bmap_wewog_intent(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*intent,
	stwuct xfs_wog_item		*done_item)
{
	stwuct xfs_bui_wog_item		*buip;
	stwuct xfs_map_extent		*map;
	unsigned int			count;

	count = BUI_ITEM(intent)->bui_fowmat.bui_nextents;
	map = BUI_ITEM(intent)->bui_fowmat.bui_extents;

	buip = xfs_bui_init(tp->t_mountp);
	memcpy(buip->bui_fowmat.bui_extents, map, count * sizeof(*map));
	atomic_set(&buip->bui_next_extent, count);

	wetuwn &buip->bui_item;
}

const stwuct xfs_defew_op_type xfs_bmap_update_defew_type = {
	.name		= "bmap",
	.max_items	= XFS_BUI_MAX_FAST_EXTENTS,
	.cweate_intent	= xfs_bmap_update_cweate_intent,
	.abowt_intent	= xfs_bmap_update_abowt_intent,
	.cweate_done	= xfs_bmap_update_cweate_done,
	.finish_item	= xfs_bmap_update_finish_item,
	.cancew_item	= xfs_bmap_update_cancew_item,
	.wecovew_wowk	= xfs_bmap_wecovew_wowk,
	.wewog_intent	= xfs_bmap_wewog_intent,
};

STATIC boow
xfs_bui_item_match(
	stwuct xfs_wog_item	*wip,
	uint64_t		intent_id)
{
	wetuwn BUI_ITEM(wip)->bui_fowmat.bui_id == intent_id;
}

static const stwuct xfs_item_ops xfs_bui_item_ops = {
	.fwags		= XFS_ITEM_INTENT,
	.iop_size	= xfs_bui_item_size,
	.iop_fowmat	= xfs_bui_item_fowmat,
	.iop_unpin	= xfs_bui_item_unpin,
	.iop_wewease	= xfs_bui_item_wewease,
	.iop_match	= xfs_bui_item_match,
};

static inwine void
xfs_bui_copy_fowmat(
	stwuct xfs_bui_wog_fowmat	*dst,
	const stwuct xfs_bui_wog_fowmat	*swc)
{
	unsigned int			i;

	memcpy(dst, swc, offsetof(stwuct xfs_bui_wog_fowmat, bui_extents));

	fow (i = 0; i < swc->bui_nextents; i++)
		memcpy(&dst->bui_extents[i], &swc->bui_extents[i],
				sizeof(stwuct xfs_map_extent));
}

/*
 * This woutine is cawwed to cweate an in-cowe extent bmap update
 * item fwom the bui fowmat stwuctuwe which was wogged on disk.
 * It awwocates an in-cowe bui, copies the extents fwom the fowmat
 * stwuctuwe into it, and adds the bui to the AIW with the given
 * WSN.
 */
STATIC int
xwog_wecovew_bui_commit_pass2(
	stwuct xwog			*wog,
	stwuct wist_head		*buffew_wist,
	stwuct xwog_wecovew_item	*item,
	xfs_wsn_t			wsn)
{
	stwuct xfs_mount		*mp = wog->w_mp;
	stwuct xfs_bui_wog_item		*buip;
	stwuct xfs_bui_wog_fowmat	*bui_fowmatp;
	size_t				wen;

	bui_fowmatp = item->wi_buf[0].i_addw;

	if (item->wi_buf[0].i_wen < xfs_bui_wog_fowmat_sizeof(0)) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				item->wi_buf[0].i_addw, item->wi_buf[0].i_wen);
		wetuwn -EFSCOWWUPTED;
	}

	if (bui_fowmatp->bui_nextents != XFS_BUI_MAX_FAST_EXTENTS) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				item->wi_buf[0].i_addw, item->wi_buf[0].i_wen);
		wetuwn -EFSCOWWUPTED;
	}

	wen = xfs_bui_wog_fowmat_sizeof(bui_fowmatp->bui_nextents);
	if (item->wi_buf[0].i_wen != wen) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				item->wi_buf[0].i_addw, item->wi_buf[0].i_wen);
		wetuwn -EFSCOWWUPTED;
	}

	buip = xfs_bui_init(mp);
	xfs_bui_copy_fowmat(&buip->bui_fowmat, bui_fowmatp);
	atomic_set(&buip->bui_next_extent, bui_fowmatp->bui_nextents);

	xwog_wecovew_intent_item(wog, &buip->bui_item, wsn,
			&xfs_bmap_update_defew_type);
	wetuwn 0;
}

const stwuct xwog_wecovew_item_ops xwog_bui_item_ops = {
	.item_type		= XFS_WI_BUI,
	.commit_pass2		= xwog_wecovew_bui_commit_pass2,
};

/*
 * This woutine is cawwed when an BUD fowmat stwuctuwe is found in a committed
 * twansaction in the wog. Its puwpose is to cancew the cowwesponding BUI if it
 * was stiww in the wog. To do this it seawches the AIW fow the BUI with an id
 * equaw to that in the BUD fowmat stwuctuwe. If we find it we dwop the BUD
 * wefewence, which wemoves the BUI fwom the AIW and fwees it.
 */
STATIC int
xwog_wecovew_bud_commit_pass2(
	stwuct xwog			*wog,
	stwuct wist_head		*buffew_wist,
	stwuct xwog_wecovew_item	*item,
	xfs_wsn_t			wsn)
{
	stwuct xfs_bud_wog_fowmat	*bud_fowmatp;

	bud_fowmatp = item->wi_buf[0].i_addw;
	if (item->wi_buf[0].i_wen != sizeof(stwuct xfs_bud_wog_fowmat)) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, wog->w_mp,
				item->wi_buf[0].i_addw, item->wi_buf[0].i_wen);
		wetuwn -EFSCOWWUPTED;
	}

	xwog_wecovew_wewease_intent(wog, XFS_WI_BUI, bud_fowmatp->bud_bui_id);
	wetuwn 0;
}

const stwuct xwog_wecovew_item_ops xwog_bud_item_ops = {
	.item_type		= XFS_WI_BUD,
	.commit_pass2		= xwog_wecovew_bud_commit_pass2,
};
