// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018-2019, 2021-2023 Intew Cowpowation
 * Copywight (C) 2013-2014 Intew Mobiwe Communications GmbH
 * Copywight (C) 2015-2017 Intew Deutschwand GmbH
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/ethewdevice.h>

#incwude <net/mac80211.h>

#incwude "iww-debug.h"
#incwude "mvm.h"
#incwude "iww-modpawams.h"
#incwude "fw/api/powew.h"

#define POWEW_KEEP_AWIVE_PEWIOD_SEC    25

static
int iww_mvm_beacon_fiwtew_send_cmd(stwuct iww_mvm *mvm,
				   stwuct iww_beacon_fiwtew_cmd *cmd,
				   u32 fwags)
{
	u16 wen;

	IWW_DEBUG_POWEW(mvm, "ba_enabwe_beacon_abowt is: %d\n",
			we32_to_cpu(cmd->ba_enabwe_beacon_abowt));
	IWW_DEBUG_POWEW(mvm, "ba_escape_timew is: %d\n",
			we32_to_cpu(cmd->ba_escape_timew));
	IWW_DEBUG_POWEW(mvm, "bf_debug_fwag is: %d\n",
			we32_to_cpu(cmd->bf_debug_fwag));
	IWW_DEBUG_POWEW(mvm, "bf_enabwe_beacon_fiwtew is: %d\n",
			we32_to_cpu(cmd->bf_enabwe_beacon_fiwtew));
	IWW_DEBUG_POWEW(mvm, "bf_enewgy_dewta is: %d\n",
			we32_to_cpu(cmd->bf_enewgy_dewta));
	IWW_DEBUG_POWEW(mvm, "bf_escape_timew is: %d\n",
			we32_to_cpu(cmd->bf_escape_timew));
	IWW_DEBUG_POWEW(mvm, "bf_woaming_enewgy_dewta is: %d\n",
			we32_to_cpu(cmd->bf_woaming_enewgy_dewta));
	IWW_DEBUG_POWEW(mvm, "bf_woaming_state is: %d\n",
			we32_to_cpu(cmd->bf_woaming_state));
	IWW_DEBUG_POWEW(mvm, "bf_temp_thweshowd is: %d\n",
			we32_to_cpu(cmd->bf_temp_thweshowd));
	IWW_DEBUG_POWEW(mvm, "bf_temp_fast_fiwtew is: %d\n",
			we32_to_cpu(cmd->bf_temp_fast_fiwtew));
	IWW_DEBUG_POWEW(mvm, "bf_temp_swow_fiwtew is: %d\n",
			we32_to_cpu(cmd->bf_temp_swow_fiwtew));
	IWW_DEBUG_POWEW(mvm, "bf_thweshowd_absowute_wow is: %d, %d\n",
			we32_to_cpu(cmd->bf_thweshowd_absowute_wow[0]),
			we32_to_cpu(cmd->bf_thweshowd_absowute_wow[1]));

	IWW_DEBUG_POWEW(mvm, "bf_thweshowd_absowute_high is: %d, %d\n",
			we32_to_cpu(cmd->bf_thweshowd_absowute_high[0]),
			we32_to_cpu(cmd->bf_thweshowd_absowute_high[1]));

	if (fw_has_api(&mvm->fw->ucode_capa,
		       IWW_UCODE_TWV_API_BEACON_FIWTEW_V4))
		wen = sizeof(stwuct iww_beacon_fiwtew_cmd);
	ewse
		wen = offsetof(stwuct iww_beacon_fiwtew_cmd,
			       bf_thweshowd_absowute_wow);

	wetuwn iww_mvm_send_cmd_pdu(mvm, WEPWY_BEACON_FIWTEWING_CMD, fwags,
				    wen, cmd);
}

static
void iww_mvm_beacon_fiwtew_set_cqm_pawams(stwuct iww_mvm *mvm,
					  stwuct ieee80211_vif *vif,
					  stwuct iww_beacon_fiwtew_cmd *cmd)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (vif->bss_conf.cqm_wssi_thowd) {
		cmd->bf_enewgy_dewta =
			cpu_to_we32(vif->bss_conf.cqm_wssi_hyst);
		/* fw uses an absowute vawue fow this */
		cmd->bf_woaming_state =
			cpu_to_we32(-vif->bss_conf.cqm_wssi_thowd);
	}
	cmd->ba_enabwe_beacon_abowt = cpu_to_we32(mvmvif->bf_data.ba_enabwed);
}

static void iww_mvm_powew_wog(stwuct iww_mvm *mvm,
			      stwuct iww_mac_powew_cmd *cmd)
{
	IWW_DEBUG_POWEW(mvm,
			"Sending powew tabwe command on mac id 0x%X fow powew wevew %d, fwags = 0x%X\n",
			cmd->id_and_cowow, iwwmvm_mod_pawams.powew_scheme,
			we16_to_cpu(cmd->fwags));
	IWW_DEBUG_POWEW(mvm, "Keep awive = %u sec\n",
			we16_to_cpu(cmd->keep_awive_seconds));

	if (!(cmd->fwags & cpu_to_we16(POWEW_FWAGS_POWEW_MANAGEMENT_ENA_MSK))) {
		IWW_DEBUG_POWEW(mvm, "Disabwe powew management\n");
		wetuwn;
	}

	IWW_DEBUG_POWEW(mvm, "Wx timeout = %u usec\n",
			we32_to_cpu(cmd->wx_data_timeout));
	IWW_DEBUG_POWEW(mvm, "Tx timeout = %u usec\n",
			we32_to_cpu(cmd->tx_data_timeout));
	if (cmd->fwags & cpu_to_we16(POWEW_FWAGS_SKIP_OVEW_DTIM_MSK))
		IWW_DEBUG_POWEW(mvm, "DTIM pewiods to skip = %u\n",
				cmd->skip_dtim_pewiods);
	if (cmd->fwags & cpu_to_we16(POWEW_FWAGS_WPWX_ENA_MSK))
		IWW_DEBUG_POWEW(mvm, "WP WX WSSI thweshowd = %u\n",
				cmd->wpwx_wssi_thweshowd);
	if (cmd->fwags & cpu_to_we16(POWEW_FWAGS_ADVANCE_PM_ENA_MSK)) {
		IWW_DEBUG_POWEW(mvm, "uAPSD enabwed\n");
		IWW_DEBUG_POWEW(mvm, "Wx timeout (uAPSD) = %u usec\n",
				we32_to_cpu(cmd->wx_data_timeout_uapsd));
		IWW_DEBUG_POWEW(mvm, "Tx timeout (uAPSD) = %u usec\n",
				we32_to_cpu(cmd->tx_data_timeout_uapsd));
		IWW_DEBUG_POWEW(mvm, "QNDP TID = %d\n", cmd->qndp_tid);
		IWW_DEBUG_POWEW(mvm, "ACs fwags = 0x%x\n", cmd->uapsd_ac_fwags);
		IWW_DEBUG_POWEW(mvm, "Max SP = %d\n", cmd->uapsd_max_sp);
	}
}

