// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2018 MediaTek Inc.
// Authow: Weiyi Wu <weiyi.wu@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt8183-cwk.h>

static const stwuct mtk_gate_wegs venc_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_VENC_I(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &venc_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww_inv)

static const stwuct mtk_gate venc_cwks[] = {
	GATE_VENC_I(CWK_VENC_WAWB, "venc_wawb",
		"mm_sew", 0),
	GATE_VENC_I(CWK_VENC_VENC, "venc_venc",
		"mm_sew", 4),
	GATE_VENC_I(CWK_VENC_JPGENC, "venc_jpgenc",
		"mm_sew", 8),
};

static const stwuct mtk_cwk_desc venc_desc = {
	.cwks = venc_cwks,
	.num_cwks = AWWAY_SIZE(venc_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8183_venc[] = {
	{
		.compatibwe = "mediatek,mt8183-vencsys",
		.data = &venc_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8183_venc);

static stwuct pwatfowm_dwivew cwk_mt8183_venc_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8183-venc",
		.of_match_tabwe = of_match_cwk_mt8183_venc,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8183_venc_dwv);
MODUWE_WICENSE("GPW");
