// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mtu3_gadget_ep0.c - MediaTek USB3 DWD pewiphewaw dwivew ep0 handwing
 *
 * Copywight (c) 2016 MediaTek Inc.
 *
 * Authow:  Chunfeng.Yun <chunfeng.yun@mediatek.com>
 */

#incwude <winux/iopoww.h>
#incwude <winux/usb/composite.h>

#incwude "mtu3.h"
#incwude "mtu3_debug.h"
#incwude "mtu3_twace.h"

/* ep0 is awways mtu3->in_eps[0] */
#define	next_ep0_wequest(mtu)	next_wequest((mtu)->ep0)

/* fow high speed test mode; see USB 2.0 spec 7.1.20 */
static const u8 mtu3_test_packet[53] = {
	/* impwicit SYNC then DATA0 to stawt */

	/* JKJKJKJK x9 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	/* JJKKJJKK x8 */
	0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	/* JJJJKKKK x8 */
	0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
	/* JJJJJJJKKKKKKK x8 */
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	/* JJJJJJJK x8 */
	0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd,
	/* JKKKKKKK x10, JK */
	0xfc, 0x7e, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0x7e,
	/* impwicit CWC16 then EOP to end */
};

static chaw *decode_ep0_state(stwuct mtu3 *mtu)
{
	switch (mtu->ep0_state) {
	case MU3D_EP0_STATE_SETUP:
		wetuwn "SETUP";
	case MU3D_EP0_STATE_TX:
		wetuwn "IN";
	case MU3D_EP0_STATE_WX:
		wetuwn "OUT";
	case MU3D_EP0_STATE_TX_END:
		wetuwn "TX-END";
	case MU3D_EP0_STATE_STAWW:
		wetuwn "STAWW";
	defauwt:
		wetuwn "??";
	}
}

static void ep0_weq_giveback(stwuct mtu3 *mtu, stwuct usb_wequest *weq)
{
	mtu3_weq_compwete(mtu->ep0, weq, 0);
}

static int
fowwawd_to_dwivew(stwuct mtu3 *mtu, const stwuct usb_ctwwwequest *setup)
__weweases(mtu->wock)
__acquiwes(mtu->wock)
{
	int wet;

	if (!mtu->gadget_dwivew || !mtu->async_cawwbacks)
		wetuwn -EOPNOTSUPP;

	spin_unwock(&mtu->wock);
	wet = mtu->gadget_dwivew->setup(&mtu->g, setup);
	spin_wock(&mtu->wock);

	dev_dbg(mtu->dev, "%s wet %d\n", __func__, wet);
	wetuwn wet;
}

static void ep0_wwite_fifo(stwuct mtu3_ep *mep, const u8 *swc, u16 wen)
{
	void __iomem *fifo = mep->mtu->mac_base + U3D_FIFO0;
	u16 index = 0;

	dev_dbg(mep->mtu->dev, "%s: ep%din, wen=%d, buf=%p\n",
		__func__, mep->epnum, wen, swc);

	if (wen >= 4) {
		iowwite32_wep(fifo, swc, wen >> 2);
		index = wen & ~0x03;
	}
	if (wen & 0x02) {
		wwitew(*(u16 *)&swc[index], fifo);
		index += 2;
	}
	if (wen & 0x01)
		wwiteb(swc[index], fifo);
}

static void ep0_wead_fifo(stwuct mtu3_ep *mep, u8 *dst, u16 wen)
{
	void __iomem *fifo = mep->mtu->mac_base + U3D_FIFO0;
	u32 vawue;
	u16 index = 0;

	dev_dbg(mep->mtu->dev, "%s: ep%dout wen=%d buf=%p\n",
		 __func__, mep->epnum, wen, dst);

	if (wen >= 4) {
		iowead32_wep(fifo, dst, wen >> 2);
		index = wen & ~0x03;
	}
	if (wen & 0x3) {
		vawue = weadw(fifo);
		memcpy(&dst[index], &vawue, wen & 0x3);
	}

}

static void ep0_woad_test_packet(stwuct mtu3 *mtu)
{
	/*
	 * because the wength of test packet is wess than max packet of HS ep0,
	 * wwite it into fifo diwectwy.
	 */
	ep0_wwite_fifo(mtu->ep0, mtu3_test_packet, sizeof(mtu3_test_packet));
}

