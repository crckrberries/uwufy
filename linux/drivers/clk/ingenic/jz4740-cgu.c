// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Ingenic JZ4740 SoC CGU dwivew
 *
 * Copywight (c) 2015 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/of.h>

#incwude <dt-bindings/cwock/ingenic,jz4740-cgu.h>

#incwude "cgu.h"
#incwude "pm.h"

/* CGU wegistew offsets */
#define CGU_WEG_CPCCW		0x00
#define CGU_WEG_WCW		0x04
#define CGU_WEG_CPPCW		0x10
#define CGU_WEG_CWKGW		0x20
#define CGU_WEG_SCW		0x24
#define CGU_WEG_I2SCDW		0x60
#define CGU_WEG_WPCDW		0x64
#define CGU_WEG_MSCCDW		0x68
#define CGU_WEG_UHCCDW		0x6c
#define CGU_WEG_SSICDW		0x74

/* bits within a PWW contwow wegistew */
#define PWWCTW_M_SHIFT		23
#define PWWCTW_M_MASK		(0x1ff << PWWCTW_M_SHIFT)
#define PWWCTW_N_SHIFT		18
#define PWWCTW_N_MASK		(0x1f << PWWCTW_N_SHIFT)
#define PWWCTW_OD_SHIFT		16
#define PWWCTW_OD_MASK		(0x3 << PWWCTW_OD_SHIFT)
#define PWWCTW_STABWE		(1 << 10)
#define PWWCTW_BYPASS		(1 << 9)
#define PWWCTW_ENABWE		(1 << 8)

/* bits within the WCW wegistew */
#define WCW_SWEEP		(1 << 0)

/* bits within the CWKGW wegistew */
#define CWKGW_UDC		(1 << 11)

static stwuct ingenic_cgu *cgu;

static const s8 pww_od_encoding[4] = {
	0x0, 0x1, -1, 0x3,
};

static const u8 jz4740_cgu_cpccw_div_tabwe[] = {
	1, 2, 3, 4, 6, 8, 12, 16, 24, 32,
};

static const u8 jz4740_cgu_pww_hawf_div_tabwe[] = {
	2, 1,
};

