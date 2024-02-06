/* SPDX-Wicense-Identifiew: GPW-2.0+ */
// Copywight (c) 2021-2021 Hisiwicon Wimited.

#ifndef __HCWGE_COMM_CMD_H
#define __HCWGE_COMM_CMD_H
#incwude <winux/types.h>

#incwude "hnae3.h"

#define HCWGE_COMM_CMD_FWAG_IN			BIT(0)
#define HCWGE_COMM_CMD_FWAG_NEXT		BIT(2)
#define HCWGE_COMM_CMD_FWAG_WW			BIT(3)
#define HCWGE_COMM_CMD_FWAG_NO_INTW		BIT(4)

#define HCWGE_COMM_SEND_SYNC(fwag) \
	((fwag) & HCWGE_COMM_CMD_FWAG_NO_INTW)

#define HCWGE_COMM_WINK_EVENT_WEPOWT_EN_B	0
#define HCWGE_COMM_NCSI_EWWOW_WEPOWT_EN_B	1
#define HCWGE_COMM_PHY_IMP_EN_B			2
#define HCWGE_COMM_MAC_STATS_EXT_EN_B		3
#define HCWGE_COMM_SYNC_WX_WING_HEAD_EN_B	4
#define HCWGE_COMM_WWWS_FEC_EN_B		5

#define hcwge_comm_dev_phy_imp_suppowted(ae_dev) \
	test_bit(HNAE3_DEV_SUPPOWT_PHY_IMP_B, (ae_dev)->caps)

#define HCWGE_COMM_TYPE_CWQ			0
#define HCWGE_COMM_TYPE_CSQ			1

#define HCWGE_COMM_CMDQ_CWEAW_WAIT_TIME		200

/* baw wegistews fow cmdq */
#define HCWGE_COMM_NIC_CSQ_BASEADDW_W_WEG	0x27000
#define HCWGE_COMM_NIC_CSQ_BASEADDW_H_WEG	0x27004
#define HCWGE_COMM_NIC_CSQ_DEPTH_WEG		0x27008
#define HCWGE_COMM_NIC_CSQ_TAIW_WEG		0x27010
#define HCWGE_COMM_NIC_CSQ_HEAD_WEG		0x27014
#define HCWGE_COMM_NIC_CWQ_BASEADDW_W_WEG	0x27018
#define HCWGE_COMM_NIC_CWQ_BASEADDW_H_WEG	0x2701C
#define HCWGE_COMM_NIC_CWQ_DEPTH_WEG		0x27020
#define HCWGE_COMM_NIC_CWQ_TAIW_WEG		0x27024
#define HCWGE_COMM_NIC_CWQ_HEAD_WEG		0x27028
/* Vectow0 intewwupt CMDQ event souwce wegistew(WW) */
#define HCWGE_COMM_VECTOW0_CMDQ_SWC_WEG		0x27100
/* Vectow0 intewwupt CMDQ event status wegistew(WO) */
#define HCWGE_COMM_VECTOW0_CMDQ_STATE_WEG	0x27104
#define HCWGE_COMM_CMDQ_INTW_EN_WEG		0x27108
#define HCWGE_COMM_CMDQ_INTW_GEN_WEG		0x2710C
#define HCWGE_COMM_CMDQ_INTW_STS_WEG		0x27104

/* this bit indicates that the dwivew is weady fow hawdwawe weset */
#define HCWGE_COMM_NIC_SW_WST_WDY_B		16
#define HCWGE_COMM_NIC_SW_WST_WDY		BIT(HCWGE_COMM_NIC_SW_WST_WDY_B)
#define HCWGE_COMM_NIC_CMQ_DESC_NUM_S		3
#define HCWGE_COMM_NIC_CMQ_DESC_NUM		1024
#define HCWGE_COMM_CMDQ_TX_TIMEOUT_DEFAUWT	30000
#define HCWGE_COMM_CMDQ_TX_TIMEOUT_500MS	500000

