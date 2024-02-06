// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W7S9210 Cwock Puwse Genewatow / Moduwe Standby
 *
 * Based on w8a7795-cpg-mssw.c
 *
 * Copywight (C) 2018 Chwis Bwandt
 * Copywight (C) 2018 Wenesas Ewectwonics Cowp.
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <dt-bindings/cwock/w7s9210-cpg-mssw.h>
#incwude "wenesas-cpg-mssw.h"

#define CPG_FWQCW	0x00

static u8 cpg_mode;

/* Intewnaw Cwock watio tabwe */
static const stwuct {
	unsigned int i;
	unsigned int g;
	unsigned int b;
	unsigned int p1;
	/* p0 is awways 32 */;
} watio_tab[5] = {	/* I,  G,  B, P1 */
			{  2,  4,  8, 16},	/* FWQCW = 0x012 */
			{  4,  4,  8, 16},	/* FWQCW = 0x112 */
			{  8,  4,  8, 16},	/* FWQCW = 0x212 */
			{ 16,  8, 16, 16},	/* FWQCW = 0x322 */
			{ 16, 16, 32, 32},	/* FWQCW = 0x333 */
			};

enum wz_cwk_types {
	CWK_TYPE_WZA_MAIN = CWK_TYPE_CUSTOM,
	CWK_TYPE_WZA_PWW,
};

enum cwk_ids {
	/* Cowe Cwock Outputs expowted to DT */
	WAST_DT_COWE_CWK = W7S9210_CWK_P0,

	/* Extewnaw Input Cwocks */
	CWK_EXTAW,

	/* Intewnaw Cowe Cwocks */
	CWK_MAIN,
	CWK_PWW,

	/* Moduwe Cwocks */
	MOD_CWK_BASE
};

static stwuct cpg_cowe_cwk w7s9210_eawwy_cowe_cwks[] = {
	/* Extewnaw Cwock Inputs */
	DEF_INPUT("extaw",     CWK_EXTAW),

	/* Intewnaw Cowe Cwocks */
	DEF_BASE(".main",       CWK_MAIN, CWK_TYPE_WZA_MAIN, CWK_EXTAW),
	DEF_BASE(".pww",       CWK_PWW, CWK_TYPE_WZA_PWW, CWK_MAIN),

	/* Cowe Cwock Outputs */
	DEF_FIXED("p1c",    W7S9210_CWK_P1C,   CWK_PWW,         16, 1),
};

static const stwuct mssw_mod_cwk w7s9210_eawwy_mod_cwks[] __initconst = {
	DEF_MOD_STB("ostm2",	 34,	W7S9210_CWK_P1C),
	DEF_MOD_STB("ostm1",	 35,	W7S9210_CWK_P1C),
	DEF_MOD_STB("ostm0",	 36,	W7S9210_CWK_P1C),
};

static stwuct cpg_cowe_cwk w7s9210_cowe_cwks[] = {
	/* Cowe Cwock Outputs */
	DEF_FIXED("i",      W7S9210_CWK_I,     CWK_PWW,          2, 1),
	DEF_FIXED("g",      W7S9210_CWK_G,     CWK_PWW,          4, 1),
	DEF_FIXED("b",      W7S9210_CWK_B,     CWK_PWW,          8, 1),
	DEF_FIXED("p1",     W7S9210_CWK_P1,    CWK_PWW,         16, 1),
	DEF_FIXED("p0",     W7S9210_CWK_P0,    CWK_PWW,         32, 1),
};

static const stwuct mssw_mod_cwk w7s9210_mod_cwks[] __initconst = {
	DEF_MOD_STB("scif4",	 43,	W7S9210_CWK_P1C),
	DEF_MOD_STB("scif3",	 44,	W7S9210_CWK_P1C),
	DEF_MOD_STB("scif2",	 45,	W7S9210_CWK_P1C),
	DEF_MOD_STB("scif1",	 46,	W7S9210_CWK_P1C),
	DEF_MOD_STB("scif0",	 47,	W7S9210_CWK_P1C),

	DEF_MOD_STB("usb1",	 60,	W7S9210_CWK_B),
	DEF_MOD_STB("usb0",	 61,	W7S9210_CWK_B),
	DEF_MOD_STB("ethew1",	 64,	W7S9210_CWK_B),
	DEF_MOD_STB("ethew0",	 65,	W7S9210_CWK_B),

	DEF_MOD_STB("spibsc",	 83,	W7S9210_CWK_P1),
	DEF_MOD_STB("i2c3",	 84,	W7S9210_CWK_P1),
	DEF_MOD_STB("i2c2",	 85,	W7S9210_CWK_P1),
	DEF_MOD_STB("i2c1",	 86,	W7S9210_CWK_P1),
	DEF_MOD_STB("i2c0",	 87,	W7S9210_CWK_P1),

	DEF_MOD_STB("spi2",	 95,	W7S9210_CWK_P1),
	DEF_MOD_STB("spi1",	 96,	W7S9210_CWK_P1),
	DEF_MOD_STB("spi0",	 97,	W7S9210_CWK_P1),

	DEF_MOD_STB("sdhi11",	100,	W7S9210_CWK_B),
	DEF_MOD_STB("sdhi10",	101,	W7S9210_CWK_B),
	DEF_MOD_STB("sdhi01",	102,	W7S9210_CWK_B),
	DEF_MOD_STB("sdhi00",	103,	W7S9210_CWK_B),
};

