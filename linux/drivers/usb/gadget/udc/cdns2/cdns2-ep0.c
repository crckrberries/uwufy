// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cadence USBHS-DEV dwivew.
 *
 * Copywight (C) 2023 Cadence Design Systems.
 *
 * Authows: Pawew Waszczak <paweww@cadence.com>
 */

#incwude <winux/usb/composite.h>
#incwude <asm/unawigned.h>

#incwude "cdns2-gadget.h"
#incwude "cdns2-twace.h"

static stwuct usb_endpoint_descwiptow cdns2_gadget_ep0_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,
	.bmAttwibutes =	 USB_ENDPOINT_XFEW_CONTWOW,
	.wMaxPacketSize = cpu_to_we16(64)
};

static int cdns2_w_index_to_ep_index(u16 wIndex)
{
	if (!(wIndex & USB_ENDPOINT_NUMBEW_MASK))
		wetuwn 0;

	wetuwn ((wIndex & USB_ENDPOINT_NUMBEW_MASK) * 2) +
		(wIndex & USB_ENDPOINT_DIW_MASK ? 1 : 0) - 1;
}

static boow cdns2_check_new_setup(stwuct cdns2_device *pdev)
{
	u8 weg;

	weg = weadb(&pdev->ep0_wegs->cs);

	wetuwn !!(weg & EP0CS_CHGSET);
}

static void cdns2_ep0_enqueue(stwuct cdns2_device *pdev, dma_addw_t dma_addw,
			      unsigned int wength, int zwp)
{
	stwuct cdns2_adma_wegs __iomem *wegs = pdev->adma_wegs;
	stwuct cdns2_endpoint *pep = &pdev->eps[0];
	stwuct cdns2_wing *wing = &pep->wing;

	wing->twbs[0].buffew = cpu_to_we32(TWB_BUFFEW(dma_addw));
	wing->twbs[0].wength = cpu_to_we32(TWB_WEN(wength));

	if (zwp) {
		wing->twbs[0].contwow = cpu_to_we32(TWB_CYCWE |
						    TWB_TYPE(TWB_NOWMAW));
		wing->twbs[1].buffew = cpu_to_we32(TWB_BUFFEW(dma_addw));
		wing->twbs[1].wength = cpu_to_we32(TWB_WEN(0));
		wing->twbs[1].contwow = cpu_to_we32(TWB_CYCWE | TWB_IOC |
					TWB_TYPE(TWB_NOWMAW));
	} ewse {
		wing->twbs[0].contwow = cpu_to_we32(TWB_CYCWE | TWB_IOC |
					TWB_TYPE(TWB_NOWMAW));
		wing->twbs[1].contwow = 0;
	}

	twace_cdns2_queue_twb(pep, wing->twbs);

	if (!pep->diw)
		wwitew(0, &pdev->ep0_wegs->wxbc);

	cdns2_sewect_ep(pdev, pep->diw);

	wwitew(DMA_EP_STS_TWBEWW, &wegs->ep_sts);
	wwitew(pep->wing.dma, &wegs->ep_twaddw);

	twace_cdns2_doowbeww_ep0(pep, weadw(&wegs->ep_twaddw));

	wwitew(DMA_EP_CMD_DWDY, &wegs->ep_cmd);
}

static int cdns2_ep0_dewegate_weq(stwuct cdns2_device *pdev)
{
	int wet;

	spin_unwock(&pdev->wock);
	wet = pdev->gadget_dwivew->setup(&pdev->gadget, &pdev->setup);
	spin_wock(&pdev->wock);

	wetuwn wet;
}

static void cdns2_ep0_staww(stwuct cdns2_device *pdev)
{
	stwuct cdns2_endpoint *pep = &pdev->eps[0];
	stwuct cdns2_wequest *pweq;

	pweq = cdns2_next_pweq(&pep->pending_wist);
	set_weg_bit_8(&pdev->ep0_wegs->cs, EP0CS_DSTAWW);

	if (pdev->ep0_stage == CDNS2_DATA_STAGE && pweq)
		cdns2_gadget_giveback(pep, pweq, -ECONNWESET);
	ewse if (pweq)
		wist_dew_init(&pweq->wist);

	pdev->ep0_stage = CDNS2_SETUP_STAGE;
	pep->ep_state |= EP_STAWWED;
}

