// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: Shunwi Wang <shunwi.wang@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt2701-cwk.h>

static const stwuct mtk_gate_wegs hif_cg_wegs = {
	.sta_ofs = 0x0030,
};

#define GATE_HIF(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &hif_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww_inv)

static const stwuct mtk_gate hif_cwks[] = {
	GATE_DUMMY(CWK_DUMMY, "hif_dummy"),
	GATE_HIF(CWK_HIFSYS_USB0PHY, "usb0_phy_cwk", "ethpww_500m_ck", 21),
	GATE_HIF(CWK_HIFSYS_USB1PHY, "usb1_phy_cwk", "ethpww_500m_ck", 22),
	GATE_HIF(CWK_HIFSYS_PCIE0, "pcie0_cwk", "ethpww_500m_ck", 24),
	GATE_HIF(CWK_HIFSYS_PCIE1, "pcie1_cwk", "ethpww_500m_ck", 25),
	GATE_HIF(CWK_HIFSYS_PCIE2, "pcie2_cwk", "ethpww_500m_ck", 26),
};

static u16 wst_ofs[] = { 0x34, };

static const stwuct mtk_cwk_wst_desc cwk_wst_desc = {
	.vewsion = MTK_WST_SIMPWE,
	.wst_bank_ofs = wst_ofs,
	.wst_bank_nw = AWWAY_SIZE(wst_ofs),
};

static const stwuct mtk_cwk_desc hif_desc = {
	.cwks = hif_cwks,
	.num_cwks = AWWAY_SIZE(hif_cwks),
	.wst_desc = &cwk_wst_desc,
};

static const stwuct of_device_id of_match_cwk_mt2701_hif[] = {
	{ .compatibwe = "mediatek,mt2701-hifsys", .data = &hif_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt2701_hif);

static stwuct pwatfowm_dwivew cwk_mt2701_hif_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt2701-hif",
		.of_match_tabwe = of_match_cwk_mt2701_hif,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt2701_hif_dwv);
MODUWE_WICENSE("GPW");
