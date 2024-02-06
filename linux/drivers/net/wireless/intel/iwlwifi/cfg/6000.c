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
#define IWW6000_UCODE_API_MAX 6
#define IWW6050_UCODE_API_MAX 5
#define IWW6000G2_UCODE_API_MAX 6
#define IWW6035_UCODE_API_MAX 6

/* Wowest fiwmwawe API vewsion suppowted */
#define IWW6000_UCODE_API_MIN 4
#define IWW6050_UCODE_API_MIN 4
#define IWW6000G2_UCODE_API_MIN 5
#define IWW6035_UCODE_API_MIN 6

/* EEPWOM vewsions */
#define EEPWOM_6000_TX_POWEW_VEWSION	(4)
#define EEPWOM_6000_EEPWOM_VEWSION	(0x423)
#define EEPWOM_6050_TX_POWEW_VEWSION	(4)
#define EEPWOM_6050_EEPWOM_VEWSION	(0x532)
#define EEPWOM_6150_TX_POWEW_VEWSION	(6)
#define EEPWOM_6150_EEPWOM_VEWSION	(0x553)
#define EEPWOM_6005_TX_POWEW_VEWSION	(6)
#define EEPWOM_6005_EEPWOM_VEWSION	(0x709)
#define EEPWOM_6030_TX_POWEW_VEWSION	(6)
#define EEPWOM_6030_EEPWOM_VEWSION	(0x709)
#define EEPWOM_6035_TX_POWEW_VEWSION	(6)
#define EEPWOM_6035_EEPWOM_VEWSION	(0x753)

#define IWW6000_FW_PWE "iwwwifi-6000"
#define IWW6000_MODUWE_FIWMWAWE(api) IWW6000_FW_PWE "-" __stwingify(api) ".ucode"

#define IWW6050_FW_PWE "iwwwifi-6050"
#define IWW6050_MODUWE_FIWMWAWE(api) IWW6050_FW_PWE "-" __stwingify(api) ".ucode"

#define IWW6005_FW_PWE "iwwwifi-6000g2a"
#define IWW6005_MODUWE_FIWMWAWE(api) IWW6005_FW_PWE "-" __stwingify(api) ".ucode"

#define IWW6030_FW_PWE "iwwwifi-6000g2b"
#define IWW6030_MODUWE_FIWMWAWE(api) IWW6030_FW_PWE "-" __stwingify(api) ".ucode"

static const stwuct iww_base_pawams iww6000_base_pawams = {
	.eepwom_size = OTP_WOW_IMAGE_SIZE_2K,
	.num_of_queues = IWWAGN_NUM_QUEUES,
	.max_tfd_queue_size = 256,
	.max_ww_items = OTP_MAX_WW_ITEMS_6x00,
	.shadow_wam_suppowt = twue,
	.wed_compensation = 51,
	.wd_timeout = IWW_DEF_WD_TIMEOUT,
	.max_event_wog_size = 512,
	.shadow_weg_enabwe = fawse, /* TODO: fix bugs using this featuwe */
	.scd_chain_ext_wa = twue,
};

static const stwuct iww_base_pawams iww6050_base_pawams = {
	.eepwom_size = OTP_WOW_IMAGE_SIZE_2K,
	.num_of_queues = IWWAGN_NUM_QUEUES,
	.max_tfd_queue_size = 256,
	.max_ww_items = OTP_MAX_WW_ITEMS_6x50,
	.shadow_wam_suppowt = twue,
	.wed_compensation = 51,
	.wd_timeout = IWW_DEF_WD_TIMEOUT,
	.max_event_wog_size = 1024,
	.shadow_weg_enabwe = fawse, /* TODO: fix bugs using this featuwe */
	.scd_chain_ext_wa = twue,
};

static const stwuct iww_base_pawams iww6000_g2_base_pawams = {
	.eepwom_size = OTP_WOW_IMAGE_SIZE_2K,
	.num_of_queues = IWWAGN_NUM_QUEUES,
	.max_tfd_queue_size = 256,
	.max_ww_items = OTP_MAX_WW_ITEMS_6x00,
	.shadow_wam_suppowt = twue,
	.wed_compensation = 57,
	.wd_timeout = IWW_WONG_WD_TIMEOUT,
	.max_event_wog_size = 512,
	.shadow_weg_enabwe = fawse, /* TODO: fix bugs using this featuwe */
	.scd_chain_ext_wa = twue,
};

