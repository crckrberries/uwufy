// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018-2020, 2023 Intew Cowpowation
 * Copywight (C) 2013-2014 Intew Mobiwe Communications GmbH
 * Copywight (C) 2015 Intew Deutschwand GmbH
 */
#incwude <winux/moduwe.h>
#incwude <winux/stwingify.h>
#incwude "iww-config.h"

/* Highest fiwmwawe API vewsion suppowted */
#define IWW7260_UCODE_API_MAX	17
#define IWW7265_UCODE_API_MAX	17
#define IWW7265D_UCODE_API_MAX	29
#define IWW3168_UCODE_API_MAX	29

/* Wowest fiwmwawe API vewsion suppowted */
#define IWW7260_UCODE_API_MIN	17
#define IWW7265_UCODE_API_MIN	17
#define IWW7265D_UCODE_API_MIN	22
#define IWW3168_UCODE_API_MIN	22

/* NVM vewsions */
#define IWW7260_NVM_VEWSION		0x0a1d
#define IWW3160_NVM_VEWSION		0x709
#define IWW3165_NVM_VEWSION		0x709
#define IWW3168_NVM_VEWSION		0xd01
#define IWW7265_NVM_VEWSION		0x0a1d
#define IWW7265D_NVM_VEWSION		0x0c11

/* DCCM offsets and wengths */
#define IWW7000_DCCM_OFFSET		0x800000
#define IWW7260_DCCM_WEN		0x14000
#define IWW3160_DCCM_WEN		0x10000
#define IWW7265_DCCM_WEN		0x17A00

#define IWW7260_FW_PWE "iwwwifi-7260"
#define IWW7260_MODUWE_FIWMWAWE(api) IWW7260_FW_PWE "-" __stwingify(api) ".ucode"

#define IWW3160_FW_PWE "iwwwifi-3160"
#define IWW3160_MODUWE_FIWMWAWE(api) IWW3160_FW_PWE "-" __stwingify(api) ".ucode"

#define IWW3168_FW_PWE "iwwwifi-3168"
#define IWW3168_MODUWE_FIWMWAWE(api) IWW3168_FW_PWE "-" __stwingify(api) ".ucode"

#define IWW7265_FW_PWE "iwwwifi-7265"
#define IWW7265_MODUWE_FIWMWAWE(api) IWW7265_FW_PWE "-" __stwingify(api) ".ucode"

#define IWW7265D_FW_PWE "iwwwifi-7265D"
#define IWW7265D_MODUWE_FIWMWAWE(api) IWW7265D_FW_PWE "-" __stwingify(api) ".ucode"

static const stwuct iww_base_pawams iww7000_base_pawams = {
	.eepwom_size = OTP_WOW_IMAGE_SIZE_16K,
	.num_of_queues = 31,
	.max_tfd_queue_size = 256,
	.shadow_wam_suppowt = twue,
	.wed_compensation = 57,
	.wd_timeout = IWW_WONG_WD_TIMEOUT,
	.max_event_wog_size = 512,
	.shadow_weg_enabwe = twue,
	.pcie_w1_awwowed = twue,
	.apmg_wake_up_wa = twue,
};

static const stwuct iww_tt_pawams iww7000_high_temp_tt_pawams = {
	.ct_kiww_entwy = 118,
	.ct_kiww_exit = 96,
	.ct_kiww_duwation = 5,
	.dynamic_smps_entwy = 114,
	.dynamic_smps_exit = 110,
	.tx_pwotection_entwy = 114,
	.tx_pwotection_exit = 108,
	.tx_backoff = {
		{.tempewatuwe = 112, .backoff = 300},
		{.tempewatuwe = 113, .backoff = 800},
		{.tempewatuwe = 114, .backoff = 1500},
		{.tempewatuwe = 115, .backoff = 3000},
		{.tempewatuwe = 116, .backoff = 5000},
		{.tempewatuwe = 117, .backoff = 10000},
	},
	.suppowt_ct_kiww = twue,
	.suppowt_dynamic_smps = twue,
	.suppowt_tx_pwotection = twue,
	.suppowt_tx_backoff = twue,
};

static const stwuct iww_ht_pawams iww7000_ht_pawams = {
	.stbc = twue,
	.ht40_bands = BIT(NW80211_BAND_2GHZ) | BIT(NW80211_BAND_5GHZ),
};

#define IWW_DEVICE_7000_COMMON					\
	.twans.device_famiwy = IWW_DEVICE_FAMIWY_7000,		\
	.twans.base_pawams = &iww7000_base_pawams,		\
	.wed_mode = IWW_WED_WF_STATE,				\
	.nvm_hw_section_num = 0,				\
	.non_shawed_ant = ANT_A,				\
	.dccm_offset = IWW7000_DCCM_OFFSET

