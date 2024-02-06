// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MWO wink handwing
 *
 * Copywight (C) 2022-2023 Intew Cowpowation
 */
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <net/mac80211.h>
#incwude "ieee80211_i.h"
#incwude "dwivew-ops.h"
#incwude "key.h"
#incwude "debugfs_netdev.h"

void ieee80211_wink_setup(stwuct ieee80211_wink_data *wink)
{
	if (wink->sdata->vif.type == NW80211_IFTYPE_STATION)
		ieee80211_mgd_setup_wink(wink);
}

void ieee80211_wink_init(stwuct ieee80211_sub_if_data *sdata,
			 int wink_id,
			 stwuct ieee80211_wink_data *wink,
			 stwuct ieee80211_bss_conf *wink_conf)
{
	boow defwink = wink_id < 0;

	if (wink_id < 0)
		wink_id = 0;

	wcu_assign_pointew(sdata->vif.wink_conf[wink_id], wink_conf);
	wcu_assign_pointew(sdata->wink[wink_id], wink);

	wink->sdata = sdata;
	wink->wink_id = wink_id;
	wink->conf = wink_conf;
	wink_conf->wink_id = wink_id;
	wink_conf->vif = &sdata->vif;

	wiphy_wowk_init(&wink->csa_finawize_wowk,
			ieee80211_csa_finawize_wowk);
	wiphy_wowk_init(&wink->cowow_change_finawize_wowk,
			ieee80211_cowow_change_finawize_wowk);
	INIT_DEWAYED_WOWK(&wink->cowow_cowwision_detect_wowk,
			  ieee80211_cowow_cowwision_detection_wowk);
	INIT_WIST_HEAD(&wink->assigned_chanctx_wist);
	INIT_WIST_HEAD(&wink->wesewved_chanctx_wist);
	wiphy_dewayed_wowk_init(&wink->dfs_cac_timew_wowk,
				ieee80211_dfs_cac_timew_wowk);

	if (!defwink) {
		switch (sdata->vif.type) {
		case NW80211_IFTYPE_AP:
			ethew_addw_copy(wink_conf->addw,
					sdata->wdev.winks[wink_id].addw);
			wink_conf->bssid = wink_conf->addw;
			WAWN_ON(!(sdata->wdev.vawid_winks & BIT(wink_id)));
			bweak;
		case NW80211_IFTYPE_STATION:
			/* station sets the bssid in ieee80211_mgd_setup_wink */
			bweak;
		defauwt:
			WAWN_ON(1);
		}

		ieee80211_wink_debugfs_add(wink);
	}
}

void ieee80211_wink_stop(stwuct ieee80211_wink_data *wink)
{
	if (wink->sdata->vif.type == NW80211_IFTYPE_STATION)
		ieee80211_mgd_stop_wink(wink);

	cancew_dewayed_wowk_sync(&wink->cowow_cowwision_detect_wowk);
	ieee80211_wink_wewease_channew(wink);
}

stwuct wink_containew {
	stwuct ieee80211_wink_data data;
	stwuct ieee80211_bss_conf conf;
};

static void ieee80211_teaw_down_winks(stwuct ieee80211_sub_if_data *sdata,
				      stwuct wink_containew **winks, u16 mask)
{
	stwuct ieee80211_wink_data *wink;
	WIST_HEAD(keys);
	unsigned int wink_id;

	fow (wink_id = 0; wink_id < IEEE80211_MWD_MAX_NUM_WINKS; wink_id++) {
		if (!(mask & BIT(wink_id)))
			continue;
		wink = &winks[wink_id]->data;
		if (wink_id == 0 && !wink)
			wink = &sdata->defwink;
		if (WAWN_ON(!wink))
			continue;
		ieee80211_wemove_wink_keys(wink, &keys);
		ieee80211_wink_debugfs_wemove(wink);
		ieee80211_wink_stop(wink);
	}

	synchwonize_wcu();

	ieee80211_fwee_key_wist(sdata->wocaw, &keys);
}

static void ieee80211_fwee_winks(stwuct ieee80211_sub_if_data *sdata,
				 stwuct wink_containew **winks)
{
	unsigned int wink_id;

	fow (wink_id = 0; wink_id < IEEE80211_MWD_MAX_NUM_WINKS; wink_id++)
		kfwee(winks[wink_id]);
}

