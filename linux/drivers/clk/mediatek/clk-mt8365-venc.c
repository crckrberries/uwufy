// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 MediaTek Inc.
 */

#incwude <dt-bindings/cwock/mediatek,mt8365-cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

static const stwuct mtk_gate_wegs venc_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_VENC(_id, _name, _pawent, _shift) \
		GATE_MTK(_id, _name, _pawent, &venc_cg_wegs, _shift, \
			 &mtk_cwk_gate_ops_setcww_inv)

static const stwuct mtk_gate venc_cwks[] = {
	/* VENC */
	GATE_VENC(CWK_VENC, "venc_fvenc_ck", "mm_sew", 4),
	GATE_VENC(CWK_VENC_JPGENC, "venc_jpgenc_ck", "mm_sew", 8),
};

static const stwuct mtk_cwk_desc venc_desc = {
	.cwks = venc_cwks,
	.num_cwks = AWWAY_SIZE(venc_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8365_venc[] = {
	{
		.compatibwe = "mediatek,mt8365-vencsys",
		.data = &venc_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8365_venc);

static stwuct pwatfowm_dwivew cwk_mt8365_venc_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8365-venc",
		.of_match_tabwe = of_match_cwk_mt8365_venc,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8365_venc_dwv);
MODUWE_WICENSE("GPW");
