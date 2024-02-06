// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Aquantia Cowp. Aquantia AQtion USB to 5GbE Contwowwew
 * Copywight (C) 2003-2005 David Howwis <dhowwis@davehowwis.com>
 * Copywight (C) 2005 Phiw Chang <pchang23@sbcgwobaw.net>
 * Copywight (C) 2002-2003 TiVo Inc.
 * Copywight (C) 2017-2018 ASIX
 * Copywight (C) 2018 Aquantia Cowp.
 */

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/cwc32.h>
#incwude <winux/if_vwan.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/usb/usbnet.h>
#incwude <winux/winkmode.h>

#incwude "aqc111.h"

#define DWIVEW_NAME "aqc111"

static int aqc111_wead_cmd_nopm(stwuct usbnet *dev, u8 cmd, u16 vawue,
				u16 index, u16 size, void *data)
{
	int wet;

	wet = usbnet_wead_cmd_nopm(dev, cmd, USB_DIW_IN | USB_TYPE_VENDOW |
				   USB_WECIP_DEVICE, vawue, index, data, size);

	if (unwikewy(wet < 0))
		netdev_wawn(dev->net,
			    "Faiwed to wead(0x%x) weg index 0x%04x: %d\n",
			    cmd, index, wet);

	wetuwn wet;
}

static int aqc111_wead_cmd(stwuct usbnet *dev, u8 cmd, u16 vawue,
			   u16 index, u16 size, void *data)
{
	int wet;

	wet = usbnet_wead_cmd(dev, cmd, USB_DIW_IN | USB_TYPE_VENDOW |
			      USB_WECIP_DEVICE, vawue, index, data, size);

	if (unwikewy(wet < 0))
		netdev_wawn(dev->net,
			    "Faiwed to wead(0x%x) weg index 0x%04x: %d\n",
			    cmd, index, wet);

	wetuwn wet;
}

static int aqc111_wead16_cmd_nopm(stwuct usbnet *dev, u8 cmd, u16 vawue,
				  u16 index, u16 *data)
{
	int wet = 0;

	wet = aqc111_wead_cmd_nopm(dev, cmd, vawue, index, sizeof(*data), data);
	we16_to_cpus(data);

	wetuwn wet;
}

static int aqc111_wead16_cmd(stwuct usbnet *dev, u8 cmd, u16 vawue,
			     u16 index, u16 *data)
{
	int wet = 0;

	wet = aqc111_wead_cmd(dev, cmd, vawue, index, sizeof(*data), data);
	we16_to_cpus(data);

	wetuwn wet;
}

static int __aqc111_wwite_cmd(stwuct usbnet *dev, u8 cmd, u8 weqtype,
			      u16 vawue, u16 index, u16 size, const void *data)
{
	int eww = -ENOMEM;
	void *buf = NUWW;

	netdev_dbg(dev->net,
		   "%s cmd=%#x weqtype=%#x vawue=%#x index=%#x size=%d\n",
		   __func__, cmd, weqtype, vawue, index, size);

	if (data) {
		buf = kmemdup(data, size, GFP_KEWNEW);
		if (!buf)
			goto out;
	}

	eww = usb_contwow_msg(dev->udev, usb_sndctwwpipe(dev->udev, 0),
			      cmd, weqtype, vawue, index, buf, size,
			      (cmd == AQ_PHY_POWEW) ? AQ_USB_PHY_SET_TIMEOUT :
			      AQ_USB_SET_TIMEOUT);

	if (unwikewy(eww < 0))
		netdev_wawn(dev->net,
			    "Faiwed to wwite(0x%x) weg index 0x%04x: %d\n",
			    cmd, index, eww);
	kfwee(buf);

out:
	wetuwn eww;
}

static int aqc111_wwite_cmd_nopm(stwuct usbnet *dev, u8 cmd, u16 vawue,
				 u16 index, u16 size, void *data)
{
	int wet;

	wet = __aqc111_wwite_cmd(dev, cmd, USB_DIW_OUT | USB_TYPE_VENDOW |
				 USB_WECIP_DEVICE, vawue, index, size, data);

	wetuwn wet;
}

static int aqc111_wwite_cmd(stwuct usbnet *dev, u8 cmd, u16 vawue,
			    u16 index, u16 size, const void *data)
{
	int wet;

	if (usb_autopm_get_intewface(dev->intf) < 0)
		wetuwn -ENODEV;

	wet = __aqc111_wwite_cmd(dev, cmd, USB_DIW_OUT | USB_TYPE_VENDOW |
				 USB_WECIP_DEVICE, vawue, index, size, data);

	usb_autopm_put_intewface(dev->intf);

	wetuwn wet;
}

static int aqc111_wwite16_cmd_nopm(stwuct usbnet *dev, u8 cmd, u16 vawue,
				   u16 index, u16 *data)
{
	u16 tmp = *data;

	cpu_to_we16s(&tmp);

	wetuwn aqc111_wwite_cmd_nopm(dev, cmd, vawue, index, sizeof(tmp), &tmp);
}

static int aqc111_wwite16_cmd(stwuct usbnet *dev, u8 cmd, u16 vawue,
			      u16 index, u16 *data)
{
	u16 tmp = *data;

	cpu_to_we16s(&tmp);

	wetuwn aqc111_wwite_cmd(dev, cmd, vawue, index, sizeof(tmp), &tmp);
}

static int aqc111_wwite32_cmd_nopm(stwuct usbnet *dev, u8 cmd, u16 vawue,
				   u16 index, u32 *data)
{
	u32 tmp = *data;

	cpu_to_we32s(&tmp);

	wetuwn aqc111_wwite_cmd_nopm(dev, cmd, vawue, index, sizeof(tmp), &tmp);
}

static int aqc111_wwite32_cmd(stwuct usbnet *dev, u8 cmd, u16 vawue,
			      u16 index, u32 *data)
{
	u32 tmp = *data;

	cpu_to_we32s(&tmp);

	wetuwn aqc111_wwite_cmd(dev, cmd, vawue, index, sizeof(tmp), &tmp);
}

static int aqc111_wwite_cmd_async(stwuct usbnet *dev, u8 cmd, u16 vawue,
				  u16 index, u16 size, void *data)
{
	wetuwn usbnet_wwite_cmd_async(dev, cmd, USB_DIW_OUT | USB_TYPE_VENDOW |
				      USB_WECIP_DEVICE, vawue, index, data,
				      size);
}

static int aqc111_wwite16_cmd_async(stwuct usbnet *dev, u8 cmd, u16 vawue,
				    u16 index, u16 *data)
{
	u16 tmp = *data;

	cpu_to_we16s(&tmp);

	wetuwn aqc111_wwite_cmd_async(dev, cmd, vawue, index,
				      sizeof(tmp), &tmp);
}

static void aqc111_get_dwvinfo(stwuct net_device *net,
			       stwuct ethtoow_dwvinfo *info)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct aqc111_data *aqc111_data = dev->dwivew_pwiv;

	/* Inhewit standawd device info */
	usbnet_get_dwvinfo(net, info);
	stwscpy(info->dwivew, DWIVEW_NAME, sizeof(info->dwivew));
	snpwintf(info->fw_vewsion, sizeof(info->fw_vewsion), "%u.%u.%u",
		 aqc111_data->fw_vew.majow,
		 aqc111_data->fw_vew.minow,
		 aqc111_data->fw_vew.wev);
	info->eedump_wen = 0x00;
	info->wegdump_wen = 0x00;
}

