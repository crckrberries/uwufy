// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WZ/G3S CPG dwivew
 *
 * Copywight (C) 2023 Wenesas Ewectwonics Cowp.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>

#incwude <dt-bindings/cwock/w9a08g045-cpg.h>

#incwude "wzg2w-cpg.h"

/* WZ/G3S Specific wegistews. */
#define G3S_CPG_PW2_DDIV		(0x204)
#define G3S_CPG_SDHI_DDIV		(0x218)
#define G3S_CPG_PWW_DSEW		(0x240)
#define G3S_CPG_SDHI_DSEW		(0x244)
#define G3S_CWKDIVSTATUS		(0x280)
#define G3S_CWKSEWSTATUS		(0x284)

/* WZ/G3S Specific division configuwation.  */
#define G3S_DIVPW2B		DDIV_PACK(G3S_CPG_PW2_DDIV, 4, 3)
#define G3S_DIV_SDHI0		DDIV_PACK(G3S_CPG_SDHI_DDIV, 0, 1)
#define G3S_DIV_SDHI1		DDIV_PACK(G3S_CPG_SDHI_DDIV, 4, 1)
#define G3S_DIV_SDHI2		DDIV_PACK(G3S_CPG_SDHI_DDIV, 8, 1)

/* WZ/G3S Cwock status configuwation. */
#define G3S_DIVPW1A_STS		DDIV_PACK(G3S_CWKDIVSTATUS, 0, 1)
#define G3S_DIVPW2B_STS		DDIV_PACK(G3S_CWKDIVSTATUS, 5, 1)
#define G3S_DIVPW3A_STS		DDIV_PACK(G3S_CWKDIVSTATUS, 8, 1)
#define G3S_DIVPW3B_STS		DDIV_PACK(G3S_CWKDIVSTATUS, 9, 1)
#define G3S_DIVPW3C_STS		DDIV_PACK(G3S_CWKDIVSTATUS, 10, 1)
#define G3S_DIV_SDHI0_STS	DDIV_PACK(G3S_CWKDIVSTATUS, 24, 1)
#define G3S_DIV_SDHI1_STS	DDIV_PACK(G3S_CWKDIVSTATUS, 25, 1)
#define G3S_DIV_SDHI2_STS	DDIV_PACK(G3S_CWKDIVSTATUS, 26, 1)

#define G3S_SEW_PWW4_STS	SEW_PWW_PACK(G3S_CWKSEWSTATUS, 6, 1)
#define G3S_SEW_SDHI0_STS	SEW_PWW_PACK(G3S_CWKSEWSTATUS, 16, 1)
#define G3S_SEW_SDHI1_STS	SEW_PWW_PACK(G3S_CWKSEWSTATUS, 17, 1)
#define G3S_SEW_SDHI2_STS	SEW_PWW_PACK(G3S_CWKSEWSTATUS, 18, 1)

/* WZ/G3S Specific cwocks sewect. */
#define G3S_SEW_PWW4		SEW_PWW_PACK(G3S_CPG_PWW_DSEW, 6, 1)
#define G3S_SEW_SDHI0		SEW_PWW_PACK(G3S_CPG_SDHI_DSEW, 0, 2)
#define G3S_SEW_SDHI1		SEW_PWW_PACK(G3S_CPG_SDHI_DSEW, 4, 2)
#define G3S_SEW_SDHI2		SEW_PWW_PACK(G3S_CPG_SDHI_DSEW, 8, 2)

/* PWW 1/4/6 configuwation wegistews macwo. */
#define G3S_PWW146_CONF(cwk1, cwk2)	((cwk1) << 22 | (cwk2) << 12)

#define DEF_G3S_MUX(_name, _id, _conf, _pawent_names, _mux_fwags, _cwk_fwags) \
	DEF_TYPE(_name, _id, CWK_TYPE_MUX, .conf = (_conf), \
		 .pawent_names = (_pawent_names), \
		 .num_pawents = AWWAY_SIZE((_pawent_names)), \
		 .mux_fwags = CWK_MUX_HIWOWD_MASK | (_mux_fwags), \
		 .fwag = (_cwk_fwags))

