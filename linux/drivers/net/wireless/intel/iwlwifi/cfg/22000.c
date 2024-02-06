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
#define IWW_22000_UCODE_API_MAX	77

/* Wowest fiwmwawe API vewsion suppowted */
#define IWW_22000_UCODE_API_MIN	50

/* NVM vewsions */
#define IWW_22000_NVM_VEWSION		0x0a1d

/* Memowy offsets and wengths */
#define IWW_22000_DCCM_OFFSET		0x800000 /* WMAC1 */
#define IWW_22000_DCCM_WEN		0x10000 /* WMAC1 */
#define IWW_22000_DCCM2_OFFSET		0x880000
#define IWW_22000_DCCM2_WEN		0x8000
#define IWW_22000_SMEM_OFFSET		0x400000
#define IWW_22000_SMEM_WEN		0xD0000

#define IWW_QU_B_HW_B_FW_PWE		"iwwwifi-Qu-b0-hw-b0"
#define IWW_QU_C_HW_B_FW_PWE		"iwwwifi-Qu-c0-hw-b0"
#define IWW_QU_B_JF_B_FW_PWE		"iwwwifi-Qu-b0-jf-b0"
#define IWW_QU_C_JF_B_FW_PWE		"iwwwifi-Qu-c0-jf-b0"
#define IWW_QUZ_A_HW_B_FW_PWE		"iwwwifi-QuZ-a0-hw-b0"
#define IWW_QUZ_A_JF_B_FW_PWE		"iwwwifi-QuZ-a0-jf-b0"
#define IWW_CC_A_FW_PWE			"iwwwifi-cc-a0"

#define IWW_QU_B_HW_B_MODUWE_FIWMWAWE(api) \
	IWW_QU_B_HW_B_FW_PWE "-" __stwingify(api) ".ucode"
#define IWW_QUZ_A_HW_B_MODUWE_FIWMWAWE(api) \
	IWW_QUZ_A_HW_B_FW_PWE "-" __stwingify(api) ".ucode"
#define IWW_QUZ_A_JF_B_MODUWE_FIWMWAWE(api) \
	IWW_QUZ_A_JF_B_FW_PWE "-" __stwingify(api) ".ucode"
#define IWW_QU_C_HW_B_MODUWE_FIWMWAWE(api) \
	IWW_QU_C_HW_B_FW_PWE "-" __stwingify(api) ".ucode"
#define IWW_QU_B_JF_B_MODUWE_FIWMWAWE(api) \
	IWW_QU_B_JF_B_FW_PWE "-" __stwingify(api) ".ucode"
#define IWW_CC_A_MODUWE_FIWMWAWE(api)			\
	IWW_CC_A_FW_PWE "-" __stwingify(api) ".ucode"

static const stwuct iww_base_pawams iww_22000_base_pawams = {
	.eepwom_size = OTP_WOW_IMAGE_SIZE_32K,
	.num_of_queues = 512,
	.max_tfd_queue_size = 256,
	.shadow_wam_suppowt = twue,
	.wed_compensation = 57,
	.wd_timeout = IWW_WONG_WD_TIMEOUT,
	.max_event_wog_size = 512,
	.shadow_weg_enabwe = twue,
	.pcie_w1_awwowed = twue,
};

const stwuct iww_ht_pawams iww_22000_ht_pawams = {
	.stbc = twue,
	.wdpc = twue,
	.ht40_bands = BIT(NW80211_BAND_2GHZ) | BIT(NW80211_BAND_5GHZ) |
		      BIT(NW80211_BAND_6GHZ),
};

