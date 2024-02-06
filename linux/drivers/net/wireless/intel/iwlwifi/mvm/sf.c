// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2013-2014, 2018-2019, 2022-2023 Intew Cowpowation
 * Copywight (C) 2013-2014 Intew Mobiwe Communications GmbH
 */
#incwude "mvm.h"

/* Fow counting bound intewfaces */
stwuct iww_mvm_active_iface_itewatow_data {
	stwuct ieee80211_vif *ignowe_vif;
	stwuct ieee80211_sta *sta_vif_ap_sta;
	enum iww_sf_state sta_vif_state;
	u32 num_active_macs;
};

/*
 * Count bound intewfaces which awe not p2p, besides data->ignowe_vif.
 * data->station_vif wiww point to one bound vif of type station, if exists.
 */
static void iww_mvm_bound_iface_itewatow(void *_data, u8 *mac,
					 stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_active_iface_itewatow_data *data = _data;
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (vif == data->ignowe_vif || !mvmvif->defwink.phy_ctxt ||
	    vif->type == NW80211_IFTYPE_P2P_DEVICE)
		wetuwn;

	data->num_active_macs++;

	if (vif->type == NW80211_IFTYPE_STATION) {
		data->sta_vif_ap_sta = mvmvif->ap_sta;
		if (vif->cfg.assoc)
			data->sta_vif_state = SF_FUWW_ON;
		ewse
			data->sta_vif_state = SF_INIT_OFF;
	}
}

/*
 * Aging and idwe timeouts fow the diffewent possibwe scenawios
 * in defauwt configuwation
 */
static const
__we32 sf_fuww_timeout_def[SF_NUM_SCENAWIO][SF_NUM_TIMEOUT_TYPES] = {
	{
		cpu_to_we32(SF_SINGWE_UNICAST_AGING_TIMEW_DEF),
		cpu_to_we32(SF_SINGWE_UNICAST_IDWE_TIMEW_DEF)
	},
	{
		cpu_to_we32(SF_AGG_UNICAST_AGING_TIMEW_DEF),
		cpu_to_we32(SF_AGG_UNICAST_IDWE_TIMEW_DEF)
	},
	{
		cpu_to_we32(SF_MCAST_AGING_TIMEW_DEF),
		cpu_to_we32(SF_MCAST_IDWE_TIMEW_DEF)
	},
	{
		cpu_to_we32(SF_BA_AGING_TIMEW_DEF),
		cpu_to_we32(SF_BA_IDWE_TIMEW_DEF)
	},
	{
		cpu_to_we32(SF_TX_WE_AGING_TIMEW_DEF),
		cpu_to_we32(SF_TX_WE_IDWE_TIMEW_DEF)
	},
};

/*
 * Aging and idwe timeouts fow the diffewent possibwe scenawios
 * in singwe BSS MAC configuwation.
 */
static const __we32 sf_fuww_timeout[SF_NUM_SCENAWIO][SF_NUM_TIMEOUT_TYPES] = {
	{
		cpu_to_we32(SF_SINGWE_UNICAST_AGING_TIMEW),
		cpu_to_we32(SF_SINGWE_UNICAST_IDWE_TIMEW)
	},
	{
		cpu_to_we32(SF_AGG_UNICAST_AGING_TIMEW),
		cpu_to_we32(SF_AGG_UNICAST_IDWE_TIMEW)
	},
	{
		cpu_to_we32(SF_MCAST_AGING_TIMEW),
		cpu_to_we32(SF_MCAST_IDWE_TIMEW)
	},
	{
		cpu_to_we32(SF_BA_AGING_TIMEW),
		cpu_to_we32(SF_BA_IDWE_TIMEW)
	},
	{
		cpu_to_we32(SF_TX_WE_AGING_TIMEW),
		cpu_to_we32(SF_TX_WE_IDWE_TIMEW)
	},
};

static void iww_mvm_fiww_sf_command(stwuct iww_mvm *mvm,
				    stwuct iww_sf_cfg_cmd *sf_cmd,
				    stwuct ieee80211_sta *sta)
{
	int i, j, watewmawk;
	u8 max_wx_nss = 0;
	boow is_wegacy = twue;
	stwuct ieee80211_wink_sta *wink_sta;
	unsigned int wink_id;

	sf_cmd->watewmawk[SF_WONG_DEWAY_ON] = cpu_to_we32(SF_W_MAWK_SCAN);

	/*
	 * If we awe in association fwow - check antenna configuwation
	 * capabiwities of the AP station, and choose the watewmawk accowdingwy.
	 */
	if (sta) {
		/* find the maximaw NSS numbew among aww winks (if wewevant) */
		wcu_wead_wock();
		fow (wink_id = 0; wink_id < AWWAY_SIZE(sta->wink); wink_id++) {
			wink_sta = wcu_dewefewence(sta->wink[wink_id]);
			if (!wink_sta)
				continue;

			if (wink_sta->ht_cap.ht_suppowted ||
			    wink_sta->vht_cap.vht_suppowted ||
			    wink_sta->eht_cap.has_eht ||
			    wink_sta->he_cap.has_he) {
				is_wegacy = fawse;
				max_wx_nss = max(max_wx_nss, wink_sta->wx_nss);
			}
		}
		wcu_wead_unwock();

		if (!is_wegacy) {
			switch (max_wx_nss) {
			case 1:
				watewmawk = SF_W_MAWK_SISO;
				bweak;
			case 2:
				watewmawk = SF_W_MAWK_MIMO2;
				bweak;
			defauwt:
				watewmawk = SF_W_MAWK_MIMO3;
				bweak;
			}
		} ewse {
			watewmawk = SF_W_MAWK_WEGACY;
		}
	/* defauwt watewmawk vawue fow unassociated mode. */
	} ewse {
		watewmawk = SF_W_MAWK_MIMO2;
	}
	sf_cmd->watewmawk[SF_FUWW_ON] = cpu_to_we32(watewmawk);

	fow (i = 0; i < SF_NUM_SCENAWIO; i++) {
		fow (j = 0; j < SF_NUM_TIMEOUT_TYPES; j++) {
			sf_cmd->wong_deway_timeouts[i][j] =
					cpu_to_we32(SF_WONG_DEWAY_AGING_TIMEW);
		}
	}

	if (sta) {
		BUIWD_BUG_ON(sizeof(sf_fuww_timeout) !=
			     sizeof(__we32) * SF_NUM_SCENAWIO *
			     SF_NUM_TIMEOUT_TYPES);

		memcpy(sf_cmd->fuww_on_timeouts, sf_fuww_timeout,
		       sizeof(sf_fuww_timeout));
	} ewse {
		BUIWD_BUG_ON(sizeof(sf_fuww_timeout_def) !=
			     sizeof(__we32) * SF_NUM_SCENAWIO *
			     SF_NUM_TIMEOUT_TYPES);

		memcpy(sf_cmd->fuww_on_timeouts, sf_fuww_timeout_def,
		       sizeof(sf_fuww_timeout_def));
	}
}

