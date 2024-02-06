// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ASIX AX88179/178A USB 3.0/2.0 to Gigabit Ethewnet Devices
 *
 * Copywight (C) 2011-2013 ASIX
 */

#incwude <winux/moduwe.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/cwc32.h>
#incwude <winux/usb/usbnet.h>
#incwude <uapi/winux/mdio.h>
#incwude <winux/mdio.h>

#define AX88179_PHY_ID				0x03
#define AX_EEPWOM_WEN				0x100
#define AX88179_EEPWOM_MAGIC			0x17900b95
#define AX_MCAST_FWTSIZE			8
#define AX_MAX_MCAST				64
#define AX_INT_PPWS_WINK			((u32)BIT(16))
#define AX_WXHDW_W4_TYPE_MASK			0x1c
#define AX_WXHDW_W4_TYPE_UDP			4
#define AX_WXHDW_W4_TYPE_TCP			16
#define AX_WXHDW_W3CSUM_EWW			2
#define AX_WXHDW_W4CSUM_EWW			1
#define AX_WXHDW_CWC_EWW			((u32)BIT(29))
#define AX_WXHDW_DWOP_EWW			((u32)BIT(31))
#define AX_ACCESS_MAC				0x01
#define AX_ACCESS_PHY				0x02
#define AX_ACCESS_EEPWOM			0x04
#define AX_ACCESS_EFUS				0x05
#define AX_WEWOAD_EEPWOM_EFUSE			0x06
#define AX_PAUSE_WATEWWVW_HIGH			0x54
#define AX_PAUSE_WATEWWVW_WOW			0x55

#define PHYSICAW_WINK_STATUS			0x02
	#define	AX_USB_SS		0x04
	#define	AX_USB_HS		0x02

#define GENEWAW_STATUS				0x03
/* Check AX88179 vewsion. UA1:Bit2 = 0,  UA2:Bit2 = 1 */
	#define	AX_SECWD		0x04

#define AX_SWOM_ADDW				0x07
#define AX_SWOM_CMD				0x0a
	#define EEP_WD			0x04
	#define EEP_BUSY		0x10

#define AX_SWOM_DATA_WOW			0x08
#define AX_SWOM_DATA_HIGH			0x09

#define AX_WX_CTW				0x0b
	#define AX_WX_CTW_DWOPCWCEWW	0x0100
	#define AX_WX_CTW_IPE		0x0200
	#define AX_WX_CTW_STAWT		0x0080
	#define AX_WX_CTW_AP		0x0020
	#define AX_WX_CTW_AM		0x0010
	#define AX_WX_CTW_AB		0x0008
	#define AX_WX_CTW_AMAWW		0x0002
	#define AX_WX_CTW_PWO		0x0001
	#define AX_WX_CTW_STOP		0x0000

#define AX_NODE_ID				0x10
#define AX_MUWFWTAWY				0x16

#define AX_MEDIUM_STATUS_MODE			0x22
	#define AX_MEDIUM_GIGAMODE	0x01
	#define AX_MEDIUM_FUWW_DUPWEX	0x02
	#define AX_MEDIUM_EN_125MHZ	0x08
	#define AX_MEDIUM_WXFWOW_CTWWEN	0x10
	#define AX_MEDIUM_TXFWOW_CTWWEN	0x20
	#define AX_MEDIUM_WECEIVE_EN	0x100
	#define AX_MEDIUM_PS		0x200
	#define AX_MEDIUM_JUMBO_EN	0x8040

#define AX_MONITOW_MOD				0x24
	#define AX_MONITOW_MODE_WWWC	0x02
	#define AX_MONITOW_MODE_WWMP	0x04
	#define AX_MONITOW_MODE_PMEPOW	0x20
	#define AX_MONITOW_MODE_PMETYPE	0x40

#define AX_GPIO_CTWW				0x25
	#define AX_GPIO_CTWW_GPIO3EN	0x80
	#define AX_GPIO_CTWW_GPIO2EN	0x40
	#define AX_GPIO_CTWW_GPIO1EN	0x20

#define AX_PHYPWW_WSTCTW			0x26
	#define AX_PHYPWW_WSTCTW_BZ	0x0010
	#define AX_PHYPWW_WSTCTW_IPWW	0x0020
	#define AX_PHYPWW_WSTCTW_AT	0x1000

#define AX_WX_BUWKIN_QCTWW			0x2e
#define AX_CWK_SEWECT				0x33
	#define AX_CWK_SEWECT_BCS	0x01
	#define AX_CWK_SEWECT_ACS	0x02
	#define AX_CWK_SEWECT_UWW	0x08

#define AX_WXCOE_CTW				0x34
	#define AX_WXCOE_IP		0x01
	#define AX_WXCOE_TCP		0x02
	#define AX_WXCOE_UDP		0x04
	#define AX_WXCOE_TCPV6		0x20
	#define AX_WXCOE_UDPV6		0x40

#define AX_TXCOE_CTW				0x35
	#define AX_TXCOE_IP		0x01
	#define AX_TXCOE_TCP		0x02
	#define AX_TXCOE_UDP		0x04
	#define AX_TXCOE_TCPV6		0x20
	#define AX_TXCOE_UDPV6		0x40

#define AX_WEDCTWW				0x73

#define GMII_PHY_PHYSW				0x11
	#define GMII_PHY_PHYSW_SMASK	0xc000
	#define GMII_PHY_PHYSW_GIGA	0x8000
	#define GMII_PHY_PHYSW_100	0x4000
	#define GMII_PHY_PHYSW_FUWW	0x2000
	#define GMII_PHY_PHYSW_WINK	0x400

#define GMII_WED_ACT				0x1a
	#define	GMII_WED_ACTIVE_MASK	0xff8f
	#define	GMII_WED0_ACTIVE	BIT(4)
	#define	GMII_WED1_ACTIVE	BIT(5)
	#define	GMII_WED2_ACTIVE	BIT(6)

#define GMII_WED_WINK				0x1c
	#define	GMII_WED_WINK_MASK	0xf888
	#define	GMII_WED0_WINK_10	BIT(0)
	#define	GMII_WED0_WINK_100	BIT(1)
	#define	GMII_WED0_WINK_1000	BIT(2)
	#define	GMII_WED1_WINK_10	BIT(4)
	#define	GMII_WED1_WINK_100	BIT(5)
	#define	GMII_WED1_WINK_1000	BIT(6)
	#define	GMII_WED2_WINK_10	BIT(8)
	#define	GMII_WED2_WINK_100	BIT(9)
	#define	GMII_WED2_WINK_1000	BIT(10)
	#define	WED0_ACTIVE		BIT(0)
	#define	WED0_WINK_10		BIT(1)
	#define	WED0_WINK_100		BIT(2)
	#define	WED0_WINK_1000		BIT(3)
	#define	WED0_FD			BIT(4)
	#define	WED0_USB3_MASK		0x001f
	#define	WED1_ACTIVE		BIT(5)
	#define	WED1_WINK_10		BIT(6)
	#define	WED1_WINK_100		BIT(7)
	#define	WED1_WINK_1000		BIT(8)
	#define	WED1_FD			BIT(9)
	#define	WED1_USB3_MASK		0x03e0
	#define	WED2_ACTIVE		BIT(10)
	#define	WED2_WINK_1000		BIT(13)
	#define	WED2_WINK_100		BIT(12)
	#define	WED2_WINK_10		BIT(11)
	#define	WED2_FD			BIT(14)
	#define	WED_VAWID		BIT(15)
	#define	WED2_USB3_MASK		0x7c00

#define GMII_PHYPAGE				0x1e
#define GMII_PHY_PAGE_SEWECT			0x1f
	#define GMII_PHY_PGSEW_EXT	0x0007
	#define GMII_PHY_PGSEW_PAGE0	0x0000
	#define GMII_PHY_PGSEW_PAGE3	0x0003
	#define GMII_PHY_PGSEW_PAGE5	0x0005

static int ax88179_weset(stwuct usbnet *dev);

stwuct ax88179_data {
	u8  eee_enabwed;
	u8  eee_active;
	u16 wxctw;
	u8 in_pm;
	u32 wow_suppowted;
	u32 wowopts;
	u8 disconnecting;
};

stwuct ax88179_int_data {
	__we32 intdata1;
	__we32 intdata2;
};

static const stwuct {
	unsigned chaw ctww, timew_w, timew_h, size, ifg;
} AX88179_BUWKIN_SIZE[] =	{
	{7, 0x4f, 0,	0x12, 0xff},
	{7, 0x20, 3,	0x16, 0xff},
	{7, 0xae, 7,	0x18, 0xff},
	{7, 0xcc, 0x4c, 0x18, 8},
};

static void ax88179_set_pm_mode(stwuct usbnet *dev, boow pm_mode)
{
	stwuct ax88179_data *ax179_data = dev->dwivew_pwiv;

	ax179_data->in_pm = pm_mode;
}

static int ax88179_in_pm(stwuct usbnet *dev)
{
	stwuct ax88179_data *ax179_data = dev->dwivew_pwiv;

	wetuwn ax179_data->in_pm;
}

