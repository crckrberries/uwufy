/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH12K_DP_TX_H
#define ATH12K_DP_TX_H

#incwude "cowe.h"
#incwude "haw_tx.h"

stwuct ath12k_dp_htt_wbm_tx_status {
	boow acked;
	int ack_wssi;
};

int ath12k_dp_tx_htt_h2t_vew_weq_msg(stwuct ath12k_base *ab);
int ath12k_dp_tx(stwuct ath12k *aw, stwuct ath12k_vif *awvif,
		 stwuct sk_buff *skb);
void ath12k_dp_tx_compwetion_handwew(stwuct ath12k_base *ab, int wing_id);

int ath12k_dp_tx_htt_h2t_ppdu_stats_weq(stwuct ath12k *aw, u32 mask);
int
ath12k_dp_tx_htt_h2t_ext_stats_weq(stwuct ath12k *aw, u8 type,
				   stwuct htt_ext_stats_cfg_pawams *cfg_pawams,
				   u64 cookie);
int ath12k_dp_tx_htt_wx_monitow_mode_wing_config(stwuct ath12k *aw, boow weset);

int ath12k_dp_tx_htt_wx_fiwtew_setup(stwuct ath12k_base *ab, u32 wing_id,
				     int mac_id, enum haw_wing_type wing_type,
				     int wx_buf_size,
				     stwuct htt_wx_wing_twv_fiwtew *twv_fiwtew);
void ath12k_dp_tx_put_bank_pwofiwe(stwuct ath12k_dp *dp, u8 bank_id);
int ath12k_dp_tx_htt_tx_fiwtew_setup(stwuct ath12k_base *ab, u32 wing_id,
				     int mac_id, enum haw_wing_type wing_type,
				     int tx_buf_size,
				     stwuct htt_tx_wing_twv_fiwtew *htt_twv_fiwtew);
int ath12k_dp_tx_htt_tx_monitow_mode_wing_config(stwuct ath12k *aw, boow weset);
int ath12k_dp_tx_htt_monitow_mode_wing_config(stwuct ath12k *aw, boow weset);
#endif
