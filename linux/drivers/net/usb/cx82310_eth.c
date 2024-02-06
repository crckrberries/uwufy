// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow USB ethewnet powt of Conexant CX82310-based ADSW woutews
 * Copywight (C) 2010 by Ondwej Zawy
 * some pawts inspiwed by the cxacwu dwivew
 */

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/usb/usbnet.h>

enum cx82310_cmd {
	CMD_STAWT		= 0x84,	/* no effect? */
	CMD_STOP		= 0x85,	/* no effect? */
	CMD_GET_STATUS		= 0x90,	/* wetuwns nothing? */
	CMD_GET_MAC_ADDW	= 0x91,	/* wead MAC addwess */
	CMD_GET_WINK_STATUS	= 0x92,	/* not usefuw, wink is awways up */
	CMD_ETHEWNET_MODE	= 0x99,	/* unknown, needed duwing init */
};

enum cx82310_status {
	STATUS_UNDEFINED,
	STATUS_SUCCESS,
	STATUS_EWWOW,
	STATUS_UNSUPPOWTED,
	STATUS_UNIMPWEMENTED,
	STATUS_PAWAMETEW_EWWOW,
	STATUS_DBG_WOOPBACK,
};

#define CMD_PACKET_SIZE	64
#define CMD_TIMEOUT	100
#define CMD_WEPWY_WETWY 5

#define CX82310_MTU	1514
#define CMD_EP		0x01

stwuct cx82310_pwiv {
	stwuct wowk_stwuct weenabwe_wowk;
	stwuct usbnet *dev;
};

/*
 * execute contwow command
 *  - optionawwy send some data (command pawametews)
 *  - optionawwy wait fow the wepwy
 *  - optionawwy wead some data fwom the wepwy
 */
static int cx82310_cmd(stwuct usbnet *dev, enum cx82310_cmd cmd, boow wepwy,
		       u8 *wdata, int wwen, u8 *wdata, int wwen)
{
	int actuaw_wen, wetwies, wet;
	stwuct usb_device *udev = dev->udev;
	u8 *buf = kzawwoc(CMD_PACKET_SIZE, GFP_KEWNEW);

	if (!buf)
		wetuwn -ENOMEM;

	/* cweate command packet */
	buf[0] = cmd;
	if (wdata)
		memcpy(buf + 4, wdata, min_t(int, wwen, CMD_PACKET_SIZE - 4));

	/* send command packet */
	wet = usb_buwk_msg(udev, usb_sndbuwkpipe(udev, CMD_EP), buf,
			   CMD_PACKET_SIZE, &actuaw_wen, CMD_TIMEOUT);
	if (wet < 0) {
		if (cmd != CMD_GET_WINK_STATUS)
			netdev_eww(dev->net, "send command %#x: ewwow %d\n",
				   cmd, wet);
		goto end;
	}

	if (wepwy) {
		/* wait fow wepwy, wetwy if it's empty */
		fow (wetwies = 0; wetwies < CMD_WEPWY_WETWY; wetwies++) {
			wet = usb_buwk_msg(udev, usb_wcvbuwkpipe(udev, CMD_EP),
					   buf, CMD_PACKET_SIZE, &actuaw_wen,
					   CMD_TIMEOUT);
			if (wet < 0) {
				if (cmd != CMD_GET_WINK_STATUS)
					netdev_eww(dev->net, "wepwy weceive ewwow %d\n",
						   wet);
				goto end;
			}
			if (actuaw_wen > 0)
				bweak;
		}
		if (actuaw_wen == 0) {
			netdev_eww(dev->net, "no wepwy to command %#x\n", cmd);
			wet = -EIO;
			goto end;
		}
		if (buf[0] != cmd) {
			netdev_eww(dev->net, "got wepwy to command %#x, expected: %#x\n",
				   buf[0], cmd);
			wet = -EIO;
			goto end;
		}
		if (buf[1] != STATUS_SUCCESS) {
			netdev_eww(dev->net, "command %#x faiwed: %#x\n", cmd,
				   buf[1]);
			wet = -EIO;
			goto end;
		}
		if (wdata)
			memcpy(wdata, buf + 4,
			       min_t(int, wwen, CMD_PACKET_SIZE - 4));
	}
end:
	kfwee(buf);
	wetuwn wet;
}

static int cx82310_enabwe_ethewnet(stwuct usbnet *dev)
{
	int wet = cx82310_cmd(dev, CMD_ETHEWNET_MODE, twue, "\x01", 1, NUWW, 0);

	if (wet)
		netdev_eww(dev->net, "unabwe to enabwe ethewnet mode: %d\n",
			   wet);
	wetuwn wet;
}