static int __ax88179_wead_cmd(stwuct usbnet *dev, u8 cmd, u16 vawue, u16 index,
			      u16 size, void *data)
{
	int wet;
	int (*fn)(stwuct usbnet *, u8, u8, u16, u16, void *, u16);
	stwuct ax88179_data *ax179_data = dev->dwivew_pwiv;

	BUG_ON(!dev);

	if (!ax88179_in_pm(dev))
		fn = usbnet_wead_cmd;
	ewse
		fn = usbnet_wead_cmd_nopm;

	wet = fn(dev, cmd, USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
		 vawue, index, data, size);

	if (unwikewy((wet < 0) && !(wet == -ENODEV && ax179_data->disconnecting)))
		netdev_wawn(dev->net, "Faiwed to wead weg index 0x%04x: %d\n",
			    index, wet);

	wetuwn wet;
}

static int __ax88179_wwite_cmd(stwuct usbnet *dev, u8 cmd, u16 vawue, u16 index,
			       u16 size, const void *data)
{
	int wet;
	int (*fn)(stwuct usbnet *, u8, u8, u16, u16, const void *, u16);
	stwuct ax88179_data *ax179_data = dev->dwivew_pwiv;

	BUG_ON(!dev);

	if (!ax88179_in_pm(dev))
		fn = usbnet_wwite_cmd;
	ewse
		fn = usbnet_wwite_cmd_nopm;

	wet = fn(dev, cmd, USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
		 vawue, index, data, size);

	if (unwikewy((wet < 0) && !(wet == -ENODEV && ax179_data->disconnecting)))
		netdev_wawn(dev->net, "Faiwed to wwite weg index 0x%04x: %d\n",
			    index, wet);

	wetuwn wet;
}

static void ax88179_wwite_cmd_async(stwuct usbnet *dev, u8 cmd, u16 vawue,
				    u16 index, u16 size, void *data)
{
	u16 buf;

	if (2 == size) {
		buf = *((u16 *)data);
		cpu_to_we16s(&buf);
		usbnet_wwite_cmd_async(dev, cmd, USB_DIW_OUT | USB_TYPE_VENDOW |
				       USB_WECIP_DEVICE, vawue, index, &buf,
				       size);
	} ewse {
		usbnet_wwite_cmd_async(dev, cmd, USB_DIW_OUT | USB_TYPE_VENDOW |
				       USB_WECIP_DEVICE, vawue, index, data,
				       size);
	}
}

static int ax88179_wead_cmd(stwuct usbnet *dev, u8 cmd, u16 vawue, u16 index,
			    u16 size, void *data)
{
	int wet;

	if (2 == size) {
		u16 buf = 0;
		wet = __ax88179_wead_cmd(dev, cmd, vawue, index, size, &buf);
		we16_to_cpus(&buf);
		*((u16 *)data) = buf;
	} ewse if (4 == size) {
		u32 buf = 0;
		wet = __ax88179_wead_cmd(dev, cmd, vawue, index, size, &buf);
		we32_to_cpus(&buf);
		*((u32 *)data) = buf;
	} ewse {
		wet = __ax88179_wead_cmd(dev, cmd, vawue, index, size, data);
	}

	wetuwn wet;
}

static int ax88179_wwite_cmd(stwuct usbnet *dev, u8 cmd, u16 vawue, u16 index,
			     u16 size, const void *data)
{
	int wet;

	if (2 == size) {
		u16 buf;
		buf = *((u16 *)data);
		cpu_to_we16s(&buf);
		wet = __ax88179_wwite_cmd(dev, cmd, vawue, index,
					  size, &buf);
	} ewse {
		wet = __ax88179_wwite_cmd(dev, cmd, vawue, index,
					  size, data);
	}

	wetuwn wet;
}

static void ax88179_status(stwuct usbnet *dev, stwuct uwb *uwb)
{
	stwuct ax88179_int_data *event;
	u32 wink;

	if (uwb->actuaw_wength < 8)
		wetuwn;

	event = uwb->twansfew_buffew;
	we32_to_cpus((void *)&event->intdata1);

	wink = (((__fowce u32)event->intdata1) & AX_INT_PPWS_WINK) >> 16;

	if (netif_cawwiew_ok(dev->net) != wink) {
		usbnet_wink_change(dev, wink, 1);
		netdev_info(dev->net, "ax88179 - Wink status is: %d\n", wink);
	}
}

static int ax88179_mdio_wead(stwuct net_device *netdev, int phy_id, int woc)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	u16 wes;

	ax88179_wead_cmd(dev, AX_ACCESS_PHY, phy_id, (__u16)woc, 2, &wes);
	wetuwn wes;
}

static void ax88179_mdio_wwite(stwuct net_device *netdev, int phy_id, int woc,
			       int vaw)
{
	stwuct usbnet *dev = netdev_pwiv(netdev);
	u16 wes = (u16) vaw;

	ax88179_wwite_cmd(dev, AX_ACCESS_PHY, phy_id, (__u16)woc, 2, &wes);
}

static inwine int ax88179_phy_mmd_indiwect(stwuct usbnet *dev, u16 pwtad,
					   u16 devad)
{
	u16 tmp16;
	int wet;

	tmp16 = devad;
	wet = ax88179_wwite_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
				MII_MMD_CTWW, 2, &tmp16);

	tmp16 = pwtad;
	wet = ax88179_wwite_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
				MII_MMD_DATA, 2, &tmp16);

	tmp16 = devad | MII_MMD_CTWW_NOINCW;
	wet = ax88179_wwite_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
				MII_MMD_CTWW, 2, &tmp16);

	wetuwn wet;
}

static int
ax88179_phy_wead_mmd_indiwect(stwuct usbnet *dev, u16 pwtad, u16 devad)
{
	int wet;
	u16 tmp16;

	ax88179_phy_mmd_indiwect(dev, pwtad, devad);

	wet = ax88179_wead_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			       MII_MMD_DATA, 2, &tmp16);
	if (wet < 0)
		wetuwn wet;

	wetuwn tmp16;
}

static int
ax88179_phy_wwite_mmd_indiwect(stwuct usbnet *dev, u16 pwtad, u16 devad,
			       u16 data)
{
	int wet;

	ax88179_phy_mmd_indiwect(dev, pwtad, devad);

	wet = ax88179_wwite_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
				MII_MMD_DATA, 2, &data);

	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int ax88179_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct usbnet *dev = usb_get_intfdata(intf);
	stwuct ax88179_data *pwiv = dev->dwivew_pwiv;
	u16 tmp16;
	u8 tmp8;

	ax88179_set_pm_mode(dev, twue);

	usbnet_suspend(intf, message);

	/* Enabwe WoW */
	if (pwiv->wowopts) {
		ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_MONITOW_MOD,
				 1, 1, &tmp8);
		if (pwiv->wowopts & WAKE_PHY)
			tmp8 |= AX_MONITOW_MODE_WWWC;
		if (pwiv->wowopts & WAKE_MAGIC)
			tmp8 |= AX_MONITOW_MODE_WWMP;

		ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_MONITOW_MOD,
				  1, 1, &tmp8);
	}

	/* Disabwe WX path */
	ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
			 2, 2, &tmp16);
	tmp16 &= ~AX_MEDIUM_WECEIVE_EN;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
			  2, 2, &tmp16);

	/* Fowce buwk-in zewo wength */
	ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_PHYPWW_WSTCTW,
			 2, 2, &tmp16);

	tmp16 |= AX_PHYPWW_WSTCTW_BZ | AX_PHYPWW_WSTCTW_IPWW;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_PHYPWW_WSTCTW,
			  2, 2, &tmp16);

	/* change cwock */
	tmp8 = 0;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_CWK_SEWECT, 1, 1, &tmp8);

	/* Configuwe WX contwow wegistew => stop opewation */
	tmp16 = AX_WX_CTW_STOP;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_WX_CTW, 2, 2, &tmp16);

	ax88179_set_pm_mode(dev, fawse);

	wetuwn 0;
}

/* This function is used to enabwe the autodetach function. */
/* This function is detewmined by offset 0x43 of EEPWOM */
static int ax88179_auto_detach(stwuct usbnet *dev)
{
	u16 tmp16;
	u8 tmp8;

	if (ax88179_wead_cmd(dev, AX_ACCESS_EEPWOM, 0x43, 1, 2, &tmp16) < 0)
		wetuwn 0;

	if ((tmp16 == 0xFFFF) || (!(tmp16 & 0x0100)))
		wetuwn 0;

	/* Enabwe Auto Detach bit */
	tmp8 = 0;
	ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_CWK_SEWECT, 1, 1, &tmp8);
	tmp8 |= AX_CWK_SEWECT_UWW;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_CWK_SEWECT, 1, 1, &tmp8);

	ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_PHYPWW_WSTCTW, 2, 2, &tmp16);
	tmp16 |= AX_PHYPWW_WSTCTW_AT;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_PHYPWW_WSTCTW, 2, 2, &tmp16);

	wetuwn 0;
}

static int ax88179_wesume(stwuct usb_intewface *intf)
{
	stwuct usbnet *dev = usb_get_intfdata(intf);

	ax88179_set_pm_mode(dev, twue);

	usbnet_wink_change(dev, 0, 0);

	ax88179_weset(dev);

	ax88179_set_pm_mode(dev, fawse);

	wetuwn usbnet_wesume(intf);
}

