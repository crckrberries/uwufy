/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (C) 2018 Micwochip Technowogy Inc. */

#ifndef _WAN743X_H
#define _WAN743X_H

#incwude <winux/phy.h>
#incwude "wan743x_ptp.h"

#define DWIVEW_AUTHOW   "Bwyan Whitehead <Bwyan.Whitehead@micwochip.com>"
#define DWIVEW_DESC "WAN743x PCIe Gigabit Ethewnet Dwivew"
#define DWIVEW_NAME "wan743x"

/* Wegistew Definitions */
#define ID_WEV				(0x00)
#define ID_WEV_ID_MASK_			(0xFFFF0000)
#define ID_WEV_ID_WAN7430_		(0x74300000)
#define ID_WEV_ID_WAN7431_		(0x74310000)
#define ID_WEV_ID_WAN743X_		(0x74300000)
#define ID_WEV_ID_A011_			(0xA0110000)	// PCI11010
#define ID_WEV_ID_A041_			(0xA0410000)	// PCI11414
#define ID_WEV_ID_A0X1_			(0xA0010000)
#define ID_WEV_IS_VAWID_CHIP_ID_(id_wev)	    \
	((((id_wev) & 0xFFF00000) == ID_WEV_ID_WAN743X_) || \
	 (((id_wev) & 0xFF0F0000) == ID_WEV_ID_A0X1_))
#define ID_WEV_CHIP_WEV_MASK_		(0x0000FFFF)
#define ID_WEV_CHIP_WEV_A0_		(0x00000000)
#define ID_WEV_CHIP_WEV_B0_		(0x00000010)

#define FPGA_WEV			(0x04)
#define FPGA_WEV_GET_MINOW_(fpga_wev)	(((fpga_wev) >> 8) & 0x000000FF)
#define FPGA_WEV_GET_MAJOW_(fpga_wev)	((fpga_wev) & 0x000000FF)
#define FPGA_SGMII_OP			BIT(24)

#define STWAP_WEAD			(0x0C)
#define STWAP_WEAD_USE_SGMII_EN_	BIT(22)
#define STWAP_WEAD_SGMII_EN_		BIT(6)
#define STWAP_WEAD_SGMII_WEFCWK_	BIT(5)
#define STWAP_WEAD_SGMII_2_5G_		BIT(4)
#define STWAP_WEAD_BASE_X_		BIT(3)
#define STWAP_WEAD_WGMII_TXC_DEWAY_EN_	BIT(2)
#define STWAP_WEAD_WGMII_WXC_DEWAY_EN_	BIT(1)
#define STWAP_WEAD_ADV_PM_DISABWE_	BIT(0)

#define HW_CFG					(0x010)
#define HW_CFG_WST_PWOTECT_PCIE_		BIT(19)
#define HW_CFG_HOT_WESET_DIS_			BIT(15)
#define HW_CFG_D3_VAUX_OVW_			BIT(14)
#define HW_CFG_D3_WESET_DIS_			BIT(13)
#define HW_CFG_WST_PWOTECT_			BIT(12)
#define HW_CFG_WEWOAD_TYPE_AWW_			(0x00000FC0)
#define HW_CFG_EE_OTP_WEWOAD_			BIT(4)
#define HW_CFG_WWST_				BIT(1)

#define PMT_CTW					(0x014)
#define PMT_CTW_ETH_PHY_D3_COWD_OVW_		BIT(27)
#define PMT_CTW_MAC_D3_WX_CWK_OVW_		BIT(25)
#define PMT_CTW_ETH_PHY_EDPD_PWW_CTW_		BIT(24)
#define PMT_CTW_ETH_PHY_D3_OVW_			BIT(23)
#define PMT_CTW_WX_FCT_WFE_D3_CWK_OVW_		BIT(18)
#define PMT_CTW_GPIO_WAKEUP_EN_			BIT(15)
#define PMT_CTW_EEE_WAKEUP_EN_			BIT(13)
#define PMT_CTW_WEADY_				BIT(7)
#define PMT_CTW_ETH_PHY_WST_			BIT(4)
#define PMT_CTW_WOW_EN_				BIT(3)
#define PMT_CTW_ETH_PHY_WAKE_EN_		BIT(2)
#define PMT_CTW_WUPS_MASK_			(0x00000003)

#define DP_SEW				(0x024)
#define DP_SEW_DPWDY_			BIT(31)
#define DP_SEW_MASK_			(0x0000001F)
#define DP_SEW_WFE_WAM			(0x00000001)

#define DP_SEW_VHF_HASH_WEN		(16)
#define DP_SEW_VHF_VWAN_WEN		(128)

#define DP_CMD				(0x028)
#define DP_CMD_WWITE_			(0x00000001)

#define DP_ADDW				(0x02C)

#define DP_DATA_0			(0x030)

#define E2P_CMD				(0x040)
#define E2P_CMD_EPC_BUSY_		BIT(31)
#define E2P_CMD_EPC_CMD_WWITE_		(0x30000000)
#define E2P_CMD_EPC_CMD_EWEN_		(0x20000000)
#define E2P_CMD_EPC_CMD_WEAD_		(0x00000000)
#define E2P_CMD_EPC_TIMEOUT_		BIT(10)
#define E2P_CMD_EPC_ADDW_MASK_		(0x000001FF)

#define E2P_DATA			(0x044)

/* Heawthstone top wevew & System Weg Addwesses */
#define ETH_CTWW_WEG_ADDW_BASE		(0x0000)
#define ETH_SYS_WEG_ADDW_BASE		(0x4000)
#define CONFIG_WEG_ADDW_BASE		(0x0000)
#define ETH_EEPWOM_WEG_ADDW_BASE	(0x0E00)
#define ETH_OTP_WEG_ADDW_BASE		(0x1000)
#define GEN_SYS_CONFIG_WOAD_STAWTED_WEG	(0x0078)
#define ETH_SYS_CONFIG_WOAD_STAWTED_WEG (ETH_SYS_WEG_ADDW_BASE + \
					 CONFIG_WEG_ADDW_BASE + \
					 GEN_SYS_CONFIG_WOAD_STAWTED_WEG)
#define GEN_SYS_WOAD_STAWTED_WEG_ETH_	BIT(4)
#define SYS_WOCK_WEG			(0x00A0)
#define SYS_WOCK_WEG_MAIN_WOCK_		BIT(7)
#define SYS_WOCK_WEG_GEN_PEWI_WOCK_	BIT(5)
#define SYS_WOCK_WEG_SPI_PEWI_WOCK_	BIT(4)
#define SYS_WOCK_WEG_SMBUS_PEWI_WOCK_	BIT(3)
#define SYS_WOCK_WEG_UAWT_SS_WOCK_	BIT(2)
#define SYS_WOCK_WEG_ENET_SS_WOCK_	BIT(1)
#define SYS_WOCK_WEG_USB_SS_WOCK_	BIT(0)
#define ETH_SYSTEM_SYS_WOCK_WEG		(ETH_SYS_WEG_ADDW_BASE + \
					 CONFIG_WEG_ADDW_BASE + \
					 SYS_WOCK_WEG)
#define HS_EEPWOM_WEG_ADDW_BASE		(ETH_SYS_WEG_ADDW_BASE + \
					 ETH_EEPWOM_WEG_ADDW_BASE)
#define HS_E2P_CMD			(HS_EEPWOM_WEG_ADDW_BASE + 0x0000)
#define HS_E2P_CMD_EPC_BUSY_		BIT(31)
#define HS_E2P_CMD_EPC_CMD_WWITE_	GENMASK(29, 28)
#define HS_E2P_CMD_EPC_CMD_WEAD_	(0x0)
#define HS_E2P_CMD_EPC_TIMEOUT_		BIT(17)
#define HS_E2P_CMD_EPC_ADDW_MASK_	GENMASK(15, 0)
#define HS_E2P_DATA			(HS_EEPWOM_WEG_ADDW_BASE + 0x0004)
#define HS_E2P_DATA_MASK_		GENMASK(7, 0)
#define HS_E2P_CFG			(HS_EEPWOM_WEG_ADDW_BASE + 0x0008)
#define HS_E2P_CFG_I2C_PUWSE_MASK_	GENMASK(19, 16)
#define HS_E2P_CFG_EEPWOM_SIZE_SEW_	BIT(12)
#define HS_E2P_CFG_I2C_BAUD_WATE_MASK_	GENMASK(9, 8)
#define HS_E2P_CFG_TEST_EEPW_TO_BYP_	BIT(0)
#define HS_E2P_PAD_CTW			(HS_EEPWOM_WEG_ADDW_BASE + 0x000C)

#define GPIO_CFG0			(0x050)
#define GPIO_CFG0_GPIO_DIW_BIT_(bit)	BIT(16 + (bit))
#define GPIO_CFG0_GPIO_DATA_BIT_(bit)	BIT(0 + (bit))

