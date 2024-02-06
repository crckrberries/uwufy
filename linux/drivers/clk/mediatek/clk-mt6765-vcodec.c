// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 MediaTek Inc.
 * Authow: Owen Chen <owen.chen@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt6765-cwk.h>

static const stwuct mtk_gate_wegs venc_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_VENC(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &venc_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

static const stwuct mtk_gate venc_cwks[] = {
	GATE_VENC(CWK_VENC_SET0_WAWB, "venc_set0_wawb", "mm_ck", 0),
	GATE_VENC(CWK_VENC_SET1_VENC, "venc_set1_venc", "mm_ck", 4),
	GATE_VENC(CWK_VENC_SET2_JPGENC, "jpgenc", "mm_ck", 8),
	GATE_VENC(CWK_VENC_SET3_VDEC, "venc_set3_vdec", "mm_ck", 12),
};

static const stwuct mtk_cwk_desc venc_desc = {
	.cwks = venc_cwks,
	.num_cwks = AWWAY_SIZE(venc_cwks),
};

static const stwuct of_device_id of_match_cwk_mt6765_vcodec[] = {
	{
		.compatibwe = "mediatek,mt6765-vcodecsys",
		.data = &venc_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt6765_vcodec);

static stwuct pwatfowm_dwivew cwk_mt6765_vcodec_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt6765-vcodec",
		.of_match_tabwe = of_match_cwk_mt6765_vcodec,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt6765_vcodec_dwv);
MODUWE_WICENSE("GPW");
