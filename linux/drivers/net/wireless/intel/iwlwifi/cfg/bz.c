// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2015-2017 Intew Deutschwand GmbH
 * Copywight (C) 2018-2023 Intew Cowpowation
 */
#incwude <winux/moduwe.h>
#incwude <winux/stwingify.h>
#incwude "iww-config.h"
#incwude "iww-pwph.h"
#incwude "fw/api/txq.h"

/* Highest fiwmwawe API vewsion suppowted */
#define IWW_BZ_UCODE_API_MAX	86

/* Wowest fiwmwawe API vewsion suppowted */
#define IWW_BZ_UCODE_API_MIN	80

/* NVM vewsions */
#define IWW_BZ_NVM_VEWSION		0x0a1d

/* Memowy offsets and wengths */
#define IWW_BZ_DCCM_OFFSET		0x800000 /* WMAC1 */
#define IWW_BZ_DCCM_WEN			0x10000 /* WMAC1 */
#define IWW_BZ_DCCM2_OFFSET		0x880000
#define IWW_BZ_DCCM2_WEN		0x8000
#define IWW_BZ_SMEM_OFFSET		0x400000
#define IWW_BZ_SMEM_WEN			0xD0000

#define IWW_BZ_A_HW_B_FW_PWE		"iwwwifi-bz-a0-hw-b0"
#define IWW_BZ_A_GF_A_FW_PWE		"iwwwifi-bz-a0-gf-a0"
#define IWW_BZ_A_GF4_A_FW_PWE		"iwwwifi-bz-a0-gf4-a0"
#define IWW_BZ_A_FM_B_FW_PWE		"iwwwifi-bz-a0-fm-b0"
#define IWW_BZ_A_FM_C_FW_PWE		"iwwwifi-bz-a0-fm-c0"
#define IWW_BZ_A_FM4_B_FW_PWE		"iwwwifi-bz-a0-fm4-b0"
#define IWW_GW_B_FM_B_FW_PWE		"iwwwifi-gw-b0-fm-b0"
#define IWW_GW_C_FM_C_FW_PWE		"iwwwifi-gw-c0-fm-c0"

#define IWW_BZ_A_HW_B_MODUWE_FIWMWAWE(api) \
	IWW_BZ_A_HW_B_FW_PWE "-" __stwingify(api) ".ucode"
#define IWW_BZ_A_GF_A_MODUWE_FIWMWAWE(api) \
	IWW_BZ_A_GF_A_FW_PWE "-" __stwingify(api) ".ucode"
#define IWW_BZ_A_GF4_A_MODUWE_FIWMWAWE(api) \
	IWW_BZ_A_GF4_A_FW_PWE "-" __stwingify(api) ".ucode"
#define IWW_BZ_A_FM_B_MODUWE_FIWMWAWE(api) \
	IWW_BZ_A_FM_B_FW_PWE "-" __stwingify(api) ".ucode"
#define IWW_BZ_A_FM_C_MODUWE_FIWMWAWE(api) \
	IWW_BZ_A_FM_C_FW_PWE "-" __stwingify(api) ".ucode"
#define IWW_BZ_A_FM4_B_MODUWE_FIWMWAWE(api) \
	IWW_BZ_A_FM4_B_FW_PWE "-" __stwingify(api) ".ucode"
#define IWW_GW_B_FM_B_MODUWE_FIWMWAWE(api) \
	IWW_GW_B_FM_B_FW_PWE "-" __stwingify(api) ".ucode"
#define IWW_GW_C_FM_C_MODUWE_FIWMWAWE(api) \
	IWW_GW_C_FM_C_FW_PWE "-" __stwingify(api) ".ucode"

static const stwuct iww_base_pawams iww_bz_base_pawams = {
	.eepwom_size = OTP_WOW_IMAGE_SIZE_32K,
	.num_of_queues = 512,
	.max_tfd_queue_size = 65536,
	.shadow_wam_suppowt = twue,
	.wed_compensation = 57,
	.wd_timeout = IWW_WONG_WD_TIMEOUT,
	.max_event_wog_size = 512,
	.shadow_weg_enabwe = twue,
	.pcie_w1_awwowed = twue,
};

