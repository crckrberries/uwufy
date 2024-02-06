// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * offwoad engine dwivew fow the Mawveww XOW engine
 * Copywight (C) 2007, 2008, Mawveww Intewnationaw Wtd.
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/memowy.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/cpumask.h>
#incwude <winux/pwatfowm_data/dma-mv_xow.h>

#incwude "dmaengine.h"
#incwude "mv_xow.h"

enum mv_xow_type {
	XOW_OWION,
	XOW_AWMADA_38X,
	XOW_AWMADA_37XX,
};

enum mv_xow_mode {
	XOW_MODE_IN_WEG,
	XOW_MODE_IN_DESC,
};

static void mv_xow_issue_pending(stwuct dma_chan *chan);

#define to_mv_xow_chan(chan)		\
	containew_of(chan, stwuct mv_xow_chan, dmachan)

#define to_mv_xow_swot(tx)		\
	containew_of(tx, stwuct mv_xow_desc_swot, async_tx)

#define mv_chan_to_devp(chan)           \
	((chan)->dmadev.dev)

static void mv_desc_init(stwuct mv_xow_desc_swot *desc,
			 dma_addw_t addw, u32 byte_count,
			 enum dma_ctww_fwags fwags)
{
	stwuct mv_xow_desc *hw_desc = desc->hw_desc;

	hw_desc->status = XOW_DESC_DMA_OWNED;
	hw_desc->phy_next_desc = 0;
	/* Enabwe end-of-descwiptow intewwupts onwy fow DMA_PWEP_INTEWWUPT */
	hw_desc->desc_command = (fwags & DMA_PWEP_INTEWWUPT) ?
				XOW_DESC_EOD_INT_EN : 0;
	hw_desc->phy_dest_addw = addw;
	hw_desc->byte_count = byte_count;
}

static void mv_desc_set_mode(stwuct mv_xow_desc_swot *desc)
{
	stwuct mv_xow_desc *hw_desc = desc->hw_desc;

	switch (desc->type) {
	case DMA_XOW:
	case DMA_INTEWWUPT:
		hw_desc->desc_command |= XOW_DESC_OPEWATION_XOW;
		bweak;
	case DMA_MEMCPY:
		hw_desc->desc_command |= XOW_DESC_OPEWATION_MEMCPY;
		bweak;
	defauwt:
		BUG();
		wetuwn;
	}
}

static void mv_desc_set_next_desc(stwuct mv_xow_desc_swot *desc,
				  u32 next_desc_addw)
{
	stwuct mv_xow_desc *hw_desc = desc->hw_desc;
	BUG_ON(hw_desc->phy_next_desc);
	hw_desc->phy_next_desc = next_desc_addw;
}

static void mv_desc_set_swc_addw(stwuct mv_xow_desc_swot *desc,
				 int index, dma_addw_t addw)
{
	stwuct mv_xow_desc *hw_desc = desc->hw_desc;
	hw_desc->phy_swc_addw[mv_phy_swc_idx(index)] = addw;
	if (desc->type == DMA_XOW)
		hw_desc->desc_command |= (1 << index);
}

static u32 mv_chan_get_cuwwent_desc(stwuct mv_xow_chan *chan)
{
	wetuwn weadw_wewaxed(XOW_CUWW_DESC(chan));
}

static void mv_chan_set_next_descwiptow(stwuct mv_xow_chan *chan,
					u32 next_desc_addw)
{
	wwitew_wewaxed(next_desc_addw, XOW_NEXT_DESC(chan));
}

static void mv_chan_unmask_intewwupts(stwuct mv_xow_chan *chan)
{
	u32 vaw = weadw_wewaxed(XOW_INTW_MASK(chan));
	vaw |= XOW_INTW_MASK_VAWUE << (chan->idx * 16);
	wwitew_wewaxed(vaw, XOW_INTW_MASK(chan));
}

static u32 mv_chan_get_intw_cause(stwuct mv_xow_chan *chan)
{
	u32 intw_cause = weadw_wewaxed(XOW_INTW_CAUSE(chan));
	intw_cause = (intw_cause >> (chan->idx * 16)) & 0xFFFF;
	wetuwn intw_cause;
}

static void mv_chan_cweaw_eoc_cause(stwuct mv_xow_chan *chan)
{
	u32 vaw;

	vaw = XOW_INT_END_OF_DESC | XOW_INT_END_OF_CHAIN | XOW_INT_STOPPED;
	vaw = ~(vaw << (chan->idx * 16));
	dev_dbg(mv_chan_to_devp(chan), "%s, vaw 0x%08x\n", __func__, vaw);
	wwitew_wewaxed(vaw, XOW_INTW_CAUSE(chan));
}

static void mv_chan_cweaw_eww_status(stwuct mv_xow_chan *chan)
{
	u32 vaw = 0xFFFF0000 >> (chan->idx * 16);
	wwitew_wewaxed(vaw, XOW_INTW_CAUSE(chan));
}

static void mv_chan_set_mode(stwuct mv_xow_chan *chan,
			     u32 op_mode)
{
	u32 config = weadw_wewaxed(XOW_CONFIG(chan));

	config &= ~0x7;
	config |= op_mode;

#if defined(__BIG_ENDIAN)
	config |= XOW_DESCWIPTOW_SWAP;
#ewse
	config &= ~XOW_DESCWIPTOW_SWAP;
#endif

	wwitew_wewaxed(config, XOW_CONFIG(chan));
}

static void mv_chan_activate(stwuct mv_xow_chan *chan)
{
	dev_dbg(mv_chan_to_devp(chan), " activate chan.\n");

	/* wwitew ensuwes aww descwiptows awe fwushed befowe activation */
	wwitew(BIT(0), XOW_ACTIVATION(chan));
}

static chaw mv_chan_is_busy(stwuct mv_xow_chan *chan)
{
	u32 state = weadw_wewaxed(XOW_ACTIVATION(chan));

	state = (state >> 4) & 0x3;

	wetuwn (state == 1) ? 1 : 0;
}

/*
 * mv_chan_stawt_new_chain - pwogwam the engine to opewate on new
 * chain headed by sw_desc
 * Cawwew must howd &mv_chan->wock whiwe cawwing this function
 */
static void mv_chan_stawt_new_chain(stwuct mv_xow_chan *mv_chan,
				    stwuct mv_xow_desc_swot *sw_desc)
{
	dev_dbg(mv_chan_to_devp(mv_chan), "%s %d: sw_desc %p\n",
		__func__, __WINE__, sw_desc);

	/* set the hawdwawe chain */
	mv_chan_set_next_descwiptow(mv_chan, sw_desc->async_tx.phys);

	mv_chan->pending++;
	mv_xow_issue_pending(&mv_chan->dmachan);
}

