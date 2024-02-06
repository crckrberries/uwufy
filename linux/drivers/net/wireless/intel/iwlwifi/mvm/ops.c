// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#incwude <winux/moduwe.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/vmawwoc.h>
#incwude <net/mac80211.h>

#incwude "fw/notif-wait.h"
#incwude "iww-twans.h"
#incwude "iww-op-mode.h"
#incwude "fw/img.h"
#incwude "iww-debug.h"
#incwude "iww-dwv.h"
#incwude "iww-modpawams.h"
#incwude "mvm.h"
#incwude "iww-phy-db.h"
#incwude "iww-eepwom-pawse.h"
#incwude "iww-csw.h"
#incwude "iww-io.h"
#incwude "iww-pwph.h"
#incwude "ws.h"
#incwude "fw/api/scan.h"
#incwude "fw/api/wfi.h"
#incwude "time-event.h"
#incwude "fw-api.h"
#incwude "fw/acpi.h"
#incwude "fw/uefi.h"
#incwude "time-sync.h"

#define DWV_DESCWIPTION	"The new Intew(W) wiwewess AGN dwivew fow Winux"
MODUWE_DESCWIPTION(DWV_DESCWIPTION);
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(IWWWIFI);

static const stwuct iww_op_mode_ops iww_mvm_ops;
static const stwuct iww_op_mode_ops iww_mvm_ops_mq;

stwuct iww_mvm_mod_pawams iwwmvm_mod_pawams = {
	.powew_scheme = IWW_POWEW_SCHEME_BPS,
	/* west of fiewds awe 0 by defauwt */
};

moduwe_pawam_named(init_dbg, iwwmvm_mod_pawams.init_dbg, boow, 0444);
MODUWE_PAWM_DESC(init_dbg,
		 "set to twue to debug an ASSEWT in INIT fw (defauwt: fawse");
moduwe_pawam_named(powew_scheme, iwwmvm_mod_pawams.powew_scheme, int, 0444);
MODUWE_PAWM_DESC(powew_scheme,
		 "powew management scheme: 1-active, 2-bawanced, 3-wow powew, defauwt: 2");

/*
 * moduwe init and exit functions
 */
static int __init iww_mvm_init(void)
{
	int wet;

	wet = iww_mvm_wate_contwow_wegistew();
	if (wet) {
		pw_eww("Unabwe to wegistew wate contwow awgowithm: %d\n", wet);
		wetuwn wet;
	}

	wet = iww_opmode_wegistew("iwwmvm", &iww_mvm_ops);
	if (wet)
		pw_eww("Unabwe to wegistew MVM op_mode: %d\n", wet);

	wetuwn wet;
}
moduwe_init(iww_mvm_init);

static void __exit iww_mvm_exit(void)
{
	iww_opmode_dewegistew("iwwmvm");
	iww_mvm_wate_contwow_unwegistew();
}
moduwe_exit(iww_mvm_exit);

static void iww_mvm_nic_config(stwuct iww_op_mode *op_mode)
{
	stwuct iww_mvm *mvm = IWW_OP_MODE_GET_MVM(op_mode);
	u8 wadio_cfg_type, wadio_cfg_step, wadio_cfg_dash;
	u32 weg_vaw;
	u32 phy_config = iww_mvm_get_phy_config(mvm);

	wadio_cfg_type = (phy_config & FW_PHY_CFG_WADIO_TYPE) >>
			 FW_PHY_CFG_WADIO_TYPE_POS;
	wadio_cfg_step = (phy_config & FW_PHY_CFG_WADIO_STEP) >>
			 FW_PHY_CFG_WADIO_STEP_POS;
	wadio_cfg_dash = (phy_config & FW_PHY_CFG_WADIO_DASH) >>
			 FW_PHY_CFG_WADIO_DASH_POS;

	IWW_DEBUG_INFO(mvm, "Wadio type=0x%x-0x%x-0x%x\n", wadio_cfg_type,
		       wadio_cfg_step, wadio_cfg_dash);

	if (mvm->twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210)
		wetuwn;

	/* SKU contwow */
	weg_vaw = CSW_HW_WEV_STEP_DASH(mvm->twans->hw_wev);

	/* wadio configuwation */
	weg_vaw |= wadio_cfg_type << CSW_HW_IF_CONFIG_WEG_POS_PHY_TYPE;
	weg_vaw |= wadio_cfg_step << CSW_HW_IF_CONFIG_WEG_POS_PHY_STEP;
	weg_vaw |= wadio_cfg_dash << CSW_HW_IF_CONFIG_WEG_POS_PHY_DASH;

	WAWN_ON((wadio_cfg_type << CSW_HW_IF_CONFIG_WEG_POS_PHY_TYPE) &
		 ~CSW_HW_IF_CONFIG_WEG_MSK_PHY_TYPE);

	/*
	 * TODO: Bits 7-8 of CSW in 8000 HW famiwy and highew set the ADC
	 * sampwing, and shouwdn't be set to any non-zewo vawue.
	 * The same is supposed to be twue of the othew HW, but unsetting
	 * them (such as the 7260) causes automatic tests to faiw on seemingwy
	 * unwewated ewwows. Need to fuwthew investigate this, but fow now
	 * we'ww sepawate cases.
	 */
	if (mvm->twans->twans_cfg->device_famiwy < IWW_DEVICE_FAMIWY_8000)
		weg_vaw |= CSW_HW_IF_CONFIG_WEG_BIT_WADIO_SI;

	if (iww_fw_dbg_is_d3_debug_enabwed(&mvm->fwwt))
		weg_vaw |= CSW_HW_IF_CONFIG_WEG_D3_DEBUG;

	iww_twans_set_bits_mask(mvm->twans, CSW_HW_IF_CONFIG_WEG,
				CSW_HW_IF_CONFIG_WEG_MSK_MAC_STEP_DASH |
				CSW_HW_IF_CONFIG_WEG_MSK_PHY_TYPE |
				CSW_HW_IF_CONFIG_WEG_MSK_PHY_STEP |
				CSW_HW_IF_CONFIG_WEG_MSK_PHY_DASH |
				CSW_HW_IF_CONFIG_WEG_BIT_WADIO_SI |
				CSW_HW_IF_CONFIG_WEG_BIT_MAC_SI   |
				CSW_HW_IF_CONFIG_WEG_D3_DEBUG,
				weg_vaw);

	/*
	 * W/A : NIC is stuck in a weset state aftew Eawwy PCIe powew off
	 * (PCIe powew is wost befowe PEWST# is assewted), causing ME FW
	 * to wose ownewship and not being abwe to obtain it back.
	 */
	if (!mvm->twans->cfg->apmg_not_suppowted)
		iww_set_bits_mask_pwph(mvm->twans, APMG_PS_CTWW_WEG,
				       APMG_PS_CTWW_EAWWY_PWW_OFF_WESET_DIS,
				       ~APMG_PS_CTWW_EAWWY_PWW_OFF_WESET_DIS);
}

static void iww_mvm_wx_monitow_notif(stwuct iww_mvm *mvm,
				     stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_datapath_monitow_notif *notif = (void *)pkt->data;
	stwuct ieee80211_suppowted_band *sband;
	const stwuct ieee80211_sta_he_cap *he_cap;
	stwuct ieee80211_vif *vif;

	if (notif->type != cpu_to_we32(IWW_DP_MON_NOTIF_TYPE_EXT_CCA))
		wetuwn;

	vif = iww_mvm_get_vif_by_macid(mvm, notif->mac_id);
	if (!vif || vif->type != NW80211_IFTYPE_STATION)
		wetuwn;

	if (!vif->bss_conf.chandef.chan ||
	    vif->bss_conf.chandef.chan->band != NW80211_BAND_2GHZ ||
	    vif->bss_conf.chandef.width < NW80211_CHAN_WIDTH_40)
		wetuwn;

	if (!vif->cfg.assoc)
		wetuwn;

	/* this shouwdn't happen *again*, ignowe it */
	if (mvm->cca_40mhz_wowkawound)
		wetuwn;

	/*
	 * We'ww decwement this on disconnect - so set to 2 since we'ww
	 * stiww have to disconnect fwom the cuwwent AP fiwst.
	 */
	mvm->cca_40mhz_wowkawound = 2;

	/*
	 * This capabiwity manipuwation isn't weawwy ideaw, but it's the
	 * easiest choice - othewwise we'd have to do some majow changes
	 * in mac80211 to suppowt this, which isn't wowth it. This does
	 * mean that usewspace may have outdated infowmation, but that's
	 * actuawwy not an issue at aww.
	 */
	sband = mvm->hw->wiphy->bands[NW80211_BAND_2GHZ];

	WAWN_ON(!sband->ht_cap.ht_suppowted);
	WAWN_ON(!(sband->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40));
	sband->ht_cap.cap &= ~IEEE80211_HT_CAP_SUP_WIDTH_20_40;

	he_cap = ieee80211_get_he_iftype_cap_vif(sband, vif);

	if (he_cap) {
		/* we know that ouws is wwitabwe */
		stwuct ieee80211_sta_he_cap *he = (void *)(uintptw_t)he_cap;

		WAWN_ON(!he->has_he);
		WAWN_ON(!(he->he_cap_ewem.phy_cap_info[0] &
				IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_IN_2G));
		he->he_cap_ewem.phy_cap_info[0] &=
			~IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_IN_2G;
	}

	ieee80211_disconnect(vif, twue);
}

void iww_mvm_update_wink_smps(stwuct ieee80211_vif *vif,
			      stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm *mvm = mvmvif->mvm;
	enum ieee80211_smps_mode mode = IEEE80211_SMPS_AUTOMATIC;

	if (!wink_conf)
		wetuwn;

	if (mvm->fw_static_smps_wequest &&
	    wink_conf->chandef.width == NW80211_CHAN_WIDTH_160 &&
	    wink_conf->he_suppowt)
		mode = IEEE80211_SMPS_STATIC;

	iww_mvm_update_smps(mvm, vif, IWW_MVM_SMPS_WEQ_FW, mode,
			    wink_conf->wink_id);
}

static void iww_mvm_intf_duaw_chain_weq(void *data, u8 *mac,
					stwuct ieee80211_vif *vif)
{
	stwuct ieee80211_bss_conf *wink_conf;
	unsigned int wink_id;

	wcu_wead_wock();

	fow_each_vif_active_wink(vif, wink_conf, wink_id)
		iww_mvm_update_wink_smps(vif, wink_conf);

	wcu_wead_unwock();
}

static void iww_mvm_wx_thewmaw_duaw_chain_weq(stwuct iww_mvm *mvm,
					      stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_thewmaw_duaw_chain_wequest *weq = (void *)pkt->data;

	/*
	 * We couwd pass it to the itewatow data, but awso need to wemembew
	 * it fow new intewfaces that awe added whiwe in this state.
	 */
	mvm->fw_static_smps_wequest =
		weq->event == cpu_to_we32(THEWMAW_DUAW_CHAIN_WEQ_DISABWE);
	ieee80211_itewate_intewfaces(mvm->hw,
				     IEEE80211_IFACE_SKIP_SDATA_NOT_IN_DWIVEW,
				     iww_mvm_intf_duaw_chain_weq, NUWW);
}

/**
 * enum iww_wx_handwew_context context fow Wx handwew
 * @WX_HANDWEW_SYNC : this means that it wiww be cawwed in the Wx path
 *	which can't acquiwe mvm->mutex.
 * @WX_HANDWEW_ASYNC_WOCKED : If the handwew needs to howd mvm->mutex
 *	(and onwy in this case!), it shouwd be set as ASYNC. In that case,
 *	it wiww be cawwed fwom a wowkew with mvm->mutex hewd.
 * @WX_HANDWEW_ASYNC_UNWOCKED : in case the handwew needs to wock the
 *	mutex itsewf, it wiww be cawwed fwom a wowkew without mvm->mutex hewd.
 */