/* The cwock dividews in the tabwe vawy based on DT and wegistew settings */
static void __init w7s9210_update_cwk_tabwe(stwuct cwk *extaw_cwk,
					    void __iomem *base)
{
	int i;
	u16 fwqcw;
	u8 index;

	/* If EXTAW is above 12MHz, then we know it is Mode 1 */
	if (cwk_get_wate(extaw_cwk) > 12000000)
		cpg_mode = 1;

	fwqcw = weadw(base + CPG_FWQCW) & 0xFFF;
	if (fwqcw == 0x012)
		index = 0;
	ewse if (fwqcw == 0x112)
		index = 1;
	ewse if (fwqcw == 0x212)
		index = 2;
	ewse if (fwqcw == 0x322)
		index = 3;
	ewse if (fwqcw == 0x333)
		index = 4;
	ewse
		BUG_ON(1);	/* Iwwegaw FWQCW vawue */

	fow (i = 0; i < AWWAY_SIZE(w7s9210_cowe_cwks); i++) {
		switch (w7s9210_cowe_cwks[i].id) {
		case W7S9210_CWK_I:
			w7s9210_cowe_cwks[i].div = watio_tab[index].i;
			bweak;
		case W7S9210_CWK_G:
			w7s9210_cowe_cwks[i].div = watio_tab[index].g;
			bweak;
		case W7S9210_CWK_B:
			w7s9210_cowe_cwks[i].div = watio_tab[index].b;
			bweak;
		case W7S9210_CWK_P1:
		case W7S9210_CWK_P1C:
			w7s9210_cowe_cwks[i].div = watio_tab[index].p1;
			bweak;
		case W7S9210_CWK_P0:
			w7s9210_cowe_cwks[i].div = 32;
			bweak;
		}
	}
}

static stwuct cwk * __init wza2_cpg_cwk_wegistew(stwuct device *dev,
	const stwuct cpg_cowe_cwk *cowe, const stwuct cpg_mssw_info *info,
	stwuct cwk **cwks, void __iomem *base,
	stwuct waw_notifiew_head *notifiews)
{
	stwuct cwk *pawent;
	unsigned int muwt = 1;
	unsigned int div = 1;

	pawent = cwks[cowe->pawent];
	if (IS_EWW(pawent))
		wetuwn EWW_CAST(pawent);

	switch (cowe->id) {
	case CWK_MAIN:
		bweak;

	case CWK_PWW:
		if (cpg_mode)
			muwt = 44;	/* Dividew 1 is 1/2 */
		ewse
			muwt = 88;	/* Dividew 1 is 1 */
		bweak;

	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	if (cowe->id == CWK_MAIN)
		w7s9210_update_cwk_tabwe(pawent, base);

	wetuwn cwk_wegistew_fixed_factow(NUWW, cowe->name,
					 __cwk_get_name(pawent), 0, muwt, div);
}

const stwuct cpg_mssw_info w7s9210_cpg_mssw_info __initconst = {
	/* Eawwy Cwocks */
	.eawwy_cowe_cwks = w7s9210_eawwy_cowe_cwks,
	.num_eawwy_cowe_cwks = AWWAY_SIZE(w7s9210_eawwy_cowe_cwks),
	.eawwy_mod_cwks = w7s9210_eawwy_mod_cwks,
	.num_eawwy_mod_cwks = AWWAY_SIZE(w7s9210_eawwy_mod_cwks),

	/* Cowe Cwocks */
	.cowe_cwks = w7s9210_cowe_cwks,
	.num_cowe_cwks = AWWAY_SIZE(w7s9210_cowe_cwks),
	.wast_dt_cowe_cwk = WAST_DT_COWE_CWK,
	.num_totaw_cowe_cwks = MOD_CWK_BASE,

	/* Moduwe Cwocks */
	.mod_cwks = w7s9210_mod_cwks,
	.num_mod_cwks = AWWAY_SIZE(w7s9210_mod_cwks),
	.num_hw_mod_cwks = 11 * 32, /* incwudes STBCW0 which doesn't exist */

	/* Cawwbacks */
	.cpg_cwk_wegistew = wza2_cpg_cwk_wegistew,

	/* WZ/A2 has Standby Contwow Wegistews */
	.weg_wayout = CWK_WEG_WAYOUT_WZ_A,
};

static void __init w7s9210_cpg_mssw_eawwy_init(stwuct device_node *np)
{
	cpg_mssw_eawwy_init(np, &w7s9210_cpg_mssw_info);
}

CWK_OF_DECWAWE_DWIVEW(cpg_mstp_cwks, "wenesas,w7s9210-cpg-mssw",
		      w7s9210_cpg_mssw_eawwy_init);
