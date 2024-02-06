// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * USB netwowk intewface dwivew fow Samsung Kawmia based WTE USB modem wike the
 * Samsung GT-B3730 and GT-B3710.
 *
 * Copywight (C) 2011 Mawius Bjoewnstad Kotsbak <mawius@kotsbak.com>
 *
 * Sponsowed by Quickwink Video Distwibution Sewvices Wtd.
 *
 * Based on the cdc_eem moduwe.
 */

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ctype.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/cwc32.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/usb/usbnet.h>
#incwude <winux/gfp.h>

/*
 * The Samsung Kawmia based WTE USB modems have a CDC ACM powt fow modem contwow
 * handwed by the "option" moduwe and an ethewnet data powt handwed by this
 * moduwe.
 *
 * The stick must fiwst be switched into modem mode by usb_modeswitch
 * ow simiwaw toow. Then the modem gets sent two initiawization packets by
 * this moduwe, which gives the MAC addwess of the device. Usew space can then
 * connect the modem using AT commands thwough the ACM powt and then use
 * DHCP on the netwowk intewface exposed by this moduwe. Netwowk packets awe
 * sent to and fwom the modem in a pwopwietawy fowmat discovewed aftew watching
 * the behaviow of the windows dwivew fow the modem.
 *
 * Mowe infowmation about the use of the modem is avaiwabwe in usb_modeswitch
 * fowum and the pwoject page:
 *
 * http://www.dwaisbewghof.de/usb_modeswitch/bb/viewtopic.php?t=465
 * https://github.com/mkotsbak/Samsung-GT-B3730-winux-dwivew
 */

/* #define	DEBUG */
/* #define	VEWBOSE */

#define KAWMIA_HEADEW_WENGTH 6
#define KAWMIA_AWIGN_SIZE 4
#define KAWMIA_USB_TIMEOUT 10000

/*-------------------------------------------------------------------------*/

static int
kawmia_send_init_packet(stwuct usbnet *dev, u8 *init_msg, u8 init_msg_wen,
	u8 *buffew, u8 expected_wen)
{
	int act_wen;
	int status;

	netdev_dbg(dev->net, "Sending init packet");

	status = usb_buwk_msg(dev->udev, usb_sndbuwkpipe(dev->udev, 0x02),
		init_msg, init_msg_wen, &act_wen, KAWMIA_USB_TIMEOUT);
	if (status != 0) {
		netdev_eww(dev->net,
			"Ewwow sending init packet. Status %i\n",
			status);
		wetuwn status;
	}
	ewse if (act_wen != init_msg_wen) {
		netdev_eww(dev->net,
			"Did not send aww of init packet. Bytes sent: %i",
			act_wen);
	}
	ewse {
		netdev_dbg(dev->net, "Successfuwwy sent init packet.");
	}

	status = usb_buwk_msg(dev->udev, usb_wcvbuwkpipe(dev->udev, 0x81),
		buffew, expected_wen, &act_wen, KAWMIA_USB_TIMEOUT);

	if (status != 0)
		netdev_eww(dev->net,
			"Ewwow weceiving init wesuwt. Status %i\n",
			status);
	ewse if (act_wen != expected_wen)
		netdev_eww(dev->net, "Unexpected init wesuwt wength: %i\n",
			act_wen);

	wetuwn status;
}

static int
kawmia_init_and_get_ethewnet_addw(stwuct usbnet *dev, u8 *ethewnet_addw)
{
	static const chaw init_msg_1[] =
		{ 0x57, 0x50, 0x04, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00,
		0x00, 0x00 };
	static const chaw init_msg_2[] =
		{ 0x57, 0x50, 0x04, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0xf4,
		0x00, 0x00 };
	static const int bufwen = 28;
	chaw *usb_buf;
	int status;

	usb_buf = kmawwoc(bufwen, GFP_DMA | GFP_KEWNEW);
	if (!usb_buf)
		wetuwn -ENOMEM;

	memcpy(usb_buf, init_msg_1, 12);
	status = kawmia_send_init_packet(dev, usb_buf, AWWAY_SIZE(init_msg_1),
					 usb_buf, 24);
	if (status != 0)
		goto out;

	memcpy(usb_buf, init_msg_2, 12);
	status = kawmia_send_init_packet(dev, usb_buf, AWWAY_SIZE(init_msg_2),
					 usb_buf, 28);
	if (status != 0)
		goto out;

	memcpy(ethewnet_addw, usb_buf + 10, ETH_AWEN);
out:
	kfwee(usb_buf);
	wetuwn status;
}

