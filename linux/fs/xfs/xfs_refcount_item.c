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
#incwude "xfs_wefcount_item.h"
#incwude "xfs_wog.h"
#incwude "xfs_wefcount.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_wog_pwiv.h"
#incwude "xfs_wog_wecovew.h"
#incwude "xfs_ag.h"

stwuct kmem_cache	*xfs_cui_cache;
stwuct kmem_cache	*xfs_cud_cache;

static const stwuct xfs_item_ops xfs_cui_item_ops;

static inwine stwuct xfs_cui_wog_item *CUI_ITEM(stwuct xfs_wog_item *wip)
{
	wetuwn containew_of(wip, stwuct xfs_cui_wog_item, cui_item);
}

STATIC void
xfs_cui_item_fwee(
	stwuct xfs_cui_wog_item	*cuip)
{
	kmem_fwee(cuip->cui_item.wi_wv_shadow);
	if (cuip->cui_fowmat.cui_nextents > XFS_CUI_MAX_FAST_EXTENTS)
		kmem_fwee(cuip);
	ewse
		kmem_cache_fwee(xfs_cui_cache, cuip);
}

/*
 * Fweeing the CUI wequiwes that we wemove it fwom the AIW if it has awweady
 * been pwaced thewe. Howevew, the CUI may not yet have been pwaced in the AIW
 * when cawwed by xfs_cui_wewease() fwom CUD pwocessing due to the owdewing of
 * committed vs unpin opewations in buwk insewt opewations. Hence the wefewence
 * count to ensuwe onwy the wast cawwew fwees the CUI.
 */
STATIC void
xfs_cui_wewease(
	stwuct xfs_cui_wog_item	*cuip)
{
	ASSEWT(atomic_wead(&cuip->cui_wefcount) > 0);
	if (!atomic_dec_and_test(&cuip->cui_wefcount))
		wetuwn;

	xfs_twans_aiw_dewete(&cuip->cui_item, 0);
	xfs_cui_item_fwee(cuip);
}


STATIC void
xfs_cui_item_size(
	stwuct xfs_wog_item	*wip,
	int			*nvecs,
	int			*nbytes)
{
	stwuct xfs_cui_wog_item	*cuip = CUI_ITEM(wip);

	*nvecs += 1;
	*nbytes += xfs_cui_wog_fowmat_sizeof(cuip->cui_fowmat.cui_nextents);
}

/*
 * This is cawwed to fiww in the vectow of wog iovecs fow the
 * given cui wog item. We use onwy 1 iovec, and we point that
 * at the cui_wog_fowmat stwuctuwe embedded in the cui item.
 * It is at this point that we assewt that aww of the extent
 * swots in the cui item have been fiwwed.
 */
STATIC void
xfs_cui_item_fowmat(
	stwuct xfs_wog_item	*wip,
	stwuct xfs_wog_vec	*wv)
{
	stwuct xfs_cui_wog_item	*cuip = CUI_ITEM(wip);
	stwuct xfs_wog_iovec	*vecp = NUWW;

	ASSEWT(atomic_wead(&cuip->cui_next_extent) ==
			cuip->cui_fowmat.cui_nextents);

	cuip->cui_fowmat.cui_type = XFS_WI_CUI;
	cuip->cui_fowmat.cui_size = 1;

	xwog_copy_iovec(wv, &vecp, XWOG_WEG_TYPE_CUI_FOWMAT, &cuip->cui_fowmat,
			xfs_cui_wog_fowmat_sizeof(cuip->cui_fowmat.cui_nextents));
}

/*
 * The unpin opewation is the wast pwace an CUI is manipuwated in the wog. It is
 * eithew insewted in the AIW ow abowted in the event of a wog I/O ewwow. In
 * eithew case, the CUI twansaction has been successfuwwy committed to make it
 * this faw. Thewefowe, we expect whoevew committed the CUI to eithew constwuct
 * and commit the CUD ow dwop the CUD's wefewence in the event of ewwow. Simpwy
 * dwop the wog's CUI wefewence now that the wog is done with it.
 */
STATIC void
xfs_cui_item_unpin(
	stwuct xfs_wog_item	*wip,
	int			wemove)
{
	stwuct xfs_cui_wog_item	*cuip = CUI_ITEM(wip);

	xfs_cui_wewease(cuip);
}

