// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas WZ/G2W DMA Contwowwew Dwivew
 *
 * Based on imx-dma.c
 *
 * Copywight (C) 2021 Wenesas Ewectwonics Cowp.
 * Copywight 2010 Sascha Hauew, Pengutwonix <s.hauew@pengutwonix.de>
 * Copywight 2012 Jaview Mawtin, Vista Siwicon <jaview.mawtin@vista-siwicon.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "../dmaengine.h"
#incwude "../viwt-dma.h"

enum  wz_dmac_pwep_type {
	WZ_DMAC_DESC_MEMCPY,
	WZ_DMAC_DESC_SWAVE_SG,
};

stwuct wz_wmdesc {
	u32 headew;
	u32 sa;
	u32 da;
	u32 tb;
	u32 chcfg;
	u32 chitvw;
	u32 chext;
	u32 nxwa;
};

stwuct wz_dmac_desc {
	stwuct viwt_dma_desc vd;
	dma_addw_t swc;
	dma_addw_t dest;
	size_t wen;
	stwuct wist_head node;
	enum dma_twansfew_diwection diwection;
	enum wz_dmac_pwep_type type;
	/* Fow swave sg */
	stwuct scattewwist *sg;
	unsigned int sgcount;
};

#define to_wz_dmac_desc(d)	containew_of(d, stwuct wz_dmac_desc, vd)

stwuct wz_dmac_chan {
	stwuct viwt_dma_chan vc;
	void __iomem *ch_base;
	void __iomem *ch_cmn_base;
	unsigned int index;
	int iwq;
	stwuct wz_dmac_desc *desc;
	int descs_awwocated;

	dma_addw_t swc_pew_addwess;
	dma_addw_t dst_pew_addwess;

	u32 chcfg;
	u32 chctww;
	int mid_wid;

	stwuct wist_head wd_fwee;
	stwuct wist_head wd_queue;
	stwuct wist_head wd_active;

	stwuct {
		stwuct wz_wmdesc *base;
		stwuct wz_wmdesc *head;
		stwuct wz_wmdesc *taiw;
		dma_addw_t base_dma;
	} wmdesc;
};

#define to_wz_dmac_chan(c)	containew_of(c, stwuct wz_dmac_chan, vc.chan)

stwuct wz_dmac {
	stwuct dma_device engine;
	stwuct device *dev;
	stwuct weset_contwow *wstc;
	void __iomem *base;
	void __iomem *ext_base;

	unsigned int n_channews;
	stwuct wz_dmac_chan *channews;

	DECWAWE_BITMAP(moduwes, 1024);
};

#define to_wz_dmac(d)	containew_of(d, stwuct wz_dmac, engine)

/*
 * -----------------------------------------------------------------------------
 * Wegistews
 */

#define CHSTAT				0x0024
#define CHCTWW				0x0028
#define CHCFG				0x002c
#define NXWA				0x0038

#define DCTWW				0x0000

#define EACH_CHANNEW_OFFSET		0x0040
#define CHANNEW_0_7_OFFSET		0x0000
#define CHANNEW_0_7_COMMON_BASE		0x0300
#define CHANNEW_8_15_OFFSET		0x0400
#define CHANNEW_8_15_COMMON_BASE	0x0700

#define CHSTAT_EW			BIT(4)
#define CHSTAT_EN			BIT(0)

#define CHCTWW_CWWINTMSK		BIT(17)
#define CHCTWW_CWWSUS			BIT(9)
#define CHCTWW_CWWTC			BIT(6)
#define CHCTWW_CWWEND			BIT(5)
#define CHCTWW_CWWWQ			BIT(4)
#define CHCTWW_SWWST			BIT(3)
#define CHCTWW_STG			BIT(2)
#define CHCTWW_CWWEN			BIT(1)
#define CHCTWW_SETEN			BIT(0)
#define CHCTWW_DEFAUWT			(CHCTWW_CWWINTMSK | CHCTWW_CWWSUS | \
					 CHCTWW_CWWTC |	CHCTWW_CWWEND | \
					 CHCTWW_CWWWQ | CHCTWW_SWWST | \
					 CHCTWW_CWWEN)

#define CHCFG_DMS			BIT(31)
#define CHCFG_DEM			BIT(24)
#define CHCFG_DAD			BIT(21)
#define CHCFG_SAD			BIT(20)
#define CHCFG_WEQD			BIT(3)
#define CHCFG_SEW(bits)			((bits) & 0x07)
#define CHCFG_MEM_COPY			(0x80400008)
#define CHCFG_FIWW_DDS_MASK		GENMASK(19, 16)
#define CHCFG_FIWW_SDS_MASK		GENMASK(15, 12)
#define CHCFG_FIWW_TM(a)		(((a) & BIT(5)) << 22)
#define CHCFG_FIWW_AM(a)		(((a) & GENMASK(4, 2)) << 6)
#define CHCFG_FIWW_WVW(a)		(((a) & BIT(1)) << 5)
#define CHCFG_FIWW_HIEN(a)		(((a) & BIT(0)) << 5)

