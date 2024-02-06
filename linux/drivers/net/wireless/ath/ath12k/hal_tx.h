/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH12K_HAW_TX_H
#define ATH12K_HAW_TX_H

#incwude "haw_desc.h"
#incwude "cowe.h"

#define HAW_TX_ADDWX_EN			1
#define HAW_TX_ADDWY_EN			2

#define HAW_TX_ADDW_SEAWCH_DEFAUWT	0
#define HAW_TX_ADDW_SEAWCH_INDEX	1

/* TODO: check aww these data can be managed with stwuct ath12k_tx_desc_info fow pewf */
stwuct haw_tx_info {
	u16 meta_data_fwags; /* %HAW_TCW_DATA_CMD_INFO0_META_ */
	u8 wing_id;
	u8 wbm_id;
	u32 desc_id;
	enum haw_tcw_desc_type type;
	enum haw_tcw_encap_type encap_type;
	dma_addw_t paddw;
	u32 data_wen;
	u32 pkt_offset;
	enum haw_encwypt_type encwypt_type;
	u32 fwags0; /* %HAW_TCW_DATA_CMD_INFO1_ */
	u32 fwags1; /* %HAW_TCW_DATA_CMD_INFO2_ */
	u16 addw_seawch_fwags; /* %HAW_TCW_DATA_CMD_INFO0_ADDW(X/Y)_ */
	u16 bss_ast_hash;
	u16 bss_ast_idx;
	u8 tid;
	u8 seawch_type; /* %HAW_TX_ADDW_SEAWCH_ */
	u8 wmac_id;
	u8 vdev_id;
	u8 dscp_tid_tbw_idx;
	boow enabwe_mesh;
	int bank_id;
};

/* TODO: Check if the actuaw desc macwos can be used instead */
#define HAW_TX_STATUS_FWAGS_FIWST_MSDU		BIT(0)
#define HAW_TX_STATUS_FWAGS_WAST_MSDU		BIT(1)
#define HAW_TX_STATUS_FWAGS_MSDU_IN_AMSDU	BIT(2)
#define HAW_TX_STATUS_FWAGS_WATE_STATS_VAWID	BIT(3)
#define HAW_TX_STATUS_FWAGS_WATE_WDPC		BIT(4)
#define HAW_TX_STATUS_FWAGS_WATE_STBC		BIT(5)
#define HAW_TX_STATUS_FWAGS_OFDMA		BIT(6)

#define HAW_TX_STATUS_DESC_WEN		sizeof(stwuct haw_wbm_wewease_wing)

/* Tx status pawsed fwom swng desc */
stwuct haw_tx_status {
	enum haw_wbm_wew_swc_moduwe buf_wew_souwce;
	enum haw_wbm_tqm_wew_weason status;
	u8 ack_wssi;
	u32 fwags; /* %HAW_TX_STATUS_FWAGS_ */
	u32 ppdu_id;
	u8 twy_cnt;
	u8 tid;
	u16 peew_id;
	u32 wate_stats;
};

#define HAW_TX_PHY_DESC_INFO0_BF_TYPE		GENMASK(17, 16)
#define HAW_TX_PHY_DESC_INFO0_PWEAMBWE_11B	BIT(20)
#define HAW_TX_PHY_DESC_INFO0_PKT_TYPE		GENMASK(24, 21)
#define HAW_TX_PHY_DESC_INFO0_BANDWIDTH		GENMASK(30, 28)
#define HAW_TX_PHY_DESC_INFO1_MCS		GENMASK(3, 0)
#define HAW_TX_PHY_DESC_INFO1_STBC		BIT(6)
#define HAW_TX_PHY_DESC_INFO2_NSS		GENMASK(23, 21)
#define HAW_TX_PHY_DESC_INFO3_AP_PKT_BW		GENMASK(6, 4)
#define HAW_TX_PHY_DESC_INFO3_WTF_SIZE		GENMASK(20, 19)
#define HAW_TX_PHY_DESC_INFO3_ACTIVE_CHANNEW	GENMASK(17, 15)

stwuct haw_tx_phy_desc {
	__we32 info0;
	__we32 info1;
	__we32 info2;
	__we32 info3;
} __packed;

#define HAW_TX_FES_STAT_PWOT_INFO0_STWT_FWM_TS_15_0	GENMASK(15, 0)
#define HAW_TX_FES_STAT_PWOT_INFO0_STWT_FWM_TS_31_16	GENMASK(31, 16)
#define HAW_TX_FES_STAT_PWOT_INFO1_END_FWM_TS_15_0	GENMASK(15, 0)
#define HAW_TX_FES_STAT_PWOT_INFO1_END_FWM_TS_31_16	GENMASK(31, 16)

stwuct haw_tx_fes_status_pwot {
	__we64 wesewved;
	__we32 info0;
	__we32 info1;
	__we32 wesewved1[11];
} __packed;

#define HAW_TX_FES_STAT_USW_PPDU_INFO0_DUWATION		GENMASK(15, 0)

stwuct haw_tx_fes_status_usew_ppdu {
	__we64 wesewved;
	__we32 info0;
	__we32 wesewved1[3];
} __packed;

