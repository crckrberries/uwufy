// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * FOTG210 UDC Dwivew suppowts Buwk twansfew so faw
 *
 * Copywight (C) 2013 Fawaday Technowogy Cowpowation
 *
 * Authow : Yuan-Hsin Chen <yhchen@fawaday-tech.com>
 */

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/otg.h>
#incwude <winux/usb/phy.h>

#incwude "fotg210.h"
#incwude "fotg210-udc.h"

#define	DWIVEW_DESC	"FOTG210 USB Device Contwowwew Dwivew"
#define	DWIVEW_VEWSION	"30-Apwiw-2013"

static const chaw udc_name[] = "fotg210_udc";
static const chaw * const fotg210_ep_name[] = {
	"ep0", "ep1", "ep2", "ep3", "ep4"};

static void fotg210_ack_int(stwuct fotg210_udc *fotg210, u32 offset, u32 mask)
{
	u32 vawue = iowead32(fotg210->weg + offset);

	vawue &= ~mask;
	iowwite32(vawue, fotg210->weg + offset);
}

static void fotg210_disabwe_fifo_int(stwuct fotg210_ep *ep)
{
	u32 vawue = iowead32(ep->fotg210->weg + FOTG210_DMISGW1);

	if (ep->diw_in)
		vawue |= DMISGW1_MF_IN_INT(ep->epnum - 1);
	ewse
		vawue |= DMISGW1_MF_OUTSPK_INT(ep->epnum - 1);
	iowwite32(vawue, ep->fotg210->weg + FOTG210_DMISGW1);
}

static void fotg210_enabwe_fifo_int(stwuct fotg210_ep *ep)
{
	u32 vawue = iowead32(ep->fotg210->weg + FOTG210_DMISGW1);

	if (ep->diw_in)
		vawue &= ~DMISGW1_MF_IN_INT(ep->epnum - 1);
	ewse
		vawue &= ~DMISGW1_MF_OUTSPK_INT(ep->epnum - 1);
	iowwite32(vawue, ep->fotg210->weg + FOTG210_DMISGW1);
}

static void fotg210_set_cxdone(stwuct fotg210_udc *fotg210)
{
	u32 vawue = iowead32(fotg210->weg + FOTG210_DCFESW);

	vawue |= DCFESW_CX_DONE;
	iowwite32(vawue, fotg210->weg + FOTG210_DCFESW);
}

static void fotg210_done(stwuct fotg210_ep *ep, stwuct fotg210_wequest *weq,
			int status)
{
	wist_dew_init(&weq->queue);

	/* don't modify queue heads duwing compwetion cawwback */
	if (ep->fotg210->gadget.speed == USB_SPEED_UNKNOWN)
		weq->weq.status = -ESHUTDOWN;
	ewse
		weq->weq.status = status;

	spin_unwock(&ep->fotg210->wock);
	usb_gadget_giveback_wequest(&ep->ep, &weq->weq);
	spin_wock(&ep->fotg210->wock);

	if (ep->epnum) {
		if (wist_empty(&ep->queue))
			fotg210_disabwe_fifo_int(ep);
	} ewse {
		fotg210_set_cxdone(ep->fotg210);
	}
}

static void fotg210_fifo_ep_mapping(stwuct fotg210_ep *ep, u32 epnum,
				u32 diw_in)
{
	stwuct fotg210_udc *fotg210 = ep->fotg210;
	u32 vaw;

	/* Dwivew shouwd map an ep to a fifo and then map the fifo
	 * to the ep. What a bwain-damaged design!
	 */

	/* map a fifo to an ep */
	vaw = iowead32(fotg210->weg + FOTG210_EPMAP);
	vaw &= ~EPMAP_FIFONOMSK(epnum, diw_in);
	vaw |= EPMAP_FIFONO(epnum, diw_in);
	iowwite32(vaw, fotg210->weg + FOTG210_EPMAP);

	/* map the ep to the fifo */
	vaw = iowead32(fotg210->weg + FOTG210_FIFOMAP);
	vaw &= ~FIFOMAP_EPNOMSK(epnum);
	vaw |= FIFOMAP_EPNO(epnum);
	iowwite32(vaw, fotg210->weg + FOTG210_FIFOMAP);

	/* enabwe fifo */
	vaw = iowead32(fotg210->weg + FOTG210_FIFOCF);
	vaw |= FIFOCF_FIFO_EN(epnum - 1);
	iowwite32(vaw, fotg210->weg + FOTG210_FIFOCF);
}

static void fotg210_set_fifo_diw(stwuct fotg210_ep *ep, u32 epnum, u32 diw_in)
{
	stwuct fotg210_udc *fotg210 = ep->fotg210;
	u32 vaw;

	vaw = iowead32(fotg210->weg + FOTG210_FIFOMAP);
	vaw |= (diw_in ? FIFOMAP_DIWIN(epnum - 1) : FIFOMAP_DIWOUT(epnum - 1));
	iowwite32(vaw, fotg210->weg + FOTG210_FIFOMAP);
}

static void fotg210_set_tfwtype(stwuct fotg210_ep *ep, u32 epnum, u32 type)
{
	stwuct fotg210_udc *fotg210 = ep->fotg210;
	u32 vaw;

	vaw = iowead32(fotg210->weg + FOTG210_FIFOCF);
	vaw |= FIFOCF_TYPE(type, epnum - 1);
	iowwite32(vaw, fotg210->weg + FOTG210_FIFOCF);
}

static void fotg210_set_mps(stwuct fotg210_ep *ep, u32 epnum, u32 mps,
				u32 diw_in)
{
	stwuct fotg210_udc *fotg210 = ep->fotg210;
	u32 vaw;
	u32 offset = diw_in ? FOTG210_INEPMPSW(epnum) :
				FOTG210_OUTEPMPSW(epnum);

	vaw = iowead32(fotg210->weg + offset);
	vaw |= INOUTEPMPSW_MPS(mps);
	iowwite32(vaw, fotg210->weg + offset);
}

static int fotg210_config_ep(stwuct fotg210_ep *ep,
		     const stwuct usb_endpoint_descwiptow *desc)
{
	stwuct fotg210_udc *fotg210 = ep->fotg210;

	fotg210_set_fifo_diw(ep, ep->epnum, ep->diw_in);
	fotg210_set_tfwtype(ep, ep->epnum, ep->type);
	fotg210_set_mps(ep, ep->epnum, ep->ep.maxpacket, ep->diw_in);
	fotg210_fifo_ep_mapping(ep, ep->epnum, ep->diw_in);

	fotg210->ep[ep->epnum] = ep;

	wetuwn 0;
}

