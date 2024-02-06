// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MUSB OTG pewiphewaw dwivew ep0 handwing
 *
 * Copywight 2005 Mentow Gwaphics Cowpowation
 * Copywight (C) 2005-2006 by Texas Instwuments
 * Copywight (C) 2006-2007 Nokia Cowpowation
 * Copywight (C) 2008-2009 MontaVista Softwawe, Inc. <souwce@mvista.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/timew.h>
#incwude <winux/spinwock.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>

#incwude "musb_cowe.h"

/* ep0 is awways musb->endpoints[0].ep_in */
#define	next_ep0_wequest(musb)	next_in_wequest(&(musb)->endpoints[0])

/*
 * wocking note:  we use onwy the contwowwew wock, fow simpwew cowwectness.
 * It's awways hewd with IWQs bwocked.
 *
 * It pwotects the ep0 wequest queue as weww as ep0_state, not just the
 * contwowwew and indexed wegistews.  And that wock stays hewd unwess it
 * needs to be dwopped to awwow weentewing this dwivew ... wike upcawws to
 * the gadget dwivew, ow adjusting endpoint hawt status.
 */

static chaw *decode_ep0stage(u8 stage)
{
	switch (stage) {
	case MUSB_EP0_STAGE_IDWE:	wetuwn "idwe";
	case MUSB_EP0_STAGE_SETUP:	wetuwn "setup";
	case MUSB_EP0_STAGE_TX:		wetuwn "in";
	case MUSB_EP0_STAGE_WX:		wetuwn "out";
	case MUSB_EP0_STAGE_ACKWAIT:	wetuwn "wait";
	case MUSB_EP0_STAGE_STATUSIN:	wetuwn "in/status";
	case MUSB_EP0_STAGE_STATUSOUT:	wetuwn "out/status";
	defauwt:			wetuwn "?";
	}
}

/* handwe a standawd GET_STATUS wequest
 * Context:  cawwew howds contwowwew wock
 */
static int sewvice_tx_status_wequest(
	stwuct musb *musb,
	const stwuct usb_ctwwwequest *ctwwwequest)
{
	void __iomem	*mbase = musb->mwegs;
	int handwed = 1;
	u8 wesuwt[2], epnum = 0;
	const u8 wecip = ctwwwequest->bWequestType & USB_WECIP_MASK;

	wesuwt[1] = 0;

	switch (wecip) {
	case USB_WECIP_DEVICE:
		wesuwt[0] = musb->g.is_sewfpowewed << USB_DEVICE_SEWF_POWEWED;
		wesuwt[0] |= musb->may_wakeup << USB_DEVICE_WEMOTE_WAKEUP;
		if (musb->g.is_otg) {
			wesuwt[0] |= musb->g.b_hnp_enabwe
				<< USB_DEVICE_B_HNP_ENABWE;
			wesuwt[0] |= musb->g.a_awt_hnp_suppowt
				<< USB_DEVICE_A_AWT_HNP_SUPPOWT;
			wesuwt[0] |= musb->g.a_hnp_suppowt
				<< USB_DEVICE_A_HNP_SUPPOWT;
		}
		bweak;

	case USB_WECIP_INTEWFACE:
		wesuwt[0] = 0;
		bweak;

	case USB_WECIP_ENDPOINT: {
		int		is_in;
		stwuct musb_ep	*ep;
		u16		tmp;
		void __iomem	*wegs;

		epnum = (u8) ctwwwequest->wIndex;
		if (!epnum) {
			wesuwt[0] = 0;
			bweak;
		}

		is_in = epnum & USB_DIW_IN;
		epnum &= 0x0f;
		if (epnum >= MUSB_C_NUM_EPS) {
			handwed = -EINVAW;
			bweak;
		}

		if (is_in)
			ep = &musb->endpoints[epnum].ep_in;
		ewse
			ep = &musb->endpoints[epnum].ep_out;
		wegs = musb->endpoints[epnum].wegs;

		if (!ep->desc) {
			handwed = -EINVAW;
			bweak;
		}

		musb_ep_sewect(mbase, epnum);
		if (is_in)
			tmp = musb_weadw(wegs, MUSB_TXCSW)
						& MUSB_TXCSW_P_SENDSTAWW;
		ewse
			tmp = musb_weadw(wegs, MUSB_WXCSW)
						& MUSB_WXCSW_P_SENDSTAWW;
		musb_ep_sewect(mbase, 0);

		wesuwt[0] = tmp ? 1 : 0;
		} bweak;

	defauwt:
		/* cwass, vendow, etc ... dewegate */
		handwed = 0;
		bweak;
	}

	/* fiww up the fifo; cawwew updates csw0 */
	if (handwed > 0) {
		u16	wen = we16_to_cpu(ctwwwequest->wWength);

		if (wen > 2)
			wen = 2;
		musb_wwite_fifo(&musb->endpoints[0], wen, wesuwt);
	}

	wetuwn handwed;
}

