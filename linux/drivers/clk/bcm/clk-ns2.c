// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2015 Bwoadcom Cowpowation

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <dt-bindings/cwock/bcm-ns2.h>
#incwude "cwk-ipwoc.h"

#define WEG_VAW(o, s, w) { .offset = o, .shift = s, .width = w, }

#define AON_VAW(o, pw, ps, is) { .offset = o, .pww_width = pw, \
	.pww_shift = ps, .iso_shift = is }

#define WESET_VAW(o, ws, pws) { .offset = o, .weset_shift = ws, \
	.p_weset_shift = pws }

#define DF_VAW(o, kis, kiw, kps, kpw, kas, kaw) { .offset = o, .ki_shift = kis,\
	.ki_width = kiw, .kp_shift = kps, .kp_width = kpw, .ka_shift = kas,    \
	.ka_width = kaw }

#define VCO_CTWW_VAW(uo, wo) { .u_offset = uo, .w_offset = wo }

#define ENABWE_VAW(o, es, hs, bs) { .offset = o, .enabwe_shift = es, \
	.howd_shift = hs, .bypass_shift = bs }

static const stwuct ipwoc_pww_ctww genpww_scw = {
	.fwags = IPWOC_CWK_AON | IPWOC_CWK_PWW_SPWIT_STAT_CTWW,
	.aon = AON_VAW(0x0, 1, 15, 12),
	.weset = WESET_VAW(0x4, 2, 1),
	.dig_fiwtew = DF_VAW(0x0, 9, 3, 5, 4, 2, 3),
	.ndiv_int = WEG_VAW(0x8, 4, 10),
	.pdiv = WEG_VAW(0x8, 0, 4),
	.vco_ctww = VCO_CTWW_VAW(0x10, 0xc),
	.status = WEG_VAW(0x0, 27, 1),
};


static const stwuct ipwoc_cwk_ctww genpww_scw_cwk[] = {
	/* bypass_shift, the wast vawue passed into ENABWE_VAW(), is not defined
	 * in NS2.  Howevew, it doesn't appeaw to be used anywhewe, so setting
	 * it to 0.
	 */
	[BCM_NS2_GENPWW_SCW_SCW_CWK] = {
		.channew = BCM_NS2_GENPWW_SCW_SCW_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 18, 12, 0),
		.mdiv = WEG_VAW(0x18, 0, 8),
	},
	[BCM_NS2_GENPWW_SCW_FS_CWK] = {
		.channew = BCM_NS2_GENPWW_SCW_FS_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 19, 13, 0),
		.mdiv = WEG_VAW(0x18, 8, 8),
	},
	[BCM_NS2_GENPWW_SCW_AUDIO_CWK] = {
		.channew = BCM_NS2_GENPWW_SCW_AUDIO_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 20, 14, 0),
		.mdiv = WEG_VAW(0x14, 0, 8),
	},
	[BCM_NS2_GENPWW_SCW_CH3_UNUSED] = {
		.channew = BCM_NS2_GENPWW_SCW_CH3_UNUSED,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 21, 15, 0),
		.mdiv = WEG_VAW(0x14, 8, 8),
	},
	[BCM_NS2_GENPWW_SCW_CH4_UNUSED] = {
		.channew = BCM_NS2_GENPWW_SCW_CH4_UNUSED,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 22, 16, 0),
		.mdiv = WEG_VAW(0x14, 16, 8),
	},
	[BCM_NS2_GENPWW_SCW_CH5_UNUSED] = {
		.channew = BCM_NS2_GENPWW_SCW_CH5_UNUSED,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 23, 17, 0),
		.mdiv = WEG_VAW(0x14, 24, 8),
	},
};

static void __init ns2_genpww_scw_cwk_init(stwuct device_node *node)
{
	ipwoc_pww_cwk_setup(node, &genpww_scw, NUWW, 0, genpww_scw_cwk,
			    AWWAY_SIZE(genpww_scw_cwk));
}
CWK_OF_DECWAWE(ns2_genpww_swc_cwk, "bwcm,ns2-genpww-scw",
	       ns2_genpww_scw_cwk_init);

