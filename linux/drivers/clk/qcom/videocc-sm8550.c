// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,sm8450-videocc.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-wegmap-dividew.h"
#incwude "common.h"
#incwude "gdsc.h"
#incwude "weset.h"

enum {
	DT_BI_TCXO,
};

enum {
	P_BI_TCXO,
	P_VIDEO_CC_PWW0_OUT_MAIN,
	P_VIDEO_CC_PWW1_OUT_MAIN,
};

static const stwuct pww_vco wucid_owe_vco[] = {
	{ 249600000, 2300000000, 0 },
};

static const stwuct awpha_pww_config video_cc_pww0_config = {
	.w = 0x25,
	.awpha = 0x8000,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00182261,
	.config_ctw_hi1_vaw = 0x82aa299c,
	.test_ctw_vaw = 0x00000000,
	.test_ctw_hi_vaw = 0x00000003,
	.test_ctw_hi1_vaw = 0x00009000,
	.test_ctw_hi2_vaw = 0x00000034,
	.usew_ctw_vaw = 0x00000000,
	.usew_ctw_hi_vaw = 0x00000005,
};

static stwuct cwk_awpha_pww video_cc_pww0 = {
	.offset = 0x0,
	.vco_tabwe = wucid_owe_vco,
	.num_vco = AWWAY_SIZE(wucid_owe_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_OWE],
	.cwkw = {
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "video_cc_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_evo_ops,
		},
	},
};

static const stwuct awpha_pww_config video_cc_pww1_config = {
	.w = 0x36,
	.awpha = 0xb000,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00182261,
	.config_ctw_hi1_vaw = 0x82aa299c,
	.test_ctw_vaw = 0x00000000,
	.test_ctw_hi_vaw = 0x00000003,
	.test_ctw_hi1_vaw = 0x00009000,
	.test_ctw_hi2_vaw = 0x00000034,
	.usew_ctw_vaw = 0x00000000,
	.usew_ctw_hi_vaw = 0x00000005,
};

static stwuct cwk_awpha_pww video_cc_pww1 = {
	.offset = 0x1000,
	.vco_tabwe = wucid_owe_vco,
	.num_vco = AWWAY_SIZE(wucid_owe_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID_OWE],
	.cwkw = {
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "video_cc_pww1",
			.pawent_data = &(const stwuct cwk_pawent_data) {
				.index = DT_BI_TCXO,
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_evo_ops,
		},
	},
};

static const stwuct pawent_map video_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_VIDEO_CC_PWW0_OUT_MAIN, 1 },
};

static const stwuct cwk_pawent_data video_cc_pawent_data_0[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &video_cc_pww0.cwkw.hw },
};

static const stwuct pawent_map video_cc_pawent_map_1[] = {
	{ P_BI_TCXO, 0 },
	{ P_VIDEO_CC_PWW1_OUT_MAIN, 1 },
};

static const stwuct cwk_pawent_data video_cc_pawent_data_1[] = {
	{ .index = DT_BI_TCXO },
	{ .hw = &video_cc_pww1.cwkw.hw },
};

