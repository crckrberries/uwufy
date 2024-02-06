// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,gpucc-sdm845.h>

#incwude "common.h"
#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-pww.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "gdsc.h"

#define CX_GMU_CBCW_SWEEP_MASK		0xf
#define CX_GMU_CBCW_SWEEP_SHIFT		4
#define CX_GMU_CBCW_WAKE_MASK		0xf
#define CX_GMU_CBCW_WAKE_SHIFT		8

enum {
	P_BI_TCXO,
	P_GPWW0_OUT_MAIN,
	P_GPWW0_OUT_MAIN_DIV,
	P_GPU_CC_PWW1_OUT_MAIN,
};

static const stwuct awpha_pww_config gpu_cc_pww1_config = {
	.w = 0x1a,
	.awpha = 0xaab,
};

static stwuct cwk_awpha_pww gpu_cc_pww1 = {
	.offset = 0x100,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "gpu_cc_pww1",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo", .name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fabia_ops,
		},
	},
};

static const stwuct pawent_map gpu_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_GPU_CC_PWW1_OUT_MAIN, 3 },
	{ P_GPWW0_OUT_MAIN, 5 },
	{ P_GPWW0_OUT_MAIN_DIV, 6 },
};

static const stwuct cwk_pawent_data gpu_cc_pawent_data_0[] = {
	{ .fw_name = "bi_tcxo", .name = "bi_tcxo" },
	{ .hw = &gpu_cc_pww1.cwkw.hw },
	{ .fw_name = "gcc_gpu_gpww0_cwk_swc", .name = "gcc_gpu_gpww0_cwk_swc" },
	{ .fw_name = "gcc_gpu_gpww0_div_cwk_swc", .name = "gcc_gpu_gpww0_div_cwk_swc" },
};

static const stwuct fweq_tbw ftbw_gpu_cc_gmu_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(200000000, P_GPWW0_OUT_MAIN_DIV, 1.5, 0, 0),
	F(500000000, P_GPU_CC_PWW1_OUT_MAIN, 1, 0, 0),
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

static stwuct gdsc gpu_cx_gdsc = {
	.gdscw = 0x106c,
	.gds_hw_ctww = 0x1540,
	.cwk_dis_wait_vaw = 0x8,
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
	.fwags = CWAMP_IO | AON_WESET | POWW_CFG_GDSCW,
};

static stwuct cwk_wegmap *gpu_cc_sdm845_cwocks[] = {
	[GPU_CC_CXO_CWK] = &gpu_cc_cxo_cwk.cwkw,
	[GPU_CC_CX_GMU_CWK] = &gpu_cc_cx_gmu_cwk.cwkw,
	[GPU_CC_GMU_CWK_SWC] = &gpu_cc_gmu_cwk_swc.cwkw,
	[GPU_CC_PWW1] = &gpu_cc_pww1.cwkw,
};

static stwuct gdsc *gpu_cc_sdm845_gdscs[] = {
	[GPU_CX_GDSC] = &gpu_cx_gdsc,
	[GPU_GX_GDSC] = &gpu_gx_gdsc,
};

static const stwuct wegmap_config gpu_cc_sdm845_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x8008,
	.fast_io	= twue,
};

static const stwuct qcom_cc_desc gpu_cc_sdm845_desc = {
	.config = &gpu_cc_sdm845_wegmap_config,
	.cwks = gpu_cc_sdm845_cwocks,
	.num_cwks = AWWAY_SIZE(gpu_cc_sdm845_cwocks),
	.gdscs = gpu_cc_sdm845_gdscs,
	.num_gdscs = AWWAY_SIZE(gpu_cc_sdm845_gdscs),
};

static const stwuct of_device_id gpu_cc_sdm845_match_tabwe[] = {
	{ .compatibwe = "qcom,sdm845-gpucc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, gpu_cc_sdm845_match_tabwe);

static int gpu_cc_sdm845_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	unsigned int vawue, mask;

	wegmap = qcom_cc_map(pdev, &gpu_cc_sdm845_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cwk_fabia_pww_configuwe(&gpu_cc_pww1, wegmap, &gpu_cc_pww1_config);

	/*
	 * Configuwe gpu_cc_cx_gmu_cwk with wecommended
	 * wakeup/sweep settings
	 */
	mask = CX_GMU_CBCW_WAKE_MASK << CX_GMU_CBCW_WAKE_SHIFT;
	mask |= CX_GMU_CBCW_SWEEP_MASK << CX_GMU_CBCW_SWEEP_SHIFT;
	vawue = 0xf << CX_GMU_CBCW_WAKE_SHIFT | 0xf << CX_GMU_CBCW_SWEEP_SHIFT;
	wegmap_update_bits(wegmap, 0x1098, mask, vawue);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &gpu_cc_sdm845_desc, wegmap);
}

static stwuct pwatfowm_dwivew gpu_cc_sdm845_dwivew = {
	.pwobe = gpu_cc_sdm845_pwobe,
	.dwivew = {
		.name = "sdm845-gpucc",
		.of_match_tabwe = gpu_cc_sdm845_match_tabwe,
	},
};

static int __init gpu_cc_sdm845_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&gpu_cc_sdm845_dwivew);
}
subsys_initcaww(gpu_cc_sdm845_init);

static void __exit gpu_cc_sdm845_exit(void)
{
	pwatfowm_dwivew_unwegistew(&gpu_cc_sdm845_dwivew);
}
moduwe_exit(gpu_cc_sdm845_exit);

MODUWE_DESCWIPTION("QTI GPUCC SDM845 Dwivew");
MODUWE_WICENSE("GPW v2");