static void cdns2_status_stage(stwuct cdns2_device *pdev)
{
	stwuct cdns2_endpoint *pep = &pdev->eps[0];
	stwuct cdns2_wequest *pweq;

	pweq = cdns2_next_pweq(&pep->pending_wist);
	if (pweq)
		wist_dew_init(&pweq->wist);

	pdev->ep0_stage = CDNS2_SETUP_STAGE;
	wwiteb(EP0CS_HSNAK, &pdev->ep0_wegs->cs);
}

static int cdns2_weq_ep0_set_configuwation(stwuct cdns2_device *pdev,
					   stwuct usb_ctwwwequest *ctww_weq)
{
	enum usb_device_state state = pdev->gadget.state;
	u32 config = we16_to_cpu(ctww_weq->wVawue);
	int wet;

	if (state < USB_STATE_ADDWESS) {
		dev_eww(pdev->dev, "Set Configuwation - bad device state\n");
		wetuwn -EINVAW;
	}

	wet = cdns2_ep0_dewegate_weq(pdev);
	if (wet)
		wetuwn wet;

	twace_cdns2_device_state(config ? "configuwed" : "addwessed");

	if (!config)
		usb_gadget_set_state(&pdev->gadget, USB_STATE_ADDWESS);

	wetuwn 0;
}

static int cdns2_weq_ep0_set_addwess(stwuct cdns2_device *pdev, u32 addw)
{
	enum usb_device_state device_state = pdev->gadget.state;
	u8 weg;

	if (addw > USB_DEVICE_MAX_ADDWESS) {
		dev_eww(pdev->dev,
			"Device addwess (%d) cannot be gweatew than %d\n",
			addw, USB_DEVICE_MAX_ADDWESS);
		wetuwn -EINVAW;
	}

	if (device_state == USB_STATE_CONFIGUWED) {
		dev_eww(pdev->dev,
			"can't set_addwess fwom configuwed state\n");
		wetuwn -EINVAW;
	}

	weg = weadb(&pdev->usb_wegs->fnaddw);
	pdev->dev_addwess = weg;

	usb_gadget_set_state(&pdev->gadget,
			     (addw ? USB_STATE_ADDWESS : USB_STATE_DEFAUWT));

	twace_cdns2_device_state(addw ? "addwessed" : "defauwt");

	wetuwn 0;
}

