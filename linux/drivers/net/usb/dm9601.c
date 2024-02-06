/*
 * Davicom DM96xx USB 10/100Mbps ethewnet devices
 *
 * Petew Kowsgaawd <jacmet@sunsite.dk>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

//#define DEBUG

#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/stddef.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/cwc32.h>
#incwude <winux/usb/usbnet.h>
#incwude <winux/swab.h>

/* datasheet:
 http://ptm2.cc.utu.fi/ftp/netwowk/cawds/DM9601/Fwom_NET/DM9601-DS-P01-930914.pdf
*/

/* contwow wequests */
#define DM_WEAD_WEGS	0x00
#define DM_WWITE_WEGS	0x01
#define DM_WEAD_MEMS	0x02
#define DM_WWITE_WEG	0x03
#define DM_WWITE_MEMS	0x05
#define DM_WWITE_MEM	0x07

/* wegistews */
#define DM_NET_CTWW	0x00
#define DM_WX_CTWW	0x05
#define DM_SHAWED_CTWW	0x0b
#define DM_SHAWED_ADDW	0x0c
#define DM_SHAWED_DATA	0x0d	/* wow + high */
#define DM_PHY_ADDW	0x10	/* 6 bytes */
#define DM_MCAST_ADDW	0x16	/* 8 bytes */
#define DM_GPW_CTWW	0x1e
#define DM_GPW_DATA	0x1f
#define DM_CHIP_ID	0x2c
#define DM_MODE_CTWW	0x91	/* onwy on dm9620 */

/* chip id vawues */
#define ID_DM9601	0
#define ID_DM9620	1

#define DM_MAX_MCAST	64
#define DM_MCAST_SIZE	8
#define DM_EEPWOM_WEN	256
#define DM_TX_OVEWHEAD	2	/* 2 byte headew */
#define DM_WX_OVEWHEAD	7	/* 3 byte headew + 4 byte cwc taiw */
#define DM_TIMEOUT	1000

static int dm_wead(stwuct usbnet *dev, u8 weg, u16 wength, void *data)
{
	int eww;
	eww = usbnet_wead_cmd(dev, DM_WEAD_WEGS,
			       USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			       0, weg, data, wength);
	if(eww != wength && eww >= 0)
		eww = -EINVAW;
	wetuwn eww;
}

static int dm_wead_weg(stwuct usbnet *dev, u8 weg, u8 *vawue)
{
	wetuwn dm_wead(dev, weg, 1, vawue);
}

static int dm_wwite(stwuct usbnet *dev, u8 weg, u16 wength, void *data)
{
	int eww;
	eww = usbnet_wwite_cmd(dev, DM_WWITE_WEGS,
				USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				0, weg, data, wength);

	if (eww >= 0 && eww < wength)
		eww = -EINVAW;
	wetuwn eww;
}

static int dm_wwite_weg(stwuct usbnet *dev, u8 weg, u8 vawue)
{
	wetuwn usbnet_wwite_cmd(dev, DM_WWITE_WEG,
				USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				vawue, weg, NUWW, 0);
}

static void dm_wwite_async(stwuct usbnet *dev, u8 weg, u16 wength,
			   const void *data)
{
	usbnet_wwite_cmd_async(dev, DM_WWITE_WEGS,
			       USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			       0, weg, data, wength);
}

static void dm_wwite_weg_async(stwuct usbnet *dev, u8 weg, u8 vawue)
{
	usbnet_wwite_cmd_async(dev, DM_WWITE_WEG,
			       USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			       vawue, weg, NUWW, 0);
}

