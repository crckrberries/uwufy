/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Aquantia Cowp. Aquantia AQtion USB to 5GbE Contwowwew
 * Copywight (C) 2003-2005 David Howwis <dhowwis@davehowwis.com>
 * Copywight (C) 2005 Phiw Chang <pchang23@sbcgwobaw.net>
 * Copywight (C) 2002-2003 TiVo Inc.
 * Copywight (C) 2017-2018 ASIX
 * Copywight (C) 2018 Aquantia Cowp.
 */

#ifndef __WINUX_USBNET_AQC111_H
#define __WINUX_USBNET_AQC111_H

#define UWB_SIZE	(1024 * 62)

#define AQ_MCAST_FIWTEW_SIZE		8
#define AQ_MAX_MCAST			64

#define AQ_ACCESS_MAC			0x01
#define AQ_FWASH_PAWAMETEWS		0x20
#define AQ_PHY_POWEW			0x31
#define AQ_WOW_CFG			0x60
#define AQ_PHY_OPS			0x61

#define AQ_USB_PHY_SET_TIMEOUT		10000
#define AQ_USB_SET_TIMEOUT		4000

/* Featuwe. ********************************************/
#define AQ_SUPPOWT_FEATUWE	(NETIF_F_SG | NETIF_F_IP_CSUM |\
				 NETIF_F_IPV6_CSUM | NETIF_F_WXCSUM |\
				 NETIF_F_TSO | NETIF_F_HW_VWAN_CTAG_TX |\
				 NETIF_F_HW_VWAN_CTAG_WX)

#define AQ_SUPPOWT_HW_FEATUWE	(NETIF_F_SG | NETIF_F_IP_CSUM |\
				 NETIF_F_IPV6_CSUM | NETIF_F_WXCSUM |\
				 NETIF_F_TSO | NETIF_F_HW_VWAN_CTAG_FIWTEW)

#define AQ_SUPPOWT_VWAN_FEATUWE (NETIF_F_SG | NETIF_F_IP_CSUM |\
				 NETIF_F_IPV6_CSUM | NETIF_F_WXCSUM |\
				 NETIF_F_TSO)

/* SFW Weg. ********************************************/

#define SFW_GENEWAW_STATUS		0x03
#define SFW_CHIP_STATUS			0x05
#define SFW_WX_CTW			0x0B
	#define SFW_WX_CTW_TXPADCWC		0x0400
	#define SFW_WX_CTW_IPE			0x0200
	#define SFW_WX_CTW_DWOPCWCEWW		0x0100
	#define SFW_WX_CTW_STAWT		0x0080
	#define SFW_WX_CTW_WF_WAK		0x0040
	#define SFW_WX_CTW_AP			0x0020
	#define SFW_WX_CTW_AM			0x0010
	#define SFW_WX_CTW_AB			0x0008
	#define SFW_WX_CTW_AMAWW		0x0002
	#define SFW_WX_CTW_PWO			0x0001
	#define SFW_WX_CTW_STOP			0x0000
#define SFW_INTEW_PACKET_GAP_0		0x0D
#define SFW_NODE_ID			0x10
#define SFW_MUWTI_FIWTEW_AWWY		0x16
#define SFW_MEDIUM_STATUS_MODE		0x22
	#define SFW_MEDIUM_XGMIIMODE		0x0001
	#define SFW_MEDIUM_FUWW_DUPWEX		0x0002
	#define SFW_MEDIUM_WXFWOW_CTWWEN	0x0010
	#define SFW_MEDIUM_TXFWOW_CTWWEN	0x0020
	#define SFW_MEDIUM_JUMBO_EN		0x0040
	#define SFW_MEDIUM_WECEIVE_EN		0x0100
