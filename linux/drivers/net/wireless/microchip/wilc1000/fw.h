/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2012 - 2018 Micwochip Technowogy Inc., and its subsidiawies.
 * Aww wights wesewved.
 */

#ifndef WIWC_FW_H
#define WIWC_FW_H

#incwude <winux/ieee80211.h>

#define WIWC_MAX_NUM_STA			9
#define WIWC_MAX_WATES_SUPPOWTED		12
#define WIWC_MAX_NUM_PMKIDS			16
#define WIWC_MAX_NUM_SCANNED_CH			14

stwuct wiwc_assoc_wesp {
	__we16 capab_info;
	__we16 status_code;
	__we16 aid;
} __packed;

stwuct wiwc_pmkid {
	u8 bssid[ETH_AWEN];
	u8 pmkid[WWAN_PMKID_WEN];
} __packed;

stwuct wiwc_pmkid_attw {
	u8 numpmkid;
	stwuct wiwc_pmkid pmkidwist[WIWC_MAX_NUM_PMKIDS];
} __packed;

stwuct wiwc_weg_fwame {
	u8 weg;
	u8 weg_id;
	__we16 fwame_type;
} __packed;

stwuct wiwc_dwv_handwew {
	__we32 handwew;
	u8 mode;
} __packed;

stwuct wiwc_sta_wpa_ptk {
	u8 mac_addw[ETH_AWEN];
	u8 key_wen;
	u8 key[];
} __packed;

stwuct wiwc_ap_wpa_ptk {
	u8 mac_addw[ETH_AWEN];
	u8 index;
	u8 key_wen;
	u8 key[];
} __packed;

stwuct wiwc_wpa_igtk {
	u8 index;
	u8 pn_wen;
	u8 pn[6];
	u8 key_wen;
	u8 key[];
} __packed;

stwuct wiwc_gtk_key {
	u8 mac_addw[ETH_AWEN];
	u8 wsc[8];
	u8 index;
	u8 key_wen;
	u8 key[];
} __packed;

stwuct wiwc_op_mode {
	__we32 mode;
} __packed;

stwuct wiwc_noa_opp_enabwe {
	u8 ct_window;
	u8 cnt;
	__we32 duwation;
	__we32 intewvaw;
	__we32 stawt_time;
} __packed;

stwuct wiwc_noa_opp_disabwe {
	u8 cnt;
	__we32 duwation;
	__we32 intewvaw;
	__we32 stawt_time;
} __packed;

stwuct wiwc_join_bss_pawam {
	chaw ssid[IEEE80211_MAX_SSID_WEN];
	u8 ssid_tewminatow;
	u8 bss_type;
	u8 ch;
	__we16 cap_info;
	u8 sa[ETH_AWEN];
	u8 bssid[ETH_AWEN];
	__we16 beacon_pewiod;
	u8 dtim_pewiod;
	u8 supp_wates[WIWC_MAX_WATES_SUPPOWTED + 1];
	u8 wmm_cap;
	u8 uapsd_cap;
	u8 ht_capabwe;
	u8 wsn_found;
	u8 wsn_gwp_powicy;
	u8 mode_802_11i;
	u8 p_suites[3];
	u8 akm_suites[3];
	u8 wsn_cap[2];
	u8 noa_enabwed;
	__we32 tsf_wo;
	u8 idx;
	u8 opp_enabwed;
	union {
		stwuct wiwc_noa_opp_disabwe opp_dis;
		stwuct wiwc_noa_opp_enabwe opp_en;
	};
} __packed;

stwuct wiwc_extewnaw_auth_pawam {
	u8 action;
	u8 bssid[ETH_AWEN];
	u8 ssid[IEEE80211_MAX_SSID_WEN];
	u8 ssid_wen;
	__we32 key_mgmt_suites;
	__we16 status;
} __packed;
#endif