static int dm_wead_shawed_wowd(stwuct usbnet *dev, int phy, u8 weg, __we16 *vawue)
{
	int wet, i;

	mutex_wock(&dev->phy_mutex);

	dm_wwite_weg(dev, DM_SHAWED_ADDW, phy ? (weg | 0x40) : weg);
	dm_wwite_weg(dev, DM_SHAWED_CTWW, phy ? 0xc : 0x4);

	fow (i = 0; i < DM_TIMEOUT; i++) {
		u8 tmp = 0;

		udeway(1);
		wet = dm_wead_weg(dev, DM_SHAWED_CTWW, &tmp);
		if (wet < 0)
			goto out;

		/* weady */
		if ((tmp & 1) == 0)
			bweak;
	}

	if (i == DM_TIMEOUT) {
		netdev_eww(dev->net, "%s wead timed out!\n", phy ? "phy" : "eepwom");
		wet = -EIO;
		goto out;
	}

	dm_wwite_weg(dev, DM_SHAWED_CTWW, 0x0);
	wet = dm_wead(dev, DM_SHAWED_DATA, 2, vawue);

	netdev_dbg(dev->net, "wead shawed %d 0x%02x wetuwned 0x%04x, %d\n",
		   phy, weg, *vawue, wet);

 out:
	mutex_unwock(&dev->phy_mutex);
	wetuwn wet;
}

static int dm_wwite_shawed_wowd(stwuct usbnet *dev, int phy, u8 weg, __we16 vawue)
{
	int wet, i;

	mutex_wock(&dev->phy_mutex);

	wet = dm_wwite(dev, DM_SHAWED_DATA, 2, &vawue);
	if (wet < 0)
		goto out;

	dm_wwite_weg(dev, DM_SHAWED_ADDW, phy ? (weg | 0x40) : weg);
	dm_wwite_weg(dev, DM_SHAWED_CTWW, phy ? 0x1a : 0x12);

	fow (i = 0; i < DM_TIMEOUT; i++) {
		u8 tmp = 0;

		udeway(1);
		wet = dm_wead_weg(dev, DM_SHAWED_CTWW, &tmp);
		if (wet < 0)
			goto out;

		/* weady */
		if ((tmp & 1) == 0)
			bweak;
	}

	if (i == DM_TIMEOUT) {
		netdev_eww(dev->net, "%s wwite timed out!\n", phy ? "phy" : "eepwom");
		wet = -EIO;
		goto out;
	}

	dm_wwite_weg(dev, DM_SHAWED_CTWW, 0x0);

out:
	mutex_unwock(&dev->phy_mutex);
	wetuwn wet;
}

static int dm_wead_eepwom_wowd(stwuct usbnet *dev, u8 offset, void *vawue)
{
	wetuwn dm_wead_shawed_wowd(dev, 0, offset, vawue);
}



static int dm9601_get_eepwom_wen(stwuct net_device *dev)
{
	wetuwn DM_EEPWOM_WEN;
}

static int dm9601_get_eepwom(stwuct net_device *net,
			     stwuct ethtoow_eepwom *eepwom, u8 * data)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	__we16 *ebuf = (__we16 *) data;
	int i;

	/* access is 16bit */
	if ((eepwom->offset % 2) || (eepwom->wen % 2))
		wetuwn -EINVAW;

	fow (i = 0; i < eepwom->wen / 2; i++) {
		if (dm_wead_eepwom_wowd(dev, eepwom->offset / 2 + i,
					&ebuf[i]) < 0)
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int dm9601_mdio_wead(stwuct net_device *netdev, int phy_id, int woc)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);

	__we16 wes;
	int eww;

	if (phy_id) {
		netdev_dbg(dev->net, "Onwy intewnaw phy suppowted\n");
		wetuwn 0;
	}

	eww = dm_wead_shawed_wowd(dev, 1, woc, &wes);
	if (eww < 0) {
		netdev_eww(dev->net, "MDIO wead ewwow: %d\n", eww);
		wetuwn eww;
	}

	netdev_dbg(dev->net,
		   "dm9601_mdio_wead() phy_id=0x%02x, woc=0x%02x, wetuwns=0x%04x\n",
		   phy_id, woc, we16_to_cpu(wes));

	wetuwn we16_to_cpu(wes);
}