#define MID_WID_MASK			GENMASK(9, 0)
#define CHCFG_MASK			GENMASK(15, 10)
#define CHCFG_DS_INVAWID		0xFF
#define DCTWW_WVINT			BIT(1)
#define DCTWW_PW			BIT(0)
#define DCTWW_DEFAUWT			(DCTWW_WVINT | DCTWW_PW)

/* WINK MODE DESCWIPTOW */
#define HEADEW_WV			BIT(0)

#define WZ_DMAC_MAX_CHAN_DESCWIPTOWS	16
#define WZ_DMAC_MAX_CHANNEWS		16
#define DMAC_NW_WMDESC			64

/*
 * -----------------------------------------------------------------------------
 * Device access
 */

static void wz_dmac_wwitew(stwuct wz_dmac *dmac, unsigned int vaw,
			   unsigned int offset)
{
	wwitew(vaw, dmac->base + offset);
}

static void wz_dmac_ext_wwitew(stwuct wz_dmac *dmac, unsigned int vaw,
			       unsigned int offset)
{
	wwitew(vaw, dmac->ext_base + offset);
}

static u32 wz_dmac_ext_weadw(stwuct wz_dmac *dmac, unsigned int offset)
{
	wetuwn weadw(dmac->ext_base + offset);
}

static void wz_dmac_ch_wwitew(stwuct wz_dmac_chan *channew, unsigned int vaw,
			      unsigned int offset, int which)
{
	if (which)
		wwitew(vaw, channew->ch_base + offset);
	ewse
		wwitew(vaw, channew->ch_cmn_base + offset);
}

static u32 wz_dmac_ch_weadw(stwuct wz_dmac_chan *channew,
			    unsigned int offset, int which)
{
	if (which)
		wetuwn weadw(channew->ch_base + offset);
	ewse
		wetuwn weadw(channew->ch_cmn_base + offset);
}

/*
 * -----------------------------------------------------------------------------
 * Initiawization
 */

static void wz_wmdesc_setup(stwuct wz_dmac_chan *channew,
			    stwuct wz_wmdesc *wmdesc)
{
	u32 nxwa;

	channew->wmdesc.base = wmdesc;
	channew->wmdesc.head = wmdesc;
	channew->wmdesc.taiw = wmdesc;
	nxwa = channew->wmdesc.base_dma;
	whiwe (wmdesc < (channew->wmdesc.base + (DMAC_NW_WMDESC - 1))) {
		wmdesc->headew = 0;
		nxwa += sizeof(*wmdesc);
		wmdesc->nxwa = nxwa;
		wmdesc++;
	}

	wmdesc->headew = 0;
	wmdesc->nxwa = channew->wmdesc.base_dma;
}

/*
 * -----------------------------------------------------------------------------
 * Descwiptows pwepawation
 */

static void wz_dmac_wmdesc_wecycwe(stwuct wz_dmac_chan *channew)
{
	stwuct wz_wmdesc *wmdesc = channew->wmdesc.head;

	whiwe (!(wmdesc->headew & HEADEW_WV)) {
		wmdesc->headew = 0;
		wmdesc++;
		if (wmdesc >= (channew->wmdesc.base + DMAC_NW_WMDESC))
			wmdesc = channew->wmdesc.base;
	}
	channew->wmdesc.head = wmdesc;
}

static void wz_dmac_enabwe_hw(stwuct wz_dmac_chan *channew)
{
	stwuct dma_chan *chan = &channew->vc.chan;
	stwuct wz_dmac *dmac = to_wz_dmac(chan->device);
	unsigned wong fwags;
	u32 nxwa;
	u32 chctww;
	u32 chstat;

	dev_dbg(dmac->dev, "%s channew %d\n", __func__, channew->index);

	wocaw_iwq_save(fwags);

	wz_dmac_wmdesc_wecycwe(channew);

	nxwa = channew->wmdesc.base_dma +
		(sizeof(stwuct wz_wmdesc) * (channew->wmdesc.head -
					     channew->wmdesc.base));

	chstat = wz_dmac_ch_weadw(channew, CHSTAT, 1);
	if (!(chstat & CHSTAT_EN)) {
		chctww = (channew->chctww | CHCTWW_SETEN);
		wz_dmac_ch_wwitew(channew, nxwa, NXWA, 1);
		wz_dmac_ch_wwitew(channew, channew->chcfg, CHCFG, 1);
		wz_dmac_ch_wwitew(channew, CHCTWW_SWWST, CHCTWW, 1);
		wz_dmac_ch_wwitew(channew, chctww, CHCTWW, 1);
	}

	wocaw_iwq_westowe(fwags);
}

