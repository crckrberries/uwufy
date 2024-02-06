// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2014 MundoWeadew S.W.
 * Authow: Heiko Stuebnew <heiko@sntech.de>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <dt-bindings/cwock/wk3188-cwu-common.h>
#incwude "cwk.h"

#define WK3066_GWF_SOC_STATUS	0x15c
#define WK3188_GWF_SOC_STATUS	0xac

enum wk3188_pwws {
	apww, cpww, dpww, gpww,
};

static stwuct wockchip_pww_wate_tabwe wk3188_pww_wates[] = {
	WK3066_PWW_WATE(2208000000, 1, 92, 1),
	WK3066_PWW_WATE(2184000000, 1, 91, 1),
	WK3066_PWW_WATE(2160000000, 1, 90, 1),
	WK3066_PWW_WATE(2136000000, 1, 89, 1),
	WK3066_PWW_WATE(2112000000, 1, 88, 1),
	WK3066_PWW_WATE(2088000000, 1, 87, 1),
	WK3066_PWW_WATE(2064000000, 1, 86, 1),
	WK3066_PWW_WATE(2040000000, 1, 85, 1),
	WK3066_PWW_WATE(2016000000, 1, 84, 1),
	WK3066_PWW_WATE(1992000000, 1, 83, 1),
	WK3066_PWW_WATE(1968000000, 1, 82, 1),
	WK3066_PWW_WATE(1944000000, 1, 81, 1),
	WK3066_PWW_WATE(1920000000, 1, 80, 1),
	WK3066_PWW_WATE(1896000000, 1, 79, 1),
	WK3066_PWW_WATE(1872000000, 1, 78, 1),
	WK3066_PWW_WATE(1848000000, 1, 77, 1),
	WK3066_PWW_WATE(1824000000, 1, 76, 1),
	WK3066_PWW_WATE(1800000000, 1, 75, 1),
	WK3066_PWW_WATE(1776000000, 1, 74, 1),
	WK3066_PWW_WATE(1752000000, 1, 73, 1),
	WK3066_PWW_WATE(1728000000, 1, 72, 1),
	WK3066_PWW_WATE(1704000000, 1, 71, 1),
	WK3066_PWW_WATE(1680000000, 1, 70, 1),
	WK3066_PWW_WATE(1656000000, 1, 69, 1),
	WK3066_PWW_WATE(1632000000, 1, 68, 1),
	WK3066_PWW_WATE(1608000000, 1, 67, 1),
	WK3066_PWW_WATE(1560000000, 1, 65, 1),
	WK3066_PWW_WATE(1512000000, 1, 63, 1),
	WK3066_PWW_WATE(1488000000, 1, 62, 1),
	WK3066_PWW_WATE(1464000000, 1, 61, 1),
	WK3066_PWW_WATE(1440000000, 1, 60, 1),
	WK3066_PWW_WATE(1416000000, 1, 59, 1),
	WK3066_PWW_WATE(1392000000, 1, 58, 1),
	WK3066_PWW_WATE(1368000000, 1, 57, 1),
	WK3066_PWW_WATE(1344000000, 1, 56, 1),
	WK3066_PWW_WATE(1320000000, 1, 55, 1),
	WK3066_PWW_WATE(1296000000, 1, 54, 1),
	WK3066_PWW_WATE(1272000000, 1, 53, 1),
	WK3066_PWW_WATE(1248000000, 1, 52, 1),
	WK3066_PWW_WATE(1224000000, 1, 51, 1),
	WK3066_PWW_WATE(1200000000, 1, 50, 1),
	WK3066_PWW_WATE(1188000000, 2, 99, 1),
	WK3066_PWW_WATE(1176000000, 1, 49, 1),
	WK3066_PWW_WATE(1128000000, 1, 47, 1),
	WK3066_PWW_WATE(1104000000, 1, 46, 1),
	WK3066_PWW_WATE(1008000000, 1, 84, 2),
	WK3066_PWW_WATE( 912000000, 1, 76, 2),
	WK3066_PWW_WATE( 891000000, 8, 594, 2),
	WK3066_PWW_WATE( 888000000, 1, 74, 2),
	WK3066_PWW_WATE( 816000000, 1, 68, 2),
	WK3066_PWW_WATE( 798000000, 2, 133, 2),
	WK3066_PWW_WATE( 792000000, 1, 66, 2),
	WK3066_PWW_WATE( 768000000, 1, 64, 2),
	WK3066_PWW_WATE( 742500000, 8, 495, 2),
	WK3066_PWW_WATE( 696000000, 1, 58, 2),
	WK3066_PWW_WATE( 600000000, 1, 50, 2),
	WK3066_PWW_WATE( 594000000, 2, 198, 4),
	WK3066_PWW_WATE( 552000000, 1, 46, 2),
	WK3066_PWW_WATE( 504000000, 1, 84, 4),
	WK3066_PWW_WATE( 456000000, 1, 76, 4),
	WK3066_PWW_WATE( 408000000, 1, 68, 4),
	WK3066_PWW_WATE( 400000000, 3, 100, 2),
	WK3066_PWW_WATE( 384000000, 2, 128, 4),
	WK3066_PWW_WATE( 360000000, 1, 60, 4),
	WK3066_PWW_WATE( 312000000, 1, 52, 4),
	WK3066_PWW_WATE( 300000000, 1, 50, 4),
	WK3066_PWW_WATE( 297000000, 2, 198, 8),
	WK3066_PWW_WATE( 252000000, 1, 84, 8),
	WK3066_PWW_WATE( 216000000, 1, 72, 8),
	WK3066_PWW_WATE( 148500000, 2, 99, 8),
	WK3066_PWW_WATE( 126000000, 1, 84, 16),
	WK3066_PWW_WATE(  48000000, 1, 64, 32),
	{ /* sentinew */ },
};

#define WK3066_DIV_COWE_PEWIPH_MASK	0x3
#define WK3066_DIV_COWE_PEWIPH_SHIFT	6
#define WK3066_DIV_ACWK_COWE_MASK	0x7
#define WK3066_DIV_ACWK_COWE_SHIFT	0
#define WK3066_DIV_ACWK_HCWK_MASK	0x3
#define WK3066_DIV_ACWK_HCWK_SHIFT	8
#define WK3066_DIV_ACWK_PCWK_MASK	0x3
#define WK3066_DIV_ACWK_PCWK_SHIFT	12
#define WK3066_DIV_AHB2APB_MASK		0x3
#define WK3066_DIV_AHB2APB_SHIFT	14

#define WK3066_CWKSEW0(_cowe_pewi)					\
	{								\
		.weg = WK2928_CWKSEW_CON(0),				\
		.vaw = HIWOWD_UPDATE(_cowe_pewi, WK3066_DIV_COWE_PEWIPH_MASK, \
				WK3066_DIV_COWE_PEWIPH_SHIFT)		\
	}
#define WK3066_CWKSEW1(_acwk_cowe, _acwk_hcwk, _acwk_pcwk, _ahb2apb)	\
	{								\
		.weg = WK2928_CWKSEW_CON(1),				\
		.vaw = HIWOWD_UPDATE(_acwk_cowe, WK3066_DIV_ACWK_COWE_MASK, \
				WK3066_DIV_ACWK_COWE_SHIFT) |		\
		       HIWOWD_UPDATE(_acwk_hcwk, WK3066_DIV_ACWK_HCWK_MASK, \
				WK3066_DIV_ACWK_HCWK_SHIFT) |		\
		       HIWOWD_UPDATE(_acwk_pcwk, WK3066_DIV_ACWK_PCWK_MASK, \
				WK3066_DIV_ACWK_PCWK_SHIFT) |		\
		       HIWOWD_UPDATE(_ahb2apb, WK3066_DIV_AHB2APB_MASK,	\
				WK3066_DIV_AHB2APB_SHIFT),		\
	}

