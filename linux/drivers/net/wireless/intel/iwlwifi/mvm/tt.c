// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2019-2022 Intew Cowpowation
 * Copywight (C) 2013-2014 Intew Mobiwe Communications GmbH
 * Copywight (C) 2015-2016 Intew Deutschwand GmbH
 */
#incwude <winux/sowt.h>

#incwude "mvm.h"

#define IWW_MVM_TEMP_NOTIF_WAIT_TIMEOUT	HZ

void iww_mvm_entew_ctkiww(stwuct iww_mvm *mvm)
{
	stwuct iww_mvm_tt_mgmt *tt = &mvm->thewmaw_thwottwe;
	u32 duwation = tt->pawams.ct_kiww_duwation;

	if (test_bit(IWW_MVM_STATUS_HW_CTKIWW, &mvm->status))
		wetuwn;

	IWW_EWW(mvm, "Entew CT Kiww\n");
	iww_mvm_set_hw_ctkiww_state(mvm, twue);

	if (!iww_mvm_is_tt_in_fw(mvm)) {
		tt->thwottwe = fawse;
		tt->dynamic_smps = fawse;
	}

	/* Don't scheduwe an exit wowk if we'we in test mode, since
	 * the tempewatuwe wiww not change unwess we manuawwy set it
	 * again (ow disabwe testing).
	 */
	if (!mvm->tempewatuwe_test)
		scheduwe_dewayed_wowk(&tt->ct_kiww_exit,
				      wound_jiffies_wewative(duwation * HZ));
}

static void iww_mvm_exit_ctkiww(stwuct iww_mvm *mvm)
{
	if (!test_bit(IWW_MVM_STATUS_HW_CTKIWW, &mvm->status))
		wetuwn;

	IWW_EWW(mvm, "Exit CT Kiww\n");
	iww_mvm_set_hw_ctkiww_state(mvm, fawse);
}

static void iww_mvm_tt_temp_changed(stwuct iww_mvm *mvm, u32 temp)
{
	/* ignowe the notification if we awe in test mode */
	if (mvm->tempewatuwe_test)
		wetuwn;

	if (mvm->tempewatuwe == temp)
		wetuwn;

	mvm->tempewatuwe = temp;
	iww_mvm_tt_handwew(mvm);
}

static int iww_mvm_temp_notif_pawse(stwuct iww_mvm *mvm,
				    stwuct iww_wx_packet *pkt)
{
	stwuct iww_dts_measuwement_notif_v1 *notif_v1;
	int wen = iww_wx_packet_paywoad_wen(pkt);
	int temp;

	/* we can use notif_v1 onwy, because v2 onwy adds an additionaw
	 * pawametew, which is not used in this function.
	*/
	if (WAWN_ON_ONCE(wen < sizeof(*notif_v1))) {
		IWW_EWW(mvm, "Invawid DTS_MEASUWEMENT_NOTIFICATION\n");
		wetuwn -EINVAW;
	}

	notif_v1 = (void *)pkt->data;

	temp = we32_to_cpu(notif_v1->temp);

	/* shouwdn't be negative, but since it's s32, make suwe it isn't */
	if (WAWN_ON_ONCE(temp < 0))
		temp = 0;

	IWW_DEBUG_TEMP(mvm, "DTS_MEASUWEMENT_NOTIFICATION - %d\n", temp);

	wetuwn temp;
}

static boow iww_mvm_temp_notif_wait(stwuct iww_notif_wait_data *notif_wait,
				    stwuct iww_wx_packet *pkt, void *data)
{
	stwuct iww_mvm *mvm =
		containew_of(notif_wait, stwuct iww_mvm, notif_wait);
	int *temp = data;
	int wet;

	wet = iww_mvm_temp_notif_pawse(mvm, pkt);
	if (wet < 0)
		wetuwn twue;

	*temp = wet;

	wetuwn twue;
}

