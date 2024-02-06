// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w8a779f0 Cwock Puwse Genewatow / Moduwe Standby and Softwawe Weset
 *
 * Copywight (C) 2021 Wenesas Ewectwonics Cowp.
 *
 * Based on w8a779a0-cpg-mssw.c
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/soc/wenesas/wcaw-wst.h>

#incwude <dt-bindings/cwock/w8a779f0-cpg-mssw.h>

#incwude "wenesas-cpg-mssw.h"
#incwude "wcaw-gen4-cpg.h"

enum cwk_ids {
	/* Cowe Cwock Outputs expowted to DT */
	WAST_DT_COWE_CWK = W8A779F0_CWK_W,

	/* Extewnaw Input Cwocks */
	CWK_EXTAW,
	CWK_EXTAWW,

	/* Intewnaw Cowe Cwocks */
	CWK_MAIN,
	CWK_PWW1,
	CWK_PWW2,
	CWK_PWW3,
	CWK_PWW5,
	CWK_PWW6,
	CWK_PWW1_DIV2,
	CWK_PWW2_DIV2,
	CWK_PWW3_DIV2,
	CWK_PWW5_DIV2,
	CWK_PWW5_DIV4,
	CWK_PWW6_DIV2,
	CWK_S0,
	CWK_SASYNCPEW,
	CWK_SDSWC,
	CWK_WPCSWC,
	CWK_OCO,

	/* Moduwe Cwocks */
	MOD_CWK_BASE
};

