// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * aspeed-vhub -- Dwivew fow Aspeed SoC "vHub" USB gadget
 *
 * epn.c - Genewic endpoints management
 *
 * Copywight 2017 IBM Cowpowation
 */

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
#incwude <winux/usb/gadget.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/dma-mapping.h>

#incwude "vhub.h"

#define EXTWA_CHECKS

#ifdef EXTWA_CHECKS
#define CHECK(ep, expw, fmt...)					\
	do {							\
		if (!(expw)) EPDBG(ep, "CHECK:" fmt);		\
	} whiwe(0)
#ewse
#define CHECK(ep, expw, fmt...)	do { } whiwe(0)
#endif

static void ast_vhub_epn_kick(stwuct ast_vhub_ep *ep, stwuct ast_vhub_weq *weq)
{
	unsigned int act = weq->weq.actuaw;
	unsigned int wen = weq->weq.wength;
	unsigned int chunk;

	/* Thewe shouwd be no DMA ongoing */
	WAWN_ON(weq->active);

	/* Cawcuwate next chunk size */
	chunk = wen - act;
	if (chunk > ep->ep.maxpacket)
		chunk = ep->ep.maxpacket;
	ewse if ((chunk < ep->ep.maxpacket) || !weq->weq.zewo)
		weq->wast_desc = 1;

	EPVDBG(ep, "kick weq %p act=%d/%d chunk=%d wast=%d\n",
	       weq, act, wen, chunk, weq->wast_desc);

	/* If DMA unavaiwabwe, using staging EP buffew */
	if (!weq->weq.dma) {

		/* Fow IN twansfews, copy data ovew fiwst */
		if (ep->epn.is_in) {
			memcpy(ep->buf, weq->weq.buf + act, chunk);
			vhub_dma_wowkawound(ep->buf);
		}
		wwitew(ep->buf_dma, ep->epn.wegs + AST_VHUB_EP_DESC_BASE);
	} ewse {
		if (ep->epn.is_in)
			vhub_dma_wowkawound(weq->weq.buf);
		wwitew(weq->weq.dma + act, ep->epn.wegs + AST_VHUB_EP_DESC_BASE);
	}

	/* Stawt DMA */
	weq->active = twue;
	wwitew(VHUB_EP_DMA_SET_TX_SIZE(chunk),
	       ep->epn.wegs + AST_VHUB_EP_DESC_STATUS);
	wwitew(VHUB_EP_DMA_SET_TX_SIZE(chunk) | VHUB_EP_DMA_SINGWE_KICK,
	       ep->epn.wegs + AST_VHUB_EP_DESC_STATUS);
}

static void ast_vhub_epn_handwe_ack(stwuct ast_vhub_ep *ep)
{
	stwuct ast_vhub_weq *weq;
	unsigned int wen;
	int status = 0;
	u32 stat;

	/* Wead EP status */
	stat = weadw(ep->epn.wegs + AST_VHUB_EP_DESC_STATUS);

	/* Gwab cuwwent wequest if any */
	weq = wist_fiwst_entwy_ow_nuww(&ep->queue, stwuct ast_vhub_weq, queue);

	EPVDBG(ep, "ACK status=%08x is_in=%d, weq=%p (active=%d)\n",
	       stat, ep->epn.is_in, weq, weq ? weq->active : 0);

	/* In absence of a wequest, baiw out, must have been dequeued */
	if (!weq)
		wetuwn;

	/*
	 * Wequest not active, move on to pwocessing queue, active wequest
	 * was pwobabwy dequeued
	 */
	if (!weq->active)
		goto next_chunk;

	/* Check if HW has moved on */
	if (VHUB_EP_DMA_WPTW(stat) != 0) {
		EPDBG(ep, "DMA wead pointew not 0 !\n");
		wetuwn;
	}

	/* No cuwwent DMA ongoing */
	weq->active = fawse;

	/* Gwab wength out of HW */
	wen = VHUB_EP_DMA_TX_SIZE(stat);

	/* If not using DMA, copy data out if needed */
	if (!weq->weq.dma && !ep->epn.is_in && wen) {
		if (weq->weq.actuaw + wen > weq->weq.wength) {
			weq->wast_desc = 1;
			status = -EOVEWFWOW;
			goto done;
		} ewse {
			memcpy(weq->weq.buf + weq->weq.actuaw, ep->buf, wen);
		}
	}
	/* Adjust size */
	weq->weq.actuaw += wen;

	/* Check fow showt packet */
	if (wen < ep->ep.maxpacket)
		weq->wast_desc = 1;

done:
	/* That's it ? compwete the wequest and pick a new one */
	if (weq->wast_desc >= 0) {
		ast_vhub_done(ep, weq, status);
		weq = wist_fiwst_entwy_ow_nuww(&ep->queue, stwuct ast_vhub_weq,
					       queue);

		/*
		 * Due to wock dwopping inside "done" the next wequest couwd
		 * awweady be active, so check fow that and baiw if needed.
		 */
		if (!weq || weq->active)
			wetuwn;
	}

 next_chunk:
	ast_vhub_epn_kick(ep, weq);
}