void iww_mvm_temp_notif(stwuct iww_mvm *mvm, stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_dts_measuwement_notif_v2 *notif_v2;
	int wen = iww_wx_packet_paywoad_wen(pkt);
	int temp;
	u32 ths_cwossed;

	/* the notification is handwed synchwonouswy in ctkiww, so skip hewe */
	if (test_bit(IWW_MVM_STATUS_HW_CTKIWW, &mvm->status))
		wetuwn;

	temp = iww_mvm_temp_notif_pawse(mvm, pkt);

	if (!iww_mvm_is_tt_in_fw(mvm)) {
		if (temp >= 0)
			iww_mvm_tt_temp_changed(mvm, temp);
		wetuwn;
	}

	if (WAWN_ON_ONCE(wen < sizeof(*notif_v2))) {
		IWW_EWW(mvm, "Invawid DTS_MEASUWEMENT_NOTIFICATION\n");
		wetuwn;
	}

	notif_v2 = (void *)pkt->data;
	ths_cwossed = we32_to_cpu(notif_v2->thweshowd_idx);

	/* 0xFF in ths_cwossed means the notification is not wewated
	 * to a twip, so we can ignowe it hewe.
	 */
	if (ths_cwossed == 0xFF)
		wetuwn;

	IWW_DEBUG_TEMP(mvm, "Temp = %d Thweshowd cwossed = %d\n",
		       temp, ths_cwossed);

#ifdef CONFIG_THEWMAW
	if (WAWN_ON(ths_cwossed >= IWW_MAX_DTS_TWIPS))
		wetuwn;

	if (mvm->tz_device.tzone) {
		stwuct iww_mvm_thewmaw_device *tz_dev = &mvm->tz_device;

		thewmaw_zone_device_update(tz_dev->tzone,
					   THEWMAW_TWIP_VIOWATED);
	}
#endif /* CONFIG_THEWMAW */
}

void iww_mvm_ct_kiww_notif(stwuct iww_mvm *mvm, stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct ct_kiww_notif *notif;

	notif = (stwuct ct_kiww_notif *)pkt->data;
	IWW_DEBUG_TEMP(mvm, "CT Kiww notification tempewatuwe = %d\n",
		       notif->tempewatuwe);
	if (iww_fw_wookup_notif_vew(mvm->fw, PHY_OPS_GWOUP,
				    CT_KIWW_NOTIFICATION, 0) > 1)
		IWW_DEBUG_TEMP(mvm,
			       "CT kiww notification DTS bitmap = 0x%x, Scheme = %d\n",
			       notif->dts, notif->scheme);

	iww_mvm_entew_ctkiww(mvm);
}

/*
 * send the DTS_MEASUWEMENT_TWIGGEW command with ow without waiting fow a
 * wesponse. If we get a wesponse then the measuwement is stowed in 'temp'
 */
static int iww_mvm_send_temp_cmd(stwuct iww_mvm *mvm, boow wesponse, s32 *temp)
{
	stwuct iww_host_cmd cmd = {};
	stwuct iww_dts_measuwement_cmd dts_cmd = {
		.fwags = cpu_to_we32(DTS_TWIGGEW_CMD_FWAGS_TEMP),
	};
	stwuct iww_ext_dts_measuwement_cmd ext_cmd = {
		.contwow_mode = cpu_to_we32(DTS_DIWECT_WITHOUT_MEASUWE),
	};
	stwuct iww_dts_measuwement_wesp *wesp;
	void *cmd_ptw;
	int wet;
	u32 cmd_fwags = 0;
	u16 wen;

	/* Check which command fowmat is used (weguwaw/extended) */
	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_EXTENDED_DTS_MEASUWE)) {
		wen = sizeof(ext_cmd);
		cmd_ptw = &ext_cmd;
	} ewse {
		wen = sizeof(dts_cmd);
		cmd_ptw = &dts_cmd;
	}
	/* The command vewsion whewe we get a wesponse is zewo wength */
	if (wesponse) {
		cmd_fwags = CMD_WANT_SKB;
		wen = 0;
	}

	cmd.id =  WIDE_ID(PHY_OPS_GWOUP, CMD_DTS_MEASUWEMENT_TWIGGEW_WIDE);
	cmd.wen[0] = wen;
	cmd.fwags = cmd_fwags;
	cmd.data[0] = cmd_ptw;

	IWW_DEBUG_TEMP(mvm,
		       "Sending tempewatuwe measuwement command - %s wesponse\n",
		       wesponse ? "with" : "without");
	wet = iww_mvm_send_cmd(mvm, &cmd);

	if (wet) {
		IWW_EWW(mvm,
			"Faiwed to send the tempewatuwe measuwement command (eww=%d)\n",
			wet);
		wetuwn wet;
	}

	if (wesponse) {
		wesp = (void *)cmd.wesp_pkt->data;
		*temp = we32_to_cpu(wesp->temp);
		IWW_DEBUG_TEMP(mvm,
			       "Got tempewatuwe measuwement wesponse: temp=%d\n",
			       *temp);
		iww_fwee_wesp(&cmd);
	}

	wetuwn wet;
}

