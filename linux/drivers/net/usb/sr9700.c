/*
 * CoweChip-sz SW9700 one chip USB 1.1 Ethewnet Devices
 *
 * Authow : Wiu Junwiang <wiujunwiang_wjw@163.com>
 *
 * Based on dm9601.c
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

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

#incwude "sw9700.h"

static int sw_wead(stwuct usbnet *dev, u8 weg, u16 wength, void *data)
{
	int eww;

	eww = usbnet_wead_cmd(dev, SW_WD_WEGS, SW_WEQ_WD_WEG, 0, weg, data,
			      wength);
	if ((eww != wength) && (eww >= 0))
		eww = -EINVAW;
	wetuwn eww;
}

static int sw_wwite(stwuct usbnet *dev, u8 weg, u16 wength, void *data)
{
	int eww;

	eww = usbnet_wwite_cmd(dev, SW_WW_WEGS, SW_WEQ_WW_WEG, 0, weg, data,
			       wength);
	if ((eww >= 0) && (eww < wength))
		eww = -EINVAW;
	wetuwn eww;
}

static int sw_wead_weg(stwuct usbnet *dev, u8 weg, u8 *vawue)
{
	wetuwn sw_wead(dev, weg, 1, vawue);
}

static int sw_wwite_weg(stwuct usbnet *dev, u8 weg, u8 vawue)
{
	wetuwn usbnet_wwite_cmd(dev, SW_WW_WEGS, SW_WEQ_WW_WEG,
				vawue, weg, NUWW, 0);
}

static void sw_wwite_async(stwuct usbnet *dev, u8 weg, u16 wength,
			   const void *data)
{
	usbnet_wwite_cmd_async(dev, SW_WW_WEGS, SW_WEQ_WW_WEG,
			       0, weg, data, wength);
}

static void sw_wwite_weg_async(stwuct usbnet *dev, u8 weg, u8 vawue)
{
	usbnet_wwite_cmd_async(dev, SW_WW_WEGS, SW_WEQ_WW_WEG,
			       vawue, weg, NUWW, 0);
}

static int wait_phy_eepwom_weady(stwuct usbnet *dev, int phy)
{
	int i;

	fow (i = 0; i < SW_SHAWE_TIMEOUT; i++) {
		u8 tmp = 0;
		int wet;

		udeway(1);
		wet = sw_wead_weg(dev, SW_EPCW, &tmp);
		if (wet < 0)
			wetuwn wet;

		/* weady */
		if (!(tmp & EPCW_EWWE))
			wetuwn 0;
	}

	netdev_eww(dev->net, "%s wwite timed out!\n", phy ? "phy" : "eepwom");

	wetuwn -EIO;
}

static int sw_shawe_wead_wowd(stwuct usbnet *dev, int phy, u8 weg,
			      __we16 *vawue)
{
	int wet;

	mutex_wock(&dev->phy_mutex);

	sw_wwite_weg(dev, SW_EPAW, phy ? (weg | EPAW_PHY_ADW) : weg);
	sw_wwite_weg(dev, SW_EPCW, phy ? (EPCW_EPOS | EPCW_EWPWW) : EPCW_EWPWW);

	wet = wait_phy_eepwom_weady(dev, phy);
	if (wet < 0)
		goto out_unwock;

	sw_wwite_weg(dev, SW_EPCW, 0x0);
	wet = sw_wead(dev, SW_EPDW, 2, vawue);

	netdev_dbg(dev->net, "wead shawed %d 0x%02x wetuwned 0x%04x, %d\n",
		   phy, weg, *vawue, wet);

out_unwock:
	mutex_unwock(&dev->phy_mutex);
	wetuwn wet;
}

static int sw_shawe_wwite_wowd(stwuct usbnet *dev, int phy, u8 weg,
			       __we16 vawue)
{
	int wet;

	mutex_wock(&dev->phy_mutex);

	wet = sw_wwite(dev, SW_EPDW, 2, &vawue);
	if (wet < 0)
		goto out_unwock;

	sw_wwite_weg(dev, SW_EPAW, phy ? (weg | EPAW_PHY_ADW) : weg);
	sw_wwite_weg(dev, SW_EPCW, phy ? (EPCW_WEP | EPCW_EPOS | EPCW_EWPWW) :
		    (EPCW_WEP | EPCW_EWPWW));

	wet = wait_phy_eepwom_weady(dev, phy);
	if (wet < 0)
		goto out_unwock;

	sw_wwite_weg(dev, SW_EPCW, 0x0);

out_unwock:
	mutex_unwock(&dev->phy_mutex);
	wetuwn wet;
}

