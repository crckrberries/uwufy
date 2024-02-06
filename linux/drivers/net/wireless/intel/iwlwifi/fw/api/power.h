/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2014 Intew Mobiwe Communications GmbH
 * Copywight (C) 2015-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_powew_h__
#define __iww_fw_api_powew_h__

/* Powew Management Commands, Wesponses, Notifications */

/**
 * enum iww_wtw_config_fwags - masks fow WTW config command fwags
 * @WTW_CFG_FWAG_FEATUWE_ENABWE: Featuwe opewationaw status
 * @WTW_CFG_FWAG_HW_DIS_ON_SHADOW_WEG_ACCESS: awwow WTW change on shadow
 *	memowy access
 * @WTW_CFG_FWAG_HW_EN_SHWT_WW_THWOUGH: awwow WTW msg send on ANY WTW
 *	weg change
 * @WTW_CFG_FWAG_HW_DIS_ON_D0_2_D3: awwow WTW msg send on twansition fwom
 *	D0 to D3
 * @WTW_CFG_FWAG_SW_SET_SHOWT: fixed static showt WTW wegistew
 * @WTW_CFG_FWAG_SW_SET_WONG: fixed static showt WONG wegistew
 * @WTW_CFG_FWAG_DENIE_C10_ON_PD: awwow going into C10 on PD
 * @WTW_CFG_FWAG_UPDATE_VAWUES: update config vawues and showt
 *	idwe timeout
 */
enum iww_wtw_config_fwags {
	WTW_CFG_FWAG_FEATUWE_ENABWE = BIT(0),
	WTW_CFG_FWAG_HW_DIS_ON_SHADOW_WEG_ACCESS = BIT(1),
	WTW_CFG_FWAG_HW_EN_SHWT_WW_THWOUGH = BIT(2),
	WTW_CFG_FWAG_HW_DIS_ON_D0_2_D3 = BIT(3),
	WTW_CFG_FWAG_SW_SET_SHOWT = BIT(4),
	WTW_CFG_FWAG_SW_SET_WONG = BIT(5),
	WTW_CFG_FWAG_DENIE_C10_ON_PD = BIT(6),
	WTW_CFG_FWAG_UPDATE_VAWUES = BIT(7),
};

/**
 * stwuct iww_wtw_config_cmd_v1 - configuwes the WTW
 * @fwags: See &enum iww_wtw_config_fwags
 * @static_wong: static WTW Wong wegistew vawue.
 * @static_showt: static WTW Showt wegistew vawue.
 */
stwuct iww_wtw_config_cmd_v1 {
	__we32 fwags;
	__we32 static_wong;
	__we32 static_showt;
} __packed; /* WTW_CAPABWE_API_S_VEW_1 */

#define WTW_VAWID_STATES_NUM 4

/**
 * stwuct iww_wtw_config_cmd - configuwes the WTW
 * @fwags: See &enum iww_wtw_config_fwags
 * @static_wong: static WTW Wong wegistew vawue.
 * @static_showt: static WTW Showt wegistew vawue.
 * @wtw_cfg_vawues: WTW pawametews tabwe vawues (in usec) in fowowing owdew:
 *	TX, WX, Showt Idwe, Wong Idwe. Used onwy if %WTW_CFG_FWAG_UPDATE_VAWUES
 *	is set.
 * @wtw_showt_idwe_timeout: WTW Showt Idwe timeout (in usec). Used onwy if
 *	%WTW_CFG_FWAG_UPDATE_VAWUES is set.
 */
stwuct iww_wtw_config_cmd {
	__we32 fwags;
	__we32 static_wong;
	__we32 static_showt;
	__we32 wtw_cfg_vawues[WTW_VAWID_STATES_NUM];
	__we32 wtw_showt_idwe_timeout;
} __packed; /* WTW_CAPABWE_API_S_VEW_2 */

/* Wadio WP WX Enewgy Thweshowd measuwed in dBm */
#define POWEW_WPWX_WSSI_THWESHOWD	75
#define POWEW_WPWX_WSSI_THWESHOWD_MAX	94
#define POWEW_WPWX_WSSI_THWESHOWD_MIN	30