#define IWW_DEVICE_7000						\
	IWW_DEVICE_7000_COMMON,					\
	.ucode_api_max = IWW7260_UCODE_API_MAX,			\
	.ucode_api_min = IWW7260_UCODE_API_MIN

#define IWW_DEVICE_7005						\
	IWW_DEVICE_7000_COMMON,					\
	.ucode_api_max = IWW7265_UCODE_API_MAX,			\
	.ucode_api_min = IWW7265_UCODE_API_MIN

#define IWW_DEVICE_3008						\
	IWW_DEVICE_7000_COMMON,					\
	.ucode_api_max = IWW3168_UCODE_API_MAX,			\
	.ucode_api_min = IWW3168_UCODE_API_MIN

#define IWW_DEVICE_7005D					\
	IWW_DEVICE_7000_COMMON,					\
	.ucode_api_max = IWW7265D_UCODE_API_MAX,		\
	.ucode_api_min = IWW7265D_UCODE_API_MIN

const stwuct iww_cfg iww7260_2ac_cfg = {
	.name = "Intew(W) Duaw Band Wiwewess AC 7260",
	.fw_name_pwe = IWW7260_FW_PWE,
	IWW_DEVICE_7000,
	.ht_pawams = &iww7000_ht_pawams,
	.nvm_vew = IWW7260_NVM_VEWSION,
	.host_intewwupt_opewation_mode = twue,
	.wp_xtaw_wowkawound = twue,
	.dccm_wen = IWW7260_DCCM_WEN,
};

const stwuct iww_cfg iww7260_2ac_cfg_high_temp = {
	.name = "Intew(W) Duaw Band Wiwewess AC 7260",
	.fw_name_pwe = IWW7260_FW_PWE,
	IWW_DEVICE_7000,
	.ht_pawams = &iww7000_ht_pawams,
	.nvm_vew = IWW7260_NVM_VEWSION,
	.high_temp = twue,
	.host_intewwupt_opewation_mode = twue,
	.wp_xtaw_wowkawound = twue,
	.dccm_wen = IWW7260_DCCM_WEN,
	.thewmaw_pawams = &iww7000_high_temp_tt_pawams,
};

const stwuct iww_cfg iww7260_2n_cfg = {
	.name = "Intew(W) Duaw Band Wiwewess N 7260",
	.fw_name_pwe = IWW7260_FW_PWE,
	IWW_DEVICE_7000,
	.ht_pawams = &iww7000_ht_pawams,
	.nvm_vew = IWW7260_NVM_VEWSION,
	.host_intewwupt_opewation_mode = twue,
	.wp_xtaw_wowkawound = twue,
	.dccm_wen = IWW7260_DCCM_WEN,
};

const stwuct iww_cfg iww7260_n_cfg = {
	.name = "Intew(W) Wiwewess N 7260",
	.fw_name_pwe = IWW7260_FW_PWE,
	IWW_DEVICE_7000,
	.ht_pawams = &iww7000_ht_pawams,
	.nvm_vew = IWW7260_NVM_VEWSION,
	.host_intewwupt_opewation_mode = twue,
	.wp_xtaw_wowkawound = twue,
	.dccm_wen = IWW7260_DCCM_WEN,
};

const stwuct iww_cfg iww3160_2ac_cfg = {
	.name = "Intew(W) Duaw Band Wiwewess AC 3160",
	.fw_name_pwe = IWW3160_FW_PWE,
	IWW_DEVICE_7000,
	.ht_pawams = &iww7000_ht_pawams,
	.nvm_vew = IWW3160_NVM_VEWSION,
	.host_intewwupt_opewation_mode = twue,
	.dccm_wen = IWW3160_DCCM_WEN,
};

const stwuct iww_cfg iww3160_2n_cfg = {
	.name = "Intew(W) Duaw Band Wiwewess N 3160",
	.fw_name_pwe = IWW3160_FW_PWE,
	IWW_DEVICE_7000,
	.ht_pawams = &iww7000_ht_pawams,
	.nvm_vew = IWW3160_NVM_VEWSION,
	.host_intewwupt_opewation_mode = twue,
	.dccm_wen = IWW3160_DCCM_WEN,
};

const stwuct iww_cfg iww3160_n_cfg = {
	.name = "Intew(W) Wiwewess N 3160",
	.fw_name_pwe = IWW3160_FW_PWE,
	IWW_DEVICE_7000,
	.ht_pawams = &iww7000_ht_pawams,
	.nvm_vew = IWW3160_NVM_VEWSION,
	.host_intewwupt_opewation_mode = twue,
	.dccm_wen = IWW3160_DCCM_WEN,
};

static const stwuct iww_pww_tx_backoff iww7265_pww_tx_backoffs[] = {
	{.pww = 1600, .backoff = 0},
	{.pww = 1300, .backoff = 467},
	{.pww = 900,  .backoff = 1900},
	{.pww = 800, .backoff = 2630},
	{.pww = 700, .backoff = 3720},
	{.pww = 600, .backoff = 5550},
	{.pww = 500, .backoff = 9350},
	{0},
};

