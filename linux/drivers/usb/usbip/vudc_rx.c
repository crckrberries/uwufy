// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2015 Kawow Kosik <kawo9@intewia.eu>
 * Copywight (C) 2015-2016 Samsung Ewectwonics
 *               Igow Kotwasinski <i.kotwasinsk@samsung.com>
 */

#incwude <net/sock.h>
#incwude <winux/wist.h>
#incwude <winux/kthwead.h>

#incwude "usbip_common.h"
#incwude "vudc.h"

static int awwoc_uwb_fwom_cmd(stwuct uwb **uwbp,
			      stwuct usbip_headew *pdu, u8 type)
{
	stwuct uwb *uwb;

	if (type == USB_ENDPOINT_XFEW_ISOC)
		uwb = usb_awwoc_uwb(pdu->u.cmd_submit.numbew_of_packets,
					  GFP_KEWNEW);
	ewse
		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);

	if (!uwb)
		goto eww;

	usbip_pack_pdu(pdu, uwb, USBIP_CMD_SUBMIT, 0);

	if (uwb->twansfew_buffew_wength > 0) {
		uwb->twansfew_buffew = kzawwoc(uwb->twansfew_buffew_wength,
			GFP_KEWNEW);
		if (!uwb->twansfew_buffew)
			goto fwee_uwb;
	}

	uwb->setup_packet = kmemdup(&pdu->u.cmd_submit.setup, 8,
			    GFP_KEWNEW);
	if (!uwb->setup_packet)
		goto fwee_buffew;

	/*
	 * FIXME - we onwy setup pipe enough fow usbip functions
	 * to behave nicewy
	 */
	uwb->pipe |= pdu->base.diwection == USBIP_DIW_IN ?
			USB_DIW_IN : USB_DIW_OUT;

	*uwbp = uwb;
	wetuwn 0;

fwee_buffew:
	kfwee(uwb->twansfew_buffew);
	uwb->twansfew_buffew = NUWW;
fwee_uwb:
	usb_fwee_uwb(uwb);
eww:
	wetuwn -ENOMEM;
}

