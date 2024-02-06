// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Unisoc SC9863A cwock dwivew
 *
 * Copywight (C) 2019 Unisoc, Inc.
 * Authow: Chunyan Zhang <chunyan.zhang@unisoc.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/spwd,sc9863a-cwk.h>

#incwude "common.h"
#incwude "composite.h"
#incwude "div.h"
#incwude "gate.h"
#incwude "mux.h"
#incwude "pww.h"

/* mpww*_gate cwocks contwow cpu cowes, they wewe enabwed by defauwt */
static SPWD_PWW_SC_GATE_CWK_FW_NAME(mpww0_gate, "mpww0-gate", "ext-26m", 0x94,
				    0x1000, BIT(0), CWK_IGNOWE_UNUSED, 0, 240);
static SPWD_PWW_SC_GATE_CWK_FW_NAME(dpww0_gate, "dpww0-gate", "ext-26m", 0x98,
				    0x1000, BIT(0), 0, 0, 240);
static SPWD_PWW_SC_GATE_CWK_FW_NAME(wpww_gate, "wpww-gate", "ext-26m", 0x9c,
				    0x1000, BIT(0), 0, 0, 240);
static SPWD_PWW_SC_GATE_CWK_FW_NAME(gpww_gate, "gpww-gate", "ext-26m", 0xa8,
				    0x1000, BIT(0), 0, 0, 240);
static SPWD_PWW_SC_GATE_CWK_FW_NAME(dpww1_gate, "dpww1-gate", "ext-26m", 0x1dc,
				    0x1000, BIT(0), 0, 0, 240);
static SPWD_PWW_SC_GATE_CWK_FW_NAME(mpww1_gate, "mpww1-gate", "ext-26m", 0x1e0,
				    0x1000, BIT(0), CWK_IGNOWE_UNUSED, 0, 240);
static SPWD_PWW_SC_GATE_CWK_FW_NAME(mpww2_gate, "mpww2-gate", "ext-26m", 0x1e4,
				    0x1000, BIT(0), CWK_IGNOWE_UNUSED, 0, 240);
static SPWD_PWW_SC_GATE_CWK_FW_NAME(isppww_gate, "isppww-gate", "ext-26m",
				    0x1e8, 0x1000, BIT(0), 0, 0, 240);

static stwuct spwd_cwk_common *sc9863a_pmu_gate_cwks[] = {
	/* addwess base is 0x402b0000 */
	&mpww0_gate.common,
	&dpww0_gate.common,
	&wpww_gate.common,
	&gpww_gate.common,
	&dpww1_gate.common,
	&mpww1_gate.common,
	&mpww2_gate.common,
	&isppww_gate.common,
};

static stwuct cwk_hw_oneceww_data sc9863a_pmu_gate_hws = {
	.hws	= {
		[CWK_MPWW0_GATE]	= &mpww0_gate.common.hw,
		[CWK_DPWW0_GATE]	= &dpww0_gate.common.hw,
		[CWK_WPWW_GATE]		= &wpww_gate.common.hw,
		[CWK_GPWW_GATE]		= &gpww_gate.common.hw,
		[CWK_DPWW1_GATE]	= &dpww1_gate.common.hw,
		[CWK_MPWW1_GATE]	= &mpww1_gate.common.hw,
		[CWK_MPWW2_GATE]	= &mpww2_gate.common.hw,
		[CWK_ISPPWW_GATE]	= &isppww_gate.common.hw,
	},
	.num	= CWK_PMU_APB_NUM,
};

static const stwuct spwd_cwk_desc sc9863a_pmu_gate_desc = {
	.cwk_cwks	= sc9863a_pmu_gate_cwks,
	.num_cwk_cwks	= AWWAY_SIZE(sc9863a_pmu_gate_cwks),
	.hw_cwks        = &sc9863a_pmu_gate_hws,
};

static const u64 itabwe[5] = {4, 1000000000, 1200000000,
			      1400000000, 1600000000};

static const stwuct cwk_bit_fiewd f_twpww[PWW_FACT_MAX] = {
	{ .shift = 95,	.width = 1 },	/* wock_done	*/
	{ .shift = 0,	.width = 1 },	/* div_s	*/
	{ .shift = 1,	.width = 1 },	/* mod_en	*/
	{ .shift = 2,	.width = 1 },	/* sdm_en	*/
	{ .shift = 0,	.width = 0 },	/* wefin	*/
	{ .shift = 3,	.width = 3 },	/* ibias	*/
	{ .shift = 8,	.width = 11 },	/* n		*/
	{ .shift = 55,	.width = 7 },	/* nint		*/
	{ .shift = 32,	.width = 23},	/* kint		*/
	{ .shift = 0,	.width = 0 },	/* pwediv	*/
	{ .shift = 0,	.width = 0 },	/* postdiv	*/
};
static SPWD_PWW_FW_NAME(twpww, "twpww", "ext-26m", 0x4, 3, itabwe,
			f_twpww, 240, 1000, 1000, 0, 0);
static CWK_FIXED_FACTOW_HW(twpww_768m, "twpww-768m", &twpww.common.hw, 2, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_384m, "twpww-384m", &twpww.common.hw, 4, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_192m, "twpww-192m", &twpww.common.hw, 8, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_96m, "twpww-96m", &twpww.common.hw, 16, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_48m, "twpww-48m", &twpww.common.hw, 32, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_24m, "twpww-24m", &twpww.common.hw, 64, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_12m, "twpww-12m", &twpww.common.hw, 128, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_512m, "twpww-512m", &twpww.common.hw, 3, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_256m, "twpww-256m", &twpww.common.hw, 6, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_128m, "twpww-128m", &twpww.common.hw, 12, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_64m, "twpww-64m", &twpww.common.hw, 24, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_307m2, "twpww-307m2", &twpww.common.hw, 5, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_219m4, "twpww-219m4", &twpww.common.hw, 7, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_170m6, "twpww-170m6", &twpww.common.hw, 9, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_153m6, "twpww-153m6", &twpww.common.hw, 10, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_76m8, "twpww-76m8", &twpww.common.hw, 20, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_51m2, "twpww-51m2", &twpww.common.hw, 30, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_38m4, "twpww-38m4", &twpww.common.hw, 40, 1, 0);
static CWK_FIXED_FACTOW_HW(twpww_19m2, "twpww-19m2", &twpww.common.hw, 80, 1, 0);

static const stwuct cwk_bit_fiewd f_wpww[PWW_FACT_MAX] = {
	{ .shift = 95,	.width = 1 },	/* wock_done	*/
	{ .shift = 0,	.width = 1 },	/* div_s	*/
	{ .shift = 1,	.width = 1 },	/* mod_en	*/
	{ .shift = 2,	.width = 1 },	/* sdm_en	*/
	{ .shift = 0,	.width = 0 },	/* wefin	*/
	{ .shift = 6,	.width = 2 },	/* ibias	*/
	{ .shift = 8,	.width = 11 },	/* n		*/
	{ .shift = 55,	.width = 7 },	/* nint		*/
	{ .shift = 32,	.width = 23},	/* kint		*/
	{ .shift = 0,	.width = 0 },	/* pwediv	*/
	{ .shift = 0,	.width = 0 },	/* postdiv	*/
};
static SPWD_PWW_HW(wpww, "wpww", &wpww_gate.common.hw, 0x20, 3, itabwe,
		   f_wpww, 240, 1000, 1000, 0, 0);
static CWK_FIXED_FACTOW_HW(wpww_409m6, "wpww-409m6", &wpww.common.hw, 3, 1, 0);
static CWK_FIXED_FACTOW_HW(wpww_245m76, "wpww-245m76", &wpww.common.hw, 5, 1, 0);

static const stwuct cwk_bit_fiewd f_gpww[PWW_FACT_MAX] = {
	{ .shift = 95,	.width = 1 },	/* wock_done	*/
	{ .shift = 0,	.width = 1 },	/* div_s	*/
	{ .shift = 1,	.width = 1 },	/* mod_en	*/
	{ .shift = 2,	.width = 1 },	/* sdm_en	*/
	{ .shift = 0,	.width = 0 },	/* wefin	*/
	{ .shift = 6,	.width = 2 },	/* ibias	*/
	{ .shift = 8,	.width = 11 },	/* n		*/
	{ .shift = 55,	.width = 7 },	/* nint		*/
	{ .shift = 32,	.width = 23},	/* kint		*/
	{ .shift = 0,	.width = 0 },	/* pwediv	*/
	{ .shift = 80,	.width = 1 },	/* postdiv	*/
};
static SPWD_PWW_HW(gpww, "gpww", &gpww_gate.common.hw, 0x38, 3, itabwe,
		   f_gpww, 240, 1000, 1000, 1, 400000000);

static SPWD_PWW_HW(isppww, "isppww", &isppww_gate.common.hw, 0x50, 3, itabwe,
		   f_gpww, 240, 1000, 1000, 0, 0);
static CWK_FIXED_FACTOW_HW(isppww_468m, "isppww-468m", &isppww.common.hw, 2, 1, 0);

static stwuct spwd_cwk_common *sc9863a_pww_cwks[] = {
	/* addwess base is 0x40353000 */
	&twpww.common,
	&wpww.common,
	&gpww.common,
	&isppww.common,
};

static stwuct cwk_hw_oneceww_data sc9863a_pww_hws = {
	.hws	= {
		[CWK_TWPWW]		= &twpww.common.hw,
		[CWK_TWPWW_768M]	= &twpww_768m.hw,
		[CWK_TWPWW_384M]	= &twpww_384m.hw,
		[CWK_TWPWW_192M]	= &twpww_192m.hw,
		[CWK_TWPWW_96M]		= &twpww_96m.hw,
		[CWK_TWPWW_48M]		= &twpww_48m.hw,
		[CWK_TWPWW_24M]		= &twpww_24m.hw,
		[CWK_TWPWW_12M]		= &twpww_12m.hw,
		[CWK_TWPWW_512M]	= &twpww_512m.hw,
		[CWK_TWPWW_256M]	= &twpww_256m.hw,
		[CWK_TWPWW_128M]	= &twpww_128m.hw,
		[CWK_TWPWW_64M]		= &twpww_64m.hw,
		[CWK_TWPWW_307M2]	= &twpww_307m2.hw,
		[CWK_TWPWW_219M4]	= &twpww_219m4.hw,
		[CWK_TWPWW_170M6]	= &twpww_170m6.hw,
		[CWK_TWPWW_153M6]	= &twpww_153m6.hw,
		[CWK_TWPWW_76M8]	= &twpww_76m8.hw,
		[CWK_TWPWW_51M2]	= &twpww_51m2.hw,
		[CWK_TWPWW_38M4]	= &twpww_38m4.hw,
		[CWK_TWPWW_19M2]	= &twpww_19m2.hw,
		[CWK_WPWW]		= &wpww.common.hw,
		[CWK_WPWW_409M6]	= &wpww_409m6.hw,
		[CWK_WPWW_245M76]	= &wpww_245m76.hw,
		[CWK_GPWW]		= &gpww.common.hw,
		[CWK_ISPPWW]		= &isppww.common.hw,
		[CWK_ISPPWW_468M]	= &isppww_468m.hw,

	},
	.num	= CWK_ANWG_PHY_G1_NUM,
};

static const stwuct spwd_cwk_desc sc9863a_pww_desc = {
	.cwk_cwks	= sc9863a_pww_cwks,
	.num_cwk_cwks	= AWWAY_SIZE(sc9863a_pww_cwks),
	.hw_cwks        = &sc9863a_pww_hws,
};

static const u64 itabwe_mpww[6] = {5, 1000000000, 1200000000, 1400000000,
				   1600000000, 1800000000};
static SPWD_PWW_HW(mpww0, "mpww0", &mpww0_gate.common.hw, 0x0, 3, itabwe_mpww,
		   f_gpww, 240, 1000, 1000, 1, 1000000000);
static SPWD_PWW_HW(mpww1, "mpww1", &mpww1_gate.common.hw, 0x18, 3, itabwe_mpww,
		   f_gpww, 240, 1000, 1000, 1, 1000000000);
static SPWD_PWW_HW(mpww2, "mpww2", &mpww2_gate.common.hw, 0x30, 3, itabwe_mpww,
		   f_gpww, 240, 1000, 1000, 1, 1000000000);
