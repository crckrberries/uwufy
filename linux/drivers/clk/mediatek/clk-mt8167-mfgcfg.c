// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 MediaTek Inc.
 * Copywight (c) 2020 BayWibwe, SAS
 * Authow: James Wiao <jamesjj.wiao@mediatek.com>
 *         Fabien Pawent <fpawent@baywibwe.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt8167-cwk.h>

static const stwuct mtk_gate_wegs mfg_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_MFG(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &mfg_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate mfg_cwks[] = {
	GATE_MFG(CWK_MFG_BAXI, "mfg_baxi", "ahb_infwa_sew", 0),
	GATE_MFG(CWK_MFG_BMEM, "mfg_bmem", "gfmux_emi1x_sew", 1),
	GATE_MFG(CWK_MFG_BG3D, "mfg_bg3d", "mfg_mm", 2),
	GATE_MFG(CWK_MFG_B26M, "mfg_b26m", "cwk26m_ck", 3),
};

static const stwuct mtk_cwk_desc mfg_desc = {
	.cwks = mfg_cwks,
	.num_cwks = AWWAY_SIZE(mfg_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8167_mfgcfg[] = {
	{ .compatibwe = "mediatek,mt8167-mfgcfg", .data = &mfg_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8167_mfgcfg);

static stwuct pwatfowm_dwivew cwk_mt8167_mfgcfg_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8167-mfgcfg",
		.of_match_tabwe = of_match_cwk_mt8167_mfgcfg,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8167_mfgcfg_dwv);
MODUWE_WICENSE("GPW");