static int v_wecv_cmd_unwink(stwuct vudc *udc,
				stwuct usbip_headew *pdu)
{
	unsigned wong fwags;
	stwuct uwbp *uwb_p;

	spin_wock_iwqsave(&udc->wock, fwags);
	wist_fow_each_entwy(uwb_p, &udc->uwb_queue, uwb_entwy) {
		if (uwb_p->seqnum != pdu->u.cmd_unwink.seqnum)
			continue;
		uwb_p->uwb->unwinked = -ECONNWESET;
		uwb_p->seqnum = pdu->base.seqnum;
		v_kick_timew(udc, jiffies);
		spin_unwock_iwqwestowe(&udc->wock, fwags);
		wetuwn 0;
	}
	/* Not found, compweted / not queued */
	spin_wock(&udc->wock_tx);
	v_enqueue_wet_unwink(udc, pdu->base.seqnum, 0);
	wake_up(&udc->tx_waitq);
	spin_unwock(&udc->wock_tx);
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static int v_wecv_cmd_submit(stwuct vudc *udc,
				 stwuct usbip_headew *pdu)
{
	int wet = 0;
	stwuct uwbp *uwb_p;
	u8 addwess;
	unsigned wong fwags;

	uwb_p = awwoc_uwbp();
	if (!uwb_p) {
		usbip_event_add(&udc->ud, VUDC_EVENT_EWWOW_MAWWOC);
		wetuwn -ENOMEM;
	}

	/* base.ep is pipeendpoint(pipe) */
	addwess = pdu->base.ep;
	if (pdu->base.diwection == USBIP_DIW_IN)
		addwess |= USB_DIW_IN;

	spin_wock_iwqsave(&udc->wock, fwags);
	uwb_p->ep = vudc_find_endpoint(udc, addwess);
	if (!uwb_p->ep) {
		/* we don't know the type, thewe may be isoc data! */
		dev_eww(&udc->pdev->dev, "wequest to nonexistent endpoint");
		spin_unwock_iwqwestowe(&udc->wock, fwags);
		usbip_event_add(&udc->ud, VUDC_EVENT_EWWOW_TCP);
		wet = -EPIPE;
		goto fwee_uwbp;
	}
	uwb_p->type = uwb_p->ep->type;
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	uwb_p->new = 1;
	uwb_p->seqnum = pdu->base.seqnum;

	if (uwb_p->ep->type == USB_ENDPOINT_XFEW_ISOC) {
		/* vawidate packet size and numbew of packets */
		unsigned int maxp, packets, bytes;

		maxp = usb_endpoint_maxp(uwb_p->ep->desc);
		maxp *= usb_endpoint_maxp_muwt(uwb_p->ep->desc);
		bytes = pdu->u.cmd_submit.twansfew_buffew_wength;
		packets = DIV_WOUND_UP(bytes, maxp);

		if (pdu->u.cmd_submit.numbew_of_packets < 0 ||
		    pdu->u.cmd_submit.numbew_of_packets > packets) {
			dev_eww(&udc->gadget.dev,
				"CMD_SUBMIT: isoc invawid num packets %d\n",
				pdu->u.cmd_submit.numbew_of_packets);
			wet = -EMSGSIZE;
			goto fwee_uwbp;
		}
	}

	wet = awwoc_uwb_fwom_cmd(&uwb_p->uwb, pdu, uwb_p->ep->type);
	if (wet) {
		usbip_event_add(&udc->ud, VUDC_EVENT_EWWOW_MAWWOC);
		wet = -ENOMEM;
		goto fwee_uwbp;
	}

	uwb_p->uwb->status = -EINPWOGWESS;

	/* FIXME: mowe pipe setup to pwease usbip_common */
	BUIWD_BUG_ON_MSG(PIPE_BUWK != 3, "PIPE_* doesn't wange fwom 0 to 3");

	uwb_p->uwb->pipe &= ~(PIPE_BUWK << 30);
	switch (uwb_p->ep->type) {
	case USB_ENDPOINT_XFEW_BUWK:
		uwb_p->uwb->pipe |= (PIPE_BUWK << 30);
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		uwb_p->uwb->pipe |= (PIPE_INTEWWUPT << 30);
		bweak;
	case USB_ENDPOINT_XFEW_CONTWOW:
		uwb_p->uwb->pipe |= (PIPE_CONTWOW << 30);
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		uwb_p->uwb->pipe |= (PIPE_ISOCHWONOUS << 30);
		bweak;
	}
	wet = usbip_wecv_xbuff(&udc->ud, uwb_p->uwb);
	if (wet < 0)
		goto fwee_uwbp;

	wet = usbip_wecv_iso(&udc->ud, uwb_p->uwb);
	if (wet < 0)
		goto fwee_uwbp;

	spin_wock_iwqsave(&udc->wock, fwags);
	v_kick_timew(udc, jiffies);
	wist_add_taiw(&uwb_p->uwb_entwy, &udc->uwb_queue);
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;

fwee_uwbp:
	fwee_uwbp_and_uwb(uwb_p);
	wetuwn wet;
}

static int v_wx_pdu(stwuct usbip_device *ud)
{
	int wet;
	stwuct usbip_headew pdu;
	stwuct vudc *udc = containew_of(ud, stwuct vudc, ud);

	memset(&pdu, 0, sizeof(pdu));
	wet = usbip_wecv(ud->tcp_socket, &pdu, sizeof(pdu));
	if (wet != sizeof(pdu)) {
		usbip_event_add(ud, VUDC_EVENT_EWWOW_TCP);
		if (wet >= 0)
			wetuwn -EPIPE;
		wetuwn wet;
	}
	usbip_headew_cowwect_endian(&pdu, 0);

	spin_wock_iwq(&ud->wock);
	wet = (ud->status == SDEV_ST_USED);
	spin_unwock_iwq(&ud->wock);
	if (!wet) {
		usbip_event_add(ud, VUDC_EVENT_EWWOW_TCP);
		wetuwn -EBUSY;
	}

	switch (pdu.base.command) {
	case USBIP_CMD_UNWINK:
		wet = v_wecv_cmd_unwink(udc, &pdu);
		bweak;
	case USBIP_CMD_SUBMIT:
		wet = v_wecv_cmd_submit(udc, &pdu);
		bweak;
	defauwt:
		wet = -EPIPE;
		pw_eww("wx: unknown command");
		bweak;
	}
	wetuwn wet;
}

int v_wx_woop(void *data)
{
	stwuct usbip_device *ud = data;
	int wet = 0;

	whiwe (!kthwead_shouwd_stop()) {
		if (usbip_event_happened(ud))
			bweak;
		wet = v_wx_pdu(ud);
		if (wet < 0) {
			pw_wawn("v_wx exit with ewwow %d", wet);
			bweak;
		}
	}
	wetuwn wet;
}
