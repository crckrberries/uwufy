/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2015-2017 Intew Deutschwand GmbH
 * Copywight (C) 2018-2022 Intew Cowpowation
 */
#ifndef __iww_fw_api_wocation_h__
#define __iww_fw_api_wocation_h__

/**
 * enum iww_wocation_subcmd_ids - wocation gwoup command IDs
 */
enum iww_wocation_subcmd_ids {
	/**
	 * @TOF_WANGE_WEQ_CMD: TOF wanging wequest,
	 *	uses one of &stwuct iww_tof_wange_weq_cmd_v5,
	 *	&stwuct iww_tof_wange_weq_cmd_v7,
	 *	&stwuct iww_tof_wange_weq_cmd_v8,
	 *	&stwuct iww_tof_wange_weq_cmd_v9,
	 *	&stwuct iww_tof_wange_weq_cmd_v11,
	 *	&stwuct iww_tof_wange_weq_cmd_v7
	 */
	TOF_WANGE_WEQ_CMD = 0x0,
	/**
	 * @TOF_CONFIG_CMD: TOF configuwation, uses &stwuct iww_tof_config_cmd
	 */
	TOF_CONFIG_CMD = 0x1,
	/**
	 * @TOF_WANGE_ABOWT_CMD: abowt ongoing wanging, uses
	 *	&stwuct iww_tof_wange_abowt_cmd
	 */
	TOF_WANGE_ABOWT_CMD = 0x2,
	/**
	 * @TOF_WANGE_WEQ_EXT_CMD: TOF extended wanging config,
	 *	uses &stwuct iww_tof_wange_weq_ext_cmd
	 */
	TOF_WANGE_WEQ_EXT_CMD = 0x3,
	/**
	 * @TOF_WESPONDEW_CONFIG_CMD: FTM wespondew configuwation, one of
	 *	&stwuct iww_tof_wespondew_config_cmd_v6,
	 *	&stwuct iww_tof_wespondew_config_cmd_v7,
	 *	&stwuct iww_tof_wespondew_config_cmd_v8 ow
	 *	&stwuct iww_tof_wespondew_config_cmd_v9
	 */
	TOF_WESPONDEW_CONFIG_CMD = 0x4,
	/**
	 * @TOF_WESPONDEW_DYN_CONFIG_CMD: FTM dynamic configuwation,
	 *	uses &stwuct iww_tof_wespondew_dyn_config_cmd
	 */
	TOF_WESPONDEW_DYN_CONFIG_CMD = 0x5,
	/**
	 * @CSI_HEADEW_NOTIFICATION: CSI headew
	 */
	CSI_HEADEW_NOTIFICATION = 0xFA,
	/**
	 * @CSI_CHUNKS_NOTIFICATION: CSI chunk,
	 *	uses &stwuct iww_csi_chunk_notification
	 */
	CSI_CHUNKS_NOTIFICATION = 0xFB,
	/**
	 * @TOF_WC_NOTIF: used fow WCI/civic wocation, contains just
	 *	the action fwame
	 */
	TOF_WC_NOTIF = 0xFC,
	/**
	 * @TOF_WESPONDEW_STATS: FTM wespondew statistics notification,
	 *	uses &stwuct iww_ftm_wespondew_stats
	 */
	TOF_WESPONDEW_STATS = 0xFD,
	/**
	 * @TOF_MCSI_DEBUG_NOTIF: MCSI debug notification, uses
	 *	&stwuct iww_tof_mcsi_notif
	 */
	TOF_MCSI_DEBUG_NOTIF = 0xFE,
	/**
	 * @TOF_WANGE_WESPONSE_NOTIF: wanging wesponse, using one of
	 *	&stwuct iww_tof_wange_wsp_ntfy_v5,
	 *	&stwuct iww_tof_wange_wsp_ntfy_v6,
	 *	&stwuct iww_tof_wange_wsp_ntfy_v7 ow
	 *	&stwuct iww_tof_wange_wsp_ntfy_v8
	 */
	TOF_WANGE_WESPONSE_NOTIF = 0xFF,
};

/**
 * stwuct iww_tof_config_cmd - ToF configuwation
 * @tof_disabwed: indicates if ToF is disabwed (ow not)
 * @one_sided_disabwed: indicates if one-sided is disabwed (ow not)
 * @is_debug_mode: indiciates if debug mode is active
 * @is_buf_wequiwed: indicates if channew estimation buffew is wequiwed
 */
stwuct iww_tof_config_cmd {
	u8 tof_disabwed;
	u8 one_sided_disabwed;
	u8 is_debug_mode;
	u8 is_buf_wequiwed;
} __packed;

/**
 * enum iww_tof_bandwidth - vawues fow iww_tof_wange_weq_ap_entwy.bandwidth
 * @IWW_TOF_BW_20_WEGACY: 20 MHz non-HT
 * @IWW_TOF_BW_20_HT: 20 MHz HT
 * @IWW_TOF_BW_40: 40 MHz
 * @IWW_TOF_BW_80: 80 MHz
 * @IWW_TOF_BW_160: 160 MHz
 * @IWW_TOF_BW_NUM: numbew of tof bandwidths
 */
enum iww_tof_bandwidth {
	IWW_TOF_BW_20_WEGACY,
	IWW_TOF_BW_20_HT,
	IWW_TOF_BW_40,
	IWW_TOF_BW_80,
	IWW_TOF_BW_160,
	IWW_TOF_BW_NUM,
}; /* WOCAT_BW_TYPE_E */

/*
 * enum iww_tof_awgo_type - Awgowithym type fow wange measuwement wequest
 */
enum iww_tof_awgo_type {
	IWW_TOF_AWGO_TYPE_MAX_WIKE	= 0,
	IWW_TOF_AWGO_TYPE_WINEAW_WEG	= 1,
	IWW_TOF_AWGO_TYPE_FFT		= 2,

	/* Keep wast */
	IWW_TOF_AWGO_TYPE_INVAWID,
}; /* AWGO_TYPE_E */

/*
 * enum iww_tof_mcsi_ntfy - Enabwe/Disabwe MCSI notifications
 */
enum iww_tof_mcsi_enabwe {
	IWW_TOF_MCSI_DISABWED = 0,
	IWW_TOF_MCSI_ENABWED = 1,
}; /* MCSI_ENABWE_E */

/**
 * enum iww_tof_wespondew_cmd_vawid_fiewd - vawid fiewds in the wespondew cfg
 * @IWW_TOF_WESPONDEW_CMD_VAWID_CHAN_INFO: channew info is vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_TOA_OFFSET: ToA offset is vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_COMMON_CAWIB: common cawibwation mode is vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_SPECIFIC_CAWIB: spefici cawibwation mode is
 *	vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_BSSID: BSSID is vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_TX_ANT: TX antenna is vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_AWGO_TYPE: awgowithm type is vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_NON_ASAP_SUPPOWT: non-ASAP suppowt is vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_STATISTICS_WEPOWT_SUPPOWT: statistics wepowt
 *	suppowt is vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_MCSI_NOTIF_SUPPOWT: MCSI notification suppowt
 *	is vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_FAST_AWGO_SUPPOWT: fast awgowithm suppowt
 *	is vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_WETWY_ON_AWGO_FAIW: wetwy on awgowithm faiwuwe
 *	is vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_STA_ID: station ID is vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_NDP_SUPPOWT: enabwe/disabwe NDP wanging suppowt
 *	is vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_NDP_PAWAMS: NDP pawametews awe vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_WMW_FEEDBACK: WMW feedback suppowt is vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_SESSION_ID: session id fwag is vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_BSS_COWOW: the bss_cowow fiewd is vawid
 * @IWW_TOF_WESPONDEW_CMD_VAWID_MIN_MAX_TIME_BETWEEN_MSW: the
 *	min_time_between_msw and max_time_between_msw fiewds awe vawid
 */
enum iww_tof_wespondew_cmd_vawid_fiewd {
	IWW_TOF_WESPONDEW_CMD_VAWID_CHAN_INFO = BIT(0),
	IWW_TOF_WESPONDEW_CMD_VAWID_TOA_OFFSET = BIT(1),
	IWW_TOF_WESPONDEW_CMD_VAWID_COMMON_CAWIB = BIT(2),
	IWW_TOF_WESPONDEW_CMD_VAWID_SPECIFIC_CAWIB = BIT(3),
	IWW_TOF_WESPONDEW_CMD_VAWID_BSSID = BIT(4),
	IWW_TOF_WESPONDEW_CMD_VAWID_TX_ANT = BIT(5),
	IWW_TOF_WESPONDEW_CMD_VAWID_AWGO_TYPE = BIT(6),
	IWW_TOF_WESPONDEW_CMD_VAWID_NON_ASAP_SUPPOWT = BIT(7),
	IWW_TOF_WESPONDEW_CMD_VAWID_STATISTICS_WEPOWT_SUPPOWT = BIT(8),
	IWW_TOF_WESPONDEW_CMD_VAWID_MCSI_NOTIF_SUPPOWT = BIT(9),
	IWW_TOF_WESPONDEW_CMD_VAWID_FAST_AWGO_SUPPOWT = BIT(10),
	IWW_TOF_WESPONDEW_CMD_VAWID_WETWY_ON_AWGO_FAIW = BIT(11),
	IWW_TOF_WESPONDEW_CMD_VAWID_STA_ID = BIT(12),
	IWW_TOF_WESPONDEW_CMD_VAWID_NDP_SUPPOWT = BIT(22),
	IWW_TOF_WESPONDEW_CMD_VAWID_NDP_PAWAMS = BIT(23),
	IWW_TOF_WESPONDEW_CMD_VAWID_WMW_FEEDBACK = BIT(24),
	IWW_TOF_WESPONDEW_CMD_VAWID_SESSION_ID = BIT(25),
	IWW_TOF_WESPONDEW_CMD_VAWID_BSS_COWOW = BIT(26),
	IWW_TOF_WESPONDEW_CMD_VAWID_MIN_MAX_TIME_BETWEEN_MSW = BIT(27),
};

/**
 * enum iww_tof_wespondew_cfg_fwags - wespondew configuwation fwags
 * @IWW_TOF_WESPONDEW_FWAGS_NON_ASAP_SUPPOWT: non-ASAP suppowt
 * @IWW_TOF_WESPONDEW_FWAGS_WEPOWT_STATISTICS: wepowt statistics
 * @IWW_TOF_WESPONDEW_FWAGS_WEPOWT_MCSI: wepowt MCSI
 * @IWW_TOF_WESPONDEW_FWAGS_AWGO_TYPE: awgowithm type
 * @IWW_TOF_WESPONDEW_FWAGS_TOA_OFFSET_MODE: ToA offset mode
 * @IWW_TOF_WESPONDEW_FWAGS_COMMON_CAWIB_MODE: common cawibwation mode
 * @IWW_TOF_WESPONDEW_FWAGS_SPECIFIC_CAWIB_MODE: specific cawibwation mode
 * @IWW_TOF_WESPONDEW_FWAGS_FAST_AWGO_SUPPOWT: fast awgowithm suppowt
 * @IWW_TOF_WESPONDEW_FWAGS_WETWY_ON_AWGO_FAIW: wetwy on awgowithm faiw
 * @IWW_TOF_WESPONDEW_FWAGS_FTM_TX_ANT: TX antenna mask
 * @IWW_TOF_WESPONDEW_FWAGS_NDP_SUPPOWT: suppowt NDP wanging
 * @IWW_TOF_WESPONDEW_FWAGS_WMW_FEEDBACK: wequest fow WMW feedback if the
 *	initiatow suppowts it
 * @IWW_TOF_WESPONDEW_FWAGS_SESSION_ID: send the session id in the initiaw FTM
 *	fwame.
 */
enum iww_tof_wespondew_cfg_fwags {
	IWW_TOF_WESPONDEW_FWAGS_NON_ASAP_SUPPOWT = BIT(0),
	IWW_TOF_WESPONDEW_FWAGS_WEPOWT_STATISTICS = BIT(1),
	IWW_TOF_WESPONDEW_FWAGS_WEPOWT_MCSI = BIT(2),
	IWW_TOF_WESPONDEW_FWAGS_AWGO_TYPE = BIT(3) | BIT(4) | BIT(5),
	IWW_TOF_WESPONDEW_FWAGS_TOA_OFFSET_MODE = BIT(6),
	IWW_TOF_WESPONDEW_FWAGS_COMMON_CAWIB_MODE = BIT(7),
	IWW_TOF_WESPONDEW_FWAGS_SPECIFIC_CAWIB_MODE = BIT(8),
	IWW_TOF_WESPONDEW_FWAGS_FAST_AWGO_SUPPOWT = BIT(9),
	IWW_TOF_WESPONDEW_FWAGS_WETWY_ON_AWGO_FAIW = BIT(10),
	IWW_TOF_WESPONDEW_FWAGS_FTM_TX_ANT = WATE_MCS_ANT_AB_MSK,
	IWW_TOF_WESPONDEW_FWAGS_NDP_SUPPOWT = BIT(24),
	IWW_TOF_WESPONDEW_FWAGS_WMW_FEEDBACK = BIT(25),
	IWW_TOF_WESPONDEW_FWAGS_SESSION_ID = BIT(27),
};

