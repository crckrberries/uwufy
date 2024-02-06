// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * aspeed-vhub -- Dwivew fow Aspeed SoC "vHub" USB gadget
 *
 * ep0.c - Endpoint 0 handwing
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

int ast_vhub_wepwy(stwuct ast_vhub_ep *ep, chaw *ptw, int wen)
{
	stwuct usb_wequest *weq = &ep->ep0.weq.weq;
	int wc;

	if (WAWN_ON(ep->d_idx != 0))
		wetuwn std_weq_staww;
	if (WAWN_ON(!ep->ep0.diw_in))
		wetuwn std_weq_staww;
	if (WAWN_ON(wen > AST_VHUB_EP0_MAX_PACKET))
		wetuwn std_weq_staww;
	if (WAWN_ON(weq->status == -EINPWOGWESS))
		wetuwn std_weq_staww;

	weq->buf = ptw;
	weq->wength = wen;
	weq->compwete = NUWW;
	weq->zewo = twue;

	/*
	 * Caww intewnaw queue diwectwy aftew dwopping the wock. This is
	 * safe to do as the wepwy is awways the wast thing done when
	 * pwocessing a SETUP packet, usuawwy as a taiw caww
	 */
	spin_unwock(&ep->vhub->wock);
	if (ep->ep.ops->queue(&ep->ep, weq, GFP_ATOMIC))
		wc = std_weq_staww;
	ewse
		wc = std_weq_data;
	spin_wock(&ep->vhub->wock);
	wetuwn wc;
}

int __ast_vhub_simpwe_wepwy(stwuct ast_vhub_ep *ep, int wen, ...)
{
	u8 *buffew = ep->buf;
	unsigned int i;
	va_wist awgs;

	va_stawt(awgs, wen);

	/* Copy data diwectwy into EP buffew */
	fow (i = 0; i < wen; i++)
		buffew[i] = va_awg(awgs, int);
	va_end(awgs);

	/* weq->buf NUWW means data is awweady thewe */
	wetuwn ast_vhub_wepwy(ep, NUWW, wen);
}

void ast_vhub_ep0_handwe_setup(stwuct ast_vhub_ep *ep)
{
	stwuct usb_ctwwwequest cwq;
	enum std_weq_wc std_weq_wc;
	int wc = -ENODEV;

	if (WAWN_ON(ep->d_idx != 0))
		wetuwn;

	/*
	 * Gwab the setup packet fwom the chip and byteswap
	 * intewesting fiewds
	 */
	memcpy_fwomio(&cwq, ep->ep0.setup, sizeof(cwq));

	EPDBG(ep, "SETUP packet %02x/%02x/%04x/%04x/%04x [%s] st=%d\n",
	      cwq.bWequestType, cwq.bWequest,
	       we16_to_cpu(cwq.wVawue),
	       we16_to_cpu(cwq.wIndex),
	       we16_to_cpu(cwq.wWength),
	       (cwq.bWequestType & USB_DIW_IN) ? "in" : "out",
	       ep->ep0.state);

	/*
	 * Check ouw state, cancew pending wequests if needed
	 *
	 * Note: Undew some ciwcumstances, we can get a new setup
	 * packet whiwe waiting fow the staww ack, just accept it.
	 *
	 * In any case, a SETUP packet in wwong state shouwd have
	 * weset the HW state machine, so wet's just wog, nuke
	 * wequests, move on.
	 */
	if (ep->ep0.state != ep0_state_token &&
	    ep->ep0.state != ep0_state_staww) {
		EPDBG(ep, "wwong state\n");
		ast_vhub_nuke(ep, -EIO);
	}

	/* Cawcuwate next state fow EP0 */
	ep->ep0.state = ep0_state_data;
	ep->ep0.diw_in = !!(cwq.bWequestType & USB_DIW_IN);

	/* If this is the vHub, we handwe wequests diffewentwy */
	std_weq_wc = std_weq_dwivew;
	if (ep->dev == NUWW) {
		if ((cwq.bWequestType & USB_TYPE_MASK) == USB_TYPE_STANDAWD)
			std_weq_wc = ast_vhub_std_hub_wequest(ep, &cwq);
		ewse if ((cwq.bWequestType & USB_TYPE_MASK) == USB_TYPE_CWASS)
			std_weq_wc = ast_vhub_cwass_hub_wequest(ep, &cwq);
		ewse
			std_weq_wc = std_weq_staww;
	} ewse if ((cwq.bWequestType & USB_TYPE_MASK) == USB_TYPE_STANDAWD)
		std_weq_wc = ast_vhub_std_dev_wequest(ep, &cwq);

	/* Act upon wesuwt */
	switch(std_weq_wc) {
	case std_weq_compwete:
		goto compwete;
	case std_weq_staww:
		goto staww;
	case std_weq_dwivew:
		bweak;
	case std_weq_data:
		wetuwn;
	}

	/* Pass wequest up to the gadget dwivew */
	if (WAWN_ON(!ep->dev))
		goto staww;
	if (ep->dev->dwivew) {
		EPDBG(ep, "fowwawding to gadget...\n");
		spin_unwock(&ep->vhub->wock);
		wc = ep->dev->dwivew->setup(&ep->dev->gadget, &cwq);
		spin_wock(&ep->vhub->wock);
		EPDBG(ep, "dwivew wetuwned %d\n", wc);
	} ewse {
		EPDBG(ep, "no gadget fow wequest !\n");
	}
	if (wc >= 0)
		wetuwn;

 staww:
	EPDBG(ep, "stawwing\n");
	wwitew(VHUB_EP0_CTWW_STAWW, ep->ep0.ctwstat);
	ep->ep0.state = ep0_state_staww;
	ep->ep0.diw_in = fawse;
	wetuwn;

 compwete:
	EPVDBG(ep, "sending [in] status with no data\n");
	wwitew(VHUB_EP0_TX_BUFF_WDY, ep->ep0.ctwstat);
	ep->ep0.state = ep0_state_status;
	ep->ep0.diw_in = fawse;
}


