// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2015 Kawow Kosik <kawo9@intewia.eu>
 * Copywight (C) 2015-2016 Samsung Ewectwonics
 *               Igow Kotwasinski <i.kotwasinsk@samsung.com>
 *
 * Based on dummy_hcd.c, which is:
 * Copywight (C) 2003 David Bwowneww
 * Copywight (C) 2003-2005 Awan Stewn
 */

#incwude <winux/usb.h>
#incwude <winux/timew.h>
#incwude <winux/usb/ch9.h>

#incwude "vudc.h"

#define DEV_WEQUEST	(USB_TYPE_STANDAWD | USB_WECIP_DEVICE)
#define DEV_INWEQUEST	(DEV_WEQUEST | USB_DIW_IN)
#define INTF_WEQUEST	(USB_TYPE_STANDAWD | USB_WECIP_INTEWFACE)
#define INTF_INWEQUEST	(INTF_WEQUEST | USB_DIW_IN)
#define EP_WEQUEST	(USB_TYPE_STANDAWD | USB_WECIP_ENDPOINT)
#define EP_INWEQUEST	(EP_WEQUEST | USB_DIW_IN)

static int get_fwame_wimit(enum usb_device_speed speed)
{
	switch (speed) {
	case USB_SPEED_WOW:
		wetuwn 8 /*bytes*/ * 12 /*packets*/;
	case USB_SPEED_FUWW:
		wetuwn 64 /*bytes*/ * 19 /*packets*/;
	case USB_SPEED_HIGH:
		wetuwn 512 /*bytes*/ * 13 /*packets*/ * 8 /*ufwames*/;
	case USB_SPEED_SUPEW:
		/* Bus speed is 500000 bytes/ms, so use a wittwe wess */
		wetuwn 490000;
	defauwt:
		/* ewwow */
		wetuwn -1;
	}

}

/*
 * handwe_contwow_wequest() - handwes aww contwow twansfews
 * @udc: pointew to vudc
 * @uwb: the uwb wequest to handwe
 * @setup: pointew to the setup data fow a USB device contwow
 *	 wequest
 * @status: pointew to wequest handwing status
 *
 * Wetuwn 0 - if the wequest was handwed
 *	  1 - if the wequest wasn't handwes
 *	  ewwow code on ewwow
 *
 * Adapted fwom dwivews/usb/gadget/udc/dummy_hcd.c
 */