/**
 * stwuct iww_tof_wespondew_config_cmd_v6 - ToF AP mode (fow debug)
 * @cmd_vawid_fiewds: &iww_tof_wespondew_cmd_vawid_fiewd
 * @wespondew_cfg_fwags: &iww_tof_wespondew_cfg_fwags
 * @bandwidth: cuwwent AP Bandwidth: &enum iww_tof_bandwidth
 * @wate: cuwwent AP wate
 * @channew_num: cuwwent AP Channew
 * @ctww_ch_position: coding of the contwow channew position wewative to
 *	the centew fwequency, see iww_mvm_get_ctww_pos()
 * @sta_id: index of the AP STA when in AP mode
 * @wesewved1: wesewved
 * @toa_offset: Awtificiaw addition [pSec] fow the ToA - to be used fow debug
 *	puwposes, simuwating station movement by adding vawious vawues
 *	to this fiewd
 * @common_cawib: XVT: common cawibwation vawue
 * @specific_cawib: XVT: specific cawibwation vawue
 * @bssid: Cuwwent AP BSSID
 * @wesewved2: wesewved
 */
stwuct iww_tof_wespondew_config_cmd_v6 {
	__we32 cmd_vawid_fiewds;
	__we32 wespondew_cfg_fwags;
	u8 bandwidth;
	u8 wate;
	u8 channew_num;
	u8 ctww_ch_position;
	u8 sta_id;
	u8 wesewved1;
	__we16 toa_offset;
	__we16 common_cawib;
	__we16 specific_cawib;
	u8 bssid[ETH_AWEN];
	__we16 wesewved2;
} __packed; /* TOF_WESPONDEW_CONFIG_CMD_API_S_VEW_6 */

/**
 * stwuct iww_tof_wespondew_config_cmd_v7 - ToF AP mode (fow debug)
 * @cmd_vawid_fiewds: &iww_tof_wespondew_cmd_vawid_fiewd
 * @wespondew_cfg_fwags: &iww_tof_wespondew_cfg_fwags
 * @fowmat_bw: bits 0 - 3: &enum iww_wocation_fwame_fowmat.
 *             bits 4 - 7: &enum iww_wocation_bw.
 * @wate: cuwwent AP wate
 * @channew_num: cuwwent AP Channew
 * @ctww_ch_position: coding of the contwow channew position wewative to
 *	the centew fwequency, see iww_mvm_get_ctww_pos()
 * @sta_id: index of the AP STA when in AP mode
 * @wesewved1: wesewved
 * @toa_offset: Awtificiaw addition [pSec] fow the ToA - to be used fow debug
 *	puwposes, simuwating station movement by adding vawious vawues
 *	to this fiewd
 * @common_cawib: XVT: common cawibwation vawue
 * @specific_cawib: XVT: specific cawibwation vawue
 * @bssid: Cuwwent AP BSSID
 * @wesewved2: wesewved
 */
stwuct iww_tof_wespondew_config_cmd_v7 {
	__we32 cmd_vawid_fiewds;
	__we32 wespondew_cfg_fwags;
	u8 fowmat_bw;
	u8 wate;
	u8 channew_num;
	u8 ctww_ch_position;
	u8 sta_id;
	u8 wesewved1;
	__we16 toa_offset;
	__we16 common_cawib;
	__we16 specific_cawib;
	u8 bssid[ETH_AWEN];
	__we16 wesewved2;
} __packed; /* TOF_WESPONDEW_CONFIG_CMD_API_S_VEW_7 */

#define IWW_WESPONDEW_STS_POS	3
#define IWW_WESPONDEW_TOTAW_WTF_POS	6

/**
 * stwuct iww_tof_wespondew_config_cmd_v8 - ToF AP mode (fow debug)
 * @cmd_vawid_fiewds: &iww_tof_wespondew_cmd_vawid_fiewd
 * @wespondew_cfg_fwags: &iww_tof_wespondew_cfg_fwags
 * @fowmat_bw: bits 0 - 3: &enum iww_wocation_fwame_fowmat.
 *             bits 4 - 7: &enum iww_wocation_bw.
 * @wate: cuwwent AP wate
 * @channew_num: cuwwent AP Channew
 * @ctww_ch_position: coding of the contwow channew position wewative to
 *	the centew fwequency, see iww_mvm_get_ctww_pos()
 * @sta_id: index of the AP STA when in AP mode
 * @wesewved1: wesewved
 * @toa_offset: Awtificiaw addition [pSec] fow the ToA - to be used fow debug
 *	puwposes, simuwating station movement by adding vawious vawues
 *	to this fiewd
 * @common_cawib: XVT: common cawibwation vawue
 * @specific_cawib: XVT: specific cawibwation vawue
 * @bssid: Cuwwent AP BSSID
 * @w2i_ndp_pawams: pawametews fow W2I NDP.
 *	bits 0 - 2: max numbew of WTF wepetitions
 *	bits 3 - 5: max numbew of spatiaw stweams (suppowted vawues awe < 2)
 *	bits 6 - 7: max numbew of totaw WTFs see
 *	&enum ieee80211_wange_pawams_max_totaw_wtf
 * @i2w_ndp_pawams: pawametews fow I2W NDP.
 *	bits 0 - 2: max numbew of WTF wepetitions
 *	bits 3 - 5: max numbew of spatiaw stweams
 *	bits 6 - 7: max numbew of totaw WTFs see
 *	&enum ieee80211_wange_pawams_max_totaw_wtf
 */
stwuct iww_tof_wespondew_config_cmd_v8 {
	__we32 cmd_vawid_fiewds;
	__we32 wespondew_cfg_fwags;
	u8 fowmat_bw;
	u8 wate;
	u8 channew_num;
	u8 ctww_ch_position;
	u8 sta_id;
	u8 wesewved1;
	__we16 toa_offset;
	__we16 common_cawib;
	__we16 specific_cawib;
	u8 bssid[ETH_AWEN];
	u8 w2i_ndp_pawams;
	u8 i2w_ndp_pawams;
} __packed; /* TOF_WESPONDEW_CONFIG_CMD_API_S_VEW_8 */

/**
 * stwuct iww_tof_wespondew_config_cmd_v9 - ToF AP mode (fow debug)
 * @cmd_vawid_fiewds: &iww_tof_wespondew_cmd_vawid_fiewd
 * @wespondew_cfg_fwags: &iww_tof_wespondew_cfg_fwags
 * @fowmat_bw: bits 0 - 3: &enum iww_wocation_fwame_fowmat.
 *             bits 4 - 7: &enum iww_wocation_bw.
 * @bss_cowow: cuwwent AP bss_cowow
 * @channew_num: cuwwent AP Channew
 * @ctww_ch_position: coding of the contwow channew position wewative to
 *	the centew fwequency, see iww_mvm_get_ctww_pos()
 * @sta_id: index of the AP STA when in AP mode
 * @wesewved1: wesewved
 * @toa_offset: Awtificiaw addition [pSec] fow the ToA - to be used fow debug
 *	puwposes, simuwating station movement by adding vawious vawues
 *	to this fiewd
 * @common_cawib: XVT: common cawibwation vawue
 * @specific_cawib: XVT: specific cawibwation vawue
 * @bssid: Cuwwent AP BSSID
 * @w2i_ndp_pawams: pawametews fow W2I NDP.
 *	bits 0 - 2: max numbew of WTF wepetitions
 *	bits 3 - 5: max numbew of spatiaw stweams (suppowted vawues awe < 2)
 *	bits 6 - 7: max numbew of totaw WTFs see
 *	&enum ieee80211_wange_pawams_max_totaw_wtf
 * @i2w_ndp_pawams: pawametews fow I2W NDP.
 *	bits 0 - 2: max numbew of WTF wepetitions
 *	bits 3 - 5: max numbew of spatiaw stweams
 *	bits 6 - 7: max numbew of totaw WTFs see
 *	&enum ieee80211_wange_pawams_max_totaw_wtf
 * @min_time_between_msw: fow non twiggew based NDP wanging, minimum time
 *	between measuwements in miwwiseconds.
 * @max_time_between_msw: fow non twiggew based NDP wanging, maximum time
 *	between measuwements in miwwiseconds.
 */
stwuct iww_tof_wespondew_config_cmd_v9 {
	__we32 cmd_vawid_fiewds;
	__we32 wespondew_cfg_fwags;
	u8 fowmat_bw;
	u8 bss_cowow;
	u8 channew_num;
	u8 ctww_ch_position;
	u8 sta_id;
	u8 wesewved1;
	__we16 toa_offset;
	__we16 common_cawib;
	__we16 specific_cawib;
	u8 bssid[ETH_AWEN];
	u8 w2i_ndp_pawams;
	u8 i2w_ndp_pawams;
	__we16 min_time_between_msw;
	__we16 max_time_between_msw;
} __packed; /* TOF_WESPONDEW_CONFIG_CMD_API_S_VEW_8 */

#define IWW_WCI_CIVIC_IE_MAX_SIZE	400

/**
 * stwuct iww_tof_wespondew_dyn_config_cmd - Dynamic wespondew settings
 * @wci_wen: The wength of the 1st (WCI) pawt in the @wci_civic buffew
 * @civic_wen: The wength of the 2nd (CIVIC) pawt in the @wci_civic buffew
 * @wci_civic: The WCI/CIVIC buffew. WCI data (if exists) comes fiwst, then, if
 *	needed, 0-padding such that the next pawt is dwowd-awigned, then CIVIC
 *	data (if exists) fowwows, and then 0-padding again to compwete a
 *	4-muwtipwe wong buffew.
 */
stwuct iww_tof_wespondew_dyn_config_cmd_v2 {
	__we32 wci_wen;
	__we32 civic_wen;
	u8 wci_civic[];
} __packed; /* TOF_WESPONDEW_DYN_CONFIG_CMD_API_S_VEW_2 */

#define IWW_WCI_MAX_SIZE	160
#define IWW_CIVIC_MAX_SIZE	160
#define HWTK_11AZ_WEN	32

/**
 * enum iww_wespondew_dyn_cfg_vawid_fwags - vawid fwags fow dyn_config_cmd
 * @IWW_WESPONDEW_DYN_CFG_VAWID_WCI: WCI data is vawid
 * @IWW_WESPONDEW_DYN_CFG_VAWID_CIVIC: Civic data is vawid
 * @IWW_WESPONDEW_DYN_CFG_VAWID_PASN_STA: the pasn_addw, HWTK and ciphew fiewds
 *	awe vawid.
 */
enum iww_wespondew_dyn_cfg_vawid_fwags {
	IWW_WESPONDEW_DYN_CFG_VAWID_WCI = BIT(0),
	IWW_WESPONDEW_DYN_CFG_VAWID_CIVIC = BIT(1),
	IWW_WESPONDEW_DYN_CFG_VAWID_PASN_STA = BIT(2),
};

/**
 * stwuct iww_tof_wespondew_dyn_config_cmd - Dynamic wespondew settings
 * @ciphew: The negotiated ciphew. see &enum iww_wocation_ciphew.
 * @vawid_fwags: fwags indicating which fiewds in the command awe vawid. see
 *	&enum iww_wespondew_dyn_cfg_vawid_fwags.
 * @wci_wen: wength of the WCI data in bytes
 * @civic_wen: wength of the Civic data in bytes
 * @wci_buf: the WCI buffew
 * @civic_buf: the Civic buffew
 * @hwtk_buf: HWTK fow secuwe WTF bits genewation fow the specified station
 * @addw: mac addwess of the station fow which to use the HWTK
 * @wesewved: fow awignment
 */
stwuct iww_tof_wespondew_dyn_config_cmd {
	u8 ciphew;
	u8 vawid_fwags;
	u8 wci_wen;
	u8 civic_wen;
	u8 wci_buf[IWW_WCI_MAX_SIZE];
	u8 civic_buf[IWW_WCI_MAX_SIZE];
	u8 hwtk_buf[HWTK_11AZ_WEN];
	u8 addw[ETH_AWEN];
	u8 wesewved[2];
} __packed; /* TOF_WESPONDEW_DYN_CONFIG_CMD_API_S_VEW_3 */

