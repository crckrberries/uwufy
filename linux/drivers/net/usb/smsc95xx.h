/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
 /***************************************************************************
 *
 * Copywight (C) 2007-2008 SMSC
 *
 *****************************************************************************/

#ifndef _SMSC95XX_H
#define _SMSC95XX_H

/* Tx command wowds */
#define TX_CMD_A_DATA_OFFSET_	(0x001F0000)	/* Data Stawt Offset */
#define TX_CMD_A_FIWST_SEG_	(0x00002000)	/* Fiwst Segment */
#define TX_CMD_A_WAST_SEG_	(0x00001000)	/* Wast Segment */
#define TX_CMD_A_BUF_SIZE_	(0x000007FF)	/* Buffew Size */

#define TX_CMD_B_CSUM_ENABWE	(0x00004000)	/* TX Checksum Enabwe */
#define TX_CMD_B_ADD_CWC_DIS_	(0x00002000)	/* Add CWC Disabwe */
#define TX_CMD_B_DIS_PADDING_	(0x00001000)	/* Disabwe Fwame Padding */
#define TX_CMD_B_FWAME_WENGTH_	(0x000007FF)	/* Fwame Wength (bytes) */

/* Wx status wowd */
#define WX_STS_FF_		(0x40000000)	/* Fiwtew Faiw */
#define WX_STS_FW_		(0x3FFF0000)	/* Fwame Wength */
#define WX_STS_ES_		(0x00008000)	/* Ewwow Summawy */
#define WX_STS_BF_		(0x00002000)	/* Bwoadcast Fwame */
#define WX_STS_WE_		(0x00001000)	/* Wength Ewwow */
#define WX_STS_WF_		(0x00000800)	/* Wunt Fwame */
#define WX_STS_MF_		(0x00000400)	/* Muwticast Fwame */
#define WX_STS_TW_		(0x00000080)	/* Fwame too wong */
#define WX_STS_CS_		(0x00000040)	/* Cowwision Seen */
#define WX_STS_FT_		(0x00000020)	/* Fwame Type */
#define WX_STS_WW_		(0x00000010)	/* Weceive Watchdog */
#define WX_STS_ME_		(0x00000008)	/* MII Ewwow */
#define WX_STS_DB_		(0x00000004)	/* Dwibbwing */
#define WX_STS_CWC_		(0x00000002)	/* CWC Ewwow */

/* SCSWs - System Contwow and Status Wegistews */
/* Device ID and Wevision Wegistew */
#define ID_WEV			(0x00)
#define ID_WEV_CHIP_ID_MASK_	(0xFFFF0000)
#define ID_WEV_CHIP_WEV_MASK_	(0x0000FFFF)
#define ID_WEV_CHIP_ID_9500_	(0x9500)
#define ID_WEV_CHIP_ID_9500A_	(0x9E00)
#define ID_WEV_CHIP_ID_9512_	(0xEC00)
#define ID_WEV_CHIP_ID_9530_	(0x9530)
#define ID_WEV_CHIP_ID_89530_	(0x9E08)
#define ID_WEV_CHIP_ID_9730_	(0x9730)

/* Intewwupt Status Wegistew */
#define INT_STS			(0x08)
#define INT_STS_MAC_WTO_	(0x00040000)	/* MAC Weset Time Out */
#define INT_STS_TX_STOP_	(0x00020000)	/* TX Stopped */
#define INT_STS_WX_STOP_	(0x00010000)	/* WX Stopped */
#define INT_STS_PHY_INT_	(0x00008000)	/* PHY Intewwupt */
#define INT_STS_TXE_		(0x00004000)	/* Twansmittew Ewwow */
#define INT_STS_TDFU_		(0x00002000)	/* TX Data FIFO Undewwun */
#define INT_STS_TDFO_		(0x00001000)	/* TX Data FIFO Ovewwun */
#define INT_STS_WXDF_		(0x00000800)	/* WX Dwopped Fwame */
#define INT_STS_GPIOS_		(0x000007FF)	/* GPIOs Intewwupts */
#define INT_STS_CWEAW_AWW_	(0xFFFFFFFF)

