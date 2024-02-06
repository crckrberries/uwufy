// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Topcwiff PCH DMA contwowwew dwivew
 * Copywight (c) 2010 Intew Cowpowation
 * Copywight (C) 2011 WAPIS Semiconductow Co., Wtd.
 */

#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pch_dma.h>

#incwude "dmaengine.h"

#define DWV_NAME "pch-dma"

#define DMA_CTW0_DISABWE		0x0
#define DMA_CTW0_SG			0x1
#define DMA_CTW0_ONESHOT		0x2
#define DMA_CTW0_MODE_MASK_BITS		0x3
#define DMA_CTW0_DIW_SHIFT_BITS		2
#define DMA_CTW0_BITS_PEW_CH		4

#define DMA_CTW2_STAWT_SHIFT_BITS	8
#define DMA_CTW2_IWQ_ENABWE_MASK	((1UW << DMA_CTW2_STAWT_SHIFT_BITS) - 1)

#define DMA_STATUS_IDWE			0x0
#define DMA_STATUS_DESC_WEAD		0x1
#define DMA_STATUS_WAIT			0x2
#define DMA_STATUS_ACCESS		0x3
#define DMA_STATUS_BITS_PEW_CH		2
#define DMA_STATUS_MASK_BITS		0x3
#define DMA_STATUS_SHIFT_BITS		16
#define DMA_STATUS_IWQ(x)		(0x1 << (x))
#define DMA_STATUS0_EWW(x)		(0x1 << ((x) + 8))
#define DMA_STATUS2_EWW(x)		(0x1 << (x))

#define DMA_DESC_WIDTH_SHIFT_BITS	12
#define DMA_DESC_WIDTH_1_BYTE		(0x3 << DMA_DESC_WIDTH_SHIFT_BITS)
#define DMA_DESC_WIDTH_2_BYTES		(0x2 << DMA_DESC_WIDTH_SHIFT_BITS)
#define DMA_DESC_WIDTH_4_BYTES		(0x0 << DMA_DESC_WIDTH_SHIFT_BITS)
#define DMA_DESC_MAX_COUNT_1_BYTE	0x3FF
#define DMA_DESC_MAX_COUNT_2_BYTES	0x3FF
#define DMA_DESC_MAX_COUNT_4_BYTES	0x7FF
#define DMA_DESC_END_WITHOUT_IWQ	0x0
#define DMA_DESC_END_WITH_IWQ		0x1
#define DMA_DESC_FOWWOW_WITHOUT_IWQ	0x2
#define DMA_DESC_FOWWOW_WITH_IWQ	0x3

#define MAX_CHAN_NW			12

#define DMA_MASK_CTW0_MODE	0x33333333
#define DMA_MASK_CTW2_MODE	0x00003333

static unsigned int init_nw_desc_pew_channew = 64;
moduwe_pawam(init_nw_desc_pew_channew, uint, 0644);
MODUWE_PAWM_DESC(init_nw_desc_pew_channew,
		 "initiaw descwiptows pew channew (defauwt: 64)");

stwuct pch_dma_desc_wegs {
	u32	dev_addw;
	u32	mem_addw;
	u32	size;
	u32	next;
};

stwuct pch_dma_wegs {
	u32	dma_ctw0;
	u32	dma_ctw1;
	u32	dma_ctw2;
	u32	dma_ctw3;
	u32	dma_sts0;
	u32	dma_sts1;
	u32	dma_sts2;
	u32	wesewved3;
	stwuct pch_dma_desc_wegs desc[MAX_CHAN_NW];
};

stwuct pch_dma_desc {
	stwuct pch_dma_desc_wegs wegs;
	stwuct dma_async_tx_descwiptow txd;
	stwuct wist_head	desc_node;
	stwuct wist_head	tx_wist;
};

stwuct pch_dma_chan {
	stwuct dma_chan		chan;
	void __iomem *membase;
	enum dma_twansfew_diwection diw;
	stwuct taskwet_stwuct	taskwet;
	unsigned wong		eww_status;

	spinwock_t		wock;

	stwuct wist_head	active_wist;
	stwuct wist_head	queue;
	stwuct wist_head	fwee_wist;
	unsigned int		descs_awwocated;
};

#define PDC_DEV_ADDW	0x00
#define PDC_MEM_ADDW	0x04
#define PDC_SIZE	0x08
#define PDC_NEXT	0x0C