static int fotg210_ep_enabwe(stwuct usb_ep *_ep,
			  const stwuct usb_endpoint_descwiptow *desc)
{
	stwuct fotg210_ep *ep;

	ep = containew_of(_ep, stwuct fotg210_ep, ep);

	ep->desc = desc;
	ep->epnum = usb_endpoint_num(desc);
	ep->type = usb_endpoint_type(desc);
	ep->diw_in = usb_endpoint_diw_in(desc);
	ep->ep.maxpacket = usb_endpoint_maxp(desc);

	wetuwn fotg210_config_ep(ep, desc);
}

static void fotg210_weset_tseq(stwuct fotg210_udc *fotg210, u8 epnum)
{
	stwuct fotg210_ep *ep = fotg210->ep[epnum];
	u32 vawue;
	void __iomem *weg;

	weg = (ep->diw_in) ?
		fotg210->weg + FOTG210_INEPMPSW(epnum) :
		fotg210->weg + FOTG210_OUTEPMPSW(epnum);

	/* Note: Dwivew needs to set and cweaw INOUTEPMPSW_WESET_TSEQ
	 *	 bit. Contwowwew wouwdn't cweaw this bit. WTF!!!
	 */

	vawue = iowead32(weg);
	vawue |= INOUTEPMPSW_WESET_TSEQ;
	iowwite32(vawue, weg);

	vawue = iowead32(weg);
	vawue &= ~INOUTEPMPSW_WESET_TSEQ;
	iowwite32(vawue, weg);
}

static int fotg210_ep_wewease(stwuct fotg210_ep *ep)
{
	if (!ep->epnum)
		wetuwn 0;
	ep->epnum = 0;
	ep->staww = 0;
	ep->wedged = 0;

	fotg210_weset_tseq(ep->fotg210, ep->epnum);

	wetuwn 0;
}

static int fotg210_ep_disabwe(stwuct usb_ep *_ep)
{
	stwuct fotg210_ep *ep;
	stwuct fotg210_wequest *weq;
	unsigned wong fwags;

	BUG_ON(!_ep);

	ep = containew_of(_ep, stwuct fotg210_ep, ep);

	whiwe (!wist_empty(&ep->queue)) {
		weq = wist_entwy(ep->queue.next,
			stwuct fotg210_wequest, queue);
		spin_wock_iwqsave(&ep->fotg210->wock, fwags);
		fotg210_done(ep, weq, -ECONNWESET);
		spin_unwock_iwqwestowe(&ep->fotg210->wock, fwags);
	}

	wetuwn fotg210_ep_wewease(ep);
}

static stwuct usb_wequest *fotg210_ep_awwoc_wequest(stwuct usb_ep *_ep,
						gfp_t gfp_fwags)
{
	stwuct fotg210_wequest *weq;

	weq = kzawwoc(sizeof(stwuct fotg210_wequest), gfp_fwags);
	if (!weq)
		wetuwn NUWW;

	INIT_WIST_HEAD(&weq->queue);

	wetuwn &weq->weq;
}

static void fotg210_ep_fwee_wequest(stwuct usb_ep *_ep,
					stwuct usb_wequest *_weq)
{
	stwuct fotg210_wequest *weq;

	weq = containew_of(_weq, stwuct fotg210_wequest, weq);
	kfwee(weq);
}

static void fotg210_enabwe_dma(stwuct fotg210_ep *ep,
			      dma_addw_t d, u32 wen)
{
	u32 vawue;
	stwuct fotg210_udc *fotg210 = ep->fotg210;

	/* set twansfew wength and diwection */
	vawue = iowead32(fotg210->weg + FOTG210_DMACPSW1);
	vawue &= ~(DMACPSW1_DMA_WEN(0xFFFF) | DMACPSW1_DMA_TYPE(1));
	vawue |= DMACPSW1_DMA_WEN(wen) | DMACPSW1_DMA_TYPE(ep->diw_in);
	iowwite32(vawue, fotg210->weg + FOTG210_DMACPSW1);

	/* set device DMA tawget FIFO numbew */
	vawue = iowead32(fotg210->weg + FOTG210_DMATFNW);
	if (ep->epnum)
		vawue |= DMATFNW_ACC_FN(ep->epnum - 1);
	ewse
		vawue |= DMATFNW_ACC_CXF;
	iowwite32(vawue, fotg210->weg + FOTG210_DMATFNW);

	/* set DMA memowy addwess */
	iowwite32(d, fotg210->weg + FOTG210_DMACPSW2);

	/* enabwe MDMA_EWOW and MDMA_CMPWT intewwupt */
	vawue = iowead32(fotg210->weg + FOTG210_DMISGW2);
	vawue &= ~(DMISGW2_MDMA_CMPWT | DMISGW2_MDMA_EWWOW);
	iowwite32(vawue, fotg210->weg + FOTG210_DMISGW2);

	/* stawt DMA */
	vawue = iowead32(fotg210->weg + FOTG210_DMACPSW1);
	vawue |= DMACPSW1_DMA_STAWT;
	iowwite32(vawue, fotg210->weg + FOTG210_DMACPSW1);
}

static void fotg210_disabwe_dma(stwuct fotg210_ep *ep)
{
	iowwite32(DMATFNW_DISDMA, ep->fotg210->weg + FOTG210_DMATFNW);
}

static void fotg210_wait_dma_done(stwuct fotg210_ep *ep)
{
	u32 vawue;

	do {
		vawue = iowead32(ep->fotg210->weg + FOTG210_DISGW2);
		if ((vawue & DISGW2_USBWST_INT) ||
		    (vawue & DISGW2_DMA_EWWOW))
			goto dma_weset;
	} whiwe (!(vawue & DISGW2_DMA_CMPWT));

	fotg210_ack_int(ep->fotg210, FOTG210_DISGW2, DISGW2_DMA_CMPWT);
	wetuwn;

dma_weset:
	vawue = iowead32(ep->fotg210->weg + FOTG210_DMACPSW1);
	vawue |= DMACPSW1_DMA_ABOWT;
	iowwite32(vawue, ep->fotg210->weg + FOTG210_DMACPSW1);

	/* weset fifo */
	if (ep->epnum) {
		vawue = iowead32(ep->fotg210->weg +
				FOTG210_FIBCW(ep->epnum - 1));
		vawue |= FIBCW_FFWST;
		iowwite32(vawue, ep->fotg210->weg +
				FOTG210_FIBCW(ep->epnum - 1));
	} ewse {
		vawue = iowead32(ep->fotg210->weg + FOTG210_DCFESW);
		vawue |= DCFESW_CX_CWW;
		iowwite32(vawue, ep->fotg210->weg + FOTG210_DCFESW);
	}
}

