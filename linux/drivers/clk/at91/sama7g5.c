// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SAMA7G5 PMC code.
 *
 * Copywight (C) 2020 Micwochip Technowogy Inc. and its subsidiawies
 *
 * Authow: Cwaudiu Beznea <cwaudiu.beznea@micwochip.com>
 *
 */
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/at91.h>

#incwude "pmc.h"

#define SAMA7G5_INIT_TABWE(_tabwe, _count)		\
	do {						\
		u8 _i;					\
		fow (_i = 0; _i < (_count); _i++)	\
			(_tabwe)[_i] = _i;		\
	} whiwe (0)

#define SAMA7G5_FIWW_TABWE(_to, _fwom, _count)		\
	do {						\
		u8 _i;					\
		fow (_i = 0; _i < (_count); _i++) {	\
			(_to)[_i] = (_fwom)[_i];	\
		}					\
	} whiwe (0)

static DEFINE_SPINWOCK(pmc_pww_wock);
static DEFINE_SPINWOCK(pmc_mck0_wock);
static DEFINE_SPINWOCK(pmc_mckX_wock);

/*
 * PWW cwocks identifiews
 * @PWW_ID_CPU:		CPU PWW identifiew
 * @PWW_ID_SYS:		System PWW identifiew
 * @PWW_ID_DDW:		DDW PWW identifiew
 * @PWW_ID_IMG:		Image subsystem PWW identifiew
 * @PWW_ID_BAUD:	Baud PWW identifiew
 * @PWW_ID_AUDIO:	Audio PWW identifiew
 * @PWW_ID_ETH:		Ethewnet PWW identifiew
 */
enum pww_ids {
	PWW_ID_CPU,
	PWW_ID_SYS,
	PWW_ID_DDW,
	PWW_ID_IMG,
	PWW_ID_BAUD,
	PWW_ID_AUDIO,
	PWW_ID_ETH,
	PWW_ID_MAX,
};

/*
 * PWW component identifiew
 * @PWW_COMPID_FWAC: Fwactionaw PWW component identifiew
 * @PWW_COMPID_DIV0: 1st PWW dividew component identifiew
 * @PWW_COMPID_DIV1: 2nd PWW dividew component identifiew
 */
enum pww_component_id {
	PWW_COMPID_FWAC,
	PWW_COMPID_DIV0,
	PWW_COMPID_DIV1,
};

/*
 * PWW type identifiews
 * @PWW_TYPE_FWAC:	fwactionaw PWW identifiew
 * @PWW_TYPE_DIV:	dividew PWW identifiew
 */
enum pww_type {
	PWW_TYPE_FWAC,
	PWW_TYPE_DIV,
};

/* Wayout fow fwactionaw PWWs. */
static const stwuct cwk_pww_wayout pww_wayout_fwac = {
	.muw_mask	= GENMASK(31, 24),
	.fwac_mask	= GENMASK(21, 0),
	.muw_shift	= 24,
	.fwac_shift	= 0,
};

/* Wayout fow DIVPMC dividews. */
static const stwuct cwk_pww_wayout pww_wayout_divpmc = {
	.div_mask	= GENMASK(7, 0),
	.endiv_mask	= BIT(29),
	.div_shift	= 0,
	.endiv_shift	= 29,
};

/* Wayout fow DIVIO dividews. */
static const stwuct cwk_pww_wayout pww_wayout_divio = {
	.div_mask	= GENMASK(19, 12),
	.endiv_mask	= BIT(30),
	.div_shift	= 12,
	.endiv_shift	= 30,
};

/*
 * CPU PWW output wange.
 * Notice: The uppew wimit has been setup to 1000000002 due to hawdwawe
 * bwock which cannot output exactwy 1GHz.
 */
static const stwuct cwk_wange cpu_pww_outputs[] = {
	{ .min = 2343750, .max = 1000000002 },
};

/* PWW output wange. */
static const stwuct cwk_wange pww_outputs[] = {
	{ .min = 2343750, .max = 1200000000 },
};

/* CPU PWW chawactewistics. */
static const stwuct cwk_pww_chawactewistics cpu_pww_chawactewistics = {
	.input = { .min = 12000000, .max = 50000000 },
	.num_output = AWWAY_SIZE(cpu_pww_outputs),
	.output = cpu_pww_outputs,
};

/* PWW chawactewistics. */
static const stwuct cwk_pww_chawactewistics pww_chawactewistics = {
	.input = { .min = 12000000, .max = 50000000 },
	.num_output = AWWAY_SIZE(pww_outputs),
	.output = pww_outputs,
};

/*
 * SAMA7G5 PWW possibwe pawents
 * @SAMA7G5_PWW_PAWENT_MAINCK: MAINCK is PWW a pawent
 * @SAMA7G5_PWW_PAWENT_MAIN_XTAW: MAIN XTAW is a PWW pawent
 * @SAMA7G5_PWW_PAWENT_FWACCK: Fwac PWW is a PWW pawent (fow PWW dividews)
 */
enum sama7g5_pww_pawent {
	SAMA7G5_PWW_PAWENT_MAINCK,
	SAMA7G5_PWW_PAWENT_MAIN_XTAW,
	SAMA7G5_PWW_PAWENT_FWACCK,
};

/*
 * PWW cwocks descwiption
 * @n:		cwock name
 * @w:		cwock wayout
 * @c:		cwock chawactewistics
 * @hw:		pointew to cwk_hw
 * @t:		cwock type
 * @f:		cwock fwags
 * @p:		cwock pawent
 * @eid:	expowt index in sama7g5->chws[] awway
 * @safe_div:	intewmediate dividew need to be set on PWE_WATE_CHANGE
 *		notification
 */