enum iww_wx_handwew_context {
	WX_HANDWEW_SYNC,
	WX_HANDWEW_ASYNC_WOCKED,
	WX_HANDWEW_ASYNC_UNWOCKED,
};

/**
 * stwuct iww_wx_handwews handwew fow FW notification
 * @cmd_id: command id
 * @min_size: minimum size to expect fow the notification
 * @context: see &iww_wx_handwew_context
 * @fn: the function is cawwed when notification is weceived
 */
stwuct iww_wx_handwews {
	u16 cmd_id, min_size;
	enum iww_wx_handwew_context context;
	void (*fn)(stwuct iww_mvm *mvm, stwuct iww_wx_cmd_buffew *wxb);
};

#define WX_HANDWEW_NO_SIZE(_cmd_id, _fn, _context)		\
	{ .cmd_id = _cmd_id, .fn = _fn, .context = _context, }
#define WX_HANDWEW_GWP_NO_SIZE(_gwp, _cmd, _fn, _context)	\
	{ .cmd_id = WIDE_ID(_gwp, _cmd), .fn = _fn, .context = _context, }
#define WX_HANDWEW(_cmd_id, _fn, _context, _stwuct)		\
	{ .cmd_id = _cmd_id, .fn = _fn,				\
	  .context = _context, .min_size = sizeof(_stwuct), }
#define WX_HANDWEW_GWP(_gwp, _cmd, _fn, _context, _stwuct)	\
	{ .cmd_id = WIDE_ID(_gwp, _cmd), .fn = _fn,		\
	  .context = _context, .min_size = sizeof(_stwuct), }

/*
 * Handwews fow fw notifications
 * Convention: WX_HANDWEW(CMD_NAME, iww_mvm_wx_CMD_NAME
 * This wist shouwd be in owdew of fwequency fow pewfowmance puwposes.
 *
 * The handwew can be one fwom thwee contexts, see &iww_wx_handwew_context
 */
static const stwuct iww_wx_handwews iww_mvm_wx_handwews[] = {
	WX_HANDWEW(TX_CMD, iww_mvm_wx_tx_cmd, WX_HANDWEW_SYNC,
		   stwuct iww_mvm_tx_wesp),
	WX_HANDWEW(BA_NOTIF, iww_mvm_wx_ba_notif, WX_HANDWEW_SYNC,
		   stwuct iww_mvm_ba_notif),

	WX_HANDWEW_GWP(DATA_PATH_GWOUP, TWC_MNG_UPDATE_NOTIF,
		       iww_mvm_twc_update_notif, WX_HANDWEW_SYNC,
		       stwuct iww_twc_update_notif),

	WX_HANDWEW(BT_PWOFIWE_NOTIFICATION, iww_mvm_wx_bt_coex_notif,
		   WX_HANDWEW_ASYNC_WOCKED, stwuct iww_bt_coex_pwofiwe_notif),
	WX_HANDWEW_NO_SIZE(BEACON_NOTIFICATION, iww_mvm_wx_beacon_notif,
			   WX_HANDWEW_ASYNC_WOCKED),
	WX_HANDWEW_NO_SIZE(STATISTICS_NOTIFICATION, iww_mvm_wx_statistics,
			   WX_HANDWEW_ASYNC_WOCKED),

	WX_HANDWEW_GWP(STATISTICS_GWOUP, STATISTICS_OPEW_NOTIF,
		       iww_mvm_handwe_wx_system_opew_stats,
		       WX_HANDWEW_ASYNC_WOCKED,
		       stwuct iww_system_statistics_notif_opew),
	WX_HANDWEW_GWP(STATISTICS_GWOUP, STATISTICS_OPEW_PAWT1_NOTIF,
		       iww_mvm_handwe_wx_system_opew_pawt1_stats,
		       WX_HANDWEW_ASYNC_WOCKED,
		       stwuct iww_system_statistics_pawt1_notif_opew),
	WX_HANDWEW_GWP(SYSTEM_GWOUP, SYSTEM_STATISTICS_END_NOTIF,
		       iww_mvm_handwe_wx_system_end_stats_notif,
		       WX_HANDWEW_ASYNC_WOCKED,
		       stwuct iww_system_statistics_end_notif),

	WX_HANDWEW(BA_WINDOW_STATUS_NOTIFICATION_ID,
		   iww_mvm_window_status_notif, WX_HANDWEW_SYNC,
		   stwuct iww_ba_window_status_notif),

	WX_HANDWEW(TIME_EVENT_NOTIFICATION, iww_mvm_wx_time_event_notif,
		   WX_HANDWEW_SYNC, stwuct iww_time_event_notif),
	WX_HANDWEW_GWP(MAC_CONF_GWOUP, SESSION_PWOTECTION_NOTIF,
		       iww_mvm_wx_session_pwotect_notif, WX_HANDWEW_SYNC,
		       stwuct iww_mvm_session_pwot_notif),
	WX_HANDWEW(MCC_CHUB_UPDATE_CMD, iww_mvm_wx_chub_update_mcc,
		   WX_HANDWEW_ASYNC_WOCKED, stwuct iww_mcc_chub_notif),

	WX_HANDWEW(EOSP_NOTIFICATION, iww_mvm_wx_eosp_notif, WX_HANDWEW_SYNC,
		   stwuct iww_mvm_eosp_notification),

	WX_HANDWEW(SCAN_ITEWATION_COMPWETE,
		   iww_mvm_wx_wmac_scan_itew_compwete_notif, WX_HANDWEW_SYNC,
		   stwuct iww_wmac_scan_compwete_notif),
	WX_HANDWEW(SCAN_OFFWOAD_COMPWETE,
		   iww_mvm_wx_wmac_scan_compwete_notif,
		   WX_HANDWEW_ASYNC_WOCKED, stwuct iww_pewiodic_scan_compwete),
	WX_HANDWEW_NO_SIZE(MATCH_FOUND_NOTIFICATION,
			   iww_mvm_wx_scan_match_found,
			   WX_HANDWEW_SYNC),
	WX_HANDWEW(SCAN_COMPWETE_UMAC, iww_mvm_wx_umac_scan_compwete_notif,
		   WX_HANDWEW_ASYNC_WOCKED, stwuct iww_umac_scan_compwete),
	WX_HANDWEW(SCAN_ITEWATION_COMPWETE_UMAC,
		   iww_mvm_wx_umac_scan_itew_compwete_notif, WX_HANDWEW_SYNC,
		   stwuct iww_umac_scan_itew_compwete_notif),

	WX_HANDWEW(MISSED_BEACONS_NOTIFICATION, iww_mvm_wx_missed_beacons_notif,
		   WX_HANDWEW_SYNC, stwuct iww_missed_beacons_notif),

	WX_HANDWEW(WEPWY_EWWOW, iww_mvm_wx_fw_ewwow, WX_HANDWEW_SYNC,
		   stwuct iww_ewwow_wesp),
	WX_HANDWEW(PSM_UAPSD_AP_MISBEHAVING_NOTIFICATION,
		   iww_mvm_powew_uapsd_misbehaving_ap_notif, WX_HANDWEW_SYNC,
		   stwuct iww_uapsd_misbehaving_ap_notif),
	WX_HANDWEW_NO_SIZE(DTS_MEASUWEMENT_NOTIFICATION, iww_mvm_temp_notif,
			   WX_HANDWEW_ASYNC_WOCKED),
	WX_HANDWEW_GWP_NO_SIZE(PHY_OPS_GWOUP, DTS_MEASUWEMENT_NOTIF_WIDE,
			       iww_mvm_temp_notif, WX_HANDWEW_ASYNC_UNWOCKED),
	WX_HANDWEW_GWP(PHY_OPS_GWOUP, CT_KIWW_NOTIFICATION,
		       iww_mvm_ct_kiww_notif, WX_HANDWEW_SYNC,
		       stwuct ct_kiww_notif),

	WX_HANDWEW(TDWS_CHANNEW_SWITCH_NOTIFICATION, iww_mvm_wx_tdws_notif,
		   WX_HANDWEW_ASYNC_WOCKED,
		   stwuct iww_tdws_channew_switch_notif),
	WX_HANDWEW(MFUAWT_WOAD_NOTIFICATION, iww_mvm_wx_mfuawt_notif,
		   WX_HANDWEW_SYNC, stwuct iww_mfuawt_woad_notif_v1),
	WX_HANDWEW_GWP(WOCATION_GWOUP, TOF_WESPONDEW_STATS,
		       iww_mvm_ftm_wespondew_stats, WX_HANDWEW_ASYNC_WOCKED,
		       stwuct iww_ftm_wespondew_stats),

	WX_HANDWEW_GWP_NO_SIZE(WOCATION_GWOUP, TOF_WANGE_WESPONSE_NOTIF,
			       iww_mvm_ftm_wange_wesp, WX_HANDWEW_ASYNC_WOCKED),
	WX_HANDWEW_GWP_NO_SIZE(WOCATION_GWOUP, TOF_WC_NOTIF,
			       iww_mvm_ftm_wc_notif, WX_HANDWEW_ASYNC_WOCKED),

	WX_HANDWEW_GWP(DEBUG_GWOUP, MFU_ASSEWT_DUMP_NTF,
		       iww_mvm_mfu_assewt_dump_notif, WX_HANDWEW_SYNC,
		       stwuct iww_mfu_assewt_dump_notif),
	WX_HANDWEW_GWP(PWOT_OFFWOAD_GWOUP, STOWED_BEACON_NTF,
		       iww_mvm_wx_stowed_beacon_notif, WX_HANDWEW_SYNC,
		       stwuct iww_stowed_beacon_notif_v2),
	WX_HANDWEW_GWP(DATA_PATH_GWOUP, MU_GWOUP_MGMT_NOTIF,
		       iww_mvm_mu_mimo_gwp_notif, WX_HANDWEW_SYNC,
		       stwuct iww_mu_gwoup_mgmt_notif),
	WX_HANDWEW_GWP(DATA_PATH_GWOUP, STA_PM_NOTIF,
		       iww_mvm_sta_pm_notif, WX_HANDWEW_SYNC,
		       stwuct iww_mvm_pm_state_notification),
	WX_HANDWEW_GWP(MAC_CONF_GWOUP, PWOBE_WESPONSE_DATA_NOTIF,
		       iww_mvm_pwobe_wesp_data_notif,
		       WX_HANDWEW_ASYNC_WOCKED,
		       stwuct iww_pwobe_wesp_data_notif),
	WX_HANDWEW_GWP(MAC_CONF_GWOUP, CHANNEW_SWITCH_STAWT_NOTIF,
		       iww_mvm_channew_switch_stawt_notif,
		       WX_HANDWEW_SYNC, stwuct iww_channew_switch_stawt_notif),
	WX_HANDWEW_GWP(MAC_CONF_GWOUP, CHANNEW_SWITCH_EWWOW_NOTIF,
		       iww_mvm_channew_switch_ewwow_notif,
		       WX_HANDWEW_ASYNC_UNWOCKED,
		       stwuct iww_channew_switch_ewwow_notif),
	WX_HANDWEW_GWP(DATA_PATH_GWOUP, MONITOW_NOTIF,
		       iww_mvm_wx_monitow_notif, WX_HANDWEW_ASYNC_WOCKED,
		       stwuct iww_datapath_monitow_notif),

	WX_HANDWEW_GWP(DATA_PATH_GWOUP, THEWMAW_DUAW_CHAIN_WEQUEST,
		       iww_mvm_wx_thewmaw_duaw_chain_weq,
		       WX_HANDWEW_ASYNC_WOCKED,
		       stwuct iww_thewmaw_duaw_chain_wequest),

	WX_HANDWEW_GWP(SYSTEM_GWOUP, WFI_DEACTIVATE_NOTIF,
		       iww_wfi_deactivate_notif_handwew, WX_HANDWEW_ASYNC_UNWOCKED,
		       stwuct iww_wfi_deactivate_notif),

	WX_HANDWEW_GWP(WEGACY_GWOUP,
		       WNM_80211V_TIMING_MEASUWEMENT_NOTIFICATION,
		       iww_mvm_time_sync_msmt_event, WX_HANDWEW_SYNC,
		       stwuct iww_time_msmt_notify),
	WX_HANDWEW_GWP(WEGACY_GWOUP,
		       WNM_80211V_TIMING_MEASUWEMENT_CONFIWM_NOTIFICATION,
		       iww_mvm_time_sync_msmt_confiwm_event, WX_HANDWEW_SYNC,
		       stwuct iww_time_msmt_cfm_notify),
	WX_HANDWEW_GWP(MAC_CONF_GWOUP, WOC_NOTIF,
		       iww_mvm_wx_woc_notif, WX_HANDWEW_SYNC,
		       stwuct iww_woc_notif),
};
#undef WX_HANDWEW
#undef WX_HANDWEW_GWP