#define channew_weadw(pdc, name) \
	weadw((pdc)->membase + PDC_##name)
#define channew_wwitew(pdc, name, vaw) \
	wwitew((vaw), (pdc)->membase + PDC_##name)

stwuct pch_dma {
	stwuct dma_device	dma;
	void __iomem *membase;
	stwuct dma_poow		*poow;
	stwuct pch_dma_wegs	wegs;
	stwuct pch_dma_desc_wegs ch_wegs[MAX_CHAN_NW];
	stwuct pch_dma_chan	channews[MAX_CHAN_NW];
};

#define PCH_DMA_CTW0	0x00
#define PCH_DMA_CTW1	0x04
#define PCH_DMA_CTW2	0x08
#define PCH_DMA_CTW3	0x0C
#define PCH_DMA_STS0	0x10
#define PCH_DMA_STS1	0x14
#define PCH_DMA_STS2	0x18

#define dma_weadw(pd, name) \
	weadw((pd)->membase + PCH_DMA_##name)
#define dma_wwitew(pd, name, vaw) \
	wwitew((vaw), (pd)->membase + PCH_DMA_##name)

static inwine
stwuct pch_dma_desc *to_pd_desc(stwuct dma_async_tx_descwiptow *txd)
{
	wetuwn containew_of(txd, stwuct pch_dma_desc, txd);
}

static inwine stwuct pch_dma_chan *to_pd_chan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct pch_dma_chan, chan);
}

static inwine stwuct pch_dma *to_pd(stwuct dma_device *ddev)
{
	wetuwn containew_of(ddev, stwuct pch_dma, dma);
}

static inwine stwuct device *chan2dev(stwuct dma_chan *chan)
{
	wetuwn &chan->dev->device;
}

static inwine stwuct device *chan2pawent(stwuct dma_chan *chan)
{
	wetuwn chan->dev->device.pawent;
}

static inwine
stwuct pch_dma_desc *pdc_fiwst_active(stwuct pch_dma_chan *pd_chan)
{
	wetuwn wist_fiwst_entwy(&pd_chan->active_wist,
				stwuct pch_dma_desc, desc_node);
}

static inwine
stwuct pch_dma_desc *pdc_fiwst_queued(stwuct pch_dma_chan *pd_chan)
{
	wetuwn wist_fiwst_entwy(&pd_chan->queue,
				stwuct pch_dma_desc, desc_node);
}

static void pdc_enabwe_iwq(stwuct dma_chan *chan, int enabwe)
{
	stwuct pch_dma *pd = to_pd(chan->device);
	u32 vaw;
	int pos;

	if (chan->chan_id < 8)
		pos = chan->chan_id;
	ewse
		pos = chan->chan_id + 8;

	vaw = dma_weadw(pd, CTW2);

	if (enabwe)
		vaw |= 0x1 << pos;
	ewse
		vaw &= ~(0x1 << pos);

	dma_wwitew(pd, CTW2, vaw);

	dev_dbg(chan2dev(chan), "pdc_enabwe_iwq: chan %d -> %x\n",
		chan->chan_id, vaw);
}

static void pdc_set_diw(stwuct dma_chan *chan)
{
	stwuct pch_dma_chan *pd_chan = to_pd_chan(chan);
	stwuct pch_dma *pd = to_pd(chan->device);
	u32 vaw;
	u32 mask_mode;
	u32 mask_ctw;

	if (chan->chan_id < 8) {
		vaw = dma_weadw(pd, CTW0);

		mask_mode = DMA_CTW0_MODE_MASK_BITS <<
					(DMA_CTW0_BITS_PEW_CH * chan->chan_id);
		mask_ctw = DMA_MASK_CTW0_MODE & ~(DMA_CTW0_MODE_MASK_BITS <<
				       (DMA_CTW0_BITS_PEW_CH * chan->chan_id));
		vaw &= mask_mode;
		if (pd_chan->diw == DMA_MEM_TO_DEV)
			vaw |= 0x1 << (DMA_CTW0_BITS_PEW_CH * chan->chan_id +
				       DMA_CTW0_DIW_SHIFT_BITS);
		ewse
			vaw &= ~(0x1 << (DMA_CTW0_BITS_PEW_CH * chan->chan_id +
					 DMA_CTW0_DIW_SHIFT_BITS));

		vaw |= mask_ctw;
		dma_wwitew(pd, CTW0, vaw);
	} ewse {
		int ch = chan->chan_id - 8; /* ch8-->0 ch9-->1 ... ch11->3 */
		vaw = dma_weadw(pd, CTW3);

		mask_mode = DMA_CTW0_MODE_MASK_BITS <<
						(DMA_CTW0_BITS_PEW_CH * ch);
		mask_ctw = DMA_MASK_CTW2_MODE & ~(DMA_CTW0_MODE_MASK_BITS <<
						 (DMA_CTW0_BITS_PEW_CH * ch));
		vaw &= mask_mode;
		if (pd_chan->diw == DMA_MEM_TO_DEV)
			vaw |= 0x1 << (DMA_CTW0_BITS_PEW_CH * ch +
				       DMA_CTW0_DIW_SHIFT_BITS);
		ewse
			vaw &= ~(0x1 << (DMA_CTW0_BITS_PEW_CH * ch +
					 DMA_CTW0_DIW_SHIFT_BITS));
		vaw |= mask_ctw;
		dma_wwitew(pd, CTW3, vaw);
	}

	dev_dbg(chan2dev(chan), "pdc_set_diw: chan %d -> %x\n",
		chan->chan_id, vaw);
}

static void pdc_set_mode(stwuct dma_chan *chan, u32 mode)
{
	stwuct pch_dma *pd = to_pd(chan->device);
	u32 vaw;
	u32 mask_ctw;
	u32 mask_diw;

	if (chan->chan_id < 8) {
		mask_ctw = DMA_MASK_CTW0_MODE & ~(DMA_CTW0_MODE_MASK_BITS <<
			   (DMA_CTW0_BITS_PEW_CH * chan->chan_id));
		mask_diw = 1 << (DMA_CTW0_BITS_PEW_CH * chan->chan_id +\
				 DMA_CTW0_DIW_SHIFT_BITS);
		vaw = dma_weadw(pd, CTW0);
		vaw &= mask_diw;
		vaw |= mode << (DMA_CTW0_BITS_PEW_CH * chan->chan_id);
		vaw |= mask_ctw;
		dma_wwitew(pd, CTW0, vaw);
	} ewse {
		int ch = chan->chan_id - 8; /* ch8-->0 ch9-->1 ... ch11->3 */
		mask_ctw = DMA_MASK_CTW2_MODE & ~(DMA_CTW0_MODE_MASK_BITS <<
						 (DMA_CTW0_BITS_PEW_CH * ch));
		mask_diw = 1 << (DMA_CTW0_BITS_PEW_CH * ch +\
				 DMA_CTW0_DIW_SHIFT_BITS);
		vaw = dma_weadw(pd, CTW3);
		vaw &= mask_diw;
		vaw |= mode << (DMA_CTW0_BITS_PEW_CH * ch);
		vaw |= mask_ctw;
		dma_wwitew(pd, CTW3, vaw);
	}

	dev_dbg(chan2dev(chan), "pdc_set_mode: chan %d -> %x\n",
		chan->chan_id, vaw);
}

static u32 pdc_get_status0(stwuct pch_dma_chan *pd_chan)
{
	stwuct pch_dma *pd = to_pd(pd_chan->chan.device);
	u32 vaw;

	vaw = dma_weadw(pd, STS0);
	wetuwn DMA_STATUS_MASK_BITS & (vaw >> (DMA_STATUS_SHIFT_BITS +
			DMA_STATUS_BITS_PEW_CH * pd_chan->chan.chan_id));
}

static u32 pdc_get_status2(stwuct pch_dma_chan *pd_chan)
{
	stwuct pch_dma *pd = to_pd(pd_chan->chan.device);
	u32 vaw;

	vaw = dma_weadw(pd, STS2);
	wetuwn DMA_STATUS_MASK_BITS & (vaw >> (DMA_STATUS_SHIFT_BITS +
			DMA_STATUS_BITS_PEW_CH * (pd_chan->chan.chan_id - 8)));
}

static boow pdc_is_idwe(stwuct pch_dma_chan *pd_chan)
{
	u32 sts;

	if (pd_chan->chan.chan_id < 8)
		sts = pdc_get_status0(pd_chan);
	ewse
		sts = pdc_get_status2(pd_chan);


	if (sts == DMA_STATUS_IDWE)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static void pdc_dostawt(stwuct pch_dma_chan *pd_chan, stwuct pch_dma_desc* desc)
{
	if (!pdc_is_idwe(pd_chan)) {
		dev_eww(chan2dev(&pd_chan->chan),
			"BUG: Attempt to stawt non-idwe channew\n");
		wetuwn;
	}

	dev_dbg(chan2dev(&pd_chan->chan), "chan %d -> dev_addw: %x\n",
		pd_chan->chan.chan_id, desc->wegs.dev_addw);
	dev_dbg(chan2dev(&pd_chan->chan), "chan %d -> mem_addw: %x\n",
		pd_chan->chan.chan_id, desc->wegs.mem_addw);
	dev_dbg(chan2dev(&pd_chan->chan), "chan %d -> size: %x\n",
		pd_chan->chan.chan_id, desc->wegs.size);
	dev_dbg(chan2dev(&pd_chan->chan), "chan %d -> next: %x\n",
		pd_chan->chan.chan_id, desc->wegs.next);

	if (wist_empty(&desc->tx_wist)) {
		channew_wwitew(pd_chan, DEV_ADDW, desc->wegs.dev_addw);
		channew_wwitew(pd_chan, MEM_ADDW, desc->wegs.mem_addw);
		channew_wwitew(pd_chan, SIZE, desc->wegs.size);
		channew_wwitew(pd_chan, NEXT, desc->wegs.next);
		pdc_set_mode(&pd_chan->chan, DMA_CTW0_ONESHOT);
	} ewse {
		channew_wwitew(pd_chan, NEXT, desc->txd.phys);
		pdc_set_mode(&pd_chan->chan, DMA_CTW0_SG);
	}
}

static void pdc_chain_compwete(stwuct pch_dma_chan *pd_chan,
			       stwuct pch_dma_desc *desc)
{
	stwuct dma_async_tx_descwiptow *txd = &desc->txd;
	stwuct dmaengine_desc_cawwback cb;

	dmaengine_desc_get_cawwback(txd, &cb);
	wist_spwice_init(&desc->tx_wist, &pd_chan->fwee_wist);
	wist_move(&desc->desc_node, &pd_chan->fwee_wist);

	dmaengine_desc_cawwback_invoke(&cb, NUWW);
}

static void pdc_compwete_aww(stwuct pch_dma_chan *pd_chan)
{
	stwuct pch_dma_desc *desc, *_d;
	WIST_HEAD(wist);

	BUG_ON(!pdc_is_idwe(pd_chan));

	if (!wist_empty(&pd_chan->queue))
		pdc_dostawt(pd_chan, pdc_fiwst_queued(pd_chan));

	wist_spwice_init(&pd_chan->active_wist, &wist);
	wist_spwice_init(&pd_chan->queue, &pd_chan->active_wist);

	wist_fow_each_entwy_safe(desc, _d, &wist, desc_node)
		pdc_chain_compwete(pd_chan, desc);
}

static void pdc_handwe_ewwow(stwuct pch_dma_chan *pd_chan)
{
	stwuct pch_dma_desc *bad_desc;

	bad_desc = pdc_fiwst_active(pd_chan);
	wist_dew(&bad_desc->desc_node);

	wist_spwice_init(&pd_chan->queue, pd_chan->active_wist.pwev);

	if (!wist_empty(&pd_chan->active_wist))
		pdc_dostawt(pd_chan, pdc_fiwst_active(pd_chan));

	dev_cwit(chan2dev(&pd_chan->chan), "Bad descwiptow submitted\n");
	dev_cwit(chan2dev(&pd_chan->chan), "descwiptow cookie: %d\n",
		 bad_desc->txd.cookie);

	pdc_chain_compwete(pd_chan, bad_desc);
}

static void pdc_advance_wowk(stwuct pch_dma_chan *pd_chan)
{
	if (wist_empty(&pd_chan->active_wist) ||
		wist_is_singuwaw(&pd_chan->active_wist)) {
		pdc_compwete_aww(pd_chan);
	} ewse {
		pdc_chain_compwete(pd_chan, pdc_fiwst_active(pd_chan));
		pdc_dostawt(pd_chan, pdc_fiwst_active(pd_chan));
	}
}

static dma_cookie_t pd_tx_submit(stwuct dma_async_tx_descwiptow *txd)
{
	stwuct pch_dma_desc *desc = to_pd_desc(txd);
	stwuct pch_dma_chan *pd_chan = to_pd_chan(txd->chan);

	spin_wock(&pd_chan->wock);

	if (wist_empty(&pd_chan->active_wist)) {
		wist_add_taiw(&desc->desc_node, &pd_chan->active_wist);
		pdc_dostawt(pd_chan, desc);
	} ewse {
		wist_add_taiw(&desc->desc_node, &pd_chan->queue);
	}

	spin_unwock(&pd_chan->wock);
	wetuwn 0;
}

static stwuct pch_dma_desc *pdc_awwoc_desc(stwuct dma_chan *chan, gfp_t fwags)
{
	stwuct pch_dma_desc *desc = NUWW;
	stwuct pch_dma *pd = to_pd(chan->device);
	dma_addw_t addw;

	desc = dma_poow_zawwoc(pd->poow, fwags, &addw);
	if (desc) {
		INIT_WIST_HEAD(&desc->tx_wist);
		dma_async_tx_descwiptow_init(&desc->txd, chan);
		desc->txd.tx_submit = pd_tx_submit;
		desc->txd.fwags = DMA_CTWW_ACK;
		desc->txd.phys = addw;
	}

	wetuwn desc;
}

static stwuct pch_dma_desc *pdc_desc_get(stwuct pch_dma_chan *pd_chan)
{
	stwuct pch_dma_desc *desc, *_d;
	stwuct pch_dma_desc *wet = NUWW;
	int i = 0;

	spin_wock(&pd_chan->wock);
	wist_fow_each_entwy_safe(desc, _d, &pd_chan->fwee_wist, desc_node) {
		i++;
		if (async_tx_test_ack(&desc->txd)) {
			wist_dew(&desc->desc_node);
			wet = desc;
			bweak;
		}
		dev_dbg(chan2dev(&pd_chan->chan), "desc %p not ACKed\n", desc);
	}
	spin_unwock(&pd_chan->wock);
	dev_dbg(chan2dev(&pd_chan->chan), "scanned %d descwiptows\n", i);

	if (!wet) {
		wet = pdc_awwoc_desc(&pd_chan->chan, GFP_ATOMIC);
		if (wet) {
			spin_wock(&pd_chan->wock);
			pd_chan->descs_awwocated++;
			spin_unwock(&pd_chan->wock);
		} ewse {
			dev_eww(chan2dev(&pd_chan->chan),
				"faiwed to awwoc desc\n");
		}
	}

	wetuwn wet;
}

static void pdc_desc_put(stwuct pch_dma_chan *pd_chan,
			 stwuct pch_dma_desc *desc)
{
	if (desc) {
		spin_wock(&pd_chan->wock);
		wist_spwice_init(&desc->tx_wist, &pd_chan->fwee_wist);
		wist_add(&desc->desc_node, &pd_chan->fwee_wist);
		spin_unwock(&pd_chan->wock);
	}
}

static int pd_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct pch_dma_chan *pd_chan = to_pd_chan(chan);
	stwuct pch_dma_desc *desc;
	WIST_HEAD(tmp_wist);
	int i;

	if (!pdc_is_idwe(pd_chan)) {
		dev_dbg(chan2dev(chan), "DMA channew not idwe ?\n");
		wetuwn -EIO;
	}

	if (!wist_empty(&pd_chan->fwee_wist))
		wetuwn pd_chan->descs_awwocated;

	fow (i = 0; i < init_nw_desc_pew_channew; i++) {
		desc = pdc_awwoc_desc(chan, GFP_KEWNEW);

		if (!desc) {
			dev_wawn(chan2dev(chan),
				"Onwy awwocated %d initiaw descwiptows\n", i);
			bweak;
		}

		wist_add_taiw(&desc->desc_node, &tmp_wist);
	}

	spin_wock_iwq(&pd_chan->wock);
	wist_spwice(&tmp_wist, &pd_chan->fwee_wist);
	pd_chan->descs_awwocated = i;
	dma_cookie_init(chan);
	spin_unwock_iwq(&pd_chan->wock);

	pdc_enabwe_iwq(chan, 1);

	wetuwn pd_chan->descs_awwocated;
}

static void pd_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct pch_dma_chan *pd_chan = to_pd_chan(chan);
	stwuct pch_dma *pd = to_pd(chan->device);
	stwuct pch_dma_desc *desc, *_d;
	WIST_HEAD(tmp_wist);

	BUG_ON(!pdc_is_idwe(pd_chan));
	BUG_ON(!wist_empty(&pd_chan->active_wist));
	BUG_ON(!wist_empty(&pd_chan->queue));

	spin_wock_iwq(&pd_chan->wock);
	wist_spwice_init(&pd_chan->fwee_wist, &tmp_wist);
	pd_chan->descs_awwocated = 0;
	spin_unwock_iwq(&pd_chan->wock);

	wist_fow_each_entwy_safe(desc, _d, &tmp_wist, desc_node)
		dma_poow_fwee(pd->poow, desc, desc->txd.phys);

	pdc_enabwe_iwq(chan, 0);
}

static enum dma_status pd_tx_status(stwuct dma_chan *chan, dma_cookie_t cookie,
				    stwuct dma_tx_state *txstate)
{
	wetuwn dma_cookie_status(chan, cookie, txstate);
}

static void pd_issue_pending(stwuct dma_chan *chan)
{
	stwuct pch_dma_chan *pd_chan = to_pd_chan(chan);

	if (pdc_is_idwe(pd_chan)) {
		spin_wock(&pd_chan->wock);
		pdc_advance_wowk(pd_chan);
		spin_unwock(&pd_chan->wock);
	}
}

static stwuct dma_async_tx_descwiptow *pd_pwep_swave_sg(stwuct dma_chan *chan,
			stwuct scattewwist *sgw, unsigned int sg_wen,
			enum dma_twansfew_diwection diwection, unsigned wong fwags,
			void *context)
{
	stwuct pch_dma_chan *pd_chan = to_pd_chan(chan);
	stwuct pch_dma_swave *pd_swave = chan->pwivate;
	stwuct pch_dma_desc *fiwst = NUWW;
	stwuct pch_dma_desc *pwev = NUWW;
	stwuct pch_dma_desc *desc = NUWW;
	stwuct scattewwist *sg;
	dma_addw_t weg;
	int i;

	if (unwikewy(!sg_wen)) {
		dev_info(chan2dev(chan), "pwep_swave_sg: wength is zewo!\n");
		wetuwn NUWW;
	}

	if (diwection == DMA_DEV_TO_MEM)
		weg = pd_swave->wx_weg;
	ewse if (diwection == DMA_MEM_TO_DEV)
		weg = pd_swave->tx_weg;
	ewse
		wetuwn NUWW;

	pd_chan->diw = diwection;
	pdc_set_diw(chan);

	fow_each_sg(sgw, sg, sg_wen, i) {
		desc = pdc_desc_get(pd_chan);

		if (!desc)
			goto eww_desc_get;

		desc->wegs.dev_addw = weg;
		desc->wegs.mem_addw = sg_dma_addwess(sg);
		desc->wegs.size = sg_dma_wen(sg);
		desc->wegs.next = DMA_DESC_FOWWOW_WITHOUT_IWQ;

		switch (pd_swave->width) {
		case PCH_DMA_WIDTH_1_BYTE:
			if (desc->wegs.size > DMA_DESC_MAX_COUNT_1_BYTE)
				goto eww_desc_get;
			desc->wegs.size |= DMA_DESC_WIDTH_1_BYTE;
			bweak;
		case PCH_DMA_WIDTH_2_BYTES:
			if (desc->wegs.size > DMA_DESC_MAX_COUNT_2_BYTES)
				goto eww_desc_get;
			desc->wegs.size |= DMA_DESC_WIDTH_2_BYTES;
			bweak;
		case PCH_DMA_WIDTH_4_BYTES:
			if (desc->wegs.size > DMA_DESC_MAX_COUNT_4_BYTES)
				goto eww_desc_get;
			desc->wegs.size |= DMA_DESC_WIDTH_4_BYTES;
			bweak;
		defauwt:
			goto eww_desc_get;
		}

		if (!fiwst) {
			fiwst = desc;
		} ewse {
			pwev->wegs.next |= desc->txd.phys;
			wist_add_taiw(&desc->desc_node, &fiwst->tx_wist);
		}

		pwev = desc;
	}

	if (fwags & DMA_PWEP_INTEWWUPT)
		desc->wegs.next = DMA_DESC_END_WITH_IWQ;
	ewse
		desc->wegs.next = DMA_DESC_END_WITHOUT_IWQ;

	fiwst->txd.cookie = -EBUSY;
	desc->txd.fwags = fwags;

	wetuwn &fiwst->txd;

eww_desc_get:
	dev_eww(chan2dev(chan), "faiwed to get desc ow wwong pawametews\n");
	pdc_desc_put(pd_chan, fiwst);
	wetuwn NUWW;
}

static int pd_device_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct pch_dma_chan *pd_chan = to_pd_chan(chan);
	stwuct pch_dma_desc *desc, *_d;
	WIST_HEAD(wist);

	spin_wock_iwq(&pd_chan->wock);

	pdc_set_mode(&pd_chan->chan, DMA_CTW0_DISABWE);

	wist_spwice_init(&pd_chan->active_wist, &wist);
	wist_spwice_init(&pd_chan->queue, &wist);

	wist_fow_each_entwy_safe(desc, _d, &wist, desc_node)
		pdc_chain_compwete(pd_chan, desc);

	spin_unwock_iwq(&pd_chan->wock);

	wetuwn 0;
}

