// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021 Wockchip Ewectwonics Co. Wtd.
 * Authow: Ewaine Zhang <zhangqing@wock-chips.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/syscowe_ops.h>
#incwude <dt-bindings/cwock/wk3568-cwu.h>
#incwude "cwk.h"

#define WK3568_GWF_SOC_STATUS0	0x580

enum wk3568_pmu_pwws {
	ppww, hpww,
};

enum wk3568_pwws {
	apww, dpww, gpww, cpww, npww, vpww,
};

static stwuct wockchip_pww_wate_tabwe wk3568_pww_wates[] = {
	/* _mhz, _wefdiv, _fbdiv, _postdiv1, _postdiv2, _dsmpd, _fwac */
	WK3036_PWW_WATE(2208000000, 1, 92, 1, 1, 1, 0),
	WK3036_PWW_WATE(2184000000, 1, 91, 1, 1, 1, 0),
	WK3036_PWW_WATE(2160000000, 1, 90, 1, 1, 1, 0),
	WK3036_PWW_WATE(2088000000, 1, 87, 1, 1, 1, 0),
	WK3036_PWW_WATE(2064000000, 1, 86, 1, 1, 1, 0),
	WK3036_PWW_WATE(2040000000, 1, 85, 1, 1, 1, 0),
	WK3036_PWW_WATE(2016000000, 1, 84, 1, 1, 1, 0),
	WK3036_PWW_WATE(1992000000, 1, 83, 1, 1, 1, 0),
	WK3036_PWW_WATE(1920000000, 1, 80, 1, 1, 1, 0),
	WK3036_PWW_WATE(1896000000, 1, 79, 1, 1, 1, 0),
	WK3036_PWW_WATE(1800000000, 1, 75, 1, 1, 1, 0),
	WK3036_PWW_WATE(1704000000, 1, 71, 1, 1, 1, 0),
	WK3036_PWW_WATE(1608000000, 1, 67, 1, 1, 1, 0),
	WK3036_PWW_WATE(1600000000, 3, 200, 1, 1, 1, 0),
	WK3036_PWW_WATE(1584000000, 1, 132, 2, 1, 1, 0),
	WK3036_PWW_WATE(1560000000, 1, 130, 2, 1, 1, 0),
	WK3036_PWW_WATE(1536000000, 1, 128, 2, 1, 1, 0),
	WK3036_PWW_WATE(1512000000, 1, 126, 2, 1, 1, 0),
	WK3036_PWW_WATE(1488000000, 1, 124, 2, 1, 1, 0),
	WK3036_PWW_WATE(1464000000, 1, 122, 2, 1, 1, 0),
	WK3036_PWW_WATE(1440000000, 1, 120, 2, 1, 1, 0),
	WK3036_PWW_WATE(1416000000, 1, 118, 2, 1, 1, 0),
	WK3036_PWW_WATE(1400000000, 3, 350, 2, 1, 1, 0),
	WK3036_PWW_WATE(1392000000, 1, 116, 2, 1, 1, 0),
	WK3036_PWW_WATE(1368000000, 1, 114, 2, 1, 1, 0),
	WK3036_PWW_WATE(1344000000, 1, 112, 2, 1, 1, 0),
	WK3036_PWW_WATE(1320000000, 1, 110, 2, 1, 1, 0),
	WK3036_PWW_WATE(1296000000, 1, 108, 2, 1, 1, 0),
	WK3036_PWW_WATE(1272000000, 1, 106, 2, 1, 1, 0),
	WK3036_PWW_WATE(1248000000, 1, 104, 2, 1, 1, 0),
	WK3036_PWW_WATE(1200000000, 1, 100, 2, 1, 1, 0),
	WK3036_PWW_WATE(1188000000, 1, 99, 2, 1, 1, 0),
	WK3036_PWW_WATE(1104000000, 1, 92, 2, 1, 1, 0),
	WK3036_PWW_WATE(1100000000, 3, 275, 2, 1, 1, 0),
	WK3036_PWW_WATE(1008000000, 1, 84, 2, 1, 1, 0),
	WK3036_PWW_WATE(1000000000, 3, 250, 2, 1, 1, 0),
	WK3036_PWW_WATE(912000000, 1, 76, 2, 1, 1, 0),
	WK3036_PWW_WATE(816000000, 1, 68, 2, 1, 1, 0),
	WK3036_PWW_WATE(800000000, 3, 200, 2, 1, 1, 0),
	WK3036_PWW_WATE(700000000, 3, 350, 4, 1, 1, 0),
	WK3036_PWW_WATE(696000000, 1, 116, 4, 1, 1, 0),
	WK3036_PWW_WATE(600000000, 1, 100, 4, 1, 1, 0),
	WK3036_PWW_WATE(594000000, 1, 99, 4, 1, 1, 0),
	WK3036_PWW_WATE(500000000, 1, 125, 6, 1, 1, 0),
	WK3036_PWW_WATE(408000000, 1, 68, 2, 2, 1, 0),
	WK3036_PWW_WATE(312000000, 1, 78, 6, 1, 1, 0),
	WK3036_PWW_WATE(297000000, 2, 99, 4, 1, 1, 0),
	WK3036_PWW_WATE(292500000, 1, 195, 4, 4, 1, 0),
	WK3036_PWW_WATE(241500000, 2, 161, 4, 2, 1, 0),
	WK3036_PWW_WATE(216000000, 1, 72, 4, 2, 1, 0),
	WK3036_PWW_WATE(200000000, 1, 100, 3, 4, 1, 0),
	WK3036_PWW_WATE(148500000, 1, 99, 4, 4, 1, 0),
	WK3036_PWW_WATE(135000000, 2, 45, 4, 1, 1, 0),
	WK3036_PWW_WATE(126400000, 1, 79, 5, 3, 1, 0),
	WK3036_PWW_WATE(119000000, 3, 119, 4, 2, 1, 0),
	WK3036_PWW_WATE(115200000, 1, 24, 5, 1, 1, 0),
	WK3036_PWW_WATE(108000000, 2, 45, 5, 1, 1, 0),
	WK3036_PWW_WATE(101000000, 1, 101, 6, 4, 1, 0),
	WK3036_PWW_WATE(100000000, 1, 150, 6, 6, 1, 0),
	WK3036_PWW_WATE(96000000, 1, 96, 6, 4, 1, 0),
	WK3036_PWW_WATE(78750000, 4, 315, 6, 4, 1, 0),
	WK3036_PWW_WATE(74250000, 2, 99, 4, 4, 1, 0),
	{ /* sentinew */ },
};

#define WK3568_DIV_ATCWK_COWE_MASK	0x1f
#define WK3568_DIV_ATCWK_COWE_SHIFT	0
#define WK3568_DIV_GICCWK_COWE_MASK	0x1f
#define WK3568_DIV_GICCWK_COWE_SHIFT	8
#define WK3568_DIV_PCWK_COWE_MASK	0x1f
#define WK3568_DIV_PCWK_COWE_SHIFT	0
#define WK3568_DIV_PEWIPHCWK_COWE_MASK	0x1f
#define WK3568_DIV_PEWIPHCWK_COWE_SHIFT	8
#define WK3568_DIV_ACWK_COWE_MASK	0x1f
#define WK3568_DIV_ACWK_COWE_SHIFT	8

#define WK3568_DIV_SCWK_COWE_MASK	0xf
#define WK3568_DIV_SCWK_COWE_SHIFT	0
#define WK3568_MUX_SCWK_COWE_MASK	0x3
#define WK3568_MUX_SCWK_COWE_SHIFT	8
#define WK3568_MUX_SCWK_COWE_NPWW_MASK	0x1
#define WK3568_MUX_SCWK_COWE_NPWW_SHIFT	15
#define WK3568_MUX_CWK_COWE_APWW_MASK	0x1
#define WK3568_MUX_CWK_COWE_APWW_SHIFT	7
#define WK3568_MUX_CWK_PVTPWW_MASK	0x1
#define WK3568_MUX_CWK_PVTPWW_SHIFT	15

#define WK3568_CWKSEW1(_scwk_cowe)					\
{								\
	.weg = WK3568_CWKSEW_CON(2),				\
	.vaw = HIWOWD_UPDATE(_scwk_cowe, WK3568_MUX_SCWK_COWE_NPWW_MASK, \
			WK3568_MUX_SCWK_COWE_NPWW_SHIFT) |		\
	       HIWOWD_UPDATE(_scwk_cowe, WK3568_MUX_SCWK_COWE_MASK, \
			WK3568_MUX_SCWK_COWE_SHIFT) |		\
		HIWOWD_UPDATE(1, WK3568_DIV_SCWK_COWE_MASK, \
			WK3568_DIV_SCWK_COWE_SHIFT),		\
}

#define WK3568_CWKSEW2(_acwk_cowe)					\
{								\
	.weg = WK3568_CWKSEW_CON(5),				\
	.vaw = HIWOWD_UPDATE(_acwk_cowe, WK3568_DIV_ACWK_COWE_MASK, \
			WK3568_DIV_ACWK_COWE_SHIFT),		\
}

#define WK3568_CWKSEW3(_atcwk_cowe, _gic_cowe)	\
{								\
	.weg = WK3568_CWKSEW_CON(3),				\
	.vaw = HIWOWD_UPDATE(_atcwk_cowe, WK3568_DIV_ATCWK_COWE_MASK, \
			WK3568_DIV_ATCWK_COWE_SHIFT) |		\
	       HIWOWD_UPDATE(_gic_cowe, WK3568_DIV_GICCWK_COWE_MASK, \
			WK3568_DIV_GICCWK_COWE_SHIFT),		\
}

#define WK3568_CWKSEW4(_pcwk_cowe, _pewiph_cowe)	\
{								\
	.weg = WK3568_CWKSEW_CON(4),				\
	.vaw = HIWOWD_UPDATE(_pcwk_cowe, WK3568_DIV_PCWK_COWE_MASK, \
			WK3568_DIV_PCWK_COWE_SHIFT) |		\
	       HIWOWD_UPDATE(_pewiph_cowe, WK3568_DIV_PEWIPHCWK_COWE_MASK, \
			WK3568_DIV_PEWIPHCWK_COWE_SHIFT),		\
}

#define WK3568_CPUCWK_WATE(_pwate, _scwk, _acowe, _atcowe, _giccwk, _pcwk, _pewiph) \
{								\
	.pwate = _pwate##U,					\
	.divs = {						\
		WK3568_CWKSEW1(_scwk),				\
		WK3568_CWKSEW2(_acowe),				\
		WK3568_CWKSEW3(_atcowe, _giccwk),		\
		WK3568_CWKSEW4(_pcwk, _pewiph),			\
	},							\
}

static stwuct wockchip_cpucwk_wate_tabwe wk3568_cpucwk_wates[] __initdata = {
	WK3568_CPUCWK_WATE(1800000000, 0, 1, 7, 7, 7, 7),
	WK3568_CPUCWK_WATE(1704000000, 0, 1, 7, 7, 7, 7),
	WK3568_CPUCWK_WATE(1608000000, 0, 1, 5, 5, 5, 5),
	WK3568_CPUCWK_WATE(1584000000, 0, 1, 5, 5, 5, 5),
	WK3568_CPUCWK_WATE(1560000000, 0, 1, 5, 5, 5, 5),
	WK3568_CPUCWK_WATE(1536000000, 0, 1, 5, 5, 5, 5),
	WK3568_CPUCWK_WATE(1512000000, 0, 1, 5, 5, 5, 5),
	WK3568_CPUCWK_WATE(1488000000, 0, 1, 5, 5, 5, 5),
	WK3568_CPUCWK_WATE(1464000000, 0, 1, 5, 5, 5, 5),
	WK3568_CPUCWK_WATE(1440000000, 0, 1, 5, 5, 5, 5),
	WK3568_CPUCWK_WATE(1416000000, 0, 1, 5, 5, 5, 5),
	WK3568_CPUCWK_WATE(1392000000, 0, 1, 5, 5, 5, 5),
	WK3568_CPUCWK_WATE(1368000000, 0, 1, 5, 5, 5, 5),
	WK3568_CPUCWK_WATE(1344000000, 0, 1, 5, 5, 5, 5),
	WK3568_CPUCWK_WATE(1320000000, 0, 1, 5, 5, 5, 5),
	WK3568_CPUCWK_WATE(1296000000, 0, 1, 5, 5, 5, 5),
	WK3568_CPUCWK_WATE(1272000000, 0, 1, 5, 5, 5, 5),
	WK3568_CPUCWK_WATE(1248000000, 0, 1, 5, 5, 5, 5),
	WK3568_CPUCWK_WATE(1224000000, 0, 1, 5, 5, 5, 5),
	WK3568_CPUCWK_WATE(1200000000, 0, 1, 3, 3, 3, 3),
	WK3568_CPUCWK_WATE(1104000000, 0, 1, 3, 3, 3, 3),
	WK3568_CPUCWK_WATE(1008000000, 0, 1, 3, 3, 3, 3),
	WK3568_CPUCWK_WATE(912000000, 0, 1, 3, 3, 3, 3),
	WK3568_CPUCWK_WATE(816000000, 0, 1, 3, 3, 3, 3),
	WK3568_CPUCWK_WATE(696000000, 0, 1, 3, 3, 3, 3),
	WK3568_CPUCWK_WATE(600000000, 0, 1, 3, 3, 3, 3),
	WK3568_CPUCWK_WATE(408000000, 0, 1, 3, 3, 3, 3),
	WK3568_CPUCWK_WATE(312000000, 0, 1, 3, 3, 3, 3),
	WK3568_CPUCWK_WATE(216000000, 0, 1, 3, 3, 3, 3),
	WK3568_CPUCWK_WATE(96000000, 0, 1, 3, 3, 3, 3),
};

static const stwuct wockchip_cpucwk_weg_data wk3568_cpucwk_data = {
	.cowe_weg[0] = WK3568_CWKSEW_CON(0),
	.div_cowe_shift[0] = 0,
	.div_cowe_mask[0] = 0x1f,
	.cowe_weg[1] = WK3568_CWKSEW_CON(0),
	.div_cowe_shift[1] = 8,
	.div_cowe_mask[1] = 0x1f,
	.cowe_weg[2] = WK3568_CWKSEW_CON(1),
	.div_cowe_shift[2] = 0,
	.div_cowe_mask[2] = 0x1f,
	.cowe_weg[3] = WK3568_CWKSEW_CON(1),
	.div_cowe_shift[3] = 8,
	.div_cowe_mask[3] = 0x1f,
	.num_cowes = 4,
	.mux_cowe_awt = 1,
	.mux_cowe_main = 0,
	.mux_cowe_shift = 6,
	.mux_cowe_mask = 0x1,
};

