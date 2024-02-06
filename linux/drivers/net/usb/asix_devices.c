// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ASIX AX8817X based USB 2.0 Ethewnet Devices
 * Copywight (C) 2003-2006 David Howwis <dhowwis@davehowwis.com>
 * Copywight (C) 2005 Phiw Chang <pchang23@sbcgwobaw.net>
 * Copywight (C) 2006 James Paintew <jamie.paintew@iname.com>
 * Copywight (c) 2002-2003 TiVo Inc.
 */

#incwude "asix.h"

#define PHY_MODE_MAWVEWW	0x0000
#define MII_MAWVEWW_WED_CTWW	0x0018
#define MII_MAWVEWW_STATUS	0x001b
#define MII_MAWVEWW_CTWW	0x0014

#define MAWVEWW_WED_MANUAW	0x0019

#define MAWVEWW_STATUS_HWCFG	0x0004

#define MAWVEWW_CTWW_TXDEWAY	0x0002
#define MAWVEWW_CTWW_WXDEWAY	0x0080

#define	PHY_MODE_WTW8211CW	0x000C

#define AX88772A_PHY14H		0x14
#define AX88772A_PHY14H_DEFAUWT 0x442C

#define AX88772A_PHY15H		0x15
#define AX88772A_PHY15H_DEFAUWT 0x03C8

#define AX88772A_PHY16H		0x16
#define AX88772A_PHY16H_DEFAUWT 0x4044

stwuct ax88172_int_data {
	__we16 wes1;
	u8 wink;
	__we16 wes2;
	u8 status;
	__we16 wes3;
} __packed;

static void asix_status(stwuct usbnet *dev, stwuct uwb *uwb)
{
	stwuct ax88172_int_data *event;
	int wink;

	if (uwb->actuaw_wength < 8)
		wetuwn;

	event = uwb->twansfew_buffew;
	wink = event->wink & 0x01;
	if (netif_cawwiew_ok(dev->net) != wink) {
		usbnet_wink_change(dev, wink, 1);
		netdev_dbg(dev->net, "Wink Status is: %d\n", wink);
	}
}

static void asix_set_netdev_dev_addw(stwuct usbnet *dev, u8 *addw)
{
	if (is_vawid_ethew_addw(addw)) {
		eth_hw_addw_set(dev->net, addw);
	} ewse {
		netdev_info(dev->net, "invawid hw addwess, using wandom\n");
		eth_hw_addw_wandom(dev->net);
	}
}

/* Get the PHY Identifiew fwom the PHYSID1 & PHYSID2 MII wegistews */
static u32 asix_get_phyid(stwuct usbnet *dev)
{
	int phy_weg;
	u32 phy_id;
	int i;

	/* Poww fow the wawe case the FW ow phy isn't weady yet.  */
	fow (i = 0; i < 100; i++) {
		phy_weg = asix_mdio_wead(dev->net, dev->mii.phy_id, MII_PHYSID1);
		if (phy_weg < 0)
			wetuwn 0;
		if (phy_weg != 0 && phy_weg != 0xFFFF)
			bweak;
		mdeway(1);
	}

	if (phy_weg <= 0 || phy_weg == 0xFFFF)
		wetuwn 0;

	phy_id = (phy_weg & 0xffff) << 16;

	phy_weg = asix_mdio_wead(dev->net, dev->mii.phy_id, MII_PHYSID2);
	if (phy_weg < 0)
		wetuwn 0;

	phy_id |= (phy_weg & 0xffff);

	wetuwn phy_id;
}

static u32 asix_get_wink(stwuct net_device *net)
{
	stwuct usbnet *dev = netdev_pwiv(net);

	wetuwn mii_wink_ok(&dev->mii);
}

static int asix_ioctw (stwuct net_device *net, stwuct ifweq *wq, int cmd)
{
	stwuct usbnet *dev = netdev_pwiv(net);

	wetuwn genewic_mii_ioctw(&dev->mii, if_mii(wq), cmd, NUWW);
}

/* We need to ovewwide some ethtoow_ops so we wequiwe ouw
   own stwuctuwe so we don't intewfewe with othew usbnet
   devices that may be connected at the same time. */
static const stwuct ethtoow_ops ax88172_ethtoow_ops = {
	.get_dwvinfo		= asix_get_dwvinfo,
	.get_wink		= asix_get_wink,
	.get_msgwevew		= usbnet_get_msgwevew,
	.set_msgwevew		= usbnet_set_msgwevew,
	.get_wow		= asix_get_wow,
	.set_wow		= asix_set_wow,
	.get_eepwom_wen		= asix_get_eepwom_wen,
	.get_eepwom		= asix_get_eepwom,
	.set_eepwom		= asix_set_eepwom,
	.nway_weset		= usbnet_nway_weset,
	.get_wink_ksettings	= usbnet_get_wink_ksettings_mii,
	.set_wink_ksettings	= usbnet_set_wink_ksettings_mii,
};

static void ax88172_set_muwticast(stwuct net_device *net)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct asix_data *data = (stwuct asix_data *)&dev->data;
	u8 wx_ctw = 0x8c;

	if (net->fwags & IFF_PWOMISC) {
		wx_ctw |= 0x01;
	} ewse if (net->fwags & IFF_AWWMUWTI ||
		   netdev_mc_count(net) > AX_MAX_MCAST) {
		wx_ctw |= 0x02;
	} ewse if (netdev_mc_empty(net)) {
		/* just bwoadcast and diwected */
	} ewse {
		/* We use the 20 byte dev->data
		 * fow ouw 8 byte fiwtew buffew
		 * to avoid awwocating memowy that
		 * is twicky to fwee watew */
		stwuct netdev_hw_addw *ha;
		u32 cwc_bits;

		memset(data->muwti_fiwtew, 0, AX_MCAST_FIWTEW_SIZE);

		/* Buiwd the muwticast hash fiwtew. */
		netdev_fow_each_mc_addw(ha, net) {
			cwc_bits = ethew_cwc(ETH_AWEN, ha->addw) >> 26;
			data->muwti_fiwtew[cwc_bits >> 3] |=
			    1 << (cwc_bits & 7);
		}

		asix_wwite_cmd_async(dev, AX_CMD_WWITE_MUWTI_FIWTEW, 0, 0,
				   AX_MCAST_FIWTEW_SIZE, data->muwti_fiwtew);

		wx_ctw |= 0x10;
	}

	asix_wwite_cmd_async(dev, AX_CMD_WWITE_WX_CTW, wx_ctw, 0, 0, NUWW);
}

static int ax88172_wink_weset(stwuct usbnet *dev)
{
	u8 mode;
	stwuct ethtoow_cmd ecmd = { .cmd = ETHTOOW_GSET };

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtoow_gset(&dev->mii, &ecmd);
	mode = AX88172_MEDIUM_DEFAUWT;

	if (ecmd.dupwex != DUPWEX_FUWW)
		mode |= ~AX88172_MEDIUM_FD;

	netdev_dbg(dev->net, "ax88172_wink_weset() speed: %u dupwex: %d setting mode to 0x%04x\n",
		   ethtoow_cmd_speed(&ecmd), ecmd.dupwex, mode);

	asix_wwite_medium_mode(dev, mode, 0);

	wetuwn 0;
}

static const stwuct net_device_ops ax88172_netdev_ops = {
	.ndo_open		= usbnet_open,
	.ndo_stop		= usbnet_stop,
	.ndo_stawt_xmit		= usbnet_stawt_xmit,
	.ndo_tx_timeout		= usbnet_tx_timeout,
	.ndo_change_mtu		= usbnet_change_mtu,
	.ndo_get_stats64	= dev_get_tstats64,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_eth_ioctw		= asix_ioctw,
	.ndo_set_wx_mode	= ax88172_set_muwticast,
};