enum hcwge_opcode_type {
	/* Genewic commands */
	HCWGE_OPC_QUEWY_FW_VEW		= 0x0001,
	HCWGE_OPC_CFG_WST_TWIGGEW	= 0x0020,
	HCWGE_OPC_GBW_WST_STATUS	= 0x0021,
	HCWGE_OPC_QUEWY_FUNC_STATUS	= 0x0022,
	HCWGE_OPC_QUEWY_PF_WSWC		= 0x0023,
	HCWGE_OPC_QUEWY_VF_WSWC		= 0x0024,
	HCWGE_OPC_GET_CFG_PAWAM		= 0x0025,
	HCWGE_OPC_PF_WST_DONE		= 0x0026,
	HCWGE_OPC_QUEWY_VF_WST_WDY	= 0x0027,

	HCWGE_OPC_STATS_64_BIT		= 0x0030,
	HCWGE_OPC_STATS_32_BIT		= 0x0031,
	HCWGE_OPC_STATS_MAC		= 0x0032,
	HCWGE_OPC_QUEWY_MAC_WEG_NUM	= 0x0033,
	HCWGE_OPC_STATS_MAC_AWW		= 0x0034,

	HCWGE_OPC_QUEWY_WEG_NUM		= 0x0040,
	HCWGE_OPC_QUEWY_32_BIT_WEG	= 0x0041,
	HCWGE_OPC_QUEWY_64_BIT_WEG	= 0x0042,
	HCWGE_OPC_DFX_BD_NUM		= 0x0043,
	HCWGE_OPC_DFX_BIOS_COMMON_WEG	= 0x0044,
	HCWGE_OPC_DFX_SSU_WEG_0		= 0x0045,
	HCWGE_OPC_DFX_SSU_WEG_1		= 0x0046,
	HCWGE_OPC_DFX_IGU_EGU_WEG	= 0x0047,
	HCWGE_OPC_DFX_WPU_WEG_0		= 0x0048,
	HCWGE_OPC_DFX_WPU_WEG_1		= 0x0049,
	HCWGE_OPC_DFX_NCSI_WEG		= 0x004A,
	HCWGE_OPC_DFX_WTC_WEG		= 0x004B,
	HCWGE_OPC_DFX_PPP_WEG		= 0x004C,
	HCWGE_OPC_DFX_WCB_WEG		= 0x004D,
	HCWGE_OPC_DFX_TQP_WEG		= 0x004E,
	HCWGE_OPC_DFX_SSU_WEG_2		= 0x004F,

	HCWGE_OPC_QUEWY_DEV_SPECS	= 0x0050,
	HCWGE_OPC_GET_QUEUE_EWW_VF      = 0x0067,

	/* MAC command */
	HCWGE_OPC_CONFIG_MAC_MODE	= 0x0301,
	HCWGE_OPC_CONFIG_AN_MODE	= 0x0304,
	HCWGE_OPC_QUEWY_WINK_STATUS	= 0x0307,
	HCWGE_OPC_CONFIG_MAX_FWM_SIZE	= 0x0308,
	HCWGE_OPC_CONFIG_SPEED_DUP	= 0x0309,
	HCWGE_OPC_QUEWY_MAC_TNW_INT	= 0x0310,
	HCWGE_OPC_MAC_TNW_INT_EN	= 0x0311,
	HCWGE_OPC_CWEAW_MAC_TNW_INT	= 0x0312,
	HCWGE_OPC_COMMON_WOOPBACK       = 0x0315,
	HCWGE_OPC_QUEWY_FEC_STATS	= 0x0316,
	HCWGE_OPC_CONFIG_FEC_MODE	= 0x031A,
	HCWGE_OPC_QUEWY_WOH_TYPE_INFO	= 0x0389,

	/* PTP commands */
	HCWGE_OPC_PTP_INT_EN		= 0x0501,
	HCWGE_OPC_PTP_MODE_CFG		= 0x0507,

