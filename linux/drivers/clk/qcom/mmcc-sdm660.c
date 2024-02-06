// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2020, Mawtin Botka <mawtin.botka@somainwine.owg>
 * Copywight (c) 2020, Konwad Dybcio <konwad.dybcio@somainwine.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/cwk.h>


#incwude <dt-bindings/cwock/qcom,mmcc-sdm660.h>

#incwude "common.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "cwk-awpha-pww.h"
#incwude "cwk-wcg.h"
#incwude "cwk-bwanch.h"
#incwude "weset.h"
#incwude "gdsc.h"

enum {
	P_XO,
	P_DSI0PWW_BYTE,
	P_DSI0PWW,
	P_DSI1PWW_BYTE,
	P_DSI1PWW,
	P_GPWW0,
	P_GPWW0_DIV,
	P_MMPWW0,
	P_MMPWW10,
	P_MMPWW3,
	P_MMPWW4,
	P_MMPWW5,
	P_MMPWW6,
	P_MMPWW7,
	P_MMPWW8,
	P_SWEEP_CWK,
	P_DP_PHY_PWW_WINK_CWK,
	P_DP_PHY_PWW_VCO_DIV,
};

static const stwuct pawent_map mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww8_gpww0_gpww0_div_map[] = {
	{ P_XO, 0 },
	{ P_MMPWW0, 1 },
	{ P_MMPWW4, 2 },
	{ P_MMPWW7, 3 },
	{ P_MMPWW8, 4 },
	{ P_GPWW0, 5 },
	{ P_GPWW0_DIV, 6 },
};

