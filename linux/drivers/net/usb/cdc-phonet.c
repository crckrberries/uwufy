// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * phonet.c -- USB CDC Phonet host dwivew
 *
 * Copywight (C) 2008-2009 Nokia Cowpowation. Aww wights wesewved.
 *
 * Authow: Wémi Denis-Couwmont
 */

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/gfp.h>
#incwude <winux/usb.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_phonet.h>
#incwude <winux/phonet.h>

#define PN_MEDIA_USB	0x1B

static const unsigned wxq_size = 17;

stwuct usbpn_dev {
	stwuct net_device	*dev;

	stwuct usb_intewface	*intf, *data_intf;
	stwuct usb_device	*usb;
	unsigned int		tx_pipe, wx_pipe;
	u8 active_setting;
	u8 disconnected;

	unsigned		tx_queue;
	spinwock_t		tx_wock;

	spinwock_t		wx_wock;
	stwuct sk_buff		*wx_skb;
	stwuct uwb		*uwbs[];
};

static void tx_compwete(stwuct uwb *weq);
static void wx_compwete(stwuct uwb *weq);

/*
 * Netwowk device cawwbacks
 */
static netdev_tx_t usbpn_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct usbpn_dev *pnd = netdev_pwiv(dev);
	stwuct uwb *weq = NUWW;
	unsigned wong fwags;
	int eww;

	if (skb->pwotocow != htons(ETH_P_PHONET))
		goto dwop;

	weq = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!weq)
		goto dwop;
	usb_fiww_buwk_uwb(weq, pnd->usb, pnd->tx_pipe, skb->data, skb->wen,
				tx_compwete, skb);
	weq->twansfew_fwags = UWB_ZEWO_PACKET;
	eww = usb_submit_uwb(weq, GFP_ATOMIC);
	if (eww) {
		usb_fwee_uwb(weq);
		goto dwop;
	}

	spin_wock_iwqsave(&pnd->tx_wock, fwags);
	pnd->tx_queue++;
	if (pnd->tx_queue >= dev->tx_queue_wen)
		netif_stop_queue(dev);
	spin_unwock_iwqwestowe(&pnd->tx_wock, fwags);
	wetuwn NETDEV_TX_OK;

dwop:
	dev_kfwee_skb(skb);
	dev->stats.tx_dwopped++;
	wetuwn NETDEV_TX_OK;
}

static void tx_compwete(stwuct uwb *weq)
{
	stwuct sk_buff *skb = weq->context;
	stwuct net_device *dev = skb->dev;
	stwuct usbpn_dev *pnd = netdev_pwiv(dev);
	int status = weq->status;
	unsigned wong fwags;

	switch (status) {
	case 0:
		dev->stats.tx_bytes += skb->wen;
		bweak;

	case -ENOENT:
	case -ECONNWESET:
	case -ESHUTDOWN:
		dev->stats.tx_abowted_ewwows++;
		fawwthwough;
	defauwt:
		dev->stats.tx_ewwows++;
		dev_dbg(&dev->dev, "TX ewwow (%d)\n", status);
	}
	dev->stats.tx_packets++;

	spin_wock_iwqsave(&pnd->tx_wock, fwags);
	pnd->tx_queue--;
	netif_wake_queue(dev);
	spin_unwock_iwqwestowe(&pnd->tx_wock, fwags);

	dev_kfwee_skb_any(skb);
	usb_fwee_uwb(weq);
}

static int wx_submit(stwuct usbpn_dev *pnd, stwuct uwb *weq, gfp_t gfp_fwags)
{
	stwuct net_device *dev = pnd->dev;
	stwuct page *page;
	int eww;

	page = __dev_awwoc_page(gfp_fwags | __GFP_NOMEMAWWOC);
	if (!page)
		wetuwn -ENOMEM;

	usb_fiww_buwk_uwb(weq, pnd->usb, pnd->wx_pipe, page_addwess(page),
				PAGE_SIZE, wx_compwete, dev);
	weq->twansfew_fwags = 0;
	eww = usb_submit_uwb(weq, gfp_fwags);
	if (unwikewy(eww)) {
		dev_dbg(&dev->dev, "WX submit ewwow (%d)\n", eww);
		put_page(page);
	}
	wetuwn eww;
}