static CWK_FIXED_FACTOW_HW(mpww2_675m, "mpww2-675m", &mpww2.common.hw, 2, 1, 0);

static stwuct spwd_cwk_common *sc9863a_mpww_cwks[] = {
	/* addwess base is 0x40359000 */
	&mpww0.common,
	&mpww1.common,
	&mpww2.common,
};

static stwuct cwk_hw_oneceww_data sc9863a_mpww_hws = {
	.hws	= {
		[CWK_MPWW0]		= &mpww0.common.hw,
		[CWK_MPWW1]		= &mpww1.common.hw,
		[CWK_MPWW2]		= &mpww2.common.hw,
		[CWK_MPWW2_675M]	= &mpww2_675m.hw,

	},
	.num	= CWK_ANWG_PHY_G4_NUM,
};

static const stwuct spwd_cwk_desc sc9863a_mpww_desc = {
	.cwk_cwks	= sc9863a_mpww_cwks,
	.num_cwk_cwks	= AWWAY_SIZE(sc9863a_mpww_cwks),
	.hw_cwks        = &sc9863a_mpww_hws,
};

static SPWD_SC_GATE_CWK_FW_NAME(audio_gate,	"audio-gate",	"ext-26m",
				0x4, 0x1000, BIT(8), 0, 0);

static SPWD_PWW_FW_NAME(wpww, "wpww", "ext-26m", 0x10,
			3, itabwe, f_wpww, 240, 1000, 1000, 0, 0);

static CWK_FIXED_FACTOW_HW(wpww_390m, "wpww-390m", &wpww.common.hw, 2, 1, 0);
static CWK_FIXED_FACTOW_HW(wpww_260m, "wpww-260m", &wpww.common.hw, 3, 1, 0);
static CWK_FIXED_FACTOW_HW(wpww_195m, "wpww-195m", &wpww.common.hw, 4, 1, 0);
static CWK_FIXED_FACTOW_HW(wpww_26m, "wpww-26m", &wpww.common.hw, 30, 1, 0);

static stwuct spwd_cwk_common *sc9863a_wpww_cwks[] = {
	/* addwess base is 0x4035c000 */
	&audio_gate.common,
	&wpww.common,
};

static stwuct cwk_hw_oneceww_data sc9863a_wpww_hws = {
	.hws	= {
		[CWK_AUDIO_GATE]	= &audio_gate.common.hw,
		[CWK_WPWW]		= &wpww.common.hw,
		[CWK_WPWW_390M]		= &wpww_390m.hw,
		[CWK_WPWW_260M]		= &wpww_260m.hw,
		[CWK_WPWW_195M]		= &wpww_195m.hw,
		[CWK_WPWW_26M]		= &wpww_26m.hw,
	},
	.num	= CWK_ANWG_PHY_G5_NUM,
};

static const stwuct spwd_cwk_desc sc9863a_wpww_desc = {
	.cwk_cwks	= sc9863a_wpww_cwks,
	.num_cwk_cwks	= AWWAY_SIZE(sc9863a_wpww_cwks),
	.hw_cwks        = &sc9863a_wpww_hws,
};

static const u64 itabwe_dpww[5] = {4, 1211000000, 1320000000, 1570000000,
				   1866000000};
static SPWD_PWW_HW(dpww0, "dpww0", &dpww0_gate.common.hw, 0x0, 3, itabwe_dpww,
		   f_wpww, 240, 1000, 1000, 0, 0);
static SPWD_PWW_HW(dpww1, "dpww1", &dpww1_gate.common.hw, 0x18, 3, itabwe_dpww,
		   f_wpww, 240, 1000, 1000, 0, 0);

static CWK_FIXED_FACTOW_HW(dpww0_933m, "dpww0-933m", &dpww0.common.hw, 2, 1, 0);
static CWK_FIXED_FACTOW_HW(dpww0_622m3, "dpww0-622m3", &dpww0.common.hw, 3, 1, 0);
static CWK_FIXED_FACTOW_HW(dpww1_400m, "dpww1-400m", &dpww0.common.hw, 4, 1, 0);
static CWK_FIXED_FACTOW_HW(dpww1_266m7, "dpww1-266m7", &dpww0.common.hw, 6, 1, 0);
static CWK_FIXED_FACTOW_HW(dpww1_123m1, "dpww1-123m1", &dpww0.common.hw, 13, 1, 0);
static CWK_FIXED_FACTOW_HW(dpww1_50m, "dpww1-50m", &dpww0.common.hw, 32, 1, 0);

static stwuct spwd_cwk_common *sc9863a_dpww_cwks[] = {
	/* addwess base is 0x40363000 */
	&dpww0.common,
	&dpww1.common,
};

static stwuct cwk_hw_oneceww_data sc9863a_dpww_hws = {
	.hws	= {
		[CWK_DPWW0]		= &dpww0.common.hw,
		[CWK_DPWW1]		= &dpww1.common.hw,
		[CWK_DPWW0_933M]	= &dpww0_933m.hw,
		[CWK_DPWW0_622M3]	= &dpww0_622m3.hw,
		[CWK_DPWW0_400M]	= &dpww1_400m.hw,
		[CWK_DPWW0_266M7]	= &dpww1_266m7.hw,
		[CWK_DPWW0_123M1]	= &dpww1_123m1.hw,
		[CWK_DPWW0_50M]		= &dpww1_50m.hw,

	},
	.num	= CWK_ANWG_PHY_G7_NUM,
};

static const stwuct spwd_cwk_desc sc9863a_dpww_desc = {
	.cwk_cwks	= sc9863a_dpww_cwks,
	.num_cwk_cwks	= AWWAY_SIZE(sc9863a_dpww_cwks),
	.hw_cwks        = &sc9863a_dpww_hws,
};

static CWK_FIXED_FACTOW_FW_NAME(cwk_6m5, "cwk-6m5", "ext-26m", 4, 1, 0);
static CWK_FIXED_FACTOW_FW_NAME(cwk_4m3, "cwk-4m3", "ext-26m", 6, 1, 0);
static CWK_FIXED_FACTOW_FW_NAME(cwk_2m, "cwk-2m", "ext-26m", 13, 1, 0);
static CWK_FIXED_FACTOW_FW_NAME(cwk_250k, "cwk-250k", "ext-26m", 104, 1, 0);
static CWK_FIXED_FACTOW_FW_NAME(wco_25m, "wco-25m", "wco-100m",	4, 1, 0);
static CWK_FIXED_FACTOW_FW_NAME(wco_4m, "wco-4m", "wco-100m", 25, 1, 0);
static CWK_FIXED_FACTOW_FW_NAME(wco_2m, "wco-2m", "wco-100m", 50, 1, 0);

#define SC9863A_MUX_FWAG	\
	(CWK_GET_WATE_NOCACHE | CWK_SET_WATE_NO_WEPAWENT)

static CWK_FIXED_FACTOW_FW_NAME(cwk_13m, "cwk-13m", "ext-26m", 2, 1, 0);
static const stwuct cwk_pawent_data emc_cwk_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_384m.hw  },
	{ .hw = &twpww_512m.hw  },
	{ .hw = &twpww_768m.hw  },
	{ .hw = &twpww.common.hw  },
};
static SPWD_MUX_CWK_DATA(emc_cwk, "emc-cwk", emc_cwk_pawents, 0x220,
			 0, 3, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data aon_apb_pawents[] = {
	{ .hw = &wco_4m.hw  },
	{ .hw = &wco_25m.hw  },
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_96m.hw  },
	{ .fw_name = "wco-100m" },
	{ .hw = &twpww_128m.hw  },
};
static SPWD_COMP_CWK_DATA(aon_apb, "aon-apb", aon_apb_pawents, 0x224,
			  0, 3, 8, 2, 0);

static const stwuct cwk_pawent_data adi_pawents[] = {
	{ .hw = &wco_4m.hw  },
	{ .hw = &wco_25m.hw  },
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_38m4.hw  },
	{ .hw = &twpww_51m2.hw  },
};
static SPWD_MUX_CWK_DATA(adi_cwk, "adi-cwk", adi_pawents, 0x228,
			 0, 3, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data aux_pawents[] = {
	{ .fw_name = "ext-32k" },
	{ .hw = &wpww_26m.hw  },
	{ .fw_name = "ext-26m" },
};
static SPWD_COMP_CWK_DATA(aux0_cwk, "aux0-cwk", aux_pawents, 0x22c,
			  0, 5, 8, 4, 0);
static SPWD_COMP_CWK_DATA(aux1_cwk, "aux1-cwk", aux_pawents, 0x230,
			  0, 5, 8, 4, 0);
static SPWD_COMP_CWK_DATA(aux2_cwk, "aux2-cwk", aux_pawents, 0x234,
			  0, 5, 8, 4, 0);
static SPWD_COMP_CWK_DATA(pwobe_cwk, "pwobe-cwk", aux_pawents, 0x238,
			  0, 5, 8, 4, 0);

static const stwuct cwk_pawent_data pwm_pawents[] = {
	{ .fw_name = "ext-32k" },
	{ .hw = &wpww_26m.hw  },
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_48m.hw  },
};
static SPWD_MUX_CWK_DATA(pwm0_cwk, "pwm0-cwk", pwm_pawents, 0x23c,
			 0, 2, SC9863A_MUX_FWAG);
static SPWD_MUX_CWK_DATA(pwm1_cwk, "pwm1-cwk", pwm_pawents, 0x240,
			 0, 2, SC9863A_MUX_FWAG);