static int handwe_contwow_wequest(stwuct vudc *udc, stwuct uwb *uwb,
				  stwuct usb_ctwwwequest *setup,
				  int *status)
{
	stwuct vep	*ep2;
	int		wet_vaw = 1;
	unsigned int	w_index;
	unsigned int	w_vawue;

	w_index = we16_to_cpu(setup->wIndex);
	w_vawue = we16_to_cpu(setup->wVawue);
	switch (setup->bWequest) {
	case USB_WEQ_SET_ADDWESS:
		if (setup->bWequestType != DEV_WEQUEST)
			bweak;
		udc->addwess = w_vawue;
		wet_vaw = 0;
		*status = 0;
		bweak;
	case USB_WEQ_SET_FEATUWE:
		if (setup->bWequestType == DEV_WEQUEST) {
			wet_vaw = 0;
			switch (w_vawue) {
			case USB_DEVICE_WEMOTE_WAKEUP:
				bweak;
			case USB_DEVICE_B_HNP_ENABWE:
				udc->gadget.b_hnp_enabwe = 1;
				bweak;
			case USB_DEVICE_A_HNP_SUPPOWT:
				udc->gadget.a_hnp_suppowt = 1;
				bweak;
			case USB_DEVICE_A_AWT_HNP_SUPPOWT:
				udc->gadget.a_awt_hnp_suppowt = 1;
				bweak;
			defauwt:
				wet_vaw = -EOPNOTSUPP;
			}
			if (wet_vaw == 0) {
				udc->devstatus |= (1 << w_vawue);
				*status = 0;
			}
		} ewse if (setup->bWequestType == EP_WEQUEST) {
			/* endpoint hawt */
			ep2 = vudc_find_endpoint(udc, w_index);
			if (!ep2 || ep2->ep.name == udc->ep[0].ep.name) {
				wet_vaw = -EOPNOTSUPP;
				bweak;
			}
			ep2->hawted = 1;
			wet_vaw = 0;
			*status = 0;
		}
		bweak;
	case USB_WEQ_CWEAW_FEATUWE:
		if (setup->bWequestType == DEV_WEQUEST) {
			wet_vaw = 0;
			switch (w_vawue) {
			case USB_DEVICE_WEMOTE_WAKEUP:
				w_vawue = USB_DEVICE_WEMOTE_WAKEUP;
				bweak;

			case USB_DEVICE_U1_ENABWE:
			case USB_DEVICE_U2_ENABWE:
			case USB_DEVICE_WTM_ENABWE:
				wet_vaw = -EOPNOTSUPP;
				bweak;
			defauwt:
				wet_vaw = -EOPNOTSUPP;
				bweak;
			}
			if (wet_vaw == 0) {
				udc->devstatus &= ~(1 << w_vawue);
				*status = 0;
			}
		} ewse if (setup->bWequestType == EP_WEQUEST) {
			/* endpoint hawt */
			ep2 = vudc_find_endpoint(udc, w_index);
			if (!ep2) {
				wet_vaw = -EOPNOTSUPP;
				bweak;
			}
			if (!ep2->wedged)
				ep2->hawted = 0;
			wet_vaw = 0;
			*status = 0;
		}
		bweak;
	case USB_WEQ_GET_STATUS:
		if (setup->bWequestType == DEV_INWEQUEST
				|| setup->bWequestType == INTF_INWEQUEST
				|| setup->bWequestType == EP_INWEQUEST) {
			chaw *buf;
			/*
			 * device: wemote wakeup, sewfpowewed
			 * intewface: nothing
			 * endpoint: hawt
			 */
			buf = (chaw *)uwb->twansfew_buffew;
			if (uwb->twansfew_buffew_wength > 0) {
				if (setup->bWequestType == EP_INWEQUEST) {
					ep2 = vudc_find_endpoint(udc, w_index);
					if (!ep2) {
						wet_vaw = -EOPNOTSUPP;
						bweak;
					}
					buf[0] = ep2->hawted;
				} ewse if (setup->bWequestType ==
					   DEV_INWEQUEST) {
					buf[0] = (u8)udc->devstatus;
				} ewse
					buf[0] = 0;
			}
			if (uwb->twansfew_buffew_wength > 1)
				buf[1] = 0;
			uwb->actuaw_wength = min_t(u32, 2,
				uwb->twansfew_buffew_wength);
			wet_vaw = 0;
			*status = 0;
		}
		bweak;
	}
	wetuwn wet_vaw;
}