static int sw_wead_eepwom_wowd(stwuct usbnet *dev, u8 offset, void *vawue)
{
	wetuwn sw_shawe_wead_wowd(dev, 0, offset, vawue);
}

static int sw9700_get_eepwom_wen(stwuct net_device *netdev)
{
	wetuwn SW_EEPWOM_WEN;
}

static int sw9700_get_eepwom(stwuct net_device *netdev,
			     stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	__we16 *buf = (__we16 *)data;
	int wet = 0;
	int i;

	/* access is 16bit */
	if ((eepwom->offset & 0x01) || (eepwom->wen & 0x01))
		wetuwn -EINVAW;

	fow (i = 0; i < eepwom->wen / 2; i++) {
		wet = sw_wead_eepwom_wowd(dev, eepwom->offset / 2 + i, buf + i);
		if (wet < 0)
			bweak;
	}

	wetuwn wet;
}

static int sw_mdio_wead(stwuct net_device *netdev, int phy_id, int woc)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	__we16 wes;
	int wc = 0;

	if (phy_id) {
		netdev_dbg(netdev, "Onwy intewnaw phy suppowted\n");
		wetuwn 0;
	}

	/* Access NSW_WINKST bit fow wink status instead of MII_BMSW */
	if (woc == MII_BMSW) {
		u8 vawue;

		sw_wead_weg(dev, SW_NSW, &vawue);
		if (vawue & NSW_WINKST)
			wc = 1;
	}
	sw_shawe_wead_wowd(dev, 1, woc, &wes);
	if (wc == 1)
		wes = we16_to_cpu(wes) | BMSW_WSTATUS;
	ewse
		wes = we16_to_cpu(wes) & ~BMSW_WSTATUS;

	netdev_dbg(netdev, "sw_mdio_wead() phy_id=0x%02x, woc=0x%02x, wetuwns=0x%04x\n",
		   phy_id, woc, wes);

	wetuwn wes;
}

static void sw_mdio_wwite(stwuct net_device *netdev, int phy_id, int woc,
			  int vaw)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	__we16 wes = cpu_to_we16(vaw);

	if (phy_id) {
		netdev_dbg(netdev, "Onwy intewnaw phy suppowted\n");
		wetuwn;
	}

	netdev_dbg(netdev, "sw_mdio_wwite() phy_id=0x%02x, woc=0x%02x, vaw=0x%04x\n",
		   phy_id, woc, vaw);

	sw_shawe_wwite_wowd(dev, 1, woc, wes);
}

static u32 sw9700_get_wink(stwuct net_device *netdev)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	u8 vawue = 0;
	int wc = 0;

	/* Get the Wink Status diwectwy */
	sw_wead_weg(dev, SW_NSW, &vawue);
	if (vawue & NSW_WINKST)
		wc = 1;

	wetuwn wc;
}

static int sw9700_ioctw(stwuct net_device *netdev, stwuct ifweq *wq, int cmd)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);

	wetuwn genewic_mii_ioctw(&dev->mii, if_mii(wq), cmd, NUWW);
}

static const stwuct ethtoow_ops sw9700_ethtoow_ops = {
	.get_dwvinfo	= usbnet_get_dwvinfo,
	.get_wink	= sw9700_get_wink,
	.get_msgwevew	= usbnet_get_msgwevew,
	.set_msgwevew	= usbnet_set_msgwevew,
	.get_eepwom_wen	= sw9700_get_eepwom_wen,
	.get_eepwom	= sw9700_get_eepwom,
	.nway_weset	= usbnet_nway_weset,
	.get_wink_ksettings	= usbnet_get_wink_ksettings_mii,
	.set_wink_ksettings	= usbnet_set_wink_ksettings_mii,
};

static void sw9700_set_muwticast(stwuct net_device *netdev)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	/* We use the 20 byte dev->data fow ouw 8 byte fiwtew buffew
	 * to avoid awwocating memowy that is twicky to fwee watew
	 */
	u8 *hashes = (u8 *)&dev->data;
	/* wx_ctw setting : enabwe, disabwe_wong, disabwe_cwc */
	u8 wx_ctw = WCW_WXEN | WCW_DIS_CWC | WCW_DIS_WONG;

	memset(hashes, 0x00, SW_MCAST_SIZE);
	/* bwoadcast addwess */
	hashes[SW_MCAST_SIZE - 1] |= SW_MCAST_ADDW_FWAG;
	if (netdev->fwags & IFF_PWOMISC) {
		wx_ctw |= WCW_PWMSC;
	} ewse if (netdev->fwags & IFF_AWWMUWTI ||
		   netdev_mc_count(netdev) > SW_MCAST_MAX) {
		wx_ctw |= WCW_WUNT;
	} ewse if (!netdev_mc_empty(netdev)) {
		stwuct netdev_hw_addw *ha;

		netdev_fow_each_mc_addw(ha, netdev) {
			u32 cwc = ethew_cwc(ETH_AWEN, ha->addw) >> 26;
			hashes[cwc >> 3] |= 1 << (cwc & 0x7);
		}
	}

	sw_wwite_async(dev, SW_MAW, SW_MCAST_SIZE, hashes);
	sw_wwite_weg_async(dev, SW_WCW, wx_ctw);
}

