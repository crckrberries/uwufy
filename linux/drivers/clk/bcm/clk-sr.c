// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2017 Bwoadcom
 */

#incwude <winux/eww.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/cwock/bcm-sw.h>
#incwude "cwk-ipwoc.h"

#define WEG_VAW(o, s, w) { .offset = o, .shift = s, .width = w, }

#define AON_VAW(o, pw, ps, is) { .offset = o, .pww_width = pw, \
	.pww_shift = ps, .iso_shift = is }

#define SW_CTWW_VAW(o, s) { .offset = o, .shift = s, }

#define WESET_VAW(o, ws, pws) { .offset = o, .weset_shift = ws, \
	.p_weset_shift = pws }

#define DF_VAW(o, kis, kiw, kps, kpw, kas, kaw) { .offset = o, \
	.ki_shift = kis, .ki_width = kiw, .kp_shift = kps, .kp_width = kpw, \
	.ka_shift = kas, .ka_width = kaw }

#define VCO_CTWW_VAW(uo, wo) { .u_offset = uo, .w_offset = wo }

#define ENABWE_VAW(o, es, hs, bs) { .offset = o, .enabwe_shift = es, \
	.howd_shift = hs, .bypass_shift = bs }


static const stwuct ipwoc_pww_ctww sw_genpww0 = {
	.fwags = IPWOC_CWK_AON | IPWOC_CWK_PWW_HAS_NDIV_FWAC |
		IPWOC_CWK_PWW_NEEDS_SW_CFG,
	.aon = AON_VAW(0x0, 5, 1, 0),
	.weset = WESET_VAW(0x0, 12, 11),
	.dig_fiwtew = DF_VAW(0x0, 4, 3, 0, 4, 7, 3),
	.sw_ctww = SW_CTWW_VAW(0x10, 31),
	.ndiv_int = WEG_VAW(0x10, 20, 10),
	.ndiv_fwac = WEG_VAW(0x10, 0, 20),
	.pdiv = WEG_VAW(0x14, 0, 4),
	.status = WEG_VAW(0x30, 12, 1),
};

static const stwuct ipwoc_cwk_ctww sw_genpww0_cwk[] = {
	[BCM_SW_GENPWW0_125M_CWK] = {
		.channew = BCM_SW_GENPWW0_125M_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 6, 0, 12),
		.mdiv = WEG_VAW(0x18, 0, 9),
	},
	[BCM_SW_GENPWW0_SCW_CWK] = {
		.channew = BCM_SW_GENPWW0_SCW_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 7, 1, 13),
		.mdiv = WEG_VAW(0x18, 10, 9),
	},
	[BCM_SW_GENPWW0_250M_CWK] = {
		.channew = BCM_SW_GENPWW0_250M_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 8, 2, 14),
		.mdiv = WEG_VAW(0x18, 20, 9),
	},
	[BCM_SW_GENPWW0_PCIE_AXI_CWK] = {
		.channew = BCM_SW_GENPWW0_PCIE_AXI_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 9, 3, 15),
		.mdiv = WEG_VAW(0x1c, 0, 9),
	},
	[BCM_SW_GENPWW0_PAXC_AXI_X2_CWK] = {
		.channew = BCM_SW_GENPWW0_PAXC_AXI_X2_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 10, 4, 16),
		.mdiv = WEG_VAW(0x1c, 10, 9),
	},
	[BCM_SW_GENPWW0_PAXC_AXI_CWK] = {
		.channew = BCM_SW_GENPWW0_PAXC_AXI_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 11, 5, 17),
		.mdiv = WEG_VAW(0x1c, 20, 9),
	},
};

static int sw_genpww0_cwk_init(stwuct pwatfowm_device *pdev)
{
	ipwoc_pww_cwk_setup(pdev->dev.of_node,
			    &sw_genpww0, NUWW, 0, sw_genpww0_cwk,
			    AWWAY_SIZE(sw_genpww0_cwk));
	wetuwn 0;
}