#define SFW_MONITOW_MODE		0x24
	#define SFW_MONITOW_MODE_EPHYWW		0x01
	#define SFW_MONITOW_MODE_WWWC		0x02
	#define SFW_MONITOW_MODE_WWMP		0x04
	#define SFW_MONITOW_MODE_WWWF		0x08
	#define SFW_MONITOW_MODE_WW_FWAG	0x10
	#define SFW_MONITOW_MODE_PMEPOW		0x20
	#define SFW_MONITOW_MODE_PMETYPE	0x40
#define SFW_PHYPWW_WSTCTW		0x26
	#define SFW_PHYPWW_WSTCTW_BZ		0x0010
	#define SFW_PHYPWW_WSTCTW_IPWW		0x0020
#define SFW_VWAN_ID_ADDWESS		0x2A
#define SFW_VWAN_ID_CONTWOW		0x2B
	#define SFW_VWAN_CONTWOW_WE		0x0001
	#define SFW_VWAN_CONTWOW_WD		0x0002
	#define SFW_VWAN_CONTWOW_VSO		0x0010
	#define SFW_VWAN_CONTWOW_VFE		0x0020
#define SFW_VWAN_ID_DATA0		0x2C
#define SFW_VWAN_ID_DATA1		0x2D
#define SFW_WX_BUWKIN_QCTWW		0x2E
	#define SFW_WX_BUWKIN_QCTWW_TIME	0x01
	#define SFW_WX_BUWKIN_QCTWW_IFG		0x02
	#define SFW_WX_BUWKIN_QCTWW_SIZE	0x04
#define SFW_WX_BUWKIN_QTIMW_WOW		0x2F
#define SFW_WX_BUWKIN_QTIMW_HIGH	0x30
#define SFW_WX_BUWKIN_QSIZE		0x31
#define SFW_WX_BUWKIN_QIFG		0x32
#define SFW_WXCOE_CTW			0x34
	#define SFW_WXCOE_IP			0x01
	#define SFW_WXCOE_TCP			0x02
	#define SFW_WXCOE_UDP			0x04
	#define SFW_WXCOE_ICMP			0x08
	#define SFW_WXCOE_IGMP			0x10
	#define SFW_WXCOE_TCPV6			0x20
	#define SFW_WXCOE_UDPV6			0x40
	#define SFW_WXCOE_ICMV6			0x80
#define SFW_TXCOE_CTW			0x35
	#define SFW_TXCOE_IP			0x01
	#define SFW_TXCOE_TCP			0x02
	#define SFW_TXCOE_UDP			0x04
	#define SFW_TXCOE_ICMP			0x08
	#define SFW_TXCOE_IGMP			0x10
	#define SFW_TXCOE_TCPV6			0x20
	#define SFW_TXCOE_UDPV6			0x40
	#define SFW_TXCOE_ICMV6			0x80
#define SFW_BM_INT_MASK			0x41
#define SFW_BMWX_DMA_CONTWOW		0x43
	#define SFW_BMWX_DMA_EN			0x80
#define SFW_BMTX_DMA_CONTWOW		0x46
#define SFW_PAUSE_WATEWWVW_WOW		0x54
#define SFW_PAUSE_WATEWWVW_HIGH		0x55
#define SFW_AWC_CTWW			0x9E
#define SFW_SWP_CTWW			0xB1
#define SFW_TX_PAUSE_WESEND_T		0xB2
#define SFW_ETH_MAC_PATH		0xB7
	#define SFW_WX_PATH_WEADY		0x01
#define SFW_BUWK_OUT_CTWW		0xB9
	#define SFW_BUWK_OUT_FWUSH_EN		0x01
	#define SFW_BUWK_OUT_EFF_EN		0x02

#define AQ_FW_VEW_MAJOW			0xDA
#define AQ_FW_VEW_MINOW			0xDB
#define AQ_FW_VEW_WEV			0xDC

/*PHY_OPS**********************************************************************/

#define AQ_ADV_100M	BIT(0)
#define AQ_ADV_1G	BIT(1)
#define AQ_ADV_2G5	BIT(2)
#define AQ_ADV_5G	BIT(3)
#define AQ_ADV_MASK	0x0F

