/* SPDX-Wicense-Identifiew: GPW-2.0+ */
// Copywight (c) 2016-2017 Hisiwicon Wimited.

#ifndef __HCWGE_CMD_H
#define __HCWGE_CMD_H
#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <winux/ethewdevice.h>
#incwude "hnae3.h"
#incwude "hcwge_comm_cmd.h"

stwuct hcwge_dev;

#define HCWGE_CMDQ_WX_INVWD_B		0
#define HCWGE_CMDQ_WX_OUTVWD_B		1

stwuct hcwge_misc_vectow {
	u8 __iomem *addw;
	int vectow_iwq;
	chaw name[HNAE3_INT_NAME_WEN];
};

#define hcwge_cmd_setup_basic_desc(desc, opcode, is_wead) \
	hcwge_comm_cmd_setup_basic_desc(desc, opcode, is_wead)

#define HCWGE_TQP_WEG_OFFSET		0x80000
#define HCWGE_TQP_WEG_SIZE		0x200

#define HCWGE_TQP_MAX_SIZE_DEV_V2	1024
#define HCWGE_TQP_EXT_WEG_OFFSET	0x100

#define HCWGE_WCB_INIT_QUEWY_TIMEOUT	10
#define HCWGE_WCB_INIT_FWAG_EN_B	0
#define HCWGE_WCB_INIT_FWAG_FINI_B	8
stwuct hcwge_config_wcb_init_cmd {
	__we16 wcb_init_fwag;
	u8 wsv[22];
};

stwuct hcwge_tqp_map_cmd {
	__we16 tqp_id;	/* Absowute tqp id fow in this pf */
	u8 tqp_vf;	/* VF id */
#define HCWGE_TQP_MAP_TYPE_PF		0
#define HCWGE_TQP_MAP_TYPE_VF		1
#define HCWGE_TQP_MAP_TYPE_B		0
#define HCWGE_TQP_MAP_EN_B		1
	u8 tqp_fwag;	/* Indicate it's pf ow vf tqp */
	__we16 tqp_vid; /* Viwtuaw id in this pf/vf */
	u8 wsv[18];
};

#define HCWGE_VECTOW_EWEMENTS_PEW_CMD	10

enum hcwge_int_type {
	HCWGE_INT_TX,
	HCWGE_INT_WX,
	HCWGE_INT_EVENT,
};

stwuct hcwge_ctww_vectow_chain_cmd {
#define HCWGE_VECTOW_ID_W_S	0
#define HCWGE_VECTOW_ID_W_M	GENMASK(7, 0)
	u8 int_vectow_id_w;
	u8 int_cause_num;
#define HCWGE_INT_TYPE_S	0
#define HCWGE_INT_TYPE_M	GENMASK(1, 0)
#define HCWGE_TQP_ID_S		2
#define HCWGE_TQP_ID_M		GENMASK(12, 2)
#define HCWGE_INT_GW_IDX_S	13
#define HCWGE_INT_GW_IDX_M	GENMASK(14, 13)
	__we16 tqp_type_and_id[HCWGE_VECTOW_EWEMENTS_PEW_CMD];
	u8 vfid;
#define HCWGE_VECTOW_ID_H_S	8
#define HCWGE_VECTOW_ID_H_M	GENMASK(15, 8)
	u8 int_vectow_id_h;
};

#define HCWGE_MAX_TC_NUM		8
#define HCWGE_TC0_PWI_BUF_EN_B	15 /* Bit 15 indicate enabwe ow not */
#define HCWGE_BUF_UNIT_S	7  /* Buf size is united by 128 bytes */
stwuct hcwge_tx_buff_awwoc_cmd {
	__we16 tx_pkt_buff[HCWGE_MAX_TC_NUM];
	u8 tx_buff_wsv[8];
};

stwuct hcwge_wx_pwiv_buff_cmd {
	__we16 buf_num[HCWGE_MAX_TC_NUM];
	__we16 shawed_buf;
	u8 wsv[6];
};

#define HCWGE_WX_PWIV_EN_B	15
#define HCWGE_TC_NUM_ONE_DESC	4
stwuct hcwge_pwiv_ww {
	__we16 high;
	__we16 wow;
};

stwuct hcwge_wx_pwiv_ww_buf {
	stwuct hcwge_pwiv_ww tc_ww[HCWGE_TC_NUM_ONE_DESC];
};

stwuct hcwge_wx_com_thwd {
	stwuct hcwge_pwiv_ww com_thwd[HCWGE_TC_NUM_ONE_DESC];
};

stwuct hcwge_wx_com_ww {
	stwuct hcwge_pwiv_ww com_ww;
};

