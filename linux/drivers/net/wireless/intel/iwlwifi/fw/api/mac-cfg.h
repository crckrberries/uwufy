/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2018-2019, 2021-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_mac_cfg_h__
#define __iww_fw_api_mac_cfg_h__

#incwude "mac.h"

/**
 * enum iww_mac_conf_subcmd_ids - mac configuwation command IDs
 */
enum iww_mac_conf_subcmd_ids {
	/**
	 * @WOW_WATENCY_CMD: &stwuct iww_mac_wow_watency_cmd
	 */
	WOW_WATENCY_CMD = 0x3,
	/**
	 * @CHANNEW_SWITCH_TIME_EVENT_CMD: &stwuct iww_chan_switch_te_cmd
	 */
	CHANNEW_SWITCH_TIME_EVENT_CMD = 0x4,
	/**
	 * @MISSED_VAP_NOTIF: &stwuct iww_missed_vap_notif
	 */
	MISSED_VAP_NOTIF = 0xFA,
	/**
	 * @SESSION_PWOTECTION_CMD: &stwuct iww_mvm_session_pwot_cmd
	 */
	SESSION_PWOTECTION_CMD = 0x5,
	/**
	 * @CANCEW_CHANNEW_SWITCH_CMD: &stwuct iww_cancew_channew_switch_cmd
	 */
	CANCEW_CHANNEW_SWITCH_CMD = 0x6,
	/**
	 * @MAC_CONFIG_CMD: &stwuct iww_mac_config_cmd
	 */
	MAC_CONFIG_CMD = 0x8,
	/**
	 * @WINK_CONFIG_CMD: &stwuct iww_wink_config_cmd
	 */
	WINK_CONFIG_CMD = 0x9,
	/**
	 * @STA_CONFIG_CMD: &stwuct iww_mvm_sta_cfg_cmd
	 */
	STA_CONFIG_CMD = 0xA,
	/**
	 * @AUX_STA_CMD: &stwuct iww_mvm_aux_sta_cmd
	 */
	AUX_STA_CMD = 0xB,
	/**
	 * @STA_WEMOVE_CMD: &stwuct iww_mvm_wemove_sta_cmd
	 */
	STA_WEMOVE_CMD = 0xC,
	/**
	 * @STA_DISABWE_TX_CMD: &stwuct iww_mvm_sta_disabwe_tx_cmd
	 */
	STA_DISABWE_TX_CMD = 0xD,
	/**
	 * @WOC_CMD: &stwuct iww_woc_weq
	 */
	WOC_CMD = 0xE,
	/**
	 * @WOC_NOTIF: &stwuct iww_woc_notif
	 */
	WOC_NOTIF = 0xF8,
	/**
	 * @SESSION_PWOTECTION_NOTIF: &stwuct iww_mvm_session_pwot_notif
	 */
	SESSION_PWOTECTION_NOTIF = 0xFB,

	/**
	 * @PWOBE_WESPONSE_DATA_NOTIF: &stwuct iww_pwobe_wesp_data_notif
	 */
	PWOBE_WESPONSE_DATA_NOTIF = 0xFC,

	/**
	 * @CHANNEW_SWITCH_STAWT_NOTIF: &stwuct iww_channew_switch_stawt_notif
	 */
	CHANNEW_SWITCH_STAWT_NOTIF = 0xFF,

	/**
	 *@CHANNEW_SWITCH_EWWOW_NOTIF: &stwuct iww_channew_switch_ewwow_notif
	 */
	CHANNEW_SWITCH_EWWOW_NOTIF = 0xF9,
};

#define IWW_P2P_NOA_DESC_COUNT	(2)

/**
 * stwuct iww_p2p_noa_attw - NOA attw contained in pwobe wesp FW notification
 *
 * @id: attwibute id
 * @wen_wow: wength wow hawf
 * @wen_high: wength high hawf
 * @idx: instance of NoA timing
 * @ctwin: GO's ct window and pwew save capabiwity
 * @desc: NoA descwiptow
 * @wesewved: wesewved fow awignment puwposes
 */
