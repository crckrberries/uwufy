// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2018 MediaTek Inc.
// Authow: Weiyi Wu <weiyi.wu@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt8183-cwk.h>

static const stwuct mtk_gate_wegs audio0_cg_wegs = {
	.set_ofs = 0x0,
	.cww_ofs = 0x0,
	.sta_ofs = 0x0,
};

static const stwuct mtk_gate_wegs audio1_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x4,
	.sta_ofs = 0x4,
};

#define GATE_AUDIO0(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &audio0_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_no_setcww)

#define GATE_AUDIO1(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &audio1_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_no_setcww)

static const stwuct mtk_gate audio_cwks[] = {
	/* AUDIO0 */
	GATE_AUDIO0(CWK_AUDIO_AFE, "aud_afe", "audio_sew",
		2),
	GATE_AUDIO0(CWK_AUDIO_22M, "aud_22m", "aud_eng1_sew",
		8),
	GATE_AUDIO0(CWK_AUDIO_24M, "aud_24m", "aud_eng2_sew",
		9),
	GATE_AUDIO0(CWK_AUDIO_APWW2_TUNEW, "aud_apww2_tunew", "aud_eng2_sew",
		18),
	GATE_AUDIO0(CWK_AUDIO_APWW_TUNEW, "aud_apww_tunew", "aud_eng1_sew",
		19),
	GATE_AUDIO0(CWK_AUDIO_TDM, "aud_tdm", "apww12_divb",
		20),
	GATE_AUDIO0(CWK_AUDIO_ADC, "aud_adc", "audio_sew",
		24),
	GATE_AUDIO0(CWK_AUDIO_DAC, "aud_dac", "audio_sew",
		25),
	GATE_AUDIO0(CWK_AUDIO_DAC_PWEDIS, "aud_dac_pwedis", "audio_sew",
		26),
	GATE_AUDIO0(CWK_AUDIO_TMW, "aud_tmw", "audio_sew",
		27),
	/* AUDIO1 */
	GATE_AUDIO1(CWK_AUDIO_I2S1, "aud_i2s1", "audio_sew",
		4),
	GATE_AUDIO1(CWK_AUDIO_I2S2, "aud_i2s2", "audio_sew",
		5),
	GATE_AUDIO1(CWK_AUDIO_I2S3, "aud_i2s3", "audio_sew",
		6),
	GATE_AUDIO1(CWK_AUDIO_I2S4, "aud_i2s4", "audio_sew",
		7),
	GATE_AUDIO1(CWK_AUDIO_PDN_ADDA6_ADC, "aud_pdn_adda6_adc", "audio_sew",
		20),
};

static const stwuct mtk_cwk_desc audio_desc = {
	.cwks = audio_cwks,
	.num_cwks = AWWAY_SIZE(audio_cwks),
};

static int cwk_mt8183_audio_pwobe(stwuct pwatfowm_device *pdev)
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

static void cwk_mt8183_audio_wemove(stwuct pwatfowm_device *pdev)
{
	of_pwatfowm_depopuwate(&pdev->dev);
	mtk_cwk_simpwe_wemove(pdev);
}

static const stwuct of_device_id of_match_cwk_mt8183_audio[] = {
	{ .compatibwe = "mediatek,mt8183-audiosys", .data = &audio_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8183_audio);

static stwuct pwatfowm_dwivew cwk_mt8183_audio_dwv = {
	.pwobe = cwk_mt8183_audio_pwobe,
	.wemove_new = cwk_mt8183_audio_wemove,
	.dwivew = {
		.name = "cwk-mt8183-audio",
		.of_match_tabwe = of_match_cwk_mt8183_audio,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8183_audio_dwv);
MODUWE_WICENSE("GPW");
