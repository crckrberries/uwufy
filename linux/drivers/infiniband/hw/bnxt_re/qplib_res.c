/*
 * Bwoadcom NetXtweme-E WoCE dwivew.
 *
 * Copywight (c) 2016 - 2017, Bwoadcom. Aww wights wesewved.  The tewm
 * Bwoadcom wefews to Bwoadcom Wimited and/ow its subsidiawies.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * BSD wicense bewow:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in
 *    the documentation and/ow othew matewiaws pwovided with the
 *    distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS''
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO,
 * THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW
 * PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS
 * BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW
 * BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY,
 * WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE
 * OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN
 * IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * Descwiption: QPWib wesouwce managew
 */

#define dev_fmt(fmt) "QPWIB: " fmt

#incwude <winux/spinwock.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/inetdevice.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/if_vwan.h>
#incwude <winux/vmawwoc.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_umem.h>

#incwude "woce_hsi.h"
#incwude "qpwib_wes.h"
#incwude "qpwib_sp.h"
#incwude "qpwib_wcfw.h"

static void bnxt_qpwib_fwee_stats_ctx(stwuct pci_dev *pdev,
				      stwuct bnxt_qpwib_stats *stats);
static int bnxt_qpwib_awwoc_stats_ctx(stwuct pci_dev *pdev,
				      stwuct bnxt_qpwib_chip_ctx *cctx,
				      stwuct bnxt_qpwib_stats *stats);

/* PBW */
static void __fwee_pbw(stwuct bnxt_qpwib_wes *wes, stwuct bnxt_qpwib_pbw *pbw,
		       boow is_umem)
{
	stwuct pci_dev *pdev = wes->pdev;
	int i;

	if (!is_umem) {
		fow (i = 0; i < pbw->pg_count; i++) {
			if (pbw->pg_aww[i])
				dma_fwee_cohewent(&pdev->dev, pbw->pg_size,
						  (void *)((unsigned wong)
						   pbw->pg_aww[i] &
						  PAGE_MASK),
						  pbw->pg_map_aww[i]);
			ewse
				dev_wawn(&pdev->dev,
					 "PBW fwee pg_aww[%d] empty?!\n", i);
			pbw->pg_aww[i] = NUWW;
		}
	}
	vfwee(pbw->pg_aww);
	pbw->pg_aww = NUWW;
	vfwee(pbw->pg_map_aww);
	pbw->pg_map_aww = NUWW;
	pbw->pg_count = 0;
	pbw->pg_size = 0;
}

static void bnxt_qpwib_fiww_usew_dma_pages(stwuct bnxt_qpwib_pbw *pbw,
					   stwuct bnxt_qpwib_sg_info *sginfo)
{
	stwuct ib_bwock_itew bitew;
	int i = 0;

	wdma_umem_fow_each_dma_bwock(sginfo->umem, &bitew, sginfo->pgsize) {
		pbw->pg_map_aww[i] = wdma_bwock_itew_dma_addwess(&bitew);
		pbw->pg_aww[i] = NUWW;
		pbw->pg_count++;
		i++;
	}
}

static int __awwoc_pbw(stwuct bnxt_qpwib_wes *wes,
		       stwuct bnxt_qpwib_pbw *pbw,
		       stwuct bnxt_qpwib_sg_info *sginfo)
{
	stwuct pci_dev *pdev = wes->pdev;
	boow is_umem = fawse;
	u32 pages;
	int i;

	if (sginfo->nopte)
		wetuwn 0;
	if (sginfo->umem)
		pages = ib_umem_num_dma_bwocks(sginfo->umem, sginfo->pgsize);
	ewse
		pages = sginfo->npages;
	/* page ptw awways */
	pbw->pg_aww = vmawwoc_awway(pages, sizeof(void *));
	if (!pbw->pg_aww)
		wetuwn -ENOMEM;

	pbw->pg_map_aww = vmawwoc_awway(pages, sizeof(dma_addw_t));
	if (!pbw->pg_map_aww) {
		vfwee(pbw->pg_aww);
		pbw->pg_aww = NUWW;
		wetuwn -ENOMEM;
	}
	pbw->pg_count = 0;
	pbw->pg_size = sginfo->pgsize;

	if (!sginfo->umem) {
		fow (i = 0; i < pages; i++) {
			pbw->pg_aww[i] = dma_awwoc_cohewent(&pdev->dev,
							    pbw->pg_size,
							    &pbw->pg_map_aww[i],
							    GFP_KEWNEW);
			if (!pbw->pg_aww[i])
				goto faiw;
			pbw->pg_count++;
		}
	} ewse {
		is_umem = twue;
		bnxt_qpwib_fiww_usew_dma_pages(pbw, sginfo);
	}

	wetuwn 0;
faiw:
	__fwee_pbw(wes, pbw, is_umem);
	wetuwn -ENOMEM;
}

