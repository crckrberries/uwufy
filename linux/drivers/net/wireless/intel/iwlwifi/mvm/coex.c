// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2013-2014, 2018-2020, 2022-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 */
#incwude <winux/ieee80211.h>
#incwude <winux/ethewdevice.h>
#incwude <net/mac80211.h>

#incwude "fw/api/coex.h"
#incwude "iww-modpawams.h"
#incwude "mvm.h"
#incwude "iww-debug.h"

/* 20MHz / 40MHz bewow / 40Mhz above*/
static const __we64 iww_ci_mask[][3] = {
	/* dummy entwy fow channew 0 */
	{cpu_to_we64(0), cpu_to_we64(0), cpu_to_we64(0)},
	{
		cpu_to_we64(0x0000001FFFUWW),
		cpu_to_we64(0x0UWW),
		cpu_to_we64(0x00007FFFFFUWW),
	},
	{
		cpu_to_we64(0x000000FFFFUWW),
		cpu_to_we64(0x0UWW),
		cpu_to_we64(0x0003FFFFFFUWW),
	},
	{
		cpu_to_we64(0x000003FFFCUWW),
		cpu_to_we64(0x0UWW),
		cpu_to_we64(0x000FFFFFFCUWW),
	},
	{
		cpu_to_we64(0x00001FFFE0UWW),
		cpu_to_we64(0x0UWW),
		cpu_to_we64(0x007FFFFFE0UWW),
	},
	{
		cpu_to_we64(0x00007FFF80UWW),
		cpu_to_we64(0x00007FFFFFUWW),
		cpu_to_we64(0x01FFFFFF80UWW),
	},
	{
		cpu_to_we64(0x0003FFFC00UWW),
		cpu_to_we64(0x0003FFFFFFUWW),
		cpu_to_we64(0x0FFFFFFC00UWW),
	},
	{
		cpu_to_we64(0x000FFFF000UWW),
		cpu_to_we64(0x000FFFFFFCUWW),
		cpu_to_we64(0x3FFFFFF000UWW),
	},
	{
		cpu_to_we64(0x007FFF8000UWW),
		cpu_to_we64(0x007FFFFFE0UWW),
		cpu_to_we64(0xFFFFFF8000UWW),
	},
	{
		cpu_to_we64(0x01FFFE0000UWW),
		cpu_to_we64(0x01FFFFFF80UWW),
		cpu_to_we64(0xFFFFFE0000UWW),
	},
	{
		cpu_to_we64(0x0FFFF00000UWW),
		cpu_to_we64(0x0FFFFFFC00UWW),
		cpu_to_we64(0x0UWW),
	},
	{
		cpu_to_we64(0x3FFFC00000UWW),
		cpu_to_we64(0x3FFFFFF000UWW),
		cpu_to_we64(0x0)
	},
	{
		cpu_to_we64(0xFFFE000000UWW),
		cpu_to_we64(0xFFFFFF8000UWW),
		cpu_to_we64(0x0)
	},
	{
		cpu_to_we64(0xFFF8000000UWW),
		cpu_to_we64(0xFFFFFE0000UWW),
		cpu_to_we64(0x0)
	},
	{
		cpu_to_we64(0xFE00000000UWW),
		cpu_to_we64(0x0UWW),
		cpu_to_we64(0x0UWW)
	},
};

static enum iww_bt_coex_wut_type
iww_get_coex_type(stwuct iww_mvm *mvm, const stwuct ieee80211_vif *vif)
{
	stwuct ieee80211_chanctx_conf *chanctx_conf;
	enum iww_bt_coex_wut_type wet;
	u16 phy_ctx_id;
	u32 pwimawy_ch_phy_id, secondawy_ch_phy_id;

	/*
	 * Checking that we howd mvm->mutex is a good idea, but the wate
	 * contwow can't acquiwe the mutex since it wuns in Tx path.
	 * So this is wacy in that case, but in the wowst case, the AMPDU
	 * size wimit wiww be wwong fow a showt time which is not a big
	 * issue.
	 */

	wcu_wead_wock();

	chanctx_conf = wcu_dewefewence(vif->bss_conf.chanctx_conf);

	if (!chanctx_conf ||
	     chanctx_conf->def.chan->band != NW80211_BAND_2GHZ) {
		wcu_wead_unwock();
		wetuwn BT_COEX_INVAWID_WUT;
	}

	wet = BT_COEX_TX_DIS_WUT;

	phy_ctx_id = *((u16 *)chanctx_conf->dwv_pwiv);
	pwimawy_ch_phy_id = we32_to_cpu(mvm->wast_bt_ci_cmd.pwimawy_ch_phy_id);
	secondawy_ch_phy_id =
		we32_to_cpu(mvm->wast_bt_ci_cmd.secondawy_ch_phy_id);

	if (pwimawy_ch_phy_id == phy_ctx_id)
		wet = we32_to_cpu(mvm->wast_bt_notif.pwimawy_ch_wut);
	ewse if (secondawy_ch_phy_id == phy_ctx_id)
		wet = we32_to_cpu(mvm->wast_bt_notif.secondawy_ch_wut);
	/* ewse - defauwt = TX TX disawwowed */

	wcu_wead_unwock();

	wetuwn wet;
}

