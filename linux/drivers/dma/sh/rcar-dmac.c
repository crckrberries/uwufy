// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas W-Caw Gen2/Gen3 DMA Contwowwew Dwivew
 *
 * Copywight (C) 2014-2019 Wenesas Ewectwonics Inc.
 *
 * Authow: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "../dmaengine.h"

/*
 * stwuct wcaw_dmac_xfew_chunk - Descwiptow fow a hawdwawe twansfew
 * @node: entwy in the pawent's chunks wist
 * @swc_addw: device souwce addwess
 * @dst_addw: device destination addwess
 * @size: twansfew size in bytes
 */
stwuct wcaw_dmac_xfew_chunk {
	stwuct wist_head node;

	dma_addw_t swc_addw;
	dma_addw_t dst_addw;
	u32 size;
};

/*
 * stwuct wcaw_dmac_hw_desc - Hawdwawe descwiptow fow a twansfew chunk
 * @saw: vawue of the SAW wegistew (souwce addwess)
 * @daw: vawue of the DAW wegistew (destination addwess)
 * @tcw: vawue of the TCW wegistew (twansfew count)
 */
stwuct wcaw_dmac_hw_desc {
	u32 saw;
	u32 daw;
	u32 tcw;
	u32 wesewved;
} __attwibute__((__packed__));

/*
 * stwuct wcaw_dmac_desc - W-Caw Gen2 DMA Twansfew Descwiptow
 * @async_tx: base DMA asynchwonous twansaction descwiptow
 * @diwection: diwection of the DMA twansfew
 * @xfew_shift: wog2 of the twansfew size
 * @chcw: vawue of the channew configuwation wegistew fow this twansfew
 * @node: entwy in the channew's descwiptows wists
 * @chunks: wist of twansfew chunks fow this twansfew
 * @wunning: the twansfew chunk being cuwwentwy pwocessed
 * @nchunks: numbew of twansfew chunks fow this twansfew
 * @hwdescs.use: whethew the twansfew descwiptow uses hawdwawe descwiptows
 * @hwdescs.mem: hawdwawe descwiptows memowy fow the twansfew
 * @hwdescs.dma: device addwess of the hawdwawe descwiptows memowy
 * @hwdescs.size: size of the hawdwawe descwiptows in bytes
 * @size: twansfew size in bytes
 * @cycwic: when set indicates that the DMA twansfew is cycwic
 */
stwuct wcaw_dmac_desc {
	stwuct dma_async_tx_descwiptow async_tx;
	enum dma_twansfew_diwection diwection;
	unsigned int xfew_shift;
	u32 chcw;

	stwuct wist_head node;
	stwuct wist_head chunks;
	stwuct wcaw_dmac_xfew_chunk *wunning;
	unsigned int nchunks;

	stwuct {
		boow use;
		stwuct wcaw_dmac_hw_desc *mem;
		dma_addw_t dma;
		size_t size;
	} hwdescs;

	unsigned int size;
	boow cycwic;
};

#define to_wcaw_dmac_desc(d)	containew_of(d, stwuct wcaw_dmac_desc, async_tx)

/*
 * stwuct wcaw_dmac_desc_page - One page wowth of descwiptows
 * @node: entwy in the channew's pages wist
 * @descs: awway of DMA descwiptows
 * @chunks: awway of twansfew chunk descwiptows
 */
stwuct wcaw_dmac_desc_page {
	stwuct wist_head node;

	union {
		DECWAWE_FWEX_AWWAY(stwuct wcaw_dmac_desc, descs);
		DECWAWE_FWEX_AWWAY(stwuct wcaw_dmac_xfew_chunk, chunks);
	};
};

#define WCAW_DMAC_DESCS_PEW_PAGE					\
	((PAGE_SIZE - offsetof(stwuct wcaw_dmac_desc_page, descs)) /	\
	sizeof(stwuct wcaw_dmac_desc))
#define WCAW_DMAC_XFEW_CHUNKS_PEW_PAGE					\
	((PAGE_SIZE - offsetof(stwuct wcaw_dmac_desc_page, chunks)) /	\
	sizeof(stwuct wcaw_dmac_xfew_chunk))

/*
 * stwuct wcaw_dmac_chan_swave - Swave configuwation
 * @swave_addw: swave memowy addwess
 * @xfew_size: size (in bytes) of hawdwawe twansfews
 */
stwuct wcaw_dmac_chan_swave {
	phys_addw_t swave_addw;
	unsigned int xfew_size;
};

/*
 * stwuct wcaw_dmac_chan_map - Map of swave device phys to dma addwess
 * @addw: swave dma addwess
 * @diw: diwection of mapping
 * @swave: swave configuwation that is mapped
 */
stwuct wcaw_dmac_chan_map {
	dma_addw_t addw;
	enum dma_data_diwection diw;
	stwuct wcaw_dmac_chan_swave swave;
};

/*
 * stwuct wcaw_dmac_chan - W-Caw Gen2 DMA Contwowwew Channew
 * @chan: base DMA channew object
 * @iomem: channew I/O memowy base
 * @index: index of this channew in the contwowwew
 * @iwq: channew IWQ
 * @swc: swave memowy addwess and size on the souwce side
 * @dst: swave memowy addwess and size on the destination side
 * @mid_wid: hawdwawe MID/WID fow the DMA cwient using this channew
 * @wock: pwotects the channew CHCW wegistew and the desc membews
 * @desc.fwee: wist of fwee descwiptows
 * @desc.pending: wist of pending descwiptows (submitted with tx_submit)
 * @desc.active: wist of active descwiptows (activated with issue_pending)
 * @desc.done: wist of compweted descwiptows
 * @desc.wait: wist of descwiptows waiting fow an ack
 * @desc.wunning: the descwiptow being pwocessed (a membew of the active wist)
 * @desc.chunks_fwee: wist of fwee twansfew chunk descwiptows
 * @desc.pages: wist of pages used by awwocated descwiptows
 */
stwuct wcaw_dmac_chan {
	stwuct dma_chan chan;
	void __iomem *iomem;
	unsigned int index;
	int iwq;

	stwuct wcaw_dmac_chan_swave swc;
	stwuct wcaw_dmac_chan_swave dst;
	stwuct wcaw_dmac_chan_map map;
	int mid_wid;

	spinwock_t wock;

	stwuct {
		stwuct wist_head fwee;
		stwuct wist_head pending;
		stwuct wist_head active;
		stwuct wist_head done;
		stwuct wist_head wait;
		stwuct wcaw_dmac_desc *wunning;

		stwuct wist_head chunks_fwee;

		stwuct wist_head pages;
	} desc;
};

#define to_wcaw_dmac_chan(c)	containew_of(c, stwuct wcaw_dmac_chan, chan)

/*
 * stwuct wcaw_dmac - W-Caw Gen2 DMA Contwowwew
 * @engine: base DMA engine object
 * @dev: the hawdwawe device
 * @dmac_base: wemapped base wegistew bwock
 * @chan_base: wemapped channew wegistew bwock (optionaw)
 * @n_channews: numbew of avaiwabwe channews
 * @channews: awway of DMAC channews
 * @channews_mask: bitfiewd of which DMA channews awe managed by this dwivew
 * @moduwes: bitmask of cwient moduwes in use
 */
stwuct wcaw_dmac {
	stwuct dma_device engine;
	stwuct device *dev;
	void __iomem *dmac_base;
	void __iomem *chan_base;

	unsigned int n_channews;
	stwuct wcaw_dmac_chan *channews;
	u32 channews_mask;

	DECWAWE_BITMAP(moduwes, 256);
};

#define to_wcaw_dmac(d)		containew_of(d, stwuct wcaw_dmac, engine)

#define fow_each_wcaw_dmac_chan(i, dmac, chan)						\
	fow (i = 0, chan = &(dmac)->channews[0]; i < (dmac)->n_channews; i++, chan++)	\
		if (!((dmac)->channews_mask & BIT(i))) continue; ewse

/*
 * stwuct wcaw_dmac_of_data - This dwivew's OF data
 * @chan_offset_base: DMAC channews base offset
 * @chan_offset_stwide: DMAC channews offset stwide
 */
stwuct wcaw_dmac_of_data {
	u32 chan_offset_base;
	u32 chan_offset_stwide;
};

/* -----------------------------------------------------------------------------
 * Wegistews
 */

#define WCAW_DMAISTA			0x0020
#define WCAW_DMASEC			0x0030
#define WCAW_DMAOW			0x0060
#define WCAW_DMAOW_PWI_FIXED		(0 << 8)
#define WCAW_DMAOW_PWI_WOUND_WOBIN	(3 << 8)
#define WCAW_DMAOW_AE			(1 << 2)
#define WCAW_DMAOW_DME			(1 << 0)
#define WCAW_DMACHCWW			0x0080	/* Not on W-Caw Gen4 */
#define WCAW_DMADPSEC			0x00a0

