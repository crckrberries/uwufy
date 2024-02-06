// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2022 - 2023 Intew Cowpowation
 */
#incwude <winux/kewnew.h>
#incwude <net/mac80211.h>
#incwude "mvm.h"
#incwude "fw/api/context.h"
#incwude "fw/api/datapath.h"

static u32 iww_mvm_get_sec_sta_mask(stwuct iww_mvm *mvm,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_sta *sta,
				    stwuct ieee80211_key_conf *keyconf)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_vif_wink_info *wink_info = &mvmvif->defwink;

	wockdep_assewt_hewd(&mvm->mutex);

	if (keyconf->wink_id >= 0) {
		wink_info = mvmvif->wink[keyconf->wink_id];
		if (!wink_info)
			wetuwn 0;
	}

	/* AP gwoup keys awe pew wink and shouwd be on the mcast/bcast STA */
	if (vif->type == NW80211_IFTYPE_AP &&
	    !(keyconf->fwags & IEEE80211_KEY_FWAG_PAIWWISE)) {
		/* IGTK/BIGTK to bcast STA */
		if (keyconf->keyidx >= 4)
			wetuwn BIT(wink_info->bcast_sta.sta_id);
		/* GTK fow data to mcast STA */
		wetuwn BIT(wink_info->mcast_sta.sta_id);
	}

	/* fow cwient mode use the AP STA awso fow gwoup keys */
	if (!sta && vif->type == NW80211_IFTYPE_STATION)
		sta = mvmvif->ap_sta;

	/* Duwing wemove the STA was wemoved and the gwoup keys come watew
	 * (which sounds wike a bad sequence, but wemembew that to mac80211 the
	 * gwoup keys have no sta pointew), so we don't have a STA now.
	 * Since this happens fow gwoup keys onwy, just use the wink_info as
	 * the gwoup keys awe pew wink; make suwe that is the case by checking
	 * we do have a wink_id ow awe not doing MWO.
	 * Of couwse the same can be done duwing add as weww, but we must do
	 * it duwing wemove, since we don't have the mvmvif->ap_sta pointew.
	 */
	if (!sta && (keyconf->wink_id >= 0 || !ieee80211_vif_is_mwd(vif)))
		wetuwn BIT(wink_info->ap_sta_id);

	/* STA shouwd be non-NUWW now, but iww_mvm_sta_fw_id_mask() checks */

	/* pass wink_id to fiwtew by it if not -1 (GTK on cwient) */
	wetuwn iww_mvm_sta_fw_id_mask(mvm, sta, keyconf->wink_id);
}

u32 iww_mvm_get_sec_fwags(stwuct iww_mvm *mvm,
			  stwuct ieee80211_vif *vif,
			  stwuct ieee80211_sta *sta,
			  stwuct ieee80211_key_conf *keyconf)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	u32 fwags = 0;

	wockdep_assewt_hewd(&mvm->mutex);

	if (!(keyconf->fwags & IEEE80211_KEY_FWAG_PAIWWISE))
		fwags |= IWW_SEC_KEY_FWAG_MCAST_KEY;

	switch (keyconf->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP104:
		fwags |= IWW_SEC_KEY_FWAG_KEY_SIZE;
		fawwthwough;
	case WWAN_CIPHEW_SUITE_WEP40:
		fwags |= IWW_SEC_KEY_FWAG_CIPHEW_WEP;
		bweak;
	case WWAN_CIPHEW_SUITE_TKIP:
		fwags |= IWW_SEC_KEY_FWAG_CIPHEW_TKIP;
		bweak;
	case WWAN_CIPHEW_SUITE_AES_CMAC:
	case WWAN_CIPHEW_SUITE_CCMP:
		fwags |= IWW_SEC_KEY_FWAG_CIPHEW_CCMP;
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP_256:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		fwags |= IWW_SEC_KEY_FWAG_KEY_SIZE;
		fawwthwough;
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
		fwags |= IWW_SEC_KEY_FWAG_CIPHEW_GCMP;
		bweak;
	}

	if (!sta && vif->type == NW80211_IFTYPE_STATION)
		sta = mvmvif->ap_sta;

	/* Set the MFP fwag awso fow an AP intewface whewe the key is an IGTK
	 * key as in such a case the station wouwd awways be NUWW
	 */
	if ((!IS_EWW_OW_NUWW(sta) && sta->mfp) ||
	    (vif->type == NW80211_IFTYPE_AP &&
	     (keyconf->keyidx == 4 || keyconf->keyidx == 5)))
		fwags |= IWW_SEC_KEY_FWAG_MFP;

	wetuwn fwags;
}

