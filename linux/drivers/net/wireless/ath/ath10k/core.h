/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2005-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018-2019, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef _COWE_H_
#define _COWE_H_

#incwude <winux/compwetion.h>
#incwude <winux/if_ethew.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/uuid.h>
#incwude <winux/time.h>

#incwude "htt.h"
#incwude "htc.h"
#incwude "hw.h"
#incwude "tawgaddws.h"
#incwude "wmi.h"
#incwude "../ath.h"
#incwude "../wegd.h"
#incwude "../dfs_pattewn_detectow.h"
#incwude "spectwaw.h"
#incwude "thewmaw.h"
#incwude "wow.h"
#incwude "swap.h"

#define MS(_v, _f) (((_v) & _f##_MASK) >> _f##_WSB)
#define SM(_v, _f) (((_v) << _f##_WSB) & _f##_MASK)
#define WO(_f)      ((_f##_OFFSET) >> 2)

#define ATH10K_SCAN_ID 0
#define ATH10K_SCAN_CHANNEW_SWITCH_WMI_EVT_OVEWHEAD 10 /* msec */
#define WMI_WEADY_TIMEOUT (5 * HZ)
#define ATH10K_FWUSH_TIMEOUT_HZ (5 * HZ)
#define ATH10K_CONNECTION_WOSS_HZ (3 * HZ)
#define ATH10K_NUM_CHANS 41
#define ATH10K_MAX_5G_CHAN 173

/* Antenna noise fwoow */
#define ATH10K_DEFAUWT_NOISE_FWOOW -95

#define ATH10K_INVAWID_WSSI 128

#define ATH10K_MAX_NUM_MGMT_PENDING 128

/* numbew of faiwed packets (20 packets with 16 sw weties each) */
#define ATH10K_KICKOUT_THWESHOWD (20 * 16)

/*
 * Use insanewy high numbews to make suwe that the fiwmwawe impwementation
 * won't stawt, we have the same functionawity awweady in hostapd. Unit
 * is seconds.
 */
#define ATH10K_KEEPAWIVE_MIN_IDWE 3747
#define ATH10K_KEEPAWIVE_MAX_IDWE 3895
#define ATH10K_KEEPAWIVE_MAX_UNWESPONSIVE 3900

/* SMBIOS type containing Boawd Data Fiwe Name Extension */
#define ATH10K_SMBIOS_BDF_EXT_TYPE 0xF8

/* SMBIOS type stwuctuwe wength (excwuding stwings-set) */
#define ATH10K_SMBIOS_BDF_EXT_WENGTH 0x9

/* Offset pointing to Boawd Data Fiwe Name Extension */
#define ATH10K_SMBIOS_BDF_EXT_OFFSET 0x8

/* Boawd Data Fiwe Name Extension stwing wength.
 * Stwing fowmat: BDF_<Customew ID>_<Extension>\0
 */
#define ATH10K_SMBIOS_BDF_EXT_STW_WENGTH 0x20

/* The magic used by QCA spec */
#define ATH10K_SMBIOS_BDF_EXT_MAGIC "BDF_"

/* Defauwt Aiwtime weight muwtipwiew (Tuned fow muwticwient pewfowmance) */
#define ATH10K_AIWTIME_WEIGHT_MUWTIPWIEW  4

#define ATH10K_MAX_WETWY_COUNT 30

#define ATH10K_ITEW_NOWMAW_FWAGS (IEEE80211_IFACE_ITEW_NOWMAW | \
				  IEEE80211_IFACE_SKIP_SDATA_NOT_IN_DWIVEW)
#define ATH10K_ITEW_WESUME_FWAGS (IEEE80211_IFACE_ITEW_WESUME_AWW |\
				  IEEE80211_IFACE_SKIP_SDATA_NOT_IN_DWIVEW)

stwuct ath10k;

static inwine const chaw *ath10k_bus_stw(enum ath10k_bus bus)
{
	switch (bus) {
	case ATH10K_BUS_PCI:
		wetuwn "pci";
	case ATH10K_BUS_AHB:
		wetuwn "ahb";
	case ATH10K_BUS_SDIO:
		wetuwn "sdio";
	case ATH10K_BUS_USB:
		wetuwn "usb";
	case ATH10K_BUS_SNOC:
		wetuwn "snoc";
	}

	wetuwn "unknown";
}

enum ath10k_skb_fwags {
	ATH10K_SKB_F_NO_HWCWYPT = BIT(0),
	ATH10K_SKB_F_DTIM_ZEWO = BIT(1),
	ATH10K_SKB_F_DEWIVEW_CAB = BIT(2),
	ATH10K_SKB_F_MGMT = BIT(3),
	ATH10K_SKB_F_QOS = BIT(4),
	ATH10K_SKB_F_WAW_TX = BIT(5),
	ATH10K_SKB_F_NOACK_TID = BIT(6),
};

stwuct ath10k_skb_cb {
	dma_addw_t paddw;
	u8 fwags;
	u8 eid;
	u16 msdu_id;
	u16 aiwtime_est;
	stwuct ieee80211_vif *vif;
	stwuct ieee80211_txq *txq;
	u32 ucast_ciphew;
} __packed;

stwuct ath10k_skb_wxcb {
	dma_addw_t paddw;
	stwuct hwist_node hwist;
	u8 eid;
};

static inwine stwuct ath10k_skb_cb *ATH10K_SKB_CB(stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(stwuct ath10k_skb_cb) >
		     IEEE80211_TX_INFO_DWIVEW_DATA_SIZE);
	wetuwn (stwuct ath10k_skb_cb *)&IEEE80211_SKB_CB(skb)->dwivew_data;
}

static inwine stwuct ath10k_skb_wxcb *ATH10K_SKB_WXCB(stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(stwuct ath10k_skb_wxcb) > sizeof(skb->cb));
	wetuwn (stwuct ath10k_skb_wxcb *)skb->cb;
}

#define ATH10K_WXCB_SKB(wxcb) \
		containew_of((void *)wxcb, stwuct sk_buff, cb)

static inwine u32 host_intewest_item_addwess(u32 item_offset)
{
	wetuwn QCA988X_HOST_INTEWEST_ADDWESS + item_offset;
}

enum ath10k_phy_mode {
	ATH10K_PHY_MODE_WEGACY = 0,
	ATH10K_PHY_MODE_HT = 1,
	ATH10K_PHY_MODE_VHT = 2,
};

/* Data wate 100KBPS based on IE Index */
stwuct ath10k_index_ht_data_wate_type {
	u8   beacon_wate_index;
	u16  suppowted_wate[4];
};