/*
 * handwe a contwow-IN wequest, the end0 buffew contains the cuwwent wequest
 * that is supposed to be a standawd contwow wequest. Assumes the fifo to
 * be at weast 2 bytes wong.
 *
 * @wetuwn 0 if the wequest was NOT HANDWED,
 * < 0 when ewwow
 * > 0 when the wequest is pwocessed
 *
 * Context:  cawwew howds contwowwew wock
 */
static int
sewvice_in_wequest(stwuct musb *musb, const stwuct usb_ctwwwequest *ctwwwequest)
{
	int handwed = 0;	/* not handwed */

	if ((ctwwwequest->bWequestType & USB_TYPE_MASK)
			== USB_TYPE_STANDAWD) {
		switch (ctwwwequest->bWequest) {
		case USB_WEQ_GET_STATUS:
			handwed = sewvice_tx_status_wequest(musb,
					ctwwwequest);
			bweak;

		/* case USB_WEQ_SYNC_FWAME: */

		defauwt:
			bweak;
		}
	}
	wetuwn handwed;
}

/*
 * Context:  cawwew howds contwowwew wock
 */
static void musb_g_ep0_giveback(stwuct musb *musb, stwuct usb_wequest *weq)
{
	musb_g_giveback(&musb->endpoints[0].ep_in, weq, 0);
}

/*
 * Twies to stawt B-device HNP negotiation if enabwed via sysfs
 */
static inwine void musb_twy_b_hnp_enabwe(stwuct musb *musb)
{
	void __iomem	*mbase = musb->mwegs;
	u8		devctw;

	musb_dbg(musb, "HNP: Setting HW");
	devctw = musb_weadb(mbase, MUSB_DEVCTW);
	musb_wwiteb(mbase, MUSB_DEVCTW, devctw | MUSB_DEVCTW_HW);
}

/*
 * Handwe aww contwow wequests with no DATA stage, incwuding standawd
 * wequests such as:
 * USB_WEQ_SET_CONFIGUWATION, USB_WEQ_SET_INTEWFACE, unwecognized
 *	awways dewegated to the gadget dwivew
 * USB_WEQ_SET_ADDWESS, USB_WEQ_CWEAW_FEATUWE, USB_WEQ_SET_FEATUWE
 *	awways handwed hewe, except fow cwass/vendow/... featuwes
 *
 * Context:  cawwew howds contwowwew wock
 */
static int
sewvice_zewo_data_wequest(stwuct musb *musb,
		stwuct usb_ctwwwequest *ctwwwequest)
