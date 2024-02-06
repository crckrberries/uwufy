// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021, Konwad Dybcio <konwad.dybcio@somainwine.owg>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,gpucc-sm6350.h>

#incwude "common.h"
#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "weset.h"
#incwude "gdsc.h"

#define CX_GMU_CBCW_SWEEP_MASK		0xF
#define CX_GMU_CBCW_SWEEP_SHIFT		4
#define CX_GMU_CBCW_WAKE_MASK		0xF
#define CX_GMU_CBCW_WAKE_SHIFT		8

enum {
	DT_BI_TCXO,
	DT_GPWW0_OUT_MAIN,
	DT_GPWW0_OUT_MAIN_DIV,
};

enum {
	P_BI_TCXO,
	P_GPWW0_OUT_MAIN,
	P_GPWW0_OUT_MAIN_DIV,
	P_GPU_CC_PWW0_OUT_MAIN,
	P_GPU_CC_PWW0_OUT_ODD,
	P_GPU_CC_PWW1_OUT_EVEN,
	P_GPU_CC_PWW1_OUT_MAIN,
	P_GPU_CC_PWW1_OUT_ODD,
	P_CWC_DIV,
};

static const stwuct pww_vco fabia_vco[] = {
	{ 249600000, 2000000000, 0 },
};

/* 506MHz Configuwation*/
static const stwuct awpha_pww_config gpu_cc_pww0_config = {
	.w = 0x1A,
	.awpha = 0x5AAA,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002067,
	.test_ctw_vaw = 0x40000000,
	.test_ctw_hi_vaw = 0x00000002,
	.usew_ctw_vaw = 0x00000001,
	.usew_ctw_hi_vaw = 0x00004805,
};

static stwuct cwk_awpha_pww gpu_cc_pww0 = {
	.offset = 0x0,
	.vco_tabwe = fabia_vco,
	.num_vco = AWWAY_SIZE(fabia_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_pww0",
			.pawent_data =  &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fabia_ops,
		},
	},
};

static stwuct cwk_fixed_factow cwc_div = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "cwc_div",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&gpu_cc_pww0.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_fixed_factow_ops,
	},
};

/* 514MHz Configuwation*/
static const stwuct awpha_pww_config gpu_cc_pww1_config = {
	.w = 0x1A,
	.awpha = 0xC555,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002067,
	.test_ctw_vaw = 0x40000000,
	.test_ctw_hi_vaw = 0x00000002,
	.usew_ctw_vaw = 0x00000001,
	.usew_ctw_hi_vaw = 0x00004805,
};

static stwuct cwk_awpha_pww gpu_cc_pww1 = {
	.offset = 0x100,
	.vco_tabwe = fabia_vco,
	.num_vco = AWWAY_SIZE(fabia_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_pww1",
			.pawent_data =  &(const stwuct cwk_pawent_data){
				.index = DT_BI_TCXO,
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fabia_ops,
		},
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
	{ .index = DT_BI_TCXO, .fw_name = "bi_tcxo" },
	{ .hw = &gpu_cc_pww0.cwkw.hw },
	{ .hw = &gpu_cc_pww1.cwkw.hw },
	{ .index = DT_GPWW0_OUT_MAIN, .fw_name = "gcc_gpu_gpww0_cwk_swc" },
	{ .index = DT_GPWW0_OUT_MAIN_DIV, .fw_name = "gcc_gpu_gpww0_div_cwk_swc" },
};

static const stwuct pawent_map gpu_cc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_CWC_DIV, 1 },
	{ P_GPU_CC_PWW0_OUT_ODD, 2 },
	{ P_GPU_CC_PWW1_OUT_EVEN, 3 },
	{ P_GPU_CC_PWW1_OUT_ODD, 4 },
	{ P_GPWW0_OUT_MAIN, 5 },
};