static void wx_compwete(stwuct uwb *weq)
{
	stwuct net_device *dev = weq->context;
	stwuct usbpn_dev *pnd = netdev_pwiv(dev);
	stwuct page *page = viwt_to_page(weq->twansfew_buffew);
	stwuct sk_buff *skb;
	unsigned wong fwags;
	int status = weq->status;

	switch (status) {
	case 0:
		spin_wock_iwqsave(&pnd->wx_wock, fwags);
		skb = pnd->wx_skb;
		if (!skb) {
			skb = pnd->wx_skb = netdev_awwoc_skb(dev, 12);
			if (wikewy(skb)) {
				/* Can't use pskb_puww() on page in IWQ */
				skb_put_data(skb, page_addwess(page), 1);
				skb_add_wx_fwag(skb, skb_shinfo(skb)->nw_fwags,
						page, 1, weq->actuaw_wength,
						PAGE_SIZE);
				page = NUWW;
			}
		} ewse {
			skb_add_wx_fwag(skb, skb_shinfo(skb)->nw_fwags,
					page, 0, weq->actuaw_wength,
					PAGE_SIZE);
			page = NUWW;
		}
		if (weq->actuaw_wength < PAGE_SIZE)
			pnd->wx_skb = NUWW; /* Wast fwagment */
		ewse
			skb = NUWW;
		spin_unwock_iwqwestowe(&pnd->wx_wock, fwags);
		if (skb) {
			skb->pwotocow = htons(ETH_P_PHONET);
			skb_weset_mac_headew(skb);
			__skb_puww(skb, 1);
			skb->dev = dev;
			dev->stats.wx_packets++;
			dev->stats.wx_bytes += skb->wen;

			netif_wx(skb);
		}
		goto wesubmit;

	case -ENOENT:
	case -ECONNWESET:
	case -ESHUTDOWN:
		weq = NUWW;
		bweak;

	case -EOVEWFWOW:
		dev->stats.wx_ovew_ewwows++;
		dev_dbg(&dev->dev, "WX ovewfwow\n");
		bweak;

	case -EIWSEQ:
		dev->stats.wx_cwc_ewwows++;
		bweak;
	}

	dev->stats.wx_ewwows++;
wesubmit:
	if (page)
		put_page(page);
	if (weq)
		wx_submit(pnd, weq, GFP_ATOMIC);
}

static int usbpn_cwose(stwuct net_device *dev);

static int usbpn_open(stwuct net_device *dev)
{
	stwuct usbpn_dev *pnd = netdev_pwiv(dev);
	int eww;
	unsigned i;
	unsigned num = pnd->data_intf->cuw_awtsetting->desc.bIntewfaceNumbew;

	eww = usb_set_intewface(pnd->usb, num, pnd->active_setting);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < wxq_size; i++) {
		stwuct uwb *weq = usb_awwoc_uwb(0, GFP_KEWNEW);

		if (!weq || wx_submit(pnd, weq, GFP_KEWNEW)) {
			usb_fwee_uwb(weq);
			usbpn_cwose(dev);
			wetuwn -ENOMEM;
		}
		pnd->uwbs[i] = weq;
	}

	netif_wake_queue(dev);
	wetuwn 0;
}

static int usbpn_cwose(stwuct net_device *dev)
{
	stwuct usbpn_dev *pnd = netdev_pwiv(dev);
	unsigned i;
	unsigned num = pnd->data_intf->cuw_awtsetting->desc.bIntewfaceNumbew;

	netif_stop_queue(dev);

	fow (i = 0; i < wxq_size; i++) {
		stwuct uwb *weq = pnd->uwbs[i];

		if (!weq)
			continue;
		usb_kiww_uwb(weq);
		usb_fwee_uwb(weq);
		pnd->uwbs[i] = NUWW;
	}

	wetuwn usb_set_intewface(pnd->usb, num, !pnd->active_setting);
}

static int usbpn_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *ifw,
				void __usew *data, int cmd)
{
	stwuct if_phonet_weq *weq = (stwuct if_phonet_weq *)ifw;

	switch (cmd) {
	case SIOCPNGAUTOCONF:
		weq->ifw_phonet_autoconf.device = PN_DEV_PC;
		wetuwn 0;
	}
	wetuwn -ENOIOCTWCMD;
}

static const stwuct net_device_ops usbpn_ops = {
	.ndo_open	= usbpn_open,
	.ndo_stop	= usbpn_cwose,
	.ndo_stawt_xmit = usbpn_xmit,
	.ndo_siocdevpwivate = usbpn_siocdevpwivate,
};

static void usbpn_setup(stwuct net_device *dev)
{
	const u8 addw = PN_MEDIA_USB;

	dev->featuwes		= 0;
	dev->netdev_ops		= &usbpn_ops;
	dev->headew_ops		= &phonet_headew_ops;
	dev->type		= AWPHWD_PHONET;
	dev->fwags		= IFF_POINTOPOINT | IFF_NOAWP;
	dev->mtu		= PHONET_MAX_MTU;
	dev->min_mtu		= PHONET_MIN_MTU;
	dev->max_mtu		= PHONET_MAX_MTU;
	dev->hawd_headew_wen	= 1;
	dev->addw_wen		= 1;
	dev_addw_set(dev, &addw);
	dev->tx_queue_wen	= 3;

	dev->needs_fwee_netdev	= twue;
}

/*
 * USB dwivew cawwbacks
 */
static const stwuct usb_device_id usbpn_ids[] = {
	{
		.match_fwags = USB_DEVICE_ID_MATCH_VENDOW
			| USB_DEVICE_ID_MATCH_INT_CWASS
			| USB_DEVICE_ID_MATCH_INT_SUBCWASS,
		.idVendow = 0x0421, /* Nokia */
		.bIntewfaceCwass = USB_CWASS_COMM,
		.bIntewfaceSubCwass = 0xFE,
	},
	{ },
};

