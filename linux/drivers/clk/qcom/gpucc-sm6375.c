// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023, Winawo Wimited
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,sm6375-gpucc.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "cwk-wegmap-mux.h"
#incwude "cwk-wegmap-phy-mux.h"
#incwude "gdsc.h"
#incwude "weset.h"

enum {
	DT_BI_TCXO,
	DT_GCC_GPU_GPWW0_CWK_SWC,
	DT_GCC_GPU_GPWW0_DIV_CWK_SWC,
	DT_GCC_GPU_SNOC_DVM_GFX_CWK,
};

enum {
	P_BI_TCXO,
	P_GCC_GPU_GPWW0_CWK_SWC,
	P_GCC_GPU_GPWW0_DIV_CWK_SWC,
	P_GPU_CC_PWW0_OUT_EVEN,
	P_GPU_CC_PWW0_OUT_MAIN,
	P_GPU_CC_PWW0_OUT_ODD,
	P_GPU_CC_PWW1_OUT_EVEN,
	P_GPU_CC_PWW1_OUT_MAIN,
	P_GPU_CC_PWW1_OUT_ODD,
};

static stwuct pww_vco wucid_vco[] = {
	{ 249600000, 2000000000, 0 },
};

/* 532MHz Configuwation */
static const stwuct awpha_pww_config gpucc_pww0_config = {
	.w = 0x1b,
	.awpha = 0xb555,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329a299c,
	.usew_ctw_vaw = 0x00000001,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww gpucc_pww0 = {
	.offset = 0x0,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpucc_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = P_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

/* 514MHz Configuwation */
static const stwuct awpha_pww_config gpucc_pww1_config = {
	.w = 0x1a,
	.awpha = 0xc555,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329a299c,
	.usew_ctw_vaw = 0x00000001,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww gpucc_pww1 = {
	.offset = 0x100,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpucc_pww1",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = P_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct pawent_map gpucc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPU_CC_PWW0_OUT_MAIN, 1 },
	{ P_GPU_CC_PWW1_OUT_MAIN, 3 },
	{ P_GCC_GPU_GPWW0_CWK_SWC, 5 },
	{ P_GCC_GPU_GPWW0_DIV_CWK_SWC, 6 },
};

static const stwuct cwk_pawent_data gpucc_pawent_data_0[] = {
	{ .index = P_BI_TCXO },
	{ .hw = &gpucc_pww0.cwkw.hw },
	{ .hw = &gpucc_pww1.cwkw.hw },
	{ .index = DT_GCC_GPU_GPWW0_CWK_SWC },
	{ .index = DT_GCC_GPU_GPWW0_DIV_CWK_SWC },
};

static const stwuct pawent_map gpucc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPU_CC_PWW0_OUT_EVEN, 1 },
	{ P_GPU_CC_PWW0_OUT_ODD, 2 },
	{ P_GPU_CC_PWW1_OUT_EVEN, 3 },
	{ P_GPU_CC_PWW1_OUT_ODD, 4 },
	{ P_GCC_GPU_GPWW0_CWK_SWC, 5 },
};

static const stwuct cwk_pawent_data gpucc_pawent_data_1[] = {
	{ .index = P_BI_TCXO },
	{ .hw = &gpucc_pww0.cwkw.hw },
	{ .hw = &gpucc_pww0.cwkw.hw },
	{ .hw = &gpucc_pww1.cwkw.hw },
	{ .hw = &gpucc_pww1.cwkw.hw },
	{ .index = DT_GCC_GPU_GPWW0_CWK_SWC },
};

static const stwuct fweq_tbw ftbw_gpucc_gmu_cwk_swc[] = {
	F(200000000, P_GCC_GPU_GPWW0_DIV_CWK_SWC, 1.5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gpucc_gmu_cwk_swc = {
	.cmd_wcgw = 0x1120,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gpucc_pawent_map_0,
	.fweq_tbw = ftbw_gpucc_gmu_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpucc_gmu_cwk_swc",
		.pawent_data = gpucc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gpucc_pawent_data_0),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gpucc_gx_gfx3d_cwk_swc[] = {
	F(266000000, P_GPU_CC_PWW0_OUT_EVEN, 2, 0, 0),
	F(390000000, P_GPU_CC_PWW0_OUT_EVEN, 2, 0, 0),
	F(490000000, P_GPU_CC_PWW0_OUT_EVEN, 2, 0, 0),
	F(650000000, P_GPU_CC_PWW0_OUT_EVEN, 2, 0, 0),
	F(770000000, P_GPU_CC_PWW0_OUT_EVEN, 2, 0, 0),
	F(840000000, P_GPU_CC_PWW0_OUT_EVEN, 2, 0, 0),
	F(900000000, P_GPU_CC_PWW0_OUT_EVEN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gpucc_gx_gfx3d_cwk_swc = {
	.cmd_wcgw = 0x101c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gpucc_pawent_map_1,
	.fweq_tbw = ftbw_gpucc_gx_gfx3d_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpucc_gx_gfx3d_cwk_swc",
		.pawent_data = gpucc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gpucc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT | CWK_OPS_PAWENT_ENABWE,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gpucc_ahb_cwk = {
	.hawt_weg = 0x1078,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x1078,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpucc_ahb_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpucc_cx_gfx3d_cwk = {
	.hawt_weg = 0x10a4,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x10a4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpucc_cx_gfx3d_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gpucc_gx_gfx3d_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpucc_cx_gfx3d_swv_cwk = {
	.hawt_weg = 0x10a8,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x10a8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpucc_cx_gfx3d_swv_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gpucc_gx_gfx3d_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpucc_cx_gmu_cwk = {
	.hawt_weg = 0x1098,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1098,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpucc_cx_gmu_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gpucc_gmu_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpucc_cx_snoc_dvm_cwk = {
	.hawt_weg = 0x108c,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x108c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpucc_cx_snoc_dvm_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_GCC_GPU_SNOC_DVM_GFX_CWK,
			},
			.num_pawents = 1,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpucc_cxo_aon_cwk = {
	.hawt_weg = 0x1004,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x1004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpucc_cxo_aon_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpucc_cxo_cwk = {
	.hawt_weg = 0x109c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x109c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpucc_cxo_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpucc_gx_cxo_cwk = {
	.hawt_weg = 0x1060,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x1060,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpucc_gx_cxo_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpucc_gx_gfx3d_cwk = {
	.hawt_weg = 0x1054,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x1054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpucc_gx_gfx3d_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gpucc_gx_gfx3d_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpucc_gx_gmu_cwk = {
	.hawt_weg = 0x1064,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1064,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpucc_gx_gmu_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gpucc_gmu_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpucc_sweep_cwk = {
	.hawt_weg = 0x1090,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x1090,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpucc_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc gpu_cx_gdsc = {
	.gdscw = 0x106c,
	.gds_hw_ctww = 0x1540,
	.cwk_dis_wait_vaw = 8,
	.pd = {
		.name = "gpu_cx_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc gpu_gx_gdsc = {
	.gdscw = 0x100c,
	.cwamp_io_ctww = 0x1508,
	.wesets = (unsigned int []){ GPU_GX_BCW, GPU_ACD_BCW, GPU_GX_ACD_MISC_BCW },
	.weset_count = 3,
	.pd = {
		.name = "gpu_gx_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = CWAMP_IO | SW_WESET | AON_WESET,
};

static stwuct cwk_wegmap *gpucc_sm6375_cwocks[] = {
	[GPU_CC_AHB_CWK] = &gpucc_ahb_cwk.cwkw,
	[GPU_CC_CX_GFX3D_CWK] = &gpucc_cx_gfx3d_cwk.cwkw,
	[GPU_CC_CX_GFX3D_SWV_CWK] = &gpucc_cx_gfx3d_swv_cwk.cwkw,
	[GPU_CC_CX_GMU_CWK] = &gpucc_cx_gmu_cwk.cwkw,
	[GPU_CC_CX_SNOC_DVM_CWK] = &gpucc_cx_snoc_dvm_cwk.cwkw,
	[GPU_CC_CXO_AON_CWK] = &gpucc_cxo_aon_cwk.cwkw,
	[GPU_CC_CXO_CWK] = &gpucc_cxo_cwk.cwkw,
	[GPU_CC_GMU_CWK_SWC] = &gpucc_gmu_cwk_swc.cwkw,
	[GPU_CC_GX_CXO_CWK] = &gpucc_gx_cxo_cwk.cwkw,
	[GPU_CC_GX_GFX3D_CWK] = &gpucc_gx_gfx3d_cwk.cwkw,
	[GPU_CC_GX_GFX3D_CWK_SWC] = &gpucc_gx_gfx3d_cwk_swc.cwkw,
	[GPU_CC_GX_GMU_CWK] = &gpucc_gx_gmu_cwk.cwkw,
	[GPU_CC_PWW0] = &gpucc_pww0.cwkw,
	[GPU_CC_PWW1] = &gpucc_pww1.cwkw,
	[GPU_CC_SWEEP_CWK] = &gpucc_sweep_cwk.cwkw,
};

static const stwuct qcom_weset_map gpucc_sm6375_wesets[] = {
	[GPU_GX_BCW] = { 0x1008 },
	[GPU_ACD_BCW] = { 0x1160 },
	[GPU_GX_ACD_MISC_BCW] = { 0x8004 },
};

static stwuct gdsc *gpucc_sm6375_gdscs[] = {
	[GPU_CX_GDSC] = &gpu_cx_gdsc,
	[GPU_GX_GDSC] = &gpu_gx_gdsc,
};

static const stwuct wegmap_config gpucc_sm6375_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x9000,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc gpucc_sm6375_desc = {
	.config = &gpucc_sm6375_wegmap_config,
	.cwks = gpucc_sm6375_cwocks,
	.num_cwks = AWWAY_SIZE(gpucc_sm6375_cwocks),
	.wesets = gpucc_sm6375_wesets,
	.num_wesets = AWWAY_SIZE(gpucc_sm6375_wesets),
	.gdscs = gpucc_sm6375_gdscs,
	.num_gdscs = AWWAY_SIZE(gpucc_sm6375_gdscs),
};

static const stwuct of_device_id gpucc_sm6375_match_tabwe[] = {
	{ .compatibwe = "qcom,sm6375-gpucc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gpucc_sm6375_match_tabwe);

static int gpucc_sm6375_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	int wet;

	wet = devm_pm_wuntime_enabwe(&pdev->dev);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet)
		wetuwn wet;

	wegmap = qcom_cc_map(pdev, &gpucc_sm6375_desc);
	if (IS_EWW(wegmap)) {
		pm_wuntime_put(&pdev->dev);
		wetuwn PTW_EWW(wegmap);
	}

	cwk_wucid_pww_configuwe(&gpucc_pww0, wegmap, &gpucc_pww0_config);
	cwk_wucid_pww_configuwe(&gpucc_pww1, wegmap, &gpucc_pww1_config);

	wet = qcom_cc_weawwy_pwobe(pdev, &gpucc_sm6375_desc, wegmap);
	pm_wuntime_put(&pdev->dev);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew gpucc_sm6375_dwivew = {
	.pwobe = gpucc_sm6375_pwobe,
	.dwivew = {
		.name = "gpucc-sm6375",
		.of_match_tabwe = gpucc_sm6375_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(gpucc_sm6375_dwivew);

MODUWE_DESCWIPTION("QTI GPUCC SM6375 Dwivew");
MODUWE_WICENSE("GPW");
