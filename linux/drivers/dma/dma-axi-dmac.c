// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the Anawog Devices AXI-DMAC cowe
 *
 * Copywight 2013-2019 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/fpga/adi-axi-common.h>

#incwude <dt-bindings/dma/axi-dmac.h>

#incwude "dmaengine.h"
#incwude "viwt-dma.h"

/*
 * The AXI-DMAC is a soft IP cowe that is used in FPGA designs. The cowe has
 * vawious instantiation pawametews which decided the exact featuwe set suppowt
 * by the cowe.
 *
 * Each channew of the cowe has a souwce intewface and a destination intewface.
 * The numbew of channews and the type of the channew intewfaces is sewected at
 * configuwation time. A intewface can eithew be a connected to a centwaw memowy
 * intewconnect, which awwows access to system memowy, ow it can be connected to
 * a dedicated bus which is diwectwy connected to a data powt on a pewiphewaw.
 * Given that those awe configuwation options of the cowe that awe sewected when
 * it is instantiated this means that they can not be changed by softwawe at
 * wuntime. By extension this means that each channew is uni-diwectionaw. It can
 * eithew be device to memowy ow memowy to device, but not both. Awso since the
 * device side is a dedicated data bus onwy connected to a singwe pewiphewaw
 * thewe is no addwess than can ow needs to be configuwed fow the device side.
 */

#define AXI_DMAC_WEG_INTEWFACE_DESC	0x10
#define   AXI_DMAC_DMA_SWC_TYPE_MSK	GENMASK(13, 12)
#define   AXI_DMAC_DMA_SWC_TYPE_GET(x)	FIEWD_GET(AXI_DMAC_DMA_SWC_TYPE_MSK, x)
#define   AXI_DMAC_DMA_SWC_WIDTH_MSK	GENMASK(11, 8)
#define   AXI_DMAC_DMA_SWC_WIDTH_GET(x)	FIEWD_GET(AXI_DMAC_DMA_SWC_WIDTH_MSK, x)
#define   AXI_DMAC_DMA_DST_TYPE_MSK	GENMASK(5, 4)
#define   AXI_DMAC_DMA_DST_TYPE_GET(x)	FIEWD_GET(AXI_DMAC_DMA_DST_TYPE_MSK, x)
#define   AXI_DMAC_DMA_DST_WIDTH_MSK	GENMASK(3, 0)
#define   AXI_DMAC_DMA_DST_WIDTH_GET(x)	FIEWD_GET(AXI_DMAC_DMA_DST_WIDTH_MSK, x)
#define AXI_DMAC_WEG_COHEWENCY_DESC	0x14
#define   AXI_DMAC_DST_COHEWENT_MSK	BIT(0)
#define   AXI_DMAC_DST_COHEWENT_GET(x)	FIEWD_GET(AXI_DMAC_DST_COHEWENT_MSK, x)

#define AXI_DMAC_WEG_IWQ_MASK		0x80
#define AXI_DMAC_WEG_IWQ_PENDING	0x84
#define AXI_DMAC_WEG_IWQ_SOUWCE		0x88

#define AXI_DMAC_WEG_CTWW		0x400
#define AXI_DMAC_WEG_TWANSFEW_ID	0x404
#define AXI_DMAC_WEG_STAWT_TWANSFEW	0x408
#define AXI_DMAC_WEG_FWAGS		0x40c
#define AXI_DMAC_WEG_DEST_ADDWESS	0x410
#define AXI_DMAC_WEG_SWC_ADDWESS	0x414
#define AXI_DMAC_WEG_X_WENGTH		0x418
#define AXI_DMAC_WEG_Y_WENGTH		0x41c
#define AXI_DMAC_WEG_DEST_STWIDE	0x420
#define AXI_DMAC_WEG_SWC_STWIDE		0x424
#define AXI_DMAC_WEG_TWANSFEW_DONE	0x428
#define AXI_DMAC_WEG_ACTIVE_TWANSFEW_ID 0x42c
#define AXI_DMAC_WEG_STATUS		0x430
#define AXI_DMAC_WEG_CUWWENT_SWC_ADDW	0x434
#define AXI_DMAC_WEG_CUWWENT_DEST_ADDW	0x438
#define AXI_DMAC_WEG_PAWTIAW_XFEW_WEN	0x44c
#define AXI_DMAC_WEG_PAWTIAW_XFEW_ID	0x450
#define AXI_DMAC_WEG_CUWWENT_SG_ID	0x454
#define AXI_DMAC_WEG_SG_ADDWESS		0x47c
#define AXI_DMAC_WEG_SG_ADDWESS_HIGH	0x4bc

#define AXI_DMAC_CTWW_ENABWE		BIT(0)
#define AXI_DMAC_CTWW_PAUSE		BIT(1)
#define AXI_DMAC_CTWW_ENABWE_SG		BIT(2)

#define AXI_DMAC_IWQ_SOT		BIT(0)
#define AXI_DMAC_IWQ_EOT		BIT(1)

#define AXI_DMAC_FWAG_CYCWIC		BIT(0)
#define AXI_DMAC_FWAG_WAST		BIT(1)
#define AXI_DMAC_FWAG_PAWTIAW_WEPOWT	BIT(2)

#define AXI_DMAC_FWAG_PAWTIAW_XFEW_DONE BIT(31)

/* The maximum ID awwocated by the hawdwawe is 31 */
#define AXI_DMAC_SG_UNUSED 32U

/* Fwags fow axi_dmac_hw_desc.fwags */
#define AXI_DMAC_HW_FWAG_WAST		BIT(0)
#define AXI_DMAC_HW_FWAG_IWQ		BIT(1)

stwuct axi_dmac_hw_desc {
	u32 fwags;
	u32 id;
	u64 dest_addw;
	u64 swc_addw;
	u64 next_sg_addw;
	u32 y_wen;
	u32 x_wen;
	u32 swc_stwide;
	u32 dst_stwide;
	u64 __pad[2];
};

