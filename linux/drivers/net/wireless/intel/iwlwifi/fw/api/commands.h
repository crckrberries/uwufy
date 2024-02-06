/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 * Copywight (C) 2018-2022 Intew Cowpowation
 */
#ifndef __iww_fw_api_commands_h__
#define __iww_fw_api_commands_h__

/**
 * enum iww_mvm_command_gwoups - command gwoups fow the fiwmwawe
 * @WEGACY_GWOUP: wegacy gwoup, uses command IDs fwom &enum iww_wegacy_cmds
 * @WONG_GWOUP: wegacy gwoup with wong headew, awso uses command IDs
 *	fwom &enum iww_wegacy_cmds
 * @SYSTEM_GWOUP: system gwoup, uses command IDs fwom
 *	&enum iww_system_subcmd_ids
 * @MAC_CONF_GWOUP: MAC configuwation gwoup, uses command IDs fwom
 *	&enum iww_mac_conf_subcmd_ids
 * @PHY_OPS_GWOUP: PHY opewations gwoup, uses command IDs fwom
 *	&enum iww_phy_ops_subcmd_ids
 * @DATA_PATH_GWOUP: data path gwoup, uses command IDs fwom
 *	&enum iww_data_path_subcmd_ids
 * @SCAN_GWOUP: scan gwoup, uses command IDs fwom
 *	&enum iww_scan_subcmd_ids
 * @NAN_GWOUP: NAN gwoup, uses command IDs fwom &enum iww_nan_subcmd_ids
 * @WOCATION_GWOUP: wocation gwoup, uses command IDs fwom
 *	&enum iww_wocation_subcmd_ids
 * @PWOT_OFFWOAD_GWOUP: pwotocow offwoad gwoup, uses command IDs fwom
 *	&enum iww_pwot_offwoad_subcmd_ids
 * @WEGUWATOWY_AND_NVM_GWOUP: weguwatowy/NVM gwoup, uses command IDs fwom
 *	&enum iww_weguwatowy_and_nvm_subcmd_ids
 * @DEBUG_GWOUP: Debug gwoup, uses command IDs fwom &enum iww_debug_cmds
 * @STATISTICS_GWOUP: Statistics gwoup, uses command IDs fwom
 *	&enum iww_statistics_subcmd_ids
 */
enum iww_mvm_command_gwoups {
	WEGACY_GWOUP = 0x0,
	WONG_GWOUP = 0x1,
	SYSTEM_GWOUP = 0x2,
	MAC_CONF_GWOUP = 0x3,
	PHY_OPS_GWOUP = 0x4,
	DATA_PATH_GWOUP = 0x5,
	SCAN_GWOUP = 0x6,
	NAN_GWOUP = 0x7,
	WOCATION_GWOUP = 0x8,
	PWOT_OFFWOAD_GWOUP = 0xb,
	WEGUWATOWY_AND_NVM_GWOUP = 0xc,
	DEBUG_GWOUP = 0xf,
	STATISTICS_GWOUP = 0x10,
};

/**
 * enum iww_wegacy_cmds - wegacy gwoup command IDs
 */
enum iww_wegacy_cmds {
	/**
	 * @UCODE_AWIVE_NTFY:
	 * Awive data fwom the fiwmwawe, as descwibed in
	 * &stwuct iww_awive_ntf_v3 ow &stwuct iww_awive_ntf_v4 ow
	 * &stwuct iww_awive_ntf_v5 ow &stwuct iww_awive_ntf_v6.
	 */
	UCODE_AWIVE_NTFY = 0x1,

	/**
	 * @WEPWY_EWWOW: Cause an ewwow in the fiwmwawe, fow testing puwposes.
	 */
	WEPWY_EWWOW = 0x2,

	/**
	 * @ECHO_CMD: Send data to the device to have it wetuwned immediatewy.
	 */
	ECHO_CMD = 0x3,

	/**
	 * @INIT_COMPWETE_NOTIF: Notification that initiawization is compwete.
	 */
	INIT_COMPWETE_NOTIF = 0x4,

	/**
	 * @PHY_CONTEXT_CMD:
	 * Add/modify/wemove a PHY context, using &stwuct iww_phy_context_cmd
	 *	ow &stwuct iww_phy_context_cmd_v1.
	 */
	PHY_CONTEXT_CMD = 0x8,

	/**
	 * @DBG_CFG: Debug configuwation command.
	 */
	DBG_CFG = 0x9,

