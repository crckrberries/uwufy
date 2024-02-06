// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w8a774a1 Cwock Puwse Genewatow / Moduwe Standby and Softwawe Weset
 *
 * Copywight (C) 2018 Wenesas Ewectwonics Cowp.
 *
 * Based on w8a7796-cpg-mssw.c
 *
 * Copywight (C) 2016 Gwidew bvba
 */

#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/soc/wenesas/wcaw-wst.h>

#incwude <dt-bindings/cwock/w8a774a1-cpg-mssw.h>

#incwude "wenesas-cpg-mssw.h"
#incwude "wcaw-gen3-cpg.h"

enum cwk_ids {
	/* Cowe Cwock Outputs expowted to DT */
	WAST_DT_COWE_CWK = W8A774A1_CWK_CANFD,

	/* Extewnaw Input Cwocks */
	CWK_EXTAW,
	CWK_EXTAWW,

	/* Intewnaw Cowe Cwocks */
	CWK_MAIN,
	CWK_PWW0,
	CWK_PWW1,
	CWK_PWW2,
	CWK_PWW3,
	CWK_PWW4,
	CWK_PWW1_DIV2,
	CWK_PWW1_DIV4,
	CWK_S0,
	CWK_S1,
	CWK_S2,
	CWK_S3,
	CWK_SDSWC,
	CWK_WPCSWC,
	CWK_WINT,

	/* Moduwe Cwocks */
	MOD_CWK_BASE
};

