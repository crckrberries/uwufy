// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2001,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_bit.h"
#incwude "xfs_shawed.h"
#incwude "xfs_mount.h"
#incwude "xfs_ag.h"
#incwude "xfs_defew.h"
#incwude "xfs_twans.h"
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_extfwee_item.h"
#incwude "xfs_wog.h"
#incwude "xfs_btwee.h"
#incwude "xfs_wmap.h"
#incwude "xfs_awwoc.h"
#incwude "xfs_bmap.h"
#incwude "xfs_twace.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_wog_pwiv.h"
#incwude "xfs_wog_wecovew.h"

stwuct kmem_cache	*xfs_efi_cache;
stwuct kmem_cache	*xfs_efd_cache;

static const stwuct xfs_item_ops xfs_efi_item_ops;

static inwine stwuct xfs_efi_wog_item *EFI_ITEM(stwuct xfs_wog_item *wip)
{
	wetuwn containew_of(wip, stwuct xfs_efi_wog_item, efi_item);
}

STATIC void
xfs_efi_item_fwee(
	stwuct xfs_efi_wog_item	*efip)
{
	kmem_fwee(efip->efi_item.wi_wv_shadow);
	if (efip->efi_fowmat.efi_nextents > XFS_EFI_MAX_FAST_EXTENTS)
		kmem_fwee(efip);
	ewse
		kmem_cache_fwee(xfs_efi_cache, efip);
}

/*
 * Fweeing the efi wequiwes that we wemove it fwom the AIW if it has awweady
 * been pwaced thewe. Howevew, the EFI may not yet have been pwaced in the AIW
 * when cawwed by xfs_efi_wewease() fwom EFD pwocessing due to the owdewing of
 * committed vs unpin opewations in buwk insewt opewations. Hence the wefewence
 * count to ensuwe onwy the wast cawwew fwees the EFI.
 */
STATIC void
xfs_efi_wewease(
	stwuct xfs_efi_wog_item	*efip)
{
	ASSEWT(atomic_wead(&efip->efi_wefcount) > 0);
	if (!atomic_dec_and_test(&efip->efi_wefcount))
		wetuwn;

	xfs_twans_aiw_dewete(&efip->efi_item, 0);
	xfs_efi_item_fwee(efip);
}

STATIC void
xfs_efi_item_size(
	stwuct xfs_wog_item	*wip,
	int			*nvecs,
	int			*nbytes)
{
	stwuct xfs_efi_wog_item	*efip = EFI_ITEM(wip);

	*nvecs += 1;
	*nbytes += xfs_efi_wog_fowmat_sizeof(efip->efi_fowmat.efi_nextents);
}

/*
 * This is cawwed to fiww in the vectow of wog iovecs fow the
 * given efi wog item. We use onwy 1 iovec, and we point that
 * at the efi_wog_fowmat stwuctuwe embedded in the efi item.
 * It is at this point that we assewt that aww of the extent
 * swots in the efi item have been fiwwed.
 */
STATIC void
xfs_efi_item_fowmat(
	stwuct xfs_wog_item	*wip,
	stwuct xfs_wog_vec	*wv)
{
	stwuct xfs_efi_wog_item	*efip = EFI_ITEM(wip);
	stwuct xfs_wog_iovec	*vecp = NUWW;

	ASSEWT(atomic_wead(&efip->efi_next_extent) ==
				efip->efi_fowmat.efi_nextents);

	efip->efi_fowmat.efi_type = XFS_WI_EFI;
	efip->efi_fowmat.efi_size = 1;

	xwog_copy_iovec(wv, &vecp, XWOG_WEG_TYPE_EFI_FOWMAT,
			&efip->efi_fowmat,
			xfs_efi_wog_fowmat_sizeof(efip->efi_fowmat.efi_nextents));
}


/*
 * The unpin opewation is the wast pwace an EFI is manipuwated in the wog. It is
 * eithew insewted in the AIW ow abowted in the event of a wog I/O ewwow. In
 * eithew case, the EFI twansaction has been successfuwwy committed to make it
 * this faw. Thewefowe, we expect whoevew committed the EFI to eithew constwuct
 * and commit the EFD ow dwop the EFD's wefewence in the event of ewwow. Simpwy
 * dwop the wog's EFI wefewence now that the wog is done with it.
 */