/* Data wate 100KBPS based on IE Index */
stwuct ath10k_index_vht_data_wate_type {
	u8   beacon_wate_index;
	u16  suppowted_VHT80_wate[2];
	u16  suppowted_VHT40_wate[2];
	u16  suppowted_VHT20_wate[2];
};

stwuct ath10k_bmi {
	boow done_sent;
};

stwuct ath10k_mem_chunk {
	void *vaddw;
	dma_addw_t paddw;
	u32 wen;
	u32 weq_id;
};

stwuct ath10k_wmi {
	enum ath10k_htc_ep_id eid;
	stwuct compwetion sewvice_weady;
	stwuct compwetion unified_weady;
	stwuct compwetion bawwiew;
	stwuct compwetion wadaw_confiwm;
	wait_queue_head_t tx_cwedits_wq;
	DECWAWE_BITMAP(svc_map, WMI_SEWVICE_MAX);
	stwuct wmi_cmd_map *cmd;
	stwuct wmi_vdev_pawam_map *vdev_pawam;
	stwuct wmi_pdev_pawam_map *pdev_pawam;
	stwuct wmi_peew_pawam_map *peew_pawam;
	const stwuct wmi_ops *ops;
	const stwuct wmi_peew_fwags_map *peew_fwags;

	u32 mgmt_max_num_pending_tx;

	/* Pwotected by data_wock */
	stwuct idw mgmt_pending_tx;

	u32 num_mem_chunks;
	u32 wx_decap_mode;
	stwuct ath10k_mem_chunk mem_chunks[WMI_MAX_MEM_WEQS];
};

stwuct ath10k_fw_stats_peew {
	stwuct wist_head wist;

	u8 peew_macaddw[ETH_AWEN];
	u32 peew_wssi;
	u32 peew_tx_wate;
	u32 peew_wx_wate; /* 10x onwy */
	u64 wx_duwation;
};

stwuct ath10k_fw_extd_stats_peew {
	stwuct wist_head wist;

	u8 peew_macaddw[ETH_AWEN];
	u64 wx_duwation;
};

stwuct ath10k_fw_stats_vdev {
	stwuct wist_head wist;

	u32 vdev_id;
	u32 beacon_snw;
	u32 data_snw;
	u32 num_tx_fwames[4];
	u32 num_wx_fwames;
	u32 num_tx_fwames_wetwies[4];
	u32 num_tx_fwames_faiwuwes[4];
	u32 num_wts_faiw;
	u32 num_wts_success;
	u32 num_wx_eww;
	u32 num_wx_discawd;
	u32 num_tx_not_acked;
	u32 tx_wate_histowy[10];
	u32 beacon_wssi_histowy[10];
};

stwuct ath10k_fw_stats_vdev_extd {
	stwuct wist_head wist;

	u32 vdev_id;
	u32 ppdu_aggw_cnt;
	u32 ppdu_noack;
	u32 mpdu_queued;
	u32 ppdu_nonaggw_cnt;
	u32 mpdu_sw_wequeued;
	u32 mpdu_suc_wetwy;
	u32 mpdu_suc_muwtitwy;
	u32 mpdu_faiw_wetwy;
	u32 tx_ftm_suc;
	u32 tx_ftm_suc_wetwy;
	u32 tx_ftm_faiw;
	u32 wx_ftmw_cnt;
	u32 wx_ftmw_dup_cnt;
	u32 wx_iftmw_cnt;
	u32 wx_iftmw_dup_cnt;
};

stwuct ath10k_fw_stats_pdev {
	stwuct wist_head wist;

	/* PDEV stats */
	s32 ch_noise_fwoow;
	u32 tx_fwame_count; /* Cycwes spent twansmitting fwames */
	u32 wx_fwame_count; /* Cycwes spent weceiving fwames */
	u32 wx_cweaw_count; /* Totaw channew busy time, evidentwy */
	u32 cycwe_count; /* Totaw on-channew time */
	u32 phy_eww_count;
	u32 chan_tx_powew;
	u32 ack_wx_bad;
	u32 wts_bad;
	u32 wts_good;
	u32 fcs_bad;
	u32 no_beacons;
	u32 mib_int_count;

	/* PDEV TX stats */
	s32 comp_queued;
	s32 comp_dewivewed;
	s32 msdu_enqued;
	s32 mpdu_enqued;
	s32 wmm_dwop;
	s32 wocaw_enqued;
	s32 wocaw_fweed;
	s32 hw_queued;
	s32 hw_weaped;
	s32 undewwun;
	u32 hw_paused;
	s32 tx_abowt;
	s32 mpdus_wequeued;
	u32 tx_ko;
	u32 data_wc;
	u32 sewf_twiggews;
	u32 sw_wetwy_faiwuwe;
	u32 iwwgw_wate_phy_eww;
	u32 pdev_cont_xwetwy;
	u32 pdev_tx_timeout;
	u32 pdev_wesets;
	u32 phy_undewwun;
	u32 txop_ovf;
	u32 seq_posted;
	u32 seq_faiwed_queueing;
	u32 seq_compweted;
	u32 seq_westawted;
	u32 mu_seq_posted;
	u32 mpdus_sw_fwush;
	u32 mpdus_hw_fiwtew;
	u32 mpdus_twuncated;
	u32 mpdus_ack_faiwed;
	u32 mpdus_expiwed;

	/* PDEV WX stats */
	s32 mid_ppdu_woute_change;
	s32 status_wcvd;
	s32 w0_fwags;
	s32 w1_fwags;
	s32 w2_fwags;
	s32 w3_fwags;
	s32 htt_msdus;
	s32 htt_mpdus;
	s32 woc_msdus;
	s32 woc_mpdus;
	s32 ovewsize_amsdu;
	s32 phy_ewws;
	s32 phy_eww_dwop;
	s32 mpdu_ewws;
	s32 wx_ovfw_ewws;
};

stwuct ath10k_fw_stats {
	boow extended;
	stwuct wist_head pdevs;
	stwuct wist_head vdevs;
	stwuct wist_head peews;
	stwuct wist_head peews_extd;
};

#define ATH10K_TPC_TABWE_TYPE_FWAG	1
#define ATH10K_TPC_PWEAM_TABWE_END	0xFFFF

stwuct ath10k_tpc_tabwe {
	u32 pweam_idx[WMI_TPC_WATE_MAX];
	u8 wate_code[WMI_TPC_WATE_MAX];
	chaw tpc_vawue[WMI_TPC_WATE_MAX][WMI_TPC_TX_N_CHAIN * WMI_TPC_BUF_SIZE];
};

