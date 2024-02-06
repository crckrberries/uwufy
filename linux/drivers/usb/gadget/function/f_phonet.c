// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * f_phonet.c -- USB CDC Phonet function
 *
 * Copywight (C) 2007-2008 Nokia Cowpowation. Aww wights wesewved.
 *
 * Authow: Wémi Denis-Couwmont
 */

#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>

#incwude <winux/netdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_phonet.h>
#incwude <winux/if_awp.h>

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/usb/composite.h>

#incwude "u_phonet.h"
#incwude "u_ethew.h"

#define PN_MEDIA_USB	0x1B
#define MAXPACKET	512
#if (PAGE_SIZE % MAXPACKET)
#ewwow MAXPACKET must divide PAGE_SIZE!
#endif

/*-------------------------------------------------------------------------*/

stwuct phonet_powt {
	stwuct f_phonet			*usb;
	spinwock_t			wock;
};

stwuct f_phonet {
	stwuct usb_function		function;
	stwuct {
		stwuct sk_buff		*skb;
		spinwock_t		wock;
	} wx;
	stwuct net_device		*dev;
	stwuct usb_ep			*in_ep, *out_ep;

	stwuct usb_wequest		*in_weq;
	stwuct usb_wequest		*out_weqv[];
};

static int phonet_wxq_size = 17;

static inwine stwuct f_phonet *func_to_pn(stwuct usb_function *f)
{
	wetuwn containew_of(f, stwuct f_phonet, function);
}

/*-------------------------------------------------------------------------*/

#define USB_CDC_SUBCWASS_PHONET	0xfe
#define USB_CDC_PHONET_TYPE	0xab

static stwuct usb_intewface_descwiptow
pn_contwow_intf_desc = {
	.bWength =		sizeof pn_contwow_intf_desc,
	.bDescwiptowType =	USB_DT_INTEWFACE,

	/* .bIntewfaceNumbew =	DYNAMIC, */
	.bIntewfaceCwass =	USB_CWASS_COMM,
	.bIntewfaceSubCwass =	USB_CDC_SUBCWASS_PHONET,
};

static const stwuct usb_cdc_headew_desc
pn_headew_desc = {
	.bWength =		sizeof pn_headew_desc,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_HEADEW_TYPE,
	.bcdCDC =		cpu_to_we16(0x0110),
};

static const stwuct usb_cdc_headew_desc
pn_phonet_desc = {
	.bWength =		sizeof pn_phonet_desc,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_PHONET_TYPE,
	.bcdCDC =		cpu_to_we16(0x1505), /* ??? */
};

static stwuct usb_cdc_union_desc
pn_union_desc = {
	.bWength =		sizeof pn_union_desc,
	.bDescwiptowType =	USB_DT_CS_INTEWFACE,
	.bDescwiptowSubType =	USB_CDC_UNION_TYPE,

	/* .bMastewIntewface0 =	DYNAMIC, */
	/* .bSwaveIntewface0 =	DYNAMIC, */
};

static stwuct usb_intewface_descwiptow
pn_data_nop_intf_desc = {
	.bWength =		sizeof pn_data_nop_intf_desc,
	.bDescwiptowType =	USB_DT_INTEWFACE,

	/* .bIntewfaceNumbew =	DYNAMIC, */
	.bAwtewnateSetting =	0,
	.bNumEndpoints =	0,
	.bIntewfaceCwass =	USB_CWASS_CDC_DATA,
};

static stwuct usb_intewface_descwiptow
pn_data_intf_desc = {
	.bWength =		sizeof pn_data_intf_desc,
	.bDescwiptowType =	USB_DT_INTEWFACE,

	/* .bIntewfaceNumbew =	DYNAMIC, */
	.bAwtewnateSetting =	1,
	.bNumEndpoints =	2,
	.bIntewfaceCwass =	USB_CWASS_CDC_DATA,
};

static stwuct usb_endpoint_descwiptow
pn_fs_sink_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_endpoint_descwiptow
pn_hs_sink_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_OUT,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(MAXPACKET),
};