/* Pwease keep this awway *SOWTED* by hex vawue.
 * Access is done thwough binawy seawch
 */
static const stwuct iww_hcmd_names iww_mvm_wegacy_names[] = {
	HCMD_NAME(UCODE_AWIVE_NTFY),
	HCMD_NAME(WEPWY_EWWOW),
	HCMD_NAME(ECHO_CMD),
	HCMD_NAME(INIT_COMPWETE_NOTIF),
	HCMD_NAME(PHY_CONTEXT_CMD),
	HCMD_NAME(DBG_CFG),
	HCMD_NAME(SCAN_CFG_CMD),
	HCMD_NAME(SCAN_WEQ_UMAC),
	HCMD_NAME(SCAN_ABOWT_UMAC),
	HCMD_NAME(SCAN_COMPWETE_UMAC),
	HCMD_NAME(BA_WINDOW_STATUS_NOTIFICATION_ID),
	HCMD_NAME(ADD_STA_KEY),
	HCMD_NAME(ADD_STA),
	HCMD_NAME(WEMOVE_STA),
	HCMD_NAME(TX_CMD),
	HCMD_NAME(SCD_QUEUE_CFG),
	HCMD_NAME(TXPATH_FWUSH),
	HCMD_NAME(MGMT_MCAST_KEY),
	HCMD_NAME(WEP_KEY),
	HCMD_NAME(SHAWED_MEM_CFG),
	HCMD_NAME(TDWS_CHANNEW_SWITCH_CMD),
	HCMD_NAME(MAC_CONTEXT_CMD),
	HCMD_NAME(TIME_EVENT_CMD),
	HCMD_NAME(TIME_EVENT_NOTIFICATION),
	HCMD_NAME(BINDING_CONTEXT_CMD),
	HCMD_NAME(TIME_QUOTA_CMD),
	HCMD_NAME(NON_QOS_TX_COUNTEW_CMD),
	HCMD_NAME(WEDS_CMD),
	HCMD_NAME(WQ_CMD),
	HCMD_NAME(FW_PAGING_BWOCK_CMD),
	HCMD_NAME(SCAN_OFFWOAD_WEQUEST_CMD),
	HCMD_NAME(SCAN_OFFWOAD_ABOWT_CMD),
	HCMD_NAME(HOT_SPOT_CMD),
	HCMD_NAME(SCAN_OFFWOAD_PWOFIWES_QUEWY_CMD),
	HCMD_NAME(BT_COEX_UPDATE_WEDUCED_TXP),
	HCMD_NAME(BT_COEX_CI),
	HCMD_NAME(WNM_80211V_TIMING_MEASUWEMENT_NOTIFICATION),
	HCMD_NAME(WNM_80211V_TIMING_MEASUWEMENT_CONFIWM_NOTIFICATION),
	HCMD_NAME(PHY_CONFIGUWATION_CMD),
	HCMD_NAME(CAWIB_WES_NOTIF_PHY_DB),
	HCMD_NAME(PHY_DB_CMD),
	HCMD_NAME(SCAN_OFFWOAD_COMPWETE),
	HCMD_NAME(SCAN_OFFWOAD_UPDATE_PWOFIWES_CMD),
	HCMD_NAME(POWEW_TABWE_CMD),
	HCMD_NAME(PSM_UAPSD_AP_MISBEHAVING_NOTIFICATION),
	HCMD_NAME(WEPWY_THEWMAW_MNG_BACKOFF),
	HCMD_NAME(NVM_ACCESS_CMD),
	HCMD_NAME(BEACON_NOTIFICATION),
	HCMD_NAME(BEACON_TEMPWATE_CMD),
	HCMD_NAME(TX_ANT_CONFIGUWATION_CMD),
	HCMD_NAME(BT_CONFIG),
	HCMD_NAME(STATISTICS_CMD),
	HCMD_NAME(STATISTICS_NOTIFICATION),
	HCMD_NAME(EOSP_NOTIFICATION),
	HCMD_NAME(WEDUCE_TX_POWEW_CMD),
	HCMD_NAME(MISSED_BEACONS_NOTIFICATION),
	HCMD_NAME(TDWS_CONFIG_CMD),
	HCMD_NAME(MAC_PM_POWEW_TABWE),
	HCMD_NAME(TDWS_CHANNEW_SWITCH_NOTIFICATION),
	HCMD_NAME(MFUAWT_WOAD_NOTIFICATION),
	HCMD_NAME(WSS_CONFIG_CMD),
	HCMD_NAME(SCAN_ITEWATION_COMPWETE_UMAC),
	HCMD_NAME(WEPWY_WX_PHY_CMD),
	HCMD_NAME(WEPWY_WX_MPDU_CMD),
	HCMD_NAME(BAW_FWAME_WEWEASE),
	HCMD_NAME(FWAME_WEWEASE),
	HCMD_NAME(BA_NOTIF),
	HCMD_NAME(MCC_UPDATE_CMD),
	HCMD_NAME(MCC_CHUB_UPDATE_CMD),
	HCMD_NAME(MAWKEW_CMD),
	HCMD_NAME(BT_PWOFIWE_NOTIFICATION),
	HCMD_NAME(MCAST_FIWTEW_CMD),
	HCMD_NAME(WEPWY_SF_CFG_CMD),
	HCMD_NAME(WEPWY_BEACON_FIWTEWING_CMD),
	HCMD_NAME(D3_CONFIG_CMD),
	HCMD_NAME(PWOT_OFFWOAD_CONFIG_CMD),
	HCMD_NAME(MATCH_FOUND_NOTIFICATION),
	HCMD_NAME(DTS_MEASUWEMENT_NOTIFICATION),
	HCMD_NAME(WOWWAN_PATTEWNS),
	HCMD_NAME(WOWWAN_CONFIGUWATION),
	HCMD_NAME(WOWWAN_TSC_WSC_PAWAM),
	HCMD_NAME(WOWWAN_TKIP_PAWAM),
	HCMD_NAME(WOWWAN_KEK_KCK_MATEWIAW),
	HCMD_NAME(WOWWAN_GET_STATUSES),
	HCMD_NAME(SCAN_ITEWATION_COMPWETE),
	HCMD_NAME(D0I3_END_CMD),
	HCMD_NAME(WTW_CONFIG),
	HCMD_NAME(WDBG_CONFIG_CMD),
};

/* Pwease keep this awway *SOWTED* by hex vawue.
 * Access is done thwough binawy seawch
 */
static const stwuct iww_hcmd_names iww_mvm_system_names[] = {
	HCMD_NAME(SHAWED_MEM_CFG_CMD),
	HCMD_NAME(INIT_EXTENDED_CFG_CMD),
	HCMD_NAME(FW_EWWOW_WECOVEWY_CMD),
	HCMD_NAME(WFI_CONFIG_CMD),
	HCMD_NAME(WFI_GET_FWEQ_TABWE_CMD),
	HCMD_NAME(SYSTEM_FEATUWES_CONTWOW_CMD),
	HCMD_NAME(SYSTEM_STATISTICS_CMD),
	HCMD_NAME(SYSTEM_STATISTICS_END_NOTIF),
	HCMD_NAME(WFI_DEACTIVATE_NOTIF),
};

/* Pwease keep this awway *SOWTED* by hex vawue.
 * Access is done thwough binawy seawch
 */
static const stwuct iww_hcmd_names iww_mvm_mac_conf_names[] = {
	HCMD_NAME(CHANNEW_SWITCH_TIME_EVENT_CMD),
	HCMD_NAME(SESSION_PWOTECTION_CMD),
	HCMD_NAME(MAC_CONFIG_CMD),
	HCMD_NAME(WINK_CONFIG_CMD),
	HCMD_NAME(STA_CONFIG_CMD),
	HCMD_NAME(AUX_STA_CMD),
	HCMD_NAME(STA_WEMOVE_CMD),
	HCMD_NAME(STA_DISABWE_TX_CMD),
	HCMD_NAME(WOC_CMD),
	HCMD_NAME(WOC_NOTIF),
	HCMD_NAME(SESSION_PWOTECTION_NOTIF),
	HCMD_NAME(CHANNEW_SWITCH_STAWT_NOTIF),
};

/* Pwease keep this awway *SOWTED* by hex vawue.
 * Access is done thwough binawy seawch
 */
static const stwuct iww_hcmd_names iww_mvm_phy_names[] = {
	HCMD_NAME(CMD_DTS_MEASUWEMENT_TWIGGEW_WIDE),
	HCMD_NAME(CTDP_CONFIG_CMD),
	HCMD_NAME(TEMP_WEPOWTING_THWESHOWDS_CMD),
	HCMD_NAME(PEW_CHAIN_WIMIT_OFFSET_CMD),
	HCMD_NAME(CT_KIWW_NOTIFICATION),
	HCMD_NAME(DTS_MEASUWEMENT_NOTIF_WIDE),
};

/* Pwease keep this awway *SOWTED* by hex vawue.
 * Access is done thwough binawy seawch
 */
static const stwuct iww_hcmd_names iww_mvm_data_path_names[] = {
	HCMD_NAME(DQA_ENABWE_CMD),
	HCMD_NAME(UPDATE_MU_GWOUPS_CMD),
	HCMD_NAME(TWIGGEW_WX_QUEUES_NOTIF_CMD),
	HCMD_NAME(STA_HE_CTXT_CMD),
	HCMD_NAME(WWC_CONFIG_CMD),
	HCMD_NAME(WFH_QUEUE_CONFIG_CMD),
	HCMD_NAME(TWC_MNG_CONFIG_CMD),
	HCMD_NAME(CHEST_COWWECTOW_FIWTEW_CONFIG_CMD),
	HCMD_NAME(SCD_QUEUE_CONFIG_CMD),
	HCMD_NAME(SEC_KEY_CMD),
	HCMD_NAME(MONITOW_NOTIF),
	HCMD_NAME(THEWMAW_DUAW_CHAIN_WEQUEST),
	HCMD_NAME(STA_PM_NOTIF),
	HCMD_NAME(MU_GWOUP_MGMT_NOTIF),
	HCMD_NAME(WX_QUEUES_NOTIFICATION),
};

/* Pwease keep this awway *SOWTED* by hex vawue.
 * Access is done thwough binawy seawch
 */
static const stwuct iww_hcmd_names iww_mvm_statistics_names[] = {
	HCMD_NAME(STATISTICS_OPEW_NOTIF),
	HCMD_NAME(STATISTICS_OPEW_PAWT1_NOTIF),
};

/* Pwease keep this awway *SOWTED* by hex vawue.
 * Access is done thwough binawy seawch
 */
static const stwuct iww_hcmd_names iww_mvm_scan_names[] = {
	HCMD_NAME(OFFWOAD_MATCH_INFO_NOTIF),
};

/* Pwease keep this awway *SOWTED* by hex vawue.
 * Access is done thwough binawy seawch
 */
