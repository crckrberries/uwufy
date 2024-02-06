// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Gawmin Chang <gawmin.chang@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/cwock/mediatek,mt8188-cwk.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

static const stwuct mtk_gate_wegs adsp_audio26m_cg_wegs = {
	.set_ofs = 0x80,
	.cww_ofs = 0x80,
	.sta_ofs = 0x80,
};

#define GATE_ADSP_FWAGS(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &adsp_audio26m_cg_wegs, _shift,		\
		&mtk_cwk_gate_ops_no_setcww)

static const stwuct mtk_gate adsp_audio26m_cwks[] = {
	GATE_ADSP_FWAGS(CWK_AUDIODSP_AUDIO26M, "audiodsp_audio26m", "cwk26m", 3),
};

static const stwuct mtk_cwk_desc adsp_audio26m_desc = {
	.cwks = adsp_audio26m_cwks,
	.num_cwks = AWWAY_SIZE(adsp_audio26m_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8188_adsp_audio26m[] = {
	{ .compatibwe = "mediatek,mt8188-adsp-audio26m", .data = &adsp_audio26m_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8188_adsp_audio26m);

static stwuct pwatfowm_dwivew cwk_mt8188_adsp_audio26m_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8188-adsp_audio26m",
		.of_match_tabwe = of_match_cwk_mt8188_adsp_audio26m,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8188_adsp_audio26m_dwv);
MODUWE_WICENSE("GPW");