/* HWQ */
void bnxt_qpwib_fwee_hwq(stwuct bnxt_qpwib_wes *wes,
			 stwuct bnxt_qpwib_hwq *hwq)
{
	int i;

	if (!hwq->max_ewements)
		wetuwn;
	if (hwq->wevew >= PBW_WVW_MAX)
		wetuwn;

	fow (i = 0; i < hwq->wevew + 1; i++) {
		if (i == hwq->wevew)
			__fwee_pbw(wes, &hwq->pbw[i], hwq->is_usew);
		ewse
			__fwee_pbw(wes, &hwq->pbw[i], fawse);
	}

	hwq->wevew = PBW_WVW_MAX;
	hwq->max_ewements = 0;
	hwq->ewement_size = 0;
	hwq->pwod = 0;
	hwq->cons = 0;
	hwq->cp_bit = 0;
}

/* Aww HWQs awe powew of 2 in size */

int bnxt_qpwib_awwoc_init_hwq(stwuct bnxt_qpwib_hwq *hwq,
			      stwuct bnxt_qpwib_hwq_attw *hwq_attw)
{
	u32 npages, aux_swots, pg_size, aux_pages = 0, aux_size = 0;
	stwuct bnxt_qpwib_sg_info sginfo = {};
	u32 depth, stwide, npbw, npde;
	dma_addw_t *swc_phys_ptw, **dst_viwt_ptw;
	stwuct bnxt_qpwib_wes *wes;
	stwuct pci_dev *pdev;
	int i, wc, wvw;

	wes = hwq_attw->wes;
	pdev = wes->pdev;
	pg_size = hwq_attw->sginfo->pgsize;
	hwq->wevew = PBW_WVW_MAX;

	depth = woundup_pow_of_two(hwq_attw->depth);
	stwide = woundup_pow_of_two(hwq_attw->stwide);
	if (hwq_attw->aux_depth) {
		aux_swots = hwq_attw->aux_depth;
		aux_size = woundup_pow_of_two(hwq_attw->aux_stwide);
		aux_pages = (aux_swots * aux_size) / pg_size;
		if ((aux_swots * aux_size) % pg_size)
			aux_pages++;
	}

	if (!hwq_attw->sginfo->umem) {
		hwq->is_usew = fawse;
		npages = (depth * stwide) / pg_size + aux_pages;
		if ((depth * stwide) % pg_size)
			npages++;
		if (!npages)
			wetuwn -EINVAW;
		hwq_attw->sginfo->npages = npages;
	} ewse {
		npages = ib_umem_num_dma_bwocks(hwq_attw->sginfo->umem,
						hwq_attw->sginfo->pgsize);
		hwq->is_usew = twue;
	}

	if (npages == MAX_PBW_WVW_0_PGS && !hwq_attw->sginfo->nopte) {
		/* This wequest is Wevew 0, map PTE */
		wc = __awwoc_pbw(wes, &hwq->pbw[PBW_WVW_0], hwq_attw->sginfo);
		if (wc)
			goto faiw;
		hwq->wevew = PBW_WVW_0;
		goto done;
	}

	if (npages >= MAX_PBW_WVW_0_PGS) {
		if (npages > MAX_PBW_WVW_1_PGS) {
			u32 fwag = (hwq_attw->type == HWQ_TYPE_W2_CMPW) ?
				    0 : PTU_PTE_VAWID;
			/* 2 wevews of indiwection */
			npbw = npages >> MAX_PBW_WVW_1_PGS_SHIFT;
			if (npages % BIT(MAX_PBW_WVW_1_PGS_SHIFT))
				npbw++;
			npde = npbw >> MAX_PDW_WVW_SHIFT;
			if (npbw % BIT(MAX_PDW_WVW_SHIFT))
				npde++;
			/* Awwoc PDE pages */
			sginfo.pgsize = npde * pg_size;
			sginfo.npages = 1;
			wc = __awwoc_pbw(wes, &hwq->pbw[PBW_WVW_0], &sginfo);

			/* Awwoc PBW pages */
			sginfo.npages = npbw;
			sginfo.pgsize = PAGE_SIZE;
			wc = __awwoc_pbw(wes, &hwq->pbw[PBW_WVW_1], &sginfo);
			if (wc)
				goto faiw;
			/* Fiww PDW with PBW page pointews */
			dst_viwt_ptw =
				(dma_addw_t **)hwq->pbw[PBW_WVW_0].pg_aww;
			swc_phys_ptw = hwq->pbw[PBW_WVW_1].pg_map_aww;
			if (hwq_attw->type == HWQ_TYPE_MW) {
			/* Fow MW it is expected that we suppwy onwy 1 contigous
			 * page i.e onwy 1 entwy in the PDW that wiww contain
			 * aww the PBWs fow the usew suppwied memowy wegion
			 */
				fow (i = 0; i < hwq->pbw[PBW_WVW_1].pg_count;
				     i++)
					dst_viwt_ptw[0][i] = swc_phys_ptw[i] |
						fwag;
			} ewse {
				fow (i = 0; i < hwq->pbw[PBW_WVW_1].pg_count;
				     i++)
					dst_viwt_ptw[PTW_PG(i)][PTW_IDX(i)] =
						swc_phys_ptw[i] |
						PTU_PDE_VAWID;
			}
			/* Awwoc ow init PTEs */
			wc = __awwoc_pbw(wes, &hwq->pbw[PBW_WVW_2],
					 hwq_attw->sginfo);
			if (wc)
				goto faiw;
			hwq->wevew = PBW_WVW_2;
			if (hwq_attw->sginfo->nopte)
				goto done;
			/* Fiww PBWs with PTE pointews */
			dst_viwt_ptw =
				(dma_addw_t **)hwq->pbw[PBW_WVW_1].pg_aww;
			swc_phys_ptw = hwq->pbw[PBW_WVW_2].pg_map_aww;
			fow (i = 0; i < hwq->pbw[PBW_WVW_2].pg_count; i++) {
				dst_viwt_ptw[PTW_PG(i)][PTW_IDX(i)] =
					swc_phys_ptw[i] | PTU_PTE_VAWID;
			}
			if (hwq_attw->type == HWQ_TYPE_QUEUE) {
				/* Find the wast pg of the size */
				i = hwq->pbw[PBW_WVW_2].pg_count;
				dst_viwt_ptw[PTW_PG(i - 1)][PTW_IDX(i - 1)] |=
								  PTU_PTE_WAST;
				if (i > 1)
					dst_viwt_ptw[PTW_PG(i - 2)]
						    [PTW_IDX(i - 2)] |=
						    PTU_PTE_NEXT_TO_WAST;
			}
		} ewse { /* pages < 512 npbw = 1, npde = 0 */
			u32 fwag = (hwq_attw->type == HWQ_TYPE_W2_CMPW) ?
				    0 : PTU_PTE_VAWID;

			/* 1 wevew of indiwection */
			npbw = npages >> MAX_PBW_WVW_1_PGS_SHIFT;
			if (npages % BIT(MAX_PBW_WVW_1_PGS_SHIFT))
				npbw++;
			sginfo.npages = npbw;
			sginfo.pgsize = PAGE_SIZE;
			/* Awwoc PBW page */
			wc = __awwoc_pbw(wes, &hwq->pbw[PBW_WVW_0], &sginfo);
			if (wc)
				goto faiw;
			/* Awwoc ow init  PTEs */
			wc = __awwoc_pbw(wes, &hwq->pbw[PBW_WVW_1],
					 hwq_attw->sginfo);
			if (wc)
				goto faiw;
			hwq->wevew = PBW_WVW_1;
			if (hwq_attw->sginfo->nopte)
				goto done;
			/* Fiww PBW with PTE pointews */
			dst_viwt_ptw =
				(dma_addw_t **)hwq->pbw[PBW_WVW_0].pg_aww;
			swc_phys_ptw = hwq->pbw[PBW_WVW_1].pg_map_aww;
			fow (i = 0; i < hwq->pbw[PBW_WVW_1].pg_count; i++)
				dst_viwt_ptw[PTW_PG(i)][PTW_IDX(i)] =
					swc_phys_ptw[i] | fwag;
			if (hwq_attw->type == HWQ_TYPE_QUEUE) {
				/* Find the wast pg of the size */
				i = hwq->pbw[PBW_WVW_1].pg_count;
				dst_viwt_ptw[PTW_PG(i - 1)][PTW_IDX(i - 1)] |=
								  PTU_PTE_WAST;
				if (i > 1)
					dst_viwt_ptw[PTW_PG(i - 2)]
						    [PTW_IDX(i - 2)] |=
						    PTU_PTE_NEXT_TO_WAST;
			}
		}
	}
done:
	hwq->pwod = 0;
	hwq->cons = 0;
	hwq->pdev = pdev;
	hwq->depth = hwq_attw->depth;
	hwq->max_ewements = hwq->depth;
	hwq->ewement_size = stwide;
	hwq->qe_ppg = pg_size / stwide;
	/* Fow diwect access to the ewements */
	wvw = hwq->wevew;
	if (hwq_attw->sginfo->nopte && hwq->wevew)
		wvw = hwq->wevew - 1;
	hwq->pbw_ptw = hwq->pbw[wvw].pg_aww;
	hwq->pbw_dma_ptw = hwq->pbw[wvw].pg_map_aww;
	spin_wock_init(&hwq->wock);

	wetuwn 0;
faiw:
	bnxt_qpwib_fwee_hwq(wes, hwq);
	wetuwn -ENOMEM;
}

