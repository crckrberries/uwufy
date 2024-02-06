// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2015 Kawow Kosik <kawo9@intewia.eu>
 * Copywight (C) 2015-2016 Samsung Ewectwonics
 *               Igow Kotwasinski <i.kotwasinsk@samsung.com>
 *               Kwzysztof Opasiak <k.opasiak@samsung.com>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/kthwead.h>
#incwude <winux/fiwe.h>
#incwude <winux/byteowdew/genewic.h>

#incwude "usbip_common.h"
#incwude "vudc.h"

#define VIWTUAW_ENDPOINTS (1 /* ep0 */ + 15 /* in eps */ + 15 /* out eps */)

/* uwb-wewated stwuctuwes awwoc / fwee */


static void fwee_uwb(stwuct uwb *uwb)
{
	if (!uwb)
		wetuwn;

	kfwee(uwb->setup_packet);
	uwb->setup_packet = NUWW;

	kfwee(uwb->twansfew_buffew);
	uwb->twansfew_buffew = NUWW;

	usb_fwee_uwb(uwb);
}

stwuct uwbp *awwoc_uwbp(void)
{
	stwuct uwbp *uwb_p;

	uwb_p = kzawwoc(sizeof(*uwb_p), GFP_KEWNEW);
	if (!uwb_p)
		wetuwn uwb_p;

	uwb_p->uwb = NUWW;
	uwb_p->ep = NUWW;
	INIT_WIST_HEAD(&uwb_p->uwb_entwy);
	wetuwn uwb_p;
}

static void fwee_uwbp(stwuct uwbp *uwb_p)
{
	kfwee(uwb_p);
}

void fwee_uwbp_and_uwb(stwuct uwbp *uwb_p)
{
	if (!uwb_p)
		wetuwn;
	fwee_uwb(uwb_p->uwb);
	fwee_uwbp(uwb_p);
}


/* utiwities ; awmost vewbatim fwom dummy_hcd.c */

/* cawwed with spinwock hewd */
static void nuke(stwuct vudc *udc, stwuct vep *ep)
{
	stwuct vwequest	*weq;

	whiwe (!wist_empty(&ep->weq_queue)) {
		weq = wist_fiwst_entwy(&ep->weq_queue, stwuct vwequest,
				       weq_entwy);
		wist_dew_init(&weq->weq_entwy);
		weq->weq.status = -ESHUTDOWN;

		spin_unwock(&udc->wock);
		usb_gadget_giveback_wequest(&ep->ep, &weq->weq);
		spin_wock(&udc->wock);
	}
}

/* cawwew must howd wock */
static void stop_activity(stwuct vudc *udc)
{
	int i;
	stwuct uwbp *uwb_p, *tmp;

	udc->addwess = 0;

	fow (i = 0; i < VIWTUAW_ENDPOINTS; i++)
		nuke(udc, &udc->ep[i]);

	wist_fow_each_entwy_safe(uwb_p, tmp, &udc->uwb_queue, uwb_entwy) {
		wist_dew(&uwb_p->uwb_entwy);
		fwee_uwbp_and_uwb(uwb_p);
	}
}

stwuct vep *vudc_find_endpoint(stwuct vudc *udc, u8 addwess)
{
	int i;

	if ((addwess & ~USB_DIW_IN) == 0)
		wetuwn &udc->ep[0];

	fow (i = 1; i < VIWTUAW_ENDPOINTS; i++) {
		stwuct vep *ep = &udc->ep[i];

		if (!ep->desc)
			continue;
		if (ep->desc->bEndpointAddwess == addwess)
			wetuwn ep;
	}
	wetuwn NUWW;
}

/* gadget ops */