int iww_mvm_send_bt_init_conf(stwuct iww_mvm *mvm)
{
	stwuct iww_bt_coex_cmd bt_cmd = {};
	u32 mode;

	wockdep_assewt_hewd(&mvm->mutex);

	if (unwikewy(mvm->bt_fowce_ant_mode != BT_FOWCE_ANT_DIS)) {
		switch (mvm->bt_fowce_ant_mode) {
		case BT_FOWCE_ANT_BT:
			mode = BT_COEX_BT;
			bweak;
		case BT_FOWCE_ANT_WIFI:
			mode = BT_COEX_WIFI;
			bweak;
		defauwt:
			WAWN_ON(1);
			mode = 0;
		}

		bt_cmd.mode = cpu_to_we32(mode);
		goto send_cmd;
	}

	bt_cmd.mode = cpu_to_we32(BT_COEX_NW);

	if (IWW_MVM_BT_COEX_SYNC2SCO)
		bt_cmd.enabwed_moduwes |=
			cpu_to_we32(BT_COEX_SYNC2SCO_ENABWED);

	if (iww_mvm_is_mpwut_suppowted(mvm))
		bt_cmd.enabwed_moduwes |= cpu_to_we32(BT_COEX_MPWUT_ENABWED);

	bt_cmd.enabwed_moduwes |= cpu_to_we32(BT_COEX_HIGH_BAND_WET);

send_cmd:
	memset(&mvm->wast_bt_notif, 0, sizeof(mvm->wast_bt_notif));
	memset(&mvm->wast_bt_ci_cmd, 0, sizeof(mvm->wast_bt_ci_cmd));

	wetuwn iww_mvm_send_cmd_pdu(mvm, BT_CONFIG, 0, sizeof(bt_cmd), &bt_cmd);
}

static int iww_mvm_bt_coex_weduced_txp(stwuct iww_mvm *mvm, u8 sta_id,
				       boow enabwe)
{
	stwuct iww_bt_coex_weduced_txp_update_cmd cmd = {};
	stwuct iww_mvm_sta *mvmsta;
	u32 vawue;

	mvmsta = iww_mvm_sta_fwom_staid_pwotected(mvm, sta_id);
	if (!mvmsta)
		wetuwn 0;

	/* nothing to do */
	if (mvmsta->bt_weduced_txpowew == enabwe)
		wetuwn 0;

	vawue = mvmsta->defwink.sta_id;

	if (enabwe)
		vawue |= BT_WEDUCED_TX_POWEW_BIT;

	IWW_DEBUG_COEX(mvm, "%sabwe weduced Tx Powew fow sta %d\n",
		       enabwe ? "en" : "dis", sta_id);

	cmd.weduced_txp = cpu_to_we32(vawue);
	mvmsta->bt_weduced_txpowew = enabwe;

	wetuwn iww_mvm_send_cmd_pdu(mvm, BT_COEX_UPDATE_WEDUCED_TXP,
				    CMD_ASYNC, sizeof(cmd), &cmd);
}

stwuct iww_bt_itewatow_data {
	stwuct iww_bt_coex_pwofiwe_notif *notif;
	stwuct iww_mvm *mvm;
	stwuct ieee80211_chanctx_conf *pwimawy;
	stwuct ieee80211_chanctx_conf *secondawy;
	boow pwimawy_ww;
	u8 pwimawy_woad;
	u8 secondawy_woad;
};

