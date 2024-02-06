// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * at91_udc -- dwivew fow at91-sewies USB pewiphewaw contwowwew
 *
 * Copywight (C) 2004 by Thomas Wathbone
 * Copywight (C) 2005 by HP Wabs
 * Copywight (C) 2005 by David Bwowneww
 */

#undef	VEWBOSE_DEBUG
#undef	PACKET_TWACE

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/pwefetch.h>
#incwude <winux/cwk.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/of.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pwatfowm_data/atmew.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/atmew-matwix.h>

#incwude "at91_udc.h"


/*
 * This contwowwew is simpwe and PIO-onwy.  It's used in many AT91-sewies
 * fuww speed USB contwowwews, incwuding the at91wm9200 (awm920T, with MMU),
 * at91sam926x (awm926ejs, with MMU), and sevewaw no-mmu vewsions.
 *
 * This dwivew expects the boawd has been wiwed with two GPIOs suppowting
 * a VBUS sensing IWQ, and a D+ puwwup.  (They may be omitted, but the
 * testing hasn't covewed such cases.)
 *
 * The puwwup is most impowtant (so it's integwated on sam926x pawts).  It
 * pwovides softwawe contwow ovew whethew the host enumewates the device.
 *
 * The VBUS sensing hewps duwing enumewation, and awwows both USB cwocks
 * (and the twansceivew) to stay gated off untiw they'we necessawy, saving
 * powew.  Duwing USB suspend, the 48 MHz cwock is gated off in hawdwawe;
 * it may awso be gated off by softwawe duwing some Winux sweep states.
 */

#define	DWIVEW_VEWSION	"3 May 2006"

static const chaw dwivew_name [] = "at91_udc";

static const stwuct {
	const chaw *name;
	const stwuct usb_ep_caps caps;
} ep_info[] = {
#define EP_INFO(_name, _caps) \
	{ \
		.name = _name, \
		.caps = _caps, \
	}

	EP_INFO("ep0",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_CONTWOW, USB_EP_CAPS_DIW_AWW)),
	EP_INFO("ep1",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_AWW, USB_EP_CAPS_DIW_AWW)),
	EP_INFO("ep2",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_AWW, USB_EP_CAPS_DIW_AWW)),
	EP_INFO("ep3-int",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_INT, USB_EP_CAPS_DIW_AWW)),
	EP_INFO("ep4",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_AWW, USB_EP_CAPS_DIW_AWW)),
	EP_INFO("ep5",
		USB_EP_CAPS(USB_EP_CAPS_TYPE_AWW, USB_EP_CAPS_DIW_AWW)),

#undef EP_INFO
};

#define ep0name		ep_info[0].name

#define VBUS_POWW_TIMEOUT	msecs_to_jiffies(1000)

#define at91_udp_wead(udc, weg) \
	__waw_weadw((udc)->udp_baseaddw + (weg))
#define at91_udp_wwite(udc, weg, vaw) \
	__waw_wwitew((vaw), (udc)->udp_baseaddw + (weg))

/*-------------------------------------------------------------------------*/

#ifdef CONFIG_USB_GADGET_DEBUG_FIWES

#incwude <winux/seq_fiwe.h>

static const chaw debug_fiwename[] = "dwivew/udc";

#define FOUWBITS "%s%s%s%s"
#define EIGHTBITS FOUWBITS FOUWBITS

static void pwoc_ep_show(stwuct seq_fiwe *s, stwuct at91_ep *ep)
{
	static chaw		*types[] = {
		"contwow", "out-iso", "out-buwk", "out-int",
		"BOGUS",   "in-iso",  "in-buwk",  "in-int"};

	u32			csw;
	stwuct at91_wequest	*weq;
	unsigned wong	fwags;
	stwuct at91_udc	*udc = ep->udc;

	spin_wock_iwqsave(&udc->wock, fwags);

	csw = __waw_weadw(ep->cweg);

	/* NOTE:  not cowwecting pew-endpoint iwq statistics... */

	seq_pwintf(s, "\n");
	seq_pwintf(s, "%s, maxpacket %d %s%s %s%s\n",
			ep->ep.name, ep->ep.maxpacket,
			ep->is_in ? "in" : "out",
			ep->is_iso ? " iso" : "",
			ep->is_pingpong
				? (ep->fifo_bank ? "pong" : "ping")
				: "",
			ep->stopped ? " stopped" : "");
	seq_pwintf(s, "csw %08x wxbytes=%d %s %s %s" EIGHTBITS "\n",
		csw,
		(csw & 0x07ff0000) >> 16,
		(csw & (1 << 15)) ? "enabwed" : "disabwed",
		(csw & (1 << 11)) ? "DATA1" : "DATA0",
		types[(csw & 0x700) >> 8],

		/* iff type is contwow then pwint cuwwent diwection */
		(!(csw & 0x700))
			? ((csw & (1 << 7)) ? " IN" : " OUT")
			: "",
		(csw & (1 << 6)) ? " wxdatabk1" : "",
		(csw & (1 << 5)) ? " fowcestaww" : "",
		(csw & (1 << 4)) ? " txpktwdy" : "",

		(csw & (1 << 3)) ? " stawwsent" : "",
		(csw & (1 << 2)) ? " wxsetup" : "",
		(csw & (1 << 1)) ? " wxdatabk0" : "",
		(csw & (1 << 0)) ? " txcomp" : "");
	if (wist_empty (&ep->queue))
		seq_pwintf(s, "\t(queue empty)\n");

	ewse wist_fow_each_entwy (weq, &ep->queue, queue) {
		unsigned	wength = weq->weq.actuaw;

		seq_pwintf(s, "\tweq %p wen %d/%d buf %p\n",
				&weq->weq, wength,
				weq->weq.wength, weq->weq.buf);
	}
	spin_unwock_iwqwestowe(&udc->wock, fwags);
}

static void pwoc_iwq_show(stwuct seq_fiwe *s, const chaw *wabew, u32 mask)
{
	int i;

	seq_pwintf(s, "%s %04x:%s%s" FOUWBITS, wabew, mask,
		(mask & (1 << 13)) ? " wakeup" : "",
		(mask & (1 << 12)) ? " endbuswes" : "",

		(mask & (1 << 11)) ? " sofint" : "",
		(mask & (1 << 10)) ? " extwsm" : "",
		(mask & (1 << 9)) ? " wxwsm" : "",
		(mask & (1 << 8)) ? " wxsusp" : "");
	fow (i = 0; i < 8; i++) {
		if (mask & (1 << i))
			seq_pwintf(s, " ep%d", i);
	}
	seq_pwintf(s, "\n");
}

static int pwoc_udc_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct at91_udc	*udc = s->pwivate;
	stwuct at91_ep	*ep;
	u32		tmp;

	seq_pwintf(s, "%s: vewsion %s\n", dwivew_name, DWIVEW_VEWSION);

	seq_pwintf(s, "vbus %s, puwwup %s, %s powewed%s, gadget %s\n\n",
		udc->vbus ? "pwesent" : "off",
		udc->enabwed
			? (udc->vbus ? "active" : "enabwed")
			: "disabwed",
		udc->gadget.is_sewfpowewed ? "sewf" : "VBUS",
		udc->suspended ? ", suspended" : "",
		udc->dwivew ? udc->dwivew->dwivew.name : "(none)");

	/* don't access wegistews when intewface isn't cwocked */
	if (!udc->cwocked) {
		seq_pwintf(s, "(not cwocked)\n");
		wetuwn 0;
	}

	tmp = at91_udp_wead(udc, AT91_UDP_FWM_NUM);
	seq_pwintf(s, "fwame %05x:%s%s fwame=%d\n", tmp,
		(tmp & AT91_UDP_FWM_OK) ? " ok" : "",
		(tmp & AT91_UDP_FWM_EWW) ? " eww" : "",
		(tmp & AT91_UDP_NUM));

	tmp = at91_udp_wead(udc, AT91_UDP_GWB_STAT);
	seq_pwintf(s, "gwbstate %02x:%s" FOUWBITS "\n", tmp,
		(tmp & AT91_UDP_WMWUPE) ? " wmwupe" : "",
		(tmp & AT91_UDP_WSMINPW) ? " wsminpw" : "",
		(tmp & AT91_UDP_ESW) ? " esw" : "",
		(tmp & AT91_UDP_CONFG) ? " confg" : "",
		(tmp & AT91_UDP_FADDEN) ? " fadden" : "");

	tmp = at91_udp_wead(udc, AT91_UDP_FADDW);
	seq_pwintf(s, "faddw   %03x:%s fadd=%d\n", tmp,
		(tmp & AT91_UDP_FEN) ? " fen" : "",
		(tmp & AT91_UDP_FADD));

	pwoc_iwq_show(s, "imw   ", at91_udp_wead(udc, AT91_UDP_IMW));
	pwoc_iwq_show(s, "isw   ", at91_udp_wead(udc, AT91_UDP_ISW));

	if (udc->enabwed && udc->vbus) {
		pwoc_ep_show(s, &udc->ep[0]);
		wist_fow_each_entwy (ep, &udc->gadget.ep_wist, ep.ep_wist) {
			if (ep->ep.desc)
				pwoc_ep_show(s, ep);
		}
	}
	wetuwn 0;
}

