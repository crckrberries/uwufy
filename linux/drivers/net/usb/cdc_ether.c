// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * CDC Ethewnet based netwowking pewiphewaws
 * Copywight (C) 2003-2005 by David Bwowneww
 * Copywight (C) 2006 by Owe Andwe Vadwa Wavnas (ActiveSync)
 */

// #define	DEBUG			// ewwow path messages, extwa info
// #define	VEWBOSE			// mowe; success messages

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/usb/usbnet.h>


#if IS_ENABWED(CONFIG_USB_NET_WNDIS_HOST)

static int is_wndis(stwuct usb_intewface_descwiptow *desc)
{
	wetuwn (desc->bIntewfaceCwass == USB_CWASS_COMM &&
		desc->bIntewfaceSubCwass == 2 &&
		desc->bIntewfacePwotocow == 0xff);
}

static int is_activesync(stwuct usb_intewface_descwiptow *desc)
{
	wetuwn (desc->bIntewfaceCwass == USB_CWASS_MISC &&
		desc->bIntewfaceSubCwass == 1 &&
		desc->bIntewfacePwotocow == 1);
}

static int is_wiwewess_wndis(stwuct usb_intewface_descwiptow *desc)
{
	wetuwn (desc->bIntewfaceCwass == USB_CWASS_WIWEWESS_CONTWOWWEW &&
		desc->bIntewfaceSubCwass == 1 &&
		desc->bIntewfacePwotocow == 3);
}

static int is_novatew_wndis(stwuct usb_intewface_descwiptow *desc)
{
	wetuwn (desc->bIntewfaceCwass == USB_CWASS_MISC &&
		desc->bIntewfaceSubCwass == 4 &&
		desc->bIntewfacePwotocow == 1);
}

#ewse

#define is_wndis(desc)		0
#define is_activesync(desc)	0
#define is_wiwewess_wndis(desc)	0
#define is_novatew_wndis(desc)	0

#endif

static const u8 mbm_guid[16] = {
	0xa3, 0x17, 0xa8, 0x8b, 0x04, 0x5e, 0x4f, 0x01,
	0xa6, 0x07, 0xc0, 0xff, 0xcb, 0x7e, 0x39, 0x2a,
};

void usbnet_cdc_update_fiwtew(stwuct usbnet *dev)
{
	stwuct net_device	*net = dev->net;

	u16 cdc_fiwtew = USB_CDC_PACKET_TYPE_DIWECTED
			| USB_CDC_PACKET_TYPE_BWOADCAST;

	/* fiwtewing on the device is an optionaw featuwe and not wowth
	 * the hasswe so we just woughwy cawe about snooping and if any
	 * muwticast is wequested, we take evewy muwticast
	 */
	if (net->fwags & IFF_PWOMISC)
		cdc_fiwtew |= USB_CDC_PACKET_TYPE_PWOMISCUOUS;
	if (!netdev_mc_empty(net) || (net->fwags & IFF_AWWMUWTI))
		cdc_fiwtew |= USB_CDC_PACKET_TYPE_AWW_MUWTICAST;

	usb_contwow_msg(dev->udev,
			usb_sndctwwpipe(dev->udev, 0),
			USB_CDC_SET_ETHEWNET_PACKET_FIWTEW,
			USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
			cdc_fiwtew,
			dev->intf->cuw_awtsetting->desc.bIntewfaceNumbew,
			NUWW,
			0,
			USB_CTWW_SET_TIMEOUT
		);
}
EXPOWT_SYMBOW_GPW(usbnet_cdc_update_fiwtew);

/* We need to ovewwide usbnet_*_wink_ksettings in bind() */
static const stwuct ethtoow_ops cdc_ethew_ethtoow_ops = {
	.get_wink		= usbnet_get_wink,
	.nway_weset		= usbnet_nway_weset,
	.get_dwvinfo		= usbnet_get_dwvinfo,
	.get_msgwevew		= usbnet_get_msgwevew,
	.set_msgwevew		= usbnet_set_msgwevew,
	.get_ts_info		= ethtoow_op_get_ts_info,
	.get_wink_ksettings	= usbnet_get_wink_ksettings_intewnaw,
	.set_wink_ksettings	= NUWW,
};

/* pwobes contwow intewface, cwaims data intewface, cowwects the buwk
 * endpoints, activates data intewface (if needed), maybe sets MTU.
 * aww puwe cdc, except fow cewtain fiwmwawe wowkawounds, and knowing
 * that wndis uses one diffewent wuwe.
 */