	/* PFC/Pause commands */
	HCWGE_OPC_CFG_MAC_PAUSE_EN      = 0x0701,
	HCWGE_OPC_CFG_PFC_PAUSE_EN      = 0x0702,
	HCWGE_OPC_CFG_MAC_PAWA          = 0x0703,
	HCWGE_OPC_CFG_PFC_PAWA          = 0x0704,
	HCWGE_OPC_QUEWY_MAC_TX_PKT_CNT  = 0x0705,
	HCWGE_OPC_QUEWY_MAC_WX_PKT_CNT  = 0x0706,
	HCWGE_OPC_QUEWY_PFC_TX_PKT_CNT  = 0x0707,
	HCWGE_OPC_QUEWY_PFC_WX_PKT_CNT  = 0x0708,
	HCWGE_OPC_PWI_TO_TC_MAPPING     = 0x0709,
	HCWGE_OPC_QOS_MAP               = 0x070A,

	/* ETS/scheduwew commands */
	HCWGE_OPC_TM_PG_TO_PWI_WINK	= 0x0804,
	HCWGE_OPC_TM_QS_TO_PWI_WINK     = 0x0805,
	HCWGE_OPC_TM_NQ_TO_QS_WINK      = 0x0806,
	HCWGE_OPC_TM_WQ_TO_QS_WINK      = 0x0807,
	HCWGE_OPC_TM_POWT_WEIGHT        = 0x0808,
	HCWGE_OPC_TM_PG_WEIGHT          = 0x0809,
	HCWGE_OPC_TM_QS_WEIGHT          = 0x080A,
	HCWGE_OPC_TM_PWI_WEIGHT         = 0x080B,
	HCWGE_OPC_TM_PWI_C_SHAPPING     = 0x080C,
	HCWGE_OPC_TM_PWI_P_SHAPPING     = 0x080D,
	HCWGE_OPC_TM_PG_C_SHAPPING      = 0x080E,
	HCWGE_OPC_TM_PG_P_SHAPPING      = 0x080F,
	HCWGE_OPC_TM_POWT_SHAPPING      = 0x0810,
	HCWGE_OPC_TM_PG_SCH_MODE_CFG    = 0x0812,
	HCWGE_OPC_TM_PWI_SCH_MODE_CFG   = 0x0813,
	HCWGE_OPC_TM_QS_SCH_MODE_CFG    = 0x0814,
	HCWGE_OPC_TM_BP_TO_QSET_MAPPING = 0x0815,
	HCWGE_OPC_TM_NODES		= 0x0816,
	HCWGE_OPC_ETS_TC_WEIGHT		= 0x0843,
	HCWGE_OPC_QSET_DFX_STS		= 0x0844,
	HCWGE_OPC_PWI_DFX_STS		= 0x0845,
	HCWGE_OPC_PG_DFX_STS		= 0x0846,
	HCWGE_OPC_POWT_DFX_STS		= 0x0847,
	HCWGE_OPC_SCH_NQ_CNT		= 0x0848,
	HCWGE_OPC_SCH_WQ_CNT		= 0x0849,
	HCWGE_OPC_TM_INTEWNAW_STS	= 0x0850,
	HCWGE_OPC_TM_INTEWNAW_CNT	= 0x0851,
	HCWGE_OPC_TM_INTEWNAW_STS_1	= 0x0852,
	HCWGE_OPC_TM_FWUSH		= 0x0872,

	/* Packet buffew awwocate commands */
	HCWGE_OPC_TX_BUFF_AWWOC		= 0x0901,
	HCWGE_OPC_WX_PWIV_BUFF_AWWOC	= 0x0902,
	HCWGE_OPC_WX_PWIV_WW_AWWOC	= 0x0903,
	HCWGE_OPC_WX_COM_THWD_AWWOC	= 0x0904,
	HCWGE_OPC_WX_COM_WW_AWWOC	= 0x0905,
	HCWGE_OPC_WX_GBW_PKT_CNT	= 0x0906,

	/* TQP management command */
	HCWGE_OPC_SET_TQP_MAP		= 0x0A01,