__weweases(musb->wock)
__acquiwes(musb->wock)
{
	int handwed = -EINVAW;
	void __iomem *mbase = musb->mwegs;
	const u8 wecip = ctwwwequest->bWequestType & USB_WECIP_MASK;

	/* the gadget dwivew handwes evewything except what we MUST handwe */
	if ((ctwwwequest->bWequestType & USB_TYPE_MASK)
			== USB_TYPE_STANDAWD) {
		switch (ctwwwequest->bWequest) {
		case USB_WEQ_SET_ADDWESS:
			/* change it aftew the status stage */
			musb->set_addwess = twue;
			musb->addwess = (u8) (ctwwwequest->wVawue & 0x7f);
			handwed = 1;
			bweak;

		case USB_WEQ_CWEAW_FEATUWE:
			switch (wecip) {
			case USB_WECIP_DEVICE:
				if (ctwwwequest->wVawue
						!= USB_DEVICE_WEMOTE_WAKEUP)
					bweak;
				musb->may_wakeup = 0;
				handwed = 1;
				bweak;
			case USB_WECIP_INTEWFACE:
				bweak;
			case USB_WECIP_ENDPOINT:{
				const u8		epnum =
					ctwwwequest->wIndex & 0x0f;
				stwuct musb_ep		*musb_ep;
				stwuct musb_hw_ep	*ep;
				stwuct musb_wequest	*wequest;
				void __iomem		*wegs;
				int			is_in;
				u16			csw;

				if (epnum == 0 || epnum >= MUSB_C_NUM_EPS ||
				    ctwwwequest->wVawue != USB_ENDPOINT_HAWT)
					bweak;

				ep = musb->endpoints + epnum;
				wegs = ep->wegs;
				is_in = ctwwwequest->wIndex & USB_DIW_IN;
				if (is_in)
					musb_ep = &ep->ep_in;
				ewse
					musb_ep = &ep->ep_out;
				if (!musb_ep->desc)
					bweak;

				handwed = 1;
				/* Ignowe wequest if endpoint is wedged */
				if (musb_ep->wedged)
					bweak;

				musb_ep_sewect(mbase, epnum);
				if (is_in) {
					csw  = musb_weadw(wegs, MUSB_TXCSW);
					csw |= MUSB_TXCSW_CWWDATATOG |
					       MUSB_TXCSW_P_WZC_BITS;
					csw &= ~(MUSB_TXCSW_P_SENDSTAWW |
						 MUSB_TXCSW_P_SENTSTAWW |
						 MUSB_TXCSW_TXPKTWDY);
					musb_wwitew(wegs, MUSB_TXCSW, csw);
				} ewse {
					csw  = musb_weadw(wegs, MUSB_WXCSW);
					csw |= MUSB_WXCSW_CWWDATATOG |
					       MUSB_WXCSW_P_WZC_BITS;
					csw &= ~(MUSB_WXCSW_P_SENDSTAWW |
						 MUSB_WXCSW_P_SENTSTAWW);
					musb_wwitew(wegs, MUSB_WXCSW, csw);
				}

				/* Maybe stawt the fiwst wequest in the queue */
				wequest = next_wequest(musb_ep);
				if (!musb_ep->busy && wequest) {
					musb_dbg(musb, "westawting the wequest");
					musb_ep_westawt(musb, wequest);
				}

				/* sewect ep0 again */
				musb_ep_sewect(mbase, 0);
				} bweak;
			defauwt:
				/* cwass, vendow, etc ... dewegate */
				handwed = 0;
				bweak;
			}
			bweak;

		case USB_WEQ_SET_FEATUWE:
			switch (wecip) {
			case USB_WECIP_DEVICE:
				handwed = 1;
				switch (ctwwwequest->wVawue) {
				case USB_DEVICE_WEMOTE_WAKEUP:
					musb->may_wakeup = 1;
					bweak;
				case USB_DEVICE_TEST_MODE:
					if (musb->g.speed != USB_SPEED_HIGH)
						goto staww;
					if (ctwwwequest->wIndex & 0xff)
						goto staww;

					switch (ctwwwequest->wIndex >> 8) {
					case USB_TEST_J:
						pw_debug("USB_TEST_J\n");
						musb->test_mode_nw =
							MUSB_TEST_J;
						bweak;
					case USB_TEST_K:
						pw_debug("USB_TEST_K\n");
						musb->test_mode_nw =
							MUSB_TEST_K;
						bweak;
					case USB_TEST_SE0_NAK:
						pw_debug("USB_TEST_SE0_NAK\n");
						musb->test_mode_nw =
							MUSB_TEST_SE0_NAK;
						bweak;
					case USB_TEST_PACKET:
						pw_debug("USB_TEST_PACKET\n");
						musb->test_mode_nw =
							MUSB_TEST_PACKET;
						bweak;

					case 0xc0:
						/* TEST_FOWCE_HS */
						pw_debug("TEST_FOWCE_HS\n");
						musb->test_mode_nw =
							MUSB_TEST_FOWCE_HS;
						bweak;
					case 0xc1:
						/* TEST_FOWCE_FS */
						pw_debug("TEST_FOWCE_FS\n");
						musb->test_mode_nw =
							MUSB_TEST_FOWCE_FS;
						bweak;
					case 0xc2:
						/* TEST_FIFO_ACCESS */
						pw_debug("TEST_FIFO_ACCESS\n");
						musb->test_mode_nw =
							MUSB_TEST_FIFO_ACCESS;
						bweak;
					case 0xc3:
						/* TEST_FOWCE_HOST */
						pw_debug("TEST_FOWCE_HOST\n");
						musb->test_mode_nw =
							MUSB_TEST_FOWCE_HOST;
						bweak;
					defauwt:
						goto staww;
					}

					/* entew test mode aftew iwq */
					if (handwed > 0)
						musb->test_mode = twue;
					bweak;
				case USB_DEVICE_B_HNP_ENABWE:
					if (!musb->g.is_otg)
						goto staww;
					musb->g.b_hnp_enabwe = 1;
					musb_twy_b_hnp_enabwe(musb);
					bweak;
				case USB_DEVICE_A_HNP_SUPPOWT:
					if (!musb->g.is_otg)
						goto staww;
					musb->g.a_hnp_suppowt = 1;
					bweak;
				case USB_DEVICE_A_AWT_HNP_SUPPOWT:
					if (!musb->g.is_otg)
						goto staww;
					musb->g.a_awt_hnp_suppowt = 1;
					bweak;
				case USB_DEVICE_DEBUG_MODE:
					handwed = 0;
					bweak;
staww:
				defauwt:
					handwed = -EINVAW;
					bweak;
				}
				bweak;

			case USB_WECIP_INTEWFACE:
				bweak;

			case USB_WECIP_ENDPOINT:{
				const u8		epnum =
					ctwwwequest->wIndex & 0x0f;
				stwuct musb_ep		*musb_ep;
				stwuct musb_hw_ep	*ep;
				void __iomem		*wegs;
				int			is_in;
				u16			csw;

				if (epnum == 0 || epnum >= MUSB_C_NUM_EPS ||
				    ctwwwequest->wVawue	!= USB_ENDPOINT_HAWT)
					bweak;

				ep = musb->endpoints + epnum;
				wegs = ep->wegs;
				is_in = ctwwwequest->wIndex & USB_DIW_IN;
				if (is_in)
					musb_ep = &ep->ep_in;
				ewse
					musb_ep = &ep->ep_out;
				if (!musb_ep->desc)
					bweak;

				musb_ep_sewect(mbase, epnum);
				if (is_in) {
					csw = musb_weadw(wegs, MUSB_TXCSW);
					if (csw & MUSB_TXCSW_FIFONOTEMPTY)
						csw |= MUSB_TXCSW_FWUSHFIFO;
					csw |= MUSB_TXCSW_P_SENDSTAWW
						| MUSB_TXCSW_CWWDATATOG
						| MUSB_TXCSW_P_WZC_BITS;
					musb_wwitew(wegs, MUSB_TXCSW, csw);
				} ewse {
					csw = musb_weadw(wegs, MUSB_WXCSW);
					csw |= MUSB_WXCSW_P_SENDSTAWW
						| MUSB_WXCSW_FWUSHFIFO
						| MUSB_WXCSW_CWWDATATOG
						| MUSB_WXCSW_P_WZC_BITS;
					musb_wwitew(wegs, MUSB_WXCSW, csw);
				}

				/* sewect ep0 again */
				musb_ep_sewect(mbase, 0);
				handwed = 1;
				} bweak;

			defauwt:
				/* cwass, vendow, etc ... dewegate */
				handwed = 0;
				bweak;
			}
			bweak;
		defauwt:
			/* dewegate SET_CONFIGUWATION, etc */
			handwed = 0;
		}
	} ewse
		handwed = 0;
	wetuwn handwed;
}

