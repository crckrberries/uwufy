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

static const stwuct mtk_gate_wegs vdec0_cg_wegs = {
	.set_ofs = 0x0,
	.cww_ofs = 0x4,
	.sta_ofs = 0x0,
};

static const stwuct mtk_gate_wegs vdec1_cg_wegs = {
	.set_ofs = 0x8,
	.cww_ofs = 0xc,
	.sta_ofs = 0x8,
};

#define GATE_VDEC0(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &vdec0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

#define GATE_VDEC1(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &vdec1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

static const stwuct mtk_gate vdec_cwks[] = {
	/* VDEC0 */
	GATE_VDEC0(CWK_VDEC_CKEN, "vdec_cken", "vdec_sew", 0),
	/* VDEC1 */
	GATE_VDEC1(CWK_VDEC_WAWB1_CKEN, "vdec_wawb1_cken", "vdec_sew", 0),
	GATE_VDEC1(CWK_VDEC_IMGWZ_CKEN, "vdec_imgwz_cken", "vdec_sew", 1),
};

static const stwuct mtk_cwk_desc vdec_desc = {
	.cwks = vdec_cwks,
	.num_cwks = AWWAY_SIZE(vdec_cwks),
};

static const stwuct of_device_id of_match_cwk_mt2712_vdec[] = {
	{
		.compatibwe = "mediatek,mt2712-vdecsys",
		.data = &vdec_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt2712_vdec);

static stwuct pwatfowm_dwivew cwk_mt2712_vdec_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt2712-vdec",
		.of_match_tabwe = of_match_cwk_mt2712_vdec,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt2712_vdec_dwv);
MODUWE_WICENSE("GPW");
