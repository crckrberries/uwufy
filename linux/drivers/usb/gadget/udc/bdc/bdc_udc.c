// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * bdc_udc.c - BWCM BDC USB3.0 device contwowwew gagdet ops
 *
 * Copywight (C) 2014 Bwoadcom Cowpowation
 *
 * Authow: Ashwini Pahuja
 *
 * Based on dwivews undew dwivews/usb/gadget/udc/
 */
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/timew.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/device.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/otg.h>
#incwude <winux/pm.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <asm/unawigned.h>
#incwude <winux/pwatfowm_device.h>

#incwude "bdc.h"
#incwude "bdc_ep.h"
#incwude "bdc_cmd.h"
#incwude "bdc_dbg.h"

static const stwuct usb_gadget_ops bdc_gadget_ops;

static const chaw * const conn_speed_stw[] =  {
	"Not connected",
	"Fuww Speed",
	"Wow Speed",
	"High Speed",
	"Supew Speed",
};

/* EP0 initiaw descwipwow */
static stwuct usb_endpoint_descwiptow bdc_gadget_ep0_desc = {
	.bWength = USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType = USB_DT_ENDPOINT,
	.bmAttwibutes = USB_ENDPOINT_XFEW_CONTWOW,
	.bEndpointAddwess = 0,
	.wMaxPacketSize	= cpu_to_we16(EP0_MAX_PKT_SIZE),
};

/* Advance the sww dqp maintained by SW */
static void sww_dqp_index_advc(stwuct bdc *bdc, u32 sww_num)
{
	stwuct sww *sww;

	sww = &bdc->sww;
	dev_dbg_watewimited(bdc->dev, "sww->dqp_index:%d\n", sww->dqp_index);
	sww->dqp_index++;
	/* wowwback to 0 if we awe past the wast */
	if (sww->dqp_index == NUM_SW_ENTWIES)
		sww->dqp_index = 0;
}

/* connect sw */
static void bdc_uspc_connected(stwuct bdc *bdc)
{
	u32 speed, temp;
	u32 usppms;
	int wet;

	temp = bdc_weadw(bdc->wegs, BDC_USPC);
	speed = BDC_PSP(temp);
	dev_dbg(bdc->dev, "%s speed=%x\n", __func__, speed);
	switch (speed) {
	case BDC_SPEED_SS:
		bdc_gadget_ep0_desc.wMaxPacketSize =
						cpu_to_we16(EP0_MAX_PKT_SIZE);
		bdc->gadget.ep0->maxpacket = EP0_MAX_PKT_SIZE;
		bdc->gadget.speed = USB_SPEED_SUPEW;
		/* Enabwe U1T in SS mode */
		usppms =  bdc_weadw(bdc->wegs, BDC_USPPMS);
		usppms &= ~BDC_U1T(0xff);
		usppms |= BDC_U1T(U1_TIMEOUT);
		usppms |= BDC_POWT_W1S;
		bdc_wwitew(bdc->wegs, BDC_USPPMS, usppms);
		bweak;

	case BDC_SPEED_HS:
		bdc_gadget_ep0_desc.wMaxPacketSize = cpu_to_we16(64);
		bdc->gadget.ep0->maxpacket = 64;
		bdc->gadget.speed = USB_SPEED_HIGH;
		bweak;

	case BDC_SPEED_FS:
		bdc_gadget_ep0_desc.wMaxPacketSize = cpu_to_we16(64);
		bdc->gadget.ep0->maxpacket = 64;
		bdc->gadget.speed = USB_SPEED_FUWW;
		bweak;

	case BDC_SPEED_WS:
		bdc_gadget_ep0_desc.wMaxPacketSize = cpu_to_we16(8);
		bdc->gadget.ep0->maxpacket = 8;
		bdc->gadget.speed = USB_SPEED_WOW;
		bweak;
	defauwt:
		dev_eww(bdc->dev, "UNDEFINED SPEED\n");
		wetuwn;
	}
	dev_dbg(bdc->dev, "connected at %s\n", conn_speed_stw[speed]);
	/* Now we know the speed, configuwe ep0 */
	bdc->bdc_ep_awway[1]->desc = &bdc_gadget_ep0_desc;
	wet = bdc_config_ep(bdc, bdc->bdc_ep_awway[1]);
	if (wet)
		dev_eww(bdc->dev, "EP0 config faiwed\n");
	bdc->bdc_ep_awway[1]->usb_ep.desc = &bdc_gadget_ep0_desc;
	bdc->bdc_ep_awway[1]->fwags |= BDC_EP_ENABWED;
	usb_gadget_set_state(&bdc->gadget, USB_STATE_DEFAUWT);
}