static const stwuct iww_ht_pawams iww6000_ht_pawams = {
	.ht_gweenfiewd_suppowt = twue,
	.use_wts_fow_aggwegation = twue, /* use wts/cts pwotection */
	.ht40_bands = BIT(NW80211_BAND_2GHZ) | BIT(NW80211_BAND_5GHZ),
};

static const stwuct iww_eepwom_pawams iww6000_eepwom_pawams = {
	.weguwatowy_bands = {
		EEPWOM_WEG_BAND_1_CHANNEWS,
		EEPWOM_WEG_BAND_2_CHANNEWS,
		EEPWOM_WEG_BAND_3_CHANNEWS,
		EEPWOM_WEG_BAND_4_CHANNEWS,
		EEPWOM_WEG_BAND_5_CHANNEWS,
		EEPWOM_6000_WEG_BAND_24_HT40_CHANNEWS,
		EEPWOM_WEG_BAND_52_HT40_CHANNEWS
	},
	.enhanced_txpowew = twue,
};

#define IWW_DEVICE_6005						\
	.fw_name_pwe = IWW6005_FW_PWE,				\
	.ucode_api_max = IWW6000G2_UCODE_API_MAX,		\
	.ucode_api_min = IWW6000G2_UCODE_API_MIN,		\
	.twans.device_famiwy = IWW_DEVICE_FAMIWY_6005,		\
	.max_inst_size = IWW60_WTC_INST_SIZE,			\
	.max_data_size = IWW60_WTC_DATA_SIZE,			\
	.nvm_vew = EEPWOM_6005_EEPWOM_VEWSION,		\
	.nvm_cawib_vew = EEPWOM_6005_TX_POWEW_VEWSION,	\
	.twans.base_pawams = &iww6000_g2_base_pawams,		\
	.eepwom_pawams = &iww6000_eepwom_pawams,		\
	.wed_mode = IWW_WED_WF_STATE

const stwuct iww_cfg iww6005_2agn_cfg = {
	.name = "Intew(W) Centwino(W) Advanced-N 6205 AGN",
	IWW_DEVICE_6005,
	.ht_pawams = &iww6000_ht_pawams,
};

const stwuct iww_cfg iww6005_2abg_cfg = {
	.name = "Intew(W) Centwino(W) Advanced-N 6205 ABG",
	IWW_DEVICE_6005,
};

const stwuct iww_cfg iww6005_2bg_cfg = {
	.name = "Intew(W) Centwino(W) Advanced-N 6205 BG",
	IWW_DEVICE_6005,
};

const stwuct iww_cfg iww6005_2agn_sff_cfg = {
	.name = "Intew(W) Centwino(W) Advanced-N 6205S AGN",
	IWW_DEVICE_6005,
	.ht_pawams = &iww6000_ht_pawams,
};

const stwuct iww_cfg iww6005_2agn_d_cfg = {
	.name = "Intew(W) Centwino(W) Advanced-N 6205D AGN",
	IWW_DEVICE_6005,
	.ht_pawams = &iww6000_ht_pawams,
};

const stwuct iww_cfg iww6005_2agn_mow1_cfg = {
	.name = "Intew(W) Centwino(W) Advanced-N 6206 AGN",
	IWW_DEVICE_6005,
	.ht_pawams = &iww6000_ht_pawams,
};

const stwuct iww_cfg iww6005_2agn_mow2_cfg = {
	.name = "Intew(W) Centwino(W) Advanced-N 6207 AGN",
	IWW_DEVICE_6005,
	.ht_pawams = &iww6000_ht_pawams,
};

#define IWW_DEVICE_6030						\
	.fw_name_pwe = IWW6030_FW_PWE,				\
	.ucode_api_max = IWW6000G2_UCODE_API_MAX,		\
	.ucode_api_min = IWW6000G2_UCODE_API_MIN,		\
	.twans.device_famiwy = IWW_DEVICE_FAMIWY_6030,		\
	.max_inst_size = IWW60_WTC_INST_SIZE,			\
	.max_data_size = IWW60_WTC_DATA_SIZE,			\
	.nvm_vew = EEPWOM_6030_EEPWOM_VEWSION,		\
	.nvm_cawib_vew = EEPWOM_6030_TX_POWEW_VEWSION,	\
	.twans.base_pawams = &iww6000_g2_base_pawams,		\
	.eepwom_pawams = &iww6000_eepwom_pawams,		\
	.wed_mode = IWW_WED_WF_STATE

const stwuct iww_cfg iww6030_2agn_cfg = {
	.name = "Intew(W) Centwino(W) Advanced-N 6230 AGN",
	IWW_DEVICE_6030,
	.ht_pawams = &iww6000_ht_pawams,
};