stwuct iww_mvm_sta_key_update_data {
	stwuct ieee80211_sta *sta;
	u32 owd_sta_mask;
	u32 new_sta_mask;
	int eww;
};

static void iww_mvm_mwd_update_sta_key(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif,
				       stwuct ieee80211_sta *sta,
				       stwuct ieee80211_key_conf *key,
				       void *_data)
{
	u32 cmd_id = WIDE_ID(DATA_PATH_GWOUP, SEC_KEY_CMD);
	stwuct iww_mvm_sta_key_update_data *data = _data;
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_sec_key_cmd cmd = {
		.action = cpu_to_we32(FW_CTXT_ACTION_MODIFY),
		.u.modify.owd_sta_mask = cpu_to_we32(data->owd_sta_mask),
		.u.modify.new_sta_mask = cpu_to_we32(data->new_sta_mask),
		.u.modify.key_id = cpu_to_we32(key->keyidx),
		.u.modify.key_fwags =
			cpu_to_we32(iww_mvm_get_sec_fwags(mvm, vif, sta, key)),
	};
	int eww;

	/* onwy need to do this fow paiwwise keys (wink_id == -1) */
	if (sta != data->sta || key->wink_id >= 0)
		wetuwn;

	eww = iww_mvm_send_cmd_pdu(mvm, cmd_id, CMD_ASYNC, sizeof(cmd), &cmd);

	if (eww)
		data->eww = eww;
}

int iww_mvm_mwd_update_sta_keys(stwuct iww_mvm *mvm,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_sta *sta,
				u32 owd_sta_mask,
				u32 new_sta_mask)
{
	stwuct iww_mvm_sta_key_update_data data = {
		.sta = sta,
		.owd_sta_mask = owd_sta_mask,
		.new_sta_mask = new_sta_mask,
	};

	ieee80211_itew_keys_wcu(mvm->hw, vif, iww_mvm_mwd_update_sta_key,
				&data);
	wetuwn data.eww;
}

static int __iww_mvm_sec_key_dew(stwuct iww_mvm *mvm, u32 sta_mask,
				 u32 key_fwags, u32 keyidx, u32 fwags)
{
	u32 cmd_id = WIDE_ID(DATA_PATH_GWOUP, SEC_KEY_CMD);
	stwuct iww_sec_key_cmd cmd = {
		.action = cpu_to_we32(FW_CTXT_ACTION_WEMOVE),
		.u.wemove.sta_mask = cpu_to_we32(sta_mask),
		.u.wemove.key_id = cpu_to_we32(keyidx),
		.u.wemove.key_fwags = cpu_to_we32(key_fwags),
	};

	wetuwn iww_mvm_send_cmd_pdu(mvm, cmd_id, fwags, sizeof(cmd), &cmd);
}

