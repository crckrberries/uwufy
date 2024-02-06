/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH11K_COWE_H
#define ATH11K_COWE_H

#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/dmi.h>
#incwude <winux/ctype.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/avewage.h>
#incwude <winux/fiwmwawe.h>

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
#incwude "thewmaw.h"
#incwude "dbwing.h"
#incwude "spectwaw.h"
#incwude "wow.h"
#incwude "fw.h"

#define SM(_v, _f) (((_v) << _f##_WSB) & _f##_MASK)

#define ATH11K_TX_MGMT_NUM_PENDING_MAX	512

#define ATH11K_TX_MGMT_TAWGET_MAX_SUPPOWT_WMI 64

/* Pending management packets thweshowd fow dwopping pwobe wesponses */
#define ATH11K_PWB_WSP_DWOP_THWESHOWD ((ATH11K_TX_MGMT_TAWGET_MAX_SUPPOWT_WMI * 3) / 4)

#define ATH11K_INVAWID_HW_MAC_ID	0xFF
#define ATH11K_CONNECTION_WOSS_HZ	(3 * HZ)

/* SMBIOS type containing Boawd Data Fiwe Name Extension */
#define ATH11K_SMBIOS_BDF_EXT_TYPE 0xF8

/* SMBIOS type stwuctuwe wength (excwuding stwings-set) */
#define ATH11K_SMBIOS_BDF_EXT_WENGTH 0x9

/* The magic used by QCA spec */
#define ATH11K_SMBIOS_BDF_EXT_MAGIC "BDF_"

extewn unsigned int ath11k_fwame_mode;
extewn boow ath11k_ftm_mode;

#define ATH11K_SCAN_TIMEOUT_HZ (20 * HZ)

#define ATH11K_MON_TIMEW_INTEWVAW  10
#define ATH11K_WESET_TIMEOUT_HZ (20 * HZ)
#define ATH11K_WESET_MAX_FAIW_COUNT_FIWST 3
#define ATH11K_WESET_MAX_FAIW_COUNT_FINAW 5
#define ATH11K_WESET_FAIW_TIMEOUT_HZ (20 * HZ)
#define ATH11K_WECONFIGUWE_TIMEOUT_HZ (10 * HZ)
#define ATH11K_WECOVEW_STAWT_TIMEOUT_HZ (20 * HZ)

enum ath11k_suppowted_bw {
	ATH11K_BW_20	= 0,
	ATH11K_BW_40	= 1,
	ATH11K_BW_80	= 2,
	ATH11K_BW_160	= 3,
};

enum ath11k_bdf_seawch {
	ATH11K_BDF_SEAWCH_DEFAUWT,
	ATH11K_BDF_SEAWCH_BUS_AND_BOAWD,
};

enum wme_ac {
	WME_AC_BE,
	WME_AC_BK,
	WME_AC_VI,
	WME_AC_VO,
	WME_NUM_AC
};

#define ATH11K_HT_MCS_MAX	7
#define ATH11K_VHT_MCS_MAX	9
#define ATH11K_HE_MCS_MAX	11

enum ath11k_cwypt_mode {
	/* Onwy use hawdwawe cwypto engine */
	ATH11K_CWYPT_MODE_HW,
	/* Onwy use softwawe cwypto */
	ATH11K_CWYPT_MODE_SW,
};

static inwine enum wme_ac ath11k_tid_to_ac(u32 tid)
{
	wetuwn (((tid == 0) || (tid == 3)) ? WME_AC_BE :
		((tid == 1) || (tid == 2)) ? WME_AC_BK :
		((tid == 4) || (tid == 5)) ? WME_AC_VI :
		WME_AC_VO);
}

enum ath11k_skb_fwags {
	ATH11K_SKB_HW_80211_ENCAP = BIT(0),
	ATH11K_SKB_CIPHEW_SET = BIT(1),
};

stwuct ath11k_skb_cb {
	dma_addw_t paddw;
	u8 eid;
	u8 fwags;
	u32 ciphew;
	stwuct ath11k *aw;
	stwuct ieee80211_vif *vif;
} __packed;

stwuct ath11k_skb_wxcb {
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
	u16 seq_no;
};

enum ath11k_hw_wev {
	ATH11K_HW_IPQ8074,
	ATH11K_HW_QCA6390_HW20,
	ATH11K_HW_IPQ6018_HW10,
	ATH11K_HW_QCN9074_HW10,
	ATH11K_HW_WCN6855_HW20,
	ATH11K_HW_WCN6855_HW21,
	ATH11K_HW_WCN6750_HW10,
	ATH11K_HW_IPQ5018_HW10,
};

enum ath11k_fiwmwawe_mode {
	/* the defauwt mode, standawd 802.11 functionawity */
	ATH11K_FIWMWAWE_MODE_NOWMAW,

	/* factowy tests etc */
	ATH11K_FIWMWAWE_MODE_FTM,

	/* Cowd boot cawibwation */
	ATH11K_FIWMWAWE_MODE_COWD_BOOT = 7,
};

extewn boow ath11k_cowd_boot_caw;

#define ATH11K_IWQ_NUM_MAX 52
#define ATH11K_EXT_IWQ_NUM_MAX	16

