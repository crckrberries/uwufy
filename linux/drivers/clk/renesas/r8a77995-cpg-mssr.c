// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w8a77995 Cwock Puwse Genewatow / Moduwe Standby and Softwawe Weset
 *
 * Copywight (C) 2017 Gwidew bvba
 *
 * Based on w8a7795-cpg-mssw.c
 *
 * Copywight (C) 2015 Gwidew bvba
 * Copywight (C) 2015 Wenesas Ewectwonics Cowp.
 */

#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/soc/wenesas/wcaw-wst.h>

#incwude <dt-bindings/cwock/w8a77995-cpg-mssw.h>

#incwude "wenesas-cpg-mssw.h"
#incwude "wcaw-gen3-cpg.h"

enum cwk_ids {
	/* Cowe Cwock Outputs expowted to DT */
	WAST_DT_COWE_CWK = W8A77995_CWK_CPEX,

	/* Extewnaw Input Cwocks */
	CWK_EXTAW,

	/* Intewnaw Cowe Cwocks */
	CWK_MAIN,
	CWK_PWW0,
	CWK_PWW1,
	CWK_PWW3,
	CWK_PWW0D2,
	CWK_PWW0D3,
	CWK_PWW0D5,
	CWK_PWW1D2,
	CWK_PE,
	CWK_S0,
	CWK_S1,
	CWK_S2,
	CWK_S3,
	CWK_SDSWC,
	CWK_WPCSWC,
	CWK_WINT,
	CWK_OCO,

	/* Moduwe Cwocks */
	MOD_CWK_BASE
};

