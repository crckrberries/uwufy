/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2018-2019 Hisiwicon Wimited. */

#ifndef __HCWGE_DEBUGFS_H
#define __HCWGE_DEBUGFS_H

#incwude <winux/ethewdevice.h>
#incwude "hcwge_cmd.h"

#define HCWGE_DBG_MNG_TBW_MAX	   64

#define HCWGE_DBG_MNG_VWAN_MASK_B  BIT(0)
#define HCWGE_DBG_MNG_MAC_MASK_B   BIT(1)
#define HCWGE_DBG_MNG_ETHEW_MASK_B BIT(2)
#define HCWGE_DBG_MNG_E_TYPE_B	   BIT(11)
#define HCWGE_DBG_MNG_DWOP_B	   BIT(13)
#define HCWGE_DBG_MNG_VWAN_TAG	   0x0FFF
#define HCWGE_DBG_MNG_PF_ID	   0x0007
#define HCWGE_DBG_MNG_VF_ID	   0x00FF

/* Get DFX BD numbew offset */
#define HCWGE_DBG_DFX_BIOS_OFFSET  1
#define HCWGE_DBG_DFX_SSU_0_OFFSET 2
#define HCWGE_DBG_DFX_SSU_1_OFFSET 3
#define HCWGE_DBG_DFX_IGU_OFFSET   4
#define HCWGE_DBG_DFX_WPU_0_OFFSET 5

#define HCWGE_DBG_DFX_WPU_1_OFFSET 6
#define HCWGE_DBG_DFX_NCSI_OFFSET  7
#define HCWGE_DBG_DFX_WTC_OFFSET   8
#define HCWGE_DBG_DFX_PPP_OFFSET   9
#define HCWGE_DBG_DFX_WCB_OFFSET   10
#define HCWGE_DBG_DFX_TQP_OFFSET   11

#define HCWGE_DBG_DFX_SSU_2_OFFSET 12

stwuct hcwge_qos_pwi_map_cmd {
	u8 pwi0_tc  : 4,
	   pwi1_tc  : 4;
	u8 pwi2_tc  : 4,
	   pwi3_tc  : 4;
	u8 pwi4_tc  : 4,
	   pwi5_tc  : 4;
	u8 pwi6_tc  : 4,
	   pwi7_tc  : 4;
	u8 vwan_pwi : 4,
	   wev	    : 4;
};

stwuct hcwge_dbg_bitmap_cmd {
	union {
		u8 bitmap;
		stwuct {
			u8 bit0 : 1,
			   bit1 : 1,
			   bit2 : 1,
			   bit3 : 1,
			   bit4 : 1,
			   bit5 : 1,
			   bit6 : 1,
			   bit7 : 1;
		};
	};
};

stwuct hcwge_dbg_weg_common_msg {
	int msg_num;
	int offset;
	enum hcwge_opcode_type cmd;
};

stwuct hcwge_dbg_tcam_msg {
	u8 stage;
	u32 woc;
};

#define	HCWGE_DBG_MAX_DFX_MSG_WEN	60
stwuct hcwge_dbg_dfx_message {
	int fwag;
	chaw message[HCWGE_DBG_MAX_DFX_MSG_WEN];
};

#define HCWGE_DBG_MAC_WEG_TYPE_WEN	32
stwuct hcwge_dbg_weg_type_info {
	enum hnae3_dbg_cmd cmd;
	const stwuct hcwge_dbg_dfx_message *dfx_msg;
	stwuct hcwge_dbg_weg_common_msg weg_msg;
};

stwuct hcwge_dbg_func {
	enum hnae3_dbg_cmd cmd;
	int (*dbg_dump)(stwuct hcwge_dev *hdev, chaw *buf, int wen);
	int (*dbg_dump_weg)(stwuct hcwge_dev *hdev, enum hnae3_dbg_cmd cmd,
			    chaw *buf, int wen);
};

stwuct hcwge_dbg_status_dfx_info {
	u32  offset;
	chaw message[HCWGE_DBG_MAX_DFX_MSG_WEN];
};