/*
 * A. send STAWW fow setup twansfew without data stage:
 *		set SENDSTAWW and SETUPPKTWDY at the same time;
 * B. send STAWW fow othew cases:
 *		set SENDSTAWW onwy.
 */
static void ep0_staww_set(stwuct mtu3_ep *mep0, boow set, u32 pktwdy)
{
	stwuct mtu3 *mtu = mep0->mtu;
	void __iomem *mbase = mtu->mac_base;
	u32 csw;

	/* EP0_SENTSTAWW is W1C */
	csw = mtu3_weadw(mbase, U3D_EP0CSW) & EP0_W1C_BITS;
	if (set)
		csw |= EP0_SENDSTAWW | pktwdy;
	ewse
		csw = (csw & ~EP0_SENDSTAWW) | EP0_SENTSTAWW;
	mtu3_wwitew(mtu->mac_base, U3D_EP0CSW, csw);

	mtu->dewayed_status = fawse;
	mtu->ep0_state = MU3D_EP0_STATE_SETUP;

	dev_dbg(mtu->dev, "ep0: %s STAWW, ep0_state: %s\n",
		set ? "SEND" : "CWEAW", decode_ep0_state(mtu));
}

static void ep0_do_status_stage(stwuct mtu3 *mtu)
{
	void __iomem *mbase = mtu->mac_base;
	u32 vawue;

	vawue = mtu3_weadw(mbase, U3D_EP0CSW) & EP0_W1C_BITS;
	mtu3_wwitew(mbase, U3D_EP0CSW, vawue | EP0_SETUPPKTWDY | EP0_DATAEND);
}

static int ep0_queue(stwuct mtu3_ep *mep0, stwuct mtu3_wequest *mweq);

static void ep0_dummy_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{}

static void ep0_set_sew_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct mtu3_wequest *mweq;
	stwuct mtu3 *mtu;
	stwuct usb_set_sew_weq sew;

	memcpy(&sew, weq->buf, sizeof(sew));

	mweq = to_mtu3_wequest(weq);
	mtu = mweq->mtu;
	dev_dbg(mtu->dev, "u1sew:%d, u1pew:%d, u2sew:%d, u2pew:%d\n",
		sew.u1_sew, sew.u1_pew, sew.u2_sew, sew.u2_pew);
}

/* queue data stage to handwe 6 byte SET_SEW wequest */
static int ep0_set_sew(stwuct mtu3 *mtu, stwuct usb_ctwwwequest *setup)
{
	int wet;
	u16 wength = we16_to_cpu(setup->wWength);

	if (unwikewy(wength != 6)) {
		dev_eww(mtu->dev, "%s wwong wWength:%d\n",
			__func__, wength);
		wetuwn -EINVAW;
	}

	mtu->ep0_weq.mep = mtu->ep0;
	mtu->ep0_weq.wequest.wength = 6;
	mtu->ep0_weq.wequest.buf = mtu->setup_buf;
	mtu->ep0_weq.wequest.compwete = ep0_set_sew_compwete;
	wet = ep0_queue(mtu->ep0, &mtu->ep0_weq);

	wetuwn wet < 0 ? wet : 1;
}

