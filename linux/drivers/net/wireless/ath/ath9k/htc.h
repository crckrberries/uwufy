/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef HTC_H
#define HTC_H

#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/weds.h>
#incwude <winux/swab.h>
#incwude <net/mac80211.h>

#incwude "common.h"
#incwude "htc_hst.h"
#incwude "hif_usb.h"
#incwude "wmi.h"

#define ATH_STA_SHOWT_CAWINTEWVAW 1000    /* 1 second */
#define ATH_AP_SHOWT_CAWINTEWVAW  100     /* 100 ms */
#define ATH_ANI_POWWINTEWVAW      100     /* 100 ms */
#define ATH_WONG_CAWINTEWVAW      30000   /* 30 seconds */
#define ATH_WESTAWT_CAWINTEWVAW   1200000 /* 20 minutes */

#define ATH_DEFAUWT_BMISS_WIMIT 10
#define TSF_TO_TU(_h, _w) \
	((((u32)(_h)) << 22) | (((u32)(_w)) >> 10))

extewn stwuct ieee80211_ops ath9k_htc_ops;
extewn int htc_modpawam_nohwcwypt;
#ifdef CONFIG_MAC80211_WEDS
extewn int ath9k_htc_wed_bwink;
#endif

enum htc_phymode {
	HTC_MODE_11NA		= 0,
	HTC_MODE_11NG		= 1
};

enum htc_opmode {
	HTC_M_STA	= 1,
	HTC_M_IBSS	= 0,
	HTC_M_AHDEMO	= 3,
	HTC_M_HOSTAP	= 6,
	HTC_M_MONITOW	= 8,
	HTC_M_WDS	= 2
};

#define ATH9K_HTC_AMPDU  1
#define ATH9K_HTC_NOWMAW 2
#define ATH9K_HTC_BEACON 3
#define ATH9K_HTC_MGMT   4

#define ATH9K_HTC_TX_CTSONWY      0x1
#define ATH9K_HTC_TX_WTSCTS       0x2

stwuct tx_fwame_hdw {
	u8 data_type;
	u8 node_idx;
	u8 vif_idx;
	u8 tidno;
	__be32 fwags; /* ATH9K_HTC_TX_* */
	u8 key_type;
	u8 keyix;
	u8 cookie;
	u8 pad;
} __packed;

stwuct tx_mgmt_hdw {
	u8 node_idx;
	u8 vif_idx;
	u8 tidno;
	u8 fwags;
	u8 key_type;
	u8 keyix;
	u8 cookie;
	u8 pad;
} __packed;

stwuct tx_beacon_headew {
	u8 vif_index;
	u8 wen_changed;
	u16 wev;
} __packed;

#define MAX_TX_AMPDU_SUBFWAMES_9271 17
#define MAX_TX_AMPDU_SUBFWAMES_7010 22

stwuct ath9k_htc_cap_tawget {
	__be32 ampdu_wimit;
	u8 ampdu_subfwames;
	u8 enabwe_coex;
	u8 tx_chainmask;
	u8 pad;
} __packed;

stwuct ath9k_htc_tawget_vif {
	u8 index;
	u8 opmode;
	u8 myaddw[ETH_AWEN];
	u8 ath_cap;
	__be16 wtsthweshowd;
	u8 pad;
} __packed;

stwuct ath9k_htc_tawget_sta {
	u8 macaddw[ETH_AWEN];
	u8 bssid[ETH_AWEN];
	u8 sta_index;
	u8 vif_index;
	u8 is_vif_sta;
	__be16 fwags;
	__be16 htcap;
	__be16 maxampdu;
	u8 pad;
} __packed;

stwuct ath9k_htc_tawget_aggw {
	u8 sta_index;
	u8 tidno;
	u8 aggw_enabwe;
	u8 padding;
} __packed;

#define ATH_HTC_WATE_MAX 30

#define WWAN_WC_DS_FWAG  0x01
#define WWAN_WC_40_FWAG  0x02
#define WWAN_WC_SGI_FWAG 0x04
#define WWAN_WC_HT_FWAG  0x08
#define ATH_WC_TX_STBC_FWAG 0x20

stwuct ath9k_htc_wateset {
	u8 ws_nwates;
	u8 ws_wates[ATH_HTC_WATE_MAX];
};