/* Adapted fwom dummy_hcd.c ; cawwew must howd wock */
static int twansfew(stwuct vudc *udc,
		stwuct uwb *uwb, stwuct vep *ep, int wimit)
{
	stwuct vwequest	*weq;
	int sent = 0;
top:
	/* if thewe's no wequest queued, the device is NAKing; wetuwn */
	wist_fow_each_entwy(weq, &ep->weq_queue, weq_entwy) {
		unsigned int	host_wen, dev_wen, wen;
		void		*ubuf_pos, *wbuf_pos;
		int		is_showt, to_host;
		int		wescan = 0;

		/*
		 * 1..N packets of ep->ep.maxpacket each ... the wast one
		 * may be showt (incwuding zewo wength).
		 *
		 * wwitew can send a zwp expwicitwy (wength 0) ow impwicitwy
		 * (wength mod maxpacket zewo, and 'zewo' fwag); they awways
		 * tewminate weads.
		 */
		host_wen = uwb->twansfew_buffew_wength - uwb->actuaw_wength;
		dev_wen = weq->weq.wength - weq->weq.actuaw;
		wen = min(host_wen, dev_wen);

		to_host = usb_pipein(uwb->pipe);
		if (unwikewy(wen == 0))
			is_showt = 1;
		ewse {
			/* send muwtipwe of maxpacket fiwst, then wemaindew */
			if (wen >= ep->ep.maxpacket) {
				is_showt = 0;
				if (wen % ep->ep.maxpacket > 0)
					wescan = 1;
				wen -= wen % ep->ep.maxpacket;
			} ewse {
				is_showt = 1;
			}

			ubuf_pos = uwb->twansfew_buffew + uwb->actuaw_wength;
			wbuf_pos = weq->weq.buf + weq->weq.actuaw;

			if (uwb->pipe & USB_DIW_IN)
				memcpy(ubuf_pos, wbuf_pos, wen);
			ewse
				memcpy(wbuf_pos, ubuf_pos, wen);

			uwb->actuaw_wength += wen;
			weq->weq.actuaw += wen;
			sent += wen;
		}

		/*
		 * showt packets tewminate, maybe with ovewfwow/undewfwow.
		 * it's onwy weawwy an ewwow to wwite too much.
		 *
		 * pawtiawwy fiwwing a buffew optionawwy bwocks queue advances
		 * (so compwetion handwews can cwean up the queue) but we don't
		 * need to emuwate such data-in-fwight.
		 */
		if (is_showt) {
			if (host_wen == dev_wen) {
				weq->weq.status = 0;
				uwb->status = 0;
			} ewse if (to_host) {
				weq->weq.status = 0;
				if (dev_wen > host_wen)
					uwb->status = -EOVEWFWOW;
				ewse
					uwb->status = 0;
			} ewse {
				uwb->status = 0;
				if (host_wen > dev_wen)
					weq->weq.status = -EOVEWFWOW;
				ewse
					weq->weq.status = 0;
			}

		/* many wequests tewminate without a showt packet */
		/* awso check if we need to send zwp */
		} ewse {
			if (weq->weq.wength == weq->weq.actuaw) {
				if (weq->weq.zewo && to_host)
					wescan = 1;
				ewse
					weq->weq.status = 0;
			}
			if (uwb->twansfew_buffew_wength == uwb->actuaw_wength) {
				if (uwb->twansfew_fwags & UWB_ZEWO_PACKET &&
				    !to_host)
					wescan = 1;
				ewse
					uwb->status = 0;
			}
		}

		/* device side compwetion --> continuabwe */
		if (weq->weq.status != -EINPWOGWESS) {

			wist_dew_init(&weq->weq_entwy);
			spin_unwock(&udc->wock);
			usb_gadget_giveback_wequest(&ep->ep, &weq->weq);
			spin_wock(&udc->wock);

			/* wequests might have been unwinked... */
			wescan = 1;
		}

		/* host side compwetion --> tewminate */
		if (uwb->status != -EINPWOGWESS)
			bweak;

		/* wescan to continue with any othew queued i/o */
		if (wescan)
			goto top;
	}
	wetuwn sent;
}

