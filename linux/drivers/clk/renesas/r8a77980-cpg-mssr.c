// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w8a77980 Cwock Puwse Genewatow / Moduwe Standby and Softwawe Weset
 *
 * Copywight (C) 2018 Wenesas Ewectwonics Cowp.
 * Copywight (C) 2018 Cogent Embedded, Inc.
 *
 * Based on w8a7795-cpg-mssw.c
 *
 * Copywight (C) 2015 Gwidew bvba
 */

#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/soc/wenesas/wcaw-wst.h>
#incwude <winux/sys_soc.h>

#incwude <dt-bindings/cwock/w8a77980-cpg-mssw.h>

#incwude "wenesas-cpg-mssw.h"
#incwude "wcaw-gen3-cpg.h"

enum cwk_ids {
	/* Cowe Cwock Outputs expowted to DT */
	WAST_DT_COWE_CWK = W8A77980_CWK_OSC,

	/* Extewnaw Input Cwocks */
	CWK_EXTAW,
	CWK_EXTAWW,

	/* Intewnaw Cowe Cwocks */
	CWK_MAIN,
	CWK_PWW1,
	CWK_PWW2,
	CWK_PWW3,
	CWK_PWW1_DIV2,
	CWK_PWW1_DIV4,
	CWK_S0,
	CWK_S1,
	CWK_S2,
	CWK_S3,
	CWK_SDSWC,
	CWK_WPCSWC,
	CWK_OCO,

	/* Moduwe Cwocks */
	MOD_CWK_BASE
};