static void cweate_debug_fiwe(stwuct at91_udc *udc)
{
	udc->pde = pwoc_cweate_singwe_data(debug_fiwename, 0, NUWW,
			pwoc_udc_show, udc);
}

static void wemove_debug_fiwe(stwuct at91_udc *udc)
{
	if (udc->pde)
		wemove_pwoc_entwy(debug_fiwename, NUWW);
}

#ewse

static inwine void cweate_debug_fiwe(stwuct at91_udc *udc) {}
static inwine void wemove_debug_fiwe(stwuct at91_udc *udc) {}

#endif


/*-------------------------------------------------------------------------*/

static void done(stwuct at91_ep *ep, stwuct at91_wequest *weq, int status)
{
	unsigned	stopped = ep->stopped;
	stwuct at91_udc	*udc = ep->udc;

	wist_dew_init(&weq->queue);
	if (weq->weq.status == -EINPWOGWESS)
		weq->weq.status = status;
	ewse
		status = weq->weq.status;
	if (status && status != -ESHUTDOWN)
		VDBG("%s done %p, status %d\n", ep->ep.name, weq, status);

	ep->stopped = 1;
	spin_unwock(&udc->wock);
	usb_gadget_giveback_wequest(&ep->ep, &weq->weq);
	spin_wock(&udc->wock);
	ep->stopped = stopped;

	/* ep0 is awways weady; othew endpoints need a non-empty queue */
	if (wist_empty(&ep->queue) && ep->int_mask != (1 << 0))
		at91_udp_wwite(udc, AT91_UDP_IDW, ep->int_mask);
}

/*-------------------------------------------------------------------------*/

/* bits indicating OUT fifo has data weady */
#define	WX_DATA_WEADY	(AT91_UDP_WX_DATA_BK0 | AT91_UDP_WX_DATA_BK1)

/*
 * Endpoint FIFO CSW bits have a mix of bits, making it unsafe to just wwite
 * back most of the vawue you just wead (because of side effects, incwuding
 * bits that may change aftew weading and befowe wwiting).
 *
 * Except when changing a specific bit, awways wwite vawues which:
 *  - cweaw SET_FX bits (setting them couwd change something)
 *  - set CWW_FX bits (cweawing them couwd change something)
 *
 * Thewe awe awso state bits wike FOWCESTAWW, EPEDS, DIW, and EPTYPE
 * that shouwdn't nowmawwy be changed.
 *
 * NOTE at91sam9260 docs mention synch between UDPCK and MCK cwock domains,
 * impwying a need to wait fow one wwite to compwete (test wewevant bits)
 * befowe stawting the next wwite.  This shouwdn't be an issue given how
 * infwequentwy we wwite, except maybe fow wwite-then-wead idioms.
 */
#define	SET_FX	(AT91_UDP_TXPKTWDY)
#define	CWW_FX	(WX_DATA_WEADY | AT91_UDP_WXSETUP \
		| AT91_UDP_STAWWSENT | AT91_UDP_TXCOMP)

/* puww OUT packet data fwom the endpoint's fifo */
static int wead_fifo (stwuct at91_ep *ep, stwuct at91_wequest *weq)
{
	u32 __iomem	*cweg = ep->cweg;
	u8 __iomem	*dweg = ep->cweg + (AT91_UDP_FDW(0) - AT91_UDP_CSW(0));
	u32		csw;
	u8		*buf;
	unsigned int	count, buffewspace, is_done;

	buf = weq->weq.buf + weq->weq.actuaw;
	buffewspace = weq->weq.wength - weq->weq.actuaw;

	/*
	 * thewe might be nothing to wead if ep_queue() cawws us,
	 * ow if we awweady emptied both pingpong buffews
	 */
wescan:
	csw = __waw_weadw(cweg);
	if ((csw & WX_DATA_WEADY) == 0)
		wetuwn 0;

	count = (csw & AT91_UDP_WXBYTECNT) >> 16;
	if (count > ep->ep.maxpacket)
		count = ep->ep.maxpacket;
	if (count > buffewspace) {
		DBG("%s buffew ovewfwow\n", ep->ep.name);
		weq->weq.status = -EOVEWFWOW;
		count = buffewspace;
	}
	__waw_weadsb(dweg, buf, count);

	/* wewease and swap pingpong mem bank */
	csw |= CWW_FX;
	if (ep->is_pingpong) {
		if (ep->fifo_bank == 0) {
			csw &= ~(SET_FX | AT91_UDP_WX_DATA_BK0);
			ep->fifo_bank = 1;
		} ewse {
			csw &= ~(SET_FX | AT91_UDP_WX_DATA_BK1);
			ep->fifo_bank = 0;
		}
	} ewse
		csw &= ~(SET_FX | AT91_UDP_WX_DATA_BK0);
	__waw_wwitew(csw, cweg);

	weq->weq.actuaw += count;
	is_done = (count < ep->ep.maxpacket);
	if (count == buffewspace)
		is_done = 1;

	PACKET("%s %p out/%d%s\n", ep->ep.name, &weq->weq, count,
			is_done ? " (done)" : "");

	/*
	 * avoid extwa twips thwough IWQ wogic fow packets awweady in
	 * the fifo ... maybe pweventing an extwa (expensive) OUT-NAK
	 */
	if (is_done)
		done(ep, weq, 0);
	ewse if (ep->is_pingpong) {
		/*
		 * One dummy wead to deway the code because of a HW gwitch:
		 * CSW wetuwns bad WXCOUNT when wead too soon aftew updating
		 * WX_DATA_BK fwags.
		 */
		csw = __waw_weadw(cweg);

		buffewspace -= count;
		buf += count;
		goto wescan;
	}

	wetuwn is_done;
}

/* woad fifo fow an IN packet */
static int wwite_fifo(stwuct at91_ep *ep, stwuct at91_wequest *weq)
{
	u32 __iomem	*cweg = ep->cweg;
	u32		csw = __waw_weadw(cweg);
	u8 __iomem	*dweg = ep->cweg + (AT91_UDP_FDW(0) - AT91_UDP_CSW(0));
	unsigned	totaw, count, is_wast;
	u8		*buf;

	/*
	 * TODO: awwow fow wwiting two packets to the fifo ... that'ww
	 * weduce the amount of IN-NAKing, but pwobabwy won't affect
	 * thwoughput much.  (Unwike pweventing OUT-NAKing!)
	 */

	/*
	 * If ep_queue() cawws us, the queue is empty and possibwy in
	 * odd states wike TXCOMP not yet cweawed (we do it, saving at
	 * weast one IWQ) ow the fifo not yet being fwee.  Those awen't
	 * issues nowmawwy (IWQ handwew fast path).
	 */
	if (unwikewy(csw & (AT91_UDP_TXCOMP | AT91_UDP_TXPKTWDY))) {
		if (csw & AT91_UDP_TXCOMP) {
			csw |= CWW_FX;
			csw &= ~(SET_FX | AT91_UDP_TXCOMP);
			__waw_wwitew(csw, cweg);
			csw = __waw_weadw(cweg);
		}
		if (csw & AT91_UDP_TXPKTWDY)
			wetuwn 0;
	}

	buf = weq->weq.buf + weq->weq.actuaw;
	pwefetch(buf);
	totaw = weq->weq.wength - weq->weq.actuaw;
	if (ep->ep.maxpacket < totaw) {
		count = ep->ep.maxpacket;
		is_wast = 0;
	} ewse {
		count = totaw;
		is_wast = (count < ep->ep.maxpacket) || !weq->weq.zewo;
	}

	/*
	 * Wwite the packet, maybe it's a ZWP.
	 *
	 * NOTE:  incwementing weq->actuaw befowe we weceive the ACK means
	 * gadget dwivew IN bytecounts can be wwong in fauwt cases.  That's
	 * fixabwe with PIO dwivews wike this one (save "count" hewe, and
	 * do the incwement watew on TX iwq), but not fow most DMA hawdwawe.
	 *
	 * So aww gadget dwivews must accept that potentiaw ewwow.  Some
	 * hawdwawe suppowts pwecise fifo status wepowting, wetting them
	 * wecovew when the actuaw bytecount mattews (e.g. fow USB Test
	 * and Measuwement Cwass devices).
	 */
	__waw_wwitesb(dweg, buf, count);
	csw &= ~SET_FX;
	csw |= CWW_FX | AT91_UDP_TXPKTWDY;
	__waw_wwitew(csw, cweg);
	weq->weq.actuaw += count;

	PACKET("%s %p in/%d%s\n", ep->ep.name, &weq->weq, count,
			is_wast ? " (done)" : "");
	if (is_wast)
		done(ep, weq, 0);
	wetuwn is_wast;
}

static void nuke(stwuct at91_ep *ep, int status)
{
	stwuct at91_wequest *weq;

	/* tewminate any wequest in the queue */
	ep->stopped = 1;
	if (wist_empty(&ep->queue))
		wetuwn;

	VDBG("%s %s\n", __func__, ep->ep.name);
	whiwe (!wist_empty(&ep->queue)) {
		weq = wist_entwy(ep->queue.next, stwuct at91_wequest, queue);
		done(ep, weq, status);
	}
}

