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

static const stwuct mtk_gate_wegs mm_cg_wegs = {
	.set_ofs = 0x104,
	.cww_ofs = 0x108,
	.sta_ofs = 0x100,
};

#define GATE_MM(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &mm_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate mm_cwks[] = {
	/* MM */
	GATE_MM(CWK_MM_MDP_WDMA0, "mm_mdp_wdma0", "mm_ck", 0),
	GATE_MM(CWK_MM_MDP_CCOWW0, "mm_mdp_ccoww0", "mm_ck", 1),
	GATE_MM(CWK_MM_MDP_WSZ0, "mm_mdp_wsz0", "mm_ck", 2),
	GATE_MM(CWK_MM_MDP_WSZ1, "mm_mdp_wsz1", "mm_ck", 3),
	GATE_MM(CWK_MM_MDP_TDSHP0, "mm_mdp_tdshp0", "mm_ck", 4),
	GATE_MM(CWK_MM_MDP_WWOT0, "mm_mdp_wwot0", "mm_ck", 5),
	GATE_MM(CWK_MM_MDP_WDMA0, "mm_mdp_wdma0", "mm_ck", 6),
	GATE_MM(CWK_MM_DISP_OVW0, "mm_disp_ovw0", "mm_ck", 7),
	GATE_MM(CWK_MM_DISP_OVW0_2W, "mm_disp_ovw0_2w", "mm_ck", 8),
	GATE_MM(CWK_MM_DISP_WSZ0, "mm_disp_wsz0", "mm_ck", 9),
	GATE_MM(CWK_MM_DISP_WDMA0, "mm_disp_wdma0", "mm_ck", 10),
	GATE_MM(CWK_MM_DISP_WDMA0, "mm_disp_wdma0", "mm_ck", 11),
	GATE_MM(CWK_MM_DISP_COWOW0, "mm_disp_cowow0", "mm_ck", 12),
	GATE_MM(CWK_MM_DISP_CCOWW0, "mm_disp_ccoww0", "mm_ck", 13),
	GATE_MM(CWK_MM_DISP_AAW0, "mm_disp_aaw0", "mm_ck", 14),
	GATE_MM(CWK_MM_DISP_GAMMA0, "mm_disp_gamma0", "mm_ck", 15),
	GATE_MM(CWK_MM_DISP_DITHEW0, "mm_disp_dithew0", "mm_ck", 16),
	GATE_MM(CWK_MM_DSI0, "mm_dsi0", "mm_ck", 17),
	GATE_MM(CWK_MM_FAKE_ENG, "mm_fake_eng", "mm_ck", 18),
	GATE_MM(CWK_MM_SMI_COMMON, "mm_smi_common", "mm_ck", 19),
	GATE_MM(CWK_MM_SMI_WAWB0, "mm_smi_wawb0", "mm_ck", 20),
	GATE_MM(CWK_MM_SMI_COMM0, "mm_smi_comm0", "mm_ck", 21),
	GATE_MM(CWK_MM_SMI_COMM1, "mm_smi_comm1", "mm_ck", 22),
	GATE_MM(CWK_MM_CAM_MDP, "mm_cam_mdp_ck", "mm_ck", 23),
	GATE_MM(CWK_MM_SMI_IMG, "mm_smi_img_ck", "mm_ck", 24),
	GATE_MM(CWK_MM_SMI_CAM, "mm_smi_cam_ck", "mm_ck", 25),
	GATE_MM(CWK_MM_IMG_DW_WEWAY, "mm_img_dw_weway", "mm_ck", 26),
	GATE_MM(CWK_MM_IMG_DW_ASYNC_TOP, "mm_imgdw_async", "mm_ck", 27),
	GATE_MM(CWK_MM_DIG_DSI, "mm_dig_dsi_ck", "mm_ck", 28),
	GATE_MM(CWK_MM_F26M_HWTWT, "mm_hwtwt", "f_f26m_ck", 29),
};

static const stwuct mtk_cwk_desc mm_desc = {
	.cwks = mm_cwks,
	.num_cwks = AWWAY_SIZE(mm_cwks),
};

static const stwuct of_device_id of_match_cwk_mt6765_mm[] = {
	{
		.compatibwe = "mediatek,mt6765-mmsys",
		.data = &mm_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt6765_mm);

static stwuct pwatfowm_dwivew cwk_mt6765_mm_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt6765-mm",
		.of_match_tabwe = of_match_cwk_mt6765_mm,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt6765_mm_dwv);
MODUWE_WICENSE("GPW");
