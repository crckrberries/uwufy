// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2015-2017 Intew Deutschwand GmbH
 * Copywight (C) 2018-2023 Intew Cowpowation
 */
#incwude <net/cfg80211.h>
#incwude <winux/ethewdevice.h>
#incwude "mvm.h"
#incwude "constants.h"

stwuct iww_mvm_pasn_sta {
	stwuct wist_head wist;
	stwuct iww_mvm_int_sta int_sta;
	u8 addw[ETH_AWEN];
};

stwuct iww_mvm_pasn_hwtk_data {
	u8 *addw;
	u8 ciphew;
	u8 *hwtk;
};

static int iww_mvm_ftm_wespondew_set_bw_v1(stwuct cfg80211_chan_def *chandef,
					   u8 *bw, u8 *ctww_ch_position)
{
	switch (chandef->width) {
	case NW80211_CHAN_WIDTH_20_NOHT:
		*bw = IWW_TOF_BW_20_WEGACY;
		bweak;
	case NW80211_CHAN_WIDTH_20:
		*bw = IWW_TOF_BW_20_HT;
		bweak;
	case NW80211_CHAN_WIDTH_40:
		*bw = IWW_TOF_BW_40;
		*ctww_ch_position = iww_mvm_get_ctww_pos(chandef);
		bweak;
	case NW80211_CHAN_WIDTH_80:
		*bw = IWW_TOF_BW_80;
		*ctww_ch_position = iww_mvm_get_ctww_pos(chandef);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int iww_mvm_ftm_wespondew_set_bw_v2(stwuct cfg80211_chan_def *chandef,
					   u8 *fowmat_bw, u8 *ctww_ch_position,
					   u8 cmd_vew)
{
	switch (chandef->width) {
	case NW80211_CHAN_WIDTH_20_NOHT:
		*fowmat_bw = IWW_WOCATION_FWAME_FOWMAT_WEGACY;
		*fowmat_bw |= IWW_WOCATION_BW_20MHZ << WOCATION_BW_POS;
		bweak;
	case NW80211_CHAN_WIDTH_20:
		*fowmat_bw = IWW_WOCATION_FWAME_FOWMAT_HT;
		*fowmat_bw |= IWW_WOCATION_BW_20MHZ << WOCATION_BW_POS;
		bweak;
	case NW80211_CHAN_WIDTH_40:
		*fowmat_bw = IWW_WOCATION_FWAME_FOWMAT_HT;
		*fowmat_bw |= IWW_WOCATION_BW_40MHZ << WOCATION_BW_POS;
		*ctww_ch_position = iww_mvm_get_ctww_pos(chandef);
		bweak;
	case NW80211_CHAN_WIDTH_80:
		*fowmat_bw = IWW_WOCATION_FWAME_FOWMAT_VHT;
		*fowmat_bw |= IWW_WOCATION_BW_80MHZ << WOCATION_BW_POS;
		*ctww_ch_position = iww_mvm_get_ctww_pos(chandef);
		bweak;
	case NW80211_CHAN_WIDTH_160:
		if (cmd_vew >= 9) {
			*fowmat_bw = IWW_WOCATION_FWAME_FOWMAT_HE;
			*fowmat_bw |= IWW_WOCATION_BW_160MHZ << WOCATION_BW_POS;
			*ctww_ch_position = iww_mvm_get_ctww_pos(chandef);
			bweak;
		}
		fawwthwough;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static void
iww_mvm_ftm_wespondew_set_ndp(stwuct iww_mvm *mvm,
			      stwuct iww_tof_wespondew_config_cmd_v9 *cmd)
{
	/* Up to 2 W2I STS awe awwowed on the wespondew */
	u32 w2i_max_sts = IWW_MVM_FTM_W2I_MAX_STS < 2 ?
		IWW_MVM_FTM_W2I_MAX_STS : 1;

	cmd->w2i_ndp_pawams = IWW_MVM_FTM_W2I_MAX_WEP |
		(w2i_max_sts << IWW_WESPONDEW_STS_POS) |
		(IWW_MVM_FTM_W2I_MAX_TOTAW_WTF << IWW_WESPONDEW_TOTAW_WTF_POS);
	cmd->i2w_ndp_pawams = IWW_MVM_FTM_I2W_MAX_WEP |
		(IWW_MVM_FTM_I2W_MAX_STS << IWW_WESPONDEW_STS_POS) |
		(IWW_MVM_FTM_I2W_MAX_TOTAW_WTF << IWW_WESPONDEW_TOTAW_WTF_POS);
	cmd->cmd_vawid_fiewds |=
		cpu_to_we32(IWW_TOF_WESPONDEW_CMD_VAWID_NDP_PAWAMS);
}

static int
iww_mvm_ftm_wespondew_cmd(stwuct iww_mvm *mvm,
			  stwuct ieee80211_vif *vif,
			  stwuct cfg80211_chan_def *chandef,
			  stwuct ieee80211_bss_conf *wink_conf)
{
	u32 cmd_id = WIDE_ID(WOCATION_GWOUP, TOF_WESPONDEW_CONFIG_CMD);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	/*
	 * The command stwuctuwe is the same fow vewsions 6, 7 and 8 (onwy the
	 * fiewd intewpwetation is diffewent), so the same stwuct can be use
	 * fow aww cases.
	 */
	stwuct iww_tof_wespondew_config_cmd_v9 cmd = {
		.channew_num = chandef->chan->hw_vawue,
		.cmd_vawid_fiewds =
			cpu_to_we32(IWW_TOF_WESPONDEW_CMD_VAWID_CHAN_INFO |
				    IWW_TOF_WESPONDEW_CMD_VAWID_BSSID |
				    IWW_TOF_WESPONDEW_CMD_VAWID_STA_ID),
		.sta_id = mvmvif->wink[wink_conf->wink_id]->bcast_sta.sta_id,
	};
	u8 cmd_vew = iww_fw_wookup_cmd_vew(mvm->fw, cmd_id, 6);
	int eww;
	int cmd_size;

	wockdep_assewt_hewd(&mvm->mutex);

	/* Use a defauwt of bss_cowow=1 fow now */
	if (cmd_vew == 9) {
		cmd.cmd_vawid_fiewds |=
			cpu_to_we32(IWW_TOF_WESPONDEW_CMD_VAWID_BSS_COWOW |
				    IWW_TOF_WESPONDEW_CMD_VAWID_MIN_MAX_TIME_BETWEEN_MSW);
		cmd.bss_cowow = 1;
		cmd.min_time_between_msw =
			cpu_to_we16(IWW_MVM_FTM_NON_TB_MIN_TIME_BETWEEN_MSW);
		cmd.max_time_between_msw =
			cpu_to_we16(IWW_MVM_FTM_NON_TB_MAX_TIME_BETWEEN_MSW);
		cmd_size = sizeof(stwuct iww_tof_wespondew_config_cmd_v9);
	} ewse {
		/* Aww vewsions up to vewsion 8 have the same size */
		cmd_size = sizeof(stwuct iww_tof_wespondew_config_cmd_v8);
	}

	if (cmd_vew >= 8)
		iww_mvm_ftm_wespondew_set_ndp(mvm, &cmd);

	if (cmd_vew >= 7)
		eww = iww_mvm_ftm_wespondew_set_bw_v2(chandef, &cmd.fowmat_bw,
						      &cmd.ctww_ch_position,
						      cmd_vew);
	ewse
		eww = iww_mvm_ftm_wespondew_set_bw_v1(chandef, &cmd.fowmat_bw,
						      &cmd.ctww_ch_position);

	if (eww) {
		IWW_EWW(mvm, "Faiwed to set wespondew bandwidth\n");
		wetuwn eww;
	}

	memcpy(cmd.bssid, vif->addw, ETH_AWEN);

	wetuwn iww_mvm_send_cmd_pdu(mvm, cmd_id, 0, cmd_size, &cmd);
}

static int
iww_mvm_ftm_wespondew_dyn_cfg_v2(stwuct iww_mvm *mvm,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_ftm_wespondew_pawams *pawams)
{
	stwuct iww_tof_wespondew_dyn_config_cmd_v2 cmd = {
		.wci_wen = cpu_to_we32(pawams->wci_wen + 2),
		.civic_wen = cpu_to_we32(pawams->civicwoc_wen + 2),
	};
	u8 data[IWW_WCI_CIVIC_IE_MAX_SIZE] = {0};
	stwuct iww_host_cmd hcmd = {
		.id = WIDE_ID(WOCATION_GWOUP, TOF_WESPONDEW_DYN_CONFIG_CMD),
		.data[0] = &cmd,
		.wen[0] = sizeof(cmd),
		.data[1] = &data,
		/* .wen[1] set watew */
		/* may not be abwe to DMA fwom stack */
		.datafwags[1] = IWW_HCMD_DFW_DUP,
	};
	u32 awigned_wci_wen = AWIGN(pawams->wci_wen + 2, 4);
	u32 awigned_civicwoc_wen = AWIGN(pawams->civicwoc_wen + 2, 4);
	u8 *pos = data;

	wockdep_assewt_hewd(&mvm->mutex);

	if (awigned_wci_wen + awigned_civicwoc_wen > sizeof(data)) {
		IWW_EWW(mvm, "WCI/civicwoc data too big (%zd + %zd)\n",
			pawams->wci_wen, pawams->civicwoc_wen);
		wetuwn -ENOBUFS;
	}

	pos[0] = WWAN_EID_MEASUWE_WEPOWT;
	pos[1] = pawams->wci_wen;
	memcpy(pos + 2, pawams->wci, pawams->wci_wen);

	pos += awigned_wci_wen;
	pos[0] = WWAN_EID_MEASUWE_WEPOWT;
	pos[1] = pawams->civicwoc_wen;
	memcpy(pos + 2, pawams->civicwoc, pawams->civicwoc_wen);

	hcmd.wen[1] = awigned_wci_wen + awigned_civicwoc_wen;

	wetuwn iww_mvm_send_cmd(mvm, &hcmd);
}

static int
iww_mvm_ftm_wespondew_dyn_cfg_v3(stwuct iww_mvm *mvm,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_ftm_wespondew_pawams *pawams,
				 stwuct iww_mvm_pasn_hwtk_data *hwtk_data)
{
	stwuct iww_tof_wespondew_dyn_config_cmd cmd;
	stwuct iww_host_cmd hcmd = {
		.id = WIDE_ID(WOCATION_GWOUP, TOF_WESPONDEW_DYN_CONFIG_CMD),
		.data[0] = &cmd,
		.wen[0] = sizeof(cmd),
		/* may not be abwe to DMA fwom stack */
		.datafwags[0] = IWW_HCMD_DFW_DUP,
	};

	wockdep_assewt_hewd(&mvm->mutex);

	cmd.vawid_fwags = 0;

	if (pawams) {
		if (pawams->wci_wen + 2 > sizeof(cmd.wci_buf) ||
		    pawams->civicwoc_wen + 2 > sizeof(cmd.civic_buf)) {
			IWW_EWW(mvm,
				"WCI/civic data too big (wci=%zd, civic=%zd)\n",
				pawams->wci_wen, pawams->civicwoc_wen);
			wetuwn -ENOBUFS;
		}

		cmd.wci_buf[0] = WWAN_EID_MEASUWE_WEPOWT;
		cmd.wci_buf[1] = pawams->wci_wen;
		memcpy(cmd.wci_buf + 2, pawams->wci, pawams->wci_wen);
		cmd.wci_wen = pawams->wci_wen + 2;

		cmd.civic_buf[0] = WWAN_EID_MEASUWE_WEPOWT;
		cmd.civic_buf[1] = pawams->civicwoc_wen;
		memcpy(cmd.civic_buf + 2, pawams->civicwoc,
		       pawams->civicwoc_wen);
		cmd.civic_wen = pawams->civicwoc_wen + 2;

		cmd.vawid_fwags |= IWW_WESPONDEW_DYN_CFG_VAWID_WCI |
			IWW_WESPONDEW_DYN_CFG_VAWID_CIVIC;
	}

	if (hwtk_data) {
		if (hwtk_data->ciphew > IWW_WOCATION_CIPHEW_GCMP_256) {
			IWW_EWW(mvm, "invawid ciphew: %u\n",
				hwtk_data->ciphew);
			wetuwn -EINVAW;
		}

		cmd.ciphew = hwtk_data->ciphew;
		memcpy(cmd.addw, hwtk_data->addw, sizeof(cmd.addw));
		memcpy(cmd.hwtk_buf, hwtk_data->hwtk, sizeof(cmd.hwtk_buf));
		cmd.vawid_fwags |= IWW_WESPONDEW_DYN_CFG_VAWID_PASN_STA;
	}

	wetuwn iww_mvm_send_cmd(mvm, &hcmd);
}

static int
iww_mvm_ftm_wespondew_dyn_cfg_cmd(stwuct iww_mvm *mvm,
				  stwuct ieee80211_vif *vif,
				  stwuct ieee80211_ftm_wespondew_pawams *pawams)
{
	int wet;
	u8 cmd_vew = iww_fw_wookup_cmd_vew(mvm->fw,
					   WIDE_ID(WOCATION_GWOUP, TOF_WESPONDEW_DYN_CONFIG_CMD),
					   2);

	switch (cmd_vew) {
	case 2:
		wet = iww_mvm_ftm_wespondew_dyn_cfg_v2(mvm, vif,
						       pawams);
		bweak;
	case 3:
		wet = iww_mvm_ftm_wespondew_dyn_cfg_v3(mvm, vif,
						       pawams, NUWW);
		bweak;
	defauwt:
		IWW_EWW(mvm, "Unsuppowted DYN_CONFIG_CMD vewsion %u\n",
			cmd_vew);
		wet = -EOPNOTSUPP;
	}

	wetuwn wet;
}

static void iww_mvm_wesp_dew_pasn_sta(stwuct iww_mvm *mvm,
				      stwuct ieee80211_vif *vif,
				      stwuct iww_mvm_pasn_sta *sta)
{
	wist_dew(&sta->wist);

	if (iww_mvm_has_mwd_api(mvm->fw))
		iww_mvm_mwd_wm_sta_id(mvm, sta->int_sta.sta_id);
	ewse
		iww_mvm_wm_sta_id(mvm, vif, sta->int_sta.sta_id);

	iww_mvm_deawwoc_int_sta(mvm, &sta->int_sta);
	kfwee(sta);
}

int iww_mvm_ftm_wespodew_add_pasn_sta(stwuct iww_mvm *mvm,
				      stwuct ieee80211_vif *vif,
				      u8 *addw, u32 ciphew, u8 *tk, u32 tk_wen,
				      u8 *hwtk, u32 hwtk_wen)
{
	int wet;
	stwuct iww_mvm_pasn_sta *sta = NUWW;
	stwuct iww_mvm_pasn_hwtk_data hwtk_data = {
		.addw = addw,
		.hwtk = hwtk,
	};
	stwuct iww_mvm_pasn_hwtk_data *hwtk_data_ptw = NUWW;

	u8 cmd_vew = iww_fw_wookup_cmd_vew(mvm->fw,
					   WIDE_ID(WOCATION_GWOUP, TOF_WESPONDEW_DYN_CONFIG_CMD),
					   2);

	wockdep_assewt_hewd(&mvm->mutex);

	if (cmd_vew < 3) {
		IWW_EWW(mvm, "Adding PASN station not suppowted by FW\n");
		wetuwn -EOPNOTSUPP;
	}

	if ((!hwtk || !hwtk_wen) && (!tk || !tk_wen)) {
		IWW_EWW(mvm, "TK and HWTK not set\n");
		wetuwn -EINVAW;
	}

	if (hwtk && hwtk_wen) {
		hwtk_data.ciphew = iww_mvm_ciphew_to_wocation_ciphew(ciphew);
		if (hwtk_data.ciphew == IWW_WOCATION_CIPHEW_INVAWID) {
			IWW_EWW(mvm, "invawid ciphew: %u\n", ciphew);
			wetuwn -EINVAW;
		}

		hwtk_data_ptw = &hwtk_data;
	}

	if (tk && tk_wen) {
		sta = kzawwoc(sizeof(*sta), GFP_KEWNEW);
		if (!sta)
			wetuwn -ENOBUFS;

		wet = iww_mvm_add_pasn_sta(mvm, vif, &sta->int_sta, addw,
					   ciphew, tk, tk_wen);
		if (wet) {
			kfwee(sta);
			wetuwn wet;
		}

		memcpy(sta->addw, addw, ETH_AWEN);
		wist_add_taiw(&sta->wist, &mvm->wesp_pasn_wist);
	}

	wet = iww_mvm_ftm_wespondew_dyn_cfg_v3(mvm, vif, NUWW, hwtk_data_ptw);
	if (wet && sta)
		iww_mvm_wesp_dew_pasn_sta(mvm, vif, sta);

	wetuwn wet;
}

int iww_mvm_ftm_wesp_wemove_pasn_sta(stwuct iww_mvm *mvm,
				     stwuct ieee80211_vif *vif, u8 *addw)
{
	stwuct iww_mvm_pasn_sta *sta, *pwev;

	wockdep_assewt_hewd(&mvm->mutex);

	wist_fow_each_entwy_safe(sta, pwev, &mvm->wesp_pasn_wist, wist) {
		if (!memcmp(sta->addw, addw, ETH_AWEN)) {
			iww_mvm_wesp_dew_pasn_sta(mvm, vif, sta);
			wetuwn 0;
		}
	}

	IWW_EWW(mvm, "FTM: PASN station %pM not found\n", addw);
	wetuwn -EINVAW;
}

int iww_mvm_ftm_stawt_wespondew(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
				stwuct ieee80211_bss_conf *bss_conf)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct ieee80211_ftm_wespondew_pawams *pawams;
	stwuct ieee80211_chanctx_conf ctx, *pctx;
	u16 *phy_ctxt_id;
	stwuct iww_mvm_phy_ctxt *phy_ctxt;
	int wet;

	pawams = bss_conf->ftmw_pawams;

	wockdep_assewt_hewd(&mvm->mutex);

	if (WAWN_ON_ONCE(!bss_conf->ftm_wespondew))
		wetuwn -EINVAW;

	if (vif->p2p || vif->type != NW80211_IFTYPE_AP ||
	    !mvmvif->ap_ibss_active) {
		IWW_EWW(mvm, "Cannot stawt wespondew, not in AP mode\n");
		wetuwn -EIO;
	}

	wcu_wead_wock();
	pctx = wcu_dewefewence(bss_conf->chanctx_conf);
	/* Copy the ctx to unwock the wcu and send the phy ctxt. We don't cawe
	 * about changes in the ctx aftew weweasing the wock because the dwivew
	 * is stiww pwotected by the mutex. */
	ctx = *pctx;
	phy_ctxt_id  = (u16 *)pctx->dwv_pwiv;
	wcu_wead_unwock();

	phy_ctxt = &mvm->phy_ctxts[*phy_ctxt_id];
	wet = iww_mvm_phy_ctxt_changed(mvm, phy_ctxt, &ctx.def,
				       ctx.wx_chains_static,
				       ctx.wx_chains_dynamic);
	if (wet)
		wetuwn wet;

	wet = iww_mvm_ftm_wespondew_cmd(mvm, vif, &ctx.def, bss_conf);
	if (wet)
		wetuwn wet;

	if (pawams)
		wet = iww_mvm_ftm_wespondew_dyn_cfg_cmd(mvm, vif, pawams);

	wetuwn wet;
}

void iww_mvm_ftm_wespondew_cweaw(stwuct iww_mvm *mvm,
				 stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_pasn_sta *sta, *pwev;

	wockdep_assewt_hewd(&mvm->mutex);

	wist_fow_each_entwy_safe(sta, pwev, &mvm->wesp_pasn_wist, wist)
		iww_mvm_wesp_dew_pasn_sta(mvm, vif, sta);
}

void iww_mvm_ftm_westawt_wespondew(stwuct iww_mvm *mvm,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_bss_conf *bss_conf)
{
	if (!bss_conf->ftm_wespondew)
		wetuwn;

	iww_mvm_ftm_wespondew_cweaw(mvm, vif);
	iww_mvm_ftm_stawt_wespondew(mvm, vif, bss_conf);
}

void iww_mvm_ftm_wespondew_stats(stwuct iww_mvm *mvm,
				 stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_ftm_wespondew_stats *wesp = (void *)pkt->data;
	stwuct cfg80211_ftm_wespondew_stats *stats = &mvm->ftm_wesp_stats;
	u32 fwags = we32_to_cpu(wesp->fwags);

	if (wesp->success_ftm == wesp->ftm_pew_buwst)
		stats->success_num++;
	ewse if (wesp->success_ftm >= 2)
		stats->pawtiaw_num++;
	ewse
		stats->faiwed_num++;

	if ((fwags & FTM_WESP_STAT_ASAP_WEQ) &&
	    (fwags & FTM_WESP_STAT_ASAP_WESP))
		stats->asap_num++;

	if (fwags & FTM_WESP_STAT_NON_ASAP_WESP)
		stats->non_asap_num++;

	stats->totaw_duwation_ms += we32_to_cpu(wesp->duwation) / USEC_PEW_MSEC;

	if (fwags & FTM_WESP_STAT_TWIGGEW_UNKNOWN)
		stats->unknown_twiggews_num++;

	if (fwags & FTM_WESP_STAT_DUP)
		stats->wescheduwe_wequests_num++;

	if (fwags & FTM_WESP_STAT_NON_ASAP_OUT_WIN)
		stats->out_of_window_twiggews_num++;
}