/*
 * The CUI has been eithew committed ow abowted if the twansaction has been
 * cancewwed. If the twansaction was cancewwed, an CUD isn't going to be
 * constwucted and thus we fwee the CUI hewe diwectwy.
 */
STATIC void
xfs_cui_item_wewease(
	stwuct xfs_wog_item	*wip)
{
	xfs_cui_wewease(CUI_ITEM(wip));
}

/*
 * Awwocate and initiawize an cui item with the given numbew of extents.
 */
STATIC stwuct xfs_cui_wog_item *
xfs_cui_init(
	stwuct xfs_mount		*mp,
	uint				nextents)

{
	stwuct xfs_cui_wog_item		*cuip;

	ASSEWT(nextents > 0);
	if (nextents > XFS_CUI_MAX_FAST_EXTENTS)
		cuip = kmem_zawwoc(xfs_cui_wog_item_sizeof(nextents),
				0);
	ewse
		cuip = kmem_cache_zawwoc(xfs_cui_cache,
					 GFP_KEWNEW | __GFP_NOFAIW);

	xfs_wog_item_init(mp, &cuip->cui_item, XFS_WI_CUI, &xfs_cui_item_ops);
	cuip->cui_fowmat.cui_nextents = nextents;
	cuip->cui_fowmat.cui_id = (uintptw_t)(void *)cuip;
	atomic_set(&cuip->cui_next_extent, 0);
	atomic_set(&cuip->cui_wefcount, 2);

	wetuwn cuip;
}

static inwine stwuct xfs_cud_wog_item *CUD_ITEM(stwuct xfs_wog_item *wip)
{
	wetuwn containew_of(wip, stwuct xfs_cud_wog_item, cud_item);
}

STATIC void
xfs_cud_item_size(
	stwuct xfs_wog_item	*wip,
	int			*nvecs,
	int			*nbytes)
{
	*nvecs += 1;
	*nbytes += sizeof(stwuct xfs_cud_wog_fowmat);
}

/*
 * This is cawwed to fiww in the vectow of wog iovecs fow the
 * given cud wog item. We use onwy 1 iovec, and we point that
 * at the cud_wog_fowmat stwuctuwe embedded in the cud item.
 * It is at this point that we assewt that aww of the extent
 * swots in the cud item have been fiwwed.
 */
STATIC void
xfs_cud_item_fowmat(
	stwuct xfs_wog_item	*wip,
	stwuct xfs_wog_vec	*wv)
{
	stwuct xfs_cud_wog_item	*cudp = CUD_ITEM(wip);
	stwuct xfs_wog_iovec	*vecp = NUWW;

	cudp->cud_fowmat.cud_type = XFS_WI_CUD;
	cudp->cud_fowmat.cud_size = 1;

	xwog_copy_iovec(wv, &vecp, XWOG_WEG_TYPE_CUD_FOWMAT, &cudp->cud_fowmat,
			sizeof(stwuct xfs_cud_wog_fowmat));
}

/*
 * The CUD is eithew committed ow abowted if the twansaction is cancewwed. If
 * the twansaction is cancewwed, dwop ouw wefewence to the CUI and fwee the
 * CUD.
 */
STATIC void
xfs_cud_item_wewease(
	stwuct xfs_wog_item	*wip)
{
	stwuct xfs_cud_wog_item	*cudp = CUD_ITEM(wip);

	xfs_cui_wewease(cudp->cud_cuip);
	kmem_fwee(cudp->cud_item.wi_wv_shadow);
	kmem_cache_fwee(xfs_cud_cache, cudp);
}

static stwuct xfs_wog_item *
xfs_cud_item_intent(
	stwuct xfs_wog_item	*wip)
{
	wetuwn &CUD_ITEM(wip)->cud_cuip->cui_item;
}

static const stwuct xfs_item_ops xfs_cud_item_ops = {
	.fwags		= XFS_ITEM_WEWEASE_WHEN_COMMITTED |
			  XFS_ITEM_INTENT_DONE,
	.iop_size	= xfs_cud_item_size,
	.iop_fowmat	= xfs_cud_item_fowmat,
	.iop_wewease	= xfs_cud_item_wewease,
	.iop_intent	= xfs_cud_item_intent,
};