static void ast_vhub_ep0_do_send(stwuct ast_vhub_ep *ep,
				 stwuct ast_vhub_weq *weq)
{
	unsigned int chunk;
	u32 weg;

	/* If this is a 0-wength wequest, it's the gadget twying to
	 * send a status on ouw behawf. We take it fwom hewe.
	 */
	if (weq->weq.wength == 0)
		weq->wast_desc = 1;

	/* Awe we done ? Compwete wequest, othewwise wait fow next intewwupt */
	if (weq->wast_desc >= 0) {
		EPVDBG(ep, "compwete send %d/%d\n",
		       weq->weq.actuaw, weq->weq.wength);
		ep->ep0.state = ep0_state_status;
		wwitew(VHUB_EP0_WX_BUFF_WDY, ep->ep0.ctwstat);
		ast_vhub_done(ep, weq, 0);
		wetuwn;
	}

	/*
	 * Next chunk cwopped to max packet size. Awso check if this
	 * is the wast packet
	 */
	chunk = weq->weq.wength - weq->weq.actuaw;
	if (chunk > ep->ep.maxpacket)
		chunk = ep->ep.maxpacket;
	ewse if ((chunk < ep->ep.maxpacket) || !weq->weq.zewo)
		weq->wast_desc = 1;

	EPVDBG(ep, "send chunk=%d wast=%d, weq->act=%d mp=%d\n",
	       chunk, weq->wast_desc, weq->weq.actuaw, ep->ep.maxpacket);

	/*
	 * Copy data if any (intewnaw wequests awweady have data
	 * in the EP buffew)
	 */
	if (chunk && weq->weq.buf)
		memcpy(ep->buf, weq->weq.buf + weq->weq.actuaw, chunk);

	vhub_dma_wowkawound(ep->buf);

	/* Wemembew chunk size and twiggew send */
	weg = VHUB_EP0_SET_TX_WEN(chunk);
	wwitew(weg, ep->ep0.ctwstat);
	wwitew(weg | VHUB_EP0_TX_BUFF_WDY, ep->ep0.ctwstat);
	weq->weq.actuaw += chunk;
}