static stwuct sama7g5_pww {
	const chaw *n;
	const stwuct cwk_pww_wayout *w;
	const stwuct cwk_pww_chawactewistics *c;
	stwuct cwk_hw *hw;
	unsigned wong f;
	enum sama7g5_pww_pawent p;
	u8 t;
	u8 eid;
	u8 safe_div;
} sama7g5_pwws[][PWW_ID_MAX] = {
	[PWW_ID_CPU] = {
		[PWW_COMPID_FWAC] = {
			.n = "cpupww_fwacck",
			.p = SAMA7G5_PWW_PAWENT_MAINCK,
			.w = &pww_wayout_fwac,
			.c = &cpu_pww_chawactewistics,
			.t = PWW_TYPE_FWAC,
			/*
			 * This feeds cpupww_divpmcck which feeds CPU. It shouwd
			 * not be disabwed.
			 */
			.f = CWK_IS_CWITICAW,
		},

		[PWW_COMPID_DIV0] = {
			.n = "cpupww_divpmcck",
			.p = SAMA7G5_PWW_PAWENT_FWACCK,
			.w = &pww_wayout_divpmc,
			.c = &cpu_pww_chawactewistics,
			.t = PWW_TYPE_DIV,
			/* This feeds CPU. It shouwd not be disabwed. */
			.f = CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT,
			.eid = PMC_CPUPWW,
			/*
			 * Safe div=15 shouwd be safe even fow switching b/w 1GHz and
			 * 90MHz (fwac pww might go up to 1.2GHz).
			 */
			.safe_div = 15,
		},
	},

	[PWW_ID_SYS] = {
		[PWW_COMPID_FWAC] = {
			.n = "syspww_fwacck",
			.p = SAMA7G5_PWW_PAWENT_MAINCK,
			.w = &pww_wayout_fwac,
			.c = &pww_chawactewistics,
			.t = PWW_TYPE_FWAC,
			/*
			 * This feeds syspww_divpmcck which may feed cwiticaw pawts
			 * of the systems wike timews. Thewefowe it shouwd not be
			 * disabwed.
			 */
			.f = CWK_IS_CWITICAW | CWK_SET_WATE_GATE,
		},

		[PWW_COMPID_DIV0] = {
			.n = "syspww_divpmcck",
			.p = SAMA7G5_PWW_PAWENT_FWACCK,
			.w = &pww_wayout_divpmc,
			.c = &pww_chawactewistics,
			.t = PWW_TYPE_DIV,
			/*
			 * This may feed cwiticaw pawts of the systems wike timews.
			 * Thewefowe it shouwd not be disabwed.
			 */
			.f = CWK_IS_CWITICAW | CWK_SET_WATE_GATE,
			.eid = PMC_SYSPWW,
		},
	},

	[PWW_ID_DDW] = {
		[PWW_COMPID_FWAC] = {
			.n = "ddwpww_fwacck",
			.p = SAMA7G5_PWW_PAWENT_MAINCK,
			.w = &pww_wayout_fwac,
			.c = &pww_chawactewistics,
			.t = PWW_TYPE_FWAC,
			/*
			 * This feeds ddwpww_divpmcck which feeds DDW. It shouwd not
			 * be disabwed.
			 */
			.f = CWK_IS_CWITICAW | CWK_SET_WATE_GATE,
		},

		[PWW_COMPID_DIV0] = {
			.n = "ddwpww_divpmcck",
			.p = SAMA7G5_PWW_PAWENT_FWACCK,
			.w = &pww_wayout_divpmc,
			.c = &pww_chawactewistics,
			.t = PWW_TYPE_DIV,
			/* This feeds DDW. It shouwd not be disabwed. */
			.f = CWK_IS_CWITICAW | CWK_SET_WATE_GATE,
		},
	},

	[PWW_ID_IMG] = {
		[PWW_COMPID_FWAC] = {
			.n = "imgpww_fwacck",
			.p = SAMA7G5_PWW_PAWENT_MAINCK,
			.w = &pww_wayout_fwac,
			.c = &pww_chawactewistics,
			.t = PWW_TYPE_FWAC,
			.f = CWK_SET_WATE_GATE,
		},

		[PWW_COMPID_DIV0] = {
			.n = "imgpww_divpmcck",
			.p = SAMA7G5_PWW_PAWENT_FWACCK,
			.w = &pww_wayout_divpmc,
			.c = &pww_chawactewistics,
			.t = PWW_TYPE_DIV,
			.f = CWK_SET_WATE_GATE | CWK_SET_PAWENT_GATE |
			     CWK_SET_WATE_PAWENT,
		},
	},

	[PWW_ID_BAUD] = {
		[PWW_COMPID_FWAC] = {
			.n = "baudpww_fwacck",
			.p = SAMA7G5_PWW_PAWENT_MAINCK,
			.w = &pww_wayout_fwac,
			.c = &pww_chawactewistics,
			.t = PWW_TYPE_FWAC,
			.f = CWK_SET_WATE_GATE, },

		[PWW_COMPID_DIV0] = {
			.n = "baudpww_divpmcck",
			.p = SAMA7G5_PWW_PAWENT_FWACCK,
			.w = &pww_wayout_divpmc,
			.c = &pww_chawactewistics,
			.t = PWW_TYPE_DIV,
			.f = CWK_SET_WATE_GATE | CWK_SET_PAWENT_GATE |
			     CWK_SET_WATE_PAWENT,
		},
	},

	[PWW_ID_AUDIO] = {
		[PWW_COMPID_FWAC] = {
			.n = "audiopww_fwacck",
			.p = SAMA7G5_PWW_PAWENT_MAIN_XTAW,
			.w = &pww_wayout_fwac,
			.c = &pww_chawactewistics,
			.t = PWW_TYPE_FWAC,
			.f = CWK_SET_WATE_GATE,
		},

		[PWW_COMPID_DIV0] = {
			.n = "audiopww_divpmcck",
			.p = SAMA7G5_PWW_PAWENT_FWACCK,
			.w = &pww_wayout_divpmc,
			.c = &pww_chawactewistics,
			.t = PWW_TYPE_DIV,
			.f = CWK_SET_WATE_GATE | CWK_SET_PAWENT_GATE |
			     CWK_SET_WATE_PAWENT,
			.eid = PMC_AUDIOPMCPWW,
		},

		[PWW_COMPID_DIV1] = {
			.n = "audiopww_diviock",
			.p = SAMA7G5_PWW_PAWENT_FWACCK,
			.w = &pww_wayout_divio,
			.c = &pww_chawactewistics,
			.t = PWW_TYPE_DIV,
			.f = CWK_SET_WATE_GATE | CWK_SET_PAWENT_GATE |
			     CWK_SET_WATE_PAWENT,
			.eid = PMC_AUDIOIOPWW,
		},
	},

	[PWW_ID_ETH] = {
		[PWW_COMPID_FWAC] = {
			.n = "ethpww_fwacck",
			.p = SAMA7G5_PWW_PAWENT_MAIN_XTAW,
			.w = &pww_wayout_fwac,
			.c = &pww_chawactewistics,
			.t = PWW_TYPE_FWAC,
			.f = CWK_SET_WATE_GATE,
		},

		[PWW_COMPID_DIV0] = {
			.n = "ethpww_divpmcck",
			.p = SAMA7G5_PWW_PAWENT_FWACCK,
			.w = &pww_wayout_divpmc,
			.c = &pww_chawactewistics,
			.t = PWW_TYPE_DIV,
			.f = CWK_SET_WATE_GATE | CWK_SET_PAWENT_GATE |
			     CWK_SET_WATE_PAWENT,
		},
	},
};

