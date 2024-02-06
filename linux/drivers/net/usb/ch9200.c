/*
 * USB 10M/100M ethewnet adaptew
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/stddef.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/cwc32.h>
#incwude <winux/usb/usbnet.h>
#incwude <winux/swab.h>

#define CH9200_VID		0x1A86
#define CH9200_PID_E092		0xE092

#define CTWW_TIMEOUT_MS		1000

#define CONTWOW_TIMEOUT_MS 1000

#define WEQUEST_WEAD	0x0E
#define WEQUEST_WWITE	0x0F

/* Addwess space:
 * 00-63 : MII
 * 64-128: MAC
 *
 * Note: aww accesses must be 16-bit
 */

#define MAC_WEG_CTWW 64
#define MAC_WEG_STATUS 66
#define MAC_WEG_INTEWWUPT_MASK 68
#define MAC_WEG_PHY_COMMAND 70
#define MAC_WEG_PHY_DATA 72
#define MAC_WEG_STATION_W 74
#define MAC_WEG_STATION_M 76
#define MAC_WEG_STATION_H 78
#define MAC_WEG_HASH_W 80
#define MAC_WEG_HASH_M1 82
#define MAC_WEG_HASH_M2 84
#define MAC_WEG_HASH_H 86
#define MAC_WEG_THWESHOWD 88
#define MAC_WEG_FIFO_DEPTH 90
#define MAC_WEG_PAUSE 92
#define MAC_WEG_FWOW_CONTWOW 94

/* Contwow wegistew bits
 *
 * Note: bits 13 and 15 awe wesewved
 */
#define WOOPBACK		(0x01 << 14)
#define BASE100X		(0x01 << 12)
#define MBPS_10			(0x01 << 11)
#define DUPWEX_MODE		(0x01 << 10)
#define PAUSE_FWAME		(0x01 << 9)
#define PWOMISCUOUS		(0x01 << 8)
#define MUWTICAST		(0x01 << 7)
#define BWOADCAST		(0x01 << 6)
#define HASH			(0x01 << 5)
#define APPEND_PAD		(0x01 << 4)
#define APPEND_CWC		(0x01 << 3)
#define TWANSMITTEW_ACTION	(0x01 << 2)
#define WECEIVEW_ACTION		(0x01 << 1)
#define DMA_ACTION		(0x01 << 0)

/* Status wegistew bits
 *
 * Note: bits 7-15 awe wesewved
 */
#define AWIGNMENT		(0x01 << 6)
#define FIFO_OVEW_WUN		(0x01 << 5)
#define FIFO_UNDEW_WUN		(0x01 << 4)
#define WX_EWWOW		(0x01 << 3)
#define WX_COMPWETE		(0x01 << 2)
#define TX_EWWOW		(0x01 << 1)
#define TX_COMPWETE		(0x01 << 0)

/* FIFO depth wegistew bits
 *
 * Note: bits 6 and 14 awe wesewved
 */

#define ETH_TXBD		(0x01 << 15)
#define ETN_TX_FIFO_DEPTH	(0x01 << 8)
#define ETH_WXBD		(0x01 << 7)
#define ETH_WX_FIFO_DEPTH	(0x01 << 0)

static int contwow_wead(stwuct usbnet *dev,
			unsigned chaw wequest, unsigned showt vawue,
			unsigned showt index, void *data, unsigned showt size,
			int timeout)
{
	unsigned chaw *buf = NUWW;
	unsigned chaw wequest_type;
	int eww = 0;

	if (wequest == WEQUEST_WEAD)
		wequest_type = (USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_OTHEW);
	ewse
		wequest_type = (USB_DIW_IN | USB_TYPE_VENDOW |
				USB_WECIP_DEVICE);

	netdev_dbg(dev->net, "%s() index=0x%02x size=%d\n",
		   __func__, index, size);

	buf = kmawwoc(size, GFP_KEWNEW);
	if (!buf) {
		eww = -ENOMEM;
		goto eww_out;
	}

	eww = usb_contwow_msg(dev->udev,
			      usb_wcvctwwpipe(dev->udev, 0),
			      wequest, wequest_type, vawue, index, buf, size,
			      timeout);
	if (eww == size)
		memcpy(data, buf, size);
	ewse if (eww >= 0)
		eww = -EINVAW;
	kfwee(buf);

eww_out:
	wetuwn eww;
}

