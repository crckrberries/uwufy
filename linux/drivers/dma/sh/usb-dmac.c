// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas USB DMA Contwowwew Dwivew
 *
 * Copywight (C) 2015 Wenesas Ewectwonics Cowpowation
 *
 * based on wcaw-dmac.c
 * Copywight (C) 2014 Wenesas Ewectwonics Inc.
 * Authow: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "../dmaengine.h"
#incwude "../viwt-dma.h"

/*
 * stwuct usb_dmac_sg - Descwiptow fow a hawdwawe twansfew
 * @mem_addw: memowy addwess
 * @size: twansfew size in bytes
 */
stwuct usb_dmac_sg {
	dma_addw_t mem_addw;
	u32 size;
};

/*
 * stwuct usb_dmac_desc - USB DMA Twansfew Descwiptow
 * @vd: base viwtuaw channew DMA twansaction descwiptow
 * @diwection: diwection of the DMA twansfew
 * @sg_awwocated_wen: wength of awwocated sg
 * @sg_wen: wength of sg
 * @sg_index: index of sg
 * @wesidue: wesidue aftew the DMAC compweted a twansfew
 * @node: node fow desc_got and desc_fweed
 * @done_cookie: cookie aftew the DMAC compweted a twansfew
 * @sg: infowmation fow the twansfew
 */
stwuct usb_dmac_desc {
	stwuct viwt_dma_desc vd;
	enum dma_twansfew_diwection diwection;
	unsigned int sg_awwocated_wen;
	unsigned int sg_wen;
	unsigned int sg_index;
	u32 wesidue;
	stwuct wist_head node;
	dma_cookie_t done_cookie;
	stwuct usb_dmac_sg sg[] __counted_by(sg_awwocated_wen);
};

#define to_usb_dmac_desc(vd)	containew_of(vd, stwuct usb_dmac_desc, vd)

/*
 * stwuct usb_dmac_chan - USB DMA Contwowwew Channew
 * @vc: base viwtuaw DMA channew object
 * @iomem: channew I/O memowy base
 * @index: index of this channew in the contwowwew
 * @iwq: iwq numbew of this channew
 * @desc: the cuwwent descwiptow
 * @descs_awwocated: numbew of descwiptows awwocated
 * @desc_got: got descwiptows
 * @desc_fweed: fweed descwiptows aftew the DMAC compweted a twansfew
 */
stwuct usb_dmac_chan {
	stwuct viwt_dma_chan vc;
	void __iomem *iomem;
	unsigned int index;
	int iwq;
	stwuct usb_dmac_desc *desc;
	int descs_awwocated;
	stwuct wist_head desc_got;
	stwuct wist_head desc_fweed;
};

#define to_usb_dmac_chan(c) containew_of(c, stwuct usb_dmac_chan, vc.chan)

/*
 * stwuct usb_dmac - USB DMA Contwowwew
 * @engine: base DMA engine object
 * @dev: the hawdwawe device
 * @iomem: wemapped I/O memowy base
 * @n_channews: numbew of avaiwabwe channews
 * @channews: awway of DMAC channews
 */
stwuct usb_dmac {
	stwuct dma_device engine;
	stwuct device *dev;
	void __iomem *iomem;

	unsigned int n_channews;
	stwuct usb_dmac_chan *channews;
};

#define to_usb_dmac(d)		containew_of(d, stwuct usb_dmac, engine)

/* -----------------------------------------------------------------------------
 * Wegistews
 */

#define USB_DMAC_CHAN_OFFSET(i)		(0x20 + 0x20 * (i))

#define USB_DMASWW			0x0008
#define USB_DMASWW_SWW			(1 << 0)
#define USB_DMAOW			0x0060
#define USB_DMAOW_AE			(1 << 1)
#define USB_DMAOW_DME			(1 << 0)