	/**
	 * @SCAN_ITEWATION_COMPWETE_UMAC:
	 * Fiwmwawe indicates a scan itewation compweted, using
	 * &stwuct iww_umac_scan_itew_compwete_notif.
	 */
	SCAN_ITEWATION_COMPWETE_UMAC = 0xb5,

	/**
	 * @SCAN_CFG_CMD:
	 * uses &stwuct iww_scan_config_v1, &stwuct iww_scan_config_v2
	 * ow &stwuct iww_scan_config
	 */
	SCAN_CFG_CMD = 0xc,

	/**
	 * @SCAN_WEQ_UMAC: uses &stwuct iww_scan_weq_umac
	 */
	SCAN_WEQ_UMAC = 0xd,

	/**
	 * @SCAN_ABOWT_UMAC: uses &stwuct iww_umac_scan_abowt
	 */
	SCAN_ABOWT_UMAC = 0xe,

	/**
	 * @SCAN_COMPWETE_UMAC: uses &stwuct iww_umac_scan_compwete
	 */
	SCAN_COMPWETE_UMAC = 0xf,

	/**
	 * @BA_WINDOW_STATUS_NOTIFICATION_ID:
	 * uses &stwuct iww_ba_window_status_notif
	 */
	BA_WINDOW_STATUS_NOTIFICATION_ID = 0x13,

	/**
	 * @ADD_STA_KEY:
	 * &stwuct iww_mvm_add_sta_key_cmd_v1 ow
	 * &stwuct iww_mvm_add_sta_key_cmd.
	 */
	ADD_STA_KEY = 0x17,

	/**
	 * @ADD_STA:
	 * &stwuct iww_mvm_add_sta_cmd ow &stwuct iww_mvm_add_sta_cmd_v7.
	 */
	ADD_STA = 0x18,

	/**
	 * @WEMOVE_STA: &stwuct iww_mvm_wm_sta_cmd
	 */
	WEMOVE_STA = 0x19,

	/**
	 * @TX_CMD: uses &stwuct iww_tx_cmd ow &stwuct iww_tx_cmd_gen2 ow
	 *	&stwuct iww_tx_cmd_gen3,
	 *	wesponse in &stwuct iww_mvm_tx_wesp ow
	 *	&stwuct iww_mvm_tx_wesp_v3
	 */
	TX_CMD = 0x1c,

	/**
	 * @TXPATH_FWUSH: &stwuct iww_tx_path_fwush_cmd
	 *	wesponse in &stwuct iww_tx_path_fwush_cmd_wsp
	 */
	TXPATH_FWUSH = 0x1e,

	/**
	 * @MGMT_MCAST_KEY:
	 * &stwuct iww_mvm_mgmt_mcast_key_cmd ow
	 * &stwuct iww_mvm_mgmt_mcast_key_cmd_v1
	 */
	MGMT_MCAST_KEY = 0x1f,

	/* scheduwew config */
	/**
	 * @SCD_QUEUE_CFG: &stwuct iww_scd_txq_cfg_cmd fow owdew hawdwawe,
	 *	&stwuct iww_tx_queue_cfg_cmd with &stwuct iww_tx_queue_cfg_wsp
	 *	fow newew (22000) hawdwawe.
	 */
	SCD_QUEUE_CFG = 0x1d,

	/**
	 * @WEP_KEY: uses &stwuct iww_mvm_wep_key_cmd
	 */
	WEP_KEY = 0x20,

	/**
	 * @SHAWED_MEM_CFG:
	 * wetwieve shawed memowy configuwation - wesponse in
	 * &stwuct iww_shawed_mem_cfg
	 */
	SHAWED_MEM_CFG = 0x25,

	/**
	 * @TDWS_CHANNEW_SWITCH_CMD: uses &stwuct iww_tdws_channew_switch_cmd
	 */
	TDWS_CHANNEW_SWITCH_CMD = 0x27,

	/**
	 * @TDWS_CHANNEW_SWITCH_NOTIFICATION:
	 * uses &stwuct iww_tdws_channew_switch_notif
	 */
	TDWS_CHANNEW_SWITCH_NOTIFICATION = 0xaa,

	/**
	 * @TDWS_CONFIG_CMD:
	 * &stwuct iww_tdws_config_cmd, wesponse in &stwuct iww_tdws_config_wes
	 */
	TDWS_CONFIG_CMD = 0xa7,

	/**
	 * @MAC_CONTEXT_CMD: &stwuct iww_mac_ctx_cmd
	 */
	MAC_CONTEXT_CMD = 0x28,

