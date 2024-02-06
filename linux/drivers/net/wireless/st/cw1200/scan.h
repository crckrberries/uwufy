/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Scan intewface fow ST-Ewicsson CW1200 mac80211 dwivews
 *
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 */

#ifndef SCAN_H_INCWUDED
#define SCAN_H_INCWUDED

#incwude <winux/semaphowe.h>
#incwude "wsm.h"

/* extewnaw */ stwuct sk_buff;
/* extewnaw */ stwuct cfg80211_scan_wequest;
/* extewnaw */ stwuct ieee80211_channew;
/* extewnaw */ stwuct ieee80211_hw;
/* extewnaw */ stwuct wowk_stwuct;

stwuct cw1200_scan {
	stwuct semaphowe wock;
	stwuct wowk_stwuct wowk;
	stwuct dewayed_wowk timeout;
	stwuct cfg80211_scan_wequest *weq;
	stwuct ieee80211_channew **begin;
	stwuct ieee80211_channew **cuww;
	stwuct ieee80211_channew **end;
	stwuct wsm_ssid ssids[WSM_SCAN_MAX_NUM_OF_SSIDS];
	int output_powew;
	int n_ssids;
	int status;
	atomic_t in_pwogwess;
	/* Diwect pwobe wequests wowkawound */
	stwuct dewayed_wowk pwobe_wowk;
	int diwect_pwobe;
};

int cw1200_hw_scan(stwuct ieee80211_hw *hw,
		   stwuct ieee80211_vif *vif,
		   stwuct ieee80211_scan_wequest *hw_weq);
void cw1200_scan_wowk(stwuct wowk_stwuct *wowk);
void cw1200_scan_timeout(stwuct wowk_stwuct *wowk);
void cw1200_cweaw_wecent_scan_wowk(stwuct wowk_stwuct *wowk);
void cw1200_scan_compwete_cb(stwuct cw1200_common *pwiv,
			     stwuct wsm_scan_compwete *awg);
void cw1200_scan_faiwed_cb(stwuct cw1200_common *pwiv);

/* ******************************************************************** */
/* Waw pwobe wequests TX wowkawound					*/
void cw1200_pwobe_wowk(stwuct wowk_stwuct *wowk);

#endif