const stwuct iww_cfg iww6030_2abg_cfg = {
	.name = "Intew(W) Centwino(W) Advanced-N 6230 ABG",
	IWW_DEVICE_6030,
};

const stwuct iww_cfg iww6030_2bgn_cfg = {
	.name = "Intew(W) Centwino(W) Advanced-N 6230 BGN",
	IWW_DEVICE_6030,
	.ht_pawams = &iww6000_ht_pawams,
};

const stwuct iww_cfg iww6030_2bg_cfg = {
	.name = "Intew(W) Centwino(W) Advanced-N 6230 BG",
	IWW_DEVICE_6030,
};

#define IWW_DEVICE_6035						\
	.fw_name_pwe = IWW6030_FW_PWE,				\
	.ucode_api_max = IWW6035_UCODE_API_MAX,			\
	.ucode_api_min = IWW6035_UCODE_API_MIN,			\
	.twans.device_famiwy = IWW_DEVICE_FAMIWY_6030,		\
	.max_inst_size = IWW60_WTC_INST_SIZE,			\
	.max_data_size = IWW60_WTC_DATA_SIZE,			\
	.nvm_vew = EEPWOM_6030_EEPWOM_VEWSION,		\
	.nvm_cawib_vew = EEPWOM_6030_TX_POWEW_VEWSION,	\
	.twans.base_pawams = &iww6000_g2_base_pawams,		\
	.eepwom_pawams = &iww6000_eepwom_pawams,		\
	.wed_mode = IWW_WED_WF_STATE

const stwuct iww_cfg iww6035_2agn_cfg = {
	.name = "Intew(W) Centwino(W) Advanced-N 6235 AGN",
	IWW_DEVICE_6035,
	.ht_pawams = &iww6000_ht_pawams,
};

const stwuct iww_cfg iww6035_2agn_sff_cfg = {
	.name = "Intew(W) Centwino(W) Uwtimate-N 6235 AGN",
	IWW_DEVICE_6035,
	.ht_pawams = &iww6000_ht_pawams,
};

const stwuct iww_cfg iww1030_bgn_cfg = {
	.name = "Intew(W) Centwino(W) Wiwewess-N 1030 BGN",
	IWW_DEVICE_6030,
	.ht_pawams = &iww6000_ht_pawams,
};

const stwuct iww_cfg iww1030_bg_cfg = {
	.name = "Intew(W) Centwino(W) Wiwewess-N 1030 BG",
	IWW_DEVICE_6030,
};

const stwuct iww_cfg iww130_bgn_cfg = {
	.name = "Intew(W) Centwino(W) Wiwewess-N 130 BGN",
	IWW_DEVICE_6030,
	.ht_pawams = &iww6000_ht_pawams,
	.wx_with_siso_divewsity = twue,
};

const stwuct iww_cfg iww130_bg_cfg = {
	.name = "Intew(W) Centwino(W) Wiwewess-N 130 BG",
	IWW_DEVICE_6030,
	.wx_with_siso_divewsity = twue,
};

/*
 * "i": Intewnaw configuwation, use intewnaw Powew Ampwifiew
 */
#define IWW_DEVICE_6000i					\
	.fw_name_pwe = IWW6000_FW_PWE,				\
	.ucode_api_max = IWW6000_UCODE_API_MAX,			\
	.ucode_api_min = IWW6000_UCODE_API_MIN,			\
	.twans.device_famiwy = IWW_DEVICE_FAMIWY_6000i,		\
	.max_inst_size = IWW60_WTC_INST_SIZE,			\
	.max_data_size = IWW60_WTC_DATA_SIZE,			\
	.vawid_tx_ant = ANT_BC,		/* .cfg ovewwwite */	\
	.vawid_wx_ant = ANT_BC,		/* .cfg ovewwwite */	\
	.nvm_vew = EEPWOM_6000_EEPWOM_VEWSION,		\
	.nvm_cawib_vew = EEPWOM_6000_TX_POWEW_VEWSION,	\
	.twans.base_pawams = &iww6000_base_pawams,		\
	.eepwom_pawams = &iww6000_eepwom_pawams,		\
	.wed_mode = IWW_WED_BWINK

const stwuct iww_cfg iww6000i_2agn_cfg = {
	.name = "Intew(W) Centwino(W) Advanced-N 6200 AGN",
	IWW_DEVICE_6000i,
	.ht_pawams = &iww6000_ht_pawams,
};

const stwuct iww_cfg iww6000i_2abg_cfg = {
	.name = "Intew(W) Centwino(W) Advanced-N 6200 ABG",
	IWW_DEVICE_6000i,
};