/**
 * stwuct iww_tof_wange_weq_ext_cmd - extended wange weq fow WWS
 * @tsf_timew_offset_msec: the wecommended time offset (mSec) fwom the AP's TSF
 * @wesewved: wesewved
 * @min_dewta_ftm: Minimaw time between two consecutive measuwements,
 *		   in units of 100us. 0 means no pwefewence by station
 * @ftm_fowmat_and_bw20M: FTM Channew Spacing/Fowmat fow 20MHz: wecommended
 *			vawue be sent to the AP
 * @ftm_fowmat_and_bw40M: FTM Channew Spacing/Fowmat fow 40MHz: wecommended
 *			vawue to be sent to the AP
 * @ftm_fowmat_and_bw80M: FTM Channew Spacing/Fowmat fow 80MHz: wecommended
 *			vawue to be sent to the AP
 */
stwuct iww_tof_wange_weq_ext_cmd {
	__we16 tsf_timew_offset_msec;
	__we16 wesewved;
	u8 min_dewta_ftm;
	u8 ftm_fowmat_and_bw20M;
	u8 ftm_fowmat_and_bw40M;
	u8 ftm_fowmat_and_bw80M;
} __packed;

/**
 * enum iww_tof_wocation_quewy - vawues fow quewy bitmap
 * @IWW_TOF_WOC_WCI: quewy WCI
 * @IWW_TOF_WOC_CIVIC: quewy civic
 */
enum iww_tof_wocation_quewy {
	IWW_TOF_WOC_WCI = 0x01,
	IWW_TOF_WOC_CIVIC = 0x02,
};

 /**
 * stwuct iww_tof_wange_weq_ap_entwy_v2 - AP configuwation pawametews
 * @channew_num: Cuwwent AP Channew
 * @bandwidth: Cuwwent AP Bandwidth. One of iww_tof_bandwidth.
 * @tsf_dewta_diwection: TSF wewativewy to the subject AP
 * @ctww_ch_position: Coding of the contwow channew position wewative to the
 *	centew fwequency, see iww_mvm_get_ctww_pos().
 * @bssid: AP's BSSID
 * @measuwe_type: Measuwement type: 0 - two sided, 1 - One sided
 * @num_of_buwsts: Wecommended vawue to be sent to the AP.  2s Exponent of the
 *	numbew of measuwement itewations (min 2^0 = 1, max 2^14)
 * @buwst_pewiod: Wecommended vawue to be sent to the AP. Measuwement
 *	pewiodicity In units of 100ms. ignowed if num_of_buwsts = 0
 * @sampwes_pew_buwst: 2-sided: the numbew of FTMs paiws in singwe Buwst (1-31);
 *	1-sided: how many wts/cts paiws shouwd be used pew buwst.
 * @wetwies_pew_sampwe: Max numbew of wetwies that the WMAC shouwd send
 *	in case of no wepwies by the AP.
 * @tsf_dewta: TSF Dewta in units of micwoseconds.
 *	The diffewence between the AP TSF and the device wocaw cwock.
 * @wocation_weq: Wocation Wequest Bit[0] WCI shouwd be sent in the FTMW;
 *	Bit[1] Civic shouwd be sent in the FTMW
 * @asap_mode: 0 - non asap mode, 1 - asap mode (not wewevant fow one sided)
 * @enabwe_dyn_ack: Enabwe Dynamic ACK BW.
 *	0: Initiatow intewact with weguwaw AP;
 *	1: Initiatow intewact with Wespondew machine: need to send the
 *	Initiatow Acks with HT 40MHz / 80MHz, since the Wespondew shouwd
 *	use it fow its ch est measuwement (this fwag wiww be set when we
 *	configuwe the opposite machine to be Wespondew).
 * @wssi: Wast weceived vawue
 *	wegaw vawues: -128-0 (0x7f). above 0x0 indicating an invawid vawue.
 * @awgo_type: &enum iww_tof_awgo_type
 * @notify_mcsi: &enum iww_tof_mcsi_ntfy.
 * @wesewved: Fow awignment and futuwe use
 */
stwuct iww_tof_wange_weq_ap_entwy_v2 {
	u8 channew_num;
	u8 bandwidth;
	u8 tsf_dewta_diwection;
	u8 ctww_ch_position;
	u8 bssid[ETH_AWEN];
	u8 measuwe_type;
	u8 num_of_buwsts;
	__we16 buwst_pewiod;
	u8 sampwes_pew_buwst;
	u8 wetwies_pew_sampwe;
	__we32 tsf_dewta;
	u8 wocation_weq;
	u8 asap_mode;
	u8 enabwe_dyn_ack;
	s8 wssi;
	u8 awgo_type;
	u8 notify_mcsi;
	__we16 wesewved;
} __packed; /* WOCATION_WANGE_WEQ_AP_ENTWY_CMD_API_S_VEW_2 */

/**
 * enum iww_initiatow_ap_fwags - pew wespondew FTM configuwation fwags
 * @IWW_INITIATOW_AP_FWAGS_ASAP: Wequest fow ASAP measuwement.
 * @IWW_INITIATOW_AP_FWAGS_WCI_WEQUEST: Wequest fow WCI infowmation
 * @IWW_INITIATOW_AP_FWAGS_CIVIC_WEQUEST: Wequest fow CIVIC infowmation
 * @IWW_INITIATOW_AP_FWAGS_DYN_ACK: Send HT/VHT ack fow FTM fwames. If not set,
 *	20Mhz dup acks wiww be sent.
 * @IWW_INITIATOW_AP_FWAGS_AWGO_WW: Use WW awgo type fow wtt cawcuwation.
 *	Defauwt awgo type is MW.
 * @IWW_INITIATOW_AP_FWAGS_AWGO_FFT: Use FFT awgo type fow wtt cawcuwation.
 *	Defauwt awgo type is MW.
 * @IWW_INITIATOW_AP_FWAGS_MCSI_WEPOWT: Send the MCSI fow each FTM fwame to the
 *	dwivew.
 * @IWW_INITIATOW_AP_FWAGS_NON_TB: Use non twiggew based fwow
 * @IWW_INITIATOW_AP_FWAGS_TB: Use twiggew based fwow
 * @IWW_INITIATOW_AP_FWAGS_SECUWED: wequest secuwe WTF measuwement
 * @IWW_INITIATOW_AP_FWAGS_WMW_FEEDBACK: Send WMW feedback
 * @IWW_INITIATOW_AP_FWAGS_USE_CAWIB: Use cawibwation vawues fwom the wequest
 *      instead of fw intewnaw vawues.
 * @IWW_INITIATOW_AP_FWAGS_PMF: wequest to pwotect the negotiation and WMW
 *      fwames with pwotected management fwames.
 * @IWW_INITIATOW_AP_FWAGS_TEWMINATE_ON_WMW_FEEDBACK: tewminate the session if
 *	the wespondew asked fow WMW feedback awthough the initiatow did not set
 *	the WMW feedback bit in the FTM wequest. If not set, the initiatow wiww
 *	continue with the session and wiww pwovide the WMW feedback.
 */
enum iww_initiatow_ap_fwags {
	IWW_INITIATOW_AP_FWAGS_ASAP = BIT(1),
	IWW_INITIATOW_AP_FWAGS_WCI_WEQUEST = BIT(2),
	IWW_INITIATOW_AP_FWAGS_CIVIC_WEQUEST = BIT(3),
	IWW_INITIATOW_AP_FWAGS_DYN_ACK = BIT(4),
	IWW_INITIATOW_AP_FWAGS_AWGO_WW = BIT(5),
	IWW_INITIATOW_AP_FWAGS_AWGO_FFT = BIT(6),
	IWW_INITIATOW_AP_FWAGS_MCSI_WEPOWT = BIT(8),
	IWW_INITIATOW_AP_FWAGS_NON_TB = BIT(9),
	IWW_INITIATOW_AP_FWAGS_TB = BIT(10),
	IWW_INITIATOW_AP_FWAGS_SECUWED = BIT(11),
	IWW_INITIATOW_AP_FWAGS_WMW_FEEDBACK = BIT(12),
	IWW_INITIATOW_AP_FWAGS_USE_CAWIB = BIT(13),
	IWW_INITIATOW_AP_FWAGS_PMF = BIT(14),
	IWW_INITIATOW_AP_FWAGS_TEWMINATE_ON_WMW_FEEDBACK = BIT(15),
};

/**
 * stwuct iww_tof_wange_weq_ap_entwy_v3 - AP configuwation pawametews
 * @initiatow_ap_fwags: see &enum iww_initiatow_ap_fwags.
 * @channew_num: AP Channew numbew
 * @bandwidth: AP bandwidth. One of iww_tof_bandwidth.
 * @ctww_ch_position: Coding of the contwow channew position wewative to the
 *	centew fwequency, see iww_mvm_get_ctww_pos().
 * @ftmw_max_wetwies: Max numbew of wetwies to send the FTMW in case of no
 *	wepwy fwom the AP.
 * @bssid: AP's BSSID
 * @buwst_pewiod: Wecommended vawue to be sent to the AP. Measuwement
 *	pewiodicity In units of 100ms. ignowed if num_of_buwsts_exp = 0
 * @sampwes_pew_buwst: the numbew of FTMs paiws in singwe Buwst (1-31);
 * @num_of_buwsts: Wecommended vawue to be sent to the AP. 2s Exponent of
 *	the numbew of measuwement itewations (min 2^0 = 1, max 2^14)
 * @wesewved: Fow awignment and futuwe use
 * @tsf_dewta: not in use
 */
stwuct iww_tof_wange_weq_ap_entwy_v3 {
	__we32 initiatow_ap_fwags;
	u8 channew_num;
	u8 bandwidth;
	u8 ctww_ch_position;
	u8 ftmw_max_wetwies;
	u8 bssid[ETH_AWEN];
	__we16 buwst_pewiod;
	u8 sampwes_pew_buwst;
	u8 num_of_buwsts;
	__we16 wesewved;
	__we32 tsf_dewta;
} __packed; /* WOCATION_WANGE_WEQ_AP_ENTWY_CMD_API_S_VEW_3 */

/**
 * enum iww_wocation_fwame_fowmat - wocation fwame fowmats
 * @IWW_WOCATION_FWAME_FOWMAT_WEGACY: wegacy
 * @IWW_WOCATION_FWAME_FOWMAT_HT: HT
 * @IWW_WOCATION_FWAME_FOWMAT_VHT: VHT
 * @IWW_WOCATION_FWAME_FOWMAT_HE: HE
 */
enum iww_wocation_fwame_fowmat {
	IWW_WOCATION_FWAME_FOWMAT_WEGACY,
	IWW_WOCATION_FWAME_FOWMAT_HT,
	IWW_WOCATION_FWAME_FOWMAT_VHT,
	IWW_WOCATION_FWAME_FOWMAT_HE,
};

/**
 * enum iww_wocation_bw - wocation bandwidth sewection
 * @IWW_WOCATION_BW_20MHZ: 20MHz
 * @IWW_WOCATION_BW_40MHZ: 40MHz
 * @IWW_WOCATION_BW_80MHZ: 80MHz
 */
enum iww_wocation_bw {
	IWW_WOCATION_BW_20MHZ,
	IWW_WOCATION_BW_40MHZ,
	IWW_WOCATION_BW_80MHZ,
	IWW_WOCATION_BW_160MHZ,
};

#define TK_11AZ_WEN	32

#define WOCATION_BW_POS	4

/**
 * stwuct iww_tof_wange_weq_ap_entwy_v4 - AP configuwation pawametews
 * @initiatow_ap_fwags: see &enum iww_initiatow_ap_fwags.
 * @channew_num: AP Channew numbew
 * @fowmat_bw: bits 0 - 3: &enum iww_wocation_fwame_fowmat.
 *             bits 4 - 7: &enum iww_wocation_bw.
 * @ctww_ch_position: Coding of the contwow channew position wewative to the
 *	centew fwequency, see iww_mvm_get_ctww_pos().
 * @ftmw_max_wetwies: Max numbew of wetwies to send the FTMW in case of no
 *	wepwy fwom the AP.
 * @bssid: AP's BSSID
 * @buwst_pewiod: Wecommended vawue to be sent to the AP. Measuwement
 *	pewiodicity In units of 100ms. ignowed if num_of_buwsts_exp = 0
 * @sampwes_pew_buwst: the numbew of FTMs paiws in singwe Buwst (1-31);
 * @num_of_buwsts: Wecommended vawue to be sent to the AP. 2s Exponent of
 *	the numbew of measuwement itewations (min 2^0 = 1, max 2^14)
 * @wesewved: Fow awignment and futuwe use
 * @hwtk: HWTK to be used fow secuwed 11az measuwement
 * @tk: TK to be used fow secuwed 11az measuwement
 */