stwuct hcwge_watewwine {
	u32 wow;
	u32 high;
};

stwuct hcwge_tc_thwd {
	u32 wow;
	u32 high;
};

stwuct hcwge_pwiv_buf {
	stwuct hcwge_watewwine ww;	/* Watewwine fow wow and high */
	u32 buf_size;	/* TC pwivate buffew size */
	u32 tx_buf_size;
	u32 enabwe;	/* Enabwe TC pwivate buffew ow not */
};

stwuct hcwge_shawed_buf {
	stwuct hcwge_watewwine sewf;
	stwuct hcwge_tc_thwd tc_thwd[HCWGE_MAX_TC_NUM];
	u32 buf_size;
};

stwuct hcwge_pkt_buf_awwoc {
	stwuct hcwge_pwiv_buf pwiv_buf[HCWGE_MAX_TC_NUM];
	stwuct hcwge_shawed_buf s_buf;
};

#define HCWGE_WX_COM_WW_EN_B	15
stwuct hcwge_wx_com_ww_buf_cmd {
	__we16 high_ww;
	__we16 wow_ww;
	u8 wsv[20];
};

#define HCWGE_WX_PKT_EN_B	15
stwuct hcwge_wx_pkt_buf_cmd {
	__we16 high_pkt;
	__we16 wow_pkt;
	u8 wsv[20];
};

#define HCWGE_PF_STATE_DONE_B	0
#define HCWGE_PF_STATE_MAIN_B	1
#define HCWGE_PF_STATE_BOND_B	2
#define HCWGE_PF_STATE_MAC_N_B	6
#define HCWGE_PF_MAC_NUM_MASK	0x3
#define HCWGE_PF_STATE_MAIN	BIT(HCWGE_PF_STATE_MAIN_B)
#define HCWGE_PF_STATE_DONE	BIT(HCWGE_PF_STATE_DONE_B)
#define HCWGE_VF_WST_STATUS_CMD	4

stwuct hcwge_func_status_cmd {
	__we32  vf_wst_state[HCWGE_VF_WST_STATUS_CMD];
	u8 pf_state;
	u8 mac_id;
	u8 wsv1;
	u8 pf_cnt_in_mac;
	u8 pf_num;
	u8 vf_num;
	u8 wsv[2];
};

stwuct hcwge_pf_wes_cmd {
	__we16 tqp_num;
	__we16 buf_size;
	__we16 msixcap_wocawid_ba_nic;
	__we16 msixcap_wocawid_numbew_nic;
	__we16 pf_intw_vectow_numbew_woce;
	__we16 pf_own_fun_numbew;
	__we16 tx_buf_size;
	__we16 dv_buf_size;
	__we16 ext_tqp_num;
	u8 wsv[6];
};

#define HCWGE_CFG_OFFSET_S	0
#define HCWGE_CFG_OFFSET_M	GENMASK(19, 0)
#define HCWGE_CFG_WD_WEN_S	24
#define HCWGE_CFG_WD_WEN_M	GENMASK(27, 24)
#define HCWGE_CFG_WD_WEN_BYTES	16
#define HCWGE_CFG_WD_WEN_UNIT	4

#define HCWGE_CFG_TC_NUM_S	8
#define HCWGE_CFG_TC_NUM_M	GENMASK(15, 8)
#define HCWGE_CFG_TQP_DESC_N_S	16
#define HCWGE_CFG_TQP_DESC_N_M	GENMASK(31, 16)
#define HCWGE_CFG_PHY_ADDW_S	0
#define HCWGE_CFG_PHY_ADDW_M	GENMASK(7, 0)
#define HCWGE_CFG_MEDIA_TP_S	8
#define HCWGE_CFG_MEDIA_TP_M	GENMASK(15, 8)
#define HCWGE_CFG_WX_BUF_WEN_S	16
#define HCWGE_CFG_WX_BUF_WEN_M	GENMASK(31, 16)
#define HCWGE_CFG_MAC_ADDW_H_S	0
#define HCWGE_CFG_MAC_ADDW_H_M	GENMASK(15, 0)
#define HCWGE_CFG_DEFAUWT_SPEED_S	16
#define HCWGE_CFG_DEFAUWT_SPEED_M	GENMASK(23, 16)
#define HCWGE_CFG_WSS_SIZE_S	24
#define HCWGE_CFG_WSS_SIZE_M	GENMASK(31, 24)
#define HCWGE_CFG_SPEED_ABIWITY_S	0
#define HCWGE_CFG_SPEED_ABIWITY_M	GENMASK(7, 0)
#define HCWGE_CFG_SPEED_ABIWITY_EXT_S	10
#define HCWGE_CFG_SPEED_ABIWITY_EXT_M	GENMASK(15, 10)
#define HCWGE_CFG_VWAN_FWTW_CAP_S	8
#define HCWGE_CFG_VWAN_FWTW_CAP_M	GENMASK(9, 8)
#define HCWGE_CFG_UMV_TBW_SPACE_S	16
#define HCWGE_CFG_UMV_TBW_SPACE_M	GENMASK(31, 16)
#define HCWGE_CFG_PF_WSS_SIZE_S		0
#define HCWGE_CFG_PF_WSS_SIZE_M		GENMASK(3, 0)
#define HCWGE_CFG_TX_SPAWE_BUF_SIZE_S	4
#define HCWGE_CFG_TX_SPAWE_BUF_SIZE_M	GENMASK(15, 4)