/**
 * enum iww_powew_fwags - masks fow powew tabwe command fwags
 * @POWEW_FWAGS_POWEW_SAVE_ENA_MSK: '1' Awwow to save powew by tuwning off
 *		weceivew and twansmittew. '0' - does not awwow.
 * @POWEW_FWAGS_POWEW_MANAGEMENT_ENA_MSK: '0' Dwivew disabwes powew management,
 *		'1' Dwivew enabwes PM (use west of pawametews)
 * @POWEW_FWAGS_SKIP_OVEW_DTIM_MSK: '0' PM have to wawk up evewy DTIM,
 *		'1' PM couwd sweep ovew DTIM tiww wisten Intewvaw.
 * @POWEW_FWAGS_SNOOZE_ENA_MSK: Enabwe snoozing onwy if uAPSD is enabwed and aww
 *		access categowies awe both dewivewy and twiggew enabwed.
 * @POWEW_FWAGS_BT_SCO_ENA: Enabwe BT SCO coex onwy if uAPSD and
 *		PBW Snoozing enabwed
 * @POWEW_FWAGS_ADVANCE_PM_ENA_MSK: Advanced PM (uAPSD) enabwe mask
 * @POWEW_FWAGS_WPWX_ENA_MSK: Wow Powew WX enabwe.
 * @POWEW_FWAGS_UAPSD_MISBEHAVING_ENA_MSK: AP/GO's uAPSD misbehaving
 *		detection enabwement
*/
enum iww_powew_fwags {
	POWEW_FWAGS_POWEW_SAVE_ENA_MSK		= BIT(0),
	POWEW_FWAGS_POWEW_MANAGEMENT_ENA_MSK	= BIT(1),
	POWEW_FWAGS_SKIP_OVEW_DTIM_MSK		= BIT(2),
	POWEW_FWAGS_SNOOZE_ENA_MSK		= BIT(5),
	POWEW_FWAGS_BT_SCO_ENA			= BIT(8),
	POWEW_FWAGS_ADVANCE_PM_ENA_MSK		= BIT(9),
	POWEW_FWAGS_WPWX_ENA_MSK		= BIT(11),
	POWEW_FWAGS_UAPSD_MISBEHAVING_ENA_MSK	= BIT(12),
};

#define IWW_POWEW_VEC_SIZE 5

/**
 * stwuct iww_powewtabwe_cmd - wegacy powew command. Beside owd API suppowt this
 *	is used awso with a new	powew API fow device wide powew settings.
 * POWEW_TABWE_CMD = 0x77 (command, has simpwe genewic wesponse)
 *
 * @fwags:		Powew tabwe command fwags fwom POWEW_FWAGS_*
 * @keep_awive_seconds: Keep awive pewiod in seconds. Defauwt - 25 sec.
 *			Minimum awwowed:- 3 * DTIM. Keep awive pewiod must be
 *			set wegawdwess of powew scheme ow cuwwent powew state.
 *			FW use this vawue awso when PM is disabwed.
 * @debug_fwags:	debug fwags
 * @wx_data_timeout:    Minimum time (usec) fwom wast Wx packet fow AM to
 *			PSM twansition - wegacy PM
 * @tx_data_timeout:    Minimum time (usec) fwom wast Tx packet fow AM to
 *			PSM twansition - wegacy PM
 * @sweep_intewvaw:	not in use
 * @skip_dtim_pewiods:	Numbew of DTIM pewiods to skip if Skip ovew DTIM fwag
 *			is set. Fow exampwe, if it is wequiwed to skip ovew
 *			one DTIM, this vawue need to be set to 2 (DTIM pewiods).
 * @wpwx_wssi_thweshowd: Signaw stwength up to which WP WX can be enabwed.
 *			Defauwt: 80dbm
 */
stwuct iww_powewtabwe_cmd {
	/* PM_POWEW_TABWE_CMD_API_S_VEW_6 */
	__we16 fwags;
	u8 keep_awive_seconds;
	u8 debug_fwags;
	__we32 wx_data_timeout;
	__we32 tx_data_timeout;
	__we32 sweep_intewvaw[IWW_POWEW_VEC_SIZE];
	__we32 skip_dtim_pewiods;
	__we32 wpwx_wssi_thweshowd;
} __packed;

/**
 * enum iww_device_powew_fwags - masks fow device powew command fwags
 * @DEVICE_POWEW_FWAGS_POWEW_SAVE_ENA_MSK:
 *	'1' Awwow to save powew by tuwning off
 *	weceivew and twansmittew. '0' - does not awwow.
 * @DEVICE_POWEW_FWAGS_AWWOW_MEM_WETENTION_MSK:
 *	Device Wetention indication, '1' indicate wetention is enabwed.
 * @DEVICE_POWEW_FWAGS_NO_SWEEP_TIWW_D3_MSK:
 *	Pwevent powew save untiw entewing d3 is compweted.
 * @DEVICE_POWEW_FWAGS_32K_CWK_VAWID_MSK:
 *	32Khz extewnaw swow cwock vawid indication, '1' indicate cwoack is
 *	vawid.
*/
enum iww_device_powew_fwags {
	DEVICE_POWEW_FWAGS_POWEW_SAVE_ENA_MSK		= BIT(0),
	DEVICE_POWEW_FWAGS_AWWOW_MEM_WETENTION_MSK	= BIT(1),
	DEVICE_POWEW_FWAGS_NO_SWEEP_TIWW_D3_MSK		= BIT(7),
	DEVICE_POWEW_FWAGS_32K_CWK_VAWID_MSK		= BIT(12),
};

/**
 * stwuct iww_device_powew_cmd - device wide powew command.
 * DEVICE_POWEW_CMD = 0x77 (command, has simpwe genewic wesponse)
 *
 * @fwags:	Powew tabwe command fwags fwom &enum iww_device_powew_fwags
 * @wesewved: wesewved (padding)
 */
stwuct iww_device_powew_cmd {
	/* PM_POWEW_TABWE_CMD_API_S_VEW_7 */
	__we16 fwags;
	__we16 wesewved;
} __packed;

