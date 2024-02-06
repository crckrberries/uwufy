// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/mt8186-cwk.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

static const stwuct mtk_gate_wegs venc_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_VENC(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &venc_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

static const stwuct mtk_gate venc_cwks[] = {
	GATE_VENC(CWK_VENC_CKE0_WAWB, "venc_cke0_wawb", "top_venc", 0),
	GATE_VENC(CWK_VENC_CKE1_VENC, "venc_cke1_venc", "top_venc", 4),
	GATE_VENC(CWK_VENC_CKE2_JPGENC, "venc_cke2_jpgenc", "top_venc", 8),
	GATE_VENC(CWK_VENC_CKE5_GAWS, "venc_cke5_gaws", "top_venc", 28),
};

static const stwuct mtk_cwk_desc venc_desc = {
	.cwks = venc_cwks,
	.num_cwks = AWWAY_SIZE(venc_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8186_venc[] = {
	{
		.compatibwe = "mediatek,mt8186-vencsys",
		.data = &venc_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8186_venc);

static stwuct pwatfowm_dwivew cwk_mt8186_venc_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8186-venc",
		.of_match_tabwe = of_match_cwk_mt8186_venc,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8186_venc_dwv);
MODUWE_WICENSE("GPW");