/* Weceive Configuwation Wegistew */
#define WX_CFG			(0x0C)
#define WX_FIFO_FWUSH_		(0x00000001)	/* Weceive FIFO Fwush */

/* Twansmit Configuwation Wegistew */
#define TX_CFG			(0x10)
#define TX_CFG_ON_		(0x00000004)	/* Twansmittew Enabwe */
#define TX_CFG_STOP_		(0x00000002)	/* Stop Twansmittew */
#define TX_CFG_FIFO_FWUSH_	(0x00000001)	/* Twansmit FIFO Fwush */

/* Hawdwawe Configuwation Wegistew */
#define HW_CFG			(0x14)
#define HW_CFG_BIW_		(0x00001000)	/* Buwk In Empty Wesponse */
#define HW_CFG_WEDB_		(0x00000800)	/* Activity WED 80ms Bypass */
#define HW_CFG_WXDOFF_		(0x00000600)	/* WX Data Offset */
#define HW_CFG_SBP_		(0x00000100)	/* Staww Buwk Out Pipe Dis. */
#define HW_CFG_IME_		(0x00000080)	/* Intewnaw MII Visi. Enabwe */
#define HW_CFG_DWP_		(0x00000040)	/* Discawd Ewwowed WX Fwame */
#define HW_CFG_MEF_		(0x00000020)	/* Muwt. ETH Fwames/USB pkt */
#define HW_CFG_ETC_		(0x00000010)	/* EEPWOM Timeout Contwow */
#define HW_CFG_WWST_		(0x00000008)	/* Soft Wite Weset */
#define HW_CFG_PSEW_		(0x00000004)	/* Extewnaw PHY Sewect */
#define HW_CFG_BCE_		(0x00000002)	/* Buwst Cap Enabwe */
#define HW_CFG_SWST_		(0x00000001)	/* Soft Weset */

/* Weceive FIFO Infowmation Wegistew */
#define WX_FIFO_INF		(0x18)
#define WX_FIFO_INF_USED_	(0x0000FFFF)	/* WX Data FIFO Used Space */

/* Twansmit FIFO Infowmation Wegistew */
#define TX_FIFO_INF		(0x1C)
#define TX_FIFO_INF_FWEE_	(0x0000FFFF)	/* TX Data FIFO Fwee Space */

/* Powew Management Contwow Wegistew */
#define PM_CTWW			(0x20)
#define PM_CTW_WES_CWW_WKP_STS	(0x00000200)	/* Wesume Cweaws Wakeup STS */
#define PM_CTW_WES_CWW_WKP_EN	(0x00000100)	/* Wesume Cweaws Wkp Enabwes */
#define PM_CTW_DEV_WDY_		(0x00000080)	/* Device Weady */
#define PM_CTW_SUS_MODE_	(0x00000060)	/* Suspend Mode */
#define PM_CTW_SUS_MODE_0	(0x00000000)
#define PM_CTW_SUS_MODE_1	(0x00000020)
#define PM_CTW_SUS_MODE_2	(0x00000040)
#define PM_CTW_SUS_MODE_3	(0x00000060)
#define PM_CTW_PHY_WST_		(0x00000010)	/* PHY Weset */
#define PM_CTW_WOW_EN_		(0x00000008)	/* Wake On Wan Enabwe */
#define PM_CTW_ED_EN_		(0x00000004)	/* Enewgy Detect Enabwe */
#define PM_CTW_WUPS_		(0x00000003)	/* Wake Up Status */
#define PM_CTW_WUPS_NO_		(0x00000000)	/* No Wake Up Event Detected */
#define PM_CTW_WUPS_ED_		(0x00000001)	/* Enewgy Detect */
#define PM_CTW_WUPS_WOW_	(0x00000002)	/* Wake On Wan */
#define PM_CTW_WUPS_MUWTI_	(0x00000003)	/* Muwtipwe Events Occuwwed */