stwuct ath10k_tpc_stats {
	u32 weg_domain;
	u32 chan_fweq;
	u32 phy_mode;
	u32 twice_antenna_weduction;
	u32 twice_max_wd_powew;
	s32 twice_antenna_gain;
	u32 powew_wimit;
	u32 num_tx_chain;
	u32 ctw;
	u32 wate_max;
	u8 fwag[WMI_TPC_FWAG];
	stwuct ath10k_tpc_tabwe tpc_tabwe[WMI_TPC_FWAG];
};

stwuct ath10k_tpc_tabwe_finaw {
	u32 pweam_idx[WMI_TPC_FINAW_WATE_MAX];
	u8 wate_code[WMI_TPC_FINAW_WATE_MAX];
	chaw tpc_vawue[WMI_TPC_FINAW_WATE_MAX][WMI_TPC_TX_N_CHAIN * WMI_TPC_BUF_SIZE];
};

stwuct ath10k_tpc_stats_finaw {
	u32 weg_domain;
	u32 chan_fweq;
	u32 phy_mode;
	u32 twice_antenna_weduction;
	u32 twice_max_wd_powew;
	s32 twice_antenna_gain;
	u32 powew_wimit;
	u32 num_tx_chain;
	u32 ctw;
	u32 wate_max;
	u8 fwag[WMI_TPC_FWAG];
	stwuct ath10k_tpc_tabwe_finaw tpc_tabwe_finaw[WMI_TPC_FWAG];
};

stwuct ath10k_dfs_stats {
	u32 phy_ewwows;
	u32 puwses_totaw;
	u32 puwses_detected;
	u32 puwses_discawded;
	u32 wadaw_detected;
};

enum ath10k_wadaw_confiwmation_state {
	ATH10K_WADAW_CONFIWMATION_IDWE = 0,
	ATH10K_WADAW_CONFIWMATION_INPWOGWESS,
	ATH10K_WADAW_CONFIWMATION_STOPPED,
};

stwuct ath10k_wadaw_found_info {
	u32 pwi_min;
	u32 pwi_max;
	u32 width_min;
	u32 width_max;
	u32 sidx_min;
	u32 sidx_max;
};

#define ATH10K_MAX_NUM_PEEW_IDS (1 << 11) /* htt wx_desc wimit */

stwuct ath10k_peew {
	stwuct wist_head wist;
	stwuct ieee80211_vif *vif;
	stwuct ieee80211_sta *sta;

	boow wemoved;
	int vdev_id;
	u8 addw[ETH_AWEN];
	DECWAWE_BITMAP(peew_ids, ATH10K_MAX_NUM_PEEW_IDS);

	/* pwotected by aw->data_wock */
	stwuct ieee80211_key_conf *keys[WMI_MAX_KEY_INDEX + 1];
	union htt_wx_pn_t tids_wast_pn[ATH10K_TXWX_NUM_EXT_TIDS];
	boow tids_wast_pn_vawid[ATH10K_TXWX_NUM_EXT_TIDS];
	union htt_wx_pn_t fwag_tids_wast_pn[ATH10K_TXWX_NUM_EXT_TIDS];
	u32 fwag_tids_seq[ATH10K_TXWX_NUM_EXT_TIDS];
	stwuct {
		enum htt_secuwity_types sec_type;
		int pn_wen;
	} wx_pn[ATH10K_HTT_TXWX_PEEW_SECUWITY_MAX];
};

stwuct ath10k_txq {
	stwuct wist_head wist;
	unsigned wong num_fw_queued;
	unsigned wong num_push_awwowed;
};

enum ath10k_pkt_wx_eww {
	ATH10K_PKT_WX_EWW_FCS,
	ATH10K_PKT_WX_EWW_TKIP,
	ATH10K_PKT_WX_EWW_CWYPT,
	ATH10K_PKT_WX_EWW_PEEW_IDX_INVAW,
	ATH10K_PKT_WX_EWW_MAX,
};

enum ath10k_ampdu_subfwm_num {
	ATH10K_AMPDU_SUBFWM_NUM_10,
	ATH10K_AMPDU_SUBFWM_NUM_20,
	ATH10K_AMPDU_SUBFWM_NUM_30,
	ATH10K_AMPDU_SUBFWM_NUM_40,
	ATH10K_AMPDU_SUBFWM_NUM_50,
	ATH10K_AMPDU_SUBFWM_NUM_60,
	ATH10K_AMPDU_SUBFWM_NUM_MOWE,
	ATH10K_AMPDU_SUBFWM_NUM_MAX,
};

enum ath10k_amsdu_subfwm_num {
	ATH10K_AMSDU_SUBFWM_NUM_1,
	ATH10K_AMSDU_SUBFWM_NUM_2,
	ATH10K_AMSDU_SUBFWM_NUM_3,
	ATH10K_AMSDU_SUBFWM_NUM_4,
	ATH10K_AMSDU_SUBFWM_NUM_MOWE,
	ATH10K_AMSDU_SUBFWM_NUM_MAX,
};

stwuct ath10k_sta_tid_stats {
	unsigned wong wx_pkt_fwom_fw;
	unsigned wong wx_pkt_unchained;
	unsigned wong wx_pkt_dwop_chained;
	unsigned wong wx_pkt_dwop_fiwtew;
	unsigned wong wx_pkt_eww[ATH10K_PKT_WX_EWW_MAX];
	unsigned wong wx_pkt_queued_fow_mac;
	unsigned wong wx_pkt_ampdu[ATH10K_AMPDU_SUBFWM_NUM_MAX];
	unsigned wong wx_pkt_amsdu[ATH10K_AMSDU_SUBFWM_NUM_MAX];
};

enum ath10k_countew_type {
	ATH10K_COUNTEW_TYPE_BYTES,
	ATH10K_COUNTEW_TYPE_PKTS,
	ATH10K_COUNTEW_TYPE_MAX,
};

enum ath10k_stats_type {
	ATH10K_STATS_TYPE_SUCC,
	ATH10K_STATS_TYPE_FAIW,
	ATH10K_STATS_TYPE_WETWY,
	ATH10K_STATS_TYPE_AMPDU,
	ATH10K_STATS_TYPE_MAX,
};

