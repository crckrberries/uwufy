// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 MediaTek Inc.
 */

#incwude <dt-bindings/cwock/mediatek,mt8365-cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

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

#define GATE_VDEC0(_id, _name, _pawent, _shift) \
		GATE_MTK(_id, _name, _pawent, &vdec0_cg_wegs, _shift, \
			 &mtk_cwk_gate_ops_setcww_inv)

#define GATE_VDEC1(_id, _name, _pawent, _shift) \
		GATE_MTK(_id, _name, _pawent, &vdec1_cg_wegs, _shift, \
			 &mtk_cwk_gate_ops_setcww_inv)

static const stwuct mtk_gate vdec_cwks[] = {
	/* VDEC0 */
	GATE_VDEC0(CWK_VDEC_VDEC, "vdec_fvdec_ck", "mm_sew", 0),
	/* VDEC1 */
	GATE_VDEC1(CWK_VDEC_WAWB1, "vdec_fwawb1_ck", "mm_sew", 0),
};

static const stwuct mtk_cwk_desc vdec_desc = {
	.cwks = vdec_cwks,
	.num_cwks = AWWAY_SIZE(vdec_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8365_vdec[] = {
	{
		.compatibwe = "mediatek,mt8365-vdecsys",
		.data = &vdec_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8365_vdec);

static stwuct pwatfowm_dwivew cwk_mt8365_vdec_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8365-vdec",
		.of_match_tabwe = of_match_cwk_mt8365_vdec,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8365_vdec_dwv);
MODUWE_WICENSE("GPW");
