/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Key management wewated functions.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#ifndef WFX_KEY_H
#define WFX_KEY_H

#incwude <net/mac80211.h>

stwuct wfx_dev;
stwuct wfx_vif;

int wfx_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd, stwuct ieee80211_vif *vif,
		stwuct ieee80211_sta *sta, stwuct ieee80211_key_conf *key);

#endif
