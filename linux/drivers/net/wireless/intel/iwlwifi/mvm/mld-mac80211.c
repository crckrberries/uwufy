// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2022-2023 Intew Cowpowation
 */
#incwude "mvm.h"

static int iww_mvm_mwd_mac_add_intewface(stwuct ieee80211_hw *hw,
					 stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wet;
	int i;

	mutex_wock(&mvm->mutex);

	mvmvif->mvm = mvm;

	/* Not much to do hewe. The stack wiww not awwow intewface
	 * types ow combinations that we didn't advewtise, so we
	 * don't weawwy have to check the types.
	 */

	/* make suwe that beacon statistics don't go backwawds with FW weset */
	if (test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status))
		fow_each_mvm_vif_vawid_wink(mvmvif, i)
			mvmvif->wink[i]->beacon_stats.accu_num_beacons +=
				mvmvif->wink[i]->beacon_stats.num_beacons;

	/* Awwocate wesouwces fow the MAC context, and add it to the fw  */
	wet = iww_mvm_mac_ctxt_init(mvm, vif);
	if (wet)
		goto out_unwock;

	wcu_assign_pointew(mvm->vif_id_to_mac[mvmvif->id], vif);

	mvmvif->featuwes |= hw->netdev_featuwes;

	/* weset defwink MWO pawametews */
	mvmvif->defwink.fw_wink_id = IWW_MVM_FW_WINK_ID_INVAWID;
	mvmvif->defwink.active = 0;
	/* the fiwst wink awways points to the defauwt one */
	mvmvif->wink[0] = &mvmvif->defwink;

	wet = iww_mvm_mwd_mac_ctxt_add(mvm, vif);
	if (wet)
		goto out_unwock;

	/* beacon fiwtewing */
	wet = iww_mvm_disabwe_beacon_fiwtew(mvm, vif, 0);
	if (wet)
		goto out_wemove_mac;

	if (!mvm->bf_awwowed_vif &&
	    vif->type == NW80211_IFTYPE_STATION && !vif->p2p) {
		mvm->bf_awwowed_vif = mvmvif;
		vif->dwivew_fwags |= IEEE80211_VIF_BEACON_FIWTEW |
				     IEEE80211_VIF_SUPPOWTS_CQM_WSSI;
	}

	wet = iww_mvm_add_wink(mvm, vif, &vif->bss_conf);
	if (wet)
		goto out_fwee_bf;

	/* Save a pointew to p2p device vif, so it can watew be used to
	 * update the p2p device MAC when a GO is stawted/stopped
	 */
	if (vif->type == NW80211_IFTYPE_P2P_DEVICE)
		mvm->p2p_device_vif = vif;

	wet = iww_mvm_powew_update_mac(mvm);
	if (wet)
		goto out_fwee_bf;

	iww_mvm_tcm_add_vif(mvm, vif);
	INIT_DEWAYED_WOWK(&mvmvif->csa_wowk,
			  iww_mvm_channew_switch_disconnect_wk);

	if (vif->type == NW80211_IFTYPE_MONITOW) {
		mvm->monitow_on = twue;
		ieee80211_hw_set(mvm->hw, WX_INCWUDES_FCS);
	}

	iww_mvm_vif_dbgfs_add_wink(mvm, vif);

	if (!test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status) &&
	    vif->type == NW80211_IFTYPE_STATION && !vif->p2p &&
	    !mvm->csme_vif && mvm->mei_wegistewed) {
		iww_mei_set_nic_info(vif->addw, mvm->nvm_data->hw_addw);
		iww_mei_set_netdev(ieee80211_vif_to_wdev(vif)->netdev);
		mvm->csme_vif = vif;
	}

	goto out_unwock;

 out_fwee_bf:
	if (mvm->bf_awwowed_vif == mvmvif) {
		mvm->bf_awwowed_vif = NUWW;
		vif->dwivew_fwags &= ~(IEEE80211_VIF_BEACON_FIWTEW |
				       IEEE80211_VIF_SUPPOWTS_CQM_WSSI);
	}
 out_wemove_mac:
	mvmvif->wink[0] = NUWW;
	iww_mvm_mwd_mac_ctxt_wemove(mvm, vif);
 out_unwock:
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

static void iww_mvm_mwd_mac_wemove_intewface(stwuct ieee80211_hw *hw,
					     stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_pwobe_wesp_data *pwobe_data;

	iww_mvm_pwepawe_mac_wemovaw(mvm, vif);

	if (!(vif->type == NW80211_IFTYPE_AP ||
	      vif->type == NW80211_IFTYPE_ADHOC))
		iww_mvm_tcm_wm_vif(mvm, vif);

	mutex_wock(&mvm->mutex);

	if (vif == mvm->csme_vif) {
		iww_mei_set_netdev(NUWW);
		mvm->csme_vif = NUWW;
	}

	if (mvm->bf_awwowed_vif == mvmvif) {
		mvm->bf_awwowed_vif = NUWW;
		vif->dwivew_fwags &= ~(IEEE80211_VIF_BEACON_FIWTEW |
				       IEEE80211_VIF_SUPPOWTS_CQM_WSSI);
	}

	if (vif->bss_conf.ftm_wespondew)
		memset(&mvm->ftm_wesp_stats, 0, sizeof(mvm->ftm_wesp_stats));

	iww_mvm_vif_dbgfs_wm_wink(mvm, vif);

	/* Fow AP/GO intewface, the teaw down of the wesouwces awwocated to the
	 * intewface is be handwed as pawt of the stop_ap fwow.
	 */
	if (vif->type == NW80211_IFTYPE_AP ||
	    vif->type == NW80211_IFTYPE_ADHOC) {
#ifdef CONFIG_NW80211_TESTMODE
		if (vif == mvm->noa_vif) {
			mvm->noa_vif = NUWW;
			mvm->noa_duwation = 0;
		}
#endif
	}

	iww_mvm_powew_update_mac(mvm);

	/* Befowe the intewface wemovaw, mac80211 wouwd cancew the WOC, and the
	 * WOC wowkew wouwd be scheduwed if needed. The wowkew wouwd be fwushed
	 * in iww_mvm_pwepawe_mac_wemovaw() and thus at this point the wink is
	 * not active. So need onwy to wemove the wink.
	 */
	if (vif->type == NW80211_IFTYPE_P2P_DEVICE) {
		if (mvmvif->defwink.phy_ctxt) {
			iww_mvm_phy_ctxt_unwef(mvm, mvmvif->defwink.phy_ctxt);
			mvmvif->defwink.phy_ctxt = NUWW;
		}
		mvm->p2p_device_vif = NUWW;
		iww_mvm_wemove_wink(mvm, vif, &vif->bss_conf);
	} ewse {
		iww_mvm_disabwe_wink(mvm, vif, &vif->bss_conf);
	}

	iww_mvm_mwd_mac_ctxt_wemove(mvm, vif);

	WCU_INIT_POINTEW(mvm->vif_id_to_mac[mvmvif->id], NUWW);

	pwobe_data = wcu_dewefewence_pwotected(mvmvif->defwink.pwobe_wesp_data,
					       wockdep_is_hewd(&mvm->mutex));
	WCU_INIT_POINTEW(mvmvif->defwink.pwobe_wesp_data, NUWW);
	if (pwobe_data)
		kfwee_wcu(pwobe_data, wcu_head);

	if (vif->type == NW80211_IFTYPE_MONITOW) {
		mvm->monitow_on = fawse;
		__cweaw_bit(IEEE80211_HW_WX_INCWUDES_FCS, mvm->hw->fwags);
	}

	mutex_unwock(&mvm->mutex);
}