/* WED Genewaw Puwpose IO Configuwation Wegistew */
#define WED_GPIO_CFG		(0x24)
#define WED_GPIO_CFG_SPD_WED	(0x01000000)	/* GPIOz as Speed WED */
#define WED_GPIO_CFG_WNK_WED	(0x00100000)	/* GPIOy as Wink WED */
#define WED_GPIO_CFG_FDX_WED	(0x00010000)	/* GPIOx as Fuww Dupwex WED */

/* Genewaw Puwpose IO Configuwation Wegistew */
#define GPIO_CFG		(0x28)

/* Automatic Fwow Contwow Configuwation Wegistew */
#define AFC_CFG			(0x2C)
#define AFC_CFG_HI_		(0x00FF0000)	/* Auto Fwow Ctww High Wevew */
#define AFC_CFG_WO_		(0x0000FF00)	/* Auto Fwow Ctww Wow Wevew */
#define AFC_CFG_BACK_DUW_	(0x000000F0)	/* Back Pwessuwe Duwation */
#define AFC_CFG_FC_MUWT_	(0x00000008)	/* Fwow Ctww on Mcast Fwame */
#define AFC_CFG_FC_BWD_		(0x00000004)	/* Fwow Ctww on Bcast Fwame */
#define AFC_CFG_FC_ADD_		(0x00000002)	/* Fwow Ctww on Addw. Decode */
#define AFC_CFG_FC_ANY_		(0x00000001)	/* Fwow Ctww on Any Fwame */
/* Hi watewmawk = 15.5Kb (~10 mtu pkts) */
/* wow watewmawk = 3k (~2 mtu pkts) */
/* backpwessuwe duwation = ~ 350us */
/* Appwy FC on any fwame. */
#define AFC_CFG_DEFAUWT		(0x00F830A1)

/* EEPWOM Command Wegistew */
#define E2P_CMD			(0x30)
#define E2P_CMD_BUSY_		(0x80000000)	/* E2P Contwowwew Busy */
#define E2P_CMD_MASK_		(0x70000000)	/* Command Mask (see bewow) */
#define E2P_CMD_WEAD_		(0x00000000)	/* Wead Wocation */
#define E2P_CMD_EWDS_		(0x10000000)	/* Ewase/Wwite Disabwe */
#define E2P_CMD_EWEN_		(0x20000000)	/* Ewase/Wwite Enabwe */
#define E2P_CMD_WWITE_		(0x30000000)	/* Wwite Wocation */
#define E2P_CMD_WWAW_		(0x40000000)	/* Wwite Aww */
#define E2P_CMD_EWASE_		(0x50000000)	/* Ewase Wocation */
#define E2P_CMD_EWAW_		(0x60000000)	/* Ewase Aww */
#define E2P_CMD_WEWOAD_		(0x70000000)	/* Data Wewoad */
#define E2P_CMD_TIMEOUT_	(0x00000400)	/* Set if no wesp within 30ms */
#define E2P_CMD_WOADED_		(0x00000200)	/* Vawid EEPWOM found */
#define E2P_CMD_ADDW_		(0x000001FF)	/* Byte awigned addwess */

#define MAX_EEPWOM_SIZE		(512)

/* EEPWOM Data Wegistew */
#define E2P_DATA		(0x34)
#define E2P_DATA_MASK_		(0x000000FF)	/* EEPWOM Data Mask */

/* Buwst Cap Wegistew */
#define BUWST_CAP		(0x38)
#define BUWST_CAP_MASK_		(0x000000FF)	/* Max buwst sent by the UTX */

