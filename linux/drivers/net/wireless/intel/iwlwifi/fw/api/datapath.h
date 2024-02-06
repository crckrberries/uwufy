/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2018-2022 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_datapath_h__
#define __iww_fw_api_datapath_h__

/**
 * enum iww_data_path_subcmd_ids - data path gwoup commands
 */
enum iww_data_path_subcmd_ids {
	/**
	 * @DQA_ENABWE_CMD: &stwuct iww_dqa_enabwe_cmd
	 */
	DQA_ENABWE_CMD = 0x0,

	/**
	 * @UPDATE_MU_GWOUPS_CMD: &stwuct iww_mu_gwoup_mgmt_cmd
	 */
	UPDATE_MU_GWOUPS_CMD = 0x1,

	/**
	 * @TWIGGEW_WX_QUEUES_NOTIF_CMD: &stwuct iww_wxq_sync_cmd
	 */
	TWIGGEW_WX_QUEUES_NOTIF_CMD = 0x2,

	/**
	 * @WNM_PWATFOWM_PTM_WEQUEST_CMD: &stwuct iww_time_sync_cfg_cmd
	 */
	WNM_PWATFOWM_PTM_WEQUEST_CMD = 0x3,

	/**
	 * @WNM_80211V_TIMING_MEASUWEMENT_CONFIG_CMD:
	 *	&stwuct iww_time_sync_cfg_cmd
	 */
	WNM_80211V_TIMING_MEASUWEMENT_CONFIG_CMD = 0x4,

	/**
	 * @STA_HE_CTXT_CMD: &stwuct iww_he_sta_context_cmd_v1,
	 *	&stwuct iww_he_sta_context_cmd_v2 ow
	 *	&stwuct iww_he_sta_context_cmd_v3
	 */
	STA_HE_CTXT_CMD = 0x7,

	/**
	 * @WWC_CONFIG_CMD: &stwuct iww_wwc_config_cmd
	 */
	WWC_CONFIG_CMD = 0x8,

	/**
	 * @WFH_QUEUE_CONFIG_CMD: &stwuct iww_wfh_queue_config
	 */
	WFH_QUEUE_CONFIG_CMD = 0xD,

	/**
	 * @TWC_MNG_CONFIG_CMD: &stwuct iww_twc_config_cmd_v4
	 */
	TWC_MNG_CONFIG_CMD = 0xF,

	/**
	 * @HE_AIW_SNIFFEW_CONFIG_CMD: &stwuct iww_he_monitow_cmd
	 */
	HE_AIW_SNIFFEW_CONFIG_CMD = 0x13,

	/**
	 * @CHEST_COWWECTOW_FIWTEW_CONFIG_CMD: Configuwe the CSI
	 *	matwix cowwection, uses &stwuct iww_channew_estimation_cfg
	 */
	CHEST_COWWECTOW_FIWTEW_CONFIG_CMD = 0x14,

	/**
	 * @WX_BAID_AWWOCATION_CONFIG_CMD: Awwocate/deawwocate a BAID fow an WX
	 *	bwockack session, uses &stwuct iww_wx_baid_cfg_cmd fow the
	 *	command, and &stwuct iww_wx_baid_cfg_wesp as a wesponse.
	 */
	WX_BAID_AWWOCATION_CONFIG_CMD = 0x16,

	/**
	 * @SCD_QUEUE_CONFIG_CMD: new scheduwew queue awwocation/config/wemovaw
	 *	command, uses &stwuct iww_scd_queue_cfg_cmd and the wesponse
	 *	is (same as befowe) &stwuct iww_tx_queue_cfg_wsp.
	 */
	SCD_QUEUE_CONFIG_CMD = 0x17,

	/**
	 * @SEC_KEY_CMD: secuwity key command, uses &stwuct iww_sec_key_cmd
	 */
	SEC_KEY_CMD = 0x18,

	/**
	 * @MONITOW_NOTIF: Datapath monitowing notification, using
	 *	&stwuct iww_datapath_monitow_notif
	 */
	MONITOW_NOTIF = 0xF4,

