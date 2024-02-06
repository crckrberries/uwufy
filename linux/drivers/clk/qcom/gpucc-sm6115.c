// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2019-2020, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023, Winawo Wimited
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,sm6115-gpucc.h>

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
};

enum {
	P_BI_TCXO,
	P_GPWW0_OUT_MAIN,
	P_GPWW0_OUT_MAIN_DIV,
	P_GPU_CC_PWW0_OUT_AUX2,
	P_GPU_CC_PWW0_OUT_MAIN,
	P_GPU_CC_PWW1_OUT_AUX,
	P_GPU_CC_PWW1_OUT_MAIN,
};

static stwuct pww_vco defauwt_vco[] = {
	{ 1000000000, 2000000000, 0 },
};

static stwuct pww_vco pww1_vco[] = {
	{ 500000000, 1000000000, 2 },
};

static const stwuct awpha_pww_config gpu_cc_pww0_config = {
	.w = 0x3e,
	.awpha = 0,
	.awpha_hi = 0x80,
	.vco_vaw = 0x0 << 20,
	.vco_mask = GENMASK(21, 20),
	.awpha_en_mask = BIT(24),
	.main_output_mask = BIT(0),
	.aux_output_mask = BIT(1),
	.aux2_output_mask = BIT(2),
	.config_ctw_vaw = 0x4001055b,
	.test_ctw_hi1_vaw = 0x1,
};

/* 1200MHz configuwation */
static stwuct cwk_awpha_pww gpu_cc_pww0 = {
	.offset = 0x0,
	.vco_tabwe = defauwt_vco,
	.num_vco = AWWAY_SIZE(defauwt_vco),
	.fwags = SUPPOWTS_DYNAMIC_UPDATE,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_gpu_cc_pww0_out_aux2[] = {
	{ 0x0, 1 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv gpu_cc_pww0_out_aux2 = {
	.offset = 0x0,
	.post_div_shift = 8,
	.post_div_tabwe = post_div_tabwe_gpu_cc_pww0_out_aux2,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_gpu_cc_pww0_out_aux2),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpu_cc_pww0_out_aux2",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gpu_cc_pww0.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_ops,
	},
};

/* 640MHz configuwation */
static const stwuct awpha_pww_config gpu_cc_pww1_config = {
	.w = 0x21,
	.awpha = 0x55555555,
	.awpha_hi = 0x55,
	.awpha_en_mask = BIT(24),
	.vco_vaw = 0x2 << 20,
	.vco_mask = GENMASK(21, 20),
	.main_output_mask = BIT(0),
	.aux_output_mask = BIT(1),
	.config_ctw_vaw = 0x4001055b,
	.test_ctw_hi1_vaw = 0x1,
};

static stwuct cwk_awpha_pww gpu_cc_pww1 = {
	.offset = 0x100,
	.vco_tabwe = pww1_vco,
	.num_vco = AWWAY_SIZE(pww1_vco),
	.fwags = SUPPOWTS_DYNAMIC_UPDATE,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_pww1",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_gpu_cc_pww1_out_aux[] = {
	{ 0x0, 1 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv gpu_cc_pww1_out_aux = {
	.offset = 0x100,
	.post_div_shift = 15,
	.post_div_tabwe = post_div_tabwe_gpu_cc_pww1_out_aux,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_gpu_cc_pww1_out_aux),
	.width = 3,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpu_cc_pww1_out_aux",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&gpu_cc_pww1.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_ops,
	},
};

static const stwuct pawent_map gpu_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPU_CC_PWW0_OUT_MAIN, 1 },
	{ P_GPU_CC_PWW1_OUT_MAIN, 3 },
	{ P_GPWW0_OUT_MAIN, 5 },
	{ P_GPWW0_OUT_MAIN_DIV, 6 },
};

static const stwuct cwk_pawent_data gpu_cc_pawent_data_0[] = {
	{ .index = P_BI_TCXO },
	{ .hw = &gpu_cc_pww0.cwkw.hw },
	{ .hw = &gpu_cc_pww1.cwkw.hw },
	{ .index = DT_GCC_GPU_GPWW0_CWK_SWC },
	{ .index = DT_GCC_GPU_GPWW0_DIV_CWK_SWC },
};

static const stwuct pawent_map gpu_cc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPU_CC_PWW0_OUT_AUX2, 2 },
	{ P_GPU_CC_PWW1_OUT_AUX, 3 },
	{ P_GPWW0_OUT_MAIN, 5 },
};