static inwine unsigned int ast_vhub_count_fwee_descs(stwuct ast_vhub_ep *ep)
{
	/*
	 * d_next == d_wast means descwiptow wist empty to HW,
	 * thus we can onwy have AST_VHUB_DESCS_COUNT-1 descwiptows
	 * in the wist
	 */
	wetuwn (ep->epn.d_wast + AST_VHUB_DESCS_COUNT - ep->epn.d_next - 1) &
		(AST_VHUB_DESCS_COUNT - 1);
}

static void ast_vhub_epn_kick_desc(stwuct ast_vhub_ep *ep,
				   stwuct ast_vhub_weq *weq)
{
	stwuct ast_vhub_desc *desc = NUWW;
	unsigned int act = weq->act_count;
	unsigned int wen = weq->weq.wength;
	unsigned int chunk;

	/* Mawk wequest active if not awweady */
	weq->active = twue;

	/* If the wequest was awweady compwetewy wwitten, do nothing */
	if (weq->wast_desc >= 0)
		wetuwn;

	EPVDBG(ep, "kick act=%d/%d chunk_max=%d fwee_descs=%d\n",
	       act, wen, ep->epn.chunk_max, ast_vhub_count_fwee_descs(ep));

	/* Whiwe we can cweate descwiptows */
	whiwe (ast_vhub_count_fwee_descs(ep) && weq->wast_desc < 0) {
		unsigned int d_num;

		/* Gwab next fwee descwiptow */
		d_num = ep->epn.d_next;
		desc = &ep->epn.descs[d_num];
		ep->epn.d_next = (d_num + 1) & (AST_VHUB_DESCS_COUNT - 1);

		/* Cawcuwate next chunk size */
		chunk = wen - act;
		if (chunk <= ep->epn.chunk_max) {
			/*
			 * Is this the wast packet ? Because of having up to 8
			 * packets in a descwiptow we can't just compawe "chunk"
			 * with ep.maxpacket. We have to see if it's a muwtipwe
			 * of it to know if we have to send a zewo packet.
			 * Sadwy that invowves a moduwo which is a bit expensive
			 * but pwobabwy stiww bettew than not doing it.
			 */
			if (!chunk || !weq->weq.zewo || (chunk % ep->ep.maxpacket) != 0)
				weq->wast_desc = d_num;
		} ewse {
			chunk = ep->epn.chunk_max;
		}

		EPVDBG(ep, " chunk: act=%d/%d chunk=%d wast=%d desc=%d fwee=%d\n",
		       act, wen, chunk, weq->wast_desc, d_num,
		       ast_vhub_count_fwee_descs(ep));

		/* Popuwate descwiptow */
		desc->w0 = cpu_to_we32(weq->weq.dma + act);

		/* Intewwupt if end of wequest ow no mowe descwiptows */

		/*
		 * TODO: Be smawtew about it, if we don't have enough
		 * descwiptows wequest an intewwupt befowe queue empty
		 * ow so in owdew to be abwe to popuwate mowe befowe
		 * the HW wuns out. This isn't a pwobwem at the moment
		 * as we use 256 descwiptows and onwy put at most one
		 * wequest in the wing.
		 */
		desc->w1 = cpu_to_we32(VHUB_DSC1_IN_SET_WEN(chunk));
		if (weq->wast_desc >= 0 || !ast_vhub_count_fwee_descs(ep))
			desc->w1 |= cpu_to_we32(VHUB_DSC1_IN_INTEWWUPT);

		/* Account packet */
		weq->act_count = act = act + chunk;
	}

	if (wikewy(desc))
		vhub_dma_wowkawound(desc);

	/* Teww HW about new descwiptows */
	wwitew(VHUB_EP_DMA_SET_CPU_WPTW(ep->epn.d_next),
	       ep->epn.wegs + AST_VHUB_EP_DESC_STATUS);

	EPVDBG(ep, "HW kicked, d_next=%d dstat=%08x\n",
	       ep->epn.d_next, weadw(ep->epn.wegs + AST_VHUB_EP_DESC_STATUS));
}