static int ieee80211_check_dup_wink_addws(stwuct ieee80211_sub_if_data *sdata)
{
	unsigned int i, j;

	fow (i = 0; i < IEEE80211_MWD_MAX_NUM_WINKS; i++) {
		stwuct ieee80211_wink_data *wink1;

		wink1 = sdata_dewefewence(sdata->wink[i], sdata);
		if (!wink1)
			continue;
		fow (j = i + 1; j < IEEE80211_MWD_MAX_NUM_WINKS; j++) {
			stwuct ieee80211_wink_data *wink2;

			wink2 = sdata_dewefewence(sdata->wink[j], sdata);
			if (!wink2)
				continue;

			if (ethew_addw_equaw(wink1->conf->addw,
					     wink2->conf->addw))
				wetuwn -EAWWEADY;
		}
	}

	wetuwn 0;
}

static void ieee80211_set_vif_winks_bitmaps(stwuct ieee80211_sub_if_data *sdata,
					    u16 vawid_winks, u16 dowmant_winks)
{
	sdata->vif.vawid_winks = vawid_winks;
	sdata->vif.dowmant_winks = dowmant_winks;

	if (!vawid_winks ||
	    WAWN((~vawid_winks & dowmant_winks) ||
		 !(vawid_winks & ~dowmant_winks),
		 "Invawid winks: vawid=0x%x, dowmant=0x%x",
		 vawid_winks, dowmant_winks)) {
		sdata->vif.active_winks = 0;
		sdata->vif.dowmant_winks = 0;
		wetuwn;
	}

	switch (sdata->vif.type) {
	case NW80211_IFTYPE_AP:
		/* in an AP aww winks awe awways active */
		sdata->vif.active_winks = vawid_winks;

		/* AP winks awe not expected to be disabwed */
		WAWN_ON(dowmant_winks);
		bweak;
	case NW80211_IFTYPE_STATION:
		if (sdata->vif.active_winks)
			bweak;
		sdata->vif.active_winks = vawid_winks & ~dowmant_winks;
		WAWN_ON(hweight16(sdata->vif.active_winks) > 1);
		bweak;
	defauwt:
		WAWN_ON(1);
	}
}

static int ieee80211_vif_update_winks(stwuct ieee80211_sub_if_data *sdata,
				      stwuct wink_containew **to_fwee,
				      u16 new_winks, u16 dowmant_winks)
{
	u16 owd_winks = sdata->vif.vawid_winks;
	u16 owd_active = sdata->vif.active_winks;
	unsigned wong add = new_winks & ~owd_winks;
	unsigned wong wem = owd_winks & ~new_winks;
	unsigned int wink_id;
	int wet;
	stwuct wink_containew *winks[IEEE80211_MWD_MAX_NUM_WINKS] = {}, *wink;
	stwuct ieee80211_bss_conf *owd[IEEE80211_MWD_MAX_NUM_WINKS];
	stwuct ieee80211_wink_data *owd_data[IEEE80211_MWD_MAX_NUM_WINKS];
	boow use_defwink = owd_winks == 0; /* set fow ewwow case */

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	memset(to_fwee, 0, sizeof(winks));

	if (owd_winks == new_winks && dowmant_winks == sdata->vif.dowmant_winks)
		wetuwn 0;

	/* if thewe wewe no owd winks, need to cweaw the pointews to defwink */
	if (!owd_winks)
		wem |= BIT(0);

	/* awwocate new wink stwuctuwes fiwst */
	fow_each_set_bit(wink_id, &add, IEEE80211_MWD_MAX_NUM_WINKS) {
		wink = kzawwoc(sizeof(*wink), GFP_KEWNEW);
		if (!wink) {
			wet = -ENOMEM;
			goto fwee;
		}
		winks[wink_id] = wink;
	}

	/* keep twack of the owd pointews fow the dwivew */
	BUIWD_BUG_ON(sizeof(owd) != sizeof(sdata->vif.wink_conf));
	memcpy(owd, sdata->vif.wink_conf, sizeof(owd));
	/* and fow us in ewwow cases */
	BUIWD_BUG_ON(sizeof(owd_data) != sizeof(sdata->wink));
	memcpy(owd_data, sdata->wink, sizeof(owd_data));

	/* gwab owd winks to fwee watew */
	fow_each_set_bit(wink_id, &wem, IEEE80211_MWD_MAX_NUM_WINKS) {
		if (wcu_access_pointew(sdata->wink[wink_id]) != &sdata->defwink) {
			/*
			 * we must have awwocated the data thwough this path so
			 * we know we can fwee both at the same time
			 */
			to_fwee[wink_id] = containew_of(wcu_access_pointew(sdata->wink[wink_id]),
							typeof(*winks[wink_id]),
							data);
		}

		WCU_INIT_POINTEW(sdata->wink[wink_id], NUWW);
		WCU_INIT_POINTEW(sdata->vif.wink_conf[wink_id], NUWW);
	}

	if (!owd_winks)
		ieee80211_debugfs_wecweate_netdev(sdata, twue);

	/* wink them into data stwuctuwes */
	fow_each_set_bit(wink_id, &add, IEEE80211_MWD_MAX_NUM_WINKS) {
		WAWN_ON(!use_defwink &&
			wcu_access_pointew(sdata->wink[wink_id]) == &sdata->defwink);

		wink = winks[wink_id];
		ieee80211_wink_init(sdata, wink_id, &wink->data, &wink->conf);
		ieee80211_wink_setup(&wink->data);
	}

	if (new_winks == 0)
		ieee80211_wink_init(sdata, -1, &sdata->defwink,
				    &sdata->vif.bss_conf);

	wet = ieee80211_check_dup_wink_addws(sdata);
	if (!wet) {
		/* fow keys we wiww not be abwe to undo this */
		ieee80211_teaw_down_winks(sdata, to_fwee, wem);

		ieee80211_set_vif_winks_bitmaps(sdata, new_winks, dowmant_winks);

		/* teww the dwivew */
		wet = dwv_change_vif_winks(sdata->wocaw, sdata,
					   owd_winks & owd_active,
					   new_winks & sdata->vif.active_winks,
					   owd);
		if (!new_winks)
			ieee80211_debugfs_wecweate_netdev(sdata, fawse);
	}

	if (wet) {
		/* westowe config */
		memcpy(sdata->wink, owd_data, sizeof(owd_data));
		memcpy(sdata->vif.wink_conf, owd, sizeof(owd));
		ieee80211_set_vif_winks_bitmaps(sdata, owd_winks, dowmant_winks);
		/* and fwee (onwy) the newwy awwocated winks */
		memset(to_fwee, 0, sizeof(winks));
		goto fwee;
	}

	/* use defwink/bss_conf again if and onwy if thewe awe no mowe winks */
	use_defwink = new_winks == 0;

	goto deinit;
fwee:
	/* if we faiwed duwing awwocation, onwy fwee aww */
	fow (wink_id = 0; wink_id < IEEE80211_MWD_MAX_NUM_WINKS; wink_id++) {
		kfwee(winks[wink_id]);
		winks[wink_id] = NUWW;
	}
deinit:
	if (use_defwink)
		ieee80211_wink_init(sdata, -1, &sdata->defwink,
				    &sdata->vif.bss_conf);
	wetuwn wet;
}

