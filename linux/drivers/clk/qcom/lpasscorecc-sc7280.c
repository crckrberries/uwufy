// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,wpasscowecc-sc7280.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "common.h"
#incwude "gdsc.h"

enum {
	P_BI_TCXO,
	P_WPASS_COWE_CC_DIG_PWW_OUT_MAIN,
	P_WPASS_COWE_CC_DIG_PWW_OUT_MAIN_DIV_CWK_SWC,
	P_WPASS_COWE_CC_DIG_PWW_OUT_ODD,
};

static const stwuct pww_vco wucid_vco[] = {
	{ 249600000, 2000000000, 0 },
};

/* 614.4MHz configuwation */
static const stwuct awpha_pww_config wpass_cowe_cc_dig_pww_config = {
	.w = 0x20,
	.awpha = 0x0,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0xB2923BBC,
	.usew_ctw_vaw = 0x00005100,
	.usew_ctw_hi_vaw = 0x00050805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww wpass_cowe_cc_dig_pww = {
	.offset = 0x1000,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "wpass_cowe_cc_dig_pww",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.index = 0,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct cwk_div_tabwe post_div_tabwe_wpass_cowe_cc_dig_pww_out_odd[] = {
	{ 0x5, 5 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv wpass_cowe_cc_dig_pww_out_odd = {
	.offset = 0x1000,
	.post_div_shift = 12,
	.post_div_tabwe = post_div_tabwe_wpass_cowe_cc_dig_pww_out_odd,
	.num_post_div = AWWAY_SIZE(post_div_tabwe_wpass_cowe_cc_dig_pww_out_odd),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "wpass_cowe_cc_dig_pww_out_odd",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&wpass_cowe_cc_dig_pww.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_wucid_ops,
	},
};

static stwuct cwk_wegmap_div wpass_cowe_cc_dig_pww_out_main_div_cwk_swc = {
	.weg = 0x1054,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(stwuct cwk_init_data) {
		.name = "wpass_cowe_cc_dig_pww_out_main_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]){
			&wpass_cowe_cc_dig_pww.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};


static const stwuct pawent_map wpass_cowe_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_WPASS_COWE_CC_DIG_PWW_OUT_ODD, 5 },
};

static const stwuct cwk_pawent_data wpass_cowe_cc_pawent_data_0[] = {
	{ .index = 0 },
	{ .hw = &wpass_cowe_cc_dig_pww_out_odd.cwkw.hw },
};

static const stwuct pawent_map wpass_cowe_cc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
	{ P_WPASS_COWE_CC_DIG_PWW_OUT_MAIN, 1 },
	{ P_WPASS_COWE_CC_DIG_PWW_OUT_MAIN_DIV_CWK_SWC, 2 },
};

static const stwuct cwk_pawent_data wpass_cowe_cc_pawent_data_ao_2[] = {
	{ .index = 1 },
	{ .hw = &wpass_cowe_cc_dig_pww.cwkw.hw },
	{ .hw = &wpass_cowe_cc_dig_pww_out_main_div_cwk_swc.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_wpass_cowe_cc_cowe_cwk_swc[] = {
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(51200000, P_WPASS_COWE_CC_DIG_PWW_OUT_MAIN_DIV_CWK_SWC, 6, 0, 0),
	F(102400000, P_WPASS_COWE_CC_DIG_PWW_OUT_MAIN_DIV_CWK_SWC, 3, 0, 0),
	F(204800000, P_WPASS_COWE_CC_DIG_PWW_OUT_MAIN, 3, 0, 0),
	{ }
};

static stwuct cwk_wcg2 wpass_cowe_cc_cowe_cwk_swc = {
	.cmd_wcgw = 0x1d000,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = wpass_cowe_cc_pawent_map_2,
	.fweq_tbw = ftbw_wpass_cowe_cc_cowe_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data){
		.name = "wpass_cowe_cc_cowe_cwk_swc",
		.pawent_data = wpass_cowe_cc_pawent_data_ao_2,
		.num_pawents = AWWAY_SIZE(wpass_cowe_cc_pawent_data_ao_2),
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_wpass_cowe_cc_ext_if0_cwk_swc[] = {
	F(256000, P_WPASS_COWE_CC_DIG_PWW_OUT_ODD, 15, 1, 32),
	F(512000, P_WPASS_COWE_CC_DIG_PWW_OUT_ODD, 15, 1, 16),
	F(768000, P_WPASS_COWE_CC_DIG_PWW_OUT_ODD, 10, 1, 16),
	F(1024000, P_WPASS_COWE_CC_DIG_PWW_OUT_ODD, 15, 1, 8),
	F(1536000, P_WPASS_COWE_CC_DIG_PWW_OUT_ODD, 10, 1, 8),
	F(2048000, P_WPASS_COWE_CC_DIG_PWW_OUT_ODD, 15, 1, 4),
	F(3072000, P_WPASS_COWE_CC_DIG_PWW_OUT_ODD, 10, 1, 4),
	F(4096000, P_WPASS_COWE_CC_DIG_PWW_OUT_ODD, 15, 1, 2),
	F(6144000, P_WPASS_COWE_CC_DIG_PWW_OUT_ODD, 10, 1, 2),
	F(8192000, P_WPASS_COWE_CC_DIG_PWW_OUT_ODD, 15, 0, 0),
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(12288000, P_WPASS_COWE_CC_DIG_PWW_OUT_ODD, 10, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(24576000, P_WPASS_COWE_CC_DIG_PWW_OUT_ODD, 5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 wpass_cowe_cc_ext_if0_cwk_swc = {
	.cmd_wcgw = 0x10000,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = wpass_cowe_cc_pawent_map_0,
	.fweq_tbw = ftbw_wpass_cowe_cc_ext_if0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data){
		.name = "wpass_cowe_cc_ext_if0_cwk_swc",
		.pawent_data = wpass_cowe_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(wpass_cowe_cc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 wpass_cowe_cc_ext_if1_cwk_swc = {
	.cmd_wcgw = 0x11000,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = wpass_cowe_cc_pawent_map_0,
	.fweq_tbw = ftbw_wpass_cowe_cc_ext_if0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data){
		.name = "wpass_cowe_cc_ext_if1_cwk_swc",
		.pawent_data = wpass_cowe_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(wpass_cowe_cc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 wpass_cowe_cc_ext_mcwk0_cwk_swc = {
	.cmd_wcgw = 0x20000,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = wpass_cowe_cc_pawent_map_0,
	.fweq_tbw = ftbw_wpass_cowe_cc_ext_if0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data){
		.name = "wpass_cowe_cc_ext_mcwk0_cwk_swc",
		.pawent_data = wpass_cowe_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(wpass_cowe_cc_pawent_data_0),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch wpass_cowe_cc_cowe_cwk = {
	.hawt_weg = 0x1f000,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x1f000,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x1f000,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_cowe_cc_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_cowe_cc_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_aon_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_cowe_cc_ext_if0_ibit_cwk = {
	.hawt_weg = 0x10018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x10018,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_cowe_cc_ext_if0_ibit_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_cowe_cc_ext_if0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_cowe_cc_ext_if1_ibit_cwk = {
	.hawt_weg = 0x11018,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x11018,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_cowe_cc_ext_if1_ibit_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_cowe_cc_ext_if1_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_cowe_cc_wpm_cowe_cwk = {
	.hawt_weg = 0x1e000,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1e000,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_cowe_cc_wpm_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_cowe_cc_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_cowe_cc_wpm_mem0_cowe_cwk = {
	.hawt_weg = 0x1e004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x1e004,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_cowe_cc_wpm_mem0_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_cowe_cc_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_cowe_cc_ext_mcwk0_cwk = {
	.hawt_weg = 0x20014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x20014,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_cowe_cc_ext_mcwk0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_cowe_cc_ext_mcwk0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_cowe_cc_sysnoc_mpowt_cowe_cwk = {
	.hawt_weg = 0x23000,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x23000,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x23000,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data){
			.name = "wpass_cowe_cc_sysnoc_mpowt_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&wpass_cowe_cc_cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc wpass_cowe_cc_wpass_cowe_hm_gdsc = {
	.gdscw = 0x0,
	.pd = {
		.name = "wpass_cowe_cc_wpass_cowe_hm_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = WETAIN_FF_ENABWE,
};

static stwuct cwk_wegmap *wpass_cowe_cc_sc7280_cwocks[] = {
	[WPASS_COWE_CC_COWE_CWK] = &wpass_cowe_cc_cowe_cwk.cwkw,
	[WPASS_COWE_CC_COWE_CWK_SWC] = &wpass_cowe_cc_cowe_cwk_swc.cwkw,
	[WPASS_COWE_CC_DIG_PWW] = &wpass_cowe_cc_dig_pww.cwkw,
	[WPASS_COWE_CC_DIG_PWW_OUT_MAIN_DIV_CWK_SWC] =
		&wpass_cowe_cc_dig_pww_out_main_div_cwk_swc.cwkw,
	[WPASS_COWE_CC_DIG_PWW_OUT_ODD] = &wpass_cowe_cc_dig_pww_out_odd.cwkw,
	[WPASS_COWE_CC_EXT_IF0_CWK_SWC] = &wpass_cowe_cc_ext_if0_cwk_swc.cwkw,
	[WPASS_COWE_CC_EXT_IF0_IBIT_CWK] = &wpass_cowe_cc_ext_if0_ibit_cwk.cwkw,
	[WPASS_COWE_CC_EXT_IF1_CWK_SWC] = &wpass_cowe_cc_ext_if1_cwk_swc.cwkw,
	[WPASS_COWE_CC_EXT_IF1_IBIT_CWK] = &wpass_cowe_cc_ext_if1_ibit_cwk.cwkw,
	[WPASS_COWE_CC_WPM_COWE_CWK] = &wpass_cowe_cc_wpm_cowe_cwk.cwkw,
	[WPASS_COWE_CC_WPM_MEM0_COWE_CWK] = &wpass_cowe_cc_wpm_mem0_cowe_cwk.cwkw,
	[WPASS_COWE_CC_SYSNOC_MPOWT_COWE_CWK] = &wpass_cowe_cc_sysnoc_mpowt_cowe_cwk.cwkw,
	[WPASS_COWE_CC_EXT_MCWK0_CWK] = &wpass_cowe_cc_ext_mcwk0_cwk.cwkw,
	[WPASS_COWE_CC_EXT_MCWK0_CWK_SWC] = &wpass_cowe_cc_ext_mcwk0_cwk_swc.cwkw,
};

static stwuct wegmap_config wpass_cowe_cc_sc7280_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc wpass_cowe_cc_sc7280_desc = {
	.config = &wpass_cowe_cc_sc7280_wegmap_config,
	.cwks = wpass_cowe_cc_sc7280_cwocks,
	.num_cwks = AWWAY_SIZE(wpass_cowe_cc_sc7280_cwocks),
};

static const stwuct of_device_id wpass_cowe_cc_sc7280_match_tabwe[] = {
	{ .compatibwe = "qcom,sc7280-wpasscowecc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpass_cowe_cc_sc7280_match_tabwe);

static stwuct gdsc *wpass_cowe_hm_sc7280_gdscs[] = {
	[WPASS_COWE_CC_WPASS_COWE_HM_GDSC] = &wpass_cowe_cc_wpass_cowe_hm_gdsc,
};

static const stwuct qcom_cc_desc wpass_cowe_hm_sc7280_desc = {
	.config = &wpass_cowe_cc_sc7280_wegmap_config,
	.gdscs = wpass_cowe_hm_sc7280_gdscs,
	.num_gdscs = AWWAY_SIZE(wpass_cowe_hm_sc7280_gdscs),
};

static int wpass_cowe_cc_sc7280_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct qcom_cc_desc *desc;
	stwuct wegmap *wegmap;

	wpass_cowe_cc_sc7280_wegmap_config.name = "wpass_cowe_cc";
	wpass_cowe_cc_sc7280_wegmap_config.max_wegistew = 0x4f004;
	desc = &wpass_cowe_cc_sc7280_desc;

	wegmap = qcom_cc_map(pdev, desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cwk_wucid_pww_configuwe(&wpass_cowe_cc_dig_pww, wegmap, &wpass_cowe_cc_dig_pww_config);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &wpass_cowe_cc_sc7280_desc, wegmap);
}

static stwuct pwatfowm_dwivew wpass_cowe_cc_sc7280_dwivew = {
	.pwobe = wpass_cowe_cc_sc7280_pwobe,
	.dwivew = {
		.name = "wpass_cowe_cc-sc7280",
		.of_match_tabwe = wpass_cowe_cc_sc7280_match_tabwe,
	},
};

static int wpass_hm_cowe_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct qcom_cc_desc *desc;

	wpass_cowe_cc_sc7280_wegmap_config.name = "wpass_hm_cowe";
	wpass_cowe_cc_sc7280_wegmap_config.max_wegistew = 0x24;
	desc = &wpass_cowe_hm_sc7280_desc;

	wetuwn qcom_cc_pwobe_by_index(pdev, 0, desc);
}

static const stwuct of_device_id wpass_hm_sc7280_match_tabwe[] = {
	{ .compatibwe = "qcom,sc7280-wpasshm" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpass_hm_sc7280_match_tabwe);

static stwuct pwatfowm_dwivew wpass_hm_sc7280_dwivew = {
	.pwobe = wpass_hm_cowe_pwobe,
	.dwivew = {
		.name = "wpass_hm-sc7280",
		.of_match_tabwe = wpass_hm_sc7280_match_tabwe,
	},
};

static int __init wpass_cowe_cc_sc7280_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&wpass_hm_sc7280_dwivew);
	if (wet)
		wetuwn wet;

	wetuwn pwatfowm_dwivew_wegistew(&wpass_cowe_cc_sc7280_dwivew);
}
subsys_initcaww(wpass_cowe_cc_sc7280_init);

static void __exit wpass_cowe_cc_sc7280_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wpass_cowe_cc_sc7280_dwivew);
	pwatfowm_dwivew_unwegistew(&wpass_hm_sc7280_dwivew);
}
moduwe_exit(wpass_cowe_cc_sc7280_exit);

MODUWE_DESCWIPTION("QTI WPASS_COWE_CC SC7280 Dwivew");
MODUWE_WICENSE("GPW v2");
