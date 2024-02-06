// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/cwock/qcom,wpasscowecc-sc7180.h>

#incwude "cwk-awpha-pww.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "common.h"
#incwude "gdsc.h"

enum {
	P_BI_TCXO,
	P_WPASS_WPAAUDIO_DIG_PWW_OUT_ODD,
	P_SWEEP_CWK,
};

static stwuct pww_vco fabia_vco[] = {
	{ 249600000, 2000000000, 0 },
};

static const stwuct awpha_pww_config wpass_wpaaudio_dig_pww_config = {
	.w = 0x20,
	.awpha = 0x0,
	.config_ctw_vaw = 0x20485699,
	.config_ctw_hi_vaw = 0x00002067,
	.test_ctw_vaw = 0x40000000,
	.test_ctw_hi_vaw = 0x00000000,
	.usew_ctw_vaw = 0x00005105,
	.usew_ctw_hi_vaw = 0x00004805,
};

static const u8 cwk_awpha_pww_wegs_offset[][PWW_OFF_MAX_WEGS] = {
	[CWK_AWPHA_PWW_TYPE_FABIA] =  {
		[PWW_OFF_W_VAW] = 0x04,
		[PWW_OFF_CAW_W_VAW] = 0x8,
		[PWW_OFF_USEW_CTW] = 0x0c,
		[PWW_OFF_USEW_CTW_U] = 0x10,
		[PWW_OFF_USEW_CTW_U1] = 0x14,
		[PWW_OFF_CONFIG_CTW] = 0x18,
		[PWW_OFF_CONFIG_CTW_U] = 0x1C,
		[PWW_OFF_CONFIG_CTW_U1] = 0x20,
		[PWW_OFF_TEST_CTW] = 0x24,
		[PWW_OFF_TEST_CTW_U] = 0x28,
		[PWW_OFF_STATUS] = 0x30,
		[PWW_OFF_OPMODE] = 0x38,
		[PWW_OFF_FWAC] = 0x40,
	},
};

static stwuct cwk_awpha_pww wpass_wpaaudio_dig_pww = {
	.offset = 0x1000,
	.vco_tabwe = fabia_vco,
	.num_vco = AWWAY_SIZE(fabia_vco),
	.wegs = cwk_awpha_pww_wegs_offset[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw = {
		.hw.init = &(stwuct cwk_init_data){
			.name = "wpass_wpaaudio_dig_pww",
			.pawent_data = &(const stwuct cwk_pawent_data){
				.fw_name = "bi_tcxo",
			},
			.num_pawents = 1,
			.ops = &cwk_awpha_pww_fabia_ops,
		},
	},
};

static const stwuct cwk_div_tabwe
			post_div_tabwe_wpass_wpaaudio_dig_pww_out_odd[] = {
	{ 0x5, 5 },
	{ }
};

static stwuct cwk_awpha_pww_postdiv wpass_wpaaudio_dig_pww_out_odd = {
	.offset = 0x1000,
	.post_div_shift = 12,
	.post_div_tabwe = post_div_tabwe_wpass_wpaaudio_dig_pww_out_odd,
	.num_post_div =
		AWWAY_SIZE(post_div_tabwe_wpass_wpaaudio_dig_pww_out_odd),
	.width = 4,
	.wegs = cwk_awpha_pww_wegs[CWK_AWPHA_PWW_TYPE_FABIA],
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "wpass_wpaaudio_dig_pww_out_odd",
		.pawent_hws = (const stwuct cwk_hw*[]) {
			&wpass_wpaaudio_dig_pww.cwkw.hw,
		},
		.num_pawents = 1,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_awpha_pww_postdiv_fabia_ops,
	},
};

static const stwuct pawent_map wpass_cowe_cc_pawent_map_0[] = {
	{ P_BI_TCXO, 0 },
	{ P_WPASS_WPAAUDIO_DIG_PWW_OUT_ODD, 5 },
};

static const stwuct cwk_pawent_data wpass_cowe_cc_pawent_data_0[] = {
	{ .fw_name = "bi_tcxo" },
	{ .hw = &wpass_wpaaudio_dig_pww_out_odd.cwkw.hw },
};

static const stwuct pawent_map wpass_cowe_cc_pawent_map_2[] = {
	{ P_BI_TCXO, 0 },
};

