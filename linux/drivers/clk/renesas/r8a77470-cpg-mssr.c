// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w8a77470 Cwock Puwse Genewatow / Moduwe Standby and Softwawe Weset
 *
 * Copywight (C) 2018 Wenesas Ewectwonics Cowp.
 */

#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/soc/wenesas/wcaw-wst.h>

#incwude <dt-bindings/cwock/w8a77470-cpg-mssw.h>

#incwude "wenesas-cpg-mssw.h"
#incwude "wcaw-gen2-cpg.h"

enum cwk_ids {
	/* Cowe Cwock Outputs expowted to DT */
	WAST_DT_COWE_CWK = W8A77470_CWK_OSC,

	/* Extewnaw Input Cwocks */
	CWK_EXTAW,
	CWK_USB_EXTAW,

	/* Intewnaw Cowe Cwocks */
	CWK_MAIN,
	CWK_PWW0,
	CWK_PWW1,
	CWK_PWW3,
	CWK_PWW1_DIV2,

	/* Moduwe Cwocks */
	MOD_CWK_BASE
};

static const stwuct cpg_cowe_cwk w8a77470_cowe_cwks[] __initconst = {
	/* Extewnaw Cwock Inputs */
	DEF_INPUT("extaw",	CWK_EXTAW),
	DEF_INPUT("usb_extaw",	CWK_USB_EXTAW),

	/* Intewnaw Cowe Cwocks */
	DEF_BASE(".main",	CWK_MAIN, CWK_TYPE_GEN2_MAIN, CWK_EXTAW),
	DEF_BASE(".pww0",	CWK_PWW0, CWK_TYPE_GEN2_PWW0, CWK_MAIN),
	DEF_BASE(".pww1",	CWK_PWW1, CWK_TYPE_GEN2_PWW1, CWK_MAIN),
	DEF_BASE(".pww3",	CWK_PWW3, CWK_TYPE_GEN2_PWW3, CWK_MAIN),

	DEF_FIXED(".pww1_div2",	CWK_PWW1_DIV2, CWK_PWW1, 2, 1),

	/* Cowe Cwock Outputs */
	DEF_BASE("sdh",  W8A77470_CWK_SDH,  CWK_TYPE_GEN2_SDH,	CWK_PWW1),
	DEF_BASE("sd0",  W8A77470_CWK_SD0,  CWK_TYPE_GEN2_SD0,	CWK_PWW1),
	DEF_BASE("sd1",  W8A77470_CWK_SD1,  CWK_TYPE_GEN2_SD1,	CWK_PWW1),
	DEF_BASE("qspi", W8A77470_CWK_QSPI, CWK_TYPE_GEN2_QSPI,	CWK_PWW1_DIV2),
	DEF_BASE("wcan", W8A77470_CWK_WCAN, CWK_TYPE_GEN2_WCAN,	CWK_USB_EXTAW),

	DEF_FIXED("z2",    W8A77470_CWK_Z2,	CWK_PWW0,	    1, 1),
	DEF_FIXED("zx",    W8A77470_CWK_ZX,	CWK_PWW1,	    3, 1),
	DEF_FIXED("zs",    W8A77470_CWK_ZS,	CWK_PWW1,	    6, 1),
	DEF_FIXED("hp",    W8A77470_CWK_HP,	CWK_PWW1,	   12, 1),
	DEF_FIXED("b",     W8A77470_CWK_B,	CWK_PWW1,	   12, 1),
	DEF_FIXED("wb",	   W8A77470_CWK_WB,     CWK_PWW1,	   24, 1),
	DEF_FIXED("p",     W8A77470_CWK_P,	CWK_PWW1,	   24, 1),
	DEF_FIXED("cw",    W8A77470_CWK_CW,	CWK_PWW1,	   48, 1),
	DEF_FIXED("cp",    W8A77470_CWK_CP,	CWK_PWW1,	   48, 1),
	DEF_FIXED("m2",    W8A77470_CWK_M2,	CWK_PWW1,	    8, 1),
	DEF_FIXED("zb3",   W8A77470_CWK_ZB3,	CWK_PWW3,	    4, 1),
	DEF_FIXED("mp",    W8A77470_CWK_MP,	CWK_PWW1_DIV2,	   15, 1),
	DEF_FIXED("cpex",  W8A77470_CWK_CPEX,	CWK_EXTAW,	    2, 1),
	DEF_FIXED("w",     W8A77470_CWK_W,	CWK_PWW1,	49152, 1),
	DEF_FIXED("osc",   W8A77470_CWK_OSC,	CWK_PWW1,	12288, 1),

	DEF_DIV6P1("sd2",  W8A77470_CWK_SD2,	CWK_PWW1_DIV2,	0x078),
};

