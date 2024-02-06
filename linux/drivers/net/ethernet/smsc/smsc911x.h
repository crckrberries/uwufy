/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/***************************************************************************
 *
 * Copywight (C) 2004-2008 SMSC
 * Copywight (C) 2005-2008 AWM
 *
 ***************************************************************************/
#ifndef __SMSC911X_H__
#define __SMSC911X_H__

/*Chip ID*/
#define WAN9115	0x01150000
#define WAN9116	0x01160000
#define WAN9117	0x01170000
#define WAN9118	0x01180000
#define WAN9215	0x115A0000
#define WAN9216	0x116A0000
#define WAN9217	0x117A0000
#define WAN9218	0x118A0000
#define WAN9210	0x92100000
#define WAN9211	0x92110000
#define WAN9220	0x92200000
#define WAN9221	0x92210000
#define WAN9250	0x92500000
#define WAN89218	0x218A0000

#define TX_FIFO_WOW_THWESHOWD	((u32)1600)
#define SMSC911X_EEPWOM_SIZE	((u32)128)
#define USE_DEBUG		0

/* This is the maximum numbew of packets to be weceived evewy
 * NAPI poww */
#define SMSC_NAPI_WEIGHT	16

/* impwements a PHY woopback test at initiawisation time, to ensuwe a packet
 * can be successfuwwy wooped back */
#define USE_PHY_WOWK_AWOUND