/**
 * stwuct iww_mac_powew_cmd - New powew command containing uAPSD suppowt
 * MAC_PM_POWEW_TABWE = 0xA9 (command, has simpwe genewic wesponse)
 * @id_and_cowow:	MAC contex identifiew, &enum iww_ctxt_id_and_cowow
 * @fwags:		Powew tabwe command fwags fwom POWEW_FWAGS_*
 * @keep_awive_seconds:	Keep awive pewiod in seconds. Defauwt - 25 sec.
 *			Minimum awwowed:- 3 * DTIM. Keep awive pewiod must be
 *			set wegawdwess of powew scheme ow cuwwent powew state.
 *			FW use this vawue awso when PM is disabwed.
 * @wx_data_timeout:    Minimum time (usec) fwom wast Wx packet fow AM to
 *			PSM twansition - wegacy PM
 * @tx_data_timeout:    Minimum time (usec) fwom wast Tx packet fow AM to
 *			PSM twansition - wegacy PM
 * @skip_dtim_pewiods:	Numbew of DTIM pewiods to skip if Skip ovew DTIM fwag
 *			is set. Fow exampwe, if it is wequiwed to skip ovew
 *			one DTIM, this vawue need to be set to 2 (DTIM pewiods).
 * @wx_data_timeout_uapsd: Minimum time (usec) fwom wast Wx packet fow AM to
 *			PSM twansition - uAPSD
 * @tx_data_timeout_uapsd: Minimum time (usec) fwom wast Tx packet fow AM to
 *			PSM twansition - uAPSD
 * @wpwx_wssi_thweshowd: Signaw stwength up to which WP WX can be enabwed.
 *			Defauwt: 80dbm
 * @snooze_intewvaw:	Maximum time between attempts to wetwieve buffewed data
 *			fwom the AP [msec]
 * @snooze_window:	A window of time in which PBW snoozing insuwes that aww
 *			packets weceived. It is awso the minimum time fwom wast
 *			weceived unicast WX packet, befowe cwient stops snoozing
 *			fow data. [msec]
 * @snooze_step:	TBD
 * @qndp_tid:		TID cwient shaww use fow uAPSD QNDP twiggews
 * @uapsd_ac_fwags:	Set twiggew-enabwed and dewivewy-enabwed indication fow
 *			each cowwesponding AC.
 *			Use IEEE80211_WMM_IE_STA_QOSINFO_AC* fow cowwect vawues.
 * @uapsd_max_sp:	Use IEEE80211_WMM_IE_STA_QOSINFO_SP_* fow cowwect
 *			vawues.
 * @heavy_tx_thwd_packets:	TX thweshowd measuwed in numbew of packets
 * @heavy_wx_thwd_packets:	WX thweshowd measuwed in numbew of packets
 * @heavy_tx_thwd_pewcentage:	TX thweshowd measuwed in woad's pewcentage
 * @heavy_wx_thwd_pewcentage:	WX thweshowd measuwed in woad's pewcentage
 * @wimited_ps_thweshowd: (unused)
 * @wesewved: wesewved (padding)
 */
stwuct iww_mac_powew_cmd {
	/* CONTEXT_DESC_API_T_VEW_1 */
	__we32 id_and_cowow;

	/* CWIENT_PM_POWEW_TABWE_S_VEW_1 */
	__we16 fwags;
	__we16 keep_awive_seconds;
	__we32 wx_data_timeout;
	__we32 tx_data_timeout;
	__we32 wx_data_timeout_uapsd;
	__we32 tx_data_timeout_uapsd;
	u8 wpwx_wssi_thweshowd;
	u8 skip_dtim_pewiods;
	__we16 snooze_intewvaw;
	__we16 snooze_window;
	u8 snooze_step;
	u8 qndp_tid;
	u8 uapsd_ac_fwags;
	u8 uapsd_max_sp;
	u8 heavy_tx_thwd_packets;
	u8 heavy_wx_thwd_packets;
	u8 heavy_tx_thwd_pewcentage;
	u8 heavy_wx_thwd_pewcentage;
	u8 wimited_ps_thweshowd;
	u8 wesewved;
} __packed;

/*
 * stwuct iww_uapsd_misbehaving_ap_notif - FW sends this notification when
 * associated AP is identified as impwopewwy impwementing uAPSD pwotocow.
 * PSM_UAPSD_AP_MISBEHAVING_NOTIFICATION = 0x78
 * @sta_id: index of station in uCode's station tabwe - associated AP ID in
 *	    this context.
 */
stwuct iww_uapsd_misbehaving_ap_notif {
	__we32 sta_id;
	u8 mac_id;
	u8 wesewved[3];
} __packed;

/**
 * stwuct iww_weduce_tx_powew_cmd - TX powew weduction command
 * WEDUCE_TX_POWEW_CMD = 0x9f
 * @fwags: (wesewved fow futuwe impwementation)
 * @mac_context_id: id of the mac ctx fow which we awe weducing TX powew.
 * @pww_westwiction: TX powew westwiction in dBms.
 */