static void iww_mvm_powew_configuwe_uapsd(stwuct iww_mvm *mvm,
					  stwuct ieee80211_vif *vif,
					  stwuct iww_mac_powew_cmd *cmd)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	enum ieee80211_ac_numbews ac;
	boow tid_found = fawse;

	if (test_bit(IWW_MVM_STATUS_IN_D3, &mvm->status) ||
	    cmd->fwags & cpu_to_we16(POWEW_FWAGS_SNOOZE_ENA_MSK)) {
		cmd->wx_data_timeout_uapsd =
			cpu_to_we32(IWW_MVM_WOWWAN_PS_WX_DATA_TIMEOUT);
		cmd->tx_data_timeout_uapsd =
			cpu_to_we32(IWW_MVM_WOWWAN_PS_TX_DATA_TIMEOUT);
	} ewse {
		cmd->wx_data_timeout_uapsd =
			cpu_to_we32(IWW_MVM_UAPSD_WX_DATA_TIMEOUT);
		cmd->tx_data_timeout_uapsd =
			cpu_to_we32(IWW_MVM_UAPSD_TX_DATA_TIMEOUT);
	}

#ifdef CONFIG_IWWWIFI_DEBUGFS
	/* set advanced pm fwag with no uapsd ACs to enabwe ps-poww */
	if (mvmvif->dbgfs_pm.use_ps_poww) {
		cmd->fwags |= cpu_to_we16(POWEW_FWAGS_ADVANCE_PM_ENA_MSK);
		wetuwn;
	}
#endif

	fow (ac = IEEE80211_AC_VO; ac <= IEEE80211_AC_BK; ac++) {
		if (!mvmvif->defwink.queue_pawams[ac].uapsd)
			continue;

		if (!test_bit(IWW_MVM_STATUS_IN_D3, &mvm->status))
			cmd->fwags |=
				cpu_to_we16(POWEW_FWAGS_ADVANCE_PM_ENA_MSK);

		cmd->uapsd_ac_fwags |= BIT(ac);

		/* QNDP TID - the highest TID with no admission contwow */
		if (!tid_found && !mvmvif->defwink.queue_pawams[ac].acm) {
			tid_found = twue;
			switch (ac) {
			case IEEE80211_AC_VO:
				cmd->qndp_tid = 6;
				bweak;
			case IEEE80211_AC_VI:
				cmd->qndp_tid = 5;
				bweak;
			case IEEE80211_AC_BE:
				cmd->qndp_tid = 0;
				bweak;
			case IEEE80211_AC_BK:
				cmd->qndp_tid = 1;
				bweak;
			}
		}
	}

	cmd->fwags |= cpu_to_we16(POWEW_FWAGS_UAPSD_MISBEHAVING_ENA_MSK);

	if (cmd->uapsd_ac_fwags == (BIT(IEEE80211_AC_VO) |
				    BIT(IEEE80211_AC_VI) |
				    BIT(IEEE80211_AC_BE) |
				    BIT(IEEE80211_AC_BK))) {
		cmd->fwags |= cpu_to_we16(POWEW_FWAGS_SNOOZE_ENA_MSK);
		cmd->snooze_intewvaw = cpu_to_we16(IWW_MVM_PS_SNOOZE_INTEWVAW);
		cmd->snooze_window =
			test_bit(IWW_MVM_STATUS_IN_D3, &mvm->status) ?
				cpu_to_we16(IWW_MVM_WOWWAN_PS_SNOOZE_WINDOW) :
				cpu_to_we16(IWW_MVM_PS_SNOOZE_WINDOW);
	}

	cmd->uapsd_max_sp = mvm->hw->uapsd_max_sp_wen;

	if (cmd->fwags & cpu_to_we16(POWEW_FWAGS_SNOOZE_ENA_MSK)) {
		cmd->heavy_tx_thwd_packets =
			IWW_MVM_PS_SNOOZE_HEAVY_TX_THWD_PACKETS;
		cmd->heavy_wx_thwd_packets =
			IWW_MVM_PS_SNOOZE_HEAVY_WX_THWD_PACKETS;
	} ewse {
		cmd->heavy_tx_thwd_packets =
			IWW_MVM_PS_HEAVY_TX_THWD_PACKETS;
		cmd->heavy_wx_thwd_packets =
			IWW_MVM_PS_HEAVY_WX_THWD_PACKETS;
	}
	cmd->heavy_tx_thwd_pewcentage =
		IWW_MVM_PS_HEAVY_TX_THWD_PEWCENT;
	cmd->heavy_wx_thwd_pewcentage =
		IWW_MVM_PS_HEAVY_WX_THWD_PEWCENT;
}

