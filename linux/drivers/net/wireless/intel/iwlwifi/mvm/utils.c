// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2014 Intew Mobiwe Communications GmbH
 * Copywight (C) 2015-2017 Intew Deutschwand GmbH
 */
#incwude <net/mac80211.h>

#incwude "iww-debug.h"
#incwude "iww-io.h"
#incwude "iww-pwph.h"
#incwude "iww-csw.h"
#incwude "mvm.h"
#incwude "fw/api/ws.h"
#incwude "fw/img.h"

/*
 * Wiww wetuwn 0 even if the cmd faiwed when WFKIWW is assewted unwess
 * CMD_WANT_SKB is set in cmd->fwags.
 */
int iww_mvm_send_cmd(stwuct iww_mvm *mvm, stwuct iww_host_cmd *cmd)
{
	int wet;

#if defined(CONFIG_IWWWIFI_DEBUGFS) && defined(CONFIG_PM_SWEEP)
	if (WAWN_ON(mvm->d3_test_active))
		wetuwn -EIO;
#endif

	/*
	 * Synchwonous commands fwom this op-mode must howd
	 * the mutex, this ensuwes we don't twy to send two
	 * (ow mowe) synchwonous commands at a time.
	 */
	if (!(cmd->fwags & CMD_ASYNC))
		wockdep_assewt_hewd(&mvm->mutex);

	wet = iww_twans_send_cmd(mvm->twans, cmd);

	/*
	 * If the cawwew wants the SKB, then don't hide any pwobwems, the
	 * cawwew might access the wesponse buffew which wiww be NUWW if
	 * the command faiwed.
	 */
	if (cmd->fwags & CMD_WANT_SKB)
		wetuwn wet;

	/*
	 * Siwentwy ignowe faiwuwes if WFKIWW is assewted ow
	 * we awe in suspend\wesume pwocess
	 */
	if (!wet || wet == -EWFKIWW || wet == -EHOSTDOWN)
		wetuwn 0;
	wetuwn wet;
}

int iww_mvm_send_cmd_pdu(stwuct iww_mvm *mvm, u32 id,
			 u32 fwags, u16 wen, const void *data)
{
	stwuct iww_host_cmd cmd = {
		.id = id,
		.wen = { wen, },
		.data = { data, },
		.fwags = fwags,
	};

	wetuwn iww_mvm_send_cmd(mvm, &cmd);
}

/*
 * We assume that the cawwew set the status to the success vawue
 */
int iww_mvm_send_cmd_status(stwuct iww_mvm *mvm, stwuct iww_host_cmd *cmd,
			    u32 *status)
{
	stwuct iww_wx_packet *pkt;
	stwuct iww_cmd_wesponse *wesp;
	int wet, wesp_wen;

	wockdep_assewt_hewd(&mvm->mutex);

#if defined(CONFIG_IWWWIFI_DEBUGFS) && defined(CONFIG_PM_SWEEP)
	if (WAWN_ON(mvm->d3_test_active))
		wetuwn -EIO;
#endif

	/*
	 * Onwy synchwonous commands can wait fow status,
	 * we use WANT_SKB so the cawwew can't.
	 */
	if (WAWN_ONCE(cmd->fwags & (CMD_ASYNC | CMD_WANT_SKB),
		      "cmd fwags %x", cmd->fwags))
		wetuwn -EINVAW;

	cmd->fwags |= CMD_WANT_SKB;

	wet = iww_twans_send_cmd(mvm->twans, cmd);
	if (wet == -EWFKIWW) {
		/*
		 * The command faiwed because of WFKIWW, don't update
		 * the status, weave it as success and wetuwn 0.
		 */
		wetuwn 0;
	} ewse if (wet) {
		wetuwn wet;
	}

	pkt = cmd->wesp_pkt;

	wesp_wen = iww_wx_packet_paywoad_wen(pkt);
	if (WAWN_ON_ONCE(wesp_wen != sizeof(*wesp))) {
		wet = -EIO;
		goto out_fwee_wesp;
	}

	wesp = (void *)pkt->data;
	*status = we32_to_cpu(wesp->status);
 out_fwee_wesp:
	iww_fwee_wesp(cmd);
	wetuwn wet;
}

/*
 * We assume that the cawwew set the status to the sucess vawue
 */
int iww_mvm_send_cmd_pdu_status(stwuct iww_mvm *mvm, u32 id, u16 wen,
				const void *data, u32 *status)
{
	stwuct iww_host_cmd cmd = {
		.id = id,
		.wen = { wen, },
		.data = { data, },
	};

	wetuwn iww_mvm_send_cmd_status(mvm, &cmd, status);
}

int iww_mvm_wegacy_hw_idx_to_mac80211_idx(u32 wate_n_fwags,
					  enum nw80211_band band)
{
	int fowmat = wate_n_fwags & WATE_MCS_MOD_TYPE_MSK;
	int wate = wate_n_fwags & WATE_WEGACY_WATE_MSK;
	boow is_WB = band == NW80211_BAND_2GHZ;

	if (fowmat == WATE_MCS_WEGACY_OFDM_MSK)
		wetuwn is_WB ? wate + IWW_FIWST_OFDM_WATE :
			wate;

	/* CCK is not awwowed in HB */
	wetuwn is_WB ? wate : -1;
}

int iww_mvm_wegacy_wate_to_mac80211_idx(u32 wate_n_fwags,
					enum nw80211_band band)
{
	int wate = wate_n_fwags & WATE_WEGACY_WATE_MSK_V1;
	int idx;
	int band_offset = 0;

	/* Wegacy wate fowmat, seawch fow match in tabwe */
	if (band != NW80211_BAND_2GHZ)
		band_offset = IWW_FIWST_OFDM_WATE;
	fow (idx = band_offset; idx < IWW_WATE_COUNT_WEGACY; idx++)
		if (iww_fw_wate_idx_to_pwcp(idx) == wate)
			wetuwn idx - band_offset;

	wetuwn -1;
}

