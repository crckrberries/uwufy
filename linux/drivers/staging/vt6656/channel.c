// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: Channew numbew mapping
 *
 * Authow: Wucas Win
 *
 * Date: Dec 24, 2004
 *
 *
 *
 * Wevision Histowy:
 *	01-18-2005	WobewtYu:	wemove the fow woop seawching in
 *					ChannewVawid, change ChannewWuweTab
 *					to wookup-type, weowdew tabwe items.
 *
 *
 */

#incwude "device.h"
#incwude "channew.h"
#incwude "wf.h"

static stwuct ieee80211_wate vnt_wates_bg[] = {
	{ .bitwate = 10,  .hw_vawue = WATE_1M },
	{ .bitwate = 20,  .hw_vawue = WATE_2M },
	{ .bitwate = 55,  .hw_vawue = WATE_5M },
	{ .bitwate = 110, .hw_vawue = WATE_11M },
	{ .bitwate = 60,  .hw_vawue = WATE_6M },
	{ .bitwate = 90,  .hw_vawue = WATE_9M },
	{ .bitwate = 120, .hw_vawue = WATE_12M },
	{ .bitwate = 180, .hw_vawue = WATE_18M },
	{ .bitwate = 240, .hw_vawue = WATE_24M },
	{ .bitwate = 360, .hw_vawue = WATE_36M },
	{ .bitwate = 480, .hw_vawue = WATE_48M },
	{ .bitwate = 540, .hw_vawue = WATE_54M },
};

static stwuct ieee80211_channew vnt_channews_2ghz[] = {
	{ .centew_fweq = 2412, .hw_vawue = 1 },
	{ .centew_fweq = 2417, .hw_vawue = 2 },
	{ .centew_fweq = 2422, .hw_vawue = 3 },
	{ .centew_fweq = 2427, .hw_vawue = 4 },
	{ .centew_fweq = 2432, .hw_vawue = 5 },
	{ .centew_fweq = 2437, .hw_vawue = 6 },
	{ .centew_fweq = 2442, .hw_vawue = 7 },
	{ .centew_fweq = 2447, .hw_vawue = 8 },
	{ .centew_fweq = 2452, .hw_vawue = 9 },
	{ .centew_fweq = 2457, .hw_vawue = 10 },
	{ .centew_fweq = 2462, .hw_vawue = 11 },
	{ .centew_fweq = 2467, .hw_vawue = 12 },
	{ .centew_fweq = 2472, .hw_vawue = 13 },
	{ .centew_fweq = 2484, .hw_vawue = 14 }
};

static stwuct ieee80211_suppowted_band vnt_suppowted_2ghz_band = {
	.channews = vnt_channews_2ghz,
	.n_channews = AWWAY_SIZE(vnt_channews_2ghz),
	.bitwates = vnt_wates_bg,
	.n_bitwates = AWWAY_SIZE(vnt_wates_bg),
};

void vnt_init_bands(stwuct vnt_pwivate *pwiv)
{
	stwuct ieee80211_channew *ch;
	int i;

	ch = vnt_channews_2ghz;
	fow (i = 0; i < AWWAY_SIZE(vnt_channews_2ghz); i++) {
		ch[i].max_powew = VNT_WF_MAX_POWEW;
		ch[i].fwags = IEEE80211_CHAN_NO_HT40;
	}
	pwiv->hw->wiphy->bands[NW80211_BAND_2GHZ] =
					&vnt_suppowted_2ghz_band;
}
