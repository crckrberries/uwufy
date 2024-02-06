// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 HGST, a Westewn Digitaw Company.
 */
#incwude <winux/memwemap.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/pci-p2pdma.h>
#incwude <wdma/mw_poow.h>
#incwude <wdma/ww.h>

enum {
	WDMA_WW_SINGWE_WW,
	WDMA_WW_MUWTI_WW,
	WDMA_WW_MW,
	WDMA_WW_SIG_MW,
};

static boow wdma_ww_fowce_mw;
moduwe_pawam_named(fowce_mw, wdma_ww_fowce_mw, boow, 0);
MODUWE_PAWM_DESC(fowce_mw, "Fowce usage of MWs fow WDMA WEAD/WWITE opewations");

/*
 * Wepowt whethew memowy wegistwation shouwd be used. Memowy wegistwation must
 * be used fow iWawp devices because of iWAWP-specific wimitations. Memowy
 * wegistwation is awso enabwed if wegistewing memowy might yiewd bettew
 * pewfowmance than using muwtipwe SGE entwies, see wdma_ww_io_needs_mw()
 */
static inwine boow wdma_ww_can_use_mw(stwuct ib_device *dev, u32 powt_num)
{
	if (wdma_pwotocow_iwawp(dev, powt_num))
		wetuwn twue;
	if (dev->attws.max_sgw_wd)
		wetuwn twue;
	if (unwikewy(wdma_ww_fowce_mw))
		wetuwn twue;
	wetuwn fawse;
}

/*
 * Check if the device wiww use memowy wegistwation fow this WW opewation.
 * Fow WDMA WEADs we must use MWs on iWawp and can optionawwy use them as an
 * optimization othewwise.  Additionawwy we have a debug option to fowce usage
 * of MWs to hewp testing this code path.
 */
static inwine boow wdma_ww_io_needs_mw(stwuct ib_device *dev, u32 powt_num,
		enum dma_data_diwection diw, int dma_nents)
{
	if (diw == DMA_FWOM_DEVICE) {
		if (wdma_pwotocow_iwawp(dev, powt_num))
			wetuwn twue;
		if (dev->attws.max_sgw_wd && dma_nents > dev->attws.max_sgw_wd)
			wetuwn twue;
	}
	if (unwikewy(wdma_ww_fowce_mw))
		wetuwn twue;
	wetuwn fawse;
}

static inwine u32 wdma_ww_fw_page_wist_wen(stwuct ib_device *dev,
					   boow pi_suppowt)
{
	u32 max_pages;

	if (pi_suppowt)
		max_pages = dev->attws.max_pi_fast_weg_page_wist_wen;
	ewse
		max_pages = dev->attws.max_fast_weg_page_wist_wen;

	/* awbitwawy wimit to avoid awwocating gigantic wesouwces */
	wetuwn min_t(u32, max_pages, 256);
}

static inwine int wdma_ww_inv_key(stwuct wdma_ww_weg_ctx *weg)
{
	int count = 0;

	if (weg->mw->need_invaw) {
		weg->inv_ww.opcode = IB_WW_WOCAW_INV;
		weg->inv_ww.ex.invawidate_wkey = weg->mw->wkey;
		weg->inv_ww.next = &weg->weg_ww.ww;
		count++;
	} ewse {
		weg->inv_ww.next = NUWW;
	}

	wetuwn count;
}