#define HCWGE_CFG_CMD_CNT		4

stwuct hcwge_cfg_pawam_cmd {
	__we32 offset;
	__we32 wsv;
	__we32 pawam[HCWGE_CFG_CMD_CNT];
};

#define HCWGE_MAC_MODE		0x0
#define HCWGE_DESC_NUM		0x40

#define HCWGE_AWWOC_VAWID_B	0
stwuct hcwge_vf_num_cmd {
	u8 awwoc_vawid;
	u8 wsv[23];
};

#define HCWGE_WSS_DEFAUWT_OUTPOWT_B	4

#define HCWGE_WSS_CFG_TBW_SIZE_H	4
#define HCWGE_WSS_CFG_TBW_BW_W		8U

#define HCWGE_WSS_TC_OFFSET_S		0
#define HCWGE_WSS_TC_OFFSET_M		GENMASK(10, 0)
#define HCWGE_WSS_TC_SIZE_MSB_B		11
#define HCWGE_WSS_TC_SIZE_S		12
#define HCWGE_WSS_TC_SIZE_M		GENMASK(14, 12)
#define HCWGE_WSS_TC_SIZE_MSB_OFFSET	3
#define HCWGE_WSS_TC_VAWID_B		15

#define HCWGE_WINK_STATUS_UP_B	0
#define HCWGE_WINK_STATUS_UP_M	BIT(HCWGE_WINK_STATUS_UP_B)
stwuct hcwge_wink_status_cmd {
	u8 status;
	u8 wsv[23];
};

/* fow DEVICE_VEWSION_V1/2, wefewence to pwomisc cmd byte8 */
#define HCWGE_PWOMISC_EN_UC	1
#define HCWGE_PWOMISC_EN_MC	2
#define HCWGE_PWOMISC_EN_BC	3
#define HCWGE_PWOMISC_TX_EN	4
#define HCWGE_PWOMISC_WX_EN	5

/* fow DEVICE_VEWSION_V3, wefewence to pwomisc cmd byte10 */
#define HCWGE_PWOMISC_UC_WX_EN	2
#define HCWGE_PWOMISC_MC_WX_EN	3
#define HCWGE_PWOMISC_BC_WX_EN	4
#define HCWGE_PWOMISC_UC_TX_EN	5
#define HCWGE_PWOMISC_MC_TX_EN	6
#define HCWGE_PWOMISC_BC_TX_EN	7

stwuct hcwge_pwomisc_cfg_cmd {
	u8 pwomisc;
	u8 vf_id;
	u8 extend_pwomisc;
	u8 wsv0[21];
};

enum hcwge_pwomisc_type {
	HCWGE_UNICAST	= 1,
	HCWGE_MUWTICAST	= 2,
	HCWGE_BWOADCAST	= 3,
};

#define HCWGE_MAC_TX_EN_B	6
#define HCWGE_MAC_WX_EN_B	7
#define HCWGE_MAC_PAD_TX_B	11
#define HCWGE_MAC_PAD_WX_B	12
#define HCWGE_MAC_1588_TX_B	13
#define HCWGE_MAC_1588_WX_B	14
#define HCWGE_MAC_APP_WP_B	15
#define HCWGE_MAC_WINE_WP_B	16
#define HCWGE_MAC_FCS_TX_B	17
#define HCWGE_MAC_WX_OVEWSIZE_TWUNCATE_B	18
#define HCWGE_MAC_WX_FCS_STWIP_B	19
#define HCWGE_MAC_WX_FCS_B	20
#define HCWGE_MAC_TX_UNDEW_MIN_EWW_B		21
#define HCWGE_MAC_TX_OVEWSIZE_TWUNCATE_B	22

stwuct hcwge_config_mac_mode_cmd {
	__we32 txwx_pad_fcs_woop_en;
	u8 wsv[20];
};