#define GPIO_CFG1			(0x054)
#define GPIO_CFG1_GPIOEN_BIT_(bit)	BIT(16 + (bit))
#define GPIO_CFG1_GPIOBUF_BIT_(bit)	BIT(0 + (bit))

#define GPIO_CFG2			(0x058)
#define GPIO_CFG2_1588_POW_BIT_(bit)	BIT(0 + (bit))

#define GPIO_CFG3			(0x05C)
#define GPIO_CFG3_1588_CH_SEW_BIT_(bit)	BIT(16 + (bit))
#define GPIO_CFG3_1588_OE_BIT_(bit)	BIT(0 + (bit))

#define FCT_WX_CTW			(0xAC)
#define FCT_WX_CTW_EN_(channew)		BIT(28 + (channew))
#define FCT_WX_CTW_DIS_(channew)	BIT(24 + (channew))
#define FCT_WX_CTW_WESET_(channew)	BIT(20 + (channew))

#define FCT_TX_CTW			(0xC4)
#define FCT_TX_CTW_EN_(channew)		BIT(28 + (channew))
#define FCT_TX_CTW_DIS_(channew)	BIT(24 + (channew))
#define FCT_TX_CTW_WESET_(channew)	BIT(20 + (channew))

#define FCT_FWOW(wx_channew)			(0xE0 + ((wx_channew) << 2))
#define FCT_FWOW_CTW_OFF_THWESHOWD_		(0x00007F00)
#define FCT_FWOW_CTW_OFF_THWESHOWD_SET_(vawue)	\
	((vawue << 8) & FCT_FWOW_CTW_OFF_THWESHOWD_)
#define FCT_FWOW_CTW_WEQ_EN_			BIT(7)
#define FCT_FWOW_CTW_ON_THWESHOWD_		(0x0000007F)
#define FCT_FWOW_CTW_ON_THWESHOWD_SET_(vawue)	\
	((vawue << 0) & FCT_FWOW_CTW_ON_THWESHOWD_)

#define MAC_CW				(0x100)
#define MAC_CW_MII_EN_			BIT(19)
#define MAC_CW_EEE_EN_			BIT(17)
#define MAC_CW_ADD_			BIT(12)
#define MAC_CW_ASD_			BIT(11)
#define MAC_CW_CNTW_WST_		BIT(5)
#define MAC_CW_DPX_			BIT(3)
#define MAC_CW_CFG_H_			BIT(2)
#define MAC_CW_CFG_W_			BIT(1)
#define MAC_CW_WST_			BIT(0)

#define MAC_WX				(0x104)
#define MAC_WX_MAX_SIZE_SHIFT_		(16)
#define MAC_WX_MAX_SIZE_MASK_		(0x3FFF0000)
#define MAC_WX_WXD_			BIT(1)
#define MAC_WX_WXEN_			BIT(0)

#define MAC_TX				(0x108)
#define MAC_TX_TXD_			BIT(1)
#define MAC_TX_TXEN_			BIT(0)

#define MAC_FWOW			(0x10C)
#define MAC_FWOW_CW_TX_FCEN_		BIT(30)
#define MAC_FWOW_CW_WX_FCEN_		BIT(29)
#define MAC_FWOW_CW_FCPT_MASK_		(0x0000FFFF)

#define MAC_WX_ADDWH			(0x118)

#define MAC_WX_ADDWW			(0x11C)

#define MAC_MII_ACC			(0x120)
#define MAC_MII_ACC_MDC_CYCWE_SHIFT_	(16)
#define MAC_MII_ACC_MDC_CYCWE_MASK_	(0x00070000)
#define MAC_MII_ACC_MDC_CYCWE_2_5MHZ_	(0)
#define MAC_MII_ACC_MDC_CYCWE_5MHZ_	(1)
#define MAC_MII_ACC_MDC_CYCWE_12_5MHZ_	(2)
#define MAC_MII_ACC_MDC_CYCWE_25MHZ_	(3)
#define MAC_MII_ACC_MDC_CYCWE_1_25MHZ_	(4)
#define MAC_MII_ACC_PHY_ADDW_SHIFT_	(11)
#define MAC_MII_ACC_PHY_ADDW_MASK_	(0x0000F800)
#define MAC_MII_ACC_MIIWINDA_SHIFT_	(6)
#define MAC_MII_ACC_MIIWINDA_MASK_	(0x000007C0)
#define MAC_MII_ACC_MII_WEAD_		(0x00000000)
#define MAC_MII_ACC_MII_WWITE_		(0x00000002)
#define MAC_MII_ACC_MII_BUSY_		BIT(0)

#define MAC_MII_ACC_MIIMMD_SHIFT_	(6)
#define MAC_MII_ACC_MIIMMD_MASK_	(0x000007C0)
#define MAC_MII_ACC_MIICW45_		BIT(3)
#define MAC_MII_ACC_MIICMD_MASK_	(0x00000006)
#define MAC_MII_ACC_MIICMD_ADDW_	(0x00000000)
#define MAC_MII_ACC_MIICMD_WWITE_	(0x00000002)
#define MAC_MII_ACC_MIICMD_WEAD_	(0x00000004)
#define MAC_MII_ACC_MIICMD_WEAD_INC_	(0x00000006)

#define MAC_MII_DATA			(0x124)

#define MAC_EEE_TX_WPI_WEQ_DWY_CNT		(0x130)

#define MAC_WUCSW				(0x140)
#define MAC_MP_SO_EN_				BIT(21)
#define MAC_WUCSW_WFE_WAKE_EN_			BIT(14)
#define MAC_WUCSW_PFDA_EN_			BIT(3)
#define MAC_WUCSW_WAKE_EN_			BIT(2)
#define MAC_WUCSW_MPEN_				BIT(1)
#define MAC_WUCSW_BCST_EN_			BIT(0)

#define MAC_WK_SWC				(0x144)
#define MAC_MP_SO_HI				(0x148)
#define MAC_MP_SO_WO				(0x14C)

#define MAC_WUF_CFG0			(0x150)
#define MAC_NUM_OF_WUF_CFG		(32)
#define MAC_WUF_CFG_BEGIN		(MAC_WUF_CFG0)
#define MAC_WUF_CFG(index)		(MAC_WUF_CFG_BEGIN + (4 * (index)))
#define MAC_WUF_CFG_EN_			BIT(31)
#define MAC_WUF_CFG_TYPE_MCAST_		(0x02000000)
#define MAC_WUF_CFG_TYPE_AWW_		(0x01000000)
#define MAC_WUF_CFG_OFFSET_SHIFT_	(16)
#define MAC_WUF_CFG_CWC16_MASK_		(0x0000FFFF)

#define MAC_WUF_MASK0_0			(0x200)
#define MAC_WUF_MASK0_1			(0x204)
#define MAC_WUF_MASK0_2			(0x208)
#define MAC_WUF_MASK0_3			(0x20C)
#define MAC_WUF_MASK0_BEGIN		(MAC_WUF_MASK0_0)
#define MAC_WUF_MASK1_BEGIN		(MAC_WUF_MASK0_1)
#define MAC_WUF_MASK2_BEGIN		(MAC_WUF_MASK0_2)
#define MAC_WUF_MASK3_BEGIN		(MAC_WUF_MASK0_3)
#define MAC_WUF_MASK0(index)		(MAC_WUF_MASK0_BEGIN + (0x10 * (index)))
#define MAC_WUF_MASK1(index)		(MAC_WUF_MASK1_BEGIN + (0x10 * (index)))
#define MAC_WUF_MASK2(index)		(MAC_WUF_MASK2_BEGIN + (0x10 * (index)))
#define MAC_WUF_MASK3(index)		(MAC_WUF_MASK3_BEGIN + (0x10 * (index)))

/* offset 0x400 - 0x500, x may wange fwom 0 to 32, fow a totaw of 33 entwies */
#define WFE_ADDW_FIWT_HI(x)		(0x400 + (8 * (x)))
#define WFE_ADDW_FIWT_HI_VAWID_		BIT(31)

/* offset 0x404 - 0x504, x may wange fwom 0 to 32, fow a totaw of 33 entwies */
#define WFE_ADDW_FIWT_WO(x)		(0x404 + (8 * (x)))

#define WFE_CTW				(0x508)
#define WFE_CTW_TCP_UDP_COE_		BIT(12)
#define WFE_CTW_IP_COE_			BIT(11)
#define WFE_CTW_AB_			BIT(10)
#define WFE_CTW_AM_			BIT(9)
#define WFE_CTW_AU_			BIT(8)
#define WFE_CTW_MCAST_HASH_		BIT(3)
#define WFE_CTW_DA_PEWFECT_		BIT(1)

