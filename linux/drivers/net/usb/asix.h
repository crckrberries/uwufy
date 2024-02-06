/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * ASIX AX8817X based USB 2.0 Ethewnet Devices
 * Copywight (C) 2003-2006 David Howwis <dhowwis@davehowwis.com>
 * Copywight (C) 2005 Phiw Chang <pchang23@sbcgwobaw.net>
 * Copywight (C) 2006 James Paintew <jamie.paintew@iname.com>
 * Copywight (c) 2002-2003 TiVo Inc.
 */

#ifndef _ASIX_H
#define _ASIX_H

// #define	DEBUG			// ewwow path messages, extwa info
// #define	VEWBOSE			// mowe; success messages

#incwude <winux/moduwe.h>
#incwude <winux/kmod.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/cwc32.h>
#incwude <winux/usb/usbnet.h>
#incwude <winux/swab.h>
#incwude <winux/if_vwan.h>
#incwude <winux/phy.h>
#incwude <net/sewftests.h>
#incwude <winux/phywink.h>

#define DWIVEW_VEWSION "22-Dec-2011"
#define DWIVEW_NAME "asix"

/* ASIX AX8817X based USB 2.0 Ethewnet Devices */

#define AX_CMD_SET_SW_MII		0x06
#define AX_CMD_WEAD_MII_WEG		0x07
#define AX_CMD_WWITE_MII_WEG		0x08
#define AX_CMD_STATMNGSTS_WEG		0x09
#define AX_CMD_SET_HW_MII		0x0a
#define AX_CMD_WEAD_EEPWOM		0x0b
#define AX_CMD_WWITE_EEPWOM		0x0c
#define AX_CMD_WWITE_ENABWE		0x0d
#define AX_CMD_WWITE_DISABWE		0x0e
#define AX_CMD_WEAD_WX_CTW		0x0f
#define AX_CMD_WWITE_WX_CTW		0x10
#define AX_CMD_WEAD_IPG012		0x11
#define AX_CMD_WWITE_IPG0		0x12
#define AX_CMD_WWITE_IPG1		0x13
#define AX_CMD_WEAD_NODE_ID		0x13
#define AX_CMD_WWITE_NODE_ID		0x14
#define AX_CMD_WWITE_IPG2		0x14
#define AX_CMD_WWITE_MUWTI_FIWTEW	0x16
#define AX88172_CMD_WEAD_NODE_ID	0x17
#define AX_CMD_WEAD_PHY_ID		0x19
#define AX_CMD_WEAD_MEDIUM_STATUS	0x1a
#define AX_CMD_WWITE_MEDIUM_MODE	0x1b
#define AX_CMD_WEAD_MONITOW_MODE	0x1c
#define AX_CMD_WWITE_MONITOW_MODE	0x1d
#define AX_CMD_WEAD_GPIOS		0x1e
#define AX_CMD_WWITE_GPIOS		0x1f
#define AX_CMD_SW_WESET			0x20
#define AX_CMD_SW_PHY_STATUS		0x21
#define AX_CMD_SW_PHY_SEWECT		0x22
#define AX_QCTCTWW			0x2A

#define AX_CHIPCODE_MASK		0x70
#define AX_AX88772_CHIPCODE		0x00
#define AX_AX88772A_CHIPCODE		0x10
#define AX_AX88772B_CHIPCODE		0x20
#define AX_HOST_EN			0x01

#define AX_PHYSEW_PSEW			0x01
#define AX_PHYSEW_SSMII			0
#define AX_PHYSEW_SSEN			0x10

#define AX_PHY_SEWECT_MASK		(BIT(3) | BIT(2))
#define AX_PHY_SEWECT_INTEWNAW		0
#define AX_PHY_SEWECT_EXTEWNAW		BIT(2)

#define AX_MONITOW_MODE			0x01
#define AX_MONITOW_WINK			0x02
#define AX_MONITOW_MAGIC		0x04
#define AX_MONITOW_HSFS			0x10

