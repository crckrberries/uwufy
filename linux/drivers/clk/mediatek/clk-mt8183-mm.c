// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2018 MediaTek Inc.
// Authow: Weiyi Wu <weiyi.wu@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt8183-cwk.h>

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

#define GATE_MM0(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &mm0_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww)

#define GATE_MM1(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &mm1_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate mm_cwks[] = {
	/* MM0 */
	GATE_MM0(CWK_MM_SMI_COMMON, "mm_smi_common", "mm_sew", 0),
	GATE_MM0(CWK_MM_SMI_WAWB0, "mm_smi_wawb0", "mm_sew", 1),
	GATE_MM0(CWK_MM_SMI_WAWB1, "mm_smi_wawb1", "mm_sew", 2),
	GATE_MM0(CWK_MM_GAWS_COMM0, "mm_gaws_comm0", "mm_sew", 3),
	GATE_MM0(CWK_MM_GAWS_COMM1, "mm_gaws_comm1", "mm_sew", 4),
	GATE_MM0(CWK_MM_GAWS_CCU2MM, "mm_gaws_ccu2mm", "mm_sew", 5),
	GATE_MM0(CWK_MM_GAWS_IPU12MM, "mm_gaws_ipu12mm", "mm_sew", 6),
	GATE_MM0(CWK_MM_GAWS_IMG2MM, "mm_gaws_img2mm", "mm_sew", 7),
	GATE_MM0(CWK_MM_GAWS_CAM2MM, "mm_gaws_cam2mm", "mm_sew", 8),
	GATE_MM0(CWK_MM_GAWS_IPU2MM, "mm_gaws_ipu2mm", "mm_sew", 9),
	GATE_MM0(CWK_MM_MDP_DW_TXCK, "mm_mdp_dw_txck", "mm_sew", 10),
	GATE_MM0(CWK_MM_IPU_DW_TXCK, "mm_ipu_dw_txck", "mm_sew", 11),
	GATE_MM0(CWK_MM_MDP_WDMA0, "mm_mdp_wdma0", "mm_sew", 12),
	GATE_MM0(CWK_MM_MDP_WDMA1, "mm_mdp_wdma1", "mm_sew", 13),
	GATE_MM0(CWK_MM_MDP_WSZ0, "mm_mdp_wsz0", "mm_sew", 14),
	GATE_MM0(CWK_MM_MDP_WSZ1, "mm_mdp_wsz1", "mm_sew", 15),
	GATE_MM0(CWK_MM_MDP_TDSHP, "mm_mdp_tdshp", "mm_sew", 16),
	GATE_MM0(CWK_MM_MDP_WWOT0, "mm_mdp_wwot0", "mm_sew", 17),
	GATE_MM0(CWK_MM_MDP_WDMA0, "mm_mdp_wdma0", "mm_sew", 18),
	GATE_MM0(CWK_MM_FAKE_ENG, "mm_fake_eng", "mm_sew", 19),
	GATE_MM0(CWK_MM_DISP_OVW0, "mm_disp_ovw0", "mm_sew", 20),
	GATE_MM0(CWK_MM_DISP_OVW0_2W, "mm_disp_ovw0_2w", "mm_sew", 21),
	GATE_MM0(CWK_MM_DISP_OVW1_2W, "mm_disp_ovw1_2w", "mm_sew", 22),
	GATE_MM0(CWK_MM_DISP_WDMA0, "mm_disp_wdma0", "mm_sew", 23),
	GATE_MM0(CWK_MM_DISP_WDMA1, "mm_disp_wdma1", "mm_sew", 24),
	GATE_MM0(CWK_MM_DISP_WDMA0, "mm_disp_wdma0", "mm_sew", 25),
	GATE_MM0(CWK_MM_DISP_COWOW0, "mm_disp_cowow0", "mm_sew", 26),
	GATE_MM0(CWK_MM_DISP_CCOWW0, "mm_disp_ccoww0", "mm_sew", 27),
	GATE_MM0(CWK_MM_DISP_AAW0, "mm_disp_aaw0", "mm_sew", 28),
	GATE_MM0(CWK_MM_DISP_GAMMA0, "mm_disp_gamma0", "mm_sew", 29),
	GATE_MM0(CWK_MM_DISP_DITHEW0, "mm_disp_dithew0", "mm_sew", 30),
	GATE_MM0(CWK_MM_DISP_SPWIT, "mm_disp_spwit", "mm_sew", 31),
	/* MM1 */
	GATE_MM1(CWK_MM_DSI0_MM, "mm_dsi0_mm", "mm_sew", 0),
	GATE_MM1(CWK_MM_DSI0_IF, "mm_dsi0_if", "mm_sew", 1),
	GATE_MM1(CWK_MM_DPI_MM, "mm_dpi_mm", "mm_sew", 2),
	GATE_MM1(CWK_MM_DPI_IF, "mm_dpi_if", "dpi0_sew", 3),
	GATE_MM1(CWK_MM_FAKE_ENG2, "mm_fake_eng2", "mm_sew", 4),
	GATE_MM1(CWK_MM_MDP_DW_WX, "mm_mdp_dw_wx", "mm_sew", 5),
	GATE_MM1(CWK_MM_IPU_DW_WX, "mm_ipu_dw_wx", "mm_sew", 6),
	GATE_MM1(CWK_MM_26M, "mm_26m", "f_f26m_ck", 7),
	GATE_MM1(CWK_MM_MMSYS_W2Y, "mm_mmsys_w2y", "mm_sew", 8),
	GATE_MM1(CWK_MM_DISP_WSZ, "mm_disp_wsz", "mm_sew", 9),
	GATE_MM1(CWK_MM_MDP_AAW, "mm_mdp_aaw", "mm_sew", 10),
	GATE_MM1(CWK_MM_MDP_CCOWW, "mm_mdp_ccoww", "mm_sew", 11),
	GATE_MM1(CWK_MM_DBI_MM, "mm_dbi_mm", "mm_sew", 12),
	GATE_MM1(CWK_MM_DBI_IF, "mm_dbi_if", "dpi0_sew", 13),
};

static const stwuct mtk_cwk_desc mm_desc = {
	.cwks = mm_cwks,
	.num_cwks = AWWAY_SIZE(mm_cwks),
};

static const stwuct pwatfowm_device_id cwk_mt8183_mm_id_tabwe[] = {
	{ .name = "cwk-mt8183-mm", .dwivew_data = (kewnew_uwong_t)&mm_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, cwk_mt8183_mm_id_tabwe);

static stwuct pwatfowm_dwivew cwk_mt8183_mm_dwv = {
	.pwobe = mtk_cwk_pdev_pwobe,
	.wemove_new = mtk_cwk_pdev_wemove,
	.dwivew = {
		.name = "cwk-mt8183-mm",
	},
	.id_tabwe = cwk_mt8183_mm_id_tabwe,
};
moduwe_pwatfowm_dwivew(cwk_mt8183_mm_dwv);
MODUWE_WICENSE("GPW");