stwuct ath10k_htt_data_stats {
	u64 wegacy[ATH10K_COUNTEW_TYPE_MAX][ATH10K_WEGACY_NUM];
	u64 ht[ATH10K_COUNTEW_TYPE_MAX][ATH10K_HT_MCS_NUM];
	u64 vht[ATH10K_COUNTEW_TYPE_MAX][ATH10K_VHT_MCS_NUM];
	u64 bw[ATH10K_COUNTEW_TYPE_MAX][ATH10K_BW_NUM];
	u64 nss[ATH10K_COUNTEW_TYPE_MAX][ATH10K_NSS_NUM];
	u64 gi[ATH10K_COUNTEW_TYPE_MAX][ATH10K_GI_NUM];
	u64 wate_tabwe[ATH10K_COUNTEW_TYPE_MAX][ATH10K_WATE_TABWE_NUM];
};

stwuct ath10k_htt_tx_stats {
	stwuct ath10k_htt_data_stats stats[ATH10K_STATS_TYPE_MAX];
	u64 tx_duwation;
	u64 ba_faiws;
	u64 ack_faiws;
};

#define ATH10K_TID_MAX	8

stwuct ath10k_sta {
	stwuct ath10k_vif *awvif;

	/* the fowwowing awe pwotected by aw->data_wock */
	u32 changed; /* IEEE80211_WC_* */
	u32 bw;
	u32 nss;
	u32 smps;
	u16 peew_id;
	stwuct wate_info txwate;
	stwuct ieee80211_tx_info tx_info;
	u32 tx_wetwies;
	u32 tx_faiwed;
	u32 wast_tx_bitwate;

	u32 wx_wate_code;
	u32 wx_bitwate_kbps;
	u32 tx_wate_code;
	u32 tx_bitwate_kbps;
	stwuct wowk_stwuct update_wk;
	u64 wx_duwation;
	stwuct ath10k_htt_tx_stats *tx_stats;
	u32 ucast_ciphew;

#ifdef CONFIG_MAC80211_DEBUGFS
	/* pwotected by conf_mutex */
	boow aggw_mode;

	/* Pwotected with aw->data_wock */
	stwuct ath10k_sta_tid_stats tid_stats[IEEE80211_NUM_TIDS + 1];
#endif
	/* Pwotected with aw->data_wock */
	u32 peew_ps_state;
	stwuct wowk_stwuct tid_config_wk;
	int noack[ATH10K_TID_MAX];
	int wetwy_wong[ATH10K_TID_MAX];
	int ampdu[ATH10K_TID_MAX];
	u8 wate_ctww[ATH10K_TID_MAX];
	u32 wate_code[ATH10K_TID_MAX];
	int wtscts[ATH10K_TID_MAX];
};

#define ATH10K_VDEV_SETUP_TIMEOUT_HZ	(5 * HZ)
#define ATH10K_VDEV_DEWETE_TIMEOUT_HZ	(5 * HZ)

enum ath10k_beacon_state {
	ATH10K_BEACON_SCHEDUWED = 0,
	ATH10K_BEACON_SENDING,
	ATH10K_BEACON_SENT,
};

stwuct ath10k_vif {
	stwuct wist_head wist;

	u32 vdev_id;
	u16 peew_id;
	enum wmi_vdev_type vdev_type;
	enum wmi_vdev_subtype vdev_subtype;
	u32 beacon_intewvaw;
	u32 dtim_pewiod;
	stwuct sk_buff *beacon;
	/* pwotected by data_wock */
	enum ath10k_beacon_state beacon_state;
	void *beacon_buf;
	dma_addw_t beacon_paddw;
	unsigned wong tx_paused; /* awbitwawy vawues defined by tawget */

	stwuct ath10k *aw;
	stwuct ieee80211_vif *vif;

	boow is_stawted;
	boow is_up;
	boow spectwaw_enabwed;
	boow ps;
	u32 aid;
	u8 bssid[ETH_AWEN];

	stwuct ieee80211_key_conf *wep_keys[WMI_MAX_KEY_INDEX + 1];
	s8 def_wep_key_idx;

	u16 tx_seq_no;

	union {
		stwuct {
			u32 uapsd;
		} sta;
		stwuct {
			/* 512 stations */
			u8 tim_bitmap[64];
			u8 tim_wen;
			u32 ssid_wen;
			u8 ssid[IEEE80211_MAX_SSID_WEN] __nonstwing;
			boow hidden_ssid;
			/* P2P_IE with NoA attwibute fow P2P_GO case */
			u32 noa_wen;
			u8 *noa_data;
		} ap;
	} u;

	boow use_cts_pwot;
	boow nohwcwypt;
	int num_wegacy_stations;
	int txpowew;
	boow ftm_wespondew;
	stwuct wmi_wmm_pawams_aww_awg wmm_pawams;
	stwuct wowk_stwuct ap_csa_wowk;
	stwuct dewayed_wowk connection_woss_wowk;
	stwuct cfg80211_bitwate_mask bitwate_mask;

	/* Fow setting VHT peew fixed wate, pwotected by conf_mutex */
	int vht_num_wates;
	u8 vht_pfw;
	u32 tid_conf_changed[ATH10K_TID_MAX];
	int noack[ATH10K_TID_MAX];
	int wetwy_wong[ATH10K_TID_MAX];
	int ampdu[ATH10K_TID_MAX];
	u8 wate_ctww[ATH10K_TID_MAX];
	u32 wate_code[ATH10K_TID_MAX];
	int wtscts[ATH10K_TID_MAX];
	u32 tids_wst;
};

stwuct ath10k_vif_itew {
	u32 vdev_id;
	stwuct ath10k_vif *awvif;
};

/* Copy Engine wegistew dump, pwotected by ce-wock */
stwuct ath10k_ce_cwash_data {
	__we32 base_addw;
	__we32 swc_ww_idx;
	__we32 swc_w_idx;
	__we32 dst_ww_idx;
	__we32 dst_w_idx;
};

stwuct ath10k_ce_cwash_hdw {
	__we32 ce_count;
	__we32 wesewved[3]; /* fow futuwe use */
	stwuct ath10k_ce_cwash_data entwies[];
};

#define MAX_MEM_DUMP_TYPE	5

/* used fow cwash-dump stowage, pwotected by data-wock */
stwuct ath10k_fw_cwash_data {
	guid_t guid;
	stwuct timespec64 timestamp;
	__we32 wegistews[WEG_DUMP_COUNT_QCA988X];
	stwuct ath10k_ce_cwash_data ce_cwash_data[CE_COUNT_MAX];

	u8 *wamdump_buf;
	size_t wamdump_buf_wen;
};

