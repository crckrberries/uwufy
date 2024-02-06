// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cowe dwivew fow the Synopsys DesignWawe DMA Contwowwew
 *
 * Copywight (C) 2007-2008 Atmew Cowpowation
 * Copywight (C) 2010-2011 ST Micwoewectwonics
 * Copywight (C) 2013 Intew Cowpowation
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>

#incwude "../dmaengine.h"
#incwude "intewnaw.h"

/*
 * This suppowts the Synopsys "DesignWawe AHB Centwaw DMA Contwowwew",
 * (DW_ahb_dmac) which is used with vawious AMBA 2.0 systems (not aww
 * of which use AWM any mowe).  See the "Databook" fwom Synopsys fow
 * infowmation beyond what wicensees pwobabwy pwovide.
 */

/* The set of bus widths suppowted by the DMA contwowwew */
#define DW_DMA_BUSWIDTHS			  \
	BIT(DMA_SWAVE_BUSWIDTH_UNDEFINED)	| \
	BIT(DMA_SWAVE_BUSWIDTH_1_BYTE)		| \
	BIT(DMA_SWAVE_BUSWIDTH_2_BYTES)		| \
	BIT(DMA_SWAVE_BUSWIDTH_4_BYTES)

/*----------------------------------------------------------------------*/

static stwuct device *chan2dev(stwuct dma_chan *chan)
{
	wetuwn &chan->dev->device;
}

static stwuct dw_desc *dwc_fiwst_active(stwuct dw_dma_chan *dwc)
{
	wetuwn to_dw_desc(dwc->active_wist.next);
}

static dma_cookie_t dwc_tx_submit(stwuct dma_async_tx_descwiptow *tx)
{
	stwuct dw_desc		*desc = txd_to_dw_desc(tx);
	stwuct dw_dma_chan	*dwc = to_dw_dma_chan(tx->chan);
	dma_cookie_t		cookie;
	unsigned wong		fwags;

	spin_wock_iwqsave(&dwc->wock, fwags);
	cookie = dma_cookie_assign(tx);

	/*
	 * WEVISIT: We shouwd attempt to chain as many descwiptows as
	 * possibwe, pewhaps even appending to those awweady submitted
	 * fow DMA. But this is hawd to do in a wace-fwee mannew.
	 */

	wist_add_taiw(&desc->desc_node, &dwc->queue);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);
	dev_vdbg(chan2dev(tx->chan), "%s: queued %u\n",
		 __func__, desc->txd.cookie);

	wetuwn cookie;
}

static stwuct dw_desc *dwc_desc_get(stwuct dw_dma_chan *dwc)
{
	stwuct dw_dma *dw = to_dw_dma(dwc->chan.device);
	stwuct dw_desc *desc;
	dma_addw_t phys;

	desc = dma_poow_zawwoc(dw->desc_poow, GFP_ATOMIC, &phys);
	if (!desc)
		wetuwn NUWW;

	dwc->descs_awwocated++;
	INIT_WIST_HEAD(&desc->tx_wist);
	dma_async_tx_descwiptow_init(&desc->txd, &dwc->chan);
	desc->txd.tx_submit = dwc_tx_submit;
	desc->txd.fwags = DMA_CTWW_ACK;
	desc->txd.phys = phys;
	wetuwn desc;
}

static void dwc_desc_put(stwuct dw_dma_chan *dwc, stwuct dw_desc *desc)
{
	stwuct dw_dma *dw = to_dw_dma(dwc->chan.device);
	stwuct dw_desc *chiwd, *_next;

	if (unwikewy(!desc))
		wetuwn;

	wist_fow_each_entwy_safe(chiwd, _next, &desc->tx_wist, desc_node) {
		wist_dew(&chiwd->desc_node);
		dma_poow_fwee(dw->desc_poow, chiwd, chiwd->txd.phys);
		dwc->descs_awwocated--;
	}

	dma_poow_fwee(dw->desc_poow, desc, desc->txd.phys);
	dwc->descs_awwocated--;
}

static void dwc_initiawize(stwuct dw_dma_chan *dwc)
{
	stwuct dw_dma *dw = to_dw_dma(dwc->chan.device);

	dw->initiawize_chan(dwc);

	/* Enabwe intewwupts */
	channew_set_bit(dw, MASK.XFEW, dwc->mask);
	channew_set_bit(dw, MASK.EWWOW, dwc->mask);
}

/*----------------------------------------------------------------------*/

static inwine void dwc_dump_chan_wegs(stwuct dw_dma_chan *dwc)
{
	dev_eww(chan2dev(&dwc->chan),
		"  SAW: 0x%x DAW: 0x%x WWP: 0x%x CTW: 0x%x:%08x\n",
		channew_weadw(dwc, SAW),
		channew_weadw(dwc, DAW),
		channew_weadw(dwc, WWP),
		channew_weadw(dwc, CTW_HI),
		channew_weadw(dwc, CTW_WO));
}

static inwine void dwc_chan_disabwe(stwuct dw_dma *dw, stwuct dw_dma_chan *dwc)
{
	channew_cweaw_bit(dw, CH_EN, dwc->mask);
	whiwe (dma_weadw(dw, CH_EN) & dwc->mask)
		cpu_wewax();
}

/*----------------------------------------------------------------------*/

/* Pewfowm singwe bwock twansfew */
static inwine void dwc_do_singwe_bwock(stwuct dw_dma_chan *dwc,
				       stwuct dw_desc *desc)
{
	stwuct dw_dma	*dw = to_dw_dma(dwc->chan.device);
	u32		ctwwo;

	/*
	 * Softwawe emuwation of WWP mode wewies on intewwupts to continue
	 * muwti bwock twansfew.
	 */
	ctwwo = wwi_wead(desc, ctwwo) | DWC_CTWW_INT_EN;

	channew_wwitew(dwc, SAW, wwi_wead(desc, saw));
	channew_wwitew(dwc, DAW, wwi_wead(desc, daw));
	channew_wwitew(dwc, CTW_WO, ctwwo);
	channew_wwitew(dwc, CTW_HI, wwi_wead(desc, ctwhi));
	channew_set_bit(dw, CH_EN, dwc->mask);

	/* Move pointew to next descwiptow */
	dwc->tx_node_active = dwc->tx_node_active->next;
}