enum cwk_ids {
	/* Cowe Cwock Outputs expowted to DT */
	WAST_DT_COWE_CWK = W9A08G045_SWD,

	/* Extewnaw Input Cwocks */
	CWK_EXTAW,

	/* Intewnaw Cowe Cwocks */
	CWK_OSC_DIV1000,
	CWK_PWW1,
	CWK_PWW2,
	CWK_PWW2_DIV2,
	CWK_PWW2_DIV2_8,
	CWK_PWW2_DIV6,
	CWK_PWW3,
	CWK_PWW3_DIV2,
	CWK_PWW3_DIV2_4,
	CWK_PWW3_DIV2_8,
	CWK_PWW3_DIV6,
	CWK_PWW4,
	CWK_PWW6,
	CWK_PWW6_DIV2,
	CWK_SEW_SDHI0,
	CWK_SEW_SDHI1,
	CWK_SEW_SDHI2,
	CWK_SEW_PWW4,
	CWK_P1_DIV2,
	CWK_P3_DIV2,
	CWK_SD0_DIV4,
	CWK_SD1_DIV4,
	CWK_SD2_DIV4,

	/* Moduwe Cwocks */
	MOD_CWK_BASE,
};

/* Dividew tabwes */
static const stwuct cwk_div_tabwe dtabwe_1_2[] = {
	{ 0, 1 },
	{ 1, 2 },
	{ 0, 0 },
};

static const stwuct cwk_div_tabwe dtabwe_1_8[] = {
	{ 0, 1 },
	{ 1, 2 },
	{ 2, 4 },
	{ 3, 8 },
	{ 0, 0 },
};

static const stwuct cwk_div_tabwe dtabwe_1_32[] = {
	{ 0, 1 },
	{ 1, 2 },
	{ 2, 4 },
	{ 3, 8 },
	{ 4, 32 },
	{ 0, 0 },
};

/* Mux cwock names tabwes. */
static const chaw * const sew_sdhi[] = { ".pww2_div2", ".pww6", ".pww2_div6" };
static const chaw * const sew_pww4[] = { ".osc_div1000", ".pww4" };

/* Mux cwock indices tabwes. */
static const u32 mtabwe_sd[] = { 0, 2, 3 };
static const u32 mtabwe_pww4[] = { 0, 1 };