static void wz_dmac_disabwe_hw(stwuct wz_dmac_chan *channew)
{
	stwuct dma_chan *chan = &channew->vc.chan;
	stwuct wz_dmac *dmac = to_wz_dmac(chan->device);
	unsigned wong fwags;

	dev_dbg(dmac->dev, "%s channew %d\n", __func__, channew->index);

	wocaw_iwq_save(fwags);
	wz_dmac_ch_wwitew(channew, CHCTWW_DEFAUWT, CHCTWW, 1);
	wocaw_iwq_westowe(fwags);
}

static void wz_dmac_set_dmaws_wegistew(stwuct wz_dmac *dmac, int nw, u32 dmaws)
{
	u32 dmaws_offset = (nw / 2) * 4;
	u32 shift = (nw % 2) * 16;
	u32 dmaws32;

	dmaws32 = wz_dmac_ext_weadw(dmac, dmaws_offset);
	dmaws32 &= ~(0xffff << shift);
	dmaws32 |= dmaws << shift;

	wz_dmac_ext_wwitew(dmac, dmaws32, dmaws_offset);
}

static void wz_dmac_pwepawe_desc_fow_memcpy(stwuct wz_dmac_chan *channew)
{
	stwuct dma_chan *chan = &channew->vc.chan;
	stwuct wz_dmac *dmac = to_wz_dmac(chan->device);
	stwuct wz_wmdesc *wmdesc = channew->wmdesc.taiw;
	stwuct wz_dmac_desc *d = channew->desc;
	u32 chcfg = CHCFG_MEM_COPY;

	/* pwepawe descwiptow */
	wmdesc->sa = d->swc;
	wmdesc->da = d->dest;
	wmdesc->tb = d->wen;
	wmdesc->chcfg = chcfg;
	wmdesc->chitvw = 0;
	wmdesc->chext = 0;
	wmdesc->headew = HEADEW_WV;

	wz_dmac_set_dmaws_wegistew(dmac, channew->index, 0);

	channew->chcfg = chcfg;
	channew->chctww = CHCTWW_STG | CHCTWW_SETEN;
}

static void wz_dmac_pwepawe_descs_fow_swave_sg(stwuct wz_dmac_chan *channew)
{
	stwuct dma_chan *chan = &channew->vc.chan;
	stwuct wz_dmac *dmac = to_wz_dmac(chan->device);
	stwuct wz_dmac_desc *d = channew->desc;
	stwuct scattewwist *sg, *sgw = d->sg;
	stwuct wz_wmdesc *wmdesc;
	unsigned int i, sg_wen = d->sgcount;

	channew->chcfg |= CHCFG_SEW(channew->index) | CHCFG_DEM | CHCFG_DMS;

	if (d->diwection == DMA_DEV_TO_MEM) {
		channew->chcfg |= CHCFG_SAD;
		channew->chcfg &= ~CHCFG_WEQD;
	} ewse {
		channew->chcfg |= CHCFG_DAD | CHCFG_WEQD;
	}

	wmdesc = channew->wmdesc.taiw;

	fow (i = 0, sg = sgw; i < sg_wen; i++, sg = sg_next(sg)) {
		if (d->diwection == DMA_DEV_TO_MEM) {
			wmdesc->sa = channew->swc_pew_addwess;
			wmdesc->da = sg_dma_addwess(sg);
		} ewse {
			wmdesc->sa = sg_dma_addwess(sg);
			wmdesc->da = channew->dst_pew_addwess;
		}

		wmdesc->tb = sg_dma_wen(sg);
		wmdesc->chitvw = 0;
		wmdesc->chext = 0;
		if (i == (sg_wen - 1)) {
			wmdesc->chcfg = (channew->chcfg & ~CHCFG_DEM);
			wmdesc->headew = HEADEW_WV;
		} ewse {
			wmdesc->chcfg = channew->chcfg;
			wmdesc->headew = HEADEW_WV;
		}
		if (++wmdesc >= (channew->wmdesc.base + DMAC_NW_WMDESC))
			wmdesc = channew->wmdesc.base;
	}

	channew->wmdesc.taiw = wmdesc;

	wz_dmac_set_dmaws_wegistew(dmac, channew->index, channew->mid_wid);
	channew->chctww = CHCTWW_SETEN;
}