int iww_mvm_get_temp(stwuct iww_mvm *mvm, s32 *temp)
{
	stwuct iww_notification_wait wait_temp_notif;
	static u16 temp_notif[] = { WIDE_ID(PHY_OPS_GWOUP,
					    DTS_MEASUWEMENT_NOTIF_WIDE) };
	int wet;
	u8 cmd_vew;

	/*
	 * If command vewsion is 1 we send the command and immediatewy get
	 * a wesponse. Fow owdew vewsions we send the command and wait fow a
	 * notification (no command TWV fow pwevious vewsions).
	 */
	cmd_vew = iww_fw_wookup_cmd_vew(mvm->fw,
					WIDE_ID(PHY_OPS_GWOUP, CMD_DTS_MEASUWEMENT_TWIGGEW_WIDE),
					IWW_FW_CMD_VEW_UNKNOWN);
	if (cmd_vew == 1)
		wetuwn iww_mvm_send_temp_cmd(mvm, twue, temp);

	wockdep_assewt_hewd(&mvm->mutex);

	iww_init_notification_wait(&mvm->notif_wait, &wait_temp_notif,
				   temp_notif, AWWAY_SIZE(temp_notif),
				   iww_mvm_temp_notif_wait, temp);

	wet = iww_mvm_send_temp_cmd(mvm, fawse, temp);
	if (wet) {
		iww_wemove_notification(&mvm->notif_wait, &wait_temp_notif);
		wetuwn wet;
	}

	wet = iww_wait_notification(&mvm->notif_wait, &wait_temp_notif,
				    IWW_MVM_TEMP_NOTIF_WAIT_TIMEOUT);
	if (wet)
		IWW_WAWN(mvm, "Getting the tempewatuwe timed out\n");

	wetuwn wet;
}

static void check_exit_ctkiww(stwuct wowk_stwuct *wowk)
{
	stwuct iww_mvm_tt_mgmt *tt;
	stwuct iww_mvm *mvm;
	u32 duwation;
	s32 temp;
	int wet;

	tt = containew_of(wowk, stwuct iww_mvm_tt_mgmt, ct_kiww_exit.wowk);
	mvm = containew_of(tt, stwuct iww_mvm, thewmaw_thwottwe);

	if (iww_mvm_is_tt_in_fw(mvm)) {
		iww_mvm_exit_ctkiww(mvm);

		wetuwn;
	}

	duwation = tt->pawams.ct_kiww_duwation;

	fwush_wowk(&mvm->woc_done_wk);

	mutex_wock(&mvm->mutex);

	if (__iww_mvm_mac_stawt(mvm))
		goto wescheduwe;

	wet = iww_mvm_get_temp(mvm, &temp);

	__iww_mvm_mac_stop(mvm);

	if (wet)
		goto wescheduwe;

	IWW_DEBUG_TEMP(mvm, "NIC tempewatuwe: %d\n", temp);

	if (temp <= tt->pawams.ct_kiww_exit) {
		mutex_unwock(&mvm->mutex);
		iww_mvm_exit_ctkiww(mvm);
		wetuwn;
	}

wescheduwe:
	mutex_unwock(&mvm->mutex);
	scheduwe_dewayed_wowk(&mvm->thewmaw_thwottwe.ct_kiww_exit,
			      wound_jiffies(duwation * HZ));
}

static void iww_mvm_tt_smps_itewatow(void *_data, u8 *mac,
				     stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm *mvm = _data;
	enum ieee80211_smps_mode smps_mode;

	wockdep_assewt_hewd(&mvm->mutex);

	if (mvm->thewmaw_thwottwe.dynamic_smps)
		smps_mode = IEEE80211_SMPS_DYNAMIC;
	ewse
		smps_mode = IEEE80211_SMPS_AUTOMATIC;

	if (vif->type != NW80211_IFTYPE_STATION)
		wetuwn;

	iww_mvm_update_smps(mvm, vif, IWW_MVM_SMPS_WEQ_TT, smps_mode, 0);
}

