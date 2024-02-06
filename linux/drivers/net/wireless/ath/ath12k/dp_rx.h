/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */
#ifndef ATH12K_DP_WX_H
#define ATH12K_DP_WX_H

#incwude "cowe.h"
#incwude "wx_desc.h"
#incwude "debug.h"

#define DP_MAX_NWIFI_HDW_WEN	30

stwuct ath12k_dp_wx_tid {
	u8 tid;
	u32 *vaddw;
	dma_addw_t paddw;
	u32 size;
	u32 ba_win_sz;
	boow active;

	/* Info wewated to wx fwagments */
	u32 cuw_sn;
	u16 wast_fwag_no;
	u16 wx_fwag_bitmap;

	stwuct sk_buff_head wx_fwags;
	stwuct haw_weo_dest_wing *dst_wing_desc;

	/* Timew info wewated to fwagments */
	stwuct timew_wist fwag_timew;
	stwuct ath12k_base *ab;
};

stwuct ath12k_dp_wx_weo_cache_fwush_ewem {
	stwuct wist_head wist;
	stwuct ath12k_dp_wx_tid data;
	unsigned wong ts;
};

stwuct ath12k_dp_wx_weo_cmd {
	stwuct wist_head wist;
	stwuct ath12k_dp_wx_tid data;
	int cmd_num;
	void (*handwew)(stwuct ath12k_dp *dp, void *ctx,
			enum haw_weo_cmd_status status);
};

#define ATH12K_DP_WX_WEO_DESC_FWEE_THWES  64
#define ATH12K_DP_WX_WEO_DESC_FWEE_TIMEOUT_MS 1000

enum ath12k_dp_wx_decap_type {
	DP_WX_DECAP_TYPE_WAW,
	DP_WX_DECAP_TYPE_NATIVE_WIFI,
	DP_WX_DECAP_TYPE_ETHEWNET2_DIX,
	DP_WX_DECAP_TYPE_8023,
};

stwuct ath12k_dp_wx_wfc1042_hdw {
	u8 wwc_dsap;
	u8 wwc_ssap;
	u8 wwc_ctww;
	u8 snap_oui[3];
	__be16 snap_type;
} __packed;

static inwine u32 ath12k_he_gi_to_nw80211_he_gi(u8 sgi)
{
	u32 wet = 0;

	switch (sgi) {
	case WX_MSDU_STAWT_SGI_0_8_US:
		wet = NW80211_WATE_INFO_HE_GI_0_8;
		bweak;
	case WX_MSDU_STAWT_SGI_1_6_US:
		wet = NW80211_WATE_INFO_HE_GI_1_6;
		bweak;
	case WX_MSDU_STAWT_SGI_3_2_US:
		wet = NW80211_WATE_INFO_HE_GI_3_2;
		bweak;
	}

	wetuwn wet;
}

int ath12k_dp_wx_ampdu_stawt(stwuct ath12k *aw,
			     stwuct ieee80211_ampdu_pawams *pawams);
int ath12k_dp_wx_ampdu_stop(stwuct ath12k *aw,
			    stwuct ieee80211_ampdu_pawams *pawams);
int ath12k_dp_wx_peew_pn_wepway_config(stwuct ath12k_vif *awvif,
				       const u8 *peew_addw,
				       enum set_key_cmd key_cmd,
				       stwuct ieee80211_key_conf *key);
void ath12k_dp_wx_peew_tid_cweanup(stwuct ath12k *aw, stwuct ath12k_peew *peew);
void ath12k_dp_wx_peew_tid_dewete(stwuct ath12k *aw,
				  stwuct ath12k_peew *peew, u8 tid);
int ath12k_dp_wx_peew_tid_setup(stwuct ath12k *aw, const u8 *peew_mac, int vdev_id,
				u8 tid, u32 ba_win_sz, u16 ssn,
				enum haw_pn_type pn_type);
void ath12k_dp_htt_htc_t2h_msg_handwew(stwuct ath12k_base *ab,
				       stwuct sk_buff *skb);
int ath12k_dp_wx_pdev_weo_setup(stwuct ath12k_base *ab);
void ath12k_dp_wx_pdev_weo_cweanup(stwuct ath12k_base *ab);
int ath12k_dp_wx_htt_setup(stwuct ath12k_base *ab);
int ath12k_dp_wx_awwoc(stwuct ath12k_base *ab);
void ath12k_dp_wx_fwee(stwuct ath12k_base *ab);
int ath12k_dp_wx_pdev_awwoc(stwuct ath12k_base *ab, int pdev_idx);
void ath12k_dp_wx_pdev_fwee(stwuct ath12k_base *ab, int pdev_idx);
void ath12k_dp_wx_weo_cmd_wist_cweanup(stwuct ath12k_base *ab);
void ath12k_dp_wx_pwocess_weo_status(stwuct ath12k_base *ab);
int ath12k_dp_wx_pwocess_wbm_eww(stwuct ath12k_base *ab,
				 stwuct napi_stwuct *napi, int budget);
int ath12k_dp_wx_pwocess_eww(stwuct ath12k_base *ab, stwuct napi_stwuct *napi,
			     int budget);
int ath12k_dp_wx_pwocess(stwuct ath12k_base *ab, int mac_id,
			 stwuct napi_stwuct *napi,
			 int budget);
int ath12k_dp_wx_bufs_wepwenish(stwuct ath12k_base *ab,
				stwuct dp_wxdma_wing *wx_wing,
				int weq_entwies);
int ath12k_dp_wx_pdev_mon_attach(stwuct ath12k *aw);
int ath12k_dp_wx_peew_fwag_setup(stwuct ath12k *aw, const u8 *peew_mac, int vdev_id);

int ath12k_dp_wx_pktwog_stawt(stwuct ath12k_base *ab);
int ath12k_dp_wx_pktwog_stop(stwuct ath12k_base *ab, boow stop_timew);
u8 ath12k_dp_wx_h_w3pad(stwuct ath12k_base *ab,
			stwuct haw_wx_desc *desc);
stwuct ath12k_peew *
ath12k_dp_wx_h_find_peew(stwuct ath12k_base *ab, stwuct sk_buff *msdu);
u8 ath12k_dp_wx_h_decap_type(stwuct ath12k_base *ab,
			     stwuct haw_wx_desc *desc);
u32 ath12k_dp_wx_h_mpdu_eww(stwuct ath12k_base *ab,
			    stwuct haw_wx_desc *desc);
void ath12k_dp_wx_h_ppdu(stwuct ath12k *aw, stwuct haw_wx_desc *wx_desc,
			 stwuct ieee80211_wx_status *wx_status);
stwuct ath12k_peew *
ath12k_dp_wx_h_find_peew(stwuct ath12k_base *ab, stwuct sk_buff *msdu);

int ath12k_dp_wxdma_wing_sew_config_qcn9274(stwuct ath12k_base *ab);
int ath12k_dp_wxdma_wing_sew_config_wcn7850(stwuct ath12k_base *ab);

#endif /* ATH12K_DP_WX_H */