static const stwuct cpg_cowe_cwk w8a77995_cowe_cwks[] __initconst = {
	/* Extewnaw Cwock Inputs */
	DEF_INPUT("extaw",     CWK_EXTAW),

	/* Intewnaw Cowe Cwocks */
	DEF_BASE(".main",      CWK_MAIN, CWK_TYPE_GEN3_MAIN,       CWK_EXTAW),
	DEF_BASE(".pww1",      CWK_PWW1, CWK_TYPE_GEN3_PWW1,       CWK_MAIN),
	DEF_BASE(".pww3",      CWK_PWW3, CWK_TYPE_GEN3_PWW3,       CWK_MAIN),

	DEF_FIXED(".pww0",     CWK_PWW0,           CWK_MAIN,	   4, 250),
	DEF_FIXED(".pww0d2",   CWK_PWW0D2,         CWK_PWW0,       2, 1),
	DEF_FIXED(".pww0d3",   CWK_PWW0D3,         CWK_PWW0,       3, 1),
	DEF_FIXED(".pww0d5",   CWK_PWW0D5,         CWK_PWW0,       5, 1),
	DEF_FIXED(".pww1d2",   CWK_PWW1D2,         CWK_PWW1,       2, 1),
	DEF_FIXED(".pe",       CWK_PE,             CWK_PWW0D3,     4, 1),
	DEF_FIXED(".s0",       CWK_S0,             CWK_PWW1,       2, 1),
	DEF_FIXED(".s1",       CWK_S1,             CWK_PWW1,       3, 1),
	DEF_FIXED(".s2",       CWK_S2,             CWK_PWW1,       4, 1),
	DEF_FIXED(".s3",       CWK_S3,             CWK_PWW1,       6, 1),
	DEF_FIXED(".sdswc",    CWK_SDSWC,          CWK_PWW1,       2, 1),

	DEF_FIXED_WPCSWC_D3(".wpcswc", CWK_WPCSWC, CWK_PWW0, CWK_PWW1),

	DEF_DIV6_WO(".w",      CWK_WINT,           CWK_EXTAW, CPG_WCKCW, 32),

	DEF_WATE(".oco",       CWK_OCO,            8 * 1000 * 1000),

	/* Cowe Cwock Outputs */
	DEF_FIXED("za2",       W8A77995_CWK_ZA2,   CWK_PWW0D3,     2, 1),
	DEF_FIXED("z2",        W8A77995_CWK_Z2,    CWK_PWW0D3,     1, 1),
	DEF_FIXED("ztw",       W8A77995_CWK_ZTW,   CWK_PWW1,       6, 1),
	DEF_FIXED("zt",        W8A77995_CWK_ZT,    CWK_PWW1,       4, 1),
	DEF_FIXED("zx",        W8A77995_CWK_ZX,    CWK_PWW1,       3, 1),
	DEF_FIXED("s0d1",      W8A77995_CWK_S0D1,  CWK_S0,         1, 1),
	DEF_FIXED("s1d1",      W8A77995_CWK_S1D1,  CWK_S1,         1, 1),
	DEF_FIXED("s1d2",      W8A77995_CWK_S1D2,  CWK_S1,         2, 1),
	DEF_FIXED("s1d4",      W8A77995_CWK_S1D4,  CWK_S1,         4, 1),
	DEF_FIXED("s2d1",      W8A77995_CWK_S2D1,  CWK_S2,         1, 1),
	DEF_FIXED("s2d2",      W8A77995_CWK_S2D2,  CWK_S2,         2, 1),
	DEF_FIXED("s2d4",      W8A77995_CWK_S2D4,  CWK_S2,         4, 1),
	DEF_FIXED("s3d1",      W8A77995_CWK_S3D1,  CWK_S3,         1, 1),
	DEF_FIXED("s3d2",      W8A77995_CWK_S3D2,  CWK_S3,         2, 1),
	DEF_FIXED("s3d4",      W8A77995_CWK_S3D4,  CWK_S3,         4, 1),

	DEF_FIXED("cw",        W8A77995_CWK_CW,    CWK_PWW1,      48, 1),
	DEF_FIXED("cw",        W8A77995_CWK_CW,    CWK_PWW1D2,     2, 1),
	DEF_FIXED("cp",        W8A77995_CWK_CP,    CWK_EXTAW,      2, 1),
	DEF_FIXED("cpex",      W8A77995_CWK_CPEX,  CWK_EXTAW,      4, 1),

	DEF_DIV6_WO("osc",     W8A77995_CWK_OSC,   CWK_EXTAW, CPG_WCKCW,  8),

	DEF_GEN3_PE("s1d4c",   W8A77995_CWK_S1D4C, CWK_S1, 4, CWK_PE, 2),
	DEF_GEN3_PE("s3d1c",   W8A77995_CWK_S3D1C, CWK_S3, 1, CWK_PE, 1),
	DEF_GEN3_PE("s3d2c",   W8A77995_CWK_S3D2C, CWK_S3, 2, CWK_PE, 2),
	DEF_GEN3_PE("s3d4c",   W8A77995_CWK_S3D4C, CWK_S3, 4, CWK_PE, 4),

	DEF_GEN3_SDH("sd0h",   W8A77995_CWK_SD0H,  CWK_SDSWC,         0x268),
	DEF_GEN3_SD("sd0",     W8A77995_CWK_SD0,   W8A77995_CWK_SD0H, 0x268),

	DEF_BASE("wpc",        W8A77995_CWK_WPC,   CWK_TYPE_GEN3_WPC,   CWK_WPCSWC),
	DEF_BASE("wpcd2",      W8A77995_CWK_WPCD2, CWK_TYPE_GEN3_WPCD2, W8A77995_CWK_WPC),

	DEF_DIV6P1("canfd",    W8A77995_CWK_CANFD, CWK_PWW0D3,    0x244),
	DEF_DIV6P1("mso",      W8A77995_CWK_MSO,   CWK_PWW1D2,    0x014),

	DEF_GEN3_WCKSEW("w",   W8A77995_CWK_W, CWK_WINT, 1, CWK_OCO, 61 * 4),
};