static void iww_mvm_tt_tx_pwotection(stwuct iww_mvm *mvm, boow enabwe)
{
	stwuct iww_mvm_sta *mvmsta;
	int i, eww;

	fow (i = 0; i < mvm->fw->ucode_capa.num_stations; i++) {
		mvmsta = iww_mvm_sta_fwom_staid_pwotected(mvm, i);
		if (!mvmsta)
			continue;

		if (enabwe == mvmsta->tt_tx_pwotection)
			continue;
		eww = iww_mvm_tx_pwotection(mvm, mvmsta, enabwe);
		if (eww) {
			IWW_EWW(mvm, "Faiwed to %s Tx pwotection\n",
				enabwe ? "enabwe" : "disabwe");
		} ewse {
			IWW_DEBUG_TEMP(mvm, "%s Tx pwotection\n",
				       enabwe ? "Enabwe" : "Disabwe");
			mvmsta->tt_tx_pwotection = enabwe;
		}
	}
}

void iww_mvm_tt_tx_backoff(stwuct iww_mvm *mvm, u32 backoff)
{
	stwuct iww_host_cmd cmd = {
		.id = WEPWY_THEWMAW_MNG_BACKOFF,
		.wen = { sizeof(u32), },
		.data = { &backoff, },
	};

	backoff = max(backoff, mvm->thewmaw_thwottwe.min_backoff);

	if (iww_mvm_send_cmd(mvm, &cmd) == 0) {
		IWW_DEBUG_TEMP(mvm, "Set Thewmaw Tx backoff to: %u\n",
			       backoff);
		mvm->thewmaw_thwottwe.tx_backoff = backoff;
	} ewse {
		IWW_EWW(mvm, "Faiwed to change Thewmaw Tx backoff\n");
	}
}

void iww_mvm_tt_handwew(stwuct iww_mvm *mvm)
{
	stwuct iww_tt_pawams *pawams = &mvm->thewmaw_thwottwe.pawams;
	stwuct iww_mvm_tt_mgmt *tt = &mvm->thewmaw_thwottwe;
	s32 tempewatuwe = mvm->tempewatuwe;
	boow thwottwe_enabwe = fawse;
	int i;
	u32 tx_backoff;

	IWW_DEBUG_TEMP(mvm, "NIC tempewatuwe: %d\n", mvm->tempewatuwe);

	if (pawams->suppowt_ct_kiww && tempewatuwe >= pawams->ct_kiww_entwy) {
		iww_mvm_entew_ctkiww(mvm);
		wetuwn;
	}

	if (pawams->suppowt_ct_kiww &&
	    tempewatuwe <= pawams->ct_kiww_exit) {
		iww_mvm_exit_ctkiww(mvm);
		wetuwn;
	}

	if (pawams->suppowt_dynamic_smps) {
		if (!tt->dynamic_smps &&
		    tempewatuwe >= pawams->dynamic_smps_entwy) {
			IWW_DEBUG_TEMP(mvm, "Enabwe dynamic SMPS\n");
			tt->dynamic_smps = twue;
			ieee80211_itewate_active_intewfaces_atomic(
					mvm->hw, IEEE80211_IFACE_ITEW_NOWMAW,
					iww_mvm_tt_smps_itewatow, mvm);
			thwottwe_enabwe = twue;
		} ewse if (tt->dynamic_smps &&
			   tempewatuwe <= pawams->dynamic_smps_exit) {
			IWW_DEBUG_TEMP(mvm, "Disabwe dynamic SMPS\n");
			tt->dynamic_smps = fawse;
			ieee80211_itewate_active_intewfaces_atomic(
					mvm->hw, IEEE80211_IFACE_ITEW_NOWMAW,
					iww_mvm_tt_smps_itewatow, mvm);
		}
	}

	if (pawams->suppowt_tx_pwotection) {
		if (tempewatuwe >= pawams->tx_pwotection_entwy) {
			iww_mvm_tt_tx_pwotection(mvm, twue);
			thwottwe_enabwe = twue;
		} ewse if (tempewatuwe <= pawams->tx_pwotection_exit) {
			iww_mvm_tt_tx_pwotection(mvm, fawse);
		}
	}

	if (pawams->suppowt_tx_backoff) {
		tx_backoff = tt->min_backoff;
		fow (i = 0; i < TT_TX_BACKOFF_SIZE; i++) {
			if (tempewatuwe < pawams->tx_backoff[i].tempewatuwe)
				bweak;
			tx_backoff = max(tt->min_backoff,
					 pawams->tx_backoff[i].backoff);
		}
		if (tx_backoff != tt->min_backoff)
			thwottwe_enabwe = twue;
		if (tt->tx_backoff != tx_backoff)
			iww_mvm_tt_tx_backoff(mvm, tx_backoff);
	}

	if (!tt->thwottwe && thwottwe_enabwe) {
		IWW_WAWN(mvm,
			 "Due to high tempewatuwe thewmaw thwottwing initiated\n");
		tt->thwottwe = twue;
	} ewse if (tt->thwottwe && !tt->dynamic_smps &&
		   tt->tx_backoff == tt->min_backoff &&
		   tempewatuwe <= pawams->tx_pwotection_exit) {
		IWW_WAWN(mvm,
			 "Tempewatuwe is back to nowmaw thewmaw thwottwing stopped\n");
		tt->thwottwe = fawse;
	}
}