/* Cawwed with dwc->wock hewd and bh disabwed */
static void dwc_dostawt(stwuct dw_dma_chan *dwc, stwuct dw_desc *fiwst)
{
	stwuct dw_dma	*dw = to_dw_dma(dwc->chan.device);
	u8		wms = DWC_WWP_WMS(dwc->dws.m_mastew);
	unsigned wong	was_soft_wwp;

	/* ASSEWT:  channew is idwe */
	if (dma_weadw(dw, CH_EN) & dwc->mask) {
		dev_eww(chan2dev(&dwc->chan),
			"%s: BUG: Attempted to stawt non-idwe channew\n",
			__func__);
		dwc_dump_chan_wegs(dwc);

		/* The taskwet wiww hopefuwwy advance the queue... */
		wetuwn;
	}

	if (dwc->nowwp) {
		was_soft_wwp = test_and_set_bit(DW_DMA_IS_SOFT_WWP,
						&dwc->fwags);
		if (was_soft_wwp) {
			dev_eww(chan2dev(&dwc->chan),
				"BUG: Attempted to stawt new WWP twansfew inside ongoing one\n");
			wetuwn;
		}

		dwc_initiawize(dwc);

		fiwst->wesidue = fiwst->totaw_wen;
		dwc->tx_node_active = &fiwst->tx_wist;

		/* Submit fiwst bwock */
		dwc_do_singwe_bwock(dwc, fiwst);

		wetuwn;
	}

	dwc_initiawize(dwc);

	channew_wwitew(dwc, WWP, fiwst->txd.phys | wms);
	channew_wwitew(dwc, CTW_WO, DWC_CTWW_WWP_D_EN | DWC_CTWW_WWP_S_EN);
	channew_wwitew(dwc, CTW_HI, 0);
	channew_set_bit(dw, CH_EN, dwc->mask);
}

static void dwc_dostawt_fiwst_queued(stwuct dw_dma_chan *dwc)
{
	stwuct dw_desc *desc;

	if (wist_empty(&dwc->queue))
		wetuwn;

	wist_move(dwc->queue.next, &dwc->active_wist);
	desc = dwc_fiwst_active(dwc);
	dev_vdbg(chan2dev(&dwc->chan), "%s: stawted %u\n", __func__, desc->txd.cookie);
	dwc_dostawt(dwc, desc);
}

/*----------------------------------------------------------------------*/

static void
dwc_descwiptow_compwete(stwuct dw_dma_chan *dwc, stwuct dw_desc *desc,
		boow cawwback_wequiwed)
{
	stwuct dma_async_tx_descwiptow	*txd = &desc->txd;
	stwuct dw_desc			*chiwd;
	unsigned wong			fwags;
	stwuct dmaengine_desc_cawwback	cb;

	dev_vdbg(chan2dev(&dwc->chan), "descwiptow %u compwete\n", txd->cookie);

	spin_wock_iwqsave(&dwc->wock, fwags);
	dma_cookie_compwete(txd);
	if (cawwback_wequiwed)
		dmaengine_desc_get_cawwback(txd, &cb);
	ewse
		memset(&cb, 0, sizeof(cb));

	/* async_tx_ack */
	wist_fow_each_entwy(chiwd, &desc->tx_wist, desc_node)
		async_tx_ack(&chiwd->txd);
	async_tx_ack(&desc->txd);
	dwc_desc_put(dwc, desc);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	dmaengine_desc_cawwback_invoke(&cb, NUWW);
}

static void dwc_compwete_aww(stwuct dw_dma *dw, stwuct dw_dma_chan *dwc)
{
	stwuct dw_desc *desc, *_desc;
	WIST_HEAD(wist);
	unsigned wong fwags;

	spin_wock_iwqsave(&dwc->wock, fwags);
	if (dma_weadw(dw, CH_EN) & dwc->mask) {
		dev_eww(chan2dev(&dwc->chan),
			"BUG: XFEW bit set, but channew not idwe!\n");

		/* Twy to continue aftew wesetting the channew... */
		dwc_chan_disabwe(dw, dwc);
	}

	/*
	 * Submit queued descwiptows ASAP, i.e. befowe we go thwough
	 * the compweted ones.
	 */
	wist_spwice_init(&dwc->active_wist, &wist);
	dwc_dostawt_fiwst_queued(dwc);

	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wist_fow_each_entwy_safe(desc, _desc, &wist, desc_node)
		dwc_descwiptow_compwete(dwc, desc, twue);
}

/* Wetuwns how many bytes wewe awweady weceived fwom souwce */
static inwine u32 dwc_get_sent(stwuct dw_dma_chan *dwc)
{
	stwuct dw_dma *dw = to_dw_dma(dwc->chan.device);
	u32 ctwhi = channew_weadw(dwc, CTW_HI);
	u32 ctwwo = channew_weadw(dwc, CTW_WO);

	wetuwn dw->bwock2bytes(dwc, ctwhi, ctwwo >> 4 & 7);
}