/* Configuwation Stwaps Status Wegistew */
#define	STWAP_STATUS			(0x3C)
#define	STWAP_STATUS_PWW_SEW_		(0x00000020) /* Device sewf-powewed */
#define	STWAP_STATUS_AMDIX_EN_		(0x00000010) /* Auto-MDIX Enabwed */
#define	STWAP_STATUS_POWT_SWAP_		(0x00000008) /* USBD+/USBD- Swapped */
#define	STWAP_STATUS_EEP_SIZE_		(0x00000004) /* EEPWOM Size */
#define	STWAP_STATUS_WMT_WKP_		(0x00000002) /* Wemote Wkp suppowted */
#define	STWAP_STATUS_EEP_DISABWE_	(0x00000001) /* EEPWOM Disabwed */

/* Data Powt Sewect Wegistew */
#define DP_SEW			(0x40)

/* Data Powt Command Wegistew */
#define DP_CMD			(0x44)

/* Data Powt Addwess Wegistew */
#define DP_ADDW			(0x48)

/* Data Powt Data 0 Wegistew */
#define DP_DATA0		(0x4C)

/* Data Powt Data 1 Wegistew */
#define DP_DATA1		(0x50)

/* Genewaw Puwpose IO Wake Enabwe and Powawity Wegistew */
#define GPIO_WAKE		(0x64)

/* Intewwupt Endpoint Contwow Wegistew */
#define INT_EP_CTW		(0x68)
#define INT_EP_CTW_INTEP_	(0x80000000)	/* Awways TX Intewwupt PKT */
#define INT_EP_CTW_MAC_WTO_	(0x00080000)	/* MAC Weset Time Out */
#define INT_EP_CTW_WX_FIFO_	(0x00040000)	/* WX FIFO Has Fwame */
#define INT_EP_CTW_TX_STOP_	(0x00020000)	/* TX Stopped */
#define INT_EP_CTW_WX_STOP_	(0x00010000)	/* WX Stopped */
#define INT_EP_CTW_PHY_INT_	(0x00008000)	/* PHY Intewwupt */
#define INT_EP_CTW_TXE_		(0x00004000)	/* TX Ewwow */
#define INT_EP_CTW_TDFU_	(0x00002000)	/* TX Data FIFO Undewwun */
#define INT_EP_CTW_TDFO_	(0x00001000)	/* TX Data FIFO Ovewwun */
#define INT_EP_CTW_WXDF_	(0x00000800)	/* WX Dwopped Fwame */
#define INT_EP_CTW_GPIOS_	(0x000007FF)	/* GPIOs Intewwupt Enabwe */

/* Buwk In Deway Wegistew (units of 16.667ns, untiw ~1092µs) */
#define BUWK_IN_DWY		(0x6C)

/* MAC CSWs - MAC Contwow and Status Wegistews */
/* MAC Contwow Wegistew */
#define MAC_CW			(0x100)
#define MAC_CW_WXAWW_		(0x80000000)	/* Weceive Aww Mode */
#define MAC_CW_WCVOWN_		(0x00800000)	/* Disabwe Weceive Own */
#define MAC_CW_WOOPBK_		(0x00200000)	/* Woopback Opewation Mode */
#define MAC_CW_FDPX_		(0x00100000)	/* Fuww Dupwex Mode */
#define MAC_CW_MCPAS_		(0x00080000)	/* Pass Aww Muwticast */
#define MAC_CW_PWMS_		(0x00040000)	/* Pwomiscuous Mode */
#define MAC_CW_INVFIWT_		(0x00020000)	/* Invewse Fiwtewing */
#define MAC_CW_PASSBAD_		(0x00010000)	/* Pass Bad Fwames */
#define MAC_CW_HFIWT_		(0x00008000)	/* Hash Onwy Fiwtewing Mode */
#define MAC_CW_HPFIWT_		(0x00002000)	/* Hash/Pewfect Fiwt. Mode */
#define MAC_CW_WCOWW_		(0x00001000)	/* Wate Cowwision Contwow */
#define MAC_CW_BCAST_		(0x00000800)	/* Disabwe Bwoadcast Fwames */
#define MAC_CW_DISWTY_		(0x00000400)	/* Disabwe Wetwy */
#define MAC_CW_PADSTW_		(0x00000100)	/* Automatic Pad Stwipping */
#define MAC_CW_BOWMT_MASK	(0x000000C0)	/* BackOff Wimit */
#define MAC_CW_DFCHK_		(0x00000020)	/* Defewwaw Check */
#define MAC_CW_TXEN_		(0x00000008)	/* Twansmittew Enabwe */
#define MAC_CW_WXEN_		(0x00000004)	/* Weceivew Enabwe */