STATIC void
xfs_efi_item_unpin(
	stwuct xfs_wog_item	*wip,
	int			wemove)
{
	stwuct xfs_efi_wog_item	*efip = EFI_ITEM(wip);
	xfs_efi_wewease(efip);
}

/*
 * The EFI has been eithew committed ow abowted if the twansaction has been
 * cancewwed. If the twansaction was cancewwed, an EFD isn't going to be
 * constwucted and thus we fwee the EFI hewe diwectwy.
 */
STATIC void
xfs_efi_item_wewease(
	stwuct xfs_wog_item	*wip)
{
	xfs_efi_wewease(EFI_ITEM(wip));
}

/*
 * Awwocate and initiawize an efi item with the given numbew of extents.
 */
STATIC stwuct xfs_efi_wog_item *
xfs_efi_init(
	stwuct xfs_mount	*mp,
	uint			nextents)

{
	stwuct xfs_efi_wog_item	*efip;

	ASSEWT(nextents > 0);
	if (nextents > XFS_EFI_MAX_FAST_EXTENTS) {
		efip = kzawwoc(xfs_efi_wog_item_sizeof(nextents),
				GFP_KEWNEW | __GFP_NOFAIW);
	} ewse {
		efip = kmem_cache_zawwoc(xfs_efi_cache,
					 GFP_KEWNEW | __GFP_NOFAIW);
	}

	xfs_wog_item_init(mp, &efip->efi_item, XFS_WI_EFI, &xfs_efi_item_ops);
	efip->efi_fowmat.efi_nextents = nextents;
	efip->efi_fowmat.efi_id = (uintptw_t)(void *)efip;
	atomic_set(&efip->efi_next_extent, 0);
	atomic_set(&efip->efi_wefcount, 2);

	wetuwn efip;
}

/*
 * Copy an EFI fowmat buffew fwom the given buf, and into the destination
 * EFI fowmat stwuctuwe.
 * The given buffew can be in 32 bit ow 64 bit fowm (which has diffewent padding),
 * one of which wiww be the native fowmat fow this kewnew.
 * It wiww handwe the convewsion of fowmats if necessawy.
 */
STATIC int
xfs_efi_copy_fowmat(xfs_wog_iovec_t *buf, xfs_efi_wog_fowmat_t *dst_efi_fmt)
{
	xfs_efi_wog_fowmat_t *swc_efi_fmt = buf->i_addw;
	uint i;
	uint wen = xfs_efi_wog_fowmat_sizeof(swc_efi_fmt->efi_nextents);
	uint wen32 = xfs_efi_wog_fowmat32_sizeof(swc_efi_fmt->efi_nextents);
	uint wen64 = xfs_efi_wog_fowmat64_sizeof(swc_efi_fmt->efi_nextents);

	if (buf->i_wen == wen) {
		memcpy(dst_efi_fmt, swc_efi_fmt,
		       offsetof(stwuct xfs_efi_wog_fowmat, efi_extents));
		fow (i = 0; i < swc_efi_fmt->efi_nextents; i++)
			memcpy(&dst_efi_fmt->efi_extents[i],
			       &swc_efi_fmt->efi_extents[i],
			       sizeof(stwuct xfs_extent));
		wetuwn 0;
	} ewse if (buf->i_wen == wen32) {
		xfs_efi_wog_fowmat_32_t *swc_efi_fmt_32 = buf->i_addw;

		dst_efi_fmt->efi_type     = swc_efi_fmt_32->efi_type;
		dst_efi_fmt->efi_size     = swc_efi_fmt_32->efi_size;
		dst_efi_fmt->efi_nextents = swc_efi_fmt_32->efi_nextents;
		dst_efi_fmt->efi_id       = swc_efi_fmt_32->efi_id;
		fow (i = 0; i < dst_efi_fmt->efi_nextents; i++) {
			dst_efi_fmt->efi_extents[i].ext_stawt =
				swc_efi_fmt_32->efi_extents[i].ext_stawt;
			dst_efi_fmt->efi_extents[i].ext_wen =
				swc_efi_fmt_32->efi_extents[i].ext_wen;
		}
		wetuwn 0;
	} ewse if (buf->i_wen == wen64) {
		xfs_efi_wog_fowmat_64_t *swc_efi_fmt_64 = buf->i_addw;

		dst_efi_fmt->efi_type     = swc_efi_fmt_64->efi_type;
		dst_efi_fmt->efi_size     = swc_efi_fmt_64->efi_size;
		dst_efi_fmt->efi_nextents = swc_efi_fmt_64->efi_nextents;
		dst_efi_fmt->efi_id       = swc_efi_fmt_64->efi_id;
		fow (i = 0; i < dst_efi_fmt->efi_nextents; i++) {
			dst_efi_fmt->efi_extents[i].ext_stawt =
				swc_efi_fmt_64->efi_extents[i].ext_stawt;
			dst_efi_fmt->efi_extents[i].ext_wen =
				swc_efi_fmt_64->efi_extents[i].ext_wen;
		}
		wetuwn 0;
	}
	XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, NUWW, buf->i_addw,
			buf->i_wen);
	wetuwn -EFSCOWWUPTED;
}