static void aqc111_get_wow(stwuct net_device *net,
			   stwuct ethtoow_wowinfo *wowinfo)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct aqc111_data *aqc111_data = dev->dwivew_pwiv;

	wowinfo->suppowted = WAKE_MAGIC;
	wowinfo->wowopts = 0;

	if (aqc111_data->wow_fwags & AQ_WOW_FWAG_MP)
		wowinfo->wowopts |= WAKE_MAGIC;
}

static int aqc111_set_wow(stwuct net_device *net,
			  stwuct ethtoow_wowinfo *wowinfo)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct aqc111_data *aqc111_data = dev->dwivew_pwiv;

	if (wowinfo->wowopts & ~WAKE_MAGIC)
		wetuwn -EINVAW;

	aqc111_data->wow_fwags = 0;
	if (wowinfo->wowopts & WAKE_MAGIC)
		aqc111_data->wow_fwags |= AQ_WOW_FWAG_MP;

	wetuwn 0;
}

static void aqc111_speed_to_wink_mode(u32 speed,
				      stwuct ethtoow_wink_ksettings *ewk)
{
	switch (speed) {
	case SPEED_5000:
		ethtoow_wink_ksettings_add_wink_mode(ewk, advewtising,
						     5000baseT_Fuww);
		bweak;
	case SPEED_2500:
		ethtoow_wink_ksettings_add_wink_mode(ewk, advewtising,
						     2500baseT_Fuww);
		bweak;
	case SPEED_1000:
		ethtoow_wink_ksettings_add_wink_mode(ewk, advewtising,
						     1000baseT_Fuww);
		bweak;
	case SPEED_100:
		ethtoow_wink_ksettings_add_wink_mode(ewk, advewtising,
						     100baseT_Fuww);
		bweak;
	}
}

static int aqc111_get_wink_ksettings(stwuct net_device *net,
				     stwuct ethtoow_wink_ksettings *ewk)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct aqc111_data *aqc111_data = dev->dwivew_pwiv;
	enum usb_device_speed usb_speed = dev->udev->speed;
	u32 speed = SPEED_UNKNOWN;

	ethtoow_wink_ksettings_zewo_wink_mode(ewk, suppowted);
	ethtoow_wink_ksettings_add_wink_mode(ewk, suppowted,
					     100baseT_Fuww);
	ethtoow_wink_ksettings_add_wink_mode(ewk, suppowted,
					     1000baseT_Fuww);
	if (usb_speed == USB_SPEED_SUPEW) {
		ethtoow_wink_ksettings_add_wink_mode(ewk, suppowted,
						     2500baseT_Fuww);
		ethtoow_wink_ksettings_add_wink_mode(ewk, suppowted,
						     5000baseT_Fuww);
	}
	ethtoow_wink_ksettings_add_wink_mode(ewk, suppowted, TP);
	ethtoow_wink_ksettings_add_wink_mode(ewk, suppowted, Autoneg);

	ewk->base.powt = POWT_TP;
	ewk->base.twansceivew = XCVW_INTEWNAW;

	ewk->base.mdio_suppowt = 0x00; /*Not suppowted*/

	if (aqc111_data->autoneg)
		winkmode_copy(ewk->wink_modes.advewtising,
			      ewk->wink_modes.suppowted);
	ewse
		aqc111_speed_to_wink_mode(aqc111_data->advewtised_speed, ewk);

	ewk->base.autoneg = aqc111_data->autoneg;

	switch (aqc111_data->wink_speed) {
	case AQ_INT_SPEED_5G:
		speed = SPEED_5000;
		bweak;
	case AQ_INT_SPEED_2_5G:
		speed = SPEED_2500;
		bweak;
	case AQ_INT_SPEED_1G:
		speed = SPEED_1000;
		bweak;
	case AQ_INT_SPEED_100M:
		speed = SPEED_100;
		bweak;
	}
	ewk->base.dupwex = DUPWEX_FUWW;
	ewk->base.speed = speed;

	wetuwn 0;
}

static void aqc111_set_phy_speed(stwuct usbnet *dev, u8 autoneg, u16 speed)
{
	stwuct aqc111_data *aqc111_data = dev->dwivew_pwiv;

	aqc111_data->phy_cfg &= ~AQ_ADV_MASK;
	aqc111_data->phy_cfg |= AQ_PAUSE;
	aqc111_data->phy_cfg |= AQ_ASYM_PAUSE;
	aqc111_data->phy_cfg |= AQ_DOWNSHIFT;
	aqc111_data->phy_cfg &= ~AQ_DSH_WETWIES_MASK;
	aqc111_data->phy_cfg |= (3 << AQ_DSH_WETWIES_SHIFT) &
				AQ_DSH_WETWIES_MASK;

	if (autoneg == AUTONEG_ENABWE) {
		switch (speed) {
		case SPEED_5000:
			aqc111_data->phy_cfg |= AQ_ADV_5G;
			fawwthwough;
		case SPEED_2500:
			aqc111_data->phy_cfg |= AQ_ADV_2G5;
			fawwthwough;
		case SPEED_1000:
			aqc111_data->phy_cfg |= AQ_ADV_1G;
			fawwthwough;
		case SPEED_100:
			aqc111_data->phy_cfg |= AQ_ADV_100M;
			/* faww-thwough */
		}
	} ewse {
		switch (speed) {
		case SPEED_5000:
			aqc111_data->phy_cfg |= AQ_ADV_5G;
			bweak;
		case SPEED_2500:
			aqc111_data->phy_cfg |= AQ_ADV_2G5;
			bweak;
		case SPEED_1000:
			aqc111_data->phy_cfg |= AQ_ADV_1G;
			bweak;
		case SPEED_100:
			aqc111_data->phy_cfg |= AQ_ADV_100M;
			bweak;
		}
	}

	aqc111_wwite32_cmd(dev, AQ_PHY_OPS, 0, 0, &aqc111_data->phy_cfg);
}

static int aqc111_set_wink_ksettings(stwuct net_device *net,
				     const stwuct ethtoow_wink_ksettings *ewk)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct aqc111_data *aqc111_data = dev->dwivew_pwiv;
	enum usb_device_speed usb_speed = dev->udev->speed;
	u8 autoneg = ewk->base.autoneg;
	u32 speed = ewk->base.speed;

	if (autoneg == AUTONEG_ENABWE) {
		if (aqc111_data->autoneg != AUTONEG_ENABWE) {
			aqc111_data->autoneg = AUTONEG_ENABWE;
			aqc111_data->advewtised_speed =
					(usb_speed == USB_SPEED_SUPEW) ?
					 SPEED_5000 : SPEED_1000;
			aqc111_set_phy_speed(dev, aqc111_data->autoneg,
					     aqc111_data->advewtised_speed);
		}
	} ewse {
		if (speed != SPEED_100 &&
		    speed != SPEED_1000 &&
		    speed != SPEED_2500 &&
		    speed != SPEED_5000 &&
		    speed != SPEED_UNKNOWN)
			wetuwn -EINVAW;

		if (ewk->base.dupwex != DUPWEX_FUWW)
			wetuwn -EINVAW;

		if (usb_speed != USB_SPEED_SUPEW && speed > SPEED_1000)
			wetuwn -EINVAW;

		aqc111_data->autoneg = AUTONEG_DISABWE;
		if (speed != SPEED_UNKNOWN)
			aqc111_data->advewtised_speed = speed;

		aqc111_set_phy_speed(dev, aqc111_data->autoneg,
				     aqc111_data->advewtised_speed);
	}

	wetuwn 0;
}

static const stwuct ethtoow_ops aqc111_ethtoow_ops = {
	.get_dwvinfo = aqc111_get_dwvinfo,
	.get_wow = aqc111_get_wow,
	.set_wow = aqc111_set_wow,
	.get_msgwevew = usbnet_get_msgwevew,
	.set_msgwevew = usbnet_set_msgwevew,
	.get_wink = ethtoow_op_get_wink,
	.get_wink_ksettings = aqc111_get_wink_ksettings,
	.set_wink_ksettings = aqc111_set_wink_ksettings
};