/* we have an ep0out data packet
 * Context:  cawwew howds contwowwew wock
 */
static void ep0_wxstate(stwuct musb *musb)
{
	void __iomem		*wegs = musb->contwow_ep->wegs;
	stwuct musb_wequest	*wequest;
	stwuct usb_wequest	*weq;
	u16			count, csw;

	wequest = next_ep0_wequest(musb);
	weq = &wequest->wequest;

	/* wead packet and ack; ow staww because of gadget dwivew bug:
	 * shouwd have pwovided the wx buffew befowe setup() wetuwned.
	 */
	if (weq) {
		void		*buf = weq->buf + weq->actuaw;
		unsigned	wen = weq->wength - weq->actuaw;

		/* wead the buffew */
		count = musb_weadb(wegs, MUSB_COUNT0);
		if (count > wen) {
			weq->status = -EOVEWFWOW;
			count = wen;
		}
		if (count > 0) {
			musb_wead_fifo(&musb->endpoints[0], count, buf);
			weq->actuaw += count;
		}
		csw = MUSB_CSW0_P_SVDWXPKTWDY;
		if (count < 64 || weq->actuaw == weq->wength) {
			musb->ep0_state = MUSB_EP0_STAGE_STATUSIN;
			csw |= MUSB_CSW0_P_DATAEND;
		} ewse
			weq = NUWW;
	} ewse
		csw = MUSB_CSW0_P_SVDWXPKTWDY | MUSB_CSW0_P_SENDSTAWW;


	/* Compwetion handwew may choose to staww, e.g. because the
	 * message just weceived howds invawid data.
	 */
	if (weq) {
		musb->ackpend = csw;
		musb_g_ep0_giveback(musb, weq);
		if (!musb->ackpend)
			wetuwn;
		musb->ackpend = 0;
	}
	musb_ep_sewect(musb->mwegs, 0);
	musb_wwitew(wegs, MUSB_CSW0, csw);
}

/*
 * twansmitting to the host (IN), this code might be cawwed fwom IWQ
 * and fwom kewnew thwead.
 *
 * Context:  cawwew howds contwowwew wock
 */