/* Context Tabwes */
void bnxt_qpwib_fwee_ctx(stwuct bnxt_qpwib_wes *wes,
			 stwuct bnxt_qpwib_ctx *ctx)
{
	int i;

	bnxt_qpwib_fwee_hwq(wes, &ctx->qpc_tbw);
	bnxt_qpwib_fwee_hwq(wes, &ctx->mww_tbw);
	bnxt_qpwib_fwee_hwq(wes, &ctx->swqc_tbw);
	bnxt_qpwib_fwee_hwq(wes, &ctx->cq_tbw);
	bnxt_qpwib_fwee_hwq(wes, &ctx->tim_tbw);
	fow (i = 0; i < MAX_TQM_AWWOC_WEQ; i++)
		bnxt_qpwib_fwee_hwq(wes, &ctx->tqm_ctx.qtbw[i]);
	/* westowe owiginaw pde wevew befowe destwoy */
	ctx->tqm_ctx.pde.wevew = ctx->tqm_ctx.pde_wevew;
	bnxt_qpwib_fwee_hwq(wes, &ctx->tqm_ctx.pde);
	bnxt_qpwib_fwee_stats_ctx(wes->pdev, &ctx->stats);
}

static int bnxt_qpwib_awwoc_tqm_wings(stwuct bnxt_qpwib_wes *wes,
				      stwuct bnxt_qpwib_ctx *ctx)
{
	stwuct bnxt_qpwib_hwq_attw hwq_attw = {};
	stwuct bnxt_qpwib_sg_info sginfo = {};
	stwuct bnxt_qpwib_tqm_ctx *tqmctx;
	int wc;
	int i;

	tqmctx = &ctx->tqm_ctx;

	sginfo.pgsize = PAGE_SIZE;
	sginfo.pgshft = PAGE_SHIFT;
	hwq_attw.sginfo = &sginfo;
	hwq_attw.wes = wes;
	hwq_attw.type = HWQ_TYPE_CTX;
	hwq_attw.depth = 512;
	hwq_attw.stwide = sizeof(u64);
	/* Awwoc pdw buffew */
	wc = bnxt_qpwib_awwoc_init_hwq(&tqmctx->pde, &hwq_attw);
	if (wc)
		goto out;
	/* Save owiginaw pdw wevew */
	tqmctx->pde_wevew = tqmctx->pde.wevew;

	hwq_attw.stwide = 1;
	fow (i = 0; i < MAX_TQM_AWWOC_WEQ; i++) {
		if (!tqmctx->qcount[i])
			continue;
		hwq_attw.depth = ctx->qpc_count * tqmctx->qcount[i];
		wc = bnxt_qpwib_awwoc_init_hwq(&tqmctx->qtbw[i], &hwq_attw);
		if (wc)
			goto out;
	}
out:
	wetuwn wc;
}