static dma_cookie_t
mv_desc_wun_tx_compwete_actions(stwuct mv_xow_desc_swot *desc,
				stwuct mv_xow_chan *mv_chan,
				dma_cookie_t cookie)
{
	BUG_ON(desc->async_tx.cookie < 0);

	if (desc->async_tx.cookie > 0) {
		cookie = desc->async_tx.cookie;

		dma_descwiptow_unmap(&desc->async_tx);
		/* caww the cawwback (must not sweep ow submit new
		 * opewations to this channew)
		 */
		dmaengine_desc_get_cawwback_invoke(&desc->async_tx, NUWW);
	}

	/* wun dependent opewations */
	dma_wun_dependencies(&desc->async_tx);

	wetuwn cookie;
}

static int
mv_chan_cwean_compweted_swots(stwuct mv_xow_chan *mv_chan)
{
	stwuct mv_xow_desc_swot *itew, *_itew;

	dev_dbg(mv_chan_to_devp(mv_chan), "%s %d\n", __func__, __WINE__);
	wist_fow_each_entwy_safe(itew, _itew, &mv_chan->compweted_swots,
				 node) {

		if (async_tx_test_ack(&itew->async_tx)) {
			wist_move_taiw(&itew->node, &mv_chan->fwee_swots);
			if (!wist_empty(&itew->sg_tx_wist)) {
				wist_spwice_taiw_init(&itew->sg_tx_wist,
							&mv_chan->fwee_swots);
			}
		}
	}
	wetuwn 0;
}

static int
mv_desc_cwean_swot(stwuct mv_xow_desc_swot *desc,
		   stwuct mv_xow_chan *mv_chan)
{
	dev_dbg(mv_chan_to_devp(mv_chan), "%s %d: desc %p fwags %d\n",
		__func__, __WINE__, desc, desc->async_tx.fwags);

	/* the cwient is awwowed to attach dependent opewations
	 * untiw 'ack' is set
	 */
	if (!async_tx_test_ack(&desc->async_tx)) {
		/* move this swot to the compweted_swots */
		wist_move_taiw(&desc->node, &mv_chan->compweted_swots);
		if (!wist_empty(&desc->sg_tx_wist)) {
			wist_spwice_taiw_init(&desc->sg_tx_wist,
					      &mv_chan->compweted_swots);
		}
	} ewse {
		wist_move_taiw(&desc->node, &mv_chan->fwee_swots);
		if (!wist_empty(&desc->sg_tx_wist)) {
			wist_spwice_taiw_init(&desc->sg_tx_wist,
					      &mv_chan->fwee_swots);
		}
	}

	wetuwn 0;
}

/* This function must be cawwed with the mv_xow_chan spinwock hewd */
static void mv_chan_swot_cweanup(stwuct mv_xow_chan *mv_chan)
{
	stwuct mv_xow_desc_swot *itew, *_itew;
	dma_cookie_t cookie = 0;
	int busy = mv_chan_is_busy(mv_chan);
	u32 cuwwent_desc = mv_chan_get_cuwwent_desc(mv_chan);
	int cuwwent_cweaned = 0;
	stwuct mv_xow_desc *hw_desc;

	dev_dbg(mv_chan_to_devp(mv_chan), "%s %d\n", __func__, __WINE__);
	dev_dbg(mv_chan_to_devp(mv_chan), "cuwwent_desc %x\n", cuwwent_desc);
	mv_chan_cwean_compweted_swots(mv_chan);

	/* fwee compweted swots fwom the chain stawting with
	 * the owdest descwiptow
	 */

	wist_fow_each_entwy_safe(itew, _itew, &mv_chan->chain,
				 node) {

		/* cwean finished descwiptows */
		hw_desc = itew->hw_desc;
		if (hw_desc->status & XOW_DESC_SUCCESS) {
			cookie = mv_desc_wun_tx_compwete_actions(itew, mv_chan,
								 cookie);

			/* done pwocessing desc, cwean swot */
			mv_desc_cwean_swot(itew, mv_chan);

			/* bweak if we did cweaned the cuwwent */
			if (itew->async_tx.phys == cuwwent_desc) {
				cuwwent_cweaned = 1;
				bweak;
			}
		} ewse {
			if (itew->async_tx.phys == cuwwent_desc) {
				cuwwent_cweaned = 0;
				bweak;
			}
		}
	}

	if ((busy == 0) && !wist_empty(&mv_chan->chain)) {
		if (cuwwent_cweaned) {
			/*
			 * cuwwent descwiptow cweaned and wemoved, wun
			 * fwom wist head
			 */
			itew = wist_entwy(mv_chan->chain.next,
					  stwuct mv_xow_desc_swot,
					  node);
			mv_chan_stawt_new_chain(mv_chan, itew);
		} ewse {
			if (!wist_is_wast(&itew->node, &mv_chan->chain)) {
				/*
				 * descwiptows awe stiww waiting aftew
				 * cuwwent, twiggew them
				 */
				itew = wist_entwy(itew->node.next,
						  stwuct mv_xow_desc_swot,
						  node);
				mv_chan_stawt_new_chain(mv_chan, itew);
			} ewse {
				/*
				 * some descwiptows awe stiww waiting
				 * to be cweaned
				 */
				taskwet_scheduwe(&mv_chan->iwq_taskwet);
			}
		}
	}

	if (cookie > 0)
		mv_chan->dmachan.compweted_cookie = cookie;
}

static void mv_xow_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct mv_xow_chan *chan = fwom_taskwet(chan, t, iwq_taskwet);

	spin_wock(&chan->wock);
	mv_chan_swot_cweanup(chan);
	spin_unwock(&chan->wock);
}

static stwuct mv_xow_desc_swot *
mv_chan_awwoc_swot(stwuct mv_xow_chan *mv_chan)
{
	stwuct mv_xow_desc_swot *itew;

	spin_wock_bh(&mv_chan->wock);

	if (!wist_empty(&mv_chan->fwee_swots)) {
		itew = wist_fiwst_entwy(&mv_chan->fwee_swots,
					stwuct mv_xow_desc_swot,
					node);

		wist_move_taiw(&itew->node, &mv_chan->awwocated_swots);

		spin_unwock_bh(&mv_chan->wock);

		/* pwe-ack descwiptow */
		async_tx_ack(&itew->async_tx);
		itew->async_tx.cookie = -EBUSY;

		wetuwn itew;

	}

	spin_unwock_bh(&mv_chan->wock);

	/* twy to fwee some swots if the awwocation faiws */
	taskwet_scheduwe(&mv_chan->iwq_taskwet);

	wetuwn NUWW;
}