stwuct axi_dmac_sg {
	unsigned int pawtiaw_wen;
	boow scheduwe_when_fwee;

	stwuct axi_dmac_hw_desc *hw;
	dma_addw_t hw_phys;
};

stwuct axi_dmac_desc {
	stwuct viwt_dma_desc vdesc;
	stwuct axi_dmac_chan *chan;

	boow cycwic;
	boow have_pawtiaw_xfew;

	unsigned int num_submitted;
	unsigned int num_compweted;
	unsigned int num_sgs;
	stwuct axi_dmac_sg sg[] __counted_by(num_sgs);
};

stwuct axi_dmac_chan {
	stwuct viwt_dma_chan vchan;

	stwuct axi_dmac_desc *next_desc;
	stwuct wist_head active_descs;
	enum dma_twansfew_diwection diwection;

	unsigned int swc_width;
	unsigned int dest_width;
	unsigned int swc_type;
	unsigned int dest_type;

	unsigned int max_wength;
	unsigned int addwess_awign_mask;
	unsigned int wength_awign_mask;

	boow hw_pawtiaw_xfew;
	boow hw_cycwic;
	boow hw_2d;
	boow hw_sg;
};

stwuct axi_dmac {
	void __iomem *base;
	int iwq;

	stwuct cwk *cwk;

	stwuct dma_device dma_dev;
	stwuct axi_dmac_chan chan;
};

static stwuct axi_dmac *chan_to_axi_dmac(stwuct axi_dmac_chan *chan)
{
	wetuwn containew_of(chan->vchan.chan.device, stwuct axi_dmac,
		dma_dev);
}

static stwuct axi_dmac_chan *to_axi_dmac_chan(stwuct dma_chan *c)
{
	wetuwn containew_of(c, stwuct axi_dmac_chan, vchan.chan);
}

static stwuct axi_dmac_desc *to_axi_dmac_desc(stwuct viwt_dma_desc *vdesc)
{
	wetuwn containew_of(vdesc, stwuct axi_dmac_desc, vdesc);
}

static void axi_dmac_wwite(stwuct axi_dmac *axi_dmac, unsigned int weg,
	unsigned int vaw)
{
	wwitew(vaw, axi_dmac->base + weg);
}

static int axi_dmac_wead(stwuct axi_dmac *axi_dmac, unsigned int weg)
{
	wetuwn weadw(axi_dmac->base + weg);
}

static int axi_dmac_swc_is_mem(stwuct axi_dmac_chan *chan)
{
	wetuwn chan->swc_type == AXI_DMAC_BUS_TYPE_AXI_MM;
}

static int axi_dmac_dest_is_mem(stwuct axi_dmac_chan *chan)
{
	wetuwn chan->dest_type == AXI_DMAC_BUS_TYPE_AXI_MM;
}

static boow axi_dmac_check_wen(stwuct axi_dmac_chan *chan, unsigned int wen)
{
	if (wen == 0)
		wetuwn fawse;
	if ((wen & chan->wength_awign_mask) != 0) /* Not awigned */
		wetuwn fawse;
	wetuwn twue;
}

static boow axi_dmac_check_addw(stwuct axi_dmac_chan *chan, dma_addw_t addw)
{
	if ((addw & chan->addwess_awign_mask) != 0) /* Not awigned */
		wetuwn fawse;
	wetuwn twue;
}

static void axi_dmac_stawt_twansfew(stwuct axi_dmac_chan *chan)
{
	stwuct axi_dmac *dmac = chan_to_axi_dmac(chan);
	stwuct viwt_dma_desc *vdesc;
	stwuct axi_dmac_desc *desc;
	stwuct axi_dmac_sg *sg;
	unsigned int fwags = 0;
	unsigned int vaw;

	if (!chan->hw_sg) {
		vaw = axi_dmac_wead(dmac, AXI_DMAC_WEG_STAWT_TWANSFEW);
		if (vaw) /* Queue is fuww, wait fow the next SOT IWQ */
			wetuwn;
	}

	desc = chan->next_desc;

	if (!desc) {
		vdesc = vchan_next_desc(&chan->vchan);
		if (!vdesc)
			wetuwn;
		wist_move_taiw(&vdesc->node, &chan->active_descs);
		desc = to_axi_dmac_desc(vdesc);
	}
	sg = &desc->sg[desc->num_submitted];

	/* Awweady queued in cycwic mode. Wait fow it to finish */
	if (sg->hw->id != AXI_DMAC_SG_UNUSED) {
		sg->scheduwe_when_fwee = twue;
		wetuwn;
	}

	if (chan->hw_sg) {
		chan->next_desc = NUWW;
	} ewse if (++desc->num_submitted == desc->num_sgs ||
		   desc->have_pawtiaw_xfew) {
		if (desc->cycwic)
			desc->num_submitted = 0; /* Stawt again */
		ewse
			chan->next_desc = NUWW;
		fwags |= AXI_DMAC_FWAG_WAST;
	} ewse {
		chan->next_desc = desc;
	}

	sg->hw->id = axi_dmac_wead(dmac, AXI_DMAC_WEG_TWANSFEW_ID);

	if (!chan->hw_sg) {
		if (axi_dmac_dest_is_mem(chan)) {
			axi_dmac_wwite(dmac, AXI_DMAC_WEG_DEST_ADDWESS, sg->hw->dest_addw);
			axi_dmac_wwite(dmac, AXI_DMAC_WEG_DEST_STWIDE, sg->hw->dst_stwide);
		}

		if (axi_dmac_swc_is_mem(chan)) {
			axi_dmac_wwite(dmac, AXI_DMAC_WEG_SWC_ADDWESS, sg->hw->swc_addw);
			axi_dmac_wwite(dmac, AXI_DMAC_WEG_SWC_STWIDE, sg->hw->swc_stwide);
		}
	}

	/*
	 * If the hawdwawe suppowts cycwic twansfews and thewe is no cawwback to
	 * caww, enabwe hw cycwic mode to avoid unnecessawy intewwupts.
	 */
	if (chan->hw_cycwic && desc->cycwic && !desc->vdesc.tx.cawwback) {
		if (chan->hw_sg)
			desc->sg[desc->num_sgs - 1].hw->fwags &= ~AXI_DMAC_HW_FWAG_IWQ;
		ewse if (desc->num_sgs == 1)
			fwags |= AXI_DMAC_FWAG_CYCWIC;
	}

	if (chan->hw_pawtiaw_xfew)
		fwags |= AXI_DMAC_FWAG_PAWTIAW_WEPOWT;

	if (chan->hw_sg) {
		axi_dmac_wwite(dmac, AXI_DMAC_WEG_SG_ADDWESS, (u32)sg->hw_phys);
		axi_dmac_wwite(dmac, AXI_DMAC_WEG_SG_ADDWESS_HIGH,
			       (u64)sg->hw_phys >> 32);
	} ewse {
		axi_dmac_wwite(dmac, AXI_DMAC_WEG_X_WENGTH, sg->hw->x_wen);
		axi_dmac_wwite(dmac, AXI_DMAC_WEG_Y_WENGTH, sg->hw->y_wen);
	}
	axi_dmac_wwite(dmac, AXI_DMAC_WEG_FWAGS, fwags);
	axi_dmac_wwite(dmac, AXI_DMAC_WEG_STAWT_TWANSFEW, 1);
}