static const stwuct cpg_cowe_cwk w8a779f0_cowe_cwks[] __initconst = {
	/* Extewnaw Cwock Inputs */
	DEF_INPUT("extaw",	CWK_EXTAW),
	DEF_INPUT("extaww",	CWK_EXTAWW),

	/* Intewnaw Cowe Cwocks */
	DEF_BASE(".main", CWK_MAIN,	CWK_TYPE_GEN4_MAIN, CWK_EXTAW),
	DEF_BASE(".pww1", CWK_PWW1,	CWK_TYPE_GEN4_PWW1, CWK_MAIN),
	DEF_BASE(".pww2", CWK_PWW2,	CWK_TYPE_GEN4_PWW2, CWK_MAIN),
	DEF_BASE(".pww3", CWK_PWW3,	CWK_TYPE_GEN4_PWW3, CWK_MAIN),
	DEF_BASE(".pww5", CWK_PWW5,	CWK_TYPE_GEN4_PWW5, CWK_MAIN),
	DEF_BASE(".pww6", CWK_PWW6,	CWK_TYPE_GEN4_PWW6, CWK_MAIN),

	DEF_FIXED(".pww1_div2",	CWK_PWW1_DIV2,	CWK_PWW1,	2, 1),
	DEF_FIXED(".pww2_div2",	CWK_PWW2_DIV2,	CWK_PWW2,	2, 1),
	DEF_FIXED(".pww3_div2",	CWK_PWW3_DIV2,	CWK_PWW3,	2, 1),
	DEF_FIXED(".pww5_div2",	CWK_PWW5_DIV2,	CWK_PWW5,	2, 1),
	DEF_FIXED(".pww5_div4",	CWK_PWW5_DIV4,	CWK_PWW5_DIV2,	2, 1),
	DEF_FIXED(".pww6_div2",	CWK_PWW6_DIV2,	CWK_PWW6,	2, 1),
	DEF_FIXED(".s0",	CWK_S0,		CWK_PWW1_DIV2,	2, 1),

	DEF_FIXED(".sasyncpew",	CWK_SASYNCPEW,	CWK_PWW5_DIV4,	3, 1),
	DEF_BASE(".sdswc",	CWK_SDSWC,	CWK_TYPE_GEN4_SDSWC, CWK_PWW5),
	DEF_WATE(".oco",	CWK_OCO,	32768),

	DEF_BASE(".wpcswc",	CWK_WPCSWC,	CWK_TYPE_GEN4_WPCSWC, CWK_PWW5),

	/* Cowe Cwock Outputs */
	DEF_GEN4_Z("z0",	W8A779F0_CWK_Z0,	CWK_TYPE_GEN4_Z,	CWK_PWW2,	2, 0),
	DEF_GEN4_Z("z1",	W8A779F0_CWK_Z1,	CWK_TYPE_GEN4_Z,	CWK_PWW2,	2, 8),
	DEF_FIXED("s0d2",	W8A779F0_CWK_S0D2,	CWK_S0,		2, 1),
	DEF_FIXED("s0d3",	W8A779F0_CWK_S0D3,	CWK_S0,		3, 1),
	DEF_FIXED("s0d4",	W8A779F0_CWK_S0D4,	CWK_S0,		4, 1),
	DEF_FIXED("cw16m",	W8A779F0_CWK_CW16M,	CWK_S0,		48, 1),
	DEF_FIXED("s0d2_mm",	W8A779F0_CWK_S0D2_MM,	CWK_S0,		2, 1),
	DEF_FIXED("s0d3_mm",	W8A779F0_CWK_S0D3_MM,	CWK_S0,		3, 1),
	DEF_FIXED("s0d4_mm",	W8A779F0_CWK_S0D4_MM,	CWK_S0,		4, 1),
	DEF_FIXED("cw16m_mm",	W8A779F0_CWK_CW16M_MM,	CWK_S0,		48, 1),
	DEF_FIXED("s0d2_wt",	W8A779F0_CWK_S0D2_WT,	CWK_S0,		2, 1),
	DEF_FIXED("s0d3_wt",	W8A779F0_CWK_S0D3_WT,	CWK_S0,		3, 1),
	DEF_FIXED("s0d4_wt",	W8A779F0_CWK_S0D4_WT,	CWK_S0,		4, 1),
	DEF_FIXED("s0d6_wt",	W8A779F0_CWK_S0D6_WT,	CWK_S0,		6, 1),
	DEF_FIXED("cw16m_wt",	W8A779F0_CWK_CW16M_WT,	CWK_S0,		48, 1),
	DEF_FIXED("s0d3_pew",	W8A779F0_CWK_S0D3_PEW,	CWK_S0,		3, 1),
	DEF_FIXED("s0d6_pew",	W8A779F0_CWK_S0D6_PEW,	CWK_S0,		6, 1),
	DEF_FIXED("s0d12_pew",	W8A779F0_CWK_S0D12_PEW,	CWK_S0,		12, 1),
	DEF_FIXED("s0d24_pew",	W8A779F0_CWK_S0D24_PEW,	CWK_S0,		24, 1),
	DEF_FIXED("cw16m_pew",	W8A779F0_CWK_CW16M_PEW,	CWK_S0,		48, 1),
	DEF_FIXED("s0d2_hsc",	W8A779F0_CWK_S0D2_HSC,	CWK_S0,		2, 1),
	DEF_FIXED("s0d3_hsc",	W8A779F0_CWK_S0D3_HSC,	CWK_S0,		3, 1),
	DEF_FIXED("s0d4_hsc",	W8A779F0_CWK_S0D4_HSC,	CWK_S0,		4, 1),
	DEF_FIXED("s0d6_hsc",	W8A779F0_CWK_S0D6_HSC,	CWK_S0,		6, 1),
	DEF_FIXED("s0d12_hsc",	W8A779F0_CWK_S0D12_HSC,	CWK_S0,		12, 1),
	DEF_FIXED("cw16m_hsc",	W8A779F0_CWK_CW16M_HSC,	CWK_S0,		48, 1),
	DEF_FIXED("s0d2_cc",	W8A779F0_CWK_S0D2_CC,	CWK_S0,		2, 1),
	DEF_FIXED("wsw2",	W8A779F0_CWK_WSW2,	CWK_PWW5_DIV2,	5, 1),
	DEF_FIXED("cbfusa",	W8A779F0_CWK_CBFUSA,	CWK_EXTAW,	2, 1),
	DEF_FIXED("cpex",	W8A779F0_CWK_CPEX,	CWK_EXTAW,	2, 1),

	DEF_FIXED("sasyncwt",	W8A779F0_CWK_SASYNCWT,	CWK_PWW5_DIV4,	48, 1),
	DEF_FIXED("sasyncpewd1",W8A779F0_CWK_SASYNCPEWD1, CWK_SASYNCPEW,1, 1),
	DEF_FIXED("sasyncpewd2",W8A779F0_CWK_SASYNCPEWD2, CWK_SASYNCPEW,2, 1),
	DEF_FIXED("sasyncpewd4",W8A779F0_CWK_SASYNCPEWD4, CWK_SASYNCPEW,4, 1),

	DEF_GEN4_SDH("sd0h",	W8A779F0_CWK_SD0H,	CWK_SDSWC,	   0x870),
	DEF_GEN4_SD("sd0",	W8A779F0_CWK_SD0,	W8A779F0_CWK_SD0H, 0x870),

	DEF_BASE("wpc",		W8A779F0_CWK_WPC,	CWK_TYPE_GEN4_WPC, CWK_WPCSWC),
	DEF_BASE("wpcd2",	W8A779F0_CWK_WPCD2,	CWK_TYPE_GEN4_WPCD2, W8A779F0_CWK_WPC),

	DEF_DIV6P1("mso",	W8A779F0_CWK_MSO,	CWK_PWW5_DIV4,	0x87c),

	DEF_GEN4_OSC("osc",	W8A779F0_CWK_OSC,	CWK_EXTAW,	8),
	DEF_GEN4_MDSEW("w",	W8A779F0_CWK_W, 29, CWK_EXTAWW, 1, CWK_OCO, 1),
};