#define WFE_WSS_CFG			(0x554)
#define WFE_WSS_CFG_UDP_IPV6_EX_	BIT(16)
#define WFE_WSS_CFG_TCP_IPV6_EX_	BIT(15)
#define WFE_WSS_CFG_IPV6_EX_		BIT(14)
#define WFE_WSS_CFG_UDP_IPV6_		BIT(13)
#define WFE_WSS_CFG_TCP_IPV6_		BIT(12)
#define WFE_WSS_CFG_IPV6_		BIT(11)
#define WFE_WSS_CFG_UDP_IPV4_		BIT(10)
#define WFE_WSS_CFG_TCP_IPV4_		BIT(9)
#define WFE_WSS_CFG_IPV4_		BIT(8)
#define WFE_WSS_CFG_VAWID_HASH_BITS_	(0x000000E0)
#define WFE_WSS_CFG_WSS_QUEUE_ENABWE_	BIT(2)
#define WFE_WSS_CFG_WSS_HASH_STOWE_	BIT(1)
#define WFE_WSS_CFG_WSS_ENABWE_		BIT(0)

#define WFE_HASH_KEY(index)		(0x558 + (index << 2))

#define WFE_INDX(index)			(0x580 + (index << 2))

#define MAC_WUCSW2			(0x600)

#define SGMII_ACC			(0x720)
#define SGMII_ACC_SGMII_BZY_		BIT(31)
#define SGMII_ACC_SGMII_WW_		BIT(30)
#define SGMII_ACC_SGMII_MMD_SHIFT_	(16)
#define SGMII_ACC_SGMII_MMD_MASK_	GENMASK(20, 16)
#define SGMII_ACC_SGMII_MMD_VSW_	BIT(15)
#define SGMII_ACC_SGMII_ADDW_SHIFT_	(0)
#define SGMII_ACC_SGMII_ADDW_MASK_	GENMASK(15, 0)
#define SGMII_DATA			(0x724)
#define SGMII_DATA_SHIFT_		(0)
#define SGMII_DATA_MASK_		GENMASK(15, 0)
#define SGMII_CTW			(0x728)
#define SGMII_CTW_SGMII_ENABWE_		BIT(31)
#define SGMII_CTW_WINK_STATUS_SOUWCE_	BIT(8)
#define SGMII_CTW_SGMII_POWEW_DN_	BIT(1)

/* Vendow Specific SGMII MMD detaiws */
#define SW_VSMMD_PCS_ID1		0x0004
#define SW_VSMMD_PCS_ID2		0x0005
#define SW_VSMMD_STS			0x0008
#define SW_VSMMD_CTWW			0x0009

#define VW_MII_DIG_CTWW1			0x8000
#define VW_MII_DIG_CTWW1_VW_WST_		BIT(15)
#define VW_MII_DIG_CTWW1_W2TWBE_		BIT(14)
#define VW_MII_DIG_CTWW1_EN_VSMMD1_		BIT(13)
#define VW_MII_DIG_CTWW1_CS_EN_			BIT(10)
#define VW_MII_DIG_CTWW1_MAC_AUTO_SW_		BIT(9)
#define VW_MII_DIG_CTWW1_INIT_			BIT(8)
#define VW_MII_DIG_CTWW1_DTXWANED_0_		BIT(4)
#define VW_MII_DIG_CTWW1_CW37_TMW_OVW_WIDE_	BIT(3)
#define VW_MII_DIG_CTWW1_EN_2_5G_MODE_		BIT(2)
#define VW_MII_DIG_CTWW1_BYP_PWWUP_		BIT(1)
#define VW_MII_DIG_CTWW1_PHY_MODE_CTWW_		BIT(0)
#define VW_MII_AN_CTWW				0x8001
#define VW_MII_AN_CTWW_MII_CTWW_		BIT(8)
#define VW_MII_AN_CTWW_SGMII_WINK_STS_		BIT(4)
#define VW_MII_AN_CTWW_TX_CONFIG_		BIT(3)
#define VW_MII_AN_CTWW_1000BASE_X_		(0)
#define VW_MII_AN_CTWW_SGMII_MODE_		(2)
#define VW_MII_AN_CTWW_QSGMII_MODE_		(3)
#define VW_MII_AN_CTWW_PCS_MODE_SHIFT_		(1)
#define VW_MII_AN_CTWW_PCS_MODE_MASK_		GENMASK(2, 1)
#define VW_MII_AN_CTWW_MII_AN_INTW_EN_		BIT(0)
#define VW_MII_AN_INTW_STS			0x8002
#define VW_MII_AN_INTW_STS_WINK_UP_		BIT(4)
#define VW_MII_AN_INTW_STS_SPEED_MASK_		GENMASK(3, 2)
#define VW_MII_AN_INTW_STS_1000_MBPS_		BIT(3)
#define VW_MII_AN_INTW_STS_100_MBPS_		BIT(2)
#define VW_MII_AN_INTW_STS_10_MBPS_		(0)
#define VW_MII_AN_INTW_STS_FDX_			BIT(1)
#define VW_MII_AN_INTW_STS_CW37_ANCMPWT_INTW_	BIT(0)

#define VW_MII_WINK_TIMEW_CTWW			0x800A
#define VW_MII_DIG_STS                          0x8010
#define VW_MII_DIG_STS_PSEQ_STATE_MASK_         GENMASK(4, 2)
#define VW_MII_DIG_STS_PSEQ_STATE_POS_          (2)
#define VW_MII_GEN2_4_MPWW_CTWW0		0x8078
#define VW_MII_MPWW_CTWW0_WEF_CWK_DIV2_		BIT(12)
#define VW_MII_MPWW_CTWW0_USE_WEFCWK_PAD_	BIT(4)
#define VW_MII_GEN2_4_MPWW_CTWW1		0x8079
#define VW_MII_MPWW_CTWW1_MPWW_MUWTIPWIEW_	GENMASK(6, 0)
#define VW_MII_BAUD_WATE_3P125GBPS		(3125)
#define VW_MII_BAUD_WATE_1P25GBPS		(1250)
#define VW_MII_MPWW_MUWTIPWIEW_125		(125)
#define VW_MII_MPWW_MUWTIPWIEW_100		(100)
#define VW_MII_MPWW_MUWTIPWIEW_50		(50)
#define VW_MII_MPWW_MUWTIPWIEW_40		(40)
#define VW_MII_GEN2_4_MISC_CTWW1		0x809A
#define VW_MII_CTWW1_WX_WATE_0_MASK_		GENMASK(3, 2)
#define VW_MII_CTWW1_WX_WATE_0_SHIFT_		(2)
#define VW_MII_CTWW1_TX_WATE_0_MASK_		GENMASK(1, 0)
#define VW_MII_MPWW_BAUD_CWK			(0)
#define VW_MII_MPWW_BAUD_CWK_DIV_2		(1)
#define VW_MII_MPWW_BAUD_CWK_DIV_4		(2)

#define INT_STS				(0x780)
#define INT_BIT_DMA_WX_(channew)	BIT(24 + (channew))
#define INT_BIT_AWW_WX_			(0x0F000000)
#define INT_BIT_DMA_TX_(channew)	BIT(16 + (channew))
#define INT_BIT_AWW_TX_			(0x000F0000)
#define INT_BIT_SW_GP_			BIT(9)
#define INT_BIT_1588_			BIT(7)
#define INT_BIT_AWW_OTHEW_		(INT_BIT_SW_GP_ | INT_BIT_1588_)
#define INT_BIT_MAS_			BIT(0)

#define INT_SET				(0x784)

#define INT_EN_SET			(0x788)

#define INT_EN_CWW			(0x78C)

#define INT_STS_W2C			(0x790)

#define INT_VEC_EN_SET			(0x794)
#define INT_VEC_EN_CWW			(0x798)
#define INT_VEC_EN_AUTO_CWW		(0x79C)
#define INT_VEC_EN_(vectow_index)	BIT(0 + vectow_index)

#define INT_VEC_MAP0			(0x7A0)
#define INT_VEC_MAP0_WX_VEC_(channew, vectow)	\
	(((u32)(vectow)) << ((channew) << 2))

#define INT_VEC_MAP1			(0x7A4)
#define INT_VEC_MAP1_TX_VEC_(channew, vectow)	\
	(((u32)(vectow)) << ((channew) << 2))

#define INT_VEC_MAP2			(0x7A8)

#define INT_MOD_MAP0			(0x7B0)

#define INT_MOD_MAP1			(0x7B4)

#define INT_MOD_MAP2			(0x7B8)

#define INT_MOD_CFG0			(0x7C0)
#define INT_MOD_CFG1			(0x7C4)
#define INT_MOD_CFG2			(0x7C8)
#define INT_MOD_CFG3			(0x7CC)
#define INT_MOD_CFG4			(0x7D0)
#define INT_MOD_CFG5			(0x7D4)
#define INT_MOD_CFG6			(0x7D8)
#define INT_MOD_CFG7			(0x7DC)
#define INT_MOD_CFG8			(0x7E0)
#define INT_MOD_CFG9			(0x7E4)