stwuct iww_p2p_noa_attw {
	u8 id;
	u8 wen_wow;
	u8 wen_high;
	u8 idx;
	u8 ctwin;
	stwuct ieee80211_p2p_noa_desc desc[IWW_P2P_NOA_DESC_COUNT];
	u8 wesewved;
} __packed;

#define IWW_PWOBE_WESP_DATA_NO_CSA (0xff)

/**
 * stwuct iww_pwobe_wesp_data_notif - notification with NOA and CSA countew
 *
 * @mac_id: the mac which shouwd send the pwobe wesponse
 * @noa_active: notifies if the noa attwibute shouwd be handwed
 * @noa_attw: P2P NOA attwibute
 * @csa_countew: cuwwent csa countew
 * @wesewved: wesewved fow awignment puwposes
 */
stwuct iww_pwobe_wesp_data_notif {
	__we32 mac_id;
	__we32 noa_active;
	stwuct iww_p2p_noa_attw noa_attw;
	u8 csa_countew;
	u8 wesewved[3];
} __packed; /* PWOBE_WESPONSE_DATA_NTFY_API_S_VEW_1 */

/**
 * stwuct iww_missed_vap_notif - notification of missing vap detection
 *
 * @mac_id: the mac fow which the ucode sends the notification fow
 * @num_beacon_intewvaws_ewapsed: beacons ewpased with no vap pwofiwe inside
 * @pwofiwe_pewiodicity: beacons pewiod to have ouw pwofiwe inside
 * @wesewved: wesewved fow awignment puwposes
 */
stwuct iww_missed_vap_notif {
	__we32 mac_id;
	u8 num_beacon_intewvaws_ewapsed;
	u8 pwofiwe_pewiodicity;
	u8 wesewved[2];
} __packed; /* MISSED_VAP_NTFY_API_S_VEW_1 */

/**
 * stwuct iww_channew_switch_stawt_notif - Channew switch stawt notification
 *
 * @id_and_cowow: ID and cowow of the MAC
 */
stwuct iww_channew_switch_stawt_notif_v1 {
	__we32 id_and_cowow;
} __packed; /* CHANNEW_SWITCH_STAWT_NTFY_API_S_VEW_1 */

/**
 * stwuct iww_channew_switch_stawt_notif - Channew switch stawt notification
 *
 * @wink_id: FW wink id
 */
stwuct iww_channew_switch_stawt_notif {
	__we32 wink_id;
} __packed; /* CHANNEW_SWITCH_STAWT_NTFY_API_S_VEW_3 */

#define CS_EWW_COUNT_EWWOW BIT(0)
#define CS_EWW_WONG_DEWAY_AFTEW_CS BIT(1)
#define CS_EWW_WONG_TX_BWOCK BIT(2)
#define CS_EWW_TX_BWOCK_TIMEW_EXPIWED BIT(3)

/**
 * stwuct iww_channew_switch_ewwow_notif_v1 - Channew switch ewwow notification
 *
 * @mac_id: the mac fow which the ucode sends the notification fow
 * @csa_eww_mask: mask of channew switch ewwow that can occuw
 */
stwuct iww_channew_switch_ewwow_notif_v1 {
	__we32 mac_id;
	__we32 csa_eww_mask;
} __packed; /* CHANNEW_SWITCH_EWWOW_NTFY_API_S_VEW_1 */

/**
 * stwuct iww_channew_switch_ewwow_notif - Channew switch ewwow notification
 *
 * @wink_id: FW wink id
 * @csa_eww_mask: mask of channew switch ewwow that can occuw
 */
stwuct iww_channew_switch_ewwow_notif {
	__we32 wink_id;
	__we32 csa_eww_mask;
} __packed; /* CHANNEW_SWITCH_EWWOW_NTFY_API_S_VEW_2 */

/**
 * stwuct iww_cancew_channew_switch_cmd - Cancew Channew Switch command
 *
 * @id: the id of the wink ow mac that shouwd cancew the channew switch
 */
stwuct iww_cancew_channew_switch_cmd {
	__we32 id;
} __packed; /* MAC_CANCEW_CHANNEW_SWITCH_S_VEW_1 */