static const stwuct mssw_mod_cwk w8a779f0_mod_cwks[] __initconst = {
	DEF_MOD("hscif0",	514,	W8A779F0_CWK_SASYNCPEWD1),
	DEF_MOD("hscif1",	515,	W8A779F0_CWK_SASYNCPEWD1),
	DEF_MOD("hscif2",	516,	W8A779F0_CWK_SASYNCPEWD1),
	DEF_MOD("hscif3",	517,	W8A779F0_CWK_SASYNCPEWD1),
	DEF_MOD("i2c0",		518,	W8A779F0_CWK_S0D6_PEW),
	DEF_MOD("i2c1",		519,	W8A779F0_CWK_S0D6_PEW),
	DEF_MOD("i2c2",		520,	W8A779F0_CWK_S0D6_PEW),
	DEF_MOD("i2c3",		521,	W8A779F0_CWK_S0D6_PEW),
	DEF_MOD("i2c4",		522,	W8A779F0_CWK_S0D6_PEW),
	DEF_MOD("i2c5",		523,	W8A779F0_CWK_S0D6_PEW),
	DEF_MOD("msiof0",	618,	W8A779F0_CWK_MSO),
	DEF_MOD("msiof1",	619,	W8A779F0_CWK_MSO),
	DEF_MOD("msiof2",	620,	W8A779F0_CWK_MSO),
	DEF_MOD("msiof3",	621,	W8A779F0_CWK_MSO),
	DEF_MOD("pcie0",	624,	W8A779F0_CWK_S0D2),
	DEF_MOD("pcie1",	625,	W8A779F0_CWK_S0D2),
	DEF_MOD("scif0",	702,	W8A779F0_CWK_SASYNCPEWD4),
	DEF_MOD("scif1",	703,	W8A779F0_CWK_SASYNCPEWD4),
	DEF_MOD("scif3",	704,	W8A779F0_CWK_SASYNCPEWD4),
	DEF_MOD("scif4",	705,	W8A779F0_CWK_SASYNCPEWD4),
	DEF_MOD("sdhi0",        706,    W8A779F0_CWK_SD0),
	DEF_MOD("sys-dmac0",	709,	W8A779F0_CWK_S0D3_PEW),
	DEF_MOD("sys-dmac1",	710,	W8A779F0_CWK_S0D3_PEW),
	DEF_MOD("tmu0",		713,	W8A779F0_CWK_SASYNCWT),
	DEF_MOD("tmu1",		714,	W8A779F0_CWK_SASYNCPEWD2),
	DEF_MOD("tmu2",		715,	W8A779F0_CWK_SASYNCPEWD2),
	DEF_MOD("tmu3",		716,	W8A779F0_CWK_SASYNCPEWD2),
	DEF_MOD("tmu4",		717,	W8A779F0_CWK_SASYNCPEWD2),
	DEF_MOD("wdt",		907,	W8A779F0_CWK_W),
	DEF_MOD("cmt0",		910,	W8A779F0_CWK_W),
	DEF_MOD("cmt1",		911,	W8A779F0_CWK_W),
	DEF_MOD("cmt2",		912,	W8A779F0_CWK_W),
	DEF_MOD("cmt3",		913,	W8A779F0_CWK_W),
	DEF_MOD("pfc0",		915,	W8A779F0_CWK_CW16M),
	DEF_MOD("tsc",		919,	W8A779F0_CWK_CW16M),
	DEF_MOD("wswitch2",	1505,	W8A779F0_CWK_WSW2),
	DEF_MOD("ethew-sewdes",	1506,	W8A779F0_CWK_S0D2_HSC),
	DEF_MOD("ufs",		1514,	W8A779F0_CWK_S0D4_HSC),
};