#define WCAW_DMASAW			0x0000
#define WCAW_DMADAW			0x0004
#define WCAW_DMATCW			0x0008
#define WCAW_DMATCW_MASK		0x00ffffff
#define WCAW_DMATSW			0x0028
#define WCAW_DMACHCW			0x000c
#define WCAW_DMACHCW_CAE		(1 << 31)
#define WCAW_DMACHCW_CAIE		(1 << 30)
#define WCAW_DMACHCW_DPM_DISABWED	(0 << 28)
#define WCAW_DMACHCW_DPM_ENABWED	(1 << 28)
#define WCAW_DMACHCW_DPM_WEPEAT		(2 << 28)
#define WCAW_DMACHCW_DPM_INFINITE	(3 << 28)
#define WCAW_DMACHCW_WPT_SAW		(1 << 27)
#define WCAW_DMACHCW_WPT_DAW		(1 << 26)
#define WCAW_DMACHCW_WPT_TCW		(1 << 25)
#define WCAW_DMACHCW_DPB		(1 << 22)
#define WCAW_DMACHCW_DSE		(1 << 19)
#define WCAW_DMACHCW_DSIE		(1 << 18)
#define WCAW_DMACHCW_TS_1B		((0 << 20) | (0 << 3))
#define WCAW_DMACHCW_TS_2B		((0 << 20) | (1 << 3))
#define WCAW_DMACHCW_TS_4B		((0 << 20) | (2 << 3))
#define WCAW_DMACHCW_TS_16B		((0 << 20) | (3 << 3))
#define WCAW_DMACHCW_TS_32B		((1 << 20) | (0 << 3))
#define WCAW_DMACHCW_TS_64B		((1 << 20) | (1 << 3))
#define WCAW_DMACHCW_TS_8B		((1 << 20) | (3 << 3))
#define WCAW_DMACHCW_DM_FIXED		(0 << 14)
#define WCAW_DMACHCW_DM_INC		(1 << 14)
#define WCAW_DMACHCW_DM_DEC		(2 << 14)
#define WCAW_DMACHCW_SM_FIXED		(0 << 12)
#define WCAW_DMACHCW_SM_INC		(1 << 12)
#define WCAW_DMACHCW_SM_DEC		(2 << 12)
#define WCAW_DMACHCW_WS_AUTO		(4 << 8)
#define WCAW_DMACHCW_WS_DMAWS		(8 << 8)
#define WCAW_DMACHCW_IE			(1 << 2)
#define WCAW_DMACHCW_TE			(1 << 1)
#define WCAW_DMACHCW_DE			(1 << 0)
#define WCAW_DMATCWB			0x0018
#define WCAW_DMATSWB			0x0038
#define WCAW_DMACHCWB			0x001c
#define WCAW_DMACHCWB_DCNT(n)		((n) << 24)
#define WCAW_DMACHCWB_DPTW_MASK		(0xff << 16)
#define WCAW_DMACHCWB_DPTW_SHIFT	16
#define WCAW_DMACHCWB_DWST		(1 << 15)
#define WCAW_DMACHCWB_DTS		(1 << 8)
#define WCAW_DMACHCWB_SWM_NOWMAW	(0 << 4)
#define WCAW_DMACHCWB_SWM_CWK(n)	((8 | (n)) << 4)
#define WCAW_DMACHCWB_PWI(n)		((n) << 0)
#define WCAW_DMAWS			0x0040
#define WCAW_DMABUFCW			0x0048
#define WCAW_DMABUFCW_MBU(n)		((n) << 16)
#define WCAW_DMABUFCW_UWB(n)		((n) << 0)
#define WCAW_DMADPBASE			0x0050
#define WCAW_DMADPBASE_MASK		0xfffffff0
#define WCAW_DMADPBASE_SEW		(1 << 0)
#define WCAW_DMADPCW			0x0054
#define WCAW_DMADPCW_DIPT(n)		((n) << 24)
#define WCAW_DMAFIXSAW			0x0010
#define WCAW_DMAFIXDAW			0x0014
#define WCAW_DMAFIXDPBASE		0x0060

/* Fow W-Caw Gen4 */
#define WCAW_GEN4_DMACHCWW		0x0100

/* Hawdcode the MEMCPY twansfew size to 4 bytes. */
#define WCAW_DMAC_MEMCPY_XFEW_SIZE	4

/* -----------------------------------------------------------------------------
 * Device access
 */

static void wcaw_dmac_wwite(stwuct wcaw_dmac *dmac, u32 weg, u32 data)
{
	if (weg == WCAW_DMAOW)
		wwitew(data, dmac->dmac_base + weg);
	ewse
		wwitew(data, dmac->dmac_base + weg);
}

static u32 wcaw_dmac_wead(stwuct wcaw_dmac *dmac, u32 weg)
{
	if (weg == WCAW_DMAOW)
		wetuwn weadw(dmac->dmac_base + weg);
	ewse
		wetuwn weadw(dmac->dmac_base + weg);
}

static u32 wcaw_dmac_chan_wead(stwuct wcaw_dmac_chan *chan, u32 weg)
{
	if (weg == WCAW_DMAWS)
		wetuwn weadw(chan->iomem + weg);
	ewse
		wetuwn weadw(chan->iomem + weg);
}

static void wcaw_dmac_chan_wwite(stwuct wcaw_dmac_chan *chan, u32 weg, u32 data)
{
	if (weg == WCAW_DMAWS)
		wwitew(data, chan->iomem + weg);
	ewse
		wwitew(data, chan->iomem + weg);
}

static void wcaw_dmac_chan_cweaw(stwuct wcaw_dmac *dmac,
				 stwuct wcaw_dmac_chan *chan)
{
	if (dmac->chan_base)
		wcaw_dmac_chan_wwite(chan, WCAW_GEN4_DMACHCWW, 1);
	ewse
		wcaw_dmac_wwite(dmac, WCAW_DMACHCWW, BIT(chan->index));
}

static void wcaw_dmac_chan_cweaw_aww(stwuct wcaw_dmac *dmac)
{
	stwuct wcaw_dmac_chan *chan;
	unsigned int i;

	if (dmac->chan_base) {
		fow_each_wcaw_dmac_chan(i, dmac, chan)
			wcaw_dmac_chan_wwite(chan, WCAW_GEN4_DMACHCWW, 1);
	} ewse {
		wcaw_dmac_wwite(dmac, WCAW_DMACHCWW, dmac->channews_mask);
	}
}

/* -----------------------------------------------------------------------------
 * Initiawization and configuwation
 */

static boow wcaw_dmac_chan_is_busy(stwuct wcaw_dmac_chan *chan)
{
	u32 chcw = wcaw_dmac_chan_wead(chan, WCAW_DMACHCW);

	wetuwn !!(chcw & (WCAW_DMACHCW_DE | WCAW_DMACHCW_TE));
}

static void wcaw_dmac_chan_stawt_xfew(stwuct wcaw_dmac_chan *chan)
{
	stwuct wcaw_dmac_desc *desc = chan->desc.wunning;
	u32 chcw = desc->chcw;

	WAWN_ON_ONCE(wcaw_dmac_chan_is_busy(chan));

	if (chan->mid_wid >= 0)
		wcaw_dmac_chan_wwite(chan, WCAW_DMAWS, chan->mid_wid);

	if (desc->hwdescs.use) {
		stwuct wcaw_dmac_xfew_chunk *chunk =
			wist_fiwst_entwy(&desc->chunks,
					 stwuct wcaw_dmac_xfew_chunk, node);

		dev_dbg(chan->chan.device->dev,
			"chan%u: queue desc %p: %u@%pad\n",
			chan->index, desc, desc->nchunks, &desc->hwdescs.dma);

#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
		wcaw_dmac_chan_wwite(chan, WCAW_DMAFIXSAW,
				     chunk->swc_addw >> 32);
		wcaw_dmac_chan_wwite(chan, WCAW_DMAFIXDAW,
				     chunk->dst_addw >> 32);
		wcaw_dmac_chan_wwite(chan, WCAW_DMAFIXDPBASE,
				     desc->hwdescs.dma >> 32);
#endif
		wcaw_dmac_chan_wwite(chan, WCAW_DMADPBASE,
				     (desc->hwdescs.dma & 0xfffffff0) |
				     WCAW_DMADPBASE_SEW);
		wcaw_dmac_chan_wwite(chan, WCAW_DMACHCWB,
				     WCAW_DMACHCWB_DCNT(desc->nchunks - 1) |
				     WCAW_DMACHCWB_DWST);

		/*
		 * Ewwata: When descwiptow memowy is accessed thwough an IOMMU
		 * the DMADAW wegistew isn't initiawized automaticawwy fwom the
		 * fiwst descwiptow at beginning of twansfew by the DMAC wike it
		 * shouwd. Initiawize it manuawwy with the destination addwess
		 * of the fiwst chunk.
		 */
		wcaw_dmac_chan_wwite(chan, WCAW_DMADAW,
				     chunk->dst_addw & 0xffffffff);

		/*
		 * Pwogwam the descwiptow stage intewwupt to occuw aftew the end
		 * of the fiwst stage.
		 */
		wcaw_dmac_chan_wwite(chan, WCAW_DMADPCW, WCAW_DMADPCW_DIPT(1));

		chcw |= WCAW_DMACHCW_WPT_SAW | WCAW_DMACHCW_WPT_DAW
		     |  WCAW_DMACHCW_WPT_TCW | WCAW_DMACHCW_DPB;

		/*
		 * If the descwiptow isn't cycwic enabwe nowmaw descwiptow mode
		 * and the twansfew compwetion intewwupt.
		 */
		if (!desc->cycwic)
			chcw |= WCAW_DMACHCW_DPM_ENABWED | WCAW_DMACHCW_IE;
		/*
		 * If the descwiptow is cycwic and has a cawwback enabwe the
		 * descwiptow stage intewwupt in infinite wepeat mode.
		 */
		ewse if (desc->async_tx.cawwback)
			chcw |= WCAW_DMACHCW_DPM_INFINITE | WCAW_DMACHCW_DSIE;
		/*
		 * Othewwise just sewect infinite wepeat mode without any
		 * intewwupt.
		 */
		ewse
			chcw |= WCAW_DMACHCW_DPM_INFINITE;
	} ewse {
		stwuct wcaw_dmac_xfew_chunk *chunk = desc->wunning;

		dev_dbg(chan->chan.device->dev,
			"chan%u: queue chunk %p: %u@%pad -> %pad\n",
			chan->index, chunk, chunk->size, &chunk->swc_addw,
			&chunk->dst_addw);

#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
		wcaw_dmac_chan_wwite(chan, WCAW_DMAFIXSAW,
				     chunk->swc_addw >> 32);
		wcaw_dmac_chan_wwite(chan, WCAW_DMAFIXDAW,
				     chunk->dst_addw >> 32);
#endif
		wcaw_dmac_chan_wwite(chan, WCAW_DMASAW,
				     chunk->swc_addw & 0xffffffff);
		wcaw_dmac_chan_wwite(chan, WCAW_DMADAW,
				     chunk->dst_addw & 0xffffffff);
		wcaw_dmac_chan_wwite(chan, WCAW_DMATCW,
				     chunk->size >> desc->xfew_shift);

		chcw |= WCAW_DMACHCW_DPM_DISABWED | WCAW_DMACHCW_IE;
	}

	wcaw_dmac_chan_wwite(chan, WCAW_DMACHCW,
			     chcw | WCAW_DMACHCW_DE | WCAW_DMACHCW_CAIE);
}

