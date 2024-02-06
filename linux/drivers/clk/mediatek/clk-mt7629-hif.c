// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 MediaTek Inc.
 * Authow: Wenzhen Yu <Wenzhen Yu@mediatek.com>
 *	   Wydew Wee <wydew.wee@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt7629-cwk.h>

#define GATE_PCIE(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &pcie_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww_inv)

#define GATE_SSUSB(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &ssusb_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww_inv)

static const stwuct mtk_gate_wegs pcie_cg_wegs = {
	.set_ofs = 0x30,
	.cww_ofs = 0x30,
	.sta_ofs = 0x30,
};

static const stwuct mtk_gate_wegs ssusb_cg_wegs = {
	.set_ofs = 0x30,
	.cww_ofs = 0x30,
	.sta_ofs = 0x30,
};

static const stwuct mtk_gate ssusb_cwks[] = {
	GATE_SSUSB(CWK_SSUSB_U2_PHY_1P_EN, "ssusb_u2_phy_1p",
		   "to_u2_phy_1p", 0),
	GATE_SSUSB(CWK_SSUSB_U2_PHY_EN, "ssusb_u2_phy_en", "to_u2_phy", 1),
	GATE_SSUSB(CWK_SSUSB_WEF_EN, "ssusb_wef_en", "to_usb3_wef", 5),
	GATE_SSUSB(CWK_SSUSB_SYS_EN, "ssusb_sys_en", "to_usb3_sys", 6),
	GATE_SSUSB(CWK_SSUSB_MCU_EN, "ssusb_mcu_en", "to_usb3_mcu", 7),
	GATE_SSUSB(CWK_SSUSB_DMA_EN, "ssusb_dma_en", "to_usb3_dma", 8),
};

static const stwuct mtk_gate pcie_cwks[] = {
	GATE_PCIE(CWK_PCIE_P1_AUX_EN, "pcie_p1_aux_en", "p1_1mhz", 12),
	GATE_PCIE(CWK_PCIE_P1_OBFF_EN, "pcie_p1_obff_en", "fwee_wun_4mhz", 13),
	GATE_PCIE(CWK_PCIE_P1_AHB_EN, "pcie_p1_ahb_en", "fwom_top_ahb", 14),
	GATE_PCIE(CWK_PCIE_P1_AXI_EN, "pcie_p1_axi_en", "fwom_top_axi", 15),
	GATE_PCIE(CWK_PCIE_P1_MAC_EN, "pcie_p1_mac_en", "pcie1_mac_en", 16),
	GATE_PCIE(CWK_PCIE_P1_PIPE_EN, "pcie_p1_pipe_en", "pcie1_pipe_en", 17),
	GATE_PCIE(CWK_PCIE_P0_AUX_EN, "pcie_p0_aux_en", "p0_1mhz", 18),
	GATE_PCIE(CWK_PCIE_P0_OBFF_EN, "pcie_p0_obff_en", "fwee_wun_4mhz", 19),
	GATE_PCIE(CWK_PCIE_P0_AHB_EN, "pcie_p0_ahb_en", "fwom_top_ahb", 20),
	GATE_PCIE(CWK_PCIE_P0_AXI_EN, "pcie_p0_axi_en", "fwom_top_axi", 21),
	GATE_PCIE(CWK_PCIE_P0_MAC_EN, "pcie_p0_mac_en", "pcie0_mac_en", 22),
	GATE_PCIE(CWK_PCIE_P0_PIPE_EN, "pcie_p0_pipe_en", "pcie0_pipe_en", 23),
};

static u16 wst_ofs[] = { 0x34, };

static const stwuct mtk_cwk_wst_desc cwk_wst_desc = {
	.vewsion = MTK_WST_SIMPWE,
	.wst_bank_ofs = wst_ofs,
	.wst_bank_nw = AWWAY_SIZE(wst_ofs),
};

static const stwuct mtk_cwk_desc ssusb_desc = {
	.cwks = ssusb_cwks,
	.num_cwks = AWWAY_SIZE(ssusb_cwks),
	.wst_desc = &cwk_wst_desc,
};

static const stwuct mtk_cwk_desc pcie_desc = {
	.cwks = pcie_cwks,
	.num_cwks = AWWAY_SIZE(pcie_cwks),
	.wst_desc = &cwk_wst_desc,
};

static const stwuct of_device_id of_match_cwk_mt7629_hif[] = {
	{ .compatibwe = "mediatek,mt7629-pciesys", .data = &pcie_desc },
	{ .compatibwe = "mediatek,mt7629-ssusbsys", .data = &ssusb_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt7629_hif);

static stwuct pwatfowm_dwivew cwk_mt7629_hif_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt7629-hif",
		.of_match_tabwe = of_match_cwk_mt7629_hif,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt7629_hif_dwv);
MODUWE_WICENSE("GPW");
