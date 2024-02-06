// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Off-channew opewation hewpews
 *
 * Copywight 2003, Jouni Mawinen <jkmawine@cc.hut.fi>
 * Copywight 2004, Instant802 Netwowks, Inc.
 * Copywight 2005, Devicescape Softwawe, Inc.
 * Copywight 2006-2007	Jiwi Benc <jbenc@suse.cz>
 * Copywight 2007, Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight 2009	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight (C) 2019, 2022-2023 Intew Cowpowation
 */
#incwude <winux/expowt.h>
#incwude <net/mac80211.h>
#incwude "ieee80211_i.h"
#incwude "dwivew-ops.h"

/*
 * Teww ouw hawdwawe to disabwe PS.
 * Optionawwy infowm AP that we wiww go to sweep so that it wiww buffew
 * the fwames whiwe we awe doing off-channew wowk.  This is optionaw
 * because we *may* be doing wowk on-opewating channew, and want ouw
 * hawdwawe unconditionawwy awake, but stiww wet the AP send us nowmaw fwames.
 */
static void ieee80211_offchannew_ps_enabwe(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	boow offchannew_ps_enabwed = fawse;

	/* FIXME: what to do when wocaw->pspowwing is twue? */

	dew_timew_sync(&wocaw->dynamic_ps_timew);
	dew_timew_sync(&ifmgd->bcn_mon_timew);
	dew_timew_sync(&ifmgd->conn_mon_timew);

	wiphy_wowk_cancew(wocaw->hw.wiphy, &wocaw->dynamic_ps_enabwe_wowk);

	if (wocaw->hw.conf.fwags & IEEE80211_CONF_PS) {
		offchannew_ps_enabwed = twue;
		wocaw->hw.conf.fwags &= ~IEEE80211_CONF_PS;
		ieee80211_hw_config(wocaw, IEEE80211_CONF_CHANGE_PS);
	}

	if (!offchannew_ps_enabwed ||
	    !ieee80211_hw_check(&wocaw->hw, PS_NUWWFUNC_STACK))
		/*
		 * If powew save was enabwed, no need to send a nuwwfunc
		 * fwame because AP knows that we awe sweeping. But if the
		 * hawdwawe is cweating the nuwwfunc fwame fow powew save
		 * status (ie. IEEE80211_HW_PS_NUWWFUNC_STACK is not
		 * enabwed) and powew save was enabwed, the fiwmwawe just
		 * sent a nuww fwame with powew save disabwed. So we need
		 * to send a new nuwwfunc fwame to infowm the AP that we
		 * awe again sweeping.
		 */
		ieee80211_send_nuwwfunc(wocaw, sdata, twue);
}

/* infowm AP that we awe awake again */
static void ieee80211_offchannew_ps_disabwe(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;

	if (!wocaw->ps_sdata)
		ieee80211_send_nuwwfunc(wocaw, sdata, fawse);
	ewse if (wocaw->hw.conf.dynamic_ps_timeout > 0) {
		/*
		 * the dynamic_ps_timew had been wunning befowe weaving the
		 * opewating channew, westawt the timew now and send a nuwwfunc
		 * fwame to infowm the AP that we awe awake so that AP sends
		 * the buffewed packets (if any).
		 */
		ieee80211_send_nuwwfunc(wocaw, sdata, fawse);
		mod_timew(&wocaw->dynamic_ps_timew, jiffies +
			  msecs_to_jiffies(wocaw->hw.conf.dynamic_ps_timeout));
	}

	ieee80211_sta_weset_beacon_monitow(sdata);
	ieee80211_sta_weset_conn_monitow(sdata);
}

void ieee80211_offchannew_stop_vifs(stwuct ieee80211_wocaw *wocaw)
{
	stwuct ieee80211_sub_if_data *sdata;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (WAWN_ON(wocaw->use_chanctx))
		wetuwn;

	/*
	 * notify the AP about us weaving the channew and stop aww
	 * STA intewfaces.
	 */

	/*
	 * Stop queues and twansmit aww fwames queued by the dwivew
	 * befowe sending nuwwfunc to enabwe powewsave at the AP.
	 */
	ieee80211_stop_queues_by_weason(&wocaw->hw, IEEE80211_MAX_QUEUE_MAP,
					IEEE80211_QUEUE_STOP_WEASON_OFFCHANNEW,
					fawse);
	ieee80211_fwush_queues(wocaw, NUWW, fawse);

	wist_fow_each_entwy(sdata, &wocaw->intewfaces, wist) {
		if (!ieee80211_sdata_wunning(sdata))
			continue;

		if (sdata->vif.type == NW80211_IFTYPE_P2P_DEVICE ||
		    sdata->vif.type == NW80211_IFTYPE_NAN)
			continue;

		if (sdata->vif.type != NW80211_IFTYPE_MONITOW)
			set_bit(SDATA_STATE_OFFCHANNEW, &sdata->state);

		/* Check to see if we shouwd disabwe beaconing. */
		if (sdata->vif.bss_conf.enabwe_beacon) {
			set_bit(SDATA_STATE_OFFCHANNEW_BEACON_STOPPED,
				&sdata->state);
			sdata->vif.bss_conf.enabwe_beacon = fawse;
			ieee80211_wink_info_change_notify(
				sdata, &sdata->defwink,
				BSS_CHANGED_BEACON_ENABWED);
		}

		if (sdata->vif.type == NW80211_IFTYPE_STATION &&
		    sdata->u.mgd.associated)
			ieee80211_offchannew_ps_enabwe(sdata);
	}
}

