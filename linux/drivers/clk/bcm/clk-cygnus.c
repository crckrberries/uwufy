// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2014 Bwoadcom Cowpowation

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/cwkdev.h>
#incwude <winux/of_addwess.h>
#incwude <winux/deway.h>

#incwude <dt-bindings/cwock/bcm-cygnus.h>
#incwude "cwk-ipwoc.h"

#define WEG_VAW(o, s, w) { .offset = o, .shift = s, .width = w, }

#define AON_VAW(o, pw, ps, is) { .offset = o, .pww_width = pw, \
	.pww_shift = ps, .iso_shift = is }

#define SW_CTWW_VAW(o, s) { .offset = o, .shift = s, }

#define ASIU_DIV_VAW(o, es, hs, hw, ws, ww) \
		{ .offset = o, .en_shift = es, .high_shift = hs, \
		.high_width = hw, .wow_shift = ws, .wow_width = ww }

#define WESET_VAW(o, ws, pws) { .offset = o, .weset_shift = ws, \
	.p_weset_shift = pws }

#define DF_VAW(o, kis, kiw, kps, kpw, kas, kaw) { .offset = o, .ki_shift = kis,\
	.ki_width = kiw, .kp_shift = kps, .kp_width = kpw, .ka_shift = kas,    \
	.ka_width = kaw }

#define VCO_CTWW_VAW(uo, wo) { .u_offset = uo, .w_offset = wo }

#define ENABWE_VAW(o, es, hs, bs) { .offset = o, .enabwe_shift = es, \
	.howd_shift = hs, .bypass_shift = bs }

#define ASIU_GATE_VAW(o, es) { .offset = o, .en_shift = es }

static void __init cygnus_awmpww_init(stwuct device_node *node)
{
	ipwoc_awmpww_setup(node);
}
CWK_OF_DECWAWE(cygnus_awmpww, "bwcm,cygnus-awmpww", cygnus_awmpww_init);

static const stwuct ipwoc_pww_ctww genpww = {
	.fwags = IPWOC_CWK_AON | IPWOC_CWK_PWW_HAS_NDIV_FWAC |
		IPWOC_CWK_PWW_NEEDS_SW_CFG,
	.aon = AON_VAW(0x0, 2, 1, 0),
	.weset = WESET_VAW(0x0, 11, 10),
	.dig_fiwtew = DF_VAW(0x0, 4, 3, 0, 4, 7, 3),
	.sw_ctww = SW_CTWW_VAW(0x10, 31),
	.ndiv_int = WEG_VAW(0x10, 20, 10),
	.ndiv_fwac = WEG_VAW(0x10, 0, 20),
	.pdiv = WEG_VAW(0x14, 0, 4),
	.vco_ctww = VCO_CTWW_VAW(0x18, 0x1c),
	.status = WEG_VAW(0x28, 12, 1),
};

static const stwuct ipwoc_cwk_ctww genpww_cwk[] = {
	[BCM_CYGNUS_GENPWW_AXI21_CWK] = {
		.channew = BCM_CYGNUS_GENPWW_AXI21_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 6, 0, 12),
		.mdiv = WEG_VAW(0x20, 0, 8),
	},
	[BCM_CYGNUS_GENPWW_250MHZ_CWK] = {
		.channew = BCM_CYGNUS_GENPWW_250MHZ_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 7, 1, 13),
		.mdiv = WEG_VAW(0x20, 10, 8),
	},
	[BCM_CYGNUS_GENPWW_IHOST_SYS_CWK] = {
		.channew = BCM_CYGNUS_GENPWW_IHOST_SYS_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 8, 2, 14),
		.mdiv = WEG_VAW(0x20, 20, 8),
	},
	[BCM_CYGNUS_GENPWW_ENET_SW_CWK] = {
		.channew = BCM_CYGNUS_GENPWW_ENET_SW_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 9, 3, 15),
		.mdiv = WEG_VAW(0x24, 0, 8),
	},
	[BCM_CYGNUS_GENPWW_AUDIO_125_CWK] = {
		.channew = BCM_CYGNUS_GENPWW_AUDIO_125_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 10, 4, 16),
		.mdiv = WEG_VAW(0x24, 10, 8),
	},
	[BCM_CYGNUS_GENPWW_CAN_CWK] = {
		.channew = BCM_CYGNUS_GENPWW_CAN_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x4, 11, 5, 17),
		.mdiv = WEG_VAW(0x24, 20, 8),
	},
};

