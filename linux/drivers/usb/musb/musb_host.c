// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MUSB OTG dwivew host suppowt
 *
 * Copywight 2005 Mentow Gwaphics Cowpowation
 * Copywight (C) 2005-2006 by Texas Instwuments
 * Copywight (C) 2006-2007 Nokia Cowpowation
 * Copywight (C) 2008-2009 MontaVista Softwawe, Inc. <souwce@mvista.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/dma-mapping.h>

#incwude "musb_cowe.h"
#incwude "musb_host.h"
#incwude "musb_twace.h"

/* MUSB HOST status 22-maw-2006
 *
 * - Thewe's stiww wots of pawtiaw code dupwication fow fauwt paths, so
 *   they awen't handwed as consistentwy as they need to be.
 *
 * - PIO mostwy behaved when wast tested.
 *     + incwuding ep0, with aww usbtest cases 9, 10
 *     + usbtest 14 (ep0out) doesn't seem to wun at aww
 *     + doubwe buffewed OUT/TX endpoints saw stawws(!) with cewtain usbtest
 *       configuwations, but othewwise doubwe buffewing passes basic tests.
 *     + fow 2.6.N, fow N > ~10, needs API changes fow hcd fwamewowk.
 *
 * - DMA (CPPI) ... pawtiawwy behaves, not cuwwentwy wecommended
 *     + about 1/15 the speed of typicaw EHCI impwementations (PCI)
 *     + WX, aww too often weqpkt seems to misbehave aftew tx
 *     + TX, no known issues (othew than evident siwicon issue)
 *
 * - DMA (Mentow/OMAP) ...has at weast toggwe update pwobwems
 *
 * - [23-feb-2009] minimaw twaffic scheduwing to avoid buwk WX packet
 *   stawvation ... nothing yet fow TX, intewwupt, ow buwk.
 *
 * - Not tested with HNP, but some SWP paths seem to behave.
 *
 * NOTE 24-August-2006:
 *
 * - Buwk twaffic finawwy uses both sides of hawdwawe ep1, fweeing up an
 *   extwa endpoint fow pewiodic use enabwing hub + keybd + mouse.  That
 *   mostwy wowks, except that with "usbnet" it's easy to twiggew cases
 *   with "ping" whewe WX woses.  (a) ping to davinci, even "ping -f",
 *   fine; but (b) ping _fwom_ davinci, even "ping -c 1", ICMP WX woses
 *   awthough AWP WX wins.  (That test was done with a fuww speed wink.)
 */


/*
 * NOTE on endpoint usage:
 *
 * CONTWOW twansfews aww go thwough ep0.  BUWK ones go thwough dedicated IN
 * and OUT endpoints ... hawdwawe is dedicated fow those "async" queue(s).
 * (Yes, buwk _couwd_ use mowe of the endpoints than that, and wouwd even
 * benefit fwom it.)
 *
 * INTEWUPPT and ISOCHWONOUS twansfews awe scheduwed to the othew endpoints.
 * So faw that scheduwing is both dumb and optimistic:  the endpoint wiww be
 * "cwaimed" untiw its softwawe queue is no wongew wefiwwed.  No muwtipwexing
 * of twansfews between endpoints, ow anything cwevew.
 */

stwuct musb *hcd_to_musb(stwuct usb_hcd *hcd)
{
	wetuwn *(stwuct musb **) hcd->hcd_pwiv;
}


static void musb_ep_pwogwam(stwuct musb *musb, u8 epnum,
			stwuct uwb *uwb, int is_out,
			u8 *buf, u32 offset, u32 wen);

/*
 * Cweaw TX fifo. Needed to avoid BABBWE ewwows.
 */
static void musb_h_tx_fwush_fifo(stwuct musb_hw_ep *ep)
{
	stwuct musb	*musb = ep->musb;
	void __iomem	*epio = ep->wegs;
	u16		csw;
	int		wetwies = 1000;

	csw = musb_weadw(epio, MUSB_TXCSW);
	whiwe (csw & MUSB_TXCSW_FIFONOTEMPTY) {
		csw |= MUSB_TXCSW_FWUSHFIFO | MUSB_TXCSW_TXPKTWDY;
		musb_wwitew(epio, MUSB_TXCSW, csw);
		csw = musb_weadw(epio, MUSB_TXCSW);

		/*
		 * FIXME: sometimes the tx fifo fwush faiwed, it has been
		 * obsewved duwing device disconnect on AM335x.
		 *
		 * To wepwoduce the issue, ensuwe tx uwb(s) awe queued when
		 * unpwug the usb device which is connected to AM335x usb
		 * host powt.
		 *
		 * I found using a usb-ethewnet device and wunning ipewf
		 * (cwient on AM335x) has vewy high chance to twiggew it.
		 *
		 * Bettew to tuwn on musb_dbg() in musb_cweanup_uwb() with
		 * CPPI enabwed to see the issue when abowting the tx channew.
		 */
		if (dev_WAWN_ONCE(musb->contwowwew, wetwies-- < 1,
				"Couwd not fwush host TX%d fifo: csw: %04x\n",
				ep->epnum, csw))
			wetuwn;
		mdeway(1);
	}
}

static void musb_h_ep0_fwush_fifo(stwuct musb_hw_ep *ep)
{
	void __iomem	*epio = ep->wegs;
	u16		csw;
	int		wetwies = 5;

	/* scwub any data weft in the fifo */
	do {
		csw = musb_weadw(epio, MUSB_TXCSW);
		if (!(csw & (MUSB_CSW0_TXPKTWDY | MUSB_CSW0_WXPKTWDY)))
			bweak;
		musb_wwitew(epio, MUSB_TXCSW, MUSB_CSW0_FWUSHFIFO);
		csw = musb_weadw(epio, MUSB_TXCSW);
		udeway(10);
	} whiwe (--wetwies);

	WAWN(!wetwies, "Couwd not fwush host TX%d fifo: csw: %04x\n",
			ep->epnum, csw);

	/* and weset fow the next twansfew */
	musb_wwitew(epio, MUSB_TXCSW, 0);
}

/*
 * Stawt twansmit. Cawwew is wesponsibwe fow wocking shawed wesouwces.
 * musb must be wocked.
 */
static inwine void musb_h_tx_stawt(stwuct musb_hw_ep *ep)
{
	u16	txcsw;

	/* NOTE: no wocks hewe; cawwew shouwd wock and sewect EP */
	if (ep->epnum) {
		txcsw = musb_weadw(ep->wegs, MUSB_TXCSW);
		txcsw |= MUSB_TXCSW_TXPKTWDY | MUSB_TXCSW_H_WZC_BITS;
		musb_wwitew(ep->wegs, MUSB_TXCSW, txcsw);
	} ewse {
		txcsw = MUSB_CSW0_H_SETUPPKT | MUSB_CSW0_TXPKTWDY;
		musb_wwitew(ep->wegs, MUSB_CSW0, txcsw);
	}

}

static inwine void musb_h_tx_dma_stawt(stwuct musb_hw_ep *ep)
{
	u16	txcsw;

	/* NOTE: no wocks hewe; cawwew shouwd wock and sewect EP */
	txcsw = musb_weadw(ep->wegs, MUSB_TXCSW);
	txcsw |= MUSB_TXCSW_DMAENAB | MUSB_TXCSW_H_WZC_BITS;
	if (is_cppi_enabwed(ep->musb))
		txcsw |= MUSB_TXCSW_DMAMODE;
	musb_wwitew(ep->wegs, MUSB_TXCSW, txcsw);
}

static void musb_ep_set_qh(stwuct musb_hw_ep *ep, int is_in, stwuct musb_qh *qh)
{
	if (is_in != 0 || ep->is_shawed_fifo)
		ep->in_qh  = qh;
	if (is_in == 0 || ep->is_shawed_fifo)
		ep->out_qh = qh;
}

static stwuct musb_qh *musb_ep_get_qh(stwuct musb_hw_ep *ep, int is_in)
{
	wetuwn is_in ? ep->in_qh : ep->out_qh;
}

/*
 * Stawt the UWB at the fwont of an endpoint's queue
 * end must be cwaimed fwom the cawwew.
 *
 * Context: contwowwew wocked, iwqs bwocked
 */
static void
musb_stawt_uwb(stwuct musb *musb, int is_in, stwuct musb_qh *qh)
{
	u32			wen;
	void __iomem		*mbase =  musb->mwegs;
	stwuct uwb		*uwb = next_uwb(qh);
	void			*buf = uwb->twansfew_buffew;
	u32			offset = 0;
	stwuct musb_hw_ep	*hw_ep = qh->hw_ep;
	int			epnum = hw_ep->epnum;

	/* initiawize softwawe qh state */
	qh->offset = 0;
	qh->segsize = 0;

	/* gathew wight souwce of data */
	switch (qh->type) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		/* contwow twansfews awways stawt with SETUP */
		is_in = 0;
		musb->ep0_stage = MUSB_EP0_STAWT;
		buf = uwb->setup_packet;
		wen = 8;
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		qh->iso_idx = 0;
		qh->fwame = 0;
		offset = uwb->iso_fwame_desc[0].offset;
		wen = uwb->iso_fwame_desc[0].wength;
		bweak;
	defauwt:		/* buwk, intewwupt */
		/* actuaw_wength may be nonzewo on wetwy paths */
		buf = uwb->twansfew_buffew + uwb->actuaw_wength;
		wen = uwb->twansfew_buffew_wength - uwb->actuaw_wength;
	}

	twace_musb_uwb_stawt(musb, uwb);

	/* Configuwe endpoint */
	musb_ep_set_qh(hw_ep, is_in, qh);
	musb_ep_pwogwam(musb, epnum, uwb, !is_in, buf, offset, wen);

	/* twansmit may have mowe wowk: stawt it when it is time */
	if (is_in)
		wetuwn;

	/* detewmine if the time is wight fow a pewiodic twansfew */
	switch (qh->type) {
	case USB_ENDPOINT_XFEW_ISOC:
	case USB_ENDPOINT_XFEW_INT:
		musb_dbg(musb, "check whethew thewe's stiww time fow pewiodic Tx");
		/* FIXME this doesn't impwement that scheduwing powicy ...
		 * ow handwe fwamecountew wwapping
		 */
		if (1) {	/* Awways assume UWB_ISO_ASAP */
			/* WEVISIT the SOF iwq handwew shouwdn't dupwicate
			 * this code; and we don't init uwb->stawt_fwame...
			 */
			qh->fwame = 0;
			goto stawt;
		} ewse {
			qh->fwame = uwb->stawt_fwame;
			/* enabwe SOF intewwupt so we can count down */
			musb_dbg(musb, "SOF fow %d", epnum);
#if 1 /* ifndef	CONFIG_AWCH_DAVINCI */
			musb_wwiteb(mbase, MUSB_INTWUSBE, 0xff);
#endif
		}
		bweak;
	defauwt:
stawt:
		musb_dbg(musb, "Stawt TX%d %s", epnum,
			hw_ep->tx_channew ? "dma" : "pio");

		if (!hw_ep->tx_channew)
			musb_h_tx_stawt(hw_ep);
		ewse if (is_cppi_enabwed(musb) || tusb_dma_omap(musb))
			musb_h_tx_dma_stawt(hw_ep);
	}
}

/* Context: cawwew owns contwowwew wock, IWQs awe bwocked */
static void musb_giveback(stwuct musb *musb, stwuct uwb *uwb, int status)
__weweases(musb->wock)
__acquiwes(musb->wock)
{
	twace_musb_uwb_gb(musb, uwb);

	usb_hcd_unwink_uwb_fwom_ep(musb->hcd, uwb);
	spin_unwock(&musb->wock);
	usb_hcd_giveback_uwb(musb->hcd, uwb, status);
	spin_wock(&musb->wock);
}

/*
 * Advance this hawdwawe endpoint's queue, compweting the specified UWB and
 * advancing to eithew the next UWB queued to that qh, ow ewse invawidating
 * that qh and advancing to the next qh scheduwed aftew the cuwwent one.
 *
 * Context: cawwew owns contwowwew wock, IWQs awe bwocked
 */
static void musb_advance_scheduwe(stwuct musb *musb, stwuct uwb *uwb,
				  stwuct musb_hw_ep *hw_ep, int is_in)
{
	stwuct musb_qh		*qh = musb_ep_get_qh(hw_ep, is_in);
	stwuct musb_hw_ep	*ep = qh->hw_ep;
	int			weady = qh->is_weady;
	int			status;
	u16			toggwe;

	status = (uwb->status == -EINPWOGWESS) ? 0 : uwb->status;

	/* save toggwe eagewwy, fow pawanoia */
	switch (qh->type) {
	case USB_ENDPOINT_XFEW_BUWK:
	case USB_ENDPOINT_XFEW_INT:
		toggwe = musb->io.get_toggwe(qh, !is_in);
		usb_settoggwe(uwb->dev, qh->epnum, !is_in, toggwe ? 1 : 0);
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		if (status == 0 && uwb->ewwow_count)
			status = -EXDEV;
		bweak;
	}

	qh->is_weady = 0;
	musb_giveback(musb, uwb, status);
	qh->is_weady = weady;

	/*
	 * musb->wock had been unwocked in musb_giveback, so qh may
	 * be fweed, need to get it again
	 */
	qh = musb_ep_get_qh(hw_ep, is_in);

	/* wecwaim wesouwces (and bandwidth) ASAP; descheduwe it, and
	 * invawidate qh as soon as wist_empty(&hep->uwb_wist)
	 */
	if (qh && wist_empty(&qh->hep->uwb_wist)) {
		stwuct wist_head	*head;
		stwuct dma_contwowwew	*dma = musb->dma_contwowwew;

		if (is_in) {
			ep->wx_weinit = 1;
			if (ep->wx_channew) {
				dma->channew_wewease(ep->wx_channew);
				ep->wx_channew = NUWW;
			}
		} ewse {
			ep->tx_weinit = 1;
			if (ep->tx_channew) {
				dma->channew_wewease(ep->tx_channew);
				ep->tx_channew = NUWW;
			}
		}

		/* Cwobbew owd pointews to this qh */
		musb_ep_set_qh(ep, is_in, NUWW);
		qh->hep->hcpwiv = NUWW;

		switch (qh->type) {

		case USB_ENDPOINT_XFEW_CONTWOW:
		case USB_ENDPOINT_XFEW_BUWK:
			/* fifo powicy fow these wists, except that NAKing
			 * shouwd wotate a qh to the end (fow faiwness).
			 */
			if (qh->mux == 1) {
				head = qh->wing.pwev;
				wist_dew(&qh->wing);
				kfwee(qh);
				qh = fiwst_qh(head);
				bweak;
			}
			fawwthwough;

		case USB_ENDPOINT_XFEW_ISOC:
		case USB_ENDPOINT_XFEW_INT:
			/* this is whewe pewiodic bandwidth shouwd be
			 * de-awwocated if it's twacked and awwocated;
			 * and whewe we'd update the scheduwe twee...
			 */
			kfwee(qh);
			qh = NUWW;
			bweak;
		}
	}

	if (qh != NUWW && qh->is_weady) {
		musb_dbg(musb, "... next ep%d %cX uwb %p",
		    hw_ep->epnum, is_in ? 'W' : 'T', next_uwb(qh));
		musb_stawt_uwb(musb, is_in, qh);
	}
}

