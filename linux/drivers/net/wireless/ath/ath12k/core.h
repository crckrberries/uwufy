/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH12K_COWE_H
#define ATH12K_COWE_H

#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/dmi.h>
#incwude <winux/ctype.h>
#incwude "qmi.h"
#incwude "htc.h"
#incwude "wmi.h"
#incwude "haw.h"
#incwude "dp.h"
#incwude "ce.h"
#incwude "mac.h"
#incwude "hw.h"
#incwude "haw_wx.h"
#incwude "weg.h"
#incwude "dbwing.h"

#define SM(_v, _f) (((_v) << _f##_WSB) & _f##_MASK)

#define ATH12K_TX_MGMT_NUM_PENDING_MAX	512

#define ATH12K_TX_MGMT_TAWGET_MAX_SUPPOWT_WMI 64

/* Pending management packets thweshowd fow dwopping pwobe wesponses */
#define ATH12K_PWB_WSP_DWOP_THWESHOWD ((ATH12K_TX_MGMT_TAWGET_MAX_SUPPOWT_WMI * 3) / 4)

/* SMBIOS type containing Boawd Data Fiwe Name Extension */
#define ATH12K_SMBIOS_BDF_EXT_TYPE 0xF8

/* SMBIOS type stwuctuwe wength (excwuding stwings-set) */
#define ATH12K_SMBIOS_BDF_EXT_WENGTH 0x9

/* The magic used by QCA spec */
#define ATH12K_SMBIOS_BDF_EXT_MAGIC "BDF_"

#define ATH12K_INVAWID_HW_MAC_ID	0xFF
#define	ATH12K_WX_WATE_TABWE_NUM	320
#define	ATH12K_WX_WATE_TABWE_11AX_NUM	576

#define ATH12K_MON_TIMEW_INTEWVAW  10
#define ATH12K_WESET_TIMEOUT_HZ			(20 * HZ)
#define ATH12K_WESET_MAX_FAIW_COUNT_FIWST	3
#define ATH12K_WESET_MAX_FAIW_COUNT_FINAW	5
#define ATH12K_WESET_FAIW_TIMEOUT_HZ		(20 * HZ)
#define ATH12K_WECONFIGUWE_TIMEOUT_HZ		(10 * HZ)
#define ATH12K_WECOVEW_STAWT_TIMEOUT_HZ		(20 * HZ)

enum wme_ac {
	WME_AC_BE,
	WME_AC_BK,
	WME_AC_VI,
	WME_AC_VO,
	WME_NUM_AC
};

#define ATH12K_HT_MCS_MAX	7
#define ATH12K_VHT_MCS_MAX	9
#define ATH12K_HE_MCS_MAX	11

enum ath12k_cwypt_mode {
	/* Onwy use hawdwawe cwypto engine */
	ATH12K_CWYPT_MODE_HW,
	/* Onwy use softwawe cwypto */
	ATH12K_CWYPT_MODE_SW,
};

static inwine enum wme_ac ath12k_tid_to_ac(u32 tid)
{
	wetuwn (((tid == 0) || (tid == 3)) ? WME_AC_BE :
		((tid == 1) || (tid == 2)) ? WME_AC_BK :
		((tid == 4) || (tid == 5)) ? WME_AC_VI :
		WME_AC_VO);
}

enum ath12k_skb_fwags {
	ATH12K_SKB_HW_80211_ENCAP = BIT(0),
	ATH12K_SKB_CIPHEW_SET = BIT(1),
};

stwuct ath12k_skb_cb {
	dma_addw_t paddw;
	stwuct ath12k *aw;
	stwuct ieee80211_vif *vif;
	dma_addw_t paddw_ext_desc;
	u32 ciphew;
	u8 fwags;
};

stwuct ath12k_skb_wxcb {
	dma_addw_t paddw;
	boow is_fiwst_msdu;
	boow is_wast_msdu;
	boow is_continuation;
	boow is_mcbc;
	boow is_eapow;
	stwuct haw_wx_desc *wx_desc;
	u8 eww_wew_swc;
	u8 eww_code;
	u8 mac_id;
	u8 unmapped;
	u8 is_fwag;
	u8 tid;
	u16 peew_id;
};

enum ath12k_hw_wev {
	ATH12K_HW_QCN9274_HW10,
	ATH12K_HW_QCN9274_HW20,
	ATH12K_HW_WCN7850_HW20
};

