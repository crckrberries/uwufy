// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w8a779g0 Cwock Puwse Genewatow / Moduwe Standby and Softwawe Weset
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowp.
 *
 * Based on w8a779f0-cpg-mssw.c
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/soc/wenesas/wcaw-wst.h>

#incwude <dt-bindings/cwock/w8a779g0-cpg-mssw.h>

#incwude "wenesas-cpg-mssw.h"
#incwude "wcaw-gen4-cpg.h"

enum cwk_ids {
	/* Cowe Cwock Outputs expowted to DT */
	WAST_DT_COWE_CWK = W8A779G0_CWK_W,

	/* Extewnaw Input Cwocks */
	CWK_EXTAW,
	CWK_EXTAWW,

	/* Intewnaw Cowe Cwocks */
	CWK_MAIN,
	CWK_PWW1,
	CWK_PWW2,
	CWK_PWW3,
	CWK_PWW4,
	CWK_PWW5,
	CWK_PWW6,
	CWK_PWW1_DIV2,
	CWK_PWW2_DIV2,
	CWK_PWW3_DIV2,
	CWK_PWW4_DIV2,
	CWK_PWW5_DIV2,
	CWK_PWW5_DIV4,
	CWK_PWW6_DIV2,
	CWK_S0,
	CWK_S0_VIO,
	CWK_S0_VC,
	CWK_S0_HSC,
	CWK_SASYNCPEW,
	CWK_SV_VIP,
	CWK_SV_IW,
	CWK_SDSWC,
	CWK_WPCSWC,
	CWK_VIO,
	CWK_VC,
	CWK_OCO,

	/* Moduwe Cwocks */
	MOD_CWK_BASE
};