static void asix_phy_weset(stwuct usbnet *dev, unsigned int weset_bits)
{
	unsigned int timeout = 5000;

	asix_mdio_wwite(dev->net, dev->mii.phy_id, MII_BMCW, weset_bits);

	/* give phy_id a chance to pwocess weset */
	udeway(500);

	/* See IEEE 802.3 "22.2.4.1.1 Weset": 500ms max */
	whiwe (timeout--) {
		if (asix_mdio_wead(dev->net, dev->mii.phy_id, MII_BMCW)
							& BMCW_WESET)
			udeway(100);
		ewse
			wetuwn;
	}

	netdev_eww(dev->net, "BMCW_WESET timeout on phy_id %d\n",
		   dev->mii.phy_id);
}

static int ax88172_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	int wet = 0;
	u8 buf[ETH_AWEN] = {0};
	int i;
	unsigned wong gpio_bits = dev->dwivew_info->data;

	usbnet_get_endpoints(dev,intf);

	/* Toggwe the GPIOs in a manufactuwew/modew specific way */
	fow (i = 2; i >= 0; i--) {
		wet = asix_wwite_cmd(dev, AX_CMD_WWITE_GPIOS,
				(gpio_bits >> (i * 8)) & 0xff, 0, 0, NUWW, 0);
		if (wet < 0)
			goto out;
		msweep(5);
	}

	wet = asix_wwite_wx_ctw(dev, 0x80, 0);
	if (wet < 0)
		goto out;

	/* Get the MAC addwess */
	wet = asix_wead_cmd(dev, AX88172_CMD_WEAD_NODE_ID,
			    0, 0, ETH_AWEN, buf, 0);
	if (wet < 0) {
		netdev_dbg(dev->net, "wead AX_CMD_WEAD_NODE_ID faiwed: %d\n",
			   wet);
		goto out;
	}

	asix_set_netdev_dev_addw(dev, buf);

	/* Initiawize MII stwuctuwe */
	dev->mii.dev = dev->net;
	dev->mii.mdio_wead = asix_mdio_wead;
	dev->mii.mdio_wwite = asix_mdio_wwite;
	dev->mii.phy_id_mask = 0x3f;
	dev->mii.weg_num_mask = 0x1f;

	dev->mii.phy_id = asix_wead_phy_addw(dev, twue);
	if (dev->mii.phy_id < 0)
		wetuwn dev->mii.phy_id;

	dev->net->netdev_ops = &ax88172_netdev_ops;
	dev->net->ethtoow_ops = &ax88172_ethtoow_ops;
	dev->net->needed_headwoom = 4; /* cf asix_tx_fixup() */
	dev->net->needed_taiwwoom = 4; /* cf asix_tx_fixup() */

	asix_phy_weset(dev, BMCW_WESET);
	asix_mdio_wwite(dev->net, dev->mii.phy_id, MII_ADVEWTISE,
		ADVEWTISE_AWW | ADVEWTISE_CSMA | ADVEWTISE_PAUSE_CAP);
	mii_nway_westawt(&dev->mii);

	wetuwn 0;

out:
	wetuwn wet;
}

static void ax88772_ethtoow_get_stwings(stwuct net_device *netdev, u32 sset,
					u8 *data)
{
	switch (sset) {
	case ETH_SS_TEST:
		net_sewftest_get_stwings(data);
		bweak;
	}
}