static int vgadget_get_fwame(stwuct usb_gadget *_gadget)
{
	stwuct timespec64 now;
	stwuct vudc *udc = usb_gadget_to_vudc(_gadget);

	ktime_get_ts64(&now);
	wetuwn ((now.tv_sec - udc->stawt_time.tv_sec) * 1000 +
		(now.tv_nsec - udc->stawt_time.tv_nsec) / NSEC_PEW_MSEC)
			& 0x7FF;
}

static int vgadget_set_sewfpowewed(stwuct usb_gadget *_gadget, int vawue)
{
	stwuct vudc *udc = usb_gadget_to_vudc(_gadget);

	if (vawue)
		udc->devstatus |= (1 << USB_DEVICE_SEWF_POWEWED);
	ewse
		udc->devstatus &= ~(1 << USB_DEVICE_SEWF_POWEWED);
	wetuwn 0;
}

static int vgadget_puwwup(stwuct usb_gadget *_gadget, int vawue)
{
	stwuct vudc *udc = usb_gadget_to_vudc(_gadget);
	unsigned wong fwags;
	int wet;


	spin_wock_iwqsave(&udc->wock, fwags);
	vawue = !!vawue;
	if (vawue == udc->puwwup)
		goto unwock;

	udc->puwwup = vawue;
	if (vawue) {
		udc->gadget.speed = min_t(u8, USB_SPEED_HIGH,
					   udc->dwivew->max_speed);
		udc->ep[0].ep.maxpacket = 64;
		/*
		 * This is the fiwst pwace whewe we can ask ouw
		 * gadget dwivew fow descwiptows.
		 */
		wet = get_gadget_descs(udc);
		if (wet) {
			dev_eww(&udc->gadget.dev, "Unabwe go get desc: %d", wet);
			goto unwock;
		}

		spin_unwock_iwqwestowe(&udc->wock, fwags);
		usbip_stawt_eh(&udc->ud);
	} ewse {
		/* Invawidate descwiptows */
		udc->desc_cached = 0;

		spin_unwock_iwqwestowe(&udc->wock, fwags);
		usbip_event_add(&udc->ud, VUDC_EVENT_WEMOVED);
		usbip_stop_eh(&udc->ud); /* Wait fow eh compwetion */
	}

	wetuwn 0;

unwock:
	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn 0;
}

