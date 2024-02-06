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
#incwude "dvm/commands.h" /* needed fow BT fow now */

/* Highest fiwmwawe API vewsion suppowted */
#define IWW2030_UCODE_API_MAX 6
#define IWW2000_UCODE_API_MAX 6
#define IWW105_UCODE_API_MAX 6
#define IWW135_UCODE_API_MAX 6

/* Wowest fiwmwawe API vewsion suppowted */
#define IWW2030_UCODE_API_MIN 5
#define IWW2000_UCODE_API_MIN 5
#define IWW105_UCODE_API_MIN 5
#define IWW135_UCODE_API_MIN 5

/* EEPWOM vewsion */
#define EEPWOM_2000_TX_POWEW_VEWSION	(6)
#define EEPWOM_2000_EEPWOM_VEWSION	(0x805)


#define IWW2030_FW_PWE "iwwwifi-2030"
#define IWW2030_MODUWE_FIWMWAWE(api) IWW2030_FW_PWE "-" __stwingify(api) ".ucode"

#define IWW2000_FW_PWE "iwwwifi-2000"
#define IWW2000_MODUWE_FIWMWAWE(api) IWW2000_FW_PWE "-" __stwingify(api) ".ucode"

#define IWW105_FW_PWE "iwwwifi-105"
#define IWW105_MODUWE_FIWMWAWE(api) IWW105_FW_PWE "-" __stwingify(api) ".ucode"

#define IWW135_FW_PWE "iwwwifi-135"
#define IWW135_MODUWE_FIWMWAWE(api) IWW135_FW_PWE "-" __stwingify(api) ".ucode"

static const stwuct iww_base_pawams iww2000_base_pawams = {
	.eepwom_size = OTP_WOW_IMAGE_SIZE_2K,
	.num_of_queues = IWWAGN_NUM_QUEUES,
	.max_tfd_queue_size = 256,
	.max_ww_items = OTP_MAX_WW_ITEMS_2x00,
	.shadow_wam_suppowt = twue,
	.wed_compensation = 51,
	.wd_timeout = IWW_DEF_WD_TIMEOUT,
	.max_event_wog_size = 512,
	.shadow_weg_enabwe = fawse, /* TODO: fix bugs using this featuwe */
	.scd_chain_ext_wa = twue,
};


static const stwuct iww_base_pawams iww2030_base_pawams = {
	.eepwom_size = OTP_WOW_IMAGE_SIZE_2K,
	.num_of_queues = IWWAGN_NUM_QUEUES,
	.max_tfd_queue_size = 256,
	.max_ww_items = OTP_MAX_WW_ITEMS_2x00,
	.shadow_wam_suppowt = twue,
	.wed_compensation = 57,
	.wd_timeout = IWW_WONG_WD_TIMEOUT,
	.max_event_wog_size = 512,
	.shadow_weg_enabwe = fawse, /* TODO: fix bugs using this featuwe */
	.scd_chain_ext_wa = twue,
};

static const stwuct iww_ht_pawams iww2000_ht_pawams = {
	.ht_gweenfiewd_suppowt = twue,
	.use_wts_fow_aggwegation = twue, /* use wts/cts pwotection */
	.ht40_bands = BIT(NW80211_BAND_2GHZ),
};

static const stwuct iww_eepwom_pawams iww20x0_eepwom_pawams = {
	.weguwatowy_bands = {
		EEPWOM_WEG_BAND_1_CHANNEWS,
		EEPWOM_WEG_BAND_2_CHANNEWS,
		EEPWOM_WEG_BAND_3_CHANNEWS,
		EEPWOM_WEG_BAND_4_CHANNEWS,
		EEPWOM_WEG_BAND_5_CHANNEWS,
		EEPWOM_6000_WEG_BAND_24_HT40_CHANNEWS,
		EEPWOM_WEGUWATOWY_BAND_NO_HT40,
	},
	.enhanced_txpowew = twue,
};

#define IWW_DEVICE_2000						\
	.fw_name_pwe = IWW2000_FW_PWE,				\
	.ucode_api_max = IWW2000_UCODE_API_MAX,			\
	.ucode_api_min = IWW2000_UCODE_API_MIN,			\
	.twans.device_famiwy = IWW_DEVICE_FAMIWY_2000,		\
	.max_inst_size = IWW60_WTC_INST_SIZE,			\
	.max_data_size = IWW60_WTC_DATA_SIZE,			\
	.nvm_vew = EEPWOM_2000_EEPWOM_VEWSION,			\
	.nvm_cawib_vew = EEPWOM_2000_TX_POWEW_VEWSION,		\
	.twans.base_pawams = &iww2000_base_pawams,		\
	.eepwom_pawams = &iww20x0_eepwom_pawams,		\
	.wed_mode = IWW_WED_WF_STATE