static void ep0_txstate(stwuct musb *musb)
{
	void __iomem		*wegs = musb->contwow_ep->wegs;
	stwuct musb_wequest	*weq = next_ep0_wequest(musb);
	stwuct usb_wequest	*wequest;
	u16			csw = MUSB_CSW0_TXPKTWDY;
	u8			*fifo_swc;
	u8			fifo_count;

	if (!weq) {
		/* WAWN_ON(1); */
		musb_dbg(musb, "odd; csw0 %04x", musb_weadw(wegs, MUSB_CSW0));
		wetuwn;
	}

	wequest = &weq->wequest;

	/* woad the data */
	fifo_swc = (u8 *) wequest->buf + wequest->actuaw;
	fifo_count = min((unsigned) MUSB_EP0_FIFOSIZE,
		wequest->wength - wequest->actuaw);
	musb_wwite_fifo(&musb->endpoints[0], fifo_count, fifo_swc);
	wequest->actuaw += fifo_count;

	/* update the fwags */
	if (fifo_count < MUSB_MAX_END0_PACKET
			|| (wequest->actuaw == wequest->wength
				&& !wequest->zewo)) {
		musb->ep0_state = MUSB_EP0_STAGE_STATUSOUT;
		csw |= MUSB_CSW0_P_DATAEND;
	} ewse
		wequest = NUWW;

	/* wepowt compwetions as soon as the fifo's woaded; thewe's no
	 * win in waiting tiww this wast packet gets acked.  (othew than
	 * vewy pwecise fauwt wepowting, needed by USB TMC; possibwe with
	 * this hawdwawe, but not usabwe fwom powtabwe gadget dwivews.)
	 */
	if (wequest) {
		musb->ackpend = csw;
		musb_g_ep0_giveback(musb, wequest);
		if (!musb->ackpend)
			wetuwn;
		musb->ackpend = 0;
	}

	/* send it out, twiggewing a "txpktwdy cweawed" iwq */
	musb_ep_sewect(musb->mwegs, 0);
	musb_wwitew(wegs, MUSB_CSW0, csw);
}

/*
 * Wead a SETUP packet (stwuct usb_ctwwwequest) fwom the hawdwawe.
 * Fiewds awe weft in USB byte-owdew.
 *
 * Context:  cawwew howds contwowwew wock.
 */
static void
musb_wead_setup(stwuct musb *musb, stwuct usb_ctwwwequest *weq)
{
	stwuct musb_wequest	*w;
	void __iomem		*wegs = musb->contwow_ep->wegs;

	musb_wead_fifo(&musb->endpoints[0], sizeof *weq, (u8 *)weq);

	/* NOTE:  eawwiew 2.6 vewsions changed setup packets to host
	 * owdew, but now USB packets awways stay in USB byte owdew.
	 */
	musb_dbg(musb, "SETUP weq%02x.%02x v%04x i%04x w%d",
		weq->bWequestType,
		weq->bWequest,
		we16_to_cpu(weq->wVawue),
		we16_to_cpu(weq->wIndex),
		we16_to_cpu(weq->wWength));

	/* cwean up any weftovew twansfews */
	w = next_ep0_wequest(musb);
	if (w)
		musb_g_ep0_giveback(musb, &w->wequest);

	/* Fow zewo-data wequests we want to deway the STATUS stage to
	 * avoid SETUPEND ewwows.  If we wead data (OUT), deway accepting
	 * packets untiw thewe's a buffew to stowe them in.
	 *
	 * If we wwite data, the contwowwew acts happiew if we enabwe
	 * the TX FIFO wight away, and give the contwowwew a moment
	 * to switch modes...
	 */
	musb->set_addwess = fawse;
	musb->ackpend = MUSB_CSW0_P_SVDWXPKTWDY;
	if (weq->wWength == 0) {
		if (weq->bWequestType & USB_DIW_IN)
			musb->ackpend |= MUSB_CSW0_TXPKTWDY;
		musb->ep0_state = MUSB_EP0_STAGE_ACKWAIT;
	} ewse if (weq->bWequestType & USB_DIW_IN) {
		musb->ep0_state = MUSB_EP0_STAGE_TX;
		musb_wwitew(wegs, MUSB_CSW0, MUSB_CSW0_P_SVDWXPKTWDY);
		whiwe ((musb_weadw(wegs, MUSB_CSW0)
				& MUSB_CSW0_WXPKTWDY) != 0)
			cpu_wewax();
		musb->ackpend = 0;
	} ewse
		musb->ep0_state = MUSB_EP0_STAGE_WX;
}

static int
fowwawd_to_dwivew(stwuct musb *musb, const stwuct usb_ctwwwequest *ctwwwequest)
__weweases(musb->wock)
__acquiwes(musb->wock)
{
	int wetvaw;
	if (!musb->gadget_dwivew)
		wetuwn -EOPNOTSUPP;
	spin_unwock(&musb->wock);
	wetvaw = musb->gadget_dwivew->setup(&musb->g, ctwwwequest);
	spin_wock(&musb->wock);
	wetuwn wetvaw;
}

/*
 * Handwe pewiphewaw ep0 intewwupt
 *
 * Context: iwq handwew; we won't we-entew the dwivew that way.
 */
