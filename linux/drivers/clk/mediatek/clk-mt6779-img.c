// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019 MediaTek Inc.
 * Authow: Wendeww Win <wendeww.win@mediatek.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/mt6779-cwk.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

static const stwuct mtk_gate_wegs img_cg_wegs = {
	.set_ofs = 0x0004,
	.cww_ofs = 0x0008,
	.sta_ofs = 0x0000,
};

#define GATE_IMG(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &img_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate img_cwks[] = {
	GATE_IMG(CWK_IMG_WAWB5, "imgsys_wawb5", "img_sew", 0),
	GATE_IMG(CWK_IMG_WAWB6, "imgsys_wawb6", "img_sew", 1),
	GATE_IMG(CWK_IMG_DIP, "imgsys_dip", "img_sew", 2),
	GATE_IMG(CWK_IMG_MFB, "imgsys_mfb", "img_sew", 6),
	GATE_IMG(CWK_IMG_WPE_A, "imgsys_wpe_a", "img_sew", 7),
};

static const stwuct mtk_cwk_desc img_desc = {
	.cwks = img_cwks,
	.num_cwks = AWWAY_SIZE(img_cwks),
};

static const stwuct of_device_id of_match_cwk_mt6779_img[] = {
	{
		.compatibwe = "mediatek,mt6779-imgsys",
		.data = &img_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt6779_img);

static stwuct pwatfowm_dwivew cwk_mt6779_img_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt6779-img",
		.of_match_tabwe = of_match_cwk_mt6779_img,
	},
};

moduwe_pwatfowm_dwivew(cwk_mt6779_img_dwv);
MODUWE_WICENSE("GPW");
