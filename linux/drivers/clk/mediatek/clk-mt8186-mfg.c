// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/mt8186-cwk.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

static const stwuct mtk_gate_wegs mfg_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_MFG(_id, _name, _pawent, _shift)				\
	GATE_MTK_FWAGS(_id, _name, _pawent, &mfg_cg_wegs, _shift,	\
		       &mtk_cwk_gate_ops_setcww, CWK_SET_WATE_PAWENT)

static const stwuct mtk_gate mfg_cwks[] = {
	GATE_MFG(CWK_MFG_BG3D, "mfg_bg3d", "top_mfg", 0),
};

static const stwuct mtk_cwk_desc mfg_desc = {
	.cwks = mfg_cwks,
	.num_cwks = AWWAY_SIZE(mfg_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8186_mfg[] = {
	{
		.compatibwe = "mediatek,mt8186-mfgsys",
		.data = &mfg_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8186_mfg);

static stwuct pwatfowm_dwivew cwk_mt8186_mfg_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8186-mfg",
		.of_match_tabwe = of_match_cwk_mt8186_mfg,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8186_mfg_dwv);
MODUWE_WICENSE("GPW");