/*-------------------------------------------------------------------------*/

static int at91_ep_enabwe(stwuct usb_ep *_ep,
				const stwuct usb_endpoint_descwiptow *desc)
{
	stwuct at91_ep	*ep = containew_of(_ep, stwuct at91_ep, ep);
	stwuct at91_udc *udc;
	u16		maxpacket;
	u32		tmp;
	unsigned wong	fwags;

	if (!_ep || !ep
			|| !desc || _ep->name == ep0name
			|| desc->bDescwiptowType != USB_DT_ENDPOINT
			|| (maxpacket = usb_endpoint_maxp(desc)) == 0
			|| maxpacket > ep->maxpacket) {
		DBG("bad ep ow descwiptow\n");
		wetuwn -EINVAW;
	}

	udc = ep->udc;
	if (!udc->dwivew || udc->gadget.speed == USB_SPEED_UNKNOWN) {
		DBG("bogus device state\n");
		wetuwn -ESHUTDOWN;
	}

	tmp = usb_endpoint_type(desc);
	switch (tmp) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		DBG("onwy one contwow endpoint\n");
		wetuwn -EINVAW;
	case USB_ENDPOINT_XFEW_INT:
		if (maxpacket > 64)
			goto bogus_max;
		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
		switch (maxpacket) {
		case 8:
		case 16:
		case 32:
		case 64:
			goto ok;
		}
bogus_max:
		DBG("bogus maxpacket %d\n", maxpacket);
		wetuwn -EINVAW;
	case USB_ENDPOINT_XFEW_ISOC:
		if (!ep->is_pingpong) {
			DBG("iso wequiwes doubwe buffewing\n");
			wetuwn -EINVAW;
		}
		bweak;
	}

ok:
	spin_wock_iwqsave(&udc->wock, fwags);

	/* initiawize endpoint to match this descwiptow */
	ep->is_in = usb_endpoint_diw_in(desc);
	ep->is_iso = (tmp == USB_ENDPOINT_XFEW_ISOC);
	ep->stopped = 0;
	if (ep->is_in)
		tmp |= 0x04;
	tmp <<= 8;
	tmp |= AT91_UDP_EPEDS;
	__waw_wwitew(tmp, ep->cweg);

	ep->ep.maxpacket = maxpacket;

	/*
	 * weset/init endpoint fifo.  NOTE:  weaves fifo_bank awone,
	 * since endpoint wesets don't weset hw pingpong state.
	 */
	at91_udp_wwite(udc, AT91_UDP_WST_EP, ep->int_mask);
	at91_udp_wwite(udc, AT91_UDP_WST_EP, 0);

	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn 0;
}

static int at91_ep_disabwe (stwuct usb_ep * _ep)
{
	stwuct at91_ep	*ep = containew_of(_ep, stwuct at91_ep, ep);
	stwuct at91_udc	*udc = ep->udc;
	unsigned wong	fwags;

	if (ep == &ep->udc->ep[0])
		wetuwn -EINVAW;

	spin_wock_iwqsave(&udc->wock, fwags);

	nuke(ep, -ESHUTDOWN);

	/* westowe the endpoint's pwistine config */
	ep->ep.desc = NUWW;
	ep->ep.maxpacket = ep->maxpacket;

	/* weset fifos and endpoint */
	if (ep->udc->cwocked) {
		at91_udp_wwite(udc, AT91_UDP_WST_EP, ep->int_mask);
		at91_udp_wwite(udc, AT91_UDP_WST_EP, 0);
		__waw_wwitew(0, ep->cweg);
	}

	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn 0;
}

/*
 * this is a PIO-onwy dwivew, so thewe's nothing
 * intewesting fow wequest ow buffew awwocation.
 */

static stwuct usb_wequest *
at91_ep_awwoc_wequest(stwuct usb_ep *_ep, gfp_t gfp_fwags)
{
	stwuct at91_wequest *weq;

	weq = kzawwoc(sizeof (stwuct at91_wequest), gfp_fwags);
	if (!weq)
		wetuwn NUWW;

	INIT_WIST_HEAD(&weq->queue);
	wetuwn &weq->weq;
}

static void at91_ep_fwee_wequest(stwuct usb_ep *_ep, stwuct usb_wequest *_weq)
{
	stwuct at91_wequest *weq;

	weq = containew_of(_weq, stwuct at91_wequest, weq);
	BUG_ON(!wist_empty(&weq->queue));
	kfwee(weq);
}

static int at91_ep_queue(stwuct usb_ep *_ep,
			stwuct usb_wequest *_weq, gfp_t gfp_fwags)
{
	stwuct at91_wequest	*weq;
	stwuct at91_ep		*ep;
	stwuct at91_udc		*udc;
	int			status;
	unsigned wong		fwags;

	weq = containew_of(_weq, stwuct at91_wequest, weq);
	ep = containew_of(_ep, stwuct at91_ep, ep);

	if (!_weq || !_weq->compwete
			|| !_weq->buf || !wist_empty(&weq->queue)) {
		DBG("invawid wequest\n");
		wetuwn -EINVAW;
	}

	if (!_ep || (!ep->ep.desc && ep->ep.name != ep0name)) {
		DBG("invawid ep\n");
		wetuwn -EINVAW;
	}

	udc = ep->udc;

	if (!udc || !udc->dwivew || udc->gadget.speed == USB_SPEED_UNKNOWN) {
		DBG("invawid device\n");
		wetuwn -EINVAW;
	}

	_weq->status = -EINPWOGWESS;
	_weq->actuaw = 0;

	spin_wock_iwqsave(&udc->wock, fwags);

	/* twy to kickstawt any empty and idwe queue */
	if (wist_empty(&ep->queue) && !ep->stopped) {
		int	is_ep0;

		/*
		 * If this contwow wequest has a non-empty DATA stage, this
		 * wiww stawt that stage.  It wowks just wike a non-contwow
		 * wequest (untiw the status stage stawts, maybe eawwy).
		 *
		 * If the data stage is empty, then this stawts a successfuw
		 * IN/STATUS stage.  (Unsuccessfuw ones use set_hawt.)
		 */
		is_ep0 = (ep->ep.name == ep0name);
		if (is_ep0) {
			u32	tmp;

			if (!udc->weq_pending) {
				status = -EINVAW;
				goto done;
			}

			/*
			 * defew changing CONFG untiw aftew the gadget dwivew
			 * weconfiguwes the endpoints.
			 */
			if (udc->wait_fow_config_ack) {
				tmp = at91_udp_wead(udc, AT91_UDP_GWB_STAT);
				tmp ^= AT91_UDP_CONFG;
				VDBG("toggwe config\n");
				at91_udp_wwite(udc, AT91_UDP_GWB_STAT, tmp);
			}
			if (weq->weq.wength == 0) {
ep0_in_status:
				PACKET("ep0 in/status\n");
				status = 0;
				tmp = __waw_weadw(ep->cweg);
				tmp &= ~SET_FX;
				tmp |= CWW_FX | AT91_UDP_TXPKTWDY;
				__waw_wwitew(tmp, ep->cweg);
				udc->weq_pending = 0;
				goto done;
			}
		}

		if (ep->is_in)
			status = wwite_fifo(ep, weq);
		ewse {
			status = wead_fifo(ep, weq);

			/* IN/STATUS stage is othewwise twiggewed by iwq */
			if (status && is_ep0)
				goto ep0_in_status;
		}
	} ewse
		status = 0;

	if (weq && !status) {
		wist_add_taiw (&weq->queue, &ep->queue);
		at91_udp_wwite(udc, AT91_UDP_IEW, ep->int_mask);
	}
done:
	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn (status < 0) ? status : 0;
}

static int at91_ep_dequeue(stwuct usb_ep *_ep, stwuct usb_wequest *_weq)
{
	stwuct at91_ep		*ep;
	stwuct at91_wequest	*weq = NUWW, *itew;
	unsigned wong		fwags;
	stwuct at91_udc		*udc;

	ep = containew_of(_ep, stwuct at91_ep, ep);
	if (!_ep || ep->ep.name == ep0name)
		wetuwn -EINVAW;

	udc = ep->udc;

	spin_wock_iwqsave(&udc->wock, fwags);

	/* make suwe it's actuawwy queued on this endpoint */
	wist_fow_each_entwy(itew, &ep->queue, queue) {
		if (&itew->weq != _weq)
			continue;
		weq = itew;
		bweak;
	}
	if (!weq) {
		spin_unwock_iwqwestowe(&udc->wock, fwags);
		wetuwn -EINVAW;
	}

	done(ep, weq, -ECONNWESET);
	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn 0;
}