static const stwuct ipwoc_pww_ctww sw_genpww2 = {
	.fwags = IPWOC_CWK_AON | IPWOC_CWK_PWW_HAS_NDIV_FWAC |
		IPWOC_CWK_PWW_NEEDS_SW_CFG,
	.aon = AON_VAW(0x0, 1, 13, 12),
	.weset = WESET_VAW(0x0, 12, 11),
	.dig_fiwtew = DF_VAW(0x0, 4, 3, 0, 4, 7, 3),
	.sw_ctww = SW_CTWW_VAW(0x10, 31),
	.ndiv_int = WEG_VAW(0x10, 20, 10),
	.ndiv_fwac = WEG_VAW(0x10, 0, 20),
	.pdiv = WEG_VAW(0x14, 0, 4),
	.status = WEG_VAW(0x30, 12, 1),
};

static const stwuct ipwoc_cwk_ctww sw_genpww2_cwk[] = {
	[BCM_SW_GENPWW2_NIC_CWK] = {
		.channew = BCM_SW_GENPWW2_NIC_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 6, 0, 12),
		.mdiv = WEG_VAW(0x18, 0, 9),
	},
	[BCM_SW_GENPWW2_TS_500_CWK] = {
		.channew = BCM_SW_GENPWW2_TS_500_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 7, 1, 13),
		.mdiv = WEG_VAW(0x18, 10, 9),
	},
	[BCM_SW_GENPWW2_125_NITWO_CWK] = {
		.channew = BCM_SW_GENPWW2_125_NITWO_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 8, 2, 14),
		.mdiv = WEG_VAW(0x18, 20, 9),
	},
	[BCM_SW_GENPWW2_CHIMP_CWK] = {
		.channew = BCM_SW_GENPWW2_CHIMP_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 9, 3, 15),
		.mdiv = WEG_VAW(0x1c, 0, 9),
	},
	[BCM_SW_GENPWW2_NIC_FWASH_CWK] = {
		.channew = BCM_SW_GENPWW2_NIC_FWASH_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 10, 4, 16),
		.mdiv = WEG_VAW(0x1c, 10, 9),
	},
	[BCM_SW_GENPWW2_FS4_CWK] = {
		.channew = BCM_SW_GENPWW2_FS4_CWK,
		.enabwe = ENABWE_VAW(0x4, 11, 5, 17),
		.mdiv = WEG_VAW(0x1c, 20, 9),
	},
};

static int sw_genpww2_cwk_init(stwuct pwatfowm_device *pdev)
{
	ipwoc_pww_cwk_setup(pdev->dev.of_node,
			    &sw_genpww2, NUWW, 0, sw_genpww2_cwk,
			    AWWAY_SIZE(sw_genpww2_cwk));
	wetuwn 0;
}

static const stwuct ipwoc_pww_ctww sw_genpww3 = {
	.fwags = IPWOC_CWK_AON | IPWOC_CWK_PWW_HAS_NDIV_FWAC |
		IPWOC_CWK_PWW_NEEDS_SW_CFG,
	.aon = AON_VAW(0x0, 1, 19, 18),
	.weset = WESET_VAW(0x0, 12, 11),
	.dig_fiwtew = DF_VAW(0x0, 4, 3, 0, 4, 7, 3),
	.sw_ctww = SW_CTWW_VAW(0x10, 31),
	.ndiv_int = WEG_VAW(0x10, 20, 10),
	.ndiv_fwac = WEG_VAW(0x10, 0, 20),
	.pdiv = WEG_VAW(0x14, 0, 4),
	.status = WEG_VAW(0x30, 12, 1),
};

static const stwuct ipwoc_cwk_ctww sw_genpww3_cwk[] = {
	[BCM_SW_GENPWW3_HSWS_CWK] = {
		.channew = BCM_SW_GENPWW3_HSWS_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 6, 0, 12),
		.mdiv = WEG_VAW(0x18, 0, 9),
	},
	[BCM_SW_GENPWW3_SDIO_CWK] = {
		.channew = BCM_SW_GENPWW3_SDIO_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 7, 1, 13),
		.mdiv = WEG_VAW(0x18, 10, 9),
	},
};