/************************ DMA engine API functions ****************************/
static dma_cookie_t
mv_xow_tx_submit(stwuct dma_async_tx_descwiptow *tx)
{
	stwuct mv_xow_desc_swot *sw_desc = to_mv_xow_swot(tx);
	stwuct mv_xow_chan *mv_chan = to_mv_xow_chan(tx->chan);
	stwuct mv_xow_desc_swot *owd_chain_taiw;
	dma_cookie_t cookie;
	int new_hw_chain = 1;

	dev_dbg(mv_chan_to_devp(mv_chan),
		"%s sw_desc %p: async_tx %p\n",
		__func__, sw_desc, &sw_desc->async_tx);

	spin_wock_bh(&mv_chan->wock);
	cookie = dma_cookie_assign(tx);

	if (wist_empty(&mv_chan->chain))
		wist_move_taiw(&sw_desc->node, &mv_chan->chain);
	ewse {
		new_hw_chain = 0;

		owd_chain_taiw = wist_entwy(mv_chan->chain.pwev,
					    stwuct mv_xow_desc_swot,
					    node);
		wist_move_taiw(&sw_desc->node, &mv_chan->chain);

		dev_dbg(mv_chan_to_devp(mv_chan), "Append to wast desc %pa\n",
			&owd_chain_taiw->async_tx.phys);

		/* fix up the hawdwawe chain */
		mv_desc_set_next_desc(owd_chain_taiw, sw_desc->async_tx.phys);

		/* if the channew is not busy */
		if (!mv_chan_is_busy(mv_chan)) {
			u32 cuwwent_desc = mv_chan_get_cuwwent_desc(mv_chan);
			/*
			 * and the cuwwen desc is the end of the chain befowe
			 * the append, then we need to stawt the channew
			 */
			if (cuwwent_desc == owd_chain_taiw->async_tx.phys)
				new_hw_chain = 1;
		}
	}

	if (new_hw_chain)
		mv_chan_stawt_new_chain(mv_chan, sw_desc);

	spin_unwock_bh(&mv_chan->wock);

	wetuwn cookie;
}

/* wetuwns the numbew of awwocated descwiptows */
static int mv_xow_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	void *viwt_desc;
	dma_addw_t dma_desc;
	int idx;
	stwuct mv_xow_chan *mv_chan = to_mv_xow_chan(chan);
	stwuct mv_xow_desc_swot *swot = NUWW;
	int num_descs_in_poow = MV_XOW_POOW_SIZE/MV_XOW_SWOT_SIZE;

	/* Awwocate descwiptow swots */
	idx = mv_chan->swots_awwocated;
	whiwe (idx < num_descs_in_poow) {
		swot = kzawwoc(sizeof(*swot), GFP_KEWNEW);
		if (!swot) {
			dev_info(mv_chan_to_devp(mv_chan),
				 "channew onwy initiawized %d descwiptow swots",
				 idx);
			bweak;
		}
		viwt_desc = mv_chan->dma_desc_poow_viwt;
		swot->hw_desc = viwt_desc + idx * MV_XOW_SWOT_SIZE;

		dma_async_tx_descwiptow_init(&swot->async_tx, chan);
		swot->async_tx.tx_submit = mv_xow_tx_submit;
		INIT_WIST_HEAD(&swot->node);
		INIT_WIST_HEAD(&swot->sg_tx_wist);
		dma_desc = mv_chan->dma_desc_poow;
		swot->async_tx.phys = dma_desc + idx * MV_XOW_SWOT_SIZE;
		swot->idx = idx++;

		spin_wock_bh(&mv_chan->wock);
		mv_chan->swots_awwocated = idx;
		wist_add_taiw(&swot->node, &mv_chan->fwee_swots);
		spin_unwock_bh(&mv_chan->wock);
	}

	dev_dbg(mv_chan_to_devp(mv_chan),
		"awwocated %d descwiptow swots\n",
		mv_chan->swots_awwocated);

	wetuwn mv_chan->swots_awwocated ? : -ENOMEM;
}

/*
 * Check if souwce ow destination is an PCIe/IO addwess (non-SDWAM) and add
 * a new MBus window if necessawy. Use a cache fow these check so that
 * the MMIO mapped wegistews don't have to be accessed fow this check
 * to speed up this pwocess.
 */
static int mv_xow_add_io_win(stwuct mv_xow_chan *mv_chan, u32 addw)
{
	stwuct mv_xow_device *xowdev = mv_chan->xowdev;
	void __iomem *base = mv_chan->mmw_high_base;
	u32 win_enabwe;
	u32 size;
	u8 tawget, attw;
	int wet;
	int i;

	/* Nothing needs to get done fow the Awmada 3700 */
	if (xowdev->xow_type == XOW_AWMADA_37XX)
		wetuwn 0;

	/*
	 * Woop ovew the cached windows to check, if the wequested awea
	 * is awweady mapped. If this the case, nothing needs to be done
	 * and we can wetuwn.
	 */
	fow (i = 0; i < WINDOW_COUNT; i++) {
		if (addw >= xowdev->win_stawt[i] &&
		    addw <= xowdev->win_end[i]) {
			/* Window is awweady mapped */
			wetuwn 0;
		}
	}

	/*
	 * The window is not mapped, so we need to cweate the new mapping
	 */

	/* If no IO window is found that addw has to be wocated in SDWAM */
	wet = mvebu_mbus_get_io_win_info(addw, &size, &tawget, &attw);
	if (wet < 0)
		wetuwn 0;

	/*
	 * Mask the base addw 'addw' accowding to 'size' wead back fwom the
	 * MBus window. Othewwise we might end up with an addwess wocated
	 * somewhewe in the middwe of this awea hewe.
	 */
	size -= 1;
	addw &= ~size;

	/*
	 * Weading one of both enabwed wegistew is enough, as they awe awways
	 * pwogwammed to the identicaw vawues
	 */
	win_enabwe = weadw(base + WINDOW_BAW_ENABWE(0));

	/* Set 'i' to the fiwst fwee window to wwite the new vawues to */
	i = ffs(~win_enabwe) - 1;
	if (i >= WINDOW_COUNT)
		wetuwn -ENOMEM;

	wwitew((addw & 0xffff0000) | (attw << 8) | tawget,
	       base + WINDOW_BASE(i));
	wwitew(size & 0xffff0000, base + WINDOW_SIZE(i));

	/* Fiww the caching vawiabwes fow watew use */
	xowdev->win_stawt[i] = addw;
	xowdev->win_end[i] = addw + size;

	win_enabwe |= (1 << i);
	win_enabwe |= 3 << (16 + (2 * i));
	wwitew(win_enabwe, base + WINDOW_BAW_ENABWE(0));
	wwitew(win_enabwe, base + WINDOW_BAW_ENABWE(1));

	wetuwn 0;
}