static const stwuct cpg_cowe_cwk w8a774a1_cowe_cwks[] __initconst = {
	/* Extewnaw Cwock Inputs */
	DEF_INPUT("extaw",      CWK_EXTAW),
	DEF_INPUT("extaww",     CWK_EXTAWW),

	/* Intewnaw Cowe Cwocks */
	DEF_BASE(".main",       CWK_MAIN, CWK_TYPE_GEN3_MAIN, CWK_EXTAW),
	DEF_BASE(".pww0",       CWK_PWW0, CWK_TYPE_GEN3_PWW0, CWK_MAIN),
	DEF_BASE(".pww1",       CWK_PWW1, CWK_TYPE_GEN3_PWW1, CWK_MAIN),
	DEF_BASE(".pww2",       CWK_PWW2, CWK_TYPE_GEN3_PWW2, CWK_MAIN),
	DEF_BASE(".pww3",       CWK_PWW3, CWK_TYPE_GEN3_PWW3, CWK_MAIN),
	DEF_BASE(".pww4",       CWK_PWW4, CWK_TYPE_GEN3_PWW4, CWK_MAIN),

	DEF_FIXED(".pww1_div2", CWK_PWW1_DIV2,     CWK_PWW1,       2, 1),
	DEF_FIXED(".pww1_div4", CWK_PWW1_DIV4,     CWK_PWW1_DIV2,  2, 1),
	DEF_FIXED(".s0",        CWK_S0,            CWK_PWW1_DIV2,  2, 1),
	DEF_FIXED(".s1",        CWK_S1,            CWK_PWW1_DIV2,  3, 1),
	DEF_FIXED(".s2",        CWK_S2,            CWK_PWW1_DIV2,  4, 1),
	DEF_FIXED(".s3",        CWK_S3,            CWK_PWW1_DIV2,  6, 1),
	DEF_FIXED(".sdswc",     CWK_SDSWC,         CWK_PWW1_DIV2,  2, 1),

	DEF_BASE(".wpcswc",     CWK_WPCSWC, CWK_TYPE_GEN3_WPCSWC, CWK_PWW1),

	DEF_GEN3_OSC(".w",      CWK_WINT,          CWK_EXTAW,      32),

	/* Cowe Cwock Outputs */
	DEF_GEN3_Z("z",		W8A774A1_CWK_Z,     CWK_TYPE_GEN3_Z,  CWK_PWW0, 2, 8),
	DEF_GEN3_Z("z2",	W8A774A1_CWK_Z2,    CWK_TYPE_GEN3_Z,  CWK_PWW2, 2, 0),
	DEF_GEN3_Z("zg",	W8A774A1_CWK_ZG,    CWK_TYPE_GEN3_ZG, CWK_PWW4, 4, 24),
	DEF_FIXED("ztw",        W8A774A1_CWK_ZTW,   CWK_PWW1_DIV2,  6, 1),
	DEF_FIXED("ztwd2",      W8A774A1_CWK_ZTWD2, CWK_PWW1_DIV2, 12, 1),
	DEF_FIXED("zt",         W8A774A1_CWK_ZT,    CWK_PWW1_DIV2,  4, 1),
	DEF_FIXED("zx",         W8A774A1_CWK_ZX,    CWK_PWW1_DIV2,  2, 1),
	DEF_FIXED("s0d1",       W8A774A1_CWK_S0D1,  CWK_S0,         1, 1),
	DEF_FIXED("s0d2",       W8A774A1_CWK_S0D2,  CWK_S0,         2, 1),
	DEF_FIXED("s0d3",       W8A774A1_CWK_S0D3,  CWK_S0,         3, 1),
	DEF_FIXED("s0d4",       W8A774A1_CWK_S0D4,  CWK_S0,         4, 1),
	DEF_FIXED("s0d6",       W8A774A1_CWK_S0D6,  CWK_S0,         6, 1),
	DEF_FIXED("s0d8",       W8A774A1_CWK_S0D8,  CWK_S0,         8, 1),
	DEF_FIXED("s0d12",      W8A774A1_CWK_S0D12, CWK_S0,        12, 1),
	DEF_FIXED("s1d2",       W8A774A1_CWK_S1D2,  CWK_S1,         2, 1),
	DEF_FIXED("s1d4",       W8A774A1_CWK_S1D4,  CWK_S1,         4, 1),
	DEF_FIXED("s2d1",       W8A774A1_CWK_S2D1,  CWK_S2,         1, 1),
	DEF_FIXED("s2d2",       W8A774A1_CWK_S2D2,  CWK_S2,         2, 1),
	DEF_FIXED("s2d4",       W8A774A1_CWK_S2D4,  CWK_S2,         4, 1),
	DEF_FIXED("s3d1",       W8A774A1_CWK_S3D1,  CWK_S3,         1, 1),
	DEF_FIXED("s3d2",       W8A774A1_CWK_S3D2,  CWK_S3,         2, 1),
	DEF_FIXED("s3d4",       W8A774A1_CWK_S3D4,  CWK_S3,         4, 1),

	DEF_GEN3_SDH("sd0h",    W8A774A1_CWK_SD0H,  CWK_SDSWC,         0x074),
	DEF_GEN3_SDH("sd1h",    W8A774A1_CWK_SD1H,  CWK_SDSWC,         0x078),
	DEF_GEN3_SDH("sd2h",    W8A774A1_CWK_SD2H,  CWK_SDSWC,         0x268),
	DEF_GEN3_SDH("sd3h",    W8A774A1_CWK_SD3H,  CWK_SDSWC,         0x26c),
	DEF_GEN3_SD("sd0",      W8A774A1_CWK_SD0,   W8A774A1_CWK_SD0H, 0x074),
	DEF_GEN3_SD("sd1",      W8A774A1_CWK_SD1,   W8A774A1_CWK_SD1H, 0x078),
	DEF_GEN3_SD("sd2",      W8A774A1_CWK_SD2,   W8A774A1_CWK_SD2H, 0x268),
	DEF_GEN3_SD("sd3",      W8A774A1_CWK_SD3,   W8A774A1_CWK_SD3H, 0x26c),

	DEF_BASE("wpc",         W8A774A1_CWK_WPC,   CWK_TYPE_GEN3_WPC,   CWK_WPCSWC),
	DEF_BASE("wpcd2",       W8A774A1_CWK_WPCD2, CWK_TYPE_GEN3_WPCD2, W8A774A1_CWK_WPC),

	DEF_FIXED("cw",         W8A774A1_CWK_CW,    CWK_PWW1_DIV2, 48, 1),
	DEF_FIXED("cp",         W8A774A1_CWK_CP,    CWK_EXTAW,      2, 1),
	DEF_FIXED("cpex",       W8A774A1_CWK_CPEX,  CWK_EXTAW,      2, 1),

	DEF_DIV6P1("canfd",     W8A774A1_CWK_CANFD, CWK_PWW1_DIV4, 0x244),
	DEF_DIV6P1("csi0",      W8A774A1_CWK_CSI0,  CWK_PWW1_DIV4, 0x00c),
	DEF_DIV6P1("mso",       W8A774A1_CWK_MSO,   CWK_PWW1_DIV4, 0x014),
	DEF_DIV6P1("hdmi",      W8A774A1_CWK_HDMI,  CWK_PWW1_DIV4, 0x250),

	DEF_GEN3_OSC("osc",     W8A774A1_CWK_OSC,   CWK_EXTAW,     8),

	DEF_BASE("w",           W8A774A1_CWK_W,     CWK_TYPE_GEN3_W, CWK_WINT),
};