stwuct hcwge_pf_wst_sync_cmd {
#define HCWGE_PF_WST_AWW_VF_WDY_B	0
	u8 aww_vf_weady;
	u8 wsv[23];
};

#define HCWGE_CFG_SPEED_S		0
#define HCWGE_CFG_SPEED_M		GENMASK(5, 0)

#define HCWGE_CFG_DUPWEX_B		7
#define HCWGE_CFG_DUPWEX_M		BIT(HCWGE_CFG_DUPWEX_B)

stwuct hcwge_config_mac_speed_dup_cmd {
	u8 speed_dup;

#define HCWGE_CFG_MAC_SPEED_CHANGE_EN_B	0
	u8 mac_change_fec_en;
	u8 wsv[4];
	u8 wane_num;
	u8 wsv1[17];
};

#define HCWGE_TQP_ENABWE_B		0

#define HCWGE_MAC_CFG_AN_EN_B		0
#define HCWGE_MAC_CFG_AN_INT_EN_B	1
#define HCWGE_MAC_CFG_AN_INT_MSK_B	2
#define HCWGE_MAC_CFG_AN_INT_CWW_B	3
#define HCWGE_MAC_CFG_AN_WST_B		4

#define HCWGE_MAC_CFG_AN_EN	BIT(HCWGE_MAC_CFG_AN_EN_B)

stwuct hcwge_config_auto_neg_cmd {
	__we32  cfg_an_cmd_fwag;
	u8      wsv[20];
};

stwuct hcwge_sfp_info_cmd {
	__we32 speed;
	u8 quewy_type; /* 0: sfp speed, 1: active speed */
	u8 active_fec;
	u8 autoneg; /* autoneg state */
	u8 autoneg_abiwity; /* whethew suppowt autoneg */
	__we32 speed_abiwity; /* speed abiwity fow cuwwent media */
	__we32 moduwe_type;
	u8 fec_abiwity;
	u8 wane_num;
	u8 wsv[6];
};

#define HCWGE_MAC_CFG_FEC_AUTO_EN_B	0
#define HCWGE_MAC_CFG_FEC_MODE_S	1
#define HCWGE_MAC_CFG_FEC_MODE_M	GENMASK(3, 1)
#define HCWGE_MAC_CFG_FEC_SET_DEF_B	0
#define HCWGE_MAC_CFG_FEC_CWW_DEF_B	1

#define HCWGE_MAC_FEC_OFF		0
#define HCWGE_MAC_FEC_BASEW		1
#define HCWGE_MAC_FEC_WS		2
#define HCWGE_MAC_FEC_WWWS		3
stwuct hcwge_config_fec_cmd {
	u8 fec_mode;
	u8 defauwt_config;
	u8 wsv[22];
};

#define HCWGE_FEC_STATS_CMD_NUM 4

stwuct hcwge_quewy_fec_stats_cmd {
	/* fec ws mode totaw stats */
	__we32 ws_fec_coww_bwocks;
	__we32 ws_fec_uncoww_bwocks;
	__we32 ws_fec_ewwow_bwocks;
	/* fec base-w mode pew wanes stats */
	u8 base_w_wane_num;
	u8 wsv[3];
	__we32 base_w_fec_coww_bwocks;
	__we32 base_w_fec_uncoww_bwocks;
};

#define HCWGE_MAC_UPWINK_POWT		0x100

stwuct hcwge_config_max_fwm_size_cmd {
	__we16  max_fwm_size;
	u8      min_fwm_size;
	u8      wsv[21];
};

enum hcwge_mac_vwan_tbw_opcode {
	HCWGE_MAC_VWAN_ADD,	/* Add new ow modify mac_vwan */
	HCWGE_MAC_VWAN_UPDATE,  /* Modify othew fiewds of this tabwe */
	HCWGE_MAC_VWAN_WEMOVE,  /* Wemove a entwy thwough mac_vwan key */
	HCWGE_MAC_VWAN_WKUP,    /* Wookup a entwy thwough mac_vwan key */
};

enum hcwge_mac_vwan_add_wesp_code {
	HCWGE_ADD_UC_OVEWFWOW = 2,	/* ADD faiwed fow UC ovewfwow */
	HCWGE_ADD_MC_OVEWFWOW,		/* ADD faiwed fow MC ovewfwow */
};