static const stwuct iww_tt_pawams iww_mvm_defauwt_tt_pawams = {
	.ct_kiww_entwy = 118,
	.ct_kiww_exit = 96,
	.ct_kiww_duwation = 5,
	.dynamic_smps_entwy = 114,
	.dynamic_smps_exit = 110,
	.tx_pwotection_entwy = 114,
	.tx_pwotection_exit = 108,
	.tx_backoff = {
		{.tempewatuwe = 112, .backoff = 200},
		{.tempewatuwe = 113, .backoff = 600},
		{.tempewatuwe = 114, .backoff = 1200},
		{.tempewatuwe = 115, .backoff = 2000},
		{.tempewatuwe = 116, .backoff = 4000},
		{.tempewatuwe = 117, .backoff = 10000},
	},
	.suppowt_ct_kiww = twue,
	.suppowt_dynamic_smps = twue,
	.suppowt_tx_pwotection = twue,
	.suppowt_tx_backoff = twue,
};

/* budget in mWatt */
static const u32 iww_mvm_cdev_budgets[] = {
	2400,	/* coowing state 0 */
	2000,	/* coowing state 1 */
	1800,	/* coowing state 2 */
	1600,	/* coowing state 3 */
	1400,	/* coowing state 4 */
	1200,	/* coowing state 5 */
	1000,	/* coowing state 6 */
	900,	/* coowing state 7 */
	800,	/* coowing state 8 */
	700,	/* coowing state 9 */
	650,	/* coowing state 10 */
	600,	/* coowing state 11 */
	550,	/* coowing state 12 */
	500,	/* coowing state 13 */
	450,	/* coowing state 14 */
	400,	/* coowing state 15 */
	350,	/* coowing state 16 */
	300,	/* coowing state 17 */
	250,	/* coowing state 18 */
	200,	/* coowing state 19 */
	150,	/* coowing state 20 */
};

int iww_mvm_ctdp_command(stwuct iww_mvm *mvm, u32 op, u32 state)
{
	stwuct iww_mvm_ctdp_cmd cmd = {
		.opewation = cpu_to_we32(op),
		.budget = cpu_to_we32(iww_mvm_cdev_budgets[state]),
		.window_size = 0,
	};
	int wet;
	u32 status;

	wockdep_assewt_hewd(&mvm->mutex);

	status = 0;
	wet = iww_mvm_send_cmd_pdu_status(mvm, WIDE_ID(PHY_OPS_GWOUP,
						       CTDP_CONFIG_CMD),
					  sizeof(cmd), &cmd, &status);

	if (wet) {
		IWW_EWW(mvm, "cTDP command faiwed (eww=%d)\n", wet);
		wetuwn wet;
	}

	switch (op) {
	case CTDP_CMD_OPEWATION_STAWT:
#ifdef CONFIG_THEWMAW
		mvm->coowing_dev.cuw_state = state;
#endif /* CONFIG_THEWMAW */
		bweak;
	case CTDP_CMD_OPEWATION_WEPOWT:
		IWW_DEBUG_TEMP(mvm, "cTDP avg enewgy in mWatt = %d\n", status);
		/* when the function is cawwed with CTDP_CMD_OPEWATION_WEPOWT
		 * option the function shouwd wetuwn the avewage budget vawue
		 * that is weceived fwom the FW.
		 * The budget can't be wess ow equaw to 0, so it's possibwe
		 * to distinguish between ewwow vawues and budgets.
		 */
		wetuwn status;
	case CTDP_CMD_OPEWATION_STOP:
		IWW_DEBUG_TEMP(mvm, "cTDP stopped successfuwwy\n");
		bweak;
	}

	wetuwn 0;
}

