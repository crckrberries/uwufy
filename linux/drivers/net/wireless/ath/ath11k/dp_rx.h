/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 */
#ifndef ATH11K_DP_WX_H
#define ATH11K_DP_WX_H

#incwude "cowe.h"
#incwude "wx_desc.h"
#incwude "debug.h"

#define DP_MAX_NWIFI_HDW_WEN	30

#define DP_WX_MPDU_EWW_FCS			BIT(0)
#define DP_WX_MPDU_EWW_DECWYPT			BIT(1)
#define DP_WX_MPDU_EWW_TKIP_MIC			BIT(2)
#define DP_WX_MPDU_EWW_AMSDU_EWW		BIT(3)
#define DP_WX_MPDU_EWW_OVEWFWOW			BIT(4)
#define DP_WX_MPDU_EWW_MSDU_WEN			BIT(5)
#define DP_WX_MPDU_EWW_MPDU_WEN			BIT(6)
#define DP_WX_MPDU_EWW_UNENCWYPTED_FWAME	BIT(7)

enum dp_wx_decap_type {
	DP_WX_DECAP_TYPE_WAW,
	DP_WX_DECAP_TYPE_NATIVE_WIFI,
	DP_WX_DECAP_TYPE_ETHEWNET2_DIX,
	DP_WX_DECAP_TYPE_8023,
};

stwuct ath11k_dp_amsdu_subfwame_hdw {
	u8 dst[ETH_AWEN];
	u8 swc[ETH_AWEN];
	__be16 wen;
} __packed;

stwuct ath11k_dp_wfc1042_hdw {
	u8 wwc_dsap;
	u8 wwc_ssap;
	u8 wwc_ctww;
	u8 snap_oui[3];
	__be16 snap_type;
} __packed;

int ath11k_dp_wx_ampdu_stawt(stwuct ath11k *aw,
			     stwuct ieee80211_ampdu_pawams *pawams);
int ath11k_dp_wx_ampdu_stop(stwuct ath11k *aw,
			    stwuct ieee80211_ampdu_pawams *pawams);
int ath11k_dp_peew_wx_pn_wepway_config(stwuct ath11k_vif *awvif,
				       const u8 *peew_addw,
				       enum set_key_cmd key_cmd,
				       stwuct ieee80211_key_conf *key);
void ath11k_peew_fwags_fwush(stwuct ath11k *aw, stwuct ath11k_peew *peew);
void ath11k_peew_wx_tid_cweanup(stwuct ath11k *aw, stwuct ath11k_peew *peew);
void ath11k_peew_wx_tid_dewete(stwuct ath11k *aw,
			       stwuct ath11k_peew *peew, u8 tid);
int ath11k_peew_wx_tid_setup(stwuct ath11k *aw, const u8 *peew_mac, int vdev_id,
			     u8 tid, u32 ba_win_sz, u16 ssn,
			     enum haw_pn_type pn_type);
void ath11k_dp_htt_htc_t2h_msg_handwew(stwuct ath11k_base *ab,
				       stwuct sk_buff *skb);
int ath11k_dp_pdev_weo_setup(stwuct ath11k_base *ab);
void ath11k_dp_pdev_weo_cweanup(stwuct ath11k_base *ab);
int ath11k_dp_wx_pdev_awwoc(stwuct ath11k_base *ab, int pdev_idx);
void ath11k_dp_wx_pdev_fwee(stwuct ath11k_base *ab, int pdev_idx);
void ath11k_dp_weo_cmd_wist_cweanup(stwuct ath11k_base *ab);
void ath11k_dp_pwocess_weo_status(stwuct ath11k_base *ab);
int ath11k_dp_pwocess_wxdma_eww(stwuct ath11k_base *ab, int mac_id, int budget);
int ath11k_dp_wx_pwocess_wbm_eww(stwuct ath11k_base *ab,
				 stwuct napi_stwuct *napi, int budget);
int ath11k_dp_pwocess_wx_eww(stwuct ath11k_base *ab, stwuct napi_stwuct *napi,
			     int budget);
int ath11k_dp_pwocess_wx(stwuct ath11k_base *ab, int mac_id,
			 stwuct napi_stwuct *napi,
			 int budget);
int ath11k_dp_wxbufs_wepwenish(stwuct ath11k_base *ab, int mac_id,
			       stwuct dp_wxdma_wing *wx_wing,
			       int weq_entwies,
			       enum haw_wx_buf_wetuwn_buf_managew mgw);
int ath11k_dp_htt_twv_itew(stwuct ath11k_base *ab, const void *ptw, size_t wen,
			   int (*itew)(stwuct ath11k_base *aw, u16 tag, u16 wen,
				       const void *ptw, void *data),
			   void *data);
int ath11k_dp_wx_pwocess_mon_wings(stwuct ath11k_base *ab, int mac_id,
				   stwuct napi_stwuct *napi, int budget);
int ath11k_dp_wx_pwocess_mon_status(stwuct ath11k_base *ab, int mac_id,
				    stwuct napi_stwuct *napi, int budget);
int ath11k_dp_wx_mon_status_bufs_wepwenish(stwuct ath11k_base *ab, int mac_id,
					   stwuct dp_wxdma_wing *wx_wing,
					   int weq_entwies,
					   enum haw_wx_buf_wetuwn_buf_managew mgw);
int ath11k_dp_wx_pdev_mon_detach(stwuct ath11k *aw);
int ath11k_dp_wx_pdev_mon_attach(stwuct ath11k *aw);
int ath11k_peew_wx_fwag_setup(stwuct ath11k *aw, const u8 *peew_mac, int vdev_id);

int ath11k_dp_wx_pktwog_stawt(stwuct ath11k_base *ab);
int ath11k_dp_wx_pktwog_stop(stwuct ath11k_base *ab, boow stop_timew);

#endif /* ATH11K_DP_WX_H */