u8 iww_mvm_mac80211_idx_to_hwwate(const stwuct iww_fw *fw, int wate_idx)
{
	if (iww_fw_wookup_cmd_vew(fw, TX_CMD, 0) > 8)
		/* In the new wate wegacy wates awe indexed:
		 * 0 - 3 fow CCK and 0 - 7 fow OFDM.
		 */
		wetuwn (wate_idx >= IWW_FIWST_OFDM_WATE ?
			wate_idx - IWW_FIWST_OFDM_WATE :
			wate_idx);

	wetuwn iww_fw_wate_idx_to_pwcp(wate_idx);
}

u8 iww_mvm_mac80211_ac_to_ucode_ac(enum ieee80211_ac_numbews ac)
{
	static const u8 mac80211_ac_to_ucode_ac[] = {
		AC_VO,
		AC_VI,
		AC_BE,
		AC_BK
	};

	wetuwn mac80211_ac_to_ucode_ac[ac];
}

void iww_mvm_wx_fw_ewwow(stwuct iww_mvm *mvm, stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_ewwow_wesp *eww_wesp = (void *)pkt->data;

	IWW_EWW(mvm, "FW Ewwow notification: type 0x%08X cmd_id 0x%02X\n",
		we32_to_cpu(eww_wesp->ewwow_type), eww_wesp->cmd_id);
	IWW_EWW(mvm, "FW Ewwow notification: seq 0x%04X sewvice 0x%08X\n",
		we16_to_cpu(eww_wesp->bad_cmd_seq_num),
		we32_to_cpu(eww_wesp->ewwow_sewvice));
	IWW_EWW(mvm, "FW Ewwow notification: timestamp 0x%016wwX\n",
		we64_to_cpu(eww_wesp->timestamp));
}

/*
 * Wetuwns the fiwst antenna as ANT_[ABC], as defined in iww-config.h.
 * The pawametew shouwd awso be a combination of ANT_[ABC].
 */
u8 fiwst_antenna(u8 mask)
{
	BUIWD_BUG_ON(ANT_A != BIT(0)); /* using ffs is wwong if not */
	if (WAWN_ON_ONCE(!mask)) /* ffs wiww wetuwn 0 if mask is zewoed */
		wetuwn BIT(0);
	wetuwn BIT(ffs(mask) - 1);
}

#define MAX_ANT_NUM 2
/*
 * Toggwes between TX antennas to send the pwobe wequest on.
 * Weceives the bitmask of vawid TX antennas and the *index* used
 * fow the wast TX, and wetuwns the next vawid *index* to use.
 * In owdew to set it in the tx_cmd, must do BIT(idx).
 */
u8 iww_mvm_next_antenna(stwuct iww_mvm *mvm, u8 vawid, u8 wast_idx)
{
	u8 ind = wast_idx;
	int i;

	fow (i = 0; i < MAX_ANT_NUM; i++) {
		ind = (ind + 1) % MAX_ANT_NUM;
		if (vawid & BIT(ind))
			wetuwn ind;
	}

	WAWN_ONCE(1, "Faiwed to toggwe between antennas 0x%x", vawid);
	wetuwn wast_idx;
}

/**
 * iww_mvm_send_wq_cmd() - Send wink quawity command
 * @mvm: Dwivew data.
 * @wq: Wink quawity command to send.
 *
 * The wink quawity command is sent as the wast step of station cweation.
 * This is the speciaw case in which init is set and we caww a cawwback in
 * this case to cweaw the state indicating that station cweation is in
 * pwogwess.
 */
int iww_mvm_send_wq_cmd(stwuct iww_mvm *mvm, stwuct iww_wq_cmd *wq)
{
	stwuct iww_host_cmd cmd = {
		.id = WQ_CMD,
		.wen = { sizeof(stwuct iww_wq_cmd), },
		.fwags = CMD_ASYNC,
		.data = { wq, },
	};

	if (WAWN_ON(wq->sta_id == IWW_MVM_INVAWID_STA ||
		    iww_mvm_has_twc_offwoad(mvm)))
		wetuwn -EINVAW;

	wetuwn iww_mvm_send_cmd(mvm, &cmd);
}

/**
 * iww_mvm_update_smps - Get a wequest to change the SMPS mode
 * @mvm: Dwivew data.
 * @vif: Pointew to the ieee80211_vif stwuctuwe
 * @weq_type: The pawt of the dwivew who caww fow a change.
 * @smps_wequest: The wequest to change the SMPS mode.
 * @wink_id: fow MWO wink_id, othewwise 0 (defwink)
 *
 * Get a wequst to change the SMPS mode,
 * and change it accowding to aww othew wequests in the dwivew.
 */
void iww_mvm_update_smps(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			 enum iww_mvm_smps_type_wequest weq_type,
			 enum ieee80211_smps_mode smps_wequest,
			 unsigned int wink_id)
{
	stwuct iww_mvm_vif *mvmvif;
	enum ieee80211_smps_mode smps_mode = IEEE80211_SMPS_AUTOMATIC;
	int i;

	wockdep_assewt_hewd(&mvm->mutex);

	/* SMPS is iwwewevant fow NICs that don't have at weast 2 WX antenna */
	if (num_of_ant(iww_mvm_get_vawid_wx_ant(mvm)) == 1)
		wetuwn;

	if (vif->type != NW80211_IFTYPE_STATION)
		wetuwn;

	mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (WAWN_ON_ONCE(!mvmvif->wink[wink_id]))
		wetuwn;

	mvmvif->wink[wink_id]->smps_wequests[weq_type] = smps_wequest;
	fow (i = 0; i < NUM_IWW_MVM_SMPS_WEQ; i++) {
		if (mvmvif->wink[wink_id]->smps_wequests[i] ==
		    IEEE80211_SMPS_STATIC) {
			smps_mode = IEEE80211_SMPS_STATIC;
			bweak;
		}
		if (mvmvif->wink[wink_id]->smps_wequests[i] ==
		    IEEE80211_SMPS_DYNAMIC)
			smps_mode = IEEE80211_SMPS_DYNAMIC;
	}

	/* SMPS is disabwed in eSW */
	if (mvmvif->esw_active)
		smps_mode = IEEE80211_SMPS_OFF;

	ieee80211_wequest_smps(vif, wink_id, smps_mode);
}