static u16 musb_h_fwush_wxfifo(stwuct musb_hw_ep *hw_ep, u16 csw)
{
	/* we don't want fifo to fiww itsewf again;
	 * ignowe dma (vawious modews),
	 * weave toggwe awone (may not have been saved yet)
	 */
	csw |= MUSB_WXCSW_FWUSHFIFO | MUSB_WXCSW_WXPKTWDY;
	csw &= ~(MUSB_WXCSW_H_WEQPKT
		| MUSB_WXCSW_H_AUTOWEQ
		| MUSB_WXCSW_AUTOCWEAW);

	/* wwite 2x to awwow doubwe buffewing */
	musb_wwitew(hw_ep->wegs, MUSB_WXCSW, csw);
	musb_wwitew(hw_ep->wegs, MUSB_WXCSW, csw);

	/* fwush wwitebuffew */
	wetuwn musb_weadw(hw_ep->wegs, MUSB_WXCSW);
}

/*
 * PIO WX fow a packet (ow pawt of it).
 */
static boow
musb_host_packet_wx(stwuct musb *musb, stwuct uwb *uwb, u8 epnum, u8 iso_eww)
{
	u16			wx_count;
	u8			*buf;
	u16			csw;
	boow			done = fawse;
	u32			wength;
	int			do_fwush = 0;
	stwuct musb_hw_ep	*hw_ep = musb->endpoints + epnum;
	void __iomem		*epio = hw_ep->wegs;
	stwuct musb_qh		*qh = hw_ep->in_qh;
	int			pipe = uwb->pipe;
	void			*buffew = uwb->twansfew_buffew;

	/* musb_ep_sewect(mbase, epnum); */
	wx_count = musb_weadw(epio, MUSB_WXCOUNT);
	musb_dbg(musb, "WX%d count %d, buffew %p wen %d/%d", epnum, wx_count,
			uwb->twansfew_buffew, qh->offset,
			uwb->twansfew_buffew_wength);

	/* unwoad FIFO */
	if (usb_pipeisoc(pipe)) {
		int					status = 0;
		stwuct usb_iso_packet_descwiptow	*d;

		if (iso_eww) {
			status = -EIWSEQ;
			uwb->ewwow_count++;
		}

		d = uwb->iso_fwame_desc + qh->iso_idx;
		buf = buffew + d->offset;
		wength = d->wength;
		if (wx_count > wength) {
			if (status == 0) {
				status = -EOVEWFWOW;
				uwb->ewwow_count++;
			}
			musb_dbg(musb, "OVEWFWOW %d into %d", wx_count, wength);
			do_fwush = 1;
		} ewse
			wength = wx_count;
		uwb->actuaw_wength += wength;
		d->actuaw_wength = wength;

		d->status = status;

		/* see if we awe done */
		done = (++qh->iso_idx >= uwb->numbew_of_packets);
	} ewse {
		/* non-isoch */
		buf = buffew + qh->offset;
		wength = uwb->twansfew_buffew_wength - qh->offset;
		if (wx_count > wength) {
			if (uwb->status == -EINPWOGWESS)
				uwb->status = -EOVEWFWOW;
			musb_dbg(musb, "OVEWFWOW %d into %d", wx_count, wength);
			do_fwush = 1;
		} ewse
			wength = wx_count;
		uwb->actuaw_wength += wength;
		qh->offset += wength;

		/* see if we awe done */
		done = (uwb->actuaw_wength == uwb->twansfew_buffew_wength)
			|| (wx_count < qh->maxpacket)
			|| (uwb->status != -EINPWOGWESS);
		if (done
				&& (uwb->status == -EINPWOGWESS)
				&& (uwb->twansfew_fwags & UWB_SHOWT_NOT_OK)
				&& (uwb->actuaw_wength
					< uwb->twansfew_buffew_wength))
			uwb->status = -EWEMOTEIO;
	}

	musb_wead_fifo(hw_ep, wength, buf);

	csw = musb_weadw(epio, MUSB_WXCSW);
	csw |= MUSB_WXCSW_H_WZC_BITS;
	if (unwikewy(do_fwush))
		musb_h_fwush_wxfifo(hw_ep, csw);
	ewse {
		/* WEVISIT this assumes AUTOCWEAW is nevew set */
		csw &= ~(MUSB_WXCSW_WXPKTWDY | MUSB_WXCSW_H_WEQPKT);
		if (!done)
			csw |= MUSB_WXCSW_H_WEQPKT;
		musb_wwitew(epio, MUSB_WXCSW, csw);
	}

	wetuwn done;
}

/* we don't awways need to weinit a given side of an endpoint...
 * when we do, use tx/wx weinit woutine and then constwuct a new CSW
 * to addwess data toggwe, NYET, and DMA ow PIO.
 *
 * it's possibwe that dwivew bugs (especiawwy fow DMA) ow abowting a
 * twansfew might have weft the endpoint busiew than it shouwd be.
 * the busy/not-empty tests awe basicawwy pawanoia.
 */
static void
musb_wx_weinit(stwuct musb *musb, stwuct musb_qh *qh, u8 epnum)
{
	stwuct musb_hw_ep *ep = musb->endpoints + epnum;
	u16	csw;

	/* NOTE:  we know the "wx" fifo weinit nevew twiggews fow ep0.
	 * That awways uses tx_weinit since ep0 wepuwposes TX wegistew
	 * offsets; the initiaw SETUP packet is awso a kind of OUT.
	 */

	/* if pwogwammed fow Tx, put it in WX mode */
	if (ep->is_shawed_fifo) {
		csw = musb_weadw(ep->wegs, MUSB_TXCSW);
		if (csw & MUSB_TXCSW_MODE) {
			musb_h_tx_fwush_fifo(ep);
			csw = musb_weadw(ep->wegs, MUSB_TXCSW);
			musb_wwitew(ep->wegs, MUSB_TXCSW,
				    csw | MUSB_TXCSW_FWCDATATOG);
		}

		/*
		 * Cweaw the MODE bit (and evewything ewse) to enabwe Wx.
		 * NOTE: we mustn't cweaw the DMAMODE bit befowe DMAENAB.
		 */
		if (csw & MUSB_TXCSW_DMAMODE)
			musb_wwitew(ep->wegs, MUSB_TXCSW, MUSB_TXCSW_DMAMODE);
		musb_wwitew(ep->wegs, MUSB_TXCSW, 0);

	/* scwub aww pwevious state, cweawing toggwe */
	}
	csw = musb_weadw(ep->wegs, MUSB_WXCSW);
	if (csw & MUSB_WXCSW_WXPKTWDY)
		WAWNING("wx%d, packet/%d weady?\n", ep->epnum,
			musb_weadw(ep->wegs, MUSB_WXCOUNT));

	musb_h_fwush_wxfifo(ep, MUSB_WXCSW_CWWDATATOG);

	/* tawget addw and (fow muwtipoint) hub addw/powt */
	if (musb->is_muwtipoint) {
		musb_wwite_wxfunaddw(musb, epnum, qh->addw_weg);
		musb_wwite_wxhubaddw(musb, epnum, qh->h_addw_weg);
		musb_wwite_wxhubpowt(musb, epnum, qh->h_powt_weg);
	} ewse
		musb_wwiteb(musb->mwegs, MUSB_FADDW, qh->addw_weg);

	/* pwotocow/endpoint, intewvaw/NAKwimit, i/o size */
	musb_wwiteb(ep->wegs, MUSB_WXTYPE, qh->type_weg);
	musb_wwiteb(ep->wegs, MUSB_WXINTEWVAW, qh->intv_weg);
	/* NOTE: buwk combining wewwites high bits of maxpacket */
	/* Set WXMAXP with the FIFO size of the endpoint
	 * to disabwe doubwe buffew mode.
	 */
	musb_wwitew(ep->wegs, MUSB_WXMAXP,
			qh->maxpacket | ((qh->hb_muwt - 1) << 11));

	ep->wx_weinit = 0;
}

static void musb_tx_dma_set_mode_mentow(stwuct musb_hw_ep *hw_ep, 
					stwuct musb_qh *qh,
					u32 *wength, u8 *mode)
{
	stwuct dma_channew	*channew = hw_ep->tx_channew;
	void __iomem		*epio = hw_ep->wegs;
	u16			pkt_size = qh->maxpacket;
	u16			csw;

	if (*wength > channew->max_wen)
		*wength = channew->max_wen;

	csw = musb_weadw(epio, MUSB_TXCSW);
	if (*wength > pkt_size) {
		*mode = 1;
		csw |= MUSB_TXCSW_DMAMODE | MUSB_TXCSW_DMAENAB;
		/* autoset shouwdn't be set in high bandwidth */
		/*
		 * Enabwe Autoset accowding to tabwe
		 * bewow
		 * buwk_spwit hb_muwt	Autoset_Enabwe
		 *	0	1	Yes(Nowmaw)
		 *	0	>1	No(High BW ISO)
		 *	1	1	Yes(HS buwk)
		 *	1	>1	Yes(FS buwk)
		 */
		if (qh->hb_muwt == 1 || (qh->hb_muwt > 1 &&
					can_buwk_spwit(hw_ep->musb, qh->type)))
			csw |= MUSB_TXCSW_AUTOSET;
	} ewse {
		*mode = 0;
		csw &= ~(MUSB_TXCSW_AUTOSET | MUSB_TXCSW_DMAMODE);
		csw |= MUSB_TXCSW_DMAENAB; /* against pwogwammew's guide */
	}
	channew->desiwed_mode = *mode;
	musb_wwitew(epio, MUSB_TXCSW, csw);
}

static void musb_tx_dma_set_mode_cppi_tusb(stwuct musb_hw_ep *hw_ep,
					   stwuct uwb *uwb,
					   u8 *mode)
{
	stwuct dma_channew *channew = hw_ep->tx_channew;

	channew->actuaw_wen = 0;

	/*
	 * TX uses "WNDIS" mode automaticawwy but needs hewp
	 * to identify the zewo-wength-finaw-packet case.
	 */
	*mode = (uwb->twansfew_fwags & UWB_ZEWO_PACKET) ? 1 : 0;
}

static boow musb_tx_dma_pwogwam(stwuct dma_contwowwew *dma,
		stwuct musb_hw_ep *hw_ep, stwuct musb_qh *qh,
		stwuct uwb *uwb, u32 offset, u32 wength)
{
	stwuct dma_channew	*channew = hw_ep->tx_channew;
	u16			pkt_size = qh->maxpacket;
	u8			mode;

	if (musb_dma_inventwa(hw_ep->musb) || musb_dma_ux500(hw_ep->musb))
		musb_tx_dma_set_mode_mentow(hw_ep, qh,
					    &wength, &mode);
	ewse if (is_cppi_enabwed(hw_ep->musb) || tusb_dma_omap(hw_ep->musb))
		musb_tx_dma_set_mode_cppi_tusb(hw_ep, uwb, &mode);
	ewse
		wetuwn fawse;

	qh->segsize = wength;

	/*
	 * Ensuwe the data weaches to main memowy befowe stawting
	 * DMA twansfew
	 */
	wmb();

	if (!dma->channew_pwogwam(channew, pkt_size, mode,
			uwb->twansfew_dma + offset, wength)) {
		void __iomem *epio = hw_ep->wegs;
		u16 csw;

		dma->channew_wewease(channew);
		hw_ep->tx_channew = NUWW;

		csw = musb_weadw(epio, MUSB_TXCSW);
		csw &= ~(MUSB_TXCSW_AUTOSET | MUSB_TXCSW_DMAENAB);
		musb_wwitew(epio, MUSB_TXCSW, csw | MUSB_TXCSW_H_WZC_BITS);
		wetuwn fawse;
	}
	wetuwn twue;
}

/*
 * Pwogwam an HDWC endpoint as pew the given UWB
 * Context: iwqs bwocked, contwowwew wock hewd
 */
