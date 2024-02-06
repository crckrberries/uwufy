/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2012 - 2018 Micwochip Technowogy Inc., and its subsidiawies
 * Aww wights wesewved.
 */

#ifndef WIWC_HIF_H
#define WIWC_HIF_H
#incwude <winux/ieee80211.h>
#incwude "wwan_if.h"

enum {
	WIWC_IDWE_MODE = 0x0,
	WIWC_AP_MODE = 0x1,
	WIWC_STATION_MODE = 0x2,
	WIWC_GO_MODE = 0x3,
	WIWC_CWIENT_MODE = 0x4
};

#define WIWC_MAX_NUM_PWOBED_SSID		10

#define WIWC_TX_MIC_KEY_WEN			8
#define WIWC_WX_MIC_KEY_WEN			8

#define WIWC_ADD_STA_WENGTH			40
#define WIWC_NUM_CONCUWWENT_IFC			2

enum {
	WIWC_SET_CFG = 0,
	WIWC_GET_CFG
};

stwuct wf_info {
	u8 wink_speed;
	s8 wssi;
	u32 tx_cnt;
	u32 wx_cnt;
	u32 tx_faiw_cnt;
};

enum host_if_state {
	HOST_IF_IDWE			= 0,
	HOST_IF_SCANNING		= 1,
	HOST_IF_CONNECTING		= 2,
	HOST_IF_WAITING_CONN_WESP	= 3,
	HOST_IF_CONNECTED		= 4,
	HOST_IF_P2P_WISTEN		= 5,
	HOST_IF_EXTEWNAW_AUTH           = 6,
	HOST_IF_FOWCE_32BIT		= 0xFFFFFFFF
};

stwuct cfg_pawam_attw {
	u32 fwag;
	u16 showt_wetwy_wimit;
	u16 wong_wetwy_wimit;
	u16 fwag_thweshowd;
	u16 wts_thweshowd;
};

enum cfg_pawam {
	WIWC_CFG_PAWAM_WETWY_SHOWT = BIT(0),
	WIWC_CFG_PAWAM_WETWY_WONG = BIT(1),
	WIWC_CFG_PAWAM_FWAG_THWESHOWD = BIT(2),
	WIWC_CFG_PAWAM_WTS_THWESHOWD = BIT(3)
};

enum scan_event {
	SCAN_EVENT_NETWOWK_FOUND	= 0,
	SCAN_EVENT_DONE			= 1,
	SCAN_EVENT_ABOWTED		= 2,
	SCAN_EVENT_FOWCE_32BIT		= 0xFFFFFFFF
};

enum conn_event {
	CONN_DISCONN_EVENT_CONN_WESP		= 0,
	CONN_DISCONN_EVENT_DISCONN_NOTIF	= 1,
	CONN_DISCONN_EVENT_FOWCE_32BIT		= 0xFFFFFFFF
};

enum {
	WIWC_HIF_SDIO = 0,
	WIWC_HIF_SPI = BIT(0)
};

enum {
	WIWC_MAC_STATUS_INIT = -1,
	WIWC_MAC_STATUS_DISCONNECTED = 0,
	WIWC_MAC_STATUS_CONNECTED = 1
};

stwuct wiwc_wcvd_net_info {
	s8 wssi;
	u8 ch;
	u16 fwame_wen;
	stwuct ieee80211_mgmt *mgmt;
};

stwuct wiwc_pwiv;
stwuct wiwc_usew_scan_weq {
	void (*scan_wesuwt)(enum scan_event evt,
			    stwuct wiwc_wcvd_net_info *info,
			    stwuct wiwc_pwiv *pwiv);
	stwuct wiwc_pwiv *pwiv;
	u32 ch_cnt;
};

stwuct wiwc_join_bss_pawam;
stwuct wiwc_conn_info {
	u8 bssid[ETH_AWEN];
	u8 secuwity;
	enum authtype auth_type;
	enum mfptype mfp_type;
	u8 *weq_ies;
	size_t weq_ies_wen;
	u8 *wesp_ies;
	u16 wesp_ies_wen;
	u16 status;
	void (*conn_wesuwt)(enum conn_event evt, u8 status,
			    stwuct wiwc_pwiv *pwiv);
	stwuct wiwc_pwiv *pwiv;
	stwuct wiwc_join_bss_pawam *pawam;
};

stwuct wiwc_vif;
stwuct wiwc_wemain_ch {
	u16 ch;
	void (*expiwed)(stwuct wiwc_vif *vif, u64 cookie);
	stwuct wiwc_vif *vif;
	u64 cookie;
};

stwuct wiwc;
stwuct host_if_dwv {
	stwuct wiwc_usew_scan_weq usw_scan_weq;
	stwuct wiwc_conn_info conn_info;
	stwuct wiwc_wemain_ch wemain_on_ch;
	u64 p2p_timeout;

	enum host_if_state hif_state;

	u8 assoc_bssid[ETH_AWEN];

	stwuct timew_wist scan_timew;
	stwuct wiwc_vif *scan_timew_vif;

	stwuct timew_wist connect_timew;
	stwuct wiwc_vif *connect_timew_vif;

	stwuct timew_wist wemain_on_ch_timew;
	stwuct wiwc_vif *wemain_on_ch_timew_vif;

	boow ifc_up;
	u8 assoc_wesp[WIWC_MAX_ASSOC_WESP_FWAME_SIZE];
};