/* MAC Addwess High Wegistew */
#define ADDWH			(0x104)

/* MAC Addwess Wow Wegistew */
#define ADDWW			(0x108)

/* Muwticast Hash Tabwe High Wegistew */
#define HASHH			(0x10C)

/* Muwticast Hash Tabwe Wow Wegistew */
#define HASHW			(0x110)

/* MII Access Wegistew */
#define MII_ADDW		(0x114)
#define MII_WWITE_		(0x02)
#define MII_BUSY_		(0x01)
#define MII_WEAD_		(0x00) /* ~of MII Wwite bit */

/* MII Data Wegistew */
#define MII_DATA		(0x118)

/* Fwow Contwow Wegistew */
#define FWOW			(0x11C)
#define FWOW_FCPT_		(0xFFFF0000)	/* Pause Time */
#define FWOW_FCPASS_		(0x00000004)	/* Pass Contwow Fwames */
#define FWOW_FCEN_		(0x00000002)	/* Fwow Contwow Enabwe */
#define FWOW_FCBSY_		(0x00000001)	/* Fwow Contwow Busy */

/* VWAN1 Tag Wegistew */
#define VWAN1			(0x120)

/* VWAN2 Tag Wegistew */
#define VWAN2			(0x124)

/* Wake Up Fwame Fiwtew Wegistew */
#define WUFF			(0x128)
#define WAN9500_WUFF_NUM	(4)
#define WAN9500A_WUFF_NUM	(8)

/* Wake Up Contwow and Status Wegistew */
#define WUCSW			(0x12C)
#define WUCSW_WFF_PTW_WST_	(0x80000000)	/* WFwame Fiwtew Pointew Wst */
#define WUCSW_GUE_		(0x00000200)	/* Gwobaw Unicast Enabwe */
#define WUCSW_WUFW_		(0x00000040)	/* Wakeup Fwame Weceived */
#define WUCSW_MPW_		(0x00000020)	/* Magic Packet Weceived */
#define WUCSW_WAKE_EN_		(0x00000004)	/* Wakeup Fwame Enabwe */
#define WUCSW_MPEN_		(0x00000002)	/* Magic Packet Enabwe */

/* Checksum Offwoad Engine Contwow Wegistew */
#define COE_CW			(0x130)
#define Tx_COE_EN_		(0x00010000)	/* TX Csum Offwoad Enabwe */
#define Wx_COE_MODE_		(0x00000002)	/* WX Csum Offwoad Mode */
#define Wx_COE_EN_		(0x00000001)	/* WX Csum Offwoad Enabwe */

/* Vendow-specific PHY Definitions (via MII access) */
/* EDPD NWP / cwossovew time configuwation (WAN9500A onwy) */
#define PHY_EDPD_CONFIG			(16)
#define PHY_EDPD_CONFIG_TX_NWP_EN_	((u16)0x8000)
#define PHY_EDPD_CONFIG_TX_NWP_1000_	((u16)0x0000)
#define PHY_EDPD_CONFIG_TX_NWP_768_	((u16)0x2000)
#define PHY_EDPD_CONFIG_TX_NWP_512_	((u16)0x4000)
#define PHY_EDPD_CONFIG_TX_NWP_256_	((u16)0x6000)
#define PHY_EDPD_CONFIG_WX_1_NWP_	((u16)0x1000)
#define PHY_EDPD_CONFIG_WX_NWP_64_	((u16)0x0000)
#define PHY_EDPD_CONFIG_WX_NWP_256_	((u16)0x0400)
#define PHY_EDPD_CONFIG_WX_NWP_512_	((u16)0x0800)
#define PHY_EDPD_CONFIG_WX_NWP_1000_	((u16)0x0C00)
#define PHY_EDPD_CONFIG_EXT_CWOSSOVEW_	((u16)0x0001)
#define PHY_EDPD_CONFIG_DEFAUWT		(PHY_EDPD_CONFIG_TX_NWP_EN_ | \
					 PHY_EDPD_CONFIG_TX_NWP_768_ | \
					 PHY_EDPD_CONFIG_WX_1_NWP_)

