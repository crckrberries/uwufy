// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
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

#incwude <dt-bindings/cwock/qcom,gcc-msm8996.h>

#incwude "common.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-awpha-pww.h"
#incwude "cwk-wcg.h"
#incwude "cwk-bwanch.h"
#incwude "weset.h"
#incwude "gdsc.h"

enum {
	P_XO,
	P_GPWW0,
	P_GPWW0_EAWWY_DIV,
	P_SWEEP_CWK,
	P_GPWW4,
	P_AUD_WEF_CWK,
};

static stwuct cwk_fixed_factow xo = {
	.muwt = 1,
	.div = 1,
	.hw.init = &(stwuct cwk_init_data){
		.name = "xo",
		.pawent_data = &(const stwuct cwk_pawent_data){
			.fw_name = "cxo", .name = "xo_boawd",
		},
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_awpha_pww gpww0_eawwy = {
	.offset = 0x00000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww0_eawwy",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "cxo", .name = "xo_boawd",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static stwuct cwk_fixed_factow gpww0_eawwy_div = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "gpww0_eawwy_div",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww0_eawwy.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_awpha_pww_postdiv gpww0 = {
	.offset = 0x00000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpww0",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww0_eawwy.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_ops,
	},
};

static stwuct cwk_bwanch gcc_mmss_gpww0_div_cwk = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x5200c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mmss_gpww0_div_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpww0.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mss_gpww0_div_cwk = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x5200c,
		.enabwe_mask = BIT(2),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mss_gpww0_div_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpww0.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops
		},
	},
};

static stwuct cwk_awpha_pww gpww4_eawwy = {
	.offset = 0x77000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.enabwe_weg = 0x52000,
		.enabwe_mask = BIT(4),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpww4_eawwy",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "cxo", .name = "xo_boawd",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static stwuct cwk_awpha_pww_postdiv gpww4 = {
	.offset = 0x77000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpww4",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpww4_eawwy.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_ops,
	},
};

static const stwuct pawent_map gcc_sweep_cwk_map[] = {
	{ P_SWEEP_CWK, 5 }
};

static const stwuct cwk_pawent_data gcc_sweep_cwk[] = {
	{ .fw_name = "sweep_cwk", .name = "sweep_cwk" }
};

static const stwuct pawent_map gcc_xo_gpww0_map[] = {
	{ P_XO, 0 },
	{ P_GPWW0, 1 }
};

static const stwuct cwk_pawent_data gcc_xo_gpww0[] = {
	{ .fw_name = "cxo", .name = "xo_boawd" },
	{ .hw = &gpww0.cwkw.hw }
};

static const stwuct pawent_map gcc_xo_sweep_cwk_map[] = {
	{ P_XO, 0 },
	{ P_SWEEP_CWK, 5 }
};

static const stwuct cwk_pawent_data gcc_xo_sweep_cwk[] = {
	{ .fw_name = "cxo", .name = "xo_boawd" },
	{ .fw_name = "sweep_cwk", .name = "sweep_cwk" }
};

static const stwuct pawent_map gcc_xo_gpww0_gpww0_eawwy_div_map[] = {
	{ P_XO, 0 },
	{ P_GPWW0, 1 },
	{ P_GPWW0_EAWWY_DIV, 6 }
};

static const stwuct cwk_pawent_data gcc_xo_gpww0_gpww0_eawwy_div[] = {
	{ .fw_name = "cxo", .name = "xo_boawd" },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww0_eawwy_div.hw }
};

static const stwuct pawent_map gcc_xo_gpww0_gpww4_map[] = {
	{ P_XO, 0 },
	{ P_GPWW0, 1 },
	{ P_GPWW4, 5 }
};

static const stwuct cwk_pawent_data gcc_xo_gpww0_gpww4[] = {
	{ .fw_name = "cxo", .name = "xo_boawd" },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww4.cwkw.hw }
};

static const stwuct pawent_map gcc_xo_gpww0_aud_wef_cwk_map[] = {
	{ P_XO, 0 },
	{ P_GPWW0, 1 },
	{ P_AUD_WEF_CWK, 2 }
};

static const stwuct cwk_pawent_data gcc_xo_gpww0_aud_wef_cwk[] = {
	{ .fw_name = "cxo", .name = "xo_boawd" },
	{ .hw = &gpww0.cwkw.hw },
	{ .fw_name = "aud_wef_cwk", .name = "aud_wef_cwk" }
};

static const stwuct pawent_map gcc_xo_gpww0_sweep_cwk_gpww0_eawwy_div_map[] = {
	{ P_XO, 0 },
	{ P_GPWW0, 1 },
	{ P_SWEEP_CWK, 5 },
	{ P_GPWW0_EAWWY_DIV, 6 }
};

static const stwuct cwk_pawent_data gcc_xo_gpww0_sweep_cwk_gpww0_eawwy_div[] = {
	{ .fw_name = "cxo", .name = "xo_boawd" },
	{ .hw = &gpww0.cwkw.hw },
	{ .fw_name = "sweep_cwk", .name = "sweep_cwk" },
	{ .hw = &gpww0_eawwy_div.hw }
};

static const stwuct pawent_map gcc_xo_gpww0_gpww4_gpww0_eawwy_div_map[] = {
	{ P_XO, 0 },
	{ P_GPWW0, 1 },
	{ P_GPWW4, 5 },
	{ P_GPWW0_EAWWY_DIV, 6 }
};

static const stwuct cwk_pawent_data gcc_xo_gpww0_gpww4_gpww0_eawwy_div[] = {
	{ .fw_name = "cxo", .name = "xo_boawd" },
	{ .hw = &gpww0.cwkw.hw },
	{ .hw = &gpww4.cwkw.hw },
	{ .hw = &gpww0_eawwy_div.hw }
};

static const stwuct fweq_tbw ftbw_usb30_mastew_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(120000000, P_GPWW0, 5, 0, 0),
	F(150000000, P_GPWW0, 4, 0, 0),
	{ }
};

static stwuct cwk_wcg2 usb30_mastew_cwk_swc = {
	.cmd_wcgw = 0x0f014,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_gpww0_eawwy_div_map,
	.fweq_tbw = ftbw_usb30_mastew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "usb30_mastew_cwk_swc",
		.pawent_data = gcc_xo_gpww0_gpww0_eawwy_div,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_gpww0_eawwy_div),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_usb30_mock_utmi_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 usb30_mock_utmi_cwk_swc = {
	.cmd_wcgw = 0x0f028,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_gpww0_eawwy_div_map,
	.fweq_tbw = ftbw_usb30_mock_utmi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "usb30_mock_utmi_cwk_swc",
		.pawent_data = gcc_xo_gpww0_gpww0_eawwy_div,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_gpww0_eawwy_div),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_usb3_phy_aux_cwk_swc[] = {
	F(1200000, P_XO, 16, 0, 0),
	{ }
};

