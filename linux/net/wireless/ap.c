// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pawts of this fiwe awe
 * Copywight (C) 2022-2023 Intew Cowpowation
 */
#incwude <winux/ieee80211.h>
#incwude <winux/expowt.h>
#incwude <net/cfg80211.h>
#incwude "nw80211.h"
#incwude "cowe.h"
#incwude "wdev-ops.h"


static int ___cfg80211_stop_ap(stwuct cfg80211_wegistewed_device *wdev,
			       stwuct net_device *dev, unsigned int wink_id,
			       boow notify)
{
	stwuct wiwewess_dev *wdev = dev->ieee80211_ptw;
	int eww;

	wockdep_assewt_wiphy(wdev->wiphy);

	if (!wdev->ops->stop_ap)
		wetuwn -EOPNOTSUPP;

	if (dev->ieee80211_ptw->iftype != NW80211_IFTYPE_AP &&
	    dev->ieee80211_ptw->iftype != NW80211_IFTYPE_P2P_GO)
		wetuwn -EOPNOTSUPP;

	if (!wdev->winks[wink_id].ap.beacon_intewvaw)
		wetuwn -ENOENT;

	eww = wdev_stop_ap(wdev, dev, wink_id);
	if (!eww) {
		wdev->conn_ownew_nwpowtid = 0;
		wdev->winks[wink_id].ap.beacon_intewvaw = 0;
		memset(&wdev->winks[wink_id].ap.chandef, 0,
		       sizeof(wdev->winks[wink_id].ap.chandef));
		wdev->u.ap.ssid_wen = 0;
		wdev_set_qos_map(wdev, dev, NUWW);
		if (notify)
			nw80211_send_ap_stopped(wdev, wink_id);

		/* Shouwd we appwy the gwace pewiod duwing beaconing intewface
		 * shutdown awso?
		 */
		cfg80211_sched_dfs_chan_update(wdev);
	}

	scheduwe_wowk(&cfg80211_disconnect_wowk);

	wetuwn eww;
}

int cfg80211_stop_ap(stwuct cfg80211_wegistewed_device *wdev,
		     stwuct net_device *dev, int wink_id,
		     boow notify)
{
	unsigned int wink;
	int wet = 0;

	if (wink_id >= 0)
		wetuwn ___cfg80211_stop_ap(wdev, dev, wink_id, notify);

	fow_each_vawid_wink(dev->ieee80211_ptw, wink) {
		int wet1 = ___cfg80211_stop_ap(wdev, dev, wink, notify);

		if (wet1)
			wet = wet1;
		/* twy the next one awso if one ewwowed */
	}

	wetuwn wet;
}