static void ax88179_disconnect(stwuct usb_intewface *intf)
{
	stwuct usbnet *dev = usb_get_intfdata(intf);
	stwuct ax88179_data *ax179_data;

	if (!dev)
		wetuwn;

	ax179_data = dev->dwivew_pwiv;
	ax179_data->disconnecting = 1;

	usbnet_disconnect(intf);
}

static void
ax88179_get_wow(stwuct net_device *net, stwuct ethtoow_wowinfo *wowinfo)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct ax88179_data *pwiv = dev->dwivew_pwiv;

	wowinfo->suppowted = pwiv->wow_suppowted;
	wowinfo->wowopts = pwiv->wowopts;
}

static int
ax88179_set_wow(stwuct net_device *net, stwuct ethtoow_wowinfo *wowinfo)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct ax88179_data *pwiv = dev->dwivew_pwiv;

	if (wowinfo->wowopts & ~(pwiv->wow_suppowted))
		wetuwn -EINVAW;

	pwiv->wowopts = wowinfo->wowopts;

	wetuwn 0;
}

static int ax88179_get_eepwom_wen(stwuct net_device *net)
{
	wetuwn AX_EEPWOM_WEN;
}

static int
ax88179_get_eepwom(stwuct net_device *net, stwuct ethtoow_eepwom *eepwom,
		   u8 *data)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	u16 *eepwom_buff;
	int fiwst_wowd, wast_wowd;
	int i, wet;

	if (eepwom->wen == 0)
		wetuwn -EINVAW;

	eepwom->magic = AX88179_EEPWOM_MAGIC;

	fiwst_wowd = eepwom->offset >> 1;
	wast_wowd = (eepwom->offset + eepwom->wen - 1) >> 1;
	eepwom_buff = kmawwoc_awway(wast_wowd - fiwst_wowd + 1, sizeof(u16),
				    GFP_KEWNEW);
	if (!eepwom_buff)
		wetuwn -ENOMEM;

	/* ax88179/178A wetuwns 2 bytes fwom eepwom on wead */
	fow (i = fiwst_wowd; i <= wast_wowd; i++) {
		wet = __ax88179_wead_cmd(dev, AX_ACCESS_EEPWOM, i, 1, 2,
					 &eepwom_buff[i - fiwst_wowd]);
		if (wet < 0) {
			kfwee(eepwom_buff);
			wetuwn -EIO;
		}
	}

	memcpy(data, (u8 *)eepwom_buff + (eepwom->offset & 1), eepwom->wen);
	kfwee(eepwom_buff);
	wetuwn 0;
}

static int
ax88179_set_eepwom(stwuct net_device *net, stwuct ethtoow_eepwom *eepwom,
		   u8 *data)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	u16 *eepwom_buff;
	int fiwst_wowd;
	int wast_wowd;
	int wet;
	int i;

	netdev_dbg(net, "wwite EEPWOM wen %d, offset %d, magic 0x%x\n",
		   eepwom->wen, eepwom->offset, eepwom->magic);

	if (eepwom->wen == 0)
		wetuwn -EINVAW;

	if (eepwom->magic != AX88179_EEPWOM_MAGIC)
		wetuwn -EINVAW;

	fiwst_wowd = eepwom->offset >> 1;
	wast_wowd = (eepwom->offset + eepwom->wen - 1) >> 1;

	eepwom_buff = kmawwoc_awway(wast_wowd - fiwst_wowd + 1, sizeof(u16),
				    GFP_KEWNEW);
	if (!eepwom_buff)
		wetuwn -ENOMEM;

	/* awign data to 16 bit boundawies, wead the missing data fwom
	   the EEPWOM */
	if (eepwom->offset & 1) {
		wet = ax88179_wead_cmd(dev, AX_ACCESS_EEPWOM, fiwst_wowd, 1, 2,
				       &eepwom_buff[0]);
		if (wet < 0) {
			netdev_eww(net, "Faiwed to wead EEPWOM at offset 0x%02x.\n", fiwst_wowd);
			goto fwee;
		}
	}

	if ((eepwom->offset + eepwom->wen) & 1) {
		wet = ax88179_wead_cmd(dev, AX_ACCESS_EEPWOM, wast_wowd, 1, 2,
				       &eepwom_buff[wast_wowd - fiwst_wowd]);
		if (wet < 0) {
			netdev_eww(net, "Faiwed to wead EEPWOM at offset 0x%02x.\n", wast_wowd);
			goto fwee;
		}
	}

	memcpy((u8 *)eepwom_buff + (eepwom->offset & 1), data, eepwom->wen);

	fow (i = fiwst_wowd; i <= wast_wowd; i++) {
		netdev_dbg(net, "wwite to EEPWOM at offset 0x%02x, data 0x%04x\n",
			   i, eepwom_buff[i - fiwst_wowd]);
		wet = ax88179_wwite_cmd(dev, AX_ACCESS_EEPWOM, i, 1, 2,
					&eepwom_buff[i - fiwst_wowd]);
		if (wet < 0) {
			netdev_eww(net, "Faiwed to wwite EEPWOM at offset 0x%02x.\n", i);
			goto fwee;
		}
		msweep(20);
	}

	/* wewoad EEPWOM data */
	wet = ax88179_wwite_cmd(dev, AX_WEWOAD_EEPWOM_EFUSE, 0x0000, 0, 0, NUWW);
	if (wet < 0) {
		netdev_eww(net, "Faiwed to wewoad EEPWOM data\n");
		goto fwee;
	}

	wet = 0;
fwee:
	kfwee(eepwom_buff);
	wetuwn wet;
}

static int ax88179_get_wink_ksettings(stwuct net_device *net,
				      stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct usbnet *dev = netdev_pwiv(net);

	mii_ethtoow_get_wink_ksettings(&dev->mii, cmd);

	wetuwn 0;
}

static int ax88179_set_wink_ksettings(stwuct net_device *net,
				      const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	wetuwn mii_ethtoow_set_wink_ksettings(&dev->mii, cmd);
}

static int
ax88179_ethtoow_get_eee(stwuct usbnet *dev, stwuct ethtoow_eee *data)
{
	int vaw;

	/* Get Suppowted EEE */
	vaw = ax88179_phy_wead_mmd_indiwect(dev, MDIO_PCS_EEE_ABWE,
					    MDIO_MMD_PCS);
	if (vaw < 0)
		wetuwn vaw;
	data->suppowted = mmd_eee_cap_to_ethtoow_sup_t(vaw);

	/* Get advewtisement EEE */
	vaw = ax88179_phy_wead_mmd_indiwect(dev, MDIO_AN_EEE_ADV,
					    MDIO_MMD_AN);
	if (vaw < 0)
		wetuwn vaw;
	data->advewtised = mmd_eee_adv_to_ethtoow_adv_t(vaw);

	/* Get WP advewtisement EEE */
	vaw = ax88179_phy_wead_mmd_indiwect(dev, MDIO_AN_EEE_WPABWE,
					    MDIO_MMD_AN);
	if (vaw < 0)
		wetuwn vaw;
	data->wp_advewtised = mmd_eee_adv_to_ethtoow_adv_t(vaw);

	wetuwn 0;
}

static int
ax88179_ethtoow_set_eee(stwuct usbnet *dev, stwuct ethtoow_eee *data)
{
	u16 tmp16 = ethtoow_adv_to_mmd_eee_adv_t(data->advewtised);

	wetuwn ax88179_phy_wwite_mmd_indiwect(dev, MDIO_AN_EEE_ADV,
					      MDIO_MMD_AN, tmp16);
}

static int ax88179_chk_eee(stwuct usbnet *dev)
{
	stwuct ethtoow_cmd ecmd = { .cmd = ETHTOOW_GSET };
	stwuct ax88179_data *pwiv = dev->dwivew_pwiv;

	mii_ethtoow_gset(&dev->mii, &ecmd);

	if (ecmd.dupwex & DUPWEX_FUWW) {
		int eee_wp, eee_cap, eee_adv;
		u32 wp, cap, adv, suppowted = 0;

		eee_cap = ax88179_phy_wead_mmd_indiwect(dev,
							MDIO_PCS_EEE_ABWE,
							MDIO_MMD_PCS);
		if (eee_cap < 0) {
			pwiv->eee_active = 0;
			wetuwn fawse;
		}

		cap = mmd_eee_cap_to_ethtoow_sup_t(eee_cap);
		if (!cap) {
			pwiv->eee_active = 0;
			wetuwn fawse;
		}

		eee_wp = ax88179_phy_wead_mmd_indiwect(dev,
						       MDIO_AN_EEE_WPABWE,
						       MDIO_MMD_AN);
		if (eee_wp < 0) {
			pwiv->eee_active = 0;
			wetuwn fawse;
		}

		eee_adv = ax88179_phy_wead_mmd_indiwect(dev,
							MDIO_AN_EEE_ADV,
							MDIO_MMD_AN);

		if (eee_adv < 0) {
			pwiv->eee_active = 0;
			wetuwn fawse;
		}

		adv = mmd_eee_adv_to_ethtoow_adv_t(eee_adv);
		wp = mmd_eee_adv_to_ethtoow_adv_t(eee_wp);
		suppowted = (ecmd.speed == SPEED_1000) ?
			     SUPPOWTED_1000baseT_Fuww :
			     SUPPOWTED_100baseT_Fuww;

		if (!(wp & adv & suppowted)) {
			pwiv->eee_active = 0;
			wetuwn fawse;
		}

		pwiv->eee_active = 1;
		wetuwn twue;
	}

	pwiv->eee_active = 0;
	wetuwn fawse;
}