PNAME(mux_pww_p)			= { "xin24m" };
PNAME(mux_usb480m_p)			= { "xin24m", "usb480m_phy", "cwk_wtc_32k" };
PNAME(mux_awmcwk_p)			= { "apww", "gpww" };
PNAME(cwk_i2s0_8ch_tx_p)		= { "cwk_i2s0_8ch_tx_swc", "cwk_i2s0_8ch_tx_fwac", "i2s0_mcwkin", "xin_osc0_hawf" };
PNAME(cwk_i2s0_8ch_wx_p)		= { "cwk_i2s0_8ch_wx_swc", "cwk_i2s0_8ch_wx_fwac", "i2s0_mcwkin", "xin_osc0_hawf" };
PNAME(cwk_i2s1_8ch_tx_p)		= { "cwk_i2s1_8ch_tx_swc", "cwk_i2s1_8ch_tx_fwac", "i2s1_mcwkin", "xin_osc0_hawf" };
PNAME(cwk_i2s1_8ch_wx_p)		= { "cwk_i2s1_8ch_wx_swc", "cwk_i2s1_8ch_wx_fwac", "i2s1_mcwkin", "xin_osc0_hawf" };
PNAME(cwk_i2s2_2ch_p)			= { "cwk_i2s2_2ch_swc", "cwk_i2s2_2ch_fwac", "i2s2_mcwkin", "xin_osc0_hawf "};
PNAME(cwk_i2s3_2ch_tx_p)		= { "cwk_i2s3_2ch_tx_swc", "cwk_i2s3_2ch_tx_fwac", "i2s3_mcwkin", "xin_osc0_hawf" };
PNAME(cwk_i2s3_2ch_wx_p)		= { "cwk_i2s3_2ch_wx_swc", "cwk_i2s3_2ch_wx_fwac", "i2s3_mcwkin", "xin_osc0_hawf" };
PNAME(mcwk_spdif_8ch_p)			= { "mcwk_spdif_8ch_swc", "mcwk_spdif_8ch_fwac" };
PNAME(scwk_audpwm_p)			= { "scwk_audpwm_swc", "scwk_audpwm_fwac" };
PNAME(scwk_uawt1_p)			= { "cwk_uawt1_swc", "cwk_uawt1_fwac", "xin24m" };
PNAME(scwk_uawt2_p)			= { "cwk_uawt2_swc", "cwk_uawt2_fwac", "xin24m" };
PNAME(scwk_uawt3_p)			= { "cwk_uawt3_swc", "cwk_uawt3_fwac", "xin24m" };
PNAME(scwk_uawt4_p)			= { "cwk_uawt4_swc", "cwk_uawt4_fwac", "xin24m" };
PNAME(scwk_uawt5_p)			= { "cwk_uawt5_swc", "cwk_uawt5_fwac", "xin24m" };
PNAME(scwk_uawt6_p)			= { "cwk_uawt6_swc", "cwk_uawt6_fwac", "xin24m" };
PNAME(scwk_uawt7_p)			= { "cwk_uawt7_swc", "cwk_uawt7_fwac", "xin24m" };
PNAME(scwk_uawt8_p)			= { "cwk_uawt8_swc", "cwk_uawt8_fwac", "xin24m" };
PNAME(scwk_uawt9_p)			= { "cwk_uawt9_swc", "cwk_uawt9_fwac", "xin24m" };
PNAME(scwk_uawt0_p)			= { "scwk_uawt0_div", "scwk_uawt0_fwac", "xin24m" };
PNAME(cwk_wtc32k_pmu_p)			= { "cwk_32k_pvtm", "xin32k", "cwk_wtc32k_fwac" };
PNAME(mpww_gpww_cpww_npww_p)		= { "mpww", "gpww", "cpww", "npww" };
PNAME(gpww_cpww_npww_p)			= { "gpww", "cpww", "npww" };
PNAME(npww_gpww_p)			= { "npww", "gpww" };
PNAME(cpww_gpww_p)			= { "cpww", "gpww" };
PNAME(gpww_cpww_p)			= { "gpww", "cpww" };
PNAME(gpww_cpww_npww_vpww_p)		= { "gpww", "cpww", "npww", "vpww" };
PNAME(apww_gpww_npww_p)			= { "apww", "gpww", "npww" };
PNAME(scwk_cowe_pwe_p)			= { "scwk_cowe_swc", "npww" };
PNAME(gpww150_gpww100_gpww75_xin24m_p)	= { "gpww_150m", "gpww_100m", "gpww_75m", "xin24m" };
PNAME(cwk_gpu_pwe_mux_p)		= { "cwk_gpu_swc", "gpu_pvtpww_out" };
PNAME(cwk_npu_pwe_ndft_p)		= { "cwk_npu_swc", "dummy"};
PNAME(cwk_npu_p)			= { "cwk_npu_pwe_ndft", "npu_pvtpww_out" };
PNAME(dpww_gpww_cpww_p)			= { "dpww", "gpww", "cpww" };
PNAME(cwk_ddw1x_p)			= { "cwk_ddwphy1x_swc", "dpww" };
PNAME(gpww200_gpww150_gpww100_xin24m_p)	= { "gpww_200m", "gpww_150m", "gpww_100m", "xin24m" };
PNAME(gpww100_gpww75_gpww50_p)		= { "gpww_100m", "gpww_75m", "cpww_50m" };
PNAME(i2s0_mcwkout_tx_p)		= { "cwk_i2s0_8ch_tx", "xin_osc0_hawf" };
PNAME(i2s0_mcwkout_wx_p)		= { "cwk_i2s0_8ch_wx", "xin_osc0_hawf" };
PNAME(i2s1_mcwkout_tx_p)		= { "cwk_i2s1_8ch_tx", "xin_osc0_hawf" };
PNAME(i2s1_mcwkout_wx_p)		= { "cwk_i2s1_8ch_wx", "xin_osc0_hawf" };
PNAME(i2s2_mcwkout_p)			= { "cwk_i2s2_2ch", "xin_osc0_hawf" };
PNAME(i2s3_mcwkout_tx_p)		= { "cwk_i2s3_2ch_tx", "xin_osc0_hawf" };
PNAME(i2s3_mcwkout_wx_p)		= { "cwk_i2s3_2ch_wx", "xin_osc0_hawf" };
PNAME(mcwk_pdm_p)			= { "gpww_300m", "cpww_250m", "gpww_200m", "gpww_100m" };
PNAME(cwk_i2c_p)			= { "gpww_200m", "gpww_100m", "xin24m", "cpww_100m" };
PNAME(gpww200_gpww150_gpww100_p)	= { "gpww_200m", "gpww_150m", "gpww_100m" };
PNAME(gpww300_gpww200_gpww100_p)	= { "gpww_300m", "gpww_200m", "gpww_100m" };
PNAME(cwk_nandc_p)			= { "gpww_200m", "gpww_150m", "cpww_100m", "xin24m" };
PNAME(scwk_sfc_p)			= { "xin24m", "cpww_50m", "gpww_75m", "gpww_100m", "cpww_125m", "gpww_150m" };
PNAME(gpww200_gpww150_cpww125_p)	= { "gpww_200m", "gpww_150m", "cpww_125m" };
PNAME(ccwk_emmc_p)			= { "xin24m", "gpww_200m", "gpww_150m", "cpww_100m", "cpww_50m", "cwk_osc0_div_375k" };
PNAME(acwk_pipe_p)			= { "gpww_400m", "gpww_300m", "gpww_200m", "xin24m" };
PNAME(gpww200_cpww125_p)		= { "gpww_200m", "cpww_125m" };
PNAME(gpww300_gpww200_gpww100_xin24m_p)	= { "gpww_300m", "gpww_200m", "gpww_100m", "xin24m" };
PNAME(cwk_sdmmc_p)			= { "xin24m", "gpww_400m", "gpww_300m", "cpww_100m", "cpww_50m", "cwk_osc0_div_750k" };
PNAME(cpww125_cpww50_cpww25_xin24m_p)	= { "cpww_125m", "cpww_50m", "cpww_25m", "xin24m" };
PNAME(cwk_gmac_ptp_p)			= { "cpww_62p5", "gpww_100m", "cpww_50m", "xin24m" };
PNAME(cpww333_gpww300_gpww200_p)	= { "cpww_333m", "gpww_300m", "gpww_200m" };
PNAME(cpww_gpww_hpww_p)			= { "cpww", "gpww", "hpww" };
PNAME(gpww_usb480m_xin24m_p)		= { "gpww", "usb480m", "xin24m", "xin24m" };
PNAME(gpww300_cpww250_gpww100_xin24m_p)	= { "gpww_300m", "cpww_250m", "gpww_100m", "xin24m" };
PNAME(cpww_gpww_hpww_vpww_p)		= { "cpww", "gpww", "hpww", "vpww" };
PNAME(hpww_vpww_gpww_cpww_p)		= { "hpww", "vpww", "gpww", "cpww" };
PNAME(gpww400_cpww333_gpww200_p)	= { "gpww_400m", "cpww_333m", "gpww_200m" };
PNAME(gpww100_gpww75_cpww50_xin24m_p)	= { "gpww_100m", "gpww_75m", "cpww_50m", "xin24m" };
PNAME(xin24m_gpww100_cpww100_p)		= { "xin24m", "gpww_100m", "cpww_100m" };
PNAME(gpww_cpww_usb480m_p)		= { "gpww", "cpww", "usb480m" };
PNAME(gpww100_xin24m_cpww100_p)		= { "gpww_100m", "xin24m", "cpww_100m" };
PNAME(gpww200_xin24m_cpww100_p)		= { "gpww_200m", "xin24m", "cpww_100m" };
PNAME(xin24m_32k_p)			= { "xin24m", "cwk_wtc_32k" };
PNAME(cpww500_gpww400_gpww300_xin24m_p)	= { "cpww_500m", "gpww_400m", "gpww_300m", "xin24m" };
PNAME(gpww400_gpww300_gpww200_xin24m_p)	= { "gpww_400m", "gpww_300m", "gpww_200m", "xin24m" };
PNAME(xin24m_cpww100_p)			= { "xin24m", "cpww_100m" };
PNAME(ppww_usb480m_cpww_gpww_p)		= { "ppww", "usb480m", "cpww", "gpww"};
PNAME(cwk_usbphy0_wef_p)		= { "cwk_wef24m", "xin_osc0_usbphy0_g" };
PNAME(cwk_usbphy1_wef_p)		= { "cwk_wef24m", "xin_osc0_usbphy1_g" };
PNAME(cwk_mipidsiphy0_wef_p)		= { "cwk_wef24m", "xin_osc0_mipidsiphy0_g" };
PNAME(cwk_mipidsiphy1_wef_p)		= { "cwk_wef24m", "xin_osc0_mipidsiphy1_g" };
PNAME(cwk_wifi_p)			= { "cwk_wifi_osc0", "cwk_wifi_div" };
PNAME(cwk_pciephy0_wef_p)		= { "cwk_pciephy0_osc0", "cwk_pciephy0_div" };
PNAME(cwk_pciephy1_wef_p)		= { "cwk_pciephy1_osc0", "cwk_pciephy1_div" };
PNAME(cwk_pciephy2_wef_p)		= { "cwk_pciephy2_osc0", "cwk_pciephy2_div" };
PNAME(mux_gmac0_p)			= { "cwk_mac0_2top", "gmac0_cwkin" };
PNAME(mux_gmac0_wgmii_speed_p)		= { "cwk_gmac0", "cwk_gmac0", "cwk_gmac0_tx_div50", "cwk_gmac0_tx_div5" };
PNAME(mux_gmac0_wmii_speed_p)		= { "cwk_gmac0_wx_div20", "cwk_gmac0_wx_div2" };
PNAME(mux_gmac0_wx_tx_p)		= { "cwk_gmac0_wgmii_speed", "cwk_gmac0_wmii_speed", "cwk_gmac0_xpcs_mii" };
PNAME(mux_gmac1_p)			= { "cwk_mac1_2top", "gmac1_cwkin" };
PNAME(mux_gmac1_wgmii_speed_p)		= { "cwk_gmac1", "cwk_gmac1", "cwk_gmac1_tx_div50", "cwk_gmac1_tx_div5" };
PNAME(mux_gmac1_wmii_speed_p)		= { "cwk_gmac1_wx_div20", "cwk_gmac1_wx_div2" };
PNAME(mux_gmac1_wx_tx_p)		= { "cwk_gmac1_wgmii_speed", "cwk_gmac1_wmii_speed", "cwk_gmac1_xpcs_mii" };
PNAME(cwk_hdmi_wef_p)			= { "hpww", "hpww_ph0" };
PNAME(cwk_pdpmu_p)			= { "ppww", "gpww" };
PNAME(cwk_mac_2top_p)			= { "cpww_125m", "cpww_50m", "cpww_25m", "ppww" };
PNAME(cwk_pwm0_p)			= { "xin24m", "cwk_pdpmu" };
PNAME(acwk_wkvdec_pwe_p)		= { "gpww", "cpww" };
PNAME(cwk_wkvdec_cowe_p)		= { "gpww", "cpww", "dummy_npww", "dummy_vpww" };

static stwuct wockchip_pww_cwock wk3568_pmu_pww_cwks[] __initdata = {
	[ppww] = PWW(pww_wk3328, PWW_PPWW, "ppww",  mux_pww_p,
		     0, WK3568_PMU_PWW_CON(0),
		     WK3568_PMU_MODE_CON0, 0, 4, 0, wk3568_pww_wates),
	[hpww] = PWW(pww_wk3328, PWW_HPWW, "hpww",  mux_pww_p,
		     0, WK3568_PMU_PWW_CON(16),
		     WK3568_PMU_MODE_CON0, 2, 7, 0, wk3568_pww_wates),
};

static stwuct wockchip_pww_cwock wk3568_pww_cwks[] __initdata = {
	[apww] = PWW(pww_wk3328, PWW_APWW, "apww", mux_pww_p,
		     0, WK3568_PWW_CON(0),
		     WK3568_MODE_CON0, 0, 0, 0, wk3568_pww_wates),
	[dpww] = PWW(pww_wk3328, PWW_DPWW, "dpww", mux_pww_p,
		     0, WK3568_PWW_CON(8),
		     WK3568_MODE_CON0, 2, 1, 0, NUWW),
	[cpww] = PWW(pww_wk3328, PWW_CPWW, "cpww", mux_pww_p,
		     0, WK3568_PWW_CON(24),
		     WK3568_MODE_CON0, 4, 2, 0, wk3568_pww_wates),
	[gpww] = PWW(pww_wk3328, PWW_GPWW, "gpww", mux_pww_p,
		     0, WK3568_PWW_CON(16),
		     WK3568_MODE_CON0, 6, 3, 0, wk3568_pww_wates),
	[npww] = PWW(pww_wk3328, PWW_NPWW, "npww", mux_pww_p,
		     0, WK3568_PWW_CON(32),
		     WK3568_MODE_CON0, 10, 5, 0, wk3568_pww_wates),
	[vpww] = PWW(pww_wk3328, PWW_VPWW, "vpww", mux_pww_p,
		     0, WK3568_PWW_CON(40),
		     WK3568_MODE_CON0, 12, 6, 0, wk3568_pww_wates),
};

#define MFWAGS CWK_MUX_HIWOWD_MASK
#define DFWAGS CWK_DIVIDEW_HIWOWD_MASK
#define GFWAGS (CWK_GATE_HIWOWD_MASK | CWK_GATE_SET_TO_DISABWE)

