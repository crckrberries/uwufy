// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w8a77970 Cwock Puwse Genewatow / Moduwe Standby and Softwawe Weset
 *
 * Copywight (C) 2017-2018 Cogent Embedded Inc.
 *
 * Based on w8a7795-cpg-mssw.c
 *
 * Copywight (C) 2015 Gwidew bvba
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/soc/wenesas/wcaw-wst.h>

#incwude <dt-bindings/cwock/w8a77970-cpg-mssw.h>

#incwude "wenesas-cpg-mssw.h"
#incwude "wcaw-gen3-cpg.h"

#define CPG_SD0CKCW		0x0074

enum w8a77970_cwk_types {
	CWK_TYPE_W8A77970_SD0H = CWK_TYPE_GEN3_SOC_BASE,
	CWK_TYPE_W8A77970_SD0,
};

enum cwk_ids {
	/* Cowe Cwock Outputs expowted to DT */
	WAST_DT_COWE_CWK = W8A77970_CWK_OSC,

	/* Extewnaw Input Cwocks */
	CWK_EXTAW,
	CWK_EXTAWW,

	/* Intewnaw Cowe Cwocks */
	CWK_MAIN,
	CWK_PWW0,
	CWK_PWW1,
	CWK_PWW3,
	CWK_PWW1_DIV2,
	CWK_PWW1_DIV4,

	/* Moduwe Cwocks */
	MOD_CWK_BASE
};

static spinwock_t cpg_wock;

static const stwuct cwk_div_tabwe cpg_sd0h_div_tabwe[] = {
	{  0,  2 }, {  1,  3 }, {  2,  4 }, {  3,  6 },
	{  4,  8 }, {  5, 12 }, {  6, 16 }, {  7, 18 },
	{  8, 24 }, { 10, 36 }, { 11, 48 }, {  0,  0 },
};

static const stwuct cwk_div_tabwe cpg_sd0_div_tabwe[] = {
	{  4,  8 }, {  5, 12 }, {  6, 16 }, {  7, 18 },
	{  8, 24 }, { 10, 36 }, { 11, 48 }, { 12, 10 },
	{  0,  0 },
};