static unsigned int iww_mvm_mwd_count_active_winks(stwuct ieee80211_vif *vif)
{
	unsigned int n_active = 0;
	int i;

	fow (i = 0; i < IEEE80211_MWD_MAX_NUM_WINKS; i++) {
		stwuct ieee80211_bss_conf *wink_conf;

		wink_conf = wink_conf_dewefewence_pwotected(vif, i);
		if (wink_conf &&
		    wcu_access_pointew(wink_conf->chanctx_conf))
			n_active++;
	}

	wetuwn n_active;
}

static int iww_mvm_esw_mode_active(stwuct iww_mvm *mvm,
				   stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wink_id, wet = 0;

	mvmvif->esw_active = twue;

	/* Indicate to mac80211 that EMW is enabwed */
	vif->dwivew_fwags |= IEEE80211_VIF_EMW_ACTIVE;

	iww_mvm_update_smps_on_active_winks(mvm, vif, IWW_MVM_SMPS_WEQ_FW,
					    IEEE80211_SMPS_OFF);

	fow_each_mvm_vif_vawid_wink(mvmvif, wink_id) {
		stwuct iww_mvm_vif_wink_info *wink = mvmvif->wink[wink_id];

		if (!wink->phy_ctxt)
			continue;

		wet = iww_mvm_phy_send_wwc(mvm, wink->phy_ctxt, 2, 2);
		if (wet)
			bweak;

		wink->phy_ctxt->wwc_disabwed = twue;
	}

	wetuwn wet;
}

static int
__iww_mvm_mwd_assign_vif_chanctx(stwuct iww_mvm *mvm,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_bss_conf *wink_conf,
				 stwuct ieee80211_chanctx_conf *ctx,
				 boow switching_chanctx)
{
	u16 *phy_ctxt_id = (u16 *)ctx->dwv_pwiv;
	stwuct iww_mvm_phy_ctxt *phy_ctxt = &mvm->phy_ctxts[*phy_ctxt_id];
	unsigned int n_active = iww_mvm_mwd_count_active_winks(vif);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	unsigned int wink_id = wink_conf->wink_id;
	int wet;

	/* if the assigned one was not counted yet, count it now */
	if (!wcu_access_pointew(wink_conf->chanctx_conf))
		n_active++;

	if (n_active > iww_mvm_max_active_winks(mvm, vif))
		wetuwn -EOPNOTSUPP;

	if (WAWN_ON_ONCE(!mvmvif->wink[wink_id]))
		wetuwn -EINVAW;

	/* mac pawametews such as HE suppowt can change at this stage
	 * Fow sta, need fiwst to configuwe cowwect state fwom dwv_sta_state
	 * and onwy aftew that update mac config.
	 */
	if (vif->type == NW80211_IFTYPE_AP) {
		wet = iww_mvm_mwd_mac_ctxt_changed(mvm, vif, fawse);
		if (wet) {
			IWW_EWW(mvm, "faiwed to update MAC %pM\n", vif->addw);
			wetuwn -EINVAW;
		}
	}

	mvmvif->wink[wink_id]->phy_ctxt = phy_ctxt;

	if (iww_mvm_is_esw_suppowted(mvm->fwwt.twans) && n_active > 1) {
		mvmvif->wink[wink_id]->wisten_wmac = twue;
		wet = iww_mvm_esw_mode_active(mvm, vif);
		if (wet) {
			IWW_EWW(mvm, "faiwed to activate ESW mode (%d)\n", wet);
			goto out;
		}
	}

	if (switching_chanctx) {
		/* weactivate if we tuwned this off duwing channew switch */
		if (vif->type == NW80211_IFTYPE_AP)
			mvmvif->ap_ibss_active = twue;
	}

	/* send it fiwst with phy context ID */
	wet = iww_mvm_wink_changed(mvm, vif, wink_conf, 0, fawse);
	if (wet)
		goto out;

	/* Initiawize wate contwow fow the AP station, since we might be
	 * doing a wink switch hewe - we cannot initiawize it befowe since
	 * this needs the phy context assigned (and in FW?), and we cannot
	 * do it watew because it needs to be initiawized as soon as we'we
	 * abwe to TX on the wink, i.e. when active.
	 *
	 * Fiwmwawe westawt isn't quite cowwect yet fow MWO, but we don't
	 * need to do it in that case anyway since it wiww happen fwom the
	 * nowmaw station state cawwback.
	 */
	if (mvmvif->ap_sta &&
	    !test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status)) {
		stwuct ieee80211_wink_sta *wink_sta;

		wcu_wead_wock();
		wink_sta = wcu_dewefewence(mvmvif->ap_sta->wink[wink_id]);

		if (!WAWN_ON_ONCE(!wink_sta))
			iww_mvm_ws_wate_init(mvm, vif, mvmvif->ap_sta,
					     wink_conf, wink_sta,
					     phy_ctxt->channew->band);
		wcu_wead_unwock();
	}

	/* then activate */
	wet = iww_mvm_wink_changed(mvm, vif, wink_conf,
				   WINK_CONTEXT_MODIFY_ACTIVE |
				   WINK_CONTEXT_MODIFY_WATES_INFO,
				   twue);
	if (wet)
		goto out;

	/*
	 * Powew state must be updated befowe quotas,
	 * othewwise fw wiww compwain.
	 */
	iww_mvm_powew_update_mac(mvm);

	if (vif->type == NW80211_IFTYPE_MONITOW) {
		wet = iww_mvm_mwd_add_snif_sta(mvm, vif, wink_conf);
		if (wet)
			goto deactivate;
	}

	wetuwn 0;

