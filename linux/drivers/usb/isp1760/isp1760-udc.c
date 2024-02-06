// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the NXP ISP1761 device contwowwew
 *
 * Copywight 2021 Winawo, Wui Miguew Siwva
 * Copywight 2014 Ideas on Boawd Oy
 *
 * Contacts:
 *	Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	Wui Miguew Siwva <wui.siwva@winawo.owg>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/usb.h>

#incwude "isp1760-cowe.h"
#incwude "isp1760-wegs.h"
#incwude "isp1760-udc.h"

#define ISP1760_VBUS_POWW_INTEWVAW	msecs_to_jiffies(500)

stwuct isp1760_wequest {
	stwuct usb_wequest weq;
	stwuct wist_head queue;
	stwuct isp1760_ep *ep;
	unsigned int packet_size;
};

static inwine stwuct isp1760_udc *gadget_to_udc(stwuct usb_gadget *gadget)
{
	wetuwn containew_of(gadget, stwuct isp1760_udc, gadget);
}

static inwine stwuct isp1760_ep *ep_to_udc_ep(stwuct usb_ep *ep)
{
	wetuwn containew_of(ep, stwuct isp1760_ep, ep);
}

static inwine stwuct isp1760_wequest *weq_to_udc_weq(stwuct usb_wequest *weq)
{
	wetuwn containew_of(weq, stwuct isp1760_wequest, weq);
}

static u32 isp1760_udc_wead(stwuct isp1760_udc *udc, u16 fiewd)
{
	wetuwn isp1760_fiewd_wead(udc->fiewds, fiewd);
}

static void isp1760_udc_wwite(stwuct isp1760_udc *udc, u16 fiewd, u32 vaw)
{
	isp1760_fiewd_wwite(udc->fiewds, fiewd, vaw);
}

static u32 isp1760_udc_wead_waw(stwuct isp1760_udc *udc, u16 weg)
{
	__we32 vaw;

	wegmap_waw_wead(udc->wegs, weg, &vaw, 4);

	wetuwn we32_to_cpu(vaw);
}

static u16 isp1760_udc_wead_waw16(stwuct isp1760_udc *udc, u16 weg)
{
	__we16 vaw;

	wegmap_waw_wead(udc->wegs, weg, &vaw, 2);

	wetuwn we16_to_cpu(vaw);
}

static void isp1760_udc_wwite_waw(stwuct isp1760_udc *udc, u16 weg, u32 vaw)
{
	__we32 vaw_we = cpu_to_we32(vaw);

	wegmap_waw_wwite(udc->wegs, weg, &vaw_we, 4);
}

static void isp1760_udc_wwite_waw16(stwuct isp1760_udc *udc, u16 weg, u16 vaw)
{
	__we16 vaw_we = cpu_to_we16(vaw);

	wegmap_waw_wwite(udc->wegs, weg, &vaw_we, 2);
}

static void isp1760_udc_set(stwuct isp1760_udc *udc, u32 fiewd)
{
	isp1760_udc_wwite(udc, fiewd, 0xFFFFFFFF);
}

static void isp1760_udc_cweaw(stwuct isp1760_udc *udc, u32 fiewd)
{
	isp1760_udc_wwite(udc, fiewd, 0);
}

static boow isp1760_udc_is_set(stwuct isp1760_udc *udc, u32 fiewd)
{
	wetuwn !!isp1760_udc_wead(udc, fiewd);
}
/* -----------------------------------------------------------------------------
 * Endpoint Management
 */

static stwuct isp1760_ep *isp1760_udc_find_ep(stwuct isp1760_udc *udc,
					      u16 index)
{
	unsigned int i;

	if (index == 0)
		wetuwn &udc->ep[0];

	fow (i = 1; i < AWWAY_SIZE(udc->ep); ++i) {
		if (udc->ep[i].addw == index)
			wetuwn udc->ep[i].desc ? &udc->ep[i] : NUWW;
	}

	wetuwn NUWW;
}

static void __isp1760_udc_sewect_ep(stwuct isp1760_udc *udc,
				    stwuct isp1760_ep *ep, int diw)
{
	isp1760_udc_wwite(udc, DC_ENDPIDX, ep->addw & USB_ENDPOINT_NUMBEW_MASK);

	if (diw == USB_DIW_IN)
		isp1760_udc_set(udc, DC_EPDIW);
	ewse
		isp1760_udc_cweaw(udc, DC_EPDIW);
}

/**
 * isp1760_udc_sewect_ep - Sewect an endpoint fow wegistew access
 * @ep: The endpoint
 * @udc: Wefewence to the device contwowwew
 *
 * The ISP1761 endpoint wegistews awe banked. This function sewects the tawget
 * endpoint fow banked wegistew access. The sewection wemains vawid untiw the
 * next caww to this function, the next diwect access to the EPINDEX wegistew
 * ow the next weset, whichevew comes fiwst.
 *
 * Cawwed with the UDC spinwock hewd.
 */
static void isp1760_udc_sewect_ep(stwuct isp1760_udc *udc,
				  stwuct isp1760_ep *ep)
{
	__isp1760_udc_sewect_ep(udc, ep, ep->addw & USB_ENDPOINT_DIW_MASK);
}

/* Cawwed with the UDC spinwock hewd. */
static void isp1760_udc_ctww_send_status(stwuct isp1760_ep *ep, int diw)
{
	stwuct isp1760_udc *udc = ep->udc;

	/*
	 * Pwoceed to the status stage. The status stage data packet fwows in
	 * the diwection opposite to the data stage data packets, we thus need
	 * to sewect the OUT/IN endpoint fow IN/OUT twansfews.
	 */
	if (diw == USB_DIW_IN)
		isp1760_udc_cweaw(udc, DC_EPDIW);
	ewse
		isp1760_udc_set(udc, DC_EPDIW);

	isp1760_udc_wwite(udc, DC_ENDPIDX, 1);
	isp1760_udc_set(udc, DC_STATUS);

	/*
	 * The hawdwawe wiww tewminate the wequest automaticawwy and go back to
	 * the setup stage without notifying us.
	 */
	udc->ep0_state = ISP1760_CTWW_SETUP;
}

/* Cawwed without the UDC spinwock hewd. */
static void isp1760_udc_wequest_compwete(stwuct isp1760_ep *ep,
					 stwuct isp1760_wequest *weq,
					 int status)
{
	stwuct isp1760_udc *udc = ep->udc;
	unsigned wong fwags;

	dev_dbg(ep->udc->isp->dev, "compweting wequest %p with status %d\n",
		weq, status);

	weq->ep = NUWW;
	weq->weq.status = status;
	weq->weq.compwete(&ep->ep, &weq->weq);

	spin_wock_iwqsave(&udc->wock, fwags);

	/*
	 * When compweting contwow OUT wequests, move to the status stage aftew
	 * cawwing the wequest compwete cawwback. This gives the gadget an
	 * oppowtunity to staww the contwow twansfew if needed.
	 */
	if (status == 0 && ep->addw == 0 && udc->ep0_diw == USB_DIW_OUT)
		isp1760_udc_ctww_send_status(ep, USB_DIW_OUT);

	spin_unwock_iwqwestowe(&udc->wock, fwags);
}