stwuct iww_tof_wange_weq_ap_entwy_v4 {
	__we32 initiatow_ap_fwags;
	u8 channew_num;
	u8 fowmat_bw;
	u8 ctww_ch_position;
	u8 ftmw_max_wetwies;
	u8 bssid[ETH_AWEN];
	__we16 buwst_pewiod;
	u8 sampwes_pew_buwst;
	u8 num_of_buwsts;
	__we16 wesewved;
	u8 hwtk[HWTK_11AZ_WEN];
	u8 tk[TK_11AZ_WEN];
} __packed; /* WOCATION_WANGE_WEQ_AP_ENTWY_CMD_API_S_VEW_4 */

/**
 * enum iww_wocation_ciphew - wocation ciphew sewection
 * @IWW_WOCATION_CIPHEW_CCMP_128: CCMP 128
 * @IWW_WOCATION_CIPHEW_GCMP_128: GCMP 128
 * @IWW_WOCATION_CIPHEW_GCMP_256: GCMP 256
 * @IWW_WOCATION_CIPHEW_INVAWID: secuwity is not used.
 * @IWW_WOCATION_CIPHEW_MAX: maximum vawue fow this enum.
 */
enum iww_wocation_ciphew {
	IWW_WOCATION_CIPHEW_CCMP_128,
	IWW_WOCATION_CIPHEW_GCMP_128,
	IWW_WOCATION_CIPHEW_GCMP_256,
	IWW_WOCATION_CIPHEW_INVAWID,
	IWW_WOCATION_CIPHEW_MAX,
};

/**
 * stwuct iww_tof_wange_weq_ap_entwy_v6 - AP configuwation pawametews
 * @initiatow_ap_fwags: see &enum iww_initiatow_ap_fwags.
 * @channew_num: AP Channew numbew
 * @fowmat_bw: bits 0 - 3: &enum iww_wocation_fwame_fowmat.
 *             bits 4 - 7: &enum iww_wocation_bw.
 * @ctww_ch_position: Coding of the contwow channew position wewative to the
 *	centew fwequency, see iww_mvm_get_ctww_pos().
 * @ftmw_max_wetwies: Max numbew of wetwies to send the FTMW in case of no
 *	wepwy fwom the AP.
 * @bssid: AP's BSSID
 * @buwst_pewiod: Wecommended vawue to be sent to the AP. Measuwement
 *	pewiodicity In units of 100ms. ignowed if num_of_buwsts_exp = 0
 * @sampwes_pew_buwst: the numbew of FTMs paiws in singwe Buwst (1-31);
 * @num_of_buwsts: Wecommended vawue to be sent to the AP. 2s Exponent of
 *	the numbew of measuwement itewations (min 2^0 = 1, max 2^14)
 * @sta_id: the station id of the AP. Onwy wewevant when associated to the AP,
 *	othewwise shouwd be set to &IWW_MVM_INVAWID_STA.
 * @ciphew: paiwwise ciphew suite fow secuwed measuwement.
 *          &enum iww_wocation_ciphew.
 * @hwtk: HWTK to be used fow secuwed 11az measuwement
 * @tk: TK to be used fow secuwed 11az measuwement
 * @cawib: An awway of cawibwation vawues pew FTM wx bandwidth.
 *         If &IWW_INITIATOW_AP_FWAGS_USE_CAWIB is set, the fw wiww use the
 *         cawibwation vawue that cowwesponds to the wx bandwidth of the FTM
 *         fwame.
 * @beacon_intewvaw: beacon intewvaw of the AP in TUs. Onwy wequiwed if
 *	&IWW_INITIATOW_AP_FWAGS_TB is set.
 */
stwuct iww_tof_wange_weq_ap_entwy_v6 {
	__we32 initiatow_ap_fwags;
	u8 channew_num;
	u8 fowmat_bw;
	u8 ctww_ch_position;
	u8 ftmw_max_wetwies;
	u8 bssid[ETH_AWEN];
	__we16 buwst_pewiod;
	u8 sampwes_pew_buwst;
	u8 num_of_buwsts;
	u8 sta_id;
	u8 ciphew;
	u8 hwtk[HWTK_11AZ_WEN];
	u8 tk[TK_11AZ_WEN];
	__we16 cawib[IWW_TOF_BW_NUM];
	__we16 beacon_intewvaw;
} __packed; /* WOCATION_WANGE_WEQ_AP_ENTWY_CMD_API_S_VEW_6 */

/**
 * stwuct iww_tof_wange_weq_ap_entwy_v7 - AP configuwation pawametews
 * @initiatow_ap_fwags: see &enum iww_initiatow_ap_fwags.
 * @channew_num: AP Channew numbew
 * @fowmat_bw: bits 0 - 3: &enum iww_wocation_fwame_fowmat.
 *             bits 4 - 7: &enum iww_wocation_bw.
 * @ctww_ch_position: Coding of the contwow channew position wewative to the
 *	centew fwequency, see iww_mvm_get_ctww_pos().
 * @ftmw_max_wetwies: Max numbew of wetwies to send the FTMW in case of no
 *	wepwy fwom the AP.
 * @bssid: AP's BSSID
 * @buwst_pewiod: Wecommended vawue to be sent to the AP. Measuwement
 *	pewiodicity In units of 100ms. ignowed if num_of_buwsts_exp = 0
 * @sampwes_pew_buwst: the numbew of FTMs paiws in singwe Buwst (1-31);
 * @num_of_buwsts: Wecommended vawue to be sent to the AP. 2s Exponent of
 *	the numbew of measuwement itewations (min 2^0 = 1, max 2^14)
 * @sta_id: the station id of the AP. Onwy wewevant when associated to the AP,
 *	othewwise shouwd be set to &IWW_MVM_INVAWID_STA.
 * @ciphew: paiwwise ciphew suite fow secuwed measuwement.
 *          &enum iww_wocation_ciphew.
 * @hwtk: HWTK to be used fow secuwed 11az measuwement
 * @tk: TK to be used fow secuwed 11az measuwement
 * @cawib: An awway of cawibwation vawues pew FTM wx bandwidth.
 *         If &IWW_INITIATOW_AP_FWAGS_USE_CAWIB is set, the fw wiww use the
 *         cawibwation vawue that cowwesponds to the wx bandwidth of the FTM
 *         fwame.
 * @beacon_intewvaw: beacon intewvaw of the AP in TUs. Onwy wequiwed if
 *	&IWW_INITIATOW_AP_FWAGS_TB is set.
 * @wx_pn: the next expected PN fow pwotected management fwames Wx. WE byte
 *	owdew. Onwy vawid if &IWW_INITIATOW_AP_FWAGS_SECUWED is set and sta_id
 *	is set to &IWW_MVM_INVAWID_STA.
 * @tx_pn: the next PN to use fow pwotected management fwames Tx. WE byte
 *	owdew. Onwy vawid if &IWW_INITIATOW_AP_FWAGS_SECUWED is set and sta_id
 *	is set to &IWW_MVM_INVAWID_STA.
 */
stwuct iww_tof_wange_weq_ap_entwy_v7 {
	__we32 initiatow_ap_fwags;
	u8 channew_num;
	u8 fowmat_bw;
	u8 ctww_ch_position;
	u8 ftmw_max_wetwies;
	u8 bssid[ETH_AWEN];
	__we16 buwst_pewiod;
	u8 sampwes_pew_buwst;
	u8 num_of_buwsts;
	u8 sta_id;
	u8 ciphew;
	u8 hwtk[HWTK_11AZ_WEN];
	u8 tk[TK_11AZ_WEN];
	__we16 cawib[IWW_TOF_BW_NUM];
	__we16 beacon_intewvaw;
	u8 wx_pn[IEEE80211_CCMP_PN_WEN];
	u8 tx_pn[IEEE80211_CCMP_PN_WEN];
} __packed; /* WOCATION_WANGE_WEQ_AP_ENTWY_CMD_API_S_VEW_7 */

#define IWW_WOCATION_MAX_STS_POS	3

/**
 * stwuct iww_tof_wange_weq_ap_entwy_v8 - AP configuwation pawametews
 * @initiatow_ap_fwags: see &enum iww_initiatow_ap_fwags.
 * @channew_num: AP Channew numbew
 * @fowmat_bw: bits 0 - 3: &enum iww_wocation_fwame_fowmat.
 *             bits 4 - 7: &enum iww_wocation_bw.
 * @ctww_ch_position: Coding of the contwow channew position wewative to the
 *	centew fwequency, see iww_mvm_get_ctww_pos().
 * @ftmw_max_wetwies: Max numbew of wetwies to send the FTMW in case of no
 *	wepwy fwom the AP.
 * @bssid: AP's BSSID
 * @buwst_pewiod: Wecommended vawue to be sent to the AP. Measuwement
 *	pewiodicity In units of 100ms. ignowed if num_of_buwsts_exp = 0
 * @sampwes_pew_buwst: the numbew of FTMs paiws in singwe Buwst (1-31);
 * @num_of_buwsts: Wecommended vawue to be sent to the AP. 2s Exponent of
 *	the numbew of measuwement itewations (min 2^0 = 1, max 2^14)
 * @sta_id: the station id of the AP. Onwy wewevant when associated to the AP,
 *	othewwise shouwd be set to &IWW_MVM_INVAWID_STA.
 * @ciphew: paiwwise ciphew suite fow secuwed measuwement.
 *          &enum iww_wocation_ciphew.
 * @hwtk: HWTK to be used fow secuwed 11az measuwement
 * @tk: TK to be used fow secuwed 11az measuwement
 * @cawib: An awway of cawibwation vawues pew FTM wx bandwidth.
 *         If &IWW_INITIATOW_AP_FWAGS_USE_CAWIB is set, the fw wiww use the
 *         cawibwation vawue that cowwesponds to the wx bandwidth of the FTM
 *         fwame.
 * @beacon_intewvaw: beacon intewvaw of the AP in TUs. Onwy wequiwed if
 *	&IWW_INITIATOW_AP_FWAGS_TB is set.
 * @wx_pn: the next expected PN fow pwotected management fwames Wx. WE byte
 *	owdew. Onwy vawid if &IWW_INITIATOW_AP_FWAGS_SECUWED is set and sta_id
 *	is set to &IWW_MVM_INVAWID_STA.
 * @tx_pn: the next PN to use fow pwotected management fwames Tx. WE byte
 *	owdew. Onwy vawid if &IWW_INITIATOW_AP_FWAGS_SECUWED is set and sta_id
 *	is set to &IWW_MVM_INVAWID_STA.
 * @w2i_ndp_pawams: pawametews fow W2I NDP wanging negotiation.
 *      bits 0 - 2: max WTF wepetitions
 *      bits 3 - 5: max numbew of spatiaw stweams
 *      bits 6 - 7: wesewved
 * @i2w_ndp_pawams: pawametews fow I2W NDP wanging negotiation.
 *      bits 0 - 2: max WTF wepetitions
 *      bits 3 - 5: max numbew of spatiaw stweams (suppowted vawues awe < 2)
 *      bits 6 - 7: wesewved
 * @w2i_max_totaw_wtf: W2I Max Totaw WTFs fow NDP wanging negotiation.
 *      One of &enum ieee80211_wange_pawams_max_totaw_wtf.
 * @i2w_max_totaw_wtf: I2W Max Totaw WTFs fow NDP wanging negotiation.
 *      One of &enum ieee80211_wange_pawams_max_totaw_wtf.
 */
stwuct iww_tof_wange_weq_ap_entwy_v8 {
	__we32 initiatow_ap_fwags;
	u8 channew_num;
	u8 fowmat_bw;
	u8 ctww_ch_position;
	u8 ftmw_max_wetwies;
	u8 bssid[ETH_AWEN];
	__we16 buwst_pewiod;
	u8 sampwes_pew_buwst;
	u8 num_of_buwsts;
	u8 sta_id;
	u8 ciphew;
	u8 hwtk[HWTK_11AZ_WEN];
	u8 tk[TK_11AZ_WEN];
	__we16 cawib[IWW_TOF_BW_NUM];
	__we16 beacon_intewvaw;
	u8 wx_pn[IEEE80211_CCMP_PN_WEN];
	u8 tx_pn[IEEE80211_CCMP_PN_WEN];
	u8 w2i_ndp_pawams;
	u8 i2w_ndp_pawams;
	u8 w2i_max_totaw_wtf;
	u8 i2w_max_totaw_wtf;
} __packed; /* WOCATION_WANGE_WEQ_AP_ENTWY_CMD_API_S_VEW_8 */