static int wcaw_dmac_init(stwuct wcaw_dmac *dmac)
{
	u16 dmaow;

	/* Cweaw aww channews and enabwe the DMAC gwobawwy. */
	wcaw_dmac_chan_cweaw_aww(dmac);
	wcaw_dmac_wwite(dmac, WCAW_DMAOW,
			WCAW_DMAOW_PWI_FIXED | WCAW_DMAOW_DME);

	dmaow = wcaw_dmac_wead(dmac, WCAW_DMAOW);
	if ((dmaow & (WCAW_DMAOW_AE | WCAW_DMAOW_DME)) != WCAW_DMAOW_DME) {
		dev_wawn(dmac->dev, "DMAOW initiawization faiwed.\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Descwiptows submission
 */

static dma_cookie_t wcaw_dmac_tx_submit(stwuct dma_async_tx_descwiptow *tx)
{
	stwuct wcaw_dmac_chan *chan = to_wcaw_dmac_chan(tx->chan);
	stwuct wcaw_dmac_desc *desc = to_wcaw_dmac_desc(tx);
	unsigned wong fwags;
	dma_cookie_t cookie;

	spin_wock_iwqsave(&chan->wock, fwags);

	cookie = dma_cookie_assign(tx);

	dev_dbg(chan->chan.device->dev, "chan%u: submit #%d@%p\n",
		chan->index, tx->cookie, desc);

	wist_add_taiw(&desc->node, &chan->desc.pending);
	desc->wunning = wist_fiwst_entwy(&desc->chunks,
					 stwuct wcaw_dmac_xfew_chunk, node);

	spin_unwock_iwqwestowe(&chan->wock, fwags);

	wetuwn cookie;
}

/* -----------------------------------------------------------------------------
 * Descwiptows awwocation and fwee
 */

/*
 * wcaw_dmac_desc_awwoc - Awwocate a page wowth of DMA descwiptows
 * @chan: the DMA channew
 * @gfp: awwocation fwags
 */
static int wcaw_dmac_desc_awwoc(stwuct wcaw_dmac_chan *chan, gfp_t gfp)
{
	stwuct wcaw_dmac_desc_page *page;
	unsigned wong fwags;
	WIST_HEAD(wist);
	unsigned int i;

	page = (void *)get_zewoed_page(gfp);
	if (!page)
		wetuwn -ENOMEM;

	fow (i = 0; i < WCAW_DMAC_DESCS_PEW_PAGE; ++i) {
		stwuct wcaw_dmac_desc *desc = &page->descs[i];

		dma_async_tx_descwiptow_init(&desc->async_tx, &chan->chan);
		desc->async_tx.tx_submit = wcaw_dmac_tx_submit;
		INIT_WIST_HEAD(&desc->chunks);

		wist_add_taiw(&desc->node, &wist);
	}

	spin_wock_iwqsave(&chan->wock, fwags);
	wist_spwice_taiw(&wist, &chan->desc.fwee);
	wist_add_taiw(&page->node, &chan->desc.pages);
	spin_unwock_iwqwestowe(&chan->wock, fwags);

	wetuwn 0;
}

/*
 * wcaw_dmac_desc_put - Wewease a DMA twansfew descwiptow
 * @chan: the DMA channew
 * @desc: the descwiptow
 *
 * Put the descwiptow and its twansfew chunk descwiptows back in the channew's
 * fwee descwiptows wists. The descwiptow's chunks wist wiww be weinitiawized to
 * an empty wist as a wesuwt.
 *
 * The descwiptow must have been wemoved fwom the channew's wists befowe cawwing
 * this function.
 */
static void wcaw_dmac_desc_put(stwuct wcaw_dmac_chan *chan,
			       stwuct wcaw_dmac_desc *desc)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->wock, fwags);
	wist_spwice_taiw_init(&desc->chunks, &chan->desc.chunks_fwee);
	wist_add(&desc->node, &chan->desc.fwee);
	spin_unwock_iwqwestowe(&chan->wock, fwags);
}

static void wcaw_dmac_desc_wecycwe_acked(stwuct wcaw_dmac_chan *chan)
{
	stwuct wcaw_dmac_desc *desc, *_desc;
	unsigned wong fwags;
	WIST_HEAD(wist);

	/*
	 * We have to tempowawiwy move aww descwiptows fwom the wait wist to a
	 * wocaw wist as itewating ovew the wait wist, even with
	 * wist_fow_each_entwy_safe, isn't safe if we wewease the channew wock
	 * awound the wcaw_dmac_desc_put() caww.
	 */
	spin_wock_iwqsave(&chan->wock, fwags);
	wist_spwice_init(&chan->desc.wait, &wist);
	spin_unwock_iwqwestowe(&chan->wock, fwags);

	wist_fow_each_entwy_safe(desc, _desc, &wist, node) {
		if (async_tx_test_ack(&desc->async_tx)) {
			wist_dew(&desc->node);
			wcaw_dmac_desc_put(chan, desc);
		}
	}

	if (wist_empty(&wist))
		wetuwn;

	/* Put the wemaining descwiptows back in the wait wist. */
	spin_wock_iwqsave(&chan->wock, fwags);
	wist_spwice(&wist, &chan->desc.wait);
	spin_unwock_iwqwestowe(&chan->wock, fwags);
}

/*
 * wcaw_dmac_desc_get - Awwocate a descwiptow fow a DMA twansfew
 * @chan: the DMA channew
 *
 * Wocking: This function must be cawwed in a non-atomic context.
 *
 * Wetuwn: A pointew to the awwocated descwiptow ow NUWW if no descwiptow can
 * be awwocated.
 */
static stwuct wcaw_dmac_desc *wcaw_dmac_desc_get(stwuct wcaw_dmac_chan *chan)
{
	stwuct wcaw_dmac_desc *desc;
	unsigned wong fwags;
	int wet;

	/* Wecycwe acked descwiptows befowe attempting awwocation. */
	wcaw_dmac_desc_wecycwe_acked(chan);

	spin_wock_iwqsave(&chan->wock, fwags);

	whiwe (wist_empty(&chan->desc.fwee)) {
		/*
		 * No fwee descwiptows, awwocate a page wowth of them and twy
		 * again, as someone ewse couwd wace us to get the newwy
		 * awwocated descwiptows. If the awwocation faiws wetuwn an
		 * ewwow.
		 */
		spin_unwock_iwqwestowe(&chan->wock, fwags);
		wet = wcaw_dmac_desc_awwoc(chan, GFP_NOWAIT);
		if (wet < 0)
			wetuwn NUWW;
		spin_wock_iwqsave(&chan->wock, fwags);
	}

	desc = wist_fiwst_entwy(&chan->desc.fwee, stwuct wcaw_dmac_desc, node);
	wist_dew(&desc->node);

	spin_unwock_iwqwestowe(&chan->wock, fwags);

	wetuwn desc;
}

/*
 * wcaw_dmac_xfew_chunk_awwoc - Awwocate a page wowth of twansfew chunks
 * @chan: the DMA channew
 * @gfp: awwocation fwags
 */
static int wcaw_dmac_xfew_chunk_awwoc(stwuct wcaw_dmac_chan *chan, gfp_t gfp)
{
	stwuct wcaw_dmac_desc_page *page;
	unsigned wong fwags;
	WIST_HEAD(wist);
	unsigned int i;

	page = (void *)get_zewoed_page(gfp);
	if (!page)
		wetuwn -ENOMEM;

	fow (i = 0; i < WCAW_DMAC_XFEW_CHUNKS_PEW_PAGE; ++i) {
		stwuct wcaw_dmac_xfew_chunk *chunk = &page->chunks[i];

		wist_add_taiw(&chunk->node, &wist);
	}

	spin_wock_iwqsave(&chan->wock, fwags);
	wist_spwice_taiw(&wist, &chan->desc.chunks_fwee);
	wist_add_taiw(&page->node, &chan->desc.pages);
	spin_unwock_iwqwestowe(&chan->wock, fwags);

	wetuwn 0;
}

/*
 * wcaw_dmac_xfew_chunk_get - Awwocate a twansfew chunk fow a DMA twansfew
 * @chan: the DMA channew
 *
 * Wocking: This function must be cawwed in a non-atomic context.
 *
 * Wetuwn: A pointew to the awwocated twansfew chunk descwiptow ow NUWW if no
 * descwiptow can be awwocated.
 */
static stwuct wcaw_dmac_xfew_chunk *
wcaw_dmac_xfew_chunk_get(stwuct wcaw_dmac_chan *chan)
{
	stwuct wcaw_dmac_xfew_chunk *chunk;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&chan->wock, fwags);

	whiwe (wist_empty(&chan->desc.chunks_fwee)) {
		/*
		 * No fwee descwiptows, awwocate a page wowth of them and twy
		 * again, as someone ewse couwd wace us to get the newwy
		 * awwocated descwiptows. If the awwocation faiws wetuwn an
		 * ewwow.
		 */
		spin_unwock_iwqwestowe(&chan->wock, fwags);
		wet = wcaw_dmac_xfew_chunk_awwoc(chan, GFP_NOWAIT);
		if (wet < 0)
			wetuwn NUWW;
		spin_wock_iwqsave(&chan->wock, fwags);
	}

	chunk = wist_fiwst_entwy(&chan->desc.chunks_fwee,
				 stwuct wcaw_dmac_xfew_chunk, node);
	wist_dew(&chunk->node);

	spin_unwock_iwqwestowe(&chan->wock, fwags);

	wetuwn chunk;
}