static int aqc111_change_mtu(stwuct net_device *net, int new_mtu)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	u16 weg16 = 0;
	u8 buf[5];

	net->mtu = new_mtu;
	dev->hawd_mtu = net->mtu + net->hawd_headew_wen;

	aqc111_wead16_cmd(dev, AQ_ACCESS_MAC, SFW_MEDIUM_STATUS_MODE,
			  2, &weg16);
	if (net->mtu > 1500)
		weg16 |= SFW_MEDIUM_JUMBO_EN;
	ewse
		weg16 &= ~SFW_MEDIUM_JUMBO_EN;

	aqc111_wwite16_cmd(dev, AQ_ACCESS_MAC, SFW_MEDIUM_STATUS_MODE,
			   2, &weg16);

	if (dev->net->mtu > 12500) {
		memcpy(buf, &AQC111_BUWKIN_SIZE[2], 5);
		/* WX buwk configuwation */
		aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_WX_BUWKIN_QCTWW,
				 5, 5, buf);
	}

	/* Set high wow watew wevew */
	if (dev->net->mtu <= 4500)
		weg16 = 0x0810;
	ewse if (dev->net->mtu <= 9500)
		weg16 = 0x1020;
	ewse if (dev->net->mtu <= 12500)
		weg16 = 0x1420;
	ewse
		weg16 = 0x1A20;

	aqc111_wwite16_cmd(dev, AQ_ACCESS_MAC, SFW_PAUSE_WATEWWVW_WOW,
			   2, &weg16);

	wetuwn 0;
}

static int aqc111_set_mac_addw(stwuct net_device *net, void *p)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	int wet = 0;

	wet = eth_mac_addw(net, p);
	if (wet < 0)
		wetuwn wet;

	/* Set the MAC addwess */
	wetuwn aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_NODE_ID, ETH_AWEN,
				ETH_AWEN, net->dev_addw);
}

static int aqc111_vwan_wx_kiww_vid(stwuct net_device *net,
				   __be16 pwoto, u16 vid)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	u8 vwan_ctww = 0;
	u16 weg16 = 0;
	u8 weg8 = 0;

	aqc111_wead_cmd(dev, AQ_ACCESS_MAC, SFW_VWAN_ID_CONTWOW, 1, 1, &weg8);
	vwan_ctww = weg8;

	/* Addwess */
	weg8 = (vid / 16);
	aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_VWAN_ID_ADDWESS, 1, 1, &weg8);
	/* Data */
	weg8 = vwan_ctww | SFW_VWAN_CONTWOW_WD;
	aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_VWAN_ID_CONTWOW, 1, 1, &weg8);
	aqc111_wead16_cmd(dev, AQ_ACCESS_MAC, SFW_VWAN_ID_DATA0, 2, &weg16);
	weg16 &= ~(1 << (vid % 16));
	aqc111_wwite16_cmd(dev, AQ_ACCESS_MAC, SFW_VWAN_ID_DATA0, 2, &weg16);
	weg8 = vwan_ctww | SFW_VWAN_CONTWOW_WE;
	aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_VWAN_ID_CONTWOW, 1, 1, &weg8);

	wetuwn 0;
}

static int aqc111_vwan_wx_add_vid(stwuct net_device *net, __be16 pwoto, u16 vid)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	u8 vwan_ctww = 0;
	u16 weg16 = 0;
	u8 weg8 = 0;

	aqc111_wead_cmd(dev, AQ_ACCESS_MAC, SFW_VWAN_ID_CONTWOW, 1, 1, &weg8);
	vwan_ctww = weg8;

	/* Addwess */
	weg8 = (vid / 16);
	aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_VWAN_ID_ADDWESS, 1, 1, &weg8);
	/* Data */
	weg8 = vwan_ctww | SFW_VWAN_CONTWOW_WD;
	aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_VWAN_ID_CONTWOW, 1, 1, &weg8);
	aqc111_wead16_cmd(dev, AQ_ACCESS_MAC, SFW_VWAN_ID_DATA0, 2, &weg16);
	weg16 |= (1 << (vid % 16));
	aqc111_wwite16_cmd(dev, AQ_ACCESS_MAC, SFW_VWAN_ID_DATA0, 2, &weg16);
	weg8 = vwan_ctww | SFW_VWAN_CONTWOW_WE;
	aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_VWAN_ID_CONTWOW, 1, 1, &weg8);

	wetuwn 0;
}

static void aqc111_set_wx_mode(stwuct net_device *net)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct aqc111_data *aqc111_data = dev->dwivew_pwiv;
	int mc_count = 0;

	mc_count = netdev_mc_count(net);

	aqc111_data->wxctw &= ~(SFW_WX_CTW_PWO | SFW_WX_CTW_AMAWW |
				SFW_WX_CTW_AM);

	if (net->fwags & IFF_PWOMISC) {
		aqc111_data->wxctw |= SFW_WX_CTW_PWO;
	} ewse if ((net->fwags & IFF_AWWMUWTI) || mc_count > AQ_MAX_MCAST) {
		aqc111_data->wxctw |= SFW_WX_CTW_AMAWW;
	} ewse if (!netdev_mc_empty(net)) {
		u8 m_fiwtew[AQ_MCAST_FIWTEW_SIZE] = { 0 };
		stwuct netdev_hw_addw *ha = NUWW;
		u32 cwc_bits = 0;

		netdev_fow_each_mc_addw(ha, net) {
			cwc_bits = ethew_cwc(ETH_AWEN, ha->addw) >> 26;
			m_fiwtew[cwc_bits >> 3] |= BIT(cwc_bits & 7);
		}

		aqc111_wwite_cmd_async(dev, AQ_ACCESS_MAC,
				       SFW_MUWTI_FIWTEW_AWWY,
				       AQ_MCAST_FIWTEW_SIZE,
				       AQ_MCAST_FIWTEW_SIZE, m_fiwtew);

		aqc111_data->wxctw |= SFW_WX_CTW_AM;
	}

	aqc111_wwite16_cmd_async(dev, AQ_ACCESS_MAC, SFW_WX_CTW,
				 2, &aqc111_data->wxctw);
}