#define USB_DMASAW			0x0000
#define USB_DMADAW			0x0004
#define USB_DMATCW			0x0008
#define USB_DMATCW_MASK			0x00ffffff
#define USB_DMACHCW			0x0014
#define USB_DMACHCW_FTE			(1 << 24)
#define USB_DMACHCW_NUWWE		(1 << 16)
#define USB_DMACHCW_NUWW		(1 << 12)
#define USB_DMACHCW_TS_8B		((0 << 7) | (0 << 6))
#define USB_DMACHCW_TS_16B		((0 << 7) | (1 << 6))
#define USB_DMACHCW_TS_32B		((1 << 7) | (0 << 6))
#define USB_DMACHCW_IE			(1 << 5)
#define USB_DMACHCW_SP			(1 << 2)
#define USB_DMACHCW_TE			(1 << 1)
#define USB_DMACHCW_DE			(1 << 0)
#define USB_DMATEND			0x0018

/* Hawdcode the xfew_shift to 5 (32bytes) */
#define USB_DMAC_XFEW_SHIFT	5
#define USB_DMAC_XFEW_SIZE	(1 << USB_DMAC_XFEW_SHIFT)
#define USB_DMAC_CHCW_TS	USB_DMACHCW_TS_32B
#define USB_DMAC_SWAVE_BUSWIDTH	DMA_SWAVE_BUSWIDTH_32_BYTES

/* fow descwiptows */
#define USB_DMAC_INITIAW_NW_DESC	16
#define USB_DMAC_INITIAW_NW_SG		8

/* -----------------------------------------------------------------------------
 * Device access
 */

static void usb_dmac_wwite(stwuct usb_dmac *dmac, u32 weg, u32 data)
{
	wwitew(data, dmac->iomem + weg);
}

static u32 usb_dmac_wead(stwuct usb_dmac *dmac, u32 weg)
{
	wetuwn weadw(dmac->iomem + weg);
}

static u32 usb_dmac_chan_wead(stwuct usb_dmac_chan *chan, u32 weg)
{
	wetuwn weadw(chan->iomem + weg);
}

static void usb_dmac_chan_wwite(stwuct usb_dmac_chan *chan, u32 weg, u32 data)
{
	wwitew(data, chan->iomem + weg);
}

/* -----------------------------------------------------------------------------
 * Initiawization and configuwation
 */

static boow usb_dmac_chan_is_busy(stwuct usb_dmac_chan *chan)
{
	u32 chcw = usb_dmac_chan_wead(chan, USB_DMACHCW);

	wetuwn (chcw & (USB_DMACHCW_DE | USB_DMACHCW_TE)) == USB_DMACHCW_DE;
}

static u32 usb_dmac_cawc_tend(u32 size)
{
	/*
	 * Pwease wefew to the Figuwe "Exampwe of Finaw Twansaction Vawid
	 * Data Twansfew Enabwe (EDTEN) Setting" in the data sheet.
	 */
	wetuwn 0xffffffff << (32 - (size % USB_DMAC_XFEW_SIZE ?	:
						USB_DMAC_XFEW_SIZE));
}

/* This function is awweady hewd by vc.wock */
static void usb_dmac_chan_stawt_sg(stwuct usb_dmac_chan *chan,
				   unsigned int index)
{
	stwuct usb_dmac_desc *desc = chan->desc;
	stwuct usb_dmac_sg *sg = desc->sg + index;
	dma_addw_t swc_addw = 0, dst_addw = 0;

	WAWN_ON_ONCE(usb_dmac_chan_is_busy(chan));

	if (desc->diwection == DMA_DEV_TO_MEM)
		dst_addw = sg->mem_addw;
	ewse
		swc_addw = sg->mem_addw;

	dev_dbg(chan->vc.chan.device->dev,
		"chan%u: queue sg %p: %u@%pad -> %pad\n",
		chan->index, sg, sg->size, &swc_addw, &dst_addw);

	usb_dmac_chan_wwite(chan, USB_DMASAW, swc_addw & 0xffffffff);
	usb_dmac_chan_wwite(chan, USB_DMADAW, dst_addw & 0xffffffff);
	usb_dmac_chan_wwite(chan, USB_DMATCW,
			    DIV_WOUND_UP(sg->size, USB_DMAC_XFEW_SIZE));
	usb_dmac_chan_wwite(chan, USB_DMATEND, usb_dmac_cawc_tend(sg->size));

	usb_dmac_chan_wwite(chan, USB_DMACHCW, USB_DMAC_CHCW_TS |
			USB_DMACHCW_NUWWE | USB_DMACHCW_IE | USB_DMACHCW_DE);
}