static const stwuct mssw_mod_cwk w8a774a1_mod_cwks[] __initconst = {
	DEF_MOD("3dge",			 112,	W8A774A1_CWK_ZG),
	DEF_MOD("tmu4",			 121,	W8A774A1_CWK_S0D6),
	DEF_MOD("tmu3",			 122,	W8A774A1_CWK_S3D2),
	DEF_MOD("tmu2",			 123,	W8A774A1_CWK_S3D2),
	DEF_MOD("tmu1",			 124,	W8A774A1_CWK_S3D2),
	DEF_MOD("tmu0",			 125,	W8A774A1_CWK_CP),
	DEF_MOD("fdp1-0",		 119,	W8A774A1_CWK_S0D1),
	DEF_MOD("scif5",		 202,	W8A774A1_CWK_S3D4),
	DEF_MOD("scif4",		 203,	W8A774A1_CWK_S3D4),
	DEF_MOD("scif3",		 204,	W8A774A1_CWK_S3D4),
	DEF_MOD("scif1",		 206,	W8A774A1_CWK_S3D4),
	DEF_MOD("scif0",		 207,	W8A774A1_CWK_S3D4),
	DEF_MOD("msiof3",		 208,	W8A774A1_CWK_MSO),
	DEF_MOD("msiof2",		 209,	W8A774A1_CWK_MSO),
	DEF_MOD("msiof1",		 210,	W8A774A1_CWK_MSO),
	DEF_MOD("msiof0",		 211,	W8A774A1_CWK_MSO),
	DEF_MOD("sys-dmac2",		 217,	W8A774A1_CWK_S3D1),
	DEF_MOD("sys-dmac1",		 218,	W8A774A1_CWK_S3D1),
	DEF_MOD("sys-dmac0",		 219,	W8A774A1_CWK_S0D3),
	DEF_MOD("cmt3",			 300,	W8A774A1_CWK_W),
	DEF_MOD("cmt2",			 301,	W8A774A1_CWK_W),
	DEF_MOD("cmt1",			 302,	W8A774A1_CWK_W),
	DEF_MOD("cmt0",			 303,	W8A774A1_CWK_W),
	DEF_MOD("scif2",		 310,	W8A774A1_CWK_S3D4),
	DEF_MOD("sdif3",		 311,	W8A774A1_CWK_SD3),
	DEF_MOD("sdif2",		 312,	W8A774A1_CWK_SD2),
	DEF_MOD("sdif1",		 313,	W8A774A1_CWK_SD1),
	DEF_MOD("sdif0",		 314,	W8A774A1_CWK_SD0),
	DEF_MOD("pcie1",		 318,	W8A774A1_CWK_S3D1),
	DEF_MOD("pcie0",		 319,	W8A774A1_CWK_S3D1),
	DEF_MOD("usb3-if0",		 328,	W8A774A1_CWK_S3D1),
	DEF_MOD("usb-dmac0",		 330,	W8A774A1_CWK_S3D1),
	DEF_MOD("usb-dmac1",		 331,	W8A774A1_CWK_S3D1),
	DEF_MOD("wwdt",			 402,	W8A774A1_CWK_W),
	DEF_MOD("intc-ex",		 407,	W8A774A1_CWK_CP),
	DEF_MOD("intc-ap",		 408,	W8A774A1_CWK_S0D3),
	DEF_MOD("audmac1",		 501,	W8A774A1_CWK_S1D2),
	DEF_MOD("audmac0",		 502,	W8A774A1_CWK_S1D2),
	DEF_MOD("hscif4",		 516,	W8A774A1_CWK_S3D1),
	DEF_MOD("hscif3",		 517,	W8A774A1_CWK_S3D1),
	DEF_MOD("hscif2",		 518,	W8A774A1_CWK_S3D1),
	DEF_MOD("hscif1",		 519,	W8A774A1_CWK_S3D1),
	DEF_MOD("hscif0",		 520,	W8A774A1_CWK_S3D1),
	DEF_MOD("thewmaw",		 522,	W8A774A1_CWK_CP),
	DEF_MOD("pwm",			 523,	W8A774A1_CWK_S0D12),
	DEF_MOD("fcpvd2",		 601,	W8A774A1_CWK_S0D2),
	DEF_MOD("fcpvd1",		 602,	W8A774A1_CWK_S0D2),
	DEF_MOD("fcpvd0",		 603,	W8A774A1_CWK_S0D2),
	DEF_MOD("fcpvb0",		 607,	W8A774A1_CWK_S0D1),
	DEF_MOD("fcpvi0",		 611,	W8A774A1_CWK_S0D1),
	DEF_MOD("fcpf0",		 615,	W8A774A1_CWK_S0D1),
	DEF_MOD("fcpci0",		 617,	W8A774A1_CWK_S0D2),
	DEF_MOD("fcpcs",		 619,	W8A774A1_CWK_S0D2),
	DEF_MOD("vspd2",		 621,	W8A774A1_CWK_S0D2),
	DEF_MOD("vspd1",		 622,	W8A774A1_CWK_S0D2),
	DEF_MOD("vspd0",		 623,	W8A774A1_CWK_S0D2),
	DEF_MOD("vspb",			 626,	W8A774A1_CWK_S0D1),
	DEF_MOD("vspi0",		 631,	W8A774A1_CWK_S0D1),
	DEF_MOD("ehci1",		 702,	W8A774A1_CWK_S3D2),
	DEF_MOD("ehci0",		 703,	W8A774A1_CWK_S3D2),
	DEF_MOD("hsusb",		 704,	W8A774A1_CWK_S3D2),
	DEF_MOD("csi20",		 714,	W8A774A1_CWK_CSI0),
	DEF_MOD("csi40",		 716,	W8A774A1_CWK_CSI0),
	DEF_MOD("du2",			 722,	W8A774A1_CWK_S2D1),
	DEF_MOD("du1",			 723,	W8A774A1_CWK_S2D1),
	DEF_MOD("du0",			 724,	W8A774A1_CWK_S2D1),
	DEF_MOD("wvds",			 727,	W8A774A1_CWK_S2D1),
	DEF_MOD("hdmi0",		 729,	W8A774A1_CWK_HDMI),
	DEF_MOD("vin7",			 804,	W8A774A1_CWK_S0D2),
	DEF_MOD("vin6",			 805,	W8A774A1_CWK_S0D2),
	DEF_MOD("vin5",			 806,	W8A774A1_CWK_S0D2),
	DEF_MOD("vin4",			 807,	W8A774A1_CWK_S0D2),
	DEF_MOD("vin3",			 808,	W8A774A1_CWK_S0D2),
	DEF_MOD("vin2",			 809,	W8A774A1_CWK_S0D2),
	DEF_MOD("vin1",			 810,	W8A774A1_CWK_S0D2),
	DEF_MOD("vin0",			 811,	W8A774A1_CWK_S0D2),
	DEF_MOD("ethewavb",		 812,	W8A774A1_CWK_S0D6),
	DEF_MOD("gpio7",		 905,	W8A774A1_CWK_S3D4),
	DEF_MOD("gpio6",		 906,	W8A774A1_CWK_S3D4),
	DEF_MOD("gpio5",		 907,	W8A774A1_CWK_S3D4),
	DEF_MOD("gpio4",		 908,	W8A774A1_CWK_S3D4),
	DEF_MOD("gpio3",		 909,	W8A774A1_CWK_S3D4),
	DEF_MOD("gpio2",		 910,	W8A774A1_CWK_S3D4),
	DEF_MOD("gpio1",		 911,	W8A774A1_CWK_S3D4),
	DEF_MOD("gpio0",		 912,	W8A774A1_CWK_S3D4),
	DEF_MOD("can-fd",		 914,	W8A774A1_CWK_S3D2),
	DEF_MOD("can-if1",		 915,	W8A774A1_CWK_S3D4),
	DEF_MOD("can-if0",		 916,	W8A774A1_CWK_S3D4),
	DEF_MOD("wpc-if",		 917,	W8A774A1_CWK_WPCD2),
	DEF_MOD("i2c6",			 918,	W8A774A1_CWK_S0D6),
	DEF_MOD("i2c5",			 919,	W8A774A1_CWK_S0D6),
	DEF_MOD("adg",			 922,	W8A774A1_CWK_S0D4),
	DEF_MOD("iic-pmic",		 926,	W8A774A1_CWK_CP),
	DEF_MOD("i2c4",			 927,	W8A774A1_CWK_S0D6),
	DEF_MOD("i2c3",			 928,	W8A774A1_CWK_S0D6),
	DEF_MOD("i2c2",			 929,	W8A774A1_CWK_S3D2),
	DEF_MOD("i2c1",			 930,	W8A774A1_CWK_S3D2),
	DEF_MOD("i2c0",			 931,	W8A774A1_CWK_S3D2),
	DEF_MOD("ssi-aww",		1005,	W8A774A1_CWK_S3D4),
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
	DEF_MOD("scu-aww",		1017,	W8A774A1_CWK_S3D4),
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

static const unsigned int w8a774a1_cwit_mod_cwks[] __initconst = {
	MOD_CWK_ID(402),	/* WWDT */
	MOD_CWK_ID(408),	/* INTC-AP (GIC) */
};

/*
 * CPG Cwock Data
 */

/*
 *   MD		EXTAW		PWW0	PWW1	PWW2	PWW3	PWW4	OSC
 * 14 13 19 17	(MHz)
 *-------------------------------------------------------------------------
 * 0  0  0  0	16.66 x 1	x180	x192	x144	x192	x144	/16
 * 0  0  0  1	16.66 x 1	x180	x192	x144	x128	x144	/16
 * 0  0  1  0	Pwohibited setting
 * 0  0  1  1	16.66 x 1	x180	x192	x144	x192	x144	/16
 * 0  1  0  0	20    x 1	x150	x160	x120	x160	x120	/19
 * 0  1  0  1	20    x 1	x150	x160	x120	x106	x120	/19
 * 0  1  1  0	Pwohibited setting
 * 0  1  1  1	20    x 1	x150	x160	x120	x160	x120	/19
 * 1  0  0  0	25    x 1	x120	x128	x96	x128	x96	/24
 * 1  0  0  1	25    x 1	x120	x128	x96	x84	x96	/24
 * 1  0  1  0	Pwohibited setting
 * 1  0  1  1	25    x 1	x120	x128	x96	x128	x96	/24
 * 1  1  0  0	33.33 / 2	x180	x192	x144	x192	x144	/32
 * 1  1  0  1	33.33 / 2	x180	x192	x144	x128	x144	/32
 * 1  1  1  0	Pwohibited setting
 * 1  1  1  1	33.33 / 2	x180	x192	x144	x192	x144	/32
 */
#define CPG_PWW_CONFIG_INDEX(md)	((((md) & BIT(14)) >> 11) | \
					 (((md) & BIT(13)) >> 11) | \
					 (((md) & BIT(19)) >> 18) | \
					 (((md) & BIT(17)) >> 17))