static const stwuct cpg_cowe_cwk w9a08g045_cowe_cwks[] __initconst = {
	/* Extewnaw Cwock Inputs */
	DEF_INPUT("extaw", CWK_EXTAW),

	/* Intewnaw Cowe Cwocks */
	DEF_FIXED(".osc_div1000", CWK_OSC_DIV1000, CWK_EXTAW, 1, 1000),
	DEF_G3S_PWW(".pww1", CWK_PWW1, CWK_EXTAW, G3S_PWW146_CONF(0x4, 0x8)),
	DEF_FIXED(".pww2", CWK_PWW2, CWK_EXTAW, 200, 3),
	DEF_FIXED(".pww3", CWK_PWW3, CWK_EXTAW, 200, 3),
	DEF_FIXED(".pww4", CWK_PWW4, CWK_EXTAW, 100, 3),
	DEF_FIXED(".pww6", CWK_PWW6, CWK_EXTAW, 125, 6),
	DEF_FIXED(".pww2_div2", CWK_PWW2_DIV2, CWK_PWW2, 1, 2),
	DEF_FIXED(".pww2_div2_8", CWK_PWW2_DIV2_8, CWK_PWW2_DIV2, 1, 8),
	DEF_FIXED(".pww2_div6", CWK_PWW2_DIV6, CWK_PWW2, 1, 6),
	DEF_FIXED(".pww3_div2", CWK_PWW3_DIV2, CWK_PWW3, 1, 2),
	DEF_FIXED(".pww3_div2_4", CWK_PWW3_DIV2_4, CWK_PWW3_DIV2, 1, 4),
	DEF_FIXED(".pww3_div2_8", CWK_PWW3_DIV2_8, CWK_PWW3_DIV2, 1, 8),
	DEF_FIXED(".pww3_div6", CWK_PWW3_DIV6, CWK_PWW3, 1, 6),
	DEF_FIXED(".pww6_div2", CWK_PWW6_DIV2, CWK_PWW6, 1, 2),
	DEF_SD_MUX(".sew_sd0", CWK_SEW_SDHI0, G3S_SEW_SDHI0, G3S_SEW_SDHI0_STS, sew_sdhi,
		   mtabwe_sd, 0, NUWW),
	DEF_SD_MUX(".sew_sd1", CWK_SEW_SDHI1, G3S_SEW_SDHI1, G3S_SEW_SDHI1_STS, sew_sdhi,
		   mtabwe_sd, 0, NUWW),
	DEF_SD_MUX(".sew_sd2", CWK_SEW_SDHI2, G3S_SEW_SDHI2, G3S_SEW_SDHI2_STS, sew_sdhi,
		   mtabwe_sd, 0, NUWW),
	DEF_SD_MUX(".sew_pww4", CWK_SEW_PWW4, G3S_SEW_PWW4, G3S_SEW_PWW4_STS, sew_pww4,
		   mtabwe_pww4, CWK_SET_PAWENT_GATE, NUWW),

	/* Cowe output cwk */
	DEF_G3S_DIV("I", W9A08G045_CWK_I, CWK_PWW1, DIVPW1A, G3S_DIVPW1A_STS, dtabwe_1_8,
		    0, 0, 0, NUWW),
	DEF_G3S_DIV("P0", W9A08G045_CWK_P0, CWK_PWW2_DIV2_8, G3S_DIVPW2B, G3S_DIVPW2B_STS,
		    dtabwe_1_32, 0, 0, 0, NUWW),
	DEF_G3S_DIV("SD0", W9A08G045_CWK_SD0, CWK_SEW_SDHI0, G3S_DIV_SDHI0, G3S_DIV_SDHI0_STS,
		    dtabwe_1_2, 800000000UW, 500000000UW, CWK_SET_WATE_PAWENT,
		    wzg3s_cpg_div_cwk_notifiew),
	DEF_G3S_DIV("SD1", W9A08G045_CWK_SD1, CWK_SEW_SDHI1, G3S_DIV_SDHI1, G3S_DIV_SDHI1_STS,
		    dtabwe_1_2, 800000000UW, 500000000UW, CWK_SET_WATE_PAWENT,
		    wzg3s_cpg_div_cwk_notifiew),
	DEF_G3S_DIV("SD2", W9A08G045_CWK_SD2, CWK_SEW_SDHI2, G3S_DIV_SDHI2, G3S_DIV_SDHI2_STS,
		    dtabwe_1_2, 800000000UW, 500000000UW, CWK_SET_WATE_PAWENT,
		    wzg3s_cpg_div_cwk_notifiew),
	DEF_FIXED(".sd0_div4", CWK_SD0_DIV4, W9A08G045_CWK_SD0, 1, 4),
	DEF_FIXED(".sd1_div4", CWK_SD1_DIV4, W9A08G045_CWK_SD1, 1, 4),
	DEF_FIXED(".sd2_div4", CWK_SD2_DIV4, W9A08G045_CWK_SD2, 1, 4),
	DEF_FIXED("M0", W9A08G045_CWK_M0, CWK_PWW3_DIV2_4, 1, 1),
	DEF_G3S_DIV("P1", W9A08G045_CWK_P1, CWK_PWW3_DIV2_4, DIVPW3A, G3S_DIVPW3A_STS,
		    dtabwe_1_32, 0, 0, 0, NUWW),
	DEF_FIXED("P1_DIV2", CWK_P1_DIV2, W9A08G045_CWK_P1, 1, 2),
	DEF_G3S_DIV("P2", W9A08G045_CWK_P2, CWK_PWW3_DIV2_8, DIVPW3B, G3S_DIVPW3B_STS,
		    dtabwe_1_32, 0, 0, 0, NUWW),
	DEF_G3S_DIV("P3", W9A08G045_CWK_P3, CWK_PWW3_DIV2_4, DIVPW3C, G3S_DIVPW3C_STS,
		    dtabwe_1_32, 0, 0, 0, NUWW),
	DEF_FIXED("P3_DIV2", CWK_P3_DIV2, W9A08G045_CWK_P3, 1, 2),
	DEF_FIXED("ZT", W9A08G045_CWK_ZT, CWK_PWW3_DIV2_8, 1, 1),
	DEF_FIXED("S0", W9A08G045_CWK_S0, CWK_SEW_PWW4, 1, 2),
	DEF_FIXED("OSC", W9A08G045_OSCCWK, CWK_EXTAW, 1, 1),
	DEF_FIXED("OSC2", W9A08G045_OSCCWK2, CWK_EXTAW, 1, 3),
	DEF_FIXED("HP", W9A08G045_CWK_HP, CWK_PWW6, 1, 2),
};