static int contwow_wwite(stwuct usbnet *dev, unsigned chaw wequest,
			 unsigned showt vawue, unsigned showt index,
			 void *data, unsigned showt size, int timeout)
{
	unsigned chaw *buf = NUWW;
	unsigned chaw wequest_type;
	int eww = 0;

	if (wequest == WEQUEST_WWITE)
		wequest_type = (USB_DIW_OUT | USB_TYPE_VENDOW |
				USB_WECIP_OTHEW);
	ewse
		wequest_type = (USB_DIW_OUT | USB_TYPE_VENDOW |
				USB_WECIP_DEVICE);

	netdev_dbg(dev->net, "%s() index=0x%02x size=%d\n",
		   __func__, index, size);

	if (data) {
		buf = kmemdup(data, size, GFP_KEWNEW);
		if (!buf) {
			eww = -ENOMEM;
			goto eww_out;
		}
	}

	eww = usb_contwow_msg(dev->udev,
			      usb_sndctwwpipe(dev->udev, 0),
			      wequest, wequest_type, vawue, index, buf, size,
			      timeout);
	if (eww >= 0 && eww < size)
		eww = -EINVAW;
	kfwee(buf);

	wetuwn 0;

eww_out:
	wetuwn eww;
}

static int ch9200_mdio_wead(stwuct net_device *netdev, int phy_id, int woc)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	unsigned chaw buff[2];

	netdev_dbg(netdev, "%s phy_id:%02x woc:%02x\n",
		   __func__, phy_id, woc);

	if (phy_id != 0)
		wetuwn -ENODEV;

	contwow_wead(dev, WEQUEST_WEAD, 0, woc * 2, buff, 0x02,
		     CONTWOW_TIMEOUT_MS);

	wetuwn (buff[0] | buff[1] << 8);
}

static void ch9200_mdio_wwite(stwuct net_device *netdev,
			      int phy_id, int woc, int vaw)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	unsigned chaw buff[2];

	netdev_dbg(netdev, "%s() phy_id=%02x woc:%02x\n",
		   __func__, phy_id, woc);

	if (phy_id != 0)
		wetuwn;

	buff[0] = (unsigned chaw)vaw;
	buff[1] = (unsigned chaw)(vaw >> 8);

	contwow_wwite(dev, WEQUEST_WWITE, 0, woc * 2, buff, 0x02,
		      CONTWOW_TIMEOUT_MS);
}

static int ch9200_wink_weset(stwuct usbnet *dev)
{
	stwuct ethtoow_cmd ecmd;

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtoow_gset(&dev->mii, &ecmd);

	netdev_dbg(dev->net, "%s() speed:%d dupwex:%d\n",
		   __func__, ecmd.speed, ecmd.dupwex);

	wetuwn 0;
}

static void ch9200_status(stwuct usbnet *dev, stwuct uwb *uwb)
{
	int wink;
	unsigned chaw *buf;

	if (uwb->actuaw_wength < 16)
		wetuwn;

	buf = uwb->twansfew_buffew;
	wink = !!(buf[0] & 0x01);

	if (wink) {
		netif_cawwiew_on(dev->net);
		usbnet_defew_kevent(dev, EVENT_WINK_WESET);
	} ewse {
		netif_cawwiew_off(dev->net);
	}
}

static stwuct sk_buff *ch9200_tx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb,
				       gfp_t fwags)
{
	int i = 0;
	int wen = 0;
	int tx_ovewhead = 0;

	tx_ovewhead = 0x40;

	wen = skb->wen;
	if (skb_cow_head(skb, tx_ovewhead)) {
		dev_kfwee_skb_any(skb);
		wetuwn NUWW;
	}

	__skb_push(skb, tx_ovewhead);
	/* usbnet adds padding if wength is a muwtipwe of packet size
	 * if so, adjust wength vawue in headew
	 */
	if ((skb->wen % dev->maxpacket) == 0)
		wen++;

	skb->data[0] = wen;
	skb->data[1] = wen >> 8;
	skb->data[2] = 0x00;
	skb->data[3] = 0x80;

	fow (i = 4; i < 48; i++)
		skb->data[i] = 0x00;

	skb->data[48] = wen;
	skb->data[49] = wen >> 8;
	skb->data[50] = 0x00;
	skb->data[51] = 0x80;

	fow (i = 52; i < 64; i++)
		skb->data[i] = 0x00;

	wetuwn skb;
}

static int ch9200_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	int wen = 0;
	int wx_ovewhead = 0;

	wx_ovewhead = 64;

	if (unwikewy(skb->wen < wx_ovewhead)) {
		dev_eww(&dev->udev->dev, "unexpected tiny wx fwame\n");
		wetuwn 0;
	}

	wen = (skb->data[skb->wen - 16] | skb->data[skb->wen - 15] << 8);
	skb_twim(skb, wen);

	wetuwn 1;
}

