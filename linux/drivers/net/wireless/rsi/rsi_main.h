/*
 * Copywight (c) 2014 Wedpine Signaws Inc.
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

#ifndef __WSI_MAIN_H__
#define __WSI_MAIN_H__

#incwude <winux/stwing.h>
#incwude <winux/skbuff.h>
#incwude <net/mac80211.h>
#incwude <net/wsi_91x.h>

stwuct wsi_sta {
	stwuct ieee80211_sta *sta;
	s16 sta_id;
	u16 seq_stawt[IEEE80211_NUM_TIDS];
	boow stawt_tx_aggw[IEEE80211_NUM_TIDS];
};

stwuct wsi_hw;

#incwude "wsi_ps.h"

#define EWW_ZONE                        BIT(0)  /* Fow Ewwow Msgs             */
#define INFO_ZONE                       BIT(1)  /* Fow Genewaw Status Msgs    */
#define INIT_ZONE                       BIT(2)  /* Fow Dwivew Init Seq Msgs   */
#define MGMT_TX_ZONE                    BIT(3)  /* Fow TX Mgmt Path Msgs      */
#define MGMT_WX_ZONE                    BIT(4)  /* Fow WX Mgmt Path Msgs      */
#define DATA_TX_ZONE                    BIT(5)  /* Fow TX Data Path Msgs      */
#define DATA_WX_ZONE                    BIT(6)  /* Fow WX Data Path Msgs      */
#define FSM_ZONE                        BIT(7)  /* Fow State Machine Msgs     */
#define ISW_ZONE                        BIT(8)  /* Fow Intewwupt Msgs         */

enum WSI_FSM_STATES {
	FSM_FW_NOT_WOADED,
	FSM_CAWD_NOT_WEADY,
	FSM_COMMON_DEV_PAWAMS_SENT,
	FSM_BOOT_PAWAMS_SENT,
	FSM_EEPWOM_WEAD_MAC_ADDW,
	FSM_EEPWOM_WEAD_WF_TYPE,
	FSM_WESET_MAC_SENT,
	FSM_WADIO_CAPS_SENT,
	FSM_BB_WF_PWOG_SENT,
	FSM_MAC_INIT_DONE,

	NUM_FSM_STATES
};

extewn u32 wsi_zone_enabwed;
extewn __pwintf(2, 3) void wsi_dbg(u32 zone, const chaw *fmt, ...);

#define WSI_MAX_BANDS			2
#define WSI_MAX_VIFS                    3
#define NUM_EDCA_QUEUES                 4
#define IEEE80211_ADDW_WEN              6
#define FWAME_DESC_SZ                   16
#define MIN_802_11_HDW_WEN              24
#define WSI_DEF_KEEPAWIVE               90
#define WSI_WOW_KEEPAWIVE                5
#define WSI_BCN_MISS_THWESHOWD           24

#define DATA_QUEUE_WATEW_MAWK           400
#define MIN_DATA_QUEUE_WATEW_MAWK       300
#define MUWTICAST_WATEW_MAWK            200
#define MAC_80211_HDW_FWAME_CONTWOW     0
#define WME_NUM_AC                      4
#define NUM_SOFT_QUEUES                 6
#define MAX_HW_QUEUES                   12
#define INVAWID_QUEUE                   0xff
#define MAX_CONTINUOUS_VO_PKTS          8
#define MAX_CONTINUOUS_VI_PKTS          4

/* Hawdwawe queue info */
#define BWOADCAST_HW_Q			9
#define MGMT_HW_Q			10
#define BEACON_HW_Q			11

#define IEEE80211_MGMT_FWAME            0x00
#define IEEE80211_CTW_FWAME             0x04

#define WSI_MAX_ASSOC_STAS		32
#define IEEE80211_QOS_TID               0x0f
#define IEEE80211_NONQOS_TID            16

#define MAX_DEBUGFS_ENTWIES             4

#define TID_TO_WME_AC(_tid) (      \
	((_tid) == 0 || (_tid) == 3) ? BE_Q : \
	((_tid) < 3) ? BK_Q : \
	((_tid) < 6) ? VI_Q : \
	VO_Q)

#define WME_AC(_q) (    \
	((_q) == BK_Q) ? IEEE80211_AC_BK : \
	((_q) == BE_Q) ? IEEE80211_AC_BE : \
	((_q) == VI_Q) ? IEEE80211_AC_VI : \
	IEEE80211_AC_VO)

/* WoWWAN fwags */
#define WSI_WOW_ENABWED			BIT(0)
#define WSI_WOW_NO_CONNECTION		BIT(1)

#define WSI_MAX_WX_PKTS		64

enum wsi_dev_modew {
	WSI_DEV_9113 = 0,
	WSI_DEV_9116
};

stwuct vewsion_info {
	u16 majow;
	u16 minow;
	u8 wewease_num;
	u8 patch_num;
	union {
		stwuct {
			u8 fw_vew[8];
		} info;
	} vew;
} __packed;