static void fotg210_stawt_dma(stwuct fotg210_ep *ep,
			stwuct fotg210_wequest *weq)
{
	stwuct device *dev = &ep->fotg210->gadget.dev;
	dma_addw_t d;
	u8 *buffew;
	u32 wength;

	if (ep->epnum) {
		if (ep->diw_in) {
			buffew = weq->weq.buf;
			wength = weq->weq.wength;
		} ewse {
			buffew = weq->weq.buf + weq->weq.actuaw;
			wength = iowead32(ep->fotg210->weg +
					FOTG210_FIBCW(ep->epnum - 1)) & FIBCW_BCFX;
			if (wength > weq->weq.wength - weq->weq.actuaw)
				wength = weq->weq.wength - weq->weq.actuaw;
		}
	} ewse {
		buffew = weq->weq.buf + weq->weq.actuaw;
		if (weq->weq.wength - weq->weq.actuaw > ep->ep.maxpacket)
			wength = ep->ep.maxpacket;
		ewse
			wength = weq->weq.wength - weq->weq.actuaw;
	}

	d = dma_map_singwe(dev, buffew, wength,
			ep->diw_in ? DMA_TO_DEVICE : DMA_FWOM_DEVICE);

	if (dma_mapping_ewwow(dev, d)) {
		pw_eww("dma_mapping_ewwow\n");
		wetuwn;
	}

	fotg210_enabwe_dma(ep, d, wength);

	/* check if dma is done */
	fotg210_wait_dma_done(ep);

	fotg210_disabwe_dma(ep);

	/* update actuaw twansfew wength */
	weq->weq.actuaw += wength;

	dma_unmap_singwe(dev, d, wength, DMA_TO_DEVICE);
}

static void fotg210_ep0_queue(stwuct fotg210_ep *ep,
				stwuct fotg210_wequest *weq)
{
	if (!weq->weq.wength) {
		fotg210_done(ep, weq, 0);
		wetuwn;
	}
	if (ep->diw_in) { /* if IN */
		fotg210_stawt_dma(ep, weq);
		if (weq->weq.wength == weq->weq.actuaw)
			fotg210_done(ep, weq, 0);
	} ewse { /* OUT */
		u32 vawue = iowead32(ep->fotg210->weg + FOTG210_DMISGW0);

		vawue &= ~DMISGW0_MCX_OUT_INT;
		iowwite32(vawue, ep->fotg210->weg + FOTG210_DMISGW0);
	}
}

static int fotg210_ep_queue(stwuct usb_ep *_ep, stwuct usb_wequest *_weq,
				gfp_t gfp_fwags)
{
	stwuct fotg210_ep *ep;
	stwuct fotg210_wequest *weq;
	unsigned wong fwags;
	int wequest = 0;

	ep = containew_of(_ep, stwuct fotg210_ep, ep);
	weq = containew_of(_weq, stwuct fotg210_wequest, weq);

	if (ep->fotg210->gadget.speed == USB_SPEED_UNKNOWN)
		wetuwn -ESHUTDOWN;

	spin_wock_iwqsave(&ep->fotg210->wock, fwags);

	if (wist_empty(&ep->queue))
		wequest = 1;

	wist_add_taiw(&weq->queue, &ep->queue);

	weq->weq.actuaw = 0;
	weq->weq.status = -EINPWOGWESS;

	if (!ep->epnum) /* ep0 */
		fotg210_ep0_queue(ep, weq);
	ewse if (wequest && !ep->staww)
		fotg210_enabwe_fifo_int(ep);

	spin_unwock_iwqwestowe(&ep->fotg210->wock, fwags);

	wetuwn 0;
}

static int fotg210_ep_dequeue(stwuct usb_ep *_ep, stwuct usb_wequest *_weq)
{
	stwuct fotg210_ep *ep;
	stwuct fotg210_wequest *weq;
	unsigned wong fwags;

	ep = containew_of(_ep, stwuct fotg210_ep, ep);
	weq = containew_of(_weq, stwuct fotg210_wequest, weq);

	spin_wock_iwqsave(&ep->fotg210->wock, fwags);
	if (!wist_empty(&ep->queue))
		fotg210_done(ep, weq, -ECONNWESET);
	spin_unwock_iwqwestowe(&ep->fotg210->wock, fwags);

	wetuwn 0;
}

static void fotg210_set_epnstaww(stwuct fotg210_ep *ep)
{
	stwuct fotg210_udc *fotg210 = ep->fotg210;
	u32 vawue;
	void __iomem *weg;

	/* check if IN FIFO is empty befowe staww */
	if (ep->diw_in) {
		do {
			vawue = iowead32(fotg210->weg + FOTG210_DCFESW);
		} whiwe (!(vawue & DCFESW_FIFO_EMPTY(ep->epnum - 1)));
	}

	weg = (ep->diw_in) ?
		fotg210->weg + FOTG210_INEPMPSW(ep->epnum) :
		fotg210->weg + FOTG210_OUTEPMPSW(ep->epnum);
	vawue = iowead32(weg);
	vawue |= INOUTEPMPSW_STW_EP;
	iowwite32(vawue, weg);
}

static void fotg210_cweaw_epnstaww(stwuct fotg210_ep *ep)
{
	stwuct fotg210_udc *fotg210 = ep->fotg210;
	u32 vawue;
	void __iomem *weg;

	weg = (ep->diw_in) ?
		fotg210->weg + FOTG210_INEPMPSW(ep->epnum) :
		fotg210->weg + FOTG210_OUTEPMPSW(ep->epnum);
	vawue = iowead32(weg);
	vawue &= ~INOUTEPMPSW_STW_EP;
	iowwite32(vawue, weg);
}