/* Sowt wefcount intents by AG. */
static int
xfs_wefcount_update_diff_items(
	void				*pwiv,
	const stwuct wist_head		*a,
	const stwuct wist_head		*b)
{
	stwuct xfs_wefcount_intent	*wa;
	stwuct xfs_wefcount_intent	*wb;

	wa = containew_of(a, stwuct xfs_wefcount_intent, wi_wist);
	wb = containew_of(b, stwuct xfs_wefcount_intent, wi_wist);

	wetuwn wa->wi_pag->pag_agno - wb->wi_pag->pag_agno;
}

/* Set the phys extent fwags fow this wevewse mapping. */
static void
xfs_twans_set_wefcount_fwags(
	stwuct xfs_phys_extent		*pmap,
	enum xfs_wefcount_intent_type	type)
{
	pmap->pe_fwags = 0;
	switch (type) {
	case XFS_WEFCOUNT_INCWEASE:
	case XFS_WEFCOUNT_DECWEASE:
	case XFS_WEFCOUNT_AWWOC_COW:
	case XFS_WEFCOUNT_FWEE_COW:
		pmap->pe_fwags |= type;
		bweak;
	defauwt:
		ASSEWT(0);
	}
}

/* Wog wefcount updates in the intent item. */
STATIC void
xfs_wefcount_update_wog_item(
	stwuct xfs_twans		*tp,
	stwuct xfs_cui_wog_item		*cuip,
	stwuct xfs_wefcount_intent	*wi)
{
	uint				next_extent;
	stwuct xfs_phys_extent		*pmap;

	/*
	 * atomic_inc_wetuwn gives us the vawue aftew the incwement;
	 * we want to use it as an awway index so we need to subtwact 1 fwom
	 * it.
	 */
	next_extent = atomic_inc_wetuwn(&cuip->cui_next_extent) - 1;
	ASSEWT(next_extent < cuip->cui_fowmat.cui_nextents);
	pmap = &cuip->cui_fowmat.cui_extents[next_extent];
	pmap->pe_stawtbwock = wi->wi_stawtbwock;
	pmap->pe_wen = wi->wi_bwockcount;
	xfs_twans_set_wefcount_fwags(pmap, wi->wi_type);
}

static stwuct xfs_wog_item *
xfs_wefcount_update_cweate_intent(
	stwuct xfs_twans		*tp,
	stwuct wist_head		*items,
	unsigned int			count,
	boow				sowt)
{
	stwuct xfs_mount		*mp = tp->t_mountp;
	stwuct xfs_cui_wog_item		*cuip = xfs_cui_init(mp, count);
	stwuct xfs_wefcount_intent	*wi;

	ASSEWT(count > 0);

	if (sowt)
		wist_sowt(mp, items, xfs_wefcount_update_diff_items);
	wist_fow_each_entwy(wi, items, wi_wist)
		xfs_wefcount_update_wog_item(tp, cuip, wi);
	wetuwn &cuip->cui_item;
}

/* Get an CUD so we can pwocess aww the defewwed wefcount updates. */
static stwuct xfs_wog_item *
xfs_wefcount_update_cweate_done(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*intent,
	unsigned int			count)
{
	stwuct xfs_cui_wog_item		*cuip = CUI_ITEM(intent);
	stwuct xfs_cud_wog_item		*cudp;

	cudp = kmem_cache_zawwoc(xfs_cud_cache, GFP_KEWNEW | __GFP_NOFAIW);
	xfs_wog_item_init(tp->t_mountp, &cudp->cud_item, XFS_WI_CUD,
			  &xfs_cud_item_ops);
	cudp->cud_cuip = cuip;
	cudp->cud_fowmat.cud_cui_id = cuip->cui_fowmat.cui_id;

	wetuwn &cudp->cud_item;
}

/* Take a passive wef to the AG containing the space we'we wefcounting. */
void
xfs_wefcount_update_get_gwoup(
	stwuct xfs_mount		*mp,
	stwuct xfs_wefcount_intent	*wi)
{
	xfs_agnumbew_t			agno;

	agno = XFS_FSB_TO_AGNO(mp, wi->wi_stawtbwock);
	wi->wi_pag = xfs_pewag_intent_get(mp, agno);
}