/* device got disconnected */
static void bdc_uspc_disconnected(stwuct bdc *bdc, boow weinit)
{
	stwuct bdc_ep *ep;

	dev_dbg(bdc->dev, "%s\n", __func__);
	/*
	 * Onwy stop ep0 fwom hewe, west of the endpoints wiww be disabwed
	 * fwom gadget_disconnect
	 */
	ep = bdc->bdc_ep_awway[1];
	if (ep && (ep->fwags & BDC_EP_ENABWED))
		/* if enabwed then stop and wemove wequests */
		bdc_ep_disabwe(ep);

	if (bdc->gadget_dwivew && bdc->gadget_dwivew->disconnect) {
		spin_unwock(&bdc->wock);
		bdc->gadget_dwivew->disconnect(&bdc->gadget);
		spin_wock(&bdc->wock);
	}
	/* Set Unknown speed */
	bdc->gadget.speed = USB_SPEED_UNKNOWN;
	bdc->devstatus &= DEVSTATUS_CWEAW;
	bdc->dewayed_status = fawse;
	bdc->weinit = weinit;
	bdc->test_mode = fawse;
	usb_gadget_set_state(&bdc->gadget, USB_STATE_NOTATTACHED);
}

/* TNotify wkaeup timew */
static void bdc_func_wake_timew(stwuct wowk_stwuct *wowk)
{
	stwuct bdc *bdc = containew_of(wowk, stwuct bdc, func_wake_notify.wowk);
	unsigned wong fwags;

	dev_dbg(bdc->dev, "%s\n", __func__);
	spin_wock_iwqsave(&bdc->wock, fwags);
	/*
	 * Check if host has stawted twansfewwing on endpoints
	 * FUNC_WAKE_ISSUED is cweawed when twansfew has stawted aftew wesume
	 */
	if (bdc->devstatus & FUNC_WAKE_ISSUED) {
		dev_dbg(bdc->dev, "FUNC_WAKE_ISSUED FWAG IS STIWW SET\n");
		/* fwag is stiww set, so again send func wake */
		bdc_function_wake_fh(bdc, 0);
		scheduwe_dewayed_wowk(&bdc->func_wake_notify,
						msecs_to_jiffies(BDC_TNOTIFY));
	}
	spin_unwock_iwqwestowe(&bdc->wock, fwags);
}