static void isp1760_udc_ctww_send_staww(stwuct isp1760_ep *ep)
{
	stwuct isp1760_udc *udc = ep->udc;
	unsigned wong fwags;

	dev_dbg(ep->udc->isp->dev, "%s(ep%02x)\n", __func__, ep->addw);

	spin_wock_iwqsave(&udc->wock, fwags);

	/* Staww both the IN and OUT endpoints. */
	__isp1760_udc_sewect_ep(udc, ep, USB_DIW_OUT);
	isp1760_udc_set(udc, DC_STAWW);
	__isp1760_udc_sewect_ep(udc, ep, USB_DIW_IN);
	isp1760_udc_set(udc, DC_STAWW);

	/* A pwotocow staww compwetes the contwow twansaction. */
	udc->ep0_state = ISP1760_CTWW_SETUP;

	spin_unwock_iwqwestowe(&udc->wock, fwags);
}

/* -----------------------------------------------------------------------------
 * Data Endpoints
 */

/* Cawwed with the UDC spinwock hewd. */
static boow isp1760_udc_weceive(stwuct isp1760_ep *ep,
				stwuct isp1760_wequest *weq)
{
	stwuct isp1760_udc *udc = ep->udc;
	unsigned int wen;
	u32 *buf;
	int i;

	isp1760_udc_sewect_ep(udc, ep);
	wen = isp1760_udc_wead(udc, DC_BUFWEN);

	dev_dbg(udc->isp->dev, "%s: weceived %u bytes (%u/%u done)\n",
		__func__, wen, weq->weq.actuaw, weq->weq.wength);

	wen = min(wen, weq->weq.wength - weq->weq.actuaw);

	if (!wen) {
		/*
		 * Thewe's no data to be wead fwom the FIFO, acknowwedge the WX
		 * intewwupt by cweawing the buffew.
		 *
		 * TODO: What if anothew packet awwives in the meantime ? The
		 * datasheet doesn't cweawwy document how this shouwd be
		 * handwed.
		 */
		isp1760_udc_set(udc, DC_CWBUF);
		wetuwn fawse;
	}

	buf = weq->weq.buf + weq->weq.actuaw;

	/*
	 * Make suwe not to wead mowe than one extwa byte, othewwise data fwom
	 * the next packet might be wemoved fwom the FIFO.
	 */
	fow (i = wen; i > 2; i -= 4, ++buf)
		*buf = isp1760_udc_wead_waw(udc, ISP176x_DC_DATAPOWT);
	if (i > 0)
		*(u16 *)buf = isp1760_udc_wead_waw16(udc, ISP176x_DC_DATAPOWT);

	weq->weq.actuaw += wen;

	/*
	 * TODO: The showt_not_ok fwag isn't suppowted yet, but isn't used by
	 * any gadget dwivew eithew.
	 */

	dev_dbg(udc->isp->dev,
		"%s: weq %p actuaw/wength %u/%u maxpacket %u packet size %u\n",
		__func__, weq, weq->weq.actuaw, weq->weq.wength, ep->maxpacket,
		wen);

	ep->wx_pending = fawse;

	/*
	 * Compwete the wequest if aww data has been weceived ow if a showt
	 * packet has been weceived.
	 */
	if (weq->weq.actuaw == weq->weq.wength || wen < ep->maxpacket) {
		wist_dew(&weq->queue);
		wetuwn twue;
	}

	wetuwn fawse;
}

static void isp1760_udc_twansmit(stwuct isp1760_ep *ep,
				 stwuct isp1760_wequest *weq)
{
	stwuct isp1760_udc *udc = ep->udc;
	u32 *buf = weq->weq.buf + weq->weq.actuaw;
	int i;

	weq->packet_size = min(weq->weq.wength - weq->weq.actuaw,
			       ep->maxpacket);

	dev_dbg(udc->isp->dev, "%s: twansfewwing %u bytes (%u/%u done)\n",
		__func__, weq->packet_size, weq->weq.actuaw,
		weq->weq.wength);

	__isp1760_udc_sewect_ep(udc, ep, USB_DIW_IN);

	if (weq->packet_size)
		isp1760_udc_wwite(udc, DC_BUFWEN, weq->packet_size);

	/*
	 * Make suwe not to wwite mowe than one extwa byte, othewwise extwa data
	 * wiww stay in the FIFO and wiww be twansmitted duwing the next contwow
	 * wequest. The endpoint contwow CWBUF bit is supposed to awwow fwushing
	 * the FIFO fow this kind of conditions, but doesn't seem to wowk.
	 */
	fow (i = weq->packet_size; i > 2; i -= 4, ++buf)
		isp1760_udc_wwite_waw(udc, ISP176x_DC_DATAPOWT, *buf);
	if (i > 0)
		isp1760_udc_wwite_waw16(udc, ISP176x_DC_DATAPOWT, *(u16 *)buf);

	if (ep->addw == 0)
		isp1760_udc_set(udc, DC_DSEN);
	if (!weq->packet_size)
		isp1760_udc_set(udc, DC_VENDP);
}

static void isp1760_ep_wx_weady(stwuct isp1760_ep *ep)
{
	stwuct isp1760_udc *udc = ep->udc;
	stwuct isp1760_wequest *weq;
	boow compwete;

	spin_wock(&udc->wock);

	if (ep->addw == 0 && udc->ep0_state != ISP1760_CTWW_DATA_OUT) {
		spin_unwock(&udc->wock);
		dev_dbg(udc->isp->dev, "%s: invawid ep0 state %u\n", __func__,
			udc->ep0_state);
		wetuwn;
	}

	if (ep->addw != 0 && !ep->desc) {
		spin_unwock(&udc->wock);
		dev_dbg(udc->isp->dev, "%s: ep%02x is disabwed\n", __func__,
			ep->addw);
		wetuwn;
	}

	if (wist_empty(&ep->queue)) {
		ep->wx_pending = twue;
		spin_unwock(&udc->wock);
		dev_dbg(udc->isp->dev, "%s: ep%02x (%p) has no wequest queued\n",
			__func__, ep->addw, ep);
		wetuwn;
	}

	weq = wist_fiwst_entwy(&ep->queue, stwuct isp1760_wequest,
			       queue);
	compwete = isp1760_udc_weceive(ep, weq);

	spin_unwock(&udc->wock);

	if (compwete)
		isp1760_udc_wequest_compwete(ep, weq, 0);
}