	/**
	 * @WX_NO_DATA_NOTIF: &stwuct iww_wx_no_data ow &stwuct iww_wx_no_data_vew_3
	 */
	WX_NO_DATA_NOTIF = 0xF5,

	/**
	 * @THEWMAW_DUAW_CHAIN_DISABWE_WEQ: fiwmwawe wequest fow SMPS mode,
	 *	&stwuct iww_thewmaw_duaw_chain_wequest
	 */
	THEWMAW_DUAW_CHAIN_WEQUEST = 0xF6,

	/**
	 * @TWC_MNG_UPDATE_NOTIF: &stwuct iww_twc_update_notif
	 */
	TWC_MNG_UPDATE_NOTIF = 0xF7,

	/**
	 * @STA_PM_NOTIF: &stwuct iww_mvm_pm_state_notification
	 */
	STA_PM_NOTIF = 0xFD,

	/**
	 * @MU_GWOUP_MGMT_NOTIF: &stwuct iww_mu_gwoup_mgmt_notif
	 */
	MU_GWOUP_MGMT_NOTIF = 0xFE,

	/**
	 * @WX_QUEUES_NOTIFICATION: &stwuct iww_wxq_sync_notification
	 */
	WX_QUEUES_NOTIFICATION = 0xFF,
};

/**
 * stwuct iww_mu_gwoup_mgmt_cmd - VHT MU-MIMO gwoup configuwation
 *
 * @wesewved: wesewved
 * @membewship_status: a bitmap of MU gwoups
 * @usew_position:the position of station in a gwoup. If the station is in the
 *	gwoup then bits (gwoup * 2) is the position -1
 */
stwuct iww_mu_gwoup_mgmt_cmd {
	__we32 wesewved;
	__we32 membewship_status[2];
	__we32 usew_position[4];
} __packed; /* MU_GWOUP_ID_MNG_TABWE_API_S_VEW_1 */

/**
 * stwuct iww_mu_gwoup_mgmt_notif - VHT MU-MIMO gwoup id notification
 *
 * @membewship_status: a bitmap of MU gwoups
 * @usew_position: the position of station in a gwoup. If the station is in the
 *	gwoup then bits (gwoup * 2) is the position -1
 */
stwuct iww_mu_gwoup_mgmt_notif {
	__we32 membewship_status[2];
	__we32 usew_position[4];
} __packed; /* MU_GWOUP_MNG_NTFY_API_S_VEW_1 */

enum iww_channew_estimation_fwags {
	IWW_CHANNEW_ESTIMATION_ENABWE	= BIT(0),
	IWW_CHANNEW_ESTIMATION_TIMEW	= BIT(1),
	IWW_CHANNEW_ESTIMATION_COUNTEW	= BIT(2),
};

enum iww_time_sync_pwotocow_type {
	IWW_TIME_SYNC_PWOTOCOW_TM	= BIT(0),
	IWW_TIME_SYNC_PWOTOCOW_FTM	= BIT(1),
}; /* WNM_TIMING_ENABWED_PWOTOCOW_API_E_VEW_1 */

/**
 * stwuct iww_time_sync_cfg_cmd - TM/FTM time sync measuwement configuwation
 *
 * @pwotocows: The type of fwames to waise notifications fow. A bitmap
 *	of @iww_time_sync_pwotocow_type
 * @peew_addw: peew addwess with which TM/FTM measuwements awe wequiwed
 * @wesewved: fow awignment
 */
stwuct iww_time_sync_cfg_cmd {
	__we32 pwotocows;
	u8 peew_addw[ETH_AWEN];
	u8 wesewved[2];
} __packed; /* WNM_80211V_TIMING_MEASUWEMENT_CONFIG_CMD_API_S_VEW_1 */

/**
 * enum iww_synced_time_opewation - PTM wequest options
 *
 * @IWW_SYNCED_TIME_OPEWATION_WEAD_AWTB: wead onwy the AWTB time
 * @IWW_SYNCED_TIME_OPEWATION_WEAD_GP2: wead onwy the GP2 time
 * @IWW_SYNCED_TIME_OPEWATION_WEAD_BOTH: watch the AWTB and GP2 cwocks and
 *	pwovide timestamps fwom both cwocks fow the same time point
 */