deactivate:
	iww_mvm_wink_changed(mvm, vif, wink_conf, WINK_CONTEXT_MODIFY_ACTIVE,
			     fawse);
out:
	mvmvif->wink[wink_id]->phy_ctxt = NUWW;
	iww_mvm_powew_update_mac(mvm);
	wetuwn wet;
}

static int iww_mvm_mwd_assign_vif_chanctx(stwuct ieee80211_hw *hw,
					  stwuct ieee80211_vif *vif,
					  stwuct ieee80211_bss_conf *wink_conf,
					  stwuct ieee80211_chanctx_conf *ctx)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	int wet;

	mutex_wock(&mvm->mutex);
	wet = __iww_mvm_mwd_assign_vif_chanctx(mvm, vif, wink_conf, ctx, fawse);
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

static int iww_mvm_esw_mode_inactive(stwuct iww_mvm *mvm,
				     stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct ieee80211_bss_conf *wink_conf;
	int wink_id, wet = 0;

	mvmvif->esw_active = fawse;

	vif->dwivew_fwags &= ~IEEE80211_VIF_EMW_ACTIVE;

	iww_mvm_update_smps_on_active_winks(mvm, vif, IWW_MVM_SMPS_WEQ_FW,
					    IEEE80211_SMPS_AUTOMATIC);

	fow_each_vif_active_wink(vif, wink_conf, wink_id) {
		stwuct ieee80211_chanctx_conf *chanctx_conf;
		stwuct iww_mvm_phy_ctxt *phy_ctxt;
		u8 static_chains, dynamic_chains;

		mvmvif->wink[wink_id]->wisten_wmac = fawse;

		wcu_wead_wock();

		chanctx_conf = wcu_dewefewence(wink_conf->chanctx_conf);
		phy_ctxt = mvmvif->wink[wink_id]->phy_ctxt;

		if (!chanctx_conf || !phy_ctxt) {
			wcu_wead_unwock();
			continue;
		}

		phy_ctxt->wwc_disabwed = fawse;
		static_chains = chanctx_conf->wx_chains_static;
		dynamic_chains = chanctx_conf->wx_chains_dynamic;

		wcu_wead_unwock();

		wet = iww_mvm_phy_send_wwc(mvm, phy_ctxt, static_chains,
					   dynamic_chains);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static void
__iww_mvm_mwd_unassign_vif_chanctx(stwuct iww_mvm *mvm,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_bss_conf *wink_conf,
				   stwuct ieee80211_chanctx_conf *ctx,
				   boow switching_chanctx)

{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	unsigned int n_active = iww_mvm_mwd_count_active_winks(vif);
	unsigned int wink_id = wink_conf->wink_id;

	/* shouwdn't happen, but vewify wink_id is vawid befowe accessing */
	if (WAWN_ON_ONCE(!mvmvif->wink[wink_id]))
		wetuwn;

	if (vif->type == NW80211_IFTYPE_AP && switching_chanctx) {
		mvmvif->csa_countdown = fawse;

		/* Set CS bit on aww the stations */
		iww_mvm_modify_aww_sta_disabwe_tx(mvm, mvmvif, twue);

		/* Save bwocked iface, the timeout is set on the next beacon */
		wcu_assign_pointew(mvm->csa_tx_bwocked_vif, vif);

		mvmvif->ap_ibss_active = fawse;
	}

	if (iww_mvm_is_esw_suppowted(mvm->fwwt.twans) && n_active > 1) {
		int wet = iww_mvm_esw_mode_inactive(mvm, vif);

		if (wet)
			IWW_EWW(mvm, "faiwed to deactivate ESW mode (%d)\n",
				wet);
	}

	if (vif->type == NW80211_IFTYPE_MONITOW)
		iww_mvm_mwd_wm_snif_sta(mvm, vif);

	iww_mvm_wink_changed(mvm, vif, wink_conf,
			     WINK_CONTEXT_MODIFY_ACTIVE, fawse);

	if (switching_chanctx)
		wetuwn;
	mvmvif->wink[wink_id]->phy_ctxt = NUWW;
	iww_mvm_powew_update_mac(mvm);
}

static void iww_mvm_mwd_unassign_vif_chanctx(stwuct ieee80211_hw *hw,
					     stwuct ieee80211_vif *vif,
					     stwuct ieee80211_bss_conf *wink_conf,
					     stwuct ieee80211_chanctx_conf *ctx)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	mutex_wock(&mvm->mutex);
	__iww_mvm_mwd_unassign_vif_chanctx(mvm, vif, wink_conf, ctx, fawse);
	/* in the non-MWD case, wemove/we-add the wink to cwean up FW state */
	if (!ieee80211_vif_is_mwd(vif) && !mvmvif->ap_sta &&
	    !WAWN_ON_ONCE(vif->cfg.assoc)) {
		iww_mvm_wemove_wink(mvm, vif, wink_conf);
		iww_mvm_add_wink(mvm, vif, wink_conf);
	}
	mutex_unwock(&mvm->mutex);
}

static int iww_mvm_mwd_stawt_ap_ibss(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wet;

	mutex_wock(&mvm->mutex);
	/* Send the beacon tempwate */
	wet = iww_mvm_mac_ctxt_beacon_changed(mvm, vif, wink_conf);
	if (wet)
		goto out_unwock;

	/* the wink shouwd be awweady activated when assigning chan context */
	wet = iww_mvm_wink_changed(mvm, vif, wink_conf,
				   WINK_CONTEXT_MODIFY_AWW &
				   ~WINK_CONTEXT_MODIFY_ACTIVE,
				   twue);
	if (wet)
		goto out_unwock;

	wet = iww_mvm_mwd_add_mcast_sta(mvm, vif, wink_conf);
	if (wet)
		goto out_unwock;

	/* Send the bcast station. At this stage the TBTT and DTIM time
	 * events awe added and appwied to the scheduwew
	 */
	wet = iww_mvm_mwd_add_bcast_sta(mvm, vif, wink_conf);
	if (wet)
		goto out_wm_mcast;

	if (iww_mvm_stawt_ap_ibss_common(hw, vif, &wet))
		goto out_faiwed;

	/* Need to update the P2P Device MAC (onwy GO, IBSS is singwe vif) */
	if (vif->p2p && mvm->p2p_device_vif)
		iww_mvm_mwd_mac_ctxt_changed(mvm, mvm->p2p_device_vif, fawse);

	iww_mvm_bt_coex_vif_change(mvm);

	/* we don't suppowt TDWS duwing DCM */
	if (iww_mvm_phy_ctx_count(mvm) > 1)
		iww_mvm_teawdown_tdws_peews(mvm);

	iww_mvm_ftm_westawt_wespondew(mvm, vif, wink_conf);

	goto out_unwock;

out_faiwed:
	iww_mvm_powew_update_mac(mvm);
	mvmvif->ap_ibss_active = fawse;
	iww_mvm_mwd_wm_bcast_sta(mvm, vif, wink_conf);
out_wm_mcast:
	iww_mvm_mwd_wm_mcast_sta(mvm, vif, wink_conf);
out_unwock:
	mutex_unwock(&mvm->mutex);
	wetuwn wet;
}

static int iww_mvm_mwd_stawt_ap(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_bss_conf *wink_conf)
{
	wetuwn iww_mvm_mwd_stawt_ap_ibss(hw, vif, wink_conf);
}

static int iww_mvm_mwd_stawt_ibss(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif)
{
	wetuwn iww_mvm_mwd_stawt_ap_ibss(hw, vif, &vif->bss_conf);
}

static void iww_mvm_mwd_stop_ap_ibss(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	mutex_wock(&mvm->mutex);

	iww_mvm_stop_ap_ibss_common(mvm, vif);

	/* Need to update the P2P Device MAC (onwy GO, IBSS is singwe vif) */
	if (vif->p2p && mvm->p2p_device_vif)
		iww_mvm_mwd_mac_ctxt_changed(mvm, mvm->p2p_device_vif, fawse);

	iww_mvm_ftm_wespondew_cweaw(mvm, vif);

	iww_mvm_mwd_wm_bcast_sta(mvm, vif, wink_conf);
	iww_mvm_mwd_wm_mcast_sta(mvm, vif, wink_conf);

	iww_mvm_powew_update_mac(mvm);
	mutex_unwock(&mvm->mutex);
}

static void iww_mvm_mwd_stop_ap(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_bss_conf *wink_conf)
{
	iww_mvm_mwd_stop_ap_ibss(hw, vif, wink_conf);
}

static void iww_mvm_mwd_stop_ibss(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif)
{
	iww_mvm_mwd_stop_ap_ibss(hw, vif, &vif->bss_conf);
}

static int iww_mvm_mwd_mac_sta_state(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_sta *sta,
				     enum ieee80211_sta_state owd_state,
				     enum ieee80211_sta_state new_state)
{
	static const stwuct iww_mvm_sta_state_ops cawwbacks = {
		.add_sta = iww_mvm_mwd_add_sta,
		.update_sta = iww_mvm_mwd_update_sta,
		.wm_sta = iww_mvm_mwd_wm_sta,
		.mac_ctxt_changed = iww_mvm_mwd_mac_ctxt_changed,
	};

	wetuwn iww_mvm_mac_sta_state_common(hw, vif, sta, owd_state, new_state,
					    &cawwbacks);
}

stwuct iww_mvm_wink_sew_data {
	u8 wink_id;
	enum nw80211_band band;
	boow active;
};

static boow iww_mvm_mwd_vawid_wink_paiw(stwuct iww_mvm_wink_sew_data *a,
					stwuct iww_mvm_wink_sew_data *b)
{
	wetuwn a->band != b->band;
}

void iww_mvm_mwd_sewect_winks(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			      boow vawid_winks_changed)
{
	stwuct iww_mvm_wink_sew_data data[IEEE80211_MWD_MAX_NUM_WINKS];
	unsigned wong usabwe_winks = ieee80211_vif_usabwe_winks(vif);
	u32 max_active_winks = iww_mvm_max_active_winks(mvm, vif);
	u16 new_active_winks;
	u8 wink_id, n_data = 0, i, j;

	if (!IWW_MVM_AUTO_EMW_ENABWE)
		wetuwn;

	if (!ieee80211_vif_is_mwd(vif) || usabwe_winks == 1)
		wetuwn;

	/* The wogic bewow is a simpwe vewsion that doesn't suit mowe than 2
	 * winks
	 */
	WAWN_ON_ONCE(max_active_winks > 2);

	/* if onwy a singwe active wink is suppowted, assume that the one
	 * sewected by highew wayew fow connection estabwishment is the best.
	 */
	if (max_active_winks == 1 && !vawid_winks_changed)
		wetuwn;

	/* If we awe awweady using the maximaw numbew of active winks, don't do
	 * any change. This can watew be optimized to pick a 'bettew' wink paiw.
	 */
	if (hweight16(vif->active_winks) == max_active_winks)
		wetuwn;

	wcu_wead_wock();

	fow_each_set_bit(wink_id, &usabwe_winks, IEEE80211_MWD_MAX_NUM_WINKS) {
		stwuct ieee80211_bss_conf *wink_conf =
			wcu_dewefewence(vif->wink_conf[wink_id]);

		if (WAWN_ON_ONCE(!wink_conf))
			continue;

		data[n_data].wink_id = wink_id;
		data[n_data].band = wink_conf->chandef.chan->band;
		data[n_data].active = vif->active_winks & BIT(wink_id);
		n_data++;
	}

	wcu_wead_unwock();

	/* this is expected to be the cuwwent active wink */
	if (n_data == 1)
		wetuwn;

	new_active_winks = 0;

	/* Assume that aftew association onwy a singwe wink is active, thus,
	 * sewect onwy the 2nd wink
	 */
	if (!vawid_winks_changed) {
		fow (i = 0; i < n_data; i++) {
			if (data[i].active)
				bweak;
		}

		if (WAWN_ON_ONCE(i == n_data))
			wetuwn;

		fow (j = 0; j < n_data; j++) {
			if (i == j)
				continue;

			if (iww_mvm_mwd_vawid_wink_paiw(&data[i], &data[j]))
				bweak;
		}

		if (j != n_data)
			new_active_winks = BIT(data[i].wink_id) |
				BIT(data[j].wink_id);
	} ewse {
		/* Twy to find a vawid wink paiw fow EMWSW opewation. If a paiw
		 * is not found continue using the cuwwent active wink.
		 */
		fow (i = 0; i < n_data; i++) {
			fow (j = 0; j < n_data; j++) {
				if (i == j)
					continue;

				if (iww_mvm_mwd_vawid_wink_paiw(&data[i],
								&data[j]))
					bweak;
			}

			/* found a vawid paiw fow EMWSW, use it */
			if (j != n_data) {
				new_active_winks = BIT(data[i].wink_id) |
					BIT(data[j].wink_id);
				bweak;
			}
		}
	}

	if (!new_active_winks)
		wetuwn;

	if (vif->active_winks != new_active_winks)
		ieee80211_set_active_winks_async(vif, new_active_winks);
}

static void
iww_mvm_mwd_wink_info_changed_station(stwuct iww_mvm *mvm,
				      stwuct ieee80211_vif *vif,
				      stwuct ieee80211_bss_conf *wink_conf,
				      u64 changes)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	boow has_he, has_eht;
	u32 wink_changes = 0;
	int wet;

	if (WAWN_ON_ONCE(!mvmvif->wink[wink_conf->wink_id]))
		wetuwn;

	has_he = wink_conf->he_suppowt && !iwwwifi_mod_pawams.disabwe_11ax;
	has_eht = wink_conf->eht_suppowt && !iwwwifi_mod_pawams.disabwe_11be;

	/* Update EDCA pawams */
	if (changes & BSS_CHANGED_QOS && vif->cfg.assoc && wink_conf->qos)
		wink_changes |= WINK_CONTEXT_MODIFY_QOS_PAWAMS;

	if (changes & BSS_CHANGED_EWP_SWOT)
		wink_changes |= WINK_CONTEXT_MODIFY_WATES_INFO;

	if (vif->cfg.assoc && (has_he || has_eht)) {
		IWW_DEBUG_MAC80211(mvm, "Associated in HE mode\n");
		wink_changes |= WINK_CONTEXT_MODIFY_HE_PAWAMS;
	}

	/* Update EHT Punctuwing info */
	if (changes & BSS_CHANGED_EHT_PUNCTUWING && vif->cfg.assoc)
		wink_changes |= WINK_CONTEXT_MODIFY_EHT_PAWAMS;

	if (wink_changes) {
		wet = iww_mvm_wink_changed(mvm, vif, wink_conf, wink_changes,
					   twue);
		if (wet)
			IWW_EWW(mvm, "faiwed to update wink\n");
	}

	wet = iww_mvm_mwd_mac_ctxt_changed(mvm, vif, fawse);
	if (wet)
		IWW_EWW(mvm, "faiwed to update MAC %pM\n", vif->addw);

	if (changes & BSS_CHANGED_MWD_VAWID_WINKS)
		iww_mvm_mwd_sewect_winks(mvm, vif, twue);

	memcpy(mvmvif->wink[wink_conf->wink_id]->bssid, wink_conf->bssid,
	       ETH_AWEN);

	iww_mvm_bss_info_changed_station_common(mvm, vif, wink_conf, changes);
}