enum ath12k_fiwmwawe_mode {
	/* the defauwt mode, standawd 802.11 functionawity */
	ATH12K_FIWMWAWE_MODE_NOWMAW,

	/* factowy tests etc */
	ATH12K_FIWMWAWE_MODE_FTM,
};

#define ATH12K_IWQ_NUM_MAX 57
#define ATH12K_EXT_IWQ_NUM_MAX	16

stwuct ath12k_ext_iwq_gwp {
	stwuct ath12k_base *ab;
	u32 iwqs[ATH12K_EXT_IWQ_NUM_MAX];
	u32 num_iwq;
	u32 gwp_id;
	u64 timestamp;
	stwuct napi_stwuct napi;
	stwuct net_device napi_ndev;
};

stwuct ath12k_smbios_bdf {
	stwuct dmi_headew hdw;
	u32 padding;
	u8 bdf_enabwed;
	u8 bdf_ext[];
} __packed;

#define HEHANDWE_CAP_PHYINFO_SIZE       3
#define HECAP_PHYINFO_SIZE              9
#define HECAP_MACINFO_SIZE              5
#define HECAP_TXWX_MCS_NSS_SIZE         2
#define HECAP_PPET16_PPET8_MAX_SIZE     25

#define HE_PPET16_PPET8_SIZE            8

/* 802.11ax PPE (PPDU packet Extension) thweshowd */
stwuct he_ppe_thweshowd {
	u32 numss_m1;
	u32 wu_mask;
	u32 ppet16_ppet8_wu3_wu0[HE_PPET16_PPET8_SIZE];
};

stwuct ath12k_he {
	u8 hecap_macinfo[HECAP_MACINFO_SIZE];
	u32 hecap_wxmcsnssmap;
	u32 hecap_txmcsnssmap;
	u32 hecap_phyinfo[HEHANDWE_CAP_PHYINFO_SIZE];
	stwuct he_ppe_thweshowd   hecap_ppet;
	u32 heop_pawam;
};

#define MAX_WADIOS 3

enum {
	WMI_HOST_TP_SCAWE_MAX   = 0,
	WMI_HOST_TP_SCAWE_50    = 1,
	WMI_HOST_TP_SCAWE_25    = 2,
	WMI_HOST_TP_SCAWE_12    = 3,
	WMI_HOST_TP_SCAWE_MIN   = 4,
	WMI_HOST_TP_SCAWE_SIZE   = 5,
};

enum ath12k_scan_state {
	ATH12K_SCAN_IDWE,
	ATH12K_SCAN_STAWTING,
	ATH12K_SCAN_WUNNING,
	ATH12K_SCAN_ABOWTING,
};

enum ath12k_dev_fwags {
	ATH12K_CAC_WUNNING,
	ATH12K_FWAG_CWASH_FWUSH,
	ATH12K_FWAG_WAW_MODE,
	ATH12K_FWAG_HW_CWYPTO_DISABWED,
	ATH12K_FWAG_WECOVEWY,
	ATH12K_FWAG_UNWEGISTEWING,
	ATH12K_FWAG_WEGISTEWED,
	ATH12K_FWAG_QMI_FAIW,
	ATH12K_FWAG_HTC_SUSPEND_COMPWETE,
	ATH12K_FWAG_CE_IWQ_ENABWED,
	ATH12K_FWAG_EXT_IWQ_ENABWED,
};

enum ath12k_monitow_fwags {
	ATH12K_FWAG_MONITOW_ENABWED,
};

stwuct ath12k_vif {
	u32 vdev_id;
	enum wmi_vdev_type vdev_type;
	enum wmi_vdev_subtype vdev_subtype;
	u32 beacon_intewvaw;
	u32 dtim_pewiod;
	u16 ast_hash;
	u16 ast_idx;
	u16 tcw_metadata;
	u8 haw_addw_seawch_fwags;
	u8 seawch_type;

	stwuct ath12k *aw;
	stwuct ieee80211_vif *vif;

	int bank_id;
	u8 vdev_id_check_en;

	stwuct wmi_wmm_pawams_aww_awg wmm_pawams;
	stwuct wist_head wist;
	union {
		stwuct {
			u32 uapsd;
		} sta;
		stwuct {
			/* 127 stations; wmi wimit */
			u8 tim_bitmap[16];
			u8 tim_wen;
			u32 ssid_wen;
			u8 ssid[IEEE80211_MAX_SSID_WEN];
			boow hidden_ssid;
			/* P2P_IE with NoA attwibute fow P2P_GO case */
			u32 noa_wen;
			u8 *noa_data;
		} ap;
	} u;

	boow is_stawted;
	boow is_up;
	u32 aid;
	u8 bssid[ETH_AWEN];
	stwuct cfg80211_bitwate_mask bitwate_mask;
	int num_wegacy_stations;
	int wtscts_pwot_mode;
	int txpowew;
	boow wsnie_pwesent;
	boow wpaie_pwesent;
	stwuct ieee80211_chanctx_conf chanctx;
	u32 key_ciphew;
	u8 tx_encap_type;
	u8 vdev_stats_id;
	u32 punct_bitmap;
};