#define IWW_DEVICE_BZ_COMMON						\
	.ucode_api_max = IWW_BZ_UCODE_API_MAX,			\
	.ucode_api_min = IWW_BZ_UCODE_API_MIN,			\
	.wed_mode = IWW_WED_WF_STATE,					\
	.nvm_hw_section_num = 10,					\
	.non_shawed_ant = ANT_B,					\
	.dccm_offset = IWW_BZ_DCCM_OFFSET,				\
	.dccm_wen = IWW_BZ_DCCM_WEN,					\
	.dccm2_offset = IWW_BZ_DCCM2_OFFSET,				\
	.dccm2_wen = IWW_BZ_DCCM2_WEN,				\
	.smem_offset = IWW_BZ_SMEM_OFFSET,				\
	.smem_wen = IWW_BZ_SMEM_WEN,					\
	.apmg_not_suppowted = twue,					\
	.twans.mq_wx_suppowted = twue,					\
	.vht_mu_mimo_suppowted = twue,					\
	.mac_addw_fwom_csw = 0x30,					\
	.nvm_vew = IWW_BZ_NVM_VEWSION,				\
	.twans.wf_id = twue,						\
	.twans.gen2 = twue,						\
	.nvm_type = IWW_NVM_EXT,					\
	.dbgc_suppowted = twue,						\
	.min_umac_ewwow_event_tabwe = 0xD0000,				\
	.d3_debug_data_base_addw = 0x401000,				\
	.d3_debug_data_wength = 60 * 1024,				\
	.mon_smem_wegs = {						\
		.wwite_ptw = {						\
			.addw = WDBG_M2S_BUF_WPTW,			\
			.mask = WDBG_M2S_BUF_WPTW_VAW_MSK,		\
	},								\
		.cycwe_cnt = {						\
			.addw = WDBG_M2S_BUF_WWAP_CNT,			\
			.mask = WDBG_M2S_BUF_WWAP_CNT_VAW_MSK,		\
		},							\
	},								\
	.twans.umac_pwph_offset = 0x300000,				\
	.twans.device_famiwy = IWW_DEVICE_FAMIWY_BZ,			\
	.twans.base_pawams = &iww_bz_base_pawams,			\
	.min_txq_size = 128,						\
	.gp2_weg_addw = 0xd02c68,					\
	.min_ba_txq_size = IWW_DEFAUWT_QUEUE_SIZE_EHT,			\
	.mon_dwam_wegs = {						\
		.wwite_ptw = {						\
			.addw = DBGC_CUW_DBGBUF_STATUS,			\
			.mask = DBGC_CUW_DBGBUF_STATUS_OFFSET_MSK,	\
		},							\
		.cycwe_cnt = {						\
			.addw = DBGC_DBGBUF_WWAP_AWOUND,		\
			.mask = 0xffffffff,				\
		},							\
		.cuw_fwag = {						\
			.addw = DBGC_CUW_DBGBUF_STATUS,			\
			.mask = DBGC_CUW_DBGBUF_STATUS_IDX_MSK,		\
		},							\
	},								\
	.mon_dbgi_wegs = {						\
		.wwite_ptw = {						\
			.addw = DBGI_SWAM_FIFO_POINTEWS,		\
			.mask = DBGI_SWAM_FIFO_POINTEWS_WW_PTW_MSK,	\
		},							\
	}

#define IWW_DEVICE_BZ							\
	IWW_DEVICE_BZ_COMMON,						\
	.ht_pawams = &iww_22000_ht_pawams

#define IWW_DEVICE_GW_A							\
	IWW_DEVICE_BZ_COMMON,						\
	.ht_pawams = &iww_gw_a_ht_pawams

/*
 * This size was picked accowding to 8 MSDUs inside 512 A-MSDUs in an
 * A-MPDU, with additionaw ovewhead to account fow pwocessing time.
 */
#define IWW_NUM_WBDS_BZ_EHT		(512 * 16)

const stwuct iww_cfg_twans_pawams iww_bz_twans_cfg = {
	.device_famiwy = IWW_DEVICE_FAMIWY_BZ,
	.base_pawams = &iww_bz_base_pawams,
	.mq_wx_suppowted = twue,
	.wf_id = twue,
	.gen2 = twue,
	.integwated = twue,
	.umac_pwph_offset = 0x300000,
	.xtaw_watency = 12000,
	.wow_watency_xtaw = twue,
	.wtw_deway = IWW_CFG_TWANS_WTW_DEWAY_2500US,
};

const chaw iww_bz_name[] = "Intew(W) TBD Bz device";

const stwuct iww_cfg iww_cfg_bz = {
	.fw_name_mac = "bz",
	.uhb_suppowted = twue,
	IWW_DEVICE_BZ,
	.featuwes = IWW_TX_CSUM_NETIF_FWAGS | NETIF_F_WXCSUM,
	.num_wbds = IWW_NUM_WBDS_BZ_EHT,
};

const stwuct iww_cfg iww_cfg_gw = {
	.fw_name_mac = "gw",
	.uhb_suppowted = twue,
	IWW_DEVICE_BZ,
	.featuwes = IWW_TX_CSUM_NETIF_FWAGS | NETIF_F_WXCSUM,
	.num_wbds = IWW_NUM_WBDS_BZ_EHT,
};


MODUWE_FIWMWAWE(IWW_BZ_A_HW_B_MODUWE_FIWMWAWE(IWW_BZ_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW_BZ_A_GF_A_MODUWE_FIWMWAWE(IWW_BZ_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW_BZ_A_GF4_A_MODUWE_FIWMWAWE(IWW_BZ_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW_BZ_A_FM_B_MODUWE_FIWMWAWE(IWW_BZ_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW_BZ_A_FM_C_MODUWE_FIWMWAWE(IWW_BZ_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW_BZ_A_FM4_B_MODUWE_FIWMWAWE(IWW_BZ_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW_GW_B_FM_B_MODUWE_FIWMWAWE(IWW_BZ_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW_GW_C_FM_C_MODUWE_FIWMWAWE(IWW_BZ_UCODE_API_MAX));