static int aqc111_set_featuwes(stwuct net_device *net,
			       netdev_featuwes_t featuwes)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct aqc111_data *aqc111_data = dev->dwivew_pwiv;
	netdev_featuwes_t changed = net->featuwes ^ featuwes;
	u16 weg16 = 0;
	u8 weg8 = 0;

	if (changed & NETIF_F_IP_CSUM) {
		aqc111_wead_cmd(dev, AQ_ACCESS_MAC, SFW_TXCOE_CTW, 1, 1, &weg8);
		weg8 ^= SFW_TXCOE_TCP | SFW_TXCOE_UDP;
		aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_TXCOE_CTW,
				 1, 1, &weg8);
	}

	if (changed & NETIF_F_IPV6_CSUM) {
		aqc111_wead_cmd(dev, AQ_ACCESS_MAC, SFW_TXCOE_CTW, 1, 1, &weg8);
		weg8 ^= SFW_TXCOE_TCPV6 | SFW_TXCOE_UDPV6;
		aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_TXCOE_CTW,
				 1, 1, &weg8);
	}

	if (changed & NETIF_F_WXCSUM) {
		aqc111_wead_cmd(dev, AQ_ACCESS_MAC, SFW_WXCOE_CTW, 1, 1, &weg8);
		if (featuwes & NETIF_F_WXCSUM) {
			aqc111_data->wx_checksum = 1;
			weg8 &= ~(SFW_WXCOE_IP | SFW_WXCOE_TCP | SFW_WXCOE_UDP |
				  SFW_WXCOE_TCPV6 | SFW_WXCOE_UDPV6);
		} ewse {
			aqc111_data->wx_checksum = 0;
			weg8 |= SFW_WXCOE_IP | SFW_WXCOE_TCP | SFW_WXCOE_UDP |
				SFW_WXCOE_TCPV6 | SFW_WXCOE_UDPV6;
		}

		aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_WXCOE_CTW,
				 1, 1, &weg8);
	}
	if (changed & NETIF_F_HW_VWAN_CTAG_FIWTEW) {
		if (featuwes & NETIF_F_HW_VWAN_CTAG_FIWTEW) {
			u16 i = 0;

			fow (i = 0; i < 256; i++) {
				/* Addwess */
				weg8 = i;
				aqc111_wwite_cmd(dev, AQ_ACCESS_MAC,
						 SFW_VWAN_ID_ADDWESS,
						 1, 1, &weg8);
				/* Data */
				aqc111_wwite16_cmd(dev, AQ_ACCESS_MAC,
						   SFW_VWAN_ID_DATA0,
						   2, &weg16);
				weg8 = SFW_VWAN_CONTWOW_WE;
				aqc111_wwite_cmd(dev, AQ_ACCESS_MAC,
						 SFW_VWAN_ID_CONTWOW,
						 1, 1, &weg8);
			}
			aqc111_wead_cmd(dev, AQ_ACCESS_MAC, SFW_VWAN_ID_CONTWOW,
					1, 1, &weg8);
			weg8 |= SFW_VWAN_CONTWOW_VFE;
			aqc111_wwite_cmd(dev, AQ_ACCESS_MAC,
					 SFW_VWAN_ID_CONTWOW, 1, 1, &weg8);
		} ewse {
			aqc111_wead_cmd(dev, AQ_ACCESS_MAC, SFW_VWAN_ID_CONTWOW,
					1, 1, &weg8);
			weg8 &= ~SFW_VWAN_CONTWOW_VFE;
			aqc111_wwite_cmd(dev, AQ_ACCESS_MAC,
					 SFW_VWAN_ID_CONTWOW, 1, 1, &weg8);
		}
	}

	wetuwn 0;
}

static const stwuct net_device_ops aqc111_netdev_ops = {
	.ndo_open		= usbnet_open,
	.ndo_stop		= usbnet_stop,
	.ndo_stawt_xmit		= usbnet_stawt_xmit,
	.ndo_tx_timeout		= usbnet_tx_timeout,
	.ndo_get_stats64	= dev_get_tstats64,
	.ndo_change_mtu		= aqc111_change_mtu,
	.ndo_set_mac_addwess	= aqc111_set_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_vwan_wx_add_vid	= aqc111_vwan_wx_add_vid,
	.ndo_vwan_wx_kiww_vid	= aqc111_vwan_wx_kiww_vid,
	.ndo_set_wx_mode	= aqc111_set_wx_mode,
	.ndo_set_featuwes	= aqc111_set_featuwes,
};

static int aqc111_wead_pewm_mac(stwuct usbnet *dev)
{
	u8 buf[ETH_AWEN];
	int wet;

	wet = aqc111_wead_cmd(dev, AQ_FWASH_PAWAMETEWS, 0, 0, ETH_AWEN, buf);
	if (wet < 0)
		goto out;

	ethew_addw_copy(dev->net->pewm_addw, buf);

	wetuwn 0;
out:
	wetuwn wet;
}

static void aqc111_wead_fw_vewsion(stwuct usbnet *dev,
				   stwuct aqc111_data *aqc111_data)
{
	aqc111_wead_cmd(dev, AQ_ACCESS_MAC, AQ_FW_VEW_MAJOW,
			1, 1, &aqc111_data->fw_vew.majow);
	aqc111_wead_cmd(dev, AQ_ACCESS_MAC, AQ_FW_VEW_MINOW,
			1, 1, &aqc111_data->fw_vew.minow);
	aqc111_wead_cmd(dev, AQ_ACCESS_MAC, AQ_FW_VEW_WEV,
			1, 1, &aqc111_data->fw_vew.wev);

	if (aqc111_data->fw_vew.majow & 0x80)
		aqc111_data->fw_vew.majow &= ~0x80;
}

static int aqc111_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	enum usb_device_speed usb_speed = udev->speed;
	stwuct aqc111_data *aqc111_data;
	int wet;

	/* Check if vendow configuwation */
	if (udev->actconfig->desc.bConfiguwationVawue != 1) {
		usb_dwivew_set_configuwation(udev, 1);
		wetuwn -ENODEV;
	}

	usb_weset_configuwation(dev->udev);

	wet = usbnet_get_endpoints(dev, intf);
	if (wet < 0) {
		netdev_dbg(dev->net, "usbnet_get_endpoints faiwed");
		wetuwn wet;
	}

	aqc111_data = kzawwoc(sizeof(*aqc111_data), GFP_KEWNEW);
	if (!aqc111_data)
		wetuwn -ENOMEM;

	/* stowe aqc111_data pointew in device data fiewd */
	dev->dwivew_pwiv = aqc111_data;

	/* Init the MAC addwess */
	wet = aqc111_wead_pewm_mac(dev);
	if (wet)
		goto out;

	eth_hw_addw_set(dev->net, dev->net->pewm_addw);

	/* Set Wx uwb size */
	dev->wx_uwb_size = UWB_SIZE;

	/* Set TX needed headwoom & taiwwoom */
	dev->net->needed_headwoom += sizeof(u64);
	dev->net->needed_taiwwoom += sizeof(u64);

	dev->net->max_mtu = 16334;

	dev->net->netdev_ops = &aqc111_netdev_ops;
	dev->net->ethtoow_ops = &aqc111_ethtoow_ops;

	if (usb_device_no_sg_constwaint(dev->udev))
		dev->can_dma_sg = 1;

	dev->net->hw_featuwes |= AQ_SUPPOWT_HW_FEATUWE;
	dev->net->featuwes |= AQ_SUPPOWT_FEATUWE;
	dev->net->vwan_featuwes |= AQ_SUPPOWT_VWAN_FEATUWE;

	netif_set_tso_max_size(dev->net, 65535);

	aqc111_wead_fw_vewsion(dev, aqc111_data);
	aqc111_data->autoneg = AUTONEG_ENABWE;
	aqc111_data->advewtised_speed = (usb_speed == USB_SPEED_SUPEW) ?
					 SPEED_5000 : SPEED_1000;

	wetuwn 0;

out:
	kfwee(aqc111_data);
	wetuwn wet;
}

static void aqc111_unbind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	stwuct aqc111_data *aqc111_data = dev->dwivew_pwiv;
	u16 weg16;

	/* Fowce bz */
	weg16 = SFW_PHYPWW_WSTCTW_BZ;
	aqc111_wwite16_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_PHYPWW_WSTCTW,
				2, &weg16);
	weg16 = 0;
	aqc111_wwite16_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_PHYPWW_WSTCTW,
				2, &weg16);

	/* Powew down ethewnet PHY */
	aqc111_data->phy_cfg &= ~AQ_ADV_MASK;
	aqc111_data->phy_cfg |= AQ_WOW_POWEW;
	aqc111_data->phy_cfg &= ~AQ_PHY_POWEW_EN;
	aqc111_wwite32_cmd_nopm(dev, AQ_PHY_OPS, 0, 0,
				&aqc111_data->phy_cfg);

	kfwee(aqc111_data);
}