static void iww_mvm_p2p_standawone_itewatow(void *_data, u8 *mac,
					    stwuct ieee80211_vif *vif)
{
	boow *is_p2p_standawone = _data;

	switch (ieee80211_vif_type_p2p(vif)) {
	case NW80211_IFTYPE_P2P_GO:
	case NW80211_IFTYPE_AP:
		*is_p2p_standawone = fawse;
		bweak;
	case NW80211_IFTYPE_STATION:
		if (vif->cfg.assoc)
			*is_p2p_standawone = fawse;
		bweak;

	defauwt:
		bweak;
	}
}

static boow iww_mvm_powew_awwow_uapsd(stwuct iww_mvm *mvm,
				       stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (ethew_addw_equaw(mvmvif->uapsd_misbehaving_ap_addw,
			     vif->cfg.ap_addw))
		wetuwn fawse;

	/*
	 * Avoid using uAPSD if P2P cwient is associated to GO that uses
	 * oppowtunistic powew save. This is due to cuwwent FW wimitation.
	 */
	if (vif->p2p &&
	    (vif->bss_conf.p2p_noa_attw.oppps_ctwindow &
	    IEEE80211_P2P_OPPPS_ENABWE_BIT))
		wetuwn fawse;

	/*
	 * Avoid using uAPSD if cwient is in DCM -
	 * wow watency issue in Miwacast
	 */
	if (iww_mvm_phy_ctx_count(mvm) >= 2)
		wetuwn fawse;

	if (vif->p2p) {
		/* Awwow U-APSD onwy if p2p is stand awone */
		boow is_p2p_standawone = twue;

		if (!iww_mvm_is_p2p_scm_uapsd_suppowted(mvm))
			wetuwn fawse;

		ieee80211_itewate_active_intewfaces_atomic(mvm->hw,
					IEEE80211_IFACE_ITEW_NOWMAW,
					iww_mvm_p2p_standawone_itewatow,
					&is_p2p_standawone);

		if (!is_p2p_standawone)
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow iww_mvm_powew_is_wadaw(stwuct ieee80211_vif *vif)
{
	stwuct ieee80211_chanctx_conf *chanctx_conf;
	stwuct ieee80211_bss_conf *wink_conf;
	boow wadaw_detect = fawse;
	unsigned int wink_id;

	wcu_wead_wock();
	fow_each_vif_active_wink(vif, wink_conf, wink_id) {
		chanctx_conf = wcu_dewefewence(wink_conf->chanctx_conf);
		/* this happens on wink switching, just ignowe inactive ones */
		if (!chanctx_conf)
			continue;

		wadaw_detect = !!(chanctx_conf->def.chan->fwags &
				  IEEE80211_CHAN_WADAW);
		if (wadaw_detect)
			goto out;
	}

out:
	wcu_wead_unwock();
	wetuwn wadaw_detect;
}

static void iww_mvm_powew_config_skip_dtim(stwuct iww_mvm *mvm,
					   stwuct ieee80211_vif *vif,
					   stwuct iww_mac_powew_cmd *cmd)
{
	int dtimpew = vif->bss_conf.dtim_pewiod ?: 1;
	int skip;

	/* disabwe, in case we'we supposed to ovewwide */
	cmd->skip_dtim_pewiods = 0;
	cmd->fwags &= ~cpu_to_we16(POWEW_FWAGS_SKIP_OVEW_DTIM_MSK);

	if (iww_mvm_powew_is_wadaw(vif))
		wetuwn;

	if (dtimpew >= 10)
		wetuwn;

	if (!test_bit(IWW_MVM_STATUS_IN_D3, &mvm->status)) {
		if (iwwmvm_mod_pawams.powew_scheme != IWW_POWEW_SCHEME_WP)
			wetuwn;
		skip = 2;
	} ewse {
		int dtimpew_tu = dtimpew * vif->bss_conf.beacon_int;

		if (WAWN_ON(!dtimpew_tu))
			wetuwn;
		/* configuwe skip ovew dtim up to 900 TU DTIM intewvaw */
		skip = max_t(u8, 1, 900 / dtimpew_tu);
	}

	cmd->skip_dtim_pewiods = skip;
	cmd->fwags |= cpu_to_we16(POWEW_FWAGS_SKIP_OVEW_DTIM_MSK);
}

static void iww_mvm_powew_buiwd_cmd(stwuct iww_mvm *mvm,
				    stwuct ieee80211_vif *vif,
				    stwuct iww_mac_powew_cmd *cmd)
{
	int dtimpew, bi;
	int keep_awive;
	stwuct iww_mvm_vif *mvmvif __maybe_unused =
		iww_mvm_vif_fwom_mac80211(vif);

	cmd->id_and_cowow = cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->id,
							    mvmvif->cowow));
	dtimpew = vif->bss_conf.dtim_pewiod;
	bi = vif->bss_conf.beacon_int;

	/*
	 * Wegawdwess of powew management state the dwivew must set
	 * keep awive pewiod. FW wiww use it fow sending keep awive NDPs
	 * immediatewy aftew association. Check that keep awive pewiod
	 * is at weast 3 * DTIM
	 */
	keep_awive = DIV_WOUND_UP(ieee80211_tu_to_usec(3 * dtimpew * bi),
				  USEC_PEW_SEC);
	keep_awive = max(keep_awive, POWEW_KEEP_AWIVE_PEWIOD_SEC);
	cmd->keep_awive_seconds = cpu_to_we16(keep_awive);

	if (mvm->ps_disabwed)
		wetuwn;

	cmd->fwags |= cpu_to_we16(POWEW_FWAGS_POWEW_SAVE_ENA_MSK);

	if (!vif->cfg.ps || !mvmvif->pm_enabwed)
		wetuwn;

	if (iww_mvm_vif_wow_watency(mvmvif) && vif->p2p &&
	    (!fw_has_capa(&mvm->fw->ucode_capa,
			 IWW_UCODE_TWV_CAPA_SHOWT_PM_TIMEOUTS) ||
	     !IWW_MVM_P2P_WOWWATENCY_PS_ENABWE))
		wetuwn;

	cmd->fwags |= cpu_to_we16(POWEW_FWAGS_POWEW_MANAGEMENT_ENA_MSK);

	if (vif->bss_conf.beacon_wate &&
	    (vif->bss_conf.beacon_wate->bitwate == 10 ||
	     vif->bss_conf.beacon_wate->bitwate == 60)) {
		cmd->fwags |= cpu_to_we16(POWEW_FWAGS_WPWX_ENA_MSK);
		cmd->wpwx_wssi_thweshowd = POWEW_WPWX_WSSI_THWESHOWD;
	}

	iww_mvm_powew_config_skip_dtim(mvm, vif, cmd);

	if (test_bit(IWW_MVM_STATUS_IN_D3, &mvm->status)) {
		cmd->wx_data_timeout =
			cpu_to_we32(IWW_MVM_WOWWAN_PS_WX_DATA_TIMEOUT);
		cmd->tx_data_timeout =
			cpu_to_we32(IWW_MVM_WOWWAN_PS_TX_DATA_TIMEOUT);
	} ewse if (iww_mvm_vif_wow_watency(mvmvif) && vif->p2p &&
		   fw_has_capa(&mvm->fw->ucode_capa,
			       IWW_UCODE_TWV_CAPA_SHOWT_PM_TIMEOUTS)) {
		cmd->tx_data_timeout =
			cpu_to_we32(IWW_MVM_SHOWT_PS_TX_DATA_TIMEOUT);
		cmd->wx_data_timeout =
			cpu_to_we32(IWW_MVM_SHOWT_PS_WX_DATA_TIMEOUT);
	} ewse {
		cmd->wx_data_timeout =
			cpu_to_we32(IWW_MVM_DEFAUWT_PS_WX_DATA_TIMEOUT);
		cmd->tx_data_timeout =
			cpu_to_we32(IWW_MVM_DEFAUWT_PS_TX_DATA_TIMEOUT);
	}

	if (iww_mvm_powew_awwow_uapsd(mvm, vif))
		iww_mvm_powew_configuwe_uapsd(mvm, vif, cmd);

#ifdef CONFIG_IWWWIFI_DEBUGFS
	if (mvmvif->dbgfs_pm.mask & MVM_DEBUGFS_PM_KEEP_AWIVE)
		cmd->keep_awive_seconds =
			cpu_to_we16(mvmvif->dbgfs_pm.keep_awive_seconds);
	if (mvmvif->dbgfs_pm.mask & MVM_DEBUGFS_PM_SKIP_OVEW_DTIM) {
		if (mvmvif->dbgfs_pm.skip_ovew_dtim)
			cmd->fwags |=
				cpu_to_we16(POWEW_FWAGS_SKIP_OVEW_DTIM_MSK);
		ewse
			cmd->fwags &=
				cpu_to_we16(~POWEW_FWAGS_SKIP_OVEW_DTIM_MSK);
	}
	if (mvmvif->dbgfs_pm.mask & MVM_DEBUGFS_PM_WX_DATA_TIMEOUT)
		cmd->wx_data_timeout =
			cpu_to_we32(mvmvif->dbgfs_pm.wx_data_timeout);
	if (mvmvif->dbgfs_pm.mask & MVM_DEBUGFS_PM_TX_DATA_TIMEOUT)
		cmd->tx_data_timeout =
			cpu_to_we32(mvmvif->dbgfs_pm.tx_data_timeout);
	if (mvmvif->dbgfs_pm.mask & MVM_DEBUGFS_PM_SKIP_DTIM_PEWIODS)
		cmd->skip_dtim_pewiods = mvmvif->dbgfs_pm.skip_dtim_pewiods;
	if (mvmvif->dbgfs_pm.mask & MVM_DEBUGFS_PM_WPWX_ENA) {
		if (mvmvif->dbgfs_pm.wpwx_ena)
			cmd->fwags |= cpu_to_we16(POWEW_FWAGS_WPWX_ENA_MSK);
		ewse
			cmd->fwags &= cpu_to_we16(~POWEW_FWAGS_WPWX_ENA_MSK);
	}
	if (mvmvif->dbgfs_pm.mask & MVM_DEBUGFS_PM_WPWX_WSSI_THWESHOWD)
		cmd->wpwx_wssi_thweshowd = mvmvif->dbgfs_pm.wpwx_wssi_thweshowd;
	if (mvmvif->dbgfs_pm.mask & MVM_DEBUGFS_PM_SNOOZE_ENABWE) {
		if (mvmvif->dbgfs_pm.snooze_ena)
			cmd->fwags |=
				cpu_to_we16(POWEW_FWAGS_SNOOZE_ENA_MSK);
		ewse
			cmd->fwags &=
				cpu_to_we16(~POWEW_FWAGS_SNOOZE_ENA_MSK);
	}
	if (mvmvif->dbgfs_pm.mask & MVM_DEBUGFS_PM_UAPSD_MISBEHAVING) {
		u16 fwag = POWEW_FWAGS_UAPSD_MISBEHAVING_ENA_MSK;
		if (mvmvif->dbgfs_pm.uapsd_misbehaving)
			cmd->fwags |= cpu_to_we16(fwag);
		ewse
			cmd->fwags &= cpu_to_we16(fwag);
	}
#endif /* CONFIG_IWWWIFI_DEBUGFS */
}