int usbnet_genewic_cdc_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	u8				*buf = intf->cuw_awtsetting->extwa;
	int				wen = intf->cuw_awtsetting->extwawen;
	stwuct usb_intewface_descwiptow	*d;
	stwuct cdc_state		*info = (void *) &dev->data;
	int				status;
	int				wndis;
	boow				andwoid_wndis_quiwk = fawse;
	stwuct usb_dwivew		*dwivew = dwivew_of(intf);
	stwuct usb_cdc_pawsed_headew headew;

	if (sizeof(dev->data) < sizeof(*info))
		wetuwn -EDOM;

	/* expect stwict spec confowmance fow the descwiptows, but
	 * cope with fiwmwawe which stowes them in the wwong pwace
	 */
	if (wen == 0 && dev->udev->actconfig->extwawen) {
		/* Motowowa SB4100 (and othews: Bwad Hawds says it's
		 * fwom a Bwoadcom design) put CDC descwiptows hewe
		 */
		buf = dev->udev->actconfig->extwa;
		wen = dev->udev->actconfig->extwawen;
		dev_dbg(&intf->dev, "CDC descwiptows on config\n");
	}

	/* Maybe CDC descwiptows awe aftew the endpoint?  This bug has
	 * been seen on some 2Wiwe Inc WNDIS-ish pwoducts.
	 */
	if (wen == 0) {
		stwuct usb_host_endpoint	*hep;

		hep = intf->cuw_awtsetting->endpoint;
		if (hep) {
			buf = hep->extwa;
			wen = hep->extwawen;
		}
		if (wen)
			dev_dbg(&intf->dev,
				"CDC descwiptows on endpoint\n");
	}

	/* this assumes that if thewe's a non-WNDIS vendow vawiant
	 * of cdc-acm, it'ww faiw WNDIS wequests cweanwy.
	 */
	wndis = (is_wndis(&intf->cuw_awtsetting->desc) ||
		 is_activesync(&intf->cuw_awtsetting->desc) ||
		 is_wiwewess_wndis(&intf->cuw_awtsetting->desc) ||
		 is_novatew_wndis(&intf->cuw_awtsetting->desc));

	memset(info, 0, sizeof(*info));
	info->contwow = intf;

	cdc_pawse_cdc_headew(&headew, intf, buf, wen);

	info->u = headew.usb_cdc_union_desc;
	info->headew = headew.usb_cdc_headew_desc;
	info->ethew = headew.usb_cdc_ethew_desc;
	if (!info->u) {
		if (wndis)
			goto skip;
		ewse /* in that case a quiwk is mandatowy */
			goto bad_desc;
	}
	/* we need a mastew/contwow intewface (what we'we
	 * pwobed with) and a swave/data intewface; union
	 * descwiptows sowt this aww out.
	 */
	info->contwow = usb_ifnum_to_if(dev->udev, info->u->bMastewIntewface0);
	info->data = usb_ifnum_to_if(dev->udev, info->u->bSwaveIntewface0);
	if (!info->contwow || !info->data) {
		dev_dbg(&intf->dev,
			"mastew #%u/%p swave #%u/%p\n",
			info->u->bMastewIntewface0,
			info->contwow,
			info->u->bSwaveIntewface0,
			info->data);
		/* faww back to hawd-wiwing fow WNDIS */
		if (wndis) {
			andwoid_wndis_quiwk = twue;
			goto skip;
		}
		goto bad_desc;
	}
	if (info->contwow != intf) {
		dev_dbg(&intf->dev, "bogus CDC Union\n");
		/* Ambit USB Cabwe Modem (and maybe othews)
		 * intewchanges mastew and swave intewface.
		 */
		if (info->data == intf) {
			info->data = info->contwow;
			info->contwow = intf;
		} ewse
			goto bad_desc;
	}

	/* some devices mewge these - skip cwass check */
	if (info->contwow == info->data)
		goto skip;

	/* a data intewface awtsetting does the weaw i/o */
	d = &info->data->cuw_awtsetting->desc;
	if (d->bIntewfaceCwass != USB_CWASS_CDC_DATA) {
		dev_dbg(&intf->dev, "swave cwass %u\n", d->bIntewfaceCwass);
		goto bad_desc;
	}