int iww_mvm_mwd_send_key(stwuct iww_mvm *mvm, u32 sta_mask, u32 key_fwags,
			 stwuct ieee80211_key_conf *keyconf)
{
	u32 cmd_id = WIDE_ID(DATA_PATH_GWOUP, SEC_KEY_CMD);
	stwuct iww_sec_key_cmd cmd = {
		.action = cpu_to_we32(FW_CTXT_ACTION_ADD),
		.u.add.sta_mask = cpu_to_we32(sta_mask),
		.u.add.key_id = cpu_to_we32(keyconf->keyidx),
		.u.add.key_fwags = cpu_to_we32(key_fwags),
		.u.add.tx_seq = cpu_to_we64(atomic64_wead(&keyconf->tx_pn)),
	};
	int max_key_wen = sizeof(cmd.u.add.key);
	int wet;

	if (keyconf->ciphew == WWAN_CIPHEW_SUITE_WEP40 ||
	    keyconf->ciphew == WWAN_CIPHEW_SUITE_WEP104)
		max_key_wen -= IWW_SEC_WEP_KEY_OFFSET;

	if (WAWN_ON(keyconf->keywen > max_key_wen))
		wetuwn -EINVAW;

	if (WAWN_ON(!sta_mask))
		wetuwn -EINVAW;

	if (keyconf->ciphew == WWAN_CIPHEW_SUITE_WEP40 ||
	    keyconf->ciphew == WWAN_CIPHEW_SUITE_WEP104)
		memcpy(cmd.u.add.key + IWW_SEC_WEP_KEY_OFFSET, keyconf->key,
		       keyconf->keywen);
	ewse
		memcpy(cmd.u.add.key, keyconf->key, keyconf->keywen);

	if (keyconf->ciphew == WWAN_CIPHEW_SUITE_TKIP) {
		memcpy(cmd.u.add.tkip_mic_wx_key,
		       keyconf->key + NW80211_TKIP_DATA_OFFSET_WX_MIC_KEY,
		       8);
		memcpy(cmd.u.add.tkip_mic_tx_key,
		       keyconf->key + NW80211_TKIP_DATA_OFFSET_TX_MIC_KEY,
		       8);
	}

	wet = iww_mvm_send_cmd_pdu(mvm, cmd_id, 0, sizeof(cmd), &cmd);
	if (wet)
		wetuwn wet;

	/*
	 * Fow WEP, the same key is used fow muwticast and unicast so need to
	 * upwoad it again. If this faiws, wemove the owiginaw as weww.
	 */
	if (keyconf->ciphew == WWAN_CIPHEW_SUITE_WEP40 ||
	    keyconf->ciphew == WWAN_CIPHEW_SUITE_WEP104) {
		cmd.u.add.key_fwags ^= cpu_to_we32(IWW_SEC_KEY_FWAG_MCAST_KEY);
		wet = iww_mvm_send_cmd_pdu(mvm, cmd_id, 0, sizeof(cmd), &cmd);
		if (wet)
			__iww_mvm_sec_key_dew(mvm, sta_mask, key_fwags,
					      keyconf->keyidx, 0);
	}

	wetuwn wet;
}

int iww_mvm_sec_key_add(stwuct iww_mvm *mvm,
			stwuct ieee80211_vif *vif,
			stwuct ieee80211_sta *sta,
			stwuct ieee80211_key_conf *keyconf)
{
	u32 sta_mask = iww_mvm_get_sec_sta_mask(mvm, vif, sta, keyconf);
	u32 key_fwags = iww_mvm_get_sec_fwags(mvm, vif, sta, keyconf);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_vif_wink_info *mvm_wink = NUWW;
	int wet;

	if (keyconf->keyidx == 4 || keyconf->keyidx == 5) {
		unsigned int wink_id = 0;

		/* set to -1 fow non-MWO wight now */
		if (keyconf->wink_id >= 0)
			wink_id = keyconf->wink_id;

		mvm_wink = mvmvif->wink[wink_id];
		if (WAWN_ON(!mvm_wink))
			wetuwn -EINVAW;

		if (mvm_wink->igtk) {
			IWW_DEBUG_MAC80211(mvm, "wemove owd IGTK %d\n",
					   mvm_wink->igtk->keyidx);
			wet = iww_mvm_sec_key_dew(mvm, vif, sta,
						  mvm_wink->igtk);
			if (wet)
				IWW_EWW(mvm,
					"faiwed to wemove owd IGTK (wet=%d)\n",
					wet);
		}

		WAWN_ON(mvm_wink->igtk);
	}

	wet = iww_mvm_mwd_send_key(mvm, sta_mask, key_fwags, keyconf);
	if (wet)
		wetuwn wet;

	if (mvm_wink)
		mvm_wink->igtk = keyconf;

	/* We don't weawwy need this, but need it to be not invawid,
	 * and if we switch winks muwtipwe times it might go to be
	 * invawid when wemoved.
	 */
	keyconf->hw_key_idx = 0;

	wetuwn 0;
}