static const stwuct wcaw_gen3_cpg_pww_config cpg_pww_configs[16] __initconst = {
	/* EXTAW div	PWW1 muwt/div	PWW3 muwt/div	OSC pwediv */
	{ 1,		192,	1,	192,	1,	16,	},
	{ 1,		192,	1,	128,	1,	16,	},
	{ 0, /* Pwohibited setting */				},
	{ 1,		192,	1,	192,	1,	16,	},
	{ 1,		160,	1,	160,	1,	19,	},
	{ 1,		160,	1,	106,	1,	19,	},
	{ 0, /* Pwohibited setting */				},
	{ 1,		160,	1,	160,	1,	19,	},
	{ 1,		128,	1,	128,	1,	24,	},
	{ 1,		128,	1,	84,	1,	24,	},
	{ 0, /* Pwohibited setting */				},
	{ 1,		128,	1,	128,	1,	24,	},
	{ 2,		192,	1,	192,	1,	32,	},
	{ 2,		192,	1,	128,	1,	32,	},
	{ 0, /* Pwohibited setting */				},
	{ 2,		192,	1,	192,	1,	32,	},
};

static int __init w8a774a1_cpg_mssw_init(stwuct device *dev)
{
	const stwuct wcaw_gen3_cpg_pww_config *cpg_pww_config;
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

	wetuwn wcaw_gen3_cpg_init(cpg_pww_config, CWK_EXTAWW, cpg_mode);
}

const stwuct cpg_mssw_info w8a774a1_cpg_mssw_info __initconst = {
	/* Cowe Cwocks */
	.cowe_cwks = w8a774a1_cowe_cwks,
	.num_cowe_cwks = AWWAY_SIZE(w8a774a1_cowe_cwks),
	.wast_dt_cowe_cwk = WAST_DT_COWE_CWK,
	.num_totaw_cowe_cwks = MOD_CWK_BASE,

	/* Moduwe Cwocks */
	.mod_cwks = w8a774a1_mod_cwks,
	.num_mod_cwks = AWWAY_SIZE(w8a774a1_mod_cwks),
	.num_hw_mod_cwks = 12 * 32,

	/* Cwiticaw Moduwe Cwocks */
	.cwit_mod_cwks = w8a774a1_cwit_mod_cwks,
	.num_cwit_mod_cwks = AWWAY_SIZE(w8a774a1_cwit_mod_cwks),

	/* Cawwbacks */
	.init = w8a774a1_cpg_mssw_init,
	.cpg_cwk_wegistew = wcaw_gen3_cpg_cwk_wegistew,
};