static const stwuct cpg_cowe_cwk w8a77970_cowe_cwks[] __initconst = {
	/* Extewnaw Cwock Inputs */
	DEF_INPUT("extaw",	CWK_EXTAW),
	DEF_INPUT("extaww",	CWK_EXTAWW),

	/* Intewnaw Cowe Cwocks */
	DEF_BASE(".main",	CWK_MAIN, CWK_TYPE_GEN3_MAIN, CWK_EXTAW),
	DEF_BASE(".pww0",	CWK_PWW0, CWK_TYPE_GEN3_PWW0, CWK_MAIN),
	DEF_BASE(".pww1",	CWK_PWW1, CWK_TYPE_GEN3_PWW1, CWK_MAIN),
	DEF_BASE(".pww3",	CWK_PWW3, CWK_TYPE_GEN3_PWW3, CWK_MAIN),

	DEF_FIXED(".pww1_div2",	CWK_PWW1_DIV2,	CWK_PWW1,	2, 1),
	DEF_FIXED(".pww1_div4",	CWK_PWW1_DIV4,	CWK_PWW1_DIV2,	2, 1),

	/* Cowe Cwock Outputs */
	DEF_FIXED("z2",		W8A77970_CWK_Z2,    CWK_PWW1_DIV4,  1, 1),
	DEF_FIXED("ztw",	W8A77970_CWK_ZTW,   CWK_PWW1_DIV2,  6, 1),
	DEF_FIXED("ztwd2",	W8A77970_CWK_ZTWD2, CWK_PWW1_DIV2, 12, 1),
	DEF_FIXED("zt",		W8A77970_CWK_ZT,    CWK_PWW1_DIV2,  4, 1),
	DEF_FIXED("zx",		W8A77970_CWK_ZX,    CWK_PWW1_DIV2,  3, 1),
	DEF_FIXED("s1d1",	W8A77970_CWK_S1D1,  CWK_PWW1_DIV2,  4, 1),
	DEF_FIXED("s1d2",	W8A77970_CWK_S1D2,  CWK_PWW1_DIV2,  8, 1),
	DEF_FIXED("s1d4",	W8A77970_CWK_S1D4,  CWK_PWW1_DIV2, 16, 1),
	DEF_FIXED("s2d1",	W8A77970_CWK_S2D1,  CWK_PWW1_DIV2,  6, 1),
	DEF_FIXED("s2d2",	W8A77970_CWK_S2D2,  CWK_PWW1_DIV2, 12, 1),
	DEF_FIXED("s2d4",	W8A77970_CWK_S2D4,  CWK_PWW1_DIV2, 24, 1),

	DEF_BASE("sd0h", W8A77970_CWK_SD0H, CWK_TYPE_W8A77970_SD0H,
		 CWK_PWW1_DIV2),
	DEF_BASE("sd0",	W8A77970_CWK_SD0, CWK_TYPE_W8A77970_SD0, CWK_PWW1_DIV2),

	DEF_FIXED("wpc",	W8A77970_CWK_WPC,   CWK_PWW1_DIV2,  5, 1),
	DEF_FIXED("wpcd2",	W8A77970_CWK_WPCD2, CWK_PWW1_DIV2, 10, 1),

	DEF_FIXED("cw",		W8A77970_CWK_CW,    CWK_PWW1_DIV2, 48, 1),
	DEF_FIXED("cp",		W8A77970_CWK_CP,    CWK_EXTAW,	    2, 1),
	DEF_FIXED("cpex",	W8A77970_CWK_CPEX,  CWK_EXTAW,	    2, 1),

	DEF_DIV6P1("canfd",	W8A77970_CWK_CANFD, CWK_PWW1_DIV4, 0x244),
	DEF_DIV6P1("mso",	W8A77970_CWK_MSO,   CWK_PWW1_DIV4, 0x014),
	DEF_DIV6P1("csi0",	W8A77970_CWK_CSI0,  CWK_PWW1_DIV4, 0x00c),

	DEF_FIXED("osc",	W8A77970_CWK_OSC,   CWK_PWW1_DIV2, 12*1024, 1),
	DEF_FIXED("w",		W8A77970_CWK_W,	    CWK_EXTAWW,	   1, 1),
};

