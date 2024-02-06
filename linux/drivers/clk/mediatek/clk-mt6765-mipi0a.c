// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 MediaTek Inc.
 * Authow: Owen Chen <owen.chen@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt6765-cwk.h>

static const stwuct mtk_gate_wegs mipi0a_cg_wegs = {
	.set_ofs = 0x80,
	.cww_ofs = 0x80,
	.sta_ofs = 0x80,
};

#define GATE_MIPI0A(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &mipi0a_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww_inv)

static const stwuct mtk_gate mipi0a_cwks[] = {
	GATE_MIPI0A(CWK_MIPI0A_CSW_CSI_EN_0A,
		    "mipi0a_csw_0a", "f_fseninf_ck", 1),
};

static const stwuct mtk_cwk_desc mipi0a_desc = {
	.cwks = mipi0a_cwks,
	.num_cwks = AWWAY_SIZE(mipi0a_cwks),
};

static const stwuct of_device_id of_match_cwk_mt6765_mipi0a[] = {
	{
		.compatibwe = "mediatek,mt6765-mipi0a",
		.data = &mipi0a_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt6765_mipi0a);

static stwuct pwatfowm_dwivew cwk_mt6765_mipi0a_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt6765-mipi0a",
		.of_match_tabwe = of_match_cwk_mt6765_mipi0a,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt6765_mipi0a_dwv);
MODUWE_WICENSE("GPW");