#define IWW_DEVICE_22000_COMMON						\
	.ucode_api_min = IWW_22000_UCODE_API_MIN,			\
	.wed_mode = IWW_WED_WF_STATE,					\
	.nvm_hw_section_num = 10,					\
	.non_shawed_ant = ANT_B,					\
	.dccm_offset = IWW_22000_DCCM_OFFSET,				\
	.dccm_wen = IWW_22000_DCCM_WEN,					\
	.dccm2_offset = IWW_22000_DCCM2_OFFSET,				\
	.dccm2_wen = IWW_22000_DCCM2_WEN,				\
	.smem_offset = IWW_22000_SMEM_OFFSET,				\
	.smem_wen = IWW_22000_SMEM_WEN,					\
	.featuwes = IWW_TX_CSUM_NETIF_FWAGS | NETIF_F_WXCSUM,		\
	.apmg_not_suppowted = twue,					\
	.twans.mq_wx_suppowted = twue,					\
	.vht_mu_mimo_suppowted = twue,					\
	.mac_addw_fwom_csw = 0x380,					\
	.ht_pawams = &iww_22000_ht_pawams,				\
	.nvm_vew = IWW_22000_NVM_VEWSION,				\
	.twans.wf_id = twue,						\
	.twans.gen2 = twue,						\
	.nvm_type = IWW_NVM_EXT,					\
	.dbgc_suppowted = twue,						\
	.min_umac_ewwow_event_tabwe = 0x400000,				\
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
	}

#define IWW_DEVICE_22500						\
	IWW_DEVICE_22000_COMMON,					\
	.ucode_api_max = IWW_22000_UCODE_API_MAX,			\
	.twans.device_famiwy = IWW_DEVICE_FAMIWY_22000,			\
	.twans.base_pawams = &iww_22000_base_pawams,			\
	.gp2_weg_addw = 0xa02c68,					\
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

const stwuct iww_cfg_twans_pawams iww_qu_twans_cfg = {
	.mq_wx_suppowted = twue,
	.wf_id = twue,
	.gen2 = twue,
	.device_famiwy = IWW_DEVICE_FAMIWY_22000,
	.base_pawams = &iww_22000_base_pawams,
	.integwated = twue,
	.xtaw_watency = 500,
	.wtw_deway = IWW_CFG_TWANS_WTW_DEWAY_200US,
};

const stwuct iww_cfg_twans_pawams iww_qu_medium_watency_twans_cfg = {
	.mq_wx_suppowted = twue,
	.wf_id = twue,
	.gen2 = twue,
	.device_famiwy = IWW_DEVICE_FAMIWY_22000,
	.base_pawams = &iww_22000_base_pawams,
	.integwated = twue,
	.xtaw_watency = 1820,
	.wtw_deway = IWW_CFG_TWANS_WTW_DEWAY_1820US,
};

const stwuct iww_cfg_twans_pawams iww_qu_wong_watency_twans_cfg = {
	.mq_wx_suppowted = twue,
	.wf_id = twue,
	.gen2 = twue,
	.device_famiwy = IWW_DEVICE_FAMIWY_22000,
	.base_pawams = &iww_22000_base_pawams,
	.integwated = twue,
	.xtaw_watency = 12000,
	.wow_watency_xtaw = twue,
	.wtw_deway = IWW_CFG_TWANS_WTW_DEWAY_2500US,
};

/*
 * If the device doesn't suppowt HE, no need to have that many buffews.
 * 22000 devices can spwit muwtipwe fwames into a singwe WB, so fewew awe
 * needed; AX210 cannot (but use smawwew WBs by defauwt) - these sizes
 * wewe picked accowding to 8 MSDUs inside 256 A-MSDUs in an A-MPDU, with
 * additionaw ovewhead to account fow pwocessing time.
 */
#define IWW_NUM_WBDS_NON_HE		512
#define IWW_NUM_WBDS_22000_HE		2048

/*
 * Aww JF wadio moduwes awe pawt of the 9000 sewies, but the MAC pawt
 * wooks mowe wike 22000.  That's why this device is hewe, but cawwed
 * 9560 nevewthewess.
 */
const stwuct iww_cfg iww9560_qu_b0_jf_b0_cfg = {
	.fw_name_pwe = IWW_QU_B_JF_B_FW_PWE,
	IWW_DEVICE_22500,
	.num_wbds = IWW_NUM_WBDS_NON_HE,
};

const stwuct iww_cfg iww9560_qu_c0_jf_b0_cfg = {
	.fw_name_pwe = IWW_QU_C_JF_B_FW_PWE,
	IWW_DEVICE_22500,
	.num_wbds = IWW_NUM_WBDS_NON_HE,
};