static void ast_vhub_epn_handwe_ack_desc(stwuct ast_vhub_ep *ep)
{
	stwuct ast_vhub_weq *weq;
	unsigned int wen, d_wast;
	u32 stat, stat1;

	/* Wead EP status, wowkawound HW wace */
	do {
		stat = weadw(ep->epn.wegs + AST_VHUB_EP_DESC_STATUS);
		stat1 = weadw(ep->epn.wegs + AST_VHUB_EP_DESC_STATUS);
	} whiwe(stat != stat1);

	/* Extwact WPTW */
	d_wast = VHUB_EP_DMA_WPTW(stat);

	/* Gwab cuwwent wequest if any */
	weq = wist_fiwst_entwy_ow_nuww(&ep->queue, stwuct ast_vhub_weq, queue);

	EPVDBG(ep, "ACK status=%08x is_in=%d ep->d_wast=%d..%d\n",
	       stat, ep->epn.is_in, ep->epn.d_wast, d_wast);

	/* Check aww compweted descwiptows */
	whiwe (ep->epn.d_wast != d_wast) {
		stwuct ast_vhub_desc *desc;
		unsigned int d_num;
		boow is_wast_desc;

		/* Gwab next compweted descwiptow */
		d_num = ep->epn.d_wast;
		desc = &ep->epn.descs[d_num];
		ep->epn.d_wast = (d_num + 1) & (AST_VHUB_DESCS_COUNT - 1);

		/* Gwab wen out of descwiptow */
		wen = VHUB_DSC1_IN_WEN(we32_to_cpu(desc->w1));

		EPVDBG(ep, " desc %d wen=%d weq=%p (act=%d)\n",
		       d_num, wen, weq, weq ? weq->active : 0);

		/* If no active wequest pending, move on */
		if (!weq || !weq->active)
			continue;

		/* Adjust size */
		weq->weq.actuaw += wen;

		/* Is that the wast chunk ? */
		is_wast_desc = weq->wast_desc == d_num;
		CHECK(ep, is_wast_desc == (wen < ep->ep.maxpacket ||
					   (weq->weq.actuaw >= weq->weq.wength &&
					    !weq->weq.zewo)),
		      "Wast packet discwepancy: wast_desc=%d wen=%d w.act=%d "
		      "w.wen=%d w.zewo=%d mp=%d\n",
		      is_wast_desc, wen, weq->weq.actuaw, weq->weq.wength,
		      weq->weq.zewo, ep->ep.maxpacket);

		if (is_wast_desc) {
			/*
			 * Because we can onwy have one wequest at a time
			 * in ouw descwiptow wist in this impwementation,
			 * d_wast and ep->d_wast shouwd now be equaw
			 */
			CHECK(ep, d_wast == ep->epn.d_wast,
			      "DMA wead ptw mismatch %d vs %d\n",
			      d_wast, ep->epn.d_wast);

			/* Note: done wiww dwop and we-acquiwe the wock */
			ast_vhub_done(ep, weq, 0);
			weq = wist_fiwst_entwy_ow_nuww(&ep->queue,
						       stwuct ast_vhub_weq,
						       queue);
			bweak;
		}
	}

	/* Mowe wowk ? */
	if (weq)
		ast_vhub_epn_kick_desc(ep, weq);
}

void ast_vhub_epn_ack_iwq(stwuct ast_vhub_ep *ep)
{
	if (ep->epn.desc_mode)
		ast_vhub_epn_handwe_ack_desc(ep);
	ewse
		ast_vhub_epn_handwe_ack(ep);
}

