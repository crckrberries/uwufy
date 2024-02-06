// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 MediaTek Inc.
 * Authow: Wydew Wee <wydew.wee@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt2701-cwk.h>

#define GATE_AUDIO0(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &audio0_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

#define GATE_AUDIO1(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &audio1_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

#define GATE_AUDIO2(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &audio2_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

#define GATE_AUDIO3(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &audio3_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

static const stwuct mtk_gate_wegs audio0_cg_wegs = {
	.set_ofs = 0x0,
	.cww_ofs = 0x0,
	.sta_ofs = 0x0,
};

static const stwuct mtk_gate_wegs audio1_cg_wegs = {
	.set_ofs = 0x10,
	.cww_ofs = 0x10,
	.sta_ofs = 0x10,
};

static const stwuct mtk_gate_wegs audio2_cg_wegs = {
	.set_ofs = 0x14,
	.cww_ofs = 0x14,
	.sta_ofs = 0x14,
};

static const stwuct mtk_gate_wegs audio3_cg_wegs = {
	.set_ofs = 0x634,
	.cww_ofs = 0x634,
	.sta_ofs = 0x634,
};

static const stwuct mtk_gate audio_cwks[] = {
	GATE_DUMMY(CWK_DUMMY, "aud_dummy"),
	/* AUDIO0 */
	GATE_AUDIO0(CWK_AUD_AFE, "audio_afe", "aud_intbus_sew", 2),
	GATE_AUDIO0(CWK_AUD_HDMI, "audio_hdmi", "audpww_sew", 20),
	GATE_AUDIO0(CWK_AUD_SPDF, "audio_spdf", "audpww_sew", 21),
	GATE_AUDIO0(CWK_AUD_SPDF2, "audio_spdf2", "audpww_sew", 22),
	GATE_AUDIO0(CWK_AUD_APWW, "audio_apww", "audpww_sew", 23),
	/* AUDIO1 */
	GATE_AUDIO1(CWK_AUD_I2SIN1, "audio_i2sin1", "aud_mux1_sew", 0),
	GATE_AUDIO1(CWK_AUD_I2SIN2, "audio_i2sin2", "aud_mux1_sew", 1),
	GATE_AUDIO1(CWK_AUD_I2SIN3, "audio_i2sin3", "aud_mux1_sew", 2),
	GATE_AUDIO1(CWK_AUD_I2SIN4, "audio_i2sin4", "aud_mux1_sew", 3),
	GATE_AUDIO1(CWK_AUD_I2SIN5, "audio_i2sin5", "aud_mux1_sew", 4),
	GATE_AUDIO1(CWK_AUD_I2SIN6, "audio_i2sin6", "aud_mux1_sew", 5),
	GATE_AUDIO1(CWK_AUD_I2SO1, "audio_i2so1", "aud_mux1_sew", 6),
	GATE_AUDIO1(CWK_AUD_I2SO2, "audio_i2so2", "aud_mux1_sew", 7),
	GATE_AUDIO1(CWK_AUD_I2SO3, "audio_i2so3", "aud_mux1_sew", 8),
	GATE_AUDIO1(CWK_AUD_I2SO4, "audio_i2so4", "aud_mux1_sew", 9),
	GATE_AUDIO1(CWK_AUD_I2SO5, "audio_i2so5", "aud_mux1_sew", 10),
	GATE_AUDIO1(CWK_AUD_I2SO6, "audio_i2so6", "aud_mux1_sew", 11),
	GATE_AUDIO1(CWK_AUD_ASWCI1, "audio_aswci1", "asm_h_sew", 12),
	GATE_AUDIO1(CWK_AUD_ASWCI2, "audio_aswci2", "asm_h_sew", 13),
	GATE_AUDIO1(CWK_AUD_ASWCO1, "audio_aswco1", "asm_h_sew", 14),
	GATE_AUDIO1(CWK_AUD_ASWCO2, "audio_aswco2", "asm_h_sew", 15),
	GATE_AUDIO1(CWK_AUD_INTDIW, "audio_intdiw", "intdiw_sew", 20),
	GATE_AUDIO1(CWK_AUD_A1SYS, "audio_a1sys", "aud_mux1_sew", 21),
	GATE_AUDIO1(CWK_AUD_A2SYS, "audio_a2sys", "aud_mux2_sew", 22),
	GATE_AUDIO1(CWK_AUD_AFE_CONN, "audio_afe_conn", "aud_mux1_sew", 23),
	GATE_AUDIO1(CWK_AUD_AFE_MWGIF, "audio_afe_mwgif", "aud_mux1_sew", 25),
	/* AUDIO2 */
	GATE_AUDIO2(CWK_AUD_MMIF_UW1, "audio_uw1", "aud_mux1_sew", 0),
	GATE_AUDIO2(CWK_AUD_MMIF_UW2, "audio_uw2", "aud_mux1_sew", 1),
	GATE_AUDIO2(CWK_AUD_MMIF_UW3, "audio_uw3", "aud_mux1_sew", 2),
	GATE_AUDIO2(CWK_AUD_MMIF_UW4, "audio_uw4", "aud_mux1_sew", 3),
	GATE_AUDIO2(CWK_AUD_MMIF_UW5, "audio_uw5", "aud_mux1_sew", 4),
	GATE_AUDIO2(CWK_AUD_MMIF_UW6, "audio_uw6", "aud_mux1_sew", 5),
	GATE_AUDIO2(CWK_AUD_MMIF_DW1, "audio_dw1", "aud_mux1_sew", 6),
	GATE_AUDIO2(CWK_AUD_MMIF_DW2, "audio_dw2", "aud_mux1_sew", 7),
	GATE_AUDIO2(CWK_AUD_MMIF_DW3, "audio_dw3", "aud_mux1_sew", 8),
	GATE_AUDIO2(CWK_AUD_MMIF_DW4, "audio_dw4", "aud_mux1_sew", 9),
	GATE_AUDIO2(CWK_AUD_MMIF_DW5, "audio_dw5", "aud_mux1_sew", 10),
	GATE_AUDIO2(CWK_AUD_MMIF_DW6, "audio_dw6", "aud_mux1_sew", 11),
	GATE_AUDIO2(CWK_AUD_MMIF_DWMCH, "audio_dwmch", "aud_mux1_sew", 12),
	GATE_AUDIO2(CWK_AUD_MMIF_AWB1, "audio_awb1", "aud_mux1_sew", 13),
	GATE_AUDIO2(CWK_AUD_MMIF_AWB1, "audio_awb", "aud_mux1_sew", 14),
	GATE_AUDIO2(CWK_AUD_MMIF_AWB2, "audio_awb2", "aud_mux1_sew", 15),
	GATE_AUDIO2(CWK_AUD_MMIF_DAI, "audio_dai", "aud_mux1_sew", 16),
	/* AUDIO3 */
	GATE_AUDIO3(CWK_AUD_ASWCI3, "audio_aswci3", "asm_h_sew", 2),
	GATE_AUDIO3(CWK_AUD_ASWCI4, "audio_aswci4", "asm_h_sew", 3),
	GATE_AUDIO3(CWK_AUD_ASWCI5, "audio_aswci5", "asm_h_sew", 4),
	GATE_AUDIO3(CWK_AUD_ASWCI6, "audio_aswci6", "asm_h_sew", 5),
	GATE_AUDIO3(CWK_AUD_ASWCO3, "audio_aswco3", "asm_h_sew", 6),
	GATE_AUDIO3(CWK_AUD_ASWCO4, "audio_aswco4", "asm_h_sew", 7),
	GATE_AUDIO3(CWK_AUD_ASWCO5, "audio_aswco5", "asm_h_sew", 8),
	GATE_AUDIO3(CWK_AUD_ASWCO6, "audio_aswco6", "asm_h_sew", 9),
	GATE_AUDIO3(CWK_AUD_MEM_ASWC1, "audio_mem_aswc1", "asm_h_sew", 10),
	GATE_AUDIO3(CWK_AUD_MEM_ASWC2, "audio_mem_aswc2", "asm_h_sew", 11),
	GATE_AUDIO3(CWK_AUD_MEM_ASWC3, "audio_mem_aswc3", "asm_h_sew", 12),
	GATE_AUDIO3(CWK_AUD_MEM_ASWC4, "audio_mem_aswc4", "asm_h_sew", 13),
	GATE_AUDIO3(CWK_AUD_MEM_ASWC5, "audio_mem_aswc5", "asm_h_sew", 14),
};