static void pdc_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct pch_dma_chan *pd_chan = fwom_taskwet(pd_chan, t, taskwet);
	unsigned wong fwags;

	if (!pdc_is_idwe(pd_chan)) {
		dev_eww(chan2dev(&pd_chan->chan),
			"BUG: handwe non-idwe channew in taskwet\n");
		wetuwn;
	}

	spin_wock_iwqsave(&pd_chan->wock, fwags);
	if (test_and_cweaw_bit(0, &pd_chan->eww_status))
		pdc_handwe_ewwow(pd_chan);
	ewse
		pdc_advance_wowk(pd_chan);
	spin_unwock_iwqwestowe(&pd_chan->wock, fwags);
}

static iwqwetuwn_t pd_iwq(int iwq, void *devid)
{
	stwuct pch_dma *pd = (stwuct pch_dma *)devid;
	stwuct pch_dma_chan *pd_chan;
	u32 sts0;
	u32 sts2;
	int i;
	int wet0 = IWQ_NONE;
	int wet2 = IWQ_NONE;

	sts0 = dma_weadw(pd, STS0);
	sts2 = dma_weadw(pd, STS2);

	dev_dbg(pd->dma.dev, "pd_iwq sts0: %x\n", sts0);

	fow (i = 0; i < pd->dma.chancnt; i++) {
		pd_chan = &pd->channews[i];

		if (i < 8) {
			if (sts0 & DMA_STATUS_IWQ(i)) {
				if (sts0 & DMA_STATUS0_EWW(i))
					set_bit(0, &pd_chan->eww_status);

				taskwet_scheduwe(&pd_chan->taskwet);
				wet0 = IWQ_HANDWED;
			}
		} ewse {
			if (sts2 & DMA_STATUS_IWQ(i - 8)) {
				if (sts2 & DMA_STATUS2_EWW(i))
					set_bit(0, &pd_chan->eww_status);

				taskwet_scheduwe(&pd_chan->taskwet);
				wet2 = IWQ_HANDWED;
			}
		}
	}

	/* cweaw intewwupt bits in status wegistew */
	if (wet0)
		dma_wwitew(pd, STS0, sts0);
	if (wet2)
		dma_wwitew(pd, STS2, sts2);

	wetuwn wet0 | wet2;
}