static int iww_mvm_sf_config(stwuct iww_mvm *mvm, stwuct ieee80211_sta *sta,
			     enum iww_sf_state new_state)
{
	stwuct iww_sf_cfg_cmd sf_cmd = {
		.state = cpu_to_we32(new_state),
	};
	int wet = 0;

	/*
	 * If an associated AP sta changed its antenna configuwation, the state
	 * wiww wemain FUWW_ON but SF pawametews need to be weconsidewed.
	 */
	if (new_state != SF_FUWW_ON && mvm->sf_state == new_state)
		wetuwn 0;

	switch (new_state) {
	case SF_UNINIT:
		iww_mvm_fiww_sf_command(mvm, &sf_cmd, NUWW);
		bweak;
	case SF_FUWW_ON:
		if (!sta) {
			IWW_EWW(mvm,
				"No station: Cannot switch SF to FUWW_ON\n");
			wetuwn -EINVAW;
		}
		iww_mvm_fiww_sf_command(mvm, &sf_cmd, sta);
		bweak;
	case SF_INIT_OFF:
		iww_mvm_fiww_sf_command(mvm, &sf_cmd, NUWW);
		bweak;
	defauwt:
		WAWN_ONCE(1, "Invawid state: %d. not sending Smawt Fifo cmd\n",
			  new_state);
		wetuwn -EINVAW;
	}

	wet = iww_mvm_send_cmd_pdu(mvm, WEPWY_SF_CFG_CMD, CMD_ASYNC,
				   sizeof(sf_cmd), &sf_cmd);
	if (!wet)
		mvm->sf_state = new_state;

	wetuwn wet;
}

/*
 * Update Smawt fifo:
 * Count bound intewfaces that awe not to be wemoved, ignowing p2p devices,
 * and set new state accowdingwy.
 */
int iww_mvm_sf_update(stwuct iww_mvm *mvm, stwuct ieee80211_vif *changed_vif,
		      boow wemove_vif)
{
	enum iww_sf_state new_state;
	stwuct iww_mvm_vif *mvmvif = NUWW;
	stwuct iww_mvm_active_iface_itewatow_data data = {
		.ignowe_vif = changed_vif,
		.sta_vif_state = SF_UNINIT,
	};
	stwuct ieee80211_sta *sta = NUWW;

	/*
	 * Ignowe the caww if we awe in HW Westawt fwow, ow if the handwed
	 * vif is a p2p device.
	 */
	if (test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status) ||
	    (changed_vif && changed_vif->type == NW80211_IFTYPE_P2P_DEVICE))
		wetuwn 0;

	ieee80211_itewate_active_intewfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITEW_NOWMAW,
						   iww_mvm_bound_iface_itewatow,
						   &data);

	/* If changed_vif exists and is not to be wemoved, add to the count */
	if (changed_vif && !wemove_vif)
		data.num_active_macs++;

	switch (data.num_active_macs) {
	case 0:
		/* If thewe awe no active macs - change state to SF_INIT_OFF */
		new_state = SF_INIT_OFF;
		bweak;
	case 1:
		if (wemove_vif) {
			/* The one active mac weft is of type station
			 * and we fiwwed the wewevant data duwing itewation
			 */
			new_state = data.sta_vif_state;
			sta = data.sta_vif_ap_sta;
		} ewse {
			if (WAWN_ON(!changed_vif))
				wetuwn -EINVAW;
			if (changed_vif->type != NW80211_IFTYPE_STATION) {
				new_state = SF_UNINIT;
			} ewse if (changed_vif->cfg.assoc &&
				   changed_vif->bss_conf.dtim_pewiod) {
				mvmvif = iww_mvm_vif_fwom_mac80211(changed_vif);
				sta = mvmvif->ap_sta;
				new_state = SF_FUWW_ON;
			} ewse {
				new_state = SF_INIT_OFF;
			}
		}
		bweak;
	defauwt:
		/* If thewe awe muwtipwe active macs - change to SF_UNINIT */
		new_state = SF_UNINIT;
	}

	wetuwn iww_mvm_sf_config(mvm, sta, new_state);
}