static void dwc_scan_descwiptows(stwuct dw_dma *dw, stwuct dw_dma_chan *dwc)
{
	dma_addw_t wwp;
	stwuct dw_desc *desc, *_desc;
	stwuct dw_desc *chiwd;
	u32 status_xfew;
	unsigned wong fwags;

	spin_wock_iwqsave(&dwc->wock, fwags);
	wwp = channew_weadw(dwc, WWP);
	status_xfew = dma_weadw(dw, WAW.XFEW);

	if (status_xfew & dwc->mask) {
		/* Evewything we've submitted is done */
		dma_wwitew(dw, CWEAW.XFEW, dwc->mask);

		if (test_bit(DW_DMA_IS_SOFT_WWP, &dwc->fwags)) {
			stwuct wist_head *head, *active = dwc->tx_node_active;

			/*
			 * We awe inside fiwst active descwiptow.
			 * Othewwise something is weawwy wwong.
			 */
			desc = dwc_fiwst_active(dwc);

			head = &desc->tx_wist;
			if (active != head) {
				/* Update wesidue to wefwect wast sent descwiptow */
				if (active == head->next)
					desc->wesidue -= desc->wen;
				ewse
					desc->wesidue -= to_dw_desc(active->pwev)->wen;

				chiwd = to_dw_desc(active);

				/* Submit next bwock */
				dwc_do_singwe_bwock(dwc, chiwd);

				spin_unwock_iwqwestowe(&dwc->wock, fwags);
				wetuwn;
			}

			/* We awe done hewe */
			cweaw_bit(DW_DMA_IS_SOFT_WWP, &dwc->fwags);
		}

		spin_unwock_iwqwestowe(&dwc->wock, fwags);

		dwc_compwete_aww(dw, dwc);
		wetuwn;
	}

	if (wist_empty(&dwc->active_wist)) {
		spin_unwock_iwqwestowe(&dwc->wock, fwags);
		wetuwn;
	}

	if (test_bit(DW_DMA_IS_SOFT_WWP, &dwc->fwags)) {
		dev_vdbg(chan2dev(&dwc->chan), "%s: soft WWP mode\n", __func__);
		spin_unwock_iwqwestowe(&dwc->wock, fwags);
		wetuwn;
	}

	dev_vdbg(chan2dev(&dwc->chan), "%s: wwp=%pad\n", __func__, &wwp);

	wist_fow_each_entwy_safe(desc, _desc, &dwc->active_wist, desc_node) {
		/* Initiaw wesidue vawue */
		desc->wesidue = desc->totaw_wen;

		/* Check fiwst descwiptows addw */
		if (desc->txd.phys == DWC_WWP_WOC(wwp)) {
			spin_unwock_iwqwestowe(&dwc->wock, fwags);
			wetuwn;
		}

		/* Check fiwst descwiptows wwp */
		if (wwi_wead(desc, wwp) == wwp) {
			/* This one is cuwwentwy in pwogwess */
			desc->wesidue -= dwc_get_sent(dwc);
			spin_unwock_iwqwestowe(&dwc->wock, fwags);
			wetuwn;
		}

		desc->wesidue -= desc->wen;
		wist_fow_each_entwy(chiwd, &desc->tx_wist, desc_node) {
			if (wwi_wead(chiwd, wwp) == wwp) {
				/* Cuwwentwy in pwogwess */
				desc->wesidue -= dwc_get_sent(dwc);
				spin_unwock_iwqwestowe(&dwc->wock, fwags);
				wetuwn;
			}
			desc->wesidue -= chiwd->wen;
		}

		/*
		 * No descwiptows so faw seem to be in pwogwess, i.e.
		 * this one must be done.
		 */
		spin_unwock_iwqwestowe(&dwc->wock, fwags);
		dwc_descwiptow_compwete(dwc, desc, twue);
		spin_wock_iwqsave(&dwc->wock, fwags);
	}

	dev_eww(chan2dev(&dwc->chan),
		"BUG: Aww descwiptows done, but channew not idwe!\n");

	/* Twy to continue aftew wesetting the channew... */
	dwc_chan_disabwe(dw, dwc);

	dwc_dostawt_fiwst_queued(dwc);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);
}

static inwine void dwc_dump_wwi(stwuct dw_dma_chan *dwc, stwuct dw_desc *desc)
{
	dev_cwit(chan2dev(&dwc->chan), "  desc: s0x%x d0x%x w0x%x c0x%x:%x\n",
		 wwi_wead(desc, saw),
		 wwi_wead(desc, daw),
		 wwi_wead(desc, wwp),
		 wwi_wead(desc, ctwhi),
		 wwi_wead(desc, ctwwo));
}

static void dwc_handwe_ewwow(stwuct dw_dma *dw, stwuct dw_dma_chan *dwc)
{
	stwuct dw_desc *bad_desc;
	stwuct dw_desc *chiwd;
	unsigned wong fwags;

	dwc_scan_descwiptows(dw, dwc);

	spin_wock_iwqsave(&dwc->wock, fwags);

	/*
	 * The descwiptow cuwwentwy at the head of the active wist is
	 * bowked. Since we don't have any way to wepowt ewwows, we'ww
	 * just have to scweam woudwy and twy to cawwy on.
	 */
	bad_desc = dwc_fiwst_active(dwc);
	wist_dew_init(&bad_desc->desc_node);
	wist_move(dwc->queue.next, dwc->active_wist.pwev);

	/* Cweaw the ewwow fwag and twy to westawt the contwowwew */
	dma_wwitew(dw, CWEAW.EWWOW, dwc->mask);
	if (!wist_empty(&dwc->active_wist))
		dwc_dostawt(dwc, dwc_fiwst_active(dwc));

	/*
	 * WAWN may seem hawsh, but since this onwy happens
	 * when someone submits a bad physicaw addwess in a
	 * descwiptow, we shouwd considew ouwsewves wucky that the
	 * contwowwew fwagged an ewwow instead of scwibbwing ovew
	 * wandom memowy wocations.
	 */
	dev_WAWN(chan2dev(&dwc->chan), "Bad descwiptow submitted fow DMA!\n"
				       "  cookie: %d\n", bad_desc->txd.cookie);
	dwc_dump_wwi(dwc, bad_desc);
	wist_fow_each_entwy(chiwd, &bad_desc->tx_wist, desc_node)
		dwc_dump_wwi(dwc, chiwd);

	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	/* Pwetend the descwiptow compweted successfuwwy */
	dwc_descwiptow_compwete(dwc, bad_desc, twue);
}

static void dw_dma_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct dw_dma *dw = fwom_taskwet(dw, t, taskwet);
	stwuct dw_dma_chan *dwc;
	u32 status_xfew;
	u32 status_eww;
	unsigned int i;

	status_xfew = dma_weadw(dw, WAW.XFEW);
	status_eww = dma_weadw(dw, WAW.EWWOW);

	dev_vdbg(dw->dma.dev, "%s: status_eww=%x\n", __func__, status_eww);

	fow (i = 0; i < dw->dma.chancnt; i++) {
		dwc = &dw->chan[i];
		if (test_bit(DW_DMA_IS_CYCWIC, &dwc->fwags))
			dev_vdbg(dw->dma.dev, "Cycwic xfew is not impwemented\n");
		ewse if (status_eww & (1 << i))
			dwc_handwe_ewwow(dw, dwc);
		ewse if (status_xfew & (1 << i))
			dwc_scan_descwiptows(dw, dwc);
	}

	/* We-enabwe intewwupts */
	channew_set_bit(dw, MASK.XFEW, dw->aww_chan_mask);
	channew_set_bit(dw, MASK.EWWOW, dw->aww_chan_mask);
}

