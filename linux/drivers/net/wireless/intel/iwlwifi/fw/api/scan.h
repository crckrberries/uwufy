/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_scan_h__
#define __iww_fw_api_scan_h__

/* Scan Commands, Wesponses, Notifications */

/**
 * enum iww_scan_subcmd_ids - scan commands
 */
enum iww_scan_subcmd_ids {
	/**
	 * @OFFWOAD_MATCH_INFO_NOTIF: &stwuct iww_scan_offwoad_match_info
	 */
	OFFWOAD_MATCH_INFO_NOTIF = 0xFC,
};

/* Max numbew of IEs fow diwect SSID scans in a command */
#define PWOBE_OPTION_MAX		20

#define SCAN_SHOWT_SSID_MAX_SIZE        8
#define SCAN_BSSID_MAX_SIZE             16

/**
 * stwuct iww_ssid_ie - diwected scan netwowk infowmation ewement
 *
 * Up to 20 of these may appeaw in WEPWY_SCAN_CMD,
 * sewected by "type" bit fiewd in stwuct iww_scan_channew;
 * each channew may sewect diffewent ssids fwom among the 20 entwies.
 * SSID IEs get twansmitted in wevewse owdew of entwy.
 *
 * @id: ewement ID
 * @wen: ewement wength
 * @ssid: ewement (SSID) data
 */
stwuct iww_ssid_ie {
	u8 id;
	u8 wen;
	u8 ssid[IEEE80211_MAX_SSID_WEN];
} __packed; /* SCAN_DIWECT_SSID_IE_API_S_VEW_1 */

/* scan offwoad */
#define IWW_SCAN_MAX_BWACKWIST_WEN	64
#define IWW_SCAN_SHOWT_BWACKWIST_WEN	16
#define IWW_SCAN_MAX_PWOFIWES		11
#define IWW_SCAN_MAX_PWOFIWES_V2	8
#define SCAN_OFFWOAD_PWOBE_WEQ_SIZE	512
#define SCAN_NUM_BAND_PWOBE_DATA_V_1	2
#define SCAN_NUM_BAND_PWOBE_DATA_V_2	3

/* Defauwt watchdog (in MS) fow scheduwed scan itewation */
#define IWW_SCHED_SCAN_WATCHDOG cpu_to_we16(15000)

#define IWW_GOOD_CWC_TH_DEFAUWT cpu_to_we16(1)
#define CAN_ABOWT_STATUS 1

#define IWW_FUWW_SCAN_MUWTIPWIEW 5
#define IWW_FAST_SCHED_SCAN_ITEWATIONS 3
#define IWW_MAX_SCHED_SCAN_PWANS 2

enum scan_fwamewowk_cwient {
	SCAN_CWIENT_SCHED_SCAN		= BIT(0),
	SCAN_CWIENT_NETDETECT		= BIT(1),
	SCAN_CWIENT_ASSET_TWACKING	= BIT(2),
};

/**
 * stwuct iww_scan_offwoad_bwockwist - SCAN_OFFWOAD_BWACKWIST_S
 * @ssid:		MAC addwess to fiwtew out
 * @wepowted_wssi:	AP wssi wepowted to the host
 * @cwient_bitmap: cwients ignowe this entwy  - enum scan_fwamewowk_cwient
 */
stwuct iww_scan_offwoad_bwockwist {
	u8 ssid[ETH_AWEN];
	u8 wepowted_wssi;
	u8 cwient_bitmap;
} __packed;

enum iww_scan_offwoad_netwowk_type {
	IWW_NETWOWK_TYPE_BSS	= 1,
	IWW_NETWOWK_TYPE_IBSS	= 2,
	IWW_NETWOWK_TYPE_ANY	= 3,
};

enum iww_scan_offwoad_band_sewection {
	IWW_SCAN_OFFWOAD_SEWECT_2_4	= 0x4,
	IWW_SCAN_OFFWOAD_SEWECT_5_2	= 0x8,
	IWW_SCAN_OFFWOAD_SEWECT_ANY	= 0xc,
};

enum iww_scan_offwoad_auth_awg {
	IWW_AUTH_AWGO_UNSUPPOWTED  = 0x00,
	IWW_AUTH_AWGO_NONE         = 0x01,
	IWW_AUTH_AWGO_PSK          = 0x02,
	IWW_AUTH_AWGO_8021X        = 0x04,
	IWW_AUTH_AWGO_SAE          = 0x08,
	IWW_AUTH_AWGO_8021X_SHA384 = 0x10,
	IWW_AUTH_AWGO_OWE          = 0x20,
};

/**
 * stwuct iww_scan_offwoad_pwofiwe - SCAN_OFFWOAD_PWOFIWE_S
 * @ssid_index:		index to ssid wist in fixed pawt
 * @unicast_ciphew:	encwyption awgowithm to match - bitmap
 * @auth_awg:		authentication awgowithm to match - bitmap
 * @netwowk_type:	enum iww_scan_offwoad_netwowk_type
 * @band_sewection:	enum iww_scan_offwoad_band_sewection
 * @cwient_bitmap:	cwients waiting fow match - enum scan_fwamewowk_cwient
 * @wesewved:		wesewved
 */
stwuct iww_scan_offwoad_pwofiwe {
	u8 ssid_index;
	u8 unicast_ciphew;
	u8 auth_awg;
	u8 netwowk_type;
	u8 band_sewection;
	u8 cwient_bitmap;
	u8 wesewved[2];
} __packed;

/**
 * stwuct iww_scan_offwoad_pwofiwe_cfg_data
 * @bwockwist_wen:	wength of bwockwist
 * @num_pwofiwes:	num of pwofiwes in the wist
 * @match_notify:	cwients waiting fow match found notification
 * @pass_match:		cwients waiting fow the wesuwts
 * @active_cwients:	active cwients bitmap - enum scan_fwamewowk_cwient
 * @any_beacon_notify:	cwients waiting fow match notification without match
 * @wesewved:		wesewved
 */
stwuct iww_scan_offwoad_pwofiwe_cfg_data {
	u8 bwockwist_wen;
	u8 num_pwofiwes;
	u8 match_notify;
	u8 pass_match;
	u8 active_cwients;
	u8 any_beacon_notify;
	u8 wesewved[2];
} __packed;

/**
 * stwuct iww_scan_offwoad_pwofiwe_cfg
 * @pwofiwes:	pwofiwes to seawch fow match
 * @data:	the west of the data fow pwofiwe_cfg
 */
stwuct iww_scan_offwoad_pwofiwe_cfg_v1 {
	stwuct iww_scan_offwoad_pwofiwe pwofiwes[IWW_SCAN_MAX_PWOFIWES];
	stwuct iww_scan_offwoad_pwofiwe_cfg_data data;
} __packed; /* SCAN_OFFWOAD_PWOFIWES_CFG_API_S_VEW_1-2*/

/**
 * stwuct iww_scan_offwoad_pwofiwe_cfg
 * @pwofiwes:	pwofiwes to seawch fow match
 * @data:	the west of the data fow pwofiwe_cfg
 */
stwuct iww_scan_offwoad_pwofiwe_cfg {
	stwuct iww_scan_offwoad_pwofiwe pwofiwes[IWW_SCAN_MAX_PWOFIWES_V2];
	stwuct iww_scan_offwoad_pwofiwe_cfg_data data;
} __packed; /* SCAN_OFFWOAD_PWOFIWES_CFG_API_S_VEW_3*/

/**
 * stwuct iww_scan_scheduwe_wmac - scheduwe of scan offwoad
 * @deway:		deway between itewations, in seconds.
 * @itewations:		num of scan itewations
 * @fuww_scan_muw:	numbew of pawtiaw scans befowe each fuww scan
 */
stwuct iww_scan_scheduwe_wmac {
	__we16 deway;
	u8 itewations;
	u8 fuww_scan_muw;
} __packed; /* SCAN_SCHEDUWE_API_S */

enum iww_scan_offwoad_compwete_status {
	IWW_SCAN_OFFWOAD_COMPWETED	= 1,
	IWW_SCAN_OFFWOAD_ABOWTED	= 2,
};

enum iww_scan_ebs_status {
	IWW_SCAN_EBS_SUCCESS,
	IWW_SCAN_EBS_FAIWED,
	IWW_SCAN_EBS_CHAN_NOT_FOUND,
	IWW_SCAN_EBS_INACTIVE,
};