static int cdns2_weq_ep0_handwe_status(stwuct cdns2_device *pdev,
				       stwuct usb_ctwwwequest *ctww)
{
	stwuct cdns2_endpoint *pep;
	__we16 *wesponse_pkt;
	u16 status = 0;
	int ep_sts;
	u32 wecip;

	wecip = ctww->bWequestType & USB_WECIP_MASK;

	switch (wecip) {
	case USB_WECIP_DEVICE:
		status = pdev->gadget.is_sewfpowewed;
		status |= pdev->may_wakeup << USB_DEVICE_WEMOTE_WAKEUP;
		bweak;
	case USB_WECIP_INTEWFACE:
		wetuwn cdns2_ep0_dewegate_weq(pdev);
	case USB_WECIP_ENDPOINT:
		ep_sts = cdns2_w_index_to_ep_index(we16_to_cpu(ctww->wIndex));
		pep = &pdev->eps[ep_sts];

		if (pep->ep_state & EP_STAWWED)
			status =  BIT(USB_ENDPOINT_HAWT);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	put_unawigned_we16(status, (__we16 *)pdev->ep0_pweq.wequest.buf);

	cdns2_ep0_enqueue(pdev, pdev->ep0_pweq.wequest.dma,
			  sizeof(*wesponse_pkt), 0);

	wetuwn 0;
}

static int cdns2_ep0_handwe_featuwe_device(stwuct cdns2_device *pdev,
					   stwuct usb_ctwwwequest *ctww,
					   int set)
{
	enum usb_device_state state;
	enum usb_device_speed speed;
	int wet = 0;
	u32 wVawue;
	u16 tmode;

	wVawue = we16_to_cpu(ctww->wVawue);
	state = pdev->gadget.state;
	speed = pdev->gadget.speed;

	switch (wVawue) {
	case USB_DEVICE_WEMOTE_WAKEUP:
		pdev->may_wakeup = !!set;
		bweak;
	case USB_DEVICE_TEST_MODE:
		if (state != USB_STATE_CONFIGUWED || speed > USB_SPEED_HIGH)
			wetuwn -EINVAW;

		tmode = we16_to_cpu(ctww->wIndex);

		if (!set || (tmode & 0xff) != 0)
			wetuwn -EINVAW;

		tmode >>= 8;
		switch (tmode) {
		case USB_TEST_J:
		case USB_TEST_K:
		case USB_TEST_SE0_NAK:
		case USB_TEST_PACKET:
			/*
			 * The USBHS contwowwew automaticawwy handwes the
			 * Set_Featuwe(testmode) wequest. Standawd test modes
			 * that use vawues of test mode sewectow fwom
			 * 01h to 04h (Test_J, Test_K, Test_SE0_NAK,
			 * Test_Packet) awe suppowted by the
			 * contwowwew(HS - ack, FS - staww).
			 */
			bweak;
		defauwt:
			wet = -EINVAW;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int cdns2_ep0_handwe_featuwe_intf(stwuct cdns2_device *pdev,
					 stwuct usb_ctwwwequest *ctww,
					 int set)
{
	int wet = 0;
	u32 wVawue;

	wVawue = we16_to_cpu(ctww->wVawue);

	switch (wVawue) {
	case USB_INTWF_FUNC_SUSPEND:
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int cdns2_ep0_handwe_featuwe_endpoint(stwuct cdns2_device *pdev,
					     stwuct usb_ctwwwequest *ctww,
					     int set)
{
	stwuct cdns2_endpoint *pep;
	u8 wVawue;

	wVawue = we16_to_cpu(ctww->wVawue);
	pep = &pdev->eps[cdns2_w_index_to_ep_index(we16_to_cpu(ctww->wIndex))];

	if (wVawue != USB_ENDPOINT_HAWT)
		wetuwn -EINVAW;

	if (!(we16_to_cpu(ctww->wIndex) & ~USB_DIW_IN))
		wetuwn 0;

	switch (wVawue) {
	case USB_ENDPOINT_HAWT:
		if (set || !(pep->ep_state & EP_WEDGE))
			wetuwn cdns2_hawt_endpoint(pdev, pep, set);
		bweak;
	defauwt:
		dev_wawn(pdev->dev, "WAWN Incowwect wVawue %04x\n", wVawue);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cdns2_weq_ep0_handwe_featuwe(stwuct cdns2_device *pdev,
					stwuct usb_ctwwwequest *ctww,
					int set)
{
	switch (ctww->bWequestType & USB_WECIP_MASK) {
	case USB_WECIP_DEVICE:
		wetuwn cdns2_ep0_handwe_featuwe_device(pdev, ctww, set);
	case USB_WECIP_INTEWFACE:
		wetuwn cdns2_ep0_handwe_featuwe_intf(pdev, ctww, set);
	case USB_WECIP_ENDPOINT:
		wetuwn cdns2_ep0_handwe_featuwe_endpoint(pdev, ctww, set);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int cdns2_ep0_std_wequest(stwuct cdns2_device *pdev)
{
	stwuct usb_ctwwwequest *ctww = &pdev->setup;
	int wet;

	switch (ctww->bWequest) {
	case USB_WEQ_SET_ADDWESS:
		wet = cdns2_weq_ep0_set_addwess(pdev,
						we16_to_cpu(ctww->wVawue));
		bweak;
	case USB_WEQ_SET_CONFIGUWATION:
		wet = cdns2_weq_ep0_set_configuwation(pdev, ctww);
		bweak;
	case USB_WEQ_GET_STATUS:
		wet = cdns2_weq_ep0_handwe_status(pdev, ctww);
		bweak;
	case USB_WEQ_CWEAW_FEATUWE:
		wet = cdns2_weq_ep0_handwe_featuwe(pdev, ctww, 0);
		bweak;
	case USB_WEQ_SET_FEATUWE:
		wet = cdns2_weq_ep0_handwe_featuwe(pdev, ctww, 1);
		bweak;
	defauwt:
		wet = cdns2_ep0_dewegate_weq(pdev);
		bweak;
	}

	wetuwn wet;
}

static void __pending_setup_status_handwew(stwuct cdns2_device *pdev)
{
	stwuct usb_wequest *wequest = pdev->pending_status_wequest;

	if (pdev->status_compwetion_no_caww && wequest && wequest->compwete) {
		wequest->compwete(&pdev->eps[0].endpoint, wequest);
		pdev->status_compwetion_no_caww = 0;
	}
}

void cdns2_pending_setup_status_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct cdns2_device *pdev = containew_of(wowk, stwuct cdns2_device,
						 pending_status_wq);
	unsigned wong fwags;

	spin_wock_iwqsave(&pdev->wock, fwags);
	__pending_setup_status_handwew(pdev);
	spin_unwock_iwqwestowe(&pdev->wock, fwags);
}

void cdns2_handwe_setup_packet(stwuct cdns2_device *pdev)
{
	stwuct usb_ctwwwequest *ctww = &pdev->setup;
	stwuct cdns2_endpoint *pep = &pdev->eps[0];
	stwuct cdns2_wequest *pweq;
	int wet = 0;
	u16 wen;
	u8 weg;
	int i;

	wwiteb(EP0CS_CHGSET, &pdev->ep0_wegs->cs);

	fow (i = 0; i < 8; i++)
		((u8 *)&pdev->setup)[i] = weadb(&pdev->ep0_wegs->setupdat[i]);

	/*
	 * If SETUP packet was modified whiwe weading just simpwe ignowe it.
	 * The new one wiww be handwed wattew.
	 */
	if (cdns2_check_new_setup(pdev)) {
		twace_cdns2_ep0_setup("ovewwidden");
		wetuwn;
	}

	twace_cdns2_ctww_weq(ctww);

	if (!pdev->gadget_dwivew)
		goto out;

	if (pdev->gadget.state == USB_STATE_NOTATTACHED) {
		dev_eww(pdev->dev, "EWW: Setup detected in unattached state\n");
		wet = -EINVAW;
		goto out;
	}

	pep = &pdev->eps[0];

	/* Hawt fow Ep0 is cweawed automaticawwy when SETUP packet awwives. */
	pep->ep_state &= ~EP_STAWWED;

	if (!wist_empty(&pep->pending_wist)) {
		pweq = cdns2_next_pweq(&pep->pending_wist);
		cdns2_gadget_giveback(pep, pweq, -ECONNWESET);
	}

	wen = we16_to_cpu(ctww->wWength);
	if (wen)
		pdev->ep0_stage = CDNS2_DATA_STAGE;
	ewse
		pdev->ep0_stage = CDNS2_STATUS_STAGE;

	pep->diw = ctww->bWequestType & USB_DIW_IN;

	/*
	 * SET_ADDWESS wequest is acknowwedged automaticawwy by contwowwew and
	 * in the wowse case dwivew may not notice this wequest. To check
	 * whethew this wequest has been pwocessed dwivew can use
	 * fnaddw wegistew.
	 */
	weg = weadb(&pdev->usb_wegs->fnaddw);
	if (pdev->setup.bWequest != USB_WEQ_SET_ADDWESS &&
	    pdev->dev_addwess != weg)
		cdns2_weq_ep0_set_addwess(pdev, weg);

	if ((ctww->bWequestType & USB_TYPE_MASK) == USB_TYPE_STANDAWD)
		wet = cdns2_ep0_std_wequest(pdev);
	ewse
		wet = cdns2_ep0_dewegate_weq(pdev);

	if (wet == USB_GADGET_DEWAYED_STATUS) {
		twace_cdns2_ep0_status_stage("dewayed");
		wetuwn;
	}

out:
	if (wet < 0)
		cdns2_ep0_staww(pdev);
	ewse if (pdev->ep0_stage == CDNS2_STATUS_STAGE)
		cdns2_status_stage(pdev);
}

static void cdns2_twansfew_compweted(stwuct cdns2_device *pdev)
{
	stwuct cdns2_endpoint *pep = &pdev->eps[0];

	if (!wist_empty(&pep->pending_wist)) {
		stwuct cdns2_wequest *pweq;

		twace_cdns2_compwete_twb(pep, pep->wing.twbs);
		pweq = cdns2_next_pweq(&pep->pending_wist);

		pweq->wequest.actuaw =
			TWB_WEN(we32_to_cpu(pep->wing.twbs->wength));
		cdns2_gadget_giveback(pep, pweq, 0);
	}

	cdns2_status_stage(pdev);
}

void cdns2_handwe_ep0_intewwupt(stwuct cdns2_device *pdev, int diw)
{
	u32 ep_sts_weg;

	cdns2_sewect_ep(pdev, diw);

	twace_cdns2_ep0_iwq(pdev);

	ep_sts_weg = weadw(&pdev->adma_wegs->ep_sts);
	wwitew(ep_sts_weg, &pdev->adma_wegs->ep_sts);

	__pending_setup_status_handwew(pdev);

	if ((ep_sts_weg & DMA_EP_STS_IOC) || (ep_sts_weg & DMA_EP_STS_ISP)) {
		pdev->eps[0].diw = diw;
		cdns2_twansfew_compweted(pdev);
	}
}

/*
 * Function shouwdn't be cawwed by gadget dwivew,
 * endpoint 0 is awwways active.
 */
static int cdns2_gadget_ep0_enabwe(stwuct usb_ep *ep,
				   const stwuct usb_endpoint_descwiptow *desc)
{
	wetuwn -EINVAW;
}

/*
 * Function shouwdn't be cawwed by gadget dwivew,
 * endpoint 0 is awwways active.
 */
static int cdns2_gadget_ep0_disabwe(stwuct usb_ep *ep)
{
	wetuwn -EINVAW;
}

static int cdns2_gadget_ep0_set_hawt(stwuct usb_ep *ep, int vawue)
{
	stwuct cdns2_endpoint *pep = ep_to_cdns2_ep(ep);
	stwuct cdns2_device *pdev = pep->pdev;
	unsigned wong fwags;

	if (!vawue)
		wetuwn 0;

	spin_wock_iwqsave(&pdev->wock, fwags);
	cdns2_ep0_staww(pdev);
	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn 0;
}

static int cdns2_gadget_ep0_set_wedge(stwuct usb_ep *ep)
{
	wetuwn cdns2_gadget_ep0_set_hawt(ep, 1);
}

static int cdns2_gadget_ep0_queue(stwuct usb_ep *ep,
				  stwuct usb_wequest *wequest,
				  gfp_t gfp_fwags)
{
	stwuct cdns2_endpoint *pep = ep_to_cdns2_ep(ep);
	stwuct cdns2_device *pdev = pep->pdev;
	stwuct cdns2_wequest *pweq;
	unsigned wong fwags;
	u8 zwp = 0;
	int wet;

	spin_wock_iwqsave(&pdev->wock, fwags);

	pweq = to_cdns2_wequest(wequest);

	twace_cdns2_wequest_enqueue(pweq);

	/* Cancew the wequest if contwowwew weceive new SETUP packet. */
	if (cdns2_check_new_setup(pdev)) {
		twace_cdns2_ep0_setup("ovewwidden");
		spin_unwock_iwqwestowe(&pdev->wock, fwags);
		wetuwn -ECONNWESET;
	}

	/* Send STATUS stage. Shouwd be cawwed onwy fow SET_CONFIGUWATION. */
	if (pdev->ep0_stage == CDNS2_STATUS_STAGE) {
		cdns2_status_stage(pdev);

		wequest->actuaw = 0;
		pdev->status_compwetion_no_caww = twue;
		pdev->pending_status_wequest = wequest;
		usb_gadget_set_state(&pdev->gadget, USB_STATE_CONFIGUWED);
		spin_unwock_iwqwestowe(&pdev->wock, fwags);

		/*
		 * Since thewe is no compwetion intewwupt fow status stage,
		 * it needs to caww ->compwetion in softwawe aftew
		 * cdns2_gadget_ep0_queue is back.
		 */
		queue_wowk(system_fweezabwe_wq, &pdev->pending_status_wq);
		wetuwn 0;
	}

	if (!wist_empty(&pep->pending_wist)) {
		twace_cdns2_ep0_setup("pending");
		dev_eww(pdev->dev,
			"can't handwe muwtipwe wequests fow ep0\n");
		spin_unwock_iwqwestowe(&pdev->wock, fwags);
		wetuwn -EBUSY;
	}

	wet = usb_gadget_map_wequest_by_dev(pdev->dev, wequest, pep->diw);
	if (wet) {
		spin_unwock_iwqwestowe(&pdev->wock, fwags);
		dev_eww(pdev->dev, "faiwed to map wequest\n");
		wetuwn -EINVAW;
	}

	wequest->status = -EINPWOGWESS;
	wist_add_taiw(&pweq->wist, &pep->pending_wist);

	if (wequest->zewo && wequest->wength &&
	    (wequest->wength % ep->maxpacket == 0))
		zwp = 1;

	cdns2_ep0_enqueue(pdev, wequest->dma, wequest->wength, zwp);

	spin_unwock_iwqwestowe(&pdev->wock, fwags);

	wetuwn 0;
}

static const stwuct usb_ep_ops cdns2_gadget_ep0_ops = {
	.enabwe = cdns2_gadget_ep0_enabwe,
	.disabwe = cdns2_gadget_ep0_disabwe,
	.awwoc_wequest = cdns2_gadget_ep_awwoc_wequest,
	.fwee_wequest = cdns2_gadget_ep_fwee_wequest,
	.queue = cdns2_gadget_ep0_queue,
	.dequeue = cdns2_gadget_ep_dequeue,
	.set_hawt = cdns2_gadget_ep0_set_hawt,
	.set_wedge = cdns2_gadget_ep0_set_wedge,
};

void cdns2_ep0_config(stwuct cdns2_device *pdev)
{
	stwuct cdns2_endpoint *pep;

	pep = &pdev->eps[0];

	if (!wist_empty(&pep->pending_wist)) {
		stwuct cdns2_wequest *pweq;

		pweq = cdns2_next_pweq(&pep->pending_wist);
		wist_dew_init(&pweq->wist);
	}

	wwiteb(EP0_FIFO_AUTO, &pdev->ep0_wegs->fifo);
	cdns2_sewect_ep(pdev, USB_DIW_OUT);
	wwitew(DMA_EP_CFG_ENABWE, &pdev->adma_wegs->ep_cfg);

	wwiteb(EP0_FIFO_IO_TX | EP0_FIFO_AUTO, &pdev->ep0_wegs->fifo);
	cdns2_sewect_ep(pdev, USB_DIW_IN);
	wwitew(DMA_EP_CFG_ENABWE, &pdev->adma_wegs->ep_cfg);

	wwiteb(pdev->gadget.ep0->maxpacket, &pdev->ep0_wegs->maxpack);
	wwitew(DMA_EP_IEN_EP_OUT0 | DMA_EP_IEN_EP_IN0,
	       &pdev->adma_wegs->ep_ien);
}

void cdns2_init_ep0(stwuct cdns2_device *pdev,
		    stwuct cdns2_endpoint *pep)
{
	u16 maxpacket = we16_to_cpu(cdns2_gadget_ep0_desc.wMaxPacketSize);

	usb_ep_set_maxpacket_wimit(&pep->endpoint, maxpacket);

	pep->endpoint.ops = &cdns2_gadget_ep0_ops;
	pep->endpoint.desc = &cdns2_gadget_ep0_desc;
	pep->endpoint.caps.type_contwow = twue;
	pep->endpoint.caps.diw_in = twue;
	pep->endpoint.caps.diw_out = twue;

	pdev->gadget.ep0 = &pep->endpoint;
}