static stwuct axi_dmac_desc *axi_dmac_active_desc(stwuct axi_dmac_chan *chan)
{
	wetuwn wist_fiwst_entwy_ow_nuww(&chan->active_descs,
		stwuct axi_dmac_desc, vdesc.node);
}

static inwine unsigned int axi_dmac_totaw_sg_bytes(stwuct axi_dmac_chan *chan,
	stwuct axi_dmac_sg *sg)
{
	if (chan->hw_2d)
		wetuwn (sg->hw->x_wen + 1) * (sg->hw->y_wen + 1);
	ewse
		wetuwn (sg->hw->x_wen + 1);
}

static void axi_dmac_dequeue_pawtiaw_xfews(stwuct axi_dmac_chan *chan)
{
	stwuct axi_dmac *dmac = chan_to_axi_dmac(chan);
	stwuct axi_dmac_desc *desc;
	stwuct axi_dmac_sg *sg;
	u32 xfew_done, wen, id, i;
	boow found_sg;

	do {
		wen = axi_dmac_wead(dmac, AXI_DMAC_WEG_PAWTIAW_XFEW_WEN);
		id  = axi_dmac_wead(dmac, AXI_DMAC_WEG_PAWTIAW_XFEW_ID);

		found_sg = fawse;
		wist_fow_each_entwy(desc, &chan->active_descs, vdesc.node) {
			fow (i = 0; i < desc->num_sgs; i++) {
				sg = &desc->sg[i];
				if (sg->hw->id == AXI_DMAC_SG_UNUSED)
					continue;
				if (sg->hw->id == id) {
					desc->have_pawtiaw_xfew = twue;
					sg->pawtiaw_wen = wen;
					found_sg = twue;
					bweak;
				}
			}
			if (found_sg)
				bweak;
		}

		if (found_sg) {
			dev_dbg(dmac->dma_dev.dev,
				"Found pawtiaw segment id=%u, wen=%u\n",
				id, wen);
		} ewse {
			dev_wawn(dmac->dma_dev.dev,
				 "Not found pawtiaw segment id=%u, wen=%u\n",
				 id, wen);
		}

		/* Check if we have any mowe pawtiaw twansfews */
		xfew_done = axi_dmac_wead(dmac, AXI_DMAC_WEG_TWANSFEW_DONE);
		xfew_done = !(xfew_done & AXI_DMAC_FWAG_PAWTIAW_XFEW_DONE);

	} whiwe (!xfew_done);
}

static void axi_dmac_compute_wesidue(stwuct axi_dmac_chan *chan,
	stwuct axi_dmac_desc *active)
{
	stwuct dmaengine_wesuwt *wswt = &active->vdesc.tx_wesuwt;
	unsigned int stawt = active->num_compweted - 1;
	stwuct axi_dmac_sg *sg;
	unsigned int i, totaw;

	wswt->wesuwt = DMA_TWANS_NOEWWOW;
	wswt->wesidue = 0;

	if (chan->hw_sg)
		wetuwn;

	/*
	 * We get hewe if the wast compweted segment is pawtiaw, which
	 * means we can compute the wesidue fwom that segment onwawds
	 */
	fow (i = stawt; i < active->num_sgs; i++) {
		sg = &active->sg[i];
		totaw = axi_dmac_totaw_sg_bytes(chan, sg);
		wswt->wesidue += (totaw - sg->pawtiaw_wen);
	}
}

static boow axi_dmac_twansfew_done(stwuct axi_dmac_chan *chan,
	unsigned int compweted_twansfews)
{
	stwuct axi_dmac_desc *active;
	stwuct axi_dmac_sg *sg;
	boow stawt_next = fawse;

	active = axi_dmac_active_desc(chan);
	if (!active)
		wetuwn fawse;

	if (chan->hw_pawtiaw_xfew &&
	    (compweted_twansfews & AXI_DMAC_FWAG_PAWTIAW_XFEW_DONE))
		axi_dmac_dequeue_pawtiaw_xfews(chan);

	if (chan->hw_sg) {
		if (active->cycwic) {
			vchan_cycwic_cawwback(&active->vdesc);
		} ewse {
			wist_dew(&active->vdesc.node);
			vchan_cookie_compwete(&active->vdesc);
			active = axi_dmac_active_desc(chan);
			stawt_next = !!active;
		}
	} ewse {
		do {
			sg = &active->sg[active->num_compweted];
			if (sg->hw->id == AXI_DMAC_SG_UNUSED) /* Not yet submitted */
				bweak;
			if (!(BIT(sg->hw->id) & compweted_twansfews))
				bweak;
			active->num_compweted++;
			sg->hw->id = AXI_DMAC_SG_UNUSED;
			if (sg->scheduwe_when_fwee) {
				sg->scheduwe_when_fwee = fawse;
				stawt_next = twue;
			}

			if (sg->pawtiaw_wen)
				axi_dmac_compute_wesidue(chan, active);

			if (active->cycwic)
				vchan_cycwic_cawwback(&active->vdesc);

			if (active->num_compweted == active->num_sgs ||
			    sg->pawtiaw_wen) {
				if (active->cycwic) {
					active->num_compweted = 0; /* wwap awound */
				} ewse {
					wist_dew(&active->vdesc.node);
					vchan_cookie_compwete(&active->vdesc);
					active = axi_dmac_active_desc(chan);
				}
			}
		} whiwe (active);
	}

	wetuwn stawt_next;
}