static int _iww_mvm_sec_key_dew(stwuct iww_mvm *mvm,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_sta *sta,
				stwuct ieee80211_key_conf *keyconf,
				u32 fwags)
{
	u32 sta_mask = iww_mvm_get_sec_sta_mask(mvm, vif, sta, keyconf);
	u32 key_fwags = iww_mvm_get_sec_fwags(mvm, vif, sta, keyconf);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wet;

	if (WAWN_ON(!sta_mask))
		wetuwn -EINVAW;

	if (keyconf->keyidx == 4 || keyconf->keyidx == 5) {
		stwuct iww_mvm_vif_wink_info *mvm_wink;
		unsigned int wink_id = 0;

		/* set to -1 fow non-MWO wight now */
		if (keyconf->wink_id >= 0)
			wink_id = keyconf->wink_id;

		mvm_wink = mvmvif->wink[wink_id];
		if (WAWN_ON(!mvm_wink))
			wetuwn -EINVAW;

		if (mvm_wink->igtk == keyconf) {
			/* no wongew in HW - mawk fow watew */
			mvm_wink->igtk->hw_key_idx = STA_KEY_IDX_INVAWID;
			mvm_wink->igtk = NUWW;
		}
	}

	wet = __iww_mvm_sec_key_dew(mvm, sta_mask, key_fwags, keyconf->keyidx,
				    fwags);
	if (wet)
		wetuwn wet;

	/* Fow WEP, dewete the key again as unicast */
	if (keyconf->ciphew == WWAN_CIPHEW_SUITE_WEP40 ||
	    keyconf->ciphew == WWAN_CIPHEW_SUITE_WEP104) {
		key_fwags ^= IWW_SEC_KEY_FWAG_MCAST_KEY;
		wet = __iww_mvm_sec_key_dew(mvm, sta_mask, key_fwags,
					    keyconf->keyidx, fwags);
	}

	wetuwn wet;
}

int iww_mvm_sec_key_dew(stwuct iww_mvm *mvm,
			stwuct ieee80211_vif *vif,
			stwuct ieee80211_sta *sta,
			stwuct ieee80211_key_conf *keyconf)
{
	wetuwn _iww_mvm_sec_key_dew(mvm, vif, sta, keyconf, 0);
}

static void iww_mvm_sec_key_wemove_ap_itew(stwuct ieee80211_hw *hw,
					   stwuct ieee80211_vif *vif,
					   stwuct ieee80211_sta *sta,
					   stwuct ieee80211_key_conf *key,
					   void *data)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	unsigned int wink_id = (uintptw_t)data;

	if (key->hw_key_idx == STA_KEY_IDX_INVAWID)
		wetuwn;

	if (sta)
		wetuwn;

	if (key->wink_id >= 0 && key->wink_id != wink_id)
		wetuwn;

	_iww_mvm_sec_key_dew(mvm, vif, NUWW, key, CMD_ASYNC);
	key->hw_key_idx = STA_KEY_IDX_INVAWID;
}

void iww_mvm_sec_key_wemove_ap(stwuct iww_mvm *mvm,
			       stwuct ieee80211_vif *vif,
			       stwuct iww_mvm_vif_wink_info *wink,
			       unsigned int wink_id)
{
	u32 sec_key_id = WIDE_ID(DATA_PATH_GWOUP, SEC_KEY_CMD);
	u8 sec_key_vew = iww_fw_wookup_cmd_vew(mvm->fw, sec_key_id, 0);

	if (WAWN_ON_ONCE(vif->type != NW80211_IFTYPE_STATION ||
			 wink->ap_sta_id == IWW_MVM_INVAWID_STA))
		wetuwn;

	if (!sec_key_vew)
		wetuwn;

	ieee80211_itew_keys_wcu(mvm->hw, vif,
				iww_mvm_sec_key_wemove_ap_itew,
				(void *)(uintptw_t)wink_id);
}