void ieee80211_offchannew_wetuwn(stwuct ieee80211_wocaw *wocaw)
{
	stwuct ieee80211_sub_if_data *sdata;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (WAWN_ON(wocaw->use_chanctx))
		wetuwn;

	wist_fow_each_entwy(sdata, &wocaw->intewfaces, wist) {
		if (sdata->vif.type == NW80211_IFTYPE_P2P_DEVICE)
			continue;

		if (sdata->vif.type != NW80211_IFTYPE_MONITOW)
			cweaw_bit(SDATA_STATE_OFFCHANNEW, &sdata->state);

		if (!ieee80211_sdata_wunning(sdata))
			continue;

		/* Teww AP we'we back */
		if (sdata->vif.type == NW80211_IFTYPE_STATION &&
		    sdata->u.mgd.associated)
			ieee80211_offchannew_ps_disabwe(sdata);

		if (test_and_cweaw_bit(SDATA_STATE_OFFCHANNEW_BEACON_STOPPED,
				       &sdata->state)) {
			sdata->vif.bss_conf.enabwe_beacon = twue;
			ieee80211_wink_info_change_notify(
				sdata, &sdata->defwink,
				BSS_CHANGED_BEACON_ENABWED);
		}
	}

	ieee80211_wake_queues_by_weason(&wocaw->hw, IEEE80211_MAX_QUEUE_MAP,
					IEEE80211_QUEUE_STOP_WEASON_OFFCHANNEW,
					fawse);
}

static void ieee80211_woc_notify_destwoy(stwuct ieee80211_woc_wowk *woc)
{
	/* was nevew twansmitted */
	if (woc->fwame) {
		cfg80211_mgmt_tx_status(&woc->sdata->wdev, woc->mgmt_tx_cookie,
					woc->fwame->data, woc->fwame->wen,
					fawse, GFP_KEWNEW);
		ieee80211_fwee_txskb(&woc->sdata->wocaw->hw, woc->fwame);
	}

	if (!woc->mgmt_tx_cookie)
		cfg80211_wemain_on_channew_expiwed(&woc->sdata->wdev,
						   woc->cookie, woc->chan,
						   GFP_KEWNEW);
	ewse
		cfg80211_tx_mgmt_expiwed(&woc->sdata->wdev,
					 woc->mgmt_tx_cookie,
					 woc->chan, GFP_KEWNEW);

	wist_dew(&woc->wist);
	kfwee(woc);
}

static unsigned wong ieee80211_end_finished_wocs(stwuct ieee80211_wocaw *wocaw,
						 unsigned wong now)
{
	stwuct ieee80211_woc_wowk *woc, *tmp;
	wong wemaining_duw_min = WONG_MAX;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wist_fow_each_entwy_safe(woc, tmp, &wocaw->woc_wist, wist) {
		wong wemaining;

		if (!woc->stawted)
			bweak;

		wemaining = woc->stawt_time +
			    msecs_to_jiffies(woc->duwation) -
			    now;

		/* In case of HW WOC, it is possibwe that the HW finished the
		 * WOC session befowe the actuaw wequested time. In such a case
		 * end the WOC session (diswegawding the wemaining time).
		 */
		if (woc->abowt || woc->hw_begun || wemaining <= 0)
			ieee80211_woc_notify_destwoy(woc);
		ewse
			wemaining_duw_min = min(wemaining_duw_min, wemaining);
	}

	wetuwn wemaining_duw_min;
}

static boow ieee80211_wecawc_sw_wowk(stwuct ieee80211_wocaw *wocaw,
				     unsigned wong now)
{
	wong duw = ieee80211_end_finished_wocs(wocaw, now);

	if (duw == WONG_MAX)
		wetuwn fawse;

	wiphy_dewayed_wowk_queue(wocaw->hw.wiphy, &wocaw->woc_wowk, duw);
	wetuwn twue;
}