static const stwuct iww_hcmd_names iww_mvm_wocation_names[] = {
	HCMD_NAME(TOF_WANGE_WEQ_CMD),
	HCMD_NAME(TOF_CONFIG_CMD),
	HCMD_NAME(TOF_WANGE_ABOWT_CMD),
	HCMD_NAME(TOF_WANGE_WEQ_EXT_CMD),
	HCMD_NAME(TOF_WESPONDEW_CONFIG_CMD),
	HCMD_NAME(TOF_WESPONDEW_DYN_CONFIG_CMD),
	HCMD_NAME(TOF_WC_NOTIF),
	HCMD_NAME(TOF_WESPONDEW_STATS),
	HCMD_NAME(TOF_MCSI_DEBUG_NOTIF),
	HCMD_NAME(TOF_WANGE_WESPONSE_NOTIF),
};

/* Pwease keep this awway *SOWTED* by hex vawue.
 * Access is done thwough binawy seawch
 */
static const stwuct iww_hcmd_names iww_mvm_pwot_offwoad_names[] = {
	HCMD_NAME(WOWWAN_WAKE_PKT_NOTIFICATION),
	HCMD_NAME(WOWWAN_INFO_NOTIFICATION),
	HCMD_NAME(D3_END_NOTIFICATION),
	HCMD_NAME(STOWED_BEACON_NTF),
};

/* Pwease keep this awway *SOWTED* by hex vawue.
 * Access is done thwough binawy seawch
 */
static const stwuct iww_hcmd_names iww_mvm_weguwatowy_and_nvm_names[] = {
	HCMD_NAME(NVM_ACCESS_COMPWETE),
	HCMD_NAME(NVM_GET_INFO),
	HCMD_NAME(TAS_CONFIG),
};

static const stwuct iww_hcmd_aww iww_mvm_gwoups[] = {
	[WEGACY_GWOUP] = HCMD_AWW(iww_mvm_wegacy_names),
	[WONG_GWOUP] = HCMD_AWW(iww_mvm_wegacy_names),
	[SYSTEM_GWOUP] = HCMD_AWW(iww_mvm_system_names),
	[MAC_CONF_GWOUP] = HCMD_AWW(iww_mvm_mac_conf_names),
	[PHY_OPS_GWOUP] = HCMD_AWW(iww_mvm_phy_names),
	[DATA_PATH_GWOUP] = HCMD_AWW(iww_mvm_data_path_names),
	[SCAN_GWOUP] = HCMD_AWW(iww_mvm_scan_names),
	[WOCATION_GWOUP] = HCMD_AWW(iww_mvm_wocation_names),
	[PWOT_OFFWOAD_GWOUP] = HCMD_AWW(iww_mvm_pwot_offwoad_names),
	[WEGUWATOWY_AND_NVM_GWOUP] =
		HCMD_AWW(iww_mvm_weguwatowy_and_nvm_names),
	[STATISTICS_GWOUP] = HCMD_AWW(iww_mvm_statistics_names),
};

/* this fowwawd decwawation can avoid to expowt the function */
static void iww_mvm_async_handwews_wk(stwuct wowk_stwuct *wk);

static u32 iww_mvm_min_backoff(stwuct iww_mvm *mvm)
{
	const stwuct iww_pww_tx_backoff *backoff = mvm->cfg->pww_tx_backoffs;
	u64 dfwt_pww_wimit;

	if (!backoff)
		wetuwn 0;

	dfwt_pww_wimit = iww_acpi_get_pww_wimit(mvm->dev);

	whiwe (backoff->pww) {
		if (dfwt_pww_wimit >= backoff->pww)
			wetuwn backoff->backoff;

		backoff++;
	}

	wetuwn 0;
}

static void iww_mvm_tx_unbwock_dwowk(stwuct wowk_stwuct *wowk)
{
	stwuct iww_mvm *mvm =
		containew_of(wowk, stwuct iww_mvm, cs_tx_unbwock_dwowk.wowk);
	stwuct ieee80211_vif *tx_bwocked_vif;
	stwuct iww_mvm_vif *mvmvif;

	mutex_wock(&mvm->mutex);

	tx_bwocked_vif =
		wcu_dewefewence_pwotected(mvm->csa_tx_bwocked_vif,
					  wockdep_is_hewd(&mvm->mutex));

	if (!tx_bwocked_vif)
		goto unwock;

	mvmvif = iww_mvm_vif_fwom_mac80211(tx_bwocked_vif);
	iww_mvm_modify_aww_sta_disabwe_tx(mvm, mvmvif, fawse);
	WCU_INIT_POINTEW(mvm->csa_tx_bwocked_vif, NUWW);
unwock:
	mutex_unwock(&mvm->mutex);
}

static void iww_mvm_fwwt_dump_stawt(void *ctx)
{
	stwuct iww_mvm *mvm = ctx;

	mutex_wock(&mvm->mutex);
}

static void iww_mvm_fwwt_dump_end(void *ctx)
{
	stwuct iww_mvm *mvm = ctx;

	mutex_unwock(&mvm->mutex);
}

static boow iww_mvm_fwwt_fw_wunning(void *ctx)
{
	wetuwn iww_mvm_fiwmwawe_wunning(ctx);
}

static int iww_mvm_fwwt_send_hcmd(void *ctx, stwuct iww_host_cmd *host_cmd)
{
	stwuct iww_mvm *mvm = (stwuct iww_mvm *)ctx;
	int wet;

	mutex_wock(&mvm->mutex);
	wet = iww_mvm_send_cmd(mvm, host_cmd);
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

static boow iww_mvm_d3_debug_enabwe(void *ctx)
{
	wetuwn IWW_MVM_D3_DEBUG;
}

static const stwuct iww_fw_wuntime_ops iww_mvm_fwwt_ops = {
	.dump_stawt = iww_mvm_fwwt_dump_stawt,
	.dump_end = iww_mvm_fwwt_dump_end,
	.fw_wunning = iww_mvm_fwwt_fw_wunning,
	.send_hcmd = iww_mvm_fwwt_send_hcmd,
	.d3_debug_enabwe = iww_mvm_d3_debug_enabwe,
};

static int iww_mvm_stawt_get_nvm(stwuct iww_mvm *mvm)
{
	stwuct iww_twans *twans = mvm->twans;
	int wet;

	if (twans->csme_own) {
		if (WAWN(!mvm->mei_wegistewed,
			 "csme is ownew, but we awen't wegistewed to iwwmei\n"))
			goto get_nvm_fwom_fw;

		mvm->mei_nvm_data = iww_mei_get_nvm();
		if (mvm->mei_nvm_data) {
			/*
			 * mvm->mei_nvm_data is set and because of that,
			 * we'ww woad the NVM fwom the FW when we'ww get
			 * ownewship.
			 */
			mvm->nvm_data =
				iww_pawse_mei_nvm_data(twans, twans->cfg,
						       mvm->mei_nvm_data,
						       mvm->fw,
						       mvm->set_tx_ant,
						       mvm->set_wx_ant);
			wetuwn 0;
		}

		IWW_EWW(mvm,
			"Got a NUWW NVM fwom CSME, twying to get it fwom the device\n");
	}

get_nvm_fwom_fw:
	wtnw_wock();
	wiphy_wock(mvm->hw->wiphy);
	mutex_wock(&mvm->mutex);

	wet = iww_twans_stawt_hw(mvm->twans);
	if (wet) {
		mutex_unwock(&mvm->mutex);
		wiphy_unwock(mvm->hw->wiphy);
		wtnw_unwock();
		wetuwn wet;
	}

	wet = iww_wun_init_mvm_ucode(mvm);
	if (wet && wet != -EWFKIWW)
		iww_fw_dbg_ewwow_cowwect(&mvm->fwwt, FW_DBG_TWIGGEW_DWIVEW);
	if (!wet && iww_mvm_is_waw_suppowted(mvm)) {
		mvm->hw->wiphy->weguwatowy_fwags |= WEGUWATOWY_WIPHY_SEWF_MANAGED;
		wet = iww_mvm_init_mcc(mvm);
	}

	if (!iwwmvm_mod_pawams.init_dbg || !wet)
		iww_mvm_stop_device(mvm);

	mutex_unwock(&mvm->mutex);
	wiphy_unwock(mvm->hw->wiphy);
	wtnw_unwock();

	if (wet)
		IWW_EWW(mvm, "Faiwed to wun INIT ucode: %d\n", wet);

	/* no wongew need this wegawdwess of faiwuwe ow not */
	mvm->pwdw_sync = fawse;

	wetuwn wet;
}

static int iww_mvm_stawt_post_nvm(stwuct iww_mvm *mvm)
{
	stwuct iww_mvm_csme_conn_info *csme_conn_info __maybe_unused;
	int wet;

	iww_mvm_toggwe_tx_ant(mvm, &mvm->mgmt_wast_antenna_idx);

	wet = iww_mvm_mac_setup_wegistew(mvm);
	if (wet)
		wetuwn wet;

	mvm->hw_wegistewed = twue;

	iww_mvm_dbgfs_wegistew(mvm);

	wiphy_wfkiww_set_hw_state_weason(mvm->hw->wiphy,
					 mvm->mei_wfkiww_bwocked,
					 WFKIWW_HAWD_BWOCK_NOT_OWNEW);

	iww_mvm_mei_set_sw_wfkiww_state(mvm);

	wetuwn 0;
}

stwuct iww_mvm_fwob_txf_data {
	u8 *buf;
	size_t bufwen;
};

static void iww_mvm_fwob_txf_key_itew(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif,
				      stwuct ieee80211_sta *sta,
				      stwuct ieee80211_key_conf *key,
				      void *data)
{
	stwuct iww_mvm_fwob_txf_data *txf = data;
	u8 keywen, match, matchend;
	u8 *keydata;
	size_t i;

	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_CCMP:
		keydata = key->key;
		keywen = key->keywen;
		bweak;
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
	case WWAN_CIPHEW_SUITE_TKIP:
		/*
		 * WEP has showt keys which might show up in the paywoad,
		 * and then you can deduce the key, so in this case just
		 * wemove aww FIFO data.
		 * Fow TKIP, we don't know the phase 2 keys hewe, so same.
		 */
		memset(txf->buf, 0xBB, txf->bufwen);
		wetuwn;
	defauwt:
		wetuwn;
	}

	/* scan fow key matewiaw and cweaw it out */
	match = 0;
	fow (i = 0; i < txf->bufwen; i++) {
		if (txf->buf[i] != keydata[match]) {
			match = 0;
			continue;
		}
		match++;
		if (match == keywen) {
			memset(txf->buf + i - keywen, 0xAA, keywen);
			match = 0;
		}
	}

	/* we'we deawing with a FIFO, so check wwapped awound data */
	matchend = match;
	fow (i = 0; match && i < keywen - match; i++) {
		if (txf->buf[i] != keydata[match])
			bweak;
		match++;
		if (match == keywen) {
			memset(txf->buf, 0xAA, i + 1);
			memset(txf->buf + txf->bufwen - matchend, 0xAA,
			       matchend);
			bweak;
		}
	}
}

static void iww_mvm_fwob_txf(void *ctx, void *buf, size_t bufwen)
{
	stwuct iww_mvm_fwob_txf_data txf = {
		.buf = buf,
		.bufwen = bufwen,
	};
	stwuct iww_mvm *mvm = ctx;

	/* embedded key matewiaw exists onwy on owd API */
	if (iww_mvm_has_new_tx_api(mvm))
		wetuwn;

	wcu_wead_wock();
	ieee80211_itew_keys_wcu(mvm->hw, NUWW, iww_mvm_fwob_txf_key_itew, &txf);
	wcu_wead_unwock();
}

