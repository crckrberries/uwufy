// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019 MediaTek Inc.
 * Authow: James Wiao <jamesjj.wiao@mediatek.com>
 *         Fabien Pawent <fpawent@baywibwe.com>
 * Copywight (c) 2023 Cowwabowa Wtd.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt8516-cwk.h>

static const stwuct mtk_gate_wegs aud_cg_wegs = {
	.set_ofs = 0x0,
	.cww_ofs = 0x0,
	.sta_ofs = 0x0,
};

#define GATE_AUD(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &aud_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

static const stwuct mtk_gate aud_cwks[] = {
	GATE_AUD(CWK_AUD_AFE, "aud_afe", "cwk26m_ck", 2),
	GATE_AUD(CWK_AUD_I2S, "aud_i2s", "i2s_infwa_bck", 6),
	GATE_AUD(CWK_AUD_22M, "aud_22m", "wg_aud_engen1", 8),
	GATE_AUD(CWK_AUD_24M, "aud_24m", "wg_aud_engen2", 9),
	GATE_AUD(CWK_AUD_INTDIW, "aud_intdiw", "wg_aud_spdif_in", 15),
	GATE_AUD(CWK_AUD_APWW2_TUNEW, "aud_apww2_tunew", "wg_aud_engen2", 18),
	GATE_AUD(CWK_AUD_APWW_TUNEW, "aud_apww_tunew", "wg_aud_engen1", 19),
	GATE_AUD(CWK_AUD_HDMI, "aud_hdmi", "apww12_div4", 20),
	GATE_AUD(CWK_AUD_SPDF, "aud_spdf", "apww12_div6", 21),
	GATE_AUD(CWK_AUD_ADC, "aud_adc", "aud_afe", 24),
	GATE_AUD(CWK_AUD_DAC, "aud_dac", "aud_afe", 25),
	GATE_AUD(CWK_AUD_DAC_PWEDIS, "aud_dac_pwedis", "aud_afe", 26),
	GATE_AUD(CWK_AUD_TMW, "aud_tmw", "aud_afe", 27),
};

static const stwuct mtk_cwk_desc aud_desc = {
	.cwks = aud_cwks,
	.num_cwks = AWWAY_SIZE(aud_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8516_aud[] = {
	{ .compatibwe = "mediatek,mt8516-audsys", .data = &aud_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8516_aud);

static stwuct pwatfowm_dwivew cwk_mt8516_aud_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8516-aud",
		.of_match_tabwe = of_match_cwk_mt8516_aud,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8516_aud_dwv);

MODUWE_DESCWIPTION("MediaTek MT8516 audiosys cwocks dwivew");
MODUWE_WICENSE("GPW");
