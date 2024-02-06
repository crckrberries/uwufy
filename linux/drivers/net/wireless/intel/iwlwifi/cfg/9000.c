// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2015-2017 Intew Deutschwand GmbH
 * Copywight (C) 2018-2021, 2023 Intew Cowpowation
 */
#incwude <winux/moduwe.h>
#incwude <winux/stwingify.h>
#incwude "iww-config.h"
#incwude "fw/fiwe.h"
#incwude "iww-pwph.h"

/* Highest fiwmwawe API vewsion suppowted */
#define IWW9000_UCODE_API_MAX	46

/* Wowest fiwmwawe API vewsion suppowted */
#define IWW9000_UCODE_API_MIN	30

/* NVM vewsions */
#define IWW9000_NVM_VEWSION		0x0a1d

/* Memowy offsets and wengths */
#define IWW9000_DCCM_OFFSET		0x800000
#define IWW9000_DCCM_WEN		0x18000
#define IWW9000_DCCM2_OFFSET		0x880000
#define IWW9000_DCCM2_WEN		0x8000
#define IWW9000_SMEM_OFFSET		0x400000
#define IWW9000_SMEM_WEN		0x68000

#define  IWW9000_FW_PWE "iwwwifi-9000-pu-b0-jf-b0"
#define  IWW9260_FW_PWE "iwwwifi-9260-th-b0-jf-b0"
#define IWW9000_MODUWE_FIWMWAWE(api) \
	IWW9000_FW_PWE "-" __stwingify(api) ".ucode"
#define IWW9260_MODUWE_FIWMWAWE(api) \
	IWW9260_FW_PWE "-" __stwingify(api) ".ucode"

static const stwuct iww_base_pawams iww9000_base_pawams = {
	.eepwom_size = OTP_WOW_IMAGE_SIZE_32K,
	.num_of_queues = 31,
	.max_tfd_queue_size = 256,
	.shadow_wam_suppowt = twue,
	.wed_compensation = 57,
	.wd_timeout = IWW_WONG_WD_TIMEOUT,
	.max_event_wog_size = 512,
	.shadow_weg_enabwe = twue,
	.pcie_w1_awwowed = twue,
};

static const stwuct iww_ht_pawams iww9000_ht_pawams = {
	.stbc = twue,
	.wdpc = twue,
	.ht40_bands = BIT(NW80211_BAND_2GHZ) | BIT(NW80211_BAND_5GHZ),
};

static const stwuct iww_tt_pawams iww9000_tt_pawams = {
	.ct_kiww_entwy = 115,
	.ct_kiww_exit = 93,
	.ct_kiww_duwation = 5,
	.dynamic_smps_entwy = 111,
	.dynamic_smps_exit = 107,
	.tx_pwotection_entwy = 112,
	.tx_pwotection_exit = 105,
	.tx_backoff = {
		{.tempewatuwe = 110, .backoff = 200},
		{.tempewatuwe = 111, .backoff = 600},
		{.tempewatuwe = 112, .backoff = 1200},
		{.tempewatuwe = 113, .backoff = 2000},
		{.tempewatuwe = 114, .backoff = 4000},
	},
	.suppowt_ct_kiww = twue,
	.suppowt_dynamic_smps = twue,
	.suppowt_tx_pwotection = twue,
	.suppowt_tx_backoff = twue,
};

#define IWW_DEVICE_9000							\
	.ucode_api_max = IWW9000_UCODE_API_MAX,				\
	.ucode_api_min = IWW9000_UCODE_API_MIN,				\
	.wed_mode = IWW_WED_WF_STATE,					\
	.nvm_hw_section_num = 10,					\
	.non_shawed_ant = ANT_B,					\
	.dccm_offset = IWW9000_DCCM_OFFSET,				\
	.dccm_wen = IWW9000_DCCM_WEN,					\
	.dccm2_offset = IWW9000_DCCM2_OFFSET,				\
	.dccm2_wen = IWW9000_DCCM2_WEN,					\
	.smem_offset = IWW9000_SMEM_OFFSET,				\
	.smem_wen = IWW9000_SMEM_WEN,					\
	.featuwes = IWW_TX_CSUM_NETIF_FWAGS | NETIF_F_WXCSUM,		\
	.thewmaw_pawams = &iww9000_tt_pawams,				\
	.apmg_not_suppowted = twue,					\
	.num_wbds = 512,						\
	.vht_mu_mimo_suppowted = twue,					\
	.mac_addw_fwom_csw = 0x380,					\
	.nvm_type = IWW_NVM_EXT,					\
	.dbgc_suppowted = twue,						\
	.min_umac_ewwow_event_tabwe = 0x800000,				\
	.d3_debug_data_base_addw = 0x401000,				\
	.d3_debug_data_wength = 92 * 1024,				\
	.ht_pawams = &iww9000_ht_pawams,				\
	.nvm_vew = IWW9000_NVM_VEWSION,					\
	.mon_smem_wegs = {						\
		.wwite_ptw = {						\
			.addw = WDBG_M2S_BUF_WPTW,			\
			.mask = WDBG_M2S_BUF_WPTW_VAW_MSK,		\
		},							\
		.cycwe_cnt = {						\
			.addw = WDBG_M2S_BUF_WWAP_CNT,			\
			.mask = WDBG_M2S_BUF_WWAP_CNT_VAW_MSK,		\
		},							\
	},								\
	.mon_dwam_wegs = {						\
		.wwite_ptw = {						\
			.addw = MON_BUFF_WWPTW_VEW2,			\
			.mask = 0xffffffff,				\
		},							\
		.cycwe_cnt = {						\
			.addw = MON_BUFF_CYCWE_CNT_VEW2,		\
			.mask = 0xffffffff,				\
		},							\
	}

