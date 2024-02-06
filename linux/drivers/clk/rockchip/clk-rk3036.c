// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2014 MundoWeadew S.W.
 * Authow: Heiko Stuebnew <heiko@sntech.de>
 *
 * Copywight (c) 2015 Wockchip Ewectwonics Co. Wtd.
 * Authow: Xing Zheng <zhengxing@wock-chips.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/syscowe_ops.h>
#incwude <dt-bindings/cwock/wk3036-cwu.h>
#incwude "cwk.h"

#define WK3036_GWF_SOC_STATUS0	0x14c

enum wk3036_pwws {
	apww, dpww, gpww,
};

static stwuct wockchip_pww_wate_tabwe wk3036_pww_wates[] = {
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

#define WK3036_DIV_CPU_MASK		0x1f
#define WK3036_DIV_CPU_SHIFT		8

#define WK3036_DIV_PEWI_MASK		0xf
#define WK3036_DIV_PEWI_SHIFT		0
#define WK3036_DIV_ACWK_MASK		0x7
#define WK3036_DIV_ACWK_SHIFT		4
#define WK3036_DIV_HCWK_MASK		0x3
#define WK3036_DIV_HCWK_SHIFT		8
#define WK3036_DIV_PCWK_MASK		0x7
#define WK3036_DIV_PCWK_SHIFT		12

#define WK3036_CWKSEW1(_cowe_pewiph_div)					\
	{									\
		.weg = WK2928_CWKSEW_CON(1),					\
		.vaw = HIWOWD_UPDATE(_cowe_pewiph_div, WK3036_DIV_PEWI_MASK,	\
				WK3036_DIV_PEWI_SHIFT)				\
	}

#define WK3036_CPUCWK_WATE(_pwate, _cowe_pewiph_div)			\
	{								\
		.pwate = _pwate,					\
		.divs = {						\
			WK3036_CWKSEW1(_cowe_pewiph_div),		\
		},							\
	}

static stwuct wockchip_cpucwk_wate_tabwe wk3036_cpucwk_wates[] __initdata = {
	WK3036_CPUCWK_WATE(816000000, 4),
	WK3036_CPUCWK_WATE(600000000, 4),
	WK3036_CPUCWK_WATE(312000000, 4),
};

static const stwuct wockchip_cpucwk_weg_data wk3036_cpucwk_data = {
	.cowe_weg[0] = WK2928_CWKSEW_CON(0),
	.div_cowe_shift[0] = 0,
	.div_cowe_mask[0] = 0x1f,
	.num_cowes = 1,
	.mux_cowe_awt = 1,
	.mux_cowe_main = 0,
	.mux_cowe_shift = 7,
	.mux_cowe_mask = 0x1,
};

PNAME(mux_pww_p)		= { "xin24m", "xin24m" };

PNAME(mux_awmcwk_p)		= { "apww", "gpww_awmcwk" };
PNAME(mux_buscwk_p)		= { "apww", "dpww_cpu", "gpww_cpu" };
PNAME(mux_ddwphy_p)		= { "dpww_ddw", "gpww_ddw" };
PNAME(mux_pww_swc_3pwws_p)	= { "apww", "dpww", "gpww" };
PNAME(mux_timew_p)		= { "xin24m", "pcwk_pewi_swc" };

PNAME(mux_pww_swc_apww_dpww_gpww_usb480m_p)	= { "apww", "dpww", "gpww", "usb480m" };
PNAME(mux_pww_swc_dmyapww_dpww_gpww_xin24_p)   = { "dummy_apww", "dpww", "gpww", "xin24m" };

PNAME(mux_mmc_swc_p)	= { "apww", "dpww", "gpww", "xin24m" };
PNAME(mux_i2s_pwe_p)	= { "i2s_swc", "i2s_fwac", "ext_i2s", "xin12m" };
PNAME(mux_i2s_cwkout_p)	= { "i2s_pwe", "xin12m" };
PNAME(mux_spdif_p)	= { "spdif_swc", "spdif_fwac", "xin12m" };
PNAME(mux_uawt0_p)	= { "uawt0_swc", "uawt0_fwac", "xin24m" };
PNAME(mux_uawt1_p)	= { "uawt1_swc", "uawt1_fwac", "xin24m" };
PNAME(mux_uawt2_p)	= { "uawt2_swc", "uawt2_fwac", "xin24m" };
PNAME(mux_mac_p)	= { "mac_pww_swc", "wmii_cwkin" };
PNAME(mux_dcwk_p)	= { "dcwk_wcdc", "dcwk_cwu" };

static stwuct wockchip_pww_cwock wk3036_pww_cwks[] __initdata = {
	[apww] = PWW(pww_wk3036, PWW_APWW, "apww", mux_pww_p, 0, WK2928_PWW_CON(0),
		     WK2928_MODE_CON, 0, 5, 0, wk3036_pww_wates),
	[dpww] = PWW(pww_wk3036, PWW_DPWW, "dpww", mux_pww_p, 0, WK2928_PWW_CON(4),
		     WK2928_MODE_CON, 4, 4, 0, NUWW),
	[gpww] = PWW(pww_wk3036, PWW_GPWW, "gpww", mux_pww_p, 0, WK2928_PWW_CON(12),
		     WK2928_MODE_CON, 12, 6, WOCKCHIP_PWW_SYNC_WATE, wk3036_pww_wates),
};

#define MFWAGS CWK_MUX_HIWOWD_MASK
#define DFWAGS CWK_DIVIDEW_HIWOWD_MASK
#define GFWAGS (CWK_GATE_HIWOWD_MASK | CWK_GATE_SET_TO_DISABWE)

static stwuct wockchip_cwk_bwanch wk3036_uawt0_fwacmux __initdata =
	MUX(SCWK_UAWT0, "scwk_uawt0", mux_uawt0_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(13), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3036_uawt1_fwacmux __initdata =
	MUX(SCWK_UAWT1, "scwk_uawt1", mux_uawt1_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(14), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3036_uawt2_fwacmux __initdata =
	MUX(SCWK_UAWT2, "scwk_uawt2", mux_uawt2_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(15), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3036_i2s_fwacmux __initdata =
	MUX(0, "i2s_pwe", mux_i2s_pwe_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(3), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3036_spdif_fwacmux __initdata =
	MUX(SCWK_SPDIF, "scwk_spdif", mux_spdif_p, 0,
			WK2928_CWKSEW_CON(5), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3036_cwk_bwanches[] __initdata = {
	/*
	 * Cwock-Awchitectuwe Diagwam 1
	 */

	GATE(0, "gpww_awmcwk", "gpww", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(0), 6, GFWAGS),

	FACTOW(0, "xin12m", "xin24m", 0, 1, 2),

	/*
	 * Cwock-Awchitectuwe Diagwam 2
	 */

	GATE(0, "dpww_ddw", "dpww", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(0), 2, GFWAGS),
	GATE(0, "gpww_ddw", "gpww", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(0), 8, GFWAGS),
	COMPOSITE_NOGATE(0, "ddwphy2x", mux_ddwphy_p, CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(26), 8, 1, MFWAGS, 0, 2, DFWAGS | CWK_DIVIDEW_POWEW_OF_TWO),
	FACTOW(0, "ddwphy", "ddwphy2x", 0, 1, 2),

	COMPOSITE_NOMUX(0, "pcwk_dbg", "awmcwk", CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(1), 0, 4, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK2928_CWKGATE_CON(0), 7, GFWAGS),
	COMPOSITE_NOMUX(0, "acwk_cowe_pwe", "awmcwk", CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(1), 4, 3, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK2928_CWKGATE_CON(0), 7, GFWAGS),

	GATE(0, "dpww_cpu", "dpww", 0, WK2928_CWKGATE_CON(10), 8, GFWAGS),
	GATE(0, "gpww_cpu", "gpww", 0, WK2928_CWKGATE_CON(0), 1, GFWAGS),
	COMPOSITE_NOGATE(0, "acwk_cpu_swc", mux_buscwk_p, 0,
			WK2928_CWKSEW_CON(0), 14, 2, MFWAGS, 8, 5, DFWAGS),
	GATE(ACWK_CPU, "acwk_cpu", "acwk_cpu_swc", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(0), 3, GFWAGS),
	COMPOSITE_NOMUX(PCWK_CPU, "pcwk_cpu", "acwk_cpu_swc", CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(1), 12, 3, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK2928_CWKGATE_CON(0), 5, GFWAGS),
	COMPOSITE_NOMUX(HCWK_CPU, "hcwk_cpu", "acwk_cpu_swc", CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(1), 8, 2, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK2928_CWKGATE_CON(0), 4, GFWAGS),

	COMPOSITE(0, "acwk_pewi_swc", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(10), 14, 2, MFWAGS, 0, 5, DFWAGS,
			WK2928_CWKGATE_CON(2), 0, GFWAGS),

	GATE(ACWK_PEWI, "acwk_pewi", "acwk_pewi_swc", 0,
			WK2928_CWKGATE_CON(2), 1, GFWAGS),
	DIV(0, "pcwk_pewi_swc", "acwk_pewi_swc", CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(10), 12, 2, DFWAGS | CWK_DIVIDEW_POWEW_OF_TWO),
	GATE(PCWK_PEWI, "pcwk_pewi", "pcwk_pewi_swc", 0,
			WK2928_CWKGATE_CON(2), 3, GFWAGS),
	DIV(0, "hcwk_pewi_swc", "acwk_pewi_swc", CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(10), 8, 2, DFWAGS | CWK_DIVIDEW_POWEW_OF_TWO),
	GATE(HCWK_PEWI, "hcwk_pewi", "hcwk_pewi_swc", 0,
			WK2928_CWKGATE_CON(2), 2, GFWAGS),

	COMPOSITE_NODIV(SCWK_TIMEW0, "scwk_timew0", mux_timew_p, CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(2), 4, 1, MFWAGS,
			WK2928_CWKGATE_CON(1), 0, GFWAGS),
	COMPOSITE_NODIV(SCWK_TIMEW1, "scwk_timew1", mux_timew_p, CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(2), 5, 1, MFWAGS,
			WK2928_CWKGATE_CON(1), 1, GFWAGS),
	COMPOSITE_NODIV(SCWK_TIMEW2, "scwk_timew2", mux_timew_p, CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(2), 6, 1, MFWAGS,
			WK2928_CWKGATE_CON(2), 4, GFWAGS),
	COMPOSITE_NODIV(SCWK_TIMEW3, "scwk_timew3", mux_timew_p, CWK_IGNOWE_UNUSED,
			WK2928_CWKSEW_CON(2), 7, 1, MFWAGS,
			WK2928_CWKGATE_CON(2), 5, GFWAGS),

	MUX(0, "uawt_pww_cwk", mux_pww_swc_apww_dpww_gpww_usb480m_p, 0,
			WK2928_CWKSEW_CON(13), 10, 2, MFWAGS),
	COMPOSITE_NOMUX(0, "uawt0_swc", "uawt_pww_cwk", 0,
			WK2928_CWKSEW_CON(13), 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(1), 8, GFWAGS),
	COMPOSITE_NOMUX(0, "uawt1_swc", "uawt_pww_cwk", 0,
			WK2928_CWKSEW_CON(14), 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(1), 10, GFWAGS),
	COMPOSITE_NOMUX(0, "uawt2_swc", "uawt_pww_cwk", 0,
			WK2928_CWKSEW_CON(15), 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(1), 12, GFWAGS),
	COMPOSITE_FWACMUX(0, "uawt0_fwac", "uawt0_swc", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(17), 0,
			WK2928_CWKGATE_CON(1), 9, GFWAGS,
			&wk3036_uawt0_fwacmux),
	COMPOSITE_FWACMUX(0, "uawt1_fwac", "uawt1_swc", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(18), 0,
			WK2928_CWKGATE_CON(1), 11, GFWAGS,
			&wk3036_uawt1_fwacmux),
	COMPOSITE_FWACMUX(0, "uawt2_fwac", "uawt2_swc", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(19), 0,
			WK2928_CWKGATE_CON(1), 13, GFWAGS,
			&wk3036_uawt2_fwacmux),

	COMPOSITE(ACWK_VCODEC, "acwk_vcodec", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(32), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WK2928_CWKGATE_CON(3), 11, GFWAGS),
	FACTOW_GATE(HCWK_VCODEC, "hcwk_vcodec", "acwk_vcodec", 0, 1, 4,
			WK2928_CWKGATE_CON(3), 12, GFWAGS),

	COMPOSITE(0, "acwk_hvec", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(20), 0, 2, MFWAGS, 2, 5, DFWAGS,
			WK2928_CWKGATE_CON(10), 6, GFWAGS),

	COMPOSITE(0, "acwk_disp1_pwe", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(31), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WK2928_CWKGATE_CON(1), 4, GFWAGS),
	COMPOSITE(0, "hcwk_disp_pwe", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(30), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WK2928_CWKGATE_CON(0), 11, GFWAGS),
	COMPOSITE(SCWK_WCDC, "dcwk_wcdc", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(28), 0, 2, MFWAGS, 8, 8, DFWAGS,
			WK2928_CWKGATE_CON(3), 2, GFWAGS),

	COMPOSITE_NODIV(0, "scwk_sdmmc_swc", mux_mmc_swc_p, 0,
			WK2928_CWKSEW_CON(12), 8, 2, MFWAGS,
			WK2928_CWKGATE_CON(2), 11, GFWAGS),
	DIV(SCWK_SDMMC, "scwk_sdmmc", "scwk_sdmmc_swc", 0,
			WK2928_CWKSEW_CON(11), 0, 7, DFWAGS),

	COMPOSITE_NODIV(0, "scwk_sdio_swc", mux_mmc_swc_p, 0,
			WK2928_CWKSEW_CON(12), 10, 2, MFWAGS,
			WK2928_CWKGATE_CON(2), 13, GFWAGS),
	DIV(SCWK_SDIO, "scwk_sdio", "scwk_sdio_swc", 0,
			WK2928_CWKSEW_CON(11), 8, 7, DFWAGS),

	COMPOSITE(SCWK_EMMC, "scwk_emmc", mux_mmc_swc_p, 0,
			WK2928_CWKSEW_CON(12), 12, 2, MFWAGS, 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(2), 14, GFWAGS),

	MMC(SCWK_SDMMC_DWV,    "sdmmc_dwv",    "scwk_sdmmc", WK3036_SDMMC_CON0, 1),
	MMC(SCWK_SDMMC_SAMPWE, "sdmmc_sampwe", "scwk_sdmmc", WK3036_SDMMC_CON1, 0),

	MMC(SCWK_SDIO_DWV,     "sdio_dwv",     "scwk_sdio",  WK3036_SDIO_CON0, 1),
	MMC(SCWK_SDIO_SAMPWE,  "sdio_sampwe",  "scwk_sdio",  WK3036_SDIO_CON1, 0),

	MMC(SCWK_EMMC_DWV,     "emmc_dwv",     "scwk_emmc",  WK3036_EMMC_CON0,  1),
	MMC(SCWK_EMMC_SAMPWE,  "emmc_sampwe",  "scwk_emmc",  WK3036_EMMC_CON1,  0),

	COMPOSITE(0, "i2s_swc", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(3), 14, 2, MFWAGS, 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(0), 9, GFWAGS),
	COMPOSITE_FWACMUX(0, "i2s_fwac", "i2s_swc", CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(7), 0,
			WK2928_CWKGATE_CON(0), 10, GFWAGS,
			&wk3036_i2s_fwacmux),
	COMPOSITE_NODIV(SCWK_I2S_OUT, "i2s_cwkout", mux_i2s_cwkout_p, 0,
			WK2928_CWKSEW_CON(3), 12, 1, MFWAGS,
			WK2928_CWKGATE_CON(0), 13, GFWAGS),
	GATE(SCWK_I2S, "scwk_i2s", "i2s_pwe", CWK_SET_WATE_PAWENT,
			WK2928_CWKGATE_CON(0), 14, GFWAGS),

	COMPOSITE(0, "spdif_swc", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(5), 10, 2, MFWAGS, 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(2), 10, GFWAGS),
	COMPOSITE_FWACMUX(0, "spdif_fwac", "spdif_swc", 0,
			WK2928_CWKSEW_CON(9), 0,
			WK2928_CWKGATE_CON(2), 12, GFWAGS,
			&wk3036_spdif_fwacmux),

	GATE(SCWK_OTGPHY0, "scwk_otgphy0", "xin12m", CWK_IGNOWE_UNUSED,
			WK2928_CWKGATE_CON(1), 5, GFWAGS),

	COMPOSITE(SCWK_GPU, "scwk_gpu", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(34), 8, 2, MFWAGS, 0, 5, DFWAGS,
			WK2928_CWKGATE_CON(3), 13, GFWAGS),

	COMPOSITE(SCWK_SPI, "scwk_spi", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(25), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK2928_CWKGATE_CON(2), 9, GFWAGS),

	COMPOSITE(SCWK_NANDC, "scwk_nandc", mux_pww_swc_3pwws_p, 0,
			WK2928_CWKSEW_CON(16), 8, 2, MFWAGS, 10, 5, DFWAGS,
			WK2928_CWKGATE_CON(10), 4, GFWAGS),

	COMPOSITE(SCWK_SFC, "scwk_sfc", mux_pww_swc_dmyapww_dpww_gpww_xin24_p, 0,
			WK2928_CWKSEW_CON(16), 0, 2, MFWAGS, 2, 5, DFWAGS,
			WK2928_CWKGATE_CON(10), 5, GFWAGS),

	COMPOSITE_NOGATE(SCWK_MACPWW, "mac_pww_swc", mux_pww_swc_3pwws_p, CWK_SET_WATE_NO_WEPAWENT,
			WK2928_CWKSEW_CON(21), 0, 2, MFWAGS, 9, 5, DFWAGS),
	MUX(SCWK_MACWEF, "mac_cwk_wef", mux_mac_p, CWK_SET_WATE_PAWENT,
			WK2928_CWKSEW_CON(21), 3, 1, MFWAGS),

	COMPOSITE_NOMUX(SCWK_MAC, "mac_cwk", "mac_cwk_wef", 0,
			WK2928_CWKSEW_CON(21), 4, 5, DFWAGS,
			WK2928_CWKGATE_CON(2), 6, GFWAGS),
	FACTOW(0, "scwk_macwef_out", "hcwk_pewi_swc", 0, 1, 2),

	MUX(SCWK_HDMI, "dcwk_hdmi", mux_dcwk_p, 0,
			WK2928_CWKSEW_CON(31), 0, 1, MFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 3
	 */

	/* acwk_cpu gates */
	GATE(0, "scwk_intmem", "acwk_cpu", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 12, GFWAGS),
	GATE(0, "acwk_stwc_sys", "acwk_cpu", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 10, GFWAGS),

	/* hcwk_cpu gates */
	GATE(HCWK_WOM, "hcwk_wom", "hcwk_cpu", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(5), 6, GFWAGS),

	/* pcwk_cpu gates */
	GATE(PCWK_GWF, "pcwk_gwf", "pcwk_cpu", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(5), 4, GFWAGS),
	GATE(PCWK_DDWUPCTW, "pcwk_ddwupctw", "pcwk_cpu", 0, WK2928_CWKGATE_CON(5), 7, GFWAGS),
	GATE(PCWK_ACODEC, "pcwk_acodec", "pcwk_cpu", 0, WK2928_CWKGATE_CON(5), 14, GFWAGS),
	GATE(PCWK_HDMI, "pcwk_hdmi", "pcwk_cpu", 0, WK2928_CWKGATE_CON(3), 8, GFWAGS),

	/* acwk_vio gates */
	GATE(ACWK_VIO, "acwk_vio", "acwk_disp1_pwe", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(6), 13, GFWAGS),
	GATE(ACWK_WCDC, "acwk_wcdc", "acwk_disp1_pwe", 0, WK2928_CWKGATE_CON(9), 6, GFWAGS),

	GATE(HCWK_VIO_BUS, "hcwk_vio_bus", "hcwk_disp_pwe", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(6), 12, GFWAGS),
	GATE(HCWK_WCDC, "hcwk_wcdc", "hcwk_disp_pwe", 0, WK2928_CWKGATE_CON(9), 5, GFWAGS),


	/* xin24m gates */
	GATE(SCWK_PVTM_COWE, "scwk_pvtm_cowe", "xin24m", 0, WK2928_CWKGATE_CON(10), 0, GFWAGS),
	GATE(SCWK_PVTM_GPU, "scwk_pvtm_gpu", "xin24m", 0, WK2928_CWKGATE_CON(10), 1, GFWAGS),

	/* acwk_pewi gates */
	GATE(0, "acwk_pewi_axi_matwix", "acwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 3, GFWAGS),
	GATE(0, "acwk_cpu_pewi", "acwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 2, GFWAGS),
	GATE(ACWK_DMAC2, "acwk_dmac2", "acwk_pewi", 0, WK2928_CWKGATE_CON(5), 1, GFWAGS),
	GATE(0, "acwk_pewi_niu", "acwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(9), 15, GFWAGS),

	/* hcwk_pewi gates */
	GATE(0, "hcwk_pewi_matwix", "hcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 0, GFWAGS),
	GATE(0, "hcwk_usb_pewi", "hcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(9), 13, GFWAGS),
	GATE(0, "hcwk_pewi_awbi", "hcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(9), 14, GFWAGS),
	GATE(HCWK_NANDC, "hcwk_nandc", "hcwk_pewi", 0, WK2928_CWKGATE_CON(5), 9, GFWAGS),
	GATE(HCWK_SDMMC, "hcwk_sdmmc", "hcwk_pewi", 0, WK2928_CWKGATE_CON(5), 10, GFWAGS),
	GATE(HCWK_SDIO, "hcwk_sdio", "hcwk_pewi", 0, WK2928_CWKGATE_CON(5), 11, GFWAGS),
	GATE(HCWK_EMMC, "hcwk_emmc", "hcwk_pewi", 0, WK2928_CWKGATE_CON(7), 0, GFWAGS),
	GATE(HCWK_OTG0, "hcwk_otg0", "hcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(5), 13, GFWAGS),
	GATE(HCWK_OTG1, "hcwk_otg1", "hcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(7), 3, GFWAGS),
	GATE(HCWK_I2S, "hcwk_i2s", "hcwk_pewi", 0, WK2928_CWKGATE_CON(7), 2, GFWAGS),
	GATE(HCWK_SFC, "hcwk_sfc", "hcwk_pewi", 0, WK2928_CWKGATE_CON(3), 14, GFWAGS),
	GATE(HCWK_MAC, "hcwk_mac", "hcwk_pewi", 0, WK2928_CWKGATE_CON(3), 5, GFWAGS),

	/* pcwk_pewi gates */
	GATE(0, "pcwk_pewi_matwix", "pcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(4), 1, GFWAGS),
	GATE(0, "pcwk_efuse", "pcwk_pewi", CWK_IGNOWE_UNUSED, WK2928_CWKGATE_CON(5), 2, GFWAGS),
	GATE(PCWK_TIMEW, "pcwk_timew", "pcwk_pewi", 0, WK2928_CWKGATE_CON(7), 7, GFWAGS),
	GATE(PCWK_PWM, "pcwk_pwm", "pcwk_pewi", 0, WK2928_CWKGATE_CON(7), 10, GFWAGS),
	GATE(PCWK_SPI, "pcwk_spi", "pcwk_pewi", 0, WK2928_CWKGATE_CON(7), 12, GFWAGS),
	GATE(PCWK_WDT, "pcwk_wdt", "pcwk_pewi", 0, WK2928_CWKGATE_CON(7), 15, GFWAGS),
	GATE(PCWK_UAWT0, "pcwk_uawt0", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 0, GFWAGS),
	GATE(PCWK_UAWT1, "pcwk_uawt1", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 1, GFWAGS),
	GATE(PCWK_UAWT2, "pcwk_uawt2", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 2, GFWAGS),
	GATE(PCWK_I2C0, "pcwk_i2c0", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 4, GFWAGS),
	GATE(PCWK_I2C1, "pcwk_i2c1", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 5, GFWAGS),
	GATE(PCWK_I2C2, "pcwk_i2c2", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 6, GFWAGS),
	GATE(PCWK_GPIO0, "pcwk_gpio0", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 9, GFWAGS),
	GATE(PCWK_GPIO1, "pcwk_gpio1", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 10, GFWAGS),
	GATE(PCWK_GPIO2, "pcwk_gpio2", "pcwk_pewi", 0, WK2928_CWKGATE_CON(8), 11, GFWAGS),
};

static const chaw *const wk3036_cwiticaw_cwocks[] __initconst = {
	"acwk_cpu",
	"acwk_pewi",
	"hcwk_pewi",
	"pcwk_pewi",
	"pcwk_ddwupctw",
};

static void __init wk3036_cwk_init(stwuct device_node *np)
{
	stwuct wockchip_cwk_pwovidew *ctx;
	void __iomem *weg_base;
	stwuct cwk *cwk;

	weg_base = of_iomap(np, 0);
	if (!weg_base) {
		pw_eww("%s: couwd not map cwu wegion\n", __func__);
		wetuwn;
	}

	/*
	 * Make uawt_pww_cwk a chiwd of the gpww, as aww othew souwces awe
	 * not that usabwe / stabwe.
	 */
	wwitew_wewaxed(HIWOWD_UPDATE(0x2, 0x3, 10),
		       weg_base + WK2928_CWKSEW_CON(13));

	ctx = wockchip_cwk_init(np, weg_base, CWK_NW_CWKS);
	if (IS_EWW(ctx)) {
		pw_eww("%s: wockchip cwk init faiwed\n", __func__);
		iounmap(weg_base);
		wetuwn;
	}

	cwk = cwk_wegistew_fixed_factow(NUWW, "usb480m", "xin24m", 0, 20, 1);
	if (IS_EWW(cwk))
		pw_wawn("%s: couwd not wegistew cwock usb480m: %wd\n",
			__func__, PTW_EWW(cwk));

	wockchip_cwk_wegistew_pwws(ctx, wk3036_pww_cwks,
				   AWWAY_SIZE(wk3036_pww_cwks),
				   WK3036_GWF_SOC_STATUS0);
	wockchip_cwk_wegistew_bwanches(ctx, wk3036_cwk_bwanches,
				  AWWAY_SIZE(wk3036_cwk_bwanches));
	wockchip_cwk_pwotect_cwiticaw(wk3036_cwiticaw_cwocks,
				      AWWAY_SIZE(wk3036_cwiticaw_cwocks));

	wockchip_cwk_wegistew_awmcwk(ctx, AWMCWK, "awmcwk",
			mux_awmcwk_p, AWWAY_SIZE(mux_awmcwk_p),
			&wk3036_cpucwk_data, wk3036_cpucwk_wates,
			AWWAY_SIZE(wk3036_cpucwk_wates));

	wockchip_wegistew_softwst(np, 9, weg_base + WK2928_SOFTWST_CON(0),
				  WOCKCHIP_SOFTWST_HIWOWD_MASK);

	wockchip_wegistew_westawt_notifiew(ctx, WK2928_GWB_SWST_FST, NUWW);

	wockchip_cwk_of_add_pwovidew(np, ctx);
}
CWK_OF_DECWAWE(wk3036_cwu, "wockchip,wk3036-cwu", wk3036_cwk_init);