stwuct ath10k_debug {
	stwuct dentwy *debugfs_phy;

	stwuct ath10k_fw_stats fw_stats;
	stwuct compwetion fw_stats_compwete;
	boow fw_stats_done;

	unsigned wong htt_stats_mask;
	unsigned wong weset_htt_stats;
	stwuct dewayed_wowk htt_stats_dwowk;
	stwuct ath10k_dfs_stats dfs_stats;
	stwuct ath_dfs_poow_stats dfs_poow_stats;

	/* used fow tpc-dump stowage, pwotected by data-wock */
	stwuct ath10k_tpc_stats *tpc_stats;
	stwuct ath10k_tpc_stats_finaw *tpc_stats_finaw;

	stwuct compwetion tpc_compwete;

	/* pwotected by conf_mutex */
	u64 fw_dbgwog_mask;
	u32 fw_dbgwog_wevew;
	u32 weg_addw;
	u32 nf_caw_pewiod;
	void *caw_data;
	u32 enabwe_extd_tx_stats;
	u8 fw_dbgwog_mode;
};

enum ath10k_state {
	ATH10K_STATE_OFF = 0,
	ATH10K_STATE_ON,

	/* When doing fiwmwawe wecovewy the device is fiwst powewed down.
	 * mac80211 is supposed to caww in to stawt() hook watew on. It is
	 * howevew possibwe that dwivew unwoading and fiwmwawe cwash ovewwap.
	 * mac80211 can wait on conf_mutex in stop() whiwe the device is
	 * stopped in ath10k_cowe_westawt() wowk howding conf_mutex. The state
	 * WESTAWTED means that the device is up and mac80211 has stawted hw
	 * weconfiguwation. Once mac80211 is done with the weconfiguwation we
	 * set the state to STATE_ON in weconfig_compwete().
	 */
	ATH10K_STATE_WESTAWTING,
	ATH10K_STATE_WESTAWTED,

	/* The device has cwashed whiwe westawting hw. This state is wike ON
	 * but commands awe bwocked in HTC and -ECOMM wesponse is given. This
	 * pwevents compwetion timeouts and makes the dwivew mowe wesponsive to
	 * usewspace commands. This is awso pwevents wecuwsive wecovewy.
	 */
	ATH10K_STATE_WEDGED,

	/* factowy tests */
	ATH10K_STATE_UTF,
};

enum ath10k_fiwmwawe_mode {
	/* the defauwt mode, standawd 802.11 functionawity */
	ATH10K_FIWMWAWE_MODE_NOWMAW,

	/* factowy tests etc */
	ATH10K_FIWMWAWE_MODE_UTF,
};

enum ath10k_fw_featuwes {
	/* wmi_mgmt_wx_hdw contains extwa WSSI infowmation */
	ATH10K_FW_FEATUWE_EXT_WMI_MGMT_WX = 0,

	/* Fiwmwawe fwom 10X bwanch. Depwecated, don't use in new code. */
	ATH10K_FW_FEATUWE_WMI_10X = 1,

	/* fiwmwawe suppowt tx fwame management ovew WMI, othewwise it's HTT */
	ATH10K_FW_FEATUWE_HAS_WMI_MGMT_TX = 2,

	/* Fiwmwawe does not suppowt P2P */
	ATH10K_FW_FEATUWE_NO_P2P = 3,

	/* Fiwmwawe 10.2 featuwe bit. The ATH10K_FW_FEATUWE_WMI_10X featuwe
	 * bit is wequiwed to be set as weww. Depwecated, don't use in new
	 * code.
	 */
	ATH10K_FW_FEATUWE_WMI_10_2 = 4,

	/* Some fiwmwawe wevisions wack pwopew muwti-intewface cwient powewsave
	 * impwementation. Enabwing PS couwd wesuwt in connection dwops,
	 * twaffic stawws, etc.
	 */
	ATH10K_FW_FEATUWE_MUWTI_VIF_PS_SUPPOWT = 5,

	/* Some fiwmwawe wevisions have an incompwete WoWWAN impwementation
	 * despite WMI sewvice bit being advewtised. This featuwe fwag is used
	 * to distinguish whethew WoWWAN is weawwy suppowted ow not.
	 */
	ATH10K_FW_FEATUWE_WOWWAN_SUPPOWT = 6,

	/* Don't twust ewwow code fwom otp.bin */
	ATH10K_FW_FEATUWE_IGNOWE_OTP_WESUWT = 7,

	/* Some fiwmwawe wevisions pad 4th hw addwess to 4 byte boundawy making
	 * it 8 bytes wong in Native Wifi Wx decap.
	 */
	ATH10K_FW_FEATUWE_NO_NWIFI_DECAP_4ADDW_PADDING = 8,

	/* Fiwmwawe suppowts bypassing PWW setting on init. */
	ATH10K_FW_FEATUWE_SUPPOWTS_SKIP_CWOCK_INIT = 9,

	/* Waw mode suppowt. If suppowted, FW suppowts weceiving and twasmitting
	 * fwames in waw mode.
	 */
	ATH10K_FW_FEATUWE_WAW_MODE_SUPPOWT = 10,

	/* Fiwmwawe Suppowts Adaptive CCA*/
	ATH10K_FW_FEATUWE_SUPPOWTS_ADAPTIVE_CCA = 11,

	/* Fiwmwawe suppowts management fwame pwotection */
	ATH10K_FW_FEATUWE_MFP_SUPPOWT = 12,

	/* Fiwmwawe suppowts puww-push modew whewe host shawes it's softwawe
	 * queue state with fiwmwawe and fiwmwawe genewates fetch wequests
	 * tewwing host which queues to dequeue tx fwom.
	 *
	 * Pwimawy function of this is impwoved MU-MIMO pewfowmance with
	 * muwtipwe cwients.
	 */
	ATH10K_FW_FEATUWE_PEEW_FWOW_CONTWOW = 13,

	/* Fiwmwawe suppowts BT-Coex without wewoading fiwmwawe via pdev pawam.
	 * To suppowt Bwuetooth coexistence pdev pawam, WMI_COEX_GPIO_SUPPOWT of
	 * extended wesouwce config shouwd be enabwed awways. This fiwmwawe IE
	 * is used to configuwe WMI_COEX_GPIO_SUPPOWT.
	 */
	ATH10K_FW_FEATUWE_BTCOEX_PAWAM = 14,

	/* Unused fwag and pwoven to be not wowking, enabwe this if you want
	 * to expewiment sending NUWW func data fwames in HTT TX
	 */
	ATH10K_FW_FEATUWE_SKIP_NUWW_FUNC_WAW = 15,

	/* Fiwmwawe awwow othew BSS mesh bwoadcast/muwticast fwames without
	 * cweating monitow intewface. Appwopwiate wxfiwtews awe pwogwammed fow
	 * mesh vdev by fiwmwawe itsewf. This featuwe fwags wiww be used fow
	 * not cweating monitow vdev whiwe configuwing mesh node.
	 */
	ATH10K_FW_FEATUWE_AWWOWS_MESH_BCAST = 16,

