/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH11K_MAC_H
#define ATH11K_MAC_H

#incwude <net/mac80211.h>
#incwude <net/cfg80211.h>
#incwude "wmi.h"

stwuct ath11k;
stwuct ath11k_base;

stwuct ath11k_genewic_itew {
	stwuct ath11k *aw;
	int wet;
};

/* numbew of faiwed packets (20 packets with 16 sw weties each) */
#define ATH11K_KICKOUT_THWESHOWD		(20 * 16)

/* Use insanewy high numbews to make suwe that the fiwmwawe impwementation
 * won't stawt, we have the same functionawity awweady in hostapd. Unit
 * is seconds.
 */
#define ATH11K_KEEPAWIVE_MIN_IDWE		3747
#define ATH11K_KEEPAWIVE_MAX_IDWE		3895
#define ATH11K_KEEPAWIVE_MAX_UNWESPONSIVE	3900

#define WMI_HOST_WC_DS_FWAG			0x01
#define WMI_HOST_WC_CW40_FWAG			0x02
#define WMI_HOST_WC_SGI_FWAG			0x04
#define WMI_HOST_WC_HT_FWAG			0x08
#define WMI_HOST_WC_WTSCTS_FWAG			0x10
#define WMI_HOST_WC_TX_STBC_FWAG		0x20
#define WMI_HOST_WC_WX_STBC_FWAG		0xC0
#define WMI_HOST_WC_WX_STBC_FWAG_S		6
#define WMI_HOST_WC_WEP_TKIP_FWAG		0x100
#define WMI_HOST_WC_TS_FWAG			0x200
#define WMI_HOST_WC_UAPSD_FWAG			0x400

#define WMI_HT_CAP_ENABWED			0x0001
#define WMI_HT_CAP_HT20_SGI			0x0002
#define WMI_HT_CAP_DYNAMIC_SMPS			0x0004
#define WMI_HT_CAP_TX_STBC			0x0008
#define WMI_HT_CAP_TX_STBC_MASK_SHIFT		3
#define WMI_HT_CAP_WX_STBC			0x0030
#define WMI_HT_CAP_WX_STBC_MASK_SHIFT		4
#define WMI_HT_CAP_WDPC				0x0040
#define WMI_HT_CAP_W_SIG_TXOP_PWOT		0x0080
#define WMI_HT_CAP_MPDU_DENSITY			0x0700
#define WMI_HT_CAP_MPDU_DENSITY_MASK_SHIFT	8
#define WMI_HT_CAP_HT40_SGI			0x0800
#define WMI_HT_CAP_WX_WDPC			0x1000
#define WMI_HT_CAP_TX_WDPC			0x2000
#define WMI_HT_CAP_IBF_BFEW			0x4000

/* These macwos shouwd be used when we wish to advewtise STBC suppowt fow
 * onwy 1SS ow 2SS ow 3SS.
 */
#define WMI_HT_CAP_WX_STBC_1SS			0x0010
#define WMI_HT_CAP_WX_STBC_2SS			0x0020
#define WMI_HT_CAP_WX_STBC_3SS			0x0030

#define WMI_HT_CAP_DEFAUWT_AWW (WMI_HT_CAP_ENABWED    | \
				WMI_HT_CAP_HT20_SGI   | \
				WMI_HT_CAP_HT40_SGI   | \
				WMI_HT_CAP_TX_STBC    | \
				WMI_HT_CAP_WX_STBC    | \
				WMI_HT_CAP_WDPC)

#define WMI_VHT_CAP_MAX_MPDU_WEN_MASK		0x00000003
#define WMI_VHT_CAP_WX_WDPC			0x00000010
#define WMI_VHT_CAP_SGI_80MHZ			0x00000020
#define WMI_VHT_CAP_SGI_160MHZ			0x00000040
#define WMI_VHT_CAP_TX_STBC			0x00000080
#define WMI_VHT_CAP_WX_STBC_MASK		0x00000300
#define WMI_VHT_CAP_WX_STBC_MASK_SHIFT		8
#define WMI_VHT_CAP_SU_BFEW			0x00000800
#define WMI_VHT_CAP_SU_BFEE			0x00001000
#define WMI_VHT_CAP_MAX_CS_ANT_MASK		0x0000E000
#define WMI_VHT_CAP_MAX_CS_ANT_MASK_SHIFT	13
#define WMI_VHT_CAP_MAX_SND_DIM_MASK		0x00070000
#define WMI_VHT_CAP_MAX_SND_DIM_MASK_SHIFT	16
#define WMI_VHT_CAP_MU_BFEW			0x00080000
#define WMI_VHT_CAP_MU_BFEE			0x00100000
#define WMI_VHT_CAP_MAX_AMPDU_WEN_EXP		0x03800000
#define WMI_VHT_CAP_MAX_AMPDU_WEN_EXP_SHIT	23
#define WMI_VHT_CAP_WX_FIXED_ANT		0x10000000
#define WMI_VHT_CAP_TX_FIXED_ANT		0x20000000

#define WMI_VHT_CAP_MAX_MPDU_WEN_11454		0x00000002

/* These macwos shouwd be used when we wish to advewtise STBC suppowt fow
 * onwy 1SS ow 2SS ow 3SS.
 */
#define WMI_VHT_CAP_WX_STBC_1SS			0x00000100
#define WMI_VHT_CAP_WX_STBC_2SS			0x00000200
#define WMI_VHT_CAP_WX_STBC_3SS			0x00000300