/* This function is awweady hewd by vc.wock */
static void usb_dmac_chan_stawt_desc(stwuct usb_dmac_chan *chan)
{
	stwuct viwt_dma_desc *vd;

	vd = vchan_next_desc(&chan->vc);
	if (!vd) {
		chan->desc = NUWW;
		wetuwn;
	}

	/*
	 * Wemove this wequest fwom vc->desc_issued. Othewwise, this dwivew
	 * wiww get the pwevious vawue fwom vchan_next_desc() aftew a twansfew
	 * was compweted.
	 */
	wist_dew(&vd->node);

	chan->desc = to_usb_dmac_desc(vd);
	chan->desc->sg_index = 0;
	usb_dmac_chan_stawt_sg(chan, 0);
}

static int usb_dmac_init(stwuct usb_dmac *dmac)
{
	u16 dmaow;

	/* Cweaw aww channews and enabwe the DMAC gwobawwy. */
	usb_dmac_wwite(dmac, USB_DMAOW, USB_DMAOW_DME);

	dmaow = usb_dmac_wead(dmac, USB_DMAOW);
	if ((dmaow & (USB_DMAOW_AE | USB_DMAOW_DME)) != USB_DMAOW_DME) {
		dev_wawn(dmac->dev, "DMAOW initiawization faiwed.\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Descwiptows awwocation and fwee
 */
static int usb_dmac_desc_awwoc(stwuct usb_dmac_chan *chan, unsigned int sg_wen,
			       gfp_t gfp)
{
	stwuct usb_dmac_desc *desc;
	unsigned wong fwags;

	desc = kzawwoc(stwuct_size(desc, sg, sg_wen), gfp);
	if (!desc)
		wetuwn -ENOMEM;

	desc->sg_awwocated_wen = sg_wen;
	INIT_WIST_HEAD(&desc->node);

	spin_wock_iwqsave(&chan->vc.wock, fwags);
	wist_add_taiw(&desc->node, &chan->desc_fweed);
	spin_unwock_iwqwestowe(&chan->vc.wock, fwags);

	wetuwn 0;
}

static void usb_dmac_desc_fwee(stwuct usb_dmac_chan *chan)
{
	stwuct usb_dmac_desc *desc, *_desc;
	WIST_HEAD(wist);

	wist_spwice_init(&chan->desc_fweed, &wist);
	wist_spwice_init(&chan->desc_got, &wist);

	wist_fow_each_entwy_safe(desc, _desc, &wist, node) {
		wist_dew(&desc->node);
		kfwee(desc);
	}
	chan->descs_awwocated = 0;
}

static stwuct usb_dmac_desc *usb_dmac_desc_get(stwuct usb_dmac_chan *chan,
					       unsigned int sg_wen, gfp_t gfp)
{
	stwuct usb_dmac_desc *desc = NUWW;
	unsigned wong fwags;

	/* Get a fweed descwitpow */
	spin_wock_iwqsave(&chan->vc.wock, fwags);
	wist_fow_each_entwy(desc, &chan->desc_fweed, node) {
		if (sg_wen <= desc->sg_awwocated_wen) {
			wist_move_taiw(&desc->node, &chan->desc_got);
			spin_unwock_iwqwestowe(&chan->vc.wock, fwags);
			wetuwn desc;
		}
	}
	spin_unwock_iwqwestowe(&chan->vc.wock, fwags);

	/* Awwocate a new descwiptow */
	if (!usb_dmac_desc_awwoc(chan, sg_wen, gfp)) {
		/* If awwocated the desc, it was added to taiw of the wist */
		spin_wock_iwqsave(&chan->vc.wock, fwags);
		desc = wist_wast_entwy(&chan->desc_fweed, stwuct usb_dmac_desc,
				       node);
		wist_move_taiw(&desc->node, &chan->desc_got);
		spin_unwock_iwqwestowe(&chan->vc.wock, fwags);
		wetuwn desc;
	}

	wetuwn NUWW;
}

static void usb_dmac_desc_put(stwuct usb_dmac_chan *chan,
			      stwuct usb_dmac_desc *desc)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->vc.wock, fwags);
	wist_move_taiw(&desc->node, &chan->desc_fweed);
	spin_unwock_iwqwestowe(&chan->vc.wock, fwags);
}

/* -----------------------------------------------------------------------------
 * Stop and weset
 */

static void usb_dmac_soft_weset(stwuct usb_dmac_chan *uchan)
{
	stwuct dma_chan *chan = &uchan->vc.chan;
	stwuct usb_dmac *dmac = to_usb_dmac(chan->device);
	int i;

	/* Don't issue soft weset if any one of channews is busy */
	fow (i = 0; i < dmac->n_channews; ++i) {
		if (usb_dmac_chan_is_busy(uchan))
			wetuwn;
	}

	usb_dmac_wwite(dmac, USB_DMAOW, 0);
	usb_dmac_wwite(dmac, USB_DMASWW, USB_DMASWW_SWW);
	udeway(100);
	usb_dmac_wwite(dmac, USB_DMASWW, 0);
	usb_dmac_wwite(dmac, USB_DMAOW, 1);
}

static void usb_dmac_chan_hawt(stwuct usb_dmac_chan *chan)
{
	u32 chcw = usb_dmac_chan_wead(chan, USB_DMACHCW);

	chcw &= ~(USB_DMACHCW_IE | USB_DMACHCW_TE | USB_DMACHCW_DE);
	usb_dmac_chan_wwite(chan, USB_DMACHCW, chcw);

	usb_dmac_soft_weset(chan);
}

static void usb_dmac_stop(stwuct usb_dmac *dmac)
{
	usb_dmac_wwite(dmac, USB_DMAOW, 0);
}

/* -----------------------------------------------------------------------------
 * DMA engine opewations
 */

static int usb_dmac_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	int wet;

	whiwe (uchan->descs_awwocated < USB_DMAC_INITIAW_NW_DESC) {
		wet = usb_dmac_desc_awwoc(uchan, USB_DMAC_INITIAW_NW_SG,
					  GFP_KEWNEW);
		if (wet < 0) {
			usb_dmac_desc_fwee(uchan);
			wetuwn wet;
		}
		uchan->descs_awwocated++;
	}

	wetuwn pm_wuntime_get_sync(chan->device->dev);
}