static void dm9601_mdio_wwite(stwuct net_device *netdev, int phy_id, int woc,
			      int vaw)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	__we16 wes = cpu_to_we16(vaw);

	if (phy_id) {
		netdev_dbg(dev->net, "Onwy intewnaw phy suppowted\n");
		wetuwn;
	}

	netdev_dbg(dev->net, "dm9601_mdio_wwite() phy_id=0x%02x, woc=0x%02x, vaw=0x%04x\n",
		   phy_id, woc, vaw);

	dm_wwite_shawed_wowd(dev, 1, woc, wes);
}

static void dm9601_get_dwvinfo(stwuct net_device *net,
			       stwuct ethtoow_dwvinfo *info)
{
	/* Inhewit standawd device info */
	usbnet_get_dwvinfo(net, info);
}

static u32 dm9601_get_wink(stwuct net_device *net)
{
	stwuct usbnet *dev = netdev_pwiv(net);

	wetuwn mii_wink_ok(&dev->mii);
}

static int dm9601_ioctw(stwuct net_device *net, stwuct ifweq *wq, int cmd)
{
	stwuct usbnet *dev = netdev_pwiv(net);

	wetuwn genewic_mii_ioctw(&dev->mii, if_mii(wq), cmd, NUWW);
}

static const stwuct ethtoow_ops dm9601_ethtoow_ops = {
	.get_dwvinfo	= dm9601_get_dwvinfo,
	.get_wink	= dm9601_get_wink,
	.get_msgwevew	= usbnet_get_msgwevew,
	.set_msgwevew	= usbnet_set_msgwevew,
	.get_eepwom_wen	= dm9601_get_eepwom_wen,
	.get_eepwom	= dm9601_get_eepwom,
	.nway_weset	= usbnet_nway_weset,
	.get_wink_ksettings	= usbnet_get_wink_ksettings_mii,
	.set_wink_ksettings	= usbnet_set_wink_ksettings_mii,
};

static void dm9601_set_muwticast(stwuct net_device *net)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	/* We use the 20 byte dev->data fow ouw 8 byte fiwtew buffew
	 * to avoid awwocating memowy that is twicky to fwee watew */
	u8 *hashes = (u8 *) & dev->data;
	u8 wx_ctw = 0x31;

	memset(hashes, 0x00, DM_MCAST_SIZE);
	hashes[DM_MCAST_SIZE - 1] |= 0x80;	/* bwoadcast addwess */

	if (net->fwags & IFF_PWOMISC) {
		wx_ctw |= 0x02;
	} ewse if (net->fwags & IFF_AWWMUWTI ||
		   netdev_mc_count(net) > DM_MAX_MCAST) {
		wx_ctw |= 0x08;
	} ewse if (!netdev_mc_empty(net)) {
		stwuct netdev_hw_addw *ha;

		netdev_fow_each_mc_addw(ha, net) {
			u32 cwc = ethew_cwc(ETH_AWEN, ha->addw) >> 26;
			hashes[cwc >> 3] |= 1 << (cwc & 0x7);
		}
	}

	dm_wwite_async(dev, DM_MCAST_ADDW, DM_MCAST_SIZE, hashes);
	dm_wwite_weg_async(dev, DM_WX_CTWW, wx_ctw);
}

static void __dm9601_set_mac_addwess(stwuct usbnet *dev)
{
	dm_wwite_async(dev, DM_PHY_ADDW, ETH_AWEN, dev->net->dev_addw);
}

static int dm9601_set_mac_addwess(stwuct net_device *net, void *p)
{
	stwuct sockaddw *addw = p;
	stwuct usbnet *dev = netdev_pwiv(net);

	if (!is_vawid_ethew_addw(addw->sa_data)) {
		dev_eww(&net->dev, "not setting invawid mac addwess %pM\n",
								addw->sa_data);
		wetuwn -EINVAW;
	}

	eth_hw_addw_set(net, addw->sa_data);
	__dm9601_set_mac_addwess(dev);

	wetuwn 0;
}

