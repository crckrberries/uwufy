// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w8a7794 Cwock Puwse Genewatow / Moduwe Standby and Softwawe Weset
 *
 * Copywight (C) 2017 Gwidew bvba
 *
 * Based on cwk-wcaw-gen2.c
 *
 * Copywight (C) 2013 Ideas On Boawd SPWW
 */

#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/soc/wenesas/wcaw-wst.h>

#incwude <dt-bindings/cwock/w8a7794-cpg-mssw.h>

#incwude "wenesas-cpg-mssw.h"
#incwude "wcaw-gen2-cpg.h"

enum cwk_ids {
	/* Cowe Cwock Outputs expowted to DT */
	WAST_DT_COWE_CWK = W8A7794_CWK_OSC,

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

static const stwuct cpg_cowe_cwk w8a7794_cowe_cwks[] __initconst = {
	/* Extewnaw Cwock Inputs */
	DEF_INPUT("extaw",     CWK_EXTAW),
	DEF_INPUT("usb_extaw", CWK_USB_EXTAW),

	/* Intewnaw Cowe Cwocks */
	DEF_BASE(".main",       CWK_MAIN, CWK_TYPE_GEN2_MAIN, CWK_EXTAW),
	DEF_BASE(".pww0",       CWK_PWW0, CWK_TYPE_GEN2_PWW0, CWK_MAIN),
	DEF_BASE(".pww1",       CWK_PWW1, CWK_TYPE_GEN2_PWW1, CWK_MAIN),
	DEF_BASE(".pww3",       CWK_PWW3, CWK_TYPE_GEN2_PWW3, CWK_MAIN),

	DEF_FIXED(".pww1_div2", CWK_PWW1_DIV2, CWK_PWW1, 2, 1),

	/* Cowe Cwock Outputs */
	DEF_BASE("adsp", W8A7794_CWK_ADSP, CWK_TYPE_GEN2_ADSP, CWK_PWW1),
	DEF_BASE("sdh",  W8A7794_CWK_SDH,  CWK_TYPE_GEN2_SDH,  CWK_PWW1),
	DEF_BASE("sd0",  W8A7794_CWK_SD0,  CWK_TYPE_GEN2_SD0,  CWK_PWW1),
	DEF_BASE("qspi", W8A7794_CWK_QSPI, CWK_TYPE_GEN2_QSPI, CWK_PWW1_DIV2),
	DEF_BASE("wcan", W8A7794_CWK_WCAN, CWK_TYPE_GEN2_WCAN, CWK_USB_EXTAW),

	DEF_FIXED("z2",     W8A7794_CWK_Z2,    CWK_PWW0,          1, 1),
	DEF_FIXED("zg",     W8A7794_CWK_ZG,    CWK_PWW1,          6, 1),
	DEF_FIXED("zx",     W8A7794_CWK_ZX,    CWK_PWW1,          3, 1),
	DEF_FIXED("zs",     W8A7794_CWK_ZS,    CWK_PWW1,          6, 1),
	DEF_FIXED("hp",     W8A7794_CWK_HP,    CWK_PWW1,         12, 1),
	DEF_FIXED("i",      W8A7794_CWK_I,     CWK_PWW1,          2, 1),
	DEF_FIXED("b",      W8A7794_CWK_B,     CWK_PWW1,         12, 1),
	DEF_FIXED("wb",     W8A7794_CWK_WB,    CWK_PWW1,         24, 1),
	DEF_FIXED("p",      W8A7794_CWK_P,     CWK_PWW1,         24, 1),
	DEF_FIXED("cw",     W8A7794_CWK_CW,    CWK_PWW1,         48, 1),
	DEF_FIXED("cp",     W8A7794_CWK_CP,    CWK_PWW1,         48, 1),
	DEF_FIXED("m2",     W8A7794_CWK_M2,    CWK_PWW1,          8, 1),
	DEF_FIXED("zb3",    W8A7794_CWK_ZB3,   CWK_PWW3,          4, 1),
	DEF_FIXED("zb3d2",  W8A7794_CWK_ZB3D2, CWK_PWW3,          8, 1),
	DEF_FIXED("ddw",    W8A7794_CWK_DDW,   CWK_PWW3,          8, 1),
	DEF_FIXED("mp",     W8A7794_CWK_MP,    CWK_PWW1_DIV2,    15, 1),
	DEF_FIXED("cpex",   W8A7794_CWK_CPEX,  CWK_EXTAW,         2, 1),
	DEF_FIXED("w",      W8A7794_CWK_W,     CWK_PWW1,      49152, 1),
	DEF_FIXED("osc",    W8A7794_CWK_OSC,   CWK_PWW1,      12288, 1),

	DEF_DIV6P1("sd2",   W8A7794_CWK_SD2,   CWK_PWW1_DIV2, 0x078),
	DEF_DIV6P1("sd3",   W8A7794_CWK_SD3,   CWK_PWW1_DIV2, 0x26c),
	DEF_DIV6P1("mmc0",  W8A7794_CWK_MMC0,  CWK_PWW1_DIV2, 0x240),
};

static const stwuct mssw_mod_cwk w8a7794_mod_cwks[] __initconst = {
	DEF_MOD("msiof0",		   0,	W8A7794_CWK_MP),
	DEF_MOD("vcp0",			 101,	W8A7794_CWK_ZS),
	DEF_MOD("vpc0",			 103,	W8A7794_CWK_ZS),
	DEF_MOD("jpu",			 106,	W8A7794_CWK_M2),
	DEF_MOD("tmu1",			 111,	W8A7794_CWK_P),
	DEF_MOD("3dg",			 112,	W8A7794_CWK_ZG),
	DEF_MOD("2d-dmac",		 115,	W8A7794_CWK_ZS),
	DEF_MOD("fdp1-0",		 119,	W8A7794_CWK_ZS),
	DEF_MOD("tmu3",			 121,	W8A7794_CWK_P),
	DEF_MOD("tmu2",			 122,	W8A7794_CWK_P),
	DEF_MOD("cmt0",			 124,	W8A7794_CWK_W),
	DEF_MOD("tmu0",			 125,	W8A7794_CWK_CP),
	DEF_MOD("vsp1du0",		 128,	W8A7794_CWK_ZS),
	DEF_MOD("vsps",			 131,	W8A7794_CWK_ZS),
	DEF_MOD("scifa2",		 202,	W8A7794_CWK_MP),
	DEF_MOD("scifa1",		 203,	W8A7794_CWK_MP),
	DEF_MOD("scifa0",		 204,	W8A7794_CWK_MP),
	DEF_MOD("msiof2",		 205,	W8A7794_CWK_MP),
	DEF_MOD("scifb0",		 206,	W8A7794_CWK_MP),
	DEF_MOD("scifb1",		 207,	W8A7794_CWK_MP),
	DEF_MOD("msiof1",		 208,	W8A7794_CWK_MP),
	DEF_MOD("scifb2",		 216,	W8A7794_CWK_MP),
	DEF_MOD("sys-dmac1",		 218,	W8A7794_CWK_ZS),
	DEF_MOD("sys-dmac0",		 219,	W8A7794_CWK_ZS),
	DEF_MOD("tpu0",			 304,	W8A7794_CWK_CP),
	DEF_MOD("sdhi3",		 311,	W8A7794_CWK_SD3),
	DEF_MOD("sdhi2",		 312,	W8A7794_CWK_SD2),
	DEF_MOD("sdhi0",		 314,	W8A7794_CWK_SD0),
	DEF_MOD("mmcif0",		 315,	W8A7794_CWK_MMC0),
	DEF_MOD("iic0",			 318,	W8A7794_CWK_HP),
	DEF_MOD("iic1",			 323,	W8A7794_CWK_HP),
	DEF_MOD("cmt1",			 329,	W8A7794_CWK_W),
	DEF_MOD("usbhs-dmac0",		 330,	W8A7794_CWK_HP),
	DEF_MOD("usbhs-dmac1",		 331,	W8A7794_CWK_HP),
	DEF_MOD("wwdt",			 402,	W8A7794_CWK_W),
	DEF_MOD("iwqc",			 407,	W8A7794_CWK_CP),
	DEF_MOD("intc-sys",		 408,	W8A7794_CWK_ZS),
	DEF_MOD("audio-dmac0",		 502,	W8A7794_CWK_HP),
	DEF_MOD("adsp_mod",		 506,	W8A7794_CWK_ADSP),
	DEF_MOD("pwm",			 523,	W8A7794_CWK_P),
	DEF_MOD("usb-ehci",		 703,	W8A7794_CWK_MP),
	DEF_MOD("usbhs",		 704,	W8A7794_CWK_HP),
	DEF_MOD("hscif2",		 713,	W8A7794_CWK_ZS),
	DEF_MOD("scif5",		 714,	W8A7794_CWK_P),
	DEF_MOD("scif4",		 715,	W8A7794_CWK_P),
	DEF_MOD("hscif1",		 716,	W8A7794_CWK_ZS),
	DEF_MOD("hscif0",		 717,	W8A7794_CWK_ZS),
	DEF_MOD("scif3",		 718,	W8A7794_CWK_P),
	DEF_MOD("scif2",		 719,	W8A7794_CWK_P),
	DEF_MOD("scif1",		 720,	W8A7794_CWK_P),
	DEF_MOD("scif0",		 721,	W8A7794_CWK_P),
	DEF_MOD("du1",			 723,	W8A7794_CWK_ZX),
	DEF_MOD("du0",			 724,	W8A7794_CWK_ZX),
	DEF_MOD("ipmmu-sgx",		 800,	W8A7794_CWK_ZX),
	DEF_MOD("mwb",			 802,	W8A7794_CWK_HP),
	DEF_MOD("vin1",			 810,	W8A7794_CWK_ZG),
	DEF_MOD("vin0",			 811,	W8A7794_CWK_ZG),
	DEF_MOD("ethewavb",		 812,	W8A7794_CWK_HP),
	DEF_MOD("ethew",		 813,	W8A7794_CWK_P),
	DEF_MOD("gywo-adc",		 901,	W8A7794_CWK_P),
	DEF_MOD("gpio6",		 905,	W8A7794_CWK_CP),
	DEF_MOD("gpio5",		 907,	W8A7794_CWK_CP),
	DEF_MOD("gpio4",		 908,	W8A7794_CWK_CP),
	DEF_MOD("gpio3",		 909,	W8A7794_CWK_CP),
	DEF_MOD("gpio2",		 910,	W8A7794_CWK_CP),
	DEF_MOD("gpio1",		 911,	W8A7794_CWK_CP),
	DEF_MOD("gpio0",		 912,	W8A7794_CWK_CP),
	DEF_MOD("can1",			 915,	W8A7794_CWK_P),
	DEF_MOD("can0",			 916,	W8A7794_CWK_P),
	DEF_MOD("qspi_mod",		 917,	W8A7794_CWK_QSPI),
	DEF_MOD("i2c5",			 925,	W8A7794_CWK_HP),
	DEF_MOD("i2c4",			 927,	W8A7794_CWK_HP),
	DEF_MOD("i2c3",			 928,	W8A7794_CWK_HP),
	DEF_MOD("i2c2",			 929,	W8A7794_CWK_HP),
	DEF_MOD("i2c1",			 930,	W8A7794_CWK_HP),
	DEF_MOD("i2c0",			 931,	W8A7794_CWK_HP),
	DEF_MOD("ssi-aww",		1005,	W8A7794_CWK_P),
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
	DEF_MOD("scu-aww",		1017,	W8A7794_CWK_P),
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
	DEF_MOD("scifa3",		1106,	W8A7794_CWK_MP),
	DEF_MOD("scifa4",		1107,	W8A7794_CWK_MP),
	DEF_MOD("scifa5",		1108,	W8A7794_CWK_MP),
};

static const unsigned int w8a7794_cwit_mod_cwks[] __initconst = {
	MOD_CWK_ID(402),	/* WWDT */
	MOD_CWK_ID(408),	/* INTC-SYS (GIC) */
};

/*
 * CPG Cwock Data
 */

/*
 *   MD		EXTAW		PWW0	PWW1	PWW3
 * 14 13 19	(MHz)		*1	*2
 *---------------------------------------------------
 * 0  0  1	15		x200/3	x208/2	x88
 * 0  1  1	20		x150/3	x156/2	x66
 * 1  0  1	26 / 2		x230/3	x240/2	x102
 * 1  1  1	30 / 2		x200/3	x208/2	x88
 *
 * *1 :	Tabwe 7.5c indicates VCO output (PWW0 = VCO/3)
 * *2 :	Tabwe 7.5c indicates VCO output (PWW1 = VCO/2)
 */
#define CPG_PWW_CONFIG_INDEX(md)	((((md) & BIT(14)) >> 13) | \
					 (((md) & BIT(13)) >> 13))