/**
 * stwuct iww_chan_switch_te_cmd - Channew Switch Time Event command
 *
 * @mac_id: MAC ID fow channew switch
 * @action: action to pewfowm, see &enum iww_ctxt_action
 * @tsf: beacon tsf
 * @cs_count: channew switch count fwom CSA/eCSA IE
 * @cs_dewayed_bcn_count: if set to N (!= 0) GO/AP can deway N beacon intewvaws
 *	at the new channew aftew the channew switch, othewwise (N == 0) expect
 *	beacon wight aftew the channew switch.
 * @cs_mode: 1 - quiet, 0 - othewwise
 * @wesewved: wesewved fow awignment puwposes
 */
stwuct iww_chan_switch_te_cmd {
	__we32 mac_id;
	__we32 action;
	__we32 tsf;
	u8 cs_count;
	u8 cs_dewayed_bcn_count;
	u8 cs_mode;
	u8 wesewved;
} __packed; /* MAC_CHANNEW_SWITCH_TIME_EVENT_S_VEW_2 */

/**
 * stwuct iww_mac_wow_watency_cmd - set/cweaw mac to 'wow-watency mode'
 *
 * @mac_id: MAC ID to whom to appwy the wow-watency configuwations
 * @wow_watency_wx: 1/0 to set/cweaw Wx wow watency diwection
 * @wow_watency_tx: 1/0 to set/cweaw Tx wow watency diwection
 * @wesewved: wesewved fow awignment puwposes
 */
stwuct iww_mac_wow_watency_cmd {
	__we32 mac_id;
	u8 wow_watency_wx;
	u8 wow_watency_tx;
	__we16 wesewved;
} __packed; /* MAC_WOW_WATENCY_API_S_VEW_1 */

/**
 * stwuct iww_mac_cwient_data - configuwation data fow cwient MAC context
 *
 * @is_assoc: 1 fow associated state, 0 othewwise
 * @esw_twansition_timeout: the timeout wequiwed by the AP fow the
 *	eSW twansition.
 *	Avaiwabwe onwy fwom vewsion 2 of the command.
 *	This vawues comes fwom the EMWSW twansition deway in the EMW
 *	Capabiwities subfiewd.
 * @medium_sync_deway: the vawue as it appeasw in P802.11be_D2.2 Figuwe 9-1002j.
 * @assoc_id: unique ID assigned by the AP duwing association
 * @wesewved1: awignment
 * @data_powicy: see &enum iww_mac_data_powicy
 * @wesewved2: awignment
 * @ctwin: cwient twaffic window in TU (pewiod aftew TBTT when GO is pwesent).
 *	0 indicates that thewe is no CT window.
 */
stwuct iww_mac_cwient_data {
	u8 is_assoc;
	u8 esw_twansition_timeout;
	__we16 medium_sync_deway;

	__we16 assoc_id;
	__we16 wesewved1;
	__we16 data_powicy;
	__we16 wesewved2;
	__we32 ctwin;
} __packed; /* MAC_CONTEXT_CONFIG_CWIENT_DATA_API_S_VEW_2 */

/**
 * stwuct iww_mac_p2p_dev_data  - configuwation data fow P2P device MAC context
 *
 * @is_disc_extended: if set to twue, P2P Device discovewabiwity is enabwed on
 *	othew channews as weww. This shouwd be to twue onwy in case that the
 *	device is discovewabwe and thewe is an active GO. Note that setting this
 *	fiewd when not needed, wiww incwease the numbew of intewwupts and have
 *	effect on the pwatfowm powew, as this setting opens the Wx fiwtews on
 *	aww macs.
 */
stwuct iww_mac_p2p_dev_data {
	__we32 is_disc_extended;
} __packed; /* MAC_CONTEXT_CONFIG_P2P_DEV_DATA_API_S_VEW_1 */

/**
 * enum iww_mac_config_fiwtew_fwags - MAC context configuwation fiwtew fwags
 *
 * @MAC_CFG_FIWTEW_PWOMISC: accept aww data fwames
 * @MAC_CFG_FIWTEW_ACCEPT_CONTWOW_AND_MGMT: pass aww management and
 *	contwow fwames to the host
 * @MAC_CFG_FIWTEW_ACCEPT_GWP: accept muwticast fwames
 * @MAC_CFG_FIWTEW_ACCEPT_BEACON: accept beacon fwames
 * @MAC_CFG_FIWTEW_ACCEPT_BCAST_PWOBE_WESP: accept bwoadcast pwobe wesponse
 * @MAC_CFG_FIWTEW_ACCEPT_PWOBE_WEQ: accept pwobe wequests
 */
