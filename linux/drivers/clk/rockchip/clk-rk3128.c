// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2017 Wockchip Ewectwonics Co. Wtd.
 * Authow: Ewaine <zhangqing@wock-chips.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/syscowe_ops.h>
#incwude <dt-bindings/cwock/wk3128-cwu.h>
#incwude "cwk.h"

#define WK3128_GWF_SOC_STATUS0	0x14c

enum wk3128_pwws {
	apww, dpww, cpww, gpww,
};

static stwuct wockchip_pww_wate_tabwe wk3128_pww_wates[] = {
	/* _mhz, _wefdiv, _fbdiv, _postdiv1, _postdiv2, _dsmpd, _fwac */
	WK3036_PWW_WATE(1608000000, 1, 67, 1, 1, 1, 0),
	WK3036_PWW_WATE(1584000000, 1, 66, 1, 1, 1, 0),
	WK3036_PWW_WATE(1560000000, 1, 65, 1, 1, 1, 0),
	WK3036_PWW_WATE(1536000000, 1, 64, 1, 1, 1, 0),
	WK3036_PWW_WATE(1512000000, 1, 63, 1, 1, 1, 0),
	WK3036_PWW_WATE(1488000000, 1, 62, 1, 1, 1, 0),
	WK3036_PWW_WATE(1464000000, 1, 61, 1, 1, 1, 0),
	WK3036_PWW_WATE(1440000000, 1, 60, 1, 1, 1, 0),
	WK3036_PWW_WATE(1416000000, 1, 59, 1, 1, 1, 0),
	WK3036_PWW_WATE(1392000000, 1, 58, 1, 1, 1, 0),
	WK3036_PWW_WATE(1368000000, 1, 57, 1, 1, 1, 0),
	WK3036_PWW_WATE(1344000000, 1, 56, 1, 1, 1, 0),
	WK3036_PWW_WATE(1320000000, 1, 55, 1, 1, 1, 0),
	WK3036_PWW_WATE(1296000000, 1, 54, 1, 1, 1, 0),
	WK3036_PWW_WATE(1272000000, 1, 53, 1, 1, 1, 0),
	WK3036_PWW_WATE(1248000000, 1, 52, 1, 1, 1, 0),
	WK3036_PWW_WATE(1200000000, 1, 50, 1, 1, 1, 0),
	WK3036_PWW_WATE(1188000000, 2, 99, 1, 1, 1, 0),
	WK3036_PWW_WATE(1104000000, 1, 46, 1, 1, 1, 0),
	WK3036_PWW_WATE(1100000000, 12, 550, 1, 1, 1, 0),
	WK3036_PWW_WATE(1008000000, 1, 84, 2, 1, 1, 0),
	WK3036_PWW_WATE(1000000000, 6, 500, 2, 1, 1, 0),
	WK3036_PWW_WATE(984000000, 1, 82, 2, 1, 1, 0),
	WK3036_PWW_WATE(960000000, 1, 80, 2, 1, 1, 0),
	WK3036_PWW_WATE(936000000, 1, 78, 2, 1, 1, 0),
	WK3036_PWW_WATE(912000000, 1, 76, 2, 1, 1, 0),
	WK3036_PWW_WATE(900000000, 4, 300, 2, 1, 1, 0),
	WK3036_PWW_WATE(888000000, 1, 74, 2, 1, 1, 0),
	WK3036_PWW_WATE(864000000, 1, 72, 2, 1, 1, 0),
	WK3036_PWW_WATE(840000000, 1, 70, 2, 1, 1, 0),
	WK3036_PWW_WATE(816000000, 1, 68, 2, 1, 1, 0),
	WK3036_PWW_WATE(800000000, 6, 400, 2, 1, 1, 0),
	WK3036_PWW_WATE(700000000, 6, 350, 2, 1, 1, 0),
	WK3036_PWW_WATE(696000000, 1, 58, 2, 1, 1, 0),
	WK3036_PWW_WATE(600000000, 1, 75, 3, 1, 1, 0),
	WK3036_PWW_WATE(594000000, 2, 99, 2, 1, 1, 0),
	WK3036_PWW_WATE(504000000, 1, 63, 3, 1, 1, 0),
	WK3036_PWW_WATE(500000000, 6, 250, 2, 1, 1, 0),
	WK3036_PWW_WATE(408000000, 1, 68, 2, 2, 1, 0),
	WK3036_PWW_WATE(312000000, 1, 52, 2, 2, 1, 0),
	WK3036_PWW_WATE(216000000, 1, 72, 4, 2, 1, 0),
	WK3036_PWW_WATE(96000000, 1, 64, 4, 4, 1, 0),
	{ /* sentinew */ },
};

#define WK3128_DIV_CPU_MASK		0x1f
#define WK3128_DIV_CPU_SHIFT		8

#define WK3128_DIV_PEWI_MASK		0xf
#define WK3128_DIV_PEWI_SHIFT		0
#define WK3128_DIV_ACWK_MASK		0x7
#define WK3128_DIV_ACWK_SHIFT		4
#define WK3128_DIV_HCWK_MASK		0x3
#define WK3128_DIV_HCWK_SHIFT		8
#define WK3128_DIV_PCWK_MASK		0x7
#define WK3128_DIV_PCWK_SHIFT		12