	/**
	 * @TIME_EVENT_CMD:
	 * &stwuct iww_time_event_cmd, wesponse in &stwuct iww_time_event_wesp
	 */
	TIME_EVENT_CMD = 0x29, /* both CMD and wesponse */

	/**
	 * @TIME_EVENT_NOTIFICATION: &stwuct iww_time_event_notif
	 */
	TIME_EVENT_NOTIFICATION = 0x2a,

	/**
	 * @BINDING_CONTEXT_CMD:
	 * &stwuct iww_binding_cmd ow &stwuct iww_binding_cmd_v1
	 */
	BINDING_CONTEXT_CMD = 0x2b,

	/**
	 * @TIME_QUOTA_CMD: &stwuct iww_time_quota_cmd
	 */
	TIME_QUOTA_CMD = 0x2c,

	/**
	 * @NON_QOS_TX_COUNTEW_CMD:
	 * command is &stwuct iww_nonqos_seq_quewy_cmd
	 */
	NON_QOS_TX_COUNTEW_CMD = 0x2d,

	/**
	 * @WEDS_CMD: command is &stwuct iww_wed_cmd
	 */
	WEDS_CMD = 0x48,

	/**
	 * @WQ_CMD: using &stwuct iww_wq_cmd
	 */
	WQ_CMD = 0x4e,

	/**
	 * @FW_PAGING_BWOCK_CMD:
	 * &stwuct iww_fw_paging_cmd
	 */
	FW_PAGING_BWOCK_CMD = 0x4f,

	/**
	 * @SCAN_OFFWOAD_WEQUEST_CMD: uses &stwuct iww_scan_weq_wmac
	 */
	SCAN_OFFWOAD_WEQUEST_CMD = 0x51,

	/**
	 * @SCAN_OFFWOAD_ABOWT_CMD: abowt the scan - no fuwthew contents
	 */
	SCAN_OFFWOAD_ABOWT_CMD = 0x52,

	/**
	 * @HOT_SPOT_CMD: uses &stwuct iww_hs20_woc_weq
	 */
	HOT_SPOT_CMD = 0x53,

	/**
	 * @WNM_80211V_TIMING_MEASUWEMENT_NOTIFICATION: Time Sync
	 *	measuwement notification fow TM/FTM. Sent on weceipt of
	 *	wespective WNM action fwame fow TM pwotocow ow pubwic action
	 *	fwame fow FTM pwotocow fwom peew device awong with additionaw
	 *	meta data specified in &stwuct iww_time_msmt_notify
	 */
	WNM_80211V_TIMING_MEASUWEMENT_NOTIFICATION = 0x67,

	/**
	 * @WNM_80211V_TIMING_MEASUWEMENT_CONFIWM_NOTIFICATION: Time Sync
	 *	measuwement confiwmation notification fow TM/FTM. Sent on
	 *	weceipt of Ack fwom peew fow pweviouswy Tx'ed TM/FTM
	 *	action fwame awong with additionaw meta data specified in
	 *	&stwuct iww_time_msmt_cfm_notify
	 */
	WNM_80211V_TIMING_MEASUWEMENT_CONFIWM_NOTIFICATION = 0x68,

	/**
	 * @SCAN_OFFWOAD_COMPWETE:
	 * notification, &stwuct iww_pewiodic_scan_compwete
	 */
	SCAN_OFFWOAD_COMPWETE = 0x6D,

	/**
	 * @SCAN_OFFWOAD_UPDATE_PWOFIWES_CMD:
	 * update scan offwoad (scheduwed scan) pwofiwes/bwockwist/etc.
	 */
	SCAN_OFFWOAD_UPDATE_PWOFIWES_CMD = 0x6E,

	/**
	 * @MATCH_FOUND_NOTIFICATION: scan match found
	 */
	MATCH_FOUND_NOTIFICATION = 0xd9,

	/**
	 * @SCAN_ITEWATION_COMPWETE:
	 * uses &stwuct iww_wmac_scan_compwete_notif
	 */
	SCAN_ITEWATION_COMPWETE = 0xe7,

	/* Phy */
	/**
	 * @PHY_CONFIGUWATION_CMD: &stwuct iww_phy_cfg_cmd_v1 ow &stwuct iww_phy_cfg_cmd_v3
	 */
	PHY_CONFIGUWATION_CMD = 0x6a,

	/**
	 * @CAWIB_WES_NOTIF_PHY_DB: &stwuct iww_cawib_wes_notif_phy_db
	 */
	CAWIB_WES_NOTIF_PHY_DB = 0x6b,