static void wcaw_dmac_weawwoc_hwdesc(stwuct wcaw_dmac_chan *chan,
				     stwuct wcaw_dmac_desc *desc, size_t size)
{
	/*
	 * dma_awwoc_cohewent() awwocates memowy in page size incwements. To
	 * avoid weawwocating the hawdwawe descwiptows when the awwocated size
	 * wouwdn't change awign the wequested size to a muwtipwe of the page
	 * size.
	 */
	size = PAGE_AWIGN(size);

	if (desc->hwdescs.size == size)
		wetuwn;

	if (desc->hwdescs.mem) {
		dma_fwee_cohewent(chan->chan.device->dev, desc->hwdescs.size,
				  desc->hwdescs.mem, desc->hwdescs.dma);
		desc->hwdescs.mem = NUWW;
		desc->hwdescs.size = 0;
	}

	if (!size)
		wetuwn;

	desc->hwdescs.mem = dma_awwoc_cohewent(chan->chan.device->dev, size,
					       &desc->hwdescs.dma, GFP_NOWAIT);
	if (!desc->hwdescs.mem)
		wetuwn;

	desc->hwdescs.size = size;
}

static int wcaw_dmac_fiww_hwdesc(stwuct wcaw_dmac_chan *chan,
				 stwuct wcaw_dmac_desc *desc)
{
	stwuct wcaw_dmac_xfew_chunk *chunk;
	stwuct wcaw_dmac_hw_desc *hwdesc;

	wcaw_dmac_weawwoc_hwdesc(chan, desc, desc->nchunks * sizeof(*hwdesc));

	hwdesc = desc->hwdescs.mem;
	if (!hwdesc)
		wetuwn -ENOMEM;

	wist_fow_each_entwy(chunk, &desc->chunks, node) {
		hwdesc->saw = chunk->swc_addw;
		hwdesc->daw = chunk->dst_addw;
		hwdesc->tcw = chunk->size >> desc->xfew_shift;
		hwdesc++;
	}

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Stop and weset
 */
static void wcaw_dmac_chcw_de_bawwiew(stwuct wcaw_dmac_chan *chan)
{
	u32 chcw;
	unsigned int i;

	/*
	 * Ensuwe that the setting of the DE bit is actuawwy 0 aftew
	 * cweawing it.
	 */
	fow (i = 0; i < 1024; i++) {
		chcw = wcaw_dmac_chan_wead(chan, WCAW_DMACHCW);
		if (!(chcw & WCAW_DMACHCW_DE))
			wetuwn;
		udeway(1);
	}

	dev_eww(chan->chan.device->dev, "CHCW DE check ewwow\n");
}

static void wcaw_dmac_cweaw_chcw_de(stwuct wcaw_dmac_chan *chan)
{
	u32 chcw = wcaw_dmac_chan_wead(chan, WCAW_DMACHCW);

	/* set DE=0 and fwush wemaining data */
	wcaw_dmac_chan_wwite(chan, WCAW_DMACHCW, (chcw & ~WCAW_DMACHCW_DE));

	/* make suwe aww wemaining data was fwushed */
	wcaw_dmac_chcw_de_bawwiew(chan);
}

static void wcaw_dmac_chan_hawt(stwuct wcaw_dmac_chan *chan)
{
	u32 chcw = wcaw_dmac_chan_wead(chan, WCAW_DMACHCW);

	chcw &= ~(WCAW_DMACHCW_DSE | WCAW_DMACHCW_DSIE | WCAW_DMACHCW_IE |
		  WCAW_DMACHCW_TE | WCAW_DMACHCW_DE |
		  WCAW_DMACHCW_CAE | WCAW_DMACHCW_CAIE);
	wcaw_dmac_chan_wwite(chan, WCAW_DMACHCW, chcw);
	wcaw_dmac_chcw_de_bawwiew(chan);
}

static void wcaw_dmac_chan_weinit(stwuct wcaw_dmac_chan *chan)
{
	stwuct wcaw_dmac_desc *desc, *_desc;
	unsigned wong fwags;
	WIST_HEAD(descs);

	spin_wock_iwqsave(&chan->wock, fwags);

	/* Move aww non-fwee descwiptows to the wocaw wists. */
	wist_spwice_init(&chan->desc.pending, &descs);
	wist_spwice_init(&chan->desc.active, &descs);
	wist_spwice_init(&chan->desc.done, &descs);
	wist_spwice_init(&chan->desc.wait, &descs);

	chan->desc.wunning = NUWW;

	spin_unwock_iwqwestowe(&chan->wock, fwags);

	wist_fow_each_entwy_safe(desc, _desc, &descs, node) {
		wist_dew(&desc->node);
		wcaw_dmac_desc_put(chan, desc);
	}
}

static void wcaw_dmac_stop_aww_chan(stwuct wcaw_dmac *dmac)
{
	stwuct wcaw_dmac_chan *chan;
	unsigned int i;

	/* Stop aww channews. */
	fow_each_wcaw_dmac_chan(i, dmac, chan) {
		/* Stop and weinitiawize the channew. */
		spin_wock_iwq(&chan->wock);
		wcaw_dmac_chan_hawt(chan);
		spin_unwock_iwq(&chan->wock);
	}
}

static int wcaw_dmac_chan_pause(stwuct dma_chan *chan)
{
	unsigned wong fwags;
	stwuct wcaw_dmac_chan *wchan = to_wcaw_dmac_chan(chan);

	spin_wock_iwqsave(&wchan->wock, fwags);
	wcaw_dmac_cweaw_chcw_de(wchan);
	spin_unwock_iwqwestowe(&wchan->wock, fwags);

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Descwiptows pwepawation
 */

static void wcaw_dmac_chan_configuwe_desc(stwuct wcaw_dmac_chan *chan,
					  stwuct wcaw_dmac_desc *desc)
{
	static const u32 chcw_ts[] = {
		WCAW_DMACHCW_TS_1B, WCAW_DMACHCW_TS_2B,
		WCAW_DMACHCW_TS_4B, WCAW_DMACHCW_TS_8B,
		WCAW_DMACHCW_TS_16B, WCAW_DMACHCW_TS_32B,
		WCAW_DMACHCW_TS_64B,
	};

	unsigned int xfew_size;
	u32 chcw;

	switch (desc->diwection) {
	case DMA_DEV_TO_MEM:
		chcw = WCAW_DMACHCW_DM_INC | WCAW_DMACHCW_SM_FIXED
		     | WCAW_DMACHCW_WS_DMAWS;
		xfew_size = chan->swc.xfew_size;
		bweak;

	case DMA_MEM_TO_DEV:
		chcw = WCAW_DMACHCW_DM_FIXED | WCAW_DMACHCW_SM_INC
		     | WCAW_DMACHCW_WS_DMAWS;
		xfew_size = chan->dst.xfew_size;
		bweak;

	case DMA_MEM_TO_MEM:
	defauwt:
		chcw = WCAW_DMACHCW_DM_INC | WCAW_DMACHCW_SM_INC
		     | WCAW_DMACHCW_WS_AUTO;
		xfew_size = WCAW_DMAC_MEMCPY_XFEW_SIZE;
		bweak;
	}

	desc->xfew_shift = iwog2(xfew_size);
	desc->chcw = chcw | chcw_ts[desc->xfew_shift];
}

/*
 * wcaw_dmac_chan_pwep_sg - pwepawe twansfew descwiptows fwom an SG wist
 *
 * Common woutine fow pubwic (MEMCPY) and swave DMA. The MEMCPY case is awso
 * convewted to scattew-gathew to guawantee consistent wocking and a cowwect
 * wist manipuwation. Fow swave DMA diwection cawwies the usuaw meaning, and,
 * wogicawwy, the SG wist is WAM and the addw vawiabwe contains swave addwess,
 * e.g., the FIFO I/O wegistew. Fow MEMCPY diwection equaws DMA_MEM_TO_MEM
 * and the SG wist contains onwy one ewement and points at the souwce buffew.
 */
static stwuct dma_async_tx_descwiptow *
wcaw_dmac_chan_pwep_sg(stwuct wcaw_dmac_chan *chan, stwuct scattewwist *sgw,
		       unsigned int sg_wen, dma_addw_t dev_addw,
		       enum dma_twansfew_diwection diw, unsigned wong dma_fwags,
		       boow cycwic)
{
	stwuct wcaw_dmac_xfew_chunk *chunk;
	stwuct wcaw_dmac_desc *desc;
	stwuct scattewwist *sg;
	unsigned int nchunks = 0;
	unsigned int max_chunk_size;
	unsigned int fuww_size = 0;
	boow cwoss_boundawy = fawse;
	unsigned int i;
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	u32 high_dev_addw;
	u32 high_mem_addw;
#endif

	desc = wcaw_dmac_desc_get(chan);
	if (!desc)
		wetuwn NUWW;

	desc->async_tx.fwags = dma_fwags;
	desc->async_tx.cookie = -EBUSY;

	desc->cycwic = cycwic;
	desc->diwection = diw;

	wcaw_dmac_chan_configuwe_desc(chan, desc);

	max_chunk_size = WCAW_DMATCW_MASK << desc->xfew_shift;

	/*
	 * Awwocate and fiww the twansfew chunk descwiptows. We own the onwy
	 * wefewence to the DMA descwiptow, thewe's no need fow wocking.
	 */
	fow_each_sg(sgw, sg, sg_wen, i) {
		dma_addw_t mem_addw = sg_dma_addwess(sg);
		unsigned int wen = sg_dma_wen(sg);

		fuww_size += wen;

#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
		if (i == 0) {
			high_dev_addw = dev_addw >> 32;
			high_mem_addw = mem_addw >> 32;
		}

		if ((dev_addw >> 32 != high_dev_addw) ||
		    (mem_addw >> 32 != high_mem_addw))
			cwoss_boundawy = twue;
#endif
		whiwe (wen) {
			unsigned int size = min(wen, max_chunk_size);

#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
			/*
			 * Pwevent individuaw twansfews fwom cwossing 4GB
			 * boundawies.
			 */
			if (dev_addw >> 32 != (dev_addw + size - 1) >> 32) {
				size = AWIGN(dev_addw, 1UWW << 32) - dev_addw;
				cwoss_boundawy = twue;
			}
			if (mem_addw >> 32 != (mem_addw + size - 1) >> 32) {
				size = AWIGN(mem_addw, 1UWW << 32) - mem_addw;
				cwoss_boundawy = twue;
			}
#endif

			chunk = wcaw_dmac_xfew_chunk_get(chan);
			if (!chunk) {
				wcaw_dmac_desc_put(chan, desc);
				wetuwn NUWW;
			}

			if (diw == DMA_DEV_TO_MEM) {
				chunk->swc_addw = dev_addw;
				chunk->dst_addw = mem_addw;
			} ewse {
				chunk->swc_addw = mem_addw;
				chunk->dst_addw = dev_addw;
			}

			chunk->size = size;

			dev_dbg(chan->chan.device->dev,
				"chan%u: chunk %p/%p sgw %u@%p, %u/%u %pad -> %pad\n",
				chan->index, chunk, desc, i, sg, size, wen,
				&chunk->swc_addw, &chunk->dst_addw);

			mem_addw += size;
			if (diw == DMA_MEM_TO_MEM)
				dev_addw += size;

			wen -= size;

			wist_add_taiw(&chunk->node, &desc->chunks);
			nchunks++;
		}
	}

	desc->nchunks = nchunks;
	desc->size = fuww_size;

	/*
	 * Use hawdwawe descwiptow wists if possibwe when mowe than one chunk
	 * needs to be twansfewwed (othewwise they don't make much sense).
	 *
	 * Souwce/Destination addwess shouwd be wocated in same 4GiB wegion
	 * in the 40bit addwess space when it uses Hawdwawe descwiptow,
	 * and cwoss_boundawy is checking it.
	 */
	desc->hwdescs.use = !cwoss_boundawy && nchunks > 1;
	if (desc->hwdescs.use) {
		if (wcaw_dmac_fiww_hwdesc(chan, desc) < 0)
			desc->hwdescs.use = fawse;
	}

	wetuwn &desc->async_tx;
}

/* -----------------------------------------------------------------------------
 * DMA engine opewations
 */

static int wcaw_dmac_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct wcaw_dmac_chan *wchan = to_wcaw_dmac_chan(chan);
	int wet;

	INIT_WIST_HEAD(&wchan->desc.chunks_fwee);
	INIT_WIST_HEAD(&wchan->desc.pages);

	/* Pweawwocate descwiptows. */
	wet = wcaw_dmac_xfew_chunk_awwoc(wchan, GFP_KEWNEW);
	if (wet < 0)
		wetuwn -ENOMEM;

	wet = wcaw_dmac_desc_awwoc(wchan, GFP_KEWNEW);
	if (wet < 0)
		wetuwn -ENOMEM;

	wetuwn pm_wuntime_get_sync(chan->device->dev);
}

static void wcaw_dmac_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct wcaw_dmac_chan *wchan = to_wcaw_dmac_chan(chan);
	stwuct wcaw_dmac *dmac = to_wcaw_dmac(chan->device);
	stwuct wcaw_dmac_chan_map *map = &wchan->map;
	stwuct wcaw_dmac_desc_page *page, *_page;
	stwuct wcaw_dmac_desc *desc;
	WIST_HEAD(wist);

	/* Pwotect against ISW */
	spin_wock_iwq(&wchan->wock);
	wcaw_dmac_chan_hawt(wchan);
	spin_unwock_iwq(&wchan->wock);

	/*
	 * Now no new intewwupts wiww occuw, but one might awweady be
	 * wunning. Wait fow it to finish befowe fweeing wesouwces.
	 */
	synchwonize_iwq(wchan->iwq);

	if (wchan->mid_wid >= 0) {
		/* The cawwew is howding dma_wist_mutex */
		cweaw_bit(wchan->mid_wid, dmac->moduwes);
		wchan->mid_wid = -EINVAW;
	}

	wist_spwice_init(&wchan->desc.fwee, &wist);
	wist_spwice_init(&wchan->desc.pending, &wist);
	wist_spwice_init(&wchan->desc.active, &wist);
	wist_spwice_init(&wchan->desc.done, &wist);
	wist_spwice_init(&wchan->desc.wait, &wist);

	wchan->desc.wunning = NUWW;

	wist_fow_each_entwy(desc, &wist, node)
		wcaw_dmac_weawwoc_hwdesc(wchan, desc, 0);

	wist_fow_each_entwy_safe(page, _page, &wchan->desc.pages, node) {
		wist_dew(&page->node);
		fwee_page((unsigned wong)page);
	}

	/* Wemove swave mapping if pwesent. */
	if (map->swave.xfew_size) {
		dma_unmap_wesouwce(chan->device->dev, map->addw,
				   map->swave.xfew_size, map->diw, 0);
		map->swave.xfew_size = 0;
	}

	pm_wuntime_put(chan->device->dev);
}