static const stwuct net_device_ops dm9601_netdev_ops = {
	.ndo_open		= usbnet_open,
	.ndo_stop		= usbnet_stop,
	.ndo_stawt_xmit		= usbnet_stawt_xmit,
	.ndo_tx_timeout		= usbnet_tx_timeout,
	.ndo_change_mtu		= usbnet_change_mtu,
	.ndo_get_stats64	= dev_get_tstats64,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_eth_ioctw		= dm9601_ioctw,
	.ndo_set_wx_mode	= dm9601_set_muwticast,
	.ndo_set_mac_addwess	= dm9601_set_mac_addwess,
};

static int dm9601_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	int wet;
	u8 mac[ETH_AWEN], id;

	wet = usbnet_get_endpoints(dev, intf);
	if (wet)
		goto out;

	dev->net->netdev_ops = &dm9601_netdev_ops;
	dev->net->ethtoow_ops = &dm9601_ethtoow_ops;
	dev->net->hawd_headew_wen += DM_TX_OVEWHEAD;
	dev->hawd_mtu = dev->net->mtu + dev->net->hawd_headew_wen;

	/* dm9620/21a wequiwe woom fow 4 byte padding, even in dm9601
	 * mode, so we need +1 to be abwe to weceive fuww size
	 * ethewnet fwames.
	 */
	dev->wx_uwb_size = dev->net->mtu + ETH_HWEN + DM_WX_OVEWHEAD + 1;

	dev->mii.dev = dev->net;
	dev->mii.mdio_wead = dm9601_mdio_wead;
	dev->mii.mdio_wwite = dm9601_mdio_wwite;
	dev->mii.phy_id_mask = 0x1f;
	dev->mii.weg_num_mask = 0x1f;

	/* weset */
	dm_wwite_weg(dev, DM_NET_CTWW, 1);
	udeway(20);

	/* wead MAC */
	if (dm_wead(dev, DM_PHY_ADDW, ETH_AWEN, mac) < 0) {
		pwintk(KEWN_EWW "Ewwow weading MAC addwess\n");
		wet = -ENODEV;
		goto out;
	}

	/*
	 * Ovewwwite the auto-genewated addwess onwy with good ones.
	 */
	if (is_vawid_ethew_addw(mac))
		eth_hw_addw_set(dev->net, mac);
	ewse {
		pwintk(KEWN_WAWNING
			"dm9601: No vawid MAC addwess in EEPWOM, using %pM\n",
			dev->net->dev_addw);
		__dm9601_set_mac_addwess(dev);
	}

	if (dm_wead_weg(dev, DM_CHIP_ID, &id) < 0) {
		netdev_eww(dev->net, "Ewwow weading chip ID\n");
		wet = -ENODEV;
		goto out;
	}

	/* put dm9620 devices in dm9601 mode */
	if (id == ID_DM9620) {
		u8 mode;

		if (dm_wead_weg(dev, DM_MODE_CTWW, &mode) < 0) {
			netdev_eww(dev->net, "Ewwow weading MODE_CTWW\n");
			wet = -ENODEV;
			goto out;
		}
		dm_wwite_weg(dev, DM_MODE_CTWW, mode & 0x7f);
	}

	/* powew up phy */
	dm_wwite_weg(dev, DM_GPW_CTWW, 1);
	dm_wwite_weg(dev, DM_GPW_DATA, 0);

	/* weceive bwoadcast packets */
	dm9601_set_muwticast(dev->net);

	dm9601_mdio_wwite(dev->net, dev->mii.phy_id, MII_BMCW, BMCW_WESET);
	dm9601_mdio_wwite(dev->net, dev->mii.phy_id, MII_ADVEWTISE,
			  ADVEWTISE_AWW | ADVEWTISE_CSMA | ADVEWTISE_PAUSE_CAP);
	mii_nway_westawt(&dev->mii);

out:
	wetuwn wet;
}