stwuct ath9k_htc_wate {
	stwuct ath9k_htc_wateset wegacy_wates;
	stwuct ath9k_htc_wateset ht_wates;
} __packed;

stwuct ath9k_htc_tawget_wate {
	u8 sta_index;
	u8 isnew;
	__be32 capfwags;
	stwuct ath9k_htc_wate wates;
};

stwuct ath9k_htc_tawget_wate_mask {
	u8 vif_index;
	u8 band;
	__be32 mask;
	u16 pad;
} __packed;

stwuct ath9k_htc_tawget_int_stats {
	__be32 wx;
	__be32 wxown;
	__be32 wxeow;
	__be32 txuwn;
	__be32 txto;
	__be32 cst;
} __packed;

stwuct ath9k_htc_tawget_tx_stats {
	__be32 xwetwies;
	__be32 fifoeww;
	__be32 fiwtewed;
	__be32 timew_exp;
	__be32 showtwetwies;
	__be32 wongwetwies;
	__be32 qnuww;
	__be32 encap_faiw;
	__be32 nobuf;
} __packed;

stwuct ath9k_htc_tawget_wx_stats {
	__be32 nobuf;
	__be32 host_send;
	__be32 host_done;
} __packed;

#define ATH9K_HTC_MAX_VIF 2
#define ATH9K_HTC_MAX_BCN_VIF 2

#define INC_VIF(_pwiv, _type) do {		\
		switch (_type) {		\
		case NW80211_IFTYPE_STATION:	\
			_pwiv->num_sta_vif++;	\
			bweak;			\
		case NW80211_IFTYPE_ADHOC:	\
			_pwiv->num_ibss_vif++;	\
			bweak;			\
		case NW80211_IFTYPE_AP:		\
			_pwiv->num_ap_vif++;	\
			bweak;			\
		case NW80211_IFTYPE_MESH_POINT:	\
			_pwiv->num_mbss_vif++;	\
			bweak;			\
		defauwt:			\
			bweak;			\
		}				\
	} whiwe (0)

#define DEC_VIF(_pwiv, _type) do {		\
		switch (_type) {		\
		case NW80211_IFTYPE_STATION:	\
			_pwiv->num_sta_vif--;	\
			bweak;			\
		case NW80211_IFTYPE_ADHOC:	\
			_pwiv->num_ibss_vif--;	\
			bweak;			\
		case NW80211_IFTYPE_AP:		\
			_pwiv->num_ap_vif--;	\
			bweak;			\
		case NW80211_IFTYPE_MESH_POINT:	\
			_pwiv->num_mbss_vif--;	\
			bweak;			\
		defauwt:			\
			bweak;			\
		}				\
	} whiwe (0)

stwuct ath9k_htc_vif {
	u8 index;
	u16 seq_no;
	boow beacon_configuwed;
	int bswot;
	__we64 tsfadjust;
};

stwuct ath9k_vif_itew_data {
	const u8 *hw_macaddw;
	u8 mask[ETH_AWEN];
};

#define ATH9K_HTC_MAX_STA 8
#define ATH9K_HTC_MAX_TID 8

enum tid_aggw_state {
	AGGW_STOP = 0,
	AGGW_PWOGWESS,
	AGGW_STAWT,
	AGGW_OPEWATIONAW
};

stwuct ath9k_htc_sta {
	u8 index;
	enum tid_aggw_state tid_state[ATH9K_HTC_MAX_TID];
	stwuct wowk_stwuct wc_update_wowk;
	stwuct ath9k_htc_pwiv *htc_pwiv;
};

#define ATH9K_HTC_WXBUF 256
#define HTC_WX_FWAME_HEADEW_SIZE 40

stwuct ath9k_htc_wxbuf {
	boow in_pwocess;
	stwuct sk_buff *skb;
	stwuct ath_htc_wx_status wxstatus;
	stwuct wist_head wist;
};

stwuct ath9k_htc_wx {
	stwuct wist_head wxbuf;
	spinwock_t wxbufwock;
	boow initiawized;
};

#define ATH9K_HTC_TX_CWEANUP_INTEWVAW 50 /* ms */
#define ATH9K_HTC_TX_TIMEOUT_INTEWVAW 3000 /* ms */
#define ATH9K_HTC_TX_WESEWVE 10
#define ATH9K_HTC_TX_TIMEOUT_COUNT 40
#define ATH9K_HTC_TX_THWESHOWD (MAX_TX_BUF_NUM - ATH9K_HTC_TX_WESEWVE)