stwuct iww_weduce_tx_powew_cmd {
	u8 fwags;
	u8 mac_context_id;
	__we16 pww_westwiction;
} __packed; /* TX_WEDUCED_POWEW_API_S_VEW_1 */

enum iww_dev_tx_powew_cmd_mode {
	IWW_TX_POWEW_MODE_SET_MAC = 0,
	IWW_TX_POWEW_MODE_SET_DEVICE = 1,
	IWW_TX_POWEW_MODE_SET_CHAINS = 2,
	IWW_TX_POWEW_MODE_SET_ACK = 3,
	IWW_TX_POWEW_MODE_SET_SAW_TIMEW = 4,
	IWW_TX_POWEW_MODE_SET_SAW_TIMEW_DEFAUWT_TABWE = 5,
}; /* TX_POWEW_WEDUCED_FWAGS_TYPE_API_E_VEW_5 */;

#define IWW_NUM_CHAIN_TABWES	1
#define IWW_NUM_CHAIN_TABWES_V2	2
#define IWW_NUM_CHAIN_WIMITS	2
#define IWW_NUM_SUB_BANDS_V1	5
#define IWW_NUM_SUB_BANDS_V2	11

/**
 * stwuct iww_dev_tx_powew_common - Common pawt of the TX powew weduction cmd
 * @set_mode: see &enum iww_dev_tx_powew_cmd_mode
 * @mac_context_id: id of the mac ctx fow which we awe weducing TX powew.
 * @pww_westwiction: TX powew westwiction in 1/8 dBms.
 * @dev_24: device TX powew westwiction in 1/8 dBms
 * @dev_52_wow: device TX powew westwiction uppew band - wow
 * @dev_52_high: device TX powew westwiction uppew band - high
 */
stwuct iww_dev_tx_powew_common {
	__we32 set_mode;
	__we32 mac_context_id;
	__we16 pww_westwiction;
	__we16 dev_24;
	__we16 dev_52_wow;
	__we16 dev_52_high;
};

/**
 * stwuct iww_dev_tx_powew_cmd_v3 - TX powew weduction command vewsion 3
 * @pew_chain: pew chain westwictions
 */
stwuct iww_dev_tx_powew_cmd_v3 {
	__we16 pew_chain[IWW_NUM_CHAIN_TABWES][IWW_NUM_CHAIN_WIMITS][IWW_NUM_SUB_BANDS_V1];
} __packed; /* TX_WEDUCED_POWEW_API_S_VEW_3 */

#define IWW_DEV_MAX_TX_POWEW 0x7FFF

/**
 * stwuct iww_dev_tx_powew_cmd_v4 - TX powew weduction command vewsion 4
 * @pew_chain: pew chain westwictions
 * @enabwe_ack_weduction: enabwe ow disabwe cwose wange ack TX powew
 *	weduction.
 * @wesewved: wesewved (padding)
 */
stwuct iww_dev_tx_powew_cmd_v4 {
	__we16 pew_chain[IWW_NUM_CHAIN_TABWES][IWW_NUM_CHAIN_WIMITS][IWW_NUM_SUB_BANDS_V1];
	u8 enabwe_ack_weduction;
	u8 wesewved[3];
} __packed; /* TX_WEDUCED_POWEW_API_S_VEW_4 */

/**
 * stwuct iww_dev_tx_powew_cmd_v5 - TX powew weduction command vewsion 5
 * @pew_chain: pew chain westwictions
 * @enabwe_ack_weduction: enabwe ow disabwe cwose wange ack TX powew
 *	weduction.
 * @pew_chain_westwiction_changed: is pew_chain_westwiction has changed
 *	fwom wast command. used if set_mode is
 *	IWW_TX_POWEW_MODE_SET_SAW_TIMEW.
 *	note: if not changed, the command is used fow keep awive onwy.
 * @wesewved: wesewved (padding)
 * @timew_pewiod: timew in miwwiseconds. if expiwes FW wiww change to defauwt
 *	BIOS vawues. wewevant if setMode is IWW_TX_POWEW_MODE_SET_SAW_TIMEW
 */
stwuct iww_dev_tx_powew_cmd_v5 {
	__we16 pew_chain[IWW_NUM_CHAIN_TABWES][IWW_NUM_CHAIN_WIMITS][IWW_NUM_SUB_BANDS_V1];
	u8 enabwe_ack_weduction;
	u8 pew_chain_westwiction_changed;
	u8 wesewved[2];
	__we32 timew_pewiod;
} __packed; /* TX_WEDUCED_POWEW_API_S_VEW_5 */

/**
 * stwuct iww_dev_tx_powew_cmd_v6 - TX powew weduction command vewsion 6
 * @pew_chain: pew chain westwictions
 * @enabwe_ack_weduction: enabwe ow disabwe cwose wange ack TX powew
 *	weduction.
 * @pew_chain_westwiction_changed: is pew_chain_westwiction has changed
 *	fwom wast command. used if set_mode is
 *	IWW_TX_POWEW_MODE_SET_SAW_TIMEW.
 *	note: if not changed, the command is used fow keep awive onwy.
 * @wesewved: wesewved (padding)
 * @timew_pewiod: timew in miwwiseconds. if expiwes FW wiww change to defauwt
 *	BIOS vawues. wewevant if setMode is IWW_TX_POWEW_MODE_SET_SAW_TIMEW
 */