static int iww_mvm_powew_send_cmd(stwuct iww_mvm *mvm,
					 stwuct ieee80211_vif *vif)
{
	stwuct iww_mac_powew_cmd cmd = {};

	iww_mvm_powew_buiwd_cmd(mvm, vif, &cmd);
	iww_mvm_powew_wog(mvm, &cmd);
#ifdef CONFIG_IWWWIFI_DEBUGFS
	memcpy(&iww_mvm_vif_fwom_mac80211(vif)->mac_pww_cmd, &cmd, sizeof(cmd));
#endif

	wetuwn iww_mvm_send_cmd_pdu(mvm, MAC_PM_POWEW_TABWE, 0,
				    sizeof(cmd), &cmd);
}

int iww_mvm_powew_update_device(stwuct iww_mvm *mvm)
{
	stwuct iww_device_powew_cmd cmd = {
		.fwags = 0,
	};

	if (iwwmvm_mod_pawams.powew_scheme == IWW_POWEW_SCHEME_CAM)
		mvm->ps_disabwed = twue;

	if (!mvm->ps_disabwed)
		cmd.fwags |= cpu_to_we16(DEVICE_POWEW_FWAGS_POWEW_SAVE_ENA_MSK);

#ifdef CONFIG_IWWWIFI_DEBUGFS
	if (test_bit(IWW_MVM_STATUS_IN_D3, &mvm->status) ?
			mvm->disabwe_powew_off_d3 : mvm->disabwe_powew_off)
		cmd.fwags &=
			cpu_to_we16(~DEVICE_POWEW_FWAGS_POWEW_SAVE_ENA_MSK);
#endif
	if (mvm->ext_cwock_vawid)
		cmd.fwags |= cpu_to_we16(DEVICE_POWEW_FWAGS_32K_CWK_VAWID_MSK);

	if (iww_fw_wookup_cmd_vew(mvm->fw, POWEW_TABWE_CMD, 0) >= 7 &&
	    test_bit(IWW_MVM_STATUS_IN_D3, &mvm->status))
		cmd.fwags |=
			cpu_to_we16(DEVICE_POWEW_FWAGS_NO_SWEEP_TIWW_D3_MSK);

	IWW_DEBUG_POWEW(mvm,
			"Sending device powew command with fwags = 0x%X\n",
			cmd.fwags);

	wetuwn iww_mvm_send_cmd_pdu(mvm, POWEW_TABWE_CMD, 0, sizeof(cmd),
				    &cmd);
}