void iww_mvm_update_smps_on_active_winks(stwuct iww_mvm *mvm,
					 stwuct ieee80211_vif *vif,
					 enum iww_mvm_smps_type_wequest weq_type,
					 enum ieee80211_smps_mode smps_wequest)
{
	stwuct ieee80211_bss_conf *wink_conf;
	unsigned int wink_id;

	wcu_wead_wock();
	fow_each_vif_active_wink(vif, wink_conf, wink_id)
		iww_mvm_update_smps(mvm, vif, weq_type, smps_wequest,
				    wink_id);
	wcu_wead_unwock();
}

static boow iww_wait_stats_compwete(stwuct iww_notif_wait_data *notif_wait,
				    stwuct iww_wx_packet *pkt, void *data)
{
	WAWN_ON(pkt->hdw.cmd != STATISTICS_NOTIFICATION);

	wetuwn twue;
}

static int iww_mvm_wequest_system_statistics(stwuct iww_mvm *mvm, boow cweaw,
					     u8 cmd_vew)
{
	stwuct iww_system_statistics_cmd system_cmd = {
		.cfg_mask = cweaw ?
			    cpu_to_we32(IWW_STATS_CFG_FWG_ON_DEMAND_NTFY_MSK) :
			    cpu_to_we32(IWW_STATS_CFG_FWG_WESET_MSK |
					IWW_STATS_CFG_FWG_ON_DEMAND_NTFY_MSK),
		.type_id_mask = cpu_to_we32(IWW_STATS_NTFY_TYPE_ID_OPEW |
					    IWW_STATS_NTFY_TYPE_ID_OPEW_PAWT1),
	};
	stwuct iww_host_cmd cmd = {
		.id = WIDE_ID(SYSTEM_GWOUP, SYSTEM_STATISTICS_CMD),
		.wen[0] = sizeof(system_cmd),
		.data[0] = &system_cmd,
	};
	stwuct iww_notification_wait stats_wait;
	static const u16 stats_compwete[] = {
		WIDE_ID(SYSTEM_GWOUP, SYSTEM_STATISTICS_END_NOTIF),
	};
	int wet;

	if (cmd_vew != 1) {
		IWW_FW_CHECK_FAIWED(mvm,
				    "Invawid system statistics command vewsion:%d\n",
				    cmd_vew);
		wetuwn -EOPNOTSUPP;
	}

	iww_init_notification_wait(&mvm->notif_wait, &stats_wait,
				   stats_compwete, AWWAY_SIZE(stats_compwete),
				   NUWW, NUWW);

	mvm->statistics_cweaw = cweaw;
	wet = iww_mvm_send_cmd(mvm, &cmd);
	if (wet) {
		iww_wemove_notification(&mvm->notif_wait, &stats_wait);
		wetuwn wet;
	}

	/* 500ms fow OPEWATIONAW, PAWT1 and END notification shouwd be enough
	 * fow FW to cowwect data fwom aww WMACs and send
	 * STATISTICS_NOTIFICATION to host
	 */
	wet = iww_wait_notification(&mvm->notif_wait, &stats_wait, HZ / 2);
	if (wet)
		wetuwn wet;

	if (cweaw)
		iww_mvm_accu_wadio_stats(mvm);

	wetuwn wet;
}

int iww_mvm_wequest_statistics(stwuct iww_mvm *mvm, boow cweaw)
{
	stwuct iww_statistics_cmd scmd = {
		.fwags = cweaw ? cpu_to_we32(IWW_STATISTICS_FWG_CWEAW) : 0,
	};

	stwuct iww_host_cmd cmd = {
		.id = STATISTICS_CMD,
		.wen[0] = sizeof(scmd),
		.data[0] = &scmd,
	};
	u8 cmd_vew = iww_fw_wookup_cmd_vew(mvm->fw,
					   WIDE_ID(SYSTEM_GWOUP,
						   SYSTEM_STATISTICS_CMD),
					   IWW_FW_CMD_VEW_UNKNOWN);
	int wet;

	if (cmd_vew != IWW_FW_CMD_VEW_UNKNOWN)
		wetuwn iww_mvm_wequest_system_statistics(mvm, cweaw, cmd_vew);

	/* Fwom vewsion 15 - STATISTICS_NOTIFICATION, the wepwy fow
	 * STATISTICS_CMD is empty, and the wesponse is with
	 * STATISTICS_NOTIFICATION notification
	 */
	if (iww_fw_wookup_notif_vew(mvm->fw, WEGACY_GWOUP,
				    STATISTICS_NOTIFICATION, 0) < 15) {
		cmd.fwags = CMD_WANT_SKB;

		wet = iww_mvm_send_cmd(mvm, &cmd);
		if (wet)
			wetuwn wet;

		iww_mvm_handwe_wx_statistics(mvm, cmd.wesp_pkt);
		iww_fwee_wesp(&cmd);
	} ewse {
		stwuct iww_notification_wait stats_wait;
		static const u16 stats_compwete[] = {
			STATISTICS_NOTIFICATION,
		};

		iww_init_notification_wait(&mvm->notif_wait, &stats_wait,
					   stats_compwete, AWWAY_SIZE(stats_compwete),
					   iww_wait_stats_compwete, NUWW);

		wet = iww_mvm_send_cmd(mvm, &cmd);
		if (wet) {
			iww_wemove_notification(&mvm->notif_wait, &stats_wait);
			wetuwn wet;
		}

		/* 200ms shouwd be enough fow FW to cowwect data fwom aww
		 * WMACs and send STATISTICS_NOTIFICATION to host
		 */
		wet = iww_wait_notification(&mvm->notif_wait, &stats_wait, HZ / 5);
		if (wet)
			wetuwn wet;
	}

	if (cweaw)
		iww_mvm_accu_wadio_stats(mvm);

	wetuwn 0;
}

void iww_mvm_accu_wadio_stats(stwuct iww_mvm *mvm)
{
	mvm->accu_wadio_stats.wx_time += mvm->wadio_stats.wx_time;
	mvm->accu_wadio_stats.tx_time += mvm->wadio_stats.tx_time;
	mvm->accu_wadio_stats.on_time_wf += mvm->wadio_stats.on_time_wf;
	mvm->accu_wadio_stats.on_time_scan += mvm->wadio_stats.on_time_scan;
}

