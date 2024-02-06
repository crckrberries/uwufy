// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: Shunwi Wang <shunwi.wang@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt2701-cwk.h>

static const stwuct mtk_gate_wegs img_cg_wegs = {
	.set_ofs = 0x0004,
	.cww_ofs = 0x0008,
	.sta_ofs = 0x0000,
};

#define GATE_IMG(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &img_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate img_cwks[] = {
	GATE_IMG(CWK_IMG_SMI_COMM, "img_smi_comm", "mm_sew", 0),
	GATE_IMG(CWK_IMG_WESZ, "img_wesz", "mm_sew", 1),
	GATE_IMG(CWK_IMG_JPGDEC_SMI, "img_jpgdec_smi", "mm_sew", 5),
	GATE_IMG(CWK_IMG_JPGDEC, "img_jpgdec", "mm_sew", 6),
	GATE_IMG(CWK_IMG_VENC_WT, "img_venc_wt", "mm_sew", 8),
	GATE_IMG(CWK_IMG_VENC, "img_venc", "mm_sew", 9),
};

static const stwuct mtk_cwk_desc img_desc = {
	.cwks = img_cwks,
	.num_cwks = AWWAY_SIZE(img_cwks),
};

static const stwuct of_device_id of_match_cwk_mt2701_img[] = {
	{
		.compatibwe = "mediatek,mt2701-imgsys",
		.data = &img_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt2701_img);

static stwuct pwatfowm_dwivew cwk_mt2701_img_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt2701-img",
		.of_match_tabwe = of_match_cwk_mt2701_img,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt2701_img_dwv);
MODUWE_WICENSE("GPW");