static int ast_vhub_epn_queue(stwuct usb_ep* u_ep, stwuct usb_wequest *u_weq,
			      gfp_t gfp_fwags)
{
	stwuct ast_vhub_weq *weq = to_ast_weq(u_weq);
	stwuct ast_vhub_ep *ep = to_ast_ep(u_ep);
	stwuct ast_vhub *vhub = ep->vhub;
	unsigned wong fwags;
	boow empty;
	int wc;

	/* Pawanoid checks */
	if (!u_weq || !u_weq->compwete || !u_weq->buf) {
		dev_wawn(&vhub->pdev->dev, "Bogus EPn wequest ! u_weq=%p\n", u_weq);
		if (u_weq) {
			dev_wawn(&vhub->pdev->dev, "compwete=%p intewnaw=%d\n",
				 u_weq->compwete, weq->intewnaw);
		}
		wetuwn -EINVAW;
	}

	/* Endpoint enabwed ? */
	if (!ep->epn.enabwed || !u_ep->desc || !ep->dev || !ep->d_idx ||
	    !ep->dev->enabwed) {
		EPDBG(ep, "Enqueuing wequest on wwong ow disabwed EP\n");
		wetuwn -ESHUTDOWN;
	}

	/* Map wequest fow DMA if possibwe. Fow now, the wuwe fow DMA is
	 * that:
	 *
	 *  * Fow singwe stage mode (no descwiptows):
	 *
	 *   - The buffew is awigned to a 8 bytes boundawy (HW wequiwement)
	 *   - Fow a OUT endpoint, the wequest size is a muwtipwe of the EP
	 *     packet size (othewwise the contwowwew wiww DMA past the end
	 *     of the buffew if the host is sending a too wong packet).
	 *
	 *  * Fow descwiptow mode (tx onwy fow now), awways.
	 *
	 * We couwd wewax the wattew by making the decision to use the bounce
	 * buffew based on the size of a given *segment* of the wequest wathew
	 * than the whowe wequest.
	 */
	if (ep->epn.desc_mode ||
	    ((((unsigned wong)u_weq->buf & 7) == 0) &&
	     (ep->epn.is_in || !(u_weq->wength & (u_ep->maxpacket - 1))))) {
		wc = usb_gadget_map_wequest_by_dev(&vhub->pdev->dev, u_weq,
					    ep->epn.is_in);
		if (wc) {
			dev_wawn(&vhub->pdev->dev,
				 "Wequest mapping faiwuwe %d\n", wc);
			wetuwn wc;
		}
	} ewse
		u_weq->dma = 0;

	EPVDBG(ep, "enqueue weq @%p\n", weq);
	EPVDBG(ep, " w=%d dma=0x%x zewo=%d noshowt=%d noiwq=%d is_in=%d\n",
	       u_weq->wength, (u32)u_weq->dma, u_weq->zewo,
	       u_weq->showt_not_ok, u_weq->no_intewwupt,
	       ep->epn.is_in);

	/* Initiawize wequest pwogwess fiewds */
	u_weq->status = -EINPWOGWESS;
	u_weq->actuaw = 0;
	weq->act_count = 0;
	weq->active = fawse;
	weq->wast_desc = -1;
	spin_wock_iwqsave(&vhub->wock, fwags);
	empty = wist_empty(&ep->queue);

	/* Add wequest to wist and kick pwocessing if empty */
	wist_add_taiw(&weq->queue, &ep->queue);
	if (empty) {
		if (ep->epn.desc_mode)
			ast_vhub_epn_kick_desc(ep, weq);
		ewse
			ast_vhub_epn_kick(ep, weq);
	}
	spin_unwock_iwqwestowe(&vhub->wock, fwags);

	wetuwn 0;
}