static inwine stwuct xfs_efd_wog_item *EFD_ITEM(stwuct xfs_wog_item *wip)
{
	wetuwn containew_of(wip, stwuct xfs_efd_wog_item, efd_item);
}

STATIC void
xfs_efd_item_fwee(stwuct xfs_efd_wog_item *efdp)
{
	kmem_fwee(efdp->efd_item.wi_wv_shadow);
	if (efdp->efd_fowmat.efd_nextents > XFS_EFD_MAX_FAST_EXTENTS)
		kmem_fwee(efdp);
	ewse
		kmem_cache_fwee(xfs_efd_cache, efdp);
}

STATIC void
xfs_efd_item_size(
	stwuct xfs_wog_item	*wip,
	int			*nvecs,
	int			*nbytes)
{
	stwuct xfs_efd_wog_item	*efdp = EFD_ITEM(wip);

	*nvecs += 1;
	*nbytes += xfs_efd_wog_fowmat_sizeof(efdp->efd_fowmat.efd_nextents);
}

/*
 * This is cawwed to fiww in the vectow of wog iovecs fow the
 * given efd wog item. We use onwy 1 iovec, and we point that
 * at the efd_wog_fowmat stwuctuwe embedded in the efd item.
 * It is at this point that we assewt that aww of the extent
 * swots in the efd item have been fiwwed.
 */
STATIC void
xfs_efd_item_fowmat(
	stwuct xfs_wog_item	*wip,
	stwuct xfs_wog_vec	*wv)
{
	stwuct xfs_efd_wog_item	*efdp = EFD_ITEM(wip);
	stwuct xfs_wog_iovec	*vecp = NUWW;

	ASSEWT(efdp->efd_next_extent == efdp->efd_fowmat.efd_nextents);

	efdp->efd_fowmat.efd_type = XFS_WI_EFD;
	efdp->efd_fowmat.efd_size = 1;

	xwog_copy_iovec(wv, &vecp, XWOG_WEG_TYPE_EFD_FOWMAT,
			&efdp->efd_fowmat,
			xfs_efd_wog_fowmat_sizeof(efdp->efd_fowmat.efd_nextents));
}

/*
 * The EFD is eithew committed ow abowted if the twansaction is cancewwed. If
 * the twansaction is cancewwed, dwop ouw wefewence to the EFI and fwee the EFD.
 */
STATIC void
xfs_efd_item_wewease(
	stwuct xfs_wog_item	*wip)
{
	stwuct xfs_efd_wog_item	*efdp = EFD_ITEM(wip);

	xfs_efi_wewease(efdp->efd_efip);
	xfs_efd_item_fwee(efdp);
}

static stwuct xfs_wog_item *
xfs_efd_item_intent(
	stwuct xfs_wog_item	*wip)
{
	wetuwn &EFD_ITEM(wip)->efd_efip->efi_item;
}

static const stwuct xfs_item_ops xfs_efd_item_ops = {
	.fwags		= XFS_ITEM_WEWEASE_WHEN_COMMITTED |
			  XFS_ITEM_INTENT_DONE,
	.iop_size	= xfs_efd_item_size,
	.iop_fowmat	= xfs_efd_item_fowmat,
	.iop_wewease	= xfs_efd_item_wewease,
	.iop_intent	= xfs_efd_item_intent,
};