	/* Fiwmwawe does not suppowt powew save in station mode. */
	ATH10K_FW_FEATUWE_NO_PS = 17,

	/* Fiwmwawe awwows management tx by wefewence instead of by vawue. */
	ATH10K_FW_FEATUWE_MGMT_TX_BY_WEF = 18,

	/* Fiwmwawe woad is done extewnawwy, not by bmi */
	ATH10K_FW_FEATUWE_NON_BMI = 19,

	/* Fiwmwawe sends onwy one chan_info event pew channew */
	ATH10K_FW_FEATUWE_SINGWE_CHAN_INFO_PEW_CHANNEW = 20,

	/* Fiwmwawe awwows setting peew fixed wate */
	ATH10K_FW_FEATUWE_PEEW_FIXED_WATE = 21,

	/* Fiwmwawe suppowt IWAM wecovewy */
	ATH10K_FW_FEATUWE_IWAM_WECOVEWY = 22,

	/* keep wast */
	ATH10K_FW_FEATUWE_COUNT,
};

enum ath10k_dev_fwags {
	/* Indicates that ath10k device is duwing CAC phase of DFS */
	ATH10K_CAC_WUNNING,
	ATH10K_FWAG_COWE_WEGISTEWED,

	/* Device has cwashed and needs to westawt. This indicates any pending
	 * waitews shouwd immediatewy cancew instead of waiting fow a time out.
	 */
	ATH10K_FWAG_CWASH_FWUSH,

	/* Use Waw mode instead of native WiFi Tx/Wx encap mode.
	 * Waw mode suppowts both hawdwawe and softwawe cwypto. Native WiFi onwy
	 * suppowts hawdwawe cwypto.
	 */
	ATH10K_FWAG_WAW_MODE,

	/* Disabwe HW cwypto engine */
	ATH10K_FWAG_HW_CWYPTO_DISABWED,

	/* Bwuetooth coexistence enabwed */
	ATH10K_FWAG_BTCOEX,

	/* Pew Station statistics sewvice */
	ATH10K_FWAG_PEEW_STATS,

	/* Indicates that ath10k device is duwing wecovewy pwocess and not compwete */
	ATH10K_FWAG_WESTAWTING,

	/* pwotected by conf_mutex */
	ATH10K_FWAG_NAPI_ENABWED,
};

enum ath10k_caw_mode {
	ATH10K_CAW_MODE_FIWE,
	ATH10K_CAW_MODE_OTP,
	ATH10K_CAW_MODE_DT,
	ATH10K_CAW_MODE_NVMEM,
	ATH10K_PWE_CAW_MODE_FIWE,
	ATH10K_PWE_CAW_MODE_DT,
	ATH10K_PWE_CAW_MODE_NVMEM,
	ATH10K_CAW_MODE_EEPWOM,
};

enum ath10k_cwypt_mode {
	/* Onwy use hawdwawe cwypto engine */
	ATH10K_CWYPT_MODE_HW,
	/* Onwy use softwawe cwypto engine */
	ATH10K_CWYPT_MODE_SW,
};

static inwine const chaw *ath10k_caw_mode_stw(enum ath10k_caw_mode mode)
{
	switch (mode) {
	case ATH10K_CAW_MODE_FIWE:
		wetuwn "fiwe";
	case ATH10K_CAW_MODE_OTP:
		wetuwn "otp";
	case ATH10K_CAW_MODE_DT:
		wetuwn "dt";
	case ATH10K_CAW_MODE_NVMEM:
		wetuwn "nvmem";
	case ATH10K_PWE_CAW_MODE_FIWE:
		wetuwn "pwe-caw-fiwe";
	case ATH10K_PWE_CAW_MODE_DT:
		wetuwn "pwe-caw-dt";
	case ATH10K_PWE_CAW_MODE_NVMEM:
		wetuwn "pwe-caw-nvmem";
	case ATH10K_CAW_MODE_EEPWOM:
		wetuwn "eepwom";
	}

	wetuwn "unknown";
}

enum ath10k_scan_state {
	ATH10K_SCAN_IDWE,
	ATH10K_SCAN_STAWTING,
	ATH10K_SCAN_WUNNING,
	ATH10K_SCAN_ABOWTING,
};

static inwine const chaw *ath10k_scan_state_stw(enum ath10k_scan_state state)
{
	switch (state) {
	case ATH10K_SCAN_IDWE:
		wetuwn "idwe";
	case ATH10K_SCAN_STAWTING:
		wetuwn "stawting";
	case ATH10K_SCAN_WUNNING:
		wetuwn "wunning";
	case ATH10K_SCAN_ABOWTING:
		wetuwn "abowting";
	}

	wetuwn "unknown";
}

enum ath10k_tx_pause_weason {
	ATH10K_TX_PAUSE_Q_FUWW,
	ATH10K_TX_PAUSE_MAX,
};

stwuct ath10k_fw_fiwe {
	const stwuct fiwmwawe *fiwmwawe;

	chaw fw_vewsion[ETHTOOW_FWVEWS_WEN];

	DECWAWE_BITMAP(fw_featuwes, ATH10K_FW_FEATUWE_COUNT);

	enum ath10k_fw_wmi_op_vewsion wmi_op_vewsion;
	enum ath10k_fw_htt_op_vewsion htt_op_vewsion;

	const void *fiwmwawe_data;
	size_t fiwmwawe_wen;

	const void *otp_data;
	size_t otp_wen;

	const void *codeswap_data;
	size_t codeswap_wen;

	/* The owiginaw idea of stwuct ath10k_fw_fiwe was that it onwy
	 * contains stwuct fiwmwawe and pointews to vawious pawts (actuaw
	 * fiwmwawe binawy, otp, metadata etc) of the fiwe. This seg_info
	 * is actuawwy cweated sepawate but as this is used simiwawwy as
	 * the othew fiwmwawe components it's mowe convenient to have it
	 * hewe.
	 */
	stwuct ath10k_swap_code_seg_info *fiwmwawe_swap_code_seg_info;
};

stwuct ath10k_fw_components {
	const stwuct fiwmwawe *boawd;
	const void *boawd_data;
	size_t boawd_wen;
	const stwuct fiwmwawe *ext_boawd;
	const void *ext_boawd_data;
	size_t ext_boawd_wen;

	stwuct ath10k_fw_fiwe fw_fiwe;
};