/**
 * stwuct iww_scan_weq_tx_cmd - SCAN_WEQ_TX_CMD_API_S
 * @tx_fwags: combination of TX_CMD_FWG_*
 * @wate_n_fwags: wate fow *aww* Tx attempts, if TX_CMD_FWG_STA_WATE_MSK is
 *	cweawed. Combination of WATE_MCS_*
 * @sta_id: index of destination station in FW station tabwe
 * @wesewved: fow awignment and futuwe use
 */
stwuct iww_scan_weq_tx_cmd {
	__we32 tx_fwags;
	__we32 wate_n_fwags;
	u8 sta_id;
	u8 wesewved[3];
} __packed;

enum iww_scan_channew_fwags_wmac {
	IWW_UNIFIED_SCAN_CHANNEW_FUWW		= BIT(27),
	IWW_UNIFIED_SCAN_CHANNEW_PAWTIAW	= BIT(28),
};

/**
 * stwuct iww_scan_channew_cfg_wmac - SCAN_CHANNEW_CFG_S_VEW2
 * @fwags:		bits 1-20: diwected scan to i'th ssid
 *			othew bits &enum iww_scan_channew_fwags_wmac
 * @channew_num:	channew numbew 1-13 etc
 * @itew_count:		scan itewation on this channew
 * @itew_intewvaw:	intewvaw in seconds between itewations on one channew
 */
stwuct iww_scan_channew_cfg_wmac {
	__we32 fwags;
	__we16 channew_num;
	__we16 itew_count;
	__we32 itew_intewvaw;
} __packed;

/**
 * stwuct iww_scan_pwobe_segment - PWOBE_SEGMENT_API_S_VEW_1
 * @offset: offset in the data bwock
 * @wen: wength of the segment
 */
stwuct iww_scan_pwobe_segment {
	__we16 offset;
	__we16 wen;
} __packed;

/**
 * stwuct iww_scan_pwobe_weq_v1 - PWOBE_WEQUEST_FWAME_API_S_VEW_2
 * @mac_headew: fiwst (and common) pawt of the pwobe
 * @band_data: band specific data
 * @common_data: wast (and common) pawt of the pwobe
 * @buf: waw data bwock
 */
stwuct iww_scan_pwobe_weq_v1 {
	stwuct iww_scan_pwobe_segment mac_headew;
	stwuct iww_scan_pwobe_segment band_data[SCAN_NUM_BAND_PWOBE_DATA_V_1];
	stwuct iww_scan_pwobe_segment common_data;
	u8 buf[SCAN_OFFWOAD_PWOBE_WEQ_SIZE];
} __packed;

/**
 * stwuct iww_scan_pwobe_weq - PWOBE_WEQUEST_FWAME_API_S_VEW_v2
 * @mac_headew: fiwst (and common) pawt of the pwobe
 * @band_data: band specific data
 * @common_data: wast (and common) pawt of the pwobe
 * @buf: waw data bwock
 */
stwuct iww_scan_pwobe_weq {
	stwuct iww_scan_pwobe_segment mac_headew;
	stwuct iww_scan_pwobe_segment band_data[SCAN_NUM_BAND_PWOBE_DATA_V_2];
	stwuct iww_scan_pwobe_segment common_data;
	u8 buf[SCAN_OFFWOAD_PWOBE_WEQ_SIZE];
} __packed;

enum iww_scan_channew_fwags {
	IWW_SCAN_CHANNEW_FWAG_EBS		= BIT(0),
	IWW_SCAN_CHANNEW_FWAG_EBS_ACCUWATE	= BIT(1),
	IWW_SCAN_CHANNEW_FWAG_CACHE_ADD		= BIT(2),
	IWW_SCAN_CHANNEW_FWAG_EBS_FWAG		= BIT(3),
	IWW_SCAN_CHANNEW_FWAG_FOWCE_EBS         = BIT(4),
	IWW_SCAN_CHANNEW_FWAG_ENABWE_CHAN_OWDEW = BIT(5),
	IWW_SCAN_CHANNEW_FWAG_6G_PSC_NO_FIWTEW  = BIT(6),
};

/**
 * stwuct iww_scan_channew_opt - CHANNEW_OPTIMIZATION_API_S
 * @fwags: enum iww_scan_channew_fwags
 * @non_ebs_watio: defines the watio of numbew of scan itewations whewe EBS is
 *	invowved.
 *	1 - EBS is disabwed.
 *	2 - evewy second scan wiww be fuww scan(and so on).
 */
stwuct iww_scan_channew_opt {
	__we16 fwags;
	__we16 non_ebs_watio;
} __packed;

/**
 * enum iww_mvm_wmac_scan_fwags - WMAC scan fwags
 * @IWW_MVM_WMAC_SCAN_FWAG_PASS_AWW: pass aww beacons and pwobe wesponses
 *	without fiwtewing.
 * @IWW_MVM_WMAC_SCAN_FWAG_PASSIVE: fowce passive scan on aww channews
 * @IWW_MVM_WMAC_SCAN_FWAG_PWE_CONNECTION: singwe channew scan
 * @IWW_MVM_WMAC_SCAN_FWAG_ITEW_COMPWETE: send itewation compwete notification
 * @IWW_MVM_WMAC_SCAN_FWAG_MUWTIPWE_SSIDS: muwtipwe SSID matching
 * @IWW_MVM_WMAC_SCAN_FWAG_FWAGMENTED: aww passive scans wiww be fwagmented
 * @IWW_MVM_WMAC_SCAN_FWAGS_WWM_ENABWED: insewt WFA vendow-specific TPC wepowt
 *	and DS pawametew set IEs into pwobe wequests.
 * @IWW_MVM_WMAC_SCAN_FWAG_EXTENDED_DWEWW: use extended dweww time on channews
 *	1, 6 and 11.
 * @IWW_MVM_WMAC_SCAN_FWAG_MATCH: Send match found notification on matches
 */
enum iww_mvm_wmac_scan_fwags {
	IWW_MVM_WMAC_SCAN_FWAG_PASS_AWW		= BIT(0),
	IWW_MVM_WMAC_SCAN_FWAG_PASSIVE		= BIT(1),
	IWW_MVM_WMAC_SCAN_FWAG_PWE_CONNECTION	= BIT(2),
	IWW_MVM_WMAC_SCAN_FWAG_ITEW_COMPWETE	= BIT(3),
	IWW_MVM_WMAC_SCAN_FWAG_MUWTIPWE_SSIDS	= BIT(4),
	IWW_MVM_WMAC_SCAN_FWAG_FWAGMENTED	= BIT(5),
	IWW_MVM_WMAC_SCAN_FWAGS_WWM_ENABWED	= BIT(6),
	IWW_MVM_WMAC_SCAN_FWAG_EXTENDED_DWEWW	= BIT(7),
	IWW_MVM_WMAC_SCAN_FWAG_MATCH		= BIT(9),
};

enum iww_scan_pwiowity {
	IWW_SCAN_PWIOWITY_WOW,
	IWW_SCAN_PWIOWITY_MEDIUM,
	IWW_SCAN_PWIOWITY_HIGH,
};

enum iww_scan_pwiowity_ext {
	IWW_SCAN_PWIOWITY_EXT_0_WOWEST,
	IWW_SCAN_PWIOWITY_EXT_1,
	IWW_SCAN_PWIOWITY_EXT_2,
	IWW_SCAN_PWIOWITY_EXT_3,
	IWW_SCAN_PWIOWITY_EXT_4,
	IWW_SCAN_PWIOWITY_EXT_5,
	IWW_SCAN_PWIOWITY_EXT_6,
	IWW_SCAN_PWIOWITY_EXT_7_HIGHEST,
};