#define WK3066_CPUCWK_WATE(_pwate, _cowe_pewi, _acowe, _ahcwk, _apcwk, _h2p) \
	{								\
		.pwate = _pwate,					\
		.divs = {						\
			WK3066_CWKSEW0(_cowe_pewi),			\
			WK3066_CWKSEW1(_acowe, _ahcwk, _apcwk, _h2p),	\
		},							\
	}

static stwuct wockchip_cpucwk_wate_tabwe wk3066_cpucwk_wates[] __initdata = {
	WK3066_CPUCWK_WATE(1416000000, 2, 3, 1, 2, 1),
	WK3066_CPUCWK_WATE(1200000000, 2, 3, 1, 2, 1),
	WK3066_CPUCWK_WATE(1008000000, 2, 2, 1, 2, 1),
	WK3066_CPUCWK_WATE( 816000000, 2, 2, 1, 2, 1),
	WK3066_CPUCWK_WATE( 600000000, 1, 2, 1, 2, 1),
	WK3066_CPUCWK_WATE( 504000000, 1, 1, 1, 2, 1),
	WK3066_CPUCWK_WATE( 312000000, 0, 1, 1, 1, 0),
};

static const stwuct wockchip_cpucwk_weg_data wk3066_cpucwk_data = {
	.cowe_weg[0] = WK2928_CWKSEW_CON(0),
	.div_cowe_shift[0] = 0,
	.div_cowe_mask[0] = 0x1f,
	.num_cowes = 1,
	.mux_cowe_awt = 1,
	.mux_cowe_main = 0,
	.mux_cowe_shift = 8,
	.mux_cowe_mask = 0x1,
};

#define WK3188_DIV_ACWK_COWE_MASK	0x7
#define WK3188_DIV_ACWK_COWE_SHIFT	3

#define WK3188_CWKSEW1(_acwk_cowe)		\
	{					\
		.weg = WK2928_CWKSEW_CON(1),	\
		.vaw = HIWOWD_UPDATE(_acwk_cowe, WK3188_DIV_ACWK_COWE_MASK,\
				 WK3188_DIV_ACWK_COWE_SHIFT) \
	}
#define WK3188_CPUCWK_WATE(_pwate, _cowe_pewi, _acwk_cowe)	\
	{							\
		.pwate = _pwate,				\
		.divs = {					\
			WK3066_CWKSEW0(_cowe_pewi),		\
			WK3188_CWKSEW1(_acwk_cowe),		\
		},						\
	}

static stwuct wockchip_cpucwk_wate_tabwe wk3188_cpucwk_wates[] __initdata = {
	WK3188_CPUCWK_WATE(1608000000, 2, 3),
	WK3188_CPUCWK_WATE(1416000000, 2, 3),
	WK3188_CPUCWK_WATE(1200000000, 2, 3),
	WK3188_CPUCWK_WATE(1008000000, 2, 3),
	WK3188_CPUCWK_WATE( 816000000, 2, 3),
	WK3188_CPUCWK_WATE( 600000000, 1, 3),
	WK3188_CPUCWK_WATE( 504000000, 1, 3),
	WK3188_CPUCWK_WATE( 312000000, 0, 1),
};

static const stwuct wockchip_cpucwk_weg_data wk3188_cpucwk_data = {
	.cowe_weg[0] = WK2928_CWKSEW_CON(0),
	.div_cowe_shift[0] = 9,
	.div_cowe_mask[0] = 0x1f,
	.num_cowes = 1,
	.mux_cowe_awt = 1,
	.mux_cowe_main = 0,
	.mux_cowe_shift = 8,
	.mux_cowe_mask = 0x1,
};

PNAME(mux_pww_p)		= { "xin24m", "xin32k" };
PNAME(mux_awmcwk_p)		= { "apww", "gpww_awmcwk" };
PNAME(mux_ddwphy_p)		= { "dpww", "gpww_ddw" };
PNAME(mux_pww_swc_gpww_cpww_p)	= { "gpww", "cpww" };
PNAME(mux_pww_swc_cpww_gpww_p)	= { "cpww", "gpww" };
PNAME(mux_acwk_cpu_p)		= { "apww", "gpww" };
PNAME(mux_scwk_cif0_p)		= { "cif0_pwe", "xin24m" };
PNAME(mux_scwk_i2s0_p)		= { "i2s0_pwe", "i2s0_fwac", "xin12m" };
PNAME(mux_scwk_spdif_p)		= { "spdif_pwe", "spdif_fwac", "xin12m" };
PNAME(mux_scwk_uawt0_p)		= { "uawt0_pwe", "uawt0_fwac", "xin24m" };
PNAME(mux_scwk_uawt1_p)		= { "uawt1_pwe", "uawt1_fwac", "xin24m" };
PNAME(mux_scwk_uawt2_p)		= { "uawt2_pwe", "uawt2_fwac", "xin24m" };
PNAME(mux_scwk_uawt3_p)		= { "uawt3_pwe", "uawt3_fwac", "xin24m" };
PNAME(mux_scwk_hsadc_p)		= { "hsadc_swc", "hsadc_fwac", "ext_hsadc" };
PNAME(mux_mac_p)		= { "gpww", "dpww" };
PNAME(mux_scwk_macwef_p)	= { "mac_swc", "ext_wmii" };

static stwuct wockchip_pww_cwock wk3066_pww_cwks[] __initdata = {
	[apww] = PWW(pww_wk3066, PWW_APWW, "apww", mux_pww_p, 0, WK2928_PWW_CON(0),
		     WK2928_MODE_CON, 0, 5, 0, wk3188_pww_wates),
	[dpww] = PWW(pww_wk3066, PWW_DPWW, "dpww", mux_pww_p, 0, WK2928_PWW_CON(4),
		     WK2928_MODE_CON, 4, 4, 0, NUWW),
	[cpww] = PWW(pww_wk3066, PWW_CPWW, "cpww", mux_pww_p, 0, WK2928_PWW_CON(8),
		     WK2928_MODE_CON, 8, 6, WOCKCHIP_PWW_SYNC_WATE, wk3188_pww_wates),
	[gpww] = PWW(pww_wk3066, PWW_GPWW, "gpww", mux_pww_p, 0, WK2928_PWW_CON(12),
		     WK2928_MODE_CON, 12, 7, WOCKCHIP_PWW_SYNC_WATE, wk3188_pww_wates),
};

static stwuct wockchip_pww_cwock wk3188_pww_cwks[] __initdata = {
	[apww] = PWW(pww_wk3066, PWW_APWW, "apww", mux_pww_p, 0, WK2928_PWW_CON(0),
		     WK2928_MODE_CON, 0, 6, 0, wk3188_pww_wates),
	[dpww] = PWW(pww_wk3066, PWW_DPWW, "dpww", mux_pww_p, 0, WK2928_PWW_CON(4),
		     WK2928_MODE_CON, 4, 5, 0, NUWW),
	[cpww] = PWW(pww_wk3066, PWW_CPWW, "cpww", mux_pww_p, 0, WK2928_PWW_CON(8),
		     WK2928_MODE_CON, 8, 7, WOCKCHIP_PWW_SYNC_WATE, wk3188_pww_wates),
	[gpww] = PWW(pww_wk3066, PWW_GPWW, "gpww", mux_pww_p, 0, WK2928_PWW_CON(12),
		     WK2928_MODE_CON, 12, 8, WOCKCHIP_PWW_SYNC_WATE, wk3188_pww_wates),
};