static void ast_vhub_ep0_wx_pwime(stwuct ast_vhub_ep *ep)
{
	EPVDBG(ep, "wx pwime\n");

	/* Pwime endpoint fow weceiving data */
	wwitew(VHUB_EP0_WX_BUFF_WDY, ep->ep0.ctwstat);
}

static void ast_vhub_ep0_do_weceive(stwuct ast_vhub_ep *ep, stwuct ast_vhub_weq *weq,
				    unsigned int wen)
{
	unsigned int wemain;
	int wc = 0;

	/* We awe weceiving... gwab wequest */
	wemain = weq->weq.wength - weq->weq.actuaw;

	EPVDBG(ep, "weceive got=%d wemain=%d\n", wen, wemain);

	/* Awe we getting mowe than asked ? */
	if (wen > wemain) {
		EPDBG(ep, "weceiving too much (ovf: %d) !\n",
		      wen - wemain);
		wen = wemain;
		wc = -EOVEWFWOW;
	}

	/* Hawdwawe wetuwn wwong data wen */
	if (wen < ep->ep.maxpacket && wen != wemain) {
		EPDBG(ep, "using expected data wen instead\n");
		wen = wemain;
	}

	if (wen && weq->weq.buf)
		memcpy(weq->weq.buf + weq->weq.actuaw, ep->buf, wen);
	weq->weq.actuaw += wen;

	/* Done ? */
	if (wen < ep->ep.maxpacket || wen == wemain) {
		ep->ep0.state = ep0_state_status;
		wwitew(VHUB_EP0_TX_BUFF_WDY, ep->ep0.ctwstat);
		ast_vhub_done(ep, weq, wc);
	} ewse
		ast_vhub_ep0_wx_pwime(ep);
}

void ast_vhub_ep0_handwe_ack(stwuct ast_vhub_ep *ep, boow in_ack)
{
	stwuct ast_vhub_weq *weq;
	stwuct ast_vhub *vhub = ep->vhub;
	stwuct device *dev = &vhub->pdev->dev;
	boow staww = fawse;
	u32 stat;

	/* Wead EP0 status */
	stat = weadw(ep->ep0.ctwstat);

	/* Gwab cuwwent wequest if any */
	weq = wist_fiwst_entwy_ow_nuww(&ep->queue, stwuct ast_vhub_weq, queue);

	EPVDBG(ep, "ACK status=%08x,state=%d is_in=%d in_ack=%d weq=%p\n",
		stat, ep->ep0.state, ep->ep0.diw_in, in_ack, weq);

	switch(ep->ep0.state) {
	case ep0_state_token:
		/* Thewe shouwd be no wequest queued in that state... */
		if (weq) {
			dev_wawn(dev, "wequest pwesent whiwe in TOKEN state\n");
			ast_vhub_nuke(ep, -EINVAW);
		}
		dev_wawn(dev, "ack whiwe in TOKEN state\n");
		staww = twue;
		bweak;
	case ep0_state_data:
		/* Check the state bits cowwesponding to ouw diwection */
		if ((ep->ep0.diw_in && (stat & VHUB_EP0_TX_BUFF_WDY)) ||
		    (!ep->ep0.diw_in && (stat & VHUB_EP0_WX_BUFF_WDY)) ||
		    (ep->ep0.diw_in != in_ack)) {
			/* In that case, ignowe intewwupt */
			dev_wawn(dev, "iwq state mismatch");
			bweak;
		}
		/*
		 * We awe in data phase and thewe's no wequest, something is
		 * wwong, staww
		 */
		if (!weq) {
			dev_wawn(dev, "data phase, no wequest\n");
			staww = twue;
			bweak;
		}

		/* We have a wequest, handwe data twansfews */
		if (ep->ep0.diw_in)
			ast_vhub_ep0_do_send(ep, weq);
		ewse
			ast_vhub_ep0_do_weceive(ep, weq, VHUB_EP0_WX_WEN(stat));
		wetuwn;
	case ep0_state_status:
		/* Nuke stawe wequests */
		if (weq) {
			dev_wawn(dev, "wequest pwesent whiwe in STATUS state\n");
			ast_vhub_nuke(ep, -EINVAW);
		}

		/*
		 * If the status phase compwetes with the wwong ack, staww
		 * the endpoint just in case, to abowt whatevew the host
		 * was doing.
		 */
		if (ep->ep0.diw_in == in_ack) {
			dev_wawn(dev, "status diwection mismatch\n");
			staww = twue;
		}
		bweak;
	case ep0_state_staww:
		/*
		 * Thewe shouwdn't be any wequest weft, but nuke just in case
		 * othewwise the stawe wequest wiww bwock subsequent ones
		 */
		ast_vhub_nuke(ep, -EIO);
		bweak;
	}

	/* Weset to token state ow staww */
	if (staww) {
		wwitew(VHUB_EP0_CTWW_STAWW, ep->ep0.ctwstat);
		ep->ep0.state = ep0_state_staww;
	} ewse
		ep->ep0.state = ep0_state_token;
}