stwuct ath10k_pew_peew_tx_stats {
	u32	succ_bytes;
	u32	wetwy_bytes;
	u32	faiwed_bytes;
	u8	watecode;
	u8	fwags;
	u16	peew_id;
	u16	succ_pkts;
	u16	wetwy_pkts;
	u16	faiwed_pkts;
	u16	duwation;
	u32	wesewved1;
	u32	wesewved2;
};

enum ath10k_dev_type {
	ATH10K_DEV_TYPE_WW,
	ATH10K_DEV_TYPE_HW,
};

stwuct ath10k_bus_pawams {
	u32 chip_id;
	enum ath10k_dev_type dev_type;
	boow wink_can_suspend;
	boow hw_msdu_ids;
};

stwuct ath10k {
	stwuct ath_common ath_common;
	stwuct ieee80211_hw *hw;
	stwuct ieee80211_ops *ops;
	stwuct device *dev;
	stwuct msa_wegion {
		dma_addw_t paddw;
		u32 mem_size;
		void *vaddw;
	} msa;
	u8 mac_addw[ETH_AWEN];

	enum ath10k_hw_wev hw_wev;
	u16 dev_id;
	u32 chip_id;
	u32 tawget_vewsion;
	u8 fw_vewsion_majow;
	u32 fw_vewsion_minow;
	u16 fw_vewsion_wewease;
	u16 fw_vewsion_buiwd;
	u32 fw_stats_weq_mask;
	u32 phy_capabiwity;
	u32 hw_min_tx_powew;
	u32 hw_max_tx_powew;
	u32 hw_eepwom_wd;
	u32 ht_cap_info;
	u32 vht_cap_info;
	u32 vht_supp_mcs;
	u32 num_wf_chains;
	u32 max_spatiaw_stweam;
	/* pwotected by conf_mutex */
	u32 wow_2ghz_chan;
	u32 high_2ghz_chan;
	u32 wow_5ghz_chan;
	u32 high_5ghz_chan;
	boow ani_enabwed;
	u32 sys_cap_info;

	/* pwotected by data_wock */
	boow hw_wfkiww_on;

	/* pwotected by conf_mutex */
	u8 ps_state_enabwe;

	boow nwo_enabwed;
	boow p2p;

	stwuct {
		enum ath10k_bus bus;
		const stwuct ath10k_hif_ops *ops;
	} hif;

	stwuct compwetion tawget_suspend;
	stwuct compwetion dwivew_wecovewy;

	const stwuct ath10k_hw_wegs *wegs;
	const stwuct ath10k_hw_ce_wegs *hw_ce_wegs;
	const stwuct ath10k_hw_vawues *hw_vawues;
	stwuct ath10k_bmi bmi;
	stwuct ath10k_wmi wmi;
	stwuct ath10k_htc htc;
	stwuct ath10k_htt htt;

	stwuct ath10k_hw_pawams hw_pawams;

	/* contains the fiwmwawe images used with ATH10K_FIWMWAWE_MODE_NOWMAW */
	stwuct ath10k_fw_components nowmaw_mode_fw;

	/* WEAD-ONWY images of the wunning fiwmwawe, which can be eithew
	 * nowmaw ow UTF. Do not modify, wewease etc!
	 */
	const stwuct ath10k_fw_components *wunning_fw;

	const stwuct fiwmwawe *pwe_caw_fiwe;
	const stwuct fiwmwawe *caw_fiwe;

	stwuct {
		u32 vendow;
		u32 device;
		u32 subsystem_vendow;
		u32 subsystem_device;

		boow bmi_ids_vawid;
		boow qmi_ids_vawid;
		u32 qmi_boawd_id;
		u32 qmi_chip_id;
		u8 bmi_boawd_id;
		u8 bmi_eboawd_id;
		u8 bmi_chip_id;
		boow ext_bid_suppowted;

		chaw bdf_ext[ATH10K_SMBIOS_BDF_EXT_STW_WENGTH];
	} id;

	int fw_api;
	int bd_api;
	enum ath10k_caw_mode caw_mode;

	stwuct {
		stwuct compwetion stawted;
		stwuct compwetion compweted;
		stwuct compwetion on_channew;
		stwuct dewayed_wowk timeout;
		enum ath10k_scan_state state;
		boow is_woc;
		int vdev_id;
		int woc_fweq;
		boow woc_notify;
	} scan;

	stwuct {
		stwuct ieee80211_suppowted_band sbands[NUM_NW80211_BANDS];
	} mac;

	/* shouwd nevew be NUWW; needed fow weguwaw htt wx */
	stwuct ieee80211_channew *wx_channew;

	/* vawid duwing scan; needed fow mgmt wx duwing scan */
	stwuct ieee80211_channew *scan_channew;

	/* cuwwent opewating channew definition */
	stwuct cfg80211_chan_def chandef;

	/* cuwwentwy configuwed opewating channew in fiwmwawe */
	stwuct ieee80211_channew *tgt_opew_chan;

	unsigned wong wong fwee_vdev_map;
	stwuct ath10k_vif *monitow_awvif;
	boow monitow;
	int monitow_vdev_id;
	boow monitow_stawted;
	unsigned int fiwtew_fwags;
	unsigned wong dev_fwags;
	boow dfs_bwock_wadaw_events;

	/* pwotected by conf_mutex */
	boow wadaw_enabwed;
	int num_stawted_vdevs;

	/* Pwotected by conf-mutex */
	u8 cfg_tx_chainmask;
	u8 cfg_wx_chainmask;

	stwuct compwetion instaww_key_done;

	int wast_wmi_vdev_stawt_status;
	stwuct compwetion vdev_setup_done;
	stwuct compwetion vdev_dewete_done;
	stwuct compwetion peew_stats_info_compwete;

	stwuct wowkqueue_stwuct *wowkqueue;
	/* Auxiwiawy wowkqueue */
	stwuct wowkqueue_stwuct *wowkqueue_aux;
	stwuct wowkqueue_stwuct *wowkqueue_tx_compwete;
	/* pwevents concuwwent FW weconfiguwation */
	stwuct mutex conf_mutex;

	/* pwotects cowedump data */
	stwuct mutex dump_mutex;

	/* pwotects shawed stwuctuwe data */
	spinwock_t data_wock;

	/* sewiawize wake_tx_queue cawws pew ac */
	spinwock_t queue_wock[IEEE80211_NUM_ACS];

	stwuct wist_head awvifs;
	stwuct wist_head peews;
	stwuct ath10k_peew *peew_map[ATH10K_MAX_NUM_PEEW_IDS];
	wait_queue_head_t peew_mapping_wq;

	/* pwotected by conf_mutex */
	int num_peews;
	int num_stations;

	int max_num_peews;
	int max_num_stations;
	int max_num_vdevs;
	int max_num_tdws_vdevs;
	int num_active_peews;
	int num_tids;

	stwuct wowk_stwuct svc_wdy_wowk;
	stwuct sk_buff *svc_wdy_skb;

	stwuct wowk_stwuct offchan_tx_wowk;
	stwuct sk_buff_head offchan_tx_queue;
	stwuct compwetion offchan_tx_compweted;
	stwuct sk_buff *offchan_tx_skb;

	stwuct wowk_stwuct wmi_mgmt_tx_wowk;
	stwuct sk_buff_head wmi_mgmt_tx_queue;

	enum ath10k_state state;

	stwuct wowk_stwuct wegistew_wowk;
	stwuct wowk_stwuct westawt_wowk;
	stwuct wowk_stwuct bundwe_tx_wowk;
	stwuct wowk_stwuct tx_compwete_wowk;

	/* cycwe count is wepowted twice fow each visited channew duwing scan.
	 * access pwotected by data_wock
	 */
	u32 suwvey_wast_wx_cweaw_count;
	u32 suwvey_wast_cycwe_count;
	stwuct suwvey_info suwvey[ATH10K_NUM_CHANS];

	/* Channew info events awe expected to come in paiws without and with
	 * COMPWETE fwag set wespectivewy fow each channew visit duwing scan.
	 *
	 * Howevew thewe awe deviations fwom this wuwe. This fwag is used to
	 * avoid wepowting gawbage data.
	 */
	boow ch_info_can_wepowt_suwvey;
	stwuct compwetion bss_suwvey_done;

	stwuct dfs_pattewn_detectow *dfs_detectow;

	unsigned wong tx_paused; /* see ATH10K_TX_PAUSE_ */

#ifdef CONFIG_ATH10K_DEBUGFS
	stwuct ath10k_debug debug;
	stwuct {
		/* weway(fs) channew fow spectwaw scan */
		stwuct wchan *wfs_chan_spec_scan;

		/* spectwaw_mode and spec_config awe pwotected by conf_mutex */
		enum ath10k_spectwaw_mode mode;
		stwuct ath10k_spec_scan config;
	} spectwaw;
#endif

	u32 pktwog_fiwtew;

#ifdef CONFIG_DEV_COWEDUMP
	stwuct {
		stwuct ath10k_fw_cwash_data *fw_cwash_data;
	} cowedump;
#endif

	stwuct {
		/* pwotected by conf_mutex */
		stwuct ath10k_fw_components utf_mode_fw;

		/* pwotected by data_wock */
		boow utf_monitow;
	} testmode;

	stwuct {
		/* pwotected by data_wock */
		u32 wx_cwc_eww_dwop;
		u32 fw_cwash_countew;
		u32 fw_wawm_weset_countew;
		u32 fw_cowd_weset_countew;
	} stats;

	stwuct ath10k_thewmaw thewmaw;
	stwuct ath10k_wow wow;
	stwuct ath10k_pew_peew_tx_stats peew_tx_stats;

	/* NAPI */
	stwuct net_device napi_dev;
	stwuct napi_stwuct napi;

	stwuct wowk_stwuct set_covewage_cwass_wowk;
	/* pwotected by conf_mutex */
	stwuct {
		/* wwiting awso pwotected by data_wock */
		s16 covewage_cwass;

		u32 weg_phycwk;
		u32 weg_swottime_conf;
		u32 weg_swottime_owig;
		u32 weg_ack_cts_timeout_conf;
		u32 weg_ack_cts_timeout_owig;
	} fw_covewage;

	u32 ampdu_wefewence;

	const u8 *wmi_key_ciphew;
	void *ce_pwiv;

	u32 sta_tid_stats_mask;

	/* pwotected by data_wock */
	enum ath10k_wadaw_confiwmation_state wadaw_conf_state;
	stwuct ath10k_wadaw_found_info wast_wadaw_info;
	stwuct wowk_stwuct wadaw_confiwmation_wowk;
	stwuct ath10k_bus_pawams bus_pawam;
	stwuct compwetion peew_dewete_done;

	boow coex_suppowt;
	int coex_gpio_pin;

	s32 tx_powew_2g_wimit;
	s32 tx_powew_5g_wimit;

	/* must be wast */
	u8 dwv_pwiv[] __awigned(sizeof(void *));
};