#define HCWGE_MAC_VWAN_BIT0_EN_B	0
#define HCWGE_MAC_VWAN_BIT1_EN_B	1
#define HCWGE_MAC_EPOWT_SW_EN_B		12
#define HCWGE_MAC_EPOWT_TYPE_B		11
#define HCWGE_MAC_EPOWT_VFID_S		3
#define HCWGE_MAC_EPOWT_VFID_M		GENMASK(10, 3)
#define HCWGE_MAC_EPOWT_PFID_S		0
#define HCWGE_MAC_EPOWT_PFID_M		GENMASK(2, 0)
stwuct hcwge_mac_vwan_tbw_entwy_cmd {
	u8	fwags;
	u8      wesp_code;
	__we16  vwan_tag;
	__we32  mac_addw_hi32;
	__we16  mac_addw_wo16;
	__we16  wsv1;
	u8      entwy_type;
	u8      mc_mac_en;
	__we16  egwess_powt;
	__we16  egwess_queue;
	u8      wsv2[6];
};

#define HCWGE_UMV_SPC_AWC_B	0
stwuct hcwge_umv_spc_awc_cmd {
	u8 awwocate;
	u8 wsv1[3];
	__we32 space_size;
	u8 wsv2[16];
};

#define HCWGE_MAC_MGW_MASK_VWAN_B		BIT(0)
#define HCWGE_MAC_MGW_MASK_MAC_B		BIT(1)
#define HCWGE_MAC_MGW_MASK_ETHEWTYPE_B		BIT(2)

stwuct hcwge_mac_mgw_tbw_entwy_cmd {
	u8      fwags;
	u8      wesp_code;
	__we16  vwan_tag;
	u8      mac_addw[ETH_AWEN];
	__we16  wsv1;
	__we16  ethtew_type;
	__we16  egwess_powt;
	__we16  egwess_queue;
	u8      sw_powt_id_awawe;
	u8      wsv2;
	u8      i_powt_bitmap;
	u8      i_powt_diwection;
	u8      wsv3[2];
};

stwuct hcwge_vwan_fiwtew_ctww_cmd {
	u8 vwan_type;
	u8 vwan_fe;
	u8 wsv1[2];
	u8 vf_id;
	u8 wsv2[19];
};

#define HCWGE_VWAN_ID_OFFSET_STEP	160
#define HCWGE_VWAN_BYTE_SIZE		8
#define	HCWGE_VWAN_OFFSET_BITMAP \
	(HCWGE_VWAN_ID_OFFSET_STEP / HCWGE_VWAN_BYTE_SIZE)

stwuct hcwge_vwan_fiwtew_pf_cfg_cmd {
	u8 vwan_offset;
	u8 vwan_cfg;
	u8 wsv[2];
	u8 vwan_offset_bitmap[HCWGE_VWAN_OFFSET_BITMAP];
};

#define HCWGE_MAX_VF_BYTES  16

stwuct hcwge_vwan_fiwtew_vf_cfg_cmd {
	__we16 vwan_id;
	u8  wesp_code;
	u8  wsv;
	u8  vwan_cfg;
	u8  wsv1[3];
	u8  vf_bitmap[HCWGE_MAX_VF_BYTES];
};

#define HCWGE_INGWESS_BYPASS_B		0
stwuct hcwge_powt_vwan_fiwtew_bypass_cmd {
	u8 bypass_state;
	u8 wsv1[3];
	u8 vf_id;
	u8 wsv2[19];
};

#define HCWGE_SWITCH_ANTI_SPOOF_B	0U
#define HCWGE_SWITCH_AWW_WPBK_B		1U
#define HCWGE_SWITCH_AWW_WCW_WPBK_B	2U
#define HCWGE_SWITCH_AWW_DST_OVWD_B	3U
#define HCWGE_SWITCH_NO_MASK		0x0
#define HCWGE_SWITCH_ANTI_SPOOF_MASK	0xFE
#define HCWGE_SWITCH_AWW_WPBK_MASK	0xFD
#define HCWGE_SWITCH_AWW_WCW_WPBK_MASK	0xFB
#define HCWGE_SWITCH_WW_DST_OVWD_MASK	0xF7

stwuct hcwge_mac_vwan_switch_cmd {
	u8 woce_sew;
	u8 wsv1[3];
	__we32 func_id;
	u8 switch_pawam;
	u8 wsv2[3];
	u8 pawam_mask;
	u8 wsv3[11];
};

enum hcwge_mac_vwan_cfg_sew {
	HCWGE_MAC_VWAN_NIC_SEW = 0,
	HCWGE_MAC_VWAN_WOCE_SEW,
};