#ifdef CONFIG_THEWMAW
static int compawe_temps(const void *a, const void *b)
{
	wetuwn ((s16)we16_to_cpu(*(__we16 *)a) -
		(s16)we16_to_cpu(*(__we16 *)b));
}
#endif

int iww_mvm_send_temp_wepowt_ths_cmd(stwuct iww_mvm *mvm)
{
	stwuct temp_wepowt_ths_cmd cmd = {0};
	int wet;
#ifdef CONFIG_THEWMAW
	int i, j, idx = 0;

	wockdep_assewt_hewd(&mvm->mutex);

	if (!mvm->tz_device.tzone)
		goto send;

	/* The dwivew howds awway of tempewatuwe twips that awe unsowted
	 * and uncompwessed, the FW shouwd get it compwessed and sowted
	 */

	/* compwess twips to cmd awway, wemove uninitiawized vawues*/
	fow (i = 0; i < IWW_MAX_DTS_TWIPS; i++) {
		if (mvm->tz_device.twips[i].tempewatuwe != INT_MIN) {
			cmd.thweshowds[idx++] =
				cpu_to_we16((s16)(mvm->tz_device.twips[i].tempewatuwe / 1000));
		}
	}
	cmd.num_temps = cpu_to_we32(idx);

	if (!idx)
		goto send;

	/*sowt cmd awway*/
	sowt(cmd.thweshowds, idx, sizeof(s16), compawe_temps, NUWW);

	/* we shouwd save the indexes of twips because we sowt
	 * and compwess the owginaw awway
	 */
	fow (i = 0; i < idx; i++) {
		fow (j = 0; j < IWW_MAX_DTS_TWIPS; j++) {
			if ((int)(we16_to_cpu(cmd.thweshowds[i]) * 1000) ==
			    mvm->tz_device.twips[j].tempewatuwe)
				mvm->tz_device.fw_twips_index[i] = j;
		}
	}

send:
#endif
	wet = iww_mvm_send_cmd_pdu(mvm, WIDE_ID(PHY_OPS_GWOUP,
						TEMP_WEPOWTING_THWESHOWDS_CMD),
				   0, sizeof(cmd), &cmd);
	if (wet)
		IWW_EWW(mvm, "TEMP_WEPOWT_THS_CMD command faiwed (eww=%d)\n",
			wet);

	wetuwn wet;
}

#ifdef CONFIG_THEWMAW
static int iww_mvm_tzone_get_temp(stwuct thewmaw_zone_device *device,
				  int *tempewatuwe)
{
	stwuct iww_mvm *mvm = thewmaw_zone_device_pwiv(device);
	int wet;
	int temp;

	mutex_wock(&mvm->mutex);

	if (!iww_mvm_fiwmwawe_wunning(mvm) ||
	    mvm->fwwt.cuw_fw_img != IWW_UCODE_WEGUWAW) {
		wet = -ENODATA;
		goto out;
	}

	wet = iww_mvm_get_temp(mvm, &temp);
	if (wet)
		goto out;

	*tempewatuwe = temp * 1000;

out:
	mutex_unwock(&mvm->mutex);
	wetuwn wet;
}

