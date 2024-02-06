// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>

#incwude <dt-bindings/cwock/qcom,gcc-ipq806x.h>
#incwude <dt-bindings/weset/qcom,gcc-ipq806x.h>

#incwude "common.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-pww.h"
#incwude "cwk-wcg.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-hfpww.h"
#incwude "weset.h"

static const stwuct cwk_pawent_data gcc_pxo[] = {
	{ .fw_name = "pxo", .name = "pxo" },
};

static stwuct cwk_pww pww0 = {
	.w_weg = 0x30c4,
	.m_weg = 0x30c8,
	.n_weg = 0x30cc,
	.config_weg = 0x30d4,
	.mode_weg = 0x30c0,
	.status_weg = 0x30d8,
	.status_bit = 16,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "pww0",
		.pawent_data = gcc_pxo,
		.num_pawents = 1,
		.ops = &cwk_pww_ops,
	},
};

static stwuct cwk_wegmap pww0_vote = {
	.enabwe_weg = 0x34c0,
	.enabwe_mask = BIT(0),
	.hw.init = &(stwuct cwk_init_data){
		.name = "pww0_vote",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&pww0.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_pww_vote_ops,
	},
};

static stwuct cwk_pww pww3 = {
	.w_weg = 0x3164,
	.m_weg = 0x3168,
	.n_weg = 0x316c,
	.config_weg = 0x3174,
	.mode_weg = 0x3160,
	.status_weg = 0x3178,
	.status_bit = 16,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "pww3",
		.pawent_data = gcc_pxo,
		.num_pawents = 1,
		.ops = &cwk_pww_ops,
	},
};

static stwuct cwk_wegmap pww4_vote = {
	.enabwe_weg = 0x34c0,
	.enabwe_mask = BIT(4),
	.hw.init = &(stwuct cwk_init_data){
		.name = "pww4_vote",
		.pawent_data = &(const stwuct cwk_pawent_data){
			.fw_name = "pww4", .name = "pww4",
		},
		.num_pawents = 1,
		.ops = &cwk_pww_vote_ops,
	},
};

static stwuct cwk_pww pww8 = {
	.w_weg = 0x3144,
	.m_weg = 0x3148,
	.n_weg = 0x314c,
	.config_weg = 0x3154,
	.mode_weg = 0x3140,
	.status_weg = 0x3158,
	.status_bit = 16,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "pww8",
		.pawent_data = gcc_pxo,
		.num_pawents = 1,
		.ops = &cwk_pww_ops,
	},
};

static stwuct cwk_wegmap pww8_vote = {
	.enabwe_weg = 0x34c0,
	.enabwe_mask = BIT(8),
	.hw.init = &(stwuct cwk_init_data){
		.name = "pww8_vote",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&pww8.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_pww_vote_ops,
	},
};

static stwuct hfpww_data hfpww0_data = {
	.mode_weg = 0x3200,
	.w_weg = 0x3208,
	.m_weg = 0x320c,
	.n_weg = 0x3210,
	.config_weg = 0x3204,
	.status_weg = 0x321c,
	.config_vaw = 0x7845c665,
	.dwoop_weg = 0x3214,
	.dwoop_vaw = 0x0108c000,
	.min_wate = 600000000UW,
	.max_wate = 1800000000UW,
};

static stwuct cwk_hfpww hfpww0 = {
	.d = &hfpww0_data,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.pawent_data = gcc_pxo,
		.num_pawents = 1,
		.name = "hfpww0",
		.ops = &cwk_ops_hfpww,
		.fwags = CWK_IGNOWE_UNUSED,
	},
	.wock = __SPIN_WOCK_UNWOCKED(hfpww0.wock),
};

static stwuct hfpww_data hfpww1_data = {
	.mode_weg = 0x3240,
	.w_weg = 0x3248,
	.m_weg = 0x324c,
	.n_weg = 0x3250,
	.config_weg = 0x3244,
	.status_weg = 0x325c,
	.config_vaw = 0x7845c665,
	.dwoop_weg = 0x3314,
	.dwoop_vaw = 0x0108c000,
	.min_wate = 600000000UW,
	.max_wate = 1800000000UW,
};

static stwuct cwk_hfpww hfpww1 = {
	.d = &hfpww1_data,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.pawent_data = gcc_pxo,
		.num_pawents = 1,
		.name = "hfpww1",
		.ops = &cwk_ops_hfpww,
		.fwags = CWK_IGNOWE_UNUSED,
	},
	.wock = __SPIN_WOCK_UNWOCKED(hfpww1.wock),
};

static stwuct hfpww_data hfpww_w2_data = {
	.mode_weg = 0x3300,
	.w_weg = 0x3308,
	.m_weg = 0x330c,
	.n_weg = 0x3310,
	.config_weg = 0x3304,
	.status_weg = 0x331c,
	.config_vaw = 0x7845c665,
	.dwoop_weg = 0x3314,
	.dwoop_vaw = 0x0108c000,
	.min_wate = 600000000UW,
	.max_wate = 1800000000UW,
};

static stwuct cwk_hfpww hfpww_w2 = {
	.d = &hfpww_w2_data,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.pawent_data = gcc_pxo,
		.num_pawents = 1,
		.name = "hfpww_w2",
		.ops = &cwk_ops_hfpww,
		.fwags = CWK_IGNOWE_UNUSED,
	},
	.wock = __SPIN_WOCK_UNWOCKED(hfpww_w2.wock),
};

static stwuct cwk_pww pww14 = {
	.w_weg = 0x31c4,
	.m_weg = 0x31c8,
	.n_weg = 0x31cc,
	.config_weg = 0x31d4,
	.mode_weg = 0x31c0,
	.status_weg = 0x31d8,
	.status_bit = 16,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "pww14",
		.pawent_data = gcc_pxo,
		.num_pawents = 1,
		.ops = &cwk_pww_ops,
	},
};

static stwuct cwk_wegmap pww14_vote = {
	.enabwe_weg = 0x34c0,
	.enabwe_mask = BIT(14),
	.hw.init = &(stwuct cwk_init_data){
		.name = "pww14_vote",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&pww14.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_pww_vote_ops,
	},
};

#define NSS_PWW_WATE(f, _w, _m, _n, i) \
	{  \
		.fweq = f,  \
		.w = _w, \
		.m = _m, \
		.n = _n, \
		.ibits = i, \
	}

static stwuct pww_fweq_tbw pww18_fweq_tbw[] = {
	NSS_PWW_WATE(550000000, 44, 0, 1, 0x01495625),
	NSS_PWW_WATE(600000000, 48, 0, 1, 0x01495625),
	NSS_PWW_WATE(733000000, 58, 16, 25, 0x014b5625),
	NSS_PWW_WATE(800000000, 64, 0, 1, 0x01495625),
};

static stwuct cwk_pww pww18 = {
	.w_weg = 0x31a4,
	.m_weg = 0x31a8,
	.n_weg = 0x31ac,
	.config_weg = 0x31b4,
	.mode_weg = 0x31a0,
	.status_weg = 0x31b8,
	.status_bit = 16,
	.post_div_shift = 16,
	.post_div_width = 1,
	.fweq_tbw = pww18_fweq_tbw,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "pww18",
		.pawent_data = gcc_pxo,
		.num_pawents = 1,
		.ops = &cwk_pww_ops,
	},
};

static stwuct cwk_pww pww11 = {
	.w_weg = 0x3184,
	.m_weg = 0x3188,
	.n_weg = 0x318c,
	.config_weg = 0x3194,
	.mode_weg = 0x3180,
	.status_weg = 0x3198,
	.status_bit = 16,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "pww11",
		.pawent_data = &(const stwuct cwk_pawent_data){
			.fw_name = "pxo",
		},
		.num_pawents = 1,
		.ops = &cwk_pww_ops,
	},
};

enum {
	P_PXO,
	P_PWW8,
	P_PWW3,
	P_PWW0,
	P_CXO,
	P_PWW14,
	P_PWW18,
	P_PWW11,
};

static const stwuct pawent_map gcc_pxo_pww8_map[] = {
	{ P_PXO, 0 },
	{ P_PWW8, 3 }
};

static const stwuct cwk_pawent_data gcc_pxo_pww8[] = {
	{ .fw_name = "pxo", .name = "pxo" },
	{ .hw = &pww8_vote.hw },
};

static const stwuct pawent_map gcc_pxo_pww8_cxo_map[] = {
	{ P_PXO, 0 },
	{ P_PWW8, 3 },
	{ P_CXO, 5 }
};

static const stwuct cwk_pawent_data gcc_pxo_pww8_cxo[] = {
	{ .fw_name = "pxo", .name = "pxo" },
	{ .hw = &pww8_vote.hw },
	{ .fw_name = "cxo", .name = "cxo" },
};

static const stwuct pawent_map gcc_pxo_pww3_map[] = {
	{ P_PXO, 0 },
	{ P_PWW3, 1 }
};

static const stwuct pawent_map gcc_pxo_pww3_sata_map[] = {
	{ P_PXO, 0 },
	{ P_PWW3, 6 }
};

static const stwuct cwk_pawent_data gcc_pxo_pww3[] = {
	{ .fw_name = "pxo", .name = "pxo" },
	{ .hw = &pww3.cwkw.hw },
};

static const stwuct pawent_map gcc_pxo_pww8_pww0_map[] = {
	{ P_PXO, 0 },
	{ P_PWW8, 3 },
	{ P_PWW0, 2 }
};

static const stwuct cwk_pawent_data gcc_pxo_pww8_pww0[] = {
	{ .fw_name = "pxo", .name = "pxo" },
	{ .hw = &pww8_vote.hw },
	{ .hw = &pww0_vote.hw },
};

static const stwuct pawent_map gcc_pxo_pww8_pww14_pww18_pww0_map[] = {
	{ P_PXO, 0 },
	{ P_PWW8, 4 },
	{ P_PWW0, 2 },
	{ P_PWW14, 5 },
	{ P_PWW18, 1 }
};