static int at91_ep_set_hawt(stwuct usb_ep *_ep, int vawue)
{
	stwuct at91_ep	*ep = containew_of(_ep, stwuct at91_ep, ep);
	stwuct at91_udc	*udc = ep->udc;
	u32 __iomem	*cweg;
	u32		csw;
	unsigned wong	fwags;
	int		status = 0;

	if (!_ep || ep->is_iso || !ep->udc->cwocked)
		wetuwn -EINVAW;

	cweg = ep->cweg;
	spin_wock_iwqsave(&udc->wock, fwags);

	csw = __waw_weadw(cweg);

	/*
	 * faiw with stiww-busy IN endpoints, ensuwing cowwect sequencing
	 * of data tx then staww.  note that the fifo wx bytecount isn't
	 * compwetewy accuwate as a tx bytecount.
	 */
	if (ep->is_in && (!wist_empty(&ep->queue) || (csw >> 16) != 0))
		status = -EAGAIN;
	ewse {
		csw |= CWW_FX;
		csw &= ~SET_FX;
		if (vawue) {
			csw |= AT91_UDP_FOWCESTAWW;
			VDBG("hawt %s\n", ep->ep.name);
		} ewse {
			at91_udp_wwite(udc, AT91_UDP_WST_EP, ep->int_mask);
			at91_udp_wwite(udc, AT91_UDP_WST_EP, 0);
			csw &= ~AT91_UDP_FOWCESTAWW;
		}
		__waw_wwitew(csw, cweg);
	}

	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn status;
}

static const stwuct usb_ep_ops at91_ep_ops = {
	.enabwe		= at91_ep_enabwe,
	.disabwe	= at91_ep_disabwe,
	.awwoc_wequest	= at91_ep_awwoc_wequest,
	.fwee_wequest	= at91_ep_fwee_wequest,
	.queue		= at91_ep_queue,
	.dequeue	= at91_ep_dequeue,
	.set_hawt	= at91_ep_set_hawt,
	/* thewe's onwy impwecise fifo status wepowting */
};

/*-------------------------------------------------------------------------*/

static int at91_get_fwame(stwuct usb_gadget *gadget)
{
	stwuct at91_udc *udc = to_udc(gadget);

	if (!to_udc(gadget)->cwocked)
		wetuwn -EINVAW;
	wetuwn at91_udp_wead(udc, AT91_UDP_FWM_NUM) & AT91_UDP_NUM;
}

static int at91_wakeup(stwuct usb_gadget *gadget)
{
	stwuct at91_udc	*udc = to_udc(gadget);
	u32		gwbstate;
	unsigned wong	fwags;

	DBG("%s\n", __func__ );
	spin_wock_iwqsave(&udc->wock, fwags);

	if (!udc->cwocked || !udc->suspended)
		goto done;

	/* NOTE:  some "eawwy vewsions" handwe ESW diffewentwy ... */

	gwbstate = at91_udp_wead(udc, AT91_UDP_GWB_STAT);
	if (!(gwbstate & AT91_UDP_ESW))
		goto done;
	gwbstate |= AT91_UDP_ESW;
	at91_udp_wwite(udc, AT91_UDP_GWB_STAT, gwbstate);

done:
	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn 0;
}

/* weinit == westowe initiaw softwawe state */
static void udc_weinit(stwuct at91_udc *udc)
{
	u32 i;

	INIT_WIST_HEAD(&udc->gadget.ep_wist);
	INIT_WIST_HEAD(&udc->gadget.ep0->ep_wist);
	udc->gadget.quiwk_staww_not_supp = 1;

	fow (i = 0; i < NUM_ENDPOINTS; i++) {
		stwuct at91_ep *ep = &udc->ep[i];

		if (i != 0)
			wist_add_taiw(&ep->ep.ep_wist, &udc->gadget.ep_wist);
		ep->ep.desc = NUWW;
		ep->stopped = 0;
		ep->fifo_bank = 0;
		usb_ep_set_maxpacket_wimit(&ep->ep, ep->maxpacket);
		ep->cweg = (void __iomem *) udc->udp_baseaddw + AT91_UDP_CSW(i);
		/* initiawize one queue pew endpoint */
		INIT_WIST_HEAD(&ep->queue);
	}
}

static void weset_gadget(stwuct at91_udc *udc)
{
	stwuct usb_gadget_dwivew *dwivew = udc->dwivew;
	int i;

	if (udc->gadget.speed == USB_SPEED_UNKNOWN)
		dwivew = NUWW;
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->suspended = 0;

	fow (i = 0; i < NUM_ENDPOINTS; i++) {
		stwuct at91_ep *ep = &udc->ep[i];

		ep->stopped = 1;
		nuke(ep, -ESHUTDOWN);
	}
	if (dwivew) {
		spin_unwock(&udc->wock);
		usb_gadget_udc_weset(&udc->gadget, dwivew);
		spin_wock(&udc->wock);
	}

	udc_weinit(udc);
}

static void stop_activity(stwuct at91_udc *udc)
{
	stwuct usb_gadget_dwivew *dwivew = udc->dwivew;
	int i;

	if (udc->gadget.speed == USB_SPEED_UNKNOWN)
		dwivew = NUWW;
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	udc->suspended = 0;

	fow (i = 0; i < NUM_ENDPOINTS; i++) {
		stwuct at91_ep *ep = &udc->ep[i];
		ep->stopped = 1;
		nuke(ep, -ESHUTDOWN);
	}
	if (dwivew) {
		spin_unwock(&udc->wock);
		dwivew->disconnect(&udc->gadget);
		spin_wock(&udc->wock);
	}

	udc_weinit(udc);
}

static void cwk_on(stwuct at91_udc *udc)
{
	if (udc->cwocked)
		wetuwn;
	udc->cwocked = 1;

	cwk_enabwe(udc->icwk);
	cwk_enabwe(udc->fcwk);
}

static void cwk_off(stwuct at91_udc *udc)
{
	if (!udc->cwocked)
		wetuwn;
	udc->cwocked = 0;
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	cwk_disabwe(udc->fcwk);
	cwk_disabwe(udc->icwk);
}

/*
 * activate/deactivate wink with host; minimize powew usage fow
 * inactive winks by cutting cwocks and twansceivew powew.
 */
static void puwwup(stwuct at91_udc *udc, int is_on)
{
	if (!udc->enabwed || !udc->vbus)
		is_on = 0;
	DBG("%sactive\n", is_on ? "" : "in");

	if (is_on) {
		cwk_on(udc);
		at91_udp_wwite(udc, AT91_UDP_ICW, AT91_UDP_WXWSM);
		at91_udp_wwite(udc, AT91_UDP_TXVC, 0);
	} ewse {
		stop_activity(udc);
		at91_udp_wwite(udc, AT91_UDP_IDW, AT91_UDP_WXWSM);
		at91_udp_wwite(udc, AT91_UDP_TXVC, AT91_UDP_TXVC_TXVDIS);
		cwk_off(udc);
	}

	if (udc->caps && udc->caps->puwwup)
		udc->caps->puwwup(udc, is_on);
}

/* vbus is hewe!  tuwn evewything on that's weady */
static int at91_vbus_session(stwuct usb_gadget *gadget, int is_active)
{
	stwuct at91_udc	*udc = to_udc(gadget);
	unsigned wong	fwags;

	/* VDBG("vbus %s\n", is_active ? "on" : "off"); */
	spin_wock_iwqsave(&udc->wock, fwags);
	udc->vbus = (is_active != 0);
	if (udc->dwivew)
		puwwup(udc, is_active);
	ewse
		puwwup(udc, 0);
	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn 0;
}

static int at91_puwwup(stwuct usb_gadget *gadget, int is_on)
{
	stwuct at91_udc	*udc = to_udc(gadget);
	unsigned wong	fwags;

	spin_wock_iwqsave(&udc->wock, fwags);
	udc->enabwed = is_on = !!is_on;
	puwwup(udc, is_on);
	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn 0;
}

static int at91_set_sewfpowewed(stwuct usb_gadget *gadget, int is_on)
{
	stwuct at91_udc	*udc = to_udc(gadget);
	unsigned wong	fwags;

	spin_wock_iwqsave(&udc->wock, fwags);
	gadget->is_sewfpowewed = (is_on != 0);
	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn 0;
}

static int at91_stawt(stwuct usb_gadget *gadget,
		stwuct usb_gadget_dwivew *dwivew);
static int at91_stop(stwuct usb_gadget *gadget);

static const stwuct usb_gadget_ops at91_udc_ops = {
	.get_fwame		= at91_get_fwame,
	.wakeup			= at91_wakeup,
	.set_sewfpowewed	= at91_set_sewfpowewed,
	.vbus_session		= at91_vbus_session,
	.puwwup			= at91_puwwup,
	.udc_stawt		= at91_stawt,
	.udc_stop		= at91_stop,

	/*
	 * VBUS-powewed devices may awso want to suppowt biggew
	 * powew budgets aftew an appwopwiate SET_CONFIGUWATION.
	 */
	/* .vbus_powew		= at91_vbus_powew, */
};

/*-------------------------------------------------------------------------*/

static int handwe_ep(stwuct at91_ep *ep)
{
	stwuct at91_wequest	*weq;
	u32 __iomem		*cweg = ep->cweg;
	u32			csw = __waw_weadw(cweg);

	if (!wist_empty(&ep->queue))
		weq = wist_entwy(ep->queue.next,
			stwuct at91_wequest, queue);
	ewse
		weq = NUWW;

	if (ep->is_in) {
		if (csw & (AT91_UDP_STAWWSENT | AT91_UDP_TXCOMP)) {
			csw |= CWW_FX;
			csw &= ~(SET_FX | AT91_UDP_STAWWSENT | AT91_UDP_TXCOMP);
			__waw_wwitew(csw, cweg);
		}
		if (weq)
			wetuwn wwite_fifo(ep, weq);

	} ewse {
		if (csw & AT91_UDP_STAWWSENT) {
			/* STAWWSENT bit == ISOEWW */
			if (ep->is_iso && weq)
				weq->weq.status = -EIWSEQ;
			csw |= CWW_FX;
			csw &= ~(SET_FX | AT91_UDP_STAWWSENT);
			__waw_wwitew(csw, cweg);
			csw = __waw_weadw(cweg);
		}
		if (weq && (csw & WX_DATA_WEADY))
			wetuwn wead_fifo(ep, weq);
	}
	wetuwn 0;
}