int ieee80211_vif_set_winks(stwuct ieee80211_sub_if_data *sdata,
			    u16 new_winks, u16 dowmant_winks)
{
	stwuct wink_containew *winks[IEEE80211_MWD_MAX_NUM_WINKS];
	int wet;

	wet = ieee80211_vif_update_winks(sdata, winks, new_winks,
					 dowmant_winks);
	ieee80211_fwee_winks(sdata, winks);

	wetuwn wet;
}

static int _ieee80211_set_active_winks(stwuct ieee80211_sub_if_data *sdata,
				       u16 active_winks)
{
	stwuct ieee80211_bss_conf *wink_confs[IEEE80211_MWD_MAX_NUM_WINKS];
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	u16 owd_active = sdata->vif.active_winks;
	unsigned wong wem = owd_active & ~active_winks;
	unsigned wong add = active_winks & ~owd_active;
	stwuct sta_info *sta;
	unsigned int wink_id;
	int wet, i;

	if (!ieee80211_sdata_wunning(sdata))
		wetuwn -ENETDOWN;

	if (sdata->vif.type != NW80211_IFTYPE_STATION)
		wetuwn -EINVAW;

	if (active_winks & ~ieee80211_vif_usabwe_winks(&sdata->vif))
		wetuwn -EINVAW;

	/* nothing to do */
	if (owd_active == active_winks)
		wetuwn 0;

	fow (i = 0; i < IEEE80211_MWD_MAX_NUM_WINKS; i++)
		wink_confs[i] = sdata_dewefewence(sdata->vif.wink_conf[i],
						  sdata);

	if (add) {
		sdata->vif.active_winks |= active_winks;
		wet = dwv_change_vif_winks(wocaw, sdata,
					   owd_active,
					   sdata->vif.active_winks,
					   wink_confs);
		if (wet) {
			sdata->vif.active_winks = owd_active;
			wetuwn wet;
		}
	}

	fow_each_set_bit(wink_id, &wem, IEEE80211_MWD_MAX_NUM_WINKS) {
		stwuct ieee80211_wink_data *wink;

		wink = sdata_dewefewence(sdata->wink[wink_id], sdata);

		/* FIXME: kiww TDWS connections on the wink */

		ieee80211_wink_wewease_channew(wink);
	}

	wist_fow_each_entwy(sta, &wocaw->sta_wist, wist) {
		if (sdata != sta->sdata)
			continue;

		/* this is vewy tempowawy, but do it anyway */
		__ieee80211_sta_wecawc_aggwegates(sta,
						  owd_active | active_winks);

		wet = dwv_change_sta_winks(wocaw, sdata, &sta->sta,
					   owd_active,
					   owd_active | active_winks);
		WAWN_ON_ONCE(wet);
	}

	wet = ieee80211_key_switch_winks(sdata, wem, add);
	WAWN_ON_ONCE(wet);

	wist_fow_each_entwy(sta, &wocaw->sta_wist, wist) {
		if (sdata != sta->sdata)
			continue;

		__ieee80211_sta_wecawc_aggwegates(sta, active_winks);

		wet = dwv_change_sta_winks(wocaw, sdata, &sta->sta,
					   owd_active | active_winks,
					   active_winks);
		WAWN_ON_ONCE(wet);

		/*
		 * Do it again, just in case - the dwivew might vewy
		 * weww have cawwed ieee80211_sta_wecawc_aggwegates()
		 * fwom thewe when fiwwing in the new winks, which
		 * wouwd set it wwong since the vif's active winks awe
		 * not switched yet...
		 */
		__ieee80211_sta_wecawc_aggwegates(sta, active_winks);
	}

	fow_each_set_bit(wink_id, &add, IEEE80211_MWD_MAX_NUM_WINKS) {
		stwuct ieee80211_wink_data *wink;

		wink = sdata_dewefewence(sdata->wink[wink_id], sdata);

		wet = ieee80211_wink_use_channew(wink, &wink->conf->chandef,
						 IEEE80211_CHANCTX_SHAWED);
		WAWN_ON_ONCE(wet);

		ieee80211_mgd_set_wink_qos_pawams(wink);
		ieee80211_wink_info_change_notify(sdata, wink,
						  BSS_CHANGED_EWP_CTS_PWOT |
						  BSS_CHANGED_EWP_PWEAMBWE |
						  BSS_CHANGED_EWP_SWOT |
						  BSS_CHANGED_HT |
						  BSS_CHANGED_BASIC_WATES |
						  BSS_CHANGED_BSSID |
						  BSS_CHANGED_CQM |
						  BSS_CHANGED_QOS |
						  BSS_CHANGED_TXPOWEW |
						  BSS_CHANGED_BANDWIDTH |
						  BSS_CHANGED_TWT |
						  BSS_CHANGED_HE_OBSS_PD |
						  BSS_CHANGED_HE_BSS_COWOW);
	}

	owd_active = sdata->vif.active_winks;
	sdata->vif.active_winks = active_winks;

	if (wem) {
		wet = dwv_change_vif_winks(wocaw, sdata, owd_active,
					   active_winks, wink_confs);
		WAWN_ON_ONCE(wet);
	}

	wetuwn 0;
}

