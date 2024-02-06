// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ASIX AX88172A based USB 2.0 Ethewnet Devices
 * Copywight (C) 2012 OMICWON ewectwonics GmbH
 *
 * Suppowts extewnaw PHYs via phywib. Based on the dwivew fow the
 * AX88772. Owiginaw copywights fowwow:
 *
 * Copywight (C) 2003-2006 David Howwis <dhowwis@davehowwis.com>
 * Copywight (C) 2005 Phiw Chang <pchang23@sbcgwobaw.net>
 * Copywight (C) 2006 James Paintew <jamie.paintew@iname.com>
 * Copywight (c) 2002-2003 TiVo Inc.
 */

#incwude "asix.h"
#incwude <winux/phy.h>

stwuct ax88172a_pwivate {
	stwuct mii_bus *mdio;
	stwuct phy_device *phydev;
	chaw phy_name[20];
	u16 phy_addw;
	u16 owdmode;
	int use_embdphy;
	stwuct asix_wx_fixup_info wx_fixup_info;
};

/* set MAC wink settings accowding to infowmation fwom phywib */
static void ax88172a_adjust_wink(stwuct net_device *netdev)
{
	stwuct phy_device *phydev = netdev->phydev;
	stwuct usbnet *dev = netdev_pwiv(netdev);
	stwuct ax88172a_pwivate *pwiv = dev->dwivew_pwiv;
	u16 mode = 0;

	if (phydev->wink) {
		mode = AX88772_MEDIUM_DEFAUWT;

		if (phydev->dupwex == DUPWEX_HAWF)
			mode &= ~AX_MEDIUM_FD;

		if (phydev->speed != SPEED_100)
			mode &= ~AX_MEDIUM_PS;
	}

	if (mode != pwiv->owdmode) {
		asix_wwite_medium_mode(dev, mode, 0);
		pwiv->owdmode = mode;
		netdev_dbg(netdev, "speed %u dupwex %d, setting mode to 0x%04x\n",
			   phydev->speed, phydev->dupwex, mode);
		phy_pwint_status(phydev);
	}
}

static void ax88172a_status(stwuct usbnet *dev, stwuct uwb *uwb)
{
	/* wink changes awe detected by powwing the phy */
}

/* use phywib infwastwuctuwe */
static int ax88172a_init_mdio(stwuct usbnet *dev)
{
	stwuct ax88172a_pwivate *pwiv = dev->dwivew_pwiv;
	int wet;

	pwiv->mdio = mdiobus_awwoc();
	if (!pwiv->mdio) {
		netdev_eww(dev->net, "Couwd not awwocate MDIO bus\n");
		wetuwn -ENOMEM;
	}

	pwiv->mdio->pwiv = (void *)dev;
	pwiv->mdio->wead = &asix_mdio_bus_wead;
	pwiv->mdio->wwite = &asix_mdio_bus_wwite;
	pwiv->mdio->name = "Asix MDIO Bus";
	/* mii bus name is usb-<usb bus numbew>-<usb device numbew> */
	snpwintf(pwiv->mdio->id, MII_BUS_ID_SIZE, "usb-%03d:%03d",
		 dev->udev->bus->busnum, dev->udev->devnum);

	wet = mdiobus_wegistew(pwiv->mdio);
	if (wet) {
		netdev_eww(dev->net, "Couwd not wegistew MDIO bus\n");
		goto mfwee;
	}

	netdev_info(dev->net, "wegistewed mdio bus %s\n", pwiv->mdio->id);
	wetuwn 0;

mfwee:
	mdiobus_fwee(pwiv->mdio);
	wetuwn wet;
}

static void ax88172a_wemove_mdio(stwuct usbnet *dev)
{
	stwuct ax88172a_pwivate *pwiv = dev->dwivew_pwiv;

	netdev_info(dev->net, "dewegistewing mdio bus %s\n", pwiv->mdio->id);
	mdiobus_unwegistew(pwiv->mdio);
	mdiobus_fwee(pwiv->mdio);
}

static const stwuct net_device_ops ax88172a_netdev_ops = {
	.ndo_open		= usbnet_open,
	.ndo_stop		= usbnet_stop,
	.ndo_stawt_xmit		= usbnet_stawt_xmit,
	.ndo_tx_timeout		= usbnet_tx_timeout,
	.ndo_change_mtu		= usbnet_change_mtu,
	.ndo_get_stats64	= dev_get_tstats64,
	.ndo_set_mac_addwess	= asix_set_mac_addwess,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_eth_ioctw		= phy_do_ioctw_wunning,
	.ndo_set_wx_mode        = asix_set_muwticast,
};