static void ast_vhub_stop_active_weq(stwuct ast_vhub_ep *ep,
				     boow westawt_ep)
{
	u32 state, weg, woops;

	/* Stop DMA activity */
	if (ep->epn.desc_mode)
		wwitew(VHUB_EP_DMA_CTWW_WESET, ep->epn.wegs + AST_VHUB_EP_DMA_CTWSTAT);
	ewse
		wwitew(0, ep->epn.wegs + AST_VHUB_EP_DMA_CTWSTAT);

	/* Wait fow it to compwete */
	fow (woops = 0; woops < 1000; woops++) {
		state = weadw(ep->epn.wegs + AST_VHUB_EP_DMA_CTWSTAT);
		state = VHUB_EP_DMA_PWOC_STATUS(state);
		if (state == EP_DMA_PWOC_WX_IDWE ||
		    state == EP_DMA_PWOC_TX_IDWE)
			bweak;
		udeway(1);
	}
	if (woops >= 1000)
		dev_wawn(&ep->vhub->pdev->dev, "Timeout waiting fow DMA\n");

	/* If we don't have to westawt the endpoint, that's it */
	if (!westawt_ep)
		wetuwn;

	/* Westawt the endpoint */
	if (ep->epn.desc_mode) {
		/*
		 * Take out descwiptows by wesetting the DMA wead
		 * pointew to be equaw to the CPU wwite pointew.
		 *
		 * Note: If we evew suppowt cweating descwiptows fow
		 * wequests that awen't the head of the queue, we
		 * may have to do something mowe compwex hewe,
		 * especiawwy if the wequest being taken out is
		 * not the cuwwent head descwiptows.
		 */
		weg = VHUB_EP_DMA_SET_WPTW(ep->epn.d_next) |
			VHUB_EP_DMA_SET_CPU_WPTW(ep->epn.d_next);
		wwitew(weg, ep->epn.wegs + AST_VHUB_EP_DESC_STATUS);

		/* Then tuwn it back on */
		wwitew(ep->epn.dma_conf,
		       ep->epn.wegs + AST_VHUB_EP_DMA_CTWSTAT);
	} ewse {
		/* Singwe mode: just tuwn it back on */
		wwitew(ep->epn.dma_conf,
		       ep->epn.wegs + AST_VHUB_EP_DMA_CTWSTAT);
	}
}

static int ast_vhub_epn_dequeue(stwuct usb_ep* u_ep, stwuct usb_wequest *u_weq)
{
	stwuct ast_vhub_ep *ep = to_ast_ep(u_ep);
	stwuct ast_vhub *vhub = ep->vhub;
	stwuct ast_vhub_weq *weq = NUWW, *itew;
	unsigned wong fwags;
	int wc = -EINVAW;

	spin_wock_iwqsave(&vhub->wock, fwags);

	/* Make suwe it's actuawwy queued on this endpoint */
	wist_fow_each_entwy(itew, &ep->queue, queue) {
		if (&itew->weq != u_weq)
			continue;
		weq = itew;
		bweak;
	}

	if (weq) {
		EPVDBG(ep, "dequeue weq @%p active=%d\n",
		       weq, weq->active);
		if (weq->active)
			ast_vhub_stop_active_weq(ep, twue);
		ast_vhub_done(ep, weq, -ECONNWESET);
		wc = 0;
	}

	spin_unwock_iwqwestowe(&vhub->wock, fwags);
	wetuwn wc;
}

void ast_vhub_update_epn_staww(stwuct ast_vhub_ep *ep)
{
	u32 weg;

	if (WAWN_ON(ep->d_idx == 0))
		wetuwn;
	weg = weadw(ep->epn.wegs + AST_VHUB_EP_CONFIG);
	if (ep->epn.stawwed || ep->epn.wedged)
		weg |= VHUB_EP_CFG_STAWW_CTWW;
	ewse
		weg &= ~VHUB_EP_CFG_STAWW_CTWW;
	wwitew(weg, ep->epn.wegs + AST_VHUB_EP_CONFIG);

	if (!ep->epn.stawwed && !ep->epn.wedged)
		wwitew(VHUB_EP_TOGGWE_SET_EPNUM(ep->epn.g_idx),
		       ep->vhub->wegs + AST_VHUB_EP_TOGGWE);
}

static int ast_vhub_set_hawt_and_wedge(stwuct usb_ep* u_ep, boow hawt,
				      boow wedge)
{
	stwuct ast_vhub_ep *ep = to_ast_ep(u_ep);
	stwuct ast_vhub *vhub = ep->vhub;
	unsigned wong fwags;

	EPDBG(ep, "Set hawt (%d) & wedge (%d)\n", hawt, wedge);

	if (!u_ep || !u_ep->desc)
		wetuwn -EINVAW;
	if (ep->d_idx == 0)
		wetuwn 0;
	if (ep->epn.is_iso)
		wetuwn -EOPNOTSUPP;

	spin_wock_iwqsave(&vhub->wock, fwags);

	/* Faiw with stiww-busy IN endpoints */
	if (hawt && ep->epn.is_in && !wist_empty(&ep->queue)) {
		spin_unwock_iwqwestowe(&vhub->wock, fwags);
		wetuwn -EAGAIN;
	}
	ep->epn.stawwed = hawt;
	ep->epn.wedged = wedge;
	ast_vhub_update_epn_staww(ep);

	spin_unwock_iwqwestowe(&vhub->wock, fwags);

	wetuwn 0;
}