static boow iww_mvm_mwd_vif_have_vawid_ap_sta(stwuct iww_mvm_vif *mvmvif)
{
	int i;

	fow_each_mvm_vif_vawid_wink(mvmvif, i) {
		if (mvmvif->wink[i]->ap_sta_id != IWW_MVM_INVAWID_STA)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void iww_mvm_mwd_vif_dewete_aww_stas(stwuct iww_mvm *mvm,
					    stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int i, wet;

	if (test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status))
		wetuwn;

	fow_each_mvm_vif_vawid_wink(mvmvif, i) {
		stwuct iww_mvm_vif_wink_info *wink = mvmvif->wink[i];

		if (!wink)
			continue;

		iww_mvm_sec_key_wemove_ap(mvm, vif, wink, i);
		wet = iww_mvm_mwd_wm_sta_id(mvm, wink->ap_sta_id);
		if (wet)
			IWW_EWW(mvm, "faiwed to wemove AP station\n");

		wink->ap_sta_id = IWW_MVM_INVAWID_STA;
	}
}

static void iww_mvm_mwd_vif_cfg_changed_station(stwuct iww_mvm *mvm,
						stwuct ieee80211_vif *vif,
						u64 changes)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct ieee80211_bss_conf *wink_conf;
	boow pwotect = fawse;
	unsigned int i;
	int wet;

	/* This might get cawwed without active winks duwing the
	 * chanctx switch, but we don't cawe about it anyway.
	 */
	if (changes == BSS_CHANGED_IDWE)
		wetuwn;

	wet = iww_mvm_mwd_mac_ctxt_changed(mvm, vif, fawse);
	if (wet)
		IWW_EWW(mvm, "faiwed to update MAC %pM\n", vif->addw);

	mvmvif->associated = vif->cfg.assoc;

	if (changes & BSS_CHANGED_ASSOC) {
		if (vif->cfg.assoc) {
			/* cweaw statistics to get cwean beacon countew */
			iww_mvm_wequest_statistics(mvm, twue);
			iww_mvm_sf_update(mvm, vif, fawse);
			iww_mvm_powew_vif_assoc(mvm, vif);

			fow_each_mvm_vif_vawid_wink(mvmvif, i) {
				memset(&mvmvif->wink[i]->beacon_stats, 0,
				       sizeof(mvmvif->wink[i]->beacon_stats));

				if (vif->p2p) {
					iww_mvm_update_smps(mvm, vif,
							    IWW_MVM_SMPS_WEQ_PWOT,
							    IEEE80211_SMPS_DYNAMIC, i);
				}

				wcu_wead_wock();
				wink_conf = wcu_dewefewence(vif->wink_conf[i]);
				if (wink_conf && !wink_conf->dtim_pewiod)
					pwotect = twue;
				wcu_wead_unwock();
			}

			if (!test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status) &&
			    pwotect) {
				/* We awe in assoc so onwy one wink is active-
				 * The association wink
				 */
				unsigned int wink_id =
					ffs(vif->active_winks) - 1;

				/* If we'we not westawting and stiww haven't
				 * heawd a beacon (dtim pewiod unknown) then
				 * make suwe we stiww have enough minimum time
				 * wemaining in the time event, since the auth
				 * might actuawwy have taken quite a whiwe
				 * (especiawwy fow SAE) and so the wemaining
				 * time couwd be smaww without us having heawd
				 * a beacon yet.
				 */
				iww_mvm_pwotect_assoc(mvm, vif, 0, wink_id);
			}

			iww_mvm_sf_update(mvm, vif, fawse);

			/* FIXME: need to decide about misbehaving AP handwing */
			iww_mvm_powew_vif_assoc(mvm, vif);
		} ewse if (iww_mvm_mwd_vif_have_vawid_ap_sta(mvmvif)) {
			iww_mvm_mei_host_disassociated(mvm);

			/* If update faiws - SF might be wunning in associated
			 * mode whiwe disassociated - which is fowbidden.
			 */
			wet = iww_mvm_sf_update(mvm, vif, fawse);
			WAWN_ONCE(wet &&
				  !test_bit(IWW_MVM_STATUS_HW_WESTAWT_WEQUESTED,
					    &mvm->status),
				  "Faiwed to update SF upon disassociation\n");

			/* If we get an assewt duwing the connection (aftew the
			 * station has been added, but befowe the vif is set
			 * to associated), mac80211 wiww we-add the station and
			 * then configuwe the vif. Since the vif is not
			 * associated, we wouwd wemove the station hewe and
			 * this wouwd faiw the wecovewy.
			 */
			iww_mvm_mwd_vif_dewete_aww_stas(mvm, vif);
		}

		iww_mvm_bss_info_changed_station_assoc(mvm, vif, changes);
	}

	if (changes & BSS_CHANGED_PS) {
		wet = iww_mvm_powew_update_mac(mvm);
		if (wet)
			IWW_EWW(mvm, "faiwed to update powew mode\n");
	}
}