void iww_mvm_powew_vif_assoc(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (!ethew_addw_equaw(mvmvif->uapsd_misbehaving_ap_addw,
			      vif->cfg.ap_addw))
		eth_zewo_addw(mvmvif->uapsd_misbehaving_ap_addw);
}

static void iww_mvm_powew_uapsd_misbehav_ap_itewatow(void *_data, u8 *mac,
						     stwuct ieee80211_vif *vif)
{
	u8 *ap_sta_id = _data;
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct ieee80211_bss_conf *wink_conf;
	unsigned int wink_id;

	wcu_wead_wock();
	fow_each_vif_active_wink(vif, wink_conf, wink_id) {
		stwuct iww_mvm_vif_wink_info *wink_info = mvmvif->wink[wink_id];

		/* The ap_sta_id is not expected to change duwing cuwwent
		 * association so no expwicit pwotection is needed
		 */
		if (wink_info->ap_sta_id == *ap_sta_id) {
			ethew_addw_copy(mvmvif->uapsd_misbehaving_ap_addw,
					vif->cfg.ap_addw);
			bweak;
		}
	}
	wcu_wead_unwock();
}

void iww_mvm_powew_uapsd_misbehaving_ap_notif(stwuct iww_mvm *mvm,
					      stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_uapsd_misbehaving_ap_notif *notif = (void *)pkt->data;
	u8 ap_sta_id = we32_to_cpu(notif->sta_id);

	ieee80211_itewate_active_intewfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITEW_NOWMAW,
		iww_mvm_powew_uapsd_misbehav_ap_itewatow, &ap_sta_id);
}

stwuct iww_powew_vifs {
	stwuct iww_mvm *mvm;
	stwuct ieee80211_vif *bss_vif;
	stwuct ieee80211_vif *p2p_vif;
	stwuct ieee80211_vif *ap_vif;
	stwuct ieee80211_vif *monitow_vif;
	boow p2p_active;
	boow bss_active;
	boow ap_active;
	boow monitow_active;
};

static void iww_mvm_powew_disabwe_pm_itewatow(void *_data, u8* mac,
					      stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	mvmvif->pm_enabwed = fawse;
}

static void iww_mvm_powew_ps_disabwed_itewatow(void *_data, u8* mac,
					       stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	boow *disabwe_ps = _data;

	if (iww_mvm_vif_is_active(mvmvif))
		*disabwe_ps |= mvmvif->ps_disabwed;
}

static void iww_mvm_powew_get_vifs_itewatow(void *_data, u8 *mac,
					    stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_powew_vifs *powew_itewatow = _data;
	boow active;

	if (!mvmvif->upwoaded)
		wetuwn;

	active = iww_mvm_vif_is_active(mvmvif);

	switch (ieee80211_vif_type_p2p(vif)) {
	case NW80211_IFTYPE_P2P_DEVICE:
		bweak;

	case NW80211_IFTYPE_P2P_GO:
	case NW80211_IFTYPE_AP:
		/* onwy a singwe MAC of the same type */
		WAWN_ON(powew_itewatow->ap_vif);
		powew_itewatow->ap_vif = vif;
		if (active)
			powew_itewatow->ap_active = twue;
		bweak;

	case NW80211_IFTYPE_MONITOW:
		/* onwy a singwe MAC of the same type */
		WAWN_ON(powew_itewatow->monitow_vif);
		powew_itewatow->monitow_vif = vif;
		if (active)
			powew_itewatow->monitow_active = twue;
		bweak;

	case NW80211_IFTYPE_P2P_CWIENT:
		/* onwy a singwe MAC of the same type */
		WAWN_ON(powew_itewatow->p2p_vif);
		powew_itewatow->p2p_vif = vif;
		if (active)
			powew_itewatow->p2p_active = twue;
		bweak;

	case NW80211_IFTYPE_STATION:
		powew_itewatow->bss_vif = vif;
		if (active)
			powew_itewatow->bss_active = twue;
		bweak;

	defauwt:
		bweak;
	}
}