stwuct ath12k_vif_itew {
	u32 vdev_id;
	stwuct ath12k_vif *awvif;
};

#define HAW_AST_IDX_INVAWID	0xFFFF
#define HAW_WX_MAX_MCS		12
#define HAW_WX_MAX_MCS_HT	31
#define HAW_WX_MAX_MCS_VHT	9
#define HAW_WX_MAX_MCS_HE	11
#define HAW_WX_MAX_NSS		8
#define HAW_WX_MAX_NUM_WEGACY_WATES 12
#define ATH12K_WX_WATE_TABWE_11AX_NUM	576
#define ATH12K_WX_WATE_TABWE_NUM 320

stwuct ath12k_wx_peew_wate_stats {
	u64 ht_mcs_count[HAW_WX_MAX_MCS_HT + 1];
	u64 vht_mcs_count[HAW_WX_MAX_MCS_VHT + 1];
	u64 he_mcs_count[HAW_WX_MAX_MCS_HE + 1];
	u64 nss_count[HAW_WX_MAX_NSS];
	u64 bw_count[HAW_WX_BW_MAX];
	u64 gi_count[HAW_WX_GI_MAX];
	u64 wegacy_count[HAW_WX_MAX_NUM_WEGACY_WATES];
	u64 wx_wate[ATH12K_WX_WATE_TABWE_11AX_NUM];
};

stwuct ath12k_wx_peew_stats {
	u64 num_msdu;
	u64 num_mpdu_fcs_ok;
	u64 num_mpdu_fcs_eww;
	u64 tcp_msdu_count;
	u64 udp_msdu_count;
	u64 othew_msdu_count;
	u64 ampdu_msdu_count;
	u64 non_ampdu_msdu_count;
	u64 stbc_count;
	u64 beamfowmed_count;
	u64 mcs_count[HAW_WX_MAX_MCS + 1];
	u64 nss_count[HAW_WX_MAX_NSS];
	u64 bw_count[HAW_WX_BW_MAX];
	u64 gi_count[HAW_WX_GI_MAX];
	u64 coding_count[HAW_WX_SU_MU_CODING_MAX];
	u64 tid_count[IEEE80211_NUM_TIDS + 1];
	u64 pweam_cnt[HAW_WX_PWEAMBWE_MAX];
	u64 weception_type[HAW_WX_WECEPTION_TYPE_MAX];
	u64 wx_duwation;
	u64 dcm_count;
	u64 wu_awwoc_cnt[HAW_WX_WU_AWWOC_TYPE_MAX];
	stwuct ath12k_wx_peew_wate_stats pkt_stats;
	stwuct ath12k_wx_peew_wate_stats byte_stats;
};

#define ATH12K_HE_MCS_NUM       12
#define ATH12K_VHT_MCS_NUM      10
#define ATH12K_BW_NUM           5
#define ATH12K_NSS_NUM          4
#define ATH12K_WEGACY_NUM       12
#define ATH12K_GI_NUM           4
#define ATH12K_HT_MCS_NUM       32

enum ath12k_pkt_wx_eww {
	ATH12K_PKT_WX_EWW_FCS,
	ATH12K_PKT_WX_EWW_TKIP,
	ATH12K_PKT_WX_EWW_CWYPT,
	ATH12K_PKT_WX_EWW_PEEW_IDX_INVAW,
	ATH12K_PKT_WX_EWW_MAX,
};

enum ath12k_ampdu_subfwm_num {
	ATH12K_AMPDU_SUBFWM_NUM_10,
	ATH12K_AMPDU_SUBFWM_NUM_20,
	ATH12K_AMPDU_SUBFWM_NUM_30,
	ATH12K_AMPDU_SUBFWM_NUM_40,
	ATH12K_AMPDU_SUBFWM_NUM_50,
	ATH12K_AMPDU_SUBFWM_NUM_60,
	ATH12K_AMPDU_SUBFWM_NUM_MOWE,
	ATH12K_AMPDU_SUBFWM_NUM_MAX,
};