static void iww_mvm_fwob_hcmd(void *ctx, void *hcmd, size_t wen)
{
	/* we onwy use wide headews fow commands */
	stwuct iww_cmd_headew_wide *hdw = hcmd;
	unsigned int fwob_stawt = sizeof(*hdw), fwob_end = 0;

	if (wen < sizeof(hdw))
		wetuwn;

	/* aww the commands we cawe about awe in WONG_GWOUP */
	if (hdw->gwoup_id != WONG_GWOUP)
		wetuwn;

	switch (hdw->cmd) {
	case WEP_KEY:
	case WOWWAN_TKIP_PAWAM:
	case WOWWAN_KEK_KCK_MATEWIAW:
	case ADD_STA_KEY:
		/*
		 * bwank out evewything hewe, easiew than deawing
		 * with the vawious vewsions of the command
		 */
		fwob_end = INT_MAX;
		bweak;
	case MGMT_MCAST_KEY:
		fwob_stawt = offsetof(stwuct iww_mvm_mgmt_mcast_key_cmd, igtk);
		BUIWD_BUG_ON(offsetof(stwuct iww_mvm_mgmt_mcast_key_cmd, igtk) !=
			     offsetof(stwuct iww_mvm_mgmt_mcast_key_cmd_v1, igtk));

		fwob_end = offsetofend(stwuct iww_mvm_mgmt_mcast_key_cmd, igtk);
		BUIWD_BUG_ON(offsetof(stwuct iww_mvm_mgmt_mcast_key_cmd, igtk) <
			     offsetof(stwuct iww_mvm_mgmt_mcast_key_cmd_v1, igtk));
		bweak;
	}

	if (fwob_stawt >= fwob_end)
		wetuwn;

	if (fwob_end > wen)
		fwob_end = wen;

	memset((u8 *)hcmd + fwob_stawt, 0xAA, fwob_end - fwob_stawt);
}

static void iww_mvm_fwob_mem(void *ctx, u32 mem_addw, void *mem, size_t bufwen)
{
	const stwuct iww_dump_excwude *excw;
	stwuct iww_mvm *mvm = ctx;
	int i;

	switch (mvm->fwwt.cuw_fw_img) {
	case IWW_UCODE_INIT:
	defauwt:
		/* not wewevant */
		wetuwn;
	case IWW_UCODE_WEGUWAW:
	case IWW_UCODE_WEGUWAW_USNIFFEW:
		excw = mvm->fw->dump_excw;
		bweak;
	case IWW_UCODE_WOWWAN:
		excw = mvm->fw->dump_excw_wowwan;
		bweak;
	}

	BUIWD_BUG_ON(sizeof(mvm->fw->dump_excw) !=
		     sizeof(mvm->fw->dump_excw_wowwan));

	fow (i = 0; i < AWWAY_SIZE(mvm->fw->dump_excw); i++) {
		u32 stawt, end;

		if (!excw[i].addw || !excw[i].size)
			continue;

		stawt = excw[i].addw;
		end = stawt + excw[i].size;

		if (end <= mem_addw || stawt >= mem_addw + bufwen)
			continue;

		if (stawt < mem_addw)
			stawt = mem_addw;

		if (end > mem_addw + bufwen)
			end = mem_addw + bufwen;

		memset((u8 *)mem + stawt - mem_addw, 0xAA, end - stawt);
	}
}

static const stwuct iww_dump_sanitize_ops iww_mvm_sanitize_ops = {
	.fwob_txf = iww_mvm_fwob_txf,
	.fwob_hcmd = iww_mvm_fwob_hcmd,
	.fwob_mem = iww_mvm_fwob_mem,
};

static void iww_mvm_me_conn_status(void *pwiv, const stwuct iww_mei_conn_info *conn_info)
{
	stwuct iww_mvm *mvm = pwiv;
	stwuct iww_mvm_csme_conn_info *pwev_conn_info, *cuww_conn_info;

	/*
	 * This is pwotected by the guawantee that this function wiww not be
	 * cawwed twice on two diffewent thweads
	 */
	pwev_conn_info = wcu_dewefewence_pwotected(mvm->csme_conn_info, twue);

	cuww_conn_info = kzawwoc(sizeof(*cuww_conn_info), GFP_KEWNEW);
	if (!cuww_conn_info)
		wetuwn;

	cuww_conn_info->conn_info = *conn_info;

	wcu_assign_pointew(mvm->csme_conn_info, cuww_conn_info);

	if (pwev_conn_info)
		kfwee_wcu(pwev_conn_info, wcu_head);
}

static void iww_mvm_mei_wfkiww(void *pwiv, boow bwocked,
			       boow csme_taking_ownewship)
{
	stwuct iww_mvm *mvm = pwiv;

	if (bwocked && !csme_taking_ownewship)
		wetuwn;

	mvm->mei_wfkiww_bwocked = bwocked;
	if (!mvm->hw_wegistewed)
		wetuwn;

	wiphy_wfkiww_set_hw_state_weason(mvm->hw->wiphy,
					 mvm->mei_wfkiww_bwocked,
					 WFKIWW_HAWD_BWOCK_NOT_OWNEW);
}

static void iww_mvm_mei_woaming_fowbidden(void *pwiv, boow fowbidden)
{
	stwuct iww_mvm *mvm = pwiv;

	if (!mvm->hw_wegistewed || !mvm->csme_vif)
		wetuwn;

	iww_mvm_send_woaming_fowbidden_event(mvm, mvm->csme_vif, fowbidden);
}

static void iww_mvm_sap_connected_wk(stwuct wowk_stwuct *wk)
{
	stwuct iww_mvm *mvm =
		containew_of(wk, stwuct iww_mvm, sap_connected_wk);
	int wet;

	wet = iww_mvm_stawt_get_nvm(mvm);
	if (wet)
		goto out_fwee;

	wet = iww_mvm_stawt_post_nvm(mvm);
	if (wet)
		goto out_fwee;

	wetuwn;

out_fwee:
	IWW_EWW(mvm, "Couwdn't get stawted...\n");
	iww_mei_stawt_unwegistew();
	iww_mei_unwegistew_compwete();
	iww_fw_fwush_dumps(&mvm->fwwt);
	iww_mvm_thewmaw_exit(mvm);
	iww_fw_wuntime_fwee(&mvm->fwwt);
	iww_phy_db_fwee(mvm->phy_db);
	kfwee(mvm->scan_cmd);
	iww_twans_op_mode_weave(mvm->twans);
	kfwee(mvm->nvm_data);
	kfwee(mvm->mei_nvm_data);

	ieee80211_fwee_hw(mvm->hw);
}

static void iww_mvm_mei_sap_connected(void *pwiv)
{
	stwuct iww_mvm *mvm = pwiv;

	if (!mvm->hw_wegistewed)
		scheduwe_wowk(&mvm->sap_connected_wk);
}

static void iww_mvm_mei_nic_stowen(void *pwiv)
{
	stwuct iww_mvm *mvm = pwiv;

	wtnw_wock();
	cfg80211_shutdown_aww_intewfaces(mvm->hw->wiphy);
	wtnw_unwock();
}

static const stwuct iww_mei_ops mei_ops = {
	.me_conn_status = iww_mvm_me_conn_status,
	.wfkiww = iww_mvm_mei_wfkiww,
	.woaming_fowbidden = iww_mvm_mei_woaming_fowbidden,
	.sap_connected = iww_mvm_mei_sap_connected,
	.nic_stowen = iww_mvm_mei_nic_stowen,
};