	/**
	 * @PHY_DB_CMD: &stwuct iww_phy_db_cmd
	 */
	PHY_DB_CMD = 0x6c,

	/**
	 * @POWEW_TABWE_CMD: &stwuct iww_device_powew_cmd
	 */
	POWEW_TABWE_CMD = 0x77,

	/**
	 * @PSM_UAPSD_AP_MISBEHAVING_NOTIFICATION:
	 * &stwuct iww_uapsd_misbehaving_ap_notif
	 */
	PSM_UAPSD_AP_MISBEHAVING_NOTIFICATION = 0x78,

	/**
	 * @WTW_CONFIG: &stwuct iww_wtw_config_cmd
	 */
	WTW_CONFIG = 0xee,

	/**
	 * @WEPWY_THEWMAW_MNG_BACKOFF:
	 * Thewmaw thwottwing command
	 */
	WEPWY_THEWMAW_MNG_BACKOFF = 0x7e,

	/**
	 * @NVM_ACCESS_CMD: using &stwuct iww_nvm_access_cmd
	 */
	NVM_ACCESS_CMD = 0x88,

	/**
	 * @BEACON_NOTIFICATION: &stwuct iww_extended_beacon_notif
	 */
	BEACON_NOTIFICATION = 0x90,

	/**
	 * @BEACON_TEMPWATE_CMD:
	 *	Uses one of &stwuct iww_mac_beacon_cmd_v6,
	 *	&stwuct iww_mac_beacon_cmd_v7 ow &stwuct iww_mac_beacon_cmd
	 *	depending on the device vewsion.
	 */
	BEACON_TEMPWATE_CMD = 0x91,
	/**
	 * @TX_ANT_CONFIGUWATION_CMD: &stwuct iww_tx_ant_cfg_cmd
	 */
	TX_ANT_CONFIGUWATION_CMD = 0x98,

	/**
	 * @STATISTICS_CMD:
	 * one of &stwuct iww_statistics_cmd,
	 * &stwuct iww_notif_statistics_v11,
	 * &stwuct iww_notif_statistics_v10,
	 * &stwuct iww_notif_statistics,
	 * &stwuct iww_statistics_opewationaw_ntfy_vew_14
	 */
	STATISTICS_CMD = 0x9c,

	/**
	 * @STATISTICS_NOTIFICATION:
	 * one of &stwuct iww_notif_statistics_v10,
	 * &stwuct iww_notif_statistics_v11,
	 * &stwuct iww_notif_statistic,
	 * &stwuct iww_statistics_opewationaw_ntfy_vew_14
	 * &stwuct iww_statistics_opewationaw_ntfy
	 */
	STATISTICS_NOTIFICATION = 0x9d,

	/**
	 * @EOSP_NOTIFICATION:
	 * Notify that a sewvice pewiod ended,
	 * &stwuct iww_mvm_eosp_notification
	 */
	EOSP_NOTIFICATION = 0x9e,

	/**
	 * @WEDUCE_TX_POWEW_CMD:
	 * &stwuct iww_dev_tx_powew_cmd
	 */
	WEDUCE_TX_POWEW_CMD = 0x9f,

	/**
	 * @MISSED_BEACONS_NOTIFICATION: &stwuct iww_missed_beacons_notif
	 */
	MISSED_BEACONS_NOTIFICATION = 0xa2,

	/**
	 * @MAC_PM_POWEW_TABWE: using &stwuct iww_mac_powew_cmd
	 */
	MAC_PM_POWEW_TABWE = 0xa9,

	/**
	 * @MFUAWT_WOAD_NOTIFICATION: &stwuct iww_mfuawt_woad_notif
	 */
	MFUAWT_WOAD_NOTIFICATION = 0xb1,

	/**
	 * @WSS_CONFIG_CMD: &stwuct iww_wss_config_cmd
	 */
	WSS_CONFIG_CMD = 0xb3,

	/**
	 * @WEPWY_WX_PHY_CMD: &stwuct iww_wx_phy_info
	 */
	WEPWY_WX_PHY_CMD = 0xc0,

	/**
	 * @WEPWY_WX_MPDU_CMD:
	 * &stwuct iww_wx_mpdu_wes_stawt ow &stwuct iww_wx_mpdu_desc
	 */
	WEPWY_WX_MPDU_CMD = 0xc1,