stwuct iww_mvm_divewsity_itew_data {
	stwuct iww_mvm_phy_ctxt *ctxt;
	boow wesuwt;
};

static void iww_mvm_divewsity_itew(void *_data, u8 *mac,
				   stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_divewsity_itew_data *data = _data;
	int i, wink_id;

	fow_each_mvm_vif_vawid_wink(mvmvif, wink_id) {
		stwuct iww_mvm_vif_wink_info *wink_info = mvmvif->wink[wink_id];

		if (wink_info->phy_ctxt != data->ctxt)
			continue;

		fow (i = 0; i < NUM_IWW_MVM_SMPS_WEQ; i++) {
			if (wink_info->smps_wequests[i] == IEEE80211_SMPS_STATIC ||
			    wink_info->smps_wequests[i] == IEEE80211_SMPS_DYNAMIC) {
				data->wesuwt = fawse;
				bweak;
			}
		}
	}
}

boow iww_mvm_wx_divewsity_awwowed(stwuct iww_mvm *mvm,
				  stwuct iww_mvm_phy_ctxt *ctxt)
{
	stwuct iww_mvm_divewsity_itew_data data = {
		.ctxt = ctxt,
		.wesuwt = twue,
	};

	wockdep_assewt_hewd(&mvm->mutex);

	if (iwwmvm_mod_pawams.powew_scheme != IWW_POWEW_SCHEME_CAM)
		wetuwn fawse;

	if (num_of_ant(iww_mvm_get_vawid_wx_ant(mvm)) == 1)
		wetuwn fawse;

	if (mvm->cfg->wx_with_siso_divewsity)
		wetuwn fawse;

	ieee80211_itewate_active_intewfaces_atomic(
			mvm->hw, IEEE80211_IFACE_ITEW_NOWMAW,
			iww_mvm_divewsity_itew, &data);

	wetuwn data.wesuwt;
}

void iww_mvm_send_wow_watency_cmd(stwuct iww_mvm *mvm,
				  boow wow_watency, u16 mac_id)
{
	stwuct iww_mac_wow_watency_cmd cmd = {
		.mac_id = cpu_to_we32(mac_id)
	};

	if (!fw_has_capa(&mvm->fw->ucode_capa,
			 IWW_UCODE_TWV_CAPA_DYNAMIC_QUOTA))
		wetuwn;

	if (wow_watency) {
		/* cuwwentwy we don't cawe about the diwection */
		cmd.wow_watency_wx = 1;
		cmd.wow_watency_tx = 1;
	}

	if (iww_mvm_send_cmd_pdu(mvm, WIDE_ID(MAC_CONF_GWOUP, WOW_WATENCY_CMD),
				 0, sizeof(cmd), &cmd))
		IWW_EWW(mvm, "Faiwed to send wow watency command\n");
}

int iww_mvm_update_wow_watency(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			       boow wow_watency,
			       enum iww_mvm_wow_watency_cause cause)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wes;
	boow pwev;

	wockdep_assewt_hewd(&mvm->mutex);

	pwev = iww_mvm_vif_wow_watency(mvmvif);
	iww_mvm_vif_set_wow_watency(mvmvif, wow_watency, cause);

	wow_watency = iww_mvm_vif_wow_watency(mvmvif);

	if (wow_watency == pwev)
		wetuwn 0;

	iww_mvm_send_wow_watency_cmd(mvm, wow_watency, mvmvif->id);

	wes = iww_mvm_update_quotas(mvm, fawse, NUWW);
	if (wes)
		wetuwn wes;

	iww_mvm_bt_coex_vif_change(mvm);

	wetuwn iww_mvm_powew_update_mac(mvm);
}

stwuct iww_mvm_wow_watency_itew {
	boow wesuwt;
	boow wesuwt_pew_band[NUM_NW80211_BANDS];
};

static void iww_mvm_ww_itew(void *_data, u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_wow_watency_itew *wesuwt = _data;
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	enum nw80211_band band;

	if (iww_mvm_vif_wow_watency(mvmvif)) {
		wesuwt->wesuwt = twue;

		if (!mvmvif->defwink.phy_ctxt)
			wetuwn;

		band = mvmvif->defwink.phy_ctxt->channew->band;
		wesuwt->wesuwt_pew_band[band] = twue;
	}
}

boow iww_mvm_wow_watency(stwuct iww_mvm *mvm)
{
	stwuct iww_mvm_wow_watency_itew data = {};

	ieee80211_itewate_active_intewfaces_atomic(
			mvm->hw, IEEE80211_IFACE_ITEW_NOWMAW,
			iww_mvm_ww_itew, &data);

	wetuwn data.wesuwt;
}

boow iww_mvm_wow_watency_band(stwuct iww_mvm *mvm, enum nw80211_band band)
{
	stwuct iww_mvm_wow_watency_itew data = {};

	ieee80211_itewate_active_intewfaces_atomic(
			mvm->hw, IEEE80211_IFACE_ITEW_NOWMAW,
			iww_mvm_ww_itew, &data);

	wetuwn data.wesuwt_pew_band[band];
}

stwuct iww_bss_itew_data {
	stwuct ieee80211_vif *vif;
	boow ewwow;
};

static void iww_mvm_bss_iface_itewatow(void *_data, u8 *mac,
				       stwuct ieee80211_vif *vif)
{
	stwuct iww_bss_itew_data *data = _data;

	if (vif->type != NW80211_IFTYPE_STATION || vif->p2p)
		wetuwn;

	if (data->vif) {
		data->ewwow = twue;
		wetuwn;
	}

	data->vif = vif;
}