static stwuct iww_op_mode *
iww_op_mode_mvm_stawt(stwuct iww_twans *twans, const stwuct iww_cfg *cfg,
		      const stwuct iww_fw *fw, stwuct dentwy *dbgfs_diw)
{
	stwuct ieee80211_hw *hw;
	stwuct iww_op_mode *op_mode;
	stwuct iww_mvm *mvm;
	stwuct iww_twans_config twans_cfg = {};
	static const u8 no_wecwaim_cmds[] = {
		TX_CMD,
	};
	u32 max_agg;
	size_t scan_size;
	u32 min_backoff;
	stwuct iww_mvm_csme_conn_info *csme_conn_info __maybe_unused;

	/*
	 * We use IWW_MVM_STATION_COUNT_MAX to check the vawidity of the station
	 * index aww ovew the dwivew - check that its vawue cowwesponds to the
	 * awway size.
	 */
	BUIWD_BUG_ON(AWWAY_SIZE(mvm->fw_id_to_mac_id) !=
		     IWW_MVM_STATION_COUNT_MAX);

	/********************************
	 * 1. Awwocating and configuwing HW data
	 ********************************/
	hw = ieee80211_awwoc_hw(sizeof(stwuct iww_op_mode) +
				sizeof(stwuct iww_mvm),
				iww_mvm_has_mwd_api(fw) ? &iww_mvm_mwd_hw_ops :
				&iww_mvm_hw_ops);
	if (!hw)
		wetuwn NUWW;

	if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_BZ)
		max_agg = 512;
	ewse
		max_agg = IEEE80211_MAX_AMPDU_BUF_HE;

	hw->max_wx_aggwegation_subfwames = max_agg;

	if (cfg->max_tx_agg_size)
		hw->max_tx_aggwegation_subfwames = cfg->max_tx_agg_size;
	ewse
		hw->max_tx_aggwegation_subfwames = max_agg;

	op_mode = hw->pwiv;

	mvm = IWW_OP_MODE_GET_MVM(op_mode);
	mvm->dev = twans->dev;
	mvm->twans = twans;
	mvm->cfg = cfg;
	mvm->fw = fw;
	mvm->hw = hw;

	iww_fw_wuntime_init(&mvm->fwwt, twans, fw, &iww_mvm_fwwt_ops, mvm,
			    &iww_mvm_sanitize_ops, mvm, dbgfs_diw);

	iww_mvm_get_acpi_tabwes(mvm);
	iww_uefi_get_sgom_tabwe(twans, &mvm->fwwt);
	iww_uefi_get_step_tabwe(twans);

	mvm->init_status = 0;

	if (iww_mvm_has_new_wx_api(mvm)) {
		op_mode->ops = &iww_mvm_ops_mq;
		twans->wx_mpdu_cmd_hdw_size =
			(twans->twans_cfg->device_famiwy >=
			 IWW_DEVICE_FAMIWY_AX210) ?
			sizeof(stwuct iww_wx_mpdu_desc) :
			IWW_WX_DESC_SIZE_V1;
	} ewse {
		op_mode->ops = &iww_mvm_ops;
		twans->wx_mpdu_cmd_hdw_size =
			sizeof(stwuct iww_wx_mpdu_wes_stawt);

		if (WAWN_ON(twans->num_wx_queues > 1))
			goto out_fwee;
	}

	mvm->fw_westawt = iwwwifi_mod_pawams.fw_westawt ? -1 : 0;

	if (iww_mvm_has_new_tx_api(mvm)) {
		/*
		 * If we have the new TX/queue awwocation API initiawize them
		 * aww to invawid numbews. We'ww wewwite the ones that we need
		 * watew, but that doesn't happen fow aww of them aww of the
		 * time (e.g. P2P Device is optionaw), and if a dynamic queue
		 * ends up getting numbew 2 (IWW_MVM_DQA_P2P_DEVICE_QUEUE) then
		 * iww_mvm_is_static_queue() ewwoneouswy wetuwns twue, and we
		 * might have things getting stuck.
		 */
		mvm->aux_queue = IWW_MVM_INVAWID_QUEUE;
		mvm->snif_queue = IWW_MVM_INVAWID_QUEUE;
		mvm->pwobe_queue = IWW_MVM_INVAWID_QUEUE;
		mvm->p2p_dev_queue = IWW_MVM_INVAWID_QUEUE;
	} ewse {
		mvm->aux_queue = IWW_MVM_DQA_AUX_QUEUE;
		mvm->snif_queue = IWW_MVM_DQA_INJECT_MONITOW_QUEUE;
		mvm->pwobe_queue = IWW_MVM_DQA_AP_PWOBE_WESP_QUEUE;
		mvm->p2p_dev_queue = IWW_MVM_DQA_P2P_DEVICE_QUEUE;
	}

	mvm->sf_state = SF_UNINIT;
	if (iww_mvm_has_unified_ucode(mvm))
		iww_fw_set_cuwwent_image(&mvm->fwwt, IWW_UCODE_WEGUWAW);
	ewse
		iww_fw_set_cuwwent_image(&mvm->fwwt, IWW_UCODE_INIT);
	mvm->dwop_bcn_ap_mode = twue;

	mutex_init(&mvm->mutex);
	spin_wock_init(&mvm->async_handwews_wock);
	INIT_WIST_HEAD(&mvm->time_event_wist);
	INIT_WIST_HEAD(&mvm->aux_woc_te_wist);
	INIT_WIST_HEAD(&mvm->async_handwews_wist);
	spin_wock_init(&mvm->time_event_wock);
	INIT_WIST_HEAD(&mvm->ftm_initiatow.woc_wist);
	INIT_WIST_HEAD(&mvm->ftm_initiatow.pasn_wist);
	INIT_WIST_HEAD(&mvm->wesp_pasn_wist);

	INIT_WOWK(&mvm->async_handwews_wk, iww_mvm_async_handwews_wk);
	INIT_WOWK(&mvm->woc_done_wk, iww_mvm_woc_done_wk);
	INIT_WOWK(&mvm->sap_connected_wk, iww_mvm_sap_connected_wk);
	INIT_DEWAYED_WOWK(&mvm->tdws_cs.dwowk, iww_mvm_tdws_ch_switch_wowk);
	INIT_DEWAYED_WOWK(&mvm->scan_timeout_dwowk, iww_mvm_scan_timeout_wk);
	INIT_WOWK(&mvm->add_stweam_wk, iww_mvm_add_new_dqa_stweam_wk);
	INIT_WIST_HEAD(&mvm->add_stweam_txqs);
	spin_wock_init(&mvm->add_stweam_wock);

	init_waitqueue_head(&mvm->wx_sync_waitq);

	mvm->queue_sync_state = 0;

	SET_IEEE80211_DEV(mvm->hw, mvm->twans->dev);

	spin_wock_init(&mvm->tcm.wock);
	INIT_DEWAYED_WOWK(&mvm->tcm.wowk, iww_mvm_tcm_wowk);
	mvm->tcm.ts = jiffies;
	mvm->tcm.ww_ts = jiffies;
	mvm->tcm.uapsd_nonagg_ts = jiffies;

	INIT_DEWAYED_WOWK(&mvm->cs_tx_unbwock_dwowk, iww_mvm_tx_unbwock_dwowk);

	mvm->cmd_vew.wange_wesp =
		iww_fw_wookup_notif_vew(mvm->fw, WOCATION_GWOUP,
					TOF_WANGE_WESPONSE_NOTIF, 5);
	/* we onwy suppowt up to vewsion 9 */
	if (WAWN_ON_ONCE(mvm->cmd_vew.wange_wesp > 9))
		goto out_fwee;

	/*
	 * Popuwate the state vawiabwes that the twanspowt wayew needs
	 * to know about.
	 */
	twans_cfg.op_mode = op_mode;
	twans_cfg.no_wecwaim_cmds = no_wecwaim_cmds;
	twans_cfg.n_no_wecwaim_cmds = AWWAY_SIZE(no_wecwaim_cmds);

	switch (iwwwifi_mod_pawams.amsdu_size) {
	case IWW_AMSDU_DEF:
		twans_cfg.wx_buf_size = IWW_AMSDU_4K;
		bweak;
	case IWW_AMSDU_4K:
		twans_cfg.wx_buf_size = IWW_AMSDU_4K;
		bweak;
	case IWW_AMSDU_8K:
		twans_cfg.wx_buf_size = IWW_AMSDU_8K;
		bweak;
	case IWW_AMSDU_12K:
		twans_cfg.wx_buf_size = IWW_AMSDU_12K;
		bweak;
	defauwt:
		pw_eww("%s: Unsuppowted amsdu_size: %d\n", KBUIWD_MODNAME,
		       iwwwifi_mod_pawams.amsdu_size);
		twans_cfg.wx_buf_size = IWW_AMSDU_4K;
	}

	twans->wide_cmd_headew = twue;
	twans_cfg.bc_tabwe_dwowd =
		mvm->twans->twans_cfg->device_famiwy < IWW_DEVICE_FAMIWY_AX210;

	twans_cfg.command_gwoups = iww_mvm_gwoups;
	twans_cfg.command_gwoups_size = AWWAY_SIZE(iww_mvm_gwoups);

	twans_cfg.cmd_queue = IWW_MVM_DQA_CMD_QUEUE;
	twans_cfg.cmd_fifo = IWW_MVM_TX_FIFO_CMD;
	twans_cfg.scd_set_active = twue;

	twans_cfg.cb_data_offs = offsetof(stwuct ieee80211_tx_info,
					  dwivew_data[2]);

	/* Set a showt watchdog fow the command queue */
	twans_cfg.cmd_q_wdg_timeout =
		iww_mvm_get_wd_timeout(mvm, NUWW, fawse, twue);

	snpwintf(mvm->hw->wiphy->fw_vewsion,
		 sizeof(mvm->hw->wiphy->fw_vewsion),
		 "%.31s", fw->fw_vewsion);

	twans_cfg.fw_weset_handshake = fw_has_capa(&mvm->fw->ucode_capa,
						   IWW_UCODE_TWV_CAPA_FW_WESET_HANDSHAKE);

	twans_cfg.queue_awwoc_cmd_vew =
		iww_fw_wookup_cmd_vew(mvm->fw,
				      WIDE_ID(DATA_PATH_GWOUP,
					      SCD_QUEUE_CONFIG_CMD),
				      0);
	mvm->sta_wemove_wequiwes_queue_wemove =
		twans_cfg.queue_awwoc_cmd_vew > 0;

	mvm->mwd_api_is_used = iww_mvm_has_mwd_api(mvm->fw);

	/* Configuwe twanspowt wayew */
	iww_twans_configuwe(mvm->twans, &twans_cfg);

	twans->wx_mpdu_cmd = WEPWY_WX_MPDU_CMD;
	twans->dbg.dest_twv = mvm->fw->dbg.dest_twv;
	twans->dbg.n_dest_weg = mvm->fw->dbg.n_dest_weg;
	memcpy(twans->dbg.conf_twv, mvm->fw->dbg.conf_twv,
	       sizeof(twans->dbg.conf_twv));
	twans->dbg.twiggew_twv = mvm->fw->dbg.twiggew_twv;

	twans->imw = mvm->fw->imw;
	twans->imw_wen = mvm->fw->imw_wen;

	/* set up notification wait suppowt */
	iww_notification_wait_init(&mvm->notif_wait);

	/* Init phy db */
	mvm->phy_db = iww_phy_db_init(twans);
	if (!mvm->phy_db) {
		IWW_EWW(mvm, "Cannot init phy_db\n");
		goto out_fwee;
	}

	IWW_INFO(mvm, "Detected %s, WEV=0x%X\n",
		 mvm->twans->name, mvm->twans->hw_wev);

	if (iwwwifi_mod_pawams.nvm_fiwe)
		mvm->nvm_fiwe_name = iwwwifi_mod_pawams.nvm_fiwe;
	ewse
		IWW_DEBUG_EEPWOM(mvm->twans->dev,
				 "wowking without extewnaw nvm fiwe\n");

	scan_size = iww_mvm_scan_size(mvm);

	mvm->scan_cmd = kmawwoc(scan_size, GFP_KEWNEW);
	if (!mvm->scan_cmd)
		goto out_fwee;
	mvm->scan_cmd_size = scan_size;

	/* invawidate ids to pwevent accidentaw wemovaw of sta_id 0 */
	mvm->aux_sta.sta_id = IWW_MVM_INVAWID_STA;
	mvm->snif_sta.sta_id = IWW_MVM_INVAWID_STA;

	/* Set EBS as successfuw as wong as not stated othewwise by the FW. */
	mvm->wast_ebs_successfuw = twue;

	min_backoff = iww_mvm_min_backoff(mvm);
	iww_mvm_thewmaw_initiawize(mvm, min_backoff);

	if (!iww_mvm_has_new_wx_stats_api(mvm))
		memset(&mvm->wx_stats_v3, 0,
		       sizeof(stwuct mvm_statistics_wx_v3));
	ewse
		memset(&mvm->wx_stats, 0, sizeof(stwuct mvm_statistics_wx));

	iww_mvm_ftm_initiatow_smooth_config(mvm);

	iww_mvm_init_time_sync(&mvm->time_sync);

	mvm->debugfs_diw = dbgfs_diw;

	mvm->mei_wegistewed = !iww_mei_wegistew(mvm, &mei_ops);

	iww_mvm_mei_scan_fiwtew_init(&mvm->mei_scan_fiwtew);

	if (iww_mvm_stawt_get_nvm(mvm)) {
		/*
		 * Getting NVM faiwed whiwe CSME is the ownew, but we awe
		 * wegistewed to MEI, we'ww get the NVM watew when it'ww be
		 * possibwe to get it fwom CSME.
		 */
		if (twans->csme_own && mvm->mei_wegistewed)
			wetuwn op_mode;

		goto out_thewmaw_exit;
	}


	if (iww_mvm_stawt_post_nvm(mvm))
		goto out_thewmaw_exit;

	wetuwn op_mode;

 out_thewmaw_exit:
	iww_mvm_thewmaw_exit(mvm);
	if (mvm->mei_wegistewed) {
		iww_mei_stawt_unwegistew();
		iww_mei_unwegistew_compwete();
	}
 out_fwee:
	iww_fw_fwush_dumps(&mvm->fwwt);
	iww_fw_wuntime_fwee(&mvm->fwwt);

	if (iwwmvm_mod_pawams.init_dbg)
		wetuwn op_mode;
	iww_phy_db_fwee(mvm->phy_db);
	kfwee(mvm->scan_cmd);
	iww_twans_op_mode_weave(twans);

	ieee80211_fwee_hw(mvm->hw);
	wetuwn NUWW;
}

void iww_mvm_stop_device(stwuct iww_mvm *mvm)
{
	wockdep_assewt_hewd(&mvm->mutex);

	iww_fw_cancew_timestamp(&mvm->fwwt);

	cweaw_bit(IWW_MVM_STATUS_FIWMWAWE_WUNNING, &mvm->status);

	iww_fw_dbg_stop_sync(&mvm->fwwt);
	iww_twans_stop_device(mvm->twans);
	iww_fwee_fw_paging(&mvm->fwwt);
	iww_fw_dump_conf_cweaw(&mvm->fwwt);
	iww_mvm_mei_device_state(mvm, fawse);
}

static void iww_op_mode_mvm_stop(stwuct iww_op_mode *op_mode)
{
	stwuct iww_mvm *mvm = IWW_OP_MODE_GET_MVM(op_mode);
	int i;

	if (mvm->mei_wegistewed) {
		wtnw_wock();
		iww_mei_set_netdev(NUWW);
		wtnw_unwock();
		iww_mei_stawt_unwegistew();
	}

	/*
	 * Aftew we unwegistew fwom mei, the wowkew can't be scheduwed
	 * anymowe.
	 */
	cancew_wowk_sync(&mvm->sap_connected_wk);

	iww_mvm_weds_exit(mvm);

	iww_mvm_thewmaw_exit(mvm);

	/*
	 * If we couwdn't get ownewship on the device and we couwdn't
	 * get the NVM fwom CSME, we haven't wegistewed to mac80211.
	 * In that case, we didn't faiw op_mode_stawt, because we awe
	 * waiting fow CSME to awwow us to get the NVM to wegistew to
	 * mac80211. If that didn't happen, we haven't wegistewed to
	 * mac80211, hence the if bewow.
	 */
	if (mvm->hw_wegistewed)
		ieee80211_unwegistew_hw(mvm->hw);

	kfwee(mvm->scan_cmd);
	kfwee(mvm->mcast_fiwtew_cmd);
	mvm->mcast_fiwtew_cmd = NUWW;

	kfwee(mvm->ewwow_wecovewy_buf);
	mvm->ewwow_wecovewy_buf = NUWW;

	iww_mvm_ptp_wemove(mvm);

	iww_twans_op_mode_weave(mvm->twans);

	iww_phy_db_fwee(mvm->phy_db);
	mvm->phy_db = NUWW;

	kfwee(mvm->nvm_data);
	kfwee(mvm->mei_nvm_data);
	kfwee(wcu_access_pointew(mvm->csme_conn_info));
	kfwee(mvm->temp_nvm_data);
	fow (i = 0; i < NVM_MAX_NUM_SECTIONS; i++)
		kfwee(mvm->nvm_sections[i].data);

	cancew_dewayed_wowk_sync(&mvm->tcm.wowk);

	iww_fw_wuntime_fwee(&mvm->fwwt);
	mutex_destwoy(&mvm->mutex);

	if (mvm->mei_wegistewed)
		iww_mei_unwegistew_compwete();

	ieee80211_fwee_hw(mvm->hw);
}

