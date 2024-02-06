// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,camcc-sdm845.h>

#incwude "common.h"
#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "gdsc.h"

enum {
	P_BI_TCXO,
	P_CAM_CC_PWW0_OUT_EVEN,
	P_CAM_CC_PWW1_OUT_EVEN,
	P_CAM_CC_PWW2_OUT_EVEN,
	P_CAM_CC_PWW3_OUT_EVEN,
};

static stwuct cwk_awpha_pww cam_cc_pww0 = {
	.offset = 0x0,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo", .name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fabia_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_fabia_even[] = {
	{ 0x0, 1 },
	{ 0x1, 2 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww0_out_even = {
	.offset = 0x0,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_fabia_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_fabia_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww0_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&cam_cc_pww0.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_fabia_ops,
	},
};

static stwuct cwk_awpha_pww cam_cc_pww1 = {
	.offset = 0x1000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_pww1",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo", .name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fabia_ops,
		},
	},
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww1_out_even = {
	.offset = 0x1000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_fabia_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_fabia_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww1_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&cam_cc_pww1.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_fabia_ops,
	},
};

static stwuct cwk_awpha_pww cam_cc_pww2 = {
	.offset = 0x2000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_pww2",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo", .name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fabia_ops,
		},
	},
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww2_out_even = {
	.offset = 0x2000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_fabia_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_fabia_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww2_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&cam_cc_pww2.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_fabia_ops,
	},
};

static stwuct cwk_awpha_pww cam_cc_pww3 = {
	.offset = 0x3000,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_pww3",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo", .name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fabia_ops,
		},
	},
};

static stwuct cwk_awpha_pww_postdiv cam_cc_pww3_out_even = {
	.offset = 0x3000,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_fabia_even,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_fabia_even),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_pww3_out_even",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&cam_cc_pww3.cwkw.hw,
		},
		.num_pawents = 1,
		.ops = &cwk_awpha_pww_postdiv_fabia_ops,
	},
};

static const stwuct pawent_map cam_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_CAM_CC_PWW2_OUT_EVEN, 1 },
	{ P_CAM_CC_PWW1_OUT_EVEN, 2 },
	{ P_CAM_CC_PWW3_OUT_EVEN, 5 },
	{ P_CAM_CC_PWW0_OUT_EVEN, 6 },
};

static const stwuct cwk_pawent_data cam_cc_pawent_data_0[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .hw = &cam_cc_pww2_out_even.cwkw.hw },
	{ .hw = &cam_cc_pww1_out_even.cwkw.hw },
	{ .hw = &cam_cc_pww3_out_even.cwkw.hw },
	{ .hw = &cam_cc_pww0_out_even.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_cam_cc_bps_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_CAM_CC_PWW0_OUT_EVEN, 6, 0, 0),
	F(200000000, P_CAM_CC_PWW0_OUT_EVEN, 3, 0, 0),
	F(404000000, P_CAM_CC_PWW1_OUT_EVEN, 2, 0, 0),
	F(480000000, P_CAM_CC_PWW2_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAM_CC_PWW0_OUT_EVEN, 1, 0, 0),
	{ }
};

/*
 * As pew HW design, some of the CAMCC WCGs needs to
 * move to XO cwock duwing theiw cwock disabwe so using
 * cwk_wcg2_shawed_ops fow such WCGs. This is wequiwed
 * to powew down the camewa memowies gwacefuwwy.
 * Awso, use CWK_SET_WATE_PAWENT fwag fow the WCGs which
 * have CAM_CC_PWW2_OUT_EVEN PWW as pawent in fwequency
 * tabwe and wequiwes weconfiguwation of the PWW fwequency.
 */