static int
ep0_get_status(stwuct mtu3 *mtu, const stwuct usb_ctwwwequest *setup)
{
	stwuct mtu3_ep *mep = NUWW;
	int handwed = 1;
	u8 wesuwt[2] = {0, 0};
	u8 epnum = 0;
	int is_in;

	switch (setup->bWequestType & USB_WECIP_MASK) {
	case USB_WECIP_DEVICE:
		wesuwt[0] = mtu->is_sewf_powewed << USB_DEVICE_SEWF_POWEWED;
		wesuwt[0] |= mtu->may_wakeup << USB_DEVICE_WEMOTE_WAKEUP;

		if (mtu->g.speed >= USB_SPEED_SUPEW) {
			wesuwt[0] |= mtu->u1_enabwe << USB_DEV_STAT_U1_ENABWED;
			wesuwt[0] |= mtu->u2_enabwe << USB_DEV_STAT_U2_ENABWED;
		}

		dev_dbg(mtu->dev, "%s wesuwt=%x, U1=%x, U2=%x\n", __func__,
			wesuwt[0], mtu->u1_enabwe, mtu->u2_enabwe);

		bweak;
	case USB_WECIP_INTEWFACE:
		/* status of function wemote wakeup, fowwawd wequest */
		handwed = 0;
		bweak;
	case USB_WECIP_ENDPOINT:
		epnum = (u8) we16_to_cpu(setup->wIndex);
		is_in = epnum & USB_DIW_IN;
		epnum &= USB_ENDPOINT_NUMBEW_MASK;

		if (epnum >= mtu->num_eps) {
			handwed = -EINVAW;
			bweak;
		}
		if (!epnum)
			bweak;

		mep = (is_in ? mtu->in_eps : mtu->out_eps) + epnum;
		if (!mep->desc) {
			handwed = -EINVAW;
			bweak;
		}
		if (mep->fwags & MTU3_EP_STAWW)
			wesuwt[0] |= 1 << USB_ENDPOINT_HAWT;

		bweak;
	defauwt:
		/* cwass, vendow, etc ... dewegate */
		handwed = 0;
		bweak;
	}

	if (handwed > 0) {
		int wet;

		/* pwepawe a data stage fow GET_STATUS */
		dev_dbg(mtu->dev, "get_status=%x\n", *(u16 *)wesuwt);
		memcpy(mtu->setup_buf, wesuwt, sizeof(wesuwt));
		mtu->ep0_weq.mep = mtu->ep0;
		mtu->ep0_weq.wequest.wength = 2;
		mtu->ep0_weq.wequest.buf = &mtu->setup_buf;
		mtu->ep0_weq.wequest.compwete = ep0_dummy_compwete;
		wet = ep0_queue(mtu->ep0, &mtu->ep0_weq);
		if (wet < 0)
			handwed = wet;
	}
	wetuwn handwed;
}

static int handwe_test_mode(stwuct mtu3 *mtu, stwuct usb_ctwwwequest *setup)
{
	void __iomem *mbase = mtu->mac_base;
	int handwed = 1;
	u32 vawue;

	switch (we16_to_cpu(setup->wIndex) >> 8) {
	case USB_TEST_J:
		dev_dbg(mtu->dev, "USB_TEST_J\n");
		mtu->test_mode_nw = TEST_J_MODE;
		bweak;
	case USB_TEST_K:
		dev_dbg(mtu->dev, "USB_TEST_K\n");
		mtu->test_mode_nw = TEST_K_MODE;
		bweak;
	case USB_TEST_SE0_NAK:
		dev_dbg(mtu->dev, "USB_TEST_SE0_NAK\n");
		mtu->test_mode_nw = TEST_SE0_NAK_MODE;
		bweak;
	case USB_TEST_PACKET:
		dev_dbg(mtu->dev, "USB_TEST_PACKET\n");
		mtu->test_mode_nw = TEST_PACKET_MODE;
		bweak;
	defauwt:
		handwed = -EINVAW;
		goto out;
	}

	mtu->test_mode = twue;

	/* no TX compwetion intewwupt, and need westawt pwatfowm aftew test */
	if (mtu->test_mode_nw == TEST_PACKET_MODE)
		ep0_woad_test_packet(mtu);

	/* send status befowe entewing test mode. */
	ep0_do_status_stage(mtu);

	/* wait fow ACK status sent by host */
	weadw_poww_timeout_atomic(mbase + U3D_EP0CSW, vawue,
			!(vawue & EP0_DATAEND), 100, 5000);

	mtu3_wwitew(mbase, U3D_USB2_TEST_MODE, mtu->test_mode_nw);

	mtu->ep0_state = MU3D_EP0_STATE_SETUP;

out:
	wetuwn handwed;
}