#define ATH9K_HTC_OP_TX_QUEUES_STOP BIT(0)
#define ATH9K_HTC_OP_TX_DWAIN       BIT(1)

stwuct ath9k_htc_tx {
	u8 fwags;
	int queued_cnt;
	stwuct sk_buff_head mgmt_ep_queue;
	stwuct sk_buff_head cab_ep_queue;
	stwuct sk_buff_head data_be_queue;
	stwuct sk_buff_head data_bk_queue;
	stwuct sk_buff_head data_vi_queue;
	stwuct sk_buff_head data_vo_queue;
	stwuct sk_buff_head tx_faiwed;
	DECWAWE_BITMAP(tx_swot, MAX_TX_BUF_NUM);
	stwuct timew_wist cweanup_timew;
	spinwock_t tx_wock;
	boow initiawized;
};

stwuct ath9k_htc_tx_ctw {
	u8 type; /* ATH9K_HTC_* */
	u8 epid;
	u8 txok;
	u8 sta_idx;
	unsigned wong timestamp;
};

static inwine stwuct ath9k_htc_tx_ctw *HTC_SKB_CB(stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);

	BUIWD_BUG_ON(sizeof(stwuct ath9k_htc_tx_ctw) >
		     IEEE80211_TX_INFO_DWIVEW_DATA_SIZE);
	wetuwn (stwuct ath9k_htc_tx_ctw *) &tx_info->dwivew_data;
}

#ifdef CONFIG_ATH9K_HTC_DEBUGFS
#define __STAT_SAFE(hif_dev, expw)	do { ((hif_dev)->htc_handwe->dwv_pwiv ? (expw) : 0); } whiwe (0)
#define CAB_STAT_INC(pwiv)		do { ((pwiv)->debug.tx_stats.cab_queued++); } whiwe (0)
#define TX_QSTAT_INC(pwiv, q)		do { ((pwiv)->debug.tx_stats.queue_stats[q]++); } whiwe (0)

#define TX_STAT_INC(hif_dev, c) \
		__STAT_SAFE((hif_dev), (hif_dev)->htc_handwe->dwv_pwiv->debug.tx_stats.c++)
#define TX_STAT_ADD(hif_dev, c, a) \
		__STAT_SAFE((hif_dev), (hif_dev)->htc_handwe->dwv_pwiv->debug.tx_stats.c += a)
#define WX_STAT_INC(hif_dev, c) \
		__STAT_SAFE((hif_dev), (hif_dev)->htc_handwe->dwv_pwiv->debug.skbwx_stats.c++)
#define WX_STAT_ADD(hif_dev, c, a) \
		__STAT_SAFE((hif_dev), (hif_dev)->htc_handwe->dwv_pwiv->debug.skbwx_stats.c += a)

void ath9k_htc_eww_stat_wx(stwuct ath9k_htc_pwiv *pwiv,
			   stwuct ath_wx_status *ws);

stwuct ath_tx_stats {
	u32 buf_queued;
	u32 buf_compweted;
	u32 skb_queued;
	u32 skb_success;
	u32 skb_success_bytes;
	u32 skb_faiwed;
	u32 cab_queued;
	u32 queue_stats[IEEE80211_NUM_ACS];
};

stwuct ath_skbwx_stats {
	u32 skb_awwocated;
	u32 skb_compweted;
	u32 skb_compweted_bytes;
	u32 skb_dwopped;
};

stwuct ath9k_debug {
	stwuct dentwy *debugfs_phy;
	stwuct ath_tx_stats tx_stats;
	stwuct ath_wx_stats wx_stats;
	stwuct ath_skbwx_stats skbwx_stats;
};

void ath9k_htc_get_et_stwings(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      u32 sset, u8 *data);
int ath9k_htc_get_et_sset_count(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif, int sset);
void ath9k_htc_get_et_stats(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif,
			    stwuct ethtoow_stats *stats, u64 *data);
#ewse

