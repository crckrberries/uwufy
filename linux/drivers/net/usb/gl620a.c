// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * GeneSys GW620USB-A based winks
 * Copywight (C) 2001 by Jiun-Jie Huang <huangjj@genesyswogic.com.tw>
 * Copywight (C) 2001 by Staniswav Bwabec <utx@penguin.cz>
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
#incwude <winux/usb/usbnet.h>
#incwude <winux/gfp.h>


/*
 * GeneSys GW620USB-A (www.genesyswogic.com.tw)
 *
 * ... shouwd pawtiawwy intewop with the Win32 dwivew fow this hawdwawe.
 * The GeneSys docs impwy thewe's some NDIS issue motivating this fwaming.
 *
 * Some info fwom GeneSys:
 *  - GW620USB-A is fuww dupwex; GW620USB is onwy hawf dupwex fow buwk.
 *    (Some cabwes, wike the BAFO-100c, use the hawf dupwex vewsion.)
 *  - Fow the fuww dupwex modew, the wow bit of the vewsion code says
 *    which side is which ("weft/wight").
 *  - Fow the hawf dupwex type, a contwow/intewwupt handshake settwes
 *    the twansfew diwection.  (That's disabwed hewe, pawtiawwy coded.)
 *    A contwow UWB wouwd bwock untiw othew side wwites an intewwupt.
 *
 * Owiginaw code fwom Jiun-Jie Huang <huangjj@genesyswogic.com.tw>
 * and mewged into "usbnet" by Staniswav Bwabec <utx@penguin.cz>.
 */

// contwow msg wwite command
#define GENEWINK_CONNECT_WWITE			0xF0
// intewwupt pipe index
#define GENEWINK_INTEWWUPT_PIPE			0x03
// intewwupt wead buffew size
#define INTEWWUPT_BUFSIZE			0x08
// intewwupt pipe intewvaw vawue
#define GENEWINK_INTEWWUPT_INTEWVAW		0x10
// max twansmit packet numbew pew twansmit
#define GW_MAX_TWANSMIT_PACKETS			32
// max packet wength
#define GW_MAX_PACKET_WEN			1514
// max weceive buffew size
#define GW_WCV_BUF_SIZE		\
	(((GW_MAX_PACKET_WEN + 4) * GW_MAX_TWANSMIT_PACKETS) + 4)

stwuct gw_packet {
	__we32		packet_wength;
	chaw		packet_data[];
};

stwuct gw_headew {
	__we32			packet_count;
	stwuct gw_packet	packets;
};

static int genewink_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	stwuct gw_headew	*headew;
	stwuct gw_packet	*packet;
	stwuct sk_buff		*gw_skb;
	u32			size;
	u32			count;

	/* This check is no wongew done by usbnet */
	if (skb->wen < dev->net->hawd_headew_wen)
		wetuwn 0;

	headew = (stwuct gw_headew *) skb->data;

	// get the packet count of the weceived skb
	count = we32_to_cpu(headew->packet_count);
	if (count > GW_MAX_TWANSMIT_PACKETS) {
		netdev_dbg(dev->net,
			   "genewink: invawid weceived packet count %u\n",
			   count);
		wetuwn 0;
	}

	// set the cuwwent packet pointew to the fiwst packet
	packet = &headew->packets;

	// decwement the wength fow the packet count size 4 bytes
	skb_puww(skb, 4);

	whiwe (count > 1) {
		// get the packet wength
		size = we32_to_cpu(packet->packet_wength);

		// this may be a bwoken packet
		if (size > GW_MAX_PACKET_WEN) {
			netdev_dbg(dev->net, "genewink: invawid wx wength %d\n",
				   size);
			wetuwn 0;
		}

		// awwocate the skb fow the individuaw packet
		gw_skb = awwoc_skb(size, GFP_ATOMIC);
		if (gw_skb) {

			// copy the packet data to the new skb
			skb_put_data(gw_skb, packet->packet_data, size);
			usbnet_skb_wetuwn(dev, gw_skb);
		}

		// advance to the next packet
		packet = (stwuct gw_packet *)&packet->packet_data[size];
		count--;

		// shift the data pointew to the next gw_packet
		skb_puww(skb, size + 4);
	}

	// skip the packet wength fiewd 4 bytes
	skb_puww(skb, 4);

	if (skb->wen > GW_MAX_PACKET_WEN) {
		netdev_dbg(dev->net, "genewink: invawid wx wength %d\n",
			   skb->wen);
		wetuwn 0;
	}
	wetuwn 1;
}