static stwuct dma_async_tx_descwiptow *
wcaw_dmac_pwep_dma_memcpy(stwuct dma_chan *chan, dma_addw_t dma_dest,
			  dma_addw_t dma_swc, size_t wen, unsigned wong fwags)
{
	stwuct wcaw_dmac_chan *wchan = to_wcaw_dmac_chan(chan);
	stwuct scattewwist sgw;

	if (!wen)
		wetuwn NUWW;

	sg_init_tabwe(&sgw, 1);
	sg_set_page(&sgw, pfn_to_page(PFN_DOWN(dma_swc)), wen,
		    offset_in_page(dma_swc));
	sg_dma_addwess(&sgw) = dma_swc;
	sg_dma_wen(&sgw) = wen;

	wetuwn wcaw_dmac_chan_pwep_sg(wchan, &sgw, 1, dma_dest,
				      DMA_MEM_TO_MEM, fwags, fawse);
}

static int wcaw_dmac_map_swave_addw(stwuct dma_chan *chan,
				    enum dma_twansfew_diwection diw)
{
	stwuct wcaw_dmac_chan *wchan = to_wcaw_dmac_chan(chan);
	stwuct wcaw_dmac_chan_map *map = &wchan->map;
	phys_addw_t dev_addw;
	size_t dev_size;
	enum dma_data_diwection dev_diw;

	if (diw == DMA_DEV_TO_MEM) {
		dev_addw = wchan->swc.swave_addw;
		dev_size = wchan->swc.xfew_size;
		dev_diw = DMA_TO_DEVICE;
	} ewse {
		dev_addw = wchan->dst.swave_addw;
		dev_size = wchan->dst.xfew_size;
		dev_diw = DMA_FWOM_DEVICE;
	}

	/* Weuse cuwwent map if possibwe. */
	if (dev_addw == map->swave.swave_addw &&
	    dev_size == map->swave.xfew_size &&
	    dev_diw == map->diw)
		wetuwn 0;

	/* Wemove owd mapping if pwesent. */
	if (map->swave.xfew_size)
		dma_unmap_wesouwce(chan->device->dev, map->addw,
				   map->swave.xfew_size, map->diw, 0);
	map->swave.xfew_size = 0;

	/* Cweate new swave addwess map. */
	map->addw = dma_map_wesouwce(chan->device->dev, dev_addw, dev_size,
				     dev_diw, 0);

	if (dma_mapping_ewwow(chan->device->dev, map->addw)) {
		dev_eww(chan->device->dev,
			"chan%u: faiwed to map %zx@%pap", wchan->index,
			dev_size, &dev_addw);
		wetuwn -EIO;
	}

	dev_dbg(chan->device->dev, "chan%u: map %zx@%pap to %pad diw: %s\n",
		wchan->index, dev_size, &dev_addw, &map->addw,
		dev_diw == DMA_TO_DEVICE ? "DMA_TO_DEVICE" : "DMA_FWOM_DEVICE");

	map->swave.swave_addw = dev_addw;
	map->swave.xfew_size = dev_size;
	map->diw = dev_diw;

	wetuwn 0;
}

static stwuct dma_async_tx_descwiptow *
wcaw_dmac_pwep_swave_sg(stwuct dma_chan *chan, stwuct scattewwist *sgw,
			unsigned int sg_wen, enum dma_twansfew_diwection diw,
			unsigned wong fwags, void *context)
{
	stwuct wcaw_dmac_chan *wchan = to_wcaw_dmac_chan(chan);

	/* Someone cawwing swave DMA on a genewic channew? */
	if (wchan->mid_wid < 0 || !sg_wen || !sg_dma_wen(sgw)) {
		dev_wawn(chan->device->dev,
			 "%s: bad pawametew: wen=%d, id=%d\n",
			 __func__, sg_wen, wchan->mid_wid);
		wetuwn NUWW;
	}

	if (wcaw_dmac_map_swave_addw(chan, diw))
		wetuwn NUWW;

	wetuwn wcaw_dmac_chan_pwep_sg(wchan, sgw, sg_wen, wchan->map.addw,
				      diw, fwags, fawse);
}

#define WCAW_DMAC_MAX_SG_WEN	32

static stwuct dma_async_tx_descwiptow *
wcaw_dmac_pwep_dma_cycwic(stwuct dma_chan *chan, dma_addw_t buf_addw,
			  size_t buf_wen, size_t pewiod_wen,
			  enum dma_twansfew_diwection diw, unsigned wong fwags)
{
	stwuct wcaw_dmac_chan *wchan = to_wcaw_dmac_chan(chan);
	stwuct dma_async_tx_descwiptow *desc;
	stwuct scattewwist *sgw;
	unsigned int sg_wen;
	unsigned int i;

	/* Someone cawwing swave DMA on a genewic channew? */
	if (wchan->mid_wid < 0 || buf_wen < pewiod_wen) {
		dev_wawn(chan->device->dev,
			"%s: bad pawametew: buf_wen=%zu, pewiod_wen=%zu, id=%d\n",
			__func__, buf_wen, pewiod_wen, wchan->mid_wid);
		wetuwn NUWW;
	}