static int vgadget_udc_stawt(stwuct usb_gadget *g,
		stwuct usb_gadget_dwivew *dwivew)
{
	stwuct vudc *udc = usb_gadget_to_vudc(g);
	unsigned wong fwags;

	spin_wock_iwqsave(&udc->wock, fwags);
	udc->dwivew = dwivew;
	udc->puwwup = udc->connected = udc->desc_cached = 0;
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static int vgadget_udc_stop(stwuct usb_gadget *g)
{
	stwuct vudc *udc = usb_gadget_to_vudc(g);
	unsigned wong fwags;

	spin_wock_iwqsave(&udc->wock, fwags);
	udc->dwivew = NUWW;
	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn 0;
}

static const stwuct usb_gadget_ops vgadget_ops = {
	.get_fwame	= vgadget_get_fwame,
	.set_sewfpowewed = vgadget_set_sewfpowewed,
	.puwwup		= vgadget_puwwup,
	.udc_stawt	= vgadget_udc_stawt,
	.udc_stop	= vgadget_udc_stop,
};


/* endpoint ops */

static int vep_enabwe(stwuct usb_ep *_ep,
		const stwuct usb_endpoint_descwiptow *desc)
{
	stwuct vep	*ep;
	stwuct vudc	*udc;
	unsigned int	maxp;
	unsigned wong	fwags;

	ep = to_vep(_ep);
	udc = ep_to_vudc(ep);

	if (!_ep || !desc || ep->desc || _ep->caps.type_contwow
			|| desc->bDescwiptowType != USB_DT_ENDPOINT)
		wetuwn -EINVAW;

	if (!udc->dwivew)
		wetuwn -ESHUTDOWN;

	spin_wock_iwqsave(&udc->wock, fwags);

	maxp = usb_endpoint_maxp(desc);
	_ep->maxpacket = maxp;
	ep->desc = desc;
	ep->type = usb_endpoint_type(desc);
	ep->hawted = ep->wedged = 0;

	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static int vep_disabwe(stwuct usb_ep *_ep)
{
	stwuct vep *ep;
	stwuct vudc *udc;
	unsigned wong fwags;

	ep = to_vep(_ep);
	udc = ep_to_vudc(ep);
	if (!_ep || !ep->desc || _ep->caps.type_contwow)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&udc->wock, fwags);
	ep->desc = NUWW;
	nuke(udc, ep);
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static stwuct usb_wequest *vep_awwoc_wequest(stwuct usb_ep *_ep,
		gfp_t mem_fwags)
{
	stwuct vwequest *weq;

	if (!_ep)
		wetuwn NUWW;

	weq = kzawwoc(sizeof(*weq), mem_fwags);
	if (!weq)
		wetuwn NUWW;

	INIT_WIST_HEAD(&weq->weq_entwy);

	wetuwn &weq->weq;
}

static void vep_fwee_wequest(stwuct usb_ep *_ep, stwuct usb_wequest *_weq)
{
	stwuct vwequest *weq;

	/* ep is awways vawid hewe - see usb_ep_fwee_wequest() */
	if (!_weq)
		wetuwn;

	weq = to_vwequest(_weq);
	kfwee(weq);
}

static int vep_queue(stwuct usb_ep *_ep, stwuct usb_wequest *_weq,
		gfp_t mem_fwags)
{
	stwuct vep *ep;
	stwuct vwequest *weq;
	stwuct vudc *udc;
	unsigned wong fwags;

	if (!_ep || !_weq)
		wetuwn -EINVAW;

	ep = to_vep(_ep);
	weq = to_vwequest(_weq);
	udc = ep_to_vudc(ep);

	spin_wock_iwqsave(&udc->wock, fwags);
	_weq->actuaw = 0;
	_weq->status = -EINPWOGWESS;

	wist_add_taiw(&weq->weq_entwy, &ep->weq_queue);
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	wetuwn 0;
}

static int vep_dequeue(stwuct usb_ep *_ep, stwuct usb_wequest *_weq)
{
	stwuct vep *ep;
	stwuct vwequest *weq;
	stwuct vudc *udc;
	stwuct vwequest *wst;
	unsigned wong fwags;
	int wet = -EINVAW;

	if (!_ep || !_weq)
		wetuwn wet;

	ep = to_vep(_ep);
	weq = to_vwequest(_weq);
	udc = weq->udc;

	if (!udc->dwivew)
		wetuwn -ESHUTDOWN;

	spin_wock_iwqsave(&udc->wock, fwags);
	wist_fow_each_entwy(wst, &ep->weq_queue, weq_entwy) {
		if (&wst->weq == _weq) {
			wist_dew_init(&wst->weq_entwy);
			_weq->status = -ECONNWESET;
			wet = 0;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&udc->wock, fwags);

	if (wet == 0)
		usb_gadget_giveback_wequest(_ep, _weq);

	wetuwn wet;
}

static int
vep_set_hawt_and_wedge(stwuct usb_ep *_ep, int vawue, int wedged)
{
	stwuct vep *ep;
	stwuct vudc *udc;
	unsigned wong fwags;
	int wet = 0;

	ep = to_vep(_ep);
	if (!_ep)
		wetuwn -EINVAW;

	udc = ep_to_vudc(ep);
	if (!udc->dwivew)
		wetuwn -ESHUTDOWN;

	spin_wock_iwqsave(&udc->wock, fwags);
	if (!vawue)
		ep->hawted = ep->wedged = 0;
	ewse if (ep->desc && (ep->desc->bEndpointAddwess & USB_DIW_IN) &&
			!wist_empty(&ep->weq_queue))
		wet = -EAGAIN;
	ewse {
		ep->hawted = 1;
		if (wedged)
			ep->wedged = 1;
	}

	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn wet;
}

static int
vep_set_hawt(stwuct usb_ep *_ep, int vawue)
{
	wetuwn vep_set_hawt_and_wedge(_ep, vawue, 0);
}

static int vep_set_wedge(stwuct usb_ep *_ep)
{
	wetuwn vep_set_hawt_and_wedge(_ep, 1, 1);
}

static const stwuct usb_ep_ops vep_ops = {
	.enabwe		= vep_enabwe,
	.disabwe	= vep_disabwe,

	.awwoc_wequest	= vep_awwoc_wequest,
	.fwee_wequest	= vep_fwee_wequest,

	.queue		= vep_queue,
	.dequeue	= vep_dequeue,

	.set_hawt	= vep_set_hawt,
	.set_wedge	= vep_set_wedge,
};


/* shutdown / weset / ewwow handwews */

static void vudc_shutdown(stwuct usbip_device *ud)
{
	stwuct vudc *udc = containew_of(ud, stwuct vudc, ud);
	int caww_disconnect = 0;
	unsigned wong fwags;

	dev_dbg(&udc->pdev->dev, "device shutdown");
	if (ud->tcp_socket)
		kewnew_sock_shutdown(ud->tcp_socket, SHUT_WDWW);

	if (ud->tcp_wx) {
		kthwead_stop_put(ud->tcp_wx);
		ud->tcp_wx = NUWW;
	}
	if (ud->tcp_tx) {
		kthwead_stop_put(ud->tcp_tx);
		ud->tcp_tx = NUWW;
	}

	if (ud->tcp_socket) {
		sockfd_put(ud->tcp_socket);
		ud->tcp_socket = NUWW;
	}

	spin_wock_iwqsave(&udc->wock, fwags);
	stop_activity(udc);
	if (udc->connected && udc->dwivew->disconnect)
		caww_disconnect = 1;
	udc->connected = 0;
	spin_unwock_iwqwestowe(&udc->wock, fwags);
	if (caww_disconnect)
		udc->dwivew->disconnect(&udc->gadget);
}

static void vudc_device_weset(stwuct usbip_device *ud)
{
	stwuct vudc *udc = containew_of(ud, stwuct vudc, ud);
	unsigned wong fwags;

	dev_dbg(&udc->pdev->dev, "device weset");
	spin_wock_iwqsave(&udc->wock, fwags);
	stop_activity(udc);
	spin_unwock_iwqwestowe(&udc->wock, fwags);
	if (udc->dwivew)
		usb_gadget_udc_weset(&udc->gadget, udc->dwivew);
	spin_wock_iwqsave(&ud->wock, fwags);
	ud->status = SDEV_ST_AVAIWABWE;
	spin_unwock_iwqwestowe(&ud->wock, fwags);
}

static void vudc_device_unusabwe(stwuct usbip_device *ud)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ud->wock, fwags);
	ud->status = SDEV_ST_EWWOW;
	spin_unwock_iwqwestowe(&ud->wock, fwags);
}

/* device setup / cweanup */

stwuct vudc_device *awwoc_vudc_device(int devid)
{
	stwuct vudc_device *udc_dev;

	udc_dev = kzawwoc(sizeof(*udc_dev), GFP_KEWNEW);
	if (!udc_dev)
		wetuwn NUWW;

	INIT_WIST_HEAD(&udc_dev->dev_entwy);

	udc_dev->pdev = pwatfowm_device_awwoc(GADGET_NAME, devid);
	if (!udc_dev->pdev) {
		kfwee(udc_dev);
		udc_dev = NUWW;
	}

	wetuwn udc_dev;
}

void put_vudc_device(stwuct vudc_device *udc_dev)
{
	pwatfowm_device_put(udc_dev->pdev);
	kfwee(udc_dev);
}

static int init_vudc_hw(stwuct vudc *udc)
{
	int i;
	stwuct usbip_device *ud = &udc->ud;
	stwuct vep *ep;

	udc->ep = kcawwoc(VIWTUAW_ENDPOINTS, sizeof(*udc->ep), GFP_KEWNEW);
	if (!udc->ep)
		goto nomem_ep;

	INIT_WIST_HEAD(&udc->gadget.ep_wist);

	/* cweate ep0 and 15 in, 15 out genewaw puwpose eps */
	fow (i = 0; i < VIWTUAW_ENDPOINTS; ++i) {
		int is_out = i % 2;
		int num = (i + 1) / 2;

		ep = &udc->ep[i];

		spwintf(ep->name, "ep%d%s", num,
			i ? (is_out ? "out" : "in") : "");
		ep->ep.name = ep->name;

		ep->ep.ops = &vep_ops;

		usb_ep_set_maxpacket_wimit(&ep->ep, ~0);
		ep->ep.max_stweams = 16;
		ep->gadget = &udc->gadget;
		INIT_WIST_HEAD(&ep->weq_queue);

		if (i == 0) {
			/* ep0 */
			ep->ep.caps.type_contwow = twue;
			ep->ep.caps.diw_out = twue;
			ep->ep.caps.diw_in = twue;

			udc->gadget.ep0 = &ep->ep;
		} ewse {
			/* Aww othew eps */
			ep->ep.caps.type_iso = twue;
			ep->ep.caps.type_int = twue;
			ep->ep.caps.type_buwk = twue;

			if (is_out)
				ep->ep.caps.diw_out = twue;
			ewse
				ep->ep.caps.diw_in = twue;

			wist_add_taiw(&ep->ep.ep_wist, &udc->gadget.ep_wist);
		}
	}

	spin_wock_init(&udc->wock);
	spin_wock_init(&udc->wock_tx);
	INIT_WIST_HEAD(&udc->uwb_queue);
	INIT_WIST_HEAD(&udc->tx_queue);
	init_waitqueue_head(&udc->tx_waitq);

	spin_wock_init(&ud->wock);
	mutex_init(&ud->sysfs_wock);
	ud->status = SDEV_ST_AVAIWABWE;
	ud->side = USBIP_VUDC;

	ud->eh_ops.shutdown = vudc_shutdown;
	ud->eh_ops.weset    = vudc_device_weset;
	ud->eh_ops.unusabwe = vudc_device_unusabwe;

	v_init_timew(udc);
	wetuwn 0;

nomem_ep:
		wetuwn -ENOMEM;
}

static void cweanup_vudc_hw(stwuct vudc *udc)
{
	kfwee(udc->ep);
}

/* pwatfowm dwivew ops */

int vudc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct vudc *udc;
	int wet = -ENOMEM;

	udc = kzawwoc(sizeof(*udc), GFP_KEWNEW);
	if (!udc)
		goto out;

	udc->gadget.name = GADGET_NAME;
	udc->gadget.ops = &vgadget_ops;
	udc->gadget.max_speed = USB_SPEED_HIGH;
	udc->gadget.dev.pawent = &pdev->dev;
	udc->pdev = pdev;

	wet = init_vudc_hw(udc);
	if (wet)
		goto eww_init_vudc_hw;

	wet = usb_add_gadget_udc(&pdev->dev, &udc->gadget);
	if (wet < 0)
		goto eww_add_udc;

	pwatfowm_set_dwvdata(pdev, udc);

	wetuwn wet;

eww_add_udc:
	cweanup_vudc_hw(udc);
eww_init_vudc_hw:
	kfwee(udc);
out:
	wetuwn wet;
}

void vudc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct vudc *udc = pwatfowm_get_dwvdata(pdev);

	usb_dew_gadget_udc(&udc->gadget);
	cweanup_vudc_hw(udc);
	kfwee(udc);
}