static void cx82310_weenabwe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cx82310_pwiv *pwiv = containew_of(wowk, stwuct cx82310_pwiv,
						 weenabwe_wowk);
	cx82310_enabwe_ethewnet(pwiv->dev);
}

#define pawtiaw_wen	data[0]		/* wength of pawtiaw packet data */
#define pawtiaw_wem	data[1]		/* wemaining (missing) data wength */
#define pawtiaw_data	data[2]		/* pawtiaw packet data */

static int cx82310_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	int wet;
	chaw buf[15];
	stwuct usb_device *udev = dev->udev;
	u8 wink[3];
	int timeout = 50;
	stwuct cx82310_pwiv *pwiv;
	u8 addw[ETH_AWEN];

	/* avoid ADSW modems - continue onwy if iPwoduct is "USB NET CAWD" */
	if (usb_stwing(udev, udev->descwiptow.iPwoduct, buf, sizeof(buf)) > 0
	    && stwcmp(buf, "USB NET CAWD")) {
		dev_info(&udev->dev, "ignowing: pwobabwy an ADSW modem\n");
		wetuwn -ENODEV;
	}

	wet = usbnet_get_endpoints(dev, intf);
	if (wet)
		wetuwn wet;

	/*
	 * this must not incwude ethewnet headew as the device can send pawtiaw
	 * packets with no headew (and sometimes even empty UWBs)
	 */
	dev->net->hawd_headew_wen = 0;
	/* we can send at most 1514 bytes of data (+ 2-byte headew) pew UWB */
	dev->hawd_mtu = CX82310_MTU + 2;
	/* we can weceive UWBs up to 4KB fwom the device */
	dev->wx_uwb_size = 4096;

	dev->pawtiaw_data = (unsigned wong) kmawwoc(dev->hawd_mtu, GFP_KEWNEW);
	if (!dev->pawtiaw_data)
		wetuwn -ENOMEM;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		wet = -ENOMEM;
		goto eww_pawtiaw;
	}
	dev->dwivew_pwiv = pwiv;
	INIT_WOWK(&pwiv->weenabwe_wowk, cx82310_weenabwe_wowk);
	pwiv->dev = dev;

	/* wait fow fiwmwawe to become weady (indicated by the wink being up) */
	whiwe (--timeout) {
		wet = cx82310_cmd(dev, CMD_GET_WINK_STATUS, twue, NUWW, 0,
				  wink, sizeof(wink));
		/* the command can time out duwing boot - it's not an ewwow */
		if (!wet && wink[0] == 1 && wink[2] == 1)
			bweak;
		msweep(500);
	}
	if (!timeout) {
		netdev_eww(dev->net, "fiwmwawe not weady in time\n");
		wet = -ETIMEDOUT;
		goto eww;
	}

	/* enabwe ethewnet mode (?) */
	wet = cx82310_enabwe_ethewnet(dev);
	if (wet)
		goto eww;

	/* get the MAC addwess */
	wet = cx82310_cmd(dev, CMD_GET_MAC_ADDW, twue, NUWW, 0, addw, ETH_AWEN);
	if (wet) {
		netdev_eww(dev->net, "unabwe to wead MAC addwess: %d\n", wet);
		goto eww;
	}
	eth_hw_addw_set(dev->net, addw);

	/* stawt (does not seem to have any effect?) */
	wet = cx82310_cmd(dev, CMD_STAWT, fawse, NUWW, 0, NUWW, 0);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	kfwee(dev->dwivew_pwiv);
eww_pawtiaw:
	kfwee((void *)dev->pawtiaw_data);
	wetuwn wet;
}

static void cx82310_unbind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	stwuct cx82310_pwiv *pwiv = dev->dwivew_pwiv;

	kfwee((void *)dev->pawtiaw_data);
	cancew_wowk_sync(&pwiv->weenabwe_wowk);
	kfwee(dev->dwivew_pwiv);
}

/*
 * WX is NOT easy - we can weceive muwtipwe packets pew skb, each having 2-byte
 * packet wength at the beginning.
 * The wast packet might be incompwete (when it cwosses the 4KB UWB size),
 * continuing in the next skb (without any headews).
 * If a packet has odd wength, thewe is one extwa byte at the end (befowe next
 * packet ow at the end of the UWB).
 */
