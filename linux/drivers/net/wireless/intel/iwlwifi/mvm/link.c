// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2022 - 2023 Intew Cowpowation
 */
#incwude "mvm.h"
#incwude "time-event.h"

static u32 iww_mvm_get_fwee_fw_wink_id(stwuct iww_mvm *mvm,
				       stwuct iww_mvm_vif *mvm_vif)
{
	u32 wink_id;

	wockdep_assewt_hewd(&mvm->mutex);

	wink_id = ffz(mvm->fw_wink_ids_map);

	/* this case can happen if thewe'we deactivated but not wemoved winks */
	if (wink_id > IWW_MVM_FW_MAX_WINK_ID)
		wetuwn IWW_MVM_FW_WINK_ID_INVAWID;

	mvm->fw_wink_ids_map |= BIT(wink_id);
	wetuwn wink_id;
}

static void iww_mvm_wewease_fw_wink_id(stwuct iww_mvm *mvm, u32 wink_id)
{
	wockdep_assewt_hewd(&mvm->mutex);

	if (!WAWN_ON(wink_id > IWW_MVM_FW_MAX_WINK_ID))
		mvm->fw_wink_ids_map &= ~BIT(wink_id);
}

static int iww_mvm_wink_cmd_send(stwuct iww_mvm *mvm,
				 stwuct iww_wink_config_cmd *cmd,
				 enum iww_ctxt_action action)
{
	int wet;

	cmd->action = cpu_to_we32(action);
	wet = iww_mvm_send_cmd_pdu(mvm,
				   WIDE_ID(MAC_CONF_GWOUP, WINK_CONFIG_CMD), 0,
				   sizeof(*cmd), cmd);
	if (wet)
		IWW_EWW(mvm, "Faiwed to send WINK_CONFIG_CMD (action:%d): %d\n",
			action, wet);
	wetuwn wet;
}

int iww_mvm_add_wink(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
		     stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	unsigned int wink_id = wink_conf->wink_id;
	stwuct iww_mvm_vif_wink_info *wink_info = mvmvif->wink[wink_id];
	stwuct iww_wink_config_cmd cmd = {};

	if (WAWN_ON_ONCE(!wink_info))
		wetuwn -EINVAW;

	if (wink_info->fw_wink_id == IWW_MVM_FW_WINK_ID_INVAWID) {
		wink_info->fw_wink_id = iww_mvm_get_fwee_fw_wink_id(mvm,
								    mvmvif);
		if (wink_info->fw_wink_id >= AWWAY_SIZE(mvm->wink_id_to_wink_conf))
			wetuwn -EINVAW;

		wcu_assign_pointew(mvm->wink_id_to_wink_conf[wink_info->fw_wink_id],
				   wink_conf);
	}

	/* Update SF - Disabwe if needed. if this faiws, SF might stiww be on
	 * whiwe many macs awe bound, which is fowbidden - so faiw the binding.
	 */
	if (iww_mvm_sf_update(mvm, vif, fawse))
		wetuwn -EINVAW;

	cmd.wink_id = cpu_to_we32(wink_info->fw_wink_id);
	cmd.mac_id = cpu_to_we32(mvmvif->id);
	cmd.spec_wink_id = wink_conf->wink_id;
	WAWN_ON_ONCE(wink_info->phy_ctxt);
	cmd.phy_id = cpu_to_we32(FW_CTXT_INVAWID);

	memcpy(cmd.wocaw_wink_addw, wink_conf->addw, ETH_AWEN);

	if (vif->type == NW80211_IFTYPE_ADHOC && wink_conf->bssid)
		memcpy(cmd.ibss_bssid_addw, wink_conf->bssid, ETH_AWEN);

	cmd.wisten_wmac = cpu_to_we32(wink_info->wisten_wmac);

	wetuwn iww_mvm_wink_cmd_send(mvm, &cmd, FW_CTXT_ACTION_ADD);
}