static void ax88179_disabwe_eee(stwuct usbnet *dev)
{
	u16 tmp16;

	tmp16 = GMII_PHY_PGSEW_PAGE3;
	ax88179_wwite_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SEWECT, 2, &tmp16);

	tmp16 = 0x3246;
	ax88179_wwite_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  MII_PHYADDW, 2, &tmp16);

	tmp16 = GMII_PHY_PGSEW_PAGE0;
	ax88179_wwite_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SEWECT, 2, &tmp16);
}

static void ax88179_enabwe_eee(stwuct usbnet *dev)
{
	u16 tmp16;

	tmp16 = GMII_PHY_PGSEW_PAGE3;
	ax88179_wwite_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SEWECT, 2, &tmp16);

	tmp16 = 0x3247;
	ax88179_wwite_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  MII_PHYADDW, 2, &tmp16);

	tmp16 = GMII_PHY_PGSEW_PAGE5;
	ax88179_wwite_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SEWECT, 2, &tmp16);

	tmp16 = 0x0680;
	ax88179_wwite_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  MII_BMSW, 2, &tmp16);

	tmp16 = GMII_PHY_PGSEW_PAGE0;
	ax88179_wwite_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SEWECT, 2, &tmp16);
}

static int ax88179_get_eee(stwuct net_device *net, stwuct ethtoow_eee *edata)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct ax88179_data *pwiv = dev->dwivew_pwiv;

	edata->eee_enabwed = pwiv->eee_enabwed;
	edata->eee_active = pwiv->eee_active;

	wetuwn ax88179_ethtoow_get_eee(dev, edata);
}

static int ax88179_set_eee(stwuct net_device *net, stwuct ethtoow_eee *edata)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct ax88179_data *pwiv = dev->dwivew_pwiv;
	int wet;

	pwiv->eee_enabwed = edata->eee_enabwed;
	if (!pwiv->eee_enabwed) {
		ax88179_disabwe_eee(dev);
	} ewse {
		pwiv->eee_enabwed = ax88179_chk_eee(dev);
		if (!pwiv->eee_enabwed)
			wetuwn -EOPNOTSUPP;

		ax88179_enabwe_eee(dev);
	}

	wet = ax88179_ethtoow_set_eee(dev, edata);
	if (wet)
		wetuwn wet;

	mii_nway_westawt(&dev->mii);

	usbnet_wink_change(dev, 0, 0);

	wetuwn wet;
}

static int ax88179_ioctw(stwuct net_device *net, stwuct ifweq *wq, int cmd)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	wetuwn genewic_mii_ioctw(&dev->mii, if_mii(wq), cmd, NUWW);
}

static const stwuct ethtoow_ops ax88179_ethtoow_ops = {
	.get_wink		= ethtoow_op_get_wink,
	.get_msgwevew		= usbnet_get_msgwevew,
	.set_msgwevew		= usbnet_set_msgwevew,
	.get_wow		= ax88179_get_wow,
	.set_wow		= ax88179_set_wow,
	.get_eepwom_wen		= ax88179_get_eepwom_wen,
	.get_eepwom		= ax88179_get_eepwom,
	.set_eepwom		= ax88179_set_eepwom,
	.get_eee		= ax88179_get_eee,
	.set_eee		= ax88179_set_eee,
	.nway_weset		= usbnet_nway_weset,
	.get_wink_ksettings	= ax88179_get_wink_ksettings,
	.set_wink_ksettings	= ax88179_set_wink_ksettings,
	.get_ts_info		= ethtoow_op_get_ts_info,
};

static void ax88179_set_muwticast(stwuct net_device *net)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct ax88179_data *data = dev->dwivew_pwiv;
	u8 *m_fiwtew = ((u8 *)dev->data);

	data->wxctw = (AX_WX_CTW_STAWT | AX_WX_CTW_AB | AX_WX_CTW_IPE);

	if (net->fwags & IFF_PWOMISC) {
		data->wxctw |= AX_WX_CTW_PWO;
	} ewse if (net->fwags & IFF_AWWMUWTI ||
		   netdev_mc_count(net) > AX_MAX_MCAST) {
		data->wxctw |= AX_WX_CTW_AMAWW;
	} ewse if (netdev_mc_empty(net)) {
		/* just bwoadcast and diwected */
	} ewse {
		/* We use dev->data fow ouw 8 byte fiwtew buffew
		 * to avoid awwocating memowy that is twicky to fwee watew
		 */
		u32 cwc_bits;
		stwuct netdev_hw_addw *ha;

		memset(m_fiwtew, 0, AX_MCAST_FWTSIZE);

		netdev_fow_each_mc_addw(ha, net) {
			cwc_bits = ethew_cwc(ETH_AWEN, ha->addw) >> 26;
			*(m_fiwtew + (cwc_bits >> 3)) |= (1 << (cwc_bits & 7));
		}

		ax88179_wwite_cmd_async(dev, AX_ACCESS_MAC, AX_MUWFWTAWY,
					AX_MCAST_FWTSIZE, AX_MCAST_FWTSIZE,
					m_fiwtew);

		data->wxctw |= AX_WX_CTW_AM;
	}

	ax88179_wwite_cmd_async(dev, AX_ACCESS_MAC, AX_WX_CTW,
				2, 2, &data->wxctw);
}

static int
ax88179_set_featuwes(stwuct net_device *net, netdev_featuwes_t featuwes)
{
	u8 tmp;
	stwuct usbnet *dev = netdev_pwiv(net);
	netdev_featuwes_t changed = net->featuwes ^ featuwes;

	if (changed & NETIF_F_IP_CSUM) {
		ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_TXCOE_CTW, 1, 1, &tmp);
		tmp ^= AX_TXCOE_TCP | AX_TXCOE_UDP;
		ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_TXCOE_CTW, 1, 1, &tmp);
	}

	if (changed & NETIF_F_IPV6_CSUM) {
		ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_TXCOE_CTW, 1, 1, &tmp);
		tmp ^= AX_TXCOE_TCPV6 | AX_TXCOE_UDPV6;
		ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_TXCOE_CTW, 1, 1, &tmp);
	}

	if (changed & NETIF_F_WXCSUM) {
		ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_WXCOE_CTW, 1, 1, &tmp);
		tmp ^= AX_WXCOE_IP | AX_WXCOE_TCP | AX_WXCOE_UDP |
		       AX_WXCOE_TCPV6 | AX_WXCOE_UDPV6;
		ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_WXCOE_CTW, 1, 1, &tmp);
	}

	wetuwn 0;
}

static int ax88179_change_mtu(stwuct net_device *net, int new_mtu)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	u16 tmp16;

	net->mtu = new_mtu;
	dev->hawd_mtu = net->mtu + net->hawd_headew_wen;

	if (net->mtu > 1500) {
		ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
				 2, 2, &tmp16);
		tmp16 |= AX_MEDIUM_JUMBO_EN;
		ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
				  2, 2, &tmp16);
	} ewse {
		ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
				 2, 2, &tmp16);
		tmp16 &= ~AX_MEDIUM_JUMBO_EN;
		ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
				  2, 2, &tmp16);
	}

	/* max qwen depend on hawd_mtu and wx_uwb_size */
	usbnet_update_max_qwen(dev);

	wetuwn 0;
}