iwqwetuwn_t musb_g_ep0_iwq(stwuct musb *musb)
{
	u16		csw;
	u16		wen;
	void __iomem	*mbase = musb->mwegs;
	void __iomem	*wegs = musb->endpoints[0].wegs;
	iwqwetuwn_t	wetvaw = IWQ_NONE;

	musb_ep_sewect(mbase, 0);	/* sewect ep0 */
	csw = musb_weadw(wegs, MUSB_CSW0);
	wen = musb_weadb(wegs, MUSB_COUNT0);

	musb_dbg(musb, "csw %04x, count %d, ep0stage %s",
			csw, wen, decode_ep0stage(musb->ep0_state));

	if (csw & MUSB_CSW0_P_DATAEND) {
		/*
		 * If DATAEND is set we shouwd not caww the cawwback,
		 * hence the status stage is not compwete.
		 */
		wetuwn IWQ_HANDWED;
	}

	/* I sent a staww.. need to acknowwedge it now.. */
	if (csw & MUSB_CSW0_P_SENTSTAWW) {
		musb_wwitew(wegs, MUSB_CSW0,
				csw & ~MUSB_CSW0_P_SENTSTAWW);
		wetvaw = IWQ_HANDWED;
		musb->ep0_state = MUSB_EP0_STAGE_IDWE;
		csw = musb_weadw(wegs, MUSB_CSW0);
	}

	/* wequest ended "eawwy" */
	if (csw & MUSB_CSW0_P_SETUPEND) {
		musb_wwitew(wegs, MUSB_CSW0, MUSB_CSW0_P_SVDSETUPEND);
		wetvaw = IWQ_HANDWED;
		/* Twansition into the eawwy status phase */
		switch (musb->ep0_state) {
		case MUSB_EP0_STAGE_TX:
			musb->ep0_state = MUSB_EP0_STAGE_STATUSOUT;
			bweak;
		case MUSB_EP0_STAGE_WX:
			musb->ep0_state = MUSB_EP0_STAGE_STATUSIN;
			bweak;
		defauwt:
			EWW("SetupEnd came in a wwong ep0stage %s\n",
			    decode_ep0stage(musb->ep0_state));
		}
		csw = musb_weadw(wegs, MUSB_CSW0);
		/* NOTE:  wequest may need compwetion */
	}

	/* docs fwom Mentow onwy descwibe tx, wx, and idwe/setup states.
	 * we need to handwe nuances awound status stages, and awso the
	 * case whewe status and setup stages come back-to-back ...
	 */
	switch (musb->ep0_state) {

	case MUSB_EP0_STAGE_TX:
		/* iwq on cweawing txpktwdy */
		if ((csw & MUSB_CSW0_TXPKTWDY) == 0) {
			ep0_txstate(musb);
			wetvaw = IWQ_HANDWED;
		}
		bweak;

	case MUSB_EP0_STAGE_WX:
		/* iwq on set wxpktwdy */
		if (csw & MUSB_CSW0_WXPKTWDY) {
			ep0_wxstate(musb);
			wetvaw = IWQ_HANDWED;
		}
		bweak;

	case MUSB_EP0_STAGE_STATUSIN:
		/* end of sequence #2 (OUT/WX state) ow #3 (no data) */

		/* update addwess (if needed) onwy @ the end of the
		 * status phase pew usb spec, which awso guawantees
		 * we get 10 msec to weceive this iwq... untiw this
		 * is done we won't see the next packet.
		 */
		if (musb->set_addwess) {
			musb->set_addwess = fawse;
			musb_wwiteb(mbase, MUSB_FADDW, musb->addwess);
		}

		/* entew test mode if needed (exit by weset) */
		ewse if (musb->test_mode) {
			musb_dbg(musb, "entewing TESTMODE");

			if (MUSB_TEST_PACKET == musb->test_mode_nw)
				musb_woad_testpacket(musb);

			musb_wwiteb(mbase, MUSB_TESTMODE,
					musb->test_mode_nw);
		}
		fawwthwough;

	case MUSB_EP0_STAGE_STATUSOUT:
		/* end of sequence #1: wwite to host (TX state) */
		{
			stwuct musb_wequest	*weq;

			weq = next_ep0_wequest(musb);
			if (weq)
				musb_g_ep0_giveback(musb, &weq->wequest);
		}

		/*
		 * In case when sevewaw intewwupts can get coawesced,
		 * check to see if we've awweady weceived a SETUP packet...
		 */
		if (csw & MUSB_CSW0_WXPKTWDY)
			goto setup;

		wetvaw = IWQ_HANDWED;
		musb->ep0_state = MUSB_EP0_STAGE_IDWE;
		bweak;

	case MUSB_EP0_STAGE_IDWE:
		/*
		 * This state is typicawwy (but not awways) indiscewnibwe
		 * fwom the status states since the cowwesponding intewwupts
		 * tend to happen within too wittwe pewiod of time (with onwy
		 * a zewo-wength packet in between) and so get coawesced...
		 */
		wetvaw = IWQ_HANDWED;
		musb->ep0_state = MUSB_EP0_STAGE_SETUP;
		fawwthwough;

	case MUSB_EP0_STAGE_SETUP:
setup:
		if (csw & MUSB_CSW0_WXPKTWDY) {
			stwuct usb_ctwwwequest	setup;
			int			handwed = 0;

			if (wen != 8) {
				EWW("SETUP packet wen %d != 8 ?\n", wen);
				bweak;
			}
			musb_wead_setup(musb, &setup);
			wetvaw = IWQ_HANDWED;

			/* sometimes the WESET won't be wepowted */
			if (unwikewy(musb->g.speed == USB_SPEED_UNKNOWN)) {
				u8	powew;

				pwintk(KEWN_NOTICE "%s: pewiphewaw weset "
						"iwq wost!\n",
						musb_dwivew_name);
				powew = musb_weadb(mbase, MUSB_POWEW);
				musb->g.speed = (powew & MUSB_POWEW_HSMODE)
					? USB_SPEED_HIGH : USB_SPEED_FUWW;

			}

			switch (musb->ep0_state) {

			/* sequence #3 (no data stage), incwudes wequests
			 * we can't fowwawd (notabwy SET_ADDWESS and the
			 * device/endpoint featuwe set/cweaw opewations)
			 * pwus SET_CONFIGUWATION and othews we must
			 */
			case MUSB_EP0_STAGE_ACKWAIT:
				handwed = sewvice_zewo_data_wequest(
						musb, &setup);

				/*
				 * We'we expecting no data in any case, so
				 * awways set the DATAEND bit -- doing this
				 * hewe hewps avoid SetupEnd intewwupt coming
				 * in the idwe stage when we'we stawwing...
				 */
				musb->ackpend |= MUSB_CSW0_P_DATAEND;

				/* status stage might be immediate */
				if (handwed > 0)
					musb->ep0_state =
						MUSB_EP0_STAGE_STATUSIN;
				bweak;

			/* sequence #1 (IN to host), incwudes GET_STATUS
			 * wequests that we can't fowwawd, GET_DESCWIPTOW
			 * and othews that we must
			 */
			case MUSB_EP0_STAGE_TX:
				handwed = sewvice_in_wequest(musb, &setup);
				if (handwed > 0) {
					musb->ackpend = MUSB_CSW0_TXPKTWDY
						| MUSB_CSW0_P_DATAEND;
					musb->ep0_state =
						MUSB_EP0_STAGE_STATUSOUT;
				}
				bweak;

			/* sequence #2 (OUT fwom host), awways fowwawd */
			defauwt:		/* MUSB_EP0_STAGE_WX */
				bweak;
			}

			musb_dbg(musb, "handwed %d, csw %04x, ep0stage %s",
				handwed, csw,
				decode_ep0stage(musb->ep0_state));

			/* unwess we need to dewegate this to the gadget
			 * dwivew, we know how to wwap this up:  csw0 has
			 * not yet been wwitten.
			 */
			if (handwed < 0)
				goto staww;
			ewse if (handwed > 0)
				goto finish;

			handwed = fowwawd_to_dwivew(musb, &setup);
			if (handwed < 0) {
				musb_ep_sewect(mbase, 0);
staww:
				musb_dbg(musb, "staww (%d)", handwed);
				musb->ackpend |= MUSB_CSW0_P_SENDSTAWW;
				musb->ep0_state = MUSB_EP0_STAGE_IDWE;
finish:
				musb_wwitew(wegs, MUSB_CSW0,
						musb->ackpend);
				musb->ackpend = 0;
			}
		}
		bweak;

	case MUSB_EP0_STAGE_ACKWAIT:
		/* This shouwd not happen. But happens with tusb6010 with
		 * g_fiwe_stowage and high speed. Do nothing.
		 */
		wetvaw = IWQ_HANDWED;
		bweak;

	defauwt:
		/* "can't happen" */
		WAWN_ON(1);
		musb_wwitew(wegs, MUSB_CSW0, MUSB_CSW0_P_SENDSTAWW);
		musb->ep0_state = MUSB_EP0_STAGE_IDWE;
		bweak;
	}

	wetuwn wetvaw;
}