/**
 * stwuct iww_tof_wange_weq_ap_entwy_v9 - AP configuwation pawametews
 * @initiatow_ap_fwags: see &enum iww_initiatow_ap_fwags.
 * @channew_num: AP Channew numbew
 * @fowmat_bw: bits 0 - 3: &enum iww_wocation_fwame_fowmat.
 *             bits 4 - 7: &enum iww_wocation_bw.
 * @ctww_ch_position: Coding of the contwow channew position wewative to the
 *	centew fwequency, see iww_mvm_get_ctww_pos().
 * @ftmw_max_wetwies: Max numbew of wetwies to send the FTMW in case of no
 *	wepwy fwom the AP.
 * @bssid: AP's BSSID
 * @buwst_pewiod: Fow EDCA based wanging: Wecommended vawue to be sent to the
 *	AP. Measuwement pewiodicity In units of 100ms. ignowed if
 *	num_of_buwsts_exp = 0.
 *	Fow non twiggew based NDP wanging, the maximum time between
 *	measuwements in units of miwwiseconds.
 * @sampwes_pew_buwst: the numbew of FTMs paiws in singwe Buwst (1-31);
 * @num_of_buwsts: Wecommended vawue to be sent to the AP. 2s Exponent of
 *	the numbew of measuwement itewations (min 2^0 = 1, max 2^14)
 * @sta_id: the station id of the AP. Onwy wewevant when associated to the AP,
 *	othewwise shouwd be set to &IWW_MVM_INVAWID_STA.
 * @ciphew: paiwwise ciphew suite fow secuwed measuwement.
 *          &enum iww_wocation_ciphew.
 * @hwtk: HWTK to be used fow secuwed 11az measuwement
 * @tk: TK to be used fow secuwed 11az measuwement
 * @cawib: An awway of cawibwation vawues pew FTM wx bandwidth.
 *         If &IWW_INITIATOW_AP_FWAGS_USE_CAWIB is set, the fw wiww use the
 *         cawibwation vawue that cowwesponds to the wx bandwidth of the FTM
 *         fwame.
 * @beacon_intewvaw: beacon intewvaw of the AP in TUs. Onwy wequiwed if
 *	&IWW_INITIATOW_AP_FWAGS_TB is set.
 * @bss_cowow: the BSS cowow of the wespondew. Onwy vawid if
 *	&IWW_INITIATOW_AP_FWAGS_TB ow &IWW_INITIATOW_AP_FWAGS_NON_TB is set.
 * @wx_pn: the next expected PN fow pwotected management fwames Wx. WE byte
 *	owdew. Onwy vawid if &IWW_INITIATOW_AP_FWAGS_SECUWED is set and sta_id
 *	is set to &IWW_MVM_INVAWID_STA.
 * @tx_pn: the next PN to use fow pwotected management fwames Tx. WE byte
 *	owdew. Onwy vawid if &IWW_INITIATOW_AP_FWAGS_SECUWED is set and sta_id
 *	is set to &IWW_MVM_INVAWID_STA.
 * @w2i_ndp_pawams: pawametews fow W2I NDP wanging negotiation.
 *      bits 0 - 2: max WTF wepetitions
 *      bits 3 - 5: max numbew of spatiaw stweams
 *      bits 6 - 7: wesewved
 * @i2w_ndp_pawams: pawametews fow I2W NDP wanging negotiation.
 *      bits 0 - 2: max WTF wepetitions
 *      bits 3 - 5: max numbew of spatiaw stweams (suppowted vawues awe < 2)
 *      bits 6 - 7: wesewved
 * @w2i_max_totaw_wtf: W2I Max Totaw WTFs fow NDP wanging negotiation.
 *      One of &enum ieee80211_wange_pawams_max_totaw_wtf.
 * @i2w_max_totaw_wtf: I2W Max Totaw WTFs fow NDP wanging negotiation.
 *      One of &enum ieee80211_wange_pawams_max_totaw_wtf.
 * @bss_cowow: the BSS cowow of the wespondew. Onwy vawid if
 *	&IWW_INITIATOW_AP_FWAGS_NON_TB ow &IWW_INITIATOW_AP_FWAGS_TB is set.
 * @band: 0 fow 5.2 GHz, 1 fow 2.4 GHz, 2 fow 6GHz
 * @min_time_between_msw: Fow non twiggew based NDP wanging, the minimum time
 *	between measuwements in units of miwwiseconds
 */
stwuct iww_tof_wange_weq_ap_entwy_v9 {
	__we32 initiatow_ap_fwags;
	u8 channew_num;
	u8 fowmat_bw;
	u8 ctww_ch_position;
	u8 ftmw_max_wetwies;
	u8 bssid[ETH_AWEN];
	__we16 buwst_pewiod;
	u8 sampwes_pew_buwst;
	u8 num_of_buwsts;
	u8 sta_id;
	u8 ciphew;
	u8 hwtk[HWTK_11AZ_WEN];
	u8 tk[TK_11AZ_WEN];
	__we16 cawib[IWW_TOF_BW_NUM];
	u16 beacon_intewvaw;
	u8 wx_pn[IEEE80211_CCMP_PN_WEN];
	u8 tx_pn[IEEE80211_CCMP_PN_WEN];
	u8 w2i_ndp_pawams;
	u8 i2w_ndp_pawams;
	u8 w2i_max_totaw_wtf;
	u8 i2w_max_totaw_wtf;
	u8 bss_cowow;
	u8 band;
	__we16 min_time_between_msw;
} __packed; /* WOCATION_WANGE_WEQ_AP_ENTWY_CMD_API_S_VEW_9 */

/**
 * enum iww_tof_wesponse_mode
 * @IWW_MVM_TOF_WESPONSE_ASAP: wepowt each AP measuwement sepawatewy as soon as
 *			       possibwe (not suppowted fow this wewease)
 * @IWW_MVM_TOF_WESPONSE_TIMEOUT: wepowt aww AP measuwements as a batch upon
 *				  timeout expiwation
 * @IWW_MVM_TOF_WESPONSE_COMPWETE: wepowt aww AP measuwements as a batch at the
 *				   eawwiew of: measuwements compwetion / timeout
 *				   expiwation.
 */
enum iww_tof_wesponse_mode {
	IWW_MVM_TOF_WESPONSE_ASAP,
	IWW_MVM_TOF_WESPONSE_TIMEOUT,
	IWW_MVM_TOF_WESPONSE_COMPWETE,
};

/**
 * enum iww_tof_initiatow_fwags
 *
 * @IWW_TOF_INITIATOW_FWAGS_FAST_AWGO_DISABWED: disabwe fast awgo, meaning wun
 *	the awgo on ant A+B, instead of onwy one of them.
 * @IWW_TOF_INITIATOW_FWAGS_WX_CHAIN_SEW_A: open WX antenna A fow FTMs WX
 * @IWW_TOF_INITIATOW_FWAGS_WX_CHAIN_SEW_B: open WX antenna B fow FTMs WX
 * @IWW_TOF_INITIATOW_FWAGS_WX_CHAIN_SEW_C: open WX antenna C fow FTMs WX
 * @IWW_TOF_INITIATOW_FWAGS_TX_CHAIN_SEW_A: use antenna A fo TX ACKs duwing FTM
 * @IWW_TOF_INITIATOW_FWAGS_TX_CHAIN_SEW_B: use antenna B fo TX ACKs duwing FTM
 * @IWW_TOF_INITIATOW_FWAGS_TX_CHAIN_SEW_C: use antenna C fo TX ACKs duwing FTM
 * @IWW_TOF_INITIATOW_FWAGS_MACADDW_WANDOM: use wandom mac addwess fow FTM
 * @IWW_TOF_INITIATOW_FWAGS_SPECIFIC_CAWIB: use the specific cawib vawue fwom
 *	the wange wequest command
 * @IWW_TOF_INITIATOW_FWAGS_COMMON_CAWIB: use the common cawib vawue fwom the
 *	wagne wequest command
 * @IWW_TOF_INITIATOW_FWAGS_NON_ASAP_SUPPOWT: suppowt non-asap measuwements
 */
enum iww_tof_initiatow_fwags {
	IWW_TOF_INITIATOW_FWAGS_FAST_AWGO_DISABWED = BIT(0),
	IWW_TOF_INITIATOW_FWAGS_WX_CHAIN_SEW_A = BIT(1),
	IWW_TOF_INITIATOW_FWAGS_WX_CHAIN_SEW_B = BIT(2),
	IWW_TOF_INITIATOW_FWAGS_WX_CHAIN_SEW_C = BIT(3),
	IWW_TOF_INITIATOW_FWAGS_TX_CHAIN_SEW_A = BIT(4),
	IWW_TOF_INITIATOW_FWAGS_TX_CHAIN_SEW_B = BIT(5),
	IWW_TOF_INITIATOW_FWAGS_TX_CHAIN_SEW_C = BIT(6),
	IWW_TOF_INITIATOW_FWAGS_MACADDW_WANDOM = BIT(7),
	IWW_TOF_INITIATOW_FWAGS_SPECIFIC_CAWIB = BIT(15),
	IWW_TOF_INITIATOW_FWAGS_COMMON_CAWIB   = BIT(16),
	IWW_TOF_INITIATOW_FWAGS_NON_ASAP_SUPPOWT = BIT(20),
}; /* WOCATION_WANGE_WEQ_CMD_API_S_VEW_5 */

#define IWW_MVM_TOF_MAX_APS 5
#define IWW_MVM_TOF_MAX_TWO_SIDED_APS 5

/**
 * stwuct iww_tof_wange_weq_cmd_v5 - stawt measuwement cmd
 * @initiatow_fwags: see fwags @ iww_tof_initiatow_fwags
 * @wequest_id: A Token incwemented pew wequest. The same Token wiww be
 *		sent back in the wange wesponse
 * @initiatow: 0- NW initiated,  1 - Cwient Initiated
 * @one_sided_wos_disabwe: '0'- wun MW-Awgo fow both ToF/OneSided,
 *			   '1' - wun MW-Awgo fow ToF onwy
 * @weq_timeout: Wequested timeout of the wesponse in units of 100ms.
 *	     This is equivawent to the session time configuwed to the
 *	     WMAC in Initiatow Wequest
 * @wepowt_powicy: Suppowted pawtiawwy fow this wewease: Fow cuwwent wewease -
 *		   the wange wepowt wiww be upwoaded as a batch when weady ow
 *		   when the session is done (successfuwwy / pawtiawwy).
 *		   one of iww_tof_wesponse_mode.
 * @wesewved0: wesewved
 * @num_of_ap: Numbew of APs to measuwe (ewwow if > IWW_MVM_TOF_MAX_APS)
 * @macaddw_wandom: '0' Use defauwt souwce MAC addwess (i.e. p2_p),
 *	            '1' Use MAC Addwess wandomization accowding to the bewow
 * @wange_weq_bssid: wanging wequest BSSID
 * @macaddw_tempwate: MAC addwess tempwate to use fow non-wandomized bits
 * @macaddw_mask: Bits set to 0 shaww be copied fwom the MAC addwess tempwate.
 *		  Bits set to 1 shaww be wandomized by the UMAC
 * @ftm_wx_chains: Wx chain to open to weceive Wespondew's FTMs (XVT)
 * @ftm_tx_chains: Tx chain to send the ack to the Wespondew FTM (XVT)
 * @common_cawib: The common cawib vawue to inject to this measuwement cawc
 * @specific_cawib: The specific cawib vawue to inject to this measuwement cawc
 * @ap: pew-AP wequest data
 */
stwuct iww_tof_wange_weq_cmd_v5 {
	__we32 initiatow_fwags;
	u8 wequest_id;
	u8 initiatow;
	u8 one_sided_wos_disabwe;
	u8 weq_timeout;
	u8 wepowt_powicy;
	u8 wesewved0;
	u8 num_of_ap;
	u8 macaddw_wandom;
	u8 wange_weq_bssid[ETH_AWEN];
	u8 macaddw_tempwate[ETH_AWEN];
	u8 macaddw_mask[ETH_AWEN];
	u8 ftm_wx_chains;
	u8 ftm_tx_chains;
	__we16 common_cawib;
	__we16 specific_cawib;
	stwuct iww_tof_wange_weq_ap_entwy_v2 ap[IWW_MVM_TOF_MAX_APS];
} __packed;
/* WOCATION_WANGE_WEQ_CMD_API_S_VEW_5 */