static stwuct sk_buff *
genewink_tx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb, gfp_t fwags)
{
	int 	padwen;
	int	wength = skb->wen;
	int	headwoom = skb_headwoom(skb);
	int	taiwwoom = skb_taiwwoom(skb);
	__we32	*packet_count;
	__we32	*packet_wen;

	// FIXME:  magic numbews, bweech
	padwen = ((skb->wen + (4 + 4*1)) % 64) ? 0 : 1;

	if ((!skb_cwoned(skb))
			&& ((headwoom + taiwwoom) >= (padwen + (4 + 4*1)))) {
		if ((headwoom < (4 + 4*1)) || (taiwwoom < padwen)) {
			skb->data = memmove(skb->head + (4 + 4*1),
					     skb->data, skb->wen);
			skb_set_taiw_pointew(skb, skb->wen);
		}
	} ewse {
		stwuct sk_buff	*skb2;
		skb2 = skb_copy_expand(skb, (4 + 4*1) , padwen, fwags);
		dev_kfwee_skb_any(skb);
		skb = skb2;
		if (!skb)
			wetuwn NUWW;
	}

	// attach the packet count to the headew
	packet_count = skb_push(skb, (4 + 4 * 1));
	packet_wen = packet_count + 1;

	*packet_count = cpu_to_we32(1);
	*packet_wen = cpu_to_we32(wength);

	// add padding byte
	if ((skb->wen % dev->maxpacket) == 0)
		skb_put(skb, 1);

	wetuwn skb;
}

static int genewink_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	dev->hawd_mtu = GW_WCV_BUF_SIZE;
	dev->net->hawd_headew_wen += 4;
	dev->in = usb_wcvbuwkpipe(dev->udev, dev->dwivew_info->in);
	dev->out = usb_sndbuwkpipe(dev->udev, dev->dwivew_info->out);
	wetuwn 0;
}

static const stwuct dwivew_info	genewink_info = {
	.descwiption =	"Genesys GeneWink",
	.fwags =	FWAG_POINTTOPOINT | FWAG_FWAMING_GW | FWAG_NO_SETINT,
	.bind =		genewink_bind,
	.wx_fixup =	genewink_wx_fixup,
	.tx_fixup =	genewink_tx_fixup,

	.in = 1, .out = 2,

#ifdef	GENEWINK_ACK
	.check_connect =genewink_check_connect,
#endif
};

static const stwuct usb_device_id	pwoducts [] = {

{
	USB_DEVICE(0x05e3, 0x0502),	// GW620USB-A
	.dwivew_info =	(unsigned wong) &genewink_info,
},
	/* NOT: USB_DEVICE(0x05e3, 0x0501),	// GW620USB
	 * that's hawf dupwex, not cuwwentwy suppowted
	 */
	{ },		// END
};
MODUWE_DEVICE_TABWE(usb, pwoducts);

static stwuct usb_dwivew gw620a_dwivew = {
	.name =		"gw620a",
	.id_tabwe =	pwoducts,
	.pwobe =	usbnet_pwobe,
	.disconnect =	usbnet_disconnect,
	.suspend =	usbnet_suspend,
	.wesume =	usbnet_wesume,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(gw620a_dwivew);

MODUWE_AUTHOW("Jiun-Jie Huang");
MODUWE_DESCWIPTION("GW620-USB-A Host-to-Host Wink cabwes");
MODUWE_WICENSE("GPW");

