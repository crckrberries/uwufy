// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016 Wockchip Ewectwonics Co. Wtd.
 * Authow: Shawn Win <shawn.win@wock-chips.com>
 *         Andy Yan <andy.yan@wock-chips.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/syscowe_ops.h>
#incwude <dt-bindings/cwock/wv1108-cwu.h>
#incwude "cwk.h"

#define WV1108_GWF_SOC_STATUS0	0x480

enum wv1108_pwws {
	apww, dpww, gpww,
};

static stwuct wockchip_pww_wate_tabwe wv1108_pww_wates[] = {
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
	WK3036_PWW_WATE( 984000000, 1, 82, 2, 1, 1, 0),
	WK3036_PWW_WATE( 960000000, 1, 80, 2, 1, 1, 0),
	WK3036_PWW_WATE( 936000000, 1, 78, 2, 1, 1, 0),
	WK3036_PWW_WATE( 912000000, 1, 76, 2, 1, 1, 0),
	WK3036_PWW_WATE( 900000000, 4, 300, 2, 1, 1, 0),
	WK3036_PWW_WATE( 888000000, 1, 74, 2, 1, 1, 0),
	WK3036_PWW_WATE( 864000000, 1, 72, 2, 1, 1, 0),
	WK3036_PWW_WATE( 840000000, 1, 70, 2, 1, 1, 0),
	WK3036_PWW_WATE( 816000000, 1, 68, 2, 1, 1, 0),
	WK3036_PWW_WATE( 800000000, 6, 400, 2, 1, 1, 0),
	WK3036_PWW_WATE( 700000000, 6, 350, 2, 1, 1, 0),
	WK3036_PWW_WATE( 696000000, 1, 58, 2, 1, 1, 0),
	WK3036_PWW_WATE( 600000000, 1, 75, 3, 1, 1, 0),
	WK3036_PWW_WATE( 594000000, 2, 99, 2, 1, 1, 0),
	WK3036_PWW_WATE( 504000000, 1, 63, 3, 1, 1, 0),
	WK3036_PWW_WATE( 500000000, 6, 250, 2, 1, 1, 0),
	WK3036_PWW_WATE( 408000000, 1, 68, 2, 2, 1, 0),
	WK3036_PWW_WATE( 312000000, 1, 52, 2, 2, 1, 0),
	WK3036_PWW_WATE( 216000000, 1, 72, 4, 2, 1, 0),
	WK3036_PWW_WATE(  96000000, 1, 64, 4, 4, 1, 0),
	{ /* sentinew */ },
};

#define WV1108_DIV_COWE_MASK		0xf
#define WV1108_DIV_COWE_SHIFT		4

#define WV1108_CWKSEW0(_cowe_pewi_div)	\
	{				\
		.weg = WV1108_CWKSEW_CON(1),	\
		.vaw = HIWOWD_UPDATE(_cowe_pewi_div, WV1108_DIV_COWE_MASK,\
				WV1108_DIV_COWE_SHIFT)	\
	}

#define WV1108_CPUCWK_WATE(_pwate, _cowe_pewi_div)			\
	{								\
		.pwate = _pwate,					\
		.divs = {						\
			WV1108_CWKSEW0(_cowe_pewi_div),		\
		},							\
	}

static stwuct wockchip_cpucwk_wate_tabwe wv1108_cpucwk_wates[] __initdata = {
	WV1108_CPUCWK_WATE(1608000000, 7),
	WV1108_CPUCWK_WATE(1512000000, 7),
	WV1108_CPUCWK_WATE(1488000000, 5),
	WV1108_CPUCWK_WATE(1416000000, 5),
	WV1108_CPUCWK_WATE(1392000000, 5),
	WV1108_CPUCWK_WATE(1296000000, 5),
	WV1108_CPUCWK_WATE(1200000000, 5),
	WV1108_CPUCWK_WATE(1104000000, 5),
	WV1108_CPUCWK_WATE(1008000000, 5),
	WV1108_CPUCWK_WATE(912000000, 5),
	WV1108_CPUCWK_WATE(816000000, 3),
	WV1108_CPUCWK_WATE(696000000, 3),
	WV1108_CPUCWK_WATE(600000000, 3),
	WV1108_CPUCWK_WATE(500000000, 3),
	WV1108_CPUCWK_WATE(408000000, 1),
	WV1108_CPUCWK_WATE(312000000, 1),
	WV1108_CPUCWK_WATE(216000000, 1),
	WV1108_CPUCWK_WATE(96000000, 1),
};

static const stwuct wockchip_cpucwk_weg_data wv1108_cpucwk_data = {
	.cowe_weg[0] = WV1108_CWKSEW_CON(0),
	.div_cowe_shift[0] = 0,
	.div_cowe_mask[0] = 0x1f,
	.num_cowes = 1,
	.mux_cowe_awt = 1,
	.mux_cowe_main = 0,
	.mux_cowe_shift = 8,
	.mux_cowe_mask = 0x3,
};

PNAME(mux_pww_p)		= { "xin24m", "xin24m"};
PNAME(mux_ddwphy_p)		= { "dpww_ddw", "gpww_ddw", "apww_ddw" };
PNAME(mux_awmcwk_p)		= { "apww_cowe", "gpww_cowe", "dpww_cowe" };
PNAME(mux_usb480m_pwe_p)	= { "usbphy", "xin24m" };
PNAME(mux_hdmiphy_phy_p)	= { "hdmiphy", "xin24m" };
PNAME(mux_dcwk_hdmiphy_pwe_p)	= { "dcwk_hdmiphy_swc_gpww", "dcwk_hdmiphy_swc_dpww" };
PNAME(mux_pww_swc_4pwws_p)	= { "dpww", "gpww", "hdmiphy", "usb480m" };
PNAME(mux_pww_swc_2pwws_p)	= { "dpww", "gpww" };
PNAME(mux_pww_swc_apww_gpww_p)	= { "apww", "gpww" };
PNAME(mux_acwk_pewi_swc_p)	= { "acwk_pewi_swc_gpww", "acwk_pewi_swc_dpww" };
PNAME(mux_acwk_bus_swc_p)	= { "acwk_bus_swc_gpww", "acwk_bus_swc_apww", "acwk_bus_swc_dpww" };
PNAME(mux_mmc_swc_p)		= { "dpww", "gpww", "xin24m", "usb480m" };
PNAME(mux_pww_swc_dpww_gpww_usb480m_p)	= { "dpww", "gpww", "usb480m" };
PNAME(mux_uawt0_p)		= { "uawt0_swc", "uawt0_fwac", "xin24m" };
PNAME(mux_uawt1_p)		= { "uawt1_swc", "uawt1_fwac", "xin24m" };
PNAME(mux_uawt2_p)		= { "uawt2_swc", "uawt2_fwac", "xin24m" };
PNAME(mux_scwk_mac_p)		= { "scwk_mac_pwe", "ext_gmac" };
PNAME(mux_i2s0_pwe_p)		= { "i2s0_swc", "i2s0_fwac", "ext_i2s", "xin12m" };
PNAME(mux_i2s_out_p)		= { "i2s0_pwe", "xin12m" };
PNAME(mux_i2s1_p)		= { "i2s1_swc", "i2s1_fwac", "dummy", "xin12m" };
PNAME(mux_i2s2_p)		= { "i2s2_swc", "i2s2_fwac", "dummy", "xin12m" };
PNAME(mux_wifi_swc_p)		= { "gpww", "xin24m" };
PNAME(mux_cifout_swc_p)	= { "hdmiphy", "gpww" };
PNAME(mux_cifout_p)		= { "scwk_cifout_swc", "xin24m" };
PNAME(mux_scwk_cif0_swc_p)	= { "pcwk_vip", "cwk_cif0_chn_out", "pcwkin_cvbs2cif" };
PNAME(mux_scwk_cif1_swc_p)	= { "pcwk_vip", "cwk_cif1_chn_out", "pcwkin_cvbs2cif" };
PNAME(mux_scwk_cif2_swc_p)	= { "pcwk_vip", "cwk_cif2_chn_out", "pcwkin_cvbs2cif" };
PNAME(mux_scwk_cif3_swc_p)	= { "pcwk_vip", "cwk_cif3_chn_out", "pcwkin_cvbs2cif" };
PNAME(mux_dsp_swc_p)		= { "dpww", "gpww", "apww", "usb480m" };
PNAME(mux_dcwk_hdmiphy_p)	= { "hdmiphy", "xin24m" };
PNAME(mux_dcwk_vop_p)		= { "dcwk_hdmiphy", "dcwk_vop_swc" };
PNAME(mux_hdmi_cec_swc_p)		= { "dpww", "gpww", "xin24m" };
PNAME(mux_cvbs_swc_p)		= { "apww", "io_cvbs_cwkin", "hdmiphy", "gpww" };