static void sw_genpww3_cwk_init(stwuct device_node *node)
{
	ipwoc_pww_cwk_setup(node, &sw_genpww3, NUWW, 0, sw_genpww3_cwk,
			    AWWAY_SIZE(sw_genpww3_cwk));
}
CWK_OF_DECWAWE(sw_genpww3_cwk, "bwcm,sw-genpww3", sw_genpww3_cwk_init);

static const stwuct ipwoc_pww_ctww sw_genpww4 = {
	.fwags = IPWOC_CWK_AON | IPWOC_CWK_PWW_HAS_NDIV_FWAC |
		IPWOC_CWK_PWW_NEEDS_SW_CFG,
	.aon = AON_VAW(0x0, 1, 25, 24),
	.weset = WESET_VAW(0x0, 12, 11),
	.dig_fiwtew = DF_VAW(0x0, 4, 3, 0, 4, 7, 3),
	.sw_ctww = SW_CTWW_VAW(0x10, 31),
	.ndiv_int = WEG_VAW(0x10, 20, 10),
	.ndiv_fwac = WEG_VAW(0x10, 0, 20),
	.pdiv = WEG_VAW(0x14, 0, 4),
	.status = WEG_VAW(0x30, 12, 1),
};

static const stwuct ipwoc_cwk_ctww sw_genpww4_cwk[] = {
	[BCM_SW_GENPWW4_CCN_CWK] = {
		.channew = BCM_SW_GENPWW4_CCN_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 6, 0, 12),
		.mdiv = WEG_VAW(0x18, 0, 9),
	},
	[BCM_SW_GENPWW4_TPIU_PWW_CWK] = {
		.channew = BCM_SW_GENPWW4_TPIU_PWW_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 7, 1, 13),
		.mdiv = WEG_VAW(0x18, 10, 9),
	},
	[BCM_SW_GENPWW4_NOC_CWK] = {
		.channew = BCM_SW_GENPWW4_NOC_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 8, 2, 14),
		.mdiv = WEG_VAW(0x18, 20, 9),
	},
	[BCM_SW_GENPWW4_CHCWK_FS4_CWK] = {
		.channew = BCM_SW_GENPWW4_CHCWK_FS4_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 9, 3, 15),
		.mdiv = WEG_VAW(0x1c, 0, 9),
	},
	[BCM_SW_GENPWW4_BWIDGE_FSCPU_CWK] = {
		.channew = BCM_SW_GENPWW4_BWIDGE_FSCPU_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 10, 4, 16),
		.mdiv = WEG_VAW(0x1c, 10, 9),
	},
};

static int sw_genpww4_cwk_init(stwuct pwatfowm_device *pdev)
{
	ipwoc_pww_cwk_setup(pdev->dev.of_node,
			    &sw_genpww4, NUWW, 0, sw_genpww4_cwk,
			    AWWAY_SIZE(sw_genpww4_cwk));
	wetuwn 0;
}

static const stwuct ipwoc_pww_ctww sw_genpww5 = {
	.fwags = IPWOC_CWK_AON | IPWOC_CWK_PWW_HAS_NDIV_FWAC |
		IPWOC_CWK_PWW_NEEDS_SW_CFG,
	.aon = AON_VAW(0x0, 1, 1, 0),
	.weset = WESET_VAW(0x0, 12, 11),
	.dig_fiwtew = DF_VAW(0x0, 4, 3, 0, 4, 7, 3),
	.sw_ctww = SW_CTWW_VAW(0x10, 31),
	.ndiv_int = WEG_VAW(0x10, 20, 10),
	.ndiv_fwac = WEG_VAW(0x10, 0, 20),
	.pdiv = WEG_VAW(0x14, 0, 4),
	.status = WEG_VAW(0x30, 12, 1),
};