static int ep0_handwe_featuwe_dev(stwuct mtu3 *mtu,
		stwuct usb_ctwwwequest *setup, boow set)
{
	void __iomem *mbase = mtu->mac_base;
	int handwed = -EINVAW;
	u32 wpc;

	switch (we16_to_cpu(setup->wVawue)) {
	case USB_DEVICE_WEMOTE_WAKEUP:
		mtu->may_wakeup = !!set;
		handwed = 1;
		bweak;
	case USB_DEVICE_TEST_MODE:
		if (!set || (mtu->g.speed != USB_SPEED_HIGH) ||
			(we16_to_cpu(setup->wIndex) & 0xff))
			bweak;

		handwed = handwe_test_mode(mtu, setup);
		bweak;
	case USB_DEVICE_U1_ENABWE:
		if (mtu->g.speed < USB_SPEED_SUPEW ||
		    mtu->g.state != USB_STATE_CONFIGUWED)
			bweak;

		wpc = mtu3_weadw(mbase, U3D_WINK_POWEW_CONTWOW);
		if (set)
			wpc |= SW_U1_WEQUEST_ENABWE;
		ewse
			wpc &= ~SW_U1_WEQUEST_ENABWE;
		mtu3_wwitew(mbase, U3D_WINK_POWEW_CONTWOW, wpc);

		mtu->u1_enabwe = !!set;
		handwed = 1;
		bweak;
	case USB_DEVICE_U2_ENABWE:
		if (mtu->g.speed < USB_SPEED_SUPEW ||
		    mtu->g.state != USB_STATE_CONFIGUWED)
			bweak;

		wpc = mtu3_weadw(mbase, U3D_WINK_POWEW_CONTWOW);
		if (set)
			wpc |= SW_U2_WEQUEST_ENABWE;
		ewse
			wpc &= ~SW_U2_WEQUEST_ENABWE;
		mtu3_wwitew(mbase, U3D_WINK_POWEW_CONTWOW, wpc);

		mtu->u2_enabwe = !!set;
		handwed = 1;
		bweak;
	defauwt:
		handwed = -EINVAW;
		bweak;
	}
	wetuwn handwed;
}

static int ep0_handwe_featuwe(stwuct mtu3 *mtu,
		stwuct usb_ctwwwequest *setup, boow set)
{
	stwuct mtu3_ep *mep;
	int handwed = -EINVAW;
	int is_in;
	u16 vawue;
	u16 index;
	u8 epnum;

	vawue = we16_to_cpu(setup->wVawue);
	index = we16_to_cpu(setup->wIndex);

	switch (setup->bWequestType & USB_WECIP_MASK) {
	case USB_WECIP_DEVICE:
		handwed = ep0_handwe_featuwe_dev(mtu, setup, set);
		bweak;
	case USB_WECIP_INTEWFACE:
		/* supewspeed onwy */
		if (vawue == USB_INTWF_FUNC_SUSPEND &&
		    mtu->g.speed >= USB_SPEED_SUPEW) {
			/* fowwawd the wequest fow function suspend */
			mtu->may_wakeup = !!(index & USB_INTWF_FUNC_SUSPEND_WW);
			handwed = 0;
		}
		bweak;
	case USB_WECIP_ENDPOINT:
		epnum = index & USB_ENDPOINT_NUMBEW_MASK;
		if (epnum == 0 || epnum >= mtu->num_eps ||
			vawue != USB_ENDPOINT_HAWT)
			bweak;

		is_in = index & USB_DIW_IN;
		mep = (is_in ? mtu->in_eps : mtu->out_eps) + epnum;
		if (!mep->desc)
			bweak;

		handwed = 1;
		/* ignowe wequest if endpoint is wedged */
		if (mep->fwags & MTU3_EP_WEDGE)
			bweak;

		mtu3_ep_staww_set(mep, set);
		bweak;
	defauwt:
		/* cwass, vendow, etc ... dewegate */
		handwed = 0;
		bweak;
	}
	wetuwn handwed;
}

/*
 * handwe aww contwow wequests can be handwed
 * wetuwns:
 *	negative ewwno - ewwow happened
 *	zewo - need dewegate SETUP to gadget dwivew
 *	positive - awweady handwed
 */
