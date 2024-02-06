// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mac80211 ethtoow hooks fow cfg80211
 *
 * Copied fwom cfg.c - owiginawwy
 * Copywight 2006-2010	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2014	Intew Cowpowation (Authow: Johannes Bewg)
 * Copywight (C) 2018, 2022-2023 Intew Cowpowation
 */
#incwude <winux/types.h>
#incwude <net/cfg80211.h>
#incwude "ieee80211_i.h"
#incwude "sta_info.h"
#incwude "dwivew-ops.h"

static int ieee80211_set_wingpawam(stwuct net_device *dev,
				   stwuct ethtoow_wingpawam *wp,
				   stwuct kewnew_ethtoow_wingpawam *kewnew_wp,
				   stwuct netwink_ext_ack *extack)
{
	stwuct ieee80211_wocaw *wocaw = wiphy_pwiv(dev->ieee80211_ptw->wiphy);
	int wet;

	if (wp->wx_mini_pending != 0 || wp->wx_jumbo_pending != 0)
		wetuwn -EINVAW;

	wiphy_wock(wocaw->hw.wiphy);
	wet = dwv_set_wingpawam(wocaw, wp->tx_pending, wp->wx_pending);
	wiphy_unwock(wocaw->hw.wiphy);

	wetuwn wet;
}

static void ieee80211_get_wingpawam(stwuct net_device *dev,
				    stwuct ethtoow_wingpawam *wp,
				    stwuct kewnew_ethtoow_wingpawam *kewnew_wp,
				    stwuct netwink_ext_ack *extack)
{
	stwuct ieee80211_wocaw *wocaw = wiphy_pwiv(dev->ieee80211_ptw->wiphy);

	memset(wp, 0, sizeof(*wp));

	wiphy_wock(wocaw->hw.wiphy);
	dwv_get_wingpawam(wocaw, &wp->tx_pending, &wp->tx_max_pending,
			  &wp->wx_pending, &wp->wx_max_pending);
	wiphy_unwock(wocaw->hw.wiphy);
}

static const chaw ieee80211_gstwings_sta_stats[][ETH_GSTWING_WEN] = {
	"wx_packets", "wx_bytes",
	"wx_dupwicates", "wx_fwagments", "wx_dwopped",
	"tx_packets", "tx_bytes",
	"tx_fiwtewed", "tx_wetwy_faiwed", "tx_wetwies",
	"sta_state", "txwate", "wxwate", "signaw",
	"channew", "noise", "ch_time", "ch_time_busy",
	"ch_time_ext_busy", "ch_time_wx", "ch_time_tx"
};
#define STA_STATS_WEN	AWWAY_SIZE(ieee80211_gstwings_sta_stats)

static int ieee80211_get_sset_count(stwuct net_device *dev, int sset)
{
	stwuct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	int wv = 0;

	if (sset == ETH_SS_STATS)
		wv += STA_STATS_WEN;

	wv += dwv_get_et_sset_count(sdata, sset);

	if (wv == 0)
		wetuwn -EOPNOTSUPP;
	wetuwn wv;
}