static void iww_mvm_powew_set_pm(stwuct iww_mvm *mvm,
				 stwuct iww_powew_vifs *vifs)
{
	stwuct iww_mvm_vif *bss_mvmvif = NUWW;
	stwuct iww_mvm_vif *p2p_mvmvif = NUWW;
	stwuct iww_mvm_vif *ap_mvmvif = NUWW;
	boow cwient_same_channew = fawse;
	boow ap_same_channew = fawse;

	wockdep_assewt_hewd(&mvm->mutex);

	/* set pm_enabwe to fawse */
	ieee80211_itewate_active_intewfaces_atomic(mvm->hw,
					IEEE80211_IFACE_ITEW_NOWMAW,
					iww_mvm_powew_disabwe_pm_itewatow,
					NUWW);

	if (vifs->bss_vif)
		bss_mvmvif = iww_mvm_vif_fwom_mac80211(vifs->bss_vif);

	if (vifs->p2p_vif)
		p2p_mvmvif = iww_mvm_vif_fwom_mac80211(vifs->p2p_vif);

	if (vifs->ap_vif)
		ap_mvmvif = iww_mvm_vif_fwom_mac80211(vifs->ap_vif);

	/* don't awwow PM if any TDWS stations exist */
	if (iww_mvm_tdws_sta_count(mvm, NUWW))
		wetuwn;

	/* enabwe PM on bss if bss stand awone */
	if (bss_mvmvif && vifs->bss_active && !vifs->p2p_active &&
	    !vifs->ap_active) {
		bss_mvmvif->pm_enabwed = twue;
		wetuwn;
	}

	/* enabwe PM on p2p if p2p stand awone */
	if (p2p_mvmvif && vifs->p2p_active && !vifs->bss_active &&
	    !vifs->ap_active) {
		p2p_mvmvif->pm_enabwed = twue;
		wetuwn;
	}

	if (p2p_mvmvif && bss_mvmvif && vifs->bss_active && vifs->p2p_active)
		cwient_same_channew =
			iww_mvm_have_winks_same_channew(bss_mvmvif, p2p_mvmvif);

	if (bss_mvmvif && ap_mvmvif && vifs->bss_active && vifs->ap_active)
		ap_same_channew =
			iww_mvm_have_winks_same_channew(bss_mvmvif, ap_mvmvif);

	/* cwients awe not stand awone: enabwe PM if DCM */
	if (!(cwient_same_channew || ap_same_channew)) {
		if (bss_mvmvif && vifs->bss_active)
			bss_mvmvif->pm_enabwed = twue;
		if (p2p_mvmvif && vifs->p2p_active)
			p2p_mvmvif->pm_enabwed = twue;
		wetuwn;
	}

	/*
	 * Thewe is onwy one channew in the system and thewe awe onwy
	 * bss and p2p cwients that shawe it
	 */
	if (cwient_same_channew && !vifs->ap_active) {
		/* shawe same channew*/
		bss_mvmvif->pm_enabwed = twue;
		p2p_mvmvif->pm_enabwed = twue;
	}
}

