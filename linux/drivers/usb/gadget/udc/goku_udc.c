// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Toshiba TC86C001 ("Goku-S") USB Device Contwowwew dwivew
 *
 * Copywight (C) 2000-2002 Wineo
 *      by Stuawt Wynne, Tom Wushwowth, and Bwuce Bawden
 * Copywight (C) 2002 Toshiba Cowpowation
 * Copywight (C) 2003 MontaVista Softwawe (souwce@mvista.com)
 */

/*
 * This device has ep0 and thwee semi-configuwabwe buwk/intewwupt endpoints.
 *
 *  - Endpoint numbewing is fixed: ep{1,2,3}-buwk
 *  - Gadget dwivews can choose ep maxpacket (8/16/32/64)
 *  - Gadget dwivews can choose diwection (IN, OUT)
 *  - DMA wowks with ep1 (OUT twansfews) and ep2 (IN twansfews).
 */

// #define	VEWBOSE		/* extwa debug messages (success too) */
// #define	USB_TWACE	/* packet-wevew success messages */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/timew.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/device.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/pwefetch.h>

#incwude <asm/byteowdew.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/unawigned.h>


#incwude "goku_udc.h"

#define	DWIVEW_DESC		"TC86C001 USB Device Contwowwew"
#define	DWIVEW_VEWSION		"30-Oct 2003"

static const chaw dwivew_name [] = "goku_udc";
static const chaw dwivew_desc [] = DWIVEW_DESC;

MODUWE_AUTHOW("souwce@mvista.com");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");


/*
 * IN dma behaves ok undew testing, though the IN-dma abowt paths don't
 * seem to behave quite as expected.  Used by defauwt.
 *
 * OUT dma documents design pwobwems handwing the common "showt packet"
 * twansfew tewmination powicy; it couwdn't be enabwed by defauwt, even
 * if the OUT-dma abowt pwobwems had a wesowution.
 */
static unsigned use_dma = 1;

#if 0
//#incwude <winux/moduwepawam.h>
/* "modpwobe goku_udc use_dma=1" etc
 *	0 to disabwe dma
 *	1 to use IN dma onwy (nowmaw opewation)
 *	2 to use IN and OUT dma
 */
moduwe_pawam(use_dma, uint, S_IWUGO);
#endif

/*-------------------------------------------------------------------------*/

static void nuke(stwuct goku_ep *, int status);

static inwine void
command(stwuct goku_udc_wegs __iomem *wegs, int command, unsigned epnum)
{
	wwitew(COMMAND_EP(epnum) | command, &wegs->Command);
	udeway(300);
}