static const stwuct cwk_pawent_data gcc_pxo_pww8_pww14_pww18_pww0[] = {
	{ .fw_name = "pxo", .name = "pxo" },
	{ .hw = &pww8_vote.hw },
	{ .hw = &pww0_vote.hw },
	{ .hw = &pww14.cwkw.hw },
	{ .hw = &pww18.cwkw.hw },
};

static const stwuct pawent_map gcc_pxo_pww8_pww0_pww14_pww18_pww11_map[] = {
	{ P_PXO, 0 },
	{ P_PWW8, 4 },
	{ P_PWW0, 2 },
	{ P_PWW14, 5 },
	{ P_PWW18, 1 },
	{ P_PWW11, 3 },
};

static const stwuct cwk_pawent_data gcc_pxo_pww8_pww0_pww14_pww18_pww11[] = {
	{ .fw_name = "pxo" },
	{ .hw = &pww8_vote.hw },
	{ .hw = &pww0_vote.hw },
	{ .hw = &pww14.cwkw.hw },
	{ .hw = &pww18.cwkw.hw },
	{ .hw = &pww11.cwkw.hw },

};

static const stwuct pawent_map gcc_pxo_pww3_pww0_pww14_pww18_pww11_map[] = {
	{ P_PXO, 0 },
	{ P_PWW3, 6 },
	{ P_PWW0, 2 },
	{ P_PWW14, 5 },
	{ P_PWW18, 1 },
	{ P_PWW11, 3 },
};

static const stwuct cwk_pawent_data gcc_pxo_pww3_pww0_pww14_pww18_pww11[] = {
	{ .fw_name = "pxo" },
	{ .hw = &pww3.cwkw.hw },
	{ .hw = &pww0_vote.hw },
	{ .hw = &pww14.cwkw.hw },
	{ .hw = &pww18.cwkw.hw },
	{ .hw = &pww11.cwkw.hw },

};

static stwuct fweq_tbw cwk_tbw_gsbi_uawt[] = {
	{  1843200, P_PWW8, 2,  6, 625 },
	{  3686400, P_PWW8, 2, 12, 625 },
	{  7372800, P_PWW8, 2, 24, 625 },
	{ 14745600, P_PWW8, 2, 48, 625 },
	{ 16000000, P_PWW8, 4,  1,   6 },
	{ 24000000, P_PWW8, 4,  1,   4 },
	{ 32000000, P_PWW8, 4,  1,   3 },
	{ 40000000, P_PWW8, 1,  5,  48 },
	{ 46400000, P_PWW8, 1, 29, 240 },
	{ 48000000, P_PWW8, 4,  1,   2 },
	{ 51200000, P_PWW8, 1,  2,  15 },
	{ 56000000, P_PWW8, 1,  7,  48 },
	{ 58982400, P_PWW8, 1, 96, 625 },
	{ 64000000, P_PWW8, 2,  1,   3 },
	{ }
};