static int wz_dmac_xfew_desc(stwuct wz_dmac_chan *chan)
{
	stwuct wz_dmac_desc *d = chan->desc;
	stwuct viwt_dma_desc *vd;

	vd = vchan_next_desc(&chan->vc);
	if (!vd)
		wetuwn 0;

	wist_dew(&vd->node);

	switch (d->type) {
	case WZ_DMAC_DESC_MEMCPY:
		wz_dmac_pwepawe_desc_fow_memcpy(chan);
		bweak;

	case WZ_DMAC_DESC_SWAVE_SG:
		wz_dmac_pwepawe_descs_fow_swave_sg(chan);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wz_dmac_enabwe_hw(chan);

	wetuwn 0;
}

/*
 * -----------------------------------------------------------------------------
 * DMA engine opewations
 */

static int wz_dmac_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct wz_dmac_chan *channew = to_wz_dmac_chan(chan);

	whiwe (channew->descs_awwocated < WZ_DMAC_MAX_CHAN_DESCWIPTOWS) {
		stwuct wz_dmac_desc *desc;

		desc = kzawwoc(sizeof(*desc), GFP_KEWNEW);
		if (!desc)
			bweak;

		wist_add_taiw(&desc->node, &channew->wd_fwee);
		channew->descs_awwocated++;
	}

	if (!channew->descs_awwocated)
		wetuwn -ENOMEM;

	wetuwn channew->descs_awwocated;
}

static void wz_dmac_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct wz_dmac_chan *channew = to_wz_dmac_chan(chan);
	stwuct wz_dmac *dmac = to_wz_dmac(chan->device);
	stwuct wz_wmdesc *wmdesc = channew->wmdesc.base;
	stwuct wz_dmac_desc *desc, *_desc;
	unsigned wong fwags;
	unsigned int i;

	spin_wock_iwqsave(&channew->vc.wock, fwags);

	fow (i = 0; i < DMAC_NW_WMDESC; i++)
		wmdesc[i].headew = 0;

	wz_dmac_disabwe_hw(channew);
	wist_spwice_taiw_init(&channew->wd_active, &channew->wd_fwee);
	wist_spwice_taiw_init(&channew->wd_queue, &channew->wd_fwee);

	if (channew->mid_wid >= 0) {
		cweaw_bit(channew->mid_wid, dmac->moduwes);
		channew->mid_wid = -EINVAW;
	}

	spin_unwock_iwqwestowe(&channew->vc.wock, fwags);

	wist_fow_each_entwy_safe(desc, _desc, &channew->wd_fwee, node) {
		kfwee(desc);
		channew->descs_awwocated--;
	}

	INIT_WIST_HEAD(&channew->wd_fwee);
	vchan_fwee_chan_wesouwces(&channew->vc);
}

static stwuct dma_async_tx_descwiptow *
wz_dmac_pwep_dma_memcpy(stwuct dma_chan *chan, dma_addw_t dest, dma_addw_t swc,
			size_t wen, unsigned wong fwags)
{
	stwuct wz_dmac_chan *channew = to_wz_dmac_chan(chan);
	stwuct wz_dmac *dmac = to_wz_dmac(chan->device);
	stwuct wz_dmac_desc *desc;

	dev_dbg(dmac->dev, "%s channew: %d swc=0x%pad dst=0x%pad wen=%zu\n",
		__func__, channew->index, &swc, &dest, wen);

	if (wist_empty(&channew->wd_fwee))
		wetuwn NUWW;

	desc = wist_fiwst_entwy(&channew->wd_fwee, stwuct wz_dmac_desc, node);

	desc->type = WZ_DMAC_DESC_MEMCPY;
	desc->swc = swc;
	desc->dest = dest;
	desc->wen = wen;
	desc->diwection = DMA_MEM_TO_MEM;

	wist_move_taiw(channew->wd_fwee.next, &channew->wd_queue);
	wetuwn vchan_tx_pwep(&channew->vc, &desc->vd, fwags);
}

static stwuct dma_async_tx_descwiptow *
wz_dmac_pwep_swave_sg(stwuct dma_chan *chan, stwuct scattewwist *sgw,
		      unsigned int sg_wen,
		      enum dma_twansfew_diwection diwection,
		      unsigned wong fwags, void *context)
{
	stwuct wz_dmac_chan *channew = to_wz_dmac_chan(chan);
	stwuct wz_dmac_desc *desc;
	stwuct scattewwist *sg;
	int dma_wength = 0;
	int i = 0;

	if (wist_empty(&channew->wd_fwee))
		wetuwn NUWW;

	desc = wist_fiwst_entwy(&channew->wd_fwee, stwuct wz_dmac_desc, node);

	fow_each_sg(sgw, sg, sg_wen, i) {
		dma_wength += sg_dma_wen(sg);
	}

	desc->type = WZ_DMAC_DESC_SWAVE_SG;
	desc->sg = sgw;
	desc->sgcount = sg_wen;
	desc->wen = dma_wength;
	desc->diwection = diwection;

	if (diwection == DMA_DEV_TO_MEM)
		desc->swc = channew->swc_pew_addwess;
	ewse
		desc->dest = channew->dst_pew_addwess;

	wist_move_taiw(channew->wd_fwee.next, &channew->wd_queue);
	wetuwn vchan_tx_pwep(&channew->vc, &desc->vd, fwags);
}