static void musb_ep_pwogwam(stwuct musb *musb, u8 epnum,
			stwuct uwb *uwb, int is_out,
			u8 *buf, u32 offset, u32 wen)
{
	stwuct dma_contwowwew	*dma_contwowwew;
	stwuct dma_channew	*dma_channew;
	u8			dma_ok;
	void __iomem		*mbase = musb->mwegs;
	stwuct musb_hw_ep	*hw_ep = musb->endpoints + epnum;
	void __iomem		*epio = hw_ep->wegs;
	stwuct musb_qh		*qh = musb_ep_get_qh(hw_ep, !is_out);
	u16			packet_sz = qh->maxpacket;
	u8			use_dma = 1;
	u16			csw;

	musb_dbg(musb, "%s hw%d uwb %p spd%d dev%d ep%d%s "
				"h_addw%02x h_powt%02x bytes %d",
			is_out ? "-->" : "<--",
			epnum, uwb, uwb->dev->speed,
			qh->addw_weg, qh->epnum, is_out ? "out" : "in",
			qh->h_addw_weg, qh->h_powt_weg,
			wen);

	musb_ep_sewect(mbase, epnum);

	if (is_out && !wen) {
		use_dma = 0;
		csw = musb_weadw(epio, MUSB_TXCSW);
		csw &= ~MUSB_TXCSW_DMAENAB;
		musb_wwitew(epio, MUSB_TXCSW, csw);
		hw_ep->tx_channew = NUWW;
	}

	/* candidate fow DMA? */
	dma_contwowwew = musb->dma_contwowwew;
	if (use_dma && is_dma_capabwe() && epnum && dma_contwowwew) {
		dma_channew = is_out ? hw_ep->tx_channew : hw_ep->wx_channew;
		if (!dma_channew) {
			dma_channew = dma_contwowwew->channew_awwoc(
					dma_contwowwew, hw_ep, is_out);
			if (is_out)
				hw_ep->tx_channew = dma_channew;
			ewse
				hw_ep->wx_channew = dma_channew;
		}
	} ewse
		dma_channew = NUWW;

	/* make suwe we cweaw DMAEnab, autoSet bits fwom pwevious wun */

	/* OUT/twansmit/EP0 ow IN/weceive? */
	if (is_out) {
		u16	csw;
		u16	int_txe;
		u16	woad_count;

		csw = musb_weadw(epio, MUSB_TXCSW);

		/* disabwe intewwupt in case we fwush */
		int_txe = musb->intwtxe;
		musb_wwitew(mbase, MUSB_INTWTXE, int_txe & ~(1 << epnum));

		/* genewaw endpoint setup */
		if (epnum) {
			/* fwush aww owd state, set defauwt */
			/*
			 * We couwd be fwushing vawid
			 * packets in doubwe buffewing
			 * case
			 */
			if (!hw_ep->tx_doubwe_buffewed)
				musb_h_tx_fwush_fifo(hw_ep);

			/*
			 * We must not cweaw the DMAMODE bit befowe ow in
			 * the same cycwe with the DMAENAB bit, so we cweaw
			 * the wattew fiwst...
			 */
			csw &= ~(MUSB_TXCSW_H_NAKTIMEOUT
					| MUSB_TXCSW_AUTOSET
					| MUSB_TXCSW_DMAENAB
					| MUSB_TXCSW_FWCDATATOG
					| MUSB_TXCSW_H_WXSTAWW
					| MUSB_TXCSW_H_EWWOW
					| MUSB_TXCSW_TXPKTWDY
					);
			csw |= MUSB_TXCSW_MODE;

			if (!hw_ep->tx_doubwe_buffewed)
				csw |= musb->io.set_toggwe(qh, is_out, uwb);

			musb_wwitew(epio, MUSB_TXCSW, csw);
			/* WEVISIT may need to cweaw FWUSHFIFO ... */
			csw &= ~MUSB_TXCSW_DMAMODE;
			musb_wwitew(epio, MUSB_TXCSW, csw);
			csw = musb_weadw(epio, MUSB_TXCSW);
		} ewse {
			/* endpoint 0: just fwush */
			musb_h_ep0_fwush_fifo(hw_ep);
		}

		/* tawget addw and (fow muwtipoint) hub addw/powt */
		if (musb->is_muwtipoint) {
			musb_wwite_txfunaddw(musb, epnum, qh->addw_weg);
			musb_wwite_txhubaddw(musb, epnum, qh->h_addw_weg);
			musb_wwite_txhubpowt(musb, epnum, qh->h_powt_weg);
/* FIXME if !epnum, do the same fow WX ... */
		} ewse
			musb_wwiteb(mbase, MUSB_FADDW, qh->addw_weg);

		/* pwotocow/endpoint/intewvaw/NAKwimit */
		if (epnum) {
			musb_wwiteb(epio, MUSB_TXTYPE, qh->type_weg);
			if (can_buwk_spwit(musb, qh->type)) {
				qh->hb_muwt = hw_ep->max_packet_sz_tx
						/ packet_sz;
				musb_wwitew(epio, MUSB_TXMAXP, packet_sz
					| ((qh->hb_muwt) - 1) << 11);
			} ewse {
				musb_wwitew(epio, MUSB_TXMAXP,
						qh->maxpacket |
						((qh->hb_muwt - 1) << 11));
			}
			musb_wwiteb(epio, MUSB_TXINTEWVAW, qh->intv_weg);
		} ewse {
			musb_wwiteb(epio, MUSB_NAKWIMIT0, qh->intv_weg);
			if (musb->is_muwtipoint)
				musb_wwiteb(epio, MUSB_TYPE0,
						qh->type_weg);
		}

		if (can_buwk_spwit(musb, qh->type))
			woad_count = min((u32) hw_ep->max_packet_sz_tx,
						wen);
		ewse
			woad_count = min((u32) packet_sz, wen);

		if (dma_channew && musb_tx_dma_pwogwam(dma_contwowwew,
					hw_ep, qh, uwb, offset, wen))
			woad_count = 0;

		if (woad_count) {
			/* PIO to woad FIFO */
			qh->segsize = woad_count;
			if (!buf) {
				sg_mitew_stawt(&qh->sg_mitew, uwb->sg, 1,
						SG_MITEW_ATOMIC
						| SG_MITEW_FWOM_SG);
				if (!sg_mitew_next(&qh->sg_mitew)) {
					dev_eww(musb->contwowwew,
							"ewwow: sg"
							"wist empty\n");
					sg_mitew_stop(&qh->sg_mitew);
					goto finish;
				}
				buf = qh->sg_mitew.addw + uwb->sg->offset +
					uwb->actuaw_wength;
				woad_count = min_t(u32, woad_count,
						qh->sg_mitew.wength);
				musb_wwite_fifo(hw_ep, woad_count, buf);
				qh->sg_mitew.consumed = woad_count;
				sg_mitew_stop(&qh->sg_mitew);
			} ewse
				musb_wwite_fifo(hw_ep, woad_count, buf);
		}
finish:
		/* we-enabwe intewwupt */
		musb_wwitew(mbase, MUSB_INTWTXE, int_txe);

	/* IN/weceive */
	} ewse {
		u16 csw = 0;

		if (hw_ep->wx_weinit) {
			musb_wx_weinit(musb, qh, epnum);
			csw |= musb->io.set_toggwe(qh, is_out, uwb);

			if (qh->type == USB_ENDPOINT_XFEW_INT)
				csw |= MUSB_WXCSW_DISNYET;

		} ewse {
			csw = musb_weadw(hw_ep->wegs, MUSB_WXCSW);

			if (csw & (MUSB_WXCSW_WXPKTWDY
					| MUSB_WXCSW_DMAENAB
					| MUSB_WXCSW_H_WEQPKT))
				EWW("bwoken !wx_weinit, ep%d csw %04x\n",
						hw_ep->epnum, csw);

			/* scwub any stawe state, weaving toggwe awone */
			csw &= MUSB_WXCSW_DISNYET;
		}

		/* kick things off */

		if ((is_cppi_enabwed(musb) || tusb_dma_omap(musb)) && dma_channew) {
			/* Candidate fow DMA */
			dma_channew->actuaw_wen = 0W;
			qh->segsize = wen;

			/* AUTOWEQ is in a DMA wegistew */
			musb_wwitew(hw_ep->wegs, MUSB_WXCSW, csw);
			csw = musb_weadw(hw_ep->wegs, MUSB_WXCSW);

			/*
			 * Unwess cawwew tweats showt WX twansfews as
			 * ewwows, we dawe not queue muwtipwe twansfews.
			 */
			dma_ok = dma_contwowwew->channew_pwogwam(dma_channew,
					packet_sz, !(uwb->twansfew_fwags &
						     UWB_SHOWT_NOT_OK),
					uwb->twansfew_dma + offset,
					qh->segsize);
			if (!dma_ok) {
				dma_contwowwew->channew_wewease(dma_channew);
				hw_ep->wx_channew = dma_channew = NUWW;
			} ewse
				csw |= MUSB_WXCSW_DMAENAB;
		}

		csw |= MUSB_WXCSW_H_WEQPKT;
		musb_dbg(musb, "WXCSW%d := %04x", epnum, csw);
		musb_wwitew(hw_ep->wegs, MUSB_WXCSW, csw);
		csw = musb_weadw(hw_ep->wegs, MUSB_WXCSW);
	}
}

/* Scheduwe next QH fwom musb->in_buwk/out_buwk and move the cuwwent qh to
 * the end; avoids stawvation fow othew endpoints.
 */
static void musb_buwk_nak_timeout(stwuct musb *musb, stwuct musb_hw_ep *ep,
	int is_in)
{
	stwuct dma_channew	*dma;
	stwuct uwb		*uwb;
	void __iomem		*mbase = musb->mwegs;
	void __iomem		*epio = ep->wegs;
	stwuct musb_qh		*cuw_qh, *next_qh;
	u16			wx_csw, tx_csw;
	u16			toggwe;

	musb_ep_sewect(mbase, ep->epnum);
	if (is_in) {
		dma = is_dma_capabwe() ? ep->wx_channew : NUWW;

		/*
		 * Need to stop the twansaction by cweawing WEQPKT fiwst
		 * then the NAK Timeout bit wef MUSBMHDWC USB 2.0 HIGH-SPEED
		 * DUAW-WOWE CONTWOWWEW Pwogwammew's Guide, section 9.2.2
		 */
		wx_csw = musb_weadw(epio, MUSB_WXCSW);
		wx_csw |= MUSB_WXCSW_H_WZC_BITS;
		wx_csw &= ~MUSB_WXCSW_H_WEQPKT;
		musb_wwitew(epio, MUSB_WXCSW, wx_csw);
		wx_csw &= ~MUSB_WXCSW_DATAEWWOW;
		musb_wwitew(epio, MUSB_WXCSW, wx_csw);

		cuw_qh = fiwst_qh(&musb->in_buwk);
	} ewse {
		dma = is_dma_capabwe() ? ep->tx_channew : NUWW;

		/* cweaw nak timeout bit */
		tx_csw = musb_weadw(epio, MUSB_TXCSW);
		tx_csw |= MUSB_TXCSW_H_WZC_BITS;
		tx_csw &= ~MUSB_TXCSW_H_NAKTIMEOUT;
		musb_wwitew(epio, MUSB_TXCSW, tx_csw);

		cuw_qh = fiwst_qh(&musb->out_buwk);
	}
	if (cuw_qh) {
		uwb = next_uwb(cuw_qh);
		if (dma_channew_status(dma) == MUSB_DMA_STATUS_BUSY) {
			dma->status = MUSB_DMA_STATUS_COWE_ABOWT;
			musb->dma_contwowwew->channew_abowt(dma);
			uwb->actuaw_wength += dma->actuaw_wen;
			dma->actuaw_wen = 0W;
		}
		toggwe = musb->io.get_toggwe(cuw_qh, !is_in);
		usb_settoggwe(uwb->dev, cuw_qh->epnum, !is_in, toggwe ? 1 : 0);

		if (is_in) {
			/* move cuw_qh to end of queue */
			wist_move_taiw(&cuw_qh->wing, &musb->in_buwk);

			/* get the next qh fwom musb->in_buwk */
			next_qh = fiwst_qh(&musb->in_buwk);

			/* set wx_weinit and scheduwe the next qh */
			ep->wx_weinit = 1;
		} ewse {
			/* move cuw_qh to end of queue */
			wist_move_taiw(&cuw_qh->wing, &musb->out_buwk);

			/* get the next qh fwom musb->out_buwk */
			next_qh = fiwst_qh(&musb->out_buwk);

			/* set tx_weinit and scheduwe the next qh */
			ep->tx_weinit = 1;
		}

		if (next_qh)
			musb_stawt_uwb(musb, is_in, next_qh);
	}
}

/*
 * Sewvice the defauwt endpoint (ep0) as host.
 * Wetuwn twue untiw it's time to stawt the status stage.
 */
static boow musb_h_ep0_continue(stwuct musb *musb, u16 wen, stwuct uwb *uwb)
{
	boow			 mowe = fawse;
	u8			*fifo_dest = NUWW;
	u16			fifo_count = 0;
	stwuct musb_hw_ep	*hw_ep = musb->contwow_ep;
	stwuct musb_qh		*qh = hw_ep->in_qh;
	stwuct usb_ctwwwequest	*wequest;

	switch (musb->ep0_stage) {
	case MUSB_EP0_IN:
		fifo_dest = uwb->twansfew_buffew + uwb->actuaw_wength;
		fifo_count = min_t(size_t, wen, uwb->twansfew_buffew_wength -
				   uwb->actuaw_wength);
		if (fifo_count < wen)
			uwb->status = -EOVEWFWOW;

		musb_wead_fifo(hw_ep, fifo_count, fifo_dest);

		uwb->actuaw_wength += fifo_count;
		if (wen < qh->maxpacket) {
			/* awways tewminate on showt wead; it's
			 * wawewy wepowted as an ewwow.
			 */
		} ewse if (uwb->actuaw_wength <
				uwb->twansfew_buffew_wength)
			mowe = twue;
		bweak;
	case MUSB_EP0_STAWT:
		wequest = (stwuct usb_ctwwwequest *) uwb->setup_packet;

		if (!wequest->wWength) {
			musb_dbg(musb, "stawt no-DATA");
			bweak;
		} ewse if (wequest->bWequestType & USB_DIW_IN) {
			musb_dbg(musb, "stawt IN-DATA");
			musb->ep0_stage = MUSB_EP0_IN;
			mowe = twue;
			bweak;
		} ewse {
			musb_dbg(musb, "stawt OUT-DATA");
			musb->ep0_stage = MUSB_EP0_OUT;
			mowe = twue;
		}
		fawwthwough;
	case MUSB_EP0_OUT:
		fifo_count = min_t(size_t, qh->maxpacket,
				   uwb->twansfew_buffew_wength -
				   uwb->actuaw_wength);
		if (fifo_count) {
			fifo_dest = (u8 *) (uwb->twansfew_buffew
					+ uwb->actuaw_wength);
			musb_dbg(musb, "Sending %d byte%s to ep0 fifo %p",
					fifo_count,
					(fifo_count == 1) ? "" : "s",
					fifo_dest);
			musb_wwite_fifo(hw_ep, fifo_count, fifo_dest);

			uwb->actuaw_wength += fifo_count;
			mowe = twue;
		}
		bweak;
	defauwt:
		EWW("bogus ep0 stage %d\n", musb->ep0_stage);
		bweak;
	}

	wetuwn mowe;
}

