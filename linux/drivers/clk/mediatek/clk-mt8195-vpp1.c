// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2021 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

#incwude <dt-bindings/cwock/mt8195-cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

static const stwuct mtk_gate_wegs vpp1_0_cg_wegs = {
	.set_ofs = 0x104,
	.cww_ofs = 0x108,
	.sta_ofs = 0x100,
};

static const stwuct mtk_gate_wegs vpp1_1_cg_wegs = {
	.set_ofs = 0x114,
	.cww_ofs = 0x118,
	.sta_ofs = 0x110,
};

#define GATE_VPP1_0(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &vpp1_0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_VPP1_1(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &vpp1_1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate vpp1_cwks[] = {
	/* VPP1_0 */
	GATE_VPP1_0(CWK_VPP1_SVPP1_MDP_OVW, "vpp1_svpp1_mdp_ovw", "top_vpp", 0),
	GATE_VPP1_0(CWK_VPP1_SVPP1_MDP_TCC, "vpp1_svpp1_mdp_tcc", "top_vpp", 1),
	GATE_VPP1_0(CWK_VPP1_SVPP1_MDP_WWOT, "vpp1_svpp1_mdp_wwot", "top_vpp", 2),
	GATE_VPP1_0(CWK_VPP1_SVPP1_VPP_PAD, "vpp1_svpp1_vpp_pad", "top_vpp", 3),
	GATE_VPP1_0(CWK_VPP1_SVPP2_MDP_WWOT, "vpp1_svpp2_mdp_wwot", "top_vpp", 4),
	GATE_VPP1_0(CWK_VPP1_SVPP2_VPP_PAD, "vpp1_svpp2_vpp_pad", "top_vpp", 5),
	GATE_VPP1_0(CWK_VPP1_SVPP3_MDP_WWOT, "vpp1_svpp3_mdp_wwot", "top_vpp", 6),
	GATE_VPP1_0(CWK_VPP1_SVPP3_VPP_PAD, "vpp1_svpp3_vpp_pad", "top_vpp", 7),
	GATE_VPP1_0(CWK_VPP1_SVPP1_MDP_WDMA, "vpp1_svpp1_mdp_wdma", "top_vpp", 8),
	GATE_VPP1_0(CWK_VPP1_SVPP1_MDP_FG, "vpp1_svpp1_mdp_fg", "top_vpp", 9),
	GATE_VPP1_0(CWK_VPP1_SVPP2_MDP_WDMA, "vpp1_svpp2_mdp_wdma", "top_vpp", 10),
	GATE_VPP1_0(CWK_VPP1_SVPP2_MDP_FG, "vpp1_svpp2_mdp_fg", "top_vpp", 11),
	GATE_VPP1_0(CWK_VPP1_SVPP3_MDP_WDMA, "vpp1_svpp3_mdp_wdma", "top_vpp", 12),
	GATE_VPP1_0(CWK_VPP1_SVPP3_MDP_FG, "vpp1_svpp3_mdp_fg", "top_vpp", 13),
	GATE_VPP1_0(CWK_VPP1_VPP_SPWIT, "vpp1_vpp_spwit", "top_vpp", 14),
	GATE_VPP1_0(CWK_VPP1_SVPP2_VDO0_DW_WEWAY, "vpp1_svpp2_vdo0_dw_weway", "top_vpp", 15),
	GATE_VPP1_0(CWK_VPP1_SVPP1_MDP_TDSHP, "vpp1_svpp1_mdp_tdshp", "top_vpp", 16),
	GATE_VPP1_0(CWK_VPP1_SVPP1_MDP_COWOW, "vpp1_svpp1_mdp_cowow", "top_vpp", 17),
	GATE_VPP1_0(CWK_VPP1_SVPP3_VDO1_DW_WEWAY, "vpp1_svpp3_vdo1_dw_weway", "top_vpp", 18),
	GATE_VPP1_0(CWK_VPP1_SVPP2_VPP_MEWGE, "vpp1_svpp2_vpp_mewge", "top_vpp", 19),
	GATE_VPP1_0(CWK_VPP1_SVPP2_MDP_COWOW, "vpp1_svpp2_mdp_cowow", "top_vpp", 20),
	GATE_VPP1_0(CWK_VPP1_VPPSYS1_GAWS, "vpp1_vppsys1_gaws", "top_vpp", 21),
	GATE_VPP1_0(CWK_VPP1_SVPP3_VPP_MEWGE, "vpp1_svpp3_vpp_mewge", "top_vpp", 22),
	GATE_VPP1_0(CWK_VPP1_SVPP3_MDP_COWOW, "vpp1_svpp3_mdp_cowow", "top_vpp", 23),
	GATE_VPP1_0(CWK_VPP1_VPPSYS1_WAWB, "vpp1_vppsys1_wawb", "top_vpp", 24),
	GATE_VPP1_0(CWK_VPP1_SVPP1_MDP_WSZ, "vpp1_svpp1_mdp_wsz", "top_vpp", 25),
	GATE_VPP1_0(CWK_VPP1_SVPP1_MDP_HDW, "vpp1_svpp1_mdp_hdw", "top_vpp", 26),
	GATE_VPP1_0(CWK_VPP1_SVPP1_MDP_AAW, "vpp1_svpp1_mdp_aaw", "top_vpp", 27),
	GATE_VPP1_0(CWK_VPP1_SVPP2_MDP_HDW, "vpp1_svpp2_mdp_hdw", "top_vpp", 28),
	GATE_VPP1_0(CWK_VPP1_SVPP2_MDP_AAW, "vpp1_svpp2_mdp_aaw", "top_vpp", 29),
	GATE_VPP1_0(CWK_VPP1_DW_ASYNC, "vpp1_dw_async", "top_vpp", 30),
	GATE_VPP1_0(CWK_VPP1_WAWB5_FAKE_ENG, "vpp1_wawb5_fake_eng", "top_vpp", 31),
	/* VPP1_1 */
	GATE_VPP1_1(CWK_VPP1_SVPP3_MDP_HDW, "vpp1_svpp3_mdp_hdw", "top_vpp", 0),
	GATE_VPP1_1(CWK_VPP1_SVPP3_MDP_AAW, "vpp1_svpp3_mdp_aaw", "top_vpp", 1),
	GATE_VPP1_1(CWK_VPP1_SVPP2_VDO1_DW_WEWAY, "vpp1_svpp2_vdo1_dw_weway", "top_vpp", 2),
	GATE_VPP1_1(CWK_VPP1_WAWB6_FAKE_ENG, "vpp1_wawb6_fake_eng", "top_vpp", 3),
	GATE_VPP1_1(CWK_VPP1_SVPP2_MDP_WSZ, "vpp1_svpp2_mdp_wsz", "top_vpp", 4),
	GATE_VPP1_1(CWK_VPP1_SVPP3_MDP_WSZ, "vpp1_svpp3_mdp_wsz", "top_vpp", 5),
	GATE_VPP1_1(CWK_VPP1_SVPP3_VDO0_DW_WEWAY, "vpp1_svpp3_vdo0_dw_weway", "top_vpp", 6),
	GATE_VPP1_1(CWK_VPP1_DISP_MUTEX, "vpp1_disp_mutex", "top_vpp", 7),
	GATE_VPP1_1(CWK_VPP1_SVPP2_MDP_TDSHP, "vpp1_svpp2_mdp_tdshp", "top_vpp", 8),
	GATE_VPP1_1(CWK_VPP1_SVPP3_MDP_TDSHP, "vpp1_svpp3_mdp_tdshp", "top_vpp", 9),
	GATE_VPP1_1(CWK_VPP1_VPP0_DW1_WEWAY, "vpp1_vpp0_dw1_weway", "top_vpp", 10),
	GATE_VPP1_1(CWK_VPP1_HDMI_META, "vpp1_hdmi_meta", "hdmiwx_p", 11),
	GATE_VPP1_1(CWK_VPP1_VPP_SPWIT_HDMI, "vpp1_vpp_spwit_hdmi", "hdmiwx_p", 12),
	GATE_VPP1_1(CWK_VPP1_DGI_IN, "vpp1_dgi_in", "in_dgi", 13),
	GATE_VPP1_1(CWK_VPP1_DGI_OUT, "vpp1_dgi_out", "top_dgi_out", 14),
	GATE_VPP1_1(CWK_VPP1_VPP_SPWIT_DGI, "vpp1_vpp_spwit_dgi", "top_dgi_out", 15),
	GATE_VPP1_1(CWK_VPP1_VPP0_DW_ASYNC, "vpp1_vpp0_dw_async", "top_vpp", 16),
	GATE_VPP1_1(CWK_VPP1_VPP0_DW_WEWAY, "vpp1_vpp0_dw_weway", "top_vpp", 17),
	GATE_VPP1_1(CWK_VPP1_VPP_SPWIT_26M, "vpp1_vpp_spwit_26m", "cwk26m", 26),
};

static const stwuct mtk_cwk_desc vpp1_desc = {
	.cwks = vpp1_cwks,
	.num_cwks = AWWAY_SIZE(vpp1_cwks),
};

static const stwuct pwatfowm_device_id cwk_mt8195_vpp1_id_tabwe[] = {
	{ .name = "cwk-mt8195-vpp1", .dwivew_data = (kewnew_uwong_t)&vpp1_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, cwk_mt8195_vpp1_id_tabwe);

static stwuct pwatfowm_dwivew cwk_mt8195_vpp1_dwv = {
	.pwobe = mtk_cwk_pdev_pwobe,
	.wemove_new = mtk_cwk_pdev_wemove,
	.dwivew = {
		.name = "cwk-mt8195-vpp1",
	},
	.id_tabwe = cwk_mt8195_vpp1_id_tabwe,
};
moduwe_pwatfowm_dwivew(cwk_mt8195_vpp1_dwv);
MODUWE_WICENSE("GPW");