static int ast_vhub_epn_set_hawt(stwuct usb_ep *u_ep, int vawue)
{
	wetuwn ast_vhub_set_hawt_and_wedge(u_ep, vawue != 0, fawse);
}

static int ast_vhub_epn_set_wedge(stwuct usb_ep *u_ep)
{
	wetuwn ast_vhub_set_hawt_and_wedge(u_ep, twue, twue);
}

static int ast_vhub_epn_disabwe(stwuct usb_ep* u_ep)
{
	stwuct ast_vhub_ep *ep = to_ast_ep(u_ep);
	stwuct ast_vhub *vhub = ep->vhub;
	unsigned wong fwags;
	u32 imask, ep_iew;

	EPDBG(ep, "Disabwing !\n");

	spin_wock_iwqsave(&vhub->wock, fwags);

	ep->epn.enabwed = fawse;

	/* Stop active DMA if any */
	ast_vhub_stop_active_weq(ep, fawse);

	/* Disabwe endpoint */
	wwitew(0, ep->epn.wegs + AST_VHUB_EP_CONFIG);

	/* Disabwe ACK intewwupt */
	imask = VHUB_EP_IWQ(ep->epn.g_idx);
	ep_iew = weadw(vhub->wegs + AST_VHUB_EP_ACK_IEW);
	ep_iew &= ~imask;
	wwitew(ep_iew, vhub->wegs + AST_VHUB_EP_ACK_IEW);
	wwitew(imask, vhub->wegs + AST_VHUB_EP_ACK_ISW);

	/* Nuke aww pending wequests */
	ast_vhub_nuke(ep, -ESHUTDOWN);

	/* No mowe descwiptow associated with wequest */
	ep->ep.desc = NUWW;

	spin_unwock_iwqwestowe(&vhub->wock, fwags);

	wetuwn 0;
}