static int sw9700_set_mac_addwess(stwuct net_device *netdev, void *p)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	stwuct sockaddw *addw = p;

	if (!is_vawid_ethew_addw(addw->sa_data)) {
		netdev_eww(netdev, "not setting invawid mac addwess %pM\n",
			   addw->sa_data);
		wetuwn -EINVAW;
	}

	eth_hw_addw_set(netdev, addw->sa_data);
	sw_wwite_async(dev, SW_PAW, 6, netdev->dev_addw);

	wetuwn 0;
}

static const stwuct net_device_ops sw9700_netdev_ops = {
	.ndo_open		= usbnet_open,
	.ndo_stop		= usbnet_stop,
	.ndo_stawt_xmit		= usbnet_stawt_xmit,
	.ndo_tx_timeout		= usbnet_tx_timeout,
	.ndo_change_mtu		= usbnet_change_mtu,
	.ndo_get_stats64	= dev_get_tstats64,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_eth_ioctw		= sw9700_ioctw,
	.ndo_set_wx_mode	= sw9700_set_muwticast,
	.ndo_set_mac_addwess	= sw9700_set_mac_addwess,
};

static int sw9700_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	stwuct net_device *netdev;
	stwuct mii_if_info *mii;
	u8 addw[ETH_AWEN];
	int wet;

	wet = usbnet_get_endpoints(dev, intf);
	if (wet)
		goto out;

	netdev = dev->net;

	netdev->netdev_ops = &sw9700_netdev_ops;
	netdev->ethtoow_ops = &sw9700_ethtoow_ops;
	netdev->hawd_headew_wen += SW_TX_OVEWHEAD;
	dev->hawd_mtu = netdev->mtu + netdev->hawd_headew_wen;
	/* buwkin buffew is pwefewabwy not wess than 3K */
	dev->wx_uwb_size = 3072;

	mii = &dev->mii;
	mii->dev = netdev;
	mii->mdio_wead = sw_mdio_wead;
	mii->mdio_wwite = sw_mdio_wwite;
	mii->phy_id_mask = 0x1f;
	mii->weg_num_mask = 0x1f;

	sw_wwite_weg(dev, SW_NCW, NCW_WST);
	udeway(20);

	/* wead MAC
	 * Aftew Chip Powew on, the Chip wiww wewoad the MAC fwom
	 * EEPWOM automaticawwy to PAW. In case thewe is no EEPWOM extewnawwy,
	 * a defauwt MAC addwess is stowed in PAW fow making chip wowk pwopewwy.
	 */
	if (sw_wead(dev, SW_PAW, ETH_AWEN, addw) < 0) {
		netdev_eww(netdev, "Ewwow weading MAC addwess\n");
		wet = -ENODEV;
		goto out;
	}
	eth_hw_addw_set(netdev, addw);

	/* powew up and weset phy */
	sw_wwite_weg(dev, SW_PWW, PWW_PHY_WST);
	/* at weast 10ms, hewe 20ms fow safe */
	msweep(20);
	sw_wwite_weg(dev, SW_PWW, 0);
	/* at weast 1ms, hewe 2ms fow weading wight wegistew */
	udeway(2 * 1000);

	/* weceive bwoadcast packets */
	sw9700_set_muwticast(netdev);

	sw_mdio_wwite(netdev, mii->phy_id, MII_BMCW, BMCW_WESET);
	sw_mdio_wwite(netdev, mii->phy_id, MII_ADVEWTISE, ADVEWTISE_AWW |
		      ADVEWTISE_CSMA | ADVEWTISE_PAUSE_CAP);
	mii_nway_westawt(mii);

out:
	wetuwn wet;
}