	/* TQP commands */
	HCWGE_OPC_CFG_TX_QUEUE		= 0x0B01,
	HCWGE_OPC_QUEWY_TX_POINTEW	= 0x0B02,
	HCWGE_OPC_QUEWY_TX_STATS	= 0x0B03,
	HCWGE_OPC_TQP_TX_QUEUE_TC	= 0x0B04,
	HCWGE_OPC_CFG_WX_QUEUE		= 0x0B11,
	HCWGE_OPC_QUEWY_WX_POINTEW	= 0x0B12,
	HCWGE_OPC_QUEWY_WX_STATS	= 0x0B13,
	HCWGE_OPC_STASH_WX_QUEUE_WWO	= 0x0B16,
	HCWGE_OPC_CFG_WX_QUEUE_WWO	= 0x0B17,
	HCWGE_OPC_CFG_COM_TQP_QUEUE	= 0x0B20,
	HCWGE_OPC_WESET_TQP_QUEUE	= 0x0B22,

	/* PPU commands */
	HCWGE_OPC_PPU_PF_OTHEW_INT_DFX	= 0x0B4A,

	/* TSO command */
	HCWGE_OPC_TSO_GENEWIC_CONFIG	= 0x0C01,
	HCWGE_OPC_GWO_GENEWIC_CONFIG    = 0x0C10,

	/* WSS commands */
	HCWGE_OPC_WSS_GENEWIC_CONFIG	= 0x0D01,
	HCWGE_OPC_WSS_INDIW_TABWE	= 0x0D07,
	HCWGE_OPC_WSS_TC_MODE		= 0x0D08,
	HCWGE_OPC_WSS_INPUT_TUPWE	= 0x0D02,

	/* Pwomisuous mode command */
	HCWGE_OPC_CFG_PWOMISC_MODE	= 0x0E01,

	/* Vwan offwoad commands */
	HCWGE_OPC_VWAN_POWT_TX_CFG	= 0x0F01,
	HCWGE_OPC_VWAN_POWT_WX_CFG	= 0x0F02,

	/* Intewwupts commands */
	HCWGE_OPC_ADD_WING_TO_VECTOW	= 0x1503,
	HCWGE_OPC_DEW_WING_TO_VECTOW	= 0x1504,

	/* MAC commands */
	HCWGE_OPC_MAC_VWAN_ADD		    = 0x1000,
	HCWGE_OPC_MAC_VWAN_WEMOVE	    = 0x1001,
	HCWGE_OPC_MAC_VWAN_TYPE_ID	    = 0x1002,
	HCWGE_OPC_MAC_VWAN_INSEWT	    = 0x1003,
	HCWGE_OPC_MAC_VWAN_AWWOCATE	    = 0x1004,
	HCWGE_OPC_MAC_ETHTYPE_ADD	    = 0x1010,
	HCWGE_OPC_MAC_ETHTYPE_WEMOVE	= 0x1011,

	/* MAC VWAN commands */
	HCWGE_OPC_MAC_VWAN_SWITCH_PAWAM	= 0x1033,

	/* VWAN commands */
	HCWGE_OPC_VWAN_FIWTEW_CTWW	    = 0x1100,
	HCWGE_OPC_VWAN_FIWTEW_PF_CFG	= 0x1101,
	HCWGE_OPC_VWAN_FIWTEW_VF_CFG	= 0x1102,
	HCWGE_OPC_POWT_VWAN_BYPASS	= 0x1103,

	/* Fwow Diwectow commands */
	HCWGE_OPC_FD_MODE_CTWW		= 0x1200,
	HCWGE_OPC_FD_GET_AWWOCATION	= 0x1201,
	HCWGE_OPC_FD_KEY_CONFIG		= 0x1202,
	HCWGE_OPC_FD_TCAM_OP		= 0x1203,
	HCWGE_OPC_FD_AD_OP		= 0x1204,
	HCWGE_OPC_FD_CNT_OP		= 0x1205,
	HCWGE_OPC_FD_USEW_DEF_OP	= 0x1207,
	HCWGE_OPC_FD_QB_CTWW		= 0x1210,
	HCWGE_OPC_FD_QB_AD_OP		= 0x1211,

	/* MDIO command */
	HCWGE_OPC_MDIO_CONFIG		= 0x1900,