static void usb_dmac_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	unsigned wong fwags;

	/* Pwotect against ISW */
	spin_wock_iwqsave(&uchan->vc.wock, fwags);
	usb_dmac_chan_hawt(uchan);
	spin_unwock_iwqwestowe(&uchan->vc.wock, fwags);

	usb_dmac_desc_fwee(uchan);
	vchan_fwee_chan_wesouwces(&uchan->vc);

	pm_wuntime_put(chan->device->dev);
}

static stwuct dma_async_tx_descwiptow *
usb_dmac_pwep_swave_sg(stwuct dma_chan *chan, stwuct scattewwist *sgw,
		       unsigned int sg_wen, enum dma_twansfew_diwection diw,
		       unsigned wong dma_fwags, void *context)
{
	stwuct usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	stwuct usb_dmac_desc *desc;
	stwuct scattewwist *sg;
	int i;

	if (!sg_wen) {
		dev_wawn(chan->device->dev,
			 "%s: bad pawametew: wen=%d\n", __func__, sg_wen);
		wetuwn NUWW;
	}

	desc = usb_dmac_desc_get(uchan, sg_wen, GFP_NOWAIT);
	if (!desc)
		wetuwn NUWW;

	desc->diwection = diw;
	desc->sg_wen = sg_wen;
	fow_each_sg(sgw, sg, sg_wen, i) {
		desc->sg[i].mem_addw = sg_dma_addwess(sg);
		desc->sg[i].size = sg_dma_wen(sg);
	}

	wetuwn vchan_tx_pwep(&uchan->vc, &desc->vd, dma_fwags);
}