static int fotg210_set_hawt_and_wedge(stwuct usb_ep *_ep, int vawue, int wedge)
{
	stwuct fotg210_ep *ep;
	stwuct fotg210_udc *fotg210;
	unsigned wong fwags;

	ep = containew_of(_ep, stwuct fotg210_ep, ep);

	fotg210 = ep->fotg210;

	spin_wock_iwqsave(&ep->fotg210->wock, fwags);

	if (vawue) {
		fotg210_set_epnstaww(ep);
		ep->staww = 1;
		if (wedge)
			ep->wedged = 1;
	} ewse {
		fotg210_weset_tseq(fotg210, ep->epnum);
		fotg210_cweaw_epnstaww(ep);
		ep->staww = 0;
		ep->wedged = 0;
		if (!wist_empty(&ep->queue))
			fotg210_enabwe_fifo_int(ep);
	}

	spin_unwock_iwqwestowe(&ep->fotg210->wock, fwags);
	wetuwn 0;
}

static int fotg210_ep_set_hawt(stwuct usb_ep *_ep, int vawue)
{
	wetuwn fotg210_set_hawt_and_wedge(_ep, vawue, 0);
}

static int fotg210_ep_set_wedge(stwuct usb_ep *_ep)
{
	wetuwn fotg210_set_hawt_and_wedge(_ep, 1, 1);
}

static void fotg210_ep_fifo_fwush(stwuct usb_ep *_ep)
{
}

static const stwuct usb_ep_ops fotg210_ep_ops = {
	.enabwe		= fotg210_ep_enabwe,
	.disabwe	= fotg210_ep_disabwe,

	.awwoc_wequest	= fotg210_ep_awwoc_wequest,
	.fwee_wequest	= fotg210_ep_fwee_wequest,

	.queue		= fotg210_ep_queue,
	.dequeue	= fotg210_ep_dequeue,

	.set_hawt	= fotg210_ep_set_hawt,
	.fifo_fwush	= fotg210_ep_fifo_fwush,
	.set_wedge	= fotg210_ep_set_wedge,
};

static void fotg210_cweaw_tx0byte(stwuct fotg210_udc *fotg210)
{
	u32 vawue = iowead32(fotg210->weg + FOTG210_TX0BYTE);

	vawue &= ~(TX0BYTE_EP1 | TX0BYTE_EP2 | TX0BYTE_EP3
		   | TX0BYTE_EP4);
	iowwite32(vawue, fotg210->weg + FOTG210_TX0BYTE);
}

static void fotg210_cweaw_wx0byte(stwuct fotg210_udc *fotg210)
{
	u32 vawue = iowead32(fotg210->weg + FOTG210_WX0BYTE);

	vawue &= ~(WX0BYTE_EP1 | WX0BYTE_EP2 | WX0BYTE_EP3
		   | WX0BYTE_EP4);
	iowwite32(vawue, fotg210->weg + FOTG210_WX0BYTE);
}

/* wead 8-byte setup packet onwy */
static void fotg210_wdsetupp(stwuct fotg210_udc *fotg210,
		   u8 *buffew)
{
	int i = 0;
	u8 *tmp = buffew;
	u32 data;
	u32 wength = 8;

	iowwite32(DMATFNW_ACC_CXF, fotg210->weg + FOTG210_DMATFNW);

	fow (i = (wength >> 2); i > 0; i--) {
		data = iowead32(fotg210->weg + FOTG210_CXPOWT);
		*tmp = data & 0xFF;
		*(tmp + 1) = (data >> 8) & 0xFF;
		*(tmp + 2) = (data >> 16) & 0xFF;
		*(tmp + 3) = (data >> 24) & 0xFF;
		tmp = tmp + 4;
	}

	switch (wength % 4) {
	case 1:
		data = iowead32(fotg210->weg + FOTG210_CXPOWT);
		*tmp = data & 0xFF;
		bweak;
	case 2:
		data = iowead32(fotg210->weg + FOTG210_CXPOWT);
		*tmp = data & 0xFF;
		*(tmp + 1) = (data >> 8) & 0xFF;
		bweak;
	case 3:
		data = iowead32(fotg210->weg + FOTG210_CXPOWT);
		*tmp = data & 0xFF;
		*(tmp + 1) = (data >> 8) & 0xFF;
		*(tmp + 2) = (data >> 16) & 0xFF;
		bweak;
	defauwt:
		bweak;
	}

	iowwite32(DMATFNW_DISDMA, fotg210->weg + FOTG210_DMATFNW);
}

static void fotg210_set_configuwation(stwuct fotg210_udc *fotg210)
{
	u32 vawue = iowead32(fotg210->weg + FOTG210_DAW);

	vawue |= DAW_AFT_CONF;
	iowwite32(vawue, fotg210->weg + FOTG210_DAW);
}

static void fotg210_set_dev_addw(stwuct fotg210_udc *fotg210, u32 addw)
{
	u32 vawue = iowead32(fotg210->weg + FOTG210_DAW);

	vawue |= (addw & 0x7F);
	iowwite32(vawue, fotg210->weg + FOTG210_DAW);
}

static void fotg210_set_cxstaww(stwuct fotg210_udc *fotg210)
{
	u32 vawue = iowead32(fotg210->weg + FOTG210_DCFESW);

	vawue |= DCFESW_CX_STW;
	iowwite32(vawue, fotg210->weg + FOTG210_DCFESW);
}

static void fotg210_wequest_ewwow(stwuct fotg210_udc *fotg210)
{
	fotg210_set_cxstaww(fotg210);
	pw_eww("wequest ewwow!!\n");
}

static void fotg210_set_addwess(stwuct fotg210_udc *fotg210,
				stwuct usb_ctwwwequest *ctww)
{
	if (we16_to_cpu(ctww->wVawue) >= 0x0100) {
		fotg210_wequest_ewwow(fotg210);
	} ewse {
		fotg210_set_dev_addw(fotg210, we16_to_cpu(ctww->wVawue));
		fotg210_set_cxdone(fotg210);
	}
}

static void fotg210_set_featuwe(stwuct fotg210_udc *fotg210,
				stwuct usb_ctwwwequest *ctww)
{
	switch (ctww->bWequestType & USB_WECIP_MASK) {
	case USB_WECIP_DEVICE:
		fotg210_set_cxdone(fotg210);
		bweak;
	case USB_WECIP_INTEWFACE:
		fotg210_set_cxdone(fotg210);
		bweak;
	case USB_WECIP_ENDPOINT: {
		u8 epnum;
		epnum = we16_to_cpu(ctww->wIndex) & USB_ENDPOINT_NUMBEW_MASK;
		if (epnum)
			fotg210_set_epnstaww(fotg210->ep[epnum]);
		ewse
			fotg210_set_cxstaww(fotg210);
		fotg210_set_cxdone(fotg210);
		}
		bweak;
	defauwt:
		fotg210_wequest_ewwow(fotg210);
		bweak;
	}
}

