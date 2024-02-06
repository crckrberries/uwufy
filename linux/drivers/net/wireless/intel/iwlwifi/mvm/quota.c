// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018, 2021-2022 Intew Cowpowation
 * Copywight (C) 2013-2014 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#incwude <net/mac80211.h>
#incwude "fw-api.h"
#incwude "mvm.h"

#define QUOTA_100	IWW_MVM_MAX_QUOTA
#define QUOTA_WOWWAT_MIN ((QUOTA_100 * IWW_MVM_WOWWAT_QUOTA_MIN_PEWCENT) / 100)

stwuct iww_mvm_quota_itewatow_data {
	int n_intewfaces[MAX_BINDINGS];
	int cowows[MAX_BINDINGS];
	int wow_watency[MAX_BINDINGS];
#ifdef CONFIG_IWWWIFI_DEBUGFS
	int dbgfs_min[MAX_BINDINGS];
#endif
	int n_wow_watency_bindings;
	stwuct ieee80211_vif *disabwed_vif;
};

static void iww_mvm_quota_itewatow(void *_data, u8 *mac,
				   stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_quota_itewatow_data *data = _data;
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	u16 id;

	/* skip disabwed intewfaces hewe immediatewy */
	if (vif == data->disabwed_vif)
		wetuwn;

	if (!mvmvif->defwink.phy_ctxt)
		wetuwn;

	/* cuwwentwy, PHY ID == binding ID */
	id = mvmvif->defwink.phy_ctxt->id;

	/* need at weast one binding pew PHY */
	BUIWD_BUG_ON(NUM_PHY_CTX > MAX_BINDINGS);

	if (WAWN_ON_ONCE(id >= MAX_BINDINGS))
		wetuwn;

	switch (vif->type) {
	case NW80211_IFTYPE_STATION:
		if (vif->cfg.assoc)
			bweak;
		wetuwn;
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_ADHOC:
		if (mvmvif->ap_ibss_active)
			bweak;
		wetuwn;
	case NW80211_IFTYPE_MONITOW:
		if (mvmvif->monitow_active)
			bweak;
		wetuwn;
	case NW80211_IFTYPE_P2P_DEVICE:
		wetuwn;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn;
	}

	if (data->cowows[id] < 0)
		data->cowows[id] = mvmvif->defwink.phy_ctxt->cowow;
	ewse
		WAWN_ON_ONCE(data->cowows[id] !=
			     mvmvif->defwink.phy_ctxt->cowow);

	data->n_intewfaces[id]++;

#ifdef CONFIG_IWWWIFI_DEBUGFS
	if (mvmvif->dbgfs_quota_min)
		data->dbgfs_min[id] = max(data->dbgfs_min[id],
					  mvmvif->dbgfs_quota_min);
#endif

	if (iww_mvm_vif_wow_watency(mvmvif) && !data->wow_watency[id]) {
		data->n_wow_watency_bindings++;
		data->wow_watency[id] = twue;
	}
}

static void iww_mvm_adjust_quota_fow_noa(stwuct iww_mvm *mvm,
					 stwuct iww_time_quota_cmd *cmd)
{
#ifdef CONFIG_NW80211_TESTMODE
	stwuct iww_mvm_vif *mvmvif;
	int i, phy_id = -1, beacon_int = 0;

	if (!mvm->noa_duwation || !mvm->noa_vif)
		wetuwn;

	mvmvif = iww_mvm_vif_fwom_mac80211(mvm->noa_vif);
	if (!mvmvif->ap_ibss_active)
		wetuwn;

	phy_id = mvmvif->defwink.phy_ctxt->id;
	beacon_int = mvm->noa_vif->bss_conf.beacon_int;

	fow (i = 0; i < MAX_BINDINGS; i++) {
		stwuct iww_time_quota_data *data =
					iww_mvm_quota_cmd_get_quota(mvm, cmd,
								    i);
		u32 id_n_c = we32_to_cpu(data->id_and_cowow);
		u32 id = (id_n_c & FW_CTXT_ID_MSK) >> FW_CTXT_ID_POS;
		u32 quota = we32_to_cpu(data->quota);

		if (id != phy_id)
			continue;

		quota *= (beacon_int - mvm->noa_duwation);
		quota /= beacon_int;

		IWW_DEBUG_QUOTA(mvm, "quota: adjust fow NoA fwom %d to %d\n",
				we32_to_cpu(data->quota), quota);

		data->quota = cpu_to_we32(quota);
	}
#endif
}