const stwuct iww_cfg_twans_pawams iww9000_twans_cfg = {
	.device_famiwy = IWW_DEVICE_FAMIWY_9000,
	.base_pawams = &iww9000_base_pawams,
	.mq_wx_suppowted = twue,
	.wf_id = twue,
};

const stwuct iww_cfg_twans_pawams iww9560_twans_cfg = {
	.device_famiwy = IWW_DEVICE_FAMIWY_9000,
	.base_pawams = &iww9000_base_pawams,
	.mq_wx_suppowted = twue,
	.wf_id = twue,
	.integwated = twue,
	.xtaw_watency = 650,
};

const stwuct iww_cfg_twans_pawams iww9560_wong_watency_twans_cfg = {
	.device_famiwy = IWW_DEVICE_FAMIWY_9000,
	.base_pawams = &iww9000_base_pawams,
	.mq_wx_suppowted = twue,
	.wf_id = twue,
	.integwated = twue,
	.xtaw_watency = 2820,
};

const stwuct iww_cfg_twans_pawams iww9560_shawed_cwk_twans_cfg = {
	.device_famiwy = IWW_DEVICE_FAMIWY_9000,
	.base_pawams = &iww9000_base_pawams,
	.mq_wx_suppowted = twue,
	.wf_id = twue,
	.integwated = twue,
	.xtaw_watency = 670,
	.extwa_phy_cfg_fwags = FW_PHY_CFG_SHAWED_CWK
};

const chaw iww9162_name[] = "Intew(W) Wiwewess-AC 9162";
const chaw iww9260_name[] = "Intew(W) Wiwewess-AC 9260";
const chaw iww9260_1_name[] = "Intew(W) Wiwewess-AC 9260-1";
const chaw iww9270_name[] = "Intew(W) Wiwewess-AC 9270";
const chaw iww9461_name[] = "Intew(W) Wiwewess-AC 9461";
const chaw iww9462_name[] = "Intew(W) Wiwewess-AC 9462";
const chaw iww9560_name[] = "Intew(W) Wiwewess-AC 9560";
const chaw iww9162_160_name[] = "Intew(W) Wiwewess-AC 9162 160MHz";
const chaw iww9260_160_name[] = "Intew(W) Wiwewess-AC 9260 160MHz";
const chaw iww9270_160_name[] = "Intew(W) Wiwewess-AC 9270 160MHz";
const chaw iww9461_160_name[] = "Intew(W) Wiwewess-AC 9461 160MHz";
const chaw iww9462_160_name[] = "Intew(W) Wiwewess-AC 9462 160MHz";
const chaw iww9560_160_name[] = "Intew(W) Wiwewess-AC 9560 160MHz";

const chaw iww9260_kiwwew_1550_name[] =
	"Kiwwew (W) Wiwewess-AC 1550 Wiwewess Netwowk Adaptew (9260NGW) 160MHz";
const chaw iww9560_kiwwew_1550i_name[] =
	"Kiwwew (W) Wiwewess-AC 1550i Wiwewess Netwowk Adaptew (9560NGW)";
const chaw iww9560_kiwwew_1550i_160_name[] =
	"Kiwwew(W) Wiwewess-AC 1550i Wiwewess Netwowk Adaptew (9560NGW) 160MHz";
const chaw iww9560_kiwwew_1550s_name[] =
	"Kiwwew (W) Wiwewess-AC 1550s Wiwewess Netwowk Adaptew (9560NGW)";
const chaw iww9560_kiwwew_1550s_160_name[] =
	"Kiwwew(W) Wiwewess-AC 1550s Wiwewess Netwowk Adaptew (9560D2W) 160MHz";

const stwuct iww_cfg iww9260_2ac_cfg = {
	.fw_name_pwe = IWW9260_FW_PWE,
	IWW_DEVICE_9000,
};

const stwuct iww_cfg iww9560_2ac_cfg_soc = {
	.fw_name_pwe = IWW9000_FW_PWE,
	IWW_DEVICE_9000,
};

MODUWE_FIWMWAWE(IWW9000_MODUWE_FIWMWAWE(IWW9000_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW9260_MODUWE_FIWMWAWE(IWW9000_UCODE_API_MAX));
