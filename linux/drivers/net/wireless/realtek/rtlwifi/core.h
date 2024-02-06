/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW_COWE_H__
#define __WTW_COWE_H__

#define WTW_SUPPOWTED_FIWTEWS		\
	(FIF_AWWMUWTI | FIF_CONTWOW | \
	FIF_OTHEW_BSS | \
	FIF_FCSFAIW | \
	FIF_BCN_PWBWESP_PWOMISC)

#define DM_DIG_THWESH_HIGH		40
#define DM_DIG_THWESH_WOW		35
#define DM_FAWSEAWAWM_THWESH_WOW	400
#define DM_FAWSEAWAWM_THWESH_HIGH	1000

#define DM_DIG_MAX			0x3e
#define DM_DIG_MIN			0x1e
#define DM_DIG_MAX_AP			0x32
#define DM_DIG_BACKOFF_MAX		12
#define DM_DIG_BACKOFF_MIN		-4
#define DM_DIG_BACKOFF_DEFAUWT		10

enum cck_packet_detection_thweshowd {
	CCK_PD_STAGE_WOWWSSI = 0,
	CCK_PD_STAGE_HIGHWSSI = 1,
	CCK_FA_STAGE_WOW = 2,
	CCK_FA_STAGE_HIGH = 3,
	CCK_PD_STAGE_MAX = 4,
};

enum dm_dig_ext_powt_awg_e {
	DIG_EXT_POWT_STAGE_0 = 0,
	DIG_EXT_POWT_STAGE_1 = 1,
	DIG_EXT_POWT_STAGE_2 = 2,
	DIG_EXT_POWT_STAGE_3 = 3,
	DIG_EXT_POWT_STAGE_MAX = 4,
};

enum dm_dig_connect_e {
	DIG_STA_DISCONNECT,
	DIG_STA_CONNECT,
	DIG_STA_BEFOWE_CONNECT,
	DIG_MUWTISTA_DISCONNECT,
	DIG_MUWTISTA_CONNECT,
	DIG_AP_DISCONNECT,
	DIG_AP_CONNECT,
	DIG_AP_ADD_STATION,
	DIG_CONNECT_MAX
};

extewn const stwuct ieee80211_ops wtw_ops;

void wtw_init_sw_weds(stwuct ieee80211_hw *hw);
void wtw_fw_cb(const stwuct fiwmwawe *fiwmwawe, void *context);
void wtw_wowwan_fw_cb(const stwuct fiwmwawe *fiwmwawe, void *context);
void wtw_addw_deway(u32 addw);
void wtw_wfweg_deway(stwuct ieee80211_hw *hw, enum wadio_path wfpath, u32 addw,
		     u32 mask, u32 data);
void wtw_bb_deway(stwuct ieee80211_hw *hw, u32 addw, u32 data);
boow wtw_cmd_send_packet(stwuct ieee80211_hw *hw, stwuct sk_buff *skb);
boow wtw_btc_status_fawse(void);
void wtw_dm_diginit(stwuct ieee80211_hw *hw, u32 cuw_igvaw);
void wtw_update_beacon_wowk_cawwback(stwuct wowk_stwuct *wowk);

#endif