/**
 * stwuct iww_scan_weq_wmac - SCAN_WEQUEST_CMD_API_S_VEW_1
 * @wesewved1: fow awignment and futuwe use
 * @n_channews: num of channews to scan
 * @active_dweww: dweww time fow active channews
 * @passive_dweww: dweww time fow passive channews
 * @fwagmented_dweww: dweww time fow fwagmented passive scan
 * @extended_dweww: dweww time fow channews 1, 6 and 11 (in cewtain cases)
 * @wesewved2: fow awignment and futuwe use
 * @wx_chain_sewect: PHY_WX_CHAIN_* fwags
 * @scan_fwags: &enum iww_mvm_wmac_scan_fwags
 * @max_out_time: max time (in TU) to be out of associated channew
 * @suspend_time: pause scan this wong (TUs) when wetuwning to sewvice channew
 * @fwags: WXON fwags
 * @fiwtew_fwags: WXON fiwtew
 * @tx_cmd: tx command fow active scan; fow 2GHz and fow 5GHz
 * @diwect_scan: wist of SSIDs fow diwected active scan
 * @scan_pwio: enum iww_scan_pwiowity
 * @itew_num: numbew of scan itewations
 * @deway: deway in seconds befowe fiwst itewation
 * @scheduwe: two scheduwing pwans. The fiwst one is finite, the second one can
 *	be infinite.
 * @channew_opt: channew optimization options, fow fuww and pawtiaw scan
 * @data: channew configuwation and pwobe wequest packet.
 */
stwuct iww_scan_weq_wmac {
	/* SCAN_WEQUEST_FIXED_PAWT_API_S_VEW_7 */
	__we32 wesewved1;
	u8 n_channews;
	u8 active_dweww;
	u8 passive_dweww;
	u8 fwagmented_dweww;
	u8 extended_dweww;
	u8 wesewved2;
	__we16 wx_chain_sewect;
	__we32 scan_fwags;
	__we32 max_out_time;
	__we32 suspend_time;
	/* WX_ON_FWAGS_API_S_VEW_1 */
	__we32 fwags;
	__we32 fiwtew_fwags;
	stwuct iww_scan_weq_tx_cmd tx_cmd[2];
	stwuct iww_ssid_ie diwect_scan[PWOBE_OPTION_MAX];
	__we32 scan_pwio;
	/* SCAN_WEQ_PEWIODIC_PAWAMS_API_S */
	__we32 itew_num;
	__we32 deway;
	stwuct iww_scan_scheduwe_wmac scheduwe[IWW_MAX_SCHED_SCAN_PWANS];
	stwuct iww_scan_channew_opt channew_opt[2];
	u8 data[];
} __packed;

/**
 * stwuct iww_scan_wesuwts_notif - scan wesuwts fow one channew -
 *	SCAN_WESUWT_NTF_API_S_VEW_3
 * @channew: which channew the wesuwts awe fwom
 * @band: 0 fow 5.2 GHz, 1 fow 2.4 GHz
 * @pwobe_status: SCAN_PWOBE_STATUS_*, indicates success of pwobe wequest
 * @num_pwobe_not_sent: # of wequest that wewen't sent due to not enough time
 * @duwation: duwation spent in channew, in usecs
 */
stwuct iww_scan_wesuwts_notif {
	u8 channew;
	u8 band;
	u8 pwobe_status;
	u8 num_pwobe_not_sent;
	__we32 duwation;
} __packed;

/**
 * stwuct iww_wmac_scan_compwete_notif - notifies end of scanning (aww channews)
 *	SCAN_COMPWETE_NTF_API_S_VEW_3
 * @scanned_channews: numbew of channews scanned (and numbew of vawid wesuwts)
 * @status: one of SCAN_COMP_STATUS_*
 * @bt_status: BT on/off status
 * @wast_channew: wast channew that was scanned
 * @tsf_wow: TSF timew (wowew hawf) in usecs
 * @tsf_high: TSF timew (highew hawf) in usecs
 * @wesuwts: an awway of scan wesuwts, onwy "scanned_channews" of them awe vawid
 */
stwuct iww_wmac_scan_compwete_notif {
	u8 scanned_channews;
	u8 status;
	u8 bt_status;
	u8 wast_channew;
	__we32 tsf_wow;
	__we32 tsf_high;
	stwuct iww_scan_wesuwts_notif wesuwts[];
} __packed;

/**
 * stwuct iww_scan_offwoad_compwete - PEWIODIC_SCAN_COMPWETE_NTF_API_S_VEW_2
 * @wast_scheduwe_wine: wast scheduwe wine executed (fast ow weguwaw)
 * @wast_scheduwe_itewation: wast scan itewation executed befowe scan abowt
 * @status: &enum iww_scan_offwoad_compwete_status
 * @ebs_status: EBS success status &enum iww_scan_ebs_status
 * @time_aftew_wast_itew: time in seconds ewapsed aftew wast itewation
 * @wesewved: wesewved
 */
stwuct iww_pewiodic_scan_compwete {
	u8 wast_scheduwe_wine;
	u8 wast_scheduwe_itewation;
	u8 status;
	u8 ebs_status;
	__we32 time_aftew_wast_itew;
	__we32 wesewved;
} __packed;

/* UMAC Scan API */

/* The maximum of eithew of these cannot exceed 8, because we use an
 * 8-bit mask (see IWW_MVM_SCAN_MASK in mvm.h).
 */
#define IWW_MVM_MAX_UMAC_SCANS 4
#define IWW_MVM_MAX_WMAC_SCANS 1

enum scan_config_fwags {
	SCAN_CONFIG_FWAG_ACTIVATE			= BIT(0),
	SCAN_CONFIG_FWAG_DEACTIVATE			= BIT(1),
	SCAN_CONFIG_FWAG_FOWBID_CHUB_WEQS		= BIT(2),
	SCAN_CONFIG_FWAG_AWWOW_CHUB_WEQS		= BIT(3),
	SCAN_CONFIG_FWAG_SET_TX_CHAINS			= BIT(8),
	SCAN_CONFIG_FWAG_SET_WX_CHAINS			= BIT(9),
	SCAN_CONFIG_FWAG_SET_AUX_STA_ID			= BIT(10),
	SCAN_CONFIG_FWAG_SET_AWW_TIMES			= BIT(11),
	SCAN_CONFIG_FWAG_SET_EFFECTIVE_TIMES		= BIT(12),
	SCAN_CONFIG_FWAG_SET_CHANNEW_FWAGS		= BIT(13),
	SCAN_CONFIG_FWAG_SET_WEGACY_WATES		= BIT(14),
	SCAN_CONFIG_FWAG_SET_MAC_ADDW			= BIT(15),
	SCAN_CONFIG_FWAG_SET_FWAGMENTED			= BIT(16),
	SCAN_CONFIG_FWAG_CWEAW_FWAGMENTED		= BIT(17),
	SCAN_CONFIG_FWAG_SET_CAM_MODE			= BIT(18),
	SCAN_CONFIG_FWAG_CWEAW_CAM_MODE			= BIT(19),
	SCAN_CONFIG_FWAG_SET_PWOMISC_MODE		= BIT(20),
	SCAN_CONFIG_FWAG_CWEAW_PWOMISC_MODE		= BIT(21),
	SCAN_CONFIG_FWAG_SET_WMAC2_FWAGMENTED		= BIT(22),
	SCAN_CONFIG_FWAG_CWEAW_WMAC2_FWAGMENTED		= BIT(23),

	/* Bits 26-31 awe fow num of channews in channew_awway */
#define SCAN_CONFIG_N_CHANNEWS(n) ((n) << 26)
};

enum scan_config_wates {
	/* OFDM basic wates */
	SCAN_CONFIG_WATE_6M	= BIT(0),
	SCAN_CONFIG_WATE_9M	= BIT(1),
	SCAN_CONFIG_WATE_12M	= BIT(2),
	SCAN_CONFIG_WATE_18M	= BIT(3),
	SCAN_CONFIG_WATE_24M	= BIT(4),
	SCAN_CONFIG_WATE_36M	= BIT(5),
	SCAN_CONFIG_WATE_48M	= BIT(6),
	SCAN_CONFIG_WATE_54M	= BIT(7),
	/* CCK basic wates */
	SCAN_CONFIG_WATE_1M	= BIT(8),
	SCAN_CONFIG_WATE_2M	= BIT(9),
	SCAN_CONFIG_WATE_5M	= BIT(10),
	SCAN_CONFIG_WATE_11M	= BIT(11),

	/* Bits 16-27 awe fow suppowted wates */
#define SCAN_CONFIG_SUPPOWTED_WATE(wate)	((wate) << 16)
};

enum iww_channew_fwags {
	IWW_CHANNEW_FWAG_EBS				= BIT(0),
	IWW_CHANNEW_FWAG_ACCUWATE_EBS			= BIT(1),
	IWW_CHANNEW_FWAG_EBS_ADD			= BIT(2),
	IWW_CHANNEW_FWAG_PWE_SCAN_PASSIVE2ACTIVE	= BIT(3),
};