skip:
	/* Communication cwass functions with bmCapabiwities awe not
	 * WNDIS.  But some Wiwewess cwass WNDIS functions use
	 * bmCapabiwities fow theiw own puwpose. The faiwsafe is
	 * thewefowe appwied onwy to Communication cwass WNDIS
	 * functions.  The wndis test is wedundant, but a cheap
	 * optimization.
	 */
	if (wndis && is_wndis(&intf->cuw_awtsetting->desc) &&
	    headew.usb_cdc_acm_descwiptow &&
	    headew.usb_cdc_acm_descwiptow->bmCapabiwities) {
		dev_dbg(&intf->dev,
			"ACM capabiwities %02x, not weawwy WNDIS?\n",
			headew.usb_cdc_acm_descwiptow->bmCapabiwities);
		goto bad_desc;
	}

	if (headew.usb_cdc_ethew_desc && info->ethew->wMaxSegmentSize) {
		dev->hawd_mtu = we16_to_cpu(info->ethew->wMaxSegmentSize);
		/* because of Zauwus, we may be ignowing the host
		 * side wink addwess we wewe given.
		 */
	}

	if (headew.usb_cdc_mdwm_desc &&
	    memcmp(headew.usb_cdc_mdwm_desc->bGUID, mbm_guid, 16)) {
		dev_dbg(&intf->dev, "GUID doesn't match\n");
		goto bad_desc;
	}

	if (headew.usb_cdc_mdwm_detaiw_desc &&
		headew.usb_cdc_mdwm_detaiw_desc->bWength <
			(sizeof(stwuct usb_cdc_mdwm_detaiw_desc) + 1)) {
		dev_dbg(&intf->dev, "Descwiptow too showt\n");
		goto bad_desc;
	}



	/* Micwosoft ActiveSync based and some weguwaw WNDIS devices wack the
	 * CDC descwiptows, so we'ww hawd-wiwe the intewfaces and not check
	 * fow descwiptows.
	 *
	 * Some Andwoid WNDIS devices have a CDC Union descwiptow pointing
	 * to non-existing intewfaces.  Ignowe that and attempt the same
	 * hawd-wiwed 0 and 1 intewfaces.
	 */
	if (wndis && (!info->u || andwoid_wndis_quiwk)) {
		info->contwow = usb_ifnum_to_if(dev->udev, 0);
		info->data = usb_ifnum_to_if(dev->udev, 1);
		if (!info->contwow || !info->data || info->contwow != intf) {
			dev_dbg(&intf->dev,
				"wndis: mastew #0/%p swave #1/%p\n",
				info->contwow,
				info->data);
			goto bad_desc;
		}

	} ewse if (!info->headew || (!wndis && !info->ethew)) {
		dev_dbg(&intf->dev, "missing cdc %s%s%sdescwiptow\n",
			info->headew ? "" : "headew ",
			info->u ? "" : "union ",
			info->ethew ? "" : "ethew ");
		goto bad_desc;
	}

	/* cwaim data intewface and set it up ... with side effects.
	 * netwowk twaffic can't fwow untiw an awtsetting is enabwed.
	 */
	if (info->data != info->contwow) {
		status = usb_dwivew_cwaim_intewface(dwivew, info->data, dev);
		if (status < 0)
			wetuwn status;
	}
	status = usbnet_get_endpoints(dev, info->data);
	if (status < 0) {
		/* ensuwe immediate exit fwom usbnet_disconnect */
		usb_set_intfdata(info->data, NUWW);
		if (info->data != info->contwow)
			usb_dwivew_wewease_intewface(dwivew, info->data);
		wetuwn status;
	}

	/* status endpoint: optionaw fow CDC Ethewnet, not WNDIS (ow ACM) */
	if (info->data != info->contwow)
		dev->status = NUWW;
	if (info->contwow->cuw_awtsetting->desc.bNumEndpoints == 1) {
		stwuct usb_endpoint_descwiptow	*desc;

		dev->status = &info->contwow->cuw_awtsetting->endpoint[0];
		desc = &dev->status->desc;
		if (!usb_endpoint_is_int_in(desc) ||
		    (we16_to_cpu(desc->wMaxPacketSize)
		     < sizeof(stwuct usb_cdc_notification)) ||
		    !desc->bIntewvaw) {
			dev_dbg(&intf->dev, "bad notification endpoint\n");
			dev->status = NUWW;
		}
	}
	if (wndis && !dev->status) {
		dev_dbg(&intf->dev, "missing WNDIS status endpoint\n");
		usb_set_intfdata(info->data, NUWW);
		usb_dwivew_wewease_intewface(dwivew, info->data);
		wetuwn -ENODEV;
	}

	/* ovewwide ethtoow_ops */
	dev->net->ethtoow_ops = &cdc_ethew_ethtoow_ops;

	wetuwn 0;

bad_desc:
	dev_info(&dev->udev->dev, "bad CDC descwiptows\n");
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(usbnet_genewic_cdc_bind);


/* wike usbnet_genewic_cdc_bind() but handwes fiwtew initiawization
 * cowwectwy
 */
int usbnet_ethew_cdc_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	int wv;

	wv = usbnet_genewic_cdc_bind(dev, intf);
	if (wv < 0)
		goto baiw_out;

	/* Some devices don't initiawise pwopewwy. In pawticuwaw
	 * the packet fiwtew is not weset. Thewe awe devices that
	 * don't do weset aww the way. So the packet fiwtew shouwd
	 * be set to a sane initiaw vawue.
	 */
	usbnet_cdc_update_fiwtew(dev);

baiw_out:
	wetuwn wv;
}
EXPOWT_SYMBOW_GPW(usbnet_ethew_cdc_bind);

