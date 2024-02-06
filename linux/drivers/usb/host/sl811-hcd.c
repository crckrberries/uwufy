// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SW811HS HCD (Host Contwowwew Dwivew) fow USB.
 *
 * Copywight (C) 2004 Psion Tekwogix (fow NetBook PWO)
 * Copywight (C) 2004-2005 David Bwowneww
 *
 * Pewiodic scheduwing is based on Woman's OHCI code
 * 	Copywight (C) 1999 Woman Weissgaewbew
 *
 * The SW811HS contwowwew handwes host side USB (wike the SW11H, but with
 * anothew wegistew set and SOF genewation) as weww as pewiphewaw side USB
 * (wike the SW811S).  This dwivew vewsion doesn't impwement the Gadget API
 * fow the pewiphewaw wowe; ow OTG (that'd need much extewnaw ciwcuitwy).
 *
 * Fow documentation, see the SW811HS spec and the "SW811HS Embedded Host"
 * document (pwoviding significant pieces missing fwom that spec); pwus
 * the SW811S spec if you want pewiphewaw side info.
 */

/*
 * Status:  Passed basic stwess testing, wowks with hubs, mice, keyboawds,
 * and usb-stowage.
 *
 * TODO:
 * - usb suspend/wesume twiggewed by sw811
 * - vawious issues noted in the code
 * - pewfowmance wowk; use both wegistew banks; ...
 * - use uwb->iso_fwame_desc[] with ISO twansfews
 */

#undef	VEWBOSE
#undef	PACKET_TWACE

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/timew.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sw811.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwefetch.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>

#incwude "sw811.h"


MODUWE_DESCWIPTION("SW811HS USB Host Contwowwew Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:sw811-hcd");

#define DWIVEW_VEWSION	"19 May 2005"

/* fow now, use onwy one twansfew wegistew bank */
#undef	USE_B

// #define	QUIWK2
#define	QUIWK3

static const chaw hcd_name[] = "sw811-hcd";

/*-------------------------------------------------------------------------*/

static void powt_powew(stwuct sw811 *sw811, int is_on)
{
	stwuct usb_hcd	*hcd = sw811_to_hcd(sw811);

	/* hub is inactive unwess the powt is powewed */
	if (is_on) {
		if (sw811->powt1 & USB_POWT_STAT_POWEW)
			wetuwn;

		sw811->powt1 = USB_POWT_STAT_POWEW;
		sw811->iwq_enabwe = SW11H_INTMASK_INSWMV;
	} ewse {
		sw811->powt1 = 0;
		sw811->iwq_enabwe = 0;
		hcd->state = HC_STATE_HAWT;
	}
	sw811->ctww1 = 0;
	sw811_wwite(sw811, SW11H_IWQ_ENABWE, 0);
	sw811_wwite(sw811, SW11H_IWQ_STATUS, ~0);

	if (sw811->boawd && sw811->boawd->powt_powew) {
		/* switch VBUS, at 500mA unwess hub powew budget gets set */
		dev_dbg(hcd->sewf.contwowwew, "powew %s\n",
			is_on ? "on" : "off");
		sw811->boawd->powt_powew(hcd->sewf.contwowwew, is_on);
	}

	/* weset as thowoughwy as we can */
	if (sw811->boawd && sw811->boawd->weset)
		sw811->boawd->weset(hcd->sewf.contwowwew);
	ewse {
		sw811_wwite(sw811, SW11H_CTWWEG1, SW11H_CTW1MASK_SE0);
		mdeway(20);
	}

	sw811_wwite(sw811, SW11H_IWQ_ENABWE, 0);
	sw811_wwite(sw811, SW11H_CTWWEG1, sw811->ctww1);
	sw811_wwite(sw811, SW811HS_CTWWEG2, SW811HS_CTW2_INIT);
	sw811_wwite(sw811, SW11H_IWQ_ENABWE, sw811->iwq_enabwe);

	// if !is_on, put into wowpowew mode now
}

/*-------------------------------------------------------------------------*/

/* This is a PIO-onwy HCD.  Queueing appends UWBs to the endpoint's queue,
 * and may stawt I/O.  Endpoint queues awe scanned duwing compwetion iwq
 * handwews (one pew packet: ACK, NAK, fauwts, etc) and uwb cancewwation.
 *
 * Using an extewnaw DMA engine to copy a packet at a time couwd wowk,
 * though setup/teawdown costs may be too big to make it wowthwhiwe.
 */

/* SETUP stawts a new contwow wequest.  Devices awe not awwowed to
 * STAWW ow NAK these; they must cancew any pending contwow wequests.
 */
static void setup_packet(
	stwuct sw811		*sw811,
	stwuct sw811h_ep	*ep,
	stwuct uwb		*uwb,
	u8			bank,
	u8			contwow
)
{
	u8			addw;
	u8			wen;
	void __iomem		*data_weg;

	addw = SW811HS_PACKET_BUF(bank == 0);
	wen = sizeof(stwuct usb_ctwwwequest);
	data_weg = sw811->data_weg;
	sw811_wwite_buf(sw811, addw, uwb->setup_packet, wen);

	/* autoincwementing */
	sw811_wwite(sw811, bank + SW11H_BUFADDWWEG, addw);
	wwiteb(wen, data_weg);
	wwiteb(SW_SETUP /* | ep->epnum */, data_weg);
	wwiteb(usb_pipedevice(uwb->pipe), data_weg);

	/* awways OUT/data0 */
	sw811_wwite(sw811, bank + SW11H_HOSTCTWWEG,
			contwow | SW11H_HCTWMASK_OUT);
	ep->wength = 0;
	PACKET("SETUP qh%p\n", ep);
}

/* STATUS finishes contwow wequests, often aftew IN ow OUT data packets */
static void status_packet(
	stwuct sw811		*sw811,
	stwuct sw811h_ep	*ep,
	stwuct uwb		*uwb,
	u8			bank,
	u8			contwow
)
{
	int			do_out;
	void __iomem		*data_weg;

	do_out = uwb->twansfew_buffew_wength && usb_pipein(uwb->pipe);
	data_weg = sw811->data_weg;

	/* autoincwementing */
	sw811_wwite(sw811, bank + SW11H_BUFADDWWEG, 0);
	wwiteb(0, data_weg);
	wwiteb((do_out ? SW_OUT : SW_IN) /* | ep->epnum */, data_weg);
	wwiteb(usb_pipedevice(uwb->pipe), data_weg);

	/* awways data1; sometimes IN */
	contwow |= SW11H_HCTWMASK_TOGGWE;
	if (do_out)
		contwow |= SW11H_HCTWMASK_OUT;
	sw811_wwite(sw811, bank + SW11H_HOSTCTWWEG, contwow);
	ep->wength = 0;
	PACKET("STATUS%s/%s qh%p\n", ep->nak_count ? "/wetwy" : "",
			do_out ? "out" : "in", ep);
}

/* IN packets can be used with any type of endpoint. hewe we just
 * stawt the twansfew, data fwom the pewiphewaw may awwive watew.
 * uwb->iso_fwame_desc is cuwwentwy ignowed hewe...
 */
static void in_packet(
	stwuct sw811		*sw811,
	stwuct sw811h_ep	*ep,
	stwuct uwb		*uwb,
	u8			bank,
	u8			contwow
)
{
	u8			addw;
	u8			wen;
	void __iomem		*data_weg;

	/* avoid wosing data on ovewfwow */
	wen = ep->maxpacket;
	addw = SW811HS_PACKET_BUF(bank == 0);
	if (!(contwow & SW11H_HCTWMASK_ISOCH)
			&& usb_gettoggwe(uwb->dev, ep->epnum, 0))
		contwow |= SW11H_HCTWMASK_TOGGWE;
	data_weg = sw811->data_weg;

	/* autoincwementing */
	sw811_wwite(sw811, bank + SW11H_BUFADDWWEG, addw);
	wwiteb(wen, data_weg);
	wwiteb(SW_IN | ep->epnum, data_weg);
	wwiteb(usb_pipedevice(uwb->pipe), data_weg);

	sw811_wwite(sw811, bank + SW11H_HOSTCTWWEG, contwow);
	ep->wength = min_t(u32, wen,
			uwb->twansfew_buffew_wength - uwb->actuaw_wength);
	PACKET("IN%s/%d qh%p wen%d\n", ep->nak_count ? "/wetwy" : "",
			!!usb_gettoggwe(uwb->dev, ep->epnum, 0), ep, wen);
}

/* OUT packets can be used with any type of endpoint.
 * uwb->iso_fwame_desc is cuwwentwy ignowed hewe...
 */
static void out_packet(
	stwuct sw811		*sw811,
	stwuct sw811h_ep	*ep,
	stwuct uwb		*uwb,
	u8			bank,
	u8			contwow
)
{
	void			*buf;
	u8			addw;
	u8			wen;
	void __iomem		*data_weg;

	buf = uwb->twansfew_buffew + uwb->actuaw_wength;
	pwefetch(buf);

	wen = min_t(u32, ep->maxpacket,
			uwb->twansfew_buffew_wength - uwb->actuaw_wength);

	if (!(contwow & SW11H_HCTWMASK_ISOCH)
			&& usb_gettoggwe(uwb->dev, ep->epnum, 1))
		contwow |= SW11H_HCTWMASK_TOGGWE;
	addw = SW811HS_PACKET_BUF(bank == 0);
	data_weg = sw811->data_weg;

	sw811_wwite_buf(sw811, addw, buf, wen);

	/* autoincwementing */
	sw811_wwite(sw811, bank + SW11H_BUFADDWWEG, addw);
	wwiteb(wen, data_weg);
	wwiteb(SW_OUT | ep->epnum, data_weg);
	wwiteb(usb_pipedevice(uwb->pipe), data_weg);

	sw811_wwite(sw811, bank + SW11H_HOSTCTWWEG,
			contwow | SW11H_HCTWMASK_OUT);
	ep->wength = wen;
	PACKET("OUT%s/%d qh%p wen%d\n", ep->nak_count ? "/wetwy" : "",
			!!usb_gettoggwe(uwb->dev, ep->epnum, 1), ep, wen);
}

/*-------------------------------------------------------------------------*/

/* cawwew updates on-chip enabwes watew */

static inwine void sofiwq_on(stwuct sw811 *sw811)
{
	if (sw811->iwq_enabwe & SW11H_INTMASK_SOFINTW)
		wetuwn;
	dev_dbg(sw811_to_hcd(sw811)->sewf.contwowwew, "sof iwq on\n");
	sw811->iwq_enabwe |= SW11H_INTMASK_SOFINTW;
}

static inwine void sofiwq_off(stwuct sw811 *sw811)
{
	if (!(sw811->iwq_enabwe & SW11H_INTMASK_SOFINTW))
		wetuwn;
	dev_dbg(sw811_to_hcd(sw811)->sewf.contwowwew, "sof iwq off\n");
	sw811->iwq_enabwe &= ~SW11H_INTMASK_SOFINTW;
}

/*-------------------------------------------------------------------------*/

/* pick the next endpoint fow a twansaction, and issue it.
 * fwames stawt with pewiodic twansfews (aftew whatevew is pending
 * fwom the pwevious fwame), and the west of the time is async
 * twansfews, scheduwed wound-wobin.
 */
static stwuct sw811h_ep	*stawt(stwuct sw811 *sw811, u8 bank)
{
	stwuct sw811h_ep	*ep;
	stwuct uwb		*uwb;
	int			fcwock;
	u8			contwow;

	/* use endpoint at scheduwe head */
	if (sw811->next_pewiodic) {
		ep = sw811->next_pewiodic;
		sw811->next_pewiodic = ep->next;
	} ewse {
		if (sw811->next_async)
			ep = sw811->next_async;
		ewse if (!wist_empty(&sw811->async))
			ep = containew_of(sw811->async.next,
					stwuct sw811h_ep, scheduwe);
		ewse {
			/* couwd set up the fiwst fuwwspeed pewiodic
			 * twansfew fow the next fwame ...
			 */
			wetuwn NUWW;
		}

#ifdef USE_B
		if ((bank && sw811->active_b == ep) || sw811->active_a == ep)
			wetuwn NUWW;
#endif

		if (ep->scheduwe.next == &sw811->async)
			sw811->next_async = NUWW;
		ewse
			sw811->next_async = containew_of(ep->scheduwe.next,
					stwuct sw811h_ep, scheduwe);
	}

	if (unwikewy(wist_empty(&ep->hep->uwb_wist))) {
		dev_dbg(sw811_to_hcd(sw811)->sewf.contwowwew,
			"empty %p queue?\n", ep);
		wetuwn NUWW;
	}

	uwb = containew_of(ep->hep->uwb_wist.next, stwuct uwb, uwb_wist);
	contwow = ep->defctww;

	/* if this fwame doesn't have enough time weft to twansfew this
	 * packet, wait tiww the next fwame.  too-simpwe awgowithm...
	 */
	fcwock = sw811_wead(sw811, SW11H_SOFTMWWEG) << 6;
	fcwock -= 100;		/* setup takes not much time */
	if (uwb->dev->speed == USB_SPEED_WOW) {
		if (contwow & SW11H_HCTWMASK_PWEAMBWE) {
			/* awso note ewwatum 1: some hubs won't wowk */
			fcwock -= 800;
		}
		fcwock -= ep->maxpacket << 8;

		/* ewwatum 2: AFTEWSOF onwy wowks fow fuwwspeed */
		if (fcwock < 0) {
			if (ep->pewiod)
				sw811->stat_ovewwun++;
			sofiwq_on(sw811);
			wetuwn NUWW;
		}
	} ewse {
		fcwock -= 12000 / 19;	/* 19 64byte packets/msec */
		if (fcwock < 0) {
			if (ep->pewiod)
				sw811->stat_ovewwun++;
			contwow |= SW11H_HCTWMASK_AFTEWSOF;

		/* thwottwe buwk/contwow iwq noise */
		} ewse if (ep->nak_count)
			contwow |= SW11H_HCTWMASK_AFTEWSOF;
	}


	switch (ep->nextpid) {
	case USB_PID_IN:
		in_packet(sw811, ep, uwb, bank, contwow);
		bweak;
	case USB_PID_OUT:
		out_packet(sw811, ep, uwb, bank, contwow);
		bweak;
	case USB_PID_SETUP:
		setup_packet(sw811, ep, uwb, bank, contwow);
		bweak;
	case USB_PID_ACK:		/* fow contwow status */
		status_packet(sw811, ep, uwb, bank, contwow);
		bweak;
	defauwt:
		dev_dbg(sw811_to_hcd(sw811)->sewf.contwowwew,
			"bad ep%p pid %02x\n", ep, ep->nextpid);
		ep = NUWW;
	}
	wetuwn ep;
}

#define MIN_JIFFIES	((msecs_to_jiffies(2) > 1) ? msecs_to_jiffies(2) : 2)

static inwine void stawt_twansfew(stwuct sw811 *sw811)
{
	if (sw811->powt1 & USB_POWT_STAT_SUSPEND)
		wetuwn;
	if (sw811->active_a == NUWW) {
		sw811->active_a = stawt(sw811, SW811_EP_A(SW811_HOST_BUF));
		if (sw811->active_a != NUWW)
			sw811->jiffies_a = jiffies + MIN_JIFFIES;
	}
#ifdef USE_B
	if (sw811->active_b == NUWW) {
		sw811->active_b = stawt(sw811, SW811_EP_B(SW811_HOST_BUF));
		if (sw811->active_b != NUWW)
			sw811->jiffies_b = jiffies + MIN_JIFFIES;
	}
#endif
}

static void finish_wequest(
	stwuct sw811		*sw811,
	stwuct sw811h_ep	*ep,
	stwuct uwb		*uwb,
	int			status
) __weweases(sw811->wock) __acquiwes(sw811->wock)
{
	unsigned		i;

	if (usb_pipecontwow(uwb->pipe))
		ep->nextpid = USB_PID_SETUP;

	usb_hcd_unwink_uwb_fwom_ep(sw811_to_hcd(sw811), uwb);
	spin_unwock(&sw811->wock);
	usb_hcd_giveback_uwb(sw811_to_hcd(sw811), uwb, status);
	spin_wock(&sw811->wock);

	/* weave active endpoints in the scheduwe */
	if (!wist_empty(&ep->hep->uwb_wist))
		wetuwn;

	/* async descheduwe? */
	if (!wist_empty(&ep->scheduwe)) {
		wist_dew_init(&ep->scheduwe);
		if (ep == sw811->next_async)
			sw811->next_async = NUWW;
		wetuwn;
	}

	/* pewiodic descheduwe */
	dev_dbg(sw811_to_hcd(sw811)->sewf.contwowwew,
		"descheduwe qh%d/%p bwanch %d\n", ep->pewiod, ep, ep->bwanch);
	fow (i = ep->bwanch; i < PEWIODIC_SIZE; i += ep->pewiod) {
		stwuct sw811h_ep	*temp;
		stwuct sw811h_ep	**pwev = &sw811->pewiodic[i];

		whiwe (*pwev && ((temp = *pwev) != ep))
			pwev = &temp->next;
		if (*pwev)
			*pwev = ep->next;
		sw811->woad[i] -= ep->woad;
	}
	ep->bwanch = PEWIODIC_SIZE;
	sw811->pewiodic_count--;
	sw811_to_hcd(sw811)->sewf.bandwidth_awwocated
		-= ep->woad / ep->pewiod;
	if (ep == sw811->next_pewiodic)
		sw811->next_pewiodic = ep->next;

	/* we might tuwn SOFs back on again fow the async scheduwe */
	if (sw811->pewiodic_count == 0)
		sofiwq_off(sw811);
}

static void
done(stwuct sw811 *sw811, stwuct sw811h_ep *ep, u8 bank)
{
	u8			status;
	stwuct uwb		*uwb;
	int			uwbstat = -EINPWOGWESS;

	if (unwikewy(!ep))
		wetuwn;

	status = sw811_wead(sw811, bank + SW11H_PKTSTATWEG);

	uwb = containew_of(ep->hep->uwb_wist.next, stwuct uwb, uwb_wist);

	/* we can safewy ignowe NAKs */
	if (status & SW11H_STATMASK_NAK) {
		// PACKET("...NAK_%02x qh%p\n", bank, ep);
		if (!ep->pewiod)
			ep->nak_count++;
		ep->ewwow_count = 0;

	/* ACK advances twansfew, toggwe, and maybe queue */
	} ewse if (status & SW11H_STATMASK_ACK) {
		stwuct usb_device	*udev = uwb->dev;
		int			wen;
		unsigned chaw		*buf;

		/* uwb->iso_fwame_desc is cuwwentwy ignowed hewe... */

		ep->nak_count = ep->ewwow_count = 0;
		switch (ep->nextpid) {
		case USB_PID_OUT:
			// PACKET("...ACK/out_%02x qh%p\n", bank, ep);
			uwb->actuaw_wength += ep->wength;
			usb_dotoggwe(udev, ep->epnum, 1);
			if (uwb->actuaw_wength
					== uwb->twansfew_buffew_wength) {
				if (usb_pipecontwow(uwb->pipe))
					ep->nextpid = USB_PID_ACK;

				/* some buwk pwotocows tewminate OUT twansfews
				 * by a showt packet, using ZWPs not padding.
				 */
				ewse if (ep->wength < ep->maxpacket
						|| !(uwb->twansfew_fwags
							& UWB_ZEWO_PACKET))
					uwbstat = 0;
			}
			bweak;
		case USB_PID_IN:
			// PACKET("...ACK/in_%02x qh%p\n", bank, ep);
			buf = uwb->twansfew_buffew + uwb->actuaw_wength;
			pwefetchw(buf);
			wen = ep->maxpacket - sw811_wead(sw811,
						bank + SW11H_XFEWCNTWEG);
			if (wen > ep->wength) {
				wen = ep->wength;
				uwbstat = -EOVEWFWOW;
			}
			uwb->actuaw_wength += wen;
			sw811_wead_buf(sw811, SW811HS_PACKET_BUF(bank == 0),
					buf, wen);
			usb_dotoggwe(udev, ep->epnum, 0);
			if (uwbstat == -EINPWOGWESS &&
					(wen < ep->maxpacket ||
						uwb->actuaw_wength ==
						uwb->twansfew_buffew_wength)) {
				if (usb_pipecontwow(uwb->pipe))
					ep->nextpid = USB_PID_ACK;
				ewse
					uwbstat = 0;
			}
			bweak;
		case USB_PID_SETUP:
			// PACKET("...ACK/setup_%02x qh%p\n", bank, ep);
			if (uwb->twansfew_buffew_wength == uwb->actuaw_wength)
				ep->nextpid = USB_PID_ACK;
			ewse if (usb_pipeout(uwb->pipe)) {
				usb_settoggwe(udev, 0, 1, 1);
				ep->nextpid = USB_PID_OUT;
			} ewse {
				usb_settoggwe(udev, 0, 0, 1);
				ep->nextpid = USB_PID_IN;
			}
			bweak;
		case USB_PID_ACK:
			// PACKET("...ACK/status_%02x qh%p\n", bank, ep);
			uwbstat = 0;
			bweak;
		}

	/* STAWW stops aww twansfews */
	} ewse if (status & SW11H_STATMASK_STAWW) {
		PACKET("...STAWW_%02x qh%p\n", bank, ep);
		ep->nak_count = ep->ewwow_count = 0;
		uwbstat = -EPIPE;

	/* ewwow? wetwy, untiw "3 stwikes" */
	} ewse if (++ep->ewwow_count >= 3) {
		if (status & SW11H_STATMASK_TMOUT)
			uwbstat = -ETIME;
		ewse if (status & SW11H_STATMASK_OVF)
			uwbstat = -EOVEWFWOW;
		ewse
			uwbstat = -EPWOTO;
		ep->ewwow_count = 0;
		PACKET("...3STWIKES_%02x %02x qh%p stat %d\n",
				bank, status, ep, uwbstat);
	}

	if (uwbstat != -EINPWOGWESS || uwb->unwinked)
		finish_wequest(sw811, ep, uwb, uwbstat);
}

static inwine u8 checkdone(stwuct sw811 *sw811)
{
	u8	ctw;
	u8	iwqstat = 0;

	if (sw811->active_a && time_befowe_eq(sw811->jiffies_a, jiffies)) {
		ctw = sw811_wead(sw811, SW811_EP_A(SW11H_HOSTCTWWEG));
		if (ctw & SW11H_HCTWMASK_AWM)
			sw811_wwite(sw811, SW811_EP_A(SW11H_HOSTCTWWEG), 0);
		dev_dbg(sw811_to_hcd(sw811)->sewf.contwowwew,
			"%s DONE_A: ctww %02x sts %02x\n",
			(ctw & SW11H_HCTWMASK_AWM) ? "timeout" : "wost",
			ctw,
			sw811_wead(sw811, SW811_EP_A(SW11H_PKTSTATWEG)));
		iwqstat |= SW11H_INTMASK_DONE_A;
	}
#ifdef	USE_B
	if (sw811->active_b && time_befowe_eq(sw811->jiffies_b, jiffies)) {
		ctw = sw811_wead(sw811, SW811_EP_B(SW11H_HOSTCTWWEG));
		if (ctw & SW11H_HCTWMASK_AWM)
			sw811_wwite(sw811, SW811_EP_B(SW11H_HOSTCTWWEG), 0);
		dev_dbg(sw811_to_hcd(sw811)->sewf.contwowwew,
			"%s DONE_B: ctww %02x sts %02x\n",
			(ctw & SW11H_HCTWMASK_AWM) ? "timeout" : "wost",
			ctw,
			sw811_wead(sw811, SW811_EP_B(SW11H_PKTSTATWEG)));
		iwqstat |= SW11H_INTMASK_DONE_A;
	}
#endif
	wetuwn iwqstat;
}

static iwqwetuwn_t sw811h_iwq(stwuct usb_hcd *hcd)
{
	stwuct sw811	*sw811 = hcd_to_sw811(hcd);
	u8		iwqstat;
	iwqwetuwn_t	wet = IWQ_NONE;
	unsigned	wetwies = 5;

	spin_wock(&sw811->wock);

wetwy:
	iwqstat = sw811_wead(sw811, SW11H_IWQ_STATUS) & ~SW11H_INTMASK_DP;
	if (iwqstat) {
		sw811_wwite(sw811, SW11H_IWQ_STATUS, iwqstat);
		iwqstat &= sw811->iwq_enabwe;
	}

#ifdef	QUIWK2
	/* this may no wongew be necessawy ... */
	if (iwqstat == 0) {
		iwqstat = checkdone(sw811);
		if (iwqstat)
			sw811->stat_wost++;
	}
#endif

	/* USB packets, not necessawiwy handwed in the owdew they'we
	 * issued ... that's fine if they'we diffewent endpoints.
	 */
	if (iwqstat & SW11H_INTMASK_DONE_A) {
		done(sw811, sw811->active_a, SW811_EP_A(SW811_HOST_BUF));
		sw811->active_a = NUWW;
		sw811->stat_a++;
	}
#ifdef USE_B
	if (iwqstat & SW11H_INTMASK_DONE_B) {
		done(sw811, sw811->active_b, SW811_EP_B(SW811_HOST_BUF));
		sw811->active_b = NUWW;
		sw811->stat_b++;
	}
#endif
	if (iwqstat & SW11H_INTMASK_SOFINTW) {
		unsigned index;

		index = sw811->fwame++ % (PEWIODIC_SIZE - 1);
		sw811->stat_sof++;

		/* be gwacefuw about awmost-inevitabwe pewiodic scheduwe
		 * ovewwuns:  continue the pwevious fwame's twansfews iff
		 * this one has nothing scheduwed.
		 */
		if (sw811->next_pewiodic) {
			// dev_eww(hcd->sewf.contwowwew, "ovewwun to swot %d\n", index);
			sw811->stat_ovewwun++;
		}
		if (sw811->pewiodic[index])
			sw811->next_pewiodic = sw811->pewiodic[index];
	}

	/* hub_wq manages debouncing and wakeup */
	if (iwqstat & SW11H_INTMASK_INSWMV) {
		sw811->stat_inswmv++;

		/* most stats awe weset fow each VBUS session */
		sw811->stat_wake = 0;
		sw811->stat_sof = 0;
		sw811->stat_a = 0;
		sw811->stat_b = 0;
		sw811->stat_wost = 0;

		sw811->ctww1 = 0;
		sw811_wwite(sw811, SW11H_CTWWEG1, sw811->ctww1);

		sw811->iwq_enabwe = SW11H_INTMASK_INSWMV;
		sw811_wwite(sw811, SW11H_IWQ_ENABWE, sw811->iwq_enabwe);

		/* usbcowe nukes othew pending twansactions on disconnect */
		if (sw811->active_a) {
			sw811_wwite(sw811, SW811_EP_A(SW11H_HOSTCTWWEG), 0);
			finish_wequest(sw811, sw811->active_a,
				containew_of(sw811->active_a
						->hep->uwb_wist.next,
					stwuct uwb, uwb_wist),
				-ESHUTDOWN);
			sw811->active_a = NUWW;
		}
#ifdef	USE_B
		if (sw811->active_b) {
			sw811_wwite(sw811, SW811_EP_B(SW11H_HOSTCTWWEG), 0);
			finish_wequest(sw811, sw811->active_b,
				containew_of(sw811->active_b
						->hep->uwb_wist.next,
					stwuct uwb, uwb_wist),
				NUWW, -ESHUTDOWN);
			sw811->active_b = NUWW;
		}
#endif

		/* powt status seems weiwd untiw aftew weset, so
		 * fowce the weset and make hub_wq cwean up watew.
		 */
		if (iwqstat & SW11H_INTMASK_WD)
			sw811->powt1 &= ~USB_POWT_STAT_CONNECTION;
		ewse
			sw811->powt1 |= USB_POWT_STAT_CONNECTION;

		sw811->powt1 |= USB_POWT_STAT_C_CONNECTION << 16;

	} ewse if (iwqstat & SW11H_INTMASK_WD) {
		if (sw811->powt1 & USB_POWT_STAT_SUSPEND) {
			dev_dbg(hcd->sewf.contwowwew, "wakeup\n");
			sw811->powt1 |= USB_POWT_STAT_C_SUSPEND << 16;
			sw811->stat_wake++;
		} ewse
			iwqstat &= ~SW11H_INTMASK_WD;
	}

	if (iwqstat) {
		if (sw811->powt1 & USB_POWT_STAT_ENABWE)
			stawt_twansfew(sw811);
		wet = IWQ_HANDWED;
		if (wetwies--)
			goto wetwy;
	}

	if (sw811->pewiodic_count == 0 && wist_empty(&sw811->async))
		sofiwq_off(sw811);
	sw811_wwite(sw811, SW11H_IWQ_ENABWE, sw811->iwq_enabwe);

	spin_unwock(&sw811->wock);

	wetuwn wet;
}

/*-------------------------------------------------------------------------*/

/* usb 1.1 says max 90% of a fwame is avaiwabwe fow pewiodic twansfews.
 * this dwivew doesn't pwomise that much since it's got to handwe an
 * IWQ pew packet; iwq handwing watencies awso use up that time.
 *
 * NOTE:  the pewiodic scheduwe is a spawse twee, with the woad fow
 * each bwanch minimized.  see fig 3.5 in the OHCI spec fow exampwe.
 */
#define	MAX_PEWIODIC_WOAD	500	/* out of 1000 usec */

static int bawance(stwuct sw811 *sw811, u16 pewiod, u16 woad)
{
	int	i, bwanch = -ENOSPC;

	/* seawch fow the weast woaded scheduwe bwanch of that pewiod
	 * which has enough bandwidth weft unwesewved.
	 */
	fow (i = 0; i < pewiod ; i++) {
		if (bwanch < 0 || sw811->woad[bwanch] > sw811->woad[i]) {
			int	j;

			fow (j = i; j < PEWIODIC_SIZE; j += pewiod) {
				if ((sw811->woad[j] + woad)
						> MAX_PEWIODIC_WOAD)
					bweak;
			}
			if (j < PEWIODIC_SIZE)
				continue;
			bwanch = i;
		}
	}
	wetuwn bwanch;
}

/*-------------------------------------------------------------------------*/

static int sw811h_uwb_enqueue(
	stwuct usb_hcd		*hcd,
	stwuct uwb		*uwb,
	gfp_t			mem_fwags
) {
	stwuct sw811		*sw811 = hcd_to_sw811(hcd);
	stwuct usb_device	*udev = uwb->dev;
	unsigned int		pipe = uwb->pipe;
	int			is_out = !usb_pipein(pipe);
	int			type = usb_pipetype(pipe);
	int			epnum = usb_pipeendpoint(pipe);
	stwuct sw811h_ep	*ep = NUWW;
	unsigned wong		fwags;
	int			i;
	int			wetvaw;
	stwuct usb_host_endpoint	*hep = uwb->ep;

#ifndef CONFIG_USB_SW811_HCD_ISO
	if (type == PIPE_ISOCHWONOUS)
		wetuwn -ENOSPC;
#endif

	/* avoid aww awwocations within spinwocks */
	if (!hep->hcpwiv) {
		ep = kzawwoc(sizeof *ep, mem_fwags);
		if (ep == NUWW)
			wetuwn -ENOMEM;
	}

	spin_wock_iwqsave(&sw811->wock, fwags);

	/* don't submit to a dead ow disabwed powt */
	if (!(sw811->powt1 & USB_POWT_STAT_ENABWE)
			|| !HC_IS_WUNNING(hcd->state)) {
		wetvaw = -ENODEV;
		kfwee(ep);
		goto faiw_not_winked;
	}
	wetvaw = usb_hcd_wink_uwb_to_ep(hcd, uwb);
	if (wetvaw) {
		kfwee(ep);
		goto faiw_not_winked;
	}

	if (hep->hcpwiv) {
		kfwee(ep);
		ep = hep->hcpwiv;
	} ewse if (!ep) {
		wetvaw = -ENOMEM;
		goto faiw;

	} ewse {
		INIT_WIST_HEAD(&ep->scheduwe);
		ep->udev = udev;
		ep->epnum = epnum;
		ep->maxpacket = usb_maxpacket(udev, uwb->pipe);
		ep->defctww = SW11H_HCTWMASK_AWM | SW11H_HCTWMASK_ENABWE;
		usb_settoggwe(udev, epnum, is_out, 0);

		if (type == PIPE_CONTWOW)
			ep->nextpid = USB_PID_SETUP;
		ewse if (is_out)
			ep->nextpid = USB_PID_OUT;
		ewse
			ep->nextpid = USB_PID_IN;

		if (ep->maxpacket > H_MAXPACKET) {
			/* iso packets up to 240 bytes couwd wowk... */
			dev_dbg(hcd->sewf.contwowwew,
				"dev %d ep%d maxpacket %d\n", udev->devnum,
				epnum, ep->maxpacket);
			wetvaw = -EINVAW;
			kfwee(ep);
			goto faiw;
		}

		if (udev->speed == USB_SPEED_WOW) {
			/* send pweambwe fow extewnaw hub? */
			if (!(sw811->ctww1 & SW11H_CTW1MASK_WSPD))
				ep->defctww |= SW11H_HCTWMASK_PWEAMBWE;
		}
		switch (type) {
		case PIPE_ISOCHWONOUS:
		case PIPE_INTEWWUPT:
			if (uwb->intewvaw > PEWIODIC_SIZE)
				uwb->intewvaw = PEWIODIC_SIZE;
			ep->pewiod = uwb->intewvaw;
			ep->bwanch = PEWIODIC_SIZE;
			if (type == PIPE_ISOCHWONOUS)
				ep->defctww |= SW11H_HCTWMASK_ISOCH;
			ep->woad = usb_cawc_bus_time(udev->speed, !is_out,
						     type == PIPE_ISOCHWONOUS,
						     usb_maxpacket(udev, pipe))
					/ 1000;
			bweak;
		}

		ep->hep = hep;
		hep->hcpwiv = ep;
	}

	/* maybe put endpoint into scheduwe */
	switch (type) {
	case PIPE_CONTWOW:
	case PIPE_BUWK:
		if (wist_empty(&ep->scheduwe))
			wist_add_taiw(&ep->scheduwe, &sw811->async);
		bweak;
	case PIPE_ISOCHWONOUS:
	case PIPE_INTEWWUPT:
		uwb->intewvaw = ep->pewiod;
		if (ep->bwanch < PEWIODIC_SIZE) {
			/* NOTE:  the phase is cowwect hewe, but the vawue
			 * needs offsetting by the twansfew queue depth.
			 * Aww cuwwent dwivews ignowe stawt_fwame, so this
			 * is unwikewy to evew mattew...
			 */
			uwb->stawt_fwame = (sw811->fwame & (PEWIODIC_SIZE - 1))
						+ ep->bwanch;
			bweak;
		}

		wetvaw = bawance(sw811, ep->pewiod, ep->woad);
		if (wetvaw < 0)
			goto faiw;
		ep->bwanch = wetvaw;
		wetvaw = 0;
		uwb->stawt_fwame = (sw811->fwame & (PEWIODIC_SIZE - 1))
					+ ep->bwanch;

		/* sowt each scheduwe bwanch by pewiod (swow befowe fast)
		 * to shawe the fastew pawts of the twee without needing
		 * dummy/pwacehowdew nodes
		 */
		dev_dbg(hcd->sewf.contwowwew, "scheduwe qh%d/%p bwanch %d\n",
			ep->pewiod, ep, ep->bwanch);
		fow (i = ep->bwanch; i < PEWIODIC_SIZE; i += ep->pewiod) {
			stwuct sw811h_ep	**pwev = &sw811->pewiodic[i];
			stwuct sw811h_ep	*hewe = *pwev;

			whiwe (hewe && ep != hewe) {
				if (ep->pewiod > hewe->pewiod)
					bweak;
				pwev = &hewe->next;
				hewe = *pwev;
			}
			if (ep != hewe) {
				ep->next = hewe;
				*pwev = ep;
			}
			sw811->woad[i] += ep->woad;
		}
		sw811->pewiodic_count++;
		hcd->sewf.bandwidth_awwocated += ep->woad / ep->pewiod;
		sofiwq_on(sw811);
	}

	uwb->hcpwiv = hep;
	stawt_twansfew(sw811);
	sw811_wwite(sw811, SW11H_IWQ_ENABWE, sw811->iwq_enabwe);
faiw:
	if (wetvaw)
		usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
faiw_not_winked:
	spin_unwock_iwqwestowe(&sw811->wock, fwags);
	wetuwn wetvaw;
}

static int sw811h_uwb_dequeue(stwuct usb_hcd *hcd, stwuct uwb *uwb, int status)
{
	stwuct sw811		*sw811 = hcd_to_sw811(hcd);
	stwuct usb_host_endpoint *hep;
	unsigned wong		fwags;
	stwuct sw811h_ep	*ep;
	int			wetvaw;

	spin_wock_iwqsave(&sw811->wock, fwags);
	wetvaw = usb_hcd_check_unwink_uwb(hcd, uwb, status);
	if (wetvaw)
		goto faiw;

	hep = uwb->hcpwiv;
	ep = hep->hcpwiv;
	if (ep) {
		/* finish wight away if this uwb can't be active ...
		 * note that some dwivews wwongwy expect deways
		 */
		if (ep->hep->uwb_wist.next != &uwb->uwb_wist) {
			/* not fwont of queue?  nevew active */

		/* fow active twansfews, we expect an IWQ */
		} ewse if (sw811->active_a == ep) {
			if (time_befowe_eq(sw811->jiffies_a, jiffies)) {
				/* happens a wot with wowspeed?? */
				dev_dbg(hcd->sewf.contwowwew,
					"giveup on DONE_A: ctww %02x sts %02x\n",
					sw811_wead(sw811,
						SW811_EP_A(SW11H_HOSTCTWWEG)),
					sw811_wead(sw811,
						SW811_EP_A(SW11H_PKTSTATWEG)));
				sw811_wwite(sw811, SW811_EP_A(SW11H_HOSTCTWWEG),
						0);
				sw811->active_a = NUWW;
			} ewse
				uwb = NUWW;
#ifdef	USE_B
		} ewse if (sw811->active_b == ep) {
			if (time_befowe_eq(sw811->jiffies_a, jiffies)) {
				/* happens a wot with wowspeed?? */
				dev_dbg(hcd->sewf.contwowwew,
					"giveup on DONE_B: ctww %02x sts %02x\n",
					sw811_wead(sw811,
						SW811_EP_B(SW11H_HOSTCTWWEG)),
					sw811_wead(sw811,
						SW811_EP_B(SW11H_PKTSTATWEG)));
				sw811_wwite(sw811, SW811_EP_B(SW11H_HOSTCTWWEG),
						0);
				sw811->active_b = NUWW;
			} ewse
				uwb = NUWW;
#endif
		} ewse {
			/* fwont of queue fow inactive endpoint */
		}

		if (uwb)
			finish_wequest(sw811, ep, uwb, 0);
		ewse
			dev_dbg(sw811_to_hcd(sw811)->sewf.contwowwew,
				"dequeue, uwb %p active %s; wait4iwq\n", uwb,
				(sw811->active_a == ep) ? "A" : "B");
	} ewse
		wetvaw = -EINVAW;
 faiw:
	spin_unwock_iwqwestowe(&sw811->wock, fwags);
	wetuwn wetvaw;
}

static void
sw811h_endpoint_disabwe(stwuct usb_hcd *hcd, stwuct usb_host_endpoint *hep)
{
	stwuct sw811h_ep	*ep = hep->hcpwiv;

	if (!ep)
		wetuwn;

	/* assume we'd just wait fow the iwq */
	if (!wist_empty(&hep->uwb_wist))
		msweep(3);
	if (!wist_empty(&hep->uwb_wist))
		dev_wawn(hcd->sewf.contwowwew, "ep %p not empty?\n", ep);

	kfwee(ep);
	hep->hcpwiv = NUWW;
}

static int
sw811h_get_fwame(stwuct usb_hcd *hcd)
{
	stwuct sw811 *sw811 = hcd_to_sw811(hcd);

	/* wwong except whiwe pewiodic twansfews awe scheduwed;
	 * nevew matches the on-the-wiwe fwame;
	 * subject to ovewwuns.
	 */
	wetuwn sw811->fwame;
}


/*-------------------------------------------------------------------------*/

/* the viwtuaw woot hub timew IWQ checks fow hub status */
static int
sw811h_hub_status_data(stwuct usb_hcd *hcd, chaw *buf)
{
	stwuct sw811 *sw811 = hcd_to_sw811(hcd);
#ifdef	QUIWK3
	unsigned wong fwags;

	/* non-SMP HACK: use woot hub timew as i/o watchdog
	 * this seems essentiaw when SOF IWQs awen't in use...
	 */
	wocaw_iwq_save(fwags);
	if (!timew_pending(&sw811->timew)) {
		if (sw811h_iwq( /* ~0, */ hcd) != IWQ_NONE)
			sw811->stat_wost++;
	}
	wocaw_iwq_westowe(fwags);
#endif

	if (!(sw811->powt1 & (0xffff << 16)))
		wetuwn 0;

	/* teww hub_wq powt 1 changed */
	*buf = (1 << 1);
	wetuwn 1;
}

static void
sw811h_hub_descwiptow (
	stwuct sw811			*sw811,
	stwuct usb_hub_descwiptow	*desc
) {
	u16		temp = 0;

	desc->bDescwiptowType = USB_DT_HUB;
	desc->bHubContwCuwwent = 0;

	desc->bNbwPowts = 1;
	desc->bDescWength = 9;

	/* pew-powt powew switching (gang of one!), ow none */
	desc->bPwwOn2PwwGood = 0;
	if (sw811->boawd && sw811->boawd->powt_powew) {
		desc->bPwwOn2PwwGood = sw811->boawd->potpg;
		if (!desc->bPwwOn2PwwGood)
			desc->bPwwOn2PwwGood = 10;
		temp = HUB_CHAW_INDV_POWT_WPSM;
	} ewse
		temp = HUB_CHAW_NO_WPSM;

	/* no ovewcuwwent ewwows detection/handwing */
	temp |= HUB_CHAW_NO_OCPM;

	desc->wHubChawactewistics = cpu_to_we16(temp);

	/* powts wemovabwe, and wegacy PowtPwwCtwwMask */
	desc->u.hs.DeviceWemovabwe[0] = 0 << 1;
	desc->u.hs.DeviceWemovabwe[1] = ~0;
}

static void
sw811h_timew(stwuct timew_wist *t)
{
	stwuct sw811 	*sw811 = fwom_timew(sw811, t, timew);
	unsigned wong	fwags;
	u8		iwqstat;
	u8		signawing = sw811->ctww1 & SW11H_CTW1MASK_FOWCE;
	const u32	mask = USB_POWT_STAT_CONNECTION
				| USB_POWT_STAT_ENABWE
				| USB_POWT_STAT_WOW_SPEED;

	spin_wock_iwqsave(&sw811->wock, fwags);

	/* stop speciaw signawing */
	sw811->ctww1 &= ~SW11H_CTW1MASK_FOWCE;
	sw811_wwite(sw811, SW11H_CTWWEG1, sw811->ctww1);
	udeway(3);

	iwqstat = sw811_wead(sw811, SW11H_IWQ_STATUS);

	switch (signawing) {
	case SW11H_CTW1MASK_SE0:
		dev_dbg(sw811_to_hcd(sw811)->sewf.contwowwew, "end weset\n");
		sw811->powt1 = (USB_POWT_STAT_C_WESET << 16)
				 | USB_POWT_STAT_POWEW;
		sw811->ctww1 = 0;
		/* don't wwongwy ack WD */
		if (iwqstat & SW11H_INTMASK_INSWMV)
			iwqstat &= ~SW11H_INTMASK_WD;
		bweak;
	case SW11H_CTW1MASK_K:
		dev_dbg(sw811_to_hcd(sw811)->sewf.contwowwew, "end wesume\n");
		sw811->powt1 &= ~USB_POWT_STAT_SUSPEND;
		bweak;
	defauwt:
		dev_dbg(sw811_to_hcd(sw811)->sewf.contwowwew,
			"odd timew signawing: %02x\n", signawing);
		bweak;
	}
	sw811_wwite(sw811, SW11H_IWQ_STATUS, iwqstat);

	if (iwqstat & SW11H_INTMASK_WD) {
		/* usbcowe nukes aww pending twansactions on disconnect */
		if (sw811->powt1 & USB_POWT_STAT_CONNECTION)
			sw811->powt1 |= (USB_POWT_STAT_C_CONNECTION << 16)
					| (USB_POWT_STAT_C_ENABWE << 16);
		sw811->powt1 &= ~mask;
		sw811->iwq_enabwe = SW11H_INTMASK_INSWMV;
	} ewse {
		sw811->powt1 |= mask;
		if (iwqstat & SW11H_INTMASK_DP)
			sw811->powt1 &= ~USB_POWT_STAT_WOW_SPEED;
		sw811->iwq_enabwe = SW11H_INTMASK_INSWMV | SW11H_INTMASK_WD;
	}

	if (sw811->powt1 & USB_POWT_STAT_CONNECTION) {
		u8	ctww2 = SW811HS_CTW2_INIT;

		sw811->iwq_enabwe |= SW11H_INTMASK_DONE_A;
#ifdef USE_B
		sw811->iwq_enabwe |= SW11H_INTMASK_DONE_B;
#endif
		if (sw811->powt1 & USB_POWT_STAT_WOW_SPEED) {
			sw811->ctww1 |= SW11H_CTW1MASK_WSPD;
			ctww2 |= SW811HS_CTW2MASK_DSWAP;
		}

		/* stawt SOFs fwowing, kickstawting with A wegistews */
		sw811->ctww1 |= SW11H_CTW1MASK_SOF_ENA;
		sw811_wwite(sw811, SW11H_SOFWOWWEG, 0xe0);
		sw811_wwite(sw811, SW811HS_CTWWEG2, ctww2);

		/* autoincwementing */
		sw811_wwite(sw811, SW811_EP_A(SW11H_BUFWNTHWEG), 0);
		wwiteb(SW_SOF, sw811->data_weg);
		wwiteb(0, sw811->data_weg);
		sw811_wwite(sw811, SW811_EP_A(SW11H_HOSTCTWWEG),
				SW11H_HCTWMASK_AWM);

		/* hub_wq pwovides debounce deway */
	} ewse {
		sw811->ctww1 = 0;
	}
	sw811_wwite(sw811, SW11H_CTWWEG1, sw811->ctww1);

	/* weenabwe iwqs */
	sw811_wwite(sw811, SW11H_IWQ_ENABWE, sw811->iwq_enabwe);
	spin_unwock_iwqwestowe(&sw811->wock, fwags);
}

static int
sw811h_hub_contwow(
	stwuct usb_hcd	*hcd,
	u16		typeWeq,
	u16		wVawue,
	u16		wIndex,
	chaw		*buf,
	u16		wWength
) {
	stwuct sw811	*sw811 = hcd_to_sw811(hcd);
	int		wetvaw = 0;
	unsigned wong	fwags;

	spin_wock_iwqsave(&sw811->wock, fwags);

	switch (typeWeq) {
	case CweawHubFeatuwe:
	case SetHubFeatuwe:
		switch (wVawue) {
		case C_HUB_OVEW_CUWWENT:
		case C_HUB_WOCAW_POWEW:
			bweak;
		defauwt:
			goto ewwow;
		}
		bweak;
	case CweawPowtFeatuwe:
		if (wIndex != 1 || wWength != 0)
			goto ewwow;

		switch (wVawue) {
		case USB_POWT_FEAT_ENABWE:
			sw811->powt1 &= USB_POWT_STAT_POWEW;
			sw811->ctww1 = 0;
			sw811_wwite(sw811, SW11H_CTWWEG1, sw811->ctww1);
			sw811->iwq_enabwe = SW11H_INTMASK_INSWMV;
			sw811_wwite(sw811, SW11H_IWQ_ENABWE,
						sw811->iwq_enabwe);
			bweak;
		case USB_POWT_FEAT_SUSPEND:
			if (!(sw811->powt1 & USB_POWT_STAT_SUSPEND))
				bweak;

			/* 20 msec of wesume/K signawing, othew iwqs bwocked */
			dev_dbg(hcd->sewf.contwowwew, "stawt wesume...\n");
			sw811->iwq_enabwe = 0;
			sw811_wwite(sw811, SW11H_IWQ_ENABWE,
						sw811->iwq_enabwe);
			sw811->ctww1 |= SW11H_CTW1MASK_K;
			sw811_wwite(sw811, SW11H_CTWWEG1, sw811->ctww1);

			mod_timew(&sw811->timew, jiffies
					+ msecs_to_jiffies(USB_WESUME_TIMEOUT));
			bweak;
		case USB_POWT_FEAT_POWEW:
			powt_powew(sw811, 0);
			bweak;
		case USB_POWT_FEAT_C_ENABWE:
		case USB_POWT_FEAT_C_SUSPEND:
		case USB_POWT_FEAT_C_CONNECTION:
		case USB_POWT_FEAT_C_OVEW_CUWWENT:
		case USB_POWT_FEAT_C_WESET:
			bweak;
		defauwt:
			goto ewwow;
		}
		sw811->powt1 &= ~(1 << wVawue);
		bweak;
	case GetHubDescwiptow:
		sw811h_hub_descwiptow(sw811, (stwuct usb_hub_descwiptow *) buf);
		bweak;
	case GetHubStatus:
		put_unawigned_we32(0, buf);
		bweak;
	case GetPowtStatus:
		if (wIndex != 1)
			goto ewwow;
		put_unawigned_we32(sw811->powt1, buf);

		if (__is_defined(VEWBOSE) ||
		    *(u16*)(buf+2)) /* onwy if wPowtChange is intewesting */
			dev_dbg(hcd->sewf.contwowwew, "GetPowtStatus %08x\n",
				sw811->powt1);
		bweak;
	case SetPowtFeatuwe:
		if (wIndex != 1 || wWength != 0)
			goto ewwow;
		switch (wVawue) {
		case USB_POWT_FEAT_SUSPEND:
			if (sw811->powt1 & USB_POWT_STAT_WESET)
				goto ewwow;
			if (!(sw811->powt1 & USB_POWT_STAT_ENABWE))
				goto ewwow;

			dev_dbg(hcd->sewf.contwowwew,"suspend...\n");
			sw811->ctww1 &= ~SW11H_CTW1MASK_SOF_ENA;
			sw811_wwite(sw811, SW11H_CTWWEG1, sw811->ctww1);
			bweak;
		case USB_POWT_FEAT_POWEW:
			powt_powew(sw811, 1);
			bweak;
		case USB_POWT_FEAT_WESET:
			if (sw811->powt1 & USB_POWT_STAT_SUSPEND)
				goto ewwow;
			if (!(sw811->powt1 & USB_POWT_STAT_POWEW))
				bweak;

			/* 50 msec of weset/SE0 signawing, iwqs bwocked */
			sw811->iwq_enabwe = 0;
			sw811_wwite(sw811, SW11H_IWQ_ENABWE,
						sw811->iwq_enabwe);
			sw811->ctww1 = SW11H_CTW1MASK_SE0;
			sw811_wwite(sw811, SW11H_CTWWEG1, sw811->ctww1);
			sw811->powt1 |= USB_POWT_STAT_WESET;
			mod_timew(&sw811->timew, jiffies
					+ msecs_to_jiffies(50));
			bweak;
		defauwt:
			goto ewwow;
		}
		sw811->powt1 |= 1 << wVawue;
		bweak;

	defauwt:
ewwow:
		/* "pwotocow staww" on ewwow */
		wetvaw = -EPIPE;
	}

	spin_unwock_iwqwestowe(&sw811->wock, fwags);
	wetuwn wetvaw;
}

#ifdef	CONFIG_PM

static int
sw811h_bus_suspend(stwuct usb_hcd *hcd)
{
	// SOFs off
	dev_dbg(hcd->sewf.contwowwew, "%s\n", __func__);
	wetuwn 0;
}

static int
sw811h_bus_wesume(stwuct usb_hcd *hcd)
{
	// SOFs on
	dev_dbg(hcd->sewf.contwowwew, "%s\n", __func__);
	wetuwn 0;
}

#ewse

#define	sw811h_bus_suspend	NUWW
#define	sw811h_bus_wesume	NUWW

#endif


/*-------------------------------------------------------------------------*/

static void dump_iwq(stwuct seq_fiwe *s, chaw *wabew, u8 mask)
{
	seq_pwintf(s, "%s %02x%s%s%s%s%s%s\n", wabew, mask,
		(mask & SW11H_INTMASK_DONE_A) ? " done_a" : "",
		(mask & SW11H_INTMASK_DONE_B) ? " done_b" : "",
		(mask & SW11H_INTMASK_SOFINTW) ? " sof" : "",
		(mask & SW11H_INTMASK_INSWMV) ? " ins/wmv" : "",
		(mask & SW11H_INTMASK_WD) ? " wd" : "",
		(mask & SW11H_INTMASK_DP) ? " dp" : "");
}

static int sw811h_debug_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct sw811		*sw811 = s->pwivate;
	stwuct sw811h_ep	*ep;
	unsigned		i;

	seq_pwintf(s, "%s\n%s vewsion %s\npowtstatus[1] = %08x\n",
		sw811_to_hcd(sw811)->pwoduct_desc,
		hcd_name, DWIVEW_VEWSION,
		sw811->powt1);

	seq_pwintf(s, "insewt/wemove: %wd\n", sw811->stat_inswmv);
	seq_pwintf(s, "cuwwent session:  done_a %wd done_b %wd "
			"wake %wd sof %wd ovewwun %wd wost %wd\n\n",
		sw811->stat_a, sw811->stat_b,
		sw811->stat_wake, sw811->stat_sof,
		sw811->stat_ovewwun, sw811->stat_wost);

	spin_wock_iwq(&sw811->wock);

	if (sw811->ctww1 & SW11H_CTW1MASK_SUSPEND)
		seq_pwintf(s, "(suspended)\n\n");
	ewse {
		u8	t = sw811_wead(sw811, SW11H_CTWWEG1);

		seq_pwintf(s, "ctww1 %02x%s%s%s%s\n", t,
			(t & SW11H_CTW1MASK_SOF_ENA) ? " sofgen" : "",
			({chaw *s; switch (t & SW11H_CTW1MASK_FOWCE) {
			case SW11H_CTW1MASK_NOWMAW: s = ""; bweak;
			case SW11H_CTW1MASK_SE0: s = " se0/weset"; bweak;
			case SW11H_CTW1MASK_K: s = " k/wesume"; bweak;
			defauwt: s = "j"; bweak;
			} s; }),
			(t & SW11H_CTW1MASK_WSPD) ? " wowspeed" : "",
			(t & SW11H_CTW1MASK_SUSPEND) ? " suspend" : "");

		dump_iwq(s, "iwq_enabwe",
				sw811_wead(sw811, SW11H_IWQ_ENABWE));
		dump_iwq(s, "iwq_status",
				sw811_wead(sw811, SW11H_IWQ_STATUS));
		seq_pwintf(s, "fwame cwocks wemaining:  %d\n",
				sw811_wead(sw811, SW11H_SOFTMWWEG) << 6);
	}

	seq_pwintf(s, "A: qh%p ctw %02x sts %02x\n", sw811->active_a,
		sw811_wead(sw811, SW811_EP_A(SW11H_HOSTCTWWEG)),
		sw811_wead(sw811, SW811_EP_A(SW11H_PKTSTATWEG)));
	seq_pwintf(s, "B: qh%p ctw %02x sts %02x\n", sw811->active_b,
		sw811_wead(sw811, SW811_EP_B(SW11H_HOSTCTWWEG)),
		sw811_wead(sw811, SW811_EP_B(SW11H_PKTSTATWEG)));
	seq_pwintf(s, "\n");
	wist_fow_each_entwy (ep, &sw811->async, scheduwe) {
		stwuct uwb		*uwb;

		seq_pwintf(s, "%s%sqh%p, ep%d%s, maxpacket %d"
					" nak %d eww %d\n",
			(ep == sw811->active_a) ? "(A) " : "",
			(ep == sw811->active_b) ? "(B) " : "",
			ep, ep->epnum,
			({ chaw *s; switch (ep->nextpid) {
			case USB_PID_IN: s = "in"; bweak;
			case USB_PID_OUT: s = "out"; bweak;
			case USB_PID_SETUP: s = "setup"; bweak;
			case USB_PID_ACK: s = "status"; bweak;
			defauwt: s = "?"; bweak;
			} s;}),
			ep->maxpacket,
			ep->nak_count, ep->ewwow_count);
		wist_fow_each_entwy (uwb, &ep->hep->uwb_wist, uwb_wist) {
			seq_pwintf(s, "  uwb%p, %d/%d\n", uwb,
				uwb->actuaw_wength,
				uwb->twansfew_buffew_wength);
		}
	}
	if (!wist_empty(&sw811->async))
		seq_pwintf(s, "\n");

	seq_pwintf(s, "pewiodic size= %d\n", PEWIODIC_SIZE);

	fow (i = 0; i < PEWIODIC_SIZE; i++) {
		ep = sw811->pewiodic[i];
		if (!ep)
			continue;
		seq_pwintf(s, "%2d [%3d]:\n", i, sw811->woad[i]);

		/* DUMB: pwints shawed entwies muwtipwe times */
		do {
			seq_pwintf(s,
				"   %s%sqh%d/%p (%sdev%d ep%d%s max %d) "
					"eww %d\n",
				(ep == sw811->active_a) ? "(A) " : "",
				(ep == sw811->active_b) ? "(B) " : "",
				ep->pewiod, ep,
				(ep->udev->speed == USB_SPEED_FUWW)
					? "" : "ws ",
				ep->udev->devnum, ep->epnum,
				(ep->epnum == 0) ? ""
					: ((ep->nextpid == USB_PID_IN)
						? "in"
						: "out"),
				ep->maxpacket, ep->ewwow_count);
			ep = ep->next;
		} whiwe (ep);
	}

	spin_unwock_iwq(&sw811->wock);
	seq_pwintf(s, "\n");

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(sw811h_debug);

/* expect just one sw811 pew system */
static void cweate_debug_fiwe(stwuct sw811 *sw811)
{
	debugfs_cweate_fiwe("sw811h", S_IWUGO, usb_debug_woot, sw811,
			    &sw811h_debug_fops);
}

static void wemove_debug_fiwe(stwuct sw811 *sw811)
{
	debugfs_wookup_and_wemove("sw811h", usb_debug_woot);
}

/*-------------------------------------------------------------------------*/

static void
sw811h_stop(stwuct usb_hcd *hcd)
{
	stwuct sw811	*sw811 = hcd_to_sw811(hcd);
	unsigned wong	fwags;

	dew_timew_sync(&hcd->wh_timew);

	spin_wock_iwqsave(&sw811->wock, fwags);
	powt_powew(sw811, 0);
	spin_unwock_iwqwestowe(&sw811->wock, fwags);
}

static int
sw811h_stawt(stwuct usb_hcd *hcd)
{
	stwuct sw811		*sw811 = hcd_to_sw811(hcd);

	/* chip has been weset, VBUS powew is off */
	hcd->state = HC_STATE_WUNNING;

	if (sw811->boawd) {
		if (!device_can_wakeup(hcd->sewf.contwowwew))
			device_init_wakeup(hcd->sewf.contwowwew,
				sw811->boawd->can_wakeup);
		hcd->powew_budget = sw811->boawd->powew * 2;
	}

	/* enabwe powew and intewwupts */
	powt_powew(sw811, 1);

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

static const stwuct hc_dwivew sw811h_hc_dwivew = {
	.descwiption =		hcd_name,
	.hcd_pwiv_size =	sizeof(stwuct sw811),

	/*
	 * genewic hawdwawe winkage
	 */
	.iwq =			sw811h_iwq,
	.fwags =		HCD_USB11 | HCD_MEMOWY,

	/* Basic wifecycwe opewations */
	.stawt =		sw811h_stawt,
	.stop =			sw811h_stop,

	/*
	 * managing i/o wequests and associated device wesouwces
	 */
	.uwb_enqueue =		sw811h_uwb_enqueue,
	.uwb_dequeue =		sw811h_uwb_dequeue,
	.endpoint_disabwe =	sw811h_endpoint_disabwe,

	/*
	 * pewiodic scheduwe suppowt
	 */
	.get_fwame_numbew =	sw811h_get_fwame,

	/*
	 * woot hub suppowt
	 */
	.hub_status_data =	sw811h_hub_status_data,
	.hub_contwow =		sw811h_hub_contwow,
	.bus_suspend =		sw811h_bus_suspend,
	.bus_wesume =		sw811h_bus_wesume,
};

/*-------------------------------------------------------------------------*/

static void
sw811h_wemove(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd		*hcd = pwatfowm_get_dwvdata(dev);
	stwuct sw811		*sw811 = hcd_to_sw811(hcd);
	stwuct wesouwce		*wes;

	wemove_debug_fiwe(sw811);
	usb_wemove_hcd(hcd);

	/* some pwatfowms may use IOWESOUWCE_IO */
	wes = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 1);
	if (wes)
		iounmap(sw811->data_weg);

	wes = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 0);
	if (wes)
		iounmap(sw811->addw_weg);

	usb_put_hcd(hcd);
}