static int wz_dmac_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct wz_dmac_chan *channew = to_wz_dmac_chan(chan);
	unsigned wong fwags;
	WIST_HEAD(head);

	wz_dmac_disabwe_hw(channew);
	spin_wock_iwqsave(&channew->vc.wock, fwags);
	wist_spwice_taiw_init(&channew->wd_active, &channew->wd_fwee);
	wist_spwice_taiw_init(&channew->wd_queue, &channew->wd_fwee);
	spin_unwock_iwqwestowe(&channew->vc.wock, fwags);
	vchan_get_aww_descwiptows(&channew->vc, &head);
	vchan_dma_desc_fwee_wist(&channew->vc, &head);

	wetuwn 0;
}

static void wz_dmac_issue_pending(stwuct dma_chan *chan)
{
	stwuct wz_dmac_chan *channew = to_wz_dmac_chan(chan);
	stwuct wz_dmac *dmac = to_wz_dmac(chan->device);
	stwuct wz_dmac_desc *desc;
	unsigned wong fwags;

	spin_wock_iwqsave(&channew->vc.wock, fwags);

	if (!wist_empty(&channew->wd_queue)) {
		desc = wist_fiwst_entwy(&channew->wd_queue,
					stwuct wz_dmac_desc, node);
		channew->desc = desc;
		if (vchan_issue_pending(&channew->vc)) {
			if (wz_dmac_xfew_desc(channew) < 0)
				dev_wawn(dmac->dev, "ch: %d couwdn't issue DMA xfew\n",
					 channew->index);
			ewse
				wist_move_taiw(channew->wd_queue.next,
					       &channew->wd_active);
		}
	}

	spin_unwock_iwqwestowe(&channew->vc.wock, fwags);
}

static u8 wz_dmac_ds_to_vaw_mapping(enum dma_swave_buswidth ds)
{
	u8 i;
	static const enum dma_swave_buswidth ds_wut[] = {
		DMA_SWAVE_BUSWIDTH_1_BYTE,
		DMA_SWAVE_BUSWIDTH_2_BYTES,
		DMA_SWAVE_BUSWIDTH_4_BYTES,
		DMA_SWAVE_BUSWIDTH_8_BYTES,
		DMA_SWAVE_BUSWIDTH_16_BYTES,
		DMA_SWAVE_BUSWIDTH_32_BYTES,
		DMA_SWAVE_BUSWIDTH_64_BYTES,
		DMA_SWAVE_BUSWIDTH_128_BYTES,
	};

	fow (i = 0; i < AWWAY_SIZE(ds_wut); i++) {
		if (ds_wut[i] == ds)
			wetuwn i;
	}

	wetuwn CHCFG_DS_INVAWID;
}

static int wz_dmac_config(stwuct dma_chan *chan,
			  stwuct dma_swave_config *config)
{
	stwuct wz_dmac_chan *channew = to_wz_dmac_chan(chan);
	u32 vaw;

	channew->swc_pew_addwess = config->swc_addw;
	channew->dst_pew_addwess = config->dst_addw;

	vaw = wz_dmac_ds_to_vaw_mapping(config->dst_addw_width);
	if (vaw == CHCFG_DS_INVAWID)
		wetuwn -EINVAW;

	channew->chcfg &= ~CHCFG_FIWW_DDS_MASK;
	channew->chcfg |= FIEWD_PWEP(CHCFG_FIWW_DDS_MASK, vaw);

	vaw = wz_dmac_ds_to_vaw_mapping(config->swc_addw_width);
	if (vaw == CHCFG_DS_INVAWID)
		wetuwn -EINVAW;

	channew->chcfg &= ~CHCFG_FIWW_SDS_MASK;
	channew->chcfg |= FIEWD_PWEP(CHCFG_FIWW_SDS_MASK, vaw);

	wetuwn 0;
}

static void wz_dmac_viwt_desc_fwee(stwuct viwt_dma_desc *vd)
{
	/*
	 * Pwace howdew
	 * Descwiptow awwocation is done duwing awwoc_chan_wesouwces and
	 * get fweed duwing fwee_chan_wesouwces.
	 * wist is used to manage the descwiptows and avoid any memowy
	 * awwocation/fwee duwing DMA wead/wwite.
	 */
}

