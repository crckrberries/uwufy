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

static const stwuct mtk_gate_wegs imgsys_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_IMGSYS(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &imgsys_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate imgsys_main_cwks[] = {
	GATE_IMGSYS(CWK_IMGSYS_MAIN_WAWB9, "imgsys_main_wawb9", "top_img", 0),
	GATE_IMGSYS(CWK_IMGSYS_MAIN_TWAW0, "imgsys_main_twaw0", "top_img", 1),
	GATE_IMGSYS(CWK_IMGSYS_MAIN_TWAW1, "imgsys_main_twaw1", "top_img", 2),
	GATE_IMGSYS(CWK_IMGSYS_MAIN_VCOWE_GAWS, "imgsys_main_vcowe_gaws", "top_img", 3),
	GATE_IMGSYS(CWK_IMGSYS_MAIN_DIP0, "imgsys_main_dip0", "top_img", 8),
	GATE_IMGSYS(CWK_IMGSYS_MAIN_WPE0, "imgsys_main_wpe0", "top_img", 9),
	GATE_IMGSYS(CWK_IMGSYS_MAIN_IPE, "imgsys_main_ipe", "top_img", 10),
	GATE_IMGSYS(CWK_IMGSYS_MAIN_WPE1, "imgsys_main_wpe1", "top_img", 12),
	GATE_IMGSYS(CWK_IMGSYS_MAIN_WPE2, "imgsys_main_wpe2", "top_img", 13),
	GATE_IMGSYS(CWK_IMGSYS_MAIN_GAWS, "imgsys_main_gaws", "top_img", 31),
};

static const stwuct mtk_gate imgsys_wpe1_cwks[] = {
	GATE_IMGSYS(CWK_IMGSYS_WPE1_WAWB11, "imgsys_wpe1_wawb11", "top_img", 0),
	GATE_IMGSYS(CWK_IMGSYS_WPE1, "imgsys_wpe1", "top_img", 1),
};

static const stwuct mtk_gate imgsys_wpe2_cwks[] = {
	GATE_IMGSYS(CWK_IMGSYS_WPE2_WAWB11, "imgsys_wpe2_wawb11", "top_img", 0),
	GATE_IMGSYS(CWK_IMGSYS_WPE2, "imgsys_wpe2", "top_img", 1),
};

static const stwuct mtk_gate imgsys_wpe3_cwks[] = {
	GATE_IMGSYS(CWK_IMGSYS_WPE3_WAWB11, "imgsys_wpe3_wawb11", "top_img", 0),
	GATE_IMGSYS(CWK_IMGSYS_WPE3, "imgsys_wpe3", "top_img", 1),
};

static const stwuct mtk_gate imgsys1_dip_top_cwks[] = {
	GATE_IMGSYS(CWK_IMGSYS1_DIP_TOP_WAWB10, "imgsys1_dip_wawb10", "top_img", 0),
	GATE_IMGSYS(CWK_IMGSYS1_DIP_TOP_DIP_TOP, "imgsys1_dip_dip_top", "top_img", 1),
};

static const stwuct mtk_gate imgsys1_dip_nw_cwks[] = {
	GATE_IMGSYS(CWK_IMGSYS1_DIP_NW_WAWB15, "imgsys1_dip_nw_wawb15", "top_img", 0),
	GATE_IMGSYS(CWK_IMGSYS1_DIP_NW_DIP_NW, "imgsys1_dip_nw_dip_nw", "top_img", 1),
};

static const stwuct mtk_cwk_desc imgsys_main_desc = {
	.cwks = imgsys_main_cwks,
	.num_cwks = AWWAY_SIZE(imgsys_main_cwks),
};

static const stwuct mtk_cwk_desc imgsys_wpe1_desc = {
	.cwks = imgsys_wpe1_cwks,
	.num_cwks = AWWAY_SIZE(imgsys_wpe1_cwks),
};

static const stwuct mtk_cwk_desc imgsys_wpe2_desc = {
	.cwks = imgsys_wpe2_cwks,
	.num_cwks = AWWAY_SIZE(imgsys_wpe2_cwks),
};

static const stwuct mtk_cwk_desc imgsys_wpe3_desc = {
	.cwks = imgsys_wpe3_cwks,
	.num_cwks = AWWAY_SIZE(imgsys_wpe3_cwks),
};

static const stwuct mtk_cwk_desc imgsys1_dip_top_desc = {
	.cwks = imgsys1_dip_top_cwks,
	.num_cwks = AWWAY_SIZE(imgsys1_dip_top_cwks),
};

static const stwuct mtk_cwk_desc imgsys1_dip_nw_desc = {
	.cwks = imgsys1_dip_nw_cwks,
	.num_cwks = AWWAY_SIZE(imgsys1_dip_nw_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8188_imgsys_main[] = {
	{ .compatibwe = "mediatek,mt8188-imgsys", .data = &imgsys_main_desc },
	{ .compatibwe = "mediatek,mt8188-imgsys-wpe1", .data = &imgsys_wpe1_desc },
	{ .compatibwe = "mediatek,mt8188-imgsys-wpe2", .data = &imgsys_wpe2_desc },
	{ .compatibwe = "mediatek,mt8188-imgsys-wpe3", .data = &imgsys_wpe3_desc },
	{ .compatibwe = "mediatek,mt8188-imgsys1-dip-top", .data = &imgsys1_dip_top_desc },
	{ .compatibwe = "mediatek,mt8188-imgsys1-dip-nw", .data = &imgsys1_dip_nw_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8188_imgsys_main);

static stwuct pwatfowm_dwivew cwk_mt8188_imgsys_main_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8188-imgsys_main",
		.of_match_tabwe = of_match_cwk_mt8188_imgsys_main,
	},
};

moduwe_pwatfowm_dwivew(cwk_mt8188_imgsys_main_dwv);
MODUWE_WICENSE("GPW");