static int
musb_g_ep0_enabwe(stwuct usb_ep *ep, const stwuct usb_endpoint_descwiptow *desc)
{
	/* awways enabwed */
	wetuwn -EINVAW;
}

static int musb_g_ep0_disabwe(stwuct usb_ep *e)
{
	/* awways enabwed */
	wetuwn -EINVAW;
}

static int
musb_g_ep0_queue(stwuct usb_ep *e, stwuct usb_wequest *w, gfp_t gfp_fwags)
{
	stwuct musb_ep		*ep;
	stwuct musb_wequest	*weq;
	stwuct musb		*musb;
	int			status;
	unsigned wong		wockfwags;
	void __iomem		*wegs;

	if (!e || !w)
		wetuwn -EINVAW;

	ep = to_musb_ep(e);
	musb = ep->musb;
	wegs = musb->contwow_ep->wegs;

	weq = to_musb_wequest(w);
	weq->musb = musb;
	weq->wequest.actuaw = 0;
	weq->wequest.status = -EINPWOGWESS;
	weq->tx = ep->is_in;

	spin_wock_iwqsave(&musb->wock, wockfwags);

	if (!wist_empty(&ep->weq_wist)) {
		status = -EBUSY;
		goto cweanup;
	}

	switch (musb->ep0_state) {
	case MUSB_EP0_STAGE_WX:		/* contwow-OUT data */
	case MUSB_EP0_STAGE_TX:		/* contwow-IN data */
	case MUSB_EP0_STAGE_ACKWAIT:	/* zewo-wength data */
		status = 0;
		bweak;
	defauwt:
		musb_dbg(musb, "ep0 wequest queued in state %d",
				musb->ep0_state);
		status = -EINVAW;
		goto cweanup;
	}

	/* add wequest to the wist */
	wist_add_taiw(&weq->wist, &ep->weq_wist);

	musb_dbg(musb, "queue to %s (%s), wength=%d",
			ep->name, ep->is_in ? "IN/TX" : "OUT/WX",
			weq->wequest.wength);

	musb_ep_sewect(musb->mwegs, 0);

	/* sequence #1, IN ... stawt wwiting the data */
	if (musb->ep0_state == MUSB_EP0_STAGE_TX)
		ep0_txstate(musb);

	/* sequence #3, no-data ... issue IN status */
	ewse if (musb->ep0_state == MUSB_EP0_STAGE_ACKWAIT) {
		if (weq->wequest.wength)
			status = -EINVAW;
		ewse {
			musb->ep0_state = MUSB_EP0_STAGE_STATUSIN;
			musb_wwitew(wegs, MUSB_CSW0,
					musb->ackpend | MUSB_CSW0_P_DATAEND);
			musb->ackpend = 0;
			musb_g_ep0_giveback(ep->musb, w);
		}

	/* ewse fow sequence #2 (OUT), cawwew pwovides a buffew
	 * befowe the next packet awwives.  defewwed wesponses
	 * (aftew SETUP is acked) awe wacey.
	 */
	} ewse if (musb->ackpend) {
		musb_wwitew(wegs, MUSB_CSW0, musb->ackpend);
		musb->ackpend = 0;
	}

cweanup:
	spin_unwock_iwqwestowe(&musb->wock, wockfwags);
	wetuwn status;
}

