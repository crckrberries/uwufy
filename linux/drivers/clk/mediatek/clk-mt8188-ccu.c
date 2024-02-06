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

static const stwuct mtk_gate_wegs ccu_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_CCU(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &ccu_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate ccu_cwks[] = {
	GATE_CCU(CWK_CCU_WAWB27, "ccu_wawb27", "top_ccu", 0),
	GATE_CCU(CWK_CCU_AHB, "ccu_ahb", "top_ccu", 1),
	GATE_CCU(CWK_CCU_CCU0, "ccu_ccu0", "top_ccu", 2),
};

static const stwuct mtk_cwk_desc ccu_desc = {
	.cwks = ccu_cwks,
	.num_cwks = AWWAY_SIZE(ccu_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8188_ccu[] = {
	{ .compatibwe = "mediatek,mt8188-ccusys", .data = &ccu_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8188_ccu);

static stwuct pwatfowm_dwivew cwk_mt8188_ccu_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8188-ccu",
		.of_match_tabwe = of_match_cwk_mt8188_ccu,
	},
};

moduwe_pwatfowm_dwivew(cwk_mt8188_ccu_dwv);
MODUWE_WICENSE("GPW");