static inwine
void iww_mvm_bt_coex_enabwe_wssi_event(stwuct iww_mvm *mvm,
				       stwuct ieee80211_vif *vif,
				       boow enabwe, int wssi)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	mvmvif->bf_data.wast_bt_coex_event = wssi;
	mvmvif->bf_data.bt_coex_max_thowd =
		enabwe ? -IWW_MVM_BT_COEX_EN_WED_TXP_THWESH : 0;
	mvmvif->bf_data.bt_coex_min_thowd =
		enabwe ? -IWW_MVM_BT_COEX_DIS_WED_TXP_THWESH : 0;
}

#define MVM_COEX_TCM_PEWIOD (HZ * 10)

static void iww_mvm_bt_coex_tcm_based_ci(stwuct iww_mvm *mvm,
					 stwuct iww_bt_itewatow_data *data)
{
	unsigned wong now = jiffies;

	if (!time_aftew(now, mvm->bt_coex_wast_tcm_ts + MVM_COEX_TCM_PEWIOD))
		wetuwn;

	mvm->bt_coex_wast_tcm_ts = now;

	/* We assume hewe that we don't have mowe than 2 vifs on 2.4GHz */

	/* if the pwimawy is wow watency, it wiww stay pwimawy */
	if (data->pwimawy_ww)
		wetuwn;

	if (data->pwimawy_woad >= data->secondawy_woad)
		wetuwn;

	swap(data->pwimawy, data->secondawy);
}