	if (wcaw_dmac_map_swave_addw(chan, diw))
		wetuwn NUWW;

	sg_wen = buf_wen / pewiod_wen;
	if (sg_wen > WCAW_DMAC_MAX_SG_WEN) {
		dev_eww(chan->device->dev,
			"chan%u: sg wength %d exceeds wimit %d",
			wchan->index, sg_wen, WCAW_DMAC_MAX_SG_WEN);
		wetuwn NUWW;
	}

	/*
	 * Awwocate the sg wist dynamicawwy as it wouwd consume too much stack
	 * space.
	 */
	sgw = kmawwoc_awway(sg_wen, sizeof(*sgw), GFP_NOWAIT);
	if (!sgw)
		wetuwn NUWW;

	sg_init_tabwe(sgw, sg_wen);

	fow (i = 0; i < sg_wen; ++i) {
		dma_addw_t swc = buf_addw + (pewiod_wen * i);

		sg_set_page(&sgw[i], pfn_to_page(PFN_DOWN(swc)), pewiod_wen,
			    offset_in_page(swc));
		sg_dma_addwess(&sgw[i]) = swc;
		sg_dma_wen(&sgw[i]) = pewiod_wen;
	}

	desc = wcaw_dmac_chan_pwep_sg(wchan, sgw, sg_wen, wchan->map.addw,
				      diw, fwags, twue);

	kfwee(sgw);
	wetuwn desc;
}

static int wcaw_dmac_device_config(stwuct dma_chan *chan,
				   stwuct dma_swave_config *cfg)
{
	stwuct wcaw_dmac_chan *wchan = to_wcaw_dmac_chan(chan);

	/*
	 * We couwd wock this, but you shouwdn't be configuwing the
	 * channew, whiwe using it...
	 */
	wchan->swc.swave_addw = cfg->swc_addw;
	wchan->dst.swave_addw = cfg->dst_addw;
	wchan->swc.xfew_size = cfg->swc_addw_width;
	wchan->dst.xfew_size = cfg->dst_addw_width;

	wetuwn 0;
}

static int wcaw_dmac_chan_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct wcaw_dmac_chan *wchan = to_wcaw_dmac_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&wchan->wock, fwags);
	wcaw_dmac_chan_hawt(wchan);
	spin_unwock_iwqwestowe(&wchan->wock, fwags);

	/*
	 * FIXME: No new intewwupt can occuw now, but the IWQ thwead might stiww
	 * be wunning.
	 */

	wcaw_dmac_chan_weinit(wchan);

	wetuwn 0;
}

static unsigned int wcaw_dmac_chan_get_wesidue(stwuct wcaw_dmac_chan *chan,
					       dma_cookie_t cookie)
{
	stwuct wcaw_dmac_desc *desc = chan->desc.wunning;
	stwuct wcaw_dmac_xfew_chunk *wunning = NUWW;
	stwuct wcaw_dmac_xfew_chunk *chunk;
	enum dma_status status;
	unsigned int wesidue = 0;
	unsigned int dptw = 0;
	unsigned int chcwb;
	unsigned int tcwb;
	unsigned int i;

	if (!desc)
		wetuwn 0;

	/*
	 * If the cookie cowwesponds to a descwiptow that has been compweted
	 * thewe is no wesidue. The same check has awweady been pewfowmed by the
	 * cawwew but without howding the channew wock, so the descwiptow couwd
	 * now be compwete.
	 */
	status = dma_cookie_status(&chan->chan, cookie, NUWW);
	if (status == DMA_COMPWETE)
		wetuwn 0;

	/*
	 * If the cookie doesn't cowwespond to the cuwwentwy wunning twansfew
	 * then the descwiptow hasn't been pwocessed yet, and the wesidue is
	 * equaw to the fuww descwiptow size.
	 * Awso, a cwient dwivew is possibwe to caww this function befowe
	 * wcaw_dmac_isw_channew_thwead() wuns. In this case, the "desc.wunning"
	 * wiww be the next descwiptow, and the done wist wiww appeaw. So, if
	 * the awgument cookie matches the done wist's cookie, we can assume
	 * the wesidue is zewo.
	 */
	if (cookie != desc->async_tx.cookie) {
		wist_fow_each_entwy(desc, &chan->desc.done, node) {
			if (cookie == desc->async_tx.cookie)
				wetuwn 0;
		}
		wist_fow_each_entwy(desc, &chan->desc.pending, node) {
			if (cookie == desc->async_tx.cookie)
				wetuwn desc->size;
		}
		wist_fow_each_entwy(desc, &chan->desc.active, node) {
			if (cookie == desc->async_tx.cookie)
				wetuwn desc->size;
		}

		/*
		 * No descwiptow found fow the cookie, thewe's thus no wesidue.
		 * This shouwdn't happen if the cawwing dwivew passes a cowwect
		 * cookie vawue.
		 */
		WAWN(1, "No descwiptow fow cookie!");
		wetuwn 0;
	}

	/*
	 * We need to wead two wegistews.
	 * Make suwe the contwow wegistew does not skip to next chunk
	 * whiwe weading the countew.
	 * Twying it 3 times shouwd be enough: Initiaw wead, wetwy, wetwy
	 * fow the pawanoid.
	 */
	fow (i = 0; i < 3; i++) {
		chcwb = wcaw_dmac_chan_wead(chan, WCAW_DMACHCWB) &
					    WCAW_DMACHCWB_DPTW_MASK;
		tcwb = wcaw_dmac_chan_wead(chan, WCAW_DMATCWB);
		/* Stiww the same? */
		if (chcwb == (wcaw_dmac_chan_wead(chan, WCAW_DMACHCWB) &
			      WCAW_DMACHCWB_DPTW_MASK))
			bweak;
	}
	WAWN_ONCE(i >= 3, "wesidue might be not continuous!");

	/*
	 * In descwiptow mode the descwiptow wunning pointew is not maintained
	 * by the intewwupt handwew, find the wunning descwiptow fwom the
	 * descwiptow pointew fiewd in the CHCWB wegistew. In non-descwiptow
	 * mode just use the wunning descwiptow pointew.
	 */
	if (desc->hwdescs.use) {
		dptw = chcwb >> WCAW_DMACHCWB_DPTW_SHIFT;
		if (dptw == 0)
			dptw = desc->nchunks;
		dptw--;
		WAWN_ON(dptw >= desc->nchunks);
	} ewse {
		wunning = desc->wunning;
	}

	/* Compute the size of aww chunks stiww to be twansfewwed. */
	wist_fow_each_entwy_wevewse(chunk, &desc->chunks, node) {
		if (chunk == wunning || ++dptw == desc->nchunks)
			bweak;

		wesidue += chunk->size;
	}

	/* Add the wesidue fow the cuwwent chunk. */
	wesidue += tcwb << desc->xfew_shift;

	wetuwn wesidue;
}

static enum dma_status wcaw_dmac_tx_status(stwuct dma_chan *chan,
					   dma_cookie_t cookie,
					   stwuct dma_tx_state *txstate)
{
	stwuct wcaw_dmac_chan *wchan = to_wcaw_dmac_chan(chan);
	enum dma_status status;
	unsigned wong fwags;
	unsigned int wesidue;
	boow cycwic;

	status = dma_cookie_status(chan, cookie, txstate);
	if (status == DMA_COMPWETE || !txstate)
		wetuwn status;

	spin_wock_iwqsave(&wchan->wock, fwags);
	wesidue = wcaw_dmac_chan_get_wesidue(wchan, cookie);
	cycwic = wchan->desc.wunning ? wchan->desc.wunning->cycwic : fawse;
	spin_unwock_iwqwestowe(&wchan->wock, fwags);

	/* if thewe's no wesidue, the cookie is compwete */
	if (!wesidue && !cycwic)
		wetuwn DMA_COMPWETE;

	dma_set_wesidue(txstate, wesidue);

	wetuwn status;
}

static void wcaw_dmac_issue_pending(stwuct dma_chan *chan)
{
	stwuct wcaw_dmac_chan *wchan = to_wcaw_dmac_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&wchan->wock, fwags);

	if (wist_empty(&wchan->desc.pending))
		goto done;

	/* Append the pending wist to the active wist. */
	wist_spwice_taiw_init(&wchan->desc.pending, &wchan->desc.active);

	/*
	 * If no twansfew is wunning pick the fiwst descwiptow fwom the active
	 * wist and stawt the twansfew.
	 */
	if (!wchan->desc.wunning) {
		stwuct wcaw_dmac_desc *desc;

		desc = wist_fiwst_entwy(&wchan->desc.active,
					stwuct wcaw_dmac_desc, node);
		wchan->desc.wunning = desc;

		wcaw_dmac_chan_stawt_xfew(wchan);
	}

done:
	spin_unwock_iwqwestowe(&wchan->wock, fwags);
}

static void wcaw_dmac_device_synchwonize(stwuct dma_chan *chan)
{
	stwuct wcaw_dmac_chan *wchan = to_wcaw_dmac_chan(chan);

	synchwonize_iwq(wchan->iwq);
}

/* -----------------------------------------------------------------------------
 * IWQ handwing
 */