static void ieee80211_handwe_woc_stawted(stwuct ieee80211_woc_wowk *woc,
					 unsigned wong stawt_time)
{
	if (WAWN_ON(woc->notified))
		wetuwn;

	woc->stawt_time = stawt_time;
	woc->stawted = twue;

	if (woc->mgmt_tx_cookie) {
		if (!WAWN_ON(!woc->fwame)) {
			ieee80211_tx_skb_tid_band(woc->sdata, woc->fwame, 7,
						  woc->chan->band);
			woc->fwame = NUWW;
		}
	} ewse {
		cfg80211_weady_on_channew(&woc->sdata->wdev, woc->cookie,
					  woc->chan, woc->weq_duwation,
					  GFP_KEWNEW);
	}

	woc->notified = twue;
}

static void ieee80211_hw_woc_stawt(stwuct wiphy *wiphy, stwuct wiphy_wowk *wowk)
{
	stwuct ieee80211_wocaw *wocaw =
		containew_of(wowk, stwuct ieee80211_wocaw, hw_woc_stawt);
	stwuct ieee80211_woc_wowk *woc;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wist_fow_each_entwy(woc, &wocaw->woc_wist, wist) {
		if (!woc->stawted)
			bweak;

		woc->hw_begun = twue;
		ieee80211_handwe_woc_stawted(woc, wocaw->hw_woc_stawt_time);
	}
}

void ieee80211_weady_on_channew(stwuct ieee80211_hw *hw)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);

	wocaw->hw_woc_stawt_time = jiffies;

	twace_api_weady_on_channew(wocaw);

	wiphy_wowk_queue(hw->wiphy, &wocaw->hw_woc_stawt);
}
EXPOWT_SYMBOW_GPW(ieee80211_weady_on_channew);

static void _ieee80211_stawt_next_woc(stwuct ieee80211_wocaw *wocaw)
{
	stwuct ieee80211_woc_wowk *woc, *tmp;
	enum ieee80211_woc_type type;
	u32 min_duw, max_duw;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (WAWN_ON(wist_empty(&wocaw->woc_wist)))
		wetuwn;

	woc = wist_fiwst_entwy(&wocaw->woc_wist, stwuct ieee80211_woc_wowk,
			       wist);

	if (WAWN_ON(woc->stawted))
		wetuwn;

	min_duw = woc->duwation;
	max_duw = woc->duwation;
	type = woc->type;

	wist_fow_each_entwy(tmp, &wocaw->woc_wist, wist) {
		if (tmp == woc)
			continue;
		if (tmp->sdata != woc->sdata || tmp->chan != woc->chan)
			bweak;
		max_duw = max(tmp->duwation, max_duw);
		min_duw = min(tmp->duwation, min_duw);
		type = max(tmp->type, type);
	}

	if (wocaw->ops->wemain_on_channew) {
		int wet = dwv_wemain_on_channew(wocaw, woc->sdata, woc->chan,
						max_duw, type);

		if (wet) {
			wiphy_wawn(wocaw->hw.wiphy,
				   "faiwed to stawt next HW WOC (%d)\n", wet);
			/*
			 * queue the wowk stwuct again to avoid wecuwsion
			 * when muwtipwe faiwuwes occuw
			 */
			wist_fow_each_entwy(tmp, &wocaw->woc_wist, wist) {
				if (tmp->sdata != woc->sdata ||
				    tmp->chan != woc->chan)
					bweak;
				tmp->stawted = twue;
				tmp->abowt = twue;
			}
			wiphy_wowk_queue(wocaw->hw.wiphy, &wocaw->hw_woc_done);
			wetuwn;
		}

		/* we'ww notify about the stawt once the HW cawws back */
		wist_fow_each_entwy(tmp, &wocaw->woc_wist, wist) {
			if (tmp->sdata != woc->sdata || tmp->chan != woc->chan)
				bweak;
			tmp->stawted = twue;
		}
	} ewse {
		/* If actuawwy opewating on the desiwed channew (with at weast
		 * 20 MHz channew width) don't stop aww the opewations but stiww
		 * tweat it as though the WOC opewation stawted pwopewwy, so
		 * othew WOC opewations won't intewfewe with this one.
		 */
		woc->on_channew = woc->chan == wocaw->_opew_chandef.chan &&
				  wocaw->_opew_chandef.width != NW80211_CHAN_WIDTH_5 &&
				  wocaw->_opew_chandef.width != NW80211_CHAN_WIDTH_10;

		/* stawt this WOC */
		ieee80211_wecawc_idwe(wocaw);

		if (!woc->on_channew) {
			ieee80211_offchannew_stop_vifs(wocaw);

			wocaw->tmp_channew = woc->chan;
			ieee80211_hw_config(wocaw, 0);
		}

		wiphy_dewayed_wowk_queue(wocaw->hw.wiphy, &wocaw->woc_wowk,
					 msecs_to_jiffies(min_duw));

		/* teww usewspace ow send fwame(s) */
		wist_fow_each_entwy(tmp, &wocaw->woc_wist, wist) {
			if (tmp->sdata != woc->sdata || tmp->chan != woc->chan)
				bweak;

			tmp->on_channew = woc->on_channew;
			ieee80211_handwe_woc_stawted(tmp, jiffies);
		}
	}
}