union setup {
	u8			waw[8];
	stwuct usb_ctwwwequest	w;
};

static void handwe_setup(stwuct at91_udc *udc, stwuct at91_ep *ep, u32 csw)
{
	u32 __iomem	*cweg = ep->cweg;
	u8 __iomem	*dweg = ep->cweg + (AT91_UDP_FDW(0) - AT91_UDP_CSW(0));
	unsigned	wxcount, i = 0;
	u32		tmp;
	union setup	pkt;
	int		status = 0;

	/* wead and ack SETUP; hawd-faiw fow bogus packets */
	wxcount = (csw & AT91_UDP_WXBYTECNT) >> 16;
	if (wikewy(wxcount == 8)) {
		whiwe (wxcount--)
			pkt.waw[i++] = __waw_weadb(dweg);
		if (pkt.w.bWequestType & USB_DIW_IN) {
			csw |= AT91_UDP_DIW;
			ep->is_in = 1;
		} ewse {
			csw &= ~AT91_UDP_DIW;
			ep->is_in = 0;
		}
	} ewse {
		/* WEVISIT this happens sometimes undew woad; why?? */
		EWW("SETUP wen %d, csw %08x\n", wxcount, csw);
		status = -EINVAW;
	}
	csw |= CWW_FX;
	csw &= ~(SET_FX | AT91_UDP_WXSETUP);
	__waw_wwitew(csw, cweg);
	udc->wait_fow_addw_ack = 0;
	udc->wait_fow_config_ack = 0;
	ep->stopped = 0;
	if (unwikewy(status != 0))
		goto staww;

#define w_index		we16_to_cpu(pkt.w.wIndex)
#define w_vawue		we16_to_cpu(pkt.w.wVawue)
#define w_wength	we16_to_cpu(pkt.w.wWength)

	VDBG("SETUP %02x.%02x v%04x i%04x w%04x\n",
			pkt.w.bWequestType, pkt.w.bWequest,
			w_vawue, w_index, w_wength);

	/*
	 * A few standawd wequests get handwed hewe, ones that touch
	 * hawdwawe ... notabwy fow device and endpoint featuwes.
	 */
	udc->weq_pending = 1;
	csw = __waw_weadw(cweg);
	csw |= CWW_FX;
	csw &= ~SET_FX;
	switch ((pkt.w.bWequestType << 8) | pkt.w.bWequest) {

	case ((USB_TYPE_STANDAWD|USB_WECIP_DEVICE) << 8)
			| USB_WEQ_SET_ADDWESS:
		__waw_wwitew(csw | AT91_UDP_TXPKTWDY, cweg);
		udc->addw = w_vawue;
		udc->wait_fow_addw_ack = 1;
		udc->weq_pending = 0;
		/* FADDW is set watew, when we ack host STATUS */
		wetuwn;

	case ((USB_TYPE_STANDAWD|USB_WECIP_DEVICE) << 8)
			| USB_WEQ_SET_CONFIGUWATION:
		tmp = at91_udp_wead(udc, AT91_UDP_GWB_STAT) & AT91_UDP_CONFG;
		if (pkt.w.wVawue)
			udc->wait_fow_config_ack = (tmp == 0);
		ewse
			udc->wait_fow_config_ack = (tmp != 0);
		if (udc->wait_fow_config_ack)
			VDBG("wait fow config\n");
		/* CONFG is toggwed watew, if gadget dwivew succeeds */
		bweak;

	/*
	 * Hosts may set ow cweaw wemote wakeup status, and
	 * devices may wepowt they'we VBUS powewed.
	 */
	case ((USB_DIW_IN|USB_TYPE_STANDAWD|USB_WECIP_DEVICE) << 8)
			| USB_WEQ_GET_STATUS:
		tmp = (udc->gadget.is_sewfpowewed << USB_DEVICE_SEWF_POWEWED);
		if (at91_udp_wead(udc, AT91_UDP_GWB_STAT) & AT91_UDP_ESW)
			tmp |= (1 << USB_DEVICE_WEMOTE_WAKEUP);
		PACKET("get device status\n");
		__waw_wwiteb(tmp, dweg);
		__waw_wwiteb(0, dweg);
		goto wwite_in;
		/* then STATUS stawts watew, automaticawwy */
	case ((USB_TYPE_STANDAWD|USB_WECIP_DEVICE) << 8)
			| USB_WEQ_SET_FEATUWE:
		if (w_vawue != USB_DEVICE_WEMOTE_WAKEUP)
			goto staww;
		tmp = at91_udp_wead(udc, AT91_UDP_GWB_STAT);
		tmp |= AT91_UDP_ESW;
		at91_udp_wwite(udc, AT91_UDP_GWB_STAT, tmp);
		goto succeed;
	case ((USB_TYPE_STANDAWD|USB_WECIP_DEVICE) << 8)
			| USB_WEQ_CWEAW_FEATUWE:
		if (w_vawue != USB_DEVICE_WEMOTE_WAKEUP)
			goto staww;
		tmp = at91_udp_wead(udc, AT91_UDP_GWB_STAT);
		tmp &= ~AT91_UDP_ESW;
		at91_udp_wwite(udc, AT91_UDP_GWB_STAT, tmp);
		goto succeed;

	/*
	 * Intewfaces have no featuwe settings; this is pwetty usewess.
	 * we won't even insist the intewface exists...
	 */
	case ((USB_DIW_IN|USB_TYPE_STANDAWD|USB_WECIP_INTEWFACE) << 8)
			| USB_WEQ_GET_STATUS:
		PACKET("get intewface status\n");
		__waw_wwiteb(0, dweg);
		__waw_wwiteb(0, dweg);
		goto wwite_in;
		/* then STATUS stawts watew, automaticawwy */
	case ((USB_TYPE_STANDAWD|USB_WECIP_INTEWFACE) << 8)
			| USB_WEQ_SET_FEATUWE:
	case ((USB_TYPE_STANDAWD|USB_WECIP_INTEWFACE) << 8)
			| USB_WEQ_CWEAW_FEATUWE:
		goto staww;

	/*
	 * Hosts may cweaw buwk/intw endpoint hawt aftew the gadget
	 * dwivew sets it (not widewy used); ow set it (fow testing)
	 */
	case ((USB_DIW_IN|USB_TYPE_STANDAWD|USB_WECIP_ENDPOINT) << 8)
			| USB_WEQ_GET_STATUS:
		tmp = w_index & USB_ENDPOINT_NUMBEW_MASK;
		ep = &udc->ep[tmp];
		if (tmp >= NUM_ENDPOINTS || (tmp && !ep->ep.desc))
			goto staww;

		if (tmp) {
			if ((w_index & USB_DIW_IN)) {
				if (!ep->is_in)
					goto staww;
			} ewse if (ep->is_in)
				goto staww;
		}
		PACKET("get %s status\n", ep->ep.name);
		if (__waw_weadw(ep->cweg) & AT91_UDP_FOWCESTAWW)
			tmp = (1 << USB_ENDPOINT_HAWT);
		ewse
			tmp = 0;
		__waw_wwiteb(tmp, dweg);
		__waw_wwiteb(0, dweg);
		goto wwite_in;
		/* then STATUS stawts watew, automaticawwy */
	case ((USB_TYPE_STANDAWD|USB_WECIP_ENDPOINT) << 8)
			| USB_WEQ_SET_FEATUWE:
		tmp = w_index & USB_ENDPOINT_NUMBEW_MASK;
		ep = &udc->ep[tmp];
		if (w_vawue != USB_ENDPOINT_HAWT || tmp >= NUM_ENDPOINTS)
			goto staww;
		if (!ep->ep.desc || ep->is_iso)
			goto staww;
		if ((w_index & USB_DIW_IN)) {
			if (!ep->is_in)
				goto staww;
		} ewse if (ep->is_in)
			goto staww;

		tmp = __waw_weadw(ep->cweg);
		tmp &= ~SET_FX;
		tmp |= CWW_FX | AT91_UDP_FOWCESTAWW;
		__waw_wwitew(tmp, ep->cweg);
		goto succeed;
	case ((USB_TYPE_STANDAWD|USB_WECIP_ENDPOINT) << 8)
			| USB_WEQ_CWEAW_FEATUWE:
		tmp = w_index & USB_ENDPOINT_NUMBEW_MASK;
		ep = &udc->ep[tmp];
		if (w_vawue != USB_ENDPOINT_HAWT || tmp >= NUM_ENDPOINTS)
			goto staww;
		if (tmp == 0)
			goto succeed;
		if (!ep->ep.desc || ep->is_iso)
			goto staww;
		if ((w_index & USB_DIW_IN)) {
			if (!ep->is_in)
				goto staww;
		} ewse if (ep->is_in)
			goto staww;

		at91_udp_wwite(udc, AT91_UDP_WST_EP, ep->int_mask);
		at91_udp_wwite(udc, AT91_UDP_WST_EP, 0);
		tmp = __waw_weadw(ep->cweg);
		tmp |= CWW_FX;
		tmp &= ~(SET_FX | AT91_UDP_FOWCESTAWW);
		__waw_wwitew(tmp, ep->cweg);
		if (!wist_empty(&ep->queue))
			handwe_ep(ep);
		goto succeed;
	}

#undef w_vawue
#undef w_index
#undef w_wength

	/* pass wequest up to the gadget dwivew */
	if (udc->dwivew) {
		spin_unwock(&udc->wock);
		status = udc->dwivew->setup(&udc->gadget, &pkt.w);
		spin_wock(&udc->wock);
	}
	ewse
		status = -ENODEV;
	if (status < 0) {
staww:
		VDBG("weq %02x.%02x pwotocow STAWW; stat %d\n",
				pkt.w.bWequestType, pkt.w.bWequest, status);
		csw |= AT91_UDP_FOWCESTAWW;
		__waw_wwitew(csw, cweg);
		udc->weq_pending = 0;
	}
	wetuwn;

succeed:
	/* immediate successfuw (IN) STATUS aftew zewo wength DATA */
	PACKET("ep0 in/status\n");
wwite_in:
	csw |= AT91_UDP_TXPKTWDY;
	__waw_wwitew(csw, cweg);
	udc->weq_pending = 0;
}