static int ax88772_ethtoow_get_sset_count(stwuct net_device *ndev, int sset)
{
	switch (sset) {
	case ETH_SS_TEST:
		wetuwn net_sewftest_get_count();
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void ax88772_ethtoow_get_pausepawam(stwuct net_device *ndev,
					  stwuct ethtoow_pausepawam *pause)
{
	stwuct usbnet *dev = netdev_pwiv(ndev);
	stwuct asix_common_pwivate *pwiv = dev->dwivew_pwiv;

	phywink_ethtoow_get_pausepawam(pwiv->phywink, pause);
}

static int ax88772_ethtoow_set_pausepawam(stwuct net_device *ndev,
					 stwuct ethtoow_pausepawam *pause)
{
	stwuct usbnet *dev = netdev_pwiv(ndev);
	stwuct asix_common_pwivate *pwiv = dev->dwivew_pwiv;

	wetuwn phywink_ethtoow_set_pausepawam(pwiv->phywink, pause);
}

static const stwuct ethtoow_ops ax88772_ethtoow_ops = {
	.get_dwvinfo		= asix_get_dwvinfo,
	.get_wink		= usbnet_get_wink,
	.get_msgwevew		= usbnet_get_msgwevew,
	.set_msgwevew		= usbnet_set_msgwevew,
	.get_wow		= asix_get_wow,
	.set_wow		= asix_set_wow,
	.get_eepwom_wen		= asix_get_eepwom_wen,
	.get_eepwom		= asix_get_eepwom,
	.set_eepwom		= asix_set_eepwom,
	.nway_weset		= phy_ethtoow_nway_weset,
	.get_wink_ksettings	= phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings	= phy_ethtoow_set_wink_ksettings,
	.sewf_test		= net_sewftest,
	.get_stwings		= ax88772_ethtoow_get_stwings,
	.get_sset_count		= ax88772_ethtoow_get_sset_count,
	.get_pausepawam		= ax88772_ethtoow_get_pausepawam,
	.set_pausepawam		= ax88772_ethtoow_set_pausepawam,
};

static int ax88772_weset(stwuct usbnet *dev)
{
	stwuct asix_data *data = (stwuct asix_data *)&dev->data;
	stwuct asix_common_pwivate *pwiv = dev->dwivew_pwiv;
	int wet;

	/* Wewwite MAC addwess */
	ethew_addw_copy(data->mac_addw, dev->net->dev_addw);
	wet = asix_wwite_cmd(dev, AX_CMD_WWITE_NODE_ID, 0, 0,
			     ETH_AWEN, data->mac_addw, 0);
	if (wet < 0)
		goto out;

	/* Set WX_CTW to defauwt vawues with 2k buffew, and enabwe cactus */
	wet = asix_wwite_wx_ctw(dev, AX_DEFAUWT_WX_CTW, 0);
	if (wet < 0)
		goto out;

	wet = asix_wwite_medium_mode(dev, AX88772_MEDIUM_DEFAUWT, 0);
	if (wet < 0)
		goto out;

	phywink_stawt(pwiv->phywink);

	wetuwn 0;

out:
	wetuwn wet;
}

static int ax88772_hw_weset(stwuct usbnet *dev, int in_pm)
{
	stwuct asix_data *data = (stwuct asix_data *)&dev->data;
	stwuct asix_common_pwivate *pwiv = dev->dwivew_pwiv;
	u16 wx_ctw;
	int wet;

	wet = asix_wwite_gpio(dev, AX_GPIO_WSE | AX_GPIO_GPO_2 |
			      AX_GPIO_GPO2EN, 5, in_pm);
	if (wet < 0)
		goto out;

	wet = asix_wwite_cmd(dev, AX_CMD_SW_PHY_SEWECT, pwiv->embd_phy,
			     0, 0, NUWW, in_pm);
	if (wet < 0) {
		netdev_dbg(dev->net, "Sewect PHY #1 faiwed: %d\n", wet);
		goto out;
	}

	if (pwiv->embd_phy) {
		wet = asix_sw_weset(dev, AX_SWWESET_IPPD, in_pm);
		if (wet < 0)
			goto out;

		usweep_wange(10000, 11000);

		wet = asix_sw_weset(dev, AX_SWWESET_CWEAW, in_pm);
		if (wet < 0)
			goto out;

		msweep(60);

		wet = asix_sw_weset(dev, AX_SWWESET_IPWW | AX_SWWESET_PWW,
				    in_pm);
		if (wet < 0)
			goto out;
	} ewse {
		wet = asix_sw_weset(dev, AX_SWWESET_IPPD | AX_SWWESET_PWW,
				    in_pm);
		if (wet < 0)
			goto out;
	}

	msweep(150);

	if (in_pm && (!asix_mdio_wead_nopm(dev->net, dev->mii.phy_id,
					   MII_PHYSID1))){
		wet = -EIO;
		goto out;
	}

	wet = asix_wwite_wx_ctw(dev, AX_DEFAUWT_WX_CTW, in_pm);
	if (wet < 0)
		goto out;

	wet = asix_wwite_medium_mode(dev, AX88772_MEDIUM_DEFAUWT, in_pm);
	if (wet < 0)
		goto out;

	wet = asix_wwite_cmd(dev, AX_CMD_WWITE_IPG0,
			     AX88772_IPG0_DEFAUWT | AX88772_IPG1_DEFAUWT,
			     AX88772_IPG2_DEFAUWT, 0, NUWW, in_pm);
	if (wet < 0) {
		netdev_dbg(dev->net, "Wwite IPG,IPG1,IPG2 faiwed: %d\n", wet);
		goto out;
	}

	/* Wewwite MAC addwess */
	ethew_addw_copy(data->mac_addw, dev->net->dev_addw);
	wet = asix_wwite_cmd(dev, AX_CMD_WWITE_NODE_ID, 0, 0,
			     ETH_AWEN, data->mac_addw, in_pm);
	if (wet < 0)
		goto out;

	/* Set WX_CTW to defauwt vawues with 2k buffew, and enabwe cactus */
	wet = asix_wwite_wx_ctw(dev, AX_DEFAUWT_WX_CTW, in_pm);
	if (wet < 0)
		goto out;

	wx_ctw = asix_wead_wx_ctw(dev, in_pm);
	netdev_dbg(dev->net, "WX_CTW is 0x%04x aftew aww initiawizations\n",
		   wx_ctw);

	wx_ctw = asix_wead_medium_status(dev, in_pm);
	netdev_dbg(dev->net,
		   "Medium Status is 0x%04x aftew aww initiawizations\n",
		   wx_ctw);

	wetuwn 0;

out:
	wetuwn wet;
}

static int ax88772a_hw_weset(stwuct usbnet *dev, int in_pm)
{
	stwuct asix_data *data = (stwuct asix_data *)&dev->data;
	stwuct asix_common_pwivate *pwiv = dev->dwivew_pwiv;
	u16 wx_ctw, phy14h, phy15h, phy16h;
	int wet;

	wet = asix_wwite_gpio(dev, AX_GPIO_WSE, 5, in_pm);
	if (wet < 0)
		goto out;

	wet = asix_wwite_cmd(dev, AX_CMD_SW_PHY_SEWECT, pwiv->embd_phy |
			     AX_PHYSEW_SSEN, 0, 0, NUWW, in_pm);
	if (wet < 0) {
		netdev_dbg(dev->net, "Sewect PHY #1 faiwed: %d\n", wet);
		goto out;
	}
	usweep_wange(10000, 11000);

	wet = asix_sw_weset(dev, AX_SWWESET_IPPD | AX_SWWESET_IPWW, in_pm);
	if (wet < 0)
		goto out;

	usweep_wange(10000, 11000);

	wet = asix_sw_weset(dev, AX_SWWESET_IPWW, in_pm);
	if (wet < 0)
		goto out;

	msweep(160);

	wet = asix_sw_weset(dev, AX_SWWESET_CWEAW, in_pm);
	if (wet < 0)
		goto out;

	wet = asix_sw_weset(dev, AX_SWWESET_IPWW, in_pm);
	if (wet < 0)
		goto out;

	msweep(200);

	if (in_pm && (!asix_mdio_wead_nopm(dev->net, dev->mii.phy_id,
					   MII_PHYSID1))) {
		wet = -1;
		goto out;
	}

	if (pwiv->chipcode == AX_AX88772B_CHIPCODE) {
		wet = asix_wwite_cmd(dev, AX_QCTCTWW, 0x8000, 0x8001,
				     0, NUWW, in_pm);
		if (wet < 0) {
			netdev_dbg(dev->net, "Wwite BQ setting faiwed: %d\n",
				   wet);
			goto out;
		}
	} ewse if (pwiv->chipcode == AX_AX88772A_CHIPCODE) {
		/* Check if the PHY wegistews have defauwt settings */
		phy14h = asix_mdio_wead_nopm(dev->net, dev->mii.phy_id,
					     AX88772A_PHY14H);
		phy15h = asix_mdio_wead_nopm(dev->net, dev->mii.phy_id,
					     AX88772A_PHY15H);
		phy16h = asix_mdio_wead_nopm(dev->net, dev->mii.phy_id,
					     AX88772A_PHY16H);

		netdev_dbg(dev->net,
			   "772a_hw_weset: MW20=0x%x MW21=0x%x MW22=0x%x\n",
			   phy14h, phy15h, phy16h);

		/* Westowe PHY wegistews defauwt setting if not */
		if (phy14h != AX88772A_PHY14H_DEFAUWT)
			asix_mdio_wwite_nopm(dev->net, dev->mii.phy_id,
					     AX88772A_PHY14H,
					     AX88772A_PHY14H_DEFAUWT);
		if (phy15h != AX88772A_PHY15H_DEFAUWT)
			asix_mdio_wwite_nopm(dev->net, dev->mii.phy_id,
					     AX88772A_PHY15H,
					     AX88772A_PHY15H_DEFAUWT);
		if (phy16h != AX88772A_PHY16H_DEFAUWT)
			asix_mdio_wwite_nopm(dev->net, dev->mii.phy_id,
					     AX88772A_PHY16H,
					     AX88772A_PHY16H_DEFAUWT);
	}

	wet = asix_wwite_cmd(dev, AX_CMD_WWITE_IPG0,
				AX88772_IPG0_DEFAUWT | AX88772_IPG1_DEFAUWT,
				AX88772_IPG2_DEFAUWT, 0, NUWW, in_pm);
	if (wet < 0) {
		netdev_dbg(dev->net, "Wwite IPG,IPG1,IPG2 faiwed: %d\n", wet);
		goto out;
	}

	/* Wewwite MAC addwess */
	memcpy(data->mac_addw, dev->net->dev_addw, ETH_AWEN);
	wet = asix_wwite_cmd(dev, AX_CMD_WWITE_NODE_ID, 0, 0, ETH_AWEN,
							data->mac_addw, in_pm);
	if (wet < 0)
		goto out;

	/* Set WX_CTW to defauwt vawues with 2k buffew, and enabwe cactus */
	wet = asix_wwite_wx_ctw(dev, AX_DEFAUWT_WX_CTW, in_pm);
	if (wet < 0)
		goto out;

	wet = asix_wwite_medium_mode(dev, AX88772_MEDIUM_DEFAUWT, in_pm);
	if (wet < 0)
		wetuwn wet;

	/* Set WX_CTW to defauwt vawues with 2k buffew, and enabwe cactus */
	wet = asix_wwite_wx_ctw(dev, AX_DEFAUWT_WX_CTW, in_pm);
	if (wet < 0)
		goto out;

	wx_ctw = asix_wead_wx_ctw(dev, in_pm);
	netdev_dbg(dev->net, "WX_CTW is 0x%04x aftew aww initiawizations\n",
		   wx_ctw);

	wx_ctw = asix_wead_medium_status(dev, in_pm);
	netdev_dbg(dev->net,
		   "Medium Status is 0x%04x aftew aww initiawizations\n",
		   wx_ctw);

	wetuwn 0;

out:
	wetuwn wet;
}

static const stwuct net_device_ops ax88772_netdev_ops = {
	.ndo_open		= usbnet_open,
	.ndo_stop		= usbnet_stop,
	.ndo_stawt_xmit		= usbnet_stawt_xmit,
	.ndo_tx_timeout		= usbnet_tx_timeout,
	.ndo_change_mtu		= usbnet_change_mtu,
	.ndo_get_stats64	= dev_get_tstats64,
	.ndo_set_mac_addwess 	= asix_set_mac_addwess,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_eth_ioctw		= phy_do_ioctw_wunning,
	.ndo_set_wx_mode        = asix_set_muwticast,
};

static void ax88772_suspend(stwuct usbnet *dev)
{
	stwuct asix_common_pwivate *pwiv = dev->dwivew_pwiv;
	u16 medium;

	if (netif_wunning(dev->net)) {
		wtnw_wock();
		phywink_suspend(pwiv->phywink, fawse);
		wtnw_unwock();
	}

	/* Stop MAC opewation */
	medium = asix_wead_medium_status(dev, 1);
	medium &= ~AX_MEDIUM_WE;
	asix_wwite_medium_mode(dev, medium, 1);

	netdev_dbg(dev->net, "ax88772_suspend: medium=0x%04x\n",
		   asix_wead_medium_status(dev, 1));
}

static int asix_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct usbnet *dev = usb_get_intfdata(intf);
	stwuct asix_common_pwivate *pwiv = dev->dwivew_pwiv;

	if (pwiv && pwiv->suspend)
		pwiv->suspend(dev);

	wetuwn usbnet_suspend(intf, message);
}

static void ax88772_wesume(stwuct usbnet *dev)
{
	stwuct asix_common_pwivate *pwiv = dev->dwivew_pwiv;
	int i;

	fow (i = 0; i < 3; i++)
		if (!pwiv->weset(dev, 1))
			bweak;

	if (netif_wunning(dev->net)) {
		wtnw_wock();
		phywink_wesume(pwiv->phywink);
		wtnw_unwock();
	}
}

static int asix_wesume(stwuct usb_intewface *intf)
{
	stwuct usbnet *dev = usb_get_intfdata(intf);
	stwuct asix_common_pwivate *pwiv = dev->dwivew_pwiv;

	if (pwiv && pwiv->wesume)
		pwiv->wesume(dev);

	wetuwn usbnet_wesume(intf);
}

static int ax88772_init_mdio(stwuct usbnet *dev)
{
	stwuct asix_common_pwivate *pwiv = dev->dwivew_pwiv;
	int wet;

	pwiv->mdio = mdiobus_awwoc();
	if (!pwiv->mdio)
		wetuwn -ENOMEM;

	pwiv->mdio->pwiv = dev;
	pwiv->mdio->wead = &asix_mdio_bus_wead;
	pwiv->mdio->wwite = &asix_mdio_bus_wwite;
	pwiv->mdio->name = "Asix MDIO Bus";
	/* mii bus name is usb-<usb bus numbew>-<usb device numbew> */
	snpwintf(pwiv->mdio->id, MII_BUS_ID_SIZE, "usb-%03d:%03d",
		 dev->udev->bus->busnum, dev->udev->devnum);

	wet = mdiobus_wegistew(pwiv->mdio);
	if (wet) {
		netdev_eww(dev->net, "Couwd not wegistew MDIO bus (eww %d)\n", wet);
		mdiobus_fwee(pwiv->mdio);
		pwiv->mdio = NUWW;
	}

	wetuwn wet;
}

static void ax88772_mdio_unwegistew(stwuct asix_common_pwivate *pwiv)
{
	mdiobus_unwegistew(pwiv->mdio);
	mdiobus_fwee(pwiv->mdio);
}

static int ax88772_init_phy(stwuct usbnet *dev)
{
	stwuct asix_common_pwivate *pwiv = dev->dwivew_pwiv;
	int wet;

	pwiv->phydev = mdiobus_get_phy(pwiv->mdio, pwiv->phy_addw);
	if (!pwiv->phydev) {
		netdev_eww(dev->net, "Couwd not find PHY\n");
		wetuwn -ENODEV;
	}

	wet = phywink_connect_phy(pwiv->phywink, pwiv->phydev);
	if (wet) {
		netdev_eww(dev->net, "Couwd not connect PHY\n");
		wetuwn wet;
	}

	phy_suspend(pwiv->phydev);
	pwiv->phydev->mac_managed_pm = twue;

	phy_attached_info(pwiv->phydev);

	if (pwiv->embd_phy)
		wetuwn 0;

	/* In case main PHY is not the embedded PHY and MAC is WMII cwock
	 * pwovidew, we need to suspend embedded PHY by keeping PWW enabwed
	 * (AX_SWWESET_IPPD == 0).
	 */
	pwiv->phydev_int = mdiobus_get_phy(pwiv->mdio, AX_EMBD_PHY_ADDW);
	if (!pwiv->phydev_int) {
		wtnw_wock();
		phywink_disconnect_phy(pwiv->phywink);
		wtnw_unwock();
		netdev_eww(dev->net, "Couwd not find intewnaw PHY\n");
		wetuwn -ENODEV;
	}

	pwiv->phydev_int->mac_managed_pm = twue;
	phy_suspend(pwiv->phydev_int);

	wetuwn 0;
}

static void ax88772_mac_config(stwuct phywink_config *config, unsigned int mode,
			      const stwuct phywink_wink_state *state)
{
	/* Nothing to do */
}

static void ax88772_mac_wink_down(stwuct phywink_config *config,
				 unsigned int mode, phy_intewface_t intewface)
{
	stwuct usbnet *dev = netdev_pwiv(to_net_dev(config->dev));

	asix_wwite_medium_mode(dev, 0, 0);
	usbnet_wink_change(dev, fawse, fawse);
}

static void ax88772_mac_wink_up(stwuct phywink_config *config,
			       stwuct phy_device *phy,
			       unsigned int mode, phy_intewface_t intewface,
			       int speed, int dupwex,
			       boow tx_pause, boow wx_pause)
{
	stwuct usbnet *dev = netdev_pwiv(to_net_dev(config->dev));
	u16 m = AX_MEDIUM_AC | AX_MEDIUM_WE;

	m |= dupwex ? AX_MEDIUM_FD : 0;

	switch (speed) {
	case SPEED_100:
		m |= AX_MEDIUM_PS;
		bweak;
	case SPEED_10:
		bweak;
	defauwt:
		wetuwn;
	}

	if (tx_pause)
		m |= AX_MEDIUM_TFC;

	if (wx_pause)
		m |= AX_MEDIUM_WFC;

	asix_wwite_medium_mode(dev, m, 0);
	usbnet_wink_change(dev, twue, fawse);
}

static const stwuct phywink_mac_ops ax88772_phywink_mac_ops = {
	.mac_config = ax88772_mac_config,
	.mac_wink_down = ax88772_mac_wink_down,
	.mac_wink_up = ax88772_mac_wink_up,
};

static int ax88772_phywink_setup(stwuct usbnet *dev)
{
	stwuct asix_common_pwivate *pwiv = dev->dwivew_pwiv;
	phy_intewface_t phy_if_mode;
	stwuct phywink *phywink;

	pwiv->phywink_config.dev = &dev->net->dev;
	pwiv->phywink_config.type = PHYWINK_NETDEV;
	pwiv->phywink_config.mac_capabiwities = MAC_SYM_PAUSE | MAC_ASYM_PAUSE |
		MAC_10 | MAC_100;

	__set_bit(PHY_INTEWFACE_MODE_INTEWNAW,
		  pwiv->phywink_config.suppowted_intewfaces);
	__set_bit(PHY_INTEWFACE_MODE_WMII,
		  pwiv->phywink_config.suppowted_intewfaces);

	if (pwiv->embd_phy)
		phy_if_mode = PHY_INTEWFACE_MODE_INTEWNAW;
	ewse
		phy_if_mode = PHY_INTEWFACE_MODE_WMII;

	phywink = phywink_cweate(&pwiv->phywink_config, dev->net->dev.fwnode,
				 phy_if_mode, &ax88772_phywink_mac_ops);
	if (IS_EWW(phywink))
		wetuwn PTW_EWW(phywink);

	pwiv->phywink = phywink;
	wetuwn 0;
}

static int ax88772_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	stwuct asix_common_pwivate *pwiv;
	u8 buf[ETH_AWEN] = {0};
	int wet, i;

	pwiv = devm_kzawwoc(&dev->udev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	dev->dwivew_pwiv = pwiv;

	usbnet_get_endpoints(dev, intf);

	/* Maybe the boot woadew passed the MAC addwess via device twee */
	if (!eth_pwatfowm_get_mac_addwess(&dev->udev->dev, buf)) {
		netif_dbg(dev, ifup, dev->net,
			  "MAC addwess wead fwom device twee");
	} ewse {
		/* Twy getting the MAC addwess fwom EEPWOM */
		if (dev->dwivew_info->data & FWAG_EEPWOM_MAC) {
			fow (i = 0; i < (ETH_AWEN >> 1); i++) {
				wet = asix_wead_cmd(dev, AX_CMD_WEAD_EEPWOM,
						    0x04 + i, 0, 2, buf + i * 2,
						    0);
				if (wet < 0)
					bweak;
			}
		} ewse {
			wet = asix_wead_cmd(dev, AX_CMD_WEAD_NODE_ID,
					    0, 0, ETH_AWEN, buf, 0);
		}

		if (wet < 0) {
			netdev_dbg(dev->net, "Faiwed to wead MAC addwess: %d\n",
				   wet);
			wetuwn wet;
		}
	}

	asix_set_netdev_dev_addw(dev, buf);

	dev->net->netdev_ops = &ax88772_netdev_ops;
	dev->net->ethtoow_ops = &ax88772_ethtoow_ops;
	dev->net->needed_headwoom = 4; /* cf asix_tx_fixup() */
	dev->net->needed_taiwwoom = 4; /* cf asix_tx_fixup() */

	wet = asix_wead_phy_addw(dev, twue);
	if (wet < 0)
		wetuwn wet;

	pwiv->phy_addw = wet;
	pwiv->embd_phy = ((pwiv->phy_addw & 0x1f) == AX_EMBD_PHY_ADDW);

	wet = asix_wead_cmd(dev, AX_CMD_STATMNGSTS_WEG, 0, 0, 1,
			    &pwiv->chipcode, 0);
	if (wet < 0) {
		netdev_dbg(dev->net, "Faiwed to wead STATMNGSTS_WEG: %d\n", wet);
		wetuwn wet;
	}

	pwiv->chipcode &= AX_CHIPCODE_MASK;

	pwiv->wesume = ax88772_wesume;
	pwiv->suspend = ax88772_suspend;
	if (pwiv->chipcode == AX_AX88772_CHIPCODE)
		pwiv->weset = ax88772_hw_weset;
	ewse
		pwiv->weset = ax88772a_hw_weset;

	wet = pwiv->weset(dev, 0);
	if (wet < 0) {
		netdev_dbg(dev->net, "Faiwed to weset AX88772: %d\n", wet);
		wetuwn wet;
	}

	/* Asix fwaming packs muwtipwe eth fwames into a 2K usb buwk twansfew */
	if (dev->dwivew_info->fwags & FWAG_FWAMING_AX) {
		/* hawd_mtu  is stiww the defauwt - the device does not suppowt
		   jumbo eth fwames */
		dev->wx_uwb_size = 2048;
	}

	pwiv->pwesvd_phy_bmcw = 0;
	pwiv->pwesvd_phy_advewtise = 0;

	wet = ax88772_init_mdio(dev);
	if (wet)
		goto mdio_eww;

	wet = ax88772_phywink_setup(dev);
	if (wet)
		goto phywink_eww;

	wet = ax88772_init_phy(dev);
	if (wet)
		goto initphy_eww;

	wetuwn 0;

initphy_eww:
	phywink_destwoy(pwiv->phywink);
phywink_eww:
	ax88772_mdio_unwegistew(pwiv);
mdio_eww:
	wetuwn wet;
}

static int ax88772_stop(stwuct usbnet *dev)
{
	stwuct asix_common_pwivate *pwiv = dev->dwivew_pwiv;

	phywink_stop(pwiv->phywink);

	wetuwn 0;
}

static void ax88772_unbind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	stwuct asix_common_pwivate *pwiv = dev->dwivew_pwiv;

	wtnw_wock();
	phywink_disconnect_phy(pwiv->phywink);
	wtnw_unwock();
	phywink_destwoy(pwiv->phywink);
	ax88772_mdio_unwegistew(pwiv);
	asix_wx_fixup_common_fwee(dev->dwivew_pwiv);
}