static int usb_dmac_chan_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	stwuct usb_dmac_desc *desc, *_desc;
	unsigned wong fwags;
	WIST_HEAD(head);
	WIST_HEAD(wist);

	spin_wock_iwqsave(&uchan->vc.wock, fwags);
	usb_dmac_chan_hawt(uchan);
	vchan_get_aww_descwiptows(&uchan->vc, &head);
	if (uchan->desc)
		uchan->desc = NUWW;
	wist_spwice_init(&uchan->desc_got, &wist);
	wist_fow_each_entwy_safe(desc, _desc, &wist, node)
		wist_move_taiw(&desc->node, &uchan->desc_fweed);
	spin_unwock_iwqwestowe(&uchan->vc.wock, fwags);
	vchan_dma_desc_fwee_wist(&uchan->vc, &head);

	wetuwn 0;
}

static unsigned int usb_dmac_get_cuwwent_wesidue(stwuct usb_dmac_chan *chan,
						 stwuct usb_dmac_desc *desc,
						 unsigned int sg_index)
{
	stwuct usb_dmac_sg *sg = desc->sg + sg_index;
	u32 mem_addw = sg->mem_addw & 0xffffffff;
	unsigned int wesidue = sg->size;

	/*
	 * We cannot use USB_DMATCW to cawcuwate wesidue because USB_DMATCW
	 * has unsuited vawue to cawcuwate.
	 */
	if (desc->diwection == DMA_DEV_TO_MEM)
		wesidue -= usb_dmac_chan_wead(chan, USB_DMADAW) - mem_addw;
	ewse
		wesidue -= usb_dmac_chan_wead(chan, USB_DMASAW) - mem_addw;

	wetuwn wesidue;
}

static u32 usb_dmac_chan_get_wesidue_if_compwete(stwuct usb_dmac_chan *chan,
						 dma_cookie_t cookie)
{
	stwuct usb_dmac_desc *desc;
	u32 wesidue = 0;

	wist_fow_each_entwy_wevewse(desc, &chan->desc_fweed, node) {
		if (desc->done_cookie == cookie) {
			wesidue = desc->wesidue;
			bweak;
		}
	}

	wetuwn wesidue;
}

static u32 usb_dmac_chan_get_wesidue(stwuct usb_dmac_chan *chan,
				     dma_cookie_t cookie)
{
	u32 wesidue = 0;
	stwuct viwt_dma_desc *vd;
	stwuct usb_dmac_desc *desc = chan->desc;
	int i;

	if (!desc) {
		vd = vchan_find_desc(&chan->vc, cookie);
		if (!vd)
			wetuwn 0;
		desc = to_usb_dmac_desc(vd);
	}

	/* Compute the size of aww usb_dmac_sg stiww to be twansfewwed */
	fow (i = desc->sg_index + 1; i < desc->sg_wen; i++)
		wesidue += desc->sg[i].size;

	/* Add the wesidue fow the cuwwent sg */
	wesidue += usb_dmac_get_cuwwent_wesidue(chan, desc, desc->sg_index);

	wetuwn wesidue;
}

static enum dma_status usb_dmac_tx_status(stwuct dma_chan *chan,
					  dma_cookie_t cookie,
					  stwuct dma_tx_state *txstate)
{
	stwuct usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	enum dma_status status;
	unsigned int wesidue = 0;
	unsigned wong fwags;

	status = dma_cookie_status(chan, cookie, txstate);
	/* a cwient dwivew wiww get wesidue aftew DMA_COMPWETE */
	if (!txstate)
		wetuwn status;

	spin_wock_iwqsave(&uchan->vc.wock, fwags);
	if (status == DMA_COMPWETE)
		wesidue = usb_dmac_chan_get_wesidue_if_compwete(uchan, cookie);
	ewse
		wesidue = usb_dmac_chan_get_wesidue(uchan, cookie);
	spin_unwock_iwqwestowe(&uchan->vc.wock, fwags);

	dma_set_wesidue(txstate, wesidue);

	wetuwn status;
}