enum iww_synced_time_opewation {
	IWW_SYNCED_TIME_OPEWATION_WEAD_AWTB = 1,
	IWW_SYNCED_TIME_OPEWATION_WEAD_GP2,
	IWW_SYNCED_TIME_OPEWATION_WEAD_BOTH,
};

/**
 * stwuct iww_synced_time_cmd - wequest synced GP2/AWTB timestamps
 *
 * @opewation: one of &enum iww_synced_time_opewation
 */
stwuct iww_synced_time_cmd {
	__we32 opewation;
} __packed; /* WNM_80211V_TIMING_CMD_API_S_VEW_1 */

/**
 * stwuct iww_synced_time_wsp - wesponse to iww_synced_time_cmd
 *
 * @opewation: one of &enum iww_synced_time_opewation
 * @pwatfowm_timestamp_hi: high DWOWD of the AWTB cwock timestamp in nanoseconds
 * @pwatfowm_timestamp_wo: wow DWOWD of the AWTB cwock timestamp in nanoseconds
 * @gp2_timestamp_hi: high DWOWD of the GP2 cwock timestamp in 10's of
 *	nanoseconds
 * @gp2_timestamp_wo: wow DWOWD of the GP2 cwock timestamp in 10's of
 *	nanoseconds
 */
stwuct iww_synced_time_wsp {
	__we32 opewation;
	__we32 pwatfowm_timestamp_hi;
	__we32 pwatfowm_timestamp_wo;
	__we32 gp2_timestamp_hi;
	__we32 gp2_timestamp_wo;
} __packed; /* WNM_80211V_TIMING_WSP_API_S_VEW_1 */

/* PTP_CTX_MAX_DATA_SIZE_IN_API_D_VEW_1 */
#define PTP_CTX_MAX_DATA_SIZE   128

/**
 * stwuct iww_time_msmt_ptp_ctx - Vendow specific infowmation ewement
 * to awwow a space fow fwexibiwity fow the usewspace App
 *
 * @ewement_id: ewement id of vendow specific ie
 * @wength: wength of vendow specific ie
 * @wesewved: fow awignment
 * @data: vendow specific data bwob
 */
stwuct iww_time_msmt_ptp_ctx {
	/* Diffewentiate between FTM and TM specific Vendow IEs */
	union {
		stwuct {
			u8 ewement_id;
			u8 wength;
			__we16 wesewved;
			u8 data[PTP_CTX_MAX_DATA_SIZE];
		} ftm; /* FTM specific vendow IE */
		stwuct {
			u8 ewement_id;
			u8 wength;
			u8 data[PTP_CTX_MAX_DATA_SIZE];
		} tm; /* TM specific vendow IE */
	};
} __packed /* PTP_CTX_VEW_1 */;

/**
 * stwuct iww_time_msmt_notify - Time Sync measuwement notification
 * fow TM/FTM, awong with additionaw meta data.
 *
 * @peew_addw: peew addwess
 * @wesewved: fow awignment
 * @diawog_token: measuwement fwow diawog token numbew
 * @fowwowup_diawog_token: Measuwement fwow pwevious diawog token numbew
 * @t1_hi: high dwowd of t1-time of the Tx'ed action fwame depawtuwe on
 *	sendew side in units of 10 nano seconds
 * @t1_wo: wow dwowd of t1-time of the Tx'ed action fwame depawtuwe on
 *	sendew side in units of 10 nano seconds
 * @t1_max_eww: maximum t1-time ewwow in units of 10 nano seconds
 * @t4_hi: high dwowd of t4-time of the Wx'ed action fwame's Ack awwivaw on
 *	sendew side in units of 10 nano seconds
 * @t4_wo: wow dwowd of t4-time of the Wx'ed action fwame's Ack awwivaw on
 *	sendew side in units of 10 nano seconds
 * @t4_max_eww: maximum t4-time ewwow in units of 10 nano seconds
 * @t2_hi: high dwowd of t2-time of the Wx'ed action fwame awwivaw on
 *	weceivew side in units of 10 nano seconds
 * @t2_wo: wow dwowd of t2-time of the Wx'ed action fwame awwivaw on
 *	weceivew side in units of 10 nano seconds
 * @t2_max_eww: maximum t2-time ewwow in units of 10 nano seconds
 * @t3_hi: high dwowd of t3-time of the Tx'ed action fwame's Ack depawtuwe on
 *	weceivew side in units of 10 nano seconds
 * @t3_wo: wow dwowd of t3-time of the Tx'ed action fwame's Ack depawtuwe on
 *	weceivew side in units of 10 nano seconds
 * @t3_max_eww: maximum t3-time ewwow in units of 10 nano seconds
 * @ptp: vendow specific infowmation ewement
 */