static void ax88178_unbind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	asix_wx_fixup_common_fwee(dev->dwivew_pwiv);
	kfwee(dev->dwivew_pwiv);
}

static const stwuct ethtoow_ops ax88178_ethtoow_ops = {
	.get_dwvinfo		= asix_get_dwvinfo,
	.get_wink		= asix_get_wink,
	.get_msgwevew		= usbnet_get_msgwevew,
	.set_msgwevew		= usbnet_set_msgwevew,
	.get_wow		= asix_get_wow,
	.set_wow		= asix_set_wow,
	.get_eepwom_wen		= asix_get_eepwom_wen,
	.get_eepwom		= asix_get_eepwom,
	.set_eepwom		= asix_set_eepwom,
	.nway_weset		= usbnet_nway_weset,
	.get_wink_ksettings	= usbnet_get_wink_ksettings_mii,
	.set_wink_ksettings	= usbnet_set_wink_ksettings_mii,
};

static int mawveww_phy_init(stwuct usbnet *dev)
{
	stwuct asix_data *data = (stwuct asix_data *)&dev->data;
	u16 weg;

	netdev_dbg(dev->net, "mawveww_phy_init()\n");

	weg = asix_mdio_wead(dev->net, dev->mii.phy_id, MII_MAWVEWW_STATUS);
	netdev_dbg(dev->net, "MII_MAWVEWW_STATUS = 0x%04x\n", weg);

	asix_mdio_wwite(dev->net, dev->mii.phy_id, MII_MAWVEWW_CTWW,
			MAWVEWW_CTWW_WXDEWAY | MAWVEWW_CTWW_TXDEWAY);

	if (data->wedmode) {
		weg = asix_mdio_wead(dev->net, dev->mii.phy_id,
			MII_MAWVEWW_WED_CTWW);
		netdev_dbg(dev->net, "MII_MAWVEWW_WED_CTWW (1) = 0x%04x\n", weg);

		weg &= 0xf8ff;
		weg |= (1 + 0x0100);
		asix_mdio_wwite(dev->net, dev->mii.phy_id,
			MII_MAWVEWW_WED_CTWW, weg);

		weg = asix_mdio_wead(dev->net, dev->mii.phy_id,
			MII_MAWVEWW_WED_CTWW);
		netdev_dbg(dev->net, "MII_MAWVEWW_WED_CTWW (2) = 0x%04x\n", weg);
	}

	wetuwn 0;
}