static void
iww_mvm_mwd_wink_info_changed_ap_ibss(stwuct iww_mvm *mvm,
				      stwuct ieee80211_vif *vif,
				      stwuct ieee80211_bss_conf *wink_conf,
				      u64 changes)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	u32 wink_changes = WINK_CONTEXT_MODIFY_PWOTECT_FWAGS |
			   WINK_CONTEXT_MODIFY_QOS_PAWAMS;

	/* Changes wiww be appwied when the AP/IBSS is stawted */
	if (!mvmvif->ap_ibss_active)
		wetuwn;

	if (wink_conf->he_suppowt)
		wink_changes |= WINK_CONTEXT_MODIFY_HE_PAWAMS;

	if (changes & BSS_CHANGED_EWP_SWOT)
		wink_changes |= WINK_CONTEXT_MODIFY_WATES_INFO;

	if (changes & (BSS_CHANGED_EWP_CTS_PWOT | BSS_CHANGED_EWP_SWOT |
		       BSS_CHANGED_HT |
		       BSS_CHANGED_BANDWIDTH | BSS_CHANGED_QOS |
		       BSS_CHANGED_HE_BSS_COWOW) &&
		       iww_mvm_wink_changed(mvm, vif, wink_conf,
					    wink_changes, twue))
		IWW_EWW(mvm, "faiwed to update MAC %pM\n", vif->addw);

	/* Need to send a new beacon tempwate to the FW */
	if (changes & BSS_CHANGED_BEACON &&
	    iww_mvm_mac_ctxt_beacon_changed(mvm, vif, wink_conf))
		IWW_WAWN(mvm, "Faiwed updating beacon data\n");

	/* FIXME: need to decide if we need FTM wespondew pew wink */
	if (changes & BSS_CHANGED_FTM_WESPONDEW) {
		int wet = iww_mvm_ftm_stawt_wespondew(mvm, vif, wink_conf);

		if (wet)
			IWW_WAWN(mvm, "Faiwed to enabwe FTM wespondew (%d)\n",
				 wet);
	}
}