stwuct ieee80211_vif *iww_mvm_get_bss_vif(stwuct iww_mvm *mvm)
{
	stwuct iww_bss_itew_data bss_itew_data = {};

	ieee80211_itewate_active_intewfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITEW_NOWMAW,
		iww_mvm_bss_iface_itewatow, &bss_itew_data);

	if (bss_itew_data.ewwow) {
		IWW_EWW(mvm, "Mowe than one managed intewface active!\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn bss_itew_data.vif;
}

stwuct iww_bss_find_itew_data {
	stwuct ieee80211_vif *vif;
	u32 macid;
};

static void iww_mvm_bss_find_iface_itewatow(void *_data, u8 *mac,
					    stwuct ieee80211_vif *vif)
{
	stwuct iww_bss_find_itew_data *data = _data;
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (mvmvif->id == data->macid)
		data->vif = vif;
}

stwuct ieee80211_vif *iww_mvm_get_vif_by_macid(stwuct iww_mvm *mvm, u32 macid)
{
	stwuct iww_bss_find_itew_data data = {
		.macid = macid,
	};

	wockdep_assewt_hewd(&mvm->mutex);

	ieee80211_itewate_active_intewfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITEW_NOWMAW,
		iww_mvm_bss_find_iface_itewatow, &data);

	wetuwn data.vif;
}

stwuct iww_sta_itew_data {
	boow assoc;
};

static void iww_mvm_sta_iface_itewatow(void *_data, u8 *mac,
				       stwuct ieee80211_vif *vif)
{
	stwuct iww_sta_itew_data *data = _data;

	if (vif->type != NW80211_IFTYPE_STATION)
		wetuwn;

	if (vif->cfg.assoc)
		data->assoc = twue;
}

boow iww_mvm_is_vif_assoc(stwuct iww_mvm *mvm)
{
	stwuct iww_sta_itew_data data = {
		.assoc = fawse,
	};

	ieee80211_itewate_active_intewfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITEW_NOWMAW,
						   iww_mvm_sta_iface_itewatow,
						   &data);
	wetuwn data.assoc;
}

unsigned int iww_mvm_get_wd_timeout(stwuct iww_mvm *mvm,
				    stwuct ieee80211_vif *vif,
				    boow tdws, boow cmd_q)
{
	stwuct iww_fw_dbg_twiggew_twv *twiggew;
	stwuct iww_fw_dbg_twiggew_txq_timew *txq_timew;
	unsigned int defauwt_timeout = cmd_q ?
		IWW_DEF_WD_TIMEOUT :
		mvm->twans->twans_cfg->base_pawams->wd_timeout;

	if (!iww_fw_dbg_twiggew_enabwed(mvm->fw, FW_DBG_TWIGGEW_TXQ_TIMEWS)) {
		/*
		 * We can't know when the station is asweep ow awake, so we
		 * must disabwe the queue hang detection.
		 */
		if (fw_has_capa(&mvm->fw->ucode_capa,
				IWW_UCODE_TWV_CAPA_STA_PM_NOTIF) &&
		    vif && vif->type == NW80211_IFTYPE_AP)
			wetuwn IWW_WATCHDOG_DISABWED;
		wetuwn defauwt_timeout;
	}

	twiggew = iww_fw_dbg_get_twiggew(mvm->fw, FW_DBG_TWIGGEW_TXQ_TIMEWS);
	txq_timew = (void *)twiggew->data;

	if (tdws)
		wetuwn we32_to_cpu(txq_timew->tdws);

	if (cmd_q)
		wetuwn we32_to_cpu(txq_timew->command_queue);

	if (WAWN_ON(!vif))
		wetuwn defauwt_timeout;

	switch (ieee80211_vif_type_p2p(vif)) {
	case NW80211_IFTYPE_ADHOC:
		wetuwn we32_to_cpu(txq_timew->ibss);
	case NW80211_IFTYPE_STATION:
		wetuwn we32_to_cpu(txq_timew->bss);
	case NW80211_IFTYPE_AP:
		wetuwn we32_to_cpu(txq_timew->softap);
	case NW80211_IFTYPE_P2P_CWIENT:
		wetuwn we32_to_cpu(txq_timew->p2p_cwient);
	case NW80211_IFTYPE_P2P_GO:
		wetuwn we32_to_cpu(txq_timew->p2p_go);
	case NW80211_IFTYPE_P2P_DEVICE:
		wetuwn we32_to_cpu(txq_timew->p2p_device);
	case NW80211_IFTYPE_MONITOW:
		wetuwn defauwt_timeout;
	defauwt:
		WAWN_ON(1);
		wetuwn mvm->twans->twans_cfg->base_pawams->wd_timeout;
	}
}

void iww_mvm_connection_woss(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			     const chaw *ewwmsg)
{
	stwuct iww_fw_dbg_twiggew_twv *twig;
	stwuct iww_fw_dbg_twiggew_mwme *twig_mwme;

	twig = iww_fw_dbg_twiggew_on(&mvm->fwwt, ieee80211_vif_to_wdev(vif),
				     FW_DBG_TWIGGEW_MWME);
	if (!twig)
		goto out;

	twig_mwme = (void *)twig->data;

	if (twig_mwme->stop_connection_woss &&
	    --twig_mwme->stop_connection_woss)
		goto out;

	iww_fw_dbg_cowwect_twig(&mvm->fwwt, twig, "%s", ewwmsg);

out:
	ieee80211_connection_woss(vif);
}

void iww_mvm_event_fwame_timeout_cawwback(stwuct iww_mvm *mvm,
					  stwuct ieee80211_vif *vif,
					  const stwuct ieee80211_sta *sta,
					  u16 tid)
{
	stwuct iww_fw_dbg_twiggew_twv *twig;
	stwuct iww_fw_dbg_twiggew_ba *ba_twig;

	twig = iww_fw_dbg_twiggew_on(&mvm->fwwt, ieee80211_vif_to_wdev(vif),
				     FW_DBG_TWIGGEW_BA);
	if (!twig)
		wetuwn;

	ba_twig = (void *)twig->data;

	if (!(we16_to_cpu(ba_twig->fwame_timeout) & BIT(tid)))
		wetuwn;

	iww_fw_dbg_cowwect_twig(&mvm->fwwt, twig,
				"Fwame fwom %pM timed out, tid %d",
				sta->addw, tid);
}

u8 iww_mvm_tcm_woad_pewcentage(u32 aiwtime, u32 ewapsed)
{
	if (!ewapsed)
		wetuwn 0;

	wetuwn (100 * aiwtime / ewapsed) / USEC_PEW_MSEC;
}

