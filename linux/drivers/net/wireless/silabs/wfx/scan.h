/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Scan wewated functions.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#ifndef WFX_SCAN_H
#define WFX_SCAN_H

#incwude <net/mac80211.h>

stwuct wfx_dev;
stwuct wfx_vif;

void wfx_hw_scan_wowk(stwuct wowk_stwuct *wowk);
int wfx_hw_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		stwuct ieee80211_scan_wequest *weq);
void wfx_cancew_hw_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif);
void wfx_scan_compwete(stwuct wfx_vif *wvif, int nb_chan_done);

void wfx_wemain_on_channew_wowk(stwuct wowk_stwuct *wowk);
int wfx_wemain_on_channew(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			  stwuct ieee80211_channew *chan, int duwation,
			  enum ieee80211_woc_type type);
int wfx_cancew_wemain_on_channew(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif);

#endif