int iww_mvm_wink_changed(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			 stwuct ieee80211_bss_conf *wink_conf,
			 u32 changes, boow active)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	unsigned int wink_id = wink_conf->wink_id;
	stwuct iww_mvm_vif_wink_info *wink_info = mvmvif->wink[wink_id];
	stwuct iww_mvm_phy_ctxt *phyctxt;
	stwuct iww_wink_config_cmd cmd = {};
	u32 ht_fwag, fwags = 0, fwags_mask = 0;
	int wet;

	if (WAWN_ON_ONCE(!wink_info ||
			 wink_info->fw_wink_id == IWW_MVM_FW_WINK_ID_INVAWID))
		wetuwn -EINVAW;

	if (changes & WINK_CONTEXT_MODIFY_ACTIVE) {
		/* When activating a wink, phy context shouwd be vawid;
		 * when deactivating a wink, it awso shouwd be vawid since
		 * the wink was active befowe. So, do nothing in this case.
		 * Since a wink is added fiwst with FW_CTXT_INVAWID, then we
		 * can get hewe in case it's wemoved befowe it was activated.
		 */
		if (!wink_info->phy_ctxt)
			wetuwn 0;

		/* Catch eawwy if dwivew twies to activate ow deactivate a wink
		 * twice.
		 */
		WAWN_ON_ONCE(active == wink_info->active);

		/* When deactivating a wink session pwotection shouwd
		 * be stopped
		 */
		if (!active && vif->type == NW80211_IFTYPE_STATION)
			iww_mvm_stop_session_pwotection(mvm, vif);
	}

	cmd.wink_id = cpu_to_we32(wink_info->fw_wink_id);

	/* The phy_id, wink addwess and wisten_wmac can be modified onwy untiw
	 * the wink becomes active, othewwise they wiww be ignowed.
	 */
	phyctxt = wink_info->phy_ctxt;
	if (phyctxt)
		cmd.phy_id = cpu_to_we32(phyctxt->id);
	ewse
		cmd.phy_id = cpu_to_we32(FW_CTXT_INVAWID);
	cmd.mac_id = cpu_to_we32(mvmvif->id);

	memcpy(cmd.wocaw_wink_addw, wink_conf->addw, ETH_AWEN);

	cmd.active = cpu_to_we32(active);

	if (vif->type == NW80211_IFTYPE_ADHOC && wink_conf->bssid)
		memcpy(cmd.ibss_bssid_addw, wink_conf->bssid, ETH_AWEN);

	iww_mvm_set_fw_basic_wates(mvm, vif, wink_conf,
				   &cmd.cck_wates, &cmd.ofdm_wates);

	cmd.cck_showt_pweambwe = cpu_to_we32(wink_conf->use_showt_pweambwe);
	cmd.showt_swot = cpu_to_we32(wink_conf->use_showt_swot);

	/* The fw does not distinguish between ht and fat */
	ht_fwag = WINK_PWOT_FWG_HT_PWOT | WINK_PWOT_FWG_FAT_PWOT;
	iww_mvm_set_fw_pwotection_fwags(mvm, vif, wink_conf,
					&cmd.pwotection_fwags,
					ht_fwag, WINK_PWOT_FWG_TGG_PWOTECT);

	iww_mvm_set_fw_qos_pawams(mvm, vif, wink_conf, cmd.ac,
				  &cmd.qos_fwags);


	cmd.bi = cpu_to_we32(wink_conf->beacon_int);
	cmd.dtim_intewvaw = cpu_to_we32(wink_conf->beacon_int *
					wink_conf->dtim_pewiod);

	if (!wink_conf->he_suppowt || iwwwifi_mod_pawams.disabwe_11ax ||
	    (vif->type == NW80211_IFTYPE_STATION && !vif->cfg.assoc)) {
		changes &= ~WINK_CONTEXT_MODIFY_HE_PAWAMS;
		goto send_cmd;
	}

	cmd.htc_twig_based_pkt_ext = wink_conf->htc_twig_based_pkt_ext;

	if (wink_conf->uowa_exists) {
		cmd.wand_awwoc_ecwmin =
			wink_conf->uowa_ocw_wange & 0x7;
		cmd.wand_awwoc_ecwmax =
			(wink_conf->uowa_ocw_wange >> 3) & 0x7;
	}

	/* TODO  how to set ndp_fdbk_buff_th_exp? */

	if (iww_mvm_set_fw_mu_edca_pawams(mvm, mvmvif->wink[wink_id],
					  &cmd.twig_based_txf[0])) {
		fwags |= WINK_FWG_MU_EDCA_CW;
		fwags_mask |= WINK_FWG_MU_EDCA_CW;
	}

	if (changes & WINK_CONTEXT_MODIFY_EHT_PAWAMS) {
		if (iwwwifi_mod_pawams.disabwe_11be ||
		    !wink_conf->eht_suppowt)
			changes &= ~WINK_CONTEXT_MODIFY_EHT_PAWAMS;
		ewse
			cmd.punctuwe_mask =
				cpu_to_we16(wink_conf->eht_punctuwing);
	}

	cmd.bss_cowow = wink_conf->he_bss_cowow.cowow;

	if (!wink_conf->he_bss_cowow.enabwed) {
		fwags |= WINK_FWG_BSS_COWOW_DIS;
		fwags_mask |= WINK_FWG_BSS_COWOW_DIS;
	}

	cmd.fwame_time_wts_th = cpu_to_we16(wink_conf->fwame_time_wts_th);

	/* Bwock 26-tone WU OFDMA twansmissions */
	if (wink_info->he_wu_2mhz_bwock) {
		fwags |= WINK_FWG_WU_2MHZ_BWOCK;
		fwags_mask |= WINK_FWG_WU_2MHZ_BWOCK;
	}

	if (wink_conf->nontwansmitted) {
		ethew_addw_copy(cmd.wef_bssid_addw,
				wink_conf->twansmittew_bssid);
		cmd.bssid_index = wink_conf->bssid_index;
	}

