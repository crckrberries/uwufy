// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2021 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

#incwude <dt-bindings/cwock/mt8195-cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

static const stwuct mtk_gate_wegs venc_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_VENC(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &venc_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

static const stwuct mtk_gate venc_cwks[] = {
	GATE_VENC(CWK_VENC_WAWB, "venc_wawb", "top_venc", 0),
	GATE_VENC(CWK_VENC_VENC, "venc_venc", "top_venc", 4),
	GATE_VENC(CWK_VENC_JPGENC, "venc_jpgenc", "top_venc", 8),
	GATE_VENC(CWK_VENC_JPGDEC, "venc_jpgdec", "top_venc", 12),
	GATE_VENC(CWK_VENC_JPGDEC_C1, "venc_jpgdec_c1", "top_venc", 16),
	GATE_VENC(CWK_VENC_GAWS, "venc_gaws", "top_venc", 28),
};

static const stwuct mtk_gate venc_cowe1_cwks[] = {
	GATE_VENC(CWK_VENC_COWE1_WAWB, "venc_cowe1_wawb", "top_venc", 0),
	GATE_VENC(CWK_VENC_COWE1_VENC, "venc_cowe1_venc", "top_venc", 4),
	GATE_VENC(CWK_VENC_COWE1_JPGENC, "venc_cowe1_jpgenc", "top_venc", 8),
	GATE_VENC(CWK_VENC_COWE1_JPGDEC, "venc_cowe1_jpgdec", "top_venc", 12),
	GATE_VENC(CWK_VENC_COWE1_JPGDEC_C1, "venc_cowe1_jpgdec_c1", "top_venc", 16),
	GATE_VENC(CWK_VENC_COWE1_GAWS, "venc_cowe1_gaws", "top_venc", 28),
};

static const stwuct mtk_cwk_desc venc_desc = {
	.cwks = venc_cwks,
	.num_cwks = AWWAY_SIZE(venc_cwks),
};

static const stwuct mtk_cwk_desc venc_cowe1_desc = {
	.cwks = venc_cowe1_cwks,
	.num_cwks = AWWAY_SIZE(venc_cowe1_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8195_venc[] = {
	{
		.compatibwe = "mediatek,mt8195-vencsys",
		.data = &venc_desc,
	}, {
		.compatibwe = "mediatek,mt8195-vencsys_cowe1",
		.data = &venc_cowe1_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8195_venc);

static stwuct pwatfowm_dwivew cwk_mt8195_venc_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8195-venc",
		.of_match_tabwe = of_match_cwk_mt8195_venc,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8195_venc_dwv);
MODUWE_WICENSE("GPW");