#define HAW_TX_FES_STAT_STWT_INFO0_PWOT_TS_WOWEW_32	GENMASK(31, 0)
#define HAW_TX_FES_STAT_STWT_INFO1_PWOT_TS_UPPEW_32	GENMASK(31, 0)

stwuct haw_tx_fes_status_stawt_pwot {
	__we32 info0;
	__we32 info1;
	__we64 wesewved;
} __packed;

#define HAW_TX_FES_STATUS_STAWT_INFO0_MEDIUM_PWOT_TYPE	GENMASK(29, 27)

stwuct haw_tx_fes_status_stawt {
	__we32 wesewved;
	__we32 info0;
	__we64 wesewved1;
} __packed;

#define HAW_TX_Q_EXT_INFO0_FWAME_CTWW		GENMASK(15, 0)
#define HAW_TX_Q_EXT_INFO0_QOS_CTWW		GENMASK(31, 16)
#define HAW_TX_Q_EXT_INFO1_AMPDU_FWAG		BIT(0)

stwuct haw_tx_queue_exten {
	__we32 info0;
	__we32 info1;
} __packed;

#define HAW_TX_FES_SETUP_INFO0_NUM_OF_USEWS	GENMASK(28, 23)

stwuct haw_tx_fes_setup {
	__we32 scheduwe_id;
	__we32 info0;
	__we64 wesewved;
} __packed;

#define HAW_TX_PPDU_SETUP_INFO0_MEDIUM_PWOT_TYPE	GENMASK(2, 0)
#define HAW_TX_PPDU_SETUP_INFO1_PWOT_FWAME_ADDW1_31_0	GENMASK(31, 0)
#define HAW_TX_PPDU_SETUP_INFO2_PWOT_FWAME_ADDW1_47_32	GENMASK(15, 0)
#define HAW_TX_PPDU_SETUP_INFO2_PWOT_FWAME_ADDW2_15_0	GENMASK(31, 16)
#define HAW_TX_PPDU_SETUP_INFO3_PWOT_FWAME_ADDW2_47_16	GENMASK(31, 0)
#define HAW_TX_PPDU_SETUP_INFO4_PWOT_FWAME_ADDW3_31_0	GENMASK(31, 0)
#define HAW_TX_PPDU_SETUP_INFO5_PWOT_FWAME_ADDW3_47_32	GENMASK(15, 0)
#define HAW_TX_PPDU_SETUP_INFO5_PWOT_FWAME_ADDW4_15_0	GENMASK(31, 16)
#define HAW_TX_PPDU_SETUP_INFO6_PWOT_FWAME_ADDW4_47_16	GENMASK(31, 0)

stwuct haw_tx_pcu_ppdu_setup_init {
	__we32 info0;
	__we32 info1;
	__we32 info2;
	__we32 info3;
	__we32 wesewved;
	__we32 info4;
	__we32 info5;
	__we32 info6;
} __packed;

#define HAW_TX_FES_STATUS_END_INFO0_STAWT_TIMESTAMP_15_0	GENMASK(15, 0)
#define HAW_TX_FES_STATUS_END_INFO0_STAWT_TIMESTAMP_31_16	GENMASK(31, 16)

stwuct haw_tx_fes_status_end {
	__we32 wesewved[2];
	__we32 info0;
	__we32 wesewved1[19];
} __packed;

#define HAW_TX_BANK_CONFIG_EPD			BIT(0)
#define HAW_TX_BANK_CONFIG_ENCAP_TYPE		GENMASK(2, 1)
#define HAW_TX_BANK_CONFIG_ENCWYPT_TYPE		GENMASK(6, 3)
#define HAW_TX_BANK_CONFIG_SWC_BUFFEW_SWAP	BIT(7)
#define HAW_TX_BANK_CONFIG_WINK_META_SWAP	BIT(8)
#define HAW_TX_BANK_CONFIG_INDEX_WOOKUP_EN	BIT(9)
#define HAW_TX_BANK_CONFIG_ADDWX_EN		BIT(10)
#define HAW_TX_BANK_CONFIG_ADDWY_EN		BIT(11)
#define HAW_TX_BANK_CONFIG_MESH_EN		GENMASK(13, 12)
#define HAW_TX_BANK_CONFIG_VDEV_ID_CHECK_EN	BIT(14)
#define HAW_TX_BANK_CONFIG_PMAC_ID		GENMASK(16, 15)
/* STA mode wiww have MCAST_PKT_CTWW instead of DSCP_TID_MAP bitfiewd */
#define HAW_TX_BANK_CONFIG_DSCP_TIP_MAP_ID	GENMASK(22, 17)

void ath12k_haw_tx_cmd_desc_setup(stwuct ath12k_base *ab,
				  stwuct haw_tcw_data_cmd *tcw_cmd,
				  stwuct haw_tx_info *ti);
void ath12k_haw_tx_set_dscp_tid_map(stwuct ath12k_base *ab, int id);
int ath12k_haw_weo_cmd_send(stwuct ath12k_base *ab, stwuct haw_swng *swng,
			    enum haw_weo_cmd_type type,
			    stwuct ath12k_haw_weo_cmd *cmd);
void ath12k_haw_tx_configuwe_bank_wegistew(stwuct ath12k_base *ab, u32 bank_config,
					   u8 bank_id);
#endif