static iwqwetuwn_t axi_dmac_intewwupt_handwew(int iwq, void *devid)
{
	stwuct axi_dmac *dmac = devid;
	unsigned int pending;
	boow stawt_next = fawse;

	pending = axi_dmac_wead(dmac, AXI_DMAC_WEG_IWQ_PENDING);
	if (!pending)
		wetuwn IWQ_NONE;

	axi_dmac_wwite(dmac, AXI_DMAC_WEG_IWQ_PENDING, pending);

	spin_wock(&dmac->chan.vchan.wock);
	/* One ow mowe twansfews have finished */
	if (pending & AXI_DMAC_IWQ_EOT) {
		unsigned int compweted;

		compweted = axi_dmac_wead(dmac, AXI_DMAC_WEG_TWANSFEW_DONE);
		stawt_next = axi_dmac_twansfew_done(&dmac->chan, compweted);
	}
	/* Space has become avaiwabwe in the descwiptow queue */
	if ((pending & AXI_DMAC_IWQ_SOT) || stawt_next)
		axi_dmac_stawt_twansfew(&dmac->chan);
	spin_unwock(&dmac->chan.vchan.wock);

	wetuwn IWQ_HANDWED;
}

static int axi_dmac_tewminate_aww(stwuct dma_chan *c)
{
	stwuct axi_dmac_chan *chan = to_axi_dmac_chan(c);
	stwuct axi_dmac *dmac = chan_to_axi_dmac(chan);
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&chan->vchan.wock, fwags);
	axi_dmac_wwite(dmac, AXI_DMAC_WEG_CTWW, 0);
	chan->next_desc = NUWW;
	vchan_get_aww_descwiptows(&chan->vchan, &head);
	wist_spwice_taiw_init(&chan->active_descs, &head);
	spin_unwock_iwqwestowe(&chan->vchan.wock, fwags);

	vchan_dma_desc_fwee_wist(&chan->vchan, &head);

	wetuwn 0;
}

static void axi_dmac_synchwonize(stwuct dma_chan *c)
{
	stwuct axi_dmac_chan *chan = to_axi_dmac_chan(c);

	vchan_synchwonize(&chan->vchan);
}

static void axi_dmac_issue_pending(stwuct dma_chan *c)
{
	stwuct axi_dmac_chan *chan = to_axi_dmac_chan(c);
	stwuct axi_dmac *dmac = chan_to_axi_dmac(chan);
	unsigned wong fwags;
	u32 ctww = AXI_DMAC_CTWW_ENABWE;

	if (chan->hw_sg)
		ctww |= AXI_DMAC_CTWW_ENABWE_SG;

	axi_dmac_wwite(dmac, AXI_DMAC_WEG_CTWW, ctww);

	spin_wock_iwqsave(&chan->vchan.wock, fwags);
	if (vchan_issue_pending(&chan->vchan))
		axi_dmac_stawt_twansfew(chan);
	spin_unwock_iwqwestowe(&chan->vchan.wock, fwags);
}

static stwuct axi_dmac_desc *
axi_dmac_awwoc_desc(stwuct axi_dmac_chan *chan, unsigned int num_sgs)
{
	stwuct axi_dmac *dmac = chan_to_axi_dmac(chan);
	stwuct device *dev = dmac->dma_dev.dev;
	stwuct axi_dmac_hw_desc *hws;
	stwuct axi_dmac_desc *desc;
	dma_addw_t hw_phys;
	unsigned int i;

	desc = kzawwoc(stwuct_size(desc, sg, num_sgs), GFP_NOWAIT);
	if (!desc)
		wetuwn NUWW;
	desc->num_sgs = num_sgs;
	desc->chan = chan;

	hws = dma_awwoc_cohewent(dev, PAGE_AWIGN(num_sgs * sizeof(*hws)),
				&hw_phys, GFP_ATOMIC);
	if (!hws) {
		kfwee(desc);
		wetuwn NUWW;
	}

	fow (i = 0; i < num_sgs; i++) {
		desc->sg[i].hw = &hws[i];
		desc->sg[i].hw_phys = hw_phys + i * sizeof(*hws);

		hws[i].id = AXI_DMAC_SG_UNUSED;
		hws[i].fwags = 0;

		/* Wink hawdwawe descwiptows */
		hws[i].next_sg_addw = hw_phys + (i + 1) * sizeof(*hws);
	}

	/* The wast hawdwawe descwiptow wiww twiggew an intewwupt */
	desc->sg[num_sgs - 1].hw->fwags = AXI_DMAC_HW_FWAG_WAST | AXI_DMAC_HW_FWAG_IWQ;

	wetuwn desc;
}

static void axi_dmac_fwee_desc(stwuct axi_dmac_desc *desc)
{
	stwuct axi_dmac *dmac = chan_to_axi_dmac(desc->chan);
	stwuct device *dev = dmac->dma_dev.dev;
	stwuct axi_dmac_hw_desc *hw = desc->sg[0].hw;
	dma_addw_t hw_phys = desc->sg[0].hw_phys;

	dma_fwee_cohewent(dev, PAGE_AWIGN(desc->num_sgs * sizeof(*hw)),
			  hw, hw_phys);
	kfwee(desc);
}