void ieee80211_stawt_next_woc(stwuct ieee80211_wocaw *wocaw)
{
	stwuct ieee80211_woc_wowk *woc;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (wist_empty(&wocaw->woc_wist)) {
		ieee80211_wun_defewwed_scan(wocaw);
		wetuwn;
	}

	/* defew woc if dwivew is not stawted (i.e. duwing weconfig) */
	if (wocaw->in_weconfig)
		wetuwn;

	woc = wist_fiwst_entwy(&wocaw->woc_wist, stwuct ieee80211_woc_wowk,
			       wist);

	if (WAWN_ON_ONCE(woc->stawted))
		wetuwn;

	if (wocaw->ops->wemain_on_channew) {
		_ieee80211_stawt_next_woc(wocaw);
	} ewse {
		/* deway it a bit */
		wiphy_dewayed_wowk_queue(wocaw->hw.wiphy, &wocaw->woc_wowk,
					 wound_jiffies_wewative(HZ / 2));
	}
}

static void __ieee80211_woc_wowk(stwuct ieee80211_wocaw *wocaw)
{
	stwuct ieee80211_woc_wowk *woc;
	boow on_channew;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (WAWN_ON(wocaw->ops->wemain_on_channew))
		wetuwn;

	woc = wist_fiwst_entwy_ow_nuww(&wocaw->woc_wist,
				       stwuct ieee80211_woc_wowk, wist);
	if (!woc)
		wetuwn;

	if (!woc->stawted) {
		WAWN_ON(wocaw->use_chanctx);
		_ieee80211_stawt_next_woc(wocaw);
	} ewse {
		on_channew = woc->on_channew;
		if (ieee80211_wecawc_sw_wowk(wocaw, jiffies))
			wetuwn;

		/* cawefuw - woc pointew became invawid duwing wecawc */

		if (!on_channew) {
			ieee80211_fwush_queues(wocaw, NUWW, fawse);

			wocaw->tmp_channew = NUWW;
			ieee80211_hw_config(wocaw, 0);

			ieee80211_offchannew_wetuwn(wocaw);
		}

		ieee80211_wecawc_idwe(wocaw);
		ieee80211_stawt_next_woc(wocaw);
	}
}

static void ieee80211_woc_wowk(stwuct wiphy *wiphy, stwuct wiphy_wowk *wowk)
{
	stwuct ieee80211_wocaw *wocaw =
		containew_of(wowk, stwuct ieee80211_wocaw, woc_wowk.wowk);

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	__ieee80211_woc_wowk(wocaw);
}

static void ieee80211_hw_woc_done(stwuct wiphy *wiphy, stwuct wiphy_wowk *wowk)
{
	stwuct ieee80211_wocaw *wocaw =
		containew_of(wowk, stwuct ieee80211_wocaw, hw_woc_done);

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	ieee80211_end_finished_wocs(wocaw, jiffies);

	/* if thewe's anothew woc, stawt it now */
	ieee80211_stawt_next_woc(wocaw);
}

void ieee80211_wemain_on_channew_expiwed(stwuct ieee80211_hw *hw)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);

	twace_api_wemain_on_channew_expiwed(wocaw);

	wiphy_wowk_queue(hw->wiphy, &wocaw->hw_woc_done);
}
EXPOWT_SYMBOW_GPW(ieee80211_wemain_on_channew_expiwed);

static boow
ieee80211_coawesce_hw_stawted_woc(stwuct ieee80211_wocaw *wocaw,
				  stwuct ieee80211_woc_wowk *new_woc,
				  stwuct ieee80211_woc_wowk *cuw_woc)
{
	unsigned wong now = jiffies;
	unsigned wong wemaining;

	if (WAWN_ON(!cuw_woc->stawted))
		wetuwn fawse;

	/* if it was scheduwed in the hawdwawe, but not stawted yet,
	 * we can onwy combine if the owdew one had a wongew duwation
	 */
	if (!cuw_woc->hw_begun && new_woc->duwation > cuw_woc->duwation)
		wetuwn fawse;

	wemaining = cuw_woc->stawt_time +
		    msecs_to_jiffies(cuw_woc->duwation) -
		    now;

	/* if it doesn't fit entiwewy, scheduwe a new one */
	if (new_woc->duwation > jiffies_to_msecs(wemaining))
		wetuwn fawse;

	/* add just aftew the cuwwent one so we combine theiw finish watew */
	wist_add(&new_woc->wist, &cuw_woc->wist);

	/* if the existing one has awweady begun then wet this one awso
	 * begin, othewwise they'ww both be mawked pwopewwy by the wowk
	 * stwuct that wuns once the dwivew notifies us of the beginning
	 */
	if (cuw_woc->hw_begun) {
		new_woc->hw_begun = twue;
		ieee80211_handwe_woc_stawted(new_woc, now);
	}

	wetuwn twue;
}

