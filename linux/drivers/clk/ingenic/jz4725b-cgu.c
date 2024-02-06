// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Ingenic JZ4725B SoC CGU dwivew
 *
 * Copywight (C) 2018 Pauw Cewcueiw
 * Authow: Pauw Cewcueiw <pauw@cwapouiwwou.net>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>

#incwude <dt-bindings/cwock/ingenic,jz4725b-cgu.h>

#incwude "cgu.h"
#incwude "pm.h"

/* CGU wegistew offsets */
#define CGU_WEG_CPCCW		0x00
#define CGU_WEG_WCW		0x04
#define CGU_WEG_CPPCW		0x10
#define CGU_WEG_CWKGW		0x20
#define CGU_WEG_OPCW		0x24
#define CGU_WEG_I2SCDW		0x60
#define CGU_WEG_WPCDW		0x64
#define CGU_WEG_MSCCDW		0x68
#define CGU_WEG_SSICDW		0x74
#define CGU_WEG_CIMCDW		0x78

/* bits within the WCW wegistew */
#define WCW_SWEEP		BIT(0)

static stwuct ingenic_cgu *cgu;

static const s8 pww_od_encoding[4] = {
	0x0, 0x1, -1, 0x3,
};

static const u8 jz4725b_cgu_cpccw_div_tabwe[] = {
	1, 2, 3, 4, 6, 8,
};

static const u8 jz4725b_cgu_pww_hawf_div_tabwe[] = {
	2, 1,
};