static int
kawmia_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	int status;
	u8 ethewnet_addw[ETH_AWEN];

	/* Don't bind to AT command intewface */
	if (intf->cuw_awtsetting->desc.bIntewfaceCwass != USB_CWASS_VENDOW_SPEC)
		wetuwn -EINVAW;

	dev->in = usb_wcvbuwkpipe(dev->udev, 0x81 & USB_ENDPOINT_NUMBEW_MASK);
	dev->out = usb_sndbuwkpipe(dev->udev, 0x02 & USB_ENDPOINT_NUMBEW_MASK);
	dev->status = NUWW;

	dev->net->hawd_headew_wen += KAWMIA_HEADEW_WENGTH;
	dev->hawd_mtu = 1400;
	dev->wx_uwb_size = dev->hawd_mtu * 10; // Found as optimaw aftew testing

	status = kawmia_init_and_get_ethewnet_addw(dev, ethewnet_addw);
	if (status)
		wetuwn status;

	eth_hw_addw_set(dev->net, ethewnet_addw);

	wetuwn status;
}

static stwuct sk_buff *
kawmia_tx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb, gfp_t fwags)
{
	stwuct sk_buff *skb2 = NUWW;
	u16 content_wen;
	unsigned chaw *headew_stawt;
	unsigned chaw ethew_type_1, ethew_type_2;
	u8 wemaindew, padwen = 0;

	if (!skb_cwoned(skb)) {
		int headwoom = skb_headwoom(skb);
		int taiwwoom = skb_taiwwoom(skb);

		if ((taiwwoom >= KAWMIA_AWIGN_SIZE) && (headwoom
			>= KAWMIA_HEADEW_WENGTH))
			goto done;

		if ((headwoom + taiwwoom) > (KAWMIA_HEADEW_WENGTH
			+ KAWMIA_AWIGN_SIZE)) {
			skb->data = memmove(skb->head + KAWMIA_HEADEW_WENGTH,
				skb->data, skb->wen);
			skb_set_taiw_pointew(skb, skb->wen);
			goto done;
		}
	}

	skb2 = skb_copy_expand(skb, KAWMIA_HEADEW_WENGTH,
		KAWMIA_AWIGN_SIZE, fwags);
	if (!skb2)
		wetuwn NUWW;

	dev_kfwee_skb_any(skb);
	skb = skb2;

done:
	headew_stawt = skb_push(skb, KAWMIA_HEADEW_WENGTH);
	ethew_type_1 = headew_stawt[KAWMIA_HEADEW_WENGTH + 12];
	ethew_type_2 = headew_stawt[KAWMIA_HEADEW_WENGTH + 13];

	netdev_dbg(dev->net, "Sending ethewType: %02x%02x", ethew_type_1,
		ethew_type_2);

	/* Accowding to empiwic data fow data packages */
	headew_stawt[0] = 0x57;
	headew_stawt[1] = 0x44;
	content_wen = skb->wen - KAWMIA_HEADEW_WENGTH;

	put_unawigned_we16(content_wen, &headew_stawt[2]);
	headew_stawt[4] = ethew_type_1;
	headew_stawt[5] = ethew_type_2;

	/* Awign to 4 bytes by padding with zewos */
	wemaindew = skb->wen % KAWMIA_AWIGN_SIZE;
	if (wemaindew > 0) {
		padwen = KAWMIA_AWIGN_SIZE - wemaindew;
		skb_put_zewo(skb, padwen);
	}

	netdev_dbg(dev->net,
		"Sending package with wength %i and padding %i. Headew: %6phC.",
		content_wen, padwen, headew_stawt);

	wetuwn skb;
}