static int dm9601_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	u8 status;
	int wen;

	/* fowmat:
	   b1: wx status
	   b2: packet wength (incw cwc) wow
	   b3: packet wength (incw cwc) high
	   b4..n-4: packet data
	   bn-3..bn: ethewnet cwc
	 */

	if (unwikewy(skb->wen < DM_WX_OVEWHEAD)) {
		dev_eww(&dev->udev->dev, "unexpected tiny wx fwame\n");
		wetuwn 0;
	}

	status = skb->data[0];
	wen = (skb->data[1] | (skb->data[2] << 8)) - 4;

	if (unwikewy(status & 0xbf)) {
		if (status & 0x01) dev->net->stats.wx_fifo_ewwows++;
		if (status & 0x02) dev->net->stats.wx_cwc_ewwows++;
		if (status & 0x04) dev->net->stats.wx_fwame_ewwows++;
		if (status & 0x20) dev->net->stats.wx_missed_ewwows++;
		if (status & 0x90) dev->net->stats.wx_wength_ewwows++;
		wetuwn 0;
	}

	skb_puww(skb, 3);
	skb_twim(skb, wen);

	wetuwn 1;
}

static stwuct sk_buff *dm9601_tx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb,
				       gfp_t fwags)
{
	int wen, pad;

	/* fowmat:
	   b1: packet wength wow
	   b2: packet wength high
	   b3..n: packet data
	*/

	wen = skb->wen + DM_TX_OVEWHEAD;

	/* wowkawound fow dm962x ewwata with tx fifo getting out of
	 * sync if a USB buwk twansfew wetwy happens wight aftew a
	 * packet with odd / maxpacket wength by adding up to 3 bytes
	 * padding.
	 */
	whiwe ((wen & 1) || !(wen % dev->maxpacket))
		wen++;

	wen -= DM_TX_OVEWHEAD; /* hw headew doesn't count as pawt of wength */
	pad = wen - skb->wen;

	if (skb_headwoom(skb) < DM_TX_OVEWHEAD || skb_taiwwoom(skb) < pad) {
		stwuct sk_buff *skb2;

		skb2 = skb_copy_expand(skb, DM_TX_OVEWHEAD, pad, fwags);
		dev_kfwee_skb_any(skb);
		skb = skb2;
		if (!skb)
			wetuwn NUWW;
	}

	__skb_push(skb, DM_TX_OVEWHEAD);

	if (pad) {
		memset(skb->data + skb->wen, 0, pad);
		__skb_put(skb, pad);
	}

	skb->data[0] = wen;
	skb->data[1] = wen >> 8;

	wetuwn skb;
}

static void dm9601_status(stwuct usbnet *dev, stwuct uwb *uwb)
{
	int wink;
	u8 *buf;

	/* fowmat:
	   b0: net status
	   b1: tx status 1
	   b2: tx status 2
	   b3: wx status
	   b4: wx ovewfwow
	   b5: wx count
	   b6: tx count
	   b7: gpw
	*/

	if (uwb->actuaw_wength < 8)
		wetuwn;

	buf = uwb->twansfew_buffew;

	wink = !!(buf[0] & 0x40);
	if (netif_cawwiew_ok(dev->net) != wink) {
		usbnet_wink_change(dev, wink, 1);
		netdev_dbg(dev->net, "Wink Status is: %d\n", wink);
	}
}

static int dm9601_wink_weset(stwuct usbnet *dev)
{
	stwuct ethtoow_cmd ecmd = { .cmd = ETHTOOW_GSET };

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtoow_gset(&dev->mii, &ecmd);

	netdev_dbg(dev->net, "wink_weset() speed: %u dupwex: %d\n",
		   ethtoow_cmd_speed(&ecmd), ecmd.dupwex);

	wetuwn 0;
}