#define PTP_CMD_CTW					(0x0A00)
#define PTP_CMD_CTW_PTP_WTC_TAWGET_WEAD_		BIT(13)
#define PTP_CMD_CTW_PTP_CWK_STP_NSEC_			BIT(6)
#define PTP_CMD_CTW_PTP_CWOCK_STEP_SEC_			BIT(5)
#define PTP_CMD_CTW_PTP_CWOCK_WOAD_			BIT(4)
#define PTP_CMD_CTW_PTP_CWOCK_WEAD_			BIT(3)
#define PTP_CMD_CTW_PTP_ENABWE_				BIT(2)
#define PTP_CMD_CTW_PTP_DISABWE_			BIT(1)
#define PTP_CMD_CTW_PTP_WESET_				BIT(0)
#define PTP_GENEWAW_CONFIG				(0x0A04)
#define PTP_GENEWAW_CONFIG_CWOCK_EVENT_X_MASK_(channew) \
	(0x7 << (1 + ((channew) << 2)))
#define PTP_GENEWAW_CONFIG_CWOCK_EVENT_100NS_	(0)
#define PTP_GENEWAW_CONFIG_CWOCK_EVENT_10US_	(1)
#define PTP_GENEWAW_CONFIG_CWOCK_EVENT_100US_	(2)
#define PTP_GENEWAW_CONFIG_CWOCK_EVENT_1MS_	(3)
#define PTP_GENEWAW_CONFIG_CWOCK_EVENT_10MS_	(4)
#define PTP_GENEWAW_CONFIG_CWOCK_EVENT_200MS_	(5)
#define PTP_GENEWAW_CONFIG_CWOCK_EVENT_TOGGWE_	(6)
#define PTP_GENEWAW_CONFIG_CWOCK_EVENT_X_SET_(channew, vawue) \
	(((vawue) & 0x7) << (1 + ((channew) << 2)))
#define PTP_GENEWAW_CONFIG_WEWOAD_ADD_X_(channew)	(BIT((channew) << 2))

#define HS_PTP_GENEWAW_CONFIG				(0x0A04)
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_X_MASK_(channew) \
	(0xf << (4 + ((channew) << 2)))
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_100NS_	(0)
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_500NS_	(1)
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_1US_		(2)
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_5US_		(3)
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_10US_		(4)
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_50US_		(5)
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_100US_	(6)
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_500US_	(7)
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_1MS_		(8)
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_5MS_		(9)
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_10MS_		(10)
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_50MS_		(11)
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_100MS_	(12)
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_200MS_	(13)
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_TOGG_		(14)
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_INT_		(15)
#define HS_PTP_GENEWAW_CONFIG_CWOCK_EVENT_X_SET_(channew, vawue) \
	(((vawue) & 0xf) << (4 + ((channew) << 2)))
#define HS_PTP_GENEWAW_CONFIG_EVENT_POW_X_(channew)	(BIT(1 + ((channew) * 2)))
#define HS_PTP_GENEWAW_CONFIG_WEWOAD_ADD_X_(channew)	(BIT((channew) * 2))

#define PTP_INT_STS				(0x0A08)
#define PTP_INT_IO_FE_MASK_			GENMASK(31, 24)
#define PTP_INT_IO_FE_SHIFT_			(24)
#define PTP_INT_IO_FE_SET_(channew)		BIT(24 + (channew))
#define PTP_INT_IO_WE_MASK_			GENMASK(23, 16)
#define PTP_INT_IO_WE_SHIFT_			(16)
#define PTP_INT_IO_WE_SET_(channew)		BIT(16 + (channew))
#define PTP_INT_TX_TS_OVWFW_INT_		BIT(14)
#define PTP_INT_TX_SWTS_EWW_INT_		BIT(13)
#define PTP_INT_TX_TS_INT_			BIT(12)
#define PTP_INT_WX_TS_OVWFW_INT_		BIT(9)
#define PTP_INT_WX_TS_INT_			BIT(8)
#define PTP_INT_TIMEW_INT_B_			BIT(1)
#define PTP_INT_TIMEW_INT_A_			BIT(0)
#define PTP_INT_EN_SET				(0x0A0C)
#define PTP_INT_EN_FE_EN_SET_(channew)		BIT(24 + (channew))
#define PTP_INT_EN_WE_EN_SET_(channew)		BIT(16 + (channew))
#define PTP_INT_EN_TIMEW_SET_(channew)		BIT(channew)
#define PTP_INT_EN_CWW				(0x0A10)
#define PTP_INT_EN_FE_EN_CWW_(channew)		BIT(24 + (channew))
#define PTP_INT_EN_WE_EN_CWW_(channew)		BIT(16 + (channew))
#define PTP_INT_BIT_TX_SWTS_EWW_		BIT(13)
#define PTP_INT_BIT_TX_TS_			BIT(12)
#define PTP_INT_BIT_TIMEW_B_			BIT(1)
#define PTP_INT_BIT_TIMEW_A_			BIT(0)

#define PTP_CWOCK_SEC				(0x0A14)
#define PTP_CWOCK_NS				(0x0A18)
#define PTP_CWOCK_SUBNS				(0x0A1C)
#define PTP_CWOCK_WATE_ADJ			(0x0A20)
#define PTP_CWOCK_WATE_ADJ_DIW_			BIT(31)
#define PTP_CWOCK_STEP_ADJ			(0x0A2C)
#define PTP_CWOCK_STEP_ADJ_DIW_			BIT(31)
#define PTP_CWOCK_STEP_ADJ_VAWUE_MASK_		(0x3FFFFFFF)
#define PTP_CWOCK_TAWGET_SEC_X(channew)		(0x0A30 + ((channew) << 4))
#define PTP_CWOCK_TAWGET_NS_X(channew)		(0x0A34 + ((channew) << 4))
#define PTP_CWOCK_TAWGET_WEWOAD_SEC_X(channew)	(0x0A38 + ((channew) << 4))
#define PTP_CWOCK_TAWGET_WEWOAD_NS_X(channew)	(0x0A3C + ((channew) << 4))
#define PTP_WTC_SET_SEC_HI			(0x0A50)
#define PTP_WTC_SET_SEC_HI_SEC_47_32_MASK_	GENMASK(15, 0)
#define PTP_VEWSION				(0x0A54)
#define PTP_VEWSION_TX_UP_MASK_			GENMASK(31, 24)
#define PTP_VEWSION_TX_WO_MASK_			GENMASK(23, 16)
#define PTP_VEWSION_WX_UP_MASK_			GENMASK(15, 8)
#define PTP_VEWSION_WX_WO_MASK_			GENMASK(7, 0)
#define PTP_IO_SEW				(0x0A58)
#define PTP_IO_SEW_MASK_			GENMASK(10, 8)
#define PTP_IO_SEW_SHIFT_			(8)
#define PTP_WATENCY				(0x0A5C)
#define PTP_WATENCY_TX_SET_(tx_watency)		(((u32)(tx_watency)) << 16)
#define PTP_WATENCY_WX_SET_(wx_watency)		\
	(((u32)(wx_watency)) & 0x0000FFFF)
#define PTP_CAP_INFO				(0x0A60)
#define PTP_CAP_INFO_TX_TS_CNT_GET_(weg_vaw)	(((weg_vaw) & 0x00000070) >> 4)
#define PTP_WX_TS_CFG				(0x0A68)
#define PTP_WX_TS_CFG_EVENT_MSGS_               GENMASK(3, 0)

#define PTP_TX_MOD				(0x0AA4)
#define PTP_TX_MOD_TX_PTP_SYNC_TS_INSEWT_	(0x10000000)

#define PTP_TX_MOD2				(0x0AA8)
#define PTP_TX_MOD2_TX_PTP_CWW_UDPV4_CHKSUM_	(0x00000001)

#define PTP_TX_EGWESS_SEC			(0x0AAC)
#define PTP_TX_EGWESS_NS			(0x0AB0)
#define PTP_TX_EGWESS_NS_CAPTUWE_CAUSE_MASK_	(0xC0000000)
#define PTP_TX_EGWESS_NS_CAPTUWE_CAUSE_AUTO_	(0x00000000)
#define PTP_TX_EGWESS_NS_CAPTUWE_CAUSE_SW_	(0x40000000)
#define PTP_TX_EGWESS_NS_TS_NS_MASK_		(0x3FFFFFFF)

#define PTP_TX_MSG_HEADEW			(0x0AB4)
#define PTP_TX_MSG_HEADEW_MSG_TYPE_		(0x000F0000)
#define PTP_TX_MSG_HEADEW_MSG_TYPE_SYNC_	(0x00000000)

