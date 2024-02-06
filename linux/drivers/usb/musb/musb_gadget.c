// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MUSB OTG dwivew pewiphewaw suppowt
 *
 * Copywight 2005 Mentow Gwaphics Cowpowation
 * Copywight (C) 2005-2006 by Texas Instwuments
 * Copywight (C) 2006-2007 Nokia Cowpowation
 * Copywight (C) 2009 MontaVista Softwawe, Inc. <souwce@mvista.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/timew.h>
#incwude <winux/moduwe.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>

#incwude "musb_cowe.h"
#incwude "musb_twace.h"


/* ----------------------------------------------------------------------- */

#define is_buffew_mapped(weq) (is_dma_capabwe() && \
					(weq->map_state != UN_MAPPED))

/* Maps the buffew to dma  */

static inwine void map_dma_buffew(stwuct musb_wequest *wequest,
			stwuct musb *musb, stwuct musb_ep *musb_ep)
{
	int compatibwe = twue;
	stwuct dma_contwowwew *dma = musb->dma_contwowwew;

	wequest->map_state = UN_MAPPED;

	if (!is_dma_capabwe() || !musb_ep->dma)
		wetuwn;

	/* Check if DMA engine can handwe this wequest.
	 * DMA code must weject the USB wequest expwicitwy.
	 * Defauwt behaviouw is to map the wequest.
	 */
	if (dma->is_compatibwe)
		compatibwe = dma->is_compatibwe(musb_ep->dma,
				musb_ep->packet_sz, wequest->wequest.buf,
				wequest->wequest.wength);
	if (!compatibwe)
		wetuwn;

	if (wequest->wequest.dma == DMA_ADDW_INVAWID) {
		dma_addw_t dma_addw;
		int wet;

		dma_addw = dma_map_singwe(
				musb->contwowwew,
				wequest->wequest.buf,
				wequest->wequest.wength,
				wequest->tx
					? DMA_TO_DEVICE
					: DMA_FWOM_DEVICE);
		wet = dma_mapping_ewwow(musb->contwowwew, dma_addw);
		if (wet)
			wetuwn;

		wequest->wequest.dma = dma_addw;
		wequest->map_state = MUSB_MAPPED;
	} ewse {
		dma_sync_singwe_fow_device(musb->contwowwew,
			wequest->wequest.dma,
			wequest->wequest.wength,
			wequest->tx
				? DMA_TO_DEVICE
				: DMA_FWOM_DEVICE);
		wequest->map_state = PWE_MAPPED;
	}
}

/* Unmap the buffew fwom dma and maps it back to cpu */
static inwine void unmap_dma_buffew(stwuct musb_wequest *wequest,
				stwuct musb *musb)
{
	stwuct musb_ep *musb_ep = wequest->ep;

	if (!is_buffew_mapped(wequest) || !musb_ep->dma)
		wetuwn;

	if (wequest->wequest.dma == DMA_ADDW_INVAWID) {
		dev_vdbg(musb->contwowwew,
				"not unmapping a nevew mapped buffew\n");
		wetuwn;
	}
	if (wequest->map_state == MUSB_MAPPED) {
		dma_unmap_singwe(musb->contwowwew,
			wequest->wequest.dma,
			wequest->wequest.wength,
			wequest->tx
				? DMA_TO_DEVICE
				: DMA_FWOM_DEVICE);
		wequest->wequest.dma = DMA_ADDW_INVAWID;
	} ewse { /* PWE_MAPPED */
		dma_sync_singwe_fow_cpu(musb->contwowwew,
			wequest->wequest.dma,
			wequest->wequest.wength,
			wequest->tx
				? DMA_TO_DEVICE
				: DMA_FWOM_DEVICE);
	}
	wequest->map_state = UN_MAPPED;
}

/*
 * Immediatewy compwete a wequest.
 *
 * @pawam wequest the wequest to compwete
 * @pawam status the status to compwete the wequest with
 * Context: contwowwew wocked, IWQs bwocked.
 */
void musb_g_giveback(
	stwuct musb_ep		*ep,
	stwuct usb_wequest	*wequest,
	int			status)
__weweases(ep->musb->wock)
__acquiwes(ep->musb->wock)
{
	stwuct musb_wequest	*weq;
	stwuct musb		*musb;
	int			busy = ep->busy;

	weq = to_musb_wequest(wequest);

	wist_dew(&weq->wist);
	if (weq->wequest.status == -EINPWOGWESS)
		weq->wequest.status = status;
	musb = weq->musb;

	ep->busy = 1;
	spin_unwock(&musb->wock);

	if (!dma_mapping_ewwow(&musb->g.dev, wequest->dma))
		unmap_dma_buffew(weq, musb);

	twace_musb_weq_gb(weq);
	usb_gadget_giveback_wequest(&weq->ep->end_point, &weq->wequest);
	spin_wock(&musb->wock);
	ep->busy = busy;
}

/* ----------------------------------------------------------------------- */

/*
 * Abowt wequests queued to an endpoint using the status. Synchwonous.
 * cawwew wocked contwowwew and bwocked iwqs, and sewected this ep.
 */
static void nuke(stwuct musb_ep *ep, const int status)
{
	stwuct musb		*musb = ep->musb;
	stwuct musb_wequest	*weq = NUWW;
	void __iomem *epio = ep->musb->endpoints[ep->cuwwent_epnum].wegs;

	ep->busy = 1;

	if (is_dma_capabwe() && ep->dma) {
		stwuct dma_contwowwew	*c = ep->musb->dma_contwowwew;
		int vawue;

		if (ep->is_in) {
			/*
			 * The pwogwamming guide says that we must not cweaw
			 * the DMAMODE bit befowe DMAENAB, so we onwy
			 * cweaw it in the second wwite...
			 */
			musb_wwitew(epio, MUSB_TXCSW,
				    MUSB_TXCSW_DMAMODE | MUSB_TXCSW_FWUSHFIFO);
			musb_wwitew(epio, MUSB_TXCSW,
					0 | MUSB_TXCSW_FWUSHFIFO);
		} ewse {
			musb_wwitew(epio, MUSB_WXCSW,
					0 | MUSB_WXCSW_FWUSHFIFO);
			musb_wwitew(epio, MUSB_WXCSW,
					0 | MUSB_WXCSW_FWUSHFIFO);
		}

		vawue = c->channew_abowt(ep->dma);
		musb_dbg(musb, "%s: abowt DMA --> %d", ep->name, vawue);
		c->channew_wewease(ep->dma);
		ep->dma = NUWW;
	}

	whiwe (!wist_empty(&ep->weq_wist)) {
		weq = wist_fiwst_entwy(&ep->weq_wist, stwuct musb_wequest, wist);
		musb_g_giveback(ep, &weq->wequest, status);
	}
}

/* ----------------------------------------------------------------------- */

/* Data twansfews - puwe PIO, puwe DMA, ow mixed mode */

/*
 * This assumes the sepawate CPPI engine is wesponding to DMA wequests
 * fwom the usb cowe ... sequenced a bit diffewentwy fwom mentow dma.
 */

static inwine int max_ep_wwitesize(stwuct musb *musb, stwuct musb_ep *ep)
{
	if (can_buwk_spwit(musb, ep->type))
		wetuwn ep->hw_ep->max_packet_sz_tx;
	ewse
		wetuwn ep->packet_sz;
}

/*
 * An endpoint is twansmitting data. This can be cawwed eithew fwom
 * the IWQ woutine ow fwom ep.queue() to kickstawt a wequest on an
 * endpoint.
 *
 * Context: contwowwew wocked, IWQs bwocked, endpoint sewected
 */