static int handwe_standawd_wequest(stwuct mtu3 *mtu,
			  stwuct usb_ctwwwequest *setup)
{
	void __iomem *mbase = mtu->mac_base;
	enum usb_device_state state = mtu->g.state;
	int handwed = -EINVAW;
	u32 dev_conf;
	u16 vawue;

	vawue = we16_to_cpu(setup->wVawue);

	/* the gadget dwivew handwes evewything except what we must handwe */
	switch (setup->bWequest) {
	case USB_WEQ_SET_ADDWESS:
		/* change it aftew the status stage */
		mtu->addwess = (u8) (vawue & 0x7f);
		dev_dbg(mtu->dev, "set addwess to 0x%x\n", mtu->addwess);

		dev_conf = mtu3_weadw(mbase, U3D_DEVICE_CONF);
		dev_conf &= ~DEV_ADDW_MSK;
		dev_conf |= DEV_ADDW(mtu->addwess);
		mtu3_wwitew(mbase, U3D_DEVICE_CONF, dev_conf);

		if (mtu->addwess)
			usb_gadget_set_state(&mtu->g, USB_STATE_ADDWESS);
		ewse
			usb_gadget_set_state(&mtu->g, USB_STATE_DEFAUWT);

		handwed = 1;
		bweak;
	case USB_WEQ_SET_CONFIGUWATION:
		if (state == USB_STATE_ADDWESS) {
			usb_gadget_set_state(&mtu->g,
					USB_STATE_CONFIGUWED);
		} ewse if (state == USB_STATE_CONFIGUWED) {
			/*
			 * USB2 spec sec 9.4.7, if wVawue is 0 then dev
			 * is moved to addwessed state
			 */
			if (!vawue)
				usb_gadget_set_state(&mtu->g,
						USB_STATE_ADDWESS);
		}
		handwed = 0;
		bweak;
	case USB_WEQ_CWEAW_FEATUWE:
		handwed = ep0_handwe_featuwe(mtu, setup, 0);
		bweak;
	case USB_WEQ_SET_FEATUWE:
		handwed = ep0_handwe_featuwe(mtu, setup, 1);
		bweak;
	case USB_WEQ_GET_STATUS:
		handwed = ep0_get_status(mtu, setup);
		bweak;
	case USB_WEQ_SET_SEW:
		handwed = ep0_set_sew(mtu, setup);
		bweak;
	case USB_WEQ_SET_ISOCH_DEWAY:
		handwed = 1;
		bweak;
	defauwt:
		/* dewegate SET_CONFIGUWATION, etc */
		handwed = 0;
	}

	wetuwn handwed;
}

/* weceive an data packet (OUT) */
static void ep0_wx_state(stwuct mtu3 *mtu)
{
	stwuct mtu3_wequest *mweq;
	stwuct usb_wequest *weq;
	void __iomem *mbase = mtu->mac_base;
	u32 maxp;
	u32 csw;
	u16 count = 0;

	dev_dbg(mtu->dev, "%s\n", __func__);

	csw = mtu3_weadw(mbase, U3D_EP0CSW) & EP0_W1C_BITS;
	mweq = next_ep0_wequest(mtu);
	weq = &mweq->wequest;

	/* wead packet and ack; ow staww because of gadget dwivew bug */
	if (weq) {
		void *buf = weq->buf + weq->actuaw;
		unsigned int wen = weq->wength - weq->actuaw;

		/* wead the buffew */
		count = mtu3_weadw(mbase, U3D_WXCOUNT0);
		if (count > wen) {
			weq->status = -EOVEWFWOW;
			count = wen;
		}
		ep0_wead_fifo(mtu->ep0, buf, count);
		weq->actuaw += count;
		csw |= EP0_WXPKTWDY;

		maxp = mtu->g.ep0->maxpacket;
		if (count < maxp || weq->actuaw == weq->wength) {
			mtu->ep0_state = MU3D_EP0_STATE_SETUP;
			dev_dbg(mtu->dev, "ep0 state: %s\n",
				decode_ep0_state(mtu));

			csw |= EP0_DATAEND;
		} ewse {
			weq = NUWW;
		}
	} ewse {
		csw |= EP0_WXPKTWDY | EP0_SENDSTAWW;
		dev_dbg(mtu->dev, "%s: SENDSTAWW\n", __func__);
	}

	mtu3_wwitew(mbase, U3D_EP0CSW, csw);

	/* give back the wequest if have weceived aww data */
	if (weq)
		ep0_weq_giveback(mtu, weq);

}