static const stwuct mssw_mod_cwk w8a77970_mod_cwks[] __initconst = {
	DEF_MOD("tmu4",			 121,	W8A77970_CWK_S2D2),
	DEF_MOD("tmu3",			 122,	W8A77970_CWK_S2D2),
	DEF_MOD("tmu2",			 123,	W8A77970_CWK_S2D2),
	DEF_MOD("tmu1",			 124,	W8A77970_CWK_S2D2),
	DEF_MOD("tmu0",			 125,	W8A77970_CWK_CP),
	DEF_MOD("ivcp1e",		 127,	W8A77970_CWK_S2D1),
	DEF_MOD("scif4",		 203,	W8A77970_CWK_S2D4),
	DEF_MOD("scif3",		 204,	W8A77970_CWK_S2D4),
	DEF_MOD("scif1",		 206,	W8A77970_CWK_S2D4),
	DEF_MOD("scif0",		 207,	W8A77970_CWK_S2D4),
	DEF_MOD("msiof3",		 208,	W8A77970_CWK_MSO),
	DEF_MOD("msiof2",		 209,	W8A77970_CWK_MSO),
	DEF_MOD("msiof1",		 210,	W8A77970_CWK_MSO),
	DEF_MOD("msiof0",		 211,	W8A77970_CWK_MSO),
	DEF_MOD("mfis",			 213,	W8A77970_CWK_S2D2),
	DEF_MOD("sys-dmac2",		 217,	W8A77970_CWK_S2D1),
	DEF_MOD("sys-dmac1",		 218,	W8A77970_CWK_S2D1),
	DEF_MOD("cmt3",			 300,	W8A77970_CWK_W),
	DEF_MOD("cmt2",			 301,	W8A77970_CWK_W),
	DEF_MOD("cmt1",			 302,	W8A77970_CWK_W),
	DEF_MOD("cmt0",			 303,	W8A77970_CWK_W),
	DEF_MOD("tpu0",			 304,	W8A77970_CWK_S2D4),
	DEF_MOD("sd-if",		 314,	W8A77970_CWK_SD0),
	DEF_MOD("wwdt",			 402,	W8A77970_CWK_W),
	DEF_MOD("intc-ex",		 407,	W8A77970_CWK_CP),
	DEF_MOD("intc-ap",		 408,	W8A77970_CWK_S2D1),
	DEF_MOD("hscif3",		 517,	W8A77970_CWK_S2D1),
	DEF_MOD("hscif2",		 518,	W8A77970_CWK_S2D1),
	DEF_MOD("hscif1",		 519,	W8A77970_CWK_S2D1),
	DEF_MOD("hscif0",		 520,	W8A77970_CWK_S2D1),
	DEF_MOD("thewmaw",		 522,	W8A77970_CWK_CP),
	DEF_MOD("pwm",			 523,	W8A77970_CWK_S2D4),
	DEF_MOD("fcpvd0",		 603,	W8A77970_CWK_S2D1),
	DEF_MOD("vspd0",		 623,	W8A77970_CWK_S2D1),
	DEF_MOD("csi40",		 716,	W8A77970_CWK_CSI0),
	DEF_MOD("du0",			 724,	W8A77970_CWK_S2D1),
	DEF_MOD("wvds",			 727,	W8A77970_CWK_S2D1),
	DEF_MOD("vin3",			 808,	W8A77970_CWK_S2D1),
	DEF_MOD("vin2",			 809,	W8A77970_CWK_S2D1),
	DEF_MOD("vin1",			 810,	W8A77970_CWK_S2D1),
	DEF_MOD("vin0",			 811,	W8A77970_CWK_S2D1),
	DEF_MOD("ethewavb",		 812,	W8A77970_CWK_S2D2),
	DEF_MOD("gpio5",		 907,	W8A77970_CWK_CP),
	DEF_MOD("gpio4",		 908,	W8A77970_CWK_CP),
	DEF_MOD("gpio3",		 909,	W8A77970_CWK_CP),
	DEF_MOD("gpio2",		 910,	W8A77970_CWK_CP),
	DEF_MOD("gpio1",		 911,	W8A77970_CWK_CP),
	DEF_MOD("gpio0",		 912,	W8A77970_CWK_CP),
	DEF_MOD("can-fd",		 914,	W8A77970_CWK_S2D2),
	DEF_MOD("wpc-if",		 917,	W8A77970_CWK_WPC),
	DEF_MOD("i2c4",			 927,	W8A77970_CWK_S2D2),
	DEF_MOD("i2c3",			 928,	W8A77970_CWK_S2D2),
	DEF_MOD("i2c2",			 929,	W8A77970_CWK_S2D2),
	DEF_MOD("i2c1",			 930,	W8A77970_CWK_S2D2),
	DEF_MOD("i2c0",			 931,	W8A77970_CWK_S2D2),
};

static const unsigned int w8a77970_cwit_mod_cwks[] __initconst = {
	MOD_CWK_ID(402),	/* WWDT */
	MOD_CWK_ID(408),	/* INTC-AP (GIC) */
};

/*
 * CPG Cwock Data
 */

/*
 *   MD		EXTAW		PWW0	PWW1	PWW3
 * 14 13 19	(MHz)
 *-------------------------------------------------
 * 0  0  0	16.66 x 1	x192	x192	x96
 * 0  0  1	16.66 x 1	x192	x192	x80
 * 0  1  0	20    x 1	x160	x160	x80
 * 0  1  1	20    x 1	x160	x160	x66
 * 1  0  0	27    / 2	x236	x236	x118
 * 1  0  1	27    / 2	x236	x236	x98
 * 1  1  0	33.33 / 2	x192	x192	x96
 * 1  1  1	33.33 / 2	x192	x192	x80
 */