static const stwuct fweq_tbw ftbw_video_cc_mvs0_cwk_swc[] = {
	F(720000000, P_VIDEO_CC_PWW0_OUT_MAIN, 1, 0, 0),
	F(1014000000, P_VIDEO_CC_PWW0_OUT_MAIN, 1, 0, 0),
	F(1098000000, P_VIDEO_CC_PWW0_OUT_MAIN, 1, 0, 0),
	F(1332000000, P_VIDEO_CC_PWW0_OUT_MAIN, 1, 0, 0),
	F(1600000000, P_VIDEO_CC_PWW0_OUT_MAIN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 video_cc_mvs0_cwk_swc = {
	.cmd_wcgw = 0x8000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = video_cc_pawent_map_0,
	.fweq_tbw = ftbw_video_cc_mvs0_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "video_cc_mvs0_cwk_swc",
		.pawent_data = video_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(video_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_video_cc_mvs1_cwk_swc[] = {
	F(1050000000, P_VIDEO_CC_PWW1_OUT_MAIN, 1, 0, 0),
	F(1350000000, P_VIDEO_CC_PWW1_OUT_MAIN, 1, 0, 0),
	F(1500000000, P_VIDEO_CC_PWW1_OUT_MAIN, 1, 0, 0),
	F(1650000000, P_VIDEO_CC_PWW1_OUT_MAIN, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 video_cc_mvs1_cwk_swc = {
	.cmd_wcgw = 0x8018,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = video_cc_pawent_map_1,
	.fweq_tbw = ftbw_video_cc_mvs1_cwk_swc,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "video_cc_mvs1_cwk_swc",
		.pawent_data = video_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(video_cc_pawent_data_1),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static stwuct cwk_wegmap_div video_cc_mvs0_div_cwk_swc = {
	.weg = 0x80c4,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "video_cc_mvs0_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&video_cc_mvs0_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_wegmap_div video_cc_mvs0c_div2_div_cwk_swc = {
	.weg = 0x8070,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "video_cc_mvs0c_div2_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&video_cc_mvs0_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_wegmap_div video_cc_mvs1_div_cwk_swc = {
	.weg = 0x80ec,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "video_cc_mvs1_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&video_cc_mvs1_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_wegmap_div video_cc_mvs1c_div2_div_cwk_swc = {
	.weg = 0x809c,
	.shift = 0,
	.width = 4,
	.cwkw.hw.init = &(const stwuct cwk_init_data) {
		.name = "video_cc_mvs1c_div2_div_cwk_swc",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&video_cc_mvs1_cwk_swc.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wegmap_div_wo_ops,
	},
};

static stwuct cwk_bwanch video_cc_mvs0_cwk = {
	.hawt_weg = 0x80b8,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x80b8,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x80b8,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "video_cc_mvs0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&video_cc_mvs0_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_mvs0c_cwk = {
	.hawt_weg = 0x8064,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8064,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "video_cc_mvs0c_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&video_cc_mvs0c_div2_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_mvs1_cwk = {
	.hawt_weg = 0x80e0,
	.hawt_check = BWANCH_HAWT_SKIP,
	.hwcg_weg = 0x80e0,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x80e0,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "video_cc_mvs1_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&video_cc_mvs1_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_mvs1c_cwk = {
	.hawt_weg = 0x8090,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8090,
		.enabwe_mask = BIT(0),
		.hw.init = &(const stwuct cwk_init_data) {
			.name = "video_cc_mvs1c_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&video_cc_mvs1c_div2_div_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc video_cc_mvs0c_gdsc = {
	.gdscw = 0x804c,
	.en_west_wait_vaw = 0x2,
	.en_few_wait_vaw = 0x2,
	.cwk_dis_wait_vaw = 0x6,
	.pd = {
		.name = "video_cc_mvs0c_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = POWW_CFG_GDSCW | WETAIN_FF_ENABWE,
};

static stwuct gdsc video_cc_mvs0_gdsc = {
	.gdscw = 0x80a4,
	.en_west_wait_vaw = 0x2,
	.en_few_wait_vaw = 0x2,
	.cwk_dis_wait_vaw = 0x6,
	.pd = {
		.name = "video_cc_mvs0_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.pawent = &video_cc_mvs0c_gdsc.pd,
	.fwags = POWW_CFG_GDSCW | WETAIN_FF_ENABWE | HW_CTWW,
};

static stwuct gdsc video_cc_mvs1c_gdsc = {
	.gdscw = 0x8078,
	.en_west_wait_vaw = 0x2,
	.en_few_wait_vaw = 0x2,
	.cwk_dis_wait_vaw = 0x6,
	.pd = {
		.name = "video_cc_mvs1c_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = POWW_CFG_GDSCW | WETAIN_FF_ENABWE,
};

static stwuct gdsc video_cc_mvs1_gdsc = {
	.gdscw = 0x80cc,
	.en_west_wait_vaw = 0x2,
	.en_few_wait_vaw = 0x2,
	.cwk_dis_wait_vaw = 0x6,
	.pd = {
		.name = "video_cc_mvs1_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.pawent = &video_cc_mvs1c_gdsc.pd,
	.fwags = POWW_CFG_GDSCW | WETAIN_FF_ENABWE | HW_CTWW,
};

static stwuct cwk_wegmap *video_cc_sm8550_cwocks[] = {
	[VIDEO_CC_MVS0_CWK] = &video_cc_mvs0_cwk.cwkw,
	[VIDEO_CC_MVS0_CWK_SWC] = &video_cc_mvs0_cwk_swc.cwkw,
	[VIDEO_CC_MVS0_DIV_CWK_SWC] = &video_cc_mvs0_div_cwk_swc.cwkw,
	[VIDEO_CC_MVS0C_CWK] = &video_cc_mvs0c_cwk.cwkw,
	[VIDEO_CC_MVS0C_DIV2_DIV_CWK_SWC] = &video_cc_mvs0c_div2_div_cwk_swc.cwkw,
	[VIDEO_CC_MVS1_CWK] = &video_cc_mvs1_cwk.cwkw,
	[VIDEO_CC_MVS1_CWK_SWC] = &video_cc_mvs1_cwk_swc.cwkw,
	[VIDEO_CC_MVS1_DIV_CWK_SWC] = &video_cc_mvs1_div_cwk_swc.cwkw,
	[VIDEO_CC_MVS1C_CWK] = &video_cc_mvs1c_cwk.cwkw,
	[VIDEO_CC_MVS1C_DIV2_DIV_CWK_SWC] = &video_cc_mvs1c_div2_div_cwk_swc.cwkw,
	[VIDEO_CC_PWW0] = &video_cc_pww0.cwkw,
	[VIDEO_CC_PWW1] = &video_cc_pww1.cwkw,
};

static stwuct gdsc *video_cc_sm8550_gdscs[] = {
	[VIDEO_CC_MVS0C_GDSC] = &video_cc_mvs0c_gdsc,
	[VIDEO_CC_MVS0_GDSC] = &video_cc_mvs0_gdsc,
	[VIDEO_CC_MVS1C_GDSC] = &video_cc_mvs1c_gdsc,
	[VIDEO_CC_MVS1_GDSC] = &video_cc_mvs1_gdsc,
};

static const stwuct qcom_weset_map video_cc_sm8550_wesets[] = {
	[CVP_VIDEO_CC_INTEWFACE_BCW] = { 0x80f0 },
	[CVP_VIDEO_CC_MVS0_BCW] = { 0x80a0 },
	[CVP_VIDEO_CC_MVS0C_BCW] = { 0x8048 },
	[CVP_VIDEO_CC_MVS1_BCW] = { 0x80c8 },
	[CVP_VIDEO_CC_MVS1C_BCW] = { 0x8074 },
	[VIDEO_CC_MVS0C_CWK_AWES] = { 0x8064, 2 },
	[VIDEO_CC_MVS1C_CWK_AWES] = { 0x8090, 2 },
};

static const stwuct wegmap_config video_cc_sm8550_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0x9f4c,
	.fast_io = twue,
};

static stwuct qcom_cc_desc video_cc_sm8550_desc = {
	.config = &video_cc_sm8550_wegmap_config,
	.cwks = video_cc_sm8550_cwocks,
	.num_cwks = AWWAY_SIZE(video_cc_sm8550_cwocks),
	.wesets = video_cc_sm8550_wesets,
	.num_wesets = AWWAY_SIZE(video_cc_sm8550_wesets),
	.gdscs = video_cc_sm8550_gdscs,
	.num_gdscs = AWWAY_SIZE(video_cc_sm8550_gdscs),
};

static const stwuct of_device_id video_cc_sm8550_match_tabwe[] = {
	{ .compatibwe = "qcom,sm8550-videocc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, video_cc_sm8550_match_tabwe);

static int video_cc_sm8550_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	int wet;

	wet = devm_pm_wuntime_enabwe(&pdev->dev);
	if (wet)
		wetuwn wet;

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet)
		wetuwn wet;

	wegmap = qcom_cc_map(pdev, &video_cc_sm8550_desc);
	if (IS_EWW(wegmap)) {
		pm_wuntime_put(&pdev->dev);
		wetuwn PTW_EWW(wegmap);
	}

	cwk_wucid_owe_pww_configuwe(&video_cc_pww0, wegmap, &video_cc_pww0_config);
	cwk_wucid_owe_pww_configuwe(&video_cc_pww1, wegmap, &video_cc_pww1_config);

	/*
	 * Keep cwocks awways enabwed:
	 *	video_cc_ahb_cwk
	 *	video_cc_sweep_cwk
	 *	video_cc_xo_cwk
	 */
	wegmap_update_bits(wegmap, 0x80f4, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x8140, BIT(0), BIT(0));
	wegmap_update_bits(wegmap, 0x8124, BIT(0), BIT(0));

	wet = qcom_cc_weawwy_pwobe(pdev, &video_cc_sm8550_desc, wegmap);

	pm_wuntime_put(&pdev->dev);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew video_cc_sm8550_dwivew = {
	.pwobe = video_cc_sm8550_pwobe,
	.dwivew = {
		.name = "video_cc-sm8550",
		.of_match_tabwe = video_cc_sm8550_match_tabwe,
	},
};

static int __init video_cc_sm8550_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&video_cc_sm8550_dwivew);
}
subsys_initcaww(video_cc_sm8550_init);

static void __exit video_cc_sm8550_exit(void)
{
	pwatfowm_dwivew_unwegistew(&video_cc_sm8550_dwivew);
}
moduwe_exit(video_cc_sm8550_exit);

MODUWE_DESCWIPTION("QTI VIDEOCC SM8550 Dwivew");
MODUWE_WICENSE("GPW");