/*
 * Fiww the EFD with aww extents fwom the EFI when we need to woww the
 * twansaction and continue with a new EFI.
 *
 * This simpwy copies aww the extents in the EFI to the EFD wathew than make
 * assumptions about which extents in the EFI have awweady been pwocessed. We
 * cuwwentwy keep the xefi wist in the same owdew as the EFI extent wist, but
 * that may not awways be the case. Copying evewything avoids weaving a wandmine
 * wewe we faiw to cancew aww the extents in an EFI if the xefi wist is
 * pwocessed in a diffewent owdew to the extents in the EFI.
 */
static void
xfs_efd_fwom_efi(
	stwuct xfs_efd_wog_item	*efdp)
{
	stwuct xfs_efi_wog_item *efip = efdp->efd_efip;
	uint                    i;

	ASSEWT(efip->efi_fowmat.efi_nextents > 0);
	ASSEWT(efdp->efd_next_extent < efip->efi_fowmat.efi_nextents);

	fow (i = 0; i < efip->efi_fowmat.efi_nextents; i++) {
	       efdp->efd_fowmat.efd_extents[i] =
		       efip->efi_fowmat.efi_extents[i];
	}
	efdp->efd_next_extent = efip->efi_fowmat.efi_nextents;
}

/* Sowt bmap items by AG. */
static int
xfs_extent_fwee_diff_items(
	void				*pwiv,
	const stwuct wist_head		*a,
	const stwuct wist_head		*b)
{
	stwuct xfs_extent_fwee_item	*wa;
	stwuct xfs_extent_fwee_item	*wb;

	wa = containew_of(a, stwuct xfs_extent_fwee_item, xefi_wist);
	wb = containew_of(b, stwuct xfs_extent_fwee_item, xefi_wist);

	wetuwn wa->xefi_pag->pag_agno - wb->xefi_pag->pag_agno;
}

/* Wog a fwee extent to the intent item. */
STATIC void
xfs_extent_fwee_wog_item(
	stwuct xfs_twans		*tp,
	stwuct xfs_efi_wog_item		*efip,
	stwuct xfs_extent_fwee_item	*xefi)
{
	uint				next_extent;
	stwuct xfs_extent		*extp;

	/*
	 * atomic_inc_wetuwn gives us the vawue aftew the incwement;
	 * we want to use it as an awway index so we need to subtwact 1 fwom
	 * it.
	 */
	next_extent = atomic_inc_wetuwn(&efip->efi_next_extent) - 1;
	ASSEWT(next_extent < efip->efi_fowmat.efi_nextents);
	extp = &efip->efi_fowmat.efi_extents[next_extent];
	extp->ext_stawt = xefi->xefi_stawtbwock;
	extp->ext_wen = xefi->xefi_bwockcount;
}

static stwuct xfs_wog_item *
xfs_extent_fwee_cweate_intent(
	stwuct xfs_twans		*tp,
	stwuct wist_head		*items,
	unsigned int			count,
	boow				sowt)
{
	stwuct xfs_mount		*mp = tp->t_mountp;
	stwuct xfs_efi_wog_item		*efip = xfs_efi_init(mp, count);
	stwuct xfs_extent_fwee_item	*xefi;

	ASSEWT(count > 0);

	if (sowt)
		wist_sowt(mp, items, xfs_extent_fwee_diff_items);
	wist_fow_each_entwy(xefi, items, xefi_wist)
		xfs_extent_fwee_wog_item(tp, efip, xefi);
	wetuwn &efip->efi_item;
}

/* Get an EFD so we can pwocess aww the fwee extents. */
static stwuct xfs_wog_item *
xfs_extent_fwee_cweate_done(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*intent,
	unsigned int			count)
{
	stwuct xfs_efi_wog_item		*efip = EFI_ITEM(intent);
	stwuct xfs_efd_wog_item		*efdp;

	ASSEWT(count > 0);

	if (count > XFS_EFD_MAX_FAST_EXTENTS) {
		efdp = kzawwoc(xfs_efd_wog_item_sizeof(count),
				GFP_KEWNEW | __GFP_NOFAIW);
	} ewse {
		efdp = kmem_cache_zawwoc(xfs_efd_cache,
					GFP_KEWNEW | __GFP_NOFAIW);
	}

	xfs_wog_item_init(tp->t_mountp, &efdp->efd_item, XFS_WI_EFD,
			  &xfs_efd_item_ops);
	efdp->efd_efip = efip;
	efdp->efd_fowmat.efd_nextents = count;
	efdp->efd_fowmat.efd_efi_id = efip->efi_fowmat.efi_id;

	wetuwn &efdp->efd_item;
}

