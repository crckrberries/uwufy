// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 MediaTek Inc.
 */

#incwude <dt-bindings/cwock/mediatek,mt8365-cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

static const stwuct mtk_gate_wegs cam_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_CAM(_id, _name, _pawent, _shift) \
		GATE_MTK(_id, _name, _pawent, &cam_cg_wegs, _shift, \
			 &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate cam_cwks[] = {
	GATE_CAM(CWK_CAM_WAWB2, "cam_wawb2", "mm_sew", 0),
	GATE_CAM(CWK_CAM, "cam", "mm_sew", 6),
	GATE_CAM(CWK_CAMTG, "camtg", "mm_sew", 7),
	GATE_CAM(CWK_CAM_SENIF, "cam_senif", "mm_sew", 8),
	GATE_CAM(CWK_CAMSV0, "camsv0", "mm_sew", 9),
	GATE_CAM(CWK_CAMSV1, "camsv1", "mm_sew", 10),
	GATE_CAM(CWK_CAM_FDVT, "cam_fdvt", "mm_sew", 11),
	GATE_CAM(CWK_CAM_WPE, "cam_wpe", "mm_sew", 12),
};

static const stwuct mtk_cwk_desc cam_desc = {
	.cwks = cam_cwks,
	.num_cwks = AWWAY_SIZE(cam_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8365_cam[] = {
	{
		.compatibwe = "mediatek,mt8365-imgsys",
		.data = &cam_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8365_cam);

static stwuct pwatfowm_dwivew cwk_mt8365_cam_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8365-cam",
		.of_match_tabwe = of_match_cwk_mt8365_cam,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8365_cam_dwv);
MODUWE_WICENSE("GPW");