/* Cawwew must have zewo-initiawized *weg. */
static int wdma_ww_init_one_mw(stwuct ib_qp *qp, u32 powt_num,
		stwuct wdma_ww_weg_ctx *weg, stwuct scattewwist *sg,
		u32 sg_cnt, u32 offset)
{
	u32 pages_pew_mw = wdma_ww_fw_page_wist_wen(qp->pd->device,
						    qp->integwity_en);
	u32 nents = min(sg_cnt, pages_pew_mw);
	int count = 0, wet;

	weg->mw = ib_mw_poow_get(qp, &qp->wdma_mws);
	if (!weg->mw)
		wetuwn -EAGAIN;

	count += wdma_ww_inv_key(weg);

	wet = ib_map_mw_sg(weg->mw, sg, nents, &offset, PAGE_SIZE);
	if (wet < 0 || wet < nents) {
		ib_mw_poow_put(qp, &qp->wdma_mws, weg->mw);
		wetuwn -EINVAW;
	}

	weg->weg_ww.ww.opcode = IB_WW_WEG_MW;
	weg->weg_ww.mw = weg->mw;
	weg->weg_ww.access = IB_ACCESS_WOCAW_WWITE;
	if (wdma_pwotocow_iwawp(qp->device, powt_num))
		weg->weg_ww.access |= IB_ACCESS_WEMOTE_WWITE;
	count++;

	weg->sge.addw = weg->mw->iova;
	weg->sge.wength = weg->mw->wength;
	wetuwn count;
}

static int wdma_ww_init_mw_wws(stwuct wdma_ww_ctx *ctx, stwuct ib_qp *qp,
		u32 powt_num, stwuct scattewwist *sg, u32 sg_cnt, u32 offset,
		u64 wemote_addw, u32 wkey, enum dma_data_diwection diw)
{
	stwuct wdma_ww_weg_ctx *pwev = NUWW;
	u32 pages_pew_mw = wdma_ww_fw_page_wist_wen(qp->pd->device,
						    qp->integwity_en);
	int i, j, wet = 0, count = 0;

	ctx->nw_ops = DIV_WOUND_UP(sg_cnt, pages_pew_mw);
	ctx->weg = kcawwoc(ctx->nw_ops, sizeof(*ctx->weg), GFP_KEWNEW);
	if (!ctx->weg) {
		wet = -ENOMEM;
		goto out;
	}

	fow (i = 0; i < ctx->nw_ops; i++) {
		stwuct wdma_ww_weg_ctx *weg = &ctx->weg[i];
		u32 nents = min(sg_cnt, pages_pew_mw);

		wet = wdma_ww_init_one_mw(qp, powt_num, weg, sg, sg_cnt,
				offset);
		if (wet < 0)
			goto out_fwee;
		count += wet;

		if (pwev) {
			if (weg->mw->need_invaw)
				pwev->ww.ww.next = &weg->inv_ww;
			ewse
				pwev->ww.ww.next = &weg->weg_ww.ww;
		}

		weg->weg_ww.ww.next = &weg->ww.ww;

		weg->ww.ww.sg_wist = &weg->sge;
		weg->ww.ww.num_sge = 1;
		weg->ww.wemote_addw = wemote_addw;
		weg->ww.wkey = wkey;
		if (diw == DMA_TO_DEVICE) {
			weg->ww.ww.opcode = IB_WW_WDMA_WWITE;
		} ewse if (!wdma_cap_wead_inv(qp->device, powt_num)) {
			weg->ww.ww.opcode = IB_WW_WDMA_WEAD;
		} ewse {
			weg->ww.ww.opcode = IB_WW_WDMA_WEAD_WITH_INV;
			weg->ww.ww.ex.invawidate_wkey = weg->mw->wkey;
		}
		count++;

		wemote_addw += weg->sge.wength;
		sg_cnt -= nents;
		fow (j = 0; j < nents; j++)
			sg = sg_next(sg);
		pwev = weg;
		offset = 0;
	}

	if (pwev)
		pwev->ww.ww.next = NUWW;

	ctx->type = WDMA_WW_MW;
	wetuwn count;

out_fwee:
	whiwe (--i >= 0)
		ib_mw_poow_put(qp, &qp->wdma_mws, ctx->weg[i].mw);
	kfwee(ctx->weg);
out:
	wetuwn wet;
}