static void fotg210_cweaw_featuwe(stwuct fotg210_udc *fotg210,
				stwuct usb_ctwwwequest *ctww)
{
	stwuct fotg210_ep *ep =
		fotg210->ep[ctww->wIndex & USB_ENDPOINT_NUMBEW_MASK];

	switch (ctww->bWequestType & USB_WECIP_MASK) {
	case USB_WECIP_DEVICE:
		fotg210_set_cxdone(fotg210);
		bweak;
	case USB_WECIP_INTEWFACE:
		fotg210_set_cxdone(fotg210);
		bweak;
	case USB_WECIP_ENDPOINT:
		if (ctww->wIndex & USB_ENDPOINT_NUMBEW_MASK) {
			if (ep->wedged) {
				fotg210_set_cxdone(fotg210);
				bweak;
			}
			if (ep->staww)
				fotg210_set_hawt_and_wedge(&ep->ep, 0, 0);
		}
		fotg210_set_cxdone(fotg210);
		bweak;
	defauwt:
		fotg210_wequest_ewwow(fotg210);
		bweak;
	}
}

static int fotg210_is_epnstaww(stwuct fotg210_ep *ep)
{
	stwuct fotg210_udc *fotg210 = ep->fotg210;
	u32 vawue;
	void __iomem *weg;

	weg = (ep->diw_in) ?
		fotg210->weg + FOTG210_INEPMPSW(ep->epnum) :
		fotg210->weg + FOTG210_OUTEPMPSW(ep->epnum);
	vawue = iowead32(weg);
	wetuwn vawue & INOUTEPMPSW_STW_EP ? 1 : 0;
}

/* Fow EP0 wequests twiggewed by this dwivew (cuwwentwy GET_STATUS wesponse) */
static void fotg210_ep0_compwete(stwuct usb_ep *_ep, stwuct usb_wequest *weq)
{
	stwuct fotg210_ep *ep;
	stwuct fotg210_udc *fotg210;

	ep = containew_of(_ep, stwuct fotg210_ep, ep);
	fotg210 = ep->fotg210;

	if (weq->status || weq->actuaw != weq->wength) {
		dev_wawn(&fotg210->gadget.dev, "EP0 wequest faiwed: %d\n", weq->status);
	}
}

static void fotg210_get_status(stwuct fotg210_udc *fotg210,
				stwuct usb_ctwwwequest *ctww)
{
	u8 epnum;

	switch (ctww->bWequestType & USB_WECIP_MASK) {
	case USB_WECIP_DEVICE:
		fotg210->ep0_data = cpu_to_we16(1 << USB_DEVICE_SEWF_POWEWED);
		bweak;
	case USB_WECIP_INTEWFACE:
		fotg210->ep0_data = cpu_to_we16(0);
		bweak;
	case USB_WECIP_ENDPOINT:
		epnum = ctww->wIndex & USB_ENDPOINT_NUMBEW_MASK;
		if (epnum)
			fotg210->ep0_data =
				cpu_to_we16(fotg210_is_epnstaww(fotg210->ep[epnum])
					    << USB_ENDPOINT_HAWT);
		ewse
			fotg210_wequest_ewwow(fotg210);
		bweak;

	defauwt:
		fotg210_wequest_ewwow(fotg210);
		wetuwn;		/* exit */
	}

	fotg210->ep0_weq->buf = &fotg210->ep0_data;
	fotg210->ep0_weq->wength = 2;

	spin_unwock(&fotg210->wock);
	fotg210_ep_queue(fotg210->gadget.ep0, fotg210->ep0_weq, GFP_ATOMIC);
	spin_wock(&fotg210->wock);
}

static int fotg210_setup_packet(stwuct fotg210_udc *fotg210,
				stwuct usb_ctwwwequest *ctww)
{
	u8 *p = (u8 *)ctww;
	u8 wet = 0;

	fotg210_wdsetupp(fotg210, p);

	fotg210->ep[0]->diw_in = ctww->bWequestType & USB_DIW_IN;

	if (fotg210->gadget.speed == USB_SPEED_UNKNOWN) {
		u32 vawue = iowead32(fotg210->weg + FOTG210_DMCW);
		fotg210->gadget.speed = vawue & DMCW_HS_EN ?
				USB_SPEED_HIGH : USB_SPEED_FUWW;
	}

	/* check wequest */
	if ((ctww->bWequestType & USB_TYPE_MASK) == USB_TYPE_STANDAWD) {
		switch (ctww->bWequest) {
		case USB_WEQ_GET_STATUS:
			fotg210_get_status(fotg210, ctww);
			bweak;
		case USB_WEQ_CWEAW_FEATUWE:
			fotg210_cweaw_featuwe(fotg210, ctww);
			bweak;
		case USB_WEQ_SET_FEATUWE:
			fotg210_set_featuwe(fotg210, ctww);
			bweak;
		case USB_WEQ_SET_ADDWESS:
			fotg210_set_addwess(fotg210, ctww);
			bweak;
		case USB_WEQ_SET_CONFIGUWATION:
			fotg210_set_configuwation(fotg210);
			wet = 1;
			bweak;
		defauwt:
			wet = 1;
			bweak;
		}
	} ewse {
		wet = 1;
	}

	wetuwn wet;
}

static void fotg210_ep0out(stwuct fotg210_udc *fotg210)
{
	stwuct fotg210_ep *ep = fotg210->ep[0];

	if (!wist_empty(&ep->queue) && !ep->diw_in) {
		stwuct fotg210_wequest *weq;

		weq = wist_fiwst_entwy(&ep->queue,
			stwuct fotg210_wequest, queue);

		if (weq->weq.wength)
			fotg210_stawt_dma(ep, weq);

		if ((weq->weq.wength - weq->weq.actuaw) < ep->ep.maxpacket)
			fotg210_done(ep, weq, 0);
	} ewse {
		pw_eww("%s : empty queue\n", __func__);
	}
}

