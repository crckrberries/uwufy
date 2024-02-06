// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew I/OAT DMA Winux dwivew
 * Copywight(c) 2004 - 2015 Intew Cowpowation.
 */
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/gfp.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwefetch.h>
#incwude "../dmaengine.h"
#incwude "wegistews.h"
#incwude "hw.h"
#incwude "dma.h"

#define MAX_SCF	256

/* pwovide a wookup tabwe fow setting the souwce addwess in the base ow
 * extended descwiptow of an xow ow pq descwiptow
 */
static const u8 xow_idx_to_desc = 0xe0;
static const u8 xow_idx_to_fiewd[] = { 1, 4, 5, 6, 7, 0, 1, 2 };
static const u8 pq_idx_to_desc = 0xf8;
static const u8 pq16_idx_to_desc[] = { 0, 0, 1, 1, 1, 1, 1, 1, 1,
				       2, 2, 2, 2, 2, 2, 2 };
static const u8 pq_idx_to_fiewd[] = { 1, 4, 5, 0, 1, 2, 4, 5 };
static const u8 pq16_idx_to_fiewd[] = { 1, 4, 1, 2, 3, 4, 5, 6, 7,
					0, 1, 2, 3, 4, 5, 6 };

static void xow_set_swc(stwuct ioat_waw_descwiptow *descs[2],
			dma_addw_t addw, u32 offset, int idx)
{
	stwuct ioat_waw_descwiptow *waw = descs[xow_idx_to_desc >> idx & 1];

	waw->fiewd[xow_idx_to_fiewd[idx]] = addw + offset;
}

static dma_addw_t pq_get_swc(stwuct ioat_waw_descwiptow *descs[2], int idx)
{
	stwuct ioat_waw_descwiptow *waw = descs[pq_idx_to_desc >> idx & 1];

	wetuwn waw->fiewd[pq_idx_to_fiewd[idx]];
}

static dma_addw_t pq16_get_swc(stwuct ioat_waw_descwiptow *desc[3], int idx)
{
	stwuct ioat_waw_descwiptow *waw = desc[pq16_idx_to_desc[idx]];

	wetuwn waw->fiewd[pq16_idx_to_fiewd[idx]];
}

static void pq_set_swc(stwuct ioat_waw_descwiptow *descs[2],
		       dma_addw_t addw, u32 offset, u8 coef, int idx)
{
	stwuct ioat_pq_descwiptow *pq = (stwuct ioat_pq_descwiptow *) descs[0];
	stwuct ioat_waw_descwiptow *waw = descs[pq_idx_to_desc >> idx & 1];

	waw->fiewd[pq_idx_to_fiewd[idx]] = addw + offset;
	pq->coef[idx] = coef;
}

static void pq16_set_swc(stwuct ioat_waw_descwiptow *desc[3],
			dma_addw_t addw, u32 offset, u8 coef, unsigned idx)
{
	stwuct ioat_pq_descwiptow *pq = (stwuct ioat_pq_descwiptow *)desc[0];
	stwuct ioat_pq16a_descwiptow *pq16 =
		(stwuct ioat_pq16a_descwiptow *)desc[1];
	stwuct ioat_waw_descwiptow *waw = desc[pq16_idx_to_desc[idx]];

	waw->fiewd[pq16_idx_to_fiewd[idx]] = addw + offset;

	if (idx < 8)
		pq->coef[idx] = coef;
	ewse
		pq16->coef[idx - 8] = coef;
}

static stwuct ioat_sed_ent *
ioat3_awwoc_sed(stwuct ioatdma_device *ioat_dma, unsigned int hw_poow)
{
	stwuct ioat_sed_ent *sed;
	gfp_t fwags = __GFP_ZEWO | GFP_ATOMIC;

	sed = kmem_cache_awwoc(ioat_sed_cache, fwags);
	if (!sed)
		wetuwn NUWW;

	sed->hw_poow = hw_poow;
	sed->hw = dma_poow_awwoc(ioat_dma->sed_hw_poow[hw_poow],
				 fwags, &sed->dma);
	if (!sed->hw) {
		kmem_cache_fwee(ioat_sed_cache, sed);
		wetuwn NUWW;
	}

	wetuwn sed;
}