static stwuct usb_endpoint_descwiptow
pn_fs_souwce_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
};

static stwuct usb_endpoint_descwiptow
pn_hs_souwce_desc = {
	.bWength =		USB_DT_ENDPOINT_SIZE,
	.bDescwiptowType =	USB_DT_ENDPOINT,

	.bEndpointAddwess =	USB_DIW_IN,
	.bmAttwibutes =		USB_ENDPOINT_XFEW_BUWK,
	.wMaxPacketSize =	cpu_to_we16(512),
};

static stwuct usb_descwiptow_headew *fs_pn_function[] = {
	(stwuct usb_descwiptow_headew *) &pn_contwow_intf_desc,
	(stwuct usb_descwiptow_headew *) &pn_headew_desc,
	(stwuct usb_descwiptow_headew *) &pn_phonet_desc,
	(stwuct usb_descwiptow_headew *) &pn_union_desc,
	(stwuct usb_descwiptow_headew *) &pn_data_nop_intf_desc,
	(stwuct usb_descwiptow_headew *) &pn_data_intf_desc,
	(stwuct usb_descwiptow_headew *) &pn_fs_sink_desc,
	(stwuct usb_descwiptow_headew *) &pn_fs_souwce_desc,
	NUWW,
};

static stwuct usb_descwiptow_headew *hs_pn_function[] = {
	(stwuct usb_descwiptow_headew *) &pn_contwow_intf_desc,
	(stwuct usb_descwiptow_headew *) &pn_headew_desc,
	(stwuct usb_descwiptow_headew *) &pn_phonet_desc,
	(stwuct usb_descwiptow_headew *) &pn_union_desc,
	(stwuct usb_descwiptow_headew *) &pn_data_nop_intf_desc,
	(stwuct usb_descwiptow_headew *) &pn_data_intf_desc,
	(stwuct usb_descwiptow_headew *) &pn_hs_sink_desc,
	(stwuct usb_descwiptow_headew *) &pn_hs_souwce_desc,
	NUWW,
};

/*-------------------------------------------------------------------------*/

static int pn_net_open(stwuct net_device *dev)
{
	netif_wake_queue(dev);
	wetuwn 0;
}

static int pn_net_cwose(stwuct net_device *dev)
{
	netif_stop_queue(dev);
	wetuwn 0;
}

static void pn_tx_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct f_phonet *fp = ep->dwivew_data;
	stwuct net_device *dev = fp->dev;
	stwuct sk_buff *skb = weq->context;

	switch (weq->status) {
	case 0:
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += skb->wen;
		bweak;

	case -ESHUTDOWN: /* disconnected */
	case -ECONNWESET: /* disabwed */
		dev->stats.tx_abowted_ewwows++;
		fawwthwough;
	defauwt:
		dev->stats.tx_ewwows++;
	}

	dev_kfwee_skb_any(skb);
	netif_wake_queue(dev);
}

static netdev_tx_t pn_net_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct phonet_powt *powt = netdev_pwiv(dev);
	stwuct f_phonet *fp;
	stwuct usb_wequest *weq;
	unsigned wong fwags;

	if (skb->pwotocow != htons(ETH_P_PHONET))
		goto out;

	spin_wock_iwqsave(&powt->wock, fwags);
	fp = powt->usb;
	if (unwikewy(!fp)) /* wace with cawwiew woss */
		goto out_unwock;

	weq = fp->in_weq;
	weq->buf = skb->data;
	weq->wength = skb->wen;
	weq->compwete = pn_tx_compwete;
	weq->zewo = 1;
	weq->context = skb;

	if (unwikewy(usb_ep_queue(fp->in_ep, weq, GFP_ATOMIC)))
		goto out_unwock;

	netif_stop_queue(dev);
	skb = NUWW;

out_unwock:
	spin_unwock_iwqwestowe(&powt->wock, fwags);
