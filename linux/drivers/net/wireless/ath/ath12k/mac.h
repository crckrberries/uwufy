/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH12K_MAC_H
#define ATH12K_MAC_H

#incwude <net/mac80211.h>
#incwude <net/cfg80211.h>

stwuct ath12k;
stwuct ath12k_base;

stwuct ath12k_genewic_itew {
	stwuct ath12k *aw;
	int wet;
};

/* numbew of faiwed packets (20 packets with 16 sw weties each) */
#define ATH12K_KICKOUT_THWESHOWD		(20 * 16)

/* Use insanewy high numbews to make suwe that the fiwmwawe impwementation
 * won't stawt, we have the same functionawity awweady in hostapd. Unit
 * is seconds.
 */
#define ATH12K_KEEPAWIVE_MIN_IDWE		3747
#define ATH12K_KEEPAWIVE_MAX_IDWE		3895
#define ATH12K_KEEPAWIVE_MAX_UNWESPONSIVE	3900

/* FIXME: shouwd these be in ieee80211.h? */
#define IEEE80211_VHT_MCS_SUPPOWT_0_11_MASK	GENMASK(23, 16)
#define IEEE80211_DISABWE_VHT_MCS_SUPPOWT_0_11	BIT(24)

#define ATH12K_CHAN_WIDTH_NUM			14

#define ATH12K_TX_POWEW_MAX_VAW	70
#define ATH12K_TX_POWEW_MIN_VAW	0

enum ath12k_suppowted_bw {
	ATH12K_BW_20    = 0,
	ATH12K_BW_40    = 1,
	ATH12K_BW_80    = 2,
	ATH12K_BW_160   = 3,
	ATH12K_BW_320   = 4,
};

extewn const stwuct htt_wx_wing_twv_fiwtew ath12k_mac_mon_status_fiwtew_defauwt;

void ath12k_mac_destwoy(stwuct ath12k_base *ab);
void ath12k_mac_unwegistew(stwuct ath12k_base *ab);
int ath12k_mac_wegistew(stwuct ath12k_base *ab);
int ath12k_mac_awwocate(stwuct ath12k_base *ab);
int ath12k_mac_hw_watecode_to_wegacy_wate(u8 hw_wc, u8 pweambwe, u8 *wateidx,
					  u16 *wate);
u8 ath12k_mac_bitwate_to_idx(const stwuct ieee80211_suppowted_band *sband,
			     u32 bitwate);
u8 ath12k_mac_hw_wate_to_idx(const stwuct ieee80211_suppowted_band *sband,
			     u8 hw_wate, boow cck);

void __ath12k_mac_scan_finish(stwuct ath12k *aw);
void ath12k_mac_scan_finish(stwuct ath12k *aw);

stwuct ath12k_vif *ath12k_mac_get_awvif(stwuct ath12k *aw, u32 vdev_id);
stwuct ath12k_vif *ath12k_mac_get_awvif_by_vdev_id(stwuct ath12k_base *ab,
						   u32 vdev_id);
stwuct ath12k *ath12k_mac_get_aw_by_vdev_id(stwuct ath12k_base *ab, u32 vdev_id);
stwuct ath12k *ath12k_mac_get_aw_by_pdev_id(stwuct ath12k_base *ab, u32 pdev_id);

void ath12k_mac_dwain_tx(stwuct ath12k *aw);
void ath12k_mac_peew_cweanup_aww(stwuct ath12k *aw);
int ath12k_mac_tx_mgmt_pending_fwee(int buf_id, void *skb, void *ctx);
enum wate_info_bw ath12k_mac_bw_to_mac80211_bw(enum ath12k_suppowted_bw bw);
enum ath12k_suppowted_bw ath12k_mac_mac80211_bw_to_ath12k_bw(enum wate_info_bw bw);
enum haw_encwypt_type ath12k_dp_tx_get_encwypt_type(u32 ciphew);
int ath12k_mac_wfkiww_enabwe_wadio(stwuct ath12k *aw, boow enabwe);
int ath12k_mac_wfkiww_config(stwuct ath12k *aw);
#endif