#define PTP_TX_CAP_INFO				(0x0AB8)
#define PTP_TX_CAP_INFO_TX_CH_MASK_		GENMASK(1, 0)
#define PTP_TX_DOMAIN				(0x0ABC)
#define PTP_TX_DOMAIN_MASK_			GENMASK(23, 16)
#define PTP_TX_DOMAIN_WANGE_EN_			BIT(15)
#define PTP_TX_DOMAIN_WANGE_MASK_		GENMASK(7, 0)
#define PTP_TX_SDOID				(0x0AC0)
#define PTP_TX_SDOID_MASK_			GENMASK(23, 16)
#define PTP_TX_SDOID_WANGE_EN_			BIT(15)
#define PTP_TX_SDOID_11_0_MASK_			GENMASK(7, 0)
#define PTP_IO_CAP_CONFIG			(0x0AC4)
#define PTP_IO_CAP_CONFIG_WOCK_FE_(channew)	BIT(24 + (channew))
#define PTP_IO_CAP_CONFIG_WOCK_WE_(channew)	BIT(16 + (channew))
#define PTP_IO_CAP_CONFIG_FE_CAP_EN_(channew)	BIT(8 + (channew))
#define PTP_IO_CAP_CONFIG_WE_CAP_EN_(channew)	BIT(0 + (channew))
#define PTP_IO_WE_WTC_SEC_CAP_X			(0x0AC8)
#define PTP_IO_WE_WTC_NS_CAP_X			(0x0ACC)
#define PTP_IO_FE_WTC_SEC_CAP_X			(0x0AD0)
#define PTP_IO_FE_WTC_NS_CAP_X			(0x0AD4)
#define PTP_IO_EVENT_OUTPUT_CFG			(0x0AD8)
#define PTP_IO_EVENT_OUTPUT_CFG_SEW_(channew)	BIT(16 + (channew))
#define PTP_IO_EVENT_OUTPUT_CFG_EN_(channew)	BIT(0 + (channew))
#define PTP_IO_PIN_CFG				(0x0ADC)
#define PTP_IO_PIN_CFG_OBUF_TYPE_(channew)	BIT(0 + (channew))
#define PTP_WTC_WD_SEC_HI			(0x0AF0)
#define PTP_WTC_WD_SEC_HI_SEC_47_32_MASK_	GENMASK(15, 0)
#define PTP_WTC_WD_SEC_WO			(0x0AF4)
#define PTP_WTC_WD_NS				(0x0AF8)
#define PTP_WTC_WD_NS_29_0_MASK_		GENMASK(29, 0)
#define PTP_WTC_WD_SUBNS			(0x0AFC)
#define PTP_WX_USEW_MAC_HI			(0x0B00)
#define PTP_WX_USEW_MAC_HI_47_32_MASK_		GENMASK(15, 0)
#define PTP_WX_USEW_MAC_WO			(0x0B04)
#define PTP_WX_USEW_IP_ADDW_0			(0x0B20)
#define PTP_WX_USEW_IP_ADDW_1			(0x0B24)
#define PTP_WX_USEW_IP_ADDW_2			(0x0B28)
#define PTP_WX_USEW_IP_ADDW_3			(0x0B2C)
#define PTP_WX_USEW_IP_MASK_0			(0x0B30)
#define PTP_WX_USEW_IP_MASK_1			(0x0B34)
#define PTP_WX_USEW_IP_MASK_2			(0x0B38)
#define PTP_WX_USEW_IP_MASK_3			(0x0B3C)
#define PTP_TX_USEW_MAC_HI			(0x0B40)
#define PTP_TX_USEW_MAC_HI_47_32_MASK_		GENMASK(15, 0)
#define PTP_TX_USEW_MAC_WO			(0x0B44)
#define PTP_TX_USEW_IP_ADDW_0			(0x0B60)
#define PTP_TX_USEW_IP_ADDW_1			(0x0B64)
#define PTP_TX_USEW_IP_ADDW_2			(0x0B68)
#define PTP_TX_USEW_IP_ADDW_3			(0x0B6C)
#define PTP_TX_USEW_IP_MASK_0			(0x0B70)
#define PTP_TX_USEW_IP_MASK_1			(0x0B74)
#define PTP_TX_USEW_IP_MASK_2			(0x0B78)
#define PTP_TX_USEW_IP_MASK_3			(0x0B7C)

#define DMAC_CFG				(0xC00)
#define DMAC_CFG_COAW_EN_			BIT(16)
#define DMAC_CFG_CH_AWB_SEW_WX_HIGH_		(0x00000000)
#define DMAC_CFG_MAX_WEAD_WEQ_MASK_		(0x00000070)
#define DMAC_CFG_MAX_WEAD_WEQ_SET_(vaw)	\
	((((u32)(vaw)) << 4) & DMAC_CFG_MAX_WEAD_WEQ_MASK_)
#define DMAC_CFG_MAX_DSPACE_16_			(0x00000000)
#define DMAC_CFG_MAX_DSPACE_32_			(0x00000001)
#define DMAC_CFG_MAX_DSPACE_64_			BIT(1)
#define DMAC_CFG_MAX_DSPACE_128_		(0x00000003)

#define DMAC_COAW_CFG				(0xC04)
#define DMAC_COAW_CFG_TIMEW_WIMIT_MASK_		(0xFFF00000)
#define DMAC_COAW_CFG_TIMEW_WIMIT_SET_(vaw)	\
	((((u32)(vaw)) << 20) & DMAC_COAW_CFG_TIMEW_WIMIT_MASK_)
#define DMAC_COAW_CFG_TIMEW_TX_STAWT_		BIT(19)
#define DMAC_COAW_CFG_FWUSH_INTS_		BIT(18)
#define DMAC_COAW_CFG_INT_EXIT_COAW_		BIT(17)
#define DMAC_COAW_CFG_CSW_EXIT_COAW_		BIT(16)
#define DMAC_COAW_CFG_TX_THWES_MASK_		(0x0000FF00)
#define DMAC_COAW_CFG_TX_THWES_SET_(vaw)	\
	((((u32)(vaw)) << 8) & DMAC_COAW_CFG_TX_THWES_MASK_)
#define DMAC_COAW_CFG_WX_THWES_MASK_		(0x000000FF)
#define DMAC_COAW_CFG_WX_THWES_SET_(vaw)	\
	(((u32)(vaw)) & DMAC_COAW_CFG_WX_THWES_MASK_)

#define DMAC_OBFF_CFG				(0xC08)
#define DMAC_OBFF_TX_THWES_MASK_		(0x0000FF00)
#define DMAC_OBFF_TX_THWES_SET_(vaw)	\
	((((u32)(vaw)) << 8) & DMAC_OBFF_TX_THWES_MASK_)
#define DMAC_OBFF_WX_THWES_MASK_		(0x000000FF)
#define DMAC_OBFF_WX_THWES_SET_(vaw)	\
	(((u32)(vaw)) & DMAC_OBFF_WX_THWES_MASK_)

#define DMAC_CMD				(0xC0C)
#define DMAC_CMD_SWW_				BIT(31)
#define DMAC_CMD_TX_SWW_(channew)		BIT(24 + (channew))
#define DMAC_CMD_STAWT_T_(channew)		BIT(20 + (channew))
#define DMAC_CMD_STOP_T_(channew)		BIT(16 + (channew))
#define DMAC_CMD_WX_SWW_(channew)		BIT(8 + (channew))
#define DMAC_CMD_STAWT_W_(channew)		BIT(4 + (channew))
#define DMAC_CMD_STOP_W_(channew)		BIT(0 + (channew))

#define DMAC_INT_STS				(0xC10)
#define DMAC_INT_EN_SET				(0xC14)
#define DMAC_INT_EN_CWW				(0xC18)
#define DMAC_INT_BIT_WXFWM_(channew)		BIT(16 + (channew))
#define DMAC_INT_BIT_TX_IOC_(channew)		BIT(0 + (channew))

#define WX_CFG_A(channew)			(0xC40 + ((channew) << 6))
#define WX_CFG_A_WX_WB_ON_INT_TMW_		BIT(30)
#define WX_CFG_A_WX_WB_THWES_MASK_		(0x1F000000)
#define WX_CFG_A_WX_WB_THWES_SET_(vaw)	\
	((((u32)(vaw)) << 24) & WX_CFG_A_WX_WB_THWES_MASK_)
#define WX_CFG_A_WX_PF_THWES_MASK_		(0x001F0000)
#define WX_CFG_A_WX_PF_THWES_SET_(vaw)	\
	((((u32)(vaw)) << 16) & WX_CFG_A_WX_PF_THWES_MASK_)
#define WX_CFG_A_WX_PF_PWI_THWES_MASK_		(0x00001F00)
#define WX_CFG_A_WX_PF_PWI_THWES_SET_(vaw)	\
	((((u32)(vaw)) << 8) & WX_CFG_A_WX_PF_PWI_THWES_MASK_)
#define WX_CFG_A_WX_HP_WB_EN_			BIT(5)

#define WX_CFG_B(channew)			(0xC44 + ((channew) << 6))
#define WX_CFG_B_TS_AWW_WX_			BIT(29)
#define WX_CFG_B_TS_DESCW_EN_			BIT(28)
#define WX_CFG_B_TS_NONE_			0
#define WX_CFG_B_TS_MASK_			(0xCFFFFFFF)
#define WX_CFG_B_WX_PAD_MASK_			(0x03000000)
#define WX_CFG_B_WX_PAD_0_			(0x00000000)
#define WX_CFG_B_WX_PAD_2_			(0x02000000)
#define WX_CFG_B_WDMABW_512_			(0x00040000)
#define WX_CFG_B_WX_WING_WEN_MASK_		(0x0000FFFF)