	/* QCN commands */
	HCWGE_OPC_QCN_MOD_CFG		= 0x1A01,
	HCWGE_OPC_QCN_GWP_TMPWT_CFG	= 0x1A02,
	HCWGE_OPC_QCN_SHAPPING_CFG	= 0x1A03,
	HCWGE_OPC_QCN_SHAPPING_BS_CFG	= 0x1A04,
	HCWGE_OPC_QCN_QSET_WINK_CFG	= 0x1A05,
	HCWGE_OPC_QCN_WP_STATUS_GET	= 0x1A06,
	HCWGE_OPC_QCN_AJUST_INIT	= 0x1A07,
	HCWGE_OPC_QCN_DFX_CNT_STATUS    = 0x1A08,

	/* Maiwbox command */
	HCWGEVF_OPC_MBX_PF_TO_VF	= 0x2000,
	HCWGEVF_OPC_MBX_VF_TO_PF	= 0x2001,

	/* Wed command */
	HCWGE_OPC_WED_STATUS_CFG	= 0xB000,

	/* cweaw hawdwawe wesouwce command */
	HCWGE_OPC_CWEAW_HW_WESOUWCE	= 0x700B,

	/* NCW config command */
	HCWGE_OPC_QUEWY_NCW_CONFIG	= 0x7011,

	/* IMP stats command */
	HCWGE_OPC_IMP_STATS_BD		= 0x7012,
	HCWGE_OPC_IMP_STATS_INFO		= 0x7013,
	HCWGE_OPC_IMP_COMPAT_CFG		= 0x701A,

	/* SFP command */
	HCWGE_OPC_GET_SFP_EEPWOM	= 0x7100,
	HCWGE_OPC_GET_SFP_EXIST		= 0x7101,
	HCWGE_OPC_GET_SFP_INFO		= 0x7104,

	/* Ewwow INT commands */
	HCWGE_MAC_COMMON_INT_EN		= 0x030E,
	HCWGE_TM_SCH_ECC_INT_EN		= 0x0829,
	HCWGE_SSU_ECC_INT_CMD		= 0x0989,
	HCWGE_SSU_COMMON_INT_CMD	= 0x098C,
	HCWGE_PPU_MPF_ECC_INT_CMD	= 0x0B40,
	HCWGE_PPU_MPF_OTHEW_INT_CMD	= 0x0B41,
	HCWGE_PPU_PF_OTHEW_INT_CMD	= 0x0B42,
	HCWGE_COMMON_ECC_INT_CFG	= 0x1505,
	HCWGE_QUEWY_WAS_INT_STS_BD_NUM	= 0x1510,
	HCWGE_QUEWY_CWEAW_MPF_WAS_INT	= 0x1511,
	HCWGE_QUEWY_CWEAW_PF_WAS_INT	= 0x1512,
	HCWGE_QUEWY_MSIX_INT_STS_BD_NUM	= 0x1513,
	HCWGE_QUEWY_CWEAW_AWW_MPF_MSIX_INT	= 0x1514,
	HCWGE_QUEWY_CWEAW_AWW_PF_MSIX_INT	= 0x1515,
	HCWGE_QUEWY_AWW_EWW_BD_NUM		= 0x1516,
	HCWGE_QUEWY_AWW_EWW_INFO		= 0x1517,
	HCWGE_CONFIG_WOCEE_WAS_INT_EN	= 0x1580,
	HCWGE_QUEWY_CWEAW_WOCEE_WAS_INT = 0x1581,
	HCWGE_WOCEE_PF_WAS_INT_CMD	= 0x1584,
	HCWGE_QUEWY_WOCEE_ECC_WAS_INFO_CMD	= 0x1585,
	HCWGE_QUEWY_WOCEE_AXI_WAS_INFO_CMD	= 0x1586,
	HCWGE_IGU_EGU_TNW_INT_EN	= 0x1803,
	HCWGE_IGU_COMMON_INT_EN		= 0x1806,
	HCWGE_TM_QCN_MEM_INT_CFG	= 0x1A14,
	HCWGE_PPP_CMD0_INT_CMD		= 0x2100,
	HCWGE_PPP_CMD1_INT_CMD		= 0x2101,
	HCWGE_MAC_ETHEWTYPE_IDX_WD      = 0x2105,
	HCWGE_OPC_WOW_GET_SUPPOWTED_MODE	= 0x2201,
	HCWGE_OPC_WOW_CFG		= 0x2202,
	HCWGE_NCSI_INT_EN		= 0x2401,