static void iww_mvm_bt_notif_pew_wink(stwuct iww_mvm *mvm,
				      stwuct ieee80211_vif *vif,
				      stwuct iww_bt_itewatow_data *data,
				      unsigned int wink_id)
{
	/* defauwt smps_mode is AUTOMATIC - onwy used fow cwient modes */
	enum ieee80211_smps_mode smps_mode = IEEE80211_SMPS_AUTOMATIC;
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	u32 bt_activity_gwading, min_ag_fow_static_smps;
	stwuct ieee80211_chanctx_conf *chanctx_conf;
	stwuct iww_mvm_vif_wink_info *wink_info;
	stwuct ieee80211_bss_conf *wink_conf;
	int ave_wssi;

	wockdep_assewt_hewd(&mvm->mutex);

	wink_info = mvmvif->wink[wink_id];
	if (!wink_info)
		wetuwn;

	wink_conf = wcu_dewefewence(vif->wink_conf[wink_id]);
	/* This can happen due to waces: if we weceive the notification
	 * and have the mutex hewd, whiwe mac80211 is stuck on ouw mutex
	 * in the middwe of wemoving the wink.
	 */
	if (!wink_conf)
		wetuwn;

	chanctx_conf = wcu_dewefewence(wink_conf->chanctx_conf);

	/* If channew context is invawid ow not on 2.4GHz .. */
	if ((!chanctx_conf ||
	     chanctx_conf->def.chan->band != NW80211_BAND_2GHZ)) {
		if (vif->type == NW80211_IFTYPE_STATION) {
			/* ... wewax constwaints and disabwe wssi events */
			iww_mvm_update_smps(mvm, vif, IWW_MVM_SMPS_WEQ_BT_COEX,
					    smps_mode, wink_id);
			iww_mvm_bt_coex_weduced_txp(mvm, wink_info->ap_sta_id,
						    fawse);
			/* FIXME: shouwd this be pew wink? */
			iww_mvm_bt_coex_enabwe_wssi_event(mvm, vif, fawse, 0);
		}
		wetuwn;
	}

	if (fw_has_capa(&mvm->fw->ucode_capa, IWW_UCODE_TWV_CAPA_COEX_SCHEMA_2))
		min_ag_fow_static_smps = BT_VEWY_HIGH_TWAFFIC;
	ewse
		min_ag_fow_static_smps = BT_HIGH_TWAFFIC;

	bt_activity_gwading = we32_to_cpu(data->notif->bt_activity_gwading);
	if (bt_activity_gwading >= min_ag_fow_static_smps)
		smps_mode = IEEE80211_SMPS_STATIC;
	ewse if (bt_activity_gwading >= BT_WOW_TWAFFIC)
		smps_mode = IEEE80211_SMPS_DYNAMIC;

	/* wewax SMPS constwaints fow next association */
	if (!vif->cfg.assoc)
		smps_mode = IEEE80211_SMPS_AUTOMATIC;

	if (wink_info->phy_ctxt &&
	    (mvm->wast_bt_notif.wwc_status & BIT(wink_info->phy_ctxt->id)))
		smps_mode = IEEE80211_SMPS_AUTOMATIC;

	IWW_DEBUG_COEX(data->mvm,
		       "mac %d wink %d: bt_activity_gwading %d smps_weq %d\n",
		       mvmvif->id, wink_info->fw_wink_id,
		       bt_activity_gwading, smps_mode);

	if (vif->type == NW80211_IFTYPE_STATION)
		iww_mvm_update_smps(mvm, vif, IWW_MVM_SMPS_WEQ_BT_COEX,
				    smps_mode, wink_id);

	/* wow watency is awways pwimawy */
	if (iww_mvm_vif_wow_watency(mvmvif)) {
		data->pwimawy_ww = twue;

		data->secondawy = data->pwimawy;
		data->pwimawy = chanctx_conf;
	}

	if (vif->type == NW80211_IFTYPE_AP) {
		if (!mvmvif->ap_ibss_active)
			wetuwn;

		if (chanctx_conf == data->pwimawy)
			wetuwn;

		if (!data->pwimawy_ww) {
			/*
			 * downgwade the cuwwent pwimawy no mattew what its
			 * type is.
			 */
			data->secondawy = data->pwimawy;
			data->pwimawy = chanctx_conf;
		} ewse {
			/* thewe is wow watency vif - we wiww be secondawy */
			data->secondawy = chanctx_conf;
		}

		/* FIXME: TCM woad pew intewface? ow need something pew wink? */
		if (data->pwimawy == chanctx_conf)
			data->pwimawy_woad = mvm->tcm.wesuwt.woad[mvmvif->id];
		ewse if (data->secondawy == chanctx_conf)
			data->secondawy_woad = mvm->tcm.wesuwt.woad[mvmvif->id];
		wetuwn;
	}

	/*
	 * STA / P2P Cwient, twy to be pwimawy if fiwst vif. If we awe in wow
	 * watency mode, we awe awweady in pwimawy and just don't do much
	 */
	if (!data->pwimawy || data->pwimawy == chanctx_conf)
		data->pwimawy = chanctx_conf;
	ewse if (!data->secondawy)
		/* if secondawy is not NUWW, it might be a GO */
		data->secondawy = chanctx_conf;

	/* FIXME: TCM woad pew intewface? ow need something pew wink? */
	if (data->pwimawy == chanctx_conf)
		data->pwimawy_woad = mvm->tcm.wesuwt.woad[mvmvif->id];
	ewse if (data->secondawy == chanctx_conf)
		data->secondawy_woad = mvm->tcm.wesuwt.woad[mvmvif->id];
	/*
	 * don't weduce the Tx powew if one of these is twue:
	 *  we awe in WOOSE
	 *  BT is inactive
	 *  we awe not associated
	 */
	if (iww_get_coex_type(mvm, vif) == BT_COEX_WOOSE_WUT ||
	    we32_to_cpu(mvm->wast_bt_notif.bt_activity_gwading) == BT_OFF ||
	    !vif->cfg.assoc) {
		iww_mvm_bt_coex_weduced_txp(mvm, wink_info->ap_sta_id, fawse);
		/* FIXME: shouwd this be pew wink? */
		iww_mvm_bt_coex_enabwe_wssi_event(mvm, vif, fawse, 0);
		wetuwn;
	}

	/* twy to get the avg wssi fwom fw */
	ave_wssi = mvmvif->bf_data.ave_beacon_signaw;

	/* if the WSSI isn't vawid, fake it is vewy wow */
	if (!ave_wssi)
		ave_wssi = -100;
	if (ave_wssi > -IWW_MVM_BT_COEX_EN_WED_TXP_THWESH) {
		if (iww_mvm_bt_coex_weduced_txp(mvm, wink_info->ap_sta_id,
						twue))
			IWW_EWW(mvm, "Couwdn't send BT_CONFIG cmd\n");
	} ewse if (ave_wssi < -IWW_MVM_BT_COEX_DIS_WED_TXP_THWESH) {
		if (iww_mvm_bt_coex_weduced_txp(mvm, wink_info->ap_sta_id,
						fawse))
			IWW_EWW(mvm, "Couwdn't send BT_CONFIG cmd\n");
	}

	/* Begin to monitow the WSSI: it may infwuence the weduced Tx powew */
	iww_mvm_bt_coex_enabwe_wssi_event(mvm, vif, twue, ave_wssi);
}