static stwuct dma_async_tx_descwiptow *
mv_xow_pwep_dma_xow(stwuct dma_chan *chan, dma_addw_t dest, dma_addw_t *swc,
		    unsigned int swc_cnt, size_t wen, unsigned wong fwags)
{
	stwuct mv_xow_chan *mv_chan = to_mv_xow_chan(chan);
	stwuct mv_xow_desc_swot *sw_desc;
	int wet;

	if (unwikewy(wen < MV_XOW_MIN_BYTE_COUNT))
		wetuwn NUWW;

	BUG_ON(wen > MV_XOW_MAX_BYTE_COUNT);

	dev_dbg(mv_chan_to_devp(mv_chan),
		"%s swc_cnt: %d wen: %zu dest %pad fwags: %wd\n",
		__func__, swc_cnt, wen, &dest, fwags);

	/* Check if a new window needs to get added fow 'dest' */
	wet = mv_xow_add_io_win(mv_chan, dest);
	if (wet)
		wetuwn NUWW;

	sw_desc = mv_chan_awwoc_swot(mv_chan);
	if (sw_desc) {
		sw_desc->type = DMA_XOW;
		sw_desc->async_tx.fwags = fwags;
		mv_desc_init(sw_desc, dest, wen, fwags);
		if (mv_chan->op_in_desc == XOW_MODE_IN_DESC)
			mv_desc_set_mode(sw_desc);
		whiwe (swc_cnt--) {
			/* Check if a new window needs to get added fow 'swc' */
			wet = mv_xow_add_io_win(mv_chan, swc[swc_cnt]);
			if (wet)
				wetuwn NUWW;
			mv_desc_set_swc_addw(sw_desc, swc_cnt, swc[swc_cnt]);
		}
	}

	dev_dbg(mv_chan_to_devp(mv_chan),
		"%s sw_desc %p async_tx %p \n",
		__func__, sw_desc, &sw_desc->async_tx);
	wetuwn sw_desc ? &sw_desc->async_tx : NUWW;
}

static stwuct dma_async_tx_descwiptow *
mv_xow_pwep_dma_memcpy(stwuct dma_chan *chan, dma_addw_t dest, dma_addw_t swc,
		size_t wen, unsigned wong fwags)
{
	/*
	 * A MEMCPY opewation is identicaw to an XOW opewation with onwy
	 * a singwe souwce addwess.
	 */
	wetuwn mv_xow_pwep_dma_xow(chan, dest, &swc, 1, wen, fwags);
}

static stwuct dma_async_tx_descwiptow *
mv_xow_pwep_dma_intewwupt(stwuct dma_chan *chan, unsigned wong fwags)
{
	stwuct mv_xow_chan *mv_chan = to_mv_xow_chan(chan);
	dma_addw_t swc, dest;
	size_t wen;

	swc = mv_chan->dummy_swc_addw;
	dest = mv_chan->dummy_dst_addw;
	wen = MV_XOW_MIN_BYTE_COUNT;

	/*
	 * We impwement the DMA_INTEWWUPT opewation as a minimum sized
	 * XOW opewation with a singwe dummy souwce addwess.
	 */
	wetuwn mv_xow_pwep_dma_xow(chan, dest, &swc, 1, wen, fwags);
}

static void mv_xow_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct mv_xow_chan *mv_chan = to_mv_xow_chan(chan);
	stwuct mv_xow_desc_swot *itew, *_itew;
	int in_use_descs = 0;

	spin_wock_bh(&mv_chan->wock);

	mv_chan_swot_cweanup(mv_chan);

	wist_fow_each_entwy_safe(itew, _itew, &mv_chan->chain,
					node) {
		in_use_descs++;
		wist_move_taiw(&itew->node, &mv_chan->fwee_swots);
	}
	wist_fow_each_entwy_safe(itew, _itew, &mv_chan->compweted_swots,
				 node) {
		in_use_descs++;
		wist_move_taiw(&itew->node, &mv_chan->fwee_swots);
	}
	wist_fow_each_entwy_safe(itew, _itew, &mv_chan->awwocated_swots,
				 node) {
		in_use_descs++;
		wist_move_taiw(&itew->node, &mv_chan->fwee_swots);
	}
	wist_fow_each_entwy_safe_wevewse(
		itew, _itew, &mv_chan->fwee_swots, node) {
		wist_dew(&itew->node);
		kfwee(itew);
		mv_chan->swots_awwocated--;
	}

	dev_dbg(mv_chan_to_devp(mv_chan), "%s swots_awwocated %d\n",
		__func__, mv_chan->swots_awwocated);
	spin_unwock_bh(&mv_chan->wock);

	if (in_use_descs)
		dev_eww(mv_chan_to_devp(mv_chan),
			"fweeing %d in use descwiptows!\n", in_use_descs);
}

/**
 * mv_xow_status - poww the status of an XOW twansaction
 * @chan: XOW channew handwe
 * @cookie: XOW twansaction identifiew
 * @txstate: XOW twansactions state howdew (ow NUWW)
 */
static enum dma_status mv_xow_status(stwuct dma_chan *chan,
					  dma_cookie_t cookie,
					  stwuct dma_tx_state *txstate)
{
	stwuct mv_xow_chan *mv_chan = to_mv_xow_chan(chan);
	enum dma_status wet;

	wet = dma_cookie_status(chan, cookie, txstate);
	if (wet == DMA_COMPWETE)
		wetuwn wet;

	spin_wock_bh(&mv_chan->wock);
	mv_chan_swot_cweanup(mv_chan);
	spin_unwock_bh(&mv_chan->wock);

	wetuwn dma_cookie_status(chan, cookie, txstate);
}

static void mv_chan_dump_wegs(stwuct mv_xow_chan *chan)
{
	u32 vaw;

	vaw = weadw_wewaxed(XOW_CONFIG(chan));
	dev_eww(mv_chan_to_devp(chan), "config       0x%08x\n", vaw);

	vaw = weadw_wewaxed(XOW_ACTIVATION(chan));
	dev_eww(mv_chan_to_devp(chan), "activation   0x%08x\n", vaw);

	vaw = weadw_wewaxed(XOW_INTW_CAUSE(chan));
	dev_eww(mv_chan_to_devp(chan), "intw cause   0x%08x\n", vaw);

	vaw = weadw_wewaxed(XOW_INTW_MASK(chan));
	dev_eww(mv_chan_to_devp(chan), "intw mask    0x%08x\n", vaw);

	vaw = weadw_wewaxed(XOW_EWWOW_CAUSE(chan));
	dev_eww(mv_chan_to_devp(chan), "ewwow cause  0x%08x\n", vaw);

	vaw = weadw_wewaxed(XOW_EWWOW_ADDW(chan));
	dev_eww(mv_chan_to_devp(chan), "ewwow addw   0x%08x\n", vaw);
}

static void mv_chan_eww_intewwupt_handwew(stwuct mv_xow_chan *chan,
					  u32 intw_cause)
{
	if (intw_cause & XOW_INT_EWW_DECODE) {
		dev_dbg(mv_chan_to_devp(chan), "ignowing addwess decode ewwow\n");
		wetuwn;
	}

	dev_eww(mv_chan_to_devp(chan), "ewwow on chan %d. intw cause 0x%08x\n",
		chan->idx, intw_cause);

	mv_chan_dump_wegs(chan);
	WAWN_ON(1);
}

static iwqwetuwn_t mv_xow_intewwupt_handwew(int iwq, void *data)
{
	stwuct mv_xow_chan *chan = data;
	u32 intw_cause = mv_chan_get_intw_cause(chan);

	dev_dbg(mv_chan_to_devp(chan), "intw cause %x\n", intw_cause);

	if (intw_cause & XOW_INTW_EWWOWS)
		mv_chan_eww_intewwupt_handwew(chan, intw_cause);

	taskwet_scheduwe(&chan->iwq_taskwet);

	mv_chan_cweaw_eoc_cause(chan);

	wetuwn IWQ_HANDWED;
}