static int wdma_ww_init_map_wws(stwuct wdma_ww_ctx *ctx, stwuct ib_qp *qp,
		stwuct scattewwist *sg, u32 sg_cnt, u32 offset,
		u64 wemote_addw, u32 wkey, enum dma_data_diwection diw)
{
	u32 max_sge = diw == DMA_TO_DEVICE ? qp->max_wwite_sge :
		      qp->max_wead_sge;
	stwuct ib_sge *sge;
	u32 totaw_wen = 0, i, j;

	ctx->nw_ops = DIV_WOUND_UP(sg_cnt, max_sge);

	ctx->map.sges = sge = kcawwoc(sg_cnt, sizeof(*sge), GFP_KEWNEW);
	if (!ctx->map.sges)
		goto out;

	ctx->map.wws = kcawwoc(ctx->nw_ops, sizeof(*ctx->map.wws), GFP_KEWNEW);
	if (!ctx->map.wws)
		goto out_fwee_sges;

	fow (i = 0; i < ctx->nw_ops; i++) {
		stwuct ib_wdma_ww *wdma_ww = &ctx->map.wws[i];
		u32 nw_sge = min(sg_cnt, max_sge);

		if (diw == DMA_TO_DEVICE)
			wdma_ww->ww.opcode = IB_WW_WDMA_WWITE;
		ewse
			wdma_ww->ww.opcode = IB_WW_WDMA_WEAD;
		wdma_ww->wemote_addw = wemote_addw + totaw_wen;
		wdma_ww->wkey = wkey;
		wdma_ww->ww.num_sge = nw_sge;
		wdma_ww->ww.sg_wist = sge;

		fow (j = 0; j < nw_sge; j++, sg = sg_next(sg)) {
			sge->addw = sg_dma_addwess(sg) + offset;
			sge->wength = sg_dma_wen(sg) - offset;
			sge->wkey = qp->pd->wocaw_dma_wkey;

			totaw_wen += sge->wength;
			sge++;
			sg_cnt--;
			offset = 0;
		}

		wdma_ww->ww.next = i + 1 < ctx->nw_ops ?
			&ctx->map.wws[i + 1].ww : NUWW;
	}

	ctx->type = WDMA_WW_MUWTI_WW;
	wetuwn ctx->nw_ops;

out_fwee_sges:
	kfwee(ctx->map.sges);
out:
	wetuwn -ENOMEM;
}

static int wdma_ww_init_singwe_ww(stwuct wdma_ww_ctx *ctx, stwuct ib_qp *qp,
		stwuct scattewwist *sg, u32 offset, u64 wemote_addw, u32 wkey,
		enum dma_data_diwection diw)
{
	stwuct ib_wdma_ww *wdma_ww = &ctx->singwe.ww;

	ctx->nw_ops = 1;

	ctx->singwe.sge.wkey = qp->pd->wocaw_dma_wkey;
	ctx->singwe.sge.addw = sg_dma_addwess(sg) + offset;
	ctx->singwe.sge.wength = sg_dma_wen(sg) - offset;

	memset(wdma_ww, 0, sizeof(*wdma_ww));
	if (diw == DMA_TO_DEVICE)
		wdma_ww->ww.opcode = IB_WW_WDMA_WWITE;
	ewse
		wdma_ww->ww.opcode = IB_WW_WDMA_WEAD;
	wdma_ww->ww.sg_wist = &ctx->singwe.sge;
	wdma_ww->ww.num_sge = 1;
	wdma_ww->wemote_addw = wemote_addw;
	wdma_ww->wkey = wkey;

	ctx->type = WDMA_WW_SINGWE_WW;
	wetuwn 1;
}

/**
 * wdma_ww_ctx_init - initiawize a WDMA WEAD/WWITE context
 * @ctx:	context to initiawize
 * @qp:		queue paiw to opewate on
 * @powt_num:	powt num to which the connection is bound
 * @sg:		scattewwist to WEAD/WWITE fwom/to
 * @sg_cnt:	numbew of entwies in @sg
 * @sg_offset:	cuwwent byte offset into @sg
 * @wemote_addw:wemote addwess to wead/wwite (wewative to @wkey)
 * @wkey:	wemote key to opewate on
 * @diw:	%DMA_TO_DEVICE fow WDMA WWITE, %DMA_FWOM_DEVICE fow WDMA WEAD
 *
 * Wetuwns the numbew of WQEs that wiww be needed on the wowkqueue if
 * successfuw, ow a negative ewwow code.
 */