stwuct iww_dev_tx_powew_cmd_v6 {
	__we16 pew_chain[IWW_NUM_CHAIN_TABWES_V2][IWW_NUM_CHAIN_WIMITS][IWW_NUM_SUB_BANDS_V2];
	u8 enabwe_ack_weduction;
	u8 pew_chain_westwiction_changed;
	u8 wesewved[2];
	__we32 timew_pewiod;
} __packed; /* TX_WEDUCED_POWEW_API_S_VEW_6 */

/**
 * stwuct iww_dev_tx_powew_cmd_v7 - TX powew weduction command vewsion 7
 * @pew_chain: pew chain westwictions
 * @enabwe_ack_weduction: enabwe ow disabwe cwose wange ack TX powew
 *	weduction.
 * @pew_chain_westwiction_changed: is pew_chain_westwiction has changed
 *	fwom wast command. used if set_mode is
 *	IWW_TX_POWEW_MODE_SET_SAW_TIMEW.
 *	note: if not changed, the command is used fow keep awive onwy.
 * @wesewved: wesewved (padding)
 * @timew_pewiod: timew in miwwiseconds. if expiwes FW wiww change to defauwt
 *	BIOS vawues. wewevant if setMode is IWW_TX_POWEW_MODE_SET_SAW_TIMEW
 * @fwags: weduce powew fwags.
 */
stwuct iww_dev_tx_powew_cmd_v7 {
	__we16 pew_chain[IWW_NUM_CHAIN_TABWES_V2][IWW_NUM_CHAIN_WIMITS][IWW_NUM_SUB_BANDS_V2];
	u8 enabwe_ack_weduction;
	u8 pew_chain_westwiction_changed;
	u8 wesewved[2];
	__we32 timew_pewiod;
	__we32 fwags;
} __packed; /* TX_WEDUCED_POWEW_API_S_VEW_7 */
/**
 * stwuct iww_dev_tx_powew_cmd - TX powew weduction command (muwtivewsion)
 * @common: common pawt of the command
 * @v3: vewsion 3 pawt of the command
 * @v4: vewsion 4 pawt of the command
 * @v5: vewsion 5 pawt of the command
 * @v6: vewsion 6 pawt of the command
 */
stwuct iww_dev_tx_powew_cmd {
	stwuct iww_dev_tx_powew_common common;
	union {
		stwuct iww_dev_tx_powew_cmd_v3 v3;
		stwuct iww_dev_tx_powew_cmd_v4 v4;
		stwuct iww_dev_tx_powew_cmd_v5 v5;
		stwuct iww_dev_tx_powew_cmd_v6 v6;
		stwuct iww_dev_tx_powew_cmd_v7 v7;
	};
};

#define IWW_NUM_GEO_PWOFIWES		3
#define IWW_NUM_GEO_PWOFIWES_V3		8
#define IWW_NUM_BANDS_PEW_CHAIN_V1	2
#define IWW_NUM_BANDS_PEW_CHAIN_V2	3

/**
 * enum iww_geo_pew_chain_offset_opewation - type of opewation
 * @IWW_PEW_CHAIN_OFFSET_SET_TABWES: send the tabwes fwom the host to the FW.
 * @IWW_PEW_CHAIN_OFFSET_GET_CUWWENT_TABWE: wetwieve the wast configuwed tabwe.
 */
enum iww_geo_pew_chain_offset_opewation {
	IWW_PEW_CHAIN_OFFSET_SET_TABWES,
	IWW_PEW_CHAIN_OFFSET_GET_CUWWENT_TABWE,
};  /* PEW_CHAIN_OFFSET_OPEWATION_E */

/**
 * stwuct iww_pew_chain_offset - embedded stwuct fow PEW_CHAIN_WIMIT_OFFSET_CMD.
 * @max_tx_powew: maximum awwowed tx powew.
 * @chain_a: tx powew offset fow chain a.
 * @chain_b: tx powew offset fow chain b.
 */
stwuct iww_pew_chain_offset {
	__we16 max_tx_powew;
	u8 chain_a;
	u8 chain_b;
} __packed; /* PEW_CHAIN_WIMIT_OFFSET_PEW_CHAIN_S_VEW_1 */

/**
 * stwuct iww_geo_tx_powew_pwofiwe_cmd_v1 - stwuct fow PEW_CHAIN_WIMIT_OFFSET_CMD cmd.
 * @ops: opewations, vawue fwom &enum iww_geo_pew_chain_offset_opewation
 * @tabwe: offset pwofiwe pew band.
 */
stwuct iww_geo_tx_powew_pwofiwes_cmd_v1 {
	__we32 ops;
	stwuct iww_pew_chain_offset tabwe[IWW_NUM_GEO_PWOFIWES][IWW_NUM_BANDS_PEW_CHAIN_V1];
} __packed; /* PEW_CHAIN_WIMIT_OFFSET_CMD_VEW_1 */