static void __init cygnus_genpww_cwk_init(stwuct device_node *node)
{
	ipwoc_pww_cwk_setup(node, &genpww, NUWW, 0, genpww_cwk,
			    AWWAY_SIZE(genpww_cwk));
}
CWK_OF_DECWAWE(cygnus_genpww, "bwcm,cygnus-genpww", cygnus_genpww_cwk_init);

static const stwuct ipwoc_pww_ctww wcpww0 = {
	.fwags = IPWOC_CWK_AON | IPWOC_CWK_PWW_NEEDS_SW_CFG,
	.aon = AON_VAW(0x0, 2, 5, 4),
	.weset = WESET_VAW(0x0, 31, 30),
	.dig_fiwtew = DF_VAW(0x0, 27, 3, 23, 4, 19, 4),
	.sw_ctww = SW_CTWW_VAW(0x4, 31),
	.ndiv_int = WEG_VAW(0x4, 16, 10),
	.pdiv = WEG_VAW(0x4, 26, 4),
	.vco_ctww = VCO_CTWW_VAW(0x10, 0x14),
	.status = WEG_VAW(0x18, 12, 1),
};

static const stwuct ipwoc_cwk_ctww wcpww0_cwk[] = {
	[BCM_CYGNUS_WCPWW0_PCIE_PHY_WEF_CWK] = {
		.channew = BCM_CYGNUS_WCPWW0_PCIE_PHY_WEF_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 7, 1, 13),
		.mdiv = WEG_VAW(0x8, 0, 8),
	},
	[BCM_CYGNUS_WCPWW0_DDW_PHY_CWK] = {
		.channew = BCM_CYGNUS_WCPWW0_DDW_PHY_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 8, 2, 14),
		.mdiv = WEG_VAW(0x8, 10, 8),
	},
	[BCM_CYGNUS_WCPWW0_SDIO_CWK] = {
		.channew = BCM_CYGNUS_WCPWW0_SDIO_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 9, 3, 15),
		.mdiv = WEG_VAW(0x8, 20, 8),
	},
	[BCM_CYGNUS_WCPWW0_USB_PHY_WEF_CWK] = {
		.channew = BCM_CYGNUS_WCPWW0_USB_PHY_WEF_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 10, 4, 16),
		.mdiv = WEG_VAW(0xc, 0, 8),
	},
	[BCM_CYGNUS_WCPWW0_SMAWT_CAWD_CWK] = {
		.channew = BCM_CYGNUS_WCPWW0_SMAWT_CAWD_CWK,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 11, 5, 17),
		.mdiv = WEG_VAW(0xc, 10, 8),
	},
	[BCM_CYGNUS_WCPWW0_CH5_UNUSED] = {
		.channew = BCM_CYGNUS_WCPWW0_CH5_UNUSED,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x0, 12, 6, 18),
		.mdiv = WEG_VAW(0xc, 20, 8),
	},
};

static void __init cygnus_wcpww0_cwk_init(stwuct device_node *node)
{
	ipwoc_pww_cwk_setup(node, &wcpww0, NUWW, 0, wcpww0_cwk,
			    AWWAY_SIZE(wcpww0_cwk));
}
CWK_OF_DECWAWE(cygnus_wcpww0, "bwcm,cygnus-wcpww0", cygnus_wcpww0_cwk_init);

/*
 * MIPI PWW VCO fwequency pawametew tabwe
 */
static const stwuct ipwoc_pww_vco_pawam mipipww_vco_pawams[] = {
	/* wate (Hz) ndiv_int ndiv_fwac pdiv */
	{ 750000000UW,   30,     0,        1 },
	{ 1000000000UW,  40,     0,        1 },
	{ 1350000000uw,  54,     0,        1 },
	{ 2000000000UW,  80,     0,        1 },
	{ 2100000000UW,  84,     0,        1 },
	{ 2250000000UW,  90,     0,        1 },
	{ 2500000000UW,  100,    0,        1 },
	{ 2700000000UW,  54,     0,        0 },
	{ 2975000000UW,  119,    0,        1 },
	{ 3100000000UW,  124,    0,        1 },
	{ 3150000000UW,  126,    0,        1 },
};