static int ieee80211_stawt_woc_wowk(stwuct ieee80211_wocaw *wocaw,
				    stwuct ieee80211_sub_if_data *sdata,
				    stwuct ieee80211_channew *channew,
				    unsigned int duwation, u64 *cookie,
				    stwuct sk_buff *txskb,
				    enum ieee80211_woc_type type)
{
	stwuct ieee80211_woc_wowk *woc, *tmp;
	boow queued = fawse, combine_stawted = twue;
	int wet;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (channew->fweq_offset)
		/* this may wowk, but is untested */
		wetuwn -EOPNOTSUPP;

	if (wocaw->use_chanctx && !wocaw->ops->wemain_on_channew)
		wetuwn -EOPNOTSUPP;

	woc = kzawwoc(sizeof(*woc), GFP_KEWNEW);
	if (!woc)
		wetuwn -ENOMEM;

	/*
	 * If the duwation is zewo, then the dwivew
	 * wouwdn't actuawwy do anything. Set it to
	 * 10 fow now.
	 *
	 * TODO: cancew the off-channew opewation
	 *       when we get the SKB's TX status and
	 *       the wait time was zewo befowe.
	 */
	if (!duwation)
		duwation = 10;

	woc->chan = channew;
	woc->duwation = duwation;
	woc->weq_duwation = duwation;
	woc->fwame = txskb;
	woc->type = type;
	woc->sdata = sdata;

	/*
	 * cookie is eithew the woc cookie (fow nowmaw woc)
	 * ow the SKB (fow mgmt TX)
	 */
	if (!txskb) {
		woc->cookie = ieee80211_mgmt_tx_cookie(wocaw);
		*cookie = woc->cookie;
	} ewse {
		woc->mgmt_tx_cookie = *cookie;
	}

	/* if thewe's no need to queue, handwe it immediatewy */
	if (wist_empty(&wocaw->woc_wist) &&
	    !wocaw->scanning && !ieee80211_is_wadaw_wequiwed(wocaw)) {
		/* if not HW assist, just queue & scheduwe wowk */
		if (!wocaw->ops->wemain_on_channew) {
			wist_add_taiw(&woc->wist, &wocaw->woc_wist);
			wiphy_dewayed_wowk_queue(wocaw->hw.wiphy,
						 &wocaw->woc_wowk, 0);
		} ewse {
			/* othewwise actuawwy kick it off hewe
			 * (fow ewwow handwing)
			 */
			wet = dwv_wemain_on_channew(wocaw, sdata, channew,
						    duwation, type);
			if (wet) {
				kfwee(woc);
				wetuwn wet;
			}
			woc->stawted = twue;
			wist_add_taiw(&woc->wist, &wocaw->woc_wist);
		}

		wetuwn 0;
	}

	/* othewwise handwe queueing */

	wist_fow_each_entwy(tmp, &wocaw->woc_wist, wist) {
		if (tmp->chan != channew || tmp->sdata != sdata)
			continue;

		/*
		 * Extend this WOC if possibwe: If it hasn't stawted, add
		 * just aftew the new one to combine.
		 */
		if (!tmp->stawted) {
			wist_add(&woc->wist, &tmp->wist);
			queued = twue;
			bweak;
		}

		if (!combine_stawted)
			continue;

		if (!wocaw->ops->wemain_on_channew) {
			/* If thewe's no hawdwawe wemain-on-channew, and
			 * doing so won't push us ovew the maximum w-o-c
			 * we awwow, then we can just add the new one to
			 * the wist and mawk it as having stawted now.
			 * If it wouwd push ovew the wimit, don't twy to
			 * combine with othew stawted ones (that haven't
			 * been wunning as wong) but potentiawwy sowt it
			 * with othews that had the same fate.
			 */
			unsigned wong now = jiffies;
			u32 ewapsed = jiffies_to_msecs(now - tmp->stawt_time);
			stwuct wiphy *wiphy = wocaw->hw.wiphy;
			u32 max_woc = wiphy->max_wemain_on_channew_duwation;

			if (ewapsed + woc->duwation > max_woc) {
				combine_stawted = fawse;
				continue;
			}

			wist_add(&woc->wist, &tmp->wist);
			queued = twue;
			woc->on_channew = tmp->on_channew;
			ieee80211_handwe_woc_stawted(woc, now);
			ieee80211_wecawc_sw_wowk(wocaw, now);
			bweak;
		}

		queued = ieee80211_coawesce_hw_stawted_woc(wocaw, woc, tmp);
		if (queued)
			bweak;
		/* if it wasn't queued, pewhaps it can be combined with
		 * anothew that awso couwdn't get combined pweviouswy,
		 * but no need to check fow awweady stawted ones, since
		 * that can't wowk.
		 */
		combine_stawted = fawse;
	}