/* Voteabwe PWW */
static stwuct cwk_awpha_pww mmpww0 = {
	.offset = 0xc000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x1f0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mmpww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static stwuct cwk_awpha_pww mmpww6 =  {
	.offset = 0xf0,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x1f0,
		.enabwe_mask = BIT(2),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mmpww6",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

/* APSS contwowwed PWWs */
static stwuct pww_vco vco[] = {
	{ 1000000000, 2000000000, 0 },
	{ 750000000, 1500000000, 1 },
	{ 500000000, 1000000000, 2 },
	{ 250000000, 500000000, 3 },
};

static stwuct pww_vco mmpww3_vco[] = {
	{ 750000000, 1500000000, 1 },
};

static const stwuct awpha_pww_config mmpww10_config = {
	.w = 0x1e,
	.config_ctw_vaw = 0x00004289,
	.main_output_mask = 0x1,
};

static stwuct cwk_awpha_pww mmpww10 = {
	.offset = 0x190,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "mmpww10",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static const stwuct awpha_pww_config mmpww3_config = {
	.w = 0x2e,
	.config_ctw_vaw = 0x4001055b,
	.vco_vaw = 0x1 << 20,
	.vco_mask = 0x3 << 20,
	.main_output_mask = 0x1,
};

static stwuct cwk_awpha_pww mmpww3 = {
	.offset = 0x0,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.vco_tabwe = mmpww3_vco,
	.num_vco = AWWAY_SIZE(mmpww3_vco),
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "mmpww3",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static const stwuct awpha_pww_config mmpww4_config = {
	.w = 0x28,
	.config_ctw_vaw = 0x4001055b,
	.vco_vaw = 0x2 << 20,
	.vco_mask = 0x3 << 20,
	.main_output_mask = 0x1,
};

static stwuct cwk_awpha_pww mmpww4 = {
	.offset = 0x50,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.vco_tabwe = vco,
	.num_vco = AWWAY_SIZE(vco),
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "mmpww4",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static const stwuct awpha_pww_config mmpww5_config = {
	.w = 0x2a,
	.config_ctw_vaw = 0x4001055b,
	.awpha_hi = 0xf8,
	.awpha_en_mask = BIT(24),
	.vco_vaw = 0x2 << 20,
	.vco_mask = 0x3 << 20,
	.main_output_mask = 0x1,
};

static stwuct cwk_awpha_pww mmpww5 = {
	.offset = 0xa0,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.vco_tabwe = vco,
	.num_vco = AWWAY_SIZE(vco),
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "mmpww5",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static const stwuct awpha_pww_config mmpww7_config = {
	.w = 0x32,
	.config_ctw_vaw = 0x4001055b,
	.vco_vaw = 0x2 << 20,
	.vco_mask = 0x3 << 20,
	.main_output_mask = 0x1,
};

static stwuct cwk_awpha_pww mmpww7 = {
	.offset = 0x140,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.vco_tabwe = vco,
	.num_vco = AWWAY_SIZE(vco),
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "mmpww7",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static const stwuct awpha_pww_config mmpww8_config = {
	.w = 0x30,
	.awpha_hi = 0x70,
	.awpha_en_mask = BIT(24),
	.config_ctw_vaw = 0x4001055b,
	.vco_vaw = 0x2 << 20,
	.vco_mask = 0x3 << 20,
	.main_output_mask = 0x1,
};

static stwuct cwk_awpha_pww mmpww8 = {
	.offset = 0x1c0,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.vco_tabwe = vco,
	.num_vco = AWWAY_SIZE(vco),
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "mmpww8",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static const stwuct cwk_pawent_data mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww8_gpww0_gpww0_div[] = {
	{ .fw_name = "xo" },
	{ .hw = &mmpww0.cwkw.hw },
	{ .hw = &mmpww4.cwkw.hw },
	{ .hw = &mmpww7.cwkw.hw },
	{ .hw = &mmpww8.cwkw.hw },
	{ .fw_name = "gpww0" },
	{ .fw_name = "gpww0_div" },
};

static const stwuct pawent_map mmcc_xo_dsibyte_map[] = {
	{ P_XO, 0 },
	{ P_DSI0PWW_BYTE, 1 },
	{ P_DSI1PWW_BYTE, 2 },
};

static const stwuct cwk_pawent_data mmcc_xo_dsibyte[] = {
	{ .fw_name = "xo" },
	{ .fw_name = "dsi0pwwbyte" },
	{ .fw_name = "dsi1pwwbyte" },
};

static const stwuct pawent_map mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_gpww0_div_map[] = {
	{ P_XO, 0 },
	{ P_MMPWW0, 1 },
	{ P_MMPWW4, 2 },
	{ P_MMPWW7, 3 },
	{ P_MMPWW10, 4 },
	{ P_GPWW0, 5 },
	{ P_GPWW0_DIV, 6 },
};

static const stwuct cwk_pawent_data mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_gpww0_div[] = {
	{ .fw_name = "xo" },
	{ .hw = &mmpww0.cwkw.hw },
	{ .hw = &mmpww4.cwkw.hw },
	{ .hw = &mmpww7.cwkw.hw },
	{ .hw = &mmpww10.cwkw.hw },
	{ .fw_name = "gpww0" },
	{ .fw_name = "gpww0_div" },
};

static const stwuct pawent_map mmcc_xo_mmpww4_mmpww7_mmpww10_sweep_gpww0_gpww0_div_map[] = {
	{ P_XO, 0 },
	{ P_MMPWW4, 1 },
	{ P_MMPWW7, 2 },
	{ P_MMPWW10, 3 },
	{ P_SWEEP_CWK, 4 },
	{ P_GPWW0, 5 },
	{ P_GPWW0_DIV, 6 },
};

static const stwuct cwk_pawent_data mmcc_xo_mmpww4_mmpww7_mmpww10_sweep_gpww0_gpww0_div[] = {
	{ .fw_name = "xo" },
	{ .hw = &mmpww4.cwkw.hw },
	{ .hw = &mmpww7.cwkw.hw },
	{ .hw = &mmpww10.cwkw.hw },
	{ .fw_name = "sweep_cwk" },
	{ .fw_name = "gpww0" },
	{ .fw_name = "gpww0_div" },
};

static const stwuct pawent_map mmcc_xo_mmpww0_mmpww7_mmpww10_sweep_gpww0_gpww0_div_map[] = {
	{ P_XO, 0 },
	{ P_MMPWW0, 1 },
	{ P_MMPWW7, 2 },
	{ P_MMPWW10, 3 },
	{ P_SWEEP_CWK, 4 },
	{ P_GPWW0, 5 },
	{ P_GPWW0_DIV, 6 },
};

static const stwuct cwk_pawent_data mmcc_xo_mmpww0_mmpww7_mmpww10_sweep_gpww0_gpww0_div[] = {
	{ .fw_name = "xo" },
	{ .hw = &mmpww0.cwkw.hw },
	{ .hw = &mmpww7.cwkw.hw },
	{ .hw = &mmpww10.cwkw.hw },
	{ .fw_name = "sweep_cwk" },
	{ .fw_name = "gpww0" },
	{ .fw_name = "gpww0_div" },
};

static const stwuct pawent_map mmcc_xo_gpww0_gpww0_div_map[] = {
	{ P_XO, 0 },
	{ P_GPWW0, 5 },
	{ P_GPWW0_DIV, 6 },
};

static const stwuct cwk_pawent_data mmcc_xo_gpww0_gpww0_div[] = {
	{ .fw_name = "xo" },
	{ .fw_name = "gpww0" },
	{ .fw_name = "gpww0_div" },
};

static const stwuct pawent_map mmcc_xo_dpwink_dpvco_map[] = {
	{ P_XO, 0 },
	{ P_DP_PHY_PWW_WINK_CWK, 1 },
	{ P_DP_PHY_PWW_VCO_DIV, 2 },
};

static const stwuct cwk_pawent_data mmcc_xo_dpwink_dpvco[] = {
	{ .fw_name = "xo" },
	{ .fw_name = "dp_wink_2x_cwk_divsew_five" },
	{ .fw_name = "dp_vco_divided_cwk_swc_mux" },
};

static const stwuct pawent_map mmcc_xo_mmpww0_mmpww5_mmpww7_gpww0_gpww0_div_map[] = {
	{ P_XO, 0 },
	{ P_MMPWW0, 1 },
	{ P_MMPWW5, 2 },
	{ P_MMPWW7, 3 },
	{ P_GPWW0, 5 },
	{ P_GPWW0_DIV, 6 },
};

static const stwuct cwk_pawent_data mmcc_xo_mmpww0_mmpww5_mmpww7_gpww0_gpww0_div[] = {
	{ .fw_name = "xo" },
	{ .hw = &mmpww0.cwkw.hw },
	{ .hw = &mmpww5.cwkw.hw },
	{ .hw = &mmpww7.cwkw.hw },
	{ .fw_name = "gpww0" },
	{ .fw_name = "gpww0_div" },
};

static const stwuct pawent_map mmcc_xo_dsi0pww_dsi1pww_map[] = {
	{ P_XO, 0 },
	{ P_DSI0PWW, 1 },
	{ P_DSI1PWW, 2 },
};

static const stwuct cwk_pawent_data mmcc_xo_dsi0pww_dsi1pww[] = {
	{ .fw_name = "xo" },
	{ .fw_name = "dsi0pww" },
	{ .fw_name = "dsi1pww" },
};

static const stwuct pawent_map mmcc_mmpww0_mmpww4_mmpww7_mmpww10_mmpww6_gpww0_map[] = {
	{ P_XO, 0 },
	{ P_MMPWW0, 1 },
	{ P_MMPWW4, 2 },
	{ P_MMPWW7, 3 },
	{ P_MMPWW10, 4 },
	{ P_MMPWW6, 5 },
	{ P_GPWW0, 6 },
};

static const stwuct cwk_pawent_data mmcc_mmpww0_mmpww4_mmpww7_mmpww10_mmpww6_gpww0[] = {
	{ .fw_name = "xo" },
	{ .hw = &mmpww0.cwkw.hw },
	{ .hw = &mmpww4.cwkw.hw },
	{ .hw = &mmpww7.cwkw.hw },
	{ .hw = &mmpww10.cwkw.hw },
	{ .hw = &mmpww6.cwkw.hw },
	{ .fw_name = "gpww0" },
};

static const stwuct pawent_map mmcc_xo_mmpww0_gpww0_gpww0_div_map[] = {
	{ P_XO, 0 },
	{ P_MMPWW0, 1 },
	{ P_GPWW0, 5 },
	{ P_GPWW0_DIV, 6 },
};

static const stwuct cwk_pawent_data mmcc_xo_mmpww0_gpww0_gpww0_div[] = {
	{ .fw_name = "xo" },
	{ .hw = &mmpww0.cwkw.hw },
	{ .fw_name = "gpww0" },
	{ .fw_name = "gpww0_div" },
};

static const stwuct pawent_map mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_mmpww6_map[] = {
	{ P_XO, 0 },
	{ P_MMPWW0, 1 },
	{ P_MMPWW4, 2 },
	{ P_MMPWW7, 3 },
	{ P_MMPWW10, 4 },
	{ P_GPWW0, 5 },
	{ P_MMPWW6, 6 },
};

static const stwuct cwk_pawent_data mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_mmpww6[] = {
	{ .fw_name = "xo" },
	{ .hw = &mmpww0.cwkw.hw },
	{ .hw = &mmpww4.cwkw.hw },
	{ .hw = &mmpww7.cwkw.hw },
	{ .hw = &mmpww10.cwkw.hw },
	{ .fw_name = "gpww0" },
	{ .hw = &mmpww6.cwkw.hw },
};

static const stwuct pawent_map mmcc_xo_mmpww0_mmpww8_mmpww3_mmpww6_gpww0_mmpww7_map[] = {
	{ P_XO, 0 },
	{ P_MMPWW0, 1 },
	{ P_MMPWW8, 2 },
	{ P_MMPWW3, 3 },
	{ P_MMPWW6, 4 },
	{ P_GPWW0, 5 },
	{ P_MMPWW7, 6 },
};

static const stwuct cwk_pawent_data mmcc_xo_mmpww0_mmpww8_mmpww3_mmpww6_gpww0_mmpww7[] = {
	{ .fw_name = "xo" },
	{ .hw = &mmpww0.cwkw.hw },
	{ .hw = &mmpww8.cwkw.hw },
	{ .hw = &mmpww3.cwkw.hw },
	{ .hw = &mmpww6.cwkw.hw },
	{ .fw_name = "gpww0" },
	{ .hw = &mmpww7.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_ahb_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(40000000, P_GPWW0_DIV, 7.5, 0, 0),
	F(80800000, P_MMPWW0, 10, 0, 0),
	{ }
};

static stwuct cwk_wcg2 ahb_cwk_swc = {
	.cmd_wcgw = 0x5000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "ahb_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 byte0_cwk_swc = {
	.cmd_wcgw = 0x2120,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_dsibyte_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "byte0_cwk_swc",
		.pawent_data = mmcc_xo_dsibyte,
		.num_pawents = AWWAY_SIZE(mmcc_xo_dsibyte),
		.ops = &cwk_byte2_ops,
		.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
	},
};

static stwuct cwk_wcg2 byte1_cwk_swc = {
	.cmd_wcgw = 0x2140,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_dsibyte_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "byte1_cwk_swc",
		.pawent_data = mmcc_xo_dsibyte,
		.num_pawents = AWWAY_SIZE(mmcc_xo_dsibyte),
		.ops = &cwk_byte2_ops,
		.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
	},
};

static const stwuct fweq_tbw ftbw_camss_gp0_cwk_swc[] = {
	F(10000, P_XO, 16, 1, 120),
	F(24000, P_XO, 16, 1, 50),
	F(6000000, P_GPWW0_DIV, 10, 1, 5),
	F(12000000, P_GPWW0_DIV, 10, 2, 5),
	F(13043478, P_GPWW0_DIV, 1, 1, 23),
	F(24000000, P_GPWW0_DIV, 1, 2, 25),
	F(50000000, P_GPWW0_DIV, 6, 0, 0),
	F(100000000, P_GPWW0_DIV, 3, 0, 0),
	F(200000000, P_GPWW0, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 camss_gp0_cwk_swc = {
	.cmd_wcgw = 0x3420,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_mmpww7_mmpww10_sweep_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_camss_gp0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camss_gp0_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_mmpww7_mmpww10_sweep_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_mmpww7_mmpww10_sweep_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 camss_gp1_cwk_swc = {
	.cmd_wcgw = 0x3450,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_mmpww7_mmpww10_sweep_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_camss_gp0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "camss_gp1_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_mmpww7_mmpww10_sweep_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_mmpww7_mmpww10_sweep_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cci_cwk_swc[] = {
	F(37500000, P_GPWW0_DIV, 8, 0, 0),
	F(50000000, P_GPWW0_DIV, 6, 0, 0),
	F(100000000, P_GPWW0, 6, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cci_cwk_swc = {
	.cmd_wcgw = 0x3300,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_mmpww7_mmpww10_sweep_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_cci_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cci_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_mmpww7_mmpww10_sweep_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_mmpww7_mmpww10_sweep_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cpp_cwk_swc[] = {
	F(120000000, P_GPWW0, 5, 0, 0),
	F(256000000, P_MMPWW4, 3, 0, 0),
	F(384000000, P_MMPWW4, 2, 0, 0),
	F(480000000, P_MMPWW7, 2, 0, 0),
	F(540000000, P_MMPWW6, 2, 0, 0),
	F(576000000, P_MMPWW10, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cpp_cwk_swc = {
	.cmd_wcgw = 0x3640,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_mmpww6_map,
	.fweq_tbw = ftbw_cpp_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cpp_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_mmpww6,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_mmpww6),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_csi0_cwk_swc[] = {
	F(100000000, P_GPWW0_DIV, 3, 0, 0),
	F(200000000, P_GPWW0, 3, 0, 0),
	F(310000000, P_MMPWW8, 3, 0, 0),
	F(404000000, P_MMPWW0, 2, 0, 0),
	F(465000000, P_MMPWW8, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 csi0_cwk_swc = {
	.cmd_wcgw = 0x3090,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww8_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_csi0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "csi0_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww8_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww8_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_csi0phytimew_cwk_swc[] = {
	F(100000000, P_GPWW0_DIV, 3, 0, 0),
	F(200000000, P_GPWW0, 3, 0, 0),
	F(269333333, P_MMPWW0, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 csi0phytimew_cwk_swc = {
	.cmd_wcgw = 0x3000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "csi0phytimew_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 csi1_cwk_swc = {
	.cmd_wcgw = 0x3100,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww8_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_csi0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "csi1_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww8_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww8_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 csi1phytimew_cwk_swc = {
	.cmd_wcgw = 0x3030,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "csi1phytimew_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 csi2_cwk_swc = {
	.cmd_wcgw = 0x3160,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww8_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_csi0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "csi2_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww8_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww8_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 csi2phytimew_cwk_swc = {
	.cmd_wcgw = 0x3060,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "csi2phytimew_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 csi3_cwk_swc = {
	.cmd_wcgw = 0x31c0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww8_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_csi0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "csi3_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww8_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww8_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_csiphy_cwk_swc[] = {
	F(100000000, P_GPWW0_DIV, 3, 0, 0),
	F(200000000, P_GPWW0, 3, 0, 0),
	F(269333333, P_MMPWW0, 3, 0, 0),
	F(320000000, P_MMPWW7, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 csiphy_cwk_swc = {
	.cmd_wcgw = 0x3800,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww8_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_csiphy_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "csiphy_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww8_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww8_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_dp_aux_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 dp_aux_cwk_swc = {
	.cmd_wcgw = 0x2260,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_dp_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "dp_aux_cwk_swc",
		.pawent_data = mmcc_xo_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_dp_cwypto_cwk_swc[] = {
	F(101250000, P_DP_PHY_PWW_VCO_DIV, 4, 0, 0),
	F(168750000, P_DP_PHY_PWW_VCO_DIV, 4, 0, 0),
	F(337500000, P_DP_PHY_PWW_VCO_DIV, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 dp_cwypto_cwk_swc = {
	.cmd_wcgw = 0x2220,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = mmcc_xo_dpwink_dpvco_map,
	.fweq_tbw = ftbw_dp_cwypto_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "dp_cwypto_cwk_swc",
		.pawent_data = mmcc_xo_dpwink_dpvco,
		.num_pawents = AWWAY_SIZE(mmcc_xo_dpwink_dpvco),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_dp_gtc_cwk_swc[] = {
	F(40000000, P_GPWW0_DIV, 7.5, 0, 0),
	F(60000000, P_GPWW0, 10, 0, 0),
	{ }
};

static stwuct cwk_wcg2 dp_gtc_cwk_swc = {
	.cmd_wcgw = 0x2280,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_dp_gtc_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "dp_gtc_cwk_swc",
		.pawent_data = mmcc_xo_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_dp_wink_cwk_swc[] = {
	F(162000000, P_DP_PHY_PWW_WINK_CWK, 2, 0, 0),
	F(270000000, P_DP_PHY_PWW_WINK_CWK, 2, 0, 0),
	F(540000000, P_DP_PHY_PWW_WINK_CWK, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 dp_wink_cwk_swc = {
	.cmd_wcgw = 0x2200,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_dpwink_dpvco_map,
	.fweq_tbw = ftbw_dp_wink_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "dp_wink_cwk_swc",
		.pawent_data = mmcc_xo_dpwink_dpvco,
		.num_pawents = AWWAY_SIZE(mmcc_xo_dpwink_dpvco),
		.ops = &cwk_wcg2_ops,
		.fwags = CWK_GET_WATE_NOCACHE | CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wcg2 dp_pixew_cwk_swc = {
	.cmd_wcgw = 0x2240,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = mmcc_xo_dpwink_dpvco_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "dp_pixew_cwk_swc",
		.pawent_data = mmcc_xo_dpwink_dpvco,
		.num_pawents = AWWAY_SIZE(mmcc_xo_dpwink_dpvco),
		.ops = &cwk_dp_ops,
		.fwags = CWK_GET_WATE_NOCACHE | CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_wcg2 esc0_cwk_swc = {
	.cmd_wcgw = 0x2160,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_dsibyte_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "esc0_cwk_swc",
		.pawent_data = mmcc_xo_dsibyte,
		.num_pawents = AWWAY_SIZE(mmcc_xo_dsibyte),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 esc1_cwk_swc = {
	.cmd_wcgw = 0x2180,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_dsibyte_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "esc1_cwk_swc",
		.pawent_data = mmcc_xo_dsibyte,
		.num_pawents = AWWAY_SIZE(mmcc_xo_dsibyte),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_jpeg0_cwk_swc[] = {
	F(66666667, P_GPWW0_DIV, 4.5, 0, 0),
	F(133333333, P_GPWW0, 4.5, 0, 0),
	F(219428571, P_MMPWW4, 3.5, 0, 0),
	F(320000000, P_MMPWW7, 3, 0, 0),
	F(480000000, P_MMPWW7, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 jpeg0_cwk_swc = {
	.cmd_wcgw = 0x3500,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_jpeg0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "jpeg0_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_mcwk0_cwk_swc[] = {
	F(4800000, P_XO, 4, 0, 0),
	F(6000000, P_GPWW0_DIV, 10, 1, 5),
	F(8000000, P_GPWW0_DIV, 1, 2, 75),
	F(9600000, P_XO, 2, 0, 0),
	F(16666667, P_GPWW0_DIV, 2, 1, 9),
	F(19200000, P_XO, 1, 0, 0),
	F(24000000, P_MMPWW10, 1, 1, 24),
	F(33333333, P_GPWW0_DIV, 1, 1, 9),
	F(48000000, P_GPWW0, 1, 2, 25),
	F(66666667, P_GPWW0, 1, 1, 9),
	{ }
};

static stwuct cwk_wcg2 mcwk0_cwk_swc = {
	.cmd_wcgw = 0x3360,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww4_mmpww7_mmpww10_sweep_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "mcwk0_cwk_swc",
		.pawent_data = mmcc_xo_mmpww4_mmpww7_mmpww10_sweep_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww4_mmpww7_mmpww10_sweep_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 mcwk1_cwk_swc = {
	.cmd_wcgw = 0x3390,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww4_mmpww7_mmpww10_sweep_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "mcwk1_cwk_swc",
		.pawent_data = mmcc_xo_mmpww4_mmpww7_mmpww10_sweep_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww4_mmpww7_mmpww10_sweep_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 mcwk2_cwk_swc = {
	.cmd_wcgw = 0x33c0,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww4_mmpww7_mmpww10_sweep_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "mcwk2_cwk_swc",
		.pawent_data = mmcc_xo_mmpww4_mmpww7_mmpww10_sweep_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww4_mmpww7_mmpww10_sweep_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 mcwk3_cwk_swc = {
	.cmd_wcgw = 0x33f0,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww4_mmpww7_mmpww10_sweep_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "mcwk3_cwk_swc",
		.pawent_data = mmcc_xo_mmpww4_mmpww7_mmpww10_sweep_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww4_mmpww7_mmpww10_sweep_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_mdp_cwk_swc[] = {
	F(100000000, P_GPWW0_DIV, 3, 0, 0),
	F(150000000, P_GPWW0_DIV, 2, 0, 0),
	F(171428571, P_GPWW0, 3.5, 0, 0),
	F(200000000, P_GPWW0, 3, 0, 0),
	F(275000000, P_MMPWW5, 3, 0, 0),
	F(300000000, P_GPWW0, 2, 0, 0),
	F(330000000, P_MMPWW5, 2.5, 0, 0),
	F(412500000, P_MMPWW5, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 mdp_cwk_swc = {
	.cmd_wcgw = 0x2040,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_mmpww5_mmpww7_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_mdp_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "mdp_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_mmpww5_mmpww7_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_mmpww5_mmpww7_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 pcwk0_cwk_swc = {
	.cmd_wcgw = 0x2000,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = mmcc_xo_dsi0pww_dsi1pww_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "pcwk0_cwk_swc",
		.pawent_data = mmcc_xo_dsi0pww_dsi1pww,
		.num_pawents = AWWAY_SIZE(mmcc_xo_dsi0pww_dsi1pww),
		.ops = &cwk_pixew_ops,
		.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
	},
};

static stwuct cwk_wcg2 pcwk1_cwk_swc = {
	.cmd_wcgw = 0x2020,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = mmcc_xo_dsi0pww_dsi1pww_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "pcwk1_cwk_swc",
		.pawent_data = mmcc_xo_dsi0pww_dsi1pww,
		.num_pawents = AWWAY_SIZE(mmcc_xo_dsi0pww_dsi1pww),
		.ops = &cwk_pixew_ops,
		.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
	},
};

static const stwuct fweq_tbw ftbw_wot_cwk_swc[] = {
	F(171428571, P_GPWW0, 3.5, 0, 0),
	F(275000000, P_MMPWW5, 3, 0, 0),
	F(300000000, P_GPWW0, 2, 0, 0),
	F(330000000, P_MMPWW5, 2.5, 0, 0),
	F(412500000, P_MMPWW5, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 wot_cwk_swc = {
	.cmd_wcgw = 0x21a0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_mmpww5_mmpww7_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_wot_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "wot_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_mmpww5_mmpww7_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_mmpww5_mmpww7_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_vfe0_cwk_swc[] = {
	F(120000000, P_GPWW0, 5, 0, 0),
	F(200000000, P_GPWW0, 3, 0, 0),
	F(256000000, P_MMPWW4, 3, 0, 0),
	F(300000000, P_GPWW0, 2, 0, 0),
	F(404000000, P_MMPWW0, 2, 0, 0),
	F(480000000, P_MMPWW7, 2, 0, 0),
	F(540000000, P_MMPWW6, 2, 0, 0),
	F(576000000, P_MMPWW10, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 vfe0_cwk_swc = {
	.cmd_wcgw = 0x3600,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_mmpww0_mmpww4_mmpww7_mmpww10_mmpww6_gpww0_map,
	.fweq_tbw = ftbw_vfe0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "vfe0_cwk_swc",
		.pawent_data = mmcc_mmpww0_mmpww4_mmpww7_mmpww10_mmpww6_gpww0,
		.num_pawents = AWWAY_SIZE(mmcc_mmpww0_mmpww4_mmpww7_mmpww10_mmpww6_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 vfe1_cwk_swc = {
	.cmd_wcgw = 0x3620,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_mmpww0_mmpww4_mmpww7_mmpww10_mmpww6_gpww0_map,
	.fweq_tbw = ftbw_vfe0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "vfe1_cwk_swc",
		.pawent_data = mmcc_mmpww0_mmpww4_mmpww7_mmpww10_mmpww6_gpww0,
		.num_pawents = AWWAY_SIZE(mmcc_mmpww0_mmpww4_mmpww7_mmpww10_mmpww6_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_video_cowe_cwk_swc[] = {
	F(133333333, P_GPWW0, 4.5, 0, 0),
	F(269333333, P_MMPWW0, 3, 0, 0),
	F(320000000, P_MMPWW7, 3, 0, 0),
	F(404000000, P_MMPWW0, 2, 0, 0),
	F(441600000, P_MMPWW3, 2, 0, 0),
	F(518400000, P_MMPWW3, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 video_cowe_cwk_swc = {
	.cmd_wcgw = 0x1000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_mmpww8_mmpww3_mmpww6_gpww0_mmpww7_map,
	.fweq_tbw = ftbw_video_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "video_cowe_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_mmpww8_mmpww3_mmpww6_gpww0_mmpww7,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_mmpww8_mmpww3_mmpww6_gpww0_mmpww7),
		.ops = &cwk_wcg2_ops,
		.fwags = CWK_IS_CWITICAW,
	},
};

static stwuct cwk_wcg2 vsync_cwk_swc = {
	.cmd_wcgw = 0x2080,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = mmcc_xo_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_dp_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "vsync_cwk_swc",
		.pawent_data = mmcc_xo_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch bimc_smmu_ahb_cwk = {
	.hawt_weg = 0xe004,
	.hawt_check = BWANCH_VOTED,
	.hwcg_weg = 0xe004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0xe004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "bimc_smmu_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch bimc_smmu_axi_cwk = {
	.hawt_weg = 0xe008,
	.hawt_check = BWANCH_VOTED,
	.hwcg_weg = 0xe008,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0xe008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "bimc_smmu_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_ahb_cwk = {
	.hawt_weg = 0x348c,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x348c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x348c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_cci_ahb_cwk = {
	.hawt_weg = 0x3348,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3348,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_cci_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_cci_cwk = {
	.hawt_weg = 0x3344,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3344,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_cci_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &cci_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_cpp_ahb_cwk = {
	.hawt_weg = 0x36b4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x36b4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_cpp_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_cpp_axi_cwk = {
	.hawt_weg = 0x36c4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x36c4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_cpp_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_cpp_cwk = {
	.hawt_weg = 0x36b0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x36b0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_cpp_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &cpp_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_cpp_vbif_ahb_cwk = {
	.hawt_weg = 0x36c8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x36c8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_cpp_vbif_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi0_ahb_cwk = {
	.hawt_weg = 0x30bc,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x30bc,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi0_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi0_cwk = {
	.hawt_weg = 0x30b4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x30b4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi0_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csi0_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi0phytimew_cwk = {
	.hawt_weg = 0x3024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi0phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csi0phytimew_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi0pix_cwk = {
	.hawt_weg = 0x30e4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x30e4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi0pix_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csi0_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi0wdi_cwk = {
	.hawt_weg = 0x30d4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x30d4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi0wdi_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csi0_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi1_ahb_cwk = {
	.hawt_weg = 0x3128,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3128,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi1_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi1_cwk = {
	.hawt_weg = 0x3124,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3124,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi1_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csi1_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi1phytimew_cwk = {
	.hawt_weg = 0x3054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi1phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csi1phytimew_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi1pix_cwk = {
	.hawt_weg = 0x3154,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3154,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi1pix_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csi1_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi1wdi_cwk = {
	.hawt_weg = 0x3144,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3144,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi1wdi_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csi1_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi2_ahb_cwk = {
	.hawt_weg = 0x3188,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3188,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi2_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi2_cwk = {
	.hawt_weg = 0x3184,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3184,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi2_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csi2_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi2phytimew_cwk = {
	.hawt_weg = 0x3084,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3084,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi2phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csi2phytimew_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi2pix_cwk = {
	.hawt_weg = 0x31b4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x31b4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi2pix_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csi2_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi2wdi_cwk = {
	.hawt_weg = 0x31a4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x31a4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi2wdi_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csi2_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi3_ahb_cwk = {
	.hawt_weg = 0x31e8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x31e8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi3_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi3_cwk = {
	.hawt_weg = 0x31e4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x31e4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi3_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csi3_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi3pix_cwk = {
	.hawt_weg = 0x3214,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3214,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi3pix_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csi3_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi3wdi_cwk = {
	.hawt_weg = 0x3204,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3204,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi3wdi_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csi3_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi_vfe0_cwk = {
	.hawt_weg = 0x3704,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3704,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi_vfe0_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &vfe0_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csi_vfe1_cwk = {
	.hawt_weg = 0x3714,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3714,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csi_vfe1_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &vfe1_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csiphy0_cwk = {
	.hawt_weg = 0x3740,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3740,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csiphy0_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csiphy_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csiphy1_cwk = {
	.hawt_weg = 0x3744,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3744,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csiphy1_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csiphy_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_csiphy2_cwk = {
	.hawt_weg = 0x3748,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3748,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_csiphy2_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csiphy_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};


static stwuct cwk_bwanch camss_cphy_csid0_cwk = {
	.hawt_weg = 0x3730,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3730,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_cphy_csid0_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &camss_csiphy0_cwk.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_cphy_csid1_cwk = {
	.hawt_weg = 0x3734,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3734,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_cphy_csid1_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &camss_csiphy1_cwk.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_cphy_csid2_cwk = {
	.hawt_weg = 0x3738,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3738,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_cphy_csid2_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &camss_csiphy2_cwk.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_cphy_csid3_cwk = {
	.hawt_weg = 0x373c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x373c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_cphy_csid3_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &csiphy_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_gp0_cwk = {
	.hawt_weg = 0x3444,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3444,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_gp0_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &camss_gp0_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_gp1_cwk = {
	.hawt_weg = 0x3474,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3474,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_gp1_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &camss_gp1_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_ispif_ahb_cwk = {
	.hawt_weg = 0x3224,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3224,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_ispif_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_jpeg0_cwk = {
	.hawt_weg = 0x35a8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x35a8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_jpeg0_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &jpeg0_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_jpeg_ahb_cwk = {
	.hawt_weg = 0x35b4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x35b4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_jpeg_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_jpeg_axi_cwk = {
	.hawt_weg = 0x35b8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x35b8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_jpeg_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch thwottwe_camss_axi_cwk = {
	.hawt_weg = 0x3c3c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3c3c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "thwottwe_camss_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_mcwk0_cwk = {
	.hawt_weg = 0x3384,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3384,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_mcwk0_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &mcwk0_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_mcwk1_cwk = {
	.hawt_weg = 0x33b4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x33b4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_mcwk1_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &mcwk1_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_mcwk2_cwk = {
	.hawt_weg = 0x33e4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x33e4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_mcwk2_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &mcwk2_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_mcwk3_cwk = {
	.hawt_weg = 0x3414,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3414,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_mcwk3_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &mcwk3_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_micwo_ahb_cwk = {
	.hawt_weg = 0x3494,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3494,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_micwo_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_top_ahb_cwk = {
	.hawt_weg = 0x3484,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3484,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_top_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_vfe0_ahb_cwk = {
	.hawt_weg = 0x3668,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3668,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_vfe0_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_vfe0_cwk = {
	.hawt_weg = 0x36a8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x36a8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_vfe0_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &vfe0_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_vfe0_stweam_cwk = {
	.hawt_weg = 0x3720,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3720,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_vfe0_stweam_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &vfe0_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_vfe1_ahb_cwk = {
	.hawt_weg = 0x3678,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3678,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_vfe1_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_vfe1_cwk = {
	.hawt_weg = 0x36ac,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x36ac,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_vfe1_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &vfe1_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_vfe1_stweam_cwk = {
	.hawt_weg = 0x3724,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x3724,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_vfe1_stweam_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &vfe1_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_vfe_vbif_ahb_cwk = {
	.hawt_weg = 0x36b8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x36b8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_vfe_vbif_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch camss_vfe_vbif_axi_cwk = {
	.hawt_weg = 0x36bc,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x36bc,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "camss_vfe_vbif_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch csiphy_ahb2cwif_cwk = {
	.hawt_weg = 0x374c,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x374c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x374c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "csiphy_ahb2cwif_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch mdss_ahb_cwk = {
	.hawt_weg = 0x2308,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x8a004,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x2308,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.fwags = CWK_SET_WATE_PAWENT,
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static const stwuct fweq_tbw ftbw_axi_cwk_swc[] = {
		F(75000000, P_GPWW0, 8, 0, 0),
		F(171428571, P_GPWW0, 3.5, 0, 0),
		F(240000000, P_GPWW0, 2.5, 0, 0),
		F(323200000, P_MMPWW0, 2.5, 0, 0),
		F(406000000, P_MMPWW0, 2, 0, 0),
		{ }
};

/* WO to winux */
static stwuct cwk_wcg2 axi_cwk_swc = {
	.cmd_wcgw = 0xd000,
	.hid_width = 5,
	.pawent_map = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_gpww0_div_map,
	.fweq_tbw = ftbw_axi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "axi_cwk_swc",
		.pawent_data = mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_gpww0_div,
		.num_pawents = AWWAY_SIZE(mmcc_xo_mmpww0_mmpww4_mmpww7_mmpww10_gpww0_gpww0_div),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch mdss_axi_cwk = {
	.hawt_weg = 0x2310,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2310,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &axi_cwk_swc.cwkw.hw },
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch thwottwe_mdss_axi_cwk = {
	.hawt_weg = 0x246c,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x246c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x246c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "thwottwe_mdss_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch mdss_byte0_cwk = {
	.hawt_weg = 0x233c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x233c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_byte0_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &byte0_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_wegmap_div mdss_byte0_intf_div_cwk = {
	.weg = 0x237c,
	.shift = 0,
	.width = 2,
	/*
	 * NOTE: Op does not wowk fow div-3. Cuwwent assumption is that div-3
	 * is not a wecommended setting fow this dividew.
	 */
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_byte0_intf_div_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &byte0_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_wegmap_div_ops,
			.fwags = CWK_GET_WATE_NOCACHE,
		},
	},
};

static stwuct cwk_bwanch mdss_byte0_intf_cwk = {
	.hawt_weg = 0x2374,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2374,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_byte0_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &mdss_byte0_intf_div_cwk.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch mdss_byte1_cwk = {
	.hawt_weg = 0x2340,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2340,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_byte1_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &byte1_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_wegmap_div mdss_byte1_intf_div_cwk = {
	.weg = 0x2380,
	.shift = 0,
	.width = 2,
	/*
	 * NOTE: Op does not wowk fow div-3. Cuwwent assumption is that div-3
	 * is not a wecommended setting fow this dividew.
	 */
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_byte1_intf_div_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &byte1_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_wegmap_div_ops,
			.fwags = CWK_GET_WATE_NOCACHE,
		},
	},
};

static stwuct cwk_bwanch mdss_byte1_intf_cwk = {
	.hawt_weg = 0x2378,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2378,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_byte1_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &mdss_byte1_intf_div_cwk.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch mdss_dp_aux_cwk = {
	.hawt_weg = 0x2364,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2364,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_dp_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &dp_aux_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch mdss_dp_cwypto_cwk = {
	.hawt_weg = 0x235c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x235c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_dp_cwypto_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &dp_cwypto_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch mdss_dp_gtc_cwk = {
	.hawt_weg = 0x2368,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2368,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_dp_gtc_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &dp_gtc_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch mdss_dp_wink_cwk = {
	.hawt_weg = 0x2354,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2354,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_dp_wink_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &dp_wink_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_GET_WATE_NOCACHE | CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

/* Weset state of MDSS_DP_WINK_INTF_DIV is 0x3 (div-4) */
static stwuct cwk_bwanch mdss_dp_wink_intf_cwk = {
	.hawt_weg = 0x2358,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2358,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_dp_wink_intf_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &dp_wink_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch mdss_dp_pixew_cwk = {
	.hawt_weg = 0x2360,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2360,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_dp_pixew_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &dp_pixew_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_GET_WATE_NOCACHE | CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch mdss_esc0_cwk = {
	.hawt_weg = 0x2344,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2344,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_esc0_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &esc0_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch mdss_esc1_cwk = {
	.hawt_weg = 0x2348,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2348,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_esc1_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &esc1_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch mdss_hdmi_dp_ahb_cwk = {
	.hawt_weg = 0x230c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x230c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_hdmi_dp_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch mdss_mdp_cwk = {
	.hawt_weg = 0x231c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x231c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_mdp_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &mdp_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch mdss_pcwk0_cwk = {
	.hawt_weg = 0x2314,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2314,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_pcwk0_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &pcwk0_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch mdss_pcwk1_cwk = {
	.hawt_weg = 0x2318,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2318,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_pcwk1_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &pcwk1_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch mdss_wot_cwk = {
	.hawt_weg = 0x2350,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2350,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_wot_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &wot_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch mdss_vsync_cwk = {
	.hawt_weg = 0x2328,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2328,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mdss_vsync_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &vsync_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch mnoc_ahb_cwk = {
	.hawt_weg = 0x5024,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x5024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "mnoc_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch misc_ahb_cwk = {
	.hawt_weg = 0x328,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x328,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x328,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "misc_ahb_cwk",
			/*
			 * Dependency to be enabwed befowe the bwanch is
			 * enabwed.
			 */
			.pawent_hws = (const stwuct cwk_hw *[]){ &mnoc_ahb_cwk.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch misc_cxo_cwk = {
	.hawt_weg = 0x324,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x324,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "misc_cxo_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch snoc_dvm_axi_cwk = {
	.hawt_weg = 0xe040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xe040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "snoc_dvm_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_ahb_cwk = {
	.hawt_weg = 0x1030,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x1030,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x1030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &ahb_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_axi_cwk = {
	.hawt_weg = 0x1034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch thwottwe_video_axi_cwk = {
	.hawt_weg = 0x118c,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x118c,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x118c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "thwottwe_video_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cowe_cwk = {
	.hawt_weg = 0x1028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &video_cowe_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_subcowe0_cwk = {
	.hawt_weg = 0x1048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1048,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_subcowe0_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){ &video_cowe_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT | CWK_GET_WATE_NOCACHE,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc venus_gdsc = {
	.gdscw = 0x1024,
	.cxcs = (unsigned int[]){ 0x1028, 0x1034, 0x1048 },
	.cxc_count = 3,
	.pd = {
		.name = "venus",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc venus_cowe0_gdsc = {
	.gdscw = 0x1040,
	.pd = {
		.name = "venus_cowe0",
	},
	.pawent = &venus_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = HW_CTWW,
};

static stwuct gdsc mdss_gdsc = {
	.gdscw = 0x2304,
	.pd = {
		.name = "mdss",
	},
	.cxcs = (unsigned int []){ 0x2040 },
	.cxc_count = 1,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc camss_top_gdsc = {
	.gdscw = 0x34a0,
	.pd = {
		.name = "camss_top",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc camss_vfe0_gdsc = {
	.gdscw = 0x3664,
	.pd = {
		.name = "camss_vfe0",
	},
	.pawent = &camss_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc camss_vfe1_gdsc = {
	.gdscw = 0x3674,
	.pd = {
		.name = "camss_vfe1_gdsc",
	},
	.pawent = &camss_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc camss_cpp_gdsc = {
	.gdscw = 0x36d4,
	.pd = {
		.name = "camss_cpp",
	},
	.pawent = &camss_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

/* This GDSC seems to hang the whowe muwtimedia subsystem.
static stwuct gdsc bimc_smmu_gdsc = {
	.gdscw = 0xe020,
	.gds_hw_ctww = 0xe024,
	.pd = {
		.name = "bimc_smmu",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.pawent = &bimc_smmu_gdsc.pd,
	.fwags = HW_CTWW,
};
*/

static stwuct cwk_wegmap *mmcc_660_cwocks[] = {
	[AHB_CWK_SWC] = &ahb_cwk_swc.cwkw,
	[BYTE0_CWK_SWC] = &byte0_cwk_swc.cwkw,
	[BYTE1_CWK_SWC] = &byte1_cwk_swc.cwkw,
	[CAMSS_GP0_CWK_SWC] = &camss_gp0_cwk_swc.cwkw,
	[CAMSS_GP1_CWK_SWC] = &camss_gp1_cwk_swc.cwkw,
	[CCI_CWK_SWC] = &cci_cwk_swc.cwkw,
	[CPP_CWK_SWC] = &cpp_cwk_swc.cwkw,
	[CSI0_CWK_SWC] = &csi0_cwk_swc.cwkw,
	[CSI0PHYTIMEW_CWK_SWC] = &csi0phytimew_cwk_swc.cwkw,
	[CSI1_CWK_SWC] = &csi1_cwk_swc.cwkw,
	[CSI1PHYTIMEW_CWK_SWC] = &csi1phytimew_cwk_swc.cwkw,
	[CSI2_CWK_SWC] = &csi2_cwk_swc.cwkw,
	[CSI2PHYTIMEW_CWK_SWC] = &csi2phytimew_cwk_swc.cwkw,
	[CSI3_CWK_SWC] = &csi3_cwk_swc.cwkw,
	[CSIPHY_CWK_SWC] = &csiphy_cwk_swc.cwkw,
	[DP_AUX_CWK_SWC] = &dp_aux_cwk_swc.cwkw,
	[DP_CWYPTO_CWK_SWC] = &dp_cwypto_cwk_swc.cwkw,
	[DP_GTC_CWK_SWC] = &dp_gtc_cwk_swc.cwkw,
	[DP_WINK_CWK_SWC] = &dp_wink_cwk_swc.cwkw,
	[DP_PIXEW_CWK_SWC] = &dp_pixew_cwk_swc.cwkw,
	[ESC0_CWK_SWC] = &esc0_cwk_swc.cwkw,
	[ESC1_CWK_SWC] = &esc1_cwk_swc.cwkw,
	[JPEG0_CWK_SWC] = &jpeg0_cwk_swc.cwkw,
	[MCWK0_CWK_SWC] = &mcwk0_cwk_swc.cwkw,
	[MCWK1_CWK_SWC] = &mcwk1_cwk_swc.cwkw,
	[MCWK2_CWK_SWC] = &mcwk2_cwk_swc.cwkw,
	[MCWK3_CWK_SWC] = &mcwk3_cwk_swc.cwkw,
	[MDP_CWK_SWC] = &mdp_cwk_swc.cwkw,
	[MMPWW0_PWW] = &mmpww0.cwkw,
	[MMPWW10_PWW] = &mmpww10.cwkw,
	[MMPWW3_PWW] = &mmpww3.cwkw,
	[MMPWW4_PWW] = &mmpww4.cwkw,
	[MMPWW5_PWW] = &mmpww5.cwkw,
	[MMPWW6_PWW] = &mmpww6.cwkw,
	[MMPWW7_PWW] = &mmpww7.cwkw,
	[MMPWW8_PWW] = &mmpww8.cwkw,
	[BIMC_SMMU_AHB_CWK] = &bimc_smmu_ahb_cwk.cwkw,
	[BIMC_SMMU_AXI_CWK] = &bimc_smmu_axi_cwk.cwkw,
	[CAMSS_AHB_CWK] = &camss_ahb_cwk.cwkw,
	[CAMSS_CCI_AHB_CWK] = &camss_cci_ahb_cwk.cwkw,
	[CAMSS_CCI_CWK] = &camss_cci_cwk.cwkw,
	[CAMSS_CPHY_CSID0_CWK] = &camss_cphy_csid0_cwk.cwkw,
	[CAMSS_CPHY_CSID1_CWK] = &camss_cphy_csid1_cwk.cwkw,
	[CAMSS_CPHY_CSID2_CWK] = &camss_cphy_csid2_cwk.cwkw,
	[CAMSS_CPHY_CSID3_CWK] = &camss_cphy_csid3_cwk.cwkw,
	[CAMSS_CPP_AHB_CWK] = &camss_cpp_ahb_cwk.cwkw,
	[CAMSS_CPP_AXI_CWK] = &camss_cpp_axi_cwk.cwkw,
	[CAMSS_CPP_CWK] = &camss_cpp_cwk.cwkw,
	[CAMSS_CPP_VBIF_AHB_CWK] = &camss_cpp_vbif_ahb_cwk.cwkw,
	[CAMSS_CSI0_AHB_CWK] = &camss_csi0_ahb_cwk.cwkw,
	[CAMSS_CSI0_CWK] = &camss_csi0_cwk.cwkw,
	[CAMSS_CSI0PHYTIMEW_CWK] = &camss_csi0phytimew_cwk.cwkw,
	[CAMSS_CSI0PIX_CWK] = &camss_csi0pix_cwk.cwkw,
	[CAMSS_CSI0WDI_CWK] = &camss_csi0wdi_cwk.cwkw,
	[CAMSS_CSI1_AHB_CWK] = &camss_csi1_ahb_cwk.cwkw,
	[CAMSS_CSI1_CWK] = &camss_csi1_cwk.cwkw,
	[CAMSS_CSI1PHYTIMEW_CWK] = &camss_csi1phytimew_cwk.cwkw,
	[CAMSS_CSI1PIX_CWK] = &camss_csi1pix_cwk.cwkw,
	[CAMSS_CSI1WDI_CWK] = &camss_csi1wdi_cwk.cwkw,
	[CAMSS_CSI2_AHB_CWK] = &camss_csi2_ahb_cwk.cwkw,
	[CAMSS_CSI2_CWK] = &camss_csi2_cwk.cwkw,
	[CAMSS_CSI2PHYTIMEW_CWK] = &camss_csi2phytimew_cwk.cwkw,
	[CAMSS_CSI2PIX_CWK] = &camss_csi2pix_cwk.cwkw,
	[CAMSS_CSI2WDI_CWK] = &camss_csi2wdi_cwk.cwkw,
	[CAMSS_CSI3_AHB_CWK] = &camss_csi3_ahb_cwk.cwkw,
	[CAMSS_CSI3_CWK] = &camss_csi3_cwk.cwkw,
	[CAMSS_CSI3PIX_CWK] = &camss_csi3pix_cwk.cwkw,
	[CAMSS_CSI3WDI_CWK] = &camss_csi3wdi_cwk.cwkw,
	[CAMSS_CSI_VFE0_CWK] = &camss_csi_vfe0_cwk.cwkw,
	[CAMSS_CSI_VFE1_CWK] = &camss_csi_vfe1_cwk.cwkw,
	[CAMSS_CSIPHY0_CWK] = &camss_csiphy0_cwk.cwkw,
	[CAMSS_CSIPHY1_CWK] = &camss_csiphy1_cwk.cwkw,
	[CAMSS_CSIPHY2_CWK] = &camss_csiphy2_cwk.cwkw,
	[CAMSS_GP0_CWK] = &camss_gp0_cwk.cwkw,
	[CAMSS_GP1_CWK] = &camss_gp1_cwk.cwkw,
	[CAMSS_ISPIF_AHB_CWK] = &camss_ispif_ahb_cwk.cwkw,
	[CAMSS_JPEG0_CWK] = &camss_jpeg0_cwk.cwkw,
	[CAMSS_JPEG_AHB_CWK] = &camss_jpeg_ahb_cwk.cwkw,
	[CAMSS_JPEG_AXI_CWK] = &camss_jpeg_axi_cwk.cwkw,
	[CAMSS_MCWK0_CWK] = &camss_mcwk0_cwk.cwkw,
	[CAMSS_MCWK1_CWK] = &camss_mcwk1_cwk.cwkw,
	[CAMSS_MCWK2_CWK] = &camss_mcwk2_cwk.cwkw,
	[CAMSS_MCWK3_CWK] = &camss_mcwk3_cwk.cwkw,
	[CAMSS_MICWO_AHB_CWK] = &camss_micwo_ahb_cwk.cwkw,
	[CAMSS_TOP_AHB_CWK] = &camss_top_ahb_cwk.cwkw,
	[CAMSS_VFE0_AHB_CWK] = &camss_vfe0_ahb_cwk.cwkw,
	[CAMSS_VFE0_CWK] = &camss_vfe0_cwk.cwkw,
	[CAMSS_VFE0_STWEAM_CWK] = &camss_vfe0_stweam_cwk.cwkw,
	[CAMSS_VFE1_AHB_CWK] = &camss_vfe1_ahb_cwk.cwkw,
	[CAMSS_VFE1_CWK] = &camss_vfe1_cwk.cwkw,
	[CAMSS_VFE1_STWEAM_CWK] = &camss_vfe1_stweam_cwk.cwkw,
	[CAMSS_VFE_VBIF_AHB_CWK] = &camss_vfe_vbif_ahb_cwk.cwkw,
	[CAMSS_VFE_VBIF_AXI_CWK] = &camss_vfe_vbif_axi_cwk.cwkw,
	[CSIPHY_AHB2CWIF_CWK] = &csiphy_ahb2cwif_cwk.cwkw,
	[MDSS_AHB_CWK] = &mdss_ahb_cwk.cwkw,
	[MDSS_AXI_CWK] = &mdss_axi_cwk.cwkw,
	[MDSS_BYTE0_CWK] = &mdss_byte0_cwk.cwkw,
	[MDSS_BYTE0_INTF_CWK] = &mdss_byte0_intf_cwk.cwkw,
	[MDSS_BYTE0_INTF_DIV_CWK] = &mdss_byte0_intf_div_cwk.cwkw,
	[MDSS_BYTE1_CWK] = &mdss_byte1_cwk.cwkw,
	[MDSS_BYTE1_INTF_CWK] = &mdss_byte1_intf_cwk.cwkw,
	[MDSS_DP_AUX_CWK] = &mdss_dp_aux_cwk.cwkw,
	[MDSS_DP_CWYPTO_CWK] = &mdss_dp_cwypto_cwk.cwkw,
	[MDSS_DP_GTC_CWK] = &mdss_dp_gtc_cwk.cwkw,
	[MDSS_DP_WINK_CWK] = &mdss_dp_wink_cwk.cwkw,
	[MDSS_DP_WINK_INTF_CWK] = &mdss_dp_wink_intf_cwk.cwkw,
	[MDSS_DP_PIXEW_CWK] = &mdss_dp_pixew_cwk.cwkw,
	[MDSS_ESC0_CWK] = &mdss_esc0_cwk.cwkw,
	[MDSS_ESC1_CWK] = &mdss_esc1_cwk.cwkw,
	[MDSS_HDMI_DP_AHB_CWK] = &mdss_hdmi_dp_ahb_cwk.cwkw,
	[MDSS_MDP_CWK] = &mdss_mdp_cwk.cwkw,
	[MDSS_PCWK0_CWK] = &mdss_pcwk0_cwk.cwkw,
	[MDSS_PCWK1_CWK] = &mdss_pcwk1_cwk.cwkw,
	[MDSS_WOT_CWK] = &mdss_wot_cwk.cwkw,
	[MDSS_VSYNC_CWK] = &mdss_vsync_cwk.cwkw,
	[MISC_AHB_CWK] = &misc_ahb_cwk.cwkw,
	[MISC_CXO_CWK] = &misc_cxo_cwk.cwkw,
	[MNOC_AHB_CWK] = &mnoc_ahb_cwk.cwkw,
	[SNOC_DVM_AXI_CWK] = &snoc_dvm_axi_cwk.cwkw,
	[THWOTTWE_CAMSS_AXI_CWK] = &thwottwe_camss_axi_cwk.cwkw,
	[THWOTTWE_MDSS_AXI_CWK] = &thwottwe_mdss_axi_cwk.cwkw,
	[THWOTTWE_VIDEO_AXI_CWK] = &thwottwe_video_axi_cwk.cwkw,
	[VIDEO_AHB_CWK] = &video_ahb_cwk.cwkw,
	[VIDEO_AXI_CWK] = &video_axi_cwk.cwkw,
	[VIDEO_COWE_CWK] = &video_cowe_cwk.cwkw,
	[VIDEO_SUBCOWE0_CWK] = &video_subcowe0_cwk.cwkw,
	[PCWK0_CWK_SWC] = &pcwk0_cwk_swc.cwkw,
	[PCWK1_CWK_SWC] = &pcwk1_cwk_swc.cwkw,
	[WOT_CWK_SWC] = &wot_cwk_swc.cwkw,
	[VFE0_CWK_SWC] = &vfe0_cwk_swc.cwkw,
	[VFE1_CWK_SWC] = &vfe1_cwk_swc.cwkw,
	[VIDEO_COWE_CWK_SWC] = &video_cowe_cwk_swc.cwkw,
	[VSYNC_CWK_SWC] = &vsync_cwk_swc.cwkw,
	[MDSS_BYTE1_INTF_DIV_CWK] = &mdss_byte1_intf_div_cwk.cwkw,
	[AXI_CWK_SWC] = &axi_cwk_swc.cwkw,
};

static stwuct gdsc *mmcc_sdm660_gdscs[] = {
	[VENUS_GDSC] = &venus_gdsc,
	[VENUS_COWE0_GDSC] = &venus_cowe0_gdsc,
	[MDSS_GDSC] = &mdss_gdsc,
	[CAMSS_TOP_GDSC] = &camss_top_gdsc,
	[CAMSS_VFE0_GDSC] = &camss_vfe0_gdsc,
	[CAMSS_VFE1_GDSC] = &camss_vfe1_gdsc,
	[CAMSS_CPP_GDSC] = &camss_cpp_gdsc,
};

static const stwuct qcom_weset_map mmcc_660_wesets[] = {
	[CAMSS_MICWO_BCW] = { 0x3490 },
};

static const stwuct wegmap_config mmcc_660_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x40000,
	.fast_io	= twue,
};

static const stwuct qcom_cc_desc mmcc_660_desc = {
	.config = &mmcc_660_wegmap_config,
	.cwks = mmcc_660_cwocks,
	.num_cwks = AWWAY_SIZE(mmcc_660_cwocks),
	.wesets = mmcc_660_wesets,
	.num_wesets = AWWAY_SIZE(mmcc_660_wesets),
	.gdscs = mmcc_sdm660_gdscs,
	.num_gdscs = AWWAY_SIZE(mmcc_sdm660_gdscs),
};

static const stwuct of_device_id mmcc_660_match_tabwe[] = {
	{ .compatibwe = "qcom,mmcc-sdm660" },
	{ .compatibwe = "qcom,mmcc-sdm630", .data = (void *)1UW },
	{ }
};
MODUWE_DEVICE_TABWE(of, mmcc_660_match_tabwe);

static void sdm630_cwock_ovewwide(void)
{
	/* SDM630 has onwy one DSI */
	mmcc_660_desc.cwks[BYTE1_CWK_SWC] = NUWW;
	mmcc_660_desc.cwks[MDSS_BYTE1_CWK] = NUWW;
	mmcc_660_desc.cwks[MDSS_BYTE1_INTF_DIV_CWK] = NUWW;
	mmcc_660_desc.cwks[MDSS_BYTE1_INTF_CWK] = NUWW;
	mmcc_660_desc.cwks[ESC1_CWK_SWC] = NUWW;
	mmcc_660_desc.cwks[MDSS_ESC1_CWK] = NUWW;
	mmcc_660_desc.cwks[PCWK1_CWK_SWC] = NUWW;
	mmcc_660_desc.cwks[MDSS_PCWK1_CWK] = NUWW;
}

static int mmcc_660_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	boow is_sdm630;

	is_sdm630 = !!device_get_match_data(&pdev->dev);

	wegmap = qcom_cc_map(pdev, &mmcc_660_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	if (is_sdm630)
		sdm630_cwock_ovewwide();

	cwk_awpha_pww_configuwe(&mmpww3, wegmap, &mmpww3_config);
	cwk_awpha_pww_configuwe(&mmpww4, wegmap, &mmpww4_config);
	cwk_awpha_pww_configuwe(&mmpww5, wegmap, &mmpww5_config);
	cwk_awpha_pww_configuwe(&mmpww7, wegmap, &mmpww7_config);
	cwk_awpha_pww_configuwe(&mmpww8, wegmap, &mmpww8_config);
	cwk_awpha_pww_configuwe(&mmpww10, wegmap, &mmpww10_config);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &mmcc_660_desc, wegmap);
}

static stwuct pwatfowm_dwivew mmcc_660_dwivew = {
	.pwobe		= mmcc_660_pwobe,
	.dwivew		= {
		.name	= "mmcc-sdm660",
		.of_match_tabwe = mmcc_660_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(mmcc_660_dwivew);

MODUWE_DESCWIPTION("Quawcomm SDM630/SDM660 MMCC dwivew");
MODUWE_WICENSE("GPW v2");