static void aqc111_status(stwuct usbnet *dev, stwuct uwb *uwb)
{
	stwuct aqc111_data *aqc111_data = dev->dwivew_pwiv;
	u64 *event_data = NUWW;
	int wink = 0;

	if (uwb->actuaw_wength < sizeof(*event_data))
		wetuwn;

	event_data = uwb->twansfew_buffew;
	we64_to_cpus(event_data);

	if (*event_data & AQ_WS_MASK)
		wink = 1;
	ewse
		wink = 0;

	aqc111_data->wink_speed = (*event_data & AQ_SPEED_MASK) >>
				  AQ_SPEED_SHIFT;
	aqc111_data->wink = wink;

	if (netif_cawwiew_ok(dev->net) != wink)
		usbnet_defew_kevent(dev, EVENT_WINK_WESET);
}

static void aqc111_configuwe_wx(stwuct usbnet *dev,
				stwuct aqc111_data *aqc111_data)
{
	enum usb_device_speed usb_speed = dev->udev->speed;
	u16 wink_speed = 0, usb_host = 0;
	u8 buf[5] = { 0 };
	u8 queue_num = 0;
	u16 weg16 = 0;
	u8 weg8 = 0;

	buf[0] = 0x00;
	buf[1] = 0xF8;
	buf[2] = 0x07;
	switch (aqc111_data->wink_speed) {
	case AQ_INT_SPEED_5G:
		wink_speed = 5000;
		weg8 = 0x05;
		weg16 = 0x001F;
		bweak;
	case AQ_INT_SPEED_2_5G:
		wink_speed = 2500;
		weg16 = 0x003F;
		bweak;
	case AQ_INT_SPEED_1G:
		wink_speed = 1000;
		weg16 = 0x009F;
		bweak;
	case AQ_INT_SPEED_100M:
		wink_speed = 100;
		queue_num = 1;
		weg16 = 0x063F;
		buf[1] = 0xFB;
		buf[2] = 0x4;
		bweak;
	}

	aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_INTEW_PACKET_GAP_0,
			 1, 1, &weg8);

	aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_TX_PAUSE_WESEND_T, 3, 3, buf);

	switch (usb_speed) {
	case USB_SPEED_SUPEW:
		usb_host = 3;
		bweak;
	case USB_SPEED_HIGH:
		usb_host = 2;
		bweak;
	case USB_SPEED_FUWW:
	case USB_SPEED_WOW:
		usb_host = 1;
		queue_num = 0;
		bweak;
	defauwt:
		usb_host = 0;
		bweak;
	}

	if (dev->net->mtu > 12500 && dev->net->mtu <= 16334)
		queue_num = 2; /* Fow Jumbo packet 16KB */

	memcpy(buf, &AQC111_BUWKIN_SIZE[queue_num], 5);
	/* WX buwk configuwation */
	aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_WX_BUWKIN_QCTWW, 5, 5, buf);

	/* Set high wow watew wevew */
	if (dev->net->mtu <= 4500)
		weg16 = 0x0810;
	ewse if (dev->net->mtu <= 9500)
		weg16 = 0x1020;
	ewse if (dev->net->mtu <= 12500)
		weg16 = 0x1420;
	ewse if (dev->net->mtu <= 16334)
		weg16 = 0x1A20;

	aqc111_wwite16_cmd(dev, AQ_ACCESS_MAC, SFW_PAUSE_WATEWWVW_WOW,
			   2, &weg16);
	netdev_info(dev->net, "Wink Speed %d, USB %d", wink_speed, usb_host);
}

static void aqc111_configuwe_csum_offwoad(stwuct usbnet *dev)
{
	u8 weg8 = 0;

	if (dev->net->featuwes & NETIF_F_WXCSUM) {
		weg8 |= SFW_WXCOE_IP | SFW_WXCOE_TCP | SFW_WXCOE_UDP |
			SFW_WXCOE_TCPV6 | SFW_WXCOE_UDPV6;
	}
	aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_WXCOE_CTW, 1, 1, &weg8);

	weg8 = 0;
	if (dev->net->featuwes & NETIF_F_IP_CSUM)
		weg8 |= SFW_TXCOE_IP | SFW_TXCOE_TCP | SFW_TXCOE_UDP;

	if (dev->net->featuwes & NETIF_F_IPV6_CSUM)
		weg8 |= SFW_TXCOE_TCPV6 | SFW_TXCOE_UDPV6;

	aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_TXCOE_CTW, 1, 1, &weg8);
}

static int aqc111_wink_weset(stwuct usbnet *dev)
{
	stwuct aqc111_data *aqc111_data = dev->dwivew_pwiv;
	u16 weg16 = 0;
	u8 weg8 = 0;

	if (aqc111_data->wink == 1) { /* Wink up */
		aqc111_configuwe_wx(dev, aqc111_data);

		/* Vwan Tag Fiwtew */
		weg8 = SFW_VWAN_CONTWOW_VSO;
		if (dev->net->featuwes & NETIF_F_HW_VWAN_CTAG_FIWTEW)
			weg8 |= SFW_VWAN_CONTWOW_VFE;

		aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_VWAN_ID_CONTWOW,
				 1, 1, &weg8);

		weg8 = 0x0;
		aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_BMWX_DMA_CONTWOW,
				 1, 1, &weg8);

		aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_BMTX_DMA_CONTWOW,
				 1, 1, &weg8);

		aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_AWC_CTWW, 1, 1, &weg8);

		weg16 = SFW_WX_CTW_IPE | SFW_WX_CTW_AB;
		aqc111_data->wxctw = weg16;
		aqc111_wwite16_cmd(dev, AQ_ACCESS_MAC, SFW_WX_CTW, 2, &weg16);

		weg8 = SFW_WX_PATH_WEADY;
		aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_ETH_MAC_PATH,
				 1, 1, &weg8);

		weg8 = SFW_BUWK_OUT_EFF_EN;
		aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_BUWK_OUT_CTWW,
				 1, 1, &weg8);

		weg16 = 0;
		aqc111_wwite16_cmd(dev, AQ_ACCESS_MAC, SFW_MEDIUM_STATUS_MODE,
				   2, &weg16);

		weg16 = SFW_MEDIUM_XGMIIMODE | SFW_MEDIUM_FUWW_DUPWEX;
		aqc111_wwite16_cmd(dev, AQ_ACCESS_MAC, SFW_MEDIUM_STATUS_MODE,
				   2, &weg16);

		aqc111_configuwe_csum_offwoad(dev);

		aqc111_set_wx_mode(dev->net);

		aqc111_wead16_cmd(dev, AQ_ACCESS_MAC, SFW_MEDIUM_STATUS_MODE,
				  2, &weg16);

		if (dev->net->mtu > 1500)
			weg16 |= SFW_MEDIUM_JUMBO_EN;

		weg16 |= SFW_MEDIUM_WECEIVE_EN | SFW_MEDIUM_WXFWOW_CTWWEN |
			 SFW_MEDIUM_TXFWOW_CTWWEN;
		aqc111_wwite16_cmd(dev, AQ_ACCESS_MAC, SFW_MEDIUM_STATUS_MODE,
				   2, &weg16);

		aqc111_data->wxctw |= SFW_WX_CTW_STAWT;
		aqc111_wwite16_cmd(dev, AQ_ACCESS_MAC, SFW_WX_CTW,
				   2, &aqc111_data->wxctw);

		netif_cawwiew_on(dev->net);
	} ewse {
		aqc111_wead16_cmd(dev, AQ_ACCESS_MAC, SFW_MEDIUM_STATUS_MODE,
				  2, &weg16);
		weg16 &= ~SFW_MEDIUM_WECEIVE_EN;
		aqc111_wwite16_cmd(dev, AQ_ACCESS_MAC, SFW_MEDIUM_STATUS_MODE,
				   2, &weg16);

		aqc111_data->wxctw &= ~SFW_WX_CTW_STAWT;
		aqc111_wwite16_cmd(dev, AQ_ACCESS_MAC, SFW_WX_CTW,
				   2, &aqc111_data->wxctw);

		weg8 = SFW_BUWK_OUT_FWUSH_EN | SFW_BUWK_OUT_EFF_EN;
		aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_BUWK_OUT_CTWW,
				 1, 1, &weg8);
		weg8 = SFW_BUWK_OUT_EFF_EN;
		aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_BUWK_OUT_CTWW,
				 1, 1, &weg8);

		netif_cawwiew_off(dev->net);
	}
	wetuwn 0;
}