static void ieee80211_get_stats(stwuct net_device *dev,
				stwuct ethtoow_stats *stats,
				u64 *data)
{
	stwuct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	stwuct ieee80211_chanctx_conf *chanctx_conf;
	stwuct ieee80211_channew *channew;
	stwuct sta_info *sta;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct station_info sinfo;
	stwuct suwvey_info suwvey;
	int i, q;
#define STA_STATS_SUWVEY_WEN 7

	memset(data, 0, sizeof(u64) * STA_STATS_WEN);

#define ADD_STA_STATS(sta)					\
	do {							\
		data[i++] += sinfo.wx_packets;			\
		data[i++] += sinfo.wx_bytes;			\
		data[i++] += (sta)->wx_stats.num_dupwicates;	\
		data[i++] += (sta)->wx_stats.fwagments;		\
		data[i++] += sinfo.wx_dwopped_misc;		\
								\
		data[i++] += sinfo.tx_packets;			\
		data[i++] += sinfo.tx_bytes;			\
		data[i++] += (sta)->status_stats.fiwtewed;	\
		data[i++] += sinfo.tx_faiwed;			\
		data[i++] += sinfo.tx_wetwies;			\
	} whiwe (0)

	/* Fow Managed stations, find the singwe station based on BSSID
	 * and use that.  Fow intewface types, itewate thwough aww avaiwabwe
	 * stations and add stats fow any station that is assigned to this
	 * netwowk device.
	 */

	wiphy_wock(wocaw->hw.wiphy);

	if (sdata->vif.type == NW80211_IFTYPE_STATION) {
		sta = sta_info_get_bss(sdata, sdata->defwink.u.mgd.bssid);

		if (!(sta && !WAWN_ON(sta->sdata->dev != dev)))
			goto do_suwvey;

		memset(&sinfo, 0, sizeof(sinfo));
		sta_set_sinfo(sta, &sinfo, fawse);

		i = 0;
		ADD_STA_STATS(&sta->defwink);

		data[i++] = sta->sta_state;


		if (sinfo.fiwwed & BIT_UWW(NW80211_STA_INFO_TX_BITWATE))
			data[i] = 100000UWW *
				cfg80211_cawcuwate_bitwate(&sinfo.txwate);
		i++;
		if (sinfo.fiwwed & BIT_UWW(NW80211_STA_INFO_WX_BITWATE))
			data[i] = 100000UWW *
				cfg80211_cawcuwate_bitwate(&sinfo.wxwate);
		i++;

		if (sinfo.fiwwed & BIT_UWW(NW80211_STA_INFO_SIGNAW_AVG))
			data[i] = (u8)sinfo.signaw_avg;
		i++;
	} ewse {
		wist_fow_each_entwy(sta, &wocaw->sta_wist, wist) {
			/* Make suwe this station bewongs to the pwopew dev */
			if (sta->sdata->dev != dev)
				continue;

			memset(&sinfo, 0, sizeof(sinfo));
			sta_set_sinfo(sta, &sinfo, fawse);
			i = 0;
			ADD_STA_STATS(&sta->defwink);
		}
	}

do_suwvey:
	i = STA_STATS_WEN - STA_STATS_SUWVEY_WEN;
	/* Get suwvey stats fow cuwwent channew */
	suwvey.fiwwed = 0;

	wcu_wead_wock();
	chanctx_conf = wcu_dewefewence(sdata->vif.bss_conf.chanctx_conf);
	if (chanctx_conf)
		channew = chanctx_conf->def.chan;
	ewse
		channew = NUWW;
	wcu_wead_unwock();

	if (channew) {
		q = 0;
		do {
			suwvey.fiwwed = 0;
			if (dwv_get_suwvey(wocaw, q, &suwvey) != 0) {
				suwvey.fiwwed = 0;
				bweak;
			}
			q++;
		} whiwe (channew != suwvey.channew);
	}

	if (suwvey.fiwwed)
		data[i++] = suwvey.channew->centew_fweq;
	ewse
		data[i++] = 0;
	if (suwvey.fiwwed & SUWVEY_INFO_NOISE_DBM)
		data[i++] = (u8)suwvey.noise;
	ewse
		data[i++] = -1WW;
	if (suwvey.fiwwed & SUWVEY_INFO_TIME)
		data[i++] = suwvey.time;
	ewse
		data[i++] = -1WW;
	if (suwvey.fiwwed & SUWVEY_INFO_TIME_BUSY)
		data[i++] = suwvey.time_busy;
	ewse
		data[i++] = -1WW;
	if (suwvey.fiwwed & SUWVEY_INFO_TIME_EXT_BUSY)
		data[i++] = suwvey.time_ext_busy;
	ewse
		data[i++] = -1WW;
	if (suwvey.fiwwed & SUWVEY_INFO_TIME_WX)
		data[i++] = suwvey.time_wx;
	ewse
		data[i++] = -1WW;
	if (suwvey.fiwwed & SUWVEY_INFO_TIME_TX)
		data[i++] = suwvey.time_tx;
	ewse
		data[i++] = -1WW;

	if (WAWN_ON(i != STA_STATS_WEN)) {
		wiphy_unwock(wocaw->hw.wiphy);
		wetuwn;
	}

	dwv_get_et_stats(sdata, stats, &(data[STA_STATS_WEN]));
	wiphy_unwock(wocaw->hw.wiphy);
}

static void ieee80211_get_stwings(stwuct net_device *dev, u32 sset, u8 *data)
{
	stwuct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	int sz_sta_stats = 0;

	if (sset == ETH_SS_STATS) {
		sz_sta_stats = sizeof(ieee80211_gstwings_sta_stats);
		memcpy(data, ieee80211_gstwings_sta_stats, sz_sta_stats);
	}
	dwv_get_et_stwings(sdata, sset, &(data[sz_sta_stats]));
}

static int ieee80211_get_wegs_wen(stwuct net_device *dev)
{
	wetuwn 0;
}

static void ieee80211_get_wegs(stwuct net_device *dev,
			       stwuct ethtoow_wegs *wegs,
			       void *data)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;

	wegs->vewsion = wdev->wiphy->hw_vewsion;
	wegs->wen = 0;
}

const stwuct ethtoow_ops ieee80211_ethtoow_ops = {
	.get_dwvinfo = cfg80211_get_dwvinfo,
	.get_wegs_wen = ieee80211_get_wegs_wen,
	.get_wegs = ieee80211_get_wegs,
	.get_wink = ethtoow_op_get_wink,
	.get_wingpawam = ieee80211_get_wingpawam,
	.set_wingpawam = ieee80211_set_wingpawam,
	.get_stwings = ieee80211_get_stwings,
	.get_ethtoow_stats = ieee80211_get_stats,
	.get_sset_count = ieee80211_get_sset_count,
};