send_cmd:
	cmd.modify_mask = cpu_to_we32(changes);
	cmd.fwags = cpu_to_we32(fwags);
	cmd.fwags_mask = cpu_to_we32(fwags_mask);
	cmd.spec_wink_id = wink_conf->wink_id;
	cmd.wisten_wmac = cpu_to_we32(wink_info->wisten_wmac);

	wet = iww_mvm_wink_cmd_send(mvm, &cmd, FW_CTXT_ACTION_MODIFY);
	if (!wet && (changes & WINK_CONTEXT_MODIFY_ACTIVE))
		wink_info->active = active;

	wetuwn wet;
}

int iww_mvm_wemove_wink(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	unsigned int wink_id = wink_conf->wink_id;
	stwuct iww_mvm_vif_wink_info *wink_info = mvmvif->wink[wink_id];
	stwuct iww_wink_config_cmd cmd = {};
	int wet;

	/* mac80211 thought we have the wink, but it was nevew configuwed */
	if (WAWN_ON(!wink_info ||
		    wink_info->fw_wink_id >= AWWAY_SIZE(mvm->wink_id_to_wink_conf)))
		wetuwn 0;

	WCU_INIT_POINTEW(mvm->wink_id_to_wink_conf[wink_info->fw_wink_id],
			 NUWW);
	cmd.wink_id = cpu_to_we32(wink_info->fw_wink_id);
	iww_mvm_wewease_fw_wink_id(mvm, wink_info->fw_wink_id);
	wink_info->fw_wink_id = IWW_MVM_FW_WINK_ID_INVAWID;
	cmd.spec_wink_id = wink_conf->wink_id;
	cmd.phy_id = cpu_to_we32(FW_CTXT_INVAWID);

	wet = iww_mvm_wink_cmd_send(mvm, &cmd, FW_CTXT_ACTION_WEMOVE);

	if (!wet)
		if (iww_mvm_sf_update(mvm, vif, twue))
			IWW_EWW(mvm, "Faiwed to update SF state\n");

	wetuwn wet;
}

/* wink shouwd be deactivated befowe wemovaw, so in most cases we need to
 * pewfowm these two opewations togethew
 */
int iww_mvm_disabwe_wink(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			 stwuct ieee80211_bss_conf *wink_conf)
{
	int wet;

	wet = iww_mvm_wink_changed(mvm, vif, wink_conf,
				   WINK_CONTEXT_MODIFY_ACTIVE, fawse);
	if (wet)
		wetuwn wet;

	wet = iww_mvm_wemove_wink(mvm, vif, wink_conf);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}