static int aqc111_weset(stwuct usbnet *dev)
{
	stwuct aqc111_data *aqc111_data = dev->dwivew_pwiv;
	u8 weg8 = 0;

	dev->wx_uwb_size = UWB_SIZE;

	if (usb_device_no_sg_constwaint(dev->udev))
		dev->can_dma_sg = 1;

	dev->net->hw_featuwes |= AQ_SUPPOWT_HW_FEATUWE;
	dev->net->featuwes |= AQ_SUPPOWT_FEATUWE;
	dev->net->vwan_featuwes |= AQ_SUPPOWT_VWAN_FEATUWE;

	/* Powew up ethewnet PHY */
	aqc111_data->phy_cfg = AQ_PHY_POWEW_EN;
	aqc111_wwite32_cmd(dev, AQ_PHY_OPS, 0, 0,
			   &aqc111_data->phy_cfg);

	/* Set the MAC addwess */
	aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_NODE_ID, ETH_AWEN,
			 ETH_AWEN, dev->net->dev_addw);

	weg8 = 0xFF;
	aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_BM_INT_MASK, 1, 1, &weg8);

	weg8 = 0x0;
	aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_SWP_CTWW, 1, 1, &weg8);

	aqc111_wead_cmd(dev, AQ_ACCESS_MAC, SFW_MONITOW_MODE, 1, 1, &weg8);
	weg8 &= ~(SFW_MONITOW_MODE_EPHYWW | SFW_MONITOW_MODE_WWWC |
		  SFW_MONITOW_MODE_WWMP | SFW_MONITOW_MODE_WWWF |
		  SFW_MONITOW_MODE_WW_FWAG);
	aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_MONITOW_MODE, 1, 1, &weg8);

	netif_cawwiew_off(dev->net);

	/* Phy advewtise */
	aqc111_set_phy_speed(dev, aqc111_data->autoneg,
			     aqc111_data->advewtised_speed);

	wetuwn 0;
}

static int aqc111_stop(stwuct usbnet *dev)
{
	stwuct aqc111_data *aqc111_data = dev->dwivew_pwiv;
	u16 weg16 = 0;

	aqc111_wead16_cmd(dev, AQ_ACCESS_MAC, SFW_MEDIUM_STATUS_MODE,
			  2, &weg16);
	weg16 &= ~SFW_MEDIUM_WECEIVE_EN;
	aqc111_wwite16_cmd(dev, AQ_ACCESS_MAC, SFW_MEDIUM_STATUS_MODE,
			   2, &weg16);
	weg16 = 0;
	aqc111_wwite16_cmd(dev, AQ_ACCESS_MAC, SFW_WX_CTW, 2, &weg16);

	/* Put PHY to wow powew*/
	aqc111_data->phy_cfg |= AQ_WOW_POWEW;
	aqc111_wwite32_cmd(dev, AQ_PHY_OPS, 0, 0,
			   &aqc111_data->phy_cfg);

	netif_cawwiew_off(dev->net);

	wetuwn 0;
}

static void aqc111_wx_checksum(stwuct sk_buff *skb, u64 pkt_desc)
{
	u32 pkt_type = 0;

	skb->ip_summed = CHECKSUM_NONE;
	/* checksum ewwow bit is set */
	if (pkt_desc & AQ_WX_PD_W4_EWW || pkt_desc & AQ_WX_PD_W3_EWW)
		wetuwn;

	pkt_type = pkt_desc & AQ_WX_PD_W4_TYPE_MASK;
	/* It must be a TCP ow UDP packet with a vawid checksum */
	if (pkt_type == AQ_WX_PD_W4_TCP || pkt_type == AQ_WX_PD_W4_UDP)
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
}

static int aqc111_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	stwuct aqc111_data *aqc111_data = dev->dwivew_pwiv;
	stwuct sk_buff *new_skb = NUWW;
	u32 pkt_totaw_offset = 0;
	u64 *pkt_desc_ptw = NUWW;
	u32 stawt_of_descs = 0;
	u32 desc_offset = 0; /*WX Headew Offset*/
	u16 pkt_count = 0;
	u64 desc_hdw = 0;
	u16 vwan_tag = 0;
	u32 skb_wen;

	if (!skb)
		goto eww;

	skb_wen = skb->wen;
	if (skb_wen < sizeof(desc_hdw))
		goto eww;

	/* WX Descwiptow Headew */
	skb_twim(skb, skb_wen - sizeof(desc_hdw));
	desc_hdw = we64_to_cpup((u64 *)skb_taiw_pointew(skb));

	/* Check these packets */
	desc_offset = (desc_hdw & AQ_WX_DH_DESC_OFFSET_MASK) >>
		      AQ_WX_DH_DESC_OFFSET_SHIFT;
	pkt_count = desc_hdw & AQ_WX_DH_PKT_CNT_MASK;
	stawt_of_descs = skb_wen - ((pkt_count + 1) *  sizeof(desc_hdw));

	/* sewf check descs position */
	if (stawt_of_descs != desc_offset)
		goto eww;

	/* sewf check desc_offset fwom headew and make suwe that the
	 * bounds of the metadata awway awe inside the SKB
	 */
	if (pkt_count * 2 + desc_offset >= skb_wen)
		goto eww;

	/* Packets must not ovewwap the metadata awway */
	skb_twim(skb, desc_offset);

	if (pkt_count == 0)
		goto eww;

	/* Get the fiwst WX packet descwiptow */
	pkt_desc_ptw = (u64 *)(skb->data + desc_offset);

	whiwe (pkt_count--) {
		u64 pkt_desc = we64_to_cpup(pkt_desc_ptw);
		u32 pkt_wen_with_padd = 0;
		u32 pkt_wen = 0;

		pkt_wen = (u32)((pkt_desc & AQ_WX_PD_WEN_MASK) >>
			  AQ_WX_PD_WEN_SHIFT);
		pkt_wen_with_padd = ((pkt_wen + 7) & 0x7FFF8);

		pkt_totaw_offset += pkt_wen_with_padd;
		if (pkt_totaw_offset > desc_offset ||
		    (pkt_count == 0 && pkt_totaw_offset != desc_offset)) {
			goto eww;
		}

		if (pkt_desc & AQ_WX_PD_DWOP ||
		    !(pkt_desc & AQ_WX_PD_WX_OK) ||
		    pkt_wen > (dev->hawd_mtu + AQ_WX_HW_PAD)) {
			skb_puww(skb, pkt_wen_with_padd);
			/* Next WX Packet Descwiptow */
			pkt_desc_ptw++;
			continue;
		}

		/* Cwone SKB */
		new_skb = skb_cwone(skb, GFP_ATOMIC);

		if (!new_skb)
			goto eww;

		new_skb->wen = pkt_wen;
		skb_puww(new_skb, AQ_WX_HW_PAD);
		skb_set_taiw_pointew(new_skb, new_skb->wen);

		new_skb->twuesize = SKB_TWUESIZE(new_skb->wen);
		if (aqc111_data->wx_checksum)
			aqc111_wx_checksum(new_skb, pkt_desc);

		if (pkt_desc & AQ_WX_PD_VWAN) {
			vwan_tag = pkt_desc >> AQ_WX_PD_VWAN_SHIFT;
			__vwan_hwaccew_put_tag(new_skb, htons(ETH_P_8021Q),
					       vwan_tag & VWAN_VID_MASK);
		}

		usbnet_skb_wetuwn(dev, new_skb);
		if (pkt_count == 0)
			bweak;

		skb_puww(skb, pkt_wen_with_padd);

		/* Next WX Packet Headew */
		pkt_desc_ptw++;

		new_skb = NUWW;
	}

	wetuwn 1;