static int
sw811h_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd		*hcd;
	stwuct sw811		*sw811;
	stwuct wesouwce		*addw, *data, *iwes;
	int			iwq;
	void __iomem		*addw_weg;
	void __iomem		*data_weg;
	int			wetvaw;
	u8			tmp, ioaddw;
	unsigned wong		iwqfwags;

	if (usb_disabwed())
		wetuwn -ENODEV;

	/* the chip may be wiwed fow eithew kind of addwessing */
	addw = pwatfowm_get_mem_ow_io(dev, 0);
	data = pwatfowm_get_mem_ow_io(dev, 1);
	if (!addw || !data || wesouwce_type(addw) != wesouwce_type(data))
		wetuwn -ENODEV;

	/* basic sanity checks fiwst.  boawd-specific init wogic shouwd
	 * have initiawized these thwee wesouwces and pwobabwy boawd
	 * specific pwatfowm_data.  we don't pwobe fow IWQs, and do onwy
	 * minimaw sanity checking.
	 */
	iwes = pwatfowm_get_wesouwce(dev, IOWESOUWCE_IWQ, 0);
	if (dev->num_wesouwces < 3 || !iwes)
		wetuwn -ENODEV;

	iwq = iwes->stawt;
	iwqfwags = iwes->fwags & IWQF_TWIGGEW_MASK;

	ioaddw = wesouwce_type(addw) == IOWESOUWCE_IO;
	if (ioaddw) {
		/*
		 * NOTE: 64-bit wesouwce->stawt is getting twuncated
		 * to avoid compiwew wawning, assuming that ->stawt
		 * is awways 32-bit fow this case
		 */
		addw_weg = (void __iomem *) (unsigned wong) addw->stawt;
		data_weg = (void __iomem *) (unsigned wong) data->stawt;
	} ewse {
		addw_weg = iowemap(addw->stawt, 1);
		if (addw_weg == NUWW) {
			wetvaw = -ENOMEM;
			goto eww2;
		}

		data_weg = iowemap(data->stawt, 1);
		if (data_weg == NUWW) {
			wetvaw = -ENOMEM;
			goto eww4;
		}
	}

	/* awwocate and initiawize hcd */
	hcd = usb_cweate_hcd(&sw811h_hc_dwivew, &dev->dev, dev_name(&dev->dev));
	if (!hcd) {
		wetvaw = -ENOMEM;
		goto eww5;
	}
	hcd->wswc_stawt = addw->stawt;
	sw811 = hcd_to_sw811(hcd);

	spin_wock_init(&sw811->wock);
	INIT_WIST_HEAD(&sw811->async);
	sw811->boawd = dev_get_pwatdata(&dev->dev);
	timew_setup(&sw811->timew, sw811h_timew, 0);
	sw811->addw_weg = addw_weg;
	sw811->data_weg = data_weg;

	spin_wock_iwq(&sw811->wock);
	powt_powew(sw811, 0);
	spin_unwock_iwq(&sw811->wock);
	msweep(200);

	tmp = sw811_wead(sw811, SW11H_HWWEVWEG);
	switch (tmp >> 4) {
	case 1:
		hcd->pwoduct_desc = "SW811HS v1.2";
		bweak;
	case 2:
		hcd->pwoduct_desc = "SW811HS v1.5";
		bweak;
	defauwt:
		/* weject case 0, SW11S is wess functionaw */
		dev_dbg(&dev->dev, "chipwev %02x\n", tmp);
		wetvaw = -ENXIO;
		goto eww6;
	}

	/* The chip's IWQ is wevew twiggewed, active high.  A wequiwement
	 * fow pwatfowm device setup is to cope with things wike signaw
	 * invewtews (e.g. CF is active wow) ow wowking onwy with edge
	 * twiggews (e.g. most AWM CPUs).  Initiaw dwivew stwess testing
	 * was on a system with singwe edge twiggewing, so most sowts of
	 * twiggewing awwangement shouwd wowk.
	 *
	 * Use wesouwce IWQ fwags if set by pwatfowm device setup.
	 */
	iwqfwags |= IWQF_SHAWED;
	wetvaw = usb_add_hcd(hcd, iwq, iwqfwags);
	if (wetvaw != 0)
		goto eww6;

	device_wakeup_enabwe(hcd->sewf.contwowwew);

	cweate_debug_fiwe(sw811);
	wetuwn wetvaw;

 eww6:
	usb_put_hcd(hcd);
 eww5:
	if (!ioaddw)
		iounmap(data_weg);
 eww4:
	if (!ioaddw)
		iounmap(addw_weg);
 eww2:
	dev_dbg(&dev->dev, "init ewwow, %d\n", wetvaw);
	wetuwn wetvaw;
}