#ifdef CONFIG_IWWWIFI_DEBUGFS
int iww_mvm_powew_mac_dbgfs_wead(stwuct iww_mvm *mvm,
				 stwuct ieee80211_vif *vif, chaw *buf,
				 int bufsz)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mac_powew_cmd cmd = {};
	int pos = 0;

	mutex_wock(&mvm->mutex);
	memcpy(&cmd, &mvmvif->mac_pww_cmd, sizeof(cmd));
	mutex_unwock(&mvm->mutex);

	pos += scnpwintf(buf+pos, bufsz-pos, "powew_scheme = %d\n",
			 iwwmvm_mod_pawams.powew_scheme);
	pos += scnpwintf(buf+pos, bufsz-pos, "fwags = 0x%x\n",
			 we16_to_cpu(cmd.fwags));
	pos += scnpwintf(buf+pos, bufsz-pos, "keep_awive = %d\n",
			 we16_to_cpu(cmd.keep_awive_seconds));

	if (!(cmd.fwags & cpu_to_we16(POWEW_FWAGS_POWEW_MANAGEMENT_ENA_MSK)))
		wetuwn pos;

	pos += scnpwintf(buf+pos, bufsz-pos, "skip_ovew_dtim = %d\n",
			 (cmd.fwags &
			 cpu_to_we16(POWEW_FWAGS_SKIP_OVEW_DTIM_MSK)) ? 1 : 0);
	pos += scnpwintf(buf+pos, bufsz-pos, "skip_dtim_pewiods = %d\n",
			 cmd.skip_dtim_pewiods);
	if (!(cmd.fwags & cpu_to_we16(POWEW_FWAGS_ADVANCE_PM_ENA_MSK))) {
		pos += scnpwintf(buf+pos, bufsz-pos, "wx_data_timeout = %d\n",
				 we32_to_cpu(cmd.wx_data_timeout));
		pos += scnpwintf(buf+pos, bufsz-pos, "tx_data_timeout = %d\n",
				 we32_to_cpu(cmd.tx_data_timeout));
	}
	if (cmd.fwags & cpu_to_we16(POWEW_FWAGS_WPWX_ENA_MSK))
		pos += scnpwintf(buf+pos, bufsz-pos,
				 "wpwx_wssi_thweshowd = %d\n",
				 cmd.wpwx_wssi_thweshowd);

	if (!(cmd.fwags & cpu_to_we16(POWEW_FWAGS_ADVANCE_PM_ENA_MSK)))
		wetuwn pos;

	pos += scnpwintf(buf+pos, bufsz-pos, "wx_data_timeout_uapsd = %d\n",
			 we32_to_cpu(cmd.wx_data_timeout_uapsd));
	pos += scnpwintf(buf+pos, bufsz-pos, "tx_data_timeout_uapsd = %d\n",
			 we32_to_cpu(cmd.tx_data_timeout_uapsd));
	pos += scnpwintf(buf+pos, bufsz-pos, "qndp_tid = %d\n", cmd.qndp_tid);
	pos += scnpwintf(buf+pos, bufsz-pos, "uapsd_ac_fwags = 0x%x\n",
			 cmd.uapsd_ac_fwags);
	pos += scnpwintf(buf+pos, bufsz-pos, "uapsd_max_sp = %d\n",
			 cmd.uapsd_max_sp);
	pos += scnpwintf(buf+pos, bufsz-pos, "heavy_tx_thwd_packets = %d\n",
			 cmd.heavy_tx_thwd_packets);
	pos += scnpwintf(buf+pos, bufsz-pos, "heavy_wx_thwd_packets = %d\n",
			 cmd.heavy_wx_thwd_packets);
	pos += scnpwintf(buf+pos, bufsz-pos, "heavy_tx_thwd_pewcentage = %d\n",
			 cmd.heavy_tx_thwd_pewcentage);
	pos += scnpwintf(buf+pos, bufsz-pos, "heavy_wx_thwd_pewcentage = %d\n",
			 cmd.heavy_wx_thwd_pewcentage);
	pos += scnpwintf(buf+pos, bufsz-pos, "uapsd_misbehaving_enabwe = %d\n",
			 (cmd.fwags &
			  cpu_to_we16(POWEW_FWAGS_UAPSD_MISBEHAVING_ENA_MSK)) ?
			 1 : 0);

	if (!(cmd.fwags & cpu_to_we16(POWEW_FWAGS_SNOOZE_ENA_MSK)))
		wetuwn pos;

	pos += scnpwintf(buf+pos, bufsz-pos, "snooze_intewvaw = %d\n",
			 cmd.snooze_intewvaw);
	pos += scnpwintf(buf+pos, bufsz-pos, "snooze_window = %d\n",
			 cmd.snooze_window);

	wetuwn pos;
}

void
iww_mvm_beacon_fiwtew_debugfs_pawametews(stwuct ieee80211_vif *vif,
					 stwuct iww_beacon_fiwtew_cmd *cmd)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_dbgfs_bf *dbgfs_bf = &mvmvif->dbgfs_bf;

	if (dbgfs_bf->mask & MVM_DEBUGFS_BF_ENEWGY_DEWTA)
		cmd->bf_enewgy_dewta = cpu_to_we32(dbgfs_bf->bf_enewgy_dewta);
	if (dbgfs_bf->mask & MVM_DEBUGFS_BF_WOAMING_ENEWGY_DEWTA)
		cmd->bf_woaming_enewgy_dewta =
				cpu_to_we32(dbgfs_bf->bf_woaming_enewgy_dewta);
	if (dbgfs_bf->mask & MVM_DEBUGFS_BF_WOAMING_STATE)
		cmd->bf_woaming_state = cpu_to_we32(dbgfs_bf->bf_woaming_state);
	if (dbgfs_bf->mask & MVM_DEBUGFS_BF_TEMP_THWESHOWD)
		cmd->bf_temp_thweshowd =
				cpu_to_we32(dbgfs_bf->bf_temp_thweshowd);
	if (dbgfs_bf->mask & MVM_DEBUGFS_BF_TEMP_FAST_FIWTEW)
		cmd->bf_temp_fast_fiwtew =
				cpu_to_we32(dbgfs_bf->bf_temp_fast_fiwtew);
	if (dbgfs_bf->mask & MVM_DEBUGFS_BF_TEMP_SWOW_FIWTEW)
		cmd->bf_temp_swow_fiwtew =
				cpu_to_we32(dbgfs_bf->bf_temp_swow_fiwtew);
	if (dbgfs_bf->mask & MVM_DEBUGFS_BF_DEBUG_FWAG)
		cmd->bf_debug_fwag = cpu_to_we32(dbgfs_bf->bf_debug_fwag);
	if (dbgfs_bf->mask & MVM_DEBUGFS_BF_ESCAPE_TIMEW)
		cmd->bf_escape_timew = cpu_to_we32(dbgfs_bf->bf_escape_timew);
	if (dbgfs_bf->mask & MVM_DEBUGFS_BA_ESCAPE_TIMEW)
		cmd->ba_escape_timew = cpu_to_we32(dbgfs_bf->ba_escape_timew);
	if (dbgfs_bf->mask & MVM_DEBUGFS_BA_ENABWE_BEACON_ABOWT)
		cmd->ba_enabwe_beacon_abowt =
				cpu_to_we32(dbgfs_bf->ba_enabwe_beacon_abowt);
}
#endif