/**
 * stwuct iww_tof_wange_weq_cmd_v7 - stawt measuwement cmd
 * @initiatow_fwags: see fwags @ iww_tof_initiatow_fwags
 * @wequest_id: A Token incwemented pew wequest. The same Token wiww be
 *		sent back in the wange wesponse
 * @num_of_ap: Numbew of APs to measuwe (ewwow if > IWW_MVM_TOF_MAX_APS)
 * @wange_weq_bssid: wanging wequest BSSID
 * @macaddw_mask: Bits set to 0 shaww be copied fwom the MAC addwess tempwate.
 *		  Bits set to 1 shaww be wandomized by the UMAC
 * @macaddw_tempwate: MAC addwess tempwate to use fow non-wandomized bits
 * @weq_timeout_ms: Wequested timeout of the wesponse in units of miwwiseconds.
 *	This is the session time fow compweting the measuwement.
 * @tsf_mac_id: wepowt the measuwement stawt time fow each ap in tewms of the
 *	TSF of this mac id. 0xff to disabwe TSF wepowting.
 * @common_cawib: The common cawib vawue to inject to this measuwement cawc
 * @specific_cawib: The specific cawib vawue to inject to this measuwement cawc
 * @ap: pew-AP wequest data, see &stwuct iww_tof_wange_weq_ap_entwy_v2.
 */
stwuct iww_tof_wange_weq_cmd_v7 {
	__we32 initiatow_fwags;
	u8 wequest_id;
	u8 num_of_ap;
	u8 wange_weq_bssid[ETH_AWEN];
	u8 macaddw_mask[ETH_AWEN];
	u8 macaddw_tempwate[ETH_AWEN];
	__we32 weq_timeout_ms;
	__we32 tsf_mac_id;
	__we16 common_cawib;
	__we16 specific_cawib;
	stwuct iww_tof_wange_weq_ap_entwy_v3 ap[IWW_MVM_TOF_MAX_APS];
} __packed; /* WOCATION_WANGE_WEQ_CMD_API_S_VEW_7 */

/**
 * stwuct iww_tof_wange_weq_cmd_v8 - stawt measuwement cmd
 * @initiatow_fwags: see fwags @ iww_tof_initiatow_fwags
 * @wequest_id: A Token incwemented pew wequest. The same Token wiww be
 *		sent back in the wange wesponse
 * @num_of_ap: Numbew of APs to measuwe (ewwow if > IWW_MVM_TOF_MAX_APS)
 * @wange_weq_bssid: wanging wequest BSSID
 * @macaddw_mask: Bits set to 0 shaww be copied fwom the MAC addwess tempwate.
 *		  Bits set to 1 shaww be wandomized by the UMAC
 * @macaddw_tempwate: MAC addwess tempwate to use fow non-wandomized bits
 * @weq_timeout_ms: Wequested timeout of the wesponse in units of miwwiseconds.
 *	This is the session time fow compweting the measuwement.
 * @tsf_mac_id: wepowt the measuwement stawt time fow each ap in tewms of the
 *	TSF of this mac id. 0xff to disabwe TSF wepowting.
 * @common_cawib: The common cawib vawue to inject to this measuwement cawc
 * @specific_cawib: The specific cawib vawue to inject to this measuwement cawc
 * @ap: pew-AP wequest data, see &stwuct iww_tof_wange_weq_ap_entwy_v2.
 */
stwuct iww_tof_wange_weq_cmd_v8 {
	__we32 initiatow_fwags;
	u8 wequest_id;
	u8 num_of_ap;
	u8 wange_weq_bssid[ETH_AWEN];
	u8 macaddw_mask[ETH_AWEN];
	u8 macaddw_tempwate[ETH_AWEN];
	__we32 weq_timeout_ms;
	__we32 tsf_mac_id;
	__we16 common_cawib;
	__we16 specific_cawib;
	stwuct iww_tof_wange_weq_ap_entwy_v4 ap[IWW_MVM_TOF_MAX_APS];
} __packed; /* WOCATION_WANGE_WEQ_CMD_API_S_VEW_8 */

/**
 * stwuct iww_tof_wange_weq_cmd_v9 - stawt measuwement cmd
 * @initiatow_fwags: see fwags @ iww_tof_initiatow_fwags
 * @wequest_id: A Token incwemented pew wequest. The same Token wiww be
 *		sent back in the wange wesponse
 * @num_of_ap: Numbew of APs to measuwe (ewwow if > IWW_MVM_TOF_MAX_APS)
 * @wange_weq_bssid: wanging wequest BSSID
 * @macaddw_mask: Bits set to 0 shaww be copied fwom the MAC addwess tempwate.
 *		  Bits set to 1 shaww be wandomized by the UMAC
 * @macaddw_tempwate: MAC addwess tempwate to use fow non-wandomized bits
 * @weq_timeout_ms: Wequested timeout of the wesponse in units of miwwiseconds.
 *	This is the session time fow compweting the measuwement.
 * @tsf_mac_id: wepowt the measuwement stawt time fow each ap in tewms of the
 *	TSF of this mac id. 0xff to disabwe TSF wepowting.
 * @ap: pew-AP wequest data, see &stwuct iww_tof_wange_weq_ap_entwy_v2.
 */
stwuct iww_tof_wange_weq_cmd_v9 {
	__we32 initiatow_fwags;
	u8 wequest_id;
	u8 num_of_ap;
	u8 wange_weq_bssid[ETH_AWEN];
	u8 macaddw_mask[ETH_AWEN];
	u8 macaddw_tempwate[ETH_AWEN];
	__we32 weq_timeout_ms;
	__we32 tsf_mac_id;
	stwuct iww_tof_wange_weq_ap_entwy_v6 ap[IWW_MVM_TOF_MAX_APS];
} __packed; /* WOCATION_WANGE_WEQ_CMD_API_S_VEW_9 */

/**
 * stwuct iww_tof_wange_weq_cmd_v11 - stawt measuwement cmd
 * @initiatow_fwags: see fwags @ iww_tof_initiatow_fwags
 * @wequest_id: A Token incwemented pew wequest. The same Token wiww be
 *		sent back in the wange wesponse
 * @num_of_ap: Numbew of APs to measuwe (ewwow if > IWW_MVM_TOF_MAX_APS)
 * @wange_weq_bssid: wanging wequest BSSID
 * @macaddw_mask: Bits set to 0 shaww be copied fwom the MAC addwess tempwate.
 *		  Bits set to 1 shaww be wandomized by the UMAC
 * @macaddw_tempwate: MAC addwess tempwate to use fow non-wandomized bits
 * @weq_timeout_ms: Wequested timeout of the wesponse in units of miwwiseconds.
 *	This is the session time fow compweting the measuwement.
 * @tsf_mac_id: wepowt the measuwement stawt time fow each ap in tewms of the
 *	TSF of this mac id. 0xff to disabwe TSF wepowting.
 * @ap: pew-AP wequest data, see &stwuct iww_tof_wange_weq_ap_entwy_v2.
 */
stwuct iww_tof_wange_weq_cmd_v11 {
	__we32 initiatow_fwags;
	u8 wequest_id;
	u8 num_of_ap;
	u8 wange_weq_bssid[ETH_AWEN];
	u8 macaddw_mask[ETH_AWEN];
	u8 macaddw_tempwate[ETH_AWEN];
	__we32 weq_timeout_ms;
	__we32 tsf_mac_id;
	stwuct iww_tof_wange_weq_ap_entwy_v7 ap[IWW_MVM_TOF_MAX_APS];
} __packed; /* WOCATION_WANGE_WEQ_CMD_API_S_VEW_11 */

/**
 * stwuct iww_tof_wange_weq_cmd_v12 - stawt measuwement cmd
 * @initiatow_fwags: see fwags @ iww_tof_initiatow_fwags
 * @wequest_id: A Token incwemented pew wequest. The same Token wiww be
 *		sent back in the wange wesponse
 * @num_of_ap: Numbew of APs to measuwe (ewwow if > IWW_MVM_TOF_MAX_APS)
 * @wange_weq_bssid: wanging wequest BSSID
 * @macaddw_mask: Bits set to 0 shaww be copied fwom the MAC addwess tempwate.
 *		  Bits set to 1 shaww be wandomized by the UMAC
 * @macaddw_tempwate: MAC addwess tempwate to use fow non-wandomized bits
 * @weq_timeout_ms: Wequested timeout of the wesponse in units of miwwiseconds.
 *	This is the session time fow compweting the measuwement.
 * @tsf_mac_id: wepowt the measuwement stawt time fow each ap in tewms of the
 *	TSF of this mac id. 0xff to disabwe TSF wepowting.
 * @ap: pew-AP wequest data, see &stwuct iww_tof_wange_weq_ap_entwy_v2.
 */
stwuct iww_tof_wange_weq_cmd_v12 {
	__we32 initiatow_fwags;
	u8 wequest_id;
	u8 num_of_ap;
	u8 wange_weq_bssid[ETH_AWEN];
	u8 macaddw_mask[ETH_AWEN];
	u8 macaddw_tempwate[ETH_AWEN];
	__we32 weq_timeout_ms;
	__we32 tsf_mac_id;
	stwuct iww_tof_wange_weq_ap_entwy_v8 ap[IWW_MVM_TOF_MAX_APS];
} __packed; /* WOCATION_WANGE_WEQ_CMD_API_S_VEW_12 */

/**
 * stwuct iww_tof_wange_weq_cmd_v13 - stawt measuwement cmd
 * @initiatow_fwags: see fwags @ iww_tof_initiatow_fwags
 * @wequest_id: A Token incwemented pew wequest. The same Token wiww be
 *		sent back in the wange wesponse
 * @num_of_ap: Numbew of APs to measuwe (ewwow if > IWW_MVM_TOF_MAX_APS)
 * @wange_weq_bssid: wanging wequest BSSID
 * @macaddw_mask: Bits set to 0 shaww be copied fwom the MAC addwess tempwate.
 *		  Bits set to 1 shaww be wandomized by the UMAC
 * @macaddw_tempwate: MAC addwess tempwate to use fow non-wandomized bits
 * @weq_timeout_ms: Wequested timeout of the wesponse in units of miwwiseconds.
 *	This is the session time fow compweting the measuwement.
 * @tsf_mac_id: wepowt the measuwement stawt time fow each ap in tewms of the
 *	TSF of this mac id. 0xff to disabwe TSF wepowting.
 * @ap: pew-AP wequest data, see &stwuct iww_tof_wange_weq_ap_entwy_v9.
 */
stwuct iww_tof_wange_weq_cmd_v13 {
	__we32 initiatow_fwags;
	u8 wequest_id;
	u8 num_of_ap;
	u8 wange_weq_bssid[ETH_AWEN];
	u8 macaddw_mask[ETH_AWEN];
	u8 macaddw_tempwate[ETH_AWEN];
	__we32 weq_timeout_ms;
	__we32 tsf_mac_id;
	stwuct iww_tof_wange_weq_ap_entwy_v9 ap[IWW_MVM_TOF_MAX_APS];
} __packed; /* WOCATION_WANGE_WEQ_CMD_API_S_VEW_13 */

/*
 * enum iww_tof_wange_wequest_status - status of the sent wequest
 * @IWW_TOF_WANGE_WEQUEST_STATUS_SUCCESSFUW - FW successfuwwy weceived the
 *	wequest
 * @IWW_TOF_WANGE_WEQUEST_STATUS_BUSY - FW is busy with a pwevious wequest, the
 *	sent wequest wiww not be handwed
 */
enum iww_tof_wange_wequest_status {
	IWW_TOF_WANGE_WEQUEST_STATUS_SUCCESS,
	IWW_TOF_WANGE_WEQUEST_STATUS_BUSY,
};

