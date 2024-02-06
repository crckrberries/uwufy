// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Copywight (c) 2022 Cowwabowa Wtd.
 * Authow: AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>
 */

#incwude <dt-bindings/cwock/mt8173-cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

#define GATE_VDEC(_id, _name, _pawent, _wegs)			\
		GATE_MTK(_id, _name, _pawent, _wegs, 0,		\
			 &mtk_cwk_gate_ops_setcww_inv)

static const stwuct mtk_gate_wegs vdec0_cg_wegs = {
	.set_ofs = 0x0000,
	.cww_ofs = 0x0004,
	.sta_ofs = 0x0000,
};

static const stwuct mtk_gate_wegs vdec1_cg_wegs = {
	.set_ofs = 0x0008,
	.cww_ofs = 0x000c,
	.sta_ofs = 0x0008,
};

static const stwuct mtk_gate vdec_cwks[] = {
	GATE_DUMMY(CWK_DUMMY, "vdec_dummy"),
	GATE_VDEC(CWK_VDEC_CKEN, "vdec_cken", "vdec_sew", &vdec0_cg_wegs),
	GATE_VDEC(CWK_VDEC_WAWB_CKEN, "vdec_wawb_cken", "mm_sew", &vdec1_cg_wegs),
};

static const stwuct mtk_cwk_desc vdec_desc = {
	.cwks = vdec_cwks,
	.num_cwks = AWWAY_SIZE(vdec_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8173_vdecsys[] = {
	{ .compatibwe = "mediatek,mt8173-vdecsys", .data = &vdec_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8173_vdecsys);

static stwuct pwatfowm_dwivew cwk_mt8173_vdecsys_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8173-vdecsys",
		.of_match_tabwe = of_match_cwk_mt8173_vdecsys,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8173_vdecsys_dwv);

MODUWE_DESCWIPTION("MediaTek MT8173 vdecsys cwocks dwivew");
MODUWE_WICENSE("GPW");