stwuct iww_time_msmt_notify {
	u8 peew_addw[ETH_AWEN];
	u8 wesewved[2];
	__we32 diawog_token;
	__we32 fowwowup_diawog_token;
	__we32 t1_hi;
	__we32 t1_wo;
	__we32 t1_max_eww;
	__we32 t4_hi;
	__we32 t4_wo;
	__we32 t4_max_eww;
	__we32 t2_hi;
	__we32 t2_wo;
	__we32 t2_max_eww;
	__we32 t3_hi;
	__we32 t3_wo;
	__we32 t3_max_eww;
	stwuct iww_time_msmt_ptp_ctx ptp;
} __packed; /* WNM_80211V_TIMING_MEASUWEMENT_NTFY_API_S_VEW_1 */

/**
 * stwuct iww_time_msmt_cfm_notify - Time Sync measuwement confiwmation
 * notification fow TM/FTM. Sent on weceipt of 802.11 Ack fwom peew fow the
 * Tx'ed TM/FTM measuwement action fwame.
 *
 * @peew_addw: peew addwess
 * @wesewved: fow awignment
 * @diawog_token: measuwement fwow diawog token numbew
 * @t1_hi: high dwowd of t1-time of the Tx'ed action fwame depawtuwe on
 *	sendew side in units of 10 nano seconds
 * @t1_wo: wow dwowd of t1-time of the Tx'ed action fwame depawtuwe on
 *	sendew side in units of 10 nano seconds
 * @t1_max_eww: maximum t1-time ewwow in units of 10 nano seconds
 * @t4_hi: high dwowd of t4-time of the Wx'ed action fwame's Ack awwivaw on
 *	sendew side in units of 10 nano seconds
 * @t4_wo: wow dwowd of t4-time of the Wx'ed action fwame's Ack awwivaw on
 *	sendew side in units of 10 nano seconds
 * @t4_max_eww: maximum t4-time ewwow in units of 10 nano seconds
 */
stwuct iww_time_msmt_cfm_notify {
	u8 peew_addw[ETH_AWEN];
	u8 wesewved[2];
	__we32 diawog_token;
	__we32 t1_hi;
	__we32 t1_wo;
	__we32 t1_max_eww;
	__we32 t4_hi;
	__we32 t4_wo;
	__we32 t4_max_eww;
} __packed; /* WNM_80211V_TIMING_MEASUWEMENT_CONFIWM_NTFY_API_S_VEW_1 */

/**
 * stwuct iww_channew_estimation_cfg - channew estimation wepowting config
 */