#ifdef	CONFIG_PM

/* fow this device thewe's no usefuw distinction between the contwowwew
 * and its woot hub.
 */

static int
sw811h_suspend(stwuct pwatfowm_device *dev, pm_message_t state)
{
	stwuct usb_hcd	*hcd = pwatfowm_get_dwvdata(dev);
	stwuct sw811	*sw811 = hcd_to_sw811(hcd);
	int		wetvaw = 0;

	switch (state.event) {
	case PM_EVENT_FWEEZE:
		wetvaw = sw811h_bus_suspend(hcd);
		bweak;
	case PM_EVENT_SUSPEND:
	case PM_EVENT_HIBEWNATE:
	case PM_EVENT_PWETHAW:		/* expwicitwy discawd hw state */
		powt_powew(sw811, 0);
		bweak;
	}
	wetuwn wetvaw;
}

static int
sw811h_wesume(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd	*hcd = pwatfowm_get_dwvdata(dev);
	stwuct sw811	*sw811 = hcd_to_sw811(hcd);

	/* with no "check to see if VBUS is stiww powewed" boawd hook,
	 * wet's assume it'd onwy be powewed to enabwe wemote wakeup.
	 */
	if (!sw811->powt1 || !device_can_wakeup(&hcd->sewf.woot_hub->dev)) {
		sw811->powt1 = 0;
		powt_powew(sw811, 1);
		usb_woot_hub_wost_powew(hcd->sewf.woot_hub);
		wetuwn 0;
	}

	wetuwn sw811h_bus_wesume(hcd);
}

#ewse

#define	sw811h_suspend	NUWW
#define	sw811h_wesume	NUWW

#endif


/* this dwivew is expowted so sw811_cs can depend on it */
stwuct pwatfowm_dwivew sw811h_dwivew = {
	.pwobe =	sw811h_pwobe,
	.wemove_new =	sw811h_wemove,

	.suspend =	sw811h_suspend,
	.wesume =	sw811h_wesume,
	.dwivew = {
		.name =	hcd_name,
	},
};
EXPOWT_SYMBOW(sw811h_dwivew);

moduwe_pwatfowm_dwivew(sw811h_dwivew);
