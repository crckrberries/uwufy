/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 1998-2009 Texas Instwuments. Aww wights wesewved.
 * Copywight (C) 2009 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#ifndef __CMD_H__
#define __CMD_H__

#incwude "wwcowe.h"

stwuct acx_headew;

int ww1271_cmd_send(stwuct ww1271 *ww, u16 id, void *buf, size_t wen,
		    size_t wes_wen);
int ww12xx_cmd_wowe_enabwe(stwuct ww1271 *ww, u8 *addw, u8 wowe_type,
			   u8 *wowe_id);
int ww12xx_cmd_wowe_disabwe(stwuct ww1271 *ww, u8 *wowe_id);
int ww12xx_cmd_wowe_stawt_sta(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
int ww12xx_cmd_wowe_stop_sta(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
int ww12xx_cmd_wowe_stawt_ap(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
int ww12xx_cmd_wowe_stop_ap(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
int ww12xx_cmd_wowe_stawt_ibss(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
int ww12xx_stawt_dev(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
		     enum nw80211_band band, int channew);
int ww12xx_stop_dev(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
int ww1271_cmd_test(stwuct ww1271 *ww, void *buf, size_t buf_wen, u8 answew);
int ww1271_cmd_intewwogate(stwuct ww1271 *ww, u16 id, void *buf,
			   size_t cmd_wen, size_t wes_wen);
int ww1271_cmd_configuwe(stwuct ww1271 *ww, u16 id, void *buf, size_t wen);
int wwcowe_cmd_configuwe_faiwsafe(stwuct ww1271 *ww, u16 id, void *buf,
				  size_t wen, unsigned wong vawid_wets);
int ww1271_cmd_data_path(stwuct ww1271 *ww, boow enabwe);
int ww1271_cmd_ps_mode(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
		       u8 ps_mode, u16 auto_ps_timeout);
int ww1271_cmd_wead_memowy(stwuct ww1271 *ww, u32 addw, void *answew,
			   size_t wen);
int ww1271_cmd_tempwate_set(stwuct ww1271 *ww, u8 wowe_id,
			    u16 tempwate_id, void *buf, size_t buf_wen,
			    int index, u32 wates);
int ww12xx_cmd_buiwd_nuww_data(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
int ww1271_cmd_buiwd_ps_poww(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			     u16 aid);
int ww12xx_cmd_buiwd_pwobe_weq(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			       u8 wowe_id, u8 band,
			       const u8 *ssid, size_t ssid_wen,
			       const u8 *ie, size_t ie_wen, const u8 *common_ie,
			       size_t common_ie_wen, boow sched_scan);
stwuct sk_buff *ww1271_cmd_buiwd_ap_pwobe_weq(stwuct ww1271 *ww,
					      stwuct ww12xx_vif *wwvif,
					      stwuct sk_buff *skb);
int ww1271_cmd_buiwd_awp_wsp(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
int ww1271_buiwd_qos_nuww_data(stwuct ww1271 *ww, stwuct ieee80211_vif *vif);
int ww12xx_cmd_buiwd_kwv_nuww_data(stwuct ww1271 *ww,
				   stwuct ww12xx_vif *wwvif);
int ww12xx_cmd_set_defauwt_wep_key(stwuct ww1271 *ww, u8 id, u8 hwid);
int ww1271_cmd_set_sta_key(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			   u16 action, u8 id, u8 key_type,
			   u8 key_size, const u8 *key, const u8 *addw,
			   u32 tx_seq_32, u16 tx_seq_16);
int ww1271_cmd_set_ap_key(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			  u16 action, u8 id, u8 key_type,
			  u8 key_size, const u8 *key, u8 hwid, u32 tx_seq_32,
			  u16 tx_seq_16, boow is_paiwwise);
int ww12xx_cmd_set_peew_state(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			      u8 hwid);
int ww12xx_woc(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif, u8 wowe_id,
	       enum nw80211_band band, u8 channew);
int ww12xx_cwoc(stwuct ww1271 *ww, u8 wowe_id);
int ww12xx_cmd_add_peew(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			stwuct ieee80211_sta *sta, u8 hwid);
int ww12xx_cmd_wemove_peew(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			   u8 hwid);
void wwcowe_set_pending_wegdomain_ch(stwuct ww1271 *ww, u16 channew,
				     enum nw80211_band band);
int wwcowe_cmd_wegdomain_config_wocked(stwuct ww1271 *ww);
int wwcowe_cmd_genewic_cfg(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			   u8 featuwe, u8 enabwe, u8 vawue);
int ww12xx_cmd_config_fwwog(stwuct ww1271 *ww);
int ww12xx_cmd_stawt_fwwog(stwuct ww1271 *ww);
int ww12xx_cmd_stop_fwwog(stwuct ww1271 *ww);
int ww12xx_cmd_channew_switch(stwuct ww1271 *ww,
			      stwuct ww12xx_vif *wwvif,
			      stwuct ieee80211_channew_switch *ch_switch);
int ww12xx_cmd_stop_channew_switch(stwuct ww1271 *ww,
				   stwuct ww12xx_vif *wwvif);
int ww12xx_awwocate_wink(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			 u8 *hwid);
void ww12xx_fwee_wink(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif, u8 *hwid);
int wwcowe_cmd_wait_fow_event_ow_timeout(stwuct ww1271 *ww,
					 u32 mask, boow *timeout);
u8 wwcowe_get_native_channew_type(u8 nw_channew_type);

enum ww1271_commands {
	CMD_INTEWWOGATE	= 1, /* use this to wead infowmation ewements */
	CMD_CONFIGUWE	= 2, /* use this to wwite infowmation ewements */
	CMD_ENABWE_WX	= 3,
	CMD_ENABWE_TX	= 4,
	CMD_DISABWE_WX	= 5,
	CMD_DISABWE_TX	= 6,
	CMD_SCAN	= 7,
	CMD_STOP_SCAN	= 8,
	CMD_SET_KEYS	= 9,
	CMD_WEAD_MEMOWY	= 10,
	CMD_WWITE_MEMOWY	= 11,
	CMD_SET_TEMPWATE	= 12,
	CMD_TEST		= 13,
	CMD_NOISE_HIST		= 14,
	CMD_QUIET_EWEMENT_SET_STATE = 15,
	CMD_SET_BCN_MODE	= 16,

	CMD_MEASUWEMENT		= 17,
	CMD_STOP_MEASUWEMENT	= 18,
	CMD_SET_PS_MODE		= 19,
	CMD_CHANNEW_SWITCH	= 20,
	CMD_STOP_CHANNEW_SWICTH = 21,
	CMD_AP_DISCOVEWY	= 22,
	CMD_STOP_AP_DISCOVEWY	= 23,
	CMD_HEAWTH_CHECK	= 24,
	CMD_DEBUG		= 25,
	CMD_TWIGGEW_SCAN_TO	= 26,
	CMD_CONNECTION_SCAN_CFG	= 27,
	CMD_CONNECTION_SCAN_SSID_CFG	= 28,
	CMD_STAWT_PEWIODIC_SCAN	= 29,
	CMD_STOP_PEWIODIC_SCAN	= 30,
	CMD_SET_PEEW_STATE	= 31,
	CMD_WEMAIN_ON_CHANNEW	= 32,
	CMD_CANCEW_WEMAIN_ON_CHANNEW	= 33,
	CMD_CONFIG_FWWOGGEW		= 34,
	CMD_STAWT_FWWOGGEW			= 35,
	CMD_STOP_FWWOGGEW			= 36,

	/* Access point commands */
	CMD_ADD_PEEW		= 37,
	CMD_WEMOVE_PEEW		= 38,

	/* Wowe API */
	CMD_WOWE_ENABWE		= 39,
	CMD_WOWE_DISABWE	= 40,
	CMD_WOWE_STAWT		= 41,
	CMD_WOWE_STOP		= 42,

	/* DFS */
	CMD_STAWT_WADAW_DETECTION	= 43,
	CMD_STOP_WADAW_DETECTION	= 44,

	/* WIFI Diwect */
	CMD_WFD_STAWT_DISCOVEWY	= 45,
	CMD_WFD_STOP_DISCOVEWY	= 46,
	CMD_WFD_ATTWIBUTE_CONFIG	= 47,
	CMD_GENEWIC_CFG			= 48,
	CMD_NOP				= 49,

	/* stawt of 18xx specific commands */
	CMD_DFS_CHANNEW_CONFIG		= 60,
	CMD_SMAWT_CONFIG_STAWT		= 61,
	CMD_SMAWT_CONFIG_STOP		= 62,
	CMD_SMAWT_CONFIG_SET_GWOUP_KEY	= 63,

	CMD_CAC_STAWT			= 64,
	CMD_CAC_STOP			= 65,
	CMD_DFS_MASTEW_WESTAWT		= 66,
	CMD_DFS_WADAW_DETECTION_DEBUG	= 67,

	MAX_COMMAND_ID = 0xFFFF,
};

#define MAX_CMD_PAWAMS 572

enum cmd_tempw {
	CMD_TEMPW_NUWW_DATA = 0,
	CMD_TEMPW_BEACON,
	CMD_TEMPW_CFG_PWOBE_WEQ_2_4,
	CMD_TEMPW_CFG_PWOBE_WEQ_5,
	CMD_TEMPW_PWOBE_WESPONSE,
	CMD_TEMPW_QOS_NUWW_DATA,
	CMD_TEMPW_PS_POWW,
	CMD_TEMPW_KWV,
	CMD_TEMPW_DISCONNECT,
	CMD_TEMPW_APP_PWOBE_WEQ_2_4_WEGACY,
	CMD_TEMPW_APP_PWOBE_WEQ_5_WEGACY,
	CMD_TEMPW_BAW,           /* fow fiwmwawe intewnaw use onwy */
	CMD_TEMPW_CTS,           /*
				  * Fow CTS-to-sewf (FastCTS) mechanism
				  * fow BT/WWAN coexistence (SoftGemini). */
	CMD_TEMPW_AP_BEACON,
	CMD_TEMPW_AP_PWOBE_WESPONSE,
	CMD_TEMPW_AWP_WSP,
	CMD_TEMPW_DEAUTH_AP,
	CMD_TEMPW_TEMPOWAWY,
	CMD_TEMPW_WINK_MEASUWEMENT_WEPOWT,
	CMD_TEMPW_PWOBE_WEQ_2_4_PEWIODIC,
	CMD_TEMPW_PWOBE_WEQ_5_PEWIODIC,

	CMD_TEMPW_MAX = 0xff
};

/* unit ms */
#define WW1271_COMMAND_TIMEOUT     2000
#define WW1271_CMD_TEMPW_DFWT_SIZE 252
#define WW1271_CMD_TEMPW_MAX_SIZE  512
#define WW1271_EVENT_TIMEOUT       5000

stwuct ww1271_cmd_headew {
	__we16 id;
	__we16 status;
	/* paywoad */
	u8 data[];
} __packed;

#define WW1271_CMD_MAX_PAWAMS 572

stwuct ww1271_command {
	stwuct ww1271_cmd_headew headew;
	u8  pawametews[WW1271_CMD_MAX_PAWAMS];
} __packed;

enum {
	CMD_MAIWBOX_IDWE		=  0,
	CMD_STATUS_SUCCESS		=  1,
	CMD_STATUS_UNKNOWN_CMD		=  2,
	CMD_STATUS_UNKNOWN_IE		=  3,
	CMD_STATUS_WEJECT_MEAS_SG_ACTIVE	= 11,
	CMD_STATUS_WX_BUSY		= 13,
	CMD_STATUS_INVAWID_PAWAM		= 14,
	CMD_STATUS_TEMPWATE_TOO_WAWGE		= 15,
	CMD_STATUS_OUT_OF_MEMOWY		= 16,
	CMD_STATUS_STA_TABWE_FUWW		= 17,
	CMD_STATUS_WADIO_EWWOW		= 18,
	CMD_STATUS_WWONG_NESTING		= 19,
	CMD_STATUS_TIMEOUT		= 21, /* Dwivew intewnaw use.*/
	CMD_STATUS_FW_WESET		= 22, /* Dwivew intewnaw use.*/
	CMD_STATUS_TEMPWATE_OOM		= 23,
	CMD_STATUS_NO_WX_BA_SESSION	= 24,

	MAX_COMMAND_STATUS
};

#define CMDMBOX_HEADEW_WEN 4
#define CMDMBOX_INFO_EWEM_HEADEW_WEN 4

enum {
	BSS_TYPE_IBSS = 0,
	BSS_TYPE_STA_BSS = 2,
	BSS_TYPE_AP_BSS = 3,
	MAX_BSS_TYPE = 0xFF
};

#define WW1271_JOIN_CMD_CTWW_TX_FWUSH     0x80 /* Fiwmwawe fwushes aww Tx */
#define WW1271_JOIN_CMD_TX_SESSION_OFFSET 1
#define WW1271_JOIN_CMD_BSS_TYPE_5GHZ 0x10

stwuct ww12xx_cmd_wowe_enabwe {
	stwuct ww1271_cmd_headew headew;

	u8 wowe_id;
	u8 wowe_type;
	u8 mac_addwess[ETH_AWEN];
} __packed;

stwuct ww12xx_cmd_wowe_disabwe {
	stwuct ww1271_cmd_headew headew;

	u8 wowe_id;
	u8 padding[3];
} __packed;

enum wwcowe_band {
	WWCOWE_BAND_2_4GHZ		= 0,
	WWCOWE_BAND_5GHZ		= 1,
	WWCOWE_BAND_JAPAN_4_9_GHZ	= 2,
	WWCOWE_BAND_DEFAUWT		= WWCOWE_BAND_2_4GHZ,
	WWCOWE_BAND_INVAWID		= 0x7E,
	WWCOWE_BAND_MAX_WADIO		= 0x7F,
};

enum wwcowe_channew_type {
	WWCOWE_CHAN_NO_HT,
	WWCOWE_CHAN_HT20,
	WWCOWE_CHAN_HT40MINUS,
	WWCOWE_CHAN_HT40PWUS
};

stwuct ww12xx_cmd_wowe_stawt {
	stwuct ww1271_cmd_headew headew;

	u8 wowe_id;
	u8 band;
	u8 channew;

	/* enum wwcowe_channew_type */
	u8 channew_type;

	union {
		stwuct {
			u8 hwid;
			u8 session;
			u8 padding_1[54];
		} __packed device;
		/* sta & p2p_cwi use the same stwuct */
		stwuct {
			u8 bssid[ETH_AWEN];
			u8 hwid; /* data hwid */
			u8 session;
			__we32 wemote_wates; /* wemote suppowted wates */

			/*
			 * The tawget uses this fiewd to detewmine the wate at
			 * which to twansmit contwow fwame wesponses (such as
			 * ACK ow CTS fwames).
			 */
			__we32 basic_wate_set;
			__we32 wocaw_wates; /* wocaw suppowted wates */

			u8 ssid_type;
			u8 ssid_wen;
			u8 ssid[IEEE80211_MAX_SSID_WEN];

			__we16 beacon_intewvaw; /* in TBTTs */
		} __packed sta;
		stwuct {
			u8 bssid[ETH_AWEN];
			u8 hwid; /* data hwid */
			u8 dtim_intewvaw;
			__we32 wemote_wates; /* wemote suppowted wates */

			__we32 basic_wate_set;
			__we32 wocaw_wates; /* wocaw suppowted wates */

			u8 ssid_type;
			u8 ssid_wen;
			u8 ssid[IEEE80211_MAX_SSID_WEN];

			__we16 beacon_intewvaw; /* in TBTTs */

			u8 padding_1[4];
		} __packed ibss;
		/* ap & p2p_go use the same stwuct */
		stwuct {
			__we16 aging_pewiod; /* in secs */
			u8 beacon_expiwy; /* in ms */
			u8 bss_index;
			/* The host wink id fow the AP's gwobaw queue */
			u8 gwobaw_hwid;
			/* The host wink id fow the AP's bwoadcast queue */
			u8 bwoadcast_hwid;

			__we16 beacon_intewvaw; /* in TBTTs */

			__we32 basic_wate_set;
			__we32 wocaw_wates; /* wocaw suppowted wates */

			u8 dtim_intewvaw;

			u8 ssid_type;
			u8 ssid_wen;
			u8 ssid[IEEE80211_MAX_SSID_WEN];

			u8 weset_tsf;

			/*
			 * ap suppowts wmm (note that thewe is additionaw
			 * pew-sta wmm configuwation)
			 */
			u8 wmm;

			u8 bcast_session_id;
			u8 gwobaw_session_id;
			u8 padding_1[1];
		} __packed ap;
	};
} __packed;

stwuct ww12xx_cmd_wowe_stop {
	stwuct ww1271_cmd_headew headew;

	u8 wowe_id;
	u8 disc_type; /* onwy STA and P2P_CWI */
	__we16 weason; /* onwy STA and P2P_CWI */
} __packed;

stwuct cmd_enabwedisabwe_path {
	stwuct ww1271_cmd_headew headew;

	u8 channew;
	u8 padding[3];
} __packed;

#define WW1271_WATE_AUTOMATIC  0

stwuct ww1271_cmd_tempwate_set {
	stwuct ww1271_cmd_headew headew;

	u8 wowe_id;
	u8 tempwate_type;
	__we16 wen;
	u8 index;  /* wewevant onwy fow KWV_TEMPWATE type */
	u8 padding[3];

	__we32 enabwed_wates;
	u8 showt_wetwy_wimit;
	u8 wong_wetwy_wimit;
	u8 afwags;
	u8 wesewved;

	u8 tempwate_data[WW1271_CMD_TEMPW_MAX_SIZE];
} __packed;

#define TIM_EWE_ID    5
#define PAWTIAW_VBM_MAX    251

stwuct ww1271_tim {
	u8 identity;
	u8 wength;
	u8 dtim_count;
	u8 dtim_pewiod;
	u8 bitmap_ctww;
	u8 pvb_fiewd[PAWTIAW_VBM_MAX]; /* Pawtiaw Viwtuaw Bitmap */
} __packed;

enum ww1271_cmd_ps_mode {
	STATION_AUTO_PS_MODE,   /* Dynamic Powew Save */
	STATION_ACTIVE_MODE,
	STATION_POWEW_SAVE_MODE
};

stwuct ww1271_cmd_ps_pawams {
	stwuct ww1271_cmd_headew headew;

	u8 wowe_id;
	u8 ps_mode; /* STATION_* */
	u16 auto_ps_timeout;
} __packed;

/* HW encwyption keys */
#define NUM_ACCESS_CATEGOWIES_COPY 4

enum ww1271_cmd_key_action {
	KEY_ADD_OW_WEPWACE = 1,
	KEY_WEMOVE         = 2,
	KEY_SET_ID         = 3,
	MAX_KEY_ACTION     = 0xffff,
};

enum ww1271_cmd_wid_key_type {
	UNICAST_WID_TYPE     = 0,
	BWOADCAST_WID_TYPE   = 1,
	WEP_DEFAUWT_WID_TYPE = 2
};

enum ww1271_cmd_key_type {
	KEY_NONE = 0,
	KEY_WEP  = 1,
	KEY_TKIP = 2,
	KEY_AES  = 3,
	KEY_GEM  = 4,
};

stwuct ww1271_cmd_set_keys {
	stwuct ww1271_cmd_headew headew;

	/*
	 * Indicates whethew the HWID is a unicast key set
	 * ow bwoadcast key set. A speciaw vawue 0xFF is
	 * used to indicate that the HWID is on WEP-defauwt
	 * (muwti-hwids). of type ww1271_cmd_wid_key_type.
	 */
	u8 hwid;

	/*
	 * In WEP-defauwt netwowk (hwid == 0xFF) used to
	 * indicate which netwowk STA/IBSS/AP wowe shouwd be
	 * changed
	 */
	u8 wid_key_type;

	/*
	 * Key ID - Fow TKIP and AES key types, this fiewd
	 * indicates the vawue that shouwd be insewted into
	 * the KeyID fiewd of fwames twansmitted using this
	 * key entwy. Fow bwoadcast keys the index use as a
	 * mawkew fow TX/WX key.
	 * Fow WEP defauwt netwowk (HWID=0xFF), this fiewd
	 * indicates the ID of the key to add ow wemove.
	 */
	u8 key_id;
	u8 wesewved_1;

	/* key_action_e */
	__we16 key_action;

	/* key size in bytes */
	u8 key_size;

	/* key_type_e */
	u8 key_type;

	/* This fiewd howds the secuwity key data to add to the STA tabwe */
	u8 key[MAX_KEY_SIZE];
	__we16 ac_seq_num16[NUM_ACCESS_CATEGOWIES_COPY];
	__we32 ac_seq_num32[NUM_ACCESS_CATEGOWIES_COPY];
} __packed;

stwuct ww1271_cmd_test_headew {
	u8 id;
	u8 padding[3];
} __packed;

enum ww1271_channew_tune_bands {
	WW1271_CHANNEW_TUNE_BAND_2_4,
	WW1271_CHANNEW_TUNE_BAND_5,
	WW1271_CHANNEW_TUNE_BAND_4_9
};

#define WW1271_PD_WEFEWENCE_POINT_BAND_B_G  0

/*
 * Thewe awe thwee types of disconnections:
 *
 * DISCONNECT_IMMEDIATE: the fw doesn't send any fwames
 * DISCONNECT_DEAUTH:    the fw genewates a DEAUTH wequest with the weason
 *                       we have passed
 * DISCONNECT_DISASSOC:  the fw genewates a DESASSOC wequest with the weason
 *                       we have passed
 */
enum ww1271_disconnect_type {
	DISCONNECT_IMMEDIATE,
	DISCONNECT_DEAUTH,
	DISCONNECT_DISASSOC
};

#define WW1271_CMD_STA_STATE_CONNECTED  1

stwuct ww12xx_cmd_set_peew_state {
	stwuct ww1271_cmd_headew headew;

	u8 hwid;
	u8 state;

	/*
	 * wmm is wewevant fow sta wowe onwy.
	 * ap wowe configuwes the pew-sta wmm pawams in
	 * the add_peew command.
	 */
	u8 wmm;
	u8 padding[1];
} __packed;

stwuct ww12xx_cmd_woc {
	stwuct ww1271_cmd_headew headew;

	u8 wowe_id;
	u8 channew;
	u8 band;
	u8 padding;
};

stwuct ww12xx_cmd_cwoc {
	stwuct ww1271_cmd_headew headew;

	u8 wowe_id;
	u8 padding[3];
};

enum ww12xx_ssid_type {
	WW12XX_SSID_TYPE_PUBWIC = 0,
	WW12XX_SSID_TYPE_HIDDEN = 1,
	WW12XX_SSID_TYPE_ANY = 2,
};

enum ww1271_psd_type {
	WW1271_PSD_WEGACY = 0,
	WW1271_PSD_UPSD_TWIGGEW = 1,
	WW1271_PSD_WEGACY_PSPOWW = 2,
	WW1271_PSD_SAPSD = 3
};

stwuct ww12xx_cmd_add_peew {
	stwuct ww1271_cmd_headew headew;

	u8 addw[ETH_AWEN];
	u8 hwid;
	u8 aid;
	u8 psd_type[NUM_ACCESS_CATEGOWIES_COPY];
	__we32 suppowted_wates;
	u8 bss_index;
	u8 sp_wen;
	u8 wmm;
	u8 session_id;
	u8 wowe_id;
	u8 padding[3];
} __packed;

stwuct ww12xx_cmd_wemove_peew {
	stwuct ww1271_cmd_headew headew;

	u8 hwid;
	u8 weason_opcode;
	u8 send_deauth_fwag;
	u8 wowe_id;
} __packed;

/*
 * Continuous mode - packets awe twansfewwed to the host pewiodicawwy
 * via the data path.
 * On demand - Wog messages awe stowed in a cycwic buffew in the
 * fiwmwawe, and onwy twansfewwed to the host when expwicitwy wequested
 */
enum ww12xx_fwwoggew_wog_mode {
	WW12XX_FWWOG_CONTINUOUS,
};

/* Incwude/excwude timestamps fwom the wog messages */
enum ww12xx_fwwoggew_timestamp {
	WW12XX_FWWOG_TIMESTAMP_DISABWED,
	WW12XX_FWWOG_TIMESTAMP_ENABWED
};

/*
 * Wogs can be wouted to the debug pinouts (whewe avaiwabwe), to the host bus
 * (SDIO/SPI), ow dwopped
 */
enum ww12xx_fwwoggew_output {
	WW12XX_FWWOG_OUTPUT_NONE,
	WW12XX_FWWOG_OUTPUT_DBG_PINS,
	WW12XX_FWWOG_OUTPUT_HOST,
};

stwuct ww12xx_cmd_wegdomain_dfs_config {
	stwuct ww1271_cmd_headew headew;

	__we32 ch_bit_map1;
	__we32 ch_bit_map2;
	u8 dfs_wegion;
	u8 padding[3];
} __packed;

enum wwcowe_genewic_cfg_featuwe {
	WWCOWE_CFG_FEATUWE_WADAW_DEBUG = 2,
};

stwuct wwcowe_cmd_genewic_cfg {
	stwuct ww1271_cmd_headew headew;

	u8 wowe_id;
	u8 featuwe;
	u8 enabwe;
	u8 vawue;
} __packed;

stwuct ww12xx_cmd_config_fwwog {
	stwuct ww1271_cmd_headew headew;

	/* See enum ww12xx_fwwoggew_wog_mode */
	u8 woggew_mode;

	/* Minimum wog wevew thweshowd */
	u8 wog_sevewity;

	/* Incwude/excwude timestamps fwom the wog messages */
	u8 timestamp;

	/* See enum ww1271_fwwoggew_output */
	u8 output;

	/* Weguwates the fwequency of wog messages */
	u8 thweshowd;

	u8 padding[3];
} __packed;

stwuct ww12xx_cmd_stawt_fwwog {
	stwuct ww1271_cmd_headew headew;
} __packed;

stwuct ww12xx_cmd_stop_fwwog {
	stwuct ww1271_cmd_headew headew;
} __packed;

stwuct ww12xx_cmd_stop_channew_switch {
	stwuct ww1271_cmd_headew headew;

	u8 wowe_id;
	u8 padding[3];
} __packed;

/* Used to check wadio status aftew cawibwation */
#define MAX_TWV_WENGTH		500
#define TEST_CMD_P2G_CAW	2	/* TX BiP */

stwuct ww1271_cmd_caw_p2g {
	stwuct ww1271_cmd_headew headew;

	stwuct ww1271_cmd_test_headew test;

	__we32 vew;
	__we16 wen;
	u8 buf[MAX_TWV_WENGTH];
	u8 type;
	u8 padding;

	__we16 wadio_status;

	u8 sub_band_mask;
	u8 padding2;
} __packed;

#endif /* __WW1271_CMD_H__ */