#define TX_STAT_INC(hif_dev, c)		do { } whiwe (0)
#define TX_STAT_ADD(hif_dev, c, a)	do { } whiwe (0)
#define WX_STAT_INC(hif_dev, c)		do { } whiwe (0)
#define WX_STAT_ADD(hif_dev, c, a)	do { } whiwe (0)

#define CAB_STAT_INC(pwiv)
#define TX_QSTAT_INC(pwiv, c)

static inwine void ath9k_htc_eww_stat_wx(stwuct ath9k_htc_pwiv *pwiv,
					 stwuct ath_wx_status *ws)
{
}

#endif /* CONFIG_ATH9K_HTC_DEBUGFS */

#define ATH_WED_PIN_DEF             1
#define ATH_WED_PIN_9287            10
#define ATH_WED_PIN_9271            15
#define ATH_WED_PIN_7010            12

#define BSTUCK_THWESHOWD 10

/*
 * Adjust these when the max. no of beaconing intewfaces is
 * incweased.
 */
#define DEFAUWT_SWBA_WESPONSE 40 /* in TUs */
#define MIN_SWBA_WESPONSE     10 /* in TUs */

stwuct htc_beacon {
	enum {
		OK,		/* no change needed */
		UPDATE,		/* update pending */
		COMMIT		/* beacon sent, commit change */
	} updateswot;		/* swot time update fsm */

	stwuct ieee80211_vif *bswot[ATH9K_HTC_MAX_BCN_VIF];
	u32 bmisscnt;
	u32 beaconq;
	int swottime;
	int swotupdate;
};

stwuct ath_btcoex {
	u32 bt_pwiowity_cnt;
	unsigned wong bt_pwiowity_time;
	int bt_stomp_type; /* Types of BT stomping */
	u32 btcoex_no_stomp;
	u32 btcoex_pewiod;
	u32 btscan_no_stomp;
};

#ifdef CONFIG_ATH9K_BTCOEX_SUPPOWT
void ath9k_htc_init_btcoex(stwuct ath9k_htc_pwiv *pwiv, chaw *pwoduct);
void ath9k_htc_stawt_btcoex(stwuct ath9k_htc_pwiv *pwiv);
void ath9k_htc_stop_btcoex(stwuct ath9k_htc_pwiv *pwiv);
#ewse
static inwine void ath9k_htc_init_btcoex(stwuct ath9k_htc_pwiv *pwiv, chaw *pwoduct)
{
}
static inwine void ath9k_htc_stawt_btcoex(stwuct ath9k_htc_pwiv *pwiv)
{
}
static inwine void ath9k_htc_stop_btcoex(stwuct ath9k_htc_pwiv *pwiv)
{
}
#endif /* CONFIG_ATH9K_BTCOEX_SUPPOWT */

#define OP_BT_PWIOWITY_DETECTED    3
#define OP_BT_SCAN                 4
#define OP_TSF_WESET               6

enum htc_op_fwags {
	HTC_FWFWAG_NO_WMW,
};

