// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,videocc-sc7280.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "common.h"
#incwude "weset.h"
#incwude "gdsc.h"

enum {
	P_BI_TCXO,
	P_SWEEP_CWK,
	P_VIDEO_PWW0_OUT_EVEN,
};

static const stwuct pww_vco wucid_vco[] = {
	{ 249600000, 2000000000, 0 },
};

/* 400MHz Configuwation */
static const stwuct awpha_pww_config video_pww0_config = {
	.w = 0x14,
	.awpha = 0xD555,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002261,
	.config_ctw_hi1_vaw = 0x329A299C,
	.usew_ctw_vaw = 0x00000001,
	.usew_ctw_hi_vaw = 0x00000805,
	.usew_ctw_hi1_vaw = 0x00000000,
};

static stwuct cwk_awpha_pww video_pww0 = {
	.offset = 0x0,
	.vco_tabwe = wucid_vco,
	.num_vco = AWWAY_SIZE(wucid_vco),
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_WUCID],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_pww0",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_wucid_ops,
		},
	},
};

static const stwuct pawent_map video_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_VIDEO_PWW0_OUT_EVEN, 3 },
};

static const stwuct cwk_pawent_data video_cc_pawent_data_0[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &video_pww0.cwkw.hw },
};

static const stwuct pawent_map video_cc_pawent_map_1[] = {
	{ P_SWEEP_CWK, 0 },
};

static const stwuct cwk_pawent_data video_cc_pawent_data_1[] = {
	{ .fw_name = "sweep_cwk" },
};

static const stwuct fweq_tbw ftbw_video_cc_iwis_cwk_swc[] = {
	F(133333333, P_VIDEO_PWW0_OUT_EVEN, 3, 0, 0),
	F(240000000, P_VIDEO_PWW0_OUT_EVEN, 2, 0, 0),
	F(335000000, P_VIDEO_PWW0_OUT_EVEN, 2, 0, 0),
	F(424000000, P_VIDEO_PWW0_OUT_EVEN, 2, 0, 0),
	F(460000000, P_VIDEO_PWW0_OUT_EVEN, 2, 0, 0),
	{ }
};

static stwuct cwk_wcg2 video_cc_iwis_cwk_swc = {
	.cmd_wcgw = 0x1000,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = video_cc_pawent_map_0,
	.fweq_tbw = ftbw_video_cc_iwis_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "video_cc_iwis_cwk_swc",
		.pawent_data = video_cc_pawent_data_0,
		.num_pawents = AWWAY_SIZE(video_cc_pawent_data_0),
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_shawed_ops,
	},
};

static const stwuct fweq_tbw ftbw_video_cc_sweep_cwk_swc[] = {
	F(32000, P_SWEEP_CWK, 1, 0, 0),
	{ }
};