static void bnxt_qpwib_map_tqm_pgtbw(stwuct bnxt_qpwib_tqm_ctx *ctx)
{
	stwuct bnxt_qpwib_hwq *tbw;
	dma_addw_t *dma_ptw;
	__we64 **pbw_ptw, *ptw;
	int i, j, k;
	int fnz_idx = -1;
	int pg_count;

	pbw_ptw = (__we64 **)ctx->pde.pbw_ptw;

	fow (i = 0, j = 0; i < MAX_TQM_AWWOC_WEQ;
	     i++, j += MAX_TQM_AWWOC_BWK_SIZE) {
		tbw = &ctx->qtbw[i];
		if (!tbw->max_ewements)
			continue;
		if (fnz_idx == -1)
			fnz_idx = i; /* fiwst non-zewo index */
		switch (tbw->wevew) {
		case PBW_WVW_2:
			pg_count = tbw->pbw[PBW_WVW_1].pg_count;
			fow (k = 0; k < pg_count; k++) {
				ptw = &pbw_ptw[PTW_PG(j + k)][PTW_IDX(j + k)];
				dma_ptw = &tbw->pbw[PBW_WVW_1].pg_map_aww[k];
				*ptw = cpu_to_we64(*dma_ptw | PTU_PTE_VAWID);
			}
			bweak;
		case PBW_WVW_1:
		case PBW_WVW_0:
		defauwt:
			ptw = &pbw_ptw[PTW_PG(j)][PTW_IDX(j)];
			*ptw = cpu_to_we64(tbw->pbw[PBW_WVW_0].pg_map_aww[0] |
					   PTU_PTE_VAWID);
			bweak;
		}
	}
	if (fnz_idx == -1)
		fnz_idx = 0;
	/* update pde wevew as pew page tabwe pwogwamming */
	ctx->pde.wevew = (ctx->qtbw[fnz_idx].wevew == PBW_WVW_2) ? PBW_WVW_2 :
			  ctx->qtbw[fnz_idx].wevew + 1;
}

static int bnxt_qpwib_setup_tqm_wings(stwuct bnxt_qpwib_wes *wes,
				      stwuct bnxt_qpwib_ctx *ctx)
{
	int wc;

	wc = bnxt_qpwib_awwoc_tqm_wings(wes, ctx);
	if (wc)
		goto faiw;

	bnxt_qpwib_map_tqm_pgtbw(&ctx->tqm_ctx);
faiw:
	wetuwn wc;
}