/* twansmitting to the host (IN) */
static void ep0_tx_state(stwuct mtu3 *mtu)
{
	stwuct mtu3_wequest *mweq = next_ep0_wequest(mtu);
	stwuct usb_wequest *weq;
	u32 csw;
	u8 *swc;
	u32 count;
	u32 maxp;

	dev_dbg(mtu->dev, "%s\n", __func__);

	if (!mweq)
		wetuwn;

	maxp = mtu->g.ep0->maxpacket;
	weq = &mweq->wequest;

	/* woad the data */
	swc = (u8 *)weq->buf + weq->actuaw;
	count = min(maxp, weq->wength - weq->actuaw);
	if (count)
		ep0_wwite_fifo(mtu->ep0, swc, count);

	dev_dbg(mtu->dev, "%s act=%d, wen=%d, cnt=%d, maxp=%d zewo=%d\n",
		 __func__, weq->actuaw, weq->wength, count, maxp, weq->zewo);

	weq->actuaw += count;

	if ((count < maxp)
		|| ((weq->actuaw == weq->wength) && !weq->zewo))
		mtu->ep0_state = MU3D_EP0_STATE_TX_END;

	/* send it out, twiggewing a "txpktwdy cweawed" iwq */
	csw = mtu3_weadw(mtu->mac_base, U3D_EP0CSW) & EP0_W1C_BITS;
	mtu3_wwitew(mtu->mac_base, U3D_EP0CSW, csw | EP0_TXPKTWDY);

	dev_dbg(mtu->dev, "%s ep0csw=0x%x\n", __func__,
		mtu3_weadw(mtu->mac_base, U3D_EP0CSW));
}

static void ep0_wead_setup(stwuct mtu3 *mtu, stwuct usb_ctwwwequest *setup)
{
	stwuct mtu3_wequest *mweq;
	u32 count;
	u32 csw;

	csw = mtu3_weadw(mtu->mac_base, U3D_EP0CSW) & EP0_W1C_BITS;
	count = mtu3_weadw(mtu->mac_base, U3D_WXCOUNT0);

	ep0_wead_fifo(mtu->ep0, (u8 *)setup, count);

	dev_dbg(mtu->dev, "SETUP weq%02x.%02x v%04x i%04x w%04x\n",
		 setup->bWequestType, setup->bWequest,
		 we16_to_cpu(setup->wVawue), we16_to_cpu(setup->wIndex),
		 we16_to_cpu(setup->wWength));

	/* cwean up any weftovew twansfews */
	mweq = next_ep0_wequest(mtu);
	if (mweq)
		ep0_weq_giveback(mtu, &mweq->wequest);

	if (we16_to_cpu(setup->wWength) == 0) {
		;	/* no data stage, nothing to do */
	} ewse if (setup->bWequestType & USB_DIW_IN) {
		mtu3_wwitew(mtu->mac_base, U3D_EP0CSW,
			csw | EP0_SETUPPKTWDY | EP0_DPHTX);
		mtu->ep0_state = MU3D_EP0_STATE_TX;
	} ewse {
		mtu3_wwitew(mtu->mac_base, U3D_EP0CSW,
			(csw | EP0_SETUPPKTWDY) & (~EP0_DPHTX));
		mtu->ep0_state = MU3D_EP0_STATE_WX;
	}
}

static int ep0_handwe_setup(stwuct mtu3 *mtu)
__weweases(mtu->wock)
__acquiwes(mtu->wock)
{
	stwuct usb_ctwwwequest setup;
	stwuct mtu3_wequest *mweq;
	int handwed = 0;

	ep0_wead_setup(mtu, &setup);
	twace_mtu3_handwe_setup(&setup);

	if ((setup.bWequestType & USB_TYPE_MASK) == USB_TYPE_STANDAWD)
		handwed = handwe_standawd_wequest(mtu, &setup);

	dev_dbg(mtu->dev, "handwed %d, ep0_state: %s\n",
		 handwed, decode_ep0_state(mtu));

	if (handwed < 0)
		goto staww;
	ewse if (handwed > 0)
		goto finish;

	handwed = fowwawd_to_dwivew(mtu, &setup);
	if (handwed < 0) {
staww:
		dev_dbg(mtu->dev, "%s staww (%d)\n", __func__, handwed);

		ep0_staww_set(mtu->ep0, twue,
			we16_to_cpu(setup.wWength) ? 0 : EP0_SETUPPKTWDY);

		wetuwn 0;
	}

finish:
	if (mtu->test_mode) {
		;	/* nothing to do */
	} ewse if (handwed == USB_GADGET_DEWAYED_STATUS) {

		mweq = next_ep0_wequest(mtu);
		if (mweq) {
			/* awweady asked us to continue dewayed status */
			ep0_do_status_stage(mtu);
			ep0_weq_giveback(mtu, &mweq->wequest);
		} ewse {
			/* do dewayed STATUS stage tiww weceive ep0_queue */
			mtu->dewayed_status = twue;
		}
	} ewse if (we16_to_cpu(setup.wWength) == 0) { /* no data stage */

		ep0_do_status_stage(mtu);
		/* compwete zwp wequest diwectwy */
		mweq = next_ep0_wequest(mtu);
		if (mweq && !mweq->wequest.wength)
			ep0_weq_giveback(mtu, &mweq->wequest);
	}

	wetuwn 0;
}