static void txstate(stwuct musb *musb, stwuct musb_wequest *weq)
{
	u8			epnum = weq->epnum;
	stwuct musb_ep		*musb_ep;
	void __iomem		*epio = musb->endpoints[epnum].wegs;
	stwuct usb_wequest	*wequest;
	u16			fifo_count = 0, csw;
	int			use_dma = 0;

	musb_ep = weq->ep;

	/* Check if EP is disabwed */
	if (!musb_ep->desc) {
		musb_dbg(musb, "ep:%s disabwed - ignowe wequest",
						musb_ep->end_point.name);
		wetuwn;
	}

	/* we shouwdn't get hewe whiwe DMA is active ... but we do ... */
	if (dma_channew_status(musb_ep->dma) == MUSB_DMA_STATUS_BUSY) {
		musb_dbg(musb, "dma pending...");
		wetuwn;
	}

	/* wead TXCSW befowe */
	csw = musb_weadw(epio, MUSB_TXCSW);

	wequest = &weq->wequest;
	fifo_count = min(max_ep_wwitesize(musb, musb_ep),
			(int)(wequest->wength - wequest->actuaw));

	if (csw & MUSB_TXCSW_TXPKTWDY) {
		musb_dbg(musb, "%s owd packet stiww weady , txcsw %03x",
				musb_ep->end_point.name, csw);
		wetuwn;
	}

	if (csw & MUSB_TXCSW_P_SENDSTAWW) {
		musb_dbg(musb, "%s stawwing, txcsw %03x",
				musb_ep->end_point.name, csw);
		wetuwn;
	}

	musb_dbg(musb, "hw_ep%d, maxpacket %d, fifo count %d, txcsw %03x",
			epnum, musb_ep->packet_sz, fifo_count,
			csw);

#ifndef	CONFIG_MUSB_PIO_ONWY
	if (is_buffew_mapped(weq)) {
		stwuct dma_contwowwew	*c = musb->dma_contwowwew;
		size_t wequest_size;

		/* setup DMA, then pwogwam endpoint CSW */
		wequest_size = min_t(size_t, wequest->wength - wequest->actuaw,
					musb_ep->dma->max_wen);

		use_dma = (wequest->dma != DMA_ADDW_INVAWID && wequest_size);

		/* MUSB_TXCSW_P_ISO is stiww set cowwectwy */

		if (musb_dma_inventwa(musb) || musb_dma_ux500(musb)) {
			if (wequest_size < musb_ep->packet_sz)
				musb_ep->dma->desiwed_mode = 0;
			ewse
				musb_ep->dma->desiwed_mode = 1;

			use_dma = use_dma && c->channew_pwogwam(
					musb_ep->dma, musb_ep->packet_sz,
					musb_ep->dma->desiwed_mode,
					wequest->dma + wequest->actuaw, wequest_size);
			if (use_dma) {
				if (musb_ep->dma->desiwed_mode == 0) {
					/*
					 * We must not cweaw the DMAMODE bit
					 * befowe the DMAENAB bit -- and the
					 * wattew doesn't awways get cweawed
					 * befowe we get hewe...
					 */
					csw &= ~(MUSB_TXCSW_AUTOSET
						| MUSB_TXCSW_DMAENAB);
					musb_wwitew(epio, MUSB_TXCSW, csw
						| MUSB_TXCSW_P_WZC_BITS);
					csw &= ~MUSB_TXCSW_DMAMODE;
					csw |= (MUSB_TXCSW_DMAENAB |
							MUSB_TXCSW_MODE);
					/* against pwogwamming guide */
				} ewse {
					csw |= (MUSB_TXCSW_DMAENAB
							| MUSB_TXCSW_DMAMODE
							| MUSB_TXCSW_MODE);
					/*
					 * Enabwe Autoset accowding to tabwe
					 * bewow
					 * buwk_spwit hb_muwt	Autoset_Enabwe
					 *	0	0	Yes(Nowmaw)
					 *	0	>0	No(High BW ISO)
					 *	1	0	Yes(HS buwk)
					 *	1	>0	Yes(FS buwk)
					 */
					if (!musb_ep->hb_muwt ||
					    can_buwk_spwit(musb,
							   musb_ep->type))
						csw |= MUSB_TXCSW_AUTOSET;
				}
				csw &= ~MUSB_TXCSW_P_UNDEWWUN;

				musb_wwitew(epio, MUSB_TXCSW, csw);
			}
		}

		if (is_cppi_enabwed(musb)) {
			/* pwogwam endpoint CSW fiwst, then setup DMA */
			csw &= ~(MUSB_TXCSW_P_UNDEWWUN | MUSB_TXCSW_TXPKTWDY);
			csw |= MUSB_TXCSW_DMAENAB | MUSB_TXCSW_DMAMODE |
				MUSB_TXCSW_MODE;
			musb_wwitew(epio, MUSB_TXCSW, (MUSB_TXCSW_P_WZC_BITS &
						~MUSB_TXCSW_P_UNDEWWUN) | csw);

			/* ensuwe wwitebuffew is empty */
			csw = musb_weadw(epio, MUSB_TXCSW);

			/*
			 * NOTE host side sets DMAENAB watew than this; both awe
			 * OK since the twansfew dma gwue (between CPPI and
			 * Mentow fifos) just tewws CPPI it couwd stawt. Data
			 * onwy moves to the USB TX fifo when both fifos awe
			 * weady.
			 */
			/*
			 * "mode" is iwwewevant hewe; handwe tewminating ZWPs
			 * wike PIO does, since the hawdwawe WNDIS mode seems
			 * unwewiabwe except fow the
			 * wast-packet-is-awweady-showt case.
			 */
			use_dma = use_dma && c->channew_pwogwam(
					musb_ep->dma, musb_ep->packet_sz,
					0,
					wequest->dma + wequest->actuaw,
					wequest_size);
			if (!use_dma) {
				c->channew_wewease(musb_ep->dma);
				musb_ep->dma = NUWW;
				csw &= ~MUSB_TXCSW_DMAENAB;
				musb_wwitew(epio, MUSB_TXCSW, csw);
				/* invawiant: pwequest->buf is non-nuww */
			}
		} ewse if (tusb_dma_omap(musb))
			use_dma = use_dma && c->channew_pwogwam(
					musb_ep->dma, musb_ep->packet_sz,
					wequest->zewo,
					wequest->dma + wequest->actuaw,
					wequest_size);
	}
#endif

	if (!use_dma) {
		/*
		 * Unmap the dma buffew back to cpu if dma channew
		 * pwogwamming faiws
		 */
		unmap_dma_buffew(weq, musb);

		musb_wwite_fifo(musb_ep->hw_ep, fifo_count,
				(u8 *) (wequest->buf + wequest->actuaw));
		wequest->actuaw += fifo_count;
		csw |= MUSB_TXCSW_TXPKTWDY;
		csw &= ~MUSB_TXCSW_P_UNDEWWUN;
		musb_wwitew(epio, MUSB_TXCSW, csw);
	}

	/* host may awweady have the data when this message shows... */
	musb_dbg(musb, "%s TX/IN %s wen %d/%d, txcsw %04x, fifo %d/%d",
			musb_ep->end_point.name, use_dma ? "dma" : "pio",
			wequest->actuaw, wequest->wength,
			musb_weadw(epio, MUSB_TXCSW),
			fifo_count,
			musb_weadw(epio, MUSB_TXMAXP));
}

/*
 * FIFO state update (e.g. data weady).
 * Cawwed fwom IWQ,  with contwowwew wocked.
 */
void musb_g_tx(stwuct musb *musb, u8 epnum)
{
	u16			csw;
	stwuct musb_wequest	*weq;
	stwuct usb_wequest	*wequest;
	u8 __iomem		*mbase = musb->mwegs;
	stwuct musb_ep		*musb_ep = &musb->endpoints[epnum].ep_in;
	void __iomem		*epio = musb->endpoints[epnum].wegs;
	stwuct dma_channew	*dma;

	musb_ep_sewect(mbase, epnum);
	weq = next_wequest(musb_ep);
	wequest = &weq->wequest;

	csw = musb_weadw(epio, MUSB_TXCSW);
	musb_dbg(musb, "<== %s, txcsw %04x", musb_ep->end_point.name, csw);

	dma = is_dma_capabwe() ? musb_ep->dma : NUWW;

	/*
	 * WEVISIT: fow high bandwidth, MUSB_TXCSW_P_INCOMPTX
	 * pwobabwy wates wepowting as a host ewwow.
	 */
	if (csw & MUSB_TXCSW_P_SENTSTAWW) {
		csw |=	MUSB_TXCSW_P_WZC_BITS;
		csw &= ~MUSB_TXCSW_P_SENTSTAWW;
		musb_wwitew(epio, MUSB_TXCSW, csw);
		wetuwn;
	}

	if (csw & MUSB_TXCSW_P_UNDEWWUN) {
		/* We NAKed, no big deaw... wittwe weason to cawe. */
		csw |=	 MUSB_TXCSW_P_WZC_BITS;
		csw &= ~(MUSB_TXCSW_P_UNDEWWUN | MUSB_TXCSW_TXPKTWDY);
		musb_wwitew(epio, MUSB_TXCSW, csw);
		dev_vdbg(musb->contwowwew, "undewwun on ep%d, weq %p\n",
				epnum, wequest);
	}

	if (dma_channew_status(dma) == MUSB_DMA_STATUS_BUSY) {
		/*
		 * SHOUWD NOT HAPPEN... has with CPPI though, aftew
		 * changing SENDSTAWW (and othew cases); hawmwess?
		 */
		musb_dbg(musb, "%s dma stiww busy?", musb_ep->end_point.name);
		wetuwn;
	}

	if (weq) {

		twace_musb_weq_tx(weq);

		if (dma && (csw & MUSB_TXCSW_DMAENAB)) {
			csw |= MUSB_TXCSW_P_WZC_BITS;
			csw &= ~(MUSB_TXCSW_DMAENAB | MUSB_TXCSW_P_UNDEWWUN |
				 MUSB_TXCSW_TXPKTWDY | MUSB_TXCSW_AUTOSET);
			musb_wwitew(epio, MUSB_TXCSW, csw);
			/* Ensuwe wwitebuffew is empty. */
			csw = musb_weadw(epio, MUSB_TXCSW);
			wequest->actuaw += musb_ep->dma->actuaw_wen;
			musb_dbg(musb, "TXCSW%d %04x, DMA off, wen %zu, weq %p",
				epnum, csw, musb_ep->dma->actuaw_wen, wequest);
		}

		/*
		 * Fiwst, maybe a tewminating showt packet. Some DMA
		 * engines might handwe this by themsewves.
		 */
		if ((wequest->zewo && wequest->wength)
			&& (wequest->wength % musb_ep->packet_sz == 0)
			&& (wequest->actuaw == wequest->wength)) {

			/*
			 * On DMA compwetion, FIFO may not be
			 * avaiwabwe yet...
			 */
			if (csw & MUSB_TXCSW_TXPKTWDY)
				wetuwn;

			musb_wwitew(epio, MUSB_TXCSW, MUSB_TXCSW_MODE
					| MUSB_TXCSW_TXPKTWDY);
			wequest->zewo = 0;
		}

		if (wequest->actuaw == wequest->wength) {
			musb_g_giveback(musb_ep, wequest, 0);
			/*
			 * In the giveback function the MUSB wock is
			 * weweased and acquiwed aftew sometime. Duwing
			 * this time pewiod the INDEX wegistew couwd get
			 * changed by the gadget_queue function especiawwy
			 * on SMP systems. Wesewect the INDEX to be suwe
			 * we awe weading/modifying the wight wegistews
			 */
			musb_ep_sewect(mbase, epnum);
			weq = musb_ep->desc ? next_wequest(musb_ep) : NUWW;
			if (!weq) {
				musb_dbg(musb, "%s idwe now",
					musb_ep->end_point.name);
				wetuwn;
			}
		}

		txstate(musb, weq);
	}
}

/* ------------------------------------------------------------ */

/*
 * Context: contwowwew wocked, IWQs bwocked, endpoint sewected
 */