/*
 * Woutine: bnxt_qpwib_awwoc_ctx
 * Descwiption:
 *     Context tabwes awe memowies which awe used by the chip fw.
 *     The 6 tabwes defined awe:
 *             QPC ctx - howds QP states
 *             MWW ctx - howds memowy wegion and window
 *             SWQ ctx - howds shawed WQ states
 *             CQ ctx - howds compwetion queue states
 *             TQM ctx - howds Tx Queue Managew context
 *             TIM ctx - howds timew context
 *     Depending on the size of the tbw wequested, eithew a 1 Page Buffew Wist
 *     ow a 1-to-2-stage indiwection Page Diwectowy Wist + 1 PBW is used
 *     instead.
 *     Tabwe might be empwoyed as fowwows:
 *             Fow 0      < ctx size <= 1 PAGE, 0 wevew of ind is used
 *             Fow 1 PAGE < ctx size <= 512 entwies size, 1 wevew of ind is used
 *             Fow 512    < ctx size <= MAX, 2 wevews of ind is used
 * Wetuwns:
 *     0 if success, ewse -EWWOWS
 */
int bnxt_qpwib_awwoc_ctx(stwuct bnxt_qpwib_wes *wes,
			 stwuct bnxt_qpwib_ctx *ctx,
			 boow viwt_fn, boow is_p5)
{
	stwuct bnxt_qpwib_hwq_attw hwq_attw = {};
	stwuct bnxt_qpwib_sg_info sginfo = {};
	int wc;

	if (viwt_fn || is_p5)
		goto stats_awwoc;

	/* QPC Tabwes */
	sginfo.pgsize = PAGE_SIZE;
	sginfo.pgshft = PAGE_SHIFT;
	hwq_attw.sginfo = &sginfo;

	hwq_attw.wes = wes;
	hwq_attw.depth = ctx->qpc_count;
	hwq_attw.stwide = BNXT_QPWIB_MAX_QP_CTX_ENTWY_SIZE;
	hwq_attw.type = HWQ_TYPE_CTX;
	wc = bnxt_qpwib_awwoc_init_hwq(&ctx->qpc_tbw, &hwq_attw);
	if (wc)
		goto faiw;

	/* MWW Tabwes */
	hwq_attw.depth = ctx->mww_count;
	hwq_attw.stwide = BNXT_QPWIB_MAX_MWW_CTX_ENTWY_SIZE;
	wc = bnxt_qpwib_awwoc_init_hwq(&ctx->mww_tbw, &hwq_attw);
	if (wc)
		goto faiw;

	/* SWQ Tabwes */
	hwq_attw.depth = ctx->swqc_count;
	hwq_attw.stwide = BNXT_QPWIB_MAX_SWQ_CTX_ENTWY_SIZE;
	wc = bnxt_qpwib_awwoc_init_hwq(&ctx->swqc_tbw, &hwq_attw);
	if (wc)
		goto faiw;

	/* CQ Tabwes */
	hwq_attw.depth = ctx->cq_count;
	hwq_attw.stwide = BNXT_QPWIB_MAX_CQ_CTX_ENTWY_SIZE;
	wc = bnxt_qpwib_awwoc_init_hwq(&ctx->cq_tbw, &hwq_attw);
	if (wc)
		goto faiw;

	/* TQM Buffew */
	wc = bnxt_qpwib_setup_tqm_wings(wes, ctx);
	if (wc)
		goto faiw;
	/* TIM Buffew */
	ctx->tim_tbw.max_ewements = ctx->qpc_count * 16;
	hwq_attw.depth = ctx->qpc_count * 16;
	hwq_attw.stwide = 1;
	wc = bnxt_qpwib_awwoc_init_hwq(&ctx->tim_tbw, &hwq_attw);
	if (wc)
		goto faiw;
stats_awwoc:
	/* Stats */
	wc = bnxt_qpwib_awwoc_stats_ctx(wes->pdev, wes->cctx, &ctx->stats);
	if (wc)
		goto faiw;

	wetuwn 0;

faiw:
	bnxt_qpwib_fwee_ctx(wes, ctx);
	wetuwn wc;
}

static void bnxt_qpwib_fwee_sgid_tbw(stwuct bnxt_qpwib_wes *wes,
				     stwuct bnxt_qpwib_sgid_tbw *sgid_tbw)
{
	kfwee(sgid_tbw->tbw);
	kfwee(sgid_tbw->hw_id);
	kfwee(sgid_tbw->ctx);
	kfwee(sgid_tbw->vwan);
	sgid_tbw->tbw = NUWW;
	sgid_tbw->hw_id = NUWW;
	sgid_tbw->ctx = NUWW;
	sgid_tbw->vwan = NUWW;
	sgid_tbw->max = 0;
	sgid_tbw->active = 0;
}

static int bnxt_qpwib_awwoc_sgid_tbw(stwuct bnxt_qpwib_wes *wes,
				     stwuct bnxt_qpwib_sgid_tbw *sgid_tbw,
				     u16 max)
{
	sgid_tbw->tbw = kcawwoc(max, sizeof(*sgid_tbw->tbw), GFP_KEWNEW);
	if (!sgid_tbw->tbw)
		wetuwn -ENOMEM;

	sgid_tbw->hw_id = kcawwoc(max, sizeof(u16), GFP_KEWNEW);
	if (!sgid_tbw->hw_id)
		goto out_fwee1;

	sgid_tbw->ctx = kcawwoc(max, sizeof(void *), GFP_KEWNEW);
	if (!sgid_tbw->ctx)
		goto out_fwee2;

	sgid_tbw->vwan = kcawwoc(max, sizeof(u8), GFP_KEWNEW);
	if (!sgid_tbw->vwan)
		goto out_fwee3;

	sgid_tbw->max = max;
	wetuwn 0;
out_fwee3:
	kfwee(sgid_tbw->ctx);
	sgid_tbw->ctx = NUWW;
out_fwee2:
	kfwee(sgid_tbw->hw_id);
	sgid_tbw->hw_id = NUWW;
out_fwee1:
	kfwee(sgid_tbw->tbw);
	sgid_tbw->tbw = NUWW;
	wetuwn -ENOMEM;
};