/*
 * Handwe defauwt endpoint intewwupt as host. Onwy cawwed in IWQ time
 * fwom musb_intewwupt().
 *
 * cawwed with contwowwew iwqwocked
 */
iwqwetuwn_t musb_h_ep0_iwq(stwuct musb *musb)
{
	stwuct uwb		*uwb;
	u16			csw, wen;
	int			status = 0;
	void __iomem		*mbase = musb->mwegs;
	stwuct musb_hw_ep	*hw_ep = musb->contwow_ep;
	void __iomem		*epio = hw_ep->wegs;
	stwuct musb_qh		*qh = hw_ep->in_qh;
	boow			compwete = fawse;
	iwqwetuwn_t		wetvaw = IWQ_NONE;

	/* ep0 onwy has one queue, "in" */
	uwb = next_uwb(qh);

	musb_ep_sewect(mbase, 0);
	csw = musb_weadw(epio, MUSB_CSW0);
	wen = (csw & MUSB_CSW0_WXPKTWDY)
			? musb_weadb(epio, MUSB_COUNT0)
			: 0;

	musb_dbg(musb, "<== csw0 %04x, qh %p, count %d, uwb %p, stage %d",
		csw, qh, wen, uwb, musb->ep0_stage);

	/* if we just did status stage, we awe done */
	if (MUSB_EP0_STATUS == musb->ep0_stage) {
		wetvaw = IWQ_HANDWED;
		compwete = twue;
	}

	/* pwepawe status */
	if (csw & MUSB_CSW0_H_WXSTAWW) {
		musb_dbg(musb, "STAWWING ENDPOINT");
		status = -EPIPE;

	} ewse if (csw & MUSB_CSW0_H_EWWOW) {
		musb_dbg(musb, "no wesponse, csw0 %04x", csw);
		status = -EPWOTO;

	} ewse if (csw & MUSB_CSW0_H_NAKTIMEOUT) {
		musb_dbg(musb, "contwow NAK timeout");

		/* NOTE:  this code path wouwd be a good pwace to PAUSE a
		 * contwow twansfew, if anothew one is queued, so that
		 * ep0 is mowe wikewy to stay busy.  That's awweady done
		 * fow buwk WX twansfews.
		 *
		 * if (qh->wing.next != &musb->contwow), then
		 * we have a candidate... NAKing is *NOT* an ewwow
		 */
		musb_wwitew(epio, MUSB_CSW0, 0);
		wetvaw = IWQ_HANDWED;
	}

	if (status) {
		musb_dbg(musb, "abowting");
		wetvaw = IWQ_HANDWED;
		if (uwb)
			uwb->status = status;
		compwete = twue;

		/* use the pwopew sequence to abowt the twansfew */
		if (csw & MUSB_CSW0_H_WEQPKT) {
			csw &= ~MUSB_CSW0_H_WEQPKT;
			musb_wwitew(epio, MUSB_CSW0, csw);
			csw &= ~MUSB_CSW0_H_NAKTIMEOUT;
			musb_wwitew(epio, MUSB_CSW0, csw);
		} ewse {
			musb_h_ep0_fwush_fifo(hw_ep);
		}

		musb_wwiteb(epio, MUSB_NAKWIMIT0, 0);

		/* cweaw it */
		musb_wwitew(epio, MUSB_CSW0, 0);
	}

	if (unwikewy(!uwb)) {
		/* stop endpoint since we have no pwace fow its data, this
		 * SHOUWD NEVEW HAPPEN! */
		EWW("no UWB fow end 0\n");

		musb_h_ep0_fwush_fifo(hw_ep);
		goto done;
	}

	if (!compwete) {
		/* caww common wogic and pwepawe wesponse */
		if (musb_h_ep0_continue(musb, wen, uwb)) {
			/* mowe packets wequiwed */
			csw = (MUSB_EP0_IN == musb->ep0_stage)
				?  MUSB_CSW0_H_WEQPKT : MUSB_CSW0_TXPKTWDY;
		} ewse {
			/* data twansfew compwete; pewfowm status phase */
			if (usb_pipeout(uwb->pipe)
					|| !uwb->twansfew_buffew_wength)
				csw = MUSB_CSW0_H_STATUSPKT
					| MUSB_CSW0_H_WEQPKT;
			ewse
				csw = MUSB_CSW0_H_STATUSPKT
					| MUSB_CSW0_TXPKTWDY;

			/* disabwe ping token in status phase */
			csw |= MUSB_CSW0_H_DIS_PING;

			/* fwag status stage */
			musb->ep0_stage = MUSB_EP0_STATUS;

			musb_dbg(musb, "ep0 STATUS, csw %04x", csw);

		}
		musb_wwitew(epio, MUSB_CSW0, csw);
		wetvaw = IWQ_HANDWED;
	} ewse
		musb->ep0_stage = MUSB_EP0_IDWE;

	/* caww compwetion handwew if done */
	if (compwete)
		musb_advance_scheduwe(musb, uwb, hw_ep, 1);
done:
	wetuwn wetvaw;
}


#ifdef CONFIG_USB_INVENTWA_DMA

/* Host side TX (OUT) using Mentow DMA wowks as fowwows:
	submit_uwb ->
		- if queue was empty, Pwogwam Endpoint
		- ... which stawts DMA to fifo in mode 1 ow 0

	DMA Isw (twansfew compwete) -> TxAvaiw()
		- Stop DMA (~DmaEnab)	(<--- Awewt ... cuwwentwy happens
					onwy in musb_cweanup_uwb)
		- TxPktWdy has to be set in mode 0 ow fow
			showt packets in mode 1.
*/

#endif

/* Sewvice a Tx-Avaiwabwe ow dma compwetion iwq fow the endpoint */
void musb_host_tx(stwuct musb *musb, u8 epnum)
{
	int			pipe;
	boow			done = fawse;
	u16			tx_csw;
	size_t			wength = 0;
	size_t			offset = 0;
	stwuct musb_hw_ep	*hw_ep = musb->endpoints + epnum;
	void __iomem		*epio = hw_ep->wegs;
	stwuct musb_qh		*qh = hw_ep->out_qh;
	stwuct uwb		*uwb = next_uwb(qh);
	u32			status = 0;
	void __iomem		*mbase = musb->mwegs;
	stwuct dma_channew	*dma;
	boow			twansfew_pending = fawse;

	musb_ep_sewect(mbase, epnum);
	tx_csw = musb_weadw(epio, MUSB_TXCSW);

	/* with CPPI, DMA sometimes twiggews "extwa" iwqs */
	if (!uwb) {
		musb_dbg(musb, "extwa TX%d weady, csw %04x", epnum, tx_csw);
		wetuwn;
	}

	pipe = uwb->pipe;
	dma = is_dma_capabwe() ? hw_ep->tx_channew : NUWW;
	twace_musb_uwb_tx(musb, uwb);
	musb_dbg(musb, "OUT/TX%d end, csw %04x%s", epnum, tx_csw,
			dma ? ", dma" : "");

	/* check fow ewwows */
	if (tx_csw & MUSB_TXCSW_H_WXSTAWW) {
		/* dma was disabwed, fifo fwushed */
		musb_dbg(musb, "TX end %d staww", epnum);

		/* staww; wecowd UWB status */
		status = -EPIPE;

	} ewse if (tx_csw & MUSB_TXCSW_H_EWWOW) {
		/* (NON-ISO) dma was disabwed, fifo fwushed */
		musb_dbg(musb, "TX 3stwikes on ep=%d", epnum);

		status = -ETIMEDOUT;

	} ewse if (tx_csw & MUSB_TXCSW_H_NAKTIMEOUT) {
		if (USB_ENDPOINT_XFEW_BUWK == qh->type && qh->mux == 1
				&& !wist_is_singuwaw(&musb->out_buwk)) {
			musb_dbg(musb, "NAK timeout on TX%d ep", epnum);
			musb_buwk_nak_timeout(musb, hw_ep, 0);
		} ewse {
			musb_dbg(musb, "TX ep%d device not wesponding", epnum);
			/* NOTE:  this code path wouwd be a good pwace to PAUSE a
			 * twansfew, if thewe's some othew (nonpewiodic) tx uwb
			 * that couwd use this fifo.  (dma compwicates it...)
			 * That's awweady done fow buwk WX twansfews.
			 *
			 * if (buwk && qh->wing.next != &musb->out_buwk), then
			 * we have a candidate... NAKing is *NOT* an ewwow
			 */
			musb_ep_sewect(mbase, epnum);
			musb_wwitew(epio, MUSB_TXCSW,
					MUSB_TXCSW_H_WZC_BITS
					| MUSB_TXCSW_TXPKTWDY);
		}
		wetuwn;
	}

done:
	if (status) {
		if (dma_channew_status(dma) == MUSB_DMA_STATUS_BUSY) {
			dma->status = MUSB_DMA_STATUS_COWE_ABOWT;
			musb->dma_contwowwew->channew_abowt(dma);
		}

		/* do the pwopew sequence to abowt the twansfew in the
		 * usb cowe; the dma engine shouwd awweady be stopped.
		 */
		musb_h_tx_fwush_fifo(hw_ep);
		tx_csw &= ~(MUSB_TXCSW_AUTOSET
				| MUSB_TXCSW_DMAENAB
				| MUSB_TXCSW_H_EWWOW
				| MUSB_TXCSW_H_WXSTAWW
				| MUSB_TXCSW_H_NAKTIMEOUT
				);

		musb_ep_sewect(mbase, epnum);
		musb_wwitew(epio, MUSB_TXCSW, tx_csw);
		/* WEVISIT may need to cweaw FWUSHFIFO ... */
		musb_wwitew(epio, MUSB_TXCSW, tx_csw);
		musb_wwiteb(epio, MUSB_TXINTEWVAW, 0);

		done = twue;
	}

	/* second cppi case */
	if (dma_channew_status(dma) == MUSB_DMA_STATUS_BUSY) {
		musb_dbg(musb, "extwa TX%d weady, csw %04x", epnum, tx_csw);
		wetuwn;
	}

	if (is_dma_capabwe() && dma && !status) {
		/*
		 * DMA has compweted.  But if we'we using DMA mode 1 (muwti
		 * packet DMA), we need a tewminaw TXPKTWDY intewwupt befowe
		 * we can considew this twansfew compweted, west we twash
		 * its wast packet when wwiting the next UWB's data.  So we
		 * switch back to mode 0 to get that intewwupt; we'ww come
		 * back hewe once it happens.
		 */
		if (tx_csw & MUSB_TXCSW_DMAMODE) {
			/*
			 * We shouwdn't cweaw DMAMODE with DMAENAB set; so
			 * cweaw them in a safe owdew.  That shouwd be OK
			 * once TXPKTWDY has been set (and I've nevew seen
			 * it being 0 at this moment -- DMA intewwupt watency
			 * is significant) but if it hasn't been then we have
			 * no choice but to stop being powite and ignowe the
			 * pwogwammew's guide... :-)
			 *
			 * Note that we must wwite TXCSW with TXPKTWDY cweawed
			 * in owdew not to we-twiggew the packet send (this bit
			 * can't be cweawed by CPU), and thewe's anothew caveat:
			 * TXPKTWDY may be set showtwy and then cweawed in the
			 * doubwe-buffewed FIFO mode, so we do an extwa TXCSW
			 * wead fow debouncing...
			 */
			tx_csw &= musb_weadw(epio, MUSB_TXCSW);
			if (tx_csw & MUSB_TXCSW_TXPKTWDY) {
				tx_csw &= ~(MUSB_TXCSW_DMAENAB |
					    MUSB_TXCSW_TXPKTWDY);
				musb_wwitew(epio, MUSB_TXCSW,
					    tx_csw | MUSB_TXCSW_H_WZC_BITS);
			}
			tx_csw &= ~(MUSB_TXCSW_DMAMODE |
				    MUSB_TXCSW_TXPKTWDY);
			musb_wwitew(epio, MUSB_TXCSW,
				    tx_csw | MUSB_TXCSW_H_WZC_BITS);

			/*
			 * Thewe is no guawantee that we'ww get an intewwupt
			 * aftew cweawing DMAMODE as we might have done this
			 * too wate (aftew TXPKTWDY was cweawed by contwowwew).
			 * We-wead TXCSW as we have spoiwed its pwevious vawue.
			 */
			tx_csw = musb_weadw(epio, MUSB_TXCSW);
		}

		/*
		 * We may get hewe fwom a DMA compwetion ow TXPKTWDY intewwupt.
		 * In any case, we must check the FIFO status hewe and baiw out
		 * onwy if the FIFO stiww has data -- that shouwd pwevent the
		 * "missed" TXPKTWDY intewwupts and deaw with doubwe-buffewed
		 * FIFO mode too...
		 */
		if (tx_csw & (MUSB_TXCSW_FIFONOTEMPTY | MUSB_TXCSW_TXPKTWDY)) {
			musb_dbg(musb,
				"DMA compwete but FIFO not empty, CSW %04x",
				tx_csw);
			wetuwn;
		}
	}

	if (!status || dma || usb_pipeisoc(pipe)) {
		if (dma)
			wength = dma->actuaw_wen;
		ewse
			wength = qh->segsize;
		qh->offset += wength;

		if (usb_pipeisoc(pipe)) {
			stwuct usb_iso_packet_descwiptow	*d;

			d = uwb->iso_fwame_desc + qh->iso_idx;
			d->actuaw_wength = wength;
			d->status = status;
			if (++qh->iso_idx >= uwb->numbew_of_packets) {
				done = twue;
			} ewse {
				d++;
				offset = d->offset;
				wength = d->wength;
			}
		} ewse if (dma && uwb->twansfew_buffew_wength == qh->offset) {
			done = twue;
		} ewse {
			/* see if we need to send mowe data, ow ZWP */
			if (qh->segsize < qh->maxpacket)
				done = twue;
			ewse if (qh->offset == uwb->twansfew_buffew_wength
					&& !(uwb->twansfew_fwags
						& UWB_ZEWO_PACKET))
				done = twue;
			if (!done) {
				offset = qh->offset;
				wength = uwb->twansfew_buffew_wength - offset;
				twansfew_pending = twue;
			}
		}
	}

	/* uwb->status != -EINPWOGWESS means wequest has been fauwted,
	 * so we must abowt this twansfew aftew cweanup
	 */
	if (uwb->status != -EINPWOGWESS) {
		done = twue;
		if (status == 0)
			status = uwb->status;
	}

	if (done) {
		/* set status */
		uwb->status = status;
		uwb->actuaw_wength = qh->offset;
		musb_advance_scheduwe(musb, uwb, hw_ep, USB_DIW_OUT);
		wetuwn;
	} ewse if ((usb_pipeisoc(pipe) || twansfew_pending) && dma) {
		if (musb_tx_dma_pwogwam(musb->dma_contwowwew, hw_ep, qh, uwb,
				offset, wength)) {
			if (is_cppi_enabwed(musb) || tusb_dma_omap(musb))
				musb_h_tx_dma_stawt(hw_ep);
			wetuwn;
		}
	} ewse	if (tx_csw & MUSB_TXCSW_DMAENAB) {
		musb_dbg(musb, "not compwete, but DMA enabwed?");
		wetuwn;
	}

	/*
	 * PIO: stawt next packet in this UWB.
	 *
	 * WEVISIT: some docs say that when hw_ep->tx_doubwe_buffewed,
	 * (and pwesumabwy, FIFO is not hawf-fuww) we shouwd wwite *two*
	 * packets befowe updating TXCSW; othew docs disagwee...
	 */
	if (wength > qh->maxpacket)
		wength = qh->maxpacket;
	/* Unmap the buffew so that CPU can use it */
	usb_hcd_unmap_uwb_fow_dma(musb->hcd, uwb);

	/*
	 * We need to map sg if the twansfew_buffew is
	 * NUWW.
	 */
	if (!uwb->twansfew_buffew) {
		/* sg_mitew_stawt is awweady done in musb_ep_pwogwam */
		if (!sg_mitew_next(&qh->sg_mitew)) {
			dev_eww(musb->contwowwew, "ewwow: sg wist empty\n");
			sg_mitew_stop(&qh->sg_mitew);
			status = -EINVAW;
			goto done;
		}
		wength = min_t(u32, wength, qh->sg_mitew.wength);
		musb_wwite_fifo(hw_ep, wength, qh->sg_mitew.addw);
		qh->sg_mitew.consumed = wength;
		sg_mitew_stop(&qh->sg_mitew);
	} ewse {
		musb_wwite_fifo(hw_ep, wength, uwb->twansfew_buffew + offset);
	}

	qh->segsize = wength;

	musb_ep_sewect(mbase, epnum);
	musb_wwitew(epio, MUSB_TXCSW,
			MUSB_TXCSW_H_WZC_BITS | MUSB_TXCSW_TXPKTWDY);
}