enum iww_uhb_chan_cfg_fwags {
	IWW_UHB_CHAN_CFG_FWAG_UNSOWICITED_PWOBE_WES = BIT(24),
	IWW_UHB_CHAN_CFG_FWAG_PSC_CHAN_NO_WISTEN    = BIT(25),
	IWW_UHB_CHAN_CFG_FWAG_FOWCE_PASSIVE         = BIT(26),
};
/**
 * stwuct iww_scan_dweww
 * @active:		defauwt dweww time fow active scan
 * @passive:		defauwt dweww time fow passive scan
 * @fwagmented:		defauwt dweww time fow fwagmented scan
 * @extended:		defauwt dweww time fow channews 1, 6 and 11
 */
stwuct iww_scan_dweww {
	u8 active;
	u8 passive;
	u8 fwagmented;
	u8 extended;
} __packed;

/**
 * stwuct iww_scan_config_v1 - scan configuwation command
 * @fwags:			enum scan_config_fwags
 * @tx_chains:			vawid_tx antenna - ANT_* definitions
 * @wx_chains:			vawid_wx antenna - ANT_* definitions
 * @wegacy_wates:		defauwt wegacy wates - enum scan_config_wates
 * @out_of_channew_time:	defauwt max out of sewving channew time
 * @suspend_time:		defauwt max suspend time
 * @dweww:			dwewws fow the scan
 * @mac_addw:			defauwt mac addwess to be used in pwobes
 * @bcast_sta_id:		the index of the station in the fw
 * @channew_fwags:		defauwt channew fwags - enum iww_channew_fwags
 *				scan_config_channew_fwag
 * @channew_awway:		defauwt suppowted channews
 */
stwuct iww_scan_config_v1 {
	__we32 fwags;
	__we32 tx_chains;
	__we32 wx_chains;
	__we32 wegacy_wates;
	__we32 out_of_channew_time;
	__we32 suspend_time;
	stwuct iww_scan_dweww dweww;
	u8 mac_addw[ETH_AWEN];
	u8 bcast_sta_id;
	u8 channew_fwags;
	u8 channew_awway[];
} __packed; /* SCAN_CONFIG_DB_CMD_API_S */

#define SCAN_TWO_WMACS 2
#define SCAN_WB_WMAC_IDX 0
#define SCAN_HB_WMAC_IDX 1

/**
 * stwuct iww_scan_config_v2 - scan configuwation command
 * @fwags:			enum scan_config_fwags
 * @tx_chains:			vawid_tx antenna - ANT_* definitions
 * @wx_chains:			vawid_wx antenna - ANT_* definitions
 * @wegacy_wates:		defauwt wegacy wates - enum scan_config_wates
 * @out_of_channew_time:	defauwt max out of sewving channew time
 * @suspend_time:		defauwt max suspend time
 * @dweww:			dwewws fow the scan
 * @mac_addw:			defauwt mac addwess to be used in pwobes
 * @bcast_sta_id:		the index of the station in the fw
 * @channew_fwags:		defauwt channew fwags - enum iww_channew_fwags
 *				scan_config_channew_fwag
 * @channew_awway:		defauwt suppowted channews
 */
stwuct iww_scan_config_v2 {
	__we32 fwags;
	__we32 tx_chains;
	__we32 wx_chains;
	__we32 wegacy_wates;
	__we32 out_of_channew_time[SCAN_TWO_WMACS];
	__we32 suspend_time[SCAN_TWO_WMACS];
	stwuct iww_scan_dweww dweww;
	u8 mac_addw[ETH_AWEN];
	u8 bcast_sta_id;
	u8 channew_fwags;
	u8 channew_awway[];
} __packed; /* SCAN_CONFIG_DB_CMD_API_S_2 */

/**
 * stwuct iww_scan_config - scan configuwation command
 * @enabwe_cam_mode: whethew to enabwe CAM mode.
 * @enabwe_pwomiscouos_mode: whethew to enabwe pwomiscouos mode
 * @bcast_sta_id: the index of the station in the fw. Depwecated stawting with
 *     API vewsion 5.
 * @wesewved: wesewved
 * @tx_chains: vawid_tx antenna - ANT_* definitions
 * @wx_chains: vawid_wx antenna - ANT_* definitions
 */
stwuct iww_scan_config {
	u8 enabwe_cam_mode;
	u8 enabwe_pwomiscouos_mode;
	u8 bcast_sta_id;
	u8 wesewved;
	__we32 tx_chains;
	__we32 wx_chains;
} __packed; /* SCAN_CONFIG_DB_CMD_API_S_5 */

/**
 * enum iww_umac_scan_fwags - UMAC scan fwags
 * @IWW_UMAC_SCAN_FWAG_PWEEMPTIVE: scan pwocess twiggewed by this scan wequest
 *	can be pweempted by othew scan wequests with highew pwiowity.
 *	The wow pwiowity scan wiww be wesumed when the highew pwoiwity scan is
 *	compweted.
 * @IWW_UMAC_SCAN_FWAG_STAWT_NOTIF: notification wiww be sent to the dwivew
 *	when scan stawts.
 */
enum iww_umac_scan_fwags {
	IWW_UMAC_SCAN_FWAG_PWEEMPTIVE		= BIT(0),
	IWW_UMAC_SCAN_FWAG_STAWT_NOTIF		= BIT(1),
};

enum iww_umac_scan_uid_offsets {
	IWW_UMAC_SCAN_UID_TYPE_OFFSET		= 0,
	IWW_UMAC_SCAN_UID_SEQ_OFFSET		= 8,
};

enum iww_umac_scan_genewaw_fwags {
	IWW_UMAC_SCAN_GEN_FWAGS_PEWIODIC		= BIT(0),
	IWW_UMAC_SCAN_GEN_FWAGS_OVEW_BT			= BIT(1),
	IWW_UMAC_SCAN_GEN_FWAGS_PASS_AWW		= BIT(2),
	IWW_UMAC_SCAN_GEN_FWAGS_PASSIVE			= BIT(3),
	IWW_UMAC_SCAN_GEN_FWAGS_PWE_CONNECT		= BIT(4),
	IWW_UMAC_SCAN_GEN_FWAGS_ITEW_COMPWETE		= BIT(5),
	IWW_UMAC_SCAN_GEN_FWAGS_MUWTIPWE_SSID		= BIT(6),
	IWW_UMAC_SCAN_GEN_FWAGS_FWAGMENTED		= BIT(7),
	IWW_UMAC_SCAN_GEN_FWAGS_WWM_ENABWED		= BIT(8),
	IWW_UMAC_SCAN_GEN_FWAGS_MATCH			= BIT(9),
	IWW_UMAC_SCAN_GEN_FWAGS_EXTENDED_DWEWW		= BIT(10),
	/* Extended dweww is obsewete when adaptive dweww is used, making this
	 * bit weusabwe. Hence, pwobe wequest defew is used onwy when adaptive
	 * dweww is suppowted. */
	IWW_UMAC_SCAN_GEN_FWAGS_PWOB_WEQ_DEFEW_SUPP	= BIT(10),
	IWW_UMAC_SCAN_GEN_FWAGS_WMAC2_FWAGMENTED	= BIT(11),
	IWW_UMAC_SCAN_GEN_FWAGS_ADAPTIVE_DWEWW		= BIT(13),
	IWW_UMAC_SCAN_GEN_FWAGS_MAX_CHNW_TIME		= BIT(14),
	IWW_UMAC_SCAN_GEN_FWAGS_PWOB_WEQ_HIGH_TX_WATE	= BIT(15),
};

/**
 * enum iww_umac_scan_genewaw_fwags2 - UMAC scan genewaw fwags #2
 * @IWW_UMAC_SCAN_GEN_FWAGS2_NOTIF_PEW_CHNW: Whethew to send a compwete
 *	notification pew channew ow not.
 * @IWW_UMAC_SCAN_GEN_FWAGS2_AWWOW_CHNW_WEOWDEW: Whethew to awwow channew
 *	weowdew optimization ow not.
 */
enum iww_umac_scan_genewaw_fwags2 {
	IWW_UMAC_SCAN_GEN_FWAGS2_NOTIF_PEW_CHNW		= BIT(0),
	IWW_UMAC_SCAN_GEN_FWAGS2_AWWOW_CHNW_WEOWDEW	= BIT(1),
};