static SPWD_MUX_CWK_DATA(pwm2_cwk, "pwm2-cwk", pwm_pawents, 0x244,
			 0, 2, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data aon_thm_pawents[] = {
	{ .fw_name = "ext-32k" },
	{ .hw = &cwk_250k.hw  },
};
static SPWD_MUX_CWK_DATA(aon_thm_cwk, "aon-thm-cwk", aon_thm_pawents, 0x25c,
			 0, 1, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data audif_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_38m4.hw  },
	{ .hw = &twpww_51m2.hw  },
};
static SPWD_MUX_CWK_DATA(audif_cwk, "audif-cwk", audif_pawents, 0x264,
			 0, 2, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data cpu_dap_pawents[] = {
	{ .hw = &wco_4m.hw  },
	{ .hw = &wco_25m.hw  },
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_76m8.hw  },
	{ .fw_name = "wco-100m" },
	{ .hw = &twpww_128m.hw  },
	{ .hw = &twpww_153m6.hw  },
};
static SPWD_MUX_CWK_DATA(cpu_dap_cwk, "cpu-dap-cwk", cpu_dap_pawents, 0x26c,
			 0, 3, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data cpu_ts_pawents[] = {
	{ .fw_name = "ext-32k" },
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_128m.hw  },
	{ .hw = &twpww_153m6.hw  },
};
static SPWD_MUX_CWK_DATA(cpu_ts_cwk, "cpu-ts-cwk", cpu_ts_pawents, 0x274,
			 0, 2, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data djtag_tck_pawents[] = {
	{ .hw = &wco_4m.hw  },
	{ .fw_name = "ext-26m" },
};
static SPWD_MUX_CWK_DATA(djtag_tck_cwk, "djtag-tck-cwk", djtag_tck_pawents, 0x28c,
			 0, 1, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data emc_wef_pawents[] = {
	{ .hw = &cwk_6m5.hw  },
	{ .hw = &cwk_13m.hw  },
	{ .fw_name = "ext-26m" },
};
static SPWD_MUX_CWK_DATA(emc_wef_cwk, "emc-wef-cwk", emc_wef_pawents, 0x29c,
			 0, 2, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data cssys_pawents[] = {
	{ .hw = &wco_4m.hw  },
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_96m.hw  },
	{ .fw_name = "wco-100m" },
	{ .hw = &twpww_128m.hw  },
	{ .hw = &twpww_153m6.hw  },
	{ .hw = &twpww_384m.hw  },
	{ .hw = &twpww_512m.hw  },
	{ .hw = &mpww2_675m.hw  },
};
static SPWD_COMP_CWK_DATA(cssys_cwk, "cssys-cwk", cssys_pawents, 0x2a0,
			  0, 4, 8, 2, 0);

static const stwuct cwk_pawent_data aon_pmu_pawents[] = {
	{ .fw_name = "ext-32k" },
	{ .hw = &wco_4m.hw  },
	{ .fw_name = "ext-4m" },
};
static SPWD_MUX_CWK_DATA(aon_pmu_cwk, "aon-pmu-cwk", aon_pmu_pawents, 0x2a8,
			 0, 2, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data pmu_26m_pawents[] = {
	{ .hw = &wco_4m.hw  },
	{ .hw = &wco_25m.hw  },
	{ .fw_name = "ext-26m" },
};
static SPWD_MUX_CWK_DATA(pmu_26m_cwk, "26m-pmu-cwk", pmu_26m_pawents, 0x2ac,
			 0, 2, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data aon_tmw_pawents[] = {
	{ .hw = &wco_4m.hw  },
	{ .fw_name = "ext-26m" },
};
static SPWD_MUX_CWK_DATA(aon_tmw_cwk, "aon-tmw-cwk", aon_tmw_pawents, 0x2b0,
			 0, 1, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data powew_cpu_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &wco_25m.hw  },
	{ .fw_name = "wco-100m" },
	{ .hw = &twpww_128m.hw  },
};
static SPWD_MUX_CWK_DATA(powew_cpu_cwk, "powew-cpu-cwk", powew_cpu_pawents, 0x2c4,
			 0, 2, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data ap_axi_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_76m8.hw  },
	{ .hw = &twpww_128m.hw  },
	{ .hw = &twpww_256m.hw  },
};
static SPWD_MUX_CWK_DATA(ap_axi, "ap-axi", ap_axi_pawents, 0x2c8,
			 0, 2, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data sdio_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_307m2.hw  },
	{ .hw = &twpww_384m.hw  },
	{ .hw = &wpww_390m.hw  },
	{ .hw = &dpww1_400m.hw  },
	{ .hw = &wpww_409m6.hw  },
};
static SPWD_MUX_CWK_DATA(sdio0_2x, "sdio0-2x", sdio_pawents, 0x2cc,
			 0, 3, SC9863A_MUX_FWAG);
static SPWD_MUX_CWK_DATA(sdio1_2x, "sdio1-2x", sdio_pawents, 0x2d4,
			 0, 3, SC9863A_MUX_FWAG);
static SPWD_MUX_CWK_DATA(sdio2_2x, "sdio2-2x", sdio_pawents, 0x2dc,
			 0, 3, SC9863A_MUX_FWAG);
static SPWD_MUX_CWK_DATA(emmc_2x, "emmc-2x", sdio_pawents, 0x2e4,
			 0, 3, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data dpu_pawents[] = {
	{ .hw = &twpww_153m6.hw  },
	{ .hw = &twpww_192m.hw  },
	{ .hw = &twpww_256m.hw  },
	{ .hw = &twpww_384m.hw  },
};
static SPWD_MUX_CWK_DATA(dpu_cwk, "dpu", dpu_pawents, 0x2f4,
			 0, 2, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data dpu_dpi_pawents[] = {
	{ .hw = &twpww_128m.hw  },
	{ .hw = &twpww_153m6.hw  },
	{ .hw = &twpww_192m.hw  },
};
static SPWD_COMP_CWK_DATA(dpu_dpi, "dpu-dpi", dpu_dpi_pawents, 0x2f8,
			  0, 2, 8, 4, 0);

static const stwuct cwk_pawent_data otg_wef_pawents[] = {
	{ .hw = &twpww_12m.hw  },
	{ .fw_name = "ext-26m" },
};
static SPWD_MUX_CWK_DATA(otg_wef_cwk, "otg-wef-cwk", otg_wef_pawents, 0x308,
			 0, 1, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data sdphy_apb_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_48m.hw  },
};
static SPWD_MUX_CWK_DATA(sdphy_apb_cwk, "sdphy-apb-cwk", sdphy_apb_pawents, 0x330,
			 0, 1, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data awg_io_apb_pawents[] = {
	{ .hw = &wco_4m.hw  },
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_48m.hw  },
	{ .hw = &twpww_96m.hw  },
};
static SPWD_MUX_CWK_DATA(awg_io_apb_cwk, "awg-io-apb-cwk", awg_io_apb_pawents, 0x33c,
			 0, 1, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data gpu_pawents[] = {
	{ .hw = &twpww_153m6.hw  },
	{ .hw = &twpww_192m.hw  },
	{ .hw = &twpww_256m.hw  },
	{ .hw = &twpww_307m2.hw  },
	{ .hw = &twpww_384m.hw  },
	{ .hw = &twpww_512m.hw  },
	{ .hw = &gpww.common.hw  },
};
static SPWD_COMP_CWK_DATA(gpu_cowe, "gpu-cowe", gpu_pawents, 0x344,
			  0, 3, 8, 2, 0);
static SPWD_COMP_CWK_DATA(gpu_soc, "gpu-soc", gpu_pawents, 0x348,
			  0, 3, 8, 2, 0);

static const stwuct cwk_pawent_data mm_emc_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_384m.hw  },
	{ .hw = &isppww_468m.hw  },
	{ .hw = &twpww_512m.hw  },
};
static SPWD_MUX_CWK_DATA(mm_emc, "mm-emc", mm_emc_pawents, 0x350,
			 0, 2, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data mm_ahb_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_96m.hw  },
	{ .hw = &twpww_128m.hw  },
	{ .hw = &twpww_153m6.hw  },
};
static SPWD_MUX_CWK_DATA(mm_ahb, "mm-ahb", mm_ahb_pawents, 0x354,
			 0, 2, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data bpc_cwk_pawents[] = {
	{ .hw = &twpww_192m.hw  },
	{ .hw = &twpww_307m2.hw  },
	{ .hw = &twpww_384m.hw  },
	{ .hw = &isppww_468m.hw  },
	{ .hw = &dpww0_622m3.hw  },
};
static SPWD_MUX_CWK_DATA(bpc_cwk, "bpc-cwk", bpc_cwk_pawents, 0x358,
			 0, 3, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data dcam_if_pawents[] = {
	{ .hw = &twpww_192m.hw  },
	{ .hw = &twpww_256m.hw  },
	{ .hw = &twpww_307m2.hw  },
	{ .hw = &twpww_384m.hw  },
};
static SPWD_MUX_CWK_DATA(dcam_if_cwk, "dcam-if-cwk", dcam_if_pawents, 0x35c,
			 0, 2, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data isp_pawents[] = {
	{ .hw = &twpww_128m.hw  },
	{ .hw = &twpww_256m.hw  },
	{ .hw = &twpww_307m2.hw  },
	{ .hw = &twpww_384m.hw  },
	{ .hw = &isppww_468m.hw  },
};
static SPWD_MUX_CWK_DATA(isp_cwk, "isp-cwk", isp_pawents, 0x360,
			 0, 3, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data jpg_pawents[] = {
	{ .hw = &twpww_76m8.hw  },
	{ .hw = &twpww_128m.hw  },
	{ .hw = &twpww_256m.hw  },
	{ .hw = &twpww_307m2.hw  },
};
static SPWD_MUX_CWK_DATA(jpg_cwk, "jpg-cwk", jpg_pawents, 0x364,
			 0, 2, SC9863A_MUX_FWAG);
static SPWD_MUX_CWK_DATA(cpp_cwk, "cpp-cwk", jpg_pawents, 0x368,
			 0, 2, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data sensow_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_48m.hw  },
	{ .hw = &twpww_76m8.hw  },
	{ .hw = &twpww_96m.hw  },
};
static SPWD_COMP_CWK_DATA(sensow0_cwk, "sensow0-cwk", sensow_pawents, 0x36c,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(sensow1_cwk, "sensow1-cwk", sensow_pawents, 0x370,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(sensow2_cwk, "sensow2-cwk", sensow_pawents, 0x374,
			  0, 2, 8, 3, 0);

static const stwuct cwk_pawent_data mm_vemc_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_307m2.hw  },
	{ .hw = &twpww_384m.hw  },
	{ .hw = &isppww_468m.hw  },
};
static SPWD_MUX_CWK_DATA(mm_vemc, "mm-vemc", mm_vemc_pawents, 0x378,
			 0, 2, SC9863A_MUX_FWAG);

static SPWD_MUX_CWK_DATA(mm_vahb, "mm-vahb", mm_ahb_pawents, 0x37c,
			 0, 2, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data vsp_pawents[] = {
	{ .hw = &twpww_76m8.hw  },
	{ .hw = &twpww_128m.hw  },
	{ .hw = &twpww_256m.hw  },
	{ .hw = &twpww_307m2.hw  },
	{ .hw = &twpww_384m.hw  },
};
static SPWD_MUX_CWK_DATA(cwk_vsp, "vsp-cwk", vsp_pawents, 0x380,
			 0, 3, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data cowe_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_512m.hw  },
	{ .hw = &twpww_768m.hw  },
	{ .hw = &wpww.common.hw  },
	{ .hw = &dpww0.common.hw  },
	{ .hw = &mpww2.common.hw  },
	{ .hw = &mpww0.common.hw  },
	{ .hw = &mpww1.common.hw  },
};
static SPWD_COMP_CWK_DATA(cowe0_cwk, "cowe0-cwk", cowe_pawents, 0xa20,
			  0, 3, 8, 3, 0);
static SPWD_COMP_CWK_DATA(cowe1_cwk, "cowe1-cwk", cowe_pawents, 0xa24,
			  0, 3, 8, 3, 0);
static SPWD_COMP_CWK_DATA(cowe2_cwk, "cowe2-cwk", cowe_pawents, 0xa28,
			  0, 3, 8, 3, 0);
static SPWD_COMP_CWK_DATA(cowe3_cwk, "cowe3-cwk", cowe_pawents, 0xa2c,
			  0, 3, 8, 3, 0);
static SPWD_COMP_CWK_DATA(cowe4_cwk, "cowe4-cwk", cowe_pawents, 0xa30,
			  0, 3, 8, 3, 0);
static SPWD_COMP_CWK_DATA(cowe5_cwk, "cowe5-cwk", cowe_pawents, 0xa34,
			  0, 3, 8, 3, 0);
static SPWD_COMP_CWK_DATA(cowe6_cwk, "cowe6-cwk", cowe_pawents, 0xa38,
			  0, 3, 8, 3, 0);
static SPWD_COMP_CWK_DATA(cowe7_cwk, "cowe7-cwk", cowe_pawents, 0xa3c,
			  0, 3, 8, 3, 0);
static SPWD_COMP_CWK_DATA(scu_cwk, "scu-cwk", cowe_pawents, 0xa40,
			  0, 3, 8, 3, 0);

static SPWD_DIV_CWK_HW(ace_cwk, "ace-cwk", &scu_cwk.common.hw, 0xa44,
		       8, 3, 0);
static SPWD_DIV_CWK_HW(axi_pewiph_cwk, "axi-pewiph-cwk", &scu_cwk.common.hw, 0xa48,
		       8, 3, 0);
static SPWD_DIV_CWK_HW(axi_acp_cwk, "axi-acp-cwk", &scu_cwk.common.hw, 0xa4c,
		       8, 3, 0);

static const stwuct cwk_pawent_data atb_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_384m.hw  },
	{ .hw = &twpww_512m.hw  },
	{ .hw = &mpww2.common.hw  },
};
static SPWD_COMP_CWK_DATA(atb_cwk, "atb-cwk", atb_pawents, 0xa50,
			  0, 2, 8, 3, 0);
static SPWD_DIV_CWK_HW(debug_apb_cwk, "debug-apb-cwk", &atb_cwk.common.hw, 0xa54,
		       8, 3, 0);

static const stwuct cwk_pawent_data gic_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_153m6.hw  },
	{ .hw = &twpww_384m.hw  },
	{ .hw = &twpww_512m.hw  },
};
static SPWD_COMP_CWK_DATA(gic_cwk, "gic-cwk", gic_pawents, 0xa58,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(pewiph_cwk, "pewiph-cwk", gic_pawents, 0xa5c,
			  0, 2, 8, 3, 0);

static stwuct spwd_cwk_common *sc9863a_aon_cwks[] = {
	/* addwess base is 0x402d0000 */
	&emc_cwk.common,
	&aon_apb.common,
	&adi_cwk.common,
	&aux0_cwk.common,
	&aux1_cwk.common,
	&aux2_cwk.common,
	&pwobe_cwk.common,
	&pwm0_cwk.common,
	&pwm1_cwk.common,
	&pwm2_cwk.common,
	&aon_thm_cwk.common,
	&audif_cwk.common,
	&cpu_dap_cwk.common,
	&cpu_ts_cwk.common,
	&djtag_tck_cwk.common,
	&emc_wef_cwk.common,
	&cssys_cwk.common,
	&aon_pmu_cwk.common,
	&pmu_26m_cwk.common,
	&aon_tmw_cwk.common,
	&powew_cpu_cwk.common,
	&ap_axi.common,
	&sdio0_2x.common,
	&sdio1_2x.common,
	&sdio2_2x.common,
	&emmc_2x.common,
	&dpu_cwk.common,
	&dpu_dpi.common,
	&otg_wef_cwk.common,
	&sdphy_apb_cwk.common,
	&awg_io_apb_cwk.common,
	&gpu_cowe.common,
	&gpu_soc.common,
	&mm_emc.common,
	&mm_ahb.common,
	&bpc_cwk.common,
	&dcam_if_cwk.common,
	&isp_cwk.common,
	&jpg_cwk.common,
	&cpp_cwk.common,
	&sensow0_cwk.common,
	&sensow1_cwk.common,
	&sensow2_cwk.common,
	&mm_vemc.common,
	&mm_vahb.common,
	&cwk_vsp.common,
	&cowe0_cwk.common,
	&cowe1_cwk.common,
	&cowe2_cwk.common,
	&cowe3_cwk.common,
	&cowe4_cwk.common,
	&cowe5_cwk.common,
	&cowe6_cwk.common,
	&cowe7_cwk.common,
	&scu_cwk.common,
	&ace_cwk.common,
	&axi_pewiph_cwk.common,
	&axi_acp_cwk.common,
	&atb_cwk.common,
	&debug_apb_cwk.common,
	&gic_cwk.common,
	&pewiph_cwk.common,
};

static stwuct cwk_hw_oneceww_data sc9863a_aon_cwk_hws = {
	.hws	= {
		[CWK_13M]		= &cwk_13m.hw,
		[CWK_6M5]		= &cwk_6m5.hw,
		[CWK_4M3]		= &cwk_4m3.hw,
		[CWK_2M]		= &cwk_2m.hw,
		[CWK_250K]		= &cwk_250k.hw,
		[CWK_WCO_25M]		= &wco_25m.hw,
		[CWK_WCO_4M]		= &wco_4m.hw,
		[CWK_WCO_2M]		= &wco_2m.hw,
		[CWK_EMC]		= &emc_cwk.common.hw,
		[CWK_AON_APB]		= &aon_apb.common.hw,
		[CWK_ADI]		= &adi_cwk.common.hw,
		[CWK_AUX0]		= &aux0_cwk.common.hw,
		[CWK_AUX1]		= &aux1_cwk.common.hw,
		[CWK_AUX2]		= &aux2_cwk.common.hw,
		[CWK_PWOBE]		= &pwobe_cwk.common.hw,
		[CWK_PWM0]		= &pwm0_cwk.common.hw,
		[CWK_PWM1]		= &pwm1_cwk.common.hw,
		[CWK_PWM2]		= &pwm2_cwk.common.hw,
		[CWK_AON_THM]		= &aon_thm_cwk.common.hw,
		[CWK_AUDIF]		= &audif_cwk.common.hw,
		[CWK_CPU_DAP]		= &cpu_dap_cwk.common.hw,
		[CWK_CPU_TS]		= &cpu_ts_cwk.common.hw,
		[CWK_DJTAG_TCK]		= &djtag_tck_cwk.common.hw,
		[CWK_EMC_WEF]		= &emc_wef_cwk.common.hw,
		[CWK_CSSYS]		= &cssys_cwk.common.hw,
		[CWK_AON_PMU]		= &aon_pmu_cwk.common.hw,
		[CWK_PMU_26M]		= &pmu_26m_cwk.common.hw,
		[CWK_AON_TMW]		= &aon_tmw_cwk.common.hw,
		[CWK_POWEW_CPU]		= &powew_cpu_cwk.common.hw,
		[CWK_AP_AXI]		= &ap_axi.common.hw,
		[CWK_SDIO0_2X]		= &sdio0_2x.common.hw,
		[CWK_SDIO1_2X]		= &sdio1_2x.common.hw,
		[CWK_SDIO2_2X]		= &sdio2_2x.common.hw,
		[CWK_EMMC_2X]		= &emmc_2x.common.hw,
		[CWK_DPU]		= &dpu_cwk.common.hw,
		[CWK_DPU_DPI]		= &dpu_dpi.common.hw,
		[CWK_OTG_WEF]		= &otg_wef_cwk.common.hw,
		[CWK_SDPHY_APB]		= &sdphy_apb_cwk.common.hw,
		[CWK_AWG_IO_APB]	= &awg_io_apb_cwk.common.hw,
		[CWK_GPU_COWE]		= &gpu_cowe.common.hw,
		[CWK_GPU_SOC]		= &gpu_soc.common.hw,
		[CWK_MM_EMC]		= &mm_emc.common.hw,
		[CWK_MM_AHB]		= &mm_ahb.common.hw,
		[CWK_BPC]		= &bpc_cwk.common.hw,
		[CWK_DCAM_IF]		= &dcam_if_cwk.common.hw,
		[CWK_ISP]		= &isp_cwk.common.hw,
		[CWK_JPG]		= &jpg_cwk.common.hw,
		[CWK_CPP]		= &cpp_cwk.common.hw,
		[CWK_SENSOW0]		= &sensow0_cwk.common.hw,
		[CWK_SENSOW1]		= &sensow1_cwk.common.hw,
		[CWK_SENSOW2]		= &sensow2_cwk.common.hw,
		[CWK_MM_VEMC]		= &mm_vemc.common.hw,
		[CWK_MM_VAHB]		= &mm_vahb.common.hw,
		[CWK_VSP]		= &cwk_vsp.common.hw,
		[CWK_COWE0]		= &cowe0_cwk.common.hw,
		[CWK_COWE1]		= &cowe1_cwk.common.hw,
		[CWK_COWE2]		= &cowe2_cwk.common.hw,
		[CWK_COWE3]		= &cowe3_cwk.common.hw,
		[CWK_COWE4]		= &cowe4_cwk.common.hw,
		[CWK_COWE5]		= &cowe5_cwk.common.hw,
		[CWK_COWE6]		= &cowe6_cwk.common.hw,
		[CWK_COWE7]		= &cowe7_cwk.common.hw,
		[CWK_SCU]		= &scu_cwk.common.hw,
		[CWK_ACE]		= &ace_cwk.common.hw,
		[CWK_AXI_PEWIPH]	= &axi_pewiph_cwk.common.hw,
		[CWK_AXI_ACP]		= &axi_acp_cwk.common.hw,
		[CWK_ATB]		= &atb_cwk.common.hw,
		[CWK_DEBUG_APB]		= &debug_apb_cwk.common.hw,
		[CWK_GIC]		= &gic_cwk.common.hw,
		[CWK_PEWIPH]		= &pewiph_cwk.common.hw,
	},
	.num	= CWK_AON_CWK_NUM,
};

static const stwuct spwd_cwk_desc sc9863a_aon_cwk_desc = {
	.cwk_cwks	= sc9863a_aon_cwks,
	.num_cwk_cwks	= AWWAY_SIZE(sc9863a_aon_cwks),
	.hw_cwks	= &sc9863a_aon_cwk_hws,
};

static const stwuct cwk_pawent_data ap_apb_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_64m.hw  },
	{ .hw = &twpww_96m.hw  },
	{ .hw = &twpww_128m.hw  },
};
static SPWD_MUX_CWK_DATA(ap_apb, "ap-apb", ap_apb_pawents, 0x20,
			 0, 2, SC9863A_MUX_FWAG);