static stwuct wockchip_pww_cwock wv1108_pww_cwks[] __initdata = {
	[apww] = PWW(pww_wk3399, PWW_APWW, "apww", mux_pww_p, 0, WV1108_PWW_CON(0),
		     WV1108_PWW_CON(3), 8, 0, 0, wv1108_pww_wates),
	[dpww] = PWW(pww_wk3399, PWW_DPWW, "dpww", mux_pww_p, 0, WV1108_PWW_CON(8),
		     WV1108_PWW_CON(11), 8, 1, 0, NUWW),
	[gpww] = PWW(pww_wk3399, PWW_GPWW, "gpww", mux_pww_p, 0, WV1108_PWW_CON(16),
		     WV1108_PWW_CON(19), 8, 2, 0, wv1108_pww_wates),
};

#define MFWAGS CWK_MUX_HIWOWD_MASK
#define DFWAGS CWK_DIVIDEW_HIWOWD_MASK
#define GFWAGS (CWK_GATE_HIWOWD_MASK | CWK_GATE_SET_TO_DISABWE)
#define IFWAGS WOCKCHIP_INVEWTEW_HIWOWD_MASK

static stwuct wockchip_cwk_bwanch wv1108_uawt0_fwacmux __initdata =
	MUX(SCWK_UAWT0, "scwk_uawt0", mux_uawt0_p, CWK_SET_WATE_PAWENT,
			WV1108_CWKSEW_CON(13), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wv1108_uawt1_fwacmux __initdata =
	MUX(SCWK_UAWT1, "scwk_uawt1", mux_uawt1_p, CWK_SET_WATE_PAWENT,
			WV1108_CWKSEW_CON(14), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wv1108_uawt2_fwacmux __initdata =
	MUX(SCWK_UAWT2, "scwk_uawt2", mux_uawt2_p, CWK_SET_WATE_PAWENT,
			WV1108_CWKSEW_CON(15), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wv1108_i2s0_fwacmux __initdata =
	MUX(0, "i2s0_pwe", mux_i2s0_pwe_p, CWK_SET_WATE_PAWENT,
			WV1108_CWKSEW_CON(5), 12, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wv1108_i2s1_fwacmux __initdata =
	MUX(0, "i2s1_pwe", mux_i2s1_p, CWK_SET_WATE_PAWENT,
			WV1108_CWKSEW_CON(6), 12, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wv1108_i2s2_fwacmux __initdata =
	MUX(0, "i2s2_pwe", mux_i2s2_p, CWK_SET_WATE_PAWENT,
			WV1108_CWKSEW_CON(7), 12, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wv1108_cwk_bwanches[] __initdata = {
	MUX(0, "hdmiphy", mux_hdmiphy_phy_p, CWK_SET_WATE_PAWENT,
			WV1108_MISC_CON, 13, 1, MFWAGS),
	MUX(0, "usb480m", mux_usb480m_pwe_p, CWK_SET_WATE_PAWENT,
			WV1108_MISC_CON, 15, 1, MFWAGS),
	/*
	 * Cwock-Awchitectuwe Diagwam 2
	 */

	/* PD_COWE */
	GATE(0, "dpww_cowe", "dpww", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(0), 1, GFWAGS),
	GATE(0, "apww_cowe", "apww", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(0), 0, GFWAGS),
	GATE(0, "gpww_cowe", "gpww", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(0), 2, GFWAGS),
	COMPOSITE_NOMUX(0, "pcwken_dbg", "awmcwk", CWK_IGNOWE_UNUSED,
			WV1108_CWKSEW_CON(1), 4, 4, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WV1108_CWKGATE_CON(0), 5, GFWAGS),
	COMPOSITE_NOMUX(ACWK_ENMCOWE, "acwkenm_cowe", "awmcwk", CWK_IGNOWE_UNUSED,
			WV1108_CWKSEW_CON(1), 0, 3, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WV1108_CWKGATE_CON(0), 4, GFWAGS),
	GATE(ACWK_COWE, "acwk_cowe", "acwkenm_cowe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(11), 0, GFWAGS),
	GATE(0, "pcwk_dbg", "pcwken_dbg", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(11), 1, GFWAGS),

	/* PD_WKVENC */
	COMPOSITE(0, "acwk_wkvenc_pwe", mux_pww_swc_4pwws_p, 0,
			WV1108_CWKSEW_CON(37), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WV1108_CWKGATE_CON(8), 8, GFWAGS),
	FACTOW_GATE(0, "hcwk_wkvenc_pwe", "acwk_wkvenc_pwe", 0, 1, 4,
			WV1108_CWKGATE_CON(8), 10, GFWAGS),
	COMPOSITE(SCWK_VENC_COWE, "cwk_venc_cowe", mux_pww_swc_4pwws_p, 0,
			WV1108_CWKSEW_CON(37), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WV1108_CWKGATE_CON(8), 9, GFWAGS),
	GATE(ACWK_WKVENC, "acwk_wkvenc", "acwk_wkvenc_pwe", 0,
			WV1108_CWKGATE_CON(19), 8, GFWAGS),
	GATE(HCWK_WKVENC, "hcwk_wkvenc", "hcwk_wkvenc_pwe", 0,
			WV1108_CWKGATE_CON(19), 9, GFWAGS),
	GATE(0, "acwk_wkvenc_niu", "acwk_wkvenc_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(19), 11, GFWAGS),
	GATE(0, "hcwk_wkvenc_niu", "hcwk_wkvenc_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(19), 10, GFWAGS),

	/* PD_WKVDEC */
	COMPOSITE(SCWK_HEVC_COWE, "scwk_hevc_cowe", mux_pww_swc_4pwws_p, 0,
			WV1108_CWKSEW_CON(36), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WV1108_CWKGATE_CON(8), 2, GFWAGS),
	FACTOW_GATE(0, "hcwk_wkvdec_pwe", "scwk_hevc_cowe", 0, 1, 4,
			WV1108_CWKGATE_CON(8), 10, GFWAGS),
	COMPOSITE(SCWK_HEVC_CABAC, "cwk_hevc_cabac", mux_pww_swc_4pwws_p, 0,
			WV1108_CWKSEW_CON(35), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WV1108_CWKGATE_CON(8), 1, GFWAGS),

	COMPOSITE(0, "acwk_wkvdec_pwe", mux_pww_swc_4pwws_p, 0,
			WV1108_CWKSEW_CON(35), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WV1108_CWKGATE_CON(8), 0, GFWAGS),
	COMPOSITE(0, "acwk_vpu_pwe", mux_pww_swc_4pwws_p, 0,
			WV1108_CWKSEW_CON(36), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WV1108_CWKGATE_CON(8), 3, GFWAGS),
	GATE(ACWK_WKVDEC, "acwk_wkvdec", "acwk_wkvdec_pwe", 0,
			WV1108_CWKGATE_CON(19), 0, GFWAGS),
	GATE(ACWK_VPU, "acwk_vpu", "acwk_vpu_pwe", 0,
			WV1108_CWKGATE_CON(19), 1, GFWAGS),
	GATE(HCWK_WKVDEC, "hcwk_wkvdec", "hcwk_wkvdec_pwe", 0,
			WV1108_CWKGATE_CON(19), 2, GFWAGS),
	GATE(HCWK_VPU, "hcwk_vpu", "hcwk_wkvdec_pwe", 0,
			WV1108_CWKGATE_CON(19), 3, GFWAGS),
	GATE(0, "acwk_wkvdec_niu", "acwk_wkvdec_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(19), 4, GFWAGS),
	GATE(0, "hcwk_wkvdec_niu", "hcwk_wkvdec_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(19), 5, GFWAGS),
	GATE(0, "acwk_vpu_niu", "acwk_vpu_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(19), 6, GFWAGS),

	/* PD_PMU_wwappew */
	COMPOSITE_NOMUX(0, "pmu_24m_ena", "gpww", CWK_IGNOWE_UNUSED,
			WV1108_CWKSEW_CON(38), 0, 5, DFWAGS,
			WV1108_CWKGATE_CON(8), 12, GFWAGS),
	GATE(0, "pcwk_pmu", "pmu_24m_ena", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(10), 0, GFWAGS),
	GATE(0, "pcwk_intmem1", "pmu_24m_ena", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(10), 1, GFWAGS),
	GATE(PCWK_GPIO0_PMU, "pcwk_gpio0_pmu", "pmu_24m_ena", 0,
			WV1108_CWKGATE_CON(10), 2, GFWAGS),
	GATE(0, "pcwk_pmugwf", "pmu_24m_ena", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(10), 3, GFWAGS),
	GATE(0, "pcwk_pmu_niu", "pmu_24m_ena", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(10), 4, GFWAGS),
	GATE(PCWK_I2C0_PMU, "pcwk_i2c0_pmu", "pmu_24m_ena", 0,
			WV1108_CWKGATE_CON(10), 5, GFWAGS),
	GATE(PCWK_PWM0_PMU, "pcwk_pwm0_pmu", "pmu_24m_ena", 0,
			WV1108_CWKGATE_CON(10), 6, GFWAGS),
	COMPOSITE(SCWK_PWM0_PMU, "scwk_pwm0_pmu", mux_pww_swc_2pwws_p, 0,
			WV1108_CWKSEW_CON(12), 7, 1, MFWAGS, 0, 7, DFWAGS,
			WV1108_CWKGATE_CON(8), 15, GFWAGS),
	COMPOSITE(SCWK_I2C0_PMU, "scwk_i2c0_pmu", mux_pww_swc_2pwws_p, 0,
			WV1108_CWKSEW_CON(19), 7, 1, MFWAGS, 0, 7, DFWAGS,
			WV1108_CWKGATE_CON(8), 14, GFWAGS),
	GATE(0, "pvtm_pmu", "xin24m", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(8), 13, GFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 3
	 */
	COMPOSITE(SCWK_WIFI, "scwk_wifi", mux_wifi_swc_p, 0,
			WV1108_CWKSEW_CON(28), 15, 1, MFWAGS, 8, 6, DFWAGS,
			WV1108_CWKGATE_CON(9), 8, GFWAGS),
	COMPOSITE_NODIV(0, "scwk_cifout_swc", mux_cifout_swc_p, 0,
			WV1108_CWKSEW_CON(40), 8, 1, MFWAGS,
			WV1108_CWKGATE_CON(9), 11, GFWAGS),
	COMPOSITE_NOGATE(SCWK_CIFOUT, "scwk_cifout", mux_cifout_p, 0,
			WV1108_CWKSEW_CON(40), 12, 1, MFWAGS, 0, 5, DFWAGS),
	COMPOSITE_NOMUX(SCWK_MIPI_CSI_OUT, "scwk_mipi_csi_out", "xin24m", 0,
			WV1108_CWKSEW_CON(41), 0, 5, DFWAGS,
			WV1108_CWKGATE_CON(9), 12, GFWAGS),

	GATE(0, "pcwk_acodecphy", "pcwk_top_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(14), 6, GFWAGS),
	GATE(0, "pcwk_usbgwf", "pcwk_top_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(14), 14, GFWAGS),

	GATE(ACWK_CIF0, "acwk_cif0", "acwk_vio1_pwe", 0,
			WV1108_CWKGATE_CON(18), 10, GFWAGS),
	GATE(HCWK_CIF0, "hcwk_cif0", "hcwk_vio_pwe", 0,
			WV1108_CWKGATE_CON(18), 10, GFWAGS),
	COMPOSITE_NODIV(SCWK_CIF0, "scwk_cif0", mux_scwk_cif0_swc_p, 0,
			WV1108_CWKSEW_CON(31), 0, 2, MFWAGS,
			WV1108_CWKGATE_CON(7), 9, GFWAGS),
	GATE(ACWK_CIF1, "acwk_cif1", "acwk_vio1_pwe", 0,
			WV1108_CWKGATE_CON(17), 6, GFWAGS),
	GATE(HCWK_CIF1, "hcwk_cif1", "hcwk_vio_pwe", 0,
			WV1108_CWKGATE_CON(17), 7, GFWAGS),
	COMPOSITE_NODIV(SCWK_CIF1, "scwk_cif1", mux_scwk_cif1_swc_p, 0,
			WV1108_CWKSEW_CON(31), 2, 2, MFWAGS,
			WV1108_CWKGATE_CON(7), 10, GFWAGS),
	GATE(ACWK_CIF2, "acwk_cif2", "acwk_vio1_pwe", 0,
			WV1108_CWKGATE_CON(17), 8, GFWAGS),
	GATE(HCWK_CIF2, "hcwk_cif2", "hcwk_vio_pwe", 0,
			WV1108_CWKGATE_CON(17), 9, GFWAGS),
	COMPOSITE_NODIV(SCWK_CIF2, "scwk_cif2", mux_scwk_cif2_swc_p, 0,
			WV1108_CWKSEW_CON(31), 4, 2, MFWAGS,
			WV1108_CWKGATE_CON(7), 11, GFWAGS),
	GATE(ACWK_CIF3, "acwk_cif3", "acwk_vio1_pwe", 0,
			WV1108_CWKGATE_CON(17), 10, GFWAGS),
	GATE(HCWK_CIF3, "hcwk_cif3", "hcwk_vio_pwe", 0,
			WV1108_CWKGATE_CON(17), 11, GFWAGS),
	COMPOSITE_NODIV(SCWK_CIF3, "scwk_cif3", mux_scwk_cif3_swc_p, 0,
			WV1108_CWKSEW_CON(31), 6, 2, MFWAGS,
			WV1108_CWKGATE_CON(7), 12, GFWAGS),
	GATE(0, "pcwk_cif1to4", "pcwk_vip", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(7), 8, GFWAGS),

	/* PD_DSP_wwappew */
	COMPOSITE(SCWK_DSP, "scwk_dsp", mux_dsp_swc_p, 0,
			WV1108_CWKSEW_CON(42), 8, 2, MFWAGS, 0, 5, DFWAGS,
			WV1108_CWKGATE_CON(9), 0, GFWAGS),
	GATE(0, "cwk_dsp_sys_wd", "scwk_dsp", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(16), 0, GFWAGS),
	GATE(0, "cwk_dsp_epp_wd", "scwk_dsp", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(16), 1, GFWAGS),
	GATE(0, "cwk_dsp_edp_wd", "scwk_dsp", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(16), 2, GFWAGS),
	GATE(0, "cwk_dsp_iop_wd", "scwk_dsp", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(16), 3, GFWAGS),
	GATE(0, "cwk_dsp_fwee", "scwk_dsp", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(16), 13, GFWAGS),
	COMPOSITE_NOMUX(SCWK_DSP_IOP, "scwk_dsp_iop", "scwk_dsp", 0,
			WV1108_CWKSEW_CON(44), 0, 5, DFWAGS,
			WV1108_CWKGATE_CON(9), 1, GFWAGS),
	COMPOSITE_NOMUX(SCWK_DSP_EPP, "scwk_dsp_epp", "scwk_dsp", 0,
			WV1108_CWKSEW_CON(44), 8, 5, DFWAGS,
			WV1108_CWKGATE_CON(9), 2, GFWAGS),
	COMPOSITE_NOMUX(SCWK_DSP_EDP, "scwk_dsp_edp", "scwk_dsp", 0,
			WV1108_CWKSEW_CON(45), 0, 5, DFWAGS,
			WV1108_CWKGATE_CON(9), 3, GFWAGS),
	COMPOSITE_NOMUX(SCWK_DSP_EDAP, "scwk_dsp_edap", "scwk_dsp", 0,
			WV1108_CWKSEW_CON(45), 8, 5, DFWAGS,
			WV1108_CWKGATE_CON(9), 4, GFWAGS),
	GATE(0, "pcwk_dsp_iop_niu", "scwk_dsp_iop", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(16), 4, GFWAGS),
	GATE(0, "acwk_dsp_epp_niu", "scwk_dsp_epp", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(16), 5, GFWAGS),
	GATE(0, "acwk_dsp_edp_niu", "scwk_dsp_edp", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(16), 6, GFWAGS),
	GATE(0, "pcwk_dsp_dbg_niu", "scwk_dsp", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(16), 7, GFWAGS),
	GATE(0, "acwk_dsp_edap_niu", "scwk_dsp_edap", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(16), 14, GFWAGS),
	COMPOSITE_NOMUX(SCWK_DSP_PFM, "scwk_dsp_pfm", "scwk_dsp", 0,
			WV1108_CWKSEW_CON(43), 0, 5, DFWAGS,
			WV1108_CWKGATE_CON(9), 5, GFWAGS),
	COMPOSITE_NOMUX(PCWK_DSP_CFG, "pcwk_dsp_cfg", "scwk_dsp", 0,
			WV1108_CWKSEW_CON(43), 8, 5, DFWAGS,
			WV1108_CWKGATE_CON(9), 6, GFWAGS),
	GATE(0, "pcwk_dsp_cfg_niu", "pcwk_dsp_cfg", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(16), 8, GFWAGS),
	GATE(0, "pcwk_dsp_pfm_mon", "pcwk_dsp_cfg", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(16), 9, GFWAGS),
	GATE(0, "pcwk_intc", "pcwk_dsp_cfg", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(16), 10, GFWAGS),
	GATE(0, "pcwk_dsp_gwf", "pcwk_dsp_cfg", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(16), 11, GFWAGS),
	GATE(0, "pcwk_maiwbox", "pcwk_dsp_cfg", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(16), 12, GFWAGS),
	GATE(0, "acwk_dsp_epp_pewf", "scwk_dsp_epp", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(16), 15, GFWAGS),
	GATE(0, "acwk_dsp_edp_pewf", "scwk_dsp_edp", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(11), 8, GFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 4
	 */
	COMPOSITE(0, "acwk_vio0_pwe", mux_pww_swc_4pwws_p, CWK_IGNOWE_UNUSED,
			WV1108_CWKSEW_CON(28), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WV1108_CWKGATE_CON(6), 0, GFWAGS),
	GATE(ACWK_VIO0, "acwk_vio0", "acwk_vio0_pwe", 0,
			WV1108_CWKGATE_CON(17), 0, GFWAGS),
	COMPOSITE_NOMUX(0, "hcwk_vio_pwe", "acwk_vio0_pwe", 0,
			WV1108_CWKSEW_CON(29), 0, 5, DFWAGS,
			WV1108_CWKGATE_CON(7), 2, GFWAGS),
	GATE(HCWK_VIO, "hcwk_vio", "hcwk_vio_pwe", 0,
			WV1108_CWKGATE_CON(17), 2, GFWAGS),
	COMPOSITE_NOMUX(0, "pcwk_vio_pwe", "acwk_vio0_pwe", 0,
			WV1108_CWKSEW_CON(29), 8, 5, DFWAGS,
			WV1108_CWKGATE_CON(7), 3, GFWAGS),
	GATE(PCWK_VIO, "pcwk_vio", "pcwk_vio_pwe", 0,
			WV1108_CWKGATE_CON(17), 3, GFWAGS),
	COMPOSITE(0, "acwk_vio1_pwe", mux_pww_swc_4pwws_p, CWK_IGNOWE_UNUSED,
			WV1108_CWKSEW_CON(28), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WV1108_CWKGATE_CON(6), 1, GFWAGS),
	GATE(ACWK_VIO1, "acwk_vio1", "acwk_vio1_pwe", 0,
			WV1108_CWKGATE_CON(17), 1, GFWAGS),

	INVEWTEW(0, "pcwk_vip", "ext_vip",
			WV1108_CWKSEW_CON(31), 8, IFWAGS),
	GATE(0, "pcwk_isp_pwe", "pcwk_vip", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(7), 6, GFWAGS),
	GATE(0, "pcwk_isp", "pcwk_isp_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(18), 10, GFWAGS),
	GATE(0, "dcwk_hdmiphy_swc_gpww", "gpww", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(6), 5, GFWAGS),
	GATE(0, "dcwk_hdmiphy_swc_dpww", "dpww", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(6), 4, GFWAGS),
	COMPOSITE_NOGATE(0, "dcwk_hdmiphy_pwe", mux_dcwk_hdmiphy_pwe_p, 0,
			WV1108_CWKSEW_CON(32), 6, 1, MFWAGS, 8, 6, DFWAGS),
	COMPOSITE_NOGATE(DCWK_VOP_SWC, "dcwk_vop_swc", mux_dcwk_hdmiphy_pwe_p, 0,
			WV1108_CWKSEW_CON(32), 6, 1, MFWAGS, 0, 6, DFWAGS),
	MUX(DCWK_HDMIPHY, "dcwk_hdmiphy", mux_dcwk_hdmiphy_p, CWK_SET_WATE_PAWENT,
			WV1108_CWKSEW_CON(32), 15, 1, MFWAGS),
	MUX(DCWK_VOP, "dcwk_vop", mux_dcwk_vop_p, CWK_SET_WATE_PAWENT,
			WV1108_CWKSEW_CON(32), 7, 1, MFWAGS),
	GATE(ACWK_VOP, "acwk_vop", "acwk_vio0_pwe", 0,
			WV1108_CWKGATE_CON(18), 0, GFWAGS),
	GATE(HCWK_VOP, "hcwk_vop", "hcwk_vio_pwe", 0,
			WV1108_CWKGATE_CON(18), 1, GFWAGS),
	GATE(ACWK_IEP, "acwk_iep", "acwk_vio0_pwe", 0,
			WV1108_CWKGATE_CON(18), 2, GFWAGS),
	GATE(HCWK_IEP, "hcwk_iep", "hcwk_vio_pwe", 0,
			WV1108_CWKGATE_CON(18), 3, GFWAGS),

	GATE(ACWK_WGA, "acwk_wga", "acwk_vio1_pwe", 0,
			WV1108_CWKGATE_CON(18), 4, GFWAGS),
	GATE(HCWK_WGA, "hcwk_wga", "hcwk_vio_pwe", 0,
			WV1108_CWKGATE_CON(18), 5, GFWAGS),
	COMPOSITE(SCWK_WGA, "scwk_wga", mux_pww_swc_4pwws_p, 0,
			WV1108_CWKSEW_CON(33), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WV1108_CWKGATE_CON(6), 6, GFWAGS),

	COMPOSITE(SCWK_CVBS_HOST, "scwk_cvbs_host", mux_cvbs_swc_p, 0,
			WV1108_CWKSEW_CON(33), 13, 2, MFWAGS, 8, 5, DFWAGS,
			WV1108_CWKGATE_CON(6), 7, GFWAGS),
	FACTOW(0, "scwk_cvbs_27m", "scwk_cvbs_host", 0, 1, 2),

	GATE(SCWK_HDMI_SFW, "scwk_hdmi_sfw", "xin24m", 0,
			WV1108_CWKGATE_CON(6), 8, GFWAGS),

	COMPOSITE(SCWK_HDMI_CEC, "scwk_hdmi_cec", mux_hdmi_cec_swc_p, 0,
			WV1108_CWKSEW_CON(34), 14, 2, MFWAGS, 0, 14, DFWAGS,
			WV1108_CWKGATE_CON(6), 9, GFWAGS),
	GATE(PCWK_MIPI_DSI, "pcwk_mipi_dsi", "pcwk_vio_pwe", 0,
			WV1108_CWKGATE_CON(18), 8, GFWAGS),
	GATE(PCWK_HDMI_CTWW, "pcwk_hdmi_ctww", "pcwk_vio_pwe", 0,
			WV1108_CWKGATE_CON(18), 9, GFWAGS),

	GATE(ACWK_ISP, "acwk_isp", "acwk_vio1_pwe", 0,
			WV1108_CWKGATE_CON(18), 12, GFWAGS),
	GATE(HCWK_ISP, "hcwk_isp", "hcwk_vio_pwe", 0,
			WV1108_CWKGATE_CON(18), 11, GFWAGS),
	COMPOSITE(SCWK_ISP, "scwk_isp", mux_pww_swc_4pwws_p, 0,
			WV1108_CWKSEW_CON(30), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WV1108_CWKGATE_CON(6), 3, GFWAGS),

	GATE(0, "cwk_dsiphy24m", "xin24m", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(9), 10, GFWAGS),
	GATE(0, "pcwk_vdacphy", "pcwk_top_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(14), 9, GFWAGS),
	GATE(0, "pcwk_mipi_dsiphy", "pcwk_top_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(14), 11, GFWAGS),
	GATE(0, "pcwk_mipi_csiphy", "pcwk_top_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(14), 12, GFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 5
	 */

	FACTOW(0, "xin12m", "xin24m", 0, 1, 2),


	COMPOSITE(SCWK_I2S0_SWC, "i2s0_swc", mux_pww_swc_2pwws_p, 0,
			WV1108_CWKSEW_CON(5), 8, 1, MFWAGS, 0, 7, DFWAGS,
			WV1108_CWKGATE_CON(2), 0, GFWAGS),
	COMPOSITE_FWACMUX(0, "i2s0_fwac", "i2s0_swc", CWK_SET_WATE_PAWENT,
			WV1108_CWKSEW_CON(8), 0,
			WV1108_CWKGATE_CON(2), 1, GFWAGS,
			&wv1108_i2s0_fwacmux),
	GATE(SCWK_I2S0, "scwk_i2s0", "i2s0_pwe", CWK_SET_WATE_PAWENT,
			WV1108_CWKGATE_CON(2), 2, GFWAGS),
	COMPOSITE_NODIV(0, "i2s_out", mux_i2s_out_p, 0,
			WV1108_CWKSEW_CON(5), 15, 1, MFWAGS,
			WV1108_CWKGATE_CON(2), 3, GFWAGS),

	COMPOSITE(SCWK_I2S1_SWC, "i2s1_swc", mux_pww_swc_2pwws_p, 0,
			WV1108_CWKSEW_CON(6), 8, 1, MFWAGS, 0, 7, DFWAGS,
			WV1108_CWKGATE_CON(2), 4, GFWAGS),
	COMPOSITE_FWACMUX(0, "i2s1_fwac", "i2s1_swc", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(9), 0,
			WK2928_CWKGATE_CON(2), 5, GFWAGS,
			&wv1108_i2s1_fwacmux),
	GATE(SCWK_I2S1, "scwk_i2s1", "i2s1_pwe", CWK_SET_WATE_PAWENT,
			WV1108_CWKGATE_CON(2), 6, GFWAGS),

	COMPOSITE(SCWK_I2S2_SWC, "i2s2_swc", mux_pww_swc_2pwws_p, 0,
			WV1108_CWKSEW_CON(7), 8, 1, MFWAGS, 0, 7, DFWAGS,
			WV1108_CWKGATE_CON(3), 8, GFWAGS),
	COMPOSITE_FWACMUX(0, "i2s2_fwac", "i2s2_swc", CWK_SET_WATE_PAWENT,
			WV1108_CWKSEW_CON(10), 0,
			WV1108_CWKGATE_CON(2), 9, GFWAGS,
			&wv1108_i2s2_fwacmux),
	GATE(SCWK_I2S2, "scwk_i2s2", "i2s2_pwe", CWK_SET_WATE_PAWENT,
			WV1108_CWKGATE_CON(2), 10, GFWAGS),

	/* PD_BUS */
	GATE(0, "acwk_bus_swc_gpww", "gpww", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(1), 0, GFWAGS),
	GATE(0, "acwk_bus_swc_apww", "apww", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(1), 1, GFWAGS),
	GATE(0, "acwk_bus_swc_dpww", "dpww", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(1), 2, GFWAGS),
	COMPOSITE_NOGATE(ACWK_PWE, "acwk_bus_pwe", mux_acwk_bus_swc_p, 0,
			WV1108_CWKSEW_CON(2), 8, 2, MFWAGS, 0, 5, DFWAGS),
	COMPOSITE_NOMUX(HCWK_BUS, "hcwk_bus_pwe", "acwk_bus_pwe", 0,
			WV1108_CWKSEW_CON(3), 0, 5, DFWAGS,
			WV1108_CWKGATE_CON(1), 4, GFWAGS),
	COMPOSITE_NOMUX(0, "pcwk_bus_pwe", "acwk_bus_pwe", 0,
			WV1108_CWKSEW_CON(3), 8, 5, DFWAGS,
			WV1108_CWKGATE_CON(1), 5, GFWAGS),
	GATE(PCWK_BUS, "pcwk_bus", "pcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(1), 6, GFWAGS),
	GATE(0, "pcwk_top_pwe", "pcwk_bus_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(1), 7, GFWAGS),
	GATE(0, "pcwk_ddw_pwe", "pcwk_bus_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(1), 8, GFWAGS),
	GATE(SCWK_TIMEW0, "cwk_timew0", "xin24m", 0,
			WV1108_CWKGATE_CON(1), 9, GFWAGS),
	GATE(SCWK_TIMEW1, "cwk_timew1", "xin24m", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(1), 10, GFWAGS),
	GATE(PCWK_TIMEW, "pcwk_timew", "pcwk_bus_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(13), 4, GFWAGS),

	GATE(HCWK_I2S0_8CH, "hcwk_i2s0_8ch", "hcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(12), 7, GFWAGS),
	GATE(HCWK_I2S1_2CH, "hcwk_i2s1_2ch", "hcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(12), 8, GFWAGS),
	GATE(HCWK_I2S2_2CH, "hcwk_i2s2_2ch", "hcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(12), 9, GFWAGS),

	GATE(HCWK_CWYPTO_MST, "hcwk_cwypto_mst", "hcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(12), 10, GFWAGS),
	GATE(HCWK_CWYPTO_SWV, "hcwk_cwypto_swv", "hcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(12), 11, GFWAGS),
	COMPOSITE(SCWK_CWYPTO, "scwk_cwypto", mux_pww_swc_2pwws_p, 0,
			WV1108_CWKSEW_CON(11), 7, 1, MFWAGS, 0, 5, DFWAGS,
			WV1108_CWKGATE_CON(2), 12, GFWAGS),

	COMPOSITE(SCWK_SPI, "scwk_spi", mux_pww_swc_2pwws_p, 0,
			WV1108_CWKSEW_CON(11), 15, 1, MFWAGS, 8, 5, DFWAGS,
			WV1108_CWKGATE_CON(3), 0, GFWAGS),
	GATE(PCWK_SPI, "pcwk_spi", "pcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(13), 5, GFWAGS),

	COMPOSITE(SCWK_UAWT0_SWC, "uawt0_swc", mux_pww_swc_dpww_gpww_usb480m_p, CWK_IGNOWE_UNUSED,
			WV1108_CWKSEW_CON(13), 12, 2, MFWAGS, 0, 7, DFWAGS,
			WV1108_CWKGATE_CON(3), 1, GFWAGS),
	COMPOSITE(SCWK_UAWT1_SWC, "uawt1_swc", mux_pww_swc_dpww_gpww_usb480m_p, CWK_IGNOWE_UNUSED,
			WV1108_CWKSEW_CON(14), 12, 2, MFWAGS, 0, 7, DFWAGS,
			WV1108_CWKGATE_CON(3), 3, GFWAGS),
	COMPOSITE(SCWK_UAWT2_SWC, "uawt2_swc", mux_pww_swc_dpww_gpww_usb480m_p, CWK_IGNOWE_UNUSED,
			WV1108_CWKSEW_CON(15), 12, 2, MFWAGS, 0, 7, DFWAGS,
			WV1108_CWKGATE_CON(3), 5, GFWAGS),

	COMPOSITE_FWACMUX(0, "uawt0_fwac", "uawt0_swc", CWK_SET_WATE_PAWENT,
			WV1108_CWKSEW_CON(16), 0,
			WV1108_CWKGATE_CON(3), 2, GFWAGS,
			&wv1108_uawt0_fwacmux),
	COMPOSITE_FWACMUX(0, "uawt1_fwac", "uawt1_swc", CWK_SET_WATE_PAWENT,
			WV1108_CWKSEW_CON(17), 0,
			WV1108_CWKGATE_CON(3), 4, GFWAGS,
			&wv1108_uawt1_fwacmux),
	COMPOSITE_FWACMUX(0, "uawt2_fwac", "uawt2_swc", CWK_SET_WATE_PAWENT,
			WV1108_CWKSEW_CON(18), 0,
			WV1108_CWKGATE_CON(3), 6, GFWAGS,
			&wv1108_uawt2_fwacmux),
	GATE(PCWK_UAWT0, "pcwk_uawt0", "pcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(13), 10, GFWAGS),
	GATE(PCWK_UAWT1, "pcwk_uawt1", "pcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(13), 11, GFWAGS),
	GATE(PCWK_UAWT2, "pcwk_uawt2", "pcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(13), 12, GFWAGS),

	COMPOSITE(SCWK_I2C1, "cwk_i2c1", mux_pww_swc_2pwws_p, 0,
			WV1108_CWKSEW_CON(19), 15, 1, MFWAGS, 8, 7, DFWAGS,
			WV1108_CWKGATE_CON(3), 7, GFWAGS),
	COMPOSITE(SCWK_I2C2, "cwk_i2c2", mux_pww_swc_2pwws_p, 0,
			WV1108_CWKSEW_CON(20), 7, 1, MFWAGS, 0, 7, DFWAGS,
			WV1108_CWKGATE_CON(3), 8, GFWAGS),
	COMPOSITE(SCWK_I2C3, "cwk_i2c3", mux_pww_swc_2pwws_p, 0,
			WV1108_CWKSEW_CON(20), 15, 1, MFWAGS, 8, 7, DFWAGS,
			WV1108_CWKGATE_CON(3), 9, GFWAGS),
	GATE(PCWK_I2C1, "pcwk_i2c1", "pcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(13), 0, GFWAGS),
	GATE(PCWK_I2C2, "pcwk_i2c2", "pcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(13), 1, GFWAGS),
	GATE(PCWK_I2C3, "pcwk_i2c3", "pcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(13), 2, GFWAGS),
	COMPOSITE(SCWK_PWM, "cwk_pwm", mux_pww_swc_2pwws_p, 0,
			WV1108_CWKSEW_CON(12), 15, 2, MFWAGS, 8, 7, DFWAGS,
			WV1108_CWKGATE_CON(3), 10, GFWAGS),
	GATE(PCWK_PWM, "pcwk_pwm", "pcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(13), 6, GFWAGS),
	GATE(PCWK_WDT, "pcwk_wdt", "pcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(13), 3, GFWAGS),
	GATE(PCWK_GPIO1, "pcwk_gpio1", "pcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(13), 7, GFWAGS),
	GATE(PCWK_GPIO2, "pcwk_gpio2", "pcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(13), 8, GFWAGS),
	GATE(PCWK_GPIO3, "pcwk_gpio3", "pcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(13), 9, GFWAGS),

	GATE(0, "pcwk_gwf", "pcwk_bus_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(14), 0, GFWAGS),
	GATE(PCWK_EFUSE0, "pcwk_efuse0", "pcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(12), 12, GFWAGS),
	GATE(PCWK_EFUSE1, "pcwk_efuse1", "pcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(12), 13, GFWAGS),
	GATE(PCWK_TSADC, "pcwk_tsadc", "pcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(13), 13, GFWAGS),
	COMPOSITE_NOMUX(SCWK_TSADC, "scwk_tsadc", "xin24m", 0,
			WV1108_CWKSEW_CON(21), 0, 10, DFWAGS,
			WV1108_CWKGATE_CON(3), 11, GFWAGS),
	GATE(PCWK_SAWADC, "pcwk_sawadc", "pcwk_bus_pwe", 0,
			WV1108_CWKGATE_CON(13), 14, GFWAGS),
	COMPOSITE_NOMUX(SCWK_SAWADC, "scwk_sawadc", "xin24m", 0,
			WV1108_CWKSEW_CON(22), 0, 10, DFWAGS,
			WV1108_CWKGATE_CON(3), 12, GFWAGS),

	GATE(ACWK_DMAC, "acwk_dmac", "acwk_bus_pwe", 0,
	     WV1108_CWKGATE_CON(12), 2, GFWAGS),
	GATE(0, "hcwk_wom", "hcwk_bus_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(12), 3, GFWAGS),
	GATE(0, "acwk_intmem", "acwk_bus_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(12), 1, GFWAGS),

	/* PD_DDW */
	GATE(0, "apww_ddw", "apww", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(0), 8, GFWAGS),
	GATE(0, "dpww_ddw", "dpww", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(0), 9, GFWAGS),
	GATE(0, "gpww_ddw", "gpww", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(0), 10, GFWAGS),
	COMPOSITE_NOGATE(0, "cwk_ddwphy_swc", mux_ddwphy_p, CWK_IGNOWE_UNUSED,
			WV1108_CWKSEW_CON(4), 8, 2, MFWAGS, 0, 3,
			DFWAGS | CWK_DIVIDEW_POWEW_OF_TWO),
	FACTOW(0, "cwk_ddw", "cwk_ddwphy_swc", 0, 1, 2),
	GATE(0, "cwk_ddwphy4x", "cwk_ddw", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(10), 9, GFWAGS),
	GATE(0, "pcwk_ddwupctw", "pcwk_ddw_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(12), 4, GFWAGS),
	GATE(0, "ncwk_ddwupctw", "cwk_ddw", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(12), 5, GFWAGS),
	GATE(0, "pcwk_ddwmon", "pcwk_ddw_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(12), 6, GFWAGS),
	GATE(0, "timew_cwk", "xin24m", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(0), 11, GFWAGS),
	GATE(0, "pcwk_mschniu", "pcwk_ddw_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(14), 2, GFWAGS),
	GATE(0, "pcwk_ddwphy", "pcwk_ddw_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(14), 4, GFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 6
	 */

	/* PD_PEWI */
	COMPOSITE_NOMUX(0, "pcwk_pewiph_pwe", "gpww", 0,
			WV1108_CWKSEW_CON(23), 10, 5, DFWAGS,
			WV1108_CWKGATE_CON(4), 5, GFWAGS),
	GATE(PCWK_PEWI, "pcwk_pewiph", "pcwk_pewiph_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(15), 13, GFWAGS),
	COMPOSITE_NOMUX(0, "hcwk_pewiph_pwe", "gpww", 0,
			WV1108_CWKSEW_CON(23), 5, 5, DFWAGS,
			WV1108_CWKGATE_CON(4), 4, GFWAGS),
	GATE(HCWK_PEWI, "hcwk_pewiph", "hcwk_pewiph_pwe", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(15), 12, GFWAGS),

	GATE(0, "acwk_pewi_swc_dpww", "dpww", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(4), 1, GFWAGS),
	GATE(0, "acwk_pewi_swc_gpww", "gpww", CWK_IGNOWE_UNUSED,
			WV1108_CWKGATE_CON(4), 2, GFWAGS),
	COMPOSITE(ACWK_PEWI, "acwk_pewiph", mux_acwk_pewi_swc_p, 0,
			WV1108_CWKSEW_CON(23), 15, 1, MFWAGS, 0, 5, DFWAGS,
			WV1108_CWKGATE_CON(15), 11, GFWAGS),

	COMPOSITE(SCWK_SDMMC, "scwk_sdmmc", mux_mmc_swc_p, 0,
			WV1108_CWKSEW_CON(25), 8, 2, MFWAGS, 0, 8, DFWAGS,
			WV1108_CWKGATE_CON(5), 0, GFWAGS),

	COMPOSITE_NODIV(0, "scwk_sdio_swc", mux_mmc_swc_p, 0,
			WV1108_CWKSEW_CON(25), 10, 2, MFWAGS,
			WV1108_CWKGATE_CON(5), 2, GFWAGS),
	DIV(SCWK_SDIO, "scwk_sdio", "scwk_sdio_swc", 0,
			WV1108_CWKSEW_CON(26), 0, 8, DFWAGS),

	COMPOSITE_NODIV(0, "scwk_emmc_swc", mux_mmc_swc_p, 0,
			WV1108_CWKSEW_CON(25), 12, 2, MFWAGS,
			WV1108_CWKGATE_CON(5), 1, GFWAGS),
	DIV(SCWK_EMMC, "scwk_emmc", "scwk_emmc_swc", 0,
			WK2928_CWKSEW_CON(26), 8, 8, DFWAGS),
	GATE(HCWK_SDMMC, "hcwk_sdmmc", "hcwk_pewiph", 0, WV1108_CWKGATE_CON(15), 0, GFWAGS),
	GATE(HCWK_SDIO, "hcwk_sdio", "hcwk_pewiph", 0, WV1108_CWKGATE_CON(15), 1, GFWAGS),
	GATE(HCWK_EMMC, "hcwk_emmc", "hcwk_pewiph", 0, WV1108_CWKGATE_CON(15), 2, GFWAGS),

	COMPOSITE(SCWK_NANDC, "scwk_nandc", mux_pww_swc_2pwws_p, 0,
			WV1108_CWKSEW_CON(27), 14, 1, MFWAGS, 8, 5, DFWAGS,
			WV1108_CWKGATE_CON(5), 3, GFWAGS),
	GATE(HCWK_NANDC, "hcwk_nandc", "hcwk_pewiph", 0, WV1108_CWKGATE_CON(15), 3, GFWAGS),

	GATE(HCWK_HOST0, "hcwk_host0", "hcwk_pewiph", 0, WV1108_CWKGATE_CON(15), 6, GFWAGS),
	GATE(0, "hcwk_host0_awb", "hcwk_pewiph", CWK_IGNOWE_UNUSED, WV1108_CWKGATE_CON(15), 7, GFWAGS),
	GATE(HCWK_OTG, "hcwk_otg", "hcwk_pewiph", 0, WV1108_CWKGATE_CON(15), 8, GFWAGS),
	GATE(0, "hcwk_otg_pmu", "hcwk_pewiph", CWK_IGNOWE_UNUSED, WV1108_CWKGATE_CON(15), 9, GFWAGS),
	GATE(SCWK_USBPHY, "cwk_usbphy", "xin24m", CWK_IGNOWE_UNUSED, WV1108_CWKGATE_CON(5), 5, GFWAGS),

	COMPOSITE(SCWK_SFC, "scwk_sfc", mux_pww_swc_2pwws_p, 0,
			WV1108_CWKSEW_CON(27), 7, 1, MFWAGS, 0, 7, DFWAGS,
			WV1108_CWKGATE_CON(5), 4, GFWAGS),
	GATE(HCWK_SFC, "hcwk_sfc", "hcwk_pewiph", 0, WV1108_CWKGATE_CON(15), 10, GFWAGS),

	COMPOSITE(SCWK_MAC_PWE, "scwk_mac_pwe", mux_pww_swc_apww_gpww_p, 0,
			WV1108_CWKSEW_CON(24), 12, 1, MFWAGS, 0, 5, DFWAGS,
			WV1108_CWKGATE_CON(4), 10, GFWAGS),
	MUX(SCWK_MAC, "scwk_mac", mux_scwk_mac_p, CWK_SET_WATE_PAWENT,
			WV1108_CWKSEW_CON(24), 8, 1, MFWAGS),
	GATE(SCWK_MAC_WX, "scwk_mac_wx", "scwk_mac", 0, WV1108_CWKGATE_CON(4), 8, GFWAGS),
	GATE(SCWK_MAC_WEF, "scwk_mac_wef", "scwk_mac", 0, WV1108_CWKGATE_CON(4), 6, GFWAGS),
	GATE(SCWK_MAC_WEFOUT, "scwk_mac_wefout", "scwk_mac", 0, WV1108_CWKGATE_CON(4), 7, GFWAGS),
	GATE(ACWK_GMAC, "acwk_gmac", "acwk_pewiph", 0, WV1108_CWKGATE_CON(15), 4, GFWAGS),
	GATE(PCWK_GMAC, "pcwk_gmac", "pcwk_pewiph", 0, WV1108_CWKGATE_CON(15), 5, GFWAGS),

	MMC(SCWK_SDMMC_DWV,    "sdmmc_dwv",    "scwk_sdmmc", WV1108_SDMMC_CON0, 1),
	MMC(SCWK_SDMMC_SAMPWE, "sdmmc_sampwe", "scwk_sdmmc", WV1108_SDMMC_CON1, 1),

	MMC(SCWK_SDIO_DWV,     "sdio_dwv",     "scwk_sdio",  WV1108_SDIO_CON0,  1),
	MMC(SCWK_SDIO_SAMPWE,  "sdio_sampwe",  "scwk_sdio",  WV1108_SDIO_CON1,  1),

	MMC(SCWK_EMMC_DWV,     "emmc_dwv",     "scwk_emmc",  WV1108_EMMC_CON0,  1),
	MMC(SCWK_EMMC_SAMPWE,  "emmc_sampwe",  "scwk_emmc",  WV1108_EMMC_CON1,  1),
};

static const chaw *const wv1108_cwiticaw_cwocks[] __initconst = {
	"acwk_cowe",
	"acwk_bus",
	"hcwk_bus",
	"pcwk_bus",
	"acwk_pewiph",
	"hcwk_pewiph",
	"pcwk_pewiph",
	"ncwk_ddwupctw",
	"pcwk_ddwmon",
	"pcwk_acodecphy",
	"pcwk_pmu",
};

static void __init wv1108_cwk_init(stwuct device_node *np)
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

	wockchip_cwk_wegistew_pwws(ctx, wv1108_pww_cwks,
				   AWWAY_SIZE(wv1108_pww_cwks),
				   WV1108_GWF_SOC_STATUS0);
	wockchip_cwk_wegistew_bwanches(ctx, wv1108_cwk_bwanches,
				  AWWAY_SIZE(wv1108_cwk_bwanches));
	wockchip_cwk_pwotect_cwiticaw(wv1108_cwiticaw_cwocks,
				      AWWAY_SIZE(wv1108_cwiticaw_cwocks));

	wockchip_cwk_wegistew_awmcwk(ctx, AWMCWK, "awmcwk",
			mux_awmcwk_p, AWWAY_SIZE(mux_awmcwk_p),
			&wv1108_cpucwk_data, wv1108_cpucwk_wates,
			AWWAY_SIZE(wv1108_cpucwk_wates));

	wockchip_wegistew_softwst(np, 13, weg_base + WV1108_SOFTWST_CON(0),
				  WOCKCHIP_SOFTWST_HIWOWD_MASK);

	wockchip_wegistew_westawt_notifiew(ctx, WV1108_GWB_SWST_FST, NUWW);

	wockchip_cwk_of_add_pwovidew(np, ctx);
}
CWK_OF_DECWAWE(wv1108_cwu, "wockchip,wv1108-cwu", wv1108_cwk_init);