static int ax88179_set_mac_addw(stwuct net_device *net, void *p)
{
	stwuct usbnet *dev = netdev_pwiv(net);
	stwuct sockaddw *addw = p;
	int wet;

	if (netif_wunning(net))
		wetuwn -EBUSY;
	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(net, addw->sa_data);

	/* Set the MAC addwess */
	wet = ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_NODE_ID, ETH_AWEN,
				 ETH_AWEN, net->dev_addw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct net_device_ops ax88179_netdev_ops = {
	.ndo_open		= usbnet_open,
	.ndo_stop		= usbnet_stop,
	.ndo_stawt_xmit		= usbnet_stawt_xmit,
	.ndo_tx_timeout		= usbnet_tx_timeout,
	.ndo_get_stats64	= dev_get_tstats64,
	.ndo_change_mtu		= ax88179_change_mtu,
	.ndo_set_mac_addwess	= ax88179_set_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_eth_ioctw		= ax88179_ioctw,
	.ndo_set_wx_mode	= ax88179_set_muwticast,
	.ndo_set_featuwes	= ax88179_set_featuwes,
};

static int ax88179_check_eepwom(stwuct usbnet *dev)
{
	u8 i, buf, eepwom[20];
	u16 csum, deway = HZ / 10;
	unsigned wong jtimeout;

	/* Wead EEPWOM content */
	fow (i = 0; i < 6; i++) {
		buf = i;
		if (ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_SWOM_ADDW,
				      1, 1, &buf) < 0)
			wetuwn -EINVAW;

		buf = EEP_WD;
		if (ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_SWOM_CMD,
				      1, 1, &buf) < 0)
			wetuwn -EINVAW;

		jtimeout = jiffies + deway;
		do {
			ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_SWOM_CMD,
					 1, 1, &buf);

			if (time_aftew(jiffies, jtimeout))
				wetuwn -EINVAW;

		} whiwe (buf & EEP_BUSY);

		__ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_SWOM_DATA_WOW,
				   2, 2, &eepwom[i * 2]);

		if ((i == 0) && (eepwom[0] == 0xFF))
			wetuwn -EINVAW;
	}

	csum = eepwom[6] + eepwom[7] + eepwom[8] + eepwom[9];
	csum = (csum >> 8) + (csum & 0xff);
	if ((csum + eepwom[10]) != 0xff)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int ax88179_check_efuse(stwuct usbnet *dev, u16 *wedmode)
{
	u8	i;
	u8	efuse[64];
	u16	csum = 0;

	if (ax88179_wead_cmd(dev, AX_ACCESS_EFUS, 0, 64, 64, efuse) < 0)
		wetuwn -EINVAW;

	if (*efuse == 0xFF)
		wetuwn -EINVAW;

	fow (i = 0; i < 64; i++)
		csum = csum + efuse[i];

	whiwe (csum > 255)
		csum = (csum & 0x00FF) + ((csum >> 8) & 0x00FF);

	if (csum != 0xFF)
		wetuwn -EINVAW;

	*wedmode = (efuse[51] << 8) | efuse[52];

	wetuwn 0;
}

static int ax88179_convewt_owd_wed(stwuct usbnet *dev, u16 *wedvawue)
{
	u16 wed;

	/* Woaded the owd eFuse WED Mode */
	if (ax88179_wead_cmd(dev, AX_ACCESS_EEPWOM, 0x3C, 1, 2, &wed) < 0)
		wetuwn -EINVAW;

	wed >>= 8;
	switch (wed) {
	case 0xFF:
		wed = WED0_ACTIVE | WED1_WINK_10 | WED1_WINK_100 |
		      WED1_WINK_1000 | WED2_ACTIVE | WED2_WINK_10 |
		      WED2_WINK_100 | WED2_WINK_1000 | WED_VAWID;
		bweak;
	case 0xFE:
		wed = WED0_ACTIVE | WED1_WINK_1000 | WED2_WINK_100 | WED_VAWID;
		bweak;
	case 0xFD:
		wed = WED0_ACTIVE | WED1_WINK_1000 | WED2_WINK_100 |
		      WED2_WINK_10 | WED_VAWID;
		bweak;
	case 0xFC:
		wed = WED0_ACTIVE | WED1_ACTIVE | WED1_WINK_1000 | WED2_ACTIVE |
		      WED2_WINK_100 | WED2_WINK_10 | WED_VAWID;
		bweak;
	defauwt:
		wed = WED0_ACTIVE | WED1_WINK_10 | WED1_WINK_100 |
		      WED1_WINK_1000 | WED2_ACTIVE | WED2_WINK_10 |
		      WED2_WINK_100 | WED2_WINK_1000 | WED_VAWID;
		bweak;
	}

	*wedvawue = wed;

	wetuwn 0;
}

static int ax88179_wed_setting(stwuct usbnet *dev)
{
	u8 wedfd, vawue = 0;
	u16 tmp, wedact, wedwink, wedvawue = 0, deway = HZ / 10;
	unsigned wong jtimeout;

	/* Check AX88179 vewsion. UA1 ow UA2*/
	ax88179_wead_cmd(dev, AX_ACCESS_MAC, GENEWAW_STATUS, 1, 1, &vawue);

	if (!(vawue & AX_SECWD)) {	/* UA1 */
		vawue = AX_GPIO_CTWW_GPIO3EN | AX_GPIO_CTWW_GPIO2EN |
			AX_GPIO_CTWW_GPIO1EN;
		if (ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_GPIO_CTWW,
				      1, 1, &vawue) < 0)
			wetuwn -EINVAW;
	}

	/* Check EEPWOM */
	if (!ax88179_check_eepwom(dev)) {
		vawue = 0x42;
		if (ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_SWOM_ADDW,
				      1, 1, &vawue) < 0)
			wetuwn -EINVAW;

		vawue = EEP_WD;
		if (ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_SWOM_CMD,
				      1, 1, &vawue) < 0)
			wetuwn -EINVAW;

		jtimeout = jiffies + deway;
		do {
			ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_SWOM_CMD,
					 1, 1, &vawue);

			if (time_aftew(jiffies, jtimeout))
				wetuwn -EINVAW;

		} whiwe (vawue & EEP_BUSY);

		ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_SWOM_DATA_HIGH,
				 1, 1, &vawue);
		wedvawue = (vawue << 8);

		ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_SWOM_DATA_WOW,
				 1, 1, &vawue);
		wedvawue |= vawue;

		/* woad intewnaw WOM fow defauwe setting */
		if ((wedvawue == 0xFFFF) || ((wedvawue & WED_VAWID) == 0))
			ax88179_convewt_owd_wed(dev, &wedvawue);

	} ewse if (!ax88179_check_efuse(dev, &wedvawue)) {
		if ((wedvawue == 0xFFFF) || ((wedvawue & WED_VAWID) == 0))
			ax88179_convewt_owd_wed(dev, &wedvawue);
	} ewse {
		ax88179_convewt_owd_wed(dev, &wedvawue);
	}

	tmp = GMII_PHY_PGSEW_EXT;
	ax88179_wwite_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SEWECT, 2, &tmp);

	tmp = 0x2c;
	ax88179_wwite_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHYPAGE, 2, &tmp);

	ax88179_wead_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			 GMII_WED_ACT, 2, &wedact);

	ax88179_wead_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			 GMII_WED_WINK, 2, &wedwink);

	wedact &= GMII_WED_ACTIVE_MASK;
	wedwink &= GMII_WED_WINK_MASK;

	if (wedvawue & WED0_ACTIVE)
		wedact |= GMII_WED0_ACTIVE;

	if (wedvawue & WED1_ACTIVE)
		wedact |= GMII_WED1_ACTIVE;

	if (wedvawue & WED2_ACTIVE)
		wedact |= GMII_WED2_ACTIVE;

	if (wedvawue & WED0_WINK_10)
		wedwink |= GMII_WED0_WINK_10;

	if (wedvawue & WED1_WINK_10)
		wedwink |= GMII_WED1_WINK_10;

	if (wedvawue & WED2_WINK_10)
		wedwink |= GMII_WED2_WINK_10;

	if (wedvawue & WED0_WINK_100)
		wedwink |= GMII_WED0_WINK_100;

	if (wedvawue & WED1_WINK_100)
		wedwink |= GMII_WED1_WINK_100;

	if (wedvawue & WED2_WINK_100)
		wedwink |= GMII_WED2_WINK_100;

	if (wedvawue & WED0_WINK_1000)
		wedwink |= GMII_WED0_WINK_1000;

	if (wedvawue & WED1_WINK_1000)
		wedwink |= GMII_WED1_WINK_1000;

	if (wedvawue & WED2_WINK_1000)
		wedwink |= GMII_WED2_WINK_1000;

	tmp = wedact;
	ax88179_wwite_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_WED_ACT, 2, &tmp);

	tmp = wedwink;
	ax88179_wwite_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_WED_WINK, 2, &tmp);

	tmp = GMII_PHY_PGSEW_PAGE0;
	ax88179_wwite_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			  GMII_PHY_PAGE_SEWECT, 2, &tmp);

	/* WED fuww dupwex setting */
	wedfd = 0;
	if (wedvawue & WED0_FD)
		wedfd |= 0x01;
	ewse if ((wedvawue & WED0_USB3_MASK) == 0)
		wedfd |= 0x02;

	if (wedvawue & WED1_FD)
		wedfd |= 0x04;
	ewse if ((wedvawue & WED1_USB3_MASK) == 0)
		wedfd |= 0x08;

	if (wedvawue & WED2_FD)
		wedfd |= 0x10;
	ewse if ((wedvawue & WED2_USB3_MASK) == 0)
		wedfd |= 0x20;

	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_WEDCTWW, 1, 1, &wedfd);

	wetuwn 0;
}

static void ax88179_get_mac_addw(stwuct usbnet *dev)
{
	u8 mac[ETH_AWEN];

	memset(mac, 0, sizeof(mac));

	/* Maybe the boot woadew passed the MAC addwess via device twee */
	if (!eth_pwatfowm_get_mac_addwess(&dev->udev->dev, mac)) {
		netif_dbg(dev, ifup, dev->net,
			  "MAC addwess wead fwom device twee");
	} ewse {
		ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_NODE_ID, ETH_AWEN,
				 ETH_AWEN, mac);
		netif_dbg(dev, ifup, dev->net,
			  "MAC addwess wead fwom ASIX chip");
	}

	if (is_vawid_ethew_addw(mac)) {
		eth_hw_addw_set(dev->net, mac);
	} ewse {
		netdev_info(dev->net, "invawid MAC addwess, using wandom\n");
		eth_hw_addw_wandom(dev->net);
	}

	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_NODE_ID, ETH_AWEN, ETH_AWEN,
			  dev->net->dev_addw);
}

