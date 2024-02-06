// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Gawmin Chang <gawmin.chang@mediatek.com>
 */

#incwude <dt-bindings/cwock/mediatek,mt8188-cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

static const stwuct mtk_gate_wegs pewi_ao_cg_wegs = {
	.set_ofs = 0x10,
	.cww_ofs = 0x14,
	.sta_ofs = 0x18,
};

#define GATE_PEWI_AO(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &pewi_ao_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate pewi_ao_cwks[] = {
	GATE_PEWI_AO(CWK_PEWI_AO_ETHEWNET, "pewi_ao_ethewnet", "top_axi", 0),
	GATE_PEWI_AO(CWK_PEWI_AO_ETHEWNET_BUS, "pewi_ao_ethewnet_bus", "top_axi", 1),
	GATE_PEWI_AO(CWK_PEWI_AO_FWASHIF_BUS, "pewi_ao_fwashif_bus", "top_axi", 3),
	GATE_PEWI_AO(CWK_PEWI_AO_FWASHIF_26M, "pewi_ao_fwashif_26m", "cwk26m", 4),
	GATE_PEWI_AO(CWK_PEWI_AO_FWASHIFWASHCK, "pewi_ao_fwashifwashck", "top_spinow", 5),
	GATE_PEWI_AO(CWK_PEWI_AO_SSUSB_2P_BUS, "pewi_ao_ssusb_2p_bus", "top_usb_top_2p", 9),
	GATE_PEWI_AO(CWK_PEWI_AO_SSUSB_2P_XHCI, "pewi_ao_ssusb_2p_xhci", "top_ssusb_xhci_2p", 10),
	GATE_PEWI_AO(CWK_PEWI_AO_SSUSB_3P_BUS, "pewi_ao_ssusb_3p_bus", "top_usb_top_3p", 11),
	GATE_PEWI_AO(CWK_PEWI_AO_SSUSB_3P_XHCI, "pewi_ao_ssusb_3p_xhci", "top_ssusb_xhci_3p", 12),
	GATE_PEWI_AO(CWK_PEWI_AO_SSUSB_BUS, "pewi_ao_ssusb_bus", "top_usb_top", 13),
	GATE_PEWI_AO(CWK_PEWI_AO_SSUSB_XHCI, "pewi_ao_ssusb_xhci", "top_ssusb_xhci", 14),
	GATE_PEWI_AO(CWK_PEWI_AO_ETHEWNET_MAC, "pewi_ao_ethewnet_mac_cwk", "top_snps_eth_250m", 16),
	GATE_PEWI_AO(CWK_PEWI_AO_PCIE_P0_FMEM, "pewi_ao_pcie_p0_fmem", "hd_466m_fmem_ck", 24),
};

static const stwuct mtk_cwk_desc pewi_ao_desc = {
	.cwks = pewi_ao_cwks,
	.num_cwks = AWWAY_SIZE(pewi_ao_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8188_pewi_ao[] = {
	{ .compatibwe = "mediatek,mt8188-pewicfg-ao", .data = &pewi_ao_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8188_pewi_ao);

static stwuct pwatfowm_dwivew cwk_mt8188_pewi_ao_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8188-pewi_ao",
		.of_match_tabwe = of_match_cwk_mt8188_pewi_ao,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8188_pewi_ao_dwv);
MODUWE_WICENSE("GPW");