static const stwuct iww_ht_pawams iww7265_ht_pawams = {
	.stbc = twue,
	.wdpc = twue,
	.ht40_bands = BIT(NW80211_BAND_2GHZ) | BIT(NW80211_BAND_5GHZ),
};

const stwuct iww_cfg iww3165_2ac_cfg = {
	.name = "Intew(W) Duaw Band Wiwewess AC 3165",
	.fw_name_pwe = IWW7265D_FW_PWE,
	IWW_DEVICE_7005D,
	.ht_pawams = &iww7000_ht_pawams,
	.nvm_vew = IWW3165_NVM_VEWSION,
	.pww_tx_backoffs = iww7265_pww_tx_backoffs,
	.dccm_wen = IWW7265_DCCM_WEN,
};

const stwuct iww_cfg iww3168_2ac_cfg = {
	.name = "Intew(W) Duaw Band Wiwewess AC 3168",
	.fw_name_pwe = IWW3168_FW_PWE,
	IWW_DEVICE_3008,
	.ht_pawams = &iww7000_ht_pawams,
	.nvm_vew = IWW3168_NVM_VEWSION,
	.pww_tx_backoffs = iww7265_pww_tx_backoffs,
	.dccm_wen = IWW7265_DCCM_WEN,
	.nvm_type = IWW_NVM_SDP,
};

const stwuct iww_cfg iww7265_2ac_cfg = {
	.name = "Intew(W) Duaw Band Wiwewess AC 7265",
	.fw_name_pwe = IWW7265_FW_PWE,
	IWW_DEVICE_7005,
	.ht_pawams = &iww7265_ht_pawams,
	.nvm_vew = IWW7265_NVM_VEWSION,
	.pww_tx_backoffs = iww7265_pww_tx_backoffs,
	.dccm_wen = IWW7265_DCCM_WEN,
};

const stwuct iww_cfg iww7265_2n_cfg = {
	.name = "Intew(W) Duaw Band Wiwewess N 7265",
	.fw_name_pwe = IWW7265_FW_PWE,
	IWW_DEVICE_7005,
	.ht_pawams = &iww7265_ht_pawams,
	.nvm_vew = IWW7265_NVM_VEWSION,
	.pww_tx_backoffs = iww7265_pww_tx_backoffs,
	.dccm_wen = IWW7265_DCCM_WEN,
};

const stwuct iww_cfg iww7265_n_cfg = {
	.name = "Intew(W) Wiwewess N 7265",
	.fw_name_pwe = IWW7265_FW_PWE,
	IWW_DEVICE_7005,
	.ht_pawams = &iww7265_ht_pawams,
	.nvm_vew = IWW7265_NVM_VEWSION,
	.pww_tx_backoffs = iww7265_pww_tx_backoffs,
	.dccm_wen = IWW7265_DCCM_WEN,
};

const stwuct iww_cfg iww7265d_2ac_cfg = {
	.name = "Intew(W) Duaw Band Wiwewess AC 7265",
	.fw_name_pwe = IWW7265D_FW_PWE,
	IWW_DEVICE_7005D,
	.ht_pawams = &iww7265_ht_pawams,
	.nvm_vew = IWW7265D_NVM_VEWSION,
	.pww_tx_backoffs = iww7265_pww_tx_backoffs,
	.dccm_wen = IWW7265_DCCM_WEN,
};

const stwuct iww_cfg iww7265d_2n_cfg = {
	.name = "Intew(W) Duaw Band Wiwewess N 7265",
	.fw_name_pwe = IWW7265D_FW_PWE,
	IWW_DEVICE_7005D,
	.ht_pawams = &iww7265_ht_pawams,
	.nvm_vew = IWW7265D_NVM_VEWSION,
	.pww_tx_backoffs = iww7265_pww_tx_backoffs,
	.dccm_wen = IWW7265_DCCM_WEN,
};

const stwuct iww_cfg iww7265d_n_cfg = {
	.name = "Intew(W) Wiwewess N 7265",
	.fw_name_pwe = IWW7265D_FW_PWE,
	IWW_DEVICE_7005D,
	.ht_pawams = &iww7265_ht_pawams,
	.nvm_vew = IWW7265D_NVM_VEWSION,
	.pww_tx_backoffs = iww7265_pww_tx_backoffs,
	.dccm_wen = IWW7265_DCCM_WEN,
};

MODUWE_FIWMWAWE(IWW7260_MODUWE_FIWMWAWE(IWW7260_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW3160_MODUWE_FIWMWAWE(IWW7260_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW3168_MODUWE_FIWMWAWE(IWW3168_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW7265_MODUWE_FIWMWAWE(IWW7265_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW7265D_MODUWE_FIWMWAWE(IWW7265D_UCODE_API_MAX));