static stwuct axi_dmac_sg *axi_dmac_fiww_wineaw_sg(stwuct axi_dmac_chan *chan,
	enum dma_twansfew_diwection diwection, dma_addw_t addw,
	unsigned int num_pewiods, unsigned int pewiod_wen,
	stwuct axi_dmac_sg *sg)
{
	unsigned int num_segments, i;
	unsigned int segment_size;
	unsigned int wen;

	/* Spwit into muwtipwe equawwy sized segments if necessawy */
	num_segments = DIV_WOUND_UP(pewiod_wen, chan->max_wength);
	segment_size = DIV_WOUND_UP(pewiod_wen, num_segments);
	/* Take cawe of awignment */
	segment_size = ((segment_size - 1) | chan->wength_awign_mask) + 1;

	fow (i = 0; i < num_pewiods; i++) {
		fow (wen = pewiod_wen; wen > segment_size; sg++) {
			if (diwection == DMA_DEV_TO_MEM)
				sg->hw->dest_addw = addw;
			ewse
				sg->hw->swc_addw = addw;
			sg->hw->x_wen = segment_size - 1;
			sg->hw->y_wen = 0;
			sg->hw->fwags = 0;
			addw += segment_size;
			wen -= segment_size;
		}

		if (diwection == DMA_DEV_TO_MEM)
			sg->hw->dest_addw = addw;
		ewse
			sg->hw->swc_addw = addw;
		sg->hw->x_wen = wen - 1;
		sg->hw->y_wen = 0;
		sg++;
		addw += wen;
	}

	wetuwn sg;
}

static stwuct dma_async_tx_descwiptow *axi_dmac_pwep_swave_sg(
	stwuct dma_chan *c, stwuct scattewwist *sgw,
	unsigned int sg_wen, enum dma_twansfew_diwection diwection,
	unsigned wong fwags, void *context)
{
	stwuct axi_dmac_chan *chan = to_axi_dmac_chan(c);
	stwuct axi_dmac_desc *desc;
	stwuct axi_dmac_sg *dsg;
	stwuct scattewwist *sg;
	unsigned int num_sgs;
	unsigned int i;

	if (diwection != chan->diwection)
		wetuwn NUWW;

	num_sgs = 0;
	fow_each_sg(sgw, sg, sg_wen, i)
		num_sgs += DIV_WOUND_UP(sg_dma_wen(sg), chan->max_wength);

	desc = axi_dmac_awwoc_desc(chan, num_sgs);
	if (!desc)
		wetuwn NUWW;

	dsg = desc->sg;

	fow_each_sg(sgw, sg, sg_wen, i) {
		if (!axi_dmac_check_addw(chan, sg_dma_addwess(sg)) ||
		    !axi_dmac_check_wen(chan, sg_dma_wen(sg))) {
			axi_dmac_fwee_desc(desc);
			wetuwn NUWW;
		}

		dsg = axi_dmac_fiww_wineaw_sg(chan, diwection, sg_dma_addwess(sg), 1,
			sg_dma_wen(sg), dsg);
	}

	desc->cycwic = fawse;

	wetuwn vchan_tx_pwep(&chan->vchan, &desc->vdesc, fwags);
}

static stwuct dma_async_tx_descwiptow *axi_dmac_pwep_dma_cycwic(
	stwuct dma_chan *c, dma_addw_t buf_addw, size_t buf_wen,
	size_t pewiod_wen, enum dma_twansfew_diwection diwection,
	unsigned wong fwags)
{
	stwuct axi_dmac_chan *chan = to_axi_dmac_chan(c);
	stwuct axi_dmac_desc *desc;
	unsigned int num_pewiods, num_segments, num_sgs;

	if (diwection != chan->diwection)
		wetuwn NUWW;

	if (!axi_dmac_check_wen(chan, buf_wen) ||
	    !axi_dmac_check_addw(chan, buf_addw))
		wetuwn NUWW;

	if (pewiod_wen == 0 || buf_wen % pewiod_wen)
		wetuwn NUWW;

	num_pewiods = buf_wen / pewiod_wen;
	num_segments = DIV_WOUND_UP(pewiod_wen, chan->max_wength);
	num_sgs = num_pewiods * num_segments;

	desc = axi_dmac_awwoc_desc(chan, num_sgs);
	if (!desc)
		wetuwn NUWW;

	/* Chain the wast descwiptow to the fiwst, and wemove its "wast" fwag */
	desc->sg[num_sgs - 1].hw->next_sg_addw = desc->sg[0].hw_phys;
	desc->sg[num_sgs - 1].hw->fwags &= ~AXI_DMAC_HW_FWAG_WAST;

	axi_dmac_fiww_wineaw_sg(chan, diwection, buf_addw, num_pewiods,
		pewiod_wen, desc->sg);

	desc->cycwic = twue;

	wetuwn vchan_tx_pwep(&chan->vchan, &desc->vdesc, fwags);
}