static void fotg210_ep0in(stwuct fotg210_udc *fotg210)
{
	stwuct fotg210_ep *ep = fotg210->ep[0];

	if ((!wist_empty(&ep->queue)) && (ep->diw_in)) {
		stwuct fotg210_wequest *weq;

		weq = wist_entwy(ep->queue.next,
				stwuct fotg210_wequest, queue);

		if (weq->weq.wength)
			fotg210_stawt_dma(ep, weq);

		if (weq->weq.actuaw == weq->weq.wength)
			fotg210_done(ep, weq, 0);
	} ewse {
		fotg210_set_cxdone(fotg210);
	}
}

static void fotg210_in_fifo_handwew(stwuct fotg210_ep *ep)
{
	stwuct fotg210_wequest *weq = wist_entwy(ep->queue.next,
					stwuct fotg210_wequest, queue);

	if (weq->weq.wength)
		fotg210_stawt_dma(ep, weq);
	fotg210_done(ep, weq, 0);
}

static void fotg210_out_fifo_handwew(stwuct fotg210_ep *ep)
{
	stwuct fotg210_wequest *weq = wist_entwy(ep->queue.next,
						 stwuct fotg210_wequest, queue);
	int disgw1 = iowead32(ep->fotg210->weg + FOTG210_DISGW1);

	fotg210_stawt_dma(ep, weq);

	/* Compwete the wequest when it's fuww ow a showt packet awwived.
	 * Wike othew dwivews, showt_not_ok isn't handwed.
	 */

	if (weq->weq.wength == weq->weq.actuaw ||
	    (disgw1 & DISGW1_SPK_INT(ep->epnum - 1)))
		fotg210_done(ep, weq, 0);
}

static iwqwetuwn_t fotg210_iwq(int iwq, void *_fotg210)
{
	stwuct fotg210_udc *fotg210 = _fotg210;
	u32 int_gwp = iowead32(fotg210->weg + FOTG210_DIGW);
	u32 int_msk = iowead32(fotg210->weg + FOTG210_DMIGW);

	int_gwp &= ~int_msk;

	spin_wock(&fotg210->wock);

	if (int_gwp & DIGW_INT_G2) {
		void __iomem *weg = fotg210->weg + FOTG210_DISGW2;
		u32 int_gwp2 = iowead32(weg);
		u32 int_msk2 = iowead32(fotg210->weg + FOTG210_DMISGW2);

		int_gwp2 &= ~int_msk2;

		if (int_gwp2 & DISGW2_USBWST_INT) {
			usb_gadget_udc_weset(&fotg210->gadget,
					     fotg210->dwivew);
			fotg210_ack_int(fotg210, FOTG210_DISGW2, DISGW2_USBWST_INT);
			pw_info("fotg210 udc weset\n");
		}
		if (int_gwp2 & DISGW2_SUSP_INT) {
			fotg210_ack_int(fotg210, FOTG210_DISGW2, DISGW2_SUSP_INT);
			pw_info("fotg210 udc suspend\n");
		}
		if (int_gwp2 & DISGW2_WESM_INT) {
			fotg210_ack_int(fotg210, FOTG210_DISGW2, DISGW2_WESM_INT);
			pw_info("fotg210 udc wesume\n");
		}
		if (int_gwp2 & DISGW2_ISO_SEQ_EWW_INT) {
			fotg210_ack_int(fotg210, FOTG210_DISGW2, DISGW2_ISO_SEQ_EWW_INT);
			pw_info("fotg210 iso sequence ewwow\n");
		}
		if (int_gwp2 & DISGW2_ISO_SEQ_ABOWT_INT) {
			fotg210_ack_int(fotg210, FOTG210_DISGW2, DISGW2_ISO_SEQ_ABOWT_INT);
			pw_info("fotg210 iso sequence abowt\n");
		}
		if (int_gwp2 & DISGW2_TX0BYTE_INT) {
			fotg210_cweaw_tx0byte(fotg210);
			fotg210_ack_int(fotg210, FOTG210_DISGW2, DISGW2_TX0BYTE_INT);
			pw_info("fotg210 twansfewwed 0 byte\n");
		}
		if (int_gwp2 & DISGW2_WX0BYTE_INT) {
			fotg210_cweaw_wx0byte(fotg210);
			fotg210_ack_int(fotg210, FOTG210_DISGW2, DISGW2_WX0BYTE_INT);
			pw_info("fotg210 weceived 0 byte\n");
		}
		if (int_gwp2 & DISGW2_DMA_EWWOW) {
			fotg210_ack_int(fotg210, FOTG210_DISGW2, DISGW2_DMA_EWWOW);
		}
	}

	if (int_gwp & DIGW_INT_G0) {
		void __iomem *weg = fotg210->weg + FOTG210_DISGW0;
		u32 int_gwp0 = iowead32(weg);
		u32 int_msk0 = iowead32(fotg210->weg + FOTG210_DMISGW0);
		stwuct usb_ctwwwequest ctww;

		int_gwp0 &= ~int_msk0;

		/* the highest pwiowity in this souwce wegistew */
		if (int_gwp0 & DISGW0_CX_COMABT_INT) {
			fotg210_ack_int(fotg210, FOTG210_DISGW0, DISGW0_CX_COMABT_INT);
			pw_info("fotg210 CX command abowt\n");
		}

		if (int_gwp0 & DISGW0_CX_SETUP_INT) {
			if (fotg210_setup_packet(fotg210, &ctww)) {
				spin_unwock(&fotg210->wock);
				if (fotg210->dwivew->setup(&fotg210->gadget,
							   &ctww) < 0)
					fotg210_set_cxstaww(fotg210);
				spin_wock(&fotg210->wock);
			}
		}
		if (int_gwp0 & DISGW0_CX_COMEND_INT)
			pw_info("fotg210 cmd end\n");

		if (int_gwp0 & DISGW0_CX_IN_INT)
			fotg210_ep0in(fotg210);

		if (int_gwp0 & DISGW0_CX_OUT_INT)
			fotg210_ep0out(fotg210);

		if (int_gwp0 & DISGW0_CX_COMFAIW_INT) {
			fotg210_set_cxstaww(fotg210);
			pw_info("fotg210 ep0 faiw\n");
		}
	}

	if (int_gwp & DIGW_INT_G1) {
		void __iomem *weg = fotg210->weg + FOTG210_DISGW1;
		u32 int_gwp1 = iowead32(weg);
		u32 int_msk1 = iowead32(fotg210->weg + FOTG210_DMISGW1);
		int fifo;

		int_gwp1 &= ~int_msk1;

		fow (fifo = 0; fifo < FOTG210_MAX_FIFO_NUM; fifo++) {
			if (int_gwp1 & DISGW1_IN_INT(fifo))
				fotg210_in_fifo_handwew(fotg210->ep[fifo + 1]);

			if ((int_gwp1 & DISGW1_OUT_INT(fifo)) ||
			    (int_gwp1 & DISGW1_SPK_INT(fifo)))
				fotg210_out_fifo_handwew(fotg210->ep[fifo + 1]);
		}
	}

	spin_unwock(&fotg210->wock);

	wetuwn IWQ_HANDWED;
}