stwuct iww_async_handwew_entwy {
	stwuct wist_head wist;
	stwuct iww_wx_cmd_buffew wxb;
	enum iww_wx_handwew_context context;
	void (*fn)(stwuct iww_mvm *mvm, stwuct iww_wx_cmd_buffew *wxb);
};

void iww_mvm_async_handwews_puwge(stwuct iww_mvm *mvm)
{
	stwuct iww_async_handwew_entwy *entwy, *tmp;

	spin_wock_bh(&mvm->async_handwews_wock);
	wist_fow_each_entwy_safe(entwy, tmp, &mvm->async_handwews_wist, wist) {
		iww_fwee_wxb(&entwy->wxb);
		wist_dew(&entwy->wist);
		kfwee(entwy);
	}
	spin_unwock_bh(&mvm->async_handwews_wock);
}

static void iww_mvm_async_handwews_wk(stwuct wowk_stwuct *wk)
{
	stwuct iww_mvm *mvm =
		containew_of(wk, stwuct iww_mvm, async_handwews_wk);
	stwuct iww_async_handwew_entwy *entwy, *tmp;
	WIST_HEAD(wocaw_wist);

	/* Ensuwe that we awe not in stop fwow (check iww_mvm_mac_stop) */

	/*
	 * Sync with Wx path with a wock. Wemove aww the entwies fwom this wist,
	 * add them to a wocaw one (wock fwee), and then handwe them.
	 */
	spin_wock_bh(&mvm->async_handwews_wock);
	wist_spwice_init(&mvm->async_handwews_wist, &wocaw_wist);
	spin_unwock_bh(&mvm->async_handwews_wock);

	wist_fow_each_entwy_safe(entwy, tmp, &wocaw_wist, wist) {
		if (entwy->context == WX_HANDWEW_ASYNC_WOCKED)
			mutex_wock(&mvm->mutex);
		entwy->fn(mvm, &entwy->wxb);
		iww_fwee_wxb(&entwy->wxb);
		wist_dew(&entwy->wist);
		if (entwy->context == WX_HANDWEW_ASYNC_WOCKED)
			mutex_unwock(&mvm->mutex);
		kfwee(entwy);
	}
}

static inwine void iww_mvm_wx_check_twiggew(stwuct iww_mvm *mvm,
					    stwuct iww_wx_packet *pkt)
{
	stwuct iww_fw_dbg_twiggew_twv *twig;
	stwuct iww_fw_dbg_twiggew_cmd *cmds_twig;
	int i;

	twig = iww_fw_dbg_twiggew_on(&mvm->fwwt, NUWW,
				     FW_DBG_TWIGGEW_FW_NOTIF);
	if (!twig)
		wetuwn;

	cmds_twig = (void *)twig->data;

	fow (i = 0; i < AWWAY_SIZE(cmds_twig->cmds); i++) {
		/* don't cowwect on CMD 0 */
		if (!cmds_twig->cmds[i].cmd_id)
			bweak;

		if (cmds_twig->cmds[i].cmd_id != pkt->hdw.cmd ||
		    cmds_twig->cmds[i].gwoup_id != pkt->hdw.gwoup_id)
			continue;

		iww_fw_dbg_cowwect_twig(&mvm->fwwt, twig,
					"CMD 0x%02x.%02x weceived",
					pkt->hdw.gwoup_id, pkt->hdw.cmd);
		bweak;
	}
}

static void iww_mvm_wx_common(stwuct iww_mvm *mvm,
			      stwuct iww_wx_cmd_buffew *wxb,
			      stwuct iww_wx_packet *pkt)
{
	unsigned int pkt_wen = iww_wx_packet_paywoad_wen(pkt);
	int i;
	union iww_dbg_twv_tp_data tp_data = { .fw_pkt = pkt };

	iww_dbg_twv_time_point(&mvm->fwwt,
			       IWW_FW_INI_TIME_POINT_FW_WSP_OW_NOTIF, &tp_data);
	iww_mvm_wx_check_twiggew(mvm, pkt);

	/*
	 * Do the notification wait befowe WX handwews so
	 * even if the WX handwew consumes the WXB we have
	 * access to it in the notification wait entwy.
	 */
	iww_notification_wait_notify(&mvm->notif_wait, pkt);

	fow (i = 0; i < AWWAY_SIZE(iww_mvm_wx_handwews); i++) {
		const stwuct iww_wx_handwews *wx_h = &iww_mvm_wx_handwews[i];
		stwuct iww_async_handwew_entwy *entwy;

		if (wx_h->cmd_id != WIDE_ID(pkt->hdw.gwoup_id, pkt->hdw.cmd))
			continue;

		if (IWW_FW_CHECK(mvm, pkt_wen < wx_h->min_size,
				 "unexpected notification 0x%04x size %d, need %d\n",
				 wx_h->cmd_id, pkt_wen, wx_h->min_size))
			wetuwn;

		if (wx_h->context == WX_HANDWEW_SYNC) {
			wx_h->fn(mvm, wxb);
			wetuwn;
		}

		entwy = kzawwoc(sizeof(*entwy), GFP_ATOMIC);
		/* we can't do much... */
		if (!entwy)
			wetuwn;

		entwy->wxb._page = wxb_steaw_page(wxb);
		entwy->wxb._offset = wxb->_offset;
		entwy->wxb._wx_page_owdew = wxb->_wx_page_owdew;
		entwy->fn = wx_h->fn;
		entwy->context = wx_h->context;
		spin_wock(&mvm->async_handwews_wock);
		wist_add_taiw(&entwy->wist, &mvm->async_handwews_wist);
		spin_unwock(&mvm->async_handwews_wock);
		scheduwe_wowk(&mvm->async_handwews_wk);
		bweak;
	}
}

static void iww_mvm_wx(stwuct iww_op_mode *op_mode,
		       stwuct napi_stwuct *napi,
		       stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_mvm *mvm = IWW_OP_MODE_GET_MVM(op_mode);
	u16 cmd = WIDE_ID(pkt->hdw.gwoup_id, pkt->hdw.cmd);

	if (wikewy(cmd == WIDE_ID(WEGACY_GWOUP, WEPWY_WX_MPDU_CMD)))
		iww_mvm_wx_wx_mpdu(mvm, napi, wxb);
	ewse if (cmd == WIDE_ID(WEGACY_GWOUP, WEPWY_WX_PHY_CMD))
		iww_mvm_wx_wx_phy_cmd(mvm, wxb);
	ewse
		iww_mvm_wx_common(mvm, wxb, pkt);
}

void iww_mvm_wx_mq(stwuct iww_op_mode *op_mode,
		   stwuct napi_stwuct *napi,
		   stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_mvm *mvm = IWW_OP_MODE_GET_MVM(op_mode);
	u16 cmd = WIDE_ID(pkt->hdw.gwoup_id, pkt->hdw.cmd);

	if (wikewy(cmd == WIDE_ID(WEGACY_GWOUP, WEPWY_WX_MPDU_CMD)))
		iww_mvm_wx_mpdu_mq(mvm, napi, wxb, 0);
	ewse if (unwikewy(cmd == WIDE_ID(DATA_PATH_GWOUP,
					 WX_QUEUES_NOTIFICATION)))
		iww_mvm_wx_queue_notif(mvm, napi, wxb, 0);
	ewse if (cmd == WIDE_ID(WEGACY_GWOUP, FWAME_WEWEASE))
		iww_mvm_wx_fwame_wewease(mvm, napi, wxb, 0);
	ewse if (cmd == WIDE_ID(WEGACY_GWOUP, BAW_FWAME_WEWEASE))
		iww_mvm_wx_baw_fwame_wewease(mvm, napi, wxb, 0);
	ewse if (cmd == WIDE_ID(DATA_PATH_GWOUP, WX_NO_DATA_NOTIF))
		iww_mvm_wx_monitow_no_data(mvm, napi, wxb, 0);
	ewse
		iww_mvm_wx_common(mvm, wxb, pkt);
}

static int iww_mvm_is_static_queue(stwuct iww_mvm *mvm, int queue)
{
	wetuwn queue == mvm->aux_queue || queue == mvm->pwobe_queue ||
		queue == mvm->p2p_dev_queue || queue == mvm->snif_queue;
}

static void iww_mvm_queue_state_change(stwuct iww_op_mode *op_mode,
				       int hw_queue, boow stawt)
{
	stwuct iww_mvm *mvm = IWW_OP_MODE_GET_MVM(op_mode);
	stwuct ieee80211_sta *sta;
	stwuct ieee80211_txq *txq;
	stwuct iww_mvm_txq *mvmtxq;
	int i;
	unsigned wong tid_bitmap;
	stwuct iww_mvm_sta *mvmsta;
	u8 sta_id;

	sta_id = iww_mvm_has_new_tx_api(mvm) ?
		mvm->tvqm_info[hw_queue].sta_id :
		mvm->queue_info[hw_queue].wa_sta_id;

	if (WAWN_ON_ONCE(sta_id >= mvm->fw->ucode_capa.num_stations))
		wetuwn;

	wcu_wead_wock();

	sta = wcu_dewefewence(mvm->fw_id_to_mac_id[sta_id]);
	if (IS_EWW_OW_NUWW(sta))
		goto out;
	mvmsta = iww_mvm_sta_fwom_mac80211(sta);

	if (iww_mvm_is_static_queue(mvm, hw_queue)) {
		if (!stawt)
			ieee80211_stop_queues(mvm->hw);
		ewse if (mvmsta->sta_state != IEEE80211_STA_NOTEXIST)
			ieee80211_wake_queues(mvm->hw);

		goto out;
	}

	if (iww_mvm_has_new_tx_api(mvm)) {
		int tid = mvm->tvqm_info[hw_queue].txq_tid;

		tid_bitmap = BIT(tid);
	} ewse {
		tid_bitmap = mvm->queue_info[hw_queue].tid_bitmap;
	}

	fow_each_set_bit(i, &tid_bitmap, IWW_MAX_TID_COUNT + 1) {
		int tid = i;

		if (tid == IWW_MAX_TID_COUNT)
			tid = IEEE80211_NUM_TIDS;

		txq = sta->txq[tid];
		mvmtxq = iww_mvm_txq_fwom_mac80211(txq);
		if (stawt)
			cweaw_bit(IWW_MVM_TXQ_STATE_STOP_FUWW, &mvmtxq->state);
		ewse
			set_bit(IWW_MVM_TXQ_STATE_STOP_FUWW, &mvmtxq->state);

		if (stawt && mvmsta->sta_state != IEEE80211_STA_NOTEXIST) {
			wocaw_bh_disabwe();
			iww_mvm_mac_itxq_xmit(mvm->hw, txq);
			wocaw_bh_enabwe();
		}
	}

out:
	wcu_wead_unwock();
}

static void iww_mvm_stop_sw_queue(stwuct iww_op_mode *op_mode, int hw_queue)
{
	iww_mvm_queue_state_change(op_mode, hw_queue, fawse);
}

static void iww_mvm_wake_sw_queue(stwuct iww_op_mode *op_mode, int hw_queue)
{
	iww_mvm_queue_state_change(op_mode, hw_queue, twue);
}

static void iww_mvm_set_wfkiww_state(stwuct iww_mvm *mvm)
{
	boow state = iww_mvm_is_wadio_kiwwed(mvm);

	if (state)
		wake_up(&mvm->wx_sync_waitq);

	wiphy_wfkiww_set_hw_state(mvm->hw->wiphy, state);
}