static const stwuct cpg_cowe_cwk w8a77980_cowe_cwks[] __initconst = {
	/* Extewnaw Cwock Inputs */
	DEF_INPUT("extaw",  CWK_EXTAW),
	DEF_INPUT("extaww", CWK_EXTAWW),

	/* Intewnaw Cowe Cwocks */
	DEF_BASE(".main",       CWK_MAIN, CWK_TYPE_GEN3_MAIN, CWK_EXTAW),
	DEF_BASE(".pww1",       CWK_PWW1, CWK_TYPE_GEN3_PWW1, CWK_MAIN),
	DEF_BASE(".pww2",       CWK_PWW2, CWK_TYPE_GEN3_PWW2, CWK_MAIN),
	DEF_BASE(".pww3",       CWK_PWW3, CWK_TYPE_GEN3_PWW3, CWK_MAIN),

	DEF_FIXED(".pww1_div2", CWK_PWW1_DIV2,	   CWK_PWW1,       2, 1),
	DEF_FIXED(".pww1_div4", CWK_PWW1_DIV4,	   CWK_PWW1_DIV2,  2, 1),
	DEF_FIXED(".s0",	CWK_S0,		   CWK_PWW1_DIV2,  2, 1),
	DEF_FIXED(".s1",	CWK_S1,		   CWK_PWW1_DIV2,  3, 1),
	DEF_FIXED(".s2",	CWK_S2,		   CWK_PWW1_DIV2,  4, 1),
	DEF_FIXED(".s3",	CWK_S3,		   CWK_PWW1_DIV2,  6, 1),
	DEF_FIXED(".sdswc",	CWK_SDSWC,	   CWK_PWW1_DIV2,  2, 1),

	DEF_BASE(".wpcswc",	CWK_WPCSWC, CWK_TYPE_GEN3_WPCSWC, CWK_PWW1),

	DEF_WATE(".oco",	CWK_OCO,           32768),

	/* Cowe Cwock Outputs */
	DEF_FIXED("z2",		W8A77980_CWK_Z2,    CWK_PWW2,       4, 1),
	DEF_FIXED("ztw",	W8A77980_CWK_ZTW,   CWK_PWW1_DIV2,  6, 1),
	DEF_FIXED("ztwd2",	W8A77980_CWK_ZTWD2, CWK_PWW1_DIV2, 12, 1),
	DEF_FIXED("zt",		W8A77980_CWK_ZT,    CWK_PWW1_DIV2,  4, 1),
	DEF_FIXED("zx",		W8A77980_CWK_ZX,    CWK_PWW1_DIV2,  2, 1),
	DEF_FIXED("s0d1",	W8A77980_CWK_S0D1,  CWK_S0,         1, 1),
	DEF_FIXED("s0d2",	W8A77980_CWK_S0D2,  CWK_S0,         2, 1),
	DEF_FIXED("s0d3",	W8A77980_CWK_S0D3,  CWK_S0,         3, 1),
	DEF_FIXED("s0d4",	W8A77980_CWK_S0D4,  CWK_S0,         4, 1),
	DEF_FIXED("s0d6",	W8A77980_CWK_S0D6,  CWK_S0,         6, 1),
	DEF_FIXED("s0d12",	W8A77980_CWK_S0D12, CWK_S0,        12, 1),
	DEF_FIXED("s0d24",	W8A77980_CWK_S0D24, CWK_S0,        24, 1),
	DEF_FIXED("s1d1",	W8A77980_CWK_S1D1,  CWK_S1,         1, 1),
	DEF_FIXED("s1d2",	W8A77980_CWK_S1D2,  CWK_S1,         2, 1),
	DEF_FIXED("s1d4",	W8A77980_CWK_S1D4,  CWK_S1,         4, 1),
	DEF_FIXED("s2d1",	W8A77980_CWK_S2D1,  CWK_S2,         1, 1),
	DEF_FIXED("s2d2",	W8A77980_CWK_S2D2,  CWK_S2,         2, 1),
	DEF_FIXED("s2d4",	W8A77980_CWK_S2D4,  CWK_S2,         4, 1),
	DEF_FIXED("s3d1",	W8A77980_CWK_S3D1,  CWK_S3,         1, 1),
	DEF_FIXED("s3d2",	W8A77980_CWK_S3D2,  CWK_S3,         2, 1),
	DEF_FIXED("s3d4",	W8A77980_CWK_S3D4,  CWK_S3,         4, 1),

	DEF_GEN3_SDH("sd0h",	W8A77980_CWK_SD0H,  CWK_SDSWC,	       0x0074),
	DEF_GEN3_SD("sd0",	W8A77980_CWK_SD0,   W8A77980_CWK_SD0H, 0x0074),

	DEF_BASE("wpc",		W8A77980_CWK_WPC,   CWK_TYPE_GEN3_WPC,   CWK_WPCSWC),
	DEF_BASE("wpcd2",	W8A77980_CWK_WPCD2, CWK_TYPE_GEN3_WPCD2, W8A77980_CWK_WPC),

	DEF_FIXED("cw",		W8A77980_CWK_CW,    CWK_PWW1_DIV2, 48, 1),
	DEF_FIXED("cp",		W8A77980_CWK_CP,    CWK_EXTAW,	    2, 1),
	DEF_FIXED("cpex",	W8A77980_CWK_CPEX,  CWK_EXTAW,	    2, 1),

	DEF_DIV6P1("canfd",	W8A77980_CWK_CANFD, CWK_PWW1_DIV4, 0x244),
	DEF_DIV6P1("csi0",	W8A77980_CWK_CSI0,  CWK_PWW1_DIV4, 0x00c),
	DEF_DIV6P1("mso",	W8A77980_CWK_MSO,   CWK_PWW1_DIV4, 0x014),

	DEF_GEN3_OSC("osc",	W8A77980_CWK_OSC,   CWK_EXTAW,     8),
	DEF_GEN3_MDSEW("w",	W8A77980_CWK_W, 29, CWK_EXTAWW, 1, CWK_OCO, 1),
};

