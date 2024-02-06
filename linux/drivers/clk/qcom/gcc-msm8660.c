// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>

#incwude <dt-bindings/cwock/qcom,gcc-msm8660.h>
#incwude <dt-bindings/weset/qcom,gcc-msm8660.h>

#incwude "common.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-pww.h"
#incwude "cwk-wcg.h"
#incwude "cwk-bwanch.h"
#incwude "weset.h"

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
		.pawent_data = &(const stwuct cwk_pawent_data){
			.fw_name = "pxo", .name = "pxo_boawd",
		},
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
			&pww8.cwkw.hw
		},
		.num_pawents = 1,
		.ops = &cwk_pww_vote_ops,
	},
};

enum {
	P_PXO,
	P_PWW8,
	P_CXO,
};

static const stwuct pawent_map gcc_pxo_pww8_map[] = {
	{ P_PXO, 0 },
	{ P_PWW8, 3 }
};

static const stwuct cwk_pawent_data gcc_pxo_pww8[] = {
	{ .fw_name = "pxo", .name = "pxo_boawd" },
	{ .hw = &pww8_vote.hw },
};

static const stwuct pawent_map gcc_pxo_pww8_cxo_map[] = {
	{ P_PXO, 0 },
	{ P_PWW8, 3 },
	{ P_CXO, 5 }
};

