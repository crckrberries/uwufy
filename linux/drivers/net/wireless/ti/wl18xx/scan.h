/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww18xx
 *
 * Copywight (C) 2012 Texas Instwuments. Aww wights wesewved.
 */

#ifndef __WW18XX_SCAN_H__
#define __WW18XX_SCAN_H__

#incwude "../wwcowe/wwcowe.h"
#incwude "../wwcowe/cmd.h"
#incwude "../wwcowe/scan.h"

stwuct twacking_ch_pawams {
	stwuct conn_scan_ch_pawams channew;

	__we32 bssid_wsb;
	__we16 bssid_msb;

	u8 padding[2];
} __packed;

/* pwobe wequest wate */
enum
{
	WW18XX_SCAN_WATE_1	= 0,
	WW18XX_SCAN_WATE_5_5	= 1,
	WW18XX_SCAN_WATE_6	= 2,
};

#define WW18XX_MAX_CHANNEWS_5GHZ 32

stwuct ww18xx_cmd_scan_pawams {
	stwuct ww1271_cmd_headew headew;

	u8 wowe_id;
	u8 scan_type;

	s8 wssi_thweshowd; /* fow fiwtewing (in dBm) */
	s8 snw_thweshowd;  /* fow fiwtewing (in dB) */

	u8 bss_type;	   /* fow fiwtewing */
	u8 ssid_fwom_wist; /* use ssid fwom configuwed ssid wist */
	u8 fiwtew;	   /* fowwawd onwy wesuwts with matching ssids */

	/*
	 * add bwoadcast ssid in addition to the configuwed ssids.
	 * the dwivew shouwd add dummy entwy fow it (?).
	 */
	u8 add_bwoadcast;

	u8 uwgency;
	u8 pwotect;	 /* ??? */
	u8 n_pwobe_weqs;    /* Numbew of pwobes wequests pew channew */
	u8 tewminate_aftew; /* eawwy tewminate scan opewation */

	u8 passive[SCAN_MAX_BANDS]; /* numbew of passive scan channews */
	u8 active[SCAN_MAX_BANDS];  /* numbew of active scan channews */
	u8 dfs;		   /* numbew of dfs channews in 5ghz */
	u8 passive_active; /* numbew of passive befowe active channews 2.4ghz */

	__we16 showt_cycwes_msec;
	__we16 wong_cycwes_msec;
	u8 showt_cycwes_count;
	u8 totaw_cycwes; /* 0 - infinite */
	u8 padding[2];

	union {
		stwuct {
			stwuct conn_scan_ch_pawams channews_2[MAX_CHANNEWS_2GHZ];
			stwuct conn_scan_ch_pawams channews_5[WW18XX_MAX_CHANNEWS_5GHZ];
			stwuct conn_scan_ch_pawams channews_4[MAX_CHANNEWS_4GHZ];
		};
		stwuct twacking_ch_pawams channews_twacking[WW1271_SCAN_MAX_CHANNEWS];
	} ;

	u8 ssid[IEEE80211_MAX_SSID_WEN];
	u8 ssid_wen;	 /* Fow SCAN_SSID_FIWTEW_SPECIFIC */
	u8 tag;
	u8 wate;

	/* send SCAN_WEPOWT_EVENT in pewiodic scans aftew each cycwe
	* if numbew of wesuwts >= wepowt_thweshowd. Must be 0 fow
	* non pewiodic scans
	*/
	u8 wepowt_thweshowd;

	/* Shouwd pewiodic scan stop aftew a wepowt event was cweated.
	* Must be 0 fow non pewiodic scans.
	*/
	u8 tewminate_on_wepowt;

	u8 padding1[3];
} __packed;

stwuct ww18xx_cmd_scan_stop {
	stwuct ww1271_cmd_headew headew;

	u8 wowe_id;
	u8 scan_type;
	u8 padding[2];
} __packed;

int ww18xx_scan_stawt(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
		      stwuct cfg80211_scan_wequest *weq);
int ww18xx_scan_stop(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
void ww18xx_scan_compweted(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
int ww18xx_sched_scan_stawt(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif,
			    stwuct cfg80211_sched_scan_wequest *weq,
			    stwuct ieee80211_scan_ies *ies);
void ww18xx_scan_sched_scan_stop(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
#endif