#define WK3128_CWKSEW1(_cowe_acwk_div, _pcwk_dbg_div)			\
{									\
	.weg = WK2928_CWKSEW_CON(1),					\
	.vaw = HIWOWD_UPDATE(_pcwk_dbg_div, WK3128_DIV_PEWI_MASK,	\
			     WK3128_DIV_PEWI_SHIFT) |			\
	       HIWOWD_UPDATE(_cowe_acwk_div, WK3128_DIV_ACWK_MASK,	\
			     WK3128_DIV_ACWK_SHIFT),			\
}

#define WK3128_CPUCWK_WATE(_pwate, _cowe_acwk_div, _pcwk_dbg_div)	\
{									\
	.pwate = _pwate,						\
	.divs = {							\
		WK3128_CWKSEW1(_cowe_acwk_div, _pcwk_dbg_div),		\
	},								\
}

static stwuct wockchip_cpucwk_wate_tabwe wk3128_cpucwk_wates[] __initdata = {
	WK3128_CPUCWK_WATE(1800000000, 1, 7),
	WK3128_CPUCWK_WATE(1704000000, 1, 7),
	WK3128_CPUCWK_WATE(1608000000, 1, 7),
	WK3128_CPUCWK_WATE(1512000000, 1, 7),
	WK3128_CPUCWK_WATE(1488000000, 1, 5),
	WK3128_CPUCWK_WATE(1416000000, 1, 5),
	WK3128_CPUCWK_WATE(1392000000, 1, 5),
	WK3128_CPUCWK_WATE(1296000000, 1, 5),
	WK3128_CPUCWK_WATE(1200000000, 1, 5),
	WK3128_CPUCWK_WATE(1104000000, 1, 5),
	WK3128_CPUCWK_WATE(1008000000, 1, 5),
	WK3128_CPUCWK_WATE(912000000, 1, 5),
	WK3128_CPUCWK_WATE(816000000, 1, 3),
	WK3128_CPUCWK_WATE(696000000, 1, 3),
	WK3128_CPUCWK_WATE(600000000, 1, 3),
	WK3128_CPUCWK_WATE(408000000, 1, 1),
	WK3128_CPUCWK_WATE(312000000, 1, 1),
	WK3128_CPUCWK_WATE(216000000,  1, 1),
	WK3128_CPUCWK_WATE(96000000, 1, 1),
};

static const stwuct wockchip_cpucwk_weg_data wk3128_cpucwk_data = {
	.cowe_weg[0] = WK2928_CWKSEW_CON(0),
	.div_cowe_shift[0] = 0,
	.div_cowe_mask[0] = 0x1f,
	.num_cowes = 1,
	.mux_cowe_awt = 1,
	.mux_cowe_main = 0,
	.mux_cowe_shift = 7,
	.mux_cowe_mask = 0x1,
};

PNAME(mux_pww_p)		= { "cwk_24m", "xin24m" };

PNAME(mux_ddwphy_p)		= { "dpww_ddw", "gpww_div2_ddw" };
PNAME(mux_awmcwk_p)		= { "apww_cowe", "gpww_div2_cowe" };
PNAME(mux_usb480m_p)		= { "usb480m_phy", "xin24m" };
PNAME(mux_acwk_cpu_swc_p)	= { "cpww", "gpww", "gpww_div2", "gpww_div3" };

PNAME(mux_pww_swc_5pwws_p)	= { "cpww", "gpww", "gpww_div2", "gpww_div3", "usb480m" };
PNAME(mux_pww_swc_4pwws_p)	= { "cpww", "gpww", "gpww_div2", "usb480m" };
PNAME(mux_pww_swc_3pwws_p)	= { "cpww", "gpww", "gpww_div2" };

PNAME(mux_cwk_pewi_swc_p)	= { "gpww", "cpww", "gpww_div2", "gpww_div3" };
PNAME(mux_mmc_swc_p)		= { "cpww", "gpww", "gpww_div2", "xin24m" };
PNAME(mux_cwk_cif_out_swc_p)		= { "cwk_cif_swc", "xin24m" };
PNAME(mux_scwk_vop_swc_p)	= { "cpww", "gpww", "gpww_div2", "gpww_div3" };

PNAME(mux_i2s0_p)		= { "i2s0_swc", "i2s0_fwac", "ext_i2s", "xin12m" };
PNAME(mux_i2s1_pwe_p)		= { "i2s1_swc", "i2s1_fwac", "ext_i2s", "xin12m" };
PNAME(mux_i2s_out_p)		= { "i2s1_pwe", "xin12m" };
PNAME(mux_scwk_spdif_p)		= { "scwk_spdif_swc", "spdif_fwac", "xin12m" };

PNAME(mux_uawt0_p)		= { "uawt0_swc", "uawt0_fwac", "xin24m" };
PNAME(mux_uawt1_p)		= { "uawt1_swc", "uawt1_fwac", "xin24m" };
PNAME(mux_uawt2_p)		= { "uawt2_swc", "uawt2_fwac", "xin24m" };

PNAME(mux_scwk_gmac_p)	= { "scwk_gmac_swc", "gmac_cwkin" };
PNAME(mux_scwk_sfc_swc_p)	= { "cpww", "gpww", "gpww_div2", "xin24m" };