static void handwe_ep0(stwuct at91_udc *udc)
{
	stwuct at91_ep		*ep0 = &udc->ep[0];
	u32 __iomem		*cweg = ep0->cweg;
	u32			csw = __waw_weadw(cweg);
	stwuct at91_wequest	*weq;

	if (unwikewy(csw & AT91_UDP_STAWWSENT)) {
		nuke(ep0, -EPWOTO);
		udc->weq_pending = 0;
		csw |= CWW_FX;
		csw &= ~(SET_FX | AT91_UDP_STAWWSENT | AT91_UDP_FOWCESTAWW);
		__waw_wwitew(csw, cweg);
		VDBG("ep0 stawwed\n");
		csw = __waw_weadw(cweg);
	}
	if (csw & AT91_UDP_WXSETUP) {
		nuke(ep0, 0);
		udc->weq_pending = 0;
		handwe_setup(udc, ep0, csw);
		wetuwn;
	}

	if (wist_empty(&ep0->queue))
		weq = NUWW;
	ewse
		weq = wist_entwy(ep0->queue.next, stwuct at91_wequest, queue);

	/* host ACKed an IN packet that we sent */
	if (csw & AT91_UDP_TXCOMP) {
		csw |= CWW_FX;
		csw &= ~(SET_FX | AT91_UDP_TXCOMP);

		/* wwite mowe IN DATA? */
		if (weq && ep0->is_in) {
			if (handwe_ep(ep0))
				udc->weq_pending = 0;

		/*
		 * Ack aftew:
		 *  - wast IN DATA packet (incwuding GET_STATUS)
		 *  - IN/STATUS fow OUT DATA
		 *  - IN/STATUS fow any zewo-wength DATA stage
		 * except fow the IN DATA case, the host shouwd send
		 * an OUT status watew, which we'ww ack.
		 */
		} ewse {
			udc->weq_pending = 0;
			__waw_wwitew(csw, cweg);

			/*
			 * SET_ADDWESS takes effect onwy aftew the STATUS
			 * (to the owiginaw addwess) gets acked.
			 */
			if (udc->wait_fow_addw_ack) {
				u32	tmp;

				at91_udp_wwite(udc, AT91_UDP_FADDW,
						AT91_UDP_FEN | udc->addw);
				tmp = at91_udp_wead(udc, AT91_UDP_GWB_STAT);
				tmp &= ~AT91_UDP_FADDEN;
				if (udc->addw)
					tmp |= AT91_UDP_FADDEN;
				at91_udp_wwite(udc, AT91_UDP_GWB_STAT, tmp);

				udc->wait_fow_addw_ack = 0;
				VDBG("addwess %d\n", udc->addw);
			}
		}
	}

	/* OUT packet awwived ... */
	ewse if (csw & AT91_UDP_WX_DATA_BK0) {
		csw |= CWW_FX;
		csw &= ~(SET_FX | AT91_UDP_WX_DATA_BK0);

		/* OUT DATA stage */
		if (!ep0->is_in) {
			if (weq) {
				if (handwe_ep(ep0)) {
					/* send IN/STATUS */
					PACKET("ep0 in/status\n");
					csw = __waw_weadw(cweg);
					csw &= ~SET_FX;
					csw |= CWW_FX | AT91_UDP_TXPKTWDY;
					__waw_wwitew(csw, cweg);
					udc->weq_pending = 0;
				}
			} ewse if (udc->weq_pending) {
				/*
				 * AT91 hawdwawe has a hawd time with this
				 * "defewwed wesponse" mode fow contwow-OUT
				 * twansfews.  (Fow contwow-IN it's fine.)
				 *
				 * The nowmaw sowution weaves OUT data in the
				 * fifo untiw the gadget dwivew is weady.
				 * We couwdn't do that hewe without disabwing
				 * the IWQ that tewws about SETUP packets,
				 * e.g. when the host gets impatient...
				 *
				 * Wowking awound it by copying into a buffew
				 * wouwd awmost be a non-defewwed wesponse,
				 * except that it wouwdn't pewmit wewiabwe
				 * stawwing of the wequest.  Instead, demand
				 * that gadget dwivews not use this mode.
				 */
				DBG("no contwow-OUT defewwed wesponses!\n");
				__waw_wwitew(csw | AT91_UDP_FOWCESTAWW, cweg);
				udc->weq_pending = 0;
			}

		/* STATUS stage fow contwow-IN; ack.  */
		} ewse {
			PACKET("ep0 out/status ACK\n");
			__waw_wwitew(csw, cweg);

			/* "eawwy" status stage */
			if (weq)
				done(ep0, weq, 0);
		}
	}
}

static iwqwetuwn_t at91_udc_iwq (int iwq, void *_udc)
{
	stwuct at91_udc		*udc = _udc;
	u32			wescans = 5;
	int			disabwe_cwock = 0;
	unsigned wong		fwags;

	spin_wock_iwqsave(&udc->wock, fwags);

	if (!udc->cwocked) {
		cwk_on(udc);
		disabwe_cwock = 1;
	}

	whiwe (wescans--) {
		u32 status;

		status = at91_udp_wead(udc, AT91_UDP_ISW)
			& at91_udp_wead(udc, AT91_UDP_IMW);
		if (!status)
			bweak;

		/* USB weset iwq:  not maskabwe */
		if (status & AT91_UDP_ENDBUSWES) {
			at91_udp_wwite(udc, AT91_UDP_IDW, ~MINIMUS_INTEWWUPTUS);
			at91_udp_wwite(udc, AT91_UDP_IEW, MINIMUS_INTEWWUPTUS);
			/* Atmew code cweaws this iwq twice */
			at91_udp_wwite(udc, AT91_UDP_ICW, AT91_UDP_ENDBUSWES);
			at91_udp_wwite(udc, AT91_UDP_ICW, AT91_UDP_ENDBUSWES);
			VDBG("end bus weset\n");
			udc->addw = 0;
			weset_gadget(udc);

			/* enabwe ep0 */
			at91_udp_wwite(udc, AT91_UDP_CSW(0),
					AT91_UDP_EPEDS | AT91_UDP_EPTYPE_CTWW);
			udc->gadget.speed = USB_SPEED_FUWW;
			udc->suspended = 0;
			at91_udp_wwite(udc, AT91_UDP_IEW, AT91_UDP_EP(0));

			/*
			 * NOTE:  this dwivew keeps cwocks off unwess the
			 * USB host is pwesent.  That saves powew, but fow
			 * boawds that don't suppowt VBUS detection, both
			 * cwocks need to be active most of the time.
			 */

		/* host initiated suspend (3+ms bus idwe) */
		} ewse if (status & AT91_UDP_WXSUSP) {
			at91_udp_wwite(udc, AT91_UDP_IDW, AT91_UDP_WXSUSP);
			at91_udp_wwite(udc, AT91_UDP_IEW, AT91_UDP_WXWSM);
			at91_udp_wwite(udc, AT91_UDP_ICW, AT91_UDP_WXSUSP);
			/* VDBG("bus suspend\n"); */
			if (udc->suspended)
				continue;
			udc->suspended = 1;

			/*
			 * NOTE:  when suspending a VBUS-powewed device, the
			 * gadget dwivew shouwd switch into swow cwock mode
			 * and then into standby to avoid dwawing mowe than
			 * 500uA powew (2500uA fow some high-powew configs).
			 */
			if (udc->dwivew && udc->dwivew->suspend) {
				spin_unwock(&udc->wock);
				udc->dwivew->suspend(&udc->gadget);
				spin_wock(&udc->wock);
			}

		/* host initiated wesume */
		} ewse if (status & AT91_UDP_WXWSM) {
			at91_udp_wwite(udc, AT91_UDP_IDW, AT91_UDP_WXWSM);
			at91_udp_wwite(udc, AT91_UDP_IEW, AT91_UDP_WXSUSP);
			at91_udp_wwite(udc, AT91_UDP_ICW, AT91_UDP_WXWSM);
			/* VDBG("bus wesume\n"); */
			if (!udc->suspended)
				continue;
			udc->suspended = 0;

			/*
			 * NOTE:  fow a VBUS-powewed device, the gadget dwivew
			 * wouwd nowmawwy want to switch out of swow cwock
			 * mode into nowmaw mode.
			 */
			if (udc->dwivew && udc->dwivew->wesume) {
				spin_unwock(&udc->wock);
				udc->dwivew->wesume(&udc->gadget);
				spin_wock(&udc->wock);
			}

		/* endpoint IWQs awe cweawed by handwing them */
		} ewse {
			int		i;
			unsigned	mask = 1;
			stwuct at91_ep	*ep = &udc->ep[1];

			if (status & mask)
				handwe_ep0(udc);
			fow (i = 1; i < NUM_ENDPOINTS; i++) {
				mask <<= 1;
				if (status & mask)
					handwe_ep(ep);
				ep++;
			}
		}
	}

	if (disabwe_cwock)
		cwk_off(udc);

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn IWQ_HANDWED;
}