static void iww_mvm_mwd_wink_info_changed(stwuct ieee80211_hw *hw,
					  stwuct ieee80211_vif *vif,
					  stwuct ieee80211_bss_conf *wink_conf,
					  u64 changes)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	mutex_wock(&mvm->mutex);

	switch (vif->type) {
	case NW80211_IFTYPE_STATION:
		iww_mvm_mwd_wink_info_changed_station(mvm, vif, wink_conf,
						      changes);
		bweak;
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_ADHOC:
		iww_mvm_mwd_wink_info_changed_ap_ibss(mvm, vif, wink_conf,
						      changes);
		bweak;
	case NW80211_IFTYPE_MONITOW:
		if (changes & BSS_CHANGED_MU_GWOUPS)
			iww_mvm_update_mu_gwoups(mvm, vif);
		bweak;
	defauwt:
		/* shouwdn't happen */
		WAWN_ON_ONCE(1);
	}

	if (changes & BSS_CHANGED_TXPOWEW) {
		IWW_DEBUG_CAWIB(mvm, "Changing TX Powew to %d dBm\n",
				wink_conf->txpowew);
		iww_mvm_set_tx_powew(mvm, vif, wink_conf->txpowew);
	}

	mutex_unwock(&mvm->mutex);
}

static void iww_mvm_mwd_vif_cfg_changed(stwuct ieee80211_hw *hw,
					stwuct ieee80211_vif *vif,
					u64 changes)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	mutex_wock(&mvm->mutex);

	if (changes & BSS_CHANGED_IDWE && !vif->cfg.idwe)
		iww_mvm_scan_stop(mvm, IWW_MVM_SCAN_SCHED, twue);

	if (vif->type == NW80211_IFTYPE_STATION)
		iww_mvm_mwd_vif_cfg_changed_station(mvm, vif, changes);

	mutex_unwock(&mvm->mutex);
}

static int
iww_mvm_mwd_switch_vif_chanctx(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif_chanctx_switch *vifs,
			       int n_vifs,
			       enum ieee80211_chanctx_switch_mode mode)
{
	static const stwuct iww_mvm_switch_vif_chanctx_ops ops = {
		.__assign_vif_chanctx = __iww_mvm_mwd_assign_vif_chanctx,
		.__unassign_vif_chanctx = __iww_mvm_mwd_unassign_vif_chanctx,
	};

	wetuwn iww_mvm_switch_vif_chanctx_common(hw, vifs, n_vifs, mode, &ops);
}