static const stwuct cwk_pawent_data gcc_pxo_pww8_cxo[] = {
	{ .fw_name = "pxo", .name = "pxo_boawd" },
	{ .hw = &pww8_vote.hw },
	{ .fw_name = "cxo", .name = "cxo_boawd" },
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
	.hawt_bit = 10,
	.cwkw = {
		.enabwe_weg = 0x29d4,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi1_uawt_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi1_uawt_swc.cwkw.hw
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
	.hawt_bit = 6,
	.cwkw = {
		.enabwe_weg = 0x29f4,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi2_uawt_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi2_uawt_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi3_uawt_swc = {
	.ns_weg = 0x2a14,
	.md_weg = 0x2a10,
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
		.enabwe_weg = 0x2a14,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi3_uawt_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi3_uawt_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 2,
	.cwkw = {
		.enabwe_weg = 0x2a14,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi3_uawt_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi3_uawt_swc.cwkw.hw
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
				&gsbi4_uawt_swc.cwkw.hw
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
				&gsbi5_uawt_swc.cwkw.hw
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
				&gsbi6_uawt_swc.cwkw.hw
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
				&gsbi7_uawt_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi8_uawt_swc = {
	.ns_weg = 0x2ab4,
	.md_weg = 0x2ab0,
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
		.enabwe_weg = 0x2ab4,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi8_uawt_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi8_uawt_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 10,
	.cwkw = {
		.enabwe_weg = 0x2ab4,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi8_uawt_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi8_uawt_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi9_uawt_swc = {
	.ns_weg = 0x2ad4,
	.md_weg = 0x2ad0,
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
		.enabwe_weg = 0x2ad4,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi9_uawt_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi9_uawt_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 6,
	.cwkw = {
		.enabwe_weg = 0x2ad4,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi9_uawt_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi9_uawt_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi10_uawt_swc = {
	.ns_weg = 0x2af4,
	.md_weg = 0x2af0,
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
		.enabwe_weg = 0x2af4,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi10_uawt_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi10_uawt_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 2,
	.cwkw = {
		.enabwe_weg = 0x2af4,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi10_uawt_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi10_uawt_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi11_uawt_swc = {
	.ns_weg = 0x2b14,
	.md_weg = 0x2b10,
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
		.enabwe_weg = 0x2b14,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi11_uawt_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi11_uawt_cwk = {
	.hawt_weg = 0x2fd4,
	.hawt_bit = 17,
	.cwkw = {
		.enabwe_weg = 0x2b14,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi11_uawt_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi11_uawt_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi12_uawt_swc = {
	.ns_weg = 0x2b34,
	.md_weg = 0x2b30,
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
		.enabwe_weg = 0x2b34,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi12_uawt_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi12_uawt_cwk = {
	.hawt_weg = 0x2fd4,
	.hawt_bit = 13,
	.cwkw = {
		.enabwe_weg = 0x2b34,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi12_uawt_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi12_uawt_swc.cwkw.hw
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
	{ 25600000, P_PWW8, 1, 1, 15 },
	{ 27000000, P_PXO,  1, 0,  0 },
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
	.hawt_bit = 9,
	.cwkw = {
		.enabwe_weg = 0x29cc,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi1_qup_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi1_qup_swc.cwkw.hw
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
	.hawt_bit = 4,
	.cwkw = {
		.enabwe_weg = 0x29ec,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi2_qup_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi2_qup_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi3_qup_swc = {
	.ns_weg = 0x2a0c,
	.md_weg = 0x2a08,
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
		.enabwe_weg = 0x2a0c,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi3_qup_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi3_qup_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 0,
	.cwkw = {
		.enabwe_weg = 0x2a0c,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi3_qup_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi3_qup_swc.cwkw.hw
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
			.fwags = CWK_SET_PAWENT_GATE,
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
				&gsbi4_qup_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
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
				&gsbi5_qup_swc.cwkw.hw
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
			.fwags = CWK_SET_PAWENT_GATE,
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
				&gsbi6_qup_swc.cwkw.hw
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
				&gsbi7_qup_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi8_qup_swc = {
	.ns_weg = 0x2aac,
	.md_weg = 0x2aa8,
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
		.enabwe_weg = 0x2aac,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi8_qup_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi8_qup_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 8,
	.cwkw = {
		.enabwe_weg = 0x2aac,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi8_qup_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi8_qup_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi9_qup_swc = {
	.ns_weg = 0x2acc,
	.md_weg = 0x2ac8,
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
		.enabwe_weg = 0x2acc,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi9_qup_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi9_qup_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 4,
	.cwkw = {
		.enabwe_weg = 0x2acc,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi9_qup_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi9_qup_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi10_qup_swc = {
	.ns_weg = 0x2aec,
	.md_weg = 0x2ae8,
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
		.enabwe_weg = 0x2aec,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi10_qup_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi10_qup_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 0,
	.cwkw = {
		.enabwe_weg = 0x2aec,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi10_qup_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi10_qup_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi11_qup_swc = {
	.ns_weg = 0x2b0c,
	.md_weg = 0x2b08,
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
		.enabwe_weg = 0x2b0c,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi11_qup_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi11_qup_cwk = {
	.hawt_weg = 0x2fd4,
	.hawt_bit = 15,
	.cwkw = {
		.enabwe_weg = 0x2b0c,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi11_qup_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi11_qup_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg gsbi12_qup_swc = {
	.ns_weg = 0x2b2c,
	.md_weg = 0x2b28,
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
		.enabwe_weg = 0x2b2c,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi12_qup_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_PAWENT_GATE,
		},
	},
};

static stwuct cwk_bwanch gsbi12_qup_cwk = {
	.hawt_weg = 0x2fd4,
	.hawt_bit = 11,
	.cwkw = {
		.enabwe_weg = 0x2b2c,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi12_qup_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gsbi12_qup_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static const stwuct fweq_tbw cwk_tbw_gp[] = {
	{ 9600000, P_CXO,  2, 0, 0 },
	{ 13500000, P_PXO,  2, 0, 0 },
	{ 19200000, P_CXO,  1, 0, 0 },
	{ 27000000, P_PXO,  1, 0, 0 },
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
				&gp0_swc.cwkw.hw
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
				&gp1_swc.cwkw.hw
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
				&gp2_swc.cwkw.hw
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
	.cwkw.hw = {
		.init = &(stwuct cwk_init_data){
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
				&pwng_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
		},
	},
};

static const stwuct fweq_tbw cwk_tbw_sdc[] = {
	{    144000, P_PXO,   3, 2, 125 },
	{    400000, P_PWW8,  4, 1, 240 },
	{  16000000, P_PWW8,  4, 1,   6 },
	{  17070000, P_PWW8,  1, 2,  45 },
	{  20210000, P_PWW8,  1, 1,  19 },
	{  24000000, P_PWW8,  4, 1,   4 },
	{  48000000, P_PWW8,  4, 1,   2 },
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
			.ops = &cwk_wcg_ops,
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
				&sdc1_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg sdc2_swc = {
	.ns_weg = 0x284c,
	.md_weg = 0x2848,
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
		.enabwe_weg = 0x284c,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sdc2_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
		},
	}
};

static stwuct cwk_bwanch sdc2_cwk = {
	.hawt_weg = 0x2fc8,
	.hawt_bit = 5,
	.cwkw = {
		.enabwe_weg = 0x284c,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sdc2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&sdc2_swc.cwkw.hw
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
				&sdc3_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg sdc4_swc = {
	.ns_weg = 0x288c,
	.md_weg = 0x2888,
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
		.enabwe_weg = 0x288c,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sdc4_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
		},
	}
};

static stwuct cwk_bwanch sdc4_cwk = {
	.hawt_weg = 0x2fc8,
	.hawt_bit = 3,
	.cwkw = {
		.enabwe_weg = 0x288c,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sdc4_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&sdc4_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg sdc5_swc = {
	.ns_weg = 0x28ac,
	.md_weg = 0x28a8,
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
		.enabwe_weg = 0x28ac,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sdc5_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
		},
	}
};

static stwuct cwk_bwanch sdc5_cwk = {
	.hawt_weg = 0x2fc8,
	.hawt_bit = 2,
	.cwkw = {
		.enabwe_weg = 0x28ac,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sdc5_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&sdc5_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
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
			.fwags = CWK_SET_WATE_GATE,
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
				&tsif_wef_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static const stwuct fweq_tbw cwk_tbw_usb[] = {
	{ 60000000, P_PWW8, 1, 5, 32 },
	{ }
};

static stwuct cwk_wcg usb_hs1_xcvw_swc = {
	.ns_weg = 0x290c,
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
		.pawent_map = gcc_pxo_pww8_map,
	},
	.fweq_tbw = cwk_tbw_usb,
	.cwkw = {
		.enabwe_weg = 0x290c,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb_hs1_xcvw_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_WATE_GATE,
		},
	}
};

static stwuct cwk_bwanch usb_hs1_xcvw_cwk = {
	.hawt_weg = 0x2fc8,
	.hawt_bit = 0,
	.cwkw = {
		.enabwe_weg = 0x290c,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb_hs1_xcvw_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb_hs1_xcvw_swc.cwkw.hw
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg usb_fs1_xcvw_fs_swc = {
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
		.pawent_map = gcc_pxo_pww8_map,
	},
	.fweq_tbw = cwk_tbw_usb,
	.cwkw = {
		.enabwe_weg = 0x2968,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb_fs1_xcvw_fs_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_WATE_GATE,
		},
	}
};

static stwuct cwk_bwanch usb_fs1_xcvw_fs_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 15,
	.cwkw = {
		.enabwe_weg = 0x2968,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb_fs1_xcvw_fs_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb_fs1_xcvw_fs_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch usb_fs1_system_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 16,
	.cwkw = {
		.enabwe_weg = 0x296c,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb_fs1_xcvw_fs_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.name = "usb_fs1_system_cwk",
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_wcg usb_fs2_xcvw_fs_swc = {
	.ns_weg = 0x2988,
	.md_weg = 0x2984,
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
	.fweq_tbw = cwk_tbw_usb,
	.cwkw = {
		.enabwe_weg = 0x2988,
		.enabwe_mask = BIT(11),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb_fs2_xcvw_fs_swc",
			.pawent_data = gcc_pxo_pww8,
			.num_pawents = AWWAY_SIZE(gcc_pxo_pww8),
			.ops = &cwk_wcg_ops,
			.fwags = CWK_SET_WATE_GATE,
		},
	}
};

static stwuct cwk_bwanch usb_fs2_xcvw_fs_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 12,
	.cwkw = {
		.enabwe_weg = 0x2988,
		.enabwe_mask = BIT(9),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb_fs2_xcvw_fs_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb_fs2_xcvw_fs_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch usb_fs2_system_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 13,
	.cwkw = {
		.enabwe_weg = 0x298c,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb_fs2_system_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb_fs2_xcvw_fs_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch_ops,
			.fwags = CWK_SET_WATE_PAWENT,
		},
	},
};

static stwuct cwk_bwanch gsbi1_h_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 11,
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
	.hawt_weg = 0x2fcc,
	.hawt_bit = 7,
	.cwkw = {
		.enabwe_weg = 0x29e0,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi2_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch gsbi3_h_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 3,
	.cwkw = {
		.enabwe_weg = 0x2a00,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi3_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch gsbi4_h_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 27,
	.cwkw = {
		.enabwe_weg = 0x2a20,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi4_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch gsbi5_h_cwk = {
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

static stwuct cwk_bwanch gsbi8_h_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 11,
	.cwkw = {
		.enabwe_weg = 0x2aa0,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi8_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch gsbi9_h_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 7,
	.cwkw = {
		.enabwe_weg = 0x2ac0,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi9_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch gsbi10_h_cwk = {
	.hawt_weg = 0x2fd0,
	.hawt_bit = 3,
	.cwkw = {
		.enabwe_weg = 0x2ae0,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi10_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch gsbi11_h_cwk = {
	.hawt_weg = 0x2fd4,
	.hawt_bit = 18,
	.cwkw = {
		.enabwe_weg = 0x2b00,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi11_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch gsbi12_h_cwk = {
	.hawt_weg = 0x2fd4,
	.hawt_bit = 14,
	.cwkw = {
		.enabwe_weg = 0x2b20,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gsbi12_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch tsif_h_cwk = {
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

static stwuct cwk_bwanch usb_fs1_h_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 17,
	.cwkw = {
		.enabwe_weg = 0x2960,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb_fs1_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch usb_fs2_h_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 14,
	.cwkw = {
		.enabwe_weg = 0x2980,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "usb_fs2_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch usb_hs1_h_cwk = {
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

static stwuct cwk_bwanch sdc1_h_cwk = {
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

static stwuct cwk_bwanch sdc2_h_cwk = {
	.hawt_weg = 0x2fc8,
	.hawt_bit = 10,
	.cwkw = {
		.enabwe_weg = 0x2840,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sdc2_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch sdc3_h_cwk = {
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

static stwuct cwk_bwanch sdc4_h_cwk = {
	.hawt_weg = 0x2fc8,
	.hawt_bit = 8,
	.cwkw = {
		.enabwe_weg = 0x2880,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sdc4_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch sdc5_h_cwk = {
	.hawt_weg = 0x2fc8,
	.hawt_bit = 7,
	.cwkw = {
		.enabwe_weg = 0x28a0,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "sdc5_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch ebi2_2x_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 18,
	.cwkw = {
		.enabwe_weg = 0x2660,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "ebi2_2x_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch ebi2_cwk = {
	.hawt_weg = 0x2fcc,
	.hawt_bit = 19,
	.cwkw = {
		.enabwe_weg = 0x2664,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "ebi2_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch adm0_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hawt_bit = 14,
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
	.hawt_weg = 0x2fdc,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hawt_bit = 13,
	.cwkw = {
		.enabwe_weg = 0x3080,
		.enabwe_mask = BIT(3),
		.hw.init = &(stwuct cwk_init_data){
			.name = "adm0_pbus_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch adm1_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_bit = 12,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x3080,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "adm1_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch adm1_pbus_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_bit = 11,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x3080,
		.enabwe_mask = BIT(5),
		.hw.init = &(stwuct cwk_init_data){
			.name = "adm1_pbus_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch modem_ahb1_h_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_bit = 8,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x3080,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "modem_ahb1_h_cwk",
			.ops = &cwk_bwanch_ops,
		},
	},
};

static stwuct cwk_bwanch modem_ahb2_h_cwk = {
	.hawt_weg = 0x2fdc,
	.hawt_bit = 7,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x3080,
		.enabwe_mask = BIT(1),
		.hw.init = &(stwuct cwk_init_data){
			.name = "modem_ahb2_h_cwk",
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

static stwuct cwk_wegmap *gcc_msm8660_cwks[] = {
	[PWW8] = &pww8.cwkw,
	[PWW8_VOTE] = &pww8_vote,
	[GSBI1_UAWT_SWC] = &gsbi1_uawt_swc.cwkw,
	[GSBI1_UAWT_CWK] = &gsbi1_uawt_cwk.cwkw,
	[GSBI2_UAWT_SWC] = &gsbi2_uawt_swc.cwkw,
	[GSBI2_UAWT_CWK] = &gsbi2_uawt_cwk.cwkw,
	[GSBI3_UAWT_SWC] = &gsbi3_uawt_swc.cwkw,
	[GSBI3_UAWT_CWK] = &gsbi3_uawt_cwk.cwkw,
	[GSBI4_UAWT_SWC] = &gsbi4_uawt_swc.cwkw,
	[GSBI4_UAWT_CWK] = &gsbi4_uawt_cwk.cwkw,
	[GSBI5_UAWT_SWC] = &gsbi5_uawt_swc.cwkw,
	[GSBI5_UAWT_CWK] = &gsbi5_uawt_cwk.cwkw,
	[GSBI6_UAWT_SWC] = &gsbi6_uawt_swc.cwkw,
	[GSBI6_UAWT_CWK] = &gsbi6_uawt_cwk.cwkw,
	[GSBI7_UAWT_SWC] = &gsbi7_uawt_swc.cwkw,
	[GSBI7_UAWT_CWK] = &gsbi7_uawt_cwk.cwkw,
	[GSBI8_UAWT_SWC] = &gsbi8_uawt_swc.cwkw,
	[GSBI8_UAWT_CWK] = &gsbi8_uawt_cwk.cwkw,
	[GSBI9_UAWT_SWC] = &gsbi9_uawt_swc.cwkw,
	[GSBI9_UAWT_CWK] = &gsbi9_uawt_cwk.cwkw,
	[GSBI10_UAWT_SWC] = &gsbi10_uawt_swc.cwkw,
	[GSBI10_UAWT_CWK] = &gsbi10_uawt_cwk.cwkw,
	[GSBI11_UAWT_SWC] = &gsbi11_uawt_swc.cwkw,
	[GSBI11_UAWT_CWK] = &gsbi11_uawt_cwk.cwkw,
	[GSBI12_UAWT_SWC] = &gsbi12_uawt_swc.cwkw,
	[GSBI12_UAWT_CWK] = &gsbi12_uawt_cwk.cwkw,
	[GSBI1_QUP_SWC] = &gsbi1_qup_swc.cwkw,
	[GSBI1_QUP_CWK] = &gsbi1_qup_cwk.cwkw,
	[GSBI2_QUP_SWC] = &gsbi2_qup_swc.cwkw,
	[GSBI2_QUP_CWK] = &gsbi2_qup_cwk.cwkw,
	[GSBI3_QUP_SWC] = &gsbi3_qup_swc.cwkw,
	[GSBI3_QUP_CWK] = &gsbi3_qup_cwk.cwkw,
	[GSBI4_QUP_SWC] = &gsbi4_qup_swc.cwkw,
	[GSBI4_QUP_CWK] = &gsbi4_qup_cwk.cwkw,
	[GSBI5_QUP_SWC] = &gsbi5_qup_swc.cwkw,
	[GSBI5_QUP_CWK] = &gsbi5_qup_cwk.cwkw,
	[GSBI6_QUP_SWC] = &gsbi6_qup_swc.cwkw,
	[GSBI6_QUP_CWK] = &gsbi6_qup_cwk.cwkw,
	[GSBI7_QUP_SWC] = &gsbi7_qup_swc.cwkw,
	[GSBI7_QUP_CWK] = &gsbi7_qup_cwk.cwkw,
	[GSBI8_QUP_SWC] = &gsbi8_qup_swc.cwkw,
	[GSBI8_QUP_CWK] = &gsbi8_qup_cwk.cwkw,
	[GSBI9_QUP_SWC] = &gsbi9_qup_swc.cwkw,
	[GSBI9_QUP_CWK] = &gsbi9_qup_cwk.cwkw,
	[GSBI10_QUP_SWC] = &gsbi10_qup_swc.cwkw,
	[GSBI10_QUP_CWK] = &gsbi10_qup_cwk.cwkw,
	[GSBI11_QUP_SWC] = &gsbi11_qup_swc.cwkw,
	[GSBI11_QUP_CWK] = &gsbi11_qup_cwk.cwkw,
	[GSBI12_QUP_SWC] = &gsbi12_qup_swc.cwkw,
	[GSBI12_QUP_CWK] = &gsbi12_qup_cwk.cwkw,
	[GP0_SWC] = &gp0_swc.cwkw,
	[GP0_CWK] = &gp0_cwk.cwkw,
	[GP1_SWC] = &gp1_swc.cwkw,
	[GP1_CWK] = &gp1_cwk.cwkw,
	[GP2_SWC] = &gp2_swc.cwkw,
	[GP2_CWK] = &gp2_cwk.cwkw,
	[PMEM_CWK] = &pmem_cwk.cwkw,
	[PWNG_SWC] = &pwng_swc.cwkw,
	[PWNG_CWK] = &pwng_cwk.cwkw,
	[SDC1_SWC] = &sdc1_swc.cwkw,
	[SDC1_CWK] = &sdc1_cwk.cwkw,
	[SDC2_SWC] = &sdc2_swc.cwkw,
	[SDC2_CWK] = &sdc2_cwk.cwkw,
	[SDC3_SWC] = &sdc3_swc.cwkw,
	[SDC3_CWK] = &sdc3_cwk.cwkw,
	[SDC4_SWC] = &sdc4_swc.cwkw,
	[SDC4_CWK] = &sdc4_cwk.cwkw,
	[SDC5_SWC] = &sdc5_swc.cwkw,
	[SDC5_CWK] = &sdc5_cwk.cwkw,
	[TSIF_WEF_SWC] = &tsif_wef_swc.cwkw,
	[TSIF_WEF_CWK] = &tsif_wef_cwk.cwkw,
	[USB_HS1_XCVW_SWC] = &usb_hs1_xcvw_swc.cwkw,
	[USB_HS1_XCVW_CWK] = &usb_hs1_xcvw_cwk.cwkw,
	[USB_FS1_XCVW_FS_SWC] = &usb_fs1_xcvw_fs_swc.cwkw,
	[USB_FS1_XCVW_FS_CWK] = &usb_fs1_xcvw_fs_cwk.cwkw,
	[USB_FS1_SYSTEM_CWK] = &usb_fs1_system_cwk.cwkw,
	[USB_FS2_XCVW_FS_SWC] = &usb_fs2_xcvw_fs_swc.cwkw,
	[USB_FS2_XCVW_FS_CWK] = &usb_fs2_xcvw_fs_cwk.cwkw,
	[USB_FS2_SYSTEM_CWK] = &usb_fs2_system_cwk.cwkw,
	[GSBI1_H_CWK] = &gsbi1_h_cwk.cwkw,
	[GSBI2_H_CWK] = &gsbi2_h_cwk.cwkw,
	[GSBI3_H_CWK] = &gsbi3_h_cwk.cwkw,
	[GSBI4_H_CWK] = &gsbi4_h_cwk.cwkw,
	[GSBI5_H_CWK] = &gsbi5_h_cwk.cwkw,
	[GSBI6_H_CWK] = &gsbi6_h_cwk.cwkw,
	[GSBI7_H_CWK] = &gsbi7_h_cwk.cwkw,
	[GSBI8_H_CWK] = &gsbi8_h_cwk.cwkw,
	[GSBI9_H_CWK] = &gsbi9_h_cwk.cwkw,
	[GSBI10_H_CWK] = &gsbi10_h_cwk.cwkw,
	[GSBI11_H_CWK] = &gsbi11_h_cwk.cwkw,
	[GSBI12_H_CWK] = &gsbi12_h_cwk.cwkw,
	[TSIF_H_CWK] = &tsif_h_cwk.cwkw,
	[USB_FS1_H_CWK] = &usb_fs1_h_cwk.cwkw,
	[USB_FS2_H_CWK] = &usb_fs2_h_cwk.cwkw,
	[USB_HS1_H_CWK] = &usb_hs1_h_cwk.cwkw,
	[SDC1_H_CWK] = &sdc1_h_cwk.cwkw,
	[SDC2_H_CWK] = &sdc2_h_cwk.cwkw,
	[SDC3_H_CWK] = &sdc3_h_cwk.cwkw,
	[SDC4_H_CWK] = &sdc4_h_cwk.cwkw,
	[SDC5_H_CWK] = &sdc5_h_cwk.cwkw,
	[EBI2_2X_CWK] = &ebi2_2x_cwk.cwkw,
	[EBI2_CWK] = &ebi2_cwk.cwkw,
	[ADM0_CWK] = &adm0_cwk.cwkw,
	[ADM0_PBUS_CWK] = &adm0_pbus_cwk.cwkw,
	[ADM1_CWK] = &adm1_cwk.cwkw,
	[ADM1_PBUS_CWK] = &adm1_pbus_cwk.cwkw,
	[MODEM_AHB1_H_CWK] = &modem_ahb1_h_cwk.cwkw,
	[MODEM_AHB2_H_CWK] = &modem_ahb2_h_cwk.cwkw,
	[PMIC_AWB0_H_CWK] = &pmic_awb0_h_cwk.cwkw,
	[PMIC_AWB1_H_CWK] = &pmic_awb1_h_cwk.cwkw,
	[PMIC_SSBI2_CWK] = &pmic_ssbi2_cwk.cwkw,
	[WPM_MSG_WAM_H_CWK] = &wpm_msg_wam_h_cwk.cwkw,
};

static const stwuct qcom_weset_map gcc_msm8660_wesets[] = {
	[AFAB_COWE_WESET] = { 0x2080, 7 },
	[SCSS_SYS_WESET] = { 0x20b4, 1 },
	[SCSS_SYS_POW_WESET] = { 0x20b4 },
	[AFAB_SMPSS_S_WESET] = { 0x20b8, 2 },
	[AFAB_SMPSS_M1_WESET] = { 0x20b8, 1 },
	[AFAB_SMPSS_M0_WESET] = { 0x20b8 },
	[AFAB_EBI1_S_WESET] = { 0x20c0, 7 },
	[SFAB_COWE_WESET] = { 0x2120, 7 },
	[SFAB_ADM0_M0_WESET] = { 0x21e0, 7 },
	[SFAB_ADM0_M1_WESET] = { 0x21e4, 7 },
	[SFAB_ADM0_M2_WESET] = { 0x21e4, 7 },
	[ADM0_C2_WESET] = { 0x220c, 4 },
	[ADM0_C1_WESET] = { 0x220c, 3 },
	[ADM0_C0_WESET] = { 0x220c, 2 },
	[ADM0_PBUS_WESET] = { 0x220c, 1 },
	[ADM0_WESET] = { 0x220c },
	[SFAB_ADM1_M0_WESET] = { 0x2220, 7 },
	[SFAB_ADM1_M1_WESET] = { 0x2224, 7 },
	[SFAB_ADM1_M2_WESET] = { 0x2228, 7 },
	[MMFAB_ADM1_M3_WESET] = { 0x2240, 7 },
	[ADM1_C3_WESET] = { 0x226c, 5 },
	[ADM1_C2_WESET] = { 0x226c, 4 },
	[ADM1_C1_WESET] = { 0x226c, 3 },
	[ADM1_C0_WESET] = { 0x226c, 2 },
	[ADM1_PBUS_WESET] = { 0x226c, 1 },
	[ADM1_WESET] = { 0x226c },
	[IMEM0_WESET] = { 0x2280, 7 },
	[SFAB_WPASS_Q6_WESET] = { 0x23a0, 7 },
	[SFAB_AFAB_M_WESET] = { 0x23e0, 7 },
	[AFAB_SFAB_M0_WESET] = { 0x2420, 7 },
	[AFAB_SFAB_M1_WESET] = { 0x2424, 7 },
	[DFAB_COWE_WESET] = { 0x24ac, 7 },
	[SFAB_DFAB_M_WESET] = { 0x2500, 7 },
	[DFAB_SFAB_M_WESET] = { 0x2520, 7 },
	[DFAB_SWAY0_WESET] = { 0x2540, 7 },
	[DFAB_SWAY1_WESET] = { 0x2544, 7 },
	[DFAB_AWB0_WESET] = { 0x2560, 7 },
	[DFAB_AWB1_WESET] = { 0x2564, 7 },
	[PPSS_PWOC_WESET] = { 0x2594, 1 },
	[PPSS_WESET] = { 0x2594 },
	[PMEM_WESET] = { 0x25a0, 7 },
	[DMA_BAM_WESET] = { 0x25c0, 7 },
	[SIC_WESET] = { 0x25e0, 7 },
	[SPS_TIC_WESET] = { 0x2600, 7 },
	[CFBP0_WESET] = { 0x2650, 7 },
	[CFBP1_WESET] = { 0x2654, 7 },
	[CFBP2_WESET] = { 0x2658, 7 },
	[EBI2_WESET] = { 0x2664, 7 },
	[SFAB_CFPB_M_WESET] = { 0x2680, 7 },
	[CFPB_MASTEW_WESET] = { 0x26a0, 7 },
	[SFAB_CFPB_S_WESET] = { 0x26c0, 7 },
	[CFPB_SPWITTEW_WESET] = { 0x26e0, 7 },
	[TSIF_WESET] = { 0x2700, 7 },
	[CE1_WESET] = { 0x2720, 7 },
	[CE2_WESET] = { 0x2740, 7 },
	[SFAB_SFPB_M_WESET] = { 0x2780, 7 },
	[SFAB_SFPB_S_WESET] = { 0x27a0, 7 },
	[WPM_PWOC_WESET] = { 0x27c0, 7 },
	[WPM_BUS_WESET] = { 0x27c4, 7 },
	[WPM_MSG_WAM_WESET] = { 0x27e0, 7 },
	[PMIC_AWB0_WESET] = { 0x2800, 7 },
	[PMIC_AWB1_WESET] = { 0x2804, 7 },
	[PMIC_SSBI2_WESET] = { 0x280c, 12 },
	[SDC1_WESET] = { 0x2830 },
	[SDC2_WESET] = { 0x2850 },
	[SDC3_WESET] = { 0x2870 },
	[SDC4_WESET] = { 0x2890 },
	[SDC5_WESET] = { 0x28b0 },
	[USB_HS1_WESET] = { 0x2910 },
	[USB_HS2_XCVW_WESET] = { 0x2934, 1 },
	[USB_HS2_WESET] = { 0x2934 },
	[USB_FS1_XCVW_WESET] = { 0x2974, 1 },
	[USB_FS1_WESET] = { 0x2974 },
	[USB_FS2_XCVW_WESET] = { 0x2994, 1 },
	[USB_FS2_WESET] = { 0x2994 },
	[GSBI1_WESET] = { 0x29dc },
	[GSBI2_WESET] = { 0x29fc },
	[GSBI3_WESET] = { 0x2a1c },
	[GSBI4_WESET] = { 0x2a3c },
	[GSBI5_WESET] = { 0x2a5c },
	[GSBI6_WESET] = { 0x2a7c },
	[GSBI7_WESET] = { 0x2a9c },
	[GSBI8_WESET] = { 0x2abc },
	[GSBI9_WESET] = { 0x2adc },
	[GSBI10_WESET] = { 0x2afc },
	[GSBI11_WESET] = { 0x2b1c },
	[GSBI12_WESET] = { 0x2b3c },
	[SPDM_WESET] = { 0x2b6c },
	[SEC_CTWW_WESET] = { 0x2b80, 7 },
	[TWMM_H_WESET] = { 0x2ba0, 7 },
	[TWMM_WESET] = { 0x2ba4, 7 },
	[MAWWM_PWWON_WESET] = { 0x2bd4, 1 },
	[MAWM_WESET] = { 0x2bd4 },
	[MAHB1_WESET] = { 0x2be4, 7 },
	[SFAB_MSS_S_WESET] = { 0x2c00, 7 },
	[MAHB2_WESET] = { 0x2c20, 7 },
	[MODEM_SW_AHB_WESET] = { 0x2c48, 1 },
	[MODEM_WESET] = { 0x2c48 },
	[SFAB_MSS_MDM1_WESET] = { 0x2c4c, 1 },
	[SFAB_MSS_MDM0_WESET] = { 0x2c4c },
	[MSS_SWP_WESET] = { 0x2c60, 7 },
	[MSS_MAWM_SAW_WESET] = { 0x2c68, 1 },
	[MSS_WDOG_WESET] = { 0x2c68 },
	[TSSC_WESET] = { 0x2ca0, 7 },
	[PDM_WESET] = { 0x2cc0, 12 },
	[SCSS_COWE0_WESET] = { 0x2d60, 1 },
	[SCSS_COWE0_POW_WESET] = { 0x2d60 },
	[SCSS_COWE1_WESET] = { 0x2d80, 1 },
	[SCSS_COWE1_POW_WESET] = { 0x2d80 },
	[MPM_WESET] = { 0x2da4, 1 },
	[EBI1_1X_DIV_WESET] = { 0x2dec, 9 },
	[EBI1_WESET] = { 0x2dec, 7 },
	[SFAB_SMPSS_S_WESET] = { 0x2e00, 7 },
	[USB_PHY0_WESET] = { 0x2e20 },
	[USB_PHY1_WESET] = { 0x2e40 },
	[PWNG_WESET] = { 0x2e80, 12 },
};

static const stwuct wegmap_config gcc_msm8660_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x363c,
	.fast_io	= twue,
};

static const stwuct qcom_cc_desc gcc_msm8660_desc = {
	.config = &gcc_msm8660_wegmap_config,
	.cwks = gcc_msm8660_cwks,
	.num_cwks = AWWAY_SIZE(gcc_msm8660_cwks),
	.wesets = gcc_msm8660_wesets,
	.num_wesets = AWWAY_SIZE(gcc_msm8660_wesets),
};

static const stwuct of_device_id gcc_msm8660_match_tabwe[] = {
	{ .compatibwe = "qcom,gcc-msm8660" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gcc_msm8660_match_tabwe);

static int gcc_msm8660_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn qcom_cc_pwobe(pdev, &gcc_msm8660_desc);
}

static stwuct pwatfowm_dwivew gcc_msm8660_dwivew = {
	.pwobe		= gcc_msm8660_pwobe,
	.dwivew		= {
		.name	= "gcc-msm8660",
		.of_match_tabwe = gcc_msm8660_match_tabwe,
	},
};

static int __init gcc_msm8660_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gcc_msm8660_dwivew);
}
cowe_initcaww(gcc_msm8660_init);

static void __exit gcc_msm8660_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gcc_msm8660_dwivew);
}
moduwe_exit(gcc_msm8660_exit);

MODUWE_DESCWIPTION("GCC MSM 8660 Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:gcc-msm8660");