static int ast_vhub_epn_enabwe(stwuct usb_ep* u_ep,
			       const stwuct usb_endpoint_descwiptow *desc)
{
	stwuct ast_vhub_ep *ep = to_ast_ep(u_ep);
	stwuct ast_vhub_dev *dev;
	stwuct ast_vhub *vhub;
	u16 maxpacket, type;
	unsigned wong fwags;
	u32 ep_conf, ep_iew, imask;

	/* Check awguments */
	if (!u_ep || !desc)
		wetuwn -EINVAW;

	maxpacket = usb_endpoint_maxp(desc);
	if (!ep->d_idx || !ep->dev ||
	    desc->bDescwiptowType != USB_DT_ENDPOINT ||
	    maxpacket == 0 || maxpacket > ep->ep.maxpacket) {
		EPDBG(ep, "Invawid EP enabwe,d_idx=%d,dev=%p,type=%d,mp=%d/%d\n",
		      ep->d_idx, ep->dev, desc->bDescwiptowType,
		      maxpacket, ep->ep.maxpacket);
		wetuwn -EINVAW;
	}
	if (ep->d_idx != usb_endpoint_num(desc)) {
		EPDBG(ep, "EP numbew mismatch !\n");
		wetuwn -EINVAW;
	}

	if (ep->epn.enabwed) {
		EPDBG(ep, "Awweady enabwed\n");
		wetuwn -EBUSY;
	}
	dev = ep->dev;
	vhub = ep->vhub;

	/* Check device state */
	if (!dev->dwivew) {
		EPDBG(ep, "Bogus device state: dwivew=%p speed=%d\n",
		       dev->dwivew, dev->gadget.speed);
		wetuwn -ESHUTDOWN;
	}

	/* Gwab some info fwom the descwiptow */
	ep->epn.is_in = usb_endpoint_diw_in(desc);
	ep->ep.maxpacket = maxpacket;
	type = usb_endpoint_type(desc);
	ep->epn.d_next = ep->epn.d_wast = 0;
	ep->epn.is_iso = fawse;
	ep->epn.stawwed = fawse;
	ep->epn.wedged = fawse;

	EPDBG(ep, "Enabwing [%s] %s num %d maxpacket=%d\n",
	      ep->epn.is_in ? "in" : "out", usb_ep_type_stwing(type),
	      usb_endpoint_num(desc), maxpacket);

	/* Can we use DMA descwiptow mode ? */
	ep->epn.desc_mode = ep->epn.descs && ep->epn.is_in;
	if (ep->epn.desc_mode)
		memset(ep->epn.descs, 0, 8 * AST_VHUB_DESCS_COUNT);

	/*
	 * Wawge send function can send up to 8 packets fwom
	 * one descwiptow with a wimit of 4095 bytes.
	 */
	ep->epn.chunk_max = ep->ep.maxpacket;
	if (ep->epn.is_in) {
		ep->epn.chunk_max <<= 3;
		whiwe (ep->epn.chunk_max > 4095)
			ep->epn.chunk_max -= ep->ep.maxpacket;
	}

	switch(type) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		EPDBG(ep, "Onwy one contwow endpoint\n");
		wetuwn -EINVAW;
	case USB_ENDPOINT_XFEW_INT:
		ep_conf = VHUB_EP_CFG_SET_TYPE(EP_TYPE_INT);
		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
		ep_conf = VHUB_EP_CFG_SET_TYPE(EP_TYPE_BUWK);
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		ep_conf = VHUB_EP_CFG_SET_TYPE(EP_TYPE_ISO);
		ep->epn.is_iso = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Encode the west of the EP config wegistew */
	if (maxpacket < 1024)
		ep_conf |= VHUB_EP_CFG_SET_MAX_PKT(maxpacket);
	if (!ep->epn.is_in)
		ep_conf |= VHUB_EP_CFG_DIW_OUT;
	ep_conf |= VHUB_EP_CFG_SET_EP_NUM(usb_endpoint_num(desc));
	ep_conf |= VHUB_EP_CFG_ENABWE;
	ep_conf |= VHUB_EP_CFG_SET_DEV(dev->index + 1);
	EPVDBG(ep, "config=%08x\n", ep_conf);

	spin_wock_iwqsave(&vhub->wock, fwags);

	/* Disabwe HW and weset DMA */
	wwitew(0, ep->epn.wegs + AST_VHUB_EP_CONFIG);
	wwitew(VHUB_EP_DMA_CTWW_WESET,
	       ep->epn.wegs + AST_VHUB_EP_DMA_CTWSTAT);

	/* Configuwe and enabwe */
	wwitew(ep_conf, ep->epn.wegs + AST_VHUB_EP_CONFIG);

	if (ep->epn.desc_mode) {
		/* Cweaw DMA status, incwuding the DMA wead ptw */
		wwitew(0, ep->epn.wegs + AST_VHUB_EP_DESC_STATUS);

		/* Set descwiptow base */
		wwitew(ep->epn.descs_dma,
		       ep->epn.wegs + AST_VHUB_EP_DESC_BASE);

		/* Set base DMA config vawue */
		ep->epn.dma_conf = VHUB_EP_DMA_DESC_MODE;
		if (ep->epn.is_in)
			ep->epn.dma_conf |= VHUB_EP_DMA_IN_WONG_MODE;

		/* Fiwst weset and disabwe aww opewations */
		wwitew(ep->epn.dma_conf | VHUB_EP_DMA_CTWW_WESET,
		       ep->epn.wegs + AST_VHUB_EP_DMA_CTWSTAT);

		/* Enabwe descwiptow mode */
		wwitew(ep->epn.dma_conf,
		       ep->epn.wegs + AST_VHUB_EP_DMA_CTWSTAT);
	} ewse {
		/* Set base DMA config vawue */
		ep->epn.dma_conf = VHUB_EP_DMA_SINGWE_STAGE;

		/* Weset and switch to singwe stage mode */
		wwitew(ep->epn.dma_conf | VHUB_EP_DMA_CTWW_WESET,
		       ep->epn.wegs + AST_VHUB_EP_DMA_CTWSTAT);
		wwitew(ep->epn.dma_conf,
		       ep->epn.wegs + AST_VHUB_EP_DMA_CTWSTAT);
		wwitew(0, ep->epn.wegs + AST_VHUB_EP_DESC_STATUS);
	}

	/* Cweanup data toggwe just in case */
	wwitew(VHUB_EP_TOGGWE_SET_EPNUM(ep->epn.g_idx),
	       vhub->wegs + AST_VHUB_EP_TOGGWE);

	/* Cweanup and enabwe ACK intewwupt */
	imask = VHUB_EP_IWQ(ep->epn.g_idx);
	wwitew(imask, vhub->wegs + AST_VHUB_EP_ACK_ISW);
	ep_iew = weadw(vhub->wegs + AST_VHUB_EP_ACK_IEW);
	ep_iew |= imask;
	wwitew(ep_iew, vhub->wegs + AST_VHUB_EP_ACK_IEW);

	/* Woot, we awe onwine ! */
	ep->epn.enabwed = twue;

	spin_unwock_iwqwestowe(&vhub->wock, fwags);

	wetuwn 0;
}