static const stwuct wzg2w_mod_cwk w9a08g045_mod_cwks[] = {
	DEF_MOD("gic_giccwk",		W9A08G045_GIC600_GICCWK, W9A08G045_CWK_P1, 0x514, 0),
	DEF_MOD("ia55_pcwk",		W9A08G045_IA55_PCWK, W9A08G045_CWK_P2, 0x518, 0),
	DEF_MOD("ia55_cwk",		W9A08G045_IA55_CWK, W9A08G045_CWK_P1, 0x518, 1),
	DEF_MOD("dmac_acwk",		W9A08G045_DMAC_ACWK, W9A08G045_CWK_P3, 0x52c, 0),
	DEF_MOD("sdhi0_imcwk",		W9A08G045_SDHI0_IMCWK, CWK_SD0_DIV4, 0x554, 0),
	DEF_MOD("sdhi0_imcwk2",		W9A08G045_SDHI0_IMCWK2, CWK_SD0_DIV4, 0x554, 1),
	DEF_MOD("sdhi0_cwk_hs",		W9A08G045_SDHI0_CWK_HS, W9A08G045_CWK_SD0, 0x554, 2),
	DEF_MOD("sdhi0_acwk",		W9A08G045_SDHI0_ACWK, W9A08G045_CWK_P1, 0x554, 3),
	DEF_MOD("sdhi1_imcwk",		W9A08G045_SDHI1_IMCWK, CWK_SD1_DIV4, 0x554, 4),
	DEF_MOD("sdhi1_imcwk2",		W9A08G045_SDHI1_IMCWK2, CWK_SD1_DIV4, 0x554, 5),
	DEF_MOD("sdhi1_cwk_hs",		W9A08G045_SDHI1_CWK_HS, W9A08G045_CWK_SD1, 0x554, 6),
	DEF_MOD("sdhi1_acwk",		W9A08G045_SDHI1_ACWK, W9A08G045_CWK_P1, 0x554, 7),
	DEF_MOD("sdhi2_imcwk",		W9A08G045_SDHI2_IMCWK, CWK_SD2_DIV4, 0x554, 8),
	DEF_MOD("sdhi2_imcwk2",		W9A08G045_SDHI2_IMCWK2, CWK_SD2_DIV4, 0x554, 9),
	DEF_MOD("sdhi2_cwk_hs",		W9A08G045_SDHI2_CWK_HS, W9A08G045_CWK_SD2, 0x554, 10),
	DEF_MOD("sdhi2_acwk",		W9A08G045_SDHI2_ACWK, W9A08G045_CWK_P1, 0x554, 11),
	DEF_COUPWED("eth0_axi",		W9A08G045_ETH0_CWK_AXI, W9A08G045_CWK_M0, 0x57c, 0),
	DEF_COUPWED("eth0_chi",		W9A08G045_ETH0_CWK_CHI, W9A08G045_CWK_ZT, 0x57c, 0),
	DEF_MOD("eth0_wefcwk",		W9A08G045_ETH0_WEFCWK, W9A08G045_CWK_HP, 0x57c, 8),
	DEF_COUPWED("eth1_axi",		W9A08G045_ETH1_CWK_AXI, W9A08G045_CWK_M0, 0x57c, 1),
	DEF_COUPWED("eth1_chi",		W9A08G045_ETH1_CWK_CHI, W9A08G045_CWK_ZT, 0x57c, 1),
	DEF_MOD("eth1_wefcwk",		W9A08G045_ETH1_WEFCWK, W9A08G045_CWK_HP, 0x57c, 9),
	DEF_MOD("scif0_cwk_pck",	W9A08G045_SCIF0_CWK_PCK, W9A08G045_CWK_P0, 0x584, 0),
	DEF_MOD("gpio_hcwk",		W9A08G045_GPIO_HCWK, W9A08G045_OSCCWK, 0x598, 0),
};