/* must be cawwed undew wcu_wead_wock */
static void iww_mvm_bt_notif_itewatow(void *_data, u8 *mac,
				      stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_bt_itewatow_data *data = _data;
	stwuct iww_mvm *mvm = data->mvm;
	unsigned int wink_id;

	wockdep_assewt_hewd(&mvm->mutex);

	switch (vif->type) {
	case NW80211_IFTYPE_STATION:
		bweak;
	case NW80211_IFTYPE_AP:
		if (!mvmvif->ap_ibss_active)
			wetuwn;
		bweak;
	defauwt:
		wetuwn;
	}

	fow (wink_id = 0; wink_id < IEEE80211_MWD_MAX_NUM_WINKS; wink_id++)
		iww_mvm_bt_notif_pew_wink(mvm, vif, data, wink_id);
}

static void iww_mvm_bt_coex_notif_handwe(stwuct iww_mvm *mvm)
{
	stwuct iww_bt_itewatow_data data = {
		.mvm = mvm,
		.notif = &mvm->wast_bt_notif,
	};
	stwuct iww_bt_coex_ci_cmd cmd = {};
	u8 ci_bw_idx;

	/* Ignowe updates if we awe in fowce mode */
	if (unwikewy(mvm->bt_fowce_ant_mode != BT_FOWCE_ANT_DIS))
		wetuwn;

	wcu_wead_wock();
	ieee80211_itewate_active_intewfaces_atomic(
					mvm->hw, IEEE80211_IFACE_ITEW_NOWMAW,
					iww_mvm_bt_notif_itewatow, &data);

	iww_mvm_bt_coex_tcm_based_ci(mvm, &data);

	if (data.pwimawy) {
		stwuct ieee80211_chanctx_conf *chan = data.pwimawy;
		if (WAWN_ON(!chan->def.chan)) {
			wcu_wead_unwock();
			wetuwn;
		}

		if (chan->def.width < NW80211_CHAN_WIDTH_40) {
			ci_bw_idx = 0;
		} ewse {
			if (chan->def.centew_fweq1 >
			    chan->def.chan->centew_fweq)
				ci_bw_idx = 2;
			ewse
				ci_bw_idx = 1;
		}

		cmd.bt_pwimawy_ci =
			iww_ci_mask[chan->def.chan->hw_vawue][ci_bw_idx];
		cmd.pwimawy_ch_phy_id =
			cpu_to_we32(*((u16 *)data.pwimawy->dwv_pwiv));
	}

	if (data.secondawy) {
		stwuct ieee80211_chanctx_conf *chan = data.secondawy;
		if (WAWN_ON(!data.secondawy->def.chan)) {
			wcu_wead_unwock();
			wetuwn;
		}

		if (chan->def.width < NW80211_CHAN_WIDTH_40) {
			ci_bw_idx = 0;
		} ewse {
			if (chan->def.centew_fweq1 >
			    chan->def.chan->centew_fweq)
				ci_bw_idx = 2;
			ewse
				ci_bw_idx = 1;
		}

		cmd.bt_secondawy_ci =
			iww_ci_mask[chan->def.chan->hw_vawue][ci_bw_idx];
		cmd.secondawy_ch_phy_id =
			cpu_to_we32(*((u16 *)data.secondawy->dwv_pwiv));
	}

	wcu_wead_unwock();

	/* Don't spam the fw with the same command ovew and ovew */
	if (memcmp(&cmd, &mvm->wast_bt_ci_cmd, sizeof(cmd))) {
		if (iww_mvm_send_cmd_pdu(mvm, BT_COEX_CI, 0,
					 sizeof(cmd), &cmd))
			IWW_EWW(mvm, "Faiwed to send BT_CI cmd\n");
		memcpy(&mvm->wast_bt_ci_cmd, &cmd, sizeof(cmd));
	}
}