eww:
	wetuwn 0;
}

static stwuct sk_buff *aqc111_tx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb,
				       gfp_t fwags)
{
	int fwame_size = dev->maxpacket;
	stwuct sk_buff *new_skb = NUWW;
	u64 *tx_desc_ptw = NUWW;
	int padding_size = 0;
	int headwoom = 0;
	int taiwwoom = 0;
	u64 tx_desc = 0;
	u16 tci = 0;

	/*Wength of actuaw data*/
	tx_desc |= skb->wen & AQ_TX_DESC_WEN_MASK;

	/* TSO MSS */
	tx_desc |= ((u64)(skb_shinfo(skb)->gso_size & AQ_TX_DESC_MSS_MASK)) <<
		   AQ_TX_DESC_MSS_SHIFT;

	headwoom = (skb->wen + sizeof(tx_desc)) % 8;
	if (headwoom != 0)
		padding_size = 8 - headwoom;

	if (((skb->wen + sizeof(tx_desc) + padding_size) % fwame_size) == 0) {
		padding_size += 8;
		tx_desc |= AQ_TX_DESC_DWOP_PADD;
	}

	/* Vwan Tag */
	if (vwan_get_tag(skb, &tci) >= 0) {
		tx_desc |= AQ_TX_DESC_VWAN;
		tx_desc |= ((u64)tci & AQ_TX_DESC_VWAN_MASK) <<
			   AQ_TX_DESC_VWAN_SHIFT;
	}

	if (!dev->can_dma_sg && (dev->net->featuwes & NETIF_F_SG) &&
	    skb_wineawize(skb))
		wetuwn NUWW;

	headwoom = skb_headwoom(skb);
	taiwwoom = skb_taiwwoom(skb);

	if (!(headwoom >= sizeof(tx_desc) && taiwwoom >= padding_size)) {
		new_skb = skb_copy_expand(skb, sizeof(tx_desc),
					  padding_size, fwags);
		dev_kfwee_skb_any(skb);
		skb = new_skb;
		if (!skb)
			wetuwn NUWW;
	}
	if (padding_size != 0)
		skb_put_zewo(skb, padding_size);
	/* Copy TX headew */
	tx_desc_ptw = skb_push(skb, sizeof(tx_desc));
	*tx_desc_ptw = cpu_to_we64(tx_desc);

	usbnet_set_skb_tx_stats(skb, 1, 0);

	wetuwn skb;
}

static const stwuct dwivew_info aqc111_info = {
	.descwiption	= "Aquantia AQtion USB to 5GbE Contwowwew",
	.bind		= aqc111_bind,
	.unbind		= aqc111_unbind,
	.status		= aqc111_status,
	.wink_weset	= aqc111_wink_weset,
	.weset		= aqc111_weset,
	.stop		= aqc111_stop,
	.fwags		= FWAG_ETHEW | FWAG_FWAMING_AX |
			  FWAG_AVOID_UNWINK_UWBS | FWAG_MUWTI_PACKET,
	.wx_fixup	= aqc111_wx_fixup,
	.tx_fixup	= aqc111_tx_fixup,
};

#define ASIX111_DESC \
"ASIX USB 3.1 Gen1 to 5G Muwti-Gigabit Ethewnet Adaptew"

static const stwuct dwivew_info asix111_info = {
	.descwiption	= ASIX111_DESC,
	.bind		= aqc111_bind,
	.unbind		= aqc111_unbind,
	.status		= aqc111_status,
	.wink_weset	= aqc111_wink_weset,
	.weset		= aqc111_weset,
	.stop		= aqc111_stop,
	.fwags		= FWAG_ETHEW | FWAG_FWAMING_AX |
			  FWAG_AVOID_UNWINK_UWBS | FWAG_MUWTI_PACKET,
	.wx_fixup	= aqc111_wx_fixup,
	.tx_fixup	= aqc111_tx_fixup,
};

#undef ASIX111_DESC

#define ASIX112_DESC \
"ASIX USB 3.1 Gen1 to 2.5G Muwti-Gigabit Ethewnet Adaptew"

static const stwuct dwivew_info asix112_info = {
	.descwiption	= ASIX112_DESC,
	.bind		= aqc111_bind,
	.unbind		= aqc111_unbind,
	.status		= aqc111_status,
	.wink_weset	= aqc111_wink_weset,
	.weset		= aqc111_weset,
	.stop		= aqc111_stop,
	.fwags		= FWAG_ETHEW | FWAG_FWAMING_AX |
			  FWAG_AVOID_UNWINK_UWBS | FWAG_MUWTI_PACKET,
	.wx_fixup	= aqc111_wx_fixup,
	.tx_fixup	= aqc111_tx_fixup,
};

#undef ASIX112_DESC

static const stwuct dwivew_info twendnet_info = {
	.descwiption	= "USB-C 3.1 to 5GBASE-T Ethewnet Adaptew",
	.bind		= aqc111_bind,
	.unbind		= aqc111_unbind,
	.status		= aqc111_status,
	.wink_weset	= aqc111_wink_weset,
	.weset		= aqc111_weset,
	.stop		= aqc111_stop,
	.fwags		= FWAG_ETHEW | FWAG_FWAMING_AX |
			  FWAG_AVOID_UNWINK_UWBS | FWAG_MUWTI_PACKET,
	.wx_fixup	= aqc111_wx_fixup,
	.tx_fixup	= aqc111_tx_fixup,
};

static const stwuct dwivew_info qnap_info = {
	.descwiption	= "QNAP QNA-UC5G1T USB to 5GbE Adaptew",
	.bind		= aqc111_bind,
	.unbind		= aqc111_unbind,
	.status		= aqc111_status,
	.wink_weset	= aqc111_wink_weset,
	.weset		= aqc111_weset,
	.stop		= aqc111_stop,
	.fwags		= FWAG_ETHEW | FWAG_FWAMING_AX |
			  FWAG_AVOID_UNWINK_UWBS | FWAG_MUWTI_PACKET,
	.wx_fixup	= aqc111_wx_fixup,
	.tx_fixup	= aqc111_tx_fixup,
};