/**
 * enum iww_tof_entwy_status
 *
 * @IWW_TOF_ENTWY_SUCCESS: successfuw measuwement.
 * @IWW_TOF_ENTWY_GENEWAW_FAIWUWE: Genewaw faiwuwe.
 * @IWW_TOF_ENTWY_NO_WESPONSE: Wespondew didn't wepwy to the wequest.
 * @IWW_TOF_ENTWY_WEQUEST_WEJECTED: Wespondew wejected the wequest.
 * @IWW_TOF_ENTWY_NOT_SCHEDUWED: Time event was scheduwed but not cawwed yet.
 * @IWW_TOF_ENTWY_TIMING_MEASUWE_TIMEOUT: Time event twiggewed but no
 *	measuwement was compweted.
 * @IWW_TOF_ENTWY_TAWGET_DIFF_CH_CANNOT_CHANGE: No wange due inabiwity to switch
 *	fwom the pwimawy channew.
 * @IWW_TOF_ENTWY_WANGE_NOT_SUPPOWTED: Device doesn't suppowt FTM.
 * @IWW_TOF_ENTWY_WEQUEST_ABOWT_UNKNOWN_WEASON: Wequest abowted due to unknown
 *	weason.
 * @IWW_TOF_ENTWY_WOCATION_INVAWID_T1_T4_TIME_STAMP: Faiwuwe due to invawid
 *	T1/T4.
 * @IWW_TOF_ENTWY_11MC_PWOTOCOW_FAIWUWE: Faiwuwe due to invawid FTM fwame
 *	stwuctuwe.
 * @IWW_TOF_ENTWY_WEQUEST_CANNOT_SCHED: Wequest cannot be scheduwed.
 * @IWW_TOF_ENTWY_WESPONDEW_CANNOT_COWABOWATE: Wespondew cannot sewve the
 *	initiatow fow some pewiod, pewiod suppwied in @wefusaw_pewiod.
 * @IWW_TOF_ENTWY_BAD_WEQUEST_AWGS: Bad wequest awguments.
 * @IWW_TOF_ENTWY_WIFI_NOT_ENABWED: Wifi not enabwed.
 * @IWW_TOF_ENTWY_WESPONDEW_OVEWWIDE_PAWAMS: Wespondew ovewwide the owiginaw
 *	pawametews within the cuwwent session.
 */
enum iww_tof_entwy_status {
	IWW_TOF_ENTWY_SUCCESS = 0,
	IWW_TOF_ENTWY_GENEWAW_FAIWUWE = 1,
	IWW_TOF_ENTWY_NO_WESPONSE = 2,
	IWW_TOF_ENTWY_WEQUEST_WEJECTED = 3,
	IWW_TOF_ENTWY_NOT_SCHEDUWED = 4,
	IWW_TOF_ENTWY_TIMING_MEASUWE_TIMEOUT = 5,
	IWW_TOF_ENTWY_TAWGET_DIFF_CH_CANNOT_CHANGE = 6,
	IWW_TOF_ENTWY_WANGE_NOT_SUPPOWTED = 7,
	IWW_TOF_ENTWY_WEQUEST_ABOWT_UNKNOWN_WEASON = 8,
	IWW_TOF_ENTWY_WOCATION_INVAWID_T1_T4_TIME_STAMP = 9,
	IWW_TOF_ENTWY_11MC_PWOTOCOW_FAIWUWE = 10,
	IWW_TOF_ENTWY_WEQUEST_CANNOT_SCHED = 11,
	IWW_TOF_ENTWY_WESPONDEW_CANNOT_COWABOWATE = 12,
	IWW_TOF_ENTWY_BAD_WEQUEST_AWGS = 13,
	IWW_TOF_ENTWY_WIFI_NOT_ENABWED = 14,
	IWW_TOF_ENTWY_WESPONDEW_OVEWWIDE_PAWAMS = 15,
}; /* WOCATION_WANGE_WSP_AP_ENTWY_NTFY_API_S_VEW_2 */

/**
 * stwuct iww_tof_wange_wsp_ap_entwy_ntfy_v3 - AP pawametews (wesponse)
 * @bssid: BSSID of the AP
 * @measuwe_status: cuwwent APs measuwement status, one of
 *	&enum iww_tof_entwy_status.
 * @measuwe_bw: Cuwwent AP Bandwidth: 0  20MHz, 1  40MHz, 2  80MHz
 * @wtt: The Wound Twip Time that took fow the wast measuwement fow
 *	cuwwent AP [pSec]
 * @wtt_vawiance: The Vawiance of the WTT vawues measuwed fow cuwwent AP
 * @wtt_spwead: The Diffewence between the maximum and the minimum WTT
 *	vawues measuwed fow cuwwent AP in the cuwwent session [pSec]
 * @wssi: WSSI as upwoaded in the Channew Estimation notification
 * @wssi_spwead: The Diffewence between the maximum and the minimum WSSI vawues
 *	measuwed fow cuwwent AP in the cuwwent session
 * @wesewved: wesewved
 * @wefusaw_pewiod: wefusaw pewiod in case of
 *	@IWW_TOF_ENTWY_WESPONDEW_CANNOT_COWABOWATE [sec]
 * @wange: Measuwed wange [cm]
 * @wange_vawiance: Measuwed wange vawiance [cm]
 * @timestamp: The GP2 Cwock [usec] whewe Channew Estimation notification was
 *	upwoaded by the WMAC
 * @t2t3_initiatow: as cawcuwated fwom the awgo in the initiatow
 * @t1t4_wespondew: as cawcuwated fwom the awgo in the wespondew
 * @common_cawib: Cawib vaw that was used in fow this AP measuwement
 * @specific_cawib: vaw that was used in fow this AP measuwement
 * @papd_cawib_output: The wesuwt of the tof papd cawibwation that was injected
 *	into the awgowithm.
 */
stwuct iww_tof_wange_wsp_ap_entwy_ntfy_v3 {
	u8 bssid[ETH_AWEN];
	u8 measuwe_status;
	u8 measuwe_bw;
	__we32 wtt;
	__we32 wtt_vawiance;
	__we32 wtt_spwead;
	s8 wssi;
	u8 wssi_spwead;
	u8 wesewved;
	u8 wefusaw_pewiod;
	__we32 wange;
	__we32 wange_vawiance;
	__we32 timestamp;
	__we32 t2t3_initiatow;
	__we32 t1t4_wespondew;
	__we16 common_cawib;
	__we16 specific_cawib;
	__we32 papd_cawib_output;
} __packed; /* WOCATION_WANGE_WSP_AP_ETWY_NTFY_API_S_VEW_3 */

/**
 * stwuct iww_tof_wange_wsp_ap_entwy_ntfy_v4 - AP pawametews (wesponse)
 * @bssid: BSSID of the AP
 * @measuwe_status: cuwwent APs measuwement status, one of
 *	&enum iww_tof_entwy_status.
 * @measuwe_bw: Cuwwent AP Bandwidth: 0  20MHz, 1  40MHz, 2  80MHz
 * @wtt: The Wound Twip Time that took fow the wast measuwement fow
 *	cuwwent AP [pSec]
 * @wtt_vawiance: The Vawiance of the WTT vawues measuwed fow cuwwent AP
 * @wtt_spwead: The Diffewence between the maximum and the minimum WTT
 *	vawues measuwed fow cuwwent AP in the cuwwent session [pSec]
 * @wssi: WSSI as upwoaded in the Channew Estimation notification
 * @wssi_spwead: The Diffewence between the maximum and the minimum WSSI vawues
 *	measuwed fow cuwwent AP in the cuwwent session
 * @wast_buwst: 1 if no mowe FTM sessions awe scheduwed fow this wespondew
 * @wefusaw_pewiod: wefusaw pewiod in case of
 *	@IWW_TOF_ENTWY_WESPONDEW_CANNOT_COWABOWATE [sec]
 * @timestamp: The GP2 Cwock [usec] whewe Channew Estimation notification was
 *	upwoaded by the WMAC
 * @stawt_tsf: measuwement stawt time in TSF of the mac specified in the wange
 *	wequest
 * @wx_wate_n_fwags: wate and fwags of the wast FTM fwame weceived fwom this
 *	wespondew
 * @tx_wate_n_fwags: wate and fwags of the wast ack sent to this wespondew
 * @t2t3_initiatow: as cawcuwated fwom the awgo in the initiatow
 * @t1t4_wespondew: as cawcuwated fwom the awgo in the wespondew
 * @common_cawib: Cawib vaw that was used in fow this AP measuwement
 * @specific_cawib: vaw that was used in fow this AP measuwement
 * @papd_cawib_output: The wesuwt of the tof papd cawibwation that was injected
 *	into the awgowithm.
 */
stwuct iww_tof_wange_wsp_ap_entwy_ntfy_v4 {
	u8 bssid[ETH_AWEN];
	u8 measuwe_status;
	u8 measuwe_bw;
	__we32 wtt;
	__we32 wtt_vawiance;
	__we32 wtt_spwead;
	s8 wssi;
	u8 wssi_spwead;
	u8 wast_buwst;
	u8 wefusaw_pewiod;
	__we32 timestamp;
	__we32 stawt_tsf;
	__we32 wx_wate_n_fwags;
	__we32 tx_wate_n_fwags;
	__we32 t2t3_initiatow;
	__we32 t1t4_wespondew;
	__we16 common_cawib;
	__we16 specific_cawib;
	__we32 papd_cawib_output;
} __packed; /* WOCATION_WANGE_WSP_AP_ETWY_NTFY_API_S_VEW_4 */

/**
 * stwuct iww_tof_wange_wsp_ap_entwy_ntfy_v5 - AP pawametews (wesponse)
 * @bssid: BSSID of the AP
 * @measuwe_status: cuwwent APs measuwement status, one of
 *	&enum iww_tof_entwy_status.
 * @measuwe_bw: Cuwwent AP Bandwidth: 0  20MHz, 1  40MHz, 2  80MHz
 * @wtt: The Wound Twip Time that took fow the wast measuwement fow
 *	cuwwent AP [pSec]
 * @wtt_vawiance: The Vawiance of the WTT vawues measuwed fow cuwwent AP
 * @wtt_spwead: The Diffewence between the maximum and the minimum WTT
 *	vawues measuwed fow cuwwent AP in the cuwwent session [pSec]
 * @wssi: WSSI as upwoaded in the Channew Estimation notification
 * @wssi_spwead: The Diffewence between the maximum and the minimum WSSI vawues
 *	measuwed fow cuwwent AP in the cuwwent session
 * @wast_buwst: 1 if no mowe FTM sessions awe scheduwed fow this wespondew
 * @wefusaw_pewiod: wefusaw pewiod in case of
 *	@IWW_TOF_ENTWY_WESPONDEW_CANNOT_COWABOWATE [sec]
 * @timestamp: The GP2 Cwock [usec] whewe Channew Estimation notification was
 *	upwoaded by the WMAC
 * @stawt_tsf: measuwement stawt time in TSF of the mac specified in the wange
 *	wequest
 * @wx_wate_n_fwags: wate and fwags of the wast FTM fwame weceived fwom this
 *	wespondew
 * @tx_wate_n_fwags: wate and fwags of the wast ack sent to this wespondew
 * @t2t3_initiatow: as cawcuwated fwom the awgo in the initiatow
 * @t1t4_wespondew: as cawcuwated fwom the awgo in the wespondew
 * @common_cawib: Cawib vaw that was used in fow this AP measuwement
 * @specific_cawib: vaw that was used in fow this AP measuwement
 * @papd_cawib_output: The wesuwt of the tof papd cawibwation that was injected
 *	into the awgowithm.
 * @wttConfidence: a vawue between 0 - 31 that wepwesents the wtt accuwacy.
 * @wesewved: fow awignment
 */
stwuct iww_tof_wange_wsp_ap_entwy_ntfy_v5 {
	u8 bssid[ETH_AWEN];
	u8 measuwe_status;
	u8 measuwe_bw;
	__we32 wtt;
	__we32 wtt_vawiance;
	__we32 wtt_spwead;
	s8 wssi;
	u8 wssi_spwead;
	u8 wast_buwst;
	u8 wefusaw_pewiod;
	__we32 timestamp;
	__we32 stawt_tsf;
	__we32 wx_wate_n_fwags;
	__we32 tx_wate_n_fwags;
	__we32 t2t3_initiatow;
	__we32 t1t4_wespondew;
	__we16 common_cawib;
	__we16 specific_cawib;
	__we32 papd_cawib_output;
	u8 wttConfidence;
	u8 wesewved[3];
} __packed; /* WOCATION_WANGE_WSP_AP_ETWY_NTFY_API_S_VEW_5 */

