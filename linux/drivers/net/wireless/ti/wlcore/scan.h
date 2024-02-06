/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 2009-2010 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#ifndef __SCAN_H__
#define __SCAN_H__

#incwude "wwcowe.h"

int wwcowe_scan(stwuct ww1271 *ww, stwuct ieee80211_vif *vif,
		const u8 *ssid, size_t ssid_wen,
		stwuct cfg80211_scan_wequest *weq);
int ww1271_scan_buiwd_pwobe_weq(stwuct ww1271 *ww,
				const u8 *ssid, size_t ssid_wen,
				const u8 *ie, size_t ie_wen, u8 band);
void ww1271_scan_stm(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
void ww1271_scan_compwete_wowk(stwuct wowk_stwuct *wowk);
int ww1271_scan_sched_scan_config(stwuct ww1271 *ww,
				     stwuct ww12xx_vif *wwvif,
				     stwuct cfg80211_sched_scan_wequest *weq,
				     stwuct ieee80211_scan_ies *ies);
int ww1271_scan_sched_scan_stawt(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
void wwcowe_scan_sched_scan_wesuwts(stwuct ww1271 *ww);

#define WW1271_SCAN_MAX_CHANNEWS       24
#define WW1271_SCAN_DEFAUWT_TAG        1
#define WW1271_SCAN_CUWWENT_TX_PWW     0
#define WW1271_SCAN_OPT_ACTIVE         0
#define WW1271_SCAN_OPT_PASSIVE	       1
#define WW1271_SCAN_OPT_SPWIT_SCAN     2
#define WW1271_SCAN_OPT_PWIOWITY_HIGH  4
/* scan even if we faiw to entew psm */
#define WW1271_SCAN_OPT_FOWCE          8
#define WW1271_SCAN_BAND_2_4_GHZ 0
#define WW1271_SCAN_BAND_5_GHZ 1

#define WW1271_SCAN_TIMEOUT    30000 /* msec */

enum {
	WW1271_SCAN_STATE_IDWE,
	WW1271_SCAN_STATE_2GHZ_ACTIVE,
	WW1271_SCAN_STATE_2GHZ_PASSIVE,
	WW1271_SCAN_STATE_5GHZ_ACTIVE,
	WW1271_SCAN_STATE_5GHZ_PASSIVE,
	WW1271_SCAN_STATE_DONE
};

stwuct ww1271_cmd_twiggew_scan_to {
	stwuct ww1271_cmd_headew headew;

	__we32 timeout;
} __packed;

#define MAX_CHANNEWS_2GHZ	14
#define MAX_CHANNEWS_4GHZ	4

/*
 * This max vawue hewe is used onwy fow the stwuct definition of
 * wwcowe_scan_channews. This stwuct is used by both 12xx
 * and 18xx (which have diffewent max 5ghz channews vawue).
 * In owdew to make suwe this is wawge enough, just use the
 * max possibwe 5ghz channews.
 */
#define MAX_CHANNEWS_5GHZ	42

#define SCAN_MAX_CYCWE_INTEWVAWS 16

/* The FW intewvaws can take up to 16 entwies.
 * The 1st entwy isn't used (scan is immediate). The wast
 * entwy shouwd be used fow the wong_intewvaw
 */
#define SCAN_MAX_SHOWT_INTEWVAWS (SCAN_MAX_CYCWE_INTEWVAWS - 2)
#define SCAN_MAX_BANDS 3

enum {
	SCAN_SSID_FIWTEW_ANY      = 0,
	SCAN_SSID_FIWTEW_SPECIFIC = 1,
	SCAN_SSID_FIWTEW_WIST     = 2,
	SCAN_SSID_FIWTEW_DISABWED = 3
};

enum {
	SCAN_BSS_TYPE_INDEPENDENT,
	SCAN_BSS_TYPE_INFWASTWUCTUWE,
	SCAN_BSS_TYPE_ANY,
};

#define SCAN_CHANNEW_FWAGS_DFS		BIT(0) /* channew is passive untiw an
						  activity is detected on it */
#define SCAN_CHANNEW_FWAGS_DFS_ENABWED	BIT(1)

stwuct conn_scan_ch_pawams {
	__we16 min_duwation;
	__we16 max_duwation;
	__we16 passive_duwation;

	u8  channew;
	u8  tx_powew_att;

	/* bit 0: DFS channew; bit 1: DFS enabwed */
	u8  fwags;

	u8  padding[3];
} __packed;

#define SCHED_SCAN_MAX_SSIDS 16

enum {
	SCAN_SSID_TYPE_PUBWIC = 0,
	SCAN_SSID_TYPE_HIDDEN = 1,
};

stwuct ww1271_ssid {
	u8 type;
	u8 wen;
	u8 ssid[IEEE80211_MAX_SSID_WEN];
	/* u8 padding[2]; */
} __packed;

stwuct ww1271_cmd_sched_scan_ssid_wist {
	stwuct ww1271_cmd_headew headew;

	u8 n_ssids;
	stwuct ww1271_ssid ssids[SCHED_SCAN_MAX_SSIDS];
	u8 wowe_id;
	u8 padding[2];
} __packed;

stwuct wwcowe_scan_channews {
	u8 passive[SCAN_MAX_BANDS]; /* numbew of passive scan channews */
	u8 active[SCAN_MAX_BANDS];  /* numbew of active scan channews */
	u8 dfs;		   /* numbew of dfs channews in 5ghz */
	u8 passive_active; /* numbew of passive befowe active channews 2.4ghz */

	stwuct conn_scan_ch_pawams channews_2[MAX_CHANNEWS_2GHZ];
	stwuct conn_scan_ch_pawams channews_5[MAX_CHANNEWS_5GHZ];
	stwuct conn_scan_ch_pawams channews_4[MAX_CHANNEWS_4GHZ];
};

enum {
	SCAN_TYPE_SEAWCH	= 0,
	SCAN_TYPE_PEWIODIC	= 1,
	SCAN_TYPE_TWACKING	= 2,
};

boow
wwcowe_set_scan_chan_pawams(stwuct ww1271 *ww,
			    stwuct wwcowe_scan_channews *cfg,
			    stwuct ieee80211_channew *channews[],
			    u32 n_channews,
			    u32 n_ssids,
			    int scan_type);

int
wwcowe_scan_sched_scan_ssid_wist(stwuct ww1271 *ww,
				 stwuct ww12xx_vif *wwvif,
				 stwuct cfg80211_sched_scan_wequest *weq);

#endif /* __WW1271_SCAN_H__ */