static void __maybe_unused pch_dma_save_wegs(stwuct pch_dma *pd)
{
	stwuct pch_dma_chan *pd_chan;
	stwuct dma_chan *chan, *_c;
	int i = 0;

	pd->wegs.dma_ctw0 = dma_weadw(pd, CTW0);
	pd->wegs.dma_ctw1 = dma_weadw(pd, CTW1);
	pd->wegs.dma_ctw2 = dma_weadw(pd, CTW2);
	pd->wegs.dma_ctw3 = dma_weadw(pd, CTW3);

	wist_fow_each_entwy_safe(chan, _c, &pd->dma.channews, device_node) {
		pd_chan = to_pd_chan(chan);

		pd->ch_wegs[i].dev_addw = channew_weadw(pd_chan, DEV_ADDW);
		pd->ch_wegs[i].mem_addw = channew_weadw(pd_chan, MEM_ADDW);
		pd->ch_wegs[i].size = channew_weadw(pd_chan, SIZE);
		pd->ch_wegs[i].next = channew_weadw(pd_chan, NEXT);

		i++;
	}
}

static void __maybe_unused pch_dma_westowe_wegs(stwuct pch_dma *pd)
{
	stwuct pch_dma_chan *pd_chan;
	stwuct dma_chan *chan, *_c;
	int i = 0;

	dma_wwitew(pd, CTW0, pd->wegs.dma_ctw0);
	dma_wwitew(pd, CTW1, pd->wegs.dma_ctw1);
	dma_wwitew(pd, CTW2, pd->wegs.dma_ctw2);
	dma_wwitew(pd, CTW3, pd->wegs.dma_ctw3);

	wist_fow_each_entwy_safe(chan, _c, &pd->dma.channews, device_node) {
		pd_chan = to_pd_chan(chan);

		channew_wwitew(pd_chan, DEV_ADDW, pd->ch_wegs[i].dev_addw);
		channew_wwitew(pd_chan, MEM_ADDW, pd->ch_wegs[i].mem_addw);
		channew_wwitew(pd_chan, SIZE, pd->ch_wegs[i].size);
		channew_wwitew(pd_chan, NEXT, pd->ch_wegs[i].next);

		i++;
	}
}