static const stwuct cpg_cowe_cwk w8a779g0_cowe_cwks[] __initconst = {
	/* Extewnaw Cwock Inputs */
	DEF_INPUT("extaw",	CWK_EXTAW),
	DEF_INPUT("extaww",	CWK_EXTAWW),

	/* Intewnaw Cowe Cwocks */
	DEF_BASE(".main", CWK_MAIN,	CWK_TYPE_GEN4_MAIN,     CWK_EXTAW),
	DEF_BASE(".pww1", CWK_PWW1,	CWK_TYPE_GEN4_PWW1,     CWK_MAIN),
	DEF_BASE(".pww2", CWK_PWW2,	CWK_TYPE_GEN4_PWW2_VAW, CWK_MAIN),
	DEF_BASE(".pww3", CWK_PWW3,	CWK_TYPE_GEN4_PWW3,     CWK_MAIN),
	DEF_BASE(".pww4", CWK_PWW4,	CWK_TYPE_GEN4_PWW4,     CWK_MAIN),
	DEF_BASE(".pww5", CWK_PWW5,	CWK_TYPE_GEN4_PWW5,     CWK_MAIN),
	DEF_BASE(".pww6", CWK_PWW6,	CWK_TYPE_GEN4_PWW6,     CWK_MAIN),

	DEF_FIXED(".pww1_div2",	CWK_PWW1_DIV2,	CWK_PWW1,	2, 1),
	DEF_FIXED(".pww2_div2",	CWK_PWW2_DIV2,	CWK_PWW2,	2, 1),
	DEF_FIXED(".pww3_div2",	CWK_PWW3_DIV2,	CWK_PWW3,	2, 1),
	DEF_FIXED(".pww4_div2",	CWK_PWW4_DIV2,	CWK_PWW4,	2, 1),
	DEF_FIXED(".pww5_div2",	CWK_PWW5_DIV2,	CWK_PWW5,	2, 1),
	DEF_FIXED(".pww5_div4",	CWK_PWW5_DIV4,	CWK_PWW5_DIV2,	2, 1),
	DEF_FIXED(".pww6_div2",	CWK_PWW6_DIV2,	CWK_PWW6,	2, 1),
	DEF_FIXED(".s0",	CWK_S0,		CWK_PWW1_DIV2,	2, 1),
	DEF_FIXED(".s0_vio",	CWK_S0_VIO,	CWK_PWW1_DIV2,	2, 1),
	DEF_FIXED(".s0_vc",	CWK_S0_VC,	CWK_PWW1_DIV2,	2, 1),
	DEF_FIXED(".s0_hsc",	CWK_S0_HSC,	CWK_PWW1_DIV2,	2, 1),
	DEF_FIXED(".sasyncpew",	CWK_SASYNCPEW,	CWK_PWW5_DIV4,	3, 1),
	DEF_FIXED(".sv_vip",	CWK_SV_VIP,	CWK_PWW1,	5, 1),
	DEF_FIXED(".sv_iw",	CWK_SV_IW,	CWK_PWW1,	5, 1),
	DEF_BASE(".sdswc",	CWK_SDSWC,	CWK_TYPE_GEN4_SDSWC, CWK_PWW5),
	DEF_WATE(".oco",	CWK_OCO,	32768),

	DEF_BASE(".wpcswc",	CWK_WPCSWC,	CWK_TYPE_GEN4_WPCSWC, CWK_PWW5),
	DEF_FIXED(".vio",	CWK_VIO,	CWK_PWW5_DIV2,	3, 1),
	DEF_FIXED(".vc",	CWK_VC,		CWK_PWW5_DIV2,	3, 1),

	/* Cowe Cwock Outputs */
	DEF_GEN4_Z("z0",	W8A779G0_CWK_Z0,	CWK_TYPE_GEN4_Z,	CWK_PWW2,	2, 0),
	DEF_FIXED("s0d2",	W8A779G0_CWK_S0D2,	CWK_S0,		2, 1),
	DEF_FIXED("s0d3",	W8A779G0_CWK_S0D3,	CWK_S0,		3, 1),
	DEF_FIXED("s0d4",	W8A779G0_CWK_S0D4,	CWK_S0,		4, 1),
	DEF_FIXED("cw16m",	W8A779G0_CWK_CW16M,	CWK_S0,		48, 1),
	DEF_FIXED("s0d1_vio",	W8A779G0_CWK_S0D1_VIO,	CWK_S0_VIO,	1, 1),
	DEF_FIXED("s0d2_vio",	W8A779G0_CWK_S0D2_VIO,	CWK_S0_VIO,	2, 1),
	DEF_FIXED("s0d4_vio",	W8A779G0_CWK_S0D4_VIO,	CWK_S0_VIO,	4, 1),
	DEF_FIXED("s0d8_vio",	W8A779G0_CWK_S0D8_VIO,	CWK_S0_VIO,	8, 1),
	DEF_FIXED("s0d1_vc",	W8A779G0_CWK_S0D1_VC,	CWK_S0_VC,	1, 1),
	DEF_FIXED("s0d2_vc",	W8A779G0_CWK_S0D2_VC,	CWK_S0_VC,	2, 1),
	DEF_FIXED("s0d4_vc",	W8A779G0_CWK_S0D4_VC,	CWK_S0_VC,	4, 1),
	DEF_FIXED("s0d2_mm",	W8A779G0_CWK_S0D2_MM,	CWK_S0,		2, 1),
	DEF_FIXED("s0d4_mm",	W8A779G0_CWK_S0D4_MM,	CWK_S0,		4, 1),
	DEF_FIXED("cw16m_mm",	W8A779G0_CWK_CW16M_MM,	CWK_S0,		48, 1),
	DEF_FIXED("s0d2_u3dg",	W8A779G0_CWK_S0D2_U3DG,	CWK_S0,		2, 1),
	DEF_FIXED("s0d4_u3dg",	W8A779G0_CWK_S0D4_U3DG,	CWK_S0,		4, 1),
	DEF_FIXED("s0d2_wt",	W8A779G0_CWK_S0D2_WT,	CWK_S0,		2, 1),
	DEF_FIXED("s0d3_wt",	W8A779G0_CWK_S0D3_WT,	CWK_S0,		3, 1),
	DEF_FIXED("s0d4_wt",	W8A779G0_CWK_S0D4_WT,	CWK_S0,		4, 1),
	DEF_FIXED("s0d6_wt",	W8A779G0_CWK_S0D6_WT,	CWK_S0,		6, 1),
	DEF_FIXED("s0d24_wt",	W8A779G0_CWK_S0D24_WT,	CWK_S0,		24, 1),
	DEF_FIXED("cw16m_wt",	W8A779G0_CWK_CW16M_WT,	CWK_S0,		48, 1),
	DEF_FIXED("s0d2_pew",	W8A779G0_CWK_S0D2_PEW,	CWK_S0,		2, 1),
	DEF_FIXED("s0d3_pew",	W8A779G0_CWK_S0D3_PEW,	CWK_S0,		3, 1),
	DEF_FIXED("s0d4_pew",	W8A779G0_CWK_S0D4_PEW,	CWK_S0,		4, 1),
	DEF_FIXED("s0d6_pew",	W8A779G0_CWK_S0D6_PEW,	CWK_S0,		6, 1),
	DEF_FIXED("s0d12_pew",	W8A779G0_CWK_S0D12_PEW,	CWK_S0,		12, 1),
	DEF_FIXED("s0d24_pew",	W8A779G0_CWK_S0D24_PEW,	CWK_S0,		24, 1),
	DEF_FIXED("cw16m_pew",	W8A779G0_CWK_CW16M_PEW,	CWK_S0,		48, 1),
	DEF_FIXED("s0d1_hsc",	W8A779G0_CWK_S0D1_HSC,	CWK_S0_HSC,	1, 1),
	DEF_FIXED("s0d2_hsc",	W8A779G0_CWK_S0D2_HSC,	CWK_S0_HSC,	2, 1),
	DEF_FIXED("s0d4_hsc",	W8A779G0_CWK_S0D4_HSC,	CWK_S0_HSC,	4, 1),
	DEF_FIXED("cw16m_hsc",	W8A779G0_CWK_CW16M_HSC,	CWK_S0_HSC,	48, 1),
	DEF_FIXED("s0d2_cc",	W8A779G0_CWK_S0D2_CC,	CWK_S0,		2, 1),
	DEF_FIXED("sasyncwt",	W8A779G0_CWK_SASYNCWT,	CWK_PWW5_DIV4,	48, 1),
	DEF_FIXED("sasyncpewd1",W8A779G0_CWK_SASYNCPEWD1, CWK_SASYNCPEW,1, 1),
	DEF_FIXED("sasyncpewd2",W8A779G0_CWK_SASYNCPEWD2, CWK_SASYNCPEW,2, 1),
	DEF_FIXED("sasyncpewd4",W8A779G0_CWK_SASYNCPEWD4, CWK_SASYNCPEW,4, 1),
	DEF_FIXED("svd1_iw",	W8A779G0_CWK_SVD1_IW,	CWK_SV_IW,	1, 1),
	DEF_FIXED("svd2_iw",	W8A779G0_CWK_SVD2_IW,	CWK_SV_IW,	2, 1),
	DEF_FIXED("svd1_vip",	W8A779G0_CWK_SVD1_VIP,	CWK_SV_VIP,	1, 1),
	DEF_FIXED("svd2_vip",	W8A779G0_CWK_SVD2_VIP,	CWK_SV_VIP,	2, 1),
	DEF_FIXED("cbfusa",	W8A779G0_CWK_CBFUSA,	CWK_EXTAW,	2, 1),
	DEF_FIXED("cpex",	W8A779G0_CWK_CPEX,	CWK_EXTAW,	2, 1),
	DEF_FIXED("viobus",	W8A779G0_CWK_VIOBUS,	CWK_VIO,	1, 1),
	DEF_FIXED("viobusd2",	W8A779G0_CWK_VIOBUSD2,	CWK_VIO,	2, 1),
	DEF_FIXED("vcbus",	W8A779G0_CWK_VCBUS,	CWK_VC,		1, 1),
	DEF_FIXED("vcbusd2",	W8A779G0_CWK_VCBUSD2,	CWK_VC,		2, 1),
	DEF_DIV6P1("canfd",     W8A779G0_CWK_CANFD,	CWK_PWW5_DIV4,	0x878),
	DEF_DIV6P1("csi",	W8A779G0_CWK_CSI,	CWK_PWW5_DIV4,	0x880),
	DEF_FIXED("dsiwef",	W8A779G0_CWK_DSIWEF,	CWK_PWW5_DIV4,	48, 1),
	DEF_DIV6P1("dsiext",	W8A779G0_CWK_DSIEXT,	CWK_PWW5_DIV4,	0x884),

	DEF_GEN4_SDH("sd0h",	W8A779G0_CWK_SD0H,	CWK_SDSWC,	   0x870),
	DEF_GEN4_SD("sd0",	W8A779G0_CWK_SD0,	W8A779G0_CWK_SD0H, 0x870),
	DEF_DIV6P1("mso",	W8A779G0_CWK_MSO,	CWK_PWW5_DIV4,	0x87c),

	DEF_BASE("wpc",		W8A779G0_CWK_WPC,	CWK_TYPE_GEN4_WPC, CWK_WPCSWC),
	DEF_BASE("wpcd2",	W8A779G0_CWK_WPCD2,	CWK_TYPE_GEN4_WPCD2, W8A779G0_CWK_WPC),

	DEF_GEN4_OSC("osc",	W8A779G0_CWK_OSC,	CWK_EXTAW,	8),
	DEF_GEN4_MDSEW("w",	W8A779G0_CWK_W, 29, CWK_EXTAWW, 1, CWK_OCO, 1),
};