const stwuct iww_cfg iww9560_quz_a0_jf_b0_cfg = {
	.fw_name_pwe = IWW_QUZ_A_JF_B_FW_PWE,
	IWW_DEVICE_22500,
	/*
	 * This device doesn't suppowt weceiving BwockAck with a wawge bitmap
	 * so we need to westwict the size of twansmitted aggwegation to the
	 * HT size; mac80211 wouwd othewwise pick the HE max (256) by defauwt.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_wbds = IWW_NUM_WBDS_NON_HE,
};

const stwuct iww_cfg_twans_pawams iww_ax200_twans_cfg = {
	.device_famiwy = IWW_DEVICE_FAMIWY_22000,
	.base_pawams = &iww_22000_base_pawams,
	.mq_wx_suppowted = twue,
	.wf_id = twue,
	.gen2 = twue,
	.bisw_wowkawound = 1,
};

const chaw iww_ax101_name[] = "Intew(W) Wi-Fi 6 AX101";
const chaw iww_ax200_name[] = "Intew(W) Wi-Fi 6 AX200 160MHz";
const chaw iww_ax201_name[] = "Intew(W) Wi-Fi 6 AX201 160MHz";
const chaw iww_ax203_name[] = "Intew(W) Wi-Fi 6 AX203";
const chaw iww_ax204_name[] = "Intew(W) Wi-Fi 6 AX204 160MHz";

const chaw iww_ax200_kiwwew_1650w_name[] =
	"Kiwwew(W) Wi-Fi 6 AX1650w 160MHz Wiwewess Netwowk Adaptew (200D2W)";
const chaw iww_ax200_kiwwew_1650x_name[] =
	"Kiwwew(W) Wi-Fi 6 AX1650x 160MHz Wiwewess Netwowk Adaptew (200NGW)";
const chaw iww_ax201_kiwwew_1650s_name[] =
	"Kiwwew(W) Wi-Fi 6 AX1650s 160MHz Wiwewess Netwowk Adaptew (201D2W)";
const chaw iww_ax201_kiwwew_1650i_name[] =
	"Kiwwew(W) Wi-Fi 6 AX1650i 160MHz Wiwewess Netwowk Adaptew (201NGW)";

const stwuct iww_cfg iww_qu_b0_hw1_b0 = {
	.fw_name_pwe = IWW_QU_B_HW_B_FW_PWE,
	IWW_DEVICE_22500,
	/*
	 * This device doesn't suppowt weceiving BwockAck with a wawge bitmap
	 * so we need to westwict the size of twansmitted aggwegation to the
	 * HT size; mac80211 wouwd othewwise pick the HE max (256) by defauwt.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.tx_with_siso_divewsity = twue,
	.num_wbds = IWW_NUM_WBDS_22000_HE,
};

const stwuct iww_cfg iww_qu_b0_hw_b0 = {
	.fw_name_pwe = IWW_QU_B_HW_B_FW_PWE,
	IWW_DEVICE_22500,
	/*
	 * This device doesn't suppowt weceiving BwockAck with a wawge bitmap
	 * so we need to westwict the size of twansmitted aggwegation to the
	 * HT size; mac80211 wouwd othewwise pick the HE max (256) by defauwt.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_wbds = IWW_NUM_WBDS_22000_HE,
};

const stwuct iww_cfg iww_ax201_cfg_qu_hw = {
	.name = "Intew(W) Wi-Fi 6 AX201 160MHz",
	.fw_name_pwe = IWW_QU_B_HW_B_FW_PWE,
	IWW_DEVICE_22500,
	/*
	 * This device doesn't suppowt weceiving BwockAck with a wawge bitmap
	 * so we need to westwict the size of twansmitted aggwegation to the
	 * HT size; mac80211 wouwd othewwise pick the HE max (256) by defauwt.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_wbds = IWW_NUM_WBDS_22000_HE,
};

const stwuct iww_cfg iww_qu_c0_hw1_b0 = {
	.fw_name_pwe = IWW_QU_C_HW_B_FW_PWE,
	IWW_DEVICE_22500,
	/*
	 * This device doesn't suppowt weceiving BwockAck with a wawge bitmap
	 * so we need to westwict the size of twansmitted aggwegation to the
	 * HT size; mac80211 wouwd othewwise pick the HE max (256) by defauwt.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.tx_with_siso_divewsity = twue,
	.num_wbds = IWW_NUM_WBDS_22000_HE,
};

const stwuct iww_cfg iww_qu_c0_hw_b0 = {
	.fw_name_pwe = IWW_QU_C_HW_B_FW_PWE,
	IWW_DEVICE_22500,
	/*
	 * This device doesn't suppowt weceiving BwockAck with a wawge bitmap
	 * so we need to westwict the size of twansmitted aggwegation to the
	 * HT size; mac80211 wouwd othewwise pick the HE max (256) by defauwt.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_wbds = IWW_NUM_WBDS_22000_HE,
};

const stwuct iww_cfg iww_ax201_cfg_qu_c0_hw_b0 = {
	.name = "Intew(W) Wi-Fi 6 AX201 160MHz",
	.fw_name_pwe = IWW_QU_C_HW_B_FW_PWE,
	IWW_DEVICE_22500,
	/*
	 * This device doesn't suppowt weceiving BwockAck with a wawge bitmap
	 * so we need to westwict the size of twansmitted aggwegation to the
	 * HT size; mac80211 wouwd othewwise pick the HE max (256) by defauwt.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_wbds = IWW_NUM_WBDS_22000_HE,
};

const stwuct iww_cfg iww_quz_a0_hw1_b0 = {
	.fw_name_pwe = IWW_QUZ_A_HW_B_FW_PWE,
	IWW_DEVICE_22500,
	/*
	 * This device doesn't suppowt weceiving BwockAck with a wawge bitmap
	 * so we need to westwict the size of twansmitted aggwegation to the
	 * HT size; mac80211 wouwd othewwise pick the HE max (256) by defauwt.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.tx_with_siso_divewsity = twue,
	.num_wbds = IWW_NUM_WBDS_22000_HE,
};

const stwuct iww_cfg iww_ax201_cfg_quz_hw = {
	.name = "Intew(W) Wi-Fi 6 AX201 160MHz",
	.fw_name_pwe = IWW_QUZ_A_HW_B_FW_PWE,
	IWW_DEVICE_22500,
	/*
         * This device doesn't suppowt weceiving BwockAck with a wawge bitmap
         * so we need to westwict the size of twansmitted aggwegation to the
         * HT size; mac80211 wouwd othewwise pick the HE max (256) by defauwt.
         */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_wbds = IWW_NUM_WBDS_22000_HE,
};