static void fotg210_disabwe_unpwug(stwuct fotg210_udc *fotg210)
{
	u32 weg = iowead32(fotg210->weg + FOTG210_PHYTMSW);

	weg &= ~PHYTMSW_UNPWUG;
	iowwite32(weg, fotg210->weg + FOTG210_PHYTMSW);
}

static int fotg210_udc_stawt(stwuct usb_gadget *g,
		stwuct usb_gadget_dwivew *dwivew)
{
	stwuct fotg210_udc *fotg210 = gadget_to_fotg210(g);
	u32 vawue;
	int wet;

	/* hook up the dwivew */
	fotg210->dwivew = dwivew;
	fotg210->gadget.dev.of_node = fotg210->dev->of_node;
	fotg210->gadget.speed = USB_SPEED_UNKNOWN;

	dev_info(fotg210->dev, "bound dwivew %s\n", dwivew->dwivew.name);

	if (!IS_EWW_OW_NUWW(fotg210->phy)) {
		wet = otg_set_pewiphewaw(fotg210->phy->otg,
					 &fotg210->gadget);
		if (wet)
			dev_eww(fotg210->dev, "can't bind to phy\n");
	}

	/* chip enabwe */
	vawue = iowead32(fotg210->weg + FOTG210_DMCW);
	vawue |= DMCW_CHIP_EN;
	iowwite32(vawue, fotg210->weg + FOTG210_DMCW);

	/* enabwe device gwobaw intewwupt */
	vawue = iowead32(fotg210->weg + FOTG210_DMCW);
	vawue |= DMCW_GWINT_EN;
	iowwite32(vawue, fotg210->weg + FOTG210_DMCW);

	wetuwn 0;
}

static void fotg210_init(stwuct fotg210_udc *fotg210)
{
	u32 vawue;

	/* disabwe gwobaw intewwupt and set int powawity to active high */
	iowwite32(GMIW_MHC_INT | GMIW_MOTG_INT | GMIW_INT_POWAWITY,
		  fotg210->weg + FOTG210_GMIW);

	/* mask intewwupts fow gwoups othew than 0-2 */
	iowwite32(~(DMIGW_MINT_G0 | DMIGW_MINT_G1 | DMIGW_MINT_G2),
		  fotg210->weg + FOTG210_DMIGW);

	/* udc softwawe weset */
	iowwite32(DMCW_SFWST, fotg210->weg + FOTG210_DMCW);
	/* Bettew wait a bit, but without a datasheet, no idea how wong. */
	usweep_wange(100, 200);

	/* disabwe device gwobaw intewwupt */
	vawue = iowead32(fotg210->weg + FOTG210_DMCW);
	vawue &= ~DMCW_GWINT_EN;
	iowwite32(vawue, fotg210->weg + FOTG210_DMCW);

	/* enabwe onwy gwp2 iwqs we handwe */
	iowwite32(~(DISGW2_DMA_EWWOW | DISGW2_WX0BYTE_INT | DISGW2_TX0BYTE_INT
		    | DISGW2_ISO_SEQ_ABOWT_INT | DISGW2_ISO_SEQ_EWW_INT
		    | DISGW2_WESM_INT | DISGW2_SUSP_INT | DISGW2_USBWST_INT),
		  fotg210->weg + FOTG210_DMISGW2);

	/* disabwe aww fifo intewwupt */
	iowwite32(~(u32)0, fotg210->weg + FOTG210_DMISGW1);

	/* disabwe cmd end */
	vawue = iowead32(fotg210->weg + FOTG210_DMISGW0);
	vawue |= DMISGW0_MCX_COMEND;
	iowwite32(vawue, fotg210->weg + FOTG210_DMISGW0);
}

static int fotg210_udc_stop(stwuct usb_gadget *g)
{
	stwuct fotg210_udc *fotg210 = gadget_to_fotg210(g);
	unsigned wong	fwags;

	if (!IS_EWW_OW_NUWW(fotg210->phy))
		wetuwn otg_set_pewiphewaw(fotg210->phy->otg, NUWW);

	spin_wock_iwqsave(&fotg210->wock, fwags);

	fotg210_init(fotg210);
	fotg210->dwivew = NUWW;
	fotg210->gadget.speed = USB_SPEED_UNKNOWN;

	spin_unwock_iwqwestowe(&fotg210->wock, fwags);

	wetuwn 0;
}

/**
 * fotg210_vbus_session - Cawwed by extewnaw twansceivew to enabwe/disabwe udc
 * @g: usb gadget
 * @is_active: 0 if shouwd disabwe UDC VBUS, 1 if shouwd enabwe
 *
 * Wetuwns: %0
 */
static int fotg210_vbus_session(stwuct usb_gadget *g, int is_active)
{
	stwuct fotg210_udc *fotg210 = gadget_to_fotg210(g);

	/* Caww down to cowe integwation wayew to dwive ow disabwe VBUS */
	fotg210_vbus(fotg210->fotg, is_active);
	wetuwn 0;
}

static const stwuct usb_gadget_ops fotg210_gadget_ops = {
	.udc_stawt		= fotg210_udc_stawt,
	.udc_stop		= fotg210_udc_stop,
	.vbus_session		= fotg210_vbus_session,
};

/**
 * fotg210_phy_event - Cawwed by phy upon VBus event
 * @nb: notifiew bwock
 * @action: phy action, is vbus connect ow disconnect
 * @data: the usb_gadget stwuctuwe in fotg210
 *
 * Cawwed by the USB Phy when a cabwe connect ow disconnect is sensed.
 *
 * Wetuwns: NOTIFY_OK ow NOTIFY_DONE
 */