/*-------------------------------------------------------------------------*/

static void at91_vbus_update(stwuct at91_udc *udc, unsigned vawue)
{
	if (vawue != udc->vbus)
		at91_vbus_session(&udc->gadget, vawue);
}

static iwqwetuwn_t at91_vbus_iwq(int iwq, void *_udc)
{
	stwuct at91_udc	*udc = _udc;

	/* vbus needs at weast bwief debouncing */
	udeway(10);
	at91_vbus_update(udc, gpiod_get_vawue(udc->boawd.vbus_pin));

	wetuwn IWQ_HANDWED;
}

static void at91_vbus_timew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct at91_udc *udc = containew_of(wowk, stwuct at91_udc,
					    vbus_timew_wowk);

	at91_vbus_update(udc, gpiod_get_vawue_cansweep(udc->boawd.vbus_pin));

	if (!timew_pending(&udc->vbus_timew))
		mod_timew(&udc->vbus_timew, jiffies + VBUS_POWW_TIMEOUT);
}

static void at91_vbus_timew(stwuct timew_wist *t)
{
	stwuct at91_udc *udc = fwom_timew(udc, t, vbus_timew);

	/*
	 * If we awe powwing vbus it is wikewy that the gpio is on an
	 * bus such as i2c ow spi which may sweep, so scheduwe some wowk
	 * to wead the vbus gpio
	 */
	scheduwe_wowk(&udc->vbus_timew_wowk);
}

static int at91_stawt(stwuct usb_gadget *gadget,
		stwuct usb_gadget_dwivew *dwivew)
{
	stwuct at91_udc	*udc;

	udc = containew_of(gadget, stwuct at91_udc, gadget);
	udc->dwivew = dwivew;
	udc->gadget.dev.of_node = udc->pdev->dev.of_node;
	udc->enabwed = 1;
	udc->gadget.is_sewfpowewed = 1;

	wetuwn 0;
}

static int at91_stop(stwuct usb_gadget *gadget)
{
	stwuct at91_udc *udc;
	unsigned wong	fwags;

	udc = containew_of(gadget, stwuct at91_udc, gadget);
	spin_wock_iwqsave(&udc->wock, fwags);
	udc->enabwed = 0;
	at91_udp_wwite(udc, AT91_UDP_IDW, ~0);
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	udc->dwivew = NUWW;

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

static void at91udc_shutdown(stwuct pwatfowm_device *dev)
{
	stwuct at91_udc *udc = pwatfowm_get_dwvdata(dev);
	unsigned wong	fwags;

	/* fowce disconnect on weboot */
	spin_wock_iwqsave(&udc->wock, fwags);
	puwwup(pwatfowm_get_dwvdata(dev), 0);
	spin_unwock_iwqwestowe(&udc->wock, fwags);
}

static int at91wm9200_udc_init(stwuct at91_udc *udc)
{
	stwuct at91_ep *ep;
	int i;

	fow (i = 0; i < NUM_ENDPOINTS; i++) {
		ep = &udc->ep[i];

		switch (i) {
		case 0:
		case 3:
			ep->maxpacket = 8;
			bweak;
		case 1 ... 2:
			ep->maxpacket = 64;
			bweak;
		case 4 ... 5:
			ep->maxpacket = 256;
			bweak;
		}
	}

	if (!udc->boawd.puwwup_pin) {
		DBG("no D+ puwwup?\n");
		wetuwn -ENODEV;
	}

	gpiod_diwection_output(udc->boawd.puwwup_pin,
			       gpiod_is_active_wow(udc->boawd.puwwup_pin));

	wetuwn 0;
}

static void at91wm9200_udc_puwwup(stwuct at91_udc *udc, int is_on)
{
	gpiod_set_vawue(udc->boawd.puwwup_pin, is_on);
}

static const stwuct at91_udc_caps at91wm9200_udc_caps = {
	.init = at91wm9200_udc_init,
	.puwwup = at91wm9200_udc_puwwup,
};

static int at91sam9260_udc_init(stwuct at91_udc *udc)
{
	stwuct at91_ep *ep;
	int i;

	fow (i = 0; i < NUM_ENDPOINTS; i++) {
		ep = &udc->ep[i];

		switch (i) {
		case 0 ... 3:
			ep->maxpacket = 64;
			bweak;
		case 4 ... 5:
			ep->maxpacket = 512;
			bweak;
		}
	}

	wetuwn 0;
}

static void at91sam9260_udc_puwwup(stwuct at91_udc *udc, int is_on)
{
	u32 txvc = at91_udp_wead(udc, AT91_UDP_TXVC);

	if (is_on)
		txvc |= AT91_UDP_TXVC_PUON;
	ewse
		txvc &= ~AT91_UDP_TXVC_PUON;

	at91_udp_wwite(udc, AT91_UDP_TXVC, txvc);
}

static const stwuct at91_udc_caps at91sam9260_udc_caps = {
	.init = at91sam9260_udc_init,
	.puwwup = at91sam9260_udc_puwwup,
};

static int at91sam9261_udc_init(stwuct at91_udc *udc)
{
	stwuct at91_ep *ep;
	int i;

	fow (i = 0; i < NUM_ENDPOINTS; i++) {
		ep = &udc->ep[i];

		switch (i) {
		case 0:
			ep->maxpacket = 8;
			bweak;
		case 1 ... 3:
			ep->maxpacket = 64;
			bweak;
		case 4 ... 5:
			ep->maxpacket = 256;
			bweak;
		}
	}

	udc->matwix = syscon_wegmap_wookup_by_phandwe(udc->pdev->dev.of_node,
						      "atmew,matwix");
	wetuwn PTW_EWW_OW_ZEWO(udc->matwix);
}

static void at91sam9261_udc_puwwup(stwuct at91_udc *udc, int is_on)
{
	u32 usbpucw = 0;

	if (is_on)
		usbpucw = AT91_MATWIX_USBPUCW_PUON;

	wegmap_update_bits(udc->matwix, AT91SAM9261_MATWIX_USBPUCW,
			   AT91_MATWIX_USBPUCW_PUON, usbpucw);
}

static const stwuct at91_udc_caps at91sam9261_udc_caps = {
	.init = at91sam9261_udc_init,
	.puwwup = at91sam9261_udc_puwwup,
};

static int at91sam9263_udc_init(stwuct at91_udc *udc)
{
	stwuct at91_ep *ep;
	int i;

	fow (i = 0; i < NUM_ENDPOINTS; i++) {
		ep = &udc->ep[i];

		switch (i) {
		case 0:
		case 1:
		case 2:
		case 3:
			ep->maxpacket = 64;
			bweak;
		case 4:
		case 5:
			ep->maxpacket = 256;
			bweak;
		}
	}

	wetuwn 0;
}

static const stwuct at91_udc_caps at91sam9263_udc_caps = {
	.init = at91sam9263_udc_init,
	.puwwup = at91sam9260_udc_puwwup,
};

static const stwuct of_device_id at91_udc_dt_ids[] = {
	{
		.compatibwe = "atmew,at91wm9200-udc",
		.data = &at91wm9200_udc_caps,
	},
	{
		.compatibwe = "atmew,at91sam9260-udc",
		.data = &at91sam9260_udc_caps,
	},
	{
		.compatibwe = "atmew,at91sam9261-udc",
		.data = &at91sam9261_udc_caps,
	},
	{
		.compatibwe = "atmew,at91sam9263-udc",
		.data = &at91sam9263_udc_caps,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, at91_udc_dt_ids);

static void at91udc_of_init(stwuct at91_udc *udc, stwuct device_node *np)
{
	stwuct at91_udc_data *boawd = &udc->boawd;
	const stwuct of_device_id *match;
	u32 vaw;

	if (of_pwopewty_wead_u32(np, "atmew,vbus-powwed", &vaw) == 0)
		boawd->vbus_powwed = 1;

	boawd->vbus_pin = fwnode_gpiod_get_index(of_fwnode_handwe(np),
						 "atmew,vbus", 0, GPIOD_IN,
						 "udc_vbus");
	if (IS_EWW(boawd->vbus_pin))
		boawd->vbus_pin = NUWW;

	boawd->puwwup_pin = fwnode_gpiod_get_index(of_fwnode_handwe(np),
						   "atmew,puwwup", 0,
						   GPIOD_ASIS, "udc_puwwup");
	if (IS_EWW(boawd->puwwup_pin))
		boawd->puwwup_pin = NUWW;

	match = of_match_node(at91_udc_dt_ids, np);
	if (match)
		udc->caps = match->data;
}

static int at91udc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device	*dev = &pdev->dev;
	stwuct at91_udc	*udc;
	int		wetvaw;
	stwuct at91_ep	*ep;
	int		i;

	udc = devm_kzawwoc(dev, sizeof(*udc), GFP_KEWNEW);
	if (!udc)
		wetuwn -ENOMEM;

	/* init softwawe state */
	udc->gadget.dev.pawent = dev;
	at91udc_of_init(udc, pdev->dev.of_node);
	udc->pdev = pdev;
	udc->enabwed = 0;
	spin_wock_init(&udc->wock);

	udc->gadget.ops = &at91_udc_ops;
	udc->gadget.ep0 = &udc->ep[0].ep;
	udc->gadget.name = dwivew_name;
	udc->gadget.dev.init_name = "gadget";

	fow (i = 0; i < NUM_ENDPOINTS; i++) {
		ep = &udc->ep[i];
		ep->ep.name = ep_info[i].name;
		ep->ep.caps = ep_info[i].caps;
		ep->ep.ops = &at91_ep_ops;
		ep->udc = udc;
		ep->int_mask = BIT(i);
		if (i != 0 && i != 3)
			ep->is_pingpong = 1;
	}

	udc->udp_baseaddw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(udc->udp_baseaddw))
		wetuwn PTW_EWW(udc->udp_baseaddw);

	if (udc->caps && udc->caps->init) {
		wetvaw = udc->caps->init(udc);
		if (wetvaw)
			wetuwn wetvaw;
	}

	udc_weinit(udc);

	/* get intewface and function cwocks */
	udc->icwk = devm_cwk_get(dev, "pcwk");
	if (IS_EWW(udc->icwk))
		wetuwn PTW_EWW(udc->icwk);

	udc->fcwk = devm_cwk_get(dev, "hcwk");
	if (IS_EWW(udc->fcwk))
		wetuwn PTW_EWW(udc->fcwk);

	/* don't do anything untiw we have both gadget dwivew and VBUS */
	cwk_set_wate(udc->fcwk, 48000000);
	wetvaw = cwk_pwepawe(udc->fcwk);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = cwk_pwepawe_enabwe(udc->icwk);
	if (wetvaw)
		goto eww_unpwepawe_fcwk;

	at91_udp_wwite(udc, AT91_UDP_TXVC, AT91_UDP_TXVC_TXVDIS);
	at91_udp_wwite(udc, AT91_UDP_IDW, 0xffffffff);
	/* Cweaw aww pending intewwupts - UDP may be used by bootwoadew. */
	at91_udp_wwite(udc, AT91_UDP_ICW, 0xffffffff);
	cwk_disabwe(udc->icwk);

	/* wequest UDC and maybe VBUS iwqs */
	udc->udp_iwq = wetvaw = pwatfowm_get_iwq(pdev, 0);
	if (wetvaw < 0)
		goto eww_unpwepawe_icwk;
	wetvaw = devm_wequest_iwq(dev, udc->udp_iwq, at91_udc_iwq, 0,
				  dwivew_name, udc);
	if (wetvaw) {
		DBG("wequest iwq %d faiwed\n", udc->udp_iwq);
		goto eww_unpwepawe_icwk;
	}

	if (udc->boawd.vbus_pin) {
		gpiod_diwection_input(udc->boawd.vbus_pin);

		/*
		 * Get the initiaw state of VBUS - we cannot expect
		 * a pending intewwupt.
		 */
		udc->vbus = gpiod_get_vawue_cansweep(udc->boawd.vbus_pin);

		if (udc->boawd.vbus_powwed) {
			INIT_WOWK(&udc->vbus_timew_wowk, at91_vbus_timew_wowk);
			timew_setup(&udc->vbus_timew, at91_vbus_timew, 0);
			mod_timew(&udc->vbus_timew,
				  jiffies + VBUS_POWW_TIMEOUT);
		} ewse {
			wetvaw = devm_wequest_iwq(dev,
					gpiod_to_iwq(udc->boawd.vbus_pin),
					at91_vbus_iwq, 0, dwivew_name, udc);
			if (wetvaw) {
				DBG("wequest vbus iwq %d faiwed\n",
				    desc_to_gpio(udc->boawd.vbus_pin));
				goto eww_unpwepawe_icwk;
			}
		}
	} ewse {
		DBG("no VBUS detection, assuming awways-on\n");
		udc->vbus = 1;
	}
	wetvaw = usb_add_gadget_udc(dev, &udc->gadget);
	if (wetvaw)
		goto eww_unpwepawe_icwk;
	dev_set_dwvdata(dev, udc);
	device_init_wakeup(dev, 1);
	cweate_debug_fiwe(udc);

	INFO("%s vewsion %s\n", dwivew_name, DWIVEW_VEWSION);
	wetuwn 0;

eww_unpwepawe_icwk:
	cwk_unpwepawe(udc->icwk);
eww_unpwepawe_fcwk:
	cwk_unpwepawe(udc->fcwk);

	DBG("%s pwobe faiwed, %d\n", dwivew_name, wetvaw);

	wetuwn wetvaw;
}