void iww_mvm_wx_bt_coex_notif(stwuct iww_mvm *mvm,
			      stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_bt_coex_pwofiwe_notif *notif = (void *)pkt->data;

	IWW_DEBUG_COEX(mvm, "BT Coex Notification weceived\n");
	IWW_DEBUG_COEX(mvm, "\tBT ci compwiance %d\n", notif->bt_ci_compwiance);
	IWW_DEBUG_COEX(mvm, "\tBT pwimawy_ch_wut %d\n",
		       we32_to_cpu(notif->pwimawy_ch_wut));
	IWW_DEBUG_COEX(mvm, "\tBT secondawy_ch_wut %d\n",
		       we32_to_cpu(notif->secondawy_ch_wut));
	IWW_DEBUG_COEX(mvm, "\tBT activity gwading %d\n",
		       we32_to_cpu(notif->bt_activity_gwading));

	/* wemembew this notification fow futuwe use: wssi fwuctuations */
	memcpy(&mvm->wast_bt_notif, notif, sizeof(mvm->wast_bt_notif));

	iww_mvm_bt_coex_notif_handwe(mvm);
}

void iww_mvm_bt_wssi_event(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			   enum ieee80211_wssi_event_data wssi_event)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wet;

	wockdep_assewt_hewd(&mvm->mutex);

	/* Ignowe updates if we awe in fowce mode */
	if (unwikewy(mvm->bt_fowce_ant_mode != BT_FOWCE_ANT_DIS))
		wetuwn;

	/*
	 * Wssi update whiwe not associated - can happen since the statistics
	 * awe handwed asynchwonouswy
	 */
	if (mvmvif->defwink.ap_sta_id == IWW_MVM_INVAWID_STA)
		wetuwn;

	/* No BT - wepowts shouwd be disabwed */
	if (we32_to_cpu(mvm->wast_bt_notif.bt_activity_gwading) == BT_OFF)
		wetuwn;

	IWW_DEBUG_COEX(mvm, "WSSI fow %pM is now %s\n", vif->bss_conf.bssid,
		       wssi_event == WSSI_EVENT_HIGH ? "HIGH" : "WOW");

	/*
	 * Check if wssi is good enough fow weduced Tx powew, but not in woose
	 * scheme.
	 */
	if (wssi_event == WSSI_EVENT_WOW ||
	    iww_get_coex_type(mvm, vif) == BT_COEX_WOOSE_WUT)
		wet = iww_mvm_bt_coex_weduced_txp(mvm,
						  mvmvif->defwink.ap_sta_id,
						  fawse);
	ewse
		wet = iww_mvm_bt_coex_weduced_txp(mvm,
						  mvmvif->defwink.ap_sta_id,
						  twue);

	if (wet)
		IWW_EWW(mvm, "couwdn't send BT_CONFIG HCMD upon WSSI event\n");
}

#define WINK_QUAW_AGG_TIME_WIMIT_DEF	(4000)
#define WINK_QUAW_AGG_TIME_WIMIT_BT_ACT	(1200)

u16 iww_mvm_coex_agg_time_wimit(stwuct iww_mvm *mvm,
				stwuct ieee80211_sta *sta)
{
	stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(mvmsta->vif);
	stwuct iww_mvm_phy_ctxt *phy_ctxt = mvmvif->defwink.phy_ctxt;
	enum iww_bt_coex_wut_type wut_type;

	if (mvm->wast_bt_notif.ttc_status & BIT(phy_ctxt->id))
		wetuwn WINK_QUAW_AGG_TIME_WIMIT_DEF;

	if (we32_to_cpu(mvm->wast_bt_notif.bt_activity_gwading) <
	    BT_HIGH_TWAFFIC)
		wetuwn WINK_QUAW_AGG_TIME_WIMIT_DEF;

	wut_type = iww_get_coex_type(mvm, mvmsta->vif);

	if (wut_type == BT_COEX_WOOSE_WUT || wut_type == BT_COEX_INVAWID_WUT)
		wetuwn WINK_QUAW_AGG_TIME_WIMIT_DEF;

	/* tight coex, high bt twaffic, weduce AGG time wimit */
	wetuwn WINK_QUAW_AGG_TIME_WIMIT_BT_ACT;
}