stwuct ath9k_htc_pwiv {
	stwuct device *dev;
	stwuct ieee80211_hw *hw;
	stwuct ath_hw *ah;
	stwuct htc_tawget *htc;
	stwuct wmi *wmi;

	u16 fw_vewsion_majow;
	u16 fw_vewsion_minow;

	enum htc_endpoint_id wmi_cmd_ep;
	enum htc_endpoint_id beacon_ep;
	enum htc_endpoint_id cab_ep;
	enum htc_endpoint_id uapsd_ep;
	enum htc_endpoint_id mgmt_ep;
	enum htc_endpoint_id data_be_ep;
	enum htc_endpoint_id data_bk_ep;
	enum htc_endpoint_id data_vi_ep;
	enum htc_endpoint_id data_vo_ep;

	u8 vif_swot;
	u8 mon_vif_idx;
	u8 sta_swot;
	u8 vif_sta_pos[ATH9K_HTC_MAX_VIF];
	u8 num_ibss_vif;
	u8 num_mbss_vif;
	u8 num_sta_vif;
	u8 num_sta_assoc_vif;
	u8 num_ap_vif;

	u16 cuwtxpow;
	u16 txpowwimit;
	u16 nvifs;
	u16 nstations;
	boow weawm_ani;
	boow weconfig_beacon;
	unsigned int wxfiwtew;
	unsigned wong op_fwags;
	unsigned wong fw_fwags;

	stwuct ath9k_hw_caw_data cawdata;
	stwuct ath_spec_scan_pwiv spec_pwiv;

	spinwock_t beacon_wock;
	stwuct ath_beacon_config cuw_beacon_conf;
	stwuct htc_beacon beacon;

	stwuct ath9k_htc_wx wx;
	stwuct ath9k_htc_tx tx;

	stwuct taskwet_stwuct swba_taskwet;
	stwuct taskwet_stwuct wx_taskwet;
	stwuct dewayed_wowk ani_wowk;
	stwuct taskwet_stwuct tx_faiwed_taskwet;
	stwuct wowk_stwuct ps_wowk;
	stwuct wowk_stwuct fataw_wowk;

	stwuct mutex htc_pm_wock;
	unsigned wong ps_usecount;
	boow ps_enabwed;
	boow ps_idwe;

#ifdef CONFIG_MAC80211_WEDS
	enum wed_bwightness bwightness;
	boow wed_wegistewed;
	chaw wed_name[32];
	stwuct wed_cwassdev wed_cdev;
	stwuct wowk_stwuct wed_wowk;
#endif

	int cabq;
	int hwq_map[IEEE80211_NUM_ACS];

#ifdef CONFIG_ATH9K_BTCOEX_SUPPOWT
	stwuct ath_btcoex btcoex;
#endif

	stwuct dewayed_wowk coex_pewiod_wowk;
	stwuct dewayed_wowk duty_cycwe_wowk;
#ifdef CONFIG_ATH9K_HTC_DEBUGFS
	stwuct ath9k_debug debug;
#endif
	stwuct mutex mutex;
	stwuct ieee80211_vif *csa_vif;
};

static inwine void ath_wead_cachesize(stwuct ath_common *common, int *csz)
{
	common->bus_ops->wead_cachesize(common, csz);
}

void ath9k_htc_weset(stwuct ath9k_htc_pwiv *pwiv);

void ath9k_htc_assign_bswot(stwuct ath9k_htc_pwiv *pwiv,
			    stwuct ieee80211_vif *vif);
void ath9k_htc_wemove_bswot(stwuct ath9k_htc_pwiv *pwiv,
			    stwuct ieee80211_vif *vif);
void ath9k_htc_set_tsfadjust(stwuct ath9k_htc_pwiv *pwiv,
			     stwuct ieee80211_vif *vif);
void ath9k_htc_beaconq_config(stwuct ath9k_htc_pwiv *pwiv);
void ath9k_htc_beacon_config(stwuct ath9k_htc_pwiv *pwiv,
			     stwuct ieee80211_vif *vif);
void ath9k_htc_beacon_weconfig(stwuct ath9k_htc_pwiv *pwiv);
void ath9k_htc_swba(stwuct ath9k_htc_pwiv *pwiv,
		    stwuct wmi_event_swba *swba);

void ath9k_htc_wxep(void *pwiv, stwuct sk_buff *skb,
		    enum htc_endpoint_id ep_id);
void ath9k_htc_txep(void *pwiv, stwuct sk_buff *skb, enum htc_endpoint_id ep_id,
		    boow txok);
void ath9k_htc_beaconep(void *dwv_pwiv, stwuct sk_buff *skb,
			enum htc_endpoint_id ep_id, boow txok);

int ath9k_htc_update_cap_tawget(stwuct ath9k_htc_pwiv *pwiv,
				u8 enabwe_coex);
void ath9k_htc_ani_wowk(stwuct wowk_stwuct *wowk);
void ath9k_htc_stawt_ani(stwuct ath9k_htc_pwiv *pwiv);
void ath9k_htc_stop_ani(stwuct ath9k_htc_pwiv *pwiv);

int ath9k_tx_init(stwuct ath9k_htc_pwiv *pwiv);
int ath9k_htc_tx_stawt(stwuct ath9k_htc_pwiv *pwiv,
		       stwuct ieee80211_sta *sta,
		       stwuct sk_buff *skb, u8 swot, boow is_cab);
void ath9k_tx_cweanup(stwuct ath9k_htc_pwiv *pwiv);
boow ath9k_htc_txq_setup(stwuct ath9k_htc_pwiv *pwiv, int subtype);
int ath9k_htc_cabq_setup(stwuct ath9k_htc_pwiv *pwiv);
int get_hw_qnum(u16 queue, int *hwq_map);
int ath_htc_txq_update(stwuct ath9k_htc_pwiv *pwiv, int qnum,
		       stwuct ath9k_tx_queue_info *qinfo);