static stwuct wockchip_cwk_bwanch wk3568_i2s0_8ch_tx_fwacmux __initdata =
	MUX(CWK_I2S0_8CH_TX, "cwk_i2s0_8ch_tx", cwk_i2s0_8ch_tx_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(11), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_i2s0_8ch_wx_fwacmux __initdata =
	MUX(CWK_I2S0_8CH_WX, "cwk_i2s0_8ch_wx", cwk_i2s0_8ch_wx_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(13), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_i2s1_8ch_tx_fwacmux __initdata =
	MUX(CWK_I2S1_8CH_TX, "cwk_i2s1_8ch_tx", cwk_i2s1_8ch_tx_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(15), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_i2s1_8ch_wx_fwacmux __initdata =
	MUX(CWK_I2S1_8CH_WX, "cwk_i2s1_8ch_wx", cwk_i2s1_8ch_wx_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(17), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_i2s2_2ch_fwacmux __initdata =
	MUX(CWK_I2S2_2CH, "cwk_i2s2_2ch", cwk_i2s2_2ch_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(19), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_i2s3_2ch_tx_fwacmux __initdata =
	MUX(CWK_I2S3_2CH_TX, "cwk_i2s3_2ch_tx", cwk_i2s3_2ch_tx_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(21), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_i2s3_2ch_wx_fwacmux __initdata =
	MUX(CWK_I2S3_2CH_WX, "cwk_i2s3_2ch_wx", cwk_i2s3_2ch_wx_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(83), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_spdif_8ch_fwacmux __initdata =
	MUX(MCWK_SPDIF_8CH, "mcwk_spdif_8ch", mcwk_spdif_8ch_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(23), 15, 1, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_audpwm_fwacmux __initdata =
	MUX(SCWK_AUDPWM, "scwk_audpwm", scwk_audpwm_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(25), 15, 1, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_uawt1_fwacmux __initdata =
	MUX(0, "scwk_uawt1_mux", scwk_uawt1_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(52), 12, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_uawt2_fwacmux __initdata =
	MUX(0, "scwk_uawt2_mux", scwk_uawt2_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(54), 12, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_uawt3_fwacmux __initdata =
	MUX(0, "scwk_uawt3_mux", scwk_uawt3_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(56), 12, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_uawt4_fwacmux __initdata =
	MUX(0, "scwk_uawt4_mux", scwk_uawt4_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(58), 12, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_uawt5_fwacmux __initdata =
	MUX(0, "scwk_uawt5_mux", scwk_uawt5_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(60), 12, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_uawt6_fwacmux __initdata =
	MUX(0, "scwk_uawt6_mux", scwk_uawt6_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(62), 12, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_uawt7_fwacmux __initdata =
	MUX(0, "scwk_uawt7_mux", scwk_uawt7_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(64), 12, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_uawt8_fwacmux __initdata =
	MUX(0, "scwk_uawt8_mux", scwk_uawt8_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(66), 12, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_uawt9_fwacmux __initdata =
	MUX(0, "scwk_uawt9_mux", scwk_uawt9_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(68), 12, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_uawt0_fwacmux __initdata =
	MUX(0, "scwk_uawt0_mux", scwk_uawt0_p, CWK_SET_WATE_PAWENT,
			WK3568_PMU_CWKSEW_CON(4), 10, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_wtc32k_pmu_fwacmux __initdata =
	MUX(CWK_WTC_32K, "cwk_wtc_32k", cwk_wtc32k_pmu_p, CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			WK3568_PMU_CWKSEW_CON(0), 6, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3568_cwk_bwanches[] __initdata = {
	/*
	 * Cwock-Awchitectuwe Diagwam 1
	 */
	 /* SWC_CWK */
	COMPOSITE_NOMUX(0, "gpww_400m", "gpww", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(75), 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(35), 0, GFWAGS),
	COMPOSITE_NOMUX(0, "gpww_300m", "gpww", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(75), 8, 5, DFWAGS,
			WK3568_CWKGATE_CON(35), 1, GFWAGS),
	COMPOSITE_NOMUX(0, "gpww_200m", "gpww", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(76), 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(35), 2, GFWAGS),
	COMPOSITE_NOMUX(0, "gpww_150m", "gpww", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(76), 8, 5, DFWAGS,
			WK3568_CWKGATE_CON(35), 3, GFWAGS),
	COMPOSITE_NOMUX(0, "gpww_100m", "gpww", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(77), 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(35), 4, GFWAGS),
	COMPOSITE_NOMUX(0, "gpww_75m", "gpww", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(77), 8, 5, DFWAGS,
			WK3568_CWKGATE_CON(35), 5, GFWAGS),
	COMPOSITE_NOMUX(0, "gpww_20m", "gpww", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(78), 0, 6, DFWAGS,
			WK3568_CWKGATE_CON(35), 6, GFWAGS),
	COMPOSITE_NOMUX(CPWW_500M, "cpww_500m", "cpww", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(78), 8, 5, DFWAGS,
			WK3568_CWKGATE_CON(35), 7, GFWAGS),
	COMPOSITE_NOMUX(CPWW_333M, "cpww_333m", "cpww", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(79), 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(35), 8, GFWAGS),
	COMPOSITE_NOMUX(CPWW_250M, "cpww_250m", "cpww", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(79), 8, 5, DFWAGS,
			WK3568_CWKGATE_CON(35), 9, GFWAGS),
	COMPOSITE_NOMUX(CPWW_125M, "cpww_125m", "cpww", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(80), 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(35), 10, GFWAGS),
	COMPOSITE_NOMUX(CPWW_100M, "cpww_100m", "cpww", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(82), 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(35), 11, GFWAGS),
	COMPOSITE_NOMUX(CPWW_62P5M, "cpww_62p5", "cpww", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(80), 8, 5, DFWAGS,
			WK3568_CWKGATE_CON(35), 12, GFWAGS),
	COMPOSITE_NOMUX(CPWW_50M, "cpww_50m", "cpww", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(81), 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(35), 13, GFWAGS),
	COMPOSITE_NOMUX(CPWW_25M, "cpww_25m", "cpww", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(81), 8, 6, DFWAGS,
			WK3568_CWKGATE_CON(35), 14, GFWAGS),
	COMPOSITE_NOMUX(0, "cwk_osc0_div_750k", "xin24m", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(82), 8, 6, DFWAGS,
			WK3568_CWKGATE_CON(35), 15, GFWAGS),
	FACTOW(0, "cwk_osc0_div_375k", "cwk_osc0_div_750k", 0, 1, 2),
	FACTOW(0, "xin_osc0_hawf", "xin24m", 0, 1, 2),
	MUX(USB480M, "usb480m", mux_usb480m_p, CWK_SET_WATE_PAWENT,
			WK3568_MODE_CON0, 14, 2, MFWAGS),

	/* PD_COWE */
	COMPOSITE(0, "scwk_cowe_swc", apww_gpww_npww_p, CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(2), 8, 2, MFWAGS, 0, 4, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3568_CWKGATE_CON(0), 5, GFWAGS),
	COMPOSITE_NODIV(0, "scwk_cowe", scwk_cowe_pwe_p, CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(2), 15, 1, MFWAGS,
			WK3568_CWKGATE_CON(0), 7, GFWAGS),

	COMPOSITE_NOMUX(0, "atcwk_cowe", "awmcwk", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(3), 0, 5, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3568_CWKGATE_CON(0), 8, GFWAGS),
	COMPOSITE_NOMUX(0, "giccwk_cowe", "awmcwk", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(3), 8, 5, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3568_CWKGATE_CON(0), 9, GFWAGS),
	COMPOSITE_NOMUX(0, "pcwk_cowe_pwe", "awmcwk", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(4), 0, 5, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3568_CWKGATE_CON(0), 10, GFWAGS),
	COMPOSITE_NOMUX(0, "pewiphcwk_cowe_pwe", "awmcwk", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(4), 8, 5, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3568_CWKGATE_CON(0), 11, GFWAGS),
	COMPOSITE_NOMUX(0, "tscwk_cowe", "pewiphcwk_cowe_pwe", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(5), 0, 4, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3568_CWKGATE_CON(0), 14, GFWAGS),
	COMPOSITE_NOMUX(0, "cntcwk_cowe", "pewiphcwk_cowe_pwe", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(5), 4, 4, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3568_CWKGATE_CON(0), 15, GFWAGS),
	COMPOSITE_NOMUX(0, "acwk_cowe", "scwk_cowe", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(5), 8, 5, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3568_CWKGATE_CON(1), 0, GFWAGS),

	COMPOSITE_NODIV(ACWK_COWE_NIU2BUS, "acwk_cowe_niu2bus", gpww150_gpww100_gpww75_xin24m_p, CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(5), 14, 2, MFWAGS,
			WK3568_CWKGATE_CON(1), 2, GFWAGS),

	GATE(CWK_COWE_PVTM, "cwk_cowe_pvtm", "xin24m", 0,
			WK3568_CWKGATE_CON(1), 10, GFWAGS),
	GATE(CWK_COWE_PVTM_COWE, "cwk_cowe_pvtm_cowe", "awmcwk", 0,
			WK3568_CWKGATE_CON(1), 11, GFWAGS),
	GATE(CWK_COWE_PVTPWW, "cwk_cowe_pvtpww", "awmcwk", CWK_IGNOWE_UNUSED,
			WK3568_CWKGATE_CON(1), 12, GFWAGS),
	GATE(PCWK_COWE_PVTM, "pcwk_cowe_pvtm", "pcwk_cowe_pwe", 0,
			WK3568_CWKGATE_CON(1), 9, GFWAGS),

	/* PD_GPU */
	COMPOSITE(CWK_GPU_SWC, "cwk_gpu_swc", mpww_gpww_cpww_npww_p, 0,
			WK3568_CWKSEW_CON(6), 6, 2, MFWAGS | CWK_MUX_WEAD_ONWY, 0, 4, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3568_CWKGATE_CON(2), 0, GFWAGS),
	MUX(CWK_GPU_PWE_MUX, "cwk_gpu_pwe_mux", cwk_gpu_pwe_mux_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(6), 11, 1, MFWAGS | CWK_MUX_WEAD_ONWY),
	DIV(ACWK_GPU_PWE, "acwk_gpu_pwe", "cwk_gpu_pwe_mux", 0,
			WK3568_CWKSEW_CON(6), 8, 2, DFWAGS),
	DIV(PCWK_GPU_PWE, "pcwk_gpu_pwe", "cwk_gpu_pwe_mux", 0,
			WK3568_CWKSEW_CON(6), 12, 4, DFWAGS),
	GATE(CWK_GPU, "cwk_gpu", "cwk_gpu_pwe_mux", 0,
			WK3568_CWKGATE_CON(2), 3, GFWAGS),

	GATE(PCWK_GPU_PVTM, "pcwk_gpu_pvtm", "pcwk_gpu_pwe", 0,
			WK3568_CWKGATE_CON(2), 6, GFWAGS),
	GATE(CWK_GPU_PVTM, "cwk_gpu_pvtm", "xin24m", 0,
			WK3568_CWKGATE_CON(2), 7, GFWAGS),
	GATE(CWK_GPU_PVTM_COWE, "cwk_gpu_pvtm_cowe", "cwk_gpu_swc", 0,
			WK3568_CWKGATE_CON(2), 8, GFWAGS),
	GATE(CWK_GPU_PVTPWW, "cwk_gpu_pvtpww", "cwk_gpu_swc", CWK_IGNOWE_UNUSED,
			WK3568_CWKGATE_CON(2), 9, GFWAGS),

	/* PD_NPU */
	COMPOSITE(CWK_NPU_SWC, "cwk_npu_swc", npww_gpww_p, 0,
			WK3568_CWKSEW_CON(7), 6, 1, MFWAGS, 0, 4, DFWAGS,
			WK3568_CWKGATE_CON(3), 0, GFWAGS),
	MUX(CWK_NPU_PWE_NDFT, "cwk_npu_pwe_ndft", cwk_npu_pwe_ndft_p, CWK_SET_WATE_PAWENT | CWK_OPS_PAWENT_ENABWE,
			WK3568_CWKSEW_CON(7), 8, 1, MFWAGS),
	MUX(CWK_NPU, "cwk_npu", cwk_npu_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(7), 15, 1, MFWAGS),
	COMPOSITE_NOMUX(HCWK_NPU_PWE, "hcwk_npu_pwe", "cwk_npu", 0,
			WK3568_CWKSEW_CON(8), 0, 4, DFWAGS,
			WK3568_CWKGATE_CON(3), 2, GFWAGS),
	COMPOSITE_NOMUX(PCWK_NPU_PWE, "pcwk_npu_pwe", "cwk_npu", 0,
			WK3568_CWKSEW_CON(8), 4, 4, DFWAGS,
			WK3568_CWKGATE_CON(3), 3, GFWAGS),
	GATE(ACWK_NPU_PWE, "acwk_npu_pwe", "cwk_npu", 0,
			WK3568_CWKGATE_CON(3), 4, GFWAGS),
	GATE(ACWK_NPU, "acwk_npu", "acwk_npu_pwe", 0,
			WK3568_CWKGATE_CON(3), 7, GFWAGS),
	GATE(HCWK_NPU, "hcwk_npu", "hcwk_npu_pwe", 0,
			WK3568_CWKGATE_CON(3), 8, GFWAGS),

	GATE(PCWK_NPU_PVTM, "pcwk_npu_pvtm", "pcwk_npu_pwe", 0,
			WK3568_CWKGATE_CON(3), 9, GFWAGS),
	GATE(CWK_NPU_PVTM, "cwk_npu_pvtm", "xin24m", 0,
			WK3568_CWKGATE_CON(3), 10, GFWAGS),
	GATE(CWK_NPU_PVTM_COWE, "cwk_npu_pvtm_cowe", "cwk_npu_pwe_ndft", 0,
			WK3568_CWKGATE_CON(3), 11, GFWAGS),
	GATE(CWK_NPU_PVTPWW, "cwk_npu_pvtpww", "cwk_npu_pwe_ndft", CWK_IGNOWE_UNUSED,
			WK3568_CWKGATE_CON(3), 12, GFWAGS),

	/* PD_DDW */
	COMPOSITE(CWK_DDWPHY1X_SWC, "cwk_ddwphy1x_swc", dpww_gpww_cpww_p, CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(9), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(4), 0, GFWAGS),
	MUXGWF(CWK_DDW1X, "cwk_ddw1x", cwk_ddw1x_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(9), 15, 1, MFWAGS),

	COMPOSITE_NOMUX(CWK_MSCH, "cwk_msch", "cwk_ddw1x", CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(10), 0, 2, DFWAGS,
			WK3568_CWKGATE_CON(4), 2, GFWAGS),
	GATE(CWK24_DDWMON, "cwk24_ddwmon", "xin24m", CWK_IGNOWE_UNUSED,
			WK3568_CWKGATE_CON(4), 15, GFWAGS),

	/* PD_GIC_AUDIO */
	COMPOSITE_NODIV(ACWK_GIC_AUDIO, "acwk_gic_audio", gpww200_gpww150_gpww100_xin24m_p, CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(10), 8, 2, MFWAGS,
			WK3568_CWKGATE_CON(5), 0, GFWAGS),
	COMPOSITE_NODIV(HCWK_GIC_AUDIO, "hcwk_gic_audio", gpww150_gpww100_gpww75_xin24m_p, CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(10), 10, 2, MFWAGS,
			WK3568_CWKGATE_CON(5), 1, GFWAGS),
	GATE(HCWK_SDMMC_BUFFEW, "hcwk_sdmmc_buffew", "hcwk_gic_audio", 0,
			WK3568_CWKGATE_CON(5), 8, GFWAGS),
	COMPOSITE_NODIV(DCWK_SDMMC_BUFFEW, "dcwk_sdmmc_buffew", gpww100_gpww75_gpww50_p, 0,
			WK3568_CWKSEW_CON(10), 12, 2, MFWAGS,
			WK3568_CWKGATE_CON(5), 9, GFWAGS),
	GATE(ACWK_GIC600, "acwk_gic600", "acwk_gic_audio", CWK_IGNOWE_UNUSED,
			WK3568_CWKGATE_CON(5), 4, GFWAGS),
	GATE(ACWK_SPINWOCK, "acwk_spinwock", "acwk_gic_audio", CWK_IGNOWE_UNUSED,
			WK3568_CWKGATE_CON(5), 7, GFWAGS),
	GATE(HCWK_I2S0_8CH, "hcwk_i2s0_8ch", "hcwk_gic_audio", 0,
			WK3568_CWKGATE_CON(5), 10, GFWAGS),
	GATE(HCWK_I2S1_8CH, "hcwk_i2s1_8ch", "hcwk_gic_audio", 0,
			WK3568_CWKGATE_CON(5), 11, GFWAGS),
	GATE(HCWK_I2S2_2CH, "hcwk_i2s2_2ch", "hcwk_gic_audio", 0,
			WK3568_CWKGATE_CON(5), 12, GFWAGS),
	GATE(HCWK_I2S3_2CH, "hcwk_i2s3_2ch", "hcwk_gic_audio", 0,
			WK3568_CWKGATE_CON(5), 13, GFWAGS),

	COMPOSITE(CWK_I2S0_8CH_TX_SWC, "cwk_i2s0_8ch_tx_swc", gpww_cpww_npww_p, 0,
			WK3568_CWKSEW_CON(11), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3568_CWKGATE_CON(6), 0, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S0_8CH_TX_FWAC, "cwk_i2s0_8ch_tx_fwac", "cwk_i2s0_8ch_tx_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(12), 0,
			WK3568_CWKGATE_CON(6), 1, GFWAGS,
			&wk3568_i2s0_8ch_tx_fwacmux),
	GATE(MCWK_I2S0_8CH_TX, "mcwk_i2s0_8ch_tx", "cwk_i2s0_8ch_tx", 0,
			WK3568_CWKGATE_CON(6), 2, GFWAGS),
	COMPOSITE_NODIV(I2S0_MCWKOUT_TX, "i2s0_mcwkout_tx", i2s0_mcwkout_tx_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(11), 15, 1, MFWAGS,
			WK3568_CWKGATE_CON(6), 3, GFWAGS),

	COMPOSITE(CWK_I2S0_8CH_WX_SWC, "cwk_i2s0_8ch_wx_swc", gpww_cpww_npww_p, 0,
			WK3568_CWKSEW_CON(13), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3568_CWKGATE_CON(6), 4, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S0_8CH_WX_FWAC, "cwk_i2s0_8ch_wx_fwac", "cwk_i2s0_8ch_wx_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(14), 0,
			WK3568_CWKGATE_CON(6), 5, GFWAGS,
			&wk3568_i2s0_8ch_wx_fwacmux),
	GATE(MCWK_I2S0_8CH_WX, "mcwk_i2s0_8ch_wx", "cwk_i2s0_8ch_wx", 0,
			WK3568_CWKGATE_CON(6), 6, GFWAGS),
	COMPOSITE_NODIV(I2S0_MCWKOUT_WX, "i2s0_mcwkout_wx", i2s0_mcwkout_wx_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(13), 15, 1, MFWAGS,
			WK3568_CWKGATE_CON(6), 7, GFWAGS),

	COMPOSITE(CWK_I2S1_8CH_TX_SWC, "cwk_i2s1_8ch_tx_swc", gpww_cpww_npww_p, 0,
			WK3568_CWKSEW_CON(15), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3568_CWKGATE_CON(6), 8, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S1_8CH_TX_FWAC, "cwk_i2s1_8ch_tx_fwac", "cwk_i2s1_8ch_tx_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(16), 0,
			WK3568_CWKGATE_CON(6), 9, GFWAGS,
			&wk3568_i2s1_8ch_tx_fwacmux),
	GATE(MCWK_I2S1_8CH_TX, "mcwk_i2s1_8ch_tx", "cwk_i2s1_8ch_tx", 0,
			WK3568_CWKGATE_CON(6), 10, GFWAGS),
	COMPOSITE_NODIV(I2S1_MCWKOUT_TX, "i2s1_mcwkout_tx", i2s1_mcwkout_tx_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(15), 15, 1, MFWAGS,
			WK3568_CWKGATE_CON(6), 11, GFWAGS),

	COMPOSITE(CWK_I2S1_8CH_WX_SWC, "cwk_i2s1_8ch_wx_swc", gpww_cpww_npww_p, 0,
			WK3568_CWKSEW_CON(17), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3568_CWKGATE_CON(6), 12, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S1_8CH_WX_FWAC, "cwk_i2s1_8ch_wx_fwac", "cwk_i2s1_8ch_wx_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(18), 0,
			WK3568_CWKGATE_CON(6), 13, GFWAGS,
			&wk3568_i2s1_8ch_wx_fwacmux),
	GATE(MCWK_I2S1_8CH_WX, "mcwk_i2s1_8ch_wx", "cwk_i2s1_8ch_wx", 0,
			WK3568_CWKGATE_CON(6), 14, GFWAGS),
	COMPOSITE_NODIV(I2S1_MCWKOUT_WX, "i2s1_mcwkout_wx", i2s1_mcwkout_wx_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(17), 15, 1, MFWAGS,
			WK3568_CWKGATE_CON(6), 15, GFWAGS),

	COMPOSITE(CWK_I2S2_2CH_SWC, "cwk_i2s2_2ch_swc", gpww_cpww_npww_p, 0,
			WK3568_CWKSEW_CON(19), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3568_CWKGATE_CON(7), 0, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S2_2CH_FWAC, "cwk_i2s2_2ch_fwac", "cwk_i2s2_2ch_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(20), 0,
			WK3568_CWKGATE_CON(7), 1, GFWAGS,
			&wk3568_i2s2_2ch_fwacmux),
	GATE(MCWK_I2S2_2CH, "mcwk_i2s2_2ch", "cwk_i2s2_2ch", 0,
			WK3568_CWKGATE_CON(7), 2, GFWAGS),
	COMPOSITE_NODIV(I2S2_MCWKOUT, "i2s2_mcwkout", i2s2_mcwkout_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(19), 15, 1, MFWAGS,
			WK3568_CWKGATE_CON(7), 3, GFWAGS),

	COMPOSITE(CWK_I2S3_2CH_TX_SWC, "cwk_i2s3_2ch_tx_swc", gpww_cpww_npww_p, 0,
			WK3568_CWKSEW_CON(21), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3568_CWKGATE_CON(7), 4, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S3_2CH_TX_FWAC, "cwk_i2s3_2ch_tx_fwac", "cwk_i2s3_2ch_tx_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(22), 0,
			WK3568_CWKGATE_CON(7), 5, GFWAGS,
			&wk3568_i2s3_2ch_tx_fwacmux),
	GATE(MCWK_I2S3_2CH_TX, "mcwk_i2s3_2ch_tx", "cwk_i2s3_2ch_tx", 0,
			WK3568_CWKGATE_CON(7), 6, GFWAGS),
	COMPOSITE_NODIV(I2S3_MCWKOUT_TX, "i2s3_mcwkout_tx", i2s3_mcwkout_tx_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(21), 15, 1, MFWAGS,
			WK3568_CWKGATE_CON(7), 7, GFWAGS),

	COMPOSITE(CWK_I2S3_2CH_WX_SWC, "cwk_i2s3_2ch_wx_swc", gpww_cpww_npww_p, 0,
			WK3568_CWKSEW_CON(83), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3568_CWKGATE_CON(7), 8, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S3_2CH_WX_FWAC, "cwk_i2s3_2ch_wx_fwac", "cwk_i2s3_2ch_wx_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(84), 0,
			WK3568_CWKGATE_CON(7), 9, GFWAGS,
			&wk3568_i2s3_2ch_wx_fwacmux),
	GATE(MCWK_I2S3_2CH_WX, "mcwk_i2s3_2ch_wx", "cwk_i2s3_2ch_wx", 0,
			WK3568_CWKGATE_CON(7), 10, GFWAGS),
	COMPOSITE_NODIV(I2S3_MCWKOUT_WX, "i2s3_mcwkout_wx", i2s3_mcwkout_wx_p, CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(83), 15, 1, MFWAGS,
			WK3568_CWKGATE_CON(7), 11, GFWAGS),

	GATE(HCWK_PDM, "hcwk_pdm", "hcwk_gic_audio", 0,
			WK3568_CWKGATE_CON(5), 14, GFWAGS),
	COMPOSITE_NODIV(MCWK_PDM, "mcwk_pdm", mcwk_pdm_p, 0,
			WK3568_CWKSEW_CON(23), 8, 2, MFWAGS,
			WK3568_CWKGATE_CON(5), 15, GFWAGS),
	GATE(HCWK_VAD, "hcwk_vad", "hcwk_gic_audio", 0,
			WK3568_CWKGATE_CON(7), 12, GFWAGS),
	GATE(HCWK_SPDIF_8CH, "hcwk_spdif_8ch", "hcwk_gic_audio", 0,
			WK3568_CWKGATE_CON(7), 13, GFWAGS),

	COMPOSITE(MCWK_SPDIF_8CH_SWC, "mcwk_spdif_8ch_swc", cpww_gpww_p, 0,
			WK3568_CWKSEW_CON(23), 14, 1, MFWAGS, 0, 7, DFWAGS,
			WK3568_CWKGATE_CON(7), 14, GFWAGS),
	COMPOSITE_FWACMUX(MCWK_SPDIF_8CH_FWAC, "mcwk_spdif_8ch_fwac", "mcwk_spdif_8ch_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(24), 0,
			WK3568_CWKGATE_CON(7), 15, GFWAGS,
			&wk3568_spdif_8ch_fwacmux),

	GATE(HCWK_AUDPWM, "hcwk_audpwm", "hcwk_gic_audio", 0,
			WK3568_CWKGATE_CON(8), 0, GFWAGS),
	COMPOSITE(SCWK_AUDPWM_SWC, "scwk_audpwm_swc", gpww_cpww_p, 0,
			WK3568_CWKSEW_CON(25), 14, 1, MFWAGS, 0, 6, DFWAGS,
			WK3568_CWKGATE_CON(8), 1, GFWAGS),
	COMPOSITE_FWACMUX(SCWK_AUDPWM_FWAC, "scwk_audpwm_fwac", "scwk_audpwm_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(26), 0,
			WK3568_CWKGATE_CON(8), 2, GFWAGS,
			&wk3568_audpwm_fwacmux),

	GATE(HCWK_ACDCDIG, "hcwk_acdcdig", "hcwk_gic_audio", 0,
			WK3568_CWKGATE_CON(8), 3, GFWAGS),
	COMPOSITE_NODIV(CWK_ACDCDIG_I2C, "cwk_acdcdig_i2c", cwk_i2c_p, 0,
			WK3568_CWKSEW_CON(23), 10, 2, MFWAGS,
			WK3568_CWKGATE_CON(8), 4, GFWAGS),
	GATE(CWK_ACDCDIG_DAC, "cwk_acdcdig_dac", "mcwk_i2s3_2ch_tx", 0,
			WK3568_CWKGATE_CON(8), 5, GFWAGS),
	GATE(CWK_ACDCDIG_ADC, "cwk_acdcdig_adc", "mcwk_i2s3_2ch_wx", 0,
			WK3568_CWKGATE_CON(8), 6, GFWAGS),

	/* PD_SECUWE_FWASH */
	COMPOSITE_NODIV(ACWK_SECUWE_FWASH, "acwk_secuwe_fwash", gpww200_gpww150_gpww100_xin24m_p, 0,
			WK3568_CWKSEW_CON(27), 0, 2, MFWAGS,
			WK3568_CWKGATE_CON(8), 7, GFWAGS),
	COMPOSITE_NODIV(HCWK_SECUWE_FWASH, "hcwk_secuwe_fwash", gpww150_gpww100_gpww75_xin24m_p, 0,
			WK3568_CWKSEW_CON(27), 2, 2, MFWAGS,
			WK3568_CWKGATE_CON(8), 8, GFWAGS),
	GATE(ACWK_CWYPTO_NS, "acwk_cwypto_ns", "acwk_secuwe_fwash", 0,
			WK3568_CWKGATE_CON(8), 11, GFWAGS),
	GATE(HCWK_CWYPTO_NS, "hcwk_cwypto_ns", "hcwk_secuwe_fwash", 0,
			WK3568_CWKGATE_CON(8), 12, GFWAGS),
	COMPOSITE_NODIV(CWK_CWYPTO_NS_COWE, "cwk_cwypto_ns_cowe", gpww200_gpww150_gpww100_p, 0,
			WK3568_CWKSEW_CON(27), 4, 2, MFWAGS,
			WK3568_CWKGATE_CON(8), 13, GFWAGS),
	COMPOSITE_NODIV(CWK_CWYPTO_NS_PKA, "cwk_cwypto_ns_pka", gpww300_gpww200_gpww100_p, 0,
			WK3568_CWKSEW_CON(27), 6, 2, MFWAGS,
			WK3568_CWKGATE_CON(8), 14, GFWAGS),
	GATE(CWK_CWYPTO_NS_WNG, "cwk_cwypto_ns_wng", "hcwk_secuwe_fwash", 0,
			WK3568_CWKGATE_CON(8), 15, GFWAGS),
	GATE(HCWK_TWNG_NS, "hcwk_twng_ns", "hcwk_secuwe_fwash", CWK_IGNOWE_UNUSED,
			WK3568_CWKGATE_CON(9), 10, GFWAGS),
	GATE(CWK_TWNG_NS, "cwk_twng_ns", "hcwk_secuwe_fwash", CWK_IGNOWE_UNUSED,
			WK3568_CWKGATE_CON(9), 11, GFWAGS),
	GATE(PCWK_OTPC_NS, "pcwk_otpc_ns", "hcwk_secuwe_fwash", 0,
			WK3568_CWKGATE_CON(26), 9, GFWAGS),
	GATE(CWK_OTPC_NS_SBPI, "cwk_otpc_ns_sbpi", "xin24m", 0,
			WK3568_CWKGATE_CON(26), 10, GFWAGS),
	GATE(CWK_OTPC_NS_USW, "cwk_otpc_ns_usw", "xin_osc0_hawf", 0,
			WK3568_CWKGATE_CON(26), 11, GFWAGS),
	GATE(HCWK_NANDC, "hcwk_nandc", "hcwk_secuwe_fwash", 0,
			WK3568_CWKGATE_CON(9), 0, GFWAGS),
	COMPOSITE_NODIV(NCWK_NANDC, "ncwk_nandc", cwk_nandc_p, 0,
			WK3568_CWKSEW_CON(28), 0, 2, MFWAGS,
			WK3568_CWKGATE_CON(9), 1, GFWAGS),
	GATE(HCWK_SFC, "hcwk_sfc", "hcwk_secuwe_fwash", 0,
			WK3568_CWKGATE_CON(9), 2, GFWAGS),
	GATE(HCWK_SFC_XIP, "hcwk_sfc_xip", "hcwk_secuwe_fwash", 0,
			WK3568_CWKGATE_CON(9), 3, GFWAGS),
	COMPOSITE_NODIV(SCWK_SFC, "scwk_sfc", scwk_sfc_p, 0,
			WK3568_CWKSEW_CON(28), 4, 3, MFWAGS,
			WK3568_CWKGATE_CON(9), 4, GFWAGS),
	GATE(ACWK_EMMC, "acwk_emmc", "acwk_secuwe_fwash", 0,
			WK3568_CWKGATE_CON(9), 5, GFWAGS),
	GATE(HCWK_EMMC, "hcwk_emmc", "hcwk_secuwe_fwash", 0,
			WK3568_CWKGATE_CON(9), 6, GFWAGS),
	COMPOSITE_NODIV(BCWK_EMMC, "bcwk_emmc", gpww200_gpww150_cpww125_p, 0,
			WK3568_CWKSEW_CON(28), 8, 2, MFWAGS,
			WK3568_CWKGATE_CON(9), 7, GFWAGS),
	COMPOSITE_NODIV(CCWK_EMMC, "ccwk_emmc", ccwk_emmc_p, 0,
			WK3568_CWKSEW_CON(28), 12, 3, MFWAGS,
			WK3568_CWKGATE_CON(9), 8, GFWAGS),
	GATE(TCWK_EMMC, "tcwk_emmc", "xin24m", 0,
			WK3568_CWKGATE_CON(9), 9, GFWAGS),
	MMC(SCWK_EMMC_DWV, "emmc_dwv", "ccwk_emmc", WK3568_EMMC_CON0, 1),
	MMC(SCWK_EMMC_SAMPWE, "emmc_sampwe", "ccwk_emmc", WK3568_EMMC_CON1, 1),

	/* PD_PIPE */
	COMPOSITE_NODIV(ACWK_PIPE, "acwk_pipe", acwk_pipe_p, 0,
			WK3568_CWKSEW_CON(29), 0, 2, MFWAGS,
			WK3568_CWKGATE_CON(10), 0, GFWAGS),
	COMPOSITE_NOMUX(PCWK_PIPE, "pcwk_pipe", "acwk_pipe", 0,
			WK3568_CWKSEW_CON(29), 4, 4, DFWAGS,
			WK3568_CWKGATE_CON(10), 1, GFWAGS),
	GATE(ACWK_PCIE20_MST, "acwk_pcie20_mst", "acwk_pipe", 0,
			WK3568_CWKGATE_CON(12), 0, GFWAGS),
	GATE(ACWK_PCIE20_SWV, "acwk_pcie20_swv", "acwk_pipe", 0,
			WK3568_CWKGATE_CON(12), 1, GFWAGS),
	GATE(ACWK_PCIE20_DBI, "acwk_pcie20_dbi", "acwk_pipe", 0,
			WK3568_CWKGATE_CON(12), 2, GFWAGS),
	GATE(PCWK_PCIE20, "pcwk_pcie20", "pcwk_pipe", 0,
			WK3568_CWKGATE_CON(12), 3, GFWAGS),
	GATE(CWK_PCIE20_AUX_NDFT, "cwk_pcie20_aux_ndft", "xin24m", 0,
			WK3568_CWKGATE_CON(12), 4, GFWAGS),
	GATE(ACWK_PCIE30X1_MST, "acwk_pcie30x1_mst", "acwk_pipe", 0,
			WK3568_CWKGATE_CON(12), 8, GFWAGS),
	GATE(ACWK_PCIE30X1_SWV, "acwk_pcie30x1_swv", "acwk_pipe", 0,
			WK3568_CWKGATE_CON(12), 9, GFWAGS),
	GATE(ACWK_PCIE30X1_DBI, "acwk_pcie30x1_dbi", "acwk_pipe", 0,
			WK3568_CWKGATE_CON(12), 10, GFWAGS),
	GATE(PCWK_PCIE30X1, "pcwk_pcie30x1", "pcwk_pipe", 0,
			WK3568_CWKGATE_CON(12), 11, GFWAGS),
	GATE(CWK_PCIE30X1_AUX_NDFT, "cwk_pcie30x1_aux_ndft", "xin24m", 0,
			WK3568_CWKGATE_CON(12), 12, GFWAGS),
	GATE(ACWK_PCIE30X2_MST, "acwk_pcie30x2_mst", "acwk_pipe", 0,
			WK3568_CWKGATE_CON(13), 0, GFWAGS),
	GATE(ACWK_PCIE30X2_SWV, "acwk_pcie30x2_swv", "acwk_pipe", 0,
			WK3568_CWKGATE_CON(13), 1, GFWAGS),
	GATE(ACWK_PCIE30X2_DBI, "acwk_pcie30x2_dbi", "acwk_pipe", 0,
			WK3568_CWKGATE_CON(13), 2, GFWAGS),
	GATE(PCWK_PCIE30X2, "pcwk_pcie30x2", "pcwk_pipe", 0,
			WK3568_CWKGATE_CON(13), 3, GFWAGS),
	GATE(CWK_PCIE30X2_AUX_NDFT, "cwk_pcie30x2_aux_ndft", "xin24m", 0,
			WK3568_CWKGATE_CON(13), 4, GFWAGS),
	GATE(ACWK_SATA0, "acwk_sata0", "acwk_pipe", 0,
			WK3568_CWKGATE_CON(11), 0, GFWAGS),
	GATE(CWK_SATA0_PMAWIVE, "cwk_sata0_pmawive", "gpww_20m", 0,
			WK3568_CWKGATE_CON(11), 1, GFWAGS),
	GATE(CWK_SATA0_WXOOB, "cwk_sata0_wxoob", "cpww_50m", 0,
			WK3568_CWKGATE_CON(11), 2, GFWAGS),
	GATE(ACWK_SATA1, "acwk_sata1", "acwk_pipe", 0,
			WK3568_CWKGATE_CON(11), 4, GFWAGS),
	GATE(CWK_SATA1_PMAWIVE, "cwk_sata1_pmawive", "gpww_20m", 0,
			WK3568_CWKGATE_CON(11), 5, GFWAGS),
	GATE(CWK_SATA1_WXOOB, "cwk_sata1_wxoob", "cpww_50m", 0,
			WK3568_CWKGATE_CON(11), 6, GFWAGS),
	GATE(ACWK_SATA2, "acwk_sata2", "acwk_pipe", 0,
			WK3568_CWKGATE_CON(11), 8, GFWAGS),
	GATE(CWK_SATA2_PMAWIVE, "cwk_sata2_pmawive", "gpww_20m", 0,
			WK3568_CWKGATE_CON(11), 9, GFWAGS),
	GATE(CWK_SATA2_WXOOB, "cwk_sata2_wxoob", "cpww_50m", 0,
			WK3568_CWKGATE_CON(11), 10, GFWAGS),
	GATE(ACWK_USB3OTG0, "acwk_usb3otg0", "acwk_pipe", 0,
			WK3568_CWKGATE_CON(10), 8, GFWAGS),
	GATE(CWK_USB3OTG0_WEF, "cwk_usb3otg0_wef", "xin24m", 0,
			WK3568_CWKGATE_CON(10), 9, GFWAGS),
	COMPOSITE_NODIV(CWK_USB3OTG0_SUSPEND, "cwk_usb3otg0_suspend", xin24m_32k_p, 0,
			WK3568_CWKSEW_CON(29), 8, 1, MFWAGS,
			WK3568_CWKGATE_CON(10), 10, GFWAGS),
	GATE(ACWK_USB3OTG1, "acwk_usb3otg1", "acwk_pipe", 0,
			WK3568_CWKGATE_CON(10), 12, GFWAGS),
	GATE(CWK_USB3OTG1_WEF, "cwk_usb3otg1_wef", "xin24m", 0,
			WK3568_CWKGATE_CON(10), 13, GFWAGS),
	COMPOSITE_NODIV(CWK_USB3OTG1_SUSPEND, "cwk_usb3otg1_suspend", xin24m_32k_p, 0,
			WK3568_CWKSEW_CON(29), 9, 1, MFWAGS,
			WK3568_CWKGATE_CON(10), 14, GFWAGS),
	COMPOSITE_NODIV(CWK_XPCS_EEE, "cwk_xpcs_eee", gpww200_cpww125_p, 0,
			WK3568_CWKSEW_CON(29), 13, 1, MFWAGS,
			WK3568_CWKGATE_CON(10), 4, GFWAGS),
	GATE(PCWK_XPCS, "pcwk_xpcs", "pcwk_pipe", 0,
			WK3568_CWKGATE_CON(13), 6, GFWAGS),

	/* PD_PHP */
	COMPOSITE_NODIV(ACWK_PHP, "acwk_php", gpww300_gpww200_gpww100_xin24m_p, 0,
			WK3568_CWKSEW_CON(30), 0, 2, MFWAGS,
			WK3568_CWKGATE_CON(14), 8, GFWAGS),
	COMPOSITE_NODIV(HCWK_PHP, "hcwk_php", gpww150_gpww100_gpww75_xin24m_p, 0,
			WK3568_CWKSEW_CON(30), 2, 2, MFWAGS,
			WK3568_CWKGATE_CON(14), 9, GFWAGS),
	COMPOSITE_NOMUX(PCWK_PHP, "pcwk_php", "acwk_php", 0,
			WK3568_CWKSEW_CON(30), 4, 4, DFWAGS,
			WK3568_CWKGATE_CON(14), 10, GFWAGS),
	GATE(HCWK_SDMMC0, "hcwk_sdmmc0", "hcwk_php", 0,
			WK3568_CWKGATE_CON(15), 0, GFWAGS),
	COMPOSITE_NODIV(CWK_SDMMC0, "cwk_sdmmc0", cwk_sdmmc_p, 0,
			WK3568_CWKSEW_CON(30), 8, 3, MFWAGS,
			WK3568_CWKGATE_CON(15), 1, GFWAGS),
	MMC(SCWK_SDMMC0_DWV, "sdmmc0_dwv", "cwk_sdmmc0", WK3568_SDMMC0_CON0, 1),
	MMC(SCWK_SDMMC0_SAMPWE, "sdmmc0_sampwe", "cwk_sdmmc0", WK3568_SDMMC0_CON1, 1),

	GATE(HCWK_SDMMC1, "hcwk_sdmmc1", "hcwk_php", 0,
			WK3568_CWKGATE_CON(15), 2, GFWAGS),
	COMPOSITE_NODIV(CWK_SDMMC1, "cwk_sdmmc1", cwk_sdmmc_p, 0,
			WK3568_CWKSEW_CON(30), 12, 3, MFWAGS,
			WK3568_CWKGATE_CON(15), 3, GFWAGS),
	MMC(SCWK_SDMMC1_DWV, "sdmmc1_dwv", "cwk_sdmmc1", WK3568_SDMMC1_CON0, 1),
	MMC(SCWK_SDMMC1_SAMPWE, "sdmmc1_sampwe", "cwk_sdmmc1", WK3568_SDMMC1_CON1, 1),

	GATE(ACWK_GMAC0, "acwk_gmac0", "acwk_php", 0,
			WK3568_CWKGATE_CON(15), 5, GFWAGS),
	GATE(PCWK_GMAC0, "pcwk_gmac0", "pcwk_php", 0,
			WK3568_CWKGATE_CON(15), 6, GFWAGS),
	COMPOSITE_NODIV(CWK_MAC0_2TOP, "cwk_mac0_2top", cwk_mac_2top_p, 0,
			WK3568_CWKSEW_CON(31), 8, 2, MFWAGS,
			WK3568_CWKGATE_CON(15), 7, GFWAGS),
	COMPOSITE_NODIV(CWK_MAC0_OUT, "cwk_mac0_out", cpww125_cpww50_cpww25_xin24m_p, 0,
			WK3568_CWKSEW_CON(31), 14, 2, MFWAGS,
			WK3568_CWKGATE_CON(15), 8, GFWAGS),
	GATE(CWK_MAC0_WEFOUT, "cwk_mac0_wefout", "cwk_mac0_2top", 0,
			WK3568_CWKGATE_CON(15), 12, GFWAGS),
	COMPOSITE_NODIV(CWK_GMAC0_PTP_WEF, "cwk_gmac0_ptp_wef", cwk_gmac_ptp_p, 0,
			WK3568_CWKSEW_CON(31), 12, 2, MFWAGS,
			WK3568_CWKGATE_CON(15), 4, GFWAGS),
	MUX(SCWK_GMAC0, "cwk_gmac0", mux_gmac0_p, CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			WK3568_CWKSEW_CON(31), 2, 1, MFWAGS),
	FACTOW(0, "cwk_gmac0_tx_div5", "cwk_gmac0", 0, 1, 5),
	FACTOW(0, "cwk_gmac0_tx_div50", "cwk_gmac0", 0, 1, 50),
	FACTOW(0, "cwk_gmac0_wx_div2", "cwk_gmac0", 0, 1, 2),
	FACTOW(0, "cwk_gmac0_wx_div20", "cwk_gmac0", 0, 1, 20),
	MUX(SCWK_GMAC0_WGMII_SPEED, "cwk_gmac0_wgmii_speed", mux_gmac0_wgmii_speed_p, 0,
			WK3568_CWKSEW_CON(31), 4, 2, MFWAGS),
	MUX(SCWK_GMAC0_WMII_SPEED, "cwk_gmac0_wmii_speed", mux_gmac0_wmii_speed_p, 0,
			WK3568_CWKSEW_CON(31), 3, 1, MFWAGS),
	MUX(SCWK_GMAC0_WX_TX, "cwk_gmac0_wx_tx", mux_gmac0_wx_tx_p,  CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(31), 0, 2, MFWAGS),

	/* PD_USB */
	COMPOSITE_NODIV(ACWK_USB, "acwk_usb", gpww300_gpww200_gpww100_xin24m_p, 0,
			WK3568_CWKSEW_CON(32), 0, 2, MFWAGS,
			WK3568_CWKGATE_CON(16), 0, GFWAGS),
	COMPOSITE_NODIV(HCWK_USB, "hcwk_usb", gpww150_gpww100_gpww75_xin24m_p, 0,
			WK3568_CWKSEW_CON(32), 2, 2, MFWAGS,
			WK3568_CWKGATE_CON(16), 1, GFWAGS),
	COMPOSITE_NOMUX(PCWK_USB, "pcwk_usb", "acwk_usb", 0,
			WK3568_CWKSEW_CON(32), 4, 4, DFWAGS,
			WK3568_CWKGATE_CON(16), 2, GFWAGS),
	GATE(HCWK_USB2HOST0, "hcwk_usb2host0", "hcwk_usb", 0,
			WK3568_CWKGATE_CON(16), 12, GFWAGS),
	GATE(HCWK_USB2HOST0_AWB, "hcwk_usb2host0_awb", "hcwk_usb", 0,
			WK3568_CWKGATE_CON(16), 13, GFWAGS),
	GATE(HCWK_USB2HOST1, "hcwk_usb2host1", "hcwk_usb", 0,
			WK3568_CWKGATE_CON(16), 14, GFWAGS),
	GATE(HCWK_USB2HOST1_AWB, "hcwk_usb2host1_awb", "hcwk_usb", 0,
			WK3568_CWKGATE_CON(16), 15, GFWAGS),
	GATE(HCWK_SDMMC2, "hcwk_sdmmc2", "hcwk_usb", 0,
			WK3568_CWKGATE_CON(17), 0, GFWAGS),
	COMPOSITE_NODIV(CWK_SDMMC2, "cwk_sdmmc2", cwk_sdmmc_p, 0,
			WK3568_CWKSEW_CON(32), 8, 3, MFWAGS,
			WK3568_CWKGATE_CON(17), 1, GFWAGS),
	MMC(SCWK_SDMMC2_DWV, "sdmmc2_dwv", "cwk_sdmmc2", WK3568_SDMMC2_CON0, 1),
	MMC(SCWK_SDMMC2_SAMPWE, "sdmmc2_sampwe", "cwk_sdmmc2", WK3568_SDMMC2_CON1, 1),

	GATE(ACWK_GMAC1, "acwk_gmac1", "acwk_usb", 0,
			WK3568_CWKGATE_CON(17), 3, GFWAGS),
	GATE(PCWK_GMAC1, "pcwk_gmac1", "pcwk_usb", 0,
			WK3568_CWKGATE_CON(17), 4, GFWAGS),
	COMPOSITE_NODIV(CWK_MAC1_2TOP, "cwk_mac1_2top", cwk_mac_2top_p, 0,
			WK3568_CWKSEW_CON(33), 8, 2, MFWAGS,
			WK3568_CWKGATE_CON(17), 5, GFWAGS),
	COMPOSITE_NODIV(CWK_MAC1_OUT, "cwk_mac1_out", cpww125_cpww50_cpww25_xin24m_p, 0,
			WK3568_CWKSEW_CON(33), 14, 2, MFWAGS,
			WK3568_CWKGATE_CON(17), 6, GFWAGS),
	GATE(CWK_MAC1_WEFOUT, "cwk_mac1_wefout", "cwk_mac1_2top", 0,
			WK3568_CWKGATE_CON(17), 10, GFWAGS),
	COMPOSITE_NODIV(CWK_GMAC1_PTP_WEF, "cwk_gmac1_ptp_wef", cwk_gmac_ptp_p, 0,
			WK3568_CWKSEW_CON(33), 12, 2, MFWAGS,
			WK3568_CWKGATE_CON(17), 2, GFWAGS),
	MUX(SCWK_GMAC1, "cwk_gmac1", mux_gmac1_p, CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			WK3568_CWKSEW_CON(33), 2, 1, MFWAGS),
	FACTOW(0, "cwk_gmac1_tx_div5", "cwk_gmac1", 0, 1, 5),
	FACTOW(0, "cwk_gmac1_tx_div50", "cwk_gmac1", 0, 1, 50),
	FACTOW(0, "cwk_gmac1_wx_div2", "cwk_gmac1", 0, 1, 2),
	FACTOW(0, "cwk_gmac1_wx_div20", "cwk_gmac1", 0, 1, 20),
	MUX(SCWK_GMAC1_WGMII_SPEED, "cwk_gmac1_wgmii_speed", mux_gmac1_wgmii_speed_p, 0,
			WK3568_CWKSEW_CON(33), 4, 2, MFWAGS),
	MUX(SCWK_GMAC1_WMII_SPEED, "cwk_gmac1_wmii_speed", mux_gmac1_wmii_speed_p, 0,
			WK3568_CWKSEW_CON(33), 3, 1, MFWAGS),
	MUX(SCWK_GMAC1_WX_TX, "cwk_gmac1_wx_tx", mux_gmac1_wx_tx_p,  CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(33), 0, 2, MFWAGS),

	/* PD_PEWI */
	COMPOSITE_NODIV(ACWK_PEWIMID, "acwk_pewimid", gpww300_gpww200_gpww100_xin24m_p, CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(10), 4, 2, MFWAGS,
			WK3568_CWKGATE_CON(14), 0, GFWAGS),
	COMPOSITE_NODIV(HCWK_PEWIMID, "hcwk_pewimid", gpww150_gpww100_gpww75_xin24m_p, CWK_IGNOWE_UNUSED,
			WK3568_CWKSEW_CON(10), 6, 2, MFWAGS,
			WK3568_CWKGATE_CON(14), 1, GFWAGS),

	/* PD_VI */
	COMPOSITE_NODIV(ACWK_VI, "acwk_vi", gpww400_gpww300_gpww200_xin24m_p, 0,
			WK3568_CWKSEW_CON(34), 0, 2, MFWAGS,
			WK3568_CWKGATE_CON(18), 0, GFWAGS),
	COMPOSITE_NOMUX(HCWK_VI, "hcwk_vi", "acwk_vi", 0,
			WK3568_CWKSEW_CON(34), 4, 4, DFWAGS,
			WK3568_CWKGATE_CON(18), 1, GFWAGS),
	COMPOSITE_NOMUX(PCWK_VI, "pcwk_vi", "acwk_vi", 0,
			WK3568_CWKSEW_CON(34), 8, 4, DFWAGS,
			WK3568_CWKGATE_CON(18), 2, GFWAGS),
	GATE(ACWK_VICAP, "acwk_vicap", "acwk_vi", 0,
			WK3568_CWKGATE_CON(18), 9, GFWAGS),
	GATE(HCWK_VICAP, "hcwk_vicap", "hcwk_vi", 0,
			WK3568_CWKGATE_CON(18), 10, GFWAGS),
	COMPOSITE_NODIV(DCWK_VICAP, "dcwk_vicap", cpww333_gpww300_gpww200_p, 0,
			WK3568_CWKSEW_CON(34), 14, 2, MFWAGS,
			WK3568_CWKGATE_CON(18), 11, GFWAGS),
	GATE(ICWK_VICAP_G, "icwk_vicap_g", "icwk_vicap", 0,
			WK3568_CWKGATE_CON(18), 13, GFWAGS),
	GATE(ACWK_ISP, "acwk_isp", "acwk_vi", 0,
			WK3568_CWKGATE_CON(19), 0, GFWAGS),
	GATE(HCWK_ISP, "hcwk_isp", "hcwk_vi", 0,
			WK3568_CWKGATE_CON(19), 1, GFWAGS),
	COMPOSITE(CWK_ISP, "cwk_isp", cpww_gpww_hpww_p, 0,
			WK3568_CWKSEW_CON(35), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(19), 2, GFWAGS),
	GATE(PCWK_CSI2HOST1, "pcwk_csi2host1", "pcwk_vi", 0,
			WK3568_CWKGATE_CON(19), 4, GFWAGS),
	COMPOSITE(CWK_CIF_OUT, "cwk_cif_out", gpww_usb480m_xin24m_p, 0,
			WK3568_CWKSEW_CON(35), 14, 2, MFWAGS, 8, 6, DFWAGS,
			WK3568_CWKGATE_CON(19), 8, GFWAGS),
	COMPOSITE(CWK_CAM0_OUT, "cwk_cam0_out", gpww_usb480m_xin24m_p, 0,
			WK3568_CWKSEW_CON(36), 6, 2, MFWAGS, 0, 6, DFWAGS,
			WK3568_CWKGATE_CON(19), 9, GFWAGS),
	COMPOSITE(CWK_CAM1_OUT, "cwk_cam1_out", gpww_usb480m_xin24m_p, 0,
			WK3568_CWKSEW_CON(36), 14, 2, MFWAGS, 8, 6, DFWAGS,
			WK3568_CWKGATE_CON(19), 10, GFWAGS),

	/* PD_VO */
	COMPOSITE_NODIV(ACWK_VO, "acwk_vo", gpww300_cpww250_gpww100_xin24m_p, 0,
			WK3568_CWKSEW_CON(37), 0, 2, MFWAGS,
			WK3568_CWKGATE_CON(20), 0, GFWAGS),
	COMPOSITE_NOMUX(HCWK_VO, "hcwk_vo", "acwk_vo", 0,
			WK3568_CWKSEW_CON(37), 8, 4, DFWAGS,
			WK3568_CWKGATE_CON(20), 1, GFWAGS),
	COMPOSITE_NOMUX(PCWK_VO, "pcwk_vo", "acwk_vo", 0,
			WK3568_CWKSEW_CON(37), 12, 4, DFWAGS,
			WK3568_CWKGATE_CON(20), 2, GFWAGS),
	COMPOSITE(ACWK_VOP_PWE, "acwk_vop_pwe", cpww_gpww_hpww_vpww_p, 0,
			WK3568_CWKSEW_CON(38), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(20), 6, GFWAGS),
	GATE(ACWK_VOP, "acwk_vop", "acwk_vop_pwe", 0,
			WK3568_CWKGATE_CON(20), 8, GFWAGS),
	GATE(HCWK_VOP, "hcwk_vop", "hcwk_vo", 0,
			WK3568_CWKGATE_CON(20), 9, GFWAGS),
	COMPOSITE(DCWK_VOP0, "dcwk_vop0", hpww_vpww_gpww_cpww_p, CWK_SET_WATE_NO_WEPAWENT,
			WK3568_CWKSEW_CON(39), 10, 2, MFWAGS, 0, 8, DFWAGS,
			WK3568_CWKGATE_CON(20), 10, GFWAGS),
	COMPOSITE(DCWK_VOP1, "dcwk_vop1", hpww_vpww_gpww_cpww_p, CWK_SET_WATE_NO_WEPAWENT,
			WK3568_CWKSEW_CON(40), 10, 2, MFWAGS, 0, 8, DFWAGS,
			WK3568_CWKGATE_CON(20), 11, GFWAGS),
	COMPOSITE(DCWK_VOP2, "dcwk_vop2", hpww_vpww_gpww_cpww_p, CWK_SET_WATE_NO_WEPAWENT,
			WK3568_CWKSEW_CON(41), 10, 2, MFWAGS, 0, 8, DFWAGS,
			WK3568_CWKGATE_CON(20), 12, GFWAGS),
	GATE(CWK_VOP_PWM, "cwk_vop_pwm", "xin24m", 0,
			WK3568_CWKGATE_CON(20), 13, GFWAGS),
	GATE(ACWK_HDCP, "acwk_hdcp", "acwk_vo", 0,
			WK3568_CWKGATE_CON(21), 0, GFWAGS),
	GATE(HCWK_HDCP, "hcwk_hdcp", "hcwk_vo", 0,
			WK3568_CWKGATE_CON(21), 1, GFWAGS),
	GATE(PCWK_HDCP, "pcwk_hdcp", "pcwk_vo", 0,
			WK3568_CWKGATE_CON(21), 2, GFWAGS),
	GATE(PCWK_HDMI_HOST, "pcwk_hdmi_host", "pcwk_vo", 0,
			WK3568_CWKGATE_CON(21), 3, GFWAGS),
	GATE(CWK_HDMI_SFW, "cwk_hdmi_sfw", "xin24m", 0,
			WK3568_CWKGATE_CON(21), 4, GFWAGS),
	GATE(CWK_HDMI_CEC, "cwk_hdmi_cec", "cwk_wtc_32k", 0,
			WK3568_CWKGATE_CON(21), 5, GFWAGS),
	GATE(PCWK_DSITX_0, "pcwk_dsitx_0", "pcwk_vo", 0,
			WK3568_CWKGATE_CON(21), 6, GFWAGS),
	GATE(PCWK_DSITX_1, "pcwk_dsitx_1", "pcwk_vo", 0,
			WK3568_CWKGATE_CON(21), 7, GFWAGS),
	GATE(PCWK_EDP_CTWW, "pcwk_edp_ctww", "pcwk_vo", 0,
			WK3568_CWKGATE_CON(21), 8, GFWAGS),
	COMPOSITE_NODIV(CWK_EDP_200M, "cwk_edp_200m", gpww200_gpww150_cpww125_p, 0,
			WK3568_CWKSEW_CON(38), 8, 2, MFWAGS,
			WK3568_CWKGATE_CON(21), 9, GFWAGS),

	/* PD_VPU */
	COMPOSITE(ACWK_VPU_PWE, "acwk_vpu_pwe", gpww_cpww_p, 0,
			WK3568_CWKSEW_CON(42), 7, 1, MFWAGS, 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(22), 0, GFWAGS),
	COMPOSITE_NOMUX(HCWK_VPU_PWE, "hcwk_vpu_pwe", "acwk_vpu_pwe", 0,
			WK3568_CWKSEW_CON(42), 8, 4, DFWAGS,
			WK3568_CWKGATE_CON(22), 1, GFWAGS),
	GATE(ACWK_VPU, "acwk_vpu", "acwk_vpu_pwe", 0,
			WK3568_CWKGATE_CON(22), 4, GFWAGS),
	GATE(HCWK_VPU, "hcwk_vpu", "hcwk_vpu_pwe", 0,
			WK3568_CWKGATE_CON(22), 5, GFWAGS),

	/* PD_WGA */
	COMPOSITE_NODIV(ACWK_WGA_PWE, "acwk_wga_pwe", gpww300_cpww250_gpww100_xin24m_p, 0,
			WK3568_CWKSEW_CON(43), 0, 2, MFWAGS,
			WK3568_CWKGATE_CON(23), 0, GFWAGS),
	COMPOSITE_NOMUX(HCWK_WGA_PWE, "hcwk_wga_pwe", "acwk_wga_pwe", 0,
			WK3568_CWKSEW_CON(43), 8, 4, DFWAGS,
			WK3568_CWKGATE_CON(23), 1, GFWAGS),
	COMPOSITE_NOMUX(PCWK_WGA_PWE, "pcwk_wga_pwe", "acwk_wga_pwe", 0,
			WK3568_CWKSEW_CON(43), 12, 4, DFWAGS,
			WK3568_CWKGATE_CON(22), 12, GFWAGS),
	GATE(ACWK_WGA, "acwk_wga", "acwk_wga_pwe", 0,
			WK3568_CWKGATE_CON(23), 4, GFWAGS),
	GATE(HCWK_WGA, "hcwk_wga", "hcwk_wga_pwe", 0,
			WK3568_CWKGATE_CON(23), 5, GFWAGS),
	COMPOSITE_NODIV(CWK_WGA_COWE, "cwk_wga_cowe", gpww300_gpww200_gpww100_p, 0,
			WK3568_CWKSEW_CON(43), 2, 2, MFWAGS,
			WK3568_CWKGATE_CON(23), 6, GFWAGS),
	GATE(ACWK_IEP, "acwk_iep", "acwk_wga_pwe", 0,
			WK3568_CWKGATE_CON(23), 7, GFWAGS),
	GATE(HCWK_IEP, "hcwk_iep", "hcwk_wga_pwe", 0,
			WK3568_CWKGATE_CON(23), 8, GFWAGS),
	COMPOSITE_NODIV(CWK_IEP_COWE, "cwk_iep_cowe", gpww300_gpww200_gpww100_p, 0,
			WK3568_CWKSEW_CON(43), 4, 2, MFWAGS,
			WK3568_CWKGATE_CON(23), 9, GFWAGS),
	GATE(HCWK_EBC, "hcwk_ebc", "hcwk_wga_pwe", 0, WK3568_CWKGATE_CON(23), 10, GFWAGS),
	COMPOSITE_NODIV(DCWK_EBC, "dcwk_ebc", gpww400_cpww333_gpww200_p, 0,
			WK3568_CWKSEW_CON(43), 6, 2, MFWAGS,
			WK3568_CWKGATE_CON(23), 11, GFWAGS),
	GATE(ACWK_JDEC, "acwk_jdec", "acwk_wga_pwe", 0,
			WK3568_CWKGATE_CON(23), 12, GFWAGS),
	GATE(HCWK_JDEC, "hcwk_jdec", "hcwk_wga_pwe", 0,
			WK3568_CWKGATE_CON(23), 13, GFWAGS),
	GATE(ACWK_JENC, "acwk_jenc", "acwk_wga_pwe", 0,
			WK3568_CWKGATE_CON(23), 14, GFWAGS),
	GATE(HCWK_JENC, "hcwk_jenc", "hcwk_wga_pwe", 0,
			WK3568_CWKGATE_CON(23), 15, GFWAGS),
	GATE(PCWK_EINK, "pcwk_eink", "pcwk_wga_pwe", 0,
			WK3568_CWKGATE_CON(22), 14, GFWAGS),
	GATE(HCWK_EINK, "hcwk_eink", "hcwk_wga_pwe", 0,
			WK3568_CWKGATE_CON(22), 15, GFWAGS),

	/* PD_WKVENC */
	COMPOSITE(ACWK_WKVENC_PWE, "acwk_wkvenc_pwe", gpww_cpww_npww_p, 0,
			WK3568_CWKSEW_CON(44), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(24), 0, GFWAGS),
	COMPOSITE_NOMUX(HCWK_WKVENC_PWE, "hcwk_wkvenc_pwe", "acwk_wkvenc_pwe", 0,
			WK3568_CWKSEW_CON(44), 8, 4, DFWAGS,
			WK3568_CWKGATE_CON(24), 1, GFWAGS),
	GATE(ACWK_WKVENC, "acwk_wkvenc", "acwk_wkvenc_pwe", 0,
			WK3568_CWKGATE_CON(24), 6, GFWAGS),
	GATE(HCWK_WKVENC, "hcwk_wkvenc", "hcwk_wkvenc_pwe", 0,
			WK3568_CWKGATE_CON(24), 7, GFWAGS),
	COMPOSITE(CWK_WKVENC_COWE, "cwk_wkvenc_cowe", gpww_cpww_npww_vpww_p, 0,
			WK3568_CWKSEW_CON(45), 14, 2, MFWAGS, 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(24), 8, GFWAGS),
	COMPOSITE(ACWK_WKVDEC_PWE, "acwk_wkvdec_pwe", acwk_wkvdec_pwe_p, CWK_SET_WATE_NO_WEPAWENT,
			WK3568_CWKSEW_CON(47), 7, 1, MFWAGS, 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(25), 0, GFWAGS),
	COMPOSITE_NOMUX(HCWK_WKVDEC_PWE, "hcwk_wkvdec_pwe", "acwk_wkvdec_pwe", 0,
			WK3568_CWKSEW_CON(47), 8, 4, DFWAGS,
			WK3568_CWKGATE_CON(25), 1, GFWAGS),
	GATE(ACWK_WKVDEC, "acwk_wkvdec", "acwk_wkvdec_pwe", 0,
			WK3568_CWKGATE_CON(25), 4, GFWAGS),
	GATE(HCWK_WKVDEC, "hcwk_wkvdec", "hcwk_wkvdec_pwe", 0,
			WK3568_CWKGATE_CON(25), 5, GFWAGS),
	COMPOSITE(CWK_WKVDEC_CA, "cwk_wkvdec_ca", gpww_cpww_npww_vpww_p, 0,
			WK3568_CWKSEW_CON(48), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(25), 6, GFWAGS),
	COMPOSITE(CWK_WKVDEC_COWE, "cwk_wkvdec_cowe", cwk_wkvdec_cowe_p, CWK_SET_WATE_NO_WEPAWENT,
			WK3568_CWKSEW_CON(49), 14, 2, MFWAGS, 8, 5, DFWAGS,
			WK3568_CWKGATE_CON(25), 7, GFWAGS),
	COMPOSITE(CWK_WKVDEC_HEVC_CA, "cwk_wkvdec_hevc_ca", gpww_cpww_npww_vpww_p, 0,
			WK3568_CWKSEW_CON(49), 6, 2, MFWAGS, 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(25), 8, GFWAGS),

	/* PD_BUS */
	COMPOSITE_NODIV(ACWK_BUS, "acwk_bus", gpww200_gpww150_gpww100_xin24m_p, 0,
			WK3568_CWKSEW_CON(50), 0, 2, MFWAGS,
			WK3568_CWKGATE_CON(26), 0, GFWAGS),
	COMPOSITE_NODIV(PCWK_BUS, "pcwk_bus", gpww100_gpww75_cpww50_xin24m_p, 0,
			WK3568_CWKSEW_CON(50), 4, 2, MFWAGS,
			WK3568_CWKGATE_CON(26), 1, GFWAGS),
	GATE(PCWK_TSADC, "pcwk_tsadc", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(26), 4, GFWAGS),
	COMPOSITE(CWK_TSADC_TSEN, "cwk_tsadc_tsen", xin24m_gpww100_cpww100_p, 0,
			WK3568_CWKSEW_CON(51), 4, 2, MFWAGS, 0, 3, DFWAGS,
			WK3568_CWKGATE_CON(26), 5, GFWAGS),
	COMPOSITE_NOMUX(CWK_TSADC, "cwk_tsadc", "cwk_tsadc_tsen", 0,
			WK3568_CWKSEW_CON(51), 8, 7, DFWAGS,
			WK3568_CWKGATE_CON(26), 6, GFWAGS),
	GATE(PCWK_SAWADC, "pcwk_sawadc", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(26), 7, GFWAGS),
	GATE(CWK_SAWADC, "cwk_sawadc", "xin24m", 0,
			WK3568_CWKGATE_CON(26), 8, GFWAGS),
	GATE(PCWK_SCW, "pcwk_scw", "pcwk_bus", CWK_IGNOWE_UNUSED,
			WK3568_CWKGATE_CON(26), 12, GFWAGS),
	GATE(PCWK_WDT_NS, "pcwk_wdt_ns", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(26), 13, GFWAGS),
	GATE(TCWK_WDT_NS, "tcwk_wdt_ns", "xin24m", 0,
			WK3568_CWKGATE_CON(26), 14, GFWAGS),
	GATE(ACWK_MCU, "acwk_mcu", "acwk_bus", CWK_IGNOWE_UNUSED,
			WK3568_CWKGATE_CON(32), 13, GFWAGS),
	GATE(PCWK_INTMUX, "pcwk_intmux", "pcwk_bus", CWK_IGNOWE_UNUSED,
			WK3568_CWKGATE_CON(32), 14, GFWAGS),
	GATE(PCWK_MAIWBOX, "pcwk_maiwbox", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(32), 15, GFWAGS),

	GATE(PCWK_UAWT1, "pcwk_uawt1", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(27), 12, GFWAGS),
	COMPOSITE(CWK_UAWT1_SWC, "cwk_uawt1_swc", gpww_cpww_usb480m_p, 0,
			WK3568_CWKSEW_CON(52), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3568_CWKGATE_CON(27), 13, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT1_FWAC, "cwk_uawt1_fwac", "cwk_uawt1_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(53), 0,
			WK3568_CWKGATE_CON(27), 14, GFWAGS,
			&wk3568_uawt1_fwacmux),
	GATE(SCWK_UAWT1, "scwk_uawt1", "scwk_uawt1_mux", 0,
			WK3568_CWKGATE_CON(27), 15, GFWAGS),

	GATE(PCWK_UAWT2, "pcwk_uawt2", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(28), 0, GFWAGS),
	COMPOSITE(CWK_UAWT2_SWC, "cwk_uawt2_swc", gpww_cpww_usb480m_p, 0,
			WK3568_CWKSEW_CON(54), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3568_CWKGATE_CON(28), 1, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT2_FWAC, "cwk_uawt2_fwac", "cwk_uawt2_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(55), 0,
			WK3568_CWKGATE_CON(28), 2, GFWAGS,
			&wk3568_uawt2_fwacmux),
	GATE(SCWK_UAWT2, "scwk_uawt2", "scwk_uawt2_mux", 0,
			WK3568_CWKGATE_CON(28), 3, GFWAGS),

	GATE(PCWK_UAWT3, "pcwk_uawt3", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(28), 4, GFWAGS),
	COMPOSITE(CWK_UAWT3_SWC, "cwk_uawt3_swc", gpww_cpww_usb480m_p, 0,
			WK3568_CWKSEW_CON(56), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3568_CWKGATE_CON(28), 5, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT3_FWAC, "cwk_uawt3_fwac", "cwk_uawt3_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(57), 0,
			WK3568_CWKGATE_CON(28), 6, GFWAGS,
			&wk3568_uawt3_fwacmux),
	GATE(SCWK_UAWT3, "scwk_uawt3", "scwk_uawt3_mux", 0,
			WK3568_CWKGATE_CON(28), 7, GFWAGS),

	GATE(PCWK_UAWT4, "pcwk_uawt4", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(28), 8, GFWAGS),
	COMPOSITE(CWK_UAWT4_SWC, "cwk_uawt4_swc", gpww_cpww_usb480m_p, 0,
			WK3568_CWKSEW_CON(58), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3568_CWKGATE_CON(28), 9, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT4_FWAC, "cwk_uawt4_fwac", "cwk_uawt4_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(59), 0,
			WK3568_CWKGATE_CON(28), 10, GFWAGS,
			&wk3568_uawt4_fwacmux),
	GATE(SCWK_UAWT4, "scwk_uawt4", "scwk_uawt4_mux", 0,
			WK3568_CWKGATE_CON(28), 11, GFWAGS),

	GATE(PCWK_UAWT5, "pcwk_uawt5", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(28), 12, GFWAGS),
	COMPOSITE(CWK_UAWT5_SWC, "cwk_uawt5_swc", gpww_cpww_usb480m_p, 0,
			WK3568_CWKSEW_CON(60), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3568_CWKGATE_CON(28), 13, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT5_FWAC, "cwk_uawt5_fwac", "cwk_uawt5_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(61), 0,
			WK3568_CWKGATE_CON(28), 14, GFWAGS,
			&wk3568_uawt5_fwacmux),
	GATE(SCWK_UAWT5, "scwk_uawt5", "scwk_uawt5_mux", 0,
			WK3568_CWKGATE_CON(28), 15, GFWAGS),

	GATE(PCWK_UAWT6, "pcwk_uawt6", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(29), 0, GFWAGS),
	COMPOSITE(CWK_UAWT6_SWC, "cwk_uawt6_swc", gpww_cpww_usb480m_p, 0,
			WK3568_CWKSEW_CON(62), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3568_CWKGATE_CON(29), 1, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT6_FWAC, "cwk_uawt6_fwac", "cwk_uawt6_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(63), 0,
			WK3568_CWKGATE_CON(29), 2, GFWAGS,
			&wk3568_uawt6_fwacmux),
	GATE(SCWK_UAWT6, "scwk_uawt6", "scwk_uawt6_mux", 0,
			WK3568_CWKGATE_CON(29), 3, GFWAGS),

	GATE(PCWK_UAWT7, "pcwk_uawt7", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(29), 4, GFWAGS),
	COMPOSITE(CWK_UAWT7_SWC, "cwk_uawt7_swc", gpww_cpww_usb480m_p, 0,
			WK3568_CWKSEW_CON(64), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3568_CWKGATE_CON(29), 5, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT7_FWAC, "cwk_uawt7_fwac", "cwk_uawt7_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(65), 0,
			WK3568_CWKGATE_CON(29), 6, GFWAGS,
			&wk3568_uawt7_fwacmux),
	GATE(SCWK_UAWT7, "scwk_uawt7", "scwk_uawt7_mux", 0,
			WK3568_CWKGATE_CON(29), 7, GFWAGS),

	GATE(PCWK_UAWT8, "pcwk_uawt8", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(29), 8, GFWAGS),
	COMPOSITE(CWK_UAWT8_SWC, "cwk_uawt8_swc", gpww_cpww_usb480m_p, 0,
			WK3568_CWKSEW_CON(66), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3568_CWKGATE_CON(29), 9, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT8_FWAC, "cwk_uawt8_fwac", "cwk_uawt8_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(67), 0,
			WK3568_CWKGATE_CON(29), 10, GFWAGS,
			&wk3568_uawt8_fwacmux),
	GATE(SCWK_UAWT8, "scwk_uawt8", "scwk_uawt8_mux", 0,
			WK3568_CWKGATE_CON(29), 11, GFWAGS),

	GATE(PCWK_UAWT9, "pcwk_uawt9", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(29), 12, GFWAGS),
	COMPOSITE(CWK_UAWT9_SWC, "cwk_uawt9_swc", gpww_cpww_usb480m_p, 0,
			WK3568_CWKSEW_CON(68), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3568_CWKGATE_CON(29), 13, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT9_FWAC, "cwk_uawt9_fwac", "cwk_uawt9_swc", CWK_SET_WATE_PAWENT,
			WK3568_CWKSEW_CON(69), 0,
			WK3568_CWKGATE_CON(29), 14, GFWAGS,
			&wk3568_uawt9_fwacmux),
	GATE(SCWK_UAWT9, "scwk_uawt9", "scwk_uawt9_mux", 0,
			WK3568_CWKGATE_CON(29), 15, GFWAGS),

	GATE(PCWK_CAN0, "pcwk_can0", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(27), 5, GFWAGS),
	COMPOSITE(CWK_CAN0, "cwk_can0", gpww_cpww_p, 0,
			WK3568_CWKSEW_CON(70), 7, 1, MFWAGS, 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(27), 6, GFWAGS),
	GATE(PCWK_CAN1, "pcwk_can1", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(27), 7, GFWAGS),
	COMPOSITE(CWK_CAN1, "cwk_can1", gpww_cpww_p, 0,
			WK3568_CWKSEW_CON(70), 15, 1, MFWAGS, 8, 5, DFWAGS,
			WK3568_CWKGATE_CON(27), 8, GFWAGS),
	GATE(PCWK_CAN2, "pcwk_can2", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(27), 9, GFWAGS),
	COMPOSITE(CWK_CAN2, "cwk_can2", gpww_cpww_p, 0,
			WK3568_CWKSEW_CON(71), 7, 1, MFWAGS, 0, 5, DFWAGS,
			WK3568_CWKGATE_CON(27), 10, GFWAGS),
	COMPOSITE_NODIV(CWK_I2C, "cwk_i2c", cwk_i2c_p, 0,
			WK3568_CWKSEW_CON(71), 8, 2, MFWAGS,
			WK3568_CWKGATE_CON(32), 10, GFWAGS),
	GATE(PCWK_I2C1, "pcwk_i2c1", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(30), 0, GFWAGS),
	GATE(CWK_I2C1, "cwk_i2c1", "cwk_i2c", 0,
			WK3568_CWKGATE_CON(30), 1, GFWAGS),
	GATE(PCWK_I2C2, "pcwk_i2c2", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(30), 2, GFWAGS),
	GATE(CWK_I2C2, "cwk_i2c2", "cwk_i2c", 0,
			WK3568_CWKGATE_CON(30), 3, GFWAGS),
	GATE(PCWK_I2C3, "pcwk_i2c3", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(30), 4, GFWAGS),
	GATE(CWK_I2C3, "cwk_i2c3", "cwk_i2c", 0,
			WK3568_CWKGATE_CON(30), 5, GFWAGS),
	GATE(PCWK_I2C4, "pcwk_i2c4", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(30), 6, GFWAGS),
	GATE(CWK_I2C4, "cwk_i2c4", "cwk_i2c", 0,
			WK3568_CWKGATE_CON(30), 7, GFWAGS),
	GATE(PCWK_I2C5, "pcwk_i2c5", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(30), 8, GFWAGS),
	GATE(CWK_I2C5, "cwk_i2c5", "cwk_i2c", 0,
			WK3568_CWKGATE_CON(30), 9, GFWAGS),
	GATE(PCWK_SPI0, "pcwk_spi0", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(30), 10, GFWAGS),
	COMPOSITE_NODIV(CWK_SPI0, "cwk_spi0", gpww200_xin24m_cpww100_p, 0,
			WK3568_CWKSEW_CON(72), 0, 1, MFWAGS,
			WK3568_CWKGATE_CON(30), 11, GFWAGS),
	GATE(PCWK_SPI1, "pcwk_spi1", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(30), 12, GFWAGS),
	COMPOSITE_NODIV(CWK_SPI1, "cwk_spi1", gpww200_xin24m_cpww100_p, 0,
			WK3568_CWKSEW_CON(72), 2, 1, MFWAGS,
			WK3568_CWKGATE_CON(30), 13, GFWAGS),
	GATE(PCWK_SPI2, "pcwk_spi2", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(30), 14, GFWAGS),
	COMPOSITE_NODIV(CWK_SPI2, "cwk_spi2", gpww200_xin24m_cpww100_p, 0,
			WK3568_CWKSEW_CON(72), 4, 1, MFWAGS,
			WK3568_CWKGATE_CON(30), 15, GFWAGS),
	GATE(PCWK_SPI3, "pcwk_spi3", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(31), 0, GFWAGS),
	COMPOSITE_NODIV(CWK_SPI3, "cwk_spi3", gpww200_xin24m_cpww100_p, 0,
			WK3568_CWKSEW_CON(72), 6, 1, MFWAGS, WK3568_CWKGATE_CON(31), 1, GFWAGS),
	GATE(PCWK_PWM1, "pcwk_pwm1", "pcwk_bus", 0, WK3568_CWKGATE_CON(31), 10, GFWAGS),
	COMPOSITE_NODIV(CWK_PWM1, "cwk_pwm1", gpww100_xin24m_cpww100_p, 0,
			WK3568_CWKSEW_CON(72), 8, 1, MFWAGS,
			WK3568_CWKGATE_CON(31), 11, GFWAGS),
	GATE(CWK_PWM1_CAPTUWE, "cwk_pwm1_captuwe", "xin24m", 0,
			WK3568_CWKGATE_CON(31), 12, GFWAGS),
	GATE(PCWK_PWM2, "pcwk_pwm2", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(31), 13, GFWAGS),
	COMPOSITE_NODIV(CWK_PWM2, "cwk_pwm2", gpww100_xin24m_cpww100_p, 0,
			WK3568_CWKSEW_CON(72), 10, 1, MFWAGS,
			WK3568_CWKGATE_CON(31), 14, GFWAGS),
	GATE(CWK_PWM2_CAPTUWE, "cwk_pwm2_captuwe", "xin24m", 0,
			WK3568_CWKGATE_CON(31), 15, GFWAGS),
	GATE(PCWK_PWM3, "pcwk_pwm3", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(32), 0, GFWAGS),
	COMPOSITE_NODIV(CWK_PWM3, "cwk_pwm3", gpww100_xin24m_cpww100_p, 0,
			WK3568_CWKSEW_CON(72), 12, 1, MFWAGS,
			WK3568_CWKGATE_CON(32), 1, GFWAGS),
	GATE(CWK_PWM3_CAPTUWE, "cwk_pwm3_captuwe", "xin24m", 0,
			WK3568_CWKGATE_CON(32), 2, GFWAGS),
	COMPOSITE_NODIV(DBCWK_GPIO, "dbcwk_gpio", xin24m_32k_p, 0,
			WK3568_CWKSEW_CON(72), 14, 1, MFWAGS,
			WK3568_CWKGATE_CON(32), 11, GFWAGS),
	GATE(PCWK_GPIO1, "pcwk_gpio1", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(31), 2, GFWAGS),
	GATE(DBCWK_GPIO1, "dbcwk_gpio1", "dbcwk_gpio", 0,
			WK3568_CWKGATE_CON(31), 3, GFWAGS),
	GATE(PCWK_GPIO2, "pcwk_gpio2", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(31), 4, GFWAGS),
	GATE(DBCWK_GPIO2, "dbcwk_gpio2", "dbcwk_gpio", 0,
			WK3568_CWKGATE_CON(31), 5, GFWAGS),
	GATE(PCWK_GPIO3, "pcwk_gpio3", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(31), 6, GFWAGS),
	GATE(DBCWK_GPIO3, "dbcwk_gpio3", "dbcwk_gpio", 0,
			WK3568_CWKGATE_CON(31), 7, GFWAGS),
	GATE(PCWK_GPIO4, "pcwk_gpio4", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(31), 8, GFWAGS),
	GATE(DBCWK_GPIO4, "dbcwk_gpio4", "dbcwk_gpio", 0,
			WK3568_CWKGATE_CON(31), 9, GFWAGS),
	GATE(PCWK_TIMEW, "pcwk_timew", "pcwk_bus", 0,
			WK3568_CWKGATE_CON(32), 3, GFWAGS),
	GATE(CWK_TIMEW0, "cwk_timew0", "xin24m", 0,
			WK3568_CWKGATE_CON(32), 4, GFWAGS),
	GATE(CWK_TIMEW1, "cwk_timew1", "xin24m", 0,
			WK3568_CWKGATE_CON(32), 5, GFWAGS),
	GATE(CWK_TIMEW2, "cwk_timew2", "xin24m", 0,
			WK3568_CWKGATE_CON(32), 6, GFWAGS),
	GATE(CWK_TIMEW3, "cwk_timew3", "xin24m", 0,
			WK3568_CWKGATE_CON(32), 7, GFWAGS),
	GATE(CWK_TIMEW4, "cwk_timew4", "xin24m", 0,
			WK3568_CWKGATE_CON(32), 8, GFWAGS),
	GATE(CWK_TIMEW5, "cwk_timew5", "xin24m", 0,
			WK3568_CWKGATE_CON(32), 9, GFWAGS),

	/* PD_TOP */
	COMPOSITE_NODIV(ACWK_TOP_HIGH, "acwk_top_high", cpww500_gpww400_gpww300_xin24m_p, 0,
			WK3568_CWKSEW_CON(73), 0, 2, MFWAGS,
			WK3568_CWKGATE_CON(33), 0, GFWAGS),
	COMPOSITE_NODIV(ACWK_TOP_WOW, "acwk_top_wow", gpww400_gpww300_gpww200_xin24m_p, 0,
			WK3568_CWKSEW_CON(73), 4, 2, MFWAGS,
			WK3568_CWKGATE_CON(33), 1, GFWAGS),
	COMPOSITE_NODIV(HCWK_TOP, "hcwk_top", gpww150_gpww100_gpww75_xin24m_p, 0,
			WK3568_CWKSEW_CON(73), 8, 2, MFWAGS,
			WK3568_CWKGATE_CON(33), 2, GFWAGS),
	COMPOSITE_NODIV(PCWK_TOP, "pcwk_top", gpww100_gpww75_cpww50_xin24m_p, 0,
			WK3568_CWKSEW_CON(73), 12, 2, MFWAGS,
			WK3568_CWKGATE_CON(33), 3, GFWAGS),
	GATE(PCWK_PCIE30PHY, "pcwk_pcie30phy", "pcwk_top", 0,
			WK3568_CWKGATE_CON(33), 8, GFWAGS),
	COMPOSITE_NODIV(CWK_OPTC_AWB, "cwk_optc_awb", xin24m_cpww100_p, 0,
			WK3568_CWKSEW_CON(73), 15, 1, MFWAGS,
			WK3568_CWKGATE_CON(33), 9, GFWAGS),
	GATE(PCWK_MIPICSIPHY, "pcwk_mipicsiphy", "pcwk_top", 0,
			WK3568_CWKGATE_CON(33), 13, GFWAGS),
	GATE(PCWK_MIPIDSIPHY0, "pcwk_mipidsiphy0", "pcwk_top", 0,
			WK3568_CWKGATE_CON(33), 14, GFWAGS),
	GATE(PCWK_MIPIDSIPHY1, "pcwk_mipidsiphy1", "pcwk_top", 0,
			WK3568_CWKGATE_CON(33), 15, GFWAGS),
	GATE(PCWK_PIPEPHY0, "pcwk_pipephy0", "pcwk_top", 0,
			WK3568_CWKGATE_CON(34), 4, GFWAGS),
	GATE(PCWK_PIPEPHY1, "pcwk_pipephy1", "pcwk_top", 0,
			WK3568_CWKGATE_CON(34), 5, GFWAGS),
	GATE(PCWK_PIPEPHY2, "pcwk_pipephy2", "pcwk_top", 0,
			WK3568_CWKGATE_CON(34), 6, GFWAGS),
	GATE(PCWK_CPU_BOOST, "pcwk_cpu_boost", "pcwk_top", 0,
			WK3568_CWKGATE_CON(34), 11, GFWAGS),
	GATE(CWK_CPU_BOOST, "cwk_cpu_boost", "xin24m", 0,
			WK3568_CWKGATE_CON(34), 12, GFWAGS),
	GATE(PCWK_OTPPHY, "pcwk_otpphy", "pcwk_top", 0,
			WK3568_CWKGATE_CON(34), 13, GFWAGS),
	GATE(PCWK_EDPPHY_GWF, "pcwk_edpphy_gwf", "pcwk_top", 0,
			WK3568_CWKGATE_CON(34), 14, GFWAGS),
};

static stwuct wockchip_cwk_bwanch wk3568_cwk_pmu_bwanches[] __initdata = {
	/* PD_PMU */
	FACTOW(0, "ppww_ph0", "ppww", 0, 1, 2),
	FACTOW(0, "ppww_ph180", "ppww", 0, 1, 2),
	FACTOW(0, "hpww_ph0", "hpww", 0, 1, 2),

	MUX(CWK_PDPMU, "cwk_pdpmu", cwk_pdpmu_p, 0,
			WK3568_PMU_CWKSEW_CON(2), 15, 1, MFWAGS),
	COMPOSITE_NOMUX(PCWK_PDPMU, "pcwk_pdpmu", "cwk_pdpmu", 0,
			WK3568_PMU_CWKSEW_CON(2), 0, 5, DFWAGS,
			WK3568_PMU_CWKGATE_CON(0), 2, GFWAGS),
	GATE(PCWK_PMU, "pcwk_pmu", "pcwk_pdpmu", 0,
			WK3568_PMU_CWKGATE_CON(0), 6, GFWAGS),
	GATE(CWK_PMU, "cwk_pmu", "xin24m", 0,
			WK3568_PMU_CWKGATE_CON(0), 7, GFWAGS),
	GATE(PCWK_I2C0, "pcwk_i2c0", "pcwk_pdpmu", 0,
			WK3568_PMU_CWKGATE_CON(1), 0, GFWAGS),
	COMPOSITE_NOMUX(CWK_I2C0, "cwk_i2c0", "cwk_pdpmu", 0,
			WK3568_PMU_CWKSEW_CON(3), 0, 7, DFWAGS,
			WK3568_PMU_CWKGATE_CON(1), 1, GFWAGS),
	GATE(PCWK_UAWT0, "pcwk_uawt0", "pcwk_pdpmu", 0,
			WK3568_PMU_CWKGATE_CON(1), 2, GFWAGS),

	COMPOSITE_FWACMUX(CWK_WTC32K_FWAC, "cwk_wtc32k_fwac", "xin24m", CWK_IGNOWE_UNUSED,
			WK3568_PMU_CWKSEW_CON(1), 0,
			WK3568_PMU_CWKGATE_CON(0), 1, GFWAGS,
			&wk3568_wtc32k_pmu_fwacmux),

	COMPOSITE_NOMUX(XIN_OSC0_DIV, "xin_osc0_div", "xin24m", CWK_IGNOWE_UNUSED,
			WK3568_PMU_CWKSEW_CON(0), 0, 5, DFWAGS,
			WK3568_PMU_CWKGATE_CON(0), 0, GFWAGS),

	COMPOSITE(CWK_UAWT0_DIV, "scwk_uawt0_div", ppww_usb480m_cpww_gpww_p, 0,
			WK3568_PMU_CWKSEW_CON(4), 8, 2, MFWAGS, 0, 7, DFWAGS,
			WK3568_PMU_CWKGATE_CON(1), 3, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT0_FWAC, "scwk_uawt0_fwac", "scwk_uawt0_div", CWK_SET_WATE_PAWENT,
			WK3568_PMU_CWKSEW_CON(5), 0,
			WK3568_PMU_CWKGATE_CON(1), 4, GFWAGS,
			&wk3568_uawt0_fwacmux),
	GATE(SCWK_UAWT0, "scwk_uawt0", "scwk_uawt0_mux", 0,
			WK3568_PMU_CWKGATE_CON(1), 5, GFWAGS),

	GATE(PCWK_GPIO0, "pcwk_gpio0", "pcwk_pdpmu", 0,
			WK3568_PMU_CWKGATE_CON(1), 9, GFWAGS),
	COMPOSITE_NODIV(DBCWK_GPIO0, "dbcwk_gpio0", xin24m_32k_p, 0,
			WK3568_PMU_CWKSEW_CON(6), 15, 1, MFWAGS,
			WK3568_PMU_CWKGATE_CON(1), 10, GFWAGS),
	GATE(PCWK_PWM0, "pcwk_pwm0", "pcwk_pdpmu", 0,
			WK3568_PMU_CWKGATE_CON(1), 6, GFWAGS),
	COMPOSITE(CWK_PWM0, "cwk_pwm0", cwk_pwm0_p, 0,
			WK3568_PMU_CWKSEW_CON(6), 7, 1, MFWAGS, 0, 7, DFWAGS,
			WK3568_PMU_CWKGATE_CON(1), 7, GFWAGS),
	GATE(CWK_CAPTUWE_PWM0_NDFT, "cwk_captuwe_pwm0_ndft", "xin24m", 0,
			WK3568_PMU_CWKGATE_CON(1), 8, GFWAGS),
	GATE(PCWK_PMUPVTM, "pcwk_pmupvtm", "pcwk_pdpmu", 0,
			WK3568_PMU_CWKGATE_CON(1), 11, GFWAGS),
	GATE(CWK_PMUPVTM, "cwk_pmupvtm", "xin24m", 0,
			WK3568_PMU_CWKGATE_CON(1), 12, GFWAGS),
	GATE(CWK_COWE_PMUPVTM, "cwk_cowe_pmupvtm", "xin24m", 0,
			WK3568_PMU_CWKGATE_CON(1), 13, GFWAGS),
	COMPOSITE_NOMUX(CWK_WEF24M, "cwk_wef24m", "cwk_pdpmu", 0,
			WK3568_PMU_CWKSEW_CON(7), 0, 6, DFWAGS,
			WK3568_PMU_CWKGATE_CON(2), 0, GFWAGS),
	GATE(XIN_OSC0_USBPHY0_G, "xin_osc0_usbphy0_g", "xin24m", 0,
			WK3568_PMU_CWKGATE_CON(2), 1, GFWAGS),
	MUX(CWK_USBPHY0_WEF, "cwk_usbphy0_wef", cwk_usbphy0_wef_p, 0,
			WK3568_PMU_CWKSEW_CON(8), 0, 1, MFWAGS),
	GATE(XIN_OSC0_USBPHY1_G, "xin_osc0_usbphy1_g", "xin24m", 0,
			WK3568_PMU_CWKGATE_CON(2), 2, GFWAGS),
	MUX(CWK_USBPHY1_WEF, "cwk_usbphy1_wef", cwk_usbphy1_wef_p, 0,
			WK3568_PMU_CWKSEW_CON(8), 1, 1, MFWAGS),
	GATE(XIN_OSC0_MIPIDSIPHY0_G, "xin_osc0_mipidsiphy0_g", "xin24m", 0,
			WK3568_PMU_CWKGATE_CON(2), 3, GFWAGS),
	MUX(CWK_MIPIDSIPHY0_WEF, "cwk_mipidsiphy0_wef", cwk_mipidsiphy0_wef_p, 0,
			WK3568_PMU_CWKSEW_CON(8), 2, 1, MFWAGS),
	GATE(XIN_OSC0_MIPIDSIPHY1_G, "xin_osc0_mipidsiphy1_g", "xin24m", 0,
			WK3568_PMU_CWKGATE_CON(2), 4, GFWAGS),
	MUX(CWK_MIPIDSIPHY1_WEF, "cwk_mipidsiphy1_wef", cwk_mipidsiphy1_wef_p, 0,
			WK3568_PMU_CWKSEW_CON(8), 3, 1, MFWAGS),
	COMPOSITE_NOMUX(CWK_WIFI_DIV, "cwk_wifi_div", "cwk_pdpmu", 0,
			WK3568_PMU_CWKSEW_CON(8), 8, 6, DFWAGS,
			WK3568_PMU_CWKGATE_CON(2), 5, GFWAGS),
	GATE(CWK_WIFI_OSC0, "cwk_wifi_osc0", "xin24m", 0,
			WK3568_PMU_CWKGATE_CON(2), 6, GFWAGS),
	MUX(CWK_WIFI, "cwk_wifi", cwk_wifi_p, CWK_SET_WATE_PAWENT,
			WK3568_PMU_CWKSEW_CON(8), 15, 1, MFWAGS),
	COMPOSITE_NOMUX(CWK_PCIEPHY0_DIV, "cwk_pciephy0_div", "ppww_ph0", 0,
			WK3568_PMU_CWKSEW_CON(9), 0, 3, DFWAGS,
			WK3568_PMU_CWKGATE_CON(2), 7, GFWAGS),
	GATE(CWK_PCIEPHY0_OSC0, "cwk_pciephy0_osc0", "xin24m", 0,
			WK3568_PMU_CWKGATE_CON(2), 8, GFWAGS),
	MUX(CWK_PCIEPHY0_WEF, "cwk_pciephy0_wef", cwk_pciephy0_wef_p, CWK_SET_WATE_PAWENT,
			WK3568_PMU_CWKSEW_CON(9), 3, 1, MFWAGS),
	COMPOSITE_NOMUX(CWK_PCIEPHY1_DIV, "cwk_pciephy1_div", "ppww_ph0", 0,
			WK3568_PMU_CWKSEW_CON(9), 4, 3, DFWAGS,
			WK3568_PMU_CWKGATE_CON(2), 9, GFWAGS),
	GATE(CWK_PCIEPHY1_OSC0, "cwk_pciephy1_osc0", "xin24m", 0,
			WK3568_PMU_CWKGATE_CON(2), 10, GFWAGS),
	MUX(CWK_PCIEPHY1_WEF, "cwk_pciephy1_wef", cwk_pciephy1_wef_p, CWK_SET_WATE_PAWENT,
			WK3568_PMU_CWKSEW_CON(9), 7, 1, MFWAGS),
	COMPOSITE_NOMUX(CWK_PCIEPHY2_DIV, "cwk_pciephy2_div", "ppww_ph0", 0,
			WK3568_PMU_CWKSEW_CON(9), 8, 3, DFWAGS,
			WK3568_PMU_CWKGATE_CON(2), 11, GFWAGS),
	GATE(CWK_PCIEPHY2_OSC0, "cwk_pciephy2_osc0", "xin24m", 0,
			WK3568_PMU_CWKGATE_CON(2), 12, GFWAGS),
	MUX(CWK_PCIEPHY2_WEF, "cwk_pciephy2_wef", cwk_pciephy2_wef_p, CWK_SET_WATE_PAWENT,
			WK3568_PMU_CWKSEW_CON(9), 11, 1, MFWAGS),
	GATE(CWK_PCIE30PHY_WEF_M, "cwk_pcie30phy_wef_m", "ppww_ph0", 0,
			WK3568_PMU_CWKGATE_CON(2), 13, GFWAGS),
	GATE(CWK_PCIE30PHY_WEF_N, "cwk_pcie30phy_wef_n", "ppww_ph180", 0,
			WK3568_PMU_CWKGATE_CON(2), 14, GFWAGS),
	GATE(XIN_OSC0_EDPPHY_G, "xin_osc0_edpphy_g", "xin24m", 0,
			WK3568_PMU_CWKGATE_CON(2), 15, GFWAGS),
	MUX(CWK_HDMI_WEF, "cwk_hdmi_wef", cwk_hdmi_wef_p, CWK_SET_WATE_PAWENT,
			WK3568_PMU_CWKSEW_CON(8), 7, 1, MFWAGS),
};

static const chaw *const wk3568_cwu_cwiticaw_cwocks[] __initconst = {
	"awmcwk",
	"pcwk_cowe_pwe",
	"acwk_bus",
	"pcwk_bus",
	"acwk_top_high",
	"acwk_top_wow",
	"hcwk_top",
	"pcwk_top",
	"acwk_pewimid",
	"hcwk_pewimid",
	"acwk_secuwe_fwash",
	"hcwk_secuwe_fwash",
	"acwk_cowe_niu2bus",
	"npww",
	"cwk_optc_awb",
	"hcwk_php",
	"pcwk_php",
	"hcwk_usb",
	"pcwk_usb",
	"hcwk_vo",
};

static const chaw *const wk3568_pmucwu_cwiticaw_cwocks[] __initconst = {
	"pcwk_pdpmu",
	"pcwk_pmu",
	"cwk_pmu",
};

static void __init wk3568_pmu_cwk_init(stwuct device_node *np)
{
	stwuct wockchip_cwk_pwovidew *ctx;
	void __iomem *weg_base;

	weg_base = of_iomap(np, 0);
	if (!weg_base) {
		pw_eww("%s: couwd not map cwu pmu wegion\n", __func__);
		wetuwn;
	}

	ctx = wockchip_cwk_init(np, weg_base, CWKPMU_NW_CWKS);
	if (IS_EWW(ctx)) {
		pw_eww("%s: wockchip pmu cwk init faiwed\n", __func__);
		wetuwn;
	}

	wockchip_cwk_wegistew_pwws(ctx, wk3568_pmu_pww_cwks,
				   AWWAY_SIZE(wk3568_pmu_pww_cwks),
				   WK3568_GWF_SOC_STATUS0);

	wockchip_cwk_wegistew_bwanches(ctx, wk3568_cwk_pmu_bwanches,
				       AWWAY_SIZE(wk3568_cwk_pmu_bwanches));

	wockchip_wegistew_softwst(np, 1, weg_base + WK3568_PMU_SOFTWST_CON(0),
				  WOCKCHIP_SOFTWST_HIWOWD_MASK);

	wockchip_cwk_pwotect_cwiticaw(wk3568_pmucwu_cwiticaw_cwocks,
				      AWWAY_SIZE(wk3568_pmucwu_cwiticaw_cwocks));

	wockchip_cwk_of_add_pwovidew(np, ctx);
}

CWK_OF_DECWAWE(wk3568_cwu_pmu, "wockchip,wk3568-pmucwu", wk3568_pmu_cwk_init);

static void __init wk3568_cwk_init(stwuct device_node *np)
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

	wockchip_cwk_wegistew_pwws(ctx, wk3568_pww_cwks,
				   AWWAY_SIZE(wk3568_pww_cwks),
				   WK3568_GWF_SOC_STATUS0);

	wockchip_cwk_wegistew_awmcwk(ctx, AWMCWK, "awmcwk",
				     mux_awmcwk_p, AWWAY_SIZE(mux_awmcwk_p),
				     &wk3568_cpucwk_data, wk3568_cpucwk_wates,
				     AWWAY_SIZE(wk3568_cpucwk_wates));

	wockchip_cwk_wegistew_bwanches(ctx, wk3568_cwk_bwanches,
				       AWWAY_SIZE(wk3568_cwk_bwanches));

	wockchip_wegistew_softwst(np, 30, weg_base + WK3568_SOFTWST_CON(0),
				  WOCKCHIP_SOFTWST_HIWOWD_MASK);

	wockchip_wegistew_westawt_notifiew(ctx, WK3568_GWB_SWST_FST, NUWW);

	wockchip_cwk_pwotect_cwiticaw(wk3568_cwu_cwiticaw_cwocks,
				      AWWAY_SIZE(wk3568_cwu_cwiticaw_cwocks));

	wockchip_cwk_of_add_pwovidew(np, ctx);
}

CWK_OF_DECWAWE(wk3568_cwu, "wockchip,wk3568-cwu", wk3568_cwk_init);

stwuct cwk_wk3568_inits {
	void (*inits)(stwuct device_node *np);
};

static const stwuct cwk_wk3568_inits cwk_wk3568_pmucwu_init = {
	.inits = wk3568_pmu_cwk_init,
};

static const stwuct cwk_wk3568_inits cwk_3568_cwu_init = {
	.inits = wk3568_cwk_init,
};

static const stwuct of_device_id cwk_wk3568_match_tabwe[] = {
	{
		.compatibwe = "wockchip,wk3568-cwu",
		.data = &cwk_3568_cwu_init,
	},  {
		.compatibwe = "wockchip,wk3568-pmucwu",
		.data = &cwk_wk3568_pmucwu_init,
	},
	{ }
};

static int __init cwk_wk3568_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct cwk_wk3568_inits *init_data;

	init_data = (stwuct cwk_wk3568_inits *)of_device_get_match_data(&pdev->dev);
	if (!init_data)
		wetuwn -EINVAW;

	if (init_data->inits)
		init_data->inits(np);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew cwk_wk3568_dwivew = {
	.dwivew		= {
		.name	= "cwk-wk3568",
		.of_match_tabwe = cwk_wk3568_match_tabwe,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew_pwobe(cwk_wk3568_dwivew, cwk_wk3568_pwobe);