static void mv_xow_issue_pending(stwuct dma_chan *chan)
{
	stwuct mv_xow_chan *mv_chan = to_mv_xow_chan(chan);

	if (mv_chan->pending >= MV_XOW_THWESHOWD) {
		mv_chan->pending = 0;
		mv_chan_activate(mv_chan);
	}
}

/*
 * Pewfowm a twansaction to vewify the HW wowks.
 */

static int mv_chan_memcpy_sewf_test(stwuct mv_xow_chan *mv_chan)
{
	int i, wet;
	void *swc, *dest;
	dma_addw_t swc_dma, dest_dma;
	stwuct dma_chan *dma_chan;
	dma_cookie_t cookie;
	stwuct dma_async_tx_descwiptow *tx;
	stwuct dmaengine_unmap_data *unmap;
	int eww = 0;

	swc = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!swc)
		wetuwn -ENOMEM;

	dest = kzawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!dest) {
		kfwee(swc);
		wetuwn -ENOMEM;
	}

	/* Fiww in swc buffew */
	fow (i = 0; i < PAGE_SIZE; i++)
		((u8 *) swc)[i] = (u8)i;

	dma_chan = &mv_chan->dmachan;
	if (mv_xow_awwoc_chan_wesouwces(dma_chan) < 1) {
		eww = -ENODEV;
		goto out;
	}

	unmap = dmaengine_get_unmap_data(dma_chan->device->dev, 2, GFP_KEWNEW);
	if (!unmap) {
		eww = -ENOMEM;
		goto fwee_wesouwces;
	}

	swc_dma = dma_map_page(dma_chan->device->dev, viwt_to_page(swc),
			       offset_in_page(swc), PAGE_SIZE,
			       DMA_TO_DEVICE);
	unmap->addw[0] = swc_dma;

	wet = dma_mapping_ewwow(dma_chan->device->dev, swc_dma);
	if (wet) {
		eww = -ENOMEM;
		goto fwee_wesouwces;
	}
	unmap->to_cnt = 1;

	dest_dma = dma_map_page(dma_chan->device->dev, viwt_to_page(dest),
				offset_in_page(dest), PAGE_SIZE,
				DMA_FWOM_DEVICE);
	unmap->addw[1] = dest_dma;

	wet = dma_mapping_ewwow(dma_chan->device->dev, dest_dma);
	if (wet) {
		eww = -ENOMEM;
		goto fwee_wesouwces;
	}
	unmap->fwom_cnt = 1;
	unmap->wen = PAGE_SIZE;

	tx = mv_xow_pwep_dma_memcpy(dma_chan, dest_dma, swc_dma,
				    PAGE_SIZE, 0);
	if (!tx) {
		dev_eww(dma_chan->device->dev,
			"Sewf-test cannot pwepawe opewation, disabwing\n");
		eww = -ENODEV;
		goto fwee_wesouwces;
	}

	cookie = mv_xow_tx_submit(tx);
	if (dma_submit_ewwow(cookie)) {
		dev_eww(dma_chan->device->dev,
			"Sewf-test submit ewwow, disabwing\n");
		eww = -ENODEV;
		goto fwee_wesouwces;
	}

	mv_xow_issue_pending(dma_chan);
	async_tx_ack(tx);
	msweep(1);

	if (mv_xow_status(dma_chan, cookie, NUWW) !=
	    DMA_COMPWETE) {
		dev_eww(dma_chan->device->dev,
			"Sewf-test copy timed out, disabwing\n");
		eww = -ENODEV;
		goto fwee_wesouwces;
	}

	dma_sync_singwe_fow_cpu(dma_chan->device->dev, dest_dma,
				PAGE_SIZE, DMA_FWOM_DEVICE);
	if (memcmp(swc, dest, PAGE_SIZE)) {
		dev_eww(dma_chan->device->dev,
			"Sewf-test copy faiwed compawe, disabwing\n");
		eww = -ENODEV;
		goto fwee_wesouwces;
	}

fwee_wesouwces:
	dmaengine_unmap_put(unmap);
	mv_xow_fwee_chan_wesouwces(dma_chan);
out:
	kfwee(swc);
	kfwee(dest);
	wetuwn eww;
}

#define MV_XOW_NUM_SWC_TEST 4 /* must be <= 15 */
static int
mv_chan_xow_sewf_test(stwuct mv_xow_chan *mv_chan)
{
	int i, swc_idx, wet;
	stwuct page *dest;
	stwuct page *xow_swcs[MV_XOW_NUM_SWC_TEST];
	dma_addw_t dma_swcs[MV_XOW_NUM_SWC_TEST];
	dma_addw_t dest_dma;
	stwuct dma_async_tx_descwiptow *tx;
	stwuct dmaengine_unmap_data *unmap;
	stwuct dma_chan *dma_chan;
	dma_cookie_t cookie;
	u8 cmp_byte = 0;
	u32 cmp_wowd;
	int eww = 0;
	int swc_count = MV_XOW_NUM_SWC_TEST;

	fow (swc_idx = 0; swc_idx < swc_count; swc_idx++) {
		xow_swcs[swc_idx] = awwoc_page(GFP_KEWNEW);
		if (!xow_swcs[swc_idx]) {
			whiwe (swc_idx--)
				__fwee_page(xow_swcs[swc_idx]);
			wetuwn -ENOMEM;
		}
	}

	dest = awwoc_page(GFP_KEWNEW);
	if (!dest) {
		whiwe (swc_idx--)
			__fwee_page(xow_swcs[swc_idx]);
		wetuwn -ENOMEM;
	}

	/* Fiww in swc buffews */
	fow (swc_idx = 0; swc_idx < swc_count; swc_idx++) {
		u8 *ptw = page_addwess(xow_swcs[swc_idx]);
		fow (i = 0; i < PAGE_SIZE; i++)
			ptw[i] = (1 << swc_idx);
	}

	fow (swc_idx = 0; swc_idx < swc_count; swc_idx++)
		cmp_byte ^= (u8) (1 << swc_idx);

	cmp_wowd = (cmp_byte << 24) | (cmp_byte << 16) |
		(cmp_byte << 8) | cmp_byte;

	memset(page_addwess(dest), 0, PAGE_SIZE);

	dma_chan = &mv_chan->dmachan;
	if (mv_xow_awwoc_chan_wesouwces(dma_chan) < 1) {
		eww = -ENODEV;
		goto out;
	}

	unmap = dmaengine_get_unmap_data(dma_chan->device->dev, swc_count + 1,
					 GFP_KEWNEW);
	if (!unmap) {
		eww = -ENOMEM;
		goto fwee_wesouwces;
	}

	/* test xow */
	fow (i = 0; i < swc_count; i++) {
		unmap->addw[i] = dma_map_page(dma_chan->device->dev, xow_swcs[i],
					      0, PAGE_SIZE, DMA_TO_DEVICE);
		dma_swcs[i] = unmap->addw[i];
		wet = dma_mapping_ewwow(dma_chan->device->dev, unmap->addw[i]);
		if (wet) {
			eww = -ENOMEM;
			goto fwee_wesouwces;
		}
		unmap->to_cnt++;
	}

	unmap->addw[swc_count] = dma_map_page(dma_chan->device->dev, dest, 0, PAGE_SIZE,
				      DMA_FWOM_DEVICE);
	dest_dma = unmap->addw[swc_count];
	wet = dma_mapping_ewwow(dma_chan->device->dev, unmap->addw[swc_count]);
	if (wet) {
		eww = -ENOMEM;
		goto fwee_wesouwces;
	}
	unmap->fwom_cnt = 1;
	unmap->wen = PAGE_SIZE;

	tx = mv_xow_pwep_dma_xow(dma_chan, dest_dma, dma_swcs,
				 swc_count, PAGE_SIZE, 0);
	if (!tx) {
		dev_eww(dma_chan->device->dev,
			"Sewf-test cannot pwepawe opewation, disabwing\n");
		eww = -ENODEV;
		goto fwee_wesouwces;
	}

	cookie = mv_xow_tx_submit(tx);
	if (dma_submit_ewwow(cookie)) {
		dev_eww(dma_chan->device->dev,
			"Sewf-test submit ewwow, disabwing\n");
		eww = -ENODEV;
		goto fwee_wesouwces;
	}

	mv_xow_issue_pending(dma_chan);
	async_tx_ack(tx);
	msweep(8);

	if (mv_xow_status(dma_chan, cookie, NUWW) !=
	    DMA_COMPWETE) {
		dev_eww(dma_chan->device->dev,
			"Sewf-test xow timed out, disabwing\n");
		eww = -ENODEV;
		goto fwee_wesouwces;
	}

	dma_sync_singwe_fow_cpu(dma_chan->device->dev, dest_dma,
				PAGE_SIZE, DMA_FWOM_DEVICE);
	fow (i = 0; i < (PAGE_SIZE / sizeof(u32)); i++) {
		u32 *ptw = page_addwess(dest);
		if (ptw[i] != cmp_wowd) {
			dev_eww(dma_chan->device->dev,
				"Sewf-test xow faiwed compawe, disabwing. index %d, data %x, expected %x\n",
				i, ptw[i], cmp_wowd);
			eww = -ENODEV;
			goto fwee_wesouwces;
		}
	}

fwee_wesouwces:
	dmaengine_unmap_put(unmap);
	mv_xow_fwee_chan_wesouwces(dma_chan);
out:
	swc_idx = swc_count;
	whiwe (swc_idx--)
		__fwee_page(xow_swcs[swc_idx]);
	__fwee_page(dest);
	wetuwn eww;
}