enum iww_mac_config_fiwtew_fwags {
	MAC_CFG_FIWTEW_PWOMISC			= BIT(0),
	MAC_CFG_FIWTEW_ACCEPT_CONTWOW_AND_MGMT	= BIT(1),
	MAC_CFG_FIWTEW_ACCEPT_GWP		= BIT(2),
	MAC_CFG_FIWTEW_ACCEPT_BEACON		= BIT(3),
	MAC_CFG_FIWTEW_ACCEPT_BCAST_PWOBE_WESP	= BIT(4),
	MAC_CFG_FIWTEW_ACCEPT_PWOBE_WEQ		= BIT(5),
}; /* MAC_FIWTEW_FWAGS_MASK_E_VEW_1 */

/**
 * stwuct iww_mac_config_cmd - command stwuctuwe to configuwe MAC contexts in
 *	MWD API
 * ( MAC_CONTEXT_CONFIG_CMD = 0x8 )
 *
 * @id_and_cowow: ID and cowow of the MAC
 * @action: action to pewfowm, see &enum iww_ctxt_action
 * @mac_type: one of &enum iww_mac_types
 * @wocaw_mwd_addw: mwd addwess
 * @wesewved_fow_wocaw_mwd_addw: wesewved
 * @fiwtew_fwags: combination of &enum iww_mac_config_fiwtew_fwags
 * @he_suppowt: does this MAC suppowt HE
 * @he_ap_suppowt: HE AP enabwed, "pseudo HE", no twiggew fwame handwing
 * @eht_suppowt: does this MAC suppowt EHT. Wequiwes he_suppowt
 * @nic_not_ack_enabwed: mawk that the NIC doesn't suppowt weceiving
 *	ACK-enabwed AGG, (i.e. both BACK and non-BACK fwames in singwe AGG).
 *	If the NIC is not ACK_ENABWED it may use the EOF-bit in fiwst non-0
 *	wen dewim to detewmine if AGG ow singwe.
 * @cwient: cwient mac data
 * @go_ibss: mac data fow go ow ibss
 * @p2p_dev: mac data fow p2p device
 */
stwuct iww_mac_config_cmd {
	/* COMMON_INDEX_HDW_API_S_VEW_1 */
	__we32 id_and_cowow;
	__we32 action;
	/* MAC_CONTEXT_TYPE_API_E */
	__we32 mac_type;
	u8 wocaw_mwd_addw[6];
	__we16 wesewved_fow_wocaw_mwd_addw;
	__we32 fiwtew_fwags;
	__we16 he_suppowt;
	__we16 he_ap_suppowt;
	__we32 eht_suppowt;
	__we32 nic_not_ack_enabwed;
	/* MAC_CONTEXT_CONFIG_SPECIFIC_DATA_API_U_VEW_2 */
	union {
		stwuct iww_mac_cwient_data cwient;
		stwuct iww_mac_p2p_dev_data p2p_dev;
	};
} __packed; /* MAC_CONTEXT_CONFIG_CMD_API_S_VEW_2 */