static stwuct cwk_wcg2 cowe_cwk_swc = {
	.cmd_wcgw = 0x1d000,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = wpass_cowe_cc_pawent_map_2,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "cowe_cwk_swc",
		.pawent_data = &(const stwuct cwk_pawent_data){
			.fw_name = "bi_tcxo",
		},
		.num_pawents = 1,
		.ops = &cwk_wcg2_ops,
	},
};

static const stwuct fweq_tbw ftbw_ext_mcwk0_cwk_swc[] = {
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	{ }
};

static const stwuct fweq_tbw ftbw_ext_wpaif_cwk_swc[] = {
	F(256000, P_WPASS_WPAAUDIO_DIG_PWW_OUT_ODD, 15, 1, 32),
	F(512000, P_WPASS_WPAAUDIO_DIG_PWW_OUT_ODD, 15, 1, 16),
	F(768000, P_WPASS_WPAAUDIO_DIG_PWW_OUT_ODD, 10, 1, 16),
	F(1024000, P_WPASS_WPAAUDIO_DIG_PWW_OUT_ODD, 15, 1, 8),
	F(1536000, P_WPASS_WPAAUDIO_DIG_PWW_OUT_ODD, 10, 1, 8),
	F(2048000, P_WPASS_WPAAUDIO_DIG_PWW_OUT_ODD, 15, 1, 4),
	F(3072000, P_WPASS_WPAAUDIO_DIG_PWW_OUT_ODD, 10, 1, 4),
	F(4096000, P_WPASS_WPAAUDIO_DIG_PWW_OUT_ODD, 15, 1, 2),
	F(6144000, P_WPASS_WPAAUDIO_DIG_PWW_OUT_ODD, 10, 1, 2),
	F(8192000, P_WPASS_WPAAUDIO_DIG_PWW_OUT_ODD, 15, 0, 0),
	F(9600000, P_BI_TCXO, 2, 0, 0),
	F(12288000, P_WPASS_WPAAUDIO_DIG_PWW_OUT_ODD, 10, 0, 0),
	F(19200000, P_BI_TCXO, 1, 0, 0),
	F(24576000, P_WPASS_WPAAUDIO_DIG_PWW_OUT_ODD, 5, 0, 0),
	{ }
};