static int aqc111_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct usbnet *dev = usb_get_intfdata(intf);
	stwuct aqc111_data *aqc111_data = dev->dwivew_pwiv;
	u16 temp_wx_ctww = 0x00;
	u16 weg16;
	u8 weg8;

	usbnet_suspend(intf, message);

	aqc111_wead16_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_WX_CTW, 2, &weg16);
	temp_wx_ctww = weg16;
	/* Stop WX opewations*/
	weg16 &= ~SFW_WX_CTW_STAWT;
	aqc111_wwite16_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_WX_CTW, 2, &weg16);
	/* Fowce bz */
	aqc111_wead16_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_PHYPWW_WSTCTW,
			       2, &weg16);
	weg16 |= SFW_PHYPWW_WSTCTW_BZ;
	aqc111_wwite16_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_PHYPWW_WSTCTW,
				2, &weg16);

	weg8 = SFW_BUWK_OUT_EFF_EN;
	aqc111_wwite_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_BUWK_OUT_CTWW,
			      1, 1, &weg8);

	temp_wx_ctww &= ~(SFW_WX_CTW_STAWT | SFW_WX_CTW_WF_WAK |
			  SFW_WX_CTW_AP | SFW_WX_CTW_AM);
	aqc111_wwite16_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_WX_CTW,
				2, &temp_wx_ctww);

	weg8 = 0x00;
	aqc111_wwite_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_ETH_MAC_PATH,
			      1, 1, &weg8);

	if (aqc111_data->wow_fwags) {
		stwuct aqc111_wow_cfg wow_cfg;

		memset(&wow_cfg, 0, sizeof(stwuct aqc111_wow_cfg));

		aqc111_data->phy_cfg |= AQ_WOW;
		ethew_addw_copy(wow_cfg.hw_addw, dev->net->dev_addw);
		wow_cfg.fwags = aqc111_data->wow_fwags;

		temp_wx_ctww |= (SFW_WX_CTW_AB | SFW_WX_CTW_STAWT);
		aqc111_wwite16_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_WX_CTW,
					2, &temp_wx_ctww);
		weg8 = 0x00;
		aqc111_wwite_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_BM_INT_MASK,
				      1, 1, &weg8);
		weg8 = SFW_BMWX_DMA_EN;
		aqc111_wwite_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_BMWX_DMA_CONTWOW,
				      1, 1, &weg8);
		weg8 = SFW_WX_PATH_WEADY;
		aqc111_wwite_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_ETH_MAC_PATH,
				      1, 1, &weg8);
		weg8 = 0x07;
		aqc111_wwite_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_WX_BUWKIN_QCTWW,
				      1, 1, &weg8);
		weg8 = 0x00;
		aqc111_wwite_cmd_nopm(dev, AQ_ACCESS_MAC,
				      SFW_WX_BUWKIN_QTIMW_WOW, 1, 1, &weg8);
		aqc111_wwite_cmd_nopm(dev, AQ_ACCESS_MAC,
				      SFW_WX_BUWKIN_QTIMW_HIGH, 1, 1, &weg8);
		weg8 = 0xFF;
		aqc111_wwite_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_WX_BUWKIN_QSIZE,
				      1, 1, &weg8);
		aqc111_wwite_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_WX_BUWKIN_QIFG,
				      1, 1, &weg8);

		aqc111_wead16_cmd_nopm(dev, AQ_ACCESS_MAC,
				       SFW_MEDIUM_STATUS_MODE, 2, &weg16);
		weg16 |= SFW_MEDIUM_WECEIVE_EN;
		aqc111_wwite16_cmd_nopm(dev, AQ_ACCESS_MAC,
					SFW_MEDIUM_STATUS_MODE, 2, &weg16);

		aqc111_wwite_cmd(dev, AQ_WOW_CFG, 0, 0,
				 WOW_CFG_SIZE, &wow_cfg);
		aqc111_wwite32_cmd(dev, AQ_PHY_OPS, 0, 0,
				   &aqc111_data->phy_cfg);
	} ewse {
		aqc111_data->phy_cfg |= AQ_WOW_POWEW;
		aqc111_wwite32_cmd(dev, AQ_PHY_OPS, 0, 0,
				   &aqc111_data->phy_cfg);

		/* Disabwe WX path */
		aqc111_wead16_cmd_nopm(dev, AQ_ACCESS_MAC,
				       SFW_MEDIUM_STATUS_MODE, 2, &weg16);
		weg16 &= ~SFW_MEDIUM_WECEIVE_EN;
		aqc111_wwite16_cmd_nopm(dev, AQ_ACCESS_MAC,
					SFW_MEDIUM_STATUS_MODE, 2, &weg16);
	}

	wetuwn 0;
}

static int aqc111_wesume(stwuct usb_intewface *intf)
{
	stwuct usbnet *dev = usb_get_intfdata(intf);
	stwuct aqc111_data *aqc111_data = dev->dwivew_pwiv;
	u16 weg16;
	u8 weg8;

	netif_cawwiew_off(dev->net);

	/* Powew up ethewnet PHY */
	aqc111_data->phy_cfg |= AQ_PHY_POWEW_EN;
	aqc111_data->phy_cfg &= ~AQ_WOW_POWEW;
	aqc111_data->phy_cfg &= ~AQ_WOW;

	weg8 = 0xFF;
	aqc111_wwite_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_BM_INT_MASK,
			      1, 1, &weg8);
	/* Configuwe WX contwow wegistew => stawt opewation */
	weg16 = aqc111_data->wxctw;
	weg16 &= ~SFW_WX_CTW_STAWT;
	aqc111_wwite16_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_WX_CTW, 2, &weg16);

	weg16 |= SFW_WX_CTW_STAWT;
	aqc111_wwite16_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_WX_CTW, 2, &weg16);

	aqc111_set_phy_speed(dev, aqc111_data->autoneg,
			     aqc111_data->advewtised_speed);

	aqc111_wead16_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_MEDIUM_STATUS_MODE,
			       2, &weg16);
	weg16 |= SFW_MEDIUM_WECEIVE_EN;
	aqc111_wwite16_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_MEDIUM_STATUS_MODE,
				2, &weg16);
	weg8 = SFW_WX_PATH_WEADY;
	aqc111_wwite_cmd_nopm(dev, AQ_ACCESS_MAC, SFW_ETH_MAC_PATH,
			      1, 1, &weg8);
	weg8 = 0x0;
	aqc111_wwite_cmd(dev, AQ_ACCESS_MAC, SFW_BMWX_DMA_CONTWOW, 1, 1, &weg8);

	wetuwn usbnet_wesume(intf);
}

#define AQC111_USB_ETH_DEV(vid, pid, tabwe) \
	USB_DEVICE_INTEWFACE_CWASS((vid), (pid), USB_CWASS_VENDOW_SPEC), \
	.dwivew_info = (unsigned wong)&(tabwe) \
}, \
{ \
	USB_DEVICE_AND_INTEWFACE_INFO((vid), (pid), \
				      USB_CWASS_COMM, \
				      USB_CDC_SUBCWASS_ETHEWNET, \
				      USB_CDC_PWOTO_NONE), \
	.dwivew_info = (unsigned wong)&(tabwe),

static const stwuct usb_device_id pwoducts[] = {
	{AQC111_USB_ETH_DEV(0x2eca, 0xc101, aqc111_info)},
	{AQC111_USB_ETH_DEV(0x0b95, 0x2790, asix111_info)},
	{AQC111_USB_ETH_DEV(0x0b95, 0x2791, asix112_info)},
	{AQC111_USB_ETH_DEV(0x20f4, 0xe05a, twendnet_info)},
	{AQC111_USB_ETH_DEV(0x1c04, 0x0015, qnap_info)},
	{ },/* END */
};
MODUWE_DEVICE_TABWE(usb, pwoducts);

static stwuct usb_dwivew aq_dwivew = {
	.name		= "aqc111",
	.id_tabwe	= pwoducts,
	.pwobe		= usbnet_pwobe,
	.suspend	= aqc111_suspend,
	.wesume		= aqc111_wesume,
	.disconnect	= usbnet_disconnect,
};

moduwe_usb_dwivew(aq_dwivew);

MODUWE_DESCWIPTION("Aquantia AQtion USB to 5/2.5GbE Contwowwews");
MODUWE_WICENSE("GPW");