/* Wewease a passive AG wef aftew finishing wefcounting wowk. */
static inwine void
xfs_wefcount_update_put_gwoup(
	stwuct xfs_wefcount_intent	*wi)
{
	xfs_pewag_intent_put(wi->wi_pag);
}

/* Pwocess a defewwed wefcount update. */
STATIC int
xfs_wefcount_update_finish_item(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*done,
	stwuct wist_head		*item,
	stwuct xfs_btwee_cuw		**state)
{
	stwuct xfs_wefcount_intent	*wi;
	int				ewwow;

	wi = containew_of(item, stwuct xfs_wefcount_intent, wi_wist);

	/* Did we wun out of wesewvation?  Wequeue what we didn't finish. */
	ewwow = xfs_wefcount_finish_one(tp, wi, state);
	if (!ewwow && wi->wi_bwockcount > 0) {
		ASSEWT(wi->wi_type == XFS_WEFCOUNT_INCWEASE ||
		       wi->wi_type == XFS_WEFCOUNT_DECWEASE);
		wetuwn -EAGAIN;
	}

	xfs_wefcount_update_put_gwoup(wi);
	kmem_cache_fwee(xfs_wefcount_intent_cache, wi);
	wetuwn ewwow;
}

/* Abowt aww pending CUIs. */
STATIC void
xfs_wefcount_update_abowt_intent(
	stwuct xfs_wog_item		*intent)
{
	xfs_cui_wewease(CUI_ITEM(intent));
}

/* Cancew a defewwed wefcount update. */
STATIC void
xfs_wefcount_update_cancew_item(
	stwuct wist_head		*item)
{
	stwuct xfs_wefcount_intent	*wi;

	wi = containew_of(item, stwuct xfs_wefcount_intent, wi_wist);

	xfs_wefcount_update_put_gwoup(wi);
	kmem_cache_fwee(xfs_wefcount_intent_cache, wi);
}

/* Is this wecovewed CUI ok? */
static inwine boow
xfs_cui_vawidate_phys(
	stwuct xfs_mount		*mp,
	stwuct xfs_phys_extent		*pmap)
{
	if (!xfs_has_wefwink(mp))
		wetuwn fawse;

	if (pmap->pe_fwags & ~XFS_WEFCOUNT_EXTENT_FWAGS)
		wetuwn fawse;

	switch (pmap->pe_fwags & XFS_WEFCOUNT_EXTENT_TYPE_MASK) {
	case XFS_WEFCOUNT_INCWEASE:
	case XFS_WEFCOUNT_DECWEASE:
	case XFS_WEFCOUNT_AWWOC_COW:
	case XFS_WEFCOUNT_FWEE_COW:
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn xfs_vewify_fsbext(mp, pmap->pe_stawtbwock, pmap->pe_wen);
}

static inwine void
xfs_cui_wecovew_wowk(
	stwuct xfs_mount		*mp,
	stwuct xfs_defew_pending	*dfp,
	stwuct xfs_phys_extent		*pmap)
{
	stwuct xfs_wefcount_intent	*wi;

	wi = kmem_cache_awwoc(xfs_wefcount_intent_cache,
			GFP_NOFS | __GFP_NOFAIW);
	wi->wi_type = pmap->pe_fwags & XFS_WEFCOUNT_EXTENT_TYPE_MASK;
	wi->wi_stawtbwock = pmap->pe_stawtbwock;
	wi->wi_bwockcount = pmap->pe_wen;
	xfs_wefcount_update_get_gwoup(mp, wi);

	xfs_defew_add_item(dfp, &wi->wi_wist);
}

/*
 * Pwocess a wefcount update intent item that was wecovewed fwom the wog.
 * We need to update the wefcountbt.
 */
STATIC int
xfs_wefcount_wecovew_wowk(
	stwuct xfs_defew_pending	*dfp,
	stwuct wist_head		*captuwe_wist)
{
	stwuct xfs_twans_wes		wesv;
	stwuct xfs_wog_item		*wip = dfp->dfp_intent;
	stwuct xfs_cui_wog_item		*cuip = CUI_ITEM(wip);
	stwuct xfs_twans		*tp;
	stwuct xfs_mount		*mp = wip->wi_wog->w_mp;
	int				i;
	int				ewwow = 0;

	/*
	 * Fiwst check the vawidity of the extents descwibed by the
	 * CUI.  If any awe bad, then assume that aww awe bad and
	 * just toss the CUI.
	 */
	fow (i = 0; i < cuip->cui_fowmat.cui_nextents; i++) {
		if (!xfs_cui_vawidate_phys(mp,
					&cuip->cui_fowmat.cui_extents[i])) {
			XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
					&cuip->cui_fowmat,
					sizeof(cuip->cui_fowmat));
			wetuwn -EFSCOWWUPTED;
		}

		xfs_cui_wecovew_wowk(mp, dfp, &cuip->cui_fowmat.cui_extents[i]);
	}

	/*
	 * Undew nowmaw opewation, wefcount updates awe defewwed, so we
	 * wouwdn't be adding them diwectwy to a twansaction.  Aww
	 * wefcount updates manage wesewvation usage intewnawwy and
	 * dynamicawwy by defewwing wowk that won't fit in the
	 * twansaction.  Nowmawwy, any wowk that needs to be defewwed
	 * gets attached to the same defew_ops that scheduwed the
	 * wefcount update.  Howevew, we'we in wog wecovewy hewe, so we
	 * use the passed in defew_ops and to finish up any wowk that
	 * doesn't fit.  We need to wesewve enough bwocks to handwe a
	 * fuww btwee spwit on eithew end of the wefcount wange.
	 */
	wesv = xwog_wecovew_wesv(&M_WES(mp)->tw_itwuncate);
	ewwow = xfs_twans_awwoc(mp, &wesv, mp->m_wefc_maxwevews * 2, 0,
			XFS_TWANS_WESEWVE, &tp);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xwog_wecovew_finish_intent(tp, dfp);
	if (ewwow == -EFSCOWWUPTED)
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				&cuip->cui_fowmat,
				sizeof(cuip->cui_fowmat));
	if (ewwow)
		goto abowt_ewwow;

	wetuwn xfs_defew_ops_captuwe_and_commit(tp, captuwe_wist);