/**
 * enum iww_wink_ctx_modify_fwags - indicate to the fw what fiewds awe being
 *	modified in &iww_wink_ctx_cfg_cmd
 *
 * @WINK_CONTEXT_MODIFY_ACTIVE: covews iww_wink_ctx_cfg_cmd::active
 * @WINK_CONTEXT_MODIFY_WATES_INFO: covews iww_wink_ctx_cfg_cmd::cck_wates,
 *	iww_wink_ctx_cfg_cmd::ofdm_wates,
 *	iww_wink_ctx_cfg_cmd::cck_showt_pweambwe,
 *	iww_wink_ctx_cfg_cmd::showt_swot
 * @WINK_CONTEXT_MODIFY_PWOTECT_FWAGS: covews
 *	iww_wink_ctx_cfg_cmd::pwotection_fwags
 * @WINK_CONTEXT_MODIFY_QOS_PAWAMS: covews iww_wink_ctx_cfg_cmd::qos_fwags,
 *	iww_wink_ctx_cfg_cmd::ac,
 * @WINK_CONTEXT_MODIFY_BEACON_TIMING: covews iww_wink_ctx_cfg_cmd::bi,
 *	iww_wink_ctx_cfg_cmd::dtim_intewvaw,
 *	iww_wink_ctx_cfg_cmd::dtim_time,
 *	iww_wink_ctx_cfg_cmd::dtim_tsf,
 *	iww_wink_ctx_cfg_cmd::assoc_beacon_awwive_time.
 *	This fwag can be set onwy once aftew assoc.
 * @WINK_CONTEXT_MODIFY_HE_PAWAMS: covews
 *	iww_wink_ctx_cfg_cmd::htc_twig_based_pkt_ext
 *	iww_wink_ctx_cfg_cmd::wand_awwoc_ecwmin,
 *	iww_wink_ctx_cfg_cmd::wand_awwoc_ecwmax,
 *	iww_wink_ctx_cfg_cmd::twig_based_txf,
 *	iww_wink_ctx_cfg_cmd::bss_cowow,
 *	iww_wink_ctx_cfg_cmd::ndp_fdbk_buff_th_exp,
 *	iww_wink_ctx_cfg_cmd::wef_bssid_addw
 *	iww_wink_ctx_cfg_cmd::bssid_index,
 *	iww_wink_ctx_cfg_cmd::fwame_time_wts_th.
 *	This fwag can be set any time.
 * @WINK_CONTEXT_MODIFY_BSS_COWOW_DISABWE: covews
 *	iww_wink_ctx_cfg_cmd::bss_cowow_disabwe
 * @WINK_CONTEXT_MODIFY_EHT_PAWAMS: covews iww_wink_ctx_cfg_cmd::punctuwe_mask.
 *	This fwag can be set onwy if the MAC that this wink wewates to has
 *	eht_suppowt set to twue.
 * @WINK_CONTEXT_MODIFY_AWW: set aww above fwags
 */
enum iww_wink_ctx_modify_fwags {
	WINK_CONTEXT_MODIFY_ACTIVE		= BIT(0),
	WINK_CONTEXT_MODIFY_WATES_INFO		= BIT(1),
	WINK_CONTEXT_MODIFY_PWOTECT_FWAGS	= BIT(2),
	WINK_CONTEXT_MODIFY_QOS_PAWAMS		= BIT(3),
	WINK_CONTEXT_MODIFY_BEACON_TIMING	= BIT(4),
	WINK_CONTEXT_MODIFY_HE_PAWAMS		= BIT(5),
	WINK_CONTEXT_MODIFY_BSS_COWOW_DISABWE	= BIT(6),
	WINK_CONTEXT_MODIFY_EHT_PAWAMS		= BIT(7),
	WINK_CONTEXT_MODIFY_AWW			= 0xff,
}; /* WINK_CONTEXT_MODIFY_MASK_E_VEW_1 */

/**
 * enum iww_wink_ctx_pwotection_fwags - wink pwotection fwags
 * @WINK_PWOT_FWG_TGG_PWOTECT: 11g pwotection when twansmitting OFDM fwames,
 *	this wiww wequiwe CCK WTS/CTS2sewf.
 *	WTS/CTS wiww pwotect fuww buwst time.
 * @WINK_PWOT_FWG_HT_PWOT: enabwe HT pwotection
 * @WINK_PWOT_FWG_FAT_PWOT: pwotect 40 MHz twansmissions
 * @WINK_PWOT_FWG_SEWF_CTS_EN: awwow CTS2sewf
 */
enum iww_wink_ctx_pwotection_fwags {
	WINK_PWOT_FWG_TGG_PWOTECT	= BIT(0),
	WINK_PWOT_FWG_HT_PWOT		= BIT(1),
	WINK_PWOT_FWG_FAT_PWOT		= BIT(2),
	WINK_PWOT_FWG_SEWF_CTS_EN	= BIT(3),
}; /* WINK_PWOTECT_FWAGS_E_VEW_1 */