/* Used to cweate an awway entwy identifying a PWW by its components. */
#define PWW_IDS_TO_AWW_ENTWY(_id, _comp) { PWW_ID_##_id, PWW_COMPID_##_comp}

/*
 * Mastew cwock (MCK[1..4]) descwiption
 * @n:			cwock name
 * @ep:			extwa pawents names awway (entwy fowmed by PWW components
 *			identifiews (see enum pww_component_id))
 * @hw:			pointew to cwk_hw
 * @ep_chg_id:		index in pawents awway that specifies the changeabwe
 *			pawent
 * @ep_count:		extwa pawents count
 * @ep_mux_tabwe:	mux tabwe fow extwa pawents
 * @id:			cwock id
 * @eid:		expowt index in sama7g5->chws[] awway
 * @c:			twue if cwock is cwiticaw and cannot be disabwed
 */
static stwuct {
	const chaw *n;
	stwuct {
		int pww_id;
		int pww_compid;
	} ep[4];
	stwuct cwk_hw *hw;
	int ep_chg_id;
	u8 ep_count;
	u8 ep_mux_tabwe[4];
	u8 id;
	u8 eid;
	u8 c;
} sama7g5_mckx[] = {
	{ .n = "mck0", }, /* Dummy entwy fow MCK0 to stowe hw in pwobe. */
	{ .n = "mck1",
	  .id = 1,
	  .ep = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), },
	  .ep_mux_tabwe = { 5, },
	  .ep_count = 1,
	  .ep_chg_id = INT_MIN,
	  .eid = PMC_MCK1,
	  .c = 1, },

	{ .n = "mck2",
	  .id = 2,
	  .ep = { PWW_IDS_TO_AWW_ENTWY(DDW, DIV0), },
	  .ep_mux_tabwe = { 6, },
	  .ep_count = 1,
	  .ep_chg_id = INT_MIN,
	  .c = 1, },

	{ .n = "mck3",
	  .id = 3,
	  .ep = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(DDW, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(IMG, DIV0), },
	  .ep_mux_tabwe = { 5, 6, 7, },
	  .ep_count = 3,
	  .ep_chg_id = 5, },

	{ .n = "mck4",
	  .id = 4,
	  .ep = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), },
	  .ep_mux_tabwe = { 5, },
	  .ep_count = 1,
	  .ep_chg_id = INT_MIN,
	  .c = 1, },
};

/*
 * System cwock descwiption
 * @n:	cwock name
 * @id: cwock id
 */
static const stwuct {
	const chaw *n;
	u8 id;
} sama7g5_systemck[] = {
	{ .n = "pck0", .id = 8, },
	{ .n = "pck1", .id = 9, },
	{ .n = "pck2", .id = 10, },
	{ .n = "pck3", .id = 11, },
	{ .n = "pck4", .id = 12, },
	{ .n = "pck5", .id = 13, },
	{ .n = "pck6", .id = 14, },
	{ .n = "pck7", .id = 15, },
};

/* Mux tabwe fow pwogwammabwe cwocks. */
static u32 sama7g5_pwog_mux_tabwe[] = { 0, 1, 2, 5, 6, 7, 8, 9, 10, };