stwuct ath11k_ext_iwq_gwp {
	stwuct ath11k_base *ab;
	u32 iwqs[ATH11K_EXT_IWQ_NUM_MAX];
	u32 num_iwq;
	u32 gwp_id;
	u64 timestamp;
	boow napi_enabwed;
	stwuct napi_stwuct napi;
	stwuct net_device napi_ndev;
};

enum ath11k_smbios_cc_type {
	/* disabwe countwy code setting fwom SMBIOS */
	ATH11K_SMBIOS_CC_DISABWE = 0,

	/* set countwy code by ANSI countwy name, based on ISO3166-1 awpha2 */
	ATH11K_SMBIOS_CC_ISO = 1,

	/* wowwdwide wegdomain */
	ATH11K_SMBIOS_CC_WW = 2,
};

stwuct ath11k_smbios_bdf {
	stwuct dmi_headew hdw;

	u8 featuwes_disabwed;

	/* enum ath11k_smbios_cc_type */
	u8 countwy_code_fwag;

	/* To set specific countwy, you need to set countwy code
	 * fwag=ATH11K_SMBIOS_CC_ISO fiwst, then if countwy is United
	 * States, then countwy code vawue = 0x5553 ("US",'U' = 0x55, 'S'=
	 * 0x53). To set countwy to INDONESIA, then countwy code vawue =
	 * 0x4944 ("IN", 'I'=0x49, 'D'=0x44). If countwy code fwag =
	 * ATH11K_SMBIOS_CC_WW, then you can use wowwdwide weguwatowy
	 * setting.
	 */
	u16 cc_code;

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

stwuct ath11k_he {
	u8 hecap_macinfo[HECAP_MACINFO_SIZE];
	u32 hecap_wxmcsnssmap;
	u32 hecap_txmcsnssmap;
	u32 hecap_phyinfo[HEHANDWE_CAP_PHYINFO_SIZE];
	stwuct he_ppe_thweshowd   hecap_ppet;
	u32 heop_pawam;
};

#define MAX_WADIOS 3

/* ipq5018 hw pawam macwos */
#define MAX_WADIOS_5018	1
#define CE_CNT_5018	6
#define TAWGET_CE_CNT_5018	9
#define SVC_CE_MAP_WEN_5018	17
#define WXDMA_PEW_PDEV_5018	1

enum {
	WMI_HOST_TP_SCAWE_MAX   = 0,
	WMI_HOST_TP_SCAWE_50    = 1,
	WMI_HOST_TP_SCAWE_25    = 2,
	WMI_HOST_TP_SCAWE_12    = 3,
	WMI_HOST_TP_SCAWE_MIN   = 4,
	WMI_HOST_TP_SCAWE_SIZE   = 5,
};

enum ath11k_scan_state {
	ATH11K_SCAN_IDWE,
	ATH11K_SCAN_STAWTING,
	ATH11K_SCAN_WUNNING,
	ATH11K_SCAN_ABOWTING,
};

enum ath11k_11d_state {
	ATH11K_11D_IDWE,
	ATH11K_11D_PWEPAWING,
	ATH11K_11D_WUNNING,
};

enum ath11k_dev_fwags {
	ATH11K_CAC_WUNNING,
	ATH11K_FWAG_COWE_WEGISTEWED,
	ATH11K_FWAG_CWASH_FWUSH,
	ATH11K_FWAG_WAW_MODE,
	ATH11K_FWAG_HW_CWYPTO_DISABWED,
	ATH11K_FWAG_BTCOEX,
	ATH11K_FWAG_WECOVEWY,
	ATH11K_FWAG_UNWEGISTEWING,
	ATH11K_FWAG_WEGISTEWED,
	ATH11K_FWAG_QMI_FAIW,
	ATH11K_FWAG_HTC_SUSPEND_COMPWETE,
	ATH11K_FWAG_CE_IWQ_ENABWED,
	ATH11K_FWAG_EXT_IWQ_ENABWED,
	ATH11K_FWAG_FIXED_MEM_WGN,
	ATH11K_FWAG_DEVICE_INIT_DONE,
	ATH11K_FWAG_MUWTI_MSI_VECTOWS,
	ATH11K_FWAG_FTM_SEGMENTED,
};

enum ath11k_monitow_fwags {
	ATH11K_FWAG_MONITOW_CONF_ENABWED,
	ATH11K_FWAG_MONITOW_STAWTED,
	ATH11K_FWAG_MONITOW_VDEV_CWEATED,
};

#define ATH11K_IPV6_UC_TYPE     0
#define ATH11K_IPV6_AC_TYPE     1

#define ATH11K_IPV6_MAX_COUNT   16
#define ATH11K_IPV4_MAX_COUNT   2

stwuct ath11k_awp_ns_offwoad {
	u8  ipv4_addw[ATH11K_IPV4_MAX_COUNT][4];
	u32 ipv4_count;
	u32 ipv6_count;
	u8  ipv6_addw[ATH11K_IPV6_MAX_COUNT][16];
	u8  sewf_ipv6_addw[ATH11K_IPV6_MAX_COUNT][16];
	u8  ipv6_type[ATH11K_IPV6_MAX_COUNT];
	boow ipv6_vawid[ATH11K_IPV6_MAX_COUNT];
	u8  mac_addw[ETH_AWEN];
};

stwuct ath11k_wekey_data {
	u8 kck[NW80211_KCK_WEN];
	u8 kek[NW80211_KCK_WEN];
	u64 wepway_ctw;
	boow enabwe_offwoad;
};

stwuct ath11k_vif {
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

	stwuct ath11k *aw;
	stwuct ieee80211_vif *vif;

	u16 tx_seq_no;
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
	boow ftm_wespondew;
	boow spectwaw_enabwed;
	boow ps;
	u32 aid;
	u8 bssid[ETH_AWEN];
	stwuct cfg80211_bitwate_mask bitwate_mask;
	stwuct dewayed_wowk connection_woss_wowk;
	int num_wegacy_stations;
	int wtscts_pwot_mode;
	int txpowew;
	boow wsnie_pwesent;
	boow wpaie_pwesent;
	boow bcca_zewo_sent;
	boow do_not_send_tmpw;
	stwuct ieee80211_chanctx_conf chanctx;
	stwuct ath11k_awp_ns_offwoad awp_ns_offwoad;
	stwuct ath11k_wekey_data wekey_data;
};

stwuct ath11k_vif_itew {
	u32 vdev_id;
	stwuct ath11k_vif *awvif;
};

stwuct ath11k_wx_peew_stats {
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
};

#define ATH11K_HE_MCS_NUM       12
#define ATH11K_VHT_MCS_NUM      10
#define ATH11K_BW_NUM           4
#define ATH11K_NSS_NUM          4
#define ATH11K_WEGACY_NUM       12
#define ATH11K_GI_NUM           4
#define ATH11K_HT_MCS_NUM       32

enum ath11k_pkt_wx_eww {
	ATH11K_PKT_WX_EWW_FCS,
	ATH11K_PKT_WX_EWW_TKIP,
	ATH11K_PKT_WX_EWW_CWYPT,
	ATH11K_PKT_WX_EWW_PEEW_IDX_INVAW,
	ATH11K_PKT_WX_EWW_MAX,
};

enum ath11k_ampdu_subfwm_num {
	ATH11K_AMPDU_SUBFWM_NUM_10,
	ATH11K_AMPDU_SUBFWM_NUM_20,
	ATH11K_AMPDU_SUBFWM_NUM_30,
	ATH11K_AMPDU_SUBFWM_NUM_40,
	ATH11K_AMPDU_SUBFWM_NUM_50,
	ATH11K_AMPDU_SUBFWM_NUM_60,
	ATH11K_AMPDU_SUBFWM_NUM_MOWE,
	ATH11K_AMPDU_SUBFWM_NUM_MAX,
};

enum ath11k_amsdu_subfwm_num {
	ATH11K_AMSDU_SUBFWM_NUM_1,
	ATH11K_AMSDU_SUBFWM_NUM_2,
	ATH11K_AMSDU_SUBFWM_NUM_3,
	ATH11K_AMSDU_SUBFWM_NUM_4,
	ATH11K_AMSDU_SUBFWM_NUM_MOWE,
	ATH11K_AMSDU_SUBFWM_NUM_MAX,
};

enum ath11k_countew_type {
	ATH11K_COUNTEW_TYPE_BYTES,
	ATH11K_COUNTEW_TYPE_PKTS,
	ATH11K_COUNTEW_TYPE_MAX,
};

enum ath11k_stats_type {
	ATH11K_STATS_TYPE_SUCC,
	ATH11K_STATS_TYPE_FAIW,
	ATH11K_STATS_TYPE_WETWY,
	ATH11K_STATS_TYPE_AMPDU,
	ATH11K_STATS_TYPE_MAX,
};

stwuct ath11k_htt_data_stats {
	u64 wegacy[ATH11K_COUNTEW_TYPE_MAX][ATH11K_WEGACY_NUM];
	u64 ht[ATH11K_COUNTEW_TYPE_MAX][ATH11K_HT_MCS_NUM];
	u64 vht[ATH11K_COUNTEW_TYPE_MAX][ATH11K_VHT_MCS_NUM];
	u64 he[ATH11K_COUNTEW_TYPE_MAX][ATH11K_HE_MCS_NUM];
	u64 bw[ATH11K_COUNTEW_TYPE_MAX][ATH11K_BW_NUM];
	u64 nss[ATH11K_COUNTEW_TYPE_MAX][ATH11K_NSS_NUM];
	u64 gi[ATH11K_COUNTEW_TYPE_MAX][ATH11K_GI_NUM];
};

stwuct ath11k_htt_tx_stats {
	stwuct ath11k_htt_data_stats stats[ATH11K_STATS_TYPE_MAX];
	u64 tx_duwation;
	u64 ba_faiws;
	u64 ack_faiws;
};

stwuct ath11k_pew_ppdu_tx_stats {
	u16 succ_pkts;
	u16 faiwed_pkts;
	u16 wetwy_pkts;
	u32 succ_bytes;
	u32 faiwed_bytes;
	u32 wetwy_bytes;
};

DECWAWE_EWMA(avg_wssi, 10, 8)

stwuct ath11k_sta {
	stwuct ath11k_vif *awvif;

	/* the fowwowing awe pwotected by aw->data_wock */
	u32 changed; /* IEEE80211_WC_* */
	u32 bw;
	u32 nss;
	u32 smps;
	enum haw_pn_type pn_type;

	stwuct wowk_stwuct update_wk;
	stwuct wowk_stwuct set_4addw_wk;
	stwuct wate_info txwate;
	u32 peew_nss;
	stwuct wate_info wast_txwate;
	u64 wx_duwation;
	u64 tx_duwation;
	u8 wssi_comb;
	stwuct ewma_avg_wssi avg_wssi;
	s8 wssi_beacon;
	s8 chain_signaw[IEEE80211_MAX_CHAINS];
	stwuct ath11k_htt_tx_stats *tx_stats;
	stwuct ath11k_wx_peew_stats *wx_stats;

#ifdef CONFIG_MAC80211_DEBUGFS
	/* pwotected by conf_mutex */
	boow aggw_mode;
#endif

	boow use_4addw_set;
	u16 tcw_metadata;

	/* Pwotected with aw->data_wock */
	enum ath11k_wmi_peew_ps_state peew_ps_state;
	u64 ps_stawt_time;
	u64 ps_stawt_jiffies;
	u64 ps_totaw_duwation;
	boow peew_cuwwent_ps_vawid;

	u32 bw_pwev;
};

#define ATH11K_MIN_5G_FWEQ 4150
#define ATH11K_MIN_6G_FWEQ 5925
#define ATH11K_MAX_6G_FWEQ 7115
#define ATH11K_NUM_CHANS 102
#define ATH11K_MAX_5G_CHAN 177

enum ath11k_state {
	ATH11K_STATE_OFF,
	ATH11K_STATE_ON,
	ATH11K_STATE_WESTAWTING,
	ATH11K_STATE_WESTAWTED,
	ATH11K_STATE_WEDGED,
	ATH11K_STATE_FTM,
	/* Add othew states as wequiwed */
};

/* Antenna noise fwoow */
#define ATH11K_DEFAUWT_NOISE_FWOOW -95

#define ATH11K_INVAWID_WSSI_FUWW -1

#define ATH11K_INVAWID_WSSI_EMPTY -128

stwuct ath11k_fw_stats {
	stwuct dentwy *debugfs_fwstats;
	u32 pdev_id;
	u32 stats_id;
	stwuct wist_head pdevs;
	stwuct wist_head vdevs;
	stwuct wist_head bcn;
};

stwuct ath11k_dbg_htt_stats {
	u8 type;
	u8 weset;
	stwuct debug_htt_stats_weq *stats_weq;
	/* pwotects shawed stats weq buffew */
	spinwock_t wock;
};

#define MAX_MODUWE_ID_BITMAP_WOWDS	16

stwuct ath11k_debug {
	stwuct dentwy *debugfs_pdev;
	stwuct ath11k_dbg_htt_stats htt_stats;
	u32 extd_tx_stats;
	u32 extd_wx_stats;
	u32 pktwog_fiwtew;
	u32 pktwog_mode;
	u32 pktwog_peew_vawid;
	u8 pktwog_peew_addw[ETH_AWEN];
	u32 wx_fiwtew;
	u32 mem_offset;
	u32 moduwe_id_bitmap[MAX_MODUWE_ID_BITMAP_WOWDS];
	stwuct ath11k_debug_dbw *dbw_debug[WMI_DIWECT_BUF_MAX];
};

stwuct ath11k_pew_peew_tx_stats {
	u32 succ_bytes;
	u32 wetwy_bytes;
	u32 faiwed_bytes;
	u16 succ_pkts;
	u16 wetwy_pkts;
	u16 faiwed_pkts;
	u32 duwation;
	u8 ba_faiws;
	boow is_ampdu;
};

#define ATH11K_FWUSH_TIMEOUT (5 * HZ)
#define ATH11K_VDEV_DEWETE_TIMEOUT_HZ (5 * HZ)

stwuct ath11k {
	stwuct ath11k_base *ab;
	stwuct ath11k_pdev *pdev;
	stwuct ieee80211_hw *hw;
	stwuct ath11k_pdev_wmi *wmi;
	stwuct ath11k_pdev_dp dp;
	u8 mac_addw[ETH_AWEN];
	stwuct ath11k_he aw_he;
	enum ath11k_state state;
	boow suppowts_6ghz;
	stwuct {
		stwuct compwetion stawted;
		stwuct compwetion compweted;
		stwuct compwetion on_channew;
		stwuct dewayed_wowk timeout;
		enum ath11k_scan_state state;
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
	/* To synchwonize concuwwent synchwonous mac80211 cawwback opewations,
	 * concuwwent debugfs configuwation and concuwwent FW statistics events.
	 */
	stwuct mutex conf_mutex;
	/* pwotects the wadio specific data wike debug stats, ppdu_stats_info stats,
	 * vdev_stop_status info, scan data, ath11k_sta info, ath11k_vif info,
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
	stwuct suwvey_info suwvey[ATH11K_NUM_CHANS];
	stwuct compwetion bss_suwvey_done;

	stwuct wowk_stwuct wegd_update_wowk;

	stwuct wowk_stwuct wmi_mgmt_tx_wowk;
	stwuct sk_buff_head wmi_mgmt_tx_queue;

	stwuct ath11k_wow wow;
	stwuct compwetion tawget_suspend;
	boow tawget_suspend_ack;
	stwuct ath11k_pew_peew_tx_stats peew_tx_stats;
	stwuct wist_head ppdu_stats_info;
	u32 ppdu_stat_wist_depth;

	stwuct ath11k_pew_peew_tx_stats cached_stats;
	u32 wast_ppdu_id;
	u32 cached_ppdu_id;
	int monitow_vdev_id;
	stwuct compwetion fw_mode_weset;
	u8 ftm_msgwef;
#ifdef CONFIG_ATH11K_DEBUGFS
	stwuct ath11k_debug debug;
#endif
#ifdef CONFIG_ATH11K_SPECTWAW
	stwuct ath11k_spectwaw spectwaw;
#endif
	boow dfs_bwock_wadaw_events;
	stwuct ath11k_thewmaw thewmaw;
	u32 vdev_id_11d_scan;
	stwuct compwetion compweted_11d_scan;
	enum ath11k_11d_state state_11d;
	boow wegdom_set_by_usew;
	int hw_wate_code;
	u8 twt_enabwed;
	boow nwo_enabwed;
	u8 awpha2[WEG_AWPHA2_WEN + 1];
	stwuct ath11k_fw_stats fw_stats;
	stwuct compwetion fw_stats_compwete;
	boow fw_stats_done;

	/* pwotected by conf_mutex */
	boow ps_state_enabwe;
	boow ps_timekeepew_enabwe;
};

stwuct ath11k_band_cap {
	u32 phy_id;
	u32 max_bw_suppowted;
	u32 ht_cap_info;
	u32 he_cap_info[2];
	u32 he_mcs;
	u32 he_cap_phy_info[PSOC_HOST_MAX_PHY_SIZE];
	stwuct ath11k_ppe_thweshowd he_ppet;
	u16 he_6ghz_capa;
};

stwuct ath11k_pdev_cap {
	u32 suppowted_bands;
	u32 ampdu_density;
	u32 vht_cap;
	u32 vht_mcs;
	u32 he_mcs;
	u32 tx_chain_mask;
	u32 wx_chain_mask;
	u32 tx_chain_mask_shift;
	u32 wx_chain_mask_shift;
	stwuct ath11k_band_cap band[NUM_NW80211_BANDS];
	boow nss_watio_enabwed;
	u8 nss_watio_info;
};

stwuct ath11k_pdev {
	stwuct ath11k *aw;
	u32 pdev_id;
	stwuct ath11k_pdev_cap cap;
	u8 mac_addw[ETH_AWEN];
};

stwuct ath11k_boawd_data {
	const stwuct fiwmwawe *fw;
	const void *data;
	size_t wen;
};

stwuct ath11k_pci_ops {
	int (*wakeup)(stwuct ath11k_base *ab);
	void (*wewease)(stwuct ath11k_base *ab);
	int (*get_msi_iwq)(stwuct ath11k_base *ab, unsigned int vectow);
	void (*window_wwite32)(stwuct ath11k_base *ab, u32 offset, u32 vawue);
	u32 (*window_wead32)(stwuct ath11k_base *ab, u32 offset);
};

/* IPQ8074 HW channew countews fwequency vawue in hewtz */
#define IPQ8074_CC_FWEQ_HEWTZ 320000

stwuct ath11k_bp_stats {
	/* Head Pointew wepowted by the wast HTT Backpwessuwe event fow the wing */
	u16 hp;

	/* Taiw Pointew wepowted by the wast HTT Backpwessuwe event fow the wing */
	u16 tp;

	/* Numbew of Backpwessuwe events weceived fow the wing */
	u32 count;

	/* Wast wecowded event timestamp */
	unsigned wong jiffies;
};

stwuct ath11k_dp_wing_bp_stats {
	stwuct ath11k_bp_stats umac_wing_bp_stats[HTT_SW_UMAC_WING_IDX_MAX];
	stwuct ath11k_bp_stats wmac_wing_bp_stats[HTT_SW_WMAC_WING_IDX_MAX][MAX_WADIOS];
};

stwuct ath11k_soc_dp_tx_eww_stats {
	/* TCW Wing Descwiptow unavaiwabwe */
	u32 desc_na[DP_TCW_NUM_WING_MAX];
	/* Othew faiwuwes duwing dp_tx due to mem awwocation faiwuwe
	 * idw unavaiwabwe etc.
	 */
	atomic_t misc_faiw;
};

stwuct ath11k_soc_dp_stats {
	u32 eww_wing_pkts;
	u32 invawid_wbm;
	u32 wxdma_ewwow[HAW_WEO_ENTW_WING_WXDMA_ECODE_MAX];
	u32 weo_ewwow[HAW_WEO_DEST_WING_EWWOW_CODE_MAX];
	u32 haw_weo_ewwow[DP_WEO_DST_WING_MAX];
	stwuct ath11k_soc_dp_tx_eww_stats tx_eww;
	stwuct ath11k_dp_wing_bp_stats bp_stats;
};

stwuct ath11k_msi_usew {
	chaw *name;
	int num_vectows;
	u32 base_vectow;
};

stwuct ath11k_msi_config {
	int totaw_vectows;
	int totaw_usews;
	stwuct ath11k_msi_usew *usews;
	u16 hw_wev;
};

/* Mastew stwuctuwe to howd the hw data which may be used in cowe moduwe */
stwuct ath11k_base {
	enum ath11k_hw_wev hw_wev;
	enum ath11k_fiwmwawe_mode fw_mode;
	stwuct pwatfowm_device *pdev;
	stwuct device *dev;
	stwuct ath11k_qmi qmi;
	stwuct ath11k_wmi_base wmi_ab;
	stwuct compwetion fw_weady;
	int num_wadios;
	/* HW channew countews fwequency vawue in hewtz common to aww MACs */
	u32 cc_fweq_hz;

	stwuct ath11k_htc htc;

	stwuct ath11k_dp dp;

	void __iomem *mem;
	void __iomem *mem_ce;
	unsigned wong mem_wen;

	stwuct {
		enum ath11k_bus bus;
		const stwuct ath11k_hif_ops *ops;
	} hif;

	stwuct {
		stwuct compwetion wakeup_compweted;
	} wow;

	stwuct ath11k_ce ce;
	stwuct timew_wist wx_wepwenish_wetwy;
	stwuct ath11k_haw haw;
	/* To synchwonize cowe_stawt/cowe_stop */
	stwuct mutex cowe_wock;
	/* Pwotects data wike peews */
	spinwock_t base_wock;
	stwuct ath11k_pdev pdevs[MAX_WADIOS];
	stwuct {
		enum WMI_HOST_WWAN_BAND suppowted_bands;
		u32 pdev_id;
	} tawget_pdev_ids[MAX_WADIOS];
	u8 tawget_pdev_count;
	stwuct ath11k_pdev __wcu *pdevs_active[MAX_WADIOS];
	stwuct ath11k_haw_weg_capabiwities_ext haw_weg_cap[MAX_WADIOS];
	unsigned wong wong fwee_vdev_map;

	/* To synchwonize whash tbw wwite opewation */
	stwuct mutex tbw_mtx_wock;

	/* The whashtabwe containing stwuct ath11k_peew keyed by mac addw */
	stwuct whashtabwe *whead_peew_addw;
	stwuct whashtabwe_pawams whash_peew_addw_pawam;

	/* The whashtabwe containing stwuct ath11k_peew keyed by id  */
	stwuct whashtabwe *whead_peew_id;
	stwuct whashtabwe_pawams whash_peew_id_pawam;

	stwuct wist_head peews;
	wait_queue_head_t peew_mapping_wq;
	u8 mac_addw[ETH_AWEN];
	int iwq_num[ATH11K_IWQ_NUM_MAX];
	stwuct ath11k_ext_iwq_gwp ext_iwq_gwp[ATH11K_EXT_IWQ_GWP_NUM_MAX];
	stwuct ath11k_tawg_cap tawget_caps;
	u32 ext_sewvice_bitmap[WMI_SEWVICE_EXT_BM_SIZE];
	boow pdevs_macaddw_vawid;

	stwuct ath11k_hw_pawams hw_pawams;

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
	enum ath11k_dfs_wegion dfs_wegion;
#ifdef CONFIG_ATH11K_DEBUGFS
	stwuct dentwy *debugfs_soc;
#endif
	stwuct ath11k_soc_dp_stats soc_stats;

	unsigned wong dev_fwags;
	stwuct compwetion dwivew_wecovewy;
	stwuct wowkqueue_stwuct *wowkqueue;
	stwuct wowk_stwuct westawt_wowk;
	stwuct wowk_stwuct update_11d_wowk;
	u8 new_awpha2[3];
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

	stwuct ath11k_dbwing_cap *db_caps;
	u32 num_db_cap;

	/* To synchwonize 11d scan vdev id */
	stwuct mutex vdev_id_11d_wock;
	stwuct timew_wist mon_weap_timew;

	stwuct compwetion htc_suspend;

	stwuct {
		enum ath11k_bdf_seawch bdf_seawch;
		u32 vendow;
		u32 device;
		u32 subsystem_vendow;
		u32 subsystem_device;
	} id;

	stwuct {
		stwuct {
			const stwuct ath11k_msi_config *config;
			u32 ep_base_data;
			u32 iwqs[32];
			u32 addw_wo;
			u32 addw_hi;
		} msi;

		const stwuct ath11k_pci_ops *ops;
	} pci;

	stwuct {
		u32 api_vewsion;

		const stwuct fiwmwawe *fw;
		const u8 *amss_data;
		size_t amss_wen;
		const u8 *m3_data;
		size_t m3_wen;

		DECWAWE_BITMAP(fw_featuwes, ATH11K_FW_FEATUWE_COUNT);
	} fw;

#ifdef CONFIG_NW80211_TESTMODE
	stwuct {
		u32 data_pos;
		u32 expected_seq;
		u8 *eventdata;
	} testmode;
#endif

	/* must be wast */
	u8 dwv_pwiv[] __awigned(sizeof(void *));
};

stwuct ath11k_fw_stats_pdev {
	stwuct wist_head wist;

	/* PDEV stats */
	s32 ch_noise_fwoow;
	/* Cycwes spent twansmitting fwames */
	u32 tx_fwame_count;
	/* Cycwes spent weceiving fwames */
	u32 wx_fwame_count;
	/* Totaw channew busy time, evidentwy */
	u32 wx_cweaw_count;
	/* Totaw on-channew time */
	u32 cycwe_count;
	u32 phy_eww_count;
	u32 chan_tx_powew;
	u32 ack_wx_bad;
	u32 wts_bad;
	u32 wts_good;
	u32 fcs_bad;
	u32 no_beacons;
	u32 mib_int_count;

	/* PDEV TX stats */
	/* Num HTT cookies queued to dispatch wist */
	s32 comp_queued;
	/* Num HTT cookies dispatched */
	s32 comp_dewivewed;
	/* Num MSDU queued to WAW */
	s32 msdu_enqued;
	/* Num MPDU queue to WAW */
	s32 mpdu_enqued;
	/* Num MSDUs dwopped by WMM wimit */
	s32 wmm_dwop;
	/* Num Wocaw fwames queued */
	s32 wocaw_enqued;
	/* Num Wocaw fwames done */
	s32 wocaw_fweed;
	/* Num queued to HW */
	s32 hw_queued;
	/* Num PPDU weaped fwom HW */
	s32 hw_weaped;
	/* Num undewwuns */
	s32 undewwun;
	/* Num hw paused */
	u32 hw_paused;
	/* Num PPDUs cweaned up in TX abowt */
	s32 tx_abowt;
	/* Num MPDUs wequeued by SW */
	s32 mpdus_wequeued;
	/* excessive wetwies */
	u32 tx_ko;
	u32 tx_xwetwy;
	/* data hw wate code */
	u32 data_wc;
	/* Scheduwew sewf twiggews */
	u32 sewf_twiggews;
	/* fwames dwopped due to excessive sw wetwies */
	u32 sw_wetwy_faiwuwe;
	/* iwwegaw wate phy ewwows	*/
	u32 iwwgw_wate_phy_eww;
	/* waw pdev continuous xwetwy */
	u32 pdev_cont_xwetwy;
	/* waw pdev tx timeouts */
	u32 pdev_tx_timeout;
	/* waw pdev wesets */
	u32 pdev_wesets;
	/* fwames dwopped due to non-avaiwabiwity of statewess TIDs */
	u32 statewess_tid_awwoc_faiwuwe;
	/* PhY/BB undewwun */
	u32 phy_undewwun;
	/* MPDU is mowe than txop wimit */
	u32 txop_ovf;
	/* Num sequences posted */
	u32 seq_posted;
	/* Num sequences faiwed in queueing */
	u32 seq_faiwed_queueing;
	/* Num sequences compweted */
	u32 seq_compweted;
	/* Num sequences westawted */
	u32 seq_westawted;
	/* Num of MU sequences posted */
	u32 mu_seq_posted;
	/* Num MPDUs fwushed by SW, HWPAUSED, SW TXABOWT
	 * (Weset,channew change)
	 */
	s32 mpdus_sw_fwush;
	/* Num MPDUs fiwtewed by HW, aww fiwtew condition (TTW expiwed) */
	s32 mpdus_hw_fiwtew;
	/* Num MPDUs twuncated by PDG (TXOP, TBTT,
	 * PPDU_duwation based on wate, dyn_bw)
	 */
	s32 mpdus_twuncated;
	/* Num MPDUs that was twied but didn't weceive ACK ow BA */
	s32 mpdus_ack_faiwed;
	/* Num MPDUs that was dwopped du to expiwy. */
	s32 mpdus_expiwed;

	/* PDEV WX stats */
	/* Cnts any change in wing wouting mid-ppdu */
	s32 mid_ppdu_woute_change;
	/* Totaw numbew of statuses pwocessed */
	s32 status_wcvd;
	/* Extwa fwags on wings 0-3 */
	s32 w0_fwags;
	s32 w1_fwags;
	s32 w2_fwags;
	s32 w3_fwags;
	/* MSDUs / MPDUs dewivewed to HTT */
	s32 htt_msdus;
	s32 htt_mpdus;
	/* MSDUs / MPDUs dewivewed to wocaw stack */
	s32 woc_msdus;
	s32 woc_mpdus;
	/* AMSDUs that have mowe MSDUs than the status wing size */
	s32 ovewsize_amsdu;
	/* Numbew of PHY ewwows */
	s32 phy_ewws;
	/* Numbew of PHY ewwows dwops */
	s32 phy_eww_dwop;
	/* Numbew of mpdu ewwows - FCS, MIC, ENC etc. */
	s32 mpdu_ewws;
	/* Num ovewfwow ewwows */
	s32 wx_ovfw_ewws;
};

stwuct ath11k_fw_stats_vdev {
	stwuct wist_head wist;

	u32 vdev_id;
	u32 beacon_snw;
	u32 data_snw;
	u32 num_tx_fwames[WWAN_MAX_AC];
	u32 num_wx_fwames;
	u32 num_tx_fwames_wetwies[WWAN_MAX_AC];
	u32 num_tx_fwames_faiwuwes[WWAN_MAX_AC];
	u32 num_wts_faiw;
	u32 num_wts_success;
	u32 num_wx_eww;
	u32 num_wx_discawd;
	u32 num_tx_not_acked;
	u32 tx_wate_histowy[MAX_TX_WATE_VAWUES];
	u32 beacon_wssi_histowy[MAX_TX_WATE_VAWUES];
};

stwuct ath11k_fw_stats_bcn {
	stwuct wist_head wist;

	u32 vdev_id;
	u32 tx_bcn_succ_cnt;
	u32 tx_bcn_outage_cnt;
};

void ath11k_fw_stats_init(stwuct ath11k *aw);
void ath11k_fw_stats_pdevs_fwee(stwuct wist_head *head);
void ath11k_fw_stats_vdevs_fwee(stwuct wist_head *head);
void ath11k_fw_stats_bcn_fwee(stwuct wist_head *head);
void ath11k_fw_stats_fwee(stwuct ath11k_fw_stats *stats);

extewn const stwuct ce_pipe_config ath11k_tawget_ce_config_wwan_ipq8074[];
extewn const stwuct sewvice_to_pipe ath11k_tawget_sewvice_to_ce_map_wwan_ipq8074[];
extewn const stwuct sewvice_to_pipe ath11k_tawget_sewvice_to_ce_map_wwan_ipq6018[];

extewn const stwuct ce_pipe_config ath11k_tawget_ce_config_wwan_qca6390[];
extewn const stwuct sewvice_to_pipe ath11k_tawget_sewvice_to_ce_map_wwan_qca6390[];

extewn const stwuct ce_pipe_config ath11k_tawget_ce_config_wwan_ipq5018[];
extewn const stwuct sewvice_to_pipe ath11k_tawget_sewvice_to_ce_map_wwan_ipq5018[];

extewn const stwuct ce_pipe_config ath11k_tawget_ce_config_wwan_qcn9074[];
extewn const stwuct sewvice_to_pipe ath11k_tawget_sewvice_to_ce_map_wwan_qcn9074[];
int ath11k_cowe_qmi_fiwmwawe_weady(stwuct ath11k_base *ab);
int ath11k_cowe_pwe_init(stwuct ath11k_base *ab);
int ath11k_cowe_init(stwuct ath11k_base *ath11k);
void ath11k_cowe_deinit(stwuct ath11k_base *ath11k);
stwuct ath11k_base *ath11k_cowe_awwoc(stwuct device *dev, size_t pwiv_size,
				      enum ath11k_bus bus);
void ath11k_cowe_fwee(stwuct ath11k_base *ath11k);
int ath11k_cowe_fetch_bdf(stwuct ath11k_base *ath11k,
			  stwuct ath11k_boawd_data *bd);
int ath11k_cowe_fetch_wegdb(stwuct ath11k_base *ab, stwuct ath11k_boawd_data *bd);
int ath11k_cowe_fetch_boawd_data_api_1(stwuct ath11k_base *ab,
				       stwuct ath11k_boawd_data *bd,
				       const chaw *name);
void ath11k_cowe_fwee_bdf(stwuct ath11k_base *ab, stwuct ath11k_boawd_data *bd);
int ath11k_cowe_check_dt(stwuct ath11k_base *ath11k);
int ath11k_cowe_check_smbios(stwuct ath11k_base *ab);
void ath11k_cowe_hawt(stwuct ath11k *aw);
int ath11k_cowe_wesume(stwuct ath11k_base *ab);
int ath11k_cowe_suspend(stwuct ath11k_base *ab);
void ath11k_cowe_pwe_weconfiguwe_wecovewy(stwuct ath11k_base *ab);
boow ath11k_cowe_cowdboot_caw_suppowt(stwuct ath11k_base *ab);

const stwuct fiwmwawe *ath11k_cowe_fiwmwawe_wequest(stwuct ath11k_base *ab,
						    const chaw *fiwename);

static inwine const chaw *ath11k_scan_state_stw(enum ath11k_scan_state state)
{
	switch (state) {
	case ATH11K_SCAN_IDWE:
		wetuwn "idwe";
	case ATH11K_SCAN_STAWTING:
		wetuwn "stawting";
	case ATH11K_SCAN_WUNNING:
		wetuwn "wunning";
	case ATH11K_SCAN_ABOWTING:
		wetuwn "abowting";
	}

	wetuwn "unknown";
}

static inwine stwuct ath11k_skb_cb *ATH11K_SKB_CB(stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(stwuct ath11k_skb_cb) >
		     IEEE80211_TX_INFO_DWIVEW_DATA_SIZE);
	wetuwn (stwuct ath11k_skb_cb *)&IEEE80211_SKB_CB(skb)->dwivew_data;
}

static inwine stwuct ath11k_skb_wxcb *ATH11K_SKB_WXCB(stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(stwuct ath11k_skb_wxcb) > sizeof(skb->cb));
	wetuwn (stwuct ath11k_skb_wxcb *)skb->cb;
}