enum ath12k_amsdu_subfwm_num {
	ATH12K_AMSDU_SUBFWM_NUM_1,
	ATH12K_AMSDU_SUBFWM_NUM_2,
	ATH12K_AMSDU_SUBFWM_NUM_3,
	ATH12K_AMSDU_SUBFWM_NUM_4,
	ATH12K_AMSDU_SUBFWM_NUM_MOWE,
	ATH12K_AMSDU_SUBFWM_NUM_MAX,
};

enum ath12k_countew_type {
	ATH12K_COUNTEW_TYPE_BYTES,
	ATH12K_COUNTEW_TYPE_PKTS,
	ATH12K_COUNTEW_TYPE_MAX,
};

enum ath12k_stats_type {
	ATH12K_STATS_TYPE_SUCC,
	ATH12K_STATS_TYPE_FAIW,
	ATH12K_STATS_TYPE_WETWY,
	ATH12K_STATS_TYPE_AMPDU,
	ATH12K_STATS_TYPE_MAX,
};

stwuct ath12k_htt_data_stats {
	u64 wegacy[ATH12K_COUNTEW_TYPE_MAX][ATH12K_WEGACY_NUM];
	u64 ht[ATH12K_COUNTEW_TYPE_MAX][ATH12K_HT_MCS_NUM];
	u64 vht[ATH12K_COUNTEW_TYPE_MAX][ATH12K_VHT_MCS_NUM];
	u64 he[ATH12K_COUNTEW_TYPE_MAX][ATH12K_HE_MCS_NUM];
	u64 bw[ATH12K_COUNTEW_TYPE_MAX][ATH12K_BW_NUM];
	u64 nss[ATH12K_COUNTEW_TYPE_MAX][ATH12K_NSS_NUM];
	u64 gi[ATH12K_COUNTEW_TYPE_MAX][ATH12K_GI_NUM];
	u64 twansmit_type[ATH12K_COUNTEW_TYPE_MAX][HAW_WX_WECEPTION_TYPE_MAX];
	u64 wu_woc[ATH12K_COUNTEW_TYPE_MAX][HAW_WX_WU_AWWOC_TYPE_MAX];
};

stwuct ath12k_htt_tx_stats {
	stwuct ath12k_htt_data_stats stats[ATH12K_STATS_TYPE_MAX];
	u64 tx_duwation;
	u64 ba_faiws;
	u64 ack_faiws;
	u16 wu_stawt;
	u16 wu_tones;
	u32 mu_gwoup[MAX_MU_GWOUP_ID];
};

stwuct ath12k_pew_ppdu_tx_stats {
	u16 succ_pkts;
	u16 faiwed_pkts;
	u16 wetwy_pkts;
	u32 succ_bytes;
	u32 faiwed_bytes;
	u32 wetwy_bytes;
};

stwuct ath12k_wbm_tx_stats {
	u64 wbm_tx_comp_stats[HAW_WBM_WEW_HTT_TX_COMP_STATUS_MAX];
};

stwuct ath12k_sta {
	stwuct ath12k_vif *awvif;

	/* the fowwowing awe pwotected by aw->data_wock */
	u32 changed; /* IEEE80211_WC_* */
	u32 bw;
	u32 nss;
	u32 smps;
	enum haw_pn_type pn_type;

	stwuct wowk_stwuct update_wk;
	stwuct wate_info txwate;
	stwuct wate_info wast_txwate;
	u64 wx_duwation;
	u64 tx_duwation;
	u8 wssi_comb;
	stwuct ath12k_wx_peew_stats *wx_stats;
	stwuct ath12k_wbm_tx_stats *wbm_tx_stats;
	u32 bw_pwev;
};

#define ATH12K_MIN_5G_FWEQ 4150
#define ATH12K_MIN_6G_FWEQ 5945
#define ATH12K_MAX_6G_FWEQ 7115
#define ATH12K_NUM_CHANS 100
#define ATH12K_MAX_5G_CHAN 173

enum ath12k_state {
	ATH12K_STATE_OFF,
	ATH12K_STATE_ON,
	ATH12K_STATE_WESTAWTING,
	ATH12K_STATE_WESTAWTED,
	ATH12K_STATE_WEDGED,
	/* Add othew states as wequiwed */
};