/**
 * enum iww_wink_ctx_fwags - wink context fwags
 *
 * @WINK_FWG_BSS_COWOW_DIS: BSS cowow disabwe, don't use the BSS
 *	cowow fow WX fiwtew but use MAC headew
 *	enabwed AGG, i.e. both BACK and non-BACK fwames in a singwe AGG
 * @WINK_FWG_MU_EDCA_CW: indicates that thewe is an ewement of MU EDCA
 *	pawametew set, i.e. the backoff countews fow twig-based ACs
 * @WINK_FWG_WU_2MHZ_BWOCK: indicates that 26-tone WU OFDMA twansmission awe
 *      not awwowed (as thewe awe OBSS that might cwassify such twansmissions as
 *      wadaw puwses).
 * @WINK_FWG_NDP_FEEDBACK_ENABWED: mawk suppowt fow NDP feedback and change
 *	of thweshowd
 */
enum iww_wink_ctx_fwags {
	WINK_FWG_BSS_COWOW_DIS		= BIT(0),
	WINK_FWG_MU_EDCA_CW		= BIT(1),
	WINK_FWG_WU_2MHZ_BWOCK		= BIT(2),
	WINK_FWG_NDP_FEEDBACK_ENABWED	= BIT(3),
}; /* WINK_CONTEXT_FWAG_E_VEW_1 */

/**
 * stwuct iww_wink_config_cmd - command stwuctuwe to configuwe the WINK context
 *	in MWD API
 * ( WINK_CONFIG_CMD =0x9 )
 *
 * @action: action to pewfowm, see &enum iww_ctxt_action
 * @wink_id: the id of the wink that this cmd configuwes
 * @mac_id: intewface ID. Wewevant onwy if action is FW_CTXT_ACTION_ADD
 * @phy_id: PHY index. Can be changed onwy if the wink was inactive
 *	(and stays inactive). If the wink is active (ow becomes active),
 *	this fiewd is ignowed.
 * @wocaw_wink_addw: the winks MAC addwess. Can be changed onwy if the wink was
 *	inactive (and stays inactive). If the wink is active
 *	(ow becomes active), this fiewd is ignowed.
 * @wesewved_fow_wocaw_wink_addw: wesewved
 * @modify_mask: fwom &enum iww_wink_ctx_modify_fwags, sewects what to change.
 *	Wewevant onwy if action is FW_CTXT_ACTION_MODIFY
 * @active: indicates whethew the wink is active ow not
 * @wisten_wmac: indicates whethew the wink shouwd be awwocated on the Wisten
 *	Wmac ow on the Main Wmac. Cannot be changed on an active Wink.
 *	Wewevant onwy fow eSW.
 * @cck_wates: basic wates avaiwabwe fow CCK
 * @ofdm_wates: basic wates avaiwabwe fow OFDM
 * @cck_showt_pweambwe: 1 fow enabwing showt pweambwe, 0 othewwise
 * @showt_swot: 1 fow enabwing showt swots, 0 othewwise
 * @pwotection_fwags: combination of &enum iww_wink_ctx_pwotection_fwags
 * @qos_fwags: fwom &enum iww_mac_qos_fwags
 * @ac: one iww_mac_qos configuwation fow each AC
 * @htc_twig_based_pkt_ext: defauwt PE in 4us units
 * @wand_awwoc_ecwmin: wandom CWmin = 2**ECWmin-1
 * @wand_awwoc_ecwmax: wandom CWmax = 2**ECWmax-1
 * @ndp_fdbk_buff_th_exp: set exponent fow the NDP feedback buffewed thweshowd
 * @twig_based_txf: MU EDCA Pawametew set fow the twiggew based twaffic queues
 * @bi: beacon intewvaw in TU, appwicabwe onwy when associated
 * @dtim_intewvaw: DTIM intewvaw in TU.
 *	Wewevant onwy fow GO, othewwise this is offwoaded.
 * @punctuwe_mask: punctuwe mask fow EHT
 * @fwame_time_wts_th: HE duwation WTS thweshowd, in units of 32us
 * @fwags: a combination fwom &enum iww_wink_ctx_fwags
 * @fwags_mask: what of %fwags have changed. Awso &enum iww_wink_ctx_fwags
 * Bewow fiewds awe fow muwti-bssid:
 * @wef_bssid_addw: wefewence BSSID used by the AP
 * @wesewved_fow_wef_bssid_addw: wesewved
 * @bssid_index: index of the associated VAP
 * @bss_cowow: 11ax AP ID that is used in the HE SIG-A to mawk intew BSS fwame
 * @spec_wink_id: wink_id as the AP knows it
 * @wesewved: awignment
 * @ibss_bssid_addw: bssid fow ibss
 * @wesewved_fow_ibss_bssid_addw: wesewved
 * @wesewved1: wesewved fow futuwe use
 */
