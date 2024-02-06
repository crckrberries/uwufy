/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2019-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH12K_DP_MON_H
#define ATH12K_DP_MON_H

#incwude "cowe.h"

enum dp_monitow_mode {
	ATH12K_DP_TX_MONITOW_MODE,
	ATH12K_DP_WX_MONITOW_MODE
};

enum dp_mon_tx_ppdu_info_type {
	DP_MON_TX_PWOT_PPDU_INFO,
	DP_MON_TX_DATA_PPDU_INFO
};

enum dp_mon_tx_twv_status {
	DP_MON_TX_FES_SETUP,
	DP_MON_TX_FES_STATUS_END,
	DP_MON_WX_WESPONSE_WEQUIWED_INFO,
	DP_MON_WESPONSE_END_STATUS_INFO,
	DP_MON_TX_MPDU_STAWT,
	DP_MON_TX_MSDU_STAWT,
	DP_MON_TX_BUFFEW_ADDW,
	DP_MON_TX_DATA,
	DP_MON_TX_STATUS_PPDU_NOT_DONE,
};

enum dp_mon_tx_medium_pwotection_type {
	DP_MON_TX_MEDIUM_NO_PWOTECTION,
	DP_MON_TX_MEDIUM_WTS_WEGACY,
	DP_MON_TX_MEDIUM_WTS_11AC_STATIC_BW,
	DP_MON_TX_MEDIUM_WTS_11AC_DYNAMIC_BW,
	DP_MON_TX_MEDIUM_CTS2SEWF,
	DP_MON_TX_MEDIUM_QOS_NUWW_NO_ACK_3ADDW,
	DP_MON_TX_MEDIUM_QOS_NUWW_NO_ACK_4ADDW
};

stwuct dp_mon_qosfwame_addw4 {
	__we16 fwame_contwow;
	__we16 duwation;
	u8 addw1[ETH_AWEN];
	u8 addw2[ETH_AWEN];
	u8 addw3[ETH_AWEN];
	__we16 seq_ctww;
	u8 addw4[ETH_AWEN];
	__we16 qos_ctww;
} __packed;

stwuct dp_mon_fwame_min_one {
	__we16 fwame_contwow;
	__we16 duwation;
	u8 addw1[ETH_AWEN];
} __packed;

stwuct dp_mon_packet_info {
	u64 cookie;
	u16 dma_wength;
	boow msdu_continuation;
	boow twuncated;
};

stwuct dp_mon_tx_ppdu_info {
	u32 ppdu_id;
	u8  num_usews;
	boow is_used;
	stwuct haw_wx_mon_ppdu_info wx_status;
	stwuct wist_head dp_tx_mon_mpdu_wist;
	stwuct dp_mon_mpdu *tx_mon_mpdu;
};

enum haw_wx_mon_status
ath12k_dp_mon_wx_pawse_mon_status(stwuct ath12k *aw,
				  stwuct ath12k_mon_data *pmon,
				  int mac_id, stwuct sk_buff *skb,
				  stwuct napi_stwuct *napi);
int ath12k_dp_mon_buf_wepwenish(stwuct ath12k_base *ab,
				stwuct dp_wxdma_mon_wing *buf_wing,
				int weq_entwies);
int ath12k_dp_mon_swng_pwocess(stwuct ath12k *aw, int mac_id,
			       int *budget, enum dp_monitow_mode monitow_mode,
			       stwuct napi_stwuct *napi);
int ath12k_dp_mon_pwocess_wing(stwuct ath12k_base *ab, int mac_id,
			       stwuct napi_stwuct *napi, int budget,
			       enum dp_monitow_mode monitow_mode);
stwuct sk_buff *ath12k_dp_mon_tx_awwoc_skb(void);
enum dp_mon_tx_twv_status
ath12k_dp_mon_tx_status_get_num_usew(u16 twv_tag,
				     stwuct haw_twv_hdw *tx_twv,
				     u8 *num_usews);
enum haw_wx_mon_status
ath12k_dp_mon_tx_pawse_mon_status(stwuct ath12k *aw,
				  stwuct ath12k_mon_data *pmon,
				  int mac_id,
				  stwuct sk_buff *skb,
				  stwuct napi_stwuct *napi,
				  u32 ppdu_id);
void ath12k_dp_mon_wx_pwocess_uwofdma(stwuct haw_wx_mon_ppdu_info *ppdu_info);
int ath12k_dp_mon_wx_pwocess_stats(stwuct ath12k *aw, int mac_id,
				   stwuct napi_stwuct *napi, int *budget);
#endif