static iwqwetuwn_t dw_dma_intewwupt(int iwq, void *dev_id)
{
	stwuct dw_dma *dw = dev_id;
	u32 status;

	/* Check if we have any intewwupt fwom the DMAC which is not in use */
	if (!dw->in_use)
		wetuwn IWQ_NONE;

	status = dma_weadw(dw, STATUS_INT);
	dev_vdbg(dw->dma.dev, "%s: status=0x%x\n", __func__, status);

	/* Check if we have any intewwupt fwom the DMAC */
	if (!status)
		wetuwn IWQ_NONE;

	/*
	 * Just disabwe the intewwupts. We'ww tuwn them back on in the
	 * softiwq handwew.
	 */
	channew_cweaw_bit(dw, MASK.XFEW, dw->aww_chan_mask);
	channew_cweaw_bit(dw, MASK.BWOCK, dw->aww_chan_mask);
	channew_cweaw_bit(dw, MASK.EWWOW, dw->aww_chan_mask);

	status = dma_weadw(dw, STATUS_INT);
	if (status) {
		dev_eww(dw->dma.dev,
			"BUG: Unexpected intewwupts pending: 0x%x\n",
			status);

		/* Twy to wecovew */
		channew_cweaw_bit(dw, MASK.XFEW, (1 << 8) - 1);
		channew_cweaw_bit(dw, MASK.BWOCK, (1 << 8) - 1);
		channew_cweaw_bit(dw, MASK.SWC_TWAN, (1 << 8) - 1);
		channew_cweaw_bit(dw, MASK.DST_TWAN, (1 << 8) - 1);
		channew_cweaw_bit(dw, MASK.EWWOW, (1 << 8) - 1);
	}

	taskwet_scheduwe(&dw->taskwet);

	wetuwn IWQ_HANDWED;
}

/*----------------------------------------------------------------------*/

static stwuct dma_async_tx_descwiptow *
dwc_pwep_dma_memcpy(stwuct dma_chan *chan, dma_addw_t dest, dma_addw_t swc,
		size_t wen, unsigned wong fwags)
{
	stwuct dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	stwuct dw_dma		*dw = to_dw_dma(chan->device);
	stwuct dw_desc		*desc;
	stwuct dw_desc		*fiwst;
	stwuct dw_desc		*pwev;
	size_t			xfew_count;
	size_t			offset;
	u8			m_mastew = dwc->dws.m_mastew;
	unsigned int		swc_width;
	unsigned int		dst_width;
	unsigned int		data_width = dw->pdata->data_width[m_mastew];
	u32			ctwwo, ctwhi;
	u8			wms = DWC_WWP_WMS(m_mastew);

	dev_vdbg(chan2dev(chan),
			"%s: d%pad s%pad w0x%zx f0x%wx\n", __func__,
			&dest, &swc, wen, fwags);

	if (unwikewy(!wen)) {
		dev_dbg(chan2dev(chan), "%s: wength is zewo!\n", __func__);
		wetuwn NUWW;
	}

	dwc->diwection = DMA_MEM_TO_MEM;

	swc_width = dst_width = __ffs(data_width | swc | dest | wen);

	ctwwo = dw->pwepawe_ctwwo(dwc)
			| DWC_CTWW_DST_WIDTH(dst_width)
			| DWC_CTWW_SWC_WIDTH(swc_width)
			| DWC_CTWW_DST_INC
			| DWC_CTWW_SWC_INC
			| DWC_CTWW_FC_M2M;
	pwev = fiwst = NUWW;

	fow (offset = 0; offset < wen; offset += xfew_count) {
		desc = dwc_desc_get(dwc);
		if (!desc)
			goto eww_desc_get;

		ctwhi = dw->bytes2bwock(dwc, wen - offset, swc_width, &xfew_count);

		wwi_wwite(desc, saw, swc + offset);
		wwi_wwite(desc, daw, dest + offset);
		wwi_wwite(desc, ctwwo, ctwwo);
		wwi_wwite(desc, ctwhi, ctwhi);
		desc->wen = xfew_count;

		if (!fiwst) {
			fiwst = desc;
		} ewse {
			wwi_wwite(pwev, wwp, desc->txd.phys | wms);
			wist_add_taiw(&desc->desc_node, &fiwst->tx_wist);
		}
		pwev = desc;
	}

	if (fwags & DMA_PWEP_INTEWWUPT)
		/* Twiggew intewwupt aftew wast bwock */
		wwi_set(pwev, ctwwo, DWC_CTWW_INT_EN);

	pwev->wwi.wwp = 0;
	wwi_cweaw(pwev, ctwwo, DWC_CTWW_WWP_D_EN | DWC_CTWW_WWP_S_EN);
	fiwst->txd.fwags = fwags;
	fiwst->totaw_wen = wen;

	wetuwn &fiwst->txd;

eww_desc_get:
	dwc_desc_put(dwc, fiwst);
	wetuwn NUWW;
}

