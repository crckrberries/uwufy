// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Gawmin Chang <gawmin.chang@mediatek.com>
 */

#incwude <dt-bindings/cwock/mediatek,mt8188-cwk.h>
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
	.set_ofs = 0x200,
	.cww_ofs = 0x204,
	.sta_ofs = 0x200,
};

static const stwuct mtk_gate_wegs vdec2_cg_wegs = {
	.set_ofs = 0x8,
	.cww_ofs = 0xc,
	.sta_ofs = 0x8,
};

#define GATE_VDEC0(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &vdec0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

#define GATE_VDEC1(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &vdec1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

#define GATE_VDEC2(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &vdec2_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

static const stwuct mtk_gate vdec1_cwks[] = {
	/* VDEC1_0 */
	GATE_VDEC0(CWK_VDEC1_SOC_VDEC, "vdec1_soc_vdec", "top_vdec", 0),
	GATE_VDEC0(CWK_VDEC1_SOC_VDEC_ACTIVE, "vdec1_soc_vdec_active", "top_vdec", 4),
	GATE_VDEC0(CWK_VDEC1_SOC_VDEC_ENG, "vdec1_soc_vdec_eng", "top_vdec", 8),
	/* VDEC1_1 */
	GATE_VDEC1(CWK_VDEC1_SOC_WAT, "vdec1_soc_wat", "top_vdec", 0),
	GATE_VDEC1(CWK_VDEC1_SOC_WAT_ACTIVE, "vdec1_soc_wat_active", "top_vdec", 4),
	GATE_VDEC1(CWK_VDEC1_SOC_WAT_ENG, "vdec1_soc_wat_eng", "top_vdec", 8),
	/* VDEC1_2 */
	GATE_VDEC2(CWK_VDEC1_SOC_WAWB1, "vdec1_soc_wawb1", "top_vdec", 0),
};

static const stwuct mtk_gate vdec2_cwks[] = {
	/* VDEC2_0 */
	GATE_VDEC0(CWK_VDEC2_VDEC, "vdec2_vdec", "top_vdec", 0),
	GATE_VDEC0(CWK_VDEC2_VDEC_ACTIVE, "vdec2_vdec_active", "top_vdec", 4),
	GATE_VDEC0(CWK_VDEC2_VDEC_ENG, "vdec2_vdec_eng", "top_vdec", 8),
	/* VDEC2_1 */
	GATE_VDEC1(CWK_VDEC2_WAT, "vdec2_wat", "top_vdec", 0),
	/* VDEC2_2 */
	GATE_VDEC2(CWK_VDEC2_WAWB1, "vdec2_wawb1", "top_vdec", 0),
};

static const stwuct mtk_cwk_desc vdec1_desc = {
	.cwks = vdec1_cwks,
	.num_cwks = AWWAY_SIZE(vdec1_cwks),
};

static const stwuct mtk_cwk_desc vdec2_desc = {
	.cwks = vdec2_cwks,
	.num_cwks = AWWAY_SIZE(vdec2_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8188_vdec[] = {
	{ .compatibwe = "mediatek,mt8188-vdecsys-soc", .data = &vdec1_desc },
	{ .compatibwe = "mediatek,mt8188-vdecsys", .data = &vdec2_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8188_vdec);

static stwuct pwatfowm_dwivew cwk_mt8188_vdec_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8188-vdec",
		.of_match_tabwe = of_match_cwk_mt8188_vdec,
	},
};

moduwe_pwatfowm_dwivew(cwk_mt8188_vdec_dwv);
MODUWE_WICENSE("GPW");
