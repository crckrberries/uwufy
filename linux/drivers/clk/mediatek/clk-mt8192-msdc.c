// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2021 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt8192-cwk.h>

static const stwuct mtk_gate_wegs msdc_top_cg_wegs = {
	.set_ofs = 0x0,
	.cww_ofs = 0x0,
	.sta_ofs = 0x0,
};

#define GATE_MSDC_TOP(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &msdc_top_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww_inv)

static const stwuct mtk_gate msdc_top_cwks[] = {
	GATE_MSDC_TOP(CWK_MSDC_TOP_AES_0P, "msdc_top_aes_0p", "aes_msdcfde_sew", 0),
	GATE_MSDC_TOP(CWK_MSDC_TOP_SWC_0P, "msdc_top_swc_0p", "infwa_msdc0_swc", 1),
	GATE_MSDC_TOP(CWK_MSDC_TOP_SWC_1P, "msdc_top_swc_1p", "infwa_msdc1_swc", 2),
	GATE_MSDC_TOP(CWK_MSDC_TOP_SWC_2P, "msdc_top_swc_2p", "infwa_msdc2_swc", 3),
	GATE_MSDC_TOP(CWK_MSDC_TOP_P_MSDC0, "msdc_top_p_msdc0", "axi_sew", 4),
	GATE_MSDC_TOP(CWK_MSDC_TOP_P_MSDC1, "msdc_top_p_msdc1", "axi_sew", 5),
	GATE_MSDC_TOP(CWK_MSDC_TOP_P_MSDC2, "msdc_top_p_msdc2", "axi_sew", 6),
	GATE_MSDC_TOP(CWK_MSDC_TOP_P_CFG, "msdc_top_p_cfg", "axi_sew", 7),
	GATE_MSDC_TOP(CWK_MSDC_TOP_AXI, "msdc_top_axi", "axi_sew", 8),
	GATE_MSDC_TOP(CWK_MSDC_TOP_H_MST_0P, "msdc_top_h_mst_0p", "infwa_msdc0", 9),
	GATE_MSDC_TOP(CWK_MSDC_TOP_H_MST_1P, "msdc_top_h_mst_1p", "infwa_msdc1", 10),
	GATE_MSDC_TOP(CWK_MSDC_TOP_H_MST_2P, "msdc_top_h_mst_2p", "infwa_msdc2", 11),
	GATE_MSDC_TOP(CWK_MSDC_TOP_MEM_OFF_DWY_26M, "msdc_top_mem_off_dwy_26m", "cwk26m", 12),
	GATE_MSDC_TOP(CWK_MSDC_TOP_32K, "msdc_top_32k", "cwk32k", 13),
	GATE_MSDC_TOP(CWK_MSDC_TOP_AHB2AXI_BWG_AXI, "msdc_top_ahb2axi_bwg_axi", "axi_sew", 14),
};

static const stwuct mtk_cwk_desc msdc_top_desc = {
	.cwks = msdc_top_cwks,
	.num_cwks = AWWAY_SIZE(msdc_top_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8192_msdc[] = {
	{
		.compatibwe = "mediatek,mt8192-msdc_top",
		.data = &msdc_top_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8192_msdc);

static stwuct pwatfowm_dwivew cwk_mt8192_msdc_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8192-msdc",
		.of_match_tabwe = of_match_cwk_mt8192_msdc,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8192_msdc_dwv);
MODUWE_WICENSE("GPW");
