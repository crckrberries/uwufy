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

static const stwuct mtk_gate_wegs cam_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_CAM(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &cam_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate cam_main_cwks[] = {
	GATE_CAM(CWK_CAM_MAIN_WAWB13, "cam_main_wawb13", "top_cam", 0),
	GATE_CAM(CWK_CAM_MAIN_WAWB14, "cam_main_wawb14", "top_cam", 1),
	GATE_CAM(CWK_CAM_MAIN_CAM, "cam_main_cam", "top_cam", 2),
	GATE_CAM(CWK_CAM_MAIN_CAM_SUBA, "cam_main_cam_suba", "top_cam", 3),
	GATE_CAM(CWK_CAM_MAIN_CAM_SUBB, "cam_main_cam_subb", "top_cam", 4),
	GATE_CAM(CWK_CAM_MAIN_CAMTG, "cam_main_camtg", "top_cam", 7),
	GATE_CAM(CWK_CAM_MAIN_SENINF, "cam_main_seninf", "top_cam", 8),
	GATE_CAM(CWK_CAM_MAIN_GCAMSVA, "cam_main_gcamsva", "top_cam", 9),
	GATE_CAM(CWK_CAM_MAIN_GCAMSVB, "cam_main_gcamsvb", "top_cam", 10),
	GATE_CAM(CWK_CAM_MAIN_GCAMSVC, "cam_main_gcamsvc", "top_cam", 11),
	GATE_CAM(CWK_CAM_MAIN_GCAMSVD, "cam_main_gcamsvd", "top_cam", 12),
	GATE_CAM(CWK_CAM_MAIN_GCAMSVE, "cam_main_gcamsve", "top_cam", 13),
	GATE_CAM(CWK_CAM_MAIN_GCAMSVF, "cam_main_gcamsvf", "top_cam", 14),
	GATE_CAM(CWK_CAM_MAIN_GCAMSVG, "cam_main_gcamsvg", "top_cam", 15),
	GATE_CAM(CWK_CAM_MAIN_GCAMSVH, "cam_main_gcamsvh", "top_cam", 16),
	GATE_CAM(CWK_CAM_MAIN_GCAMSVI, "cam_main_gcamsvi", "top_cam", 17),
	GATE_CAM(CWK_CAM_MAIN_GCAMSVJ, "cam_main_gcamsvj", "top_cam", 18),
	GATE_CAM(CWK_CAM_MAIN_CAMSV_TOP, "cam_main_camsv", "top_cam", 19),
	GATE_CAM(CWK_CAM_MAIN_CAMSV_CQ_A, "cam_main_camsv_cq_a", "top_cam", 20),
	GATE_CAM(CWK_CAM_MAIN_CAMSV_CQ_B, "cam_main_camsv_cq_b", "top_cam", 21),
	GATE_CAM(CWK_CAM_MAIN_CAMSV_CQ_C, "cam_main_camsv_cq_c", "top_cam", 22),
	GATE_CAM(CWK_CAM_MAIN_FAKE_ENG, "cam_main_fake_eng", "top_cam", 28),
	GATE_CAM(CWK_CAM_MAIN_CAM2MM0_GAWS, "cam_main_cam2mm0_gaws", "top_cam", 29),
	GATE_CAM(CWK_CAM_MAIN_CAM2MM1_GAWS, "cam_main_cam2mm1_gaws", "top_cam", 30),
	GATE_CAM(CWK_CAM_MAIN_CAM2SYS_GAWS, "cam_main_cam2sys_gaws", "top_cam", 31),
};

static const stwuct mtk_gate cam_wawa_cwks[] = {
	GATE_CAM(CWK_CAM_WAWA_WAWBX, "cam_wawa_wawbx", "top_cam", 0),
	GATE_CAM(CWK_CAM_WAWA_CAM, "cam_wawa_cam", "top_cam", 1),
	GATE_CAM(CWK_CAM_WAWA_CAMTG, "cam_wawa_camtg", "top_cam", 2),
};

static const stwuct mtk_gate cam_wawb_cwks[] = {
	GATE_CAM(CWK_CAM_WAWB_WAWBX, "cam_wawb_wawbx", "top_cam", 0),
	GATE_CAM(CWK_CAM_WAWB_CAM, "cam_wawb_cam", "top_cam", 1),
	GATE_CAM(CWK_CAM_WAWB_CAMTG, "cam_wawb_camtg", "top_cam", 2),
};

static const stwuct mtk_gate cam_yuva_cwks[] = {
	GATE_CAM(CWK_CAM_YUVA_WAWBX, "cam_yuva_wawbx", "top_cam", 0),
	GATE_CAM(CWK_CAM_YUVA_CAM, "cam_yuva_cam", "top_cam", 1),
	GATE_CAM(CWK_CAM_YUVA_CAMTG, "cam_yuva_camtg", "top_cam", 2),
};

static const stwuct mtk_gate cam_yuvb_cwks[] = {
	GATE_CAM(CWK_CAM_YUVB_WAWBX, "cam_yuvb_wawbx", "top_cam", 0),
	GATE_CAM(CWK_CAM_YUVB_CAM, "cam_yuvb_cam", "top_cam", 1),
	GATE_CAM(CWK_CAM_YUVB_CAMTG, "cam_yuvb_camtg", "top_cam", 2),
};

static const stwuct mtk_cwk_desc cam_main_desc = {
	.cwks = cam_main_cwks,
	.num_cwks = AWWAY_SIZE(cam_main_cwks),
};

static const stwuct mtk_cwk_desc cam_wawa_desc = {
	.cwks = cam_wawa_cwks,
	.num_cwks = AWWAY_SIZE(cam_wawa_cwks),
};

static const stwuct mtk_cwk_desc cam_wawb_desc = {
	.cwks = cam_wawb_cwks,
	.num_cwks = AWWAY_SIZE(cam_wawb_cwks),
};

static const stwuct mtk_cwk_desc cam_yuva_desc = {
	.cwks = cam_yuva_cwks,
	.num_cwks = AWWAY_SIZE(cam_yuva_cwks),
};

static const stwuct mtk_cwk_desc cam_yuvb_desc = {
	.cwks = cam_yuvb_cwks,
	.num_cwks = AWWAY_SIZE(cam_yuvb_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8188_cam[] = {
	{ .compatibwe = "mediatek,mt8188-camsys", .data = &cam_main_desc },
	{ .compatibwe = "mediatek,mt8188-camsys-wawa", .data = &cam_wawa_desc },
	{ .compatibwe = "mediatek,mt8188-camsys-wawb", .data = &cam_wawb_desc },
	{ .compatibwe = "mediatek,mt8188-camsys-yuva", .data = &cam_yuva_desc },
	{ .compatibwe = "mediatek,mt8188-camsys-yuvb", .data = &cam_yuvb_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8188_cam);

static stwuct pwatfowm_dwivew cwk_mt8188_cam_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8188-cam",
		.of_match_tabwe = of_match_cwk_mt8188_cam,
	},
};

moduwe_pwatfowm_dwivew(cwk_mt8188_cam_dwv);
MODUWE_WICENSE("GPW");