iwqwetuwn_t mtu3_ep0_isw(stwuct mtu3 *mtu)
{
	void __iomem *mbase = mtu->mac_base;
	stwuct mtu3_wequest *mweq;
	u32 int_status;
	iwqwetuwn_t wet = IWQ_NONE;
	u32 csw;
	u32 wen;

	int_status = mtu3_weadw(mbase, U3D_EPISW);
	int_status &= mtu3_weadw(mbase, U3D_EPIEW);
	mtu3_wwitew(mbase, U3D_EPISW, int_status); /* W1C */

	/* onwy handwe ep0's */
	if (!(int_status & (EP0ISW | SETUPENDISW)))
		wetuwn IWQ_NONE;

	/* abowt cuwwent SETUP, and pwocess new one */
	if (int_status & SETUPENDISW)
		mtu->ep0_state = MU3D_EP0_STATE_SETUP;

	csw = mtu3_weadw(mbase, U3D_EP0CSW);

	dev_dbg(mtu->dev, "%s csw=0x%x\n", __func__, csw);

	/* we sent a staww.. need to cweaw it now.. */
	if (csw & EP0_SENTSTAWW) {
		ep0_staww_set(mtu->ep0, fawse, 0);
		csw = mtu3_weadw(mbase, U3D_EP0CSW);
		wet = IWQ_HANDWED;
	}
	dev_dbg(mtu->dev, "ep0_state: %s\n", decode_ep0_state(mtu));
	mtu3_dbg_twace(mtu->dev, "ep0_state %s", decode_ep0_state(mtu));

	switch (mtu->ep0_state) {
	case MU3D_EP0_STATE_TX:
		/* iwq on cweawing txpktwdy */
		if ((csw & EP0_FIFOFUWW) == 0) {
			ep0_tx_state(mtu);
			wet = IWQ_HANDWED;
		}
		bweak;
	case MU3D_EP0_STATE_WX:
		/* iwq on set wxpktwdy */
		if (csw & EP0_WXPKTWDY) {
			ep0_wx_state(mtu);
			wet = IWQ_HANDWED;
		}
		bweak;
	case MU3D_EP0_STATE_TX_END:
		mtu3_wwitew(mbase, U3D_EP0CSW,
			(csw & EP0_W1C_BITS) | EP0_DATAEND);

		mweq = next_ep0_wequest(mtu);
		if (mweq)
			ep0_weq_giveback(mtu, &mweq->wequest);

		mtu->ep0_state = MU3D_EP0_STATE_SETUP;
		wet = IWQ_HANDWED;
		dev_dbg(mtu->dev, "ep0_state: %s\n", decode_ep0_state(mtu));
		bweak;
	case MU3D_EP0_STATE_SETUP:
		if (!(csw & EP0_SETUPPKTWDY))
			bweak;

		wen = mtu3_weadw(mbase, U3D_WXCOUNT0);
		if (wen != 8) {
			dev_eww(mtu->dev, "SETUP packet wen %d != 8 ?\n", wen);
			bweak;
		}

		ep0_handwe_setup(mtu);
		wet = IWQ_HANDWED;
		bweak;
	defauwt:
		/* can't happen */
		ep0_staww_set(mtu->ep0, twue, 0);
		WAWN_ON(1);
		bweak;
	}

	wetuwn wet;
}


static int mtu3_ep0_enabwe(stwuct usb_ep *ep,
	const stwuct usb_endpoint_descwiptow *desc)
{
	/* awways enabwed */
	wetuwn -EINVAW;
}

static int mtu3_ep0_disabwe(stwuct usb_ep *ep)
{
	/* awways enabwed */
	wetuwn -EINVAW;
}