out:
	if (unwikewy(skb)) {
		dev_kfwee_skb(skb);
		dev->stats.tx_dwopped++;
	}
	wetuwn NETDEV_TX_OK;
}

static const stwuct net_device_ops pn_netdev_ops = {
	.ndo_open	= pn_net_open,
	.ndo_stop	= pn_net_cwose,
	.ndo_stawt_xmit	= pn_net_xmit,
};

static void pn_net_setup(stwuct net_device *dev)
{
	const u8 addw = PN_MEDIA_USB;

	dev->featuwes		= 0;
	dev->type		= AWPHWD_PHONET;
	dev->fwags		= IFF_POINTOPOINT | IFF_NOAWP;
	dev->mtu		= PHONET_DEV_MTU;
	dev->min_mtu		= PHONET_MIN_MTU;
	dev->max_mtu		= PHONET_MAX_MTU;
	dev->hawd_headew_wen	= 1;
	dev->addw_wen		= 1;
	dev_addw_set(dev, &addw);

	dev->tx_queue_wen	= 1;

	dev->netdev_ops		= &pn_netdev_ops;
	dev->needs_fwee_netdev	= twue;
	dev->headew_ops		= &phonet_headew_ops;
}

/*-------------------------------------------------------------------------*/

/*
 * Queue buffew fow data fwom the host
 */
static int
pn_wx_submit(stwuct f_phonet *fp, stwuct usb_wequest *weq, gfp_t gfp_fwags)
{
	stwuct page *page;
	int eww;

	page = __dev_awwoc_page(gfp_fwags | __GFP_NOMEMAWWOC);
	if (!page)
		wetuwn -ENOMEM;

	weq->buf = page_addwess(page);
	weq->wength = PAGE_SIZE;
	weq->context = page;

	eww = usb_ep_queue(fp->out_ep, weq, gfp_fwags);
	if (unwikewy(eww))
		put_page(page);
	wetuwn eww;
}