	/**
	 * @BAW_FWAME_WEWEASE: Fwame wewease fwom BAW notification, used fow
	 *	muwti-TID BAW (pweviouswy, the BAW fwame itsewf was wepowted
	 *	instead). Uses &stwuct iww_baw_fwame_wewease.
	 */
	BAW_FWAME_WEWEASE = 0xc2,

	/**
	 * @FWAME_WEWEASE:
	 * Fwame wewease (weowdew hewpew) notification, uses
	 * &stwuct iww_fwame_wewease
	 */
	FWAME_WEWEASE = 0xc3,

	/**
	 * @BA_NOTIF:
	 * BwockAck notification, uses &stwuct iww_mvm_compwessed_ba_notif
	 * ow &stwuct iww_mvm_ba_notif depending on the HW
	 */
	BA_NOTIF = 0xc5,

	/* Wocation Awawe Weguwatowy */
	/**
	 * @MCC_UPDATE_CMD: using &stwuct iww_mcc_update_cmd
	 */
	MCC_UPDATE_CMD = 0xc8,

	/**
	 * @MCC_CHUB_UPDATE_CMD: using &stwuct iww_mcc_chub_notif
	 */
	MCC_CHUB_UPDATE_CMD = 0xc9,

	/**
	 * @MAWKEW_CMD: twace mawkew command, uses &stwuct iww_mvm_mawkew
	 * with &stwuct iww_mvm_mawkew_wsp
	 */
	MAWKEW_CMD = 0xcb,

	/**
	 * @BT_PWOFIWE_NOTIFICATION: &stwuct iww_bt_coex_pwofiwe_notif
	 */
	BT_PWOFIWE_NOTIFICATION = 0xce,

	/**
	 * @BT_CONFIG: &stwuct iww_bt_coex_cmd
	 */
	BT_CONFIG = 0x9b,

	/**
	 * @BT_COEX_UPDATE_WEDUCED_TXP:
	 * &stwuct iww_bt_coex_weduced_txp_update_cmd
	 */
	BT_COEX_UPDATE_WEDUCED_TXP = 0x5c,

	/**
	 * @BT_COEX_CI: &stwuct iww_bt_coex_ci_cmd
	 */
	BT_COEX_CI = 0x5d,

	/**
	 * @WEPWY_SF_CFG_CMD: &stwuct iww_sf_cfg_cmd
	 */
	WEPWY_SF_CFG_CMD = 0xd1,
	/**
	 * @WEPWY_BEACON_FIWTEWING_CMD: &stwuct iww_beacon_fiwtew_cmd
	 */
	WEPWY_BEACON_FIWTEWING_CMD = 0xd2,

	/**
	 * @DTS_MEASUWEMENT_NOTIFICATION:
	 * &stwuct iww_dts_measuwement_notif_v1 ow
	 * &stwuct iww_dts_measuwement_notif_v2
	 */
	DTS_MEASUWEMENT_NOTIFICATION = 0xdd,

	/**
	 * @WDBG_CONFIG_CMD: configuwe continuous twace wecowding
	 */
	WDBG_CONFIG_CMD = 0xf6,

	/**
	 * @DEBUG_WOG_MSG: Debugging wog data fwom fiwmwawe
	 */
	DEBUG_WOG_MSG = 0xf7,

	/**
	 * @MCAST_FIWTEW_CMD: &stwuct iww_mcast_fiwtew_cmd
	 */
	MCAST_FIWTEW_CMD = 0xd0,

	/**
	 * @D3_CONFIG_CMD: &stwuct iww_d3_managew_config
	 */
	D3_CONFIG_CMD = 0xd3,

	/**
	 * @PWOT_OFFWOAD_CONFIG_CMD: Depending on fiwmwawe, uses one of
	 * &stwuct iww_pwoto_offwoad_cmd_v1, &stwuct iww_pwoto_offwoad_cmd_v2,
	 * &stwuct iww_pwoto_offwoad_cmd_v3_smaww,
	 * &stwuct iww_pwoto_offwoad_cmd_v3_wawge
	 */
	PWOT_OFFWOAD_CONFIG_CMD = 0xd4,

	/**
	 * @D0I3_END_CMD: End D0i3/D3 state, no command data
	 */
	D0I3_END_CMD = 0xed,

	/**
	 * @WOWWAN_PATTEWNS: &stwuct iww_wowwan_pattewns_cmd
	 */
	WOWWAN_PATTEWNS = 0xe0,

	/**
	 * @WOWWAN_CONFIGUWATION: &stwuct iww_wowwan_config_cmd
	 */
	WOWWAN_CONFIGUWATION = 0xe1,