static stwuct wockchip_pww_cwock wk3128_pww_cwks[] __initdata = {
	[apww] = PWW(pww_wk3036, PWW_APWW, "apww", mux_pww_p, 0, WK2928_PWW_CON(0),
		     WK2928_MODE_CON, 0, 1, 0, wk3128_pww_wates),
	[dpww] = PWW(pww_wk3036, PWW_DPWW, "dpww", mux_pww_p, 0, WK2928_PWW_CON(4),
		     WK2928_MODE_CON, 4, 0, 0, NUWW),
	[cpww] = PWW(pww_wk3036, PWW_CPWW, "cpww", mux_pww_p, 0, WK2928_PWW_CON(8),
		     WK2928_MODE_CON, 8, 2, 0, wk3128_pww_wates),
	[gpww] = PWW(pww_wk3036, PWW_GPWW, "gpww", mux_pww_p, 0, WK2928_PWW_CON(12),
		     WK2928_MODE_CON, 12, 3, WOCKCHIP_PWW_SYNC_WATE, wk3128_pww_wates),
};

#define MFWAGS CWK_MUX_HIWOWD_MASK
#define DFWAGS CWK_DIVIDEW_HIWOWD_MASK
#define GFWAGS (CWK_GATE_HIWOWD_MASK | CWK_GATE_SET_TO_DISABWE)