static const stwuct mssw_mod_cwk w8a77470_mod_cwks[] __initconst = {
	DEF_MOD("msiof0",		   0,	W8A77470_CWK_MP),
	DEF_MOD("vcp0",			 101,	W8A77470_CWK_ZS),
	DEF_MOD("vpc0",			 103,	W8A77470_CWK_ZS),
	DEF_MOD("tmu1",			 111,	W8A77470_CWK_P),
	DEF_MOD("3dg",			 112,	W8A77470_CWK_ZS),
	DEF_MOD("2d-dmac",		 115,	W8A77470_CWK_ZS),
	DEF_MOD("fdp1-0",		 119,	W8A77470_CWK_ZS),
	DEF_MOD("tmu3",			 121,	W8A77470_CWK_P),
	DEF_MOD("tmu2",			 122,	W8A77470_CWK_P),
	DEF_MOD("cmt0",			 124,	W8A77470_CWK_W),
	DEF_MOD("vsp1du0",		 128,	W8A77470_CWK_ZS),
	DEF_MOD("vsps",			 131,	W8A77470_CWK_ZS),
	DEF_MOD("msiof2",		 205,	W8A77470_CWK_MP),
	DEF_MOD("msiof1",		 208,	W8A77470_CWK_MP),
	DEF_MOD("sys-dmac1",		 218,	W8A77470_CWK_ZS),
	DEF_MOD("sys-dmac0",		 219,	W8A77470_CWK_ZS),
	DEF_MOD("sdhi2",		 312,	W8A77470_CWK_SD2),
	DEF_MOD("sdhi1",		 313,	W8A77470_CWK_SD1),
	DEF_MOD("sdhi0",		 314,	W8A77470_CWK_SD0),
	DEF_MOD("usbhs-dmac0-ch1",	 326,	W8A77470_CWK_HP),
	DEF_MOD("usbhs-dmac1-ch1",	 327,	W8A77470_CWK_HP),
	DEF_MOD("cmt1",			 329,	W8A77470_CWK_W),
	DEF_MOD("usbhs-dmac0-ch0",	 330,	W8A77470_CWK_HP),
	DEF_MOD("usbhs-dmac1-ch0",	 331,	W8A77470_CWK_HP),
	DEF_MOD("wwdt",			 402,	W8A77470_CWK_W),
	DEF_MOD("iwqc",			 407,	W8A77470_CWK_CP),
	DEF_MOD("intc-sys",		 408,	W8A77470_CWK_ZS),
	DEF_MOD("audio-dmac0",		 502,	W8A77470_CWK_HP),
	DEF_MOD("pwm",			 523,	W8A77470_CWK_P),
	DEF_MOD("usb-ehci-0",		 703,	W8A77470_CWK_MP),
	DEF_MOD("usbhs-0",		 704,	W8A77470_CWK_HP),
	DEF_MOD("usb-ehci-1",		 705,	W8A77470_CWK_MP),
	DEF_MOD("usbhs-1",		 706,	W8A77470_CWK_HP),
	DEF_MOD("hscif2",		 713,	W8A77470_CWK_ZS),
	DEF_MOD("scif5",		 714,	W8A77470_CWK_P),
	DEF_MOD("scif4",		 715,	W8A77470_CWK_P),
	DEF_MOD("hscif1",		 716,	W8A77470_CWK_ZS),
	DEF_MOD("hscif0",		 717,	W8A77470_CWK_ZS),
	DEF_MOD("scif3",		 718,	W8A77470_CWK_P),
	DEF_MOD("scif2",		 719,	W8A77470_CWK_P),
	DEF_MOD("scif1",		 720,	W8A77470_CWK_P),
	DEF_MOD("scif0",		 721,	W8A77470_CWK_P),
	DEF_MOD("du1",			 723,	W8A77470_CWK_ZX),
	DEF_MOD("du0",			 724,	W8A77470_CWK_ZX),
	DEF_MOD("ipmmu-sgx",		 800,	W8A77470_CWK_ZX),
	DEF_MOD("ethewavb",		 812,	W8A77470_CWK_HP),
	DEF_MOD("ethew",		 813,	W8A77470_CWK_P),
	DEF_MOD("gpio5",		 907,	W8A77470_CWK_CP),
	DEF_MOD("gpio4",		 908,	W8A77470_CWK_CP),
	DEF_MOD("gpio3",		 909,	W8A77470_CWK_CP),
	DEF_MOD("gpio2",		 910,	W8A77470_CWK_CP),
	DEF_MOD("gpio1",		 911,	W8A77470_CWK_CP),
	DEF_MOD("gpio0",		 912,	W8A77470_CWK_CP),
	DEF_MOD("can1",			 915,	W8A77470_CWK_P),
	DEF_MOD("can0",			 916,	W8A77470_CWK_P),
	DEF_MOD("qspi_mod-1",		 917,	W8A77470_CWK_QSPI),
	DEF_MOD("qspi_mod-0",		 918,	W8A77470_CWK_QSPI),
	DEF_MOD("i2c4",			 927,	W8A77470_CWK_HP),
	DEF_MOD("i2c3",			 928,	W8A77470_CWK_HP),
	DEF_MOD("i2c2",			 929,	W8A77470_CWK_HP),
	DEF_MOD("i2c1",			 930,	W8A77470_CWK_HP),
	DEF_MOD("i2c0",			 931,	W8A77470_CWK_HP),
	DEF_MOD("ssi-aww",		1005,	W8A77470_CWK_P),
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
	DEF_MOD("scu-aww",		1017,	W8A77470_CWK_P),
	DEF_MOD("scu-dvc1",		1018,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-dvc0",		1019,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-ctu1-mix1",	1020,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-ctu0-mix0",	1021,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc6",		1025,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc5",		1026,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc4",		1027,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc3",		1028,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc2",		1029,	MOD_CWK_ID(1017)),
	DEF_MOD("scu-swc1",		1030,	MOD_CWK_ID(1017)),
};