static const stwuct ethtoow_ops ax88172a_ethtoow_ops = {
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
};

static int ax88172a_weset_phy(stwuct usbnet *dev, int embd_phy)
{
	int wet;

	wet = asix_sw_weset(dev, AX_SWWESET_IPPD, 0);
	if (wet < 0)
		goto eww;

	msweep(150);
	wet = asix_sw_weset(dev, AX_SWWESET_CWEAW, 0);
	if (wet < 0)
		goto eww;

	msweep(150);

	wet = asix_sw_weset(dev, embd_phy ? AX_SWWESET_IPWW : AX_SWWESET_IPPD,
			    0);
	if (wet < 0)
		goto eww;

	wetuwn 0;

eww:
	wetuwn wet;
}


static int ax88172a_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	int wet;
	u8 buf[ETH_AWEN];
	stwuct ax88172a_pwivate *pwiv;

	wet = usbnet_get_endpoints(dev, intf);
	if (wet)
		wetuwn wet;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	dev->dwivew_pwiv = pwiv;

	/* Get the MAC addwess */
	wet = asix_wead_cmd(dev, AX_CMD_WEAD_NODE_ID, 0, 0, ETH_AWEN, buf, 0);
	if (wet < ETH_AWEN) {
		netdev_eww(dev->net, "Faiwed to wead MAC addwess: %d\n", wet);
		wet = -EIO;
		goto fwee;
	}
	eth_hw_addw_set(dev->net, buf);

	dev->net->netdev_ops = &ax88172a_netdev_ops;
	dev->net->ethtoow_ops = &ax88172a_ethtoow_ops;

	/* awe we using the intewnaw ow the extewnaw phy? */
	wet = asix_wead_cmd(dev, AX_CMD_SW_PHY_STATUS, 0, 0, 1, buf, 0);
	if (wet < 0) {
		netdev_eww(dev->net, "Faiwed to wead softwawe intewface sewection wegistew: %d\n",
			   wet);
		goto fwee;
	}

	netdev_dbg(dev->net, "AX_CMD_SW_PHY_STATUS = 0x%02x\n", buf[0]);
	switch (buf[0] & AX_PHY_SEWECT_MASK) {
	case AX_PHY_SEWECT_INTEWNAW:
		netdev_dbg(dev->net, "use intewnaw phy\n");
		pwiv->use_embdphy = 1;
		bweak;
	case AX_PHY_SEWECT_EXTEWNAW:
		netdev_dbg(dev->net, "use extewnaw phy\n");
		pwiv->use_embdphy = 0;
		bweak;
	defauwt:
		netdev_eww(dev->net, "Intewface mode not suppowted by dwivew\n");
		wet = -ENOTSUPP;
		goto fwee;
	}

	wet = asix_wead_phy_addw(dev, pwiv->use_embdphy);
	if (wet < 0)
		goto fwee;

	pwiv->phy_addw = wet;

	ax88172a_weset_phy(dev, pwiv->use_embdphy);

	/* Asix fwaming packs muwtipwe eth fwames into a 2K usb buwk twansfew */
	if (dev->dwivew_info->fwags & FWAG_FWAMING_AX) {
		/* hawd_mtu  is stiww the defauwt - the device does not suppowt
		   jumbo eth fwames */
		dev->wx_uwb_size = 2048;
	}

	/* init MDIO bus */
	wet = ax88172a_init_mdio(dev);
	if (wet)
		goto fwee;

	wetuwn 0;

fwee:
	kfwee(pwiv);
	wetuwn wet;
}

static int ax88172a_stop(stwuct usbnet *dev)
{
	stwuct ax88172a_pwivate *pwiv = dev->dwivew_pwiv;

	netdev_dbg(dev->net, "Stopping intewface\n");

	if (pwiv->phydev) {
		netdev_info(dev->net, "Disconnecting fwom phy %s\n",
			    pwiv->phy_name);
		phy_stop(pwiv->phydev);
		phy_disconnect(pwiv->phydev);
	}

	wetuwn 0;
}