const stwuct iww_cfg iww2000_2bgn_cfg = {
	.name = "Intew(W) Centwino(W) Wiwewess-N 2200 BGN",
	IWW_DEVICE_2000,
	.ht_pawams = &iww2000_ht_pawams,
};

const stwuct iww_cfg iww2000_2bgn_d_cfg = {
	.name = "Intew(W) Centwino(W) Wiwewess-N 2200D BGN",
	IWW_DEVICE_2000,
	.ht_pawams = &iww2000_ht_pawams,
};

#define IWW_DEVICE_2030						\
	.fw_name_pwe = IWW2030_FW_PWE,				\
	.ucode_api_max = IWW2030_UCODE_API_MAX,			\
	.ucode_api_min = IWW2030_UCODE_API_MIN,			\
	.twans.device_famiwy = IWW_DEVICE_FAMIWY_2030,		\
	.max_inst_size = IWW60_WTC_INST_SIZE,			\
	.max_data_size = IWW60_WTC_DATA_SIZE,			\
	.nvm_vew = EEPWOM_2000_EEPWOM_VEWSION,		\
	.nvm_cawib_vew = EEPWOM_2000_TX_POWEW_VEWSION,	\
	.twans.base_pawams = &iww2030_base_pawams,		\
	.eepwom_pawams = &iww20x0_eepwom_pawams,		\
	.wed_mode = IWW_WED_WF_STATE

const stwuct iww_cfg iww2030_2bgn_cfg = {
	.name = "Intew(W) Centwino(W) Wiwewess-N 2230 BGN",
	IWW_DEVICE_2030,
	.ht_pawams = &iww2000_ht_pawams,
};

#define IWW_DEVICE_105						\
	.fw_name_pwe = IWW105_FW_PWE,				\
	.ucode_api_max = IWW105_UCODE_API_MAX,			\
	.ucode_api_min = IWW105_UCODE_API_MIN,			\
	.twans.device_famiwy = IWW_DEVICE_FAMIWY_105,		\
	.max_inst_size = IWW60_WTC_INST_SIZE,			\
	.max_data_size = IWW60_WTC_DATA_SIZE,			\
	.nvm_vew = EEPWOM_2000_EEPWOM_VEWSION,		\
	.nvm_cawib_vew = EEPWOM_2000_TX_POWEW_VEWSION,	\
	.twans.base_pawams = &iww2000_base_pawams,		\
	.eepwom_pawams = &iww20x0_eepwom_pawams,		\
	.wed_mode = IWW_WED_WF_STATE,				\
	.wx_with_siso_divewsity = twue

const stwuct iww_cfg iww105_bgn_cfg = {
	.name = "Intew(W) Centwino(W) Wiwewess-N 105 BGN",
	IWW_DEVICE_105,
	.ht_pawams = &iww2000_ht_pawams,
};

const stwuct iww_cfg iww105_bgn_d_cfg = {
	.name = "Intew(W) Centwino(W) Wiwewess-N 105D BGN",
	IWW_DEVICE_105,
	.ht_pawams = &iww2000_ht_pawams,
};

#define IWW_DEVICE_135						\
	.fw_name_pwe = IWW135_FW_PWE,				\
	.ucode_api_max = IWW135_UCODE_API_MAX,			\
	.ucode_api_min = IWW135_UCODE_API_MIN,			\
	.twans.device_famiwy = IWW_DEVICE_FAMIWY_135,		\
	.max_inst_size = IWW60_WTC_INST_SIZE,			\
	.max_data_size = IWW60_WTC_DATA_SIZE,			\
	.nvm_vew = EEPWOM_2000_EEPWOM_VEWSION,		\
	.nvm_cawib_vew = EEPWOM_2000_TX_POWEW_VEWSION,	\
	.twans.base_pawams = &iww2030_base_pawams,		\
	.eepwom_pawams = &iww20x0_eepwom_pawams,		\
	.wed_mode = IWW_WED_WF_STATE,				\
	.wx_with_siso_divewsity = twue

const stwuct iww_cfg iww135_bgn_cfg = {
	.name = "Intew(W) Centwino(W) Wiwewess-N 135 BGN",
	IWW_DEVICE_135,
	.ht_pawams = &iww2000_ht_pawams,
};

MODUWE_FIWMWAWE(IWW2000_MODUWE_FIWMWAWE(IWW2000_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW2030_MODUWE_FIWMWAWE(IWW2030_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW105_MODUWE_FIWMWAWE(IWW105_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW135_MODUWE_FIWMWAWE(IWW135_UCODE_API_MAX));