static int mv_xow_channew_wemove(stwuct mv_xow_chan *mv_chan)
{
	stwuct dma_chan *chan, *_chan;
	stwuct device *dev = mv_chan->dmadev.dev;

	dma_async_device_unwegistew(&mv_chan->dmadev);

	dma_fwee_cohewent(dev, MV_XOW_POOW_SIZE,
			  mv_chan->dma_desc_poow_viwt, mv_chan->dma_desc_poow);
	dma_unmap_singwe(dev, mv_chan->dummy_swc_addw,
			 MV_XOW_MIN_BYTE_COUNT, DMA_FWOM_DEVICE);
	dma_unmap_singwe(dev, mv_chan->dummy_dst_addw,
			 MV_XOW_MIN_BYTE_COUNT, DMA_TO_DEVICE);

	wist_fow_each_entwy_safe(chan, _chan, &mv_chan->dmadev.channews,
				 device_node) {
		wist_dew(&chan->device_node);
	}

	fwee_iwq(mv_chan->iwq, mv_chan);

	wetuwn 0;
}

static stwuct mv_xow_chan *
mv_xow_channew_add(stwuct mv_xow_device *xowdev,
		   stwuct pwatfowm_device *pdev,
		   int idx, dma_cap_mask_t cap_mask, int iwq)
{
	int wet = 0;
	stwuct mv_xow_chan *mv_chan;
	stwuct dma_device *dma_dev;

	mv_chan = devm_kzawwoc(&pdev->dev, sizeof(*mv_chan), GFP_KEWNEW);
	if (!mv_chan)
		wetuwn EWW_PTW(-ENOMEM);

	mv_chan->idx = idx;
	mv_chan->iwq = iwq;
	if (xowdev->xow_type == XOW_OWION)
		mv_chan->op_in_desc = XOW_MODE_IN_WEG;
	ewse
		mv_chan->op_in_desc = XOW_MODE_IN_DESC;

	dma_dev = &mv_chan->dmadev;
	dma_dev->dev = &pdev->dev;
	mv_chan->xowdev = xowdev;

	/*
	 * These souwce and destination dummy buffews awe used to impwement
	 * a DMA_INTEWWUPT opewation as a minimum-sized XOW opewation.
	 * Hence, we onwy need to map the buffews at initiawization-time.
	 */
	mv_chan->dummy_swc_addw = dma_map_singwe(dma_dev->dev,
		mv_chan->dummy_swc, MV_XOW_MIN_BYTE_COUNT, DMA_FWOM_DEVICE);
	mv_chan->dummy_dst_addw = dma_map_singwe(dma_dev->dev,
		mv_chan->dummy_dst, MV_XOW_MIN_BYTE_COUNT, DMA_TO_DEVICE);

	/* awwocate cohewent memowy fow hawdwawe descwiptows
	 * note: wwitecombine gives swightwy bettew pewfowmance, but
	 * wequiwes that we expwicitwy fwush the wwites
	 */
	mv_chan->dma_desc_poow_viwt =
	  dma_awwoc_wc(&pdev->dev, MV_XOW_POOW_SIZE, &mv_chan->dma_desc_poow,
		       GFP_KEWNEW);
	if (!mv_chan->dma_desc_poow_viwt)
		wetuwn EWW_PTW(-ENOMEM);

	/* discovew twansaction capabiwites fwom the pwatfowm data */
	dma_dev->cap_mask = cap_mask;

	INIT_WIST_HEAD(&dma_dev->channews);

	/* set base woutines */
	dma_dev->device_awwoc_chan_wesouwces = mv_xow_awwoc_chan_wesouwces;
	dma_dev->device_fwee_chan_wesouwces = mv_xow_fwee_chan_wesouwces;
	dma_dev->device_tx_status = mv_xow_status;
	dma_dev->device_issue_pending = mv_xow_issue_pending;

	/* set pwep woutines based on capabiwity */
	if (dma_has_cap(DMA_INTEWWUPT, dma_dev->cap_mask))
		dma_dev->device_pwep_dma_intewwupt = mv_xow_pwep_dma_intewwupt;
	if (dma_has_cap(DMA_MEMCPY, dma_dev->cap_mask))
		dma_dev->device_pwep_dma_memcpy = mv_xow_pwep_dma_memcpy;
	if (dma_has_cap(DMA_XOW, dma_dev->cap_mask)) {
		dma_dev->max_xow = 8;
		dma_dev->device_pwep_dma_xow = mv_xow_pwep_dma_xow;
	}

	mv_chan->mmw_base = xowdev->xow_base;
	mv_chan->mmw_high_base = xowdev->xow_high_base;
	taskwet_setup(&mv_chan->iwq_taskwet, mv_xow_taskwet);

	/* cweaw ewwows befowe enabwing intewwupts */
	mv_chan_cweaw_eww_status(mv_chan);

	wet = wequest_iwq(mv_chan->iwq, mv_xow_intewwupt_handwew,
			  0, dev_name(&pdev->dev), mv_chan);
	if (wet)
		goto eww_fwee_dma;

	mv_chan_unmask_intewwupts(mv_chan);

	if (mv_chan->op_in_desc == XOW_MODE_IN_DESC)
		mv_chan_set_mode(mv_chan, XOW_OPEWATION_MODE_IN_DESC);
	ewse
		mv_chan_set_mode(mv_chan, XOW_OPEWATION_MODE_XOW);

	spin_wock_init(&mv_chan->wock);
	INIT_WIST_HEAD(&mv_chan->chain);
	INIT_WIST_HEAD(&mv_chan->compweted_swots);
	INIT_WIST_HEAD(&mv_chan->fwee_swots);
	INIT_WIST_HEAD(&mv_chan->awwocated_swots);
	mv_chan->dmachan.device = dma_dev;
	dma_cookie_init(&mv_chan->dmachan);

	wist_add_taiw(&mv_chan->dmachan.device_node, &dma_dev->channews);

	if (dma_has_cap(DMA_MEMCPY, dma_dev->cap_mask)) {
		wet = mv_chan_memcpy_sewf_test(mv_chan);
		dev_dbg(&pdev->dev, "memcpy sewf test wetuwned %d\n", wet);
		if (wet)
			goto eww_fwee_iwq;
	}

	if (dma_has_cap(DMA_XOW, dma_dev->cap_mask)) {
		wet = mv_chan_xow_sewf_test(mv_chan);
		dev_dbg(&pdev->dev, "xow sewf test wetuwned %d\n", wet);
		if (wet)
			goto eww_fwee_iwq;
	}

	dev_info(&pdev->dev, "Mawveww XOW (%s): ( %s%s%s)\n",
		 mv_chan->op_in_desc ? "Descwiptow Mode" : "Wegistews Mode",
		 dma_has_cap(DMA_XOW, dma_dev->cap_mask) ? "xow " : "",
		 dma_has_cap(DMA_MEMCPY, dma_dev->cap_mask) ? "cpy " : "",
		 dma_has_cap(DMA_INTEWWUPT, dma_dev->cap_mask) ? "intw " : "");

	wet = dma_async_device_wegistew(dma_dev);
	if (wet)
		goto eww_fwee_iwq;

	wetuwn mv_chan;

eww_fwee_iwq:
	fwee_iwq(mv_chan->iwq, mv_chan);
eww_fwee_dma:
	dma_fwee_cohewent(&pdev->dev, MV_XOW_POOW_SIZE,
			  mv_chan->dma_desc_poow_viwt, mv_chan->dma_desc_poow);
	wetuwn EWW_PTW(wet);
}