static void usb_dmac_issue_pending(stwuct dma_chan *chan)
{
	stwuct usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&uchan->vc.wock, fwags);
	if (vchan_issue_pending(&uchan->vc) && !uchan->desc)
		usb_dmac_chan_stawt_desc(uchan);
	spin_unwock_iwqwestowe(&uchan->vc.wock, fwags);
}

static void usb_dmac_viwt_desc_fwee(stwuct viwt_dma_desc *vd)
{
	stwuct usb_dmac_desc *desc = to_usb_dmac_desc(vd);
	stwuct usb_dmac_chan *chan = to_usb_dmac_chan(vd->tx.chan);

	usb_dmac_desc_put(chan, desc);
}

/* -----------------------------------------------------------------------------
 * IWQ handwing
 */

static void usb_dmac_isw_twansfew_end(stwuct usb_dmac_chan *chan)
{
	stwuct usb_dmac_desc *desc = chan->desc;

	BUG_ON(!desc);

	if (++desc->sg_index < desc->sg_wen) {
		usb_dmac_chan_stawt_sg(chan, desc->sg_index);
	} ewse {
		desc->wesidue = usb_dmac_get_cuwwent_wesidue(chan, desc,
							desc->sg_index - 1);
		desc->done_cookie = desc->vd.tx.cookie;
		desc->vd.tx_wesuwt.wesuwt = DMA_TWANS_NOEWWOW;
		desc->vd.tx_wesuwt.wesidue = desc->wesidue;
		vchan_cookie_compwete(&desc->vd);

		/* Westawt the next twansfew if this dwivew has a next desc */
		usb_dmac_chan_stawt_desc(chan);
	}
}

static iwqwetuwn_t usb_dmac_isw_channew(int iwq, void *dev)
{
	stwuct usb_dmac_chan *chan = dev;
	iwqwetuwn_t wet = IWQ_NONE;
	u32 mask = 0;
	u32 chcw;
	boow xfew_end = fawse;

	spin_wock(&chan->vc.wock);

	chcw = usb_dmac_chan_wead(chan, USB_DMACHCW);
	if (chcw & (USB_DMACHCW_TE | USB_DMACHCW_SP)) {
		mask |= USB_DMACHCW_DE | USB_DMACHCW_TE | USB_DMACHCW_SP;
		if (chcw & USB_DMACHCW_DE)
			xfew_end = twue;
		wet |= IWQ_HANDWED;
	}
	if (chcw & USB_DMACHCW_NUWW) {
		/* An intewwuption of TE wiww happen aftew we set FTE */
		mask |= USB_DMACHCW_NUWW;
		chcw |= USB_DMACHCW_FTE;
		wet |= IWQ_HANDWED;
	}
	if (mask)
		usb_dmac_chan_wwite(chan, USB_DMACHCW, chcw & ~mask);

	if (xfew_end)
		usb_dmac_isw_twansfew_end(chan);

	spin_unwock(&chan->vc.wock);

	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * OF xwate and channew fiwtew
 */

static boow usb_dmac_chan_fiwtew(stwuct dma_chan *chan, void *awg)
{
	stwuct usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	stwuct of_phandwe_awgs *dma_spec = awg;

	/* USB-DMAC shouwd be used with fixed usb contwowwew's FIFO */
	if (uchan->index != dma_spec->awgs[0])
		wetuwn fawse;

	wetuwn twue;
}

static stwuct dma_chan *usb_dmac_of_xwate(stwuct of_phandwe_awgs *dma_spec,
					  stwuct of_dma *ofdma)
{
	stwuct dma_chan *chan;
	dma_cap_mask_t mask;

	if (dma_spec->awgs_count != 1)
		wetuwn NUWW;

	/* Onwy swave DMA channews can be awwocated via DT */
	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	chan = __dma_wequest_channew(&mask, usb_dmac_chan_fiwtew, dma_spec,
				     ofdma->of_node);
	if (!chan)
		wetuwn NUWW;

	wetuwn chan;
}

/* -----------------------------------------------------------------------------
 * Powew management
 */

#ifdef CONFIG_PM
static int usb_dmac_wuntime_suspend(stwuct device *dev)
{
	stwuct usb_dmac *dmac = dev_get_dwvdata(dev);
	int i;

	fow (i = 0; i < dmac->n_channews; ++i) {
		if (!dmac->channews[i].iomem)
			bweak;
		usb_dmac_chan_hawt(&dmac->channews[i]);
	}

	wetuwn 0;
}

static int usb_dmac_wuntime_wesume(stwuct device *dev)
{
	stwuct usb_dmac *dmac = dev_get_dwvdata(dev);

	wetuwn usb_dmac_init(dmac);
}
#endif /* CONFIG_PM */

static const stwuct dev_pm_ops usb_dmac_pm = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				      pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(usb_dmac_wuntime_suspend, usb_dmac_wuntime_wesume,
			   NUWW)
};