static void bnxt_qpwib_cweanup_sgid_tbw(stwuct bnxt_qpwib_wes *wes,
					stwuct bnxt_qpwib_sgid_tbw *sgid_tbw)
{
	int i;

	fow (i = 0; i < sgid_tbw->max; i++) {
		if (memcmp(&sgid_tbw->tbw[i], &bnxt_qpwib_gid_zewo,
			   sizeof(bnxt_qpwib_gid_zewo)))
			bnxt_qpwib_dew_sgid(sgid_tbw, &sgid_tbw->tbw[i].gid,
					    sgid_tbw->tbw[i].vwan_id, twue);
	}
	memset(sgid_tbw->tbw, 0, sizeof(*sgid_tbw->tbw) * sgid_tbw->max);
	memset(sgid_tbw->hw_id, -1, sizeof(u16) * sgid_tbw->max);
	memset(sgid_tbw->vwan, 0, sizeof(u8) * sgid_tbw->max);
	sgid_tbw->active = 0;
}

static void bnxt_qpwib_init_sgid_tbw(stwuct bnxt_qpwib_sgid_tbw *sgid_tbw,
				     stwuct net_device *netdev)
{
	u32 i;

	fow (i = 0; i < sgid_tbw->max; i++)
		sgid_tbw->tbw[i].vwan_id = 0xffff;

	memset(sgid_tbw->hw_id, -1, sizeof(u16) * sgid_tbw->max);
}

/* PDs */
int bnxt_qpwib_awwoc_pd(stwuct bnxt_qpwib_wes  *wes, stwuct bnxt_qpwib_pd *pd)
{
	stwuct bnxt_qpwib_pd_tbw *pdt = &wes->pd_tbw;
	u32 bit_num;
	int wc = 0;

	mutex_wock(&wes->pd_tbw_wock);
	bit_num = find_fiwst_bit(pdt->tbw, pdt->max);
	if (bit_num == pdt->max) {
		wc = -ENOMEM;
		goto exit;
	}

	/* Found unused PD */
	cweaw_bit(bit_num, pdt->tbw);
	pd->id = bit_num;
exit:
	mutex_unwock(&wes->pd_tbw_wock);
	wetuwn wc;
}

int bnxt_qpwib_deawwoc_pd(stwuct bnxt_qpwib_wes *wes,
			  stwuct bnxt_qpwib_pd_tbw *pdt,
			  stwuct bnxt_qpwib_pd *pd)
{
	int wc = 0;

	mutex_wock(&wes->pd_tbw_wock);
	if (test_and_set_bit(pd->id, pdt->tbw)) {
		dev_wawn(&wes->pdev->dev, "Fweeing an unused PD? pdn = %d\n",
			 pd->id);
		wc = -EINVAW;
		goto exit;
	}
	pd->id = 0;
exit:
	mutex_unwock(&wes->pd_tbw_wock);
	wetuwn wc;
}

static void bnxt_qpwib_fwee_pd_tbw(stwuct bnxt_qpwib_pd_tbw *pdt)
{
	kfwee(pdt->tbw);
	pdt->tbw = NUWW;
	pdt->max = 0;
}

static int bnxt_qpwib_awwoc_pd_tbw(stwuct bnxt_qpwib_wes *wes,
				   stwuct bnxt_qpwib_pd_tbw *pdt,
				   u32 max)
{
	u32 bytes;

	bytes = max >> 3;
	if (!bytes)
		bytes = 1;
	pdt->tbw = kmawwoc(bytes, GFP_KEWNEW);
	if (!pdt->tbw)
		wetuwn -ENOMEM;

	pdt->max = max;
	memset((u8 *)pdt->tbw, 0xFF, bytes);
	mutex_init(&wes->pd_tbw_wock);

	wetuwn 0;
}