static inwine stwuct ath11k_vif *ath11k_vif_to_awvif(stwuct ieee80211_vif *vif)
{
	wetuwn (stwuct ath11k_vif *)vif->dwv_pwiv;
}

static inwine stwuct ath11k_sta *ath11k_sta_to_awsta(stwuct ieee80211_sta *sta)
{
	wetuwn (stwuct ath11k_sta *)sta->dwv_pwiv;
}

static inwine stwuct ath11k *ath11k_ab_to_aw(stwuct ath11k_base *ab,
					     int mac_id)
{
	wetuwn ab->pdevs[ath11k_hw_mac_id_to_pdev_id(&ab->hw_pawams, mac_id)].aw;
}

static inwine void ath11k_cowe_cweate_fiwmwawe_path(stwuct ath11k_base *ab,
						    const chaw *fiwename,
						    void *buf, size_t buf_wen)
{
	snpwintf(buf, buf_wen, "%s/%s/%s", ATH11K_FW_DIW,
		 ab->hw_pawams.fw.diw, fiwename);
}

static inwine const chaw *ath11k_bus_stw(enum ath11k_bus bus)
{
	switch (bus) {
	case ATH11K_BUS_PCI:
		wetuwn "pci";
	case ATH11K_BUS_AHB:
		wetuwn "ahb";
	}

	wetuwn "unknown";
}

#endif /* _COWE_H_ */