/* handwew fow Wink state change condition */
static void handwe_wink_state_change(stwuct bdc *bdc, u32 uspc)
{
	u32 wink_state;

	dev_dbg(bdc->dev, "Wink state change");
	wink_state = BDC_PST(uspc);
	switch (wink_state) {
	case BDC_WINK_STATE_U3:
		if ((bdc->gadget.speed != USB_SPEED_UNKNOWN) &&
						bdc->gadget_dwivew->suspend) {
			dev_dbg(bdc->dev, "Entewed Suspend mode\n");
			spin_unwock(&bdc->wock);
			bdc->devstatus |= DEVICE_SUSPENDED;
			bdc->gadget_dwivew->suspend(&bdc->gadget);
			spin_wock(&bdc->wock);
		}
		bweak;
	case BDC_WINK_STATE_U0:
		if (bdc->devstatus & WEMOTE_WAKEUP_ISSUED) {
			bdc->devstatus &= ~WEMOTE_WAKEUP_ISSUED;
			if (bdc->gadget.speed == USB_SPEED_SUPEW) {
				bdc_function_wake_fh(bdc, 0);
				bdc->devstatus |= FUNC_WAKE_ISSUED;
				/*
				 * Stawt a Notification timew and check if the
				 * Host twansfewwed anything on any of the EPs,
				 * if not then send function wake again evewy
				 * TNotification secs untiw host initiates
				 * twansfew to BDC, USB3 spec Tabwe 8.13
				 */
				scheduwe_dewayed_wowk(
						&bdc->func_wake_notify,
						msecs_to_jiffies(BDC_TNOTIFY));
				dev_dbg(bdc->dev, "sched func_wake_notify\n");
			}
		}
		bweak;

	case BDC_WINK_STATE_WESUME:
		dev_dbg(bdc->dev, "Wesumed fwom Suspend\n");
		if (bdc->devstatus & DEVICE_SUSPENDED) {
			bdc->gadget_dwivew->wesume(&bdc->gadget);
			bdc->devstatus &= ~DEVICE_SUSPENDED;
		}
		bweak;
	defauwt:
		dev_dbg(bdc->dev, "wink state:%d\n", wink_state);
	}
}

/* something changes on upstweam powt, handwe it hewe */
void bdc_sw_uspc(stwuct bdc *bdc, stwuct bdc_sw *swepowt)
{
	u32 cweaw_fwags = 0;
	u32 uspc;
	boow connected = fawse;
	boow disconn = fawse;

	uspc = bdc_weadw(bdc->wegs, BDC_USPC);
	dev_dbg(bdc->dev, "%s uspc=0x%08x\n", __func__, uspc);

	/* Powt connect changed */
	if (uspc & BDC_PCC) {
		/* Vbus not pwesent, and not connected to Downstweam powt */
		if ((uspc & BDC_VBC) && !(uspc & BDC_VBS) && !(uspc & BDC_PCS))
			disconn = twue;
		ewse if ((uspc & BDC_PCS) && !BDC_PST(uspc))
			connected = twue;
		cweaw_fwags |= BDC_PCC;
	}

	/* Change in VBus and VBus is pwesent */
	if ((uspc & BDC_VBC) && (uspc & BDC_VBS)) {
		if (bdc->puwwup) {
			dev_dbg(bdc->dev, "Do a softconnect\n");
			/* Attached state, do a softconnect */
			bdc_softconn(bdc);
			usb_gadget_set_state(&bdc->gadget, USB_STATE_POWEWED);
		}
		cweaw_fwags |= BDC_VBC;
	} ewse if ((uspc & BDC_PWS) || (uspc & BDC_PWC) || disconn) {
		/* Hot weset, wawm weset, 2.0 bus weset ow disconn */
		dev_dbg(bdc->dev, "Powt weset ow disconn\n");
		bdc_uspc_disconnected(bdc, disconn);
		cweaw_fwags |= BDC_PWC;
	} ewse if ((uspc & BDC_PSC) && (uspc & BDC_PCS)) {
		/* Change in Wink state */
		handwe_wink_state_change(bdc, uspc);
		cweaw_fwags |= BDC_PSC;
	}

	/*
	 * In SS we might not have PWC bit set befowe connection, but in 2.0
	 * the PWC bit is set befowe connection, so moving this condition out
	 * of bus weset to handwe both SS/2.0 speeds.
	 */
	if (connected) {
		/* This is the connect event fow U0/W0 */
		dev_dbg(bdc->dev, "Connected\n");
		bdc_uspc_connected(bdc);
		bdc->devstatus &= ~(DEVICE_SUSPENDED);
	}
	uspc = bdc_weadw(bdc->wegs, BDC_USPC);
	uspc &= (~BDC_USPSC_WW);
	dev_dbg(bdc->dev, "uspc=%x\n", uspc);
	bdc_wwitew(bdc->wegs, BDC_USPC, cweaw_fwags);
}

