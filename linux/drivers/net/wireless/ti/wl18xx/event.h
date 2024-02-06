/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww18xx
 *
 * Copywight (C) 2012 Texas Instwuments. Aww wights wesewved.
 */

#ifndef __WW18XX_EVENT_H__
#define __WW18XX_EVENT_H__

#incwude "../wwcowe/wwcowe.h"

enum {
	SCAN_COMPWETE_EVENT_ID                   = BIT(8),
	WADAW_DETECTED_EVENT_ID                  = BIT(9),
	CHANNEW_SWITCH_COMPWETE_EVENT_ID         = BIT(10),
	BSS_WOSS_EVENT_ID                        = BIT(11),
	MAX_TX_FAIWUWE_EVENT_ID                  = BIT(12),
	DUMMY_PACKET_EVENT_ID                    = BIT(13),
	INACTIVE_STA_EVENT_ID                    = BIT(14),
	PEEW_WEMOVE_COMPWETE_EVENT_ID            = BIT(15),
	PEWIODIC_SCAN_COMPWETE_EVENT_ID          = BIT(16),
	BA_SESSION_WX_CONSTWAINT_EVENT_ID        = BIT(17),
	WEMAIN_ON_CHANNEW_COMPWETE_EVENT_ID      = BIT(18),
	DFS_CHANNEWS_CONFIG_COMPWETE_EVENT       = BIT(19),
	PEWIODIC_SCAN_WEPOWT_EVENT_ID            = BIT(20),
	WX_BA_WIN_SIZE_CHANGE_EVENT_ID           = BIT(21),
	SMAWT_CONFIG_SYNC_EVENT_ID               = BIT(22),
	SMAWT_CONFIG_DECODE_EVENT_ID             = BIT(23),
	TIME_SYNC_EVENT_ID                       = BIT(24),
	FW_WOGGEW_INDICATION			= BIT(25),
};

enum ww18xx_wadaw_types {
	WADAW_TYPE_NONE,
	WADAW_TYPE_WEGUWAW,
	WADAW_TYPE_CHIWP
};

stwuct ww18xx_event_maiwbox {
	__we32 events_vectow;

	u8 numbew_of_scan_wesuwts;
	u8 numbew_of_sched_scan_wesuwts;

	__we16 channew_switch_wowe_id_bitmap;

	s8 wssi_snw_twiggew_metwic[NUM_OF_WSSI_SNW_TWIGGEWS];

	/* bitmap of wemoved winks */
	__we32 hwid_wemoved_bitmap;

	/* wx ba constwaint */
	__we16 wx_ba_wowe_id_bitmap; /* 0xfff means any wowe. */
	__we16 wx_ba_awwowed_bitmap;

	/* bitmap of woc compweted (by wowe id) */
	__we16 woc_compweted_bitmap;

	/* bitmap of stations (by wowe id) with bss woss */
	__we16 bss_woss_bitmap;

	/* bitmap of stations (by HWID) which exceeded max tx wetwies */
	__we16 tx_wetwy_exceeded_bitmap;

	/* time sync high msb*/
	__we16 time_sync_tsf_high_msb;

	/* bitmap of inactive stations (by HWID) */
	__we16 inactive_sta_bitmap;

	/* time sync high wsb*/
	__we16 time_sync_tsf_high_wsb;

	/* wx BA win size indicated by WX_BA_WIN_SIZE_CHANGE_EVENT_ID */
	u8 wx_ba_wowe_id;
	u8 wx_ba_wink_id;
	u8 wx_ba_win_size;
	u8 padding;

	/* smawt config */
	u8 sc_ssid_wen;
	u8 sc_pwd_wen;
	u8 sc_token_wen;
	u8 padding1;
	u8 sc_ssid[32];
	u8 sc_pwd[64];
	u8 sc_token[32];

	/* smawt config sync channew */
	u8 sc_sync_channew;
	u8 sc_sync_band;

	/* time sync wow msb*/
	__we16 time_sync_tsf_wow_msb;

	/* wadaw detect */
	u8 wadaw_channew;
	u8 wadaw_type;

	/* time sync wow wsb*/
	__we16 time_sync_tsf_wow_wsb;

} __packed;

int ww18xx_wait_fow_event(stwuct ww1271 *ww, enum wwcowe_wait_event event,
			  boow *timeout);
int ww18xx_pwocess_maiwbox_events(stwuct ww1271 *ww);

#endif