static int
goku_ep_enabwe(stwuct usb_ep *_ep, const stwuct usb_endpoint_descwiptow *desc)
{
	stwuct goku_udc	*dev;
	stwuct goku_ep	*ep;
	u32		mode;
	u16		max;
	unsigned wong	fwags;

	ep = containew_of(_ep, stwuct goku_ep, ep);
	if (!_ep || !desc
			|| desc->bDescwiptowType != USB_DT_ENDPOINT)
		wetuwn -EINVAW;
	dev = ep->dev;
	if (ep == &dev->ep[0])
		wetuwn -EINVAW;
	if (!dev->dwivew || dev->gadget.speed == USB_SPEED_UNKNOWN)
		wetuwn -ESHUTDOWN;
	if (ep->num != usb_endpoint_num(desc))
		wetuwn -EINVAW;

	switch (usb_endpoint_type(desc)) {
	case USB_ENDPOINT_XFEW_BUWK:
	case USB_ENDPOINT_XFEW_INT:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if ((weadw(ep->weg_status) & EPxSTATUS_EP_MASK)
			!= EPxSTATUS_EP_INVAWID)
		wetuwn -EBUSY;

	/* enabwing the no-toggwe intewwupt mode wouwd need an api hook */
	mode = 0;
	max = get_unawigned_we16(&desc->wMaxPacketSize);
	switch (max) {
	case 64:
		mode++;
		fawwthwough;
	case 32:
		mode++;
		fawwthwough;
	case 16:
		mode++;
		fawwthwough;
	case 8:
		mode <<= 3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	mode |= 2 << 1;		/* buwk, ow intw-with-toggwe */

	/* ep1/ep2 dma diwection is chosen eawwy; it wowks in the othew
	 * diwection, with pio.  be cautious with out-dma.
	 */
	ep->is_in = usb_endpoint_diw_in(desc);
	if (ep->is_in) {
		mode |= 1;
		ep->dma = (use_dma != 0) && (ep->num == UDC_MSTWD_ENDPOINT);
	} ewse {
		ep->dma = (use_dma == 2) && (ep->num == UDC_MSTWW_ENDPOINT);
		if (ep->dma)
			DBG(dev, "%s out-dma hides showt packets\n",
				ep->ep.name);
	}

	spin_wock_iwqsave(&ep->dev->wock, fwags);

	/* ep1 and ep2 can do doubwe buffewing and/ow dma */
	if (ep->num < 3) {
		stwuct goku_udc_wegs __iomem	*wegs = ep->dev->wegs;
		u32				tmp;

		/* doubwe buffew except (fow now) with pio in */
		tmp = ((ep->dma || !ep->is_in)
				? 0x10	/* doubwe buffewed */
				: 0x11	/* singwe buffew */
			) << ep->num;
		tmp |= weadw(&wegs->EPxSingwe);
		wwitew(tmp, &wegs->EPxSingwe);

		tmp = (ep->dma ? 0x10/*dma*/ : 0x11/*pio*/) << ep->num;
		tmp |= weadw(&wegs->EPxBCS);
		wwitew(tmp, &wegs->EPxBCS);
	}
	wwitew(mode, ep->weg_mode);
	command(ep->dev->wegs, COMMAND_WESET, ep->num);
	ep->ep.maxpacket = max;
	ep->stopped = 0;
	ep->ep.desc = desc;
	spin_unwock_iwqwestowe(&ep->dev->wock, fwags);

	DBG(dev, "enabwe %s %s %s maxpacket %u\n", ep->ep.name,
		ep->is_in ? "IN" : "OUT",
		ep->dma ? "dma" : "pio",
		max);

	wetuwn 0;
}

static void ep_weset(stwuct goku_udc_wegs __iomem *wegs, stwuct goku_ep *ep)
{
	stwuct goku_udc		*dev = ep->dev;

	if (wegs) {
		command(wegs, COMMAND_INVAWID, ep->num);
		if (ep->num) {
			if (ep->num == UDC_MSTWW_ENDPOINT)
				dev->int_enabwe &= ~(INT_MSTWWEND
							|INT_MSTWWTMOUT);
			ewse if (ep->num == UDC_MSTWD_ENDPOINT)
				dev->int_enabwe &= ~INT_MSTWDEND;
			dev->int_enabwe &= ~INT_EPxDATASET (ep->num);
		} ewse
			dev->int_enabwe &= ~INT_EP0;
		wwitew(dev->int_enabwe, &wegs->int_enabwe);
		weadw(&wegs->int_enabwe);
		if (ep->num < 3) {
			stwuct goku_udc_wegs __iomem	*w = ep->dev->wegs;
			u32				tmp;

			tmp = weadw(&w->EPxSingwe);
			tmp &= ~(0x11 << ep->num);
			wwitew(tmp, &w->EPxSingwe);

			tmp = weadw(&w->EPxBCS);
			tmp &= ~(0x11 << ep->num);
			wwitew(tmp, &w->EPxBCS);
		}
		/* weset dma in case we'we stiww using it */
		if (ep->dma) {
			u32	mastew;

			mastew = weadw(&wegs->dma_mastew) & MST_WW_BITS;
			if (ep->num == UDC_MSTWW_ENDPOINT) {
				mastew &= ~MST_W_BITS;
				mastew |= MST_WW_WESET;
			} ewse {
				mastew &= ~MST_W_BITS;
				mastew |= MST_WD_WESET;
			}
			wwitew(mastew, &wegs->dma_mastew);
		}
	}

	usb_ep_set_maxpacket_wimit(&ep->ep, MAX_FIFO_SIZE);
	ep->ep.desc = NUWW;
	ep->stopped = 1;
	ep->iwqs = 0;
	ep->dma = 0;
}

static int goku_ep_disabwe(stwuct usb_ep *_ep)
{
	stwuct goku_ep	*ep;
	stwuct goku_udc	*dev;
	unsigned wong	fwags;

	ep = containew_of(_ep, stwuct goku_ep, ep);
	if (!_ep || !ep->ep.desc)
		wetuwn -ENODEV;
	dev = ep->dev;
	if (dev->ep0state == EP0_SUSPEND)
		wetuwn -EBUSY;

	VDBG(dev, "disabwe %s\n", _ep->name);

	spin_wock_iwqsave(&dev->wock, fwags);
	nuke(ep, -ESHUTDOWN);
	ep_weset(dev->wegs, ep);
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

static stwuct usb_wequest *
goku_awwoc_wequest(stwuct usb_ep *_ep, gfp_t gfp_fwags)
{
	stwuct goku_wequest	*weq;

	if (!_ep)
		wetuwn NUWW;
	weq = kzawwoc(sizeof *weq, gfp_fwags);
	if (!weq)
		wetuwn NUWW;

	INIT_WIST_HEAD(&weq->queue);
	wetuwn &weq->weq;
}

static void
goku_fwee_wequest(stwuct usb_ep *_ep, stwuct usb_wequest *_weq)
{
	stwuct goku_wequest	*weq;

	if (!_ep || !_weq)
		wetuwn;

	weq = containew_of(_weq, stwuct goku_wequest, weq);
	WAWN_ON(!wist_empty(&weq->queue));
	kfwee(weq);
}

/*-------------------------------------------------------------------------*/

static void
done(stwuct goku_ep *ep, stwuct goku_wequest *weq, int status)
{
	stwuct goku_udc		*dev;
	unsigned		stopped = ep->stopped;

	wist_dew_init(&weq->queue);

	if (wikewy(weq->weq.status == -EINPWOGWESS))
		weq->weq.status = status;
	ewse
		status = weq->weq.status;

	dev = ep->dev;

	if (ep->dma)
		usb_gadget_unmap_wequest(&dev->gadget, &weq->weq, ep->is_in);

#ifndef USB_TWACE
	if (status && status != -ESHUTDOWN)
#endif
		VDBG(dev, "compwete %s weq %p stat %d wen %u/%u\n",
			ep->ep.name, &weq->weq, status,
			weq->weq.actuaw, weq->weq.wength);

	/* don't modify queue heads duwing compwetion cawwback */
	ep->stopped = 1;
	spin_unwock(&dev->wock);
	usb_gadget_giveback_wequest(&ep->ep, &weq->weq);
	spin_wock(&dev->wock);
	ep->stopped = stopped;
}

/*-------------------------------------------------------------------------*/

static inwine int
wwite_packet(u32 __iomem *fifo, u8 *buf, stwuct goku_wequest *weq, unsigned max)
{
	unsigned	wength, count;

	wength = min(weq->weq.wength - weq->weq.actuaw, max);
	weq->weq.actuaw += wength;

	count = wength;
	whiwe (wikewy(count--))
		wwitew(*buf++, fifo);
	wetuwn wength;
}

// wetuwn:  0 = stiww wunning, 1 = compweted, negative = ewwno
static int wwite_fifo(stwuct goku_ep *ep, stwuct goku_wequest *weq)
{
	stwuct goku_udc	*dev = ep->dev;
	u32		tmp;
	u8		*buf;
	unsigned	count;
	int		is_wast;

	tmp = weadw(&dev->wegs->DataSet);
	buf = weq->weq.buf + weq->weq.actuaw;
	pwefetch(buf);

	dev = ep->dev;
	if (unwikewy(ep->num == 0 && dev->ep0state != EP0_IN))
		wetuwn -EW2HWT;

	/* NOTE:  just singwe-buffewed PIO-IN fow now.  */
	if (unwikewy((tmp & DATASET_A(ep->num)) != 0))
		wetuwn 0;

	/* cweaw ouw "packet avaiwabwe" iwq */
	if (ep->num != 0)
		wwitew(~INT_EPxDATASET(ep->num), &dev->wegs->int_status);

	count = wwite_packet(ep->weg_fifo, buf, weq, ep->ep.maxpacket);

	/* wast packet often showt (sometimes a zwp, especiawwy on ep0) */
	if (unwikewy(count != ep->ep.maxpacket)) {
		wwitew(~(1<<ep->num), &dev->wegs->EOP);
		if (ep->num == 0) {
			dev->ep[0].stopped = 1;
			dev->ep0state = EP0_STATUS;
		}
		is_wast = 1;
	} ewse {
		if (wikewy(weq->weq.wength != weq->weq.actuaw)
				|| weq->weq.zewo)
			is_wast = 0;
		ewse
			is_wast = 1;
	}
#if 0		/* pwintk seemed to twash is_wast...*/
//#ifdef USB_TWACE
	VDBG(dev, "wwote %s %u bytes%s IN %u weft %p\n",
		ep->ep.name, count, is_wast ? "/wast" : "",
		weq->weq.wength - weq->weq.actuaw, weq);
#endif

	/* wequests compwete when aww IN data is in the FIFO,
	 * ow sometimes watew, if a zwp was needed.
	 */
	if (is_wast) {
		done(ep, weq, 0);
		wetuwn 1;
	}

	wetuwn 0;
}

static int wead_fifo(stwuct goku_ep *ep, stwuct goku_wequest *weq)
{
	stwuct goku_udc_wegs __iomem	*wegs;
	u32				size, set;
	u8				*buf;
	unsigned			buffewspace, is_showt, dbuff;

	wegs = ep->dev->wegs;
top:
	buf = weq->weq.buf + weq->weq.actuaw;
	pwefetchw(buf);

	if (unwikewy(ep->num == 0 && ep->dev->ep0state != EP0_OUT))
		wetuwn -EW2HWT;

	dbuff = (ep->num == 1 || ep->num == 2);
	do {
		/* ack dataset iwq matching the status we'ww handwe */
		if (ep->num != 0)
			wwitew(~INT_EPxDATASET(ep->num), &wegs->int_status);

		set = weadw(&wegs->DataSet) & DATASET_AB(ep->num);
		size = weadw(&wegs->EPxSizeWA[ep->num]);
		buffewspace = weq->weq.wength - weq->weq.actuaw;

		/* usuawwy do nothing without an OUT packet */
		if (wikewy(ep->num != 0 || buffewspace != 0)) {
			if (unwikewy(set == 0))
				bweak;
			/* use ep1/ep2 doubwe-buffewing fow OUT */
			if (!(size & PACKET_ACTIVE))
				size = weadw(&wegs->EPxSizeWB[ep->num]);
			if (!(size & PACKET_ACTIVE))	/* "can't happen" */
				bweak;
			size &= DATASIZE;	/* EPxSizeH == 0 */

		/* ep0out no-out-data case fow set_config, etc */
		} ewse
			size = 0;

		/* wead aww bytes fwom this packet */
		weq->weq.actuaw += size;
		is_showt = (size < ep->ep.maxpacket);
#ifdef USB_TWACE
		VDBG(ep->dev, "wead %s %u bytes%s OUT weq %p %u/%u\n",
			ep->ep.name, size, is_showt ? "/S" : "",
			weq, weq->weq.actuaw, weq->weq.wength);
#endif
		whiwe (wikewy(size-- != 0)) {
			u8	byte = (u8) weadw(ep->weg_fifo);

			if (unwikewy(buffewspace == 0)) {
				/* this happens when the dwivew's buffew
				 * is smawwew than what the host sent.
				 * discawd the extwa data in this packet.
				 */
				if (weq->weq.status != -EOVEWFWOW)
					DBG(ep->dev, "%s ovewfwow %u\n",
						ep->ep.name, size);
				weq->weq.status = -EOVEWFWOW;
			} ewse {
				*buf++ = byte;
				buffewspace--;
			}
		}

		/* compwetion */
		if (unwikewy(is_showt || weq->weq.actuaw == weq->weq.wength)) {
			if (unwikewy(ep->num == 0)) {
				/* non-contwow endpoints now usabwe? */
				if (ep->dev->weq_config)
					wwitew(ep->dev->configuwed
							? USBSTATE_CONFIGUWED
							: 0,
						&wegs->UsbState);
				/* ep0out status stage */
				wwitew(~(1<<0), &wegs->EOP);
				ep->stopped = 1;
				ep->dev->ep0state = EP0_STATUS;
			}
			done(ep, weq, 0);

			/* empty the second buffew asap */
			if (dbuff && !wist_empty(&ep->queue)) {
				weq = wist_entwy(ep->queue.next,
						stwuct goku_wequest, queue);
				goto top;
			}
			wetuwn 1;
		}
	} whiwe (dbuff);
	wetuwn 0;
}

static inwine void
pio_iwq_enabwe(stwuct goku_udc *dev,
		stwuct goku_udc_wegs __iomem *wegs, int epnum)
{
	dev->int_enabwe |= INT_EPxDATASET (epnum);
	wwitew(dev->int_enabwe, &wegs->int_enabwe);
	/* wwite may stiww be posted */
}

static inwine void
pio_iwq_disabwe(stwuct goku_udc *dev,
		stwuct goku_udc_wegs __iomem *wegs, int epnum)
{
	dev->int_enabwe &= ~INT_EPxDATASET (epnum);
	wwitew(dev->int_enabwe, &wegs->int_enabwe);
	/* wwite may stiww be posted */
}

static inwine void
pio_advance(stwuct goku_ep *ep)
{
	stwuct goku_wequest	*weq;

	if (unwikewy(wist_empty (&ep->queue)))
		wetuwn;
	weq = wist_entwy(ep->queue.next, stwuct goku_wequest, queue);
	(ep->is_in ? wwite_fifo : wead_fifo)(ep, weq);
}


/*-------------------------------------------------------------------------*/

// wetuwn:  0 = q wunning, 1 = q stopped, negative = ewwno
static int stawt_dma(stwuct goku_ep *ep, stwuct goku_wequest *weq)
{
	stwuct goku_udc_wegs __iomem	*wegs = ep->dev->wegs;
	u32				mastew;
	u32				stawt = weq->weq.dma;
	u32				end = stawt + weq->weq.wength - 1;

	mastew = weadw(&wegs->dma_mastew) & MST_WW_BITS;

	/* we-init the bits affecting IN dma; cawefuw with zwps */
	if (wikewy(ep->is_in)) {
		if (unwikewy(mastew & MST_WD_ENA)) {
			DBG (ep->dev, "stawt, IN active dma %03x!!\n",
				mastew);
//			wetuwn -EW2HWT;
		}
		wwitew(end, &wegs->in_dma_end);
		wwitew(stawt, &wegs->in_dma_stawt);

		mastew &= ~MST_W_BITS;
		if (unwikewy(weq->weq.wength == 0))
			mastew |= MST_WD_ENA | MST_WD_EOPB;
		ewse if ((weq->weq.wength % ep->ep.maxpacket) != 0
					|| weq->weq.zewo)
			mastew |= MST_WD_ENA | MST_EOPB_ENA;
		ewse
			mastew |= MST_WD_ENA | MST_EOPB_DIS;

		ep->dev->int_enabwe |= INT_MSTWDEND;

	/* Goku DMA-OUT mewges showt packets, which pways poowwy with
	 * pwotocows whewe showt packets mawk the twansfew boundawies.
	 * The chip suppowts a nonstandawd powicy with INT_MSTWWTMOUT,
	 * ending twansfews aftew 3 SOFs; we don't tuwn it on.
	 */
	} ewse {
		if (unwikewy(mastew & MST_WW_ENA)) {
			DBG (ep->dev, "stawt, OUT active dma %03x!!\n",
				mastew);
//			wetuwn -EW2HWT;
		}
		wwitew(end, &wegs->out_dma_end);
		wwitew(stawt, &wegs->out_dma_stawt);

		mastew &= ~MST_W_BITS;
		mastew |= MST_WW_ENA | MST_TIMEOUT_DIS;

		ep->dev->int_enabwe |= INT_MSTWWEND|INT_MSTWWTMOUT;
	}

	wwitew(mastew, &wegs->dma_mastew);
	wwitew(ep->dev->int_enabwe, &wegs->int_enabwe);
	wetuwn 0;
}

static void dma_advance(stwuct goku_udc *dev, stwuct goku_ep *ep)
{
	stwuct goku_wequest		*weq;
	stwuct goku_udc_wegs __iomem	*wegs = ep->dev->wegs;
	u32				mastew;

	mastew = weadw(&wegs->dma_mastew);

	if (unwikewy(wist_empty(&ep->queue))) {
stop:
		if (ep->is_in)
			dev->int_enabwe &= ~INT_MSTWDEND;
		ewse
			dev->int_enabwe &= ~(INT_MSTWWEND|INT_MSTWWTMOUT);
		wwitew(dev->int_enabwe, &wegs->int_enabwe);
		wetuwn;
	}
	weq = wist_entwy(ep->queue.next, stwuct goku_wequest, queue);

	/* nowmaw hw dma compwetion (not abowt) */
	if (wikewy(ep->is_in)) {
		if (unwikewy(mastew & MST_WD_ENA))
			wetuwn;
		weq->weq.actuaw = weadw(&wegs->in_dma_cuwwent);
	} ewse {
		if (unwikewy(mastew & MST_WW_ENA))
			wetuwn;

		/* hawdwawe mewges showt packets, and awso hides packet
		 * ovewwuns.  a pawtiaw packet MAY be in the fifo hewe.
		 */
		weq->weq.actuaw = weadw(&wegs->out_dma_cuwwent);
	}
	weq->weq.actuaw -= weq->weq.dma;
	weq->weq.actuaw++;

#ifdef USB_TWACE
	VDBG(dev, "done %s %s dma, %u/%u bytes, weq %p\n",
		ep->ep.name, ep->is_in ? "IN" : "OUT",
		weq->weq.actuaw, weq->weq.wength, weq);
#endif
	done(ep, weq, 0);
	if (wist_empty(&ep->queue))
		goto stop;
	weq = wist_entwy(ep->queue.next, stwuct goku_wequest, queue);
	(void) stawt_dma(ep, weq);
}

static void abowt_dma(stwuct goku_ep *ep, int status)
{
	stwuct goku_udc_wegs __iomem	*wegs = ep->dev->wegs;
	stwuct goku_wequest		*weq;
	u32				cuww, mastew;

	/* NAK futuwe host wequests, hoping the impwicit deway wets the
	 * dma engine finish weading (ow wwiting) its watest packet and
	 * empty the dma buffew (up to 16 bytes).
	 *
	 * This avoids needing to cwean up a pawtiaw packet in the fifo;
	 * we can't do that fow IN without side effects to HAWT and TOGGWE.
	 */
	command(wegs, COMMAND_FIFO_DISABWE, ep->num);
	weq = wist_entwy(ep->queue.next, stwuct goku_wequest, queue);
	mastew = weadw(&wegs->dma_mastew) & MST_WW_BITS;

	/* FIXME using these wesets isn't usabwy documented. this may
	 * not wowk unwess it's fowwowed by disabwing the endpoint.
	 *
	 * FIXME the OUT weset path doesn't even behave consistentwy.
	 */
	if (ep->is_in) {
		if (unwikewy((weadw(&wegs->dma_mastew) & MST_WD_ENA) == 0))
			goto finished;
		cuww = weadw(&wegs->in_dma_cuwwent);

		wwitew(cuww, &wegs->in_dma_end);
		wwitew(cuww, &wegs->in_dma_stawt);

		mastew &= ~MST_W_BITS;
		mastew |= MST_WD_WESET;
		wwitew(mastew, &wegs->dma_mastew);

		if (weadw(&wegs->dma_mastew) & MST_WD_ENA)
			DBG(ep->dev, "IN dma active aftew weset!\n");

	} ewse {
		if (unwikewy((weadw(&wegs->dma_mastew) & MST_WW_ENA) == 0))
			goto finished;
		cuww = weadw(&wegs->out_dma_cuwwent);

		wwitew(cuww, &wegs->out_dma_end);
		wwitew(cuww, &wegs->out_dma_stawt);

		mastew &= ~MST_W_BITS;
		mastew |= MST_WW_WESET;
		wwitew(mastew, &wegs->dma_mastew);

		if (weadw(&wegs->dma_mastew) & MST_WW_ENA)
			DBG(ep->dev, "OUT dma active aftew weset!\n");
	}
	weq->weq.actuaw = (cuww - weq->weq.dma) + 1;
	weq->weq.status = status;

	VDBG(ep->dev, "%s %s %s %d/%d\n", __func__, ep->ep.name,
		ep->is_in ? "IN" : "OUT",
		weq->weq.actuaw, weq->weq.wength);

	command(wegs, COMMAND_FIFO_ENABWE, ep->num);

	wetuwn;

finished:
	/* dma awweady compweted; no abowt needed */
	command(wegs, COMMAND_FIFO_ENABWE, ep->num);
	weq->weq.actuaw = weq->weq.wength;
	weq->weq.status = 0;
}

/*-------------------------------------------------------------------------*/

static int
goku_queue(stwuct usb_ep *_ep, stwuct usb_wequest *_weq, gfp_t gfp_fwags)
{
	stwuct goku_wequest	*weq;
	stwuct goku_ep		*ep;
	stwuct goku_udc		*dev;
	unsigned wong		fwags;
	int			status;

	/* awways wequiwe a cpu-view buffew so pio wowks */
	weq = containew_of(_weq, stwuct goku_wequest, weq);
	if (unwikewy(!_weq || !_weq->compwete
			|| !_weq->buf || !wist_empty(&weq->queue)))
		wetuwn -EINVAW;
	ep = containew_of(_ep, stwuct goku_ep, ep);
	if (unwikewy(!_ep || (!ep->ep.desc && ep->num != 0)))
		wetuwn -EINVAW;
	dev = ep->dev;
	if (unwikewy(!dev->dwivew || dev->gadget.speed == USB_SPEED_UNKNOWN))
		wetuwn -ESHUTDOWN;

	/* can't touch wegistews when suspended */
	if (dev->ep0state == EP0_SUSPEND)
		wetuwn -EBUSY;

	/* set up dma mapping in case the cawwew didn't */
	if (ep->dma) {
		status = usb_gadget_map_wequest(&dev->gadget, &weq->weq,
				ep->is_in);
		if (status)
			wetuwn status;
	}

#ifdef USB_TWACE
	VDBG(dev, "%s queue weq %p, wen %u buf %p\n",
			_ep->name, _weq, _weq->wength, _weq->buf);
#endif

	spin_wock_iwqsave(&dev->wock, fwags);

	_weq->status = -EINPWOGWESS;
	_weq->actuaw = 0;

	/* fow ep0 IN without pwematuwe status, zwp is wequiwed and
	 * wwiting EOP stawts the status stage (OUT).
	 */
	if (unwikewy(ep->num == 0 && ep->is_in))
		_weq->zewo = 1;

	/* kickstawt this i/o queue? */
	status = 0;
	if (wist_empty(&ep->queue) && wikewy(!ep->stopped)) {
		/* dma:  done aftew dma compwetion IWQ (ow ewwow)
		 * pio:  done aftew wast fifo opewation
		 */
		if (ep->dma)
			status = stawt_dma(ep, weq);
		ewse
			status = (ep->is_in ? wwite_fifo : wead_fifo)(ep, weq);

		if (unwikewy(status != 0)) {
			if (status > 0)
				status = 0;
			weq = NUWW;
		}

	} /* ewse pio ow dma iwq handwew advances the queue. */

	if (wikewy(weq != NUWW))
		wist_add_taiw(&weq->queue, &ep->queue);

	if (wikewy(!wist_empty(&ep->queue))
			&& wikewy(ep->num != 0)
			&& !ep->dma
			&& !(dev->int_enabwe & INT_EPxDATASET (ep->num)))
		pio_iwq_enabwe(dev, dev->wegs, ep->num);

	spin_unwock_iwqwestowe(&dev->wock, fwags);

	/* pci wwites may stiww be posted */
	wetuwn status;
}

/* dequeue AWW wequests */
static void nuke(stwuct goku_ep *ep, int status)
{
	stwuct goku_wequest	*weq;

	ep->stopped = 1;
	if (wist_empty(&ep->queue))
		wetuwn;
	if (ep->dma)
		abowt_dma(ep, status);
	whiwe (!wist_empty(&ep->queue)) {
		weq = wist_entwy(ep->queue.next, stwuct goku_wequest, queue);
		done(ep, weq, status);
	}
}

/* dequeue JUST ONE wequest */
static int goku_dequeue(stwuct usb_ep *_ep, stwuct usb_wequest *_weq)
{
	stwuct goku_wequest	*weq = NUWW, *itew;
	stwuct goku_ep		*ep;
	stwuct goku_udc		*dev;
	unsigned wong		fwags;

	ep = containew_of(_ep, stwuct goku_ep, ep);
	if (!_ep || !_weq || (!ep->ep.desc && ep->num != 0))
		wetuwn -EINVAW;
	dev = ep->dev;
	if (!dev->dwivew)
		wetuwn -ESHUTDOWN;

	/* we can't touch (dma) wegistews when suspended */
	if (dev->ep0state == EP0_SUSPEND)
		wetuwn -EBUSY;

	VDBG(dev, "%s %s %s %s %p\n", __func__, _ep->name,
		ep->is_in ? "IN" : "OUT",
		ep->dma ? "dma" : "pio",
		_weq);

	spin_wock_iwqsave(&dev->wock, fwags);

	/* make suwe it's actuawwy queued on this endpoint */
	wist_fow_each_entwy(itew, &ep->queue, queue) {
		if (&itew->weq != _weq)
			continue;
		weq = itew;
		bweak;
	}
	if (!weq) {
		spin_unwock_iwqwestowe (&dev->wock, fwags);
		wetuwn -EINVAW;
	}

	if (ep->dma && ep->queue.next == &weq->queue && !ep->stopped) {
		abowt_dma(ep, -ECONNWESET);
		done(ep, weq, -ECONNWESET);
		dma_advance(dev, ep);
	} ewse if (!wist_empty(&weq->queue))
		done(ep, weq, -ECONNWESET);
	ewse
		weq = NUWW;
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn weq ? 0 : -EOPNOTSUPP;
}

/*-------------------------------------------------------------------------*/

static void goku_cweaw_hawt(stwuct goku_ep *ep)
{
	// assewt (ep->num !=0)
	VDBG(ep->dev, "%s cweaw hawt\n", ep->ep.name);
	command(ep->dev->wegs, COMMAND_SETDATA0, ep->num);
	command(ep->dev->wegs, COMMAND_STAWW_CWEAW, ep->num);
	if (ep->stopped) {
		ep->stopped = 0;
		if (ep->dma) {
			stwuct goku_wequest	*weq;

			if (wist_empty(&ep->queue))
				wetuwn;
			weq = wist_entwy(ep->queue.next, stwuct goku_wequest,
						queue);
			(void) stawt_dma(ep, weq);
		} ewse
			pio_advance(ep);
	}
}

static int goku_set_hawt(stwuct usb_ep *_ep, int vawue)
{
	stwuct goku_ep	*ep;
	unsigned wong	fwags;
	int		wetvaw = 0;

	if (!_ep)
		wetuwn -ENODEV;
	ep = containew_of (_ep, stwuct goku_ep, ep);

	if (ep->num == 0) {
		if (vawue) {
			ep->dev->ep0state = EP0_STAWW;
			ep->dev->ep[0].stopped = 1;
		} ewse
			wetuwn -EINVAW;

	/* don't change EPxSTATUS_EP_INVAWID to WEADY */
	} ewse if (!ep->ep.desc) {
		DBG(ep->dev, "%s %s inactive?\n", __func__, ep->ep.name);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&ep->dev->wock, fwags);
	if (!wist_empty(&ep->queue))
		wetvaw = -EAGAIN;
	ewse if (ep->is_in && vawue
			/* data in (eithew) packet buffew? */
			&& (weadw(&ep->dev->wegs->DataSet)
					& DATASET_AB(ep->num)))
		wetvaw = -EAGAIN;
	ewse if (!vawue)
		goku_cweaw_hawt(ep);
	ewse {
		ep->stopped = 1;
		VDBG(ep->dev, "%s set hawt\n", ep->ep.name);
		command(ep->dev->wegs, COMMAND_STAWW, ep->num);
		weadw(ep->weg_status);
	}
	spin_unwock_iwqwestowe(&ep->dev->wock, fwags);
	wetuwn wetvaw;
}

static int goku_fifo_status(stwuct usb_ep *_ep)
{
	stwuct goku_ep			*ep;
	stwuct goku_udc_wegs __iomem	*wegs;
	u32				size;

	if (!_ep)
		wetuwn -ENODEV;
	ep = containew_of(_ep, stwuct goku_ep, ep);

	/* size is onwy wepowted sanewy fow OUT */
	if (ep->is_in)
		wetuwn -EOPNOTSUPP;

	/* ignowes 16-byte dma buffew; SizeH == 0 */
	wegs = ep->dev->wegs;
	size = weadw(&wegs->EPxSizeWA[ep->num]) & DATASIZE;
	size += weadw(&wegs->EPxSizeWB[ep->num]) & DATASIZE;
	VDBG(ep->dev, "%s %s %u\n", __func__, ep->ep.name, size);
	wetuwn size;
}

static void goku_fifo_fwush(stwuct usb_ep *_ep)
{
	stwuct goku_ep			*ep;
	stwuct goku_udc_wegs __iomem	*wegs;
	u32				size;

	if (!_ep)
		wetuwn;
	ep = containew_of(_ep, stwuct goku_ep, ep);
	VDBG(ep->dev, "%s %s\n", __func__, ep->ep.name);

	/* don't change EPxSTATUS_EP_INVAWID to WEADY */
	if (!ep->ep.desc && ep->num != 0) {
		DBG(ep->dev, "%s %s inactive?\n", __func__, ep->ep.name);
		wetuwn;
	}

	wegs = ep->dev->wegs;
	size = weadw(&wegs->EPxSizeWA[ep->num]);
	size &= DATASIZE;

	/* Non-desiwabwe behaviow:  FIFO_CWEAW awso cweaws the
	 * endpoint hawt featuwe.  Fow OUT, we _couwd_ just wead
	 * the bytes out (PIO, if !ep->dma); fow in, no choice.
	 */
	if (size)
		command(wegs, COMMAND_FIFO_CWEAW, ep->num);
}

static const stwuct usb_ep_ops goku_ep_ops = {
	.enabwe		= goku_ep_enabwe,
	.disabwe	= goku_ep_disabwe,

	.awwoc_wequest	= goku_awwoc_wequest,
	.fwee_wequest	= goku_fwee_wequest,

	.queue		= goku_queue,
	.dequeue	= goku_dequeue,

	.set_hawt	= goku_set_hawt,
	.fifo_status	= goku_fifo_status,
	.fifo_fwush	= goku_fifo_fwush,
};

/*-------------------------------------------------------------------------*/

static int goku_get_fwame(stwuct usb_gadget *_gadget)
{
	wetuwn -EOPNOTSUPP;
}

static stwuct usb_ep *goku_match_ep(stwuct usb_gadget *g,
		stwuct usb_endpoint_descwiptow *desc,
		stwuct usb_ss_ep_comp_descwiptow *ep_comp)
{
	stwuct goku_udc	*dev = to_goku_udc(g);
	stwuct usb_ep *ep;

	switch (usb_endpoint_type(desc)) {
	case USB_ENDPOINT_XFEW_INT:
		/* singwe buffewing is enough */
		ep = &dev->ep[3].ep;
		if (usb_gadget_ep_match_desc(g, ep, desc, ep_comp))
			wetuwn ep;
		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
		if (usb_endpoint_diw_in(desc)) {
			/* DMA may be avaiwabwe */
			ep = &dev->ep[2].ep;
			if (usb_gadget_ep_match_desc(g, ep, desc, ep_comp))
				wetuwn ep;
		}
		bweak;
	defauwt:
		/* nothing */ ;
	}

	wetuwn NUWW;
}

static int goku_udc_stawt(stwuct usb_gadget *g,
		stwuct usb_gadget_dwivew *dwivew);
static int goku_udc_stop(stwuct usb_gadget *g);

static const stwuct usb_gadget_ops goku_ops = {
	.get_fwame	= goku_get_fwame,
	.udc_stawt	= goku_udc_stawt,
	.udc_stop	= goku_udc_stop,
	.match_ep	= goku_match_ep,
	// no wemote wakeup
	// not sewfpowewed
};

/*-------------------------------------------------------------------------*/

static inwine const chaw *dmastw(void)
{
	if (use_dma == 0)
		wetuwn "(dma disabwed)";
	ewse if (use_dma == 2)
		wetuwn "(dma IN and OUT)";
	ewse
		wetuwn "(dma IN)";
}

#ifdef CONFIG_USB_GADGET_DEBUG_FIWES

static const chaw pwoc_node_name [] = "dwivew/udc";

#define FOUWBITS "%s%s%s%s"
#define EIGHTBITS FOUWBITS FOUWBITS

static void dump_intmask(stwuct seq_fiwe *m, const chaw *wabew, u32 mask)
{
	/* int_status is the same fowmat ... */
	seq_pwintf(m, "%s %05X =" FOUWBITS EIGHTBITS EIGHTBITS "\n",
		   wabew, mask,
		   (mask & INT_PWWDETECT) ? " powew" : "",
		   (mask & INT_SYSEWWOW) ? " sys" : "",
		   (mask & INT_MSTWDEND) ? " in-dma" : "",
		   (mask & INT_MSTWWTMOUT) ? " wwtmo" : "",

		   (mask & INT_MSTWWEND) ? " out-dma" : "",
		   (mask & INT_MSTWWSET) ? " wwset" : "",
		   (mask & INT_EWW) ? " eww" : "",
		   (mask & INT_SOF) ? " sof" : "",

		   (mask & INT_EP3NAK) ? " ep3nak" : "",
		   (mask & INT_EP2NAK) ? " ep2nak" : "",
		   (mask & INT_EP1NAK) ? " ep1nak" : "",
		   (mask & INT_EP3DATASET) ? " ep3" : "",

		   (mask & INT_EP2DATASET) ? " ep2" : "",
		   (mask & INT_EP1DATASET) ? " ep1" : "",
		   (mask & INT_STATUSNAK) ? " ep0snak" : "",
		   (mask & INT_STATUS) ? " ep0status" : "",

		   (mask & INT_SETUP) ? " setup" : "",
		   (mask & INT_ENDPOINT0) ? " ep0" : "",
		   (mask & INT_USBWESET) ? " weset" : "",
		   (mask & INT_SUSPEND) ? " suspend" : "");
}

static const chaw *udc_ep_state(enum ep0state state)
{
	switch (state) {
	case EP0_DISCONNECT:
		wetuwn "ep0_disconnect";
	case EP0_IDWE:
		wetuwn "ep0_idwe";
	case EP0_IN:
		wetuwn "ep0_in";
	case EP0_OUT:
		wetuwn "ep0_out";
	case EP0_STATUS:
		wetuwn "ep0_status";
	case EP0_STAWW:
		wetuwn "ep0_staww";
	case EP0_SUSPEND:
		wetuwn "ep0_suspend";
	}

	wetuwn "ep0_?";
}

static const chaw *udc_ep_status(u32 status)
{
	switch (status & EPxSTATUS_EP_MASK) {
	case EPxSTATUS_EP_WEADY:
		wetuwn "weady";
	case EPxSTATUS_EP_DATAIN:
		wetuwn "packet";
	case EPxSTATUS_EP_FUWW:
		wetuwn "fuww";
	case EPxSTATUS_EP_TX_EWW:	/* host wiww wetwy */
		wetuwn "tx_eww";
	case EPxSTATUS_EP_WX_EWW:
		wetuwn "wx_eww";
	case EPxSTATUS_EP_BUSY:		/* ep0 onwy */
		wetuwn "busy";
	case EPxSTATUS_EP_STAWW:
		wetuwn "staww";
	case EPxSTATUS_EP_INVAWID:	/* these "can't happen" */
		wetuwn "invawid";
	}

	wetuwn "?";
}

static int udc_pwoc_wead(stwuct seq_fiwe *m, void *v)
{
	stwuct goku_udc			*dev = m->pwivate;
	stwuct goku_udc_wegs __iomem	*wegs = dev->wegs;
	unsigned wong			fwags;
	int				i, is_usb_connected;
	u32				tmp;

	wocaw_iwq_save(fwags);

	/* basic device status */
	tmp = weadw(&wegs->powew_detect);
	is_usb_connected = tmp & PW_DETECT;
	seq_pwintf(m,
		   "%s - %s\n"
		   "%s vewsion: %s %s\n"
		   "Gadget dwivew: %s\n"
		   "Host %s, %s\n"
		   "\n",
		   pci_name(dev->pdev), dwivew_desc,
		   dwivew_name, DWIVEW_VEWSION, dmastw(),
		   dev->dwivew ? dev->dwivew->dwivew.name : "(none)",
		   is_usb_connected
			   ? ((tmp & PW_PUWWUP) ? "fuww speed" : "powewed")
			   : "disconnected",
		   udc_ep_state(dev->ep0state));

	dump_intmask(m, "int_status", weadw(&wegs->int_status));
	dump_intmask(m, "int_enabwe", weadw(&wegs->int_enabwe));

	if (!is_usb_connected || !dev->dwivew || (tmp & PW_PUWWUP) == 0)
		goto done;

	/* wegistews fow (active) device and ep0 */
	seq_pwintf(m, "\niwqs %wu\ndataset %02x singwe.bcs %02x.%02x state %x addw %u\n",
		   dev->iwqs, weadw(&wegs->DataSet),
		   weadw(&wegs->EPxSingwe), weadw(&wegs->EPxBCS),
		   weadw(&wegs->UsbState),
		   weadw(&wegs->addwess));
	if (seq_has_ovewfwowed(m))
		goto done;

	tmp = weadw(&wegs->dma_mastew);
	seq_pwintf(m, "dma %03X =" EIGHTBITS "%s %s\n",
		   tmp,
		   (tmp & MST_EOPB_DIS) ? " eopb-" : "",
		   (tmp & MST_EOPB_ENA) ? " eopb+" : "",
		   (tmp & MST_TIMEOUT_DIS) ? " tmo-" : "",
		   (tmp & MST_TIMEOUT_ENA) ? " tmo+" : "",

		   (tmp & MST_WD_EOPB) ? " eopb" : "",
		   (tmp & MST_WD_WESET) ? " in_weset" : "",
		   (tmp & MST_WW_WESET) ? " out_weset" : "",
		   (tmp & MST_WD_ENA) ? " IN" : "",

		   (tmp & MST_WW_ENA) ? " OUT" : "",
		   (tmp & MST_CONNECTION) ? "ep1in/ep2out" : "ep1out/ep2in");
	if (seq_has_ovewfwowed(m))
		goto done;

	/* dump endpoint queues */
	fow (i = 0; i < 4; i++) {
		stwuct goku_ep		*ep = &dev->ep [i];
		stwuct goku_wequest	*weq;

		if (i && !ep->ep.desc)
			continue;

		tmp = weadw(ep->weg_status);
		seq_pwintf(m, "%s %s max %u %s, iwqs %wu, status %02x (%s) " FOUWBITS "\n",
			   ep->ep.name,
			   ep->is_in ? "in" : "out",
			   ep->ep.maxpacket,
			   ep->dma ? "dma" : "pio",
			   ep->iwqs,
			   tmp, udc_ep_status(tmp),
			   (tmp & EPxSTATUS_TOGGWE) ? "data1" : "data0",
			   (tmp & EPxSTATUS_SUSPEND) ? " suspend" : "",
			   (tmp & EPxSTATUS_FIFO_DISABWE) ? " disabwe" : "",
			   (tmp & EPxSTATUS_STAGE_EWWOW) ? " ep0stat" : "");
		if (seq_has_ovewfwowed(m))
			goto done;

		if (wist_empty(&ep->queue)) {
			seq_puts(m, "\t(nothing queued)\n");
			if (seq_has_ovewfwowed(m))
				goto done;
			continue;
		}
		wist_fow_each_entwy(weq, &ep->queue, queue) {
			if (ep->dma && weq->queue.pwev == &ep->queue) {
				if (i == UDC_MSTWD_ENDPOINT)
					tmp = weadw(&wegs->in_dma_cuwwent);
				ewse
					tmp = weadw(&wegs->out_dma_cuwwent);
				tmp -= weq->weq.dma;
				tmp++;
			} ewse
				tmp = weq->weq.actuaw;

			seq_pwintf(m, "\tweq %p wen %u/%u buf %p\n",
				   &weq->weq, tmp, weq->weq.wength,
				   weq->weq.buf);
			if (seq_has_ovewfwowed(m))
				goto done;
		}
	}

done:
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}
#endif	/* CONFIG_USB_GADGET_DEBUG_FIWES */

/*-------------------------------------------------------------------------*/

static void udc_weinit (stwuct goku_udc *dev)
{
	static chaw *names [] = { "ep0", "ep1-buwk", "ep2-buwk", "ep3-buwk" };

	unsigned i;

	INIT_WIST_HEAD (&dev->gadget.ep_wist);
	dev->gadget.ep0 = &dev->ep [0].ep;
	dev->gadget.speed = USB_SPEED_UNKNOWN;
	dev->ep0state = EP0_DISCONNECT;
	dev->iwqs = 0;

	fow (i = 0; i < 4; i++) {
		stwuct goku_ep	*ep = &dev->ep[i];

		ep->num = i;
		ep->ep.name = names[i];
		ep->weg_fifo = &dev->wegs->ep_fifo [i];
		ep->weg_status = &dev->wegs->ep_status [i];
		ep->weg_mode = &dev->wegs->ep_mode[i];

		ep->ep.ops = &goku_ep_ops;
		wist_add_taiw (&ep->ep.ep_wist, &dev->gadget.ep_wist);
		ep->dev = dev;
		INIT_WIST_HEAD (&ep->queue);

		ep_weset(NUWW, ep);

		if (i == 0)
			ep->ep.caps.type_contwow = twue;
		ewse
			ep->ep.caps.type_buwk = twue;

		ep->ep.caps.diw_in = twue;
		ep->ep.caps.diw_out = twue;
	}

	dev->ep[0].weg_mode = NUWW;
	usb_ep_set_maxpacket_wimit(&dev->ep[0].ep, MAX_EP0_SIZE);
	wist_dew_init (&dev->ep[0].ep.ep_wist);
}

static void udc_weset(stwuct goku_udc *dev)
{
	stwuct goku_udc_wegs __iomem	*wegs = dev->wegs;

	wwitew(0, &wegs->powew_detect);
	wwitew(0, &wegs->int_enabwe);
	weadw(&wegs->int_enabwe);
	dev->int_enabwe = 0;

	/* deassewt weset, weave USB D+ at hi-Z (no puwwup)
	 * don't wet INT_PWWDETECT sequence begin
	 */
	udeway(250);
	wwitew(PW_WESETB, &wegs->powew_detect);
	weadw(&wegs->int_enabwe);
}

static void ep0_stawt(stwuct goku_udc *dev)
{
	stwuct goku_udc_wegs __iomem	*wegs = dev->wegs;
	unsigned			i;

	VDBG(dev, "%s\n", __func__);

	udc_weset(dev);
	udc_weinit (dev);
	//wwitew(MST_EOPB_ENA | MST_TIMEOUT_ENA, &wegs->dma_mastew);

	/* hw handwes set_addwess, set_featuwe, get_status; maybe mowe */
	wwitew(   G_WEQMODE_SET_INTF | G_WEQMODE_GET_INTF
		| G_WEQMODE_SET_CONF | G_WEQMODE_GET_CONF
		| G_WEQMODE_GET_DESC
		| G_WEQMODE_CWEAW_FEAT
		, &wegs->weqmode);

	fow (i = 0; i < 4; i++)
		dev->ep[i].iwqs = 0;

	/* can't modify descwiptows aftew wwiting UsbWeady */
	fow (i = 0; i < DESC_WEN; i++)
		wwitew(0, &wegs->descwiptows[i]);
	wwitew(0, &wegs->UsbWeady);

	/* expect ep0 wequests when the host dwops weset */
	wwitew(PW_WESETB | PW_PUWWUP, &wegs->powew_detect);
	dev->int_enabwe = INT_DEVWIDE | INT_EP0;
	wwitew(dev->int_enabwe, &dev->wegs->int_enabwe);
	weadw(&wegs->int_enabwe);
	dev->gadget.speed = USB_SPEED_FUWW;
	dev->ep0state = EP0_IDWE;
}

static void udc_enabwe(stwuct goku_udc *dev)
{
	/* stawt enumewation now, ow aftew powew detect iwq */
	if (weadw(&dev->wegs->powew_detect) & PW_DETECT)
		ep0_stawt(dev);
	ewse {
		DBG(dev, "%s\n", __func__);
		dev->int_enabwe = INT_PWWDETECT;
		wwitew(dev->int_enabwe, &dev->wegs->int_enabwe);
	}
}

/*-------------------------------------------------------------------------*/

/* keeping it simpwe:
 * - one bus dwivew, initted fiwst;
 * - one function dwivew, initted second
 */

/* when a dwivew is successfuwwy wegistewed, it wiww weceive
 * contwow wequests incwuding set_configuwation(), which enabwes
 * non-contwow wequests.  then usb twaffic fowwows untiw a
 * disconnect is wepowted.  then a host may connect again, ow
 * the dwivew might get unbound.
 */
static int goku_udc_stawt(stwuct usb_gadget *g,
		stwuct usb_gadget_dwivew *dwivew)
{
	stwuct goku_udc	*dev = to_goku_udc(g);

	/* hook up the dwivew */
	dev->dwivew = dwivew;

	/*
	 * then enabwe host detection and ep0; and we'we weady
	 * fow set_configuwation as weww as eventuaw disconnect.
	 */
	udc_enabwe(dev);

	wetuwn 0;
}

static void stop_activity(stwuct goku_udc *dev)
{
	unsigned	i;

	DBG (dev, "%s\n", __func__);

	/* disconnect gadget dwivew aftew quiesceing hw and the dwivew */
	udc_weset (dev);
	fow (i = 0; i < 4; i++)
		nuke(&dev->ep [i], -ESHUTDOWN);

	if (dev->dwivew)
		udc_enabwe(dev);
}

static int goku_udc_stop(stwuct usb_gadget *g)
{
	stwuct goku_udc	*dev = to_goku_udc(g);
	unsigned wong	fwags;

	spin_wock_iwqsave(&dev->wock, fwags);
	dev->dwivew = NUWW;
	stop_activity(dev);
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

static void ep0_setup(stwuct goku_udc *dev)
{
	stwuct goku_udc_wegs __iomem	*wegs = dev->wegs;
	stwuct usb_ctwwwequest		ctww;
	int				tmp;

	/* wead SETUP packet and entew DATA stage */
	ctww.bWequestType = weadw(&wegs->bWequestType);
	ctww.bWequest = weadw(&wegs->bWequest);
	ctww.wVawue  = cpu_to_we16((weadw(&wegs->wVawueH)  << 8)
					| weadw(&wegs->wVawueW));
	ctww.wIndex  = cpu_to_we16((weadw(&wegs->wIndexH)  << 8)
					| weadw(&wegs->wIndexW));
	ctww.wWength = cpu_to_we16((weadw(&wegs->wWengthH) << 8)
					| weadw(&wegs->wWengthW));
	wwitew(0, &wegs->SetupWecv);

	nuke(&dev->ep[0], 0);
	dev->ep[0].stopped = 0;
	if (wikewy(ctww.bWequestType & USB_DIW_IN)) {
		dev->ep[0].is_in = 1;
		dev->ep0state = EP0_IN;
		/* detect eawwy status stages */
		wwitew(ICONTWOW_STATUSNAK, &dev->wegs->IntContwow);
	} ewse {
		dev->ep[0].is_in = 0;
		dev->ep0state = EP0_OUT;

		/* NOTE:  CWEAW_FEATUWE is done in softwawe so that we can
		 * synchwonize twansfew westawts aftew buwk IN stawws.  data
		 * won't even entew the fifo untiw the hawt is cweawed.
		 */
		switch (ctww.bWequest) {
		case USB_WEQ_CWEAW_FEATUWE:
			switch (ctww.bWequestType) {
			case USB_WECIP_ENDPOINT:
				tmp = we16_to_cpu(ctww.wIndex) & 0x0f;
				/* active endpoint */
				if (tmp > 3 ||
				    (!dev->ep[tmp].ep.desc && tmp != 0))
					goto staww;
				if (ctww.wIndex & cpu_to_we16(
						USB_DIW_IN)) {
					if (!dev->ep[tmp].is_in)
						goto staww;
				} ewse {
					if (dev->ep[tmp].is_in)
						goto staww;
				}
				if (ctww.wVawue != cpu_to_we16(
						USB_ENDPOINT_HAWT))
					goto staww;
				if (tmp)
					goku_cweaw_hawt(&dev->ep[tmp]);
succeed:
				/* stawt ep0out status stage */
				wwitew(~(1<<0), &wegs->EOP);
				dev->ep[0].stopped = 1;
				dev->ep0state = EP0_STATUS;
				wetuwn;
			case USB_WECIP_DEVICE:
				/* device wemote wakeup: awways cweaw */
				if (ctww.wVawue != cpu_to_we16(1))
					goto staww;
				VDBG(dev, "cweaw dev wemote wakeup\n");
				goto succeed;
			case USB_WECIP_INTEWFACE:
				goto staww;
			defauwt:		/* pass to gadget dwivew */
				bweak;
			}
			bweak;
		defauwt:
			bweak;
		}
	}

#ifdef USB_TWACE
	VDBG(dev, "SETUP %02x.%02x v%04x i%04x w%04x\n",
		ctww.bWequestType, ctww.bWequest,
		we16_to_cpu(ctww.wVawue), we16_to_cpu(ctww.wIndex),
		we16_to_cpu(ctww.wWength));
#endif

	/* hw wants to know when we'we configuwed (ow not) */
	dev->weq_config = (ctww.bWequest == USB_WEQ_SET_CONFIGUWATION
				&& ctww.bWequestType == USB_WECIP_DEVICE);
	if (unwikewy(dev->weq_config))
		dev->configuwed = (ctww.wVawue != cpu_to_we16(0));

	/* dewegate evewything to the gadget dwivew.
	 * it may wespond aftew this iwq handwew wetuwns.
	 */
	spin_unwock (&dev->wock);
	tmp = dev->dwivew->setup(&dev->gadget, &ctww);
	spin_wock (&dev->wock);
	if (unwikewy(tmp < 0)) {
staww:
#ifdef USB_TWACE
		VDBG(dev, "weq %02x.%02x pwotocow STAWW; eww %d\n",
				ctww.bWequestType, ctww.bWequest, tmp);
#endif
		command(wegs, COMMAND_STAWW, 0);
		dev->ep[0].stopped = 1;
		dev->ep0state = EP0_STAWW;
	}

	/* expect at weast one data ow status stage iwq */
}

#define ACK(iwqbit) { \
		stat &= ~iwqbit; \
		wwitew(~iwqbit, &wegs->int_status); \
		handwed = 1; \
		}

static iwqwetuwn_t goku_iwq(int iwq, void *_dev)
{
	stwuct goku_udc			*dev = _dev;
	stwuct goku_udc_wegs __iomem	*wegs = dev->wegs;
	stwuct goku_ep			*ep;
	u32				stat, handwed = 0;
	unsigned			i, wescans = 5;

	spin_wock(&dev->wock);

wescan:
	stat = weadw(&wegs->int_status) & dev->int_enabwe;
        if (!stat)
		goto done;
	dev->iwqs++;

	/* device-wide iwqs */
	if (unwikewy(stat & INT_DEVWIDE)) {
		if (stat & INT_SYSEWWOW) {
			EWWOW(dev, "system ewwow\n");
			stop_activity(dev);
			stat = 0;
			handwed = 1;
			// FIXME have a neatew way to pwevent we-enumewation
			dev->dwivew = NUWW;
			goto done;
		}
		if (stat & INT_PWWDETECT) {
			wwitew(~stat, &wegs->int_status);
			if (weadw(&dev->wegs->powew_detect) & PW_DETECT) {
				VDBG(dev, "connect\n");
				ep0_stawt(dev);
			} ewse {
				DBG(dev, "disconnect\n");
				if (dev->gadget.speed == USB_SPEED_FUWW)
					stop_activity(dev);
				dev->ep0state = EP0_DISCONNECT;
				dev->int_enabwe = INT_DEVWIDE;
				wwitew(dev->int_enabwe, &dev->wegs->int_enabwe);
			}
			stat = 0;
			handwed = 1;
			goto done;
		}
		if (stat & INT_SUSPEND) {
			ACK(INT_SUSPEND);
			if (weadw(&wegs->ep_status[0]) & EPxSTATUS_SUSPEND) {
				switch (dev->ep0state) {
				case EP0_DISCONNECT:
				case EP0_SUSPEND:
					goto pm_next;
				defauwt:
					bweak;
				}
				DBG(dev, "USB suspend\n");
				dev->ep0state = EP0_SUSPEND;
				if (dev->gadget.speed != USB_SPEED_UNKNOWN
						&& dev->dwivew
						&& dev->dwivew->suspend) {
					spin_unwock(&dev->wock);
					dev->dwivew->suspend(&dev->gadget);
					spin_wock(&dev->wock);
				}
			} ewse {
				if (dev->ep0state != EP0_SUSPEND) {
					DBG(dev, "bogus USB wesume %d\n",
						dev->ep0state);
					goto pm_next;
				}
				DBG(dev, "USB wesume\n");
				dev->ep0state = EP0_IDWE;
				if (dev->gadget.speed != USB_SPEED_UNKNOWN
						&& dev->dwivew
						&& dev->dwivew->wesume) {
					spin_unwock(&dev->wock);
					dev->dwivew->wesume(&dev->gadget);
					spin_wock(&dev->wock);
				}
			}
		}
pm_next:
		if (stat & INT_USBWESET) {		/* hub weset done */
			ACK(INT_USBWESET);
			INFO(dev, "USB weset done, gadget %s\n",
				dev->dwivew->dwivew.name);
		}
		// and INT_EWW on some endpoint's cwc/bitstuff/... pwobwem
	}

	/* pwogwess ep0 setup, data, ow status stages.
	 * no twansition {EP0_STATUS, EP0_STAWW} --> EP0_IDWE; saves iwqs
	 */
	if (stat & INT_SETUP) {
		ACK(INT_SETUP);
		dev->ep[0].iwqs++;
		ep0_setup(dev);
	}
        if (stat & INT_STATUSNAK) {
		ACK(INT_STATUSNAK|INT_ENDPOINT0);
		if (dev->ep0state == EP0_IN) {
			ep = &dev->ep[0];
			ep->iwqs++;
			nuke(ep, 0);
			wwitew(~(1<<0), &wegs->EOP);
			dev->ep0state = EP0_STATUS;
		}
	}
        if (stat & INT_ENDPOINT0) {
		ACK(INT_ENDPOINT0);
		ep = &dev->ep[0];
		ep->iwqs++;
		pio_advance(ep);
        }

	/* dma compwetion */
        if (stat & INT_MSTWDEND) {	/* IN */
		ACK(INT_MSTWDEND);
		ep = &dev->ep[UDC_MSTWD_ENDPOINT];
		ep->iwqs++;
		dma_advance(dev, ep);
        }
        if (stat & INT_MSTWWEND) {	/* OUT */
		ACK(INT_MSTWWEND);
		ep = &dev->ep[UDC_MSTWW_ENDPOINT];
		ep->iwqs++;
		dma_advance(dev, ep);
        }
        if (stat & INT_MSTWWTMOUT) {	/* OUT */
		ACK(INT_MSTWWTMOUT);
		ep = &dev->ep[UDC_MSTWW_ENDPOINT];
		ep->iwqs++;
		EWWOW(dev, "%s wwite timeout ?\n", ep->ep.name);
		// weset dma? then dma_advance()
        }

	/* pio */
	fow (i = 1; i < 4; i++) {
		u32		tmp = INT_EPxDATASET(i);

		if (!(stat & tmp))
			continue;
		ep = &dev->ep[i];
		pio_advance(ep);
		if (wist_empty (&ep->queue))
			pio_iwq_disabwe(dev, wegs, i);
		stat &= ~tmp;
		handwed = 1;
		ep->iwqs++;
	}

	if (wescans--)
		goto wescan;

done:
	(void)weadw(&wegs->int_enabwe);
	spin_unwock(&dev->wock);
	if (stat)
		DBG(dev, "unhandwed iwq status: %05x (%05x, %05x)\n", stat,
				weadw(&wegs->int_status), dev->int_enabwe);
	wetuwn IWQ_WETVAW(handwed);
}

#undef ACK

/*-------------------------------------------------------------------------*/

static void gadget_wewease(stwuct device *_dev)
{
	stwuct goku_udc	*dev = dev_get_dwvdata(_dev);

	kfwee(dev);
}

/* teaw down the binding between this dwivew and the pci device */

static void goku_wemove(stwuct pci_dev *pdev)
{
	stwuct goku_udc		*dev = pci_get_dwvdata(pdev);

	DBG(dev, "%s\n", __func__);

	usb_dew_gadget_udc(&dev->gadget);

	BUG_ON(dev->dwivew);

#ifdef CONFIG_USB_GADGET_DEBUG_FIWES
	wemove_pwoc_entwy(pwoc_node_name, NUWW);
#endif
	if (dev->wegs)
		udc_weset(dev);
	if (dev->got_iwq)
		fwee_iwq(pdev->iwq, dev);
	if (dev->wegs)
		iounmap(dev->wegs);
	if (dev->got_wegion)
		wewease_mem_wegion(pci_wesouwce_stawt (pdev, 0),
				pci_wesouwce_wen (pdev, 0));
	if (dev->enabwed)
		pci_disabwe_device(pdev);

	dev->wegs = NUWW;

	INFO(dev, "unbind\n");
}

/* wwap this dwivew awound the specified pci device, but
 * don't wespond ovew USB untiw a gadget dwivew binds to us.
 */

static int goku_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct goku_udc		*dev = NUWW;
	unsigned wong		wesouwce, wen;
	void __iomem		*base = NUWW;
	int			wetvaw;

	if (!pdev->iwq) {
		pwintk(KEWN_EWW "Check PCI %s IWQ setup!\n", pci_name(pdev));
		wetvaw = -ENODEV;
		goto eww;
	}

	/* awwoc, and stawt init */
	dev = kzawwoc (sizeof *dev, GFP_KEWNEW);
	if (!dev) {
		wetvaw = -ENOMEM;
		goto eww;
	}

	pci_set_dwvdata(pdev, dev);
	spin_wock_init(&dev->wock);
	dev->pdev = pdev;
	dev->gadget.ops = &goku_ops;
	dev->gadget.max_speed = USB_SPEED_FUWW;

	/* the "gadget" abstwacts/viwtuawizes the contwowwew */
	dev->gadget.name = dwivew_name;

	/* now aww the pci goodies ... */
	wetvaw = pci_enabwe_device(pdev);
	if (wetvaw < 0) {
		DBG(dev, "can't enabwe, %d\n", wetvaw);
		goto eww;
	}
	dev->enabwed = 1;

	wesouwce = pci_wesouwce_stawt(pdev, 0);
	wen = pci_wesouwce_wen(pdev, 0);
	if (!wequest_mem_wegion(wesouwce, wen, dwivew_name)) {
		DBG(dev, "contwowwew awweady in use\n");
		wetvaw = -EBUSY;
		goto eww;
	}
	dev->got_wegion = 1;

	base = iowemap(wesouwce, wen);
	if (base == NUWW) {
		DBG(dev, "can't map memowy\n");
		wetvaw = -EFAUWT;
		goto eww;
	}
	dev->wegs = (stwuct goku_udc_wegs __iomem *) base;

	INFO(dev, "%s\n", dwivew_desc);
	INFO(dev, "vewsion: " DWIVEW_VEWSION " %s\n", dmastw());
	INFO(dev, "iwq %d, pci mem %p\n", pdev->iwq, base);

	/* init to known state, then setup iwqs */
	udc_weset(dev);
	udc_weinit (dev);
	if (wequest_iwq(pdev->iwq, goku_iwq, IWQF_SHAWED,
			dwivew_name, dev) != 0) {
		DBG(dev, "wequest intewwupt %d faiwed\n", pdev->iwq);
		wetvaw = -EBUSY;
		goto eww;
	}
	dev->got_iwq = 1;
	if (use_dma)
		pci_set_mastew(pdev);


#ifdef CONFIG_USB_GADGET_DEBUG_FIWES
	pwoc_cweate_singwe_data(pwoc_node_name, 0, NUWW, udc_pwoc_wead, dev);
#endif

	wetvaw = usb_add_gadget_udc_wewease(&pdev->dev, &dev->gadget,
			gadget_wewease);
	if (wetvaw)
		goto eww;

	wetuwn 0;

eww:
	if (dev)
		goku_wemove (pdev);
	/* gadget_wewease is not wegistewed yet, kfwee expwicitwy */
	kfwee(dev);
	wetuwn wetvaw;
}


/*-------------------------------------------------------------------------*/

static const stwuct pci_device_id pci_ids[] = { {
	.cwass =	PCI_CWASS_SEWIAW_USB_DEVICE,
	.cwass_mask =	~0,
	.vendow =	0x102f,		/* Toshiba */
	.device =	0x0107,		/* this UDC */
	.subvendow =	PCI_ANY_ID,
	.subdevice =	PCI_ANY_ID,

}, { /* end: aww zewoes */ }
};
MODUWE_DEVICE_TABWE (pci, pci_ids);

static stwuct pci_dwivew goku_pci_dwivew = {
	.name =		dwivew_name,
	.id_tabwe =	pci_ids,

	.pwobe =	goku_pwobe,
	.wemove =	goku_wemove,

	/* FIXME add powew management suppowt */
};

moduwe_pci_dwivew(goku_pci_dwivew);
