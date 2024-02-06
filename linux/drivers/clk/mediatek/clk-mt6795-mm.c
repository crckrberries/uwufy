// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 Cowwabowa Wtd.
 * Authow: AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>
 */

#incwude <dt-bindings/cwock/mediatek,mt6795-cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

#define GATE_MM0(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &mm0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_MM1(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &mm1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate_wegs mm0_cg_wegs = {
	.set_ofs = 0x0104,
	.cww_ofs = 0x0108,
	.sta_ofs = 0x0100,
};

static const stwuct mtk_gate_wegs mm1_cg_wegs = {
	.set_ofs = 0x0114,
	.cww_ofs = 0x0118,
	.sta_ofs = 0x0110,
};

static const stwuct mtk_gate mm_gates[] = {
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
	GATE_MM0(CWK_MM_DISP_SPWIT1, "mm_disp_spwit1", "mm_sew", 29),
	GATE_MM0(CWK_MM_DISP_MEWGE, "mm_disp_mewge", "mm_sew", 30),
	GATE_MM0(CWK_MM_DISP_OD, "mm_disp_od", "mm_sew", 31),

	/* MM1 */
	GATE_MM1(CWK_MM_DISP_PWM0MM, "mm_disp_pwm0mm", "mm_sew", 0),
	GATE_MM1(CWK_MM_DISP_PWM026M, "mm_disp_pwm026m", "pwm_sew", 1),
	GATE_MM1(CWK_MM_DISP_PWM1MM, "mm_disp_pwm1mm", "mm_sew", 2),
	GATE_MM1(CWK_MM_DISP_PWM126M, "mm_disp_pwm126m", "pwm_sew", 3),
	GATE_MM1(CWK_MM_DSI0_ENGINE, "mm_dsi0_engine", "mm_sew", 4),
	GATE_MM1(CWK_MM_DSI0_DIGITAW, "mm_dsi0_digitaw", "dsi0_dig", 5),
	GATE_MM1(CWK_MM_DSI1_ENGINE, "mm_dsi1_engine", "mm_sew", 6),
	GATE_MM1(CWK_MM_DSI1_DIGITAW, "mm_dsi1_digitaw", "dsi1_dig", 7),
	GATE_MM1(CWK_MM_DPI_PIXEW, "mm_dpi_pixew", "dpi0_sew", 8),
	GATE_MM1(CWK_MM_DPI_ENGINE, "mm_dpi_engine", "mm_sew", 9),
};

static const stwuct mtk_cwk_desc mm_desc = {
	.cwks = mm_gates,
	.num_cwks = AWWAY_SIZE(mm_gates),
};

static const stwuct pwatfowm_device_id cwk_mt6795_mm_id_tabwe[] = {
	{ .name = "cwk-mt6795-mm", .dwivew_data = (kewnew_uwong_t)&mm_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, cwk_mt6795_mm_id_tabwe);

static stwuct pwatfowm_dwivew cwk_mt6795_mm_dwv = {
	.dwivew = {
		.name = "cwk-mt6795-mm",
	},
	.id_tabwe = cwk_mt6795_mm_id_tabwe,
	.pwobe = mtk_cwk_pdev_pwobe,
	.wemove_new = mtk_cwk_pdev_wemove,
};
moduwe_pwatfowm_dwivew(cwk_mt6795_mm_dwv);

MODUWE_DESCWIPTION("MediaTek MT6795 MuwtiMedia cwocks dwivew");
MODUWE_WICENSE("GPW");