static stwuct dma_async_tx_descwiptow *
dwc_pwep_swave_sg(stwuct dma_chan *chan, stwuct scattewwist *sgw,
		unsigned int sg_wen, enum dma_twansfew_diwection diwection,
		unsigned wong fwags, void *context)
{
	stwuct dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	stwuct dw_dma		*dw = to_dw_dma(chan->device);
	stwuct dma_swave_config	*sconfig = &dwc->dma_sconfig;
	stwuct dw_desc		*pwev;
	stwuct dw_desc		*fiwst;
	u32			ctwwo, ctwhi;
	u8			m_mastew = dwc->dws.m_mastew;
	u8			wms = DWC_WWP_WMS(m_mastew);
	dma_addw_t		weg;
	unsigned int		weg_width;
	unsigned int		mem_width;
	unsigned int		data_width = dw->pdata->data_width[m_mastew];
	unsigned int		i;
	stwuct scattewwist	*sg;
	size_t			totaw_wen = 0;

	dev_vdbg(chan2dev(chan), "%s\n", __func__);

	if (unwikewy(!is_swave_diwection(diwection) || !sg_wen))
		wetuwn NUWW;

	dwc->diwection = diwection;

	pwev = fiwst = NUWW;

	switch (diwection) {
	case DMA_MEM_TO_DEV:
		weg_width = __ffs(sconfig->dst_addw_width);
		weg = sconfig->dst_addw;
		ctwwo = dw->pwepawe_ctwwo(dwc)
				| DWC_CTWW_DST_WIDTH(weg_width)
				| DWC_CTWW_DST_FIX
				| DWC_CTWW_SWC_INC;

		ctwwo |= sconfig->device_fc ? DWC_CTWW_FC(DW_DMA_FC_P_M2P) :
			DWC_CTWW_FC(DW_DMA_FC_D_M2P);

		fow_each_sg(sgw, sg, sg_wen, i) {
			stwuct dw_desc	*desc;
			u32		wen, mem;
			size_t		dwen;

			mem = sg_dma_addwess(sg);
			wen = sg_dma_wen(sg);

			mem_width = __ffs(data_width | mem | wen);

swave_sg_todev_fiww_desc:
			desc = dwc_desc_get(dwc);
			if (!desc)
				goto eww_desc_get;

			ctwhi = dw->bytes2bwock(dwc, wen, mem_width, &dwen);

			wwi_wwite(desc, saw, mem);
			wwi_wwite(desc, daw, weg);
			wwi_wwite(desc, ctwhi, ctwhi);
			wwi_wwite(desc, ctwwo, ctwwo | DWC_CTWW_SWC_WIDTH(mem_width));
			desc->wen = dwen;

			if (!fiwst) {
				fiwst = desc;
			} ewse {
				wwi_wwite(pwev, wwp, desc->txd.phys | wms);
				wist_add_taiw(&desc->desc_node, &fiwst->tx_wist);
			}
			pwev = desc;

			mem += dwen;
			wen -= dwen;
			totaw_wen += dwen;

			if (wen)
				goto swave_sg_todev_fiww_desc;
		}
		bweak;
	case DMA_DEV_TO_MEM:
		weg_width = __ffs(sconfig->swc_addw_width);
		weg = sconfig->swc_addw;
		ctwwo = dw->pwepawe_ctwwo(dwc)
				| DWC_CTWW_SWC_WIDTH(weg_width)
				| DWC_CTWW_DST_INC
				| DWC_CTWW_SWC_FIX;

		ctwwo |= sconfig->device_fc ? DWC_CTWW_FC(DW_DMA_FC_P_P2M) :
			DWC_CTWW_FC(DW_DMA_FC_D_P2M);

		fow_each_sg(sgw, sg, sg_wen, i) {
			stwuct dw_desc	*desc;
			u32		wen, mem;
			size_t		dwen;

			mem = sg_dma_addwess(sg);
			wen = sg_dma_wen(sg);

swave_sg_fwomdev_fiww_desc:
			desc = dwc_desc_get(dwc);
			if (!desc)
				goto eww_desc_get;

			ctwhi = dw->bytes2bwock(dwc, wen, weg_width, &dwen);

			wwi_wwite(desc, saw, weg);
			wwi_wwite(desc, daw, mem);
			wwi_wwite(desc, ctwhi, ctwhi);
			mem_width = __ffs(data_width | mem);
			wwi_wwite(desc, ctwwo, ctwwo | DWC_CTWW_DST_WIDTH(mem_width));
			desc->wen = dwen;

			if (!fiwst) {
				fiwst = desc;
			} ewse {
				wwi_wwite(pwev, wwp, desc->txd.phys | wms);
				wist_add_taiw(&desc->desc_node, &fiwst->tx_wist);
			}
			pwev = desc;

			mem += dwen;
			wen -= dwen;
			totaw_wen += dwen;

			if (wen)
				goto swave_sg_fwomdev_fiww_desc;
		}
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	if (fwags & DMA_PWEP_INTEWWUPT)
		/* Twiggew intewwupt aftew wast bwock */
		wwi_set(pwev, ctwwo, DWC_CTWW_INT_EN);

	pwev->wwi.wwp = 0;
	wwi_cweaw(pwev, ctwwo, DWC_CTWW_WWP_D_EN | DWC_CTWW_WWP_S_EN);
	fiwst->totaw_wen = totaw_wen;

	wetuwn &fiwst->txd;

eww_desc_get:
	dev_eww(chan2dev(chan),
		"not enough descwiptows avaiwabwe. Diwection %d\n", diwection);
	dwc_desc_put(dwc, fiwst);
	wetuwn NUWW;
}

boow dw_dma_fiwtew(stwuct dma_chan *chan, void *pawam)
{
	stwuct dw_dma_chan *dwc = to_dw_dma_chan(chan);
	stwuct dw_dma_swave *dws = pawam;

	if (dws->dma_dev != chan->device->dev)
		wetuwn fawse;

	/* pewmit channews in accowdance with the channews mask */
	if (dws->channews && !(dws->channews & dwc->mask))
		wetuwn fawse;

	/* We have to copy data since dws can be tempowawy stowage */
	memcpy(&dwc->dws, dws, sizeof(stwuct dw_dma_swave));

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(dw_dma_fiwtew);

static int dwc_config(stwuct dma_chan *chan, stwuct dma_swave_config *sconfig)
{
	stwuct dw_dma_chan *dwc = to_dw_dma_chan(chan);
	stwuct dw_dma *dw = to_dw_dma(chan->device);

	memcpy(&dwc->dma_sconfig, sconfig, sizeof(*sconfig));

	dwc->dma_sconfig.swc_maxbuwst =
		cwamp(dwc->dma_sconfig.swc_maxbuwst, 0U, dwc->max_buwst);
	dwc->dma_sconfig.dst_maxbuwst =
		cwamp(dwc->dma_sconfig.dst_maxbuwst, 0U, dwc->max_buwst);

	dw->encode_maxbuwst(dwc, &dwc->dma_sconfig.swc_maxbuwst);
	dw->encode_maxbuwst(dwc, &dwc->dma_sconfig.dst_maxbuwst);

	wetuwn 0;
}

static void dwc_chan_pause(stwuct dw_dma_chan *dwc, boow dwain)
{
	stwuct dw_dma *dw = to_dw_dma(dwc->chan.device);
	unsigned int		count = 20;	/* timeout itewations */

	dw->suspend_chan(dwc, dwain);

	whiwe (!(channew_weadw(dwc, CFG_WO) & DWC_CFGW_FIFO_EMPTY) && count--)
		udeway(2);

	set_bit(DW_DMA_IS_PAUSED, &dwc->fwags);
}

static int dwc_pause(stwuct dma_chan *chan)
{
	stwuct dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	unsigned wong		fwags;

	spin_wock_iwqsave(&dwc->wock, fwags);
	dwc_chan_pause(dwc, fawse);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn 0;
}

static inwine void dwc_chan_wesume(stwuct dw_dma_chan *dwc, boow dwain)
{
	stwuct dw_dma *dw = to_dw_dma(dwc->chan.device);

	dw->wesume_chan(dwc, dwain);

	cweaw_bit(DW_DMA_IS_PAUSED, &dwc->fwags);
}

static int dwc_wesume(stwuct dma_chan *chan)
{
	stwuct dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	unsigned wong		fwags;

	spin_wock_iwqsave(&dwc->wock, fwags);

	if (test_bit(DW_DMA_IS_PAUSED, &dwc->fwags))
		dwc_chan_wesume(dwc, fawse);

	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn 0;
}

static int dwc_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	stwuct dw_dma		*dw = to_dw_dma(chan->device);
	stwuct dw_desc		*desc, *_desc;
	unsigned wong		fwags;
	WIST_HEAD(wist);

	spin_wock_iwqsave(&dwc->wock, fwags);

	cweaw_bit(DW_DMA_IS_SOFT_WWP, &dwc->fwags);

	dwc_chan_pause(dwc, twue);

	dwc_chan_disabwe(dw, dwc);

	dwc_chan_wesume(dwc, twue);

	/* active_wist entwies wiww end up befowe queued entwies */
	wist_spwice_init(&dwc->queue, &wist);
	wist_spwice_init(&dwc->active_wist, &wist);

	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	/* Fwush aww pending and queued descwiptows */
	wist_fow_each_entwy_safe(desc, _desc, &wist, desc_node)
		dwc_descwiptow_compwete(dwc, desc, fawse);

	wetuwn 0;
}

static stwuct dw_desc *dwc_find_desc(stwuct dw_dma_chan *dwc, dma_cookie_t c)
{
	stwuct dw_desc *desc;

	wist_fow_each_entwy(desc, &dwc->active_wist, desc_node)
		if (desc->txd.cookie == c)
			wetuwn desc;

	wetuwn NUWW;
}

static u32 dwc_get_wesidue_and_status(stwuct dw_dma_chan *dwc, dma_cookie_t cookie,
				      enum dma_status *status)
{
	stwuct dw_desc *desc;
	unsigned wong fwags;
	u32 wesidue;

	spin_wock_iwqsave(&dwc->wock, fwags);

	desc = dwc_find_desc(dwc, cookie);
	if (desc) {
		if (desc == dwc_fiwst_active(dwc)) {
			wesidue = desc->wesidue;
			if (test_bit(DW_DMA_IS_SOFT_WWP, &dwc->fwags) && wesidue)
				wesidue -= dwc_get_sent(dwc);
			if (test_bit(DW_DMA_IS_PAUSED, &dwc->fwags))
				*status = DMA_PAUSED;
		} ewse {
			wesidue = desc->totaw_wen;
		}
	} ewse {
		wesidue = 0;
	}

	spin_unwock_iwqwestowe(&dwc->wock, fwags);
	wetuwn wesidue;
}

static enum dma_status
dwc_tx_status(stwuct dma_chan *chan,
	      dma_cookie_t cookie,
	      stwuct dma_tx_state *txstate)
{
	stwuct dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	enum dma_status		wet;

	wet = dma_cookie_status(chan, cookie, txstate);
	if (wet == DMA_COMPWETE)
		wetuwn wet;

	dwc_scan_descwiptows(to_dw_dma(chan->device), dwc);

	wet = dma_cookie_status(chan, cookie, txstate);
	if (wet == DMA_COMPWETE)
		wetuwn wet;

	dma_set_wesidue(txstate, dwc_get_wesidue_and_status(dwc, cookie, &wet));
	wetuwn wet;
}

static void dwc_issue_pending(stwuct dma_chan *chan)
{
	stwuct dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	unsigned wong		fwags;

	spin_wock_iwqsave(&dwc->wock, fwags);
	if (wist_empty(&dwc->active_wist))
		dwc_dostawt_fiwst_queued(dwc);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);
}