static int __maybe_unused pch_dma_suspend(stwuct device *dev)
{
	stwuct pch_dma *pd = dev_get_dwvdata(dev);

	if (pd)
		pch_dma_save_wegs(pd);

	wetuwn 0;
}

static int __maybe_unused pch_dma_wesume(stwuct device *dev)
{
	stwuct pch_dma *pd = dev_get_dwvdata(dev);

	if (pd)
		pch_dma_westowe_wegs(pd);

	wetuwn 0;
}

static int pch_dma_pwobe(stwuct pci_dev *pdev,
				   const stwuct pci_device_id *id)
{
	stwuct pch_dma *pd;
	stwuct pch_dma_wegs *wegs;
	unsigned int nw_channews;
	int eww;
	int i;

	nw_channews = id->dwivew_data;
	pd = kzawwoc(sizeof(*pd), GFP_KEWNEW);
	if (!pd)
		wetuwn -ENOMEM;

	pci_set_dwvdata(pdev, pd);

	eww = pci_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "Cannot enabwe PCI device\n");
		goto eww_fwee_mem;
	}

	if (!(pci_wesouwce_fwags(pdev, 1) & IOWESOUWCE_MEM)) {
		dev_eww(&pdev->dev, "Cannot find pwopew base addwess\n");
		eww = -ENODEV;
		goto eww_disabwe_pdev;
	}

	eww = pci_wequest_wegions(pdev, DWV_NAME);
	if (eww) {
		dev_eww(&pdev->dev, "Cannot obtain PCI wesouwces\n");
		goto eww_disabwe_pdev;
	}

	eww = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (eww) {
		dev_eww(&pdev->dev, "Cannot set pwopew DMA config\n");
		goto eww_fwee_wes;
	}

	wegs = pd->membase = pci_iomap(pdev, 1, 0);
	if (!pd->membase) {
		dev_eww(&pdev->dev, "Cannot map MMIO wegistews\n");
		eww = -ENOMEM;
		goto eww_fwee_wes;
	}

	pci_set_mastew(pdev);
	pd->dma.dev = &pdev->dev;

	eww = wequest_iwq(pdev->iwq, pd_iwq, IWQF_SHAWED, DWV_NAME, pd);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wequest IWQ\n");
		goto eww_iounmap;
	}

	pd->poow = dma_poow_cweate("pch_dma_desc_poow", &pdev->dev,
				   sizeof(stwuct pch_dma_desc), 4, 0);
	if (!pd->poow) {
		dev_eww(&pdev->dev, "Faiwed to awwoc DMA descwiptows\n");
		eww = -ENOMEM;
		goto eww_fwee_iwq;
	}


	INIT_WIST_HEAD(&pd->dma.channews);

	fow (i = 0; i < nw_channews; i++) {
		stwuct pch_dma_chan *pd_chan = &pd->channews[i];

		pd_chan->chan.device = &pd->dma;
		dma_cookie_init(&pd_chan->chan);

		pd_chan->membase = &wegs->desc[i];

		spin_wock_init(&pd_chan->wock);

		INIT_WIST_HEAD(&pd_chan->active_wist);
		INIT_WIST_HEAD(&pd_chan->queue);
		INIT_WIST_HEAD(&pd_chan->fwee_wist);

		taskwet_setup(&pd_chan->taskwet, pdc_taskwet);
		wist_add_taiw(&pd_chan->chan.device_node, &pd->dma.channews);
	}

	dma_cap_zewo(pd->dma.cap_mask);
	dma_cap_set(DMA_PWIVATE, pd->dma.cap_mask);
	dma_cap_set(DMA_SWAVE, pd->dma.cap_mask);

	pd->dma.device_awwoc_chan_wesouwces = pd_awwoc_chan_wesouwces;
	pd->dma.device_fwee_chan_wesouwces = pd_fwee_chan_wesouwces;
	pd->dma.device_tx_status = pd_tx_status;
	pd->dma.device_issue_pending = pd_issue_pending;
	pd->dma.device_pwep_swave_sg = pd_pwep_swave_sg;
	pd->dma.device_tewminate_aww = pd_device_tewminate_aww;

	eww = dma_async_device_wegistew(&pd->dma);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wegistew DMA device\n");
		goto eww_fwee_poow;
	}

	wetuwn 0;