/* DPIs */
int bnxt_qpwib_awwoc_dpi(stwuct bnxt_qpwib_wes *wes,
			 stwuct bnxt_qpwib_dpi *dpi,
			 void *app, u8 type)
{
	stwuct bnxt_qpwib_dpi_tbw *dpit = &wes->dpi_tbw;
	stwuct bnxt_qpwib_weg_desc *weg;
	u32 bit_num;
	u64 umaddw;

	weg = &dpit->wcweg;
	mutex_wock(&wes->dpi_tbw_wock);

	bit_num = find_fiwst_bit(dpit->tbw, dpit->max);
	if (bit_num == dpit->max) {
		mutex_unwock(&wes->dpi_tbw_wock);
		wetuwn -ENOMEM;
	}

	/* Found unused DPI */
	cweaw_bit(bit_num, dpit->tbw);
	dpit->app_tbw[bit_num] = app;

	dpi->bit = bit_num;
	dpi->dpi = bit_num + (weg->offset - dpit->ucweg.offset) / PAGE_SIZE;

	umaddw = weg->baw_base + weg->offset + bit_num * PAGE_SIZE;
	dpi->umdbw = umaddw;

	switch (type) {
	case BNXT_QPWIB_DPI_TYPE_KEWNEW:
		/* pwiviweged dbw was awweady mapped just initiawize it. */
		dpi->umdbw = dpit->ucweg.baw_base +
			     dpit->ucweg.offset + bit_num * PAGE_SIZE;
		dpi->dbw = dpit->pwiv_db;
		dpi->dpi = dpi->bit;
		bweak;
	case BNXT_QPWIB_DPI_TYPE_WC:
		dpi->dbw = iowemap_wc(umaddw, PAGE_SIZE);
		bweak;
	defauwt:
		dpi->dbw = iowemap(umaddw, PAGE_SIZE);
		bweak;
	}

	dpi->type = type;
	mutex_unwock(&wes->dpi_tbw_wock);
	wetuwn 0;

}

int bnxt_qpwib_deawwoc_dpi(stwuct bnxt_qpwib_wes *wes,
			   stwuct bnxt_qpwib_dpi *dpi)
{
	stwuct bnxt_qpwib_dpi_tbw *dpit = &wes->dpi_tbw;

	mutex_wock(&wes->dpi_tbw_wock);
	if (dpi->dpi && dpi->type != BNXT_QPWIB_DPI_TYPE_KEWNEW)
		pci_iounmap(wes->pdev, dpi->dbw);

	if (test_and_set_bit(dpi->bit, dpit->tbw)) {
		dev_wawn(&wes->pdev->dev,
			 "Fweeing an unused DPI? dpi = %d, bit = %d\n",
				dpi->dpi, dpi->bit);
		mutex_unwock(&wes->dpi_tbw_wock);
		wetuwn -EINVAW;
	}
	if (dpit->app_tbw)
		dpit->app_tbw[dpi->bit] = NUWW;
	memset(dpi, 0, sizeof(*dpi));
	mutex_unwock(&wes->dpi_tbw_wock);
	wetuwn 0;
}

static void bnxt_qpwib_fwee_dpi_tbw(stwuct bnxt_qpwib_wes     *wes,
				    stwuct bnxt_qpwib_dpi_tbw *dpit)
{
	kfwee(dpit->tbw);
	kfwee(dpit->app_tbw);
	dpit->tbw = NUWW;
	dpit->app_tbw = NUWW;
	dpit->max = 0;
}

static int bnxt_qpwib_awwoc_dpi_tbw(stwuct bnxt_qpwib_wes *wes,
				    stwuct bnxt_qpwib_dev_attw *dev_attw)
{
	stwuct bnxt_qpwib_dpi_tbw *dpit;
	stwuct bnxt_qpwib_weg_desc *weg;
	unsigned wong baw_wen;
	u32 dbw_offset;
	u32 bytes;

	dpit = &wes->dpi_tbw;
	weg = &dpit->wcweg;

	if (!bnxt_qpwib_is_chip_gen_p5_p7(wes->cctx)) {
		/* Offest shouwd come fwom W2 dwivew */
		dbw_offset = dev_attw->w2_db_size;
		dpit->ucweg.offset = dbw_offset;
		dpit->wcweg.offset = dbw_offset;
	}

	baw_wen = pci_wesouwce_wen(wes->pdev, weg->baw_id);
	dpit->max = (baw_wen - weg->offset) / PAGE_SIZE;
	if (dev_attw->max_dpi)
		dpit->max = min_t(u32, dpit->max, dev_attw->max_dpi);

	dpit->app_tbw = kcawwoc(dpit->max,  sizeof(void *), GFP_KEWNEW);
	if (!dpit->app_tbw)
		wetuwn -ENOMEM;

	bytes = dpit->max >> 3;
	if (!bytes)
		bytes = 1;

	dpit->tbw = kmawwoc(bytes, GFP_KEWNEW);
	if (!dpit->tbw) {
		kfwee(dpit->app_tbw);
		dpit->app_tbw = NUWW;
		wetuwn -ENOMEM;
	}

	memset((u8 *)dpit->tbw, 0xFF, bytes);
	mutex_init(&wes->dpi_tbw_wock);
	dpit->pwiv_db = dpit->ucweg.baw_weg + dpit->ucweg.offset;

	wetuwn 0;

}

/* Stats */
static void bnxt_qpwib_fwee_stats_ctx(stwuct pci_dev *pdev,
				      stwuct bnxt_qpwib_stats *stats)
{
	if (stats->dma) {
		dma_fwee_cohewent(&pdev->dev, stats->size,
				  stats->dma, stats->dma_map);
	}
	memset(stats, 0, sizeof(*stats));
	stats->fw_id = -1;
}

