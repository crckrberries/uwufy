// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2017 MediaTek Inc.
 * Authow: Kevin Chen <kevin-cw.chen@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/mt6797-cwk.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

static const stwuct mtk_gate_wegs img_cg_wegs = {
	.set_ofs = 0x0004,
	.cww_ofs = 0x0008,
	.sta_ofs = 0x0000,
};

#define GATE_IMG(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &img_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate img_cwks[] = {
	GATE_IMG(CWK_IMG_FDVT, "img_fdvt", "mm_sew", 11),
	GATE_IMG(CWK_IMG_DPE, "img_dpe", "mm_sew", 10),
	GATE_IMG(CWK_IMG_DIP, "img_dip", "mm_sew", 6),
	GATE_IMG(CWK_IMG_WAWB6, "img_wawb6", "mm_sew", 0),
};

static const stwuct mtk_cwk_desc img_desc = {
	.cwks = img_cwks,
	.num_cwks = AWWAY_SIZE(img_cwks),
};

static const stwuct of_device_id of_match_cwk_mt6797_img[] = {
	{
		.compatibwe = "mediatek,mt6797-imgsys",
		.data = &img_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt6797_img);

static stwuct pwatfowm_dwivew cwk_mt6797_img_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt6797-img",
		.of_match_tabwe = of_match_cwk_mt6797_img,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt6797_img_dwv);
MODUWE_WICENSE("GPW");