static stwuct cwk_wcg2 usb3_phy_aux_cwk_swc = {
	.cmd_wcgw = 0x5000c,
	.hid_width = 5,
	.pawent_map = gcc_xo_sweep_cwk_map,
	.fweq_tbw = ftbw_usb3_phy_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "usb3_phy_aux_cwk_swc",
		.pawent_data = gcc_xo_sweep_cwk,
		.num_pawents = AWWAY_SIZE(gcc_xo_sweep_cwk),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_usb20_mastew_cwk_swc[] = {
	F(120000000, P_GPWW0, 5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 usb20_mastew_cwk_swc = {
	.cmd_wcgw = 0x12010,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_gpww0_eawwy_div_map,
	.fweq_tbw = ftbw_usb20_mastew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "usb20_mastew_cwk_swc",
		.pawent_data = gcc_xo_gpww0_gpww0_eawwy_div,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_gpww0_eawwy_div),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 usb20_mock_utmi_cwk_swc = {
	.cmd_wcgw = 0x12024,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_gpww0_eawwy_div_map,
	.fweq_tbw = ftbw_usb30_mock_utmi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "usb20_mock_utmi_cwk_swc",
		.pawent_data = gcc_xo_gpww0_gpww0_eawwy_div,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_gpww0_eawwy_div),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_sdcc1_apps_cwk_swc[] = {
	F(144000, P_XO, 16, 3, 25),
	F(400000, P_XO, 12, 1, 4),
	F(20000000, P_GPWW0, 15, 1, 2),
	F(25000000, P_GPWW0, 12, 1, 2),
	F(50000000, P_GPWW0, 12, 0, 0),
	F(96000000, P_GPWW4, 4, 0, 0),
	F(192000000, P_GPWW4, 2, 0, 0),
	F(384000000, P_GPWW4, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 sdcc1_apps_cwk_swc = {
	.cmd_wcgw = 0x13010,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_gpww4_gpww0_eawwy_div_map,
	.fweq_tbw = ftbw_sdcc1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "sdcc1_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_gpww4_gpww0_eawwy_div,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_gpww4_gpww0_eawwy_div),
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static stwuct fweq_tbw ftbw_sdcc1_ice_cowe_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(150000000, P_GPWW0, 4, 0, 0),
	F(300000000, P_GPWW0, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 sdcc1_ice_cowe_cwk_swc = {
	.cmd_wcgw = 0x13024,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_gpww4_gpww0_eawwy_div_map,
	.fweq_tbw = ftbw_sdcc1_ice_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "sdcc1_ice_cowe_cwk_swc",
		.pawent_data = gcc_xo_gpww0_gpww4_gpww0_eawwy_div,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_gpww4_gpww0_eawwy_div),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_sdcc2_apps_cwk_swc[] = {
	F(144000, P_XO, 16, 3, 25),
	F(400000, P_XO, 12, 1, 4),
	F(20000000, P_GPWW0, 15, 1, 2),
	F(25000000, P_GPWW0, 12, 1, 2),
	F(50000000, P_GPWW0, 12, 0, 0),
	F(100000000, P_GPWW0, 6, 0, 0),
	F(200000000, P_GPWW0, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 sdcc2_apps_cwk_swc = {
	.cmd_wcgw = 0x14010,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_gpww4_map,
	.fweq_tbw = ftbw_sdcc2_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "sdcc2_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_gpww4,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_gpww4),
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static stwuct cwk_wcg2 sdcc3_apps_cwk_swc = {
	.cmd_wcgw = 0x15010,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_gpww4_map,
	.fweq_tbw = ftbw_sdcc2_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "sdcc3_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0_gpww4,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_gpww4),
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static const stwuct fweq_tbw ftbw_sdcc4_apps_cwk_swc[] = {
	F(144000, P_XO, 16, 3, 25),
	F(400000, P_XO, 12, 1, 4),
	F(20000000, P_GPWW0, 15, 1, 2),
	F(25000000, P_GPWW0, 12, 1, 2),
	F(50000000, P_GPWW0, 12, 0, 0),
	F(100000000, P_GPWW0, 6, 0, 0),
	{ }
};

static stwuct cwk_wcg2 sdcc4_apps_cwk_swc = {
	.cmd_wcgw = 0x16010,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_sdcc4_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "sdcc4_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_fwoow_ops,
	},
};

static const stwuct fweq_tbw ftbw_bwsp1_qup1_spi_apps_cwk_swc[] = {
	F(960000, P_XO, 10, 1, 2),
	F(4800000, P_XO, 4, 0, 0),
	F(9600000, P_XO, 2, 0, 0),
	F(15000000, P_GPWW0, 10, 1, 4),
	F(19200000, P_XO, 1, 0, 0),
	F(25000000, P_GPWW0, 12, 1, 2),
	F(50000000, P_GPWW0, 12, 0, 0),
	{ }
};

static stwuct cwk_wcg2 bwsp1_qup1_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x1900c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup1_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_bwsp1_qup1_i2c_apps_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(50000000, P_GPWW0, 12, 0, 0),
	{ }
};

static stwuct cwk_wcg2 bwsp1_qup1_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x19020,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup1_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_bwsp1_uawt1_apps_cwk_swc[] = {
	F(3686400, P_GPWW0, 1, 96, 15625),
	F(7372800, P_GPWW0, 1, 192, 15625),
	F(14745600, P_GPWW0, 1, 384, 15625),
	F(16000000, P_GPWW0, 5, 2, 15),
	F(19200000, P_XO, 1, 0, 0),
	F(24000000, P_GPWW0, 5, 1, 5),
	F(32000000, P_GPWW0, 1, 4, 75),
	F(40000000, P_GPWW0, 15, 0, 0),
	F(46400000, P_GPWW0, 1, 29, 375),
	F(48000000, P_GPWW0, 12.5, 0, 0),
	F(51200000, P_GPWW0, 1, 32, 375),
	F(56000000, P_GPWW0, 1, 7, 75),
	F(58982400, P_GPWW0, 1, 1536, 15625),
	F(60000000, P_GPWW0, 10, 0, 0),
	F(63157895, P_GPWW0, 9.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 bwsp1_uawt1_apps_cwk_swc = {
	.cmd_wcgw = 0x1a00c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_uawt1_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_qup2_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x1b00c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup2_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_qup2_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x1b020,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup2_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_uawt2_apps_cwk_swc = {
	.cmd_wcgw = 0x1c00c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_uawt2_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_qup3_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x1d00c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup3_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_qup3_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x1d020,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup3_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_uawt3_apps_cwk_swc = {
	.cmd_wcgw = 0x1e00c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_uawt3_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_qup4_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x1f00c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup4_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_qup4_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x1f020,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup4_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_uawt4_apps_cwk_swc = {
	.cmd_wcgw = 0x2000c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_uawt4_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_qup5_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x2100c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup5_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_qup5_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x21020,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup5_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_uawt5_apps_cwk_swc = {
	.cmd_wcgw = 0x2200c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_uawt5_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_qup6_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x2300c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup6_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_qup6_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x23020,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_qup6_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp1_uawt6_apps_cwk_swc = {
	.cmd_wcgw = 0x2400c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp1_uawt6_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_qup1_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x2600c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_qup1_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_qup1_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x26020,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_qup1_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_uawt1_apps_cwk_swc = {
	.cmd_wcgw = 0x2700c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_uawt1_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_qup2_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x2800c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_qup2_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_qup2_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x28020,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_qup2_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_uawt2_apps_cwk_swc = {
	.cmd_wcgw = 0x2900c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_uawt2_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_qup3_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x2a00c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_qup3_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_qup3_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x2a020,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_qup3_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_uawt3_apps_cwk_swc = {
	.cmd_wcgw = 0x2b00c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_uawt3_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_qup4_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x2c00c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_qup4_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_qup4_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x2c020,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_qup4_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_uawt4_apps_cwk_swc = {
	.cmd_wcgw = 0x2d00c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_uawt4_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_qup5_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x2e00c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_qup5_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_qup5_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x2e020,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_qup5_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_uawt5_apps_cwk_swc = {
	.cmd_wcgw = 0x2f00c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_uawt5_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_qup6_spi_apps_cwk_swc = {
	.cmd_wcgw = 0x3000c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_spi_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_qup6_spi_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_qup6_i2c_apps_cwk_swc = {
	.cmd_wcgw = 0x30020,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_qup1_i2c_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_qup6_i2c_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 bwsp2_uawt6_apps_cwk_swc = {
	.cmd_wcgw = 0x3100c,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_bwsp1_uawt1_apps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "bwsp2_uawt6_apps_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_pdm2_cwk_swc[] = {
	F(60000000, P_GPWW0, 10, 0, 0),
	{ }
};

static stwuct cwk_wcg2 pdm2_cwk_swc = {
	.cmd_wcgw = 0x33010,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_pdm2_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "pdm2_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_tsif_wef_cwk_swc[] = {
	F(105495, P_XO, 1, 1, 182),
	{ }
};

static stwuct cwk_wcg2 tsif_wef_cwk_swc = {
	.cmd_wcgw = 0x36010,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_aud_wef_cwk_map,
	.fweq_tbw = ftbw_tsif_wef_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "tsif_wef_cwk_swc",
		.pawent_data = gcc_xo_gpww0_aud_wef_cwk,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_aud_wef_cwk),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gcc_sweep_cwk_swc = {
	.cmd_wcgw = 0x43014,
	.hid_width = 5,
	.pawent_map = gcc_sweep_cwk_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gcc_sweep_cwk_swc",
		.pawent_data = gcc_sweep_cwk,
		.num_pawents = AWWAY_SIZE(gcc_sweep_cwk),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 hmss_wbcpw_cwk_swc = {
	.cmd_wcgw = 0x48040,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_usb30_mock_utmi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "hmss_wbcpw_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 hmss_gpww0_cwk_swc = {
	.cmd_wcgw = 0x48058,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "hmss_gpww0_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gp1_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(100000000, P_GPWW0, 6, 0, 0),
	F(200000000, P_GPWW0, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gp1_cwk_swc = {
	.cmd_wcgw = 0x64004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_sweep_cwk_gpww0_eawwy_div_map,
	.fweq_tbw = ftbw_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gp1_cwk_swc",
		.pawent_data = gcc_xo_gpww0_sweep_cwk_gpww0_eawwy_div,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_sweep_cwk_gpww0_eawwy_div),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gp2_cwk_swc = {
	.cmd_wcgw = 0x65004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_sweep_cwk_gpww0_eawwy_div_map,
	.fweq_tbw = ftbw_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gp2_cwk_swc",
		.pawent_data = gcc_xo_gpww0_sweep_cwk_gpww0_eawwy_div,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_sweep_cwk_gpww0_eawwy_div),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 gp3_cwk_swc = {
	.cmd_wcgw = 0x66004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_sweep_cwk_gpww0_eawwy_div_map,
	.fweq_tbw = ftbw_gp1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gp3_cwk_swc",
		.pawent_data = gcc_xo_gpww0_sweep_cwk_gpww0_eawwy_div,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_sweep_cwk_gpww0_eawwy_div),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_pcie_aux_cwk_swc[] = {
	F(1010526, P_XO, 1, 1, 19),
	{ }
};

static stwuct cwk_wcg2 pcie_aux_cwk_swc = {
	.cmd_wcgw = 0x6c000,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = gcc_xo_sweep_cwk_map,
	.fweq_tbw = ftbw_pcie_aux_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "pcie_aux_cwk_swc",
		.pawent_data = gcc_xo_sweep_cwk,
		.num_pawents = AWWAY_SIZE(gcc_xo_sweep_cwk),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_ufs_axi_cwk_swc[] = {
	F(100000000, P_GPWW0, 6, 0, 0),
	F(200000000, P_GPWW0, 3, 0, 0),
	F(240000000, P_GPWW0, 2.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 ufs_axi_cwk_swc = {
	.cmd_wcgw = 0x75024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_ufs_axi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "ufs_axi_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_ufs_ice_cowe_cwk_swc[] = {
	F(19200000, P_XO, 1, 0, 0),
	F(150000000, P_GPWW0, 4, 0, 0),
	F(300000000, P_GPWW0, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 ufs_ice_cowe_cwk_swc = {
	.cmd_wcgw = 0x76014,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_map,
	.fweq_tbw = ftbw_ufs_ice_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "ufs_ice_cowe_cwk_swc",
		.pawent_data = gcc_xo_gpww0,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_qspi_sew_cwk_swc[] = {
	F(75000000, P_GPWW0, 8, 0, 0),
	F(150000000, P_GPWW0, 4, 0, 0),
	F(256000000, P_GPWW4, 1.5, 0, 0),
	F(300000000, P_GPWW0, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 qspi_sew_cwk_swc = {
	.cmd_wcgw = 0x8b00c,
	.hid_width = 5,
	.pawent_map = gcc_xo_gpww0_gpww4_gpww0_eawwy_div_map,
	.fweq_tbw = ftbw_qspi_sew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "qspi_sew_cwk_swc",
		.pawent_data = gcc_xo_gpww0_gpww4_gpww0_eawwy_div,
		.num_pawents = AWWAY_SIZE(gcc_xo_gpww0_gpww4_gpww0_eawwy_div),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gcc_sys_noc_usb3_axi_cwk = {
	.hawt_weg = 0x0f03c,
	.cwkw = {
		.enabwe_weg = 0x0f03c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sys_noc_usb3_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb30_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sys_noc_ufs_axi_cwk = {
	.hawt_weg = 0x75038,
	.cwkw = {
		.enabwe_weg = 0x75038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sys_noc_ufs_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&ufs_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pewiph_noc_usb20_ahb_cwk = {
	.hawt_weg = 0x6010,
	.cwkw = {
		.enabwe_weg = 0x6010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pewiph_noc_usb20_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb20_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mmss_noc_cfg_ahb_cwk = {
	.hawt_weg = 0x9008,
	.cwkw = {
		.enabwe_weg = 0x9008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mmss_noc_cfg_ahb_cwk",
			.fwags = CWK_IGNOWE_UNUSED,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mmss_bimc_gfx_cwk = {
	.hawt_weg = 0x9010,
	.cwkw = {
		.enabwe_weg = 0x9010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mmss_bimc_gfx_cwk",
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_mastew_cwk = {
	.hawt_weg = 0x0f008,
	.cwkw = {
		.enabwe_weg = 0x0f008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_mastew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb30_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_sweep_cwk = {
	.hawt_weg = 0x0f00c,
	.cwkw = {
		.enabwe_weg = 0x0f00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_sweep_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_sweep_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb30_mock_utmi_cwk = {
	.hawt_weg = 0x0f010,
	.cwkw = {
		.enabwe_weg = 0x0f010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb30_mock_utmi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb30_mock_utmi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_phy_aux_cwk = {
	.hawt_weg = 0x50000,
	.cwkw = {
		.enabwe_weg = 0x50000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_phy_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb3_phy_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_phy_pipe_cwk = {
	.hawt_weg = 0x50004,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x50004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_phy_pipe_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "usb3_phy_pipe_cwk_swc", .name = "usb3_phy_pipe_cwk_swc",
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb20_mastew_cwk = {
	.hawt_weg = 0x12004,
	.cwkw = {
		.enabwe_weg = 0x12004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb20_mastew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb20_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb20_sweep_cwk = {
	.hawt_weg = 0x12008,
	.cwkw = {
		.enabwe_weg = 0x12008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb20_sweep_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_sweep_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb20_mock_utmi_cwk = {
	.hawt_weg = 0x1200c,
	.cwkw = {
		.enabwe_weg = 0x1200c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb20_mock_utmi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb20_mock_utmi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb_phy_cfg_ahb2phy_cwk = {
	.hawt_weg = 0x6a004,
	.cwkw = {
		.enabwe_weg = 0x6a004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb_phy_cfg_ahb2phy_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_apps_cwk = {
	.hawt_weg = 0x13004,
	.cwkw = {
		.enabwe_weg = 0x13004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&sdcc1_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_ahb_cwk = {
	.hawt_weg = 0x13008,
	.cwkw = {
		.enabwe_weg = 0x13008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc1_ice_cowe_cwk = {
	.hawt_weg = 0x13038,
	.cwkw = {
		.enabwe_weg = 0x13038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc1_ice_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&sdcc1_ice_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc2_apps_cwk = {
	.hawt_weg = 0x14004,
	.cwkw = {
		.enabwe_weg = 0x14004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc2_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&sdcc2_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc2_ahb_cwk = {
	.hawt_weg = 0x14008,
	.cwkw = {
		.enabwe_weg = 0x14008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc2_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc3_apps_cwk = {
	.hawt_weg = 0x15004,
	.cwkw = {
		.enabwe_weg = 0x15004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc3_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&sdcc3_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc3_ahb_cwk = {
	.hawt_weg = 0x15008,
	.cwkw = {
		.enabwe_weg = 0x15008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc3_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc4_apps_cwk = {
	.hawt_weg = 0x16004,
	.cwkw = {
		.enabwe_weg = 0x16004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc4_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&sdcc4_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_sdcc4_ahb_cwk = {
	.hawt_weg = 0x16008,
	.cwkw = {
		.enabwe_weg = 0x16008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_sdcc4_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_ahb_cwk = {
	.hawt_weg = 0x17004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(17),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_sweep_cwk = {
	.hawt_weg = 0x17008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(16),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_sweep_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_sweep_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup1_spi_apps_cwk = {
	.hawt_weg = 0x19004,
	.cwkw = {
		.enabwe_weg = 0x19004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup1_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_qup1_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup1_i2c_apps_cwk = {
	.hawt_weg = 0x19008,
	.cwkw = {
		.enabwe_weg = 0x19008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup1_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_qup1_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt1_apps_cwk = {
	.hawt_weg = 0x1a004,
	.cwkw = {
		.enabwe_weg = 0x1a004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt1_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_uawt1_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup2_spi_apps_cwk = {
	.hawt_weg = 0x1b004,
	.cwkw = {
		.enabwe_weg = 0x1b004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup2_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_qup2_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup2_i2c_apps_cwk = {
	.hawt_weg = 0x1b008,
	.cwkw = {
		.enabwe_weg = 0x1b008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup2_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_qup2_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt2_apps_cwk = {
	.hawt_weg = 0x1c004,
	.cwkw = {
		.enabwe_weg = 0x1c004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt2_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_uawt2_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup3_spi_apps_cwk = {
	.hawt_weg = 0x1d004,
	.cwkw = {
		.enabwe_weg = 0x1d004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup3_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_qup3_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup3_i2c_apps_cwk = {
	.hawt_weg = 0x1d008,
	.cwkw = {
		.enabwe_weg = 0x1d008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup3_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_qup3_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt3_apps_cwk = {
	.hawt_weg = 0x1e004,
	.cwkw = {
		.enabwe_weg = 0x1e004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt3_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_uawt3_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup4_spi_apps_cwk = {
	.hawt_weg = 0x1f004,
	.cwkw = {
		.enabwe_weg = 0x1f004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup4_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_qup4_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup4_i2c_apps_cwk = {
	.hawt_weg = 0x1f008,
	.cwkw = {
		.enabwe_weg = 0x1f008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup4_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_qup4_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt4_apps_cwk = {
	.hawt_weg = 0x20004,
	.cwkw = {
		.enabwe_weg = 0x20004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt4_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_uawt4_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup5_spi_apps_cwk = {
	.hawt_weg = 0x21004,
	.cwkw = {
		.enabwe_weg = 0x21004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup5_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_qup5_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup5_i2c_apps_cwk = {
	.hawt_weg = 0x21008,
	.cwkw = {
		.enabwe_weg = 0x21008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup5_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_qup5_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt5_apps_cwk = {
	.hawt_weg = 0x22004,
	.cwkw = {
		.enabwe_weg = 0x22004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt5_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_uawt5_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup6_spi_apps_cwk = {
	.hawt_weg = 0x23004,
	.cwkw = {
		.enabwe_weg = 0x23004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup6_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_qup6_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_qup6_i2c_apps_cwk = {
	.hawt_weg = 0x23008,
	.cwkw = {
		.enabwe_weg = 0x23008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_qup6_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_qup6_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp1_uawt6_apps_cwk = {
	.hawt_weg = 0x24004,
	.cwkw = {
		.enabwe_weg = 0x24004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp1_uawt6_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp1_uawt6_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_ahb_cwk = {
	.hawt_weg = 0x25004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(15),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_sweep_cwk = {
	.hawt_weg = 0x25008,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(14),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_sweep_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_sweep_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_qup1_spi_apps_cwk = {
	.hawt_weg = 0x26004,
	.cwkw = {
		.enabwe_weg = 0x26004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_qup1_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_qup1_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_qup1_i2c_apps_cwk = {
	.hawt_weg = 0x26008,
	.cwkw = {
		.enabwe_weg = 0x26008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_qup1_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_qup1_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_uawt1_apps_cwk = {
	.hawt_weg = 0x27004,
	.cwkw = {
		.enabwe_weg = 0x27004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_uawt1_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_uawt1_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_qup2_spi_apps_cwk = {
	.hawt_weg = 0x28004,
	.cwkw = {
		.enabwe_weg = 0x28004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_qup2_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_qup2_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_qup2_i2c_apps_cwk = {
	.hawt_weg = 0x28008,
	.cwkw = {
		.enabwe_weg = 0x28008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_qup2_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_qup2_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_uawt2_apps_cwk = {
	.hawt_weg = 0x29004,
	.cwkw = {
		.enabwe_weg = 0x29004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_uawt2_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_uawt2_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_qup3_spi_apps_cwk = {
	.hawt_weg = 0x2a004,
	.cwkw = {
		.enabwe_weg = 0x2a004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_qup3_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_qup3_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_qup3_i2c_apps_cwk = {
	.hawt_weg = 0x2a008,
	.cwkw = {
		.enabwe_weg = 0x2a008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_qup3_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_qup3_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_uawt3_apps_cwk = {
	.hawt_weg = 0x2b004,
	.cwkw = {
		.enabwe_weg = 0x2b004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_uawt3_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_uawt3_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_qup4_spi_apps_cwk = {
	.hawt_weg = 0x2c004,
	.cwkw = {
		.enabwe_weg = 0x2c004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_qup4_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_qup4_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_qup4_i2c_apps_cwk = {
	.hawt_weg = 0x2c008,
	.cwkw = {
		.enabwe_weg = 0x2c008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_qup4_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_qup4_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_uawt4_apps_cwk = {
	.hawt_weg = 0x2d004,
	.cwkw = {
		.enabwe_weg = 0x2d004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_uawt4_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_uawt4_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_qup5_spi_apps_cwk = {
	.hawt_weg = 0x2e004,
	.cwkw = {
		.enabwe_weg = 0x2e004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_qup5_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_qup5_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_qup5_i2c_apps_cwk = {
	.hawt_weg = 0x2e008,
	.cwkw = {
		.enabwe_weg = 0x2e008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_qup5_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_qup5_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_uawt5_apps_cwk = {
	.hawt_weg = 0x2f004,
	.cwkw = {
		.enabwe_weg = 0x2f004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_uawt5_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_uawt5_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_qup6_spi_apps_cwk = {
	.hawt_weg = 0x30004,
	.cwkw = {
		.enabwe_weg = 0x30004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_qup6_spi_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_qup6_spi_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_qup6_i2c_apps_cwk = {
	.hawt_weg = 0x30008,
	.cwkw = {
		.enabwe_weg = 0x30008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_qup6_i2c_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_qup6_i2c_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bwsp2_uawt6_apps_cwk = {
	.hawt_weg = 0x31004,
	.cwkw = {
		.enabwe_weg = 0x31004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bwsp2_uawt6_apps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&bwsp2_uawt6_apps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pdm_ahb_cwk = {
	.hawt_weg = 0x33004,
	.cwkw = {
		.enabwe_weg = 0x33004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pdm_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pdm2_cwk = {
	.hawt_weg = 0x3300c,
	.cwkw = {
		.enabwe_weg = 0x3300c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pdm2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&pdm2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pwng_ahb_cwk = {
	.hawt_weg = 0x34004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(13),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pwng_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_tsif_ahb_cwk = {
	.hawt_weg = 0x36004,
	.cwkw = {
		.enabwe_weg = 0x36004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_tsif_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_tsif_wef_cwk = {
	.hawt_weg = 0x36008,
	.cwkw = {
		.enabwe_weg = 0x36008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_tsif_wef_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&tsif_wef_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_tsif_inactivity_timews_cwk = {
	.hawt_weg = 0x3600c,
	.cwkw = {
		.enabwe_weg = 0x3600c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_tsif_inactivity_timews_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gcc_sweep_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_boot_wom_ahb_cwk = {
	.hawt_weg = 0x38004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x52004,
		.enabwe_mask = BIT(10),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_boot_wom_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_bimc_gfx_cwk = {
	.hawt_weg = 0x46018,
	.cwkw = {
		.enabwe_weg = 0x46018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_bimc_gfx_cwk",
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_hmss_wbcpw_cwk = {
	.hawt_weg = 0x4800c,
	.cwkw = {
		.enabwe_weg = 0x4800c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_hmss_wbcpw_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&hmss_wbcpw_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp1_cwk = {
	.hawt_weg = 0x64000,
	.cwkw = {
		.enabwe_weg = 0x64000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gp1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp2_cwk = {
	.hawt_weg = 0x65000,
	.cwkw = {
		.enabwe_weg = 0x65000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gp2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_gp3_cwk = {
	.hawt_weg = 0x66000,
	.cwkw = {
		.enabwe_weg = 0x66000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_gp3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gp3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_swv_axi_cwk = {
	.hawt_weg = 0x6b008,
	.cwkw = {
		.enabwe_weg = 0x6b008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_swv_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_mstw_axi_cwk = {
	.hawt_weg = 0x6b00c,
	.cwkw = {
		.enabwe_weg = 0x6b00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_mstw_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_cfg_ahb_cwk = {
	.hawt_weg = 0x6b010,
	.cwkw = {
		.enabwe_weg = 0x6b010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_aux_cwk = {
	.hawt_weg = 0x6b014,
	.cwkw = {
		.enabwe_weg = 0x6b014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&pcie_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_0_pipe_cwk = {
	.hawt_weg = 0x6b018,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x6b018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_0_pipe_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "pcie_0_pipe_cwk_swc", .name = "pcie_0_pipe_cwk_swc",
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_swv_axi_cwk = {
	.hawt_weg = 0x6d008,
	.cwkw = {
		.enabwe_weg = 0x6d008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_swv_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_mstw_axi_cwk = {
	.hawt_weg = 0x6d00c,
	.cwkw = {
		.enabwe_weg = 0x6d00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_mstw_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_cfg_ahb_cwk = {
	.hawt_weg = 0x6d010,
	.cwkw = {
		.enabwe_weg = 0x6d010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_aux_cwk = {
	.hawt_weg = 0x6d014,
	.cwkw = {
		.enabwe_weg = 0x6d014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&pcie_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_1_pipe_cwk = {
	.hawt_weg = 0x6d018,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x6d018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_1_pipe_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "pcie_1_pipe_cwk_swc", .name = "pcie_1_pipe_cwk_swc",
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_2_swv_axi_cwk = {
	.hawt_weg = 0x6e008,
	.cwkw = {
		.enabwe_weg = 0x6e008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_2_swv_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_2_mstw_axi_cwk = {
	.hawt_weg = 0x6e00c,
	.cwkw = {
		.enabwe_weg = 0x6e00c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_2_mstw_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_2_cfg_ahb_cwk = {
	.hawt_weg = 0x6e010,
	.cwkw = {
		.enabwe_weg = 0x6e010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_2_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_2_aux_cwk = {
	.hawt_weg = 0x6e014,
	.cwkw = {
		.enabwe_weg = 0x6e014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_2_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&pcie_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_2_pipe_cwk = {
	.hawt_weg = 0x6e018,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x6e018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_2_pipe_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "pcie_2_pipe_cwk_swc", .name = "pcie_2_pipe_cwk_swc",
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_phy_cfg_ahb_cwk = {
	.hawt_weg = 0x6f004,
	.cwkw = {
		.enabwe_weg = 0x6f004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_phy_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_phy_aux_cwk = {
	.hawt_weg = 0x6f008,
	.cwkw = {
		.enabwe_weg = 0x6f008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_phy_aux_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&pcie_aux_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_axi_cwk = {
	.hawt_weg = 0x75008,
	.cwkw = {
		.enabwe_weg = 0x75008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&ufs_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_ahb_cwk = {
	.hawt_weg = 0x7500c,
	.cwkw = {
		.enabwe_weg = 0x7500c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_fixed_factow ufs_tx_cfg_cwk_swc = {
	.muwt = 1,
	.div = 16,
	.hw.init = &(stwuct cwk_init_data){
		.name = "ufs_tx_cfg_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&ufs_axi_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_bwanch gcc_ufs_tx_cfg_cwk = {
	.hawt_weg = 0x75010,
	.cwkw = {
		.enabwe_weg = 0x75010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_tx_cfg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&ufs_tx_cfg_cwk_swc.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_fixed_factow ufs_wx_cfg_cwk_swc = {
	.muwt = 1,
	.div = 16,
	.hw.init = &(stwuct cwk_init_data){
		.name = "ufs_wx_cfg_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&ufs_axi_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_bwanch gcc_hwos1_vote_wpass_cowe_smmu_cwk = {
	.hawt_weg = 0x7d010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7d010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "hwos1_vote_wpass_cowe_smmu_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_hwos1_vote_wpass_adsp_smmu_cwk = {
	.hawt_weg = 0x7d014,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x7d014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "hwos1_vote_wpass_adsp_smmu_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_wx_cfg_cwk = {
	.hawt_weg = 0x75014,
	.cwkw = {
		.enabwe_weg = 0x75014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_wx_cfg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&ufs_wx_cfg_cwk_swc.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_tx_symbow_0_cwk = {
	.hawt_weg = 0x75018,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x75018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_tx_symbow_0_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "ufs_tx_symbow_0_cwk_swc", .name = "ufs_tx_symbow_0_cwk_swc",
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_wx_symbow_0_cwk = {
	.hawt_weg = 0x7501c,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x7501c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_wx_symbow_0_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "ufs_wx_symbow_0_cwk_swc", .name = "ufs_wx_symbow_0_cwk_swc",
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_wx_symbow_1_cwk = {
	.hawt_weg = 0x75020,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x75020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_wx_symbow_1_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "ufs_wx_symbow_1_cwk_swc", .name = "ufs_wx_symbow_1_cwk_swc",
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_fixed_factow ufs_ice_cowe_postdiv_cwk_swc = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "ufs_ice_cowe_postdiv_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&ufs_ice_cowe_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_fixed_factow_ops,
	},
};

static stwuct cwk_bwanch gcc_ufs_unipwo_cowe_cwk = {
	.hawt_weg = 0x7600c,
	.cwkw = {
		.enabwe_weg = 0x7600c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_unipwo_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&ufs_ice_cowe_postdiv_cwk_swc.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_ice_cowe_cwk = {
	.hawt_weg = 0x76010,
	.cwkw = {
		.enabwe_weg = 0x76010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_ice_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&ufs_ice_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_sys_cwk_cowe_cwk = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x76030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_sys_cwk_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_tx_symbow_cwk_cowe_cwk = {
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x76034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_tx_symbow_cwk_cowe_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_aggwe0_snoc_axi_cwk = {
	.hawt_weg = 0x81008,
	.cwkw = {
		.enabwe_weg = 0x81008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_aggwe0_snoc_axi_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_aggwe0_cnoc_ahb_cwk = {
	.hawt_weg = 0x8100c,
	.cwkw = {
		.enabwe_weg = 0x8100c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_aggwe0_cnoc_ahb_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_smmu_aggwe0_axi_cwk = {
	.hawt_weg = 0x81014,
	.cwkw = {
		.enabwe_weg = 0x81014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_smmu_aggwe0_axi_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_smmu_aggwe0_ahb_cwk = {
	.hawt_weg = 0x81018,
	.cwkw = {
		.enabwe_weg = 0x81018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_smmu_aggwe0_ahb_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_aggwe2_ufs_axi_cwk = {
	.hawt_weg = 0x83014,
	.cwkw = {
		.enabwe_weg = 0x83014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_aggwe2_ufs_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&ufs_axi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_aggwe2_usb3_axi_cwk = {
	.hawt_weg = 0x83018,
	.cwkw = {
		.enabwe_weg = 0x83018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_aggwe2_usb3_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&usb30_mastew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_dcc_ahb_cwk = {
	.hawt_weg = 0x84004,
	.cwkw = {
		.enabwe_weg = 0x84004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_dcc_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_aggwe0_noc_mpu_cfg_ahb_cwk = {
	.hawt_weg = 0x85000,
	.cwkw = {
		.enabwe_weg = 0x85000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_aggwe0_noc_mpu_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qspi_ahb_cwk = {
	.hawt_weg = 0x8b004,
	.cwkw = {
		.enabwe_weg = 0x8b004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qspi_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_qspi_sew_cwk = {
	.hawt_weg = 0x8b008,
	.cwkw = {
		.enabwe_weg = 0x8b008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_qspi_sew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&qspi_sew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_usb3_cwkwef_cwk = {
	.hawt_weg = 0x8800C,
	.cwkw = {
		.enabwe_weg = 0x8800C,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_usb3_cwkwef_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "cxo2",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_hdmi_cwkwef_cwk = {
	.hawt_weg = 0x88000,
	.cwkw = {
		.enabwe_weg = 0x88000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_hdmi_cwkwef_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "cxo2",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_edp_cwkwef_cwk = {
	.hawt_weg = 0x88004,
	.cwkw = {
		.enabwe_weg = 0x88004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_edp_cwkwef_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "cxo2",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_ufs_cwkwef_cwk = {
	.hawt_weg = 0x88008,
	.cwkw = {
		.enabwe_weg = 0x88008,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_ufs_cwkwef_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "cxo2",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_pcie_cwkwef_cwk = {
	.hawt_weg = 0x88010,
	.cwkw = {
		.enabwe_weg = 0x88010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_pcie_cwkwef_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "cxo2",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wx2_usb2_cwkwef_cwk = {
	.hawt_weg = 0x88014,
	.cwkw = {
		.enabwe_weg = 0x88014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_wx2_usb2_cwkwef_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "cxo2",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_wx1_usb2_cwkwef_cwk = {
	.hawt_weg = 0x88018,
	.cwkw = {
		.enabwe_weg = 0x88018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_wx1_usb2_cwkwef_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "cxo2",
				.name = "xo",
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mss_cfg_ahb_cwk = {
	.hawt_weg = 0x8a000,
	.cwkw = {
		.enabwe_weg = 0x8a000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mss_cfg_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mss_mnoc_bimc_axi_cwk = {
	.hawt_weg = 0x8a004,
	.cwkw = {
		.enabwe_weg = 0x8a004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mss_mnoc_bimc_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mss_snoc_axi_cwk = {
	.hawt_weg = 0x8a024,
	.cwkw = {
		.enabwe_weg = 0x8a024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mss_snoc_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gcc_mss_q6_bimc_axi_cwk = {
	.hawt_weg = 0x8a028,
	.cwkw = {
		.enabwe_weg = 0x8a028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gcc_mss_q6_bimc_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_hw *gcc_msm8996_hws[] = {
	&xo.hw,
	&gpww0_eawwy_div.hw,
	&ufs_tx_cfg_cwk_swc.hw,
	&ufs_wx_cfg_cwk_swc.hw,
	&ufs_ice_cowe_postdiv_cwk_swc.hw,
};

static stwuct gdsc aggwe0_noc_gdsc = {
	.gdscw = 0x81004,
	.gds_hw_ctww = 0x81028,
	.pd = {
		.name = "aggwe0_noc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE | AWWAYS_ON,
};

static stwuct gdsc hwos1_vote_aggwe0_noc_gdsc = {
	.gdscw = 0x7d024,
	.pd = {
		.name = "hwos1_vote_aggwe0_noc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc hwos1_vote_wpass_adsp_gdsc = {
	.gdscw = 0x7d034,
	.pd = {
		.name = "hwos1_vote_wpass_adsp",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc hwos1_vote_wpass_cowe_gdsc = {
	.gdscw = 0x7d038,
	.pd = {
		.name = "hwos1_vote_wpass_cowe",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc usb30_gdsc = {
	.gdscw = 0xf004,
	.pd = {
		.name = "usb30",
	},
	/* TODO: Change to OFF_ON when USB dwivews get pwopew suspend suppowt */
	.pwwsts = PWWSTS_WET_ON,
};

static stwuct gdsc pcie0_gdsc = {
	.gdscw = 0x6b004,
	.pd = {
		.name = "pcie0",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc pcie1_gdsc = {
	.gdscw = 0x6d004,
	.pd = {
		.name = "pcie1",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc pcie2_gdsc = {
	.gdscw = 0x6e004,
	.pd = {
		.name = "pcie2",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ufs_gdsc = {
	.gdscw = 0x75004,
	.pd = {
		.name = "ufs",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct cwk_wegmap *gcc_msm8996_cwocks[] = {
	[GPWW0_EAWWY] = &gpww0_eawwy.cwkw,
	[GPWW0] = &gpww0.cwkw,
	[GPWW4_EAWWY] = &gpww4_eawwy.cwkw,
	[GPWW4] = &gpww4.cwkw,
	[USB30_MASTEW_CWK_SWC] = &usb30_mastew_cwk_swc.cwkw,
	[USB30_MOCK_UTMI_CWK_SWC] = &usb30_mock_utmi_cwk_swc.cwkw,
	[USB3_PHY_AUX_CWK_SWC] = &usb3_phy_aux_cwk_swc.cwkw,
	[USB20_MASTEW_CWK_SWC] = &usb20_mastew_cwk_swc.cwkw,
	[USB20_MOCK_UTMI_CWK_SWC] = &usb20_mock_utmi_cwk_swc.cwkw,
	[SDCC1_APPS_CWK_SWC] = &sdcc1_apps_cwk_swc.cwkw,
	[SDCC1_ICE_COWE_CWK_SWC] = &sdcc1_ice_cowe_cwk_swc.cwkw,
	[SDCC2_APPS_CWK_SWC] = &sdcc2_apps_cwk_swc.cwkw,
	[SDCC3_APPS_CWK_SWC] = &sdcc3_apps_cwk_swc.cwkw,
	[SDCC4_APPS_CWK_SWC] = &sdcc4_apps_cwk_swc.cwkw,
	[BWSP1_QUP1_SPI_APPS_CWK_SWC] = &bwsp1_qup1_spi_apps_cwk_swc.cwkw,
	[BWSP1_QUP1_I2C_APPS_CWK_SWC] = &bwsp1_qup1_i2c_apps_cwk_swc.cwkw,
	[BWSP1_UAWT1_APPS_CWK_SWC] = &bwsp1_uawt1_apps_cwk_swc.cwkw,
	[BWSP1_QUP2_SPI_APPS_CWK_SWC] = &bwsp1_qup2_spi_apps_cwk_swc.cwkw,
	[BWSP1_QUP2_I2C_APPS_CWK_SWC] = &bwsp1_qup2_i2c_apps_cwk_swc.cwkw,
	[BWSP1_UAWT2_APPS_CWK_SWC] = &bwsp1_uawt2_apps_cwk_swc.cwkw,
	[BWSP1_QUP3_SPI_APPS_CWK_SWC] = &bwsp1_qup3_spi_apps_cwk_swc.cwkw,
	[BWSP1_QUP3_I2C_APPS_CWK_SWC] = &bwsp1_qup3_i2c_apps_cwk_swc.cwkw,
	[BWSP1_UAWT3_APPS_CWK_SWC] = &bwsp1_uawt3_apps_cwk_swc.cwkw,
	[BWSP1_QUP4_SPI_APPS_CWK_SWC] = &bwsp1_qup4_spi_apps_cwk_swc.cwkw,
	[BWSP1_QUP4_I2C_APPS_CWK_SWC] = &bwsp1_qup4_i2c_apps_cwk_swc.cwkw,
	[BWSP1_UAWT4_APPS_CWK_SWC] = &bwsp1_uawt4_apps_cwk_swc.cwkw,
	[BWSP1_QUP5_SPI_APPS_CWK_SWC] = &bwsp1_qup5_spi_apps_cwk_swc.cwkw,
	[BWSP1_QUP5_I2C_APPS_CWK_SWC] = &bwsp1_qup5_i2c_apps_cwk_swc.cwkw,
	[BWSP1_UAWT5_APPS_CWK_SWC] = &bwsp1_uawt5_apps_cwk_swc.cwkw,
	[BWSP1_QUP6_SPI_APPS_CWK_SWC] = &bwsp1_qup6_spi_apps_cwk_swc.cwkw,
	[BWSP1_QUP6_I2C_APPS_CWK_SWC] = &bwsp1_qup6_i2c_apps_cwk_swc.cwkw,
	[BWSP1_UAWT6_APPS_CWK_SWC] = &bwsp1_uawt6_apps_cwk_swc.cwkw,
	[BWSP2_QUP1_SPI_APPS_CWK_SWC] = &bwsp2_qup1_spi_apps_cwk_swc.cwkw,
	[BWSP2_QUP1_I2C_APPS_CWK_SWC] = &bwsp2_qup1_i2c_apps_cwk_swc.cwkw,
	[BWSP2_UAWT1_APPS_CWK_SWC] = &bwsp2_uawt1_apps_cwk_swc.cwkw,
	[BWSP2_QUP2_SPI_APPS_CWK_SWC] = &bwsp2_qup2_spi_apps_cwk_swc.cwkw,
	[BWSP2_QUP2_I2C_APPS_CWK_SWC] = &bwsp2_qup2_i2c_apps_cwk_swc.cwkw,
	[BWSP2_UAWT2_APPS_CWK_SWC] = &bwsp2_uawt2_apps_cwk_swc.cwkw,
	[BWSP2_QUP3_SPI_APPS_CWK_SWC] = &bwsp2_qup3_spi_apps_cwk_swc.cwkw,
	[BWSP2_QUP3_I2C_APPS_CWK_SWC] = &bwsp2_qup3_i2c_apps_cwk_swc.cwkw,
	[BWSP2_UAWT3_APPS_CWK_SWC] = &bwsp2_uawt3_apps_cwk_swc.cwkw,
	[BWSP2_QUP4_SPI_APPS_CWK_SWC] = &bwsp2_qup4_spi_apps_cwk_swc.cwkw,
	[BWSP2_QUP4_I2C_APPS_CWK_SWC] = &bwsp2_qup4_i2c_apps_cwk_swc.cwkw,
	[BWSP2_UAWT4_APPS_CWK_SWC] = &bwsp2_uawt4_apps_cwk_swc.cwkw,
	[BWSP2_QUP5_SPI_APPS_CWK_SWC] = &bwsp2_qup5_spi_apps_cwk_swc.cwkw,
	[BWSP2_QUP5_I2C_APPS_CWK_SWC] = &bwsp2_qup5_i2c_apps_cwk_swc.cwkw,
	[BWSP2_UAWT5_APPS_CWK_SWC] = &bwsp2_uawt5_apps_cwk_swc.cwkw,
	[BWSP2_QUP6_SPI_APPS_CWK_SWC] = &bwsp2_qup6_spi_apps_cwk_swc.cwkw,
	[BWSP2_QUP6_I2C_APPS_CWK_SWC] = &bwsp2_qup6_i2c_apps_cwk_swc.cwkw,
	[BWSP2_UAWT6_APPS_CWK_SWC] = &bwsp2_uawt6_apps_cwk_swc.cwkw,
	[PDM2_CWK_SWC] = &pdm2_cwk_swc.cwkw,
	[TSIF_WEF_CWK_SWC] = &tsif_wef_cwk_swc.cwkw,
	[GCC_SWEEP_CWK_SWC] = &gcc_sweep_cwk_swc.cwkw,
	[HMSS_WBCPW_CWK_SWC] = &hmss_wbcpw_cwk_swc.cwkw,
	[HMSS_GPWW0_CWK_SWC] = &hmss_gpww0_cwk_swc.cwkw,
	[GP1_CWK_SWC] = &gp1_cwk_swc.cwkw,
	[GP2_CWK_SWC] = &gp2_cwk_swc.cwkw,
	[GP3_CWK_SWC] = &gp3_cwk_swc.cwkw,
	[PCIE_AUX_CWK_SWC] = &pcie_aux_cwk_swc.cwkw,
	[UFS_AXI_CWK_SWC] = &ufs_axi_cwk_swc.cwkw,
	[UFS_ICE_COWE_CWK_SWC] = &ufs_ice_cowe_cwk_swc.cwkw,
	[QSPI_SEW_CWK_SWC] = &qspi_sew_cwk_swc.cwkw,
	[GCC_SYS_NOC_USB3_AXI_CWK] = &gcc_sys_noc_usb3_axi_cwk.cwkw,
	[GCC_SYS_NOC_UFS_AXI_CWK] = &gcc_sys_noc_ufs_axi_cwk.cwkw,
	[GCC_PEWIPH_NOC_USB20_AHB_CWK] = &gcc_pewiph_noc_usb20_ahb_cwk.cwkw,
	[GCC_MMSS_NOC_CFG_AHB_CWK] = &gcc_mmss_noc_cfg_ahb_cwk.cwkw,
	[GCC_MMSS_BIMC_GFX_CWK] = &gcc_mmss_bimc_gfx_cwk.cwkw,
	[GCC_USB30_MASTEW_CWK] = &gcc_usb30_mastew_cwk.cwkw,
	[GCC_USB30_SWEEP_CWK] = &gcc_usb30_sweep_cwk.cwkw,
	[GCC_USB30_MOCK_UTMI_CWK] = &gcc_usb30_mock_utmi_cwk.cwkw,
	[GCC_USB3_PHY_AUX_CWK] = &gcc_usb3_phy_aux_cwk.cwkw,
	[GCC_USB3_PHY_PIPE_CWK] = &gcc_usb3_phy_pipe_cwk.cwkw,
	[GCC_USB20_MASTEW_CWK] = &gcc_usb20_mastew_cwk.cwkw,
	[GCC_USB20_SWEEP_CWK] = &gcc_usb20_sweep_cwk.cwkw,
	[GCC_USB20_MOCK_UTMI_CWK] = &gcc_usb20_mock_utmi_cwk.cwkw,
	[GCC_USB_PHY_CFG_AHB2PHY_CWK] = &gcc_usb_phy_cfg_ahb2phy_cwk.cwkw,
	[GCC_SDCC1_APPS_CWK] = &gcc_sdcc1_apps_cwk.cwkw,
	[GCC_SDCC1_AHB_CWK] = &gcc_sdcc1_ahb_cwk.cwkw,
	[GCC_SDCC1_ICE_COWE_CWK] = &gcc_sdcc1_ice_cowe_cwk.cwkw,
	[GCC_SDCC2_APPS_CWK] = &gcc_sdcc2_apps_cwk.cwkw,
	[GCC_SDCC2_AHB_CWK] = &gcc_sdcc2_ahb_cwk.cwkw,
	[GCC_SDCC3_APPS_CWK] = &gcc_sdcc3_apps_cwk.cwkw,
	[GCC_SDCC3_AHB_CWK] = &gcc_sdcc3_ahb_cwk.cwkw,
	[GCC_SDCC4_APPS_CWK] = &gcc_sdcc4_apps_cwk.cwkw,
	[GCC_SDCC4_AHB_CWK] = &gcc_sdcc4_ahb_cwk.cwkw,
	[GCC_BWSP1_AHB_CWK] = &gcc_bwsp1_ahb_cwk.cwkw,
	[GCC_BWSP1_SWEEP_CWK] = &gcc_bwsp1_sweep_cwk.cwkw,
	[GCC_BWSP1_QUP1_SPI_APPS_CWK] = &gcc_bwsp1_qup1_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP1_I2C_APPS_CWK] = &gcc_bwsp1_qup1_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT1_APPS_CWK] = &gcc_bwsp1_uawt1_apps_cwk.cwkw,
	[GCC_BWSP1_QUP2_SPI_APPS_CWK] = &gcc_bwsp1_qup2_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP2_I2C_APPS_CWK] = &gcc_bwsp1_qup2_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT2_APPS_CWK] = &gcc_bwsp1_uawt2_apps_cwk.cwkw,
	[GCC_BWSP1_QUP3_SPI_APPS_CWK] = &gcc_bwsp1_qup3_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP3_I2C_APPS_CWK] = &gcc_bwsp1_qup3_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT3_APPS_CWK] = &gcc_bwsp1_uawt3_apps_cwk.cwkw,
	[GCC_BWSP1_QUP4_SPI_APPS_CWK] = &gcc_bwsp1_qup4_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP4_I2C_APPS_CWK] = &gcc_bwsp1_qup4_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT4_APPS_CWK] = &gcc_bwsp1_uawt4_apps_cwk.cwkw,
	[GCC_BWSP1_QUP5_SPI_APPS_CWK] = &gcc_bwsp1_qup5_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP5_I2C_APPS_CWK] = &gcc_bwsp1_qup5_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT5_APPS_CWK] = &gcc_bwsp1_uawt5_apps_cwk.cwkw,
	[GCC_BWSP1_QUP6_SPI_APPS_CWK] = &gcc_bwsp1_qup6_spi_apps_cwk.cwkw,
	[GCC_BWSP1_QUP6_I2C_APPS_CWK] = &gcc_bwsp1_qup6_i2c_apps_cwk.cwkw,
	[GCC_BWSP1_UAWT6_APPS_CWK] = &gcc_bwsp1_uawt6_apps_cwk.cwkw,
	[GCC_BWSP2_AHB_CWK] = &gcc_bwsp2_ahb_cwk.cwkw,
	[GCC_BWSP2_SWEEP_CWK] = &gcc_bwsp2_sweep_cwk.cwkw,
	[GCC_BWSP2_QUP1_SPI_APPS_CWK] = &gcc_bwsp2_qup1_spi_apps_cwk.cwkw,
	[GCC_BWSP2_QUP1_I2C_APPS_CWK] = &gcc_bwsp2_qup1_i2c_apps_cwk.cwkw,
	[GCC_BWSP2_UAWT1_APPS_CWK] = &gcc_bwsp2_uawt1_apps_cwk.cwkw,
	[GCC_BWSP2_QUP2_SPI_APPS_CWK] = &gcc_bwsp2_qup2_spi_apps_cwk.cwkw,
	[GCC_BWSP2_QUP2_I2C_APPS_CWK] = &gcc_bwsp2_qup2_i2c_apps_cwk.cwkw,
	[GCC_BWSP2_UAWT2_APPS_CWK] = &gcc_bwsp2_uawt2_apps_cwk.cwkw,
	[GCC_BWSP2_QUP3_SPI_APPS_CWK] = &gcc_bwsp2_qup3_spi_apps_cwk.cwkw,
	[GCC_BWSP2_QUP3_I2C_APPS_CWK] = &gcc_bwsp2_qup3_i2c_apps_cwk.cwkw,
	[GCC_BWSP2_UAWT3_APPS_CWK] = &gcc_bwsp2_uawt3_apps_cwk.cwkw,
	[GCC_BWSP2_QUP4_SPI_APPS_CWK] = &gcc_bwsp2_qup4_spi_apps_cwk.cwkw,
	[GCC_BWSP2_QUP4_I2C_APPS_CWK] = &gcc_bwsp2_qup4_i2c_apps_cwk.cwkw,
	[GCC_BWSP2_UAWT4_APPS_CWK] = &gcc_bwsp2_uawt4_apps_cwk.cwkw,
	[GCC_BWSP2_QUP5_SPI_APPS_CWK] = &gcc_bwsp2_qup5_spi_apps_cwk.cwkw,
	[GCC_BWSP2_QUP5_I2C_APPS_CWK] = &gcc_bwsp2_qup5_i2c_apps_cwk.cwkw,
	[GCC_BWSP2_UAWT5_APPS_CWK] = &gcc_bwsp2_uawt5_apps_cwk.cwkw,
	[GCC_BWSP2_QUP6_SPI_APPS_CWK] = &gcc_bwsp2_qup6_spi_apps_cwk.cwkw,
	[GCC_BWSP2_QUP6_I2C_APPS_CWK] = &gcc_bwsp2_qup6_i2c_apps_cwk.cwkw,
	[GCC_BWSP2_UAWT6_APPS_CWK] = &gcc_bwsp2_uawt6_apps_cwk.cwkw,
	[GCC_PDM_AHB_CWK] = &gcc_pdm_ahb_cwk.cwkw,
	[GCC_PDM2_CWK] = &gcc_pdm2_cwk.cwkw,
	[GCC_PWNG_AHB_CWK] = &gcc_pwng_ahb_cwk.cwkw,
	[GCC_TSIF_AHB_CWK] = &gcc_tsif_ahb_cwk.cwkw,
	[GCC_TSIF_WEF_CWK] = &gcc_tsif_wef_cwk.cwkw,
	[GCC_TSIF_INACTIVITY_TIMEWS_CWK] = &gcc_tsif_inactivity_timews_cwk.cwkw,
	[GCC_BOOT_WOM_AHB_CWK] = &gcc_boot_wom_ahb_cwk.cwkw,
	[GCC_BIMC_GFX_CWK] = &gcc_bimc_gfx_cwk.cwkw,
	[GCC_HMSS_WBCPW_CWK] = &gcc_hmss_wbcpw_cwk.cwkw,
	[GCC_GP1_CWK] = &gcc_gp1_cwk.cwkw,
	[GCC_GP2_CWK] = &gcc_gp2_cwk.cwkw,
	[GCC_GP3_CWK] = &gcc_gp3_cwk.cwkw,
	[GCC_PCIE_0_SWV_AXI_CWK] = &gcc_pcie_0_swv_axi_cwk.cwkw,
	[GCC_PCIE_0_MSTW_AXI_CWK] = &gcc_pcie_0_mstw_axi_cwk.cwkw,
	[GCC_PCIE_0_CFG_AHB_CWK] = &gcc_pcie_0_cfg_ahb_cwk.cwkw,
	[GCC_PCIE_0_AUX_CWK] = &gcc_pcie_0_aux_cwk.cwkw,
	[GCC_PCIE_0_PIPE_CWK] = &gcc_pcie_0_pipe_cwk.cwkw,
	[GCC_PCIE_1_SWV_AXI_CWK] = &gcc_pcie_1_swv_axi_cwk.cwkw,
	[GCC_PCIE_1_MSTW_AXI_CWK] = &gcc_pcie_1_mstw_axi_cwk.cwkw,
	[GCC_PCIE_1_CFG_AHB_CWK] = &gcc_pcie_1_cfg_ahb_cwk.cwkw,
	[GCC_PCIE_1_AUX_CWK] = &gcc_pcie_1_aux_cwk.cwkw,
	[GCC_PCIE_1_PIPE_CWK] = &gcc_pcie_1_pipe_cwk.cwkw,
	[GCC_PCIE_2_SWV_AXI_CWK] = &gcc_pcie_2_swv_axi_cwk.cwkw,
	[GCC_PCIE_2_MSTW_AXI_CWK] = &gcc_pcie_2_mstw_axi_cwk.cwkw,
	[GCC_PCIE_2_CFG_AHB_CWK] = &gcc_pcie_2_cfg_ahb_cwk.cwkw,
	[GCC_PCIE_2_AUX_CWK] = &gcc_pcie_2_aux_cwk.cwkw,
	[GCC_PCIE_2_PIPE_CWK] = &gcc_pcie_2_pipe_cwk.cwkw,
	[GCC_PCIE_PHY_CFG_AHB_CWK] = &gcc_pcie_phy_cfg_ahb_cwk.cwkw,
	[GCC_PCIE_PHY_AUX_CWK] = &gcc_pcie_phy_aux_cwk.cwkw,
	[GCC_UFS_AXI_CWK] = &gcc_ufs_axi_cwk.cwkw,
	[GCC_UFS_AHB_CWK] = &gcc_ufs_ahb_cwk.cwkw,
	[GCC_UFS_TX_CFG_CWK] = &gcc_ufs_tx_cfg_cwk.cwkw,
	[GCC_UFS_WX_CFG_CWK] = &gcc_ufs_wx_cfg_cwk.cwkw,
	[GCC_HWOS1_VOTE_WPASS_COWE_SMMU_CWK] = &gcc_hwos1_vote_wpass_cowe_smmu_cwk.cwkw,
	[GCC_HWOS1_VOTE_WPASS_ADSP_SMMU_CWK] = &gcc_hwos1_vote_wpass_adsp_smmu_cwk.cwkw,
	[GCC_UFS_TX_SYMBOW_0_CWK] = &gcc_ufs_tx_symbow_0_cwk.cwkw,
	[GCC_UFS_WX_SYMBOW_0_CWK] = &gcc_ufs_wx_symbow_0_cwk.cwkw,
	[GCC_UFS_WX_SYMBOW_1_CWK] = &gcc_ufs_wx_symbow_1_cwk.cwkw,
	[GCC_UFS_UNIPWO_COWE_CWK] = &gcc_ufs_unipwo_cowe_cwk.cwkw,
	[GCC_UFS_ICE_COWE_CWK] = &gcc_ufs_ice_cowe_cwk.cwkw,
	[GCC_UFS_SYS_CWK_COWE_CWK] = &gcc_ufs_sys_cwk_cowe_cwk.cwkw,
	[GCC_UFS_TX_SYMBOW_CWK_COWE_CWK] = &gcc_ufs_tx_symbow_cwk_cowe_cwk.cwkw,
	[GCC_AGGWE0_SNOC_AXI_CWK] = &gcc_aggwe0_snoc_axi_cwk.cwkw,
	[GCC_AGGWE0_CNOC_AHB_CWK] = &gcc_aggwe0_cnoc_ahb_cwk.cwkw,
	[GCC_SMMU_AGGWE0_AXI_CWK] = &gcc_smmu_aggwe0_axi_cwk.cwkw,
	[GCC_SMMU_AGGWE0_AHB_CWK] = &gcc_smmu_aggwe0_ahb_cwk.cwkw,
	[GCC_AGGWE2_UFS_AXI_CWK] = &gcc_aggwe2_ufs_axi_cwk.cwkw,
	[GCC_AGGWE2_USB3_AXI_CWK] = &gcc_aggwe2_usb3_axi_cwk.cwkw,
	[GCC_QSPI_AHB_CWK] = &gcc_qspi_ahb_cwk.cwkw,
	[GCC_QSPI_SEW_CWK] = &gcc_qspi_sew_cwk.cwkw,
	[GCC_USB3_CWKWEF_CWK] = &gcc_usb3_cwkwef_cwk.cwkw,
	[GCC_HDMI_CWKWEF_CWK] = &gcc_hdmi_cwkwef_cwk.cwkw,
	[GCC_UFS_CWKWEF_CWK] = &gcc_ufs_cwkwef_cwk.cwkw,
	[GCC_PCIE_CWKWEF_CWK] = &gcc_pcie_cwkwef_cwk.cwkw,
	[GCC_WX2_USB2_CWKWEF_CWK] = &gcc_wx2_usb2_cwkwef_cwk.cwkw,
	[GCC_WX1_USB2_CWKWEF_CWK] = &gcc_wx1_usb2_cwkwef_cwk.cwkw,
	[GCC_EDP_CWKWEF_CWK] = &gcc_edp_cwkwef_cwk.cwkw,
	[GCC_MSS_CFG_AHB_CWK] = &gcc_mss_cfg_ahb_cwk.cwkw,
	[GCC_MSS_Q6_BIMC_AXI_CWK] = &gcc_mss_q6_bimc_axi_cwk.cwkw,
	[GCC_MSS_SNOC_AXI_CWK] = &gcc_mss_snoc_axi_cwk.cwkw,
	[GCC_MSS_MNOC_BIMC_AXI_CWK] = &gcc_mss_mnoc_bimc_axi_cwk.cwkw,
	[GCC_DCC_AHB_CWK] = &gcc_dcc_ahb_cwk.cwkw,
	[GCC_AGGWE0_NOC_MPU_CFG_AHB_CWK] = &gcc_aggwe0_noc_mpu_cfg_ahb_cwk.cwkw,
	[GCC_MMSS_GPWW0_DIV_CWK] = &gcc_mmss_gpww0_div_cwk.cwkw,
	[GCC_MSS_GPWW0_DIV_CWK] = &gcc_mss_gpww0_div_cwk.cwkw,
};

static stwuct gdsc *gcc_msm8996_gdscs[] = {
	[AGGWE0_NOC_GDSC] = &aggwe0_noc_gdsc,
	[HWOS1_VOTE_AGGWE0_NOC_GDSC] = &hwos1_vote_aggwe0_noc_gdsc,
	[HWOS1_VOTE_WPASS_ADSP_GDSC] = &hwos1_vote_wpass_adsp_gdsc,
	[HWOS1_VOTE_WPASS_COWE_GDSC] = &hwos1_vote_wpass_cowe_gdsc,
	[USB30_GDSC] = &usb30_gdsc,
	[PCIE0_GDSC] = &pcie0_gdsc,
	[PCIE1_GDSC] = &pcie1_gdsc,
	[PCIE2_GDSC] = &pcie2_gdsc,
	[UFS_GDSC] = &ufs_gdsc,
};

static const stwuct qcom_weset_map gcc_msm8996_wesets[] = {
	[GCC_SYSTEM_NOC_BCW] = { 0x4000 },
	[GCC_CONFIG_NOC_BCW] = { 0x5000 },
	[GCC_PEWIPH_NOC_BCW] = { 0x6000 },
	[GCC_IMEM_BCW] = { 0x8000 },
	[GCC_MMSS_BCW] = { 0x9000 },
	[GCC_PIMEM_BCW] = { 0x0a000 },
	[GCC_QDSS_BCW] = { 0x0c000 },
	[GCC_USB_30_BCW] = { 0x0f000 },
	[GCC_USB_20_BCW] = { 0x12000 },
	[GCC_QUSB2PHY_PWIM_BCW] = { 0x12038 },
	[GCC_QUSB2PHY_SEC_BCW] = { 0x1203c },
	[GCC_USB3_PHY_BCW] = { 0x50020 },
	[GCC_USB3PHY_PHY_BCW] = { 0x50024 },
	[GCC_USB_PHY_CFG_AHB2PHY_BCW] = { 0x6a000 },
	[GCC_SDCC1_BCW] = { 0x13000 },
	[GCC_SDCC2_BCW] = { 0x14000 },
	[GCC_SDCC3_BCW] = { 0x15000 },
	[GCC_SDCC4_BCW] = { 0x16000 },
	[GCC_BWSP1_BCW] = { 0x17000 },
	[GCC_BWSP1_QUP1_BCW] = { 0x19000 },
	[GCC_BWSP1_UAWT1_BCW] = { 0x1a000 },
	[GCC_BWSP1_QUP2_BCW] = { 0x1b000 },
	[GCC_BWSP1_UAWT2_BCW] = { 0x1c000 },
	[GCC_BWSP1_QUP3_BCW] = { 0x1d000 },
	[GCC_BWSP1_UAWT3_BCW] = { 0x1e000 },
	[GCC_BWSP1_QUP4_BCW] = { 0x1f000 },
	[GCC_BWSP1_UAWT4_BCW] = { 0x20000 },
	[GCC_BWSP1_QUP5_BCW] = { 0x21000 },
	[GCC_BWSP1_UAWT5_BCW] = { 0x22000 },
	[GCC_BWSP1_QUP6_BCW] = { 0x23000 },
	[GCC_BWSP1_UAWT6_BCW] = { 0x24000 },
	[GCC_BWSP2_BCW] = { 0x25000 },
	[GCC_BWSP2_QUP1_BCW] = { 0x26000 },
	[GCC_BWSP2_UAWT1_BCW] = { 0x27000 },
	[GCC_BWSP2_QUP2_BCW] = { 0x28000 },
	[GCC_BWSP2_UAWT2_BCW] = { 0x29000 },
	[GCC_BWSP2_QUP3_BCW] = { 0x2a000 },
	[GCC_BWSP2_UAWT3_BCW] = { 0x2b000 },
	[GCC_BWSP2_QUP4_BCW] = { 0x2c000 },
	[GCC_BWSP2_UAWT4_BCW] = { 0x2d000 },
	[GCC_BWSP2_QUP5_BCW] = { 0x2e000 },
	[GCC_BWSP2_UAWT5_BCW] = { 0x2f000 },
	[GCC_BWSP2_QUP6_BCW] = { 0x30000 },
	[GCC_BWSP2_UAWT6_BCW] = { 0x31000 },
	[GCC_PDM_BCW] = { 0x33000 },
	[GCC_PWNG_BCW] = { 0x34000 },
	[GCC_TSIF_BCW] = { 0x36000 },
	[GCC_TCSW_BCW] = { 0x37000 },
	[GCC_BOOT_WOM_BCW] = { 0x38000 },
	[GCC_MSG_WAM_BCW] = { 0x39000 },
	[GCC_TWMM_BCW] = { 0x3a000 },
	[GCC_MPM_BCW] = { 0x3b000 },
	[GCC_SEC_CTWW_BCW] = { 0x3d000 },
	[GCC_SPMI_BCW] = { 0x3f000 },
	[GCC_SPDM_BCW] = { 0x40000 },
	[GCC_CE1_BCW] = { 0x41000 },
	[GCC_BIMC_BCW] = { 0x44000 },
	[GCC_SNOC_BUS_TIMEOUT0_BCW] = { 0x49000 },
	[GCC_SNOC_BUS_TIMEOUT2_BCW] = { 0x49008 },
	[GCC_SNOC_BUS_TIMEOUT1_BCW] = { 0x49010 },
	[GCC_SNOC_BUS_TIMEOUT3_BCW] = { 0x49018 },
	[GCC_SNOC_BUS_TIMEOUT_EXTWEF_BCW] = { 0x49020 },
	[GCC_PNOC_BUS_TIMEOUT0_BCW] = { 0x4a000 },
	[GCC_PNOC_BUS_TIMEOUT1_BCW] = { 0x4a008 },
	[GCC_PNOC_BUS_TIMEOUT2_BCW] = { 0x4a010 },
	[GCC_PNOC_BUS_TIMEOUT3_BCW] = { 0x4a018 },
	[GCC_PNOC_BUS_TIMEOUT4_BCW] = { 0x4a020 },
	[GCC_CNOC_BUS_TIMEOUT0_BCW] = { 0x4b000 },
	[GCC_CNOC_BUS_TIMEOUT1_BCW] = { 0x4b008 },
	[GCC_CNOC_BUS_TIMEOUT2_BCW] = { 0x4b010 },
	[GCC_CNOC_BUS_TIMEOUT3_BCW] = { 0x4b018 },
	[GCC_CNOC_BUS_TIMEOUT4_BCW] = { 0x4b020 },
	[GCC_CNOC_BUS_TIMEOUT5_BCW] = { 0x4b028 },
	[GCC_CNOC_BUS_TIMEOUT6_BCW] = { 0x4b030 },
	[GCC_CNOC_BUS_TIMEOUT7_BCW] = { 0x4b038 },
	[GCC_CNOC_BUS_TIMEOUT8_BCW] = { 0x80000 },
	[GCC_CNOC_BUS_TIMEOUT9_BCW] = { 0x80008 },
	[GCC_CNOC_BUS_TIMEOUT_EXTWEF_BCW] = { 0x80010 },
	[GCC_APB2JTAG_BCW] = { 0x4c000 },
	[GCC_WBCPW_CX_BCW] = { 0x4e000 },
	[GCC_WBCPW_MX_BCW] = { 0x4f000 },
	[GCC_PCIE_0_BCW] = { 0x6b000 },
	[GCC_PCIE_0_PHY_BCW] = { 0x6c01c },
	[GCC_PCIE_1_BCW] = { 0x6d000 },
	[GCC_PCIE_1_PHY_BCW] = { 0x6d038 },
	[GCC_PCIE_2_BCW] = { 0x6e000 },
	[GCC_PCIE_2_PHY_BCW] = { 0x6e038 },
	[GCC_PCIE_PHY_BCW] = { 0x6f000 },
	[GCC_PCIE_PHY_COM_BCW] = { 0x6f014 },
	[GCC_PCIE_PHY_COM_NOCSW_BCW] = { 0x6f00c },
	[GCC_DCD_BCW] = { 0x70000 },
	[GCC_OBT_ODT_BCW] = { 0x73000 },
	[GCC_UFS_BCW] = { 0x75000 },
	[GCC_SSC_BCW] = { 0x63000 },
	[GCC_VS_BCW] = { 0x7a000 },
	[GCC_AGGWE0_NOC_BCW] = { 0x81000 },
	[GCC_AGGWE1_NOC_BCW] = { 0x82000 },
	[GCC_AGGWE2_NOC_BCW] = { 0x83000 },
	[GCC_DCC_BCW] = { 0x84000 },
	[GCC_IPA_BCW] = { 0x89000 },
	[GCC_QSPI_BCW] = { 0x8b000 },
	[GCC_SKW_BCW] = { 0x8c000 },
	[GCC_MSMPU_BCW] = { 0x8d000 },
	[GCC_MSS_Q6_BCW] = { 0x8e000 },
	[GCC_QWEFS_VBG_CAW_BCW] = { 0x88020 },
	[GCC_MSS_WESTAWT] = { 0x8f008 },
};

static const stwuct wegmap_config gcc_msm8996_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x8f010,
	.fast_io	= twue,
};

static const stwuct qcom_cc_desc gcc_msm8996_desc = {
	.config = &gcc_msm8996_wegmap_config,
	.cwks = gcc_msm8996_cwocks,
	.num_cwks = AWWAY_SIZE(gcc_msm8996_cwocks),
	.wesets = gcc_msm8996_wesets,
	.num_wesets = AWWAY_SIZE(gcc_msm8996_wesets),
	.gdscs = gcc_msm8996_gdscs,
	.num_gdscs = AWWAY_SIZE(gcc_msm8996_gdscs),
	.cwk_hws = gcc_msm8996_hws,
	.num_cwk_hws = AWWAY_SIZE(gcc_msm8996_hws),
};

static const stwuct of_device_id gcc_msm8996_match_tabwe[] = {
	{ .compatibwe = "qcom,gcc-msm8996" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gcc_msm8996_match_tabwe);

static int gcc_msm8996_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, &gcc_msm8996_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/*
	 * Set the HMSS_AHB_CWK_SWEEP_ENA bit to awwow the hmss_ahb_cwk to be
	 * tuwned off by hawdwawe duwing cewtain apps wow powew modes.
	 */
	wegmap_update_bits(wegmap, 0x52008, BIT(21), BIT(21));

	wetuwn qcom_cc_weawwy_pwobe(pdev, &gcc_msm8996_desc, wegmap);
}

static stwuct pwatfowm_dwivew gcc_msm8996_dwivew = {
	.pwobe		= gcc_msm8996_pwobe,
	.dwivew		= {
		.name	= "gcc-msm8996",
		.of_match_tabwe = gcc_msm8996_match_tabwe,
	},
};

static int __init gcc_msm8996_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gcc_msm8996_dwivew);
}
cowe_initcaww(gcc_msm8996_init);

static void __exit gcc_msm8996_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gcc_msm8996_dwivew);
}
moduwe_exit(gcc_msm8996_exit);

MODUWE_DESCWIPTION("QCOM GCC MSM8996 Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:gcc-msm8996");