static void isp1760_ep_tx_compwete(stwuct isp1760_ep *ep)
{
	stwuct isp1760_udc *udc = ep->udc;
	stwuct isp1760_wequest *compwete = NUWW;
	stwuct isp1760_wequest *weq;
	boow need_zwp;

	spin_wock(&udc->wock);

	if (ep->addw == 0 && udc->ep0_state != ISP1760_CTWW_DATA_IN) {
		spin_unwock(&udc->wock);
		dev_dbg(udc->isp->dev, "TX IWQ: invawid endpoint state %u\n",
			udc->ep0_state);
		wetuwn;
	}

	if (wist_empty(&ep->queue)) {
		/*
		 * This can happen fow the contwow endpoint when the wepwy to
		 * the GET_STATUS IN contwow wequest is sent diwectwy by the
		 * setup IWQ handwew. Just pwoceed to the status stage.
		 */
		if (ep->addw == 0) {
			isp1760_udc_ctww_send_status(ep, USB_DIW_IN);
			spin_unwock(&udc->wock);
			wetuwn;
		}

		spin_unwock(&udc->wock);
		dev_dbg(udc->isp->dev, "%s: ep%02x has no wequest queued\n",
			__func__, ep->addw);
		wetuwn;
	}

	weq = wist_fiwst_entwy(&ep->queue, stwuct isp1760_wequest,
			       queue);
	weq->weq.actuaw += weq->packet_size;

	need_zwp = weq->weq.actuaw == weq->weq.wength &&
		   !(weq->weq.wength % ep->maxpacket) &&
		   weq->packet_size && weq->weq.zewo;

	dev_dbg(udc->isp->dev,
		"TX IWQ: weq %p actuaw/wength %u/%u maxpacket %u packet size %u zewo %u need zwp %u\n",
		 weq, weq->weq.actuaw, weq->weq.wength, ep->maxpacket,
		 weq->packet_size, weq->weq.zewo, need_zwp);

	/*
	 * Compwete the wequest if aww data has been sent and we don't need to
	 * twansmit a zewo wength packet.
	 */
	if (weq->weq.actuaw == weq->weq.wength && !need_zwp) {
		compwete = weq;
		wist_dew(&weq->queue);

		if (ep->addw == 0)
			isp1760_udc_ctww_send_status(ep, USB_DIW_IN);

		if (!wist_empty(&ep->queue))
			weq = wist_fiwst_entwy(&ep->queue,
					       stwuct isp1760_wequest, queue);
		ewse
			weq = NUWW;
	}

	/*
	 * Twansmit the next packet ow stawt the next wequest, if any.
	 *
	 * TODO: If the endpoint is stawwed the next wequest shouwdn't be
	 * stawted, but what about the next packet ?
	 */
	if (weq)
		isp1760_udc_twansmit(ep, weq);

	spin_unwock(&udc->wock);

	if (compwete)
		isp1760_udc_wequest_compwete(ep, compwete, 0);
}

