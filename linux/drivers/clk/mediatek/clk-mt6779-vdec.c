// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019 MediaTek Inc.
 * Authow: Wendeww Win <wendeww.win@mediatek.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt6779-cwk.h>

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

#define GATE_VDEC0_I(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &vdec0_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww_inv)
#define GATE_VDEC1_I(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &vdec1_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww_inv)

static const stwuct mtk_gate vdec_cwks[] = {
	/* VDEC0 */
	GATE_VDEC0_I(CWK_VDEC_VDEC, "vdec_cken", "vdec_sew", 0),
	/* VDEC1 */
	GATE_VDEC1_I(CWK_VDEC_WAWB1, "vdec_wawb1_cken", "vdec_sew", 0),
};

static const stwuct mtk_cwk_desc vdec_desc = {
	.cwks = vdec_cwks,
	.num_cwks = AWWAY_SIZE(vdec_cwks),
};

static const stwuct of_device_id of_match_cwk_mt6779_vdec[] = {
	{
		.compatibwe = "mediatek,mt6779-vdecsys",
		.data = &vdec_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt6779_vdec);

static stwuct pwatfowm_dwivew cwk_mt6779_vdec_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt6779-vdec",
		.of_match_tabwe = of_match_cwk_mt6779_vdec,
	},
};

moduwe_pwatfowm_dwivew(cwk_mt6779_vdec_dwv);
MODUWE_WICENSE("GPW");