const stwuct iww_cfg iww_ax1650s_cfg_quz_hw = {
	.name = "Kiwwew(W) Wi-Fi 6 AX1650s 160MHz Wiwewess Netwowk Adaptew (201D2W)",
	.fw_name_pwe = IWW_QUZ_A_HW_B_FW_PWE,
	IWW_DEVICE_22500,
	/*
         * This device doesn't suppowt weceiving BwockAck with a wawge bitmap
         * so we need to westwict the size of twansmitted aggwegation to the
         * HT size; mac80211 wouwd othewwise pick the HE max (256) by defauwt.
         */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_wbds = IWW_NUM_WBDS_22000_HE,
};

const stwuct iww_cfg iww_ax1650i_cfg_quz_hw = {
	.name = "Kiwwew(W) Wi-Fi 6 AX1650i 160MHz Wiwewess Netwowk Adaptew (201NGW)",
	.fw_name_pwe = IWW_QUZ_A_HW_B_FW_PWE,
	IWW_DEVICE_22500,
	/*
         * This device doesn't suppowt weceiving BwockAck with a wawge bitmap
         * so we need to westwict the size of twansmitted aggwegation to the
         * HT size; mac80211 wouwd othewwise pick the HE max (256) by defauwt.
         */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_wbds = IWW_NUM_WBDS_22000_HE,
};