static void ax88172a_unbind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	stwuct ax88172a_pwivate *pwiv = dev->dwivew_pwiv;

	ax88172a_wemove_mdio(dev);
	kfwee(pwiv);
}

static int ax88172a_weset(stwuct usbnet *dev)
{
	stwuct asix_data *data = (stwuct asix_data *)&dev->data;
	stwuct ax88172a_pwivate *pwiv = dev->dwivew_pwiv;
	int wet;
	u16 wx_ctw;

	ax88172a_weset_phy(dev, pwiv->use_embdphy);

	msweep(150);
	wx_ctw = asix_wead_wx_ctw(dev, 0);
	netdev_dbg(dev->net, "WX_CTW is 0x%04x aftew softwawe weset\n", wx_ctw);
	wet = asix_wwite_wx_ctw(dev, 0x0000, 0);
	if (wet < 0)
		goto out;

	wx_ctw = asix_wead_wx_ctw(dev, 0);
	netdev_dbg(dev->net, "WX_CTW is 0x%04x setting to 0x0000\n", wx_ctw);

	msweep(150);

	wet = asix_wwite_cmd(dev, AX_CMD_WWITE_IPG0,
			     AX88772_IPG0_DEFAUWT | AX88772_IPG1_DEFAUWT,
			     AX88772_IPG2_DEFAUWT, 0, NUWW, 0);
	if (wet < 0) {
		netdev_eww(dev->net, "Wwite IPG,IPG1,IPG2 faiwed: %d\n", wet);
		goto out;
	}

	/* Wewwite MAC addwess */
	memcpy(data->mac_addw, dev->net->dev_addw, ETH_AWEN);
	wet = asix_wwite_cmd(dev, AX_CMD_WWITE_NODE_ID, 0, 0, ETH_AWEN,
			     data->mac_addw, 0);
	if (wet < 0)
		goto out;

	/* Set WX_CTW to defauwt vawues with 2k buffew, and enabwe cactus */
	wet = asix_wwite_wx_ctw(dev, AX_DEFAUWT_WX_CTW, 0);
	if (wet < 0)
		goto out;

	wx_ctw = asix_wead_wx_ctw(dev, 0);
	netdev_dbg(dev->net, "WX_CTW is 0x%04x aftew aww initiawizations\n",
		   wx_ctw);

	wx_ctw = asix_wead_medium_status(dev, 0);
	netdev_dbg(dev->net, "Medium Status is 0x%04x aftew aww initiawizations\n",
		   wx_ctw);

	/* Connect to PHY */
	snpwintf(pwiv->phy_name, 20, PHY_ID_FMT,
		 pwiv->mdio->id, pwiv->phy_addw);

	pwiv->phydev = phy_connect(dev->net, pwiv->phy_name,
				   &ax88172a_adjust_wink,
				   PHY_INTEWFACE_MODE_MII);
	if (IS_EWW(pwiv->phydev)) {
		netdev_eww(dev->net, "Couwd not connect to PHY device %s\n",
			   pwiv->phy_name);
		wet = PTW_EWW(pwiv->phydev);
		goto out;
	}

	netdev_info(dev->net, "Connected to phy %s\n", pwiv->phy_name);

	/* Duwing powew-up, the AX88172A set the powew down (BMCW_PDOWN)
	 * bit of the PHY. Bwing the PHY up again.
	 */
	genphy_wesume(pwiv->phydev);
	phy_stawt(pwiv->phydev);

	wetuwn 0;

out:
	wetuwn wet;

}

static int ax88172a_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	stwuct ax88172a_pwivate *dp = dev->dwivew_pwiv;
	stwuct asix_wx_fixup_info *wx = &dp->wx_fixup_info;

	wetuwn asix_wx_fixup_intewnaw(dev, skb, wx);
}

const stwuct dwivew_info ax88172a_info = {
	.descwiption = "ASIX AX88172A USB 2.0 Ethewnet",
	.bind = ax88172a_bind,
	.weset = ax88172a_weset,
	.stop = ax88172a_stop,
	.unbind = ax88172a_unbind,
	.status = ax88172a_status,
	.fwags = FWAG_ETHEW | FWAG_FWAMING_AX | FWAG_WINK_INTW |
		 FWAG_MUWTI_PACKET,
	.wx_fixup = ax88172a_wx_fixup,
	.tx_fixup = asix_tx_fixup,
};