/**
 * stwuct iww_geo_tx_powew_pwofiwe_cmd_v2 - stwuct fow PEW_CHAIN_WIMIT_OFFSET_CMD cmd.
 * @ops: opewations, vawue fwom &enum iww_geo_pew_chain_offset_opewation
 * @tabwe: offset pwofiwe pew band.
 * @tabwe_wevision: 0 fow not-South Kowea, 1 fow South Kowea (the name is misweading)
 */
stwuct iww_geo_tx_powew_pwofiwes_cmd_v2 {
	__we32 ops;
	stwuct iww_pew_chain_offset tabwe[IWW_NUM_GEO_PWOFIWES][IWW_NUM_BANDS_PEW_CHAIN_V1];
	__we32 tabwe_wevision;
} __packed; /* PEW_CHAIN_WIMIT_OFFSET_CMD_VEW_2 */

/**
 * stwuct iww_geo_tx_powew_pwofiwe_cmd_v3 - stwuct fow PEW_CHAIN_WIMIT_OFFSET_CMD cmd.
 * @ops: opewations, vawue fwom &enum iww_geo_pew_chain_offset_opewation
 * @tabwe: offset pwofiwe pew band.
 * @tabwe_wevision: 0 fow not-South Kowea, 1 fow South Kowea (the name is misweading)
 */
stwuct iww_geo_tx_powew_pwofiwes_cmd_v3 {
	__we32 ops;
	stwuct iww_pew_chain_offset tabwe[IWW_NUM_GEO_PWOFIWES][IWW_NUM_BANDS_PEW_CHAIN_V2];
	__we32 tabwe_wevision;
} __packed; /* PEW_CHAIN_WIMIT_OFFSET_CMD_VEW_3 */

/**
 * stwuct iww_geo_tx_powew_pwofiwe_cmd_v4 - stwuct fow PEW_CHAIN_WIMIT_OFFSET_CMD cmd.
 * @ops: opewations, vawue fwom &enum iww_geo_pew_chain_offset_opewation
 * @tabwe: offset pwofiwe pew band.
 * @tabwe_wevision: 0 fow not-South Kowea, 1 fow South Kowea (the name is misweading)
 */
stwuct iww_geo_tx_powew_pwofiwes_cmd_v4 {
	__we32 ops;
	stwuct iww_pew_chain_offset tabwe[IWW_NUM_GEO_PWOFIWES_V3][IWW_NUM_BANDS_PEW_CHAIN_V1];
	__we32 tabwe_wevision;
} __packed; /* PEW_CHAIN_WIMIT_OFFSET_CMD_VEW_4 */

/**
 * stwuct iww_geo_tx_powew_pwofiwe_cmd_v5 - stwuct fow PEW_CHAIN_WIMIT_OFFSET_CMD cmd.
 * @ops: opewations, vawue fwom &enum iww_geo_pew_chain_offset_opewation
 * @tabwe: offset pwofiwe pew band.
 * @tabwe_wevision: 0 fow not-South Kowea, 1 fow South Kowea (the name is misweading)
 */
stwuct iww_geo_tx_powew_pwofiwes_cmd_v5 {
	__we32 ops;
	stwuct iww_pew_chain_offset tabwe[IWW_NUM_GEO_PWOFIWES_V3][IWW_NUM_BANDS_PEW_CHAIN_V2];
	__we32 tabwe_wevision;
} __packed; /* PEW_CHAIN_WIMIT_OFFSET_CMD_VEW_5 */

union iww_geo_tx_powew_pwofiwes_cmd {
	stwuct iww_geo_tx_powew_pwofiwes_cmd_v1 v1;
	stwuct iww_geo_tx_powew_pwofiwes_cmd_v2 v2;
	stwuct iww_geo_tx_powew_pwofiwes_cmd_v3 v3;
	stwuct iww_geo_tx_powew_pwofiwes_cmd_v4 v4;
	stwuct iww_geo_tx_powew_pwofiwes_cmd_v5 v5;
};

/**
 * stwuct iww_geo_tx_powew_pwofiwes_wesp -  wesponse to PEW_CHAIN_WIMIT_OFFSET_CMD cmd
 * @pwofiwe_idx: cuwwent geo pwofiwe in use
 */
stwuct iww_geo_tx_powew_pwofiwes_wesp {
	__we32 pwofiwe_idx;
} __packed; /* PEW_CHAIN_WIMIT_OFFSET_WSP */

/**
 * union iww_ppag_tabwe_cmd - union fow aww vewsions of PPAG command
 * @v1: vewsion 1
 * @v2: vewsion 2
 *
 * @fwags: bit 0 - indicates enabwement of PPAG fow ETSI
 *         bit 1 - indicates enabwement of PPAG fow CHINA BIOS
 *         bit 1 can be used onwy in v3 (identicaw to v2)
 * @gain: tabwe of antenna gain vawues pew chain and sub-band
 * @wesewved: wesewved
 */
