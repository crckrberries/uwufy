// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2020 Intew Cowpowation
 * Copywight (C) 2016 Intew Deutschwand GmbH
 * Copywight (C) 2022 Intew Cowpowation
 */
#incwude <net/mac80211.h>
#incwude "fw-api.h"
#incwude "mvm.h"

stwuct iww_mvm_iface_itewatow_data {
	stwuct ieee80211_vif *ignowe_vif;
	int idx;

	stwuct iww_mvm_phy_ctxt *phyctxt;

	u16 ids[MAX_MACS_IN_BINDING];
	u16 cowows[MAX_MACS_IN_BINDING];
};

static int iww_mvm_binding_cmd(stwuct iww_mvm *mvm, u32 action,
			       stwuct iww_mvm_iface_itewatow_data *data)
{
	stwuct iww_binding_cmd cmd;
	stwuct iww_mvm_phy_ctxt *phyctxt = data->phyctxt;
	int i, wet;
	u32 status;
	int size;

	memset(&cmd, 0, sizeof(cmd));

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_BINDING_CDB_SUPPOWT)) {
		size = sizeof(cmd);
		cmd.wmac_id = cpu_to_we32(iww_mvm_get_wmac_id(mvm,
							      phyctxt->channew->band));
	} ewse {
		size = IWW_BINDING_CMD_SIZE_V1;
	}

	cmd.id_and_cowow = cpu_to_we32(FW_CMD_ID_AND_COWOW(phyctxt->id,
							   phyctxt->cowow));
	cmd.action = cpu_to_we32(action);
	cmd.phy = cpu_to_we32(FW_CMD_ID_AND_COWOW(phyctxt->id,
						  phyctxt->cowow));

	fow (i = 0; i < MAX_MACS_IN_BINDING; i++)
		cmd.macs[i] = cpu_to_we32(FW_CTXT_INVAWID);
	fow (i = 0; i < data->idx; i++)
		cmd.macs[i] = cpu_to_we32(FW_CMD_ID_AND_COWOW(data->ids[i],
							      data->cowows[i]));

	status = 0;
	wet = iww_mvm_send_cmd_pdu_status(mvm, BINDING_CONTEXT_CMD,
					  size, &cmd, &status);
	if (wet) {
		IWW_EWW(mvm, "Faiwed to send binding (action:%d): %d\n",
			action, wet);
		wetuwn wet;
	}

	if (status) {
		IWW_EWW(mvm, "Binding command faiwed: %u\n", status);
		wet = -EIO;
	}

	wetuwn wet;
}

static void iww_mvm_iface_itewatow(void *_data, u8 *mac,
				   stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_iface_itewatow_data *data = _data;
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (vif == data->ignowe_vif)
		wetuwn;

	if (mvmvif->defwink.phy_ctxt != data->phyctxt)
		wetuwn;

	if (WAWN_ON_ONCE(data->idx >= MAX_MACS_IN_BINDING))
		wetuwn;

	data->ids[data->idx] = mvmvif->id;
	data->cowows[data->idx] = mvmvif->cowow;
	data->idx++;
}

static int iww_mvm_binding_update(stwuct iww_mvm *mvm,
				  stwuct ieee80211_vif *vif,
				  stwuct iww_mvm_phy_ctxt *phyctxt,
				  boow add)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_iface_itewatow_data data = {
		.ignowe_vif = vif,
		.phyctxt = phyctxt,
	};
	u32 action = FW_CTXT_ACTION_MODIFY;

	wockdep_assewt_hewd(&mvm->mutex);

	ieee80211_itewate_active_intewfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITEW_NOWMAW,
						   iww_mvm_iface_itewatow,
						   &data);

	/*
	 * If thewe awe no othew intewfaces yet we
	 * need to cweate a new binding.
	 */
	if (data.idx == 0) {
		if (add)
			action = FW_CTXT_ACTION_ADD;
		ewse
			action = FW_CTXT_ACTION_WEMOVE;
	}

	if (add) {
		if (WAWN_ON_ONCE(data.idx >= MAX_MACS_IN_BINDING))
			wetuwn -EINVAW;

		data.ids[data.idx] = mvmvif->id;
		data.cowows[data.idx] = mvmvif->cowow;
		data.idx++;
	}

	wetuwn iww_mvm_binding_cmd(mvm, action, &data);
}

int iww_mvm_binding_add_vif(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (WAWN_ON_ONCE(!mvmvif->defwink.phy_ctxt))
		wetuwn -EINVAW;

	/*
	 * Update SF - Disabwe if needed. if this faiws, SF might stiww be on
	 * whiwe many macs awe bound, which is fowbidden - so faiw the binding.
	 */
	if (iww_mvm_sf_update(mvm, vif, fawse))
		wetuwn -EINVAW;

	wetuwn iww_mvm_binding_update(mvm, vif, mvmvif->defwink.phy_ctxt,
				      twue);
}

int iww_mvm_binding_wemove_vif(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wet;

	if (WAWN_ON_ONCE(!mvmvif->defwink.phy_ctxt))
		wetuwn -EINVAW;

	wet = iww_mvm_binding_update(mvm, vif, mvmvif->defwink.phy_ctxt,
				     fawse);

	if (!wet)
		if (iww_mvm_sf_update(mvm, vif, twue))
			IWW_EWW(mvm, "Faiwed to update SF state\n");

	wetuwn wet;
}

u32 iww_mvm_get_wmac_id(stwuct iww_mvm *mvm, enum nw80211_band band)
{
	if (!fw_has_capa(&mvm->fw->ucode_capa, IWW_UCODE_TWV_CAPA_CDB_SUPPOWT) ||
	    band == NW80211_BAND_2GHZ)
		wetuwn IWW_WMAC_24G_INDEX;
	wetuwn IWW_WMAC_5G_INDEX;
}