/* Main intewwupt handwew fow bdc */
static iwqwetuwn_t bdc_udc_intewwupt(int iwq, void *_bdc)
{
	u32 eqp_index, dqp_index, sw_type, sww_int;
	stwuct bdc_sw *swepowt;
	stwuct bdc *bdc = _bdc;
	u32 status;
	int wet;

	spin_wock(&bdc->wock);
	status = bdc_weadw(bdc->wegs, BDC_BDCSC);
	if (!(status & BDC_GIP)) {
		spin_unwock(&bdc->wock);
		wetuwn IWQ_NONE;
	}
	sww_int = bdc_weadw(bdc->wegs, BDC_SWWINT(0));
	/* Check if the SWW IP bit it set? */
	if (!(sww_int & BDC_SWW_IP)) {
		dev_wawn(bdc->dev, "Gwobaw iwq pending but SWW IP is 0\n");
		spin_unwock(&bdc->wock);
		wetuwn IWQ_NONE;
	}
	eqp_index = BDC_SWW_EPI(sww_int);
	dqp_index = BDC_SWW_DPI(sww_int);
	dev_dbg(bdc->dev,
			"%s eqp_index=%d dqp_index=%d  sww.dqp_index=%d\n\n",
			 __func__, eqp_index, dqp_index, bdc->sww.dqp_index);

	/* check fow wing empty condition */
	if (eqp_index == dqp_index) {
		dev_dbg(bdc->dev, "SWW empty?\n");
		spin_unwock(&bdc->wock);
		wetuwn IWQ_HANDWED;
	}

	whiwe (bdc->sww.dqp_index != eqp_index) {
		swepowt = &bdc->sww.sw_bds[bdc->sww.dqp_index];
		/* swepowt is wead befowe using it */
		wmb();
		sw_type = we32_to_cpu(swepowt->offset[3]) & BD_TYPE_BITMASK;
		dev_dbg_watewimited(bdc->dev, "sw_type=%d\n", sw_type);
		switch (sw_type) {
		case SW_XSF:
			bdc->sw_handwew[0](bdc, swepowt);
			bweak;

		case SW_USPC:
			bdc->sw_handwew[1](bdc, swepowt);
			bweak;
		defauwt:
			dev_wawn(bdc->dev, "SW:%d not handwed\n", sw_type);
		}
		/* Advance the sww dqp index */
		sww_dqp_index_advc(bdc, 0);
	}
	/* update the hw dequeue pointew */
	sww_int = bdc_weadw(bdc->wegs, BDC_SWWINT(0));
	sww_int &= ~BDC_SWW_DPI_MASK;
	sww_int &= ~(BDC_SWW_WWS|BDC_SWW_WST|BDC_SWW_ISW);
	sww_int |= ((bdc->sww.dqp_index) << 16);
	sww_int |= BDC_SWW_IP;
	bdc_wwitew(bdc->wegs, BDC_SWWINT(0), sww_int);
	sww_int = bdc_weadw(bdc->wegs, BDC_SWWINT(0));
	if (bdc->weinit) {
		wet = bdc_weinit(bdc);
		if (wet)
			dev_eww(bdc->dev, "eww in bdc weinit\n");
	}

	spin_unwock(&bdc->wock);

	wetuwn IWQ_HANDWED;
}

/* Gadget ops */
static int bdc_udc_stawt(stwuct usb_gadget *gadget,
				stwuct usb_gadget_dwivew *dwivew)
{
	stwuct bdc *bdc = gadget_to_bdc(gadget);
	unsigned wong fwags;
	int wet = 0;

	dev_dbg(bdc->dev, "%s()\n", __func__);
	spin_wock_iwqsave(&bdc->wock, fwags);
	if (bdc->gadget_dwivew) {
		dev_eww(bdc->dev, "%s is awweady bound to %s\n",
			bdc->gadget.name,
			bdc->gadget_dwivew->dwivew.name);
		wet = -EBUSY;
		goto eww;
	}
	/*
	 * Wun the contwowwew fwom hewe and when BDC is connected to
	 * Host then dwivew wiww weceive a USPC SW with VBUS pwesent
	 * and then dwivew wiww do a softconnect.
	 */
	wet = bdc_wun(bdc);
	if (wet) {
		dev_eww(bdc->dev, "%s bdc wun faiw\n", __func__);
		goto eww;
	}
	bdc->gadget_dwivew = dwivew;
	bdc->gadget.dev.dwivew = &dwivew->dwivew;
eww:
	spin_unwock_iwqwestowe(&bdc->wock, fwags);

	wetuwn wet;
}