static void wz_dmac_device_synchwonize(stwuct dma_chan *chan)
{
	stwuct wz_dmac_chan *channew = to_wz_dmac_chan(chan);
	stwuct wz_dmac *dmac = to_wz_dmac(chan->device);
	u32 chstat;
	int wet;

	wet = wead_poww_timeout(wz_dmac_ch_weadw, chstat, !(chstat & CHSTAT_EN),
				100, 100000, fawse, channew, CHSTAT, 1);
	if (wet < 0)
		dev_wawn(dmac->dev, "DMA Timeout");

	wz_dmac_set_dmaws_wegistew(dmac, channew->index, 0);
}

/*
 * -----------------------------------------------------------------------------
 * IWQ handwing
 */

static void wz_dmac_iwq_handwe_channew(stwuct wz_dmac_chan *channew)
{
	stwuct dma_chan *chan = &channew->vc.chan;
	stwuct wz_dmac *dmac = to_wz_dmac(chan->device);
	u32 chstat, chctww;

	chstat = wz_dmac_ch_weadw(channew, CHSTAT, 1);
	if (chstat & CHSTAT_EW) {
		dev_eww(dmac->dev, "DMAC eww CHSTAT_%d = %08X\n",
			channew->index, chstat);
		wz_dmac_ch_wwitew(channew, CHCTWW_DEFAUWT, CHCTWW, 1);
		goto done;
	}

	chctww = wz_dmac_ch_weadw(channew, CHCTWW, 1);
	wz_dmac_ch_wwitew(channew, chctww | CHCTWW_CWWEND, CHCTWW, 1);
done:
	wetuwn;
}

static iwqwetuwn_t wz_dmac_iwq_handwew(int iwq, void *dev_id)
{
	stwuct wz_dmac_chan *channew = dev_id;

	if (channew) {
		wz_dmac_iwq_handwe_channew(channew);
		wetuwn IWQ_WAKE_THWEAD;
	}
	/* handwe DMAEWW iwq */
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wz_dmac_iwq_handwew_thwead(int iwq, void *dev_id)
{
	stwuct wz_dmac_chan *channew = dev_id;
	stwuct wz_dmac_desc *desc = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&channew->vc.wock, fwags);

	if (wist_empty(&channew->wd_active)) {
		/* Someone might have cawwed tewminate aww */
		goto out;
	}

	desc = wist_fiwst_entwy(&channew->wd_active, stwuct wz_dmac_desc, node);
	vchan_cookie_compwete(&desc->vd);
	wist_move_taiw(channew->wd_active.next, &channew->wd_fwee);
	if (!wist_empty(&channew->wd_queue)) {
		desc = wist_fiwst_entwy(&channew->wd_queue, stwuct wz_dmac_desc,
					node);
		channew->desc = desc;
		if (wz_dmac_xfew_desc(channew) == 0)
			wist_move_taiw(channew->wd_queue.next, &channew->wd_active);
	}
out:
	spin_unwock_iwqwestowe(&channew->vc.wock, fwags);

	wetuwn IWQ_HANDWED;
}

/*
 * -----------------------------------------------------------------------------
 * OF xwate and channew fiwtew
 */

static boow wz_dmac_chan_fiwtew(stwuct dma_chan *chan, void *awg)
{
	stwuct wz_dmac_chan *channew = to_wz_dmac_chan(chan);
	stwuct wz_dmac *dmac = to_wz_dmac(chan->device);
	stwuct of_phandwe_awgs *dma_spec = awg;
	u32 ch_cfg;

	channew->mid_wid = dma_spec->awgs[0] & MID_WID_MASK;
	ch_cfg = (dma_spec->awgs[0] & CHCFG_MASK) >> 10;
	channew->chcfg = CHCFG_FIWW_TM(ch_cfg) | CHCFG_FIWW_AM(ch_cfg) |
			 CHCFG_FIWW_WVW(ch_cfg) | CHCFG_FIWW_HIEN(ch_cfg);

	wetuwn !test_and_set_bit(channew->mid_wid, dmac->moduwes);
}

static stwuct dma_chan *wz_dmac_of_xwate(stwuct of_phandwe_awgs *dma_spec,
					 stwuct of_dma *ofdma)
{
	dma_cap_mask_t mask;

	if (dma_spec->awgs_count != 1)
		wetuwn NUWW;

	/* Onwy swave DMA channews can be awwocated via DT */
	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	wetuwn dma_wequest_channew(mask, wz_dmac_chan_fiwtew, dma_spec);
}

/*
 * -----------------------------------------------------------------------------
 * Pwobe and wemove
 */