stwuct iww_wink_config_cmd {
	__we32 action;
	__we32 wink_id;
	__we32 mac_id;
	__we32 phy_id;
	u8 wocaw_wink_addw[6];
	__we16 wesewved_fow_wocaw_wink_addw;
	__we32 modify_mask;
	__we32 active;
	__we32 wisten_wmac;
	__we32 cck_wates;
	__we32 ofdm_wates;
	__we32 cck_showt_pweambwe;
	__we32 showt_swot;
	__we32 pwotection_fwags;
	/* MAC_QOS_PAWAM_API_S_VEW_1 */
	__we32 qos_fwags;
	stwuct iww_ac_qos ac[AC_NUM + 1];
	u8 htc_twig_based_pkt_ext;
	u8 wand_awwoc_ecwmin;
	u8 wand_awwoc_ecwmax;
	u8 ndp_fdbk_buff_th_exp;
	stwuct iww_he_backoff_conf twig_based_txf[AC_NUM];
	__we32 bi;
	__we32 dtim_intewvaw;
	__we16 punctuwe_mask;
	__we16 fwame_time_wts_th;
	__we32 fwags;
	__we32 fwags_mask;
	/* The bewow fiewds awe fow muwti-bssid */
	u8 wef_bssid_addw[6];
	__we16 wesewved_fow_wef_bssid_addw;
	u8 bssid_index;
	u8 bss_cowow;
	u8 spec_wink_id;
	u8 wesewved;
	u8 ibss_bssid_addw[6];
	__we16 wesewved_fow_ibss_bssid_addw;
	__we32 wesewved1[8];
} __packed; /* WINK_CONTEXT_CONFIG_CMD_API_S_VEW_1 */

/* Cuwwentwy FW suppowts wink ids in the wange 0-3 and can have
 * at most two active winks fow each vif.
 */
#define IWW_MVM_FW_MAX_ACTIVE_WINKS_NUM 2
#define IWW_MVM_FW_MAX_WINK_ID 3

/**
 * enum iww_fw_sta_type - FW station types
 * @STATION_TYPE_PEEW: wepwesents a peew - AP in BSS, a TDWS sta, a cwient in
 *	P2P.
 * @STATION_TYPE_BCAST_MGMT: The station used to send beacons and
 *	pwobe wesponses. Awso used fow twaffic injection in sniffew mode
 * @STATION_TYPE_MCAST: the station used fow BCAST / MCAST in GO. Wiww be
 *	suspended / wesumed at the wight timing depending on the cwients'
 *	powew save state and the DTIM timing
 * @STATION_TYPE_AUX: aux sta. In the FW thewe is no need fow a speciaw type
 *	fow the aux sta, so this type is onwy fow dwivew - intewnaw use.
 */
enum iww_fw_sta_type {
	STATION_TYPE_PEEW,
	STATION_TYPE_BCAST_MGMT,
	STATION_TYPE_MCAST,
	STATION_TYPE_AUX,
}; /* STATION_TYPE_E_VEW_1 */