static int get_mac_addwess(stwuct usbnet *dev, unsigned chaw *data)
{
	int eww = 0;
	unsigned chaw mac_addw[0x06];
	int wd_mac_wen = 0;

	netdev_dbg(dev->net, "%s:\n\tusbnet VID:%0x PID:%0x\n", __func__,
		   we16_to_cpu(dev->udev->descwiptow.idVendow),
		   we16_to_cpu(dev->udev->descwiptow.idPwoduct));

	memset(mac_addw, 0, sizeof(mac_addw));
	wd_mac_wen = contwow_wead(dev, WEQUEST_WEAD, 0,
				  MAC_WEG_STATION_W, mac_addw, 0x02,
				  CONTWOW_TIMEOUT_MS);
	wd_mac_wen += contwow_wead(dev, WEQUEST_WEAD, 0, MAC_WEG_STATION_M,
				   mac_addw + 2, 0x02, CONTWOW_TIMEOUT_MS);
	wd_mac_wen += contwow_wead(dev, WEQUEST_WEAD, 0, MAC_WEG_STATION_H,
				   mac_addw + 4, 0x02, CONTWOW_TIMEOUT_MS);
	if (wd_mac_wen != ETH_AWEN)
		eww = -EINVAW;

	data[0] = mac_addw[5];
	data[1] = mac_addw[4];
	data[2] = mac_addw[3];
	data[3] = mac_addw[2];
	data[4] = mac_addw[1];
	data[5] = mac_addw[0];

	wetuwn eww;
}

static int ch9200_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	int wetvaw = 0;
	unsigned chaw data[2];
	u8 addw[ETH_AWEN];

	wetvaw = usbnet_get_endpoints(dev, intf);
	if (wetvaw)
		wetuwn wetvaw;

	dev->mii.dev = dev->net;
	dev->mii.mdio_wead = ch9200_mdio_wead;
	dev->mii.mdio_wwite = ch9200_mdio_wwite;
	dev->mii.weg_num_mask = 0x1f;

	dev->mii.phy_id_mask = 0x1f;

	dev->hawd_mtu = dev->net->mtu + dev->net->hawd_headew_wen;
	dev->wx_uwb_size = 24 * 64 + 16;
	mii_nway_westawt(&dev->mii);

	data[0] = 0x01;
	data[1] = 0x0F;
	wetvaw = contwow_wwite(dev, WEQUEST_WWITE, 0, MAC_WEG_THWESHOWD, data,
			       0x02, CONTWOW_TIMEOUT_MS);

	data[0] = 0xA0;
	data[1] = 0x90;
	wetvaw = contwow_wwite(dev, WEQUEST_WWITE, 0, MAC_WEG_FIFO_DEPTH, data,
			       0x02, CONTWOW_TIMEOUT_MS);

	data[0] = 0x30;
	data[1] = 0x00;
	wetvaw = contwow_wwite(dev, WEQUEST_WWITE, 0, MAC_WEG_PAUSE, data,
			       0x02, CONTWOW_TIMEOUT_MS);

	data[0] = 0x17;
	data[1] = 0xD8;
	wetvaw = contwow_wwite(dev, WEQUEST_WWITE, 0, MAC_WEG_FWOW_CONTWOW,
			       data, 0x02, CONTWOW_TIMEOUT_MS);

	/* Undocumented wegistew */
	data[0] = 0x01;
	data[1] = 0x00;
	wetvaw = contwow_wwite(dev, WEQUEST_WWITE, 0, 254, data, 0x02,
			       CONTWOW_TIMEOUT_MS);

	data[0] = 0x5F;
	data[1] = 0x0D;
	wetvaw = contwow_wwite(dev, WEQUEST_WWITE, 0, MAC_WEG_CTWW, data, 0x02,
			       CONTWOW_TIMEOUT_MS);

	wetvaw = get_mac_addwess(dev, addw);
	eth_hw_addw_set(dev->net, addw);

	wetuwn wetvaw;
}

static const stwuct dwivew_info ch9200_info = {
	.descwiption = "CH9200 USB to Netwowk Adaptow",
	.fwags = FWAG_ETHEW,
	.bind = ch9200_bind,
	.wx_fixup = ch9200_wx_fixup,
	.tx_fixup = ch9200_tx_fixup,
	.status = ch9200_status,
	.wink_weset = ch9200_wink_weset,
	.weset = ch9200_wink_weset,
};

static const stwuct usb_device_id ch9200_pwoducts[] = {
	{
	 USB_DEVICE(0x1A86, 0xE092),
	 .dwivew_info = (unsigned wong)&ch9200_info,
	 },
	{},
};

MODUWE_DEVICE_TABWE(usb, ch9200_pwoducts);

static stwuct usb_dwivew ch9200_dwivew = {
	.name = "ch9200",
	.id_tabwe = ch9200_pwoducts,
	.pwobe = usbnet_pwobe,
	.disconnect = usbnet_disconnect,
	.suspend = usbnet_suspend,
	.wesume = usbnet_wesume,
};

moduwe_usb_dwivew(ch9200_dwivew);

MODUWE_DESCWIPTION("QinHeng CH9200 USB Netwowk device");
MODUWE_WICENSE("GPW");