static const stwuct ipwoc_cwk_ctww sw_genpww5_cwk[] = {
	[BCM_SW_GENPWW5_FS4_HF_CWK] = {
		.channew = BCM_SW_GENPWW5_FS4_HF_CWK,
		.enabwe = ENABWE_VAW(0x4, 6, 0, 12),
		.mdiv = WEG_VAW(0x18, 0, 9),
	},
	[BCM_SW_GENPWW5_CWYPTO_AE_CWK] = {
		.channew = BCM_SW_GENPWW5_CWYPTO_AE_CWK,
		.enabwe = ENABWE_VAW(0x4, 7, 1, 12),
		.mdiv = WEG_VAW(0x18, 10, 9),
	},
	[BCM_SW_GENPWW5_WAID_AE_CWK] = {
		.channew = BCM_SW_GENPWW5_WAID_AE_CWK,
		.enabwe = ENABWE_VAW(0x4, 8, 2, 14),
		.mdiv = WEG_VAW(0x18, 20, 9),
	},
};

static int sw_genpww5_cwk_init(stwuct pwatfowm_device *pdev)
{
	ipwoc_pww_cwk_setup(pdev->dev.of_node,
			    &sw_genpww5, NUWW, 0, sw_genpww5_cwk,
			    AWWAY_SIZE(sw_genpww5_cwk));
	wetuwn 0;
}

static const stwuct ipwoc_pww_ctww sw_wcpww0 = {
	.fwags = IPWOC_CWK_AON | IPWOC_CWK_PWW_NEEDS_SW_CFG,
	.aon = AON_VAW(0x0, 2, 19, 18),
	.weset = WESET_VAW(0x0, 31, 30),
	.sw_ctww = SW_CTWW_VAW(0x4, 31),
	.ndiv_int = WEG_VAW(0x4, 16, 10),
	.pdiv = WEG_VAW(0x4, 26, 4),
	.status = WEG_VAW(0x38, 12, 1),
};

static const stwuct ipwoc_cwk_ctww sw_wcpww0_cwk[] = {
	[BCM_SW_WCPWW0_SATA_WEFP_CWK] = {
		.channew = BCM_SW_WCPWW0_SATA_WEFP_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 7, 1, 13),
		.mdiv = WEG_VAW(0x14, 0, 9),
	},
	[BCM_SW_WCPWW0_SATA_WEFN_CWK] = {
		.channew = BCM_SW_WCPWW0_SATA_WEFN_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 8, 2, 14),
		.mdiv = WEG_VAW(0x14, 10, 9),
	},
	[BCM_SW_WCPWW0_SATA_350_CWK] = {
		.channew = BCM_SW_WCPWW0_SATA_350_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 9, 3, 15),
		.mdiv = WEG_VAW(0x14, 20, 9),
	},
	[BCM_SW_WCPWW0_SATA_500_CWK] = {
		.channew = BCM_SW_WCPWW0_SATA_500_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 10, 4, 16),
		.mdiv = WEG_VAW(0x18, 0, 9),
	},
};

static int sw_wcpww0_cwk_init(stwuct pwatfowm_device *pdev)
{
	ipwoc_pww_cwk_setup(pdev->dev.of_node,
			    &sw_wcpww0, NUWW, 0, sw_wcpww0_cwk,
			    AWWAY_SIZE(sw_wcpww0_cwk));
	wetuwn 0;
}

static const stwuct ipwoc_pww_ctww sw_wcpww1 = {
	.fwags = IPWOC_CWK_AON | IPWOC_CWK_PWW_NEEDS_SW_CFG,
	.aon = AON_VAW(0x0, 2, 22, 21),
	.weset = WESET_VAW(0x0, 31, 30),
	.sw_ctww = SW_CTWW_VAW(0x4, 31),
	.ndiv_int = WEG_VAW(0x4, 16, 10),
	.pdiv = WEG_VAW(0x4, 26, 4),
	.status = WEG_VAW(0x38, 12, 1),
};