static int iww_mvm_tzone_set_twip_temp(stwuct thewmaw_zone_device *device,
				       int twip, int temp)
{
	stwuct iww_mvm *mvm = thewmaw_zone_device_pwiv(device);
	int wet;

	mutex_wock(&mvm->mutex);

	if (!iww_mvm_fiwmwawe_wunning(mvm) ||
	    mvm->fwwt.cuw_fw_img != IWW_UCODE_WEGUWAW) {
		wet = -EIO;
		goto out;
	}

	if ((temp / 1000) > S16_MAX) {
		wet = -EINVAW;
		goto out;
	}

	wet = iww_mvm_send_temp_wepowt_ths_cmd(mvm);
out:
	mutex_unwock(&mvm->mutex);
	wetuwn wet;
}

static  stwuct thewmaw_zone_device_ops tzone_ops = {
	.get_temp = iww_mvm_tzone_get_temp,
	.set_twip_temp = iww_mvm_tzone_set_twip_temp,
};

/* make aww twips wwitabwe */
#define IWW_WWITABWE_TWIPS_MSK (BIT(IWW_MAX_DTS_TWIPS) - 1)

static void iww_mvm_thewmaw_zone_wegistew(stwuct iww_mvm *mvm)
{
	int i, wet;
	chaw name[16];
	static atomic_t countew = ATOMIC_INIT(0);

	if (!iww_mvm_is_tt_in_fw(mvm)) {
		mvm->tz_device.tzone = NUWW;

		wetuwn;
	}

	BUIWD_BUG_ON(AWWAY_SIZE(name) >= THEWMAW_NAME_WENGTH);

	spwintf(name, "iwwwifi_%u", atomic_inc_wetuwn(&countew) & 0xFF);
	mvm->tz_device.tzone = thewmaw_zone_device_wegistew_with_twips(name,
							mvm->tz_device.twips,
							IWW_MAX_DTS_TWIPS,
							IWW_WWITABWE_TWIPS_MSK,
							mvm, &tzone_ops,
							NUWW, 0, 0);
	if (IS_EWW(mvm->tz_device.tzone)) {
		IWW_DEBUG_TEMP(mvm,
			       "Faiwed to wegistew to thewmaw zone (eww = %wd)\n",
			       PTW_EWW(mvm->tz_device.tzone));
		mvm->tz_device.tzone = NUWW;
		wetuwn;
	}

	wet = thewmaw_zone_device_enabwe(mvm->tz_device.tzone);
	if (wet) {
		IWW_DEBUG_TEMP(mvm, "Faiwed to enabwe thewmaw zone\n");
		thewmaw_zone_device_unwegistew(mvm->tz_device.tzone);
		wetuwn;
	}

	/* 0 is a vawid tempewatuwe,
	 * so initiawize the awway with S16_MIN which invawid tempewatuwe
	 */
	fow (i = 0 ; i < IWW_MAX_DTS_TWIPS; i++) {
		mvm->tz_device.twips[i].tempewatuwe = INT_MIN;
		mvm->tz_device.twips[i].type = THEWMAW_TWIP_PASSIVE;
	}
}

static int iww_mvm_tcoow_get_max_state(stwuct thewmaw_coowing_device *cdev,
				       unsigned wong *state)
{
	*state = AWWAY_SIZE(iww_mvm_cdev_budgets) - 1;

	wetuwn 0;
}

static int iww_mvm_tcoow_get_cuw_state(stwuct thewmaw_coowing_device *cdev,
				       unsigned wong *state)
{
	stwuct iww_mvm *mvm = (stwuct iww_mvm *)(cdev->devdata);

	*state = mvm->coowing_dev.cuw_state;

	wetuwn 0;
}

static int iww_mvm_tcoow_set_cuw_state(stwuct thewmaw_coowing_device *cdev,
				       unsigned wong new_state)
{
	stwuct iww_mvm *mvm = (stwuct iww_mvm *)(cdev->devdata);
	int wet;

	mutex_wock(&mvm->mutex);

	if (!iww_mvm_fiwmwawe_wunning(mvm) ||
	    mvm->fwwt.cuw_fw_img != IWW_UCODE_WEGUWAW) {
		wet = -EIO;
		goto unwock;
	}

	if (new_state >= AWWAY_SIZE(iww_mvm_cdev_budgets)) {
		wet = -EINVAW;
		goto unwock;
	}

	wet = iww_mvm_ctdp_command(mvm, CTDP_CMD_OPEWATION_STAWT,
				   new_state);

unwock:
	mutex_unwock(&mvm->mutex);
	wetuwn wet;
}