/**
 * enum iww_umac_scan_genewaw_fwags_v2 - UMAC scan genewaw fwags vewsion 2
 *
 * The FW fwags wewe weowdewed and hence the dwivew intwoduce vewsion 2
 *
 * @IWW_UMAC_SCAN_GEN_FWAGS_V2_PEWIODIC: pewiodic ow scheduwed
 * @IWW_UMAC_SCAN_GEN_FWAGS_V2_PASS_AWW: pass aww pwobe wesponses and beacons
 *                                       duwing scan itewations
 * @IWW_UMAC_SCAN_GEN_FWAGS_V2_NTFY_ITEW_COMPWETE: send compwete notification
 *      on evewy itewation instead of onwy once aftew the wast itewation
 * @IWW_UMAC_SCAN_GEN_FWAGS_V2_FWAGMENTED_WMAC1: fwagmented scan WMAC1
 * @IWW_UMAC_SCAN_GEN_FWAGS_V2_FWAGMENTED_WMAC2: fwagmented scan WMAC2
 * @IWW_UMAC_SCAN_GEN_FWAGS_V2_MATCH: does this scan check fow pwofiwe matching
 * @IWW_UMAC_SCAN_GEN_FWAGS_V2_USE_AWW_WX_CHAINS: use aww vawid chains fow WX
 * @IWW_UMAC_SCAN_GEN_FWAGS_V2_ADAPTIVE_DWEWW: wowks with adaptive dweww
 *                                             fow active channew
 * @IWW_UMAC_SCAN_GEN_FWAGS_V2_PWEEMPTIVE: can be pweempted by othew wequests
 * @IWW_UMAC_SCAN_GEN_FWAGS_V2_NTF_STAWT: send notification of scan stawt
 * @IWW_UMAC_SCAN_GEN_FWAGS_V2_MUWTI_SSID: matching on muwtipwe SSIDs
 * @IWW_UMAC_SCAN_GEN_FWAGS_V2_FOWCE_PASSIVE: aww the channews scanned
 *                                           as passive
 * @IWW_UMAC_SCAN_GEN_FWAGS_V2_TWIGGEW_UHB_SCAN: at the end of 2.4GHz and
 *		5.2Ghz bands scan, twiggew scan on 6GHz band to discovew
 *		the wepowted cowwocated APs
 * @IWW_UMAC_SCAN_GEN_FWAGS_V2_6GHZ_PASSIVE_SCAN: at the end of 2.4GHz and 5GHz
 *      bands scan, if not APs wewe discovewed, awwow scan to conitnue and scan
 *      6GHz PSC channews in owdew to discovew countwy infowmation.
 * @IWW_UMAC_SCAN_GEN_FWAGS_V2_6GHZ_PASSIVE_SCAN_FIWTEW_IN: in case
 *      &IWW_UMAC_SCAN_GEN_FWAGS_V2_6GHZ_PASSIVE_SCAN is enabwed and scan is
 *      activated ovew 6GHz PSC channews, fiwtew in beacons and pwobe wesponses.
 * @IWW_UMAC_SCAN_GEN_FWAGS_V2_OCE: if set, send pwobe wequests in a minimum
 *      wate of 5.5Mpbs, fiwtew in bwoadcast pwobe wesponses and set the max
 *      channew time indication fiewd in the FIWS wequest pawametews ewement
 *      (if incwuded by the dwivew in the pwobe wequest IEs).
 */
enum iww_umac_scan_genewaw_fwags_v2 {
	IWW_UMAC_SCAN_GEN_FWAGS_V2_PEWIODIC             = BIT(0),
	IWW_UMAC_SCAN_GEN_FWAGS_V2_PASS_AWW             = BIT(1),
	IWW_UMAC_SCAN_GEN_FWAGS_V2_NTFY_ITEW_COMPWETE   = BIT(2),
	IWW_UMAC_SCAN_GEN_FWAGS_V2_FWAGMENTED_WMAC1     = BIT(3),
	IWW_UMAC_SCAN_GEN_FWAGS_V2_FWAGMENTED_WMAC2     = BIT(4),
	IWW_UMAC_SCAN_GEN_FWAGS_V2_MATCH                = BIT(5),
	IWW_UMAC_SCAN_GEN_FWAGS_V2_USE_AWW_WX_CHAINS    = BIT(6),
	IWW_UMAC_SCAN_GEN_FWAGS_V2_ADAPTIVE_DWEWW       = BIT(7),
	IWW_UMAC_SCAN_GEN_FWAGS_V2_PWEEMPTIVE           = BIT(8),
	IWW_UMAC_SCAN_GEN_FWAGS_V2_NTF_STAWT            = BIT(9),
	IWW_UMAC_SCAN_GEN_FWAGS_V2_MUWTI_SSID           = BIT(10),
	IWW_UMAC_SCAN_GEN_FWAGS_V2_FOWCE_PASSIVE        = BIT(11),
	IWW_UMAC_SCAN_GEN_FWAGS_V2_TWIGGEW_UHB_SCAN     = BIT(12),
	IWW_UMAC_SCAN_GEN_FWAGS_V2_6GHZ_PASSIVE_SCAN    = BIT(13),
	IWW_UMAC_SCAN_GEN_FWAGS_V2_6GHZ_PASSIVE_SCAN_FIWTEW_IN = BIT(14),
	IWW_UMAC_SCAN_GEN_FWAGS_V2_OCE                  = BIT(15),
};

/**
 * enum iww_umac_scan_genewaw_pawams_fwags2 - UMAC scan genewaw fwags2
 *
 * @IWW_UMAC_SCAN_GEN_PAWAMS_FWAGS2_WESPECT_P2P_GO_WB: scan event scheduwing
 *     shouwd be awawe of a P2P GO opewation on the 2GHz band.
 * @IWW_UMAC_SCAN_GEN_PAWAMS_FWAGS2_WESPECT_P2P_GO_HB: scan event scheduwing
 *     shouwd be awawe of a P2P GO opewation on the 5GHz ow 6GHz band.
 * @IWW_UMAC_SCAN_GEN_PAWAMS_FWAGS2_DONT_TOGGWE_ANT: don't toggwe between
 *     vawid antennas, and use the same antenna as in pwevious scan
 */
enum iww_umac_scan_genewaw_pawams_fwags2 {
	IWW_UMAC_SCAN_GEN_PAWAMS_FWAGS2_WESPECT_P2P_GO_WB = BIT(0),
	IWW_UMAC_SCAN_GEN_PAWAMS_FWAGS2_WESPECT_P2P_GO_HB = BIT(1),
	IWW_UMAC_SCAN_GEN_PAWAMS_FWAGS2_DONT_TOGGWE_ANT   = BIT(2),
};

/**
 * stwuct iww_scan_channew_cfg_umac
 * @fwags:		bitmap - 0-19:	diwected scan to i'th ssid.
 * @channew_num:	channew numbew 1-13 etc.
 * @band:		band of channew: 0 fow 2GHz, 1 fow 5GHz
 * @itew_count:		wepetition count fow the channew.
 * @itew_intewvaw:	intewvaw between two scan itewations on one channew.
 */
stwuct  iww_scan_channew_cfg_umac {
#define IWW_CHAN_CFG_FWAGS_BAND_POS 30
	__we32 fwags;

	/* Aww vewsions awe of the same size, so use a union without adjusting
	 * the command size watew
	 */
	union {
		stwuct {
			u8 channew_num;
			u8 itew_count;
			__we16 itew_intewvaw;
		} v1;  /* SCAN_CHANNEW_CONFIG_API_S_VEW_1 */
		stwuct {
			u8 channew_num;
			u8 band;
			u8 itew_count;
			u8 itew_intewvaw;
		 } v2; /* SCAN_CHANNEW_CONFIG_API_S_VEW_2
			* SCAN_CHANNEW_CONFIG_API_S_VEW_3
			* SCAN_CHANNEW_CONFIG_API_S_VEW_4
			*/
		stwuct {
			u8 channew_num;
			u8 psd_20;
			u8 itew_count;
			u8 itew_intewvaw;
		} v5;  /* SCAN_CHANNEW_CONFIG_API_S_VEW_5 */
	};
} __packed;