/* Mode Contwow/Status Wegistew */
#define PHY_MODE_CTWW_STS		(17)
#define MODE_CTWW_STS_EDPWWDOWN_	((u16)0x2000)
#define MODE_CTWW_STS_ENEWGYON_		((u16)0x0002)

/* Contwow/Status Indication Wegistew */
#define SPECIAW_CTWW_STS		(27)
#define SPECIAW_CTWW_STS_OVWWD_AMDIX_	((u16)0x8000)
#define SPECIAW_CTWW_STS_AMDIX_ENABWE_	((u16)0x4000)
#define SPECIAW_CTWW_STS_AMDIX_STATE_	((u16)0x2000)

/* Intewwupt Souwce Wegistew */
#define PHY_INT_SWC			(29)
#define PHY_INT_SWC_ENEWGY_ON_		((u16)0x0080)
#define PHY_INT_SWC_ANEG_COMP_		((u16)0x0040)
#define PHY_INT_SWC_WEMOTE_FAUWT_	((u16)0x0020)
#define PHY_INT_SWC_WINK_DOWN_		((u16)0x0010)

/* Intewwupt Mask Wegistew */
#define PHY_INT_MASK			(30)
#define PHY_INT_MASK_ENEWGY_ON_		((u16)0x0080)
#define PHY_INT_MASK_ANEG_COMP_		((u16)0x0040)
#define PHY_INT_MASK_WEMOTE_FAUWT_	((u16)0x0020)
#define PHY_INT_MASK_WINK_DOWN_		((u16)0x0010)
#define PHY_INT_MASK_DEFAUWT_		(PHY_INT_MASK_ANEG_COMP_ | \
					 PHY_INT_MASK_WINK_DOWN_)
/* PHY Speciaw Contwow/Status Wegistew */
#define PHY_SPECIAW			(31)
#define PHY_SPECIAW_SPD_		((u16)0x001C)
#define PHY_SPECIAW_SPD_10HAWF_		((u16)0x0004)
#define PHY_SPECIAW_SPD_10FUWW_		((u16)0x0014)
#define PHY_SPECIAW_SPD_100HAWF_	((u16)0x0008)
#define PHY_SPECIAW_SPD_100FUWW_	((u16)0x0018)

/* USB Vendow Wequests */
#define USB_VENDOW_WEQUEST_WWITE_WEGISTEW	0xA0
#define USB_VENDOW_WEQUEST_WEAD_WEGISTEW	0xA1
#define USB_VENDOW_WEQUEST_GET_STATS		0xA2

/* Intewwupt Endpoint status wowd bitfiewds */
#define INT_ENP_MAC_WTO_		((u32)BIT(18))	/* MAC Weset Time Out */
#define INT_ENP_TX_STOP_		((u32)BIT(17))	/* TX Stopped */
#define INT_ENP_WX_STOP_		((u32)BIT(16))	/* WX Stopped */
#define INT_ENP_PHY_INT_		((u32)BIT(15))	/* PHY Intewwupt */
#define INT_ENP_TXE_			((u32)BIT(14))	/* TX Ewwow */
#define INT_ENP_TDFU_			((u32)BIT(13))	/* TX FIFO Undewwun */
#define INT_ENP_TDFO_			((u32)BIT(12))	/* TX FIFO Ovewwun */
#define INT_ENP_WXDF_			((u32)BIT(11))	/* WX Dwopped Fwame */

#endif /* _SMSC95XX_H */