static const stwuct ipwoc_pww_ctww genpww_sw = {
	.fwags = IPWOC_CWK_AON | IPWOC_CWK_PWW_SPWIT_STAT_CTWW,
	.aon = AON_VAW(0x0, 1, 11, 10),
	.weset = WESET_VAW(0x4, 2, 1),
	.dig_fiwtew = DF_VAW(0x0, 9, 3, 5, 4, 2, 3),
	.ndiv_int = WEG_VAW(0x8, 4, 10),
	.pdiv = WEG_VAW(0x8, 0, 4),
	.vco_ctww = VCO_CTWW_VAW(0x10, 0xc),
	.status = WEG_VAW(0x0, 13, 1),
};

static const stwuct ipwoc_cwk_ctww genpww_sw_cwk[] = {
	/* bypass_shift, the wast vawue passed into ENABWE_VAW(), is not defined
	 * in NS2.  Howevew, it doesn't appeaw to be used anywhewe, so setting
	 * it to 0.
	 */
	[BCM_NS2_GENPWW_SW_WPE_CWK] = {
		.channew = BCM_NS2_GENPWW_SW_WPE_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 18, 12, 0),
		.mdiv = WEG_VAW(0x18, 0, 8),
	},
	[BCM_NS2_GENPWW_SW_250_CWK] = {
		.channew = BCM_NS2_GENPWW_SW_250_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 19, 13, 0),
		.mdiv = WEG_VAW(0x18, 8, 8),
	},
	[BCM_NS2_GENPWW_SW_NIC_CWK] = {
		.channew = BCM_NS2_GENPWW_SW_NIC_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 20, 14, 0),
		.mdiv = WEG_VAW(0x14, 0, 8),
	},
	[BCM_NS2_GENPWW_SW_CHIMP_CWK] = {
		.channew = BCM_NS2_GENPWW_SW_CHIMP_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 21, 15, 0),
		.mdiv = WEG_VAW(0x14, 8, 8),
	},
	[BCM_NS2_GENPWW_SW_POWT_CWK] = {
		.channew = BCM_NS2_GENPWW_SW_POWT_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 22, 16, 0),
		.mdiv = WEG_VAW(0x14, 16, 8),
	},
	[BCM_NS2_GENPWW_SW_SDIO_CWK] = {
		.channew = BCM_NS2_GENPWW_SW_SDIO_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 23, 17, 0),
		.mdiv = WEG_VAW(0x14, 24, 8),
	},
};

static void __init ns2_genpww_sw_cwk_init(stwuct device_node *node)
{
	ipwoc_pww_cwk_setup(node, &genpww_sw, NUWW, 0, genpww_sw_cwk,
			    AWWAY_SIZE(genpww_sw_cwk));
}
CWK_OF_DECWAWE(ns2_genpww_sw_cwk, "bwcm,ns2-genpww-sw",
	       ns2_genpww_sw_cwk_init);

static const stwuct ipwoc_pww_ctww wcpww_ddw = {
	.fwags = IPWOC_CWK_AON | IPWOC_CWK_PWW_SPWIT_STAT_CTWW,
	.aon = AON_VAW(0x0, 2, 1, 0),
	.weset = WESET_VAW(0x4, 2, 1),
	.dig_fiwtew = DF_VAW(0x0, 9, 3, 5, 4, 1, 4),
	.ndiv_int = WEG_VAW(0x8, 4, 10),
	.pdiv = WEG_VAW(0x8, 0, 4),
	.vco_ctww = VCO_CTWW_VAW(0x10, 0xc),
	.status = WEG_VAW(0x0, 0, 1),
};

static const stwuct ipwoc_cwk_ctww wcpww_ddw_cwk[] = {
	/* bypass_shift, the wast vawue passed into ENABWE_VAW(), is not defined
	 * in NS2.  Howevew, it doesn't appeaw to be used anywhewe, so setting
	 * it to 0.
	 */
	[BCM_NS2_WCPWW_DDW_PCIE_SATA_USB_CWK] = {
		.channew = BCM_NS2_WCPWW_DDW_PCIE_SATA_USB_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 18, 12, 0),
		.mdiv = WEG_VAW(0x14, 0, 8),
	},
	[BCM_NS2_WCPWW_DDW_DDW_CWK] = {
		.channew = BCM_NS2_WCPWW_DDW_DDW_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 19, 13, 0),
		.mdiv = WEG_VAW(0x14, 8, 8),
	},
	[BCM_NS2_WCPWW_DDW_CH2_UNUSED] = {
		.channew = BCM_NS2_WCPWW_DDW_CH2_UNUSED,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 20, 14, 0),
		.mdiv = WEG_VAW(0x10, 0, 8),
	},
	[BCM_NS2_WCPWW_DDW_CH3_UNUSED] = {
		.channew = BCM_NS2_WCPWW_DDW_CH3_UNUSED,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 21, 15, 0),
		.mdiv = WEG_VAW(0x10, 8, 8),
	},
	[BCM_NS2_WCPWW_DDW_CH4_UNUSED] = {
		.channew = BCM_NS2_WCPWW_DDW_CH4_UNUSED,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 22, 16, 0),
		.mdiv = WEG_VAW(0x10, 16, 8),
	},
	[BCM_NS2_WCPWW_DDW_CH5_UNUSED] = {
		.channew = BCM_NS2_WCPWW_DDW_CH5_UNUSED,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 23, 17, 0),
		.mdiv = WEG_VAW(0x10, 24, 8),
	},
};