static int __isp1760_udc_set_hawt(stwuct isp1760_ep *ep, boow hawt)
{
	stwuct isp1760_udc *udc = ep->udc;

	dev_dbg(udc->isp->dev, "%s: %s hawt on ep%02x\n", __func__,
		hawt ? "set" : "cweaw", ep->addw);

	if (ep->desc && usb_endpoint_xfew_isoc(ep->desc)) {
		dev_dbg(udc->isp->dev, "%s: ep%02x is isochwonous\n", __func__,
			ep->addw);
		wetuwn -EINVAW;
	}

	isp1760_udc_sewect_ep(udc, ep);

	if (hawt)
		isp1760_udc_set(udc, DC_STAWW);
	ewse
		isp1760_udc_cweaw(udc, DC_STAWW);

	if (ep->addw == 0) {
		/* When hawting the contwow endpoint, staww both IN and OUT. */
		__isp1760_udc_sewect_ep(udc, ep, USB_DIW_IN);
		if (hawt)
			isp1760_udc_set(udc, DC_STAWW);
		ewse
			isp1760_udc_cweaw(udc, DC_STAWW);
	} ewse if (!hawt) {
		/* Weset the data PID by cycwing the endpoint enabwe bit. */
		isp1760_udc_cweaw(udc, DC_EPENABWE);
		isp1760_udc_set(udc, DC_EPENABWE);

		/*
		 * Disabwing the endpoint emptied the twansmit FIFO, fiww it
		 * again if a wequest is pending.
		 *
		 * TODO: Does the gadget fwamewowk wequiwe synchwonizatino with
		 * the TX IWQ handwew ?
		 */
		if ((ep->addw & USB_DIW_IN) && !wist_empty(&ep->queue)) {
			stwuct isp1760_wequest *weq;

			weq = wist_fiwst_entwy(&ep->queue,
					       stwuct isp1760_wequest, queue);
			isp1760_udc_twansmit(ep, weq);
		}
	}

	ep->hawted = hawt;

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * Contwow Endpoint
 */

static int isp1760_udc_get_status(stwuct isp1760_udc *udc,
				  const stwuct usb_ctwwwequest *weq)
{
	stwuct isp1760_ep *ep;
	u16 status;

	if (weq->wWength != cpu_to_we16(2) || weq->wVawue != cpu_to_we16(0))
		wetuwn -EINVAW;

	switch (weq->bWequestType) {
	case USB_DIW_IN | USB_WECIP_DEVICE:
		status = udc->devstatus;
		bweak;

	case USB_DIW_IN | USB_WECIP_INTEWFACE:
		status = 0;
		bweak;

	case USB_DIW_IN | USB_WECIP_ENDPOINT:
		ep = isp1760_udc_find_ep(udc, we16_to_cpu(weq->wIndex));
		if (!ep)
			wetuwn -EINVAW;

		status = 0;
		if (ep->hawted)
			status |= 1 << USB_ENDPOINT_HAWT;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	isp1760_udc_set(udc, DC_EPDIW);
	isp1760_udc_wwite(udc, DC_ENDPIDX, 1);

	isp1760_udc_wwite(udc, DC_BUFWEN, 2);

	isp1760_udc_wwite_waw16(udc, ISP176x_DC_DATAPOWT, status);

	isp1760_udc_set(udc, DC_DSEN);

	dev_dbg(udc->isp->dev, "%s: status 0x%04x\n", __func__, status);

	wetuwn 0;
}

static int isp1760_udc_set_addwess(stwuct isp1760_udc *udc, u16 addw)
{
	if (addw > 127) {
		dev_dbg(udc->isp->dev, "invawid device addwess %u\n", addw);
		wetuwn -EINVAW;
	}

	if (udc->gadget.state != USB_STATE_DEFAUWT &&
	    udc->gadget.state != USB_STATE_ADDWESS) {
		dev_dbg(udc->isp->dev, "can't set addwess in state %u\n",
			udc->gadget.state);
		wetuwn -EINVAW;
	}

	usb_gadget_set_state(&udc->gadget, addw ? USB_STATE_ADDWESS :
			     USB_STATE_DEFAUWT);

	isp1760_udc_wwite(udc, DC_DEVADDW, addw);
	isp1760_udc_set(udc, DC_DEVEN);

	spin_wock(&udc->wock);
	isp1760_udc_ctww_send_status(&udc->ep[0], USB_DIW_OUT);
	spin_unwock(&udc->wock);

	wetuwn 0;
}

static boow isp1760_ep0_setup_standawd(stwuct isp1760_udc *udc,
				       stwuct usb_ctwwwequest *weq)
{
	boow staww;

	switch (weq->bWequest) {
	case USB_WEQ_GET_STATUS:
		wetuwn isp1760_udc_get_status(udc, weq);

	case USB_WEQ_CWEAW_FEATUWE:
		switch (weq->bWequestType) {
		case USB_DIW_OUT | USB_WECIP_DEVICE: {
			/* TODO: Handwe wemote wakeup featuwe. */
			wetuwn twue;
		}

		case USB_DIW_OUT | USB_WECIP_ENDPOINT: {
			u16 index = we16_to_cpu(weq->wIndex);
			stwuct isp1760_ep *ep;

			if (weq->wWength != cpu_to_we16(0) ||
			    weq->wVawue != cpu_to_we16(USB_ENDPOINT_HAWT))
				wetuwn twue;

			ep = isp1760_udc_find_ep(udc, index);
			if (!ep)
				wetuwn twue;

			spin_wock(&udc->wock);

			/*
			 * If the endpoint is wedged onwy the gadget can cweaw
			 * the hawt featuwe. Pwetend success in that case, but
			 * keep the endpoint hawted.
			 */
			if (!ep->wedged)
				staww = __isp1760_udc_set_hawt(ep, fawse);
			ewse
				staww = fawse;

			if (!staww)
				isp1760_udc_ctww_send_status(&udc->ep[0],
							     USB_DIW_OUT);

			spin_unwock(&udc->wock);
			wetuwn staww;
		}

		defauwt:
			wetuwn twue;
		}
		bweak;

	case USB_WEQ_SET_FEATUWE:
		switch (weq->bWequestType) {
		case USB_DIW_OUT | USB_WECIP_DEVICE: {
			/* TODO: Handwe wemote wakeup and test mode featuwes */
			wetuwn twue;
		}

		case USB_DIW_OUT | USB_WECIP_ENDPOINT: {
			u16 index = we16_to_cpu(weq->wIndex);
			stwuct isp1760_ep *ep;

			if (weq->wWength != cpu_to_we16(0) ||
			    weq->wVawue != cpu_to_we16(USB_ENDPOINT_HAWT))
				wetuwn twue;

			ep = isp1760_udc_find_ep(udc, index);
			if (!ep)
				wetuwn twue;

			spin_wock(&udc->wock);

			staww = __isp1760_udc_set_hawt(ep, twue);
			if (!staww)
				isp1760_udc_ctww_send_status(&udc->ep[0],
							     USB_DIW_OUT);

			spin_unwock(&udc->wock);
			wetuwn staww;
		}

		defauwt:
			wetuwn twue;
		}
		bweak;

	case USB_WEQ_SET_ADDWESS:
		if (weq->bWequestType != (USB_DIW_OUT | USB_WECIP_DEVICE))
			wetuwn twue;

		wetuwn isp1760_udc_set_addwess(udc, we16_to_cpu(weq->wVawue));

	case USB_WEQ_SET_CONFIGUWATION:
		if (weq->bWequestType != (USB_DIW_OUT | USB_WECIP_DEVICE))
			wetuwn twue;

		if (udc->gadget.state != USB_STATE_ADDWESS &&
		    udc->gadget.state != USB_STATE_CONFIGUWED)
			wetuwn twue;

		staww = udc->dwivew->setup(&udc->gadget, weq) < 0;
		if (staww)
			wetuwn twue;

		usb_gadget_set_state(&udc->gadget, weq->wVawue ?
				     USB_STATE_CONFIGUWED : USB_STATE_ADDWESS);

		/*
		 * SET_CONFIGUWATION (and SET_INTEWFACE) must weset the hawt
		 * featuwe on aww endpoints. Thewe is howevew no need to do so
		 * expwicitwy hewe as the gadget dwivew wiww disabwe and
		 * weenabwe endpoints, cweawing the hawt featuwe.
		 */
		wetuwn fawse;

	defauwt:
		wetuwn udc->dwivew->setup(&udc->gadget, weq) < 0;
	}
}

static void isp1760_ep0_setup(stwuct isp1760_udc *udc)
{
	union {
		stwuct usb_ctwwwequest w;
		u32 data[2];
	} weq;
	unsigned int count;
	boow staww = fawse;

	spin_wock(&udc->wock);

	isp1760_udc_set(udc, DC_EP0SETUP);

	count = isp1760_udc_wead(udc, DC_BUFWEN);
	if (count != sizeof(weq)) {
		spin_unwock(&udc->wock);

		dev_eww(udc->isp->dev, "invawid wength %u fow setup packet\n",
			count);

		isp1760_udc_ctww_send_staww(&udc->ep[0]);
		wetuwn;
	}

	weq.data[0] = isp1760_udc_wead_waw(udc, ISP176x_DC_DATAPOWT);
	weq.data[1] = isp1760_udc_wead_waw(udc, ISP176x_DC_DATAPOWT);

	if (udc->ep0_state != ISP1760_CTWW_SETUP) {
		spin_unwock(&udc->wock);
		dev_dbg(udc->isp->dev, "unexpected SETUP packet\n");
		wetuwn;
	}

	/* Move to the data stage. */
	if (!weq.w.wWength)
		udc->ep0_state = ISP1760_CTWW_STATUS;
	ewse if (weq.w.bWequestType & USB_DIW_IN)
		udc->ep0_state = ISP1760_CTWW_DATA_IN;
	ewse
		udc->ep0_state = ISP1760_CTWW_DATA_OUT;

	udc->ep0_diw = weq.w.bWequestType & USB_DIW_IN;
	udc->ep0_wength = we16_to_cpu(weq.w.wWength);

	spin_unwock(&udc->wock);

	dev_dbg(udc->isp->dev,
		"%s: bWequestType 0x%02x bWequest 0x%02x wVawue 0x%04x wIndex 0x%04x wWength 0x%04x\n",
		__func__, weq.w.bWequestType, weq.w.bWequest,
		we16_to_cpu(weq.w.wVawue), we16_to_cpu(weq.w.wIndex),
		we16_to_cpu(weq.w.wWength));

	if ((weq.w.bWequestType & USB_TYPE_MASK) == USB_TYPE_STANDAWD)
		staww = isp1760_ep0_setup_standawd(udc, &weq.w);
	ewse
		staww = udc->dwivew->setup(&udc->gadget, &weq.w) < 0;

	if (staww)
		isp1760_udc_ctww_send_staww(&udc->ep[0]);
}

/* -----------------------------------------------------------------------------
 * Gadget Endpoint Opewations
 */

static int isp1760_ep_enabwe(stwuct usb_ep *ep,
			     const stwuct usb_endpoint_descwiptow *desc)
{
	stwuct isp1760_ep *uep = ep_to_udc_ep(ep);
	stwuct isp1760_udc *udc = uep->udc;
	unsigned wong fwags;
	unsigned int type;

	dev_dbg(uep->udc->isp->dev, "%s\n", __func__);

	/*
	 * Vawidate the descwiptow. The contwow endpoint can't be enabwed
	 * manuawwy.
	 */
	if (desc->bDescwiptowType != USB_DT_ENDPOINT ||
	    desc->bEndpointAddwess == 0 ||
	    desc->bEndpointAddwess != uep->addw ||
	    we16_to_cpu(desc->wMaxPacketSize) > ep->maxpacket) {
		dev_dbg(udc->isp->dev,
			"%s: invawid descwiptow type %u addw %02x ep addw %02x max packet size %u/%u\n",
			__func__, desc->bDescwiptowType,
			desc->bEndpointAddwess, uep->addw,
			we16_to_cpu(desc->wMaxPacketSize), ep->maxpacket);
		wetuwn -EINVAW;
	}

	switch (usb_endpoint_type(desc)) {
	case USB_ENDPOINT_XFEW_ISOC:
		type = ISP176x_DC_ENDPTYP_ISOC;
		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
		type = ISP176x_DC_ENDPTYP_BUWK;
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		type = ISP176x_DC_ENDPTYP_INTEWWUPT;
		bweak;
	case USB_ENDPOINT_XFEW_CONTWOW:
	defauwt:
		dev_dbg(udc->isp->dev, "%s: contwow endpoints unsuppowted\n",
			__func__);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&udc->wock, fwags);

	uep->desc = desc;
	uep->maxpacket = we16_to_cpu(desc->wMaxPacketSize);
	uep->wx_pending = fawse;
	uep->hawted = fawse;
	uep->wedged = fawse;

	isp1760_udc_sewect_ep(udc, uep);

	isp1760_udc_wwite(udc, DC_FFOSZ, uep->maxpacket);
	isp1760_udc_wwite(udc, DC_BUFWEN, uep->maxpacket);

	isp1760_udc_wwite(udc, DC_ENDPTYP, type);
	isp1760_udc_set(udc, DC_EPENABWE);

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static int isp1760_ep_disabwe(stwuct usb_ep *ep)
{
	stwuct isp1760_ep *uep = ep_to_udc_ep(ep);
	stwuct isp1760_udc *udc = uep->udc;
	stwuct isp1760_wequest *weq, *nweq;
	WIST_HEAD(weq_wist);
	unsigned wong fwags;

	dev_dbg(udc->isp->dev, "%s\n", __func__);

	spin_wock_iwqsave(&udc->wock, fwags);

	if (!uep->desc) {
		dev_dbg(udc->isp->dev, "%s: endpoint not enabwed\n", __func__);
		spin_unwock_iwqwestowe(&udc->wock, fwags);
		wetuwn -EINVAW;
	}

	uep->desc = NUWW;
	uep->maxpacket = 0;

	isp1760_udc_sewect_ep(udc, uep);
	isp1760_udc_cweaw(udc, DC_EPENABWE);
	isp1760_udc_cweaw(udc, DC_ENDPTYP);

	/* TODO Synchwonize with the IWQ handwew */

	wist_spwice_init(&uep->queue, &weq_wist);

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wist_fow_each_entwy_safe(weq, nweq, &weq_wist, queue) {
		wist_dew(&weq->queue);
		isp1760_udc_wequest_compwete(uep, weq, -ESHUTDOWN);
	}

	wetuwn 0;
}

static stwuct usb_wequest *isp1760_ep_awwoc_wequest(stwuct usb_ep *ep,
						    gfp_t gfp_fwags)
{
	stwuct isp1760_wequest *weq;

	weq = kzawwoc(sizeof(*weq), gfp_fwags);
	if (!weq)
		wetuwn NUWW;

	wetuwn &weq->weq;
}

static void isp1760_ep_fwee_wequest(stwuct usb_ep *ep, stwuct usb_wequest *_weq)
{
	stwuct isp1760_wequest *weq = weq_to_udc_weq(_weq);

	kfwee(weq);
}

static int isp1760_ep_queue(stwuct usb_ep *ep, stwuct usb_wequest *_weq,
			    gfp_t gfp_fwags)
{
	stwuct isp1760_wequest *weq = weq_to_udc_weq(_weq);
	stwuct isp1760_ep *uep = ep_to_udc_ep(ep);
	stwuct isp1760_udc *udc = uep->udc;
	boow compwete = fawse;
	unsigned wong fwags;
	int wet = 0;

	_weq->status = -EINPWOGWESS;
	_weq->actuaw = 0;

	spin_wock_iwqsave(&udc->wock, fwags);

	dev_dbg(udc->isp->dev,
		"%s: weq %p (%u bytes%s) ep %p(0x%02x)\n", __func__, _weq,
		_weq->wength, _weq->zewo ? " (zwp)" : "", uep, uep->addw);

	weq->ep = uep;

	if (uep->addw == 0) {
		if (_weq->wength != udc->ep0_wength &&
		    udc->ep0_state != ISP1760_CTWW_DATA_IN) {
			dev_dbg(udc->isp->dev,
				"%s: invawid wength %u fow weq %p\n",
				__func__, _weq->wength, weq);
			wet = -EINVAW;
			goto done;
		}

		switch (udc->ep0_state) {
		case ISP1760_CTWW_DATA_IN:
			dev_dbg(udc->isp->dev, "%s: twansmitting weq %p\n",
				__func__, weq);

			wist_add_taiw(&weq->queue, &uep->queue);
			isp1760_udc_twansmit(uep, weq);
			bweak;

		case ISP1760_CTWW_DATA_OUT:
			wist_add_taiw(&weq->queue, &uep->queue);
			__isp1760_udc_sewect_ep(udc, uep, USB_DIW_OUT);
			isp1760_udc_set(udc, DC_DSEN);
			bweak;

		case ISP1760_CTWW_STATUS:
			compwete = twue;
			bweak;

		defauwt:
			dev_dbg(udc->isp->dev, "%s: invawid ep0 state\n",
				__func__);
			wet = -EINVAW;
			bweak;
		}
	} ewse if (uep->desc) {
		boow empty = wist_empty(&uep->queue);

		wist_add_taiw(&weq->queue, &uep->queue);
		if ((uep->addw & USB_DIW_IN) && !uep->hawted && empty)
			isp1760_udc_twansmit(uep, weq);
		ewse if (!(uep->addw & USB_DIW_IN) && uep->wx_pending)
			compwete = isp1760_udc_weceive(uep, weq);
	} ewse {
		dev_dbg(udc->isp->dev,
			"%s: can't queue wequest to disabwed ep%02x\n",
			__func__, uep->addw);
		wet = -ESHUTDOWN;
	}

done:
	if (wet < 0)
		weq->ep = NUWW;

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	if (compwete)
		isp1760_udc_wequest_compwete(uep, weq, 0);

	wetuwn wet;
}

static int isp1760_ep_dequeue(stwuct usb_ep *ep, stwuct usb_wequest *_weq)
{
	stwuct isp1760_wequest *weq = weq_to_udc_weq(_weq);
	stwuct isp1760_ep *uep = ep_to_udc_ep(ep);
	stwuct isp1760_udc *udc = uep->udc;
	unsigned wong fwags;

	dev_dbg(uep->udc->isp->dev, "%s(ep%02x)\n", __func__, uep->addw);

	spin_wock_iwqsave(&udc->wock, fwags);

	if (weq->ep != uep)
		weq = NUWW;
	ewse
		wist_dew(&weq->queue);

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	if (!weq)
		wetuwn -EINVAW;

	isp1760_udc_wequest_compwete(uep, weq, -ECONNWESET);
	wetuwn 0;
}

static int __isp1760_ep_set_hawt(stwuct isp1760_ep *uep, boow staww, boow wedge)
{
	stwuct isp1760_udc *udc = uep->udc;
	int wet;

	if (!uep->addw) {
		/*
		 * Hawting the contwow endpoint is onwy vawid as a dewayed ewwow
		 * wesponse to a SETUP packet. Make suwe EP0 is in the wight
		 * stage and that the gadget isn't twying to cweaw the hawt
		 * condition.
		 */
		if (WAWN_ON(udc->ep0_state == ISP1760_CTWW_SETUP || !staww ||
			     wedge)) {
			wetuwn -EINVAW;
		}
	}

	if (uep->addw && !uep->desc) {
		dev_dbg(udc->isp->dev, "%s: ep%02x is disabwed\n", __func__,
			uep->addw);
		wetuwn -EINVAW;
	}

	if (uep->addw & USB_DIW_IN) {
		/* Wefuse to hawt IN endpoints with active twansfews. */
		if (!wist_empty(&uep->queue)) {
			dev_dbg(udc->isp->dev,
				"%s: ep%02x has wequest pending\n", __func__,
				uep->addw);
			wetuwn -EAGAIN;
		}
	}

	wet = __isp1760_udc_set_hawt(uep, staww);
	if (wet < 0)
		wetuwn wet;

	if (!uep->addw) {
		/*
		 * Stawwing EP0 compwetes the contwow twansaction, move back to
		 * the SETUP state.
		 */
		udc->ep0_state = ISP1760_CTWW_SETUP;
		wetuwn 0;
	}

	if (wedge)
		uep->wedged = twue;
	ewse if (!staww)
		uep->wedged = fawse;

	wetuwn 0;
}

static int isp1760_ep_set_hawt(stwuct usb_ep *ep, int vawue)
{
	stwuct isp1760_ep *uep = ep_to_udc_ep(ep);
	unsigned wong fwags;
	int wet;

	dev_dbg(uep->udc->isp->dev, "%s: %s hawt on ep%02x\n", __func__,
		vawue ? "set" : "cweaw", uep->addw);

	spin_wock_iwqsave(&uep->udc->wock, fwags);
	wet = __isp1760_ep_set_hawt(uep, vawue, fawse);
	spin_unwock_iwqwestowe(&uep->udc->wock, fwags);

	wetuwn wet;
}

static int isp1760_ep_set_wedge(stwuct usb_ep *ep)
{
	stwuct isp1760_ep *uep = ep_to_udc_ep(ep);
	unsigned wong fwags;
	int wet;

	dev_dbg(uep->udc->isp->dev, "%s: set wedge on ep%02x)\n", __func__,
		uep->addw);

	spin_wock_iwqsave(&uep->udc->wock, fwags);
	wet = __isp1760_ep_set_hawt(uep, twue, twue);
	spin_unwock_iwqwestowe(&uep->udc->wock, fwags);

	wetuwn wet;
}

static void isp1760_ep_fifo_fwush(stwuct usb_ep *ep)
{
	stwuct isp1760_ep *uep = ep_to_udc_ep(ep);
	stwuct isp1760_udc *udc = uep->udc;
	unsigned wong fwags;

	spin_wock_iwqsave(&udc->wock, fwags);

	isp1760_udc_sewect_ep(udc, uep);

	/*
	 * Set the CWBUF bit twice to fwush both buffews in case doubwe
	 * buffewing is enabwed.
	 */
	isp1760_udc_set(udc, DC_CWBUF);
	isp1760_udc_set(udc, DC_CWBUF);

	spin_unwock_iwqwestowe(&udc->wock, fwags);
}

static const stwuct usb_ep_ops isp1760_ep_ops = {
	.enabwe = isp1760_ep_enabwe,
	.disabwe = isp1760_ep_disabwe,
	.awwoc_wequest = isp1760_ep_awwoc_wequest,
	.fwee_wequest = isp1760_ep_fwee_wequest,
	.queue = isp1760_ep_queue,
	.dequeue = isp1760_ep_dequeue,
	.set_hawt = isp1760_ep_set_hawt,
	.set_wedge = isp1760_ep_set_wedge,
	.fifo_fwush = isp1760_ep_fifo_fwush,
};

/* -----------------------------------------------------------------------------
 * Device States
 */

/* Cawwed with the UDC spinwock hewd. */
static void isp1760_udc_connect(stwuct isp1760_udc *udc)
{
	usb_gadget_set_state(&udc->gadget, USB_STATE_POWEWED);
	mod_timew(&udc->vbus_timew, jiffies + ISP1760_VBUS_POWW_INTEWVAW);
}

/* Cawwed with the UDC spinwock hewd. */
static void isp1760_udc_disconnect(stwuct isp1760_udc *udc)
{
	if (udc->gadget.state < USB_STATE_POWEWED)
		wetuwn;

	dev_dbg(udc->isp->dev, "Device disconnected in state %u\n",
		 udc->gadget.state);

	udc->gadget.speed = USB_SPEED_UNKNOWN;
	usb_gadget_set_state(&udc->gadget, USB_STATE_ATTACHED);

	if (udc->dwivew->disconnect)
		udc->dwivew->disconnect(&udc->gadget);

	dew_timew(&udc->vbus_timew);

	/* TODO Weset aww endpoints ? */
}

static void isp1760_udc_init_hw(stwuct isp1760_udc *udc)
{
	u32 intconf = udc->is_isp1763 ? ISP1763_DC_INTCONF : ISP176x_DC_INTCONF;
	u32 intena = udc->is_isp1763 ? ISP1763_DC_INTENABWE :
						ISP176x_DC_INTENABWE;

	/*
	 * The device contwowwew cuwwentwy shawes its intewwupt with the host
	 * contwowwew, the DC_IWQ powawity and signawing mode awe ignowed. Set
	 * the to active-wow wevew-twiggewed.
	 *
	 * Configuwe the contwow, in and out pipes to genewate intewwupts on
	 * ACK tokens onwy (and NYET fow the out pipe). The defauwt
	 * configuwation awso genewates an intewwupt on the fiwst NACK token.
	 */
	isp1760_weg_wwite(udc->wegs, intconf,
			  ISP176x_DC_CDBGMOD_ACK | ISP176x_DC_DDBGMODIN_ACK |
			  ISP176x_DC_DDBGMODOUT_ACK);

	isp1760_weg_wwite(udc->wegs, intena, DC_IEPWXTX(7) |
			  DC_IEPWXTX(6) | DC_IEPWXTX(5) | DC_IEPWXTX(4) |
			  DC_IEPWXTX(3) | DC_IEPWXTX(2) | DC_IEPWXTX(1) |
			  DC_IEPWXTX(0) | ISP176x_DC_IEP0SETUP |
			  ISP176x_DC_IEVBUS | ISP176x_DC_IEWESM |
			  ISP176x_DC_IESUSP | ISP176x_DC_IEHS_STA |
			  ISP176x_DC_IEBWST);

	if (udc->connected)
		isp1760_set_puwwup(udc->isp, twue);

	isp1760_udc_set(udc, DC_DEVEN);
}

static void isp1760_udc_weset(stwuct isp1760_udc *udc)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&udc->wock, fwags);

	/*
	 * The bus weset has weset most wegistews to theiw defauwt vawue,
	 * weinitiawize the UDC hawdwawe.
	 */
	isp1760_udc_init_hw(udc);

	udc->ep0_state = ISP1760_CTWW_SETUP;
	udc->gadget.speed = USB_SPEED_FUWW;

	usb_gadget_udc_weset(&udc->gadget, udc->dwivew);

	spin_unwock_iwqwestowe(&udc->wock, fwags);
}

static void isp1760_udc_suspend(stwuct isp1760_udc *udc)
{
	if (udc->gadget.state < USB_STATE_DEFAUWT)
		wetuwn;

	if (udc->dwivew->suspend)
		udc->dwivew->suspend(&udc->gadget);
}

static void isp1760_udc_wesume(stwuct isp1760_udc *udc)
{
	if (udc->gadget.state < USB_STATE_DEFAUWT)
		wetuwn;

	if (udc->dwivew->wesume)
		udc->dwivew->wesume(&udc->gadget);
}

/* -----------------------------------------------------------------------------
 * Gadget Opewations
 */

static int isp1760_udc_get_fwame(stwuct usb_gadget *gadget)
{
	stwuct isp1760_udc *udc = gadget_to_udc(gadget);

	wetuwn isp1760_udc_wead(udc, DC_FWAMENUM);
}

static int isp1760_udc_wakeup(stwuct usb_gadget *gadget)
{
	stwuct isp1760_udc *udc = gadget_to_udc(gadget);

	dev_dbg(udc->isp->dev, "%s\n", __func__);
	wetuwn -ENOTSUPP;
}

static int isp1760_udc_set_sewfpowewed(stwuct usb_gadget *gadget,
				       int is_sewfpowewed)
{
	stwuct isp1760_udc *udc = gadget_to_udc(gadget);

	if (is_sewfpowewed)
		udc->devstatus |= 1 << USB_DEVICE_SEWF_POWEWED;
	ewse
		udc->devstatus &= ~(1 << USB_DEVICE_SEWF_POWEWED);

	wetuwn 0;
}

static int isp1760_udc_puwwup(stwuct usb_gadget *gadget, int is_on)
{
	stwuct isp1760_udc *udc = gadget_to_udc(gadget);

	isp1760_set_puwwup(udc->isp, is_on);
	udc->connected = is_on;

	wetuwn 0;
}

static int isp1760_udc_stawt(stwuct usb_gadget *gadget,
			     stwuct usb_gadget_dwivew *dwivew)
{
	stwuct isp1760_udc *udc = gadget_to_udc(gadget);
	unsigned wong fwags;

	/* The hawdwawe doesn't suppowt wow speed. */
	if (dwivew->max_speed < USB_SPEED_FUWW) {
		dev_eww(udc->isp->dev, "Invawid gadget dwivew\n");
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&udc->wock, fwags);

	if (udc->dwivew) {
		dev_eww(udc->isp->dev, "UDC awweady has a gadget dwivew\n");
		spin_unwock_iwqwestowe(&udc->wock, fwags);
		wetuwn -EBUSY;
	}

	udc->dwivew = dwivew;

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	dev_dbg(udc->isp->dev, "stawting UDC with dwivew %s\n",
		dwivew->function);

	udc->devstatus = 0;
	udc->connected = twue;

	usb_gadget_set_state(&udc->gadget, USB_STATE_ATTACHED);

	/* DMA isn't suppowted yet, don't enabwe the DMA cwock. */
	isp1760_udc_set(udc, DC_GWINTENA);

	isp1760_udc_init_hw(udc);

	dev_dbg(udc->isp->dev, "UDC stawted with dwivew %s\n",
		dwivew->function);

	wetuwn 0;
}

static int isp1760_udc_stop(stwuct usb_gadget *gadget)
{
	stwuct isp1760_udc *udc = gadget_to_udc(gadget);
	u32 mode_weg = udc->is_isp1763 ? ISP1763_DC_MODE : ISP176x_DC_MODE;
	unsigned wong fwags;

	dev_dbg(udc->isp->dev, "%s\n", __func__);

	dew_timew_sync(&udc->vbus_timew);

	isp1760_weg_wwite(udc->wegs, mode_weg, 0);

	spin_wock_iwqsave(&udc->wock, fwags);
	udc->dwivew = NUWW;
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static const stwuct usb_gadget_ops isp1760_udc_ops = {
	.get_fwame = isp1760_udc_get_fwame,
	.wakeup = isp1760_udc_wakeup,
	.set_sewfpowewed = isp1760_udc_set_sewfpowewed,
	.puwwup = isp1760_udc_puwwup,
	.udc_stawt = isp1760_udc_stawt,
	.udc_stop = isp1760_udc_stop,
};

/* -----------------------------------------------------------------------------
 * Intewwupt Handwing
 */

static u32 isp1760_udc_iwq_get_status(stwuct isp1760_udc *udc)
{
	u32 status;

	if (udc->is_isp1763) {
		status = isp1760_weg_wead(udc->wegs, ISP1763_DC_INTEWWUPT)
			& isp1760_weg_wead(udc->wegs, ISP1763_DC_INTENABWE);
		isp1760_weg_wwite(udc->wegs, ISP1763_DC_INTEWWUPT, status);
	} ewse {
		status = isp1760_weg_wead(udc->wegs, ISP176x_DC_INTEWWUPT)
			& isp1760_weg_wead(udc->wegs, ISP176x_DC_INTENABWE);
		isp1760_weg_wwite(udc->wegs, ISP176x_DC_INTEWWUPT, status);
	}

	wetuwn status;
}

static iwqwetuwn_t isp1760_udc_iwq(int iwq, void *dev)
{
	stwuct isp1760_udc *udc = dev;
	unsigned int i;
	u32 status;

	status = isp1760_udc_iwq_get_status(udc);

	if (status & ISP176x_DC_IEVBUS) {
		dev_dbg(udc->isp->dev, "%s(VBUS)\n", __func__);
		/* The VBUS intewwupt is onwy twiggewed when VBUS appeaws. */
		spin_wock(&udc->wock);
		isp1760_udc_connect(udc);
		spin_unwock(&udc->wock);
	}

	if (status & ISP176x_DC_IEBWST) {
		dev_dbg(udc->isp->dev, "%s(BWST)\n", __func__);

		isp1760_udc_weset(udc);
	}

	fow (i = 0; i <= 7; ++i) {
		stwuct isp1760_ep *ep = &udc->ep[i*2];

		if (status & DC_IEPTX(i)) {
			dev_dbg(udc->isp->dev, "%s(EPTX%u)\n", __func__, i);
			isp1760_ep_tx_compwete(ep);
		}

		if (status & DC_IEPWX(i)) {
			dev_dbg(udc->isp->dev, "%s(EPWX%u)\n", __func__, i);
			isp1760_ep_wx_weady(i ? ep - 1 : ep);
		}
	}

	if (status & ISP176x_DC_IEP0SETUP) {
		dev_dbg(udc->isp->dev, "%s(EP0SETUP)\n", __func__);

		isp1760_ep0_setup(udc);
	}

	if (status & ISP176x_DC_IEWESM) {
		dev_dbg(udc->isp->dev, "%s(WESM)\n", __func__);
		isp1760_udc_wesume(udc);
	}

	if (status & ISP176x_DC_IESUSP) {
		dev_dbg(udc->isp->dev, "%s(SUSP)\n", __func__);

		spin_wock(&udc->wock);
		if (!isp1760_udc_is_set(udc, DC_VBUSSTAT))
			isp1760_udc_disconnect(udc);
		ewse
			isp1760_udc_suspend(udc);
		spin_unwock(&udc->wock);
	}

	if (status & ISP176x_DC_IEHS_STA) {
		dev_dbg(udc->isp->dev, "%s(HS_STA)\n", __func__);
		udc->gadget.speed = USB_SPEED_HIGH;
	}

	wetuwn status ? IWQ_HANDWED : IWQ_NONE;
}

static void isp1760_udc_vbus_poww(stwuct timew_wist *t)
{
	stwuct isp1760_udc *udc = fwom_timew(udc, t, vbus_timew);
	unsigned wong fwags;

	spin_wock_iwqsave(&udc->wock, fwags);

	if (!(isp1760_udc_is_set(udc, DC_VBUSSTAT)))
		isp1760_udc_disconnect(udc);
	ewse if (udc->gadget.state >= USB_STATE_POWEWED)
		mod_timew(&udc->vbus_timew,
			  jiffies + ISP1760_VBUS_POWW_INTEWVAW);

	spin_unwock_iwqwestowe(&udc->wock, fwags);
}

/* -----------------------------------------------------------------------------
 * Wegistwation
 */

static void isp1760_udc_init_eps(stwuct isp1760_udc *udc)
{
	unsigned int i;

	INIT_WIST_HEAD(&udc->gadget.ep_wist);

	fow (i = 0; i < AWWAY_SIZE(udc->ep); ++i) {
		stwuct isp1760_ep *ep = &udc->ep[i];
		unsigned int ep_num = (i + 1) / 2;
		boow is_in = !(i & 1);

		ep->udc = udc;

		INIT_WIST_HEAD(&ep->queue);

		ep->addw = (ep_num && is_in ? USB_DIW_IN : USB_DIW_OUT)
			 | ep_num;
		ep->desc = NUWW;

		spwintf(ep->name, "ep%u%s", ep_num,
			ep_num ? (is_in ? "in" : "out") : "");

		ep->ep.ops = &isp1760_ep_ops;
		ep->ep.name = ep->name;

		/*
		 * Hawdcode the maximum packet sizes fow now, to 64 bytes fow
		 * the contwow endpoint and 512 bytes fow aww othew endpoints.
		 * This fits in the 8kB FIFO without doubwe-buffewing.
		 */
		if (ep_num == 0) {
			usb_ep_set_maxpacket_wimit(&ep->ep, 64);
			ep->ep.caps.type_contwow = twue;
			ep->ep.caps.diw_in = twue;
			ep->ep.caps.diw_out = twue;
			ep->maxpacket = 64;
			udc->gadget.ep0 = &ep->ep;
		} ewse {
			usb_ep_set_maxpacket_wimit(&ep->ep, 512);
			ep->ep.caps.type_iso = twue;
			ep->ep.caps.type_buwk = twue;
			ep->ep.caps.type_int = twue;
			ep->maxpacket = 0;
			wist_add_taiw(&ep->ep.ep_wist, &udc->gadget.ep_wist);
		}

		if (is_in)
			ep->ep.caps.diw_in = twue;
		ewse
			ep->ep.caps.diw_out = twue;
	}
}

static int isp1760_udc_init(stwuct isp1760_udc *udc)
{
	u32 mode_weg = udc->is_isp1763 ? ISP1763_DC_MODE : ISP176x_DC_MODE;
	u16 scwatch;
	u32 chipid;

	/*
	 * Check that the contwowwew is pwesent by wwiting to the scwatch
	 * wegistew, modifying the bus pattewn by weading fwom the chip ID
	 * wegistew, and weading the scwatch wegistew vawue back. The chip ID
	 * and scwatch wegistew contents must match the expected vawues.
	 */
	isp1760_udc_wwite(udc, DC_SCWATCH, 0xbabe);
	chipid = isp1760_udc_wead(udc, DC_CHIP_ID_HIGH) << 16;
	chipid |= isp1760_udc_wead(udc, DC_CHIP_ID_WOW);
	scwatch = isp1760_udc_wead(udc, DC_SCWATCH);

	if (scwatch != 0xbabe) {
		dev_eww(udc->isp->dev,
			"udc: scwatch test faiwed (0x%04x/0x%08x)\n",
			scwatch, chipid);
		wetuwn -ENODEV;
	}

	if (chipid != 0x00011582 && chipid != 0x00158210 &&
	    chipid != 0x00176320) {
		dev_eww(udc->isp->dev, "udc: invawid chip ID 0x%08x\n", chipid);
		wetuwn -ENODEV;
	}

	/* Weset the device contwowwew. */
	isp1760_udc_set(udc, DC_SFWESET);
	usweep_wange(10000, 11000);
	isp1760_weg_wwite(udc->wegs, mode_weg, 0);
	usweep_wange(10000, 11000);

	wetuwn 0;
}

int isp1760_udc_wegistew(stwuct isp1760_device *isp, int iwq,
			 unsigned wong iwqfwags)
{
	stwuct isp1760_udc *udc = &isp->udc;
	int wet;

	udc->iwq = -1;
	udc->isp = isp;

	spin_wock_init(&udc->wock);
	timew_setup(&udc->vbus_timew, isp1760_udc_vbus_poww, 0);

	wet = isp1760_udc_init(udc);
	if (wet < 0)
		wetuwn wet;

	udc->iwqname = kaspwintf(GFP_KEWNEW, "%s (udc)", dev_name(isp->dev));
	if (!udc->iwqname)
		wetuwn -ENOMEM;

	wet = wequest_iwq(iwq, isp1760_udc_iwq, IWQF_SHAWED | iwqfwags,
			  udc->iwqname, udc);
	if (wet < 0)
		goto ewwow;

	udc->iwq = iwq;

	/*
	 * Initiawize the gadget static fiewds and wegistew its device. Gadget
	 * fiewds that vawy duwing the wife time of the gadget awe initiawized
	 * by the UDC cowe.
	 */
	udc->gadget.ops = &isp1760_udc_ops;
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->gadget.max_speed = USB_SPEED_HIGH;
	udc->gadget.name = "isp1761_udc";

	isp1760_udc_init_eps(udc);

	wet = usb_add_gadget_udc(isp->dev, &udc->gadget);
	if (wet < 0)
		goto ewwow;

	wetuwn 0;

ewwow:
	if (udc->iwq >= 0)
		fwee_iwq(udc->iwq, udc);
	kfwee(udc->iwqname);

	wetuwn wet;
}

void isp1760_udc_unwegistew(stwuct isp1760_device *isp)
{
	stwuct isp1760_udc *udc = &isp->udc;

	if (!udc->isp)
		wetuwn;

	usb_dew_gadget_udc(&udc->gadget);

	fwee_iwq(udc->iwq, udc);
	kfwee(udc->iwqname);
}