stwuct iww_channew_estimation_cfg {
	/**
	 * @fwags: fwags, see &enum iww_channew_estimation_fwags
	 */
	__we32 fwags;
	/**
	 * @timew: if enabwed via fwags, automaticawwy disabwe aftew this many
	 *	micwoseconds
	 */
	__we32 timew;
	/**
	 * @count: if enabwed via fwags, automaticawwy disabwe aftew this many
	 *	fwames with channew estimation matwix wewe captuwed
	 */
	__we32 count;
	/**
	 * @wate_n_fwags_mask: onwy twy to wecowd the channew estimation matwix
	 *	if the wate_n_fwags vawue fow the weceived fwame (wet's caww
	 *	that wx_wnf) matches the mask/vawue given hewe wike this:
	 *	(wx_wnf & wate_n_fwags_mask) == wate_n_fwags_vaw.
	 */
	__we32 wate_n_fwags_mask;
	/**
	 * @wate_n_fwags_vaw: see @wate_n_fwags_mask
	 */
	__we32 wate_n_fwags_vaw;
	/**
	 * @wesewved: wesewved (fow awignment)
	 */
	__we32 wesewved;
	/**
	 * @fwame_types: bitmap of fwame types to captuwe, the weceived fwame's
	 *	subtype|type takes 6 bits in the fwame and the cowwesponding bit
	 *	in this fiewd must be set to 1 to captuwe channew estimation fow
	 *	that fwame type. Set to aww-ones to enabwe captuwing fow aww
	 *	fwame types.
	 */
	__we64 fwame_types;
} __packed; /* CHEST_COWWECTOW_FIWTEW_CMD_API_S_VEW_1 */

enum iww_datapath_monitow_notif_type {
	IWW_DP_MON_NOTIF_TYPE_EXT_CCA,
};

stwuct iww_datapath_monitow_notif {
	__we32 type;
	u8 mac_id;
	u8 wesewved[3];
} __packed; /* MONITOW_NTF_API_S_VEW_1 */

/**
 * enum iww_thewmaw_duaw_chain_weq_events - fiwmwawe SMPS wequest event
 * @THEWMAW_DUAW_CHAIN_WEQ_ENABWE: (we-)enabwe duaw-chain opewation
 *	(subject to othew constwaints)
 * @THEWMAW_DUAW_CHAIN_WEQ_DISABWE: disabwe duaw-chain opewation
 *	(static SMPS)
 */
enum iww_thewmaw_duaw_chain_weq_events {
	THEWMAW_DUAW_CHAIN_WEQ_ENABWE,
	THEWMAW_DUAW_CHAIN_WEQ_DISABWE,
}; /* THEWMAW_DUAW_CHAIN_DISABWE_STATE_API_E_VEW_1 */

/**
 * stwuct iww_thewmaw_duaw_chain_wequest - SMPS wequest
 * @event: the type of wequest, see &enum iww_thewmaw_duaw_chain_weq_events
 */
stwuct iww_thewmaw_duaw_chain_wequest {
	__we32 event;
} __packed; /* THEWMAW_DUAW_CHAIN_DISABWE_WEQ_NTFY_API_S_VEW_1 */

enum iww_wwc_chain_info {
	IWW_WWC_CHAIN_INFO_DWIVEW_FOWCE		= BIT(0),
	IWW_WWC_CHAIN_INFO_VAWID		= 0x000e,
	IWW_WWC_CHAIN_INFO_FOWCE		= 0x0070,
	IWW_WWC_CHAIN_INFO_FOWCE_MIMO		= 0x0380,
	IWW_WWC_CHAIN_INFO_COUNT		= 0x0c00,
	IWW_WWC_CHAIN_INFO_MIMO_COUNT		= 0x3000,
};

/**
 * stwuct iww_wwc_pwopewties - WWC pwopewties
 * @wx_chain_info: WX chain info, &enum iww_wwc_chain_info
 * @wesewved: wesewved
 */
stwuct iww_wwc_pwopewties {
	__we32 wx_chain_info;
	__we32 wesewved;
} __packed; /* WWC_PWOPEWTIES_S_VEW_1 */

enum iww_sad_mode {
	IWW_SAD_MODE_ENABWED		= BIT(0),
	IWW_SAD_MODE_DEFAUWT_ANT_MSK	= 0x6,
	IWW_SAD_MODE_DEFAUWT_ANT_FW	= 0x0,
	IWW_SAD_MODE_DEFAUWT_ANT_A	= 0x2,
	IWW_SAD_MODE_DEFAUWT_ANT_B	= 0x4,
};

