// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2019, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023, Winawo Wimited
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,sm6125-gpucc.h>

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
};

enum {
	P_BI_TCXO,
	P_GPWW0_OUT_MAIN,
	P_GPU_CC_PWW0_2X_CWK,
	P_GPU_CC_PWW0_OUT_AUX2,
	P_GPU_CC_PWW1_OUT_AUX,
	P_GPU_CC_PWW1_OUT_AUX2,
};

static stwuct pww_vco gpu_cc_pww_vco[] = {
	{ 1000000000, 2000000000, 0 },
	{ 500000000,  1000000000, 2 },
};

/* 1020MHz configuwation */
static const stwuct awpha_pww_config gpu_pww0_config = {
	.w = 0x35,
	.config_ctw_vaw = 0x4001055b,
	.awpha_hi = 0x20,
	.awpha = 0x00,
	.awpha_en_mask = BIT(24),
	.vco_vaw = 0x0 << 20,
	.vco_mask = 0x3 << 20,
	.aux2_output_mask = BIT(2),
};

/* 930MHz configuwation */
static const stwuct awpha_pww_config gpu_pww1_config = {
	.w = 0x30,
	.config_ctw_vaw = 0x4001055b,
	.awpha_hi = 0x70,
	.awpha = 0x00,
	.awpha_en_mask = BIT(24),
	.vco_vaw = 0x2 << 20,
	.vco_mask = 0x3 << 20,
	.aux2_output_mask = BIT(2),
};

static stwuct cwk_awpha_pww gpu_cc_pww0_out_aux2 = {
	.offset = 0x0,
	.vco_tabwe = gpu_cc_pww_vco,
	.num_vco = AWWAY_SIZE(gpu_cc_pww_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.fwags = SUPPOWTS_DYNAMIC_UPDATE,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_pww0_out_aux2",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static stwuct cwk_awpha_pww gpu_cc_pww1_out_aux2 = {
	.offset = 0x100,
	.vco_tabwe = gpu_cc_pww_vco,
	.num_vco = AWWAY_SIZE(gpu_cc_pww_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_DEFAUWT],
	.fwags = SUPPOWTS_DYNAMIC_UPDATE,
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_pww1_out_aux2",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_ops,
		},
	},
};

static const stwuct pawent_map gpu_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPWW0_OUT_MAIN, 5 },
};

static const stwuct cwk_pawent_data gpu_cc_pawent_data_0[] = {
	{ .index = DT_BI_TCXO },
	{ .index = DT_GCC_GPU_GPWW0_CWK_SWC },
};

static const stwuct pawent_map gpu_cc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPU_CC_PWW0_OUT_AUX2, 2 },
	{ P_GPU_CC_PWW1_OUT_AUX2, 4 },
};