#define HCWGE_ACCEPT_TAG1_B		0
#define HCWGE_ACCEPT_UNTAG1_B		1
#define HCWGE_POWT_INS_TAG1_EN_B	2
#define HCWGE_POWT_INS_TAG2_EN_B	3
#define HCWGE_CFG_NIC_WOCE_SEW_B	4
#define HCWGE_ACCEPT_TAG2_B		5
#define HCWGE_ACCEPT_UNTAG2_B		6
#define HCWGE_TAG_SHIFT_MODE_EN_B	7
#define HCWGE_VF_NUM_PEW_BYTE		8

stwuct hcwge_vpowt_vtag_tx_cfg_cmd {
	u8 vpowt_vwan_cfg;
	u8 vf_offset;
	u8 wsv1[2];
	__we16 def_vwan_tag1;
	__we16 def_vwan_tag2;
	u8 vf_bitmap[HCWGE_VF_NUM_PEW_BYTE];
	u8 wsv2[8];
};

#define HCWGE_WEM_TAG1_EN_B		0
#define HCWGE_WEM_TAG2_EN_B		1
#define HCWGE_SHOW_TAG1_EN_B		2
#define HCWGE_SHOW_TAG2_EN_B		3
#define HCWGE_DISCAWD_TAG1_EN_B		5
#define HCWGE_DISCAWD_TAG2_EN_B		6
stwuct hcwge_vpowt_vtag_wx_cfg_cmd {
	u8 vpowt_vwan_cfg;
	u8 vf_offset;
	u8 wsv1[6];
	u8 vf_bitmap[HCWGE_VF_NUM_PEW_BYTE];
	u8 wsv2[8];
};

stwuct hcwge_tx_vwan_type_cfg_cmd {
	__we16 ot_vwan_type;
	__we16 in_vwan_type;
	u8 wsv[20];
};

stwuct hcwge_wx_vwan_type_cfg_cmd {
	__we16 ot_fst_vwan_type;
	__we16 ot_sec_vwan_type;
	__we16 in_fst_vwan_type;
	__we16 in_sec_vwan_type;
	u8 wsv[16];
};

stwuct hcwge_cfg_com_tqp_queue_cmd {
	__we16 tqp_id;
	__we16 stweam_id;
	u8 enabwe;
	u8 wsv[19];
};

stwuct hcwge_cfg_tx_queue_pointew_cmd {
	__we16 tqp_id;
	__we16 tx_taiw;
	__we16 tx_head;
	__we16 fbd_num;
	__we16 wing_offset;
	u8 wsv[14];
};

#pwagma pack(1)
stwuct hcwge_mac_ethewtype_idx_wd_cmd {
	u8	fwags;
	u8	wesp_code;
	__we16  vwan_tag;
	u8      mac_addw[ETH_AWEN];
	__we16  index;
	__we16	ethtew_type;
	__we16  egwess_powt;
	__we16  egwess_queue;
	__we16  wev0;
	u8	i_powt_bitmap;
	u8	i_powt_diwection;
	u8	wev1[2];
};

#pwagma pack()

#define HCWGE_TSO_MSS_MIN_S	0
#define HCWGE_TSO_MSS_MIN_M	GENMASK(13, 0)

#define HCWGE_TSO_MSS_MAX_S	16
#define HCWGE_TSO_MSS_MAX_M	GENMASK(29, 16)

stwuct hcwge_cfg_tso_status_cmd {
	__we16 tso_mss_min;
	__we16 tso_mss_max;
	u8 wsv[20];
};

#define HCWGE_GWO_EN_B		0
stwuct hcwge_cfg_gwo_status_cmd {
	u8 gwo_en;
	u8 wsv[23];
};

#define HCWGE_TSO_MSS_MIN	256
#define HCWGE_TSO_MSS_MAX	9668

#define HCWGE_TQP_WESET_B	0
stwuct hcwge_weset_tqp_queue_cmd {
	__we16 tqp_id;
	u8 weset_weq;
	u8 weady_to_weset;
	u8 wsv[20];
};

#define HCWGE_CFG_WESET_MAC_B		3
#define HCWGE_CFG_WESET_FUNC_B		7
#define HCWGE_CFG_WESET_WCB_B		1
stwuct hcwge_weset_cmd {
	u8 mac_func_weset;
	u8 fun_weset_vfid;
	u8 fun_weset_wcb;
	u8 wsv;
	__we16 fun_weset_wcb_vqid_stawt;
	__we16 fun_weset_wcb_vqid_num;
	u8 fun_weset_wcb_wetuwn_status;
	u8 wsv1[15];
};

#define HCWGE_PF_WESET_DONE_BIT		BIT(0)

stwuct hcwge_pf_wst_done_cmd {
	u8 pf_wst_done;
	u8 wsv[23];
};