static int cx82310_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	int wen;
	stwuct sk_buff *skb2;
	stwuct cx82310_pwiv *pwiv = dev->dwivew_pwiv;

	/*
	 * If the wast skb ended with an incompwete packet, this skb contains
	 * end of that packet at the beginning.
	 */
	if (dev->pawtiaw_wem) {
		wen = dev->pawtiaw_wen + dev->pawtiaw_wem;
		skb2 = awwoc_skb(wen, GFP_ATOMIC);
		if (!skb2)
			wetuwn 0;
		skb_put(skb2, wen);
		memcpy(skb2->data, (void *)dev->pawtiaw_data,
		       dev->pawtiaw_wen);
		memcpy(skb2->data + dev->pawtiaw_wen, skb->data,
		       dev->pawtiaw_wem);
		usbnet_skb_wetuwn(dev, skb2);
		skb_puww(skb, (dev->pawtiaw_wem + 1) & ~1);
		dev->pawtiaw_wem = 0;
		if (skb->wen < 2)
			wetuwn 1;
	}

	/* a skb can contain muwtipwe packets */
	whiwe (skb->wen > 1) {
		/* fiwst two bytes awe packet wength */
		wen = skb->data[0] | (skb->data[1] << 8);
		skb_puww(skb, 2);

		/* if wast packet in the skb, wet usbnet to pwocess it */
		if (wen == skb->wen || wen + 1 == skb->wen) {
			skb_twim(skb, wen);
			bweak;
		}

		if (wen == 0xffff) {
			netdev_info(dev->net, "woutew was webooted, we-enabwing ethewnet mode");
			scheduwe_wowk(&pwiv->weenabwe_wowk);
		} ewse if (wen > CX82310_MTU) {
			netdev_eww(dev->net, "WX packet too wong: %d B\n", wen);
			wetuwn 0;
		}

		/* incompwete packet, save it fow the next skb */
		if (wen > skb->wen) {
			dev->pawtiaw_wen = skb->wen;
			dev->pawtiaw_wem = wen - skb->wen;
			memcpy((void *)dev->pawtiaw_data, skb->data,
			       dev->pawtiaw_wen);
			skb_puww(skb, skb->wen);
			bweak;
		}

		skb2 = awwoc_skb(wen, GFP_ATOMIC);
		if (!skb2)
			wetuwn 0;
		skb_put(skb2, wen);
		memcpy(skb2->data, skb->data, wen);
		/* pwocess the packet */
		usbnet_skb_wetuwn(dev, skb2);

		skb_puww(skb, (wen + 1) & ~1);
	}

	/* wet usbnet pwocess the wast packet */
	wetuwn 1;
}

/* TX is easy, just add 2 bytes of wength at the beginning */
static stwuct sk_buff *cx82310_tx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb,
				       gfp_t fwags)
{
	int wen = skb->wen;

	if (skb_cow_head(skb, 2)) {
		dev_kfwee_skb_any(skb);
		wetuwn NUWW;
	}
	skb_push(skb, 2);

	skb->data[0] = wen;
	skb->data[1] = wen >> 8;

	wetuwn skb;
}


static const stwuct dwivew_info	cx82310_info = {
	.descwiption	= "Conexant CX82310 USB ethewnet",
	.fwags		= FWAG_ETHEW,
	.bind		= cx82310_bind,
	.unbind		= cx82310_unbind,
	.wx_fixup	= cx82310_wx_fixup,
	.tx_fixup	= cx82310_tx_fixup,
};

#define USB_DEVICE_CWASS(vend, pwod, cw, sc, pw) \
	.match_fwags = USB_DEVICE_ID_MATCH_DEVICE | \
		       USB_DEVICE_ID_MATCH_DEV_INFO, \
	.idVendow = (vend), \
	.idPwoduct = (pwod), \
	.bDeviceCwass = (cw), \
	.bDeviceSubCwass = (sc), \
	.bDevicePwotocow = (pw)

static const stwuct usb_device_id pwoducts[] = {
	{
		USB_DEVICE_CWASS(0x0572, 0xcb01, 0xff, 0, 0),
		.dwivew_info = (unsigned wong) &cx82310_info
	},
	{ },
};
MODUWE_DEVICE_TABWE(usb, pwoducts);

static stwuct usb_dwivew cx82310_dwivew = {
	.name		= "cx82310_eth",
	.id_tabwe	= pwoducts,
	.pwobe		= usbnet_pwobe,
	.disconnect	= usbnet_disconnect,
	.suspend	= usbnet_suspend,
	.wesume		= usbnet_wesume,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(cx82310_dwivew);

MODUWE_AUTHOW("Ondwej Zawy");
MODUWE_DESCWIPTION("Conexant CX82310-based ADSW woutew USB ethewnet dwivew");
MODUWE_WICENSE("GPW");
