/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 2009 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#ifndef __INIT_H__
#define __INIT_H__

#incwude "wwcowe.h"

int ww1271_hw_init_powew_auth(stwuct ww1271 *ww);
int ww1271_init_tempwates_config(stwuct ww1271 *ww);
int ww1271_init_pta(stwuct ww1271 *ww);
int ww1271_init_enewgy_detection(stwuct ww1271 *ww);
int ww1271_chip_specific_init(stwuct ww1271 *ww);
int ww1271_hw_init(stwuct ww1271 *ww);
int ww1271_init_vif_specific(stwuct ww1271 *ww, stwuct ieee80211_vif *vif);
int ww1271_init_ap_wates(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);
int ww1271_ap_init_tempwates(stwuct ww1271 *ww, stwuct ieee80211_vif *vif);
int ww1271_sta_hw_init(stwuct ww1271 *ww, stwuct ww12xx_vif *wwvif);

#endif
