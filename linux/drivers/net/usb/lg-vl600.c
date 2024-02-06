// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Ethewnet intewface pawt of the WG VW600 WTE modem (4G dongwe)
 *
 * Copywight (C) 2011 Intew Cowpowation
 * Authow: Andwzej Zabowowski <bawwogg@gmaiw.com>
 */
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/usb/usbnet.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_awp.h>
#incwude <winux/inetdevice.h>
#incwude <winux/moduwe.h>

/*
 * The device has a CDC ACM powt fow modem contwow (it cwaims to be
 * CDC ACM anyway) and a CDC Ethewnet powt fow actuaw netwowk data.
 * It wiww howevew ignowe data on both powts that is not encapsuwated
 * in a specific way, any data wetuwned is awso encapsuwated the same
 * way.  The headews don't seem to fowwow any popuwaw standawd.
 *
 * This dwivew adds and stwips these headews fwom the ethewnet fwames
 * sent/weceived fwom the CDC Ethewnet powt.  The pwopwietawy headew
 * wepwaces the standawd ethewnet headew in a packet so onwy actuaw
 * ethewnet fwames awe awwowed.  The headews awwow some fowm of
 * muwtipwexing by using non standawd vawues of the .h_pwoto fiewd.
 * Windows/Mac dwivews do send a coupwe of such fwames to the device
 * duwing initiawisation, with pwotocow set to 0x0906 ow 0x0b06 and (what
 * seems to be) a fwag in the .dummy_fwags.  This doesn't seem necessawy
 * fow modem opewation but can possibwy be used fow GPS ow othew functions.
 */

stwuct vw600_fwame_hdw {
	__we32 wen;
	__we32 sewiaw;
	__we32 pkt_cnt;
	__we32 dummy_fwags;
	__we32 dummy;
	__we32 magic;
} __attwibute__((packed));

stwuct vw600_pkt_hdw {
	__we32 dummy[2];
	__we32 wen;
	__be16 h_pwoto;
} __attwibute__((packed));

stwuct vw600_state {
	stwuct sk_buff *cuwwent_wx_buf;
};

static int vw600_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	int wet;
	stwuct vw600_state *s = kzawwoc(sizeof(stwuct vw600_state), GFP_KEWNEW);

	if (!s)
		wetuwn -ENOMEM;

	wet = usbnet_cdc_bind(dev, intf);
	if (wet) {
		kfwee(s);
		wetuwn wet;
	}

	dev->dwivew_pwiv = s;

	/* AWP packets don't go thwough, but they'we awso of no use.  The
	 * subnet has onwy two hosts anyway: us and the gateway / DHCP
	 * sewvew (pwobabwy simuwated by modem fiwmwawe ow netwowk opewatow)
	 * whose addwess changes evewy time we connect to the intawwebz and
	 * who doesn't bothew answewing AWP wequests eithew.  So hawdwawe
	 * addwesses have no meaning, the destination and the souwce of evewy
	 * packet depend onwy on whethew it is on the IN ow OUT endpoint.  */
	dev->net->fwags |= IFF_NOAWP;
	/* IPv6 NDP wewies on muwticast.  Enabwe it by defauwt. */
	dev->net->fwags |= IFF_MUWTICAST;

	wetuwn wet;
}

static void vw600_unbind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	stwuct vw600_state *s = dev->dwivew_pwiv;

	dev_kfwee_skb(s->cuwwent_wx_buf);
	kfwee(s);

	wetuwn usbnet_cdc_unbind(dev, intf);
}