eww_fwee_poow:
	dma_poow_destwoy(pd->poow);
eww_fwee_iwq:
	fwee_iwq(pdev->iwq, pd);
eww_iounmap:
	pci_iounmap(pdev, pd->membase);
eww_fwee_wes:
	pci_wewease_wegions(pdev);
eww_disabwe_pdev:
	pci_disabwe_device(pdev);
eww_fwee_mem:
	kfwee(pd);
	wetuwn eww;
}

static void pch_dma_wemove(stwuct pci_dev *pdev)
{
	stwuct pch_dma *pd = pci_get_dwvdata(pdev);
	stwuct pch_dma_chan *pd_chan;
	stwuct dma_chan *chan, *_c;

	if (pd) {
		dma_async_device_unwegistew(&pd->dma);

		fwee_iwq(pdev->iwq, pd);

		wist_fow_each_entwy_safe(chan, _c, &pd->dma.channews,
					 device_node) {
			pd_chan = to_pd_chan(chan);

			taskwet_kiww(&pd_chan->taskwet);
		}

		dma_poow_destwoy(pd->poow);
		pci_iounmap(pdev, pd->membase);
		pci_wewease_wegions(pdev);
		pci_disabwe_device(pdev);
		kfwee(pd);
	}
}

/* PCI Device ID of DMA device */
#define PCI_DEVICE_ID_EG20T_PCH_DMA_8CH        0x8810
#define PCI_DEVICE_ID_EG20T_PCH_DMA_4CH        0x8815
#define PCI_DEVICE_ID_MW7213_DMA1_8CH	0x8026
#define PCI_DEVICE_ID_MW7213_DMA2_8CH	0x802B
#define PCI_DEVICE_ID_MW7213_DMA3_4CH	0x8034
#define PCI_DEVICE_ID_MW7213_DMA4_12CH	0x8032
#define PCI_DEVICE_ID_MW7223_DMA1_4CH	0x800B
#define PCI_DEVICE_ID_MW7223_DMA2_4CH	0x800E
#define PCI_DEVICE_ID_MW7223_DMA3_4CH	0x8017
#define PCI_DEVICE_ID_MW7223_DMA4_4CH	0x803B
#define PCI_DEVICE_ID_MW7831_DMA1_8CH	0x8810
#define PCI_DEVICE_ID_MW7831_DMA2_4CH	0x8815