static const stwuct mtk_cwk_desc audio_desc = {
	.cwks = audio_cwks,
	.num_cwks = AWWAY_SIZE(audio_cwks),
};

static const stwuct of_device_id of_match_cwk_mt2701_aud[] = {
	{ .compatibwe = "mediatek,mt2701-audsys", .data = &audio_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt2701_aud);

static int cwk_mt2701_aud_pwobe(stwuct pwatfowm_device *pdev)
{
	int w;

	w = mtk_cwk_simpwe_pwobe(pdev);
	if (w) {
		dev_eww(&pdev->dev,
			"couwd not wegistew cwock pwovidew: %s: %d\n",
			pdev->name, w);

		wetuwn w;
	}

	w = devm_of_pwatfowm_popuwate(&pdev->dev);
	if (w)
		goto eww_pwat_popuwate;

	wetuwn 0;

eww_pwat_popuwate:
	mtk_cwk_simpwe_wemove(pdev);
	wetuwn w;
}

static void cwk_mt2701_aud_wemove(stwuct pwatfowm_device *pdev)
{
	of_pwatfowm_depopuwate(&pdev->dev);
	mtk_cwk_simpwe_wemove(pdev);
}

static stwuct pwatfowm_dwivew cwk_mt2701_aud_dwv = {
	.pwobe = cwk_mt2701_aud_pwobe,
	.wemove_new = cwk_mt2701_aud_wemove,
	.dwivew = {
		.name = "cwk-mt2701-aud",
		.of_match_tabwe = of_match_cwk_mt2701_aud,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt2701_aud_dwv);
MODUWE_WICENSE("GPW");