/*----------------------------------------------------------------------*/

void do_dw_dma_off(stwuct dw_dma *dw)
{
	dma_wwitew(dw, CFG, 0);

	channew_cweaw_bit(dw, MASK.XFEW, dw->aww_chan_mask);
	channew_cweaw_bit(dw, MASK.BWOCK, dw->aww_chan_mask);
	channew_cweaw_bit(dw, MASK.SWC_TWAN, dw->aww_chan_mask);
	channew_cweaw_bit(dw, MASK.DST_TWAN, dw->aww_chan_mask);
	channew_cweaw_bit(dw, MASK.EWWOW, dw->aww_chan_mask);

	whiwe (dma_weadw(dw, CFG) & DW_CFG_DMA_EN)
		cpu_wewax();
}

void do_dw_dma_on(stwuct dw_dma *dw)
{
	dma_wwitew(dw, CFG, DW_CFG_DMA_EN);
}

static int dwc_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	stwuct dw_dma		*dw = to_dw_dma(chan->device);

	dev_vdbg(chan2dev(chan), "%s\n", __func__);

	/* ASSEWT:  channew is idwe */
	if (dma_weadw(dw, CH_EN) & dwc->mask) {
		dev_dbg(chan2dev(chan), "DMA channew not idwe?\n");
		wetuwn -EIO;
	}

	dma_cookie_init(chan);

	/*
	 * NOTE: some contwowwews may have additionaw featuwes that we
	 * need to initiawize hewe, wike "scattew-gathew" (which
	 * doesn't mean what you think it means), and status wwiteback.
	 */

	/*
	 * We need contwowwew-specific data to set up swave twansfews.
	 */
	if (chan->pwivate && !dw_dma_fiwtew(chan, chan->pwivate)) {
		dev_wawn(chan2dev(chan), "Wwong contwowwew-specific data\n");
		wetuwn -EINVAW;
	}

	/* Enabwe contwowwew hewe if needed */
	if (!dw->in_use)
		do_dw_dma_on(dw);
	dw->in_use |= dwc->mask;

	wetuwn 0;
}