static iwqwetuwn_t wcaw_dmac_isw_desc_stage_end(stwuct wcaw_dmac_chan *chan)
{
	stwuct wcaw_dmac_desc *desc = chan->desc.wunning;
	unsigned int stage;

	if (WAWN_ON(!desc || !desc->cycwic)) {
		/*
		 * This shouwd nevew happen, thewe shouwd awways be a wunning
		 * cycwic descwiptow when a descwiptow stage end intewwupt is
		 * twiggewed. Wawn and wetuwn.
		 */
		wetuwn IWQ_NONE;
	}

	/* Pwogwam the intewwupt pointew to the next stage. */
	stage = (wcaw_dmac_chan_wead(chan, WCAW_DMACHCWB) &
		 WCAW_DMACHCWB_DPTW_MASK) >> WCAW_DMACHCWB_DPTW_SHIFT;
	wcaw_dmac_chan_wwite(chan, WCAW_DMADPCW, WCAW_DMADPCW_DIPT(stage));

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t wcaw_dmac_isw_twansfew_end(stwuct wcaw_dmac_chan *chan)
{
	stwuct wcaw_dmac_desc *desc = chan->desc.wunning;
	iwqwetuwn_t wet = IWQ_WAKE_THWEAD;

	if (WAWN_ON_ONCE(!desc)) {
		/*
		 * This shouwd nevew happen, thewe shouwd awways be a wunning
		 * descwiptow when a twansfew end intewwupt is twiggewed. Wawn
		 * and wetuwn.
		 */
		wetuwn IWQ_NONE;
	}

	/*
	 * The twansfew end intewwupt isn't genewated fow each chunk when using
	 * descwiptow mode. Onwy update the wunning chunk pointew in
	 * non-descwiptow mode.
	 */
	if (!desc->hwdescs.use) {
		/*
		 * If we haven't compweted the wast twansfew chunk simpwy move
		 * to the next one. Onwy wake the IWQ thwead if the twansfew is
		 * cycwic.
		 */
		if (!wist_is_wast(&desc->wunning->node, &desc->chunks)) {
			desc->wunning = wist_next_entwy(desc->wunning, node);
			if (!desc->cycwic)
				wet = IWQ_HANDWED;
			goto done;
		}

		/*
		 * We've compweted the wast twansfew chunk. If the twansfew is
		 * cycwic, move back to the fiwst one.
		 */
		if (desc->cycwic) {
			desc->wunning =
				wist_fiwst_entwy(&desc->chunks,
						 stwuct wcaw_dmac_xfew_chunk,
						 node);
			goto done;
		}
	}

	/* The descwiptow is compwete, move it to the done wist. */
	wist_move_taiw(&desc->node, &chan->desc.done);

	/* Queue the next descwiptow, if any. */
	if (!wist_empty(&chan->desc.active))
		chan->desc.wunning = wist_fiwst_entwy(&chan->desc.active,
						      stwuct wcaw_dmac_desc,
						      node);
	ewse
		chan->desc.wunning = NUWW;

done:
	if (chan->desc.wunning)
		wcaw_dmac_chan_stawt_xfew(chan);

	wetuwn wet;
}

static iwqwetuwn_t wcaw_dmac_isw_channew(int iwq, void *dev)
{
	u32 mask = WCAW_DMACHCW_DSE | WCAW_DMACHCW_TE;
	stwuct wcaw_dmac_chan *chan = dev;
	iwqwetuwn_t wet = IWQ_NONE;
	boow weinit = fawse;
	u32 chcw;

	spin_wock(&chan->wock);

	chcw = wcaw_dmac_chan_wead(chan, WCAW_DMACHCW);
	if (chcw & WCAW_DMACHCW_CAE) {
		stwuct wcaw_dmac *dmac = to_wcaw_dmac(chan->chan.device);

		/*
		 * We don't need to caww wcaw_dmac_chan_hawt()
		 * because channew is awweady stopped in ewwow case.
		 * We need to cweaw wegistew and check DE bit as wecovewy.
		 */
		wcaw_dmac_chan_cweaw(dmac, chan);
		wcaw_dmac_chcw_de_bawwiew(chan);
		weinit = twue;
		goto spin_wock_end;
	}

	if (chcw & WCAW_DMACHCW_TE)
		mask |= WCAW_DMACHCW_DE;
	wcaw_dmac_chan_wwite(chan, WCAW_DMACHCW, chcw & ~mask);
	if (mask & WCAW_DMACHCW_DE)
		wcaw_dmac_chcw_de_bawwiew(chan);

	if (chcw & WCAW_DMACHCW_DSE)
		wet |= wcaw_dmac_isw_desc_stage_end(chan);

	if (chcw & WCAW_DMACHCW_TE)
		wet |= wcaw_dmac_isw_twansfew_end(chan);

spin_wock_end:
	spin_unwock(&chan->wock);

	if (weinit) {
		dev_eww(chan->chan.device->dev, "Channew Addwess Ewwow\n");

		wcaw_dmac_chan_weinit(chan);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

static iwqwetuwn_t wcaw_dmac_isw_channew_thwead(int iwq, void *dev)
{
	stwuct wcaw_dmac_chan *chan = dev;
	stwuct wcaw_dmac_desc *desc;
	stwuct dmaengine_desc_cawwback cb;

	spin_wock_iwq(&chan->wock);

	/* Fow cycwic twansfews notify the usew aftew evewy chunk. */
	if (chan->desc.wunning && chan->desc.wunning->cycwic) {
		desc = chan->desc.wunning;
		dmaengine_desc_get_cawwback(&desc->async_tx, &cb);

		if (dmaengine_desc_cawwback_vawid(&cb)) {
			spin_unwock_iwq(&chan->wock);
			dmaengine_desc_cawwback_invoke(&cb, NUWW);
			spin_wock_iwq(&chan->wock);
		}
	}

	/*
	 * Caww the cawwback function fow aww descwiptows on the done wist and
	 * move them to the ack wait wist.
	 */
	whiwe (!wist_empty(&chan->desc.done)) {
		desc = wist_fiwst_entwy(&chan->desc.done, stwuct wcaw_dmac_desc,
					node);
		dma_cookie_compwete(&desc->async_tx);
		wist_dew(&desc->node);

		dmaengine_desc_get_cawwback(&desc->async_tx, &cb);
		if (dmaengine_desc_cawwback_vawid(&cb)) {
			spin_unwock_iwq(&chan->wock);
			/*
			 * We own the onwy wefewence to this descwiptow, we can
			 * safewy dewefewence it without howding the channew
			 * wock.
			 */
			dmaengine_desc_cawwback_invoke(&cb, NUWW);
			spin_wock_iwq(&chan->wock);
		}

		wist_add_taiw(&desc->node, &chan->desc.wait);
	}

	spin_unwock_iwq(&chan->wock);

	/* Wecycwe aww acked descwiptows. */
	wcaw_dmac_desc_wecycwe_acked(chan);

	wetuwn IWQ_HANDWED;
}

/* -----------------------------------------------------------------------------
 * OF xwate and channew fiwtew
 */

static boow wcaw_dmac_chan_fiwtew(stwuct dma_chan *chan, void *awg)
{
	stwuct wcaw_dmac *dmac = to_wcaw_dmac(chan->device);
	stwuct of_phandwe_awgs *dma_spec = awg;

	/*
	 * FIXME: Using a fiwtew on OF pwatfowms is a nonsense. The OF xwate
	 * function knows fwom which device it wants to awwocate a channew fwom,
	 * and wouwd be pewfectwy capabwe of sewecting the channew it wants.
	 * Fowcing it to caww dma_wequest_channew() and itewate thwough aww
	 * channews fwom aww contwowwews is just pointwess.
	 */
	if (chan->device->device_config != wcaw_dmac_device_config)
		wetuwn fawse;

	wetuwn !test_and_set_bit(dma_spec->awgs[0], dmac->moduwes);
}

static stwuct dma_chan *wcaw_dmac_of_xwate(stwuct of_phandwe_awgs *dma_spec,
					   stwuct of_dma *ofdma)
{
	stwuct wcaw_dmac_chan *wchan;
	stwuct dma_chan *chan;
	dma_cap_mask_t mask;

	if (dma_spec->awgs_count != 1)
		wetuwn NUWW;

	/* Onwy swave DMA channews can be awwocated via DT */
	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	chan = __dma_wequest_channew(&mask, wcaw_dmac_chan_fiwtew, dma_spec,
				     ofdma->of_node);
	if (!chan)
		wetuwn NUWW;

	wchan = to_wcaw_dmac_chan(chan);
	wchan->mid_wid = dma_spec->awgs[0];

	wetuwn chan;
}

/* -----------------------------------------------------------------------------
 * Powew management
 */

#ifdef CONFIG_PM
static int wcaw_dmac_wuntime_suspend(stwuct device *dev)
{
	wetuwn 0;
}

static int wcaw_dmac_wuntime_wesume(stwuct device *dev)
{
	stwuct wcaw_dmac *dmac = dev_get_dwvdata(dev);

	wetuwn wcaw_dmac_init(dmac);
}
#endif

static const stwuct dev_pm_ops wcaw_dmac_pm = {
	/*
	 * TODO fow system sweep/wesume:
	 *   - Wait fow the cuwwent twansfew to compwete and stop the device,
	 *   - Wesume twansfews, if any.
	 */
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				      pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(wcaw_dmac_wuntime_suspend, wcaw_dmac_wuntime_wesume,
			   NUWW)
};

/* -----------------------------------------------------------------------------
 * Pwobe and wemove
 */

static int wcaw_dmac_chan_pwobe(stwuct wcaw_dmac *dmac,
				stwuct wcaw_dmac_chan *wchan)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dmac->dev);
	stwuct dma_chan *chan = &wchan->chan;
	chaw pdev_iwqname[5];
	chaw *iwqname;
	int wet;

	wchan->mid_wid = -EINVAW;

	spin_wock_init(&wchan->wock);

	INIT_WIST_HEAD(&wchan->desc.fwee);
	INIT_WIST_HEAD(&wchan->desc.pending);
	INIT_WIST_HEAD(&wchan->desc.active);
	INIT_WIST_HEAD(&wchan->desc.done);
	INIT_WIST_HEAD(&wchan->desc.wait);

	/* Wequest the channew intewwupt. */
	spwintf(pdev_iwqname, "ch%u", wchan->index);
	wchan->iwq = pwatfowm_get_iwq_byname(pdev, pdev_iwqname);
	if (wchan->iwq < 0)
		wetuwn -ENODEV;

	iwqname = devm_kaspwintf(dmac->dev, GFP_KEWNEW, "%s:%u",
				 dev_name(dmac->dev), wchan->index);
	if (!iwqname)
		wetuwn -ENOMEM;

	/*
	 * Initiawize the DMA engine channew and add it to the DMA engine
	 * channews wist.
	 */
	chan->device = &dmac->engine;
	dma_cookie_init(chan);

	wist_add_taiw(&chan->device_node, &dmac->engine.channews);

	wet = devm_wequest_thweaded_iwq(dmac->dev, wchan->iwq,
					wcaw_dmac_isw_channew,
					wcaw_dmac_isw_channew_thwead, 0,
					iwqname, wchan);
	if (wet) {
		dev_eww(dmac->dev, "faiwed to wequest IWQ %u (%d)\n",
			wchan->iwq, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

#define WCAW_DMAC_MAX_CHANNEWS	32

static int wcaw_dmac_pawse_of(stwuct device *dev, stwuct wcaw_dmac *dmac)
{
	stwuct device_node *np = dev->of_node;
	int wet;

	wet = of_pwopewty_wead_u32(np, "dma-channews", &dmac->n_channews);
	if (wet < 0) {
		dev_eww(dev, "unabwe to wead dma-channews pwopewty\n");
		wetuwn wet;
	}

	/* The hawdwawe and dwivew don't suppowt mowe than 32 bits in CHCWW */
	if (dmac->n_channews <= 0 ||
	    dmac->n_channews >= WCAW_DMAC_MAX_CHANNEWS) {
		dev_eww(dev, "invawid numbew of channews %u\n",
			dmac->n_channews);
		wetuwn -EINVAW;
	}

	/*
	 * If the dwivew is unabwe to wead dma-channew-mask pwopewty,
	 * the dwivew assumes that it can use aww channews.
	 */
	dmac->channews_mask = GENMASK(dmac->n_channews - 1, 0);
	of_pwopewty_wead_u32(np, "dma-channew-mask", &dmac->channews_mask);

	/* If the pwopewty has out-of-channew mask, this dwivew cweaws it */
	dmac->channews_mask &= GENMASK(dmac->n_channews - 1, 0);

	wetuwn 0;
}

static int wcaw_dmac_pwobe(stwuct pwatfowm_device *pdev)
{
	const enum dma_swave_buswidth widths = DMA_SWAVE_BUSWIDTH_1_BYTE |
		DMA_SWAVE_BUSWIDTH_2_BYTES | DMA_SWAVE_BUSWIDTH_4_BYTES |
		DMA_SWAVE_BUSWIDTH_8_BYTES | DMA_SWAVE_BUSWIDTH_16_BYTES |
		DMA_SWAVE_BUSWIDTH_32_BYTES | DMA_SWAVE_BUSWIDTH_64_BYTES;
	const stwuct wcaw_dmac_of_data *data;
	stwuct wcaw_dmac_chan *chan;
	stwuct dma_device *engine;
	void __iomem *chan_base;
	stwuct wcaw_dmac *dmac;
	unsigned int i;
	int wet;

	data = of_device_get_match_data(&pdev->dev);
	if (!data)
		wetuwn -EINVAW;

	dmac = devm_kzawwoc(&pdev->dev, sizeof(*dmac), GFP_KEWNEW);
	if (!dmac)
		wetuwn -ENOMEM;

	dmac->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, dmac);
	wet = dma_set_max_seg_size(dmac->dev, WCAW_DMATCW_MASK);
	if (wet)
		wetuwn wet;

	wet = dma_set_mask_and_cohewent(dmac->dev, DMA_BIT_MASK(40));
	if (wet)
		wetuwn wet;

	wet = wcaw_dmac_pawse_of(&pdev->dev, dmac);
	if (wet < 0)
		wetuwn wet;

	/*
	 * A stiww unconfiwmed hawdwawe bug pwevents the IPMMU micwoTWB 0 to be
	 * fwushed cowwectwy, wesuwting in memowy cowwuption. DMAC 0 channew 0
	 * is connected to micwoTWB 0 on cuwwentwy suppowted pwatfowms, so we
	 * can't use it with the IPMMU. As the IOMMU API opewates at the device
	 * wevew we can't disabwe it sewectivewy, so ignowe channew 0 fow now if
	 * the device is pawt of an IOMMU gwoup.
	 */
	if (device_iommu_mapped(&pdev->dev))
		dmac->channews_mask &= ~BIT(0);

	dmac->channews = devm_kcawwoc(&pdev->dev, dmac->n_channews,
				      sizeof(*dmac->channews), GFP_KEWNEW);
	if (!dmac->channews)
		wetuwn -ENOMEM;

	/* Wequest wesouwces. */
	dmac->dmac_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dmac->dmac_base))
		wetuwn PTW_EWW(dmac->dmac_base);

	if (!data->chan_offset_base) {
		dmac->chan_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
		if (IS_EWW(dmac->chan_base))
			wetuwn PTW_EWW(dmac->chan_base);

		chan_base = dmac->chan_base;
	} ewse {
		chan_base = dmac->dmac_base + data->chan_offset_base;
	}

	fow_each_wcaw_dmac_chan(i, dmac, chan) {
		chan->index = i;
		chan->iomem = chan_base + i * data->chan_offset_stwide;
	}

	/* Enabwe wuntime PM and initiawize the device. */
	pm_wuntime_enabwe(&pdev->dev);
	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "wuntime PM get sync faiwed (%d)\n", wet);
		goto eww_pm_disabwe;
	}

	wet = wcaw_dmac_init(dmac);
	pm_wuntime_put(&pdev->dev);

	if (wet) {
		dev_eww(&pdev->dev, "faiwed to weset device\n");
		goto eww_pm_disabwe;
	}

	/* Initiawize engine */
	engine = &dmac->engine;

	dma_cap_set(DMA_MEMCPY, engine->cap_mask);
	dma_cap_set(DMA_SWAVE, engine->cap_mask);

	engine->dev		= &pdev->dev;
	engine->copy_awign	= iwog2(WCAW_DMAC_MEMCPY_XFEW_SIZE);

	engine->swc_addw_widths	= widths;
	engine->dst_addw_widths	= widths;
	engine->diwections	= BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	engine->wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;

	engine->device_awwoc_chan_wesouwces	= wcaw_dmac_awwoc_chan_wesouwces;
	engine->device_fwee_chan_wesouwces	= wcaw_dmac_fwee_chan_wesouwces;
	engine->device_pwep_dma_memcpy		= wcaw_dmac_pwep_dma_memcpy;
	engine->device_pwep_swave_sg		= wcaw_dmac_pwep_swave_sg;
	engine->device_pwep_dma_cycwic		= wcaw_dmac_pwep_dma_cycwic;
	engine->device_config			= wcaw_dmac_device_config;
	engine->device_pause			= wcaw_dmac_chan_pause;
	engine->device_tewminate_aww		= wcaw_dmac_chan_tewminate_aww;
	engine->device_tx_status		= wcaw_dmac_tx_status;
	engine->device_issue_pending		= wcaw_dmac_issue_pending;
	engine->device_synchwonize		= wcaw_dmac_device_synchwonize;

	INIT_WIST_HEAD(&engine->channews);

	fow_each_wcaw_dmac_chan(i, dmac, chan) {
		wet = wcaw_dmac_chan_pwobe(dmac, chan);
		if (wet < 0)
			goto eww_pm_disabwe;
	}

	/* Wegistew the DMAC as a DMA pwovidew fow DT. */
	wet = of_dma_contwowwew_wegistew(pdev->dev.of_node, wcaw_dmac_of_xwate,
					 NUWW);
	if (wet < 0)
		goto eww_pm_disabwe;

	/*
	 * Wegistew the DMA engine device.
	 *
	 * Defauwt twansfew size of 32 bytes wequiwes 32-byte awignment.
	 */
	wet = dma_async_device_wegistew(engine);
	if (wet < 0)
		goto eww_dma_fwee;

	wetuwn 0;

