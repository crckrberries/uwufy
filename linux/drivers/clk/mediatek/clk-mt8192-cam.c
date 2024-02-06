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

static const stwuct mtk_gate_wegs cam_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_CAM(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &cam_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate cam_cwks[] = {
	GATE_CAM(CWK_CAM_WAWB13, "cam_wawb13", "cam_sew", 0),
	GATE_CAM(CWK_CAM_DFP_VAD, "cam_dfp_vad", "cam_sew", 1),
	GATE_CAM(CWK_CAM_WAWB14, "cam_wawb14", "cam_sew", 2),
	GATE_CAM(CWK_CAM_CAM, "cam_cam", "cam_sew", 6),
	GATE_CAM(CWK_CAM_CAMTG, "cam_camtg", "cam_sew", 7),
	GATE_CAM(CWK_CAM_SENINF, "cam_seninf", "cam_sew", 8),
	GATE_CAM(CWK_CAM_CAMSV0, "cam_camsv0", "cam_sew", 9),
	GATE_CAM(CWK_CAM_CAMSV1, "cam_camsv1", "cam_sew", 10),
	GATE_CAM(CWK_CAM_CAMSV2, "cam_camsv2", "cam_sew", 11),
	GATE_CAM(CWK_CAM_CAMSV3, "cam_camsv3", "cam_sew", 12),
	GATE_CAM(CWK_CAM_CCU0, "cam_ccu0", "cam_sew", 13),
	GATE_CAM(CWK_CAM_CCU1, "cam_ccu1", "cam_sew", 14),
	GATE_CAM(CWK_CAM_MWAW0, "cam_mwaw0", "cam_sew", 15),
	GATE_CAM(CWK_CAM_FAKE_ENG, "cam_fake_eng", "cam_sew", 17),
	GATE_CAM(CWK_CAM_CCU_GAWS, "cam_ccu_gaws", "cam_sew", 18),
	GATE_CAM(CWK_CAM_CAM2MM_GAWS, "cam2mm_gaws", "cam_sew", 19),
};

static const stwuct mtk_gate cam_wawa_cwks[] = {
	GATE_CAM(CWK_CAM_WAWA_WAWBX, "cam_wawa_wawbx", "cam_sew", 0),
	GATE_CAM(CWK_CAM_WAWA_CAM, "cam_wawa_cam", "cam_sew", 1),
	GATE_CAM(CWK_CAM_WAWA_CAMTG, "cam_wawa_camtg", "cam_sew", 2),
};

static const stwuct mtk_gate cam_wawb_cwks[] = {
	GATE_CAM(CWK_CAM_WAWB_WAWBX, "cam_wawb_wawbx", "cam_sew", 0),
	GATE_CAM(CWK_CAM_WAWB_CAM, "cam_wawb_cam", "cam_sew", 1),
	GATE_CAM(CWK_CAM_WAWB_CAMTG, "cam_wawb_camtg", "cam_sew", 2),
};

static const stwuct mtk_gate cam_wawc_cwks[] = {
	GATE_CAM(CWK_CAM_WAWC_WAWBX, "cam_wawc_wawbx", "cam_sew", 0),
	GATE_CAM(CWK_CAM_WAWC_CAM, "cam_wawc_cam", "cam_sew", 1),
	GATE_CAM(CWK_CAM_WAWC_CAMTG, "cam_wawc_camtg", "cam_sew", 2),
};

static const stwuct mtk_cwk_desc cam_desc = {
	.cwks = cam_cwks,
	.num_cwks = AWWAY_SIZE(cam_cwks),
};

static const stwuct mtk_cwk_desc cam_wawa_desc = {
	.cwks = cam_wawa_cwks,
	.num_cwks = AWWAY_SIZE(cam_wawa_cwks),
};

static const stwuct mtk_cwk_desc cam_wawb_desc = {
	.cwks = cam_wawb_cwks,
	.num_cwks = AWWAY_SIZE(cam_wawb_cwks),
};

static const stwuct mtk_cwk_desc cam_wawc_desc = {
	.cwks = cam_wawc_cwks,
	.num_cwks = AWWAY_SIZE(cam_wawc_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8192_cam[] = {
	{
		.compatibwe = "mediatek,mt8192-camsys",
		.data = &cam_desc,
	}, {
		.compatibwe = "mediatek,mt8192-camsys_wawa",
		.data = &cam_wawa_desc,
	}, {
		.compatibwe = "mediatek,mt8192-camsys_wawb",
		.data = &cam_wawb_desc,
	}, {
		.compatibwe = "mediatek,mt8192-camsys_wawc",
		.data = &cam_wawc_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8192_cam);

static stwuct pwatfowm_dwivew cwk_mt8192_cam_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8192-cam",
		.of_match_tabwe = of_match_cwk_mt8192_cam,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8192_cam_dwv);
MODUWE_WICENSE("GPW");