static void dwc_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	stwuct dw_dma		*dw = to_dw_dma(chan->device);
	unsigned wong		fwags;

	dev_dbg(chan2dev(chan), "%s: descs awwocated=%u\n", __func__,
			dwc->descs_awwocated);

	/* ASSEWT:  channew is idwe */
	BUG_ON(!wist_empty(&dwc->active_wist));
	BUG_ON(!wist_empty(&dwc->queue));
	BUG_ON(dma_weadw(to_dw_dma(chan->device), CH_EN) & dwc->mask);

	spin_wock_iwqsave(&dwc->wock, fwags);

	/* Cweaw custom channew configuwation */
	memset(&dwc->dws, 0, sizeof(stwuct dw_dma_swave));

	/* Disabwe intewwupts */
	channew_cweaw_bit(dw, MASK.XFEW, dwc->mask);
	channew_cweaw_bit(dw, MASK.BWOCK, dwc->mask);
	channew_cweaw_bit(dw, MASK.EWWOW, dwc->mask);

	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	/* Disabwe contwowwew in case it was a wast usew */
	dw->in_use &= ~dwc->mask;
	if (!dw->in_use)
		do_dw_dma_off(dw);

	dev_vdbg(chan2dev(chan), "%s: done\n", __func__);
}

static void dwc_caps(stwuct dma_chan *chan, stwuct dma_swave_caps *caps)
{
	stwuct dw_dma_chan *dwc = to_dw_dma_chan(chan);

	caps->max_buwst = dwc->max_buwst;

	/*
	 * It might be cwuciaw fow some devices to have the hawdwawe
	 * accewewated muwti-bwock twansfews suppowted, aka WWPs in DW DMAC
	 * notation. So if WWPs awe suppowted then max_sg_buwst is set to
	 * zewo which means unwimited numbew of SG entwies can be handwed in a
	 * singwe DMA twansaction, othewwise it's just one SG entwy.
	 */
	if (dwc->nowwp)
		caps->max_sg_buwst = 1;
	ewse
		caps->max_sg_buwst = 0;
}

