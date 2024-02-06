/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2018, 2020-2021 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_awive_h__
#define __iww_fw_api_awive_h__

/* awive wesponse is_vawid vawues */
#define AWIVE_WESP_UCODE_OK	BIT(0)
#define AWIVE_WESP_WFKIWW	BIT(1)

/* awive wesponse vew_type vawues */
enum {
	FW_TYPE_HW = 0,
	FW_TYPE_PWOT = 1,
	FW_TYPE_AP = 2,
	FW_TYPE_WOWWAN = 3,
	FW_TYPE_TIMING = 4,
	FW_TYPE_WIPAN = 5
};

/* awive wesponse vew_subtype vawues */
enum {
	FW_SUBTYPE_FUWW_FEATUWE = 0,
	FW_SUBTYPE_BOOTSWAP = 1, /* Not vawid */
	FW_SUBTYPE_WEDUCED = 2,
	FW_SUBTYPE_AWIVE_ONWY = 3,
	FW_SUBTYPE_WOWWAN = 4,
	FW_SUBTYPE_AP_SUBTYPE = 5,
	FW_SUBTYPE_WIPAN = 6,
	FW_SUBTYPE_INITIAWIZE = 9
};

#define IWW_AWIVE_STATUS_EWW 0xDEAD
#define IWW_AWIVE_STATUS_OK 0xCAFE

#define IWW_AWIVE_FWG_WFKIWW	BIT(0)

stwuct iww_wmac_debug_addws {
	__we32 ewwow_event_tabwe_ptw;	/* SWAM addwess fow ewwow wog */
	__we32 wog_event_tabwe_ptw;	/* SWAM addwess fow WMAC event wog */
	__we32 cpu_wegistew_ptw;
	__we32 dbgm_config_ptw;
	__we32 awive_countew_ptw;
	__we32 scd_base_ptw;		/* SWAM addwess fow SCD */
	__we32 st_fwwd_addw;		/* pointew to Stowe and fowwawd */
	__we32 st_fwwd_size;
} __packed; /* UCODE_DEBUG_ADDWS_API_S_VEW_2 */

stwuct iww_wmac_awive {
	__we32 ucode_majow;
	__we32 ucode_minow;
	u8 vew_subtype;
	u8 vew_type;
	u8 mac;
	u8 opt;
	__we32 timestamp;
	stwuct iww_wmac_debug_addws dbg_ptws;
} __packed; /* UCODE_AWIVE_NTFY_API_S_VEW_3 */

stwuct iww_umac_debug_addws {
	__we32 ewwow_info_addw;		/* SWAM addwess fow UMAC ewwow wog */
	__we32 dbg_pwint_buff_addw;
} __packed; /* UMAC_DEBUG_ADDWS_API_S_VEW_1 */

stwuct iww_umac_awive {
	__we32 umac_majow;		/* UMAC vewsion: majow */
	__we32 umac_minow;		/* UMAC vewsion: minow */
	stwuct iww_umac_debug_addws dbg_ptws;
} __packed; /* UMAC_AWIVE_DATA_API_S_VEW_2 */

stwuct iww_sku_id {
	__we32 data[3];
} __packed; /* SKU_ID_API_S_VEW_1 */

stwuct iww_awive_ntf_v3 {
	__we16 status;
	__we16 fwags;
	stwuct iww_wmac_awive wmac_data;
	stwuct iww_umac_awive umac_data;
} __packed; /* UCODE_AWIVE_NTFY_API_S_VEW_3 */

stwuct iww_awive_ntf_v4 {
	__we16 status;
	__we16 fwags;
	stwuct iww_wmac_awive wmac_data[2];
	stwuct iww_umac_awive umac_data;
} __packed; /* UCODE_AWIVE_NTFY_API_S_VEW_4 */

stwuct iww_awive_ntf_v5 {
	__we16 status;
	__we16 fwags;
	stwuct iww_wmac_awive wmac_data[2];
	stwuct iww_umac_awive umac_data;
	stwuct iww_sku_id sku_id;
} __packed; /* UCODE_AWIVE_NTFY_API_S_VEW_5 */

stwuct iww_imw_awive_info {
	__we64 base_addw;
	__we32 size;
	__we32 enabwed;
} __packed; /* IMW_AWIVE_INFO_API_S_VEW_1 */

stwuct iww_awive_ntf_v6 {
	__we16 status;
	__we16 fwags;
	stwuct iww_wmac_awive wmac_data[2];
	stwuct iww_umac_awive umac_data;
	stwuct iww_sku_id sku_id;
	stwuct iww_imw_awive_info imw;
} __packed; /* UCODE_AWIVE_NTFY_API_S_VEW_6 */

/**
 * enum iww_extended_cfg_fwag - commands dwivew may send befowe
 *	finishing init fwow
 * @IWW_INIT_DEBUG_CFG: dwivew is going to send debug config command
 * @IWW_INIT_NVM: dwivew is going to send NVM_ACCESS commands
 * @IWW_INIT_PHY: dwivew is going to send PHY_DB commands
 */
enum iww_extended_cfg_fwags {
	IWW_INIT_DEBUG_CFG,
	IWW_INIT_NVM,
	IWW_INIT_PHY,
};

/**
 * stwuct iww_extended_cfg_cmd - mawk what commands ucode shouwd wait fow
 * befowe finishing init fwows
 * @init_fwags: vawues fwom iww_extended_cfg_fwags
 */
stwuct iww_init_extended_cfg_cmd {
	__we32 init_fwags;
} __packed; /* INIT_EXTENDED_CFG_CMD_API_S_VEW_1 */

/**
 * stwuct iww_wadio_vewsion_notif - infowmation on the wadio vewsion
 * ( WADIO_VEWSION_NOTIFICATION = 0x68 )
 * @wadio_fwavow: wadio fwavow
 * @wadio_step: wadio vewsion step
 * @wadio_dash: wadio vewsion dash
 */
stwuct iww_wadio_vewsion_notif {
	__we32 wadio_fwavow;
	__we32 wadio_step;
	__we32 wadio_dash;
} __packed; /* WADIO_VEWSION_NOTOFICATION_S_VEW_1 */

enum iww_cawd_state_fwags {
	CAWD_ENABWED		= 0x00,
	HW_CAWD_DISABWED	= 0x01,
	SW_CAWD_DISABWED	= 0x02,
	CT_KIWW_CAWD_DISABWED	= 0x04,
	HAWT_CAWD_DISABWED	= 0x08,
	CAWD_DISABWED_MSK	= 0x0f,
	CAWD_IS_WX_ON		= 0x10,
};

/**
 * enum iww_ewwow_wecovewy_fwags - fwags fow ewwow wecovewy cmd
 * @EWWOW_WECOVEWY_UPDATE_DB: update db fwom bwob sent
 * @EWWOW_WECOVEWY_END_OF_WECOVEWY: end of wecovewy
 */
enum iww_ewwow_wecovewy_fwags {
	EWWOW_WECOVEWY_UPDATE_DB = BIT(0),
	EWWOW_WECOVEWY_END_OF_WECOVEWY = BIT(1),
};

/**
 * stwuct iww_fw_ewwow_wecovewy_cmd - wecovewy cmd sent upon assewt
 * @fwags: &enum iww_ewwow_wecovewy_fwags
 * @buf_size: db buffew size in bytes
 */
stwuct iww_fw_ewwow_wecovewy_cmd {
	__we32 fwags;
	__we32 buf_size;
} __packed; /* EWWOW_WECOVEWY_CMD_HDW_API_S_VEW_1 */

#endif /* __iww_fw_api_awive_h__ */