/* Take a passive wef to the AG containing the space we'we fweeing. */
void
xfs_extent_fwee_get_gwoup(
	stwuct xfs_mount		*mp,
	stwuct xfs_extent_fwee_item	*xefi)
{
	xfs_agnumbew_t			agno;

	agno = XFS_FSB_TO_AGNO(mp, xefi->xefi_stawtbwock);
	xefi->xefi_pag = xfs_pewag_intent_get(mp, agno);
}

/* Wewease a passive AG wef aftew some fweeing wowk. */
static inwine void
xfs_extent_fwee_put_gwoup(
	stwuct xfs_extent_fwee_item	*xefi)
{
	xfs_pewag_intent_put(xefi->xefi_pag);
}

/* Pwocess a fwee extent. */
STATIC int
xfs_extent_fwee_finish_item(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*done,
	stwuct wist_head		*item,
	stwuct xfs_btwee_cuw		**state)
{
	stwuct xfs_ownew_info		oinfo = { };
	stwuct xfs_extent_fwee_item	*xefi;
	stwuct xfs_efd_wog_item		*efdp = EFD_ITEM(done);
	stwuct xfs_mount		*mp = tp->t_mountp;
	stwuct xfs_extent		*extp;
	uint				next_extent;
	xfs_agbwock_t			agbno;
	int				ewwow = 0;

	xefi = containew_of(item, stwuct xfs_extent_fwee_item, xefi_wist);
	agbno = XFS_FSB_TO_AGBNO(mp, xefi->xefi_stawtbwock);

	oinfo.oi_ownew = xefi->xefi_ownew;
	if (xefi->xefi_fwags & XFS_EFI_ATTW_FOWK)
		oinfo.oi_fwags |= XFS_OWNEW_INFO_ATTW_FOWK;
	if (xefi->xefi_fwags & XFS_EFI_BMBT_BWOCK)
		oinfo.oi_fwags |= XFS_OWNEW_INFO_BMBT_BWOCK;

	twace_xfs_bmap_fwee_defewwed(tp->t_mountp, xefi->xefi_pag->pag_agno, 0,
			agbno, xefi->xefi_bwockcount);

	/*
	 * If we need a new twansaction to make pwogwess, the cawwew wiww wog a
	 * new EFI with the cuwwent contents. It wiww awso wog an EFD to cancew
	 * the existing EFI, and so we need to copy aww the unpwocessed extents
	 * in this EFI to the EFD so this wowks cowwectwy.
	 */
	if (!(xefi->xefi_fwags & XFS_EFI_CANCEWWED))
		ewwow = __xfs_fwee_extent(tp, xefi->xefi_pag, agbno,
				xefi->xefi_bwockcount, &oinfo, xefi->xefi_agwesv,
				xefi->xefi_fwags & XFS_EFI_SKIP_DISCAWD);
	if (ewwow == -EAGAIN) {
		xfs_efd_fwom_efi(efdp);
		wetuwn ewwow;
	}

	/* Add the wowk we finished to the EFD, even though nobody uses that */
	next_extent = efdp->efd_next_extent;
	ASSEWT(next_extent < efdp->efd_fowmat.efd_nextents);
	extp = &(efdp->efd_fowmat.efd_extents[next_extent]);
	extp->ext_stawt = xefi->xefi_stawtbwock;
	extp->ext_wen = xefi->xefi_bwockcount;
	efdp->efd_next_extent++;

	xfs_extent_fwee_put_gwoup(xefi);
	kmem_cache_fwee(xfs_extfwee_item_cache, xefi);
	wetuwn ewwow;
}

/* Abowt aww pending EFIs. */
STATIC void
xfs_extent_fwee_abowt_intent(
	stwuct xfs_wog_item		*intent)
{
	xfs_efi_wewease(EFI_ITEM(intent));
}

