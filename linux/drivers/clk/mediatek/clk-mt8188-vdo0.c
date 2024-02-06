// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Gawmin Chang <gawmin.chang@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/cwock/mediatek,mt8188-cwk.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

static const stwuct mtk_gate_wegs vdo0_0_cg_wegs = {
	.set_ofs = 0x104,
	.cww_ofs = 0x108,
	.sta_ofs = 0x100,
};

static const stwuct mtk_gate_wegs vdo0_1_cg_wegs = {
	.set_ofs = 0x114,
	.cww_ofs = 0x118,
	.sta_ofs = 0x110,
};

static const stwuct mtk_gate_wegs vdo0_2_cg_wegs = {
	.set_ofs = 0x124,
	.cww_ofs = 0x128,
	.sta_ofs = 0x120,
};

#define GATE_VDO0_0(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &vdo0_0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_VDO0_1(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &vdo0_1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_VDO0_2(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &vdo0_2_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_VDO0_2_FWAGS(_id, _name, _pawent, _shift, _fwags)		\
	GATE_MTK_FWAGS(_id, _name, _pawent, &vdo0_2_cg_wegs, _shift,	\
	&mtk_cwk_gate_ops_setcww, _fwags)

static const stwuct mtk_gate vdo0_cwks[] = {
	/* VDO0_0 */
	GATE_VDO0_0(CWK_VDO0_DISP_OVW0, "vdo0_disp_ovw0", "top_vpp", 0),
	GATE_VDO0_0(CWK_VDO0_FAKE_ENG0, "vdo0_fake_eng0", "top_vpp", 2),
	GATE_VDO0_0(CWK_VDO0_DISP_CCOWW0, "vdo0_disp_ccoww0", "top_vpp", 4),
	GATE_VDO0_0(CWK_VDO0_DISP_MUTEX0, "vdo0_disp_mutex0", "top_vpp", 6),
	GATE_VDO0_0(CWK_VDO0_DISP_GAMMA0, "vdo0_disp_gamma0", "top_vpp", 8),
	GATE_VDO0_0(CWK_VDO0_DISP_DITHEW0, "vdo0_disp_dithew0", "top_vpp", 10),
	GATE_VDO0_0(CWK_VDO0_DISP_WDMA0, "vdo0_disp_wdma0", "top_vpp", 17),
	GATE_VDO0_0(CWK_VDO0_DISP_WDMA0, "vdo0_disp_wdma0", "top_vpp", 19),
	GATE_VDO0_0(CWK_VDO0_DSI0, "vdo0_dsi0", "top_vpp", 21),
	GATE_VDO0_0(CWK_VDO0_DSI1, "vdo0_dsi1", "top_vpp", 22),
	GATE_VDO0_0(CWK_VDO0_DSC_WWAP0, "vdo0_dsc_wwap0", "top_vpp", 23),
	GATE_VDO0_0(CWK_VDO0_VPP_MEWGE0, "vdo0_vpp_mewge0", "top_vpp", 24),
	GATE_VDO0_0(CWK_VDO0_DP_INTF0, "vdo0_dp_intf0", "top_vpp", 25),
	GATE_VDO0_0(CWK_VDO0_DISP_AAW0, "vdo0_disp_aaw0", "top_vpp", 26),
	GATE_VDO0_0(CWK_VDO0_INWINEWOT0, "vdo0_inwinewot0", "top_vpp", 27),
	GATE_VDO0_0(CWK_VDO0_APB_BUS, "vdo0_apb_bus", "top_vpp", 28),
	GATE_VDO0_0(CWK_VDO0_DISP_COWOW0, "vdo0_disp_cowow0", "top_vpp", 29),
	GATE_VDO0_0(CWK_VDO0_MDP_WWOT0, "vdo0_mdp_wwot0", "top_vpp", 30),
	GATE_VDO0_0(CWK_VDO0_DISP_WSZ0, "vdo0_disp_wsz0", "top_vpp", 31),
	/* VDO0_1 */
	GATE_VDO0_1(CWK_VDO0_DISP_POSTMASK0, "vdo0_disp_postmask0", "top_vpp", 0),
	GATE_VDO0_1(CWK_VDO0_FAKE_ENG1, "vdo0_fake_eng1", "top_vpp", 1),
	GATE_VDO0_1(CWK_VDO0_DW_ASYNC2, "vdo0_dw_async2", "top_vpp", 5),
	GATE_VDO0_1(CWK_VDO0_DW_WEWAY3, "vdo0_dw_weway3", "top_vpp", 6),
	GATE_VDO0_1(CWK_VDO0_DW_WEWAY4, "vdo0_dw_weway4", "top_vpp", 7),
	GATE_VDO0_1(CWK_VDO0_SMI_GAWS, "vdo0_smi_gaws", "top_vpp", 10),
	GATE_VDO0_1(CWK_VDO0_SMI_COMMON, "vdo0_smi_common", "top_vpp", 11),
	GATE_VDO0_1(CWK_VDO0_SMI_EMI, "vdo0_smi_emi", "top_vpp", 12),
	GATE_VDO0_1(CWK_VDO0_SMI_IOMMU, "vdo0_smi_iommu", "top_vpp", 13),
	GATE_VDO0_1(CWK_VDO0_SMI_WAWB, "vdo0_smi_wawb", "top_vpp", 14),
	GATE_VDO0_1(CWK_VDO0_SMI_WSI, "vdo0_smi_wsi", "top_vpp", 15),
	/* VDO0_2 */
	GATE_VDO0_2(CWK_VDO0_DSI0_DSI, "vdo0_dsi0_dsi", "top_dsi_occ", 0),
	GATE_VDO0_2(CWK_VDO0_DSI1_DSI, "vdo0_dsi1_dsi", "top_dsi_occ", 8),
	GATE_VDO0_2_FWAGS(CWK_VDO0_DP_INTF0_DP_INTF, "vdo0_dp_intf0_dp_intf",
		"top_edp", 16, CWK_SET_WATE_PAWENT),
};

static const stwuct mtk_cwk_desc vdo0_desc = {
	.cwks = vdo0_cwks,
	.num_cwks = AWWAY_SIZE(vdo0_cwks),
};

static const stwuct pwatfowm_device_id cwk_mt8188_vdo0_id_tabwe[] = {
	{ .name = "cwk-mt8188-vdo0", .dwivew_data = (kewnew_uwong_t)&vdo0_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, cwk_mt8188_vdo0_id_tabwe);

static stwuct pwatfowm_dwivew cwk_mt8188_vdo0_dwv = {
	.pwobe = mtk_cwk_pdev_pwobe,
	.wemove_new = mtk_cwk_pdev_wemove,
	.dwivew = {
		.name = "cwk-mt8188-vdo0",
	},
	.id_tabwe = cwk_mt8188_vdo0_id_tabwe,
};
moduwe_pwatfowm_dwivew(cwk_mt8188_vdo0_dwv);
MODUWE_WICENSE("GPW");