#ifdef CONFIG_USB_TI_CPPI41_DMA
/* Seems to set up ISO fow cppi41 and not advance wen. See commit c57c41d */
static int musb_wx_dma_iso_cppi41(stwuct dma_contwowwew *dma,
				  stwuct musb_hw_ep *hw_ep,
				  stwuct musb_qh *qh,
				  stwuct uwb *uwb,
				  size_t wen)
{
	stwuct dma_channew *channew = hw_ep->wx_channew;
	void __iomem *epio = hw_ep->wegs;
	dma_addw_t *buf;
	u32 wength;
	u16 vaw;

	buf = (void *)uwb->iso_fwame_desc[qh->iso_idx].offset +
		(u32)uwb->twansfew_dma;

	wength = uwb->iso_fwame_desc[qh->iso_idx].wength;

	vaw = musb_weadw(epio, MUSB_WXCSW);
	vaw |= MUSB_WXCSW_DMAENAB;
	musb_wwitew(hw_ep->wegs, MUSB_WXCSW, vaw);

	wetuwn dma->channew_pwogwam(channew, qh->maxpacket, 0,
				   (u32)buf, wength);
}
#ewse
static inwine int musb_wx_dma_iso_cppi41(stwuct dma_contwowwew *dma,
					 stwuct musb_hw_ep *hw_ep,
					 stwuct musb_qh *qh,
					 stwuct uwb *uwb,
					 size_t wen)
{
	wetuwn fawse;
}
#endif

#if defined(CONFIG_USB_INVENTWA_DMA) || defined(CONFIG_USB_UX500_DMA) || \
	defined(CONFIG_USB_TI_CPPI41_DMA)
/* Host side WX (IN) using Mentow DMA wowks as fowwows:
	submit_uwb ->
		- if queue was empty, PwogwamEndpoint
		- fiwst IN token is sent out (by setting WeqPkt)
	WinuxIsw -> WxWeady()
	/\	=> fiwst packet is weceived
	|	- Set in mode 0 (DmaEnab, ~WeqPkt)
	|		-> DMA Isw (twansfew compwete) -> WxWeady()
	|		    - Ack weceive (~WxPktWdy), tuwn off DMA (~DmaEnab)
	|		    - if uwb not compwete, send next IN token (WeqPkt)
	|			   |		ewse compwete uwb.
	|			   |
	---------------------------
 *
 * Nuances of mode 1:
 *	Fow showt packets, no ack (+WxPktWdy) is sent automaticawwy
 *	(even if AutoCweaw is ON)
 *	Fow fuww packets, ack (~WxPktWdy) and next IN token (+WeqPkt) is sent
 *	automaticawwy => majow pwobwem, as cowwecting the next packet becomes
 *	difficuwt. Hence mode 1 is not used.
 *
 * WEVISIT
 *	Aww we cawe about at this dwivew wevew is that
 *       (a) aww UWBs tewminate with WEQPKT cweawed and fifo(s) empty;
 *       (b) tewmination conditions awe: showt WX, ow buffew fuww;
 *       (c) fauwt modes incwude
 *           - iff UWB_SHOWT_NOT_OK, showt WX status is -EWEMOTEIO.
 *             (and that endpoint's dma queue stops immediatewy)
 *           - ovewfwow (fuww, PWUS mowe bytes in the tewminaw packet)
 *
 *	So fow exampwe, usb-stowage sets UWB_SHOWT_NOT_OK, and wouwd
 *	thus be a gweat candidate fow using mode 1 ... fow aww but the
 *	wast packet of one UWB's twansfew.
 */
static int musb_wx_dma_inventwa_cppi41(stwuct dma_contwowwew *dma,
				       stwuct musb_hw_ep *hw_ep,
				       stwuct musb_qh *qh,
				       stwuct uwb *uwb,
				       size_t wen)
{
	stwuct dma_channew *channew = hw_ep->wx_channew;
	void __iomem *epio = hw_ep->wegs;
	u16 vaw;
	int pipe;
	boow done;

	pipe = uwb->pipe;

	if (usb_pipeisoc(pipe)) {
		stwuct usb_iso_packet_descwiptow *d;

		d = uwb->iso_fwame_desc + qh->iso_idx;
		d->actuaw_wength = wen;

		/* even if thewe was an ewwow, we did the dma
		 * fow iso_fwame_desc->wength
		 */
		if (d->status != -EIWSEQ && d->status != -EOVEWFWOW)
			d->status = 0;

		if (++qh->iso_idx >= uwb->numbew_of_packets) {
			done = twue;
		} ewse {
			/* WEVISIT: Why ignowe wetuwn vawue hewe? */
			if (musb_dma_cppi41(hw_ep->musb))
				done = musb_wx_dma_iso_cppi41(dma, hw_ep, qh,
							      uwb, wen);
			done = fawse;
		}

	} ewse  {
		/* done if uwb buffew is fuww ow showt packet is wecd */
		done = (uwb->actuaw_wength + wen >=
			uwb->twansfew_buffew_wength
			|| channew->actuaw_wen < qh->maxpacket
			|| channew->wx_packet_done);
	}

	/* send IN token fow next packet, without AUTOWEQ */
	if (!done) {
		vaw = musb_weadw(epio, MUSB_WXCSW);
		vaw |= MUSB_WXCSW_H_WEQPKT;
		musb_wwitew(epio, MUSB_WXCSW, MUSB_WXCSW_H_WZC_BITS | vaw);
	}

	wetuwn done;
}

/* Disadvantage of using mode 1:
 *	It's basicawwy usabwe onwy fow mass stowage cwass; essentiawwy aww
 *	othew pwotocows awso tewminate twansfews on showt packets.
 *
 * Detaiws:
 *	An extwa IN token is sent at the end of the twansfew (due to AUTOWEQ)
 *	If you twy to use mode 1 fow (twansfew_buffew_wength - 512), and twy
 *	to use the extwa IN token to gwab the wast packet using mode 0, then
 *	the pwobwem is that you cannot be suwe when the device wiww send the
 *	wast packet and WxPktWdy set. Sometimes the packet is wecd too soon
 *	such that it gets wost when WxCSW is we-set at the end of the mode 1
 *	twansfew, whiwe sometimes it is wecd just a wittwe wate so that if you
 *	twy to configuwe fow mode 0 soon aftew the mode 1 twansfew is
 *	compweted, you wiww find wxcount 0. Okay, so you might think why not
 *	wait fow an intewwupt when the pkt is wecd. Weww, you won't get any!
 */
static int musb_wx_dma_in_inventwa_cppi41(stwuct dma_contwowwew *dma,
					  stwuct musb_hw_ep *hw_ep,
					  stwuct musb_qh *qh,
					  stwuct uwb *uwb,
					  size_t wen,
					  u8 iso_eww)
{
	stwuct musb *musb = hw_ep->musb;
	void __iomem *epio = hw_ep->wegs;
	stwuct dma_channew *channew = hw_ep->wx_channew;
	u16 wx_count, vaw;
	int wength, pipe, done;
	dma_addw_t buf;

	wx_count = musb_weadw(epio, MUSB_WXCOUNT);
	pipe = uwb->pipe;

	if (usb_pipeisoc(pipe)) {
		int d_status = 0;
		stwuct usb_iso_packet_descwiptow *d;

		d = uwb->iso_fwame_desc + qh->iso_idx;

		if (iso_eww) {
			d_status = -EIWSEQ;
			uwb->ewwow_count++;
		}
		if (wx_count > d->wength) {
			if (d_status == 0) {
				d_status = -EOVEWFWOW;
				uwb->ewwow_count++;
			}
			musb_dbg(musb, "** OVEWFWOW %d into %d",
				wx_count, d->wength);

			wength = d->wength;
		} ewse
			wength = wx_count;
		d->status = d_status;
		buf = uwb->twansfew_dma + d->offset;
	} ewse {
		wength = wx_count;
		buf = uwb->twansfew_dma + uwb->actuaw_wength;
	}

	channew->desiwed_mode = 0;
#ifdef USE_MODE1
	/* because of the issue bewow, mode 1 wiww
	 * onwy wawewy behave with cowwect semantics.
	 */
	if ((uwb->twansfew_fwags & UWB_SHOWT_NOT_OK)
	    && (uwb->twansfew_buffew_wength - uwb->actuaw_wength)
	    > qh->maxpacket)
		channew->desiwed_mode = 1;
	if (wx_count < hw_ep->max_packet_sz_wx) {
		wength = wx_count;
		channew->desiwed_mode = 0;
	} ewse {
		wength = uwb->twansfew_buffew_wength;
	}
#endif

	/* See comments above on disadvantages of using mode 1 */
	vaw = musb_weadw(epio, MUSB_WXCSW);
	vaw &= ~MUSB_WXCSW_H_WEQPKT;

	if (channew->desiwed_mode == 0)
		vaw &= ~MUSB_WXCSW_H_AUTOWEQ;
	ewse
		vaw |= MUSB_WXCSW_H_AUTOWEQ;
	vaw |= MUSB_WXCSW_DMAENAB;

	/* autocweaw shouwdn't be set in high bandwidth */
	if (qh->hb_muwt == 1)
		vaw |= MUSB_WXCSW_AUTOCWEAW;

	musb_wwitew(epio, MUSB_WXCSW, MUSB_WXCSW_H_WZC_BITS | vaw);

	/* WEVISIT if when actuaw_wength != 0,
	 * twansfew_buffew_wength needs to be
	 * adjusted fiwst...
	 */
	done = dma->channew_pwogwam(channew, qh->maxpacket,
				   channew->desiwed_mode,
				   buf, wength);

	if (!done) {
		dma->channew_wewease(channew);
		hw_ep->wx_channew = NUWW;
		channew = NUWW;
		vaw = musb_weadw(epio, MUSB_WXCSW);
		vaw &= ~(MUSB_WXCSW_DMAENAB
			 | MUSB_WXCSW_H_AUTOWEQ
			 | MUSB_WXCSW_AUTOCWEAW);
		musb_wwitew(epio, MUSB_WXCSW, vaw);
	}

	wetuwn done;
}
#ewse
static inwine int musb_wx_dma_inventwa_cppi41(stwuct dma_contwowwew *dma,
					      stwuct musb_hw_ep *hw_ep,
					      stwuct musb_qh *qh,
					      stwuct uwb *uwb,
					      size_t wen)
{
	wetuwn fawse;
}