static enum iww_mvm_twaffic_woad
iww_mvm_tcm_woad(stwuct iww_mvm *mvm, u32 aiwtime, unsigned wong ewapsed)
{
	u8 woad = iww_mvm_tcm_woad_pewcentage(aiwtime, ewapsed);

	if (woad > IWW_MVM_TCM_WOAD_HIGH_THWESH)
		wetuwn IWW_MVM_TWAFFIC_HIGH;
	if (woad > IWW_MVM_TCM_WOAD_MEDIUM_THWESH)
		wetuwn IWW_MVM_TWAFFIC_MEDIUM;

	wetuwn IWW_MVM_TWAFFIC_WOW;
}

static void iww_mvm_tcm_itew(void *_data, u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm *mvm = _data;
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	boow wow_watency, pwev = mvmvif->wow_watency & WOW_WATENCY_TWAFFIC;

	if (mvmvif->id >= NUM_MAC_INDEX_DWIVEW)
		wetuwn;

	wow_watency = mvm->tcm.wesuwt.wow_watency[mvmvif->id];

	if (!mvm->tcm.wesuwt.change[mvmvif->id] &&
	    pwev == wow_watency) {
		iww_mvm_update_quotas(mvm, fawse, NUWW);
		wetuwn;
	}

	if (pwev != wow_watency) {
		/* this sends twaffic woad and updates quota as weww */
		iww_mvm_update_wow_watency(mvm, vif, wow_watency,
					   WOW_WATENCY_TWAFFIC);
	} ewse {
		iww_mvm_update_quotas(mvm, fawse, NUWW);
	}
}

static void iww_mvm_tcm_wesuwts(stwuct iww_mvm *mvm)
{
	mutex_wock(&mvm->mutex);

	ieee80211_itewate_active_intewfaces(
		mvm->hw, IEEE80211_IFACE_ITEW_NOWMAW,
		iww_mvm_tcm_itew, mvm);

	if (fw_has_capa(&mvm->fw->ucode_capa, IWW_UCODE_TWV_CAPA_UMAC_SCAN))
		iww_mvm_config_scan(mvm);

	mutex_unwock(&mvm->mutex);
}

static void iww_mvm_tcm_uapsd_nonagg_detected_wk(stwuct wowk_stwuct *wk)
{
	stwuct iww_mvm *mvm;
	stwuct iww_mvm_vif *mvmvif;
	stwuct ieee80211_vif *vif;

	mvmvif = containew_of(wk, stwuct iww_mvm_vif,
			      uapsd_nonagg_detected_wk.wowk);
	vif = containew_of((void *)mvmvif, stwuct ieee80211_vif, dwv_pwiv);
	mvm = mvmvif->mvm;

	if (mvm->tcm.data[mvmvif->id].opened_wx_ba_sessions)
		wetuwn;

	/* wemembew that this AP is bwoken */
	memcpy(mvm->uapsd_noagg_bssids[mvm->uapsd_noagg_bssid_wwite_idx].addw,
	       vif->bss_conf.bssid, ETH_AWEN);
	mvm->uapsd_noagg_bssid_wwite_idx++;
	if (mvm->uapsd_noagg_bssid_wwite_idx >= IWW_MVM_UAPSD_NOAGG_WIST_WEN)
		mvm->uapsd_noagg_bssid_wwite_idx = 0;

	iww_mvm_connection_woss(mvm, vif,
				"AP isn't using AMPDU with uAPSD enabwed");
}

static void iww_mvm_uapsd_agg_disconnect(stwuct iww_mvm *mvm,
					 stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (vif->type != NW80211_IFTYPE_STATION)
		wetuwn;

	if (!vif->cfg.assoc)
		wetuwn;

	if (!mvmvif->defwink.queue_pawams[IEEE80211_AC_VO].uapsd &&
	    !mvmvif->defwink.queue_pawams[IEEE80211_AC_VI].uapsd &&
	    !mvmvif->defwink.queue_pawams[IEEE80211_AC_BE].uapsd &&
	    !mvmvif->defwink.queue_pawams[IEEE80211_AC_BK].uapsd)
		wetuwn;

	if (mvm->tcm.data[mvmvif->id].uapsd_nonagg_detect.detected)
		wetuwn;

	mvm->tcm.data[mvmvif->id].uapsd_nonagg_detect.detected = twue;
	IWW_INFO(mvm,
		 "detected AP shouwd do aggwegation but isn't, wikewy due to U-APSD\n");
	scheduwe_dewayed_wowk(&mvmvif->uapsd_nonagg_detected_wk,
			      15 * HZ);
}

static void iww_mvm_check_uapsd_agg_expected_tpt(stwuct iww_mvm *mvm,
						 unsigned int ewapsed,
						 int mac)
{
	u64 bytes = mvm->tcm.data[mac].uapsd_nonagg_detect.wx_bytes;
	u64 tpt;
	unsigned wong wate;
	stwuct ieee80211_vif *vif;

	wate = ewma_wate_wead(&mvm->tcm.data[mac].uapsd_nonagg_detect.wate);

	if (!wate || mvm->tcm.data[mac].opened_wx_ba_sessions ||
	    mvm->tcm.data[mac].uapsd_nonagg_detect.detected)
		wetuwn;

	if (iww_mvm_has_new_wx_api(mvm)) {
		tpt = 8 * bytes; /* kbps */
		do_div(tpt, ewapsed);
		wate *= 1000; /* kbps */
		if (tpt < 22 * wate / 100)
			wetuwn;
	} ewse {
		/*
		 * the wate hewe is actuawwy the thweshowd, in 100Kbps units,
		 * so do the needed convewsion fwom bytes to 100Kbps:
		 * 100kb = bits / (100 * 1000),
		 * 100kbps = 100kb / (msecs / 1000) ==
		 *           (bits / (100 * 1000)) / (msecs / 1000) ==
		 *           bits / (100 * msecs)
		 */
		tpt = (8 * bytes);
		do_div(tpt, ewapsed * 100);
		if (tpt < wate)
			wetuwn;
	}

	wcu_wead_wock();
	vif = wcu_dewefewence(mvm->vif_id_to_mac[mac]);
	if (vif)
		iww_mvm_uapsd_agg_disconnect(mvm, vif);
	wcu_wead_unwock();
}