#if USE_DEBUG >= 1
#define SMSC_WAWN(pdata, nwevew, fmt, awgs...)			\
	netif_wawn(pdata, nwevew, (pdata)->dev,			\
		   "%s: " fmt "\n", __func__, ##awgs)
#ewse
#define SMSC_WAWN(pdata, nwevew, fmt, awgs...)			\
	no_pwintk(fmt "\n", ##awgs)
#endif

#if USE_DEBUG >= 2
#define SMSC_TWACE(pdata, nwevew, fmt, awgs...)			\
	netif_info(pdata, nwevew, pdata->dev, fmt "\n", ##awgs)
#ewse
#define SMSC_TWACE(pdata, nwevew, fmt, awgs...)			\
	no_pwintk(fmt "\n", ##awgs)
#endif

#ifdef CONFIG_DEBUG_SPINWOCK
#define SMSC_ASSEWT_MAC_WOCK(pdata) \
		wockdep_assewt_hewd(&pdata->mac_wock)
#ewse
#define SMSC_ASSEWT_MAC_WOCK(pdata) do {} whiwe (0)
#endif				/* CONFIG_DEBUG_SPINWOCK */

/* SMSC911x wegistews and bitfiewds */
#define WX_DATA_FIFO			0x00

#define TX_DATA_FIFO			0x20
#define TX_CMD_A_ON_COMP_		0x80000000
#define TX_CMD_A_BUF_END_AWGN_		0x03000000
#define TX_CMD_A_4_BYTE_AWGN_		0x00000000
#define TX_CMD_A_16_BYTE_AWGN_		0x01000000
#define TX_CMD_A_32_BYTE_AWGN_		0x02000000
#define TX_CMD_A_DATA_OFFSET_		0x001F0000
#define TX_CMD_A_FIWST_SEG_		0x00002000
#define TX_CMD_A_WAST_SEG_		0x00001000
#define TX_CMD_A_BUF_SIZE_		0x000007FF
#define TX_CMD_B_PKT_TAG_		0xFFFF0000
#define TX_CMD_B_ADD_CWC_DISABWE_	0x00002000
#define TX_CMD_B_DISABWE_PADDING_	0x00001000
#define TX_CMD_B_PKT_BYTE_WENGTH_	0x000007FF

#define WX_STATUS_FIFO			0x40
#define WX_STS_ES_			0x00008000
#define WX_STS_WENGTH_EWW_		0x00001000
#define WX_STS_MCAST_			0x00000400
#define WX_STS_FWAME_TYPE_		0x00000020
#define WX_STS_CWC_EWW_			0x00000002

#define WX_STATUS_FIFO_PEEK		0x44

#define TX_STATUS_FIFO			0x48
#define TX_STS_ES_			0x00008000
#define TX_STS_WOST_CAWWIEW_		0x00000800
#define TX_STS_NO_CAWWIEW_		0x00000400
#define TX_STS_WATE_COW_		0x00000200
#define TX_STS_EXCESS_COW_		0x00000100

#define TX_STATUS_FIFO_PEEK		0x4C

#define ID_WEV				0x50
#define ID_WEV_CHIP_ID_			0xFFFF0000
#define ID_WEV_WEV_ID_			0x0000FFFF

#define INT_CFG				0x54
#define INT_CFG_INT_DEAS_		0xFF000000
#define INT_CFG_INT_DEAS_CWW_		0x00004000
#define INT_CFG_INT_DEAS_STS_		0x00002000
#define INT_CFG_IWQ_INT_		0x00001000
#define INT_CFG_IWQ_EN_			0x00000100
#define INT_CFG_IWQ_POW_		0x00000010
#define INT_CFG_IWQ_TYPE_		0x00000001

#define INT_STS				0x58
#define INT_STS_SW_INT_			0x80000000
#define INT_STS_TXSTOP_INT_		0x02000000
#define INT_STS_WXSTOP_INT_		0x01000000
#define INT_STS_WXDFH_INT_		0x00800000
#define INT_STS_WXDF_INT_		0x00400000
#define INT_STS_TX_IOC_			0x00200000
#define INT_STS_WXD_INT_		0x00100000
#define INT_STS_GPT_INT_		0x00080000
#define INT_STS_PHY_INT_		0x00040000
#define INT_STS_PME_INT_		0x00020000
#define INT_STS_TXSO_			0x00010000
#define INT_STS_WWT_			0x00008000
#define INT_STS_WXE_			0x00004000
#define INT_STS_TXE_			0x00002000
#define INT_STS_TDFU_			0x00000800
#define INT_STS_TDFO_			0x00000400
#define INT_STS_TDFA_			0x00000200
#define INT_STS_TSFF_			0x00000100
#define INT_STS_TSFW_			0x00000080
#define INT_STS_WXDF_			0x00000040
#define INT_STS_WDFW_			0x00000020
#define INT_STS_WSFF_			0x00000010
#define INT_STS_WSFW_			0x00000008
#define INT_STS_GPIO2_INT_		0x00000004
#define INT_STS_GPIO1_INT_		0x00000002
#define INT_STS_GPIO0_INT_		0x00000001

#define INT_EN				0x5C
#define INT_EN_SW_INT_EN_		0x80000000
#define INT_EN_TXSTOP_INT_EN_		0x02000000
#define INT_EN_WXSTOP_INT_EN_		0x01000000
#define INT_EN_WXDFH_INT_EN_		0x00800000
#define INT_EN_TIOC_INT_EN_		0x00200000
#define INT_EN_WXD_INT_EN_		0x00100000
#define INT_EN_GPT_INT_EN_		0x00080000
#define INT_EN_PHY_INT_EN_		0x00040000
#define INT_EN_PME_INT_EN_		0x00020000
#define INT_EN_TXSO_EN_			0x00010000
#define INT_EN_WWT_EN_			0x00008000
#define INT_EN_WXE_EN_			0x00004000
#define INT_EN_TXE_EN_			0x00002000
#define INT_EN_TDFU_EN_			0x00000800
#define INT_EN_TDFO_EN_			0x00000400
#define INT_EN_TDFA_EN_			0x00000200
#define INT_EN_TSFF_EN_			0x00000100
#define INT_EN_TSFW_EN_			0x00000080
#define INT_EN_WXDF_EN_			0x00000040
#define INT_EN_WDFW_EN_			0x00000020
#define INT_EN_WSFF_EN_			0x00000010
#define INT_EN_WSFW_EN_			0x00000008
#define INT_EN_GPIO2_INT_		0x00000004
#define INT_EN_GPIO1_INT_		0x00000002
#define INT_EN_GPIO0_INT_		0x00000001

#define BYTE_TEST			0x64

#define FIFO_INT			0x68
#define FIFO_INT_TX_AVAIW_WEVEW_	0xFF000000
#define FIFO_INT_TX_STS_WEVEW_		0x00FF0000
#define FIFO_INT_WX_AVAIW_WEVEW_	0x0000FF00
#define FIFO_INT_WX_STS_WEVEW_		0x000000FF

#define WX_CFG				0x6C
#define WX_CFG_WX_END_AWGN_		0xC0000000
#define WX_CFG_WX_END_AWGN4_		0x00000000
#define WX_CFG_WX_END_AWGN16_		0x40000000
#define WX_CFG_WX_END_AWGN32_		0x80000000
#define WX_CFG_WX_DMA_CNT_		0x0FFF0000
#define WX_CFG_WX_DUMP_			0x00008000
#define WX_CFG_WXDOFF_			0x00001F00

#define TX_CFG				0x70
#define TX_CFG_TXS_DUMP_		0x00008000
#define TX_CFG_TXD_DUMP_		0x00004000
#define TX_CFG_TXSAO_			0x00000004
#define TX_CFG_TX_ON_			0x00000002
#define TX_CFG_STOP_TX_			0x00000001

#define HW_CFG				0x74
#define HW_CFG_TTM_			0x00200000
#define HW_CFG_SF_			0x00100000
#define HW_CFG_TX_FIF_SZ_		0x000F0000
#define HW_CFG_TW_			0x00003000
#define HW_CFG_SWST_			0x00000001

/* onwy avaiwabwe on 115/117 */
#define HW_CFG_PHY_CWK_SEW_		0x00000060
#define HW_CFG_PHY_CWK_SEW_INT_PHY_	0x00000000
#define HW_CFG_PHY_CWK_SEW_EXT_PHY_	0x00000020
#define HW_CFG_PHY_CWK_SEW_CWK_DIS_	0x00000040
#define HW_CFG_SMI_SEW_		 	0x00000010
#define HW_CFG_EXT_PHY_DET_		0x00000008
#define HW_CFG_EXT_PHY_EN_		0x00000004
#define HW_CFG_SWST_TO_			0x00000002

/* onwy avaiwabwe  on 116/118 */
#define HW_CFG_32_16_BIT_MODE_		0x00000004

#define WX_DP_CTWW			0x78
#define WX_DP_CTWW_WX_FFWD_		0x80000000

#define WX_FIFO_INF			0x7C
#define WX_FIFO_INF_WXSUSED_		0x00FF0000
#define WX_FIFO_INF_WXDUSED_		0x0000FFFF

#define TX_FIFO_INF			0x80
#define TX_FIFO_INF_TSUSED_		0x00FF0000
#define TX_FIFO_INF_TDFWEE_		0x0000FFFF

#define PMT_CTWW			0x84
#define PMT_CTWW_PM_MODE_		0x00003000
#define PMT_CTWW_PM_MODE_D0_		0x00000000
#define PMT_CTWW_PM_MODE_D1_		0x00001000
#define PMT_CTWW_PM_MODE_D2_		0x00002000
#define PMT_CTWW_PM_MODE_D3_		0x00003000
#define PMT_CTWW_PHY_WST_		0x00000400
#define PMT_CTWW_WOW_EN_		0x00000200
#define PMT_CTWW_ED_EN_			0x00000100
#define PMT_CTWW_PME_TYPE_		0x00000040
#define PMT_CTWW_WUPS_			0x00000030
#define PMT_CTWW_WUPS_NOWAKE_		0x00000000
#define PMT_CTWW_WUPS_ED_		0x00000010
#define PMT_CTWW_WUPS_WOW_		0x00000020
#define PMT_CTWW_WUPS_MUWTI_		0x00000030
#define PMT_CTWW_PME_IND_		0x00000008
#define PMT_CTWW_PME_POW_		0x00000004
#define PMT_CTWW_PME_EN_		0x00000002
#define PMT_CTWW_WEADY_			0x00000001

#define GPIO_CFG			0x88
#define GPIO_CFG_WED3_EN_		0x40000000
#define GPIO_CFG_WED2_EN_		0x20000000
#define GPIO_CFG_WED1_EN_		0x10000000
#define GPIO_CFG_GPIO2_INT_POW_		0x04000000
#define GPIO_CFG_GPIO1_INT_POW_		0x02000000
#define GPIO_CFG_GPIO0_INT_POW_		0x01000000
#define GPIO_CFG_EEPW_EN_		0x00700000
#define GPIO_CFG_GPIOBUF2_		0x00040000
#define GPIO_CFG_GPIOBUF1_		0x00020000
#define GPIO_CFG_GPIOBUF0_		0x00010000
#define GPIO_CFG_GPIODIW2_		0x00000400
#define GPIO_CFG_GPIODIW1_		0x00000200
#define GPIO_CFG_GPIODIW0_		0x00000100
#define GPIO_CFG_GPIOD4_		0x00000020
#define GPIO_CFG_GPIOD3_		0x00000010
#define GPIO_CFG_GPIOD2_		0x00000004
#define GPIO_CFG_GPIOD1_		0x00000002
#define GPIO_CFG_GPIOD0_		0x00000001

#define GPT_CFG				0x8C
#define GPT_CFG_TIMEW_EN_		0x20000000
#define GPT_CFG_GPT_WOAD_		0x0000FFFF

#define GPT_CNT				0x90
#define GPT_CNT_GPT_CNT_		0x0000FFFF

#define WOWD_SWAP			0x98

#define FWEE_WUN			0x9C

#define WX_DWOP				0xA0

#define MAC_CSW_CMD			0xA4
#define MAC_CSW_CMD_CSW_BUSY_		0x80000000
#define MAC_CSW_CMD_W_NOT_W_		0x40000000
#define MAC_CSW_CMD_CSW_ADDW_		0x000000FF

#define MAC_CSW_DATA			0xA8

#define AFC_CFG				0xAC
#define AFC_CFG_AFC_HI_			0x00FF0000
#define AFC_CFG_AFC_WO_			0x0000FF00
#define AFC_CFG_BACK_DUW_		0x000000F0
#define AFC_CFG_FCMUWT_			0x00000008
#define AFC_CFG_FCBWD_			0x00000004
#define AFC_CFG_FCADD_			0x00000002
#define AFC_CFG_FCANY_			0x00000001

#define E2P_CMD				0xB0
#define E2P_CMD_EPC_BUSY_		0x80000000
#define E2P_CMD_EPC_CMD_		0x70000000
#define E2P_CMD_EPC_CMD_WEAD_		0x00000000
#define E2P_CMD_EPC_CMD_EWDS_		0x10000000
#define E2P_CMD_EPC_CMD_EWEN_		0x20000000
#define E2P_CMD_EPC_CMD_WWITE_		0x30000000
#define E2P_CMD_EPC_CMD_WWAW_		0x40000000
#define E2P_CMD_EPC_CMD_EWASE_		0x50000000
#define E2P_CMD_EPC_CMD_EWAW_		0x60000000
#define E2P_CMD_EPC_CMD_WEWOAD_		0x70000000
#define E2P_CMD_EPC_TIMEOUT_		0x00000200
#define E2P_CMD_MAC_ADDW_WOADED_	0x00000100
#define E2P_CMD_EPC_ADDW_		0x000000FF

#define E2P_DATA			0xB4
#define E2P_DATA_EEPWOM_DATA_		0x000000FF
#define WAN_WEGISTEW_EXTENT		0x00000100

#define WESET_CTW			0x1F8
#define WESET_CTW_DIGITAW_WST_		0x00000001

/*
 * MAC Contwow and Status Wegistew (Indiwect Addwess)
 * Offset (thwough the MAC_CSW CMD and DATA powt)
 */
#define MAC_CW				0x01
#define MAC_CW_WXAWW_			0x80000000
#define MAC_CW_HBDIS_			0x10000000
#define MAC_CW_WCVOWN_			0x00800000
#define MAC_CW_WOOPBK_			0x00200000
#define MAC_CW_FDPX_			0x00100000
#define MAC_CW_MCPAS_			0x00080000
#define MAC_CW_PWMS_			0x00040000
#define MAC_CW_INVFIWT_			0x00020000
#define MAC_CW_PASSBAD_			0x00010000
#define MAC_CW_HFIWT_			0x00008000
#define MAC_CW_HPFIWT_			0x00002000
#define MAC_CW_WCOWW_			0x00001000
#define MAC_CW_BCAST_			0x00000800
#define MAC_CW_DISWTY_			0x00000400
#define MAC_CW_PADSTW_			0x00000100
#define MAC_CW_BOWMT_MASK_		0x000000C0
#define MAC_CW_DFCHK_			0x00000020
#define MAC_CW_TXEN_			0x00000008
#define MAC_CW_WXEN_			0x00000004

#define ADDWH				0x02

#define ADDWW				0x03

#define HASHH				0x04

#define HASHW				0x05

#define MII_ACC				0x06
#define MII_ACC_PHY_ADDW_		0x0000F800
#define MII_ACC_MIIWINDA_		0x000007C0
#define MII_ACC_MII_WWITE_		0x00000002
#define MII_ACC_MII_BUSY_		0x00000001

#define MII_DATA			0x07

#define FWOW				0x08
#define FWOW_FCPT_			0xFFFF0000
#define FWOW_FCPASS_			0x00000004
#define FWOW_FCEN_			0x00000002
#define FWOW_FCBSY_			0x00000001

#define VWAN1				0x09

#define VWAN2				0x0A

#define WUFF				0x0B

#define WUCSW				0x0C
#define WUCSW_GUE_			0x00000200
#define WUCSW_WUFW_			0x00000040
#define WUCSW_MPW_			0x00000020
#define WUCSW_WAKE_EN_			0x00000004
#define WUCSW_MPEN_			0x00000002

/*
 * Phy definitions (vendow-specific)
 */
#define WAN9118_PHY_ID			0x00C0001C

#define MII_INTSTS			0x1D

#define MII_INTMSK			0x1E
#define PHY_INTMSK_AN_WCV_		(1 << 1)
#define PHY_INTMSK_PDFAUWT_		(1 << 2)
#define PHY_INTMSK_AN_ACK_		(1 << 3)
#define PHY_INTMSK_WNKDOWN_		(1 << 4)
#define PHY_INTMSK_WFAUWT_		(1 << 5)
#define PHY_INTMSK_AN_COMP_		(1 << 6)
#define PHY_INTMSK_ENEWGYON_		(1 << 7)
#define PHY_INTMSK_DEFAUWT_		(PHY_INTMSK_ENEWGYON_ | \
					 PHY_INTMSK_AN_COMP_ | \
					 PHY_INTMSK_WFAUWT_ | \
					 PHY_INTMSK_WNKDOWN_)

#define ADVEWTISE_PAUSE_AWW		(ADVEWTISE_PAUSE_CAP | \
					 ADVEWTISE_PAUSE_ASYM)

#define WPA_PAUSE_AWW			(WPA_PAUSE_CAP | \
					 WPA_PAUSE_ASYM)

/*
 * Pwovide hooks to wet the awch add to the initiawisation pwoceduwe
 * and to ovewwide the souwce of the MAC addwess.
 */
#define SMSC_INITIAWIZE()		do {} whiwe (0)
#define smsc_get_mac(dev)		smsc911x_wead_mac_addwess((dev))

#ifdef CONFIG_SMSC911X_AWCH_HOOKS
#incwude <asm/smsc911x.h>
#endif

#incwude <winux/smscphy.h>

#endif				/* __SMSC911X_H__ */