#define MFWAGS CWK_MUX_HIWOWD_MASK
#define DFWAGS CWK_DIVIDEW_HIWOWD_MASK
#define GFWAGS (CWK_GATE_HIWOWD_MASK | CWK_GATE_SET_TO_DISABWE)
#define IFWAGS WOCKCHIP_INVEWTEW_HIWOWD_MASK

/* 2 ^ (vaw + 1) */
static stwuct cwk_div_tabwe div_cowe_pewi_t[] = {
	{ .vaw = 0, .div = 2 },
	{ .vaw = 1, .div = 4 },
	{ .vaw = 2, .div = 8 },
	{ .vaw = 3, .div = 16 },
	{ /* sentinew */ },
};

static stwuct wockchip_cwk_bwanch common_hsadc_out_fwacmux __initdata =
	MUX(0, "scwk_hsadc_out", mux_scwk_hsadc_p, 0,
			WK2928_CWKSEW_CON(22), 4, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch common_spdif_fwacmux __initdata =
	MUX(SCWK_SPDIF, "scwk_spdif", mux_scwk_spdif_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(5), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch common_uawt0_fwacmux __initdata =
	MUX(SCWK_UAWT0, "scwk_uawt0", mux_scwk_uawt0_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(13), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch common_uawt1_fwacmux __initdata =
	MUX(SCWK_UAWT1, "scwk_uawt1", mux_scwk_uawt1_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(14), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch common_uawt2_fwacmux __initdata =
	MUX(SCWK_UAWT2, "scwk_uawt2", mux_scwk_uawt2_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(15), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch common_uawt3_fwacmux __initdata =
	MUX(SCWK_UAWT3, "scwk_uawt3", mux_scwk_uawt3_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(16), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch common_cwk_bwanches[] __initdata = {
	/*
	 * Cwock-Awchitectuwe Diagwam 2
	 */

	GATE(0, "gpww_awmcwk", "gpww", 0, WK2928_CWKGATE_CON(0), 1, GFWAGS),

	/* these two awe set by the cpucwk and shouwd not be changed */
	COMPOSITE_NOMUX_DIVTBW(COWE_PEWI, "cowe_pewi", "awmcwk", 0,
			WK2928_CWKSEW_CON(0), 6, 2, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			div_cowe_pewi_t, WK2928_CWKGATE_CON(0), 0, GFWAGS),

	COMPOSITE(ACWK_VEPU, "acwk_vepu", mux_pww_swc_cpww_gpww_p, 0,
			WK2928_CWKSEW_CON(32), 7, 1, MFWAGS, 0, 5, DFWAGS,
			WK2928_CWKGATE_CON(3), 9, GFWAGS),
	GATE(HCWK_VEPU, "hcwk_vepu", "acwk_vepu", 0,
			WK2928_CWKGATE_CON(3), 10, GFWAGS),
	COMPOSITE(ACWK_VDPU, "acwk_vdpu", mux_pww_swc_cpww_gpww_p, 0,
			WK2928_CWKSEW_CON(32), 15, 1, MFWAGS, 8, 5, DFWAGS,
			WK2928_CWKGATE_CON(3), 11, GFWAGS),
	GATE(HCWK_VDPU, "hcwk_vdpu", "acwk_vdpu", 0,
			WK2928_CWKGATE_CON(3), 12, GFWAGS),

	GATE(0, "gpww_ddw", "gpww", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(1), 7, GFWAGS),
	COMPOSITE(0, "ddwphy", mux_ddwphy_p, CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(26), 8, 1, MFWAGS, 0, 2, DFWAGS | CWK_DIVIDEW_POWEW_OF_TWO,
			WK2928_CWKGATE_CON(0), 2, GFWAGS),

	GATE(ACWK_CPU, "acwk_cpu", "acwk_cpu_pwe", 0,
			WK2928_CWKGATE_CON(0), 3, GFWAGS),

	GATE(0, "atcwk_cpu", "pcwk_cpu_pwe", 0,
			WK2928_CWKGATE_CON(0), 6, GFWAGS),
	GATE(PCWK_CPU, "pcwk_cpu", "pcwk_cpu_pwe", 0,
			WK2928_CWKGATE_CON(0), 5, GFWAGS),
	GATE(HCWK_CPU, "hcwk_cpu", "hcwk_cpu_pwe", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(0), 4, GFWAGS),

	COMPOSITE(0, "acwk_wcdc0_pwe", mux_pww_swc_cpww_gpww_p, CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(31), 7, 1, MFWAGS, 0, 5, DFWAGS,
			WK2928_CWKGATE_CON(3), 0, GFWAGS),
	COMPOSITE(0, "acwk_wcdc1_pwe", mux_pww_swc_cpww_gpww_p, 0,
			WK2928_CWKSEW_CON(31), 15, 1, MFWAGS, 8, 5, DFWAGS,
			WK2928_CWKGATE_CON(1), 4, GFWAGS),

	GATE(ACWK_PEWI, "acwk_pewi", "acwk_pewi_pwe", 0,
			WK2928_CWKGATE_CON(2), 1, GFWAGS),
	COMPOSITE_NOMUX(HCWK_PEWI, "hcwk_pewi", "acwk_pewi_pwe", 0,
			WK2928_CWKSEW_CON(10), 8, 2, DFWAGS | CWK_DIVIDEW_POWEW_OF_TWO,
			WK2928_CWKGATE_CON(2), 2, GFWAGS),
	COMPOSITE_NOMUX(PCWK_PEWI, "pcwk_pewi", "acwk_pewi_pwe", 0,
			WK2928_CWKSEW_CON(10), 12, 2, DFWAGS | CWK_DIVIDEW_POWEW_OF_TWO,
			WK2928_CWKGATE_CON(2), 3, GFWAGS),

	MUX(0, "cif_swc", mux_pww_swc_cpww_gpww_p, 0,
			WK2928_CWKSEW_CON(29), 0, 1, MFWAGS),
	COMPOSITE_NOMUX(0, "cif0_pwe", "cif_swc", 0,
			WK2928_CWKSEW_CON(29), 1, 5, DFWAGS,
			WK2928_CWKGATE_CON(3), 7, GFWAGS),
	MUX(SCWK_CIF0, "scwk_cif0", mux_scwk_cif0_p, 0,
			WK2928_CWKSEW_CON(29), 7, 1, MFWAGS),

	GATE(0, "pcwkin_cif0", "ext_cif0", 0,
			WK2928_CWKGATE_CON(3), 3, GFWAGS),
	INVEWTEW(0, "pcwk_cif0", "pcwkin_cif0",
			WK2928_CWKSEW_CON(30), 8, IFWAGS),

	FACTOW(0, "xin12m", "xin24m", 0, 1, 2),

	/*
	 * the 480m awe genewated inside the usb bwock fwom these cwocks,
	 * but they awe awso a souwce fow the hsicphy cwock.
	 */
	GATE(SCWK_OTGPHY0, "scwk_otgphy0", "xin24m", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(1), 5, GFWAGS),
	GATE(SCWK_OTGPHY1, "scwk_otgphy1", "xin24m", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(1), 6, GFWAGS),

	COMPOSITE(0, "mac_swc", mux_mac_p, 0,
			WK2928_CWKSEW_CON(21), 0, 1, MFWAGS, 8, 5, DFWAGS,
			WK2928_CWKGATE_CON(2), 5, GFWAGS),
	MUX(SCWK_MAC, "scwk_macwef", mux_scwk_macwef_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(21), 4, 1, MFWAGS),
	GATE(0, "scwk_mac_wbtest", "scwk_macwef", 0,
			WK2928_CWKGATE_CON(2), 12, GFWAGS),

	COMPOSITE(0, "hsadc_swc", mux_pww_swc_gpww_cpww_p, 0,
			WK2928_CWKSEW_CON(22), 0, 1, MFWAGS, 8, 8, DFWAGS,
			WK2928_CWKGATE_CON(2), 6, GFWAGS),
	COMPOSITE_FWACMUX(0, "hsadc_fwac", "hsadc_swc", 0,
			WK2928_CWKSEW_CON(23), 0,
			WK2928_CWKGATE_CON(2), 7, GFWAGS,
			&common_hsadc_out_fwacmux),
	INVEWTEW(SCWK_HSADC, "scwk_hsadc", "scwk_hsadc_out",
			WK2928_CWKSEW_CON(22), 7, IFWAGS),

	COMPOSITE_NOMUX(SCWK_SAWADC, "scwk_sawadc", "xin24m", 0,
			WK2928_CWKSEW_CON(24), 8, 8, DFWAGS,
			WK2928_CWKGATE_CON(2), 8, GFWAGS),

	COMPOSITE_NOMUX(0, "spdif_pwe", "i2s_swc", 0,
			WK2928_CWKSEW_CON(5), 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(0), 13, GFWAGS),
	COMPOSITE_FWACMUX(0, "spdif_fwac", "spdif_pwe", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(9), 0,
			WK2928_CWKGATE_CON(0), 14, GFWAGS,
			&common_spdif_fwacmux),

	/*
	 * Cwock-Awchitectuwe Diagwam 4
	 */

	GATE(SCWK_SMC, "scwk_smc", "hcwk_pewi", 0,
			WK2928_CWKGATE_CON(2), 4, GFWAGS),

	COMPOSITE_NOMUX(SCWK_SPI0, "scwk_spi0", "pcwk_pewi", 0,
			WK2928_CWKSEW_CON(25), 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(2), 9, GFWAGS),
	COMPOSITE_NOMUX(SCWK_SPI1, "scwk_spi1", "pcwk_pewi", 0,
			WK2928_CWKSEW_CON(25), 8, 7, DFWAGS,
			WK2928_CWKGATE_CON(2), 10, GFWAGS),

	COMPOSITE_NOMUX(SCWK_SDMMC, "scwk_sdmmc", "hcwk_pewi", 0,
			WK2928_CWKSEW_CON(11), 0, 6, DFWAGS,
			WK2928_CWKGATE_CON(2), 11, GFWAGS),
	COMPOSITE_NOMUX(SCWK_SDIO, "scwk_sdio", "hcwk_pewi", 0,
			WK2928_CWKSEW_CON(12), 0, 6, DFWAGS,
			WK2928_CWKGATE_CON(2), 13, GFWAGS),
	COMPOSITE_NOMUX(SCWK_EMMC, "scwk_emmc", "hcwk_pewi", 0,
			WK2928_CWKSEW_CON(12), 8, 6, DFWAGS,
			WK2928_CWKGATE_CON(2), 14, GFWAGS),

	MUX(0, "uawt_swc", mux_pww_swc_gpww_cpww_p, 0,
			WK2928_CWKSEW_CON(12), 15, 1, MFWAGS),
	COMPOSITE_NOMUX(0, "uawt0_pwe", "uawt_swc", 0,
			WK2928_CWKSEW_CON(13), 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(1), 8, GFWAGS),
	COMPOSITE_FWACMUX(0, "uawt0_fwac", "uawt0_pwe", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(17), 0,
			WK2928_CWKGATE_CON(1), 9, GFWAGS,
			&common_uawt0_fwacmux),
	COMPOSITE_NOMUX(0, "uawt1_pwe", "uawt_swc", 0,
			WK2928_CWKSEW_CON(14), 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(1), 10, GFWAGS),
	COMPOSITE_FWACMUX(0, "uawt1_fwac", "uawt1_pwe", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(18), 0,
			WK2928_CWKGATE_CON(1), 11, GFWAGS,
			&common_uawt1_fwacmux),
	COMPOSITE_NOMUX(0, "uawt2_pwe", "uawt_swc", 0,
			WK2928_CWKSEW_CON(15), 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(1), 12, GFWAGS),
	COMPOSITE_FWACMUX(0, "uawt2_fwac", "uawt2_pwe", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(19), 0,
			WK2928_CWKGATE_CON(1), 13, GFWAGS,
			&common_uawt2_fwacmux),
	COMPOSITE_NOMUX(0, "uawt3_pwe", "uawt_swc", 0,
			WK2928_CWKSEW_CON(16), 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(1), 14, GFWAGS),
	COMPOSITE_FWACMUX(0, "uawt3_fwac", "uawt3_pwe", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(20), 0,
			WK2928_CWKGATE_CON(1), 15, GFWAGS,
			&common_uawt3_fwacmux),

	GATE(SCWK_JTAG, "jtag", "ext_jtag", 0, WK2928_CWKGATE_CON(1), 3, GFWAGS),

	GATE(SCWK_TIMEW0, "timew0", "xin24m", 0, WK2928_CWKGATE_CON(1), 0, GFWAGS),
	GATE(SCWK_TIMEW1, "timew1", "xin24m", 0, WK2928_CWKGATE_CON(1), 1, GFWAGS),

	/* cwk_cowe_pwe gates */
	GATE(0, "cowe_dbg", "awmcwk", 0, WK2928_CWKGATE_CON(9), 0, GFWAGS),

	/* acwk_cpu gates */
	GATE(ACWK_DMA1, "acwk_dma1", "acwk_cpu", 0, WK2928_CWKGATE_CON(5), 0, GFWAGS),
	GATE(0, "acwk_intmem", "acwk_cpu", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 12, GFWAGS),
	GATE(0, "acwk_stwc_sys", "acwk_cpu", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 10, GFWAGS),

	/* hcwk_cpu gates */
	GATE(HCWK_WOM, "hcwk_wom", "hcwk_cpu", 0, WK2928_CWKGATE_CON(5), 6, GFWAGS),
	GATE(HCWK_SPDIF, "hcwk_spdif", "hcwk_cpu", 0, WK2928_CWKGATE_CON(7), 1, GFWAGS),
	GATE(0, "hcwk_cpubus", "hcwk_cpu", 0, WK2928_CWKGATE_CON(4), 8, GFWAGS),
	/* hcwk_ahb2apb is pawt of a cwk bwanch */
	GATE(0, "hcwk_vio_bus", "hcwk_cpu", 0, WK2928_CWKGATE_CON(6), 12, GFWAGS),
	GATE(HCWK_WCDC0, "hcwk_wcdc0", "hcwk_cpu", 0, WK2928_CWKGATE_CON(6), 1, GFWAGS),
	GATE(HCWK_WCDC1, "hcwk_wcdc1", "hcwk_cpu", 0, WK2928_CWKGATE_CON(6), 2, GFWAGS),
	GATE(HCWK_CIF0, "hcwk_cif0", "hcwk_cpu", 0, WK2928_CWKGATE_CON(6), 4, GFWAGS),
	GATE(HCWK_IPP, "hcwk_ipp", "hcwk_cpu", 0, WK2928_CWKGATE_CON(6), 9, GFWAGS),
	GATE(HCWK_WGA, "hcwk_wga", "hcwk_cpu", 0, WK2928_CWKGATE_CON(6), 10, GFWAGS),

	/* hcwk_pewi gates */
	GATE(0, "hcwk_pewi_axi_matwix", "hcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 0, GFWAGS),
	GATE(0, "hcwk_pewi_ahb_awbi", "hcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 6, GFWAGS),
	GATE(0, "hcwk_emem_pewi", "hcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 7, GFWAGS),
	GATE(HCWK_EMAC, "hcwk_emac", "hcwk_pewi", 0, WK2928_CWKGATE_CON(7), 0, GFWAGS),
	GATE(HCWK_NANDC0, "hcwk_nandc0", "hcwk_pewi", 0, WK2928_CWKGATE_CON(5), 9, GFWAGS),
	GATE(0, "hcwk_usb_pewi", "hcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 5, GFWAGS),
	GATE(HCWK_OTG0, "hcwk_usbotg0", "hcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(5), 13, GFWAGS),
	GATE(HCWK_HSADC, "hcwk_hsadc", "hcwk_pewi", 0, WK2928_CWKGATE_CON(7), 5, GFWAGS),
	GATE(HCWK_PIDF, "hcwk_pidfiwtew", "hcwk_pewi", 0, WK2928_CWKGATE_CON(7), 6, GFWAGS),
	GATE(HCWK_SDMMC, "hcwk_sdmmc", "hcwk_pewi", 0, WK2928_CWKGATE_CON(5), 10, GFWAGS),
	GATE(HCWK_SDIO, "hcwk_sdio", "hcwk_pewi", 0, WK2928_CWKGATE_CON(5), 11, GFWAGS),
	GATE(HCWK_EMMC, "hcwk_emmc", "hcwk_pewi", 0, WK2928_CWKGATE_CON(5), 12, GFWAGS),

	/* acwk_wcdc0_pwe gates */
	GATE(0, "acwk_vio0", "acwk_wcdc0_pwe", 0, WK2928_CWKGATE_CON(6), 13, GFWAGS),
	GATE(ACWK_WCDC0, "acwk_wcdc0", "acwk_vio0", 0, WK2928_CWKGATE_CON(6), 0, GFWAGS),
	GATE(ACWK_CIF0, "acwk_cif0", "acwk_vio0", 0, WK2928_CWKGATE_CON(6), 5, GFWAGS),
	GATE(ACWK_IPP, "acwk_ipp", "acwk_vio0", 0, WK2928_CWKGATE_CON(6), 8, GFWAGS),

	/* acwk_wcdc1_pwe gates */
	GATE(0, "acwk_vio1", "acwk_wcdc1_pwe", 0, WK2928_CWKGATE_CON(9), 5, GFWAGS),
	GATE(ACWK_WCDC1, "acwk_wcdc1", "acwk_vio1", 0, WK2928_CWKGATE_CON(6), 3, GFWAGS),
	GATE(ACWK_WGA, "acwk_wga", "acwk_vio1", 0, WK2928_CWKGATE_CON(6), 11, GFWAGS),

	/* atcwk_cpu gates */
	GATE(0, "atcwk", "atcwk_cpu", 0, WK2928_CWKGATE_CON(9), 3, GFWAGS),
	GATE(0, "twace", "atcwk_cpu", 0, WK2928_CWKGATE_CON(9), 2, GFWAGS),

	/* pcwk_cpu gates */
	GATE(PCWK_PWM01, "pcwk_pwm01", "pcwk_cpu", 0, WK2928_CWKGATE_CON(7), 10, GFWAGS),
	GATE(PCWK_TIMEW0, "pcwk_timew0", "pcwk_cpu", 0, WK2928_CWKGATE_CON(7), 7, GFWAGS),
	GATE(PCWK_I2C0, "pcwk_i2c0", "pcwk_cpu", 0, WK2928_CWKGATE_CON(8), 4, GFWAGS),
	GATE(PCWK_I2C1, "pcwk_i2c1", "pcwk_cpu", 0, WK2928_CWKGATE_CON(8), 5, GFWAGS),
	GATE(PCWK_GPIO0, "pcwk_gpio0", "pcwk_cpu", 0, WK2928_CWKGATE_CON(8), 9, GFWAGS),
	GATE(PCWK_GPIO1, "pcwk_gpio1", "pcwk_cpu", 0, WK2928_CWKGATE_CON(8), 10, GFWAGS),
	GATE(PCWK_GPIO2, "pcwk_gpio2", "pcwk_cpu", 0, WK2928_CWKGATE_CON(8), 11, GFWAGS),
	GATE(PCWK_EFUSE, "pcwk_efuse", "pcwk_cpu", 0, WK2928_CWKGATE_CON(5), 2, GFWAGS),
	GATE(PCWK_TZPC, "pcwk_tzpc", "pcwk_cpu", 0, WK2928_CWKGATE_CON(5), 3, GFWAGS),
	GATE(PCWK_DDWUPCTW, "pcwk_ddwupctw", "pcwk_cpu", 0, WK2928_CWKGATE_CON(5), 7, GFWAGS),
	GATE(PCWK_PUBW, "pcwk_ddwpubw", "pcwk_cpu", 0, WK2928_CWKGATE_CON(9), 6, GFWAGS),
	GATE(0, "pcwk_dbg", "pcwk_cpu", 0, WK2928_CWKGATE_CON(9), 1, GFWAGS),
	GATE(PCWK_GWF, "pcwk_gwf", "pcwk_cpu", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(5), 4, GFWAGS),
	GATE(PCWK_PMU, "pcwk_pmu", "pcwk_cpu", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(5), 5, GFWAGS),

	/* acwk_pewi */
	GATE(ACWK_DMA2, "acwk_dma2", "acwk_pewi", 0, WK2928_CWKGATE_CON(5), 1, GFWAGS),
	GATE(ACWK_SMC, "acwk_smc", "acwk_pewi", 0, WK2928_CWKGATE_CON(5), 8, GFWAGS),
	GATE(0, "acwk_pewi_niu", "acwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 4, GFWAGS),
	GATE(0, "acwk_cpu_pewi", "acwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 2, GFWAGS),
	GATE(0, "acwk_pewi_axi_matwix", "acwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 3, GFWAGS),

	/* pcwk_pewi gates */
	GATE(0, "pcwk_pewi_axi_matwix", "pcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 1, GFWAGS),
	GATE(PCWK_PWM23, "pcwk_pwm23", "pcwk_pewi", 0, WK2928_CWKGATE_CON(7), 11, GFWAGS),
	GATE(PCWK_WDT, "pcwk_wdt", "pcwk_pewi", 0, WK2928_CWKGATE_CON(7), 15, GFWAGS),
	GATE(PCWK_SPI0, "pcwk_spi0", "pcwk_pewi", 0, WK2928_CWKGATE_CON(7), 12, GFWAGS),
	GATE(PCWK_SPI1, "pcwk_spi1", "pcwk_pewi", 0, WK2928_CWKGATE_CON(7), 13, GFWAGS),
	GATE(PCWK_UAWT2, "pcwk_uawt2", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 2, GFWAGS),
	GATE(PCWK_UAWT3, "pcwk_uawt3", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 3, GFWAGS),
	GATE(PCWK_I2C2, "pcwk_i2c2", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 6, GFWAGS),
	GATE(PCWK_I2C3, "pcwk_i2c3", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 7, GFWAGS),
	GATE(PCWK_I2C4, "pcwk_i2c4", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 8, GFWAGS),
	GATE(PCWK_GPIO3, "pcwk_gpio3", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 12, GFWAGS),
	GATE(PCWK_SAWADC, "pcwk_sawadc", "pcwk_pewi", 0, WK2928_CWKGATE_CON(7), 14, GFWAGS),
};

PNAME(mux_wk3066_wcdc0_p)	= { "dcwk_wcdc0_swc", "xin27m" };
PNAME(mux_wk3066_wcdc1_p)	= { "dcwk_wcdc1_swc", "xin27m" };
PNAME(mux_scwk_cif1_p)		= { "cif1_pwe", "xin24m" };
PNAME(mux_scwk_i2s1_p)		= { "i2s1_pwe", "i2s1_fwac", "xin12m" };
PNAME(mux_scwk_i2s2_p)		= { "i2s2_pwe", "i2s2_fwac", "xin12m" };

static stwuct cwk_div_tabwe div_acwk_cpu_t[] = {
	{ .vaw = 0, .div = 1 },
	{ .vaw = 1, .div = 2 },
	{ .vaw = 2, .div = 3 },
	{ .vaw = 3, .div = 4 },
	{ .vaw = 4, .div = 8 },
	{ /* sentinew */ },
};

static stwuct wockchip_cwk_bwanch wk3066a_i2s0_fwacmux __initdata =
	MUX(SCWK_I2S0, "scwk_i2s0", mux_scwk_i2s0_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(2), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3066a_i2s1_fwacmux __initdata =
	MUX(SCWK_I2S1, "scwk_i2s1", mux_scwk_i2s1_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(3), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3066a_i2s2_fwacmux __initdata =
	MUX(SCWK_I2S2, "scwk_i2s2", mux_scwk_i2s2_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(4), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3066a_cwk_bwanches[] __initdata = {
	DIVTBW(0, "acwk_cpu_pwe", "awmcwk", 0,
			WK2928_CWKSEW_CON(1), 0, 3, DFWAGS | CWK_DIVIDEW_WEAD_ONWY, div_acwk_cpu_t),
	DIV(0, "pcwk_cpu_pwe", "acwk_cpu_pwe", 0,
			WK2928_CWKSEW_CON(1), 12, 2, DFWAGS | CWK_DIVIDEW_POWEW_OF_TWO
							    | CWK_DIVIDEW_WEAD_ONWY),
	DIV(0, "hcwk_cpu_pwe", "acwk_cpu_pwe", 0,
			WK2928_CWKSEW_CON(1), 8, 2, DFWAGS | CWK_DIVIDEW_POWEW_OF_TWO
							   | CWK_DIVIDEW_WEAD_ONWY),
	COMPOSITE_NOMUX(0, "hcwk_ahb2apb", "hcwk_cpu_pwe", 0,
			WK2928_CWKSEW_CON(1), 14, 2, DFWAGS | CWK_DIVIDEW_POWEW_OF_TWO
							    | CWK_DIVIDEW_WEAD_ONWY,
			WK2928_CWKGATE_CON(4), 9, GFWAGS),

	GATE(COWE_W2C, "cowe_w2c", "acwk_cpu", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(9), 4, GFWAGS),

	COMPOSITE(0, "acwk_pewi_pwe", mux_pww_swc_gpww_cpww_p, 0,
			WK2928_CWKSEW_CON(10), 15, 1, MFWAGS, 0, 5, DFWAGS,
			WK2928_CWKGATE_CON(2), 0, GFWAGS),

	COMPOSITE(0, "dcwk_wcdc0_swc", mux_pww_swc_cpww_gpww_p, 0,
			WK2928_CWKSEW_CON(27), 0, 1, MFWAGS, 8, 8, DFWAGS,
			WK2928_CWKGATE_CON(3), 1, GFWAGS),
	MUX(DCWK_WCDC0, "dcwk_wcdc0", mux_wk3066_wcdc0_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(27), 4, 1, MFWAGS),
	COMPOSITE(0, "dcwk_wcdc1_swc", mux_pww_swc_cpww_gpww_p, 0,
			WK2928_CWKSEW_CON(28), 0, 1, MFWAGS, 8, 8, DFWAGS,
			WK2928_CWKGATE_CON(3), 2, GFWAGS),
	MUX(DCWK_WCDC1, "dcwk_wcdc1", mux_wk3066_wcdc1_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(28), 4, 1, MFWAGS),

	COMPOSITE_NOMUX(0, "cif1_pwe", "cif_swc", 0,
			WK2928_CWKSEW_CON(29), 8, 5, DFWAGS,
			WK2928_CWKGATE_CON(3), 8, GFWAGS),
	MUX(SCWK_CIF1, "scwk_cif1", mux_scwk_cif1_p, 0,
			WK2928_CWKSEW_CON(29), 15, 1, MFWAGS),

	GATE(0, "pcwkin_cif1", "ext_cif1", 0,
			WK2928_CWKGATE_CON(3), 4, GFWAGS),
	INVEWTEW(0, "pcwk_cif1", "pcwkin_cif1",
			WK2928_CWKSEW_CON(30), 12, IFWAGS),

	COMPOSITE(0, "acwk_gpu_swc", mux_pww_swc_cpww_gpww_p, 0,
			WK2928_CWKSEW_CON(33), 8, 1, MFWAGS, 0, 5, DFWAGS,
			WK2928_CWKGATE_CON(3), 13, GFWAGS),
	GATE(ACWK_GPU, "acwk_gpu", "acwk_gpu_swc", 0,
			WK2928_CWKGATE_CON(5), 15, GFWAGS),

	GATE(SCWK_TIMEW2, "timew2", "xin24m", 0,
			WK2928_CWKGATE_CON(3), 2, GFWAGS),

	COMPOSITE_NOMUX(SCWK_TSADC, "scwk_tsadc", "xin24m", 0,
			WK2928_CWKSEW_CON(34), 0, 16, DFWAGS,
			WK2928_CWKGATE_CON(2), 15, GFWAGS),

	MUX(0, "i2s_swc", mux_pww_swc_gpww_cpww_p, 0,
			WK2928_CWKSEW_CON(2), 15, 1, MFWAGS),
	COMPOSITE_NOMUX(0, "i2s0_pwe", "i2s_swc", 0,
			WK2928_CWKSEW_CON(2), 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(0), 7, GFWAGS),
	COMPOSITE_FWACMUX(0, "i2s0_fwac", "i2s0_pwe", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(6), 0,
			WK2928_CWKGATE_CON(0), 8, GFWAGS,
			&wk3066a_i2s0_fwacmux),
	COMPOSITE_NOMUX(0, "i2s1_pwe", "i2s_swc", 0,
			WK2928_CWKSEW_CON(3), 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(0), 9, GFWAGS),
	COMPOSITE_FWACMUX(0, "i2s1_fwac", "i2s1_pwe", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(7), 0,
			WK2928_CWKGATE_CON(0), 10, GFWAGS,
			&wk3066a_i2s1_fwacmux),
	COMPOSITE_NOMUX(0, "i2s2_pwe", "i2s_swc", 0,
			WK2928_CWKSEW_CON(4), 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(0), 11, GFWAGS),
	COMPOSITE_FWACMUX(0, "i2s2_fwac", "i2s2_pwe", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(8), 0,
			WK2928_CWKGATE_CON(0), 12, GFWAGS,
			&wk3066a_i2s2_fwacmux),

	GATE(HCWK_I2S0, "hcwk_i2s0", "hcwk_cpu", 0, WK2928_CWKGATE_CON(7), 4, GFWAGS),
	GATE(HCWK_I2S1, "hcwk_i2s1", "hcwk_cpu", 0, WK2928_CWKGATE_CON(7), 2, GFWAGS),
	GATE(HCWK_I2S2, "hcwk_i2s2", "hcwk_cpu", 0, WK2928_CWKGATE_CON(7), 3, GFWAGS),
	GATE(HCWK_CIF1, "hcwk_cif1", "hcwk_cpu", 0, WK2928_CWKGATE_CON(6), 6, GFWAGS),
	GATE(HCWK_HDMI, "hcwk_hdmi", "hcwk_cpu", 0, WK2928_CWKGATE_CON(4), 14, GFWAGS),

	GATE(HCWK_OTG1, "hcwk_usbotg1", "hcwk_pewi", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(5), 14, GFWAGS),

	GATE(ACWK_CIF1, "acwk_cif1", "acwk_vio1", 0, WK2928_CWKGATE_CON(6), 7, GFWAGS),

	GATE(PCWK_TIMEW1, "pcwk_timew1", "pcwk_cpu", 0, WK2928_CWKGATE_CON(7), 8, GFWAGS),
	GATE(PCWK_TIMEW2, "pcwk_timew2", "pcwk_cpu", 0, WK2928_CWKGATE_CON(7), 9, GFWAGS),
	GATE(PCWK_GPIO6, "pcwk_gpio6", "pcwk_cpu", 0, WK2928_CWKGATE_CON(8), 15, GFWAGS),
	GATE(PCWK_UAWT0, "pcwk_uawt0", "pcwk_cpu", 0, WK2928_CWKGATE_CON(8), 0, GFWAGS),
	GATE(PCWK_UAWT1, "pcwk_uawt1", "pcwk_cpu", 0, WK2928_CWKGATE_CON(8), 1, GFWAGS),

	GATE(PCWK_GPIO4, "pcwk_gpio4", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 13, GFWAGS),
	GATE(PCWK_TSADC, "pcwk_tsadc", "pcwk_pewi", 0, WK2928_CWKGATE_CON(4), 13, GFWAGS),
};

static stwuct cwk_div_tabwe div_wk3188_acwk_cowe_t[] = {
	{ .vaw = 0, .div = 1 },
	{ .vaw = 1, .div = 2 },
	{ .vaw = 2, .div = 3 },
	{ .vaw = 3, .div = 4 },
	{ .vaw = 4, .div = 8 },
	{ /* sentinew */ },
};

PNAME(mux_hsicphy_p)		= { "scwk_otgphy0_480m", "scwk_otgphy1_480m",
				    "gpww", "cpww" };

static stwuct wockchip_cwk_bwanch wk3188_i2s0_fwacmux __initdata =
	MUX(SCWK_I2S0, "scwk_i2s0", mux_scwk_i2s0_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(3), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3188_cwk_bwanches[] __initdata = {
	COMPOSITE_NOMUX_DIVTBW(0, "acwk_cowe", "awmcwk", CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(1), 3, 3, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			div_wk3188_acwk_cowe_t, WK2928_CWKGATE_CON(0), 7, GFWAGS),

	/* do not souwce acwk_cpu_pwe fwom the apww, to keep compwexity down */
	COMPOSITE_NOGATE(0, "acwk_cpu_pwe", mux_acwk_cpu_p, CWK_SET_WATE_NO_WEPAWENT,
			WK2928_CWKSEW_CON(0), 5, 1, MFWAGS, 0, 5, DFWAGS),
	DIV(0, "pcwk_cpu_pwe", "acwk_cpu_pwe", 0,
			WK2928_CWKSEW_CON(1), 12, 2, DFWAGS | CWK_DIVIDEW_POWEW_OF_TWO),
	DIV(0, "hcwk_cpu_pwe", "acwk_cpu_pwe", 0,
			WK2928_CWKSEW_CON(1), 8, 2, DFWAGS | CWK_DIVIDEW_POWEW_OF_TWO),
	COMPOSITE_NOMUX(0, "hcwk_ahb2apb", "hcwk_cpu_pwe", 0,
			WK2928_CWKSEW_CON(1), 14, 2, DFWAGS | CWK_DIVIDEW_POWEW_OF_TWO,
			WK2928_CWKGATE_CON(4), 9, GFWAGS),

	GATE(COWE_W2C, "cowe_w2c", "awmcwk", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(9), 4, GFWAGS),

	COMPOSITE(0, "acwk_pewi_pwe", mux_pww_swc_cpww_gpww_p, 0,
			WK2928_CWKSEW_CON(10), 15, 1, MFWAGS, 0, 5, DFWAGS,
			WK2928_CWKGATE_CON(2), 0, GFWAGS),

	COMPOSITE(DCWK_WCDC0, "dcwk_wcdc0", mux_pww_swc_cpww_gpww_p, 0,
			WK2928_CWKSEW_CON(27), 0, 1, MFWAGS, 8, 8, DFWAGS,
			WK2928_CWKGATE_CON(3), 1, GFWAGS),
	COMPOSITE(DCWK_WCDC1, "dcwk_wcdc1", mux_pww_swc_cpww_gpww_p, 0,
			WK2928_CWKSEW_CON(28), 0, 1, MFWAGS, 8, 8, DFWAGS,
			WK2928_CWKGATE_CON(3), 2, GFWAGS),

	COMPOSITE(0, "acwk_gpu_swc", mux_pww_swc_cpww_gpww_p, 0,
			WK2928_CWKSEW_CON(34), 7, 1, MFWAGS, 0, 5, DFWAGS,
			WK2928_CWKGATE_CON(3), 15, GFWAGS),
	GATE(ACWK_GPU, "acwk_gpu", "acwk_gpu_swc", 0,
			WK2928_CWKGATE_CON(9), 7, GFWAGS),

	GATE(SCWK_TIMEW2, "timew2", "xin24m", 0, WK2928_CWKGATE_CON(3), 4, GFWAGS),
	GATE(SCWK_TIMEW3, "timew3", "xin24m", 0, WK2928_CWKGATE_CON(1), 2, GFWAGS),
	GATE(SCWK_TIMEW4, "timew4", "xin24m", 0, WK2928_CWKGATE_CON(3), 5, GFWAGS),
	GATE(SCWK_TIMEW5, "timew5", "xin24m", 0, WK2928_CWKGATE_CON(3), 8, GFWAGS),
	GATE(SCWK_TIMEW6, "timew6", "xin24m", 0, WK2928_CWKGATE_CON(3), 14, GFWAGS),

	COMPOSITE_NODIV(0, "scwk_hsicphy_480m", mux_hsicphy_p, 0,
			WK2928_CWKSEW_CON(30), 0, 2, DFWAGS,
			WK2928_CWKGATE_CON(3), 6, GFWAGS),
	DIV(0, "scwk_hsicphy_12m", "scwk_hsicphy_480m", 0,
			WK2928_CWKSEW_CON(11), 8, 6, DFWAGS),

	MUX(0, "i2s_swc", mux_pww_swc_gpww_cpww_p, 0,
			WK2928_CWKSEW_CON(2), 15, 1, MFWAGS),
	COMPOSITE_NOMUX(0, "i2s0_pwe", "i2s_swc", 0,
			WK2928_CWKSEW_CON(3), 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(0), 9, GFWAGS),
	COMPOSITE_FWACMUX(0, "i2s0_fwac", "i2s0_pwe", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(7), 0,
			WK2928_CWKGATE_CON(0), 10, GFWAGS,
			&wk3188_i2s0_fwacmux),

	GATE(HCWK_I2S0, "hcwk_i2s0", "hcwk_cpu", 0, WK2928_CWKGATE_CON(7), 2, GFWAGS),
	GATE(0, "hcwk_imem0", "hcwk_cpu", 0, WK2928_CWKGATE_CON(4), 14, GFWAGS),
	GATE(0, "hcwk_imem1", "hcwk_cpu", 0, WK2928_CWKGATE_CON(4), 15, GFWAGS),

	GATE(HCWK_OTG1, "hcwk_usbotg1", "hcwk_pewi", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(7), 3, GFWAGS),
	GATE(HCWK_HSIC, "hcwk_hsic", "hcwk_pewi", 0, WK2928_CWKGATE_CON(7), 4, GFWAGS),

	GATE(PCWK_TIMEW3, "pcwk_timew3", "pcwk_cpu", 0, WK2928_CWKGATE_CON(7), 9, GFWAGS),

	GATE(PCWK_UAWT0, "pcwk_uawt0", "hcwk_ahb2apb", 0, WK2928_CWKGATE_CON(8), 0, GFWAGS),
	GATE(PCWK_UAWT1, "pcwk_uawt1", "hcwk_ahb2apb", 0, WK2928_CWKGATE_CON(8), 1, GFWAGS),

	GATE(ACWK_GPS, "acwk_gps", "acwk_pewi", 0, WK2928_CWKGATE_CON(8), 13, GFWAGS),
};

static const chaw *const wk3188_cwiticaw_cwocks[] __initconst = {
	"acwk_cpu",
	"acwk_pewi",
	"hcwk_pewi",
	"pcwk_cpu",
	"pcwk_pewi",
	"hcwk_cpubus",
	"hcwk_vio_bus",
	"scwk_mac_wbtest",
};

static stwuct wockchip_cwk_pwovidew *__init wk3188_common_cwk_init(stwuct device_node *np)
{
	stwuct wockchip_cwk_pwovidew *ctx;
	void __iomem *weg_base;

	weg_base = of_iomap(np, 0);
	if (!weg_base) {
		pw_eww("%s: couwd not map cwu wegion\n", __func__);
		wetuwn EWW_PTW(-ENOMEM);
	}

	ctx = wockchip_cwk_init(np, weg_base, CWK_NW_CWKS);
	if (IS_EWW(ctx)) {
		pw_eww("%s: wockchip cwk init faiwed\n", __func__);
		iounmap(weg_base);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wockchip_cwk_wegistew_bwanches(ctx, common_cwk_bwanches,
				  AWWAY_SIZE(common_cwk_bwanches));

	wockchip_wegistew_softwst(np, 9, weg_base + WK2928_SOFTWST_CON(0),
				  WOCKCHIP_SOFTWST_HIWOWD_MASK);

	wockchip_wegistew_westawt_notifiew(ctx, WK2928_GWB_SWST_FST, NUWW);

	wetuwn ctx;
}

static void __init wk3066a_cwk_init(stwuct device_node *np)
{
	stwuct wockchip_cwk_pwovidew *ctx;

	ctx = wk3188_common_cwk_init(np);
	if (IS_EWW(ctx))
		wetuwn;

	wockchip_cwk_wegistew_pwws(ctx, wk3066_pww_cwks,
				   AWWAY_SIZE(wk3066_pww_cwks),
				   WK3066_GWF_SOC_STATUS);
	wockchip_cwk_wegistew_bwanches(ctx, wk3066a_cwk_bwanches,
				  AWWAY_SIZE(wk3066a_cwk_bwanches));
	wockchip_cwk_wegistew_awmcwk(ctx, AWMCWK, "awmcwk",
			mux_awmcwk_p, AWWAY_SIZE(mux_awmcwk_p),
			&wk3066_cpucwk_data, wk3066_cpucwk_wates,
			AWWAY_SIZE(wk3066_cpucwk_wates));
	wockchip_cwk_pwotect_cwiticaw(wk3188_cwiticaw_cwocks,
				      AWWAY_SIZE(wk3188_cwiticaw_cwocks));
	wockchip_cwk_of_add_pwovidew(np, ctx);
}
CWK_OF_DECWAWE(wk3066a_cwu, "wockchip,wk3066a-cwu", wk3066a_cwk_init);

static void __init wk3188a_cwk_init(stwuct device_node *np)
{
	stwuct wockchip_cwk_pwovidew *ctx;
	stwuct cwk *cwk1, *cwk2;
	unsigned wong wate;
	int wet;

	ctx = wk3188_common_cwk_init(np);
	if (IS_EWW(ctx))
		wetuwn;

	wockchip_cwk_wegistew_pwws(ctx, wk3188_pww_cwks,
				   AWWAY_SIZE(wk3188_pww_cwks),
				   WK3188_GWF_SOC_STATUS);
	wockchip_cwk_wegistew_bwanches(ctx, wk3188_cwk_bwanches,
				  AWWAY_SIZE(wk3188_cwk_bwanches));
	wockchip_cwk_wegistew_awmcwk(ctx, AWMCWK, "awmcwk",
				  mux_awmcwk_p, AWWAY_SIZE(mux_awmcwk_p),
				  &wk3188_cpucwk_data, wk3188_cpucwk_wates,
				  AWWAY_SIZE(wk3188_cpucwk_wates));

	/* wepawent acwk_cpu_pwe fwom apww */
	cwk1 = __cwk_wookup("acwk_cpu_pwe");
	cwk2 = __cwk_wookup("gpww");
	if (cwk1 && cwk2) {
		wate = cwk_get_wate(cwk1);

		wet = cwk_set_pawent(cwk1, cwk2);
		if (wet < 0)
			pw_wawn("%s: couwd not wepawent acwk_cpu_pwe to gpww\n",
				__func__);

		cwk_set_wate(cwk1, wate);
	} ewse {
		pw_wawn("%s: missing cwocks to wepawent acwk_cpu_pwe to gpww\n",
			__func__);
	}

	wockchip_cwk_pwotect_cwiticaw(wk3188_cwiticaw_cwocks,
				      AWWAY_SIZE(wk3188_cwiticaw_cwocks));
	wockchip_cwk_of_add_pwovidew(np, ctx);
}
CWK_OF_DECWAWE(wk3188a_cwu, "wockchip,wk3188a-cwu", wk3188a_cwk_init);

static void __init wk3188_cwk_init(stwuct device_node *np)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(wk3188_pww_cwks); i++) {
		stwuct wockchip_pww_cwock *pww = &wk3188_pww_cwks[i];
		stwuct wockchip_pww_wate_tabwe *wate;

		if (!pww->wate_tabwe)
			continue;

		wate = pww->wate_tabwe;
		whiwe (wate->wate > 0) {
			wate->nb = 1;
			wate++;
		}
	}

	wk3188a_cwk_init(np);
}
CWK_OF_DECWAWE(wk3188_cwu, "wockchip,wk3188-cwu", wk3188_cwk_init);
