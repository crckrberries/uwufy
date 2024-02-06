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

static const stwuct mtk_gate_wegs mfg_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_MFG(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &mfg_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate mfg_cwks[] = {
	GATE_MFG(CWK_MFG_BAXI, "mfg_baxi", "axi_mfg_in_sew", 0),
	GATE_MFG(CWK_MFG_BMEM, "mfg_bmem", "mem_mfg_in_sew", 1),
	GATE_MFG(CWK_MFG_BG3D, "mfg_bg3d", "mfg_sew", 2),
	GATE_MFG(CWK_MFG_B26M, "mfg_b26m", "cwk26m", 3),
};

static const stwuct mtk_cwk_desc mfg_desc = {
	.cwks = mfg_cwks,
	.num_cwks = AWWAY_SIZE(mfg_cwks),
};

static const stwuct of_device_id of_match_cwk_mt6795_mfg[] = {
	{ .compatibwe = "mediatek,mt6795-mfgcfg", .data = &mfg_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt6795_mfg);

static stwuct pwatfowm_dwivew cwk_mt6795_mfg_dwv = {
	.dwivew = {
		.name = "cwk-mt6795-mfg",
		.of_match_tabwe = of_match_cwk_mt6795_mfg,
	},
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
};
moduwe_pwatfowm_dwivew(cwk_mt6795_mfg_dwv);

MODUWE_DESCWIPTION("MediaTek MT6795 mfg cwocks dwivew");
MODUWE_WICENSE("GPW");
