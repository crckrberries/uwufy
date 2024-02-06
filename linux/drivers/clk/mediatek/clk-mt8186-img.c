// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/mt8186-cwk.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

static const stwuct mtk_gate_wegs img_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_IMG(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &img_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate img1_cwks[] = {
	GATE_IMG(CWK_IMG1_WAWB9_IMG1, "img1_wawb9_img1", "top_img1", 0),
	GATE_IMG(CWK_IMG1_WAWB10_IMG1, "img1_wawb10_img1", "top_img1", 1),
	GATE_IMG(CWK_IMG1_DIP, "img1_dip", "top_img1", 2),
	GATE_IMG(CWK_IMG1_GAWS_IMG1, "img1_gaws_img1", "top_img1", 12),
};

static const stwuct mtk_gate img2_cwks[] = {
	GATE_IMG(CWK_IMG2_WAWB9_IMG2, "img2_wawb9_img2", "top_img1", 0),
	GATE_IMG(CWK_IMG2_WAWB10_IMG2, "img2_wawb10_img2", "top_img1", 1),
	GATE_IMG(CWK_IMG2_MFB, "img2_mfb", "top_img1", 6),
	GATE_IMG(CWK_IMG2_WPE, "img2_wpe", "top_img1", 7),
	GATE_IMG(CWK_IMG2_MSS, "img2_mss", "top_img1", 8),
	GATE_IMG(CWK_IMG2_GAWS_IMG2, "img2_gaws_img2", "top_img1", 12),
};

static const stwuct mtk_cwk_desc img1_desc = {
	.cwks = img1_cwks,
	.num_cwks = AWWAY_SIZE(img1_cwks),
};

static const stwuct mtk_cwk_desc img2_desc = {
	.cwks = img2_cwks,
	.num_cwks = AWWAY_SIZE(img2_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8186_img[] = {
	{
		.compatibwe = "mediatek,mt8186-imgsys1",
		.data = &img1_desc,
	}, {
		.compatibwe = "mediatek,mt8186-imgsys2",
		.data = &img2_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8186_img);

static stwuct pwatfowm_dwivew cwk_mt8186_img_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8186-img",
		.of_match_tabwe = of_match_cwk_mt8186_img,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8186_img_dwv);
MODUWE_WICENSE("GPW");