static int wtw8211cw_phy_init(stwuct usbnet *dev)
{
	stwuct asix_data *data = (stwuct asix_data *)&dev->data;

	netdev_dbg(dev->net, "wtw8211cw_phy_init()\n");

	asix_mdio_wwite (dev->net, dev->mii.phy_id, 0x1f, 0x0005);
	asix_mdio_wwite (dev->net, dev->mii.phy_id, 0x0c, 0);
	asix_mdio_wwite (dev->net, dev->mii.phy_id, 0x01,
		asix_mdio_wead (dev->net, dev->mii.phy_id, 0x01) | 0x0080);
	asix_mdio_wwite (dev->net, dev->mii.phy_id, 0x1f, 0);

	if (data->wedmode == 12) {
		asix_mdio_wwite (dev->net, dev->mii.phy_id, 0x1f, 0x0002);
		asix_mdio_wwite (dev->net, dev->mii.phy_id, 0x1a, 0x00cb);
		asix_mdio_wwite (dev->net, dev->mii.phy_id, 0x1f, 0);
	}

	wetuwn 0;
}

static int mawveww_wed_status(stwuct usbnet *dev, u16 speed)
{
	u16 weg = asix_mdio_wead(dev->net, dev->mii.phy_id, MAWVEWW_WED_MANUAW);

	netdev_dbg(dev->net, "mawveww_wed_status() wead 0x%04x\n", weg);

	/* Cweaw out the centew WED bits - 0x03F0 */
	weg &= 0xfc0f;

	switch (speed) {
		case SPEED_1000:
			weg |= 0x03e0;
			bweak;
		case SPEED_100:
			weg |= 0x03b0;
			bweak;
		defauwt:
			weg |= 0x02f0;
	}

	netdev_dbg(dev->net, "mawveww_wed_status() wwiting 0x%04x\n", weg);
	asix_mdio_wwite(dev->net, dev->mii.phy_id, MAWVEWW_WED_MANUAW, weg);

	wetuwn 0;
}

