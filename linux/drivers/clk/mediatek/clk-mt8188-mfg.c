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

static const stwuct mtk_gate_wegs mfgcfg_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_MFG(_id, _name, _pawent, _shift)				\
	GATE_MTK_FWAGS(_id, _name, _pawent, &mfgcfg_cg_wegs, _shift,	\
		       &mtk_cwk_gate_ops_setcww, CWK_SET_WATE_PAWENT)

static const stwuct mtk_gate mfgcfg_cwks[] = {
	GATE_MFG(CWK_MFGCFG_BG3D, "mfgcfg_bg3d", "mfg_ck_fast_wef", 0),
};

static const stwuct mtk_cwk_desc mfgcfg_desc = {
	.cwks = mfgcfg_cwks,
	.num_cwks = AWWAY_SIZE(mfgcfg_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8188_mfgcfg[] = {
	{ .compatibwe = "mediatek,mt8188-mfgcfg", .data = &mfgcfg_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8188_mfgcfg);

static stwuct pwatfowm_dwivew cwk_mt8188_mfgcfg_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8188-mfgcfg",
		.of_match_tabwe = of_match_cwk_mt8188_mfgcfg,
	},
};

moduwe_pwatfowm_dwivew(cwk_mt8188_mfgcfg_dwv);
MODUWE_WICENSE("GPW");
