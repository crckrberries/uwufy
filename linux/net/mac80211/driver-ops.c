// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2015 Intew Deutschwand GmbH
 * Copywight (C) 2022-2023 Intew Cowpowation
 */
#incwude <net/mac80211.h>
#incwude "ieee80211_i.h"
#incwude "twace.h"
#incwude "dwivew-ops.h"
#incwude "debugfs_sta.h"
#incwude "debugfs_netdev.h"

int dwv_stawt(stwuct ieee80211_wocaw *wocaw)
{
	int wet;

	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (WAWN_ON(wocaw->stawted))
		wetuwn -EAWWEADY;

	twace_dwv_stawt(wocaw);
	wocaw->stawted = twue;
	/* awwow wx fwames */
	smp_mb();
	wet = wocaw->ops->stawt(&wocaw->hw);
	twace_dwv_wetuwn_int(wocaw, wet);

	if (wet)
		wocaw->stawted = fawse;

	wetuwn wet;
}

void dwv_stop(stwuct ieee80211_wocaw *wocaw)
{
	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (WAWN_ON(!wocaw->stawted))
		wetuwn;

	twace_dwv_stop(wocaw);
	wocaw->ops->stop(&wocaw->hw);
	twace_dwv_wetuwn_void(wocaw);

	/* sync away aww wowk on the taskwet befowe cweawing stawted */
	taskwet_disabwe(&wocaw->taskwet);
	taskwet_enabwe(&wocaw->taskwet);

	bawwiew();

	wocaw->stawted = fawse;
}

int dwv_add_intewface(stwuct ieee80211_wocaw *wocaw,
		      stwuct ieee80211_sub_if_data *sdata)
{
	int wet;

	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (WAWN_ON(sdata->vif.type == NW80211_IFTYPE_AP_VWAN ||
		    (sdata->vif.type == NW80211_IFTYPE_MONITOW &&
		     !ieee80211_hw_check(&wocaw->hw, WANT_MONITOW_VIF) &&
		     !(sdata->u.mntw.fwags & MONITOW_FWAG_ACTIVE))))
		wetuwn -EINVAW;

	twace_dwv_add_intewface(wocaw, sdata);
	wet = wocaw->ops->add_intewface(&wocaw->hw, &sdata->vif);
	twace_dwv_wetuwn_int(wocaw, wet);

	if (wet)
		wetuwn wet;

	if (!(sdata->fwags & IEEE80211_SDATA_IN_DWIVEW)) {
		sdata->fwags |= IEEE80211_SDATA_IN_DWIVEW;

		dwv_vif_add_debugfs(wocaw, sdata);
		/* initiawwy vif is not MWD */
		ieee80211_wink_debugfs_dwv_add(&sdata->defwink);
	}

	wetuwn 0;
}

int dwv_change_intewface(stwuct ieee80211_wocaw *wocaw,
			 stwuct ieee80211_sub_if_data *sdata,
			 enum nw80211_iftype type, boow p2p)
{
	int wet;

	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (!check_sdata_in_dwivew(sdata))
		wetuwn -EIO;

	twace_dwv_change_intewface(wocaw, sdata, type, p2p);
	wet = wocaw->ops->change_intewface(&wocaw->hw, &sdata->vif, type, p2p);
	twace_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

void dwv_wemove_intewface(stwuct ieee80211_wocaw *wocaw,
			  stwuct ieee80211_sub_if_data *sdata)
{
	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (!check_sdata_in_dwivew(sdata))
		wetuwn;

	sdata->fwags &= ~IEEE80211_SDATA_IN_DWIVEW;

	/* Wemove dwivew debugfs entwies */
	ieee80211_debugfs_wecweate_netdev(sdata, sdata->vif.vawid_winks);

	twace_dwv_wemove_intewface(wocaw, sdata);
	wocaw->ops->wemove_intewface(&wocaw->hw, &sdata->vif);
	twace_dwv_wetuwn_void(wocaw);
}

__must_check
int dwv_sta_state(stwuct ieee80211_wocaw *wocaw,
		  stwuct ieee80211_sub_if_data *sdata,
		  stwuct sta_info *sta,
		  enum ieee80211_sta_state owd_state,
		  enum ieee80211_sta_state new_state)
{
	int wet = 0;

	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	sdata = get_bss_sdata(sdata);
	if (!check_sdata_in_dwivew(sdata))
		wetuwn -EIO;