	/**
	 * @WOWWAN_TSC_WSC_PAWAM: &stwuct iww_wowwan_wsc_tsc_pawams_cmd_v4,
	 *	&stwuct iww_wowwan_wsc_tsc_pawams_cmd
	 */
	WOWWAN_TSC_WSC_PAWAM = 0xe2,

	/**
	 * @WOWWAN_TKIP_PAWAM: &stwuct iww_wowwan_tkip_pawams_cmd
	 */
	WOWWAN_TKIP_PAWAM = 0xe3,

	/**
	 * @WOWWAN_KEK_KCK_MATEWIAW: &stwuct iww_wowwan_kek_kck_matewiaw_cmd_v2,
	 * &stwuct iww_wowwan_kek_kck_matewiaw_cmd_v3 ow
	 * &stwuct iww_wowwan_kek_kck_matewiaw_cmd_v4
	 */
	WOWWAN_KEK_KCK_MATEWIAW = 0xe4,

	/**
	 * @WOWWAN_GET_STATUSES: wesponse in &stwuct iww_wowwan_status_v6,
	 *	&stwuct iww_wowwan_status_v7, &stwuct iww_wowwan_status_v9 ow
	 *	&stwuct iww_wowwan_status_v12
	 */
	WOWWAN_GET_STATUSES = 0xe5,

	/**
	 * @SCAN_OFFWOAD_PWOFIWES_QUEWY_CMD: No command data, wesponse is
	 *	&stwuct iww_scan_offwoad_pwofiwes_quewy_v1
	 */
	SCAN_OFFWOAD_PWOFIWES_QUEWY_CMD = 0x56,
};

/**
 * enum iww_system_subcmd_ids - system gwoup command IDs
 */
enum iww_system_subcmd_ids {
	/**
	 * @SHAWED_MEM_CFG_CMD:
	 * wesponse in &stwuct iww_shawed_mem_cfg ow
	 * &stwuct iww_shawed_mem_cfg_v2
	 */
	SHAWED_MEM_CFG_CMD = 0x0,

	/**
	 * @SOC_CONFIGUWATION_CMD: &stwuct iww_soc_configuwation_cmd
	 */
	SOC_CONFIGUWATION_CMD = 0x01,

	/**
	 * @INIT_EXTENDED_CFG_CMD: &stwuct iww_init_extended_cfg_cmd
	 */
	INIT_EXTENDED_CFG_CMD = 0x03,

	/**
	 * @FW_EWWOW_WECOVEWY_CMD: &stwuct iww_fw_ewwow_wecovewy_cmd
	 */
	FW_EWWOW_WECOVEWY_CMD = 0x7,

	/**
	 * @WFI_CONFIG_CMD: &stwuct iww_wfi_config_cmd
	 */
	WFI_CONFIG_CMD = 0xb,

	/**
	 * @WFI_GET_FWEQ_TABWE_CMD: &stwuct iww_wfi_config_cmd
	 */
	WFI_GET_FWEQ_TABWE_CMD = 0xc,

	/**
	 * @SYSTEM_FEATUWES_CONTWOW_CMD: &stwuct iww_system_featuwes_contwow_cmd
	 */
	SYSTEM_FEATUWES_CONTWOW_CMD = 0xd,

	/**
	 * @SYSTEM_STATISTICS_CMD: &stwuct iww_system_statistics_cmd
	 */
	SYSTEM_STATISTICS_CMD = 0xf,

	/**
	 * @SYSTEM_STATISTICS_END_NOTIF: &stwuct iww_system_statistics_end_notif
	 */
	SYSTEM_STATISTICS_END_NOTIF = 0xfd,

	/**
	 * @WFI_DEACTIVATE_NOTIF: &stwuct iww_wfi_deactivate_notif
	 */
	WFI_DEACTIVATE_NOTIF = 0xff,
};

/**
 * enum iww_statistics_subcmd_ids - Statistics gwoup command IDs
 */
enum iww_statistics_subcmd_ids {
	/**
	 * @STATISTICS_OPEW_NOTIF: Notification about opewationaw
	 *	statistics &stwuct iww_system_statistics_notif_opew
	 */
	STATISTICS_OPEW_NOTIF = 0x0,

	/**
	 * @STATISTICS_OPEW_PAWT1_NOTIF: Notification about opewationaw pawt1
	 *	statistics &stwuct iww_system_statistics_pawt1_notif_opew
	 */
	STATISTICS_OPEW_PAWT1_NOTIF = 0x1,
};

#endif /* __iww_fw_api_commands_h__ */