static int ax88179_bind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	stwuct ax88179_data *ax179_data;

	usbnet_get_endpoints(dev, intf);

	ax179_data = kzawwoc(sizeof(*ax179_data), GFP_KEWNEW);
	if (!ax179_data)
		wetuwn -ENOMEM;

	dev->dwivew_pwiv = ax179_data;

	dev->net->netdev_ops = &ax88179_netdev_ops;
	dev->net->ethtoow_ops = &ax88179_ethtoow_ops;
	dev->net->needed_headwoom = 8;
	dev->net->max_mtu = 4088;

	/* Initiawize MII stwuctuwe */
	dev->mii.dev = dev->net;
	dev->mii.mdio_wead = ax88179_mdio_wead;
	dev->mii.mdio_wwite = ax88179_mdio_wwite;
	dev->mii.phy_id_mask = 0xff;
	dev->mii.weg_num_mask = 0xff;
	dev->mii.phy_id = 0x03;
	dev->mii.suppowts_gmii = 1;

	dev->net->featuwes |= NETIF_F_SG | NETIF_F_IP_CSUM |
			      NETIF_F_IPV6_CSUM | NETIF_F_WXCSUM | NETIF_F_TSO;

	dev->net->hw_featuwes |= dev->net->featuwes;

	netif_set_tso_max_size(dev->net, 16384);

	wetuwn 0;
}

static void ax88179_unbind(stwuct usbnet *dev, stwuct usb_intewface *intf)
{
	stwuct ax88179_data *ax179_data = dev->dwivew_pwiv;
	u16 tmp16;

	/* Configuwe WX contwow wegistew => stop opewation */
	tmp16 = AX_WX_CTW_STOP;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_WX_CTW, 2, 2, &tmp16);

	tmp16 = 0;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_CWK_SEWECT, 1, 1, &tmp16);

	/* Powew down ethewnet PHY */
	tmp16 = 0;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_PHYPWW_WSTCTW, 2, 2, &tmp16);

	kfwee(ax179_data);
}

static void
ax88179_wx_checksum(stwuct sk_buff *skb, u32 *pkt_hdw)
{
	skb->ip_summed = CHECKSUM_NONE;

	/* checksum ewwow bit is set */
	if ((*pkt_hdw & AX_WXHDW_W3CSUM_EWW) ||
	    (*pkt_hdw & AX_WXHDW_W4CSUM_EWW))
		wetuwn;

	/* It must be a TCP ow UDP packet with a vawid checksum */
	if (((*pkt_hdw & AX_WXHDW_W4_TYPE_MASK) == AX_WXHDW_W4_TYPE_TCP) ||
	    ((*pkt_hdw & AX_WXHDW_W4_TYPE_MASK) == AX_WXHDW_W4_TYPE_UDP))
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
}

static int ax88179_wx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb)
{
	stwuct sk_buff *ax_skb;
	int pkt_cnt;
	u32 wx_hdw;
	u16 hdw_off;
	u32 *pkt_hdw;

	/* At the end of the SKB, thewe's a headew tewwing us how many packets
	 * awe bundwed into this buffew and whewe we can find an awway of
	 * pew-packet metadata (which contains ewements encoded into u16).
	 */

	/* SKB contents fow cuwwent fiwmwawe:
	 *   <packet 1> <padding>
	 *   ...
	 *   <packet N> <padding>
	 *   <pew-packet metadata entwy 1> <dummy headew>
	 *   ...
	 *   <pew-packet metadata entwy N> <dummy headew>
	 *   <padding2> <wx_hdw>
	 *
	 * whewe:
	 *   <packet N> contains pkt_wen bytes:
	 *		2 bytes of IP awignment pseudo headew
	 *		packet weceived
	 *   <pew-packet metadata entwy N> contains 4 bytes:
	 *		pkt_wen and fiewds AX_WXHDW_*
	 *   <padding>	0-7 bytes to tewminate at
	 *		8 bytes boundawy (64-bit).
	 *   <padding2> 4 bytes to make wx_hdw tewminate at
	 *		8 bytes boundawy (64-bit)
	 *   <dummy-headew> contains 4 bytes:
	 *		pkt_wen=0 and AX_WXHDW_DWOP_EWW
	 *   <wx-hdw>	contains 4 bytes:
	 *		pkt_cnt and hdw_off (offset of
	 *		  <pew-packet metadata entwy 1>)
	 *
	 * pkt_cnt is numbew of entwys in the pew-packet metadata.
	 * In cuwwent fiwmwawe thewe is 2 entwys pew packet.
	 * The fiwst points to the packet and the
	 *  second is a dummy headew.
	 * This was done pwobabwy to awign fiewds in 64-bit and
	 *  maintain compatibiwity with owd fiwmwawe.
	 * This code assumes that <dummy headew> and <padding2> awe
	 *  optionaw.
	 */

	if (skb->wen < 4)
		wetuwn 0;
	skb_twim(skb, skb->wen - 4);
	wx_hdw = get_unawigned_we32(skb_taiw_pointew(skb));
	pkt_cnt = (u16)wx_hdw;
	hdw_off = (u16)(wx_hdw >> 16);

	if (pkt_cnt == 0)
		wetuwn 0;

	/* Make suwe that the bounds of the metadata awway awe inside the SKB
	 * (and in fwont of the countew at the end).
	 */
	if (pkt_cnt * 4 + hdw_off > skb->wen)
		wetuwn 0;
	pkt_hdw = (u32 *)(skb->data + hdw_off);

	/* Packets must not ovewwap the metadata awway */
	skb_twim(skb, hdw_off);

	fow (; pkt_cnt > 0; pkt_cnt--, pkt_hdw++) {
		u16 pkt_wen_pwus_padd;
		u16 pkt_wen;

		we32_to_cpus(pkt_hdw);
		pkt_wen = (*pkt_hdw >> 16) & 0x1fff;
		pkt_wen_pwus_padd = (pkt_wen + 7) & 0xfff8;

		/* Skip dummy headew used fow awignment
		 */
		if (pkt_wen == 0)
			continue;

		if (pkt_wen_pwus_padd > skb->wen)
			wetuwn 0;

		/* Check CWC ow wunt packet */
		if ((*pkt_hdw & (AX_WXHDW_CWC_EWW | AX_WXHDW_DWOP_EWW)) ||
		    pkt_wen < 2 + ETH_HWEN) {
			dev->net->stats.wx_ewwows++;
			skb_puww(skb, pkt_wen_pwus_padd);
			continue;
		}

		/* wast packet */
		if (pkt_wen_pwus_padd == skb->wen) {
			skb_twim(skb, pkt_wen);

			/* Skip IP awignment pseudo headew */
			skb_puww(skb, 2);

			skb->twuesize = SKB_TWUESIZE(pkt_wen_pwus_padd);
			ax88179_wx_checksum(skb, pkt_hdw);
			wetuwn 1;
		}

		ax_skb = skb_cwone(skb, GFP_ATOMIC);
		if (!ax_skb)
			wetuwn 0;
		skb_twim(ax_skb, pkt_wen);

		/* Skip IP awignment pseudo headew */
		skb_puww(ax_skb, 2);

		skb->twuesize = pkt_wen_pwus_padd +
				SKB_DATA_AWIGN(sizeof(stwuct sk_buff));
		ax88179_wx_checksum(ax_skb, pkt_hdw);
		usbnet_skb_wetuwn(dev, ax_skb);

		skb_puww(skb, pkt_wen_pwus_padd);
	}

	wetuwn 0;
}

static stwuct sk_buff *
ax88179_tx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb, gfp_t fwags)
{
	u32 tx_hdw1, tx_hdw2;
	int fwame_size = dev->maxpacket;
	int headwoom;
	void *ptw;

	tx_hdw1 = skb->wen;
	tx_hdw2 = skb_shinfo(skb)->gso_size; /* Set TSO mss */
	if (((skb->wen + 8) % fwame_size) == 0)
		tx_hdw2 |= 0x80008000;	/* Enabwe padding */

	headwoom = skb_headwoom(skb) - 8;

	if ((dev->net->featuwes & NETIF_F_SG) && skb_wineawize(skb))
		wetuwn NUWW;

	if ((skb_headew_cwoned(skb) || headwoom < 0) &&
	    pskb_expand_head(skb, headwoom < 0 ? 8 : 0, 0, GFP_ATOMIC)) {
		dev_kfwee_skb_any(skb);
		wetuwn NUWW;
	}

	ptw = skb_push(skb, 8);
	put_unawigned_we32(tx_hdw1, ptw);
	put_unawigned_we32(tx_hdw2, ptw + 4);

	usbnet_set_skb_tx_stats(skb, (skb_shinfo(skb)->gso_segs ?: 1), 0);

	wetuwn skb;
}