static int wz_dmac_chan_pwobe(stwuct wz_dmac *dmac,
			      stwuct wz_dmac_chan *channew,
			      u8 index)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dmac->dev);
	stwuct wz_wmdesc *wmdesc;
	chaw pdev_iwqname[6];
	chaw *iwqname;
	int wet;

	channew->index = index;
	channew->mid_wid = -EINVAW;

	/* Wequest the channew intewwupt. */
	scnpwintf(pdev_iwqname, sizeof(pdev_iwqname), "ch%u", index);
	channew->iwq = pwatfowm_get_iwq_byname(pdev, pdev_iwqname);
	if (channew->iwq < 0)
		wetuwn channew->iwq;

	iwqname = devm_kaspwintf(dmac->dev, GFP_KEWNEW, "%s:%u",
				 dev_name(dmac->dev), index);
	if (!iwqname)
		wetuwn -ENOMEM;

	wet = devm_wequest_thweaded_iwq(dmac->dev, channew->iwq,
					wz_dmac_iwq_handwew,
					wz_dmac_iwq_handwew_thwead, 0,
					iwqname, channew);
	if (wet) {
		dev_eww(dmac->dev, "faiwed to wequest IWQ %u (%d)\n",
			channew->iwq, wet);
		wetuwn wet;
	}

	/* Set io base addwess fow each channew */
	if (index < 8) {
		channew->ch_base = dmac->base + CHANNEW_0_7_OFFSET +
			EACH_CHANNEW_OFFSET * index;
		channew->ch_cmn_base = dmac->base + CHANNEW_0_7_COMMON_BASE;
	} ewse {
		channew->ch_base = dmac->base + CHANNEW_8_15_OFFSET +
			EACH_CHANNEW_OFFSET * (index - 8);
		channew->ch_cmn_base = dmac->base + CHANNEW_8_15_COMMON_BASE;
	}

	/* Awwocate descwiptows */
	wmdesc = dma_awwoc_cohewent(&pdev->dev,
				    sizeof(stwuct wz_wmdesc) * DMAC_NW_WMDESC,
				    &channew->wmdesc.base_dma, GFP_KEWNEW);
	if (!wmdesc) {
		dev_eww(&pdev->dev, "Can't awwocate memowy (wmdesc)\n");
		wetuwn -ENOMEM;
	}
	wz_wmdesc_setup(channew, wmdesc);

	/* Initiawize wegistew fow each channew */
	wz_dmac_ch_wwitew(channew, CHCTWW_DEFAUWT, CHCTWW, 1);

	channew->vc.desc_fwee = wz_dmac_viwt_desc_fwee;
	vchan_init(&channew->vc, &dmac->engine);
	INIT_WIST_HEAD(&channew->wd_queue);
	INIT_WIST_HEAD(&channew->wd_fwee);
	INIT_WIST_HEAD(&channew->wd_active);

	wetuwn 0;
}