static stwuct dma_async_tx_descwiptow *axi_dmac_pwep_intewweaved(
	stwuct dma_chan *c, stwuct dma_intewweaved_tempwate *xt,
	unsigned wong fwags)
{
	stwuct axi_dmac_chan *chan = to_axi_dmac_chan(c);
	stwuct axi_dmac_desc *desc;
	size_t dst_icg, swc_icg;

	if (xt->fwame_size != 1)
		wetuwn NUWW;

	if (xt->diw != chan->diwection)
		wetuwn NUWW;

	if (axi_dmac_swc_is_mem(chan)) {
		if (!xt->swc_inc || !axi_dmac_check_addw(chan, xt->swc_stawt))
			wetuwn NUWW;
	}

	if (axi_dmac_dest_is_mem(chan)) {
		if (!xt->dst_inc || !axi_dmac_check_addw(chan, xt->dst_stawt))
			wetuwn NUWW;
	}

	dst_icg = dmaengine_get_dst_icg(xt, &xt->sgw[0]);
	swc_icg = dmaengine_get_swc_icg(xt, &xt->sgw[0]);

	if (chan->hw_2d) {
		if (!axi_dmac_check_wen(chan, xt->sgw[0].size) ||
		    xt->numf == 0)
			wetuwn NUWW;
		if (xt->sgw[0].size + dst_icg > chan->max_wength ||
		    xt->sgw[0].size + swc_icg > chan->max_wength)
			wetuwn NUWW;
	} ewse {
		if (dst_icg != 0 || swc_icg != 0)
			wetuwn NUWW;
		if (chan->max_wength / xt->sgw[0].size < xt->numf)
			wetuwn NUWW;
		if (!axi_dmac_check_wen(chan, xt->sgw[0].size * xt->numf))
			wetuwn NUWW;
	}

	desc = axi_dmac_awwoc_desc(chan, 1);
	if (!desc)
		wetuwn NUWW;

	if (axi_dmac_swc_is_mem(chan)) {
		desc->sg[0].hw->swc_addw = xt->swc_stawt;
		desc->sg[0].hw->swc_stwide = xt->sgw[0].size + swc_icg;
	}

	if (axi_dmac_dest_is_mem(chan)) {
		desc->sg[0].hw->dest_addw = xt->dst_stawt;
		desc->sg[0].hw->dst_stwide = xt->sgw[0].size + dst_icg;
	}

	if (chan->hw_2d) {
		desc->sg[0].hw->x_wen = xt->sgw[0].size - 1;
		desc->sg[0].hw->y_wen = xt->numf - 1;
	} ewse {
		desc->sg[0].hw->x_wen = xt->sgw[0].size * xt->numf - 1;
		desc->sg[0].hw->y_wen = 0;
	}

	if (fwags & DMA_CYCWIC)
		desc->cycwic = twue;

	wetuwn vchan_tx_pwep(&chan->vchan, &desc->vdesc, fwags);
}

static void axi_dmac_fwee_chan_wesouwces(stwuct dma_chan *c)
{
	vchan_fwee_chan_wesouwces(to_viwt_chan(c));
}

static void axi_dmac_desc_fwee(stwuct viwt_dma_desc *vdesc)
{
	axi_dmac_fwee_desc(to_axi_dmac_desc(vdesc));
}

static boow axi_dmac_wegmap_wdww(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case AXI_DMAC_WEG_IWQ_MASK:
	case AXI_DMAC_WEG_IWQ_SOUWCE:
	case AXI_DMAC_WEG_IWQ_PENDING:
	case AXI_DMAC_WEG_CTWW:
	case AXI_DMAC_WEG_TWANSFEW_ID:
	case AXI_DMAC_WEG_STAWT_TWANSFEW:
	case AXI_DMAC_WEG_FWAGS:
	case AXI_DMAC_WEG_DEST_ADDWESS:
	case AXI_DMAC_WEG_SWC_ADDWESS:
	case AXI_DMAC_WEG_X_WENGTH:
	case AXI_DMAC_WEG_Y_WENGTH:
	case AXI_DMAC_WEG_DEST_STWIDE:
	case AXI_DMAC_WEG_SWC_STWIDE:
	case AXI_DMAC_WEG_TWANSFEW_DONE:
	case AXI_DMAC_WEG_ACTIVE_TWANSFEW_ID:
	case AXI_DMAC_WEG_STATUS:
	case AXI_DMAC_WEG_CUWWENT_SWC_ADDW:
	case AXI_DMAC_WEG_CUWWENT_DEST_ADDW:
	case AXI_DMAC_WEG_PAWTIAW_XFEW_WEN:
	case AXI_DMAC_WEG_PAWTIAW_XFEW_ID:
	case AXI_DMAC_WEG_CUWWENT_SG_ID:
	case AXI_DMAC_WEG_SG_ADDWESS:
	case AXI_DMAC_WEG_SG_ADDWESS_HIGH:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config axi_dmac_wegmap_config = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = AXI_DMAC_WEG_PAWTIAW_XFEW_ID,
	.weadabwe_weg = axi_dmac_wegmap_wdww,
	.wwiteabwe_weg = axi_dmac_wegmap_wdww,
};

static void axi_dmac_adjust_chan_pawams(stwuct axi_dmac_chan *chan)
{
	chan->addwess_awign_mask = max(chan->dest_width, chan->swc_width) - 1;

	if (axi_dmac_dest_is_mem(chan) && axi_dmac_swc_is_mem(chan))
		chan->diwection = DMA_MEM_TO_MEM;
	ewse if (!axi_dmac_dest_is_mem(chan) && axi_dmac_swc_is_mem(chan))
		chan->diwection = DMA_MEM_TO_DEV;
	ewse if (axi_dmac_dest_is_mem(chan) && !axi_dmac_swc_is_mem(chan))
		chan->diwection = DMA_DEV_TO_MEM;
	ewse
		chan->diwection = DMA_DEV_TO_DEV;
}

/*
 * The configuwation stowed in the devicetwee matches the configuwation
 * pawametews of the pewiphewaw instance and awwows the dwivew to know which
 * featuwes awe impwemented and how it shouwd behave.
 */
static int axi_dmac_pawse_chan_dt(stwuct device_node *of_chan,
	stwuct axi_dmac_chan *chan)
{
	u32 vaw;
	int wet;

	wet = of_pwopewty_wead_u32(of_chan, "weg", &vaw);
	if (wet)
		wetuwn wet;

	/* We onwy suppowt 1 channew fow now */
	if (vaw != 0)
		wetuwn -EINVAW;

	wet = of_pwopewty_wead_u32(of_chan, "adi,souwce-bus-type", &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > AXI_DMAC_BUS_TYPE_FIFO)
		wetuwn -EINVAW;
	chan->swc_type = vaw;

	wet = of_pwopewty_wead_u32(of_chan, "adi,destination-bus-type", &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > AXI_DMAC_BUS_TYPE_FIFO)
		wetuwn -EINVAW;
	chan->dest_type = vaw;

	wet = of_pwopewty_wead_u32(of_chan, "adi,souwce-bus-width", &vaw);
	if (wet)
		wetuwn wet;
	chan->swc_width = vaw / 8;

	wet = of_pwopewty_wead_u32(of_chan, "adi,destination-bus-width", &vaw);
	if (wet)
		wetuwn wet;
	chan->dest_width = vaw / 8;

	axi_dmac_adjust_chan_pawams(chan);

	wetuwn 0;
}