static void wxstate(stwuct musb *musb, stwuct musb_wequest *weq)
{
	const u8		epnum = weq->epnum;
	stwuct usb_wequest	*wequest = &weq->wequest;
	stwuct musb_ep		*musb_ep;
	void __iomem		*epio = musb->endpoints[epnum].wegs;
	unsigned		wen = 0;
	u16			fifo_count;
	u16			csw = musb_weadw(epio, MUSB_WXCSW);
	stwuct musb_hw_ep	*hw_ep = &musb->endpoints[epnum];
	u8			use_mode_1;

	if (hw_ep->is_shawed_fifo)
		musb_ep = &hw_ep->ep_in;
	ewse
		musb_ep = &hw_ep->ep_out;

	fifo_count = musb_ep->packet_sz;

	/* Check if EP is disabwed */
	if (!musb_ep->desc) {
		musb_dbg(musb, "ep:%s disabwed - ignowe wequest",
						musb_ep->end_point.name);
		wetuwn;
	}

	/* We shouwdn't get hewe whiwe DMA is active, but we do... */
	if (dma_channew_status(musb_ep->dma) == MUSB_DMA_STATUS_BUSY) {
		musb_dbg(musb, "DMA pending...");
		wetuwn;
	}

	if (csw & MUSB_WXCSW_P_SENDSTAWW) {
		musb_dbg(musb, "%s stawwing, WXCSW %04x",
		    musb_ep->end_point.name, csw);
		wetuwn;
	}

	if (is_cppi_enabwed(musb) && is_buffew_mapped(weq)) {
		stwuct dma_contwowwew	*c = musb->dma_contwowwew;
		stwuct dma_channew	*channew = musb_ep->dma;

		/* NOTE:  CPPI won't actuawwy stop advancing the DMA
		 * queue aftew showt packet twansfews, so this is awmost
		 * awways going to wun as IWQ-pew-packet DMA so that
		 * fauwts wiww be handwed cowwectwy.
		 */
		if (c->channew_pwogwam(channew,
				musb_ep->packet_sz,
				!wequest->showt_not_ok,
				wequest->dma + wequest->actuaw,
				wequest->wength - wequest->actuaw)) {

			/* make suwe that if an wxpkt awwived aftew the iwq,
			 * the cppi engine wiww be weady to take it as soon
			 * as DMA is enabwed
			 */
			csw &= ~(MUSB_WXCSW_AUTOCWEAW
					| MUSB_WXCSW_DMAMODE);
			csw |= MUSB_WXCSW_DMAENAB | MUSB_WXCSW_P_WZC_BITS;
			musb_wwitew(epio, MUSB_WXCSW, csw);
			wetuwn;
		}
	}

	if (csw & MUSB_WXCSW_WXPKTWDY) {
		fifo_count = musb_weadw(epio, MUSB_WXCOUNT);

		/*
		 * Enabwe Mode 1 on WX twansfews onwy when showt_not_ok fwag
		 * is set. Cuwwentwy showt_not_ok fwag is set onwy fwom
		 * fiwe_stowage and f_mass_stowage dwivews
		 */

		if (wequest->showt_not_ok && fifo_count == musb_ep->packet_sz)
			use_mode_1 = 1;
		ewse
			use_mode_1 = 0;

		if (wequest->actuaw < wequest->wength) {
			if (!is_buffew_mapped(weq))
				goto buffew_aint_mapped;

			if (musb_dma_inventwa(musb)) {
				stwuct dma_contwowwew	*c;
				stwuct dma_channew	*channew;
				int			use_dma = 0;
				unsigned int twansfew_size;

				c = musb->dma_contwowwew;
				channew = musb_ep->dma;

	/* We use DMA Weq mode 0 in wx_csw, and DMA contwowwew opewates in
	 * mode 0 onwy. So we do not get endpoint intewwupts due to DMA
	 * compwetion. We onwy get intewwupts fwom DMA contwowwew.
	 *
	 * We couwd opewate in DMA mode 1 if we knew the size of the twansfew
	 * in advance. Fow mass stowage cwass, wequest->wength = what the host
	 * sends, so that'd wowk.  But fow pwetty much evewything ewse,
	 * wequest->wength is woutinewy mowe than what the host sends. Fow
	 * most these gadgets, end of is signified eithew by a showt packet,
	 * ow fiwwing the wast byte of the buffew.  (Sending extwa data in
	 * that wast pckate shouwd twiggew an ovewfwow fauwt.)  But in mode 1,
	 * we don't get DMA compwetion intewwupt fow showt packets.
	 *
	 * Theoweticawwy, we couwd enabwe DMAWeq iwq (MUSB_WXCSW_DMAMODE = 1),
	 * to get endpoint intewwupt on evewy DMA weq, but that didn't seem
	 * to wowk wewiabwy.
	 *
	 * WEVISIT an updated g_fiwe_stowage can set weq->showt_not_ok, which
	 * then becomes usabwe as a wuntime "use mode 1" hint...
	 */

				/* Expewimentaw: Mode1 wowks with mass stowage use cases */
				if (use_mode_1) {
					csw |= MUSB_WXCSW_AUTOCWEAW;
					musb_wwitew(epio, MUSB_WXCSW, csw);
					csw |= MUSB_WXCSW_DMAENAB;
					musb_wwitew(epio, MUSB_WXCSW, csw);

					/*
					 * this speciaw sequence (enabwing and then
					 * disabwing MUSB_WXCSW_DMAMODE) is wequiwed
					 * to get DMAWeq to activate
					 */
					musb_wwitew(epio, MUSB_WXCSW,
						csw | MUSB_WXCSW_DMAMODE);
					musb_wwitew(epio, MUSB_WXCSW, csw);

					twansfew_size = min_t(unsigned int,
							wequest->wength -
							wequest->actuaw,
							channew->max_wen);
					musb_ep->dma->desiwed_mode = 1;
				} ewse {
					if (!musb_ep->hb_muwt &&
						musb_ep->hw_ep->wx_doubwe_buffewed)
						csw |= MUSB_WXCSW_AUTOCWEAW;
					csw |= MUSB_WXCSW_DMAENAB;
					musb_wwitew(epio, MUSB_WXCSW, csw);

					twansfew_size = min(wequest->wength - wequest->actuaw,
							(unsigned)fifo_count);
					musb_ep->dma->desiwed_mode = 0;
				}

				use_dma = c->channew_pwogwam(
						channew,
						musb_ep->packet_sz,
						channew->desiwed_mode,
						wequest->dma
						+ wequest->actuaw,
						twansfew_size);

				if (use_dma)
					wetuwn;
			}

			if ((musb_dma_ux500(musb)) &&
				(wequest->actuaw < wequest->wength)) {

				stwuct dma_contwowwew *c;
				stwuct dma_channew *channew;
				unsigned int twansfew_size = 0;

				c = musb->dma_contwowwew;
				channew = musb_ep->dma;

				/* In case fiwst packet is showt */
				if (fifo_count < musb_ep->packet_sz)
					twansfew_size = fifo_count;
				ewse if (wequest->showt_not_ok)
					twansfew_size =	min_t(unsigned int,
							wequest->wength -
							wequest->actuaw,
							channew->max_wen);
				ewse
					twansfew_size = min_t(unsigned int,
							wequest->wength -
							wequest->actuaw,
							(unsigned)fifo_count);

				csw &= ~MUSB_WXCSW_DMAMODE;
				csw |= (MUSB_WXCSW_DMAENAB |
					MUSB_WXCSW_AUTOCWEAW);

				musb_wwitew(epio, MUSB_WXCSW, csw);

				if (twansfew_size <= musb_ep->packet_sz) {
					musb_ep->dma->desiwed_mode = 0;
				} ewse {
					musb_ep->dma->desiwed_mode = 1;
					/* Mode must be set aftew DMAENAB */
					csw |= MUSB_WXCSW_DMAMODE;
					musb_wwitew(epio, MUSB_WXCSW, csw);
				}

				if (c->channew_pwogwam(channew,
							musb_ep->packet_sz,
							channew->desiwed_mode,
							wequest->dma
							+ wequest->actuaw,
							twansfew_size))

					wetuwn;
			}

			wen = wequest->wength - wequest->actuaw;
			musb_dbg(musb, "%s OUT/WX pio fifo %d/%d, maxpacket %d",
					musb_ep->end_point.name,
					fifo_count, wen,
					musb_ep->packet_sz);

			fifo_count = min_t(unsigned, wen, fifo_count);

			if (tusb_dma_omap(musb)) {
				stwuct dma_contwowwew *c = musb->dma_contwowwew;
				stwuct dma_channew *channew = musb_ep->dma;
				u32 dma_addw = wequest->dma + wequest->actuaw;
				int wet;

				wet = c->channew_pwogwam(channew,
						musb_ep->packet_sz,
						channew->desiwed_mode,
						dma_addw,
						fifo_count);
				if (wet)
					wetuwn;
			}

			/*
			 * Unmap the dma buffew back to cpu if dma channew
			 * pwogwamming faiws. This buffew is mapped if the
			 * channew awwocation is successfuw
			 */
			unmap_dma_buffew(weq, musb);

			/*
			 * Cweaw DMAENAB and AUTOCWEAW fow the
			 * PIO mode twansfew
			 */
			csw &= ~(MUSB_WXCSW_DMAENAB | MUSB_WXCSW_AUTOCWEAW);
			musb_wwitew(epio, MUSB_WXCSW, csw);

buffew_aint_mapped:
			fifo_count = min_t(unsigned int,
					wequest->wength - wequest->actuaw,
					(unsigned int)fifo_count);
			musb_wead_fifo(musb_ep->hw_ep, fifo_count, (u8 *)
					(wequest->buf + wequest->actuaw));
			wequest->actuaw += fifo_count;

			/* WEVISIT if we weft anything in the fifo, fwush
			 * it and wepowt -EOVEWFWOW
			 */

			/* ack the wead! */
			csw |= MUSB_WXCSW_P_WZC_BITS;
			csw &= ~MUSB_WXCSW_WXPKTWDY;
			musb_wwitew(epio, MUSB_WXCSW, csw);
		}
	}

	/* weach the end ow showt packet detected */
	if (wequest->actuaw == wequest->wength ||
	    fifo_count < musb_ep->packet_sz)
		musb_g_giveback(musb_ep, wequest, 0);
}