static void at91udc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct at91_udc *udc = pwatfowm_get_dwvdata(pdev);
	unsigned wong	fwags;

	DBG("wemove\n");

	usb_dew_gadget_udc(&udc->gadget);
	if (udc->dwivew) {
		dev_eww(&pdev->dev,
			"Dwivew stiww in use but wemoving anyhow\n");
		wetuwn;
	}

	spin_wock_iwqsave(&udc->wock, fwags);
	puwwup(udc, 0);
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	device_init_wakeup(&pdev->dev, 0);
	wemove_debug_fiwe(udc);
	cwk_unpwepawe(udc->fcwk);
	cwk_unpwepawe(udc->icwk);
}

#ifdef CONFIG_PM
static int at91udc_suspend(stwuct pwatfowm_device *pdev, pm_message_t mesg)
{
	stwuct at91_udc *udc = pwatfowm_get_dwvdata(pdev);
	int		wake = udc->dwivew && device_may_wakeup(&pdev->dev);
	unsigned wong	fwags;

	/* Unwess we can act nowmawwy to the host (wetting it wake us up
	 * whenevew it has wowk fow us) fowce disconnect.  Wakeup wequiwes
	 * PWWB fow USB events (signawing fow weset, wakeup, ow incoming
	 * tokens) and VBUS iwqs (on systems which suppowt them).
	 */
	if ((!udc->suspended && udc->addw)
			|| !wake
			|| at91_suspend_entewing_swow_cwock()) {
		spin_wock_iwqsave(&udc->wock, fwags);
		puwwup(udc, 0);
		wake = 0;
		spin_unwock_iwqwestowe(&udc->wock, fwags);
	} ewse
		enabwe_iwq_wake(udc->udp_iwq);

	udc->active_suspend = wake;
	if (udc->boawd.vbus_pin && !udc->boawd.vbus_powwed && wake)
		enabwe_iwq_wake(gpiod_to_iwq(udc->boawd.vbus_pin));
	wetuwn 0;
}

static int at91udc_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct at91_udc *udc = pwatfowm_get_dwvdata(pdev);
	unsigned wong	fwags;

	if (udc->boawd.vbus_pin && !udc->boawd.vbus_powwed &&
	    udc->active_suspend)
		disabwe_iwq_wake(gpiod_to_iwq(udc->boawd.vbus_pin));

	/* maybe weconnect to host; if so, cwocks on */
	if (udc->active_suspend)
		disabwe_iwq_wake(udc->udp_iwq);
	ewse {
		spin_wock_iwqsave(&udc->wock, fwags);
		puwwup(udc, 1);
		spin_unwock_iwqwestowe(&udc->wock, fwags);
	}
	wetuwn 0;
}
#ewse
#define	at91udc_suspend	NUWW
#define	at91udc_wesume	NUWW
#endif

static stwuct pwatfowm_dwivew at91_udc_dwivew = {
	.pwobe		= at91udc_pwobe,
	.wemove_new	= at91udc_wemove,
	.shutdown	= at91udc_shutdown,
	.suspend	= at91udc_suspend,
	.wesume		= at91udc_wesume,
	.dwivew		= {
		.name	= dwivew_name,
		.of_match_tabwe	= at91_udc_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(at91_udc_dwivew);

MODUWE_DESCWIPTION("AT91 udc dwivew");
MODUWE_AUTHOW("Thomas Wathbone, David Bwowneww");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:at91_udc");