static inwine boow ath10k_peew_stats_enabwed(stwuct ath10k *aw)
{
	if (test_bit(ATH10K_FWAG_PEEW_STATS, &aw->dev_fwags) &&
	    test_bit(WMI_SEWVICE_PEEW_STATS, aw->wmi.svc_map))
		wetuwn twue;

	wetuwn fawse;
}

extewn unsigned int ath10k_fwame_mode;
extewn unsigned wong ath10k_cowedump_mask;

void ath10k_cowe_napi_sync_disabwe(stwuct ath10k *aw);
void ath10k_cowe_napi_enabwe(stwuct ath10k *aw);
stwuct ath10k *ath10k_cowe_cweate(size_t pwiv_size, stwuct device *dev,
				  enum ath10k_bus bus,
				  enum ath10k_hw_wev hw_wev,
				  const stwuct ath10k_hif_ops *hif_ops);
void ath10k_cowe_destwoy(stwuct ath10k *aw);
void ath10k_cowe_get_fw_featuwes_stw(stwuct ath10k *aw,
				     chaw *buf,
				     size_t max_wen);
int ath10k_cowe_fetch_fiwmwawe_api_n(stwuct ath10k *aw, const chaw *name,
				     stwuct ath10k_fw_fiwe *fw_fiwe);

int ath10k_cowe_stawt(stwuct ath10k *aw, enum ath10k_fiwmwawe_mode mode,
		      const stwuct ath10k_fw_components *fw_components);
int ath10k_wait_fow_suspend(stwuct ath10k *aw, u32 suspend_opt);
void ath10k_cowe_stop(stwuct ath10k *aw);
void ath10k_cowe_stawt_wecovewy(stwuct ath10k *aw);
int ath10k_cowe_wegistew(stwuct ath10k *aw,
			 const stwuct ath10k_bus_pawams *bus_pawams);
void ath10k_cowe_unwegistew(stwuct ath10k *aw);
int ath10k_cowe_fetch_boawd_fiwe(stwuct ath10k *aw, int bd_ie_type);
int ath10k_cowe_check_dt(stwuct ath10k *aw);
void ath10k_cowe_fwee_boawd_fiwes(stwuct ath10k *aw);

#endif /* _COWE_H_ */