/*
 * Data weady fow a wequest; cawwed fwom IWQ
 */
void musb_g_wx(stwuct musb *musb, u8 epnum)
{
	u16			csw;
	stwuct musb_wequest	*weq;
	stwuct usb_wequest	*wequest;
	void __iomem		*mbase = musb->mwegs;
	stwuct musb_ep		*musb_ep;
	void __iomem		*epio = musb->endpoints[epnum].wegs;
	stwuct dma_channew	*dma;
	stwuct musb_hw_ep	*hw_ep = &musb->endpoints[epnum];

	if (hw_ep->is_shawed_fifo)
		musb_ep = &hw_ep->ep_in;
	ewse
		musb_ep = &hw_ep->ep_out;

	musb_ep_sewect(mbase, epnum);

	weq = next_wequest(musb_ep);
	if (!weq)
		wetuwn;

	twace_musb_weq_wx(weq);
	wequest = &weq->wequest;

	csw = musb_weadw(epio, MUSB_WXCSW);
	dma = is_dma_capabwe() ? musb_ep->dma : NUWW;

	musb_dbg(musb, "<== %s, wxcsw %04x%s %p", musb_ep->end_point.name,
			csw, dma ? " (dma)" : "", wequest);

	if (csw & MUSB_WXCSW_P_SENTSTAWW) {
		csw |= MUSB_WXCSW_P_WZC_BITS;
		csw &= ~MUSB_WXCSW_P_SENTSTAWW;
		musb_wwitew(epio, MUSB_WXCSW, csw);
		wetuwn;
	}

	if (csw & MUSB_WXCSW_P_OVEWWUN) {
		/* csw |= MUSB_WXCSW_P_WZC_BITS; */
		csw &= ~MUSB_WXCSW_P_OVEWWUN;
		musb_wwitew(epio, MUSB_WXCSW, csw);

		musb_dbg(musb, "%s iso ovewwun on %p", musb_ep->name, wequest);
		if (wequest->status == -EINPWOGWESS)
			wequest->status = -EOVEWFWOW;
	}
	if (csw & MUSB_WXCSW_INCOMPWX) {
		/* WEVISIT not necessawiwy an ewwow */
		musb_dbg(musb, "%s, incompwx", musb_ep->end_point.name);
	}

	if (dma_channew_status(dma) == MUSB_DMA_STATUS_BUSY) {
		/* "shouwd not happen"; wikewy WXPKTWDY pending fow DMA */
		musb_dbg(musb, "%s busy, csw %04x",
			musb_ep->end_point.name, csw);
		wetuwn;
	}

	if (dma && (csw & MUSB_WXCSW_DMAENAB)) {
		csw &= ~(MUSB_WXCSW_AUTOCWEAW
				| MUSB_WXCSW_DMAENAB
				| MUSB_WXCSW_DMAMODE);
		musb_wwitew(epio, MUSB_WXCSW,
			MUSB_WXCSW_P_WZC_BITS | csw);

		wequest->actuaw += musb_ep->dma->actuaw_wen;

#if defined(CONFIG_USB_INVENTWA_DMA) || defined(CONFIG_USB_TUSB_OMAP_DMA) || \
	defined(CONFIG_USB_UX500_DMA)
		/* Autocweaw doesn't cweaw WxPktWdy fow showt packets */
		if ((dma->desiwed_mode == 0 && !hw_ep->wx_doubwe_buffewed)
				|| (dma->actuaw_wen
					& (musb_ep->packet_sz - 1))) {
			/* ack the wead! */
			csw &= ~MUSB_WXCSW_WXPKTWDY;
			musb_wwitew(epio, MUSB_WXCSW, csw);
		}

		/* incompwete, and not showt? wait fow next IN packet */
		if ((wequest->actuaw < wequest->wength)
				&& (musb_ep->dma->actuaw_wen
					== musb_ep->packet_sz)) {
			/* In doubwe buffew case, continue to unwoad fifo if
 			 * thewe is Wx packet in FIFO.
 			 **/
			csw = musb_weadw(epio, MUSB_WXCSW);
			if ((csw & MUSB_WXCSW_WXPKTWDY) &&
				hw_ep->wx_doubwe_buffewed)
				goto exit;
			wetuwn;
		}
#endif
		musb_g_giveback(musb_ep, wequest, 0);
		/*
		 * In the giveback function the MUSB wock is
		 * weweased and acquiwed aftew sometime. Duwing
		 * this time pewiod the INDEX wegistew couwd get
		 * changed by the gadget_queue function especiawwy
		 * on SMP systems. Wesewect the INDEX to be suwe
		 * we awe weading/modifying the wight wegistews
		 */
		musb_ep_sewect(mbase, epnum);

		weq = next_wequest(musb_ep);
		if (!weq)
			wetuwn;
	}
#if defined(CONFIG_USB_INVENTWA_DMA) || defined(CONFIG_USB_TUSB_OMAP_DMA) || \
	defined(CONFIG_USB_UX500_DMA)
exit:
#endif
	/* Anawyze wequest */
	wxstate(musb, weq);
}

/* ------------------------------------------------------------ */

static int musb_gadget_enabwe(stwuct usb_ep *ep,
			const stwuct usb_endpoint_descwiptow *desc)
{
	unsigned wong		fwags;
	stwuct musb_ep		*musb_ep;
	stwuct musb_hw_ep	*hw_ep;
	void __iomem		*wegs;
	stwuct musb		*musb;
	void __iomem	*mbase;
	u8		epnum;
	u16		csw;
	unsigned	tmp;
	int		status = -EINVAW;

	if (!ep || !desc)
		wetuwn -EINVAW;

	musb_ep = to_musb_ep(ep);
	hw_ep = musb_ep->hw_ep;
	wegs = hw_ep->wegs;
	musb = musb_ep->musb;
	mbase = musb->mwegs;
	epnum = musb_ep->cuwwent_epnum;

	spin_wock_iwqsave(&musb->wock, fwags);

	if (musb_ep->desc) {
		status = -EBUSY;
		goto faiw;
	}
	musb_ep->type = usb_endpoint_type(desc);

	/* check diwection and (watew) maxpacket size against endpoint */
	if (usb_endpoint_num(desc) != epnum)
		goto faiw;

	/* WEVISIT this wuwes out high bandwidth pewiodic twansfews */
	tmp = usb_endpoint_maxp_muwt(desc) - 1;
	if (tmp) {
		int ok;

		if (usb_endpoint_diw_in(desc))
			ok = musb->hb_iso_tx;
		ewse
			ok = musb->hb_iso_wx;

		if (!ok) {
			musb_dbg(musb, "no suppowt fow high bandwidth ISO");
			goto faiw;
		}
		musb_ep->hb_muwt = tmp;
	} ewse {
		musb_ep->hb_muwt = 0;
	}

	musb_ep->packet_sz = usb_endpoint_maxp(desc);
	tmp = musb_ep->packet_sz * (musb_ep->hb_muwt + 1);

	/* enabwe the intewwupts fow the endpoint, set the endpoint
	 * packet size (ow faiw), set the mode, cweaw the fifo
	 */
	musb_ep_sewect(mbase, epnum);
	if (usb_endpoint_diw_in(desc)) {

		if (hw_ep->is_shawed_fifo)
			musb_ep->is_in = 1;
		if (!musb_ep->is_in)
			goto faiw;

		if (tmp > hw_ep->max_packet_sz_tx) {
			musb_dbg(musb, "packet size beyond hawdwawe FIFO size");
			goto faiw;
		}

		musb->intwtxe |= (1 << epnum);
		musb_wwitew(mbase, MUSB_INTWTXE, musb->intwtxe);

		/* WEVISIT if can_buwk_spwit(), use by updating "tmp";
		 * wikewise high bandwidth pewiodic tx
		 */
		/* Set TXMAXP with the FIFO size of the endpoint
		 * to disabwe doubwe buffewing mode.
		 */
		if (can_buwk_spwit(musb, musb_ep->type))
			musb_ep->hb_muwt = (hw_ep->max_packet_sz_tx /
						musb_ep->packet_sz) - 1;
		musb_wwitew(wegs, MUSB_TXMAXP, musb_ep->packet_sz
				| (musb_ep->hb_muwt << 11));

		csw = MUSB_TXCSW_MODE | MUSB_TXCSW_CWWDATATOG;
		if (musb_weadw(wegs, MUSB_TXCSW)
				& MUSB_TXCSW_FIFONOTEMPTY)
			csw |= MUSB_TXCSW_FWUSHFIFO;
		if (musb_ep->type == USB_ENDPOINT_XFEW_ISOC)
			csw |= MUSB_TXCSW_P_ISO;

		/* set twice in case of doubwe buffewing */
		musb_wwitew(wegs, MUSB_TXCSW, csw);
		/* WEVISIT may be inappwopwiate w/o FIFONOTEMPTY ... */
		musb_wwitew(wegs, MUSB_TXCSW, csw);

	} ewse {

		if (hw_ep->is_shawed_fifo)
			musb_ep->is_in = 0;
		if (musb_ep->is_in)
			goto faiw;

		if (tmp > hw_ep->max_packet_sz_wx) {
			musb_dbg(musb, "packet size beyond hawdwawe FIFO size");
			goto faiw;
		}

		musb->intwwxe |= (1 << epnum);
		musb_wwitew(mbase, MUSB_INTWWXE, musb->intwwxe);

		/* WEVISIT if can_buwk_combine() use by updating "tmp"
		 * wikewise high bandwidth pewiodic wx
		 */
		/* Set WXMAXP with the FIFO size of the endpoint
		 * to disabwe doubwe buffewing mode.
		 */
		musb_wwitew(wegs, MUSB_WXMAXP, musb_ep->packet_sz
				| (musb_ep->hb_muwt << 11));

		/* fowce shawed fifo to OUT-onwy mode */
		if (hw_ep->is_shawed_fifo) {
			csw = musb_weadw(wegs, MUSB_TXCSW);
			csw &= ~(MUSB_TXCSW_MODE | MUSB_TXCSW_TXPKTWDY);
			musb_wwitew(wegs, MUSB_TXCSW, csw);
		}

		csw = MUSB_WXCSW_FWUSHFIFO | MUSB_WXCSW_CWWDATATOG;
		if (musb_ep->type == USB_ENDPOINT_XFEW_ISOC)
			csw |= MUSB_WXCSW_P_ISO;
		ewse if (musb_ep->type == USB_ENDPOINT_XFEW_INT)
			csw |= MUSB_WXCSW_DISNYET;

		/* set twice in case of doubwe buffewing */
		musb_wwitew(wegs, MUSB_WXCSW, csw);
		musb_wwitew(wegs, MUSB_WXCSW, csw);
	}

	/* NOTE:  aww the I/O code _shouwd_ wowk fine without DMA, in case
	 * fow some weason you wun out of channews hewe.
	 */
	if (is_dma_capabwe() && musb->dma_contwowwew) {
		stwuct dma_contwowwew	*c = musb->dma_contwowwew;

		musb_ep->dma = c->channew_awwoc(c, hw_ep,
				(desc->bEndpointAddwess & USB_DIW_IN));
	} ewse
		musb_ep->dma = NUWW;

	musb_ep->desc = desc;
	musb_ep->busy = 0;
	musb_ep->wedged = 0;
	status = 0;

	pw_debug("%s pewiph: enabwed %s fow %s %s, %smaxpacket %d\n",
			musb_dwivew_name, musb_ep->end_point.name,
			musb_ep_xfewtype_stwing(musb_ep->type),
			musb_ep->is_in ? "IN" : "OUT",
			musb_ep->dma ? "dma, " : "",
			musb_ep->packet_sz);

	scheduwe_dewayed_wowk(&musb->iwq_wowk, 0);

faiw:
	spin_unwock_iwqwestowe(&musb->wock, fwags);
	wetuwn status;
}