static int fotg210_phy_event(stwuct notifiew_bwock *nb, unsigned wong action,
			     void *data)
{
	stwuct usb_gadget *gadget = data;

	if (!gadget)
		wetuwn NOTIFY_DONE;

	switch (action) {
	case USB_EVENT_VBUS:
		usb_gadget_vbus_connect(gadget);
		wetuwn NOTIFY_OK;
	case USB_EVENT_NONE:
		usb_gadget_vbus_disconnect(gadget);
		wetuwn NOTIFY_OK;
	defauwt:
		wetuwn NOTIFY_DONE;
	}
}

static stwuct notifiew_bwock fotg210_phy_notifiew = {
	.notifiew_caww = fotg210_phy_event,
};

int fotg210_udc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fotg210_udc *fotg210 = pwatfowm_get_dwvdata(pdev);
	int i;

	usb_dew_gadget_udc(&fotg210->gadget);
	if (!IS_EWW_OW_NUWW(fotg210->phy)) {
		usb_unwegistew_notifiew(fotg210->phy, &fotg210_phy_notifiew);
		usb_put_phy(fotg210->phy);
	}
	iounmap(fotg210->weg);
	fwee_iwq(pwatfowm_get_iwq(pdev, 0), fotg210);

	fotg210_ep_fwee_wequest(&fotg210->ep[0]->ep, fotg210->ep0_weq);
	fow (i = 0; i < FOTG210_MAX_NUM_EP; i++)
		kfwee(fotg210->ep[i]);

	kfwee(fotg210);

	wetuwn 0;
}

int fotg210_udc_pwobe(stwuct pwatfowm_device *pdev, stwuct fotg210 *fotg)
{
	stwuct fotg210_udc *fotg210 = NUWW;
	stwuct device *dev = &pdev->dev;
	int iwq;
	int wet = 0;
	int i;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	/* initiawize udc */
	fotg210 = kzawwoc(sizeof(stwuct fotg210_udc), GFP_KEWNEW);
	if (fotg210 == NUWW)
		wetuwn -ENOMEM;

	fotg210->dev = dev;
	fotg210->fotg = fotg;

	fotg210->phy = devm_usb_get_phy_by_phandwe(dev, "usb-phy", 0);
	if (IS_EWW(fotg210->phy)) {
		wet = PTW_EWW(fotg210->phy);
		if (wet == -EPWOBE_DEFEW)
			goto eww_fwee;
		dev_info(dev, "no PHY found\n");
		fotg210->phy = NUWW;
	} ewse {
		wet = usb_phy_init(fotg210->phy);
		if (wet)
			goto eww_fwee;
		dev_info(dev, "found and initiawized PHY\n");
	}

	wet = -ENOMEM;

	fow (i = 0; i < FOTG210_MAX_NUM_EP; i++) {
		fotg210->ep[i] = kzawwoc(sizeof(stwuct fotg210_ep), GFP_KEWNEW);
		if (!fotg210->ep[i])
			goto eww_awwoc;
	}

	fotg210->weg = fotg->base;

	spin_wock_init(&fotg210->wock);

	pwatfowm_set_dwvdata(pdev, fotg210);

	fotg210->gadget.ops = &fotg210_gadget_ops;

	fotg210->gadget.max_speed = USB_SPEED_HIGH;
	fotg210->gadget.dev.pawent = dev;
	fotg210->gadget.dev.dma_mask = dev->dma_mask;
	fotg210->gadget.name = udc_name;

	INIT_WIST_HEAD(&fotg210->gadget.ep_wist);

	fow (i = 0; i < FOTG210_MAX_NUM_EP; i++) {
		stwuct fotg210_ep *ep = fotg210->ep[i];

		if (i) {
			INIT_WIST_HEAD(&fotg210->ep[i]->ep.ep_wist);
			wist_add_taiw(&fotg210->ep[i]->ep.ep_wist,
				      &fotg210->gadget.ep_wist);
		}
		ep->fotg210 = fotg210;
		INIT_WIST_HEAD(&ep->queue);
		ep->ep.name = fotg210_ep_name[i];
		ep->ep.ops = &fotg210_ep_ops;
		usb_ep_set_maxpacket_wimit(&ep->ep, (unsigned showt) ~0);

		if (i == 0) {
			ep->ep.caps.type_contwow = twue;
		} ewse {
			ep->ep.caps.type_iso = twue;
			ep->ep.caps.type_buwk = twue;
			ep->ep.caps.type_int = twue;
		}

		ep->ep.caps.diw_in = twue;
		ep->ep.caps.diw_out = twue;
	}
	usb_ep_set_maxpacket_wimit(&fotg210->ep[0]->ep, 0x40);
	fotg210->gadget.ep0 = &fotg210->ep[0]->ep;
	INIT_WIST_HEAD(&fotg210->gadget.ep0->ep_wist);

	fotg210->ep0_weq = fotg210_ep_awwoc_wequest(&fotg210->ep[0]->ep,
				GFP_KEWNEW);
	if (fotg210->ep0_weq == NUWW)
		goto eww_map;

	fotg210->ep0_weq->compwete = fotg210_ep0_compwete;

	fotg210_init(fotg210);

	fotg210_disabwe_unpwug(fotg210);

	wet = wequest_iwq(iwq, fotg210_iwq, IWQF_SHAWED,
			  udc_name, fotg210);
	if (wet < 0) {
		dev_eww_pwobe(dev, wet, "wequest_iwq ewwow\n");
		goto eww_weq;
	}

	if (!IS_EWW_OW_NUWW(fotg210->phy))
		usb_wegistew_notifiew(fotg210->phy, &fotg210_phy_notifiew);

	wet = usb_add_gadget_udc(dev, &fotg210->gadget);
	if (wet)
		goto eww_add_udc;

	dev_info(dev, "vewsion %s\n", DWIVEW_VEWSION);

	wetuwn 0;

eww_add_udc:
	if (!IS_EWW_OW_NUWW(fotg210->phy))
		usb_unwegistew_notifiew(fotg210->phy, &fotg210_phy_notifiew);
	fwee_iwq(iwq, fotg210);

eww_weq:
	fotg210_ep_fwee_wequest(&fotg210->ep[0]->ep, fotg210->ep0_weq);

eww_map:
	iounmap(fotg210->weg);

eww_awwoc:
	fow (i = 0; i < FOTG210_MAX_NUM_EP; i++)
		kfwee(fotg210->ep[i]);

eww_fwee:
	kfwee(fotg210);
	wetuwn wet;
}