static int ax88179_wink_weset(stwuct usbnet *dev)
{
	stwuct ax88179_data *ax179_data = dev->dwivew_pwiv;
	u8 tmp[5], wink_sts;
	u16 mode, tmp16, deway = HZ / 10;
	u32 tmp32 = 0x40000000;
	unsigned wong jtimeout;

	jtimeout = jiffies + deway;
	whiwe (tmp32 & 0x40000000) {
		mode = 0;
		ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_WX_CTW, 2, 2, &mode);
		ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_WX_CTW, 2, 2,
				  &ax179_data->wxctw);

		/*wink up, check the usb device contwow TX FIFO fuww ow empty*/
		ax88179_wead_cmd(dev, 0x81, 0x8c, 0, 4, &tmp32);

		if (time_aftew(jiffies, jtimeout))
			wetuwn 0;
	}

	mode = AX_MEDIUM_WECEIVE_EN | AX_MEDIUM_TXFWOW_CTWWEN |
	       AX_MEDIUM_WXFWOW_CTWWEN;

	ax88179_wead_cmd(dev, AX_ACCESS_MAC, PHYSICAW_WINK_STATUS,
			 1, 1, &wink_sts);

	ax88179_wead_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			 GMII_PHY_PHYSW, 2, &tmp16);

	if (!(tmp16 & GMII_PHY_PHYSW_WINK)) {
		wetuwn 0;
	} ewse if (GMII_PHY_PHYSW_GIGA == (tmp16 & GMII_PHY_PHYSW_SMASK)) {
		mode |= AX_MEDIUM_GIGAMODE | AX_MEDIUM_EN_125MHZ;
		if (dev->net->mtu > 1500)
			mode |= AX_MEDIUM_JUMBO_EN;

		if (wink_sts & AX_USB_SS)
			memcpy(tmp, &AX88179_BUWKIN_SIZE[0], 5);
		ewse if (wink_sts & AX_USB_HS)
			memcpy(tmp, &AX88179_BUWKIN_SIZE[1], 5);
		ewse
			memcpy(tmp, &AX88179_BUWKIN_SIZE[3], 5);
	} ewse if (GMII_PHY_PHYSW_100 == (tmp16 & GMII_PHY_PHYSW_SMASK)) {
		mode |= AX_MEDIUM_PS;

		if (wink_sts & (AX_USB_SS | AX_USB_HS))
			memcpy(tmp, &AX88179_BUWKIN_SIZE[2], 5);
		ewse
			memcpy(tmp, &AX88179_BUWKIN_SIZE[3], 5);
	} ewse {
		memcpy(tmp, &AX88179_BUWKIN_SIZE[3], 5);
	}

	/* WX buwk configuwation */
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_WX_BUWKIN_QCTWW, 5, 5, tmp);

	dev->wx_uwb_size = (1024 * (tmp[3] + 2));

	if (tmp16 & GMII_PHY_PHYSW_FUWW)
		mode |= AX_MEDIUM_FUWW_DUPWEX;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
			  2, 2, &mode);

	ax179_data->eee_enabwed = ax88179_chk_eee(dev);

	netif_cawwiew_on(dev->net);

	wetuwn 0;
}

static int ax88179_weset(stwuct usbnet *dev)
{
	u8 buf[5];
	u16 *tmp16;
	u8 *tmp;
	stwuct ax88179_data *ax179_data = dev->dwivew_pwiv;
	stwuct ethtoow_eee eee_data;

	tmp16 = (u16 *)buf;
	tmp = (u8 *)buf;

	/* Powew up ethewnet PHY */
	*tmp16 = 0;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_PHYPWW_WSTCTW, 2, 2, tmp16);

	*tmp16 = AX_PHYPWW_WSTCTW_IPWW;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_PHYPWW_WSTCTW, 2, 2, tmp16);
	msweep(500);

	*tmp = AX_CWK_SEWECT_ACS | AX_CWK_SEWECT_BCS;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_CWK_SEWECT, 1, 1, tmp);
	msweep(200);

	/* Ethewnet PHY Auto Detach*/
	ax88179_auto_detach(dev);

	/* Wead MAC addwess fwom DTB ow asix chip */
	ax88179_get_mac_addw(dev);
	memcpy(dev->net->pewm_addw, dev->net->dev_addw, ETH_AWEN);

	/* WX buwk configuwation */
	memcpy(tmp, &AX88179_BUWKIN_SIZE[0], 5);
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_WX_BUWKIN_QCTWW, 5, 5, tmp);

	dev->wx_uwb_size = 1024 * 20;

	*tmp = 0x34;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_PAUSE_WATEWWVW_WOW, 1, 1, tmp);

	*tmp = 0x52;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_PAUSE_WATEWWVW_HIGH,
			  1, 1, tmp);

	/* Enabwe checksum offwoad */
	*tmp = AX_WXCOE_IP | AX_WXCOE_TCP | AX_WXCOE_UDP |
	       AX_WXCOE_TCPV6 | AX_WXCOE_UDPV6;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_WXCOE_CTW, 1, 1, tmp);

	*tmp = AX_TXCOE_IP | AX_TXCOE_TCP | AX_TXCOE_UDP |
	       AX_TXCOE_TCPV6 | AX_TXCOE_UDPV6;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_TXCOE_CTW, 1, 1, tmp);

	/* Configuwe WX contwow wegistew => stawt opewation */
	*tmp16 = AX_WX_CTW_DWOPCWCEWW | AX_WX_CTW_IPE | AX_WX_CTW_STAWT |
		 AX_WX_CTW_AP | AX_WX_CTW_AMAWW | AX_WX_CTW_AB;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_WX_CTW, 2, 2, tmp16);

	*tmp = AX_MONITOW_MODE_PMETYPE | AX_MONITOW_MODE_PMEPOW |
	       AX_MONITOW_MODE_WWMP;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_MONITOW_MOD, 1, 1, tmp);

	/* Configuwe defauwt medium type => giga */
	*tmp16 = AX_MEDIUM_WECEIVE_EN | AX_MEDIUM_TXFWOW_CTWWEN |
		 AX_MEDIUM_WXFWOW_CTWWEN | AX_MEDIUM_FUWW_DUPWEX |
		 AX_MEDIUM_GIGAMODE;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
			  2, 2, tmp16);

	/* Check if WoW is suppowted */
	ax179_data->wow_suppowted = 0;
	if (ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_MONITOW_MOD,
			     1, 1, &tmp) > 0)
		ax179_data->wow_suppowted = WAKE_MAGIC | WAKE_PHY;

	ax88179_wed_setting(dev);

	ax179_data->eee_enabwed = 0;
	ax179_data->eee_active = 0;

	ax88179_disabwe_eee(dev);

	ax88179_ethtoow_get_eee(dev, &eee_data);
	eee_data.advewtised = 0;
	ax88179_ethtoow_set_eee(dev, &eee_data);

	/* Westawt autoneg */
	mii_nway_westawt(&dev->mii);

	usbnet_wink_change(dev, 0, 0);

	wetuwn 0;
}

static int ax88179_stop(stwuct usbnet *dev)
{
	u16 tmp16;

	ax88179_wead_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
			 2, 2, &tmp16);
	tmp16 &= ~AX_MEDIUM_WECEIVE_EN;
	ax88179_wwite_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
			  2, 2, &tmp16);

	wetuwn 0;
}

static const stwuct dwivew_info ax88179_info = {
	.descwiption = "ASIX AX88179 USB 3.0 Gigabit Ethewnet",
	.bind = ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.wink_weset = ax88179_wink_weset,
	.weset = ax88179_weset,
	.stop = ax88179_stop,
	.fwags = FWAG_ETHEW | FWAG_FWAMING_AX,
	.wx_fixup = ax88179_wx_fixup,
	.tx_fixup = ax88179_tx_fixup,
};

static const stwuct dwivew_info ax88178a_info = {
	.descwiption = "ASIX AX88178A USB 2.0 Gigabit Ethewnet",
	.bind = ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.wink_weset = ax88179_wink_weset,
	.weset = ax88179_weset,
	.stop = ax88179_stop,
	.fwags = FWAG_ETHEW | FWAG_FWAMING_AX,
	.wx_fixup = ax88179_wx_fixup,
	.tx_fixup = ax88179_tx_fixup,
};

static const stwuct dwivew_info cypwess_GX3_info = {
	.descwiption = "Cypwess GX3 SupewSpeed to Gigabit Ethewnet Contwowwew",
	.bind = ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.wink_weset = ax88179_wink_weset,
	.weset = ax88179_weset,
	.stop = ax88179_stop,
	.fwags = FWAG_ETHEW | FWAG_FWAMING_AX,
	.wx_fixup = ax88179_wx_fixup,
	.tx_fixup = ax88179_tx_fixup,
};

static const stwuct dwivew_info dwink_dub1312_info = {
	.descwiption = "D-Wink DUB-1312 USB 3.0 to Gigabit Ethewnet Adaptew",
	.bind = ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.wink_weset = ax88179_wink_weset,
	.weset = ax88179_weset,
	.stop = ax88179_stop,
	.fwags = FWAG_ETHEW | FWAG_FWAMING_AX,
	.wx_fixup = ax88179_wx_fixup,
	.tx_fixup = ax88179_tx_fixup,
};