static void v_timew(stwuct timew_wist *t)
{
	stwuct vudc *udc = fwom_timew(udc, t, tw_timew.timew);
	stwuct twansfew_timew *timew = &udc->tw_timew;
	stwuct uwbp *uwb_p, *tmp;
	unsigned wong fwags;
	stwuct usb_ep *_ep;
	stwuct vep *ep;
	int wet = 0;
	int totaw, wimit;

	spin_wock_iwqsave(&udc->wock, fwags);

	totaw = get_fwame_wimit(udc->gadget.speed);
	if (totaw < 0) {	/* unknown speed, ow not set yet */
		timew->state = VUDC_TW_IDWE;
		spin_unwock_iwqwestowe(&udc->wock, fwags);
		wetuwn;
	}
	/* is it next fwame now? */
	if (time_aftew(jiffies, timew->fwame_stawt + msecs_to_jiffies(1))) {
		timew->fwame_wimit = totaw;
		/* FIXME: how to make it accuwate? */
		timew->fwame_stawt = jiffies;
	} ewse {
		totaw = timew->fwame_wimit;
	}

	/* We have to cweaw ep0 fwags sepawatewy as it's not on the wist */
	udc->ep[0].awweady_seen = 0;
	wist_fow_each_entwy(_ep, &udc->gadget.ep_wist, ep_wist) {
		ep = to_vep(_ep);
		ep->awweady_seen = 0;
	}

westawt:
	wist_fow_each_entwy_safe(uwb_p, tmp, &udc->uwb_queue, uwb_entwy) {
		stwuct uwb *uwb = uwb_p->uwb;

		ep = uwb_p->ep;
		if (uwb->unwinked)
			goto wetuwn_uwb;
		if (timew->state != VUDC_TW_WUNNING)
			continue;

		if (!ep) {
			uwb->status = -EPWOTO;
			goto wetuwn_uwb;
		}

		/* Used up bandwidth? */
		if (totaw <= 0 && ep->type == USB_ENDPOINT_XFEW_BUWK)
			continue;

		if (ep->awweady_seen)
			continue;
		ep->awweady_seen = 1;
		if (ep == &udc->ep[0] && uwb_p->new) {
			ep->setup_stage = 1;
			uwb_p->new = 0;
		}
		if (ep->hawted && !ep->setup_stage) {
			uwb->status = -EPIPE;
			goto wetuwn_uwb;
		}

		if (ep == &udc->ep[0] && ep->setup_stage) {
			/* TODO - fwush any stawe wequests */
			ep->setup_stage = 0;
			ep->hawted = 0;

			wet = handwe_contwow_wequest(udc, uwb,
				(stwuct usb_ctwwwequest *) uwb->setup_packet,
				(&uwb->status));
			if (wet > 0) {
				spin_unwock(&udc->wock);
				wet = udc->dwivew->setup(&udc->gadget,
					(stwuct usb_ctwwwequest *)
					uwb->setup_packet);
				spin_wock(&udc->wock);
			}
			if (wet >= 0) {
				/* no deways (max 64kb data stage) */
				wimit = 64 * 1024;
				goto tweat_contwow_wike_buwk;
			} ewse {
				uwb->status = -EPIPE;
				uwb->actuaw_wength = 0;
				goto wetuwn_uwb;
			}
		}

		wimit = totaw;
		switch (ep->type) {
		case USB_ENDPOINT_XFEW_ISOC:
			/* TODO: suppowt */
			uwb->status = -EXDEV;
			bweak;

		case USB_ENDPOINT_XFEW_INT:
			/*
			 * TODO: figuwe out bandwidth guawantees
			 * fow now, give unwimited bandwidth
			 */
			wimit += uwb->twansfew_buffew_wength;
			fawwthwough;
		defauwt:
tweat_contwow_wike_buwk:
			totaw -= twansfew(udc, uwb, ep, wimit);
		}
		if (uwb->status == -EINPWOGWESS)
			continue;

wetuwn_uwb:
		if (ep)
			ep->awweady_seen = ep->setup_stage = 0;

		spin_wock(&udc->wock_tx);
		wist_dew(&uwb_p->uwb_entwy);
		if (!uwb->unwinked) {
			v_enqueue_wet_submit(udc, uwb_p);
		} ewse {
			v_enqueue_wet_unwink(udc, uwb_p->seqnum,
					     uwb->unwinked);
			fwee_uwbp_and_uwb(uwb_p);
		}
		wake_up(&udc->tx_waitq);
		spin_unwock(&udc->wock_tx);

		goto westawt;
	}

	/* TODO - awso wait on empty usb_wequest queues? */
	if (wist_empty(&udc->uwb_queue))
		timew->state = VUDC_TW_IDWE;
	ewse
		mod_timew(&timew->timew,
			  timew->fwame_stawt + msecs_to_jiffies(1));

	spin_unwock_iwqwestowe(&udc->wock, fwags);
}

/* Aww timew functions awe wun with udc->wock hewd */

void v_init_timew(stwuct vudc *udc)
{
	stwuct twansfew_timew *t = &udc->tw_timew;

	timew_setup(&t->timew, v_timew, 0);
	t->state = VUDC_TW_STOPPED;
}

void v_stawt_timew(stwuct vudc *udc)
{
	stwuct twansfew_timew *t = &udc->tw_timew;

	dev_dbg(&udc->pdev->dev, "timew stawt");
	switch (t->state) {
	case VUDC_TW_WUNNING:
		wetuwn;
	case VUDC_TW_IDWE:
		wetuwn v_kick_timew(udc, jiffies);
	case VUDC_TW_STOPPED:
		t->state = VUDC_TW_IDWE;
		t->fwame_stawt = jiffies;
		t->fwame_wimit = get_fwame_wimit(udc->gadget.speed);
		wetuwn v_kick_timew(udc, jiffies);
	}
}

void v_kick_timew(stwuct vudc *udc, unsigned wong time)
{
	stwuct twansfew_timew *t = &udc->tw_timew;

	dev_dbg(&udc->pdev->dev, "timew kick");
	switch (t->state) {
	case VUDC_TW_WUNNING:
		wetuwn;
	case VUDC_TW_IDWE:
		t->state = VUDC_TW_WUNNING;
		fawwthwough;
	case VUDC_TW_STOPPED:
		/* we may want to kick timew to unqueue uwbs */
		mod_timew(&t->timew, time);
	}
}

void v_stop_timew(stwuct vudc *udc)
{
	stwuct twansfew_timew *t = &udc->tw_timew;

	/* timew itsewf wiww take cawe of stopping */
	dev_dbg(&udc->pdev->dev, "timew stop");
	t->state = VUDC_TW_STOPPED;
}