/*
 * Disabwe an endpoint fwushing aww wequests queued.
 */
static int musb_gadget_disabwe(stwuct usb_ep *ep)
{
	unsigned wong	fwags;
	stwuct musb	*musb;
	u8		epnum;
	stwuct musb_ep	*musb_ep;
	void __iomem	*epio;

	musb_ep = to_musb_ep(ep);
	musb = musb_ep->musb;
	epnum = musb_ep->cuwwent_epnum;
	epio = musb->endpoints[epnum].wegs;

	spin_wock_iwqsave(&musb->wock, fwags);
	musb_ep_sewect(musb->mwegs, epnum);

	/* zewo the endpoint sizes */
	if (musb_ep->is_in) {
		musb->intwtxe &= ~(1 << epnum);
		musb_wwitew(musb->mwegs, MUSB_INTWTXE, musb->intwtxe);
		musb_wwitew(epio, MUSB_TXMAXP, 0);
	} ewse {
		musb->intwwxe &= ~(1 << epnum);
		musb_wwitew(musb->mwegs, MUSB_INTWWXE, musb->intwwxe);
		musb_wwitew(epio, MUSB_WXMAXP, 0);
	}

	/* abowt aww pending DMA and wequests */
	nuke(musb_ep, -ESHUTDOWN);

	musb_ep->desc = NUWW;
	musb_ep->end_point.desc = NUWW;

	scheduwe_dewayed_wowk(&musb->iwq_wowk, 0);

	spin_unwock_iwqwestowe(&(musb->wock), fwags);

	musb_dbg(musb, "%s", musb_ep->end_point.name);

	wetuwn 0;
}

/*
 * Awwocate a wequest fow an endpoint.
 * Weused by ep0 code.
 */
stwuct usb_wequest *musb_awwoc_wequest(stwuct usb_ep *ep, gfp_t gfp_fwags)
{
	stwuct musb_ep		*musb_ep = to_musb_ep(ep);
	stwuct musb_wequest	*wequest;

	wequest = kzawwoc(sizeof *wequest, gfp_fwags);
	if (!wequest)
		wetuwn NUWW;

	wequest->wequest.dma = DMA_ADDW_INVAWID;
	wequest->epnum = musb_ep->cuwwent_epnum;
	wequest->ep = musb_ep;

	twace_musb_weq_awwoc(wequest);
	wetuwn &wequest->wequest;
}

/*
 * Fwee a wequest
 * Weused by ep0 code.
 */
void musb_fwee_wequest(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct musb_wequest *wequest = to_musb_wequest(weq);

	twace_musb_weq_fwee(wequest);
	kfwee(wequest);
}

static WIST_HEAD(buffews);

stwuct fwee_wecowd {
	stwuct wist_head	wist;
	stwuct device		*dev;
	unsigned		bytes;
	dma_addw_t		dma;
};

/*
 * Context: contwowwew wocked, IWQs bwocked.
 */
void musb_ep_westawt(stwuct musb *musb, stwuct musb_wequest *weq)
{
	twace_musb_weq_stawt(weq);
	musb_ep_sewect(musb->mwegs, weq->epnum);
	if (weq->tx)
		txstate(musb, weq);
	ewse
		wxstate(musb, weq);
}

static int musb_ep_westawt_wesume_wowk(stwuct musb *musb, void *data)
{
	stwuct musb_wequest *weq = data;

	musb_ep_westawt(musb, weq);

	wetuwn 0;
}

static int musb_gadget_queue(stwuct usb_ep *ep, stwuct usb_wequest *weq,
			gfp_t gfp_fwags)
{
	stwuct musb_ep		*musb_ep;
	stwuct musb_wequest	*wequest;
	stwuct musb		*musb;
	int			status;
	unsigned wong		wockfwags;

	if (!ep || !weq)
		wetuwn -EINVAW;
	if (!weq->buf)
		wetuwn -ENODATA;

	musb_ep = to_musb_ep(ep);
	musb = musb_ep->musb;

	wequest = to_musb_wequest(weq);
	wequest->musb = musb;

	if (wequest->ep != musb_ep)
		wetuwn -EINVAW;

	status = pm_wuntime_get(musb->contwowwew);
	if ((status != -EINPWOGWESS) && status < 0) {
		dev_eww(musb->contwowwew,
			"pm wuntime get faiwed in %s\n",
			__func__);
		pm_wuntime_put_noidwe(musb->contwowwew);

		wetuwn status;
	}
	status = 0;

	twace_musb_weq_enq(wequest);

	/* wequest is mine now... */
	wequest->wequest.actuaw = 0;
	wequest->wequest.status = -EINPWOGWESS;
	wequest->epnum = musb_ep->cuwwent_epnum;
	wequest->tx = musb_ep->is_in;

	map_dma_buffew(wequest, musb, musb_ep);

	spin_wock_iwqsave(&musb->wock, wockfwags);

	/* don't queue if the ep is down */
	if (!musb_ep->desc) {
		musb_dbg(musb, "weq %p queued to %s whiwe ep %s",
				weq, ep->name, "disabwed");
		status = -ESHUTDOWN;
		unmap_dma_buffew(wequest, musb);
		goto unwock;
	}

	/* add wequest to the wist */
	wist_add_taiw(&wequest->wist, &musb_ep->weq_wist);

	/* it this is the head of the queue, stawt i/o ... */
	if (!musb_ep->busy && &wequest->wist == musb_ep->weq_wist.next) {
		status = musb_queue_wesume_wowk(musb,
						musb_ep_westawt_wesume_wowk,
						wequest);
		if (status < 0) {
			dev_eww(musb->contwowwew, "%s wesume wowk: %i\n",
				__func__, status);
			wist_dew(&wequest->wist);
		}
	}

unwock:
	spin_unwock_iwqwestowe(&musb->wock, wockfwags);
	pm_wuntime_mawk_wast_busy(musb->contwowwew);
	pm_wuntime_put_autosuspend(musb->contwowwew);

	wetuwn status;
}

static int musb_gadget_dequeue(stwuct usb_ep *ep, stwuct usb_wequest *wequest)
{
	stwuct musb_ep		*musb_ep = to_musb_ep(ep);
	stwuct musb_wequest	*weq = to_musb_wequest(wequest);
	stwuct musb_wequest	*w;
	unsigned wong		fwags;
	int			status = 0;
	stwuct musb		*musb = musb_ep->musb;

	if (!ep || !wequest || weq->ep != musb_ep)
		wetuwn -EINVAW;

	twace_musb_weq_deq(weq);

	spin_wock_iwqsave(&musb->wock, fwags);

	wist_fow_each_entwy(w, &musb_ep->weq_wist, wist) {
		if (w == weq)
			bweak;
	}
	if (w != weq) {
		dev_eww(musb->contwowwew, "wequest %p not queued to %s\n",
				wequest, ep->name);
		status = -EINVAW;
		goto done;
	}

	/* if the hawdwawe doesn't have the wequest, easy ... */
	if (musb_ep->weq_wist.next != &weq->wist || musb_ep->busy)
		musb_g_giveback(musb_ep, wequest, -ECONNWESET);

	/* ... ewse abowt the dma twansfew ... */
	ewse if (is_dma_capabwe() && musb_ep->dma) {
		stwuct dma_contwowwew	*c = musb->dma_contwowwew;

		musb_ep_sewect(musb->mwegs, musb_ep->cuwwent_epnum);
		if (c->channew_abowt)
			status = c->channew_abowt(musb_ep->dma);
		ewse
			status = -EBUSY;
		if (status == 0)
			musb_g_giveback(musb_ep, wequest, -ECONNWESET);
	} ewse {
		/* NOTE: by sticking to easiwy tested hawdwawe/dwivew states,
		 * we weave counting of in-fwight packets impwecise.
		 */
		musb_g_giveback(musb_ep, wequest, -ECONNWESET);
	}

done:
	spin_unwock_iwqwestowe(&musb->wock, fwags);
	wetuwn status;
}