static const stwuct cwk_pawent_data gpu_cc_pawent_data_1[] = {
	{ .index = P_BI_TCXO },
	{ .hw = &gpu_cc_pww0_out_aux2.cwkw.hw },
	{ .hw = &gpu_cc_pww1_out_aux.cwkw.hw },
	{ .index = DT_GCC_GPU_GPWW0_CWK_SWC },
};

static const stwuct fweq_tbw ftbw_gpu_cc_gmu_cwk_swc[] = {
	F(200000000, P_GPWW0_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gpu_cc_gmu_cwk_swc = {
	.cmd_wcgw = 0x1120,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gpu_cc_pawent_map_0,
	.fweq_tbw = ftbw_gpu_cc_gmu_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpu_cc_gmu_cwk_swc",
		.pawent_data = gpu_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(gpu_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gpu_cc_gx_gfx3d_cwk_swc[] = {
	F(320000000, P_GPU_CC_PWW1_OUT_AUX, 2, 0, 0),
	F(465000000, P_GPU_CC_PWW1_OUT_AUX, 2, 0, 0),
	F(600000000, P_GPU_CC_PWW0_OUT_AUX2, 2, 0, 0),
	F(745000000, P_GPU_CC_PWW0_OUT_AUX2, 2, 0, 0),
	F(820000000, P_GPU_CC_PWW0_OUT_AUX2, 2, 0, 0),
	F(900000000, P_GPU_CC_PWW0_OUT_AUX2, 2, 0, 0),
	F(950000000, P_GPU_CC_PWW0_OUT_AUX2, 2, 0, 0),
	F(980000000, P_GPU_CC_PWW0_OUT_AUX2, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 gpu_cc_gx_gfx3d_cwk_swc = {
	.cmd_wcgw = 0x101c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = gpu_cc_pawent_map_1,
	.fweq_tbw = ftbw_gpu_cc_gx_gfx3d_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "gpu_cc_gx_gfx3d_cwk_swc",
		.pawent_data = gpu_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(gpu_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT | CWK_OPS_PAWENT_ENABWE,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gpu_cc_ahb_cwk = {
	.hawt_weg = 0x1078,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x1078,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_ahb_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_cwc_ahb_cwk = {
	.hawt_weg = 0x107c,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x107c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_cwc_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_cx_gfx3d_cwk = {
	.hawt_weg = 0x10a4,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x10a4,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_cx_gfx3d_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.hw = &gpu_cc_gx_gfx3d_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_cx_gmu_cwk = {
	.hawt_weg = 0x1098,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1098,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_cx_gmu_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.hw = &gpu_cc_gmu_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_cx_snoc_dvm_cwk = {
	.hawt_weg = 0x108c,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x108c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_cx_snoc_dvm_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_cxo_aon_cwk = {
	.hawt_weg = 0x1004,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x1004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_cxo_aon_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_cxo_cwk = {
	.hawt_weg = 0x109c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x109c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_cxo_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_gx_cxo_cwk = {
	.hawt_weg = 0x1060,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x1060,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_gx_cxo_cwk",
			.fwags = CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_gx_gfx3d_cwk = {
	.hawt_weg = 0x1054,
	.hawt_check = BWANCH_HAWT_SKIP,
	.cwkw = {
		.enabwe_weg = 0x1054,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_gx_gfx3d_cwk",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.hw = &gpu_cc_gx_gfx3d_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_sweep_cwk = {
	.hawt_weg = 0x1090,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x1090,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_sweep_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_hwos1_vote_gpu_smmu_cwk = {
	.hawt_weg = 0x5000,
	.hawt_check = BWANCH_VOTED,
	.cwkw = {
		.enabwe_weg = 0x5000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			 .name = "gpu_cc_hwos1_vote_gpu_smmu_cwk",
			 .ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc gpu_cx_gdsc = {
	.gdscw = 0x106c,
	.gds_hw_ctww = 0x1540,
	.pd = {
		.name = "gpu_cx_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc gpu_gx_gdsc = {
	.gdscw = 0x100c,
	.cwamp_io_ctww = 0x1508,
	.wesets = (unsigned int []){ GPU_GX_BCW },
	.weset_count = 1,
	.pd = {
		.name = "gpu_gx_gdsc",
	},
	.pawent = &gpu_cx_gdsc.pd,
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = CWAMP_IO | SW_WESET | VOTABWE,
};

static stwuct cwk_wegmap *gpu_cc_sm6115_cwocks[] = {
	[GPU_CC_AHB_CWK] = &gpu_cc_ahb_cwk.cwkw,
	[GPU_CC_CWC_AHB_CWK] = &gpu_cc_cwc_ahb_cwk.cwkw,
	[GPU_CC_CX_GFX3D_CWK] = &gpu_cc_cx_gfx3d_cwk.cwkw,
	[GPU_CC_CX_GMU_CWK] = &gpu_cc_cx_gmu_cwk.cwkw,
	[GPU_CC_CX_SNOC_DVM_CWK] = &gpu_cc_cx_snoc_dvm_cwk.cwkw,
	[GPU_CC_CXO_AON_CWK] = &gpu_cc_cxo_aon_cwk.cwkw,
	[GPU_CC_CXO_CWK] = &gpu_cc_cxo_cwk.cwkw,
	[GPU_CC_GMU_CWK_SWC] = &gpu_cc_gmu_cwk_swc.cwkw,
	[GPU_CC_GX_CXO_CWK] = &gpu_cc_gx_cxo_cwk.cwkw,
	[GPU_CC_GX_GFX3D_CWK] = &gpu_cc_gx_gfx3d_cwk.cwkw,
	[GPU_CC_GX_GFX3D_CWK_SWC] = &gpu_cc_gx_gfx3d_cwk_swc.cwkw,
	[GPU_CC_PWW0] = &gpu_cc_pww0.cwkw,
	[GPU_CC_PWW0_OUT_AUX2] = &gpu_cc_pww0_out_aux2.cwkw,
	[GPU_CC_PWW1] = &gpu_cc_pww1.cwkw,
	[GPU_CC_PWW1_OUT_AUX] = &gpu_cc_pww1_out_aux.cwkw,
	[GPU_CC_SWEEP_CWK] = &gpu_cc_sweep_cwk.cwkw,
	[GPU_CC_HWOS1_VOTE_GPU_SMMU_CWK] = &gpu_cc_hwos1_vote_gpu_smmu_cwk.cwkw,
};

static const stwuct qcom_weset_map gpu_cc_sm6115_wesets[] = {
	[GPU_GX_BCW] = { 0x1008 },
};

static stwuct gdsc *gpu_cc_sm6115_gdscs[] = {
	[GPU_CX_GDSC] = &gpu_cx_gdsc,
	[GPU_GX_GDSC] = &gpu_gx_gdsc,
};

static const stwuct wegmap_config gpu_cc_sm6115_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x9000,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc gpu_cc_sm6115_desc = {
	.config = &gpu_cc_sm6115_wegmap_config,
	.cwks = gpu_cc_sm6115_cwocks,
	.num_cwks = AWWAY_SIZE(gpu_cc_sm6115_cwocks),
	.wesets = gpu_cc_sm6115_wesets,
	.num_wesets = AWWAY_SIZE(gpu_cc_sm6115_wesets),
	.gdscs = gpu_cc_sm6115_gdscs,
	.num_gdscs = AWWAY_SIZE(gpu_cc_sm6115_gdscs),
};

static const stwuct of_device_id gpu_cc_sm6115_match_tabwe[] = {
	{ .compatibwe = "qcom,sm6115-gpucc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gpu_cc_sm6115_match_tabwe);

static int gpu_cc_sm6115_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, &gpu_cc_sm6115_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cwk_awpha_pww_configuwe(&gpu_cc_pww0, wegmap, &gpu_cc_pww0_config);
	cwk_awpha_pww_configuwe(&gpu_cc_pww1, wegmap, &gpu_cc_pww1_config);

	/* Set wecommended WAKEUP/SWEEP settings fow the gpu_cc_cx_gmu_cwk */
	qcom_bwanch_set_wakeup(wegmap, gpu_cc_cx_gmu_cwk, 0xf);
	qcom_bwanch_set_sweep(wegmap, gpu_cc_cx_gmu_cwk, 0xf);

	qcom_bwanch_set_fowce_mem_cowe(wegmap, gpu_cc_gx_gfx3d_cwk, twue);
	qcom_bwanch_set_fowce_pewiph_on(wegmap, gpu_cc_gx_gfx3d_cwk, twue);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &gpu_cc_sm6115_desc, wegmap);
}

static stwuct pwatfowm_dwivew gpu_cc_sm6115_dwivew = {
	.pwobe = gpu_cc_sm6115_pwobe,
	.dwivew = {
		.name = "sm6115-gpucc",
		.of_match_tabwe = gpu_cc_sm6115_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(gpu_cc_sm6115_dwivew);

MODUWE_DESCWIPTION("QTI GPU_CC SM6115 Dwivew");
MODUWE_WICENSE("GPW");