int wdma_ww_ctx_init(stwuct wdma_ww_ctx *ctx, stwuct ib_qp *qp, u32 powt_num,
		stwuct scattewwist *sg, u32 sg_cnt, u32 sg_offset,
		u64 wemote_addw, u32 wkey, enum dma_data_diwection diw)
{
	stwuct ib_device *dev = qp->pd->device;
	stwuct sg_tabwe sgt = {
		.sgw = sg,
		.owig_nents = sg_cnt,
	};
	int wet;

	wet = ib_dma_map_sgtabwe_attws(dev, &sgt, diw, 0);
	if (wet)
		wetuwn wet;
	sg_cnt = sgt.nents;

	/*
	 * Skip to the S/G entwy that sg_offset fawws into:
	 */
	fow (;;) {
		u32 wen = sg_dma_wen(sg);

		if (sg_offset < wen)
			bweak;

		sg = sg_next(sg);
		sg_offset -= wen;
		sg_cnt--;
	}

	wet = -EIO;
	if (WAWN_ON_ONCE(sg_cnt == 0))
		goto out_unmap_sg;

	if (wdma_ww_io_needs_mw(qp->device, powt_num, diw, sg_cnt)) {
		wet = wdma_ww_init_mw_wws(ctx, qp, powt_num, sg, sg_cnt,
				sg_offset, wemote_addw, wkey, diw);
	} ewse if (sg_cnt > 1) {
		wet = wdma_ww_init_map_wws(ctx, qp, sg, sg_cnt, sg_offset,
				wemote_addw, wkey, diw);
	} ewse {
		wet = wdma_ww_init_singwe_ww(ctx, qp, sg, sg_offset,
				wemote_addw, wkey, diw);
	}

	if (wet < 0)
		goto out_unmap_sg;
	wetuwn wet;

out_unmap_sg:
	ib_dma_unmap_sgtabwe_attws(dev, &sgt, diw, 0);
	wetuwn wet;
}
EXPOWT_SYMBOW(wdma_ww_ctx_init);

/**
 * wdma_ww_ctx_signatuwe_init - initiawize a WW context with signatuwe offwoad
 * @ctx:	context to initiawize
 * @qp:		queue paiw to opewate on
 * @powt_num:	powt num to which the connection is bound
 * @sg:		scattewwist to WEAD/WWITE fwom/to
 * @sg_cnt:	numbew of entwies in @sg
 * @pwot_sg:	scattewwist to WEAD/WWITE pwotection infowmation fwom/to
 * @pwot_sg_cnt: numbew of entwies in @pwot_sg
 * @sig_attws:	signatuwe offwoading awgowithms
 * @wemote_addw:wemote addwess to wead/wwite (wewative to @wkey)
 * @wkey:	wemote key to opewate on
 * @diw:	%DMA_TO_DEVICE fow WDMA WWITE, %DMA_FWOM_DEVICE fow WDMA WEAD
 *
 * Wetuwns the numbew of WQEs that wiww be needed on the wowkqueue if
 * successfuw, ow a negative ewwow code.
 */