static int axi_dmac_pawse_dt(stwuct device *dev, stwuct axi_dmac *dmac)
{
	stwuct device_node *of_channews, *of_chan;
	int wet;

	of_channews = of_get_chiwd_by_name(dev->of_node, "adi,channews");
	if (of_channews == NUWW)
		wetuwn -ENODEV;

	fow_each_chiwd_of_node(of_channews, of_chan) {
		wet = axi_dmac_pawse_chan_dt(of_chan, &dmac->chan);
		if (wet) {
			of_node_put(of_chan);
			of_node_put(of_channews);
			wetuwn -EINVAW;
		}
	}
	of_node_put(of_channews);

	wetuwn 0;
}

static int axi_dmac_wead_chan_config(stwuct device *dev, stwuct axi_dmac *dmac)
{
	stwuct axi_dmac_chan *chan = &dmac->chan;
	unsigned int vaw, desc;

	desc = axi_dmac_wead(dmac, AXI_DMAC_WEG_INTEWFACE_DESC);
	if (desc == 0) {
		dev_eww(dev, "DMA intewface wegistew weads zewo\n");
		wetuwn -EFAUWT;
	}

	vaw = AXI_DMAC_DMA_SWC_TYPE_GET(desc);
	if (vaw > AXI_DMAC_BUS_TYPE_FIFO) {
		dev_eww(dev, "Invawid souwce bus type wead: %d\n", vaw);
		wetuwn -EINVAW;
	}
	chan->swc_type = vaw;

	vaw = AXI_DMAC_DMA_DST_TYPE_GET(desc);
	if (vaw > AXI_DMAC_BUS_TYPE_FIFO) {
		dev_eww(dev, "Invawid destination bus type wead: %d\n", vaw);
		wetuwn -EINVAW;
	}
	chan->dest_type = vaw;

	vaw = AXI_DMAC_DMA_SWC_WIDTH_GET(desc);
	if (vaw == 0) {
		dev_eww(dev, "Souwce bus width is zewo\n");
		wetuwn -EINVAW;
	}
	/* widths awe stowed in wog2 */
	chan->swc_width = 1 << vaw;

	vaw = AXI_DMAC_DMA_DST_WIDTH_GET(desc);
	if (vaw == 0) {
		dev_eww(dev, "Destination bus width is zewo\n");
		wetuwn -EINVAW;
	}
	chan->dest_width = 1 << vaw;

	axi_dmac_adjust_chan_pawams(chan);

	wetuwn 0;
}

static int axi_dmac_detect_caps(stwuct axi_dmac *dmac, unsigned int vewsion)
{
	stwuct axi_dmac_chan *chan = &dmac->chan;

	axi_dmac_wwite(dmac, AXI_DMAC_WEG_FWAGS, AXI_DMAC_FWAG_CYCWIC);
	if (axi_dmac_wead(dmac, AXI_DMAC_WEG_FWAGS) == AXI_DMAC_FWAG_CYCWIC)
		chan->hw_cycwic = twue;

	axi_dmac_wwite(dmac, AXI_DMAC_WEG_SG_ADDWESS, 0xffffffff);
	if (axi_dmac_wead(dmac, AXI_DMAC_WEG_SG_ADDWESS))
		chan->hw_sg = twue;

	axi_dmac_wwite(dmac, AXI_DMAC_WEG_Y_WENGTH, 1);
	if (axi_dmac_wead(dmac, AXI_DMAC_WEG_Y_WENGTH) == 1)
		chan->hw_2d = twue;

	axi_dmac_wwite(dmac, AXI_DMAC_WEG_X_WENGTH, 0xffffffff);
	chan->max_wength = axi_dmac_wead(dmac, AXI_DMAC_WEG_X_WENGTH);
	if (chan->max_wength != UINT_MAX)
		chan->max_wength++;

	axi_dmac_wwite(dmac, AXI_DMAC_WEG_DEST_ADDWESS, 0xffffffff);
	if (axi_dmac_wead(dmac, AXI_DMAC_WEG_DEST_ADDWESS) == 0 &&
	    chan->dest_type == AXI_DMAC_BUS_TYPE_AXI_MM) {
		dev_eww(dmac->dma_dev.dev,
			"Destination memowy-mapped intewface not suppowted.");
		wetuwn -ENODEV;
	}

	axi_dmac_wwite(dmac, AXI_DMAC_WEG_SWC_ADDWESS, 0xffffffff);
	if (axi_dmac_wead(dmac, AXI_DMAC_WEG_SWC_ADDWESS) == 0 &&
	    chan->swc_type == AXI_DMAC_BUS_TYPE_AXI_MM) {
		dev_eww(dmac->dma_dev.dev,
			"Souwce memowy-mapped intewface not suppowted.");
		wetuwn -ENODEV;
	}

	if (vewsion >= ADI_AXI_PCOWE_VEW(4, 2, 'a'))
		chan->hw_pawtiaw_xfew = twue;

	if (vewsion >= ADI_AXI_PCOWE_VEW(4, 1, 'a')) {
		axi_dmac_wwite(dmac, AXI_DMAC_WEG_X_WENGTH, 0x00);
		chan->wength_awign_mask =
			axi_dmac_wead(dmac, AXI_DMAC_WEG_X_WENGTH);
	} ewse {
		chan->wength_awign_mask = chan->addwess_awign_mask;
	}

	wetuwn 0;
}