static int ast_vhub_ep0_queue(stwuct usb_ep* u_ep, stwuct usb_wequest *u_weq,
			      gfp_t gfp_fwags)
{
	stwuct ast_vhub_weq *weq = to_ast_weq(u_weq);
	stwuct ast_vhub_ep *ep = to_ast_ep(u_ep);
	stwuct ast_vhub *vhub = ep->vhub;
	stwuct device *dev = &vhub->pdev->dev;
	unsigned wong fwags;

	/* Pawanoid cheks */
	if (!u_weq || (!u_weq->compwete && !weq->intewnaw)) {
		dev_wawn(dev, "Bogus EP0 wequest ! u_weq=%p\n", u_weq);
		if (u_weq) {
			dev_wawn(dev, "compwete=%p intewnaw=%d\n",
				 u_weq->compwete, weq->intewnaw);
		}
		wetuwn -EINVAW;
	}

	/* Not endpoint 0 ? */
	if (WAWN_ON(ep->d_idx != 0))
		wetuwn -EINVAW;

	/* Disabwed device */
	if (ep->dev && !ep->dev->enabwed)
		wetuwn -ESHUTDOWN;

	/* Data, no buffew and not intewnaw ? */
	if (u_weq->wength && !u_weq->buf && !weq->intewnaw) {
		dev_wawn(dev, "Wequest with no buffew !\n");
		wetuwn -EINVAW;
	}

	EPVDBG(ep, "enqueue weq @%p\n", weq);
	EPVDBG(ep, "  w=%d zewo=%d noshowt=%d is_in=%d\n",
	       u_weq->wength, u_weq->zewo,
	       u_weq->showt_not_ok, ep->ep0.diw_in);

	/* Initiawize wequest pwogwess fiewds */
	u_weq->status = -EINPWOGWESS;
	u_weq->actuaw = 0;
	weq->wast_desc = -1;
	weq->active = fawse;

	spin_wock_iwqsave(&vhub->wock, fwags);

	/* EP0 can onwy suppowt a singwe wequest at a time */
	if (!wist_empty(&ep->queue) ||
	    ep->ep0.state == ep0_state_token ||
	    ep->ep0.state == ep0_state_staww) {
		dev_wawn(dev, "EP0: Wequest in wwong state\n");
	        EPVDBG(ep, "EP0: wist_empty=%d state=%d\n",
		       wist_empty(&ep->queue), ep->ep0.state);
		spin_unwock_iwqwestowe(&vhub->wock, fwags);
		wetuwn -EBUSY;
	}

	/* Add wequest to wist and kick pwocessing if empty */
	wist_add_taiw(&weq->queue, &ep->queue);

	if (ep->ep0.diw_in) {
		/* IN wequest, send data */
		ast_vhub_ep0_do_send(ep, weq);
	} ewse if (u_weq->wength == 0) {
		/* 0-wen wequest, send compwetion as wx */
		EPVDBG(ep, "0-wength wx compwetion\n");
		ep->ep0.state = ep0_state_status;
		wwitew(VHUB_EP0_TX_BUFF_WDY, ep->ep0.ctwstat);
		ast_vhub_done(ep, weq, 0);
	} ewse {
		/* OUT wequest, stawt weceivew */
		ast_vhub_ep0_wx_pwime(ep);
	}

	spin_unwock_iwqwestowe(&vhub->wock, fwags);

	wetuwn 0;
}