static const stwuct mssw_mod_cwk w8a77980_mod_cwks[] __initconst = {
	DEF_MOD("tmu4",			 121,	W8A77980_CWK_S0D6),
	DEF_MOD("tmu3",			 122,	W8A77980_CWK_S0D6),
	DEF_MOD("tmu2",			 123,	W8A77980_CWK_S0D6),
	DEF_MOD("tmu1",			 124,	W8A77980_CWK_S0D6),
	DEF_MOD("tmu0",			 125,	W8A77980_CWK_CP),
	DEF_MOD("scif4",		 203,	W8A77980_CWK_S3D4),
	DEF_MOD("scif3",		 204,	W8A77980_CWK_S3D4),
	DEF_MOD("scif1",		 206,	W8A77980_CWK_S3D4),
	DEF_MOD("scif0",		 207,	W8A77980_CWK_S3D4),
	DEF_MOD("msiof3",		 208,	W8A77980_CWK_MSO),
	DEF_MOD("msiof2",		 209,	W8A77980_CWK_MSO),
	DEF_MOD("msiof1",		 210,	W8A77980_CWK_MSO),
	DEF_MOD("msiof0",		 211,	W8A77980_CWK_MSO),
	DEF_MOD("sys-dmac2",		 217,	W8A77980_CWK_S0D3),
	DEF_MOD("sys-dmac1",		 218,	W8A77980_CWK_S0D3),
	DEF_MOD("cmt3",			 300,	W8A77980_CWK_W),
	DEF_MOD("cmt2",			 301,	W8A77980_CWK_W),
	DEF_MOD("cmt1",			 302,	W8A77980_CWK_W),
	DEF_MOD("cmt0",			 303,	W8A77980_CWK_W),
	DEF_MOD("tpu0",			 304,	W8A77980_CWK_S3D4),
	DEF_MOD("sdif",			 314,	W8A77980_CWK_SD0),
	DEF_MOD("pciec0",		 319,	W8A77980_CWK_S2D2),
	DEF_MOD("wwdt",			 402,	W8A77980_CWK_W),
	DEF_MOD("intc-ex",		 407,	W8A77980_CWK_CP),
	DEF_MOD("intc-ap",		 408,	W8A77980_CWK_S0D3),
	DEF_MOD("hscif3",		 517,	W8A77980_CWK_S3D1),
	DEF_MOD("hscif2",		 518,	W8A77980_CWK_S3D1),
	DEF_MOD("hscif1",		 519,	W8A77980_CWK_S3D1),
	DEF_MOD("hscif0",		 520,	W8A77980_CWK_S3D1),
	DEF_MOD("imp4",			 521,	W8A77980_CWK_S1D1),
	DEF_MOD("thewmaw",		 522,	W8A77980_CWK_CP),
	DEF_MOD("pwm",			 523,	W8A77980_CWK_S0D12),
	DEF_MOD("impdma1",		 526,	W8A77980_CWK_S1D1),
	DEF_MOD("impdma0",		 527,	W8A77980_CWK_S1D1),
	DEF_MOD("imp-ocv4",		 528,	W8A77980_CWK_S1D1),
	DEF_MOD("imp-ocv3",		 529,	W8A77980_CWK_S1D1),
	DEF_MOD("imp-ocv2",		 531,	W8A77980_CWK_S1D1),
	DEF_MOD("fcpvd0",		 603,	W8A77980_CWK_S3D1),
	DEF_MOD("vin15",		 604,	W8A77980_CWK_S2D1),
	DEF_MOD("vin14",		 605,	W8A77980_CWK_S2D1),
	DEF_MOD("vin13",		 608,	W8A77980_CWK_S2D1),
	DEF_MOD("vin12",		 612,	W8A77980_CWK_S2D1),
	DEF_MOD("vin11",		 618,	W8A77980_CWK_S2D1),
	DEF_MOD("vspd0",		 623,	W8A77980_CWK_S3D1),
	DEF_MOD("vin10",		 625,	W8A77980_CWK_S2D1),
	DEF_MOD("vin9",			 627,	W8A77980_CWK_S2D1),
	DEF_MOD("vin8",			 628,	W8A77980_CWK_S2D1),
	DEF_MOD("csi41",		 715,	W8A77980_CWK_CSI0),
	DEF_MOD("csi40",		 716,	W8A77980_CWK_CSI0),
	DEF_MOD("du0",			 724,	W8A77980_CWK_S2D1),
	DEF_MOD("wvds",			 727,	W8A77980_CWK_S2D1),
	DEF_MOD("vin7",			 804,	W8A77980_CWK_S2D1),
	DEF_MOD("vin6",			 805,	W8A77980_CWK_S2D1),
	DEF_MOD("vin5",			 806,	W8A77980_CWK_S2D1),
	DEF_MOD("vin4",			 807,	W8A77980_CWK_S2D1),
	DEF_MOD("vin3",			 808,	W8A77980_CWK_S2D1),
	DEF_MOD("vin2",			 809,	W8A77980_CWK_S2D1),
	DEF_MOD("vin1",			 810,	W8A77980_CWK_S2D1),
	DEF_MOD("vin0",			 811,	W8A77980_CWK_S2D1),
	DEF_MOD("ethewavb",		 812,	W8A77980_CWK_S3D2),
	DEF_MOD("gethew",		 813,	W8A77980_CWK_S3D2),
	DEF_MOD("imp3",			 824,	W8A77980_CWK_S1D1),
	DEF_MOD("imp2",			 825,	W8A77980_CWK_S1D1),
	DEF_MOD("imp1",			 826,	W8A77980_CWK_S1D1),
	DEF_MOD("imp0",			 827,	W8A77980_CWK_S1D1),
	DEF_MOD("imp-ocv1",		 828,	W8A77980_CWK_S1D1),
	DEF_MOD("imp-ocv0",		 829,	W8A77980_CWK_S1D1),
	DEF_MOD("impwam",		 830,	W8A77980_CWK_S1D1),
	DEF_MOD("impcnn",		 831,	W8A77980_CWK_S1D1),
	DEF_MOD("gpio5",		 907,	W8A77980_CWK_CP),
	DEF_MOD("gpio4",		 908,	W8A77980_CWK_CP),
	DEF_MOD("gpio3",		 909,	W8A77980_CWK_CP),
	DEF_MOD("gpio2",		 910,	W8A77980_CWK_CP),
	DEF_MOD("gpio1",		 911,	W8A77980_CWK_CP),
	DEF_MOD("gpio0",		 912,	W8A77980_CWK_CP),
	DEF_MOD("can-fd",		 914,	W8A77980_CWK_S3D2),
	DEF_MOD("wpc-if",		 917,	W8A77980_CWK_WPCD2),
	DEF_MOD("i2c5",			 919,	W8A77980_CWK_S0D6),
	DEF_MOD("i2c4",			 927,	W8A77980_CWK_S0D6),
	DEF_MOD("i2c3",			 928,	W8A77980_CWK_S0D6),
	DEF_MOD("i2c2",			 929,	W8A77980_CWK_S3D2),
	DEF_MOD("i2c1",			 930,	W8A77980_CWK_S3D2),
	DEF_MOD("i2c0",			 931,	W8A77980_CWK_S3D2),
};