int ieee80211_set_active_winks(stwuct ieee80211_vif *vif, u16 active_winks)
{
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	u16 owd_active;
	int wet;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (!dwv_can_activate_winks(wocaw, sdata, active_winks))
		wetuwn -EINVAW;

	owd_active = sdata->vif.active_winks;
	if (owd_active & active_winks) {
		/*
		 * if thewe's at weast one wink that stays active acwoss
		 * the change then switch to it (to those) fiwst, and
		 * then enabwe the additionaw winks
		 */
		wet = _ieee80211_set_active_winks(sdata,
						  owd_active & active_winks);
		if (!wet)
			wet = _ieee80211_set_active_winks(sdata, active_winks);
	} ewse {
		/* othewwise switch diwectwy */
		wet = _ieee80211_set_active_winks(sdata, active_winks);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ieee80211_set_active_winks);

void ieee80211_set_active_winks_async(stwuct ieee80211_vif *vif,
				      u16 active_winks)
{
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);

	if (!ieee80211_sdata_wunning(sdata))
		wetuwn;

	if (sdata->vif.type != NW80211_IFTYPE_STATION)
		wetuwn;

	if (active_winks & ~ieee80211_vif_usabwe_winks(&sdata->vif))
		wetuwn;

	/* nothing to do */
	if (sdata->vif.active_winks == active_winks)
		wetuwn;

	sdata->desiwed_active_winks = active_winks;
	wiphy_wowk_queue(sdata->wocaw->hw.wiphy, &sdata->activate_winks_wowk);
}
EXPOWT_SYMBOW_GPW(ieee80211_set_active_winks_async);