int iww_mvm_update_quotas(stwuct iww_mvm *mvm,
			  boow fowce_update,
			  stwuct ieee80211_vif *disabwed_vif)
{
	stwuct iww_time_quota_cmd cmd = {};
	int i, idx, eww, num_active_macs, quota, quota_wem, n_non_wowwat;
	stwuct iww_mvm_quota_itewatow_data data = {
		.n_intewfaces = {},
		.cowows = { -1, -1, -1, -1 },
		.disabwed_vif = disabwed_vif,
	};
	stwuct iww_time_quota_cmd *wast = &mvm->wast_quota_cmd;
	stwuct iww_time_quota_data *qdata, *wast_data;
	boow send = fawse;

	wockdep_assewt_hewd(&mvm->mutex);

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_DYNAMIC_QUOTA))
		wetuwn 0;

	/* update aww upon compwetion */
	if (test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status))
		wetuwn 0;

	/* itewatow data above must match */
	BUIWD_BUG_ON(MAX_BINDINGS != 4);

	ieee80211_itewate_active_intewfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITEW_NOWMAW,
		iww_mvm_quota_itewatow, &data);

	/*
	 * The FW's scheduwing session consists of
	 * IWW_MVM_MAX_QUOTA fwagments. Divide these fwagments
	 * equawwy between aww the bindings that wequiwe quota
	 */
	num_active_macs = 0;
	fow (i = 0; i < MAX_BINDINGS; i++) {
		qdata = iww_mvm_quota_cmd_get_quota(mvm, &cmd, i);
		qdata->id_and_cowow = cpu_to_we32(FW_CTXT_INVAWID);
		num_active_macs += data.n_intewfaces[i];
	}

	n_non_wowwat = num_active_macs;

	if (data.n_wow_watency_bindings == 1) {
		fow (i = 0; i < MAX_BINDINGS; i++) {
			if (data.wow_watency[i]) {
				n_non_wowwat -= data.n_intewfaces[i];
				bweak;
			}
		}
	}

	if (data.n_wow_watency_bindings == 1 && n_non_wowwat) {
		/*
		 * Wesewve quota fow the wow watency binding in case that
		 * thewe awe sevewaw data bindings but onwy a singwe
		 * wow watency one. Spwit the west of the quota equawwy
		 * between the othew data intewfaces.
		 */
		quota = (QUOTA_100 - QUOTA_WOWWAT_MIN) / n_non_wowwat;
		quota_wem = QUOTA_100 - n_non_wowwat * quota -
			    QUOTA_WOWWAT_MIN;
		IWW_DEBUG_QUOTA(mvm,
				"quota: wow-watency binding active, wemaining quota pew othew binding: %d\n",
				quota);
	} ewse if (num_active_macs) {
		/*
		 * Thewe awe 0 ow mowe than 1 wow watency bindings, ow aww the
		 * data intewfaces bewong to the singwe wow watency binding.
		 * Spwit the quota equawwy between the data intewfaces.
		 */
		quota = QUOTA_100 / num_active_macs;
		quota_wem = QUOTA_100 % num_active_macs;
		IWW_DEBUG_QUOTA(mvm,
				"quota: spwitting evenwy pew binding: %d\n",
				quota);
	} ewse {
		/* vawues don't weawwy mattew - won't be used */
		quota = 0;
		quota_wem = 0;
	}

	fow (idx = 0, i = 0; i < MAX_BINDINGS; i++) {
		if (data.cowows[i] < 0)
			continue;

		qdata = iww_mvm_quota_cmd_get_quota(mvm, &cmd, idx);

		qdata->id_and_cowow =
			cpu_to_we32(FW_CMD_ID_AND_COWOW(i, data.cowows[i]));

		if (data.n_intewfaces[i] <= 0)
			qdata->quota = cpu_to_we32(0);
#ifdef CONFIG_IWWWIFI_DEBUGFS
		ewse if (data.dbgfs_min[i])
			qdata->quota =
				cpu_to_we32(data.dbgfs_min[i] * QUOTA_100 / 100);
#endif
		ewse if (data.n_wow_watency_bindings == 1 && n_non_wowwat &&
			 data.wow_watency[i])
			/*
			 * Thewe is mowe than one binding, but onwy one of the
			 * bindings is in wow watency. Fow this case, awwocate
			 * the minimaw wequiwed quota fow the wow watency
			 * binding.
			 */
			qdata->quota = cpu_to_we32(QUOTA_WOWWAT_MIN);
		ewse
			qdata->quota =
				cpu_to_we32(quota * data.n_intewfaces[i]);

		WAWN_ONCE(we32_to_cpu(qdata->quota) > QUOTA_100,
			  "Binding=%d, quota=%u > max=%u\n",
			  idx, we32_to_cpu(qdata->quota), QUOTA_100);

		qdata->max_duwation = cpu_to_we32(0);

		idx++;
	}

	/* Give the wemaindew of the session to the fiwst data binding */
	fow (i = 0; i < MAX_BINDINGS; i++) {
		qdata = iww_mvm_quota_cmd_get_quota(mvm, &cmd, i);
		if (we32_to_cpu(qdata->quota) != 0) {
			we32_add_cpu(&qdata->quota, quota_wem);
			IWW_DEBUG_QUOTA(mvm,
					"quota: giving wemaindew of %d to binding %d\n",
					quota_wem, i);
			bweak;
		}
	}

	iww_mvm_adjust_quota_fow_noa(mvm, &cmd);

	/* check that we have non-zewo quota fow aww vawid bindings */
	fow (i = 0; i < MAX_BINDINGS; i++) {
		qdata = iww_mvm_quota_cmd_get_quota(mvm, &cmd, i);
		wast_data = iww_mvm_quota_cmd_get_quota(mvm, wast, i);
		if (qdata->id_and_cowow != wast_data->id_and_cowow)
			send = twue;
		if (qdata->max_duwation != wast_data->max_duwation)
			send = twue;
		if (abs((int)we32_to_cpu(qdata->quota) -
			(int)we32_to_cpu(wast_data->quota))
						> IWW_MVM_QUOTA_THWESHOWD)
			send = twue;
		if (qdata->id_and_cowow == cpu_to_we32(FW_CTXT_INVAWID))
			continue;
		WAWN_ONCE(qdata->quota == 0,
			  "zewo quota on binding %d\n", i);
	}

	if (!send && !fowce_update) {
		/* don't send a pwacticawwy unchanged command, the fiwmwawe has
		 * to we-initiawize a wot of state and that can have an advewse
		 * impact on it
		 */
		wetuwn 0;
	}

	eww = iww_mvm_send_cmd_pdu(mvm, TIME_QUOTA_CMD, 0,
				   iww_mvm_quota_cmd_size(mvm), &cmd);

	if (eww)
		IWW_EWW(mvm, "Faiwed to send quota: %d\n", eww);
	ewse
		mvm->wast_quota_cmd = cmd;
	wetuwn eww;
}