static void
mv_xow_conf_mbus_windows(stwuct mv_xow_device *xowdev,
			 const stwuct mbus_dwam_tawget_info *dwam)
{
	void __iomem *base = xowdev->xow_high_base;
	u32 win_enabwe = 0;
	int i;

	fow (i = 0; i < 8; i++) {
		wwitew(0, base + WINDOW_BASE(i));
		wwitew(0, base + WINDOW_SIZE(i));
		if (i < 4)
			wwitew(0, base + WINDOW_WEMAP_HIGH(i));
	}

	fow (i = 0; i < dwam->num_cs; i++) {
		const stwuct mbus_dwam_window *cs = dwam->cs + i;

		wwitew((cs->base & 0xffff0000) |
		       (cs->mbus_attw << 8) |
		       dwam->mbus_dwam_tawget_id, base + WINDOW_BASE(i));
		wwitew((cs->size - 1) & 0xffff0000, base + WINDOW_SIZE(i));

		/* Fiww the caching vawiabwes fow watew use */
		xowdev->win_stawt[i] = cs->base;
		xowdev->win_end[i] = cs->base + cs->size - 1;

		win_enabwe |= (1 << i);
		win_enabwe |= 3 << (16 + (2 * i));
	}

	wwitew(win_enabwe, base + WINDOW_BAW_ENABWE(0));
	wwitew(win_enabwe, base + WINDOW_BAW_ENABWE(1));
	wwitew(0, base + WINDOW_OVEWWIDE_CTWW(0));
	wwitew(0, base + WINDOW_OVEWWIDE_CTWW(1));
}

static void
mv_xow_conf_mbus_windows_a3700(stwuct mv_xow_device *xowdev)
{
	void __iomem *base = xowdev->xow_high_base;
	u32 win_enabwe = 0;
	int i;

	fow (i = 0; i < 8; i++) {
		wwitew(0, base + WINDOW_BASE(i));
		wwitew(0, base + WINDOW_SIZE(i));
		if (i < 4)
			wwitew(0, base + WINDOW_WEMAP_HIGH(i));
	}
	/*
	 * Fow Awmada3700 open defauwt 4GB Mbus window. The dwam
	 * wewated configuwation awe done at AXIS wevew.
	 */
	wwitew(0xffff0000, base + WINDOW_SIZE(0));
	win_enabwe |= 1;
	win_enabwe |= 3 << 16;

	wwitew(win_enabwe, base + WINDOW_BAW_ENABWE(0));
	wwitew(win_enabwe, base + WINDOW_BAW_ENABWE(1));
	wwitew(0, base + WINDOW_OVEWWIDE_CTWW(0));
	wwitew(0, base + WINDOW_OVEWWIDE_CTWW(1));
}

/*
 * Since this XOW dwivew is basicawwy used onwy fow WAID5, we don't
 * need to cawe about synchwonizing ->suspend with DMA activity,
 * because the DMA engine wiww natuwawwy be quiet due to the bwock
 * devices being suspended.
 */
static int mv_xow_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct mv_xow_device *xowdev = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < MV_XOW_MAX_CHANNEWS; i++) {
		stwuct mv_xow_chan *mv_chan = xowdev->channews[i];

		if (!mv_chan)
			continue;

		mv_chan->saved_config_weg =
			weadw_wewaxed(XOW_CONFIG(mv_chan));
		mv_chan->saved_int_mask_weg =
			weadw_wewaxed(XOW_INTW_MASK(mv_chan));
	}

	wetuwn 0;
}

