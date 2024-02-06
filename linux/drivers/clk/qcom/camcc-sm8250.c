// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2018-2021, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>

#incwude <dt-bindings/cwock/qcom,camcc-sm8250.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "common.h"
#incwude "gdsc.h"
#incwude "weset.h"

enum {
	P_BI_TCXO,
	P_CAM_CC_PWW0_OUT_EVEN,
	P_CAM_CC_PWW0_OUT_MAIN,
	P_CAM_CC_PWW0_OUT_ODD,
	P_CAM_CC_PWW1_OUT_EVEN,
	P_CAM_CC_PWW2_OUT_EAWWY,
	P_CAM_CC_PWW2_OUT_MAIN,
	P_CAM_CC_PWW3_OUT_EVEN,
	P_CAM_CC_PWW4_OUT_EVEN,
	P_SWEEP_CWK,
};

static stwuct pww_vco wucid_vco[] = {
	{ 249600000, 2000000000, 0 },
};

static stwuct pww_vco zonda_vco[] = {
	{ 595200000UW, 3600000000UW, 0 },
};

static const stwuct awpha_pww_config cam_cc_pww0_config = {
	.w = 0x3e,
	.awpha = 0x8000,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329A699c,
	.usew_ctw_vaw = 0x00003100,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww cam_cc_pww0 = {
	.offset = 0x0,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww0_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww0_out_even = {
	.offset = 0x0,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww0_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww0_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww0_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&cam_cc_pww0.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww0_out_odd[] = {
	{ 0x3, 3 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww0_out_odd = {
	.offset = 0x0,
	.post_div_shift = 12,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww0_out_odd,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww0_out_odd),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww0_out_odd",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&cam_cc_pww0.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static const stwuct awpha_pww_config cam_cc_pww1_config = {
	.w = 0x1f,
	.awpha = 0x4000,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329A699c,
	.usew_ctw_vaw = 0x00000100,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww cam_cc_pww1 = {
	.offset = 0x1000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_pww1",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww1_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww1_out_even = {
	.offset = 0x1000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww1_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww1_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww1_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&cam_cc_pww1.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static const stwuct awpha_pww_config cam_cc_pww2_config = {
	.w = 0x4b,
	.awpha = 0x0,
	.config_ctw_vaw = 0x08200920,
	.config_ctw_hi_vaw = 0x05002015,
	.config_ctw_hi1_vaw = 0x00000000,
	.usew_ctw_vaw = 0x00000100,
	.usew_ctw_hi_vaw = 0x00000000,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww cam_cc_pww2 = {
	.offset = 0x2000,
	.vco_tabwe = zonda_vco,
	.num_vco = AWWAY_SIZE(zonda_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_ZONDA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_pww2",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_zonda_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww2_out_main[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww2_out_main = {
	.offset = 0x2000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww2_out_main,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww2_out_main),
	.width = 2,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_ZONDA],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww2_out_main",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&cam_cc_pww2.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_zonda_ops,
	},
};

static const stwuct awpha_pww_config cam_cc_pww3_config = {
	.w = 0x24,
	.awpha = 0x7555,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329A699c,
	.usew_ctw_vaw = 0x00000100,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww cam_cc_pww3 = {
	.offset = 0x3000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_pww3",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww3_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww3_out_even = {
	.offset = 0x3000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww3_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww3_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww3_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&cam_cc_pww3.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static const stwuct awpha_pww_config cam_cc_pww4_config = {
	.w = 0x24,
	.awpha = 0x7555,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329A699c,
	.usew_ctw_vaw = 0x00000100,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww cam_cc_pww4 = {
	.offset = 0x4000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_pww4",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_cam_cc_pww4_out_even[] = {
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww4_out_even = {
	.offset = 0x4000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_cam_cc_pww4_out_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_cam_cc_pww4_out_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww4_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&cam_cc_pww4.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static const stwuct pawent_map cam_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW0_OUT_MAIN, 1 },
	{ P_CAM_CC_PWW0_OUT_EVEN, 2 },
	{ P_CAM_CC_PWW0_OUT_ODD, 3 },
	{ P_CAM_CC_PWW2_OUT_MAIN, 5 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_0[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &cam_cc_pww0.cwkw.hw },
	{ .hw = &cam_cc_pww0_out_even.cwkw.hw },
	{ .hw = &cam_cc_pww0_out_odd.cwkw.hw },
	{ .hw = &cam_cc_pww2_out_main.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW2_OUT_EAWWY, 5 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_1[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &cam_cc_pww2.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW3_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_2[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &cam_cc_pww3_out_even.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_3[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW4_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_3[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &cam_cc_pww4_out_even.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_4[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW1_OUT_EVEN, 4 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_4[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &cam_cc_pww1_out_even.cwkw.hw },
};

static const stwuct pawent_map cam_cc_pawent_map_5[] = {
	{ P_SWEEP_CWK, 0 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_5[] = {
	{ .fw_name = "sweep_cwk" },
};

static const stwuct pawent_map cam_cc_pawent_map_6[] = {
	{ P_BI_TCXO, 0 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_6[] = {
	{ .fw_name = "bi_tcxo" },
};

static const stwuct fweq_tbw ftbw_cam_cc_bps_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_CAM_CC_PWW0_OUT_EVEN, 6, 0, 0),
	F(200000000, P_CAM_CC_PWW0_OUT_ODD, 2, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_ODD, 1, 0, 0),
	F(480000000, P_CAM_CC_PWW2_OUT_MAIN, 1.5, 0, 0),
	F(600000000, P_CAM_CC_PWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_bps_cwk_swc = {
	.cmd_wcgw = 0x7010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_bps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_bps_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_camnoc_axi_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(300000000, P_CAM_CC_PWW0_OUT_EVEN, 2, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_ODD, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_camnoc_axi_cwk_swc = {
	.cmd_wcgw = 0xc0f8,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_camnoc_axi_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_camnoc_axi_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_cci_0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(37500000, P_CAM_CC_PWW0_OUT_EVEN, 16, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_cci_0_cwk_swc = {
	.cmd_wcgw = 0xc0bc,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_cci_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_cci_0_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_cci_1_cwk_swc = {
	.cmd_wcgw = 0xc0d8,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_cci_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_cci_1_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_cphy_wx_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_ODD, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_cphy_wx_cwk_swc = {
	.cmd_wcgw = 0xa068,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_cphy_wx_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_cphy_wx_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_csi0phytimew_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(300000000, P_CAM_CC_PWW0_OUT_EVEN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_csi0phytimew_cwk_swc = {
	.cmd_wcgw = 0x6000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_csi0phytimew_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_csi1phytimew_cwk_swc = {
	.cmd_wcgw = 0x6020,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_csi1phytimew_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_csi2phytimew_cwk_swc = {
	.cmd_wcgw = 0x6040,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_csi2phytimew_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_csi3phytimew_cwk_swc = {
	.cmd_wcgw = 0x6060,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_csi3phytimew_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_csi4phytimew_cwk_swc = {
	.cmd_wcgw = 0x6080,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_csi4phytimew_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_csi5phytimew_cwk_swc = {
	.cmd_wcgw = 0x60a0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_csi0phytimew_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_csi5phytimew_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_fast_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(50000000, P_CAM_CC_PWW0_OUT_EVEN, 12, 0, 0),
	F(100000000, P_CAM_CC_PWW0_OUT_EVEN, 6, 0, 0),
	F(200000000, P_CAM_CC_PWW0_OUT_EVEN, 3, 0, 0),
	F(300000000, P_CAM_CC_PWW0_OUT_MAIN, 4, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_fast_ahb_cwk_swc = {
	.cmd_wcgw = 0x703c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_fast_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_fast_ahb_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_fd_cowe_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_ODD, 1, 0, 0),
	F(480000000, P_CAM_CC_PWW2_OUT_MAIN, 1.5, 0, 0),
	F(600000000, P_CAM_CC_PWW0_OUT_MAIN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_fd_cowe_cwk_swc = {
	.cmd_wcgw = 0xc098,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_fd_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_fd_cowe_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_icp_cwk_swc = {
	.cmd_wcgw = 0xc074,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_fd_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_icp_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ife_0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(350000000, P_CAM_CC_PWW3_OUT_EVEN, 1, 0, 0),
	F(475000000, P_CAM_CC_PWW3_OUT_EVEN, 1, 0, 0),
	F(576000000, P_CAM_CC_PWW3_OUT_EVEN, 1, 0, 0),
	F(680000000, P_CAM_CC_PWW3_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ife_0_cwk_swc = {
	.cmd_wcgw = 0xa010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_2,
	.fweq_tbw = ftbw_cam_cc_ife_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_0_cwk_swc",
		.pawent_data = cam_cc_pawent_data_2,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_2),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wegmap_div cam_cc_sbi_div_cwk_swc = {
	.weg = 0x9010,
	.shift = 0,
	.width = 3,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "cam_cc_sbi_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&cam_cc_ife_0_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ife_0_csid_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(75000000, P_CAM_CC_PWW0_OUT_EVEN, 8, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_ODD, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ife_0_csid_cwk_swc = {
	.cmd_wcgw = 0xa040,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_ife_0_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_0_csid_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ife_1_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(350000000, P_CAM_CC_PWW4_OUT_EVEN, 1, 0, 0),
	F(475000000, P_CAM_CC_PWW4_OUT_EVEN, 1, 0, 0),
	F(576000000, P_CAM_CC_PWW4_OUT_EVEN, 1, 0, 0),
	F(680000000, P_CAM_CC_PWW4_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ife_1_cwk_swc = {
	.cmd_wcgw = 0xb010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_3,
	.fweq_tbw = ftbw_cam_cc_ife_1_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_1_cwk_swc",
		.pawent_data = cam_cc_pawent_data_3,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_3),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_ife_1_csid_cwk_swc = {
	.cmd_wcgw = 0xb040,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_ife_0_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_1_csid_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ife_wite_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_ODD, 1, 0, 0),
	F(480000000, P_CAM_CC_PWW2_OUT_MAIN, 1.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ife_wite_cwk_swc = {
	.cmd_wcgw = 0xc000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_ife_wite_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_wite_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_ife_wite_csid_cwk_swc = {
	.cmd_wcgw = 0xc01c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_cphy_wx_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_wite_csid_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ipe_0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(300000000, P_CAM_CC_PWW1_OUT_EVEN, 1, 0, 0),
	F(475000000, P_CAM_CC_PWW1_OUT_EVEN, 1, 0, 0),
	F(525000000, P_CAM_CC_PWW1_OUT_EVEN, 1, 0, 0),
	F(700000000, P_CAM_CC_PWW1_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ipe_0_cwk_swc = {
	.cmd_wcgw = 0x8010,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_4,
	.fweq_tbw = ftbw_cam_cc_ipe_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ipe_0_cwk_swc",
		.pawent_data = cam_cc_pawent_data_4,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_4),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_jpeg_cwk_swc = {
	.cmd_wcgw = 0xc048,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_bps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_jpeg_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_mcwk0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(24000000, P_CAM_CC_PWW2_OUT_EAWWY, 10, 1, 6),
	F(68571429, P_CAM_CC_PWW2_OUT_EAWWY, 1, 1, 21),
	{ }
};

static stwuct cwk_wcg2 cam_cc_mcwk0_cwk_swc = {
	.cmd_wcgw = 0x5000,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_mcwk0_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk1_cwk_swc = {
	.cmd_wcgw = 0x501c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_mcwk1_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk2_cwk_swc = {
	.cmd_wcgw = 0x5038,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_mcwk2_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk3_cwk_swc = {
	.cmd_wcgw = 0x5054,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_mcwk3_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk4_cwk_swc = {
	.cmd_wcgw = 0x5070,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_mcwk4_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk5_cwk_swc = {
	.cmd_wcgw = 0x508c,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_mcwk5_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk6_cwk_swc = {
	.cmd_wcgw = 0x50a8,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_1,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_mcwk6_cwk_swc",
		.pawent_data = cam_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_sbi_csid_cwk_swc = {
	.cmd_wcgw = 0x901c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_cphy_wx_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_sbi_csid_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_sweep_cwk_swc[] = {
	F(32768, P_SWEEP_CWK, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_sweep_cwk_swc = {
	.cmd_wcgw = 0xc170,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_5,
	.fweq_tbw = ftbw_cam_cc_sweep_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_sweep_cwk_swc",
		.pawent_data = cam_cc_pawent_data_5,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_5),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_swow_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(80000000, P_CAM_CC_PWW0_OUT_EVEN, 7.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_swow_ahb_cwk_swc = {
	.cmd_wcgw = 0x7058,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_swow_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_swow_ahb_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_xo_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_xo_cwk_swc = {
	.cmd_wcgw = 0xc154,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_6,
	.fweq_tbw = ftbw_cam_cc_xo_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_xo_cwk_swc",
		.pawent_data = cam_cc_pawent_data_6,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_6),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch cam_cc_bps_ahb_cwk = {
	.hawt_weg = 0x7070,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7070,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_bps_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_bps_aweg_cwk = {
	.hawt_weg = 0x7054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_bps_aweg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_bps_axi_cwk = {
	.hawt_weg = 0x7038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_bps_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_camnoc_axi_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_bps_cwk = {
	.hawt_weg = 0x7028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_bps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_bps_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_camnoc_axi_cwk = {
	.hawt_weg = 0xc114,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc114,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_camnoc_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_camnoc_axi_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_camnoc_dcd_xo_cwk = {
	.hawt_weg = 0xc11c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc11c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_camnoc_dcd_xo_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_xo_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cci_0_cwk = {
	.hawt_weg = 0xc0d4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc0d4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_cci_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cci_0_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cci_1_cwk = {
	.hawt_weg = 0xc0f0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc0f0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_cci_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cci_1_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cowe_ahb_cwk = {
	.hawt_weg = 0xc150,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0xc150,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_cowe_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cpas_ahb_cwk = {
	.hawt_weg = 0xc0f4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc0f4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_cpas_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csi0phytimew_cwk = {
	.hawt_weg = 0x6018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csi0phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_csi0phytimew_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csi1phytimew_cwk = {
	.hawt_weg = 0x6038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csi1phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_csi1phytimew_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csi2phytimew_cwk = {
	.hawt_weg = 0x6058,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6058,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csi2phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_csi2phytimew_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csi3phytimew_cwk = {
	.hawt_weg = 0x6078,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6078,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csi3phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_csi3phytimew_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csi4phytimew_cwk = {
	.hawt_weg = 0x6098,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6098,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csi4phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_csi4phytimew_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csi5phytimew_cwk = {
	.hawt_weg = 0x60b8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x60b8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csi5phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_csi5phytimew_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csiphy0_cwk = {
	.hawt_weg = 0x601c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x601c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csiphy0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csiphy1_cwk = {
	.hawt_weg = 0x603c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x603c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csiphy1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csiphy2_cwk = {
	.hawt_weg = 0x605c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x605c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csiphy2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csiphy3_cwk = {
	.hawt_weg = 0x607c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x607c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csiphy3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csiphy4_cwk = {
	.hawt_weg = 0x609c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x609c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csiphy4_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csiphy5_cwk = {
	.hawt_weg = 0x60bc,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x60bc,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csiphy5_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_fd_cowe_cwk = {
	.hawt_weg = 0xc0b0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc0b0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_fd_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_fd_cowe_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_fd_cowe_uaw_cwk = {
	.hawt_weg = 0xc0b8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc0b8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_fd_cowe_uaw_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_fd_cowe_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_gdsc_cwk = {
	.hawt_weg = 0xc16c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc16c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_gdsc_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_xo_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_icp_ahb_cwk = {
	.hawt_weg = 0xc094,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc094,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_icp_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_icp_cwk = {
	.hawt_weg = 0xc08c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc08c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_icp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_icp_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_ahb_cwk = {
	.hawt_weg = 0xa088,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa088,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_0_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_aweg_cwk = {
	.hawt_weg = 0xa030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_0_aweg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_axi_cwk = {
	.hawt_weg = 0xa084,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa084,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_0_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_camnoc_axi_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_cwk = {
	.hawt_weg = 0xa028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_0_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_cphy_wx_cwk = {
	.hawt_weg = 0xa080,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa080,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_0_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_csid_cwk = {
	.hawt_weg = 0xa058,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa058,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_0_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_0_csid_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_dsp_cwk = {
	.hawt_weg = 0xa03c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa03c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_0_dsp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_0_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_ahb_cwk = {
	.hawt_weg = 0xb068,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb068,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_1_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_aweg_cwk = {
	.hawt_weg = 0xb030,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb030,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_1_aweg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_axi_cwk = {
	.hawt_weg = 0xb064,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb064,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_1_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_camnoc_axi_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_cwk = {
	.hawt_weg = 0xb028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_1_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_cphy_wx_cwk = {
	.hawt_weg = 0xb060,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb060,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_1_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_csid_cwk = {
	.hawt_weg = 0xb058,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb058,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_1_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_1_csid_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_dsp_cwk = {
	.hawt_weg = 0xb03c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb03c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_1_dsp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_1_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_wite_ahb_cwk = {
	.hawt_weg = 0xc040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_wite_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_wite_axi_cwk = {
	.hawt_weg = 0xc044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc044,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_wite_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_camnoc_axi_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_wite_cwk = {
	.hawt_weg = 0xc018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_wite_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_wite_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_wite_cphy_wx_cwk = {
	.hawt_weg = 0xc03c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc03c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_wite_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_wite_csid_cwk = {
	.hawt_weg = 0xc034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_wite_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_wite_csid_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_0_ahb_cwk = {
	.hawt_weg = 0x8040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ipe_0_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_0_aweg_cwk = {
	.hawt_weg = 0x803c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x803c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ipe_0_aweg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_0_axi_cwk = {
	.hawt_weg = 0x8038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ipe_0_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_camnoc_axi_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_0_cwk = {
	.hawt_weg = 0x8028,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8028,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ipe_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ipe_0_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_jpeg_cwk = {
	.hawt_weg = 0xc060,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc060,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_jpeg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_jpeg_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk0_cwk = {
	.hawt_weg = 0x5018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_mcwk0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_mcwk0_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk1_cwk = {
	.hawt_weg = 0x5034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_mcwk1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_mcwk1_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk2_cwk = {
	.hawt_weg = 0x5050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_mcwk2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_mcwk2_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk3_cwk = {
	.hawt_weg = 0x506c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x506c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_mcwk3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_mcwk3_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk4_cwk = {
	.hawt_weg = 0x5088,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5088,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_mcwk4_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_mcwk4_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk5_cwk = {
	.hawt_weg = 0x50a4,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x50a4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_mcwk5_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_mcwk5_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk6_cwk = {
	.hawt_weg = 0x50c0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x50c0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_mcwk6_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_mcwk6_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_sbi_ahb_cwk = {
	.hawt_weg = 0x9040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_sbi_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_sbi_axi_cwk = {
	.hawt_weg = 0x903c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x903c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_sbi_axi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_camnoc_axi_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_sbi_cwk = {
	.hawt_weg = 0x9014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_sbi_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_sbi_div_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_sbi_cphy_wx_cwk = {
	.hawt_weg = 0x9038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_sbi_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_sbi_csid_cwk = {
	.hawt_weg = 0x9034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_sbi_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_sbi_csid_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_sbi_ife_0_cwk = {
	.hawt_weg = 0x9044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9044,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_sbi_ife_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_0_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_sbi_ife_1_cwk = {
	.hawt_weg = 0x9048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9048,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_sbi_ife_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_1_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_sweep_cwk = {
	.hawt_weg = 0xc188,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xc188,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_sweep_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_sweep_cwk_swc.cwkw.hw
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc titan_top_gdsc;

static stwuct gdsc bps_gdsc = {
	.gdscw = 0x7004,
	.pd = {
		.name = "bps_gdsc",
	},
	.fwags = HW_CTWW | POWW_CFG_GDSCW,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ipe_0_gdsc = {
	.gdscw = 0x8004,
	.pd = {
		.name = "ipe_0_gdsc",
	},
	.fwags = HW_CTWW | POWW_CFG_GDSCW,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc sbi_gdsc = {
	.gdscw = 0x9004,
	.pd = {
		.name = "sbi_gdsc",
	},
	.fwags = HW_CTWW | POWW_CFG_GDSCW,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ife_0_gdsc = {
	.gdscw = 0xa004,
	.pd = {
		.name = "ife_0_gdsc",
	},
	.fwags = POWW_CFG_GDSCW,
	.pawent = &titan_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ife_1_gdsc = {
	.gdscw = 0xb004,
	.pd = {
		.name = "ife_1_gdsc",
	},
	.fwags = POWW_CFG_GDSCW,
	.pawent = &titan_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc titan_top_gdsc = {
	.gdscw = 0xc144,
	.pd = {
		.name = "titan_top_gdsc",
	},
	.fwags = POWW_CFG_GDSCW,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct cwk_wegmap *cam_cc_sm8250_cwocks[] = {
	[CAM_CC_BPS_AHB_CWK] = &cam_cc_bps_ahb_cwk.cwkw,
	[CAM_CC_BPS_AWEG_CWK] = &cam_cc_bps_aweg_cwk.cwkw,
	[CAM_CC_BPS_AXI_CWK] = &cam_cc_bps_axi_cwk.cwkw,
	[CAM_CC_BPS_CWK] = &cam_cc_bps_cwk.cwkw,
	[CAM_CC_BPS_CWK_SWC] = &cam_cc_bps_cwk_swc.cwkw,
	[CAM_CC_CAMNOC_AXI_CWK] = &cam_cc_camnoc_axi_cwk.cwkw,
	[CAM_CC_CAMNOC_AXI_CWK_SWC] = &cam_cc_camnoc_axi_cwk_swc.cwkw,
	[CAM_CC_CAMNOC_DCD_XO_CWK] = &cam_cc_camnoc_dcd_xo_cwk.cwkw,
	[CAM_CC_CCI_0_CWK] = &cam_cc_cci_0_cwk.cwkw,
	[CAM_CC_CCI_0_CWK_SWC] = &cam_cc_cci_0_cwk_swc.cwkw,
	[CAM_CC_CCI_1_CWK] = &cam_cc_cci_1_cwk.cwkw,
	[CAM_CC_CCI_1_CWK_SWC] = &cam_cc_cci_1_cwk_swc.cwkw,
	[CAM_CC_COWE_AHB_CWK] = &cam_cc_cowe_ahb_cwk.cwkw,
	[CAM_CC_CPAS_AHB_CWK] = &cam_cc_cpas_ahb_cwk.cwkw,
	[CAM_CC_CPHY_WX_CWK_SWC] = &cam_cc_cphy_wx_cwk_swc.cwkw,
	[CAM_CC_CSI0PHYTIMEW_CWK] = &cam_cc_csi0phytimew_cwk.cwkw,
	[CAM_CC_CSI0PHYTIMEW_CWK_SWC] = &cam_cc_csi0phytimew_cwk_swc.cwkw,
	[CAM_CC_CSI1PHYTIMEW_CWK] = &cam_cc_csi1phytimew_cwk.cwkw,
	[CAM_CC_CSI1PHYTIMEW_CWK_SWC] = &cam_cc_csi1phytimew_cwk_swc.cwkw,
	[CAM_CC_CSI2PHYTIMEW_CWK] = &cam_cc_csi2phytimew_cwk.cwkw,
	[CAM_CC_CSI2PHYTIMEW_CWK_SWC] = &cam_cc_csi2phytimew_cwk_swc.cwkw,
	[CAM_CC_CSI3PHYTIMEW_CWK] = &cam_cc_csi3phytimew_cwk.cwkw,
	[CAM_CC_CSI3PHYTIMEW_CWK_SWC] = &cam_cc_csi3phytimew_cwk_swc.cwkw,
	[CAM_CC_CSI4PHYTIMEW_CWK] = &cam_cc_csi4phytimew_cwk.cwkw,
	[CAM_CC_CSI4PHYTIMEW_CWK_SWC] = &cam_cc_csi4phytimew_cwk_swc.cwkw,
	[CAM_CC_CSI5PHYTIMEW_CWK] = &cam_cc_csi5phytimew_cwk.cwkw,
	[CAM_CC_CSI5PHYTIMEW_CWK_SWC] = &cam_cc_csi5phytimew_cwk_swc.cwkw,
	[CAM_CC_CSIPHY0_CWK] = &cam_cc_csiphy0_cwk.cwkw,
	[CAM_CC_CSIPHY1_CWK] = &cam_cc_csiphy1_cwk.cwkw,
	[CAM_CC_CSIPHY2_CWK] = &cam_cc_csiphy2_cwk.cwkw,
	[CAM_CC_CSIPHY3_CWK] = &cam_cc_csiphy3_cwk.cwkw,
	[CAM_CC_CSIPHY4_CWK] = &cam_cc_csiphy4_cwk.cwkw,
	[CAM_CC_CSIPHY5_CWK] = &cam_cc_csiphy5_cwk.cwkw,
	[CAM_CC_FAST_AHB_CWK_SWC] = &cam_cc_fast_ahb_cwk_swc.cwkw,
	[CAM_CC_FD_COWE_CWK] = &cam_cc_fd_cowe_cwk.cwkw,
	[CAM_CC_FD_COWE_CWK_SWC] = &cam_cc_fd_cowe_cwk_swc.cwkw,
	[CAM_CC_FD_COWE_UAW_CWK] = &cam_cc_fd_cowe_uaw_cwk.cwkw,
	[CAM_CC_GDSC_CWK] = &cam_cc_gdsc_cwk.cwkw,
	[CAM_CC_ICP_AHB_CWK] = &cam_cc_icp_ahb_cwk.cwkw,
	[CAM_CC_ICP_CWK] = &cam_cc_icp_cwk.cwkw,
	[CAM_CC_ICP_CWK_SWC] = &cam_cc_icp_cwk_swc.cwkw,
	[CAM_CC_IFE_0_AHB_CWK] = &cam_cc_ife_0_ahb_cwk.cwkw,
	[CAM_CC_IFE_0_AWEG_CWK] = &cam_cc_ife_0_aweg_cwk.cwkw,
	[CAM_CC_IFE_0_AXI_CWK] = &cam_cc_ife_0_axi_cwk.cwkw,
	[CAM_CC_IFE_0_CWK] = &cam_cc_ife_0_cwk.cwkw,
	[CAM_CC_IFE_0_CWK_SWC] = &cam_cc_ife_0_cwk_swc.cwkw,
	[CAM_CC_IFE_0_CPHY_WX_CWK] = &cam_cc_ife_0_cphy_wx_cwk.cwkw,
	[CAM_CC_IFE_0_CSID_CWK] = &cam_cc_ife_0_csid_cwk.cwkw,
	[CAM_CC_IFE_0_CSID_CWK_SWC] = &cam_cc_ife_0_csid_cwk_swc.cwkw,
	[CAM_CC_IFE_0_DSP_CWK] = &cam_cc_ife_0_dsp_cwk.cwkw,
	[CAM_CC_IFE_1_AHB_CWK] = &cam_cc_ife_1_ahb_cwk.cwkw,
	[CAM_CC_IFE_1_AWEG_CWK] = &cam_cc_ife_1_aweg_cwk.cwkw,
	[CAM_CC_IFE_1_AXI_CWK] = &cam_cc_ife_1_axi_cwk.cwkw,
	[CAM_CC_IFE_1_CWK] = &cam_cc_ife_1_cwk.cwkw,
	[CAM_CC_IFE_1_CWK_SWC] = &cam_cc_ife_1_cwk_swc.cwkw,
	[CAM_CC_IFE_1_CPHY_WX_CWK] = &cam_cc_ife_1_cphy_wx_cwk.cwkw,
	[CAM_CC_IFE_1_CSID_CWK] = &cam_cc_ife_1_csid_cwk.cwkw,
	[CAM_CC_IFE_1_CSID_CWK_SWC] = &cam_cc_ife_1_csid_cwk_swc.cwkw,
	[CAM_CC_IFE_1_DSP_CWK] = &cam_cc_ife_1_dsp_cwk.cwkw,
	[CAM_CC_IFE_WITE_AHB_CWK] = &cam_cc_ife_wite_ahb_cwk.cwkw,
	[CAM_CC_IFE_WITE_AXI_CWK] = &cam_cc_ife_wite_axi_cwk.cwkw,
	[CAM_CC_IFE_WITE_CWK] = &cam_cc_ife_wite_cwk.cwkw,
	[CAM_CC_IFE_WITE_CWK_SWC] = &cam_cc_ife_wite_cwk_swc.cwkw,
	[CAM_CC_IFE_WITE_CPHY_WX_CWK] = &cam_cc_ife_wite_cphy_wx_cwk.cwkw,
	[CAM_CC_IFE_WITE_CSID_CWK] = &cam_cc_ife_wite_csid_cwk.cwkw,
	[CAM_CC_IFE_WITE_CSID_CWK_SWC] = &cam_cc_ife_wite_csid_cwk_swc.cwkw,
	[CAM_CC_IPE_0_AHB_CWK] = &cam_cc_ipe_0_ahb_cwk.cwkw,
	[CAM_CC_IPE_0_AWEG_CWK] = &cam_cc_ipe_0_aweg_cwk.cwkw,
	[CAM_CC_IPE_0_AXI_CWK] = &cam_cc_ipe_0_axi_cwk.cwkw,
	[CAM_CC_IPE_0_CWK] = &cam_cc_ipe_0_cwk.cwkw,
	[CAM_CC_IPE_0_CWK_SWC] = &cam_cc_ipe_0_cwk_swc.cwkw,
	[CAM_CC_JPEG_CWK] = &cam_cc_jpeg_cwk.cwkw,
	[CAM_CC_JPEG_CWK_SWC] = &cam_cc_jpeg_cwk_swc.cwkw,
	[CAM_CC_MCWK0_CWK] = &cam_cc_mcwk0_cwk.cwkw,
	[CAM_CC_MCWK0_CWK_SWC] = &cam_cc_mcwk0_cwk_swc.cwkw,
	[CAM_CC_MCWK1_CWK] = &cam_cc_mcwk1_cwk.cwkw,
	[CAM_CC_MCWK1_CWK_SWC] = &cam_cc_mcwk1_cwk_swc.cwkw,
	[CAM_CC_MCWK2_CWK] = &cam_cc_mcwk2_cwk.cwkw,
	[CAM_CC_MCWK2_CWK_SWC] = &cam_cc_mcwk2_cwk_swc.cwkw,
	[CAM_CC_MCWK3_CWK] = &cam_cc_mcwk3_cwk.cwkw,
	[CAM_CC_MCWK3_CWK_SWC] = &cam_cc_mcwk3_cwk_swc.cwkw,
	[CAM_CC_MCWK4_CWK] = &cam_cc_mcwk4_cwk.cwkw,
	[CAM_CC_MCWK4_CWK_SWC] = &cam_cc_mcwk4_cwk_swc.cwkw,
	[CAM_CC_MCWK5_CWK] = &cam_cc_mcwk5_cwk.cwkw,
	[CAM_CC_MCWK5_CWK_SWC] = &cam_cc_mcwk5_cwk_swc.cwkw,
	[CAM_CC_MCWK6_CWK] = &cam_cc_mcwk6_cwk.cwkw,
	[CAM_CC_MCWK6_CWK_SWC] = &cam_cc_mcwk6_cwk_swc.cwkw,
	[CAM_CC_PWW0] = &cam_cc_pww0.cwkw,
	[CAM_CC_PWW0_OUT_EVEN] = &cam_cc_pww0_out_even.cwkw,
	[CAM_CC_PWW0_OUT_ODD] = &cam_cc_pww0_out_odd.cwkw,
	[CAM_CC_PWW1] = &cam_cc_pww1.cwkw,
	[CAM_CC_PWW1_OUT_EVEN] = &cam_cc_pww1_out_even.cwkw,
	[CAM_CC_PWW2] = &cam_cc_pww2.cwkw,
	[CAM_CC_PWW2_OUT_MAIN] = &cam_cc_pww2_out_main.cwkw,
	[CAM_CC_PWW3] = &cam_cc_pww3.cwkw,
	[CAM_CC_PWW3_OUT_EVEN] = &cam_cc_pww3_out_even.cwkw,
	[CAM_CC_PWW4] = &cam_cc_pww4.cwkw,
	[CAM_CC_PWW4_OUT_EVEN] = &cam_cc_pww4_out_even.cwkw,
	[CAM_CC_SBI_AHB_CWK] = &cam_cc_sbi_ahb_cwk.cwkw,
	[CAM_CC_SBI_AXI_CWK] = &cam_cc_sbi_axi_cwk.cwkw,
	[CAM_CC_SBI_CWK] = &cam_cc_sbi_cwk.cwkw,
	[CAM_CC_SBI_CPHY_WX_CWK] = &cam_cc_sbi_cphy_wx_cwk.cwkw,
	[CAM_CC_SBI_CSID_CWK] = &cam_cc_sbi_csid_cwk.cwkw,
	[CAM_CC_SBI_CSID_CWK_SWC] = &cam_cc_sbi_csid_cwk_swc.cwkw,
	[CAM_CC_SBI_DIV_CWK_SWC] = &cam_cc_sbi_div_cwk_swc.cwkw,
	[CAM_CC_SBI_IFE_0_CWK] = &cam_cc_sbi_ife_0_cwk.cwkw,
	[CAM_CC_SBI_IFE_1_CWK] = &cam_cc_sbi_ife_1_cwk.cwkw,
	[CAM_CC_SWEEP_CWK] = &cam_cc_sweep_cwk.cwkw,
	[CAM_CC_SWEEP_CWK_SWC] = &cam_cc_sweep_cwk_swc.cwkw,
	[CAM_CC_SWOW_AHB_CWK_SWC] = &cam_cc_swow_ahb_cwk_swc.cwkw,
	[CAM_CC_XO_CWK_SWC] = &cam_cc_xo_cwk_swc.cwkw,
};

static stwuct gdsc *cam_cc_sm8250_gdscs[] = {
	[BPS_GDSC] = &bps_gdsc,
	[IPE_0_GDSC] = &ipe_0_gdsc,
	[SBI_GDSC] = &sbi_gdsc,
	[IFE_0_GDSC] = &ife_0_gdsc,
	[IFE_1_GDSC] = &ife_1_gdsc,
	[TITAN_TOP_GDSC] = &titan_top_gdsc,
};

static const stwuct qcom_weset_map cam_cc_sm8250_wesets[] = {
	[CAM_CC_BPS_BCW] = { 0x7000 },
	[CAM_CC_ICP_BCW] = { 0xc070 },
	[CAM_CC_IFE_0_BCW] = { 0xa000 },
	[CAM_CC_IFE_1_BCW] = { 0xb000 },
	[CAM_CC_IPE_0_BCW] = { 0x8000 },
	[CAM_CC_SBI_BCW] = { 0x9000 },
};

static const stwuct wegmap_config cam_cc_sm8250_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0xe004,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc cam_cc_sm8250_desc = {
	.config = &cam_cc_sm8250_wegmap_config,
	.cwks = cam_cc_sm8250_cwocks,
	.num_cwks = AWWAY_SIZE(cam_cc_sm8250_cwocks),
	.wesets = cam_cc_sm8250_wesets,
	.num_wesets = AWWAY_SIZE(cam_cc_sm8250_wesets),
	.gdscs = cam_cc_sm8250_gdscs,
	.num_gdscs = AWWAY_SIZE(cam_cc_sm8250_gdscs),
};

static const stwuct of_device_id cam_cc_sm8250_match_tabwe[] = {
	{ .compatibwe = "qcom,sm8250-camcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, cam_cc_sm8250_match_tabwe);

static int cam_cc_sm8250_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, &cam_cc_sm8250_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cwk_wucid_pww_configuwe(&cam_cc_pww0, wegmap, &cam_cc_pww0_config);
	cwk_wucid_pww_configuwe(&cam_cc_pww1, wegmap, &cam_cc_pww1_config);
	cwk_zonda_pww_configuwe(&cam_cc_pww2, wegmap, &cam_cc_pww2_config);
	cwk_wucid_pww_configuwe(&cam_cc_pww3, wegmap, &cam_cc_pww3_config);
	cwk_wucid_pww_configuwe(&cam_cc_pww4, wegmap, &cam_cc_pww4_config);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &cam_cc_sm8250_desc, wegmap);
}

static stwuct pwatfowm_dwivew cam_cc_sm8250_dwivew = {
	.pwobe = cam_cc_sm8250_pwobe,
	.dwivew = {
		.name = "cam_cc-sm8250",
		.of_match_tabwe = cam_cc_sm8250_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(cam_cc_sm8250_dwivew);

MODUWE_DESCWIPTION("QTI CAMCC SM8250 Dwivew");
MODUWE_WICENSE("GPW v2");