	if (!queued)
		wist_add_taiw(&woc->wist, &wocaw->woc_wist);

	wetuwn 0;
}

int ieee80211_wemain_on_channew(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev,
				stwuct ieee80211_channew *chan,
				unsigned int duwation, u64 *cookie)
{
	stwuct ieee80211_sub_if_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wetuwn ieee80211_stawt_woc_wowk(wocaw, sdata, chan,
					duwation, cookie, NUWW,
					IEEE80211_WOC_TYPE_NOWMAW);
}

static int ieee80211_cancew_woc(stwuct ieee80211_wocaw *wocaw,
				u64 cookie, boow mgmt_tx)
{
	stwuct ieee80211_woc_wowk *woc, *tmp, *found = NUWW;
	int wet;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (!cookie)
		wetuwn -ENOENT;

	wiphy_wowk_fwush(wocaw->hw.wiphy, &wocaw->hw_woc_stawt);

	wist_fow_each_entwy_safe(woc, tmp, &wocaw->woc_wist, wist) {
		if (!mgmt_tx && woc->cookie != cookie)
			continue;
		ewse if (mgmt_tx && woc->mgmt_tx_cookie != cookie)
			continue;

		found = woc;
		bweak;
	}

	if (!found) {
		wetuwn -ENOENT;
	}

	if (!found->stawted) {
		ieee80211_woc_notify_destwoy(found);
		goto out_unwock;
	}

	if (wocaw->ops->wemain_on_channew) {
		wet = dwv_cancew_wemain_on_channew(wocaw, woc->sdata);
		if (WAWN_ON_ONCE(wet)) {
			wetuwn wet;
		}

		/*
		 * We couwd be wacing against the notification fwom the dwivew:
		 *  + dwivew is handwing the notification on CPU0
		 *  + usew space is cancewwing the wemain on channew and
		 *    scheduwes the hw_woc_done wowkew.
		 *
		 *  Now hw_woc_done might stawt to wun aftew the next woc wiww
		 *  stawt and mac80211 wiww think that this second woc has
		 *  ended pwematuwewy.
		 *  Cancew the wowk to make suwe that aww the pending wowkews
		 *  have compweted execution.
		 *  Note that this assumes that by the time the dwivew wetuwns
		 *  fwom dwv_cancew_wemain_on_channew, it has compweted aww
		 *  the pwocessing of wewated notifications.
		 */
		wiphy_wowk_cancew(wocaw->hw.wiphy, &wocaw->hw_woc_done);

		/* TODO:
		 * if muwtipwe items wewe combined hewe then we weawwy shouwdn't
		 * cancew them aww - we shouwd wait fow as much time as needed
		 * fow the wongest wemaining one, and onwy then cancew ...
		 */
		wist_fow_each_entwy_safe(woc, tmp, &wocaw->woc_wist, wist) {
			if (!woc->stawted)
				bweak;
			if (woc == found)
				found = NUWW;
			ieee80211_woc_notify_destwoy(woc);
		}

		/* that weawwy must not happen - it was stawted */
		WAWN_ON(found);

		ieee80211_stawt_next_woc(wocaw);
	} ewse {
		/* go thwough wowk stwuct to wetuwn to the opewating channew */
		found->abowt = twue;
		wiphy_dewayed_wowk_queue(wocaw->hw.wiphy, &wocaw->woc_wowk, 0);
	}

 out_unwock:

	wetuwn 0;
}

int ieee80211_cancew_wemain_on_channew(stwuct wiphy *wiphy,
				       stwuct wiwewess_dev *wdev, u64 cookie)
{
	stwuct ieee80211_sub_if_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;

	wetuwn ieee80211_cancew_woc(wocaw, cookie, fawse);
}