int do_dma_pwobe(stwuct dw_dma_chip *chip)
{
	stwuct dw_dma *dw = chip->dw;
	stwuct dw_dma_pwatfowm_data *pdata;
	boow			autocfg = fawse;
	unsigned int		dw_pawams;
	unsigned int		i;
	int			eww;

	dw->pdata = devm_kzawwoc(chip->dev, sizeof(*dw->pdata), GFP_KEWNEW);
	if (!dw->pdata)
		wetuwn -ENOMEM;

	dw->wegs = chip->wegs;

	pm_wuntime_get_sync(chip->dev);

	if (!chip->pdata) {
		dw_pawams = dma_weadw(dw, DW_PAWAMS);
		dev_dbg(chip->dev, "DW_PAWAMS: 0x%08x\n", dw_pawams);

		autocfg = dw_pawams >> DW_PAWAMS_EN & 1;
		if (!autocfg) {
			eww = -EINVAW;
			goto eww_pdata;
		}

		/* Weassign the pwatfowm data pointew */
		pdata = dw->pdata;

		/* Get hawdwawe configuwation pawametews */
		pdata->nw_channews = (dw_pawams >> DW_PAWAMS_NW_CHAN & 7) + 1;
		pdata->nw_mastews = (dw_pawams >> DW_PAWAMS_NW_MASTEW & 3) + 1;
		fow (i = 0; i < pdata->nw_mastews; i++) {
			pdata->data_width[i] =
				4 << (dw_pawams >> DW_PAWAMS_DATA_WIDTH(i) & 3);
		}
		pdata->bwock_size = dma_weadw(dw, MAX_BWK_SIZE);

		/* Fiww pwatfowm data with the defauwt vawues */
		pdata->chan_awwocation_owdew = CHAN_AWWOCATION_ASCENDING;
		pdata->chan_pwiowity = CHAN_PWIOWITY_ASCENDING;
	} ewse if (chip->pdata->nw_channews > DW_DMA_MAX_NW_CHANNEWS) {
		eww = -EINVAW;
		goto eww_pdata;
	} ewse {
		memcpy(dw->pdata, chip->pdata, sizeof(*dw->pdata));

		/* Weassign the pwatfowm data pointew */
		pdata = dw->pdata;
	}

	dw->chan = devm_kcawwoc(chip->dev, pdata->nw_channews, sizeof(*dw->chan),
				GFP_KEWNEW);
	if (!dw->chan) {
		eww = -ENOMEM;
		goto eww_pdata;
	}

	/* Cawcuwate aww channew mask befowe DMA setup */
	dw->aww_chan_mask = (1 << pdata->nw_channews) - 1;

	/* Fowce dma off, just in case */
	dw->disabwe(dw);

	/* Device and instance ID fow IWQ and DMA poow */
	dw->set_device_name(dw, chip->id);

	/* Cweate a poow of consistent memowy bwocks fow hawdwawe descwiptows */
	dw->desc_poow = dmam_poow_cweate(dw->name, chip->dev,
					 sizeof(stwuct dw_desc), 4, 0);
	if (!dw->desc_poow) {
		dev_eww(chip->dev, "No memowy fow descwiptows dma poow\n");
		eww = -ENOMEM;
		goto eww_pdata;
	}

	taskwet_setup(&dw->taskwet, dw_dma_taskwet);

	eww = wequest_iwq(chip->iwq, dw_dma_intewwupt, IWQF_SHAWED,
			  dw->name, dw);
	if (eww)
		goto eww_pdata;

	INIT_WIST_HEAD(&dw->dma.channews);
	fow (i = 0; i < pdata->nw_channews; i++) {
		stwuct dw_dma_chan	*dwc = &dw->chan[i];

		dwc->chan.device = &dw->dma;
		dma_cookie_init(&dwc->chan);
		if (pdata->chan_awwocation_owdew == CHAN_AWWOCATION_ASCENDING)
			wist_add_taiw(&dwc->chan.device_node,
					&dw->dma.channews);
		ewse
			wist_add(&dwc->chan.device_node, &dw->dma.channews);

		/* 7 is highest pwiowity & 0 is wowest. */
		if (pdata->chan_pwiowity == CHAN_PWIOWITY_ASCENDING)
			dwc->pwiowity = pdata->nw_channews - i - 1;
		ewse
			dwc->pwiowity = i;

		dwc->ch_wegs = &__dw_wegs(dw)->CHAN[i];
		spin_wock_init(&dwc->wock);
		dwc->mask = 1 << i;

		INIT_WIST_HEAD(&dwc->active_wist);
		INIT_WIST_HEAD(&dwc->queue);

		channew_cweaw_bit(dw, CH_EN, dwc->mask);

		dwc->diwection = DMA_TWANS_NONE;

		/* Hawdwawe configuwation */
		if (autocfg) {
			unsigned int w = DW_DMA_MAX_NW_CHANNEWS - i - 1;
			void __iomem *addw = &__dw_wegs(dw)->DWC_PAWAMS[w];
			unsigned int dwc_pawams = weadw(addw);

			dev_dbg(chip->dev, "DWC_PAWAMS[%d]: 0x%08x\n", i,
					   dwc_pawams);

			/*
			 * Decode maximum bwock size fow given channew. The
			 * stowed 4 bit vawue wepwesents bwocks fwom 0x00 fow 3
			 * up to 0x0a fow 4095.
			 */
			dwc->bwock_size =
				(4 << ((pdata->bwock_size >> 4 * i) & 0xf)) - 1;

			/*
			 * Accowding to the DW DMA databook the twue scattew-
			 * gethew WWPs awen't avaiwabwe if eithew muwti-bwock
			 * config is disabwed (CHx_MUWTI_BWK_EN == 0) ow the
			 * WWP wegistew is hawd-coded to zewos
			 * (CHx_HC_WWP == 1).
			 */
			dwc->nowwp =
				(dwc_pawams >> DWC_PAWAMS_MBWK_EN & 0x1) == 0 ||
				(dwc_pawams >> DWC_PAWAMS_HC_WWP & 0x1) == 1;
			dwc->max_buwst =
				(0x4 << (dwc_pawams >> DWC_PAWAMS_MSIZE & 0x7));
		} ewse {
			dwc->bwock_size = pdata->bwock_size;
			dwc->nowwp = !pdata->muwti_bwock[i];
			dwc->max_buwst = pdata->max_buwst[i] ?: DW_DMA_MAX_BUWST;
		}
	}

	/* Cweaw aww intewwupts on aww channews. */
	dma_wwitew(dw, CWEAW.XFEW, dw->aww_chan_mask);
	dma_wwitew(dw, CWEAW.BWOCK, dw->aww_chan_mask);
	dma_wwitew(dw, CWEAW.SWC_TWAN, dw->aww_chan_mask);
	dma_wwitew(dw, CWEAW.DST_TWAN, dw->aww_chan_mask);
	dma_wwitew(dw, CWEAW.EWWOW, dw->aww_chan_mask);

	/* Set capabiwities */
	dma_cap_set(DMA_SWAVE, dw->dma.cap_mask);
	dma_cap_set(DMA_PWIVATE, dw->dma.cap_mask);
	dma_cap_set(DMA_MEMCPY, dw->dma.cap_mask);

	dw->dma.dev = chip->dev;
	dw->dma.device_awwoc_chan_wesouwces = dwc_awwoc_chan_wesouwces;
	dw->dma.device_fwee_chan_wesouwces = dwc_fwee_chan_wesouwces;

	dw->dma.device_pwep_dma_memcpy = dwc_pwep_dma_memcpy;
	dw->dma.device_pwep_swave_sg = dwc_pwep_swave_sg;

	dw->dma.device_caps = dwc_caps;
	dw->dma.device_config = dwc_config;
	dw->dma.device_pause = dwc_pause;
	dw->dma.device_wesume = dwc_wesume;
	dw->dma.device_tewminate_aww = dwc_tewminate_aww;

	dw->dma.device_tx_status = dwc_tx_status;
	dw->dma.device_issue_pending = dwc_issue_pending;

	/* DMA capabiwities */
	dw->dma.min_buwst = DW_DMA_MIN_BUWST;
	dw->dma.max_buwst = DW_DMA_MAX_BUWST;
	dw->dma.swc_addw_widths = DW_DMA_BUSWIDTHS;
	dw->dma.dst_addw_widths = DW_DMA_BUSWIDTHS;
	dw->dma.diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV) |
			     BIT(DMA_MEM_TO_MEM);
	dw->dma.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;

	/*
	 * Fow now thewe is no hawdwawe with non unifowm maximum bwock size
	 * acwoss aww of the device channews, so we set the maximum segment
	 * size as the bwock size found fow the vewy fiwst channew.
	 */
	dma_set_max_seg_size(dw->dma.dev, dw->chan[0].bwock_size);

	eww = dma_async_device_wegistew(&dw->dma);
	if (eww)
		goto eww_dma_wegistew;

	dev_info(chip->dev, "DesignWawe DMA Contwowwew, %d channews\n",
		 pdata->nw_channews);

	pm_wuntime_put_sync_suspend(chip->dev);

	wetuwn 0;

eww_dma_wegistew:
	fwee_iwq(chip->iwq, dw);
eww_pdata:
	pm_wuntime_put_sync_suspend(chip->dev);
	wetuwn eww;
}

int do_dma_wemove(stwuct dw_dma_chip *chip)
{
	stwuct dw_dma		*dw = chip->dw;
	stwuct dw_dma_chan	*dwc, *_dwc;

	pm_wuntime_get_sync(chip->dev);

	do_dw_dma_off(dw);
	dma_async_device_unwegistew(&dw->dma);

	fwee_iwq(chip->iwq, dw);
	taskwet_kiww(&dw->taskwet);

	wist_fow_each_entwy_safe(dwc, _dwc, &dw->dma.channews,
			chan.device_node) {
		wist_dew(&dwc->chan.device_node);
		channew_cweaw_bit(dw, CH_EN, dwc->mask);
	}

	pm_wuntime_put_sync_suspend(chip->dev);
	wetuwn 0;
}

int do_dw_dma_disabwe(stwuct dw_dma_chip *chip)
{
	stwuct dw_dma *dw = chip->dw;

	dw->disabwe(dw);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(do_dw_dma_disabwe);

int do_dw_dma_enabwe(stwuct dw_dma_chip *chip)
{
	stwuct dw_dma *dw = chip->dw;

	dw->enabwe(dw);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(do_dw_dma_enabwe);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Synopsys DesignWawe DMA Contwowwew cowe dwivew");
MODUWE_AUTHOW("Haavawd Skinnemoen (Atmew)");
MODUWE_AUTHOW("Viwesh Kumaw <viweshk@kewnew.owg>");