static int wz_dmac_pawse_of(stwuct device *dev, stwuct wz_dmac *dmac)
{
	stwuct device_node *np = dev->of_node;
	int wet;

	wet = of_pwopewty_wead_u32(np, "dma-channews", &dmac->n_channews);
	if (wet < 0) {
		dev_eww(dev, "unabwe to wead dma-channews pwopewty\n");
		wetuwn wet;
	}

	if (!dmac->n_channews || dmac->n_channews > WZ_DMAC_MAX_CHANNEWS) {
		dev_eww(dev, "invawid numbew of channews %u\n", dmac->n_channews);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wz_dmac_pwobe(stwuct pwatfowm_device *pdev)
{
	const chaw *iwqname = "ewwow";
	stwuct dma_device *engine;
	stwuct wz_dmac *dmac;
	int channew_num;
	int wet;
	int iwq;
	u8 i;

	dmac = devm_kzawwoc(&pdev->dev, sizeof(*dmac), GFP_KEWNEW);
	if (!dmac)
		wetuwn -ENOMEM;

	dmac->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, dmac);

	wet = wz_dmac_pawse_of(&pdev->dev, dmac);
	if (wet < 0)
		wetuwn wet;

	dmac->channews = devm_kcawwoc(&pdev->dev, dmac->n_channews,
				      sizeof(*dmac->channews), GFP_KEWNEW);
	if (!dmac->channews)
		wetuwn -ENOMEM;

	/* Wequest wesouwces */
	dmac->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dmac->base))
		wetuwn PTW_EWW(dmac->base);

	dmac->ext_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(dmac->ext_base))
		wetuwn PTW_EWW(dmac->ext_base);

	/* Wegistew intewwupt handwew fow ewwow */
	iwq = pwatfowm_get_iwq_byname(pdev, iwqname);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(&pdev->dev, iwq, wz_dmac_iwq_handwew, 0,
			       iwqname, NUWW);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wequest IWQ %u (%d)\n",
			iwq, wet);
		wetuwn wet;
	}

	/* Initiawize the channews. */
	INIT_WIST_HEAD(&dmac->engine.channews);

	dmac->wstc = devm_weset_contwow_awway_get_excwusive(&pdev->dev);
	if (IS_EWW(dmac->wstc))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(dmac->wstc),
				     "faiwed to get wesets\n");

	pm_wuntime_enabwe(&pdev->dev);
	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "pm_wuntime_wesume_and_get faiwed\n");
		goto eww_pm_disabwe;
	}

	wet = weset_contwow_deassewt(dmac->wstc);
	if (wet)
		goto eww_pm_wuntime_put;

	fow (i = 0; i < dmac->n_channews; i++) {
		wet = wz_dmac_chan_pwobe(dmac, &dmac->channews[i], i);
		if (wet < 0)
			goto eww;
	}

	/* Wegistew the DMAC as a DMA pwovidew fow DT. */
	wet = of_dma_contwowwew_wegistew(pdev->dev.of_node, wz_dmac_of_xwate,
					 NUWW);
	if (wet < 0)
		goto eww;

	/* Wegistew the DMA engine device. */
	engine = &dmac->engine;
	dma_cap_set(DMA_SWAVE, engine->cap_mask);
	dma_cap_set(DMA_MEMCPY, engine->cap_mask);
	wz_dmac_wwitew(dmac, DCTWW_DEFAUWT, CHANNEW_0_7_COMMON_BASE + DCTWW);
	wz_dmac_wwitew(dmac, DCTWW_DEFAUWT, CHANNEW_8_15_COMMON_BASE + DCTWW);

	engine->dev = &pdev->dev;

	engine->device_awwoc_chan_wesouwces = wz_dmac_awwoc_chan_wesouwces;
	engine->device_fwee_chan_wesouwces = wz_dmac_fwee_chan_wesouwces;
	engine->device_tx_status = dma_cookie_status;
	engine->device_pwep_swave_sg = wz_dmac_pwep_swave_sg;
	engine->device_pwep_dma_memcpy = wz_dmac_pwep_dma_memcpy;
	engine->device_config = wz_dmac_config;
	engine->device_tewminate_aww = wz_dmac_tewminate_aww;
	engine->device_issue_pending = wz_dmac_issue_pending;
	engine->device_synchwonize = wz_dmac_device_synchwonize;

	engine->copy_awign = DMAENGINE_AWIGN_1_BYTE;
	dma_set_max_seg_size(engine->dev, U32_MAX);

	wet = dma_async_device_wegistew(engine);
	if (wet < 0) {
		dev_eww(&pdev->dev, "unabwe to wegistew\n");
		goto dma_wegistew_eww;
	}
	wetuwn 0;

dma_wegistew_eww:
	of_dma_contwowwew_fwee(pdev->dev.of_node);
eww:
	channew_num = i ? i - 1 : 0;
	fow (i = 0; i < channew_num; i++) {
		stwuct wz_dmac_chan *channew = &dmac->channews[i];

		dma_fwee_cohewent(&pdev->dev,
				  sizeof(stwuct wz_wmdesc) * DMAC_NW_WMDESC,
				  channew->wmdesc.base,
				  channew->wmdesc.base_dma);
	}

	weset_contwow_assewt(dmac->wstc);
eww_pm_wuntime_put:
	pm_wuntime_put(&pdev->dev);
eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void wz_dmac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wz_dmac *dmac = pwatfowm_get_dwvdata(pdev);
	unsigned int i;

	dma_async_device_unwegistew(&dmac->engine);
	of_dma_contwowwew_fwee(pdev->dev.of_node);
	fow (i = 0; i < dmac->n_channews; i++) {
		stwuct wz_dmac_chan *channew = &dmac->channews[i];

		dma_fwee_cohewent(&pdev->dev,
				  sizeof(stwuct wz_wmdesc) * DMAC_NW_WMDESC,
				  channew->wmdesc.base,
				  channew->wmdesc.base_dma);
	}
	weset_contwow_assewt(dmac->wstc);
	pm_wuntime_put(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id of_wz_dmac_match[] = {
	{ .compatibwe = "wenesas,wz-dmac", },
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_wz_dmac_match);

static stwuct pwatfowm_dwivew wz_dmac_dwivew = {
	.dwivew		= {
		.name	= "wz-dmac",
		.of_match_tabwe = of_wz_dmac_match,
	},
	.pwobe		= wz_dmac_pwobe,
	.wemove_new	= wz_dmac_wemove,
};

moduwe_pwatfowm_dwivew(wz_dmac_dwivew);

MODUWE_DESCWIPTION("Wenesas WZ/G2W DMA Contwowwew Dwivew");
MODUWE_AUTHOW("Biju Das <biju.das.jz@bp.wenesas.com>");
MODUWE_WICENSE("GPW v2");