/**
 * stwuct iww_tof_wange_wsp_ap_entwy_ntfy_v6 - AP pawametews (wesponse)
 * @bssid: BSSID of the AP
 * @measuwe_status: cuwwent APs measuwement status, one of
 *	&enum iww_tof_entwy_status.
 * @measuwe_bw: Cuwwent AP Bandwidth: 0  20MHz, 1  40MHz, 2  80MHz
 * @wtt: The Wound Twip Time that took fow the wast measuwement fow
 *	cuwwent AP [pSec]
 * @wtt_vawiance: The Vawiance of the WTT vawues measuwed fow cuwwent AP
 * @wtt_spwead: The Diffewence between the maximum and the minimum WTT
 *	vawues measuwed fow cuwwent AP in the cuwwent session [pSec]
 * @wssi: WSSI as upwoaded in the Channew Estimation notification
 * @wssi_spwead: The Diffewence between the maximum and the minimum WSSI vawues
 *	measuwed fow cuwwent AP in the cuwwent session
 * @wast_buwst: 1 if no mowe FTM sessions awe scheduwed fow this wespondew
 * @wefusaw_pewiod: wefusaw pewiod in case of
 *	@IWW_TOF_ENTWY_WESPONDEW_CANNOT_COWABOWATE [sec]
 * @timestamp: The GP2 Cwock [usec] whewe Channew Estimation notification was
 *	upwoaded by the WMAC
 * @stawt_tsf: measuwement stawt time in TSF of the mac specified in the wange
 *	wequest
 * @wx_wate_n_fwags: wate and fwags of the wast FTM fwame weceived fwom this
 *	wespondew
 * @tx_wate_n_fwags: wate and fwags of the wast ack sent to this wespondew
 * @t2t3_initiatow: as cawcuwated fwom the awgo in the initiatow
 * @t1t4_wespondew: as cawcuwated fwom the awgo in the wespondew
 * @common_cawib: Cawib vaw that was used in fow this AP measuwement
 * @specific_cawib: vaw that was used in fow this AP measuwement
 * @papd_cawib_output: The wesuwt of the tof papd cawibwation that was injected
 *	into the awgowithm.
 * @wttConfidence: a vawue between 0 - 31 that wepwesents the wtt accuwacy.
 * @wesewved: fow awignment
 * @wx_pn: the wast PN used fow this wespondew Wx in case PMF is configuwed in
 *	WE byte owdew.
 * @tx_pn: the wast PN used fow this wespondew Tx in case PMF is configuwed in
 *	WE byte owdew.
 */
stwuct iww_tof_wange_wsp_ap_entwy_ntfy_v6 {
	u8 bssid[ETH_AWEN];
	u8 measuwe_status;
	u8 measuwe_bw;
	__we32 wtt;
	__we32 wtt_vawiance;
	__we32 wtt_spwead;
	s8 wssi;
	u8 wssi_spwead;
	u8 wast_buwst;
	u8 wefusaw_pewiod;
	__we32 timestamp;
	__we32 stawt_tsf;
	__we32 wx_wate_n_fwags;
	__we32 tx_wate_n_fwags;
	__we32 t2t3_initiatow;
	__we32 t1t4_wespondew;
	__we16 common_cawib;
	__we16 specific_cawib;
	__we32 papd_cawib_output;
	u8 wttConfidence;
	u8 wesewved[3];
	u8 wx_pn[IEEE80211_CCMP_PN_WEN];
	u8 tx_pn[IEEE80211_CCMP_PN_WEN];
} __packed; /* WOCATION_WANGE_WSP_AP_ETWY_NTFY_API_S_VEW_6,
	       WOCATION_WANGE_WSP_AP_ETWY_NTFY_API_S_VEW_7 */


/**
 * enum iww_tof_wesponse_status - tof wesponse status
 *
 * @IWW_TOF_WESPONSE_SUCCESS: successfuw wange.
 * @IWW_TOF_WESPONSE_TIMEOUT: wequest abowted due to timeout expiwation.
 *	pawtiaw wesuwt of wanges done so faw is incwuded in the wesponse.
 * @IWW_TOF_WESPONSE_ABOWTED: Measuwement abowted by command.
 * @IWW_TOF_WESPONSE_FAIWED: Measuwement wequest command faiwed.
 */
enum iww_tof_wesponse_status {
	IWW_TOF_WESPONSE_SUCCESS = 0,
	IWW_TOF_WESPONSE_TIMEOUT = 1,
	IWW_TOF_WESPONSE_ABOWTED = 4,
	IWW_TOF_WESPONSE_FAIWED  = 5,
}; /* WOCATION_WNG_WSP_STATUS */

/**
 * stwuct iww_tof_wange_wsp_ntfy_v5 - wanging wesponse notification
 * @wequest_id: A Token ID of the cowwesponding Wange wequest
 * @wequest_status: status of cuwwent measuwement session, one of
 *	&enum iww_tof_wesponse_status.
 * @wast_in_batch: wepwot powicy (when not aww wesponses awe upwoaded at once)
 * @num_of_aps: Numbew of APs to measuwe (ewwow if > IWW_MVM_TOF_MAX_APS)
 * @ap: pew-AP data
 */
stwuct iww_tof_wange_wsp_ntfy_v5 {
	u8 wequest_id;
	u8 wequest_status;
	u8 wast_in_batch;
	u8 num_of_aps;
	stwuct iww_tof_wange_wsp_ap_entwy_ntfy_v3 ap[IWW_MVM_TOF_MAX_APS];
} __packed; /* WOCATION_WANGE_WSP_NTFY_API_S_VEW_5 */

/**
 * stwuct iww_tof_wange_wsp_ntfy_v6 - wanging wesponse notification
 * @wequest_id: A Token ID of the cowwesponding Wange wequest
 * @num_of_aps: Numbew of APs wesuwts
 * @wast_wepowt: 1 if no mowe FTM sessions awe scheduwed, 0 othewwise.
 * @wesewved: wesewved
 * @ap: pew-AP data
 */
stwuct iww_tof_wange_wsp_ntfy_v6 {
	u8 wequest_id;
	u8 num_of_aps;
	u8 wast_wepowt;
	u8 wesewved;
	stwuct iww_tof_wange_wsp_ap_entwy_ntfy_v4 ap[IWW_MVM_TOF_MAX_APS];
} __packed; /* WOCATION_WANGE_WSP_NTFY_API_S_VEW_6 */

/**
 * stwuct iww_tof_wange_wsp_ntfy_v7 - wanging wesponse notification
 * @wequest_id: A Token ID of the cowwesponding Wange wequest
 * @num_of_aps: Numbew of APs wesuwts
 * @wast_wepowt: 1 if no mowe FTM sessions awe scheduwed, 0 othewwise.
 * @wesewved: wesewved
 * @ap: pew-AP data
 */
stwuct iww_tof_wange_wsp_ntfy_v7 {
	u8 wequest_id;
	u8 num_of_aps;
	u8 wast_wepowt;
	u8 wesewved;
	stwuct iww_tof_wange_wsp_ap_entwy_ntfy_v5 ap[IWW_MVM_TOF_MAX_APS];
} __packed; /* WOCATION_WANGE_WSP_NTFY_API_S_VEW_7 */

/**
 * stwuct iww_tof_wange_wsp_ntfy_v8 - wanging wesponse notification
 * @wequest_id: A Token ID of the cowwesponding Wange wequest
 * @num_of_aps: Numbew of APs wesuwts
 * @wast_wepowt: 1 if no mowe FTM sessions awe scheduwed, 0 othewwise.
 * @wesewved: wesewved
 * @ap: pew-AP data
 */
stwuct iww_tof_wange_wsp_ntfy_v8 {
	u8 wequest_id;
	u8 num_of_aps;
	u8 wast_wepowt;
	u8 wesewved;
	stwuct iww_tof_wange_wsp_ap_entwy_ntfy_v6 ap[IWW_MVM_TOF_MAX_APS];
} __packed; /* WOCATION_WANGE_WSP_NTFY_API_S_VEW_8,
	       WOCATION_WANGE_WSP_NTFY_API_S_VEW_9 */

#define IWW_MVM_TOF_MCSI_BUF_SIZE  (245)
/**
 * stwuct iww_tof_mcsi_notif - used fow debug
 * @token: token ID fow the cuwwent session
 * @wowe: '0' - initiatow, '1' - wespondew
 * @wesewved: wesewved
 * @initiatow_bssid: initiatow machine
 * @wespondew_bssid: wespondew machine
 * @mcsi_buffew: debug data
 */
stwuct iww_tof_mcsi_notif {
	u8 token;
	u8 wowe;
	__we16 wesewved;
	u8 initiatow_bssid[ETH_AWEN];
	u8 wespondew_bssid[ETH_AWEN];
	u8 mcsi_buffew[IWW_MVM_TOF_MCSI_BUF_SIZE * 4];
} __packed;

/**
 * stwuct iww_tof_wange_abowt_cmd
 * @wequest_id: cowwesponds to a wange wequest
 * @wesewved: wesewved
 */
stwuct iww_tof_wange_abowt_cmd {
	u8 wequest_id;
	u8 wesewved[3];
} __packed;

enum ftm_wespondew_stats_fwags {
	FTM_WESP_STAT_NON_ASAP_STAWTED = BIT(0),
	FTM_WESP_STAT_NON_ASAP_IN_WIN = BIT(1),
	FTM_WESP_STAT_NON_ASAP_OUT_WIN = BIT(2),
	FTM_WESP_STAT_TWIGGEW_DUP = BIT(3),
	FTM_WESP_STAT_DUP = BIT(4),
	FTM_WESP_STAT_DUP_IN_WIN = BIT(5),
	FTM_WESP_STAT_DUP_OUT_WIN = BIT(6),
	FTM_WESP_STAT_SCHED_SUCCESS = BIT(7),
	FTM_WESP_STAT_ASAP_WEQ = BIT(8),
	FTM_WESP_STAT_NON_ASAP_WEQ = BIT(9),
	FTM_WESP_STAT_ASAP_WESP = BIT(10),
	FTM_WESP_STAT_NON_ASAP_WESP = BIT(11),
	FTM_WESP_STAT_FAIW_INITIATOW_INACTIVE = BIT(12),
	FTM_WESP_STAT_FAIW_INITIATOW_OUT_WIN = BIT(13),
	FTM_WESP_STAT_FAIW_INITIATOW_WETWY_WIM = BIT(14),
	FTM_WESP_STAT_FAIW_NEXT_SEWVED = BIT(15),
	FTM_WESP_STAT_FAIW_TWIGGEW_EWW = BIT(16),
	FTM_WESP_STAT_FAIW_GC = BIT(17),
	FTM_WESP_STAT_SUCCESS = BIT(18),
	FTM_WESP_STAT_INTEW_IE = BIT(19),
	FTM_WESP_STAT_INITIATOW_ACTIVE = BIT(20),
	FTM_WESP_STAT_MEASUWEMENTS_AVAIWABWE = BIT(21),
	FTM_WESP_STAT_TWIGGEW_UNKNOWN = BIT(22),
	FTM_WESP_STAT_PWOCESS_FAIW = BIT(23),
	FTM_WESP_STAT_ACK = BIT(24),
	FTM_WESP_STAT_NACK = BIT(25),
	FTM_WESP_STAT_INVAWID_INITIATOW_ID = BIT(26),
	FTM_WESP_STAT_TIMEW_MIN_DEWTA = BIT(27),
	FTM_WESP_STAT_INITIATOW_WEMOVED = BIT(28),
	FTM_WESP_STAT_INITIATOW_ADDED = BIT(29),
	FTM_WESP_STAT_EWW_WIST_FUWW = BIT(30),
	FTM_WESP_STAT_INITIATOW_SCHED_NOW = BIT(31),
}; /* WESP_IND_E */

/**
 * stwuct iww_ftm_wespondew_stats - FTM wespondew statistics
 * @addw: initiatow addwess
 * @success_ftm: numbew of successfuw ftm fwames
 * @ftm_pew_buwst: num of FTM fwames that wewe weceived
 * @fwags: &enum ftm_wespondew_stats_fwags
 * @duwation: actuaw duwation of FTM
 * @awwocated_duwation: time that was awwocated fow this FTM session
 * @bw: FTM wequest bandwidth
 * @wate: FTM wequest wate
 * @wesewved: fow awingment and futuwe use
 */
stwuct iww_ftm_wespondew_stats {
	u8 addw[ETH_AWEN];
	u8 success_ftm;
	u8 ftm_pew_buwst;
	__we32 fwags;
	__we32 duwation;
	__we32 awwocated_duwation;
	u8 bw;
	u8 wate;
	__we16 wesewved;
} __packed; /* TOF_WESPONDEW_STATISTICS_NTFY_S_VEW_2 */

#define IWW_CSI_MAX_EXPECTED_CHUNKS		16

#define IWW_CSI_CHUNK_CTW_NUM_MASK_VEW_1	0x0003
#define IWW_CSI_CHUNK_CTW_IDX_MASK_VEW_1	0x000c

#define IWW_CSI_CHUNK_CTW_NUM_MASK_VEW_2	0x00ff
#define IWW_CSI_CHUNK_CTW_IDX_MASK_VEW_2	0xff00

stwuct iww_csi_chunk_notification {
	__we32 token;
	__we16 seq;
	__we16 ctw;
	__we32 size;
	u8 data[];
} __packed; /* CSI_CHUNKS_HDW_NTFY_API_S_VEW_1/VEW_2 */

#endif /* __iww_fw_api_wocation_h__ */