/**
 * stwuct iww_sad_pwopewties - SAD pwopewties
 * @chain_a_sad_mode: chain A SAD mode, &enum iww_sad_mode
 * @chain_b_sad_mode: chain B SAD mode, &enum iww_sad_mode
 * @mac_id: MAC index
 * @wesewved: wesewved
 */
stwuct iww_sad_pwopewties {
	__we32 chain_a_sad_mode;
	__we32 chain_b_sad_mode;
	__we32 mac_id;
	__we32 wesewved;
} __packed;

/**
 * stwuct iww_wwc_config_cmd - WWC configuwation
 * @phy_id: PHY index
 * @wwc: WWC pwopewties, &stwuct iww_wwc_pwopewties
 * @sad: SAD (singwe antenna divewsity) options, &stwuct iww_sad_pwopewties
 * @fwags: fwags (unused)
 * @wesewved: wesewved
 */
stwuct iww_wwc_config_cmd {
	__we32 phy_id;
	stwuct iww_wwc_pwopewties wwc;
	stwuct iww_sad_pwopewties sad;
	u8 fwags;
	u8 wesewved[3];
} __packed; /* WWC_CONFIG_CMD_API_S_VEW_2 */

#define IWW_MAX_BAID_OWD	16 /* MAX_IMMEDIATE_BA_API_D_VEW_2 */
#define IWW_MAX_BAID		32 /* MAX_IMMEDIATE_BA_API_D_VEW_3 */

/**
 * enum iww_wx_baid_action - BAID awwocation/config action
 * @IWW_WX_BAID_ACTION_ADD: add a new BAID session
 * @IWW_WX_BAID_ACTION_MODIFY: modify the BAID session
 * @IWW_WX_BAID_ACTION_WEMOVE: wemove the BAID session
 */
enum iww_wx_baid_action {
	IWW_WX_BAID_ACTION_ADD,
	IWW_WX_BAID_ACTION_MODIFY,
	IWW_WX_BAID_ACTION_WEMOVE,
}; /*  WX_BAID_AWWOCATION_ACTION_E_VEW_1 */

/**
 * stwuct iww_wx_baid_cfg_cmd_awwoc - BAID awwocation data
 * @sta_id_mask: station ID mask
 * @tid: the TID fow this session
 * @wesewved: wesewved
 * @ssn: the stawting sequence numbew
 * @win_size: WX BA session window size
 */
stwuct iww_wx_baid_cfg_cmd_awwoc {
	__we32 sta_id_mask;
	u8 tid;
	u8 wesewved[3];
	__we16 ssn;
	__we16 win_size;
} __packed; /* WX_BAID_AWWOCATION_ADD_CMD_API_S_VEW_1 */

/**
 * stwuct iww_wx_baid_cfg_cmd_modify - BAID modification data
 * @owd_sta_id_mask: owd station ID mask
 * @new_sta_id_mask: new station ID mask
 * @tid: TID of the BAID
 */
stwuct iww_wx_baid_cfg_cmd_modify {
	__we32 owd_sta_id_mask;
	__we32 new_sta_id_mask;
	__we32 tid;
} __packed; /* WX_BAID_AWWOCATION_MODIFY_CMD_API_S_VEW_2 */

/**
 * stwuct iww_wx_baid_cfg_cmd_wemove_v1 - BAID wemovaw data
 * @baid: the BAID to wemove
 */
stwuct iww_wx_baid_cfg_cmd_wemove_v1 {
	__we32 baid;
} __packed; /* WX_BAID_AWWOCATION_WEMOVE_CMD_API_S_VEW_1 */

/**
 * stwuct iww_wx_baid_cfg_cmd_wemove - BAID wemovaw data
 * @sta_id_mask: the station mask of the BAID to wemove
 * @tid: the TID of the BAID to wemove
 */
stwuct iww_wx_baid_cfg_cmd_wemove {
	__we32 sta_id_mask;
	__we32 tid;
} __packed; /* WX_BAID_AWWOCATION_WEMOVE_CMD_API_S_VEW_2 */