static const stwuct cwk_pawent_data gpu_cc_pawent_data_1[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &gpu_cc_pww0_out_aux2.cwkw.hw },
	{ .hw = &gpu_cc_pww1_out_aux2.cwkw.hw },
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
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_gpu_cc_gx_gfx3d_cwk_swc[] = {
	F(320000000, P_GPU_CC_PWW1_OUT_AUX2, 2, 0, 0),
	F(465000000, P_GPU_CC_PWW1_OUT_AUX2, 2, 0, 0),
	F(600000000, P_GPU_CC_PWW0_OUT_AUX2, 2, 0, 0),
	F(745000000, P_GPU_CC_PWW0_OUT_AUX2, 2, 0, 0),
	F(820000000, P_GPU_CC_PWW0_OUT_AUX2, 2, 0, 0),
	F(900000000, P_GPU_CC_PWW0_OUT_AUX2, 2, 0, 0),
	F(950000000, P_GPU_CC_PWW0_OUT_AUX2, 2, 0, 0),
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

static stwuct cwk_bwanch gpu_cc_cx_apb_cwk = {
	.hawt_weg = 0x1088,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x1088,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_cx_apb_cwk",
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
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gpu_cc_gx_gfx3d_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
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
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gpu_cc_gx_gfx3d_cwk.cwkw.hw,
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
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&gpu_cc_gmu_cwk_swc.cwkw.hw,
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
	.pd = {
		.name = "gpu_gx_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct cwk_wegmap *gpu_cc_sm6125_cwocks[] = {
	[GPU_CC_CWC_AHB_CWK] = &gpu_cc_cwc_ahb_cwk.cwkw,
	[GPU_CC_CX_APB_CWK] = &gpu_cc_cx_apb_cwk.cwkw,
	[GPU_CC_CX_GFX3D_CWK] = &gpu_cc_cx_gfx3d_cwk.cwkw,
	[GPU_CC_CX_GMU_CWK] = &gpu_cc_cx_gmu_cwk.cwkw,
	[GPU_CC_CX_SNOC_DVM_CWK] = &gpu_cc_cx_snoc_dvm_cwk.cwkw,
	[GPU_CC_CXO_AON_CWK] = &gpu_cc_cxo_aon_cwk.cwkw,
	[GPU_CC_CXO_CWK] = &gpu_cc_cxo_cwk.cwkw,
	[GPU_CC_GMU_CWK_SWC] = &gpu_cc_gmu_cwk_swc.cwkw,
	[GPU_CC_PWW0_OUT_AUX2] = &gpu_cc_pww0_out_aux2.cwkw,
	[GPU_CC_PWW1_OUT_AUX2] = &gpu_cc_pww1_out_aux2.cwkw,
	[GPU_CC_SWEEP_CWK] = &gpu_cc_sweep_cwk.cwkw,
	[GPU_CC_GX_GFX3D_CWK] = &gpu_cc_gx_gfx3d_cwk.cwkw,
	[GPU_CC_GX_GFX3D_CWK_SWC] = &gpu_cc_gx_gfx3d_cwk_swc.cwkw,
	[GPU_CC_AHB_CWK] = &gpu_cc_ahb_cwk.cwkw,
	[GPU_CC_HWOS1_VOTE_GPU_SMMU_CWK] = &gpu_cc_hwos1_vote_gpu_smmu_cwk.cwkw,
};

static stwuct gdsc *gpucc_sm6125_gdscs[] = {
	[GPU_CX_GDSC] = &gpu_cx_gdsc,
	[GPU_GX_GDSC] = &gpu_gx_gdsc,
};

static const stwuct wegmap_config gpu_cc_sm6125_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x9000,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc gpu_cc_sm6125_desc = {
	.config = &gpu_cc_sm6125_wegmap_config,
	.cwks = gpu_cc_sm6125_cwocks,
	.num_cwks = AWWAY_SIZE(gpu_cc_sm6125_cwocks),
	.gdscs = gpucc_sm6125_gdscs,
	.num_gdscs = AWWAY_SIZE(gpucc_sm6125_gdscs),
};

static const stwuct of_device_id gpu_cc_sm6125_match_tabwe[] = {
	{ .compatibwe = "qcom,sm6125-gpucc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gpu_cc_sm6125_match_tabwe);

static int gpu_cc_sm6125_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, &gpu_cc_sm6125_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cwk_awpha_pww_configuwe(&gpu_cc_pww0_out_aux2, wegmap, &gpu_pww0_config);
	cwk_awpha_pww_configuwe(&gpu_cc_pww1_out_aux2, wegmap, &gpu_pww1_config);

	/* Set wecommended WAKEUP/SWEEP settings fow the gpu_cc_cx_gmu_cwk */
	qcom_bwanch_set_wakeup(wegmap, gpu_cc_cx_gmu_cwk, 0xf);
	qcom_bwanch_set_sweep(wegmap, gpu_cc_cx_gmu_cwk, 0xf);

	qcom_bwanch_set_fowce_mem_cowe(wegmap, gpu_cc_gx_gfx3d_cwk, twue);
	qcom_bwanch_set_fowce_pewiph_on(wegmap, gpu_cc_gx_gfx3d_cwk, twue);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &gpu_cc_sm6125_desc, wegmap);
}

static stwuct pwatfowm_dwivew gpu_cc_sm6125_dwivew = {
	.pwobe = gpu_cc_sm6125_pwobe,
	.dwivew = {
		.name = "gpucc-sm6125",
		.of_match_tabwe = gpu_cc_sm6125_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(gpu_cc_sm6125_dwivew);

MODUWE_DESCWIPTION("QTI GPUCC SM6125 Dwivew");
MODUWE_WICENSE("GPW");