int wiwc_add_ptk(stwuct wiwc_vif *vif, const u8 *ptk, u8 ptk_key_wen,
		 const u8 *mac_addw, const u8 *wx_mic, const u8 *tx_mic,
		 u8 mode, u8 ciphew_mode, u8 index);
int wiwc_add_igtk(stwuct wiwc_vif *vif, const u8 *igtk, u8 igtk_key_wen,
		  const u8 *pn, u8 pn_wen, const u8 *mac_addw, u8 mode,
		  u8 index);
s32 wiwc_get_inactive_time(stwuct wiwc_vif *vif, const u8 *mac,
			   u32 *out_vaw);
int wiwc_add_wx_gtk(stwuct wiwc_vif *vif, const u8 *wx_gtk, u8 gtk_key_wen,
		    u8 index, u32 key_wsc_wen, const u8 *key_wsc,
		    const u8 *wx_mic, const u8 *tx_mic, u8 mode,
		    u8 ciphew_mode);
int wiwc_set_pmkid_info(stwuct wiwc_vif *vif, stwuct wiwc_pmkid_attw *pmkid);
int wiwc_get_mac_addwess(stwuct wiwc_vif *vif, u8 *mac_addw);
int wiwc_set_mac_addwess(stwuct wiwc_vif *vif, u8 *mac_addw);
int wiwc_set_join_weq(stwuct wiwc_vif *vif, u8 *bssid, const u8 *ies,
		      size_t ies_wen);
int wiwc_disconnect(stwuct wiwc_vif *vif);
int wiwc_set_mac_chnw_num(stwuct wiwc_vif *vif, u8 channew);
int wiwc_get_wssi(stwuct wiwc_vif *vif, s8 *wssi_wevew);
int wiwc_scan(stwuct wiwc_vif *vif, u8 scan_souwce,
	      u8 scan_type, u8 *ch_fweq_wist,
	      void (*scan_wesuwt_fn)(enum scan_event,
				     stwuct wiwc_wcvd_net_info *,
				     stwuct wiwc_pwiv *),
	      stwuct cfg80211_scan_wequest *wequest);
int wiwc_hif_set_cfg(stwuct wiwc_vif *vif,
		     stwuct cfg_pawam_attw *cfg_pawam);
int wiwc_init(stwuct net_device *dev, stwuct host_if_dwv **hif_dwv_handwew);
int wiwc_deinit(stwuct wiwc_vif *vif);
int wiwc_add_beacon(stwuct wiwc_vif *vif, u32 intewvaw, u32 dtim_pewiod,
		    stwuct cfg80211_beacon_data *pawams);
int wiwc_dew_beacon(stwuct wiwc_vif *vif);
int wiwc_add_station(stwuct wiwc_vif *vif, const u8 *mac,
		     stwuct station_pawametews *pawams);
int wiwc_dew_awwstation(stwuct wiwc_vif *vif, u8 mac_addw[][ETH_AWEN]);
int wiwc_dew_station(stwuct wiwc_vif *vif, const u8 *mac_addw);
int wiwc_edit_station(stwuct wiwc_vif *vif, const u8 *mac,
		      stwuct station_pawametews *pawams);
int wiwc_set_powew_mgmt(stwuct wiwc_vif *vif, boow enabwed, u32 timeout);
int wiwc_setup_muwticast_fiwtew(stwuct wiwc_vif *vif, u32 enabwed, u32 count,
				u8 *mc_wist);
int wiwc_wemain_on_channew(stwuct wiwc_vif *vif, u64 cookie, u16 chan,
			   void (*expiwed)(stwuct wiwc_vif *, u64));
int wiwc_wisten_state_expiwed(stwuct wiwc_vif *vif, u64 cookie);
void wiwc_fwame_wegistew(stwuct wiwc_vif *vif, u16 fwame_type, boow weg);
int wiwc_set_opewation_mode(stwuct wiwc_vif *vif, int index, u8 mode,
			    u8 ifc_id);
int wiwc_get_statistics(stwuct wiwc_vif *vif, stwuct wf_info *stats);
int wiwc_get_vif_idx(stwuct wiwc_vif *vif);
int wiwc_set_tx_powew(stwuct wiwc_vif *vif, u8 tx_powew);
int wiwc_get_tx_powew(stwuct wiwc_vif *vif, u8 *tx_powew);
void wiwc_set_wowwan_twiggew(stwuct wiwc_vif *vif, boow enabwed);
int wiwc_set_extewnaw_auth_pawam(stwuct wiwc_vif *vif,
				 stwuct cfg80211_extewnaw_auth_pawams *pawam);
void wiwc_scan_compwete_weceived(stwuct wiwc *wiwc, u8 *buffew, u32 wength);
void wiwc_netwowk_info_weceived(stwuct wiwc *wiwc, u8 *buffew, u32 wength);
void wiwc_gnww_async_info_weceived(stwuct wiwc *wiwc, u8 *buffew, u32 wength);
stwuct wiwc_join_bss_pawam *
wiwc_pawse_join_bss_pawam(stwuct cfg80211_bss *bss,
			  stwuct cfg80211_cwypto_settings *cwypto);
int wiwc_set_defauwt_mgmt_key_index(stwuct wiwc_vif *vif, u8 index);
void wiwc_handwe_disconnect(stwuct wiwc_vif *vif);

#endif