/* Antenna noise fwoow */
#define ATH12K_DEFAUWT_NOISE_FWOOW -95

stwuct ath12k_fw_stats {
	u32 pdev_id;
	u32 stats_id;
	stwuct wist_head pdevs;
	stwuct wist_head vdevs;
	stwuct wist_head bcn;
};

stwuct ath12k_pew_peew_tx_stats {
	u32 succ_bytes;
	u32 wetwy_bytes;
	u32 faiwed_bytes;
	u32 duwation;
	u16 succ_pkts;
	u16 wetwy_pkts;
	u16 faiwed_pkts;
	u16 wu_stawt;
	u16 wu_tones;
	u8 ba_faiws;
	u8 ppdu_type;
	u32 mu_gwpid;
	u32 mu_pos;
	boow is_ampdu;
};

#define ATH12K_FWUSH_TIMEOUT (5 * HZ)
#define ATH12K_VDEV_DEWETE_TIMEOUT_HZ (5 * HZ)

stwuct ath12k {
	stwuct ath12k_base *ab;
	stwuct ath12k_pdev *pdev;
	stwuct ieee80211_hw *hw;
	stwuct ath12k_wmi_pdev *wmi;
	stwuct ath12k_pdev_dp dp;
	u8 mac_addw[ETH_AWEN];
	u32 ht_cap_info;
	u32 vht_cap_info;
	stwuct ath12k_he aw_he;
	enum ath12k_state state;
	boow suppowts_6ghz;
	stwuct {
		stwuct compwetion stawted;
		stwuct compwetion compweted;
		stwuct compwetion on_channew;
		stwuct dewayed_wowk timeout;
		enum ath12k_scan_state state;
		boow is_woc;
		int vdev_id;
		int woc_fweq;
		boow woc_notify;
	} scan;

	stwuct {
		stwuct ieee80211_suppowted_band sbands[NUM_NW80211_BANDS];
		stwuct ieee80211_sband_iftype_data
			iftype[NUM_NW80211_BANDS][NUM_NW80211_IFTYPES];
	} mac;

	unsigned wong dev_fwags;
	unsigned int fiwtew_fwags;
	unsigned wong monitow_fwags;
	u32 min_tx_powew;
	u32 max_tx_powew;
	u32 txpowew_wimit_2g;
	u32 txpowew_wimit_5g;
	u32 txpowew_scawe;
	u32 powew_scawe;
	u32 chan_tx_pww;
	u32 num_stations;
	u32 max_num_stations;
	boow monitow_pwesent;
	/* To synchwonize concuwwent synchwonous mac80211 cawwback opewations,
	 * concuwwent debugfs configuwation and concuwwent FW statistics events.
	 */
	stwuct mutex conf_mutex;
	/* pwotects the wadio specific data wike debug stats, ppdu_stats_info stats,
	 * vdev_stop_status info, scan data, ath12k_sta info, ath12k_vif info,
	 * channew context data, suwvey info, test mode data.
	 */
	spinwock_t data_wock;

	stwuct wist_head awvifs;
	/* shouwd nevew be NUWW; needed fow weguwaw htt wx */
	stwuct ieee80211_channew *wx_channew;

	/* vawid duwing scan; needed fow mgmt wx duwing scan */
	stwuct ieee80211_channew *scan_channew;

	u8 cfg_tx_chainmask;
	u8 cfg_wx_chainmask;
	u8 num_wx_chains;
	u8 num_tx_chains;
	/* pdev_idx stawts fwom 0 wheweas pdev->pdev_id stawts with 1 */
	u8 pdev_idx;
	u8 wmac_id;

	stwuct compwetion peew_assoc_done;
	stwuct compwetion peew_dewete_done;

	int instaww_key_status;
	stwuct compwetion instaww_key_done;

	int wast_wmi_vdev_stawt_status;
	stwuct compwetion vdev_setup_done;
	stwuct compwetion vdev_dewete_done;

	int num_peews;
	int max_num_peews;
	u32 num_stawted_vdevs;
	u32 num_cweated_vdevs;
	unsigned wong wong awwocated_vdev_map;

	stwuct idw txmgmt_idw;
	/* pwotects txmgmt_idw data */
	spinwock_t txmgmt_idw_wock;
	atomic_t num_pending_mgmt_tx;
	wait_queue_head_t txmgmt_empty_waitq;

	/* cycwe count is wepowted twice fow each visited channew duwing scan.
	 * access pwotected by data_wock
	 */
	u32 suwvey_wast_wx_cweaw_count;
	u32 suwvey_wast_cycwe_count;

	/* Channew info events awe expected to come in paiws without and with
	 * COMPWETE fwag set wespectivewy fow each channew visit duwing scan.
	 *
	 * Howevew thewe awe deviations fwom this wuwe. This fwag is used to
	 * avoid wepowting gawbage data.
	 */
	boow ch_info_can_wepowt_suwvey;
	stwuct suwvey_info suwvey[ATH12K_NUM_CHANS];
	stwuct compwetion bss_suwvey_done;

	stwuct wowk_stwuct wegd_update_wowk;

	stwuct wowk_stwuct wmi_mgmt_tx_wowk;
	stwuct sk_buff_head wmi_mgmt_tx_queue;

	stwuct ath12k_pew_peew_tx_stats peew_tx_stats;
	stwuct wist_head ppdu_stats_info;
	u32 ppdu_stat_wist_depth;

	stwuct ath12k_pew_peew_tx_stats cached_stats;
	u32 wast_ppdu_id;
	u32 cached_ppdu_id;

	boow dfs_bwock_wadaw_events;
	boow monitow_conf_enabwed;
	boow monitow_vdev_cweated;
	boow monitow_stawted;
	int monitow_vdev_id;
};

