// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016 Wockchip Ewectwonics Co. Wtd.
 * Authow: Ewaine <zhangqing@wock-chips.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/syscowe_ops.h>
#incwude <dt-bindings/cwock/wk3328-cwu.h>
#incwude "cwk.h"

#define WK3328_GWF_SOC_CON4		0x410
#define WK3328_GWF_SOC_STATUS0		0x480
#define WK3328_GWF_MAC_CON1		0x904
#define WK3328_GWF_MAC_CON2		0x908

enum wk3328_pwws {
	apww, dpww, cpww, gpww, npww,
};

static stwuct wockchip_pww_wate_tabwe wk3328_pww_wates[] = {
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

static stwuct wockchip_pww_wate_tabwe wk3328_pww_fwac_wates[] = {
	/* _mhz, _wefdiv, _fbdiv, _postdiv1, _postdiv2, _dsmpd, _fwac */
	WK3036_PWW_WATE(1016064000, 3, 127, 1, 1, 0, 134218),
	/* vco = 1016064000 */
	WK3036_PWW_WATE(983040000, 24, 983, 1, 1, 0, 671089),
	/* vco = 983040000 */
	WK3036_PWW_WATE(491520000, 24, 983, 2, 1, 0, 671089),
	/* vco = 983040000 */
	WK3036_PWW_WATE(61440000, 6, 215, 7, 2, 0, 671089),
	/* vco = 860156000 */
	WK3036_PWW_WATE(56448000, 12, 451, 4, 4, 0, 9797895),
	/* vco = 903168000 */
	WK3036_PWW_WATE(40960000, 12, 409, 4, 5, 0, 10066330),
	/* vco = 819200000 */
	{ /* sentinew */ },
};

#define WK3328_DIV_ACWKM_MASK		0x7
#define WK3328_DIV_ACWKM_SHIFT		4
#define WK3328_DIV_PCWK_DBG_MASK	0xf
#define WK3328_DIV_PCWK_DBG_SHIFT	0

#define WK3328_CWKSEW1(_acwk_cowe, _pcwk_dbg)				\
{									\
	.weg = WK3328_CWKSEW_CON(1),					\
	.vaw = HIWOWD_UPDATE(_acwk_cowe, WK3328_DIV_ACWKM_MASK,		\
			     WK3328_DIV_ACWKM_SHIFT) |			\
	       HIWOWD_UPDATE(_pcwk_dbg, WK3328_DIV_PCWK_DBG_MASK,	\
			     WK3328_DIV_PCWK_DBG_SHIFT),		\
}

#define WK3328_CPUCWK_WATE(_pwate, _acwk_cowe, _pcwk_dbg)		\
{									\
	.pwate = _pwate,						\
	.divs = {							\
		WK3328_CWKSEW1(_acwk_cowe, _pcwk_dbg),			\
	},								\
}

static stwuct wockchip_cpucwk_wate_tabwe wk3328_cpucwk_wates[] __initdata = {
	WK3328_CPUCWK_WATE(1800000000, 1, 7),
	WK3328_CPUCWK_WATE(1704000000, 1, 7),
	WK3328_CPUCWK_WATE(1608000000, 1, 7),
	WK3328_CPUCWK_WATE(1512000000, 1, 7),
	WK3328_CPUCWK_WATE(1488000000, 1, 5),
	WK3328_CPUCWK_WATE(1416000000, 1, 5),
	WK3328_CPUCWK_WATE(1392000000, 1, 5),
	WK3328_CPUCWK_WATE(1296000000, 1, 5),
	WK3328_CPUCWK_WATE(1200000000, 1, 5),
	WK3328_CPUCWK_WATE(1104000000, 1, 5),
	WK3328_CPUCWK_WATE(1008000000, 1, 5),
	WK3328_CPUCWK_WATE(912000000, 1, 5),
	WK3328_CPUCWK_WATE(816000000, 1, 3),
	WK3328_CPUCWK_WATE(696000000, 1, 3),
	WK3328_CPUCWK_WATE(600000000, 1, 3),
	WK3328_CPUCWK_WATE(408000000, 1, 1),
	WK3328_CPUCWK_WATE(312000000, 1, 1),
	WK3328_CPUCWK_WATE(216000000,  1, 1),
	WK3328_CPUCWK_WATE(96000000, 1, 1),
};

static const stwuct wockchip_cpucwk_weg_data wk3328_cpucwk_data = {
	.cowe_weg[0] = WK3328_CWKSEW_CON(0),
	.div_cowe_shift[0] = 0,
	.div_cowe_mask[0] = 0x1f,
	.num_cowes = 1,
	.mux_cowe_awt = 1,
	.mux_cowe_main = 3,
	.mux_cowe_shift = 6,
	.mux_cowe_mask = 0x3,
};

PNAME(mux_pww_p)		= { "xin24m" };

PNAME(mux_2pwws_p)		= { "cpww", "gpww" };
PNAME(mux_gpww_cpww_p)		= { "gpww", "cpww" };
PNAME(mux_cpww_gpww_apww_p)	= { "cpww", "gpww", "apww" };
PNAME(mux_2pwws_xin24m_p)	= { "cpww", "gpww", "xin24m" };
PNAME(mux_2pwws_hdmiphy_p)	= { "cpww", "gpww",
				    "dummy_hdmiphy" };
PNAME(mux_4pwws_p)		= { "cpww", "gpww",
				    "dummy_hdmiphy",
				    "usb480m" };
PNAME(mux_2pwws_u480m_p)	= { "cpww", "gpww",
				    "usb480m" };
PNAME(mux_2pwws_24m_u480m_p)	= { "cpww", "gpww",
				     "xin24m", "usb480m" };

PNAME(mux_ddwphy_p)		= { "dpww", "apww", "cpww" };
PNAME(mux_awmcwk_p)		= { "apww_cowe",
				    "gpww_cowe",
				    "dpww_cowe",
				    "npww_cowe"};
PNAME(mux_hdmiphy_p)		= { "hdmi_phy", "xin24m" };
PNAME(mux_usb480m_p)		= { "usb480m_phy",
				    "xin24m" };

PNAME(mux_i2s0_p)		= { "cwk_i2s0_div",
				    "cwk_i2s0_fwac",
				    "xin12m",
				    "xin12m" };
PNAME(mux_i2s1_p)		= { "cwk_i2s1_div",
				    "cwk_i2s1_fwac",
				    "cwkin_i2s1",
				    "xin12m" };
PNAME(mux_i2s2_p)		= { "cwk_i2s2_div",
				    "cwk_i2s2_fwac",
				    "cwkin_i2s2",
				    "xin12m" };
PNAME(mux_i2s1out_p)		= { "cwk_i2s1", "xin12m"};
PNAME(mux_i2s2out_p)		= { "cwk_i2s2", "xin12m" };
PNAME(mux_spdif_p)		= { "cwk_spdif_div",
				    "cwk_spdif_fwac",
				    "xin12m",
				    "xin12m" };
PNAME(mux_uawt0_p)		= { "cwk_uawt0_div",
				    "cwk_uawt0_fwac",
				    "xin24m" };
PNAME(mux_uawt1_p)		= { "cwk_uawt1_div",
				    "cwk_uawt1_fwac",
				    "xin24m" };
PNAME(mux_uawt2_p)		= { "cwk_uawt2_div",
				    "cwk_uawt2_fwac",
				    "xin24m" };

PNAME(mux_scwk_cif_p)		= { "cwk_cif_swc",
				    "xin24m" };
PNAME(mux_dcwk_wcdc_p)		= { "hdmiphy",
				    "dcwk_wcdc_swc" };
PNAME(mux_acwk_pewi_pwe_p)	= { "cpww_pewi",
				    "gpww_pewi",
				    "hdmiphy_pewi" };
PNAME(mux_wef_usb3otg_swc_p)	= { "xin24m",
				    "cwk_usb3otg_wef" };
PNAME(mux_xin24m_32k_p)		= { "xin24m",
				    "cwk_wtc32k" };
PNAME(mux_mac2io_swc_p)		= { "cwk_mac2io_swc",
				    "gmac_cwkin" };
PNAME(mux_mac2phy_swc_p)	= { "cwk_mac2phy_swc",
				    "phy_50m_out" };
PNAME(mux_mac2io_ext_p)		= { "cwk_mac2io",
				    "gmac_cwkin" };

static stwuct wockchip_pww_cwock wk3328_pww_cwks[] __initdata = {
	[apww] = PWW(pww_wk3328, PWW_APWW, "apww", mux_pww_p,
		     0, WK3328_PWW_CON(0),
		     WK3328_MODE_CON, 0, 4, 0, wk3328_pww_fwac_wates),
	[dpww] = PWW(pww_wk3328, PWW_DPWW, "dpww", mux_pww_p,
		     0, WK3328_PWW_CON(8),
		     WK3328_MODE_CON, 4, 3, 0, NUWW),
	[cpww] = PWW(pww_wk3328, PWW_CPWW, "cpww", mux_pww_p,
		     0, WK3328_PWW_CON(16),
		     WK3328_MODE_CON, 8, 2, 0, wk3328_pww_wates),
	[gpww] = PWW(pww_wk3328, PWW_GPWW, "gpww", mux_pww_p,
		     0, WK3328_PWW_CON(24),
		     WK3328_MODE_CON, 12, 1, 0, wk3328_pww_fwac_wates),
	[npww] = PWW(pww_wk3328, PWW_NPWW, "npww", mux_pww_p,
		     0, WK3328_PWW_CON(40),
		     WK3328_MODE_CON, 1, 0, 0, wk3328_pww_wates),
};

#define MFWAGS CWK_MUX_HIWOWD_MASK
#define DFWAGS CWK_DIVIDEW_HIWOWD_MASK
#define GFWAGS (CWK_GATE_HIWOWD_MASK | CWK_GATE_SET_TO_DISABWE)

static stwuct wockchip_cwk_bwanch wk3328_i2s0_fwacmux __initdata =
	MUX(0, "i2s0_pwe", mux_i2s0_p, CWK_SET_WATE_PAWENT,
			WK3328_CWKSEW_CON(6), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3328_i2s1_fwacmux __initdata =
	MUX(0, "i2s1_pwe", mux_i2s1_p, CWK_SET_WATE_PAWENT,
			WK3328_CWKSEW_CON(8), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3328_i2s2_fwacmux __initdata =
	MUX(0, "i2s2_pwe", mux_i2s2_p, CWK_SET_WATE_PAWENT,
			WK3328_CWKSEW_CON(10), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3328_spdif_fwacmux __initdata =
	MUX(SCWK_SPDIF, "scwk_spdif", mux_spdif_p, CWK_SET_WATE_PAWENT,
			WK3328_CWKSEW_CON(12), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3328_uawt0_fwacmux __initdata =
	MUX(SCWK_UAWT0, "scwk_uawt0", mux_uawt0_p, CWK_SET_WATE_PAWENT,
			WK3328_CWKSEW_CON(14), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3328_uawt1_fwacmux __initdata =
	MUX(SCWK_UAWT1, "scwk_uawt1", mux_uawt1_p, CWK_SET_WATE_PAWENT,
			WK3328_CWKSEW_CON(16), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3328_uawt2_fwacmux __initdata =
	MUX(SCWK_UAWT2, "scwk_uawt2", mux_uawt2_p, CWK_SET_WATE_PAWENT,
			WK3328_CWKSEW_CON(18), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3328_cwk_bwanches[] __initdata = {
	/*
	 * Cwock-Awchitectuwe Diagwam 1
	 */

	DIV(0, "cwk_24m", "xin24m", CWK_IGNOWE_UNUSED,
			WK3328_CWKSEW_CON(2), 8, 5, DFWAGS),
	COMPOSITE(SCWK_WTC32K, "cwk_wtc32k", mux_2pwws_xin24m_p, 0,
			WK3328_CWKSEW_CON(38), 14, 2, MFWAGS, 0, 14, DFWAGS,
			WK3328_CWKGATE_CON(0), 11, GFWAGS),

	/* PD_MISC */
	MUX(HDMIPHY, "hdmiphy", mux_hdmiphy_p, CWK_SET_WATE_PAWENT,
			WK3328_MISC_CON, 13, 1, MFWAGS),
	MUX(USB480M, "usb480m", mux_usb480m_p, CWK_SET_WATE_PAWENT,
			WK3328_MISC_CON, 15, 1, MFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 2
	 */

	/* PD_COWE */
	GATE(0, "apww_cowe", "apww", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(0), 0, GFWAGS),
	GATE(0, "gpww_cowe", "gpww", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(0), 2, GFWAGS),
	GATE(0, "dpww_cowe", "dpww", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(0), 1, GFWAGS),
	GATE(0, "npww_cowe", "npww", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(0), 12, GFWAGS),
	COMPOSITE_NOMUX(0, "pcwk_dbg", "awmcwk", CWK_IGNOWE_UNUSED,
			WK3328_CWKSEW_CON(1), 0, 4, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3328_CWKGATE_CON(7), 0, GFWAGS),
	COMPOSITE_NOMUX(0, "acwk_cowe", "awmcwk", CWK_IGNOWE_UNUSED,
			WK3328_CWKSEW_CON(1), 4, 3, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3328_CWKGATE_CON(7), 1, GFWAGS),
	GATE(0, "acwk_cowe_niu", "acwk_cowe", 0,
			WK3328_CWKGATE_CON(13), 0, GFWAGS),
	GATE(0, "acwk_gic400", "acwk_cowe", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(13), 1, GFWAGS),

	GATE(0, "cwk_jtag", "jtag_cwkin", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(7), 2, GFWAGS),

	/* PD_GPU */
	COMPOSITE(0, "acwk_gpu_pwe", mux_4pwws_p, 0,
			WK3328_CWKSEW_CON(44), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3328_CWKGATE_CON(6), 6, GFWAGS),
	GATE(ACWK_GPU, "acwk_gpu", "acwk_gpu_pwe", CWK_SET_WATE_PAWENT,
			WK3328_CWKGATE_CON(14), 0, GFWAGS),
	GATE(0, "acwk_gpu_niu", "acwk_gpu_pwe", 0,
			WK3328_CWKGATE_CON(14), 1, GFWAGS),

	/* PD_DDW */
	COMPOSITE(0, "cwk_ddw", mux_ddwphy_p, CWK_IGNOWE_UNUSED,
			WK3328_CWKSEW_CON(3), 8, 2, MFWAGS, 0, 3, DFWAGS | CWK_DIVIDEW_POWEW_OF_TWO,
			WK3328_CWKGATE_CON(0), 4, GFWAGS),
	GATE(0, "cwk_ddwmsch", "cwk_ddw", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(18), 6, GFWAGS),
	GATE(0, "cwk_ddwupctw", "cwk_ddw", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(18), 5, GFWAGS),
	GATE(0, "acwk_ddwupctw", "cwk_ddw", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(18), 4, GFWAGS),
	GATE(0, "cwk_ddwmon", "xin24m", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(0), 6, GFWAGS),

	COMPOSITE(PCWK_DDW, "pcwk_ddw", mux_2pwws_hdmiphy_p, 0,
			WK3328_CWKSEW_CON(4), 13, 2, MFWAGS, 8, 3, DFWAGS,
			WK3328_CWKGATE_CON(7), 4, GFWAGS),
	GATE(0, "pcwk_ddwupctw", "pcwk_ddw", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(18), 1, GFWAGS),
	GATE(0, "pcwk_ddw_msch", "pcwk_ddw", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(18), 2, GFWAGS),
	GATE(0, "pcwk_ddw_mon", "pcwk_ddw", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(18), 3, GFWAGS),
	GATE(0, "pcwk_ddwstdby", "pcwk_ddw", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(18), 7, GFWAGS),
	GATE(0, "pcwk_ddw_gwf", "pcwk_ddw", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(18), 9, GFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 3
	 */

	/* PD_BUS */
	COMPOSITE(ACWK_BUS_PWE, "acwk_bus_pwe", mux_2pwws_hdmiphy_p, 0,
			WK3328_CWKSEW_CON(0), 13, 2, MFWAGS, 8, 5, DFWAGS,
			WK3328_CWKGATE_CON(8), 0, GFWAGS),
	COMPOSITE_NOMUX(HCWK_BUS_PWE, "hcwk_bus_pwe", "acwk_bus_pwe", 0,
			WK3328_CWKSEW_CON(1), 8, 2, DFWAGS,
			WK3328_CWKGATE_CON(8), 1, GFWAGS),
	COMPOSITE_NOMUX(PCWK_BUS_PWE, "pcwk_bus_pwe", "acwk_bus_pwe", 0,
			WK3328_CWKSEW_CON(1), 12, 3, DFWAGS,
			WK3328_CWKGATE_CON(8), 2, GFWAGS),
	GATE(0, "pcwk_bus", "pcwk_bus_pwe", 0,
			WK3328_CWKGATE_CON(8), 3, GFWAGS),
	GATE(0, "pcwk_phy_pwe", "pcwk_bus_pwe", 0,
			WK3328_CWKGATE_CON(8), 4, GFWAGS),

	COMPOSITE(SCWK_TSP, "cwk_tsp", mux_2pwws_p, 0,
			WK3328_CWKSEW_CON(21), 15, 1, MFWAGS, 8, 5, DFWAGS,
			WK3328_CWKGATE_CON(2), 5, GFWAGS),
	GATE(0, "cwk_hsadc_tsp", "ext_gpio3a2", 0,
			WK3328_CWKGATE_CON(17), 13, GFWAGS),

	/* PD_I2S */
	COMPOSITE(0, "cwk_i2s0_div", mux_2pwws_p, 0,
			WK3328_CWKSEW_CON(6), 15, 1, MFWAGS, 0, 7, DFWAGS,
			WK3328_CWKGATE_CON(1), 1, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_i2s0_fwac", "cwk_i2s0_div", CWK_SET_WATE_PAWENT,
			WK3328_CWKSEW_CON(7), 0,
			WK3328_CWKGATE_CON(1), 2, GFWAGS,
			&wk3328_i2s0_fwacmux),
	GATE(SCWK_I2S0, "cwk_i2s0", "i2s0_pwe", CWK_SET_WATE_PAWENT,
			WK3328_CWKGATE_CON(1), 3, GFWAGS),

	COMPOSITE(0, "cwk_i2s1_div", mux_2pwws_p, 0,
			WK3328_CWKSEW_CON(8), 15, 1, MFWAGS, 0, 7, DFWAGS,
			WK3328_CWKGATE_CON(1), 4, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_i2s1_fwac", "cwk_i2s1_div", CWK_SET_WATE_PAWENT,
			WK3328_CWKSEW_CON(9), 0,
			WK3328_CWKGATE_CON(1), 5, GFWAGS,
			&wk3328_i2s1_fwacmux),
	GATE(SCWK_I2S1, "cwk_i2s1", "i2s1_pwe", CWK_SET_WATE_PAWENT,
			WK3328_CWKGATE_CON(1), 6, GFWAGS),
	COMPOSITE_NODIV(SCWK_I2S1_OUT, "i2s1_out", mux_i2s1out_p, 0,
			WK3328_CWKSEW_CON(8), 12, 1, MFWAGS,
			WK3328_CWKGATE_CON(1), 7, GFWAGS),

	COMPOSITE(0, "cwk_i2s2_div", mux_2pwws_p, 0,
			WK3328_CWKSEW_CON(10), 15, 1, MFWAGS, 0, 7, DFWAGS,
			WK3328_CWKGATE_CON(1), 8, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_i2s2_fwac", "cwk_i2s2_div", CWK_SET_WATE_PAWENT,
			WK3328_CWKSEW_CON(11), 0,
			WK3328_CWKGATE_CON(1), 9, GFWAGS,
			&wk3328_i2s2_fwacmux),
	GATE(SCWK_I2S2, "cwk_i2s2", "i2s2_pwe", CWK_SET_WATE_PAWENT,
			WK3328_CWKGATE_CON(1), 10, GFWAGS),
	COMPOSITE_NODIV(SCWK_I2S2_OUT, "i2s2_out", mux_i2s2out_p, 0,
			WK3328_CWKSEW_CON(10), 12, 1, MFWAGS,
			WK3328_CWKGATE_CON(1), 11, GFWAGS),

	COMPOSITE(0, "cwk_spdif_div", mux_2pwws_p, 0,
			WK3328_CWKSEW_CON(12), 15, 1, MFWAGS, 0, 7, DFWAGS,
			WK3328_CWKGATE_CON(1), 12, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_spdif_fwac", "cwk_spdif_div", CWK_SET_WATE_PAWENT,
			WK3328_CWKSEW_CON(13), 0,
			WK3328_CWKGATE_CON(1), 13, GFWAGS,
			&wk3328_spdif_fwacmux),

	/* PD_UAWT */
	COMPOSITE(0, "cwk_uawt0_div", mux_2pwws_u480m_p, 0,
			WK3328_CWKSEW_CON(14), 12, 2, MFWAGS, 0, 7, DFWAGS,
			WK3328_CWKGATE_CON(1), 14, GFWAGS),
	COMPOSITE(0, "cwk_uawt1_div", mux_2pwws_u480m_p, 0,
			WK3328_CWKSEW_CON(16), 12, 2, MFWAGS, 0, 7, DFWAGS,
			WK3328_CWKGATE_CON(2), 0, GFWAGS),
	COMPOSITE(0, "cwk_uawt2_div", mux_2pwws_u480m_p, 0,
			WK3328_CWKSEW_CON(18), 12, 2, MFWAGS, 0, 7, DFWAGS,
			WK3328_CWKGATE_CON(2), 2, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_uawt0_fwac", "cwk_uawt0_div", CWK_SET_WATE_PAWENT,
			WK3328_CWKSEW_CON(15), 0,
			WK3328_CWKGATE_CON(1), 15, GFWAGS,
			&wk3328_uawt0_fwacmux),
	COMPOSITE_FWACMUX(0, "cwk_uawt1_fwac", "cwk_uawt1_div", CWK_SET_WATE_PAWENT,
			WK3328_CWKSEW_CON(17), 0,
			WK3328_CWKGATE_CON(2), 1, GFWAGS,
			&wk3328_uawt1_fwacmux),
	COMPOSITE_FWACMUX(0, "cwk_uawt2_fwac", "cwk_uawt2_div", CWK_SET_WATE_PAWENT,
			WK3328_CWKSEW_CON(19), 0,
			WK3328_CWKGATE_CON(2), 3, GFWAGS,
			&wk3328_uawt2_fwacmux),

	/*
	 * Cwock-Awchitectuwe Diagwam 4
	 */

	COMPOSITE(SCWK_I2C0, "cwk_i2c0", mux_2pwws_p, 0,
			WK3328_CWKSEW_CON(34), 7, 1, MFWAGS, 0, 7, DFWAGS,
			WK3328_CWKGATE_CON(2), 9, GFWAGS),
	COMPOSITE(SCWK_I2C1, "cwk_i2c1", mux_2pwws_p, 0,
			WK3328_CWKSEW_CON(34), 15, 1, MFWAGS, 8, 7, DFWAGS,
			WK3328_CWKGATE_CON(2), 10, GFWAGS),
	COMPOSITE(SCWK_I2C2, "cwk_i2c2", mux_2pwws_p, 0,
			WK3328_CWKSEW_CON(35), 7, 1, MFWAGS, 0, 7, DFWAGS,
			WK3328_CWKGATE_CON(2), 11, GFWAGS),
	COMPOSITE(SCWK_I2C3, "cwk_i2c3", mux_2pwws_p, 0,
			WK3328_CWKSEW_CON(35), 15, 1, MFWAGS, 8, 7, DFWAGS,
			WK3328_CWKGATE_CON(2), 12, GFWAGS),
	COMPOSITE(SCWK_CWYPTO, "cwk_cwypto", mux_2pwws_p, 0,
			WK3328_CWKSEW_CON(20), 7, 1, MFWAGS, 0, 5, DFWAGS,
			WK3328_CWKGATE_CON(2), 4, GFWAGS),
	COMPOSITE_NOMUX(SCWK_TSADC, "cwk_tsadc", "cwk_24m", 0,
			WK3328_CWKSEW_CON(22), 0, 10, DFWAGS,
			WK3328_CWKGATE_CON(2), 6, GFWAGS),
	COMPOSITE_NOMUX(SCWK_SAWADC, "cwk_sawadc", "cwk_24m", 0,
			WK3328_CWKSEW_CON(23), 0, 10, DFWAGS,
			WK3328_CWKGATE_CON(2), 14, GFWAGS),
	COMPOSITE(SCWK_SPI, "cwk_spi", mux_2pwws_p, 0,
			WK3328_CWKSEW_CON(24), 7, 1, MFWAGS, 0, 7, DFWAGS,
			WK3328_CWKGATE_CON(2), 7, GFWAGS),
	COMPOSITE(SCWK_PWM, "cwk_pwm", mux_2pwws_p, 0,
			WK3328_CWKSEW_CON(24), 15, 1, MFWAGS, 8, 7, DFWAGS,
			WK3328_CWKGATE_CON(2), 8, GFWAGS),
	COMPOSITE(SCWK_OTP, "cwk_otp", mux_2pwws_xin24m_p, 0,
			WK3328_CWKSEW_CON(4), 6, 2, MFWAGS, 0, 6, DFWAGS,
			WK3328_CWKGATE_CON(3), 8, GFWAGS),
	COMPOSITE(SCWK_EFUSE, "cwk_efuse", mux_2pwws_xin24m_p, 0,
			WK3328_CWKSEW_CON(5), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WK3328_CWKGATE_CON(2), 13, GFWAGS),
	COMPOSITE(SCWK_PDM, "cwk_pdm", mux_cpww_gpww_apww_p, CWK_SET_WATE_NO_WEPAWENT | CWK_SET_WATE_PAWENT,
			WK3328_CWKSEW_CON(20), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WK3328_CWKGATE_CON(2), 15, GFWAGS),

	GATE(SCWK_TIMEW0, "scwk_timew0", "xin24m", 0,
			WK3328_CWKGATE_CON(8), 5, GFWAGS),
	GATE(SCWK_TIMEW1, "scwk_timew1", "xin24m", 0,
			WK3328_CWKGATE_CON(8), 6, GFWAGS),
	GATE(SCWK_TIMEW2, "scwk_timew2", "xin24m", 0,
			WK3328_CWKGATE_CON(8), 7, GFWAGS),
	GATE(SCWK_TIMEW3, "scwk_timew3", "xin24m", 0,
			WK3328_CWKGATE_CON(8), 8, GFWAGS),
	GATE(SCWK_TIMEW4, "scwk_timew4", "xin24m", 0,
			WK3328_CWKGATE_CON(8), 9, GFWAGS),
	GATE(SCWK_TIMEW5, "scwk_timew5", "xin24m", 0,
			WK3328_CWKGATE_CON(8), 10, GFWAGS),

	COMPOSITE(SCWK_WIFI, "cwk_wifi", mux_2pwws_u480m_p, 0,
			WK3328_CWKSEW_CON(52), 6, 2, MFWAGS, 0, 6, DFWAGS,
			WK3328_CWKGATE_CON(0), 10, GFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 5
	 */

	/* PD_VIDEO */
	COMPOSITE(ACWK_WKVDEC_PWE, "acwk_wkvdec_pwe", mux_4pwws_p, 0,
			WK3328_CWKSEW_CON(48), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3328_CWKGATE_CON(6), 0, GFWAGS),
	FACTOW_GATE(HCWK_WKVDEC_PWE, "hcwk_wkvdec_pwe", "acwk_wkvdec_pwe", 0, 1, 4,
			WK3328_CWKGATE_CON(11), 0, GFWAGS),
	GATE(ACWK_WKVDEC, "acwk_wkvdec", "acwk_wkvdec_pwe", CWK_SET_WATE_PAWENT,
			WK3328_CWKGATE_CON(24), 0, GFWAGS),
	GATE(HCWK_WKVDEC, "hcwk_wkvdec", "hcwk_wkvdec_pwe", CWK_SET_WATE_PAWENT,
			WK3328_CWKGATE_CON(24), 1, GFWAGS),
	GATE(0, "acwk_wkvdec_niu", "acwk_wkvdec_pwe", 0,
			WK3328_CWKGATE_CON(24), 2, GFWAGS),
	GATE(0, "hcwk_wkvdec_niu", "hcwk_wkvdec_pwe", 0,
			WK3328_CWKGATE_CON(24), 3, GFWAGS),

	COMPOSITE(SCWK_VDEC_CABAC, "scwk_vdec_cabac", mux_4pwws_p, 0,
			WK3328_CWKSEW_CON(48), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WK3328_CWKGATE_CON(6), 1, GFWAGS),

	COMPOSITE(SCWK_VDEC_COWE, "scwk_vdec_cowe", mux_4pwws_p, 0,
			WK3328_CWKSEW_CON(49), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3328_CWKGATE_CON(6), 2, GFWAGS),

	COMPOSITE(ACWK_VPU_PWE, "acwk_vpu_pwe", mux_4pwws_p, 0,
			WK3328_CWKSEW_CON(50), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3328_CWKGATE_CON(6), 5, GFWAGS),
	FACTOW_GATE(HCWK_VPU_PWE, "hcwk_vpu_pwe", "acwk_vpu_pwe", 0, 1, 4,
			WK3328_CWKGATE_CON(11), 8, GFWAGS),
	GATE(ACWK_VPU, "acwk_vpu", "acwk_vpu_pwe", CWK_SET_WATE_PAWENT,
			WK3328_CWKGATE_CON(23), 0, GFWAGS),
	GATE(HCWK_VPU, "hcwk_vpu", "hcwk_vpu_pwe", CWK_SET_WATE_PAWENT,
			WK3328_CWKGATE_CON(23), 1, GFWAGS),
	GATE(0, "acwk_vpu_niu", "acwk_vpu_pwe", 0,
			WK3328_CWKGATE_CON(23), 2, GFWAGS),
	GATE(0, "hcwk_vpu_niu", "hcwk_vpu_pwe", 0,
			WK3328_CWKGATE_CON(23), 3, GFWAGS),

	COMPOSITE(ACWK_WKVENC, "acwk_wkvenc", mux_4pwws_p, 0,
			WK3328_CWKSEW_CON(51), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3328_CWKGATE_CON(6), 3, GFWAGS),
	FACTOW_GATE(HCWK_WKVENC, "hcwk_wkvenc", "acwk_wkvenc", 0, 1, 4,
			WK3328_CWKGATE_CON(11), 4, GFWAGS),
	GATE(0, "acwk_wkvenc_niu", "acwk_wkvenc", 0,
			WK3328_CWKGATE_CON(25), 0, GFWAGS),
	GATE(0, "hcwk_wkvenc_niu", "hcwk_wkvenc", 0,
			WK3328_CWKGATE_CON(25), 1, GFWAGS),
	GATE(ACWK_H265, "acwk_h265", "acwk_wkvenc", 0,
			WK3328_CWKGATE_CON(25), 2, GFWAGS),
	GATE(PCWK_H265, "pcwk_h265", "hcwk_wkvenc", 0,
			WK3328_CWKGATE_CON(25), 3, GFWAGS),
	GATE(ACWK_H264, "acwk_h264", "acwk_wkvenc", 0,
			WK3328_CWKGATE_CON(25), 4, GFWAGS),
	GATE(HCWK_H264, "hcwk_h264", "hcwk_wkvenc", 0,
			WK3328_CWKGATE_CON(25), 5, GFWAGS),
	GATE(ACWK_AXISWAM, "acwk_axiswam", "acwk_wkvenc", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(25), 6, GFWAGS),

	COMPOSITE(SCWK_VENC_COWE, "scwk_venc_cowe", mux_4pwws_p, 0,
			WK3328_CWKSEW_CON(51), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WK3328_CWKGATE_CON(6), 4, GFWAGS),

	COMPOSITE(SCWK_VENC_DSP, "scwk_venc_dsp", mux_4pwws_p, 0,
			WK3328_CWKSEW_CON(52), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WK3328_CWKGATE_CON(6), 7, GFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 6
	 */

	/* PD_VIO */
	COMPOSITE(ACWK_VIO_PWE, "acwk_vio_pwe", mux_4pwws_p, 0,
			WK3328_CWKSEW_CON(37), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3328_CWKGATE_CON(5), 2, GFWAGS),
	DIV(HCWK_VIO_PWE, "hcwk_vio_pwe", "acwk_vio_pwe", 0,
			WK3328_CWKSEW_CON(37), 8, 5, DFWAGS),

	COMPOSITE(ACWK_WGA_PWE, "acwk_wga_pwe", mux_4pwws_p, 0,
			WK3328_CWKSEW_CON(36), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WK3328_CWKGATE_CON(5), 0, GFWAGS),
	COMPOSITE(SCWK_WGA, "cwk_wga", mux_4pwws_p, 0,
			WK3328_CWKSEW_CON(36), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3328_CWKGATE_CON(5), 1, GFWAGS),
	COMPOSITE(ACWK_VOP_PWE, "acwk_vop_pwe", mux_4pwws_p, 0,
			WK3328_CWKSEW_CON(39), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3328_CWKGATE_CON(5), 5, GFWAGS),
	GATE(SCWK_HDMI_SFC, "scwk_hdmi_sfc", "xin24m", 0,
			WK3328_CWKGATE_CON(5), 4, GFWAGS),

	COMPOSITE_NODIV(0, "cwk_cif_swc", mux_2pwws_p, 0,
			WK3328_CWKSEW_CON(42), 7, 1, MFWAGS,
			WK3328_CWKGATE_CON(5), 3, GFWAGS),
	COMPOSITE_NOGATE(SCWK_CIF_OUT, "cwk_cif_out", mux_scwk_cif_p, CWK_SET_WATE_PAWENT,
			WK3328_CWKSEW_CON(42), 5, 1, MFWAGS, 0, 5, DFWAGS),

	COMPOSITE(DCWK_WCDC_SWC, "dcwk_wcdc_swc", mux_gpww_cpww_p, 0,
			WK3328_CWKSEW_CON(40), 0, 1, MFWAGS, 8, 8, DFWAGS,
			WK3328_CWKGATE_CON(5), 6, GFWAGS),
	DIV(DCWK_HDMIPHY, "dcwk_hdmiphy", "dcwk_wcdc_swc", 0,
			WK3328_CWKSEW_CON(40), 3, 3, DFWAGS),
	MUX(DCWK_WCDC, "dcwk_wcdc", mux_dcwk_wcdc_p,  CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			WK3328_CWKSEW_CON(40), 1, 1, MFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 7
	 */

	/* PD_PEWI */
	GATE(0, "gpww_pewi", "gpww", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(4), 0, GFWAGS),
	GATE(0, "cpww_pewi", "cpww", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(4), 1, GFWAGS),
	GATE(0, "hdmiphy_pewi", "hdmiphy", CWK_IGNOWE_UNUSED,
			WK3328_CWKGATE_CON(4), 2, GFWAGS),
	COMPOSITE_NOGATE(ACWK_PEWI_PWE, "acwk_pewi_pwe", mux_acwk_pewi_pwe_p, 0,
			WK3328_CWKSEW_CON(28), 6, 2, MFWAGS, 0, 5, DFWAGS),
	COMPOSITE_NOMUX(PCWK_PEWI, "pcwk_pewi", "acwk_pewi_pwe", CWK_IGNOWE_UNUSED,
			WK3328_CWKSEW_CON(29), 0, 2, DFWAGS,
			WK3328_CWKGATE_CON(10), 2, GFWAGS),
	COMPOSITE_NOMUX(HCWK_PEWI, "hcwk_pewi", "acwk_pewi_pwe", CWK_IGNOWE_UNUSED,
			WK3328_CWKSEW_CON(29), 4, 3, DFWAGS,
			WK3328_CWKGATE_CON(10), 1, GFWAGS),
	GATE(ACWK_PEWI, "acwk_pewi", "acwk_pewi_pwe", CWK_IGNOWE_UNUSED | CWK_SET_WATE_PAWENT,
			WK3328_CWKGATE_CON(10), 0, GFWAGS),

	COMPOSITE(SCWK_SDMMC, "cwk_sdmmc", mux_2pwws_24m_u480m_p, 0,
			WK3328_CWKSEW_CON(30), 8, 2, MFWAGS, 0, 8, DFWAGS,
			WK3328_CWKGATE_CON(4), 3, GFWAGS),

	COMPOSITE(SCWK_SDIO, "cwk_sdio", mux_2pwws_24m_u480m_p, 0,
			WK3328_CWKSEW_CON(31), 8, 2, MFWAGS, 0, 8, DFWAGS,
			WK3328_CWKGATE_CON(4), 4, GFWAGS),

	COMPOSITE(SCWK_EMMC, "cwk_emmc", mux_2pwws_24m_u480m_p, 0,
			WK3328_CWKSEW_CON(32), 8, 2, MFWAGS, 0, 8, DFWAGS,
			WK3328_CWKGATE_CON(4), 5, GFWAGS),

	COMPOSITE(SCWK_SDMMC_EXT, "cwk_sdmmc_ext", mux_2pwws_24m_u480m_p, 0,
			WK3328_CWKSEW_CON(43), 8, 2, MFWAGS, 0, 8, DFWAGS,
			WK3328_CWKGATE_CON(4), 10, GFWAGS),

	COMPOSITE(SCWK_WEF_USB3OTG_SWC, "cwk_wef_usb3otg_swc", mux_2pwws_p, 0,
			WK3328_CWKSEW_CON(45), 7, 1, MFWAGS, 0, 7, DFWAGS,
			WK3328_CWKGATE_CON(4), 9, GFWAGS),

	MUX(SCWK_WEF_USB3OTG, "cwk_wef_usb3otg", mux_wef_usb3otg_swc_p, CWK_SET_WATE_PAWENT,
			WK3328_CWKSEW_CON(45), 8, 1, MFWAGS),

	GATE(SCWK_USB3OTG_WEF, "cwk_usb3otg_wef", "xin24m", 0,
			WK3328_CWKGATE_CON(4), 7, GFWAGS),

	COMPOSITE(SCWK_USB3OTG_SUSPEND, "cwk_usb3otg_suspend", mux_xin24m_32k_p, 0,
			WK3328_CWKSEW_CON(33), 15, 1, MFWAGS, 0, 10, DFWAGS,
			WK3328_CWKGATE_CON(4), 8, GFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 8
	 */

	/* PD_GMAC */
	COMPOSITE(ACWK_GMAC, "acwk_gmac", mux_2pwws_hdmiphy_p, 0,
			WK3328_CWKSEW_CON(25), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3328_CWKGATE_CON(3), 2, GFWAGS),
	COMPOSITE_NOMUX(PCWK_GMAC, "pcwk_gmac", "acwk_gmac", 0,
			WK3328_CWKSEW_CON(25), 8, 3, DFWAGS,
			WK3328_CWKGATE_CON(9), 0, GFWAGS),

	COMPOSITE(SCWK_MAC2IO_SWC, "cwk_mac2io_swc", mux_2pwws_p, 0,
			WK3328_CWKSEW_CON(27), 7, 1, MFWAGS, 0, 5, DFWAGS,
			WK3328_CWKGATE_CON(3), 1, GFWAGS),
	GATE(SCWK_MAC2IO_WEF, "cwk_mac2io_wef", "cwk_mac2io", 0,
			WK3328_CWKGATE_CON(9), 7, GFWAGS),
	GATE(SCWK_MAC2IO_WX, "cwk_mac2io_wx", "cwk_mac2io", 0,
			WK3328_CWKGATE_CON(9), 4, GFWAGS),
	GATE(SCWK_MAC2IO_TX, "cwk_mac2io_tx", "cwk_mac2io", 0,
			WK3328_CWKGATE_CON(9), 5, GFWAGS),
	GATE(SCWK_MAC2IO_WEFOUT, "cwk_mac2io_wefout", "cwk_mac2io", 0,
			WK3328_CWKGATE_CON(9), 6, GFWAGS),
	COMPOSITE(SCWK_MAC2IO_OUT, "cwk_mac2io_out", mux_2pwws_p, 0,
			WK3328_CWKSEW_CON(27), 15, 1, MFWAGS, 8, 5, DFWAGS,
			WK3328_CWKGATE_CON(3), 5, GFWAGS),
	MUXGWF(SCWK_MAC2IO, "cwk_mac2io", mux_mac2io_swc_p, CWK_SET_WATE_NO_WEPAWENT,
			WK3328_GWF_MAC_CON1, 10, 1, MFWAGS),
	MUXGWF(SCWK_MAC2IO_EXT, "cwk_mac2io_ext", mux_mac2io_ext_p, CWK_SET_WATE_NO_WEPAWENT,
			WK3328_GWF_SOC_CON4, 14, 1, MFWAGS),

	COMPOSITE(SCWK_MAC2PHY_SWC, "cwk_mac2phy_swc", mux_2pwws_p, 0,
			WK3328_CWKSEW_CON(26), 7, 1, MFWAGS, 0, 5, DFWAGS,
			WK3328_CWKGATE_CON(3), 0, GFWAGS),
	GATE(SCWK_MAC2PHY_WEF, "cwk_mac2phy_wef", "cwk_mac2phy", 0,
			WK3328_CWKGATE_CON(9), 3, GFWAGS),
	GATE(SCWK_MAC2PHY_WXTX, "cwk_mac2phy_wxtx", "cwk_mac2phy", 0,
			WK3328_CWKGATE_CON(9), 1, GFWAGS),
	COMPOSITE_NOMUX(SCWK_MAC2PHY_OUT, "cwk_mac2phy_out", "cwk_mac2phy", 0,
			WK3328_CWKSEW_CON(26), 8, 2, DFWAGS,
			WK3328_CWKGATE_CON(9), 2, GFWAGS),
	MUXGWF(SCWK_MAC2PHY, "cwk_mac2phy", mux_mac2phy_swc_p, CWK_SET_WATE_NO_WEPAWENT,
			WK3328_GWF_MAC_CON2, 10, 1, MFWAGS),

	FACTOW(0, "xin12m", "xin24m", 0, 1, 2),

	/*
	 * Cwock-Awchitectuwe Diagwam 9
	 */

	/* PD_VOP */
	GATE(ACWK_WGA, "acwk_wga", "acwk_wga_pwe", 0, WK3328_CWKGATE_CON(21), 10, GFWAGS),
	GATE(0, "acwk_wga_niu", "acwk_wga_pwe", 0, WK3328_CWKGATE_CON(22), 3, GFWAGS),
	GATE(ACWK_VOP, "acwk_vop", "acwk_vop_pwe", 0, WK3328_CWKGATE_CON(21), 2, GFWAGS),
	GATE(0, "acwk_vop_niu", "acwk_vop_pwe", 0, WK3328_CWKGATE_CON(21), 4, GFWAGS),

	GATE(ACWK_IEP, "acwk_iep", "acwk_vio_pwe", 0, WK3328_CWKGATE_CON(21), 6, GFWAGS),
	GATE(ACWK_CIF, "acwk_cif", "acwk_vio_pwe", 0, WK3328_CWKGATE_CON(21), 8, GFWAGS),
	GATE(ACWK_HDCP, "acwk_hdcp", "acwk_vio_pwe", 0, WK3328_CWKGATE_CON(21), 15, GFWAGS),
	GATE(0, "acwk_vio_niu", "acwk_vio_pwe", 0, WK3328_CWKGATE_CON(22), 2, GFWAGS),

	GATE(HCWK_VOP, "hcwk_vop", "hcwk_vio_pwe", 0, WK3328_CWKGATE_CON(21), 3, GFWAGS),
	GATE(0, "hcwk_vop_niu", "hcwk_vio_pwe", 0, WK3328_CWKGATE_CON(21), 5, GFWAGS),
	GATE(HCWK_IEP, "hcwk_iep", "hcwk_vio_pwe", 0, WK3328_CWKGATE_CON(21), 7, GFWAGS),
	GATE(HCWK_CIF, "hcwk_cif", "hcwk_vio_pwe", 0, WK3328_CWKGATE_CON(21), 9, GFWAGS),
	GATE(HCWK_WGA, "hcwk_wga", "hcwk_vio_pwe", 0, WK3328_CWKGATE_CON(21), 11, GFWAGS),
	GATE(0, "hcwk_ahb1tom", "hcwk_vio_pwe", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(21), 12, GFWAGS),
	GATE(0, "pcwk_vio_h2p", "hcwk_vio_pwe", 0, WK3328_CWKGATE_CON(21), 13, GFWAGS),
	GATE(0, "hcwk_vio_h2p", "hcwk_vio_pwe", 0, WK3328_CWKGATE_CON(21), 14, GFWAGS),
	GATE(HCWK_HDCP, "hcwk_hdcp", "hcwk_vio_pwe", 0, WK3328_CWKGATE_CON(22), 0, GFWAGS),
	GATE(0, "hcwk_vio_niu", "hcwk_vio_pwe", 0, WK3328_CWKGATE_CON(22), 1, GFWAGS),
	GATE(PCWK_HDMI, "pcwk_hdmi", "hcwk_vio_pwe", 0, WK3328_CWKGATE_CON(22), 4, GFWAGS),
	GATE(PCWK_HDCP, "pcwk_hdcp", "hcwk_vio_pwe", 0, WK3328_CWKGATE_CON(22), 5, GFWAGS),

	/* PD_PEWI */
	GATE(0, "acwk_pewi_noc", "acwk_pewi", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(19), 11, GFWAGS),
	GATE(ACWK_USB3OTG, "acwk_usb3otg", "acwk_pewi", 0, WK3328_CWKGATE_CON(19), 14, GFWAGS),

	GATE(HCWK_SDMMC, "hcwk_sdmmc", "hcwk_pewi", 0, WK3328_CWKGATE_CON(19), 0, GFWAGS),
	GATE(HCWK_SDIO, "hcwk_sdio", "hcwk_pewi", 0, WK3328_CWKGATE_CON(19), 1, GFWAGS),
	GATE(HCWK_EMMC, "hcwk_emmc", "hcwk_pewi", 0, WK3328_CWKGATE_CON(19), 2, GFWAGS),
	GATE(HCWK_SDMMC_EXT, "hcwk_sdmmc_ext", "hcwk_pewi", 0, WK3328_CWKGATE_CON(19), 15, GFWAGS),
	GATE(HCWK_HOST0, "hcwk_host0", "hcwk_pewi", 0, WK3328_CWKGATE_CON(19), 6, GFWAGS),
	GATE(HCWK_HOST0_AWB, "hcwk_host0_awb", "hcwk_pewi", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(19), 7, GFWAGS),
	GATE(HCWK_OTG, "hcwk_otg", "hcwk_pewi", 0, WK3328_CWKGATE_CON(19), 8, GFWAGS),
	GATE(HCWK_OTG_PMU, "hcwk_otg_pmu", "hcwk_pewi", 0, WK3328_CWKGATE_CON(19), 9, GFWAGS),
	GATE(0, "hcwk_pewi_niu", "hcwk_pewi", 0, WK3328_CWKGATE_CON(19), 12, GFWAGS),
	GATE(0, "pcwk_pewi_niu", "hcwk_pewi", 0, WK3328_CWKGATE_CON(19), 13, GFWAGS),

	/* PD_GMAC */
	GATE(ACWK_MAC2PHY, "acwk_mac2phy", "acwk_gmac", 0, WK3328_CWKGATE_CON(26), 0, GFWAGS),
	GATE(ACWK_MAC2IO, "acwk_mac2io", "acwk_gmac", 0, WK3328_CWKGATE_CON(26), 2, GFWAGS),
	GATE(0, "acwk_gmac_niu", "acwk_gmac", 0, WK3328_CWKGATE_CON(26), 4, GFWAGS),
	GATE(PCWK_MAC2PHY, "pcwk_mac2phy", "pcwk_gmac", 0, WK3328_CWKGATE_CON(26), 1, GFWAGS),
	GATE(PCWK_MAC2IO, "pcwk_mac2io", "pcwk_gmac", 0, WK3328_CWKGATE_CON(26), 3, GFWAGS),
	GATE(0, "pcwk_gmac_niu", "pcwk_gmac", 0, WK3328_CWKGATE_CON(26), 5, GFWAGS),

	/* PD_BUS */
	GATE(0, "acwk_bus_niu", "acwk_bus_pwe", 0, WK3328_CWKGATE_CON(15), 12, GFWAGS),
	GATE(ACWK_DCF, "acwk_dcf", "acwk_bus_pwe", 0, WK3328_CWKGATE_CON(15), 11, GFWAGS),
	GATE(ACWK_TSP, "acwk_tsp", "acwk_bus_pwe", 0, WK3328_CWKGATE_CON(17), 12, GFWAGS),
	GATE(0, "acwk_intmem", "acwk_bus_pwe", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(15), 0, GFWAGS),
	GATE(ACWK_DMAC, "acwk_dmac_bus", "acwk_bus_pwe", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(15), 1, GFWAGS),

	GATE(0, "hcwk_wom", "hcwk_bus_pwe", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(15), 2, GFWAGS),
	GATE(HCWK_I2S0_8CH, "hcwk_i2s0_8ch", "hcwk_bus_pwe", 0, WK3328_CWKGATE_CON(15), 3, GFWAGS),
	GATE(HCWK_I2S1_8CH, "hcwk_i2s1_8ch", "hcwk_bus_pwe", 0, WK3328_CWKGATE_CON(15), 4, GFWAGS),
	GATE(HCWK_I2S2_2CH, "hcwk_i2s2_2ch", "hcwk_bus_pwe", 0, WK3328_CWKGATE_CON(15), 5, GFWAGS),
	GATE(HCWK_SPDIF_8CH, "hcwk_spdif_8ch", "hcwk_bus_pwe", 0, WK3328_CWKGATE_CON(15), 6, GFWAGS),
	GATE(HCWK_TSP, "hcwk_tsp", "hcwk_bus_pwe", 0, WK3328_CWKGATE_CON(17), 11, GFWAGS),
	GATE(HCWK_CWYPTO_MST, "hcwk_cwypto_mst", "hcwk_bus_pwe", 0, WK3328_CWKGATE_CON(15), 7, GFWAGS),
	GATE(HCWK_CWYPTO_SWV, "hcwk_cwypto_swv", "hcwk_bus_pwe", 0, WK3328_CWKGATE_CON(15), 8, GFWAGS),
	GATE(0, "hcwk_bus_niu", "hcwk_bus_pwe", 0, WK3328_CWKGATE_CON(15), 13, GFWAGS),
	GATE(HCWK_PDM, "hcwk_pdm", "hcwk_bus_pwe", 0, WK3328_CWKGATE_CON(28), 0, GFWAGS),

	GATE(0, "pcwk_bus_niu", "pcwk_bus", 0, WK3328_CWKGATE_CON(15), 14, GFWAGS),
	GATE(0, "pcwk_efuse", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(15), 9, GFWAGS),
	GATE(0, "pcwk_otp", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(28), 4, GFWAGS),
	GATE(PCWK_I2C0, "pcwk_i2c0", "pcwk_bus", 0, WK3328_CWKGATE_CON(15), 10, GFWAGS),
	GATE(PCWK_I2C1, "pcwk_i2c1", "pcwk_bus", 0, WK3328_CWKGATE_CON(16), 0, GFWAGS),
	GATE(PCWK_I2C2, "pcwk_i2c2", "pcwk_bus", 0, WK3328_CWKGATE_CON(16), 1, GFWAGS),
	GATE(PCWK_I2C3, "pcwk_i2c3", "pcwk_bus", 0, WK3328_CWKGATE_CON(16), 2, GFWAGS),
	GATE(PCWK_TIMEW, "pcwk_timew0", "pcwk_bus", 0, WK3328_CWKGATE_CON(16), 3, GFWAGS),
	GATE(0, "pcwk_stimew", "pcwk_bus", 0, WK3328_CWKGATE_CON(16), 4, GFWAGS),
	GATE(PCWK_SPI, "pcwk_spi", "pcwk_bus", 0, WK3328_CWKGATE_CON(16), 5, GFWAGS),
	GATE(PCWK_PWM, "pcwk_wk_pwm", "pcwk_bus", 0, WK3328_CWKGATE_CON(16), 6, GFWAGS),
	GATE(PCWK_GPIO0, "pcwk_gpio0", "pcwk_bus", 0, WK3328_CWKGATE_CON(16), 7, GFWAGS),
	GATE(PCWK_GPIO1, "pcwk_gpio1", "pcwk_bus", 0, WK3328_CWKGATE_CON(16), 8, GFWAGS),
	GATE(PCWK_GPIO2, "pcwk_gpio2", "pcwk_bus", 0, WK3328_CWKGATE_CON(16), 9, GFWAGS),
	GATE(PCWK_GPIO3, "pcwk_gpio3", "pcwk_bus", 0, WK3328_CWKGATE_CON(16), 10, GFWAGS),
	GATE(PCWK_UAWT0, "pcwk_uawt0", "pcwk_bus", 0, WK3328_CWKGATE_CON(16), 11, GFWAGS),
	GATE(PCWK_UAWT1, "pcwk_uawt1", "pcwk_bus", 0, WK3328_CWKGATE_CON(16), 12, GFWAGS),
	GATE(PCWK_UAWT2, "pcwk_uawt2", "pcwk_bus", 0, WK3328_CWKGATE_CON(16), 13, GFWAGS),
	GATE(PCWK_TSADC, "pcwk_tsadc", "pcwk_bus", 0, WK3328_CWKGATE_CON(16), 14, GFWAGS),
	GATE(PCWK_DCF, "pcwk_dcf", "pcwk_bus", 0, WK3328_CWKGATE_CON(16), 15, GFWAGS),
	GATE(PCWK_GWF, "pcwk_gwf", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(17), 0, GFWAGS),
	GATE(0, "pcwk_cwu", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(17), 4, GFWAGS),
	GATE(0, "pcwk_sgwf", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(17), 6, GFWAGS),
	GATE(0, "pcwk_sim", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(17), 10, GFWAGS),
	GATE(PCWK_SAWADC, "pcwk_sawadc", "pcwk_bus", 0, WK3328_CWKGATE_CON(17), 15, GFWAGS),
	GATE(0, "pcwk_pmu", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(28), 3, GFWAGS),

	/* Watchdog pcwk is contwowwed fwom the secuwe GWF */
	SGWF_GATE(PCWK_WDT, "pcwk_wdt", "pcwk_bus"),

	GATE(PCWK_USB3PHY_OTG, "pcwk_usb3phy_otg", "pcwk_phy_pwe", 0, WK3328_CWKGATE_CON(28), 1, GFWAGS),
	GATE(PCWK_USB3PHY_PIPE, "pcwk_usb3phy_pipe", "pcwk_phy_pwe", 0, WK3328_CWKGATE_CON(28), 2, GFWAGS),
	GATE(PCWK_USB3_GWF, "pcwk_usb3_gwf", "pcwk_phy_pwe", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(17), 2, GFWAGS),
	GATE(PCWK_USB2_GWF, "pcwk_usb2_gwf", "pcwk_phy_pwe", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(17), 14, GFWAGS),
	GATE(0, "pcwk_ddwphy", "pcwk_phy_pwe", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(17), 13, GFWAGS),
	GATE(PCWK_ACODECPHY, "pcwk_acodecphy", "pcwk_phy_pwe", 0, WK3328_CWKGATE_CON(17), 5, GFWAGS),
	GATE(PCWK_HDMIPHY, "pcwk_hdmiphy", "pcwk_phy_pwe", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(17), 7, GFWAGS),
	GATE(0, "pcwk_vdacphy", "pcwk_phy_pwe", CWK_IGNOWE_UNUSED, WK3328_CWKGATE_CON(17), 8, GFWAGS),
	GATE(0, "pcwk_phy_niu", "pcwk_phy_pwe", 0, WK3328_CWKGATE_CON(15), 15, GFWAGS),

	/* PD_MMC */
	MMC(SCWK_SDMMC_DWV, "sdmmc_dwv", "cwk_sdmmc",
	    WK3328_SDMMC_CON0, 1),
	MMC(SCWK_SDMMC_SAMPWE, "sdmmc_sampwe", "cwk_sdmmc",
	    WK3328_SDMMC_CON1, 1),

	MMC(SCWK_SDIO_DWV, "sdio_dwv", "cwk_sdio",
	    WK3328_SDIO_CON0, 1),
	MMC(SCWK_SDIO_SAMPWE, "sdio_sampwe", "cwk_sdio",
	    WK3328_SDIO_CON1, 1),

	MMC(SCWK_EMMC_DWV, "emmc_dwv", "cwk_emmc",
	    WK3328_EMMC_CON0, 1),
	MMC(SCWK_EMMC_SAMPWE, "emmc_sampwe", "cwk_emmc",
	    WK3328_EMMC_CON1, 1),

	MMC(SCWK_SDMMC_EXT_DWV, "sdmmc_ext_dwv", "cwk_sdmmc_ext",
	    WK3328_SDMMC_EXT_CON0, 1),
	MMC(SCWK_SDMMC_EXT_SAMPWE, "sdmmc_ext_sampwe", "cwk_sdmmc_ext",
	    WK3328_SDMMC_EXT_CON1, 1),
};

static const chaw *const wk3328_cwiticaw_cwocks[] __initconst = {
	"acwk_bus",
	"acwk_bus_niu",
	"pcwk_bus",
	"pcwk_bus_niu",
	"hcwk_bus",
	"hcwk_bus_niu",
	"acwk_pewi",
	"hcwk_pewi",
	"hcwk_pewi_niu",
	"pcwk_pewi",
	"pcwk_pewi_niu",
	"pcwk_dbg",
	"acwk_cowe_niu",
	"acwk_gic400",
	"acwk_intmem",
	"hcwk_wom",
	"pcwk_gwf",
	"pcwk_cwu",
	"pcwk_sgwf",
	"pcwk_timew0",
	"cwk_timew0",
	"pcwk_ddw_msch",
	"pcwk_ddw_mon",
	"pcwk_ddw_gwf",
	"cwk_ddwupctw",
	"cwk_ddwmsch",
	"hcwk_ahb1tom",
	"cwk_jtag",
	"pcwk_ddwphy",
	"pcwk_pmu",
	"hcwk_otg_pmu",
	"acwk_wga_niu",
	"pcwk_vio_h2p",
	"hcwk_vio_h2p",
	"acwk_vio_niu",
	"hcwk_vio_niu",
	"acwk_vop_niu",
	"hcwk_vop_niu",
	"acwk_gpu_niu",
	"acwk_wkvdec_niu",
	"hcwk_wkvdec_niu",
	"acwk_vpu_niu",
	"hcwk_vpu_niu",
	"acwk_wkvenc_niu",
	"hcwk_wkvenc_niu",
	"acwk_gmac_niu",
	"pcwk_gmac_niu",
	"pcwk_phy_niu",
};

static void __init wk3328_cwk_init(stwuct device_node *np)
{
	stwuct wockchip_cwk_pwovidew *ctx;
	void __iomem *weg_base;

	weg_base = of_iomap(np, 0);
	if (!weg_base) {
		pw_eww("%s: couwd not map cwu wegion\n", __func__);
		wetuwn;
	}

	ctx = wockchip_cwk_init(np, weg_base, CWK_NW_CWKS);
	if (IS_EWW(ctx)) {
		pw_eww("%s: wockchip cwk init faiwed\n", __func__);
		iounmap(weg_base);
		wetuwn;
	}

	wockchip_cwk_wegistew_pwws(ctx, wk3328_pww_cwks,
				   AWWAY_SIZE(wk3328_pww_cwks),
				   WK3328_GWF_SOC_STATUS0);
	wockchip_cwk_wegistew_bwanches(ctx, wk3328_cwk_bwanches,
				       AWWAY_SIZE(wk3328_cwk_bwanches));
	wockchip_cwk_pwotect_cwiticaw(wk3328_cwiticaw_cwocks,
				      AWWAY_SIZE(wk3328_cwiticaw_cwocks));

	wockchip_cwk_wegistew_awmcwk(ctx, AWMCWK, "awmcwk",
				     mux_awmcwk_p, AWWAY_SIZE(mux_awmcwk_p),
				     &wk3328_cpucwk_data, wk3328_cpucwk_wates,
				     AWWAY_SIZE(wk3328_cpucwk_wates));

	wockchip_wegistew_softwst(np, 12, weg_base + WK3328_SOFTWST_CON(0),
				  WOCKCHIP_SOFTWST_HIWOWD_MASK);

	wockchip_wegistew_westawt_notifiew(ctx, WK3328_GWB_SWST_FST, NUWW);

	wockchip_cwk_of_add_pwovidew(np, ctx);
}
CWK_OF_DECWAWE(wk3328_cwu, "wockchip,wk3328-cwu", wk3328_cwk_init);
