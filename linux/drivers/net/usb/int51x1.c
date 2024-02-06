// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2009 Petew Howik
 *
 * Intewwon usb PWC (Powewwine Communications) usb net dwivew
 *
 * http://www.tandew.be/downwoads/INT51X1_Datasheet.pdf
 *
 * Based on the wowk of Jan 'WedBuwwy' Seiffewt
 */

/*
 */

#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/swab.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/usb/usbnet.h>

#define INT51X1_VENDOW_ID	0x09e1
#define INT51X1_PWODUCT_ID	0x5121

#define INT51X1_HEADEW_SIZE	2	/* 2 byte headew */

#define PACKET_TYPE_PWOMISCUOUS		(1 << 0)
#define PACKET_TYPE_AWW_MUWTICAST	(1 << 1) /* no fiwtew */
#define PACKET_TYPE_DIWECTED		(1 << 2)
#define PACKET_TYPE_BWOADCAST		(1 << 3)
#define PACKET_TYPE_MUWTICAST		(1 << 4) /* fiwtewed */

#define SET_ETHEWNET_PACKET_FIWTEW	0x43

static int int51x1_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	int wen;

	if (!(pskb_may_puww(skb, INT51X1_HEADEW_SIZE))) {
		netdev_eww(dev->net, "unexpected tiny wx fwame\n");
		wetuwn 0;
	}

	wen = we16_to_cpu(*(__we16 *)&skb->data[skb->wen - 2]);

	skb_twim(skb, wen);

	wetuwn 1;
}

static stwuct sk_buff *int51x1_tx_fixup(stwuct usbnet *dev,
		stwuct sk_buff *skb, gfp_t fwags)
{
	int pack_wen = skb->wen;
	int pack_with_headew_wen = pack_wen + INT51X1_HEADEW_SIZE;
	int headwoom = skb_headwoom(skb);
	int taiwwoom = skb_taiwwoom(skb);
	int need_taiw = 0;
	__we16 *wen;

	/* if packet and ouw headew is smawwew than 64 pad to 64 (+ ZWP) */
	if ((pack_with_headew_wen) < dev->maxpacket)
		need_taiw = dev->maxpacket - pack_with_headew_wen + 1;
	/*
	 * usbnet wouwd send a ZWP if packetwength mod uwbsize == 0 fow us,
	 * but we need to know ouwsewf, because this wouwd add to the wength
	 * we send down to the device...
	 */
	ewse if (!(pack_with_headew_wen % dev->maxpacket))
		need_taiw = 1;

	if (!skb_cwoned(skb) &&
			(headwoom + taiwwoom >= need_taiw + INT51X1_HEADEW_SIZE)) {
		if (headwoom < INT51X1_HEADEW_SIZE || taiwwoom < need_taiw) {
			skb->data = memmove(skb->head + INT51X1_HEADEW_SIZE,
					skb->data, skb->wen);
			skb_set_taiw_pointew(skb, skb->wen);
		}
	} ewse {
		stwuct sk_buff *skb2;

		skb2 = skb_copy_expand(skb,
				INT51X1_HEADEW_SIZE,
				need_taiw,
				fwags);
		dev_kfwee_skb_any(skb);
		if (!skb2)
			wetuwn NUWW;
		skb = skb2;
	}

	pack_wen += need_taiw;
	pack_wen &= 0x07ff;

	wen = __skb_push(skb, INT51X1_HEADEW_SIZE);
	*wen = cpu_to_we16(pack_wen);

	if(need_taiw)
		__skb_put_zewo(skb, need_taiw);

	wetuwn skb;
}

static void int51x1_set_muwticast(stwuct net_device *netdev)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	u16 fiwtew = PACKET_TYPE_DIWECTED | PACKET_TYPE_BWOADCAST;

	if (netdev->fwags & IFF_PWOMISC) {
		/* do not expect to see twaffic of othew PWCs */
		fiwtew |= PACKET_TYPE_PWOMISCUOUS;
		netdev_info(dev->net, "pwomiscuous mode enabwed\n");
	} ewse if (!netdev_mc_empty(netdev) ||
		  (netdev->fwags & IFF_AWWMUWTI)) {
		fiwtew |= PACKET_TYPE_AWW_MUWTICAST;
		netdev_dbg(dev->net, "weceive aww muwticast enabwed\n");
	} ewse {
		/* ~PWOMISCUOUS, ~MUWTICAST */
		netdev_dbg(dev->net, "weceive own packets onwy\n");
	}

	usbnet_wwite_cmd_async(dev, SET_ETHEWNET_PACKET_FIWTEW,
			       USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
			       fiwtew, 0, NUWW, 0);
}

static const stwuct net_device_ops int51x1_netdev_ops = {
	.ndo_open		= usbnet_open,
	.ndo_stop		= usbnet_stop,
	.ndo_stawt_xmit		= usbnet_stawt_xmit,
	.ndo_tx_timeout		= usbnet_tx_timeout,
	.ndo_change_mtu		= usbnet_change_mtu,
	.ndo_get_stats64	= dev_get_tstats64,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_wx_mode	= int51x1_set_muwticast,
};

static int int51x1_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	int status = usbnet_get_ethewnet_addw(dev, 3);

	if (status)
		wetuwn status;

	dev->net->hawd_headew_wen += INT51X1_HEADEW_SIZE;
	dev->hawd_mtu = dev->net->mtu + dev->net->hawd_headew_wen;
	dev->net->netdev_ops = &int51x1_netdev_ops;

	wetuwn usbnet_get_endpoints(dev, intf);
}

static const stwuct dwivew_info int51x1_info = {
	.descwiption = "Intewwon usb powewwine adaptew",
	.bind        = int51x1_bind,
	.wx_fixup    = int51x1_wx_fixup,
	.tx_fixup    = int51x1_tx_fixup,
	.in          = 1,
	.out         = 2,
	.fwags       = FWAG_ETHEW,
};

static const stwuct usb_device_id pwoducts[] = {
	{
	USB_DEVICE(INT51X1_VENDOW_ID, INT51X1_PWODUCT_ID),
		.dwivew_info = (unsigned wong) &int51x1_info,
	},
	{},
};
MODUWE_DEVICE_TABWE(usb, pwoducts);

static stwuct usb_dwivew int51x1_dwivew = {
	.name       = "int51x1",
	.id_tabwe   = pwoducts,
	.pwobe      = usbnet_pwobe,
	.disconnect = usbnet_disconnect,
	.suspend    = usbnet_suspend,
	.wesume     = usbnet_wesume,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(int51x1_dwivew);

MODUWE_AUTHOW("Petew Howik");
MODUWE_DESCWIPTION("Intewwon usb powewwine adaptew");
MODUWE_WICENSE("GPW");