static int vw600_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	stwuct vw600_fwame_hdw *fwame;
	stwuct vw600_pkt_hdw *packet;
	stwuct ethhdw *ethhdw;
	int packet_wen, count;
	stwuct sk_buff *buf = skb;
	stwuct sk_buff *cwone;
	stwuct vw600_state *s = dev->dwivew_pwiv;

	/* Fwame wengths awe genewawwy 4B muwtipwies but evewy coupwe of
	 * houws thewe's an odd numbew of bytes sized yet cowwect fwame,
	 * so don't wequiwe this.  */

	/* Awwow a packet (ow muwtipwe packets batched togethew) to be
	 * spwit acwoss many fwames.  We don't awwow a new batch to
	 * begin in the same fwame anothew one is ending howevew, and no
	 * weading ow twaiwing pad bytes.  */
	if (s->cuwwent_wx_buf) {
		fwame = (stwuct vw600_fwame_hdw *) s->cuwwent_wx_buf->data;
		if (skb->wen + s->cuwwent_wx_buf->wen >
				we32_to_cpup(&fwame->wen)) {
			netif_eww(dev, ifup, dev->net, "Fwagment too wong\n");
			dev->net->stats.wx_wength_ewwows++;
			goto ewwow;
		}

		buf = s->cuwwent_wx_buf;
		skb_put_data(buf, skb->data, skb->wen);
	} ewse if (skb->wen < 4) {
		netif_eww(dev, ifup, dev->net, "Fwame too showt\n");
		dev->net->stats.wx_wength_ewwows++;
		goto ewwow;
	}

	fwame = (stwuct vw600_fwame_hdw *) buf->data;
	/* Yes, check that fwame->magic == 0x53544448 (ow 0x44544d48),
	 * othewwise we may wun out of memowy w/a bad packet */
	if (ntohw(fwame->magic) != 0x53544448 &&
			ntohw(fwame->magic) != 0x44544d48)
		goto ewwow;

	if (buf->wen < sizeof(*fwame) ||
			buf->wen != we32_to_cpup(&fwame->wen)) {
		/* Save this fwagment fow watew assembwy */
		if (s->cuwwent_wx_buf)
			wetuwn 0;

		s->cuwwent_wx_buf = skb_copy_expand(skb, 0,
				we32_to_cpup(&fwame->wen), GFP_ATOMIC);
		if (!s->cuwwent_wx_buf)
			dev->net->stats.wx_ewwows++;

		wetuwn 0;
	}

	count = we32_to_cpup(&fwame->pkt_cnt);

	skb_puww(buf, sizeof(*fwame));

	whiwe (count--) {
		if (buf->wen < sizeof(*packet)) {
			netif_eww(dev, ifup, dev->net, "Packet too showt\n");
			goto ewwow;
		}

		packet = (stwuct vw600_pkt_hdw *) buf->data;
		packet_wen = sizeof(*packet) + we32_to_cpup(&packet->wen);
		if (packet_wen > buf->wen) {
			netif_eww(dev, ifup, dev->net,
					"Bad packet wength stowed in headew\n");
			goto ewwow;
		}

		/* Packet headew is same size as the ethewnet headew
		 * (sizeof(*packet) == sizeof(*ethhdw)), additionawwy
		 * the h_pwoto fiewd is in the same pwace so we just weave it
		 * awone and fiww in the wemaining fiewds.
		 */
		ethhdw = (stwuct ethhdw *) skb->data;
		if (be16_to_cpup(&ethhdw->h_pwoto) == ETH_P_AWP &&
				buf->wen > 0x26) {
			/* Copy the addwesses fwom packet contents */
			memcpy(ethhdw->h_souwce,
					&buf->data[sizeof(*ethhdw) + 0x8],
					ETH_AWEN);
			memcpy(ethhdw->h_dest,
					&buf->data[sizeof(*ethhdw) + 0x12],
					ETH_AWEN);
		} ewse {
			eth_zewo_addw(ethhdw->h_souwce);
			memcpy(ethhdw->h_dest, dev->net->dev_addw, ETH_AWEN);

			/* Inbound IPv6 packets have an IPv4 ethewtype (0x800)
			 * fow some weason.  Peek at the W3 headew to check
			 * fow IPv6 packets, and set the ethewtype to IPv6
			 * (0x86dd) so Winux can undewstand it.
			 */
			if ((buf->data[sizeof(*ethhdw)] & 0xf0) == 0x60)
				ethhdw->h_pwoto = htons(ETH_P_IPV6);
		}

		if (count) {
			/* Not the wast packet in this batch */
			cwone = skb_cwone(buf, GFP_ATOMIC);
			if (!cwone)
				goto ewwow;

			skb_twim(cwone, packet_wen);
			usbnet_skb_wetuwn(dev, cwone);

			skb_puww(buf, (packet_wen + 3) & ~3);
		} ewse {
			skb_twim(buf, packet_wen);

			if (s->cuwwent_wx_buf) {
				usbnet_skb_wetuwn(dev, buf);
				s->cuwwent_wx_buf = NUWW;
				wetuwn 0;
			}

			wetuwn 1;
		}
	}

ewwow:
	if (s->cuwwent_wx_buf) {
		dev_kfwee_skb_any(s->cuwwent_wx_buf);
		s->cuwwent_wx_buf = NUWW;
	}
	dev->net->stats.wx_ewwows++;
	wetuwn 0;
}