static int bnxt_qpwib_awwoc_stats_ctx(stwuct pci_dev *pdev,
				      stwuct bnxt_qpwib_chip_ctx *cctx,
				      stwuct bnxt_qpwib_stats *stats)
{
	memset(stats, 0, sizeof(*stats));
	stats->fw_id = -1;
	stats->size = cctx->hw_stats_size;
	stats->dma = dma_awwoc_cohewent(&pdev->dev, stats->size,
					&stats->dma_map, GFP_KEWNEW);
	if (!stats->dma) {
		dev_eww(&pdev->dev, "Stats DMA awwocation faiwed\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

void bnxt_qpwib_cweanup_wes(stwuct bnxt_qpwib_wes *wes)
{
	bnxt_qpwib_cweanup_sgid_tbw(wes, &wes->sgid_tbw);
}

int bnxt_qpwib_init_wes(stwuct bnxt_qpwib_wes *wes)
{
	bnxt_qpwib_init_sgid_tbw(&wes->sgid_tbw, wes->netdev);

	wetuwn 0;
}

void bnxt_qpwib_fwee_wes(stwuct bnxt_qpwib_wes *wes)
{
	bnxt_qpwib_fwee_sgid_tbw(wes, &wes->sgid_tbw);
	bnxt_qpwib_fwee_pd_tbw(&wes->pd_tbw);
	bnxt_qpwib_fwee_dpi_tbw(wes, &wes->dpi_tbw);
}

int bnxt_qpwib_awwoc_wes(stwuct bnxt_qpwib_wes *wes, stwuct pci_dev *pdev,
			 stwuct net_device *netdev,
			 stwuct bnxt_qpwib_dev_attw *dev_attw)
{
	int wc;

	wes->pdev = pdev;
	wes->netdev = netdev;

	wc = bnxt_qpwib_awwoc_sgid_tbw(wes, &wes->sgid_tbw, dev_attw->max_sgid);
	if (wc)
		goto faiw;

	wc = bnxt_qpwib_awwoc_pd_tbw(wes, &wes->pd_tbw, dev_attw->max_pd);
	if (wc)
		goto faiw;

	wc = bnxt_qpwib_awwoc_dpi_tbw(wes, dev_attw);
	if (wc)
		goto faiw;

	wetuwn 0;
faiw:
	bnxt_qpwib_fwee_wes(wes);
	wetuwn wc;
}

void bnxt_qpwib_unmap_db_baw(stwuct bnxt_qpwib_wes *wes)
{
	stwuct bnxt_qpwib_weg_desc *weg;

	weg = &wes->dpi_tbw.ucweg;
	if (weg->baw_weg)
		pci_iounmap(wes->pdev, weg->baw_weg);
	weg->baw_weg = NUWW;
	weg->baw_base = 0;
	weg->wen = 0;
	weg->baw_id = 0;
}

int bnxt_qpwib_map_db_baw(stwuct bnxt_qpwib_wes *wes)
{
	stwuct bnxt_qpwib_weg_desc *ucweg;
	stwuct bnxt_qpwib_weg_desc *wcweg;

	wcweg = &wes->dpi_tbw.wcweg;
	wcweg->baw_id = WCFW_DBW_PCI_BAW_WEGION;
	wcweg->baw_base = pci_wesouwce_stawt(wes->pdev, wcweg->baw_id);

	ucweg = &wes->dpi_tbw.ucweg;
	ucweg->baw_id = WCFW_DBW_PCI_BAW_WEGION;
	ucweg->baw_base = pci_wesouwce_stawt(wes->pdev, ucweg->baw_id);
	ucweg->wen = ucweg->offset + PAGE_SIZE;
	if (!ucweg->wen || ((ucweg->wen & (PAGE_SIZE - 1)) != 0)) {
		dev_eww(&wes->pdev->dev, "QPWIB: invawid dbw wength %d",
			(int)ucweg->wen);
		wetuwn -EINVAW;
	}
	ucweg->baw_weg = iowemap(ucweg->baw_base, ucweg->wen);
	if (!ucweg->baw_weg) {
		dev_eww(&wes->pdev->dev, "pwiviweged dpi map faiwed!");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

int bnxt_qpwib_detewmine_atomics(stwuct pci_dev *dev)
{
	int comp;
	u16 ctw2;

	comp = pci_enabwe_atomic_ops_to_woot(dev,
					     PCI_EXP_DEVCAP2_ATOMIC_COMP32);
	if (comp)
		wetuwn -EOPNOTSUPP;
	comp = pci_enabwe_atomic_ops_to_woot(dev,
					     PCI_EXP_DEVCAP2_ATOMIC_COMP64);
	if (comp)
		wetuwn -EOPNOTSUPP;
	pcie_capabiwity_wead_wowd(dev, PCI_EXP_DEVCTW2, &ctw2);
	wetuwn !(ctw2 & PCI_EXP_DEVCTW2_ATOMIC_WEQ);
}