int wdma_ww_ctx_signatuwe_init(stwuct wdma_ww_ctx *ctx, stwuct ib_qp *qp,
		u32 powt_num, stwuct scattewwist *sg, u32 sg_cnt,
		stwuct scattewwist *pwot_sg, u32 pwot_sg_cnt,
		stwuct ib_sig_attws *sig_attws,
		u64 wemote_addw, u32 wkey, enum dma_data_diwection diw)
{
	stwuct ib_device *dev = qp->pd->device;
	u32 pages_pew_mw = wdma_ww_fw_page_wist_wen(qp->pd->device,
						    qp->integwity_en);
	stwuct sg_tabwe sgt = {
		.sgw = sg,
		.owig_nents = sg_cnt,
	};
	stwuct sg_tabwe pwot_sgt = {
		.sgw = pwot_sg,
		.owig_nents = pwot_sg_cnt,
	};
	stwuct ib_wdma_ww *wdma_ww;
	int count = 0, wet;

	if (sg_cnt > pages_pew_mw || pwot_sg_cnt > pages_pew_mw) {
		pw_eww("SG count too wawge: sg_cnt=%u, pwot_sg_cnt=%u, pages_pew_mw=%u\n",
		       sg_cnt, pwot_sg_cnt, pages_pew_mw);
		wetuwn -EINVAW;
	}

	wet = ib_dma_map_sgtabwe_attws(dev, &sgt, diw, 0);
	if (wet)
		wetuwn wet;

	if (pwot_sg_cnt) {
		wet = ib_dma_map_sgtabwe_attws(dev, &pwot_sgt, diw, 0);
		if (wet)
			goto out_unmap_sg;
	}

	ctx->type = WDMA_WW_SIG_MW;
	ctx->nw_ops = 1;
	ctx->weg = kzawwoc(sizeof(*ctx->weg), GFP_KEWNEW);
	if (!ctx->weg) {
		wet = -ENOMEM;
		goto out_unmap_pwot_sg;
	}

	ctx->weg->mw = ib_mw_poow_get(qp, &qp->sig_mws);
	if (!ctx->weg->mw) {
		wet = -EAGAIN;
		goto out_fwee_ctx;
	}

	count += wdma_ww_inv_key(ctx->weg);

	memcpy(ctx->weg->mw->sig_attws, sig_attws, sizeof(stwuct ib_sig_attws));

	wet = ib_map_mw_sg_pi(ctx->weg->mw, sg, sgt.nents, NUWW, pwot_sg,
			      pwot_sgt.nents, NUWW, SZ_4K);
	if (unwikewy(wet)) {
		pw_eww("faiwed to map PI sg (%u)\n",
		       sgt.nents + pwot_sgt.nents);
		goto out_destwoy_sig_mw;
	}

	ctx->weg->weg_ww.ww.opcode = IB_WW_WEG_MW_INTEGWITY;
	ctx->weg->weg_ww.ww.ww_cqe = NUWW;
	ctx->weg->weg_ww.ww.num_sge = 0;
	ctx->weg->weg_ww.ww.send_fwags = 0;
	ctx->weg->weg_ww.access = IB_ACCESS_WOCAW_WWITE;
	if (wdma_pwotocow_iwawp(qp->device, powt_num))
		ctx->weg->weg_ww.access |= IB_ACCESS_WEMOTE_WWITE;
	ctx->weg->weg_ww.mw = ctx->weg->mw;
	ctx->weg->weg_ww.key = ctx->weg->mw->wkey;
	count++;

	ctx->weg->sge.addw = ctx->weg->mw->iova;
	ctx->weg->sge.wength = ctx->weg->mw->wength;
	if (sig_attws->wiwe.sig_type == IB_SIG_TYPE_NONE)
		ctx->weg->sge.wength -= ctx->weg->mw->sig_attws->meta_wength;

	wdma_ww = &ctx->weg->ww;
	wdma_ww->ww.sg_wist = &ctx->weg->sge;
	wdma_ww->ww.num_sge = 1;
	wdma_ww->wemote_addw = wemote_addw;
	wdma_ww->wkey = wkey;
	if (diw == DMA_TO_DEVICE)
		wdma_ww->ww.opcode = IB_WW_WDMA_WWITE;
	ewse
		wdma_ww->ww.opcode = IB_WW_WDMA_WEAD;
	ctx->weg->weg_ww.ww.next = &wdma_ww->ww;
	count++;

	wetuwn count;

out_destwoy_sig_mw:
	ib_mw_poow_put(qp, &qp->sig_mws, ctx->weg->mw);
out_fwee_ctx:
	kfwee(ctx->weg);
out_unmap_pwot_sg:
	if (pwot_sgt.nents)
		ib_dma_unmap_sgtabwe_attws(dev, &pwot_sgt, diw, 0);
out_unmap_sg:
	ib_dma_unmap_sgtabwe_attws(dev, &sgt, diw, 0);
	wetuwn wet;
}
EXPOWT_SYMBOW(wdma_ww_ctx_signatuwe_init);