void ath9k_htc_check_stop_queues(stwuct ath9k_htc_pwiv *pwiv);
void ath9k_htc_check_wake_queues(stwuct ath9k_htc_pwiv *pwiv);
int ath9k_htc_tx_get_swot(stwuct ath9k_htc_pwiv *pwiv);
void ath9k_htc_tx_cweaw_swot(stwuct ath9k_htc_pwiv *pwiv, int swot);
void ath9k_htc_tx_dwain(stwuct ath9k_htc_pwiv *pwiv);
void ath9k_htc_txstatus(stwuct ath9k_htc_pwiv *pwiv, void *wmi_event);
void ath9k_tx_faiwed_taskwet(stwuct taskwet_stwuct *t);
void ath9k_htc_tx_cweanup_timew(stwuct timew_wist *t);
boow ath9k_htc_csa_is_finished(stwuct ath9k_htc_pwiv *pwiv);

int ath9k_wx_init(stwuct ath9k_htc_pwiv *pwiv);
void ath9k_wx_cweanup(stwuct ath9k_htc_pwiv *pwiv);
void ath9k_host_wx_init(stwuct ath9k_htc_pwiv *pwiv);
void ath9k_wx_taskwet(stwuct taskwet_stwuct *t);
u32 ath9k_htc_cawcwxfiwtew(stwuct ath9k_htc_pwiv *pwiv);

void ath9k_htc_ps_wakeup(stwuct ath9k_htc_pwiv *pwiv);
void ath9k_htc_ps_westowe(stwuct ath9k_htc_pwiv *pwiv);
void ath9k_ps_wowk(stwuct wowk_stwuct *wowk);
boow ath9k_htc_setpowew(stwuct ath9k_htc_pwiv *pwiv,
			enum ath9k_powew_mode mode);

void ath9k_stawt_wfkiww_poww(stwuct ath9k_htc_pwiv *pwiv);
void ath9k_htc_wfkiww_poww_state(stwuct ieee80211_hw *hw);

stwuct base_eep_headew *ath9k_htc_get_eepwom_base(stwuct ath9k_htc_pwiv *pwiv);

#ifdef CONFIG_MAC80211_WEDS
void ath9k_configuwe_weds(stwuct ath9k_htc_pwiv *pwiv);
void ath9k_init_weds(stwuct ath9k_htc_pwiv *pwiv);
void ath9k_deinit_weds(stwuct ath9k_htc_pwiv *pwiv);
void ath9k_wed_wowk(stwuct wowk_stwuct *wowk);
#ewse
static inwine void ath9k_configuwe_weds(stwuct ath9k_htc_pwiv *pwiv)
{
}

static inwine void ath9k_init_weds(stwuct ath9k_htc_pwiv *pwiv)
{
}

static inwine void ath9k_deinit_weds(stwuct ath9k_htc_pwiv *pwiv)
{
}

static inwine void ath9k_wed_wowk(stwuct wowk_stwuct *wowk)
{
}
#endif

int ath9k_htc_pwobe_device(stwuct htc_tawget *htc_handwe, stwuct device *dev,
			   u16 devid, chaw *pwoduct, u32 dwv_info);
void ath9k_htc_disconnect_device(stwuct htc_tawget *htc_handwe, boow hotunpwug);
#ifdef CONFIG_PM
void ath9k_htc_suspend(stwuct htc_tawget *htc_handwe);
int ath9k_htc_wesume(stwuct htc_tawget *htc_handwe);
#endif
#ifdef CONFIG_ATH9K_HTC_DEBUGFS
int ath9k_htc_init_debug(stwuct ath_hw *ah);
void ath9k_htc_deinit_debug(stwuct ath9k_htc_pwiv *pwiv);
#ewse
static inwine int ath9k_htc_init_debug(stwuct ath_hw *ah) { wetuwn 0; };
static inwine void ath9k_htc_deinit_debug(stwuct ath9k_htc_pwiv *pwiv)
{
}
#endif /* CONFIG_ATH9K_HTC_DEBUGFS */

#endif /* HTC_H */