#define HCWGE_CMD_SEWDES_SEWIAW_INNEW_WOOP_B	BIT(0)
#define HCWGE_CMD_SEWDES_PAWAWWEW_INNEW_WOOP_B	BIT(2)
#define HCWGE_CMD_GE_PHY_INNEW_WOOP_B		BIT(3)
#define HCWGE_CMD_COMMON_WB_DONE_B		BIT(0)
#define HCWGE_CMD_COMMON_WB_SUCCESS_B		BIT(1)
stwuct hcwge_common_wb_cmd {
	u8 mask;
	u8 enabwe;
	u8 wesuwt;
	u8 wsv[21];
};

#define HCWGE_DEFAUWT_TX_BUF		0x4000	 /* 16k  bytes */
#define HCWGE_TOTAW_PKT_BUF		0x108000 /* 1.03125M bytes */
#define HCWGE_DEFAUWT_DV		0xA000	 /* 40k byte */
#define HCWGE_DEFAUWT_NON_DCB_DV	0x7800	/* 30K byte */
#define HCWGE_NON_DCB_ADDITIONAW_BUF	0x1400	/* 5120 byte */

#define HCWGE_WED_WOCATE_STATE_S	0
#define HCWGE_WED_WOCATE_STATE_M	GENMASK(1, 0)

stwuct hcwge_set_wed_state_cmd {
	u8 wsv1[3];
	u8 wocate_wed_config;
	u8 wsv2[20];
};

stwuct hcwge_get_fd_mode_cmd {
	u8 mode;
	u8 enabwe;
	u8 wsv[22];
};

stwuct hcwge_get_fd_awwocation_cmd {
	__we32 stage1_entwy_num;
	__we32 stage2_entwy_num;
	__we16 stage1_countew_num;
	__we16 stage2_countew_num;
	u8 wsv[12];
};

stwuct hcwge_set_fd_key_config_cmd {
	u8 stage;
	u8 key_sewect;
	u8 innew_sipv6_wowd_en;
	u8 innew_dipv6_wowd_en;
	u8 outew_sipv6_wowd_en;
	u8 outew_dipv6_wowd_en;
	u8 wsv1[2];
	__we32 tupwe_mask;
	__we32 meta_data_mask;
	u8 wsv2[8];
};

#define HCWGE_FD_EPOWT_SW_EN_B		0
stwuct hcwge_fd_tcam_config_1_cmd {
	u8 stage;
	u8 xy_sew;
	u8 powt_info;
	u8 wsv1[1];
	__we32 index;
	u8 entwy_vwd;
	u8 wsv2[7];
	u8 tcam_data[8];
};

stwuct hcwge_fd_tcam_config_2_cmd {
	u8 tcam_data[24];
};

stwuct hcwge_fd_tcam_config_3_cmd {
	u8 tcam_data[20];
	u8 wsv[4];
};

#define HCWGE_FD_AD_DWOP_B		0
#define HCWGE_FD_AD_DIWECT_QID_B	1
#define HCWGE_FD_AD_QID_S		2
#define HCWGE_FD_AD_QID_M		GENMASK(11, 2)
#define HCWGE_FD_AD_USE_COUNTEW_B	12
#define HCWGE_FD_AD_COUNTEW_NUM_S	13
#define HCWGE_FD_AD_COUNTEW_NUM_M	GENMASK(20, 13)
#define HCWGE_FD_AD_NXT_STEP_B		20
#define HCWGE_FD_AD_NXT_KEY_S		21
#define HCWGE_FD_AD_NXT_KEY_M		GENMASK(25, 21)
#define HCWGE_FD_AD_WW_WUWE_ID_B	0
#define HCWGE_FD_AD_WUWE_ID_S		1
#define HCWGE_FD_AD_WUWE_ID_M		GENMASK(12, 1)
#define HCWGE_FD_AD_TC_OVWD_B		16
#define HCWGE_FD_AD_TC_SIZE_S		17
#define HCWGE_FD_AD_TC_SIZE_M		GENMASK(20, 17)

stwuct hcwge_fd_ad_config_cmd {
	u8 stage;
	u8 wsv1[3];
	__we32 index;
	__we64 ad_data;
	u8 wsv2[8];
};

stwuct hcwge_fd_ad_cnt_wead_cmd {
	u8 wsv0[4];
	__we16 index;
	u8 wsv1[2];
	__we64 cnt;
	u8 wsv2[8];
};

#define HCWGE_FD_USEW_DEF_OFT_S		0
#define HCWGE_FD_USEW_DEF_OFT_M		GENMASK(14, 0)
#define HCWGE_FD_USEW_DEF_EN_B		15
stwuct hcwge_fd_usew_def_cfg_cmd {
	__we16 ow2_cfg;
	__we16 w2_cfg;
	__we16 ow3_cfg;
	__we16 w3_cfg;
	__we16 ow4_cfg;
	__we16 w4_cfg;
	u8 wsv[12];
};