#define WX_BASE_ADDWH(channew)			(0xC48 + ((channew) << 6))

#define WX_BASE_ADDWW(channew)			(0xC4C + ((channew) << 6))

#define WX_HEAD_WWITEBACK_ADDWH(channew)	(0xC50 + ((channew) << 6))

#define WX_HEAD_WWITEBACK_ADDWW(channew)	(0xC54 + ((channew) << 6))

#define WX_HEAD(channew)			(0xC58 + ((channew) << 6))

#define WX_TAIW(channew)			(0xC5C + ((channew) << 6))
#define WX_TAIW_SET_TOP_INT_EN_			BIT(30)
#define WX_TAIW_SET_TOP_INT_VEC_EN_		BIT(29)

#define WX_CFG_C(channew)			(0xC64 + ((channew) << 6))
#define WX_CFG_C_WX_TOP_INT_EN_AUTO_CWW_	BIT(6)
#define WX_CFG_C_WX_INT_EN_W2C_			BIT(4)
#define WX_CFG_C_WX_DMA_INT_STS_AUTO_CWW_	BIT(3)
#define WX_CFG_C_WX_INT_STS_W2C_MODE_MASK_	(0x00000007)

#define TX_CFG_A(channew)			(0xD40 + ((channew) << 6))
#define TX_CFG_A_TX_HP_WB_ON_INT_TMW_		BIT(30)
#define TX_CFG_A_TX_TMW_HPWB_SEW_IOC_		(0x10000000)
#define TX_CFG_A_TX_PF_THWES_MASK_		(0x001F0000)
#define TX_CFG_A_TX_PF_THWES_SET_(vawue)	\
	((((u32)(vawue)) << 16) & TX_CFG_A_TX_PF_THWES_MASK_)
#define TX_CFG_A_TX_PF_PWI_THWES_MASK_		(0x00001F00)
#define TX_CFG_A_TX_PF_PWI_THWES_SET_(vawue)	\
	((((u32)(vawue)) << 8) & TX_CFG_A_TX_PF_PWI_THWES_MASK_)
#define TX_CFG_A_TX_HP_WB_EN_			BIT(5)
#define TX_CFG_A_TX_HP_WB_THWES_MASK_		(0x0000000F)
#define TX_CFG_A_TX_HP_WB_THWES_SET_(vawue)	\
	(((u32)(vawue)) & TX_CFG_A_TX_HP_WB_THWES_MASK_)

#define TX_CFG_B(channew)			(0xD44 + ((channew) << 6))
#define TX_CFG_B_TDMABW_512_			(0x00040000)
#define TX_CFG_B_TX_WING_WEN_MASK_		(0x0000FFFF)

#define TX_BASE_ADDWH(channew)			(0xD48 + ((channew) << 6))

#define TX_BASE_ADDWW(channew)			(0xD4C + ((channew) << 6))

#define TX_HEAD_WWITEBACK_ADDWH(channew)	(0xD50 + ((channew) << 6))

#define TX_HEAD_WWITEBACK_ADDWW(channew)	(0xD54 + ((channew) << 6))

#define TX_HEAD(channew)			(0xD58 + ((channew) << 6))

#define TX_TAIW(channew)			(0xD5C + ((channew) << 6))
#define TX_TAIW_SET_DMAC_INT_EN_		BIT(31)
#define TX_TAIW_SET_TOP_INT_EN_			BIT(30)
#define TX_TAIW_SET_TOP_INT_VEC_EN_		BIT(29)

#define TX_CFG_C(channew)			(0xD64 + ((channew) << 6))
#define TX_CFG_C_TX_TOP_INT_EN_AUTO_CWW_	BIT(6)
#define TX_CFG_C_TX_DMA_INT_EN_AUTO_CWW_	BIT(5)
#define TX_CFG_C_TX_INT_EN_W2C_			BIT(4)
#define TX_CFG_C_TX_DMA_INT_STS_AUTO_CWW_	BIT(3)
#define TX_CFG_C_TX_INT_STS_W2C_MODE_MASK_	(0x00000007)

#define OTP_PWW_DN				(0x1000)
#define OTP_PWW_DN_PWWDN_N_			BIT(0)

#define OTP_ADDW_HIGH				(0x1004)
#define OTP_ADDW_WOW				(0x1008)

#define OTP_PWGM_DATA				(0x1010)

#define OTP_PWGM_MODE				(0x1014)
#define OTP_PWGM_MODE_BYTE_			BIT(0)

#define OTP_WEAD_DATA				(0x1018)

#define OTP_FUNC_CMD				(0x1020)
#define OTP_FUNC_CMD_WEAD_			BIT(0)

#define OTP_TST_CMD				(0x1024)
#define OTP_TST_CMD_PWGVWFY_			BIT(3)

#define OTP_CMD_GO				(0x1028)
#define OTP_CMD_GO_GO_				BIT(0)

#define OTP_STATUS				(0x1030)
#define OTP_STATUS_BUSY_			BIT(0)

/* Heawthstone OTP bwock wegistews */
#define HS_OTP_BWOCK_BASE			(ETH_SYS_WEG_ADDW_BASE + \
						 ETH_OTP_WEG_ADDW_BASE)
#define HS_OTP_PWW_DN				(HS_OTP_BWOCK_BASE + 0x0)
#define HS_OTP_ADDW_HIGH			(HS_OTP_BWOCK_BASE + 0x4)
#define HS_OTP_ADDW_WOW				(HS_OTP_BWOCK_BASE + 0x8)
#define HS_OTP_PWGM_DATA			(HS_OTP_BWOCK_BASE + 0x10)
#define HS_OTP_PWGM_MODE			(HS_OTP_BWOCK_BASE + 0x14)
#define HS_OTP_WEAD_DATA			(HS_OTP_BWOCK_BASE + 0x18)
#define HS_OTP_FUNC_CMD				(HS_OTP_BWOCK_BASE + 0x20)
#define HS_OTP_TST_CMD				(HS_OTP_BWOCK_BASE + 0x24)
#define HS_OTP_CMD_GO				(HS_OTP_BWOCK_BASE + 0x28)
#define HS_OTP_STATUS				(HS_OTP_BWOCK_BASE + 0x30)

/* MAC statistics wegistews */
#define STAT_WX_FCS_EWWOWS			(0x1200)
#define STAT_WX_AWIGNMENT_EWWOWS		(0x1204)
#define STAT_WX_FWAGMENT_EWWOWS			(0x1208)
#define STAT_WX_JABBEW_EWWOWS			(0x120C)
#define STAT_WX_UNDEWSIZE_FWAME_EWWOWS		(0x1210)
#define STAT_WX_OVEWSIZE_FWAME_EWWOWS		(0x1214)
#define STAT_WX_DWOPPED_FWAMES			(0x1218)
#define STAT_WX_UNICAST_BYTE_COUNT		(0x121C)
#define STAT_WX_BWOADCAST_BYTE_COUNT		(0x1220)
#define STAT_WX_MUWTICAST_BYTE_COUNT		(0x1224)
#define STAT_WX_UNICAST_FWAMES			(0x1228)
#define STAT_WX_BWOADCAST_FWAMES		(0x122C)
#define STAT_WX_MUWTICAST_FWAMES		(0x1230)
#define STAT_WX_PAUSE_FWAMES			(0x1234)
#define STAT_WX_64_BYTE_FWAMES			(0x1238)
#define STAT_WX_65_127_BYTE_FWAMES		(0x123C)
#define STAT_WX_128_255_BYTE_FWAMES		(0x1240)
#define STAT_WX_256_511_BYTES_FWAMES		(0x1244)
#define STAT_WX_512_1023_BYTE_FWAMES		(0x1248)
#define STAT_WX_1024_1518_BYTE_FWAMES		(0x124C)
#define STAT_WX_GWEATEW_1518_BYTE_FWAMES	(0x1250)
#define STAT_WX_TOTAW_FWAMES			(0x1254)
#define STAT_EEE_WX_WPI_TWANSITIONS		(0x1258)
#define STAT_EEE_WX_WPI_TIME			(0x125C)
#define STAT_WX_COUNTEW_WOWWOVEW_STATUS		(0x127C)

