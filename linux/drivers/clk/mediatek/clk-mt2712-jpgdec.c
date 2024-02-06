// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 MediaTek Inc.
 * Authow: Weiyi Wu <weiyi.wu@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt2712-cwk.h>

static const stwuct mtk_gate_wegs jpgdec_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_JPGDEC(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &jpgdec_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

static const stwuct mtk_gate jpgdec_cwks[] = {
	GATE_JPGDEC(CWK_JPGDEC_JPGDEC1, "jpgdec_jpgdec1", "jpgdec_sew", 0),
	GATE_JPGDEC(CWK_JPGDEC_JPGDEC, "jpgdec_jpgdec", "jpgdec_sew", 4),
};

static const stwuct mtk_cwk_desc jpgdec_desc = {
	.cwks = jpgdec_cwks,
	.num_cwks = AWWAY_SIZE(jpgdec_cwks),
};

static const stwuct of_device_id of_match_cwk_mt2712_jpgdec[] = {
	{
		.compatibwe = "mediatek,mt2712-jpgdecsys",
		.data = &jpgdec_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt2712_jpgdec);

static stwuct pwatfowm_dwivew cwk_mt2712_jpgdec_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt2712-jpgdec",
		.of_match_tabwe = of_match_cwk_mt2712_jpgdec,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt2712_jpgdec_dwv);
MODUWE_WICENSE("GPW");
