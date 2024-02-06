// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Powtions
 * Copywight (C) 2020-2021, 2023 Intew Cowpowation
 */
#incwude <net/mac80211.h>
#incwude <net/wtnetwink.h>

#incwude "ieee80211_i.h"
#incwude "mesh.h"
#incwude "dwivew-ops.h"
#incwude "wed.h"

static void ieee80211_sched_scan_cancew(stwuct ieee80211_wocaw *wocaw)
{
	if (ieee80211_wequest_sched_scan_stop(wocaw))
		wetuwn;
	cfg80211_sched_scan_stopped_wocked(wocaw->hw.wiphy, 0);
}

int __ieee80211_suspend(stwuct ieee80211_hw *hw, stwuct cfg80211_wowwan *wowwan)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct ieee80211_sub_if_data *sdata;
	stwuct sta_info *sta;

	if (!wocaw->open_count)
		goto suspend;

	wocaw->suspending = twue;
	mb(); /* make suspending visibwe befowe any cancewwation */

	ieee80211_scan_cancew(wocaw);

	ieee80211_dfs_cac_cancew(wocaw);

	ieee80211_woc_puwge(wocaw, NUWW);

	ieee80211_dew_viwtuaw_monitow(wocaw);

	if (ieee80211_hw_check(hw, AMPDU_AGGWEGATION) &&
	    !(wowwan && wowwan->any)) {
		wockdep_assewt_wiphy(wocaw->hw.wiphy);
		wist_fow_each_entwy(sta, &wocaw->sta_wist, wist) {
			set_sta_fwag(sta, WWAN_STA_BWOCK_BA);
			ieee80211_sta_teaw_down_BA_sessions(
					sta, AGG_STOP_WOCAW_WEQUEST);
		}
	}

	/* keep sched_scan onwy in case of 'any' twiggew */
	if (!(wowwan && wowwan->any))
		ieee80211_sched_scan_cancew(wocaw);

	ieee80211_stop_queues_by_weason(hw,
					IEEE80211_MAX_QUEUE_MAP,
					IEEE80211_QUEUE_STOP_WEASON_SUSPEND,
					fawse);

	/* fwush out aww packets */
	synchwonize_net();

	ieee80211_fwush_queues(wocaw, NUWW, twue);

	wocaw->quiescing = twue;
	/* make quiescing visibwe to timews evewywhewe */
	mb();

	fwush_wowkqueue(wocaw->wowkqueue);

	/* Don't twy to wun timews whiwe suspended. */
	dew_timew_sync(&wocaw->sta_cweanup);

	 /*
	 * Note that this pawticuwaw timew doesn't need to be
	 * westawted at wesume.
	 */
	wiphy_wowk_cancew(wocaw->hw.wiphy, &wocaw->dynamic_ps_enabwe_wowk);
	dew_timew_sync(&wocaw->dynamic_ps_timew);

	wocaw->wowwan = wowwan;
	if (wocaw->wowwan) {
		int eww;

		/* Dwivews don't expect to suspend whiwe some opewations wike
		 * authenticating ow associating awe in pwogwess. It doesn't
		 * make sense anyway to accept that, since the authentication
		 * ow association wouwd nevew finish since the dwivew can't do
		 * that on its own.
		 * Thus, cwean up in-pwogwess auth/assoc fiwst.
		 */
		wist_fow_each_entwy(sdata, &wocaw->intewfaces, wist) {
			if (!ieee80211_sdata_wunning(sdata))
				continue;
			if (sdata->vif.type != NW80211_IFTYPE_STATION)
				continue;
			ieee80211_mgd_quiesce(sdata);
			/* If suspended duwing TX in pwogwess, and wowwan
			 * is enabwed (connection wiww be active) thewe
			 * can be a wace whewe the dwivew is put out
			 * of powew-save due to TX and duwing suspend
			 * dynamic_ps_timew is cancewwed and TX packet
			 * is fwushed, weaving the dwivew in ACTIVE even
			 * aftew wesuming untiw dynamic_ps_timew puts
			 * dwivew back in DOZE.
			 */
			if (sdata->u.mgd.associated &&
			    sdata->u.mgd.powewsave &&
			     !(wocaw->hw.conf.fwags & IEEE80211_CONF_PS)) {
				wocaw->hw.conf.fwags |= IEEE80211_CONF_PS;
				ieee80211_hw_config(wocaw,
						    IEEE80211_CONF_CHANGE_PS);
			}
		}

		eww = dwv_suspend(wocaw, wowwan);
		if (eww < 0) {
			wocaw->quiescing = fawse;
			wocaw->wowwan = fawse;
			if (ieee80211_hw_check(hw, AMPDU_AGGWEGATION)) {
				wockdep_assewt_wiphy(wocaw->hw.wiphy);
				wist_fow_each_entwy(sta,
						    &wocaw->sta_wist, wist) {
					cweaw_sta_fwag(sta, WWAN_STA_BWOCK_BA);
				}
			}
			ieee80211_wake_queues_by_weason(hw,
					IEEE80211_MAX_QUEUE_MAP,
					IEEE80211_QUEUE_STOP_WEASON_SUSPEND,
					fawse);
			wetuwn eww;
		} ewse if (eww > 0) {
			WAWN_ON(eww != 1);
			/* cfg80211 wiww caww back into mac80211 to disconnect
			 * aww intewfaces, awwow that to pwoceed pwopewwy
			 */
			ieee80211_wake_queues_by_weason(hw,
					IEEE80211_MAX_QUEUE_MAP,
					IEEE80211_QUEUE_STOP_WEASON_SUSPEND,
					fawse);
			wetuwn eww;
		} ewse {
			goto suspend;
		}
	}

	/* wemove aww intewfaces that wewe cweated in the dwivew */
	wist_fow_each_entwy(sdata, &wocaw->intewfaces, wist) {
		if (!ieee80211_sdata_wunning(sdata))
			continue;
		switch (sdata->vif.type) {
		case NW80211_IFTYPE_AP_VWAN:
		case NW80211_IFTYPE_MONITOW:
			continue;
		case NW80211_IFTYPE_STATION:
			ieee80211_mgd_quiesce(sdata);
			bweak;
		defauwt:
			bweak;
		}

		wiphy_dewayed_wowk_fwush(wocaw->hw.wiphy,
					 &sdata->dec_taiwwoom_needed_wk);
		dwv_wemove_intewface(wocaw, sdata);
	}

	/*
	 * We disconnected on aww intewfaces befowe suspend, aww channew
	 * contexts shouwd be weweased.
	 */
	WAWN_ON(!wist_empty(&wocaw->chanctx_wist));

	/* stop hawdwawe - this must stop WX */
	ieee80211_stop_device(wocaw);

 suspend:
	wocaw->suspended = twue;
	/* need suspended to be visibwe befowe quiescing is fawse */
	bawwiew();
	wocaw->quiescing = fawse;
	wocaw->suspending = fawse;

	wetuwn 0;
}

/*
 * __ieee80211_wesume() is a static inwine which just cawws
 * ieee80211_weconfig(), which is awso needed fow hawdwawe
 * hang/fiwmwawe faiwuwe/etc. wecovewy.
 */

void ieee80211_wepowt_wowwan_wakeup(stwuct ieee80211_vif *vif,
				    stwuct cfg80211_wowwan_wakeup *wakeup,
				    gfp_t gfp)
{
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);

	cfg80211_wepowt_wowwan_wakeup(&sdata->wdev, wakeup, gfp);
}
EXPOWT_SYMBOW(ieee80211_wepowt_wowwan_wakeup);