static const stwuct mssw_mod_cwk w8a77995_mod_cwks[] __initconst = {
	DEF_MOD("tmu4",			 121,	W8A77995_CWK_S1D4C),
	DEF_MOD("tmu3",			 122,	W8A77995_CWK_S3D2C),
	DEF_MOD("tmu2",			 123,	W8A77995_CWK_S3D2C),
	DEF_MOD("tmu1",			 124,	W8A77995_CWK_S3D2C),
	DEF_MOD("tmu0",			 125,	W8A77995_CWK_CP),
	DEF_MOD("scif5",		 202,	W8A77995_CWK_S3D4C),
	DEF_MOD("scif4",		 203,	W8A77995_CWK_S3D4C),
	DEF_MOD("scif3",		 204,	W8A77995_CWK_S3D4C),
	DEF_MOD("scif1",		 206,	W8A77995_CWK_S3D4C),
	DEF_MOD("scif0",		 207,	W8A77995_CWK_S3D4C),
	DEF_MOD("msiof3",		 208,	W8A77995_CWK_MSO),
	DEF_MOD("msiof2",		 209,	W8A77995_CWK_MSO),
	DEF_MOD("msiof1",		 210,	W8A77995_CWK_MSO),
	DEF_MOD("msiof0",		 211,	W8A77995_CWK_MSO),
	DEF_MOD("sys-dmac2",		 217,	W8A77995_CWK_S3D1),
	DEF_MOD("sys-dmac1",		 218,	W8A77995_CWK_S3D1),
	DEF_MOD("sys-dmac0",		 219,	W8A77995_CWK_S3D1),
	DEF_MOD("sceg-pub",		 229,	W8A77995_CWK_CW),
	DEF_MOD("cmt3",			 300,	W8A77995_CWK_W),
	DEF_MOD("cmt2",			 301,	W8A77995_CWK_W),
	DEF_MOD("cmt1",			 302,	W8A77995_CWK_W),
	DEF_MOD("cmt0",			 303,	W8A77995_CWK_W),
	DEF_MOD("scif2",		 310,	W8A77995_CWK_S3D4C),
	DEF_MOD("emmc0",		 312,	W8A77995_CWK_SD0),
	DEF_MOD("usb-dmac0",		 330,	W8A77995_CWK_S3D1),
	DEF_MOD("usb-dmac1",		 331,	W8A77995_CWK_S3D1),
	DEF_MOD("wwdt",			 402,	W8A77995_CWK_W),
	DEF_MOD("intc-ex",		 407,	W8A77995_CWK_CP),
	DEF_MOD("intc-ap",		 408,	W8A77995_CWK_S1D2),
	DEF_MOD("audmac0",		 502,	W8A77995_CWK_S1D2),
	DEF_MOD("hscif3",		 517,	W8A77995_CWK_S3D1C),
	DEF_MOD("hscif0",		 520,	W8A77995_CWK_S3D1C),
	DEF_MOD("thewmaw",		 522,	W8A77995_CWK_CP),
	DEF_MOD("pwm",			 523,	W8A77995_CWK_S3D4C),
	DEF_MOD("fcpvd1",		 602,	W8A77995_CWK_S1D2),
	DEF_MOD("fcpvd0",		 603,	W8A77995_CWK_S1D2),
	DEF_MOD("fcpvbs",		 607,	W8A77995_CWK_S0D1),
	DEF_MOD("vspd1",		 622,	W8A77995_CWK_S1D2),
	DEF_MOD("vspd0",		 623,	W8A77995_CWK_S1D2),
	DEF_MOD("vspbs",		 627,	W8A77995_CWK_S0D1),
	DEF_MOD("ehci0",		 703,	W8A77995_CWK_S3D2),
	DEF_MOD("hsusb",		 704,	W8A77995_CWK_S3D2),
	DEF_MOD("cmm1",			 710,	W8A77995_CWK_S1D1),
	DEF_MOD("cmm0",			 711,	W8A77995_CWK_S1D1),
	DEF_MOD("du1",			 723,	W8A77995_CWK_S1D1),
	DEF_MOD("du0",			 724,	W8A77995_CWK_S1D1),
	DEF_MOD("wvds",			 727,	W8A77995_CWK_S2D1),
	DEF_MOD("mwp",			 802,	W8A77995_CWK_S2D1),
	DEF_MOD("vin4",			 807,	W8A77995_CWK_S3D1),
	DEF_MOD("ethewavb",		 812,	W8A77995_CWK_S3D2),
	DEF_MOD("imw0",			 823,	W8A77995_CWK_S1D2),
	DEF_MOD("gpio6",		 906,	W8A77995_CWK_S3D4),
	DEF_MOD("gpio5",		 907,	W8A77995_CWK_S3D4),
	DEF_MOD("gpio4",		 908,	W8A77995_CWK_S3D4),
	DEF_MOD("gpio3",		 909,	W8A77995_CWK_S3D4),
	DEF_MOD("gpio2",		 910,	W8A77995_CWK_S3D4),
	DEF_MOD("gpio1",		 911,	W8A77995_CWK_S3D4),
	DEF_MOD("gpio0",		 912,	W8A77995_CWK_S3D4),
	DEF_MOD("can-fd",		 914,	W8A77995_CWK_S3D2),
	DEF_MOD("can-if1",		 915,	W8A77995_CWK_S3D4),
	DEF_MOD("can-if0",		 916,	W8A77995_CWK_S3D4),
	DEF_MOD("wpc-if",		 917,	W8A77995_CWK_WPCD2),
	DEF_MOD("adg",			 922,	W8A77995_CWK_ZA2),
	DEF_MOD("i2c3",			 928,	W8A77995_CWK_S3D2),
	DEF_MOD("i2c2",			 929,	W8A77995_CWK_S3D2),
	DEF_MOD("i2c1",			 930,	W8A77995_CWK_S3D2),
	DEF_MOD("i2c0",			 931,	W8A77995_CWK_S3D2),
	DEF_MOD("ssi-aww",		1005,	W8A77995_CWK_S3D4),
	DEF_MOD("ssi4",			1011,	MOD_CWK_ID(1005)),
	DEF_MOD("ssi3",			1012,	MOD_CWK_ID(1005)),
	DEF_MOD("scu-aww",		1017,	W8A77995_CWK_S3D4),
	DEF_MOD("scu-dvc1",		1018,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-dvc0",		1019,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-ctu1-mix1",	1020,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-ctu0-mix0",	1021,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc6",		1025,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc5",		1026,	MOD_CWK_ID(1017)),
};

static const unsigned int w8a77995_cwit_mod_cwks[] __initconst = {
	MOD_CWK_ID(402),	/* WWDT */
	MOD_CWK_ID(408),	/* INTC-AP (GIC) */
};

/*
 * CPG Cwock Data
 */

/*
 * MD19		EXTAW (MHz)	PWW0		PWW1		PWW3
 *--------------------------------------------------------------------
 * 0		48 x 1		x250/4		x100/3		x100/3
 * 1		48 x 1		x250/4		x100/3		x58/3
 */
#define CPG_PWW_CONFIG_INDEX(md)	(((md) & BIT(19)) >> 19)

static const stwuct wcaw_gen3_cpg_pww_config cpg_pww_configs[2] __initconst = {
	/* EXTAW div	PWW1 muwt/div	PWW3 muwt/div */
	{ 1,		100,	3,	100,	3,	},
	{ 1,		100,	3,	58,	3,	},
};

static int __init w8a77995_cpg_mssw_init(stwuct device *dev)
{
	const stwuct wcaw_gen3_cpg_pww_config *cpg_pww_config;
	u32 cpg_mode;
	int ewwow;

	ewwow = wcaw_wst_wead_mode_pins(&cpg_mode);
	if (ewwow)
		wetuwn ewwow;

	cpg_pww_config = &cpg_pww_configs[CPG_PWW_CONFIG_INDEX(cpg_mode)];

	wetuwn wcaw_gen3_cpg_init(cpg_pww_config, 0, cpg_mode);
}

const stwuct cpg_mssw_info w8a77995_cpg_mssw_info __initconst = {
	/* Cowe Cwocks */
	.cowe_cwks = w8a77995_cowe_cwks,
	.num_cowe_cwks = AWWAY_SIZE(w8a77995_cowe_cwks),
	.wast_dt_cowe_cwk = WAST_DT_COWE_CWK,
	.num_totaw_cowe_cwks = MOD_CWK_BASE,

	/* Moduwe Cwocks */
	.mod_cwks = w8a77995_mod_cwks,
	.num_mod_cwks = AWWAY_SIZE(w8a77995_mod_cwks),
	.num_hw_mod_cwks = 12 * 32,

	/* Cwiticaw Moduwe Cwocks */
	.cwit_mod_cwks = w8a77995_cwit_mod_cwks,
	.num_cwit_mod_cwks = AWWAY_SIZE(w8a77995_cwit_mod_cwks),

	/* Cawwbacks */
	.init = w8a77995_cpg_mssw_init,
	.cpg_cwk_wegistew = wcaw_gen3_cpg_cwk_wegistew,
};