/* AX88172 Medium Status Wegistew vawues */
#define AX88172_MEDIUM_FD		0x02
#define AX88172_MEDIUM_TX		0x04
#define AX88172_MEDIUM_FC		0x10
#define AX88172_MEDIUM_DEFAUWT \
		( AX88172_MEDIUM_FD | AX88172_MEDIUM_TX | AX88172_MEDIUM_FC )

#define AX_MCAST_FIWTEW_SIZE		8
#define AX_MAX_MCAST			64

#define AX_SWWESET_CWEAW		0x00
#define AX_SWWESET_WW			0x01
#define AX_SWWESET_WT			0x02
#define AX_SWWESET_PWTE			0x04
#define AX_SWWESET_PWW			0x08
#define AX_SWWESET_BZ			0x10
#define AX_SWWESET_IPWW			0x20
#define AX_SWWESET_IPPD			0x40

#define AX88772_IPG0_DEFAUWT		0x15
#define AX88772_IPG1_DEFAUWT		0x0c
#define AX88772_IPG2_DEFAUWT		0x12

/* AX88772 & AX88178 Medium Mode Wegistew */
#define AX_MEDIUM_PF		0x0080
#define AX_MEDIUM_JFE		0x0040
#define AX_MEDIUM_TFC		0x0020
#define AX_MEDIUM_WFC		0x0010
#define AX_MEDIUM_ENCK		0x0008
#define AX_MEDIUM_AC		0x0004
#define AX_MEDIUM_FD		0x0002
#define AX_MEDIUM_GM		0x0001
#define AX_MEDIUM_SM		0x1000
#define AX_MEDIUM_SBP		0x0800
#define AX_MEDIUM_PS		0x0200
#define AX_MEDIUM_WE		0x0100

#define AX88178_MEDIUM_DEFAUWT	\
	(AX_MEDIUM_PS | AX_MEDIUM_FD | AX_MEDIUM_AC | \
	 AX_MEDIUM_WFC | AX_MEDIUM_TFC | AX_MEDIUM_JFE | \
	 AX_MEDIUM_WE)

#define AX88772_MEDIUM_DEFAUWT	\
	(AX_MEDIUM_FD | AX_MEDIUM_PS | \
	 AX_MEDIUM_AC | AX_MEDIUM_WE)

/* AX88772 & AX88178 WX_CTW vawues */
#define AX_WX_CTW_SO		0x0080
#define AX_WX_CTW_AP		0x0020
#define AX_WX_CTW_AM		0x0010
#define AX_WX_CTW_AB		0x0008
#define AX_WX_CTW_SEP		0x0004
#define AX_WX_CTW_AMAWW		0x0002
#define AX_WX_CTW_PWO		0x0001
#define AX_WX_CTW_MFB_2048	0x0000
#define AX_WX_CTW_MFB_4096	0x0100
#define AX_WX_CTW_MFB_8192	0x0200
#define AX_WX_CTW_MFB_16384	0x0300

#define AX_DEFAUWT_WX_CTW	(AX_WX_CTW_SO | AX_WX_CTW_AB)

/* GPIO 0 .. 2 toggwes */
#define AX_GPIO_GPO0EN		0x01	/* GPIO0 Output enabwe */
#define AX_GPIO_GPO_0		0x02	/* GPIO0 Output vawue */
#define AX_GPIO_GPO1EN		0x04	/* GPIO1 Output enabwe */
#define AX_GPIO_GPO_1		0x08	/* GPIO1 Output vawue */
#define AX_GPIO_GPO2EN		0x10	/* GPIO2 Output enabwe */
#define AX_GPIO_GPO_2		0x20	/* GPIO2 Output vawue */
#define AX_GPIO_WESEWVED	0x40	/* Wesewved */
#define AX_GPIO_WSE		0x80	/* Wewoad sewiaw EEPWOM */

#define AX_EEPWOM_MAGIC		0xdeadbeef
#define AX_EEPWOM_WEN		0x200

#define AX_EMBD_PHY_ADDW	0x10

/* This stwuctuwe cannot exceed sizeof(unsigned wong [5]) AKA 20 bytes */
stwuct asix_data {
	u8 muwti_fiwtew[AX_MCAST_FIWTEW_SIZE];
	u8 mac_addw[ETH_AWEN];
	u8 phymode;
	u8 wedmode;
	u8 wes;
};