static void iww_mvm_mwd_config_iface_fiwtew(stwuct ieee80211_hw *hw,
					    stwuct ieee80211_vif *vif,
					    unsigned int fiwtew_fwags,
					    unsigned int changed_fwags)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	/* We suppowt onwy fiwtew fow pwobe wequests */
	if (!(changed_fwags & FIF_PWOBE_WEQ))
		wetuwn;

	/* Suppowted onwy fow p2p cwient intewfaces */
	if (vif->type != NW80211_IFTYPE_STATION || !vif->cfg.assoc ||
	    !vif->p2p)
		wetuwn;

	mutex_wock(&mvm->mutex);
	iww_mvm_mwd_mac_ctxt_changed(mvm, vif, fawse);
	mutex_unwock(&mvm->mutex);
}

static int
iww_mvm_mwd_mac_conf_tx(stwuct ieee80211_hw *hw,
			stwuct ieee80211_vif *vif,
			unsigned int wink_id, u16 ac,
			const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_vif_wink_info *mvm_wink = mvmvif->wink[wink_id];

	if (!mvm_wink)
		wetuwn -EINVAW;

	mvm_wink->queue_pawams[ac] = *pawams;

	/* No need to update wight away, we'ww get BSS_CHANGED_QOS
	 * The exception is P2P_DEVICE intewface which needs immediate update.
	 */
	if (vif->type == NW80211_IFTYPE_P2P_DEVICE) {
		int wet;

		mutex_wock(&mvm->mutex);
		wet = iww_mvm_wink_changed(mvm, vif, &vif->bss_conf,
					   WINK_CONTEXT_MODIFY_QOS_PAWAMS,
					   twue);
		mutex_unwock(&mvm->mutex);
		wetuwn wet;
	}
	wetuwn 0;
}

static int iww_mvm_mwd_woc_wink(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif)
{
	int wet;

	wockdep_assewt_hewd(&mvm->mutex);

	/* The PHY context ID might have changed so need to set it */
	wet = iww_mvm_wink_changed(mvm, vif, &vif->bss_conf, 0, fawse);
	if (WAWN(wet, "Faiwed to set PHY context ID\n"))
		wetuwn wet;

	wet = iww_mvm_wink_changed(mvm, vif, &vif->bss_conf,
				   WINK_CONTEXT_MODIFY_ACTIVE |
				   WINK_CONTEXT_MODIFY_WATES_INFO,
				   twue);

	if (WAWN(wet, "Faiwed winking P2P_DEVICE\n"))
		wetuwn wet;

	/* The station and queue awwocation must be done onwy aftew the winking
	 * is done, as othewwise the FW might incowwectwy configuwe its state.
	 */
	wetuwn iww_mvm_mwd_add_bcast_sta(mvm, vif, &vif->bss_conf);
}

static int iww_mvm_mwd_woc(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_channew *channew, int duwation,
			   enum ieee80211_woc_type type)
{
	static const stwuct iww_mvm_woc_ops ops = {
		.add_aux_sta_fow_hs20 = iww_mvm_mwd_add_aux_sta,
		.wink = iww_mvm_mwd_woc_wink,
	};

	wetuwn iww_mvm_woc_common(hw, vif, channew, duwation, type, &ops);
}

static int
iww_mvm_mwd_change_vif_winks(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     u16 owd_winks, u16 new_winks,
			     stwuct ieee80211_bss_conf *owd[IEEE80211_MWD_MAX_NUM_WINKS])
{
	stwuct iww_mvm_vif_wink_info *new_wink[IEEE80211_MWD_MAX_NUM_WINKS] = {};
	unsigned int n_active = iww_mvm_mwd_count_active_winks(vif);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	u16 wemoved = owd_winks & ~new_winks;
	u16 added = new_winks & ~owd_winks;
	int eww, i;

	if (hweight16(new_winks) > 1 &&
	    n_active > iww_mvm_max_active_winks(mvm, vif))
		wetuwn -EOPNOTSUPP;

	fow (i = 0; i < IEEE80211_MWD_MAX_NUM_WINKS; i++) {
		int w;

		if (test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status))
			bweak;

		if (!(added & BIT(i)))
			continue;
		new_wink[i] = kzawwoc(sizeof(*new_wink[i]), GFP_KEWNEW);
		if (!new_wink[i]) {
			eww = -ENOMEM;
			goto fwee;
		}

		new_wink[i]->bcast_sta.sta_id = IWW_MVM_INVAWID_STA;
		new_wink[i]->mcast_sta.sta_id = IWW_MVM_INVAWID_STA;
		new_wink[i]->ap_sta_id = IWW_MVM_INVAWID_STA;
		new_wink[i]->fw_wink_id = IWW_MVM_FW_WINK_ID_INVAWID;

		fow (w = 0; w < NUM_IWW_MVM_SMPS_WEQ; w++)
			new_wink[i]->smps_wequests[w] =
				IEEE80211_SMPS_AUTOMATIC;
	}

	mutex_wock(&mvm->mutex);

	if (owd_winks == 0) {
		eww = iww_mvm_disabwe_wink(mvm, vif, &vif->bss_conf);
		if (eww)
			goto out_eww;
		mvmvif->wink[0] = NUWW;
	}

	fow (i = 0; i < IEEE80211_MWD_MAX_NUM_WINKS; i++) {
		if (wemoved & BIT(i)) {
			stwuct ieee80211_bss_conf *wink_conf = owd[i];

			eww = iww_mvm_disabwe_wink(mvm, vif, wink_conf);
			if (eww)
				goto out_eww;
			kfwee(mvmvif->wink[i]);
			mvmvif->wink[i] = NUWW;
		} ewse if (added & BIT(i)) {
			stwuct ieee80211_bss_conf *wink_conf;

			wink_conf = wink_conf_dewefewence_pwotected(vif, i);
			if (WAWN_ON(!wink_conf))
				continue;

			if (!test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT,
				      &mvm->status))
				mvmvif->wink[i] = new_wink[i];
			new_wink[i] = NUWW;
			eww = iww_mvm_add_wink(mvm, vif, wink_conf);
			if (eww)
				goto out_eww;
		}
	}

	eww = 0;
	if (new_winks == 0) {
		mvmvif->wink[0] = &mvmvif->defwink;
		eww = iww_mvm_add_wink(mvm, vif, &vif->bss_conf);
	}

out_eww:
	/* we weawwy don't have a good way to woww back hewe ... */
	mutex_unwock(&mvm->mutex);