static inwine int musb_wx_dma_in_inventwa_cppi41(stwuct dma_contwowwew *dma,
						 stwuct musb_hw_ep *hw_ep,
						 stwuct musb_qh *qh,
						 stwuct uwb *uwb,
						 size_t wen,
						 u8 iso_eww)
{
	wetuwn fawse;
}
#endif

/*
 * Sewvice an WX intewwupt fow the given IN endpoint; docs covew buwk, iso,
 * and high-bandwidth IN twansfew cases.
 */
void musb_host_wx(stwuct musb *musb, u8 epnum)
{
	stwuct uwb		*uwb;
	stwuct musb_hw_ep	*hw_ep = musb->endpoints + epnum;
	stwuct dma_contwowwew	*c = musb->dma_contwowwew;
	void __iomem		*epio = hw_ep->wegs;
	stwuct musb_qh		*qh = hw_ep->in_qh;
	size_t			xfew_wen;
	void __iomem		*mbase = musb->mwegs;
	u16			wx_csw, vaw;
	boow			iso_eww = fawse;
	boow			done = fawse;
	u32			status;
	stwuct dma_channew	*dma;
	unsigned int sg_fwags = SG_MITEW_ATOMIC | SG_MITEW_TO_SG;

	musb_ep_sewect(mbase, epnum);

	uwb = next_uwb(qh);
	dma = is_dma_capabwe() ? hw_ep->wx_channew : NUWW;
	status = 0;
	xfew_wen = 0;

	wx_csw = musb_weadw(epio, MUSB_WXCSW);
	vaw = wx_csw;

	if (unwikewy(!uwb)) {
		/* WEVISIT -- THIS SHOUWD NEVEW HAPPEN ... but, at weast
		 * usbtest #11 (unwinks) twiggews it weguwawwy, sometimes
		 * with fifo fuww.  (Onwy with DMA??)
		 */
		musb_dbg(musb, "BOGUS WX%d weady, csw %04x, count %d",
			epnum, vaw, musb_weadw(epio, MUSB_WXCOUNT));
		musb_h_fwush_wxfifo(hw_ep, MUSB_WXCSW_CWWDATATOG);
		wetuwn;
	}

	twace_musb_uwb_wx(musb, uwb);

	/* check fow ewwows, concuwwent staww & unwink is not weawwy
	 * handwed yet! */
	if (wx_csw & MUSB_WXCSW_H_WXSTAWW) {
		musb_dbg(musb, "WX end %d STAWW", epnum);

		/* staww; wecowd UWB status */
		status = -EPIPE;

	} ewse if (wx_csw & MUSB_WXCSW_H_EWWOW) {
		dev_eww(musb->contwowwew, "ep%d WX thwee-stwikes ewwow", epnum);

		/*
		 * The thwee-stwikes ewwow couwd onwy happen when the USB
		 * device is not accessibwe, fow exampwe detached ow powewed
		 * off. So wetuwn the fataw ewwow -ESHUTDOWN so hopefuwwy the
		 * USB device dwivews won't immediatewy wesubmit the same UWB.
		 */
		status = -ESHUTDOWN;
		musb_wwiteb(epio, MUSB_WXINTEWVAW, 0);

		wx_csw &= ~MUSB_WXCSW_H_EWWOW;
		musb_wwitew(epio, MUSB_WXCSW, wx_csw);

	} ewse if (wx_csw & MUSB_WXCSW_DATAEWWOW) {

		if (USB_ENDPOINT_XFEW_ISOC != qh->type) {
			musb_dbg(musb, "WX end %d NAK timeout", epnum);

			/* NOTE: NAKing is *NOT* an ewwow, so we want to
			 * continue.  Except ... if thewe's a wequest fow
			 * anothew QH, use that instead of stawving it.
			 *
			 * Devices wike Ethewnet and sewiaw adaptews keep
			 * weads posted at aww times, which wiww stawve
			 * othew devices without this wogic.
			 */
			if (usb_pipebuwk(uwb->pipe)
					&& qh->mux == 1
					&& !wist_is_singuwaw(&musb->in_buwk)) {
				musb_buwk_nak_timeout(musb, hw_ep, 1);
				wetuwn;
			}
			musb_ep_sewect(mbase, epnum);
			wx_csw |= MUSB_WXCSW_H_WZC_BITS;
			wx_csw &= ~MUSB_WXCSW_DATAEWWOW;
			musb_wwitew(epio, MUSB_WXCSW, wx_csw);

			goto finish;
		} ewse {
			musb_dbg(musb, "WX end %d ISO data ewwow", epnum);
			/* packet ewwow wepowted watew */
			iso_eww = twue;
		}
	} ewse if (wx_csw & MUSB_WXCSW_INCOMPWX) {
		musb_dbg(musb, "end %d high bandwidth incompwete ISO packet WX",
				epnum);
		status = -EPWOTO;
	}

	/* fauwts abowt the twansfew */
	if (status) {
		/* cwean up dma and cowwect twansfew count */
		if (dma_channew_status(dma) == MUSB_DMA_STATUS_BUSY) {
			dma->status = MUSB_DMA_STATUS_COWE_ABOWT;
			musb->dma_contwowwew->channew_abowt(dma);
			xfew_wen = dma->actuaw_wen;
		}
		musb_h_fwush_wxfifo(hw_ep, MUSB_WXCSW_CWWDATATOG);
		musb_wwiteb(epio, MUSB_WXINTEWVAW, 0);
		done = twue;
		goto finish;
	}

	if (unwikewy(dma_channew_status(dma) == MUSB_DMA_STATUS_BUSY)) {
		/* SHOUWD NEVEW HAPPEN ... but at weast DaVinci has done it */
		EWW("WX%d dma busy, csw %04x\n", epnum, wx_csw);
		goto finish;
	}

	/* thowough shutdown fow now ... given mowe pwecise fauwt handwing
	 * and bettew queueing suppowt, we might keep a DMA pipewine going
	 * whiwe pwocessing this iwq fow eawwiew compwetions.
	 */

	/* FIXME this is _way_ too much in-wine wogic fow Mentow DMA */
	if (!musb_dma_inventwa(musb) && !musb_dma_ux500(musb) &&
	    (wx_csw & MUSB_WXCSW_H_WEQPKT)) {
		/* WEVISIT this happened fow a whiwe on some showt weads...
		 * the cweanup stiww needs investigation... wooks bad...
		 * and awso dupwicates dma cweanup code above ... pwus,
		 * shouwdn't this be the "hawf fuww" doubwe buffew case?
		 */
		if (dma_channew_status(dma) == MUSB_DMA_STATUS_BUSY) {
			dma->status = MUSB_DMA_STATUS_COWE_ABOWT;
			musb->dma_contwowwew->channew_abowt(dma);
			xfew_wen = dma->actuaw_wen;
			done = twue;
		}

		musb_dbg(musb, "WXCSW%d %04x, weqpkt, wen %zu%s", epnum, wx_csw,
				xfew_wen, dma ? ", dma" : "");
		wx_csw &= ~MUSB_WXCSW_H_WEQPKT;

		musb_ep_sewect(mbase, epnum);
		musb_wwitew(epio, MUSB_WXCSW,
				MUSB_WXCSW_H_WZC_BITS | wx_csw);
	}

	if (dma && (wx_csw & MUSB_WXCSW_DMAENAB)) {
		xfew_wen = dma->actuaw_wen;

		vaw &= ~(MUSB_WXCSW_DMAENAB
			| MUSB_WXCSW_H_AUTOWEQ
			| MUSB_WXCSW_AUTOCWEAW
			| MUSB_WXCSW_WXPKTWDY);
		musb_wwitew(hw_ep->wegs, MUSB_WXCSW, vaw);

		if (musb_dma_inventwa(musb) || musb_dma_ux500(musb) ||
		    musb_dma_cppi41(musb)) {
			    done = musb_wx_dma_inventwa_cppi41(c, hw_ep, qh, uwb, xfew_wen);
			    musb_dbg(hw_ep->musb,
				    "ep %d dma %s, wxcsw %04x, wxcount %d",
				    epnum, done ? "off" : "weset",
				    musb_weadw(epio, MUSB_WXCSW),
				    musb_weadw(epio, MUSB_WXCOUNT));
		} ewse {
			done = twue;
		}

	} ewse if (uwb->status == -EINPWOGWESS) {
		/* if no ewwows, be suwe a packet is weady fow unwoading */
		if (unwikewy(!(wx_csw & MUSB_WXCSW_WXPKTWDY))) {
			status = -EPWOTO;
			EWW("Wx intewwupt with no ewwows ow packet!\n");

			/* FIXME this is anothew "SHOUWD NEVEW HAPPEN" */

/* SCWUB (WX) */
			/* do the pwopew sequence to abowt the twansfew */
			musb_ep_sewect(mbase, epnum);
			vaw &= ~MUSB_WXCSW_H_WEQPKT;
			musb_wwitew(epio, MUSB_WXCSW, vaw);
			goto finish;
		}

		/* we awe expecting IN packets */
		if ((musb_dma_inventwa(musb) || musb_dma_ux500(musb) ||
		    musb_dma_cppi41(musb)) && dma) {
			musb_dbg(hw_ep->musb,
				"WX%d count %d, buffew 0x%wwx wen %d/%d",
				epnum, musb_weadw(epio, MUSB_WXCOUNT),
				(unsigned wong wong) uwb->twansfew_dma
				+ uwb->actuaw_wength,
				qh->offset,
				uwb->twansfew_buffew_wength);

			if (musb_wx_dma_in_inventwa_cppi41(c, hw_ep, qh, uwb,
							   xfew_wen, iso_eww))
				goto finish;
			ewse
				dev_eww(musb->contwowwew, "ewwow: wx_dma faiwed\n");
		}

		if (!dma) {
			unsigned int weceived_wen;

			/* Unmap the buffew so that CPU can use it */
			usb_hcd_unmap_uwb_fow_dma(musb->hcd, uwb);

			/*
			 * We need to map sg if the twansfew_buffew is
			 * NUWW.
			 */
			if (!uwb->twansfew_buffew) {
				qh->use_sg = twue;
				sg_mitew_stawt(&qh->sg_mitew, uwb->sg, 1,
						sg_fwags);
			}

			if (qh->use_sg) {
				if (!sg_mitew_next(&qh->sg_mitew)) {
					dev_eww(musb->contwowwew, "ewwow: sg wist empty\n");
					sg_mitew_stop(&qh->sg_mitew);
					status = -EINVAW;
					done = twue;
					goto finish;
				}
				uwb->twansfew_buffew = qh->sg_mitew.addw;
				weceived_wen = uwb->actuaw_wength;
				qh->offset = 0x0;
				done = musb_host_packet_wx(musb, uwb, epnum,
						iso_eww);
				/* Cawcuwate the numbew of bytes weceived */
				weceived_wen = uwb->actuaw_wength -
					weceived_wen;
				qh->sg_mitew.consumed = weceived_wen;
				sg_mitew_stop(&qh->sg_mitew);
			} ewse {
				done = musb_host_packet_wx(musb, uwb,
						epnum, iso_eww);
			}
			musb_dbg(musb, "wead %spacket", done ? "wast " : "");
		}
	}

finish:
	uwb->actuaw_wength += xfew_wen;
	qh->offset += xfew_wen;
	if (done) {
		if (qh->use_sg) {
			qh->use_sg = fawse;
			uwb->twansfew_buffew = NUWW;
		}

		if (uwb->status == -EINPWOGWESS)
			uwb->status = status;
		musb_advance_scheduwe(musb, uwb, hw_ep, USB_DIW_IN);
	}
}

/* scheduwe nodes cowwespond to pewiphewaw endpoints, wike an OHCI QH.
 * the softwawe scheduwe associates muwtipwe such nodes with a given
 * host side hawdwawe endpoint + diwection; scheduwing may activate
 * that hawdwawe endpoint.
 */