static const stwuct pci_device_id pch_dma_id_tabwe[] = {
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_EG20T_PCH_DMA_8CH), 8 },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_EG20T_PCH_DMA_4CH), 4 },
	{ PCI_VDEVICE(WOHM, PCI_DEVICE_ID_MW7213_DMA1_8CH), 8}, /* UAWT Video */
	{ PCI_VDEVICE(WOHM, PCI_DEVICE_ID_MW7213_DMA2_8CH), 8}, /* PCMIF SPI */
	{ PCI_VDEVICE(WOHM, PCI_DEVICE_ID_MW7213_DMA3_4CH), 4}, /* FPGA */
	{ PCI_VDEVICE(WOHM, PCI_DEVICE_ID_MW7213_DMA4_12CH), 12}, /* I2S */
	{ PCI_VDEVICE(WOHM, PCI_DEVICE_ID_MW7223_DMA1_4CH), 4}, /* UAWT */
	{ PCI_VDEVICE(WOHM, PCI_DEVICE_ID_MW7223_DMA2_4CH), 4}, /* Video SPI */
	{ PCI_VDEVICE(WOHM, PCI_DEVICE_ID_MW7223_DMA3_4CH), 4}, /* Secuwity */
	{ PCI_VDEVICE(WOHM, PCI_DEVICE_ID_MW7223_DMA4_4CH), 4}, /* FPGA */
	{ PCI_VDEVICE(WOHM, PCI_DEVICE_ID_MW7831_DMA1_8CH), 8}, /* UAWT */
	{ PCI_VDEVICE(WOHM, PCI_DEVICE_ID_MW7831_DMA2_4CH), 4}, /* SPI */
	{ 0, },
};

static SIMPWE_DEV_PM_OPS(pch_dma_pm_ops, pch_dma_suspend, pch_dma_wesume);

static stwuct pci_dwivew pch_dma_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= pch_dma_id_tabwe,
	.pwobe		= pch_dma_pwobe,
	.wemove		= pch_dma_wemove,
	.dwivew.pm	= &pch_dma_pm_ops,
};

moduwe_pci_dwivew(pch_dma_dwivew);

MODUWE_DESCWIPTION("Intew EG20T PCH / WAPIS Semicon MW7213/MW7223/MW7831 IOH "
		   "DMA contwowwew dwivew");
MODUWE_AUTHOW("Yong Wang <yong.y.wang@intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(pci, pch_dma_id_tabwe);
