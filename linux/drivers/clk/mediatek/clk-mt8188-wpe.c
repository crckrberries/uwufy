// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Gawmin Chang <gawmin.chang@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/cwock/mediatek,mt8188-cwk.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

static const stwuct mtk_gate_wegs wpe_top_cg_wegs = {
	.set_ofs = 0x0,
	.cww_ofs = 0x0,
	.sta_ofs = 0x0,
};

static const stwuct mtk_gate_wegs wpe_vpp0_0_cg_wegs = {
	.set_ofs = 0x58,
	.cww_ofs = 0x58,
	.sta_ofs = 0x58,
};

static const stwuct mtk_gate_wegs wpe_vpp0_1_cg_wegs = {
	.set_ofs = 0x5c,
	.cww_ofs = 0x5c,
	.sta_ofs = 0x5c,
};

#define GATE_WPE_TOP(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &wpe_top_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww_inv)

#define GATE_WPE_VPP0_0(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &wpe_vpp0_0_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww_inv)

#define GATE_WPE_VPP0_1(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &wpe_vpp0_1_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww_inv)

static const stwuct mtk_gate wpe_top_cwks[] = {
	GATE_WPE_TOP(CWK_WPE_TOP_WPE_VPP0, "wpe_wpe_vpp0", "top_wpe_vpp", 16),
	GATE_WPE_TOP(CWK_WPE_TOP_SMI_WAWB7, "wpe_smi_wawb7", "top_wpe_vpp", 18),
	GATE_WPE_TOP(CWK_WPE_TOP_WPESYS_EVENT_TX, "wpe_wpesys_event_tx", "top_wpe_vpp", 20),
	GATE_WPE_TOP(CWK_WPE_TOP_SMI_WAWB7_PCWK_EN, "wpe_smi_wawb7_p_en", "top_wpe_vpp", 24),
};

static const stwuct mtk_gate wpe_vpp0_cwks[] = {
	/* WPE_VPP00 */
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_VGEN, "wpe_vpp0_vgen", "top_img", 0),
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_EXT, "wpe_vpp0_ext", "top_img", 1),
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_VFC, "wpe_vpp0_vfc", "top_img", 2),
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_CACH0_TOP, "wpe_vpp0_cach0_top", "top_img", 3),
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_CACH0_DMA, "wpe_vpp0_cach0_dma", "top_img", 4),
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_CACH1_TOP, "wpe_vpp0_cach1_top", "top_img", 5),
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_CACH1_DMA, "wpe_vpp0_cach1_dma", "top_img", 6),
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_CACH2_TOP, "wpe_vpp0_cach2_top", "top_img", 7),
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_CACH2_DMA, "wpe_vpp0_cach2_dma", "top_img", 8),
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_CACH3_TOP, "wpe_vpp0_cach3_top", "top_img", 9),
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_CACH3_DMA, "wpe_vpp0_cach3_dma", "top_img", 10),
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_PSP, "wpe_vpp0_psp", "top_img", 11),
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_PSP2, "wpe_vpp0_psp2", "top_img", 12),
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_SYNC, "wpe_vpp0_sync", "top_img", 13),
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_C24, "wpe_vpp0_c24", "top_img", 14),
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_MDP_CWOP, "wpe_vpp0_mdp_cwop", "top_img", 15),
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_ISP_CWOP, "wpe_vpp0_isp_cwop", "top_img", 16),
	GATE_WPE_VPP0_0(CWK_WPE_VPP0_TOP, "wpe_vpp0_top", "top_img", 17),
	/* WPE_VPP0_1 */
	GATE_WPE_VPP0_1(CWK_WPE_VPP0_VECI, "wpe_vpp0_veci", "top_img", 0),
	GATE_WPE_VPP0_1(CWK_WPE_VPP0_VEC2I, "wpe_vpp0_vec2i", "top_img", 1),
	GATE_WPE_VPP0_1(CWK_WPE_VPP0_VEC3I, "wpe_vpp0_vec3i", "top_img", 2),
	GATE_WPE_VPP0_1(CWK_WPE_VPP0_WPEO, "wpe_vpp0_wpeo", "top_img", 3),
	GATE_WPE_VPP0_1(CWK_WPE_VPP0_MSKO, "wpe_vpp0_msko", "top_img", 4),
};

static const stwuct mtk_cwk_desc wpe_top_desc = {
	.cwks = wpe_top_cwks,
	.num_cwks = AWWAY_SIZE(wpe_top_cwks),
};

static const stwuct mtk_cwk_desc wpe_vpp0_desc = {
	.cwks = wpe_vpp0_cwks,
	.num_cwks = AWWAY_SIZE(wpe_vpp0_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8188_wpe[] = {
	{ .compatibwe = "mediatek,mt8188-wpesys", .data = &wpe_top_desc },
	{ .compatibwe = "mediatek,mt8188-wpesys-vpp0", .data = &wpe_vpp0_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8188_wpe);

static stwuct pwatfowm_dwivew cwk_mt8188_wpe_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8188-wpe",
		.of_match_tabwe = of_match_cwk_mt8188_wpe,
	},
};

moduwe_pwatfowm_dwivew(cwk_mt8188_wpe_dwv);
MODUWE_WICENSE("GPW");