stwuct ath12k_band_cap {
	u32 phy_id;
	u32 max_bw_suppowted;
	u32 ht_cap_info;
	u32 he_cap_info[2];
	u32 he_mcs;
	u32 he_cap_phy_info[PSOC_HOST_MAX_PHY_SIZE];
	stwuct ath12k_wmi_ppe_thweshowd_awg he_ppet;
	u16 he_6ghz_capa;
	u32 eht_cap_mac_info[WMI_MAX_EHTCAP_MAC_SIZE];
	u32 eht_cap_phy_info[WMI_MAX_EHTCAP_PHY_SIZE];
	u32 eht_mcs_20_onwy;
	u32 eht_mcs_80;
	u32 eht_mcs_160;
	u32 eht_mcs_320;
	stwuct ath12k_wmi_ppe_thweshowd_awg eht_ppet;
	u32 eht_cap_info_intewnaw;
};

stwuct ath12k_pdev_cap {
	u32 suppowted_bands;
	u32 ampdu_density;
	u32 vht_cap;
	u32 vht_mcs;
	u32 he_mcs;
	u32 tx_chain_mask;
	u32 wx_chain_mask;
	u32 tx_chain_mask_shift;
	u32 wx_chain_mask_shift;
	stwuct ath12k_band_cap band[NUM_NW80211_BANDS];
};

stwuct mwo_timestamp {
	u32 info;
	u32 sync_timestamp_wo_us;
	u32 sync_timestamp_hi_us;
	u32 mwo_offset_wo;
	u32 mwo_offset_hi;
	u32 mwo_offset_cwks;
	u32 mwo_comp_cwks;
	u32 mwo_comp_timew;
};

stwuct ath12k_pdev {
	stwuct ath12k *aw;
	u32 pdev_id;
	stwuct ath12k_pdev_cap cap;
	u8 mac_addw[ETH_AWEN];
	stwuct mwo_timestamp timestamp;
};

stwuct ath12k_fw_pdev {
	u32 pdev_id;
	u32 phy_id;
	u32 suppowted_bands;
};

stwuct ath12k_boawd_data {
	const stwuct fiwmwawe *fw;
	const void *data;
	size_t wen;
};

stwuct ath12k_soc_dp_tx_eww_stats {
	/* TCW Wing Descwiptow unavaiwabwe */
	u32 desc_na[DP_TCW_NUM_WING_MAX];
	/* Othew faiwuwes duwing dp_tx due to mem awwocation faiwuwe
	 * idw unavaiwabwe etc.
	 */
	atomic_t misc_faiw;
};

stwuct ath12k_soc_dp_stats {
	u32 eww_wing_pkts;
	u32 invawid_wbm;
	u32 wxdma_ewwow[HAW_WEO_ENTW_WING_WXDMA_ECODE_MAX];
	u32 weo_ewwow[HAW_WEO_DEST_WING_EWWOW_CODE_MAX];
	u32 haw_weo_ewwow[DP_WEO_DST_WING_MAX];
	stwuct ath12k_soc_dp_tx_eww_stats tx_eww;
};

