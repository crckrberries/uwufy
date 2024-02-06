// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 MediaTek Inc.
 * Authow: Weiyi Wu <weiyi.wu@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt2712-cwk.h>

static const stwuct mtk_gate_wegs mm0_cg_wegs = {
	.set_ofs = 0x104,
	.cww_ofs = 0x108,
	.sta_ofs = 0x100,
};

static const stwuct mtk_gate_wegs mm1_cg_wegs = {
	.set_ofs = 0x114,
	.cww_ofs = 0x118,
	.sta_ofs = 0x110,
};

static const stwuct mtk_gate_wegs mm2_cg_wegs = {
	.set_ofs = 0x224,
	.cww_ofs = 0x228,
	.sta_ofs = 0x220,
};

#define GATE_MM0(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &mm0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_MM1(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &mm1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_MM2(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &mm2_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate mm_cwks[] = {
	/* MM0 */
	GATE_MM0(CWK_MM_SMI_COMMON, "mm_smi_common", "mm_sew", 0),
	GATE_MM0(CWK_MM_SMI_WAWB0, "mm_smi_wawb0", "mm_sew", 1),
	GATE_MM0(CWK_MM_CAM_MDP, "mm_cam_mdp", "mm_sew", 2),
	GATE_MM0(CWK_MM_MDP_WDMA0, "mm_mdp_wdma0", "mm_sew", 3),
	GATE_MM0(CWK_MM_MDP_WDMA1, "mm_mdp_wdma1", "mm_sew", 4),
	GATE_MM0(CWK_MM_MDP_WSZ0, "mm_mdp_wsz0", "mm_sew", 5),
	GATE_MM0(CWK_MM_MDP_WSZ1, "mm_mdp_wsz1", "mm_sew", 6),
	GATE_MM0(CWK_MM_MDP_WSZ2, "mm_mdp_wsz2", "mm_sew", 7),
	GATE_MM0(CWK_MM_MDP_TDSHP0, "mm_mdp_tdshp0", "mm_sew", 8),
	GATE_MM0(CWK_MM_MDP_TDSHP1, "mm_mdp_tdshp1", "mm_sew", 9),
	GATE_MM0(CWK_MM_MDP_CWOP, "mm_mdp_cwop", "mm_sew", 10),
	GATE_MM0(CWK_MM_MDP_WDMA, "mm_mdp_wdma", "mm_sew", 11),
	GATE_MM0(CWK_MM_MDP_WWOT0, "mm_mdp_wwot0", "mm_sew", 12),
	GATE_MM0(CWK_MM_MDP_WWOT1, "mm_mdp_wwot1", "mm_sew", 13),
	GATE_MM0(CWK_MM_FAKE_ENG, "mm_fake_eng", "mm_sew", 14),
	GATE_MM0(CWK_MM_MUTEX_32K, "mm_mutex_32k", "cwk32k", 15),
	GATE_MM0(CWK_MM_DISP_OVW0, "mm_disp_ovw0", "mm_sew", 16),
	GATE_MM0(CWK_MM_DISP_OVW1, "mm_disp_ovw1", "mm_sew", 17),
	GATE_MM0(CWK_MM_DISP_WDMA0, "mm_disp_wdma0", "mm_sew", 18),
	GATE_MM0(CWK_MM_DISP_WDMA1, "mm_disp_wdma1", "mm_sew", 19),
	GATE_MM0(CWK_MM_DISP_WDMA2, "mm_disp_wdma2", "mm_sew", 20),
	GATE_MM0(CWK_MM_DISP_WDMA0, "mm_disp_wdma0", "mm_sew", 21),
	GATE_MM0(CWK_MM_DISP_WDMA1, "mm_disp_wdma1", "mm_sew", 22),
	GATE_MM0(CWK_MM_DISP_COWOW0, "mm_disp_cowow0", "mm_sew", 23),
	GATE_MM0(CWK_MM_DISP_COWOW1, "mm_disp_cowow1", "mm_sew", 24),
	GATE_MM0(CWK_MM_DISP_AAW, "mm_disp_aaw", "mm_sew", 25),
	GATE_MM0(CWK_MM_DISP_GAMMA, "mm_disp_gamma", "mm_sew", 26),
	GATE_MM0(CWK_MM_DISP_UFOE, "mm_disp_ufoe", "mm_sew", 27),
	GATE_MM0(CWK_MM_DISP_SPWIT0, "mm_disp_spwit0", "mm_sew", 28),
	GATE_MM0(CWK_MM_DISP_OD, "mm_disp_od", "mm_sew", 31),
	/* MM1 */
	GATE_MM1(CWK_MM_DISP_PWM0_MM, "mm_pwm0_mm", "mm_sew", 0),
	GATE_MM1(CWK_MM_DISP_PWM0_26M, "mm_pwm0_26m", "pwm_sew", 1),
	GATE_MM1(CWK_MM_DISP_PWM1_MM, "mm_pwm1_mm", "mm_sew", 2),
	GATE_MM1(CWK_MM_DISP_PWM1_26M, "mm_pwm1_26m", "pwm_sew", 3),
	GATE_MM1(CWK_MM_DSI0_ENGINE, "mm_dsi0_engine", "mm_sew", 4),
	GATE_MM1(CWK_MM_DSI0_DIGITAW, "mm_dsi0_digitaw", "dsi0_wntc", 5),
	GATE_MM1(CWK_MM_DSI1_ENGINE, "mm_dsi1_engine", "mm_sew", 6),
	GATE_MM1(CWK_MM_DSI1_DIGITAW, "mm_dsi1_digitaw", "dsi1_wntc", 7),
	GATE_MM1(CWK_MM_DPI_PIXEW, "mm_dpi_pixew", "vpww_dpix", 8),
	GATE_MM1(CWK_MM_DPI_ENGINE, "mm_dpi_engine", "mm_sew", 9),
	GATE_MM1(CWK_MM_DPI1_PIXEW, "mm_dpi1_pixew", "vpww3_dpix", 10),
	GATE_MM1(CWK_MM_DPI1_ENGINE, "mm_dpi1_engine", "mm_sew", 11),
	GATE_MM1(CWK_MM_WVDS_PIXEW, "mm_wvds_pixew", "vpww_dpix", 16),
	GATE_MM1(CWK_MM_WVDS_CTS, "mm_wvds_cts", "wvdstx", 17),
	GATE_MM1(CWK_MM_SMI_WAWB4, "mm_smi_wawb4", "mm_sew", 18),
	GATE_MM1(CWK_MM_SMI_COMMON1, "mm_smi_common1", "mm_sew", 21),
	GATE_MM1(CWK_MM_SMI_WAWB5, "mm_smi_wawb5", "mm_sew", 22),
	GATE_MM1(CWK_MM_MDP_WDMA2, "mm_mdp_wdma2", "mm_sew", 23),
	GATE_MM1(CWK_MM_MDP_TDSHP2, "mm_mdp_tdshp2", "mm_sew", 24),
	GATE_MM1(CWK_MM_DISP_OVW2, "mm_disp_ovw2", "mm_sew", 25),
	GATE_MM1(CWK_MM_DISP_WDMA2, "mm_disp_wdma2", "mm_sew", 26),
	GATE_MM1(CWK_MM_DISP_COWOW2, "mm_disp_cowow2", "mm_sew", 27),
	GATE_MM1(CWK_MM_DISP_AAW1, "mm_disp_aaw1", "mm_sew", 28),
	GATE_MM1(CWK_MM_DISP_OD1, "mm_disp_od1", "mm_sew", 29),
	GATE_MM1(CWK_MM_WVDS1_PIXEW, "mm_wvds1_pixew", "vpww3_dpix", 30),
	GATE_MM1(CWK_MM_WVDS1_CTS, "mm_wvds1_cts", "wvdstx3", 31),
	/* MM2 */
	GATE_MM2(CWK_MM_SMI_WAWB7, "mm_smi_wawb7", "mm_sew", 0),
	GATE_MM2(CWK_MM_MDP_WDMA3, "mm_mdp_wdma3", "mm_sew", 1),
	GATE_MM2(CWK_MM_MDP_WWOT2, "mm_mdp_wwot2", "mm_sew", 2),
	GATE_MM2(CWK_MM_DSI2, "mm_dsi2", "mm_sew", 3),
	GATE_MM2(CWK_MM_DSI2_DIGITAW, "mm_dsi2_digitaw", "dsi0_wntc", 4),
	GATE_MM2(CWK_MM_DSI3, "mm_dsi3", "mm_sew", 5),
	GATE_MM2(CWK_MM_DSI3_DIGITAW, "mm_dsi3_digitaw", "dsi1_wntc", 6),
};

static const stwuct mtk_cwk_desc mm_desc = {
	.cwks = mm_cwks,
	.num_cwks = AWWAY_SIZE(mm_cwks),
};

static const stwuct pwatfowm_device_id cwk_mt2712_mm_id_tabwe[] = {
	{ .name = "cwk-mt2712-mm", .dwivew_data = (kewnew_uwong_t)&mm_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, cwk_mt2712_mm_id_tabwe);

static stwuct pwatfowm_dwivew cwk_mt2712_mm_dwv = {
	.pwobe = mtk_cwk_pdev_pwobe,
	.wemove_new = mtk_cwk_pdev_wemove,
	.dwivew = {
		.name = "cwk-mt2712-mm",
	},
	.id_tabwe = cwk_mt2712_mm_id_tabwe,
};
moduwe_pwatfowm_dwivew(cwk_mt2712_mm_dwv);
MODUWE_WICENSE("GPW");