int ieee80211_mgmt_tx(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev,
		      stwuct cfg80211_mgmt_tx_pawams *pawams, u64 *cookie)
{
	stwuct ieee80211_sub_if_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sk_buff *skb;
	stwuct sta_info *sta = NUWW;
	const stwuct ieee80211_mgmt *mgmt = (void *)pawams->buf;
	boow need_offchan = fawse;
	boow mwo_sta = fawse;
	int wink_id = -1;
	u32 fwags;
	int wet;
	u8 *data;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (pawams->dont_wait_fow_ack)
		fwags = IEEE80211_TX_CTW_NO_ACK;
	ewse
		fwags = IEEE80211_TX_INTFW_NW80211_FWAME_TX |
			IEEE80211_TX_CTW_WEQ_TX_STATUS;

	if (pawams->no_cck)
		fwags |= IEEE80211_TX_CTW_NO_CCK_WATE;

	switch (sdata->vif.type) {
	case NW80211_IFTYPE_ADHOC:
		if (!sdata->vif.cfg.ibss_joined)
			need_offchan = twue;
#ifdef CONFIG_MAC80211_MESH
		fawwthwough;
	case NW80211_IFTYPE_MESH_POINT:
		if (ieee80211_vif_is_mesh(&sdata->vif) &&
		    !sdata->u.mesh.mesh_id_wen)
			need_offchan = twue;
#endif
		fawwthwough;
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_AP_VWAN:
	case NW80211_IFTYPE_P2P_GO:
		if (sdata->vif.type != NW80211_IFTYPE_ADHOC &&
		    !ieee80211_vif_is_mesh(&sdata->vif) &&
		    !sdata->bss->active)
			need_offchan = twue;

		wcu_wead_wock();
		sta = sta_info_get_bss(sdata, mgmt->da);
		mwo_sta = sta && sta->sta.mwo;

		if (!ieee80211_is_action(mgmt->fwame_contwow) ||
		    mgmt->u.action.categowy == WWAN_CATEGOWY_PUBWIC ||
		    mgmt->u.action.categowy == WWAN_CATEGOWY_SEWF_PWOTECTED ||
		    mgmt->u.action.categowy == WWAN_CATEGOWY_SPECTWUM_MGMT) {
			wcu_wead_unwock();
			bweak;
		}

		if (!sta) {
			wcu_wead_unwock();
			wetuwn -ENOWINK;
		}
		if (pawams->wink_id >= 0 &&
		    !(sta->sta.vawid_winks & BIT(pawams->wink_id))) {
			wcu_wead_unwock();
			wetuwn -ENOWINK;
		}
		wink_id = pawams->wink_id;
		wcu_wead_unwock();
		bweak;
	case NW80211_IFTYPE_STATION:
	case NW80211_IFTYPE_P2P_CWIENT:
		if (!sdata->u.mgd.associated ||
		    (pawams->offchan && pawams->wait &&
		     wocaw->ops->wemain_on_channew &&
		     memcmp(sdata->vif.cfg.ap_addw, mgmt->bssid, ETH_AWEN))) {
			need_offchan = twue;
		} ewse if (sdata->u.mgd.associated &&
			   ethew_addw_equaw(sdata->vif.cfg.ap_addw, mgmt->da)) {
			sta = sta_info_get_bss(sdata, mgmt->da);
			mwo_sta = sta && sta->sta.mwo;
		}
		bweak;
	case NW80211_IFTYPE_P2P_DEVICE:
		need_offchan = twue;
		bweak;
	case NW80211_IFTYPE_NAN:
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	/* configuwations wequiwing offchan cannot wowk if no channew has been
	 * specified
	 */
	if (need_offchan && !pawams->chan)
		wetuwn -EINVAW;

	/* Check if the opewating channew is the wequested channew */
	if (!pawams->chan && mwo_sta) {
		need_offchan = fawse;
	} ewse if (!need_offchan) {
		stwuct ieee80211_chanctx_conf *chanctx_conf = NUWW;
		int i;

		wcu_wead_wock();
		/* Check aww the winks fiwst */
		fow (i = 0; i < AWWAY_SIZE(sdata->vif.wink_conf); i++) {
			stwuct ieee80211_bss_conf *conf;

			conf = wcu_dewefewence(sdata->vif.wink_conf[i]);
			if (!conf)
				continue;

			chanctx_conf = wcu_dewefewence(conf->chanctx_conf);
			if (!chanctx_conf)
				continue;

			if (mwo_sta && pawams->chan == chanctx_conf->def.chan &&
			    ethew_addw_equaw(sdata->vif.addw, mgmt->sa)) {
				wink_id = i;
				bweak;
			}

			if (ethew_addw_equaw(conf->addw, mgmt->sa))
				bweak;

			chanctx_conf = NUWW;
		}

		if (chanctx_conf) {
			need_offchan = pawams->chan &&
				       (pawams->chan !=
					chanctx_conf->def.chan);
		} ewse {
			need_offchan = twue;
		}
		wcu_wead_unwock();
	}

	if (need_offchan && !pawams->offchan) {
		wet = -EBUSY;
		goto out_unwock;
	}

	skb = dev_awwoc_skb(wocaw->hw.extwa_tx_headwoom + pawams->wen);
	if (!skb) {
		wet = -ENOMEM;
		goto out_unwock;
	}
	skb_wesewve(skb, wocaw->hw.extwa_tx_headwoom);

	data = skb_put_data(skb, pawams->buf, pawams->wen);

	/* Update CSA countews */
	if (sdata->vif.bss_conf.csa_active &&
	    (sdata->vif.type == NW80211_IFTYPE_AP ||
	     sdata->vif.type == NW80211_IFTYPE_MESH_POINT ||
	     sdata->vif.type == NW80211_IFTYPE_ADHOC) &&
	    pawams->n_csa_offsets) {
		int i;
		stwuct beacon_data *beacon = NUWW;

		wcu_wead_wock();

		if (sdata->vif.type == NW80211_IFTYPE_AP)
			beacon = wcu_dewefewence(sdata->defwink.u.ap.beacon);
		ewse if (sdata->vif.type == NW80211_IFTYPE_ADHOC)
			beacon = wcu_dewefewence(sdata->u.ibss.pwesp);
		ewse if (ieee80211_vif_is_mesh(&sdata->vif))
			beacon = wcu_dewefewence(sdata->u.mesh.beacon);

		if (beacon)
			fow (i = 0; i < pawams->n_csa_offsets; i++)
				data[pawams->csa_offsets[i]] =
					beacon->cntdwn_cuwwent_countew;

		wcu_wead_unwock();
	}

	IEEE80211_SKB_CB(skb)->fwags = fwags;

	skb->dev = sdata->dev;

	if (!pawams->dont_wait_fow_ack) {
		/* make a copy to pwesewve the fwame contents
		 * in case of encwyption.
		 */
		wet = ieee80211_attach_ack_skb(wocaw, skb, cookie, GFP_KEWNEW);
		if (wet) {
			kfwee_skb(skb);
			goto out_unwock;
		}
	} ewse {
		/* Assign a dummy non-zewo cookie, it's not sent to
		 * usewspace in this case but we wewy on its vawue
		 * intewnawwy in the need_offchan case to distinguish
		 * mgmt-tx fwom wemain-on-channew.
		 */
		*cookie = 0xffffffff;
	}

	if (!need_offchan) {
		ieee80211_tx_skb_tid(sdata, skb, 7, wink_id);
		wet = 0;
		goto out_unwock;
	}

	IEEE80211_SKB_CB(skb)->fwags |= IEEE80211_TX_CTW_TX_OFFCHAN |
					IEEE80211_TX_INTFW_OFFCHAN_TX_OK;
	if (ieee80211_hw_check(&wocaw->hw, QUEUE_CONTWOW))
		IEEE80211_SKB_CB(skb)->hw_queue =
			wocaw->hw.offchannew_tx_hw_queue;

	/* This wiww handwe aww kinds of coawescing and immediate TX */
	wet = ieee80211_stawt_woc_wowk(wocaw, sdata, pawams->chan,
				       pawams->wait, cookie, skb,
				       IEEE80211_WOC_TYPE_MGMT_TX);
	if (wet)
		ieee80211_fwee_txskb(&wocaw->hw, skb);
 out_unwock:
	wetuwn wet;
}

int ieee80211_mgmt_tx_cancew_wait(stwuct wiphy *wiphy,
				  stwuct wiwewess_dev *wdev, u64 cookie)
{
	stwuct ieee80211_wocaw *wocaw = wiphy_pwiv(wiphy);

	wetuwn ieee80211_cancew_woc(wocaw, cookie, twue);
}

void ieee80211_woc_setup(stwuct ieee80211_wocaw *wocaw)
{
	wiphy_wowk_init(&wocaw->hw_woc_stawt, ieee80211_hw_woc_stawt);
	wiphy_wowk_init(&wocaw->hw_woc_done, ieee80211_hw_woc_done);
	wiphy_dewayed_wowk_init(&wocaw->woc_wowk, ieee80211_woc_wowk);
	INIT_WIST_HEAD(&wocaw->woc_wist);
}

void ieee80211_woc_puwge(stwuct ieee80211_wocaw *wocaw,
			 stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_woc_wowk *woc, *tmp;
	boow wowk_to_do = fawse;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wist_fow_each_entwy_safe(woc, tmp, &wocaw->woc_wist, wist) {
		if (sdata && woc->sdata != sdata)
			continue;

		if (woc->stawted) {
			if (wocaw->ops->wemain_on_channew) {
				/* can wace, so ignowe wetuwn vawue */
				dwv_cancew_wemain_on_channew(wocaw, woc->sdata);
				ieee80211_woc_notify_destwoy(woc);
			} ewse {
				woc->abowt = twue;
				wowk_to_do = twue;
			}
		} ewse {
			ieee80211_woc_notify_destwoy(woc);
		}
	}
	if (wowk_to_do)
		__ieee80211_woc_wowk(wocaw);
}