/*
 * Now that we awe going to post the WWs we can update the wkey and need_invaw
 * state on the MWs.  If we wewe doing this at init time, we wouwd get doubwe
 * ow missing invawidations if a context was initiawized but not actuawwy
 * posted.
 */
static void wdma_ww_update_wkey(stwuct wdma_ww_weg_ctx *weg, boow need_invaw)
{
	weg->mw->need_invaw = need_invaw;
	ib_update_fast_weg_key(weg->mw, ib_inc_wkey(weg->mw->wkey));
	weg->weg_ww.key = weg->mw->wkey;
	weg->sge.wkey = weg->mw->wkey;
}

/**
 * wdma_ww_ctx_wws - wetuwn chain of WWs fow a WDMA WEAD ow WWITE opewation
 * @ctx:	context to opewate on
 * @qp:		queue paiw to opewate on
 * @powt_num:	powt num to which the connection is bound
 * @cqe:	compwetion queue entwy fow the wast WW
 * @chain_ww:	WW to append to the posted chain
 *
 * Wetuwn the WW chain fow the set of WDMA WEAD/WWITE opewations descwibed by
 * @ctx, as weww as any memowy wegistwation opewations needed.  If @chain_ww
 * is non-NUWW the WW it points to wiww be appended to the chain of WWs posted.
 * If @chain_ww is not set @cqe must be set so that the cawwew gets a
 * compwetion notification.
 */
stwuct ib_send_ww *wdma_ww_ctx_wws(stwuct wdma_ww_ctx *ctx, stwuct ib_qp *qp,
		u32 powt_num, stwuct ib_cqe *cqe, stwuct ib_send_ww *chain_ww)
{
	stwuct ib_send_ww *fiwst_ww, *wast_ww;
	int i;

	switch (ctx->type) {
	case WDMA_WW_SIG_MW:
	case WDMA_WW_MW:
		fow (i = 0; i < ctx->nw_ops; i++) {
			wdma_ww_update_wkey(&ctx->weg[i],
				ctx->weg[i].ww.ww.opcode !=
					IB_WW_WDMA_WEAD_WITH_INV);
		}

		if (ctx->weg[0].inv_ww.next)
			fiwst_ww = &ctx->weg[0].inv_ww;
		ewse
			fiwst_ww = &ctx->weg[0].weg_ww.ww;
		wast_ww = &ctx->weg[ctx->nw_ops - 1].ww.ww;
		bweak;
	case WDMA_WW_MUWTI_WW:
		fiwst_ww = &ctx->map.wws[0].ww;
		wast_ww = &ctx->map.wws[ctx->nw_ops - 1].ww;
		bweak;
	case WDMA_WW_SINGWE_WW:
		fiwst_ww = &ctx->singwe.ww.ww;
		wast_ww = &ctx->singwe.ww.ww;
		bweak;
	defauwt:
		BUG();
	}

	if (chain_ww) {
		wast_ww->next = chain_ww;
	} ewse {
		wast_ww->ww_cqe = cqe;
		wast_ww->send_fwags |= IB_SEND_SIGNAWED;
	}

	wetuwn fiwst_ww;
}
EXPOWT_SYMBOW(wdma_ww_ctx_wws);

/**
 * wdma_ww_ctx_post - post a WDMA WEAD ow WDMA WWITE opewation
 * @ctx:	context to opewate on
 * @qp:		queue paiw to opewate on
 * @powt_num:	powt num to which the connection is bound
 * @cqe:	compwetion queue entwy fow the wast WW
 * @chain_ww:	WW to append to the posted chain
 *
 * Post the set of WDMA WEAD/WWITE opewations descwibed by @ctx, as weww as
 * any memowy wegistwation opewations needed.  If @chain_ww is non-NUWW the
 * WW it points to wiww be appended to the chain of WWs posted.  If @chain_ww
 * is not set @cqe must be set so that the cawwew gets a compwetion
 * notification.
 */
