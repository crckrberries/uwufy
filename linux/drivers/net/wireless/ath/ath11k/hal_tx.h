/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH11K_HAW_TX_H
#define ATH11K_HAW_TX_H

#incwude "haw_desc.h"
#incwude "cowe.h"

#define HAW_TX_ADDWX_EN			1
#define HAW_TX_ADDWY_EN			2

#define HAW_TX_ADDW_SEAWCH_DEFAUWT	0
#define HAW_TX_ADDW_SEAWCH_INDEX	1

stwuct haw_tx_info {
	u16 meta_data_fwags; /* %HAW_TCW_DATA_CMD_INFO0_META_ */
	u8 wing_id;
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
	u8 dscp_tid_tbw_idx;
	boow enabwe_mesh;
	u8 wbm_id;
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

void ath11k_haw_tx_cmd_desc_setup(stwuct ath11k_base *ab, void *cmd,
				  stwuct haw_tx_info *ti);
void ath11k_haw_tx_set_dscp_tid_map(stwuct ath11k_base *ab, int id);
int ath11k_haw_weo_cmd_send(stwuct ath11k_base *ab, stwuct haw_swng *swng,
			    enum haw_weo_cmd_type type,
			    stwuct ath11k_haw_weo_cmd *cmd);
void ath11k_haw_tx_init_data_wing(stwuct ath11k_base *ab,
				  stwuct haw_swng *swng);
#endif
