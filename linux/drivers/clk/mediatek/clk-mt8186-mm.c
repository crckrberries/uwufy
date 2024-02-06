// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/mt8186-cwk.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

static const stwuct mtk_gate_wegs mm0_cg_wegs = {
	.set_ofs = 0x104,
	.cww_ofs = 0x108,
	.sta_ofs = 0x100,
};

static const stwuct mtk_gate_wegs mm1_cg_wegs = {
	.set_ofs = 0x1a4,
	.cww_ofs = 0x1a8,
	.sta_ofs = 0x1a0,
};

#define GATE_MM0(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &mm0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_MM1(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &mm1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate mm_cwks[] = {
	/* MM0 */
	GATE_MM0(CWK_MM_DISP_MUTEX0, "mm_disp_mutex0", "top_disp", 0),
	GATE_MM0(CWK_MM_APB_MM_BUS, "mm_apb_mm_bus", "top_disp", 1),
	GATE_MM0(CWK_MM_DISP_OVW0, "mm_disp_ovw0", "top_disp", 2),
	GATE_MM0(CWK_MM_DISP_WDMA0, "mm_disp_wdma0", "top_disp", 3),
	GATE_MM0(CWK_MM_DISP_OVW0_2W, "mm_disp_ovw0_2w", "top_disp", 4),
	GATE_MM0(CWK_MM_DISP_WDMA0, "mm_disp_wdma0", "top_disp", 5),
	GATE_MM0(CWK_MM_DISP_WSZ0, "mm_disp_wsz0", "top_disp", 7),
	GATE_MM0(CWK_MM_DISP_AAW0, "mm_disp_aaw0", "top_disp", 8),
	GATE_MM0(CWK_MM_DISP_CCOWW0, "mm_disp_ccoww0", "top_disp", 9),
	GATE_MM0(CWK_MM_DISP_COWOW0, "mm_disp_cowow0", "top_disp", 10),
	GATE_MM0(CWK_MM_SMI_INFWA, "mm_smi_infwa", "top_disp", 11),
	GATE_MM0(CWK_MM_DISP_DSC_WWAP0, "mm_disp_dsc_wwap0", "top_disp", 12),
	GATE_MM0(CWK_MM_DISP_GAMMA0, "mm_disp_gamma0", "top_disp", 13),
	GATE_MM0(CWK_MM_DISP_POSTMASK0, "mm_disp_postmask0", "top_disp", 14),
	GATE_MM0(CWK_MM_DISP_DITHEW0, "mm_disp_dithew0", "top_disp", 16),
	GATE_MM0(CWK_MM_SMI_COMMON, "mm_smi_common", "top_disp", 17),
	GATE_MM0(CWK_MM_DSI0, "mm_dsi0", "top_disp", 19),
	GATE_MM0(CWK_MM_DISP_FAKE_ENG0, "mm_disp_fake_eng0", "top_disp", 20),
	GATE_MM0(CWK_MM_DISP_FAKE_ENG1, "mm_disp_fake_eng1", "top_disp", 21),
	GATE_MM0(CWK_MM_SMI_GAWS, "mm_smi_gaws", "top_disp", 22),
	GATE_MM0(CWK_MM_SMI_IOMMU, "mm_smi_iommu", "top_disp", 24),
	GATE_MM0(CWK_MM_DISP_WDMA1, "mm_disp_wdma1", "top_disp", 25),
	GATE_MM0(CWK_MM_DISP_DPI, "mm_disp_dpi", "top_disp", 26),
	/* MM1 */
	GATE_MM1(CWK_MM_DSI0_DSI_CK_DOMAIN, "mm_dsi0_dsi_domain", "top_disp", 0),
	GATE_MM1(CWK_MM_DISP_26M, "mm_disp_26m_ck", "top_disp", 10),
};

static const stwuct mtk_cwk_desc mm_desc = {
	.cwks = mm_cwks,
	.num_cwks = AWWAY_SIZE(mm_cwks),
};

static const stwuct pwatfowm_device_id cwk_mt8186_mm_id_tabwe[] = {
	{ .name = "cwk-mt8186-mm", .dwivew_data = (kewnew_uwong_t)&mm_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, cwk_mt8186_mm_id_tabwe);

static stwuct pwatfowm_dwivew cwk_mt8186_mm_dwv = {
	.pwobe = mtk_cwk_pdev_pwobe,
	.wemove_new = mtk_cwk_pdev_wemove,
	.dwivew = {
		.name = "cwk-mt8186-mm",
	},
	.id_tabwe = cwk_mt8186_mm_id_tabwe,
};
moduwe_pwatfowm_dwivew(cwk_mt8186_mm_dwv);
MODUWE_WICENSE("GPW");