static stwuct cwk_wcg2 video_cc_sweep_cwk_swc = {
	.cmd_wcgw = 0x701c,
	.mnd_width = 0,
	.hid_width = 5,
	.pawent_map = video_cc_pawent_map_1,
	.fweq_tbw = ftbw_video_cc_sweep_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "video_cc_sweep_cwk_swc",
		.pawent_data = video_cc_pawent_data_1,
		.num_pawents = AWWAY_SIZE(video_cc_pawent_data_1),
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch video_cc_iwis_ahb_cwk = {
	.hawt_weg = 0x5004,
	.hawt_check = BWANCH_HAWT_VOTED,
	.cwkw = {
		.enabwe_weg = 0x5004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_iwis_ahb_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&video_cc_iwis_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_mvs0_axi_cwk = {
	.hawt_weg = 0x800c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x800c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_mvs0_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_mvs0_cowe_cwk = {
	.hawt_weg = 0x3010,
	.hawt_check = BWANCH_HAWT_VOTED,
	.hwcg_weg = 0x3010,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x3010,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_mvs0_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&video_cc_iwis_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_mvsc_cowe_cwk = {
	.hawt_weg = 0x2014,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x2014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_mvsc_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&video_cc_iwis_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_mvsc_ctw_axi_cwk = {
	.hawt_weg = 0x8004,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x8004,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_mvsc_ctw_axi_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_sweep_cwk = {
	.hawt_weg = 0x7034,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x7034,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_sweep_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]){
				&video_cc_sweep_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch video_cc_venus_ahb_cwk = {
	.hawt_weg = 0x801c,
	.hawt_check = BWANCH_HAWT,
	.cwkw = {
		.enabwe_weg = 0x801c,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "video_cc_venus_ahb_cwk",
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct gdsc mvs0_gdsc = {
	.gdscw = 0x3004,
	.pd = {
		.name = "mvs0_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = HW_CTWW | WETAIN_FF_ENABWE,
};

static stwuct gdsc mvsc_gdsc = {
	.gdscw = 0x2004,
	.pd = {
		.name = "mvsc_gdsc",
	},
	.fwags = WETAIN_FF_ENABWE,
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct cwk_wegmap *video_cc_sc7280_cwocks[] = {
	[VIDEO_CC_IWIS_AHB_CWK] = &video_cc_iwis_ahb_cwk.cwkw,
	[VIDEO_CC_IWIS_CWK_SWC] = &video_cc_iwis_cwk_swc.cwkw,
	[VIDEO_CC_MVS0_AXI_CWK] = &video_cc_mvs0_axi_cwk.cwkw,
	[VIDEO_CC_MVS0_COWE_CWK] = &video_cc_mvs0_cowe_cwk.cwkw,
	[VIDEO_CC_MVSC_COWE_CWK] = &video_cc_mvsc_cowe_cwk.cwkw,
	[VIDEO_CC_MVSC_CTW_AXI_CWK] = &video_cc_mvsc_ctw_axi_cwk.cwkw,
	[VIDEO_CC_SWEEP_CWK] = &video_cc_sweep_cwk.cwkw,
	[VIDEO_CC_SWEEP_CWK_SWC] = &video_cc_sweep_cwk_swc.cwkw,
	[VIDEO_CC_VENUS_AHB_CWK] = &video_cc_venus_ahb_cwk.cwkw,
	[VIDEO_PWW0] = &video_pww0.cwkw,
};

static stwuct gdsc *video_cc_sc7280_gdscs[] = {
	[MVS0_GDSC] = &mvs0_gdsc,
	[MVSC_GDSC] = &mvsc_gdsc,
};

static const stwuct wegmap_config video_cc_sc7280_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0xb000,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc video_cc_sc7280_desc = {
	.config = &video_cc_sc7280_wegmap_config,
	.cwks = video_cc_sc7280_cwocks,
	.num_cwks = AWWAY_SIZE(video_cc_sc7280_cwocks),
	.gdscs = video_cc_sc7280_gdscs,
	.num_gdscs = AWWAY_SIZE(video_cc_sc7280_gdscs),
};

static const stwuct of_device_id video_cc_sc7280_match_tabwe[] = {
	{ .compatibwe = "qcom,sc7280-videocc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, video_cc_sc7280_match_tabwe);

static int video_cc_sc7280_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, &video_cc_sc7280_desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	cwk_wucid_pww_configuwe(&video_pww0, wegmap, &video_pww0_config);

	wetuwn qcom_cc_weawwy_pwobe(pdev, &video_cc_sc7280_desc, wegmap);
}

static stwuct pwatfowm_dwivew video_cc_sc7280_dwivew = {
	.pwobe = video_cc_sc7280_pwobe,
	.dwivew = {
		.name = "video_cc-sc7280",
		.of_match_tabwe = video_cc_sc7280_match_tabwe,
	},
};

static int __init video_cc_sc7280_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&video_cc_sc7280_dwivew);
}
subsys_initcaww(video_cc_sc7280_init);

static void __exit video_cc_sc7280_exit(void)
{
	pwatfowm_dwivew_unwegistew(&video_cc_sc7280_dwivew);
}
moduwe_exit(video_cc_sc7280_exit);

MODUWE_DESCWIPTION("QTI VIDEO_CC sc7280 Dwivew");
MODUWE_WICENSE("GPW v2");