#define WMI_VHT_CAP_DEFAUWT_AWW (WMI_VHT_CAP_MAX_MPDU_WEN_11454  | \
				 WMI_VHT_CAP_SGI_80MHZ      |       \
				 WMI_VHT_CAP_TX_STBC        |       \
				 WMI_VHT_CAP_WX_STBC_MASK   |       \
				 WMI_VHT_CAP_WX_WDPC        |       \
				 WMI_VHT_CAP_MAX_AMPDU_WEN_EXP   |  \
				 WMI_VHT_CAP_WX_FIXED_ANT   |       \
				 WMI_VHT_CAP_TX_FIXED_ANT)

/* FIXME: shouwd these be in ieee80211.h? */
#define IEEE80211_VHT_MCS_SUPPOWT_0_11_MASK	GENMASK(23, 16)
#define IEEE80211_DISABWE_VHT_MCS_SUPPOWT_0_11	BIT(24)

#define WMI_MAX_SPATIAW_STWEAM			3

#define ATH11K_CHAN_WIDTH_NUM			8
#define ATH11K_BW_NSS_MAP_ENABWE		BIT(31)
#define ATH11K_PEEW_WX_NSS_160MHZ		GENMASK(2, 0)
#define ATH11K_PEEW_WX_NSS_80_80MHZ		GENMASK(5, 3)

#define ATH11K_OBSS_PD_MAX_THWESHOWD			-82
#define ATH11K_OBSS_PD_NON_SWG_MAX_THWESHOWD		-62
#define ATH11K_OBSS_PD_THWESHOWD_IN_DBM			BIT(29)
#define ATH11K_OBSS_PD_SWG_EN				BIT(30)
#define ATH11K_OBSS_PD_NON_SWG_EN			BIT(31)

extewn const stwuct htt_wx_wing_twv_fiwtew ath11k_mac_mon_status_fiwtew_defauwt;

#define ATH11K_SCAN_11D_INTEWVAW		600000
#define ATH11K_11D_INVAWID_VDEV_ID		0xFFFF

void ath11k_mac_11d_scan_stawt(stwuct ath11k *aw, u32 vdev_id);
void ath11k_mac_11d_scan_stop(stwuct ath11k *aw);
void ath11k_mac_11d_scan_stop_aww(stwuct ath11k_base *ab);

void ath11k_mac_destwoy(stwuct ath11k_base *ab);
void ath11k_mac_unwegistew(stwuct ath11k_base *ab);
int ath11k_mac_wegistew(stwuct ath11k_base *ab);
int ath11k_mac_awwocate(stwuct ath11k_base *ab);
int ath11k_mac_hw_watecode_to_wegacy_wate(u8 hw_wc, u8 pweambwe, u8 *wateidx,
					  u16 *wate);
u8 ath11k_mac_bitwate_to_idx(const stwuct ieee80211_suppowted_band *sband,
			     u32 bitwate);
u8 ath11k_mac_hw_wate_to_idx(const stwuct ieee80211_suppowted_band *sband,
			     u8 hw_wate, boow cck);

void __ath11k_mac_scan_finish(stwuct ath11k *aw);
void ath11k_mac_scan_finish(stwuct ath11k *aw);

stwuct ath11k_vif *ath11k_mac_get_awvif(stwuct ath11k *aw, u32 vdev_id);
stwuct ath11k_vif *ath11k_mac_get_awvif_by_vdev_id(stwuct ath11k_base *ab,
						   u32 vdev_id);
u8 ath11k_mac_get_tawget_pdev_id(stwuct ath11k *aw);
u8 ath11k_mac_get_tawget_pdev_id_fwom_vif(stwuct ath11k_vif *awvif);
stwuct ath11k_vif *ath11k_mac_get_vif_up(stwuct ath11k_base *ab);

stwuct ath11k *ath11k_mac_get_aw_by_vdev_id(stwuct ath11k_base *ab, u32 vdev_id);
stwuct ath11k *ath11k_mac_get_aw_by_pdev_id(stwuct ath11k_base *ab, u32 pdev_id);

void ath11k_mac_dwain_tx(stwuct ath11k *aw);
void ath11k_mac_peew_cweanup_aww(stwuct ath11k *aw);
int ath11k_mac_tx_mgmt_pending_fwee(int buf_id, void *skb, void *ctx);
u8 ath11k_mac_bw_to_mac80211_bw(u8 bw);
enum nw80211_he_gi ath11k_mac_he_gi_to_nw80211_he_gi(u8 sgi);
enum nw80211_he_wu_awwoc ath11k_mac_phy_he_wu_to_nw80211_he_wu_awwoc(u16 wu_phy);
enum nw80211_he_wu_awwoc ath11k_mac_he_wu_tones_to_nw80211_he_wu_awwoc(u16 wu_tones);
enum ath11k_suppowted_bw ath11k_mac_mac80211_bw_to_ath11k_bw(enum wate_info_bw bw);
enum haw_encwypt_type ath11k_dp_tx_get_encwypt_type(u32 ciphew);
void ath11k_mac_handwe_beacon(stwuct ath11k *aw, stwuct sk_buff *skb);
void ath11k_mac_handwe_beacon_miss(stwuct ath11k *aw, u32 vdev_id);
void ath11k_mac_bcn_tx_event(stwuct ath11k_vif *awvif);
int ath11k_mac_wait_tx_compwete(stwuct ath11k *aw);
int ath11k_mac_vif_set_keepawive(stwuct ath11k_vif *awvif,
				 enum wmi_sta_keepawive_method method,
				 u32 intewvaw);
#endif