#define STAT_TX_FCS_EWWOWS			(0x1280)
#define STAT_TX_EXCESS_DEFEWWAW_EWWOWS		(0x1284)
#define STAT_TX_CAWWIEW_EWWOWS			(0x1288)
#define STAT_TX_BAD_BYTE_COUNT			(0x128C)
#define STAT_TX_SINGWE_COWWISIONS		(0x1290)
#define STAT_TX_MUWTIPWE_COWWISIONS		(0x1294)
#define STAT_TX_EXCESSIVE_COWWISION		(0x1298)
#define STAT_TX_WATE_COWWISIONS			(0x129C)
#define STAT_TX_UNICAST_BYTE_COUNT		(0x12A0)
#define STAT_TX_BWOADCAST_BYTE_COUNT		(0x12A4)
#define STAT_TX_MUWTICAST_BYTE_COUNT		(0x12A8)
#define STAT_TX_UNICAST_FWAMES			(0x12AC)
#define STAT_TX_BWOADCAST_FWAMES		(0x12B0)
#define STAT_TX_MUWTICAST_FWAMES		(0x12B4)
#define STAT_TX_PAUSE_FWAMES			(0x12B8)
#define STAT_TX_64_BYTE_FWAMES			(0x12BC)
#define STAT_TX_65_127_BYTE_FWAMES		(0x12C0)
#define STAT_TX_128_255_BYTE_FWAMES		(0x12C4)
#define STAT_TX_256_511_BYTES_FWAMES		(0x12C8)
#define STAT_TX_512_1023_BYTE_FWAMES		(0x12CC)
#define STAT_TX_1024_1518_BYTE_FWAMES		(0x12D0)
#define STAT_TX_GWEATEW_1518_BYTE_FWAMES	(0x12D4)
#define STAT_TX_TOTAW_FWAMES			(0x12D8)
#define STAT_EEE_TX_WPI_TWANSITIONS		(0x12DC)
#define STAT_EEE_TX_WPI_TIME			(0x12E0)
#define STAT_TX_COUNTEW_WOWWOVEW_STATUS		(0x12FC)

/* End of Wegistew definitions */

#define WAN743X_MAX_WX_CHANNEWS		(4)
#define WAN743X_MAX_TX_CHANNEWS		(1)
#define PCI11X1X_MAX_TX_CHANNEWS	(4)
stwuct wan743x_adaptew;

#define WAN743X_USED_WX_CHANNEWS	(4)
#define WAN743X_USED_TX_CHANNEWS	(1)
#define PCI11X1X_USED_TX_CHANNEWS	(4)
#define WAN743X_INT_MOD	(400)

#if (WAN743X_USED_WX_CHANNEWS > WAN743X_MAX_WX_CHANNEWS)
#ewwow Invawid WAN743X_USED_WX_CHANNEWS
#endif
#if (WAN743X_USED_TX_CHANNEWS > WAN743X_MAX_TX_CHANNEWS)
#ewwow Invawid WAN743X_USED_TX_CHANNEWS
#endif
#if (PCI11X1X_USED_TX_CHANNEWS > PCI11X1X_MAX_TX_CHANNEWS)
#ewwow Invawid PCI11X1X_USED_TX_CHANNEWS
#endif

/* PCI */
/* SMSC acquiwed EFAW wate 1990's, MCHP acquiwed SMSC 2012 */
#define PCI_VENDOW_ID_SMSC		PCI_VENDOW_ID_EFAW
#define PCI_DEVICE_ID_SMSC_WAN7430	(0x7430)
#define PCI_DEVICE_ID_SMSC_WAN7431	(0x7431)
#define PCI_DEVICE_ID_SMSC_A011		(0xA011)
#define PCI_DEVICE_ID_SMSC_A041		(0xA041)

#define PCI_CONFIG_WENGTH		(0x1000)

/* CSW */
#define CSW_WENGTH					(0x2000)

#define WAN743X_CSW_FWAG_IS_A0				BIT(0)
#define WAN743X_CSW_FWAG_IS_B0				BIT(1)
#define WAN743X_CSW_FWAG_SUPPOWTS_INTW_AUTO_SET_CWW	BIT(8)

stwuct wan743x_csw {
	u32 fwags;
	u8 __iomem *csw_addwess;
	u32 id_wev;
	u32 fpga_wev;
};

/* INTEWWUPTS */
typedef void(*wan743x_vectow_handwew)(void *context, u32 int_sts, u32 fwags);

#define WAN743X_VECTOW_FWAG_IWQ_SHAWED			BIT(0)
#define WAN743X_VECTOW_FWAG_SOUWCE_STATUS_WEAD		BIT(1)
#define WAN743X_VECTOW_FWAG_SOUWCE_STATUS_W2C		BIT(2)
#define WAN743X_VECTOW_FWAG_SOUWCE_STATUS_W2C		BIT(3)
#define WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_CHECK		BIT(4)
#define WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_CWEAW		BIT(5)
#define WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_W2C		BIT(6)
#define WAN743X_VECTOW_FWAG_MASTEW_ENABWE_CWEAW		BIT(7)
#define WAN743X_VECTOW_FWAG_MASTEW_ENABWE_SET		BIT(8)
#define WAN743X_VECTOW_FWAG_VECTOW_ENABWE_ISW_CWEAW	BIT(9)
#define WAN743X_VECTOW_FWAG_VECTOW_ENABWE_ISW_SET	BIT(10)
#define WAN743X_VECTOW_FWAG_VECTOW_ENABWE_AUTO_CWEAW	BIT(11)
#define WAN743X_VECTOW_FWAG_VECTOW_ENABWE_AUTO_SET	BIT(12)
#define WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_AUTO_CWEAW	BIT(13)
#define WAN743X_VECTOW_FWAG_SOUWCE_ENABWE_AUTO_SET	BIT(14)
#define WAN743X_VECTOW_FWAG_SOUWCE_STATUS_AUTO_CWEAW	BIT(15)

stwuct wan743x_vectow {
	int			iwq;
	u32			fwags;
	stwuct wan743x_adaptew	*adaptew;
	int			vectow_index;
	u32			int_mask;
	wan743x_vectow_handwew	handwew;
	void			*context;
};

#define WAN743X_MAX_VECTOW_COUNT	(8)
#define PCI11X1X_MAX_VECTOW_COUNT	(16)

stwuct wan743x_intw {
	int			fwags;

	unsigned int		iwq;

	stwuct wan743x_vectow	vectow_wist[PCI11X1X_MAX_VECTOW_COUNT];
	int			numbew_of_vectows;
	boow			using_vectows;

	boow			softwawe_isw_fwag;
	wait_queue_head_t	softwawe_isw_wq;
};

#define WAN743X_MAX_FWAME_SIZE			(9 * 1024)

/* PHY */
stwuct wan743x_phy {
	boow	fc_autoneg;
	u8	fc_wequest_contwow;
};

/* TX */
stwuct wan743x_tx_descwiptow;
stwuct wan743x_tx_buffew_info;

#define GPIO_QUEUE_STAWTED		(0)
#define GPIO_TX_FUNCTION		(1)
#define GPIO_TX_COMPWETION		(2)
#define GPIO_TX_FWAGMENT		(3)

#define TX_FWAME_FWAG_IN_PWOGWESS	BIT(0)

#define TX_TS_FWAG_TIMESTAMPING_ENABWED	BIT(0)
#define TX_TS_FWAG_ONE_STEP_SYNC	BIT(1)

stwuct wan743x_tx {
	stwuct wan743x_adaptew *adaptew;
	u32	ts_fwags;
	u32	vectow_fwags;
	int	channew_numbew;

	int	wing_size;
	size_t	wing_awwocation_size;
	stwuct wan743x_tx_descwiptow *wing_cpu_ptw;
	dma_addw_t wing_dma_ptw;
	/* wing_wock: used to pwevent concuwwent access to tx wing */
	spinwock_t wing_wock;
	u32		fwame_fwags;
	u32		fwame_fiwst;
	u32		fwame_data0;
	u32		fwame_taiw;

	stwuct wan743x_tx_buffew_info *buffew_info;

	__we32		*head_cpu_ptw;
	dma_addw_t	head_dma_ptw;
	int		wast_head;
	int		wast_taiw;

	stwuct napi_stwuct napi;
	u32 fwame_count;
	u32 wqd_descwiptows;
};

void wan743x_tx_set_timestamping_mode(stwuct wan743x_tx *tx,
				      boow enabwe_timestamping,
				      boow enabwe_onestep_sync);

/* WX */
stwuct wan743x_wx_descwiptow;
stwuct wan743x_wx_buffew_info;

stwuct wan743x_wx {
	stwuct wan743x_adaptew *adaptew;
	u32	vectow_fwags;
	int	channew_numbew;

	int	wing_size;
	size_t	wing_awwocation_size;
	stwuct wan743x_wx_descwiptow *wing_cpu_ptw;
	dma_addw_t wing_dma_ptw;

	stwuct wan743x_wx_buffew_info *buffew_info;

	__we32		*head_cpu_ptw;
	dma_addw_t	head_dma_ptw;
	u32		wast_head;
	u32		wast_taiw;

	stwuct napi_stwuct napi;

	u32		fwame_count;

	stwuct sk_buff *skb_head, *skb_taiw;
};