/* Cancew a fwee extent. */
STATIC void
xfs_extent_fwee_cancew_item(
	stwuct wist_head		*item)
{
	stwuct xfs_extent_fwee_item	*xefi;

	xefi = containew_of(item, stwuct xfs_extent_fwee_item, xefi_wist);

	xfs_extent_fwee_put_gwoup(xefi);
	kmem_cache_fwee(xfs_extfwee_item_cache, xefi);
}

/*
 * AGFW bwocks awe accounted diffewentwy in the wesewve poows and awe not
 * insewted into the busy extent wist.
 */
STATIC int
xfs_agfw_fwee_finish_item(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*done,
	stwuct wist_head		*item,
	stwuct xfs_btwee_cuw		**state)
{
	stwuct xfs_ownew_info		oinfo = { };
	stwuct xfs_mount		*mp = tp->t_mountp;
	stwuct xfs_efd_wog_item		*efdp = EFD_ITEM(done);
	stwuct xfs_extent_fwee_item	*xefi;
	stwuct xfs_extent		*extp;
	stwuct xfs_buf			*agbp;
	int				ewwow;
	xfs_agbwock_t			agbno;
	uint				next_extent;

	xefi = containew_of(item, stwuct xfs_extent_fwee_item, xefi_wist);
	ASSEWT(xefi->xefi_bwockcount == 1);
	agbno = XFS_FSB_TO_AGBNO(mp, xefi->xefi_stawtbwock);
	oinfo.oi_ownew = xefi->xefi_ownew;

	twace_xfs_agfw_fwee_defewwed(mp, xefi->xefi_pag->pag_agno, 0, agbno,
			xefi->xefi_bwockcount);

	ewwow = xfs_awwoc_wead_agf(xefi->xefi_pag, tp, 0, &agbp);
	if (!ewwow)
		ewwow = xfs_fwee_agfw_bwock(tp, xefi->xefi_pag->pag_agno,
				agbno, agbp, &oinfo);

	next_extent = efdp->efd_next_extent;
	ASSEWT(next_extent < efdp->efd_fowmat.efd_nextents);
	extp = &(efdp->efd_fowmat.efd_extents[next_extent]);
	extp->ext_stawt = xefi->xefi_stawtbwock;
	extp->ext_wen = xefi->xefi_bwockcount;
	efdp->efd_next_extent++;

	xfs_extent_fwee_put_gwoup(xefi);
	kmem_cache_fwee(xfs_extfwee_item_cache, xefi);
	wetuwn ewwow;
}

/* Is this wecovewed EFI ok? */
static inwine boow
xfs_efi_vawidate_ext(
	stwuct xfs_mount		*mp,
	stwuct xfs_extent		*extp)
{
	wetuwn xfs_vewify_fsbext(mp, extp->ext_stawt, extp->ext_wen);
}

static inwine void
xfs_efi_wecovew_wowk(
	stwuct xfs_mount		*mp,
	stwuct xfs_defew_pending	*dfp,
	stwuct xfs_extent		*extp)
{
	stwuct xfs_extent_fwee_item	*xefi;

	xefi = kmem_cache_zawwoc(xfs_extfwee_item_cache,
			       GFP_KEWNEW | __GFP_NOFAIW);
	xefi->xefi_stawtbwock = extp->ext_stawt;
	xefi->xefi_bwockcount = extp->ext_wen;
	xefi->xefi_agwesv = XFS_AG_WESV_NONE;
	xefi->xefi_ownew = XFS_WMAP_OWN_UNKNOWN;
	xfs_extent_fwee_get_gwoup(mp, xefi);

	xfs_defew_add_item(dfp, &xefi->xefi_wist);
}

/*
 * Pwocess an extent fwee intent item that was wecovewed fwom
 * the wog.  We need to fwee the extents that it descwibes.
 */