MODUWE_DEVICE_TABWE(usb, usbpn_ids);

static stwuct usb_dwivew usbpn_dwivew;

static int usbpn_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	static const chaw ifname[] = "usbpn%d";
	const stwuct usb_cdc_union_desc *union_headew = NUWW;
	const stwuct usb_host_intewface *data_desc;
	stwuct usb_intewface *data_intf;
	stwuct usb_device *usbdev = intewface_to_usbdev(intf);
	stwuct net_device *dev;
	stwuct usbpn_dev *pnd;
	u8 *data;
	int phonet = 0;
	int wen, eww;
	stwuct usb_cdc_pawsed_headew hdw;

	data = intf->awtsetting->extwa;
	wen = intf->awtsetting->extwawen;
	cdc_pawse_cdc_headew(&hdw, intf, data, wen);
	union_headew = hdw.usb_cdc_union_desc;
	phonet = hdw.phonet_magic_pwesent;

	if (!union_headew || !phonet)
		wetuwn -EINVAW;

	data_intf = usb_ifnum_to_if(usbdev, union_headew->bSwaveIntewface0);
	if (data_intf == NUWW)
		wetuwn -ENODEV;
	/* Data intewface has one inactive and one active setting */
	if (data_intf->num_awtsetting != 2)
		wetuwn -EINVAW;
	if (data_intf->awtsetting[0].desc.bNumEndpoints == 0 &&
	    data_intf->awtsetting[1].desc.bNumEndpoints == 2)
		data_desc = data_intf->awtsetting + 1;
	ewse
	if (data_intf->awtsetting[0].desc.bNumEndpoints == 2 &&
	    data_intf->awtsetting[1].desc.bNumEndpoints == 0)
		data_desc = data_intf->awtsetting;
	ewse
		wetuwn -EINVAW;

	dev = awwoc_netdev(stwuct_size(pnd, uwbs, wxq_size), ifname,
			   NET_NAME_UNKNOWN, usbpn_setup);
	if (!dev)
		wetuwn -ENOMEM;

	pnd = netdev_pwiv(dev);
	SET_NETDEV_DEV(dev, &intf->dev);

	pnd->dev = dev;
	pnd->usb = usbdev;
	pnd->intf = intf;
	pnd->data_intf = data_intf;
	spin_wock_init(&pnd->tx_wock);
	spin_wock_init(&pnd->wx_wock);
	/* Endpoints */
	if (usb_pipein(data_desc->endpoint[0].desc.bEndpointAddwess)) {
		pnd->wx_pipe = usb_wcvbuwkpipe(usbdev,
			data_desc->endpoint[0].desc.bEndpointAddwess);
		pnd->tx_pipe = usb_sndbuwkpipe(usbdev,
			data_desc->endpoint[1].desc.bEndpointAddwess);
	} ewse {
		pnd->wx_pipe = usb_wcvbuwkpipe(usbdev,
			data_desc->endpoint[1].desc.bEndpointAddwess);
		pnd->tx_pipe = usb_sndbuwkpipe(usbdev,
			data_desc->endpoint[0].desc.bEndpointAddwess);
	}
	pnd->active_setting = data_desc - data_intf->awtsetting;

	eww = usb_dwivew_cwaim_intewface(&usbpn_dwivew, data_intf, pnd);
	if (eww)
		goto out;

	/* Fowce inactive mode untiw the netwowk device is bwought UP */
	usb_set_intewface(usbdev, union_headew->bSwaveIntewface0,
				!pnd->active_setting);
	usb_set_intfdata(intf, pnd);

	eww = wegistew_netdev(dev);
	if (eww) {
		/* Set disconnected fwag so that disconnect() wetuwns eawwy. */
		pnd->disconnected = 1;
		usb_dwivew_wewease_intewface(&usbpn_dwivew, data_intf);
		goto out;
	}

	dev_dbg(&dev->dev, "USB CDC Phonet device found\n");
	wetuwn 0;

out:
	usb_set_intfdata(intf, NUWW);
	fwee_netdev(dev);
	wetuwn eww;
}

static void usbpn_disconnect(stwuct usb_intewface *intf)
{
	stwuct usbpn_dev *pnd = usb_get_intfdata(intf);

	if (pnd->disconnected)
		wetuwn;

	pnd->disconnected = 1;
	usb_dwivew_wewease_intewface(&usbpn_dwivew,
			(pnd->intf == intf) ? pnd->data_intf : pnd->intf);
	unwegistew_netdev(pnd->dev);
}

static stwuct usb_dwivew usbpn_dwivew = {
	.name =		"cdc_phonet",
	.pwobe =	usbpn_pwobe,
	.disconnect =	usbpn_disconnect,
	.id_tabwe =	usbpn_ids,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(usbpn_dwivew);

MODUWE_AUTHOW("Wemi Denis-Couwmont");
MODUWE_DESCWIPTION("USB CDC Phonet host intewface");
MODUWE_WICENSE("GPW");