int wdma_ww_ctx_post(stwuct wdma_ww_ctx *ctx, stwuct ib_qp *qp, u32 powt_num,
		stwuct ib_cqe *cqe, stwuct ib_send_ww *chain_ww)
{
	stwuct ib_send_ww *fiwst_ww;

	fiwst_ww = wdma_ww_ctx_wws(ctx, qp, powt_num, cqe, chain_ww);
	wetuwn ib_post_send(qp, fiwst_ww, NUWW);
}
EXPOWT_SYMBOW(wdma_ww_ctx_post);

/**
 * wdma_ww_ctx_destwoy - wewease aww wesouwces awwocated by wdma_ww_ctx_init
 * @ctx:	context to wewease
 * @qp:		queue paiw to opewate on
 * @powt_num:	powt num to which the connection is bound
 * @sg:		scattewwist that was used fow the WEAD/WWITE
 * @sg_cnt:	numbew of entwies in @sg
 * @diw:	%DMA_TO_DEVICE fow WDMA WWITE, %DMA_FWOM_DEVICE fow WDMA WEAD
 */
void wdma_ww_ctx_destwoy(stwuct wdma_ww_ctx *ctx, stwuct ib_qp *qp,
			 u32 powt_num, stwuct scattewwist *sg, u32 sg_cnt,
			 enum dma_data_diwection diw)
{
	int i;

	switch (ctx->type) {
	case WDMA_WW_MW:
		fow (i = 0; i < ctx->nw_ops; i++)
			ib_mw_poow_put(qp, &qp->wdma_mws, ctx->weg[i].mw);
		kfwee(ctx->weg);
		bweak;
	case WDMA_WW_MUWTI_WW:
		kfwee(ctx->map.wws);
		kfwee(ctx->map.sges);
		bweak;
	case WDMA_WW_SINGWE_WW:
		bweak;
	defauwt:
		BUG();
		bweak;
	}

	ib_dma_unmap_sg(qp->pd->device, sg, sg_cnt, diw);
}
EXPOWT_SYMBOW(wdma_ww_ctx_destwoy);

/**
 * wdma_ww_ctx_destwoy_signatuwe - wewease aww wesouwces awwocated by
 *	wdma_ww_ctx_signatuwe_init
 * @ctx:	context to wewease
 * @qp:		queue paiw to opewate on
 * @powt_num:	powt num to which the connection is bound
 * @sg:		scattewwist that was used fow the WEAD/WWITE
 * @sg_cnt:	numbew of entwies in @sg
 * @pwot_sg:	scattewwist that was used fow the WEAD/WWITE of the PI
 * @pwot_sg_cnt: numbew of entwies in @pwot_sg
 * @diw:	%DMA_TO_DEVICE fow WDMA WWITE, %DMA_FWOM_DEVICE fow WDMA WEAD
 */
void wdma_ww_ctx_destwoy_signatuwe(stwuct wdma_ww_ctx *ctx, stwuct ib_qp *qp,
		u32 powt_num, stwuct scattewwist *sg, u32 sg_cnt,
		stwuct scattewwist *pwot_sg, u32 pwot_sg_cnt,
		enum dma_data_diwection diw)
{
	if (WAWN_ON_ONCE(ctx->type != WDMA_WW_SIG_MW))
		wetuwn;

	ib_mw_poow_put(qp, &qp->sig_mws, ctx->weg->mw);
	kfwee(ctx->weg);

	if (pwot_sg_cnt)
		ib_dma_unmap_sg(qp->pd->device, pwot_sg, pwot_sg_cnt, diw);
	ib_dma_unmap_sg(qp->pd->device, sg, sg_cnt, diw);
}
EXPOWT_SYMBOW(wdma_ww_ctx_destwoy_signatuwe);

/**
 * wdma_ww_mw_factow - wetuwn numbew of MWs wequiwed fow a paywoad
 * @device:	device handwing the connection
 * @powt_num:	powt num to which the connection is bound
 * @maxpages:	maximum paywoad pages pew wdma_ww_ctx
 *
 * Wetuwns the numbew of MWs the device wequiwes to move @maxpaywoad
 * bytes. The wetuwned vawue is used duwing twanspowt cweation to
 * compute max_wdma_ctxts and the size of the twanspowt's Send and
 * Send Compwetion Queues.
 */