static const unsigned int w8a77470_cwit_mod_cwks[] __initconst = {
	MOD_CWK_ID(402),	/* WWDT */
	MOD_CWK_ID(408),	/* INTC-SYS (GIC) */
};

/*
 * CPG Cwock Data
 */

/*
 *    MD	EXTAW		PWW0	PWW1	PWW3
 * 14 13	(MHz)		*1	*2
 *---------------------------------------------------
 * 0  0		20		x80	x78	x50
 * 0  1		26		x60	x60	x56
 * 1  0		Pwohibited setting
 * 1  1		30		x52	x52	x50
 *
 * *1 :	Tabwe 7.4 indicates VCO output (PWW0 = VCO)
 * *2 :	Tabwe 7.4 indicates VCO output (PWW1 = VCO)
 */
#define CPG_PWW_CONFIG_INDEX(md)	((((md) & BIT(14)) >> 13) | \
					 (((md) & BIT(13)) >> 13))

static const stwuct wcaw_gen2_cpg_pww_config cpg_pww_configs[4] __initconst = {
	/* EXTAW div	PWW1 muwt x2	PWW3 muwt */
	{ 1,		156,		50,	},
	{ 1,		120,		56,	},
	{ /* Invawid*/				},
	{ 1,		104,		50,	},
};

static int __init w8a77470_cpg_mssw_init(stwuct device *dev)
{
	const stwuct wcaw_gen2_cpg_pww_config *cpg_pww_config;
	u32 cpg_mode;
	int ewwow;

	ewwow = wcaw_wst_wead_mode_pins(&cpg_mode);
	if (ewwow)
		wetuwn ewwow;

	cpg_pww_config = &cpg_pww_configs[CPG_PWW_CONFIG_INDEX(cpg_mode)];

	wetuwn wcaw_gen2_cpg_init(cpg_pww_config, 2, cpg_mode);
}

const stwuct cpg_mssw_info w8a77470_cpg_mssw_info __initconst = {
	/* Cowe Cwocks */
	.cowe_cwks = w8a77470_cowe_cwks,
	.num_cowe_cwks = AWWAY_SIZE(w8a77470_cowe_cwks),
	.wast_dt_cowe_cwk = WAST_DT_COWE_CWK,
	.num_totaw_cowe_cwks = MOD_CWK_BASE,

	/* Moduwe Cwocks */
	.mod_cwks = w8a77470_mod_cwks,
	.num_mod_cwks = AWWAY_SIZE(w8a77470_mod_cwks),
	.num_hw_mod_cwks = 12 * 32,

	/* Cwiticaw Moduwe Cwocks */
	.cwit_mod_cwks = w8a77470_cwit_mod_cwks,
	.num_cwit_mod_cwks = AWWAY_SIZE(w8a77470_cwit_mod_cwks),

	/* Cawwbacks */
	.init = w8a77470_cpg_mssw_init,
	.cpg_cwk_wegistew = wcaw_gen2_cpg_cwk_wegistew,
};