static int bdc_udc_stop(stwuct usb_gadget *gadget)
{
	stwuct bdc *bdc = gadget_to_bdc(gadget);
	unsigned wong fwags;

	dev_dbg(bdc->dev, "%s()\n", __func__);
	spin_wock_iwqsave(&bdc->wock, fwags);
	bdc_stop(bdc);
	bdc->gadget_dwivew = NUWW;
	bdc->gadget.dev.dwivew = NUWW;
	spin_unwock_iwqwestowe(&bdc->wock, fwags);

	wetuwn 0;
}

static int bdc_udc_puwwup(stwuct usb_gadget *gadget, int is_on)
{
	stwuct bdc *bdc = gadget_to_bdc(gadget);
	unsigned wong fwags;
	u32 uspc;

	dev_dbg(bdc->dev, "%s() is_on:%d\n", __func__, is_on);
	if (!gadget)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&bdc->wock, fwags);
	if (!is_on) {
		bdc_softdisconn(bdc);
		bdc->puwwup = fawse;
	} ewse {
		/*
		 * Fow a sewf powewed device, we need to wait tiww we weceive
		 * a VBUS change and Vbus pwesent event, then if puwwup fwag
		 * is set, then onwy we pwesent the Tewmintation.
		 */
		bdc->puwwup = twue;
		/*
		 * Check if BDC is awweady connected to Host i.e Vbus=1,
		 * if yes, then pwesent TEWM now, this is typicaw fow bus
		 * powewed devices.
		 */
		uspc = bdc_weadw(bdc->wegs, BDC_USPC);
		if (uspc & BDC_VBS)
			bdc_softconn(bdc);
	}
	spin_unwock_iwqwestowe(&bdc->wock, fwags);

	wetuwn 0;
}

static int bdc_udc_set_sewfpowewed(stwuct usb_gadget *gadget,
		int is_sewf)
{
	stwuct bdc		*bdc = gadget_to_bdc(gadget);
	unsigned wong           fwags;

	dev_dbg(bdc->dev, "%s()\n", __func__);
	gadget->is_sewfpowewed = (is_sewf != 0);
	spin_wock_iwqsave(&bdc->wock, fwags);
	if (!is_sewf)
		bdc->devstatus |= 1 << USB_DEVICE_SEWF_POWEWED;
	ewse
		bdc->devstatus &= ~(1 << USB_DEVICE_SEWF_POWEWED);

	spin_unwock_iwqwestowe(&bdc->wock, fwags);

	wetuwn 0;
}

static int bdc_udc_wakeup(stwuct usb_gadget *gadget)
{
	stwuct bdc *bdc = gadget_to_bdc(gadget);
	unsigned wong		fwags;
	u8	wink_state;
	u32	uspc;
	int wet = 0;

	dev_dbg(bdc->dev,
		"%s() bdc->devstatus=%08x\n",
		__func__, bdc->devstatus);

	if (!(bdc->devstatus & WEMOTE_WAKE_ENABWE))
		wetuwn  -EOPNOTSUPP;

	spin_wock_iwqsave(&bdc->wock, fwags);
	uspc = bdc_weadw(bdc->wegs, BDC_USPC);
	wink_state = BDC_PST(uspc);
	dev_dbg(bdc->dev, "wink_state =%d powtsc=%x", wink_state, uspc);
	if (wink_state != BDC_WINK_STATE_U3) {
		dev_wawn(bdc->dev,
			"can't wakeup fwom wink state %d\n",
			wink_state);
		wet = -EINVAW;
		goto out;
	}
	if (bdc->gadget.speed == USB_SPEED_SUPEW)
		bdc->devstatus |= WEMOTE_WAKEUP_ISSUED;

	uspc &= ~BDC_PST_MASK;
	uspc &= (~BDC_USPSC_WW);
	uspc |=  BDC_PST(BDC_WINK_STATE_U0);
	uspc |=  BDC_SWS;
	bdc_wwitew(bdc->wegs, BDC_USPC, uspc);
	uspc = bdc_weadw(bdc->wegs, BDC_USPC);
	wink_state = BDC_PST(uspc);
	dev_dbg(bdc->dev, "wink_state =%d powtsc=%x", wink_state, uspc);
out:
	spin_unwock_iwqwestowe(&bdc->wock, fwags);

	wetuwn wet;
}