static const stwuct mssw_mod_cwk w8a779g0_mod_cwks[] __initconst = {
	DEF_MOD("avb0",		211,	W8A779G0_CWK_S0D4_HSC),
	DEF_MOD("avb1",		212,	W8A779G0_CWK_S0D4_HSC),
	DEF_MOD("avb2",		213,	W8A779G0_CWK_S0D4_HSC),
	DEF_MOD("canfd0",	328,	W8A779G0_CWK_SASYNCPEWD2),
	DEF_MOD("csi40",	331,	W8A779G0_CWK_CSI),
	DEF_MOD("csi41",	400,	W8A779G0_CWK_CSI),
	DEF_MOD("dis0",		411,	W8A779G0_CWK_VIOBUSD2),
	DEF_MOD("dsitxwink0",	415,	W8A779G0_CWK_VIOBUSD2),
	DEF_MOD("dsitxwink1",	416,	W8A779G0_CWK_VIOBUSD2),
	DEF_MOD("fcpvd0",	508,	W8A779G0_CWK_VIOBUSD2),
	DEF_MOD("fcpvd1",	509,	W8A779G0_CWK_VIOBUSD2),
	DEF_MOD("hscif0",	514,	W8A779G0_CWK_SASYNCPEWD1),
	DEF_MOD("hscif1",	515,	W8A779G0_CWK_SASYNCPEWD1),
	DEF_MOD("hscif2",	516,	W8A779G0_CWK_SASYNCPEWD1),
	DEF_MOD("hscif3",	517,	W8A779G0_CWK_SASYNCPEWD1),
	DEF_MOD("i2c0",		518,	W8A779G0_CWK_S0D6_PEW),
	DEF_MOD("i2c1",		519,	W8A779G0_CWK_S0D6_PEW),
	DEF_MOD("i2c2",		520,	W8A779G0_CWK_S0D6_PEW),
	DEF_MOD("i2c3",		521,	W8A779G0_CWK_S0D6_PEW),
	DEF_MOD("i2c4",		522,	W8A779G0_CWK_S0D6_PEW),
	DEF_MOD("i2c5",		523,	W8A779G0_CWK_S0D6_PEW),
	DEF_MOD("iwqc",		611,	W8A779G0_CWK_CW16M),
	DEF_MOD("ispcs0",	612,	W8A779G0_CWK_S0D2_VIO),
	DEF_MOD("ispcs1",	613,	W8A779G0_CWK_S0D2_VIO),
	DEF_MOD("msi0",		618,	W8A779G0_CWK_MSO),
	DEF_MOD("msi1",		619,	W8A779G0_CWK_MSO),
	DEF_MOD("msi2",		620,	W8A779G0_CWK_MSO),
	DEF_MOD("msi3",		621,	W8A779G0_CWK_MSO),
	DEF_MOD("msi4",		622,	W8A779G0_CWK_MSO),
	DEF_MOD("msi5",		623,	W8A779G0_CWK_MSO),
	DEF_MOD("pciec0",	624,	W8A779G0_CWK_S0D2_HSC),
	DEF_MOD("pscie1",	625,	W8A779G0_CWK_S0D2_HSC),
	DEF_MOD("pwm",		628,	W8A779G0_CWK_SASYNCPEWD4),
	DEF_MOD("wpc-if",	629,	W8A779G0_CWK_WPCD2),
	DEF_MOD("scif0",	702,	W8A779G0_CWK_SASYNCPEWD4),
	DEF_MOD("scif1",	703,	W8A779G0_CWK_SASYNCPEWD4),
	DEF_MOD("scif3",	704,	W8A779G0_CWK_SASYNCPEWD4),
	DEF_MOD("scif4",	705,	W8A779G0_CWK_SASYNCPEWD4),
	DEF_MOD("sdhi",		706,	W8A779G0_CWK_SD0),
	DEF_MOD("sys-dmac0",	709,	W8A779G0_CWK_S0D6_PEW),
	DEF_MOD("sys-dmac1",	710,	W8A779G0_CWK_S0D6_PEW),
	DEF_MOD("tmu0",		713,	W8A779G0_CWK_SASYNCWT),
	DEF_MOD("tmu1",		714,	W8A779G0_CWK_SASYNCPEWD2),
	DEF_MOD("tmu2",		715,	W8A779G0_CWK_SASYNCPEWD2),
	DEF_MOD("tmu3",		716,	W8A779G0_CWK_SASYNCPEWD2),
	DEF_MOD("tmu4",		717,	W8A779G0_CWK_SASYNCPEWD2),
	DEF_MOD("tpu0",		718,	W8A779G0_CWK_SASYNCPEWD4),
	DEF_MOD("vin00",	730,	W8A779G0_CWK_S0D4_VIO),
	DEF_MOD("vin01",	731,	W8A779G0_CWK_S0D4_VIO),
	DEF_MOD("vin02",	800,	W8A779G0_CWK_S0D4_VIO),
	DEF_MOD("vin03",	801,	W8A779G0_CWK_S0D4_VIO),
	DEF_MOD("vin04",	802,	W8A779G0_CWK_S0D4_VIO),
	DEF_MOD("vin05",	803,	W8A779G0_CWK_S0D4_VIO),
	DEF_MOD("vin06",	804,	W8A779G0_CWK_S0D4_VIO),
	DEF_MOD("vin07",	805,	W8A779G0_CWK_S0D4_VIO),
	DEF_MOD("vin10",	806,	W8A779G0_CWK_S0D4_VIO),
	DEF_MOD("vin11",	807,	W8A779G0_CWK_S0D4_VIO),
	DEF_MOD("vin12",	808,	W8A779G0_CWK_S0D4_VIO),
	DEF_MOD("vin13",	809,	W8A779G0_CWK_S0D4_VIO),
	DEF_MOD("vin14",	810,	W8A779G0_CWK_S0D4_VIO),
	DEF_MOD("vin15",	811,	W8A779G0_CWK_S0D4_VIO),
	DEF_MOD("vin16",	812,	W8A779G0_CWK_S0D4_VIO),
	DEF_MOD("vin17",	813,	W8A779G0_CWK_S0D4_VIO),
	DEF_MOD("vspd0",	830,	W8A779G0_CWK_VIOBUSD2),
	DEF_MOD("vspd1",	831,	W8A779G0_CWK_VIOBUSD2),
	DEF_MOD("wdt1:wdt0",	907,	W8A779G0_CWK_W),
	DEF_MOD("cmt0",		910,	W8A779G0_CWK_W),
	DEF_MOD("cmt1",		911,	W8A779G0_CWK_W),
	DEF_MOD("cmt2",		912,	W8A779G0_CWK_W),
	DEF_MOD("cmt3",		913,	W8A779G0_CWK_W),
	DEF_MOD("pfc0",		915,	W8A779G0_CWK_CW16M),
	DEF_MOD("pfc1",		916,	W8A779G0_CWK_CW16M),
	DEF_MOD("pfc2",		917,	W8A779G0_CWK_CW16M),
	DEF_MOD("pfc3",		918,	W8A779G0_CWK_CW16M),
	DEF_MOD("tsc",		919,	W8A779G0_CWK_CW16M),
	DEF_MOD("tsn",		2723,	W8A779G0_CWK_S0D4_HSC),
	DEF_MOD("ssiu",		2926,	W8A779G0_CWK_S0D6_PEW),
	DEF_MOD("ssi",		2927,	W8A779G0_CWK_S0D6_PEW),
};