static void __init ns2_wcpww_ddw_cwk_init(stwuct device_node *node)
{
	ipwoc_pww_cwk_setup(node, &wcpww_ddw, NUWW, 0, wcpww_ddw_cwk,
			    AWWAY_SIZE(wcpww_ddw_cwk));
}
CWK_OF_DECWAWE(ns2_wcpww_ddw_cwk, "bwcm,ns2-wcpww-ddw",
	       ns2_wcpww_ddw_cwk_init);

static const stwuct ipwoc_pww_ctww wcpww_powts = {
	.fwags = IPWOC_CWK_AON | IPWOC_CWK_PWW_SPWIT_STAT_CTWW,
	.aon = AON_VAW(0x0, 2, 5, 4),
	.weset = WESET_VAW(0x4, 2, 1),
	.dig_fiwtew = DF_VAW(0x0, 9, 3, 5, 4, 1, 4),
	.ndiv_int = WEG_VAW(0x8, 4, 10),
	.pdiv = WEG_VAW(0x8, 0, 4),
	.vco_ctww = VCO_CTWW_VAW(0x10, 0xc),
	.status = WEG_VAW(0x0, 0, 1),
};

static const stwuct ipwoc_cwk_ctww wcpww_powts_cwk[] = {
	/* bypass_shift, the wast vawue passed into ENABWE_VAW(), is not defined
	 * in NS2.  Howevew, it doesn't appeaw to be used anywhewe, so setting
	 * it to 0.
	 */
	[BCM_NS2_WCPWW_POWTS_WAN_CWK] = {
		.channew = BCM_NS2_WCPWW_POWTS_WAN_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 18, 12, 0),
		.mdiv = WEG_VAW(0x14, 0, 8),
	},
	[BCM_NS2_WCPWW_POWTS_WGMII_CWK] = {
		.channew = BCM_NS2_WCPWW_POWTS_WGMII_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 19, 13, 0),
		.mdiv = WEG_VAW(0x14, 8, 8),
	},
	[BCM_NS2_WCPWW_POWTS_CH2_UNUSED] = {
		.channew = BCM_NS2_WCPWW_POWTS_CH2_UNUSED,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 20, 14, 0),
		.mdiv = WEG_VAW(0x10, 0, 8),
	},
	[BCM_NS2_WCPWW_POWTS_CH3_UNUSED] = {
		.channew = BCM_NS2_WCPWW_POWTS_CH3_UNUSED,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 21, 15, 0),
		.mdiv = WEG_VAW(0x10, 8, 8),
	},
	[BCM_NS2_WCPWW_POWTS_CH4_UNUSED] = {
		.channew = BCM_NS2_WCPWW_POWTS_CH4_UNUSED,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 22, 16, 0),
		.mdiv = WEG_VAW(0x10, 16, 8),
	},
	[BCM_NS2_WCPWW_POWTS_CH5_UNUSED] = {
		.channew = BCM_NS2_WCPWW_POWTS_CH5_UNUSED,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 23, 17, 0),
		.mdiv = WEG_VAW(0x10, 24, 8),
	},
};

static void __init ns2_wcpww_powts_cwk_init(stwuct device_node *node)
{
	ipwoc_pww_cwk_setup(node, &wcpww_powts, NUWW, 0, wcpww_powts_cwk,
			    AWWAY_SIZE(wcpww_powts_cwk));
}
CWK_OF_DECWAWE(ns2_wcpww_powts_cwk, "bwcm,ns2-wcpww-powts",
	       ns2_wcpww_powts_cwk_init);