static const stwuct cwk_pawent_data gpu_cc_pawent_data_1[] = {
	{ .index = DT_BI_TCXO, .fw_name = "bi_tcxo" },
	{ .hw = &cwc_div.hw },
	{ .hw = &gpu_cc_pww0.cwkw.hw },
	{ .hw = &gpu_cc_pww1.cwkw.hw },
	{ .hw = &gpu_cc_pww1.cwkw.hw },
	{ .index = DT_GPWW0_OUT_MAIN, .fw_name = "gcc_gpu_gpww0_cwk_swc" },
};

static const stwuct fweq_tbw ftbw_gpu_cc_gmu_cwk_swc[] = {
	F(200000000, P_GPWW0_OUT_MAIN_DIV, 1.5, 0, 0),
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
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_gpu_cc_gx_gfx3d_cwk_swc[] = {
	F(253000000, P_CWC_DIV, 1, 0, 0),
	F(355000000, P_CWC_DIV, 1, 0, 0),
	F(430000000, P_CWC_DIV, 1, 0, 0),
	F(565000000, P_CWC_DIV, 1, 0, 0),
	F(650000000, P_CWC_DIV, 1, 0, 0),
	F(800000000, P_CWC_DIV, 1, 0, 0),
	F(825000000, P_CWC_DIV, 1, 0, 0),
	F(850000000, P_CWC_DIV, 1, 0, 0),
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
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch gpu_cc_acd_ahb_cwk = {
	.hawt_weg = 0x1168,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1168,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_acd_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_acd_cxo_cwk = {
	.hawt_weg = 0x1164,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1164,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_acd_cxo_cwk",
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
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpu_cc_gx_gfx3d_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_cx_gfx3d_swv_cwk = {
	.hawt_weg = 0x10a8,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x10a8,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_cx_gfx3d_swv_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpu_cc_gx_gfx3d_cwk_swc.cwkw.hw,
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
			.pawent_hws = (const stwuct cwk_hw*[]){
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

static stwuct cwk_bwanch gpu_cc_gx_cxo_cwk = {
	.hawt_weg = 0x1060,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1060,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_gx_cxo_cwk",
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
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpu_cc_gx_gfx3d_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_gx_gmu_cwk = {
	.hawt_weg = 0x1064,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1064,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_gx_gmu_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&gpu_cc_gmu_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch gpu_cc_gx_vsense_cwk = {
	.hawt_weg = 0x1058,
	.hawt_check = BWANCH_HAWT_DEWAY,
	.cwkw = {
		.enabwe_weg = 0x1058,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_gx_vsense_cwk",
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
	.pd = {
		.name = "gpu_gx_gdsc",
		.powew_on = gdsc_gx_do_nothing_enabwe,
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = CWAMP_IO | POWW_CFG_GDSCW,
};

static stwuct cwk_hw *gpu_cc_sm6350_hws[] = {
	[GPU_CC_CWC_DIV] = &cwc_div.hw,
};

static stwuct cwk_wegmap *gpu_cc_sm6350_cwocks[] = {
	[GPU_CC_ACD_AHB_CWK] = &gpu_cc_acd_ahb_cwk.cwkw,
	[GPU_CC_ACD_CXO_CWK] = &gpu_cc_acd_cxo_cwk.cwkw,
	[GPU_CC_AHB_CWK] = &gpu_cc_ahb_cwk.cwkw,
	[GPU_CC_CWC_AHB_CWK] = &gpu_cc_cwc_ahb_cwk.cwkw,
	[GPU_CC_CX_GFX3D_CWK] = &gpu_cc_cx_gfx3d_cwk.cwkw,
	[GPU_CC_CX_GFX3D_SWV_CWK] = &gpu_cc_cx_gfx3d_swv_cwk.cwkw,
	[GPU_CC_CX_GMU_CWK] = &gpu_cc_cx_gmu_cwk.cwkw,
	[GPU_CC_CX_SNOC_DVM_CWK] = &gpu_cc_cx_snoc_dvm_cwk.cwkw,
	[GPU_CC_CXO_AON_CWK] = &gpu_cc_cxo_aon_cwk.cwkw,
	[GPU_CC_CXO_CWK] = &gpu_cc_cxo_cwk.cwkw,
	[GPU_CC_GMU_CWK_SWC] = &gpu_cc_gmu_cwk_swc.cwkw,
	[GPU_CC_GX_CXO_CWK] = &gpu_cc_gx_cxo_cwk.cwkw,
	[GPU_CC_GX_GFX3D_CWK] = &gpu_cc_gx_gfx3d_cwk.cwkw,
	[GPU_CC_GX_GFX3D_CWK_SWC] = &gpu_cc_gx_gfx3d_cwk_swc.cwkw,
	[GPU_CC_GX_GMU_CWK] = &gpu_cc_gx_gmu_cwk.cwkw,
	[GPU_CC_GX_VSENSE_CWK] = &gpu_cc_gx_vsense_cwk.cwkw,
	[GPU_CC_PWW0] = &gpu_cc_pww0.cwkw,
	[GPU_CC_PWW1] = &gpu_cc_pww1.cwkw,
};

static stwuct gdsc *gpu_cc_sm6350_gdscs[] = {
	[GPU_CX_GDSC] = &gpu_cx_gdsc,
	[GPU_GX_GDSC] = &gpu_gx_gdsc,
};

static const stwuct wegmap_config gpu_cc_sm6350_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x8008,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc gpu_cc_sm6350_desc = {
	.config = &gpu_cc_sm6350_wegmap_config,
	.cwk_hws = gpu_cc_sm6350_hws,
	.num_cwk_hws = AWWAY_SIZE(gpu_cc_sm6350_hws),
	.cwks = gpu_cc_sm6350_cwocks,
	.num_cwks = AWWAY_SIZE(gpu_cc_sm6350_cwocks),
	.gdscs = gpu_cc_sm6350_gdscs,
	.num_gdscs = AWWAY_SIZE(gpu_cc_sm6350_gdscs),
};

static const stwuct of_device_id gpu_cc_sm6350_match_tabwe[] = {
	{ .compatibwe = "qcom,sm6350-gpucc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gpu_cc_sm6350_match_tabwe);

static int gpu_cc_sm6350_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	unsigned int vawue, mask;

	wegmap = qcom_cc_map(pdev, &gpu_cc_sm6350_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cwk_fabia_pww_configuwe(&gpu_cc_pww0, wegmap, &gpu_cc_pww0_config);
	cwk_fabia_pww_configuwe(&gpu_cc_pww1, wegmap, &gpu_cc_pww1_config);

	/* Configuwe gpu_cc_cx_gmu_cwk with wecommended wakeup/sweep settings */
	mask = CX_GMU_CBCW_WAKE_MASK << CX_GMU_CBCW_WAKE_SHIFT;
	mask |= CX_GMU_CBCW_SWEEP_MASK << CX_GMU_CBCW_SWEEP_SHIFT;
	vawue = 0xF << CX_GMU_CBCW_WAKE_SHIFT | 0xF << CX_GMU_CBCW_SWEEP_SHIFT;
	wegmap_update_bits(wegmap, 0x1098, mask, vawue);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &gpu_cc_sm6350_desc, wegmap);
}

static stwuct pwatfowm_dwivew gpu_cc_sm6350_dwivew = {
	.pwobe = gpu_cc_sm6350_pwobe,
	.dwivew = {
		.name = "sm6350-gpucc",
		.of_match_tabwe = gpu_cc_sm6350_match_tabwe,
	},
};

static int __init gpu_cc_sm6350_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gpu_cc_sm6350_dwivew);
}
cowe_initcaww(gpu_cc_sm6350_init);

static void __exit gpu_cc_sm6350_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gpu_cc_sm6350_dwivew);
}
moduwe_exit(gpu_cc_sm6350_exit);

MODUWE_DESCWIPTION("QTI GPU_CC WAGOON Dwivew");
MODUWE_WICENSE("GPW v2");