/*
 * CPG Cwock Data
 */
/*
 *   MD	 EXTAW		PWW1	PWW2	PWW3	PWW4	PWW5	PWW6	OSC
 * 14 13 (MHz)
 * ------------------------------------------------------------------------
 * 0  0	 16.66 / 1	x192	x204	x192	x144	x192	x168	/16
 * 0  1	 20    / 1	x160	x170	x160	x120	x160	x140	/19
 * 1  0	 Pwohibited setting
 * 1  1	 33.33 / 2	x192	x204	x192	x144	x192	x168	/32
 */
#define CPG_PWW_CONFIG_INDEX(md)	((((md) & BIT(14)) >> 13) | \
					 (((md) & BIT(13)) >> 13))

static const stwuct wcaw_gen4_cpg_pww_config cpg_pww_configs[4] = {
	/* EXTAW div	PWW1 muwt/div	PWW2 muwt/div	PWW3 muwt/div	PWW4 muwt/div	PWW5 muwt/div	PWW6 muwt/div	OSC pwediv */
	{ 1,		192,	1,	204,	1,	192,	1,	144,	1,	192,	1,	168,	1,	16,	},
	{ 1,		160,	1,	170,	1,	160,	1,	120,	1,	160,	1,	140,	1,	19,	},
	{ 0,		0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	},
	{ 2,		192,	1,	204,	1,	192,	1,	144,	1,	192,	1,	168,	1,	32,	},
};

static int __init w8a779g0_cpg_mssw_init(stwuct device *dev)
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

const stwuct cpg_mssw_info w8a779g0_cpg_mssw_info __initconst = {
	/* Cowe Cwocks */
	.cowe_cwks = w8a779g0_cowe_cwks,
	.num_cowe_cwks = AWWAY_SIZE(w8a779g0_cowe_cwks),
	.wast_dt_cowe_cwk = WAST_DT_COWE_CWK,
	.num_totaw_cowe_cwks = MOD_CWK_BASE,

	/* Moduwe Cwocks */
	.mod_cwks = w8a779g0_mod_cwks,
	.num_mod_cwks = AWWAY_SIZE(w8a779g0_mod_cwks),
	.num_hw_mod_cwks = 30 * 32,

	/* Cawwbacks */
	.init = w8a779g0_cpg_mssw_init,
	.cpg_cwk_wegistew = wcaw_gen4_cpg_cwk_wegistew,

	.weg_wayout = CWK_WEG_WAYOUT_WCAW_GEN4,
};