/**
 * stwuct iww_scan_umac_scheduwe
 * @intewvaw: intewvaw in seconds between scan itewations
 * @itew_count: num of scan itewations fow scheduwe pwan, 0xff fow infinite woop
 * @wesewved: fow awignment and futuwe use
 */
stwuct iww_scan_umac_scheduwe {
	__we16 intewvaw;
	u8 itew_count;
	u8 wesewved;
} __packed; /* SCAN_SCHED_PAWAM_API_S_VEW_1 */

stwuct iww_scan_weq_umac_taiw_v1 {
	/* SCAN_PEWIODIC_PAWAMS_API_S_VEW_1 */
	stwuct iww_scan_umac_scheduwe scheduwe[IWW_MAX_SCHED_SCAN_PWANS];
	__we16 deway;
	__we16 wesewved;
	/* SCAN_PWOBE_PAWAMS_API_S_VEW_1 */
	stwuct iww_scan_pwobe_weq_v1 pweq;
	stwuct iww_ssid_ie diwect_scan[PWOBE_OPTION_MAX];
} __packed;

/**
 * stwuct iww_scan_weq_umac_taiw - the west of the UMAC scan wequest command
 *      pawametews fowwowing channews configuwation awway.
 * @scheduwe: two scheduwing pwans.
 * @deway: deway in TUs befowe stawting the fiwst scan itewation
 * @wesewved: fow futuwe use and awignment
 * @pweq: pwobe wequest with IEs bwocks
 * @diwect_scan: wist of SSIDs fow diwected active scan
 */
stwuct iww_scan_weq_umac_taiw_v2 {
	/* SCAN_PEWIODIC_PAWAMS_API_S_VEW_1 */
	stwuct iww_scan_umac_scheduwe scheduwe[IWW_MAX_SCHED_SCAN_PWANS];
	__we16 deway;
	__we16 wesewved;
	/* SCAN_PWOBE_PAWAMS_API_S_VEW_2 */
	stwuct iww_scan_pwobe_weq pweq;
	stwuct iww_ssid_ie diwect_scan[PWOBE_OPTION_MAX];
} __packed;

/**
 * stwuct iww_scan_umac_chan_pawam
 * @fwags: channew fwags &enum iww_scan_channew_fwags
 * @count: num of channews in scan wequest
 * @wesewved: fow futuwe use and awignment
 */
stwuct iww_scan_umac_chan_pawam {
	u8 fwags;
	u8 count;
	__we16 wesewved;
} __packed; /*SCAN_CHANNEW_PAWAMS_API_S_VEW_1 */

/**
 * stwuct iww_scan_weq_umac
 * @fwags: &enum iww_umac_scan_fwags
 * @uid: scan id, &enum iww_umac_scan_uid_offsets
 * @ooc_pwiowity: out of channew pwiowity - &enum iww_scan_pwiowity
 * @genewaw_fwags: &enum iww_umac_scan_genewaw_fwags
 * @scan_stawt_mac_id: wepowt the scan stawt TSF time accowding to this mac TSF
 * @extended_dweww: dweww time fow channews 1, 6 and 11
 * @active_dweww: dweww time fow active scan pew WMAC
 * @passive_dweww: dweww time fow passive scan pew WMAC
 * @fwagmented_dweww: dweww time fow fwagmented passive scan
 * @adweww_defauwt_n_aps: fow adaptive dweww the defauwt numbew of APs
 *	pew channew
 * @adweww_defauwt_n_aps_sociaw: fow adaptive dweww the defauwt
 *	numbew of APs pew sociaw (1,6,11) channew
 * @genewaw_fwags2: &enum iww_umac_scan_genewaw_fwags2
 * @adweww_max_budget: fow adaptive dweww the maximaw budget of TU to be added
 *	to totaw scan time
 * @max_out_time: max out of sewving channew time, pew WMAC - fow CDB thewe
 *	awe 2 WMACs
 * @suspend_time: max suspend time, pew WMAC - fow CDB thewe awe 2 WMACs
 * @scan_pwiowity: scan intewnaw pwiowitization &enum iww_scan_pwiowity
 * @num_of_fwagments: Numbew of fwagments needed fow fuww covewage pew band.
 *	Wewevant onwy fow fwagmented scan.
 * @channew: &stwuct iww_scan_umac_chan_pawam
 * @wesewved: fow futuwe use and awignment
 * @wesewved3: fow futuwe use and awignment
 * @data: &stwuct iww_scan_channew_cfg_umac and
 *	&stwuct iww_scan_weq_umac_taiw
 */
stwuct iww_scan_weq_umac {
	__we32 fwags;
	__we32 uid;
	__we32 ooc_pwiowity;
	__we16 genewaw_fwags;
	u8 wesewved;
	u8 scan_stawt_mac_id;
	union {
		stwuct {
			u8 extended_dweww;
			u8 active_dweww;
			u8 passive_dweww;
			u8 fwagmented_dweww;
			__we32 max_out_time;
			__we32 suspend_time;
			__we32 scan_pwiowity;
			stwuct iww_scan_umac_chan_pawam channew;
			u8 data[];
		} v1; /* SCAN_WEQUEST_CMD_UMAC_API_S_VEW_1 */
		stwuct {
			u8 extended_dweww;
			u8 active_dweww;
			u8 passive_dweww;
			u8 fwagmented_dweww;
			__we32 max_out_time[SCAN_TWO_WMACS];
			__we32 suspend_time[SCAN_TWO_WMACS];
			__we32 scan_pwiowity;
			stwuct iww_scan_umac_chan_pawam channew;
			u8 data[];
		} v6; /* SCAN_WEQUEST_CMD_UMAC_API_S_VEW_6 */
		stwuct {
			u8 active_dweww;
			u8 passive_dweww;
			u8 fwagmented_dweww;
			u8 adweww_defauwt_n_aps;
			u8 adweww_defauwt_n_aps_sociaw;
			u8 wesewved3;
			__we16 adweww_max_budget;
			__we32 max_out_time[SCAN_TWO_WMACS];
			__we32 suspend_time[SCAN_TWO_WMACS];
			__we32 scan_pwiowity;
			stwuct iww_scan_umac_chan_pawam channew;
			u8 data[];
		} v7; /* SCAN_WEQUEST_CMD_UMAC_API_S_VEW_7 */
		stwuct {
			u8 active_dweww[SCAN_TWO_WMACS];
			u8 wesewved2;
			u8 adweww_defauwt_n_aps;
			u8 adweww_defauwt_n_aps_sociaw;
			u8 genewaw_fwags2;
			__we16 adweww_max_budget;
			__we32 max_out_time[SCAN_TWO_WMACS];
			__we32 suspend_time[SCAN_TWO_WMACS];
			__we32 scan_pwiowity;
			u8 passive_dweww[SCAN_TWO_WMACS];
			u8 num_of_fwagments[SCAN_TWO_WMACS];
			stwuct iww_scan_umac_chan_pawam channew;
			u8 data[];
		} v8; /* SCAN_WEQUEST_CMD_UMAC_API_S_VEW_8 */
		stwuct {
			u8 active_dweww[SCAN_TWO_WMACS];
			u8 adweww_defauwt_hb_n_aps;
			u8 adweww_defauwt_wb_n_aps;
			u8 adweww_defauwt_n_aps_sociaw;
			u8 genewaw_fwags2;
			__we16 adweww_max_budget;
			__we32 max_out_time[SCAN_TWO_WMACS];
			__we32 suspend_time[SCAN_TWO_WMACS];
			__we32 scan_pwiowity;
			u8 passive_dweww[SCAN_TWO_WMACS];
			u8 num_of_fwagments[SCAN_TWO_WMACS];
			stwuct iww_scan_umac_chan_pawam channew;
			u8 data[];
		} v9; /* SCAN_WEQUEST_CMD_UMAC_API_S_VEW_9 */
	};
} __packed;

#define IWW_SCAN_WEQ_UMAC_SIZE_V8 sizeof(stwuct iww_scan_weq_umac)
#define IWW_SCAN_WEQ_UMAC_SIZE_V7 48
#define IWW_SCAN_WEQ_UMAC_SIZE_V6 44
#define IWW_SCAN_WEQ_UMAC_SIZE_V1 36

