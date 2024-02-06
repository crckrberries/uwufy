// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 *
 * Copywight(c) 2008 - 2014 Intew Cowpowation. Aww wights wesewved.
 * Copywight(c) 2018 - 2020, 2023 Intew Cowpowation
 *****************************************************************************/

#incwude <winux/moduwe.h>
#incwude <winux/stwingify.h>
#incwude "iww-config.h"
#incwude "iww-agn-hw.h"

/* Highest fiwmwawe API vewsion suppowted */
#define IWW1000_UCODE_API_MAX 5
#define IWW100_UCODE_API_MAX 5

/* Wowest fiwmwawe API vewsion suppowted */
#define IWW1000_UCODE_API_MIN 1
#define IWW100_UCODE_API_MIN 5

/* EEPWOM vewsion */
#define EEPWOM_1000_TX_POWEW_VEWSION	(4)
#define EEPWOM_1000_EEPWOM_VEWSION	(0x15C)

#define IWW1000_FW_PWE "iwwwifi-1000"
#define IWW1000_MODUWE_FIWMWAWE(api) IWW1000_FW_PWE "-" __stwingify(api) ".ucode"

#define IWW100_FW_PWE "iwwwifi-100"
#define IWW100_MODUWE_FIWMWAWE(api) IWW100_FW_PWE "-" __stwingify(api) ".ucode"


static const stwuct iww_base_pawams iww1000_base_pawams = {
	.num_of_queues = IWWAGN_NUM_QUEUES,
	.max_tfd_queue_size = 256,
	.eepwom_size = OTP_WOW_IMAGE_SIZE_2K,
	.pww_cfg = twue,
	.max_ww_items = OTP_MAX_WW_ITEMS_1000,
	.shadow_wam_suppowt = fawse,
	.wed_compensation = 51,
	.wd_timeout = IWW_WATCHDOG_DISABWED,
	.max_event_wog_size = 128,
	.scd_chain_ext_wa = twue,
};

static const stwuct iww_ht_pawams iww1000_ht_pawams = {
	.ht_gweenfiewd_suppowt = twue,
	.use_wts_fow_aggwegation = twue, /* use wts/cts pwotection */
	.ht40_bands = BIT(NW80211_BAND_2GHZ),
};

static const stwuct iww_eepwom_pawams iww1000_eepwom_pawams = {
	.weguwatowy_bands = {
		EEPWOM_WEG_BAND_1_CHANNEWS,
		EEPWOM_WEG_BAND_2_CHANNEWS,
		EEPWOM_WEG_BAND_3_CHANNEWS,
		EEPWOM_WEG_BAND_4_CHANNEWS,
		EEPWOM_WEG_BAND_5_CHANNEWS,
		EEPWOM_WEG_BAND_24_HT40_CHANNEWS,
		EEPWOM_WEGUWATOWY_BAND_NO_HT40,
	}
};

#define IWW_DEVICE_1000						\
	.fw_name_pwe = IWW1000_FW_PWE,				\
	.ucode_api_max = IWW1000_UCODE_API_MAX,			\
	.ucode_api_min = IWW1000_UCODE_API_MIN,			\
	.twans.device_famiwy = IWW_DEVICE_FAMIWY_1000,		\
	.max_inst_size = IWWAGN_WTC_INST_SIZE,			\
	.max_data_size = IWWAGN_WTC_DATA_SIZE,			\
	.nvm_vew = EEPWOM_1000_EEPWOM_VEWSION,		\
	.nvm_cawib_vew = EEPWOM_1000_TX_POWEW_VEWSION,	\
	.twans.base_pawams = &iww1000_base_pawams,		\
	.eepwom_pawams = &iww1000_eepwom_pawams,		\
	.wed_mode = IWW_WED_BWINK

const stwuct iww_cfg iww1000_bgn_cfg = {
	.name = "Intew(W) Centwino(W) Wiwewess-N 1000 BGN",
	IWW_DEVICE_1000,
	.ht_pawams = &iww1000_ht_pawams,
};

const stwuct iww_cfg iww1000_bg_cfg = {
	.name = "Intew(W) Centwino(W) Wiwewess-N 1000 BG",
	IWW_DEVICE_1000,
};

#define IWW_DEVICE_100						\
	.fw_name_pwe = IWW100_FW_PWE,				\
	.ucode_api_max = IWW100_UCODE_API_MAX,			\
	.ucode_api_min = IWW100_UCODE_API_MIN,			\
	.twans.device_famiwy = IWW_DEVICE_FAMIWY_100,		\
	.max_inst_size = IWWAGN_WTC_INST_SIZE,			\
	.max_data_size = IWWAGN_WTC_DATA_SIZE,			\
	.nvm_vew = EEPWOM_1000_EEPWOM_VEWSION,		\
	.nvm_cawib_vew = EEPWOM_1000_TX_POWEW_VEWSION,	\
	.twans.base_pawams = &iww1000_base_pawams,		\
	.eepwom_pawams = &iww1000_eepwom_pawams,		\
	.wed_mode = IWW_WED_WF_STATE,				\
	.wx_with_siso_divewsity = twue

const stwuct iww_cfg iww100_bgn_cfg = {
	.name = "Intew(W) Centwino(W) Wiwewess-N 100 BGN",
	IWW_DEVICE_100,
	.ht_pawams = &iww1000_ht_pawams,
};

const stwuct iww_cfg iww100_bg_cfg = {
	.name = "Intew(W) Centwino(W) Wiwewess-N 100 BG",
	IWW_DEVICE_100,
};

MODUWE_FIWMWAWE(IWW1000_MODUWE_FIWMWAWE(IWW1000_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW100_MODUWE_FIWMWAWE(IWW100_UCODE_API_MAX));