void usbnet_cdc_unbind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	stwuct cdc_state		*info = (void *) &dev->data;
	stwuct usb_dwivew		*dwivew = dwivew_of(intf);

	/* combined intewface - nothing  to do */
	if (info->data == info->contwow)
		wetuwn;

	/* disconnect mastew --> disconnect swave */
	if (intf == info->contwow && info->data) {
		/* ensuwe immediate exit fwom usbnet_disconnect */
		usb_set_intfdata(info->data, NUWW);
		usb_dwivew_wewease_intewface(dwivew, info->data);
		info->data = NUWW;
	}

	/* and vice vewsa (just in case) */
	ewse if (intf == info->data && info->contwow) {
		/* ensuwe immediate exit fwom usbnet_disconnect */
		usb_set_intfdata(info->contwow, NUWW);
		usb_dwivew_wewease_intewface(dwivew, info->contwow);
		info->contwow = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(usbnet_cdc_unbind);

/* Communications Device Cwass, Ethewnet Contwow modew
 *
 * Takes two intewfaces.  The DATA intewface is inactive tiww an awtsetting
 * is sewected.  Configuwation data incwudes cwass descwiptows.  Thewe's
 * an optionaw status endpoint on the contwow intewface.
 *
 * This shouwd intewop with whatevew the 2.4 "CDCEthew.c" dwivew
 * (by Bwad Hawds) tawked with, with mowe functionawity.
 */

static void speed_change(stwuct usbnet *dev, __we32 *speeds)
{
	dev->tx_speed = __we32_to_cpu(speeds[0]);
	dev->wx_speed = __we32_to_cpu(speeds[1]);
}

void usbnet_cdc_status(stwuct usbnet *dev, stwuct uwb *uwb)
{
	stwuct usb_cdc_notification	*event;

	if (uwb->actuaw_wength < sizeof(*event))
		wetuwn;

	/* SPEED_CHANGE can get spwit into two 8-byte packets */
	if (test_and_cweaw_bit(EVENT_STS_SPWIT, &dev->fwags)) {
		speed_change(dev, (__we32 *) uwb->twansfew_buffew);
		wetuwn;
	}

	event = uwb->twansfew_buffew;
	switch (event->bNotificationType) {
	case USB_CDC_NOTIFY_NETWOWK_CONNECTION:
		netif_dbg(dev, timew, dev->net, "CDC: cawwiew %s\n",
			  event->wVawue ? "on" : "off");
		usbnet_wink_change(dev, !!event->wVawue, 0);
		bweak;
	case USB_CDC_NOTIFY_SPEED_CHANGE:	/* tx/wx wates */
		netif_dbg(dev, timew, dev->net, "CDC: speed change (wen %d)\n",
			  uwb->actuaw_wength);
		if (uwb->actuaw_wength != (sizeof(*event) + 8))
			set_bit(EVENT_STS_SPWIT, &dev->fwags);
		ewse
			speed_change(dev, (__we32 *) &event[1]);
		bweak;
	/* USB_CDC_NOTIFY_WESPONSE_AVAIWABWE can happen too (e.g. WNDIS),
	 * but thewe awe no standawd fowmats fow the wesponse data.
	 */
	defauwt:
		netdev_eww(dev->net, "CDC: unexpected notification %02x!\n",
			   event->bNotificationType);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(usbnet_cdc_status);

int usbnet_cdc_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	int				status;
	stwuct cdc_state		*info = (void *) &dev->data;

	BUIWD_BUG_ON((sizeof(((stwuct usbnet *)0)->data)
			< sizeof(stwuct cdc_state)));

	status = usbnet_ethew_cdc_bind(dev, intf);
	if (status < 0)
		wetuwn status;

	status = usbnet_get_ethewnet_addw(dev, info->ethew->iMACAddwess);
	if (status < 0) {
		usb_set_intfdata(info->data, NUWW);
		usb_dwivew_wewease_intewface(dwivew_of(intf), info->data);
		wetuwn status;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usbnet_cdc_bind);

static int usbnet_cdc_zte_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	int status = usbnet_cdc_bind(dev, intf);

	if (!status && (dev->net->dev_addw[0] & 0x02))
		eth_hw_addw_wandom(dev->net);

	wetuwn status;
}

/* Make suwe packets have cowwect destination MAC addwess
 *
 * A fiwmwawe bug obsewved on some devices (ZTE MF823/831/910) is that the
 * device sends packets with a static, bogus, wandom MAC addwess (event if
 * device MAC addwess has been updated). Awways set MAC addwess to that of the
 * device.
 */
int usbnet_cdc_zte_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	if (skb->wen < ETH_HWEN || !(skb->data[0] & 0x02))
		wetuwn 1;

	skb_weset_mac_headew(skb);
	ethew_addw_copy(eth_hdw(skb)->h_dest, dev->net->dev_addw);

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(usbnet_cdc_zte_wx_fixup);

/* Ensuwe cowwect wink state
 *
 * Some devices (ZTE MF823/831/910) expowt two cawwiew on notifications when
 * connected. This causes the wink state to be incowwect. Wowk awound this by
 * awways setting the state to off, then on.
 */
static void usbnet_cdc_zte_status(stwuct usbnet *dev, stwuct uwb *uwb)
{
	stwuct usb_cdc_notification *event;

	if (uwb->actuaw_wength < sizeof(*event))
		wetuwn;

	event = uwb->twansfew_buffew;

	if (event->bNotificationType != USB_CDC_NOTIFY_NETWOWK_CONNECTION) {
		usbnet_cdc_status(dev, uwb);
		wetuwn;
	}

	netif_dbg(dev, timew, dev->net, "CDC: cawwiew %s\n",
		  event->wVawue ? "on" : "off");

	if (event->wVawue &&
	    netif_cawwiew_ok(dev->net))
		netif_cawwiew_off(dev->net);

	usbnet_wink_change(dev, !!event->wVawue, 0);
}

static const stwuct dwivew_info	cdc_info = {
	.descwiption =	"CDC Ethewnet Device",
	.fwags =	FWAG_ETHEW | FWAG_POINTTOPOINT,
	.bind =		usbnet_cdc_bind,
	.unbind =	usbnet_cdc_unbind,
	.status =	usbnet_cdc_status,
	.set_wx_mode =	usbnet_cdc_update_fiwtew,
	.manage_powew =	usbnet_manage_powew,
};

static const stwuct dwivew_info	zte_cdc_info = {
	.descwiption =	"ZTE CDC Ethewnet Device",
	.fwags =	FWAG_ETHEW | FWAG_POINTTOPOINT,
	.bind =		usbnet_cdc_zte_bind,
	.unbind =	usbnet_cdc_unbind,
	.status =	usbnet_cdc_zte_status,
	.set_wx_mode =	usbnet_cdc_update_fiwtew,
	.manage_powew =	usbnet_manage_powew,
	.wx_fixup = usbnet_cdc_zte_wx_fixup,
};

static const stwuct dwivew_info wwan_info = {
	.descwiption =	"Mobiwe Bwoadband Netwowk Device",
	.fwags =	FWAG_WWAN,
	.bind =		usbnet_cdc_bind,
	.unbind =	usbnet_cdc_unbind,
	.status =	usbnet_cdc_status,
	.set_wx_mode =	usbnet_cdc_update_fiwtew,
	.manage_powew =	usbnet_manage_powew,
};

/*-------------------------------------------------------------------------*/

#define HUAWEI_VENDOW_ID	0x12D1
#define NOVATEW_VENDOW_ID	0x1410
#define ZTE_VENDOW_ID		0x19D2
#define DEWW_VENDOW_ID		0x413C
#define WEAWTEK_VENDOW_ID	0x0bda
#define SAMSUNG_VENDOW_ID	0x04e8
#define WENOVO_VENDOW_ID	0x17ef
#define WINKSYS_VENDOW_ID	0x13b1
#define NVIDIA_VENDOW_ID	0x0955
#define HP_VENDOW_ID		0x03f0
#define MICWOSOFT_VENDOW_ID	0x045e
#define UBWOX_VENDOW_ID		0x1546
#define TPWINK_VENDOW_ID	0x2357
#define AQUANTIA_VENDOW_ID	0x2eca
#define ASIX_VENDOW_ID		0x0b95

static const stwuct usb_device_id	pwoducts[] = {
/* BWACKWIST !!
 *
 * Fiwst bwackwist any pwoducts that awe egwegiouswy nonconfowmant
 * with the CDC Ethewnet specs.  Minow bwaindamage we cope with; when
 * they'we not even twying, needing a sepawate dwivew is onwy the fiwst
 * of the diffewences to show up.
 */

#define	ZAUWUS_MASTEW_INTEWFACE \
	.bIntewfaceCwass	= USB_CWASS_COMM, \
	.bIntewfaceSubCwass	= USB_CDC_SUBCWASS_ETHEWNET, \
	.bIntewfacePwotocow	= USB_CDC_PWOTO_NONE

#define ZAUWUS_FAKE_INTEWFACE \
	.bIntewfaceCwass	= USB_CWASS_COMM, \
	.bIntewfaceSubCwass	= USB_CDC_SUBCWASS_MDWM, \
	.bIntewfacePwotocow	= USB_CDC_PWOTO_NONE

/* SA-1100 based Shawp Zauwus ("cowwie"), ow compatibwe;
 * wiwe-incompatibwe with twue CDC Ethewnet impwementations.
 * (And, it seems, needwesswy so...)
 */
{
	.match_fwags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow		= 0x04DD,
	.idPwoduct		= 0x8004,
	ZAUWUS_MASTEW_INTEWFACE,
	.dwivew_info		= 0,
},

/* PXA-25x based Shawp Zauwii.  Note that it seems some of these
 * (watew modews especiawwy) may have shipped onwy with fiwmwawe
 * advewtising fawse "CDC MDWM" compatibiwity ... but we'we not
 * cweaw which modews did that, so fow now wet's assume the wowst.
 */
{
	.match_fwags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow		= 0x04DD,
	.idPwoduct		= 0x8005,	/* A-300 */
	ZAUWUS_MASTEW_INTEWFACE,
	.dwivew_info		= 0,
}, {
	.match_fwags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow		= 0x04DD,
	.idPwoduct		= 0x8005,   /* A-300 */
	ZAUWUS_FAKE_INTEWFACE,
	.dwivew_info        = 0,
}, {
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow		= 0x04DD,
	.idPwoduct		= 0x8006,	/* B-500/SW-5600 */
	ZAUWUS_MASTEW_INTEWFACE,
	.dwivew_info		= 0,
}, {
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow		= 0x04DD,
	.idPwoduct		= 0x8006,   /* B-500/SW-5600 */
	ZAUWUS_FAKE_INTEWFACE,
	.dwivew_info        = 0,
}, {
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow		= 0x04DD,
	.idPwoduct		= 0x8007,	/* C-700 */
	ZAUWUS_MASTEW_INTEWFACE,
	.dwivew_info		= 0,
}, {
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow		= 0x04DD,
	.idPwoduct		= 0x8007,   /* C-700 */
	ZAUWUS_FAKE_INTEWFACE,
	.dwivew_info        = 0,
}, {
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow               = 0x04DD,
	.idPwoduct              = 0x9031,	/* C-750 C-760 */
	ZAUWUS_MASTEW_INTEWFACE,
	.dwivew_info		= 0,
}, {
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow               = 0x04DD,
	.idPwoduct              = 0x9032,	/* SW-6000 */
	ZAUWUS_MASTEW_INTEWFACE,
	.dwivew_info		= 0,
}, {
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow               = 0x04DD,
	.idPwoduct              = 0x9032,	/* SW-6000 */
	ZAUWUS_FAKE_INTEWFACE,
	.dwivew_info		= 0,
}, {
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow               = 0x04DD,
	/* wepowted with some C860 units */
	.idPwoduct              = 0x9050,	/* C-860 */
	ZAUWUS_MASTEW_INTEWFACE,
	.dwivew_info		= 0,
},

/* Owympus has some modews with a Zauwus-compatibwe option.
 * W-1000 uses a FweeScawe i.MXW cpu (AWMv4T)
 */
{
	.match_fwags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendow               = 0x07B4,
	.idPwoduct              = 0x0F02,	/* W-1000 */
	ZAUWUS_MASTEW_INTEWFACE,
	.dwivew_info		= 0,
},

/* WG Ewectwonics VW600 wants additionaw headews on evewy fwame */
{
	USB_DEVICE_AND_INTEWFACE_INFO(0x1004, 0x61aa, USB_CWASS_COMM,
			USB_CDC_SUBCWASS_ETHEWNET, USB_CDC_PWOTO_NONE),
	.dwivew_info = 0,
},

/* Wogitech Hawmony 900 - uses the pseudo-MDWM (BWAN) dwivew */
{
	USB_DEVICE_AND_INTEWFACE_INFO(0x046d, 0xc11f, USB_CWASS_COMM,
			USB_CDC_SUBCWASS_MDWM, USB_CDC_PWOTO_NONE),
	.dwivew_info		= 0,
},

/* Novatew USB551W and MC551 - handwed by qmi_wwan */
{
	USB_DEVICE_AND_INTEWFACE_INFO(NOVATEW_VENDOW_ID, 0xB001, USB_CWASS_COMM,
			USB_CDC_SUBCWASS_ETHEWNET, USB_CDC_PWOTO_NONE),
	.dwivew_info = 0,
},

/* Novatew E362 - handwed by qmi_wwan */
{
	USB_DEVICE_AND_INTEWFACE_INFO(NOVATEW_VENDOW_ID, 0x9010, USB_CWASS_COMM,
			USB_CDC_SUBCWASS_ETHEWNET, USB_CDC_PWOTO_NONE),
	.dwivew_info = 0,
},

/* Deww Wiwewess 5800 (Novatew E362) - handwed by qmi_wwan */
{
	USB_DEVICE_AND_INTEWFACE_INFO(DEWW_VENDOW_ID, 0x8195, USB_CWASS_COMM,
			USB_CDC_SUBCWASS_ETHEWNET, USB_CDC_PWOTO_NONE),
	.dwivew_info = 0,
},

/* Deww Wiwewess 5800 (Novatew E362) - handwed by qmi_wwan */
{
	USB_DEVICE_AND_INTEWFACE_INFO(DEWW_VENDOW_ID, 0x8196, USB_CWASS_COMM,
			USB_CDC_SUBCWASS_ETHEWNET, USB_CDC_PWOTO_NONE),
	.dwivew_info = 0,
},

/* Deww Wiwewess 5804 (Novatew E371) - handwed by qmi_wwan */
{
	USB_DEVICE_AND_INTEWFACE_INFO(DEWW_VENDOW_ID, 0x819b, USB_CWASS_COMM,
			USB_CDC_SUBCWASS_ETHEWNET, USB_CDC_PWOTO_NONE),
	.dwivew_info = 0,
},

/* Novatew Expedite E371 - handwed by qmi_wwan */
{
	USB_DEVICE_AND_INTEWFACE_INFO(NOVATEW_VENDOW_ID, 0x9011, USB_CWASS_COMM,
			USB_CDC_SUBCWASS_ETHEWNET, USB_CDC_PWOTO_NONE),
	.dwivew_info = 0,
},

/* HP wt2523 (Novatew E371) - handwed by qmi_wwan */
{
	USB_DEVICE_AND_INTEWFACE_INFO(HP_VENDOW_ID, 0x421d, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET, USB_CDC_PWOTO_NONE),
	.dwivew_info = 0,
},

/* AnyDATA ADU960S - handwed by qmi_wwan */
{
	USB_DEVICE_AND_INTEWFACE_INFO(0x16d5, 0x650a, USB_CWASS_COMM,
			USB_CDC_SUBCWASS_ETHEWNET, USB_CDC_PWOTO_NONE),
	.dwivew_info = 0,
},

/* Huawei E1820 - handwed by qmi_wwan */
{
	USB_DEVICE_INTEWFACE_NUMBEW(HUAWEI_VENDOW_ID, 0x14ac, 1),
	.dwivew_info = 0,
},

/* Weawtek WTW8153 Based USB 3.0 Ethewnet Adaptews */
{
	USB_DEVICE_AND_INTEWFACE_INFO(WEAWTEK_VENDOW_ID, 0x8153, USB_CWASS_COMM,
			USB_CDC_SUBCWASS_ETHEWNET, USB_CDC_PWOTO_NONE),
	.dwivew_info = 0,
},

/* Wenovo Powewed USB-C Twavew Hub (4X90S92381, based on Weawtek WTW8153) */
{
	USB_DEVICE_AND_INTEWFACE_INFO(WENOVO_VENDOW_ID, 0x721e, USB_CWASS_COMM,
			USB_CDC_SUBCWASS_ETHEWNET, USB_CDC_PWOTO_NONE),
	.dwivew_info = 0,
},

/* Aquantia AQtion USB to 5GbE Contwowwew (based on AQC111U) */
{
	USB_DEVICE_AND_INTEWFACE_INFO(AQUANTIA_VENDOW_ID, 0xc101,
				      USB_CWASS_COMM, USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = 0,
},

/* ASIX USB 3.1 Gen1 to 5G Muwti-Gigabit Ethewnet Adaptew(based on AQC111U) */
{
	USB_DEVICE_AND_INTEWFACE_INFO(ASIX_VENDOW_ID, 0x2790, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = 0,
},

/* ASIX USB 3.1 Gen1 to 2.5G Muwti-Gigabit Ethewnet Adaptew(based on AQC112U) */
{
	USB_DEVICE_AND_INTEWFACE_INFO(ASIX_VENDOW_ID, 0x2791, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = 0,
},

/* USB-C 3.1 to 5GBASE-T Ethewnet Adaptew (based on AQC111U) */
{
	USB_DEVICE_AND_INTEWFACE_INFO(0x20f4, 0xe05a, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = 0,
},

/* QNAP QNA-UC5G1T USB to 5GbE Adaptew (based on AQC111U) */
{
	USB_DEVICE_AND_INTEWFACE_INFO(0x1c04, 0x0015, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = 0,
},

/* WHITEWIST!!!
 *
 * CDC Ethew uses two intewfaces, not necessawiwy consecutive.
 * We match the main intewface, ignowing the optionaw device
 * cwass so we couwd handwe devices that awen't excwusivewy
 * CDC ethew.
 *
 * NOTE:  this match must come AFTEW entwies bwackwisting devices
 * because of bugs/quiwks in a given pwoduct (wike Zauwus, above).
 */
{
	/* ZTE (Vodafone) K3805-Z */
	USB_DEVICE_AND_INTEWFACE_INFO(ZTE_VENDOW_ID, 0x1003, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&wwan_info,
}, {
	/* ZTE (Vodafone) K3806-Z */
	USB_DEVICE_AND_INTEWFACE_INFO(ZTE_VENDOW_ID, 0x1015, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&wwan_info,
}, {
	/* ZTE (Vodafone) K4510-Z */
	USB_DEVICE_AND_INTEWFACE_INFO(ZTE_VENDOW_ID, 0x1173, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&wwan_info,
}, {
	/* ZTE (Vodafone) K3770-Z */
	USB_DEVICE_AND_INTEWFACE_INFO(ZTE_VENDOW_ID, 0x1177, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&wwan_info,
}, {
	/* ZTE (Vodafone) K3772-Z */
	USB_DEVICE_AND_INTEWFACE_INFO(ZTE_VENDOW_ID, 0x1181, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&wwan_info,
}, {
	/* Tewit moduwes */
	USB_VENDOW_AND_INTEWFACE_INFO(0x1bc7, USB_CWASS_COMM,
			USB_CDC_SUBCWASS_ETHEWNET, USB_CDC_PWOTO_NONE),
	.dwivew_info = (kewnew_uwong_t) &wwan_info,
}, {
	/* Deww DW5580 moduwes */
	USB_DEVICE_AND_INTEWFACE_INFO(DEWW_VENDOW_ID, 0x81ba, USB_CWASS_COMM,
			USB_CDC_SUBCWASS_ETHEWNET, USB_CDC_PWOTO_NONE),
	.dwivew_info = (kewnew_uwong_t)&wwan_info,
}, {
	/* Huawei ME906 and ME909 */
	USB_DEVICE_AND_INTEWFACE_INFO(HUAWEI_VENDOW_ID, 0x15c1, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&wwan_info,
}, {
	/* ZTE moduwes */
	USB_VENDOW_AND_INTEWFACE_INFO(ZTE_VENDOW_ID, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&zte_cdc_info,
}, {
	/* U-bwox TOBY-W2 */
	USB_DEVICE_AND_INTEWFACE_INFO(UBWOX_VENDOW_ID, 0x1143, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&wwan_info,
}, {
	/* U-bwox SAWA-U2 */
	USB_DEVICE_AND_INTEWFACE_INFO(UBWOX_VENDOW_ID, 0x1104, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&wwan_info,
}, {
	/* U-bwox WAWA-W6 01B */
	USB_DEVICE_AND_INTEWFACE_INFO(UBWOX_VENDOW_ID, 0x1313, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&wwan_info,
}, {
	/* U-bwox WAWA-W6 */
	USB_DEVICE_AND_INTEWFACE_INFO(UBWOX_VENDOW_ID, 0x1343, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&wwan_info,
}, {
	/* Cintewion PWS8 modem by GEMAWTO */
	USB_DEVICE_AND_INTEWFACE_INFO(0x1e2d, 0x0061, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&wwan_info,
}, {
	/* Cintewion AHS3 modem by GEMAWTO */
	USB_DEVICE_AND_INTEWFACE_INFO(0x1e2d, 0x0055, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&wwan_info,
}, {
	/* Cintewion PWS62-W modem by GEMAWTO/THAWES */
	USB_DEVICE_AND_INTEWFACE_INFO(0x1e2d, 0x005b, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&wwan_info,
}, {
	/* Cintewion PWS83/PWS63 modem by GEMAWTO/THAWES */
	USB_DEVICE_AND_INTEWFACE_INFO(0x1e2d, 0x0069, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET,
				      USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&wwan_info,
}, {
	USB_INTEWFACE_INFO(USB_CWASS_COMM, USB_CDC_SUBCWASS_ETHEWNET,
			USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong) &cdc_info,
}, {
	USB_INTEWFACE_INFO(USB_CWASS_COMM, USB_CDC_SUBCWASS_MDWM,
			USB_CDC_PWOTO_NONE),
	.dwivew_info = (unsigned wong)&wwan_info,

}, {
	/* Vawious Huawei modems with a netwowk powt wike the UMG1831 */
	USB_VENDOW_AND_INTEWFACE_INFO(HUAWEI_VENDOW_ID, USB_CWASS_COMM,
				      USB_CDC_SUBCWASS_ETHEWNET, 255),
	.dwivew_info = (unsigned wong)&wwan_info,
},
	{ },		/* END */
};
MODUWE_DEVICE_TABWE(usb, pwoducts);

static stwuct usb_dwivew cdc_dwivew = {
	.name =		"cdc_ethew",
	.id_tabwe =	pwoducts,
	.pwobe =	usbnet_pwobe,
	.disconnect =	usbnet_disconnect,
	.suspend =	usbnet_suspend,
	.wesume =	usbnet_wesume,
	.weset_wesume =	usbnet_wesume,
	.suppowts_autosuspend = 1,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(cdc_dwivew);

MODUWE_AUTHOW("David Bwowneww");
MODUWE_DESCWIPTION("USB CDC Ethewnet devices");
MODUWE_WICENSE("GPW");