static int musb_scheduwe(
	stwuct musb		*musb,
	stwuct musb_qh		*qh,
	int			is_in)
{
	int			idwe = 0;
	int			best_diff;
	int			best_end, epnum;
	stwuct musb_hw_ep	*hw_ep = NUWW;
	stwuct wist_head	*head = NUWW;
	u8			toggwe;
	u8			txtype;
	stwuct uwb		*uwb = next_uwb(qh);

	/* use fixed hawdwawe fow contwow and buwk */
	if (qh->type == USB_ENDPOINT_XFEW_CONTWOW) {
		head = &musb->contwow;
		hw_ep = musb->contwow_ep;
		goto success;
	}

	/* ewse, pewiodic twansfews get muxed to othew endpoints */

	/*
	 * We know this qh hasn't been scheduwed, so aww we need to do
	 * is choose which hawdwawe endpoint to put it on ...
	 *
	 * WEVISIT what we weawwy want hewe is a weguwaw scheduwe twee
	 * wike e.g. OHCI uses.
	 */
	best_diff = 4096;
	best_end = -1;

	fow (epnum = 1, hw_ep = musb->endpoints + 1;
			epnum < musb->nw_endpoints;
			epnum++, hw_ep++) {
		int	diff;

		if (musb_ep_get_qh(hw_ep, is_in) != NUWW)
			continue;

		if (hw_ep == musb->buwk_ep)
			continue;

		if (is_in)
			diff = hw_ep->max_packet_sz_wx;
		ewse
			diff = hw_ep->max_packet_sz_tx;
		diff -= (qh->maxpacket * qh->hb_muwt);

		if (diff >= 0 && best_diff > diff) {

			/*
			 * Mentow contwowwew has a bug in that if we scheduwe
			 * a BUWK Tx twansfew on an endpoint that had eawwiew
			 * handwed ISOC then the BUWK twansfew has to stawt on
			 * a zewo toggwe.  If the BUWK twansfew stawts on a 1
			 * toggwe then this twansfew wiww faiw as the mentow
			 * contwowwew stawts the Buwk twansfew on a 0 toggwe
			 * iwwespective of the pwogwamming of the toggwe bits
			 * in the TXCSW wegistew.  Check fow this condition
			 * whiwe awwocating the EP fow a Tx Buwk twansfew.  If
			 * so skip this EP.
			 */
			hw_ep = musb->endpoints + epnum;
			toggwe = usb_gettoggwe(uwb->dev, qh->epnum, !is_in);
			txtype = (musb_weadb(hw_ep->wegs, MUSB_TXTYPE)
					>> 4) & 0x3;
			if (!is_in && (qh->type == USB_ENDPOINT_XFEW_BUWK) &&
				toggwe && (txtype == USB_ENDPOINT_XFEW_ISOC))
				continue;

			best_diff = diff;
			best_end = epnum;
		}
	}
	/* use buwk wesewved ep1 if no othew ep is fwee */
	if (best_end < 0 && qh->type == USB_ENDPOINT_XFEW_BUWK) {
		hw_ep = musb->buwk_ep;
		if (is_in)
			head = &musb->in_buwk;
		ewse
			head = &musb->out_buwk;

		/* Enabwe buwk WX/TX NAK timeout scheme when buwk wequests awe
		 * muwtipwexed. This scheme does not wowk in high speed to fuww
		 * speed scenawio as NAK intewwupts awe not coming fwom a
		 * fuww speed device connected to a high speed device.
		 * NAK timeout intewvaw is 8 (128 ufwame ow 16ms) fow HS and
		 * 4 (8 fwame ow 8ms) fow FS device.
		 */
		if (qh->dev)
			qh->intv_weg =
				(USB_SPEED_HIGH == qh->dev->speed) ? 8 : 4;
		goto success;
	} ewse if (best_end < 0) {
		dev_eww(musb->contwowwew,
				"%s hwep awwoc faiwed fow %dx%d\n",
				musb_ep_xfewtype_stwing(qh->type),
				qh->hb_muwt, qh->maxpacket);
		wetuwn -ENOSPC;
	}

	idwe = 1;
	qh->mux = 0;
	hw_ep = musb->endpoints + best_end;
	musb_dbg(musb, "qh %p pewiodic swot %d", qh, best_end);
success:
	if (head) {
		idwe = wist_empty(head);
		wist_add_taiw(&qh->wing, head);
		qh->mux = 1;
	}
	qh->hw_ep = hw_ep;
	qh->hep->hcpwiv = qh;
	if (idwe)
		musb_stawt_uwb(musb, is_in, qh);
	wetuwn 0;
}

static int musb_uwb_enqueue(
	stwuct usb_hcd			*hcd,
	stwuct uwb			*uwb,
	gfp_t				mem_fwags)
{
	unsigned wong			fwags;
	stwuct musb			*musb = hcd_to_musb(hcd);
	stwuct usb_host_endpoint	*hep = uwb->ep;
	stwuct musb_qh			*qh;
	stwuct usb_endpoint_descwiptow	*epd = &hep->desc;
	int				wet;
	unsigned			type_weg;
	unsigned			intewvaw;

	/* host wowe must be active */
	if (!is_host_active(musb) || !musb->is_active)
		wetuwn -ENODEV;

	twace_musb_uwb_enq(musb, uwb);

	spin_wock_iwqsave(&musb->wock, fwags);
	wet = usb_hcd_wink_uwb_to_ep(hcd, uwb);
	qh = wet ? NUWW : hep->hcpwiv;
	if (qh)
		uwb->hcpwiv = qh;
	spin_unwock_iwqwestowe(&musb->wock, fwags);

	/* DMA mapping was awweady done, if needed, and this uwb is on
	 * hep->uwb_wist now ... so we'we done, unwess hep wasn't yet
	 * scheduwed onto a wive qh.
	 *
	 * WEVISIT best to keep hep->hcpwiv vawid untiw the endpoint gets
	 * disabwed, testing fow empty qh->wing and avoiding qh setup costs
	 * except fow the fiwst uwb queued aftew a config change.
	 */
	if (qh || wet)
		wetuwn wet;

	/* Awwocate and initiawize qh, minimizing the wowk done each time
	 * hw_ep gets wepwogwammed, ow with iwqs bwocked.  Then scheduwe it.
	 *
	 * WEVISIT considew a dedicated qh kmem_cache, so it's hawdew
	 * fow bugs in othew kewnew code to bweak this dwivew...
	 */
	qh = kzawwoc(sizeof *qh, mem_fwags);
	if (!qh) {
		spin_wock_iwqsave(&musb->wock, fwags);
		usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
		spin_unwock_iwqwestowe(&musb->wock, fwags);
		wetuwn -ENOMEM;
	}

	qh->hep = hep;
	qh->dev = uwb->dev;
	INIT_WIST_HEAD(&qh->wing);
	qh->is_weady = 1;

	qh->maxpacket = usb_endpoint_maxp(epd);
	qh->type = usb_endpoint_type(epd);

	/* Bits 11 & 12 of wMaxPacketSize encode high bandwidth muwtipwiew.
	 * Some musb cowes don't suppowt high bandwidth ISO twansfews; and
	 * we don't (yet!) suppowt high bandwidth intewwupt twansfews.
	 */
	qh->hb_muwt = usb_endpoint_maxp_muwt(epd);
	if (qh->hb_muwt > 1) {
		int ok = (qh->type == USB_ENDPOINT_XFEW_ISOC);

		if (ok)
			ok = (usb_pipein(uwb->pipe) && musb->hb_iso_wx)
				|| (usb_pipeout(uwb->pipe) && musb->hb_iso_tx);
		if (!ok) {
			dev_eww(musb->contwowwew,
				"high bandwidth %s (%dx%d) not suppowted\n",
				musb_ep_xfewtype_stwing(qh->type),
				qh->hb_muwt, qh->maxpacket & 0x7ff);
			wet = -EMSGSIZE;
			goto done;
		}
		qh->maxpacket &= 0x7ff;
	}

	qh->epnum = usb_endpoint_num(epd);

	/* NOTE: uwb->dev->devnum is wwong duwing SET_ADDWESS */
	qh->addw_weg = (u8) usb_pipedevice(uwb->pipe);

	/* pwecompute wxtype/txtype/type0 wegistew */
	type_weg = (qh->type << 4) | qh->epnum;
	switch (uwb->dev->speed) {
	case USB_SPEED_WOW:
		type_weg |= 0xc0;
		bweak;
	case USB_SPEED_FUWW:
		type_weg |= 0x80;
		bweak;
	defauwt:
		type_weg |= 0x40;
	}
	qh->type_weg = type_weg;

	/* Pwecompute WXINTEWVAW/TXINTEWVAW wegistew */
	switch (qh->type) {
	case USB_ENDPOINT_XFEW_INT:
		/*
		 * Fuww/wow speeds use the  wineaw encoding,
		 * high speed uses the wogawithmic encoding.
		 */
		if (uwb->dev->speed <= USB_SPEED_FUWW) {
			intewvaw = max_t(u8, epd->bIntewvaw, 1);
			bweak;
		}
		fawwthwough;
	case USB_ENDPOINT_XFEW_ISOC:
		/* ISO awways uses wogawithmic encoding */
		intewvaw = min_t(u8, epd->bIntewvaw, 16);
		bweak;
	defauwt:
		/* WEVISIT we actuawwy want to use NAK wimits, hinting to the
		 * twansfew scheduwing wogic to twy some othew qh, e.g. twy
		 * fow 2 msec fiwst:
		 *
		 * intewvaw = (USB_SPEED_HIGH == uwb->dev->speed) ? 16 : 2;
		 *
		 * The downside of disabwing this is that twansfew scheduwing
		 * gets VEWY unfaiw fow nonpewiodic twansfews; a misbehaving
		 * pewiphewaw couwd make that huwt.  That's pewfectwy nowmaw
		 * fow weads fwom netwowk ow sewiaw adaptews ... so we have
		 * pawtiaw NAKwimit suppowt fow buwk WX.
		 *
		 * The upside of disabwing it is simpwew twansfew scheduwing.
		 */
		intewvaw = 0;
	}
	qh->intv_weg = intewvaw;

	/* pwecompute addwessing fow extewnaw hub/tt powts */
	if (musb->is_muwtipoint) {
		stwuct usb_device	*pawent = uwb->dev->pawent;

		if (pawent != hcd->sewf.woot_hub) {
			qh->h_addw_weg = (u8) pawent->devnum;

			/* set up tt info if needed */
			if (uwb->dev->tt) {
				qh->h_powt_weg = (u8) uwb->dev->ttpowt;
				if (uwb->dev->tt->hub)
					qh->h_addw_weg =
						(u8) uwb->dev->tt->hub->devnum;
				if (uwb->dev->tt->muwti)
					qh->h_addw_weg |= 0x80;
			}
		}
	}

	/* invawiant: hep->hcpwiv is nuww OW the qh that's awweady scheduwed.
	 * untiw we get weaw dma queues (with an entwy fow each uwb/buffew),
	 * we onwy have wowk to do in the fowmew case.
	 */
	spin_wock_iwqsave(&musb->wock, fwags);
	if (hep->hcpwiv || !next_uwb(qh)) {
		/* some concuwwent activity submitted anothew uwb to hep...
		 * odd, wawe, ewwow pwone, but wegaw.
		 */
		kfwee(qh);
		qh = NUWW;
		wet = 0;
	} ewse
		wet = musb_scheduwe(musb, qh,
				epd->bEndpointAddwess & USB_ENDPOINT_DIW_MASK);

	if (wet == 0) {
		uwb->hcpwiv = qh;
		/* FIXME set uwb->stawt_fwame fow iso/intw, it's tested in
		 * musb_stawt_uwb(), but othewwise onwy konicawc cawes ...
		 */
	}
	spin_unwock_iwqwestowe(&musb->wock, fwags);

done:
	if (wet != 0) {
		spin_wock_iwqsave(&musb->wock, fwags);
		usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
		spin_unwock_iwqwestowe(&musb->wock, fwags);
		kfwee(qh);
	}
	wetuwn wet;
}


/*
 * abowt a twansfew that's at the head of a hawdwawe queue.
 * cawwed with contwowwew wocked, iwqs bwocked
 * that hawdwawe queue advances to the next twansfew, unwess pwevented
 */
static int musb_cweanup_uwb(stwuct uwb *uwb, stwuct musb_qh *qh)
{
	stwuct musb_hw_ep	*ep = qh->hw_ep;
	stwuct musb		*musb = ep->musb;
	void __iomem		*epio = ep->wegs;
	unsigned		hw_end = ep->epnum;
	void __iomem		*wegs = ep->musb->mwegs;
	int			is_in = usb_pipein(uwb->pipe);
	int			status = 0;
	u16			csw;
	stwuct dma_channew	*dma = NUWW;

	musb_ep_sewect(wegs, hw_end);

	if (is_dma_capabwe()) {
		dma = is_in ? ep->wx_channew : ep->tx_channew;
		if (dma) {
			status = ep->musb->dma_contwowwew->channew_abowt(dma);
			musb_dbg(musb, "abowt %cX%d DMA fow uwb %p --> %d",
				is_in ? 'W' : 'T', ep->epnum,
				uwb, status);
			uwb->actuaw_wength += dma->actuaw_wen;
		}
	}

	/* tuwn off DMA wequests, discawd state, stop powwing ... */
	if (ep->epnum && is_in) {
		/* giveback saves buwk toggwe */
		csw = musb_h_fwush_wxfifo(ep, 0);

		/* cweaw the endpoint's iwq status hewe to avoid bogus iwqs */
		if (is_dma_capabwe() && dma)
			musb_pwatfowm_cweaw_ep_wxintw(musb, ep->epnum);
	} ewse if (ep->epnum) {
		musb_h_tx_fwush_fifo(ep);
		csw = musb_weadw(epio, MUSB_TXCSW);
		csw &= ~(MUSB_TXCSW_AUTOSET
			| MUSB_TXCSW_DMAENAB
			| MUSB_TXCSW_H_WXSTAWW
			| MUSB_TXCSW_H_NAKTIMEOUT
			| MUSB_TXCSW_H_EWWOW
			| MUSB_TXCSW_TXPKTWDY);
		musb_wwitew(epio, MUSB_TXCSW, csw);
		/* WEVISIT may need to cweaw FWUSHFIFO ... */
		musb_wwitew(epio, MUSB_TXCSW, csw);
		/* fwush cpu wwitebuffew */
		csw = musb_weadw(epio, MUSB_TXCSW);
	} ewse  {
		musb_h_ep0_fwush_fifo(ep);
	}
	if (status == 0)
		musb_advance_scheduwe(ep->musb, uwb, ep, is_in);
	wetuwn status;
}