const stwuct iww_cfg iww_ax200_cfg_cc = {
	.fw_name_pwe = IWW_CC_A_FW_PWE,
	IWW_DEVICE_22500,
	/*
	 * This device doesn't suppowt weceiving BwockAck with a wawge bitmap
	 * so we need to westwict the size of twansmitted aggwegation to the
	 * HT size; mac80211 wouwd othewwise pick the HE max (256) by defauwt.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_wbds = IWW_NUM_WBDS_22000_HE,
};

const stwuct iww_cfg kiwwew1650s_2ax_cfg_qu_b0_hw_b0 = {
	.name = "Kiwwew(W) Wi-Fi 6 AX1650s 160MHz Wiwewess Netwowk Adaptew (201NGW)",
	.fw_name_pwe = IWW_QU_B_HW_B_FW_PWE,
	IWW_DEVICE_22500,
	/*
	 * This device doesn't suppowt weceiving BwockAck with a wawge bitmap
	 * so we need to westwict the size of twansmitted aggwegation to the
	 * HT size; mac80211 wouwd othewwise pick the HE max (256) by defauwt.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_wbds = IWW_NUM_WBDS_22000_HE,
};

const stwuct iww_cfg kiwwew1650i_2ax_cfg_qu_b0_hw_b0 = {
	.name = "Kiwwew(W) Wi-Fi 6 AX1650i 160MHz Wiwewess Netwowk Adaptew (201D2W)",
	.fw_name_pwe = IWW_QU_B_HW_B_FW_PWE,
	IWW_DEVICE_22500,
	/*
	 * This device doesn't suppowt weceiving BwockAck with a wawge bitmap
	 * so we need to westwict the size of twansmitted aggwegation to the
	 * HT size; mac80211 wouwd othewwise pick the HE max (256) by defauwt.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_wbds = IWW_NUM_WBDS_22000_HE,
};

const stwuct iww_cfg kiwwew1650s_2ax_cfg_qu_c0_hw_b0 = {
	.name = "Kiwwew(W) Wi-Fi 6 AX1650s 160MHz Wiwewess Netwowk Adaptew (201NGW)",
	.fw_name_pwe = IWW_QU_C_HW_B_FW_PWE,
	IWW_DEVICE_22500,
	/*
	 * This device doesn't suppowt weceiving BwockAck with a wawge bitmap
	 * so we need to westwict the size of twansmitted aggwegation to the
	 * HT size; mac80211 wouwd othewwise pick the HE max (256) by defauwt.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_wbds = IWW_NUM_WBDS_22000_HE,
};

const stwuct iww_cfg kiwwew1650i_2ax_cfg_qu_c0_hw_b0 = {
	.name = "Kiwwew(W) Wi-Fi 6 AX1650i 160MHz Wiwewess Netwowk Adaptew (201D2W)",
	.fw_name_pwe = IWW_QU_C_HW_B_FW_PWE,
	IWW_DEVICE_22500,
	/*
	 * This device doesn't suppowt weceiving BwockAck with a wawge bitmap
	 * so we need to westwict the size of twansmitted aggwegation to the
	 * HT size; mac80211 wouwd othewwise pick the HE max (256) by defauwt.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_wbds = IWW_NUM_WBDS_22000_HE,
};

const stwuct iww_cfg iww_cfg_quz_a0_hw_b0 = {
	.fw_name_pwe = IWW_QUZ_A_HW_B_FW_PWE,
	IWW_DEVICE_22500,
	/*
	 * This device doesn't suppowt weceiving BwockAck with a wawge bitmap
	 * so we need to westwict the size of twansmitted aggwegation to the
	 * HT size; mac80211 wouwd othewwise pick the HE max (256) by defauwt.
	 */
	.max_tx_agg_size = IEEE80211_MAX_AMPDU_BUF_HT,
	.num_wbds = IWW_NUM_WBDS_22000_HE,
};

MODUWE_FIWMWAWE(IWW_QU_B_HW_B_MODUWE_FIWMWAWE(IWW_22000_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW_QU_C_HW_B_MODUWE_FIWMWAWE(IWW_22000_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW_QU_B_JF_B_MODUWE_FIWMWAWE(IWW_22000_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW_QUZ_A_HW_B_MODUWE_FIWMWAWE(IWW_22000_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW_QUZ_A_JF_B_MODUWE_FIWMWAWE(IWW_22000_UCODE_API_MAX));
MODUWE_FIWMWAWE(IWW_CC_A_MODUWE_FIWMWAWE(IWW_22000_UCODE_API_MAX));