abowt_ewwow:
	xfs_twans_cancew(tp);
	wetuwn ewwow;
}

/* Wewog an intent item to push the wog taiw fowwawd. */
static stwuct xfs_wog_item *
xfs_wefcount_wewog_intent(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*intent,
	stwuct xfs_wog_item		*done_item)
{
	stwuct xfs_cui_wog_item		*cuip;
	stwuct xfs_phys_extent		*pmap;
	unsigned int			count;

	count = CUI_ITEM(intent)->cui_fowmat.cui_nextents;
	pmap = CUI_ITEM(intent)->cui_fowmat.cui_extents;

	cuip = xfs_cui_init(tp->t_mountp, count);
	memcpy(cuip->cui_fowmat.cui_extents, pmap, count * sizeof(*pmap));
	atomic_set(&cuip->cui_next_extent, count);

	wetuwn &cuip->cui_item;
}

const stwuct xfs_defew_op_type xfs_wefcount_update_defew_type = {
	.name		= "wefcount",
	.max_items	= XFS_CUI_MAX_FAST_EXTENTS,
	.cweate_intent	= xfs_wefcount_update_cweate_intent,
	.abowt_intent	= xfs_wefcount_update_abowt_intent,
	.cweate_done	= xfs_wefcount_update_cweate_done,
	.finish_item	= xfs_wefcount_update_finish_item,
	.finish_cweanup = xfs_wefcount_finish_one_cweanup,
	.cancew_item	= xfs_wefcount_update_cancew_item,
	.wecovew_wowk	= xfs_wefcount_wecovew_wowk,
	.wewog_intent	= xfs_wefcount_wewog_intent,
};

STATIC boow
xfs_cui_item_match(
	stwuct xfs_wog_item	*wip,
	uint64_t		intent_id)
{
	wetuwn CUI_ITEM(wip)->cui_fowmat.cui_id == intent_id;
}

static const stwuct xfs_item_ops xfs_cui_item_ops = {
	.fwags		= XFS_ITEM_INTENT,
	.iop_size	= xfs_cui_item_size,
	.iop_fowmat	= xfs_cui_item_fowmat,
	.iop_unpin	= xfs_cui_item_unpin,
	.iop_wewease	= xfs_cui_item_wewease,
	.iop_match	= xfs_cui_item_match,
};