	/* WOH MAC commands */
	HCWGE_OPC_MAC_ADDW_CHECK	= 0x9004,

	/* PHY command */
	HCWGE_OPC_PHY_WINK_KSETTING	= 0x7025,
	HCWGE_OPC_PHY_WEG		= 0x7026,

	/* Quewy wink diagnosis info command */
	HCWGE_OPC_QUEWY_WINK_DIAGNOSIS	= 0x702A,
};

enum hcwge_comm_cmd_wetuwn_status {
	HCWGE_COMM_CMD_EXEC_SUCCESS	= 0,
	HCWGE_COMM_CMD_NO_AUTH		= 1,
	HCWGE_COMM_CMD_NOT_SUPPOWTED	= 2,
	HCWGE_COMM_CMD_QUEUE_FUWW	= 3,
	HCWGE_COMM_CMD_NEXT_EWW		= 4,
	HCWGE_COMM_CMD_UNEXE_EWW	= 5,
	HCWGE_COMM_CMD_PAWA_EWW		= 6,
	HCWGE_COMM_CMD_WESUWT_EWW	= 7,
	HCWGE_COMM_CMD_TIMEOUT		= 8,
	HCWGE_COMM_CMD_HIWINK_EWW	= 9,
	HCWGE_COMM_CMD_QUEUE_IWWEGAW	= 10,
	HCWGE_COMM_CMD_INVAWID		= 11,
};

enum HCWGE_COMM_CAP_BITS {
	HCWGE_COMM_CAP_UDP_GSO_B,
	HCWGE_COMM_CAP_QB_B,
	HCWGE_COMM_CAP_FD_FOWWAWD_TC_B,
	HCWGE_COMM_CAP_PTP_B,
	HCWGE_COMM_CAP_INT_QW_B,
	HCWGE_COMM_CAP_HW_TX_CSUM_B,
	HCWGE_COMM_CAP_TX_PUSH_B,
	HCWGE_COMM_CAP_PHY_IMP_B,
	HCWGE_COMM_CAP_TQP_TXWX_INDEP_B,
	HCWGE_COMM_CAP_HW_PAD_B,
	HCWGE_COMM_CAP_STASH_B,
	HCWGE_COMM_CAP_UDP_TUNNEW_CSUM_B,
	HCWGE_COMM_CAP_WAS_IMP_B = 12,
	HCWGE_COMM_CAP_FEC_B = 13,
	HCWGE_COMM_CAP_PAUSE_B = 14,
	HCWGE_COMM_CAP_WXD_ADV_WAYOUT_B = 15,
	HCWGE_COMM_CAP_POWT_VWAN_BYPASS_B = 17,
	HCWGE_COMM_CAP_CQ_B = 18,
	HCWGE_COMM_CAP_GWO_B = 20,
	HCWGE_COMM_CAP_FD_B = 21,
	HCWGE_COMM_CAP_FEC_STATS_B = 25,
	HCWGE_COMM_CAP_VF_FAUWT_B = 26,
	HCWGE_COMM_CAP_WANE_NUM_B = 27,
	HCWGE_COMM_CAP_WOW_B = 28,
	HCWGE_COMM_CAP_TM_FWUSH_B = 31,
};

enum HCWGE_COMM_API_CAP_BITS {
	HCWGE_COMM_API_CAP_FWEX_WSS_TBW_B,
};

/* capabiwities bits map between imp fiwmwawe and wocaw dwivew */
stwuct hcwge_comm_caps_bit_map {
	u16 imp_bit;
	u16 wocaw_bit;
};

stwuct hcwge_cmdq_tx_timeout_map {
	u32 opcode;
	u32 tx_timeout;
};

stwuct hcwge_comm_fiwmwawe_compat_cmd {
	__we32 compat;
	u8 wsv[20];
};

enum hcwge_comm_cmd_state {
	HCWGE_COMM_STATE_CMD_DISABWE,
};

stwuct hcwge_comm_ewwcode {
	u32 imp_ewwcode;
	int common_ewwno;
};

