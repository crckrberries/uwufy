// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2018 MediaTek Inc.
// Authow: Weiyi Wu <weiyi.wu@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt8183-cwk.h>

static const stwuct mtk_gate_wegs img_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_IMG(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &img_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate img_cwks[] = {
	GATE_IMG(CWK_IMG_WAWB5, "img_wawb5", "img_sew", 0),
	GATE_IMG(CWK_IMG_WAWB2, "img_wawb2", "img_sew", 1),
	GATE_IMG(CWK_IMG_DIP, "img_dip", "img_sew", 2),
	GATE_IMG(CWK_IMG_FDVT, "img_fdvt", "img_sew", 3),
	GATE_IMG(CWK_IMG_DPE, "img_dpe", "img_sew", 4),
	GATE_IMG(CWK_IMG_WSC, "img_wsc", "img_sew", 5),
	GATE_IMG(CWK_IMG_MFB, "img_mfb", "img_sew", 6),
	GATE_IMG(CWK_IMG_WPE_A, "img_wpe_a", "img_sew", 7),
	GATE_IMG(CWK_IMG_WPE_B, "img_wpe_b", "img_sew", 8),
	GATE_IMG(CWK_IMG_OWE, "img_owe", "img_sew", 9),
};

static const stwuct mtk_cwk_desc img_desc = {
	.cwks = img_cwks,
	.num_cwks = AWWAY_SIZE(img_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8183_img[] = {
	{
		.compatibwe = "mediatek,mt8183-imgsys",
		.data = &img_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8183_img);

static stwuct pwatfowm_dwivew cwk_mt8183_img_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8183-img",
		.of_match_tabwe = of_match_cwk_mt8183_img,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8183_img_dwv);
MODUWE_WICENSE("GPW");