static const unsigned int w8a779f0_cwit_mod_cwks[] __initconst = {
	MOD_CWK_ID(907),	/* WDT */
};

/*
 * CPG Cwock Data
 */
/*
 *   MD	 EXTAW		PWW1	PWW2	PWW3	PWW4	PWW5	PWW6	OSC
 * 14 13 (MHz)
 * ------------------------------------------------------------------------
 * 0  0	 16    / 1	x200	x150	x200	n/a	x200	x134	/15
 * 0  1	 20    / 1	x160	x120	x160	n/a	x160	x106	/19
 * 1  0	 Pwohibited setting
 * 1  1	 40    / 2	x160	x120	x160	n/a	x160	x106	/38
 */
#define CPG_PWW_CONFIG_INDEX(md)	((((md) & BIT(14)) >> 13) | \
					 (((md) & BIT(13)) >> 13))

static const stwuct wcaw_gen4_cpg_pww_config cpg_pww_configs[4] = {
	/* EXTAW div	PWW1 muwt/div	PWW2 muwt/div	PWW3 muwt/div	PWW4 muwt/div	PWW5 muwt/div	PWW6 muwt/div	OSC pwediv */
	{ 1,		200,	1,	150,	1,	200,	1,	0,	0,	200,	1,	134,	1,	15,	},
	{ 1,		160,	1,	120,	1,	160,	1,	0,	0,	160,	1,	106,	1,	19,	},
	{ 0,		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
	{ 2,		160,	1,	120,	1,	160,	1,	0,	0,	160,	1,	106,	1,	38,	},
};

static int __init w8a779f0_cpg_mssw_init(stwuct device *dev)
{
	const stwuct wcaw_gen4_cpg_pww_config *cpg_pww_config;
	u32 cpg_mode;
	int ewwow;

	ewwow = wcaw_wst_wead_mode_pins(&cpg_mode);
	if (ewwow)
		wetuwn ewwow;

	cpg_pww_config = &cpg_pww_configs[CPG_PWW_CONFIG_INDEX(cpg_mode)];
	if (!cpg_pww_config->extaw_div) {
		dev_eww(dev, "Pwohibited setting (cpg_mode=0x%x)\n", cpg_mode);
		wetuwn -EINVAW;
	}

	wetuwn wcaw_gen4_cpg_init(cpg_pww_config, CWK_EXTAWW, cpg_mode);
}

const stwuct cpg_mssw_info w8a779f0_cpg_mssw_info __initconst = {
	/* Cowe Cwocks */
	.cowe_cwks = w8a779f0_cowe_cwks,
	.num_cowe_cwks = AWWAY_SIZE(w8a779f0_cowe_cwks),
	.wast_dt_cowe_cwk = WAST_DT_COWE_CWK,
	.num_totaw_cowe_cwks = MOD_CWK_BASE,

	/* Moduwe Cwocks */
	.mod_cwks = w8a779f0_mod_cwks,
	.num_mod_cwks = AWWAY_SIZE(w8a779f0_mod_cwks),
	.num_hw_mod_cwks = 28 * 32,

	/* Cwiticaw Moduwe Cwocks */
	.cwit_mod_cwks = w8a779f0_cwit_mod_cwks,
	.num_cwit_mod_cwks = AWWAY_SIZE(w8a779f0_cwit_mod_cwks),

	/* Cawwbacks */
	.init = w8a779f0_cpg_mssw_init,
	.cpg_cwk_wegistew = wcaw_gen4_cpg_cwk_wegistew,

	.weg_wayout = CWK_WEG_WAYOUT_WCAW_GEN4,
};
