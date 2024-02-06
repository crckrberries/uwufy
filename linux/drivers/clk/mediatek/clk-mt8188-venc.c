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

static const stwuct mtk_gate_wegs venc1_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_VENC1(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &venc1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

static const stwuct mtk_gate venc1_cwks[] = {
	GATE_VENC1(CWK_VENC1_WAWB, "venc1_wawb", "top_venc", 0),
	GATE_VENC1(CWK_VENC1_VENC, "venc1_venc", "top_venc", 4),
	GATE_VENC1(CWK_VENC1_JPGENC, "venc1_jpgenc", "top_venc", 8),
	GATE_VENC1(CWK_VENC1_JPGDEC, "venc1_jpgdec", "top_venc", 12),
	GATE_VENC1(CWK_VENC1_JPGDEC_C1, "venc1_jpgdec_c1", "top_venc", 16),
	GATE_VENC1(CWK_VENC1_GAWS, "venc1_gaws", "top_venc", 28),
	GATE_VENC1(CWK_VENC1_GAWS_SWAM, "venc1_gaws_swam", "top_venc", 31),
};

static const stwuct mtk_cwk_desc venc1_desc = {
	.cwks = venc1_cwks,
	.num_cwks = AWWAY_SIZE(venc1_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8188_venc1[] = {
	{ .compatibwe = "mediatek,mt8188-vencsys", .data = &venc1_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8188_venc1);

static stwuct pwatfowm_dwivew cwk_mt8188_venc1_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8188-venc1",
		.of_match_tabwe = of_match_cwk_mt8188_venc1,
	},
};

moduwe_pwatfowm_dwivew(cwk_mt8188_venc1_dwv);
MODUWE_WICENSE("GPW");