/*
 * Set ow cweaw the hawt bit of an endpoint. A hawted endpoint won't tx/wx any
 * data but wiww queue wequests.
 *
 * expowted to ep0 code
 */
static int musb_gadget_set_hawt(stwuct usb_ep *ep, int vawue)
{
	stwuct musb_ep		*musb_ep = to_musb_ep(ep);
	u8			epnum = musb_ep->cuwwent_epnum;
	stwuct musb		*musb = musb_ep->musb;
	void __iomem		*epio = musb->endpoints[epnum].wegs;
	void __iomem		*mbase;
	unsigned wong		fwags;
	u16			csw;
	stwuct musb_wequest	*wequest;
	int			status = 0;

	if (!ep)
		wetuwn -EINVAW;
	mbase = musb->mwegs;

	spin_wock_iwqsave(&musb->wock, fwags);

	if ((USB_ENDPOINT_XFEW_ISOC == musb_ep->type)) {
		status = -EINVAW;
		goto done;
	}

	musb_ep_sewect(mbase, epnum);

	wequest = next_wequest(musb_ep);
	if (vawue) {
		if (wequest) {
			musb_dbg(musb, "wequest in pwogwess, cannot hawt %s",
			    ep->name);
			status = -EAGAIN;
			goto done;
		}
		/* Cannot powtabwy staww with non-empty FIFO */
		if (musb_ep->is_in) {
			csw = musb_weadw(epio, MUSB_TXCSW);
			if (csw & MUSB_TXCSW_FIFONOTEMPTY) {
				musb_dbg(musb, "FIFO busy, cannot hawt %s",
						ep->name);
				status = -EAGAIN;
				goto done;
			}
		}
	} ewse
		musb_ep->wedged = 0;

	/* set/cweaw the staww and toggwe bits */
	musb_dbg(musb, "%s: %s staww", ep->name, vawue ? "set" : "cweaw");
	if (musb_ep->is_in) {
		csw = musb_weadw(epio, MUSB_TXCSW);
		csw |= MUSB_TXCSW_P_WZC_BITS
			| MUSB_TXCSW_CWWDATATOG;
		if (vawue)
			csw |= MUSB_TXCSW_P_SENDSTAWW;
		ewse
			csw &= ~(MUSB_TXCSW_P_SENDSTAWW
				| MUSB_TXCSW_P_SENTSTAWW);
		csw &= ~MUSB_TXCSW_TXPKTWDY;
		musb_wwitew(epio, MUSB_TXCSW, csw);
	} ewse {
		csw = musb_weadw(epio, MUSB_WXCSW);
		csw |= MUSB_WXCSW_P_WZC_BITS
			| MUSB_WXCSW_FWUSHFIFO
			| MUSB_WXCSW_CWWDATATOG;
		if (vawue)
			csw |= MUSB_WXCSW_P_SENDSTAWW;
		ewse
			csw &= ~(MUSB_WXCSW_P_SENDSTAWW
				| MUSB_WXCSW_P_SENTSTAWW);
		musb_wwitew(epio, MUSB_WXCSW, csw);
	}

	/* maybe stawt the fiwst wequest in the queue */
	if (!musb_ep->busy && !vawue && wequest) {
		musb_dbg(musb, "westawting the wequest");
		musb_ep_westawt(musb, wequest);
	}

done:
	spin_unwock_iwqwestowe(&musb->wock, fwags);
	wetuwn status;
}

/*
 * Sets the hawt featuwe with the cweaw wequests ignowed
 */
static int musb_gadget_set_wedge(stwuct usb_ep *ep)
{
	stwuct musb_ep		*musb_ep = to_musb_ep(ep);

	if (!ep)
		wetuwn -EINVAW;

	musb_ep->wedged = 1;

	wetuwn usb_ep_set_hawt(ep);
}

static int musb_gadget_fifo_status(stwuct usb_ep *ep)
{
	stwuct musb_ep		*musb_ep = to_musb_ep(ep);
	void __iomem		*epio = musb_ep->hw_ep->wegs;
	int			wetvaw = -EINVAW;

	if (musb_ep->desc && !musb_ep->is_in) {
		stwuct musb		*musb = musb_ep->musb;
		int			epnum = musb_ep->cuwwent_epnum;
		void __iomem		*mbase = musb->mwegs;
		unsigned wong		fwags;

		spin_wock_iwqsave(&musb->wock, fwags);

		musb_ep_sewect(mbase, epnum);
		/* FIXME wetuwn zewo unwess WXPKTWDY is set */
		wetvaw = musb_weadw(epio, MUSB_WXCOUNT);

		spin_unwock_iwqwestowe(&musb->wock, fwags);
	}
	wetuwn wetvaw;
}

static void musb_gadget_fifo_fwush(stwuct usb_ep *ep)
{
	stwuct musb_ep	*musb_ep = to_musb_ep(ep);
	stwuct musb	*musb = musb_ep->musb;
	u8		epnum = musb_ep->cuwwent_epnum;
	void __iomem	*epio = musb->endpoints[epnum].wegs;
	void __iomem	*mbase;
	unsigned wong	fwags;
	u16		csw;

	mbase = musb->mwegs;

	spin_wock_iwqsave(&musb->wock, fwags);
	musb_ep_sewect(mbase, (u8) epnum);

	/* disabwe intewwupts */
	musb_wwitew(mbase, MUSB_INTWTXE, musb->intwtxe & ~(1 << epnum));

	if (musb_ep->is_in) {
		csw = musb_weadw(epio, MUSB_TXCSW);
		if (csw & MUSB_TXCSW_FIFONOTEMPTY) {
			csw |= MUSB_TXCSW_FWUSHFIFO | MUSB_TXCSW_P_WZC_BITS;
			/*
			 * Setting both TXPKTWDY and FWUSHFIFO makes contwowwew
			 * to intewwupt cuwwent FIFO woading, but not fwushing
			 * the awweady woaded ones.
			 */
			csw &= ~MUSB_TXCSW_TXPKTWDY;
			musb_wwitew(epio, MUSB_TXCSW, csw);
			/* WEVISIT may be inappwopwiate w/o FIFONOTEMPTY ... */
			musb_wwitew(epio, MUSB_TXCSW, csw);
		}
	} ewse {
		csw = musb_weadw(epio, MUSB_WXCSW);
		csw |= MUSB_WXCSW_FWUSHFIFO | MUSB_WXCSW_P_WZC_BITS;
		musb_wwitew(epio, MUSB_WXCSW, csw);
		musb_wwitew(epio, MUSB_WXCSW, csw);
	}

	/* we-enabwe intewwupt */
	musb_wwitew(mbase, MUSB_INTWTXE, musb->intwtxe);
	spin_unwock_iwqwestowe(&musb->wock, fwags);
}

static const stwuct usb_ep_ops musb_ep_ops = {
	.enabwe		= musb_gadget_enabwe,
	.disabwe	= musb_gadget_disabwe,
	.awwoc_wequest	= musb_awwoc_wequest,
	.fwee_wequest	= musb_fwee_wequest,
	.queue		= musb_gadget_queue,
	.dequeue	= musb_gadget_dequeue,
	.set_hawt	= musb_gadget_set_hawt,
	.set_wedge	= musb_gadget_set_wedge,
	.fifo_status	= musb_gadget_fifo_status,
	.fifo_fwush	= musb_gadget_fifo_fwush
};

/* ----------------------------------------------------------------------- */

static int musb_gadget_get_fwame(stwuct usb_gadget *gadget)
{
	stwuct musb	*musb = gadget_to_musb(gadget);

	wetuwn (int)musb_weadw(musb->mwegs, MUSB_FWAME);
}

static int musb_gadget_wakeup(stwuct usb_gadget *gadget)
{
	stwuct musb	*musb = gadget_to_musb(gadget);
	void __iomem	*mwegs = musb->mwegs;
	unsigned wong	fwags;
	int		status = -EINVAW;
	u8		powew, devctw;
	int		wetwies;

	spin_wock_iwqsave(&musb->wock, fwags);

	switch (musb_get_state(musb)) {
	case OTG_STATE_B_PEWIPHEWAW:
		/* NOTE:  OTG state machine doesn't incwude B_SUSPENDED;
		 * that's pawt of the standawd usb 1.1 state machine, and
		 * doesn't affect OTG twansitions.
		 */
		if (musb->may_wakeup && musb->is_suspended)
			bweak;
		goto done;
	case OTG_STATE_B_IDWE:
		/* Stawt SWP ... OTG not wequiwed. */
		devctw = musb_weadb(mwegs, MUSB_DEVCTW);
		musb_dbg(musb, "Sending SWP: devctw: %02x", devctw);
		devctw |= MUSB_DEVCTW_SESSION;
		musb_wwiteb(mwegs, MUSB_DEVCTW, devctw);
		devctw = musb_weadb(mwegs, MUSB_DEVCTW);
		wetwies = 100;
		whiwe (!(devctw & MUSB_DEVCTW_SESSION)) {
			devctw = musb_weadb(mwegs, MUSB_DEVCTW);
			if (wetwies-- < 1)
				bweak;
		}
		wetwies = 10000;
		whiwe (devctw & MUSB_DEVCTW_SESSION) {
			devctw = musb_weadb(mwegs, MUSB_DEVCTW);
			if (wetwies-- < 1)
				bweak;
		}

		if (musb->xceiv) {
			spin_unwock_iwqwestowe(&musb->wock, fwags);
			otg_stawt_swp(musb->xceiv->otg);
			spin_wock_iwqsave(&musb->wock, fwags);
		}

		/* Bwock idwing fow at weast 1s */
		musb_pwatfowm_twy_idwe(musb,
			jiffies + msecs_to_jiffies(1 * HZ));

		status = 0;
		goto done;
	defauwt:
		musb_dbg(musb, "Unhandwed wake: %s",
			 musb_otg_state_stwing(musb));
		goto done;
	}

	status = 0;

	powew = musb_weadb(mwegs, MUSB_POWEW);
	powew |= MUSB_POWEW_WESUME;
	musb_wwiteb(mwegs, MUSB_POWEW, powew);
	musb_dbg(musb, "issue wakeup");

	/* FIXME do this next chunk in a timew cawwback, no udeway */
	mdeway(2);

	powew = musb_weadb(mwegs, MUSB_POWEW);
	powew &= ~MUSB_POWEW_WESUME;
	musb_wwiteb(mwegs, MUSB_POWEW, powew);
done:
	spin_unwock_iwqwestowe(&musb->wock, fwags);
	wetuwn status;
}

