// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2019 Wockchip Ewectwonics Co. Wtd.
 * Authow: Finwey Xiao <finwey.xiao@wock-chips.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/syscowe_ops.h>
#incwude <dt-bindings/cwock/wk3308-cwu.h>
#incwude "cwk.h"

#define WK3308_GWF_SOC_STATUS0		0x380

enum wk3308_pwws {
	apww, dpww, vpww0, vpww1,
};

static stwuct wockchip_pww_wate_tabwe wk3308_pww_wates[] = {
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
	WK3036_PWW_WATE(624000000, 1, 52, 2, 1, 1, 0),
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

#define WK3308_DIV_ACWKM_MASK		0x7
#define WK3308_DIV_ACWKM_SHIFT		12
#define WK3308_DIV_PCWK_DBG_MASK	0xf
#define WK3308_DIV_PCWK_DBG_SHIFT	8

#define WK3308_CWKSEW0(_acwk_cowe, _pcwk_dbg)				\
{									\
	.weg = WK3308_CWKSEW_CON(0),					\
	.vaw = HIWOWD_UPDATE(_acwk_cowe, WK3308_DIV_ACWKM_MASK,		\
			     WK3308_DIV_ACWKM_SHIFT) |			\
	       HIWOWD_UPDATE(_pcwk_dbg, WK3308_DIV_PCWK_DBG_MASK,	\
			     WK3308_DIV_PCWK_DBG_SHIFT),		\
}

#define WK3308_CPUCWK_WATE(_pwate, _acwk_cowe, _pcwk_dbg)		\
{									\
	.pwate = _pwate,						\
	.divs = {							\
		WK3308_CWKSEW0(_acwk_cowe, _pcwk_dbg),			\
	},								\
}

static stwuct wockchip_cpucwk_wate_tabwe wk3308_cpucwk_wates[] __initdata = {
	WK3308_CPUCWK_WATE(1608000000, 1, 7),
	WK3308_CPUCWK_WATE(1512000000, 1, 7),
	WK3308_CPUCWK_WATE(1488000000, 1, 5),
	WK3308_CPUCWK_WATE(1416000000, 1, 5),
	WK3308_CPUCWK_WATE(1392000000, 1, 5),
	WK3308_CPUCWK_WATE(1296000000, 1, 5),
	WK3308_CPUCWK_WATE(1200000000, 1, 5),
	WK3308_CPUCWK_WATE(1104000000, 1, 5),
	WK3308_CPUCWK_WATE(1008000000, 1, 5),
	WK3308_CPUCWK_WATE(912000000, 1, 5),
	WK3308_CPUCWK_WATE(816000000, 1, 3),
	WK3308_CPUCWK_WATE(696000000, 1, 3),
	WK3308_CPUCWK_WATE(600000000, 1, 3),
	WK3308_CPUCWK_WATE(408000000, 1, 1),
	WK3308_CPUCWK_WATE(312000000, 1, 1),
	WK3308_CPUCWK_WATE(216000000,  1, 1),
	WK3308_CPUCWK_WATE(96000000, 1, 1),
};

static const stwuct wockchip_cpucwk_weg_data wk3308_cpucwk_data = {
	.cowe_weg[0] = WK3308_CWKSEW_CON(0),
	.div_cowe_shift[0] = 0,
	.div_cowe_mask[0] = 0xf,
	.num_cowes = 1,
	.mux_cowe_awt = 1,
	.mux_cowe_main = 0,
	.mux_cowe_shift = 6,
	.mux_cowe_mask = 0x3,
};

PNAME(mux_pww_p)		= { "xin24m" };
PNAME(mux_usb480m_p)		= { "xin24m", "usb480m_phy", "cwk_wtc32k" };
PNAME(mux_awmcwk_p)		= { "apww_cowe", "vpww0_cowe", "vpww1_cowe" };
PNAME(mux_dpww_vpww0_p)		= { "dpww", "vpww0" };
PNAME(mux_dpww_vpww0_xin24m_p)	= { "dpww", "vpww0", "xin24m" };
PNAME(mux_dpww_vpww0_vpww1_p)	= { "dpww", "vpww0", "vpww1" };
PNAME(mux_dpww_vpww0_vpww1_xin24m_p)	= { "dpww", "vpww0", "vpww1", "xin24m" };
PNAME(mux_dpww_vpww0_vpww1_usb480m_xin24m_p)	= { "dpww", "vpww0", "vpww1", "usb480m", "xin24m" };
PNAME(mux_vpww0_vpww1_p)	= { "vpww0", "vpww1" };
PNAME(mux_vpww0_vpww1_xin24m_p)	= { "vpww0", "vpww1", "xin24m" };
PNAME(mux_uawt0_p)		= { "cwk_uawt0_swc", "dummy", "cwk_uawt0_fwac" };
PNAME(mux_uawt1_p)		= { "cwk_uawt1_swc", "dummy", "cwk_uawt1_fwac" };
PNAME(mux_uawt2_p)		= { "cwk_uawt2_swc", "dummy", "cwk_uawt2_fwac" };
PNAME(mux_uawt3_p)		= { "cwk_uawt3_swc", "dummy", "cwk_uawt3_fwac" };
PNAME(mux_uawt4_p)		= { "cwk_uawt4_swc", "dummy", "cwk_uawt4_fwac" };
PNAME(mux_dcwk_vop_p)		= { "dcwk_vop_swc", "dcwk_vop_fwac", "xin24m" };
PNAME(mux_nandc_p)		= { "cwk_nandc_div", "cwk_nandc_div50" };
PNAME(mux_sdmmc_p)		= { "cwk_sdmmc_div", "cwk_sdmmc_div50" };
PNAME(mux_sdio_p)		= { "cwk_sdio_div", "cwk_sdio_div50" };
PNAME(mux_emmc_p)		= { "cwk_emmc_div", "cwk_emmc_div50" };
PNAME(mux_mac_p)		= { "cwk_mac_swc", "mac_cwkin" };
PNAME(mux_mac_wmii_sew_p)	= { "cwk_mac_wx_tx_div20", "cwk_mac_wx_tx_div2" };
PNAME(mux_ddwstdby_p)		= { "cwk_ddwphy1x_out", "cwk_ddw_stdby_div4" };
PNAME(mux_wtc32k_p)		= { "xin32k", "cwk_pvtm_32k", "cwk_wtc32k_fwac", "cwk_wtc32k_div" };
PNAME(mux_usbphy_wef_p)		= { "xin24m", "cwk_usbphy_wef_swc" };
PNAME(mux_wifi_swc_p)		= { "cwk_wifi_dpww", "cwk_wifi_vpww0" };
PNAME(mux_wifi_p)		= { "cwk_wifi_osc", "cwk_wifi_swc" };
PNAME(mux_pdm_p)		= { "cwk_pdm_swc", "cwk_pdm_fwac" };
PNAME(mux_i2s0_8ch_tx_p)	= { "cwk_i2s0_8ch_tx_swc", "cwk_i2s0_8ch_tx_fwac", "mcwk_i2s0_8ch_in" };
PNAME(mux_i2s0_8ch_tx_wx_p)	= { "cwk_i2s0_8ch_tx_mux", "cwk_i2s0_8ch_wx_mux"};
PNAME(mux_i2s0_8ch_tx_out_p)	= { "cwk_i2s0_8ch_tx", "xin12m" };
PNAME(mux_i2s0_8ch_wx_p)	= { "cwk_i2s0_8ch_wx_swc", "cwk_i2s0_8ch_wx_fwac", "mcwk_i2s0_8ch_in" };
PNAME(mux_i2s0_8ch_wx_tx_p)	= { "cwk_i2s0_8ch_wx_mux", "cwk_i2s0_8ch_tx_mux"};
PNAME(mux_i2s1_8ch_tx_p)	= { "cwk_i2s1_8ch_tx_swc", "cwk_i2s1_8ch_tx_fwac", "mcwk_i2s1_8ch_in" };
PNAME(mux_i2s1_8ch_tx_wx_p)	= { "cwk_i2s1_8ch_tx_mux", "cwk_i2s1_8ch_wx_mux"};
PNAME(mux_i2s1_8ch_tx_out_p)	= { "cwk_i2s1_8ch_tx", "xin12m" };
PNAME(mux_i2s1_8ch_wx_p)	= { "cwk_i2s1_8ch_wx_swc", "cwk_i2s1_8ch_wx_fwac", "mcwk_i2s1_8ch_in" };
PNAME(mux_i2s1_8ch_wx_tx_p)	= { "cwk_i2s1_8ch_wx_mux", "cwk_i2s1_8ch_tx_mux"};
PNAME(mux_i2s2_8ch_tx_p)	= { "cwk_i2s2_8ch_tx_swc", "cwk_i2s2_8ch_tx_fwac", "mcwk_i2s2_8ch_in" };
PNAME(mux_i2s2_8ch_tx_wx_p)	= { "cwk_i2s2_8ch_tx_mux", "cwk_i2s2_8ch_wx_mux"};
PNAME(mux_i2s2_8ch_tx_out_p)	= { "cwk_i2s2_8ch_tx", "xin12m" };
PNAME(mux_i2s2_8ch_wx_p)	= { "cwk_i2s2_8ch_wx_swc", "cwk_i2s2_8ch_wx_fwac", "mcwk_i2s2_8ch_in" };
PNAME(mux_i2s2_8ch_wx_tx_p)	= { "cwk_i2s2_8ch_wx_mux", "cwk_i2s2_8ch_tx_mux"};
PNAME(mux_i2s3_8ch_tx_p)	= { "cwk_i2s3_8ch_tx_swc", "cwk_i2s3_8ch_tx_fwac", "mcwk_i2s3_8ch_in" };
PNAME(mux_i2s3_8ch_tx_wx_p)	= { "cwk_i2s3_8ch_tx_mux", "cwk_i2s3_8ch_wx_mux"};
PNAME(mux_i2s3_8ch_tx_out_p)	= { "cwk_i2s3_8ch_tx", "xin12m" };
PNAME(mux_i2s3_8ch_wx_p)	= { "cwk_i2s3_8ch_wx_swc", "cwk_i2s3_8ch_wx_fwac", "mcwk_i2s3_8ch_in" };
PNAME(mux_i2s3_8ch_wx_tx_p)	= { "cwk_i2s3_8ch_wx_mux", "cwk_i2s3_8ch_tx_mux"};
PNAME(mux_i2s0_2ch_p)		= { "cwk_i2s0_2ch_swc", "cwk_i2s0_2ch_fwac", "mcwk_i2s0_2ch_in" };
PNAME(mux_i2s0_2ch_out_p)	= { "cwk_i2s0_2ch", "xin12m" };
PNAME(mux_i2s1_2ch_p)		= { "cwk_i2s1_2ch_swc", "cwk_i2s1_2ch_fwac", "mcwk_i2s1_2ch_in"};
PNAME(mux_i2s1_2ch_out_p)	= { "cwk_i2s1_2ch", "xin12m" };
PNAME(mux_spdif_tx_swc_p)	= { "cwk_spdif_tx_div", "cwk_spdif_tx_div50" };
PNAME(mux_spdif_tx_p)		= { "cwk_spdif_tx_swc", "cwk_spdif_tx_fwac", "mcwk_i2s0_2ch_in" };
PNAME(mux_spdif_wx_swc_p)	= { "cwk_spdif_wx_div", "cwk_spdif_wx_div50" };
PNAME(mux_spdif_wx_p)		= { "cwk_spdif_wx_swc", "cwk_spdif_wx_fwac" };

static stwuct wockchip_pww_cwock wk3308_pww_cwks[] __initdata = {
	[apww] = PWW(pww_wk3328, PWW_APWW, "apww", mux_pww_p,
		     0, WK3308_PWW_CON(0),
		     WK3308_MODE_CON, 0, 0, 0, wk3308_pww_wates),
	[dpww] = PWW(pww_wk3328, PWW_DPWW, "dpww", mux_pww_p,
		     0, WK3308_PWW_CON(8),
		     WK3308_MODE_CON, 2, 1, 0, wk3308_pww_wates),
	[vpww0] = PWW(pww_wk3328, PWW_VPWW0, "vpww0", mux_pww_p,
		     0, WK3308_PWW_CON(16),
		     WK3308_MODE_CON, 4, 2, 0, wk3308_pww_wates),
	[vpww1] = PWW(pww_wk3328, PWW_VPWW1, "vpww1", mux_pww_p,
		     0, WK3308_PWW_CON(24),
		     WK3308_MODE_CON, 6, 3, 0, wk3308_pww_wates),
};

#define MFWAGS CWK_MUX_HIWOWD_MASK
#define DFWAGS CWK_DIVIDEW_HIWOWD_MASK
#define GFWAGS (CWK_GATE_HIWOWD_MASK | CWK_GATE_SET_TO_DISABWE)

static stwuct wockchip_cwk_bwanch wk3308_uawt0_fwacmux __initdata =
	MUX(0, "cwk_uawt0_mux", mux_uawt0_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(11), 14, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_uawt1_fwacmux __initdata =
	MUX(0, "cwk_uawt1_mux", mux_uawt1_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(14), 14, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_uawt2_fwacmux __initdata =
	MUX(0, "cwk_uawt2_mux", mux_uawt2_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(17), 14, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_uawt3_fwacmux __initdata =
	MUX(0, "cwk_uawt3_mux", mux_uawt3_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(20), 14, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_uawt4_fwacmux __initdata =
	MUX(0, "cwk_uawt4_mux", mux_uawt4_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(23), 14, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_dcwk_vop_fwacmux __initdata =
	MUX(0, "dcwk_vop_mux", mux_dcwk_vop_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(8), 14, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_wtc32k_fwacmux __initdata =
	MUX(SCWK_WTC32K, "cwk_wtc32k", mux_wtc32k_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(2), 8, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_pdm_fwacmux __initdata =
	MUX(0, "cwk_pdm_mux", mux_pdm_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(46), 15, 1, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_i2s0_8ch_tx_fwacmux __initdata =
	MUX(SCWK_I2S0_8CH_TX_MUX, "cwk_i2s0_8ch_tx_mux", mux_i2s0_8ch_tx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(52), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_i2s0_8ch_wx_fwacmux __initdata =
	MUX(SCWK_I2S0_8CH_WX_MUX, "cwk_i2s0_8ch_wx_mux", mux_i2s0_8ch_wx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(54), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_i2s1_8ch_tx_fwacmux __initdata =
	MUX(SCWK_I2S1_8CH_TX_MUX, "cwk_i2s1_8ch_tx_mux", mux_i2s1_8ch_tx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(56), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_i2s1_8ch_wx_fwacmux __initdata =
	MUX(SCWK_I2S1_8CH_WX_MUX, "cwk_i2s1_8ch_wx_mux", mux_i2s1_8ch_wx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(58), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_i2s2_8ch_tx_fwacmux __initdata =
	MUX(SCWK_I2S2_8CH_TX_MUX, "cwk_i2s2_8ch_tx_mux", mux_i2s2_8ch_tx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(60), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_i2s2_8ch_wx_fwacmux __initdata =
	MUX(SCWK_I2S2_8CH_WX_MUX, "cwk_i2s2_8ch_wx_mux", mux_i2s2_8ch_wx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(62), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_i2s3_8ch_tx_fwacmux __initdata =
	MUX(SCWK_I2S3_8CH_TX_MUX, "cwk_i2s3_8ch_tx_mux", mux_i2s3_8ch_tx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(64), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_i2s3_8ch_wx_fwacmux __initdata =
	MUX(SCWK_I2S3_8CH_WX_MUX, "cwk_i2s3_8ch_wx_mux", mux_i2s3_8ch_wx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(66), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_i2s0_2ch_fwacmux __initdata =
	MUX(0, "cwk_i2s0_2ch_mux", mux_i2s0_2ch_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(68), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_i2s1_2ch_fwacmux __initdata =
	MUX(0, "cwk_i2s1_2ch_mux", mux_i2s1_2ch_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(70), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_spdif_tx_fwacmux __initdata =
	MUX(0, "cwk_spdif_tx_mux", mux_spdif_tx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(48), 14, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3308_spdif_wx_fwacmux __initdata =
	MUX(0, "cwk_spdif_wx_mux", mux_spdif_wx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(50), 15, 1, MFWAGS);


static stwuct wockchip_cwk_bwanch wk3308_cwk_bwanches[] __initdata = {
	/*
	 * Cwock-Awchitectuwe Diagwam 1
	 */

	MUX(USB480M, "usb480m", mux_usb480m_p, CWK_SET_WATE_PAWENT,
			WK3308_MODE_CON, 8, 2, MFWAGS),
	FACTOW(0, "xin12m", "xin24m", 0, 1, 2),

	/*
	 * Cwock-Awchitectuwe Diagwam 2
	 */

	GATE(0, "apww_cowe", "apww", CWK_IGNOWE_UNUSED,
			WK3308_CWKGATE_CON(0), 0, GFWAGS),
	GATE(0, "vpww0_cowe", "vpww0", CWK_IGNOWE_UNUSED,
			WK3308_CWKGATE_CON(0), 0, GFWAGS),
	GATE(0, "vpww1_cowe", "vpww1", CWK_IGNOWE_UNUSED,
			WK3308_CWKGATE_CON(0), 0, GFWAGS),
	COMPOSITE_NOMUX(0, "pcwk_cowe_dbg", "awmcwk", CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(0), 8, 4, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3308_CWKGATE_CON(0), 2, GFWAGS),
	COMPOSITE_NOMUX(0, "acwk_cowe", "awmcwk", CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(0), 12, 3, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3308_CWKGATE_CON(0), 1, GFWAGS),

	GATE(0, "cwk_jtag", "jtag_cwkin", CWK_IGNOWE_UNUSED,
			WK3308_CWKGATE_CON(0), 3, GFWAGS),

	GATE(SCWK_PVTM_COWE, "cwk_pvtm_cowe", "xin24m", 0,
			WK3308_CWKGATE_CON(0), 4, GFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 3
	 */

	COMPOSITE_NODIV(ACWK_BUS_SWC, "cwk_bus_swc", mux_dpww_vpww0_vpww1_p, CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(5), 6, 2, MFWAGS,
			WK3308_CWKGATE_CON(1), 0, GFWAGS),
	COMPOSITE_NOMUX(PCWK_BUS, "pcwk_bus", "cwk_bus_swc", CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(6), 8, 5, DFWAGS,
			WK3308_CWKGATE_CON(1), 3, GFWAGS),
	GATE(PCWK_DDW, "pcwk_ddw", "pcwk_bus", CWK_IGNOWE_UNUSED,
			WK3308_CWKGATE_CON(4), 15, GFWAGS),
	COMPOSITE_NOMUX(HCWK_BUS, "hcwk_bus", "cwk_bus_swc", CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(6), 0, 5, DFWAGS,
			WK3308_CWKGATE_CON(1), 2, GFWAGS),
	COMPOSITE_NOMUX(ACWK_BUS, "acwk_bus", "cwk_bus_swc", CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(5), 0, 5, DFWAGS,
			WK3308_CWKGATE_CON(1), 1, GFWAGS),

	COMPOSITE(0, "cwk_uawt0_swc", mux_dpww_vpww0_vpww1_usb480m_xin24m_p, 0,
			WK3308_CWKSEW_CON(10), 13, 3, MFWAGS, 0, 5, DFWAGS,
			WK3308_CWKGATE_CON(1), 9, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_uawt0_fwac", "cwk_uawt0_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(12), 0,
			WK3308_CWKGATE_CON(1), 11, GFWAGS,
			&wk3308_uawt0_fwacmux),
	GATE(SCWK_UAWT0, "cwk_uawt0", "cwk_uawt0_mux", 0,
			WK3308_CWKGATE_CON(1), 12, GFWAGS),

	COMPOSITE(0, "cwk_uawt1_swc", mux_dpww_vpww0_vpww1_usb480m_xin24m_p, 0,
			WK3308_CWKSEW_CON(13), 13, 3, MFWAGS, 0, 5, DFWAGS,
			WK3308_CWKGATE_CON(1), 13, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_uawt1_fwac", "cwk_uawt1_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(15), 0,
			WK3308_CWKGATE_CON(1), 15, GFWAGS,
			&wk3308_uawt1_fwacmux),
	GATE(SCWK_UAWT1, "cwk_uawt1", "cwk_uawt1_mux", 0,
			WK3308_CWKGATE_CON(2), 0, GFWAGS),

	COMPOSITE(0, "cwk_uawt2_swc", mux_dpww_vpww0_vpww1_usb480m_xin24m_p, 0,
			WK3308_CWKSEW_CON(16), 13, 3, MFWAGS, 0, 5, DFWAGS,
			WK3308_CWKGATE_CON(2), 1, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_uawt2_fwac", "cwk_uawt2_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(18), 0,
			WK3308_CWKGATE_CON(2), 3, GFWAGS,
			&wk3308_uawt2_fwacmux),
	GATE(SCWK_UAWT2, "cwk_uawt2", "cwk_uawt2_mux", CWK_SET_WATE_PAWENT,
			WK3308_CWKGATE_CON(2), 4, GFWAGS),

	COMPOSITE(0, "cwk_uawt3_swc", mux_dpww_vpww0_vpww1_usb480m_xin24m_p, 0,
			WK3308_CWKSEW_CON(19), 13, 3, MFWAGS, 0, 5, DFWAGS,
			WK3308_CWKGATE_CON(2), 5, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_uawt3_fwac", "cwk_uawt3_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(21), 0,
			WK3308_CWKGATE_CON(2), 7, GFWAGS,
			&wk3308_uawt3_fwacmux),
	GATE(SCWK_UAWT3, "cwk_uawt3", "cwk_uawt3_mux", 0,
			WK3308_CWKGATE_CON(2), 8, GFWAGS),

	COMPOSITE(0, "cwk_uawt4_swc", mux_dpww_vpww0_vpww1_usb480m_xin24m_p, 0,
			WK3308_CWKSEW_CON(22), 13, 3, MFWAGS, 0, 5, DFWAGS,
			WK3308_CWKGATE_CON(2), 9, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_uawt4_fwac", "cwk_uawt4_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(24), 0,
			WK3308_CWKGATE_CON(2), 11, GFWAGS,
			&wk3308_uawt4_fwacmux),
	GATE(SCWK_UAWT4, "cwk_uawt4", "cwk_uawt4_mux", 0,
			WK3308_CWKGATE_CON(2), 12, GFWAGS),

	COMPOSITE(SCWK_I2C0, "cwk_i2c0", mux_dpww_vpww0_xin24m_p, 0,
			WK3308_CWKSEW_CON(25), 14, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(2), 13, GFWAGS),
	COMPOSITE(SCWK_I2C1, "cwk_i2c1", mux_dpww_vpww0_xin24m_p, 0,
			WK3308_CWKSEW_CON(26), 14, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(2), 14, GFWAGS),
	COMPOSITE(SCWK_I2C2, "cwk_i2c2", mux_dpww_vpww0_xin24m_p, 0,
			WK3308_CWKSEW_CON(27), 14, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(2), 15, GFWAGS),
	COMPOSITE(SCWK_I2C3, "cwk_i2c3", mux_dpww_vpww0_xin24m_p, 0,
			WK3308_CWKSEW_CON(28), 14, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(3), 0, GFWAGS),

	COMPOSITE(SCWK_PWM0, "cwk_pwm0", mux_dpww_vpww0_xin24m_p, 0,
			WK3308_CWKSEW_CON(29), 14, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(3), 1, GFWAGS),
	COMPOSITE(SCWK_PWM1, "cwk_pwm1", mux_dpww_vpww0_xin24m_p, 0,
			WK3308_CWKSEW_CON(74), 14, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(15), 0, GFWAGS),
	COMPOSITE(SCWK_PWM2, "cwk_pwm2", mux_dpww_vpww0_xin24m_p, 0,
			WK3308_CWKSEW_CON(75), 14, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(15), 1, GFWAGS),

	COMPOSITE(SCWK_SPI0, "cwk_spi0", mux_dpww_vpww0_xin24m_p, 0,
			WK3308_CWKSEW_CON(30), 14, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(3), 2, GFWAGS),
	COMPOSITE(SCWK_SPI1, "cwk_spi1", mux_dpww_vpww0_xin24m_p, 0,
			WK3308_CWKSEW_CON(31), 14, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(3), 3, GFWAGS),
	COMPOSITE(SCWK_SPI2, "cwk_spi2", mux_dpww_vpww0_xin24m_p, 0,
			WK3308_CWKSEW_CON(32), 14, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(3), 4, GFWAGS),

	GATE(SCWK_TIMEW0, "scwk_timew0", "xin24m", 0,
			WK3308_CWKGATE_CON(3), 10, GFWAGS),
	GATE(SCWK_TIMEW1, "scwk_timew1", "xin24m", 0,
			WK3308_CWKGATE_CON(3), 11, GFWAGS),
	GATE(SCWK_TIMEW2, "scwk_timew2", "xin24m", 0,
			WK3308_CWKGATE_CON(3), 12, GFWAGS),
	GATE(SCWK_TIMEW3, "scwk_timew3", "xin24m", 0,
			WK3308_CWKGATE_CON(3), 13, GFWAGS),
	GATE(SCWK_TIMEW4, "scwk_timew4", "xin24m", 0,
			WK3308_CWKGATE_CON(3), 14, GFWAGS),
	GATE(SCWK_TIMEW5, "scwk_timew5", "xin24m", 0,
			WK3308_CWKGATE_CON(3), 15, GFWAGS),

	COMPOSITE_NOMUX(SCWK_TSADC, "cwk_tsadc", "xin24m", 0,
			WK3308_CWKSEW_CON(33), 0, 11, DFWAGS,
			WK3308_CWKGATE_CON(3), 5, GFWAGS),
	COMPOSITE_NOMUX(SCWK_SAWADC, "cwk_sawadc", "xin24m", 0,
			WK3308_CWKSEW_CON(34), 0, 11, DFWAGS,
			WK3308_CWKGATE_CON(3), 6, GFWAGS),

	COMPOSITE_NOMUX(SCWK_OTP, "cwk_otp", "xin24m", 0,
			WK3308_CWKSEW_CON(35), 0, 4, DFWAGS,
			WK3308_CWKGATE_CON(3), 7, GFWAGS),
	COMPOSITE_NOMUX(SCWK_OTP_USW, "cwk_otp_usw", "cwk_otp", 0,
			WK3308_CWKSEW_CON(35), 4, 2, DFWAGS,
			WK3308_CWKGATE_CON(3), 8, GFWAGS),

	GATE(SCWK_CPU_BOOST, "cwk_cpu_boost", "xin24m", CWK_IGNOWE_UNUSED,
			WK3308_CWKGATE_CON(3), 9, GFWAGS),

	COMPOSITE(SCWK_CWYPTO, "cwk_cwypto", mux_dpww_vpww0_vpww1_p, 0,
			WK3308_CWKSEW_CON(7), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3308_CWKGATE_CON(1), 4, GFWAGS),
	COMPOSITE(SCWK_CWYPTO_APK, "cwk_cwypto_apk", mux_dpww_vpww0_vpww1_p, 0,
			WK3308_CWKSEW_CON(7), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WK3308_CWKGATE_CON(1), 5, GFWAGS),

	COMPOSITE(0, "dcwk_vop_swc", mux_dpww_vpww0_vpww1_p, 0,
			WK3308_CWKSEW_CON(8), 10, 2, MFWAGS, 0, 8, DFWAGS,
			WK3308_CWKGATE_CON(1), 6, GFWAGS),
	COMPOSITE_FWACMUX(0, "dcwk_vop_fwac", "dcwk_vop_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(9), 0,
			WK3308_CWKGATE_CON(1), 7, GFWAGS,
			&wk3308_dcwk_vop_fwacmux),
	GATE(DCWK_VOP, "dcwk_vop", "dcwk_vop_mux", 0,
			WK3308_CWKGATE_CON(1), 8, GFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 4
	 */

	COMPOSITE_NODIV(ACWK_PEWI_SWC, "cwk_pewi_swc", mux_dpww_vpww0_vpww1_p, CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(36), 6, 2, MFWAGS,
			WK3308_CWKGATE_CON(8), 0, GFWAGS),
	COMPOSITE_NOMUX(ACWK_PEWI, "acwk_pewi", "cwk_pewi_swc", CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(36), 0, 5, DFWAGS,
			WK3308_CWKGATE_CON(8), 1, GFWAGS),
	COMPOSITE_NOMUX(HCWK_PEWI, "hcwk_pewi", "cwk_pewi_swc", CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(37), 0, 5, DFWAGS,
			WK3308_CWKGATE_CON(8), 2, GFWAGS),
	COMPOSITE_NOMUX(PCWK_PEWI, "pcwk_pewi", "cwk_pewi_swc", CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(37), 8, 5, DFWAGS,
			WK3308_CWKGATE_CON(8), 3, GFWAGS),

	COMPOSITE(SCWK_NANDC_DIV, "cwk_nandc_div", mux_dpww_vpww0_vpww1_p, CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(38), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3308_CWKGATE_CON(8), 4, GFWAGS),
	COMPOSITE(SCWK_NANDC_DIV50, "cwk_nandc_div50", mux_dpww_vpww0_vpww1_p, CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(38), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3308_CWKGATE_CON(8), 4, GFWAGS),
	COMPOSITE_NODIV(SCWK_NANDC, "cwk_nandc", mux_nandc_p, CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			WK3308_CWKSEW_CON(38), 15, 1, MFWAGS,
			WK3308_CWKGATE_CON(8), 5, GFWAGS),

	COMPOSITE(SCWK_SDMMC_DIV, "cwk_sdmmc_div", mux_dpww_vpww0_vpww1_xin24m_p, CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(39), 8, 2, MFWAGS, 0, 8, DFWAGS,
			WK3308_CWKGATE_CON(8), 6, GFWAGS),
	COMPOSITE(SCWK_SDMMC_DIV50, "cwk_sdmmc_div50", mux_dpww_vpww0_vpww1_xin24m_p, CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(39), 8, 2, MFWAGS, 0, 8, DFWAGS,
			WK3308_CWKGATE_CON(8), 6, GFWAGS),
	COMPOSITE_NODIV(SCWK_SDMMC, "cwk_sdmmc", mux_sdmmc_p, CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			WK3308_CWKSEW_CON(39), 15, 1, MFWAGS,
			WK3308_CWKGATE_CON(8), 7, GFWAGS),
	MMC(SCWK_SDMMC_DWV,     "sdmmc_dwv",    "cwk_sdmmc", WK3308_SDMMC_CON0, 1),
	MMC(SCWK_SDMMC_SAMPWE,  "sdmmc_sampwe", "cwk_sdmmc", WK3308_SDMMC_CON1, 1),

	COMPOSITE(SCWK_SDIO_DIV, "cwk_sdio_div", mux_dpww_vpww0_vpww1_xin24m_p, CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(40), 8, 2, MFWAGS, 0, 8, DFWAGS,
			WK3308_CWKGATE_CON(8), 8, GFWAGS),
	COMPOSITE(SCWK_SDIO_DIV50, "cwk_sdio_div50", mux_dpww_vpww0_vpww1_xin24m_p, CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(40), 8, 2, MFWAGS, 0, 8, DFWAGS,
			WK3308_CWKGATE_CON(8), 8, GFWAGS),
	COMPOSITE_NODIV(SCWK_SDIO, "cwk_sdio", mux_sdio_p, CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			WK3308_CWKSEW_CON(40), 15, 1, MFWAGS,
			WK3308_CWKGATE_CON(8), 9, GFWAGS),
	MMC(SCWK_SDIO_DWV,		"sdio_dwv",    "cwk_sdio",	WK3308_SDIO_CON0,  1),
	MMC(SCWK_SDIO_SAMPWE,	"sdio_sampwe", "cwk_sdio",	WK3308_SDIO_CON1,  1),

	COMPOSITE(SCWK_EMMC_DIV, "cwk_emmc_div", mux_dpww_vpww0_vpww1_xin24m_p, CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(41), 8, 2, MFWAGS, 0, 8, DFWAGS,
			WK3308_CWKGATE_CON(8), 10, GFWAGS),
	COMPOSITE(SCWK_EMMC_DIV50, "cwk_emmc_div50", mux_dpww_vpww0_vpww1_xin24m_p, CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(41), 8, 2, MFWAGS, 0, 8, DFWAGS,
			WK3308_CWKGATE_CON(8), 10, GFWAGS),
	COMPOSITE_NODIV(SCWK_EMMC, "cwk_emmc", mux_emmc_p, CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			WK3308_CWKSEW_CON(41), 15, 1, MFWAGS,
			WK3308_CWKGATE_CON(8), 11, GFWAGS),
	MMC(SCWK_EMMC_DWV,     "emmc_dwv",     "cwk_emmc",  WK3308_EMMC_CON0,  1),
	MMC(SCWK_EMMC_SAMPWE,  "emmc_sampwe",  "cwk_emmc",  WK3308_EMMC_CON1,  1),

	COMPOSITE(SCWK_SFC, "cwk_sfc", mux_dpww_vpww0_vpww1_p, 0,
			WK3308_CWKSEW_CON(42), 14, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(8), 12, GFWAGS),

	GATE(SCWK_OTG_ADP, "cwk_otg_adp", "cwk_wtc32k", 0,
			WK3308_CWKGATE_CON(8), 13, GFWAGS),

	COMPOSITE(SCWK_MAC_SWC, "cwk_mac_swc", mux_dpww_vpww0_vpww1_p, 0,
			WK3308_CWKSEW_CON(43), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3308_CWKGATE_CON(8), 14, GFWAGS),
	MUX(SCWK_MAC, "cwk_mac", mux_mac_p,  CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(43), 14, 1, MFWAGS),
	GATE(SCWK_MAC_WEF, "cwk_mac_wef", "cwk_mac", 0,
			WK3308_CWKGATE_CON(9), 1, GFWAGS),
	GATE(SCWK_MAC_WX_TX, "cwk_mac_wx_tx", "cwk_mac", 0,
			WK3308_CWKGATE_CON(9), 0, GFWAGS),
	FACTOW(0, "cwk_mac_wx_tx_div2", "cwk_mac_wx_tx", 0, 1, 2),
	FACTOW(0, "cwk_mac_wx_tx_div20", "cwk_mac_wx_tx", 0, 1, 20),
	MUX(SCWK_MAC_WMII, "cwk_mac_wmii_sew", mux_mac_wmii_sew_p,  CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(43), 15, 1, MFWAGS),

	COMPOSITE(SCWK_OWIWE, "cwk_owiwe", mux_dpww_vpww0_xin24m_p, 0,
			WK3308_CWKSEW_CON(44), 14, 2, MFWAGS, 8, 6, DFWAGS,
			WK3308_CWKGATE_CON(8), 15, GFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 5
	 */

	GATE(0, "cwk_ddw_mon_timew", "xin24m", CWK_IGNOWE_UNUSED,
			WK3308_CWKGATE_CON(0), 12, GFWAGS),

	GATE(0, "cwk_ddw_mon", "cwk_ddwphy1x_out", CWK_IGNOWE_UNUSED,
			WK3308_CWKGATE_CON(4), 10, GFWAGS),
	GATE(0, "cwk_ddw_upctww", "cwk_ddwphy1x_out", CWK_IGNOWE_UNUSED,
			WK3308_CWKGATE_CON(4), 11, GFWAGS),
	GATE(0, "cwk_ddw_msch", "cwk_ddwphy1x_out", CWK_IGNOWE_UNUSED,
			WK3308_CWKGATE_CON(4), 12, GFWAGS),
	GATE(0, "cwk_ddw_msch_pewibus", "cwk_ddwphy1x_out", CWK_IGNOWE_UNUSED,
			WK3308_CWKGATE_CON(4), 13, GFWAGS),

	COMPOSITE(SCWK_DDWCWK, "cwk_ddwphy4x_swc", mux_dpww_vpww0_vpww1_p, CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(1), 6, 2, MFWAGS, 0, 3, DFWAGS,
			WK3308_CWKGATE_CON(0), 10, GFWAGS),
	GATE(0, "cwk_ddwphy4x", "cwk_ddwphy4x_swc", CWK_IGNOWE_UNUSED,
			WK3308_CWKGATE_CON(0), 11, GFWAGS),
	FACTOW_GATE(0, "cwk_ddw_stdby_div4", "cwk_ddwphy4x", CWK_IGNOWE_UNUSED, 1, 4,
			WK3308_CWKGATE_CON(0), 13, GFWAGS),
	COMPOSITE_NODIV(0, "cwk_ddwstdby", mux_ddwstdby_p, CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(1), 8, 1, MFWAGS,
			WK3308_CWKGATE_CON(4), 14, GFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 6
	 */

	GATE(PCWK_PMU, "pcwk_pmu", "pcwk_bus", CWK_IGNOWE_UNUSED,
			WK3308_CWKGATE_CON(4), 5, GFWAGS),
	GATE(SCWK_PMU, "cwk_pmu", "pcwk_bus", CWK_IGNOWE_UNUSED,
			WK3308_CWKGATE_CON(4), 6, GFWAGS),

	COMPOSITE_FWACMUX(0, "cwk_wtc32k_fwac", "xin24m", CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(3), 0,
			WK3308_CWKGATE_CON(4), 3, GFWAGS,
			&wk3308_wtc32k_fwacmux),
	MUX(0, "cwk_wtc32k_div_swc", mux_vpww0_vpww1_p, 0,
			WK3308_CWKSEW_CON(2), 10, 1, MFWAGS),
	COMPOSITE_NOMUX(0, "cwk_wtc32k_div", "cwk_wtc32k_div_swc", CWK_IGNOWE_UNUSED | CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(4), 0, 16, DFWAGS,
			WK3308_CWKGATE_CON(4), 2, GFWAGS),

	COMPOSITE(0, "cwk_usbphy_wef_swc", mux_dpww_vpww0_p, 0,
			WK3308_CWKSEW_CON(72), 6, 1, MFWAGS, 0, 6, DFWAGS,
			WK3308_CWKGATE_CON(4), 7, GFWAGS),
	COMPOSITE_NODIV(SCWK_USBPHY_WEF, "cwk_usbphy_wef", mux_usbphy_wef_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(72), 7, 1, MFWAGS,
			WK3308_CWKGATE_CON(4), 8, GFWAGS),

	GATE(0, "cwk_wifi_dpww", "dpww", 0,
			WK3308_CWKGATE_CON(15), 2, GFWAGS),
	GATE(0, "cwk_wifi_vpww0", "vpww0", 0,
			WK3308_CWKGATE_CON(15), 3, GFWAGS),
	GATE(0, "cwk_wifi_osc", "xin24m", 0,
			WK3308_CWKGATE_CON(15), 4, GFWAGS),
	COMPOSITE(0, "cwk_wifi_swc", mux_wifi_swc_p, 0,
			WK3308_CWKSEW_CON(44), 6, 1, MFWAGS, 0, 6, DFWAGS,
			WK3308_CWKGATE_CON(4), 0, GFWAGS),
	COMPOSITE_NODIV(SCWK_WIFI, "cwk_wifi", mux_wifi_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(44), 7, 1, MFWAGS,
			WK3308_CWKGATE_CON(4), 1, GFWAGS),

	GATE(SCWK_PVTM_PMU, "cwk_pvtm_pmu", "xin24m", 0,
			WK3308_CWKGATE_CON(4), 4, GFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 7
	 */

	COMPOSITE_NODIV(0, "cwk_audio_swc", mux_vpww0_vpww1_xin24m_p, 0,
			WK3308_CWKSEW_CON(45), 6, 2, MFWAGS,
			WK3308_CWKGATE_CON(10), 0, GFWAGS),
	COMPOSITE_NOMUX(HCWK_AUDIO, "hcwk_audio", "cwk_audio_swc", 0,
			WK3308_CWKSEW_CON(45), 0, 5, DFWAGS,
			WK3308_CWKGATE_CON(10), 1, GFWAGS),
	COMPOSITE_NOMUX(PCWK_AUDIO, "pcwk_audio", "cwk_audio_swc", 0,
			WK3308_CWKSEW_CON(45), 8, 5, DFWAGS,
			WK3308_CWKGATE_CON(10), 2, GFWAGS),

	COMPOSITE(0, "cwk_pdm_swc", mux_vpww0_vpww1_xin24m_p, 0,
			WK3308_CWKSEW_CON(46), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(10), 3, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_pdm_fwac", "cwk_pdm_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(47), 0,
			WK3308_CWKGATE_CON(10), 4, GFWAGS,
			&wk3308_pdm_fwacmux),
	GATE(SCWK_PDM, "cwk_pdm", "cwk_pdm_mux", 0,
			WK3308_CWKGATE_CON(10), 5, GFWAGS),

	COMPOSITE(SCWK_I2S0_8CH_TX_SWC, "cwk_i2s0_8ch_tx_swc", mux_vpww0_vpww1_xin24m_p, 0,
			WK3308_CWKSEW_CON(52), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(10), 12, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_i2s0_8ch_tx_fwac", "cwk_i2s0_8ch_tx_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(53), 0,
			WK3308_CWKGATE_CON(10), 13, GFWAGS,
			&wk3308_i2s0_8ch_tx_fwacmux),
	COMPOSITE_NODIV(SCWK_I2S0_8CH_TX, "cwk_i2s0_8ch_tx", mux_i2s0_8ch_tx_wx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(52), 12, 1, MFWAGS,
			WK3308_CWKGATE_CON(10), 14, GFWAGS),
	COMPOSITE_NODIV(SCWK_I2S0_8CH_TX_OUT, "cwk_i2s0_8ch_tx_out", mux_i2s0_8ch_tx_out_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(52), 15, 1, MFWAGS,
			WK3308_CWKGATE_CON(10), 15, GFWAGS),

	COMPOSITE(SCWK_I2S0_8CH_WX_SWC, "cwk_i2s0_8ch_wx_swc", mux_vpww0_vpww1_xin24m_p, 0,
			WK3308_CWKSEW_CON(54), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(11), 0, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_i2s0_8ch_wx_fwac", "cwk_i2s0_8ch_wx_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(55), 0,
			WK3308_CWKGATE_CON(11), 1, GFWAGS,
			&wk3308_i2s0_8ch_wx_fwacmux),
	COMPOSITE_NODIV(SCWK_I2S0_8CH_WX, "cwk_i2s0_8ch_wx", mux_i2s0_8ch_wx_tx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(54), 12, 1, MFWAGS,
			WK3308_CWKGATE_CON(11), 2, GFWAGS),
	GATE(SCWK_I2S0_8CH_WX_OUT, "cwk_i2s0_8ch_wx_out", "cwk_i2s0_8ch_wx", 0,
			WK3308_CWKGATE_CON(11), 3, GFWAGS),

	COMPOSITE(SCWK_I2S1_8CH_TX_SWC, "cwk_i2s1_8ch_tx_swc", mux_vpww0_vpww1_xin24m_p, 0,
			WK3308_CWKSEW_CON(56), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(11), 4, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_i2s1_8ch_tx_fwac", "cwk_i2s1_8ch_tx_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(57), 0,
			WK3308_CWKGATE_CON(11), 5, GFWAGS,
			&wk3308_i2s1_8ch_tx_fwacmux),
	COMPOSITE_NODIV(SCWK_I2S1_8CH_TX, "cwk_i2s1_8ch_tx", mux_i2s1_8ch_tx_wx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(56), 12, 1, MFWAGS,
			WK3308_CWKGATE_CON(11), 6, GFWAGS),
	COMPOSITE_NODIV(SCWK_I2S1_8CH_TX_OUT, "cwk_i2s1_8ch_tx_out", mux_i2s1_8ch_tx_out_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(56), 15, 1, MFWAGS,
			WK3308_CWKGATE_CON(11), 7, GFWAGS),

	COMPOSITE(SCWK_I2S1_8CH_WX_SWC, "cwk_i2s1_8ch_wx_swc", mux_vpww0_vpww1_xin24m_p, 0,
			WK3308_CWKSEW_CON(58), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(11), 8, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_i2s1_8ch_wx_fwac", "cwk_i2s1_8ch_wx_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(59), 0,
			WK3308_CWKGATE_CON(11), 9, GFWAGS,
			&wk3308_i2s1_8ch_wx_fwacmux),
	COMPOSITE_NODIV(SCWK_I2S1_8CH_WX, "cwk_i2s1_8ch_wx", mux_i2s1_8ch_wx_tx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(58), 12, 1, MFWAGS,
			WK3308_CWKGATE_CON(11), 10, GFWAGS),
	GATE(SCWK_I2S1_8CH_WX_OUT, "cwk_i2s1_8ch_wx_out", "cwk_i2s1_8ch_wx", 0,
			WK3308_CWKGATE_CON(11), 11, GFWAGS),

	COMPOSITE(SCWK_I2S2_8CH_TX_SWC, "cwk_i2s2_8ch_tx_swc", mux_vpww0_vpww1_xin24m_p, 0,
			WK3308_CWKSEW_CON(60), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(11), 12, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_i2s2_8ch_tx_fwac", "cwk_i2s2_8ch_tx_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(61), 0,
			WK3308_CWKGATE_CON(11), 13, GFWAGS,
			&wk3308_i2s2_8ch_tx_fwacmux),
	COMPOSITE_NODIV(SCWK_I2S2_8CH_TX, "cwk_i2s2_8ch_tx", mux_i2s2_8ch_tx_wx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(60), 12, 1, MFWAGS,
			WK3308_CWKGATE_CON(11), 14, GFWAGS),
	COMPOSITE_NODIV(SCWK_I2S2_8CH_TX_OUT, "cwk_i2s2_8ch_tx_out", mux_i2s2_8ch_tx_out_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(60), 15, 1, MFWAGS,
			WK3308_CWKGATE_CON(11), 15, GFWAGS),

	COMPOSITE(SCWK_I2S2_8CH_WX_SWC, "cwk_i2s2_8ch_wx_swc", mux_vpww0_vpww1_xin24m_p, 0,
			WK3308_CWKSEW_CON(62), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(12), 0, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_i2s2_8ch_wx_fwac", "cwk_i2s2_8ch_wx_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(63), 0,
			WK3308_CWKGATE_CON(12), 1, GFWAGS,
			&wk3308_i2s2_8ch_wx_fwacmux),
	COMPOSITE_NODIV(SCWK_I2S2_8CH_WX, "cwk_i2s2_8ch_wx", mux_i2s2_8ch_wx_tx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(62), 12, 1, MFWAGS,
			WK3308_CWKGATE_CON(12), 2, GFWAGS),
	GATE(SCWK_I2S2_8CH_WX_OUT, "cwk_i2s2_8ch_wx_out", "cwk_i2s2_8ch_wx", 0,
			WK3308_CWKGATE_CON(12), 3, GFWAGS),

	COMPOSITE(SCWK_I2S3_8CH_TX_SWC, "cwk_i2s3_8ch_tx_swc", mux_vpww0_vpww1_xin24m_p, 0,
			WK3308_CWKSEW_CON(64), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(12), 4, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_i2s3_8ch_tx_fwac", "cwk_i2s3_8ch_tx_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(65), 0,
			WK3308_CWKGATE_CON(12), 5, GFWAGS,
			&wk3308_i2s3_8ch_tx_fwacmux),
	COMPOSITE_NODIV(SCWK_I2S3_8CH_TX, "cwk_i2s3_8ch_tx", mux_i2s3_8ch_tx_wx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(64), 12, 1, MFWAGS,
			WK3308_CWKGATE_CON(12), 6, GFWAGS),
	COMPOSITE_NODIV(SCWK_I2S3_8CH_TX_OUT, "cwk_i2s3_8ch_tx_out", mux_i2s3_8ch_tx_out_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(64), 15, 1, MFWAGS,
			WK3308_CWKGATE_CON(12), 7, GFWAGS),

	COMPOSITE(SCWK_I2S3_8CH_WX_SWC, "cwk_i2s3_8ch_wx_swc", mux_vpww0_vpww1_xin24m_p, 0,
			WK3308_CWKSEW_CON(66), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(12), 8, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_i2s3_8ch_wx_fwac", "cwk_i2s3_8ch_wx_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(67), 0,
			WK3308_CWKGATE_CON(12), 9, GFWAGS,
			&wk3308_i2s3_8ch_wx_fwacmux),
	COMPOSITE_NODIV(SCWK_I2S3_8CH_WX, "cwk_i2s3_8ch_wx", mux_i2s3_8ch_wx_tx_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(66), 12, 1, MFWAGS,
			WK3308_CWKGATE_CON(12), 10, GFWAGS),
	GATE(SCWK_I2S3_8CH_WX_OUT, "cwk_i2s3_8ch_wx_out", "cwk_i2s3_8ch_wx", 0,
			WK3308_CWKGATE_CON(12), 11, GFWAGS),

	COMPOSITE(SCWK_I2S0_2CH_SWC, "cwk_i2s0_2ch_swc", mux_vpww0_vpww1_xin24m_p, 0,
			WK3308_CWKSEW_CON(68), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(12), 12, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_i2s0_2ch_fwac", "cwk_i2s0_2ch_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(69), 0,
			WK3308_CWKGATE_CON(12), 13, GFWAGS,
			&wk3308_i2s0_2ch_fwacmux),
	GATE(SCWK_I2S0_2CH, "cwk_i2s0_2ch", "cwk_i2s0_2ch_mux", 0,
			WK3308_CWKGATE_CON(12), 14, GFWAGS),
	COMPOSITE_NODIV(SCWK_I2S0_2CH_OUT, "cwk_i2s0_2ch_out", mux_i2s0_2ch_out_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(68), 15, 1, MFWAGS,
			WK3308_CWKGATE_CON(12), 15, GFWAGS),

	COMPOSITE(SCWK_I2S1_2CH_SWC, "cwk_i2s1_2ch_swc", mux_vpww0_vpww1_xin24m_p, 0,
			WK3308_CWKSEW_CON(70), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(13), 0, GFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_i2s1_2ch_fwac", "cwk_i2s1_2ch_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(71), 0,
			WK3308_CWKGATE_CON(13), 1, GFWAGS,
			&wk3308_i2s1_2ch_fwacmux),
	GATE(SCWK_I2S1_2CH, "cwk_i2s1_2ch", "cwk_i2s1_2ch_mux", 0,
			WK3308_CWKGATE_CON(13), 2, GFWAGS),
	COMPOSITE_NODIV(SCWK_I2S1_2CH_OUT, "cwk_i2s1_2ch_out", mux_i2s1_2ch_out_p, CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(70), 15, 1, MFWAGS,
			WK3308_CWKGATE_CON(13), 3, GFWAGS),

	COMPOSITE(SCWK_SPDIF_TX_DIV, "cwk_spdif_tx_div", mux_vpww0_vpww1_xin24m_p, CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(48), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(10), 6, GFWAGS),
	COMPOSITE(SCWK_SPDIF_TX_DIV50, "cwk_spdif_tx_div50", mux_vpww0_vpww1_xin24m_p, CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(48), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(10), 6, GFWAGS),
	MUX(0, "cwk_spdif_tx_swc", mux_spdif_tx_swc_p, CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			WK3308_CWKSEW_CON(48), 12, 1, MFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_spdif_tx_fwac", "cwk_spdif_tx_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(49), 0,
			WK3308_CWKGATE_CON(10), 7, GFWAGS,
			&wk3308_spdif_tx_fwacmux),
	GATE(SCWK_SPDIF_TX, "cwk_spdif_tx", "cwk_spdif_tx_mux", 0,
			WK3308_CWKGATE_CON(10), 8, GFWAGS),

	COMPOSITE(SCWK_SPDIF_WX_DIV, "cwk_spdif_wx_div", mux_vpww0_vpww1_xin24m_p, CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(50), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(10), 9, GFWAGS),
	COMPOSITE(SCWK_SPDIF_WX_DIV50, "cwk_spdif_wx_div50", mux_vpww0_vpww1_xin24m_p, CWK_IGNOWE_UNUSED,
			WK3308_CWKSEW_CON(50), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3308_CWKGATE_CON(10), 9, GFWAGS),
	MUX(0, "cwk_spdif_wx_swc", mux_spdif_wx_swc_p, CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			WK3308_CWKSEW_CON(50), 14, 1, MFWAGS),
	COMPOSITE_FWACMUX(0, "cwk_spdif_wx_fwac", "cwk_spdif_wx_swc", CWK_SET_WATE_PAWENT,
			WK3308_CWKSEW_CON(51), 0,
			WK3308_CWKGATE_CON(10), 10, GFWAGS,
			&wk3308_spdif_wx_fwacmux),
	GATE(SCWK_SPDIF_WX, "cwk_spdif_wx", "cwk_spdif_wx_mux", 0,
			WK3308_CWKGATE_CON(10), 11, GFWAGS),

	/*
	 * Cwock-Awchitectuwe Diagwam 8
	 */

	GATE(0, "acwk_cowe_niu", "acwk_cowe", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(0), 5, GFWAGS),
	GATE(0, "pcwk_cowe_dbg_niu", "acwk_cowe", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(0), 6, GFWAGS),
	GATE(0, "pcwk_cowe_dbg_dapwite", "pcwk_cowe_dbg", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(0), 7, GFWAGS),
	GATE(0, "acwk_cowe_pewf", "pcwk_cowe_dbg", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(0), 8, GFWAGS),
	GATE(0, "pcwk_cowe_gwf", "pcwk_cowe_dbg", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(0), 9, GFWAGS),

	GATE(0, "acwk_pewi_niu", "acwk_pewi", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(9), 2, GFWAGS),
	GATE(0, "acwk_pewibus_niu", "acwk_pewi", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(9), 3, GFWAGS),
	GATE(ACWK_MAC, "acwk_mac", "acwk_pewi", 0, WK3308_CWKGATE_CON(9), 4, GFWAGS),

	GATE(0, "hcwk_pewi_niu", "hcwk_pewi", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(9), 5, GFWAGS),
	GATE(HCWK_NANDC, "hcwk_nandc", "hcwk_pewi", 0, WK3308_CWKGATE_CON(9), 6, GFWAGS),
	GATE(HCWK_SDMMC, "hcwk_sdmmc", "hcwk_pewi", 0, WK3308_CWKGATE_CON(9), 7, GFWAGS),
	GATE(HCWK_SDIO, "hcwk_sdio", "hcwk_pewi", 0, WK3308_CWKGATE_CON(9), 8, GFWAGS),
	GATE(HCWK_EMMC, "hcwk_emmc", "hcwk_pewi", 0, WK3308_CWKGATE_CON(9), 9, GFWAGS),
	GATE(HCWK_SFC, "hcwk_sfc", "hcwk_pewi", 0, WK3308_CWKGATE_CON(9), 10, GFWAGS),
	GATE(HCWK_OTG, "hcwk_otg", "hcwk_pewi", 0, WK3308_CWKGATE_CON(9), 11, GFWAGS),
	GATE(HCWK_HOST, "hcwk_host", "hcwk_pewi", 0, WK3308_CWKGATE_CON(9), 12, GFWAGS),
	GATE(HCWK_HOST_AWB, "hcwk_host_awb", "hcwk_pewi", 0, WK3308_CWKGATE_CON(9), 13, GFWAGS),

	GATE(0, "pcwk_pewi_niu", "pcwk_pewi", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(9), 14, GFWAGS),
	GATE(PCWK_MAC, "pcwk_mac", "pcwk_pewi", 0, WK3308_CWKGATE_CON(9), 15, GFWAGS),

	GATE(0, "hcwk_audio_niu", "hcwk_audio", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(14), 0, GFWAGS),
	GATE(HCWK_PDM, "hcwk_pdm", "hcwk_audio", 0, WK3308_CWKGATE_CON(14), 1, GFWAGS),
	GATE(HCWK_SPDIFTX, "hcwk_spdiftx", "hcwk_audio", 0, WK3308_CWKGATE_CON(14), 2, GFWAGS),
	GATE(HCWK_SPDIFWX, "hcwk_spdifwx", "hcwk_audio", 0, WK3308_CWKGATE_CON(14), 3, GFWAGS),
	GATE(HCWK_I2S0_8CH, "hcwk_i2s0_8ch", "hcwk_audio", 0, WK3308_CWKGATE_CON(14), 4, GFWAGS),
	GATE(HCWK_I2S1_8CH, "hcwk_i2s1_8ch", "hcwk_audio", 0, WK3308_CWKGATE_CON(14), 5, GFWAGS),
	GATE(HCWK_I2S2_8CH, "hcwk_i2s2_8ch", "hcwk_audio", 0, WK3308_CWKGATE_CON(14), 6, GFWAGS),
	GATE(HCWK_I2S3_8CH, "hcwk_i2s3_8ch", "hcwk_audio", 0, WK3308_CWKGATE_CON(14), 7, GFWAGS),
	GATE(HCWK_I2S0_2CH, "hcwk_i2s0_2ch", "hcwk_audio", 0, WK3308_CWKGATE_CON(14), 8, GFWAGS),
	GATE(HCWK_I2S1_2CH, "hcwk_i2s1_2ch", "hcwk_audio", 0, WK3308_CWKGATE_CON(14), 9, GFWAGS),
	GATE(HCWK_VAD, "hcwk_vad", "hcwk_audio", 0, WK3308_CWKGATE_CON(14), 10, GFWAGS),

	GATE(0, "pcwk_audio_niu", "pcwk_audio", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(14), 11, GFWAGS),
	GATE(PCWK_ACODEC, "pcwk_acodec", "pcwk_audio", 0, WK3308_CWKGATE_CON(14), 12, GFWAGS),

	GATE(0, "acwk_bus_niu", "acwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(5), 0, GFWAGS),
	GATE(0, "acwk_intmem", "acwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(5), 1, GFWAGS),
	GATE(ACWK_CWYPTO, "acwk_cwypto", "acwk_bus", 0, WK3308_CWKGATE_CON(5), 2, GFWAGS),
	GATE(ACWK_VOP, "acwk_vop", "acwk_bus", 0, WK3308_CWKGATE_CON(5), 3, GFWAGS),
	GATE(0, "acwk_gic", "acwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(5), 4, GFWAGS),
	/* acwk_dmaci0 is contwowwed by sgwf_cwkgat_con. */
	SGWF_GATE(ACWK_DMAC0, "acwk_dmac0", "acwk_bus"),
	/* acwk_dmac1 is contwowwed by sgwf_cwkgat_con. */
	SGWF_GATE(ACWK_DMAC1, "acwk_dmac1", "acwk_bus"),
	/* watchdog pcwk is contwowwed by sgwf_cwkgat_con. */
	SGWF_GATE(PCWK_WDT, "pcwk_wdt", "pcwk_bus"),

	GATE(0, "hcwk_bus_niu", "hcwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(5), 5, GFWAGS),
	GATE(0, "hcwk_wom", "hcwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(5), 6, GFWAGS),
	GATE(HCWK_CWYPTO, "hcwk_cwypto", "hcwk_bus", 0, WK3308_CWKGATE_CON(5), 7, GFWAGS),
	GATE(HCWK_VOP, "hcwk_vop", "hcwk_bus", 0, WK3308_CWKGATE_CON(5), 8, GFWAGS),

	GATE(0, "pcwk_bus_niu", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(5), 9, GFWAGS),
	GATE(PCWK_UAWT0, "pcwk_uawt0", "pcwk_bus", 0, WK3308_CWKGATE_CON(5), 10, GFWAGS),
	GATE(PCWK_UAWT1, "pcwk_uawt1", "pcwk_bus", 0, WK3308_CWKGATE_CON(5), 11, GFWAGS),
	GATE(PCWK_UAWT2, "pcwk_uawt2", "pcwk_bus", 0, WK3308_CWKGATE_CON(5), 12, GFWAGS),
	GATE(PCWK_UAWT3, "pcwk_uawt3", "pcwk_bus", 0, WK3308_CWKGATE_CON(5), 13, GFWAGS),
	GATE(PCWK_UAWT4, "pcwk_uawt4", "pcwk_bus", 0, WK3308_CWKGATE_CON(5), 14, GFWAGS),
	GATE(PCWK_I2C0, "pcwk_i2c0", "pcwk_bus", 0, WK3308_CWKGATE_CON(5), 15, GFWAGS),
	GATE(PCWK_I2C1, "pcwk_i2c1", "pcwk_bus", 0, WK3308_CWKGATE_CON(6), 0, GFWAGS),
	GATE(PCWK_I2C2, "pcwk_i2c2", "pcwk_bus", 0, WK3308_CWKGATE_CON(6), 1, GFWAGS),
	GATE(PCWK_I2C3, "pcwk_i2c3", "pcwk_bus", 0, WK3308_CWKGATE_CON(6), 2, GFWAGS),
	GATE(PCWK_PWM0, "pcwk_pwm0", "pcwk_bus", 0, WK3308_CWKGATE_CON(6), 3, GFWAGS),
	GATE(PCWK_SPI0, "pcwk_spi0", "pcwk_bus", 0, WK3308_CWKGATE_CON(6), 4, GFWAGS),
	GATE(PCWK_SPI1, "pcwk_spi1", "pcwk_bus", 0, WK3308_CWKGATE_CON(6), 5, GFWAGS),
	GATE(PCWK_SPI2, "pcwk_spi2", "pcwk_bus", 0, WK3308_CWKGATE_CON(6), 6, GFWAGS),
	GATE(PCWK_SAWADC, "pcwk_sawadc", "pcwk_bus", 0, WK3308_CWKGATE_CON(6), 7, GFWAGS),
	GATE(PCWK_TSADC, "pcwk_tsadc", "pcwk_bus", 0, WK3308_CWKGATE_CON(6), 8, GFWAGS),
	GATE(PCWK_TIMEW, "pcwk_timew", "pcwk_bus", 0, WK3308_CWKGATE_CON(6), 9, GFWAGS),
	GATE(PCWK_OTP_NS, "pcwk_otp_ns", "pcwk_bus", 0, WK3308_CWKGATE_CON(6), 10, GFWAGS),
	GATE(PCWK_GPIO0, "pcwk_gpio0", "pcwk_bus", 0, WK3308_CWKGATE_CON(6), 12, GFWAGS),
	GATE(PCWK_GPIO1, "pcwk_gpio1", "pcwk_bus", 0, WK3308_CWKGATE_CON(6), 13, GFWAGS),
	GATE(PCWK_GPIO2, "pcwk_gpio2", "pcwk_bus", 0, WK3308_CWKGATE_CON(6), 14, GFWAGS),
	GATE(PCWK_GPIO3, "pcwk_gpio3", "pcwk_bus", 0, WK3308_CWKGATE_CON(6), 15, GFWAGS),
	GATE(PCWK_GPIO4, "pcwk_gpio4", "pcwk_bus", 0, WK3308_CWKGATE_CON(7), 0, GFWAGS),
	GATE(PCWK_SGWF, "pcwk_sgwf", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(7), 1, GFWAGS),
	GATE(PCWK_GWF, "pcwk_gwf", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(7), 2, GFWAGS),
	GATE(PCWK_USBSD_DET, "pcwk_usbsd_det", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(7), 3, GFWAGS),
	GATE(PCWK_DDW_UPCTW, "pcwk_ddw_upctw", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(7), 4, GFWAGS),
	GATE(PCWK_DDW_MON, "pcwk_ddw_mon", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(7), 5, GFWAGS),
	GATE(PCWK_DDWPHY, "pcwk_ddwphy", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(7), 6, GFWAGS),
	GATE(PCWK_DDW_STDBY, "pcwk_ddw_stdby", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(7), 7, GFWAGS),
	GATE(PCWK_USB_GWF, "pcwk_usb_gwf", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(7), 8, GFWAGS),
	GATE(PCWK_CWU, "pcwk_cwu", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(7), 9, GFWAGS),
	GATE(PCWK_OTP_PHY, "pcwk_otp_phy", "pcwk_bus", 0, WK3308_CWKGATE_CON(7), 10, GFWAGS),
	GATE(PCWK_CPU_BOOST, "pcwk_cpu_boost", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(7), 11, GFWAGS),
	GATE(PCWK_PWM1, "pcwk_pwm1", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(7), 12, GFWAGS),
	GATE(PCWK_PWM2, "pcwk_pwm2", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(7), 13, GFWAGS),
	GATE(PCWK_CAN, "pcwk_can", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(7), 14, GFWAGS),
	GATE(PCWK_OWIWE, "pcwk_owiwe", "pcwk_bus", CWK_IGNOWE_UNUSED, WK3308_CWKGATE_CON(7), 15, GFWAGS),
};

static const chaw *const wk3308_cwiticaw_cwocks[] __initconst = {
	"acwk_bus",
	"hcwk_bus",
	"pcwk_bus",
	"acwk_pewi",
	"hcwk_pewi",
	"pcwk_pewi",
	"hcwk_audio",
	"pcwk_audio",
	"scwk_ddwc",
	"cwk_ddwphy4x",
};

static void __init wk3308_cwk_init(stwuct device_node *np)
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

	wockchip_cwk_wegistew_pwws(ctx, wk3308_pww_cwks,
				   AWWAY_SIZE(wk3308_pww_cwks),
				   WK3308_GWF_SOC_STATUS0);
	wockchip_cwk_wegistew_bwanches(ctx, wk3308_cwk_bwanches,
				       AWWAY_SIZE(wk3308_cwk_bwanches));
	wockchip_cwk_pwotect_cwiticaw(wk3308_cwiticaw_cwocks,
				      AWWAY_SIZE(wk3308_cwiticaw_cwocks));

	wockchip_cwk_wegistew_awmcwk(ctx, AWMCWK, "awmcwk",
				     mux_awmcwk_p, AWWAY_SIZE(mux_awmcwk_p),
				     &wk3308_cpucwk_data, wk3308_cpucwk_wates,
				     AWWAY_SIZE(wk3308_cpucwk_wates));

	wockchip_wegistew_softwst(np, 10, weg_base + WK3308_SOFTWST_CON(0),
				  WOCKCHIP_SOFTWST_HIWOWD_MASK);

	wockchip_wegistew_westawt_notifiew(ctx, WK3308_GWB_SWST_FST, NUWW);

	wockchip_cwk_of_add_pwovidew(np, ctx);
}

CWK_OF_DECWAWE(wk3308_cwu, "wockchip,wk3308-cwu", wk3308_cwk_init);