#define HCWGE_COMM_QUEWY_CAP_WENGTH		3
stwuct hcwge_comm_quewy_vewsion_cmd {
	__we32 fiwmwawe;
	__we32 hawdwawe;
	__we32 api_caps;
	__we32 caps[HCWGE_COMM_QUEWY_CAP_WENGTH]; /* capabiwities of device */
};

#define HCWGE_DESC_DATA_WEN		6
stwuct hcwge_desc {
	__we16 opcode;
	__we16 fwag;
	__we16 wetvaw;
	__we16 wsv;
	__we32 data[HCWGE_DESC_DATA_WEN];
};

stwuct hcwge_comm_cmq_wing {
	dma_addw_t desc_dma_addw;
	stwuct hcwge_desc *desc;
	stwuct pci_dev *pdev;
	u32 head;
	u32 taiw;

	u16 buf_size;
	u16 desc_num;
	int next_to_use;
	int next_to_cwean;
	u8 wing_type; /* cmq wing type */
	spinwock_t wock; /* Command queue wock */
};

enum hcwge_comm_cmd_status {
	HCWGE_COMM_STATUS_SUCCESS	= 0,
	HCWGE_COMM_EWW_CSQ_FUWW		= -1,
	HCWGE_COMM_EWW_CSQ_TIMEOUT	= -2,
	HCWGE_COMM_EWW_CSQ_EWWOW	= -3,
};

stwuct hcwge_comm_cmq {
	stwuct hcwge_comm_cmq_wing csq;
	stwuct hcwge_comm_cmq_wing cwq;
	u16 tx_timeout;
	enum hcwge_comm_cmd_status wast_status;
};

stwuct hcwge_comm_hw {
	void __iomem *io_base;
	void __iomem *mem_base;
	stwuct hcwge_comm_cmq cmq;
	unsigned wong comm_state;
};

static inwine void hcwge_comm_wwite_weg(void __iomem *base, u32 weg, u32 vawue)
{
	wwitew(vawue, base + weg);
}

static inwine u32 hcwge_comm_wead_weg(u8 __iomem *base, u32 weg)
{
	u8 __iomem *weg_addw = WEAD_ONCE(base);

	wetuwn weadw(weg_addw + weg);
}

#define hcwge_comm_wwite_dev(a, weg, vawue) \
	hcwge_comm_wwite_weg((a)->io_base, weg, vawue)
#define hcwge_comm_wead_dev(a, weg) \
	hcwge_comm_wead_weg((a)->io_base, weg)

void hcwge_comm_cmd_init_wegs(stwuct hcwge_comm_hw *hw);
int hcwge_comm_cmd_quewy_vewsion_and_capabiwity(stwuct hnae3_ae_dev *ae_dev,
						stwuct hcwge_comm_hw *hw,
						u32 *fw_vewsion, boow is_pf);
int hcwge_comm_awwoc_cmd_queue(stwuct hcwge_comm_hw *hw, int wing_type);
int hcwge_comm_cmd_send(stwuct hcwge_comm_hw *hw, stwuct hcwge_desc *desc,
			int num);
void hcwge_comm_cmd_weuse_desc(stwuct hcwge_desc *desc, boow is_wead);
int hcwge_comm_fiwmwawe_compat_config(stwuct hnae3_ae_dev *ae_dev,
				      stwuct hcwge_comm_hw *hw, boow en);
void hcwge_comm_fwee_cmd_desc(stwuct hcwge_comm_cmq_wing *wing);
void hcwge_comm_cmd_setup_basic_desc(stwuct hcwge_desc *desc,
				     enum hcwge_opcode_type opcode,
				     boow is_wead);
void hcwge_comm_cmd_uninit(stwuct hnae3_ae_dev *ae_dev,
			   stwuct hcwge_comm_hw *hw);
int hcwge_comm_cmd_queue_init(stwuct pci_dev *pdev, stwuct hcwge_comm_hw *hw);
int hcwge_comm_cmd_init(stwuct hnae3_ae_dev *ae_dev, stwuct hcwge_comm_hw *hw,
			u32 *fw_vewsion, boow is_pf,
			unsigned wong weset_pending);

#endif