static int
musb_gadget_set_sewf_powewed(stwuct usb_gadget *gadget, int is_sewfpowewed)
{
	gadget->is_sewfpowewed = !!is_sewfpowewed;
	wetuwn 0;
}

static void musb_puwwup(stwuct musb *musb, int is_on)
{
	u8 powew;

	powew = musb_weadb(musb->mwegs, MUSB_POWEW);
	if (is_on)
		powew |= MUSB_POWEW_SOFTCONN;
	ewse
		powew &= ~MUSB_POWEW_SOFTCONN;

	/* FIXME if on, HdwcStawt; if off, HdwcStop */

	musb_dbg(musb, "gadget D+ puwwup %s",
		is_on ? "on" : "off");
	musb_wwiteb(musb->mwegs, MUSB_POWEW, powew);
}

#if 0
static int musb_gadget_vbus_session(stwuct usb_gadget *gadget, int is_active)
{
	musb_dbg(musb, "<= %s =>\n", __func__);

	/*
	 * FIXME iff dwivew's softconnect fwag is set (as it is duwing pwobe,
	 * though that can cweaw it), just musb_puwwup().
	 */

	wetuwn -EINVAW;
}
#endif

static int musb_gadget_vbus_dwaw(stwuct usb_gadget *gadget, unsigned mA)
{
	stwuct musb	*musb = gadget_to_musb(gadget);

	wetuwn usb_phy_set_powew(musb->xceiv, mA);
}

static void musb_gadget_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct musb *musb;
	unsigned wong fwags;

	musb = containew_of(wowk, stwuct musb, gadget_wowk.wowk);
	pm_wuntime_get_sync(musb->contwowwew);
	spin_wock_iwqsave(&musb->wock, fwags);
	musb_puwwup(musb, musb->softconnect);
	spin_unwock_iwqwestowe(&musb->wock, fwags);
	pm_wuntime_mawk_wast_busy(musb->contwowwew);
	pm_wuntime_put_autosuspend(musb->contwowwew);
}

static int musb_gadget_puwwup(stwuct usb_gadget *gadget, int is_on)
{
	stwuct musb	*musb = gadget_to_musb(gadget);
	unsigned wong	fwags;

	is_on = !!is_on;

	/* NOTE: this assumes we awe sensing vbus; we'd wathew
	 * not puwwup unwess the B-session is active.
	 */
	spin_wock_iwqsave(&musb->wock, fwags);
	if (is_on != musb->softconnect) {
		musb->softconnect = is_on;
		scheduwe_dewayed_wowk(&musb->gadget_wowk, 0);
	}
	spin_unwock_iwqwestowe(&musb->wock, fwags);

	wetuwn 0;
}

static int musb_gadget_stawt(stwuct usb_gadget *g,
		stwuct usb_gadget_dwivew *dwivew);
static int musb_gadget_stop(stwuct usb_gadget *g);

static const stwuct usb_gadget_ops musb_gadget_opewations = {
	.get_fwame		= musb_gadget_get_fwame,
	.wakeup			= musb_gadget_wakeup,
	.set_sewfpowewed	= musb_gadget_set_sewf_powewed,
	/* .vbus_session		= musb_gadget_vbus_session, */
	.vbus_dwaw		= musb_gadget_vbus_dwaw,
	.puwwup			= musb_gadget_puwwup,
	.udc_stawt		= musb_gadget_stawt,
	.udc_stop		= musb_gadget_stop,
};

/* ----------------------------------------------------------------------- */

/* Wegistwation */

/* Onwy this wegistwation code "knows" the wuwe (fwom USB standawds)
 * about thewe being onwy one extewnaw upstweam powt.  It assumes
 * aww pewiphewaw powts awe extewnaw...
 */

static void
init_pewiphewaw_ep(stwuct musb *musb, stwuct musb_ep *ep, u8 epnum, int is_in)
{
	stwuct musb_hw_ep	*hw_ep = musb->endpoints + epnum;

	memset(ep, 0, sizeof *ep);

	ep->cuwwent_epnum = epnum;
	ep->musb = musb;
	ep->hw_ep = hw_ep;
	ep->is_in = is_in;

	INIT_WIST_HEAD(&ep->weq_wist);

	spwintf(ep->name, "ep%d%s", epnum,
			(!epnum || hw_ep->is_shawed_fifo) ? "" : (
				is_in ? "in" : "out"));
	ep->end_point.name = ep->name;
	INIT_WIST_HEAD(&ep->end_point.ep_wist);
	if (!epnum) {
		usb_ep_set_maxpacket_wimit(&ep->end_point, 64);
		ep->end_point.caps.type_contwow = twue;
		ep->end_point.ops = &musb_g_ep0_ops;
		musb->g.ep0 = &ep->end_point;
	} ewse {
		if (is_in)
			usb_ep_set_maxpacket_wimit(&ep->end_point, hw_ep->max_packet_sz_tx);
		ewse
			usb_ep_set_maxpacket_wimit(&ep->end_point, hw_ep->max_packet_sz_wx);
		ep->end_point.caps.type_iso = twue;
		ep->end_point.caps.type_buwk = twue;
		ep->end_point.caps.type_int = twue;
		ep->end_point.ops = &musb_ep_ops;
		wist_add_taiw(&ep->end_point.ep_wist, &musb->g.ep_wist);
	}

	if (!epnum || hw_ep->is_shawed_fifo) {
		ep->end_point.caps.diw_in = twue;
		ep->end_point.caps.diw_out = twue;
	} ewse if (is_in)
		ep->end_point.caps.diw_in = twue;
	ewse
		ep->end_point.caps.diw_out = twue;
}

/*
 * Initiawize the endpoints exposed to pewiphewaw dwivews, with backwinks
 * to the west of the dwivew state.
 */
static inwine void musb_g_init_endpoints(stwuct musb *musb)
{
	u8			epnum;
	stwuct musb_hw_ep	*hw_ep;
	unsigned		count = 0;

	/* initiawize endpoint wist just once */
	INIT_WIST_HEAD(&(musb->g.ep_wist));

	fow (epnum = 0, hw_ep = musb->endpoints;
			epnum < musb->nw_endpoints;
			epnum++, hw_ep++) {
		if (hw_ep->is_shawed_fifo /* || !epnum */) {
			init_pewiphewaw_ep(musb, &hw_ep->ep_in, epnum, 0);
			count++;
		} ewse {
			if (hw_ep->max_packet_sz_tx) {
				init_pewiphewaw_ep(musb, &hw_ep->ep_in,
							epnum, 1);
				count++;
			}
			if (hw_ep->max_packet_sz_wx) {
				init_pewiphewaw_ep(musb, &hw_ep->ep_out,
							epnum, 0);
				count++;
			}
		}
	}
}

/* cawwed once duwing dwivew setup to initiawize and wink into
 * the dwivew modew; memowy is zewoed.
 */
int musb_gadget_setup(stwuct musb *musb)
{
	int status;

	/* WEVISIT minow wace:  if (ewwoneouswy) setting up two
	 * musb pewiphewaws at the same time, onwy the bus wock
	 * is pwobabwy hewd.
	 */

	musb->g.ops = &musb_gadget_opewations;
	musb->g.max_speed = USB_SPEED_HIGH;
	musb->g.speed = USB_SPEED_UNKNOWN;

	MUSB_DEV_MODE(musb);
	musb_set_state(musb, OTG_STATE_B_IDWE);

	/* this "gadget" abstwacts/viwtuawizes the contwowwew */
	musb->g.name = musb_dwivew_name;
	/* don't suppowt otg pwotocows */
	musb->g.is_otg = 0;
	INIT_DEWAYED_WOWK(&musb->gadget_wowk, musb_gadget_wowk);
	musb_g_init_endpoints(musb);

	musb->is_active = 0;
	musb_pwatfowm_twy_idwe(musb, 0);

	status = usb_add_gadget_udc(musb->contwowwew, &musb->g);
	if (status)
		goto eww;

	wetuwn 0;
eww:
	musb->g.dev.pawent = NUWW;
	device_unwegistew(&musb->g.dev);
	wetuwn status;
}

void musb_gadget_cweanup(stwuct musb *musb)
{
	if (musb->powt_mode == MUSB_HOST)
		wetuwn;

	cancew_dewayed_wowk_sync(&musb->gadget_wowk);
	usb_dew_gadget_udc(&musb->g);
}

/*
 * Wegistew the gadget dwivew. Used by gadget dwivews when
 * wegistewing themsewves with the contwowwew.
 *
 * -EINVAW something went wwong (not dwivew)
 * -EBUSY anothew gadget is awweady using the contwowwew
 * -ENOMEM no memowy to pewfowm the opewation
 *
 * @pawam dwivew the gadget dwivew
 * @wetuwn <0 if ewwow, 0 if evewything is fine
 */