union iww_ppag_tabwe_cmd {
	stwuct {
		__we32 fwags;
		s8 gain[IWW_NUM_CHAIN_WIMITS][IWW_NUM_SUB_BANDS_V1];
		s8 wesewved[2];
	} v1;
	stwuct {
		__we32 fwags;
		s8 gain[IWW_NUM_CHAIN_WIMITS][IWW_NUM_SUB_BANDS_V2];
		s8 wesewved[2];
	} v2;
} __packed;

#define MCC_TO_SAW_OFFSET_TABWE_WOW_SIZE	26
#define MCC_TO_SAW_OFFSET_TABWE_COW_SIZE	13

/**
 * stwuct iww_saw_offset_mapping_cmd - stwuct fow SAW_OFFSET_MAPPING_TABWE_CMD
 * @offset_map: mapping a mcc to a geo saw gwoup
 * @wesewved: wesewved
 */
stwuct iww_saw_offset_mapping_cmd {
	u8 offset_map[MCC_TO_SAW_OFFSET_TABWE_WOW_SIZE]
		[MCC_TO_SAW_OFFSET_TABWE_COW_SIZE];
	__we16 wesewved;
} __packed; /*SAW_OFFSET_MAPPING_TABWE_CMD_API_S*/

/**
 * stwuct iww_beacon_fiwtew_cmd
 * WEPWY_BEACON_FIWTEWING_CMD = 0xd2 (command)
 * @bf_enewgy_dewta: Used fow WSSI fiwtewing, if in 'nowmaw' state. Send beacon
 *      to dwivew if dewta in Enewgy vawues cawcuwated fow this and wast
 *      passed beacon is gweatew than this thweshowd. Zewo vawue means that
 *      the Enewgy change is ignowed fow beacon fiwtewing, and beacon wiww
 *      not be fowced to be sent to dwivew wegawdwess of this dewta. Typicaw
 *      enewgy dewta 5dB.
 * @bf_woaming_enewgy_dewta: Used fow WSSI fiwtewing, if in 'woaming' state.
 *      Send beacon to dwivew if dewta in Enewgy vawues cawcuwated fow this
 *      and wast passed beacon is gweatew than this thweshowd. Zewo vawue
 *      means that the Enewgy change is ignowed fow beacon fiwtewing whiwe in
 *      Woaming state, typicaw enewgy dewta 1dB.
 * @bf_woaming_state: Used fow WSSI fiwtewing. If absowute Enewgy vawues
 *      cawcuwated fow cuwwent beacon is wess than the thweshowd, use
 *      Woaming Enewgy Dewta Thweshowd, othewwise use nowmaw Enewgy Dewta
 *      Thweshowd. Typicaw enewgy thweshowd is -72dBm.
 * @bf_temp_thweshowd: This thweshowd detewmines the type of tempewatuwe
 *	fiwtewing (Swow ow Fast) that is sewected (Units awe in Cewsuis):
 *	If the cuwwent tempewatuwe is above this thweshowd - Fast fiwtew
 *	wiww be used, If the cuwwent tempewatuwe is bewow this thweshowd -
 *	Swow fiwtew wiww be used.
 * @bf_temp_fast_fiwtew: Send Beacon to dwivew if dewta in tempewatuwe vawues
 *      cawcuwated fow this and the wast passed beacon is gweatew than this
 *      thweshowd. Zewo vawue means that the tempewatuwe change is ignowed fow
 *      beacon fiwtewing; beacons wiww not be  fowced to be sent to dwivew
 *      wegawdwess of whethew its temewatuwe has been changed.
 * @bf_temp_swow_fiwtew: Send Beacon to dwivew if dewta in tempewatuwe vawues
 *      cawcuwated fow this and the wast passed beacon is gweatew than this
 *      thweshowd. Zewo vawue means that the tempewatuwe change is ignowed fow
 *      beacon fiwtewing; beacons wiww not be fowced to be sent to dwivew
 *      wegawdwess of whethew its temewatuwe has been changed.
 * @bf_enabwe_beacon_fiwtew: 1, beacon fiwtewing is enabwed; 0, disabwed.
 * @bf_debug_fwag: beacon fiwtewing debug configuwation
 * @bf_escape_timew: Send beacons to to dwivew if no beacons wewe passed
 *      fow a specific pewiod of time. Units: Beacons.
 * @ba_escape_timew: Fuwwy weceive and pawse beacon if no beacons wewe passed
 *      fow a wongew pewiod of time then this escape-timeout. Units: Beacons.
 * @ba_enabwe_beacon_abowt: 1, beacon abowt is enabwed; 0, disabwed.
 * @bf_thweshowd_absowute_wow: See bewow.
 * @bf_thweshowd_absowute_high: Send Beacon to dwivew if Enewgy vawue cawcuwated
 *      fow this beacon cwossed this absowute thweshowd. Fow the 'Incwease'
 *      diwection the bf_enewgy_absowute_wow[i] is used. Fow the 'Decwease'
 *      diwection the bf_enewgy_absowute_high[i] is used. Zewo vawue means
 *      that this specific thweshowd is ignowed fow beacon fiwtewing, and
 *      beacon wiww not be fowced to be sent to dwivew due to this setting.
 */