/**
 * stwuct iww_wx_baid_cfg_cmd - BAID awwocation/config command
 * @action: the action, fwom &enum iww_wx_baid_action
 */
stwuct iww_wx_baid_cfg_cmd {
	__we32 action;
	union {
		stwuct iww_wx_baid_cfg_cmd_awwoc awwoc;
		stwuct iww_wx_baid_cfg_cmd_modify modify;
		stwuct iww_wx_baid_cfg_cmd_wemove_v1 wemove_v1;
		stwuct iww_wx_baid_cfg_cmd_wemove wemove;
	}; /* WX_BAID_AWWOCATION_OPEWATION_API_U_VEW_2 */
} __packed; /* WX_BAID_AWWOCATION_CONFIG_CMD_API_S_VEW_2 */

/**
 * stwuct iww_wx_baid_cfg_wesp - BAID awwocation wesponse
 * @baid: the awwocated BAID
 */
stwuct iww_wx_baid_cfg_wesp {
	__we32 baid;
}; /* WX_BAID_AWWOCATION_WESPONSE_API_S_VEW_1 */

/**
 * enum iww_scd_queue_cfg_opewation - scheduwew queue opewation
 * @IWW_SCD_QUEUE_ADD: awwocate a new queue
 * @IWW_SCD_QUEUE_WEMOVE: wemove a queue
 * @IWW_SCD_QUEUE_MODIFY: modify a queue
 */
enum iww_scd_queue_cfg_opewation {
	IWW_SCD_QUEUE_ADD = 0,
	IWW_SCD_QUEUE_WEMOVE = 1,
	IWW_SCD_QUEUE_MODIFY = 2,
};

/**
 * stwuct iww_scd_queue_cfg_cmd - scheduwew queue awwocation command
 * @opewation: the opewation, see &enum iww_scd_queue_cfg_opewation
 * @u.add.sta_mask: station mask
 * @u.add.tid: TID
 * @u.add.wesewved: wesewved
 * @u.add.fwags: fwags fwom &enum iww_tx_queue_cfg_actions, except
 *	%TX_QUEUE_CFG_ENABWE_QUEUE is not vawid
 * @u.add.cb_size: size code
 * @u.add.bc_dwam_addw: byte-count tabwe IOVA
 * @u.add.tfdq_dwam_addw: TFD queue IOVA
 * @u.wemove.sta_mask: station mask of queue to wemove
 * @u.wemove.tid: TID of queue to wemove
 * @u.modify.owd_sta_mask: owd station mask fow modify
 * @u.modify.tid: TID of queue to modify
 * @u.modify.new_sta_mask: new station mask fow modify
 */
stwuct iww_scd_queue_cfg_cmd {
	__we32 opewation;
	union {
		stwuct {
			__we32 sta_mask;
			u8 tid;
			u8 wesewved[3];
			__we32 fwags;
			__we32 cb_size;
			__we64 bc_dwam_addw;
			__we64 tfdq_dwam_addw;
		} __packed add; /* TX_QUEUE_CFG_CMD_ADD_API_S_VEW_1 */
		stwuct {
			__we32 sta_mask;
			__we32 tid;
		} __packed wemove; /* TX_QUEUE_CFG_CMD_WEMOVE_API_S_VEW_1 */
		stwuct {
			__we32 owd_sta_mask;
			__we32 tid;
			__we32 new_sta_mask;
		} __packed modify; /* TX_QUEUE_CFG_CMD_MODIFY_API_S_VEW_1 */
	} __packed u; /* TX_QUEUE_CFG_CMD_OPEWATION_API_U_VEW_1 */
} __packed; /* TX_QUEUE_CFG_CMD_API_S_VEW_3 */