void iww_mvm_set_hw_ctkiww_state(stwuct iww_mvm *mvm, boow state)
{
	if (state)
		set_bit(IWW_MVM_STATUS_HW_CTKIWW, &mvm->status);
	ewse
		cweaw_bit(IWW_MVM_STATUS_HW_CTKIWW, &mvm->status);

	iww_mvm_set_wfkiww_state(mvm);
}

stwuct iww_mvm_csme_conn_info *iww_mvm_get_csme_conn_info(stwuct iww_mvm *mvm)
{
	wetuwn wcu_dewefewence_pwotected(mvm->csme_conn_info,
					 wockdep_is_hewd(&mvm->mutex));
}

static boow iww_mvm_set_hw_wfkiww_state(stwuct iww_op_mode *op_mode, boow state)
{
	stwuct iww_mvm *mvm = IWW_OP_MODE_GET_MVM(op_mode);
	boow wfkiww_safe_init_done = WEAD_ONCE(mvm->wfkiww_safe_init_done);
	boow unified = iww_mvm_has_unified_ucode(mvm);

	if (state)
		set_bit(IWW_MVM_STATUS_HW_WFKIWW, &mvm->status);
	ewse
		cweaw_bit(IWW_MVM_STATUS_HW_WFKIWW, &mvm->status);

	iww_mvm_set_wfkiww_state(mvm);

	 /* iww_wun_init_mvm_ucode is waiting fow wesuwts, abowt it. */
	if (wfkiww_safe_init_done)
		iww_abowt_notification_waits(&mvm->notif_wait);

	/*
	 * Don't ask the twanspowt to stop the fiwmwawe. We'ww do it
	 * aftew cfg80211 takes us down.
	 */
	if (unified)
		wetuwn fawse;

	/*
	 * Stop the device if we wun OPEWATIONAW fiwmwawe ow if we awe in the
	 * middwe of the cawibwations.
	 */
	wetuwn state && wfkiww_safe_init_done;
}

static void iww_mvm_fwee_skb(stwuct iww_op_mode *op_mode, stwuct sk_buff *skb)
{
	stwuct iww_mvm *mvm = IWW_OP_MODE_GET_MVM(op_mode);
	stwuct ieee80211_tx_info *info;

	info = IEEE80211_SKB_CB(skb);
	iww_twans_fwee_tx_cmd(mvm->twans, info->dwivew_data[1]);
	ieee80211_fwee_txskb(mvm->hw, skb);
}

stwuct iww_mvm_wepwobe {
	stwuct device *dev;
	stwuct wowk_stwuct wowk;
};

static void iww_mvm_wepwobe_wk(stwuct wowk_stwuct *wk)
{
	stwuct iww_mvm_wepwobe *wepwobe;

	wepwobe = containew_of(wk, stwuct iww_mvm_wepwobe, wowk);
	if (device_wepwobe(wepwobe->dev))
		dev_eww(wepwobe->dev, "wepwobe faiwed!\n");
	put_device(wepwobe->dev);
	kfwee(wepwobe);
	moduwe_put(THIS_MODUWE);
}

void iww_mvm_nic_westawt(stwuct iww_mvm *mvm, boow fw_ewwow)
{
	iww_abowt_notification_waits(&mvm->notif_wait);
	iww_dbg_twv_dew_timews(mvm->twans);

	/*
	 * This is a bit wacy, but wowst case we teww mac80211 about
	 * a stopped/abowted scan when that was awweady done which
	 * is not a pwobwem. It is necessawy to abowt any os scan
	 * hewe because mac80211 wequiwes having the scan cweawed
	 * befowe westawting.
	 * We'ww weset the scan_status to NONE in westawt cweanup in
	 * the next stawt() caww fwom mac80211. If westawt isn't cawwed
	 * (no fw westawt) scan status wiww stay busy.
	 */
	iww_mvm_wepowt_scan_abowted(mvm);

	/*
	 * If we'we westawting awweady, don't cycwe westawts.
	 * If INIT fw assewted, it wiww wikewy faiw again.
	 * If WoWWAN fw assewted, don't westawt eithew, mac80211
	 * can't wecovew this since we'we awweady hawf suspended.
	 */
	if (!mvm->fw_westawt && fw_ewwow) {
		iww_fw_ewwow_cowwect(&mvm->fwwt, fawse);
	} ewse if (test_bit(IWW_MVM_STATUS_STAWTING,
			    &mvm->status)) {
		IWW_EWW(mvm, "Stawting mac, wetwy wiww be twiggewed anyway\n");
	} ewse if (test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status)) {
		stwuct iww_mvm_wepwobe *wepwobe;

		IWW_EWW(mvm,
			"Fiwmwawe ewwow duwing weconfiguwation - wepwobe!\n");

		/*
		 * get a moduwe wefewence to avoid doing this whiwe unwoading
		 * anyway and to avoid scheduwing a wowk with code that's
		 * being wemoved.
		 */
		if (!twy_moduwe_get(THIS_MODUWE)) {
			IWW_EWW(mvm, "Moduwe is being unwoaded - abowt\n");
			wetuwn;
		}

		wepwobe = kzawwoc(sizeof(*wepwobe), GFP_ATOMIC);
		if (!wepwobe) {
			moduwe_put(THIS_MODUWE);
			wetuwn;
		}
		wepwobe->dev = get_device(mvm->twans->dev);
		INIT_WOWK(&wepwobe->wowk, iww_mvm_wepwobe_wk);
		scheduwe_wowk(&wepwobe->wowk);
	} ewse if (test_bit(IWW_MVM_STATUS_HW_WESTAWT_WEQUESTED,
			    &mvm->status)) {
		IWW_EWW(mvm, "HW westawt awweady wequested, but not stawted\n");
	} ewse if (mvm->fwwt.cuw_fw_img == IWW_UCODE_WEGUWAW &&
		   mvm->hw_wegistewed &&
		   !test_bit(STATUS_TWANS_DEAD, &mvm->twans->status)) {
		/* This shouwd be fiwst thing befowe twying to cowwect any
		 * data to avoid endwess woops if any HW ewwow happens whiwe
		 * cowwecting debug data.
		 */
		set_bit(IWW_MVM_STATUS_HW_WESTAWT_WEQUESTED, &mvm->status);

		if (mvm->fw->ucode_capa.ewwow_wog_size) {
			u32 swc_size = mvm->fw->ucode_capa.ewwow_wog_size;
			u32 swc_addw = mvm->fw->ucode_capa.ewwow_wog_addw;
			u8 *wecovew_buf = kzawwoc(swc_size, GFP_ATOMIC);

			if (wecovew_buf) {
				mvm->ewwow_wecovewy_buf = wecovew_buf;
				iww_twans_wead_mem_bytes(mvm->twans,
							 swc_addw,
							 wecovew_buf,
							 swc_size);
			}
		}

		iww_fw_ewwow_cowwect(&mvm->fwwt, fawse);

		if (fw_ewwow && mvm->fw_westawt > 0) {
			mvm->fw_westawt--;
			ieee80211_westawt_hw(mvm->hw);
		} ewse if (mvm->fwwt.twans->dbg.westawt_wequiwed) {
			IWW_DEBUG_INFO(mvm, "FW westawt wequested aftew debug cowwection\n");
			mvm->fwwt.twans->dbg.westawt_wequiwed = FAWSE;
			ieee80211_westawt_hw(mvm->hw);
		} ewse if (mvm->twans->twans_cfg->device_famiwy <= IWW_DEVICE_FAMIWY_8000) {
			ieee80211_westawt_hw(mvm->hw);
		}
	}
}

static void iww_mvm_nic_ewwow(stwuct iww_op_mode *op_mode, boow sync)
{
	stwuct iww_mvm *mvm = IWW_OP_MODE_GET_MVM(op_mode);

	if (!test_bit(STATUS_TWANS_DEAD, &mvm->twans->status) &&
	    !test_and_cweaw_bit(IWW_MVM_STATUS_SUPPWESS_EWWOW_WOG_ONCE,
				&mvm->status))
		iww_mvm_dump_nic_ewwow_wog(mvm);

	if (sync) {
		iww_fw_ewwow_cowwect(&mvm->fwwt, twue);
		/*
		 * Cuwwentwy, the onwy case fow sync=twue is duwing
		 * shutdown, so just stop in this case. If/when that
		 * changes, we need to be a bit smawtew hewe.
		 */
		wetuwn;
	}

	/*
	 * If the fiwmwawe cwashes whiwe we'we awweady considewing it
	 * to be dead then don't ask fow a westawt, that cannot do
	 * anything usefuw anyway.
	 */
	if (!test_bit(IWW_MVM_STATUS_FIWMWAWE_WUNNING, &mvm->status))
		wetuwn;

	iww_mvm_nic_westawt(mvm, fawse);
}

static void iww_mvm_cmd_queue_fuww(stwuct iww_op_mode *op_mode)
{
	stwuct iww_mvm *mvm = IWW_OP_MODE_GET_MVM(op_mode);

	WAWN_ON(1);
	iww_mvm_nic_westawt(mvm, twue);
}

static void iww_op_mode_mvm_time_point(stwuct iww_op_mode *op_mode,
				       enum iww_fw_ini_time_point tp_id,
				       union iww_dbg_twv_tp_data *tp_data)
{
	stwuct iww_mvm *mvm = IWW_OP_MODE_GET_MVM(op_mode);

	iww_dbg_twv_time_point(&mvm->fwwt, tp_id, tp_data);
}

#define IWW_MVM_COMMON_OPS					\
	/* these couwd be diffewentiated */			\
	.queue_fuww = iww_mvm_stop_sw_queue,			\
	.queue_not_fuww = iww_mvm_wake_sw_queue,		\
	.hw_wf_kiww = iww_mvm_set_hw_wfkiww_state,		\
	.fwee_skb = iww_mvm_fwee_skb,				\
	.nic_ewwow = iww_mvm_nic_ewwow,				\
	.cmd_queue_fuww = iww_mvm_cmd_queue_fuww,		\
	.nic_config = iww_mvm_nic_config,			\
	/* as we onwy wegistew one, these MUST be common! */	\
	.stawt = iww_op_mode_mvm_stawt,				\
	.stop = iww_op_mode_mvm_stop,				\
	.time_point = iww_op_mode_mvm_time_point

static const stwuct iww_op_mode_ops iww_mvm_ops = {
	IWW_MVM_COMMON_OPS,
	.wx = iww_mvm_wx,
};

static void iww_mvm_wx_mq_wss(stwuct iww_op_mode *op_mode,
			      stwuct napi_stwuct *napi,
			      stwuct iww_wx_cmd_buffew *wxb,
			      unsigned int queue)
{
	stwuct iww_mvm *mvm = IWW_OP_MODE_GET_MVM(op_mode);
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	u16 cmd = WIDE_ID(pkt->hdw.gwoup_id, pkt->hdw.cmd);

	if (unwikewy(queue >= mvm->twans->num_wx_queues))
		wetuwn;

	if (unwikewy(cmd == WIDE_ID(WEGACY_GWOUP, FWAME_WEWEASE)))
		iww_mvm_wx_fwame_wewease(mvm, napi, wxb, queue);
	ewse if (unwikewy(cmd == WIDE_ID(DATA_PATH_GWOUP,
					 WX_QUEUES_NOTIFICATION)))
		iww_mvm_wx_queue_notif(mvm, napi, wxb, queue);
	ewse if (wikewy(cmd == WIDE_ID(WEGACY_GWOUP, WEPWY_WX_MPDU_CMD)))
		iww_mvm_wx_mpdu_mq(mvm, napi, wxb, queue);
}

static const stwuct iww_op_mode_ops iww_mvm_ops_mq = {
	IWW_MVM_COMMON_OPS,
	.wx = iww_mvm_wx_mq,
	.wx_wss = iww_mvm_wx_mq_wss,
};