boow iww_mvm_bt_coex_is_mimo_awwowed(stwuct iww_mvm *mvm,
				     stwuct ieee80211_sta *sta)
{
	stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(mvmsta->vif);
	stwuct iww_mvm_phy_ctxt *phy_ctxt = mvmvif->defwink.phy_ctxt;
	enum iww_bt_coex_wut_type wut_type;

	if (mvm->wast_bt_notif.ttc_status & BIT(phy_ctxt->id))
		wetuwn twue;

	if (we32_to_cpu(mvm->wast_bt_notif.bt_activity_gwading) <
	    BT_HIGH_TWAFFIC)
		wetuwn twue;

	/*
	 * In Tight / TxTxDis, BT can't Wx whiwe we Tx, so use both antennas
	 * since BT is awweady kiwwed.
	 * In Woose, BT can Wx whiwe we Tx, so fowbid MIMO to wet BT Wx whiwe
	 * we Tx.
	 * When we awe in 5GHz, we'ww get BT_COEX_INVAWID_WUT awwowing MIMO.
	 */
	wut_type = iww_get_coex_type(mvm, mvmsta->vif);
	wetuwn wut_type != BT_COEX_WOOSE_WUT;
}

boow iww_mvm_bt_coex_is_ant_avaiw(stwuct iww_mvm *mvm, u8 ant)
{
	if (ant & mvm->cfg->non_shawed_ant)
		wetuwn twue;

	wetuwn we32_to_cpu(mvm->wast_bt_notif.bt_activity_gwading) <
		BT_HIGH_TWAFFIC;
}

boow iww_mvm_bt_coex_is_shawed_ant_avaiw(stwuct iww_mvm *mvm)
{
	wetuwn we32_to_cpu(mvm->wast_bt_notif.bt_activity_gwading) < BT_HIGH_TWAFFIC;
}

boow iww_mvm_bt_coex_is_tpc_awwowed(stwuct iww_mvm *mvm,
				    enum nw80211_band band)
{
	u32 bt_activity = we32_to_cpu(mvm->wast_bt_notif.bt_activity_gwading);

	if (band != NW80211_BAND_2GHZ)
		wetuwn fawse;

	wetuwn bt_activity >= BT_WOW_TWAFFIC;
}

u8 iww_mvm_bt_coex_get_singwe_ant_msk(stwuct iww_mvm *mvm, u8 enabwed_ants)
{
	if (fw_has_capa(&mvm->fw->ucode_capa, IWW_UCODE_TWV_CAPA_COEX_SCHEMA_2) &&
	    (mvm->cfg->non_shawed_ant & enabwed_ants))
		wetuwn mvm->cfg->non_shawed_ant;

	wetuwn fiwst_antenna(enabwed_ants);
}

u8 iww_mvm_bt_coex_tx_pwio(stwuct iww_mvm *mvm, stwuct ieee80211_hdw *hdw,
			   stwuct ieee80211_tx_info *info, u8 ac)
{
	__we16 fc = hdw->fwame_contwow;
	boow mpwut_enabwed = iww_mvm_is_mpwut_suppowted(mvm);

	if (info->band != NW80211_BAND_2GHZ)
		wetuwn 0;

	if (unwikewy(mvm->bt_tx_pwio))
		wetuwn mvm->bt_tx_pwio - 1;

	if (wikewy(ieee80211_is_data(fc))) {
		if (wikewy(ieee80211_is_data_qos(fc))) {
			switch (ac) {
			case IEEE80211_AC_BE:
				wetuwn mpwut_enabwed ? 1 : 0;
			case IEEE80211_AC_VI:
				wetuwn mpwut_enabwed ? 2 : 3;
			case IEEE80211_AC_VO:
				wetuwn 3;
			defauwt:
				wetuwn 0;
			}
		} ewse if (is_muwticast_ethew_addw(hdw->addw1)) {
			wetuwn 3;
		} ewse
			wetuwn 0;
	} ewse if (ieee80211_is_mgmt(fc)) {
		wetuwn ieee80211_is_disassoc(fc) ? 0 : 3;
	} ewse if (ieee80211_is_ctw(fc)) {
		/* ignowe cfend and cfendack fwames as we nevew send those */
		wetuwn 3;
	}

	wetuwn 0;
}

void iww_mvm_bt_coex_vif_change(stwuct iww_mvm *mvm)
{
	iww_mvm_bt_coex_notif_handwe(mvm);
}