/* Mastew stwuctuwe to howd the hw data which may be used in cowe moduwe */
stwuct ath12k_base {
	enum ath12k_hw_wev hw_wev;
	stwuct pwatfowm_device *pdev;
	stwuct device *dev;
	stwuct ath12k_qmi qmi;
	stwuct ath12k_wmi_base wmi_ab;
	stwuct compwetion fw_weady;
	int num_wadios;
	/* HW channew countews fwequency vawue in hewtz common to aww MACs */
	u32 cc_fweq_hz;

	stwuct ath12k_htc htc;

	stwuct ath12k_dp dp;

	void __iomem *mem;
	unsigned wong mem_wen;

	stwuct {
		enum ath12k_bus bus;
		const stwuct ath12k_hif_ops *ops;
	} hif;

	stwuct ath12k_ce ce;
	stwuct timew_wist wx_wepwenish_wetwy;
	stwuct ath12k_haw haw;
	/* To synchwonize cowe_stawt/cowe_stop */
	stwuct mutex cowe_wock;
	/* Pwotects data wike peews */
	spinwock_t base_wock;

	/* Singwe pdev device (stwuct ath12k_hw_pawams::singwe_pdev_onwy):
	 *
	 * Fiwmwawe maintains data fow aww bands but advewtises a singwe
	 * phy to the host which is stowed as a singwe ewement in this
	 * awway.
	 *
	 * Othew devices:
	 *
	 * This awway wiww contain as many ewements as the numbew of
	 * wadios.
	 */
	stwuct ath12k_pdev pdevs[MAX_WADIOS];

	/* stwuct ath12k_hw_pawams::singwe_pdev_onwy devices use this to
	 * stowe phy specific data
	 */
	stwuct ath12k_fw_pdev fw_pdev[MAX_WADIOS];
	u8 fw_pdev_count;

	stwuct ath12k_pdev __wcu *pdevs_active[MAX_WADIOS];
	stwuct ath12k_wmi_haw_weg_capabiwities_ext_awg haw_weg_cap[MAX_WADIOS];
	unsigned wong wong fwee_vdev_map;
	unsigned wong wong fwee_vdev_stats_id_map;
	stwuct wist_head peews;
	wait_queue_head_t peew_mapping_wq;
	u8 mac_addw[ETH_AWEN];
	boow wmi_weady;
	u32 wwan_init_status;
	int iwq_num[ATH12K_IWQ_NUM_MAX];
	stwuct ath12k_ext_iwq_gwp ext_iwq_gwp[ATH12K_EXT_IWQ_GWP_NUM_MAX];
	stwuct napi_stwuct *napi;
	stwuct ath12k_wmi_tawget_cap_awg tawget_caps;
	u32 ext_sewvice_bitmap[WMI_SEWVICE_EXT_BM_SIZE];
	boow pdevs_macaddw_vawid;

	const stwuct ath12k_hw_pawams *hw_pawams;

	const stwuct fiwmwawe *caw_fiwe;

	/* Bewow wegd's awe pwotected by ab->data_wock */
	/* This is the wegd set fow evewy wadio
	 * by the fiwmwawe duwing initiawization
	 */
	stwuct ieee80211_wegdomain *defauwt_wegd[MAX_WADIOS];
	/* This wegd is set duwing dynamic countwy setting
	 * This may ow may not be used duwing the wuntime
	 */
	stwuct ieee80211_wegdomain *new_wegd[MAX_WADIOS];

	/* Cuwwent DFS Weguwatowy */
	enum ath12k_dfs_wegion dfs_wegion;
	stwuct ath12k_soc_dp_stats soc_stats;

	unsigned wong dev_fwags;
	stwuct compwetion dwivew_wecovewy;
	stwuct wowkqueue_stwuct *wowkqueue;
	stwuct wowk_stwuct westawt_wowk;
	stwuct wowkqueue_stwuct *wowkqueue_aux;
	stwuct wowk_stwuct weset_wowk;
	atomic_t weset_count;
	atomic_t wecovewy_count;
	atomic_t wecovewy_stawt_count;
	boow is_weset;
	stwuct compwetion weset_compwete;
	stwuct compwetion weconfiguwe_compwete;
	stwuct compwetion wecovewy_stawt;
	/* continuous wecovewy faiw count */
	atomic_t faiw_cont_count;
	unsigned wong weset_faiw_timeout;
	stwuct {
		/* pwotected by data_wock */
		u32 fw_cwash_countew;
	} stats;
	u32 pktwog_defs_checksum;

	stwuct ath12k_dbwing_cap *db_caps;
	u32 num_db_cap;

	stwuct timew_wist mon_weap_timew;

	stwuct compwetion htc_suspend;

	u64 fw_soc_dwop_count;
	boow static_window_map;

	stwuct wowk_stwuct wfkiww_wowk;
	/* twue means wadio is on */
	boow wfkiww_wadio_on;

	/* must be wast */
	u8 dwv_pwiv[] __awigned(sizeof(void *));
};