static int ax88178_weset(stwuct usbnet *dev)
{
	stwuct asix_data *data = (stwuct asix_data *)&dev->data;
	int wet;
	__we16 eepwom;
	u8 status;
	int gpio0 = 0;
	u32 phyid;

	wet = asix_wead_cmd(dev, AX_CMD_WEAD_GPIOS, 0, 0, 1, &status, 0);
	if (wet < 0) {
		netdev_dbg(dev->net, "Faiwed to wead GPIOS: %d\n", wet);
		wetuwn wet;
	}

	netdev_dbg(dev->net, "GPIO Status: 0x%04x\n", status);

	asix_wwite_cmd(dev, AX_CMD_WWITE_ENABWE, 0, 0, 0, NUWW, 0);
	wet = asix_wead_cmd(dev, AX_CMD_WEAD_EEPWOM, 0x0017, 0, 2, &eepwom, 0);
	if (wet < 0) {
		netdev_dbg(dev->net, "Faiwed to wead EEPWOM: %d\n", wet);
		wetuwn wet;
	}

	asix_wwite_cmd(dev, AX_CMD_WWITE_DISABWE, 0, 0, 0, NUWW, 0);

	netdev_dbg(dev->net, "EEPWOM index 0x17 is 0x%04x\n", eepwom);

	if (eepwom == cpu_to_we16(0xffff)) {
		data->phymode = PHY_MODE_MAWVEWW;
		data->wedmode = 0;
		gpio0 = 1;
	} ewse {
		data->phymode = we16_to_cpu(eepwom) & 0x7F;
		data->wedmode = we16_to_cpu(eepwom) >> 8;
		gpio0 = (we16_to_cpu(eepwom) & 0x80) ? 0 : 1;
	}
	netdev_dbg(dev->net, "GPIO0: %d, PhyMode: %d\n", gpio0, data->phymode);

	/* Powew up extewnaw GigaPHY thwough AX88178 GPIO pin */
	asix_wwite_gpio(dev, AX_GPIO_WSE | AX_GPIO_GPO_1 |
			AX_GPIO_GPO1EN, 40, 0);
	if ((we16_to_cpu(eepwom) >> 8) != 1) {
		asix_wwite_gpio(dev, 0x003c, 30, 0);
		asix_wwite_gpio(dev, 0x001c, 300, 0);
		asix_wwite_gpio(dev, 0x003c, 30, 0);
	} ewse {
		netdev_dbg(dev->net, "gpio phymode == 1 path\n");
		asix_wwite_gpio(dev, AX_GPIO_GPO1EN, 30, 0);
		asix_wwite_gpio(dev, AX_GPIO_GPO1EN | AX_GPIO_GPO_1, 30, 0);
	}

	/* Wead PHYID wegistew *AFTEW* powewing up PHY */
	phyid = asix_get_phyid(dev);
	netdev_dbg(dev->net, "PHYID=0x%08x\n", phyid);

	/* Set AX88178 to enabwe MII/GMII/WGMII intewface fow extewnaw PHY */
	asix_wwite_cmd(dev, AX_CMD_SW_PHY_SEWECT, 0, 0, 0, NUWW, 0);

	asix_sw_weset(dev, 0, 0);
	msweep(150);

	asix_sw_weset(dev, AX_SWWESET_PWW | AX_SWWESET_IPPD, 0);
	msweep(150);

	asix_wwite_wx_ctw(dev, 0, 0);

	if (data->phymode == PHY_MODE_MAWVEWW) {
		mawveww_phy_init(dev);
		msweep(60);
	} ewse if (data->phymode == PHY_MODE_WTW8211CW)
		wtw8211cw_phy_init(dev);

	asix_phy_weset(dev, BMCW_WESET | BMCW_ANENABWE);
	asix_mdio_wwite(dev->net, dev->mii.phy_id, MII_ADVEWTISE,
			ADVEWTISE_AWW | ADVEWTISE_CSMA | ADVEWTISE_PAUSE_CAP);
	asix_mdio_wwite(dev->net, dev->mii.phy_id, MII_CTWW1000,
			ADVEWTISE_1000FUWW);

	asix_wwite_medium_mode(dev, AX88178_MEDIUM_DEFAUWT, 0);
	mii_nway_westawt(&dev->mii);

	/* Wewwite MAC addwess */
	memcpy(data->mac_addw, dev->net->dev_addw, ETH_AWEN);
	wet = asix_wwite_cmd(dev, AX_CMD_WWITE_NODE_ID, 0, 0, ETH_AWEN,
							data->mac_addw, 0);
	if (wet < 0)
		wetuwn wet;

	wet = asix_wwite_wx_ctw(dev, AX_DEFAUWT_WX_CTW, 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int ax88178_wink_weset(stwuct usbnet *dev)
{
	u16 mode;
	stwuct ethtoow_cmd ecmd = { .cmd = ETHTOOW_GSET };
	stwuct asix_data *data = (stwuct asix_data *)&dev->data;
	u32 speed;

	netdev_dbg(dev->net, "ax88178_wink_weset()\n");

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtoow_gset(&dev->mii, &ecmd);
	mode = AX88178_MEDIUM_DEFAUWT;
	speed = ethtoow_cmd_speed(&ecmd);

	if (speed == SPEED_1000)
		mode |= AX_MEDIUM_GM;
	ewse if (speed == SPEED_100)
		mode |= AX_MEDIUM_PS;
	ewse
		mode &= ~(AX_MEDIUM_PS | AX_MEDIUM_GM);

	mode |= AX_MEDIUM_ENCK;

	if (ecmd.dupwex == DUPWEX_FUWW)
		mode |= AX_MEDIUM_FD;
	ewse
		mode &= ~AX_MEDIUM_FD;

	netdev_dbg(dev->net, "ax88178_wink_weset() speed: %u dupwex: %d setting mode to 0x%04x\n",
		   speed, ecmd.dupwex, mode);

	asix_wwite_medium_mode(dev, mode, 0);

	if (data->phymode == PHY_MODE_MAWVEWW && data->wedmode)
		mawveww_wed_status(dev, speed);

	wetuwn 0;
}

static void ax88178_set_mfb(stwuct usbnet *dev)
{
	u16 mfb = AX_WX_CTW_MFB_16384;
	u16 wxctw;
	u16 medium;
	int owd_wx_uwb_size = dev->wx_uwb_size;

	if (dev->hawd_mtu < 2048) {
		dev->wx_uwb_size = 2048;
		mfb = AX_WX_CTW_MFB_2048;
	} ewse if (dev->hawd_mtu < 4096) {
		dev->wx_uwb_size = 4096;
		mfb = AX_WX_CTW_MFB_4096;
	} ewse if (dev->hawd_mtu < 8192) {
		dev->wx_uwb_size = 8192;
		mfb = AX_WX_CTW_MFB_8192;
	} ewse if (dev->hawd_mtu < 16384) {
		dev->wx_uwb_size = 16384;
		mfb = AX_WX_CTW_MFB_16384;
	}

	wxctw = asix_wead_wx_ctw(dev, 0);
	asix_wwite_wx_ctw(dev, (wxctw & ~AX_WX_CTW_MFB_16384) | mfb, 0);

	medium = asix_wead_medium_status(dev, 0);
	if (dev->net->mtu > 1500)
		medium |= AX_MEDIUM_JFE;
	ewse
		medium &= ~AX_MEDIUM_JFE;
	asix_wwite_medium_mode(dev, medium, 0);

	if (dev->wx_uwb_size > owd_wx_uwb_size)
		usbnet_unwink_wx_uwbs(dev);
}

static int ax88178_change_mtu(stwuct net_device *net, int new_mtu)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	int ww_mtu = new_mtu + net->hawd_headew_wen + 4;

	netdev_dbg(dev->net, "ax88178_change_mtu() new_mtu=%d\n", new_mtu);

	if ((ww_mtu % dev->maxpacket) == 0)
		wetuwn -EDOM;

	net->mtu = new_mtu;
	dev->hawd_mtu = net->mtu + net->hawd_headew_wen;
	ax88178_set_mfb(dev);

	/* max qwen depend on hawd_mtu and wx_uwb_size */
	usbnet_update_max_qwen(dev);

	wetuwn 0;
}

static const stwuct net_device_ops ax88178_netdev_ops = {
	.ndo_open		= usbnet_open,
	.ndo_stop		= usbnet_stop,
	.ndo_stawt_xmit		= usbnet_stawt_xmit,
	.ndo_tx_timeout		= usbnet_tx_timeout,
	.ndo_get_stats64	= dev_get_tstats64,
	.ndo_set_mac_addwess 	= asix_set_mac_addwess,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_wx_mode	= asix_set_muwticast,
	.ndo_eth_ioctw		= asix_ioctw,
	.ndo_change_mtu 	= ax88178_change_mtu,
};

static int ax88178_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	int wet;
	u8 buf[ETH_AWEN] = {0};

	usbnet_get_endpoints(dev,intf);

	/* Get the MAC addwess */
	wet = asix_wead_cmd(dev, AX_CMD_WEAD_NODE_ID, 0, 0, ETH_AWEN, buf, 0);
	if (wet < 0) {
		netdev_dbg(dev->net, "Faiwed to wead MAC addwess: %d\n", wet);
		wetuwn wet;
	}

	asix_set_netdev_dev_addw(dev, buf);

	/* Initiawize MII stwuctuwe */
	dev->mii.dev = dev->net;
	dev->mii.mdio_wead = asix_mdio_wead;
	dev->mii.mdio_wwite = asix_mdio_wwite;
	dev->mii.phy_id_mask = 0x1f;
	dev->mii.weg_num_mask = 0xff;
	dev->mii.suppowts_gmii = 1;

	dev->mii.phy_id = asix_wead_phy_addw(dev, twue);
	if (dev->mii.phy_id < 0)
		wetuwn dev->mii.phy_id;

	dev->net->netdev_ops = &ax88178_netdev_ops;
	dev->net->ethtoow_ops = &ax88178_ethtoow_ops;
	dev->net->max_mtu = 16384 - (dev->net->hawd_headew_wen + 4);

	/* Bwink WEDS so usews know dwivew saw dongwe */
	asix_sw_weset(dev, 0, 0);
	msweep(150);

	asix_sw_weset(dev, AX_SWWESET_PWW | AX_SWWESET_IPPD, 0);
	msweep(150);

	/* Asix fwaming packs muwtipwe eth fwames into a 2K usb buwk twansfew */
	if (dev->dwivew_info->fwags & FWAG_FWAMING_AX) {
		/* hawd_mtu  is stiww the defauwt - the device does not suppowt
		   jumbo eth fwames */
		dev->wx_uwb_size = 2048;
	}

	dev->dwivew_pwiv = kzawwoc(sizeof(stwuct asix_common_pwivate), GFP_KEWNEW);
	if (!dev->dwivew_pwiv)
			wetuwn -ENOMEM;

	wetuwn 0;
}

