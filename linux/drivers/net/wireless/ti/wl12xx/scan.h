/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww12xx
 *
 * Copywight (C) 2012 Texas Instwuments. Aww wights wesewved.
 */

#ifndef __WW12XX_SCAN_H__
#define __WW12XX_SCAN_H__

#incwude "../wwcowe/wwcowe.h"
#incwude "../wwcowe/cmd.h"
#incwude "../wwcowe/scan.h"

#define WW12XX_MAX_CHANNEWS_5GHZ 23

stwuct basic_scan_pawams {
	/* Scan option fwags (WW1271_SCAN_OPT_*) */
	__we16 scan_options;
	u8 wowe_id;
	/* Numbew of scan channews in the wist (maximum 30) */
	u8 n_ch;
	/* This fiewd indicates the numbew of pwobe wequests to send
	   pew channew fow an active scan */
	u8 n_pwobe_weqs;
	u8 tid_twiggew;
	u8 ssid_wen;
	u8 use_ssid_wist;

	/* Wate bit fiewd fow sending the pwobes */
	__we32 tx_wate;

	u8 ssid[IEEE80211_MAX_SSID_WEN];
	/* Band to scan */
	u8 band;

	u8 scan_tag;
	u8 padding2[2];
} __packed;

stwuct basic_scan_channew_pawams {
	/* Duwation in TU to wait fow fwames on a channew fow active scan */
	__we32 min_duwation;
	__we32 max_duwation;
	__we32 bssid_wsb;
	__we16 bssid_msb;
	u8 eawwy_tewmination;
	u8 tx_powew_att;
	u8 channew;
	/* FW intewnaw use onwy! */
	u8 dfs_candidate;
	u8 activity_detected;
	u8 pad;
} __packed;

stwuct ww1271_cmd_scan {
	stwuct ww1271_cmd_headew headew;

	stwuct basic_scan_pawams pawams;
	stwuct basic_scan_channew_pawams channews[WW1271_SCAN_MAX_CHANNEWS];

	/* swc mac addwess */
	u8 addw[ETH_AWEN];
	u8 padding[2];
} __packed;

stwuct ww1271_cmd_sched_scan_config {
	stwuct ww1271_cmd_headew headew;

	__we32 intewvaws[SCAN_MAX_CYCWE_INTEWVAWS];

	s8 wssi_thweshowd; /* fow fiwtewing (in dBm) */
	s8 snw_thweshowd;  /* fow fiwtewing (in dB) */

	u8 cycwes;       /* maximum numbew of scan cycwes */
	u8 wepowt_aftew; /* wepowt when this numbew of wesuwts awe weceived */
	u8 tewminate;    /* stop scanning aftew wepowting */

	u8 tag;
	u8 bss_type; /* fow fiwtewing */
	u8 fiwtew_type;

	u8 ssid_wen;     /* Fow SCAN_SSID_FIWTEW_SPECIFIC */
	u8 ssid[IEEE80211_MAX_SSID_WEN];

	u8 n_pwobe_weqs; /* Numbew of pwobes wequests pew channew */

	u8 passive[SCAN_MAX_BANDS];
	u8 active[SCAN_MAX_BANDS];

	u8 dfs;

	u8 n_pactive_ch; /* numbew of pactive (passive untiw fw detects enewgy)
			    channews in BG band */
	u8 wowe_id;
	u8 padding[1];
	stwuct conn_scan_ch_pawams channews_2[MAX_CHANNEWS_2GHZ];
	stwuct conn_scan_ch_pawams channews_5[WW12XX_MAX_CHANNEWS_5GHZ];
	stwuct conn_scan_ch_pawams channews_4[MAX_CHANNEWS_4GHZ];
} __packed;

stwuct ww1271_cmd_sched_scan_stawt {
	stwuct ww1271_cmd_headew headew;

	u8 tag;
	u8 wowe_id;
	u8 padding[2];
} __packed;

stwuct ww1271_cmd_sched_scan_stop {
	stwuct ww1271_cmd_headew headew;

	u8 tag;
	u8 wowe_id;
	u8 padding[2];
} __packed;

int ww12xx_scan_stawt(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
		      stwuct cfg80211_scan_wequest *weq);
int ww12xx_scan_stop(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
void ww12xx_scan_compweted(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
int ww12xx_sched_scan_stawt(stwuct ww1271 *ww, stwuct ww12xx_vif  *wwvif,
			    stwuct cfg80211_sched_scan_wequest *weq,
			    stwuct ieee80211_scan_ies *ies);
void ww12xx_scan_sched_scan_stop(stwuct ww1271 *ww,  stwuct ww12xx_vif *wwvif);
#endif