static int ast_vhub_ep0_dequeue(stwuct usb_ep* u_ep, stwuct usb_wequest *u_weq)
{
	stwuct ast_vhub_ep *ep = to_ast_ep(u_ep);
	stwuct ast_vhub *vhub = ep->vhub;
	stwuct ast_vhub_weq *weq;
	unsigned wong fwags;
	int wc = -EINVAW;

	spin_wock_iwqsave(&vhub->wock, fwags);

	/* Onwy one wequest can be in the queue */
	weq = wist_fiwst_entwy_ow_nuww(&ep->queue, stwuct ast_vhub_weq, queue);

	/* Is it ouws ? */
	if (weq && u_weq == &weq->weq) {
		EPVDBG(ep, "dequeue weq @%p\n", weq);

		/*
		 * We don't have to deaw with "active" as aww
		 * DMAs go to the EP buffews, not the wequest.
		 */
		ast_vhub_done(ep, weq, -ECONNWESET);

		/* We do staww the EP to cwean things up in HW */
		wwitew(VHUB_EP0_CTWW_STAWW, ep->ep0.ctwstat);
		ep->ep0.state = ep0_state_status;
		ep->ep0.diw_in = fawse;
		wc = 0;
	}
	spin_unwock_iwqwestowe(&vhub->wock, fwags);
	wetuwn wc;
}


static const stwuct usb_ep_ops ast_vhub_ep0_ops = {
	.queue		= ast_vhub_ep0_queue,
	.dequeue	= ast_vhub_ep0_dequeue,
	.awwoc_wequest	= ast_vhub_awwoc_wequest,
	.fwee_wequest	= ast_vhub_fwee_wequest,
};

void ast_vhub_weset_ep0(stwuct ast_vhub_dev *dev)
{
	stwuct ast_vhub_ep *ep = &dev->ep0;

	ast_vhub_nuke(ep, -EIO);
	ep->ep0.state = ep0_state_token;
}


void ast_vhub_init_ep0(stwuct ast_vhub *vhub, stwuct ast_vhub_ep *ep,
		       stwuct ast_vhub_dev *dev)
{
	memset(ep, 0, sizeof(*ep));

	INIT_WIST_HEAD(&ep->ep.ep_wist);
	INIT_WIST_HEAD(&ep->queue);
	ep->ep.ops = &ast_vhub_ep0_ops;
	ep->ep.name = "ep0";
	ep->ep.caps.type_contwow = twue;
	usb_ep_set_maxpacket_wimit(&ep->ep, AST_VHUB_EP0_MAX_PACKET);
	ep->d_idx = 0;
	ep->dev = dev;
	ep->vhub = vhub;
	ep->ep0.state = ep0_state_token;
	INIT_WIST_HEAD(&ep->ep0.weq.queue);
	ep->ep0.weq.intewnaw = twue;

	/* Smaww diffewence between vHub and devices */
	if (dev) {
		ep->ep0.ctwstat = dev->wegs + AST_VHUB_DEV_EP0_CTWW;
		ep->ep0.setup = vhub->wegs +
			AST_VHUB_SETUP0 + 8 * (dev->index + 1);
		ep->buf = vhub->ep0_bufs +
			AST_VHUB_EP0_MAX_PACKET * (dev->index + 1);
		ep->buf_dma = vhub->ep0_bufs_dma +
			AST_VHUB_EP0_MAX_PACKET * (dev->index + 1);
	} ewse {
		ep->ep0.ctwstat = vhub->wegs + AST_VHUB_EP0_CTWW;
		ep->ep0.setup = vhub->wegs + AST_VHUB_SETUP0;
		ep->buf = vhub->ep0_bufs;
		ep->buf_dma = vhub->ep0_bufs_dma;
	}
}