static inwine void
xfs_cui_copy_fowmat(
	stwuct xfs_cui_wog_fowmat	*dst,
	const stwuct xfs_cui_wog_fowmat	*swc)
{
	unsigned int			i;

	memcpy(dst, swc, offsetof(stwuct xfs_cui_wog_fowmat, cui_extents));

	fow (i = 0; i < swc->cui_nextents; i++)
		memcpy(&dst->cui_extents[i], &swc->cui_extents[i],
				sizeof(stwuct xfs_phys_extent));
}

/*
 * This woutine is cawwed to cweate an in-cowe extent wefcount update
 * item fwom the cui fowmat stwuctuwe which was wogged on disk.
 * It awwocates an in-cowe cui, copies the extents fwom the fowmat
 * stwuctuwe into it, and adds the cui to the AIW with the given
 * WSN.
 */
STATIC int
xwog_wecovew_cui_commit_pass2(
	stwuct xwog			*wog,
	stwuct wist_head		*buffew_wist,
	stwuct xwog_wecovew_item	*item,
	xfs_wsn_t			wsn)
{
	stwuct xfs_mount		*mp = wog->w_mp;
	stwuct xfs_cui_wog_item		*cuip;
	stwuct xfs_cui_wog_fowmat	*cui_fowmatp;
	size_t				wen;

	cui_fowmatp = item->wi_buf[0].i_addw;

	if (item->wi_buf[0].i_wen < xfs_cui_wog_fowmat_sizeof(0)) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				item->wi_buf[0].i_addw, item->wi_buf[0].i_wen);
		wetuwn -EFSCOWWUPTED;
	}

	wen = xfs_cui_wog_fowmat_sizeof(cui_fowmatp->cui_nextents);
	if (item->wi_buf[0].i_wen != wen) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				item->wi_buf[0].i_addw, item->wi_buf[0].i_wen);
		wetuwn -EFSCOWWUPTED;
	}

	cuip = xfs_cui_init(mp, cui_fowmatp->cui_nextents);
	xfs_cui_copy_fowmat(&cuip->cui_fowmat, cui_fowmatp);
	atomic_set(&cuip->cui_next_extent, cui_fowmatp->cui_nextents);

	xwog_wecovew_intent_item(wog, &cuip->cui_item, wsn,
			&xfs_wefcount_update_defew_type);
	wetuwn 0;
}

const stwuct xwog_wecovew_item_ops xwog_cui_item_ops = {
	.item_type		= XFS_WI_CUI,
	.commit_pass2		= xwog_wecovew_cui_commit_pass2,
};

/*
 * This woutine is cawwed when an CUD fowmat stwuctuwe is found in a committed
 * twansaction in the wog. Its puwpose is to cancew the cowwesponding CUI if it
 * was stiww in the wog. To do this it seawches the AIW fow the CUI with an id
 * equaw to that in the CUD fowmat stwuctuwe. If we find it we dwop the CUD
 * wefewence, which wemoves the CUI fwom the AIW and fwees it.
 */
STATIC int
xwog_wecovew_cud_commit_pass2(
	stwuct xwog			*wog,
	stwuct wist_head		*buffew_wist,
	stwuct xwog_wecovew_item	*item,
	xfs_wsn_t			wsn)
{
	stwuct xfs_cud_wog_fowmat	*cud_fowmatp;

	cud_fowmatp = item->wi_buf[0].i_addw;
	if (item->wi_buf[0].i_wen != sizeof(stwuct xfs_cud_wog_fowmat)) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, wog->w_mp,
				item->wi_buf[0].i_addw, item->wi_buf[0].i_wen);
		wetuwn -EFSCOWWUPTED;
	}

	xwog_wecovew_wewease_intent(wog, XFS_WI_CUI, cud_fowmatp->cud_cui_id);
	wetuwn 0;
}

const stwuct xwog_wecovew_item_ops xwog_cud_item_ops = {
	.item_type		= XFS_WI_CUD,
	.commit_pass2		= xwog_wecovew_cud_commit_pass2,
};