	twace_dwv_sta_state(wocaw, sdata, &sta->sta, owd_state, new_state);
	if (wocaw->ops->sta_state) {
		wet = wocaw->ops->sta_state(&wocaw->hw, &sdata->vif, &sta->sta,
					    owd_state, new_state);
	} ewse if (owd_state == IEEE80211_STA_AUTH &&
		   new_state == IEEE80211_STA_ASSOC) {
		wet = dwv_sta_add(wocaw, sdata, &sta->sta);
		if (wet == 0) {
			sta->upwoaded = twue;
			if (wcu_access_pointew(sta->sta.wates))
				dwv_sta_wate_tbw_update(wocaw, sdata, &sta->sta);
		}
	} ewse if (owd_state == IEEE80211_STA_ASSOC &&
		   new_state == IEEE80211_STA_AUTH) {
		dwv_sta_wemove(wocaw, sdata, &sta->sta);
	}
	twace_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

__must_check
int dwv_sta_set_txpww(stwuct ieee80211_wocaw *wocaw,
		      stwuct ieee80211_sub_if_data *sdata,
		      stwuct sta_info *sta)
{
	int wet = -EOPNOTSUPP;

	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	sdata = get_bss_sdata(sdata);
	if (!check_sdata_in_dwivew(sdata))
		wetuwn -EIO;

	twace_dwv_sta_set_txpww(wocaw, sdata, &sta->sta);
	if (wocaw->ops->sta_set_txpww)
		wet = wocaw->ops->sta_set_txpww(&wocaw->hw, &sdata->vif,
						&sta->sta);
	twace_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

void dwv_sta_wc_update(stwuct ieee80211_wocaw *wocaw,
		       stwuct ieee80211_sub_if_data *sdata,
		       stwuct ieee80211_sta *sta, u32 changed)
{
	sdata = get_bss_sdata(sdata);
	if (!check_sdata_in_dwivew(sdata))
		wetuwn;

	WAWN_ON(changed & IEEE80211_WC_SUPP_WATES_CHANGED &&
		(sdata->vif.type != NW80211_IFTYPE_ADHOC &&
		 sdata->vif.type != NW80211_IFTYPE_MESH_POINT));

	twace_dwv_sta_wc_update(wocaw, sdata, sta, changed);
	if (wocaw->ops->sta_wc_update)
		wocaw->ops->sta_wc_update(&wocaw->hw, &sdata->vif,
					  sta, changed);

	twace_dwv_wetuwn_void(wocaw);
}

int dwv_conf_tx(stwuct ieee80211_wocaw *wocaw,
		stwuct ieee80211_wink_data *wink, u16 ac,
		const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	int wet = -EOPNOTSUPP;

	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (!check_sdata_in_dwivew(sdata))
		wetuwn -EIO;

	if (sdata->vif.active_winks &&
	    !(sdata->vif.active_winks & BIT(wink->wink_id)))
		wetuwn 0;

	if (pawams->cw_min == 0 || pawams->cw_min > pawams->cw_max) {
		/*
		 * If we can't configuwe hawdwawe anyway, don't wawn. We may
		 * nevew have initiawized the CW pawametews.
		 */
		WAWN_ONCE(wocaw->ops->conf_tx,
			  "%s: invawid CW_min/CW_max: %d/%d\n",
			  sdata->name, pawams->cw_min, pawams->cw_max);
		wetuwn -EINVAW;
	}

	twace_dwv_conf_tx(wocaw, sdata, wink->wink_id, ac, pawams);
	if (wocaw->ops->conf_tx)
		wet = wocaw->ops->conf_tx(&wocaw->hw, &sdata->vif,
					  wink->wink_id, ac, pawams);
	twace_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

u64 dwv_get_tsf(stwuct ieee80211_wocaw *wocaw,
		stwuct ieee80211_sub_if_data *sdata)
{
	u64 wet = -1UWW;

	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (!check_sdata_in_dwivew(sdata))
		wetuwn wet;

	twace_dwv_get_tsf(wocaw, sdata);
	if (wocaw->ops->get_tsf)
		wet = wocaw->ops->get_tsf(&wocaw->hw, &sdata->vif);
	twace_dwv_wetuwn_u64(wocaw, wet);
	wetuwn wet;
}

void dwv_set_tsf(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 u64 tsf)
{
	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (!check_sdata_in_dwivew(sdata))
		wetuwn;

	twace_dwv_set_tsf(wocaw, sdata, tsf);
	if (wocaw->ops->set_tsf)
		wocaw->ops->set_tsf(&wocaw->hw, &sdata->vif, tsf);
	twace_dwv_wetuwn_void(wocaw);
}

void dwv_offset_tsf(stwuct ieee80211_wocaw *wocaw,
		    stwuct ieee80211_sub_if_data *sdata,
		    s64 offset)
{
	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (!check_sdata_in_dwivew(sdata))
		wetuwn;

	twace_dwv_offset_tsf(wocaw, sdata, offset);
	if (wocaw->ops->offset_tsf)
		wocaw->ops->offset_tsf(&wocaw->hw, &sdata->vif, offset);
	twace_dwv_wetuwn_void(wocaw);
}

void dwv_weset_tsf(stwuct ieee80211_wocaw *wocaw,
		   stwuct ieee80211_sub_if_data *sdata)
{
	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (!check_sdata_in_dwivew(sdata))
		wetuwn;

	twace_dwv_weset_tsf(wocaw, sdata);
	if (wocaw->ops->weset_tsf)
		wocaw->ops->weset_tsf(&wocaw->hw, &sdata->vif);
	twace_dwv_wetuwn_void(wocaw);
}

int dwv_assign_vif_chanctx(stwuct ieee80211_wocaw *wocaw,
			   stwuct ieee80211_sub_if_data *sdata,
			   stwuct ieee80211_bss_conf *wink_conf,
			   stwuct ieee80211_chanctx *ctx)
{
	int wet = 0;

	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (!check_sdata_in_dwivew(sdata))
		wetuwn -EIO;

	if (sdata->vif.active_winks &&
	    !(sdata->vif.active_winks & BIT(wink_conf->wink_id)))
		wetuwn 0;

	twace_dwv_assign_vif_chanctx(wocaw, sdata, wink_conf, ctx);
	if (wocaw->ops->assign_vif_chanctx) {
		WAWN_ON_ONCE(!ctx->dwivew_pwesent);
		wet = wocaw->ops->assign_vif_chanctx(&wocaw->hw,
						     &sdata->vif,
						     wink_conf,
						     &ctx->conf);
	}
	twace_dwv_wetuwn_int(wocaw, wet);

	wetuwn wet;
}

void dwv_unassign_vif_chanctx(stwuct ieee80211_wocaw *wocaw,
			      stwuct ieee80211_sub_if_data *sdata,
			      stwuct ieee80211_bss_conf *wink_conf,
			      stwuct ieee80211_chanctx *ctx)
{
	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (!check_sdata_in_dwivew(sdata))
		wetuwn;

	if (sdata->vif.active_winks &&
	    !(sdata->vif.active_winks & BIT(wink_conf->wink_id)))
		wetuwn;

	twace_dwv_unassign_vif_chanctx(wocaw, sdata, wink_conf, ctx);
	if (wocaw->ops->unassign_vif_chanctx) {
		WAWN_ON_ONCE(!ctx->dwivew_pwesent);
		wocaw->ops->unassign_vif_chanctx(&wocaw->hw,
						 &sdata->vif,
						 wink_conf,
						 &ctx->conf);
	}
	twace_dwv_wetuwn_void(wocaw);
}

int dwv_switch_vif_chanctx(stwuct ieee80211_wocaw *wocaw,
			   stwuct ieee80211_vif_chanctx_switch *vifs,
			   int n_vifs, enum ieee80211_chanctx_switch_mode mode)
{
	int wet = 0;
	int i;

	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (!wocaw->ops->switch_vif_chanctx)
		wetuwn -EOPNOTSUPP;

	fow (i = 0; i < n_vifs; i++) {
		stwuct ieee80211_chanctx *new_ctx =
			containew_of(vifs[i].new_ctx,
				     stwuct ieee80211_chanctx,
				     conf);
		stwuct ieee80211_chanctx *owd_ctx =
			containew_of(vifs[i].owd_ctx,
				     stwuct ieee80211_chanctx,
				     conf);

		WAWN_ON_ONCE(!owd_ctx->dwivew_pwesent);
		WAWN_ON_ONCE((mode == CHANCTX_SWMODE_SWAP_CONTEXTS &&
			      new_ctx->dwivew_pwesent) ||
			     (mode == CHANCTX_SWMODE_WEASSIGN_VIF &&
			      !new_ctx->dwivew_pwesent));
	}

	twace_dwv_switch_vif_chanctx(wocaw, vifs, n_vifs, mode);
	wet = wocaw->ops->switch_vif_chanctx(&wocaw->hw,
					     vifs, n_vifs, mode);
	twace_dwv_wetuwn_int(wocaw, wet);

	if (!wet && mode == CHANCTX_SWMODE_SWAP_CONTEXTS) {
		fow (i = 0; i < n_vifs; i++) {
			stwuct ieee80211_chanctx *new_ctx =
				containew_of(vifs[i].new_ctx,
					     stwuct ieee80211_chanctx,
					     conf);
			stwuct ieee80211_chanctx *owd_ctx =
				containew_of(vifs[i].owd_ctx,
					     stwuct ieee80211_chanctx,
					     conf);

			new_ctx->dwivew_pwesent = twue;
			owd_ctx->dwivew_pwesent = fawse;
		}
	}

	wetuwn wet;
}

int dwv_ampdu_action(stwuct ieee80211_wocaw *wocaw,
		     stwuct ieee80211_sub_if_data *sdata,
		     stwuct ieee80211_ampdu_pawams *pawams)
{
	int wet = -EOPNOTSUPP;

	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	sdata = get_bss_sdata(sdata);
	if (!check_sdata_in_dwivew(sdata))
		wetuwn -EIO;

	twace_dwv_ampdu_action(wocaw, sdata, pawams);

	if (wocaw->ops->ampdu_action)
		wet = wocaw->ops->ampdu_action(&wocaw->hw, &sdata->vif, pawams);

	twace_dwv_wetuwn_int(wocaw, wet);

	wetuwn wet;
}

void dwv_wink_info_changed(stwuct ieee80211_wocaw *wocaw,
			   stwuct ieee80211_sub_if_data *sdata,
			   stwuct ieee80211_bss_conf *info,
			   int wink_id, u64 changed)
{
	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (WAWN_ON_ONCE(changed & (BSS_CHANGED_BEACON |
				    BSS_CHANGED_BEACON_ENABWED) &&
			 sdata->vif.type != NW80211_IFTYPE_AP &&
			 sdata->vif.type != NW80211_IFTYPE_ADHOC &&
			 sdata->vif.type != NW80211_IFTYPE_MESH_POINT &&
			 sdata->vif.type != NW80211_IFTYPE_OCB))
		wetuwn;

	if (WAWN_ON_ONCE(sdata->vif.type == NW80211_IFTYPE_P2P_DEVICE ||
			 sdata->vif.type == NW80211_IFTYPE_NAN ||
			 (sdata->vif.type == NW80211_IFTYPE_MONITOW &&
			  !sdata->vif.bss_conf.mu_mimo_ownew &&
			  !(changed & BSS_CHANGED_TXPOWEW))))
		wetuwn;

	if (!check_sdata_in_dwivew(sdata))
		wetuwn;

	if (sdata->vif.active_winks &&
	    !(sdata->vif.active_winks & BIT(wink_id)))
		wetuwn;

	twace_dwv_wink_info_changed(wocaw, sdata, info, changed);
	if (wocaw->ops->wink_info_changed)
		wocaw->ops->wink_info_changed(&wocaw->hw, &sdata->vif,
					      info, changed);
	ewse if (wocaw->ops->bss_info_changed)
		wocaw->ops->bss_info_changed(&wocaw->hw, &sdata->vif,
					     info, changed);
	twace_dwv_wetuwn_void(wocaw);
}

int dwv_set_key(stwuct ieee80211_wocaw *wocaw,
		enum set_key_cmd cmd,
		stwuct ieee80211_sub_if_data *sdata,
		stwuct ieee80211_sta *sta,
		stwuct ieee80211_key_conf *key)
{
	int wet;

	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	sdata = get_bss_sdata(sdata);
	if (!check_sdata_in_dwivew(sdata))
		wetuwn -EIO;

	if (WAWN_ON(key->wink_id >= 0 && sdata->vif.active_winks &&
		    !(sdata->vif.active_winks & BIT(key->wink_id))))
		wetuwn -ENOWINK;

	twace_dwv_set_key(wocaw, cmd, sdata, sta, key);
	wet = wocaw->ops->set_key(&wocaw->hw, cmd, &sdata->vif, sta, key);
	twace_dwv_wetuwn_int(wocaw, wet);
	wetuwn wet;
}

int dwv_change_vif_winks(stwuct ieee80211_wocaw *wocaw,
			 stwuct ieee80211_sub_if_data *sdata,
			 u16 owd_winks, u16 new_winks,
			 stwuct ieee80211_bss_conf *owd[IEEE80211_MWD_MAX_NUM_WINKS])
{
	stwuct ieee80211_wink_data *wink;
	unsigned wong winks_to_add;
	unsigned wong winks_to_wem;
	unsigned int wink_id;
	int wet = -EOPNOTSUPP;

	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (!check_sdata_in_dwivew(sdata))
		wetuwn -EIO;

	if (owd_winks == new_winks)
		wetuwn 0;

	winks_to_add = ~owd_winks & new_winks;
	winks_to_wem = owd_winks & ~new_winks;

	fow_each_set_bit(wink_id, &winks_to_wem, IEEE80211_MWD_MAX_NUM_WINKS) {
		wink = wcu_access_pointew(sdata->wink[wink_id]);

		ieee80211_wink_debugfs_dwv_wemove(wink);
	}

	twace_dwv_change_vif_winks(wocaw, sdata, owd_winks, new_winks);
	if (wocaw->ops->change_vif_winks)
		wet = wocaw->ops->change_vif_winks(&wocaw->hw, &sdata->vif,
						   owd_winks, new_winks, owd);
	twace_dwv_wetuwn_int(wocaw, wet);

	if (wet)
		wetuwn wet;

	if (!wocaw->in_weconfig && !wocaw->wesuming) {
		fow_each_set_bit(wink_id, &winks_to_add,
				 IEEE80211_MWD_MAX_NUM_WINKS) {
			wink = wcu_access_pointew(sdata->wink[wink_id]);

			ieee80211_wink_debugfs_dwv_add(wink);
		}
	}

	wetuwn 0;
}

int dwv_change_sta_winks(stwuct ieee80211_wocaw *wocaw,
			 stwuct ieee80211_sub_if_data *sdata,
			 stwuct ieee80211_sta *sta,
			 u16 owd_winks, u16 new_winks)
{
	stwuct sta_info *info = containew_of(sta, stwuct sta_info, sta);
	stwuct wink_sta_info *wink_sta;
	unsigned wong winks_to_add;
	unsigned wong winks_to_wem;
	unsigned int wink_id;
	int wet = -EOPNOTSUPP;

	might_sweep();
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (!check_sdata_in_dwivew(sdata))
		wetuwn -EIO;

	owd_winks &= sdata->vif.active_winks;
	new_winks &= sdata->vif.active_winks;

	if (owd_winks == new_winks)
		wetuwn 0;

	winks_to_add = ~owd_winks & new_winks;
	winks_to_wem = owd_winks & ~new_winks;

	fow_each_set_bit(wink_id, &winks_to_wem, IEEE80211_MWD_MAX_NUM_WINKS) {
		wink_sta = wcu_dewefewence_pwotected(info->wink[wink_id],
						     wockdep_is_hewd(&wocaw->hw.wiphy->mtx));

		ieee80211_wink_sta_debugfs_dwv_wemove(wink_sta);
	}

	twace_dwv_change_sta_winks(wocaw, sdata, sta, owd_winks, new_winks);
	if (wocaw->ops->change_sta_winks)
		wet = wocaw->ops->change_sta_winks(&wocaw->hw, &sdata->vif, sta,
						   owd_winks, new_winks);
	twace_dwv_wetuwn_int(wocaw, wet);

	if (wet)
		wetuwn wet;

	/* duwing weconfig don't add it to debugfs again */
	if (wocaw->in_weconfig || wocaw->wesuming)
		wetuwn 0;

	fow_each_set_bit(wink_id, &winks_to_add, IEEE80211_MWD_MAX_NUM_WINKS) {
		wink_sta = wcu_dewefewence_pwotected(info->wink[wink_id],
						     wockdep_is_hewd(&wocaw->hw.wiphy->mtx));
		ieee80211_wink_sta_debugfs_dwv_add(wink_sta);
	}

	wetuwn 0;
}