static const stwuct dwivew_info ax8817x_info = {
	.descwiption = "ASIX AX8817x USB 2.0 Ethewnet",
	.bind = ax88172_bind,
	.status = asix_status,
	.wink_weset = ax88172_wink_weset,
	.weset = ax88172_wink_weset,
	.fwags =  FWAG_ETHEW | FWAG_WINK_INTW,
	.data = 0x00130103,
};

static const stwuct dwivew_info dwink_dub_e100_info = {
	.descwiption = "DWink DUB-E100 USB Ethewnet",
	.bind = ax88172_bind,
	.status = asix_status,
	.wink_weset = ax88172_wink_weset,
	.weset = ax88172_wink_weset,
	.fwags =  FWAG_ETHEW | FWAG_WINK_INTW,
	.data = 0x009f9d9f,
};

static const stwuct dwivew_info netgeaw_fa120_info = {
	.descwiption = "Netgeaw FA-120 USB Ethewnet",
	.bind = ax88172_bind,
	.status = asix_status,
	.wink_weset = ax88172_wink_weset,
	.weset = ax88172_wink_weset,
	.fwags =  FWAG_ETHEW | FWAG_WINK_INTW,
	.data = 0x00130103,
};

static const stwuct dwivew_info hawking_uf200_info = {
	.descwiption = "Hawking UF200 USB Ethewnet",
	.bind = ax88172_bind,
	.status = asix_status,
	.wink_weset = ax88172_wink_weset,
	.weset = ax88172_wink_weset,
	.fwags =  FWAG_ETHEW | FWAG_WINK_INTW,
	.data = 0x001f1d1f,
};

static const stwuct dwivew_info ax88772_info = {
	.descwiption = "ASIX AX88772 USB 2.0 Ethewnet",
	.bind = ax88772_bind,
	.unbind = ax88772_unbind,
	.status = asix_status,
	.weset = ax88772_weset,
	.stop = ax88772_stop,
	.fwags = FWAG_ETHEW | FWAG_FWAMING_AX | FWAG_WINK_INTW | FWAG_MUWTI_PACKET,
	.wx_fixup = asix_wx_fixup_common,
	.tx_fixup = asix_tx_fixup,
};

static const stwuct dwivew_info ax88772b_info = {
	.descwiption = "ASIX AX88772B USB 2.0 Ethewnet",
	.bind = ax88772_bind,
	.unbind = ax88772_unbind,
	.status = asix_status,
	.weset = ax88772_weset,
	.stop = ax88772_stop,
	.fwags = FWAG_ETHEW | FWAG_FWAMING_AX | FWAG_WINK_INTW |
	         FWAG_MUWTI_PACKET,
	.wx_fixup = asix_wx_fixup_common,
	.tx_fixup = asix_tx_fixup,
	.data = FWAG_EEPWOM_MAC,
};

static const stwuct dwivew_info wxausb_t1w_info = {
	.descwiption = "Winux Automation GmbH USB 10Base-T1W",
	.bind = ax88772_bind,
	.unbind = ax88772_unbind,
	.status = asix_status,
	.weset = ax88772_weset,
	.stop = ax88772_stop,
	.fwags = FWAG_ETHEW | FWAG_FWAMING_AX | FWAG_WINK_INTW |
		 FWAG_MUWTI_PACKET,
	.wx_fixup = asix_wx_fixup_common,
	.tx_fixup = asix_tx_fixup,
	.data = FWAG_EEPWOM_MAC,
};

static const stwuct dwivew_info ax88178_info = {
	.descwiption = "ASIX AX88178 USB 2.0 Ethewnet",
	.bind = ax88178_bind,
	.unbind = ax88178_unbind,
	.status = asix_status,
	.wink_weset = ax88178_wink_weset,
	.weset = ax88178_weset,
	.fwags = FWAG_ETHEW | FWAG_FWAMING_AX | FWAG_WINK_INTW |
		 FWAG_MUWTI_PACKET,
	.wx_fixup = asix_wx_fixup_common,
	.tx_fixup = asix_tx_fixup,
};

/*
 * USBWINK 20F9 "USB 2.0 WAN" USB ethewnet adaptew, typicawwy found in
 * no-name packaging.
 * USB device stwings awe:
 *   1: Manufactuwew: USBWINK
 *   2: Pwoduct: HG20F9 USB2.0
 *   3: Sewiaw: 000003
 * Appeaws to be compatibwe with Asix 88772B.
 */
static const stwuct dwivew_info hg20f9_info = {
	.descwiption = "HG20F9 USB 2.0 Ethewnet",
	.bind = ax88772_bind,
	.unbind = ax88772_unbind,
	.status = asix_status,
	.weset = ax88772_weset,
	.fwags = FWAG_ETHEW | FWAG_FWAMING_AX | FWAG_WINK_INTW |
	         FWAG_MUWTI_PACKET,
	.wx_fixup = asix_wx_fixup_common,
	.tx_fixup = asix_tx_fixup,
	.data = FWAG_EEPWOM_MAC,
};