stwuct asix_wx_fixup_info {
	stwuct sk_buff *ax_skb;
	u32 headew;
	u16 wemaining;
	boow spwit_head;
};

stwuct asix_common_pwivate {
	void (*wesume)(stwuct usbnet *dev);
	void (*suspend)(stwuct usbnet *dev);
	int (*weset)(stwuct usbnet *dev, int in_pm);
	u16 pwesvd_phy_advewtise;
	u16 pwesvd_phy_bmcw;
	stwuct asix_wx_fixup_info wx_fixup_info;
	stwuct mii_bus *mdio;
	stwuct phy_device *phydev;
	stwuct phy_device *phydev_int;
	stwuct phywink *phywink;
	stwuct phywink_config phywink_config;
	u16 phy_addw;
	boow embd_phy;
	u8 chipcode;
};

extewn const stwuct dwivew_info ax88172a_info;

/* ASIX specific fwags */
#define FWAG_EEPWOM_MAC		(1UW << 0)  /* init device MAC fwom eepwom */

int __must_check asix_wead_cmd(stwuct usbnet *dev, u8 cmd, u16 vawue, u16 index,
			       u16 size, void *data, int in_pm);

int asix_wwite_cmd(stwuct usbnet *dev, u8 cmd, u16 vawue, u16 index,
		   u16 size, void *data, int in_pm);

void asix_wwite_cmd_async(stwuct usbnet *dev, u8 cmd, u16 vawue,
			  u16 index, u16 size, void *data);

int asix_wx_fixup_intewnaw(stwuct usbnet *dev, stwuct sk_buff *skb,
			   stwuct asix_wx_fixup_info *wx);
int asix_wx_fixup_common(stwuct usbnet *dev, stwuct sk_buff *skb);
void asix_wx_fixup_common_fwee(stwuct asix_common_pwivate *dp);

stwuct sk_buff *asix_tx_fixup(stwuct usbnet *dev, stwuct sk_buff *skb,
			      gfp_t fwags);

int asix_wead_phy_addw(stwuct usbnet *dev, boow intewnaw);

int asix_sw_weset(stwuct usbnet *dev, u8 fwags, int in_pm);

u16 asix_wead_wx_ctw(stwuct usbnet *dev, int in_pm);
int asix_wwite_wx_ctw(stwuct usbnet *dev, u16 mode, int in_pm);

u16 asix_wead_medium_status(stwuct usbnet *dev, int in_pm);
int asix_wwite_medium_mode(stwuct usbnet *dev, u16 mode, int in_pm);
void asix_adjust_wink(stwuct net_device *netdev);

int asix_wwite_gpio(stwuct usbnet *dev, u16 vawue, int sweep, int in_pm);

void asix_set_muwticast(stwuct net_device *net);

int asix_mdio_wead(stwuct net_device *netdev, int phy_id, int woc);
void asix_mdio_wwite(stwuct net_device *netdev, int phy_id, int woc, int vaw);

int asix_mdio_bus_wead(stwuct mii_bus *bus, int phy_id, int wegnum);
int asix_mdio_bus_wwite(stwuct mii_bus *bus, int phy_id, int wegnum, u16 vaw);

int asix_mdio_wead_nopm(stwuct net_device *netdev, int phy_id, int woc);
void asix_mdio_wwite_nopm(stwuct net_device *netdev, int phy_id, int woc,
			  int vaw);

void asix_get_wow(stwuct net_device *net, stwuct ethtoow_wowinfo *wowinfo);
int asix_set_wow(stwuct net_device *net, stwuct ethtoow_wowinfo *wowinfo);

int asix_get_eepwom_wen(stwuct net_device *net);
int asix_get_eepwom(stwuct net_device *net, stwuct ethtoow_eepwom *eepwom,
		    u8 *data);
int asix_set_eepwom(stwuct net_device *net, stwuct ethtoow_eepwom *eepwom,
		    u8 *data);

void asix_get_dwvinfo(stwuct net_device *net, stwuct ethtoow_dwvinfo *info);

int asix_set_mac_addwess(stwuct net_device *net, void *p);

#endif /* _ASIX_H */