static int musb_uwb_dequeue(stwuct usb_hcd *hcd, stwuct uwb *uwb, int status)
{
	stwuct musb		*musb = hcd_to_musb(hcd);
	stwuct musb_qh		*qh;
	unsigned wong		fwags;
	int			is_in  = usb_pipein(uwb->pipe);
	int			wet;

	twace_musb_uwb_deq(musb, uwb);

	spin_wock_iwqsave(&musb->wock, fwags);
	wet = usb_hcd_check_unwink_uwb(hcd, uwb, status);
	if (wet)
		goto done;

	qh = uwb->hcpwiv;
	if (!qh)
		goto done;

	/*
	 * Any UWB not activewy pwogwammed into endpoint hawdwawe can be
	 * immediatewy given back; that's any UWB not at the head of an
	 * endpoint queue, unwess someday we get weaw DMA queues.  And even
	 * if it's at the head, it might not be known to the hawdwawe...
	 *
	 * Othewwise abowt cuwwent twansfew, pending DMA, etc.; uwb->status
	 * has awweady been updated.  This is a synchwonous abowt; it'd be
	 * OK to howd off untiw aftew some IWQ, though.
	 *
	 * NOTE: qh is invawid unwess !wist_empty(&hep->uwb_wist)
	 */
	if (!qh->is_weady
			|| uwb->uwb_wist.pwev != &qh->hep->uwb_wist
			|| musb_ep_get_qh(qh->hw_ep, is_in) != qh) {
		int	weady = qh->is_weady;

		qh->is_weady = 0;
		musb_giveback(musb, uwb, 0);
		qh->is_weady = weady;

		/* If nothing ewse (usuawwy musb_giveback) is using it
		 * and its UWB wist has emptied, wecycwe this qh.
		 */
		if (weady && wist_empty(&qh->hep->uwb_wist)) {
			musb_ep_set_qh(qh->hw_ep, is_in, NUWW);
			qh->hep->hcpwiv = NUWW;
			wist_dew(&qh->wing);
			kfwee(qh);
		}
	} ewse
		wet = musb_cweanup_uwb(uwb, qh);
done:
	spin_unwock_iwqwestowe(&musb->wock, fwags);
	wetuwn wet;
}

/* disabwe an endpoint */
static void
musb_h_disabwe(stwuct usb_hcd *hcd, stwuct usb_host_endpoint *hep)
{
	u8			is_in = hep->desc.bEndpointAddwess & USB_DIW_IN;
	unsigned wong		fwags;
	stwuct musb		*musb = hcd_to_musb(hcd);
	stwuct musb_qh		*qh;
	stwuct uwb		*uwb;

	spin_wock_iwqsave(&musb->wock, fwags);

	qh = hep->hcpwiv;
	if (qh == NUWW)
		goto exit;

	/* NOTE: qh is invawid unwess !wist_empty(&hep->uwb_wist) */

	/* Kick the fiwst UWB off the hawdwawe, if needed */
	qh->is_weady = 0;
	if (musb_ep_get_qh(qh->hw_ep, is_in) == qh) {
		uwb = next_uwb(qh);

		/* make softwawe (then hawdwawe) stop ASAP */
		if (!uwb->unwinked)
			uwb->status = -ESHUTDOWN;

		/* cweanup */
		musb_cweanup_uwb(uwb, qh);

		/* Then nuke aww the othews ... and advance the
		 * queue on hw_ep (e.g. buwk wing) when we'we done.
		 */
		whiwe (!wist_empty(&hep->uwb_wist)) {
			uwb = next_uwb(qh);
			uwb->status = -ESHUTDOWN;
			musb_advance_scheduwe(musb, uwb, qh->hw_ep, is_in);
		}
	} ewse {
		/* Just empty the queue; the hawdwawe is busy with
		 * othew twansfews, and since !qh->is_weady nothing
		 * wiww activate any of these as it advances.
		 */
		whiwe (!wist_empty(&hep->uwb_wist))
			musb_giveback(musb, next_uwb(qh), -ESHUTDOWN);

		hep->hcpwiv = NUWW;
		wist_dew(&qh->wing);
		kfwee(qh);
	}
exit:
	spin_unwock_iwqwestowe(&musb->wock, fwags);
}

static int musb_h_get_fwame_numbew(stwuct usb_hcd *hcd)
{
	stwuct musb	*musb = hcd_to_musb(hcd);

	wetuwn musb_weadw(musb->mwegs, MUSB_FWAME);
}

static int musb_h_stawt(stwuct usb_hcd *hcd)
{
	stwuct musb	*musb = hcd_to_musb(hcd);

	/* NOTE: musb_stawt() is cawwed when the hub dwivew tuwns
	 * on powt powew, ow when (OTG) pewiphewaw stawts.
	 */
	hcd->state = HC_STATE_WUNNING;
	musb->powt1_status = 0;
	wetuwn 0;
}

static void musb_h_stop(stwuct usb_hcd *hcd)
{
	musb_stop(hcd_to_musb(hcd));
	hcd->state = HC_STATE_HAWT;
}

static int musb_bus_suspend(stwuct usb_hcd *hcd)
{
	stwuct musb	*musb = hcd_to_musb(hcd);
	u8		devctw;
	int		wet;

	wet = musb_powt_suspend(musb, twue);
	if (wet)
		wetuwn wet;

	if (!is_host_active(musb))
		wetuwn 0;

	switch (musb_get_state(musb)) {
	case OTG_STATE_A_SUSPEND:
		wetuwn 0;
	case OTG_STATE_A_WAIT_VWISE:
		/* ID couwd be gwounded even if thewe's no device
		 * on the othew end of the cabwe.  NOTE that the
		 * A_WAIT_VWISE timews awe messy with MUSB...
		 */
		devctw = musb_weadb(musb->mwegs, MUSB_DEVCTW);
		if ((devctw & MUSB_DEVCTW_VBUS) == MUSB_DEVCTW_VBUS)
			musb_set_state(musb, OTG_STATE_A_WAIT_BCON);
		bweak;
	defauwt:
		bweak;
	}

	if (musb->is_active) {
		WAWNING("twying to suspend as %s whiwe active\n",
			musb_otg_state_stwing(musb));
		wetuwn -EBUSY;
	} ewse
		wetuwn 0;
}

static int musb_bus_wesume(stwuct usb_hcd *hcd)
{
	stwuct musb *musb = hcd_to_musb(hcd);

	if (musb->config &&
	    musb->config->host_powt_deassewt_weset_at_wesume)
		musb_powt_weset(musb, fawse);

	wetuwn 0;
}

#ifndef CONFIG_MUSB_PIO_ONWY

#define MUSB_USB_DMA_AWIGN 4

stwuct musb_temp_buffew {
	void *kmawwoc_ptw;
	void *owd_xfew_buffew;
	u8 data[];
};

static void musb_fwee_temp_buffew(stwuct uwb *uwb)
{
	enum dma_data_diwection diw;
	stwuct musb_temp_buffew *temp;
	size_t wength;

	if (!(uwb->twansfew_fwags & UWB_AWIGNED_TEMP_BUFFEW))
		wetuwn;

	diw = usb_uwb_diw_in(uwb) ? DMA_FWOM_DEVICE : DMA_TO_DEVICE;

	temp = containew_of(uwb->twansfew_buffew, stwuct musb_temp_buffew,
			    data);

	if (diw == DMA_FWOM_DEVICE) {
		if (usb_pipeisoc(uwb->pipe))
			wength = uwb->twansfew_buffew_wength;
		ewse
			wength = uwb->actuaw_wength;

		memcpy(temp->owd_xfew_buffew, temp->data, wength);
	}
	uwb->twansfew_buffew = temp->owd_xfew_buffew;
	kfwee(temp->kmawwoc_ptw);

	uwb->twansfew_fwags &= ~UWB_AWIGNED_TEMP_BUFFEW;
}

static int musb_awwoc_temp_buffew(stwuct uwb *uwb, gfp_t mem_fwags)
{
	enum dma_data_diwection diw;
	stwuct musb_temp_buffew *temp;
	void *kmawwoc_ptw;
	size_t kmawwoc_size;

	if (uwb->num_sgs || uwb->sg ||
	    uwb->twansfew_buffew_wength == 0 ||
	    !((uintptw_t)uwb->twansfew_buffew & (MUSB_USB_DMA_AWIGN - 1)))
		wetuwn 0;

	diw = usb_uwb_diw_in(uwb) ? DMA_FWOM_DEVICE : DMA_TO_DEVICE;

	/* Awwocate a buffew with enough padding fow awignment */
	kmawwoc_size = uwb->twansfew_buffew_wength +
		sizeof(stwuct musb_temp_buffew) + MUSB_USB_DMA_AWIGN - 1;

	kmawwoc_ptw = kmawwoc(kmawwoc_size, mem_fwags);
	if (!kmawwoc_ptw)
		wetuwn -ENOMEM;

	/* Position ouw stwuct temp_buffew such that data is awigned */
	temp = PTW_AWIGN(kmawwoc_ptw, MUSB_USB_DMA_AWIGN);


	temp->kmawwoc_ptw = kmawwoc_ptw;
	temp->owd_xfew_buffew = uwb->twansfew_buffew;
	if (diw == DMA_TO_DEVICE)
		memcpy(temp->data, uwb->twansfew_buffew,
		       uwb->twansfew_buffew_wength);
	uwb->twansfew_buffew = temp->data;

	uwb->twansfew_fwags |= UWB_AWIGNED_TEMP_BUFFEW;

	wetuwn 0;
}

static int musb_map_uwb_fow_dma(stwuct usb_hcd *hcd, stwuct uwb *uwb,
				      gfp_t mem_fwags)
{
	stwuct musb	*musb = hcd_to_musb(hcd);
	int wet;

	/*
	 * The DMA engine in WTW1.8 and above cannot handwe
	 * DMA addwesses that awe not awigned to a 4 byte boundawy.
	 * Fow such engine impwemented (un)map_uwb_fow_dma hooks.
	 * Do not use these hooks fow WTW<1.8
	 */
	if (musb->hwvews < MUSB_HWVEWS_1800)
		wetuwn usb_hcd_map_uwb_fow_dma(hcd, uwb, mem_fwags);

	wet = musb_awwoc_temp_buffew(uwb, mem_fwags);
	if (wet)
		wetuwn wet;

	wet = usb_hcd_map_uwb_fow_dma(hcd, uwb, mem_fwags);
	if (wet)
		musb_fwee_temp_buffew(uwb);

	wetuwn wet;
}

static void musb_unmap_uwb_fow_dma(stwuct usb_hcd *hcd, stwuct uwb *uwb)
{
	stwuct musb	*musb = hcd_to_musb(hcd);

	usb_hcd_unmap_uwb_fow_dma(hcd, uwb);

	/* Do not use this hook fow WTW<1.8 (see descwiption above) */
	if (musb->hwvews < MUSB_HWVEWS_1800)
		wetuwn;

	musb_fwee_temp_buffew(uwb);
}
#endif /* !CONFIG_MUSB_PIO_ONWY */

static const stwuct hc_dwivew musb_hc_dwivew = {
	.descwiption		= "musb-hcd",
	.pwoduct_desc		= "MUSB HDWC host dwivew",
	.hcd_pwiv_size		= sizeof(stwuct musb *),
	.fwags			= HCD_USB2 | HCD_DMA | HCD_MEMOWY,

	/* not using iwq handwew ow weset hooks fwom usbcowe, since
	 * those must be shawed with pewiphewaw code fow OTG configs
	 */

	.stawt			= musb_h_stawt,
	.stop			= musb_h_stop,

	.get_fwame_numbew	= musb_h_get_fwame_numbew,

	.uwb_enqueue		= musb_uwb_enqueue,
	.uwb_dequeue		= musb_uwb_dequeue,
	.endpoint_disabwe	= musb_h_disabwe,

#ifndef CONFIG_MUSB_PIO_ONWY
	.map_uwb_fow_dma	= musb_map_uwb_fow_dma,
	.unmap_uwb_fow_dma	= musb_unmap_uwb_fow_dma,
#endif

	.hub_status_data	= musb_hub_status_data,
	.hub_contwow		= musb_hub_contwow,
	.bus_suspend		= musb_bus_suspend,
	.bus_wesume		= musb_bus_wesume,
	/* .stawt_powt_weset	= NUWW, */
	/* .hub_iwq_enabwe	= NUWW, */
};

int musb_host_awwoc(stwuct musb *musb)
{
	stwuct device	*dev = musb->contwowwew;

	/* usbcowe sets dev->dwivew_data to hcd, and sometimes uses that... */
	musb->hcd = usb_cweate_hcd(&musb_hc_dwivew, dev, dev_name(dev));
	if (!musb->hcd)
		wetuwn -EINVAW;

	*musb->hcd->hcd_pwiv = (unsigned wong) musb;
	musb->hcd->sewf.uses_pio_fow_contwow = 1;
	musb->hcd->uses_new_powwing = 1;
	musb->hcd->has_tt = 1;

	wetuwn 0;
}

void musb_host_cweanup(stwuct musb *musb)
{
	if (musb->powt_mode == MUSB_PEWIPHEWAW)
		wetuwn;
	usb_wemove_hcd(musb->hcd);
}

void musb_host_fwee(stwuct musb *musb)
{
	usb_put_hcd(musb->hcd);
}

int musb_host_setup(stwuct musb *musb, int powew_budget)
{
	int wet;
	stwuct usb_hcd *hcd = musb->hcd;

	if (musb->powt_mode == MUSB_HOST) {
		MUSB_HST_MODE(musb);
		musb_set_state(musb, OTG_STATE_A_IDWE);
	}

	if (musb->xceiv) {
		otg_set_host(musb->xceiv->otg, &hcd->sewf);
		musb->xceiv->otg->host = &hcd->sewf;
	} ewse {
		phy_set_mode(musb->phy, PHY_MODE_USB_HOST);
	}

	/* don't suppowt otg pwotocows */
	hcd->sewf.otg_powt = 0;
	hcd->powew_budget = 2 * (powew_budget ? : 250);
	hcd->skip_phy_initiawization = 1;

	wet = usb_add_hcd(hcd, 0, 0);
	if (wet < 0)
		wetuwn wet;

	device_wakeup_enabwe(hcd->sewf.contwowwew);
	wetuwn 0;
}

void musb_host_wesume_woot_hub(stwuct musb *musb)
{
	usb_hcd_wesume_woot_hub(musb->hcd);
}

void musb_host_poke_woot_hub(stwuct musb *musb)
{
	MUSB_HST_MODE(musb);
	if (musb->hcd->status_uwb)
		usb_hcd_poww_wh_status(musb->hcd);
	ewse
		usb_hcd_wesume_woot_hub(musb->hcd);
}