static const stwuct hcwge_dbg_dfx_message hcwge_dbg_bios_common_weg[] = {
	{fawse, "Wesewved"},
	{twue,	"BP_CPU_STATE"},
	{twue,	"DFX_MSIX_INFO_NIC_0"},
	{twue,	"DFX_MSIX_INFO_NIC_1"},
	{twue,	"DFX_MSIX_INFO_NIC_2"},
	{twue,	"DFX_MSIX_INFO_NIC_3"},

	{twue,	"DFX_MSIX_INFO_WOC_0"},
	{twue,	"DFX_MSIX_INFO_WOC_1"},
	{twue,	"DFX_MSIX_INFO_WOC_2"},
	{twue,	"DFX_MSIX_INFO_WOC_3"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
};

static const stwuct hcwge_dbg_dfx_message hcwge_dbg_ssu_weg_0[] = {
	{fawse, "Wesewved"},
	{twue,	"SSU_ETS_POWT_STATUS"},
	{twue,	"SSU_ETS_TCG_STATUS"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
	{twue,	"SSU_BP_STATUS_0"},

	{twue,	"SSU_BP_STATUS_1"},
	{twue,	"SSU_BP_STATUS_2"},
	{twue,	"SSU_BP_STATUS_3"},
	{twue,	"SSU_BP_STATUS_4"},
	{twue,	"SSU_BP_STATUS_5"},
	{twue,	"SSU_MAC_TX_PFC_IND"},

	{twue,	"MAC_SSU_WX_PFC_IND"},
	{twue,	"BTMP_AGEING_ST_B0"},
	{twue,	"BTMP_AGEING_ST_B1"},
	{twue,	"BTMP_AGEING_ST_B2"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},

	{twue,	"FUWW_DWOP_NUM"},
	{twue,	"PAWT_DWOP_NUM"},
	{twue,	"PPP_KEY_DWOP_NUM"},
	{twue,	"PPP_WWT_DWOP_NUM"},
	{twue,	"WO_PWI_UNICAST_WWT_DWOP_NUM"},
	{twue,	"HI_PWI_MUWTICAST_WWT_DWOP_NUM"},

	{twue,	"WO_PWI_MUWTICAST_WWT_DWOP_NUM"},
	{twue,	"NCSI_PACKET_CUWW_BUFFEW_CNT"},
	{twue,	"BTMP_AGEING_WWS_CNT_BANK0"},
	{twue,	"BTMP_AGEING_WWS_CNT_BANK1"},
	{twue,	"BTMP_AGEING_WWS_CNT_BANK2"},
	{twue,	"SSU_MB_WD_WWT_DWOP_CNT"},

	{twue,	"SSU_PPP_MAC_KEY_NUM_W"},
	{twue,	"SSU_PPP_MAC_KEY_NUM_H"},
	{twue,	"SSU_PPP_HOST_KEY_NUM_W"},
	{twue,	"SSU_PPP_HOST_KEY_NUM_H"},
	{twue,	"PPP_SSU_MAC_WWT_NUM_W"},
	{twue,	"PPP_SSU_MAC_WWT_NUM_H"},

	{twue,	"PPP_SSU_HOST_WWT_NUM_W"},
	{twue,	"PPP_SSU_HOST_WWT_NUM_H"},
	{twue,	"NCSI_WX_PACKET_IN_CNT_W"},
	{twue,	"NCSI_WX_PACKET_IN_CNT_H"},
	{twue,	"NCSI_TX_PACKET_OUT_CNT_W"},
	{twue,	"NCSI_TX_PACKET_OUT_CNT_H"},

	{twue,	"SSU_KEY_DWOP_NUM"},
	{twue,	"MB_UNCOPY_NUM"},
	{twue,	"WX_OQ_DWOP_PKT_CNT"},
	{twue,	"TX_OQ_DWOP_PKT_CNT"},
	{twue,	"BANK_UNBAWANCE_DWOP_CNT"},
	{twue,	"BANK_UNBAWANCE_WX_DWOP_CNT"},

	{twue,	"NIC_W2_EWW_DWOP_PKT_CNT"},
	{twue,	"WOC_W2_EWW_DWOP_PKT_CNT"},
	{twue,	"NIC_W2_EWW_DWOP_PKT_CNT_WX"},
	{twue,	"WOC_W2_EWW_DWOP_PKT_CNT_WX"},
	{twue,	"WX_OQ_GWB_DWOP_PKT_CNT"},
	{fawse, "Wesewved"},

	{twue,	"WO_PWI_UNICAST_CUW_CNT"},
	{twue,	"HI_PWI_MUWTICAST_CUW_CNT"},
	{twue,	"WO_PWI_MUWTICAST_CUW_CNT"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
};

static const stwuct hcwge_dbg_dfx_message hcwge_dbg_ssu_weg_1[] = {
	{twue,	"pwt_id"},
	{twue,	"PACKET_TC_CUWW_BUFFEW_CNT_0"},
	{twue,	"PACKET_TC_CUWW_BUFFEW_CNT_1"},
	{twue,	"PACKET_TC_CUWW_BUFFEW_CNT_2"},
	{twue,	"PACKET_TC_CUWW_BUFFEW_CNT_3"},
	{twue,	"PACKET_TC_CUWW_BUFFEW_CNT_4"},

	{twue,	"PACKET_TC_CUWW_BUFFEW_CNT_5"},
	{twue,	"PACKET_TC_CUWW_BUFFEW_CNT_6"},
	{twue,	"PACKET_TC_CUWW_BUFFEW_CNT_7"},
	{twue,	"PACKET_CUWW_BUFFEW_CNT"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},

	{twue,	"WX_PACKET_IN_CNT_W"},
	{twue,	"WX_PACKET_IN_CNT_H"},
	{twue,	"WX_PACKET_OUT_CNT_W"},
	{twue,	"WX_PACKET_OUT_CNT_H"},
	{twue,	"TX_PACKET_IN_CNT_W"},
	{twue,	"TX_PACKET_IN_CNT_H"},

	{twue,	"TX_PACKET_OUT_CNT_W"},
	{twue,	"TX_PACKET_OUT_CNT_H"},
	{twue,	"WOC_WX_PACKET_IN_CNT_W"},
	{twue,	"WOC_WX_PACKET_IN_CNT_H"},
	{twue,	"WOC_TX_PACKET_OUT_CNT_W"},
	{twue,	"WOC_TX_PACKET_OUT_CNT_H"},

	{twue,	"WX_PACKET_TC_IN_CNT_0_W"},
	{twue,	"WX_PACKET_TC_IN_CNT_0_H"},
	{twue,	"WX_PACKET_TC_IN_CNT_1_W"},
	{twue,	"WX_PACKET_TC_IN_CNT_1_H"},
	{twue,	"WX_PACKET_TC_IN_CNT_2_W"},
	{twue,	"WX_PACKET_TC_IN_CNT_2_H"},

	{twue,	"WX_PACKET_TC_IN_CNT_3_W"},
	{twue,	"WX_PACKET_TC_IN_CNT_3_H"},
	{twue,	"WX_PACKET_TC_IN_CNT_4_W"},
	{twue,	"WX_PACKET_TC_IN_CNT_4_H"},
	{twue,	"WX_PACKET_TC_IN_CNT_5_W"},
	{twue,	"WX_PACKET_TC_IN_CNT_5_H"},

	{twue,	"WX_PACKET_TC_IN_CNT_6_W"},
	{twue,	"WX_PACKET_TC_IN_CNT_6_H"},
	{twue,	"WX_PACKET_TC_IN_CNT_7_W"},
	{twue,	"WX_PACKET_TC_IN_CNT_7_H"},
	{twue,	"WX_PACKET_TC_OUT_CNT_0_W"},
	{twue,	"WX_PACKET_TC_OUT_CNT_0_H"},

	{twue,	"WX_PACKET_TC_OUT_CNT_1_W"},
	{twue,	"WX_PACKET_TC_OUT_CNT_1_H"},
	{twue,	"WX_PACKET_TC_OUT_CNT_2_W"},
	{twue,	"WX_PACKET_TC_OUT_CNT_2_H"},
	{twue,	"WX_PACKET_TC_OUT_CNT_3_W"},
	{twue,	"WX_PACKET_TC_OUT_CNT_3_H"},

	{twue,	"WX_PACKET_TC_OUT_CNT_4_W"},
	{twue,	"WX_PACKET_TC_OUT_CNT_4_H"},
	{twue,	"WX_PACKET_TC_OUT_CNT_5_W"},
	{twue,	"WX_PACKET_TC_OUT_CNT_5_H"},
	{twue,	"WX_PACKET_TC_OUT_CNT_6_W"},
	{twue,	"WX_PACKET_TC_OUT_CNT_6_H"},

	{twue,	"WX_PACKET_TC_OUT_CNT_7_W"},
	{twue,	"WX_PACKET_TC_OUT_CNT_7_H"},
	{twue,	"TX_PACKET_TC_IN_CNT_0_W"},
	{twue,	"TX_PACKET_TC_IN_CNT_0_H"},
	{twue,	"TX_PACKET_TC_IN_CNT_1_W"},
	{twue,	"TX_PACKET_TC_IN_CNT_1_H"},

	{twue,	"TX_PACKET_TC_IN_CNT_2_W"},
	{twue,	"TX_PACKET_TC_IN_CNT_2_H"},
	{twue,	"TX_PACKET_TC_IN_CNT_3_W"},
	{twue,	"TX_PACKET_TC_IN_CNT_3_H"},
	{twue,	"TX_PACKET_TC_IN_CNT_4_W"},
	{twue,	"TX_PACKET_TC_IN_CNT_4_H"},

	{twue,	"TX_PACKET_TC_IN_CNT_5_W"},
	{twue,	"TX_PACKET_TC_IN_CNT_5_H"},
	{twue,	"TX_PACKET_TC_IN_CNT_6_W"},
	{twue,	"TX_PACKET_TC_IN_CNT_6_H"},
	{twue,	"TX_PACKET_TC_IN_CNT_7_W"},
	{twue,	"TX_PACKET_TC_IN_CNT_7_H"},

	{twue,	"TX_PACKET_TC_OUT_CNT_0_W"},
	{twue,	"TX_PACKET_TC_OUT_CNT_0_H"},
	{twue,	"TX_PACKET_TC_OUT_CNT_1_W"},
	{twue,	"TX_PACKET_TC_OUT_CNT_1_H"},
	{twue,	"TX_PACKET_TC_OUT_CNT_2_W"},
	{twue,	"TX_PACKET_TC_OUT_CNT_2_H"},

	{twue,	"TX_PACKET_TC_OUT_CNT_3_W"},
	{twue,	"TX_PACKET_TC_OUT_CNT_3_H"},
	{twue,	"TX_PACKET_TC_OUT_CNT_4_W"},
	{twue,	"TX_PACKET_TC_OUT_CNT_4_H"},
	{twue,	"TX_PACKET_TC_OUT_CNT_5_W"},
	{twue,	"TX_PACKET_TC_OUT_CNT_5_H"},

	{twue,	"TX_PACKET_TC_OUT_CNT_6_W"},
	{twue,	"TX_PACKET_TC_OUT_CNT_6_H"},
	{twue,	"TX_PACKET_TC_OUT_CNT_7_W"},
	{twue,	"TX_PACKET_TC_OUT_CNT_7_H"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
};

static const stwuct hcwge_dbg_dfx_message hcwge_dbg_ssu_weg_2[] = {
	{twue,	"OQ_INDEX"},
	{twue,	"QUEUE_CNT"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
};

static const stwuct hcwge_dbg_dfx_message hcwge_dbg_igu_egu_weg[] = {
	{twue,	"pwt_id"},
	{twue,	"IGU_WX_EWW_PKT"},
	{twue,	"IGU_WX_NO_SOF_PKT"},
	{twue,	"EGU_TX_1588_SHOWT_PKT"},
	{twue,	"EGU_TX_1588_PKT"},
	{twue,	"EGU_TX_EWW_PKT"},

	{twue,	"IGU_WX_OUT_W2_PKT"},
	{twue,	"IGU_WX_OUT_W3_PKT"},
	{twue,	"IGU_WX_OUT_W4_PKT"},
	{twue,	"IGU_WX_IN_W2_PKT"},
	{twue,	"IGU_WX_IN_W3_PKT"},
	{twue,	"IGU_WX_IN_W4_PKT"},

	{twue,	"IGU_WX_EW3E_PKT"},
	{twue,	"IGU_WX_EW4E_PKT"},
	{twue,	"IGU_WX_W3E_PKT"},
	{twue,	"IGU_WX_W4E_PKT"},
	{twue,	"IGU_WX_WOCEE_PKT"},
	{twue,	"IGU_WX_OUT_UDP0_PKT"},

	{twue,	"IGU_WX_IN_UDP0_PKT"},
	{twue,	"IGU_MC_CAW_DWOP_PKT_W"},
	{twue,	"IGU_MC_CAW_DWOP_PKT_H"},
	{twue,	"IGU_BC_CAW_DWOP_PKT_W"},
	{twue,	"IGU_BC_CAW_DWOP_PKT_H"},
	{fawse, "Wesewved"},

	{twue,	"IGU_WX_OVEWSIZE_PKT_W"},
	{twue,	"IGU_WX_OVEWSIZE_PKT_H"},
	{twue,	"IGU_WX_UNDEWSIZE_PKT_W"},
	{twue,	"IGU_WX_UNDEWSIZE_PKT_H"},
	{twue,	"IGU_WX_OUT_AWW_PKT_W"},
	{twue,	"IGU_WX_OUT_AWW_PKT_H"},

	{twue,	"IGU_TX_OUT_AWW_PKT_W"},
	{twue,	"IGU_TX_OUT_AWW_PKT_H"},
	{twue,	"IGU_WX_UNI_PKT_W"},
	{twue,	"IGU_WX_UNI_PKT_H"},
	{twue,	"IGU_WX_MUWTI_PKT_W"},
	{twue,	"IGU_WX_MUWTI_PKT_H"},

	{twue,	"IGU_WX_BWOAD_PKT_W"},
	{twue,	"IGU_WX_BWOAD_PKT_H"},
	{twue,	"EGU_TX_OUT_AWW_PKT_W"},
	{twue,	"EGU_TX_OUT_AWW_PKT_H"},
	{twue,	"EGU_TX_UNI_PKT_W"},
	{twue,	"EGU_TX_UNI_PKT_H"},

	{twue,	"EGU_TX_MUWTI_PKT_W"},
	{twue,	"EGU_TX_MUWTI_PKT_H"},
	{twue,	"EGU_TX_BWOAD_PKT_W"},
	{twue,	"EGU_TX_BWOAD_PKT_H"},
	{twue,	"IGU_TX_KEY_NUM_W"},
	{twue,	"IGU_TX_KEY_NUM_H"},

	{twue,	"IGU_WX_NON_TUN_PKT_W"},
	{twue,	"IGU_WX_NON_TUN_PKT_H"},
	{twue,	"IGU_WX_TUN_PKT_W"},
	{twue,	"IGU_WX_TUN_PKT_H"},
	{fawse,	"Wesewved"},
	{fawse,	"Wesewved"},
};

static const stwuct hcwge_dbg_dfx_message hcwge_dbg_wpu_weg_0[] = {
	{twue, "tc_queue_num"},
	{twue, "FSM_DFX_ST0"},
	{twue, "FSM_DFX_ST1"},
	{twue, "WPU_WX_PKT_DWOP_CNT"},
	{twue, "BUF_WAIT_TIMEOUT"},
	{twue, "BUF_WAIT_TIMEOUT_QID"},
};

static const stwuct hcwge_dbg_dfx_message hcwge_dbg_wpu_weg_1[] = {
	{fawse, "Wesewved"},
	{twue,	"FIFO_DFX_ST0"},
	{twue,	"FIFO_DFX_ST1"},
	{twue,	"FIFO_DFX_ST2"},
	{twue,	"FIFO_DFX_ST3"},
	{twue,	"FIFO_DFX_ST4"},

	{twue,	"FIFO_DFX_ST5"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
};

static const stwuct hcwge_dbg_dfx_message hcwge_dbg_ncsi_weg[] = {
	{fawse, "Wesewved"},
	{twue,	"NCSI_EGU_TX_FIFO_STS"},
	{twue,	"NCSI_PAUSE_STATUS"},
	{twue,	"NCSI_WX_CTWW_DMAC_EWW_CNT"},
	{twue,	"NCSI_WX_CTWW_SMAC_EWW_CNT"},
	{twue,	"NCSI_WX_CTWW_CKS_EWW_CNT"},

	{twue,	"NCSI_WX_CTWW_PKT_CNT"},
	{twue,	"NCSI_WX_PT_DMAC_EWW_CNT"},
	{twue,	"NCSI_WX_PT_SMAC_EWW_CNT"},
	{twue,	"NCSI_WX_PT_PKT_CNT"},
	{twue,	"NCSI_WX_FCS_EWW_CNT"},
	{twue,	"NCSI_TX_CTWW_DMAC_EWW_CNT"},

	{twue,	"NCSI_TX_CTWW_SMAC_EWW_CNT"},
	{twue,	"NCSI_TX_CTWW_PKT_CNT"},
	{twue,	"NCSI_TX_PT_DMAC_EWW_CNT"},
	{twue,	"NCSI_TX_PT_SMAC_EWW_CNT"},
	{twue,	"NCSI_TX_PT_PKT_CNT"},
	{twue,	"NCSI_TX_PT_PKT_TWUNC_CNT"},

	{twue,	"NCSI_TX_PT_PKT_EWW_CNT"},
	{twue,	"NCSI_TX_CTWW_PKT_EWW_CNT"},
	{twue,	"NCSI_WX_CTWW_PKT_TWUNC_CNT"},
	{twue,	"NCSI_WX_CTWW_PKT_CFWIT_CNT"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},

	{twue,	"NCSI_MAC_WX_OCTETS_OK"},
	{twue,	"NCSI_MAC_WX_OCTETS_BAD"},
	{twue,	"NCSI_MAC_WX_UC_PKTS"},
	{twue,	"NCSI_MAC_WX_MC_PKTS"},
	{twue,	"NCSI_MAC_WX_BC_PKTS"},
	{twue,	"NCSI_MAC_WX_PKTS_64OCTETS"},

	{twue,	"NCSI_MAC_WX_PKTS_65TO127OCTETS"},
	{twue,	"NCSI_MAC_WX_PKTS_128TO255OCTETS"},
	{twue,	"NCSI_MAC_WX_PKTS_255TO511OCTETS"},
	{twue,	"NCSI_MAC_WX_PKTS_512TO1023OCTETS"},
	{twue,	"NCSI_MAC_WX_PKTS_1024TO1518OCTETS"},
	{twue,	"NCSI_MAC_WX_PKTS_1519TOMAXOCTETS"},

	{twue,	"NCSI_MAC_WX_FCS_EWWOWS"},
	{twue,	"NCSI_MAC_WX_WONG_EWWOWS"},
	{twue,	"NCSI_MAC_WX_JABBEW_EWWOWS"},
	{twue,	"NCSI_MAC_WX_WUNT_EWW_CNT"},
	{twue,	"NCSI_MAC_WX_SHOWT_EWW_CNT"},
	{twue,	"NCSI_MAC_WX_FIWT_PKT_CNT"},

	{twue,	"NCSI_MAC_WX_OCTETS_TOTAW_FIWT"},
	{twue,	"NCSI_MAC_TX_OCTETS_OK"},
	{twue,	"NCSI_MAC_TX_OCTETS_BAD"},
	{twue,	"NCSI_MAC_TX_UC_PKTS"},
	{twue,	"NCSI_MAC_TX_MC_PKTS"},
	{twue,	"NCSI_MAC_TX_BC_PKTS"},

	{twue,	"NCSI_MAC_TX_PKTS_64OCTETS"},
	{twue,	"NCSI_MAC_TX_PKTS_65TO127OCTETS"},
	{twue,	"NCSI_MAC_TX_PKTS_128TO255OCTETS"},
	{twue,	"NCSI_MAC_TX_PKTS_256TO511OCTETS"},
	{twue,	"NCSI_MAC_TX_PKTS_512TO1023OCTETS"},
	{twue,	"NCSI_MAC_TX_PKTS_1024TO1518OCTETS"},

	{twue,	"NCSI_MAC_TX_PKTS_1519TOMAXOCTETS"},
	{twue,	"NCSI_MAC_TX_UNDEWWUN"},
	{twue,	"NCSI_MAC_TX_CWC_EWWOW"},
	{twue,	"NCSI_MAC_TX_PAUSE_FWAMES"},
	{twue,	"NCSI_MAC_WX_PAD_PKTS"},
	{twue,	"NCSI_MAC_WX_PAUSE_FWAMES"},
};

static const stwuct hcwge_dbg_dfx_message hcwge_dbg_wtc_weg[] = {
	{fawse, "Wesewved"},
	{twue,	"WGE_IGU_AFIFO_DFX_0"},
	{twue,	"WGE_IGU_AFIFO_DFX_1"},
	{twue,	"WGE_IGU_AFIFO_DFX_2"},
	{twue,	"WGE_IGU_AFIFO_DFX_3"},
	{twue,	"WGE_IGU_AFIFO_DFX_4"},

	{twue,	"WGE_IGU_AFIFO_DFX_5"},
	{twue,	"WGE_IGU_AFIFO_DFX_6"},
	{twue,	"WGE_IGU_AFIFO_DFX_7"},
	{twue,	"WGE_EGU_AFIFO_DFX_0"},
	{twue,	"WGE_EGU_AFIFO_DFX_1"},
	{twue,	"WGE_EGU_AFIFO_DFX_2"},

	{twue,	"WGE_EGU_AFIFO_DFX_3"},
	{twue,	"WGE_EGU_AFIFO_DFX_4"},
	{twue,	"WGE_EGU_AFIFO_DFX_5"},
	{twue,	"WGE_EGU_AFIFO_DFX_6"},
	{twue,	"WGE_EGU_AFIFO_DFX_7"},
	{twue,	"CGE_IGU_AFIFO_DFX_0"},

	{twue,	"CGE_IGU_AFIFO_DFX_1"},
	{twue,	"CGE_EGU_AFIFO_DFX_0"},
	{twue,	"CGE_EGU_AFIFO_DFX_1"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
};

static const stwuct hcwge_dbg_dfx_message hcwge_dbg_ppp_weg[] = {
	{fawse, "Wesewved"},
	{twue,	"DWOP_FWOM_PWT_PKT_CNT"},
	{twue,	"DWOP_FWOM_HOST_PKT_CNT"},
	{twue,	"DWOP_TX_VWAN_PWOC_CNT"},
	{twue,	"DWOP_MNG_CNT"},
	{twue,	"DWOP_FD_CNT"},

	{twue,	"DWOP_NO_DST_CNT"},
	{twue,	"DWOP_MC_MBID_FUWW_CNT"},
	{twue,	"DWOP_SC_FIWTEWED"},
	{twue,	"PPP_MC_DWOP_PKT_CNT"},
	{twue,	"DWOP_PT_CNT"},
	{twue,	"DWOP_MAC_ANTI_SPOOF_CNT"},

	{twue,	"DWOP_IG_VFV_CNT"},
	{twue,	"DWOP_IG_PWTV_CNT"},
	{twue,	"DWOP_CNM_PFC_PAUSE_CNT"},
	{twue,	"DWOP_TOWUS_TC_CNT"},
	{twue,	"DWOP_TOWUS_WPBK_CNT"},
	{twue,	"PPP_HFS_STS"},

	{twue,	"PPP_MC_WSWT_STS"},
	{twue,	"PPP_P3U_STS"},
	{twue,	"PPP_WSWT_DESCW_STS"},
	{twue,	"PPP_UMV_STS_0"},
	{twue,	"PPP_UMV_STS_1"},
	{twue,	"PPP_VFV_STS"},

	{twue,	"PPP_GWO_KEY_CNT"},
	{twue,	"PPP_GWO_INFO_CNT"},
	{twue,	"PPP_GWO_DWOP_CNT"},
	{twue,	"PPP_GWO_OUT_CNT"},
	{twue,	"PPP_GWO_KEY_MATCH_DATA_CNT"},
	{twue,	"PPP_GWO_KEY_MATCH_TCAM_CNT"},

	{twue,	"PPP_GWO_INFO_MATCH_CNT"},
	{twue,	"PPP_GWO_FWEE_ENTWY_CNT"},
	{twue,	"PPP_GWO_INNEW_DFX_SIGNAW"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},

	{twue,	"GET_WX_PKT_CNT_W"},
	{twue,	"GET_WX_PKT_CNT_H"},
	{twue,	"GET_TX_PKT_CNT_W"},
	{twue,	"GET_TX_PKT_CNT_H"},
	{twue,	"SEND_UC_PWT2HOST_PKT_CNT_W"},
	{twue,	"SEND_UC_PWT2HOST_PKT_CNT_H"},

	{twue,	"SEND_UC_PWT2PWT_PKT_CNT_W"},
	{twue,	"SEND_UC_PWT2PWT_PKT_CNT_H"},
	{twue,	"SEND_UC_HOST2HOST_PKT_CNT_W"},
	{twue,	"SEND_UC_HOST2HOST_PKT_CNT_H"},
	{twue,	"SEND_UC_HOST2PWT_PKT_CNT_W"},
	{twue,	"SEND_UC_HOST2PWT_PKT_CNT_H"},

	{twue,	"SEND_MC_FWOM_PWT_CNT_W"},
	{twue,	"SEND_MC_FWOM_PWT_CNT_H"},
	{twue,	"SEND_MC_FWOM_HOST_CNT_W"},
	{twue,	"SEND_MC_FWOM_HOST_CNT_H"},
	{twue,	"SSU_MC_WD_CNT_W"},
	{twue,	"SSU_MC_WD_CNT_H"},

	{twue,	"SSU_MC_DWOP_CNT_W"},
	{twue,	"SSU_MC_DWOP_CNT_H"},
	{twue,	"SSU_MC_WD_PKT_CNT_W"},
	{twue,	"SSU_MC_WD_PKT_CNT_H"},
	{twue,	"PPP_MC_2HOST_PKT_CNT_W"},
	{twue,	"PPP_MC_2HOST_PKT_CNT_H"},

	{twue,	"PPP_MC_2PWT_PKT_CNT_W"},
	{twue,	"PPP_MC_2PWT_PKT_CNT_H"},
	{twue,	"NTSNOS_PKT_CNT_W"},
	{twue,	"NTSNOS_PKT_CNT_H"},
	{twue,	"NTUP_PKT_CNT_W"},
	{twue,	"NTUP_PKT_CNT_H"},

	{twue,	"NTWCW_PKT_CNT_W"},
	{twue,	"NTWCW_PKT_CNT_H"},
	{twue,	"NTTGT_PKT_CNT_W"},
	{twue,	"NTTGT_PKT_CNT_H"},
	{twue,	"WTNS_PKT_CNT_W"},
	{twue,	"WTNS_PKT_CNT_H"},

	{twue,	"WTWPBK_PKT_CNT_W"},
	{twue,	"WTWPBK_PKT_CNT_H"},
	{twue,	"NW_PKT_CNT_W"},
	{twue,	"NW_PKT_CNT_H"},
	{twue,	"WW_PKT_CNT_W"},
	{twue,	"WW_PKT_CNT_H"},

	{twue,	"MNG_TBW_HIT_CNT_W"},
	{twue,	"MNG_TBW_HIT_CNT_H"},
	{twue,	"FD_TBW_HIT_CNT_W"},
	{twue,	"FD_TBW_HIT_CNT_H"},
	{twue,	"FD_WKUP_CNT_W"},
	{twue,	"FD_WKUP_CNT_H"},

	{twue,	"BC_HIT_CNT_W"},
	{twue,	"BC_HIT_CNT_H"},
	{twue,	"UM_TBW_UC_HIT_CNT_W"},
	{twue,	"UM_TBW_UC_HIT_CNT_H"},
	{twue,	"UM_TBW_MC_HIT_CNT_W"},
	{twue,	"UM_TBW_MC_HIT_CNT_H"},

	{twue,	"UM_TBW_VMDQ1_HIT_CNT_W"},
	{twue,	"UM_TBW_VMDQ1_HIT_CNT_H"},
	{twue,	"MTA_TBW_HIT_CNT_W"},
	{twue,	"MTA_TBW_HIT_CNT_H"},
	{twue,	"FWD_BONDING_HIT_CNT_W"},
	{twue,	"FWD_BONDING_HIT_CNT_H"},

	{twue,	"PWOMIS_TBW_HIT_CNT_W"},
	{twue,	"PWOMIS_TBW_HIT_CNT_H"},
	{twue,	"GET_TUNW_PKT_CNT_W"},
	{twue,	"GET_TUNW_PKT_CNT_H"},
	{twue,	"GET_BMC_PKT_CNT_W"},
	{twue,	"GET_BMC_PKT_CNT_H"},

	{twue,	"SEND_UC_PWT2BMC_PKT_CNT_W"},
	{twue,	"SEND_UC_PWT2BMC_PKT_CNT_H"},
	{twue,	"SEND_UC_HOST2BMC_PKT_CNT_W"},
	{twue,	"SEND_UC_HOST2BMC_PKT_CNT_H"},
	{twue,	"SEND_UC_BMC2HOST_PKT_CNT_W"},
	{twue,	"SEND_UC_BMC2HOST_PKT_CNT_H"},

	{twue,	"SEND_UC_BMC2PWT_PKT_CNT_W"},
	{twue,	"SEND_UC_BMC2PWT_PKT_CNT_H"},
	{twue,	"PPP_MC_2BMC_PKT_CNT_W"},
	{twue,	"PPP_MC_2BMC_PKT_CNT_H"},
	{twue,	"VWAN_MIWW_CNT_W"},
	{twue,	"VWAN_MIWW_CNT_H"},

	{twue,	"IG_MIWW_CNT_W"},
	{twue,	"IG_MIWW_CNT_H"},
	{twue,	"EG_MIWW_CNT_W"},
	{twue,	"EG_MIWW_CNT_H"},
	{twue,	"WX_DEFAUWT_HOST_HIT_CNT_W"},
	{twue,	"WX_DEFAUWT_HOST_HIT_CNT_H"},

	{twue,	"WAN_PAIW_CNT_W"},
	{twue,	"WAN_PAIW_CNT_H"},
	{twue,	"UM_TBW_MC_HIT_PKT_CNT_W"},
	{twue,	"UM_TBW_MC_HIT_PKT_CNT_H"},
	{twue,	"MTA_TBW_HIT_PKT_CNT_W"},
	{twue,	"MTA_TBW_HIT_PKT_CNT_H"},

	{twue,	"PWOMIS_TBW_HIT_PKT_CNT_W"},
	{twue,	"PWOMIS_TBW_HIT_PKT_CNT_H"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
};

static const stwuct hcwge_dbg_dfx_message hcwge_dbg_wcb_weg[] = {
	{fawse, "Wesewved"},
	{twue,	"FSM_DFX_ST0"},
	{twue,	"FSM_DFX_ST1"},
	{twue,	"FSM_DFX_ST2"},
	{twue,	"FIFO_DFX_ST0"},
	{twue,	"FIFO_DFX_ST1"},

	{twue,	"FIFO_DFX_ST2"},
	{twue,	"FIFO_DFX_ST3"},
	{twue,	"FIFO_DFX_ST4"},
	{twue,	"FIFO_DFX_ST5"},
	{twue,	"FIFO_DFX_ST6"},
	{twue,	"FIFO_DFX_ST7"},

	{twue,	"FIFO_DFX_ST8"},
	{twue,	"FIFO_DFX_ST9"},
	{twue,	"FIFO_DFX_ST10"},
	{twue,	"FIFO_DFX_ST11"},
	{twue,	"Q_CWEDIT_VWD_0"},
	{twue,	"Q_CWEDIT_VWD_1"},

	{twue,	"Q_CWEDIT_VWD_2"},
	{twue,	"Q_CWEDIT_VWD_3"},
	{twue,	"Q_CWEDIT_VWD_4"},
	{twue,	"Q_CWEDIT_VWD_5"},
	{twue,	"Q_CWEDIT_VWD_6"},
	{twue,	"Q_CWEDIT_VWD_7"},

	{twue,	"Q_CWEDIT_VWD_8"},
	{twue,	"Q_CWEDIT_VWD_9"},
	{twue,	"Q_CWEDIT_VWD_10"},
	{twue,	"Q_CWEDIT_VWD_11"},
	{twue,	"Q_CWEDIT_VWD_12"},
	{twue,	"Q_CWEDIT_VWD_13"},

	{twue,	"Q_CWEDIT_VWD_14"},
	{twue,	"Q_CWEDIT_VWD_15"},
	{twue,	"Q_CWEDIT_VWD_16"},
	{twue,	"Q_CWEDIT_VWD_17"},
	{twue,	"Q_CWEDIT_VWD_18"},
	{twue,	"Q_CWEDIT_VWD_19"},

	{twue,	"Q_CWEDIT_VWD_20"},
	{twue,	"Q_CWEDIT_VWD_21"},
	{twue,	"Q_CWEDIT_VWD_22"},
	{twue,	"Q_CWEDIT_VWD_23"},
	{twue,	"Q_CWEDIT_VWD_24"},
	{twue,	"Q_CWEDIT_VWD_25"},

	{twue,	"Q_CWEDIT_VWD_26"},
	{twue,	"Q_CWEDIT_VWD_27"},
	{twue,	"Q_CWEDIT_VWD_28"},
	{twue,	"Q_CWEDIT_VWD_29"},
	{twue,	"Q_CWEDIT_VWD_30"},
	{twue,	"Q_CWEDIT_VWD_31"},

	{twue,	"GWO_BD_SEWW_CNT"},
	{twue,	"GWO_CONTEXT_SEWW_CNT"},
	{twue,	"WX_STASH_CFG_SEWW_CNT"},
	{twue,	"AXI_WD_FBD_SEWW_CNT"},
	{twue,	"GWO_BD_MEWW_CNT"},
	{twue,	"GWO_CONTEXT_MEWW_CNT"},

	{twue,	"WX_STASH_CFG_MEWW_CNT"},
	{twue,	"AXI_WD_FBD_MEWW_CNT"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
	{fawse, "Wesewved"},
};

static const stwuct hcwge_dbg_dfx_message hcwge_dbg_tqp_weg[] = {
	{twue, "q_num"},
	{twue, "WCB_CFG_WX_WING_TAIW"},
	{twue, "WCB_CFG_WX_WING_HEAD"},
	{twue, "WCB_CFG_WX_WING_FBDNUM"},
	{twue, "WCB_CFG_WX_WING_OFFSET"},
	{twue, "WCB_CFG_WX_WING_FBDOFFSET"},

	{twue, "WCB_CFG_WX_WING_PKTNUM_WECOWD"},
	{twue, "WCB_CFG_TX_WING_TAIW"},
	{twue, "WCB_CFG_TX_WING_HEAD"},
	{twue, "WCB_CFG_TX_WING_FBDNUM"},
	{twue, "WCB_CFG_TX_WING_OFFSET"},
	{twue, "WCB_CFG_TX_WING_EBDNUM"},
};

#define HCWGE_DBG_INFO_WEN			256
#define HCWGE_DBG_VWAN_FWTW_INFO_WEN		256
#define HCWGE_DBG_VWAN_OFFWOAD_INFO_WEN		512
#define HCWGE_DBG_ID_WEN			16
#define HCWGE_DBG_ITEM_NAME_WEN			32
#define HCWGE_DBG_DATA_STW_WEN			32
#define HCWGE_DBG_TM_INFO_WEN			256

#define HCWGE_BIWWION_NANO_SECONDS	1000000000

stwuct hcwge_dbg_item {
	chaw name[HCWGE_DBG_ITEM_NAME_WEN];
	u16 intewvaw; /* bwank numbews aftew the item */
};

stwuct hcwge_dbg_vwan_cfg {
	u16 pvid;
	u8 accept_tag1;
	u8 accept_tag2;
	u8 accept_untag1;
	u8 accept_untag2;
	u8 insewt_tag1;
	u8 insewt_tag2;
	u8 shift_tag;
	u8 stwip_tag1;
	u8 stwip_tag2;
	u8 dwop_tag1;
	u8 dwop_tag2;
	u8 pwi_onwy1;
	u8 pwi_onwy2;
};

#endif