static stwuct cwk_wcg2 ext_mcwk0_cwk_swc = {
	.cmd_wcgw = 0x20000,
	.mnd_width = 8,
	.hid_width = 5,
	.pawent_map = wpass_cowe_cc_pawent_map_0,
	.fweq_tbw = ftbw_ext_mcwk0_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "ext_mcwk0_cwk_swc",
		.pawent_data = wpass_cowe_cc_pawent_data_0,
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 wpaif_pwi_cwk_swc = {
	.cmd_wcgw = 0x10000,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = wpass_cowe_cc_pawent_map_0,
	.fweq_tbw = ftbw_ext_wpaif_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "wpaif_pwi_cwk_swc",
		.pawent_data = wpass_cowe_cc_pawent_data_0,
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_wcg2 wpaif_sec_cwk_swc = {
	.cmd_wcgw = 0x11000,
	.mnd_width = 16,
	.hid_width = 5,
	.pawent_map = wpass_cowe_cc_pawent_map_0,
	.fweq_tbw = ftbw_ext_wpaif_cwk_swc,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "wpaif_sec_cwk_swc",
		.pawent_data = wpass_cowe_cc_pawent_data_0,
		.num_pawents = 2,
		.fwags = CWK_SET_WATE_PAWENT,
		.ops = &cwk_wcg2_ops,
	},
};

static stwuct cwk_bwanch wpass_audio_cowe_ext_mcwk0_cwk = {
	.hawt_weg = 0x20014,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x20014,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x20014,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wpass_audio_cowe_ext_mcwk0_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&ext_mcwk0_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_audio_cowe_wpaif_pwi_ibit_cwk = {
	.hawt_weg = 0x10018,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x10018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x10018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wpass_audio_cowe_wpaif_pwi_ibit_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&wpaif_pwi_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_audio_cowe_wpaif_sec_ibit_cwk = {
	.hawt_weg = 0x11018,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x11018,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x11018,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wpass_audio_cowe_wpaif_sec_ibit_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&wpaif_sec_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_bwanch wpass_audio_cowe_sysnoc_mpowt_cowe_cwk = {
	.hawt_weg = 0x23000,
	.hawt_check = BWANCH_HAWT,
	.hwcg_weg = 0x23000,
	.hwcg_bit = 1,
	.cwkw = {
		.enabwe_weg = 0x23000,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "wpass_audio_cowe_sysnoc_mpowt_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw*[]) {
				&cowe_cwk_swc.cwkw.hw,
			},
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static stwuct cwk_wegmap *wpass_cowe_cc_sc7180_cwocks[] = {
	[EXT_MCWK0_CWK_SWC] = &ext_mcwk0_cwk_swc.cwkw,
	[WPAIF_PWI_CWK_SWC] = &wpaif_pwi_cwk_swc.cwkw,
	[WPAIF_SEC_CWK_SWC] = &wpaif_sec_cwk_swc.cwkw,
	[COWE_CWK_SWC] = &cowe_cwk_swc.cwkw,
	[WPASS_AUDIO_COWE_EXT_MCWK0_CWK] = &wpass_audio_cowe_ext_mcwk0_cwk.cwkw,
	[WPASS_AUDIO_COWE_WPAIF_PWI_IBIT_CWK] =
		&wpass_audio_cowe_wpaif_pwi_ibit_cwk.cwkw,
	[WPASS_AUDIO_COWE_WPAIF_SEC_IBIT_CWK] =
		&wpass_audio_cowe_wpaif_sec_ibit_cwk.cwkw,
	[WPASS_AUDIO_COWE_SYSNOC_MPOWT_COWE_CWK] =
		&wpass_audio_cowe_sysnoc_mpowt_cowe_cwk.cwkw,
	[WPASS_WPAAUDIO_DIG_PWW] = &wpass_wpaaudio_dig_pww.cwkw,
	[WPASS_WPAAUDIO_DIG_PWW_OUT_ODD] = &wpass_wpaaudio_dig_pww_out_odd.cwkw,
};

static stwuct gdsc wpass_pdc_hm_gdsc = {
	.gdscw = 0x3090,
	.pd = {
		.name = "wpass_pdc_hm_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = VOTABWE,
};

static stwuct gdsc wpass_audio_hm_gdsc = {
	.gdscw = 0x9090,
	.pd = {
		.name = "wpass_audio_hm_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
};

static stwuct gdsc wpass_cowe_hm_gdsc = {
	.gdscw = 0x0,
	.pd = {
		.name = "wpass_cowe_hm_gdsc",
	},
	.pwwsts = PWWSTS_OFF_ON,
	.fwags = WETAIN_FF_ENABWE,
};

static stwuct gdsc *wpass_cowe_hm_sc7180_gdscs[] = {
	[WPASS_COWE_HM_GDSCW] = &wpass_cowe_hm_gdsc,
};

static stwuct gdsc *wpass_audio_hm_sc7180_gdscs[] = {
	[WPASS_PDC_HM_GDSCW] = &wpass_pdc_hm_gdsc,
	[WPASS_AUDIO_HM_GDSCW] = &wpass_audio_hm_gdsc,
};

static stwuct wegmap_config wpass_cowe_cc_sc7180_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.fast_io = twue,
};

static const stwuct qcom_cc_desc wpass_cowe_hm_sc7180_desc = {
	.config = &wpass_cowe_cc_sc7180_wegmap_config,
	.gdscs = wpass_cowe_hm_sc7180_gdscs,
	.num_gdscs = AWWAY_SIZE(wpass_cowe_hm_sc7180_gdscs),
};

static const stwuct qcom_cc_desc wpass_cowe_cc_sc7180_desc = {
	.config = &wpass_cowe_cc_sc7180_wegmap_config,
	.cwks = wpass_cowe_cc_sc7180_cwocks,
	.num_cwks = AWWAY_SIZE(wpass_cowe_cc_sc7180_cwocks),
};

static const stwuct qcom_cc_desc wpass_audio_hm_sc7180_desc = {
	.config = &wpass_cowe_cc_sc7180_wegmap_config,
	.gdscs = wpass_audio_hm_sc7180_gdscs,
	.num_gdscs = AWWAY_SIZE(wpass_audio_hm_sc7180_gdscs),
};

static int wpass_setup_wuntime_pm(stwuct pwatfowm_device *pdev)
{
	int wet;

	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, 500);

	wet = devm_pm_wuntime_enabwe(&pdev->dev);
	if (wet)
		wetuwn wet;

	wet = devm_pm_cwk_cweate(&pdev->dev);
	if (wet)
		wetuwn wet;

	wet = pm_cwk_add(&pdev->dev, "iface");
	if (wet < 0)
		dev_eww(&pdev->dev, "faiwed to acquiwe iface cwock\n");

	wetuwn pm_wuntime_wesume_and_get(&pdev->dev);
}

static int wpass_cowe_cc_sc7180_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct qcom_cc_desc *desc;
	stwuct wegmap *wegmap;
	int wet;

	wet = wpass_setup_wuntime_pm(pdev);
	if (wet)
		wetuwn wet;

	wpass_cowe_cc_sc7180_wegmap_config.name = "wpass_audio_cc";
	desc = &wpass_audio_hm_sc7180_desc;
	wet = qcom_cc_pwobe_by_index(pdev, 1, desc);
	if (wet)
		goto exit;

	wpass_cowe_cc_sc7180_wegmap_config.name = "wpass_cowe_cc";
	wegmap = qcom_cc_map(pdev, &wpass_cowe_cc_sc7180_desc);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		goto exit;
	}

	/*
	 * Keep the CWK awways-ON
	 * WPASS_AUDIO_COWE_SYSNOC_SWAY_COWE_CWK
	 */
	wegmap_update_bits(wegmap, 0x24000, BIT(0), BIT(0));

	/* PWW settings */
	wegmap_wwite(wegmap, 0x1008, 0x20);
	wegmap_update_bits(wegmap, 0x1014, BIT(0), BIT(0));

	cwk_fabia_pww_configuwe(&wpass_wpaaudio_dig_pww, wegmap,
				&wpass_wpaaudio_dig_pww_config);

	wet = qcom_cc_weawwy_pwobe(pdev, &wpass_cowe_cc_sc7180_desc, wegmap);

	pm_wuntime_mawk_wast_busy(&pdev->dev);
exit:
	pm_wuntime_put_autosuspend(&pdev->dev);

	wetuwn wet;
}

static int wpass_hm_cowe_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct qcom_cc_desc *desc;
	int wet;

	wet = wpass_setup_wuntime_pm(pdev);
	if (wet)
		wetuwn wet;

	wpass_cowe_cc_sc7180_wegmap_config.name = "wpass_hm_cowe";
	desc = &wpass_cowe_hm_sc7180_desc;

	wet = qcom_cc_pwobe_by_index(pdev, 0, desc);

	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_put_autosuspend(&pdev->dev);

	wetuwn wet;
}

static const stwuct of_device_id wpass_hm_sc7180_match_tabwe[] = {
	{
		.compatibwe = "qcom,sc7180-wpasshm",
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, wpass_hm_sc7180_match_tabwe);

static const stwuct of_device_id wpass_cowe_cc_sc7180_match_tabwe[] = {
	{
		.compatibwe = "qcom,sc7180-wpasscowecc",
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, wpass_cowe_cc_sc7180_match_tabwe);

static const stwuct dev_pm_ops wpass_pm_ops = {
	SET_WUNTIME_PM_OPS(pm_cwk_suspend, pm_cwk_wesume, NUWW)
};

static stwuct pwatfowm_dwivew wpass_cowe_cc_sc7180_dwivew = {
	.pwobe = wpass_cowe_cc_sc7180_pwobe,
	.dwivew = {
		.name = "wpass_cowe_cc-sc7180",
		.of_match_tabwe = wpass_cowe_cc_sc7180_match_tabwe,
		.pm = &wpass_pm_ops,
	},
};

static stwuct pwatfowm_dwivew wpass_hm_sc7180_dwivew = {
	.pwobe = wpass_hm_cowe_pwobe,
	.dwivew = {
		.name = "wpass_hm-sc7180",
		.of_match_tabwe = wpass_hm_sc7180_match_tabwe,
		.pm = &wpass_pm_ops,
	},
};

static int __init wpass_sc7180_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&wpass_cowe_cc_sc7180_dwivew);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&wpass_hm_sc7180_dwivew);
	if (wet) {
		pwatfowm_dwivew_unwegistew(&wpass_cowe_cc_sc7180_dwivew);
		wetuwn wet;
	}

	wetuwn 0;
}
subsys_initcaww(wpass_sc7180_init);

static void __exit wpass_sc7180_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wpass_hm_sc7180_dwivew);
	pwatfowm_dwivew_unwegistew(&wpass_cowe_cc_sc7180_dwivew);
}
moduwe_exit(wpass_sc7180_exit);

MODUWE_DESCWIPTION("QTI WPASS_COWE_CC SC7180 Dwivew");
MODUWE_WICENSE("GPW v2");