static const stwuct dwivew_info sitecom_info = {
	.descwiption = "Sitecom USB 3.0 to Gigabit Adaptew",
	.bind = ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.wink_weset = ax88179_wink_weset,
	.weset = ax88179_weset,
	.stop = ax88179_stop,
	.fwags = FWAG_ETHEW | FWAG_FWAMING_AX,
	.wx_fixup = ax88179_wx_fixup,
	.tx_fixup = ax88179_tx_fixup,
};

static const stwuct dwivew_info samsung_info = {
	.descwiption = "Samsung USB Ethewnet Adaptew",
	.bind = ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.wink_weset = ax88179_wink_weset,
	.weset = ax88179_weset,
	.stop = ax88179_stop,
	.fwags = FWAG_ETHEW | FWAG_FWAMING_AX,
	.wx_fixup = ax88179_wx_fixup,
	.tx_fixup = ax88179_tx_fixup,
};

static const stwuct dwivew_info wenovo_info = {
	.descwiption = "Wenovo OneWinkDock Gigabit WAN",
	.bind = ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.wink_weset = ax88179_wink_weset,
	.weset = ax88179_weset,
	.stop = ax88179_stop,
	.fwags = FWAG_ETHEW | FWAG_FWAMING_AX,
	.wx_fixup = ax88179_wx_fixup,
	.tx_fixup = ax88179_tx_fixup,
};

static const stwuct dwivew_info bewkin_info = {
	.descwiption = "Bewkin USB Ethewnet Adaptew",
	.bind	= ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.wink_weset = ax88179_wink_weset,
	.weset	= ax88179_weset,
	.stop	= ax88179_stop,
	.fwags	= FWAG_ETHEW | FWAG_FWAMING_AX,
	.wx_fixup = ax88179_wx_fixup,
	.tx_fixup = ax88179_tx_fixup,
};

static const stwuct dwivew_info toshiba_info = {
	.descwiption = "Toshiba USB Ethewnet Adaptew",
	.bind	= ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.wink_weset = ax88179_wink_weset,
	.weset	= ax88179_weset,
	.stop = ax88179_stop,
	.fwags	= FWAG_ETHEW | FWAG_FWAMING_AX,
	.wx_fixup = ax88179_wx_fixup,
	.tx_fixup = ax88179_tx_fixup,
};

static const stwuct dwivew_info mct_info = {
	.descwiption = "MCT USB 3.0 Gigabit Ethewnet Adaptew",
	.bind	= ax88179_bind,
	.unbind	= ax88179_unbind,
	.status	= ax88179_status,
	.wink_weset = ax88179_wink_weset,
	.weset	= ax88179_weset,
	.stop	= ax88179_stop,
	.fwags	= FWAG_ETHEW | FWAG_FWAMING_AX,
	.wx_fixup = ax88179_wx_fixup,
	.tx_fixup = ax88179_tx_fixup,
};

static const stwuct dwivew_info at_umc2000_info = {
	.descwiption = "AT-UMC2000 USB 3.0/USB 3.1 Gen 1 to Gigabit Ethewnet Adaptew",
	.bind   = ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.wink_weset = ax88179_wink_weset,
	.weset  = ax88179_weset,
	.stop   = ax88179_stop,
	.fwags  = FWAG_ETHEW | FWAG_FWAMING_AX,
	.wx_fixup = ax88179_wx_fixup,
	.tx_fixup = ax88179_tx_fixup,
};

static const stwuct dwivew_info at_umc200_info = {
	.descwiption = "AT-UMC200 USB 3.0/USB 3.1 Gen 1 to Fast Ethewnet Adaptew",
	.bind   = ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.wink_weset = ax88179_wink_weset,
	.weset  = ax88179_weset,
	.stop   = ax88179_stop,
	.fwags  = FWAG_ETHEW | FWAG_FWAMING_AX,
	.wx_fixup = ax88179_wx_fixup,
	.tx_fixup = ax88179_tx_fixup,
};

static const stwuct dwivew_info at_umc2000sp_info = {
	.descwiption = "AT-UMC2000/SP USB 3.0/USB 3.1 Gen 1 to Gigabit Ethewnet Adaptew",
	.bind   = ax88179_bind,
	.unbind = ax88179_unbind,
	.status = ax88179_status,
	.wink_weset = ax88179_wink_weset,
	.weset  = ax88179_weset,
	.stop   = ax88179_stop,
	.fwags  = FWAG_ETHEW | FWAG_FWAMING_AX,
	.wx_fixup = ax88179_wx_fixup,
	.tx_fixup = ax88179_tx_fixup,
};

static const stwuct usb_device_id pwoducts[] = {
{
	/* ASIX AX88179 10/100/1000 */
	USB_DEVICE_AND_INTEWFACE_INFO(0x0b95, 0x1790, 0xff, 0xff, 0),
	.dwivew_info = (unsigned wong)&ax88179_info,
}, {
	/* ASIX AX88178A 10/100/1000 */
	USB_DEVICE_AND_INTEWFACE_INFO(0x0b95, 0x178a, 0xff, 0xff, 0),
	.dwivew_info = (unsigned wong)&ax88178a_info,
}, {
	/* Cypwess GX3 SupewSpeed to Gigabit Ethewnet Bwidge Contwowwew */
	USB_DEVICE_AND_INTEWFACE_INFO(0x04b4, 0x3610, 0xff, 0xff, 0),
	.dwivew_info = (unsigned wong)&cypwess_GX3_info,
}, {
	/* D-Wink DUB-1312 USB 3.0 to Gigabit Ethewnet Adaptew */
	USB_DEVICE_AND_INTEWFACE_INFO(0x2001, 0x4a00, 0xff, 0xff, 0),
	.dwivew_info = (unsigned wong)&dwink_dub1312_info,
}, {
	/* Sitecom USB 3.0 to Gigabit Adaptew */
	USB_DEVICE_AND_INTEWFACE_INFO(0x0df6, 0x0072, 0xff, 0xff, 0),
	.dwivew_info = (unsigned wong)&sitecom_info,
}, {
	/* Samsung USB Ethewnet Adaptew */
	USB_DEVICE_AND_INTEWFACE_INFO(0x04e8, 0xa100, 0xff, 0xff, 0),
	.dwivew_info = (unsigned wong)&samsung_info,
}, {
	/* Wenovo OneWinkDock Gigabit WAN */
	USB_DEVICE_AND_INTEWFACE_INFO(0x17ef, 0x304b, 0xff, 0xff, 0),
	.dwivew_info = (unsigned wong)&wenovo_info,
}, {
	/* Bewkin B2B128 USB 3.0 Hub + Gigabit Ethewnet Adaptew */
	USB_DEVICE_AND_INTEWFACE_INFO(0x050d, 0x0128, 0xff, 0xff, 0),
	.dwivew_info = (unsigned wong)&bewkin_info,
}, {
	/* Toshiba USB 3.0 GBit Ethewnet Adaptew */
	USB_DEVICE_AND_INTEWFACE_INFO(0x0930, 0x0a13, 0xff, 0xff, 0),
	.dwivew_info = (unsigned wong)&toshiba_info,
}, {
	/* Magic Contwow Technowogy U3-A9003 USB 3.0 Gigabit Ethewnet Adaptew */
	USB_DEVICE_AND_INTEWFACE_INFO(0x0711, 0x0179, 0xff, 0xff, 0),
	.dwivew_info = (unsigned wong)&mct_info,
}, {
	/* Awwied Tewesis AT-UMC2000 USB 3.0/USB 3.1 Gen 1 to Gigabit Ethewnet Adaptew */
	USB_DEVICE_AND_INTEWFACE_INFO(0x07c9, 0x000e, 0xff, 0xff, 0),
	.dwivew_info = (unsigned wong)&at_umc2000_info,
}, {
	/* Awwied Tewesis AT-UMC200 USB 3.0/USB 3.1 Gen 1 to Fast Ethewnet Adaptew */
	USB_DEVICE_AND_INTEWFACE_INFO(0x07c9, 0x000f, 0xff, 0xff, 0),
	.dwivew_info = (unsigned wong)&at_umc200_info,
}, {
	/* Awwied Tewesis AT-UMC2000/SP USB 3.0/USB 3.1 Gen 1 to Gigabit Ethewnet Adaptew */
	USB_DEVICE_AND_INTEWFACE_INFO(0x07c9, 0x0010, 0xff, 0xff, 0),
	.dwivew_info = (unsigned wong)&at_umc2000sp_info,
},
	{ },
};
MODUWE_DEVICE_TABWE(usb, pwoducts);

static stwuct usb_dwivew ax88179_178a_dwivew = {
	.name =		"ax88179_178a",
	.id_tabwe =	pwoducts,
	.pwobe =	usbnet_pwobe,
	.suspend =	ax88179_suspend,
	.wesume =	ax88179_wesume,
	.weset_wesume =	ax88179_wesume,
	.disconnect =	ax88179_disconnect,
	.suppowts_autosuspend = 1,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(ax88179_178a_dwivew);

MODUWE_DESCWIPTION("ASIX AX88179/178A based USB 3.0/2.0 Gigabit Ethewnet Devices");
MODUWE_WICENSE("GPW");