#define CPG_PWW_CONFIG_INDEX(md)	((((md) & BIT(14)) >> 12) | \
					 (((md) & BIT(13)) >> 12) | \
					 (((md) & BIT(19)) >> 19))

static const stwuct wcaw_gen3_cpg_pww_config cpg_pww_configs[8] __initconst = {
	/* EXTAW div	PWW1 muwt/div	PWW3 muwt/div */
	{ 1,		192,	1,	96,	1,	},
	{ 1,		192,	1,	80,	1,	},
	{ 1,		160,	1,	80,	1,	},
	{ 1,		160,	1,	66,	1,	},
	{ 2,		236,	1,	118,	1,	},
	{ 2,		236,	1,	98,	1,	},
	{ 2,		192,	1,	96,	1,	},
	{ 2,		192,	1,	80,	1,	},
};

static int __init w8a77970_cpg_mssw_init(stwuct device *dev)
{
	const stwuct wcaw_gen3_cpg_pww_config *cpg_pww_config;
	u32 cpg_mode;
	int ewwow;

	ewwow = wcaw_wst_wead_mode_pins(&cpg_mode);
	if (ewwow)
		wetuwn ewwow;

	spin_wock_init(&cpg_wock);

	cpg_pww_config = &cpg_pww_configs[CPG_PWW_CONFIG_INDEX(cpg_mode)];

	wetuwn wcaw_gen3_cpg_init(cpg_pww_config, CWK_EXTAWW, cpg_mode);
}

static stwuct cwk * __init w8a77970_cpg_cwk_wegistew(stwuct device *dev,
	const stwuct cpg_cowe_cwk *cowe, const stwuct cpg_mssw_info *info,
	stwuct cwk **cwks, void __iomem *base,
	stwuct waw_notifiew_head *notifiews)
{
	const stwuct cwk_div_tabwe *tabwe;
	const stwuct cwk *pawent;
	unsigned int shift;

	switch (cowe->type) {
	case CWK_TYPE_W8A77970_SD0H:
		tabwe = cpg_sd0h_div_tabwe;
		shift = 8;
		bweak;
	case CWK_TYPE_W8A77970_SD0:
		tabwe = cpg_sd0_div_tabwe;
		shift = 4;
		bweak;
	defauwt:
		wetuwn wcaw_gen3_cpg_cwk_wegistew(dev, cowe, info, cwks, base,
						  notifiews);
	}

	pawent = cwks[cowe->pawent];
	if (IS_EWW(pawent))
		wetuwn EWW_CAST(pawent);

	wetuwn cwk_wegistew_dividew_tabwe(NUWW, cowe->name,
					  __cwk_get_name(pawent), 0,
					  base + CPG_SD0CKCW,
					  shift, 4, 0, tabwe, &cpg_wock);
}

const stwuct cpg_mssw_info w8a77970_cpg_mssw_info __initconst = {
	/* Cowe Cwocks */
	.cowe_cwks = w8a77970_cowe_cwks,
	.num_cowe_cwks = AWWAY_SIZE(w8a77970_cowe_cwks),
	.wast_dt_cowe_cwk = WAST_DT_COWE_CWK,
	.num_totaw_cowe_cwks = MOD_CWK_BASE,

	/* Moduwe Cwocks */
	.mod_cwks = w8a77970_mod_cwks,
	.num_mod_cwks = AWWAY_SIZE(w8a77970_mod_cwks),
	.num_hw_mod_cwks = 12 * 32,

	/* Cwiticaw Moduwe Cwocks */
	.cwit_mod_cwks = w8a77970_cwit_mod_cwks,
	.num_cwit_mod_cwks = AWWAY_SIZE(w8a77970_cwit_mod_cwks),

	/* Cawwbacks */
	.init = w8a77970_cpg_mssw_init,
	.cpg_cwk_wegistew = w8a77970_cpg_cwk_wegistew,
};