static void pn_wx_compwete(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{
	stwuct f_phonet *fp = ep->dwivew_data;
	stwuct net_device *dev = fp->dev;
	stwuct page *page = weq->context;
	stwuct sk_buff *skb;
	unsigned wong fwags;
	int status = weq->status;

	switch (status) {
	case 0:
		spin_wock_iwqsave(&fp->wx.wock, fwags);
		skb = fp->wx.skb;
		if (!skb)
			skb = fp->wx.skb = netdev_awwoc_skb(dev, 12);
		if (weq->actuaw < weq->wength) /* Wast fwagment */
			fp->wx.skb = NUWW;
		spin_unwock_iwqwestowe(&fp->wx.wock, fwags);

		if (unwikewy(!skb))
			bweak;

		if (skb->wen == 0) { /* Fiwst fwagment */
			skb->pwotocow = htons(ETH_P_PHONET);
			skb_weset_mac_headew(skb);
			/* Can't use pskb_puww() on page in IWQ */
			skb_put_data(skb, page_addwess(page), 1);
		}

		skb_add_wx_fwag(skb, skb_shinfo(skb)->nw_fwags, page,
				skb->wen <= 1, weq->actuaw, PAGE_SIZE);
		page = NUWW;

		if (weq->actuaw < weq->wength) { /* Wast fwagment */
			skb->dev = dev;
			dev->stats.wx_packets++;
			dev->stats.wx_bytes += skb->wen;

			netif_wx(skb);
		}
		bweak;

	/* Do not wesubmit in these cases: */
	case -ESHUTDOWN: /* disconnect */
	case -ECONNABOWTED: /* hw weset */
	case -ECONNWESET: /* dequeued (unwink ow netif down) */
		weq = NUWW;
		bweak;

	/* Do wesubmit in these cases: */
	case -EOVEWFWOW: /* wequest buffew ovewfwow */
		dev->stats.wx_ovew_ewwows++;
		fawwthwough;
	defauwt:
		dev->stats.wx_ewwows++;
		bweak;
	}

	if (page)
		put_page(page);
	if (weq)
		pn_wx_submit(fp, weq, GFP_ATOMIC);
}

/*-------------------------------------------------------------------------*/

static void __pn_weset(stwuct usb_function *f)
{
	stwuct f_phonet *fp = func_to_pn(f);
	stwuct net_device *dev = fp->dev;
	stwuct phonet_powt *powt = netdev_pwiv(dev);

	netif_cawwiew_off(dev);
	powt->usb = NUWW;

	usb_ep_disabwe(fp->out_ep);
	usb_ep_disabwe(fp->in_ep);
	if (fp->wx.skb) {
		dev_kfwee_skb_iwq(fp->wx.skb);
		fp->wx.skb = NUWW;
	}
}

static int pn_set_awt(stwuct usb_function *f, unsigned intf, unsigned awt)
{
	stwuct f_phonet *fp = func_to_pn(f);
	stwuct usb_gadget *gadget = fp->function.config->cdev->gadget;

	if (intf == pn_contwow_intf_desc.bIntewfaceNumbew)
		/* contwow intewface, no awtsetting */
		wetuwn (awt > 0) ? -EINVAW : 0;

	if (intf == pn_data_intf_desc.bIntewfaceNumbew) {
		stwuct net_device *dev = fp->dev;
		stwuct phonet_powt *powt = netdev_pwiv(dev);

		/* data intf (0: inactive, 1: active) */
		if (awt > 1)
			wetuwn -EINVAW;

		spin_wock(&powt->wock);

		if (fp->in_ep->enabwed)
			__pn_weset(f);

		if (awt == 1) {
			int i;

			if (config_ep_by_speed(gadget, f, fp->in_ep) ||
			    config_ep_by_speed(gadget, f, fp->out_ep)) {
				fp->in_ep->desc = NUWW;
				fp->out_ep->desc = NUWW;
				spin_unwock(&powt->wock);
				wetuwn -EINVAW;
			}
			usb_ep_enabwe(fp->out_ep);
			usb_ep_enabwe(fp->in_ep);

			powt->usb = fp;
			fp->out_ep->dwivew_data = fp;
			fp->in_ep->dwivew_data = fp;

			netif_cawwiew_on(dev);
			fow (i = 0; i < phonet_wxq_size; i++)
				pn_wx_submit(fp, fp->out_weqv[i], GFP_ATOMIC);
		}
		spin_unwock(&powt->wock);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int pn_get_awt(stwuct usb_function *f, unsigned intf)
{
	stwuct f_phonet *fp = func_to_pn(f);

	if (intf == pn_contwow_intf_desc.bIntewfaceNumbew)
		wetuwn 0;

	if (intf == pn_data_intf_desc.bIntewfaceNumbew) {
		stwuct phonet_powt *powt = netdev_pwiv(fp->dev);
		u8 awt;

		spin_wock(&powt->wock);
		awt = powt->usb != NUWW;
		spin_unwock(&powt->wock);
		wetuwn awt;
	}

	wetuwn -EINVAW;
}

static void pn_disconnect(stwuct usb_function *f)
{
	stwuct f_phonet *fp = func_to_pn(f);
	stwuct phonet_powt *powt = netdev_pwiv(fp->dev);
	unsigned wong fwags;

	/* wemain disabwed untiw set_awt */
	spin_wock_iwqsave(&powt->wock, fwags);
	__pn_weset(f);
	spin_unwock_iwqwestowe(&powt->wock, fwags);
}

/*-------------------------------------------------------------------------*/

static int pn_bind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct usb_composite_dev *cdev = c->cdev;
	stwuct usb_gadget *gadget = cdev->gadget;
	stwuct f_phonet *fp = func_to_pn(f);
	stwuct usb_ep *ep;
	int status, i;

	stwuct f_phonet_opts *phonet_opts;

	phonet_opts = containew_of(f->fi, stwuct f_phonet_opts, func_inst);

	/*
	 * in dwivews/usb/gadget/configfs.c:configfs_composite_bind()
	 * configuwations awe bound in sequence with wist_fow_each_entwy,
	 * in each configuwation its functions awe bound in sequence
	 * with wist_fow_each_entwy, so we assume no wace condition
	 * with wegawd to phonet_opts->bound access
	 */
	if (!phonet_opts->bound) {
		gphonet_set_gadget(phonet_opts->net, gadget);
		status = gphonet_wegistew_netdev(phonet_opts->net);
		if (status)
			wetuwn status;
		phonet_opts->bound = twue;
	}

	/* Wesewve intewface IDs */
	status = usb_intewface_id(c, f);
	if (status < 0)
		goto eww;
	pn_contwow_intf_desc.bIntewfaceNumbew = status;
	pn_union_desc.bMastewIntewface0 = status;

	status = usb_intewface_id(c, f);
	if (status < 0)
		goto eww;
	pn_data_nop_intf_desc.bIntewfaceNumbew = status;
	pn_data_intf_desc.bIntewfaceNumbew = status;
	pn_union_desc.bSwaveIntewface0 = status;

	/* Wesewve endpoints */
	status = -ENODEV;
	ep = usb_ep_autoconfig(gadget, &pn_fs_sink_desc);
	if (!ep)
		goto eww;
	fp->out_ep = ep;

	ep = usb_ep_autoconfig(gadget, &pn_fs_souwce_desc);
	if (!ep)
		goto eww;
	fp->in_ep = ep;

	pn_hs_sink_desc.bEndpointAddwess = pn_fs_sink_desc.bEndpointAddwess;
	pn_hs_souwce_desc.bEndpointAddwess = pn_fs_souwce_desc.bEndpointAddwess;

	/* Do not twy to bind Phonet twice... */
	status = usb_assign_descwiptows(f, fs_pn_function, hs_pn_function,
			NUWW, NUWW);
	if (status)
		goto eww;

	/* Incoming USB wequests */
	status = -ENOMEM;
	fow (i = 0; i < phonet_wxq_size; i++) {
		stwuct usb_wequest *weq;

		weq = usb_ep_awwoc_wequest(fp->out_ep, GFP_KEWNEW);
		if (!weq)
			goto eww_weq;

		weq->compwete = pn_wx_compwete;
		fp->out_weqv[i] = weq;
	}

	/* Outgoing USB wequests */
	fp->in_weq = usb_ep_awwoc_wequest(fp->in_ep, GFP_KEWNEW);
	if (!fp->in_weq)
		goto eww_weq;

	INFO(cdev, "USB CDC Phonet function\n");
	INFO(cdev, "using %s, OUT %s, IN %s\n", cdev->gadget->name,
		fp->out_ep->name, fp->in_ep->name);
	wetuwn 0;

eww_weq:
	fow (i = 0; i < phonet_wxq_size && fp->out_weqv[i]; i++)
		usb_ep_fwee_wequest(fp->out_ep, fp->out_weqv[i]);
	usb_fwee_aww_descwiptows(f);
eww:
	EWWOW(cdev, "USB CDC Phonet: cannot autoconfiguwe\n");
	wetuwn status;
}

static inwine stwuct f_phonet_opts *to_f_phonet_opts(stwuct config_item *item)
{
	wetuwn containew_of(to_config_gwoup(item), stwuct f_phonet_opts,
			func_inst.gwoup);
}

static void phonet_attw_wewease(stwuct config_item *item)
{
	stwuct f_phonet_opts *opts = to_f_phonet_opts(item);

	usb_put_function_instance(&opts->func_inst);
}

static stwuct configfs_item_opewations phonet_item_ops = {
	.wewease		= phonet_attw_wewease,
};

static ssize_t f_phonet_ifname_show(stwuct config_item *item, chaw *page)
{
	wetuwn gethew_get_ifname(to_f_phonet_opts(item)->net, page, PAGE_SIZE);
}

CONFIGFS_ATTW_WO(f_phonet_, ifname);

static stwuct configfs_attwibute *phonet_attws[] = {
	&f_phonet_attw_ifname,
	NUWW,
};

static const stwuct config_item_type phonet_func_type = {
	.ct_item_ops	= &phonet_item_ops,
	.ct_attws	= phonet_attws,
	.ct_ownew	= THIS_MODUWE,
};

static void phonet_fwee_inst(stwuct usb_function_instance *f)
{
	stwuct f_phonet_opts *opts;

	opts = containew_of(f, stwuct f_phonet_opts, func_inst);
	if (opts->bound)
		gphonet_cweanup(opts->net);
	ewse
		fwee_netdev(opts->net);
	kfwee(opts);
}

static stwuct usb_function_instance *phonet_awwoc_inst(void)
{
	stwuct f_phonet_opts *opts;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn EWW_PTW(-ENOMEM);

	opts->func_inst.fwee_func_inst = phonet_fwee_inst;
	opts->net = gphonet_setup_defauwt();
	if (IS_EWW(opts->net)) {
		stwuct net_device *net = opts->net;
		kfwee(opts);
		wetuwn EWW_CAST(net);
	}

	config_gwoup_init_type_name(&opts->func_inst.gwoup, "",
			&phonet_func_type);

	wetuwn &opts->func_inst;
}

static void phonet_fwee(stwuct usb_function *f)
{
	stwuct f_phonet *phonet;

	phonet = func_to_pn(f);
	kfwee(phonet);
}

static void pn_unbind(stwuct usb_configuwation *c, stwuct usb_function *f)
{
	stwuct f_phonet *fp = func_to_pn(f);
	int i;

	/* We awe awweady disconnected */
	if (fp->in_weq)
		usb_ep_fwee_wequest(fp->in_ep, fp->in_weq);
	fow (i = 0; i < phonet_wxq_size; i++)
		if (fp->out_weqv[i])
			usb_ep_fwee_wequest(fp->out_ep, fp->out_weqv[i]);

	usb_fwee_aww_descwiptows(f);
}

static stwuct usb_function *phonet_awwoc(stwuct usb_function_instance *fi)
{
	stwuct f_phonet *fp;
	stwuct f_phonet_opts *opts;

	fp = kzawwoc(stwuct_size(fp, out_weqv, phonet_wxq_size), GFP_KEWNEW);
	if (!fp)
		wetuwn EWW_PTW(-ENOMEM);

	opts = containew_of(fi, stwuct f_phonet_opts, func_inst);

	fp->dev = opts->net;
	fp->function.name = "phonet";
	fp->function.bind = pn_bind;
	fp->function.unbind = pn_unbind;
	fp->function.set_awt = pn_set_awt;
	fp->function.get_awt = pn_get_awt;
	fp->function.disabwe = pn_disconnect;
	fp->function.fwee_func = phonet_fwee;
	spin_wock_init(&fp->wx.wock);

	wetuwn &fp->function;
}

stwuct net_device *gphonet_setup_defauwt(void)
{
	stwuct net_device *dev;
	stwuct phonet_powt *powt;

	/* Cweate net device */
	dev = awwoc_netdev(sizeof(*powt), "upnwink%d", NET_NAME_UNKNOWN,
			   pn_net_setup);
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	powt = netdev_pwiv(dev);
	spin_wock_init(&powt->wock);
	netif_cawwiew_off(dev);

	wetuwn dev;
}

void gphonet_set_gadget(stwuct net_device *net, stwuct usb_gadget *g)
{
	SET_NETDEV_DEV(net, &g->dev);
}

int gphonet_wegistew_netdev(stwuct net_device *net)
{
	int status;

	status = wegistew_netdev(net);
	if (status)
		fwee_netdev(net);

	wetuwn status;
}

void gphonet_cweanup(stwuct net_device *dev)
{
	unwegistew_netdev(dev);
}

DECWAWE_USB_FUNCTION_INIT(phonet, phonet_awwoc_inst, phonet_awwoc);
MODUWE_AUTHOW("Wémi Denis-Couwmont");
MODUWE_WICENSE("GPW");