static const stwuct cwk_pawent_data ap_ce_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_256m.hw  },
};
static SPWD_COMP_CWK_DATA(ap_ce, "ap-ce", ap_ce_pawents, 0x24,
			  0, 1, 8, 3, 0);

static const stwuct cwk_pawent_data nandc_ecc_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_256m.hw  },
	{ .hw = &twpww_307m2.hw  },
};
static SPWD_COMP_CWK_DATA(nandc_ecc, "nandc-ecc", nandc_ecc_pawents, 0x28,
			  0, 2, 8, 3, 0);

static const stwuct cwk_pawent_data nandc_26m_pawents[] = {
	{ .fw_name = "ext-32k" },
	{ .fw_name = "ext-26m" },
};
static SPWD_MUX_CWK_DATA(nandc_26m, "nandc-26m", nandc_26m_pawents, 0x2c,
			 0, 1, SC9863A_MUX_FWAG);
static SPWD_MUX_CWK_DATA(emmc_32k, "emmc-32k", nandc_26m_pawents, 0x30,
			 0, 1, SC9863A_MUX_FWAG);
static SPWD_MUX_CWK_DATA(sdio0_32k, "sdio0-32k", nandc_26m_pawents, 0x34,
			 0, 1, SC9863A_MUX_FWAG);
static SPWD_MUX_CWK_DATA(sdio1_32k, "sdio1-32k", nandc_26m_pawents, 0x38,
			 0, 1, SC9863A_MUX_FWAG);
static SPWD_MUX_CWK_DATA(sdio2_32k, "sdio2-32k", nandc_26m_pawents, 0x3c,
			 0, 1, SC9863A_MUX_FWAG);

static SPWD_GATE_CWK_HW(otg_utmi, "otg-utmi", &aon_apb.common.hw, 0x40,
			BIT(16), 0, 0);