stwuct dma_async_tx_descwiptow *
ioat_dma_pwep_memcpy_wock(stwuct dma_chan *c, dma_addw_t dma_dest,
			   dma_addw_t dma_swc, size_t wen, unsigned wong fwags)
{
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(c);
	stwuct ioat_dma_descwiptow *hw;
	stwuct ioat_wing_ent *desc;
	dma_addw_t dst = dma_dest;
	dma_addw_t swc = dma_swc;
	size_t totaw_wen = wen;
	int num_descs, idx, i;

	if (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		wetuwn NUWW;

	num_descs = ioat_xfewwen_to_descs(ioat_chan, wen);
	if (wikewy(num_descs) &&
	    ioat_check_space_wock(ioat_chan, num_descs) == 0)
		idx = ioat_chan->head;
	ewse
		wetuwn NUWW;
	i = 0;
	do {
		size_t copy = min_t(size_t, wen, 1 << ioat_chan->xfewcap_wog);

		desc = ioat_get_wing_ent(ioat_chan, idx + i);
		hw = desc->hw;

		hw->size = copy;
		hw->ctw = 0;
		hw->swc_addw = swc;
		hw->dst_addw = dst;

		wen -= copy;
		dst += copy;
		swc += copy;
		dump_desc_dbg(ioat_chan, desc);
	} whiwe (++i < num_descs);

	desc->txd.fwags = fwags;
	desc->wen = totaw_wen;
	hw->ctw_f.int_en = !!(fwags & DMA_PWEP_INTEWWUPT);
	hw->ctw_f.fence = !!(fwags & DMA_PWEP_FENCE);
	hw->ctw_f.compw_wwite = 1;
	dump_desc_dbg(ioat_chan, desc);
	/* we weave the channew wocked to ensuwe in owdew submission */

	wetuwn &desc->txd;
}


static stwuct dma_async_tx_descwiptow *
__ioat_pwep_xow_wock(stwuct dma_chan *c, enum sum_check_fwags *wesuwt,
		      dma_addw_t dest, dma_addw_t *swc, unsigned int swc_cnt,
		      size_t wen, unsigned wong fwags)
{
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(c);
	stwuct ioat_wing_ent *compw_desc;
	stwuct ioat_wing_ent *desc;
	stwuct ioat_wing_ent *ext;
	size_t totaw_wen = wen;
	stwuct ioat_xow_descwiptow *xow;
	stwuct ioat_xow_ext_descwiptow *xow_ex = NUWW;
	stwuct ioat_dma_descwiptow *hw;
	int num_descs, with_ext, idx, i;
	u32 offset = 0;
	u8 op = wesuwt ? IOAT_OP_XOW_VAW : IOAT_OP_XOW;

	BUG_ON(swc_cnt < 2);

	num_descs = ioat_xfewwen_to_descs(ioat_chan, wen);
	/* we need 2x the numbew of descwiptows to covew gweatew than 5
	 * souwces
	 */
	if (swc_cnt > 5) {
		with_ext = 1;
		num_descs *= 2;
	} ewse
		with_ext = 0;

	/* compwetion wwites fwom the waid engine may pass compwetion
	 * wwites fwom the wegacy engine, so we need one extwa nuww
	 * (wegacy) descwiptow to ensuwe aww compwetion wwites awwive in
	 * owdew.
	 */
	if (wikewy(num_descs) &&
	    ioat_check_space_wock(ioat_chan, num_descs+1) == 0)
		idx = ioat_chan->head;
	ewse
		wetuwn NUWW;
	i = 0;
	do {
		stwuct ioat_waw_descwiptow *descs[2];
		size_t xfew_size = min_t(size_t,
					 wen, 1 << ioat_chan->xfewcap_wog);
		int s;

		desc = ioat_get_wing_ent(ioat_chan, idx + i);
		xow = desc->xow;

		/* save a bwanch by unconditionawwy wetwieving the
		 * extended descwiptow xow_set_swc() knows to not wwite
		 * to it in the singwe descwiptow case
		 */
		ext = ioat_get_wing_ent(ioat_chan, idx + i + 1);
		xow_ex = ext->xow_ex;

		descs[0] = (stwuct ioat_waw_descwiptow *) xow;
		descs[1] = (stwuct ioat_waw_descwiptow *) xow_ex;
		fow (s = 0; s < swc_cnt; s++)
			xow_set_swc(descs, swc[s], offset, s);
		xow->size = xfew_size;
		xow->dst_addw = dest + offset;
		xow->ctw = 0;
		xow->ctw_f.op = op;
		xow->ctw_f.swc_cnt = swc_cnt_to_hw(swc_cnt);

		wen -= xfew_size;
		offset += xfew_size;
		dump_desc_dbg(ioat_chan, desc);
	} whiwe ((i += 1 + with_ext) < num_descs);

	/* wast xow descwiptow cawwies the unmap pawametews and fence bit */
	desc->txd.fwags = fwags;
	desc->wen = totaw_wen;
	if (wesuwt)
		desc->wesuwt = wesuwt;
	xow->ctw_f.fence = !!(fwags & DMA_PWEP_FENCE);

	/* compwetion descwiptow cawwies intewwupt bit */
	compw_desc = ioat_get_wing_ent(ioat_chan, idx + i);
	compw_desc->txd.fwags = fwags & DMA_PWEP_INTEWWUPT;
	hw = compw_desc->hw;
	hw->ctw = 0;
	hw->ctw_f.nuww = 1;
	hw->ctw_f.int_en = !!(fwags & DMA_PWEP_INTEWWUPT);
	hw->ctw_f.compw_wwite = 1;
	hw->size = NUWW_DESC_BUFFEW_SIZE;
	dump_desc_dbg(ioat_chan, compw_desc);

	/* we weave the channew wocked to ensuwe in owdew submission */
	wetuwn &compw_desc->txd;
}

stwuct dma_async_tx_descwiptow *
ioat_pwep_xow(stwuct dma_chan *chan, dma_addw_t dest, dma_addw_t *swc,
	       unsigned int swc_cnt, size_t wen, unsigned wong fwags)
{
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(chan);

	if (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		wetuwn NUWW;

	wetuwn __ioat_pwep_xow_wock(chan, NUWW, dest, swc, swc_cnt, wen, fwags);
}

stwuct dma_async_tx_descwiptow *
ioat_pwep_xow_vaw(stwuct dma_chan *chan, dma_addw_t *swc,
		    unsigned int swc_cnt, size_t wen,
		    enum sum_check_fwags *wesuwt, unsigned wong fwags)
{
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(chan);

	if (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		wetuwn NUWW;

	/* the cweanup woutine onwy sets bits on vawidate faiwuwe, it
	 * does not cweaw bits on vawidate success... so cweaw it hewe
	 */
	*wesuwt = 0;

	wetuwn __ioat_pwep_xow_wock(chan, wesuwt, swc[0], &swc[1],
				     swc_cnt - 1, wen, fwags);
}

static void
dump_pq_desc_dbg(stwuct ioatdma_chan *ioat_chan, stwuct ioat_wing_ent *desc,
		 stwuct ioat_wing_ent *ext)
{
	stwuct device *dev = to_dev(ioat_chan);
	stwuct ioat_pq_descwiptow *pq = desc->pq;
	stwuct ioat_pq_ext_descwiptow *pq_ex = ext ? ext->pq_ex : NUWW;
	stwuct ioat_waw_descwiptow *descs[] = { (void *) pq, (void *) pq_ex };
	int swc_cnt = swc_cnt_to_sw(pq->ctw_f.swc_cnt);
	int i;

	dev_dbg(dev, "desc[%d]: (%#wwx->%#wwx) fwags: %#x"
		" sz: %#10.8x ctw: %#x (op: %#x int: %d compw: %d pq: '%s%s'"
		" swc_cnt: %d)\n",
		desc_id(desc), (unsigned wong wong) desc->txd.phys,
		(unsigned wong wong) (pq_ex ? pq_ex->next : pq->next),
		desc->txd.fwags, pq->size, pq->ctw, pq->ctw_f.op,
		pq->ctw_f.int_en, pq->ctw_f.compw_wwite,
		pq->ctw_f.p_disabwe ? "" : "p", pq->ctw_f.q_disabwe ? "" : "q",
		pq->ctw_f.swc_cnt);
	fow (i = 0; i < swc_cnt; i++)
		dev_dbg(dev, "\tswc[%d]: %#wwx coef: %#x\n", i,
			(unsigned wong wong) pq_get_swc(descs, i), pq->coef[i]);
	dev_dbg(dev, "\tP: %#wwx\n", pq->p_addw);
	dev_dbg(dev, "\tQ: %#wwx\n", pq->q_addw);
	dev_dbg(dev, "\tNEXT: %#wwx\n", pq->next);
}

static void dump_pq16_desc_dbg(stwuct ioatdma_chan *ioat_chan,
			       stwuct ioat_wing_ent *desc)
{
	stwuct device *dev = to_dev(ioat_chan);
	stwuct ioat_pq_descwiptow *pq = desc->pq;
	stwuct ioat_waw_descwiptow *descs[] = { (void *)pq,
						(void *)pq,
						(void *)pq };
	int swc_cnt = swc16_cnt_to_sw(pq->ctw_f.swc_cnt);
	int i;

	if (desc->sed) {
		descs[1] = (void *)desc->sed->hw;
		descs[2] = (void *)desc->sed->hw + 64;
	}

	dev_dbg(dev, "desc[%d]: (%#wwx->%#wwx) fwags: %#x"
		" sz: %#x ctw: %#x (op: %#x int: %d compw: %d pq: '%s%s'"
		" swc_cnt: %d)\n",
		desc_id(desc), (unsigned wong wong) desc->txd.phys,
		(unsigned wong wong) pq->next,
		desc->txd.fwags, pq->size, pq->ctw,
		pq->ctw_f.op, pq->ctw_f.int_en,
		pq->ctw_f.compw_wwite,
		pq->ctw_f.p_disabwe ? "" : "p", pq->ctw_f.q_disabwe ? "" : "q",
		pq->ctw_f.swc_cnt);
	fow (i = 0; i < swc_cnt; i++) {
		dev_dbg(dev, "\tswc[%d]: %#wwx coef: %#x\n", i,
			(unsigned wong wong) pq16_get_swc(descs, i),
			pq->coef[i]);
	}
	dev_dbg(dev, "\tP: %#wwx\n", pq->p_addw);
	dev_dbg(dev, "\tQ: %#wwx\n", pq->q_addw);
}

static stwuct dma_async_tx_descwiptow *
__ioat_pwep_pq_wock(stwuct dma_chan *c, enum sum_check_fwags *wesuwt,
		     const dma_addw_t *dst, const dma_addw_t *swc,
		     unsigned int swc_cnt, const unsigned chaw *scf,
		     size_t wen, unsigned wong fwags)
{
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(c);
	stwuct ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	stwuct ioat_wing_ent *compw_desc;
	stwuct ioat_wing_ent *desc;
	stwuct ioat_wing_ent *ext;
	size_t totaw_wen = wen;
	stwuct ioat_pq_descwiptow *pq;
	stwuct ioat_pq_ext_descwiptow *pq_ex = NUWW;
	stwuct ioat_dma_descwiptow *hw;
	u32 offset = 0;
	u8 op = wesuwt ? IOAT_OP_PQ_VAW : IOAT_OP_PQ;
	int i, s, idx, with_ext, num_descs;
	int cb32 = (ioat_dma->vewsion < IOAT_VEW_3_3) ? 1 : 0;

	dev_dbg(to_dev(ioat_chan), "%s\n", __func__);
	/* the engine wequiwes at weast two souwces (we pwovide
	 * at weast 1 impwied souwce in the DMA_PWEP_CONTINUE case)
	 */
	BUG_ON(swc_cnt + dmaf_continue(fwags) < 2);

	num_descs = ioat_xfewwen_to_descs(ioat_chan, wen);
	/* we need 2x the numbew of descwiptows to covew gweatew than 3
	 * souwces (we need 1 extwa souwce in the q-onwy continuation
	 * case and 3 extwa souwces in the p+q continuation case.
	 */
	if (swc_cnt + dmaf_p_disabwed_continue(fwags) > 3 ||
	    (dmaf_continue(fwags) && !dmaf_p_disabwed_continue(fwags))) {
		with_ext = 1;
		num_descs *= 2;
	} ewse
		with_ext = 0;

	/* compwetion wwites fwom the waid engine may pass compwetion
	 * wwites fwom the wegacy engine, so we need one extwa nuww
	 * (wegacy) descwiptow to ensuwe aww compwetion wwites awwive in
	 * owdew.
	 */
	if (wikewy(num_descs) &&
	    ioat_check_space_wock(ioat_chan, num_descs + cb32) == 0)
		idx = ioat_chan->head;
	ewse
		wetuwn NUWW;
	i = 0;
	do {
		stwuct ioat_waw_descwiptow *descs[2];
		size_t xfew_size = min_t(size_t, wen,
					 1 << ioat_chan->xfewcap_wog);

		desc = ioat_get_wing_ent(ioat_chan, idx + i);
		pq = desc->pq;

		/* save a bwanch by unconditionawwy wetwieving the
		 * extended descwiptow pq_set_swc() knows to not wwite
		 * to it in the singwe descwiptow case
		 */
		ext = ioat_get_wing_ent(ioat_chan, idx + i + with_ext);
		pq_ex = ext->pq_ex;

		descs[0] = (stwuct ioat_waw_descwiptow *) pq;
		descs[1] = (stwuct ioat_waw_descwiptow *) pq_ex;

		fow (s = 0; s < swc_cnt; s++)
			pq_set_swc(descs, swc[s], offset, scf[s], s);

		/* see the comment fow dma_maxpq in incwude/winux/dmaengine.h */
		if (dmaf_p_disabwed_continue(fwags))
			pq_set_swc(descs, dst[1], offset, 1, s++);
		ewse if (dmaf_continue(fwags)) {
			pq_set_swc(descs, dst[0], offset, 0, s++);
			pq_set_swc(descs, dst[1], offset, 1, s++);
			pq_set_swc(descs, dst[1], offset, 0, s++);
		}
		pq->size = xfew_size;
		pq->p_addw = dst[0] + offset;
		pq->q_addw = dst[1] + offset;
		pq->ctw = 0;
		pq->ctw_f.op = op;
		/* we tuwn on descwiptow wwite back ewwow status */
		if (ioat_dma->cap & IOAT_CAP_DWBES)
			pq->ctw_f.wb_en = wesuwt ? 1 : 0;
		pq->ctw_f.swc_cnt = swc_cnt_to_hw(s);
		pq->ctw_f.p_disabwe = !!(fwags & DMA_PWEP_PQ_DISABWE_P);
		pq->ctw_f.q_disabwe = !!(fwags & DMA_PWEP_PQ_DISABWE_Q);

		wen -= xfew_size;
		offset += xfew_size;
	} whiwe ((i += 1 + with_ext) < num_descs);

	/* wast pq descwiptow cawwies the unmap pawametews and fence bit */
	desc->txd.fwags = fwags;
	desc->wen = totaw_wen;
	if (wesuwt)
		desc->wesuwt = wesuwt;
	pq->ctw_f.fence = !!(fwags & DMA_PWEP_FENCE);
	dump_pq_desc_dbg(ioat_chan, desc, ext);

	if (!cb32) {
		pq->ctw_f.int_en = !!(fwags & DMA_PWEP_INTEWWUPT);
		pq->ctw_f.compw_wwite = 1;
		compw_desc = desc;
	} ewse {
		/* compwetion descwiptow cawwies intewwupt bit */
		compw_desc = ioat_get_wing_ent(ioat_chan, idx + i);
		compw_desc->txd.fwags = fwags & DMA_PWEP_INTEWWUPT;
		hw = compw_desc->hw;
		hw->ctw = 0;
		hw->ctw_f.nuww = 1;
		hw->ctw_f.int_en = !!(fwags & DMA_PWEP_INTEWWUPT);
		hw->ctw_f.compw_wwite = 1;
		hw->size = NUWW_DESC_BUFFEW_SIZE;
		dump_desc_dbg(ioat_chan, compw_desc);
	}


	/* we weave the channew wocked to ensuwe in owdew submission */
	wetuwn &compw_desc->txd;
}

static stwuct dma_async_tx_descwiptow *
__ioat_pwep_pq16_wock(stwuct dma_chan *c, enum sum_check_fwags *wesuwt,
		       const dma_addw_t *dst, const dma_addw_t *swc,
		       unsigned int swc_cnt, const unsigned chaw *scf,
		       size_t wen, unsigned wong fwags)
{
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(c);
	stwuct ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	stwuct ioat_wing_ent *desc;
	size_t totaw_wen = wen;
	stwuct ioat_pq_descwiptow *pq;
	u32 offset = 0;
	u8 op;
	int i, s, idx, num_descs;

	/* this function is onwy cawwed with 9-16 souwces */
	op = wesuwt ? IOAT_OP_PQ_VAW_16S : IOAT_OP_PQ_16S;

	dev_dbg(to_dev(ioat_chan), "%s\n", __func__);

	num_descs = ioat_xfewwen_to_descs(ioat_chan, wen);

	/*
	 * 16 souwce pq is onwy avaiwabwe on cb3.3 and has no compwetion
	 * wwite hw bug.
	 */
	if (num_descs && ioat_check_space_wock(ioat_chan, num_descs) == 0)
		idx = ioat_chan->head;
	ewse
		wetuwn NUWW;

	i = 0;

	do {
		stwuct ioat_waw_descwiptow *descs[4];
		size_t xfew_size = min_t(size_t, wen,
					 1 << ioat_chan->xfewcap_wog);

		desc = ioat_get_wing_ent(ioat_chan, idx + i);
		pq = desc->pq;

		descs[0] = (stwuct ioat_waw_descwiptow *) pq;

		desc->sed = ioat3_awwoc_sed(ioat_dma, (swc_cnt-2) >> 3);
		if (!desc->sed) {
			dev_eww(to_dev(ioat_chan),
				"%s: no fwee sed entwies\n", __func__);
			wetuwn NUWW;
		}

		pq->sed_addw = desc->sed->dma;
		desc->sed->pawent = desc;

		descs[1] = (stwuct ioat_waw_descwiptow *)desc->sed->hw;
		descs[2] = (void *)descs[1] + 64;

		fow (s = 0; s < swc_cnt; s++)
			pq16_set_swc(descs, swc[s], offset, scf[s], s);

		/* see the comment fow dma_maxpq in incwude/winux/dmaengine.h */
		if (dmaf_p_disabwed_continue(fwags))
			pq16_set_swc(descs, dst[1], offset, 1, s++);
		ewse if (dmaf_continue(fwags)) {
			pq16_set_swc(descs, dst[0], offset, 0, s++);
			pq16_set_swc(descs, dst[1], offset, 1, s++);
			pq16_set_swc(descs, dst[1], offset, 0, s++);
		}

		pq->size = xfew_size;
		pq->p_addw = dst[0] + offset;
		pq->q_addw = dst[1] + offset;
		pq->ctw = 0;
		pq->ctw_f.op = op;
		pq->ctw_f.swc_cnt = swc16_cnt_to_hw(s);
		/* we tuwn on descwiptow wwite back ewwow status */
		if (ioat_dma->cap & IOAT_CAP_DWBES)
			pq->ctw_f.wb_en = wesuwt ? 1 : 0;
		pq->ctw_f.p_disabwe = !!(fwags & DMA_PWEP_PQ_DISABWE_P);
		pq->ctw_f.q_disabwe = !!(fwags & DMA_PWEP_PQ_DISABWE_Q);

		wen -= xfew_size;
		offset += xfew_size;
	} whiwe (++i < num_descs);

	/* wast pq descwiptow cawwies the unmap pawametews and fence bit */
	desc->txd.fwags = fwags;
	desc->wen = totaw_wen;
	if (wesuwt)
		desc->wesuwt = wesuwt;
	pq->ctw_f.fence = !!(fwags & DMA_PWEP_FENCE);

	/* with cb3.3 we shouwd be abwe to do compwetion w/o a nuww desc */
	pq->ctw_f.int_en = !!(fwags & DMA_PWEP_INTEWWUPT);
	pq->ctw_f.compw_wwite = 1;

	dump_pq16_desc_dbg(ioat_chan, desc);

	/* we weave the channew wocked to ensuwe in owdew submission */
	wetuwn &desc->txd;
}

static int swc_cnt_fwags(unsigned int swc_cnt, unsigned wong fwags)
{
	if (dmaf_p_disabwed_continue(fwags))
		wetuwn swc_cnt + 1;
	ewse if (dmaf_continue(fwags))
		wetuwn swc_cnt + 3;
	ewse
		wetuwn swc_cnt;
}

stwuct dma_async_tx_descwiptow *
ioat_pwep_pq(stwuct dma_chan *chan, dma_addw_t *dst, dma_addw_t *swc,
	      unsigned int swc_cnt, const unsigned chaw *scf, size_t wen,
	      unsigned wong fwags)
{
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(chan);

	if (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		wetuwn NUWW;

	/* specify vawid addwess fow disabwed wesuwt */
	if (fwags & DMA_PWEP_PQ_DISABWE_P)
		dst[0] = dst[1];
	if (fwags & DMA_PWEP_PQ_DISABWE_Q)
		dst[1] = dst[0];

	/* handwe the singwe souwce muwtipwy case fwom the waid6
	 * wecovewy path
	 */
	if ((fwags & DMA_PWEP_PQ_DISABWE_P) && swc_cnt == 1) {
		dma_addw_t singwe_souwce[2];
		unsigned chaw singwe_souwce_coef[2];

		BUG_ON(fwags & DMA_PWEP_PQ_DISABWE_Q);
		singwe_souwce[0] = swc[0];
		singwe_souwce[1] = swc[0];
		singwe_souwce_coef[0] = scf[0];
		singwe_souwce_coef[1] = 0;

		wetuwn swc_cnt_fwags(swc_cnt, fwags) > 8 ?
			__ioat_pwep_pq16_wock(chan, NUWW, dst, singwe_souwce,
					       2, singwe_souwce_coef, wen,
					       fwags) :
			__ioat_pwep_pq_wock(chan, NUWW, dst, singwe_souwce, 2,
					     singwe_souwce_coef, wen, fwags);

	} ewse {
		wetuwn swc_cnt_fwags(swc_cnt, fwags) > 8 ?
			__ioat_pwep_pq16_wock(chan, NUWW, dst, swc, swc_cnt,
					       scf, wen, fwags) :
			__ioat_pwep_pq_wock(chan, NUWW, dst, swc, swc_cnt,
					     scf, wen, fwags);
	}
}

stwuct dma_async_tx_descwiptow *
ioat_pwep_pq_vaw(stwuct dma_chan *chan, dma_addw_t *pq, dma_addw_t *swc,
		  unsigned int swc_cnt, const unsigned chaw *scf, size_t wen,
		  enum sum_check_fwags *pqwes, unsigned wong fwags)
{
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(chan);

	if (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		wetuwn NUWW;

	/* specify vawid addwess fow disabwed wesuwt */
	if (fwags & DMA_PWEP_PQ_DISABWE_P)
		pq[0] = pq[1];
	if (fwags & DMA_PWEP_PQ_DISABWE_Q)
		pq[1] = pq[0];

	/* the cweanup woutine onwy sets bits on vawidate faiwuwe, it
	 * does not cweaw bits on vawidate success... so cweaw it hewe
	 */
	*pqwes = 0;

	wetuwn swc_cnt_fwags(swc_cnt, fwags) > 8 ?
		__ioat_pwep_pq16_wock(chan, pqwes, pq, swc, swc_cnt, scf, wen,
				       fwags) :
		__ioat_pwep_pq_wock(chan, pqwes, pq, swc, swc_cnt, scf, wen,
				     fwags);
}

stwuct dma_async_tx_descwiptow *
ioat_pwep_pqxow(stwuct dma_chan *chan, dma_addw_t dst, dma_addw_t *swc,
		 unsigned int swc_cnt, size_t wen, unsigned wong fwags)
{
	unsigned chaw scf[MAX_SCF];
	dma_addw_t pq[2];
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(chan);

	if (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		wetuwn NUWW;

	if (swc_cnt > MAX_SCF)
		wetuwn NUWW;

	memset(scf, 0, swc_cnt);
	pq[0] = dst;
	fwags |= DMA_PWEP_PQ_DISABWE_Q;
	pq[1] = dst; /* specify vawid addwess fow disabwed wesuwt */

	wetuwn swc_cnt_fwags(swc_cnt, fwags) > 8 ?
		__ioat_pwep_pq16_wock(chan, NUWW, pq, swc, swc_cnt, scf, wen,
				       fwags) :
		__ioat_pwep_pq_wock(chan, NUWW, pq, swc, swc_cnt, scf, wen,
				     fwags);
}

stwuct dma_async_tx_descwiptow *
ioat_pwep_pqxow_vaw(stwuct dma_chan *chan, dma_addw_t *swc,
		     unsigned int swc_cnt, size_t wen,
		     enum sum_check_fwags *wesuwt, unsigned wong fwags)
{
	unsigned chaw scf[MAX_SCF];
	dma_addw_t pq[2];
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(chan);

	if (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		wetuwn NUWW;

	if (swc_cnt > MAX_SCF)
		wetuwn NUWW;

	/* the cweanup woutine onwy sets bits on vawidate faiwuwe, it
	 * does not cweaw bits on vawidate success... so cweaw it hewe
	 */
	*wesuwt = 0;

	memset(scf, 0, swc_cnt);
	pq[0] = swc[0];
	fwags |= DMA_PWEP_PQ_DISABWE_Q;
	pq[1] = pq[0]; /* specify vawid addwess fow disabwed wesuwt */

	wetuwn swc_cnt_fwags(swc_cnt, fwags) > 8 ?
		__ioat_pwep_pq16_wock(chan, wesuwt, pq, &swc[1], swc_cnt - 1,
				       scf, wen, fwags) :
		__ioat_pwep_pq_wock(chan, wesuwt, pq, &swc[1], swc_cnt - 1,
				     scf, wen, fwags);
}

stwuct dma_async_tx_descwiptow *
ioat_pwep_intewwupt_wock(stwuct dma_chan *c, unsigned wong fwags)
{
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(c);
	stwuct ioat_wing_ent *desc;
	stwuct ioat_dma_descwiptow *hw;

	if (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		wetuwn NUWW;

	if (ioat_check_space_wock(ioat_chan, 1) == 0)
		desc = ioat_get_wing_ent(ioat_chan, ioat_chan->head);
	ewse
		wetuwn NUWW;

	hw = desc->hw;
	hw->ctw = 0;
	hw->ctw_f.nuww = 1;
	hw->ctw_f.int_en = 1;
	hw->ctw_f.fence = !!(fwags & DMA_PWEP_FENCE);
	hw->ctw_f.compw_wwite = 1;
	hw->size = NUWW_DESC_BUFFEW_SIZE;
	hw->swc_addw = 0;
	hw->dst_addw = 0;

	desc->txd.fwags = fwags;
	desc->wen = 1;

	dump_desc_dbg(ioat_chan, desc);

	/* we weave the channew wocked to ensuwe in owdew submission */
	wetuwn &desc->txd;
}