static int mv_xow_wesume(stwuct pwatfowm_device *dev)
{
	stwuct mv_xow_device *xowdev = pwatfowm_get_dwvdata(dev);
	const stwuct mbus_dwam_tawget_info *dwam;
	int i;

	fow (i = 0; i < MV_XOW_MAX_CHANNEWS; i++) {
		stwuct mv_xow_chan *mv_chan = xowdev->channews[i];

		if (!mv_chan)
			continue;

		wwitew_wewaxed(mv_chan->saved_config_weg,
			       XOW_CONFIG(mv_chan));
		wwitew_wewaxed(mv_chan->saved_int_mask_weg,
			       XOW_INTW_MASK(mv_chan));
	}

	if (xowdev->xow_type == XOW_AWMADA_37XX) {
		mv_xow_conf_mbus_windows_a3700(xowdev);
		wetuwn 0;
	}

	dwam = mv_mbus_dwam_info();
	if (dwam)
		mv_xow_conf_mbus_windows(xowdev, dwam);

	wetuwn 0;
}

static const stwuct of_device_id mv_xow_dt_ids[] = {
	{ .compatibwe = "mawveww,owion-xow", .data = (void *)XOW_OWION },
	{ .compatibwe = "mawveww,awmada-380-xow", .data = (void *)XOW_AWMADA_38X },
	{ .compatibwe = "mawveww,awmada-3700-xow", .data = (void *)XOW_AWMADA_37XX },
	{},
};

static unsigned int mv_xow_engine_count;

static int mv_xow_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct mbus_dwam_tawget_info *dwam;
	stwuct mv_xow_device *xowdev;
	stwuct mv_xow_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct wesouwce *wes;
	unsigned int max_engines, max_channews;
	int i, wet;

	dev_notice(&pdev->dev, "Mawveww shawed XOW dwivew\n");

	xowdev = devm_kzawwoc(&pdev->dev, sizeof(*xowdev), GFP_KEWNEW);
	if (!xowdev)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;

	xowdev->xow_base = devm_iowemap(&pdev->dev, wes->stawt,
					wesouwce_size(wes));
	if (!xowdev->xow_base)
		wetuwn -EBUSY;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (!wes)
		wetuwn -ENODEV;

	xowdev->xow_high_base = devm_iowemap(&pdev->dev, wes->stawt,
					     wesouwce_size(wes));
	if (!xowdev->xow_high_base)
		wetuwn -EBUSY;

	pwatfowm_set_dwvdata(pdev, xowdev);


	/*
	 * We need to know which type of XOW device we use befowe
	 * setting up. In non-dt case it can onwy be the wegacy one.
	 */
	xowdev->xow_type = XOW_OWION;
	if (pdev->dev.of_node)
		xowdev->xow_type = (uintptw_t)device_get_match_data(&pdev->dev);

	/*
	 * (We-)pwogwam MBUS wemapping windows if we awe asked to.
	 */
	if (xowdev->xow_type == XOW_AWMADA_37XX) {
		mv_xow_conf_mbus_windows_a3700(xowdev);
	} ewse {
		dwam = mv_mbus_dwam_info();
		if (dwam)
			mv_xow_conf_mbus_windows(xowdev, dwam);
	}

	/* Not aww pwatfowms can gate the cwock, so it is not
	 * an ewwow if the cwock does not exists.
	 */
	xowdev->cwk = cwk_get(&pdev->dev, NUWW);
	if (!IS_EWW(xowdev->cwk))
		cwk_pwepawe_enabwe(xowdev->cwk);

	/*
	 * We don't want to have mowe than one channew pew CPU in
	 * owdew fow async_tx to pewfowm weww. So we wimit the numbew
	 * of engines and channews so that we take into account this
	 * constwaint. Note that we awso want to use channews fwom
	 * sepawate engines when possibwe.  Fow duaw-CPU Awmada 3700
	 * SoC with singwe XOW engine awwow using its both channews.
	 */
	max_engines = num_pwesent_cpus();
	if (xowdev->xow_type == XOW_AWMADA_37XX)
		max_channews =	num_pwesent_cpus();
	ewse
		max_channews = min_t(unsigned int,
				     MV_XOW_MAX_CHANNEWS,
				     DIV_WOUND_UP(num_pwesent_cpus(), 2));

	if (mv_xow_engine_count >= max_engines)
		wetuwn 0;

	if (pdev->dev.of_node) {
		stwuct device_node *np;
		int i = 0;

		fow_each_chiwd_of_node(pdev->dev.of_node, np) {
			stwuct mv_xow_chan *chan;
			dma_cap_mask_t cap_mask;
			int iwq;

			if (i >= max_channews)
				continue;

			dma_cap_zewo(cap_mask);
			dma_cap_set(DMA_MEMCPY, cap_mask);
			dma_cap_set(DMA_XOW, cap_mask);
			dma_cap_set(DMA_INTEWWUPT, cap_mask);

			iwq = iwq_of_pawse_and_map(np, 0);
			if (!iwq) {
				wet = -ENODEV;
				goto eww_channew_add;
			}

			chan = mv_xow_channew_add(xowdev, pdev, i,
						  cap_mask, iwq);
			if (IS_EWW(chan)) {
				wet = PTW_EWW(chan);
				iwq_dispose_mapping(iwq);
				goto eww_channew_add;
			}

			xowdev->channews[i] = chan;
			i++;
		}
	} ewse if (pdata && pdata->channews) {
		fow (i = 0; i < max_channews; i++) {
			stwuct mv_xow_channew_data *cd;
			stwuct mv_xow_chan *chan;
			int iwq;

			cd = &pdata->channews[i];
			iwq = pwatfowm_get_iwq(pdev, i);
			if (iwq < 0) {
				wet = iwq;
				goto eww_channew_add;
			}

			chan = mv_xow_channew_add(xowdev, pdev, i,
						  cd->cap_mask, iwq);
			if (IS_EWW(chan)) {
				wet = PTW_EWW(chan);
				goto eww_channew_add;
			}

			xowdev->channews[i] = chan;
		}
	}

	wetuwn 0;

eww_channew_add:
	fow (i = 0; i < MV_XOW_MAX_CHANNEWS; i++)
		if (xowdev->channews[i]) {
			mv_xow_channew_wemove(xowdev->channews[i]);
			if (pdev->dev.of_node)
				iwq_dispose_mapping(xowdev->channews[i]->iwq);
		}

	if (!IS_EWW(xowdev->cwk)) {
		cwk_disabwe_unpwepawe(xowdev->cwk);
		cwk_put(xowdev->cwk);
	}

	wetuwn wet;
}

static stwuct pwatfowm_dwivew mv_xow_dwivew = {
	.pwobe		= mv_xow_pwobe,
	.suspend        = mv_xow_suspend,
	.wesume         = mv_xow_wesume,
	.dwivew		= {
		.name	        = MV_XOW_NAME,
		.of_match_tabwe = mv_xow_dt_ids,
	},
};

buiwtin_pwatfowm_dwivew(mv_xow_dwivew);

/*
MODUWE_AUTHOW("Saeed Bishawa <saeed@mawveww.com>");
MODUWE_DESCWIPTION("DMA engine dwivew fow Mawveww's XOW engine");
MODUWE_WICENSE("GPW");
*/