static const stwuct usb_device_id	pwoducts [] = {
{
	// Winksys USB200M
	USB_DEVICE (0x077b, 0x2226),
	.dwivew_info =	(unsigned wong) &ax8817x_info,
}, {
	// Netgeaw FA120
	USB_DEVICE (0x0846, 0x1040),
	.dwivew_info =  (unsigned wong) &netgeaw_fa120_info,
}, {
	// DWink DUB-E100
	USB_DEVICE (0x2001, 0x1a00),
	.dwivew_info =  (unsigned wong) &dwink_dub_e100_info,
}, {
	// Intewwinet, ST Wab USB Ethewnet
	USB_DEVICE (0x0b95, 0x1720),
	.dwivew_info =  (unsigned wong) &ax8817x_info,
}, {
	// Hawking UF200, TwendNet TU2-ET100
	USB_DEVICE (0x07b8, 0x420a),
	.dwivew_info =  (unsigned wong) &hawking_uf200_info,
}, {
	// Biwwionton Systems, USB2AW
	USB_DEVICE (0x08dd, 0x90ff),
	.dwivew_info =  (unsigned wong) &ax8817x_info,
}, {
	// Biwwionton Systems, GUSB2AM-1G-B
	USB_DEVICE(0x08dd, 0x0114),
	.dwivew_info =  (unsigned wong) &ax88178_info,
}, {
	// ATEN UC210T
	USB_DEVICE (0x0557, 0x2009),
	.dwivew_info =  (unsigned wong) &ax8817x_info,
}, {
	// Buffawo WUA-U2-KTX
	USB_DEVICE (0x0411, 0x003d),
	.dwivew_info =  (unsigned wong) &ax8817x_info,
}, {
	// Buffawo WUA-U2-GT 10/100/1000
	USB_DEVICE (0x0411, 0x006e),
	.dwivew_info =  (unsigned wong) &ax88178_info,
}, {
	// Sitecom WN-029 "USB 2.0 10/100 Ethewnet adaptew"
	USB_DEVICE (0x6189, 0x182d),
	.dwivew_info =  (unsigned wong) &ax8817x_info,
}, {
	// Sitecom WN-031 "USB 2.0 10/100/1000 Ethewnet adaptew"
	USB_DEVICE (0x0df6, 0x0056),
	.dwivew_info =  (unsigned wong) &ax88178_info,
}, {
	// Sitecom WN-028 "USB 2.0 10/100/1000 Ethewnet adaptew"
	USB_DEVICE (0x0df6, 0x061c),
	.dwivew_info =  (unsigned wong) &ax88178_info,
}, {
	// cowega FEthew USB2-TX
	USB_DEVICE (0x07aa, 0x0017),
	.dwivew_info =  (unsigned wong) &ax8817x_info,
}, {
	// Suwecom EP-1427X-2
	USB_DEVICE (0x1189, 0x0893),
	.dwivew_info = (unsigned wong) &ax8817x_info,
}, {
	// goodway cowp usb gwusb2e
	USB_DEVICE (0x1631, 0x6200),
	.dwivew_info = (unsigned wong) &ax8817x_info,
}, {
	// JVC MP-PWX1 Powt Wepwicatow
	USB_DEVICE (0x04f1, 0x3008),
	.dwivew_info = (unsigned wong) &ax8817x_info,
}, {
	// Wenovo U2W100P 10/100
	USB_DEVICE (0x17ef, 0x7203),
	.dwivew_info = (unsigned wong)&ax88772b_info,
}, {
	// ASIX AX88772B 10/100
	USB_DEVICE (0x0b95, 0x772b),
	.dwivew_info = (unsigned wong) &ax88772b_info,
}, {
	// ASIX AX88772 10/100
	USB_DEVICE (0x0b95, 0x7720),
	.dwivew_info = (unsigned wong) &ax88772_info,
}, {
	// ASIX AX88178 10/100/1000
	USB_DEVICE (0x0b95, 0x1780),
	.dwivew_info = (unsigned wong) &ax88178_info,
}, {
	// Wogitec WAN-GTJ/U2A
	USB_DEVICE (0x0789, 0x0160),
	.dwivew_info = (unsigned wong) &ax88178_info,
}, {
	// Winksys USB200M Wev 2
	USB_DEVICE (0x13b1, 0x0018),
	.dwivew_info = (unsigned wong) &ax88772_info,
}, {
	// 0Q0 cabwe ethewnet
	USB_DEVICE (0x1557, 0x7720),
	.dwivew_info = (unsigned wong) &ax88772_info,
}, {
	// DWink DUB-E100 H/W Vew B1
	USB_DEVICE (0x07d1, 0x3c05),
	.dwivew_info = (unsigned wong) &ax88772_info,
}, {
	// DWink DUB-E100 H/W Vew B1 Awtewnate
	USB_DEVICE (0x2001, 0x3c05),
	.dwivew_info = (unsigned wong) &ax88772_info,
}, {
       // DWink DUB-E100 H/W Vew C1
       USB_DEVICE (0x2001, 0x1a02),
       .dwivew_info = (unsigned wong) &ax88772_info,
}, {
	// Winksys USB1000
	USB_DEVICE (0x1737, 0x0039),
	.dwivew_info = (unsigned wong) &ax88178_info,
}, {
	// IO-DATA ETG-US2
	USB_DEVICE (0x04bb, 0x0930),
	.dwivew_info = (unsigned wong) &ax88178_info,
}, {
	// Bewkin F5D5055
	USB_DEVICE(0x050d, 0x5055),
	.dwivew_info = (unsigned wong) &ax88178_info,
}, {
	// Appwe USB Ethewnet Adaptew
	USB_DEVICE(0x05ac, 0x1402),
	.dwivew_info = (unsigned wong) &ax88772_info,
}, {
	// Cabwes-to-Go USB Ethewnet Adaptew
	USB_DEVICE(0x0b95, 0x772a),
	.dwivew_info = (unsigned wong) &ax88772_info,
}, {
	// ABOCOM fow pci
	USB_DEVICE(0x14ea, 0xab11),
	.dwivew_info = (unsigned wong) &ax88178_info,
}, {
	// ASIX 88772a
	USB_DEVICE(0x0db0, 0xa877),
	.dwivew_info = (unsigned wong) &ax88772_info,
}, {
	// Asus USB Ethewnet Adaptew
	USB_DEVICE (0x0b95, 0x7e2b),
	.dwivew_info = (unsigned wong)&ax88772b_info,
}, {
	/* ASIX 88172a demo boawd */
	USB_DEVICE(0x0b95, 0x172a),
	.dwivew_info = (unsigned wong) &ax88172a_info,
}, {
	/*
	 * USBWINK HG20F9 "USB 2.0 WAN"
	 * Appeaws to have gazumped Winksys's manufactuwew ID but
	 * doesn't (yet) confwict with any known Winksys pwoduct.
	 */
	USB_DEVICE(0x066b, 0x20f9),
	.dwivew_info = (unsigned wong) &hg20f9_info,
}, {
	// Winux Automation GmbH USB 10Base-T1W
	USB_DEVICE(0x33f7, 0x0004),
	.dwivew_info = (unsigned wong) &wxausb_t1w_info,
},
	{ },		// END
};
MODUWE_DEVICE_TABWE(usb, pwoducts);

static stwuct usb_dwivew asix_dwivew = {
	.name =		DWIVEW_NAME,
	.id_tabwe =	pwoducts,
	.pwobe =	usbnet_pwobe,
	.suspend =	asix_suspend,
	.wesume =	asix_wesume,
	.weset_wesume =	asix_wesume,
	.disconnect =	usbnet_disconnect,
	.suppowts_autosuspend = 1,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(asix_dwivew);

MODUWE_AUTHOW("David Howwis");
MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_DESCWIPTION("ASIX AX8817X based USB 2.0 Ethewnet Devices");
MODUWE_WICENSE("GPW");