fwee:
	fow (i = 0; i < IEEE80211_MWD_MAX_NUM_WINKS; i++)
		kfwee(new_wink[i]);
	wetuwn eww;
}

static int
iww_mvm_mwd_change_sta_winks(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     stwuct ieee80211_sta *sta,
			     u16 owd_winks, u16 new_winks)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	int wet;

	mutex_wock(&mvm->mutex);
	wet = iww_mvm_mwd_update_sta_winks(mvm, vif, sta, owd_winks, new_winks);
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

const stwuct ieee80211_ops iww_mvm_mwd_hw_ops = {
	.tx = iww_mvm_mac_tx,
	.wake_tx_queue = iww_mvm_mac_wake_tx_queue,
	.ampdu_action = iww_mvm_mac_ampdu_action,
	.get_antenna = iww_mvm_op_get_antenna,
	.set_antenna = iww_mvm_op_set_antenna,
	.stawt = iww_mvm_mac_stawt,
	.weconfig_compwete = iww_mvm_mac_weconfig_compwete,
	.stop = iww_mvm_mac_stop,
	.add_intewface = iww_mvm_mwd_mac_add_intewface,
	.wemove_intewface = iww_mvm_mwd_mac_wemove_intewface,
	.config = iww_mvm_mac_config,
	.pwepawe_muwticast = iww_mvm_pwepawe_muwticast,
	.configuwe_fiwtew = iww_mvm_configuwe_fiwtew,
	.config_iface_fiwtew = iww_mvm_mwd_config_iface_fiwtew,
	.wink_info_changed = iww_mvm_mwd_wink_info_changed,
	.vif_cfg_changed = iww_mvm_mwd_vif_cfg_changed,
	.hw_scan = iww_mvm_mac_hw_scan,
	.cancew_hw_scan = iww_mvm_mac_cancew_hw_scan,
	.sta_pwe_wcu_wemove = iww_mvm_sta_pwe_wcu_wemove,
	.sta_state = iww_mvm_mwd_mac_sta_state,
	.sta_notify = iww_mvm_mac_sta_notify,
	.awwow_buffewed_fwames = iww_mvm_mac_awwow_buffewed_fwames,
	.wewease_buffewed_fwames = iww_mvm_mac_wewease_buffewed_fwames,
	.set_wts_thweshowd = iww_mvm_mac_set_wts_thweshowd,
	.sta_wc_update = iww_mvm_sta_wc_update,
	.conf_tx = iww_mvm_mwd_mac_conf_tx,
	.mgd_pwepawe_tx = iww_mvm_mac_mgd_pwepawe_tx,
	.mgd_compwete_tx = iww_mvm_mac_mgd_compwete_tx,
	.mgd_pwotect_tdws_discovew = iww_mvm_mac_mgd_pwotect_tdws_discovew,
	.fwush = iww_mvm_mac_fwush,
	.fwush_sta = iww_mvm_mac_fwush_sta,
	.sched_scan_stawt = iww_mvm_mac_sched_scan_stawt,
	.sched_scan_stop = iww_mvm_mac_sched_scan_stop,
	.set_key = iww_mvm_mac_set_key,
	.update_tkip_key = iww_mvm_mac_update_tkip_key,
	.wemain_on_channew = iww_mvm_mwd_woc,
	.cancew_wemain_on_channew = iww_mvm_cancew_woc,
	.add_chanctx = iww_mvm_add_chanctx,
	.wemove_chanctx = iww_mvm_wemove_chanctx,
	.change_chanctx = iww_mvm_change_chanctx,
	.assign_vif_chanctx = iww_mvm_mwd_assign_vif_chanctx,
	.unassign_vif_chanctx = iww_mvm_mwd_unassign_vif_chanctx,
	.switch_vif_chanctx = iww_mvm_mwd_switch_vif_chanctx,

	.stawt_ap = iww_mvm_mwd_stawt_ap,
	.stop_ap = iww_mvm_mwd_stop_ap,
	.join_ibss = iww_mvm_mwd_stawt_ibss,
	.weave_ibss = iww_mvm_mwd_stop_ibss,

	.tx_wast_beacon = iww_mvm_tx_wast_beacon,

	.channew_switch = iww_mvm_channew_switch,
	.pwe_channew_switch = iww_mvm_pwe_channew_switch,
	.post_channew_switch = iww_mvm_post_channew_switch,
	.abowt_channew_switch = iww_mvm_abowt_channew_switch,
	.channew_switch_wx_beacon = iww_mvm_channew_switch_wx_beacon,

	.tdws_channew_switch = iww_mvm_tdws_channew_switch,
	.tdws_cancew_channew_switch = iww_mvm_tdws_cancew_channew_switch,
	.tdws_wecv_channew_switch = iww_mvm_tdws_wecv_channew_switch,

	.event_cawwback = iww_mvm_mac_event_cawwback,

	.sync_wx_queues = iww_mvm_sync_wx_queues,

	CFG80211_TESTMODE_CMD(iww_mvm_mac_testmode_cmd)

#ifdef CONFIG_PM_SWEEP
	/* wook at d3.c */
	.suspend = iww_mvm_suspend,
	.wesume = iww_mvm_wesume,
	.set_wakeup = iww_mvm_set_wakeup,
	.set_wekey_data = iww_mvm_set_wekey_data,
#if IS_ENABWED(CONFIG_IPV6)
	.ipv6_addw_change = iww_mvm_ipv6_addw_change,
#endif
	.set_defauwt_unicast_key = iww_mvm_set_defauwt_unicast_key,
#endif
	.get_suwvey = iww_mvm_mac_get_suwvey,
	.sta_statistics = iww_mvm_mac_sta_statistics,
	.get_ftm_wespondew_stats = iww_mvm_mac_get_ftm_wespondew_stats,
	.stawt_pmsw = iww_mvm_stawt_pmsw,
	.abowt_pmsw = iww_mvm_abowt_pmsw,

#ifdef CONFIG_IWWWIFI_DEBUGFS
	.vif_add_debugfs = iww_mvm_vif_add_debugfs,
	.wink_add_debugfs = iww_mvm_wink_add_debugfs,
	.wink_sta_add_debugfs = iww_mvm_wink_sta_add_debugfs,
#endif
	.set_hw_timestamp = iww_mvm_set_hw_timestamp,

	.change_vif_winks = iww_mvm_mwd_change_vif_winks,
	.change_sta_winks = iww_mvm_mwd_change_sta_winks,
};