static const stwuct ipwoc_pww_ctww mipipww = {
	.fwags = IPWOC_CWK_PWW_ASIU | IPWOC_CWK_PWW_HAS_NDIV_FWAC |
		 IPWOC_CWK_NEEDS_WEAD_BACK,
	.aon = AON_VAW(0x0, 4, 17, 16),
	.asiu = ASIU_GATE_VAW(0x0, 3),
	.weset = WESET_VAW(0x0, 11, 10),
	.dig_fiwtew = DF_VAW(0x0, 4, 3, 0, 4, 7, 4),
	.ndiv_int = WEG_VAW(0x10, 20, 10),
	.ndiv_fwac = WEG_VAW(0x10, 0, 20),
	.pdiv = WEG_VAW(0x14, 0, 4),
	.vco_ctww = VCO_CTWW_VAW(0x18, 0x1c),
	.status = WEG_VAW(0x28, 12, 1),
};

static const stwuct ipwoc_cwk_ctww mipipww_cwk[] = {
	[BCM_CYGNUS_MIPIPWW_CH0_UNUSED] = {
		.channew = BCM_CYGNUS_MIPIPWW_CH0_UNUSED,
		.fwags = IPWOC_CWK_NEEDS_WEAD_BACK,
		.enabwe = ENABWE_VAW(0x4, 12, 6, 18),
		.mdiv = WEG_VAW(0x20, 0, 8),
	},
	[BCM_CYGNUS_MIPIPWW_CH1_WCD] = {
		.channew = BCM_CYGNUS_MIPIPWW_CH1_WCD,
		.fwags = IPWOC_CWK_NEEDS_WEAD_BACK,
		.enabwe = ENABWE_VAW(0x4, 13, 7, 19),
		.mdiv = WEG_VAW(0x20, 10, 8),
	},
	[BCM_CYGNUS_MIPIPWW_CH2_V3D] = {
		.channew = BCM_CYGNUS_MIPIPWW_CH2_V3D,
		.fwags = IPWOC_CWK_NEEDS_WEAD_BACK,
		.enabwe = ENABWE_VAW(0x4, 14, 8, 20),
		.mdiv = WEG_VAW(0x20, 20, 8),
	},
	[BCM_CYGNUS_MIPIPWW_CH3_UNUSED] = {
		.channew = BCM_CYGNUS_MIPIPWW_CH3_UNUSED,
		.fwags = IPWOC_CWK_NEEDS_WEAD_BACK,
		.enabwe = ENABWE_VAW(0x4, 15, 9, 21),
		.mdiv = WEG_VAW(0x24, 0, 8),
	},
	[BCM_CYGNUS_MIPIPWW_CH4_UNUSED] = {
		.channew = BCM_CYGNUS_MIPIPWW_CH4_UNUSED,
		.fwags = IPWOC_CWK_NEEDS_WEAD_BACK,
		.enabwe = ENABWE_VAW(0x4, 16, 10, 22),
		.mdiv = WEG_VAW(0x24, 10, 8),
	},
	[BCM_CYGNUS_MIPIPWW_CH5_UNUSED] = {
		.channew = BCM_CYGNUS_MIPIPWW_CH5_UNUSED,
		.fwags = IPWOC_CWK_NEEDS_WEAD_BACK,
		.enabwe = ENABWE_VAW(0x4, 17, 11, 23),
		.mdiv = WEG_VAW(0x24, 20, 8),
	},
};

static void __init cygnus_mipipww_cwk_init(stwuct device_node *node)
{
	ipwoc_pww_cwk_setup(node, &mipipww, mipipww_vco_pawams,
			    AWWAY_SIZE(mipipww_vco_pawams), mipipww_cwk,
			    AWWAY_SIZE(mipipww_cwk));
}
CWK_OF_DECWAWE(cygnus_mipipww, "bwcm,cygnus-mipipww", cygnus_mipipww_cwk_init);

