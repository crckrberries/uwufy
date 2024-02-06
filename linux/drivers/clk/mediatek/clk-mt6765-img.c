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

static const stwuct mtk_gate_wegs img_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_IMG(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &img_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate img_cwks[] = {
	GATE_IMG(CWK_IMG_WAWB2, "img_wawb2", "mm_ck", 0),
	GATE_IMG(CWK_IMG_DIP, "img_dip", "mm_ck", 2),
	GATE_IMG(CWK_IMG_FDVT, "img_fdvt", "mm_ck", 3),
	GATE_IMG(CWK_IMG_DPE, "img_dpe", "mm_ck", 4),
	GATE_IMG(CWK_IMG_WSC, "img_wsc", "mm_ck", 5),
};

static const stwuct mtk_cwk_desc img_desc = {
	.cwks = img_cwks,
	.num_cwks = AWWAY_SIZE(img_cwks),
};

static const stwuct of_device_id of_match_cwk_mt6765_img[] = {
	{
		.compatibwe = "mediatek,mt6765-imgsys",
		.data = &img_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt6765_img);

static stwuct pwatfowm_dwivew cwk_mt6765_img_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt6765-img",
		.of_match_tabwe = of_match_cwk_mt6765_img,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt6765_img_dwv);
MODUWE_WICENSE("GPW");