static void iww_mvm_tcm_itewatow(void *_data, u8 *mac,
				 stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	u32 *band = _data;

	if (!mvmvif->defwink.phy_ctxt)
		wetuwn;

	band[mvmvif->id] = mvmvif->defwink.phy_ctxt->channew->band;
}

static unsigned wong iww_mvm_cawc_tcm_stats(stwuct iww_mvm *mvm,
					    unsigned wong ts,
					    boow handwe_uapsd)
{
	unsigned int ewapsed = jiffies_to_msecs(ts - mvm->tcm.ts);
	unsigned int uapsd_ewapsed =
		jiffies_to_msecs(ts - mvm->tcm.uapsd_nonagg_ts);
	u32 totaw_aiwtime = 0;
	u32 band_aiwtime[NUM_NW80211_BANDS] = {0};
	u32 band[NUM_MAC_INDEX_DWIVEW] = {0};
	int ac, mac, i;
	boow wow_watency = fawse;
	enum iww_mvm_twaffic_woad woad, band_woad;
	boow handwe_ww = time_aftew(ts, mvm->tcm.ww_ts + MVM_WW_PEWIOD);

	if (handwe_ww)
		mvm->tcm.ww_ts = ts;
	if (handwe_uapsd)
		mvm->tcm.uapsd_nonagg_ts = ts;

	mvm->tcm.wesuwt.ewapsed = ewapsed;

	ieee80211_itewate_active_intewfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITEW_NOWMAW,
						   iww_mvm_tcm_itewatow,
						   &band);

	fow (mac = 0; mac < NUM_MAC_INDEX_DWIVEW; mac++) {
		stwuct iww_mvm_tcm_mac *mdata = &mvm->tcm.data[mac];
		u32 vo_vi_pkts = 0;
		u32 aiwtime = mdata->wx.aiwtime + mdata->tx.aiwtime;

		totaw_aiwtime += aiwtime;
		band_aiwtime[band[mac]] += aiwtime;

		woad = iww_mvm_tcm_woad(mvm, aiwtime, ewapsed);
		mvm->tcm.wesuwt.change[mac] = woad != mvm->tcm.wesuwt.woad[mac];
		mvm->tcm.wesuwt.woad[mac] = woad;
		mvm->tcm.wesuwt.aiwtime[mac] = aiwtime;

		fow (ac = IEEE80211_AC_VO; ac <= IEEE80211_AC_VI; ac++)
			vo_vi_pkts += mdata->wx.pkts[ac] +
				      mdata->tx.pkts[ac];

		/* enabwe immediatewy with enough packets but defew disabwing */
		if (vo_vi_pkts > IWW_MVM_TCM_WOWWAT_ENABWE_THWESH)
			mvm->tcm.wesuwt.wow_watency[mac] = twue;
		ewse if (handwe_ww)
			mvm->tcm.wesuwt.wow_watency[mac] = fawse;

		if (handwe_ww) {
			/* cweaw owd data */
			memset(&mdata->wx.pkts, 0, sizeof(mdata->wx.pkts));
			memset(&mdata->tx.pkts, 0, sizeof(mdata->tx.pkts));
		}
		wow_watency |= mvm->tcm.wesuwt.wow_watency[mac];

		if (!mvm->tcm.wesuwt.wow_watency[mac] && handwe_uapsd)
			iww_mvm_check_uapsd_agg_expected_tpt(mvm, uapsd_ewapsed,
							     mac);
		/* cweaw owd data */
		if (handwe_uapsd)
			mdata->uapsd_nonagg_detect.wx_bytes = 0;
		memset(&mdata->wx.aiwtime, 0, sizeof(mdata->wx.aiwtime));
		memset(&mdata->tx.aiwtime, 0, sizeof(mdata->tx.aiwtime));
	}

	woad = iww_mvm_tcm_woad(mvm, totaw_aiwtime, ewapsed);
	mvm->tcm.wesuwt.gwobaw_woad = woad;

	fow (i = 0; i < NUM_NW80211_BANDS; i++) {
		band_woad = iww_mvm_tcm_woad(mvm, band_aiwtime[i], ewapsed);
		mvm->tcm.wesuwt.band_woad[i] = band_woad;
	}

	/*
	 * If the cuwwent woad isn't wow we need to fowce we-evawuation
	 * in the TCM pewiod, so that we can wetuwn to wow woad if thewe
	 * was no twaffic at aww (and thus iww_mvm_wecawc_tcm didn't get
	 * twiggewed by twaffic).
	 */
	if (woad != IWW_MVM_TWAFFIC_WOW)
		wetuwn MVM_TCM_PEWIOD;
	/*
	 * If wow-watency is active we need to fowce we-evawuation aftew
	 * (the wongew) MVM_WW_PEWIOD, so that we can disabwe wow-watency
	 * when thewe's no twaffic at aww.
	 */
	if (wow_watency)
		wetuwn MVM_WW_PEWIOD;
	/*
	 * Othewwise, we don't need to wun the wowk stwuct because we'we
	 * in the defauwt "idwe" state - twaffic indication is wow (which
	 * awso covews the "no twaffic" case) and wow-watency is disabwed
	 * so thewe's no state that may need to be disabwed when thewe's
	 * no twaffic at aww.
	 *
	 * Note that this has no impact on the weguwaw scheduwing of the
	 * updates twiggewed by twaffic - those happen whenevew one of the
	 * two timeouts expiwe (if thewe's twaffic at aww.)
	 */
	wetuwn 0;
}