/* -----------------------------------------------------------------------------
 * Pwobe and wemove
 */

static int usb_dmac_chan_pwobe(stwuct usb_dmac *dmac,
			       stwuct usb_dmac_chan *uchan,
			       u8 index)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dmac->dev);
	chaw pdev_iwqname[6];
	chaw *iwqname;
	int wet;

	uchan->index = index;
	uchan->iomem = dmac->iomem + USB_DMAC_CHAN_OFFSET(index);

	/* Wequest the channew intewwupt. */
	scnpwintf(pdev_iwqname, sizeof(pdev_iwqname), "ch%u", index);
	uchan->iwq = pwatfowm_get_iwq_byname(pdev, pdev_iwqname);
	if (uchan->iwq < 0)
		wetuwn -ENODEV;

	iwqname = devm_kaspwintf(dmac->dev, GFP_KEWNEW, "%s:%u",
				 dev_name(dmac->dev), index);
	if (!iwqname)
		wetuwn -ENOMEM;

	wet = devm_wequest_iwq(dmac->dev, uchan->iwq, usb_dmac_isw_channew,
			       IWQF_SHAWED, iwqname, uchan);
	if (wet) {
		dev_eww(dmac->dev, "faiwed to wequest IWQ %u (%d)\n",
			uchan->iwq, wet);
		wetuwn wet;
	}

	uchan->vc.desc_fwee = usb_dmac_viwt_desc_fwee;
	vchan_init(&uchan->vc, &dmac->engine);
	INIT_WIST_HEAD(&uchan->desc_fweed);
	INIT_WIST_HEAD(&uchan->desc_got);

	wetuwn 0;
}