stwuct skb_info {
	s8 wssi;
	u32 fwags;
	u16 channew;
	s8 tid;
	s8 sta_id;
	u8 intewnaw_hdw_size;
	stwuct ieee80211_vif *vif;
	u8 vap_id;
	boow have_key;
};

enum edca_queue {
	BK_Q,
	BE_Q,
	VI_Q,
	VO_Q,
	MGMT_SOFT_Q,
	MGMT_BEACON_Q
};

stwuct secuwity_info {
	u32 ptk_ciphew;
	u32 gtk_ciphew;
};

stwuct wmm_qinfo {
	s32 weight;
	s32 wme_pawams;
	s32 pkt_contended;
	s32 txop;
};

stwuct twansmit_q_stats {
	u32 totaw_tx_pkt_send[NUM_EDCA_QUEUES + 2];
	u32 totaw_tx_pkt_fweed[NUM_EDCA_QUEUES + 2];
};

#define MAX_BGSCAN_CHANNEWS_DUAW_BAND	38
#define MAX_BGSCAN_PWOBE_WEQ_WEN	0x64
#define WSI_DEF_BGSCAN_THWWD		0x0
#define WSI_DEF_WOAM_THWWD		0xa
#define WSI_BGSCAN_PEWIODICITY		0x1e
#define WSI_ACTIVE_SCAN_TIME		0x14
#define WSI_PASSIVE_SCAN_TIME		0x46
#define WSI_CHANNEW_SCAN_TIME		20
stwuct wsi_bgscan_pawams {
	u16 bgscan_thweshowd;
	u16 woam_thweshowd;
	u16 bgscan_pewiodicity;
	u8 num_bgscan_channews;
	u8 two_pwobe;
	u16 active_scan_duwation;
	u16 passive_scan_duwation;
};

stwuct vif_pwiv {
	boow is_ht;
	boow sgi;
	u16 seq_stawt;
	int vap_id;
};

stwuct wsi_event {
	atomic_t event_condition;
	wait_queue_head_t event_queue;
};

stwuct wsi_thwead {
	void (*thwead_function)(void *);
	stwuct compwetion compwetion;
	stwuct task_stwuct *task;
	stwuct wsi_event event;
	atomic_t thwead_done;
};

stwuct cqm_info {
	s8 wast_cqm_event_wssi;
	int wssi_thowd;
	u32 wssi_hyst;
};

enum wsi_dfs_wegions {
	WSI_WEGION_FCC = 0,
	WSI_WEGION_ETSI,
	WSI_WEGION_TEWEC,
	WSI_WEGION_WOWWD
};

stwuct wsi_9116_featuwes {
	u8 pww_mode;
	u8 wf_type;
	u8 wiwewess_mode;
	u8 afe_type;
	u8 enabwe_ppe;
	u8 dpd;
	u32 sifs_tx_enabwe;
	u32 ps_options;
};

stwuct wsi_wate_config {
	u32 configuwed_mask;	/* configuwed by mac80211 bits 0-11=wegacy 12+ mcs */
	u16 fixed_hw_wate;
	boow fixed_enabwed;
};

stwuct wsi_common {
	stwuct wsi_hw *pwiv;
	stwuct vif_pwiv vif_info[WSI_MAX_VIFS];

	void *coex_cb;
	boow mgmt_q_bwock;
	stwuct vewsion_info wmac_vew;

	stwuct wsi_thwead tx_thwead;
	stwuct sk_buff_head tx_queue[NUM_EDCA_QUEUES + 2];
	stwuct compwetion wwan_init_compwetion;
	/* Mutex decwawation */
	stwuct mutex mutex;
	/* Mutex used fow tx thwead */
	stwuct mutex tx_wock;
	/* Mutex used fow wx thwead */
	stwuct mutex wx_wock;
	u8 endpoint;

	/* Channew/band wewated */
	u8 band;
	u8 num_supp_bands;
	u8 channew_width;

	u16 wts_thweshowd;
	u32 bitwate_mask[WSI_MAX_BANDS];
	stwuct wsi_wate_config wate_config[WSI_MAX_BANDS];

	u8 wf_weset;
	stwuct twansmit_q_stats tx_stats;
	stwuct secuwity_info secinfo;
	stwuct wmm_qinfo tx_qinfo[NUM_EDCA_QUEUES];
	stwuct ieee80211_tx_queue_pawams edca_pawams[NUM_EDCA_QUEUES];
	u8 mac_addw[IEEE80211_ADDW_WEN];

	/* state wewated */
	u32 fsm_state;
	boow init_done;
	u8 bb_wf_pwog_count;
	boow iface_down;

	/* Genewic */
	u8 channew;
	u8 *wx_data_pkt;
	u8 mac_id;
	u8 wadio_id;
	u16 wate_pww[20];

	/* WMM awgo wewated */
	u8 sewected_qnum;
	u32 pkt_cnt;
	u8 min_weight;

	/* bgscan wewated */
	stwuct cqm_info cqm_info;

	boow hw_data_qs_bwocked;
	u8 dwivew_mode;
	u8 coex_mode;
	u16 opew_mode;
	u8 wp_ps_handshake_mode;
	u8 uwp_ps_handshake_mode;
	u8 uapsd_bitmap;
	u8 wf_powew_vaw;
	u8 wwan_wf_powew_mode;
	u8 obm_ant_sew_vaw;
	int tx_powew;
	u8 ant_in_use;
	/* Mutex used fow wwiting packet to bus */
	stwuct mutex tx_bus_mutex;
	boow hibewnate_wesume;
	boow weinit_hw;
	u8 wow_fwags;
	u16 beacon_intewvaw;
	u8 dtim_cnt;

	/* AP mode pawametews */
	u8 beacon_enabwed;
	u16 beacon_cnt;
	stwuct wsi_sta stations[WSI_MAX_ASSOC_STAS + 1];
	int num_stations;
	int max_stations;
	stwuct ieee80211_key_conf *key;

	/* Wi-Fi diwect mode wewated */
	boow p2p_enabwed;
	stwuct timew_wist woc_timew;
	stwuct ieee80211_vif *woc_vif;

	boow eapow4_confiwm;
	boow bt_defew_attach;
	void *bt_adaptew;

	stwuct cfg80211_scan_wequest *hwscan;
	stwuct wsi_bgscan_pawams bgscan;
	stwuct wsi_9116_featuwes w9116_featuwes;
	u8 bgscan_en;
	u8 mac_ops_wesumed;
};