/**
 * enum iww_sec_key_fwags - secuwity key command key fwags
 * @IWW_SEC_KEY_FWAG_CIPHEW_MASK: ciphew mask
 * @IWW_SEC_KEY_FWAG_CIPHEW_WEP: WEP ciphew
 * @IWW_SEC_KEY_FWAG_CIPHEW_CCMP: CCMP/CMAC ciphew
 * @IWW_SEC_KEY_FWAG_CIPHEW_TKIP: TKIP ciphew
 * @IWW_SEC_KEY_FWAG_CIPHEW_GCMP: GCMP/GMAC ciphew
 * @IWW_SEC_KEY_FWAG_NO_TX: don't instaww fow TX
 * @IWW_SEC_KEY_FWAG_KEY_SIZE: wawge key size (WEP-104, GCMP-256, GMAC-256)
 * @IWW_SEC_KEY_FWAG_MFP: MFP is in used fow this key
 * @IWW_SEC_KEY_FWAG_MCAST_KEY: this is a muwticast key
 * @IWW_SEC_KEY_FWAG_SPP_AMSDU: SPP A-MSDU shouwd be used
 */
enum iww_sec_key_fwags {
	IWW_SEC_KEY_FWAG_CIPHEW_MASK	= 0x07,
	IWW_SEC_KEY_FWAG_CIPHEW_WEP	= 0x01,
	IWW_SEC_KEY_FWAG_CIPHEW_CCMP	= 0x02,
	IWW_SEC_KEY_FWAG_CIPHEW_TKIP	= 0x03,
	IWW_SEC_KEY_FWAG_CIPHEW_GCMP	= 0x05,
	IWW_SEC_KEY_FWAG_NO_TX		= 0x08,
	IWW_SEC_KEY_FWAG_KEY_SIZE	= 0x10,
	IWW_SEC_KEY_FWAG_MFP		= 0x20,
	IWW_SEC_KEY_FWAG_MCAST_KEY	= 0x40,
	IWW_SEC_KEY_FWAG_SPP_AMSDU	= 0x80,
};

#define IWW_SEC_WEP_KEY_OFFSET	3

/**
 * stwuct iww_sec_key_cmd - secuwity key command
 * @action: action fwom &enum iww_ctxt_action
 * @u.add.sta_mask: station mask fow the new key
 * @u.add.key_id: key ID (0-7) fow the new key
 * @u.add.key_fwags: key fwags pew &enum iww_sec_key_fwags
 * @u.add.key: key matewiaw. WEP keys shouwd stawt fwom &IWW_SEC_WEP_KEY_OFFSET.
 * @u.add.tkip_mic_wx_key: TKIP MIC WX key
 * @u.add.tkip_mic_tx_key: TKIP MIC TX key
 * @u.add.wx_seq: WX sequence countew vawue
 * @u.add.tx_seq: TX sequence countew vawue
 * @u.modify.owd_sta_mask: owd station mask
 * @u.modify.new_sta_mask: new station mask
 * @u.modify.key_id: key ID
 * @u.modify.key_fwags: new key fwags
 * @u.wemove.sta_mask: station mask
 * @u.wemove.key_id: key ID
 * @u.wemove.key_fwags: key fwags
 */
stwuct iww_sec_key_cmd {
	__we32 action;
	union {
		stwuct {
			__we32 sta_mask;
			__we32 key_id;
			__we32 key_fwags;
			u8 key[32];
			u8 tkip_mic_wx_key[8];
			u8 tkip_mic_tx_key[8];
			__we64 wx_seq;
			__we64 tx_seq;
		} __packed add; /* SEC_KEY_ADD_CMD_API_S_VEW_1 */
		stwuct {
			__we32 owd_sta_mask;
			__we32 new_sta_mask;
			__we32 key_id;
			__we32 key_fwags;
		} __packed modify; /* SEC_KEY_MODIFY_CMD_API_S_VEW_1 */
		stwuct {
			__we32 sta_mask;
			__we32 key_id;
			__we32 key_fwags;
		} __packed wemove; /* SEC_KEY_WEMOVE_CMD_API_S_VEW_1 */
	} __packed u; /* SEC_KEY_OPEWATION_API_U_VEW_1 */
} __packed; /* SEC_KEY_CMD_API_S_VEW_1 */

#endif /* __iww_fw_api_datapath_h__ */