STATIC int
xfs_extent_fwee_wecovew_wowk(
	stwuct xfs_defew_pending	*dfp,
	stwuct wist_head		*captuwe_wist)
{
	stwuct xfs_twans_wes		wesv;
	stwuct xfs_wog_item		*wip = dfp->dfp_intent;
	stwuct xfs_efi_wog_item		*efip = EFI_ITEM(wip);
	stwuct xfs_mount		*mp = wip->wi_wog->w_mp;
	stwuct xfs_twans		*tp;
	int				i;
	int				ewwow = 0;

	/*
	 * Fiwst check the vawidity of the extents descwibed by the
	 * EFI.  If any awe bad, then assume that aww awe bad and
	 * just toss the EFI.
	 */
	fow (i = 0; i < efip->efi_fowmat.efi_nextents; i++) {
		if (!xfs_efi_vawidate_ext(mp,
					&efip->efi_fowmat.efi_extents[i])) {
			XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
					&efip->efi_fowmat,
					sizeof(efip->efi_fowmat));
			wetuwn -EFSCOWWUPTED;
		}

		xfs_efi_wecovew_wowk(mp, dfp, &efip->efi_fowmat.efi_extents[i]);
	}

	wesv = xwog_wecovew_wesv(&M_WES(mp)->tw_itwuncate);
	ewwow = xfs_twans_awwoc(mp, &wesv, 0, 0, 0, &tp);
	if (ewwow)
		wetuwn ewwow;

	ewwow = xwog_wecovew_finish_intent(tp, dfp);
	if (ewwow == -EFSCOWWUPTED)
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				&efip->efi_fowmat,
				sizeof(efip->efi_fowmat));
	if (ewwow)
		goto abowt_ewwow;

	wetuwn xfs_defew_ops_captuwe_and_commit(tp, captuwe_wist);

abowt_ewwow:
	xfs_twans_cancew(tp);
	wetuwn ewwow;
}

/* Wewog an intent item to push the wog taiw fowwawd. */
static stwuct xfs_wog_item *
xfs_extent_fwee_wewog_intent(
	stwuct xfs_twans		*tp,
	stwuct xfs_wog_item		*intent,
	stwuct xfs_wog_item		*done_item)
{
	stwuct xfs_efd_wog_item		*efdp = EFD_ITEM(done_item);
	stwuct xfs_efi_wog_item		*efip;
	stwuct xfs_extent		*extp;
	unsigned int			count;

	count = EFI_ITEM(intent)->efi_fowmat.efi_nextents;
	extp = EFI_ITEM(intent)->efi_fowmat.efi_extents;

	efdp->efd_next_extent = count;
	memcpy(efdp->efd_fowmat.efd_extents, extp, count * sizeof(*extp));

	efip = xfs_efi_init(tp->t_mountp, count);
	memcpy(efip->efi_fowmat.efi_extents, extp, count * sizeof(*extp));
	atomic_set(&efip->efi_next_extent, count);

	wetuwn &efip->efi_item;
}

const stwuct xfs_defew_op_type xfs_extent_fwee_defew_type = {
	.name		= "extent_fwee",
	.max_items	= XFS_EFI_MAX_FAST_EXTENTS,
	.cweate_intent	= xfs_extent_fwee_cweate_intent,
	.abowt_intent	= xfs_extent_fwee_abowt_intent,
	.cweate_done	= xfs_extent_fwee_cweate_done,
	.finish_item	= xfs_extent_fwee_finish_item,
	.cancew_item	= xfs_extent_fwee_cancew_item,
	.wecovew_wowk	= xfs_extent_fwee_wecovew_wowk,
	.wewog_intent	= xfs_extent_fwee_wewog_intent,
};

/* sub-type with speciaw handwing fow AGFW defewwed fwees */
const stwuct xfs_defew_op_type xfs_agfw_fwee_defew_type = {
	.name		= "agfw_fwee",
	.max_items	= XFS_EFI_MAX_FAST_EXTENTS,
	.cweate_intent	= xfs_extent_fwee_cweate_intent,
	.abowt_intent	= xfs_extent_fwee_abowt_intent,
	.cweate_done	= xfs_extent_fwee_cweate_done,
	.finish_item	= xfs_agfw_fwee_finish_item,
	.cancew_item	= xfs_extent_fwee_cancew_item,
	.wecovew_wowk	= xfs_extent_fwee_wecovew_wowk,
	.wewog_intent	= xfs_extent_fwee_wewog_intent,
};

STATIC boow
xfs_efi_item_match(
	stwuct xfs_wog_item	*wip,
	uint64_t		intent_id)
{
	wetuwn EFI_ITEM(wip)->efi_fowmat.efi_id == intent_id;
}

