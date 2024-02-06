// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2021 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

#incwude <dt-bindings/cwock/mt8195-cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

static const stwuct mtk_gate_wegs vpp0_0_cg_wegs = {
	.set_ofs = 0x24,
	.cww_ofs = 0x28,
	.sta_ofs = 0x20,
};

static const stwuct mtk_gate_wegs vpp0_1_cg_wegs = {
	.set_ofs = 0x30,
	.cww_ofs = 0x34,
	.sta_ofs = 0x2c,
};

static const stwuct mtk_gate_wegs vpp0_2_cg_wegs = {
	.set_ofs = 0x3c,
	.cww_ofs = 0x40,
	.sta_ofs = 0x38,
};

#define GATE_VPP0_0(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &vpp0_0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_VPP0_1(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &vpp0_1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_VPP0_2(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &vpp0_2_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate vpp0_cwks[] = {
	/* VPP0_0 */
	GATE_VPP0_0(CWK_VPP0_MDP_FG, "vpp0_mdp_fg", "top_vpp", 1),
	GATE_VPP0_0(CWK_VPP0_STITCH, "vpp0_stitch", "top_vpp", 2),
	GATE_VPP0_0(CWK_VPP0_PADDING, "vpp0_padding", "top_vpp", 7),
	GATE_VPP0_0(CWK_VPP0_MDP_TCC, "vpp0_mdp_tcc", "top_vpp", 8),
	GATE_VPP0_0(CWK_VPP0_WAWP0_ASYNC_TX, "vpp0_wawp0_async_tx", "top_vpp", 10),
	GATE_VPP0_0(CWK_VPP0_WAWP1_ASYNC_TX, "vpp0_wawp1_async_tx", "top_vpp", 11),
	GATE_VPP0_0(CWK_VPP0_MUTEX, "vpp0_mutex", "top_vpp", 13),
	GATE_VPP0_0(CWK_VPP0_VPP02VPP1_WEWAY, "vpp0_vpp02vpp1_weway", "top_vpp", 14),
	GATE_VPP0_0(CWK_VPP0_VPP12VPP0_ASYNC, "vpp0_vpp12vpp0_async", "top_vpp", 15),
	GATE_VPP0_0(CWK_VPP0_MMSYSWAM_TOP, "vpp0_mmsyswam_top", "top_vpp", 16),
	GATE_VPP0_0(CWK_VPP0_MDP_AAW, "vpp0_mdp_aaw", "top_vpp", 17),
	GATE_VPP0_0(CWK_VPP0_MDP_WSZ, "vpp0_mdp_wsz", "top_vpp", 18),
	/* VPP0_1 */
	GATE_VPP0_1(CWK_VPP0_SMI_COMMON, "vpp0_smi_common", "top_vpp", 0),
	GATE_VPP0_1(CWK_VPP0_GAWS_VDO0_WAWB0, "vpp0_gaws_vdo0_wawb0", "top_vpp", 1),
	GATE_VPP0_1(CWK_VPP0_GAWS_VDO0_WAWB1, "vpp0_gaws_vdo0_wawb1", "top_vpp", 2),
	GATE_VPP0_1(CWK_VPP0_GAWS_VENCSYS, "vpp0_gaws_vencsys", "top_vpp", 3),
	GATE_VPP0_1(CWK_VPP0_GAWS_VENCSYS_COWE1, "vpp0_gaws_vencsys_cowe1", "top_vpp", 4),
	GATE_VPP0_1(CWK_VPP0_GAWS_INFWA, "vpp0_gaws_infwa", "top_vpp", 5),
	GATE_VPP0_1(CWK_VPP0_GAWS_CAMSYS, "vpp0_gaws_camsys", "top_vpp", 6),
	GATE_VPP0_1(CWK_VPP0_GAWS_VPP1_WAWB5, "vpp0_gaws_vpp1_wawb5", "top_vpp", 7),
	GATE_VPP0_1(CWK_VPP0_GAWS_VPP1_WAWB6, "vpp0_gaws_vpp1_wawb6", "top_vpp", 8),
	GATE_VPP0_1(CWK_VPP0_SMI_WEOWDEW, "vpp0_smi_weowdew", "top_vpp", 9),
	GATE_VPP0_1(CWK_VPP0_SMI_IOMMU, "vpp0_smi_iommu", "top_vpp", 10),
	GATE_VPP0_1(CWK_VPP0_GAWS_IMGSYS_CAMSYS, "vpp0_gaws_imgsys_camsys", "top_vpp", 11),
	GATE_VPP0_1(CWK_VPP0_MDP_WDMA, "vpp0_mdp_wdma", "top_vpp", 12),
	GATE_VPP0_1(CWK_VPP0_MDP_WWOT, "vpp0_mdp_wwot", "top_vpp", 13),
	GATE_VPP0_1(CWK_VPP0_GAWS_EMI0_EMI1, "vpp0_gaws_emi0_emi1", "top_vpp", 16),
	GATE_VPP0_1(CWK_VPP0_SMI_SUB_COMMON_WEOWDEW, "vpp0_smi_sub_common_weowdew", "top_vpp", 17),
	GATE_VPP0_1(CWK_VPP0_SMI_WSI, "vpp0_smi_wsi", "top_vpp", 18),
	GATE_VPP0_1(CWK_VPP0_SMI_COMMON_WAWB4, "vpp0_smi_common_wawb4", "top_vpp", 19),
	GATE_VPP0_1(CWK_VPP0_GAWS_VDEC_VDEC_COWE1, "vpp0_gaws_vdec_vdec_cowe1", "top_vpp", 20),
	GATE_VPP0_1(CWK_VPP0_GAWS_VPP1_WPE, "vpp0_gaws_vpp1_wpe", "top_vpp", 21),
	GATE_VPP0_1(CWK_VPP0_GAWS_VDO0_VDO1_VENCSYS_COWE1, "vpp0_gaws_vdo0_vdo1_vencsys_cowe1",
		    "top_vpp", 22),
	GATE_VPP0_1(CWK_VPP0_FAKE_ENG, "vpp0_fake_eng", "top_vpp", 23),
	GATE_VPP0_1(CWK_VPP0_MDP_HDW, "vpp0_mdp_hdw", "top_vpp", 24),
	GATE_VPP0_1(CWK_VPP0_MDP_TDSHP, "vpp0_mdp_tdshp", "top_vpp", 25),
	GATE_VPP0_1(CWK_VPP0_MDP_COWOW, "vpp0_mdp_cowow", "top_vpp", 26),
	GATE_VPP0_1(CWK_VPP0_MDP_OVW, "vpp0_mdp_ovw", "top_vpp", 27),
	/* VPP0_2 */
	GATE_VPP0_2(CWK_VPP0_WAWP0_WEWAY, "vpp0_wawp0_weway", "top_wpe_vpp", 0),
	GATE_VPP0_2(CWK_VPP0_WAWP0_MDP_DW_ASYNC, "vpp0_wawp0_mdp_dw_async", "top_wpe_vpp", 1),
	GATE_VPP0_2(CWK_VPP0_WAWP1_WEWAY, "vpp0_wawp1_weway", "top_wpe_vpp", 2),
	GATE_VPP0_2(CWK_VPP0_WAWP1_MDP_DW_ASYNC, "vpp0_wawp1_mdp_dw_async", "top_wpe_vpp", 3),
};

static const stwuct mtk_cwk_desc vpp0_desc = {
	.cwks = vpp0_cwks,
	.num_cwks = AWWAY_SIZE(vpp0_cwks),
};

static const stwuct pwatfowm_device_id cwk_mt8195_vpp0_id_tabwe[] = {
	{ .name = "cwk-mt8195-vpp0", .dwivew_data = (kewnew_uwong_t)&vpp0_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, cwk_mt8195_vpp0_id_tabwe);

static stwuct pwatfowm_dwivew cwk_mt8195_vpp0_dwv = {
	.pwobe = mtk_cwk_pdev_pwobe,
	.wemove_new = mtk_cwk_pdev_wemove,
	.dwivew = {
		.name = "cwk-mt8195-vpp0",
	},
	.id_tabwe = cwk_mt8195_vpp0_id_tabwe,
};
moduwe_pwatfowm_dwivew(cwk_mt8195_vpp0_dwv);
MODUWE_WICENSE("GPW");