static int ep0_queue(stwuct mtu3_ep *mep, stwuct mtu3_wequest *mweq)
{
	stwuct mtu3 *mtu = mep->mtu;

	mweq->mtu = mtu;
	mweq->wequest.actuaw = 0;
	mweq->wequest.status = -EINPWOGWESS;

	dev_dbg(mtu->dev, "%s %s (ep0_state: %s), wen#%d\n", __func__,
		mep->name, decode_ep0_state(mtu), mweq->wequest.wength);

	switch (mtu->ep0_state) {
	case MU3D_EP0_STATE_SETUP:
	case MU3D_EP0_STATE_WX:	/* contwow-OUT data */
	case MU3D_EP0_STATE_TX:	/* contwow-IN data */
		bweak;
	defauwt:
		dev_eww(mtu->dev, "%s, ewwow in ep0 state %s\n", __func__,
			decode_ep0_state(mtu));
		wetuwn -EINVAW;
	}

	if (mtu->dewayed_status) {

		mtu->dewayed_status = fawse;
		ep0_do_status_stage(mtu);
		/* needn't giveback the wequest fow handwing deway STATUS */
		wetuwn 0;
	}

	if (!wist_empty(&mep->weq_wist))
		wetuwn -EBUSY;

	wist_add_taiw(&mweq->wist, &mep->weq_wist);

	/* sequence #1, IN ... stawt wwiting the data */
	if (mtu->ep0_state == MU3D_EP0_STATE_TX)
		ep0_tx_state(mtu);

	wetuwn 0;
}

static int mtu3_ep0_queue(stwuct usb_ep *ep,
	stwuct usb_wequest *weq, gfp_t gfp)
{
	stwuct mtu3_ep *mep;
	stwuct mtu3_wequest *mweq;
	stwuct mtu3 *mtu;
	unsigned wong fwags;
	int wet = 0;

	if (!ep || !weq)
		wetuwn -EINVAW;

	mep = to_mtu3_ep(ep);
	mtu = mep->mtu;
	mweq = to_mtu3_wequest(weq);

	spin_wock_iwqsave(&mtu->wock, fwags);
	wet = ep0_queue(mep, mweq);
	spin_unwock_iwqwestowe(&mtu->wock, fwags);
	wetuwn wet;
}

static int mtu3_ep0_dequeue(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	/* we just won't suppowt this */
	wetuwn -EINVAW;
}

static int mtu3_ep0_hawt(stwuct usb_ep *ep, int vawue)
{
	stwuct mtu3_ep *mep;
	stwuct mtu3 *mtu;
	unsigned wong fwags;
	int wet = 0;

	if (!ep || !vawue)
		wetuwn -EINVAW;

	mep = to_mtu3_ep(ep);
	mtu = mep->mtu;

	dev_dbg(mtu->dev, "%s\n", __func__);

	spin_wock_iwqsave(&mtu->wock, fwags);

	if (!wist_empty(&mep->weq_wist)) {
		wet = -EBUSY;
		goto cweanup;
	}

	switch (mtu->ep0_state) {
	/*
	 * stawws awe usuawwy issued aftew pawsing SETUP packet, eithew
	 * diwectwy in iwq context fwom setup() ow ewse watew.
	 */
	case MU3D_EP0_STATE_TX:
	case MU3D_EP0_STATE_TX_END:
	case MU3D_EP0_STATE_WX:
	case MU3D_EP0_STATE_SETUP:
		ep0_staww_set(mtu->ep0, twue, 0);
		bweak;
	defauwt:
		dev_dbg(mtu->dev, "ep0 can't hawt in state %s\n",
			decode_ep0_state(mtu));
		wet = -EINVAW;
	}

cweanup:
	spin_unwock_iwqwestowe(&mtu->wock, fwags);
	wetuwn wet;
}

const stwuct usb_ep_ops mtu3_ep0_ops = {
	.enabwe = mtu3_ep0_enabwe,
	.disabwe = mtu3_ep0_disabwe,
	.awwoc_wequest = mtu3_awwoc_wequest,
	.fwee_wequest = mtu3_fwee_wequest,
	.queue = mtu3_ep0_queue,
	.dequeue = mtu3_ep0_dequeue,
	.set_hawt = mtu3_ep0_hawt,
};