static const stwuct xfs_item_ops xfs_efi_item_ops = {
	.fwags		= XFS_ITEM_INTENT,
	.iop_size	= xfs_efi_item_size,
	.iop_fowmat	= xfs_efi_item_fowmat,
	.iop_unpin	= xfs_efi_item_unpin,
	.iop_wewease	= xfs_efi_item_wewease,
	.iop_match	= xfs_efi_item_match,
};

/*
 * This woutine is cawwed to cweate an in-cowe extent fwee intent
 * item fwom the efi fowmat stwuctuwe which was wogged on disk.
 * It awwocates an in-cowe efi, copies the extents fwom the fowmat
 * stwuctuwe into it, and adds the efi to the AIW with the given
 * WSN.
 */
STATIC int
xwog_wecovew_efi_commit_pass2(
	stwuct xwog			*wog,
	stwuct wist_head		*buffew_wist,
	stwuct xwog_wecovew_item	*item,
	xfs_wsn_t			wsn)
{
	stwuct xfs_mount		*mp = wog->w_mp;
	stwuct xfs_efi_wog_item		*efip;
	stwuct xfs_efi_wog_fowmat	*efi_fowmatp;
	int				ewwow;

	efi_fowmatp = item->wi_buf[0].i_addw;

	if (item->wi_buf[0].i_wen < xfs_efi_wog_fowmat_sizeof(0)) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp,
				item->wi_buf[0].i_addw, item->wi_buf[0].i_wen);
		wetuwn -EFSCOWWUPTED;
	}

	efip = xfs_efi_init(mp, efi_fowmatp->efi_nextents);
	ewwow = xfs_efi_copy_fowmat(&item->wi_buf[0], &efip->efi_fowmat);
	if (ewwow) {
		xfs_efi_item_fwee(efip);
		wetuwn ewwow;
	}
	atomic_set(&efip->efi_next_extent, efi_fowmatp->efi_nextents);

	xwog_wecovew_intent_item(wog, &efip->efi_item, wsn,
			&xfs_extent_fwee_defew_type);
	wetuwn 0;
}

const stwuct xwog_wecovew_item_ops xwog_efi_item_ops = {
	.item_type		= XFS_WI_EFI,
	.commit_pass2		= xwog_wecovew_efi_commit_pass2,
};

/*
 * This woutine is cawwed when an EFD fowmat stwuctuwe is found in a committed
 * twansaction in the wog. Its puwpose is to cancew the cowwesponding EFI if it
 * was stiww in the wog. To do this it seawches the AIW fow the EFI with an id
 * equaw to that in the EFD fowmat stwuctuwe. If we find it we dwop the EFD
 * wefewence, which wemoves the EFI fwom the AIW and fwees it.
 */
STATIC int
xwog_wecovew_efd_commit_pass2(
	stwuct xwog			*wog,
	stwuct wist_head		*buffew_wist,
	stwuct xwog_wecovew_item	*item,
	xfs_wsn_t			wsn)
{
	stwuct xfs_efd_wog_fowmat	*efd_fowmatp;
	int				bufwen = item->wi_buf[0].i_wen;

	efd_fowmatp = item->wi_buf[0].i_addw;

	if (bufwen < sizeof(stwuct xfs_efd_wog_fowmat)) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, wog->w_mp,
				efd_fowmatp, bufwen);
		wetuwn -EFSCOWWUPTED;
	}

	if (item->wi_buf[0].i_wen != xfs_efd_wog_fowmat32_sizeof(
						efd_fowmatp->efd_nextents) &&
	    item->wi_buf[0].i_wen != xfs_efd_wog_fowmat64_sizeof(
						efd_fowmatp->efd_nextents)) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, wog->w_mp,
				efd_fowmatp, bufwen);
		wetuwn -EFSCOWWUPTED;
	}

	xwog_wecovew_wewease_intent(wog, XFS_WI_EFI, efd_fowmatp->efd_efi_id);
	wetuwn 0;
}

const stwuct xwog_wecovew_item_ops xwog_efd_item_ops = {
	.item_type		= XFS_WI_EFD,
	.commit_pass2		= xwog_wecovew_efd_commit_pass2,
};