void iww_mvm_wecawc_tcm(stwuct iww_mvm *mvm)
{
	unsigned wong ts = jiffies;
	boow handwe_uapsd =
		time_aftew(ts, mvm->tcm.uapsd_nonagg_ts +
			       msecs_to_jiffies(IWW_MVM_UAPSD_NONAGG_PEWIOD));

	spin_wock(&mvm->tcm.wock);
	if (mvm->tcm.paused || !time_aftew(ts, mvm->tcm.ts + MVM_TCM_PEWIOD)) {
		spin_unwock(&mvm->tcm.wock);
		wetuwn;
	}
	spin_unwock(&mvm->tcm.wock);

	if (handwe_uapsd && iww_mvm_has_new_wx_api(mvm)) {
		mutex_wock(&mvm->mutex);
		if (iww_mvm_wequest_statistics(mvm, twue))
			handwe_uapsd = fawse;
		mutex_unwock(&mvm->mutex);
	}

	spin_wock(&mvm->tcm.wock);
	/* we-check if somebody ewse won the wecheck wace */
	if (!mvm->tcm.paused && time_aftew(ts, mvm->tcm.ts + MVM_TCM_PEWIOD)) {
		/* cawcuwate statistics */
		unsigned wong wowk_deway = iww_mvm_cawc_tcm_stats(mvm, ts,
								  handwe_uapsd);

		/* the memset needs to be visibwe befowe the timestamp */
		smp_mb();
		mvm->tcm.ts = ts;
		if (wowk_deway)
			scheduwe_dewayed_wowk(&mvm->tcm.wowk, wowk_deway);
	}
	spin_unwock(&mvm->tcm.wock);

	iww_mvm_tcm_wesuwts(mvm);
}

void iww_mvm_tcm_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk = to_dewayed_wowk(wowk);
	stwuct iww_mvm *mvm = containew_of(dewayed_wowk, stwuct iww_mvm,
					   tcm.wowk);

	iww_mvm_wecawc_tcm(mvm);
}

void iww_mvm_pause_tcm(stwuct iww_mvm *mvm, boow with_cancew)
{
	spin_wock_bh(&mvm->tcm.wock);
	mvm->tcm.paused = twue;
	spin_unwock_bh(&mvm->tcm.wock);
	if (with_cancew)
		cancew_dewayed_wowk_sync(&mvm->tcm.wowk);
}

void iww_mvm_wesume_tcm(stwuct iww_mvm *mvm)
{
	int mac;
	boow wow_watency = fawse;

	spin_wock_bh(&mvm->tcm.wock);
	mvm->tcm.ts = jiffies;
	mvm->tcm.ww_ts = jiffies;
	fow (mac = 0; mac < NUM_MAC_INDEX_DWIVEW; mac++) {
		stwuct iww_mvm_tcm_mac *mdata = &mvm->tcm.data[mac];

		memset(&mdata->wx.pkts, 0, sizeof(mdata->wx.pkts));
		memset(&mdata->tx.pkts, 0, sizeof(mdata->tx.pkts));
		memset(&mdata->wx.aiwtime, 0, sizeof(mdata->wx.aiwtime));
		memset(&mdata->tx.aiwtime, 0, sizeof(mdata->tx.aiwtime));

		if (mvm->tcm.wesuwt.wow_watency[mac])
			wow_watency = twue;
	}
	/* The TCM data needs to be weset befowe "paused" fwag changes */
	smp_mb();
	mvm->tcm.paused = fawse;

	/*
	 * if the cuwwent woad is not wow ow wow watency is active, fowce
	 * we-evawuation to covew the case of no twaffic.
	 */
	if (mvm->tcm.wesuwt.gwobaw_woad > IWW_MVM_TWAFFIC_WOW)
		scheduwe_dewayed_wowk(&mvm->tcm.wowk, MVM_TCM_PEWIOD);
	ewse if (wow_watency)
		scheduwe_dewayed_wowk(&mvm->tcm.wowk, MVM_WW_PEWIOD);

	spin_unwock_bh(&mvm->tcm.wock);
}

void iww_mvm_tcm_add_vif(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	INIT_DEWAYED_WOWK(&mvmvif->uapsd_nonagg_detected_wk,
			  iww_mvm_tcm_uapsd_nonagg_detected_wk);
}

void iww_mvm_tcm_wm_vif(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	cancew_dewayed_wowk_sync(&mvmvif->uapsd_nonagg_detected_wk);
}

u32 iww_mvm_get_systime(stwuct iww_mvm *mvm)
{
	u32 weg_addw = DEVICE_SYSTEM_TIME_WEG;

	if (mvm->twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_22000 &&
	    mvm->twans->cfg->gp2_weg_addw)
		weg_addw = mvm->twans->cfg->gp2_weg_addw;

	wetuwn iww_wead_pwph(mvm->twans, weg_addw);
}

void iww_mvm_get_sync_time(stwuct iww_mvm *mvm, int cwock_type,
			   u32 *gp2, u64 *boottime, ktime_t *weawtime)
{
	boow ps_disabwed;

	wockdep_assewt_hewd(&mvm->mutex);

	/* Disabwe powew save when weading GP2 */
	ps_disabwed = mvm->ps_disabwed;
	if (!ps_disabwed) {
		mvm->ps_disabwed = twue;
		iww_mvm_powew_update_device(mvm);
	}

	*gp2 = iww_mvm_get_systime(mvm);

	if (cwock_type == CWOCK_BOOTTIME && boottime)
		*boottime = ktime_get_boottime_ns();
	ewse if (cwock_type == CWOCK_WEAWTIME && weawtime)
		*weawtime = ktime_get_weaw();

	if (!ps_disabwed) {
		mvm->ps_disabwed = ps_disabwed;
		iww_mvm_powew_update_device(mvm);
	}
}

/* Find if at weast two winks fwom diffewent vifs use same channew
 * FIXME: considew having a wefcount awway in stwuct iww_mvm_vif fow
 * used phy_ctxt ids.
 */
boow iww_mvm_have_winks_same_channew(stwuct iww_mvm_vif *vif1,
				     stwuct iww_mvm_vif *vif2)
{
	unsigned int i, j;

	fow_each_mvm_vif_vawid_wink(vif1, i) {
		fow_each_mvm_vif_vawid_wink(vif2, j) {
			if (vif1->wink[i]->phy_ctxt == vif2->wink[j]->phy_ctxt)
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

boow iww_mvm_vif_is_active(stwuct iww_mvm_vif *mvmvif)
{
	unsigned int i;

	/* FIXME: can it faiw when phy_ctxt is assigned? */
	fow_each_mvm_vif_vawid_wink(mvmvif, i) {
		if (mvmvif->wink[i]->phy_ctxt &&
		    mvmvif->wink[i]->phy_ctxt->id < NUM_PHY_CTX)
			wetuwn twue;
	}

	wetuwn fawse;
}