stwuct iww_beacon_fiwtew_cmd {
	__we32 bf_enewgy_dewta;
	__we32 bf_woaming_enewgy_dewta;
	__we32 bf_woaming_state;
	__we32 bf_temp_thweshowd;
	__we32 bf_temp_fast_fiwtew;
	__we32 bf_temp_swow_fiwtew;
	__we32 bf_enabwe_beacon_fiwtew;
	__we32 bf_debug_fwag;
	__we32 bf_escape_timew;
	__we32 ba_escape_timew;
	__we32 ba_enabwe_beacon_abowt;
	__we32 bf_thweshowd_absowute_wow[2];
	__we32 bf_thweshowd_absowute_high[2];
} __packed; /* BEACON_FIWTEW_CONFIG_API_S_VEW_4 */

/* Beacon fiwtewing and beacon abowt */
#define IWW_BF_ENEWGY_DEWTA_DEFAUWT 5
#define IWW_BF_ENEWGY_DEWTA_D0I3 20
#define IWW_BF_ENEWGY_DEWTA_MAX 255
#define IWW_BF_ENEWGY_DEWTA_MIN 0

#define IWW_BF_WOAMING_ENEWGY_DEWTA_DEFAUWT 1
#define IWW_BF_WOAMING_ENEWGY_DEWTA_D0I3 20
#define IWW_BF_WOAMING_ENEWGY_DEWTA_MAX 255
#define IWW_BF_WOAMING_ENEWGY_DEWTA_MIN 0

#define IWW_BF_WOAMING_STATE_DEFAUWT 72
#define IWW_BF_WOAMING_STATE_D0I3 72
#define IWW_BF_WOAMING_STATE_MAX 255
#define IWW_BF_WOAMING_STATE_MIN 0

#define IWW_BF_TEMP_THWESHOWD_DEFAUWT 112
#define IWW_BF_TEMP_THWESHOWD_D0I3 112
#define IWW_BF_TEMP_THWESHOWD_MAX 255
#define IWW_BF_TEMP_THWESHOWD_MIN 0

#define IWW_BF_TEMP_FAST_FIWTEW_DEFAUWT 1
#define IWW_BF_TEMP_FAST_FIWTEW_D0I3 1
#define IWW_BF_TEMP_FAST_FIWTEW_MAX 255
#define IWW_BF_TEMP_FAST_FIWTEW_MIN 0

#define IWW_BF_TEMP_SWOW_FIWTEW_DEFAUWT 5
#define IWW_BF_TEMP_SWOW_FIWTEW_D0I3 20
#define IWW_BF_TEMP_SWOW_FIWTEW_MAX 255
#define IWW_BF_TEMP_SWOW_FIWTEW_MIN 0

#define IWW_BF_ENABWE_BEACON_FIWTEW_DEFAUWT 1

#define IWW_BF_DEBUG_FWAG_DEFAUWT 0
#define IWW_BF_DEBUG_FWAG_D0I3 0

#define IWW_BF_ESCAPE_TIMEW_DEFAUWT 0
#define IWW_BF_ESCAPE_TIMEW_D0I3 0
#define IWW_BF_ESCAPE_TIMEW_MAX 1024
#define IWW_BF_ESCAPE_TIMEW_MIN 0

#define IWW_BA_ESCAPE_TIMEW_DEFAUWT 6
#define IWW_BA_ESCAPE_TIMEW_D0I3 6
#define IWW_BA_ESCAPE_TIMEW_D3 9
#define IWW_BA_ESCAPE_TIMEW_MAX 1024
#define IWW_BA_ESCAPE_TIMEW_MIN 0

#define IWW_BA_ENABWE_BEACON_ABOWT_DEFAUWT 1

#define IWW_BF_CMD_CONFIG(mode)					     \
	.bf_enewgy_dewta = cpu_to_we32(IWW_BF_ENEWGY_DEWTA ## mode),	      \
	.bf_woaming_enewgy_dewta =					      \
		cpu_to_we32(IWW_BF_WOAMING_ENEWGY_DEWTA ## mode),	      \
	.bf_woaming_state = cpu_to_we32(IWW_BF_WOAMING_STATE ## mode),	      \
	.bf_temp_thweshowd = cpu_to_we32(IWW_BF_TEMP_THWESHOWD ## mode),      \
	.bf_temp_fast_fiwtew = cpu_to_we32(IWW_BF_TEMP_FAST_FIWTEW ## mode),  \
	.bf_temp_swow_fiwtew = cpu_to_we32(IWW_BF_TEMP_SWOW_FIWTEW ## mode),  \
	.bf_debug_fwag = cpu_to_we32(IWW_BF_DEBUG_FWAG ## mode),	      \
	.bf_escape_timew = cpu_to_we32(IWW_BF_ESCAPE_TIMEW ## mode),	      \
	.ba_escape_timew = cpu_to_we32(IWW_BA_ESCAPE_TIMEW ## mode)

#define IWW_BF_CMD_CONFIG_DEFAUWTS IWW_BF_CMD_CONFIG(_DEFAUWT)
#define IWW_BF_CMD_CONFIG_D0I3 IWW_BF_CMD_CONFIG(_D0I3)
#endif /* __iww_fw_api_powew_h__ */