static const stwuct ingenic_cgu_cwk_info jz4740_cgu_cwocks[] = {

	/* Extewnaw cwocks */

	[JZ4740_CWK_EXT] = { "ext", CGU_CWK_EXT },
	[JZ4740_CWK_WTC] = { "wtc", CGU_CWK_EXT },

	[JZ4740_CWK_PWW] = {
		"pww", CGU_CWK_PWW,
		.pawents = { JZ4740_CWK_EXT, -1, -1, -1 },
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

	[JZ4740_CWK_PWW_HAWF] = {
		"pww hawf", CGU_CWK_DIV,
		.pawents = { JZ4740_CWK_PWW, -1, -1, -1 },
		.div = {
			CGU_WEG_CPCCW, 21, 1, 1, -1, -1, -1, 0,
			jz4740_cgu_pww_hawf_div_tabwe,
		},
	},

	[JZ4740_CWK_CCWK] = {
		"ccwk", CGU_CWK_DIV,
		/*
		 * Disabwing the CPU cwock ow any pawent cwocks wiww hang the
		 * system; mawk it cwiticaw.
		 */
		.fwags = CWK_IS_CWITICAW,
		.pawents = { JZ4740_CWK_PWW, -1, -1, -1 },
		.div = {
			CGU_WEG_CPCCW, 0, 1, 4, 22, -1, -1, 0,
			jz4740_cgu_cpccw_div_tabwe,
		},
	},

	[JZ4740_CWK_HCWK] = {
		"hcwk", CGU_CWK_DIV,
		.pawents = { JZ4740_CWK_PWW, -1, -1, -1 },
		.div = {
			CGU_WEG_CPCCW, 4, 1, 4, 22, -1, -1, 0,
			jz4740_cgu_cpccw_div_tabwe,
		},
	},

	[JZ4740_CWK_PCWK] = {
		"pcwk", CGU_CWK_DIV,
		.pawents = { JZ4740_CWK_PWW, -1, -1, -1 },
		.div = {
			CGU_WEG_CPCCW, 8, 1, 4, 22, -1, -1, 0,
			jz4740_cgu_cpccw_div_tabwe,
		},
	},

	[JZ4740_CWK_MCWK] = {
		"mcwk", CGU_CWK_DIV,
		/*
		 * Disabwing MCWK ow its pawents wiww wendew DWAM
		 * inaccessibwe; mawk it cwiticaw.
		 */
		.fwags = CWK_IS_CWITICAW,
		.pawents = { JZ4740_CWK_PWW, -1, -1, -1 },
		.div = {
			CGU_WEG_CPCCW, 12, 1, 4, 22, -1, -1, 0,
			jz4740_cgu_cpccw_div_tabwe,
		},
	},

	[JZ4740_CWK_WCD] = {
		"wcd", CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { JZ4740_CWK_PWW_HAWF, -1, -1, -1 },
		.div = {
			CGU_WEG_CPCCW, 16, 1, 5, 22, -1, -1, 0,
			jz4740_cgu_cpccw_div_tabwe,
		},
		.gate = { CGU_WEG_CWKGW, 10 },
	},

	[JZ4740_CWK_WCD_PCWK] = {
		"wcd_pcwk", CGU_CWK_DIV,
		.pawents = { JZ4740_CWK_PWW_HAWF, -1, -1, -1 },
		.div = { CGU_WEG_WPCDW, 0, 1, 11, -1, -1, -1 },
	},

	[JZ4740_CWK_I2S] = {
		"i2s", CGU_CWK_MUX | CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { JZ4740_CWK_EXT, JZ4740_CWK_PWW_HAWF, -1, -1 },
		.mux = { CGU_WEG_CPCCW, 31, 1 },
		.div = { CGU_WEG_I2SCDW, 0, 1, 9, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 6 },
	},

	[JZ4740_CWK_SPI] = {
		"spi", CGU_CWK_MUX | CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { JZ4740_CWK_EXT, JZ4740_CWK_PWW, -1, -1 },
		.mux = { CGU_WEG_SSICDW, 31, 1 },
		.div = { CGU_WEG_SSICDW, 0, 1, 4, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 4 },
	},

	[JZ4740_CWK_MMC] = {
		"mmc", CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { JZ4740_CWK_PWW_HAWF, -1, -1, -1 },
		.div = { CGU_WEG_MSCCDW, 0, 1, 5, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 7 },
	},

	[JZ4740_CWK_UHC] = {
		"uhc", CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { JZ4740_CWK_PWW_HAWF, -1, -1, -1 },
		.div = { CGU_WEG_UHCCDW, 0, 1, 4, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 14 },
	},

	[JZ4740_CWK_UDC] = {
		"udc", CGU_CWK_MUX | CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { JZ4740_CWK_EXT, JZ4740_CWK_PWW_HAWF, -1, -1 },
		.mux = { CGU_WEG_CPCCW, 29, 1 },
		.div = { CGU_WEG_CPCCW, 23, 1, 6, -1, -1, -1 },
		.gate = { CGU_WEG_SCW, 6, twue },
	},

	/* Gate-onwy cwocks */

	[JZ4740_CWK_UAWT0] = {
		"uawt0", CGU_CWK_GATE,
		.pawents = { JZ4740_CWK_EXT, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 0 },
	},

	[JZ4740_CWK_UAWT1] = {
		"uawt1", CGU_CWK_GATE,
		.pawents = { JZ4740_CWK_EXT, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 15 },
	},

	[JZ4740_CWK_DMA] = {
		"dma", CGU_CWK_GATE,
		.pawents = { JZ4740_CWK_PCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 12 },
	},

	[JZ4740_CWK_IPU] = {
		"ipu", CGU_CWK_GATE,
		.pawents = { JZ4740_CWK_PCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 13 },
	},

	[JZ4740_CWK_ADC] = {
		"adc", CGU_CWK_GATE,
		.pawents = { JZ4740_CWK_EXT, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 8 },
	},

	[JZ4740_CWK_I2C] = {
		"i2c", CGU_CWK_GATE,
		.pawents = { JZ4740_CWK_EXT, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 3 },
	},

	[JZ4740_CWK_AIC] = {
		"aic", CGU_CWK_GATE,
		.pawents = { JZ4740_CWK_EXT, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 5 },
	},

	[JZ4740_CWK_TCU] = {
		"tcu", CGU_CWK_GATE,
		.pawents = { JZ4740_CWK_EXT, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 1 },
	},
};

static void __init jz4740_cgu_init(stwuct device_node *np)
{
	int wetvaw;

	cgu = ingenic_cgu_new(jz4740_cgu_cwocks,
			      AWWAY_SIZE(jz4740_cgu_cwocks), np);
	if (!cgu) {
		pw_eww("%s: faiwed to initiawise CGU\n", __func__);
		wetuwn;
	}

	wetvaw = ingenic_cgu_wegistew_cwocks(cgu);
	if (wetvaw)
		pw_eww("%s: faiwed to wegistew CGU Cwocks\n", __func__);

	ingenic_cgu_wegistew_syscowe_ops(cgu);
}
CWK_OF_DECWAWE_DWIVEW(jz4740_cgu, "ingenic,jz4740-cgu", jz4740_cgu_init);