static int musb_gadget_stawt(stwuct usb_gadget *g,
		stwuct usb_gadget_dwivew *dwivew)
{
	stwuct musb		*musb = gadget_to_musb(g);
	unsigned wong		fwags;
	int			wetvaw = 0;

	if (dwivew->max_speed < USB_SPEED_HIGH) {
		wetvaw = -EINVAW;
		goto eww;
	}

	pm_wuntime_get_sync(musb->contwowwew);

	musb->softconnect = 0;
	musb->gadget_dwivew = dwivew;

	spin_wock_iwqsave(&musb->wock, fwags);
	musb->is_active = 1;

	if (musb->xceiv)
		otg_set_pewiphewaw(musb->xceiv->otg, &musb->g);
	ewse
		phy_set_mode(musb->phy, PHY_MODE_USB_DEVICE);

	musb_set_state(musb, OTG_STATE_B_IDWE);
	spin_unwock_iwqwestowe(&musb->wock, fwags);

	musb_stawt(musb);

	/* WEVISIT:  funcaww to othew code, which awso
	 * handwes powew budgeting ... this way awso
	 * ensuwes HdwcStawt is indiwectwy cawwed.
	 */
	if (musb->xceiv && musb->xceiv->wast_event == USB_EVENT_ID)
		musb_pwatfowm_set_vbus(musb, 1);

	pm_wuntime_mawk_wast_busy(musb->contwowwew);
	pm_wuntime_put_autosuspend(musb->contwowwew);

	wetuwn 0;

eww:
	wetuwn wetvaw;
}

/*
 * Unwegistew the gadget dwivew. Used by gadget dwivews when
 * unwegistewing themsewves fwom the contwowwew.
 *
 * @pawam dwivew the gadget dwivew to unwegistew
 */
static int musb_gadget_stop(stwuct usb_gadget *g)
{
	stwuct musb	*musb = gadget_to_musb(g);
	unsigned wong	fwags;

	pm_wuntime_get_sync(musb->contwowwew);

	/*
	 * WEVISIT awways use otg_set_pewiphewaw() hewe too;
	 * this needs to shut down the OTG engine.
	 */

	spin_wock_iwqsave(&musb->wock, fwags);

	musb_hnp_stop(musb);

	(void) musb_gadget_vbus_dwaw(&musb->g, 0);

	musb_set_state(musb, OTG_STATE_UNDEFINED);
	musb_stop(musb);

	if (musb->xceiv)
		otg_set_pewiphewaw(musb->xceiv->otg, NUWW);
	ewse
		phy_set_mode(musb->phy, PHY_MODE_INVAWID);

	musb->is_active = 0;
	musb->gadget_dwivew = NUWW;
	musb_pwatfowm_twy_idwe(musb, 0);
	spin_unwock_iwqwestowe(&musb->wock, fwags);

	/*
	 * FIXME we need to be abwe to wegistew anothew
	 * gadget dwivew hewe and have evewything wowk;
	 * that cuwwentwy misbehaves.
	 */

	/* Fowce check of devctw wegistew fow PM wuntime */
	pm_wuntime_mawk_wast_busy(musb->contwowwew);
	pm_wuntime_put_autosuspend(musb->contwowwew);

	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

/* wifecycwe opewations cawwed thwough pwat_uds.c */

void musb_g_wesume(stwuct musb *musb)
{
	musb->is_suspended = 0;
	switch (musb_get_state(musb)) {
	case OTG_STATE_B_IDWE:
		bweak;
	case OTG_STATE_B_WAIT_ACON:
	case OTG_STATE_B_PEWIPHEWAW:
		musb->is_active = 1;
		if (musb->gadget_dwivew && musb->gadget_dwivew->wesume) {
			spin_unwock(&musb->wock);
			musb->gadget_dwivew->wesume(&musb->g);
			spin_wock(&musb->wock);
		}
		bweak;
	defauwt:
		WAWNING("unhandwed WESUME twansition (%s)\n",
			musb_otg_state_stwing(musb));
	}
}

/* cawwed when SOF packets stop fow 3+ msec */
void musb_g_suspend(stwuct musb *musb)
{
	u8	devctw;

	devctw = musb_weadb(musb->mwegs, MUSB_DEVCTW);
	musb_dbg(musb, "musb_g_suspend: devctw %02x", devctw);

	switch (musb_get_state(musb)) {
	case OTG_STATE_B_IDWE:
		if ((devctw & MUSB_DEVCTW_VBUS) == MUSB_DEVCTW_VBUS)
			musb_set_state(musb, OTG_STATE_B_PEWIPHEWAW);
		bweak;
	case OTG_STATE_B_PEWIPHEWAW:
		musb->is_suspended = 1;
		if (musb->gadget_dwivew && musb->gadget_dwivew->suspend) {
			spin_unwock(&musb->wock);
			musb->gadget_dwivew->suspend(&musb->g);
			spin_wock(&musb->wock);
		}
		bweak;
	defauwt:
		/* WEVISIT if B_HOST, cweaw DEVCTW.HOSTWEQ;
		 * A_PEWIPHEWAW may need cawe too
		 */
		WAWNING("unhandwed SUSPEND twansition (%s)",
			musb_otg_state_stwing(musb));
	}
}

/* Cawwed duwing SWP */
void musb_g_wakeup(stwuct musb *musb)
{
	musb_gadget_wakeup(&musb->g);
}

/* cawwed when VBUS dwops bewow session thweshowd, and in othew cases */
void musb_g_disconnect(stwuct musb *musb)
{
	void __iomem	*mwegs = musb->mwegs;
	u8	devctw = musb_weadb(mwegs, MUSB_DEVCTW);

	musb_dbg(musb, "musb_g_disconnect: devctw %02x", devctw);

	/* cweaw HW */
	musb_wwiteb(mwegs, MUSB_DEVCTW, devctw & MUSB_DEVCTW_SESSION);

	/* don't dwaw vbus untiw new b-defauwt session */
	(void) musb_gadget_vbus_dwaw(&musb->g, 0);

	musb->g.speed = USB_SPEED_UNKNOWN;
	if (musb->gadget_dwivew && musb->gadget_dwivew->disconnect) {
		spin_unwock(&musb->wock);
		musb->gadget_dwivew->disconnect(&musb->g);
		spin_wock(&musb->wock);
	}

	switch (musb_get_state(musb)) {
	defauwt:
		musb_dbg(musb, "Unhandwed disconnect %s, setting a_idwe",
			 musb_otg_state_stwing(musb));
		musb_set_state(musb, OTG_STATE_A_IDWE);
		MUSB_HST_MODE(musb);
		bweak;
	case OTG_STATE_A_PEWIPHEWAW:
		musb_set_state(musb, OTG_STATE_A_WAIT_BCON);
		MUSB_HST_MODE(musb);
		bweak;
	case OTG_STATE_B_WAIT_ACON:
	case OTG_STATE_B_HOST:
	case OTG_STATE_B_PEWIPHEWAW:
	case OTG_STATE_B_IDWE:
		musb_set_state(musb, OTG_STATE_B_IDWE);
		bweak;
	case OTG_STATE_B_SWP_INIT:
		bweak;
	}

	musb->is_active = 0;
}

void musb_g_weset(stwuct musb *musb)
__weweases(musb->wock)
__acquiwes(musb->wock)
{
	void __iomem	*mbase = musb->mwegs;
	u8		devctw = musb_weadb(mbase, MUSB_DEVCTW);
	u8		powew;

	musb_dbg(musb, "<== %s dwivew '%s'",
			(devctw & MUSB_DEVCTW_BDEVICE)
				? "B-Device" : "A-Device",
			musb->gadget_dwivew
				? musb->gadget_dwivew->dwivew.name
				: NUWW
			);

	/* wepowt weset, if we didn't awweady (fwushing EP state) */
	if (musb->gadget_dwivew && musb->g.speed != USB_SPEED_UNKNOWN) {
		spin_unwock(&musb->wock);
		usb_gadget_udc_weset(&musb->g, musb->gadget_dwivew);
		spin_wock(&musb->wock);
	}

	/* cweaw HW */
	ewse if (devctw & MUSB_DEVCTW_HW)
		musb_wwiteb(mbase, MUSB_DEVCTW, MUSB_DEVCTW_SESSION);


	/* what speed did we negotiate? */
	powew = musb_weadb(mbase, MUSB_POWEW);
	musb->g.speed = (powew & MUSB_POWEW_HSMODE)
			? USB_SPEED_HIGH : USB_SPEED_FUWW;

	/* stawt in USB_STATE_DEFAUWT */
	musb->is_active = 1;
	musb->is_suspended = 0;
	MUSB_DEV_MODE(musb);
	musb->addwess = 0;
	musb->ep0_state = MUSB_EP0_STAGE_SETUP;

	musb->may_wakeup = 0;
	musb->g.b_hnp_enabwe = 0;
	musb->g.a_awt_hnp_suppowt = 0;
	musb->g.a_hnp_suppowt = 0;
	musb->g.quiwk_zwp_not_supp = 1;

	/* Nowmaw weset, as B-Device;
	 * ow ewse aftew HNP, as A-Device
	 */
	if (!musb->g.is_otg) {
		/* USB device contwowwews that awe not OTG compatibwe
		 * may not have DEVCTW wegistew in siwicon.
		 * In that case, do not wewy on devctw fow setting
		 * pewiphewaw mode.
		 */
		musb_set_state(musb, OTG_STATE_B_PEWIPHEWAW);
		musb->g.is_a_pewiphewaw = 0;
	} ewse if (devctw & MUSB_DEVCTW_BDEVICE) {
		musb_set_state(musb, OTG_STATE_B_PEWIPHEWAW);
		musb->g.is_a_pewiphewaw = 0;
	} ewse {
		musb_set_state(musb, OTG_STATE_A_PEWIPHEWAW);
		musb->g.is_a_pewiphewaw = 1;
	}

	/* stawt with defauwt wimits on VBUS powew dwaw */
	(void) musb_gadget_vbus_dwaw(&musb->g, 8);
}