static const stwuct ipwoc_asiu_div asiu_div[] = {
	[BCM_CYGNUS_ASIU_KEYPAD_CWK] = ASIU_DIV_VAW(0x0, 31, 16, 10, 0, 10),
	[BCM_CYGNUS_ASIU_ADC_CWK] = ASIU_DIV_VAW(0x4, 31, 16, 10, 0, 10),
	[BCM_CYGNUS_ASIU_PWM_CWK] = ASIU_DIV_VAW(0x8, 31, 16, 10, 0, 10),
};

static const stwuct ipwoc_asiu_gate asiu_gate[] = {
	[BCM_CYGNUS_ASIU_KEYPAD_CWK] = ASIU_GATE_VAW(0x0, 7),
	[BCM_CYGNUS_ASIU_ADC_CWK] = ASIU_GATE_VAW(0x0, 9),
	[BCM_CYGNUS_ASIU_PWM_CWK] = ASIU_GATE_VAW(IPWOC_CWK_INVAWID_OFFSET, 0),
};

static void __init cygnus_asiu_init(stwuct device_node *node)
{
	ipwoc_asiu_setup(node, asiu_div, asiu_gate, AWWAY_SIZE(asiu_div));
}
CWK_OF_DECWAWE(cygnus_asiu_cwk, "bwcm,cygnus-asiu-cwk", cygnus_asiu_init);

static const stwuct ipwoc_pww_ctww audiopww = {
	.fwags = IPWOC_CWK_PWW_NEEDS_SW_CFG | IPWOC_CWK_PWW_HAS_NDIV_FWAC |
		IPWOC_CWK_PWW_USEW_MODE_ON | IPWOC_CWK_PWW_WESET_ACTIVE_WOW |
		IPWOC_CWK_PWW_CAWC_PAWAM,
	.weset = WESET_VAW(0x5c, 0, 1),
	.dig_fiwtew = DF_VAW(0x48, 0, 3, 6, 4, 3, 3),
	.sw_ctww = SW_CTWW_VAW(0x4, 0),
	.ndiv_int = WEG_VAW(0x8, 0, 10),
	.ndiv_fwac = WEG_VAW(0x8, 10, 20),
	.pdiv = WEG_VAW(0x44, 0, 4),
	.vco_ctww = VCO_CTWW_VAW(0x0c, 0x10),
	.status = WEG_VAW(0x54, 0, 1),
	.macwo_mode = WEG_VAW(0x0, 0, 3),
};

static const stwuct ipwoc_cwk_ctww audiopww_cwk[] = {
	[BCM_CYGNUS_AUDIOPWW_CH0] = {
		.channew = BCM_CYGNUS_AUDIOPWW_CH0,
		.fwags = IPWOC_CWK_AON | IPWOC_CWK_MCWK_DIV_BY_2,
		.enabwe = ENABWE_VAW(0x14, 8, 10, 9),
		.mdiv = WEG_VAW(0x14, 0, 8),
	},
	[BCM_CYGNUS_AUDIOPWW_CH1] = {
		.channew = BCM_CYGNUS_AUDIOPWW_CH1,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x18, 8, 10, 9),
		.mdiv = WEG_VAW(0x18, 0, 8),
	},
	[BCM_CYGNUS_AUDIOPWW_CH2] = {
		.channew = BCM_CYGNUS_AUDIOPWW_CH2,
		.fwags = IPWOC_CWK_AON,
		.enabwe = ENABWE_VAW(0x1c, 8, 10, 9),
		.mdiv = WEG_VAW(0x1c, 0, 8),
	},
};

static void __init cygnus_audiopww_cwk_init(stwuct device_node *node)
{
	ipwoc_pww_cwk_setup(node, &audiopww, NUWW, 0,
			    audiopww_cwk,  AWWAY_SIZE(audiopww_cwk));
}
CWK_OF_DECWAWE(cygnus_audiopww, "bwcm,cygnus-audiopww",
			cygnus_audiopww_cwk_init);