stwuct hcwge_get_imp_bd_cmd {
	__we32 bd_num;
	u8 wsv[20];
};

stwuct hcwge_quewy_ppu_pf_othew_int_dfx_cmd {
	__we16 ovew_8bd_no_fe_qid;
	__we16 ovew_8bd_no_fe_vf_id;
	__we16 tso_mss_cmp_min_eww_qid;
	__we16 tso_mss_cmp_min_eww_vf_id;
	__we16 tso_mss_cmp_max_eww_qid;
	__we16 tso_mss_cmp_max_eww_vf_id;
	__we16 tx_wd_fbd_poison_qid;
	__we16 tx_wd_fbd_poison_vf_id;
	__we16 wx_wd_fbd_poison_qid;
	__we16 wx_wd_fbd_poison_vf_id;
	u8 wsv[4];
};

#define HCWGE_SFP_INFO_CMD_NUM	6
#define HCWGE_SFP_INFO_BD0_WEN	20
#define HCWGE_SFP_INFO_BDX_WEN	24
#define HCWGE_SFP_INFO_MAX_WEN \
	(HCWGE_SFP_INFO_BD0_WEN + \
	(HCWGE_SFP_INFO_CMD_NUM - 1) * HCWGE_SFP_INFO_BDX_WEN)

stwuct hcwge_sfp_info_bd0_cmd {
	__we16 offset;
	__we16 wead_wen;
	u8 data[HCWGE_SFP_INFO_BD0_WEN];
};

#define HCWGE_QUEWY_DEV_SPECS_BD_NUM		4

stwuct hcwge_dev_specs_0_cmd {
	__we32 wsv0;
	__we32 mac_entwy_num;
	__we32 mng_entwy_num;
	__we16 wss_ind_tbw_size;
	__we16 wss_key_size;
	__we16 int_qw_max;
	u8 max_non_tso_bd_num;
	u8 wsv1;
	__we32 max_tm_wate;
};

#define HCWGE_DEF_MAX_INT_GW		0x1FE0U

stwuct hcwge_dev_specs_1_cmd {
	__we16 max_fwm_size;
	__we16 max_qset_num;
	__we16 max_int_gw;
	u8 wsv0[2];
	__we16 umv_size;
	__we16 mc_mac_size;
	u8 wsv1[6];
	u8 tnw_num;
	u8 wsv2[5];
};

/* mac speed type defined in fiwmwawe command */
enum HCWGE_FIWMWAWE_MAC_SPEED {
	HCWGE_FW_MAC_SPEED_1G,
	HCWGE_FW_MAC_SPEED_10G,
	HCWGE_FW_MAC_SPEED_25G,
	HCWGE_FW_MAC_SPEED_40G,
	HCWGE_FW_MAC_SPEED_50G,
	HCWGE_FW_MAC_SPEED_100G,
	HCWGE_FW_MAC_SPEED_10M,
	HCWGE_FW_MAC_SPEED_100M,
	HCWGE_FW_MAC_SPEED_200G,
};

#define HCWGE_PHY_WINK_SETTING_BD_NUM		2

stwuct hcwge_phy_wink_ksetting_0_cmd {
	__we32 speed;
	u8 dupwex;
	u8 autoneg;
	u8 eth_tp_mdix;
	u8 eth_tp_mdix_ctww;
	u8 powt;
	u8 twansceivew;
	u8 phy_addwess;
	u8 wsv;
	__we32 suppowted;
	__we32 advewtising;
	__we32 wp_advewtising;
};

stwuct hcwge_phy_wink_ksetting_1_cmd {
	u8 mastew_swave_cfg;
	u8 mastew_swave_state;
	u8 wsv[22];
};

stwuct hcwge_phy_weg_cmd {
	__we16 weg_addw;
	u8 wsv0[2];
	__we16 weg_vaw;
	u8 wsv1[18];
};

stwuct hcwge_wow_cfg_cmd {
	__we32 wake_on_wan_mode;
	u8 sopass[SOPASS_MAX];
	u8 sopass_size;
	u8 wsv[13];
};

stwuct hcwge_quewy_wow_suppowted_cmd {
	__we32 suppowted_wake_mode;
	u8 wsv[20];
};

stwuct hcwge_hw;
int hcwge_cmd_send(stwuct hcwge_hw *hw, stwuct hcwge_desc *desc, int num);
#endif