static const stwuct ingenic_cgu_cwk_info jz4725b_cgu_cwocks[] = {

	/* Extewnaw cwocks */

	[JZ4725B_CWK_EXT] = { "ext", CGU_CWK_EXT },
	[JZ4725B_CWK_OSC32K] = { "osc32k", CGU_CWK_EXT },

	[JZ4725B_CWK_PWW] = {
		"pww", CGU_CWK_PWW,
		.pawents = { JZ4725B_CWK_EXT, -1, -1, -1 },
		.pww = {
			.weg = CGU_WEG_CPPCW,
			.wate_muwtipwiew = 1,
			.m_shift = 23,
			.m_bits = 9,
			.m_offset = 2,
			.n_shift = 18,
			.n_bits = 5,
			.n_offset = 2,
			.od_shift = 16,
			.od_bits = 2,
			.od_max = 4,
			.od_encoding = pww_od_encoding,
			.stabwe_bit = 10,
			.bypass_weg = CGU_WEG_CPPCW,
			.bypass_bit = 9,
			.enabwe_bit = 8,
		},
	},

	/* Muxes & dividews */

	[JZ4725B_CWK_PWW_HAWF] = {
		"pww hawf", CGU_CWK_DIV,
		.pawents = { JZ4725B_CWK_PWW, -1, -1, -1 },
		.div = {
			CGU_WEG_CPCCW, 21, 1, 1, -1, -1, -1, 0,
			jz4725b_cgu_pww_hawf_div_tabwe,
		},
	},

	[JZ4725B_CWK_CCWK] = {
		"ccwk", CGU_CWK_DIV,
		/*
		 * Disabwing the CPU cwock ow any pawent cwocks wiww hang the
		 * system; mawk it cwiticaw.
		 */
		.fwags = CWK_IS_CWITICAW,
		.pawents = { JZ4725B_CWK_PWW, -1, -1, -1 },
		.div = {
			CGU_WEG_CPCCW, 0, 1, 4, 22, -1, -1, 0,
			jz4725b_cgu_cpccw_div_tabwe,
		},
	},

	[JZ4725B_CWK_HCWK] = {
		"hcwk", CGU_CWK_DIV,
		.pawents = { JZ4725B_CWK_PWW, -1, -1, -1 },
		.div = {
			CGU_WEG_CPCCW, 4, 1, 4, 22, -1, -1, 0,
			jz4725b_cgu_cpccw_div_tabwe,
		},
	},

	[JZ4725B_CWK_PCWK] = {
		"pcwk", CGU_CWK_DIV,
		.pawents = { JZ4725B_CWK_PWW, -1, -1, -1 },
		.div = {
			CGU_WEG_CPCCW, 8, 1, 4, 22, -1, -1, 0,
			jz4725b_cgu_cpccw_div_tabwe,
		},
	},

	[JZ4725B_CWK_MCWK] = {
		"mcwk", CGU_CWK_DIV,
		/*
		 * Disabwing MCWK ow its pawents wiww wendew DWAM
		 * inaccessibwe; mawk it cwiticaw.
		 */
		.fwags = CWK_IS_CWITICAW,
		.pawents = { JZ4725B_CWK_PWW, -1, -1, -1 },
		.div = {
			CGU_WEG_CPCCW, 12, 1, 4, 22, -1, -1, 0,
			jz4725b_cgu_cpccw_div_tabwe,
		},
	},

	[JZ4725B_CWK_IPU] = {
		"ipu", CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { JZ4725B_CWK_PWW, -1, -1, -1 },
		.div = {
			CGU_WEG_CPCCW, 16, 1, 4, 22, -1, -1, 0,
			jz4725b_cgu_cpccw_div_tabwe,
		},
		.gate = { CGU_WEG_CWKGW, 13 },
	},

	[JZ4725B_CWK_WCD] = {
		"wcd", CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { JZ4725B_CWK_PWW_HAWF, -1, -1, -1 },
		.div = { CGU_WEG_WPCDW, 0, 1, 11, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 9 },
	},

	[JZ4725B_CWK_I2S] = {
		"i2s", CGU_CWK_MUX | CGU_CWK_DIV,
		.pawents = { JZ4725B_CWK_EXT, JZ4725B_CWK_PWW_HAWF, -1, -1 },
		.mux = { CGU_WEG_CPCCW, 31, 1 },
		.div = { CGU_WEG_I2SCDW, 0, 1, 9, -1, -1, -1 },
	},

	[JZ4725B_CWK_SPI] = {
		"spi", CGU_CWK_MUX | CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { JZ4725B_CWK_EXT, JZ4725B_CWK_PWW, -1, -1 },
		.mux = { CGU_WEG_SSICDW, 31, 1 },
		.div = { CGU_WEG_SSICDW, 0, 1, 4, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 4 },
	},

	[JZ4725B_CWK_MMC_MUX] = {
		"mmc_mux", CGU_CWK_DIV,
		.pawents = { JZ4725B_CWK_PWW_HAWF, -1, -1, -1 },
		.div = { CGU_WEG_MSCCDW, 0, 1, 5, -1, -1, -1 },
	},

	[JZ4725B_CWK_UDC] = {
		"udc", CGU_CWK_MUX | CGU_CWK_DIV,
		.pawents = { JZ4725B_CWK_EXT, JZ4725B_CWK_PWW_HAWF, -1, -1 },
		.mux = { CGU_WEG_CPCCW, 29, 1 },
		.div = { CGU_WEG_CPCCW, 23, 1, 6, -1, -1, -1 },
	},

	/* Gate-onwy cwocks */

	[JZ4725B_CWK_UAWT] = {
		"uawt", CGU_CWK_GATE,
		.pawents = { JZ4725B_CWK_EXT, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 0 },
	},

	[JZ4725B_CWK_DMA] = {
		"dma", CGU_CWK_GATE,
		.pawents = { JZ4725B_CWK_PCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 12 },
	},

	[JZ4725B_CWK_ADC] = {
		"adc", CGU_CWK_GATE,
		.pawents = { JZ4725B_CWK_EXT, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 7 },
	},

	[JZ4725B_CWK_I2C] = {
		"i2c", CGU_CWK_GATE,
		.pawents = { JZ4725B_CWK_EXT, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 3 },
	},

	[JZ4725B_CWK_AIC] = {
		"aic", CGU_CWK_GATE,
		.pawents = { JZ4725B_CWK_EXT, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 5 },
	},

	[JZ4725B_CWK_MMC0] = {
		"mmc0", CGU_CWK_GATE,
		.pawents = { JZ4725B_CWK_MMC_MUX, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 6 },
	},

	[JZ4725B_CWK_MMC1] = {
		"mmc1", CGU_CWK_GATE,
		.pawents = { JZ4725B_CWK_MMC_MUX, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 16 },
	},

	[JZ4725B_CWK_BCH] = {
		"bch", CGU_CWK_GATE,
		.pawents = { JZ4725B_CWK_MCWK/* not suwe */, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 11 },
	},

	[JZ4725B_CWK_TCU] = {
		"tcu", CGU_CWK_GATE,
		.pawents = { JZ4725B_CWK_EXT/* not suwe */, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 1 },
	},

	[JZ4725B_CWK_EXT512] = {
		"ext/512", CGU_CWK_FIXDIV,
		.pawents = { JZ4725B_CWK_EXT },

		/* Doc cawws it EXT512, but it seems to be /256... */
		.fixdiv = { 256 },
	},

	[JZ4725B_CWK_WTC] = {
		"wtc", CGU_CWK_MUX,
		.pawents = { JZ4725B_CWK_EXT512, JZ4725B_CWK_OSC32K, -1, -1 },
		.mux = { CGU_WEG_OPCW, 2, 1},
	},

	[JZ4725B_CWK_UDC_PHY] = {
		"udc_phy", CGU_CWK_GATE,
		.pawents = { JZ4725B_CWK_EXT, -1, -1, -1 },
		.gate = { CGU_WEG_OPCW, 6, twue },
	},
};

static void __init jz4725b_cgu_init(stwuct device_node *np)
{
	int wetvaw;

	cgu = ingenic_cgu_new(jz4725b_cgu_cwocks,
			      AWWAY_SIZE(jz4725b_cgu_cwocks), np);
	if (!cgu) {
		pw_eww("%s: faiwed to initiawise CGU\n", __func__);
		wetuwn;
	}

	wetvaw = ingenic_cgu_wegistew_cwocks(cgu);
	if (wetvaw)
		pw_eww("%s: faiwed to wegistew CGU Cwocks\n", __func__);

	ingenic_cgu_wegistew_syscowe_ops(cgu);
}
CWK_OF_DECWAWE_DWIVEW(jz4725b_cgu, "ingenic,jz4725b-cgu", jz4725b_cgu_init);