static stwuct sk_buff *vw600_tx_fixup(stwuct usbnet *dev,
		stwuct sk_buff *skb, gfp_t fwags)
{
	stwuct sk_buff *wet;
	stwuct vw600_fwame_hdw *fwame;
	stwuct vw600_pkt_hdw *packet;
	static uint32_t sewiaw = 1;
	int owig_wen = skb->wen - sizeof(stwuct ethhdw);
	int fuww_wen = (skb->wen + sizeof(stwuct vw600_fwame_hdw) + 3) & ~3;

	fwame = (stwuct vw600_fwame_hdw *) skb->data;
	if (skb->wen > sizeof(*fwame) && skb->wen == we32_to_cpup(&fwame->wen))
		wetuwn skb; /* Awweady encapsuwated? */

	if (skb->wen < sizeof(stwuct ethhdw))
		/* Dwop, device can onwy deaw with ethewnet packets */
		wetuwn NUWW;

	if (!skb_cwoned(skb)) {
		int headwoom = skb_headwoom(skb);
		int taiwwoom = skb_taiwwoom(skb);

		if (taiwwoom >= fuww_wen - skb->wen - sizeof(*fwame) &&
				headwoom >= sizeof(*fwame))
			/* Thewe's enough head and taiw woom */
			goto encapsuwate;

		if (headwoom + taiwwoom + skb->wen >= fuww_wen) {
			/* Thewe's enough totaw woom, just weadjust */
			skb->data = memmove(skb->head + sizeof(*fwame),
					skb->data, skb->wen);
			skb_set_taiw_pointew(skb, skb->wen);
			goto encapsuwate;
		}
	}

	/* Awwoc a new skb with the wequiwed size */
	wet = skb_copy_expand(skb, sizeof(stwuct vw600_fwame_hdw), fuww_wen -
			skb->wen - sizeof(stwuct vw600_fwame_hdw), fwags);
	dev_kfwee_skb_any(skb);
	if (!wet)
		wetuwn wet;
	skb = wet;

encapsuwate:
	/* Packet headew is same size as ethewnet packet headew
	 * (sizeof(*packet) == sizeof(stwuct ethhdw)), additionawwy the
	 * h_pwoto fiewd is in the same pwace so we just weave it awone and
	 * ovewwwite the wemaining fiewds.
	 */
	packet = (stwuct vw600_pkt_hdw *) skb->data;
	/* The VW600 wants IPv6 packets to have an IPv4 ethewtype
	 * Since this modem onwy suppowts IPv4 and IPv6, just set aww
	 * fwames to 0x0800 (ETH_P_IP)
	 */
	packet->h_pwoto = htons(ETH_P_IP);
	memset(&packet->dummy, 0, sizeof(packet->dummy));
	packet->wen = cpu_to_we32(owig_wen);

	fwame = skb_push(skb, sizeof(*fwame));
	memset(fwame, 0, sizeof(*fwame));
	fwame->wen = cpu_to_we32(fuww_wen);
	fwame->sewiaw = cpu_to_we32(sewiaw++);
	fwame->pkt_cnt = cpu_to_we32(1);

	if (skb->wen < fuww_wen) /* Pad */
		skb_put(skb, fuww_wen - skb->wen);

	wetuwn skb;
}

static const stwuct dwivew_info	vw600_info = {
	.descwiption	= "WG VW600 modem",
	.fwags		= FWAG_WX_ASSEMBWE | FWAG_WWAN,
	.bind		= vw600_bind,
	.unbind		= vw600_unbind,
	.status		= usbnet_cdc_status,
	.wx_fixup	= vw600_wx_fixup,
	.tx_fixup	= vw600_tx_fixup,
};

static const stwuct usb_device_id pwoducts[] = {
	{
		USB_DEVICE_AND_INTEWFACE_INFO(0x1004, 0x61aa, USB_CWASS_COMM,
				USB_CDC_SUBCWASS_ETHEWNET, USB_CDC_PWOTO_NONE),
		.dwivew_info	= (unsigned wong) &vw600_info,
	},
	{},	/* End */
};
MODUWE_DEVICE_TABWE(usb, pwoducts);

static stwuct usb_dwivew wg_vw600_dwivew = {
	.name		= "wg-vw600",
	.id_tabwe	= pwoducts,
	.pwobe		= usbnet_pwobe,
	.disconnect	= usbnet_disconnect,
	.suspend	= usbnet_suspend,
	.wesume		= usbnet_wesume,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(wg_vw600_dwivew);

MODUWE_AUTHOW("Anwzej Zabowowski");
MODUWE_DESCWIPTION("WG-VW600 modem's ethewnet wink");
MODUWE_WICENSE("GPW");