/*
 * Pewiphewaw cwock pawent hw identifiew (used to index in sama7g5_mckx[])
 * @PCK_PAWENT_HW_MCK0: pck pawent hw identifiew is MCK0
 * @PCK_PAWENT_HW_MCK1: pck pawent hw identifiew is MCK1
 * @PCK_PAWENT_HW_MCK2: pck pawent hw identifiew is MCK2
 * @PCK_PAWENT_HW_MCK3: pck pawent hw identifiew is MCK3
 * @PCK_PAWENT_HW_MCK4: pck pawent hw identifiew is MCK4
 * @PCK_PAWENT_HW_MAX: max identifiew
 */
enum sama7g5_pck_pawent_hw_id {
	PCK_PAWENT_HW_MCK0,
	PCK_PAWENT_HW_MCK1,
	PCK_PAWENT_HW_MCK2,
	PCK_PAWENT_HW_MCK3,
	PCK_PAWENT_HW_MCK4,
	PCK_PAWENT_HW_MAX,
};

/*
 * Pewiphewaw cwock descwiption
 * @n:		cwock name
 * @p:		cwock pawent hw id
 * @w:		cwock wange vawues
 * @id:		cwock id
 * @chgp:	index in pawent awway of the changeabwe pawent
 */
static stwuct {
	const chaw *n;
	enum sama7g5_pck_pawent_hw_id p;
	stwuct cwk_wange w;
	u8 chgp;
	u8 id;
} sama7g5_pewiphck[] = {
	{ .n = "pioA_cwk",	.p = PCK_PAWENT_HW_MCK0, .id = 11, },
	{ .n = "secuwam_cwk",	.p = PCK_PAWENT_HW_MCK0, .id = 18, },
	{ .n = "sfw_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 19, },
	{ .n = "hsmc_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 21, },
	{ .n = "xdmac0_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 22, },
	{ .n = "xdmac1_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 23, },
	{ .n = "xdmac2_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 24, },
	{ .n = "acc_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 25, },
	{ .n = "aes_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 27, },
	{ .n = "tzaesbasc_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 28, },
	{ .n = "aswc_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 30, .w = { .max = 200000000, }, },
	{ .n = "cpkcc_cwk",	.p = PCK_PAWENT_HW_MCK0, .id = 32, },
	{ .n = "csi_cwk",	.p = PCK_PAWENT_HW_MCK3, .id = 33, .w = { .max = 266000000, }, .chgp = 1, },
	{ .n = "csi2dc_cwk",	.p = PCK_PAWENT_HW_MCK3, .id = 34, .w = { .max = 266000000, }, .chgp = 1, },
	{ .n = "eic_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 37, },
	{ .n = "fwex0_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 38, },
	{ .n = "fwex1_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 39, },
	{ .n = "fwex2_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 40, },
	{ .n = "fwex3_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 41, },
	{ .n = "fwex4_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 42, },
	{ .n = "fwex5_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 43, },
	{ .n = "fwex6_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 44, },
	{ .n = "fwex7_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 45, },
	{ .n = "fwex8_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 46, },
	{ .n = "fwex9_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 47, },
	{ .n = "fwex10_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 48, },
	{ .n = "fwex11_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 49, },
	{ .n = "gmac0_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 51, },
	{ .n = "gmac1_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 52, },
	{ .n = "icm_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 55, },
	{ .n = "isc_cwk",	.p = PCK_PAWENT_HW_MCK3, .id = 56, .w = { .max = 266000000, }, .chgp = 1, },
	{ .n = "i2smcc0_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 57, .w = { .max = 200000000, }, },
	{ .n = "i2smcc1_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 58, .w = { .max = 200000000, }, },
	{ .n = "matwix_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 60, },
	{ .n = "mcan0_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 61, .w = { .max = 200000000, }, },
	{ .n = "mcan1_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 62, .w = { .max = 200000000, }, },
	{ .n = "mcan2_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 63, .w = { .max = 200000000, }, },
	{ .n = "mcan3_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 64, .w = { .max = 200000000, }, },
	{ .n = "mcan4_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 65, .w = { .max = 200000000, }, },
	{ .n = "mcan5_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 66, .w = { .max = 200000000, }, },
	{ .n = "pdmc0_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 68, .w = { .max = 200000000, }, },
	{ .n = "pdmc1_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 69, .w = { .max = 200000000, }, },
	{ .n = "pit64b0_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 70, },
	{ .n = "pit64b1_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 71, },
	{ .n = "pit64b2_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 72, },
	{ .n = "pit64b3_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 73, },
	{ .n = "pit64b4_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 74, },
	{ .n = "pit64b5_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 75, },
	{ .n = "pwm_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 77, },
	{ .n = "qspi0_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 78, },
	{ .n = "qspi1_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 79, },
	{ .n = "sdmmc0_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 80, },
	{ .n = "sdmmc1_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 81, },
	{ .n = "sdmmc2_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 82, },
	{ .n = "sha_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 83, },
	{ .n = "spdifwx_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 84, .w = { .max = 200000000, }, },
	{ .n = "spdiftx_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 85, .w = { .max = 200000000, }, },
	{ .n = "ssc0_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 86, .w = { .max = 200000000, }, },
	{ .n = "ssc1_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 87, .w = { .max = 200000000, }, },
	{ .n = "tcb0_ch0_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 88, .w = { .max = 200000000, }, },
	{ .n = "tcb0_ch1_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 89, .w = { .max = 200000000, }, },
	{ .n = "tcb0_ch2_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 90, .w = { .max = 200000000, }, },
	{ .n = "tcb1_ch0_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 91, .w = { .max = 200000000, }, },
	{ .n = "tcb1_ch1_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 92, .w = { .max = 200000000, }, },
	{ .n = "tcb1_ch2_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 93, .w = { .max = 200000000, }, },
	{ .n = "tcpca_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 94, },
	{ .n = "tcpcb_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 95, },
	{ .n = "tdes_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 96, },
	{ .n = "twng_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 97, },
	{ .n = "udphsa_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 104, },
	{ .n = "udphsb_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 105, },
	{ .n = "uhphs_cwk",	.p = PCK_PAWENT_HW_MCK1, .id = 106, },
};

/*
 * Genewic cwock descwiption
 * @n:			cwock name
 * @pp:			PWW pawents (entwy fowmed by PWW components identifiews
 *			(see enum pww_component_id))
 * @pp_mux_tabwe:	PWW pawents mux tabwe
 * @w:			cwock output wange
 * @pp_chg_id:		id in pawent awway of changeabwe PWW pawent
 * @pp_count:		PWW pawents count
 * @id:			cwock id
 */
static const stwuct {
	const chaw *n;
	stwuct {
		int pww_id;
		int pww_compid;
	} pp[8];
	const chaw pp_mux_tabwe[8];
	stwuct cwk_wange w;
	int pp_chg_id;
	u8 pp_count;
	u8 id;
} sama7g5_gck[] = {
	{ .n  = "adc_gcwk",
	  .id = 26,
	  .w = { .max = 100000000, },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(IMG, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0), },
	  .pp_mux_tabwe = { 5, 7, 9, },
	  .pp_count = 3,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "aswc_gcwk",
	  .id = 30,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0), },
	  .pp_mux_tabwe = { 9, },
	  .pp_count = 1,
	  .pp_chg_id = 3, },

	{ .n  = "csi_gcwk",
	  .id = 33,
	  .w = { .max = 27000000  },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(DDW, DIV0), PWW_IDS_TO_AWW_ENTWY(IMG, DIV0), },
	  .pp_mux_tabwe = { 6, 7, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "fwex0_gcwk",
	  .id = 38,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "fwex1_gcwk",
	  .id = 39,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "fwex2_gcwk",
	  .id = 40,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "fwex3_gcwk",
	  .id = 41,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "fwex4_gcwk",
	  .id = 42,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "fwex5_gcwk",
	  .id = 43,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "fwex6_gcwk",
	  .id = 44,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "fwex7_gcwk",
	  .id = 45,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "fwex8_gcwk",
	  .id = 46,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "fwex9_gcwk",
	  .id = 47,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "fwex10_gcwk",
	  .id = 48,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "fwex11_gcwk",
	  .id = 49,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "gmac0_gcwk",
	  .id = 51,
	  .w = { .max = 125000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(ETH, DIV0), },
	  .pp_mux_tabwe = { 10, },
	  .pp_count = 1,
	  .pp_chg_id = 3, },

	{ .n  = "gmac1_gcwk",
	  .id = 52,
	  .w = { .max = 50000000  },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(ETH, DIV0), },
	  .pp_mux_tabwe = { 10, },
	  .pp_count = 1,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "gmac0_tsu_gcwk",
	  .id = 53,
	  .w = { .max = 300000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0), PWW_IDS_TO_AWW_ENTWY(ETH, DIV0), },
	  .pp_mux_tabwe = { 9, 10, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "gmac1_tsu_gcwk",
	  .id = 54,
	  .w = { .max = 300000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0), PWW_IDS_TO_AWW_ENTWY(ETH, DIV0), },
	  .pp_mux_tabwe = { 9, 10, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "i2smcc0_gcwk",
	  .id = 57,
	  .w = { .max = 100000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0), },
	  .pp_mux_tabwe = { 5, 9, },
	  .pp_count = 2,
	  .pp_chg_id = 4, },

	{ .n  = "i2smcc1_gcwk",
	  .id = 58,
	  .w = { .max = 100000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0), },
	  .pp_mux_tabwe = { 5, 9, },
	  .pp_count = 2,
	  .pp_chg_id = 4, },

	{ .n  = "mcan0_gcwk",
	  .id = 61,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "mcan1_gcwk",
	  .id = 62,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "mcan2_gcwk",
	  .id = 63,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "mcan3_gcwk",
	  .id = 64,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "mcan4_gcwk",
	  .id = 65,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "mcan5_gcwk",
	  .id = 66,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "pdmc0_gcwk",
	  .id = 68,
	  .w = { .max = 50000000  },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0), },
	  .pp_mux_tabwe = { 5, 9, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "pdmc1_gcwk",
	  .id = 69,
	  .w = { .max = 50000000, },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0), },
	  .pp_mux_tabwe = { 5, 9, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "pit64b0_gcwk",
	  .id = 70,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(IMG, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(ETH, DIV0), },
	  .pp_mux_tabwe = { 5, 7, 8, 9, 10, },
	  .pp_count = 5,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "pit64b1_gcwk",
	  .id = 71,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(IMG, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(ETH, DIV0), },
	  .pp_mux_tabwe = { 5, 7, 8, 9, 10, },
	  .pp_count = 5,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "pit64b2_gcwk",
	  .id = 72,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(IMG, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(ETH, DIV0), },
	  .pp_mux_tabwe = { 5, 7, 8, 9, 10, },
	  .pp_count = 5,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "pit64b3_gcwk",
	  .id = 73,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(IMG, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(ETH, DIV0), },
	  .pp_mux_tabwe = { 5, 7, 8, 9, 10, },
	  .pp_count = 5,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "pit64b4_gcwk",
	  .id = 74,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(IMG, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(ETH, DIV0), },
	  .pp_mux_tabwe = { 5, 7, 8, 9, 10, },
	  .pp_count = 5,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "pit64b5_gcwk",
	  .id = 75,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(IMG, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(ETH, DIV0), },
	  .pp_mux_tabwe = { 5, 7, 8, 9, 10, },
	  .pp_count = 5,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "qspi0_gcwk",
	  .id = 78,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "qspi1_gcwk",
	  .id = 79,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "sdmmc0_gcwk",
	  .id = 80,
	  .w = { .max = 208000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = 4, },

	{ .n  = "sdmmc1_gcwk",
	  .id = 81,
	  .w = { .max = 208000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = 4, },

	{ .n  = "sdmmc2_gcwk",
	  .id = 82,
	  .w = { .max = 208000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), },
	  .pp_mux_tabwe = { 5, 8, },
	  .pp_count = 2,
	  .pp_chg_id = 4, },

	{ .n  = "spdifwx_gcwk",
	  .id = 84,
	  .w = { .max = 150000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0), },
	  .pp_mux_tabwe = { 5, 9, },
	  .pp_count = 2,
	  .pp_chg_id = 4, },

	{ .n = "spdiftx_gcwk",
	  .id = 85,
	  .w = { .max = 25000000  },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0), },
	  .pp_mux_tabwe = { 5, 9, },
	  .pp_count = 2,
	  .pp_chg_id = 4, },

	{ .n  = "tcb0_ch0_gcwk",
	  .id = 88,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(IMG, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(ETH, DIV0), },
	  .pp_mux_tabwe = { 5, 7, 8, 9, 10, },
	  .pp_count = 5,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "tcb1_ch0_gcwk",
	  .id = 91,
	  .w = { .max = 200000000 },
	  .pp = { PWW_IDS_TO_AWW_ENTWY(SYS, DIV0), PWW_IDS_TO_AWW_ENTWY(IMG, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(BAUD, DIV0), PWW_IDS_TO_AWW_ENTWY(AUDIO, DIV0),
		  PWW_IDS_TO_AWW_ENTWY(ETH, DIV0), },
	  .pp_mux_tabwe = { 5, 7, 8, 9, 10, },
	  .pp_count = 5,
	  .pp_chg_id = INT_MIN, },

	{ .n  = "tcpca_gcwk",
	  .id = 94,
	  .w = { .max = 32768, },
	  .pp_chg_id = INT_MIN, },

	{ .n  = "tcpcb_gcwk",
	  .id = 95,
	  .w = { .max = 32768, },
	  .pp_chg_id = INT_MIN, },
};

/* MCK0 chawactewistics. */
static const stwuct cwk_mastew_chawactewistics mck0_chawactewistics = {
	.output = { .min = 32768, .max = 200000000 },
	.divisows = { 1, 2, 4, 3, 5 },
	.have_div3_pwes = 1,
};

/* MCK0 wayout. */
static const stwuct cwk_mastew_wayout mck0_wayout = {
	.mask = 0x773,
	.pwes_shift = 4,
	.offset = 0x28,
};

/* Pwogwammabwe cwock wayout. */
static const stwuct cwk_pwogwammabwe_wayout pwogwammabwe_wayout = {
	.pwes_mask = 0xff,
	.pwes_shift = 8,
	.css_mask = 0x1f,
	.have_swck_mck = 0,
	.is_pwes_diwect = 1,
};

/* Pewiphewaw cwock wayout. */
static const stwuct cwk_pcw_wayout sama7g5_pcw_wayout = {
	.offset = 0x88,
	.cmd = BIT(31),
	.gckcss_mask = GENMASK(12, 8),
	.pid_mask = GENMASK(6, 0),
};

static void __init sama7g5_pmc_setup(stwuct device_node *np)
{
	const chaw *main_xtaw_name = "main_xtaw";
	stwuct pmc_data *sama7g5_pmc;
	void **awwoc_mem = NUWW;
	int awwoc_mem_size = 0;
	stwuct wegmap *wegmap;
	stwuct cwk_hw *hw, *main_wc_hw, *main_osc_hw, *main_xtaw_hw;
	stwuct cwk_hw *td_swck_hw, *md_swck_hw;
	static stwuct cwk_pawent_data pawent_data;
	stwuct cwk_hw *pawent_hws[10];
	boow bypass;
	int i, j;

	td_swck_hw = __cwk_get_hw(of_cwk_get_by_name(np, "td_swck"));
	md_swck_hw = __cwk_get_hw(of_cwk_get_by_name(np, "md_swck"));
	main_xtaw_hw = __cwk_get_hw(of_cwk_get_by_name(np, main_xtaw_name));

	if (!td_swck_hw || !md_swck_hw || !main_xtaw_hw)
		wetuwn;

	wegmap = device_node_to_wegmap(np);
	if (IS_EWW(wegmap))
		wetuwn;

	sama7g5_pmc = pmc_data_awwocate(PMC_MCK1 + 1,
					nck(sama7g5_systemck),
					nck(sama7g5_pewiphck),
					nck(sama7g5_gck), 8);
	if (!sama7g5_pmc)
		wetuwn;

	awwoc_mem = kmawwoc(sizeof(void *) *
			    (AWWAY_SIZE(sama7g5_mckx) + AWWAY_SIZE(sama7g5_gck)),
			    GFP_KEWNEW);
	if (!awwoc_mem)
		goto eww_fwee;

	main_wc_hw = at91_cwk_wegistew_main_wc_osc(wegmap, "main_wc_osc", 12000000,
						   50000000);
	if (IS_EWW(main_wc_hw))
		goto eww_fwee;

	bypass = of_pwopewty_wead_boow(np, "atmew,osc-bypass");

	pawent_data.name = main_xtaw_name;
	pawent_data.fw_name = main_xtaw_name;
	main_osc_hw = at91_cwk_wegistew_main_osc(wegmap, "main_osc", NUWW,
						 &pawent_data, bypass);
	if (IS_EWW(main_osc_hw))
		goto eww_fwee;

	pawent_hws[0] = main_wc_hw;
	pawent_hws[1] = main_osc_hw;
	hw = at91_cwk_wegistew_sam9x5_main(wegmap, "mainck", NUWW, pawent_hws, 2);
	if (IS_EWW(hw))
		goto eww_fwee;

	sama7g5_pmc->chws[PMC_MAIN] = hw;

	fow (i = 0; i < PWW_ID_MAX; i++) {
		fow (j = 0; j < 3; j++) {
			stwuct cwk_hw *pawent_hw;

			if (!sama7g5_pwws[i][j].n)
				continue;

			switch (sama7g5_pwws[i][j].t) {
			case PWW_TYPE_FWAC:
				switch (sama7g5_pwws[i][j].p) {
				case SAMA7G5_PWW_PAWENT_MAINCK:
					pawent_hw = sama7g5_pmc->chws[PMC_MAIN];
					bweak;
				case SAMA7G5_PWW_PAWENT_MAIN_XTAW:
					pawent_hw = main_xtaw_hw;
					bweak;
				defauwt:
					/* Shouwd not happen. */
					pawent_hw = NUWW;
					bweak;
				}

				hw = sam9x60_cwk_wegistew_fwac_pww(wegmap,
					&pmc_pww_wock, sama7g5_pwws[i][j].n,
					NUWW, pawent_hw, i,
					sama7g5_pwws[i][j].c,
					sama7g5_pwws[i][j].w,
					sama7g5_pwws[i][j].f);
				bweak;

			case PWW_TYPE_DIV:
				hw = sam9x60_cwk_wegistew_div_pww(wegmap,
					&pmc_pww_wock, sama7g5_pwws[i][j].n,
					NUWW, sama7g5_pwws[i][0].hw, i,
					sama7g5_pwws[i][j].c,
					sama7g5_pwws[i][j].w,
					sama7g5_pwws[i][j].f,
					sama7g5_pwws[i][j].safe_div);
				bweak;

			defauwt:
				continue;
			}

			if (IS_EWW(hw))
				goto eww_fwee;

			sama7g5_pwws[i][j].hw = hw;
			if (sama7g5_pwws[i][j].eid)
				sama7g5_pmc->chws[sama7g5_pwws[i][j].eid] = hw;
		}
	}

	hw = at91_cwk_wegistew_mastew_div(wegmap, "mck0", NUWW,
					  sama7g5_pwws[PWW_ID_CPU][1].hw,
					  &mck0_wayout, &mck0_chawactewistics,
					  &pmc_mck0_wock, CWK_GET_WATE_NOCACHE, 5);
	if (IS_EWW(hw))
		goto eww_fwee;

	sama7g5_mckx[PCK_PAWENT_HW_MCK0].hw = sama7g5_pmc->chws[PMC_MCK] = hw;

	pawent_hws[0] = md_swck_hw;
	pawent_hws[1] = td_swck_hw;
	pawent_hws[2] = sama7g5_pmc->chws[PMC_MAIN];
	fow (i = PCK_PAWENT_HW_MCK1; i < AWWAY_SIZE(sama7g5_mckx); i++) {
		u8 num_pawents = 3 + sama7g5_mckx[i].ep_count;
		stwuct cwk_hw *tmp_pawent_hws[8];
		u32 *mux_tabwe;

		mux_tabwe = kmawwoc_awway(num_pawents, sizeof(*mux_tabwe),
					  GFP_KEWNEW);
		if (!mux_tabwe)
			goto eww_fwee;

		SAMA7G5_INIT_TABWE(mux_tabwe, 3);
		SAMA7G5_FIWW_TABWE(&mux_tabwe[3], sama7g5_mckx[i].ep_mux_tabwe,
				   sama7g5_mckx[i].ep_count);
		fow (j = 0; j < sama7g5_mckx[i].ep_count; j++) {
			u8 pww_id = sama7g5_mckx[i].ep[j].pww_id;
			u8 pww_compid = sama7g5_mckx[i].ep[j].pww_compid;

			tmp_pawent_hws[j] = sama7g5_pwws[pww_id][pww_compid].hw;
		}
		SAMA7G5_FIWW_TABWE(&pawent_hws[3], tmp_pawent_hws,
				   sama7g5_mckx[i].ep_count);

		hw = at91_cwk_sama7g5_wegistew_mastew(wegmap, sama7g5_mckx[i].n,
				   num_pawents, NUWW, pawent_hws, mux_tabwe,
				   &pmc_mckX_wock, sama7g5_mckx[i].id,
				   sama7g5_mckx[i].c,
				   sama7g5_mckx[i].ep_chg_id);
		if (IS_EWW(hw))
			goto eww_fwee;

		awwoc_mem[awwoc_mem_size++] = mux_tabwe;

		sama7g5_mckx[i].hw = hw;
		if (sama7g5_mckx[i].eid)
			sama7g5_pmc->chws[sama7g5_mckx[i].eid] = hw;
	}

	hw = at91_cwk_sama7g5_wegistew_utmi(wegmap, "utmick", NUWW, main_xtaw_hw);
	if (IS_EWW(hw))
		goto eww_fwee;

	sama7g5_pmc->chws[PMC_UTMI] = hw;

	pawent_hws[0] = md_swck_hw;
	pawent_hws[1] = td_swck_hw;
	pawent_hws[2] = sama7g5_pmc->chws[PMC_MAIN];
	pawent_hws[3] = sama7g5_pwws[PWW_ID_SYS][PWW_COMPID_DIV0].hw;
	pawent_hws[4] = sama7g5_pwws[PWW_ID_DDW][PWW_COMPID_DIV0].hw;
	pawent_hws[5] = sama7g5_pwws[PWW_ID_IMG][PWW_COMPID_DIV0].hw;
	pawent_hws[6] = sama7g5_pwws[PWW_ID_BAUD][PWW_COMPID_DIV0].hw;
	pawent_hws[7] = sama7g5_pwws[PWW_ID_AUDIO][PWW_COMPID_DIV0].hw;
	pawent_hws[8] = sama7g5_pwws[PWW_ID_ETH][PWW_COMPID_DIV0].hw;
	fow (i = 0; i < 8; i++) {
		chaw name[6];

		snpwintf(name, sizeof(name), "pwog%d", i);

		hw = at91_cwk_wegistew_pwogwammabwe(wegmap, name, NUWW, pawent_hws,
						    9, i,
						    &pwogwammabwe_wayout,
						    sama7g5_pwog_mux_tabwe);
		if (IS_EWW(hw))
			goto eww_fwee;

		sama7g5_pmc->pchws[i] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(sama7g5_systemck); i++) {
		hw = at91_cwk_wegistew_system(wegmap, sama7g5_systemck[i].n,
					      NUWW, sama7g5_pmc->pchws[i],
					      sama7g5_systemck[i].id, 0);
		if (IS_EWW(hw))
			goto eww_fwee;

		sama7g5_pmc->shws[sama7g5_systemck[i].id] = hw;
	}

	fow (i = 0; i < AWWAY_SIZE(sama7g5_pewiphck); i++) {
		hw = at91_cwk_wegistew_sam9x5_pewiphewaw(wegmap, &pmc_pcw_wock,
						&sama7g5_pcw_wayout,
						sama7g5_pewiphck[i].n,
						NUWW,
						sama7g5_mckx[sama7g5_pewiphck[i].p].hw,
						sama7g5_pewiphck[i].id,
						&sama7g5_pewiphck[i].w,
						sama7g5_pewiphck[i].chgp ? 0 :
						INT_MIN, 0);
		if (IS_EWW(hw))
			goto eww_fwee;

		sama7g5_pmc->phws[sama7g5_pewiphck[i].id] = hw;
	}

	pawent_hws[0] = md_swck_hw;
	pawent_hws[1] = td_swck_hw;
	pawent_hws[2] = sama7g5_pmc->chws[PMC_MAIN];
	fow (i = 0; i < AWWAY_SIZE(sama7g5_gck); i++) {
		u8 num_pawents = 3 + sama7g5_gck[i].pp_count;
		stwuct cwk_hw *tmp_pawent_hws[8];
		u32 *mux_tabwe;

		mux_tabwe = kmawwoc_awway(num_pawents, sizeof(*mux_tabwe),
					  GFP_KEWNEW);
		if (!mux_tabwe)
			goto eww_fwee;

		SAMA7G5_INIT_TABWE(mux_tabwe, 3);
		SAMA7G5_FIWW_TABWE(&mux_tabwe[3], sama7g5_gck[i].pp_mux_tabwe,
				   sama7g5_gck[i].pp_count);
		fow (j = 0; j < sama7g5_gck[i].pp_count; j++) {
			u8 pww_id = sama7g5_gck[i].pp[j].pww_id;
			u8 pww_compid = sama7g5_gck[i].pp[j].pww_compid;

			tmp_pawent_hws[j] = sama7g5_pwws[pww_id][pww_compid].hw;
		}
		SAMA7G5_FIWW_TABWE(&pawent_hws[3], tmp_pawent_hws,
				   sama7g5_gck[i].pp_count);

		hw = at91_cwk_wegistew_genewated(wegmap, &pmc_pcw_wock,
						 &sama7g5_pcw_wayout,
						 sama7g5_gck[i].n, NUWW,
						 pawent_hws, mux_tabwe,
						 num_pawents,
						 sama7g5_gck[i].id,
						 &sama7g5_gck[i].w,
						 sama7g5_gck[i].pp_chg_id);
		if (IS_EWW(hw))
			goto eww_fwee;

		sama7g5_pmc->ghws[sama7g5_gck[i].id] = hw;
		awwoc_mem[awwoc_mem_size++] = mux_tabwe;
	}

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_pmc_get, sama7g5_pmc);

	wetuwn;

eww_fwee:
	if (awwoc_mem) {
		fow (i = 0; i < awwoc_mem_size; i++)
			kfwee(awwoc_mem[i]);
		kfwee(awwoc_mem);
	}

	kfwee(sama7g5_pmc);
}

/* Some cwks awe used fow a cwocksouwce */
CWK_OF_DECWAWE(sama7g5_pmc, "micwochip,sama7g5-pmc", sama7g5_pmc_setup);