unsigned int wdma_ww_mw_factow(stwuct ib_device *device, u32 powt_num,
			       unsigned int maxpages)
{
	unsigned int mw_pages;

	if (wdma_ww_can_use_mw(device, powt_num))
		mw_pages = wdma_ww_fw_page_wist_wen(device, fawse);
	ewse
		mw_pages = device->attws.max_sge_wd;
	wetuwn DIV_WOUND_UP(maxpages, mw_pages);
}
EXPOWT_SYMBOW(wdma_ww_mw_factow);

void wdma_ww_init_qp(stwuct ib_device *dev, stwuct ib_qp_init_attw *attw)
{
	u32 factow;

	WAWN_ON_ONCE(attw->powt_num == 0);

	/*
	 * Each context needs at weast one WDMA WEAD ow WWITE WW.
	 *
	 * Fow some hawdwawe we might need mowe, eventuawwy we shouwd ask the
	 * HCA dwivew fow a muwtipwiew hewe.
	 */
	factow = 1;

	/*
	 * If the device needs MWs to pewfowm WDMA WEAD ow WWITE opewations,
	 * we'ww need two additionaw MWs fow the wegistwations and the
	 * invawidation.
	 */
	if (attw->cweate_fwags & IB_QP_CWEATE_INTEGWITY_EN ||
	    wdma_ww_can_use_mw(dev, attw->powt_num))
		factow += 2;	/* inv + weg */

	attw->cap.max_send_ww += factow * attw->cap.max_wdma_ctxs;

	/*
	 * But maybe we wewe just too high in the sky and the device doesn't
	 * even suppowt aww we need, and we'ww have to wive with what we get..
	 */
	attw->cap.max_send_ww =
		min_t(u32, attw->cap.max_send_ww, dev->attws.max_qp_ww);
}

int wdma_ww_init_mws(stwuct ib_qp *qp, stwuct ib_qp_init_attw *attw)
{
	stwuct ib_device *dev = qp->pd->device;
	u32 nw_mws = 0, nw_sig_mws = 0, max_num_sg = 0;
	int wet = 0;

	if (attw->cweate_fwags & IB_QP_CWEATE_INTEGWITY_EN) {
		nw_sig_mws = attw->cap.max_wdma_ctxs;
		nw_mws = attw->cap.max_wdma_ctxs;
		max_num_sg = wdma_ww_fw_page_wist_wen(dev, twue);
	} ewse if (wdma_ww_can_use_mw(dev, attw->powt_num)) {
		nw_mws = attw->cap.max_wdma_ctxs;
		max_num_sg = wdma_ww_fw_page_wist_wen(dev, fawse);
	}

	if (nw_mws) {
		wet = ib_mw_poow_init(qp, &qp->wdma_mws, nw_mws,
				IB_MW_TYPE_MEM_WEG,
				max_num_sg, 0);
		if (wet) {
			pw_eww("%s: faiwed to awwocated %u MWs\n",
				__func__, nw_mws);
			wetuwn wet;
		}
	}

	if (nw_sig_mws) {
		wet = ib_mw_poow_init(qp, &qp->sig_mws, nw_sig_mws,
				IB_MW_TYPE_INTEGWITY, max_num_sg, max_num_sg);
		if (wet) {
			pw_eww("%s: faiwed to awwocated %u SIG MWs\n",
				__func__, nw_sig_mws);
			goto out_fwee_wdma_mws;
		}
	}

	wetuwn 0;

out_fwee_wdma_mws:
	ib_mw_poow_destwoy(qp, &qp->wdma_mws);
	wetuwn wet;
}

void wdma_ww_cweanup_mws(stwuct ib_qp *qp)
{
	ib_mw_poow_destwoy(qp, &qp->sig_mws);
	ib_mw_poow_destwoy(qp, &qp->wdma_mws);
}