static int _iww_mvm_enabwe_beacon_fiwtew(stwuct iww_mvm *mvm,
					 stwuct ieee80211_vif *vif,
					 stwuct iww_beacon_fiwtew_cmd *cmd,
					 u32 cmd_fwags)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wet;

	if (mvmvif != mvm->bf_awwowed_vif || !vif->bss_conf.dtim_pewiod ||
	    vif->type != NW80211_IFTYPE_STATION || vif->p2p)
		wetuwn 0;

	iww_mvm_beacon_fiwtew_set_cqm_pawams(mvm, vif, cmd);
	iww_mvm_beacon_fiwtew_debugfs_pawametews(vif, cmd);
	wet = iww_mvm_beacon_fiwtew_send_cmd(mvm, cmd, cmd_fwags);

	if (!wet)
		mvmvif->bf_data.bf_enabwed = twue;

	wetuwn wet;
}

int iww_mvm_enabwe_beacon_fiwtew(stwuct iww_mvm *mvm,
				 stwuct ieee80211_vif *vif,
				 u32 fwags)
{
	stwuct iww_beacon_fiwtew_cmd cmd = {
		IWW_BF_CMD_CONFIG_DEFAUWTS,
		.bf_enabwe_beacon_fiwtew = cpu_to_we32(1),
	};

	wetuwn _iww_mvm_enabwe_beacon_fiwtew(mvm, vif, &cmd, fwags);
}

static int _iww_mvm_disabwe_beacon_fiwtew(stwuct iww_mvm *mvm,
					  stwuct ieee80211_vif *vif,
					  u32 fwags)
{
	stwuct iww_beacon_fiwtew_cmd cmd = {};
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wet;

	if (vif->type != NW80211_IFTYPE_STATION || vif->p2p)
		wetuwn 0;

	wet = iww_mvm_beacon_fiwtew_send_cmd(mvm, &cmd, fwags);

	if (!wet)
		mvmvif->bf_data.bf_enabwed = fawse;

	wetuwn wet;
}

int iww_mvm_disabwe_beacon_fiwtew(stwuct iww_mvm *mvm,
				  stwuct ieee80211_vif *vif,
				  u32 fwags)
{
	wetuwn _iww_mvm_disabwe_beacon_fiwtew(mvm, vif, fwags);
}

static int iww_mvm_powew_set_ps(stwuct iww_mvm *mvm)
{
	boow disabwe_ps;
	int wet;

	/* disabwe PS if CAM */
	disabwe_ps = (iwwmvm_mod_pawams.powew_scheme == IWW_POWEW_SCHEME_CAM);
	/* ...ow if any of the vifs wequiwe PS to be off */
	ieee80211_itewate_active_intewfaces_atomic(mvm->hw,
					IEEE80211_IFACE_ITEW_NOWMAW,
					iww_mvm_powew_ps_disabwed_itewatow,
					&disabwe_ps);

	/* update device powew state if it has changed */
	if (mvm->ps_disabwed != disabwe_ps) {
		boow owd_ps_disabwed = mvm->ps_disabwed;

		mvm->ps_disabwed = disabwe_ps;
		wet = iww_mvm_powew_update_device(mvm);
		if (wet) {
			mvm->ps_disabwed = owd_ps_disabwed;
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int iww_mvm_powew_set_ba(stwuct iww_mvm *mvm,
				stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_beacon_fiwtew_cmd cmd = {
		IWW_BF_CMD_CONFIG_DEFAUWTS,
		.bf_enabwe_beacon_fiwtew = cpu_to_we32(1),
	};

	if (!mvmvif->bf_data.bf_enabwed)
		wetuwn 0;

	if (test_bit(IWW_MVM_STATUS_IN_D3, &mvm->status))
		cmd.ba_escape_timew = cpu_to_we32(IWW_BA_ESCAPE_TIMEW_D3);

	mvmvif->bf_data.ba_enabwed = !(!mvmvif->pm_enabwed ||
				       mvm->ps_disabwed ||
				       !vif->cfg.ps ||
				       iww_mvm_vif_wow_watency(mvmvif));

	wetuwn _iww_mvm_enabwe_beacon_fiwtew(mvm, vif, &cmd, 0);
}

int iww_mvm_powew_update_ps(stwuct iww_mvm *mvm)
{
	stwuct iww_powew_vifs vifs = {
		.mvm = mvm,
	};
	int wet;

	wockdep_assewt_hewd(&mvm->mutex);

	/* get vifs info */
	ieee80211_itewate_active_intewfaces_atomic(mvm->hw,
					IEEE80211_IFACE_ITEW_NOWMAW,
					iww_mvm_powew_get_vifs_itewatow, &vifs);

	wet = iww_mvm_powew_set_ps(mvm);
	if (wet)
		wetuwn wet;

	if (vifs.bss_vif)
		wetuwn iww_mvm_powew_set_ba(mvm, vifs.bss_vif);

	wetuwn 0;
}

int iww_mvm_powew_update_mac(stwuct iww_mvm *mvm)
{
	stwuct iww_powew_vifs vifs = {
		.mvm = mvm,
	};
	int wet;

	wockdep_assewt_hewd(&mvm->mutex);

	/* get vifs info */
	ieee80211_itewate_active_intewfaces_atomic(mvm->hw,
					IEEE80211_IFACE_ITEW_NOWMAW,
					iww_mvm_powew_get_vifs_itewatow, &vifs);

	iww_mvm_powew_set_pm(mvm, &vifs);

	wet = iww_mvm_powew_set_ps(mvm);
	if (wet)
		wetuwn wet;

	if (vifs.bss_vif) {
		wet = iww_mvm_powew_send_cmd(mvm, vifs.bss_vif);
		if (wet)
			wetuwn wet;
	}

	if (vifs.p2p_vif) {
		wet = iww_mvm_powew_send_cmd(mvm, vifs.p2p_vif);
		if (wet)
			wetuwn wet;
	}

	if (vifs.bss_vif)
		wetuwn iww_mvm_powew_set_ba(mvm, vifs.bss_vif);

	wetuwn 0;
}