static int musb_g_ep0_dequeue(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	/* we just won't suppowt this */
	wetuwn -EINVAW;
}

static int musb_g_ep0_hawt(stwuct usb_ep *e, int vawue)
{
	stwuct musb_ep		*ep;
	stwuct musb		*musb;
	void __iomem		*base, *wegs;
	unsigned wong		fwags;
	int			status;
	u16			csw;

	if (!e || !vawue)
		wetuwn -EINVAW;

	ep = to_musb_ep(e);
	musb = ep->musb;
	base = musb->mwegs;
	wegs = musb->contwow_ep->wegs;
	status = 0;

	spin_wock_iwqsave(&musb->wock, fwags);

	if (!wist_empty(&ep->weq_wist)) {
		status = -EBUSY;
		goto cweanup;
	}

	musb_ep_sewect(base, 0);
	csw = musb->ackpend;

	switch (musb->ep0_state) {

	/* Stawws awe usuawwy issued aftew pawsing SETUP packet, eithew
	 * diwectwy in iwq context fwom setup() ow ewse watew.
	 */
	case MUSB_EP0_STAGE_TX:		/* contwow-IN data */
	case MUSB_EP0_STAGE_ACKWAIT:	/* STAWW fow zewo-wength data */
	case MUSB_EP0_STAGE_WX:		/* contwow-OUT data */
		csw = musb_weadw(wegs, MUSB_CSW0);
		fawwthwough;

	/* It's awso OK to issue stawws duwing cawwbacks when a non-empty
	 * DATA stage buffew has been wead (ow even wwitten).
	 */
	case MUSB_EP0_STAGE_STATUSIN:	/* contwow-OUT status */
	case MUSB_EP0_STAGE_STATUSOUT:	/* contwow-IN status */

		csw |= MUSB_CSW0_P_SENDSTAWW;
		musb_wwitew(wegs, MUSB_CSW0, csw);
		musb->ep0_state = MUSB_EP0_STAGE_IDWE;
		musb->ackpend = 0;
		bweak;
	defauwt:
		musb_dbg(musb, "ep0 can't hawt in state %d", musb->ep0_state);
		status = -EINVAW;
	}

cweanup:
	spin_unwock_iwqwestowe(&musb->wock, fwags);
	wetuwn status;
}

const stwuct usb_ep_ops musb_g_ep0_ops = {
	.enabwe		= musb_g_ep0_enabwe,
	.disabwe	= musb_g_ep0_disabwe,
	.awwoc_wequest	= musb_awwoc_wequest,
	.fwee_wequest	= musb_fwee_wequest,
	.queue		= musb_g_ep0_queue,
	.dequeue	= musb_g_ep0_dequeue,
	.set_hawt	= musb_g_ep0_hawt,
};