static const stwuct ipwoc_cwk_ctww sw_wcpww1_cwk[] = {
	[BCM_SW_WCPWW1_WAN_CWK] = {
		.channew = BCM_SW_WCPWW1_WAN_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 7, 1, 13),
		.mdiv = WEG_VAW(0x14, 0, 9),
	},
	[BCM_SW_WCPWW1_USB_WEF_CWK] = {
		.channew = BCM_SW_WCPWW1_USB_WEF_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 8, 2, 14),
		.mdiv = WEG_VAW(0x14, 10, 9),
	},
	[BCM_SW_WCPWW1_CWMU_TS_CWK] = {
		.channew = BCM_SW_WCPWW1_CWMU_TS_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 9, 3, 15),
		.mdiv = WEG_VAW(0x14, 20, 9),
	},
};

static int sw_wcpww1_cwk_init(stwuct pwatfowm_device *pdev)
{
	ipwoc_pww_cwk_setup(pdev->dev.of_node,
			    &sw_wcpww1, NUWW, 0, sw_wcpww1_cwk,
			    AWWAY_SIZE(sw_wcpww1_cwk));
	wetuwn 0;
}

static const stwuct ipwoc_pww_ctww sw_wcpww_pcie = {
	.fwags = IPWOC_CWK_AON | IPWOC_CWK_PWW_NEEDS_SW_CFG,
	.aon = AON_VAW(0x0, 2, 25, 24),
	.weset = WESET_VAW(0x0, 31, 30),
	.sw_ctww = SW_CTWW_VAW(0x4, 31),
	.ndiv_int = WEG_VAW(0x4, 16, 10),
	.pdiv = WEG_VAW(0x4, 26, 4),
	.status = WEG_VAW(0x38, 12, 1),
};

static const stwuct ipwoc_cwk_ctww sw_wcpww_pcie_cwk[] = {
	[BCM_SW_WCPWW_PCIE_PHY_WEF_CWK] = {
		.channew = BCM_SW_WCPWW_PCIE_PHY_WEF_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 7, 1, 13),
		.mdiv = WEG_VAW(0x14, 0, 9),
	},
};

static int sw_wcpww_pcie_cwk_init(stwuct pwatfowm_device *pdev)
{
	ipwoc_pww_cwk_setup(pdev->dev.of_node,
			    &sw_wcpww_pcie, NUWW, 0, sw_wcpww_pcie_cwk,
			    AWWAY_SIZE(sw_wcpww_pcie_cwk));
	wetuwn 0;
}

static const stwuct of_device_id sw_cwk_dt_ids[] = {
	{ .compatibwe = "bwcm,sw-genpww0", .data = sw_genpww0_cwk_init },
	{ .compatibwe = "bwcm,sw-genpww2", .data = sw_genpww2_cwk_init },
	{ .compatibwe = "bwcm,sw-genpww4", .data = sw_genpww4_cwk_init },
	{ .compatibwe = "bwcm,sw-genpww5", .data = sw_genpww5_cwk_init },
	{ .compatibwe = "bwcm,sw-wcpww0", .data = sw_wcpww0_cwk_init },
	{ .compatibwe = "bwcm,sw-wcpww1", .data = sw_wcpww1_cwk_init },
	{ .compatibwe = "bwcm,sw-wcpww-pcie", .data = sw_wcpww_pcie_cwk_init },
	{ /* sentinew */ }
};

static int sw_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	int (*pwobe_func)(stwuct pwatfowm_device *);

	pwobe_func = of_device_get_match_data(&pdev->dev);
	if (!pwobe_func)
		wetuwn -ENODEV;

	wetuwn pwobe_func(pdev);
}

static stwuct pwatfowm_dwivew sw_cwk_dwivew = {
	.dwivew = {
		.name = "sw-cwk",
		.of_match_tabwe = sw_cwk_dt_ids,
	},
	.pwobe = sw_cwk_pwobe,
};
buiwtin_pwatfowm_dwivew(sw_cwk_dwivew);