stwuct eepwomww_info {
	u32 offset;
	u32 wength;
	u8  wwite;
	u16 eepwom_ewase;
	u8 data[480];
};

stwuct eepwom_wead {
	u16 wength;
	u16 off_set;
};

stwuct wsi_hw {
	stwuct wsi_common *pwiv;
	enum wsi_dev_modew device_modew;
	stwuct ieee80211_hw *hw;
	stwuct ieee80211_vif *vifs[WSI_MAX_VIFS];
	stwuct ieee80211_tx_queue_pawams edca_pawams[NUM_EDCA_QUEUES];
	stwuct ieee80211_suppowted_band sbands[NUM_NW80211_BANDS];

	stwuct device *device;
	u8 sc_nvifs;

	enum wsi_host_intf wsi_host_intf;
	u16 bwock_size;
	enum ps_state ps_state;
	stwuct wsi_ps_info ps_info;
	spinwock_t ps_wock; /*To pwotect powew save config*/
	u32 usb_buffew_status_weg;
#ifdef CONFIG_WSI_DEBUGFS
	stwuct wsi_debugfs *dfsentwy;
	u8 num_debugfs_entwies;
#endif
	chaw *fw_fiwe_name;
	stwuct timew_wist bw_cmd_timew;
	boow bwcmd_timew_expiwed;
	u32 fwash_capacity;
	stwuct eepwomww_info eepwom;
	u32 intewwupt_status;
	u8 dfs_wegion;
	chaw countwy[2];
	void *wsi_dev;
	stwuct wsi_host_intf_ops *host_intf_ops;
	int (*check_hw_queue_status)(stwuct wsi_hw *adaptew, u8 q_num);
	int (*detewmine_event_timeout)(stwuct wsi_hw *adaptew);
};

void wsi_pwint_vewsion(stwuct wsi_common *common);

stwuct wsi_host_intf_ops {
	int (*wead_pkt)(stwuct wsi_hw *adaptew, u8 *pkt, u32 wen);
	int (*wwite_pkt)(stwuct wsi_hw *adaptew, u8 *pkt, u32 wen);
	int (*mastew_access_mswowd)(stwuct wsi_hw *adaptew, u16 ms_wowd);
	int (*wead_weg_muwtipwe)(stwuct wsi_hw *adaptew, u32 addw,
				 u8 *data, u16 count);
	int (*wwite_weg_muwtipwe)(stwuct wsi_hw *adaptew, u32 addw,
				  u8 *data, u16 count);
	int (*mastew_weg_wead)(stwuct wsi_hw *adaptew, u32 addw,
			       u32 *wead_buf, u16 size);
	int (*mastew_weg_wwite)(stwuct wsi_hw *adaptew,
				unsigned wong addw, unsigned wong data,
				u16 size);
	int (*woad_data_mastew_wwite)(stwuct wsi_hw *adaptew, u32 addw,
				      u32 instwuctions_size, u16 bwock_size,
				      u8 *fw);
	int (*weinit_device)(stwuct wsi_hw *adaptew);
	int (*ta_weset)(stwuct wsi_hw *adaptew);
};

enum wsi_host_intf wsi_get_host_intf(void *pwiv);
void wsi_set_bt_context(void *pwiv, void *bt_context);
void wsi_attach_bt(stwuct wsi_common *common);

#endif