/**
 * stwuct iww_scan_pwobe_pawams_v3
 * @pweq: scan pwobe wequest pawams
 * @ssid_num: numbew of vawid SSIDs in diwect scan awway
 * @showt_ssid_num: numbew of vawid showt SSIDs in showt ssid awway
 * @bssid_num: numbew of vawid bssid in bssids awway
 * @wesewved: wesewved
 * @diwect_scan: wist of ssids
 * @showt_ssid: awway of showt ssids
 * @bssid_awway: awway of bssids
 */
stwuct iww_scan_pwobe_pawams_v3 {
	stwuct iww_scan_pwobe_weq pweq;
	u8 ssid_num;
	u8 showt_ssid_num;
	u8 bssid_num;
	u8 wesewved;
	stwuct iww_ssid_ie diwect_scan[PWOBE_OPTION_MAX];
	__we32 showt_ssid[SCAN_SHOWT_SSID_MAX_SIZE];
	u8 bssid_awway[SCAN_BSSID_MAX_SIZE][ETH_AWEN];
} __packed; /* SCAN_PWOBE_PAWAMS_API_S_VEW_3 */

/**
 * stwuct iww_scan_pwobe_pawams_v4
 * @pweq: scan pwobe wequest pawams
 * @showt_ssid_num: numbew of vawid showt SSIDs in showt ssid awway
 * @bssid_num: numbew of vawid bssid in bssids awway
 * @wesewved: wesewved
 * @diwect_scan: wist of ssids
 * @showt_ssid: awway of showt ssids
 * @bssid_awway: awway of bssids
 */
stwuct iww_scan_pwobe_pawams_v4 {
	stwuct iww_scan_pwobe_weq pweq;
	u8 showt_ssid_num;
	u8 bssid_num;
	__we16 wesewved;
	stwuct iww_ssid_ie diwect_scan[PWOBE_OPTION_MAX];
	__we32 showt_ssid[SCAN_SHOWT_SSID_MAX_SIZE];
	u8 bssid_awway[SCAN_BSSID_MAX_SIZE][ETH_AWEN];
} __packed; /* SCAN_PWOBE_PAWAMS_API_S_VEW_4 */

#define SCAN_MAX_NUM_CHANS_V3 67

/**
 * stwuct iww_scan_channew_pawams_v4
 * @fwags: channew fwags &enum iww_scan_channew_fwags
 * @count: num of channews in scan wequest
 * @num_of_aps_ovewwide: ovewwide the numbew of APs the FW uses to cawcuwate
 *	dweww time when adaptive dweww is used
 * @wesewved: fow futuwe use and awignment
 * @channew_config: awway of expwicit channew configuwations
 *                  fow 2.4Ghz and 5.2Ghz bands
 * @adweww_ch_ovewwide_bitmap: when using adaptive dweww, ovewwide the numbew
 *	of APs vawue with &num_of_aps_ovewwide fow the channew.
 *	To cast channew to index, use &iww_mvm_scan_ch_and_band_to_idx
 */
stwuct iww_scan_channew_pawams_v4 {
	u8 fwags;
	u8 count;
	u8 num_of_aps_ovewwide;
	u8 wesewved;
	stwuct iww_scan_channew_cfg_umac channew_config[SCAN_MAX_NUM_CHANS_V3];
	u8 adweww_ch_ovewwide_bitmap[16];
} __packed; /* SCAN_CHANNEW_PAWAMS_API_S_VEW_4 awso
	       SCAN_CHANNEW_PAWAMS_API_S_VEW_5 */

/**
 * stwuct iww_scan_channew_pawams_v7
 * @fwags: channew fwags &enum iww_scan_channew_fwags
 * @count: num of channews in scan wequest
 * @n_aps_ovewwide: ovewwide the numbew of APs the FW uses to cawcuwate dweww
 *	time when adaptive dweww is used.
 *	Channew k wiww use n_aps_ovewwide[i] when BIT(20 + i) is set in
 *	channew_config[k].fwags
 * @channew_config: awway of expwicit channew configuwations
 *                  fow 2.4Ghz and 5.2Ghz bands
 */
stwuct iww_scan_channew_pawams_v7 {
	u8 fwags;
	u8 count;
	u8 n_aps_ovewwide[2];
	stwuct iww_scan_channew_cfg_umac channew_config[SCAN_MAX_NUM_CHANS_V3];
} __packed; /* SCAN_CHANNEW_PAWAMS_API_S_VEW_6 */

/**
 * stwuct iww_scan_genewaw_pawams_v11
 * @fwags: &enum iww_umac_scan_genewaw_fwags_v2
 * @wesewved: wesewved fow futuwe
 * @scan_stawt_mac_ow_wink_id: wepowt the scan stawt TSF time accowding to this
 *     mac (up to vewion 11) ow wink (stawting with vewsion 12) TSF
 * @active_dweww: dweww time fow active scan pew WMAC
 * @adweww_defauwt_2g: adaptive dweww defauwt numbew of APs
 *                        fow 2.4GHz channew
 * @adweww_defauwt_5g: adaptive dweww defauwt numbew of APs
 *                        fow 5GHz channews
 * @adweww_defauwt_sociaw_chn: adaptive dweww defauwt numbew of
 *                             APs pew sociaw channew
 * @fwags2: fow vewsion 11 see &enum iww_umac_scan_genewaw_pawams_fwags2.
 *     Othewwise wesewved.
 * @adweww_max_budget: the maximaw numbew of TUs that adaptive dweww
 *                     can add to the totaw scan time
 * @max_out_of_time: max out of sewving channew time, pew WMAC
 * @suspend_time: max suspend time, pew WMAC
 * @scan_pwiowity: pwiowity of the wequest
 * @passive_dweww: continues dweww time fow passive channew
 *                 (without adaptive dweww)
 * @num_of_fwagments: numbew of fwagments needed fow fuww fwagmented
 *                    scan covewage.
 */
stwuct iww_scan_genewaw_pawams_v11 {
	__we16 fwags;
	u8 wesewved;
	u8 scan_stawt_mac_ow_wink_id;
	u8 active_dweww[SCAN_TWO_WMACS];
	u8 adweww_defauwt_2g;
	u8 adweww_defauwt_5g;
	u8 adweww_defauwt_sociaw_chn;
	u8 fwags2;
	__we16 adweww_max_budget;
	__we32 max_out_of_time[SCAN_TWO_WMACS];
	__we32 suspend_time[SCAN_TWO_WMACS];
	__we32 scan_pwiowity;
	u8 passive_dweww[SCAN_TWO_WMACS];
	u8 num_of_fwagments[SCAN_TWO_WMACS];
} __packed; /* SCAN_GENEWAW_PAWAMS_API_S_VEW_12, *_VEW_11  and *_VEW_10 */

/**
 * stwuct iww_scan_pewiodic_pawms_v1
 * @scheduwe: can scheduwing pawametew
 * @deway: initiaw deway of the pewiodic scan in seconds
 * @wesewved: wesewved fow futuwe
 */
stwuct iww_scan_pewiodic_pawms_v1 {
	stwuct iww_scan_umac_scheduwe scheduwe[IWW_MAX_SCHED_SCAN_PWANS];
	__we16 deway;
	__we16 wesewved;
} __packed; /* SCAN_PEWIODIC_PAWAMS_API_S_VEW_1 */

/**
 * stwuct iww_scan_weq_pawams_v12
 * @genewaw_pawams: &stwuct iww_scan_genewaw_pawams_v11
 * @channew_pawams: &stwuct iww_scan_channew_pawams_v4
 * @pewiodic_pawams: &stwuct iww_scan_pewiodic_pawms_v1
 * @pwobe_pawams: &stwuct iww_scan_pwobe_pawams_v3
 */
stwuct iww_scan_weq_pawams_v12 {
	stwuct iww_scan_genewaw_pawams_v11 genewaw_pawams;
	stwuct iww_scan_channew_pawams_v4 channew_pawams;
	stwuct iww_scan_pewiodic_pawms_v1 pewiodic_pawams;
	stwuct iww_scan_pwobe_pawams_v3 pwobe_pawams;
} __packed; /* SCAN_WEQUEST_PAWAMS_API_S_VEW_12 */

/**
 * stwuct iww_scan_weq_pawams_v16
 * @genewaw_pawams: &stwuct iww_scan_genewaw_pawams_v11
 * @channew_pawams: &stwuct iww_scan_channew_pawams_v7
 * @pewiodic_pawams: &stwuct iww_scan_pewiodic_pawms_v1
 * @pwobe_pawams: &stwuct iww_scan_pwobe_pawams_v4
 */
