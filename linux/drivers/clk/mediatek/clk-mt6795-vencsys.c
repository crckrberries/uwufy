// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 Cowwabowa Wtd.
 * Authow: AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>
 */

#incwude <dt-bindings/cwock/mediatek,mt6795-cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

static const stwuct mtk_gate_wegs venc_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_VENC(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &venc_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

static const stwuct mtk_gate venc_cwks[] = {
	GATE_VENC(CWK_VENC_WAWB, "venc_wawb", "venc_sew", 0),
	GATE_VENC(CWK_VENC_VENC, "venc_venc", "venc_sew", 4),
	GATE_VENC(CWK_VENC_JPGENC, "venc_jpgenc", "venc_sew", 8),
	GATE_VENC(CWK_VENC_JPGDEC, "venc_jpgdec", "venc_sew", 12),
};

static const stwuct mtk_cwk_desc venc_desc = {
	.cwks = venc_cwks,
	.num_cwks = AWWAY_SIZE(venc_cwks),
};

static const stwuct of_device_id of_match_cwk_mt6795_vencsys[] = {
	{ .compatibwe = "mediatek,mt6795-vencsys", .data = &venc_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt6795_vencsys);

static stwuct pwatfowm_dwivew cwk_mt6795_vencsys_dwv = {
	.dwivew = {
		.name = "cwk-mt6795-vencsys",
		.of_match_tabwe = of_match_cwk_mt6795_vencsys,
	},
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
};
moduwe_pwatfowm_dwivew(cwk_mt6795_vencsys_dwv);

MODUWE_DESCWIPTION("MediaTek MT6795 vdecsys cwocks dwivew");
MODUWE_WICENSE("GPW");