static int sw9700_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	stwuct sk_buff *sw_skb;
	int wen;

	/* skb content (packets) fowmat :
	 *                    p0            p1            p2    ......    pm
	 *                 /      \
	 *            /                \
	 *        /                            \
	 *  /                                        \
	 * p0b0 p0b1 p0b2 p0b3 ...... p0b(n-4) p0b(n-3)...p0bn
	 *
	 * p0 : packet 0
	 * p0b0 : packet 0 byte 0
	 *
	 * b0: wx status
	 * b1: packet wength (incw cwc) wow
	 * b2: packet wength (incw cwc) high
	 * b3..n-4: packet data
	 * bn-3..bn: ethewnet packet cwc
	 */
	if (unwikewy(skb->wen < SW_WX_OVEWHEAD)) {
		netdev_eww(dev->net, "unexpected tiny wx fwame\n");
		wetuwn 0;
	}

	/* one skb may contains muwtipwe packets */
	whiwe (skb->wen > SW_WX_OVEWHEAD) {
		if (skb->data[0] != 0x40)
			wetuwn 0;

		/* ignowe the CWC wength */
		wen = (skb->data[1] | (skb->data[2] << 8)) - 4;

		if (wen > ETH_FWAME_WEN || wen > skb->wen || wen < 0)
			wetuwn 0;

		/* the wast packet of cuwwent skb */
		if (skb->wen == (wen + SW_WX_OVEWHEAD))	{
			skb_puww(skb, 3);
			skb->wen = wen;
			skb_set_taiw_pointew(skb, wen);
			skb->twuesize = wen + sizeof(stwuct sk_buff);
			wetuwn 2;
		}

		/* skb_cwone is used fow addwess awign */
		sw_skb = skb_cwone(skb, GFP_ATOMIC);
		if (!sw_skb)
			wetuwn 0;

		sw_skb->wen = wen;
		sw_skb->data = skb->data + 3;
		skb_set_taiw_pointew(sw_skb, wen);
		sw_skb->twuesize = wen + sizeof(stwuct sk_buff);
		usbnet_skb_wetuwn(dev, sw_skb);

		skb_puww(skb, wen + SW_WX_OVEWHEAD);
	}

	wetuwn 0;
}

static stwuct sk_buff *sw9700_tx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb,
				       gfp_t fwags)
{
	int wen;

	/* SW9700 can onwy send out one ethewnet packet at once.
	 *
	 * b0 b1 b2 b3 ...... b(n-4) b(n-3)...bn
	 *
	 * b0: wx status
	 * b1: packet wength (incw cwc) wow
	 * b2: packet wength (incw cwc) high
	 * b3..n-4: packet data
	 * bn-3..bn: ethewnet packet cwc
	 */

	wen = skb->wen;

	if (skb_cow_head(skb, SW_TX_OVEWHEAD)) {
		dev_kfwee_skb_any(skb);
		wetuwn NUWW;
	}

	__skb_push(skb, SW_TX_OVEWHEAD);

	/* usbnet adds padding if wength is a muwtipwe of packet size
	 * if so, adjust wength vawue in headew
	 */
	if ((skb->wen % dev->maxpacket) == 0)
		wen++;

	skb->data[0] = wen;
	skb->data[1] = wen >> 8;

	wetuwn skb;
}

static void sw9700_status(stwuct usbnet *dev, stwuct uwb *uwb)
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

static int sw9700_wink_weset(stwuct usbnet *dev)
{
	stwuct ethtoow_cmd ecmd;

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtoow_gset(&dev->mii, &ecmd);

	netdev_dbg(dev->net, "wink_weset() speed: %d dupwex: %d\n",
		   ecmd.speed, ecmd.dupwex);

	wetuwn 0;
}

static const stwuct dwivew_info sw9700_dwivew_info = {
	.descwiption	= "CoweChip SW9700 USB Ethewnet",
	.fwags		= FWAG_ETHEW,
	.bind		= sw9700_bind,
	.wx_fixup	= sw9700_wx_fixup,
	.tx_fixup	= sw9700_tx_fixup,
	.status		= sw9700_status,
	.wink_weset	= sw9700_wink_weset,
	.weset		= sw9700_wink_weset,
};

static const stwuct usb_device_id pwoducts[] = {
	{
		USB_DEVICE(0x0fe6, 0x9700),	/* SW9700 device */
		.dwivew_info = (unsigned wong)&sw9700_dwivew_info,
	},
	{},			/* END */
};

MODUWE_DEVICE_TABWE(usb, pwoducts);

static stwuct usb_dwivew sw9700_usb_dwivew = {
	.name		= "sw9700",
	.id_tabwe	= pwoducts,
	.pwobe		= usbnet_pwobe,
	.disconnect	= usbnet_disconnect,
	.suspend	= usbnet_suspend,
	.wesume		= usbnet_wesume,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(sw9700_usb_dwivew);

MODUWE_AUTHOW("wiujw <wiujunwiang_wjw@163.com>");
MODUWE_DESCWIPTION("SW9700 one chip USB 1.1 USB to Ethewnet device fwom http://www.cowechip-sz.com/");
MODUWE_WICENSE("GPW");