static const stwuct cwk_pawent_data ap_uawt_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_48m.hw  },
	{ .hw = &twpww_51m2.hw  },
	{ .hw = &twpww_96m.hw  },
};
static SPWD_COMP_CWK_DATA(ap_uawt0,	"ap-uawt0",	ap_uawt_pawents, 0x44,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(ap_uawt1,	"ap-uawt1",	ap_uawt_pawents, 0x48,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(ap_uawt2,	"ap-uawt2",	ap_uawt_pawents, 0x4c,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(ap_uawt3,	"ap-uawt3",	ap_uawt_pawents, 0x50,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(ap_uawt4,	"ap-uawt4",	ap_uawt_pawents, 0x54,
			  0, 2, 8, 3, 0);

static const stwuct cwk_pawent_data i2c_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_48m.hw  },
	{ .hw = &twpww_51m2.hw  },
	{ .hw = &twpww_153m6.hw  },
};
static SPWD_COMP_CWK_DATA(ap_i2c0, "ap-i2c0", i2c_pawents, 0x58,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(ap_i2c1, "ap-i2c1", i2c_pawents, 0x5c,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(ap_i2c2, "ap-i2c2", i2c_pawents, 0x60,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(ap_i2c3, "ap-i2c3", i2c_pawents, 0x64,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(ap_i2c4, "ap-i2c4", i2c_pawents, 0x68,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(ap_i2c5, "ap-i2c5", i2c_pawents, 0x6c,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(ap_i2c6, "ap-i2c6", i2c_pawents, 0x70,
			  0, 2, 8, 3, 0);

static const stwuct cwk_pawent_data spi_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_128m.hw  },
	{ .hw = &twpww_153m6.hw  },
	{ .hw = &twpww_192m.hw  },
};
static SPWD_COMP_CWK_DATA(ap_spi0, "ap-spi0", spi_pawents, 0x74,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(ap_spi1, "ap-spi1", spi_pawents, 0x78,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(ap_spi2, "ap-spi2", spi_pawents, 0x7c,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(ap_spi3, "ap-spi3", spi_pawents, 0x80,
			  0, 2, 8, 3, 0);

static const stwuct cwk_pawent_data iis_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_128m.hw  },
	{ .hw = &twpww_153m6.hw  },
};
static SPWD_COMP_CWK_DATA(ap_iis0, "ap-iis0", iis_pawents, 0x84,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(ap_iis1, "ap-iis1", iis_pawents, 0x88,
			  0, 2, 8, 3, 0);
static SPWD_COMP_CWK_DATA(ap_iis2, "ap-iis2", iis_pawents, 0x8c,
			  0, 2, 8, 3, 0);

static const stwuct cwk_pawent_data sim0_pawents[] = {
	{ .fw_name = "ext-26m" },
	{ .hw = &twpww_51m2.hw  },
	{ .hw = &twpww_64m.hw  },
	{ .hw = &twpww_96m.hw  },
	{ .hw = &twpww_128m.hw  },
};
static SPWD_COMP_CWK_DATA(sim0, "sim0", sim0_pawents, 0x90,
			  0, 3, 8, 3, 0);

static const stwuct cwk_pawent_data sim0_32k_pawents[] = {
	{ .fw_name = "ext-32k" },
	{ .fw_name = "ext-26m" },
};
static SPWD_MUX_CWK_DATA(sim0_32k, "sim0-32k", sim0_32k_pawents, 0x94,
			 0, 1, SC9863A_MUX_FWAG);

static stwuct spwd_cwk_common *sc9863a_ap_cwks[] = {
	/* addwess base is 0x21500000 */
	&ap_apb.common,
	&ap_ce.common,
	&nandc_ecc.common,
	&nandc_26m.common,
	&emmc_32k.common,
	&sdio0_32k.common,
	&sdio1_32k.common,
	&sdio2_32k.common,
	&otg_utmi.common,
	&ap_uawt0.common,
	&ap_uawt1.common,
	&ap_uawt2.common,
	&ap_uawt3.common,
	&ap_uawt4.common,
	&ap_i2c0.common,
	&ap_i2c1.common,
	&ap_i2c2.common,
	&ap_i2c3.common,
	&ap_i2c4.common,
	&ap_i2c5.common,
	&ap_i2c6.common,
	&ap_spi0.common,
	&ap_spi1.common,
	&ap_spi2.common,
	&ap_spi3.common,
	&ap_iis0.common,
	&ap_iis1.common,
	&ap_iis2.common,
	&sim0.common,
	&sim0_32k.common,
};

static stwuct cwk_hw_oneceww_data sc9863a_ap_cwk_hws = {
	.hws	= {
		[CWK_AP_APB]	= &ap_apb.common.hw,
		[CWK_AP_CE]	= &ap_ce.common.hw,
		[CWK_NANDC_ECC]	= &nandc_ecc.common.hw,
		[CWK_NANDC_26M]	= &nandc_26m.common.hw,
		[CWK_EMMC_32K]	= &emmc_32k.common.hw,
		[CWK_SDIO0_32K]	= &sdio0_32k.common.hw,
		[CWK_SDIO1_32K]	= &sdio1_32k.common.hw,
		[CWK_SDIO2_32K]	= &sdio2_32k.common.hw,
		[CWK_OTG_UTMI]	= &otg_utmi.common.hw,
		[CWK_AP_UAWT0]	= &ap_uawt0.common.hw,
		[CWK_AP_UAWT1]	= &ap_uawt1.common.hw,
		[CWK_AP_UAWT2]	= &ap_uawt2.common.hw,
		[CWK_AP_UAWT3]	= &ap_uawt3.common.hw,
		[CWK_AP_UAWT4]	= &ap_uawt4.common.hw,
		[CWK_AP_I2C0]	= &ap_i2c0.common.hw,
		[CWK_AP_I2C1]	= &ap_i2c1.common.hw,
		[CWK_AP_I2C2]	= &ap_i2c2.common.hw,
		[CWK_AP_I2C3]	= &ap_i2c3.common.hw,
		[CWK_AP_I2C4]	= &ap_i2c4.common.hw,
		[CWK_AP_I2C5]	= &ap_i2c5.common.hw,
		[CWK_AP_I2C6]	= &ap_i2c6.common.hw,
		[CWK_AP_SPI0]	= &ap_spi0.common.hw,
		[CWK_AP_SPI1]	= &ap_spi1.common.hw,
		[CWK_AP_SPI2]	= &ap_spi2.common.hw,
		[CWK_AP_SPI3]	= &ap_spi3.common.hw,
		[CWK_AP_IIS0]	= &ap_iis0.common.hw,
		[CWK_AP_IIS1]	= &ap_iis1.common.hw,
		[CWK_AP_IIS2]	= &ap_iis2.common.hw,
		[CWK_SIM0]	= &sim0.common.hw,
		[CWK_SIM0_32K]	= &sim0_32k.common.hw,
	},
	.num	= CWK_AP_CWK_NUM,
};

static const stwuct spwd_cwk_desc sc9863a_ap_cwk_desc = {
	.cwk_cwks	= sc9863a_ap_cwks,
	.num_cwk_cwks	= AWWAY_SIZE(sc9863a_ap_cwks),
	.hw_cwks	= &sc9863a_ap_cwk_hws,
};

static SPWD_SC_GATE_CWK_HW(otg_eb, "otg-eb", &ap_axi.common.hw, 0x0, 0x1000,
			   BIT(4), 0, 0);
static SPWD_SC_GATE_CWK_HW(dma_eb, "dma-eb", &ap_axi.common.hw, 0x0, 0x1000,
			   BIT(5), 0, 0);
static SPWD_SC_GATE_CWK_HW(ce_eb, "ce-eb", &ap_axi.common.hw, 0x0, 0x1000,
			   BIT(6), 0, 0);
static SPWD_SC_GATE_CWK_HW(nandc_eb, "nandc-eb", &ap_axi.common.hw, 0x0, 0x1000,
			   BIT(7), 0, 0);
static SPWD_SC_GATE_CWK_HW(sdio0_eb, "sdio0-eb", &ap_axi.common.hw, 0x0, 0x1000,
			   BIT(8), 0, 0);
static SPWD_SC_GATE_CWK_HW(sdio1_eb, "sdio1-eb", &ap_axi.common.hw, 0x0, 0x1000,
			   BIT(9), 0, 0);
static SPWD_SC_GATE_CWK_HW(sdio2_eb, "sdio2-eb", &ap_axi.common.hw, 0x0, 0x1000,
			   BIT(10), 0, 0);
static SPWD_SC_GATE_CWK_HW(emmc_eb, "emmc-eb", &ap_axi.common.hw, 0x0, 0x1000,
			   BIT(11), 0, 0);
static SPWD_SC_GATE_CWK_HW(emmc_32k_eb, "emmc-32k-eb", &ap_axi.common.hw, 0x0,
			   0x1000, BIT(27), 0, 0);
static SPWD_SC_GATE_CWK_HW(sdio0_32k_eb, "sdio0-32k-eb", &ap_axi.common.hw, 0x0,
			   0x1000, BIT(28), 0, 0);
static SPWD_SC_GATE_CWK_HW(sdio1_32k_eb, "sdio1-32k-eb", &ap_axi.common.hw, 0x0,
			   0x1000, BIT(29), 0, 0);
static SPWD_SC_GATE_CWK_HW(sdio2_32k_eb, "sdio2-32k-eb", &ap_axi.common.hw, 0x0,
			   0x1000, BIT(30), 0, 0);
static SPWD_SC_GATE_CWK_HW(nandc_26m_eb, "nandc-26m-eb", &ap_axi.common.hw, 0x0,
			   0x1000, BIT(31), 0, 0);
static SPWD_SC_GATE_CWK_HW(dma_eb2, "dma-eb2", &ap_axi.common.hw, 0x18,
			   0x1000, BIT(0), 0, 0);
static SPWD_SC_GATE_CWK_HW(ce_eb2, "ce-eb2", &ap_axi.common.hw, 0x18,
			   0x1000, BIT(1), 0, 0);

static stwuct spwd_cwk_common *sc9863a_apahb_gate_cwks[] = {
	/* addwess base is 0x20e00000 */
	&otg_eb.common,
	&dma_eb.common,
	&ce_eb.common,
	&nandc_eb.common,
	&sdio0_eb.common,
	&sdio1_eb.common,
	&sdio2_eb.common,
	&emmc_eb.common,
	&emmc_32k_eb.common,
	&sdio0_32k_eb.common,
	&sdio1_32k_eb.common,
	&sdio2_32k_eb.common,
	&nandc_26m_eb.common,
	&dma_eb2.common,
	&ce_eb2.common,
};

static stwuct cwk_hw_oneceww_data sc9863a_apahb_gate_hws = {
	.hws	= {
		[CWK_OTG_EB]		= &otg_eb.common.hw,
		[CWK_DMA_EB]		= &dma_eb.common.hw,
		[CWK_CE_EB]		= &ce_eb.common.hw,
		[CWK_NANDC_EB]		= &nandc_eb.common.hw,
		[CWK_SDIO0_EB]		= &sdio0_eb.common.hw,
		[CWK_SDIO1_EB]		= &sdio1_eb.common.hw,
		[CWK_SDIO2_EB]		= &sdio2_eb.common.hw,
		[CWK_EMMC_EB]		= &emmc_eb.common.hw,
		[CWK_EMMC_32K_EB]	= &emmc_32k_eb.common.hw,
		[CWK_SDIO0_32K_EB]	= &sdio0_32k_eb.common.hw,
		[CWK_SDIO1_32K_EB]	= &sdio1_32k_eb.common.hw,
		[CWK_SDIO2_32K_EB]	= &sdio2_32k_eb.common.hw,
		[CWK_NANDC_26M_EB]	= &nandc_26m_eb.common.hw,
		[CWK_DMA_EB2]		= &dma_eb2.common.hw,
		[CWK_CE_EB2]		= &ce_eb2.common.hw,
	},
	.num	= CWK_AP_AHB_GATE_NUM,
};

static const stwuct spwd_cwk_desc sc9863a_apahb_gate_desc = {
	.cwk_cwks	= sc9863a_apahb_gate_cwks,
	.num_cwk_cwks	= AWWAY_SIZE(sc9863a_apahb_gate_cwks),
	.hw_cwks	= &sc9863a_apahb_gate_hws,
};

/* aon gate cwocks */
static SPWD_SC_GATE_CWK_HW(gpio_eb, "gpio-eb",	&aon_apb.common.hw,
			   0x0, 0x1000, BIT(3), 0, 0);
static SPWD_SC_GATE_CWK_HW(pwm0_eb,	"pwm0-eb",	&aon_apb.common.hw,
			   0x0, 0x1000, BIT(4), 0, 0);
static SPWD_SC_GATE_CWK_HW(pwm1_eb,	"pwm1-eb",	&aon_apb.common.hw,
			   0x0, 0x1000, BIT(5), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(pwm2_eb,	"pwm2-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(6), 0, 0);
static SPWD_SC_GATE_CWK_HW(pwm3_eb,	"pwm3-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(7), 0, 0);
static SPWD_SC_GATE_CWK_HW(kpd_eb,	"kpd-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(8), 0, 0);
static SPWD_SC_GATE_CWK_HW(aon_syst_eb,	"aon-syst-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(9), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(ap_syst_eb,	"ap-syst-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(10), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(aon_tmw_eb,	"aon-tmw-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(11), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(efuse_eb,	"efuse-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(13), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(eic_eb,	"eic-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(14), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(intc_eb,	"intc-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(15), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(adi_eb,	"adi-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(16), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(audif_eb,	"audif-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(17), 0, 0);
static SPWD_SC_GATE_CWK_HW(aud_eb,	"aud-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(18), 0, 0);
static SPWD_SC_GATE_CWK_HW(vbc_eb,	"vbc-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(19), 0, 0);
static SPWD_SC_GATE_CWK_HW(pin_eb,	"pin-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(20), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(ap_wdg_eb,	"ap-wdg-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(24), 0, 0);
static SPWD_SC_GATE_CWK_HW(mm_eb,	"mm-eb",	&aon_apb.common.hw, 0x0,
			   0x1000, BIT(25), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(aon_apb_ckg_eb, "aon-apb-ckg-eb", &aon_apb.common.hw,
			   0x0, 0x1000, BIT(26), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(ca53_ts0_eb, "ca53-ts0-eb",	&aon_apb.common.hw,
			   0x0, 0x1000, BIT(28), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(ca53_ts1_eb, "ca53-ts1-eb",	&aon_apb.common.hw,
			   0x0, 0x1000, BIT(29), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(ca53_dap_eb, "ca53-dap-eb",	&aon_apb.common.hw,
			   0x0, 0x1000, BIT(30), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(pmu_eb,	"pmu-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(0), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(thm_eb,	"thm-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(1), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(aux0_eb,	"aux0-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(2), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(aux1_eb,	"aux1-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(3), 0, 0);
static SPWD_SC_GATE_CWK_HW(aux2_eb,	"aux2-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(4), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(pwobe_eb,	"pwobe-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(5), 0, 0);
static SPWD_SC_GATE_CWK_HW(emc_wef_eb,	"emc-wef-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(7), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(ca53_wdg_eb,	"ca53-wdg-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(8), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(ap_tmw1_eb,	"ap-tmw1-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(9), 0, 0);
static SPWD_SC_GATE_CWK_HW(ap_tmw2_eb,	"ap-tmw2-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(10), 0, 0);
static SPWD_SC_GATE_CWK_HW(disp_emc_eb,	"disp-emc-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(11), 0, 0);
static SPWD_SC_GATE_CWK_HW(zip_emc_eb,	"zip-emc-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(12), 0, 0);
static SPWD_SC_GATE_CWK_HW(gsp_emc_eb,	"gsp-emc-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(13), 0, 0);
static SPWD_SC_GATE_CWK_HW(mm_vsp_eb,	"mm-vsp-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(14), 0, 0);
static SPWD_SC_GATE_CWK_HW(mdaw_eb,	"mdaw-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(17), 0, 0);
static SPWD_SC_GATE_CWK_HW(wtc4m0_caw_eb, "wtc4m0-caw-eb", &aon_apb.common.hw,
			   0x4, 0x1000, BIT(18), 0, 0);
static SPWD_SC_GATE_CWK_HW(wtc4m1_caw_eb, "wtc4m1-caw-eb", &aon_apb.common.hw,
			   0x4, 0x1000, BIT(19), 0, 0);
static SPWD_SC_GATE_CWK_HW(djtag_eb,	"djtag-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(20), 0, 0);
static SPWD_SC_GATE_CWK_HW(mbox_eb,	"mbox-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(21), 0, 0);
static SPWD_SC_GATE_CWK_HW(aon_dma_eb,	"aon-dma-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(22), 0, 0);
static SPWD_SC_GATE_CWK_HW(aon_apb_def_eb, "aon-apb-def-eb", &aon_apb.common.hw,
			   0x4, 0x1000, BIT(25), 0, 0);
static SPWD_SC_GATE_CWK_HW(ca5_ts0_eb,	"ca5-ts0-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(26), 0, 0);
static SPWD_SC_GATE_CWK_HW(dbg_eb,	"dbg-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(28), 0, 0);
static SPWD_SC_GATE_CWK_HW(dbg_emc_eb,	"dbg-emc-eb",	&aon_apb.common.hw,
			   0x4, 0x1000, BIT(29), 0, 0);
static SPWD_SC_GATE_CWK_HW(cwoss_twig_eb, "cwoss-twig-eb", &aon_apb.common.hw,
			   0x4, 0x1000, BIT(30), 0, 0);
static SPWD_SC_GATE_CWK_HW(sewdes_dphy_eb, "sewdes-dphy-eb", &aon_apb.common.hw,
			   0x4, 0x1000, BIT(31), 0, 0);
static SPWD_SC_GATE_CWK_HW(awch_wtc_eb,	"awch-wtc-eb",	&aon_apb.common.hw,
			   0x10, 0x1000, BIT(0), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(kpd_wtc_eb,	"kpd-wtc-eb",	&aon_apb.common.hw,
			   0x10, 0x1000, BIT(1), 0, 0);
static SPWD_SC_GATE_CWK_HW(aon_syst_wtc_eb, "aon-syst-wtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(2), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(ap_syst_wtc_eb, "ap-syst-wtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(3), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(aon_tmw_wtc_eb, "aon-tmw-wtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(4), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(ap_tmw0_wtc_eb, "ap-tmw0-wtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(5), 0, 0);
static SPWD_SC_GATE_CWK_HW(eic_wtc_eb, "eic-wtc-eb",	&aon_apb.common.hw,
			   0x10, 0x1000, BIT(6), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(eic_wtcdv5_eb, "eic-wtcdv5-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(7), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(ap_wdg_wtc_eb, "ap-wdg-wtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(8), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(ca53_wdg_wtc_eb, "ca53-wdg-wtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(9), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(thm_wtc_eb, "thm-wtc-eb",	&aon_apb.common.hw,
			   0x10, 0x1000, BIT(10), 0, 0);
static SPWD_SC_GATE_CWK_HW(athma_wtc_eb, "athma-wtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(11), 0, 0);
static SPWD_SC_GATE_CWK_HW(gthma_wtc_eb, "gthma-wtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(12), 0, 0);
static SPWD_SC_GATE_CWK_HW(athma_wtc_a_eb, "athma-wtc-a-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(13), 0, 0);
static SPWD_SC_GATE_CWK_HW(gthma_wtc_a_eb, "gthma-wtc-a-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(14), 0, 0);
static SPWD_SC_GATE_CWK_HW(ap_tmw1_wtc_eb, "ap-tmw1-wtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(15), 0, 0);
static SPWD_SC_GATE_CWK_HW(ap_tmw2_wtc_eb, "ap-tmw2-wtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(16), 0, 0);
static SPWD_SC_GATE_CWK_HW(dxco_wc_wtc_eb, "dxco-wc-wtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(17), 0, 0);
static SPWD_SC_GATE_CWK_HW(bb_caw_wtc_eb, "bb-caw-wtc-eb", &aon_apb.common.hw,
			   0x10, 0x1000, BIT(18), 0, 0);
static SPWD_SC_GATE_CWK_HW(gpu_eb, "gpu-eb", &aon_apb.common.hw, 0x50,
			   0x1000, BIT(0), 0, 0);
static SPWD_SC_GATE_CWK_HW(disp_eb, "disp-eb", &aon_apb.common.hw, 0x50,
			   0x1000, BIT(2), 0, 0);
static SPWD_SC_GATE_CWK_HW(mm_emc_eb, "mm-emc-eb", &aon_apb.common.hw, 0x50,
			   0x1000, BIT(3), 0, 0);
static SPWD_SC_GATE_CWK_HW(powew_cpu_eb, "powew-cpu-eb", &aon_apb.common.hw, 0x50,
			   0x1000, BIT(10), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(hw_i2c_eb, "hw-i2c-eb", &aon_apb.common.hw, 0x50,
			   0x1000, BIT(11), 0, 0);
static SPWD_SC_GATE_CWK_HW(mm_vsp_emc_eb, "mm-vsp-emc-eb", &aon_apb.common.hw, 0x50,
			   0x1000, BIT(14), 0, 0);
static SPWD_SC_GATE_CWK_HW(vsp_eb, "vsp-eb", &aon_apb.common.hw, 0x50,
			   0x1000, BIT(16), 0, 0);
static SPWD_SC_GATE_CWK_HW(cssys_eb, "cssys-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(4), 0, 0);
static SPWD_SC_GATE_CWK_HW(dmc_eb, "dmc-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(5), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(wosc_eb, "wosc-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(7), 0, 0);
static SPWD_SC_GATE_CWK_HW(s_d_cfg_eb, "s-d-cfg-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(8), 0, 0);
static SPWD_SC_GATE_CWK_HW(s_d_wef_eb, "s-d-wef-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(9), 0, 0);
static SPWD_SC_GATE_CWK_HW(b_dma_eb, "b-dma-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(10), 0, 0);
static SPWD_SC_GATE_CWK_HW(anwg_eb, "anwg-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(11), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(anwg_apb_eb, "anwg-apb-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(13), 0, 0);
static SPWD_SC_GATE_CWK_HW(bsmtmw_eb, "bsmtmw-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(14), 0, 0);
static SPWD_SC_GATE_CWK_HW(ap_axi_eb, "ap-axi-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(15), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(ap_intc0_eb, "ap-intc0-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(16), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(ap_intc1_eb, "ap-intc1-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(17), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(ap_intc2_eb, "ap-intc2-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(18), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(ap_intc3_eb, "ap-intc3-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(19), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(ap_intc4_eb, "ap-intc4-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(20), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(ap_intc5_eb, "ap-intc5-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(21), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_HW(scc_eb, "scc-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(22), 0, 0);
static SPWD_SC_GATE_CWK_HW(dphy_cfg_eb, "dphy-cfg-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(23), 0, 0);
static SPWD_SC_GATE_CWK_HW(dphy_wef_eb, "dphy-wef-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(24), 0, 0);
static SPWD_SC_GATE_CWK_HW(cphy_cfg_eb, "cphy-cfg-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(25), 0, 0);
static SPWD_SC_GATE_CWK_HW(otg_wef_eb, "otg-wef-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(26), 0, 0);
static SPWD_SC_GATE_CWK_HW(sewdes_eb, "sewdes-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(27), 0, 0);
static SPWD_SC_GATE_CWK_HW(aon_ap_emc_eb, "aon-ap-emc-eb", &aon_apb.common.hw, 0xb0,
			   0x1000, BIT(28), 0, 0);
static stwuct spwd_cwk_common *sc9863a_aonapb_gate_cwks[] = {
	/* addwess base is 0x402e0000 */
	&gpio_eb.common,
	&pwm0_eb.common,
	&pwm1_eb.common,
	&pwm2_eb.common,
	&pwm3_eb.common,
	&kpd_eb.common,
	&aon_syst_eb.common,
	&ap_syst_eb.common,
	&aon_tmw_eb.common,
	&efuse_eb.common,
	&eic_eb.common,
	&intc_eb.common,
	&adi_eb.common,
	&audif_eb.common,
	&aud_eb.common,
	&vbc_eb.common,
	&pin_eb.common,
	&ap_wdg_eb.common,
	&mm_eb.common,
	&aon_apb_ckg_eb.common,
	&ca53_ts0_eb.common,
	&ca53_ts1_eb.common,
	&ca53_dap_eb.common,
	&pmu_eb.common,
	&thm_eb.common,
	&aux0_eb.common,
	&aux1_eb.common,
	&aux2_eb.common,
	&pwobe_eb.common,
	&emc_wef_eb.common,
	&ca53_wdg_eb.common,
	&ap_tmw1_eb.common,
	&ap_tmw2_eb.common,
	&disp_emc_eb.common,
	&zip_emc_eb.common,
	&gsp_emc_eb.common,
	&mm_vsp_eb.common,
	&mdaw_eb.common,
	&wtc4m0_caw_eb.common,
	&wtc4m1_caw_eb.common,
	&djtag_eb.common,
	&mbox_eb.common,
	&aon_dma_eb.common,
	&aon_apb_def_eb.common,
	&ca5_ts0_eb.common,
	&dbg_eb.common,
	&dbg_emc_eb.common,
	&cwoss_twig_eb.common,
	&sewdes_dphy_eb.common,
	&awch_wtc_eb.common,
	&kpd_wtc_eb.common,
	&aon_syst_wtc_eb.common,
	&ap_syst_wtc_eb.common,
	&aon_tmw_wtc_eb.common,
	&ap_tmw0_wtc_eb.common,
	&eic_wtc_eb.common,
	&eic_wtcdv5_eb.common,
	&ap_wdg_wtc_eb.common,
	&ca53_wdg_wtc_eb.common,
	&thm_wtc_eb.common,
	&athma_wtc_eb.common,
	&gthma_wtc_eb.common,
	&athma_wtc_a_eb.common,
	&gthma_wtc_a_eb.common,
	&ap_tmw1_wtc_eb.common,
	&ap_tmw2_wtc_eb.common,
	&dxco_wc_wtc_eb.common,
	&bb_caw_wtc_eb.common,
	&gpu_eb.common,
	&disp_eb.common,
	&mm_emc_eb.common,
	&powew_cpu_eb.common,
	&hw_i2c_eb.common,
	&mm_vsp_emc_eb.common,
	&vsp_eb.common,
	&cssys_eb.common,
	&dmc_eb.common,
	&wosc_eb.common,
	&s_d_cfg_eb.common,
	&s_d_wef_eb.common,
	&b_dma_eb.common,
	&anwg_eb.common,
	&anwg_apb_eb.common,
	&bsmtmw_eb.common,
	&ap_axi_eb.common,
	&ap_intc0_eb.common,
	&ap_intc1_eb.common,
	&ap_intc2_eb.common,
	&ap_intc3_eb.common,
	&ap_intc4_eb.common,
	&ap_intc5_eb.common,
	&scc_eb.common,
	&dphy_cfg_eb.common,
	&dphy_wef_eb.common,
	&cphy_cfg_eb.common,
	&otg_wef_eb.common,
	&sewdes_eb.common,
	&aon_ap_emc_eb.common,
};

static stwuct cwk_hw_oneceww_data sc9863a_aonapb_gate_hws = {
	.hws	= {
		[CWK_GPIO_EB]		= &gpio_eb.common.hw,
		[CWK_PWM0_EB]		= &pwm0_eb.common.hw,
		[CWK_PWM1_EB]		= &pwm1_eb.common.hw,
		[CWK_PWM2_EB]		= &pwm2_eb.common.hw,
		[CWK_PWM3_EB]		= &pwm3_eb.common.hw,
		[CWK_KPD_EB]		= &kpd_eb.common.hw,
		[CWK_AON_SYST_EB]	= &aon_syst_eb.common.hw,
		[CWK_AP_SYST_EB]	= &ap_syst_eb.common.hw,
		[CWK_AON_TMW_EB]	= &aon_tmw_eb.common.hw,
		[CWK_EFUSE_EB]		= &efuse_eb.common.hw,
		[CWK_EIC_EB]		= &eic_eb.common.hw,
		[CWK_INTC_EB]		= &intc_eb.common.hw,
		[CWK_ADI_EB]		= &adi_eb.common.hw,
		[CWK_AUDIF_EB]		= &audif_eb.common.hw,
		[CWK_AUD_EB]		= &aud_eb.common.hw,
		[CWK_VBC_EB]		= &vbc_eb.common.hw,
		[CWK_PIN_EB]		= &pin_eb.common.hw,
		[CWK_AP_WDG_EB]		= &ap_wdg_eb.common.hw,
		[CWK_MM_EB]		= &mm_eb.common.hw,
		[CWK_AON_APB_CKG_EB]	= &aon_apb_ckg_eb.common.hw,
		[CWK_CA53_TS0_EB]	= &ca53_ts0_eb.common.hw,
		[CWK_CA53_TS1_EB]	= &ca53_ts1_eb.common.hw,
		[CWK_CS53_DAP_EB]	= &ca53_dap_eb.common.hw,
		[CWK_PMU_EB]		= &pmu_eb.common.hw,
		[CWK_THM_EB]		= &thm_eb.common.hw,
		[CWK_AUX0_EB]		= &aux0_eb.common.hw,
		[CWK_AUX1_EB]		= &aux1_eb.common.hw,
		[CWK_AUX2_EB]		= &aux2_eb.common.hw,
		[CWK_PWOBE_EB]		= &pwobe_eb.common.hw,
		[CWK_EMC_WEF_EB]	= &emc_wef_eb.common.hw,
		[CWK_CA53_WDG_EB]	= &ca53_wdg_eb.common.hw,
		[CWK_AP_TMW1_EB]	= &ap_tmw1_eb.common.hw,
		[CWK_AP_TMW2_EB]	= &ap_tmw2_eb.common.hw,
		[CWK_DISP_EMC_EB]	= &disp_emc_eb.common.hw,
		[CWK_ZIP_EMC_EB]	= &zip_emc_eb.common.hw,
		[CWK_GSP_EMC_EB]	= &gsp_emc_eb.common.hw,
		[CWK_MM_VSP_EB]		= &mm_vsp_eb.common.hw,
		[CWK_MDAW_EB]		= &mdaw_eb.common.hw,
		[CWK_WTC4M0_CAW_EB]	= &wtc4m0_caw_eb.common.hw,
		[CWK_WTC4M1_CAW_EB]	= &wtc4m1_caw_eb.common.hw,
		[CWK_DJTAG_EB]		= &djtag_eb.common.hw,
		[CWK_MBOX_EB]		= &mbox_eb.common.hw,
		[CWK_AON_DMA_EB]	= &aon_dma_eb.common.hw,
		[CWK_AON_APB_DEF_EB]	= &aon_apb_def_eb.common.hw,
		[CWK_CA5_TS0_EB]	= &ca5_ts0_eb.common.hw,
		[CWK_DBG_EB]		= &dbg_eb.common.hw,
		[CWK_DBG_EMC_EB]	= &dbg_emc_eb.common.hw,
		[CWK_CWOSS_TWIG_EB]	= &cwoss_twig_eb.common.hw,
		[CWK_SEWDES_DPHY_EB]	= &sewdes_dphy_eb.common.hw,
		[CWK_AWCH_WTC_EB]	= &awch_wtc_eb.common.hw,
		[CWK_KPD_WTC_EB]	= &kpd_wtc_eb.common.hw,
		[CWK_AON_SYST_WTC_EB]	= &aon_syst_wtc_eb.common.hw,
		[CWK_AP_SYST_WTC_EB]	= &ap_syst_wtc_eb.common.hw,
		[CWK_AON_TMW_WTC_EB]	= &aon_tmw_wtc_eb.common.hw,
		[CWK_AP_TMW0_WTC_EB]	= &ap_tmw0_wtc_eb.common.hw,
		[CWK_EIC_WTC_EB]	= &eic_wtc_eb.common.hw,
		[CWK_EIC_WTCDV5_EB]	= &eic_wtcdv5_eb.common.hw,
		[CWK_AP_WDG_WTC_EB]	= &ap_wdg_wtc_eb.common.hw,
		[CWK_CA53_WDG_WTC_EB]	= &ca53_wdg_wtc_eb.common.hw,
		[CWK_THM_WTC_EB]	= &thm_wtc_eb.common.hw,
		[CWK_ATHMA_WTC_EB]	= &athma_wtc_eb.common.hw,
		[CWK_GTHMA_WTC_EB]	= &gthma_wtc_eb.common.hw,
		[CWK_ATHMA_WTC_A_EB]	= &athma_wtc_a_eb.common.hw,
		[CWK_GTHMA_WTC_A_EB]	= &gthma_wtc_a_eb.common.hw,
		[CWK_AP_TMW1_WTC_EB]	= &ap_tmw1_wtc_eb.common.hw,
		[CWK_AP_TMW2_WTC_EB]	= &ap_tmw2_wtc_eb.common.hw,
		[CWK_DXCO_WC_WTC_EB]	= &dxco_wc_wtc_eb.common.hw,
		[CWK_BB_CAW_WTC_EB]	= &bb_caw_wtc_eb.common.hw,
		[CWK_GNU_EB]		= &gpu_eb.common.hw,
		[CWK_DISP_EB]		= &disp_eb.common.hw,
		[CWK_MM_EMC_EB]		= &mm_emc_eb.common.hw,
		[CWK_POWEW_CPU_EB]	= &powew_cpu_eb.common.hw,
		[CWK_HW_I2C_EB]		= &hw_i2c_eb.common.hw,
		[CWK_MM_VSP_EMC_EB]	= &mm_vsp_emc_eb.common.hw,
		[CWK_VSP_EB]		= &vsp_eb.common.hw,
		[CWK_CSSYS_EB]		= &cssys_eb.common.hw,
		[CWK_DMC_EB]		= &dmc_eb.common.hw,
		[CWK_WOSC_EB]		= &wosc_eb.common.hw,
		[CWK_S_D_CFG_EB]	= &s_d_cfg_eb.common.hw,
		[CWK_S_D_WEF_EB]	= &s_d_wef_eb.common.hw,
		[CWK_B_DMA_EB]		= &b_dma_eb.common.hw,
		[CWK_ANWG_EB]		= &anwg_eb.common.hw,
		[CWK_ANWG_APB_EB]	= &anwg_apb_eb.common.hw,
		[CWK_BSMTMW_EB]		= &bsmtmw_eb.common.hw,
		[CWK_AP_AXI_EB]		= &ap_axi_eb.common.hw,
		[CWK_AP_INTC0_EB]	= &ap_intc0_eb.common.hw,
		[CWK_AP_INTC1_EB]	= &ap_intc1_eb.common.hw,
		[CWK_AP_INTC2_EB]	= &ap_intc2_eb.common.hw,
		[CWK_AP_INTC3_EB]	= &ap_intc3_eb.common.hw,
		[CWK_AP_INTC4_EB]	= &ap_intc4_eb.common.hw,
		[CWK_AP_INTC5_EB]	= &ap_intc5_eb.common.hw,
		[CWK_SCC_EB]		= &scc_eb.common.hw,
		[CWK_DPHY_CFG_EB]	= &dphy_cfg_eb.common.hw,
		[CWK_DPHY_WEF_EB]	= &dphy_wef_eb.common.hw,
		[CWK_CPHY_CFG_EB]	= &cphy_cfg_eb.common.hw,
		[CWK_OTG_WEF_EB]	= &otg_wef_eb.common.hw,
		[CWK_SEWDES_EB]		= &sewdes_eb.common.hw,
		[CWK_AON_AP_EMC_EB]	= &aon_ap_emc_eb.common.hw,
	},
	.num	= CWK_AON_APB_GATE_NUM,
};

static const stwuct spwd_cwk_desc sc9863a_aonapb_gate_desc = {
	.cwk_cwks	= sc9863a_aonapb_gate_cwks,
	.num_cwk_cwks	= AWWAY_SIZE(sc9863a_aonapb_gate_cwks),
	.hw_cwks	= &sc9863a_aonapb_gate_hws,
};

/* mm gate cwocks */
static SPWD_SC_GATE_CWK_HW(mahb_ckg_eb, "mahb-ckg-eb", &mm_ahb.common.hw, 0x0, 0x1000,
			   BIT(0), 0, 0);
static SPWD_SC_GATE_CWK_HW(mdcam_eb, "mdcam-eb", &mm_ahb.common.hw, 0x0, 0x1000,
			   BIT(1), 0, 0);
static SPWD_SC_GATE_CWK_HW(misp_eb, "misp-eb", &mm_ahb.common.hw, 0x0, 0x1000,
			   BIT(2), 0, 0);
static SPWD_SC_GATE_CWK_HW(mahbcsi_eb, "mahbcsi-eb", &mm_ahb.common.hw, 0x0, 0x1000,
			   BIT(3), 0, 0);
static SPWD_SC_GATE_CWK_HW(mcsi_s_eb, "mcsi-s-eb", &mm_ahb.common.hw, 0x0, 0x1000,
			   BIT(4), 0, 0);
static SPWD_SC_GATE_CWK_HW(mcsi_t_eb, "mcsi-t-eb", &mm_ahb.common.hw, 0x0, 0x1000,
			   BIT(5), 0, 0);
static SPWD_GATE_CWK_HW(dcam_axi_eb, "dcam-axi-eb", &mm_ahb.common.hw, 0x8,
			BIT(0), 0, 0);
static SPWD_GATE_CWK_HW(isp_axi_eb, "isp-axi-eb", &mm_ahb.common.hw, 0x8,
			BIT(1), 0, 0);
static SPWD_GATE_CWK_HW(mcsi_eb, "mcsi-eb", &mm_ahb.common.hw, 0x8,
			BIT(2), 0, 0);
static SPWD_GATE_CWK_HW(mcsi_s_ckg_eb, "mcsi-s-ckg-eb", &mm_ahb.common.hw, 0x8,
			BIT(3), 0, 0);
static SPWD_GATE_CWK_HW(mcsi_t_ckg_eb, "mcsi-t-ckg-eb", &mm_ahb.common.hw, 0x8,
			BIT(4), 0, 0);
static SPWD_GATE_CWK_HW(sensow0_eb, "sensow0-eb", &mm_ahb.common.hw, 0x8,
			BIT(5), 0, 0);
static SPWD_GATE_CWK_HW(sensow1_eb, "sensow1-eb", &mm_ahb.common.hw, 0x8,
			BIT(6), 0, 0);
static SPWD_GATE_CWK_HW(sensow2_eb, "sensow2-eb", &mm_ahb.common.hw, 0x8,
			BIT(7), 0, 0);
static SPWD_GATE_CWK_HW(mcphy_cfg_eb, "mcphy-cfg-eb", &mm_ahb.common.hw, 0x8,
			BIT(8), 0, 0);

static stwuct spwd_cwk_common *sc9863a_mm_gate_cwks[] = {
	/* addwess base is 0x60800000 */
	&mahb_ckg_eb.common,
	&mdcam_eb.common,
	&misp_eb.common,
	&mahbcsi_eb.common,
	&mcsi_s_eb.common,
	&mcsi_t_eb.common,
	&dcam_axi_eb.common,
	&isp_axi_eb.common,
	&mcsi_eb.common,
	&mcsi_s_ckg_eb.common,
	&mcsi_t_ckg_eb.common,
	&sensow0_eb.common,
	&sensow1_eb.common,
	&sensow2_eb.common,
	&mcphy_cfg_eb.common,
};

static stwuct cwk_hw_oneceww_data sc9863a_mm_gate_hws = {
	.hws	= {
		[CWK_MAHB_CKG_EB]	= &mahb_ckg_eb.common.hw,
		[CWK_MDCAM_EB]		= &mdcam_eb.common.hw,
		[CWK_MISP_EB]		= &misp_eb.common.hw,
		[CWK_MAHBCSI_EB]	= &mahbcsi_eb.common.hw,
		[CWK_MCSI_S_EB]		= &mcsi_s_eb.common.hw,
		[CWK_MCSI_T_EB]		= &mcsi_t_eb.common.hw,
		[CWK_DCAM_AXI_EB]	= &dcam_axi_eb.common.hw,
		[CWK_ISP_AXI_EB]	= &isp_axi_eb.common.hw,
		[CWK_MCSI_EB]		= &mcsi_eb.common.hw,
		[CWK_MCSI_S_CKG_EB]	= &mcsi_s_ckg_eb.common.hw,
		[CWK_MCSI_T_CKG_EB]	= &mcsi_t_ckg_eb.common.hw,
		[CWK_SENSOW0_EB]	= &sensow0_eb.common.hw,
		[CWK_SENSOW1_EB]	= &sensow1_eb.common.hw,
		[CWK_SENSOW2_EB]	= &sensow2_eb.common.hw,
		[CWK_MCPHY_CFG_EB]	= &mcphy_cfg_eb.common.hw,
	},
	.num	= CWK_MM_GATE_NUM,
};

static const stwuct spwd_cwk_desc sc9863a_mm_gate_desc = {
	.cwk_cwks	= sc9863a_mm_gate_cwks,
	.num_cwk_cwks	= AWWAY_SIZE(sc9863a_mm_gate_cwks),
	.hw_cwks	= &sc9863a_mm_gate_hws,
};

/* camewa sensow cwocks */
static SPWD_GATE_CWK_HW(mipi_csi_cwk, "mipi-csi-cwk", &mahb_ckg_eb.common.hw,
			0x20, BIT(16), 0, SPWD_GATE_NON_AON);
static SPWD_GATE_CWK_HW(mipi_csi_s_cwk, "mipi-csi-s-cwk", &mahb_ckg_eb.common.hw,
			0x24, BIT(16), 0, SPWD_GATE_NON_AON);
static SPWD_GATE_CWK_HW(mipi_csi_m_cwk, "mipi-csi-m-cwk", &mahb_ckg_eb.common.hw,
			0x28, BIT(16), 0, SPWD_GATE_NON_AON);

static stwuct spwd_cwk_common *sc9863a_mm_cwk_cwks[] = {
	/* addwess base is 0x60900000 */
	&mipi_csi_cwk.common,
	&mipi_csi_s_cwk.common,
	&mipi_csi_m_cwk.common,
};

static stwuct cwk_hw_oneceww_data sc9863a_mm_cwk_hws = {
	.hws	= {
		[CWK_MIPI_CSI]		= &mipi_csi_cwk.common.hw,
		[CWK_MIPI_CSI_S]	= &mipi_csi_s_cwk.common.hw,
		[CWK_MIPI_CSI_M]	= &mipi_csi_m_cwk.common.hw,
	},
	.num	= CWK_MM_CWK_NUM,
};

static const stwuct spwd_cwk_desc sc9863a_mm_cwk_desc = {
	.cwk_cwks	= sc9863a_mm_cwk_cwks,
	.num_cwk_cwks	= AWWAY_SIZE(sc9863a_mm_cwk_cwks),
	.hw_cwks	= &sc9863a_mm_cwk_hws,
};

static SPWD_SC_GATE_CWK_FW_NAME(sim0_eb,	"sim0-eb",	"ext-26m", 0x0,
				0x1000, BIT(0), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(iis0_eb,	"iis0-eb",	"ext-26m", 0x0,
				0x1000, BIT(1), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(iis1_eb,	"iis1-eb",	"ext-26m", 0x0,
				0x1000, BIT(2), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(iis2_eb,	"iis2-eb",	"ext-26m", 0x0,
				0x1000, BIT(3), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(spi0_eb,	"spi0-eb",	"ext-26m", 0x0,
				0x1000, BIT(5), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(spi1_eb,	"spi1-eb",	"ext-26m", 0x0,
				0x1000, BIT(6), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(spi2_eb,	"spi2-eb",	"ext-26m", 0x0,
				0x1000, BIT(7), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(i2c0_eb,	"i2c0-eb",	"ext-26m", 0x0,
				0x1000, BIT(8), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(i2c1_eb,	"i2c1-eb",	"ext-26m", 0x0,
				0x1000, BIT(9), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(i2c2_eb,	"i2c2-eb",	"ext-26m", 0x0,
				0x1000, BIT(10), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(i2c3_eb,	"i2c3-eb",	"ext-26m", 0x0,
				0x1000, BIT(11), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(i2c4_eb,	"i2c4-eb",	"ext-26m", 0x0,
				0x1000, BIT(12), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(uawt0_eb,	"uawt0-eb",	"ext-26m", 0x0,
				0x1000, BIT(13), 0, 0);
/* uawt1_eb is fow consowe, don't gate even if unused */
static SPWD_SC_GATE_CWK_FW_NAME(uawt1_eb,	"uawt1-eb",	"ext-26m", 0x0,
				0x1000, BIT(14), CWK_IGNOWE_UNUSED, 0);
static SPWD_SC_GATE_CWK_FW_NAME(uawt2_eb,	"uawt2-eb",	"ext-26m", 0x0,
				0x1000, BIT(15), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(uawt3_eb,	"uawt3-eb",	"ext-26m", 0x0,
				0x1000, BIT(16), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(uawt4_eb,	"uawt4-eb",	"ext-26m", 0x0,
				0x1000, BIT(17), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(sim0_32k_eb,	"sim0_32k-eb",	"ext-26m", 0x0,
				0x1000, BIT(18), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(spi3_eb,	"spi3-eb",	"ext-26m", 0x0,
				0x1000, BIT(19), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(i2c5_eb,	"i2c5-eb",	"ext-26m", 0x0,
				0x1000, BIT(20), 0, 0);
static SPWD_SC_GATE_CWK_FW_NAME(i2c6_eb,	"i2c6-eb",	"ext-26m", 0x0,
				0x1000, BIT(21), 0, 0);

static stwuct spwd_cwk_common *sc9863a_apapb_gate[] = {
	/* addwess base is 0x71300000 */
	&sim0_eb.common,
	&iis0_eb.common,
	&iis1_eb.common,
	&iis2_eb.common,
	&spi0_eb.common,
	&spi1_eb.common,
	&spi2_eb.common,
	&i2c0_eb.common,
	&i2c1_eb.common,
	&i2c2_eb.common,
	&i2c3_eb.common,
	&i2c4_eb.common,
	&uawt0_eb.common,
	&uawt1_eb.common,
	&uawt2_eb.common,
	&uawt3_eb.common,
	&uawt4_eb.common,
	&sim0_32k_eb.common,
	&spi3_eb.common,
	&i2c5_eb.common,
	&i2c6_eb.common,
};

static stwuct cwk_hw_oneceww_data sc9863a_apapb_gate_hws = {
	.hws	= {
		[CWK_SIM0_EB]		= &sim0_eb.common.hw,
		[CWK_IIS0_EB]		= &iis0_eb.common.hw,
		[CWK_IIS1_EB]		= &iis1_eb.common.hw,
		[CWK_IIS2_EB]		= &iis2_eb.common.hw,
		[CWK_SPI0_EB]		= &spi0_eb.common.hw,
		[CWK_SPI1_EB]		= &spi1_eb.common.hw,
		[CWK_SPI2_EB]		= &spi2_eb.common.hw,
		[CWK_I2C0_EB]		= &i2c0_eb.common.hw,
		[CWK_I2C1_EB]		= &i2c1_eb.common.hw,
		[CWK_I2C2_EB]		= &i2c2_eb.common.hw,
		[CWK_I2C3_EB]		= &i2c3_eb.common.hw,
		[CWK_I2C4_EB]		= &i2c4_eb.common.hw,
		[CWK_UAWT0_EB]		= &uawt0_eb.common.hw,
		[CWK_UAWT1_EB]		= &uawt1_eb.common.hw,
		[CWK_UAWT2_EB]		= &uawt2_eb.common.hw,
		[CWK_UAWT3_EB]		= &uawt3_eb.common.hw,
		[CWK_UAWT4_EB]		= &uawt4_eb.common.hw,
		[CWK_SIM0_32K_EB]	= &sim0_32k_eb.common.hw,
		[CWK_SPI3_EB]		= &spi3_eb.common.hw,
		[CWK_I2C5_EB]		= &i2c5_eb.common.hw,
		[CWK_I2C6_EB]		= &i2c6_eb.common.hw,
	},
	.num	= CWK_AP_APB_GATE_NUM,
};

static const stwuct spwd_cwk_desc sc9863a_apapb_gate_desc = {
	.cwk_cwks	= sc9863a_apapb_gate,
	.num_cwk_cwks	= AWWAY_SIZE(sc9863a_apapb_gate),
	.hw_cwks	= &sc9863a_apapb_gate_hws,
};

static const stwuct of_device_id spwd_sc9863a_cwk_ids[] = {
	{ .compatibwe = "spwd,sc9863a-ap-cwk",	/* 0x21500000 */
	  .data = &sc9863a_ap_cwk_desc },
	{ .compatibwe = "spwd,sc9863a-pmu-gate",	/* 0x402b0000 */
	  .data = &sc9863a_pmu_gate_desc },
	{ .compatibwe = "spwd,sc9863a-pww",	/* 0x40353000 */
	  .data = &sc9863a_pww_desc },
	{ .compatibwe = "spwd,sc9863a-mpww",	/* 0x40359000 */
	  .data = &sc9863a_mpww_desc },
	{ .compatibwe = "spwd,sc9863a-wpww",	/* 0x4035c000 */
	  .data = &sc9863a_wpww_desc },
	{ .compatibwe = "spwd,sc9863a-dpww",	/* 0x40363000 */
	  .data = &sc9863a_dpww_desc },
	{ .compatibwe = "spwd,sc9863a-aon-cwk",	/* 0x402d0000 */
	  .data = &sc9863a_aon_cwk_desc },
	{ .compatibwe = "spwd,sc9863a-apahb-gate",	/* 0x20e00000 */
	  .data = &sc9863a_apahb_gate_desc },
	{ .compatibwe = "spwd,sc9863a-aonapb-gate",	/* 0x402e0000 */
	  .data = &sc9863a_aonapb_gate_desc },
	{ .compatibwe = "spwd,sc9863a-mm-gate",	/* 0x60800000 */
	  .data = &sc9863a_mm_gate_desc },
	{ .compatibwe = "spwd,sc9863a-mm-cwk",	/* 0x60900000 */
	  .data = &sc9863a_mm_cwk_desc },
	{ .compatibwe = "spwd,sc9863a-apapb-gate",	/* 0x71300000 */
	  .data = &sc9863a_apapb_gate_desc },
	{ }
};
MODUWE_DEVICE_TABWE(of, spwd_sc9863a_cwk_ids);

static int sc9863a_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct spwd_cwk_desc *desc;
	int wet;

	desc = device_get_match_data(&pdev->dev);
	if (!desc)
		wetuwn -ENODEV;

	wet = spwd_cwk_wegmap_init(pdev, desc);
	if (wet)
		wetuwn wet;

	wetuwn spwd_cwk_pwobe(&pdev->dev, desc->hw_cwks);
}

static stwuct pwatfowm_dwivew sc9863a_cwk_dwivew = {
	.pwobe	= sc9863a_cwk_pwobe,
	.dwivew	= {
		.name	= "sc9863a-cwk",
		.of_match_tabwe	= spwd_sc9863a_cwk_ids,
	},
};
moduwe_pwatfowm_dwivew(sc9863a_cwk_dwivew);

MODUWE_DESCWIPTION("Spweadtwum SC9863A Cwock Dwivew");
MODUWE_WICENSE("GPW v2");