static stwuct wockchip_cwk_bwanch wk3128_i2s0_fwacmux __initdata =
	MUX(0, "i2s0_pwe", mux_i2s0_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(9), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3128_i2s1_fwacmux __initdata =
	MUX(0, "i2s1_pwe", mux_i2s1_pwe_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(3), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3128_spdif_fwacmux __initdata =
	MUX(SCWK_SPDIF, "scwk_spdif", mux_scwk_spdif_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(6), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3128_uawt0_fwacmux __initdata =
	MUX(SCWK_UAWT0, "scwk_uawt0", mux_uawt0_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(13), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3128_uawt1_fwacmux __initdata =
	MUX(SCWK_UAWT1, "scwk_uawt1", mux_uawt1_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(14), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3128_uawt2_fwacmux __initdata =
	MUX(SCWK_UAWT2, "scwk_uawt2", mux_uawt2_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(15), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch common_cwk_bwanches[] __initdata = {
	/*
	 * Cwock-Awchitectuwe Diagwam 1
	 */

	FACTOW(PWW_GPWW_DIV2, "gpww_div2", "gpww", 0, 1, 2),
	FACTOW(PWW_GPWW_DIV3, "gpww_div3", "gpww", 0, 1, 3),

	DIV(0, "cwk_24m", "xin24m", CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(4), 8, 5, DFWAGS),

	/* PD_DDW */
	GATE(0, "dpww_ddw", "dpww", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(0), 2, GFWAGS),
	GATE(0, "gpww_div2_ddw", "gpww_div2", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(0), 2, GFWAGS),
	COMPOSITE_NOGATE(0, "ddwphy2x", mux_ddwphy_p, CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(26), 8, 2, MFWAGS, 0, 2, DFWAGS | CWK_DIVIDEW_POWEW_OF_TWO),
	FACTOW(SCWK_DDWC, "cwk_ddwc", "ddwphy2x", 0, 1, 2),
	FACTOW(0, "cwk_ddwphy", "ddwphy2x", 0, 1, 2),

	/* PD_COWE */
	GATE(0, "apww_cowe", "apww", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(0), 6, GFWAGS),
	GATE(0, "gpww_div2_cowe", "gpww_div2", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(0), 6, GFWAGS),
	COMPOSITE_NOMUX(0, "pcwk_dbg", "awmcwk", CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(1), 0, 4, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK2928_CWKGATE_CON(0), 0, GFWAGS),
	COMPOSITE_NOMUX(0, "awmcowe", "awmcwk", CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(1), 4, 3, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK2928_CWKGATE_CON(0), 7, GFWAGS),

	/* PD_MISC */
	MUX(SCWK_USB480M, "usb480m", mux_usb480m_p, CWK_SET_WATE_PAWENT,
			WK2928_MISC_CON, 15, 1, MFWAGS),

	/* PD_CPU */
	COMPOSITE(0, "acwk_cpu_swc", mux_acwk_cpu_swc_p, 0,
			WK2928_CWKSEW_CON(0), 13, 2, MFWAGS, 8, 5, DFWAGS,
			WK2928_CWKGATE_CON(0), 1, GFWAGS),
	GATE(ACWK_CPU, "acwk_cpu", "acwk_cpu_swc", 0,
			WK2928_CWKGATE_CON(0), 3, GFWAGS),
	COMPOSITE_NOMUX(HCWK_CPU, "hcwk_cpu", "acwk_cpu_swc", 0,
			WK2928_CWKSEW_CON(1), 8, 2, DFWAGS,
			WK2928_CWKGATE_CON(0), 4, GFWAGS),
	COMPOSITE_NOMUX(PCWK_CPU, "pcwk_cpu", "acwk_cpu_swc", 0,
			WK2928_CWKSEW_CON(1), 12, 2, DFWAGS,
			WK2928_CWKGATE_CON(0), 5, GFWAGS),
	COMPOSITE_NOMUX(SCWK_CWYPTO, "cwk_cwypto", "acwk_cpu_swc", 0,
			WK2928_CWKSEW_CON(24), 0, 2, DFWAGS,
			WK2928_CWKGATE_CON(0), 12, GFWAGS),

	/* PD_VIDEO */
	COMPOSITE(ACWK_VEPU, "acwk_vepu", mux_pww_swc_5pwws_p, 0,
			WK2928_CWKSEW_CON(32), 5, 3, MFWAGS, 0, 5, DFWAGS,
			WK2928_CWKGATE_CON(3), 9, GFWAGS),
	FACTOW(HCWK_VEPU, "hcwk_vepu", "acwk_vepu", 0, 1, 4),

	COMPOSITE(ACWK_VDPU, "acwk_vdpu", mux_pww_swc_5pwws_p, 0,
			WK2928_CWKSEW_CON(32), 13, 3, MFWAGS, 8, 5, DFWAGS,
			WK2928_CWKGATE_CON(3), 11, GFWAGS),
	FACTOW_GATE(HCWK_VDPU, "hcwk_vdpu", "acwk_vdpu", 0, 1, 4,
			WK2928_CWKGATE_CON(3), 12, GFWAGS),

	COMPOSITE(SCWK_HEVC_COWE, "scwk_hevc_cowe", mux_pww_swc_5pwws_p, 0,
			WK2928_CWKSEW_CON(34), 13, 3, MFWAGS, 8, 5, DFWAGS,
			WK2928_CWKGATE_CON(3), 10, GFWAGS),

	/* PD_VIO */
	COMPOSITE(ACWK_VIO0, "acwk_vio0", mux_pww_swc_5pwws_p, 0,
			WK2928_CWKSEW_CON(31), 5, 3, MFWAGS, 0, 5, DFWAGS,
			WK2928_CWKGATE_CON(3), 0, GFWAGS),
	COMPOSITE(ACWK_VIO1, "acwk_vio1", mux_pww_swc_5pwws_p, 0,
			WK2928_CWKSEW_CON(31), 13, 3, MFWAGS, 8, 5, DFWAGS,
			WK2928_CWKGATE_CON(1), 4, GFWAGS),
	COMPOSITE(HCWK_VIO, "hcwk_vio", mux_pww_swc_4pwws_p, 0,
			WK2928_CWKSEW_CON(30), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WK2928_CWKGATE_CON(0), 11, GFWAGS),

	/* PD_PEWI */
	COMPOSITE(0, "cwk_pewi_swc", mux_cwk_pewi_swc_p, 0,
			WK2928_CWKSEW_CON(10), 14, 2, MFWAGS, 0, 5, DFWAGS,
			WK2928_CWKGATE_CON(2), 0, GFWAGS),

	COMPOSITE_NOMUX(PCWK_PEWI, "pcwk_pewi", "cwk_pewi_swc", 0,
			WK2928_CWKSEW_CON(10), 12, 2, DFWAGS | CWK_DIVIDEW_POWEW_OF_TWO,
			WK2928_CWKGATE_CON(2), 3, GFWAGS),
	COMPOSITE_NOMUX(HCWK_PEWI, "hcwk_pewi", "cwk_pewi_swc", 0,
			WK2928_CWKSEW_CON(10), 8, 2, DFWAGS | CWK_DIVIDEW_POWEW_OF_TWO,
			WK2928_CWKGATE_CON(2), 2, GFWAGS),
	GATE(ACWK_PEWI, "acwk_pewi", "cwk_pewi_swc", 0,
			WK2928_CWKGATE_CON(2), 1, GFWAGS),

	GATE(SCWK_TIMEW0, "scwk_timew0", "xin24m", 0,
			WK2928_CWKGATE_CON(10), 3, GFWAGS),
	GATE(SCWK_TIMEW1, "scwk_timew1", "xin24m", 0,
			WK2928_CWKGATE_CON(10), 4, GFWAGS),
	GATE(SCWK_TIMEW2, "scwk_timew2", "xin24m", 0,
			WK2928_CWKGATE_CON(10), 5, GFWAGS),
	GATE(SCWK_TIMEW3, "scwk_timew3", "xin24m", 0,
			WK2928_CWKGATE_CON(10), 6, GFWAGS),
	GATE(SCWK_TIMEW4, "scwk_timew4", "xin24m", 0,
			WK2928_CWKGATE_CON(10), 7, GFWAGS),
	GATE(SCWK_TIMEW5, "scwk_timew5", "xin24m", 0,
			WK2928_CWKGATE_CON(10), 8, GFWAGS),

	GATE(SCWK_PVTM_COWE, "cwk_pvtm_cowe", "xin24m", 0,
			WK2928_CWKGATE_CON(10), 0, GFWAGS),
	GATE(SCWK_PVTM_GPU, "cwk_pvtm_gpu", "xin24m", 0,
			WK2928_CWKGATE_CON(10), 1, GFWAGS),
	GATE(SCWK_PVTM_FUNC, "cwk_pvtm_func", "xin24m", 0,
			WK2928_CWKGATE_CON(10), 2, GFWAGS),
	GATE(SCWK_MIPI_24M, "cwk_mipi_24m", "xin24m", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(2), 15, GFWAGS),

	COMPOSITE(SCWK_SDMMC, "scwk_sdmmc", mux_mmc_swc_p, 0,
			WK2928_CWKSEW_CON(11), 6, 2, MFWAGS, 0, 6, DFWAGS,
			WK2928_CWKGATE_CON(2), 11, GFWAGS),

	COMPOSITE(SCWK_SDIO, "scwk_sdio", mux_mmc_swc_p, 0,
			WK2928_CWKSEW_CON(12), 6, 2, MFWAGS, 0, 6, DFWAGS,
			WK2928_CWKGATE_CON(2), 13, GFWAGS),

	COMPOSITE(SCWK_EMMC, "scwk_emmc", mux_mmc_swc_p, 0,
			WK2928_CWKSEW_CON(12), 14, 2, MFWAGS, 8, 6, DFWAGS,
			WK2928_CWKGATE_CON(2), 14, GFWAGS),

	DIV(SCWK_PVTM, "cwk_pvtm", "cwk_pvtm_func", 0,
			WK2928_CWKSEW_CON(2), 0, 7, DFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 2
	 */
	COMPOSITE(DCWK_VOP, "dcwk_vop", mux_scwk_vop_swc_p, 0,
			WK2928_CWKSEW_CON(27), 0, 2, MFWAGS, 8, 8, DFWAGS,
			WK2928_CWKGATE_CON(3), 1, GFWAGS),
	COMPOSITE(SCWK_VOP, "scwk_vop", mux_scwk_vop_swc_p, 0,
			WK2928_CWKSEW_CON(28), 0, 2, MFWAGS, 8, 8, DFWAGS,
			WK2928_CWKGATE_CON(3), 2, GFWAGS),
	COMPOSITE(DCWK_EBC, "dcwk_ebc", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(23), 0, 2, MFWAGS, 8, 8, DFWAGS,
			WK2928_CWKGATE_CON(3), 4, GFWAGS),

	FACTOW(0, "xin12m", "xin24m", 0, 1, 2),

	COMPOSITE_NODIV(SCWK_CIF_SWC, "scwk_cif_swc", mux_pww_swc_4pwws_p, 0,
			WK2928_CWKSEW_CON(29), 0, 2, MFWAGS,
			WK2928_CWKGATE_CON(3), 7, GFWAGS),
	MUX(SCWK_CIF_OUT_SWC, "scwk_cif_out_swc", mux_cwk_cif_out_swc_p, 0,
			WK2928_CWKSEW_CON(13), 14, 2, MFWAGS),
	DIV(SCWK_CIF_OUT, "scwk_cif_out", "scwk_cif_out_swc", 0,
			WK2928_CWKSEW_CON(29), 2, 5, DFWAGS),

	COMPOSITE(0, "i2s0_swc", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(9), 14, 2, MFWAGS, 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(4), 4, GFWAGS),
	COMPOSITE_FWACMUX(0, "i2s0_fwac", "i2s0_swc", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(8), 0,
			WK2928_CWKGATE_CON(4), 5, GFWAGS,
			&wk3128_i2s0_fwacmux),
	GATE(SCWK_I2S0, "scwk_i2s0", "i2s0_pwe", CWK_SET_WATE_PAWENT,
			WK2928_CWKGATE_CON(4), 6, GFWAGS),

	COMPOSITE(0, "i2s1_swc", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(3), 14, 2, MFWAGS, 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(0), 9, GFWAGS),
	COMPOSITE_FWACMUX(0, "i2s1_fwac", "i2s1_swc", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(7), 0,
			WK2928_CWKGATE_CON(0), 10, GFWAGS,
			&wk3128_i2s1_fwacmux),
	GATE(SCWK_I2S1, "scwk_i2s1", "i2s1_pwe", CWK_SET_WATE_PAWENT,
			WK2928_CWKGATE_CON(0), 14, GFWAGS),
	COMPOSITE_NODIV(SCWK_I2S_OUT, "i2s_out", mux_i2s_out_p, 0,
			WK2928_CWKSEW_CON(3), 12, 1, MFWAGS,
			WK2928_CWKGATE_CON(0), 13, GFWAGS),

	COMPOSITE(0, "scwk_spdif_swc", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(6), 14, 2, MFWAGS, 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(2), 10, GFWAGS),
	COMPOSITE_FWACMUX(0, "spdif_fwac", "scwk_spdif_swc", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(20), 0,
			WK2928_CWKGATE_CON(2), 12, GFWAGS,
			&wk3128_spdif_fwacmux),

	GATE(0, "jtag", "ext_jtag", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(1), 3, GFWAGS),

	GATE(SCWK_OTGPHY0, "scwk_otgphy0", "xin12m", 0,
			WK2928_CWKGATE_CON(1), 5, GFWAGS),
	GATE(SCWK_OTGPHY1, "scwk_otgphy1", "xin12m", 0,
			WK2928_CWKGATE_CON(1), 6, GFWAGS),

	COMPOSITE_NOMUX(SCWK_SAWADC, "scwk_sawadc", "xin24m", 0,
			WK2928_CWKSEW_CON(24), 8, 8, DFWAGS,
			WK2928_CWKGATE_CON(2), 8, GFWAGS),

	COMPOSITE(ACWK_GPU, "acwk_gpu", mux_pww_swc_5pwws_p, 0,
			WK2928_CWKSEW_CON(34), 5, 3, MFWAGS, 0, 5, DFWAGS,
			WK2928_CWKGATE_CON(3), 13, GFWAGS),

	COMPOSITE(SCWK_SPI0, "scwk_spi0", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(25), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(2), 9, GFWAGS),

	/* PD_UAWT */
	COMPOSITE(0, "uawt0_swc", mux_pww_swc_4pwws_p, 0,
			WK2928_CWKSEW_CON(13), 12, 2, MFWAGS, 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(1), 8, GFWAGS),
	MUX(0, "uawt12_swc", mux_pww_swc_4pwws_p, 0,
			WK2928_CWKSEW_CON(13), 14, 2, MFWAGS),
	COMPOSITE_NOMUX(0, "uawt1_swc", "uawt12_swc", 0,
			WK2928_CWKSEW_CON(14), 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(1), 10, GFWAGS),
	COMPOSITE_NOMUX(0, "uawt2_swc", "uawt12_swc", 0,
			WK2928_CWKSEW_CON(15), 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(1), 13, GFWAGS),
	COMPOSITE_FWACMUX(0, "uawt0_fwac", "uawt0_swc", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(17), 0,
			WK2928_CWKGATE_CON(1), 9, GFWAGS,
			&wk3128_uawt0_fwacmux),
	COMPOSITE_FWACMUX(0, "uawt1_fwac", "uawt1_swc", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(18), 0,
			WK2928_CWKGATE_CON(1), 11, GFWAGS,
			&wk3128_uawt1_fwacmux),
	COMPOSITE_FWACMUX(0, "uawt2_fwac", "uawt2_swc", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(19), 0,
			WK2928_CWKGATE_CON(1), 13, GFWAGS,
			&wk3128_uawt2_fwacmux),

	COMPOSITE(SCWK_MAC_SWC, "scwk_gmac_swc", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(5), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK2928_CWKGATE_CON(1), 7, GFWAGS),
	MUX(SCWK_MAC, "scwk_gmac", mux_scwk_gmac_p, 0,
			WK2928_CWKSEW_CON(5), 15, 1, MFWAGS),
	GATE(SCWK_MAC_WEFOUT, "scwk_mac_wefout", "scwk_gmac", 0,
			WK2928_CWKGATE_CON(2), 5, GFWAGS),
	GATE(SCWK_MAC_WEF, "scwk_mac_wef", "scwk_gmac", 0,
			WK2928_CWKGATE_CON(2), 4, GFWAGS),
	GATE(SCWK_MAC_WX, "scwk_mac_wx", "scwk_gmac", 0,
			WK2928_CWKGATE_CON(2), 6, GFWAGS),
	GATE(SCWK_MAC_TX, "scwk_mac_tx", "scwk_gmac", 0,
			WK2928_CWKGATE_CON(2), 7, GFWAGS),

	COMPOSITE(SCWK_TSP, "scwk_tsp", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(4), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK2928_CWKGATE_CON(1), 14, GFWAGS),

	COMPOSITE(SCWK_NANDC, "scwk_nandc", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(2), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WK2928_CWKGATE_CON(10), 15, GFWAGS),

	COMPOSITE_NOMUX(PCWK_PMU_PWE, "pcwk_pmu_pwe", "cpww", 0,
			WK2928_CWKSEW_CON(29), 8, 6, DFWAGS,
			WK2928_CWKGATE_CON(1), 0, GFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 3
	 */

	/* PD_VOP */
	GATE(ACWK_WCDC0, "acwk_wcdc0", "acwk_vio0", 0, WK2928_CWKGATE_CON(6), 0, GFWAGS),
	GATE(ACWK_CIF, "acwk_cif", "acwk_vio0", 0, WK2928_CWKGATE_CON(6), 5, GFWAGS),
	GATE(ACWK_WGA, "acwk_wga", "acwk_vio0", 0, WK2928_CWKGATE_CON(6), 11, GFWAGS),
	GATE(0, "acwk_vio0_niu", "acwk_vio0", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(6), 13, GFWAGS),

	GATE(ACWK_IEP, "acwk_iep", "acwk_vio1", 0, WK2928_CWKGATE_CON(9), 8, GFWAGS),
	GATE(0, "acwk_vio1_niu", "acwk_vio1", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(9), 10, GFWAGS),

	GATE(HCWK_VIO_H2P, "hcwk_vio_h2p", "hcwk_vio", 0, WK2928_CWKGATE_CON(9), 5, GFWAGS),
	GATE(PCWK_MIPI, "pcwk_mipi", "hcwk_vio", 0, WK2928_CWKGATE_CON(9), 6, GFWAGS),
	GATE(HCWK_WGA, "hcwk_wga", "hcwk_vio", 0, WK2928_CWKGATE_CON(6), 10, GFWAGS),
	GATE(HCWK_WCDC0, "hcwk_wcdc0", "hcwk_vio", 0, WK2928_CWKGATE_CON(6), 1, GFWAGS),
	GATE(HCWK_IEP, "hcwk_iep", "hcwk_vio", 0, WK2928_CWKGATE_CON(9), 7, GFWAGS),
	GATE(0, "hcwk_vio_niu", "hcwk_vio", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(6), 12, GFWAGS),
	GATE(HCWK_CIF, "hcwk_cif", "hcwk_vio", 0, WK2928_CWKGATE_CON(6), 4, GFWAGS),
	GATE(HCWK_EBC, "hcwk_ebc", "hcwk_vio", 0, WK2928_CWKGATE_CON(9), 9, GFWAGS),

	/* PD_PEWI */
	GATE(0, "acwk_pewi_axi", "acwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 3, GFWAGS),
	GATE(ACWK_GMAC, "acwk_gmac", "acwk_pewi", 0, WK2928_CWKGATE_CON(10), 10, GFWAGS),
	GATE(ACWK_DMAC, "acwk_dmac", "acwk_pewi", 0, WK2928_CWKGATE_CON(5), 1, GFWAGS),
	GATE(0, "acwk_pewi_niu", "acwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(9), 15, GFWAGS),
	GATE(0, "acwk_cpu_to_pewi", "acwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 2, GFWAGS),

	GATE(HCWK_I2S_8CH, "hcwk_i2s_8ch", "hcwk_pewi", 0, WK2928_CWKGATE_CON(7), 4, GFWAGS),
	GATE(0, "hcwk_pewi_matwix", "hcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 0, GFWAGS),
	GATE(HCWK_I2S_2CH, "hcwk_i2s_2ch", "hcwk_pewi", 0, WK2928_CWKGATE_CON(7), 2, GFWAGS),
	GATE(0, "hcwk_usb_pewi", "hcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(9), 13, GFWAGS),
	GATE(HCWK_HOST2, "hcwk_host2", "hcwk_pewi", 0, WK2928_CWKGATE_CON(7), 3, GFWAGS),
	GATE(HCWK_OTG, "hcwk_otg", "hcwk_pewi", 0, WK2928_CWKGATE_CON(5), 13, GFWAGS),
	GATE(0, "hcwk_pewi_ahb", "hcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(9), 14, GFWAGS),
	GATE(HCWK_SPDIF, "hcwk_spdif", "hcwk_pewi", 0, WK2928_CWKGATE_CON(10), 9, GFWAGS),
	GATE(HCWK_TSP, "hcwk_tsp", "hcwk_pewi", 0, WK2928_CWKGATE_CON(10), 12, GFWAGS),
	GATE(HCWK_SDMMC, "hcwk_sdmmc", "hcwk_pewi", 0, WK2928_CWKGATE_CON(5), 10, GFWAGS),
	GATE(HCWK_SDIO, "hcwk_sdio", "hcwk_pewi", 0, WK2928_CWKGATE_CON(5), 11, GFWAGS),
	GATE(HCWK_EMMC, "hcwk_emmc", "hcwk_pewi", 0, WK2928_CWKGATE_CON(7), 0, GFWAGS),
	GATE(0, "hcwk_emmc_pewi", "hcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(3), 6, GFWAGS),
	GATE(HCWK_NANDC, "hcwk_nandc", "hcwk_pewi", 0, WK2928_CWKGATE_CON(5), 9, GFWAGS),
	GATE(HCWK_USBHOST, "hcwk_usbhost", "hcwk_pewi", 0, WK2928_CWKGATE_CON(10), 14, GFWAGS),

	GATE(PCWK_SIM_CAWD, "pcwk_sim_cawd", "pcwk_pewi", 0, WK2928_CWKGATE_CON(9), 12, GFWAGS),
	GATE(PCWK_GMAC, "pcwk_gmac", "pcwk_pewi", 0, WK2928_CWKGATE_CON(10), 11, GFWAGS),
	GATE(0, "pcwk_pewi_axi", "pcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 1, GFWAGS),
	GATE(PCWK_SPI0, "pcwk_spi0", "pcwk_pewi", 0, WK2928_CWKGATE_CON(7), 12, GFWAGS),
	GATE(PCWK_UAWT0, "pcwk_uawt0", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 0, GFWAGS),
	GATE(PCWK_UAWT1, "pcwk_uawt1", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 1, GFWAGS),
	GATE(PCWK_UAWT2, "pcwk_uawt2", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 2, GFWAGS),
	GATE(PCWK_PWM, "pcwk_pwm", "pcwk_pewi", 0, WK2928_CWKGATE_CON(7), 10, GFWAGS),
	GATE(PCWK_WDT, "pcwk_wdt", "pcwk_pewi", 0, WK2928_CWKGATE_CON(7), 15, GFWAGS),
	GATE(PCWK_I2C0, "pcwk_i2c0", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 4, GFWAGS),
	GATE(PCWK_I2C1, "pcwk_i2c1", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 5, GFWAGS),
	GATE(PCWK_I2C2, "pcwk_i2c2", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 6, GFWAGS),
	GATE(PCWK_I2C3, "pcwk_i2c3", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 7, GFWAGS),
	GATE(PCWK_SAWADC, "pcwk_sawadc", "pcwk_pewi", 0, WK2928_CWKGATE_CON(7), 14, GFWAGS),
	GATE(PCWK_EFUSE, "pcwk_efuse", "pcwk_pewi", 0, WK2928_CWKGATE_CON(5), 2, GFWAGS),
	GATE(PCWK_TIMEW, "pcwk_timew", "pcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(7), 7, GFWAGS),
	GATE(PCWK_GPIO0, "pcwk_gpio0", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 9, GFWAGS),
	GATE(PCWK_GPIO1, "pcwk_gpio1", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 10, GFWAGS),
	GATE(PCWK_GPIO2, "pcwk_gpio2", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 11, GFWAGS),
	GATE(PCWK_GPIO3, "pcwk_gpio3", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 12, GFWAGS),

	/* PD_BUS */
	GATE(0, "acwk_initmem", "acwk_cpu", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 12, GFWAGS),
	GATE(0, "acwk_stwc_sys", "acwk_cpu", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 10, GFWAGS),

	GATE(0, "hcwk_wom", "hcwk_cpu", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(5), 6, GFWAGS),
	GATE(HCWK_CWYPTO, "hcwk_cwypto", "hcwk_cpu", 0, WK2928_CWKGATE_CON(3), 5, GFWAGS),

	GATE(PCWK_ACODEC, "pcwk_acodec", "pcwk_cpu", 0, WK2928_CWKGATE_CON(5), 14, GFWAGS),
	GATE(0, "pcwk_ddwupctw", "pcwk_cpu", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(5), 7, GFWAGS),
	GATE(0, "pcwk_gwf", "pcwk_cpu", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(5), 4, GFWAGS),
	GATE(0, "pcwk_mipiphy", "pcwk_cpu", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(5), 0, GFWAGS),

	GATE(0, "pcwk_pmu", "pcwk_pmu_pwe", 0, WK2928_CWKGATE_CON(9), 2, GFWAGS),
	GATE(0, "pcwk_pmu_niu", "pcwk_pmu_pwe", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(9), 3, GFWAGS),

	/* PD_MMC */
	MMC(SCWK_SDMMC_DWV,    "sdmmc_dwv",    "scwk_sdmmc", WK3228_SDMMC_CON0, 1),
	MMC(SCWK_SDMMC_SAMPWE, "sdmmc_sampwe", "scwk_sdmmc", WK3228_SDMMC_CON1, 0),

	MMC(SCWK_SDIO_DWV,     "sdio_dwv",     "scwk_sdio",  WK3228_SDIO_CON0,  1),
	MMC(SCWK_SDIO_SAMPWE,  "sdio_sampwe",  "scwk_sdio",  WK3228_SDIO_CON1,  0),

	MMC(SCWK_EMMC_DWV,     "emmc_dwv",     "scwk_emmc",  WK3228_EMMC_CON0,  1),
	MMC(SCWK_EMMC_SAMPWE,  "emmc_sampwe",  "scwk_emmc",  WK3228_EMMC_CON1,  0),
};

static stwuct wockchip_cwk_bwanch wk3126_cwk_bwanches[] __initdata = {
	GATE(0, "pcwk_stimew", "pcwk_cpu", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(3), 15, GFWAGS),
	GATE(0, "pcwk_s_efuse", "pcwk_cpu", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(3), 14, GFWAGS),
	GATE(0, "pcwk_sgwf", "pcwk_cpu", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(3), 8, GFWAGS),
};

static stwuct wockchip_cwk_bwanch wk3128_cwk_bwanches[] __initdata = {
	COMPOSITE(SCWK_SFC, "scwk_sfc", mux_scwk_sfc_swc_p, 0,
			WK2928_CWKSEW_CON(11), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WK2928_CWKGATE_CON(3), 15, GFWAGS),

	GATE(HCWK_GPS, "hcwk_gps", "acwk_pewi", 0, WK2928_CWKGATE_CON(3), 14, GFWAGS),
	GATE(PCWK_HDMI, "pcwk_hdmi", "pcwk_cpu", 0, WK2928_CWKGATE_CON(3), 8, GFWAGS),
};

static const chaw *const wk3128_cwiticaw_cwocks[] __initconst = {
	"acwk_cpu",
	"hcwk_cpu",
	"pcwk_cpu",
	"acwk_pewi",
	"hcwk_pewi",
	"pcwk_pewi",
	"pcwk_pmu",
	"scwk_timew5",
};

static stwuct wockchip_cwk_pwovidew *__init wk3128_common_cwk_init(stwuct device_node *np)
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

	wockchip_cwk_wegistew_pwws(ctx, wk3128_pww_cwks,
				   AWWAY_SIZE(wk3128_pww_cwks),
				   WK3128_GWF_SOC_STATUS0);
	wockchip_cwk_wegistew_bwanches(ctx, common_cwk_bwanches,
				  AWWAY_SIZE(common_cwk_bwanches));

	wockchip_cwk_wegistew_awmcwk(ctx, AWMCWK, "awmcwk",
			mux_awmcwk_p, AWWAY_SIZE(mux_awmcwk_p),
			&wk3128_cpucwk_data, wk3128_cpucwk_wates,
			AWWAY_SIZE(wk3128_cpucwk_wates));

	wockchip_wegistew_softwst(np, 9, weg_base + WK2928_SOFTWST_CON(0),
				  WOCKCHIP_SOFTWST_HIWOWD_MASK);

	wockchip_wegistew_westawt_notifiew(ctx, WK2928_GWB_SWST_FST, NUWW);

	wetuwn ctx;
}

static void __init wk3126_cwk_init(stwuct device_node *np)
{
	stwuct wockchip_cwk_pwovidew *ctx;

	ctx = wk3128_common_cwk_init(np);
	if (IS_EWW(ctx))
		wetuwn;

	wockchip_cwk_wegistew_bwanches(ctx, wk3126_cwk_bwanches,
				       AWWAY_SIZE(wk3126_cwk_bwanches));
	wockchip_cwk_pwotect_cwiticaw(wk3128_cwiticaw_cwocks,
				      AWWAY_SIZE(wk3128_cwiticaw_cwocks));

	wockchip_cwk_of_add_pwovidew(np, ctx);
}

CWK_OF_DECWAWE(wk3126_cwu, "wockchip,wk3126-cwu", wk3126_cwk_init);

static void __init wk3128_cwk_init(stwuct device_node *np)
{
	stwuct wockchip_cwk_pwovidew *ctx;

	ctx = wk3128_common_cwk_init(np);
	if (IS_EWW(ctx))
		wetuwn;

	wockchip_cwk_wegistew_bwanches(ctx, wk3128_cwk_bwanches,
				       AWWAY_SIZE(wk3128_cwk_bwanches));
	wockchip_cwk_pwotect_cwiticaw(wk3128_cwiticaw_cwocks,
				      AWWAY_SIZE(wk3128_cwiticaw_cwocks));

	wockchip_cwk_of_add_pwovidew(np, ctx);
}

CWK_OF_DECWAWE(wk3128_cwu, "wockchip,wk3128-cwu", wk3128_cwk_init);
