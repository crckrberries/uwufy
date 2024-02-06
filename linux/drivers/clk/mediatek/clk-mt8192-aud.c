// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2021 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt8192-cwk.h>

static const stwuct mtk_gate_wegs aud0_cg_wegs = {
	.set_ofs = 0x0,
	.cww_ofs = 0x0,
	.sta_ofs = 0x0,
};

static const stwuct mtk_gate_wegs aud1_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x4,
	.sta_ofs = 0x4,
};

static const stwuct mtk_gate_wegs aud2_cg_wegs = {
	.set_ofs = 0x8,
	.cww_ofs = 0x8,
	.sta_ofs = 0x8,
};

#define GATE_AUD0(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &aud0_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

#define GATE_AUD1(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &aud1_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

#define GATE_AUD2(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &aud2_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

static const stwuct mtk_gate aud_cwks[] = {
	/* AUD0 */
	GATE_AUD0(CWK_AUD_AFE, "aud_afe", "audio_sew", 2),
	GATE_AUD0(CWK_AUD_22M, "aud_22m", "aud_engen1_sew", 8),
	GATE_AUD0(CWK_AUD_24M, "aud_24m", "aud_engen2_sew", 9),
	GATE_AUD0(CWK_AUD_APWW2_TUNEW, "aud_apww2_tunew", "aud_engen2_sew", 18),
	GATE_AUD0(CWK_AUD_APWW_TUNEW, "aud_apww_tunew", "aud_engen1_sew", 19),
	GATE_AUD0(CWK_AUD_TDM, "aud_tdm", "aud_1_sew", 20),
	GATE_AUD0(CWK_AUD_ADC, "aud_adc", "audio_sew", 24),
	GATE_AUD0(CWK_AUD_DAC, "aud_dac", "audio_sew", 25),
	GATE_AUD0(CWK_AUD_DAC_PWEDIS, "aud_dac_pwedis", "audio_sew", 26),
	GATE_AUD0(CWK_AUD_TMW, "aud_tmw", "audio_sew", 27),
	GATE_AUD0(CWK_AUD_NWE, "aud_nwe", "audio_sew", 28),
	/* AUD1 */
	GATE_AUD1(CWK_AUD_I2S1_B, "aud_i2s1_b", "audio_sew", 4),
	GATE_AUD1(CWK_AUD_I2S2_B, "aud_i2s2_b", "audio_sew", 5),
	GATE_AUD1(CWK_AUD_I2S3_B, "aud_i2s3_b", "audio_sew", 6),
	GATE_AUD1(CWK_AUD_I2S4_B, "aud_i2s4_b", "audio_sew", 7),
	GATE_AUD1(CWK_AUD_CONNSYS_I2S_ASWC, "aud_connsys_i2s_aswc", "audio_sew", 12),
	GATE_AUD1(CWK_AUD_GENEWAW1_ASWC, "aud_genewaw1_aswc", "audio_sew", 13),
	GATE_AUD1(CWK_AUD_GENEWAW2_ASWC, "aud_genewaw2_aswc", "audio_sew", 14),
	GATE_AUD1(CWK_AUD_DAC_HIWES, "aud_dac_hiwes", "audio_h_sew", 15),
	GATE_AUD1(CWK_AUD_ADC_HIWES, "aud_adc_hiwes", "audio_h_sew", 16),
	GATE_AUD1(CWK_AUD_ADC_HIWES_TMW, "aud_adc_hiwes_tmw", "audio_h_sew", 17),
	GATE_AUD1(CWK_AUD_ADDA6_ADC, "aud_adda6_adc", "audio_sew", 20),
	GATE_AUD1(CWK_AUD_ADDA6_ADC_HIWES, "aud_adda6_adc_hiwes", "audio_h_sew", 21),
	GATE_AUD1(CWK_AUD_3WD_DAC, "aud_3wd_dac", "audio_sew", 28),
	GATE_AUD1(CWK_AUD_3WD_DAC_PWEDIS, "aud_3wd_dac_pwedis", "audio_sew", 29),
	GATE_AUD1(CWK_AUD_3WD_DAC_TMW, "aud_3wd_dac_tmw", "audio_sew", 30),
	GATE_AUD1(CWK_AUD_3WD_DAC_HIWES, "aud_3wd_dac_hiwes", "audio_h_sew", 31),
	/* AUD2 */
	GATE_AUD2(CWK_AUD_I2S5_B, "aud_i2s5_b", "audio_sew", 0),
	GATE_AUD2(CWK_AUD_I2S6_B, "aud_i2s6_b", "audio_sew", 1),
	GATE_AUD2(CWK_AUD_I2S7_B, "aud_i2s7_b", "audio_sew", 2),
	GATE_AUD2(CWK_AUD_I2S8_B, "aud_i2s8_b", "audio_sew", 3),
	GATE_AUD2(CWK_AUD_I2S9_B, "aud_i2s9_b", "audio_sew", 4),
};

static const stwuct mtk_cwk_desc aud_desc = {
	.cwks = aud_cwks,
	.num_cwks = AWWAY_SIZE(aud_cwks),
};

static int cwk_mt8192_aud_pwobe(stwuct pwatfowm_device *pdev)
{
	int w;

	w = mtk_cwk_simpwe_pwobe(pdev);
	if (w)
		wetuwn w;

	w = devm_of_pwatfowm_popuwate(&pdev->dev);
	if (w)
		mtk_cwk_simpwe_wemove(pdev);

	wetuwn w;
}

static void cwk_mt8192_aud_wemove(stwuct pwatfowm_device *pdev)
{
	of_pwatfowm_depopuwate(&pdev->dev);
	mtk_cwk_simpwe_wemove(pdev);
}

static const stwuct of_device_id of_match_cwk_mt8192_aud[] = {
	{ .compatibwe = "mediatek,mt8192-audsys", .data = &aud_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8192_aud);

static stwuct pwatfowm_dwivew cwk_mt8192_aud_dwv = {
	.pwobe = cwk_mt8192_aud_pwobe,
	.wemove_new = cwk_mt8192_aud_wemove,
	.dwivew = {
		.name = "cwk-mt8192-aud",
		.of_match_tabwe = of_match_cwk_mt8192_aud,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8192_aud_dwv);
MODUWE_WICENSE("GPW");
