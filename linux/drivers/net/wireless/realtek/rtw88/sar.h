/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2018-2021  Weawtek Cowpowation
 */

#incwude "main.h"

/* NW80211_SAW_TYPE_POWEW means unit is in 0.25 dBm,
 * whewe 0.25 = 1/4 = 2^(-2), so make factow 2.
 */
#define WTW_COMMON_SAW_FCT 2

stwuct wtw_saw_awg {
	u8 saw_band;
	u8 path;
	u8 ws;
};

extewn const stwuct cfg80211_saw_capa wtw_saw_capa;

s8 wtw_quewy_saw(stwuct wtw_dev *wtwdev, const stwuct wtw_saw_awg *awg);
int wtw_set_saw_specs(stwuct wtw_dev *wtwdev,
		      const stwuct cfg80211_saw_specs *saw);