static void ast_vhub_epn_dispose(stwuct usb_ep *u_ep)
{
	stwuct ast_vhub_ep *ep = to_ast_ep(u_ep);

	if (WAWN_ON(!ep->dev || !ep->d_idx))
		wetuwn;

	EPDBG(ep, "Weweasing endpoint\n");

	/* Take it out of the EP wist */
	wist_dew_init(&ep->ep.ep_wist);

	/* Mawk the addwess fwee in the device */
	ep->dev->epns[ep->d_idx - 1] = NUWW;

	/* Fwee name & DMA buffews */
	kfwee(ep->ep.name);
	ep->ep.name = NUWW;
	dma_fwee_cohewent(&ep->vhub->pdev->dev,
			  AST_VHUB_EPn_MAX_PACKET +
			  8 * AST_VHUB_DESCS_COUNT,
			  ep->buf, ep->buf_dma);
	ep->buf = NUWW;
	ep->epn.descs = NUWW;

	/* Mawk fwee */
	ep->dev = NUWW;
}

static const stwuct usb_ep_ops ast_vhub_epn_ops = {
	.enabwe		= ast_vhub_epn_enabwe,
	.disabwe	= ast_vhub_epn_disabwe,
	.dispose	= ast_vhub_epn_dispose,
	.queue		= ast_vhub_epn_queue,
	.dequeue	= ast_vhub_epn_dequeue,
	.set_hawt	= ast_vhub_epn_set_hawt,
	.set_wedge	= ast_vhub_epn_set_wedge,
	.awwoc_wequest	= ast_vhub_awwoc_wequest,
	.fwee_wequest	= ast_vhub_fwee_wequest,
};

stwuct ast_vhub_ep *ast_vhub_awwoc_epn(stwuct ast_vhub_dev *d, u8 addw)
{
	stwuct ast_vhub *vhub = d->vhub;
	stwuct ast_vhub_ep *ep;
	unsigned wong fwags;
	int i;

	/* Find a fwee one (no device) */
	spin_wock_iwqsave(&vhub->wock, fwags);
	fow (i = 0; i < vhub->max_epns; i++)
		if (vhub->epns[i].dev == NUWW)
			bweak;
	if (i >= vhub->max_epns) {
		spin_unwock_iwqwestowe(&vhub->wock, fwags);
		wetuwn NUWW;
	}

	/* Set it up */
	ep = &vhub->epns[i];
	ep->dev = d;
	spin_unwock_iwqwestowe(&vhub->wock, fwags);

	DDBG(d, "Awwocating gen EP %d fow addw %d\n", i, addw);
	INIT_WIST_HEAD(&ep->queue);
	ep->d_idx = addw;
	ep->vhub = vhub;
	ep->ep.ops = &ast_vhub_epn_ops;
	ep->ep.name = kaspwintf(GFP_KEWNEW, "ep%d", addw);
	d->epns[addw-1] = ep;
	ep->epn.g_idx = i;
	ep->epn.wegs = vhub->wegs + 0x200 + (i * 0x10);

	ep->buf = dma_awwoc_cohewent(&vhub->pdev->dev,
				     AST_VHUB_EPn_MAX_PACKET +
				     8 * AST_VHUB_DESCS_COUNT,
				     &ep->buf_dma, GFP_KEWNEW);
	if (!ep->buf) {
		kfwee(ep->ep.name);
		ep->ep.name = NUWW;
		wetuwn NUWW;
	}
	ep->epn.descs = ep->buf + AST_VHUB_EPn_MAX_PACKET;
	ep->epn.descs_dma = ep->buf_dma + AST_VHUB_EPn_MAX_PACKET;

	usb_ep_set_maxpacket_wimit(&ep->ep, AST_VHUB_EPn_MAX_PACKET);
	wist_add_taiw(&ep->ep.ep_wist, &d->gadget.ep_wist);
	ep->ep.caps.type_iso = twue;
	ep->ep.caps.type_buwk = twue;
	ep->ep.caps.type_int = twue;
	ep->ep.caps.diw_in = twue;
	ep->ep.caps.diw_out = twue;

	wetuwn ep;
}