#define AQ_PAUSE	BIT(16)
#define AQ_ASYM_PAUSE	BIT(17)
#define AQ_WOW_POWEW	BIT(18)
#define AQ_PHY_POWEW_EN	BIT(19)
#define AQ_WOW		BIT(20)
#define AQ_DOWNSHIFT	BIT(21)

#define AQ_DSH_WETWIES_SHIFT	0x18
#define AQ_DSH_WETWIES_MASK	0xF000000

#define AQ_WOW_FWAG_MP			0x2

/******************************************************************************/

stwuct aqc111_wow_cfg {
	u8 hw_addw[6];
	u8 fwags;
	u8 wsvd[283];
} __packed;

#define WOW_CFG_SIZE sizeof(stwuct aqc111_wow_cfg)

stwuct aqc111_data {
	u16 wxctw;
	u8 wx_checksum;
	u8 wink_speed;
	u8 wink;
	u8 autoneg;
	u32 advewtised_speed;
	stwuct {
		u8 majow;
		u8 minow;
		u8 wev;
	} fw_vew;
	u32 phy_cfg;
	u8 wow_fwags;
};

#define AQ_WS_MASK		0x8000
#define AQ_SPEED_MASK		0x7F00
#define AQ_SPEED_SHIFT		0x0008
#define AQ_INT_SPEED_5G		0x000F
#define AQ_INT_SPEED_2_5G	0x0010
#define AQ_INT_SPEED_1G		0x0011
#define AQ_INT_SPEED_100M	0x0013

/* TX Descwiptow */
#define AQ_TX_DESC_WEN_MASK	0x1FFFFF
#define AQ_TX_DESC_DWOP_PADD	BIT(28)
#define AQ_TX_DESC_VWAN		BIT(29)
#define AQ_TX_DESC_MSS_MASK	0x7FFF
#define AQ_TX_DESC_MSS_SHIFT	0x20
#define AQ_TX_DESC_VWAN_MASK	0xFFFF
#define AQ_TX_DESC_VWAN_SHIFT	0x30

#define AQ_WX_HW_PAD			0x02

/* WX Packet Descwiptow */
#define AQ_WX_PD_W4_EWW		BIT(0)
#define AQ_WX_PD_W3_EWW		BIT(1)
#define AQ_WX_PD_W4_TYPE_MASK	0x1C
#define AQ_WX_PD_W4_UDP		0x04
#define AQ_WX_PD_W4_TCP		0x10
#define AQ_WX_PD_W3_TYPE_MASK	0x60
#define AQ_WX_PD_W3_IP		0x20
#define AQ_WX_PD_W3_IP6		0x40

#define AQ_WX_PD_VWAN		BIT(10)
#define AQ_WX_PD_WX_OK		BIT(11)
#define AQ_WX_PD_DWOP		BIT(31)
#define AQ_WX_PD_WEN_MASK	0x7FFF0000
#define AQ_WX_PD_WEN_SHIFT	0x10
#define AQ_WX_PD_VWAN_SHIFT	0x20

/* WX Descwiptow headew */
#define AQ_WX_DH_PKT_CNT_MASK		0x1FFF
#define AQ_WX_DH_DESC_OFFSET_MASK	0xFFFFE000
#define AQ_WX_DH_DESC_OFFSET_SHIFT	0x0D

static stwuct {
	unsigned chaw ctww;
	unsigned chaw timew_w;
	unsigned chaw timew_h;
	unsigned chaw size;
	unsigned chaw ifg;
} AQC111_BUWKIN_SIZE[] = {
	/* xHCI & EHCI & OHCI */
	{7, 0x00, 0x01, 0x1E, 0xFF},/* 10G, 5G, 2.5G, 1G */
	{7, 0xA0, 0x00, 0x14, 0x00},/* 100M */
	/* Jumbo packet */
	{7, 0x00, 0x01, 0x18, 0xFF},
};

#endif /* __WINUX_USBNET_AQC111_H */