static stwuct cwk_wcg2 cam_cc_bps_cwk_swc = {
	.cmd_wcgw = 0x600c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_bps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_bps_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_cci_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(37500000, P_CAM_CC_PWW0_OUT_EVEN, 16, 0, 0),
	F(50000000, P_CAM_CC_PWW0_OUT_EVEN, 12, 0, 0),
	F(100000000, P_CAM_CC_PWW0_OUT_EVEN, 6, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_cci_cwk_swc = {
	.cmd_wcgw = 0xb0d8,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_cci_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_cci_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_cphy_wx_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(384000000, P_CAM_CC_PWW3_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_cphy_wx_cwk_swc = {
	.cmd_wcgw = 0x9060,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_cphy_wx_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_cphy_wx_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_csi0phytimew_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(240000000, P_CAM_CC_PWW2_OUT_EVEN, 2, 0, 0),
	F(269333333, P_CAM_CC_PWW1_OUT_EVEN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_csi0phytimew_cwk_swc = {
	.cmd_wcgw = 0x5004,
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
	.cmd_wcgw = 0x5028,
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
	.cmd_wcgw = 0x504c,
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
	.cmd_wcgw = 0x5070,
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

static const stwuct fweq_tbw ftbw_cam_cc_fast_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(50000000, P_CAM_CC_PWW0_OUT_EVEN, 12, 0, 0),
	F(100000000, P_CAM_CC_PWW0_OUT_EVEN, 6, 0, 0),
	F(200000000, P_CAM_CC_PWW0_OUT_EVEN, 3, 0, 0),
	F(300000000, P_CAM_CC_PWW0_OUT_EVEN, 2, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_EVEN, 1.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_fast_ahb_cwk_swc = {
	.cmd_wcgw = 0x6038,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_fast_ahb_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_fast_ahb_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_fd_cowe_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(384000000, P_CAM_CC_PWW3_OUT_EVEN, 1, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_EVEN, 1.5, 0, 0),
	F(538666667, P_CAM_CC_PWW1_OUT_EVEN, 1.5, 0, 0),
	F(600000000, P_CAM_CC_PWW0_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_fd_cowe_cwk_swc = {
	.cmd_wcgw = 0xb0b0,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_fd_cowe_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_fd_cowe_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_icp_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(384000000, P_CAM_CC_PWW3_OUT_EVEN, 1, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_EVEN, 1.5, 0, 0),
	F(538666667, P_CAM_CC_PWW1_OUT_EVEN, 1.5, 0, 0),
	F(600000000, P_CAM_CC_PWW0_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_icp_cwk_swc = {
	.cmd_wcgw = 0xb088,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_icp_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_icp_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ife_0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_CAM_CC_PWW0_OUT_EVEN, 6, 0, 0),
	F(320000000, P_CAM_CC_PWW2_OUT_EVEN, 1.5, 0, 0),
	F(404000000, P_CAM_CC_PWW1_OUT_EVEN, 2, 0, 0),
	F(480000000, P_CAM_CC_PWW2_OUT_EVEN, 1, 0, 0),
	F(600000000, P_CAM_CC_PWW0_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ife_0_cwk_swc = {
	.cmd_wcgw = 0x900c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_ife_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_0_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ife_0_csid_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(75000000, P_CAM_CC_PWW0_OUT_EVEN, 8, 0, 0),
	F(384000000, P_CAM_CC_PWW3_OUT_EVEN, 1, 0, 0),
	F(538666667, P_CAM_CC_PWW1_OUT_EVEN, 1.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ife_0_csid_cwk_swc = {
	.cmd_wcgw = 0x9038,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_ife_0_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_0_csid_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_ife_1_cwk_swc = {
	.cmd_wcgw = 0xa00c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_ife_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_1_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_ife_1_csid_cwk_swc = {
	.cmd_wcgw = 0xa030,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_ife_0_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_1_csid_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_ife_wite_cwk_swc = {
	.cmd_wcgw = 0xb004,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_ife_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_wite_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_ife_wite_csid_cwk_swc = {
	.cmd_wcgw = 0xb024,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_ife_0_csid_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ife_wite_csid_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_ipe_0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_CAM_CC_PWW0_OUT_EVEN, 6, 0, 0),
	F(240000000, P_CAM_CC_PWW0_OUT_EVEN, 2.5, 0, 0),
	F(404000000, P_CAM_CC_PWW1_OUT_EVEN, 2, 0, 0),
	F(480000000, P_CAM_CC_PWW2_OUT_EVEN, 1, 0, 0),
	F(538666667, P_CAM_CC_PWW1_OUT_EVEN, 1.5, 0, 0),
	F(600000000, P_CAM_CC_PWW0_OUT_EVEN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_ipe_0_cwk_swc = {
	.cmd_wcgw = 0x700c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_ipe_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ipe_0_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_ipe_1_cwk_swc = {
	.cmd_wcgw = 0x800c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_ipe_0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_ipe_1_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_jpeg_cwk_swc = {
	.cmd_wcgw = 0xb04c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_bps_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_jpeg_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_wwme_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(100000000, P_CAM_CC_PWW0_OUT_EVEN, 6, 0, 0),
	F(200000000, P_CAM_CC_PWW0_OUT_EVEN, 3, 0, 0),
	F(269333333, P_CAM_CC_PWW1_OUT_EVEN, 3, 0, 0),
	F(320000000, P_CAM_CC_PWW2_OUT_EVEN, 1.5, 0, 0),
	F(400000000, P_CAM_CC_PWW0_OUT_EVEN, 1.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_wwme_cwk_swc = {
	.cmd_wcgw = 0xb0f8,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_wwme_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_wwme_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_mcwk0_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(24000000, P_CAM_CC_PWW2_OUT_EVEN, 10, 1, 2),
	F(33333333, P_CAM_CC_PWW0_OUT_EVEN, 2, 1, 9),
	F(34285714, P_CAM_CC_PWW2_OUT_EVEN, 14, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_mcwk0_cwk_swc = {
	.cmd_wcgw = 0x4004,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_mcwk0_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk1_cwk_swc = {
	.cmd_wcgw = 0x4024,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_mcwk1_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk2_cwk_swc = {
	.cmd_wcgw = 0x4044,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_mcwk2_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 cam_cc_mcwk3_cwk_swc = {
	.cmd_wcgw = 0x4064,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = cam_cc_pawent_map_0,
	.fweq_tbw = ftbw_cam_cc_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cam_cc_mcwk3_cwk_swc",
		.pawent_data = cam_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(cam_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_cam_cc_swow_ahb_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(60000000, P_CAM_CC_PWW0_OUT_EVEN, 10, 0, 0),
	F(66666667, P_CAM_CC_PWW0_OUT_EVEN, 9, 0, 0),
	F(73846154, P_CAM_CC_PWW2_OUT_EVEN, 6.5, 0, 0),
	F(80000000, P_CAM_CC_PWW2_OUT_EVEN, 6, 0, 0),
	{ }
};

static stwuct cwk_wcg2 cam_cc_swow_ahb_cwk_swc = {
	.cmd_wcgw = 0x6054,
	.mnd_width = 0,
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

static stwuct cwk_bwanch cam_cc_bps_ahb_cwk = {
	.hawt_weg = 0x606c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x606c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_bps_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_bps_aweg_cwk = {
	.hawt_weg = 0x6050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_bps_aweg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_bps_axi_cwk = {
	.hawt_weg = 0x6034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_bps_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_bps_cwk = {
	.hawt_weg = 0x6024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x6024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_bps_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_bps_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_camnoc_atb_cwk = {
	.hawt_weg = 0xb12c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb12c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_camnoc_atb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_camnoc_axi_cwk = {
	.hawt_weg = 0xb124,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb124,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_camnoc_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cci_cwk = {
	.hawt_weg = 0xb0f0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb0f0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_cci_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cci_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_cpas_ahb_cwk = {
	.hawt_weg = 0xb11c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb11c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_cpas_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csi0phytimew_cwk = {
	.hawt_weg = 0x501c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x501c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csi0phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_csi0phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csi1phytimew_cwk = {
	.hawt_weg = 0x5040,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5040,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csi1phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_csi1phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csi2phytimew_cwk = {
	.hawt_weg = 0x5064,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5064,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csi2phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_csi2phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csi3phytimew_cwk = {
	.hawt_weg = 0x5088,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5088,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csi3phytimew_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_csi3phytimew_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csiphy0_cwk = {
	.hawt_weg = 0x5020,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5020,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csiphy0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csiphy1_cwk = {
	.hawt_weg = 0x5044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5044,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csiphy1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csiphy2_cwk = {
	.hawt_weg = 0x5068,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x5068,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csiphy2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_csiphy3_cwk = {
	.hawt_weg = 0x508c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x508c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_csiphy3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_fd_cowe_cwk = {
	.hawt_weg = 0xb0c8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb0c8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_fd_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_fd_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_fd_cowe_uaw_cwk = {
	.hawt_weg = 0xb0d0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb0d0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_fd_cowe_uaw_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_fd_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_icp_apb_cwk = {
	.hawt_weg = 0xb084,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb084,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_icp_apb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_icp_atb_cwk = {
	.hawt_weg = 0xb078,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb078,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_icp_atb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_icp_cwk = {
	.hawt_weg = 0xb0a0,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb0a0,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_icp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_icp_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_icp_cti_cwk = {
	.hawt_weg = 0xb07c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb07c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_icp_cti_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_icp_ts_cwk = {
	.hawt_weg = 0xb080,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb080,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_icp_ts_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_axi_cwk = {
	.hawt_weg = 0x907c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x907c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_0_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_cwk = {
	.hawt_weg = 0x9024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_cphy_wx_cwk = {
	.hawt_weg = 0x9078,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9078,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_0_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_csid_cwk = {
	.hawt_weg = 0x9050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_0_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_0_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_0_dsp_cwk = {
	.hawt_weg = 0x9034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x9034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_0_dsp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_axi_cwk = {
	.hawt_weg = 0xa054,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_1_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_cwk = {
	.hawt_weg = 0xa024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_cphy_wx_cwk = {
	.hawt_weg = 0xa050,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa050,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_1_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_csid_cwk = {
	.hawt_weg = 0xa048,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa048,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_1_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_1_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_1_dsp_cwk = {
	.hawt_weg = 0xa02c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xa02c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_1_dsp_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_wite_cwk = {
	.hawt_weg = 0xb01c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb01c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_wite_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_wite_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_wite_cphy_wx_cwk = {
	.hawt_weg = 0xb044,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb044,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_wite_cphy_wx_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_cphy_wx_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ife_wite_csid_cwk = {
	.hawt_weg = 0xb03c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb03c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ife_wite_csid_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ife_wite_csid_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_0_ahb_cwk = {
	.hawt_weg = 0x703c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x703c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ipe_0_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_0_aweg_cwk = {
	.hawt_weg = 0x7038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ipe_0_aweg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_0_axi_cwk = {
	.hawt_weg = 0x7034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ipe_0_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_0_cwk = {
	.hawt_weg = 0x7024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ipe_0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ipe_0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_1_ahb_cwk = {
	.hawt_weg = 0x803c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x803c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ipe_1_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_swow_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_1_aweg_cwk = {
	.hawt_weg = 0x8038,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8038,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ipe_1_aweg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_fast_ahb_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_1_axi_cwk = {
	.hawt_weg = 0x8034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ipe_1_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_ipe_1_cwk = {
	.hawt_weg = 0x8024,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8024,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_ipe_1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_ipe_1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_jpeg_cwk = {
	.hawt_weg = 0xb064,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb064,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_jpeg_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_jpeg_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_wwme_cwk = {
	.hawt_weg = 0xb110,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb110,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_wwme_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_wwme_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk0_cwk = {
	.hawt_weg = 0x401c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x401c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_mcwk0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_mcwk0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk1_cwk = {
	.hawt_weg = 0x403c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x403c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_mcwk1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_mcwk1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk2_cwk = {
	.hawt_weg = 0x405c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x405c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_mcwk2_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_mcwk2_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_mcwk3_cwk = {
	.hawt_weg = 0x407c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x407c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_mcwk3_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&cam_cc_mcwk3_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_soc_ahb_cwk = {
	.hawt_weg = 0xb13c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb13c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_soc_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch cam_cc_sys_tmw_cwk = {
	.hawt_weg = 0xb0a8,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0xb0a8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "cam_cc_sys_tmw_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc titan_top_gdsc;

static stwuct gdsc bps_gdsc = {
	.gdscw = 0x6004,
	.pd = {
		.name = "bps_gdsc",
	},
	.fwags = HW_CTWW | POWW_CFG_GDSCW,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ipe_0_gdsc = {
	.gdscw = 0x7004,
	.pd = {
		.name = "ipe_0_gdsc",
	},
	.fwags = HW_CTWW | POWW_CFG_GDSCW,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ipe_1_gdsc = {
	.gdscw = 0x8004,
	.pd = {
		.name = "ipe_1_gdsc",
	},
	.fwags = HW_CTWW | POWW_CFG_GDSCW,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ife_0_gdsc = {
	.gdscw = 0x9004,
	.pd = {
		.name = "ife_0_gdsc",
	},
	.fwags = POWW_CFG_GDSCW,
	.pawent = &titan_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc ife_1_gdsc = {
	.gdscw = 0xa004,
	.pd = {
		.name = "ife_1_gdsc",
	},
	.fwags = POWW_CFG_GDSCW,
	.pawent = &titan_top_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc titan_top_gdsc = {
	.gdscw = 0xb134,
	.pd = {
		.name = "titan_top_gdsc",
	},
	.fwags = POWW_CFG_GDSCW,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct cwk_wegmap *cam_cc_sdm845_cwocks[] = {
	[CAM_CC_BPS_AHB_CWK] = &cam_cc_bps_ahb_cwk.cwkw,
	[CAM_CC_BPS_AWEG_CWK] = &cam_cc_bps_aweg_cwk.cwkw,
	[CAM_CC_BPS_AXI_CWK] = &cam_cc_bps_axi_cwk.cwkw,
	[CAM_CC_BPS_CWK] = &cam_cc_bps_cwk.cwkw,
	[CAM_CC_BPS_CWK_SWC] = &cam_cc_bps_cwk_swc.cwkw,
	[CAM_CC_CAMNOC_ATB_CWK] = &cam_cc_camnoc_atb_cwk.cwkw,
	[CAM_CC_CAMNOC_AXI_CWK] = &cam_cc_camnoc_axi_cwk.cwkw,
	[CAM_CC_CCI_CWK] = &cam_cc_cci_cwk.cwkw,
	[CAM_CC_CCI_CWK_SWC] = &cam_cc_cci_cwk_swc.cwkw,
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
	[CAM_CC_CSIPHY0_CWK] = &cam_cc_csiphy0_cwk.cwkw,
	[CAM_CC_CSIPHY1_CWK] = &cam_cc_csiphy1_cwk.cwkw,
	[CAM_CC_CSIPHY2_CWK] = &cam_cc_csiphy2_cwk.cwkw,
	[CAM_CC_CSIPHY3_CWK] = &cam_cc_csiphy3_cwk.cwkw,
	[CAM_CC_FAST_AHB_CWK_SWC] = &cam_cc_fast_ahb_cwk_swc.cwkw,
	[CAM_CC_FD_COWE_CWK] = &cam_cc_fd_cowe_cwk.cwkw,
	[CAM_CC_FD_COWE_CWK_SWC] = &cam_cc_fd_cowe_cwk_swc.cwkw,
	[CAM_CC_FD_COWE_UAW_CWK] = &cam_cc_fd_cowe_uaw_cwk.cwkw,
	[CAM_CC_ICP_APB_CWK] = &cam_cc_icp_apb_cwk.cwkw,
	[CAM_CC_ICP_ATB_CWK] = &cam_cc_icp_atb_cwk.cwkw,
	[CAM_CC_ICP_CWK] = &cam_cc_icp_cwk.cwkw,
	[CAM_CC_ICP_CWK_SWC] = &cam_cc_icp_cwk_swc.cwkw,
	[CAM_CC_ICP_CTI_CWK] = &cam_cc_icp_cti_cwk.cwkw,
	[CAM_CC_ICP_TS_CWK] = &cam_cc_icp_ts_cwk.cwkw,
	[CAM_CC_IFE_0_AXI_CWK] = &cam_cc_ife_0_axi_cwk.cwkw,
	[CAM_CC_IFE_0_CWK] = &cam_cc_ife_0_cwk.cwkw,
	[CAM_CC_IFE_0_CWK_SWC] = &cam_cc_ife_0_cwk_swc.cwkw,
	[CAM_CC_IFE_0_CPHY_WX_CWK] = &cam_cc_ife_0_cphy_wx_cwk.cwkw,
	[CAM_CC_IFE_0_CSID_CWK] = &cam_cc_ife_0_csid_cwk.cwkw,
	[CAM_CC_IFE_0_CSID_CWK_SWC] = &cam_cc_ife_0_csid_cwk_swc.cwkw,
	[CAM_CC_IFE_0_DSP_CWK] = &cam_cc_ife_0_dsp_cwk.cwkw,
	[CAM_CC_IFE_1_AXI_CWK] = &cam_cc_ife_1_axi_cwk.cwkw,
	[CAM_CC_IFE_1_CWK] = &cam_cc_ife_1_cwk.cwkw,
	[CAM_CC_IFE_1_CWK_SWC] = &cam_cc_ife_1_cwk_swc.cwkw,
	[CAM_CC_IFE_1_CPHY_WX_CWK] = &cam_cc_ife_1_cphy_wx_cwk.cwkw,
	[CAM_CC_IFE_1_CSID_CWK] = &cam_cc_ife_1_csid_cwk.cwkw,
	[CAM_CC_IFE_1_CSID_CWK_SWC] = &cam_cc_ife_1_csid_cwk_swc.cwkw,
	[CAM_CC_IFE_1_DSP_CWK] = &cam_cc_ife_1_dsp_cwk.cwkw,
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
	[CAM_CC_IPE_1_AHB_CWK] = &cam_cc_ipe_1_ahb_cwk.cwkw,
	[CAM_CC_IPE_1_AWEG_CWK] = &cam_cc_ipe_1_aweg_cwk.cwkw,
	[CAM_CC_IPE_1_AXI_CWK] = &cam_cc_ipe_1_axi_cwk.cwkw,
	[CAM_CC_IPE_1_CWK] = &cam_cc_ipe_1_cwk.cwkw,
	[CAM_CC_IPE_1_CWK_SWC] = &cam_cc_ipe_1_cwk_swc.cwkw,
	[CAM_CC_JPEG_CWK] = &cam_cc_jpeg_cwk.cwkw,
	[CAM_CC_JPEG_CWK_SWC] = &cam_cc_jpeg_cwk_swc.cwkw,
	[CAM_CC_WWME_CWK] = &cam_cc_wwme_cwk.cwkw,
	[CAM_CC_WWME_CWK_SWC] = &cam_cc_wwme_cwk_swc.cwkw,
	[CAM_CC_MCWK0_CWK] = &cam_cc_mcwk0_cwk.cwkw,
	[CAM_CC_MCWK0_CWK_SWC] = &cam_cc_mcwk0_cwk_swc.cwkw,
	[CAM_CC_MCWK1_CWK] = &cam_cc_mcwk1_cwk.cwkw,
	[CAM_CC_MCWK1_CWK_SWC] = &cam_cc_mcwk1_cwk_swc.cwkw,
	[CAM_CC_MCWK2_CWK] = &cam_cc_mcwk2_cwk.cwkw,
	[CAM_CC_MCWK2_CWK_SWC] = &cam_cc_mcwk2_cwk_swc.cwkw,
	[CAM_CC_MCWK3_CWK] = &cam_cc_mcwk3_cwk.cwkw,
	[CAM_CC_MCWK3_CWK_SWC] = &cam_cc_mcwk3_cwk_swc.cwkw,
	[CAM_CC_PWW0] = &cam_cc_pww0.cwkw,
	[CAM_CC_PWW0_OUT_EVEN] = &cam_cc_pww0_out_even.cwkw,
	[CAM_CC_PWW1] = &cam_cc_pww1.cwkw,
	[CAM_CC_PWW1_OUT_EVEN] = &cam_cc_pww1_out_even.cwkw,
	[CAM_CC_PWW2] = &cam_cc_pww2.cwkw,
	[CAM_CC_PWW2_OUT_EVEN] = &cam_cc_pww2_out_even.cwkw,
	[CAM_CC_PWW3] = &cam_cc_pww3.cwkw,
	[CAM_CC_PWW3_OUT_EVEN] = &cam_cc_pww3_out_even.cwkw,
	[CAM_CC_SWOW_AHB_CWK_SWC] = &cam_cc_swow_ahb_cwk_swc.cwkw,
	[CAM_CC_SOC_AHB_CWK] = &cam_cc_soc_ahb_cwk.cwkw,
	[CAM_CC_SYS_TMW_CWK] = &cam_cc_sys_tmw_cwk.cwkw,
};

static stwuct gdsc *cam_cc_sdm845_gdscs[] = {
	[BPS_GDSC] = &bps_gdsc,
	[IPE_0_GDSC] = &ipe_0_gdsc,
	[IPE_1_GDSC] = &ipe_1_gdsc,
	[IFE_0_GDSC] = &ife_0_gdsc,
	[IFE_1_GDSC] = &ife_1_gdsc,
	[TITAN_TOP_GDSC] = &titan_top_gdsc,
};

static const stwuct wegmap_config cam_cc_sdm845_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0xd004,
	.fast_io	= twue,
};

static const stwuct qcom_cc_desc cam_cc_sdm845_desc = {
	.config = &cam_cc_sdm845_wegmap_config,
	.cwks = cam_cc_sdm845_cwocks,
	.num_cwks = AWWAY_SIZE(cam_cc_sdm845_cwocks),
	.gdscs = cam_cc_sdm845_gdscs,
	.num_gdscs = AWWAY_SIZE(cam_cc_sdm845_gdscs),
};

static const stwuct of_device_id cam_cc_sdm845_match_tabwe[] = {
	{ .compatibwe = "qcom,sdm845-camcc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, cam_cc_sdm845_match_tabwe);

static int cam_cc_sdm845_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	stwuct awpha_pww_config cam_cc_pww_config = { };

	wegmap = qcom_cc_map(pdev, &cam_cc_sdm845_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cam_cc_pww_config.w = 0x1f;
	cam_cc_pww_config.awpha = 0x4000;
	cwk_fabia_pww_configuwe(&cam_cc_pww0, wegmap, &cam_cc_pww_config);

	cam_cc_pww_config.w = 0x2a;
	cam_cc_pww_config.awpha = 0x1556;
	cwk_fabia_pww_configuwe(&cam_cc_pww1, wegmap, &cam_cc_pww_config);

	cam_cc_pww_config.w = 0x32;
	cam_cc_pww_config.awpha = 0x0;
	cwk_fabia_pww_configuwe(&cam_cc_pww2, wegmap, &cam_cc_pww_config);

	cam_cc_pww_config.w = 0x14;
	cwk_fabia_pww_configuwe(&cam_cc_pww3, wegmap, &cam_cc_pww_config);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &cam_cc_sdm845_desc, wegmap);
}

static stwuct pwatfowm_dwivew cam_cc_sdm845_dwivew = {
	.pwobe	= cam_cc_sdm845_pwobe,
	.dwivew	= {
		.name = "sdm845-camcc",
		.of_match_tabwe = cam_cc_sdm845_match_tabwe,
	},
};

static int __init cam_cc_sdm845_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&cam_cc_sdm845_dwivew);
}
subsys_initcaww(cam_cc_sdm845_init);

static void __exit cam_cc_sdm845_exit(void)
{
	pwatfowm_dwivew_unwegistew(&cam_cc_sdm845_dwivew);
}
moduwe_exit(cam_cc_sdm845_exit);

MODUWE_DESCWIPTION("QTI CAM_CC SDM845 Dwivew");
MODUWE_WICENSE("GPW v2");