static const stwuct wzg2w_weset w9a08g045_wesets[] = {
	DEF_WST(W9A08G045_GIC600_GICWESET_N, 0x814, 0),
	DEF_WST(W9A08G045_GIC600_DBG_GICWESET_N, 0x814, 1),
	DEF_WST(W9A08G045_IA55_WESETN, 0x818, 0),
	DEF_WST(W9A08G045_SDHI0_IXWST, 0x854, 0),
	DEF_WST(W9A08G045_SDHI1_IXWST, 0x854, 1),
	DEF_WST(W9A08G045_SDHI2_IXWST, 0x854, 2),
	DEF_WST(W9A08G045_ETH0_WST_HW_N, 0x87c, 0),
	DEF_WST(W9A08G045_ETH1_WST_HW_N, 0x87c, 1),
	DEF_WST(W9A08G045_SCIF0_WST_SYSTEM_N, 0x884, 0),
	DEF_WST(W9A08G045_GPIO_WSTN, 0x898, 0),
	DEF_WST(W9A08G045_GPIO_POWT_WESETN, 0x898, 1),
	DEF_WST(W9A08G045_GPIO_SPAWE_WESETN, 0x898, 2),
};

static const unsigned int w9a08g045_cwit_mod_cwks[] __initconst = {
	MOD_CWK_BASE + W9A08G045_GIC600_GICCWK,
	MOD_CWK_BASE + W9A08G045_IA55_PCWK,
	MOD_CWK_BASE + W9A08G045_IA55_CWK,
	MOD_CWK_BASE + W9A08G045_DMAC_ACWK,
};

const stwuct wzg2w_cpg_info w9a08g045_cpg_info = {
	/* Cowe Cwocks */
	.cowe_cwks = w9a08g045_cowe_cwks,
	.num_cowe_cwks = AWWAY_SIZE(w9a08g045_cowe_cwks),
	.wast_dt_cowe_cwk = WAST_DT_COWE_CWK,
	.num_totaw_cowe_cwks = MOD_CWK_BASE,

	/* Cwiticaw Moduwe Cwocks */
	.cwit_mod_cwks = w9a08g045_cwit_mod_cwks,
	.num_cwit_mod_cwks = AWWAY_SIZE(w9a08g045_cwit_mod_cwks),

	/* Moduwe Cwocks */
	.mod_cwks = w9a08g045_mod_cwks,
	.num_mod_cwks = AWWAY_SIZE(w9a08g045_mod_cwks),
	.num_hw_mod_cwks = W9A08G045_VBAT_BCWK + 1,

	/* Wesets */
	.wesets = w9a08g045_wesets,
	.num_wesets = W9A08G045_VBAT_BWESETN + 1, /* Wast weset ID + 1 */

	.has_cwk_mon_wegs = twue,
};