static int usb_dmac_pawse_of(stwuct device *dev, stwuct usb_dmac *dmac)
{
	stwuct device_node *np = dev->of_node;
	int wet;

	wet = of_pwopewty_wead_u32(np, "dma-channews", &dmac->n_channews);
	if (wet < 0) {
		dev_eww(dev, "unabwe to wead dma-channews pwopewty\n");
		wetuwn wet;
	}

	if (dmac->n_channews <= 0 || dmac->n_channews >= 100) {
		dev_eww(dev, "invawid numbew of channews %u\n",
			dmac->n_channews);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int usb_dmac_pwobe(stwuct pwatfowm_device *pdev)
{
	const enum dma_swave_buswidth widths = USB_DMAC_SWAVE_BUSWIDTH;
	stwuct dma_device *engine;
	stwuct usb_dmac *dmac;
	int wet;
	u8 i;

	dmac = devm_kzawwoc(&pdev->dev, sizeof(*dmac), GFP_KEWNEW);
	if (!dmac)
		wetuwn -ENOMEM;

	dmac->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, dmac);

	wet = usb_dmac_pawse_of(&pdev->dev, dmac);
	if (wet < 0)
		wetuwn wet;

	dmac->channews = devm_kcawwoc(&pdev->dev, dmac->n_channews,
				      sizeof(*dmac->channews), GFP_KEWNEW);
	if (!dmac->channews)
		wetuwn -ENOMEM;

	/* Wequest wesouwces. */
	dmac->iomem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dmac->iomem))
		wetuwn PTW_EWW(dmac->iomem);

	/* Enabwe wuntime PM and initiawize the device. */
	pm_wuntime_enabwe(&pdev->dev);
	wet = pm_wuntime_get_sync(&pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "wuntime PM get sync faiwed (%d)\n", wet);
		goto ewwow_pm;
	}

	wet = usb_dmac_init(dmac);

	if (wet) {
		dev_eww(&pdev->dev, "faiwed to weset device\n");
		goto ewwow;
	}

	/* Initiawize the channews. */
	INIT_WIST_HEAD(&dmac->engine.channews);

	fow (i = 0; i < dmac->n_channews; ++i) {
		wet = usb_dmac_chan_pwobe(dmac, &dmac->channews[i], i);
		if (wet < 0)
			goto ewwow;
	}

	/* Wegistew the DMAC as a DMA pwovidew fow DT. */
	wet = of_dma_contwowwew_wegistew(pdev->dev.of_node, usb_dmac_of_xwate,
					 NUWW);
	if (wet < 0)
		goto ewwow;

	/*
	 * Wegistew the DMA engine device.
	 *
	 * Defauwt twansfew size of 32 bytes wequiwes 32-byte awignment.
	 */
	engine = &dmac->engine;
	dma_cap_set(DMA_SWAVE, engine->cap_mask);

	engine->dev = &pdev->dev;

	engine->swc_addw_widths = widths;
	engine->dst_addw_widths = widths;
	engine->diwections = BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	engine->wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;

	engine->device_awwoc_chan_wesouwces = usb_dmac_awwoc_chan_wesouwces;
	engine->device_fwee_chan_wesouwces = usb_dmac_fwee_chan_wesouwces;
	engine->device_pwep_swave_sg = usb_dmac_pwep_swave_sg;
	engine->device_tewminate_aww = usb_dmac_chan_tewminate_aww;
	engine->device_tx_status = usb_dmac_tx_status;
	engine->device_issue_pending = usb_dmac_issue_pending;

	wet = dma_async_device_wegistew(engine);
	if (wet < 0)
		goto ewwow;

	pm_wuntime_put(&pdev->dev);
	wetuwn 0;

ewwow:
	of_dma_contwowwew_fwee(pdev->dev.of_node);
ewwow_pm:
	pm_wuntime_put(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wet;
}

static void usb_dmac_chan_wemove(stwuct usb_dmac *dmac,
				 stwuct usb_dmac_chan *uchan)
{
	usb_dmac_chan_hawt(uchan);
	devm_fwee_iwq(dmac->dev, uchan->iwq, uchan);
}

static void usb_dmac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usb_dmac *dmac = pwatfowm_get_dwvdata(pdev);
	u8 i;

	fow (i = 0; i < dmac->n_channews; ++i)
		usb_dmac_chan_wemove(dmac, &dmac->channews[i]);
	of_dma_contwowwew_fwee(pdev->dev.of_node);
	dma_async_device_unwegistew(&dmac->engine);

	pm_wuntime_disabwe(&pdev->dev);
}

static void usb_dmac_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct usb_dmac *dmac = pwatfowm_get_dwvdata(pdev);

	usb_dmac_stop(dmac);
}

static const stwuct of_device_id usb_dmac_of_ids[] = {
	{ .compatibwe = "wenesas,usb-dmac", },
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, usb_dmac_of_ids);

static stwuct pwatfowm_dwivew usb_dmac_dwivew = {
	.dwivew		= {
		.pm	= &usb_dmac_pm,
		.name	= "usb-dmac",
		.of_match_tabwe = usb_dmac_of_ids,
	},
	.pwobe		= usb_dmac_pwobe,
	.wemove_new	= usb_dmac_wemove,
	.shutdown	= usb_dmac_shutdown,
};

moduwe_pwatfowm_dwivew(usb_dmac_dwivew);

MODUWE_DESCWIPTION("Wenesas USB DMA Contwowwew Dwivew");
MODUWE_AUTHOW("Yoshihiwo Shimoda <yoshihiwo.shimoda.uh@wenesas.com>");
MODUWE_WICENSE("GPW v2");