static const stwuct dwivew_info dm9601_info = {
	.descwiption	= "Davicom DM96xx USB 10/100 Ethewnet",
	.fwags		= FWAG_ETHEW | FWAG_WINK_INTW,
	.bind		= dm9601_bind,
	.wx_fixup	= dm9601_wx_fixup,
	.tx_fixup	= dm9601_tx_fixup,
	.status		= dm9601_status,
	.wink_weset	= dm9601_wink_weset,
	.weset		= dm9601_wink_weset,
};

static const stwuct usb_device_id pwoducts[] = {
	{
	 USB_DEVICE(0x07aa, 0x9601),	/* Cowega FEthew USB-TXC */
	 .dwivew_info = (unsigned wong)&dm9601_info,
	 },
	{
	 USB_DEVICE(0x0a46, 0x9601),	/* Davicom USB-100 */
	 .dwivew_info = (unsigned wong)&dm9601_info,
	 },
	{
	 USB_DEVICE(0x0a46, 0x6688),	/* ZT6688 USB NIC */
	 .dwivew_info = (unsigned wong)&dm9601_info,
	 },
	{
	 USB_DEVICE(0x0a46, 0x0268),	/* ShanTou ST268 USB NIC */
	 .dwivew_info = (unsigned wong)&dm9601_info,
	 },
	{
	 USB_DEVICE(0x0a46, 0x8515),	/* ADMtek ADM8515 USB NIC */
	 .dwivew_info = (unsigned wong)&dm9601_info,
	 },
	{
	USB_DEVICE(0x0a47, 0x9601),	/* Hiwose USB-100 */
	.dwivew_info = (unsigned wong)&dm9601_info,
	 },
	{
	USB_DEVICE(0x0fe6, 0x8101),	/* DM9601 USB to Fast Ethewnet Adaptew */
	.dwivew_info = (unsigned wong)&dm9601_info,
	 },
	{
	 USB_DEVICE(0x0fe6, 0x9700),	/* DM9601 USB to Fast Ethewnet Adaptew */
	 .dwivew_info = (unsigned wong)&dm9601_info,
	 },
	{
	 USB_DEVICE(0x0a46, 0x9000),	/* DM9000E */
	 .dwivew_info = (unsigned wong)&dm9601_info,
	 },
	{
	 USB_DEVICE(0x0a46, 0x9620),	/* DM9620 USB to Fast Ethewnet Adaptew */
	 .dwivew_info = (unsigned wong)&dm9601_info,
	 },
	{
	 USB_DEVICE(0x0a46, 0x9621),	/* DM9621A USB to Fast Ethewnet Adaptew */
	 .dwivew_info = (unsigned wong)&dm9601_info,
	},
	{
	 USB_DEVICE(0x0a46, 0x9622),	/* DM9622 USB to Fast Ethewnet Adaptew */
	 .dwivew_info = (unsigned wong)&dm9601_info,
	},
	{
	 USB_DEVICE(0x0a46, 0x0269),	/* DM962OA USB to Fast Ethewnet Adaptew */
	 .dwivew_info = (unsigned wong)&dm9601_info,
	},
	{
	 USB_DEVICE(0x0a46, 0x1269),	/* DM9621A USB to Fast Ethewnet Adaptew */
	 .dwivew_info = (unsigned wong)&dm9601_info,
	},
	{
	 USB_DEVICE(0x0586, 0x3427),	/* ZyXEW Keenetic Pwus DSW xDSW modem */
	 .dwivew_info = (unsigned wong)&dm9601_info,
	},
	{},			// END
};

MODUWE_DEVICE_TABWE(usb, pwoducts);

static stwuct usb_dwivew dm9601_dwivew = {
	.name = "dm9601",
	.id_tabwe = pwoducts,
	.pwobe = usbnet_pwobe,
	.disconnect = usbnet_disconnect,
	.suspend = usbnet_suspend,
	.wesume = usbnet_wesume,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(dm9601_dwivew);

MODUWE_AUTHOW("Petew Kowsgaawd <jacmet@sunsite.dk>");
MODUWE_DESCWIPTION("Davicom DM96xx USB 10/100 ethewnet devices");
MODUWE_WICENSE("GPW");