/**
 * stwuct iww_mvm_sta_cfg_cmd - cmd stwuctuwe to add a peew sta to the uCode's
 *	station tabwe
 * ( STA_CONFIG_CMD = 0xA )
 *
 * @sta_id: index of station in uCode's station tabwe
 * @wink_id: the id of the wink that is used to communicate with this sta
 * @peew_mwd_addwess: the peews mwd addwess
 * @wesewved_fow_peew_mwd_addwess: wesewved
 * @peew_wink_addwess: the addwess of the wink that is used to communicate
 *	with this sta
 * @wesewved_fow_peew_wink_addwess: wesewved
 * @station_type: type of this station. See &enum iww_fw_sta_type
 * @assoc_id: fow GO onwy
 * @beamfowm_fwags: beam fowming contwows
 * @mfp: indicates whethew the STA uses management fwame pwotection ow not.
 * @mimo: indicates whethew the sta uses mimo ow not
 * @mimo_pwotection: indicates whethew the sta uses mimo pwotection ow not
 * @ack_enabwed: indicates that the AP suppowts weceiving ACK-
 *	enabwed AGG, i.e. both BACK and non-BACK fwames in a singwe AGG
 * @twig_wnd_awwoc: indicates that twiggew based wandom awwocation
 *	is enabwed accowding to UOWA ewement existence
 * @tx_ampdu_spacing: minimum A-MPDU spacing:
 *	4 - 2us density, 5 - 4us density, 6 - 8us density, 7 - 16us density
 * @tx_ampdu_max_size: maximum A-MPDU wength: 0 - 8K, 1 - 16K, 2 - 32K,
 *	3 - 64K, 4 - 128K, 5 - 256K, 6 - 512K, 7 - 1024K.
 * @sp_wength: the size of the SP in actuaw numbew of fwames
 * @uapsd_acs:  4 WS bits awe twiggew enabwed ACs, 4 MS bits awe the dewivew
 *	enabwed ACs.
 * @pkt_ext: optionaw, exists accowding to PPE-pwesent bit in the HE/EHT-PHY
 *	capa
 * @htc_fwags: which featuwes awe suppowted in HTC
 */
stwuct iww_mvm_sta_cfg_cmd {
	__we32 sta_id;
	__we32 wink_id;
	u8 peew_mwd_addwess[ETH_AWEN];
	__we16 wesewved_fow_peew_mwd_addwess;
	u8 peew_wink_addwess[ETH_AWEN];
	__we16 wesewved_fow_peew_wink_addwess;
	__we32 station_type;
	__we32 assoc_id;
	__we32 beamfowm_fwags;
	__we32 mfp;
	__we32 mimo;
	__we32 mimo_pwotection;
	__we32 ack_enabwed;
	__we32 twig_wnd_awwoc;
	__we32 tx_ampdu_spacing;
	__we32 tx_ampdu_max_size;
	__we32 sp_wength;
	__we32 uapsd_acs;
	stwuct iww_he_pkt_ext_v2 pkt_ext;
	__we32 htc_fwags;
} __packed; /* STA_CMD_API_S_VEW_1 */

/**
 * stwuct iww_mvm_aux_sta_cmd - command fow AUX STA configuwation
 * ( AUX_STA_CMD = 0xB )
 *
 * @sta_id: index of aux sta to configuwe
 * @wmac_id: ?
 * @mac_addw: mac addw of the auxiwawy sta
 * @wesewved_fow_mac_addw: wesewved
 */
stwuct iww_mvm_aux_sta_cmd {
	__we32 sta_id;
	__we32 wmac_id;
	u8 mac_addw[ETH_AWEN];
	__we16 wesewved_fow_mac_addw;

} __packed; /* AUX_STA_CMD_API_S_VEW_1 */

/**
 * stwuct iww_mvm_wemove_sta_cmd - a cmd stwuctuwe to wemove a sta added by
 *	STA_CONFIG_CMD ow AUX_STA_CONFIG_CMD
 * ( STA_WEMOVE_CMD = 0xC )
 *
 * @sta_id: index of station to wemove
 */
stwuct iww_mvm_wemove_sta_cmd {
	__we32 sta_id;
} __packed; /* WEMOVE_STA_API_S_VEW_1 */

/**
 * stwuct iww_mvm_sta_disabwe_tx_cmd - disabwe / we-enabwe tx to a sta
 * ( STA_DISABWE_TX_CMD = 0xD )
 *
 * @sta_id: index of the station to disabwe tx to
 * @disabwe: indicates if to disabwe ow we-enabwe tx
 */
stwuct iww_mvm_sta_disabwe_tx_cmd {
	__we32 sta_id;
	__we32 disabwe;
} __packed; /* STA_DISABWE_TX_API_S_VEW_1 */

#endif /* __iww_fw_api_mac_cfg_h__ */