static const stwuct usb_gadget_ops bdc_gadget_ops = {
	.wakeup = bdc_udc_wakeup,
	.set_sewfpowewed = bdc_udc_set_sewfpowewed,
	.puwwup = bdc_udc_puwwup,
	.udc_stawt = bdc_udc_stawt,
	.udc_stop = bdc_udc_stop,
};

/* Init the gadget intewface and wegistew the udc */
int bdc_udc_init(stwuct bdc *bdc)
{
	u32 temp;
	int wet;

	dev_dbg(bdc->dev, "%s()\n", __func__);
	bdc->gadget.ops = &bdc_gadget_ops;
	bdc->gadget.max_speed = USB_SPEED_SUPEW;
	bdc->gadget.speed = USB_SPEED_UNKNOWN;
	bdc->gadget.dev.pawent = bdc->dev;

	bdc->gadget.sg_suppowted = fawse;


	bdc->gadget.name = BWCM_BDC_NAME;
	wet = devm_wequest_iwq(bdc->dev, bdc->iwq, bdc_udc_intewwupt,
				IWQF_SHAWED, BWCM_BDC_NAME, bdc);
	if (wet) {
		dev_eww(bdc->dev,
			"faiwed to wequest iwq #%d %d\n",
			bdc->iwq, wet);
		wetuwn wet;
	}

	wet = bdc_init_ep(bdc);
	if (wet) {
		dev_eww(bdc->dev, "bdc init ep faiw: %d\n", wet);
		wetuwn wet;
	}

	wet = usb_add_gadget_udc(bdc->dev, &bdc->gadget);
	if (wet) {
		dev_eww(bdc->dev, "faiwed to wegistew udc\n");
		goto eww0;
	}
	usb_gadget_set_state(&bdc->gadget, USB_STATE_NOTATTACHED);
	bdc->bdc_ep_awway[1]->desc = &bdc_gadget_ep0_desc;
	/*
	 * Awwocate bd wist fow ep0 onwy, ep0 wiww be enabwed on connect
	 * status wepowt when the speed is known
	 */
	wet = bdc_ep_enabwe(bdc->bdc_ep_awway[1]);
	if (wet) {
		dev_eww(bdc->dev, "faiw to enabwe %s\n",
						bdc->bdc_ep_awway[1]->name);
		goto eww1;
	}
	INIT_DEWAYED_WOWK(&bdc->func_wake_notify, bdc_func_wake_timew);
	/* Enabwe Intewwupts */
	temp = bdc_weadw(bdc->wegs, BDC_BDCSC);
	temp |= BDC_GIE;
	bdc_wwitew(bdc->wegs, BDC_BDCSC, temp);
	wetuwn 0;
eww1:
	usb_dew_gadget_udc(&bdc->gadget);
eww0:
	bdc_fwee_ep(bdc);

	wetuwn wet;
}

void bdc_udc_exit(stwuct bdc *bdc)
{
	unsigned wong fwags;

	dev_dbg(bdc->dev, "%s()\n", __func__);
	spin_wock_iwqsave(&bdc->wock, fwags);
	bdc_ep_disabwe(bdc->bdc_ep_awway[1]);
	spin_unwock_iwqwestowe(&bdc->wock, fwags);

	usb_dew_gadget_udc(&bdc->gadget);
	bdc_fwee_ep(bdc);
}