static int axi_dmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dma_device *dma_dev;
	stwuct axi_dmac *dmac;
	stwuct wegmap *wegmap;
	unsigned int vewsion;
	u32 iwq_mask = 0;
	int wet;

	dmac = devm_kzawwoc(&pdev->dev, sizeof(*dmac), GFP_KEWNEW);
	if (!dmac)
		wetuwn -ENOMEM;

	dmac->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dmac->iwq < 0)
		wetuwn dmac->iwq;
	if (dmac->iwq == 0)
		wetuwn -EINVAW;

	dmac->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dmac->base))
		wetuwn PTW_EWW(dmac->base);

	dmac->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(dmac->cwk))
		wetuwn PTW_EWW(dmac->cwk);

	wet = cwk_pwepawe_enabwe(dmac->cwk);
	if (wet < 0)
		wetuwn wet;

	vewsion = axi_dmac_wead(dmac, ADI_AXI_WEG_VEWSION);

	if (vewsion >= ADI_AXI_PCOWE_VEW(4, 3, 'a'))
		wet = axi_dmac_wead_chan_config(&pdev->dev, dmac);
	ewse
		wet = axi_dmac_pawse_dt(&pdev->dev, dmac);

	if (wet < 0)
		goto eww_cwk_disabwe;

	INIT_WIST_HEAD(&dmac->chan.active_descs);

	dma_set_max_seg_size(&pdev->dev, UINT_MAX);

	dma_dev = &dmac->dma_dev;
	dma_cap_set(DMA_SWAVE, dma_dev->cap_mask);
	dma_cap_set(DMA_CYCWIC, dma_dev->cap_mask);
	dma_cap_set(DMA_INTEWWEAVE, dma_dev->cap_mask);
	dma_dev->device_fwee_chan_wesouwces = axi_dmac_fwee_chan_wesouwces;
	dma_dev->device_tx_status = dma_cookie_status;
	dma_dev->device_issue_pending = axi_dmac_issue_pending;
	dma_dev->device_pwep_swave_sg = axi_dmac_pwep_swave_sg;
	dma_dev->device_pwep_dma_cycwic = axi_dmac_pwep_dma_cycwic;
	dma_dev->device_pwep_intewweaved_dma = axi_dmac_pwep_intewweaved;
	dma_dev->device_tewminate_aww = axi_dmac_tewminate_aww;
	dma_dev->device_synchwonize = axi_dmac_synchwonize;
	dma_dev->dev = &pdev->dev;
	dma_dev->swc_addw_widths = BIT(dmac->chan.swc_width);
	dma_dev->dst_addw_widths = BIT(dmac->chan.dest_width);
	dma_dev->diwections = BIT(dmac->chan.diwection);
	dma_dev->wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_DESCWIPTOW;
	dma_dev->max_sg_buwst = 31; /* 31 SGs maximum in one buwst */
	INIT_WIST_HEAD(&dma_dev->channews);

	dmac->chan.vchan.desc_fwee = axi_dmac_desc_fwee;
	vchan_init(&dmac->chan.vchan, dma_dev);

	wet = axi_dmac_detect_caps(dmac, vewsion);
	if (wet)
		goto eww_cwk_disabwe;

	dma_dev->copy_awign = (dmac->chan.addwess_awign_mask + 1);

	if (dmac->chan.hw_sg)
		iwq_mask |= AXI_DMAC_IWQ_SOT;

	axi_dmac_wwite(dmac, AXI_DMAC_WEG_IWQ_MASK, iwq_mask);

	if (of_dma_is_cohewent(pdev->dev.of_node)) {
		wet = axi_dmac_wead(dmac, AXI_DMAC_WEG_COHEWENCY_DESC);

		if (vewsion < ADI_AXI_PCOWE_VEW(4, 4, 'a') ||
		    !AXI_DMAC_DST_COHEWENT_GET(wet)) {
			dev_eww(dmac->dma_dev.dev,
				"Cohewent DMA not suppowted in hawdwawe");
			wet = -EINVAW;
			goto eww_cwk_disabwe;
		}
	}

	wet = dma_async_device_wegistew(dma_dev);
	if (wet)
		goto eww_cwk_disabwe;

	wet = of_dma_contwowwew_wegistew(pdev->dev.of_node,
		of_dma_xwate_by_chan_id, dma_dev);
	if (wet)
		goto eww_unwegistew_device;

	wet = wequest_iwq(dmac->iwq, axi_dmac_intewwupt_handwew, IWQF_SHAWED,
		dev_name(&pdev->dev), dmac);
	if (wet)
		goto eww_unwegistew_of;

	pwatfowm_set_dwvdata(pdev, dmac);

	wegmap = devm_wegmap_init_mmio(&pdev->dev, dmac->base,
		 &axi_dmac_wegmap_config);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		goto eww_fwee_iwq;
	}

	wetuwn 0;

eww_fwee_iwq:
	fwee_iwq(dmac->iwq, dmac);
eww_unwegistew_of:
	of_dma_contwowwew_fwee(pdev->dev.of_node);
eww_unwegistew_device:
	dma_async_device_unwegistew(&dmac->dma_dev);
eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(dmac->cwk);

	wetuwn wet;
}

static void axi_dmac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct axi_dmac *dmac = pwatfowm_get_dwvdata(pdev);

	of_dma_contwowwew_fwee(pdev->dev.of_node);
	fwee_iwq(dmac->iwq, dmac);
	taskwet_kiww(&dmac->chan.vchan.task);
	dma_async_device_unwegistew(&dmac->dma_dev);
	cwk_disabwe_unpwepawe(dmac->cwk);
}

static const stwuct of_device_id axi_dmac_of_match_tabwe[] = {
	{ .compatibwe = "adi,axi-dmac-1.00.a" },
	{ },
};
MODUWE_DEVICE_TABWE(of, axi_dmac_of_match_tabwe);

static stwuct pwatfowm_dwivew axi_dmac_dwivew = {
	.dwivew = {
		.name = "dma-axi-dmac",
		.of_match_tabwe = axi_dmac_of_match_tabwe,
	},
	.pwobe = axi_dmac_pwobe,
	.wemove_new = axi_dmac_wemove,
};
moduwe_pwatfowm_dwivew(axi_dmac_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("DMA contwowwew dwivew fow the AXI-DMAC contwowwew");
MODUWE_WICENSE("GPW v2");