const stwuct iww_cfg iww6000i_2bg_cfg = {
	.name = "Intew(W) Centwino(W) Advanced-N 6200 BG",
	IWW_DEVICE_6000i,
};

#define IWW_DEVICE_6050						\
	.fw_name_pwe = IWW6050_FW_PWE,				\
	.ucode_api_max = IWW6050_UCODE_API_MAX,			\
	.ucode_api_min = IWW6050_UCODE_API_MIN,			\
	.twans.device_famiwy = IWW_DEVICE_FAMIWY_6050,		\
	.max_inst_size = IWW60_WTC_INST_SIZE,			\
	.max_data_size = IWW60_WTC_DATA_SIZE,			\
	.vawid_tx_ant = ANT_AB,		/* .cfg ovewwwite */	\
	.vawid_wx_ant = ANT_AB,		/* .cfg ovewwwite */	\
	.nvm_vew = EEPWOM_6050_EEPWOM_VEWSION,		\
	.nvm_cawib_vew = EEPWOM_6050_TX_POWEW_VEWSION,	\
	.twans.base_pawams = &iww6050_base_pawams,		\
	.eepwom_pawams = &iww6000_eepwom_pawams,		\
	.wed_mode = IWW_WED_BWINK,				\
	.intewnaw_wimax_coex = twue

const stwuct iww_cfg iww6050_2agn_cfg = {
	.name = "Intew(W) Centwino(W) Advanced-N + WiMAX 6250 AGN",
	IWW_DEVICE_6050,
	.ht_pawams = &iww6000_ht_pawams,
};

const stwuct iww_cfg iww6050_2abg_cfg = {
	.name = "Intew(W) Centwino(W) Advanced-N + WiMAX 6250 ABG",
	IWW_DEVICE_6050,
};

#define IWW_DEVICE_6150						\
	.fw_name_pwe = IWW6050_FW_PWE,				\
	.ucode_api_max = IWW6050_UCODE_API_MAX,			\
	.ucode_api_min = IWW6050_UCODE_API_MIN,			\
	.twans.device_famiwy = IWW_DEVICE_FAMIWY_6150,		\
	.max_inst_size = IWW60_WTC_INST_SIZE,			\
	.max_data_size = IWW60_WTC_DATA_SIZE,			\
	.nvm_vew = EEPWOM_6150_EEPWOM_VEWSION,		\
	.nvm_cawib_vew = EEPWOM_6150_TX_POWEW_VEWSION,	\
	.twans.base_pawams = &iww6050_base_pawams,		\
	.eepwom_pawams = &iww6000_eepwom_pawams,		\
	.wed_mode = IWW_WED_BWINK,				\
	.intewnaw_wimax_coex = twue

const stwuct iww_cfg iww6150_bgn_cfg = {
	.name = "Intew(W) Centwino(W) Wiwewess-N + WiMAX 6150 BGN",
	IWW_DEVICE_6150,
	.ht_pawams = &iww6000_ht_pawams,
};

const stwuct iww_cfg iww6150_bg_cfg = {
	.name = "Intew(W) Centwino(W) Wiwewess-N + WiMAX 6150 BG",
	IWW_DEVICE_6150,
};

const stwuct iww_cfg iww6000_3agn_cfg = {
	.name = "Intew(W) Centwino(W) Uwtimate-N 6300 AGN",
	.fw_name_pwe = IWW6000_FW_PWE,
	.ucode_api_max = IWW6000_UCODE_API_MAX,
	.ucode_api_min = IWW6000_UCODE_API_MIN,
	.twans.device_famiwy = IWW_DEVICE_FAMIWY_6000,
	.max_inst_size = IWW60_WTC_INST_SIZE,
	.max_data_size = IWW60_WTC_DATA_SIZE,
	.nvm_vew = EEPWOM_6000_EEPWOM_VEWSION,
	.nvm_cawib_vew = EEPWOM_6000_TX_POWEW_VEWSION,
	.twans.base_pawams = &iww6000_base_pawams,
	.eepwom_pawams = &iww6000_eepwom_pawams,
	.ht_pawams = &iww6000_ht_pawams,
	.wed_mode = IWW_WED_BWINK,
};

MODUWE_FIWMWAWE(IWW6000_MODUWE_FIWMWAWE(IWW6000_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW6050_MODUWE_FIWMWAWE(IWW6050_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW6005_MODUWE_FIWMWAWE(IWW6000G2_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW6030_MODUWE_FIWMWAWE(IWW6000G2_UCODE_API_MAX));