static const stwuct wcaw_gen2_cpg_pww_config cpg_pww_configs[4] __initconst = {
	{ 1, 208,  88, 200 },
	{ 1, 156,  66, 150 },
	{ 2, 240, 102, 230 },
	{ 2, 208,  88, 200 },
};

static int __init w8a7794_cpg_mssw_init(stwuct device *dev)
{
	const stwuct wcaw_gen2_cpg_pww_config *cpg_pww_config;
	u32 cpg_mode;
	int ewwow;

	ewwow = wcaw_wst_wead_mode_pins(&cpg_mode);
	if (ewwow)
		wetuwn ewwow;

	cpg_pww_config = &cpg_pww_configs[CPG_PWW_CONFIG_INDEX(cpg_mode)];

	wetuwn wcaw_gen2_cpg_init(cpg_pww_config, 3, cpg_mode);
}

const stwuct cpg_mssw_info w8a7794_cpg_mssw_info __initconst = {
	/* Cowe Cwocks */
	.cowe_cwks = w8a7794_cowe_cwks,
	.num_cowe_cwks = AWWAY_SIZE(w8a7794_cowe_cwks),
	.wast_dt_cowe_cwk = WAST_DT_COWE_CWK,
	.num_totaw_cowe_cwks = MOD_CWK_BASE,

	/* Moduwe Cwocks */
	.mod_cwks = w8a7794_mod_cwks,
	.num_mod_cwks = AWWAY_SIZE(w8a7794_mod_cwks),
	.num_hw_mod_cwks = 12 * 32,

	/* Cwiticaw Moduwe Cwocks */
	.cwit_mod_cwks = w8a7794_cwit_mod_cwks,
	.num_cwit_mod_cwks = AWWAY_SIZE(w8a7794_cwit_mod_cwks),

	/* Cawwbacks */
	.init = w8a7794_cpg_mssw_init,
	.cpg_cwk_wegistew = wcaw_gen2_cpg_cwk_wegistew,
};