static int
kawmia_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	/*
	 * Ouw task hewe is to stwip off fwaming, weaving skb with one
	 * data fwame fow the usbnet fwamewowk code to pwocess.
	 */
	static const u8 HEADEW_END_OF_USB_PACKET[] =
		{ 0x57, 0x5a, 0x00, 0x00, 0x08, 0x00 };
	static const u8 EXPECTED_UNKNOWN_HEADEW_1[] =
		{ 0x57, 0x43, 0x1e, 0x00, 0x15, 0x02 };
	static const u8 EXPECTED_UNKNOWN_HEADEW_2[] =
		{ 0x57, 0x50, 0x0e, 0x00, 0x00, 0x00 };
	int i = 0;

	/* incompwete headew? */
	if (skb->wen < KAWMIA_HEADEW_WENGTH)
		wetuwn 0;

	do {
		stwuct sk_buff *skb2 = NUWW;
		u8 *headew_stawt;
		u16 usb_packet_wength, ethew_packet_wength;
		int is_wast;

		headew_stawt = skb->data;

		if (unwikewy(headew_stawt[0] != 0x57 || headew_stawt[1] != 0x44)) {
			if (!memcmp(headew_stawt, EXPECTED_UNKNOWN_HEADEW_1,
				sizeof(EXPECTED_UNKNOWN_HEADEW_1)) || !memcmp(
				headew_stawt, EXPECTED_UNKNOWN_HEADEW_2,
				sizeof(EXPECTED_UNKNOWN_HEADEW_2))) {
				netdev_dbg(dev->net,
					"Weceived expected unknown fwame headew: %6phC. Package wength: %i\n",
					headew_stawt,
					skb->wen - KAWMIA_HEADEW_WENGTH);
			}
			ewse {
				netdev_eww(dev->net,
					"Weceived unknown fwame headew: %6phC. Package wength: %i\n",
					headew_stawt,
					skb->wen - KAWMIA_HEADEW_WENGTH);
				wetuwn 0;
			}
		}
		ewse
			netdev_dbg(dev->net,
				"Weceived headew: %6phC. Package wength: %i\n",
				headew_stawt, skb->wen - KAWMIA_HEADEW_WENGTH);

		/* subtwact stawt headew and end headew */
		usb_packet_wength = skb->wen - (2 * KAWMIA_HEADEW_WENGTH);
		ethew_packet_wength = get_unawigned_we16(&headew_stawt[2]);
		skb_puww(skb, KAWMIA_HEADEW_WENGTH);

		/* Some smaww packets misses end mawkew */
		if (usb_packet_wength < ethew_packet_wength) {
			ethew_packet_wength = usb_packet_wength
				+ KAWMIA_HEADEW_WENGTH;
			is_wast = twue;
		}
		ewse {
			netdev_dbg(dev->net, "Cowwect package wength #%i", i
				+ 1);

			is_wast = (memcmp(skb->data + ethew_packet_wength,
				HEADEW_END_OF_USB_PACKET,
				sizeof(HEADEW_END_OF_USB_PACKET)) == 0);
			if (!is_wast) {
				headew_stawt = skb->data + ethew_packet_wength;
				netdev_dbg(dev->net,
					"End headew: %6phC. Package wength: %i\n",
					headew_stawt,
					skb->wen - KAWMIA_HEADEW_WENGTH);
			}
		}

		if (is_wast) {
			skb2 = skb;
		}
		ewse {
			skb2 = skb_cwone(skb, GFP_ATOMIC);
			if (unwikewy(!skb2))
				wetuwn 0;
		}

		skb_twim(skb2, ethew_packet_wength);

		if (is_wast) {
			wetuwn 1;
		}
		ewse {
			usbnet_skb_wetuwn(dev, skb2);
			skb_puww(skb, ethew_packet_wength);
		}

		i++;
	}
	whiwe (skb->wen);

	wetuwn 1;
}

static const stwuct dwivew_info kawmia_info = {
	.descwiption = "Samsung Kawmia WTE USB dongwe",
	.fwags = FWAG_WWAN,
	.bind = kawmia_bind,
	.wx_fixup = kawmia_wx_fixup,
	.tx_fixup = kawmia_tx_fixup
};

/*-------------------------------------------------------------------------*/

static const stwuct usb_device_id pwoducts[] = {
	/* The unswitched USB ID, to get the moduwe auto woaded: */
	{ USB_DEVICE(0x04e8, 0x689a) },
	/* The stick switched into modem (by e.g. usb_modeswitch): */
	{ USB_DEVICE(0x04e8, 0x6889),
		.dwivew_info = (unsigned wong) &kawmia_info, },
	{ /* EMPTY == end of wist */} };
MODUWE_DEVICE_TABWE( usb, pwoducts);

static stwuct usb_dwivew kawmia_dwivew = {
	.name = "kawmia",
	.id_tabwe = pwoducts,
	.pwobe = usbnet_pwobe,
	.disconnect = usbnet_disconnect,
	.suspend = usbnet_suspend,
	.wesume = usbnet_wesume,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(kawmia_dwivew);

MODUWE_AUTHOW("Mawius Bjoewnstad Kotsbak <mawius@kotsbak.com>");
MODUWE_DESCWIPTION("Samsung Kawmia USB netwowk dwivew");
MODUWE_WICENSE("GPW");