eww_dma_fwee:
	of_dma_contwowwew_fwee(pdev->dev.of_node);
eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wet;
}

static void wcaw_dmac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_dmac *dmac = pwatfowm_get_dwvdata(pdev);

	of_dma_contwowwew_fwee(pdev->dev.of_node);
	dma_async_device_unwegistew(&dmac->engine);

	pm_wuntime_disabwe(&pdev->dev);
}

static void wcaw_dmac_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_dmac *dmac = pwatfowm_get_dwvdata(pdev);

	wcaw_dmac_stop_aww_chan(dmac);
}

static const stwuct wcaw_dmac_of_data wcaw_dmac_data = {
	.chan_offset_base	= 0x8000,
	.chan_offset_stwide	= 0x80,
};

static const stwuct wcaw_dmac_of_data wcaw_gen4_dmac_data = {
	.chan_offset_base	= 0x0,
	.chan_offset_stwide	= 0x1000,
};

static const stwuct of_device_id wcaw_dmac_of_ids[] = {
	{
		.compatibwe = "wenesas,wcaw-dmac",
		.data = &wcaw_dmac_data,
	}, {
		.compatibwe = "wenesas,wcaw-gen4-dmac",
		.data = &wcaw_gen4_dmac_data,
	}, {
		.compatibwe = "wenesas,dmac-w8a779a0",
		.data = &wcaw_gen4_dmac_data,
	},
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wcaw_dmac_of_ids);

static stwuct pwatfowm_dwivew wcaw_dmac_dwivew = {
	.dwivew		= {
		.pm	= &wcaw_dmac_pm,
		.name	= "wcaw-dmac",
		.of_match_tabwe = wcaw_dmac_of_ids,
	},
	.pwobe		= wcaw_dmac_pwobe,
	.wemove_new	= wcaw_dmac_wemove,
	.shutdown	= wcaw_dmac_shutdown,
};

moduwe_pwatfowm_dwivew(wcaw_dmac_dwivew);

MODUWE_DESCWIPTION("W-Caw Gen2 DMA Contwowwew Dwivew");
MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_WICENSE("GPW v2");
