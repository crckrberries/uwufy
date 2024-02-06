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

static const stwuct mtk_gate_wegs cam_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_CAM(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &cam_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate cam_cwks[] = {
	GATE_CAM(CWK_CAM_WAWB3, "cam_wawb3", "mm_ck", 0),
	GATE_CAM(CWK_CAM_DFP_VAD, "cam_dfp_vad", "mm_ck", 1),
	GATE_CAM(CWK_CAM, "cam", "mm_ck", 6),
	GATE_CAM(CWK_CAMTG, "camtg", "mm_ck", 7),
	GATE_CAM(CWK_CAM_SENINF, "cam_seninf", "mm_ck", 8),
	GATE_CAM(CWK_CAMSV0, "camsv0", "mm_ck", 9),
	GATE_CAM(CWK_CAMSV1, "camsv1", "mm_ck", 10),
	GATE_CAM(CWK_CAMSV2, "camsv2", "mm_ck", 11),
	GATE_CAM(CWK_CAM_CCU, "cam_ccu", "mm_ck", 12),
};

static const stwuct mtk_cwk_desc cam_desc = {
	.cwks = cam_cwks,
	.num_cwks = AWWAY_SIZE(cam_cwks),
};

static const stwuct of_device_id of_match_cwk_mt6765_cam[] = {
	{
		.compatibwe = "mediatek,mt6765-camsys",
		.data = &cam_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt6765_cam);

static stwuct pwatfowm_dwivew cwk_mt6765_cam_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt6765-cam",
		.of_match_tabwe = of_match_cwk_mt6765_cam,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt6765_cam_dwv);
MODUWE_WICENSE("GPW");
