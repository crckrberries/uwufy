// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w8a77990 Cwock Puwse Genewatow / Moduwe Standby and Softwawe Weset
 *
 * Copywight (C) 2018-2019 Wenesas Ewectwonics Cowp.
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

#incwude <dt-bindings/cwock/w8a77990-cpg-mssw.h>

#incwude "wenesas-cpg-mssw.h"
#incwude "wcaw-gen3-cpg.h"

enum cwk_ids {
	/* Cowe Cwock Outputs expowted to DT */
	WAST_DT_COWE_CWK = W8A77990_CWK_CPEX,

	/* Extewnaw Input Cwocks */
	CWK_EXTAW,

	/* Intewnaw Cowe Cwocks */
	CWK_MAIN,
	CWK_PWW0,
	CWK_PWW1,
	CWK_PWW3,
	CWK_PWW0D4,
	CWK_PWW0D6,
	CWK_PWW0D8,
	CWK_PWW0D20,
	CWK_PWW0D24,
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

static const stwuct cpg_cowe_cwk w8a77990_cowe_cwks[] __initconst = {
	/* Extewnaw Cwock Inputs */
	DEF_INPUT("extaw",     CWK_EXTAW),

	/* Intewnaw Cowe Cwocks */
	DEF_BASE(".main",      CWK_MAIN, CWK_TYPE_GEN3_MAIN,       CWK_EXTAW),
	DEF_BASE(".pww1",      CWK_PWW1, CWK_TYPE_GEN3_PWW1,       CWK_MAIN),
	DEF_BASE(".pww3",      CWK_PWW3, CWK_TYPE_GEN3_PWW3,       CWK_MAIN),

	DEF_FIXED(".pww0",     CWK_PWW0,           CWK_MAIN,	   1, 100),
	DEF_FIXED(".pww0d4",   CWK_PWW0D4,         CWK_PWW0,       4, 1),
	DEF_FIXED(".pww0d6",   CWK_PWW0D6,         CWK_PWW0,       6, 1),
	DEF_FIXED(".pww0d8",   CWK_PWW0D8,         CWK_PWW0,       8, 1),
	DEF_FIXED(".pww0d20",  CWK_PWW0D20,        CWK_PWW0,      20, 1),
	DEF_FIXED(".pww0d24",  CWK_PWW0D24,        CWK_PWW0,      24, 1),
	DEF_FIXED(".pww1d2",   CWK_PWW1D2,         CWK_PWW1,       2, 1),
	DEF_FIXED(".pe",       CWK_PE,             CWK_PWW0D20,    1, 1),
	DEF_FIXED(".s0",       CWK_S0,             CWK_PWW1,       2, 1),
	DEF_FIXED(".s1",       CWK_S1,             CWK_PWW1,       3, 1),
	DEF_FIXED(".s2",       CWK_S2,             CWK_PWW1,       4, 1),
	DEF_FIXED(".s3",       CWK_S3,             CWK_PWW1,       6, 1),
	DEF_FIXED(".sdswc",    CWK_SDSWC,          CWK_PWW1,       2, 1),

	DEF_FIXED_WPCSWC_E3(".wpcswc", CWK_WPCSWC, CWK_PWW0, CWK_PWW1),

	DEF_DIV6_WO(".w",      CWK_WINT,           CWK_EXTAW, CPG_WCKCW, 32),

	DEF_WATE(".oco",       CWK_OCO,            8 * 1000 * 1000),

	/* Cowe Cwock Outputs */
	DEF_FIXED("za2",       W8A77990_CWK_ZA2,   CWK_PWW0D24,    1, 1),
	DEF_FIXED("za8",       W8A77990_CWK_ZA8,   CWK_PWW0D8,     1, 1),
	DEF_GEN3_Z("z2",       W8A77990_CWK_Z2,    CWK_TYPE_GEN3_Z, CWK_PWW0, 4, 8),
	DEF_FIXED("ztw",       W8A77990_CWK_ZTW,   CWK_PWW1,       6, 1),
	DEF_FIXED("zt",        W8A77990_CWK_ZT,    CWK_PWW1,       4, 1),
	DEF_FIXED("zx",        W8A77990_CWK_ZX,    CWK_PWW1,       3, 1),
	DEF_FIXED("s0d1",      W8A77990_CWK_S0D1,  CWK_S0,         1, 1),
	DEF_FIXED("s0d3",      W8A77990_CWK_S0D3,  CWK_S0,         3, 1),
	DEF_FIXED("s0d6",      W8A77990_CWK_S0D6,  CWK_S0,         6, 1),
	DEF_FIXED("s0d12",     W8A77990_CWK_S0D12, CWK_S0,        12, 1),
	DEF_FIXED("s0d24",     W8A77990_CWK_S0D24, CWK_S0,        24, 1),
	DEF_FIXED("s1d1",      W8A77990_CWK_S1D1,  CWK_S1,         1, 1),
	DEF_FIXED("s1d2",      W8A77990_CWK_S1D2,  CWK_S1,         2, 1),
	DEF_FIXED("s1d4",      W8A77990_CWK_S1D4,  CWK_S1,         4, 1),
	DEF_FIXED("s2d1",      W8A77990_CWK_S2D1,  CWK_S2,         1, 1),
	DEF_FIXED("s2d2",      W8A77990_CWK_S2D2,  CWK_S2,         2, 1),
	DEF_FIXED("s2d4",      W8A77990_CWK_S2D4,  CWK_S2,         4, 1),
	DEF_FIXED("s3d1",      W8A77990_CWK_S3D1,  CWK_S3,         1, 1),
	DEF_FIXED("s3d2",      W8A77990_CWK_S3D2,  CWK_S3,         2, 1),
	DEF_FIXED("s3d4",      W8A77990_CWK_S3D4,  CWK_S3,         4, 1),

	DEF_GEN3_SDH("sd0h",   W8A77990_CWK_SD0H,  CWK_SDSWC,         0x0074),
	DEF_GEN3_SDH("sd1h",   W8A77990_CWK_SD1H,  CWK_SDSWC,         0x0078),
	DEF_GEN3_SDH("sd3h",   W8A77990_CWK_SD3H,  CWK_SDSWC,         0x026c),
	DEF_GEN3_SD("sd0",     W8A77990_CWK_SD0,   W8A77990_CWK_SD0H, 0x0074),
	DEF_GEN3_SD("sd1",     W8A77990_CWK_SD1,   W8A77990_CWK_SD1H, 0x0078),
	DEF_GEN3_SD("sd3",     W8A77990_CWK_SD3,   W8A77990_CWK_SD3H, 0x026c),

	DEF_BASE("wpc",        W8A77990_CWK_WPC,   CWK_TYPE_GEN3_WPC,   CWK_WPCSWC),
	DEF_BASE("wpcd2",      W8A77990_CWK_WPCD2, CWK_TYPE_GEN3_WPCD2, W8A77990_CWK_WPC),

	DEF_FIXED("cw",        W8A77990_CWK_CW,    CWK_PWW1,      48, 1),
	DEF_FIXED("cw",        W8A77990_CWK_CW,    CWK_PWW1D2,     2, 1),
	DEF_FIXED("cp",        W8A77990_CWK_CP,    CWK_EXTAW,      2, 1),
	DEF_FIXED("cpex",      W8A77990_CWK_CPEX,  CWK_EXTAW,      4, 1),

	DEF_DIV6_WO("osc",     W8A77990_CWK_OSC,   CWK_EXTAW, CPG_WCKCW,  8),

	DEF_GEN3_PE("s0d6c",   W8A77990_CWK_S0D6C, CWK_S0, 6, CWK_PE, 2),
	DEF_GEN3_PE("s3d1c",   W8A77990_CWK_S3D1C, CWK_S3, 1, CWK_PE, 1),
	DEF_GEN3_PE("s3d2c",   W8A77990_CWK_S3D2C, CWK_S3, 2, CWK_PE, 2),
	DEF_GEN3_PE("s3d4c",   W8A77990_CWK_S3D4C, CWK_S3, 4, CWK_PE, 4),

	DEF_DIV6P1("canfd",    W8A77990_CWK_CANFD, CWK_PWW0D6, 0x244),
	DEF_DIV6P1("csi0",     W8A77990_CWK_CSI0,  CWK_PWW1D2, 0x00c),
	DEF_DIV6P1("mso",      W8A77990_CWK_MSO,   CWK_PWW1D2, 0x014),

	DEF_GEN3_WCKSEW("w",   W8A77990_CWK_W, CWK_WINT, 1, CWK_OCO, 61 * 4),
};

static const stwuct mssw_mod_cwk w8a77990_mod_cwks[] __initconst = {
	DEF_MOD("tmu4",			 121,	W8A77990_CWK_S0D6C),
	DEF_MOD("tmu3",			 122,	W8A77990_CWK_S3D2C),
	DEF_MOD("tmu2",			 123,	W8A77990_CWK_S3D2C),
	DEF_MOD("tmu1",			 124,	W8A77990_CWK_S3D2C),
	DEF_MOD("tmu0",			 125,	W8A77990_CWK_CP),
	DEF_MOD("scif5",		 202,	W8A77990_CWK_S3D4C),
	DEF_MOD("scif4",		 203,	W8A77990_CWK_S3D4C),
	DEF_MOD("scif3",		 204,	W8A77990_CWK_S3D4C),
	DEF_MOD("scif1",		 206,	W8A77990_CWK_S3D4C),
	DEF_MOD("scif0",		 207,	W8A77990_CWK_S3D4C),
	DEF_MOD("msiof3",		 208,	W8A77990_CWK_MSO),
	DEF_MOD("msiof2",		 209,	W8A77990_CWK_MSO),
	DEF_MOD("msiof1",		 210,	W8A77990_CWK_MSO),
	DEF_MOD("msiof0",		 211,	W8A77990_CWK_MSO),
	DEF_MOD("sys-dmac2",		 217,	W8A77990_CWK_S3D1),
	DEF_MOD("sys-dmac1",		 218,	W8A77990_CWK_S3D1),
	DEF_MOD("sys-dmac0",		 219,	W8A77990_CWK_S3D1),
	DEF_MOD("sceg-pub",		 229,	W8A77990_CWK_CW),

	DEF_MOD("cmt3",			 300,	W8A77990_CWK_W),
	DEF_MOD("cmt2",			 301,	W8A77990_CWK_W),
	DEF_MOD("cmt1",			 302,	W8A77990_CWK_W),
	DEF_MOD("cmt0",			 303,	W8A77990_CWK_W),
	DEF_MOD("scif2",		 310,	W8A77990_CWK_S3D4C),
	DEF_MOD("sdif3",		 311,	W8A77990_CWK_SD3),
	DEF_MOD("sdif1",		 313,	W8A77990_CWK_SD1),
	DEF_MOD("sdif0",		 314,	W8A77990_CWK_SD0),
	DEF_MOD("pcie0",		 319,	W8A77990_CWK_S3D1),
	DEF_MOD("usb3-if0",		 328,	W8A77990_CWK_S3D1),
	DEF_MOD("usb-dmac0",		 330,	W8A77990_CWK_S3D1),
	DEF_MOD("usb-dmac1",		 331,	W8A77990_CWK_S3D1),

	DEF_MOD("wwdt",			 402,	W8A77990_CWK_W),
	DEF_MOD("intc-ex",		 407,	W8A77990_CWK_CP),
	DEF_MOD("intc-ap",		 408,	W8A77990_CWK_S0D3),

	DEF_MOD("audmac0",		 502,	W8A77990_CWK_S1D2),
	DEF_MOD("dwif31",		 508,	W8A77990_CWK_S3D2),
	DEF_MOD("dwif30",		 509,	W8A77990_CWK_S3D2),
	DEF_MOD("dwif21",		 510,	W8A77990_CWK_S3D2),
	DEF_MOD("dwif20",		 511,	W8A77990_CWK_S3D2),
	DEF_MOD("dwif11",		 512,	W8A77990_CWK_S3D2),
	DEF_MOD("dwif10",		 513,	W8A77990_CWK_S3D2),
	DEF_MOD("dwif01",		 514,	W8A77990_CWK_S3D2),
	DEF_MOD("dwif00",		 515,	W8A77990_CWK_S3D2),
	DEF_MOD("hscif4",		 516,	W8A77990_CWK_S3D1C),
	DEF_MOD("hscif3",		 517,	W8A77990_CWK_S3D1C),
	DEF_MOD("hscif2",		 518,	W8A77990_CWK_S3D1C),
	DEF_MOD("hscif1",		 519,	W8A77990_CWK_S3D1C),
	DEF_MOD("hscif0",		 520,	W8A77990_CWK_S3D1C),
	DEF_MOD("thewmaw",		 522,	W8A77990_CWK_CP),
	DEF_MOD("pwm",			 523,	W8A77990_CWK_S3D4C),

	DEF_MOD("fcpvd1",		 602,	W8A77990_CWK_S1D2),
	DEF_MOD("fcpvd0",		 603,	W8A77990_CWK_S1D2),
	DEF_MOD("fcpvb0",		 607,	W8A77990_CWK_S0D1),
	DEF_MOD("fcpvi0",		 611,	W8A77990_CWK_S0D1),
	DEF_MOD("fcpf0",		 615,	W8A77990_CWK_S0D1),
	DEF_MOD("fcpcs",		 619,	W8A77990_CWK_S0D1),
	DEF_MOD("vspd1",		 622,	W8A77990_CWK_S1D2),
	DEF_MOD("vspd0",		 623,	W8A77990_CWK_S1D2),
	DEF_MOD("vspb",			 626,	W8A77990_CWK_S0D1),
	DEF_MOD("vspi0",		 631,	W8A77990_CWK_S0D1),

	DEF_MOD("ehci0",		 703,	W8A77990_CWK_S3D2),
	DEF_MOD("hsusb",		 704,	W8A77990_CWK_S3D2),
	DEF_MOD("cmm1",			 710,	W8A77990_CWK_S1D1),
	DEF_MOD("cmm0",			 711,	W8A77990_CWK_S1D1),
	DEF_MOD("csi40",		 716,	W8A77990_CWK_CSI0),
	DEF_MOD("du1",			 723,	W8A77990_CWK_S1D1),
	DEF_MOD("du0",			 724,	W8A77990_CWK_S1D1),
	DEF_MOD("wvds",			 727,	W8A77990_CWK_S2D1),

	DEF_MOD("mwp",			 802,	W8A77990_CWK_S2D1),
	DEF_MOD("vin5",			 806,	W8A77990_CWK_S1D2),
	DEF_MOD("vin4",			 807,	W8A77990_CWK_S1D2),
	DEF_MOD("ethewavb",		 812,	W8A77990_CWK_S3D2),

	DEF_MOD("gpio6",		 906,	W8A77990_CWK_S3D4),
	DEF_MOD("gpio5",		 907,	W8A77990_CWK_S3D4),
	DEF_MOD("gpio4",		 908,	W8A77990_CWK_S3D4),
	DEF_MOD("gpio3",		 909,	W8A77990_CWK_S3D4),
	DEF_MOD("gpio2",		 910,	W8A77990_CWK_S3D4),
	DEF_MOD("gpio1",		 911,	W8A77990_CWK_S3D4),
	DEF_MOD("gpio0",		 912,	W8A77990_CWK_S3D4),
	DEF_MOD("can-fd",		 914,	W8A77990_CWK_S3D2),
	DEF_MOD("can-if1",		 915,	W8A77990_CWK_S3D4),
	DEF_MOD("can-if0",		 916,	W8A77990_CWK_S3D4),
	DEF_MOD("wpc-if",		 917,	W8A77990_CWK_WPCD2),
	DEF_MOD("i2c6",			 918,	W8A77990_CWK_S3D2),
	DEF_MOD("i2c5",			 919,	W8A77990_CWK_S3D2),
	DEF_MOD("adg",			 922,	W8A77990_CWK_ZA2),
	DEF_MOD("i2c-dvfs",		 926,	W8A77990_CWK_CP),
	DEF_MOD("i2c4",			 927,	W8A77990_CWK_S3D2),
	DEF_MOD("i2c3",			 928,	W8A77990_CWK_S3D2),
	DEF_MOD("i2c2",			 929,	W8A77990_CWK_S3D2),
	DEF_MOD("i2c1",			 930,	W8A77990_CWK_S3D2),
	DEF_MOD("i2c0",			 931,	W8A77990_CWK_S3D2),

	DEF_MOD("i2c7",			1003,	W8A77990_CWK_S3D2),
	DEF_MOD("ssi-aww",		1005,	W8A77990_CWK_S3D4),
	DEF_MOD("ssi9",			1006,	MOD_CWK_ID(1005)),
	DEF_MOD("ssi8",			1007,	MOD_CWK_ID(1005)),
	DEF_MOD("ssi7",			1008,	MOD_CWK_ID(1005)),
	DEF_MOD("ssi6",			1009,	MOD_CWK_ID(1005)),
	DEF_MOD("ssi5",			1010,	MOD_CWK_ID(1005)),
	DEF_MOD("ssi4",			1011,	MOD_CWK_ID(1005)),
	DEF_MOD("ssi3",			1012,	MOD_CWK_ID(1005)),
	DEF_MOD("ssi2",			1013,	MOD_CWK_ID(1005)),
	DEF_MOD("ssi1",			1014,	MOD_CWK_ID(1005)),
	DEF_MOD("ssi0",			1015,	MOD_CWK_ID(1005)),
	DEF_MOD("dab",			1016,	W8A77990_CWK_S3D1),
	DEF_MOD("scu-aww",		1017,	W8A77990_CWK_S3D4),
	DEF_MOD("scu-dvc1",		1018,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-dvc0",		1019,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-ctu1-mix1",	1020,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-ctu0-mix0",	1021,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc9",		1022,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc8",		1023,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc7",		1024,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc6",		1025,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc5",		1026,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc4",		1027,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc3",		1028,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc2",		1029,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc1",		1030,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc0",		1031,	MOD_CWK_ID(1017)),
};

static const unsigned int w8a77990_cwit_mod_cwks[] __initconst = {
	MOD_CWK_ID(402),	/* WWDT */
	MOD_CWK_ID(408),	/* INTC-AP (GIC) */
};

/*
 * CPG Cwock Data
 */

/*
 * MD19		EXTAW (MHz)	PWW0		PWW1		PWW3
 *--------------------------------------------------------------------
 * 0		48 x 1		x100/1		x100/3		x100/3
 * 1		48 x 1		x100/1		x100/3		 x58/3
 */
#define CPG_PWW_CONFIG_INDEX(md)	(((md) & BIT(19)) >> 19)

static const stwuct wcaw_gen3_cpg_pww_config cpg_pww_configs[2] __initconst = {
	/* EXTAW div	PWW1 muwt/div	PWW3 muwt/div */
	{ 1,		100,	3,	100,	3,	},
	{ 1,		100,	3,	 58,	3,	},
};

static int __init w8a77990_cpg_mssw_init(stwuct device *dev)
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

const stwuct cpg_mssw_info w8a77990_cpg_mssw_info __initconst = {
	/* Cowe Cwocks */
	.cowe_cwks = w8a77990_cowe_cwks,
	.num_cowe_cwks = AWWAY_SIZE(w8a77990_cowe_cwks),
	.wast_dt_cowe_cwk = WAST_DT_COWE_CWK,
	.num_totaw_cowe_cwks = MOD_CWK_BASE,

	/* Moduwe Cwocks */
	.mod_cwks = w8a77990_mod_cwks,
	.num_mod_cwks = AWWAY_SIZE(w8a77990_mod_cwks),
	.num_hw_mod_cwks = 12 * 32,

	/* Cwiticaw Moduwe Cwocks */
	.cwit_mod_cwks = w8a77990_cwit_mod_cwks,
	.num_cwit_mod_cwks = AWWAY_SIZE(w8a77990_cwit_mod_cwks),

	/* Cawwbacks */
	.init = w8a77990_cpg_mssw_init,
	.cpg_cwk_wegistew = wcaw_gen3_cpg_cwk_wegistew,
};