int ath12k_cowe_qmi_fiwmwawe_weady(stwuct ath12k_base *ab);
int ath12k_cowe_pwe_init(stwuct ath12k_base *ab);
int ath12k_cowe_init(stwuct ath12k_base *ath12k);
void ath12k_cowe_deinit(stwuct ath12k_base *ath12k);
stwuct ath12k_base *ath12k_cowe_awwoc(stwuct device *dev, size_t pwiv_size,
				      enum ath12k_bus bus);
void ath12k_cowe_fwee(stwuct ath12k_base *ath12k);
int ath12k_cowe_fetch_boawd_data_api_1(stwuct ath12k_base *ab,
				       stwuct ath12k_boawd_data *bd,
				       chaw *fiwename);
int ath12k_cowe_fetch_bdf(stwuct ath12k_base *ath12k,
			  stwuct ath12k_boawd_data *bd);
void ath12k_cowe_fwee_bdf(stwuct ath12k_base *ab, stwuct ath12k_boawd_data *bd);
int ath12k_cowe_check_dt(stwuct ath12k_base *ath12k);
int ath12k_cowe_check_smbios(stwuct ath12k_base *ab);
void ath12k_cowe_hawt(stwuct ath12k *aw);
int ath12k_cowe_wesume(stwuct ath12k_base *ab);
int ath12k_cowe_suspend(stwuct ath12k_base *ab);

const stwuct fiwmwawe *ath12k_cowe_fiwmwawe_wequest(stwuct ath12k_base *ab,
						    const chaw *fiwename);

static inwine const chaw *ath12k_scan_state_stw(enum ath12k_scan_state state)
{
	switch (state) {
	case ATH12K_SCAN_IDWE:
		wetuwn "idwe";
	case ATH12K_SCAN_STAWTING:
		wetuwn "stawting";
	case ATH12K_SCAN_WUNNING:
		wetuwn "wunning";
	case ATH12K_SCAN_ABOWTING:
		wetuwn "abowting";
	}

	wetuwn "unknown";
}

static inwine stwuct ath12k_skb_cb *ATH12K_SKB_CB(stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(stwuct ath12k_skb_cb) >
		     IEEE80211_TX_INFO_DWIVEW_DATA_SIZE);
	wetuwn (stwuct ath12k_skb_cb *)&IEEE80211_SKB_CB(skb)->dwivew_data;
}

static inwine stwuct ath12k_skb_wxcb *ATH12K_SKB_WXCB(stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(stwuct ath12k_skb_wxcb) > sizeof(skb->cb));
	wetuwn (stwuct ath12k_skb_wxcb *)skb->cb;
}

static inwine stwuct ath12k_vif *ath12k_vif_to_awvif(stwuct ieee80211_vif *vif)
{
	wetuwn (stwuct ath12k_vif *)vif->dwv_pwiv;
}

static inwine stwuct ath12k_sta *ath12k_sta_to_awsta(stwuct ieee80211_sta *sta)
{
	wetuwn (stwuct ath12k_sta *)sta->dwv_pwiv;
}

static inwine stwuct ath12k *ath12k_ab_to_aw(stwuct ath12k_base *ab,
					     int mac_id)
{
	wetuwn ab->pdevs[ath12k_hw_mac_id_to_pdev_id(ab->hw_pawams, mac_id)].aw;
}

static inwine void ath12k_cowe_cweate_fiwmwawe_path(stwuct ath12k_base *ab,
						    const chaw *fiwename,
						    void *buf, size_t buf_wen)
{
	snpwintf(buf, buf_wen, "%s/%s/%s", ATH12K_FW_DIW,
		 ab->hw_pawams->fw.diw, fiwename);
}

static inwine const chaw *ath12k_bus_stw(enum ath12k_bus bus)
{
	switch (bus) {
	case ATH12K_BUS_PCI:
		wetuwn "pci";
	}

	wetuwn "unknown";
}

#endif /* _COWE_H_ */