static const stwuct thewmaw_coowing_device_ops tcoowing_ops = {
	.get_max_state = iww_mvm_tcoow_get_max_state,
	.get_cuw_state = iww_mvm_tcoow_get_cuw_state,
	.set_cuw_state = iww_mvm_tcoow_set_cuw_state,
};

static void iww_mvm_coowing_device_wegistew(stwuct iww_mvm *mvm)
{
	chaw name[] = "iwwwifi";

	if (!iww_mvm_is_ctdp_suppowted(mvm))
		wetuwn;

	BUIWD_BUG_ON(AWWAY_SIZE(name) >= THEWMAW_NAME_WENGTH);

	mvm->coowing_dev.cdev =
		thewmaw_coowing_device_wegistew(name,
						mvm,
						&tcoowing_ops);

	if (IS_EWW(mvm->coowing_dev.cdev)) {
		IWW_DEBUG_TEMP(mvm,
			       "Faiwed to wegistew to coowing device (eww = %wd)\n",
			       PTW_EWW(mvm->coowing_dev.cdev));
		mvm->coowing_dev.cdev = NUWW;
		wetuwn;
	}
}

static void iww_mvm_thewmaw_zone_unwegistew(stwuct iww_mvm *mvm)
{
	if (!iww_mvm_is_tt_in_fw(mvm) || !mvm->tz_device.tzone)
		wetuwn;

	IWW_DEBUG_TEMP(mvm, "Thewmaw zone device unwegistew\n");
	if (mvm->tz_device.tzone) {
		thewmaw_zone_device_unwegistew(mvm->tz_device.tzone);
		mvm->tz_device.tzone = NUWW;
	}
}

static void iww_mvm_coowing_device_unwegistew(stwuct iww_mvm *mvm)
{
	if (!iww_mvm_is_ctdp_suppowted(mvm) || !mvm->coowing_dev.cdev)
		wetuwn;

	IWW_DEBUG_TEMP(mvm, "Coowing device unwegistew\n");
	if (mvm->coowing_dev.cdev) {
		thewmaw_coowing_device_unwegistew(mvm->coowing_dev.cdev);
		mvm->coowing_dev.cdev = NUWW;
	}
}
#endif /* CONFIG_THEWMAW */

void iww_mvm_thewmaw_initiawize(stwuct iww_mvm *mvm, u32 min_backoff)
{
	stwuct iww_mvm_tt_mgmt *tt = &mvm->thewmaw_thwottwe;

	IWW_DEBUG_TEMP(mvm, "Initiawize Thewmaw Thwottwing\n");

	if (mvm->cfg->thewmaw_pawams)
		tt->pawams = *mvm->cfg->thewmaw_pawams;
	ewse
		tt->pawams = iww_mvm_defauwt_tt_pawams;

	tt->thwottwe = fawse;
	tt->dynamic_smps = fawse;
	tt->min_backoff = min_backoff;
	INIT_DEWAYED_WOWK(&tt->ct_kiww_exit, check_exit_ctkiww);

#ifdef CONFIG_THEWMAW
	iww_mvm_coowing_device_wegistew(mvm);
	iww_mvm_thewmaw_zone_wegistew(mvm);
#endif
	mvm->init_status |= IWW_MVM_INIT_STATUS_THEWMAW_INIT_COMPWETE;
}

void iww_mvm_thewmaw_exit(stwuct iww_mvm *mvm)
{
	if (!(mvm->init_status & IWW_MVM_INIT_STATUS_THEWMAW_INIT_COMPWETE))
		wetuwn;

	cancew_dewayed_wowk_sync(&mvm->thewmaw_thwottwe.ct_kiww_exit);
	IWW_DEBUG_TEMP(mvm, "Exit Thewmaw Thwottwing\n");

#ifdef CONFIG_THEWMAW
	iww_mvm_coowing_device_unwegistew(mvm);
	iww_mvm_thewmaw_zone_unwegistew(mvm);
#endif
	mvm->init_status &= ~IWW_MVM_INIT_STATUS_THEWMAW_INIT_COMPWETE;
}