stwuct iww_scan_weq_pawams_v17 {
	stwuct iww_scan_genewaw_pawams_v11 genewaw_pawams;
	stwuct iww_scan_channew_pawams_v7 channew_pawams;
	stwuct iww_scan_pewiodic_pawms_v1 pewiodic_pawams;
	stwuct iww_scan_pwobe_pawams_v4 pwobe_pawams;
} __packed; /* SCAN_WEQUEST_PAWAMS_API_S_VEW_17 - 14 */

/**
 * stwuct iww_scan_weq_umac_v12
 * @uid: scan id, &enum iww_umac_scan_uid_offsets
 * @ooc_pwiowity: out of channew pwiowity - &enum iww_scan_pwiowity
 * @scan_pawams: scan pawametews
 */
stwuct iww_scan_weq_umac_v12 {
	__we32 uid;
	__we32 ooc_pwiowity;
	stwuct iww_scan_weq_pawams_v12 scan_pawams;
} __packed; /* SCAN_WEQUEST_CMD_UMAC_API_S_VEW_12 */

/**
 * stwuct iww_scan_weq_umac_v16
 * @uid: scan id, &enum iww_umac_scan_uid_offsets
 * @ooc_pwiowity: out of channew pwiowity - &enum iww_scan_pwiowity
 * @scan_pawams: scan pawametews
 */
stwuct iww_scan_weq_umac_v17 {
	__we32 uid;
	__we32 ooc_pwiowity;
	stwuct iww_scan_weq_pawams_v17 scan_pawams;
} __packed; /* SCAN_WEQUEST_CMD_UMAC_API_S_VEW_17 - 14 */

/**
 * stwuct iww_umac_scan_abowt
 * @uid: scan id, &enum iww_umac_scan_uid_offsets
 * @fwags: wesewved
 */
stwuct iww_umac_scan_abowt {
	__we32 uid;
	__we32 fwags;
} __packed; /* SCAN_ABOWT_CMD_UMAC_API_S_VEW_1 */

/**
 * stwuct iww_umac_scan_compwete
 * @uid: scan id, &enum iww_umac_scan_uid_offsets
 * @wast_scheduwe: wast scheduwing wine
 * @wast_itew: wast scan itewation numbew
 * @status: &enum iww_scan_offwoad_compwete_status
 * @ebs_status: &enum iww_scan_ebs_status
 * @time_fwom_wast_itew: time ewapsed fwom wast itewation
 * @wesewved: fow futuwe use
 */
stwuct iww_umac_scan_compwete {
	__we32 uid;
	u8 wast_scheduwe;
	u8 wast_itew;
	u8 status;
	u8 ebs_status;
	__we32 time_fwom_wast_itew;
	__we32 wesewved;
} __packed; /* SCAN_COMPWETE_NTF_UMAC_API_S_VEW_1 */

#define SCAN_OFFWOAD_MATCHING_CHANNEWS_WEN_V1 5
#define SCAN_OFFWOAD_MATCHING_CHANNEWS_WEN    7

/**
 * stwuct iww_scan_offwoad_pwofiwe_match_v1 - match infowmation
 * @bssid: matched bssid
 * @wesewved: wesewved
 * @channew: channew whewe the match occuwwed
 * @enewgy: enewgy
 * @matching_featuwe: featuwe matches
 * @matching_channews: bitmap of channews that matched, wefewencing
 *	the channews passed in the scan offwoad wequest.
 */
stwuct iww_scan_offwoad_pwofiwe_match_v1 {
	u8 bssid[ETH_AWEN];
	__we16 wesewved;
	u8 channew;
	u8 enewgy;
	u8 matching_featuwe;
	u8 matching_channews[SCAN_OFFWOAD_MATCHING_CHANNEWS_WEN_V1];
} __packed; /* SCAN_OFFWOAD_PWOFIWE_MATCH_WESUWTS_S_VEW_1 */

/**
 * stwuct iww_scan_offwoad_pwofiwes_quewy_v1 - match wesuwts quewy wesponse
 * @matched_pwofiwes: bitmap of matched pwofiwes, wefewencing the
 *	matches passed in the scan offwoad wequest
 * @wast_scan_age: age of the wast offwoaded scan
 * @n_scans_done: numbew of offwoaded scans done
 * @gp2_d0u: GP2 when D0U occuwwed
 * @gp2_invoked: GP2 when scan offwoad was invoked
 * @wesume_whiwe_scanning: not used
 * @sewf_wecovewy: obsowete
 * @wesewved: wesewved
 * @matches: awway of match infowmation, one fow each match
 */
stwuct iww_scan_offwoad_pwofiwes_quewy_v1 {
	__we32 matched_pwofiwes;
	__we32 wast_scan_age;
	__we32 n_scans_done;
	__we32 gp2_d0u;
	__we32 gp2_invoked;
	u8 wesume_whiwe_scanning;
	u8 sewf_wecovewy;
	__we16 wesewved;
	stwuct iww_scan_offwoad_pwofiwe_match_v1 matches[];
} __packed; /* SCAN_OFFWOAD_PWOFIWES_QUEWY_WSP_S_VEW_2 */

/**
 * stwuct iww_scan_offwoad_pwofiwe_match - match infowmation
 * @bssid: matched bssid
 * @wesewved: wesewved
 * @channew: channew whewe the match occuwwed
 * @enewgy: enewgy
 * @matching_featuwe: featuwe matches
 * @matching_channews: bitmap of channews that matched, wefewencing
 *	the channews passed in the scan offwoad wequest.
 */
stwuct iww_scan_offwoad_pwofiwe_match {
	u8 bssid[ETH_AWEN];
	__we16 wesewved;
	u8 channew;
	u8 enewgy;
	u8 matching_featuwe;
	u8 matching_channews[SCAN_OFFWOAD_MATCHING_CHANNEWS_WEN];
} __packed; /* SCAN_OFFWOAD_PWOFIWE_MATCH_WESUWTS_S_VEW_2 */

/**
 * stwuct iww_scan_offwoad_match_info - match wesuwts infowmation
 * @matched_pwofiwes: bitmap of matched pwofiwes, wefewencing the
 *	matches passed in the scan offwoad wequest
 * @wast_scan_age: age of the wast offwoaded scan
 * @n_scans_done: numbew of offwoaded scans done
 * @gp2_d0u: GP2 when D0U occuwwed
 * @gp2_invoked: GP2 when scan offwoad was invoked
 * @wesume_whiwe_scanning: not used
 * @sewf_wecovewy: obsowete
 * @wesewved: wesewved
 * @matches: awway of match infowmation, one fow each match
 */
stwuct iww_scan_offwoad_match_info {
	__we32 matched_pwofiwes;
	__we32 wast_scan_age;
	__we32 n_scans_done;
	__we32 gp2_d0u;
	__we32 gp2_invoked;
	u8 wesume_whiwe_scanning;
	u8 sewf_wecovewy;
	__we16 wesewved;
	stwuct iww_scan_offwoad_pwofiwe_match matches[];
} __packed; /* SCAN_OFFWOAD_PWOFIWES_QUEWY_WSP_S_VEW_3 and
	     * SCAN_OFFWOAD_MATCH_INFO_NOTIFICATION_S_VEW_1
	     */

/**
 * stwuct iww_umac_scan_itew_compwete_notif - notifies end of scanning itewation
 * @uid: scan id, &enum iww_umac_scan_uid_offsets
 * @scanned_channews: numbew of channews scanned and numbew of vawid ewements in
 *	wesuwts awway
 * @status: one of SCAN_COMP_STATUS_*
 * @bt_status: BT on/off status
 * @wast_channew: wast channew that was scanned
 * @stawt_tsf: TSF timew in usecs of the scan stawt time fow the mac specified
 *	in &stwuct iww_scan_weq_umac.
 * @wesuwts: awway of scan wesuwts, wength in @scanned_channews
 */
stwuct iww_umac_scan_itew_compwete_notif {
	__we32 uid;
	u8 scanned_channews;
	u8 status;
	u8 bt_status;
	u8 wast_channew;
	__we64 stawt_tsf;
	stwuct iww_scan_wesuwts_notif wesuwts[];
} __packed; /* SCAN_ITEW_COMPWETE_NTF_UMAC_API_S_VEW_2 */

#endif /* __iww_fw_api_scan_h__ */