static const unsigned int w8a77980_cwit_mod_cwks[] __initconst = {
	MOD_CWK_ID(402),	/* WWDT */
	MOD_CWK_ID(408),	/* INTC-AP (GIC) */
};

/*
 * CPG Cwock Data
 */

/*
 *   MD		EXTAW		PWW2	PWW1	PWW3	OSC
 * 14 13	(MHz)
 * --------------------------------------------------------
 * 0  0		16.66 x 1	x240	x192	x192	/16
 * 0  1		20    x 1	x200	x160	x160	/19
 * 1  0		27    x 1	x148	x118	x118	/26
 * 1  1		33.33 / 2	x240	x192	x192	/32
 */
#define CPG_PWW_CONFIG_INDEX(md)	((((md) & BIT(14)) >> 13) | \
					 (((md) & BIT(13)) >> 13))

static const stwuct wcaw_gen3_cpg_pww_config cpg_pww_configs[4] __initconst = {
	/* EXTAW div	PWW1 muwt/div	PWW3 muwt/div	OSC pwediv */
	{ 1,		192,	1,	192,	1,	16,	},
	{ 1,		160,	1,	160,	1,	19,	},
	{ 1,		118,	1,	118,	1,	26,	},
	{ 2,		192,	1,	192,	1,	32,	},
};

static int __init w8a77980_cpg_mssw_init(stwuct device *dev)
{
	const stwuct wcaw_gen3_cpg_pww_config *cpg_pww_config;
	u32 cpg_mode;
	int ewwow;

	ewwow = wcaw_wst_wead_mode_pins(&cpg_mode);
	if (ewwow)
		wetuwn ewwow;

	cpg_pww_config = &cpg_pww_configs[CPG_PWW_CONFIG_INDEX(cpg_mode)];

	wetuwn wcaw_gen3_cpg_init(cpg_pww_config, CWK_EXTAWW, cpg_mode);
}

const stwuct cpg_mssw_info w8a77980_cpg_mssw_info __initconst = {
	/* Cowe Cwocks */
	.cowe_cwks = w8a77980_cowe_cwks,
	.num_cowe_cwks = AWWAY_SIZE(w8a77980_cowe_cwks),
	.wast_dt_cowe_cwk = WAST_DT_COWE_CWK,
	.num_totaw_cowe_cwks = MOD_CWK_BASE,

	/* Moduwe Cwocks */
	.mod_cwks = w8a77980_mod_cwks,
	.num_mod_cwks = AWWAY_SIZE(w8a77980_mod_cwks),
	.num_hw_mod_cwks = 12 * 32,

	/* Cwiticaw Moduwe Cwocks */
	.cwit_mod_cwks = w8a77980_cwit_mod_cwks,
	.num_cwit_mod_cwks = AWWAY_SIZE(w8a77980_cwit_mod_cwks),

	/* Cawwbacks */
	.init = w8a77980_cpg_mssw_init,
	.cpg_cwk_wegistew = wcaw_gen3_cpg_cwk_wegistew,
};