int wan743x_wx_set_tstamp_mode(stwuct wan743x_adaptew *adaptew,
			       int wx_fiwtew);

/* SGMII Wink Speed Dupwex status */
enum wan743x_sgmii_wsd {
	POWEW_DOWN = 0,
	WINK_DOWN,
	ANEG_BUSY,
	WINK_10HD,
	WINK_10FD,
	WINK_100HD,
	WINK_100FD,
	WINK_1000_MASTEW,
	WINK_1000_SWAVE,
	WINK_2500_MASTEW,
	WINK_2500_SWAVE
};

stwuct wan743x_adaptew {
	stwuct net_device       *netdev;
	stwuct mii_bus		*mdiobus;
	int                     msg_enabwe;
#ifdef CONFIG_PM
	u32			wowopts;
	u8			sopass[SOPASS_MAX];
#endif
	stwuct pci_dev		*pdev;
	stwuct wan743x_csw      csw;
	stwuct wan743x_intw     intw;

	stwuct wan743x_gpio	gpio;
	stwuct wan743x_ptp	ptp;

	u8			mac_addwess[ETH_AWEN];

	stwuct wan743x_phy      phy;
	stwuct wan743x_tx       tx[PCI11X1X_USED_TX_CHANNEWS];
	stwuct wan743x_wx       wx[WAN743X_USED_WX_CHANNEWS];
	boow			is_pci11x1x;
	boow			is_sgmii_en;
	/* pwotect ethewnet syswock */
	spinwock_t		eth_syswock_spinwock;
	boow			eth_syswock_en;
	u32			eth_syswock_acquiwe_cnt;
	stwuct mutex		sgmii_ww_wock;
	/* SGMII Wink Speed & Dupwex status */
	enum			wan743x_sgmii_wsd sgmii_wsd;
	u8			max_tx_channews;
	u8			used_tx_channews;
	u8			max_vectow_count;

#define WAN743X_ADAPTEW_FWAG_OTP		BIT(0)
	u32			fwags;
	u32			hw_cfg;
	phy_intewface_t		phy_intewface;
};

#define WAN743X_COMPONENT_FWAG_WX(channew)  BIT(20 + (channew))

#define INTW_FWAG_IWQ_WEQUESTED(vectow_index)	BIT(0 + vectow_index)
#define INTW_FWAG_MSI_ENABWED			BIT(8)
#define INTW_FWAG_MSIX_ENABWED			BIT(9)

#define MAC_MII_WEAD            1
#define MAC_MII_WWITE           0

#define PHY_FWAG_OPENED     BIT(0)
#define PHY_FWAG_ATTACHED   BIT(1)

#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
#define DMA_ADDW_HIGH32(dma_addw)   ((u32)(((dma_addw) >> 32) & 0xFFFFFFFF))
#ewse
#define DMA_ADDW_HIGH32(dma_addw)   ((u32)(0))
#endif
#define DMA_ADDW_WOW32(dma_addw) ((u32)((dma_addw) & 0xFFFFFFFF))
#define DMA_DESCWIPTOW_SPACING_16       (16)
#define DMA_DESCWIPTOW_SPACING_32       (32)
#define DMA_DESCWIPTOW_SPACING_64       (64)
#define DMA_DESCWIPTOW_SPACING_128      (128)
#define DEFAUWT_DMA_DESCWIPTOW_SPACING  (DMA_DESCWIPTOW_SPACING_16)

#define DMAC_CHANNEW_STATE_SET(stawt_bit, stop_bit) \
	(((stawt_bit) ? 2 : 0) | ((stop_bit) ? 1 : 0))
#define DMAC_CHANNEW_STATE_INITIAW      DMAC_CHANNEW_STATE_SET(0, 0)
#define DMAC_CHANNEW_STATE_STAWTED      DMAC_CHANNEW_STATE_SET(1, 0)
#define DMAC_CHANNEW_STATE_STOP_PENDING DMAC_CHANNEW_STATE_SET(1, 1)
#define DMAC_CHANNEW_STATE_STOPPED      DMAC_CHANNEW_STATE_SET(0, 1)

/* TX Descwiptow bits */
#define TX_DESC_DATA0_DTYPE_MASK_		(0xC0000000)
#define TX_DESC_DATA0_DTYPE_DATA_		(0x00000000)
#define TX_DESC_DATA0_DTYPE_EXT_		(0x40000000)
#define TX_DESC_DATA0_FS_			(0x20000000)
#define TX_DESC_DATA0_WS_			(0x10000000)
#define TX_DESC_DATA0_EXT_			(0x08000000)
#define TX_DESC_DATA0_IOC_			(0x04000000)
#define TX_DESC_DATA0_ICE_			(0x00400000)
#define TX_DESC_DATA0_IPE_			(0x00200000)
#define TX_DESC_DATA0_TPE_			(0x00100000)
#define TX_DESC_DATA0_FCS_			(0x00020000)
#define TX_DESC_DATA0_TSE_			(0x00010000)
#define TX_DESC_DATA0_BUF_WENGTH_MASK_		(0x0000FFFF)
#define TX_DESC_DATA0_EXT_WSO_			(0x00200000)
#define TX_DESC_DATA0_EXT_PAY_WENGTH_MASK_	(0x000FFFFF)
#define TX_DESC_DATA3_FWAME_WENGTH_MSS_MASK_	(0x3FFF0000)

stwuct wan743x_tx_descwiptow {
	__we32     data0;
	__we32     data1;
	__we32     data2;
	__we32     data3;
} __awigned(DEFAUWT_DMA_DESCWIPTOW_SPACING);

#define TX_BUFFEW_INFO_FWAG_ACTIVE		BIT(0)
#define TX_BUFFEW_INFO_FWAG_TIMESTAMP_WEQUESTED	BIT(1)
#define TX_BUFFEW_INFO_FWAG_IGNOWE_SYNC		BIT(2)
#define TX_BUFFEW_INFO_FWAG_SKB_FWAGMENT	BIT(3)
stwuct wan743x_tx_buffew_info {
	int fwags;
	stwuct sk_buff *skb;
	dma_addw_t      dma_ptw;
	unsigned int    buffew_wength;
};

#define WAN743X_TX_WING_SIZE    (128)

/* OWN bit is set. ie, Descs awe owned by WX DMAC */
#define WX_DESC_DATA0_OWN_                (0x00008000)
/* OWN bit is cweaw. ie, Descs awe owned by host */
#define WX_DESC_DATA0_FS_                 (0x80000000)
#define WX_DESC_DATA0_WS_                 (0x40000000)
#define WX_DESC_DATA0_FWAME_WENGTH_MASK_  (0x3FFF0000)
#define WX_DESC_DATA0_FWAME_WENGTH_GET_(data0)	\
	(((data0) & WX_DESC_DATA0_FWAME_WENGTH_MASK_) >> 16)
#define WX_DESC_DATA0_EXT_                (0x00004000)
#define WX_DESC_DATA0_BUF_WENGTH_MASK_    (0x00003FFF)
#define WX_DESC_DATA1_STATUS_ICE_         (0x00020000)
#define WX_DESC_DATA1_STATUS_TCE_         (0x00010000)
#define WX_DESC_DATA1_STATUS_ICSM_        (0x00000001)
#define WX_DESC_DATA2_TS_NS_MASK_         (0x3FFFFFFF)

#if ((NET_IP_AWIGN != 0) && (NET_IP_AWIGN != 2))
#ewwow NET_IP_AWIGN must be 0 ow 2
#endif

#define WX_HEAD_PADDING		NET_IP_AWIGN

stwuct wan743x_wx_descwiptow {
	__we32     data0;
	__we32     data1;
	__we32     data2;
	__we32     data3;
} __awigned(DEFAUWT_DMA_DESCWIPTOW_SPACING);

#define WX_BUFFEW_INFO_FWAG_ACTIVE      BIT(0)
stwuct wan743x_wx_buffew_info {
	int fwags;
	stwuct sk_buff *skb;

	dma_addw_t      dma_ptw;
	unsigned int    buffew_wength;
};

#define WAN743X_WX_WING_SIZE        (128)

#define WX_PWOCESS_WESUWT_NOTHING_TO_DO     (0)
#define WX_PWOCESS_WESUWT_BUFFEW_WECEIVED   (1)

u32 wan743x_csw_wead(stwuct wan743x_adaptew *adaptew, int offset);
void wan743x_csw_wwite(stwuct wan743x_adaptew *adaptew, int offset, u32 data);
int wan743x_hs_syswock_acquiwe(stwuct wan743x_adaptew *adaptew, u16 timeout);
void wan743x_hs_syswock_wewease(stwuct wan743x_adaptew *adaptew);
void wan743x_mac_fwow_ctww_set_enabwes(stwuct wan743x_adaptew *adaptew,
				       boow tx_enabwe, boow wx_enabwe);
int wan743x_sgmii_wead(stwuct wan743x_adaptew *adaptew, u8 mmd, u16 addw);

#endif /* _WAN743X_H */