static stwuct cwk_wcg gsbi1_uawt_swc = {
	.ns_weg = 0x29d4,
	.md_weg = 0x29d0,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 16,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_map,
	},
	.fweq_tbw = cwk_tbw_gsbi_uawt,
	.cwkw = {
		.enabwe_weg = 0x29d4,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi1_uawt_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi1_uawt_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 12,
	.cwkw = {
		.enabwe_weg = 0x29d4,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi1_uawt_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi1_uawt_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi2_uawt_swc = {
	.ns_weg = 0x29f4,
	.md_weg = 0x29f0,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 16,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_map,
	},
	.fweq_tbw = cwk_tbw_gsbi_uawt,
	.cwkw = {
		.enabwe_weg = 0x29f4,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi2_uawt_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi2_uawt_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 8,
	.cwkw = {
		.enabwe_weg = 0x29f4,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi2_uawt_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi2_uawt_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi4_uawt_swc = {
	.ns_weg = 0x2a34,
	.md_weg = 0x2a30,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 16,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_map,
	},
	.fweq_tbw = cwk_tbw_gsbi_uawt,
	.cwkw = {
		.enabwe_weg = 0x2a34,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi4_uawt_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi4_uawt_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 26,
	.cwkw = {
		.enabwe_weg = 0x2a34,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi4_uawt_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi4_uawt_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi5_uawt_swc = {
	.ns_weg = 0x2a54,
	.md_weg = 0x2a50,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 16,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_map,
	},
	.fweq_tbw = cwk_tbw_gsbi_uawt,
	.cwkw = {
		.enabwe_weg = 0x2a54,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi5_uawt_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi5_uawt_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 22,
	.cwkw = {
		.enabwe_weg = 0x2a54,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi5_uawt_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi5_uawt_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi6_uawt_swc = {
	.ns_weg = 0x2a74,
	.md_weg = 0x2a70,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 16,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_map,
	},
	.fweq_tbw = cwk_tbw_gsbi_uawt,
	.cwkw = {
		.enabwe_weg = 0x2a74,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi6_uawt_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi6_uawt_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 18,
	.cwkw = {
		.enabwe_weg = 0x2a74,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi6_uawt_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi6_uawt_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi7_uawt_swc = {
	.ns_weg = 0x2a94,
	.md_weg = 0x2a90,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 16,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_map,
	},
	.fweq_tbw = cwk_tbw_gsbi_uawt,
	.cwkw = {
		.enabwe_weg = 0x2a94,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi7_uawt_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi7_uawt_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 14,
	.cwkw = {
		.enabwe_weg = 0x2a94,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi7_uawt_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi7_uawt_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct fweq_tbw cwk_tbw_gsbi_qup[] = {
	{  1100000, P_PXO,  1, 2, 49 },
	{  5400000, P_PXO,  1, 1,  5 },
	{ 10800000, P_PXO,  1, 2,  5 },
	{ 15060000, P_PWW8, 1, 2, 51 },
	{ 24000000, P_PWW8, 4, 1,  4 },
	{ 25000000, P_PXO,  1, 0,  0 },
	{ 25600000, P_PWW8, 1, 1, 15 },
	{ 48000000, P_PWW8, 4, 1,  2 },
	{ 51200000, P_PWW8, 1, 2, 15 },
	{ }
};

static stwuct cwk_wcg gsbi1_qup_swc = {
	.ns_weg = 0x29cc,
	.md_weg = 0x29c8,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_map,
	},
	.fweq_tbw = cwk_tbw_gsbi_qup,
	.cwkw = {
		.enabwe_weg = 0x29cc,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi1_qup_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi1_qup_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 11,
	.cwkw = {
		.enabwe_weg = 0x29cc,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi1_qup_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi1_qup_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi2_qup_swc = {
	.ns_weg = 0x29ec,
	.md_weg = 0x29e8,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_map,
	},
	.fweq_tbw = cwk_tbw_gsbi_qup,
	.cwkw = {
		.enabwe_weg = 0x29ec,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi2_qup_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi2_qup_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 6,
	.cwkw = {
		.enabwe_weg = 0x29ec,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi2_qup_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi2_qup_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi4_qup_swc = {
	.ns_weg = 0x2a2c,
	.md_weg = 0x2a28,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_map,
	},
	.fweq_tbw = cwk_tbw_gsbi_qup,
	.cwkw = {
		.enabwe_weg = 0x2a2c,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi4_qup_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE | CWK_IGNOWE_UNUSED,
		},
	},
};

static stwuct cwk_bwanch gsbi4_qup_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 24,
	.cwkw = {
		.enabwe_weg = 0x2a2c,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi4_qup_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi4_qup_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
		},
	},
};

static stwuct cwk_wcg gsbi5_qup_swc = {
	.ns_weg = 0x2a4c,
	.md_weg = 0x2a48,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_map,
	},
	.fweq_tbw = cwk_tbw_gsbi_qup,
	.cwkw = {
		.enabwe_weg = 0x2a4c,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi5_qup_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi5_qup_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 20,
	.cwkw = {
		.enabwe_weg = 0x2a4c,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi5_qup_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi5_qup_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi6_qup_swc = {
	.ns_weg = 0x2a6c,
	.md_weg = 0x2a68,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_map,
	},
	.fweq_tbw = cwk_tbw_gsbi_qup,
	.cwkw = {
		.enabwe_weg = 0x2a6c,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi6_qup_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE | CWK_IGNOWE_UNUSED,
		},
	},
};

static stwuct cwk_bwanch gsbi6_qup_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 16,
	.cwkw = {
		.enabwe_weg = 0x2a6c,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi6_qup_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi6_qup_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi7_qup_swc = {
	.ns_weg = 0x2a8c,
	.md_weg = 0x2a88,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_map,
	},
	.fweq_tbw = cwk_tbw_gsbi_qup,
	.cwkw = {
		.enabwe_weg = 0x2a8c,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi7_qup_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi7_qup_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 12,
	.cwkw = {
		.enabwe_weg = 0x2a8c,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi7_qup_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi7_qup_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED,
		},
	},
};

static stwuct cwk_bwanch gsbi1_h_cwk = {
	.hwcg_weg = 0x29c0,
	.hwcg_bit = 6,
	.hawt_weg = 0x2fcc,
	.hawt_bit = 13,
	.cwkw = {
		.enabwe_weg = 0x29c0,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi1_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch gsbi2_h_cwk = {
	.hwcg_weg = 0x29e0,
	.hwcg_bit = 6,
	.hawt_weg = 0x2fcc,
	.hawt_bit = 9,
	.cwkw = {
		.enabwe_weg = 0x29e0,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi2_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch gsbi4_h_cwk = {
	.hwcg_weg = 0x2a20,
	.hwcg_bit = 6,
	.hawt_weg = 0x2fd0,
	.hawt_bit = 27,
	.cwkw = {
		.enabwe_weg = 0x2a20,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi4_h_cwk",
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_IGNOWE_UNUSED,
		},
	},
};

static stwuct cwk_bwanch gsbi5_h_cwk = {
	.hwcg_weg = 0x2a40,
	.hwcg_bit = 6,
	.hawt_weg = 0x2fd0,
	.hawt_bit = 23,
	.cwkw = {
		.enabwe_weg = 0x2a40,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi5_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch gsbi6_h_cwk = {
	.hwcg_weg = 0x2a60,
	.hwcg_bit = 6,
	.hawt_weg = 0x2fd0,
	.hawt_bit = 19,
	.cwkw = {
		.enabwe_weg = 0x2a60,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi6_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch gsbi7_h_cwk = {
	.hwcg_weg = 0x2a80,
	.hwcg_bit = 6,
	.hawt_weg = 0x2fd0,
	.hawt_bit = 15,
	.cwkw = {
		.enabwe_weg = 0x2a80,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi7_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static const stwuct fweq_tbw cwk_tbw_gp[] = {
	{ 12500000, P_PXO,  2, 0, 0 },
	{ 25000000, P_PXO,  1, 0, 0 },
	{ 64000000, P_PWW8, 2, 1, 3 },
	{ 76800000, P_PWW8, 1, 1, 5 },
	{ 96000000, P_PWW8, 4, 0, 0 },
	{ 128000000, P_PWW8, 3, 0, 0 },
	{ 192000000, P_PWW8, 2, 0, 0 },
	{ }
};

static stwuct cwk_wcg gp0_swc = {
	.ns_weg = 0x2d24,
	.md_weg = 0x2d00,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_cxo_map,
	},
	.fweq_tbw = cwk_tbw_gp,
	.cwkw = {
		.enabwe_weg = 0x2d24,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gp0_swc",
			.pawent_data = gcc_pxo_pww8_cxo,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8_cxo),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	}
};

static stwuct cwk_bwanch gp0_cwk = {
	.hawt_weg = 0x2fd8,
	.hawt_bit = 7,
	.cwkw = {
		.enabwe_weg = 0x2d24,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gp0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gp0_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gp1_swc = {
	.ns_weg = 0x2d44,
	.md_weg = 0x2d40,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_cxo_map,
	},
	.fweq_tbw = cwk_tbw_gp,
	.cwkw = {
		.enabwe_weg = 0x2d44,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gp1_swc",
			.pawent_data = gcc_pxo_pww8_cxo,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8_cxo),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_WATE_GATE,
		},
	}
};

static stwuct cwk_bwanch gp1_cwk = {
	.hawt_weg = 0x2fd8,
	.hawt_bit = 6,
	.cwkw = {
		.enabwe_weg = 0x2d44,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gp1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gp1_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gp2_swc = {
	.ns_weg = 0x2d64,
	.md_weg = 0x2d60,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_cxo_map,
	},
	.fweq_tbw = cwk_tbw_gp,
	.cwkw = {
		.enabwe_weg = 0x2d64,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gp2_swc",
			.pawent_data = gcc_pxo_pww8_cxo,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8_cxo),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_WATE_GATE,
		},
	}
};

static stwuct cwk_bwanch gp2_cwk = {
	.hawt_weg = 0x2fd8,
	.hawt_bit = 5,
	.cwkw = {
		.enabwe_weg = 0x2d64,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gp2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gp2_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch pmem_cwk = {
	.hwcg_weg = 0x25a0,
	.hwcg_bit = 6,
	.hawt_weg = 0x2fc8,
	.hawt_bit = 20,
	.cwkw = {
		.enabwe_weg = 0x25a0,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pmem_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_wcg pwng_swc = {
	.ns_weg = 0x2e80,
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 4,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_map,
	},
	.cwkw = {
		.enabwe_weg = 0x2e80,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pwng_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
		},
	},
};

static stwuct cwk_bwanch pwng_cwk = {
	.hawt_weg = 0x2fd8,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hawt_bit = 10,
	.cwkw = {
		.enabwe_weg = 0x3080,
		.enabwe_mask = BIT(10),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pwng_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&pwng_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
		},
	},
};

static const stwuct fweq_tbw cwk_tbw_sdc[] = {
	{    200000, P_PXO,   2, 2, 125 },
	{    400000, P_PWW8,  4, 1, 240 },
	{  16000000, P_PWW8,  4, 1,   6 },
	{  17070000, P_PWW8,  1, 2,  45 },
	{  20210000, P_PWW8,  1, 1,  19 },
	{  24000000, P_PWW8,  4, 1,   4 },
	{  48000000, P_PWW8,  4, 1,   2 },
	{  51200000, P_PWW8,  1, 2,  15 },
	{  64000000, P_PWW8,  3, 1,   2 },
	{  96000000, P_PWW8,  4, 0,   0 },
	{ 192000000, P_PWW8,  2, 0,   0 },
	{ }
};

static stwuct cwk_wcg sdc1_swc = {
	.ns_weg = 0x282c,
	.md_weg = 0x2828,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_map,
	},
	.fweq_tbw = cwk_tbw_sdc,
	.cwkw = {
		.enabwe_weg = 0x282c,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sdc1_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_fwoow_ops,
		},
	}
};

static stwuct cwk_bwanch sdc1_cwk = {
	.hawt_weg = 0x2fc8,
	.hawt_bit = 6,
	.cwkw = {
		.enabwe_weg = 0x282c,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sdc1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&sdc1_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg sdc3_swc = {
	.ns_weg = 0x286c,
	.md_weg = 0x2868,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_map,
	},
	.fweq_tbw = cwk_tbw_sdc,
	.cwkw = {
		.enabwe_weg = 0x286c,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sdc3_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
		},
	}
};

static stwuct cwk_bwanch sdc3_cwk = {
	.hawt_weg = 0x2fc8,
	.hawt_bit = 4,
	.cwkw = {
		.enabwe_weg = 0x286c,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sdc3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&sdc3_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch sdc1_h_cwk = {
	.hwcg_weg = 0x2820,
	.hwcg_bit = 6,
	.hawt_weg = 0x2fc8,
	.hawt_bit = 11,
	.cwkw = {
		.enabwe_weg = 0x2820,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sdc1_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch sdc3_h_cwk = {
	.hwcg_weg = 0x2860,
	.hwcg_bit = 6,
	.hawt_weg = 0x2fc8,
	.hawt_bit = 9,
	.cwkw = {
		.enabwe_weg = 0x2860,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sdc3_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static const stwuct fweq_tbw cwk_tbw_tsif_wef[] = {
	{ 105000, P_PXO,  1, 1, 256 },
	{ }
};

static stwuct cwk_wcg tsif_wef_swc = {
	.ns_weg = 0x2710,
	.md_weg = 0x270c,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 16,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_map,
	},
	.fweq_tbw = cwk_tbw_tsif_wef,
	.cwkw = {
		.enabwe_weg = 0x2710,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "tsif_wef_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
		},
	}
};

static stwuct cwk_bwanch tsif_wef_cwk = {
	.hawt_weg = 0x2fd4,
	.hawt_bit = 5,
	.cwkw = {
		.enabwe_weg = 0x2710,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "tsif_wef_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&tsif_wef_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch tsif_h_cwk = {
	.hwcg_weg = 0x2700,
	.hwcg_bit = 6,
	.hawt_weg = 0x2fd4,
	.hawt_bit = 7,
	.cwkw = {
		.enabwe_weg = 0x2700,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "tsif_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch dma_bam_h_cwk = {
	.hwcg_weg = 0x25c0,
	.hwcg_bit = 6,
	.hawt_weg = 0x2fc8,
	.hawt_bit = 12,
	.cwkw = {
		.enabwe_weg = 0x25c0,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "dma_bam_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch adm0_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hawt_bit = 12,
	.cwkw = {
		.enabwe_weg = 0x3080,
		.enabwe_mask = BIT(2),
		.hw.init = &(stwuct cwk_init_data){
			.name = "adm0_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch adm0_pbus_cwk = {
	.hwcg_weg = 0x2208,
	.hwcg_bit = 6,
	.hawt_weg = 0x2fdc,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hawt_bit = 11,
	.cwkw = {
		.enabwe_weg = 0x3080,
		.enabwe_mask = BIT(3),
		.hw.init = &(stwuct cwk_init_data){
			.name = "adm0_pbus_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch pmic_awb0_h_cwk = {
	.hawt_weg = 0x2fd8,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hawt_bit = 22,
	.cwkw = {
		.enabwe_weg = 0x3080,
		.enabwe_mask = BIT(8),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pmic_awb0_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch pmic_awb1_h_cwk = {
	.hawt_weg = 0x2fd8,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hawt_bit = 21,
	.cwkw = {
		.enabwe_weg = 0x3080,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pmic_awb1_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch pmic_ssbi2_cwk = {
	.hawt_weg = 0x2fd8,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hawt_bit = 23,
	.cwkw = {
		.enabwe_weg = 0x3080,
		.enabwe_mask = BIT(7),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pmic_ssbi2_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch wpm_msg_wam_h_cwk = {
	.hwcg_weg = 0x27e0,
	.hwcg_bit = 6,
	.hawt_weg = 0x2fd8,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hawt_bit = 12,
	.cwkw = {
		.enabwe_weg = 0x3080,
		.enabwe_mask = BIT(6),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wpm_msg_wam_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static const stwuct fweq_tbw cwk_tbw_pcie_wef[] = {
	{ 100000000, P_PWW3,  12, 0, 0 },
	{ }
};

static stwuct cwk_wcg pcie_wef_swc = {
	.ns_weg = 0x3860,
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 4,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww3_map,
	},
	.fweq_tbw = cwk_tbw_pcie_wef,
	.cwkw = {
		.enabwe_weg = 0x3860,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie_wef_swc",
			.pawent_data = gcc_pxo_pww3,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww3),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_WATE_GATE,
		},
	},
};

static stwuct cwk_bwanch pcie_wef_swc_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_bit = 30,
	.cwkw = {
		.enabwe_weg = 0x3860,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie_wef_swc_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&pcie_wef_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch pcie_a_cwk = {
	.hawt_weg = 0x2fc0,
	.hawt_bit = 13,
	.cwkw = {
		.enabwe_weg = 0x22c0,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie_a_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch pcie_aux_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_bit = 31,
	.cwkw = {
		.enabwe_weg = 0x22c8,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie_aux_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch pcie_h_cwk = {
	.hawt_weg = 0x2fd4,
	.hawt_bit = 8,
	.cwkw = {
		.enabwe_weg = 0x22cc,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch pcie_phy_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_bit = 29,
	.cwkw = {
		.enabwe_weg = 0x22d0,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie_phy_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_wcg pcie1_wef_swc = {
	.ns_weg = 0x3aa0,
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 4,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww3_map,
	},
	.fweq_tbw = cwk_tbw_pcie_wef,
	.cwkw = {
		.enabwe_weg = 0x3aa0,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie1_wef_swc",
			.pawent_data = gcc_pxo_pww3,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww3),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_WATE_GATE,
		},
	},
};

static stwuct cwk_bwanch pcie1_wef_swc_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_bit = 27,
	.cwkw = {
		.enabwe_weg = 0x3aa0,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie1_wef_swc_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&pcie1_wef_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch pcie1_a_cwk = {
	.hawt_weg = 0x2fc0,
	.hawt_bit = 10,
	.cwkw = {
		.enabwe_weg = 0x3a80,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie1_a_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch pcie1_aux_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_bit = 28,
	.cwkw = {
		.enabwe_weg = 0x3a88,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie1_aux_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch pcie1_h_cwk = {
	.hawt_weg = 0x2fd4,
	.hawt_bit = 9,
	.cwkw = {
		.enabwe_weg = 0x3a8c,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie1_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch pcie1_phy_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_bit = 26,
	.cwkw = {
		.enabwe_weg = 0x3a90,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie1_phy_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_wcg pcie2_wef_swc = {
	.ns_weg = 0x3ae0,
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 4,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww3_map,
	},
	.fweq_tbw = cwk_tbw_pcie_wef,
	.cwkw = {
		.enabwe_weg = 0x3ae0,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie2_wef_swc",
			.pawent_data = gcc_pxo_pww3,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww3),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_WATE_GATE,
		},
	},
};

static stwuct cwk_bwanch pcie2_wef_swc_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_bit = 24,
	.cwkw = {
		.enabwe_weg = 0x3ae0,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie2_wef_swc_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&pcie2_wef_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch pcie2_a_cwk = {
	.hawt_weg = 0x2fc0,
	.hawt_bit = 9,
	.cwkw = {
		.enabwe_weg = 0x3ac0,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie2_a_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch pcie2_aux_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_bit = 25,
	.cwkw = {
		.enabwe_weg = 0x3ac8,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie2_aux_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch pcie2_h_cwk = {
	.hawt_weg = 0x2fd4,
	.hawt_bit = 10,
	.cwkw = {
		.enabwe_weg = 0x3acc,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie2_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch pcie2_phy_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_bit = 23,
	.cwkw = {
		.enabwe_weg = 0x3ad0,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "pcie2_phy_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static const stwuct fweq_tbw cwk_tbw_sata_wef[] = {
	{ 100000000, P_PWW3,  12, 0, 0 },
	{ }
};

static stwuct cwk_wcg sata_wef_swc = {
	.ns_weg = 0x2c08,
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 4,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww3_sata_map,
	},
	.fweq_tbw = cwk_tbw_sata_wef,
	.cwkw = {
		.enabwe_weg = 0x2c08,
		.enabwe_mask = BIT(7),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sata_wef_swc",
			.pawent_data = gcc_pxo_pww3,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww3),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_WATE_GATE,
		},
	},
};

static stwuct cwk_bwanch sata_wxoob_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_bit = 20,
	.cwkw = {
		.enabwe_weg = 0x2c0c,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sata_wxoob_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&sata_wef_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch sata_pmawive_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_bit = 19,
	.cwkw = {
		.enabwe_weg = 0x2c10,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sata_pmawive_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&sata_wef_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch sata_phy_wef_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_bit = 18,
	.cwkw = {
		.enabwe_weg = 0x2c14,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sata_phy_wef_cwk",
			.pawent_data = gcc_pxo,
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch sata_a_cwk = {
	.hawt_weg = 0x2fc0,
	.hawt_bit = 12,
	.cwkw = {
		.enabwe_weg = 0x2c20,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sata_a_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch sata_h_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_bit = 21,
	.cwkw = {
		.enabwe_weg = 0x2c00,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sata_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch sfab_sata_s_h_cwk = {
	.hawt_weg = 0x2fc4,
	.hawt_bit = 14,
	.cwkw = {
		.enabwe_weg = 0x2480,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sfab_sata_s_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch sata_phy_cfg_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 14,
	.cwkw = {
		.enabwe_weg = 0x2c40,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sata_phy_cfg_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static const stwuct fweq_tbw cwk_tbw_usb30_mastew[] = {
	{ 125000000, P_PWW0,  1, 5, 32 },
	{ }
};

static stwuct cwk_wcg usb30_mastew_cwk_swc = {
	.ns_weg = 0x3b2c,
	.md_weg = 0x3b28,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww0_map,
	},
	.fweq_tbw = cwk_tbw_usb30_mastew,
	.cwkw = {
		.enabwe_weg = 0x3b2c,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb30_mastew_wef_swc",
			.pawent_data = gcc_pxo_pww8_pww0,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8_pww0),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_WATE_GATE,
		},
	},
};

static stwuct cwk_bwanch usb30_0_bwanch_cwk = {
	.hawt_weg = 0x2fc4,
	.hawt_bit = 22,
	.cwkw = {
		.enabwe_weg = 0x3b24,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb30_0_bwanch_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb30_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch usb30_1_bwanch_cwk = {
	.hawt_weg = 0x2fc4,
	.hawt_bit = 17,
	.cwkw = {
		.enabwe_weg = 0x3b34,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb30_1_bwanch_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb30_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static const stwuct fweq_tbw cwk_tbw_usb30_utmi[] = {
	{ 60000000, P_PWW8,  1, 5, 32 },
	{ }
};

static stwuct cwk_wcg usb30_utmi_cwk = {
	.ns_weg = 0x3b44,
	.md_weg = 0x3b40,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww0_map,
	},
	.fweq_tbw = cwk_tbw_usb30_utmi,
	.cwkw = {
		.enabwe_weg = 0x3b44,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb30_utmi_cwk",
			.pawent_data = gcc_pxo_pww8_pww0,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8_pww0),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_WATE_GATE,
		},
	},
};

static stwuct cwk_bwanch usb30_0_utmi_cwk_ctw = {
	.hawt_weg = 0x2fc4,
	.hawt_bit = 21,
	.cwkw = {
		.enabwe_weg = 0x3b48,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb30_0_utmi_cwk_ctw",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb30_utmi_cwk.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch usb30_1_utmi_cwk_ctw = {
	.hawt_weg = 0x2fc4,
	.hawt_bit = 15,
	.cwkw = {
		.enabwe_weg = 0x3b4c,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb30_1_utmi_cwk_ctw",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb30_utmi_cwk.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static const stwuct fweq_tbw cwk_tbw_usb[] = {
	{ 60000000, P_PWW8,  1, 5, 32 },
	{ }
};

static stwuct cwk_wcg usb_hs1_xcvw_cwk_swc = {
	.ns_weg = 0x290C,
	.md_weg = 0x2908,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww0_map,
	},
	.fweq_tbw = cwk_tbw_usb,
	.cwkw = {
		.enabwe_weg = 0x2968,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb_hs1_xcvw_swc",
			.pawent_data = gcc_pxo_pww8_pww0,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8_pww0),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_WATE_GATE,
		},
	},
};

static stwuct cwk_bwanch usb_hs1_xcvw_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 17,
	.cwkw = {
		.enabwe_weg = 0x290c,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb_hs1_xcvw_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb_hs1_xcvw_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch usb_hs1_h_cwk = {
	.hwcg_weg = 0x2900,
	.hwcg_bit = 6,
	.hawt_weg = 0x2fc8,
	.hawt_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x2900,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb_hs1_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_wcg usb_fs1_xcvw_cwk_swc = {
	.ns_weg = 0x2968,
	.md_weg = 0x2964,
	.mn = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.p = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.s = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww0_map,
	},
	.fweq_tbw = cwk_tbw_usb,
	.cwkw = {
		.enabwe_weg = 0x2968,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb_fs1_xcvw_swc",
			.pawent_data = gcc_pxo_pww8_pww0,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8_pww0),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_WATE_GATE,
		},
	},
};

static stwuct cwk_bwanch usb_fs1_xcvw_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 17,
	.cwkw = {
		.enabwe_weg = 0x2968,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb_fs1_xcvw_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb_fs1_xcvw_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch usb_fs1_sys_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 18,
	.cwkw = {
		.enabwe_weg = 0x296c,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb_fs1_sys_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb_fs1_xcvw_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch usb_fs1_h_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 19,
	.cwkw = {
		.enabwe_weg = 0x2960,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb_fs1_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch ebi2_cwk = {
	.hwcg_weg = 0x3b00,
	.hwcg_bit = 6,
	.hawt_weg = 0x2fcc,
	.hawt_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x3b00,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "ebi2_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch ebi2_aon_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 0,
	.cwkw = {
		.enabwe_weg = 0x3b00,
		.enabwe_mask = BIT(8),
		.hw.init = &(stwuct cwk_init_data){
			.name = "ebi2_awways_on_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static const stwuct fweq_tbw cwk_tbw_gmac[] = {
	{ 133000000, P_PWW0, 1,  50, 301 },
	{ 266000000, P_PWW0, 1, 127, 382 },
	{ }
};

static stwuct cwk_dyn_wcg gmac_cowe1_swc = {
	.ns_weg[0] = 0x3cac,
	.ns_weg[1] = 0x3cb0,
	.md_weg[0] = 0x3ca4,
	.md_weg[1] = 0x3ca8,
	.bank_weg = 0x3ca0,
	.mn[0] = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.mn[1] = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.s[0] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww14_pww18_pww0_map,
	},
	.s[1] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww14_pww18_pww0_map,
	},
	.p[0] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.p[1] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.mux_sew_bit = 0,
	.fweq_tbw = cwk_tbw_gmac,
	.cwkw = {
		.enabwe_weg = 0x3ca0,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gmac_cowe1_swc",
			.pawent_data = gcc_pxo_pww8_pww14_pww18_pww0,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8_pww14_pww18_pww0),
			.ops = &cwk_dyn_wcg_ops,
		},
	},
};

static stwuct cwk_bwanch gmac_cowe1_cwk = {
	.hawt_weg = 0x3c20,
	.hawt_bit = 4,
	.hwcg_weg = 0x3cb4,
	.hwcg_bit = 6,
	.cwkw = {
		.enabwe_weg = 0x3cb4,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gmac_cowe1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gmac_cowe1_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_dyn_wcg gmac_cowe2_swc = {
	.ns_weg[0] = 0x3ccc,
	.ns_weg[1] = 0x3cd0,
	.md_weg[0] = 0x3cc4,
	.md_weg[1] = 0x3cc8,
	.bank_weg = 0x3ca0,
	.mn[0] = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.mn[1] = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.s[0] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww14_pww18_pww0_map,
	},
	.s[1] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww14_pww18_pww0_map,
	},
	.p[0] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.p[1] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.mux_sew_bit = 0,
	.fweq_tbw = cwk_tbw_gmac,
	.cwkw = {
		.enabwe_weg = 0x3cc0,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gmac_cowe2_swc",
			.pawent_data = gcc_pxo_pww8_pww14_pww18_pww0,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8_pww14_pww18_pww0),
			.ops = &cwk_dyn_wcg_ops,
		},
	},
};

static stwuct cwk_bwanch gmac_cowe2_cwk = {
	.hawt_weg = 0x3c20,
	.hawt_bit = 5,
	.hwcg_weg = 0x3cd4,
	.hwcg_bit = 6,
	.cwkw = {
		.enabwe_weg = 0x3cd4,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gmac_cowe2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gmac_cowe2_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_dyn_wcg gmac_cowe3_swc = {
	.ns_weg[0] = 0x3cec,
	.ns_weg[1] = 0x3cf0,
	.md_weg[0] = 0x3ce4,
	.md_weg[1] = 0x3ce8,
	.bank_weg = 0x3ce0,
	.mn[0] = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.mn[1] = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.s[0] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww14_pww18_pww0_map,
	},
	.s[1] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww14_pww18_pww0_map,
	},
	.p[0] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.p[1] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.mux_sew_bit = 0,
	.fweq_tbw = cwk_tbw_gmac,
	.cwkw = {
		.enabwe_weg = 0x3ce0,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gmac_cowe3_swc",
			.pawent_data = gcc_pxo_pww8_pww14_pww18_pww0,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8_pww14_pww18_pww0),
			.ops = &cwk_dyn_wcg_ops,
		},
	},
};

static stwuct cwk_bwanch gmac_cowe3_cwk = {
	.hawt_weg = 0x3c20,
	.hawt_bit = 6,
	.hwcg_weg = 0x3cf4,
	.hwcg_bit = 6,
	.cwkw = {
		.enabwe_weg = 0x3cf4,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gmac_cowe3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gmac_cowe3_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_dyn_wcg gmac_cowe4_swc = {
	.ns_weg[0] = 0x3d0c,
	.ns_weg[1] = 0x3d10,
	.md_weg[0] = 0x3d04,
	.md_weg[1] = 0x3d08,
	.bank_weg = 0x3d00,
	.mn[0] = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.mn[1] = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.s[0] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww14_pww18_pww0_map,
	},
	.s[1] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww14_pww18_pww0_map,
	},
	.p[0] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.p[1] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.mux_sew_bit = 0,
	.fweq_tbw = cwk_tbw_gmac,
	.cwkw = {
		.enabwe_weg = 0x3d00,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gmac_cowe4_swc",
			.pawent_data = gcc_pxo_pww8_pww14_pww18_pww0,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8_pww14_pww18_pww0),
			.ops = &cwk_dyn_wcg_ops,
		},
	},
};

static stwuct cwk_bwanch gmac_cowe4_cwk = {
	.hawt_weg = 0x3c20,
	.hawt_bit = 7,
	.hwcg_weg = 0x3d14,
	.hwcg_bit = 6,
	.cwkw = {
		.enabwe_weg = 0x3d14,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gmac_cowe4_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gmac_cowe4_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static const stwuct fweq_tbw cwk_tbw_nss_tcm[] = {
	{ 266000000, P_PWW0, 3, 0, 0 },
	{ 400000000, P_PWW0, 2, 0, 0 },
	{ }
};

static stwuct cwk_dyn_wcg nss_tcm_swc = {
	.ns_weg[0] = 0x3dc4,
	.ns_weg[1] = 0x3dc8,
	.bank_weg = 0x3dc0,
	.s[0] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww14_pww18_pww0_map,
	},
	.s[1] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww14_pww18_pww0_map,
	},
	.p[0] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 4,
	},
	.p[1] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 4,
	},
	.mux_sew_bit = 0,
	.fweq_tbw = cwk_tbw_nss_tcm,
	.cwkw = {
		.enabwe_weg = 0x3dc0,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "nss_tcm_swc",
			.pawent_data = gcc_pxo_pww8_pww14_pww18_pww0,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8_pww14_pww18_pww0),
			.ops = &cwk_dyn_wcg_ops,
		},
	},
};

static stwuct cwk_bwanch nss_tcm_cwk = {
	.hawt_weg = 0x3c20,
	.hawt_bit = 14,
	.cwkw = {
		.enabwe_weg = 0x3dd0,
		.enabwe_mask = BIT(6) | BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "nss_tcm_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&nss_tcm_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static const stwuct fweq_tbw cwk_tbw_nss_ipq8064[] = {
	{ 110000000, P_PWW18, 1, 1, 5 },
	{ 275000000, P_PWW18, 2, 0, 0 },
	{ 550000000, P_PWW18, 1, 0, 0 },
	{ 733000000, P_PWW18, 1, 0, 0 },
	{ }
};

static const stwuct fweq_tbw cwk_tbw_nss_ipq8065[] = {
	{ 110000000, P_PWW18, 1, 1, 5 },
	{ 275000000, P_PWW18, 2, 0, 0 },
	{ 600000000, P_PWW18, 1, 0, 0 },
	{ 800000000, P_PWW18, 1, 0, 0 },
	{ }
};

static stwuct cwk_dyn_wcg ubi32_cowe1_swc_cwk = {
	.ns_weg[0] = 0x3d2c,
	.ns_weg[1] = 0x3d30,
	.md_weg[0] = 0x3d24,
	.md_weg[1] = 0x3d28,
	.bank_weg = 0x3d20,
	.mn[0] = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.mn[1] = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.s[0] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww14_pww18_pww0_map,
	},
	.s[1] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww14_pww18_pww0_map,
	},
	.p[0] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.p[1] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.mux_sew_bit = 0,
	/* nss fweq tabwe is sewected based on the SoC compatibwe */
	.cwkw = {
		.enabwe_weg = 0x3d20,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "ubi32_cowe1_swc_cwk",
			.pawent_data = gcc_pxo_pww8_pww14_pww18_pww0,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8_pww14_pww18_pww0),
			.ops = &cwk_dyn_wcg_ops,
			.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
		},
	},
};

static stwuct cwk_dyn_wcg ubi32_cowe2_swc_cwk = {
	.ns_weg[0] = 0x3d4c,
	.ns_weg[1] = 0x3d50,
	.md_weg[0] = 0x3d44,
	.md_weg[1] = 0x3d48,
	.bank_weg = 0x3d40,
	.mn[0] = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.mn[1] = {
		.mnctw_en_bit = 8,
		.mnctw_weset_bit = 7,
		.mnctw_mode_shift = 5,
		.n_vaw_shift = 16,
		.m_vaw_shift = 16,
		.width = 8,
	},
	.s[0] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww14_pww18_pww0_map,
	},
	.s[1] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww14_pww18_pww0_map,
	},
	.p[0] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.p[1] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 2,
	},
	.mux_sew_bit = 0,
	/* nss fweq tabwe is sewected based on the SoC compatibwe */
	.cwkw = {
		.enabwe_weg = 0x3d40,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "ubi32_cowe2_swc_cwk",
			.pawent_data = gcc_pxo_pww8_pww14_pww18_pww0,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8_pww14_pww18_pww0),
			.ops = &cwk_dyn_wcg_ops,
			.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
		},
	},
};

static const stwuct fweq_tbw cwk_tbw_ce5_cowe[] = {
	{ 150000000, P_PWW3, 8, 1, 1 },
	{ 213200000, P_PWW11, 5, 1, 1 },
	{ }
};

static stwuct cwk_dyn_wcg ce5_cowe_swc = {
	.ns_weg[0] = 0x36C4,
	.ns_weg[1] = 0x36C8,
	.bank_weg = 0x36C0,
	.s[0] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww3_pww0_pww14_pww18_pww11_map,
	},
	.s[1] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww3_pww0_pww14_pww18_pww11_map,
	},
	.p[0] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 4,
	},
	.p[1] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 4,
	},
	.mux_sew_bit = 0,
	.fweq_tbw = cwk_tbw_ce5_cowe,
	.cwkw = {
		.enabwe_weg = 0x36C0,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "ce5_cowe_swc",
			.pawent_data = gcc_pxo_pww3_pww0_pww14_pww18_pww11,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww3_pww0_pww14_pww18_pww11),
			.ops = &cwk_dyn_wcg_ops,
		},
	},
};

static stwuct cwk_bwanch ce5_cowe_cwk = {
	.hawt_weg = 0x2FDC,
	.hawt_bit = 5,
	.hwcg_weg = 0x36CC,
	.hwcg_bit = 6,
	.cwkw = {
		.enabwe_weg = 0x36CC,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "ce5_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&ce5_cowe_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static const stwuct fweq_tbw cwk_tbw_ce5_a_cwk[] = {
	{ 160000000, P_PWW0, 5, 1, 1 },
	{ 213200000, P_PWW11, 5, 1, 1 },
	{ }
};

static stwuct cwk_dyn_wcg ce5_a_cwk_swc = {
	.ns_weg[0] = 0x3d84,
	.ns_weg[1] = 0x3d88,
	.bank_weg = 0x3d80,
	.s[0] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww0_pww14_pww18_pww11_map,
	},
	.s[1] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww0_pww14_pww18_pww11_map,
	},
	.p[0] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 4,
	},
	.p[1] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 4,
	},
	.mux_sew_bit = 0,
	.fweq_tbw = cwk_tbw_ce5_a_cwk,
	.cwkw = {
		.enabwe_weg = 0x3d80,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "ce5_a_cwk_swc",
			.pawent_data = gcc_pxo_pww8_pww0_pww14_pww18_pww11,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8_pww0_pww14_pww18_pww11),
			.ops = &cwk_dyn_wcg_ops,
		},
	},
};

static stwuct cwk_bwanch ce5_a_cwk = {
	.hawt_weg = 0x3c20,
	.hawt_bit = 12,
	.hwcg_weg = 0x3d8c,
	.hwcg_bit = 6,
	.cwkw = {
		.enabwe_weg = 0x3d8c,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "ce5_a_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&ce5_a_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static const stwuct fweq_tbw cwk_tbw_ce5_h_cwk[] = {
	{ 160000000, P_PWW0, 5, 1, 1 },
	{ 213200000, P_PWW11, 5, 1, 1 },
	{ }
};

static stwuct cwk_dyn_wcg ce5_h_cwk_swc = {
	.ns_weg[0] = 0x3c64,
	.ns_weg[1] = 0x3c68,
	.bank_weg = 0x3c60,
	.s[0] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww0_pww14_pww18_pww11_map,
	},
	.s[1] = {
		.swc_sew_shift = 0,
		.pawent_map = gcc_pxo_pww8_pww0_pww14_pww18_pww11_map,
	},
	.p[0] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 4,
	},
	.p[1] = {
		.pwe_div_shift = 3,
		.pwe_div_width = 4,
	},
	.mux_sew_bit = 0,
	.fweq_tbw = cwk_tbw_ce5_h_cwk,
	.cwkw = {
		.enabwe_weg = 0x3c60,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "ce5_h_cwk_swc",
			.pawent_data = gcc_pxo_pww8_pww0_pww14_pww18_pww11,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8_pww0_pww14_pww18_pww11),
			.ops = &cwk_dyn_wcg_ops,
		},
	},
};

static stwuct cwk_bwanch ce5_h_cwk = {
	.hawt_weg = 0x3c20,
	.hawt_bit = 11,
	.hwcg_weg = 0x3c6c,
	.hwcg_bit = 6,
	.cwkw = {
		.enabwe_weg = 0x3c6c,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "ce5_h_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&ce5_h_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wegmap *gcc_ipq806x_cwks[] = {
	[PWW0] = &pww0.cwkw,
	[PWW0_VOTE] = &pww0_vote,
	[PWW3] = &pww3.cwkw,
	[PWW4_VOTE] = &pww4_vote,
	[PWW8] = &pww8.cwkw,
	[PWW8_VOTE] = &pww8_vote,
	[PWW11] = &pww11.cwkw,
	[PWW14] = &pww14.cwkw,
	[PWW14_VOTE] = &pww14_vote,
	[PWW18] = &pww18.cwkw,
	[GSBI1_UAWT_SWC] = &gsbi1_uawt_swc.cwkw,
	[GSBI1_UAWT_CWK] = &gsbi1_uawt_cwk.cwkw,
	[GSBI2_UAWT_SWC] = &gsbi2_uawt_swc.cwkw,
	[GSBI2_UAWT_CWK] = &gsbi2_uawt_cwk.cwkw,
	[GSBI4_UAWT_SWC] = &gsbi4_uawt_swc.cwkw,
	[GSBI4_UAWT_CWK] = &gsbi4_uawt_cwk.cwkw,
	[GSBI5_UAWT_SWC] = &gsbi5_uawt_swc.cwkw,
	[GSBI5_UAWT_CWK] = &gsbi5_uawt_cwk.cwkw,
	[GSBI6_UAWT_SWC] = &gsbi6_uawt_swc.cwkw,
	[GSBI6_UAWT_CWK] = &gsbi6_uawt_cwk.cwkw,
	[GSBI7_UAWT_SWC] = &gsbi7_uawt_swc.cwkw,
	[GSBI7_UAWT_CWK] = &gsbi7_uawt_cwk.cwkw,
	[GSBI1_QUP_SWC] = &gsbi1_qup_swc.cwkw,
	[GSBI1_QUP_CWK] = &gsbi1_qup_cwk.cwkw,
	[GSBI2_QUP_SWC] = &gsbi2_qup_swc.cwkw,
	[GSBI2_QUP_CWK] = &gsbi2_qup_cwk.cwkw,
	[GSBI4_QUP_SWC] = &gsbi4_qup_swc.cwkw,
	[GSBI4_QUP_CWK] = &gsbi4_qup_cwk.cwkw,
	[GSBI5_QUP_SWC] = &gsbi5_qup_swc.cwkw,
	[GSBI5_QUP_CWK] = &gsbi5_qup_cwk.cwkw,
	[GSBI6_QUP_SWC] = &gsbi6_qup_swc.cwkw,
	[GSBI6_QUP_CWK] = &gsbi6_qup_cwk.cwkw,
	[GSBI7_QUP_SWC] = &gsbi7_qup_swc.cwkw,
	[GSBI7_QUP_CWK] = &gsbi7_qup_cwk.cwkw,
	[GP0_SWC] = &gp0_swc.cwkw,
	[GP0_CWK] = &gp0_cwk.cwkw,
	[GP1_SWC] = &gp1_swc.cwkw,
	[GP1_CWK] = &gp1_cwk.cwkw,
	[GP2_SWC] = &gp2_swc.cwkw,
	[GP2_CWK] = &gp2_cwk.cwkw,
	[PMEM_A_CWK] = &pmem_cwk.cwkw,
	[PWNG_SWC] = &pwng_swc.cwkw,
	[PWNG_CWK] = &pwng_cwk.cwkw,
	[SDC1_SWC] = &sdc1_swc.cwkw,
	[SDC1_CWK] = &sdc1_cwk.cwkw,
	[SDC3_SWC] = &sdc3_swc.cwkw,
	[SDC3_CWK] = &sdc3_cwk.cwkw,
	[TSIF_WEF_SWC] = &tsif_wef_swc.cwkw,
	[TSIF_WEF_CWK] = &tsif_wef_cwk.cwkw,
	[DMA_BAM_H_CWK] = &dma_bam_h_cwk.cwkw,
	[GSBI1_H_CWK] = &gsbi1_h_cwk.cwkw,
	[GSBI2_H_CWK] = &gsbi2_h_cwk.cwkw,
	[GSBI4_H_CWK] = &gsbi4_h_cwk.cwkw,
	[GSBI5_H_CWK] = &gsbi5_h_cwk.cwkw,
	[GSBI6_H_CWK] = &gsbi6_h_cwk.cwkw,
	[GSBI7_H_CWK] = &gsbi7_h_cwk.cwkw,
	[TSIF_H_CWK] = &tsif_h_cwk.cwkw,
	[SDC1_H_CWK] = &sdc1_h_cwk.cwkw,
	[SDC3_H_CWK] = &sdc3_h_cwk.cwkw,
	[ADM0_CWK] = &adm0_cwk.cwkw,
	[ADM0_PBUS_CWK] = &adm0_pbus_cwk.cwkw,
	[PCIE_A_CWK] = &pcie_a_cwk.cwkw,
	[PCIE_AUX_CWK] = &pcie_aux_cwk.cwkw,
	[PCIE_H_CWK] = &pcie_h_cwk.cwkw,
	[PCIE_PHY_CWK] = &pcie_phy_cwk.cwkw,
	[SFAB_SATA_S_H_CWK] = &sfab_sata_s_h_cwk.cwkw,
	[PMIC_AWB0_H_CWK] = &pmic_awb0_h_cwk.cwkw,
	[PMIC_AWB1_H_CWK] = &pmic_awb1_h_cwk.cwkw,
	[PMIC_SSBI2_CWK] = &pmic_ssbi2_cwk.cwkw,
	[WPM_MSG_WAM_H_CWK] = &wpm_msg_wam_h_cwk.cwkw,
	[SATA_H_CWK] = &sata_h_cwk.cwkw,
	[SATA_CWK_SWC] = &sata_wef_swc.cwkw,
	[SATA_WXOOB_CWK] = &sata_wxoob_cwk.cwkw,
	[SATA_PMAWIVE_CWK] = &sata_pmawive_cwk.cwkw,
	[SATA_PHY_WEF_CWK] = &sata_phy_wef_cwk.cwkw,
	[SATA_A_CWK] = &sata_a_cwk.cwkw,
	[SATA_PHY_CFG_CWK] = &sata_phy_cfg_cwk.cwkw,
	[PCIE_AWT_WEF_SWC] = &pcie_wef_swc.cwkw,
	[PCIE_AWT_WEF_CWK] = &pcie_wef_swc_cwk.cwkw,
	[PCIE_1_A_CWK] = &pcie1_a_cwk.cwkw,
	[PCIE_1_AUX_CWK] = &pcie1_aux_cwk.cwkw,
	[PCIE_1_H_CWK] = &pcie1_h_cwk.cwkw,
	[PCIE_1_PHY_CWK] = &pcie1_phy_cwk.cwkw,
	[PCIE_1_AWT_WEF_SWC] = &pcie1_wef_swc.cwkw,
	[PCIE_1_AWT_WEF_CWK] = &pcie1_wef_swc_cwk.cwkw,
	[PCIE_2_A_CWK] = &pcie2_a_cwk.cwkw,
	[PCIE_2_AUX_CWK] = &pcie2_aux_cwk.cwkw,
	[PCIE_2_H_CWK] = &pcie2_h_cwk.cwkw,
	[PCIE_2_PHY_CWK] = &pcie2_phy_cwk.cwkw,
	[PCIE_2_AWT_WEF_SWC] = &pcie2_wef_swc.cwkw,
	[PCIE_2_AWT_WEF_CWK] = &pcie2_wef_swc_cwk.cwkw,
	[USB30_MASTEW_SWC] = &usb30_mastew_cwk_swc.cwkw,
	[USB30_0_MASTEW_CWK] = &usb30_0_bwanch_cwk.cwkw,
	[USB30_1_MASTEW_CWK] = &usb30_1_bwanch_cwk.cwkw,
	[USB30_UTMI_SWC] = &usb30_utmi_cwk.cwkw,
	[USB30_0_UTMI_CWK] = &usb30_0_utmi_cwk_ctw.cwkw,
	[USB30_1_UTMI_CWK] = &usb30_1_utmi_cwk_ctw.cwkw,
	[USB_HS1_H_CWK] = &usb_hs1_h_cwk.cwkw,
	[USB_HS1_XCVW_SWC] = &usb_hs1_xcvw_cwk_swc.cwkw,
	[USB_HS1_XCVW_CWK] = &usb_hs1_xcvw_cwk.cwkw,
	[USB_FS1_H_CWK] = &usb_fs1_h_cwk.cwkw,
	[USB_FS1_XCVW_SWC] = &usb_fs1_xcvw_cwk_swc.cwkw,
	[USB_FS1_XCVW_CWK] = &usb_fs1_xcvw_cwk.cwkw,
	[USB_FS1_SYSTEM_CWK] = &usb_fs1_sys_cwk.cwkw,
	[EBI2_CWK] = &ebi2_cwk.cwkw,
	[EBI2_AON_CWK] = &ebi2_aon_cwk.cwkw,
	[GMAC_COWE1_CWK_SWC] = &gmac_cowe1_swc.cwkw,
	[GMAC_COWE1_CWK] = &gmac_cowe1_cwk.cwkw,
	[GMAC_COWE2_CWK_SWC] = &gmac_cowe2_swc.cwkw,
	[GMAC_COWE2_CWK] = &gmac_cowe2_cwk.cwkw,
	[GMAC_COWE3_CWK_SWC] = &gmac_cowe3_swc.cwkw,
	[GMAC_COWE3_CWK] = &gmac_cowe3_cwk.cwkw,
	[GMAC_COWE4_CWK_SWC] = &gmac_cowe4_swc.cwkw,
	[GMAC_COWE4_CWK] = &gmac_cowe4_cwk.cwkw,
	[UBI32_COWE1_CWK_SWC] = &ubi32_cowe1_swc_cwk.cwkw,
	[UBI32_COWE2_CWK_SWC] = &ubi32_cowe2_swc_cwk.cwkw,
	[NSSTCM_CWK_SWC] = &nss_tcm_swc.cwkw,
	[NSSTCM_CWK] = &nss_tcm_cwk.cwkw,
	[PWW9] = &hfpww0.cwkw,
	[PWW10] = &hfpww1.cwkw,
	[PWW12] = &hfpww_w2.cwkw,
	[CE5_A_CWK_SWC] = &ce5_a_cwk_swc.cwkw,
	[CE5_A_CWK] = &ce5_a_cwk.cwkw,
	[CE5_H_CWK_SWC] = &ce5_h_cwk_swc.cwkw,
	[CE5_H_CWK] = &ce5_h_cwk.cwkw,
	[CE5_COWE_CWK_SWC] = &ce5_cowe_swc.cwkw,
	[CE5_COWE_CWK] = &ce5_cowe_cwk.cwkw,
};

static const stwuct qcom_weset_map gcc_ipq806x_wesets[] = {
	[QDSS_STM_WESET] = { 0x2060, 6 },
	[AFAB_SMPSS_S_WESET] = { 0x20b8, 2 },
	[AFAB_SMPSS_M1_WESET] = { 0x20b8, 1 },
	[AFAB_SMPSS_M0_WESET] = { 0x20b8, 0 },
	[AFAB_EBI1_CH0_WESET] = { 0x20c0, 7 },
	[AFAB_EBI1_CH1_WESET] = { 0x20c4, 7 },
	[SFAB_ADM0_M0_WESET] = { 0x21e0, 7 },
	[SFAB_ADM0_M1_WESET] = { 0x21e4, 7 },
	[SFAB_ADM0_M2_WESET] = { 0x21e8, 7 },
	[ADM0_C2_WESET] = { 0x220c, 4 },
	[ADM0_C1_WESET] = { 0x220c, 3 },
	[ADM0_C0_WESET] = { 0x220c, 2 },
	[ADM0_PBUS_WESET] = { 0x220c, 1 },
	[ADM0_WESET] = { 0x220c, 0 },
	[QDSS_CWKS_SW_WESET] = { 0x2260, 5 },
	[QDSS_POW_WESET] = { 0x2260, 4 },
	[QDSS_TSCTW_WESET] = { 0x2260, 3 },
	[QDSS_HWESET_WESET] = { 0x2260, 2 },
	[QDSS_AXI_WESET] = { 0x2260, 1 },
	[QDSS_DBG_WESET] = { 0x2260, 0 },
	[SFAB_PCIE_M_WESET] = { 0x22d8, 1 },
	[SFAB_PCIE_S_WESET] = { 0x22d8, 0 },
	[PCIE_EXT_WESET] = { 0x22dc, 6 },
	[PCIE_PHY_WESET] = { 0x22dc, 5 },
	[PCIE_PCI_WESET] = { 0x22dc, 4 },
	[PCIE_POW_WESET] = { 0x22dc, 3 },
	[PCIE_HCWK_WESET] = { 0x22dc, 2 },
	[PCIE_ACWK_WESET] = { 0x22dc, 0 },
	[SFAB_WPASS_WESET] = { 0x23a0, 7 },
	[SFAB_AFAB_M_WESET] = { 0x23e0, 7 },
	[AFAB_SFAB_M0_WESET] = { 0x2420, 7 },
	[AFAB_SFAB_M1_WESET] = { 0x2424, 7 },
	[SFAB_SATA_S_WESET] = { 0x2480, 7 },
	[SFAB_DFAB_M_WESET] = { 0x2500, 7 },
	[DFAB_SFAB_M_WESET] = { 0x2520, 7 },
	[DFAB_SWAY0_WESET] = { 0x2540, 7 },
	[DFAB_SWAY1_WESET] = { 0x2544, 7 },
	[DFAB_AWB0_WESET] = { 0x2560, 7 },
	[DFAB_AWB1_WESET] = { 0x2564, 7 },
	[PPSS_PWOC_WESET] = { 0x2594, 1 },
	[PPSS_WESET] = { 0x2594, 0 },
	[DMA_BAM_WESET] = { 0x25c0, 7 },
	[SPS_TIC_H_WESET] = { 0x2600, 7 },
	[SFAB_CFPB_M_WESET] = { 0x2680, 7 },
	[SFAB_CFPB_S_WESET] = { 0x26c0, 7 },
	[TSIF_H_WESET] = { 0x2700, 7 },
	[CE1_H_WESET] = { 0x2720, 7 },
	[CE1_COWE_WESET] = { 0x2724, 7 },
	[CE1_SWEEP_WESET] = { 0x2728, 7 },
	[CE2_H_WESET] = { 0x2740, 7 },
	[CE2_COWE_WESET] = { 0x2744, 7 },
	[SFAB_SFPB_M_WESET] = { 0x2780, 7 },
	[SFAB_SFPB_S_WESET] = { 0x27a0, 7 },
	[WPM_PWOC_WESET] = { 0x27c0, 7 },
	[PMIC_SSBI2_WESET] = { 0x280c, 12 },
	[SDC1_WESET] = { 0x2830, 0 },
	[SDC2_WESET] = { 0x2850, 0 },
	[SDC3_WESET] = { 0x2870, 0 },
	[SDC4_WESET] = { 0x2890, 0 },
	[USB_HS1_WESET] = { 0x2910, 0 },
	[USB_HSIC_WESET] = { 0x2934, 0 },
	[USB_FS1_XCVW_WESET] = { 0x2974, 1 },
	[USB_FS1_WESET] = { 0x2974, 0 },
	[GSBI1_WESET] = { 0x29dc, 0 },
	[GSBI2_WESET] = { 0x29fc, 0 },
	[GSBI3_WESET] = { 0x2a1c, 0 },
	[GSBI4_WESET] = { 0x2a3c, 0 },
	[GSBI5_WESET] = { 0x2a5c, 0 },
	[GSBI6_WESET] = { 0x2a7c, 0 },
	[GSBI7_WESET] = { 0x2a9c, 0 },
	[SPDM_WESET] = { 0x2b6c, 0 },
	[SEC_CTWW_WESET] = { 0x2b80, 7 },
	[TWMM_H_WESET] = { 0x2ba0, 7 },
	[SFAB_SATA_M_WESET] = { 0x2c18, 0 },
	[SATA_WESET] = { 0x2c1c, 0 },
	[TSSC_WESET] = { 0x2ca0, 7 },
	[PDM_WESET] = { 0x2cc0, 12 },
	[MPM_H_WESET] = { 0x2da0, 7 },
	[MPM_WESET] = { 0x2da4, 0 },
	[SFAB_SMPSS_S_WESET] = { 0x2e00, 7 },
	[PWNG_WESET] = { 0x2e80, 12 },
	[SFAB_CE3_M_WESET] = { 0x36c8, 1 },
	[SFAB_CE3_S_WESET] = { 0x36c8, 0 },
	[CE3_SWEEP_WESET] = { 0x36d0, 7 },
	[PCIE_1_M_WESET] = { 0x3a98, 1 },
	[PCIE_1_S_WESET] = { 0x3a98, 0 },
	[PCIE_1_EXT_WESET] = { 0x3a9c, 6 },
	[PCIE_1_PHY_WESET] = { 0x3a9c, 5 },
	[PCIE_1_PCI_WESET] = { 0x3a9c, 4 },
	[PCIE_1_POW_WESET] = { 0x3a9c, 3 },
	[PCIE_1_HCWK_WESET] = { 0x3a9c, 2 },
	[PCIE_1_ACWK_WESET] = { 0x3a9c, 0 },
	[PCIE_2_M_WESET] = { 0x3ad8, 1 },
	[PCIE_2_S_WESET] = { 0x3ad8, 0 },
	[PCIE_2_EXT_WESET] = { 0x3adc, 6 },
	[PCIE_2_PHY_WESET] = { 0x3adc, 5 },
	[PCIE_2_PCI_WESET] = { 0x3adc, 4 },
	[PCIE_2_POW_WESET] = { 0x3adc, 3 },
	[PCIE_2_HCWK_WESET] = { 0x3adc, 2 },
	[PCIE_2_ACWK_WESET] = { 0x3adc, 0 },
	[SFAB_USB30_S_WESET] = { 0x3b54, 1 },
	[SFAB_USB30_M_WESET] = { 0x3b54, 0 },
	[USB30_0_POWT2_HS_PHY_WESET] = { 0x3b50, 5 },
	[USB30_0_MASTEW_WESET] = { 0x3b50, 4 },
	[USB30_0_SWEEP_WESET] = { 0x3b50, 3 },
	[USB30_0_UTMI_PHY_WESET] = { 0x3b50, 2 },
	[USB30_0_POWEWON_WESET] = { 0x3b50, 1 },
	[USB30_0_PHY_WESET] = { 0x3b50, 0 },
	[USB30_1_MASTEW_WESET] = { 0x3b58, 4 },
	[USB30_1_SWEEP_WESET] = { 0x3b58, 3 },
	[USB30_1_UTMI_PHY_WESET] = { 0x3b58, 2 },
	[USB30_1_POWEWON_WESET] = { 0x3b58, 1 },
	[USB30_1_PHY_WESET] = { 0x3b58, 0 },
	[NSSFB0_WESET] = { 0x3b60, 6 },
	[NSSFB1_WESET] = { 0x3b60, 7 },
	[UBI32_COWE1_CWKWST_CWAMP_WESET] = { 0x3d3c, 3},
	[UBI32_COWE1_CWAMP_WESET] = { 0x3d3c, 2 },
	[UBI32_COWE1_AHB_WESET] = { 0x3d3c, 1 },
	[UBI32_COWE1_AXI_WESET] = { 0x3d3c, 0 },
	[UBI32_COWE2_CWKWST_CWAMP_WESET] = { 0x3d5c, 3 },
	[UBI32_COWE2_CWAMP_WESET] = { 0x3d5c, 2 },
	[UBI32_COWE2_AHB_WESET] = { 0x3d5c, 1 },
	[UBI32_COWE2_AXI_WESET] = { 0x3d5c, 0 },
	[GMAC_COWE1_WESET] = { 0x3cbc, 0 },
	[GMAC_COWE2_WESET] = { 0x3cdc, 0 },
	[GMAC_COWE3_WESET] = { 0x3cfc, 0 },
	[GMAC_COWE4_WESET] = { 0x3d1c, 0 },
	[GMAC_AHB_WESET] = { 0x3e24, 0 },
	[CWYPTO_ENG1_WESET] = { 0x3e00, 0},
	[CWYPTO_ENG2_WESET] = { 0x3e04, 0},
	[CWYPTO_ENG3_WESET] = { 0x3e08, 0},
	[CWYPTO_ENG4_WESET] = { 0x3e0c, 0},
	[CWYPTO_AHB_WESET] = { 0x3e10, 0},
	[NSS_CH0_WST_WX_CWK_N_WESET] = { 0x3b60, 0 },
	[NSS_CH0_WST_TX_CWK_N_WESET] = { 0x3b60, 1 },
	[NSS_CH0_WST_WX_125M_N_WESET] = { 0x3b60, 2 },
	[NSS_CH0_HW_WST_WX_125M_N_WESET] = { 0x3b60, 3 },
	[NSS_CH0_WST_TX_125M_N_WESET] = { 0x3b60, 4 },
	[NSS_CH1_WST_WX_CWK_N_WESET] = { 0x3b60, 5 },
	[NSS_CH1_WST_TX_CWK_N_WESET] = { 0x3b60, 6 },
	[NSS_CH1_WST_WX_125M_N_WESET] = { 0x3b60, 7 },
	[NSS_CH1_HW_WST_WX_125M_N_WESET] = { 0x3b60, 8 },
	[NSS_CH1_WST_TX_125M_N_WESET] = { 0x3b60, 9 },
	[NSS_CH2_WST_WX_CWK_N_WESET] = { 0x3b60, 10 },
	[NSS_CH2_WST_TX_CWK_N_WESET] = { 0x3b60, 11 },
	[NSS_CH2_WST_WX_125M_N_WESET] = { 0x3b60, 12 },
	[NSS_CH2_HW_WST_WX_125M_N_WESET] = { 0x3b60, 13 },
	[NSS_CH2_WST_TX_125M_N_WESET] = { 0x3b60, 14 },
	[NSS_CH3_WST_WX_CWK_N_WESET] = { 0x3b60, 15 },
	[NSS_CH3_WST_TX_CWK_N_WESET] = { 0x3b60, 16 },
	[NSS_CH3_WST_WX_125M_N_WESET] = { 0x3b60, 17 },
	[NSS_CH3_HW_WST_WX_125M_N_WESET] = { 0x3b60, 18 },
	[NSS_CH3_WST_TX_125M_N_WESET] = { 0x3b60, 19 },
	[NSS_WST_WX_250M_125M_N_WESET] = { 0x3b60, 20 },
	[NSS_WST_TX_250M_125M_N_WESET] = { 0x3b60, 21 },
	[NSS_QSGMII_TXPI_WST_N_WESET] = { 0x3b60, 22 },
	[NSS_QSGMII_CDW_WST_N_WESET] = { 0x3b60, 23 },
	[NSS_SGMII2_CDW_WST_N_WESET] = { 0x3b60, 24 },
	[NSS_SGMII3_CDW_WST_N_WESET] = { 0x3b60, 25 },
	[NSS_CAW_PWBS_WST_N_WESET] = { 0x3b60, 26 },
	[NSS_WCKDT_WST_N_WESET] = { 0x3b60, 27 },
	[NSS_SWDS_N_WESET] = { 0x3b60, 28 },
};

static const stwuct wegmap_config gcc_ipq806x_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x3e40,
	.fast_io	= twue,
};

static const stwuct qcom_cc_desc gcc_ipq806x_desc = {
	.config = &gcc_ipq806x_wegmap_config,
	.cwks = gcc_ipq806x_cwks,
	.num_cwks = AWWAY_SIZE(gcc_ipq806x_cwks),
	.wesets = gcc_ipq806x_wesets,
	.num_wesets = AWWAY_SIZE(gcc_ipq806x_wesets),
};

static const stwuct of_device_id gcc_ipq806x_match_tabwe[] = {
	{ .compatibwe = "qcom,gcc-ipq8064" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gcc_ipq806x_match_tabwe);

static int gcc_ipq806x_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wegmap *wegmap;
	int wet;

	wet = qcom_cc_wegistew_boawd_cwk(dev, "cxo_boawd", "cxo", 25000000);
	if (wet)
		wetuwn wet;

	wet = qcom_cc_wegistew_boawd_cwk(dev, "pxo_boawd", "pxo", 25000000);
	if (wet)
		wetuwn wet;

	if (of_machine_is_compatibwe("qcom,ipq8065")) {
		ubi32_cowe1_swc_cwk.fweq_tbw = cwk_tbw_nss_ipq8065;
		ubi32_cowe2_swc_cwk.fweq_tbw = cwk_tbw_nss_ipq8065;
	} ewse {
		ubi32_cowe1_swc_cwk.fweq_tbw = cwk_tbw_nss_ipq8064;
		ubi32_cowe2_swc_cwk.fweq_tbw = cwk_tbw_nss_ipq8064;
	}

	wet = qcom_cc_pwobe(pdev, &gcc_ipq806x_desc);
	if (wet)
		wetuwn wet;

	wegmap = dev_get_wegmap(dev, NUWW);
	if (!wegmap)
		wetuwn -ENODEV;

	/* Setup PWW18 static bits */
	wegmap_update_bits(wegmap, 0x31a4, 0xffffffc0, 0x40000400);
	wegmap_wwite(wegmap, 0x31b0, 0x3080);

	/* Set GMAC footswitch sweep/wakeup vawues */
	wegmap_wwite(wegmap, 0x3cb8, 8);
	wegmap_wwite(wegmap, 0x3cd8, 8);
	wegmap_wwite(wegmap, 0x3cf8, 8);
	wegmap_wwite(wegmap, 0x3d18, 8);

	wetuwn of_pwatfowm_popuwate(pdev->dev.of_node, NUWW, NUWW, &pdev->dev);
}

static stwuct pwatfowm_dwivew gcc_ipq806x_dwivew = {
	.pwobe		= gcc_ipq806x_pwobe,
	.dwivew		= {
		.name	= "gcc-ipq806x",
		.of_match_tabwe = gcc_ipq806x_match_tabwe,
	},
};

static int __init gcc_ipq806x_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gcc_ipq806x_dwivew);
}
cowe_initcaww(gcc_ipq806x_init);

static void __exit gcc_ipq806x_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gcc_ipq806x_dwivew);
}
moduwe_exit(gcc_ipq806x_exit);

MODUWE_DESCWIPTION("QCOM GCC IPQ806x Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:gcc-ipq806x");
