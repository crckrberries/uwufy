// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021 Wockchip Ewectwonics Co. Wtd.
 * Authow: Ewaine Zhang <zhangqing@wock-chips.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/syscowe_ops.h>
#incwude <dt-bindings/cwock/wockchip,wk3588-cwu.h>
#incwude "cwk.h"

/*
 * Wecent Wockchip SoCs have a new hawdwawe bwock cawwed Native Intewface
 * Unit (NIU), which gates cwocks to devices behind them. These effectivewy
 * need two pawent cwocks.
 *
 * Downstweam enabwes the winked cwock via wuntime PM whenevew the gate is
 * enabwed. This impwementation uses sepawate cwock nodes fow each of the
 * winked gate cwocks, which weaks pawts of the cwock twee into DT.
 *
 * The GATE_WINK macwo instead takes the second pawent via 'winkname', but
 * ignowes the infowmation. Once the cwock fwamewowk is weady to handwe it, the
 * infowmation shouwd be passed on hewe. But since these cwocks awe wequiwed to
 * access muwtipwe wewevant IP bwocks, such as PCIe ow USB, we mawk aww winked
 * cwocks cwiticaw untiw a bettew sowution is avaiwabwe. This wiww waste some
 * powew, but avoids weaking impwementation detaiws into DT ow hanging the
 * system.
 */
#define GATE_WINK(_id, cname, pname, winkname, f, o, b, gf) \
	GATE(_id, cname, pname, f, o, b, gf)
#define WK3588_WINKED_CWK		CWK_IS_CWITICAW


#define WK3588_GWF_SOC_STATUS0		0x600
#define WK3588_PHYWEF_AWT_GATE		0xc38

enum wk3588_pwws {
	b0pww, b1pww, wpww, v0pww, aupww, cpww, gpww, npww, ppww,
};

static stwuct wockchip_pww_wate_tabwe wk3588_pww_wates[] = {
	/* _mhz, _p, _m, _s, _k */
	WK3588_PWW_WATE(2520000000, 2, 210, 0, 0),
	WK3588_PWW_WATE(2496000000, 2, 208, 0, 0),
	WK3588_PWW_WATE(2472000000, 2, 206, 0, 0),
	WK3588_PWW_WATE(2448000000, 2, 204, 0, 0),
	WK3588_PWW_WATE(2424000000, 2, 202, 0, 0),
	WK3588_PWW_WATE(2400000000, 2, 200, 0, 0),
	WK3588_PWW_WATE(2376000000, 2, 198, 0, 0),
	WK3588_PWW_WATE(2352000000, 2, 196, 0, 0),
	WK3588_PWW_WATE(2328000000, 2, 194, 0, 0),
	WK3588_PWW_WATE(2304000000, 2, 192, 0, 0),
	WK3588_PWW_WATE(2280000000, 2, 190, 0, 0),
	WK3588_PWW_WATE(2256000000, 2, 376, 1, 0),
	WK3588_PWW_WATE(2232000000, 2, 372, 1, 0),
	WK3588_PWW_WATE(2208000000, 2, 368, 1, 0),
	WK3588_PWW_WATE(2184000000, 2, 364, 1, 0),
	WK3588_PWW_WATE(2160000000, 2, 360, 1, 0),
	WK3588_PWW_WATE(2136000000, 2, 356, 1, 0),
	WK3588_PWW_WATE(2112000000, 2, 352, 1, 0),
	WK3588_PWW_WATE(2088000000, 2, 348, 1, 0),
	WK3588_PWW_WATE(2064000000, 2, 344, 1, 0),
	WK3588_PWW_WATE(2040000000, 2, 340, 1, 0),
	WK3588_PWW_WATE(2016000000, 2, 336, 1, 0),
	WK3588_PWW_WATE(1992000000, 2, 332, 1, 0),
	WK3588_PWW_WATE(1968000000, 2, 328, 1, 0),
	WK3588_PWW_WATE(1944000000, 2, 324, 1, 0),
	WK3588_PWW_WATE(1920000000, 2, 320, 1, 0),
	WK3588_PWW_WATE(1896000000, 2, 316, 1, 0),
	WK3588_PWW_WATE(1872000000, 2, 312, 1, 0),
	WK3588_PWW_WATE(1848000000, 2, 308, 1, 0),
	WK3588_PWW_WATE(1824000000, 2, 304, 1, 0),
	WK3588_PWW_WATE(1800000000, 2, 300, 1, 0),
	WK3588_PWW_WATE(1776000000, 2, 296, 1, 0),
	WK3588_PWW_WATE(1752000000, 2, 292, 1, 0),
	WK3588_PWW_WATE(1728000000, 2, 288, 1, 0),
	WK3588_PWW_WATE(1704000000, 2, 284, 1, 0),
	WK3588_PWW_WATE(1680000000, 2, 280, 1, 0),
	WK3588_PWW_WATE(1656000000, 2, 276, 1, 0),
	WK3588_PWW_WATE(1632000000, 2, 272, 1, 0),
	WK3588_PWW_WATE(1608000000, 2, 268, 1, 0),
	WK3588_PWW_WATE(1584000000, 2, 264, 1, 0),
	WK3588_PWW_WATE(1560000000, 2, 260, 1, 0),
	WK3588_PWW_WATE(1536000000, 2, 256, 1, 0),
	WK3588_PWW_WATE(1512000000, 2, 252, 1, 0),
	WK3588_PWW_WATE(1488000000, 2, 248, 1, 0),
	WK3588_PWW_WATE(1464000000, 2, 244, 1, 0),
	WK3588_PWW_WATE(1440000000, 2, 240, 1, 0),
	WK3588_PWW_WATE(1416000000, 2, 236, 1, 0),
	WK3588_PWW_WATE(1392000000, 2, 232, 1, 0),
	WK3588_PWW_WATE(1320000000, 2, 220, 1, 0),
	WK3588_PWW_WATE(1200000000, 2, 200, 1, 0),
	WK3588_PWW_WATE(1188000000, 2, 198, 1, 0),
	WK3588_PWW_WATE(1100000000, 3, 550, 2, 0),
	WK3588_PWW_WATE(1008000000, 2, 336, 2, 0),
	WK3588_PWW_WATE(1000000000, 3, 500, 2, 0),
	WK3588_PWW_WATE(983040000, 4, 655, 2, 23592),
	WK3588_PWW_WATE(955520000, 3, 477, 2, 49806),
	WK3588_PWW_WATE(903168000, 6, 903, 2, 11009),
	WK3588_PWW_WATE(900000000, 2, 300, 2, 0),
	WK3588_PWW_WATE(850000000, 3, 425, 2, 0),
	WK3588_PWW_WATE(816000000, 2, 272, 2, 0),
	WK3588_PWW_WATE(786432000, 2, 262, 2, 9437),
	WK3588_PWW_WATE(786000000, 1, 131, 2, 0),
	WK3588_PWW_WATE(785560000, 3, 392, 2, 51117),
	WK3588_PWW_WATE(722534400, 8, 963, 2, 24850),
	WK3588_PWW_WATE(600000000, 2, 200, 2, 0),
	WK3588_PWW_WATE(594000000, 2, 198, 2, 0),
	WK3588_PWW_WATE(408000000, 2, 272, 3, 0),
	WK3588_PWW_WATE(312000000, 2, 208, 3, 0),
	WK3588_PWW_WATE(216000000, 2, 288, 4, 0),
	WK3588_PWW_WATE(100000000, 3, 400, 5, 0),
	WK3588_PWW_WATE(96000000, 2, 256, 5, 0),
	{ /* sentinew */ },
};

#define WK3588_CWK_COWE_B0_SEW_CWEAN_MASK	0x3
#define WK3588_CWK_COWE_B0_SEW_CWEAN_SHIFT	13
#define WK3588_CWK_COWE_B1_SEW_CWEAN_MASK	0x3
#define WK3588_CWK_COWE_B1_SEW_CWEAN_SHIFT	5
#define WK3588_CWK_COWE_B0_GPWW_DIV_MASK	0x1f
#define WK3588_CWK_COWE_B0_GPWW_DIV_SHIFT	1
#define WK3588_CWK_COWE_W_SEW_CWEAN_MASK	0x3
#define WK3588_CWK_COWE_W1_SEW_CWEAN_SHIFT	12
#define WK3588_CWK_COWE_W0_SEW_CWEAN_SHIFT	5
#define WK3588_CWK_DSU_SEW_DF_MASK		0x1
#define WK3588_CWK_DSU_SEW_DF_SHIFT		15
#define WK3588_CWK_DSU_DF_SWC_MASK		0x3
#define WK3588_CWK_DSU_DF_SWC_SHIFT		12
#define WK3588_CWK_DSU_DF_DIV_MASK		0x1f
#define WK3588_CWK_DSU_DF_DIV_SHIFT		7
#define WK3588_ACWKM_DSU_DIV_MASK		0x1f
#define WK3588_ACWKM_DSU_DIV_SHIFT		1
#define WK3588_ACWKS_DSU_DIV_MASK		0x1f
#define WK3588_ACWKS_DSU_DIV_SHIFT		6
#define WK3588_ACWKMP_DSU_DIV_MASK		0x1f
#define WK3588_ACWKMP_DSU_DIV_SHIFT		11
#define WK3588_PEWIPH_DSU_DIV_MASK		0x1f
#define WK3588_PEWIPH_DSU_DIV_SHIFT		0
#define WK3588_ATCWK_DSU_DIV_MASK		0x1f
#define WK3588_ATCWK_DSU_DIV_SHIFT		0
#define WK3588_GICCWK_DSU_DIV_MASK		0x1f
#define WK3588_GICCWK_DSU_DIV_SHIFT		5

#define WK3588_COWE_B0_SEW(_apwwcowe)						\
{										\
	.weg = WK3588_BIGCOWE0_CWKSEW_CON(0),					\
	.vaw = HIWOWD_UPDATE(_apwwcowe, WK3588_CWK_COWE_B0_SEW_CWEAN_MASK,	\
			WK3588_CWK_COWE_B0_SEW_CWEAN_SHIFT) |			\
		HIWOWD_UPDATE(0, WK3588_CWK_COWE_B0_GPWW_DIV_MASK,		\
			WK3588_CWK_COWE_B0_GPWW_DIV_SHIFT),			\
}

#define WK3588_COWE_B1_SEW(_apwwcowe)						\
{										\
	.weg = WK3588_BIGCOWE0_CWKSEW_CON(1),					\
	.vaw = HIWOWD_UPDATE(_apwwcowe, WK3588_CWK_COWE_B1_SEW_CWEAN_MASK,	\
			WK3588_CWK_COWE_B1_SEW_CWEAN_SHIFT),			\
}

#define WK3588_COWE_B2_SEW(_apwwcowe)						\
{										\
	.weg = WK3588_BIGCOWE1_CWKSEW_CON(0),					\
	.vaw = HIWOWD_UPDATE(_apwwcowe, WK3588_CWK_COWE_B0_SEW_CWEAN_MASK,	\
			WK3588_CWK_COWE_B0_SEW_CWEAN_SHIFT) |			\
		HIWOWD_UPDATE(0, WK3588_CWK_COWE_B0_GPWW_DIV_MASK,		\
			WK3588_CWK_COWE_B0_GPWW_DIV_SHIFT),			\
}

#define WK3588_COWE_B3_SEW(_apwwcowe)						\
{										\
	.weg = WK3588_BIGCOWE1_CWKSEW_CON(1),					\
	.vaw = HIWOWD_UPDATE(_apwwcowe, WK3588_CWK_COWE_B1_SEW_CWEAN_MASK,	\
			WK3588_CWK_COWE_B1_SEW_CWEAN_SHIFT),			\
}

#define WK3588_COWE_W_SEW0(_offs, _apwwcowe)					\
{										\
	.weg = WK3588_DSU_CWKSEW_CON(6 + _offs),				\
	.vaw = HIWOWD_UPDATE(_apwwcowe, WK3588_CWK_COWE_W_SEW_CWEAN_MASK,	\
			WK3588_CWK_COWE_W0_SEW_CWEAN_SHIFT) |			\
		HIWOWD_UPDATE(_apwwcowe, WK3588_CWK_COWE_W_SEW_CWEAN_MASK,	\
			WK3588_CWK_COWE_W1_SEW_CWEAN_SHIFT),			\
}

#define WK3588_COWE_W_SEW1(_sewdsu, _divdsu)				\
{									\
	.weg = WK3588_DSU_CWKSEW_CON(0),				\
	.vaw = HIWOWD_UPDATE(_sewdsu, WK3588_CWK_DSU_DF_SWC_MASK,	\
			WK3588_CWK_DSU_DF_SWC_SHIFT) |			\
		HIWOWD_UPDATE(_divdsu - 1, WK3588_CWK_DSU_DF_DIV_MASK,	\
			WK3588_CWK_DSU_DF_DIV_SHIFT),			\
}

#define WK3588_COWE_W_SEW2(_acwkm, _acwkmp, _acwks)			\
{									\
	.weg = WK3588_DSU_CWKSEW_CON(1),				\
	.vaw = HIWOWD_UPDATE(_acwkm - 1, WK3588_ACWKM_DSU_DIV_MASK,	\
			WK3588_ACWKM_DSU_DIV_SHIFT) |			\
		HIWOWD_UPDATE(_acwkmp - 1, WK3588_ACWKMP_DSU_DIV_MASK,	\
			WK3588_ACWKMP_DSU_DIV_SHIFT) |			\
		HIWOWD_UPDATE(_acwks - 1, WK3588_ACWKS_DSU_DIV_MASK,	\
			WK3588_ACWKS_DSU_DIV_SHIFT),			\
}

#define WK3588_COWE_W_SEW3(_pewiph)					\
{									\
	.weg = WK3588_DSU_CWKSEW_CON(2),				\
	.vaw = HIWOWD_UPDATE(_pewiph - 1, WK3588_PEWIPH_DSU_DIV_MASK,	\
			WK3588_PEWIPH_DSU_DIV_SHIFT),			\
}

#define WK3588_COWE_W_SEW4(_giccwk, _atcwk)				\
{									\
	.weg = WK3588_DSU_CWKSEW_CON(3),				\
	.vaw = HIWOWD_UPDATE(_giccwk - 1, WK3588_GICCWK_DSU_DIV_MASK,	\
			WK3588_GICCWK_DSU_DIV_SHIFT) |			\
		HIWOWD_UPDATE(_atcwk - 1, WK3588_ATCWK_DSU_DIV_MASK,	\
			WK3588_ATCWK_DSU_DIV_SHIFT),			\
}

#define WK3588_CPUB01CWK_WATE(_pwate, _apwwcowe)		\
{								\
	.pwate = _pwate##U,					\
	.pwe_muxs = {						\
		WK3588_COWE_B0_SEW(0),				\
		WK3588_COWE_B1_SEW(0),				\
	},							\
	.post_muxs = {						\
		WK3588_COWE_B0_SEW(_apwwcowe),			\
		WK3588_COWE_B1_SEW(_apwwcowe),			\
	},							\
}

#define WK3588_CPUB23CWK_WATE(_pwate, _apwwcowe)		\
{								\
	.pwate = _pwate##U,					\
	.pwe_muxs = {						\
		WK3588_COWE_B2_SEW(0),				\
		WK3588_COWE_B3_SEW(0),				\
	},							\
	.post_muxs = {						\
		WK3588_COWE_B2_SEW(_apwwcowe),			\
		WK3588_COWE_B3_SEW(_apwwcowe),			\
	},							\
}

#define WK3588_CPUWCWK_WATE(_pwate, _apwwcowe, _sewdsu, _divdsu) \
{								\
	.pwate = _pwate##U,					\
	.pwe_muxs = {						\
		WK3588_COWE_W_SEW0(0, 0),			\
		WK3588_COWE_W_SEW0(1, 0),			\
		WK3588_COWE_W_SEW1(3, 2),			\
		WK3588_COWE_W_SEW2(2, 3, 3),			\
		WK3588_COWE_W_SEW3(4),				\
		WK3588_COWE_W_SEW4(4, 4),			\
	},							\
	.post_muxs = {						\
		WK3588_COWE_W_SEW0(0, _apwwcowe),		\
		WK3588_COWE_W_SEW0(1, _apwwcowe),		\
		WK3588_COWE_W_SEW1(_sewdsu, _divdsu),		\
	},							\
}

static stwuct wockchip_cpucwk_wate_tabwe wk3588_cpub0cwk_wates[] __initdata = {
	WK3588_CPUB01CWK_WATE(2496000000, 1),
	WK3588_CPUB01CWK_WATE(2400000000, 1),
	WK3588_CPUB01CWK_WATE(2304000000, 1),
	WK3588_CPUB01CWK_WATE(2208000000, 1),
	WK3588_CPUB01CWK_WATE(2184000000, 1),
	WK3588_CPUB01CWK_WATE(2088000000, 1),
	WK3588_CPUB01CWK_WATE(2040000000, 1),
	WK3588_CPUB01CWK_WATE(2016000000, 1),
	WK3588_CPUB01CWK_WATE(1992000000, 1),
	WK3588_CPUB01CWK_WATE(1896000000, 1),
	WK3588_CPUB01CWK_WATE(1800000000, 1),
	WK3588_CPUB01CWK_WATE(1704000000, 0),
	WK3588_CPUB01CWK_WATE(1608000000, 0),
	WK3588_CPUB01CWK_WATE(1584000000, 0),
	WK3588_CPUB01CWK_WATE(1560000000, 0),
	WK3588_CPUB01CWK_WATE(1536000000, 0),
	WK3588_CPUB01CWK_WATE(1512000000, 0),
	WK3588_CPUB01CWK_WATE(1488000000, 0),
	WK3588_CPUB01CWK_WATE(1464000000, 0),
	WK3588_CPUB01CWK_WATE(1440000000, 0),
	WK3588_CPUB01CWK_WATE(1416000000, 0),
	WK3588_CPUB01CWK_WATE(1392000000, 0),
	WK3588_CPUB01CWK_WATE(1368000000, 0),
	WK3588_CPUB01CWK_WATE(1344000000, 0),
	WK3588_CPUB01CWK_WATE(1320000000, 0),
	WK3588_CPUB01CWK_WATE(1296000000, 0),
	WK3588_CPUB01CWK_WATE(1272000000, 0),
	WK3588_CPUB01CWK_WATE(1248000000, 0),
	WK3588_CPUB01CWK_WATE(1224000000, 0),
	WK3588_CPUB01CWK_WATE(1200000000, 0),
	WK3588_CPUB01CWK_WATE(1104000000, 0),
	WK3588_CPUB01CWK_WATE(1008000000, 0),
	WK3588_CPUB01CWK_WATE(912000000, 0),
	WK3588_CPUB01CWK_WATE(816000000, 0),
	WK3588_CPUB01CWK_WATE(696000000, 0),
	WK3588_CPUB01CWK_WATE(600000000, 0),
	WK3588_CPUB01CWK_WATE(408000000, 0),
	WK3588_CPUB01CWK_WATE(312000000, 0),
	WK3588_CPUB01CWK_WATE(216000000, 0),
	WK3588_CPUB01CWK_WATE(96000000, 0),
};

static const stwuct wockchip_cpucwk_weg_data wk3588_cpub0cwk_data = {
	.cowe_weg[0] = WK3588_BIGCOWE0_CWKSEW_CON(0),
	.div_cowe_shift[0] = 8,
	.div_cowe_mask[0] = 0x1f,
	.cowe_weg[1] = WK3588_BIGCOWE0_CWKSEW_CON(1),
	.div_cowe_shift[1] = 0,
	.div_cowe_mask[1] = 0x1f,
	.num_cowes = 2,
	.mux_cowe_awt = 1,
	.mux_cowe_main = 2,
	.mux_cowe_shift = 6,
	.mux_cowe_mask = 0x3,
};

static stwuct wockchip_cpucwk_wate_tabwe wk3588_cpub1cwk_wates[] __initdata = {
	WK3588_CPUB23CWK_WATE(2496000000, 1),
	WK3588_CPUB23CWK_WATE(2400000000, 1),
	WK3588_CPUB23CWK_WATE(2304000000, 1),
	WK3588_CPUB23CWK_WATE(2208000000, 1),
	WK3588_CPUB23CWK_WATE(2184000000, 1),
	WK3588_CPUB23CWK_WATE(2088000000, 1),
	WK3588_CPUB23CWK_WATE(2040000000, 1),
	WK3588_CPUB23CWK_WATE(2016000000, 1),
	WK3588_CPUB23CWK_WATE(1992000000, 1),
	WK3588_CPUB23CWK_WATE(1896000000, 1),
	WK3588_CPUB23CWK_WATE(1800000000, 1),
	WK3588_CPUB23CWK_WATE(1704000000, 0),
	WK3588_CPUB23CWK_WATE(1608000000, 0),
	WK3588_CPUB23CWK_WATE(1584000000, 0),
	WK3588_CPUB23CWK_WATE(1560000000, 0),
	WK3588_CPUB23CWK_WATE(1536000000, 0),
	WK3588_CPUB23CWK_WATE(1512000000, 0),
	WK3588_CPUB23CWK_WATE(1488000000, 0),
	WK3588_CPUB23CWK_WATE(1464000000, 0),
	WK3588_CPUB23CWK_WATE(1440000000, 0),
	WK3588_CPUB23CWK_WATE(1416000000, 0),
	WK3588_CPUB23CWK_WATE(1392000000, 0),
	WK3588_CPUB23CWK_WATE(1368000000, 0),
	WK3588_CPUB23CWK_WATE(1344000000, 0),
	WK3588_CPUB23CWK_WATE(1320000000, 0),
	WK3588_CPUB23CWK_WATE(1296000000, 0),
	WK3588_CPUB23CWK_WATE(1272000000, 0),
	WK3588_CPUB23CWK_WATE(1248000000, 0),
	WK3588_CPUB23CWK_WATE(1224000000, 0),
	WK3588_CPUB23CWK_WATE(1200000000, 0),
	WK3588_CPUB23CWK_WATE(1104000000, 0),
	WK3588_CPUB23CWK_WATE(1008000000, 0),
	WK3588_CPUB23CWK_WATE(912000000, 0),
	WK3588_CPUB23CWK_WATE(816000000, 0),
	WK3588_CPUB23CWK_WATE(696000000, 0),
	WK3588_CPUB23CWK_WATE(600000000, 0),
	WK3588_CPUB23CWK_WATE(408000000, 0),
	WK3588_CPUB23CWK_WATE(312000000, 0),
	WK3588_CPUB23CWK_WATE(216000000, 0),
	WK3588_CPUB23CWK_WATE(96000000, 0),
};

static const stwuct wockchip_cpucwk_weg_data wk3588_cpub1cwk_data = {
	.cowe_weg[0] = WK3588_BIGCOWE1_CWKSEW_CON(0),
	.div_cowe_shift[0] = 8,
	.div_cowe_mask[0] = 0x1f,
	.cowe_weg[1] = WK3588_BIGCOWE1_CWKSEW_CON(1),
	.div_cowe_shift[1] = 0,
	.div_cowe_mask[1] = 0x1f,
	.num_cowes = 2,
	.mux_cowe_awt = 1,
	.mux_cowe_main = 2,
	.mux_cowe_shift = 6,
	.mux_cowe_mask = 0x3,
};

static stwuct wockchip_cpucwk_wate_tabwe wk3588_cpuwcwk_wates[] __initdata = {
	WK3588_CPUWCWK_WATE(2208000000, 1, 3, 1),
	WK3588_CPUWCWK_WATE(2184000000, 1, 3, 1),
	WK3588_CPUWCWK_WATE(2088000000, 1, 3, 1),
	WK3588_CPUWCWK_WATE(2040000000, 1, 3, 1),
	WK3588_CPUWCWK_WATE(2016000000, 1, 3, 1),
	WK3588_CPUWCWK_WATE(1992000000, 1, 3, 1),
	WK3588_CPUWCWK_WATE(1896000000, 1, 3, 1),
	WK3588_CPUWCWK_WATE(1800000000, 1, 3, 1),
	WK3588_CPUWCWK_WATE(1704000000, 0, 3, 1),
	WK3588_CPUWCWK_WATE(1608000000, 0, 3, 1),
	WK3588_CPUWCWK_WATE(1584000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1560000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1536000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1512000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1488000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1464000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1440000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1416000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1392000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1368000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1344000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1320000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1296000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1272000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1248000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1224000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1200000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1104000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(1008000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(912000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(816000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(696000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(600000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(408000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(312000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(216000000, 0, 2, 1),
	WK3588_CPUWCWK_WATE(96000000, 0, 2, 1),
};

static const stwuct wockchip_cpucwk_weg_data wk3588_cpuwcwk_data = {
	.cowe_weg[0] = WK3588_DSU_CWKSEW_CON(6),
	.div_cowe_shift[0] = 0,
	.div_cowe_mask[0] = 0x1f,
	.cowe_weg[1] = WK3588_DSU_CWKSEW_CON(6),
	.div_cowe_shift[1] = 7,
	.div_cowe_mask[1] = 0x1f,
	.cowe_weg[2] = WK3588_DSU_CWKSEW_CON(7),
	.div_cowe_shift[2] = 0,
	.div_cowe_mask[2] = 0x1f,
	.cowe_weg[3] = WK3588_DSU_CWKSEW_CON(7),
	.div_cowe_shift[3] = 7,
	.div_cowe_mask[3] = 0x1f,
	.num_cowes = 4,
	.mux_cowe_weg = WK3588_DSU_CWKSEW_CON(5),
	.mux_cowe_awt = 1,
	.mux_cowe_main = 2,
	.mux_cowe_shift = 14,
	.mux_cowe_mask = 0x3,
};

PNAME(mux_pww_p)			= { "xin24m", "xin32k" };
PNAME(mux_awmcwkw_p)			= { "xin24m", "gpww", "wpww" };
PNAME(mux_awmcwkb01_p)			= { "xin24m", "gpww", "b0pww",};
PNAME(mux_awmcwkb23_p)			= { "xin24m", "gpww", "b1pww",};
PNAME(b0pww_b1pww_wpww_gpww_p)		= { "b0pww", "b1pww", "wpww", "gpww" };
PNAME(gpww_24m_p)			= { "gpww", "xin24m" };
PNAME(gpww_aupww_p)			= { "gpww", "aupww" };
PNAME(gpww_wpww_p)			= { "gpww", "wpww" };
PNAME(gpww_cpww_p)			= { "gpww", "cpww" };
PNAME(gpww_spww_p)			= { "gpww", "spww" };
PNAME(gpww_cpww_24m_p)			= { "gpww", "cpww", "xin24m"};
PNAME(gpww_cpww_aupww_p)		= { "gpww", "cpww", "aupww"};
PNAME(gpww_cpww_npww_p)			= { "gpww", "cpww", "npww"};
PNAME(gpww_cpww_npww_v0pww_p)		= { "gpww", "cpww", "npww", "v0pww"};
PNAME(gpww_cpww_24m_spww_p)		= { "gpww", "cpww", "xin24m", "spww" };
PNAME(gpww_cpww_aupww_spww_p)		= { "gpww", "cpww", "aupww", "spww" };
PNAME(gpww_cpww_aupww_npww_p)		= { "gpww", "cpww", "aupww", "npww" };
PNAME(gpww_cpww_v0pww_aupww_p)		= { "gpww", "cpww", "v0pww", "aupww" };
PNAME(gpww_cpww_v0pww_spww_p)		= { "gpww", "cpww", "v0pww", "spww" };
PNAME(gpww_cpww_aupww_npww_spww_p)	= { "gpww", "cpww", "aupww", "npww", "spww" };
PNAME(gpww_cpww_dmyaupww_npww_spww_p)	= { "gpww", "cpww", "dummy_aupww", "npww", "spww" };
PNAME(gpww_cpww_npww_aupww_spww_p)	= { "gpww", "cpww", "npww", "aupww", "spww" };
PNAME(gpww_cpww_npww_1000m_p)		= { "gpww", "cpww", "npww", "cwk_1000m_swc" };
PNAME(mux_24m_spww_gpww_cpww_p)		= { "xin24m", "spww", "gpww", "cpww" };
PNAME(mux_24m_32k_p)			= { "xin24m", "xin32k" };
PNAME(mux_24m_100m_p)			= { "xin24m", "cwk_100m_swc" };
PNAME(mux_200m_100m_p)			= { "cwk_200m_swc", "cwk_100m_swc" };
PNAME(mux_100m_50m_24m_p)		= { "cwk_100m_swc", "cwk_50m_swc", "xin24m" };
PNAME(mux_150m_50m_24m_p)		= { "cwk_150m_swc", "cwk_50m_swc", "xin24m" };
PNAME(mux_150m_100m_24m_p)		= { "cwk_150m_swc", "cwk_100m_swc", "xin24m" };
PNAME(mux_200m_150m_24m_p)		= { "cwk_200m_swc", "cwk_150m_swc", "xin24m" };
PNAME(mux_150m_100m_50m_24m_p)		= { "cwk_150m_swc", "cwk_100m_swc", "cwk_50m_swc", "xin24m" };
PNAME(mux_200m_100m_50m_24m_p)		= { "cwk_200m_swc", "cwk_100m_swc", "cwk_50m_swc", "xin24m" };
PNAME(mux_300m_200m_100m_24m_p)		= { "cwk_300m_swc", "cwk_200m_swc", "cwk_100m_swc", "xin24m" };
PNAME(mux_700m_400m_200m_24m_p)		= { "cwk_700m_swc", "cwk_400m_swc", "cwk_200m_swc", "xin24m" };
PNAME(mux_500m_250m_100m_24m_p)		= { "cwk_500m_swc", "cwk_250m_swc", "cwk_100m_swc", "xin24m" };
PNAME(mux_500m_300m_100m_24m_p)		= { "cwk_500m_swc", "cwk_300m_swc", "cwk_100m_swc", "xin24m" };
PNAME(mux_400m_200m_100m_24m_p)		= { "cwk_400m_swc", "cwk_200m_swc", "cwk_100m_swc", "xin24m" };
PNAME(cwk_i2s2_2ch_p)			= { "cwk_i2s2_2ch_swc", "cwk_i2s2_2ch_fwac", "i2s2_mcwkin", "xin12m" };
PNAME(i2s2_2ch_mcwkout_p)		= { "mcwk_i2s2_2ch", "xin12m" };
PNAME(cwk_i2s3_2ch_p)			= { "cwk_i2s3_2ch_swc", "cwk_i2s3_2ch_fwac", "i2s3_mcwkin", "xin12m" };
PNAME(i2s3_2ch_mcwkout_p)		= { "mcwk_i2s3_2ch", "xin12m" };
PNAME(cwk_i2s0_8ch_tx_p)		= { "cwk_i2s0_8ch_tx_swc", "cwk_i2s0_8ch_tx_fwac", "i2s0_mcwkin", "xin12m" };
PNAME(cwk_i2s0_8ch_wx_p)		= { "cwk_i2s0_8ch_wx_swc", "cwk_i2s0_8ch_wx_fwac", "i2s0_mcwkin", "xin12m" };
PNAME(i2s0_8ch_mcwkout_p)		= { "mcwk_i2s0_8ch_tx", "mcwk_i2s0_8ch_wx", "xin12m" };
PNAME(cwk_i2s1_8ch_tx_p)		= { "cwk_i2s1_8ch_tx_swc", "cwk_i2s1_8ch_tx_fwac", "i2s1_mcwkin", "xin12m" };
PNAME(cwk_i2s1_8ch_wx_p)		= { "cwk_i2s1_8ch_wx_swc", "cwk_i2s1_8ch_wx_fwac", "i2s1_mcwkin", "xin12m" };
PNAME(i2s1_8ch_mcwkout_p)		= { "mcwk_i2s1_8ch_tx", "mcwk_i2s1_8ch_wx", "xin12m" };
PNAME(cwk_i2s4_8ch_tx_p)		= { "cwk_i2s4_8ch_tx_swc", "cwk_i2s4_8ch_tx_fwac", "i2s4_mcwkin", "xin12m" };
PNAME(cwk_i2s5_8ch_tx_p)		= { "cwk_i2s5_8ch_tx_swc", "cwk_i2s5_8ch_tx_fwac", "i2s5_mcwkin", "xin12m" };
PNAME(cwk_i2s6_8ch_tx_p)		= { "cwk_i2s6_8ch_tx_swc", "cwk_i2s6_8ch_tx_fwac", "i2s6_mcwkin", "xin12m" };
PNAME(cwk_i2s6_8ch_wx_p)		= { "cwk_i2s6_8ch_wx_swc", "cwk_i2s6_8ch_wx_fwac", "i2s6_mcwkin", "xin12m" };
PNAME(i2s6_8ch_mcwkout_p)		= { "mcwk_i2s6_8ch_tx", "mcwk_i2s6_8ch_wx", "xin12m" };
PNAME(cwk_i2s7_8ch_wx_p)		= { "cwk_i2s7_8ch_wx_swc", "cwk_i2s7_8ch_wx_fwac", "i2s7_mcwkin", "xin12m" };
PNAME(cwk_i2s8_8ch_tx_p)		= { "cwk_i2s8_8ch_tx_swc", "cwk_i2s8_8ch_tx_fwac", "i2s8_mcwkin", "xin12m" };
PNAME(cwk_i2s9_8ch_wx_p)		= { "cwk_i2s9_8ch_wx_swc", "cwk_i2s9_8ch_wx_fwac", "i2s9_mcwkin", "xin12m" };
PNAME(cwk_i2s10_8ch_wx_p)		= { "cwk_i2s10_8ch_wx_swc", "cwk_i2s10_8ch_wx_fwac", "i2s10_mcwkin", "xin12m" };
PNAME(cwk_spdif0_p)			= { "cwk_spdif0_swc", "cwk_spdif0_fwac", "xin12m" };
PNAME(cwk_spdif1_p)			= { "cwk_spdif1_swc", "cwk_spdif1_fwac", "xin12m" };
PNAME(cwk_spdif2_dp0_p)			= { "cwk_spdif2_dp0_swc", "cwk_spdif2_dp0_fwac", "xin12m" };
PNAME(cwk_spdif3_p)			= { "cwk_spdif3_swc", "cwk_spdif3_fwac", "xin12m" };
PNAME(cwk_spdif4_p)			= { "cwk_spdif4_swc", "cwk_spdif4_fwac", "xin12m" };
PNAME(cwk_spdif5_dp1_p)			= { "cwk_spdif5_dp1_swc", "cwk_spdif5_dp1_fwac", "xin12m" };
PNAME(cwk_uawt0_p)			= { "cwk_uawt0_swc", "cwk_uawt0_fwac", "xin24m" };
PNAME(cwk_uawt1_p)			= { "cwk_uawt1_swc", "cwk_uawt1_fwac", "xin24m" };
PNAME(cwk_uawt2_p)			= { "cwk_uawt2_swc", "cwk_uawt2_fwac", "xin24m" };
PNAME(cwk_uawt3_p)			= { "cwk_uawt3_swc", "cwk_uawt3_fwac", "xin24m" };
PNAME(cwk_uawt4_p)			= { "cwk_uawt4_swc", "cwk_uawt4_fwac", "xin24m" };
PNAME(cwk_uawt5_p)			= { "cwk_uawt5_swc", "cwk_uawt5_fwac", "xin24m" };
PNAME(cwk_uawt6_p)			= { "cwk_uawt6_swc", "cwk_uawt6_fwac", "xin24m" };
PNAME(cwk_uawt7_p)			= { "cwk_uawt7_swc", "cwk_uawt7_fwac", "xin24m" };
PNAME(cwk_uawt8_p)			= { "cwk_uawt8_swc", "cwk_uawt8_fwac", "xin24m" };
PNAME(cwk_uawt9_p)			= { "cwk_uawt9_swc", "cwk_uawt9_fwac", "xin24m" };
PNAME(cwk_gmac0_ptp_wef_p)		= { "cpww", "cwk_gmac0_ptpwef_io" };
PNAME(cwk_gmac1_ptp_wef_p)		= { "cpww", "cwk_gmac1_ptpwef_io" };
PNAME(cwk_hdmiwx_aud_p)			= { "cwk_hdmiwx_aud_swc", "cwk_hdmiwx_aud_fwac" };
PNAME(acwk_hdcp1_woot_p)		= { "gpww", "cpww", "cwk_hdmitwx_wefswc" };
PNAME(acwk_vop_sub_swc_p)		= { "acwk_vop_woot", "acwk_vop_div2_swc" };
PNAME(dcwk_vop0_p)			= { "dcwk_vop0_swc", "cwk_hdmiphy_pixew0", "cwk_hdmiphy_pixew1" };
PNAME(dcwk_vop1_p)			= { "dcwk_vop1_swc", "cwk_hdmiphy_pixew0", "cwk_hdmiphy_pixew1" };
PNAME(dcwk_vop2_p)			= { "dcwk_vop2_swc", "cwk_hdmiphy_pixew0", "cwk_hdmiphy_pixew1" };
PNAME(pmu_200m_100m_p)			= { "cwk_pmu1_200m_swc", "cwk_pmu1_100m_swc" };
PNAME(pmu_300m_24m_p)			= { "cwk_300m_swc", "xin24m" };
PNAME(pmu_400m_24m_p)			= { "cwk_400m_swc", "xin24m" };
PNAME(pmu_100m_50m_24m_swc_p)		= { "cwk_pmu1_100m_swc", "cwk_pmu1_50m_swc", "xin24m" };
PNAME(pmu_24m_32k_100m_swc_p)		= { "xin24m", "32k", "cwk_pmu1_100m_swc" };
PNAME(hcwk_pmu1_woot_p)			= { "cwk_pmu1_200m_swc", "cwk_pmu1_100m_swc", "cwk_pmu1_50m_swc", "xin24m" };
PNAME(hcwk_pmu_cm0_woot_p)		= { "cwk_pmu1_400m_swc", "cwk_pmu1_200m_swc", "cwk_pmu1_100m_swc", "xin24m" };
PNAME(mcwk_pdm0_p)			= { "cwk_pmu1_300m_swc", "cwk_pmu1_200m_swc" };
PNAME(mux_24m_ppww_spww_p)		= { "xin24m", "ppww", "spww" };
PNAME(mux_24m_ppww_p)			= { "xin24m", "ppww" };
PNAME(cwk_wef_pipe_phy0_p)		= { "cwk_wef_pipe_phy0_osc_swc", "cwk_wef_pipe_phy0_pww_swc" };
PNAME(cwk_wef_pipe_phy1_p)		= { "cwk_wef_pipe_phy1_osc_swc", "cwk_wef_pipe_phy1_pww_swc" };
PNAME(cwk_wef_pipe_phy2_p)		= { "cwk_wef_pipe_phy2_osc_swc", "cwk_wef_pipe_phy2_pww_swc" };

#define MFWAGS CWK_MUX_HIWOWD_MASK
#define DFWAGS CWK_DIVIDEW_HIWOWD_MASK
#define GFWAGS (CWK_GATE_HIWOWD_MASK | CWK_GATE_SET_TO_DISABWE)

static stwuct wockchip_cwk_bwanch wk3588_i2s0_8ch_tx_fwacmux __initdata =
	MUX(CWK_I2S0_8CH_TX, "cwk_i2s0_8ch_tx", cwk_i2s0_8ch_tx_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(26), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_i2s0_8ch_wx_fwacmux __initdata =
	MUX(CWK_I2S0_8CH_WX, "cwk_i2s0_8ch_wx", cwk_i2s0_8ch_wx_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(28), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_i2s1_8ch_tx_fwacmux __initdata =
	MUX(CWK_I2S1_8CH_TX, "cwk_i2s1_8ch_tx", cwk_i2s1_8ch_tx_p, CWK_SET_WATE_PAWENT,
			 WK3588_PMU_CWKSEW_CON(7), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_i2s1_8ch_wx_fwacmux __initdata =
	MUX(CWK_I2S1_8CH_WX, "cwk_i2s1_8ch_wx", cwk_i2s1_8ch_wx_p, CWK_SET_WATE_PAWENT,
			 WK3588_PMU_CWKSEW_CON(9), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_i2s2_2ch_fwacmux __initdata =
	MUX(CWK_I2S2_2CH, "cwk_i2s2_2ch", cwk_i2s2_2ch_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(30), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_i2s3_2ch_fwacmux __initdata =
	MUX(CWK_I2S3_2CH, "cwk_i2s3_2ch", cwk_i2s3_2ch_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(32), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_i2s4_8ch_tx_fwacmux __initdata =
	MUX(CWK_I2S4_8CH_TX, "cwk_i2s4_8ch_tx", cwk_i2s4_8ch_tx_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(120), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_i2s5_8ch_tx_fwacmux __initdata =
	MUX(CWK_I2S5_8CH_TX, "cwk_i2s5_8ch_tx", cwk_i2s5_8ch_tx_p, CWK_SET_WATE_PAWENT,
			 WK3588_CWKSEW_CON(142), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_i2s6_8ch_tx_fwacmux __initdata =
	MUX(CWK_I2S6_8CH_TX, "cwk_i2s6_8ch_tx", cwk_i2s6_8ch_tx_p, CWK_SET_WATE_PAWENT,
			 WK3588_CWKSEW_CON(146), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_i2s6_8ch_wx_fwacmux __initdata =
	MUX(CWK_I2S6_8CH_WX, "cwk_i2s6_8ch_wx", cwk_i2s6_8ch_wx_p, CWK_SET_WATE_PAWENT,
			 WK3588_CWKSEW_CON(148), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_i2s7_8ch_wx_fwacmux __initdata =
	MUX(CWK_I2S7_8CH_WX, "cwk_i2s7_8ch_wx", cwk_i2s7_8ch_wx_p, CWK_SET_WATE_PAWENT,
			 WK3588_CWKSEW_CON(131), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_i2s8_8ch_tx_fwacmux __initdata =
	MUX(CWK_I2S8_8CH_TX, "cwk_i2s8_8ch_tx", cwk_i2s8_8ch_tx_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(122), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_i2s9_8ch_wx_fwacmux __initdata =
	MUX(CWK_I2S9_8CH_WX, "cwk_i2s9_8ch_wx", cwk_i2s9_8ch_wx_p, CWK_SET_WATE_PAWENT,
			 WK3588_CWKSEW_CON(155), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_i2s10_8ch_wx_fwacmux __initdata =
	MUX(CWK_I2S10_8CH_WX, "cwk_i2s10_8ch_wx", cwk_i2s10_8ch_wx_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(157), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_spdif0_fwacmux __initdata =
	MUX(CWK_SPDIF0, "cwk_spdif0", cwk_spdif0_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(34), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_spdif1_fwacmux __initdata =
	MUX(CWK_SPDIF1, "cwk_spdif1", cwk_spdif1_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(36), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_spdif2_dp0_fwacmux __initdata =
	MUX(CWK_SPDIF2_DP0, "cwk_spdif2_dp0", cwk_spdif2_dp0_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(124), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_spdif3_fwacmux __initdata =
	MUX(CWK_SPDIF3, "cwk_spdif3", cwk_spdif3_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(150), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_spdif4_fwacmux __initdata =
	MUX(CWK_SPDIF4, "cwk_spdif4", cwk_spdif4_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(152), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_spdif5_dp1_fwacmux __initdata =
	MUX(CWK_SPDIF5_DP1, "cwk_spdif5_dp1", cwk_spdif5_dp1_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(126), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_uawt0_fwacmux __initdata =
	MUX(CWK_UAWT0, "cwk_uawt0", cwk_uawt0_p, CWK_SET_WATE_PAWENT,
			WK3588_PMU_CWKSEW_CON(5), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_uawt1_fwacmux __initdata =
	MUX(CWK_UAWT1, "cwk_uawt1", cwk_uawt1_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(43), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_uawt2_fwacmux __initdata =
	MUX(CWK_UAWT2, "cwk_uawt2", cwk_uawt2_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(45), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_uawt3_fwacmux __initdata =
	MUX(CWK_UAWT3, "cwk_uawt3", cwk_uawt3_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(47), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_uawt4_fwacmux __initdata =
	MUX(CWK_UAWT4, "cwk_uawt4", cwk_uawt4_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(49), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_uawt5_fwacmux __initdata =
	MUX(CWK_UAWT5, "cwk_uawt5", cwk_uawt5_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(51), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_uawt6_fwacmux __initdata =
	MUX(CWK_UAWT6, "cwk_uawt6", cwk_uawt6_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(53), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_uawt7_fwacmux __initdata =
	MUX(CWK_UAWT7, "cwk_uawt7", cwk_uawt7_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(55), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_uawt8_fwacmux __initdata =
	MUX(CWK_UAWT8, "cwk_uawt8", cwk_uawt8_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(57), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_uawt9_fwacmux __initdata =
	MUX(CWK_UAWT9, "cwk_uawt9", cwk_uawt9_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(59), 0, 2, MFWAGS);

static stwuct wockchip_cwk_bwanch wk3588_hdmiwx_aud_fwacmux __initdata =
	MUX(CWK_HDMIWX_AUD_P_MUX, "cwk_hdmiwx_aud_mux", cwk_hdmiwx_aud_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(140), 0, 1, MFWAGS);

static stwuct wockchip_pww_cwock wk3588_pww_cwks[] __initdata = {
	[b0pww] = PWW(pww_wk3588_cowe, PWW_B0PWW, "b0pww", mux_pww_p,
		     CWK_IGNOWE_UNUSED, WK3588_B0_PWW_CON(0),
		     WK3588_B0_PWW_MODE_CON0, 0, 15, 0, wk3588_pww_wates),
	[b1pww] = PWW(pww_wk3588_cowe, PWW_B1PWW, "b1pww", mux_pww_p,
		     CWK_IGNOWE_UNUSED, WK3588_B1_PWW_CON(8),
		     WK3588_B1_PWW_MODE_CON0, 0, 15, 0, wk3588_pww_wates),
	[wpww] = PWW(pww_wk3588_cowe, PWW_WPWW, "wpww", mux_pww_p,
		     CWK_IGNOWE_UNUSED, WK3588_WPWW_CON(16),
		     WK3588_WPWW_MODE_CON0, 0, 15, 0, wk3588_pww_wates),
	[v0pww] = PWW(pww_wk3588, PWW_V0PWW, "v0pww", mux_pww_p,
		     0, WK3588_PWW_CON(88),
		     WK3588_MODE_CON0, 4, 15, 0, wk3588_pww_wates),
	[aupww] = PWW(pww_wk3588, PWW_AUPWW, "aupww", mux_pww_p,
		     0, WK3588_PWW_CON(96),
		     WK3588_MODE_CON0, 6, 15, 0, wk3588_pww_wates),
	[cpww] = PWW(pww_wk3588, PWW_CPWW, "cpww", mux_pww_p,
		     CWK_IGNOWE_UNUSED, WK3588_PWW_CON(104),
		     WK3588_MODE_CON0, 8, 15, 0, wk3588_pww_wates),
	[gpww] = PWW(pww_wk3588, PWW_GPWW, "gpww", mux_pww_p,
		     CWK_IGNOWE_UNUSED, WK3588_PWW_CON(112),
		     WK3588_MODE_CON0, 2, 15, 0, wk3588_pww_wates),
	[npww] = PWW(pww_wk3588, PWW_NPWW, "npww", mux_pww_p,
		     0, WK3588_PWW_CON(120),
		     WK3588_MODE_CON0, 0, 15, 0, wk3588_pww_wates),
	[ppww] = PWW(pww_wk3588_cowe, PWW_PPWW, "ppww", mux_pww_p,
		     CWK_IGNOWE_UNUSED, WK3588_PMU_PWW_CON(128),
		     WK3588_MODE_CON0, 10, 15, 0, wk3588_pww_wates),
};

static stwuct wockchip_cwk_bwanch wk3588_cwk_bwanches[] __initdata = {
	/*
	 * CWU Cwock-Awchitectuwe
	 */
	/* fixed */
	FACTOW(0, "xin12m", "xin24m", 0, 1, 2),

	/* top */
	COMPOSITE(CWK_50M_SWC, "cwk_50m_swc", gpww_cpww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(0), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(0), 0, GFWAGS),
	COMPOSITE(CWK_100M_SWC, "cwk_100m_swc", gpww_cpww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(0), 11, 1, MFWAGS, 6, 5, DFWAGS,
			WK3588_CWKGATE_CON(0), 1, GFWAGS),
	COMPOSITE(CWK_150M_SWC, "cwk_150m_swc", gpww_cpww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(1), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(0), 2, GFWAGS),
	COMPOSITE(CWK_200M_SWC, "cwk_200m_swc", gpww_cpww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(1), 11, 1, MFWAGS, 6, 5, DFWAGS,
			WK3588_CWKGATE_CON(0), 3, GFWAGS),
	COMPOSITE(CWK_250M_SWC, "cwk_250m_swc", gpww_cpww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(2), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(0), 4, GFWAGS),
	COMPOSITE(CWK_300M_SWC, "cwk_300m_swc", gpww_cpww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(2), 11, 1, MFWAGS, 6, 5, DFWAGS,
			WK3588_CWKGATE_CON(0), 5, GFWAGS),
	COMPOSITE(CWK_350M_SWC, "cwk_350m_swc", gpww_spww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(3), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(0), 6, GFWAGS),
	COMPOSITE(CWK_400M_SWC, "cwk_400m_swc", gpww_cpww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(3), 11, 1, MFWAGS, 6, 5, DFWAGS,
			WK3588_CWKGATE_CON(0), 7, GFWAGS),
	COMPOSITE_HAWFDIV(CWK_450M_SWC, "cwk_450m_swc", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(4), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(0), 8, GFWAGS),
	COMPOSITE(CWK_500M_SWC, "cwk_500m_swc", gpww_cpww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(4), 11, 1, MFWAGS, 6, 5, DFWAGS,
			WK3588_CWKGATE_CON(0), 9, GFWAGS),
	COMPOSITE(CWK_600M_SWC, "cwk_600m_swc", gpww_cpww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(5), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(0), 10, GFWAGS),
	COMPOSITE(CWK_650M_SWC, "cwk_650m_swc", gpww_wpww_p, 0,
			WK3588_CWKSEW_CON(5), 11, 1, MFWAGS, 6, 5, DFWAGS,
			WK3588_CWKGATE_CON(0), 11, GFWAGS),
	COMPOSITE(CWK_700M_SWC, "cwk_700m_swc", gpww_spww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(6), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(0), 12, GFWAGS),
	COMPOSITE(CWK_800M_SWC, "cwk_800m_swc", gpww_aupww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(6), 11, 1, MFWAGS, 6, 5, DFWAGS,
			WK3588_CWKGATE_CON(0), 13, GFWAGS),
	COMPOSITE_HAWFDIV(CWK_1000M_SWC, "cwk_1000m_swc", gpww_cpww_npww_v0pww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(7), 5, 2, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(0), 14, GFWAGS),
	COMPOSITE(CWK_1200M_SWC, "cwk_1200m_swc", gpww_cpww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(7), 12, 1, MFWAGS, 7, 5, DFWAGS,
			WK3588_CWKGATE_CON(0), 15, GFWAGS),
	COMPOSITE_NODIV(ACWK_TOP_M300_WOOT, "acwk_top_m300_woot", mux_300m_200m_100m_24m_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(9), 0, 2, MFWAGS,
			WK3588_CWKGATE_CON(1), 10, GFWAGS),
	COMPOSITE_NODIV(ACWK_TOP_M500_WOOT, "acwk_top_m500_woot", mux_500m_300m_100m_24m_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(9), 2, 2, MFWAGS,
			WK3588_CWKGATE_CON(1), 11, GFWAGS),
	COMPOSITE_NODIV(ACWK_TOP_M400_WOOT, "acwk_top_m400_woot", mux_400m_200m_100m_24m_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(9), 4, 2, MFWAGS,
			WK3588_CWKGATE_CON(1), 12, GFWAGS),
	COMPOSITE_NODIV(ACWK_TOP_S200_WOOT, "acwk_top_s200_woot", mux_200m_100m_50m_24m_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(9), 6, 2, MFWAGS,
			WK3588_CWKGATE_CON(1), 13, GFWAGS),
	COMPOSITE_NODIV(ACWK_TOP_S400_WOOT, "acwk_top_s400_woot", mux_400m_200m_100m_24m_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(9), 8, 2, MFWAGS,
			WK3588_CWKGATE_CON(1), 14, GFWAGS),
	COMPOSITE(ACWK_TOP_WOOT, "acwk_top_woot", gpww_cpww_aupww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(8), 5, 2, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(1), 0, GFWAGS),
	COMPOSITE_NODIV(PCWK_TOP_WOOT, "pcwk_top_woot", mux_100m_50m_24m_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(8), 7, 2, MFWAGS,
			WK3588_CWKGATE_CON(1), 1, GFWAGS),
	COMPOSITE(ACWK_WOW_TOP_WOOT, "acwk_wow_top_woot", gpww_cpww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(8), 14, 1, MFWAGS, 9, 5, DFWAGS,
			WK3588_CWKGATE_CON(1), 2, GFWAGS),
	COMPOSITE(CWK_MIPI_CAMAWAOUT_M0, "cwk_mipi_camawaout_m0", mux_24m_spww_gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(18), 8, 2, MFWAGS, 0, 8, DFWAGS,
			WK3588_CWKGATE_CON(5), 9, GFWAGS),
	COMPOSITE(CWK_MIPI_CAMAWAOUT_M1, "cwk_mipi_camawaout_m1", mux_24m_spww_gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(19), 8, 2, MFWAGS, 0, 8, DFWAGS,
			WK3588_CWKGATE_CON(5), 10, GFWAGS),
	COMPOSITE(CWK_MIPI_CAMAWAOUT_M2, "cwk_mipi_camawaout_m2", mux_24m_spww_gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(20), 8, 2, MFWAGS, 0, 8, DFWAGS,
			WK3588_CWKGATE_CON(5), 11, GFWAGS),
	COMPOSITE(CWK_MIPI_CAMAWAOUT_M3, "cwk_mipi_camawaout_m3", mux_24m_spww_gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(21), 8, 2, MFWAGS, 0, 8, DFWAGS,
			WK3588_CWKGATE_CON(5), 12, GFWAGS),
	COMPOSITE(CWK_MIPI_CAMAWAOUT_M4, "cwk_mipi_camawaout_m4", mux_24m_spww_gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(22), 8, 2, MFWAGS, 0, 8, DFWAGS,
			WK3588_CWKGATE_CON(5), 13, GFWAGS),
	COMPOSITE(MCWK_GMAC0_OUT, "mcwk_gmac0_out", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(15), 7, 1, MFWAGS, 0, 7, DFWAGS,
			WK3588_CWKGATE_CON(5), 3, GFWAGS),
	COMPOSITE(WEFCWKO25M_ETH0_OUT, "wefcwko25m_eth0_out", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(15), 15, 1, MFWAGS, 8, 7, DFWAGS,
			WK3588_CWKGATE_CON(5), 4, GFWAGS),
	COMPOSITE(WEFCWKO25M_ETH1_OUT, "wefcwko25m_eth1_out", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(16), 7, 1, MFWAGS, 0, 7, DFWAGS,
			WK3588_CWKGATE_CON(5), 5, GFWAGS),
	COMPOSITE(CWK_CIFOUT_OUT, "cwk_cifout_out", gpww_cpww_24m_spww_p, 0,
			WK3588_CWKSEW_CON(17), 8, 2, MFWAGS, 0, 8, DFWAGS,
			WK3588_CWKGATE_CON(5), 6, GFWAGS),
	GATE(PCWK_MIPI_DCPHY0, "pcwk_mipi_dcphy0", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(3), 14, GFWAGS),
	GATE(PCWK_MIPI_DCPHY1, "pcwk_mipi_dcphy1", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(4), 3, GFWAGS),
	GATE(PCWK_CSIPHY0, "pcwk_csiphy0", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(1), 6, GFWAGS),
	GATE(PCWK_CSIPHY1, "pcwk_csiphy1", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(1), 8, GFWAGS),
	GATE(PCWK_CWU, "pcwk_cwu", "pcwk_top_woot", CWK_IS_CWITICAW,
			WK3588_CWKGATE_CON(5), 0, GFWAGS),

	/* bigcowe0 */
	COMPOSITE_NODIV(PCWK_BIGCOWE0_WOOT, "pcwk_bigcowe0_woot", mux_100m_50m_24m_p,
			CWK_IS_CWITICAW,
			WK3588_BIGCOWE0_CWKSEW_CON(2), 0, 2, MFWAGS,
			WK3588_BIGCOWE0_CWKGATE_CON(0), 14, GFWAGS),
	GATE(PCWK_BIGCOWE0_PVTM, "pcwk_bigcowe0_pvtm", "pcwk_bigcowe0_woot", 0,
			WK3588_BIGCOWE0_CWKGATE_CON(1), 0, GFWAGS),
	GATE(CWK_BIGCOWE0_PVTM, "cwk_bigcowe0_pvtm", "xin24m", 0,
			WK3588_BIGCOWE0_CWKGATE_CON(0), 12, GFWAGS),
	GATE(CWK_COWE_BIGCOWE0_PVTM, "cwk_cowe_bigcowe0_pvtm", "awmcwk_b01", 0,
			WK3588_BIGCOWE0_CWKGATE_CON(0), 13, GFWAGS),

	/* bigcowe1 */
	COMPOSITE_NODIV(PCWK_BIGCOWE1_WOOT, "pcwk_bigcowe1_woot", mux_100m_50m_24m_p,
			CWK_IS_CWITICAW,
			WK3588_BIGCOWE1_CWKSEW_CON(2), 0, 2, MFWAGS,
			WK3588_BIGCOWE1_CWKGATE_CON(0), 14, GFWAGS),
	GATE(PCWK_BIGCOWE1_PVTM, "pcwk_bigcowe1_pvtm", "pcwk_bigcowe1_woot", 0,
			WK3588_BIGCOWE1_CWKGATE_CON(1), 0, GFWAGS),
	GATE(CWK_BIGCOWE1_PVTM, "cwk_bigcowe1_pvtm", "xin24m", 0,
			WK3588_BIGCOWE1_CWKGATE_CON(0), 12, GFWAGS),
	GATE(CWK_COWE_BIGCOWE1_PVTM, "cwk_cowe_bigcowe1_pvtm", "awmcwk_b23", 0,
			WK3588_BIGCOWE1_CWKGATE_CON(0), 13, GFWAGS),

	/* dsu */
	COMPOSITE(0, "scwk_dsu", b0pww_b1pww_wpww_gpww_p, CWK_IS_CWITICAW,
			WK3588_DSU_CWKSEW_CON(0), 12, 2, MFWAGS, 0, 5, DFWAGS,
			WK3588_DSU_CWKGATE_CON(0), 4, GFWAGS),
	COMPOSITE_NOMUX(0, "atcwk_dsu", "scwk_dsu", CWK_IS_CWITICAW,
			WK3588_DSU_CWKSEW_CON(3), 0, 5, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3588_DSU_CWKGATE_CON(1), 0, GFWAGS),
	COMPOSITE_NOMUX(0, "giccwk_dsu", "scwk_dsu", CWK_IS_CWITICAW,
			WK3588_DSU_CWKSEW_CON(3), 5, 5, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3588_DSU_CWKGATE_CON(1), 1, GFWAGS),
	COMPOSITE_NOMUX(0, "acwkmp_dsu", "scwk_dsu", CWK_IS_CWITICAW,
			WK3588_DSU_CWKSEW_CON(1), 11, 5, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3588_DSU_CWKGATE_CON(0), 12, GFWAGS),
	COMPOSITE_NOMUX(0, "acwkm_dsu", "scwk_dsu", CWK_IS_CWITICAW,
			WK3588_DSU_CWKSEW_CON(1), 1, 5, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3588_DSU_CWKGATE_CON(0), 8, GFWAGS),
	COMPOSITE_NOMUX(0, "acwks_dsu", "scwk_dsu", CWK_IS_CWITICAW,
			WK3588_DSU_CWKSEW_CON(1), 6, 5, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3588_DSU_CWKGATE_CON(0), 9, GFWAGS),
	COMPOSITE_NOMUX(0, "pewiph_dsu", "scwk_dsu", CWK_IS_CWITICAW,
			WK3588_DSU_CWKSEW_CON(2), 0, 5, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3588_DSU_CWKGATE_CON(0), 13, GFWAGS),
	COMPOSITE_NOMUX(0, "cntcwk_dsu", "pewiph_dsu", CWK_IS_CWITICAW,
			WK3588_DSU_CWKSEW_CON(2), 5, 5, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3588_DSU_CWKGATE_CON(0), 14, GFWAGS),
	COMPOSITE_NOMUX(0, "tscwk_dsu", "pewiph_dsu", CWK_IS_CWITICAW,
			WK3588_DSU_CWKSEW_CON(2), 10, 5, DFWAGS | CWK_DIVIDEW_WEAD_ONWY,
			WK3588_DSU_CWKGATE_CON(0), 15, GFWAGS),
	COMPOSITE_NODIV(PCWK_DSU_S_WOOT, "pcwk_dsu_s_woot", mux_100m_50m_24m_p, CWK_IS_CWITICAW,
			WK3588_DSU_CWKSEW_CON(4), 11, 2, MFWAGS,
			WK3588_DSU_CWKGATE_CON(2), 2, GFWAGS),
	COMPOSITE(PCWK_DSU_WOOT, "pcwk_dsu_woot", b0pww_b1pww_wpww_gpww_p, CWK_IS_CWITICAW,
			WK3588_DSU_CWKSEW_CON(4), 5, 2, MFWAGS, 0, 5, DFWAGS,
			WK3588_DSU_CWKGATE_CON(1), 3, GFWAGS),
	COMPOSITE_NODIV(PCWK_DSU_NS_WOOT, "pcwk_dsu_ns_woot", mux_100m_50m_24m_p, CWK_IS_CWITICAW,
			WK3588_DSU_CWKSEW_CON(4), 7, 2, MFWAGS,
			WK3588_DSU_CWKGATE_CON(1), 4, GFWAGS),
	GATE(PCWK_WITCOWE_PVTM, "pcwk_witcowe_pvtm", "pcwk_dsu_ns_woot", 0,
			WK3588_DSU_CWKGATE_CON(2), 6, GFWAGS),
	GATE(PCWK_DBG, "pcwk_dbg", "pcwk_dsu_woot", CWK_IS_CWITICAW,
			WK3588_DSU_CWKGATE_CON(1), 7, GFWAGS),
	GATE(PCWK_DSU, "pcwk_dsu", "pcwk_dsu_woot", CWK_IS_CWITICAW,
			WK3588_DSU_CWKGATE_CON(1), 6, GFWAGS),
	GATE(PCWK_S_DAPWITE, "pcwk_s_dapwite", "pcwk_dsu_ns_woot", CWK_IGNOWE_UNUSED,
			WK3588_DSU_CWKGATE_CON(1), 8, GFWAGS),
	GATE(PCWK_M_DAPWITE, "pcwk_m_dapwite", "pcwk_dsu_woot", CWK_IGNOWE_UNUSED,
			WK3588_DSU_CWKGATE_CON(1), 9, GFWAGS),
	GATE(CWK_WITCOWE_PVTM, "cwk_witcowe_pvtm", "xin24m", 0,
			WK3588_DSU_CWKGATE_CON(2), 0, GFWAGS),
	GATE(CWK_COWE_WITCOWE_PVTM, "cwk_cowe_witcowe_pvtm", "awmcwk_w", 0,
			WK3588_DSU_CWKGATE_CON(2), 1, GFWAGS),

	/* audio */
	COMPOSITE_NODIV(HCWK_AUDIO_WOOT, "hcwk_audio_woot", mux_200m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(24), 0, 2, MFWAGS,
			WK3588_CWKGATE_CON(7), 0, GFWAGS),
	COMPOSITE_NODIV(PCWK_AUDIO_WOOT, "pcwk_audio_woot", mux_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(24), 2, 2, MFWAGS,
			WK3588_CWKGATE_CON(7), 1, GFWAGS),
	GATE(HCWK_I2S2_2CH, "hcwk_i2s2_2ch", "hcwk_audio_woot", 0,
			WK3588_CWKGATE_CON(7), 12, GFWAGS),
	GATE(HCWK_I2S3_2CH, "hcwk_i2s3_2ch", "hcwk_audio_woot", 0,
			WK3588_CWKGATE_CON(7), 13, GFWAGS),
	COMPOSITE(CWK_I2S2_2CH_SWC, "cwk_i2s2_2ch_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(28), 9, 1, MFWAGS, 4, 5, DFWAGS,
			WK3588_CWKGATE_CON(7), 14, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S2_2CH_FWAC, "cwk_i2s2_2ch_fwac", "cwk_i2s2_2ch_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(29), 0,
			WK3588_CWKGATE_CON(7), 15, GFWAGS,
			&wk3588_i2s2_2ch_fwacmux),
	GATE(MCWK_I2S2_2CH, "mcwk_i2s2_2ch", "cwk_i2s2_2ch", 0,
			WK3588_CWKGATE_CON(8), 0, GFWAGS),
	MUX(I2S2_2CH_MCWKOUT, "i2s2_2ch_mcwkout", i2s2_2ch_mcwkout_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(30), 2, 1, MFWAGS),

	COMPOSITE(CWK_I2S3_2CH_SWC, "cwk_i2s3_2ch_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(30), 8, 1, MFWAGS, 3, 5, DFWAGS,
			WK3588_CWKGATE_CON(8), 1, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S3_2CH_FWAC, "cwk_i2s3_2ch_fwac", "cwk_i2s3_2ch_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(31), 0,
			WK3588_CWKGATE_CON(8), 2, GFWAGS,
			&wk3588_i2s3_2ch_fwacmux),
	GATE(MCWK_I2S3_2CH, "mcwk_i2s3_2ch", "cwk_i2s3_2ch", 0,
			WK3588_CWKGATE_CON(8), 3, GFWAGS),
	GATE(CWK_DAC_ACDCDIG, "cwk_dac_acdcdig", "mcwk_i2s3_2ch", 0,
			WK3588_CWKGATE_CON(8), 4, GFWAGS),
	MUX(I2S3_2CH_MCWKOUT, "i2s3_2ch_mcwkout", i2s3_2ch_mcwkout_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(32), 2, 1, MFWAGS),
	GATE(PCWK_ACDCDIG, "pcwk_acdcdig", "pcwk_audio_woot", 0,
			WK3588_CWKGATE_CON(7), 11, GFWAGS),
	GATE(HCWK_I2S0_8CH, "hcwk_i2s0_8ch", "hcwk_audio_woot", 0,
			WK3588_CWKGATE_CON(7), 4, GFWAGS),

	COMPOSITE(CWK_I2S0_8CH_TX_SWC, "cwk_i2s0_8ch_tx_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(24), 9, 1, MFWAGS, 4, 5, DFWAGS,
			WK3588_CWKGATE_CON(7), 5, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S0_8CH_TX_FWAC, "cwk_i2s0_8ch_tx_fwac", "cwk_i2s0_8ch_tx_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(25), 0,
			WK3588_CWKGATE_CON(7), 6, GFWAGS,
			&wk3588_i2s0_8ch_tx_fwacmux),
	GATE(MCWK_I2S0_8CH_TX, "mcwk_i2s0_8ch_tx", "cwk_i2s0_8ch_tx", 0,
			WK3588_CWKGATE_CON(7), 7, GFWAGS),

	COMPOSITE(CWK_I2S0_8CH_WX_SWC, "cwk_i2s0_8ch_wx_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(26), 7, 1, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(7), 8, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S0_8CH_WX_FWAC, "cwk_i2s0_8ch_wx_fwac", "cwk_i2s0_8ch_wx_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(27), 0,
			WK3588_CWKGATE_CON(7), 9, GFWAGS,
			&wk3588_i2s0_8ch_wx_fwacmux),
	GATE(MCWK_I2S0_8CH_WX, "mcwk_i2s0_8ch_wx", "cwk_i2s0_8ch_wx", 0,
			WK3588_CWKGATE_CON(7), 10, GFWAGS),
	MUX(I2S0_8CH_MCWKOUT, "i2s0_8ch_mcwkout", i2s0_8ch_mcwkout_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(28), 2, 2, MFWAGS),

	GATE(HCWK_PDM1, "hcwk_pdm1", "hcwk_audio_woot", 0,
			WK3588_CWKGATE_CON(9), 6, GFWAGS),
	COMPOSITE(MCWK_PDM1, "mcwk_pdm1", gpww_cpww_aupww_p, 0,
			WK3588_CWKSEW_CON(36), 7, 2, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(9), 7, GFWAGS),

	GATE(HCWK_SPDIF0, "hcwk_spdif0", "hcwk_audio_woot", 0,
			WK3588_CWKGATE_CON(8), 14, GFWAGS),
	COMPOSITE(CWK_SPDIF0_SWC, "cwk_spdif0_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(32), 8, 1, MFWAGS, 3, 5, DFWAGS,
			WK3588_CWKGATE_CON(8), 15, GFWAGS),
	COMPOSITE_FWACMUX(CWK_SPDIF0_FWAC, "cwk_spdif0_fwac", "cwk_spdif0_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(33), 0,
			WK3588_CWKGATE_CON(9), 0, GFWAGS,
			&wk3588_spdif0_fwacmux),
	GATE(MCWK_SPDIF0, "mcwk_spdif0", "cwk_spdif0", 0,
			WK3588_CWKGATE_CON(9), 1, GFWAGS),

	GATE(HCWK_SPDIF1, "hcwk_spdif1", "hcwk_audio_woot", 0,
			WK3588_CWKGATE_CON(9), 2, GFWAGS),
	COMPOSITE(CWK_SPDIF1_SWC, "cwk_spdif1_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(34), 7, 1, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(9), 3, GFWAGS),
	COMPOSITE_FWACMUX(CWK_SPDIF1_FWAC, "cwk_spdif1_fwac", "cwk_spdif1_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(35), 0,
			WK3588_CWKGATE_CON(9), 4, GFWAGS,
			&wk3588_spdif1_fwacmux),
	GATE(MCWK_SPDIF1, "mcwk_spdif1", "cwk_spdif1", 0,
			WK3588_CWKGATE_CON(9), 5, GFWAGS),

	COMPOSITE(ACWK_AV1_WOOT, "acwk_av1_woot", gpww_cpww_aupww_p, 0,
			WK3588_CWKSEW_CON(163), 5, 2, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(68), 0, GFWAGS),
	COMPOSITE_NODIV(PCWK_AV1_WOOT, "pcwk_av1_woot", mux_200m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(163), 7, 2, MFWAGS,
			WK3588_CWKGATE_CON(68), 3, GFWAGS),

	/* bus */
	COMPOSITE(ACWK_BUS_WOOT, "acwk_bus_woot", gpww_cpww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(38), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(10), 0, GFWAGS),

	GATE(PCWK_MAIWBOX0, "pcwk_maiwbox0", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(16), 11, GFWAGS),
	GATE(PCWK_MAIWBOX1, "pcwk_maiwbox1", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(16), 12, GFWAGS),
	GATE(PCWK_MAIWBOX2, "pcwk_maiwbox2", "pcwk_top_woot", 0,
		WK3588_CWKGATE_CON(16), 13, GFWAGS),
	GATE(PCWK_PMU2, "pcwk_pmu2", "pcwk_top_woot", CWK_IS_CWITICAW,
			WK3588_CWKGATE_CON(19), 3, GFWAGS),
	GATE(PCWK_PMUCM0_INTMUX, "pcwk_pmucm0_intmux", "pcwk_top_woot", CWK_IS_CWITICAW,
			WK3588_CWKGATE_CON(19), 4, GFWAGS),
	GATE(PCWK_DDWCM0_INTMUX, "pcwk_ddwcm0_intmux", "pcwk_top_woot", CWK_IS_CWITICAW,
			WK3588_CWKGATE_CON(19), 5, GFWAGS),

	GATE(PCWK_PWM1, "pcwk_pwm1", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(15), 3, GFWAGS),
	COMPOSITE_NODIV(CWK_PWM1, "cwk_pwm1", mux_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(59), 12, 2, MFWAGS,
			WK3588_CWKGATE_CON(15), 4, GFWAGS),
	GATE(CWK_PWM1_CAPTUWE, "cwk_pwm1_captuwe", "xin24m", 0,
			WK3588_CWKGATE_CON(15), 5, GFWAGS),
	GATE(PCWK_PWM2, "pcwk_pwm2", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(15), 6, GFWAGS),
	COMPOSITE_NODIV(CWK_PWM2, "cwk_pwm2", mux_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(59), 14, 2, MFWAGS,
			WK3588_CWKGATE_CON(15), 7, GFWAGS),
	GATE(CWK_PWM2_CAPTUWE, "cwk_pwm2_captuwe", "xin24m", 0,
			WK3588_CWKGATE_CON(15), 8, GFWAGS),
	GATE(PCWK_PWM3, "pcwk_pwm3", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(15), 9, GFWAGS),
	COMPOSITE_NODIV(CWK_PWM3, "cwk_pwm3", mux_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(60), 0, 2, MFWAGS,
			WK3588_CWKGATE_CON(15), 10, GFWAGS),
	GATE(CWK_PWM3_CAPTUWE, "cwk_pwm3_captuwe", "xin24m", 0,
			WK3588_CWKGATE_CON(15), 11, GFWAGS),

	GATE(PCWK_BUSTIMEW0, "pcwk_bustimew0", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(15), 12, GFWAGS),
	GATE(PCWK_BUSTIMEW1, "pcwk_bustimew1", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(15), 13, GFWAGS),
	COMPOSITE_NODIV(CWK_BUS_TIMEW_WOOT, "cwk_bus_timew_woot", mux_24m_100m_p, 0,
			WK3588_CWKSEW_CON(60), 2, 1, MFWAGS,
			WK3588_CWKGATE_CON(15), 14, GFWAGS),
	GATE(CWK_BUSTIMEW0, "cwk_bustimew0", "cwk_bus_timew_woot", 0,
			WK3588_CWKGATE_CON(15), 15, GFWAGS),
	GATE(CWK_BUSTIMEW1, "cwk_bustimew1", "cwk_bus_timew_woot", 0,
			WK3588_CWKGATE_CON(16), 0, GFWAGS),
	GATE(CWK_BUSTIMEW2, "cwk_bustimew2", "cwk_bus_timew_woot", 0,
			WK3588_CWKGATE_CON(16), 1, GFWAGS),
	GATE(CWK_BUSTIMEW3, "cwk_bustimew3", "cwk_bus_timew_woot", 0,
			WK3588_CWKGATE_CON(16), 2, GFWAGS),
	GATE(CWK_BUSTIMEW4, "cwk_bustimew4", "cwk_bus_timew_woot", 0,
			WK3588_CWKGATE_CON(16), 3, GFWAGS),
	GATE(CWK_BUSTIMEW5, "cwk_bustimew5", "cwk_bus_timew_woot", 0,
			WK3588_CWKGATE_CON(16), 4, GFWAGS),
	GATE(CWK_BUSTIMEW6, "cwk_bustimew6", "cwk_bus_timew_woot", 0,
			WK3588_CWKGATE_CON(16), 5, GFWAGS),
	GATE(CWK_BUSTIMEW7, "cwk_bustimew7", "cwk_bus_timew_woot", 0,
			WK3588_CWKGATE_CON(16), 6, GFWAGS),
	GATE(CWK_BUSTIMEW8, "cwk_bustimew8", "cwk_bus_timew_woot", 0,
			WK3588_CWKGATE_CON(16), 7, GFWAGS),
	GATE(CWK_BUSTIMEW9, "cwk_bustimew9", "cwk_bus_timew_woot", 0,
			WK3588_CWKGATE_CON(16), 8, GFWAGS),
	GATE(CWK_BUSTIMEW10, "cwk_bustimew10", "cwk_bus_timew_woot", 0,
			WK3588_CWKGATE_CON(16), 9, GFWAGS),
	GATE(CWK_BUSTIMEW11, "cwk_bustimew11", "cwk_bus_timew_woot", 0,
			WK3588_CWKGATE_CON(16), 10, GFWAGS),

	GATE(PCWK_WDT0, "pcwk_wdt0", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(15), 0, GFWAGS),
	GATE(TCWK_WDT0, "tcwk_wdt0", "xin24m", 0,
			WK3588_CWKGATE_CON(15), 1, GFWAGS),

	GATE(PCWK_CAN0, "pcwk_can0", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(11), 8, GFWAGS),
	COMPOSITE(CWK_CAN0, "cwk_can0", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(39), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(11), 9, GFWAGS),
	GATE(PCWK_CAN1, "pcwk_can1", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(11), 10, GFWAGS),
	COMPOSITE(CWK_CAN1, "cwk_can1", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(39), 11, 1, MFWAGS, 6, 5, DFWAGS,
			WK3588_CWKGATE_CON(11), 11, GFWAGS),
	GATE(PCWK_CAN2, "pcwk_can2", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(11), 12, GFWAGS),
	COMPOSITE(CWK_CAN2, "cwk_can2", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(40), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(11), 13, GFWAGS),

	GATE(ACWK_DECOM, "acwk_decom", "acwk_bus_woot", 0,
			WK3588_CWKGATE_CON(17), 6, GFWAGS),
	GATE(PCWK_DECOM, "pcwk_decom", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(17), 7, GFWAGS),
	COMPOSITE(DCWK_DECOM, "dcwk_decom", gpww_spww_p, 0,
			WK3588_CWKSEW_CON(62), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(17), 8, GFWAGS),
	GATE(ACWK_DMAC0, "acwk_dmac0", "acwk_bus_woot", 0,
			WK3588_CWKGATE_CON(10), 5, GFWAGS),
	GATE(ACWK_DMAC1, "acwk_dmac1", "acwk_bus_woot", 0,
			WK3588_CWKGATE_CON(10), 6, GFWAGS),
	GATE(ACWK_DMAC2, "acwk_dmac2", "acwk_bus_woot", 0,
			WK3588_CWKGATE_CON(10), 7, GFWAGS),
	GATE(ACWK_GIC, "acwk_gic", "acwk_bus_woot", CWK_IS_CWITICAW,
			WK3588_CWKGATE_CON(10), 3, GFWAGS),

	GATE(PCWK_GPIO1, "pcwk_gpio1", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(16), 14, GFWAGS),
	COMPOSITE(DBCWK_GPIO1, "dbcwk_gpio1", mux_24m_32k_p, 0,
			WK3588_CWKSEW_CON(60), 8, 1, MFWAGS, 3, 5, DFWAGS,
			WK3588_CWKGATE_CON(16), 15, GFWAGS),
	GATE(PCWK_GPIO2, "pcwk_gpio2", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(17), 0, GFWAGS),
	COMPOSITE(DBCWK_GPIO2, "dbcwk_gpio2", mux_24m_32k_p, 0,
			WK3588_CWKSEW_CON(60), 14, 1, MFWAGS, 9, 5, DFWAGS,
			WK3588_CWKGATE_CON(17), 1, GFWAGS),
	GATE(PCWK_GPIO3, "pcwk_gpio3", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(17), 2, GFWAGS),
	COMPOSITE(DBCWK_GPIO3, "dbcwk_gpio3", mux_24m_32k_p, 0,
			WK3588_CWKSEW_CON(61), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(17), 3, GFWAGS),
	GATE(PCWK_GPIO4, "pcwk_gpio4", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(17), 4, GFWAGS),
	COMPOSITE(DBCWK_GPIO4, "dbcwk_gpio4", mux_24m_32k_p, 0,
			WK3588_CWKSEW_CON(61), 11, 1, MFWAGS, 6, 5, DFWAGS,
			WK3588_CWKGATE_CON(17), 5, GFWAGS),

	GATE(PCWK_I2C1, "pcwk_i2c1", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(10), 8, GFWAGS),
	GATE(PCWK_I2C2, "pcwk_i2c2", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(10), 9, GFWAGS),
	GATE(PCWK_I2C3, "pcwk_i2c3", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(10), 10, GFWAGS),
	GATE(PCWK_I2C4, "pcwk_i2c4", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(10), 11, GFWAGS),
	GATE(PCWK_I2C5, "pcwk_i2c5", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(10), 12, GFWAGS),
	GATE(PCWK_I2C6, "pcwk_i2c6", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(10), 13, GFWAGS),
	GATE(PCWK_I2C7, "pcwk_i2c7", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(10), 14, GFWAGS),
	GATE(PCWK_I2C8, "pcwk_i2c8", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(10), 15, GFWAGS),
	COMPOSITE_NODIV(CWK_I2C1, "cwk_i2c1", mux_200m_100m_p, 0,
			WK3588_CWKSEW_CON(38), 6, 1, MFWAGS,
			WK3588_CWKGATE_CON(11), 0, GFWAGS),
	COMPOSITE_NODIV(CWK_I2C2, "cwk_i2c2", mux_200m_100m_p, 0,
			WK3588_CWKSEW_CON(38), 7, 1, MFWAGS,
			WK3588_CWKGATE_CON(11), 1, GFWAGS),
	COMPOSITE_NODIV(CWK_I2C3, "cwk_i2c3", mux_200m_100m_p, 0,
			WK3588_CWKSEW_CON(38), 8, 1, MFWAGS,
			WK3588_CWKGATE_CON(11), 2, GFWAGS),
	COMPOSITE_NODIV(CWK_I2C4, "cwk_i2c4", mux_200m_100m_p, 0,
			WK3588_CWKSEW_CON(38), 9, 1, MFWAGS,
			WK3588_CWKGATE_CON(11), 3, GFWAGS),
	COMPOSITE_NODIV(CWK_I2C5, "cwk_i2c5", mux_200m_100m_p, 0,
			WK3588_CWKSEW_CON(38), 10, 1, MFWAGS,
			WK3588_CWKGATE_CON(11), 4, GFWAGS),
	COMPOSITE_NODIV(CWK_I2C6, "cwk_i2c6", mux_200m_100m_p, 0,
			WK3588_CWKSEW_CON(38), 11, 1, MFWAGS,
			WK3588_CWKGATE_CON(11), 5, GFWAGS),
	COMPOSITE_NODIV(CWK_I2C7, "cwk_i2c7", mux_200m_100m_p, 0,
			WK3588_CWKSEW_CON(38), 12, 1, MFWAGS,
			WK3588_CWKGATE_CON(11), 6, GFWAGS),
	COMPOSITE_NODIV(CWK_I2C8, "cwk_i2c8", mux_200m_100m_p, 0,
			WK3588_CWKSEW_CON(38), 13, 1, MFWAGS,
			WK3588_CWKGATE_CON(11), 7, GFWAGS),

	GATE(PCWK_OTPC_NS, "pcwk_otpc_ns", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(18), 9, GFWAGS),
	GATE(CWK_OTPC_NS, "cwk_otpc_ns", "xin24m", 0,
			WK3588_CWKGATE_CON(18), 10, GFWAGS),
	GATE(CWK_OTPC_AWB, "cwk_otpc_awb", "xin24m", 0,
			WK3588_CWKGATE_CON(18), 11, GFWAGS),
	GATE(CWK_OTP_PHY_G, "cwk_otp_phy_g", "xin24m", 0,
			WK3588_CWKGATE_CON(18), 13, GFWAGS),
	GATE(CWK_OTPC_AUTO_WD_G, "cwk_otpc_auto_wd_g", "xin24m", 0,
			WK3588_CWKGATE_CON(18), 12, GFWAGS),

	GATE(PCWK_SAWADC, "pcwk_sawadc", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(11), 14, GFWAGS),
	COMPOSITE(CWK_SAWADC, "cwk_sawadc", gpww_24m_p, 0,
			WK3588_CWKSEW_CON(40), 14, 1, MFWAGS, 6, 8, DFWAGS,
			WK3588_CWKGATE_CON(11), 15, GFWAGS),

	GATE(PCWK_SPI0, "pcwk_spi0", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(14), 6, GFWAGS),
	GATE(PCWK_SPI1, "pcwk_spi1", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(14), 7, GFWAGS),
	GATE(PCWK_SPI2, "pcwk_spi2", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(14), 8, GFWAGS),
	GATE(PCWK_SPI3, "pcwk_spi3", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(14), 9, GFWAGS),
	GATE(PCWK_SPI4, "pcwk_spi4", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(14), 10, GFWAGS),
	COMPOSITE_NODIV(CWK_SPI0, "cwk_spi0", mux_200m_150m_24m_p, 0,
			WK3588_CWKSEW_CON(59), 2, 2, MFWAGS,
			WK3588_CWKGATE_CON(14), 11, GFWAGS),
	COMPOSITE_NODIV(CWK_SPI1, "cwk_spi1", mux_200m_150m_24m_p, 0,
			WK3588_CWKSEW_CON(59), 4, 2, MFWAGS,
			WK3588_CWKGATE_CON(14), 12, GFWAGS),
	COMPOSITE_NODIV(CWK_SPI2, "cwk_spi2", mux_200m_150m_24m_p, 0,
			WK3588_CWKSEW_CON(59), 6, 2, MFWAGS,
			WK3588_CWKGATE_CON(14), 13, GFWAGS),
	COMPOSITE_NODIV(CWK_SPI3, "cwk_spi3", mux_200m_150m_24m_p, 0,
			WK3588_CWKSEW_CON(59), 8, 2, MFWAGS,
			WK3588_CWKGATE_CON(14), 14, GFWAGS),
	COMPOSITE_NODIV(CWK_SPI4, "cwk_spi4", mux_200m_150m_24m_p, 0,
			WK3588_CWKSEW_CON(59), 10, 2, MFWAGS,
			WK3588_CWKGATE_CON(14), 15, GFWAGS),

	GATE(ACWK_SPINWOCK, "acwk_spinwock", "acwk_bus_woot", CWK_IGNOWE_UNUSED,
			WK3588_CWKGATE_CON(18), 6, GFWAGS),
	GATE(PCWK_TSADC, "pcwk_tsadc", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(12), 0, GFWAGS),
	COMPOSITE(CWK_TSADC, "cwk_tsadc", gpww_24m_p, 0,
			WK3588_CWKSEW_CON(41), 8, 1, MFWAGS, 0, 8, DFWAGS,
			WK3588_CWKGATE_CON(12), 1, GFWAGS),

	GATE(PCWK_UAWT1, "pcwk_uawt1", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(12), 2, GFWAGS),
	GATE(PCWK_UAWT2, "pcwk_uawt2", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(12), 3, GFWAGS),
	GATE(PCWK_UAWT3, "pcwk_uawt3", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(12), 4, GFWAGS),
	GATE(PCWK_UAWT4, "pcwk_uawt4", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(12), 5, GFWAGS),
	GATE(PCWK_UAWT5, "pcwk_uawt5", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(12), 6, GFWAGS),
	GATE(PCWK_UAWT6, "pcwk_uawt6", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(12), 7, GFWAGS),
	GATE(PCWK_UAWT7, "pcwk_uawt7", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(12), 8, GFWAGS),
	GATE(PCWK_UAWT8, "pcwk_uawt8", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(12), 9, GFWAGS),
	GATE(PCWK_UAWT9, "pcwk_uawt9", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(12), 10, GFWAGS),

	COMPOSITE(CWK_UAWT1_SWC, "cwk_uawt1_swc", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(41), 14, 1, MFWAGS, 9, 5, DFWAGS,
			WK3588_CWKGATE_CON(12), 11, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT1_FWAC, "cwk_uawt1_fwac", "cwk_uawt1_swc", CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(42), 0,
			WK3588_CWKGATE_CON(12), 12, GFWAGS,
			&wk3588_uawt1_fwacmux),
	GATE(SCWK_UAWT1, "scwk_uawt1", "cwk_uawt1", 0,
			WK3588_CWKGATE_CON(12), 13, GFWAGS),
	COMPOSITE(CWK_UAWT2_SWC, "cwk_uawt2_swc", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(43), 7, 1, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(12), 14, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT2_FWAC, "cwk_uawt2_fwac", "cwk_uawt2_swc", CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(44), 0,
			WK3588_CWKGATE_CON(12), 15, GFWAGS,
			&wk3588_uawt2_fwacmux),
	GATE(SCWK_UAWT2, "scwk_uawt2", "cwk_uawt2", 0,
			WK3588_CWKGATE_CON(13), 0, GFWAGS),
	COMPOSITE(CWK_UAWT3_SWC, "cwk_uawt3_swc", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(45), 7, 1, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(13), 1, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT3_FWAC, "cwk_uawt3_fwac", "cwk_uawt3_swc", CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(46), 0,
			WK3588_CWKGATE_CON(13), 2, GFWAGS,
			&wk3588_uawt3_fwacmux),
	GATE(SCWK_UAWT3, "scwk_uawt3", "cwk_uawt3", 0,
			WK3588_CWKGATE_CON(13), 3, GFWAGS),
	COMPOSITE(CWK_UAWT4_SWC, "cwk_uawt4_swc", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(47), 7, 1, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(13), 4, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT4_FWAC, "cwk_uawt4_fwac", "cwk_uawt4_swc", CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(48), 0,
			WK3588_CWKGATE_CON(13), 5, GFWAGS,
			&wk3588_uawt4_fwacmux),
	GATE(SCWK_UAWT4, "scwk_uawt4", "cwk_uawt4", 0,
			WK3588_CWKGATE_CON(13), 6, GFWAGS),
	COMPOSITE(CWK_UAWT5_SWC, "cwk_uawt5_swc", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(49), 7, 1, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(13), 7, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT5_FWAC, "cwk_uawt5_fwac", "cwk_uawt5_swc", CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(50), 0,
			WK3588_CWKGATE_CON(13), 8, GFWAGS,
			&wk3588_uawt5_fwacmux),
	GATE(SCWK_UAWT5, "scwk_uawt5", "cwk_uawt5", 0,
			WK3588_CWKGATE_CON(13), 9, GFWAGS),
	COMPOSITE(CWK_UAWT6_SWC, "cwk_uawt6_swc", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(51), 7, 1, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(13), 10, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT6_FWAC, "cwk_uawt6_fwac", "cwk_uawt6_swc", CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(52), 0,
			WK3588_CWKGATE_CON(13), 11, GFWAGS,
			&wk3588_uawt6_fwacmux),
	GATE(SCWK_UAWT6, "scwk_uawt6", "cwk_uawt6", 0,
			WK3588_CWKGATE_CON(13), 12, GFWAGS),
	COMPOSITE(CWK_UAWT7_SWC, "cwk_uawt7_swc", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(53), 7, 1, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(13), 13, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT7_FWAC, "cwk_uawt7_fwac", "cwk_uawt7_swc", CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(54), 0,
			WK3588_CWKGATE_CON(13), 14, GFWAGS,
			&wk3588_uawt7_fwacmux),
	GATE(SCWK_UAWT7, "scwk_uawt7", "cwk_uawt7", 0,
			WK3588_CWKGATE_CON(13), 15, GFWAGS),
	COMPOSITE(CWK_UAWT8_SWC, "cwk_uawt8_swc", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(55), 7, 1, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(14), 0, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT8_FWAC, "cwk_uawt8_fwac", "cwk_uawt8_swc", CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(56), 0,
			WK3588_CWKGATE_CON(14), 1, GFWAGS,
			&wk3588_uawt8_fwacmux),
	GATE(SCWK_UAWT8, "scwk_uawt8", "cwk_uawt8", 0,
			WK3588_CWKGATE_CON(14), 2, GFWAGS),
	COMPOSITE(CWK_UAWT9_SWC, "cwk_uawt9_swc", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(57), 7, 1, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(14), 3, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT9_FWAC, "cwk_uawt9_fwac", "cwk_uawt9_swc", CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(58), 0,
			WK3588_CWKGATE_CON(14), 4, GFWAGS,
			&wk3588_uawt9_fwacmux),
	GATE(SCWK_UAWT9, "scwk_uawt9", "cwk_uawt9", 0,
			WK3588_CWKGATE_CON(14), 5, GFWAGS),

	/* centew */
	COMPOSITE_NODIV(ACWK_CENTEW_WOOT, "acwk_centew_woot", mux_700m_400m_200m_24m_p,
			CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(165), 0, 2, MFWAGS,
			WK3588_CWKGATE_CON(69), 0, GFWAGS),
	COMPOSITE_NODIV(ACWK_CENTEW_WOW_WOOT, "acwk_centew_wow_woot", mux_500m_250m_100m_24m_p,
			CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(165), 2, 2, MFWAGS,
			WK3588_CWKGATE_CON(69), 1, GFWAGS),
	COMPOSITE_NODIV(HCWK_CENTEW_WOOT, "hcwk_centew_woot", mux_400m_200m_100m_24m_p,
			CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(165), 4, 2, MFWAGS,
			WK3588_CWKGATE_CON(69), 2, GFWAGS),
	COMPOSITE_NODIV(PCWK_CENTEW_WOOT, "pcwk_centew_woot", mux_200m_100m_50m_24m_p,
			CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(165), 6, 2, MFWAGS | CWK_MUX_WEAD_ONWY,
			WK3588_CWKGATE_CON(69), 3, GFWAGS),
	GATE(ACWK_DMA2DDW, "acwk_dma2ddw", "acwk_centew_woot", CWK_IS_CWITICAW,
			WK3588_CWKGATE_CON(69), 5, GFWAGS),
	GATE(ACWK_DDW_SHAWEMEM, "acwk_ddw_shawemem", "acwk_centew_wow_woot", CWK_IS_CWITICAW,
			WK3588_CWKGATE_CON(69), 6, GFWAGS),
	COMPOSITE_NODIV(ACWK_CENTEW_S200_WOOT, "acwk_centew_s200_woot", mux_200m_100m_50m_24m_p,
			CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(165), 8, 2, MFWAGS,
			WK3588_CWKGATE_CON(69), 8, GFWAGS),
	COMPOSITE_NODIV(ACWK_CENTEW_S400_WOOT, "acwk_centew_s400_woot", mux_400m_200m_100m_24m_p,
			CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(165), 10, 2, MFWAGS,
			WK3588_CWKGATE_CON(69), 9, GFWAGS),
	GATE(FCWK_DDW_CM0_COWE, "fcwk_ddw_cm0_cowe", "hcwk_centew_woot", CWK_IS_CWITICAW,
			WK3588_CWKGATE_CON(69), 14, GFWAGS),
	COMPOSITE_NODIV(CWK_DDW_TIMEW_WOOT, "cwk_ddw_timew_woot", mux_24m_100m_p, CWK_IGNOWE_UNUSED,
			WK3588_CWKSEW_CON(165), 12, 1, MFWAGS,
			WK3588_CWKGATE_CON(69), 15, GFWAGS),
	GATE(CWK_DDW_TIMEW0, "cwk_ddw_timew0", "cwk_ddw_timew_woot", 0,
			WK3588_CWKGATE_CON(70), 0, GFWAGS),
	GATE(CWK_DDW_TIMEW1, "cwk_ddw_timew1", "cwk_ddw_timew_woot", 0,
			WK3588_CWKGATE_CON(70), 1, GFWAGS),
	GATE(TCWK_WDT_DDW, "tcwk_wdt_ddw", "xin24m", 0,
			WK3588_CWKGATE_CON(70), 2, GFWAGS),
	COMPOSITE(CWK_DDW_CM0_WTC, "cwk_ddw_cm0_wtc", mux_24m_32k_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(166), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(70), 4, GFWAGS),
	GATE(PCWK_WDT, "pcwk_wdt", "pcwk_centew_woot", 0,
			WK3588_CWKGATE_CON(70), 7, GFWAGS),
	GATE(PCWK_TIMEW, "pcwk_timew", "pcwk_centew_woot", 0,
			WK3588_CWKGATE_CON(70), 8, GFWAGS),
	GATE(PCWK_DMA2DDW, "pcwk_dma2ddw", "pcwk_centew_woot", CWK_IS_CWITICAW,
			WK3588_CWKGATE_CON(70), 9, GFWAGS),
	GATE(PCWK_SHAWEMEM, "pcwk_shawemem", "pcwk_centew_woot", CWK_IS_CWITICAW,
			WK3588_CWKGATE_CON(70), 10, GFWAGS),

	/* gpu */
	COMPOSITE(CWK_GPU_SWC, "cwk_gpu_swc", gpww_cpww_aupww_npww_spww_p, 0,
			WK3588_CWKSEW_CON(158), 5, 3, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(66), 1, GFWAGS),
	GATE(CWK_GPU, "cwk_gpu", "cwk_gpu_swc", 0,
			WK3588_CWKGATE_CON(66), 4, GFWAGS),
	GATE(CWK_GPU_COWEGWOUP, "cwk_gpu_cowegwoup", "cwk_gpu_swc", 0,
			WK3588_CWKGATE_CON(66), 6, GFWAGS),
	COMPOSITE_NOMUX(CWK_GPU_STACKS, "cwk_gpu_stacks", "cwk_gpu_swc", 0,
			WK3588_CWKSEW_CON(159), 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(66), 7, GFWAGS),
	GATE(CWK_GPU_PVTM, "cwk_gpu_pvtm", "xin24m", 0,
			WK3588_CWKGATE_CON(67), 0, GFWAGS),
	GATE(CWK_COWE_GPU_PVTM, "cwk_cowe_gpu_pvtm", "cwk_gpu_swc", 0,
			WK3588_CWKGATE_CON(67), 1, GFWAGS),

	/* isp1 */
	COMPOSITE(ACWK_ISP1_WOOT, "acwk_isp1_woot", gpww_cpww_aupww_spww_p, 0,
			WK3588_CWKSEW_CON(67), 5, 2, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(26), 0, GFWAGS),
	COMPOSITE_NODIV(HCWK_ISP1_WOOT, "hcwk_isp1_woot", mux_200m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(67), 7, 2, MFWAGS,
			WK3588_CWKGATE_CON(26), 1, GFWAGS),
	COMPOSITE(CWK_ISP1_COWE, "cwk_isp1_cowe", gpww_cpww_aupww_spww_p, 0,
			WK3588_CWKSEW_CON(67), 14, 2, MFWAGS, 9, 5, DFWAGS,
			WK3588_CWKGATE_CON(26), 2, GFWAGS),
	GATE(CWK_ISP1_COWE_MAWVIN, "cwk_isp1_cowe_mawvin", "cwk_isp1_cowe", 0,
			WK3588_CWKGATE_CON(26), 3, GFWAGS),
	GATE(CWK_ISP1_COWE_VICAP, "cwk_isp1_cowe_vicap", "cwk_isp1_cowe", 0,
			WK3588_CWKGATE_CON(26), 4, GFWAGS),

	/* npu */
	COMPOSITE_NODIV(HCWK_NPU_WOOT, "hcwk_npu_woot", mux_200m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(73), 0, 2, MFWAGS,
			WK3588_CWKGATE_CON(29), 0, GFWAGS),
	COMPOSITE(CWK_NPU_DSU0, "cwk_npu_dsu0", gpww_cpww_aupww_npww_spww_p, 0,
			WK3588_CWKSEW_CON(73), 7, 3, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(29), 1, GFWAGS),
	COMPOSITE_NODIV(PCWK_NPU_WOOT, "pcwk_npu_woot", mux_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(74), 1, 2, MFWAGS,
			WK3588_CWKGATE_CON(29), 4, GFWAGS),
	GATE(ACWK_NPU1, "acwk_npu1", "cwk_npu_dsu0", 0,
			WK3588_CWKGATE_CON(27), 0, GFWAGS),
	GATE(HCWK_NPU1, "hcwk_npu1", "hcwk_npu_woot", 0,
			WK3588_CWKGATE_CON(27), 2, GFWAGS),
	GATE(ACWK_NPU2, "acwk_npu2", "cwk_npu_dsu0", 0,
			WK3588_CWKGATE_CON(28), 0, GFWAGS),
	GATE(HCWK_NPU2, "hcwk_npu2", "hcwk_npu_woot", 0,
			WK3588_CWKGATE_CON(28), 2, GFWAGS),
	COMPOSITE_NODIV(HCWK_NPU_CM0_WOOT, "hcwk_npu_cm0_woot", mux_400m_200m_100m_24m_p, 0,
			WK3588_CWKSEW_CON(74), 5, 2, MFWAGS,
			WK3588_CWKGATE_CON(30), 1, GFWAGS),
	GATE(FCWK_NPU_CM0_COWE, "fcwk_npu_cm0_cowe", "hcwk_npu_cm0_woot", 0,
			WK3588_CWKGATE_CON(30), 3, GFWAGS),
	COMPOSITE(CWK_NPU_CM0_WTC, "cwk_npu_cm0_wtc", mux_24m_32k_p, 0,
			WK3588_CWKSEW_CON(74), 12, 1, MFWAGS, 7, 5, DFWAGS,
			WK3588_CWKGATE_CON(30), 5, GFWAGS),
	GATE(PCWK_NPU_PVTM, "pcwk_npu_pvtm", "pcwk_npu_woot", 0,
			WK3588_CWKGATE_CON(29), 12, GFWAGS),
	GATE(PCWK_NPU_GWF, "pcwk_npu_gwf", "pcwk_npu_woot", CWK_IGNOWE_UNUSED,
			WK3588_CWKGATE_CON(29), 13, GFWAGS),
	GATE(CWK_NPU_PVTM, "cwk_npu_pvtm", "xin24m", 0,
			WK3588_CWKGATE_CON(29), 14, GFWAGS),
	GATE(CWK_COWE_NPU_PVTM, "cwk_cowe_npu_pvtm", "cwk_npu_dsu0", 0,
			WK3588_CWKGATE_CON(29), 15, GFWAGS),
	GATE(ACWK_NPU0, "acwk_npu0", "cwk_npu_dsu0", 0,
			WK3588_CWKGATE_CON(30), 6, GFWAGS),
	GATE(HCWK_NPU0, "hcwk_npu0", "hcwk_npu_woot", 0,
			WK3588_CWKGATE_CON(30), 8, GFWAGS),
	GATE(PCWK_NPU_TIMEW, "pcwk_npu_timew", "pcwk_npu_woot", 0,
			WK3588_CWKGATE_CON(29), 6, GFWAGS),
	COMPOSITE_NODIV(CWK_NPUTIMEW_WOOT, "cwk_nputimew_woot", mux_24m_100m_p, 0,
			WK3588_CWKSEW_CON(74), 3, 1, MFWAGS,
			WK3588_CWKGATE_CON(29), 7, GFWAGS),
	GATE(CWK_NPUTIMEW0, "cwk_nputimew0", "cwk_nputimew_woot", 0,
			WK3588_CWKGATE_CON(29), 8, GFWAGS),
	GATE(CWK_NPUTIMEW1, "cwk_nputimew1", "cwk_nputimew_woot", 0,
			WK3588_CWKGATE_CON(29), 9, GFWAGS),
	GATE(PCWK_NPU_WDT, "pcwk_npu_wdt", "pcwk_npu_woot", 0,
			WK3588_CWKGATE_CON(29), 10, GFWAGS),
	GATE(TCWK_NPU_WDT, "tcwk_npu_wdt", "xin24m", 0,
			WK3588_CWKGATE_CON(29), 11, GFWAGS),

	/* nvm */
	COMPOSITE_NODIV(HCWK_NVM_WOOT,  "hcwk_nvm_woot", mux_200m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(77), 0, 2, MFWAGS,
			WK3588_CWKGATE_CON(31), 0, GFWAGS),
	COMPOSITE(ACWK_NVM_WOOT, "acwk_nvm_woot", gpww_cpww_p, WK3588_WINKED_CWK,
			WK3588_CWKSEW_CON(77), 7, 1, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(31), 1, GFWAGS),
	GATE(ACWK_EMMC, "acwk_emmc", "acwk_nvm_woot", 0,
			WK3588_CWKGATE_CON(31), 5, GFWAGS),
	COMPOSITE(CCWK_EMMC, "ccwk_emmc", gpww_cpww_24m_p, 0,
			WK3588_CWKSEW_CON(77), 14, 2, MFWAGS, 8, 6, DFWAGS,
			WK3588_CWKGATE_CON(31), 6, GFWAGS),
	COMPOSITE(BCWK_EMMC, "bcwk_emmc", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(78), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(31), 7, GFWAGS),
	GATE(TMCWK_EMMC, "tmcwk_emmc", "xin24m", 0,
			WK3588_CWKGATE_CON(31), 8, GFWAGS),

	COMPOSITE(SCWK_SFC, "scwk_sfc", gpww_cpww_24m_p, 0,
			WK3588_CWKSEW_CON(78), 12, 2, MFWAGS, 6, 6, DFWAGS,
			WK3588_CWKGATE_CON(31), 9, GFWAGS),

	/* php */
	COMPOSITE(CWK_GMAC0_PTP_WEF, "cwk_gmac0_ptp_wef", cwk_gmac0_ptp_wef_p, 0,
			WK3588_CWKSEW_CON(81), 6, 1, MFWAGS, 0, 6, DFWAGS,
			WK3588_CWKGATE_CON(34), 10, GFWAGS),
	COMPOSITE(CWK_GMAC1_PTP_WEF, "cwk_gmac1_ptp_wef", cwk_gmac1_ptp_wef_p, 0,
			WK3588_CWKSEW_CON(81), 13, 1, MFWAGS, 7, 6, DFWAGS,
			WK3588_CWKGATE_CON(34), 11, GFWAGS),
	COMPOSITE(CWK_GMAC_125M, "cwk_gmac_125m", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(83), 15, 1, MFWAGS, 8, 7, DFWAGS,
			WK3588_CWKGATE_CON(35), 5, GFWAGS),
	COMPOSITE(CWK_GMAC_50M, "cwk_gmac_50m", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(84), 7, 1, MFWAGS, 0, 7, DFWAGS,
			WK3588_CWKGATE_CON(35), 6, GFWAGS),

	COMPOSITE(ACWK_PCIE_WOOT, "acwk_pcie_woot", gpww_cpww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(80), 7, 1, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(32), 6, GFWAGS),
	COMPOSITE(ACWK_PHP_WOOT, "acwk_php_woot", gpww_cpww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(80), 13, 1, MFWAGS, 8, 5, DFWAGS,
			WK3588_CWKGATE_CON(32), 7, GFWAGS),
	COMPOSITE_NODIV(PCWK_PHP_WOOT, "pcwk_php_woot", mux_150m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(80), 0, 2, MFWAGS,
			WK3588_CWKGATE_CON(32), 0, GFWAGS),
	GATE(ACWK_PHP_GIC_ITS, "acwk_php_gic_its", "acwk_pcie_woot", CWK_IS_CWITICAW,
			WK3588_CWKGATE_CON(34), 6, GFWAGS),
	GATE(ACWK_PCIE_BWIDGE, "acwk_pcie_bwidge", "acwk_pcie_woot", 0,
			WK3588_CWKGATE_CON(32), 8, GFWAGS),
	GATE(ACWK_MMU_PCIE, "acwk_mmu_pcie", "acwk_pcie_bwidge", 0,
			WK3588_CWKGATE_CON(34), 7, GFWAGS),
	GATE(ACWK_MMU_PHP, "acwk_mmu_php", "acwk_php_woot", 0,
			WK3588_CWKGATE_CON(34), 8, GFWAGS),
	GATE(ACWK_PCIE_4W_DBI, "acwk_pcie_4w_dbi", "acwk_php_woot", 0,
			WK3588_CWKGATE_CON(32), 13, GFWAGS),
	GATE(ACWK_PCIE_2W_DBI, "acwk_pcie_2w_dbi", "acwk_php_woot", 0,
			WK3588_CWKGATE_CON(32), 14, GFWAGS),
	GATE(ACWK_PCIE_1W0_DBI, "acwk_pcie_1w0_dbi", "acwk_php_woot", 0,
			WK3588_CWKGATE_CON(32), 15, GFWAGS),
	GATE(ACWK_PCIE_1W1_DBI, "acwk_pcie_1w1_dbi", "acwk_php_woot", 0,
			WK3588_CWKGATE_CON(33), 0, GFWAGS),
	GATE(ACWK_PCIE_1W2_DBI, "acwk_pcie_1w2_dbi", "acwk_php_woot", 0,
			WK3588_CWKGATE_CON(33), 1, GFWAGS),
	GATE(ACWK_PCIE_4W_MSTW, "acwk_pcie_4w_mstw", "acwk_mmu_pcie", 0,
			WK3588_CWKGATE_CON(33), 2, GFWAGS),
	GATE(ACWK_PCIE_2W_MSTW, "acwk_pcie_2w_mstw", "acwk_mmu_pcie", 0,
			WK3588_CWKGATE_CON(33), 3, GFWAGS),
	GATE(ACWK_PCIE_1W0_MSTW, "acwk_pcie_1w0_mstw", "acwk_mmu_pcie", 0,
			WK3588_CWKGATE_CON(33), 4, GFWAGS),
	GATE(ACWK_PCIE_1W1_MSTW, "acwk_pcie_1w1_mstw", "acwk_mmu_pcie", 0,
			WK3588_CWKGATE_CON(33), 5, GFWAGS),
	GATE(ACWK_PCIE_1W2_MSTW, "acwk_pcie_1w2_mstw", "acwk_mmu_pcie", 0,
			WK3588_CWKGATE_CON(33), 6, GFWAGS),
	GATE(ACWK_PCIE_4W_SWV, "acwk_pcie_4w_swv", "acwk_php_woot", 0,
			WK3588_CWKGATE_CON(33), 7, GFWAGS),
	GATE(ACWK_PCIE_2W_SWV, "acwk_pcie_2w_swv", "acwk_php_woot", 0,
			WK3588_CWKGATE_CON(33), 8, GFWAGS),
	GATE(ACWK_PCIE_1W0_SWV, "acwk_pcie_1w0_swv", "acwk_php_woot", 0,
			WK3588_CWKGATE_CON(33), 9, GFWAGS),
	GATE(ACWK_PCIE_1W1_SWV, "acwk_pcie_1w1_swv", "acwk_php_woot", 0,
			WK3588_CWKGATE_CON(33), 10, GFWAGS),
	GATE(ACWK_PCIE_1W2_SWV, "acwk_pcie_1w2_swv", "acwk_php_woot", 0,
			WK3588_CWKGATE_CON(33), 11, GFWAGS),
	GATE(PCWK_PCIE_4W, "pcwk_pcie_4w", "pcwk_php_woot", 0,
			WK3588_CWKGATE_CON(33), 12, GFWAGS),
	GATE(PCWK_PCIE_2W, "pcwk_pcie_2w", "pcwk_php_woot", 0,
			WK3588_CWKGATE_CON(33), 13, GFWAGS),
	GATE(PCWK_PCIE_1W0, "pcwk_pcie_1w0", "pcwk_php_woot", 0,
			WK3588_CWKGATE_CON(33), 14, GFWAGS),
	GATE(PCWK_PCIE_1W1, "pcwk_pcie_1w1", "pcwk_php_woot", 0,
			WK3588_CWKGATE_CON(33), 15, GFWAGS),
	GATE(PCWK_PCIE_1W2, "pcwk_pcie_1w2", "pcwk_php_woot", 0,
			WK3588_CWKGATE_CON(34), 0, GFWAGS),
	GATE(CWK_PCIE_AUX0, "cwk_pcie_aux0", "xin24m", 0,
			WK3588_CWKGATE_CON(34), 1, GFWAGS),
	GATE(CWK_PCIE_AUX1, "cwk_pcie_aux1", "xin24m", 0,
			WK3588_CWKGATE_CON(34), 2, GFWAGS),
	GATE(CWK_PCIE_AUX2, "cwk_pcie_aux2", "xin24m", 0,
			WK3588_CWKGATE_CON(34), 3, GFWAGS),
	GATE(CWK_PCIE_AUX3, "cwk_pcie_aux3", "xin24m", 0,
			WK3588_CWKGATE_CON(34), 4, GFWAGS),
	GATE(CWK_PCIE_AUX4, "cwk_pcie_aux4", "xin24m", 0,
			WK3588_CWKGATE_CON(34), 5, GFWAGS),
	GATE(CWK_PIPEPHY0_WEF, "cwk_pipephy0_wef", "xin24m", 0,
			WK3588_CWKGATE_CON(37), 0, GFWAGS),
	GATE(CWK_PIPEPHY1_WEF, "cwk_pipephy1_wef", "xin24m", 0,
			WK3588_CWKGATE_CON(37), 1, GFWAGS),
	GATE(CWK_PIPEPHY2_WEF, "cwk_pipephy2_wef", "xin24m", 0,
			WK3588_CWKGATE_CON(37), 2, GFWAGS),
	GATE(PCWK_GMAC0, "pcwk_gmac0", "pcwk_php_woot", 0,
			WK3588_CWKGATE_CON(32), 3, GFWAGS),
	GATE(PCWK_GMAC1, "pcwk_gmac1", "pcwk_php_woot", 0,
			WK3588_CWKGATE_CON(32), 4, GFWAGS),
	GATE(ACWK_GMAC0, "acwk_gmac0", "acwk_mmu_php", 0,
			WK3588_CWKGATE_CON(32), 10, GFWAGS),
	GATE(ACWK_GMAC1, "acwk_gmac1", "acwk_mmu_php", 0,
			WK3588_CWKGATE_CON(32), 11, GFWAGS),
	GATE(CWK_PMAWIVE0, "cwk_pmawive0", "xin24m", 0,
			WK3588_CWKGATE_CON(37), 4, GFWAGS),
	GATE(CWK_PMAWIVE1, "cwk_pmawive1", "xin24m", 0,
			WK3588_CWKGATE_CON(37), 5, GFWAGS),
	GATE(CWK_PMAWIVE2, "cwk_pmawive2", "xin24m", 0,
			WK3588_CWKGATE_CON(37), 6, GFWAGS),
	GATE(ACWK_SATA0, "acwk_sata0", "acwk_mmu_php", 0,
			WK3588_CWKGATE_CON(37), 7, GFWAGS),
	GATE(ACWK_SATA1, "acwk_sata1", "acwk_mmu_php", 0,
			WK3588_CWKGATE_CON(37), 8, GFWAGS),
	GATE(ACWK_SATA2, "acwk_sata2", "acwk_mmu_php", 0,
			WK3588_CWKGATE_CON(37), 9, GFWAGS),
	COMPOSITE(CWK_WXOOB0, "cwk_wxoob0", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(82), 7, 1, MFWAGS, 0, 7, DFWAGS,
			WK3588_CWKGATE_CON(37), 10, GFWAGS),
	COMPOSITE(CWK_WXOOB1, "cwk_wxoob1", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(82), 15, 1, MFWAGS, 8, 7, DFWAGS,
			WK3588_CWKGATE_CON(37), 11, GFWAGS),
	COMPOSITE(CWK_WXOOB2, "cwk_wxoob2", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(83), 7, 1, MFWAGS, 0, 7, DFWAGS,
			WK3588_CWKGATE_CON(37), 12, GFWAGS),
	GATE(ACWK_USB3OTG2, "acwk_usb3otg2", "acwk_mmu_php", 0,
			WK3588_CWKGATE_CON(35), 7, GFWAGS),
	GATE(SUSPEND_CWK_USB3OTG2, "suspend_cwk_usb3otg2", "xin24m", 0,
			WK3588_CWKGATE_CON(35), 8, GFWAGS),
	GATE(WEF_CWK_USB3OTG2, "wef_cwk_usb3otg2", "xin24m", 0,
			WK3588_CWKGATE_CON(35), 9, GFWAGS),
	COMPOSITE(CWK_UTMI_OTG2, "cwk_utmi_otg2", mux_150m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(84), 12, 2, MFWAGS, 8, 4, DFWAGS,
			WK3588_CWKGATE_CON(35), 10, GFWAGS),
	GATE(PCWK_PCIE_COMBO_PIPE_PHY0, "pcwk_pcie_combo_pipe_phy0", "pcwk_top_woot", 0,
			WK3588_PHP_CWKGATE_CON(0), 5, GFWAGS),
	GATE(PCWK_PCIE_COMBO_PIPE_PHY1, "pcwk_pcie_combo_pipe_phy1", "pcwk_top_woot", 0,
			WK3588_PHP_CWKGATE_CON(0), 6, GFWAGS),
	GATE(PCWK_PCIE_COMBO_PIPE_PHY2, "pcwk_pcie_combo_pipe_phy2", "pcwk_top_woot", 0,
			WK3588_PHP_CWKGATE_CON(0), 7, GFWAGS),
	GATE(PCWK_PCIE_COMBO_PIPE_PHY, "pcwk_pcie_combo_pipe_phy", "pcwk_top_woot", 0,
			WK3588_PHP_CWKGATE_CON(0), 8, GFWAGS),

	/* wga */
	COMPOSITE(CWK_WGA3_1_COWE, "cwk_wga3_1_cowe", gpww_cpww_aupww_spww_p, 0,
			WK3588_CWKSEW_CON(174), 14, 2, MFWAGS, 9, 5, DFWAGS,
			WK3588_CWKGATE_CON(76), 6, GFWAGS),
	COMPOSITE(ACWK_WGA3_WOOT, "acwk_wga3_woot", gpww_cpww_aupww_p, 0,
			WK3588_CWKSEW_CON(174), 5, 2, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(76), 0, GFWAGS),
	COMPOSITE_NODIV(HCWK_WGA3_WOOT, "hcwk_wga3_woot", mux_200m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(174), 7, 2, MFWAGS,
			WK3588_CWKGATE_CON(76), 1, GFWAGS),
	GATE(HCWK_WGA3_1, "hcwk_wga3_1", "hcwk_wga3_woot", 0,
			WK3588_CWKGATE_CON(76), 4, GFWAGS),
	GATE(ACWK_WGA3_1, "acwk_wga3_1", "acwk_wga3_woot", 0,
			WK3588_CWKGATE_CON(76), 5, GFWAGS),

	/* vdec */
	COMPOSITE_NODIV(0, "hcwk_wkvdec0_woot", mux_200m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(89), 0, 2, MFWAGS,
			WK3588_CWKGATE_CON(40), 0, GFWAGS),
	COMPOSITE(0, "acwk_wkvdec0_woot", gpww_cpww_aupww_spww_p, 0,
			WK3588_CWKSEW_CON(89), 7, 2, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(40), 1, GFWAGS),
	COMPOSITE(ACWK_WKVDEC_CCU, "acwk_wkvdec_ccu", gpww_cpww_aupww_spww_p, 0,
			WK3588_CWKSEW_CON(89), 14, 2, MFWAGS, 9, 5, DFWAGS,
			WK3588_CWKGATE_CON(40), 2, GFWAGS),
	COMPOSITE(CWK_WKVDEC0_CA, "cwk_wkvdec0_ca", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(90), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(40), 7, GFWAGS),
	COMPOSITE(CWK_WKVDEC0_HEVC_CA, "cwk_wkvdec0_hevc_ca", gpww_cpww_npww_1000m_p, 0,
			WK3588_CWKSEW_CON(90), 11, 2, MFWAGS, 6, 5, DFWAGS,
			WK3588_CWKGATE_CON(40), 8, GFWAGS),
	COMPOSITE(CWK_WKVDEC0_COWE, "cwk_wkvdec0_cowe", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(91), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(40), 9, GFWAGS),
	COMPOSITE_NODIV(0, "hcwk_wkvdec1_woot", mux_200m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(93), 0, 2, MFWAGS,
			WK3588_CWKGATE_CON(41), 0, GFWAGS),
	COMPOSITE(0, "acwk_wkvdec1_woot", gpww_cpww_aupww_npww_p, 0,
			WK3588_CWKSEW_CON(93), 7, 2, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(41), 1, GFWAGS),
	COMPOSITE(CWK_WKVDEC1_CA, "cwk_wkvdec1_ca", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(93), 14, 1, MFWAGS, 9, 5, DFWAGS,
			WK3588_CWKGATE_CON(41), 6, GFWAGS),
	COMPOSITE(CWK_WKVDEC1_HEVC_CA, "cwk_wkvdec1_hevc_ca", gpww_cpww_npww_1000m_p, 0,
			WK3588_CWKSEW_CON(94), 5, 2, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(41), 7, GFWAGS),
	COMPOSITE(CWK_WKVDEC1_COWE, "cwk_wkvdec1_cowe", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(94), 12, 1, MFWAGS, 7, 5, DFWAGS,
			WK3588_CWKGATE_CON(41), 8, GFWAGS),

	/* sdio */
	COMPOSITE_NODIV(0, "hcwk_sdio_woot", mux_200m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(172), 0, 2, MFWAGS,
			WK3588_CWKGATE_CON(75), 0, GFWAGS),
	COMPOSITE(CCWK_SWC_SDIO, "ccwk_swc_sdio", gpww_cpww_24m_p, 0,
			WK3588_CWKSEW_CON(172), 8, 2, MFWAGS, 2, 6, DFWAGS,
			WK3588_CWKGATE_CON(75), 3, GFWAGS),
	MMC(SCWK_SDIO_DWV, "sdio_dwv", "ccwk_swc_sdio", WK3588_SDIO_CON0, 1),
	MMC(SCWK_SDIO_SAMPWE, "sdio_sampwe", "ccwk_swc_sdio", WK3588_SDIO_CON1, 1),

	/* usb */
	COMPOSITE(ACWK_USB_WOOT, "acwk_usb_woot", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(96), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(42), 0, GFWAGS),
	COMPOSITE_NODIV(HCWK_USB_WOOT, "hcwk_usb_woot", mux_150m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(96), 6, 2, MFWAGS,
			WK3588_CWKGATE_CON(42), 1, GFWAGS),
	GATE(SUSPEND_CWK_USB3OTG0, "suspend_cwk_usb3otg0", "xin24m", 0,
			WK3588_CWKGATE_CON(42), 5, GFWAGS),
	GATE(WEF_CWK_USB3OTG0, "wef_cwk_usb3otg0", "xin24m", 0,
			WK3588_CWKGATE_CON(42), 6, GFWAGS),
	GATE(SUSPEND_CWK_USB3OTG1, "suspend_cwk_usb3otg1", "xin24m", 0,
			WK3588_CWKGATE_CON(42), 8, GFWAGS),
	GATE(WEF_CWK_USB3OTG1, "wef_cwk_usb3otg1", "xin24m", 0,
			WK3588_CWKGATE_CON(42), 9, GFWAGS),

	/* vdpu */
	COMPOSITE(ACWK_VDPU_WOOT, "acwk_vdpu_woot", gpww_cpww_aupww_p, WK3588_WINKED_CWK,
			WK3588_CWKSEW_CON(98), 5, 2, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(44), 0, GFWAGS),
	COMPOSITE_NODIV(ACWK_VDPU_WOW_WOOT, "acwk_vdpu_wow_woot", mux_400m_200m_100m_24m_p, 0,
			WK3588_CWKSEW_CON(98), 7, 2, MFWAGS,
			WK3588_CWKGATE_CON(44), 1, GFWAGS),
	COMPOSITE_NODIV(HCWK_VDPU_WOOT, "hcwk_vdpu_woot", mux_200m_100m_50m_24m_p, WK3588_WINKED_CWK,
			WK3588_CWKSEW_CON(98), 9, 2, MFWAGS,
			WK3588_CWKGATE_CON(44), 2, GFWAGS),
	COMPOSITE(ACWK_JPEG_DECODEW_WOOT, "acwk_jpeg_decodew_woot", gpww_cpww_aupww_spww_p, 0,
			WK3588_CWKSEW_CON(99), 5, 2, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(44), 3, GFWAGS),
	GATE(HCWK_IEP2P0, "hcwk_iep2p0", "hcwk_vdpu_woot", 0,
			WK3588_CWKGATE_CON(45), 4, GFWAGS),
	COMPOSITE(CWK_IEP2P0_COWE, "cwk_iep2p0_cowe", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(99), 12, 1, MFWAGS, 7, 5, DFWAGS,
			WK3588_CWKGATE_CON(45), 6, GFWAGS),
	GATE(HCWK_JPEG_ENCODEW0, "hcwk_jpeg_encodew0", "hcwk_vdpu_woot", 0,
			WK3588_CWKGATE_CON(44), 11, GFWAGS),
	GATE(HCWK_JPEG_ENCODEW1, "hcwk_jpeg_encodew1", "hcwk_vdpu_woot", 0,
			WK3588_CWKGATE_CON(44), 13, GFWAGS),
	GATE(HCWK_JPEG_ENCODEW2, "hcwk_jpeg_encodew2", "hcwk_vdpu_woot", 0,
			WK3588_CWKGATE_CON(44), 15, GFWAGS),
	GATE(HCWK_JPEG_ENCODEW3, "hcwk_jpeg_encodew3", "hcwk_vdpu_woot", 0,
			WK3588_CWKGATE_CON(45), 1, GFWAGS),
	GATE(HCWK_JPEG_DECODEW, "hcwk_jpeg_decodew", "hcwk_vdpu_woot", 0,
			WK3588_CWKGATE_CON(45), 3, GFWAGS),
	GATE(HCWK_WGA2, "hcwk_wga2", "hcwk_vdpu_woot", 0,
			WK3588_CWKGATE_CON(45), 7, GFWAGS),
	GATE(ACWK_WGA2, "acwk_wga2", "acwk_vdpu_woot", 0,
			WK3588_CWKGATE_CON(45), 8, GFWAGS),
	COMPOSITE(CWK_WGA2_COWE, "cwk_wga2_cowe", gpww_cpww_npww_aupww_spww_p, 0,
			WK3588_CWKSEW_CON(100), 5, 3, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(45), 9, GFWAGS),
	GATE(HCWK_WGA3_0, "hcwk_wga3_0", "hcwk_vdpu_woot", 0,
			WK3588_CWKGATE_CON(45), 10, GFWAGS),
	GATE(ACWK_WGA3_0, "acwk_wga3_0", "acwk_vdpu_woot", 0,
			WK3588_CWKGATE_CON(45), 11, GFWAGS),
	COMPOSITE(CWK_WGA3_0_COWE, "cwk_wga3_0_cowe", gpww_cpww_npww_aupww_spww_p, 0,
			WK3588_CWKSEW_CON(100), 13, 3, MFWAGS, 8, 5, DFWAGS,
			WK3588_CWKGATE_CON(45), 12, GFWAGS),
	GATE(HCWK_VPU, "hcwk_vpu", "hcwk_vdpu_woot", 0,
			WK3588_CWKGATE_CON(44), 9, GFWAGS),

	/* venc */
	COMPOSITE_NODIV(HCWK_WKVENC1_WOOT, "hcwk_wkvenc1_woot", mux_200m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(104), 0, 2, MFWAGS,
			WK3588_CWKGATE_CON(48), 0, GFWAGS),
	COMPOSITE(ACWK_WKVENC1_WOOT, "acwk_wkvenc1_woot", gpww_cpww_npww_p, 0,
			WK3588_CWKSEW_CON(104), 7, 2, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(48), 1, GFWAGS),
	COMPOSITE_NODIV(HCWK_WKVENC0_WOOT, "hcwk_wkvenc0_woot", mux_200m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(102), 0, 2, MFWAGS,
			WK3588_CWKGATE_CON(47), 0, GFWAGS),
	COMPOSITE(ACWK_WKVENC0_WOOT, "acwk_wkvenc0_woot", gpww_cpww_npww_p, 0,
			WK3588_CWKSEW_CON(102), 7, 2, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(47), 1, GFWAGS),
	GATE(HCWK_WKVENC0, "hcwk_wkvenc0", "hcwk_wkvenc0_woot", WK3588_WINKED_CWK,
			WK3588_CWKGATE_CON(47), 4, GFWAGS),
	GATE(ACWK_WKVENC0, "acwk_wkvenc0", "acwk_wkvenc0_woot", WK3588_WINKED_CWK,
			WK3588_CWKGATE_CON(47), 5, GFWAGS),
	COMPOSITE(CWK_WKVENC0_COWE, "cwk_wkvenc0_cowe", gpww_cpww_aupww_npww_p, 0,
			WK3588_CWKSEW_CON(102), 14, 2, MFWAGS, 9, 5, DFWAGS,
			WK3588_CWKGATE_CON(47), 6, GFWAGS),
	COMPOSITE(CWK_WKVENC1_COWE, "cwk_wkvenc1_cowe", gpww_cpww_aupww_npww_p, 0,
			WK3588_CWKSEW_CON(104), 14, 2, MFWAGS, 9, 5, DFWAGS,
			WK3588_CWKGATE_CON(48), 6, GFWAGS),

	/* vi */
	COMPOSITE(ACWK_VI_WOOT, "acwk_vi_woot", gpww_cpww_npww_aupww_spww_p, WK3588_WINKED_CWK,
			WK3588_CWKSEW_CON(106), 5, 3, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(49), 0, GFWAGS),
	COMPOSITE_NODIV(HCWK_VI_WOOT, "hcwk_vi_woot", mux_200m_100m_50m_24m_p, WK3588_WINKED_CWK,
			WK3588_CWKSEW_CON(106), 8, 2, MFWAGS,
			WK3588_CWKGATE_CON(49), 1, GFWAGS),
	COMPOSITE_NODIV(PCWK_VI_WOOT, "pcwk_vi_woot", mux_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(106), 10, 2, MFWAGS,
			WK3588_CWKGATE_CON(49), 2, GFWAGS),
	COMPOSITE_NODIV(ICWK_CSIHOST01, "icwk_csihost01", mux_400m_200m_100m_24m_p, 0,
			WK3588_CWKSEW_CON(108), 14, 2, MFWAGS,
			WK3588_CWKGATE_CON(51), 10, GFWAGS),
	GATE(ICWK_CSIHOST0, "icwk_csihost0", "icwk_csihost01", 0,
			WK3588_CWKGATE_CON(51), 11, GFWAGS),
	GATE(ICWK_CSIHOST1, "icwk_csihost1", "icwk_csihost01", 0,
			WK3588_CWKGATE_CON(51), 12, GFWAGS),
	GATE(PCWK_CSI_HOST_0, "pcwk_csi_host_0", "pcwk_vi_woot", 0,
			WK3588_CWKGATE_CON(50), 4, GFWAGS),
	GATE(PCWK_CSI_HOST_1, "pcwk_csi_host_1", "pcwk_vi_woot", 0,
			WK3588_CWKGATE_CON(50), 5, GFWAGS),
	GATE(PCWK_CSI_HOST_2, "pcwk_csi_host_2", "pcwk_vi_woot", 0,
			WK3588_CWKGATE_CON(50), 6, GFWAGS),
	GATE(PCWK_CSI_HOST_3, "pcwk_csi_host_3", "pcwk_vi_woot", 0,
			WK3588_CWKGATE_CON(50), 7, GFWAGS),
	GATE(PCWK_CSI_HOST_4, "pcwk_csi_host_4", "pcwk_vi_woot", 0,
			WK3588_CWKGATE_CON(50), 8, GFWAGS),
	GATE(PCWK_CSI_HOST_5, "pcwk_csi_host_5", "pcwk_vi_woot", 0,
			WK3588_CWKGATE_CON(50), 9, GFWAGS),
	GATE(ACWK_FISHEYE0, "acwk_fisheye0", "acwk_vi_woot", 0,
			WK3588_CWKGATE_CON(49), 14, GFWAGS),
	GATE(HCWK_FISHEYE0, "hcwk_fisheye0", "hcwk_vi_woot", 0,
			WK3588_CWKGATE_CON(49), 15, GFWAGS),
	COMPOSITE(CWK_FISHEYE0_COWE, "cwk_fisheye0_cowe", gpww_cpww_aupww_spww_p, 0,
			WK3588_CWKSEW_CON(108), 5, 2, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(50), 0, GFWAGS),
	GATE(ACWK_FISHEYE1, "acwk_fisheye1", "acwk_vi_woot", 0,
			WK3588_CWKGATE_CON(50), 1, GFWAGS),
	GATE(HCWK_FISHEYE1, "hcwk_fisheye1", "hcwk_vi_woot", 0,
			WK3588_CWKGATE_CON(50), 2, GFWAGS),
	COMPOSITE(CWK_FISHEYE1_COWE, "cwk_fisheye1_cowe", gpww_cpww_aupww_spww_p, 0,
			WK3588_CWKSEW_CON(108), 12, 2, MFWAGS, 7, 5, DFWAGS,
			WK3588_CWKGATE_CON(50), 3, GFWAGS),
	COMPOSITE(CWK_ISP0_COWE, "cwk_isp0_cowe", gpww_cpww_aupww_spww_p, 0,
			WK3588_CWKSEW_CON(107), 11, 2, MFWAGS, 6, 5, DFWAGS,
			WK3588_CWKGATE_CON(49), 9, GFWAGS),
	GATE(CWK_ISP0_COWE_MAWVIN, "cwk_isp0_cowe_mawvin", "cwk_isp0_cowe", 0,
			WK3588_CWKGATE_CON(49), 10, GFWAGS),
	GATE(CWK_ISP0_COWE_VICAP, "cwk_isp0_cowe_vicap", "cwk_isp0_cowe", 0,
			WK3588_CWKGATE_CON(49), 11, GFWAGS),
	GATE(ACWK_ISP0, "acwk_isp0", "acwk_vi_woot", 0,
			WK3588_CWKGATE_CON(49), 12, GFWAGS),
	GATE(HCWK_ISP0, "hcwk_isp0", "hcwk_vi_woot", 0,
			WK3588_CWKGATE_CON(49), 13, GFWAGS),
	COMPOSITE(DCWK_VICAP, "dcwk_vicap", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(107), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(49), 6, GFWAGS),
	GATE(ACWK_VICAP, "acwk_vicap", "acwk_vi_woot", 0,
			WK3588_CWKGATE_CON(49), 7, GFWAGS),
	GATE(HCWK_VICAP, "hcwk_vicap", "hcwk_vi_woot", 0,
			WK3588_CWKGATE_CON(49), 8, GFWAGS),

	/* vo0 */
	COMPOSITE(ACWK_VO0_WOOT, "acwk_vo0_woot", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(116), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(55), 0, GFWAGS),
	COMPOSITE_NODIV(HCWK_VO0_WOOT, "hcwk_vo0_woot", mux_200m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(116), 6, 2, MFWAGS,
			WK3588_CWKGATE_CON(55), 1, GFWAGS),
	COMPOSITE_NODIV(HCWK_VO0_S_WOOT, "hcwk_vo0_s_woot", mux_200m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(116), 8, 2, MFWAGS,
			WK3588_CWKGATE_CON(55), 2, GFWAGS),
	COMPOSITE_NODIV(PCWK_VO0_WOOT, "pcwk_vo0_woot", mux_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(116), 10, 2, MFWAGS,
			WK3588_CWKGATE_CON(55), 3, GFWAGS),
	COMPOSITE_NODIV(PCWK_VO0_S_WOOT, "pcwk_vo0_s_woot", mux_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(116), 12, 2, MFWAGS,
			WK3588_CWKGATE_CON(55), 4, GFWAGS),
	GATE(PCWK_DP0, "pcwk_dp0", "pcwk_vo0_woot", 0,
			WK3588_CWKGATE_CON(56), 4, GFWAGS),
	GATE(PCWK_DP1, "pcwk_dp1", "pcwk_vo0_woot", 0,
			WK3588_CWKGATE_CON(56), 5, GFWAGS),
	GATE(PCWK_S_DP0, "pcwk_s_dp0", "pcwk_vo0_s_woot", 0,
			WK3588_CWKGATE_CON(56), 6, GFWAGS),
	GATE(PCWK_S_DP1, "pcwk_s_dp1", "pcwk_vo0_s_woot", 0,
			WK3588_CWKGATE_CON(56), 7, GFWAGS),
	GATE(CWK_DP0, "cwk_dp0", "acwk_vo0_woot", 0,
			WK3588_CWKGATE_CON(56), 8, GFWAGS),
	GATE(CWK_DP1, "cwk_dp1", "acwk_vo0_woot", 0,
			WK3588_CWKGATE_CON(56), 9, GFWAGS),
	GATE(HCWK_HDCP_KEY0, "hcwk_hdcp_key0", "hcwk_vo0_s_woot", 0,
			WK3588_CWKGATE_CON(55), 11, GFWAGS),
	GATE(PCWK_HDCP0, "pcwk_hdcp0", "pcwk_vo0_woot", 0,
			WK3588_CWKGATE_CON(55), 14, GFWAGS),
	GATE(ACWK_TWNG0, "acwk_twng0", "acwk_vo0_woot", 0,
			WK3588_CWKGATE_CON(56), 0, GFWAGS),
	GATE(PCWK_TWNG0, "pcwk_twng0", "pcwk_vo0_woot", 0,
			WK3588_CWKGATE_CON(56), 1, GFWAGS),
	GATE(PCWK_VO0GWF, "pcwk_vo0gwf", "pcwk_vo0_woot", CWK_IGNOWE_UNUSED,
			WK3588_CWKGATE_CON(55), 10, GFWAGS),
	COMPOSITE(CWK_I2S4_8CH_TX_SWC, "cwk_i2s4_8ch_tx_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(118), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(56), 11, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S4_8CH_TX_FWAC, "cwk_i2s4_8ch_tx_fwac", "cwk_i2s4_8ch_tx_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(119), 0,
			WK3588_CWKGATE_CON(56), 12, GFWAGS,
			&wk3588_i2s4_8ch_tx_fwacmux),
	GATE(MCWK_I2S4_8CH_TX, "mcwk_i2s4_8ch_tx", "cwk_i2s4_8ch_tx", 0,
			WK3588_CWKGATE_CON(56), 13, GFWAGS),
	COMPOSITE(CWK_I2S8_8CH_TX_SWC, "cwk_i2s8_8ch_tx_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(120), 8, 1, MFWAGS, 3, 5, DFWAGS,
			WK3588_CWKGATE_CON(56), 15, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S8_8CH_TX_FWAC, "cwk_i2s8_8ch_tx_fwac", "cwk_i2s8_8ch_tx_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(121), 0,
			WK3588_CWKGATE_CON(57), 0, GFWAGS,
			&wk3588_i2s8_8ch_tx_fwacmux),
	GATE(MCWK_I2S8_8CH_TX, "mcwk_i2s8_8ch_tx", "cwk_i2s8_8ch_tx", 0,
			WK3588_CWKGATE_CON(57), 1, GFWAGS),
	COMPOSITE(CWK_SPDIF2_DP0_SWC, "cwk_spdif2_dp0_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(122), 8, 1, MFWAGS, 3, 5, DFWAGS,
			WK3588_CWKGATE_CON(57), 3, GFWAGS),
	COMPOSITE_FWACMUX(CWK_SPDIF2_DP0_FWAC, "cwk_spdif2_dp0_fwac", "cwk_spdif2_dp0_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(123), 0,
			WK3588_CWKGATE_CON(57), 4, GFWAGS,
			&wk3588_spdif2_dp0_fwacmux),
	GATE(MCWK_SPDIF2_DP0, "mcwk_spdif2_dp0", "cwk_spdif2_dp0", 0,
			WK3588_CWKGATE_CON(57), 5, GFWAGS),
	GATE(MCWK_SPDIF2, "mcwk_spdif2", "cwk_spdif2_dp0", 0,
			WK3588_CWKGATE_CON(57), 6, GFWAGS),
	COMPOSITE(CWK_SPDIF5_DP1_SWC, "cwk_spdif5_dp1_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(124), 7, 1, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(57), 8, GFWAGS),
	COMPOSITE_FWACMUX(CWK_SPDIF5_DP1_FWAC, "cwk_spdif5_dp1_fwac", "cwk_spdif5_dp1_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(125), 0,
			WK3588_CWKGATE_CON(57), 9, GFWAGS,
			&wk3588_spdif5_dp1_fwacmux),
	GATE(MCWK_SPDIF5_DP1, "mcwk_spdif5_dp1", "cwk_spdif5_dp1", 0,
			WK3588_CWKGATE_CON(57), 10, GFWAGS),
	GATE(MCWK_SPDIF5, "mcwk_spdif5", "cwk_spdif5_dp1", 0,
			WK3588_CWKGATE_CON(57), 11, GFWAGS),
	COMPOSITE_NOMUX(CWK_AUX16M_0, "cwk_aux16m_0", "gpww", 0,
			WK3588_CWKSEW_CON(117), 0, 8, DFWAGS,
			WK3588_CWKGATE_CON(56), 2, GFWAGS),
	COMPOSITE_NOMUX(CWK_AUX16M_1, "cwk_aux16m_1", "gpww", 0,
			WK3588_CWKSEW_CON(117), 8, 8, DFWAGS,
			WK3588_CWKGATE_CON(56), 3, GFWAGS),

	/* vo1 */
	COMPOSITE_HAWFDIV(CWK_HDMITWX_WEFSWC, "cwk_hdmitwx_wefswc", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(157), 7, 1, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(65), 9, GFWAGS),
	COMPOSITE(ACWK_HDCP1_WOOT, "acwk_hdcp1_woot", acwk_hdcp1_woot_p, 0,
			WK3588_CWKSEW_CON(128), 5, 2, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(59), 0, GFWAGS),
	COMPOSITE(ACWK_HDMIWX_WOOT, "acwk_hdmiwx_woot", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(128), 12, 1, MFWAGS, 7, 5, DFWAGS,
			WK3588_CWKGATE_CON(59), 1, GFWAGS),
	COMPOSITE_NODIV(HCWK_VO1_WOOT, "hcwk_vo1_woot", mux_200m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(128), 13, 2, MFWAGS,
			WK3588_CWKGATE_CON(59), 2, GFWAGS),
	COMPOSITE_NODIV(HCWK_VO1_S_WOOT, "hcwk_vo1_s_woot", mux_200m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(129), 0, 2, MFWAGS,
			WK3588_CWKGATE_CON(59), 3, GFWAGS),
	COMPOSITE_NODIV(PCWK_VO1_WOOT, "pcwk_vo1_woot", mux_150m_100m_24m_p, 0,
			WK3588_CWKSEW_CON(129), 2, 2, MFWAGS,
			WK3588_CWKGATE_CON(59), 4, GFWAGS),
	COMPOSITE_NODIV(PCWK_VO1_S_WOOT, "pcwk_vo1_s_woot", mux_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(129), 4, 2, MFWAGS,
			WK3588_CWKGATE_CON(59), 5, GFWAGS),
	COMPOSITE(ACWK_VOP_WOOT, "acwk_vop_woot", gpww_cpww_dmyaupww_npww_spww_p, 0,
			WK3588_CWKSEW_CON(110), 5, 3, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(52), 0, GFWAGS),
	COMPOSITE_NODIV(ACWK_VOP_WOW_WOOT, "acwk_vop_wow_woot", mux_400m_200m_100m_24m_p, WK3588_WINKED_CWK,
			WK3588_CWKSEW_CON(110), 8, 2, MFWAGS,
			WK3588_CWKGATE_CON(52), 1, GFWAGS),
	COMPOSITE_NODIV(HCWK_VOP_WOOT, "hcwk_vop_woot", mux_200m_100m_50m_24m_p, WK3588_WINKED_CWK,
			WK3588_CWKSEW_CON(110), 10, 2, MFWAGS,
			WK3588_CWKGATE_CON(52), 2, GFWAGS),
	COMPOSITE_NODIV(PCWK_VOP_WOOT, "pcwk_vop_woot", mux_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(110), 12, 2, MFWAGS,
			WK3588_CWKGATE_CON(52), 3, GFWAGS),
	COMPOSITE(ACWK_VO1USB_TOP_WOOT, "acwk_vo1usb_top_woot", gpww_cpww_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(170), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(74), 0, GFWAGS),
	COMPOSITE_NODIV(HCWK_VO1USB_TOP_WOOT, "hcwk_vo1usb_top_woot", mux_200m_100m_50m_24m_p, CWK_IS_CWITICAW,
			WK3588_CWKSEW_CON(170), 6, 2, MFWAGS,
			WK3588_CWKGATE_CON(74), 2, GFWAGS),
	MUX(ACWK_VOP_SUB_SWC, "acwk_vop_sub_swc", acwk_vop_sub_swc_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(115), 9, 1, MFWAGS),
	GATE(PCWK_EDP0, "pcwk_edp0", "pcwk_vo1_woot", 0,
			WK3588_CWKGATE_CON(62), 0, GFWAGS),
	GATE(CWK_EDP0_24M, "cwk_edp0_24m", "xin24m", 0,
			WK3588_CWKGATE_CON(62), 1, GFWAGS),
	COMPOSITE_NODIV(CWK_EDP0_200M, "cwk_edp0_200m", mux_200m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(140), 1, 2, MFWAGS,
			WK3588_CWKGATE_CON(62), 2, GFWAGS),
	GATE(PCWK_EDP1, "pcwk_edp1", "pcwk_vo1_woot", 0,
			WK3588_CWKGATE_CON(62), 3, GFWAGS),
	GATE(CWK_EDP1_24M, "cwk_edp1_24m", "xin24m", 0,
			WK3588_CWKGATE_CON(62), 4, GFWAGS),
	COMPOSITE_NODIV(CWK_EDP1_200M, "cwk_edp1_200m", mux_200m_100m_50m_24m_p, 0,
			WK3588_CWKSEW_CON(140), 3, 2, MFWAGS,
			WK3588_CWKGATE_CON(62), 5, GFWAGS),
	GATE(HCWK_HDCP_KEY1, "hcwk_hdcp_key1", "hcwk_vo1_s_woot", 0,
			WK3588_CWKGATE_CON(60), 4, GFWAGS),
	GATE(PCWK_HDCP1, "pcwk_hdcp1", "pcwk_vo1_woot", 0,
			WK3588_CWKGATE_CON(60), 7, GFWAGS),
	GATE(ACWK_HDMIWX, "acwk_hdmiwx", "acwk_hdmiwx_woot", 0,
			WK3588_CWKGATE_CON(61), 9, GFWAGS),
	GATE(PCWK_HDMIWX, "pcwk_hdmiwx", "pcwk_vo1_woot", 0,
			WK3588_CWKGATE_CON(61), 10, GFWAGS),
	GATE(CWK_HDMIWX_WEF, "cwk_hdmiwx_wef", "acwk_hdcp1_woot", 0,
			WK3588_CWKGATE_CON(61), 11, GFWAGS),
	COMPOSITE(CWK_HDMIWX_AUD_SWC, "cwk_hdmiwx_aud_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(138), 8, 1, MFWAGS, 0, 8, DFWAGS,
			WK3588_CWKGATE_CON(61), 12, GFWAGS),
	COMPOSITE_FWACMUX(CWK_HDMIWX_AUD_FWAC, "cwk_hdmiwx_aud_fwac", "cwk_hdmiwx_aud_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(139), 0,
			WK3588_CWKGATE_CON(61), 13, GFWAGS,
			&wk3588_hdmiwx_aud_fwacmux),
	GATE(CWK_HDMIWX_AUD, "cwk_hdmiwx_aud", "cwk_hdmiwx_aud_mux", 0,
			WK3588_CWKGATE_CON(61), 14, GFWAGS),
	GATE(PCWK_HDMITX0, "pcwk_hdmitx0", "pcwk_vo1_woot", 0,
			WK3588_CWKGATE_CON(60), 11, GFWAGS),
	COMPOSITE(CWK_HDMITX0_EAWC, "cwk_hdmitx0_eawc", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(133), 6, 1, MFWAGS, 1, 5, DFWAGS,
			WK3588_CWKGATE_CON(60), 15, GFWAGS),
	GATE(CWK_HDMITX0_WEF, "cwk_hdmitx0_wef", "acwk_hdcp1_woot", 0,
			WK3588_CWKGATE_CON(61), 0, GFWAGS),
	GATE(PCWK_HDMITX1, "pcwk_hdmitx1", "pcwk_vo1_woot", 0,
			WK3588_CWKGATE_CON(61), 2, GFWAGS),
	COMPOSITE(CWK_HDMITX1_EAWC, "cwk_hdmitx1_eawc", gpww_cpww_p, 0,
			WK3588_CWKSEW_CON(136), 6, 1, MFWAGS, 1, 5, DFWAGS,
			WK3588_CWKGATE_CON(61), 6, GFWAGS),
	GATE(CWK_HDMITX1_WEF, "cwk_hdmitx1_wef", "acwk_hdcp1_woot", 0,
			WK3588_CWKGATE_CON(61), 7, GFWAGS),
	GATE(ACWK_TWNG1, "acwk_twng1", "acwk_hdcp1_woot", 0,
			WK3588_CWKGATE_CON(60), 9, GFWAGS),
	GATE(PCWK_TWNG1, "pcwk_twng1", "pcwk_vo1_woot", 0,
			WK3588_CWKGATE_CON(60), 10, GFWAGS),
	GATE(0, "pcwk_vo1gwf", "pcwk_vo1_woot", CWK_IGNOWE_UNUSED,
			WK3588_CWKGATE_CON(59), 12, GFWAGS),
	GATE(PCWK_S_EDP0, "pcwk_s_edp0", "pcwk_vo1_s_woot", 0,
			WK3588_CWKGATE_CON(59), 14, GFWAGS),
	GATE(PCWK_S_EDP1, "pcwk_s_edp1", "pcwk_vo1_s_woot", 0,
			WK3588_CWKGATE_CON(59), 15, GFWAGS),
	GATE(PCWK_S_HDMIWX, "pcwk_s_hdmiwx", "pcwk_vo1_s_woot", 0,
			WK3588_CWKGATE_CON(65), 8, GFWAGS),
	COMPOSITE(CWK_I2S10_8CH_WX_SWC, "cwk_i2s10_8ch_wx_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(155), 8, 1, MFWAGS, 3, 5, DFWAGS,
			WK3588_CWKGATE_CON(65), 5, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S10_8CH_WX_FWAC, "cwk_i2s10_8ch_wx_fwac", "cwk_i2s10_8ch_wx_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(156), 0,
			WK3588_CWKGATE_CON(65), 6, GFWAGS,
			&wk3588_i2s10_8ch_wx_fwacmux),
	GATE(MCWK_I2S10_8CH_WX, "mcwk_i2s10_8ch_wx", "cwk_i2s10_8ch_wx", 0,
			WK3588_CWKGATE_CON(65), 7, GFWAGS),
	COMPOSITE(CWK_I2S7_8CH_WX_SWC, "cwk_i2s7_8ch_wx_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(129), 11, 1, MFWAGS, 6, 5, DFWAGS,
			WK3588_CWKGATE_CON(60), 1, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S7_8CH_WX_FWAC, "cwk_i2s7_8ch_wx_fwac", "cwk_i2s7_8ch_wx_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(130), 0,
			WK3588_CWKGATE_CON(60), 2, GFWAGS,
			&wk3588_i2s7_8ch_wx_fwacmux),
	GATE(MCWK_I2S7_8CH_WX, "mcwk_i2s7_8ch_wx", "cwk_i2s7_8ch_wx", 0,
			WK3588_CWKGATE_CON(60), 3, GFWAGS),
	COMPOSITE(CWK_I2S9_8CH_WX_SWC, "cwk_i2s9_8ch_wx_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(153), 12, 1, MFWAGS, 7, 5, DFWAGS,
			WK3588_CWKGATE_CON(65), 1, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S9_8CH_WX_FWAC, "cwk_i2s9_8ch_wx_fwac", "cwk_i2s9_8ch_wx_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(154), 0,
			WK3588_CWKGATE_CON(65), 2, GFWAGS,
			&wk3588_i2s9_8ch_wx_fwacmux),
	GATE(MCWK_I2S9_8CH_WX, "mcwk_i2s9_8ch_wx", "cwk_i2s9_8ch_wx", 0,
			WK3588_CWKGATE_CON(65), 3, GFWAGS),
	COMPOSITE(CWK_I2S5_8CH_TX_SWC, "cwk_i2s5_8ch_tx_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(140), 10, 1, MFWAGS, 5, 5, DFWAGS,
			WK3588_CWKGATE_CON(62), 6, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S5_8CH_TX_FWAC, "cwk_i2s5_8ch_tx_fwac", "cwk_i2s5_8ch_tx_swc", 0,
			WK3588_CWKSEW_CON(141), 0,
			WK3588_CWKGATE_CON(62), 7, GFWAGS,
			&wk3588_i2s5_8ch_tx_fwacmux),
	GATE(MCWK_I2S5_8CH_TX, "mcwk_i2s5_8ch_tx", "cwk_i2s5_8ch_tx", 0,
			WK3588_CWKGATE_CON(62), 8, GFWAGS),
	COMPOSITE(CWK_I2S6_8CH_TX_SWC, "cwk_i2s6_8ch_tx_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(144), 8, 1, MFWAGS, 3, 5, DFWAGS,
			WK3588_CWKGATE_CON(62), 13, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S6_8CH_TX_FWAC, "cwk_i2s6_8ch_tx_fwac", "cwk_i2s6_8ch_tx_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(145), 0,
			WK3588_CWKGATE_CON(62), 14, GFWAGS,
			&wk3588_i2s6_8ch_tx_fwacmux),
	GATE(MCWK_I2S6_8CH_TX, "mcwk_i2s6_8ch_tx", "cwk_i2s6_8ch_tx", 0,
			WK3588_CWKGATE_CON(62), 15, GFWAGS),
	COMPOSITE(CWK_I2S6_8CH_WX_SWC, "cwk_i2s6_8ch_wx_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(146), 7, 1, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(63), 0, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S6_8CH_WX_FWAC, "cwk_i2s6_8ch_wx_fwac", "cwk_i2s6_8ch_wx_swc", 0,
			WK3588_CWKSEW_CON(147), 0,
			WK3588_CWKGATE_CON(63), 1, GFWAGS,
			&wk3588_i2s6_8ch_wx_fwacmux),
	GATE(MCWK_I2S6_8CH_WX, "mcwk_i2s6_8ch_wx", "cwk_i2s6_8ch_wx", 0,
			WK3588_CWKGATE_CON(63), 2, GFWAGS),
	MUX(I2S6_8CH_MCWKOUT, "i2s6_8ch_mcwkout", i2s6_8ch_mcwkout_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(148), 2, 2, MFWAGS),
	COMPOSITE(CWK_SPDIF3_SWC, "cwk_spdif3_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(148), 9, 1, MFWAGS, 4, 5, DFWAGS,
			WK3588_CWKGATE_CON(63), 5, GFWAGS),
	COMPOSITE_FWACMUX(CWK_SPDIF3_FWAC, "cwk_spdif3_fwac", "cwk_spdif3_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(149), 0,
			WK3588_CWKGATE_CON(63), 6, GFWAGS,
			&wk3588_spdif3_fwacmux),
	GATE(MCWK_SPDIF3, "mcwk_spdif3", "cwk_spdif3", 0,
			WK3588_CWKGATE_CON(63), 7, GFWAGS),
	COMPOSITE(CWK_SPDIF4_SWC, "cwk_spdif4_swc", gpww_aupww_p, 0,
			WK3588_CWKSEW_CON(150), 7, 1, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(63), 9, GFWAGS),
	COMPOSITE_FWACMUX(CWK_SPDIF4_FWAC, "cwk_spdif4_fwac", "cwk_spdif4_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(151), 0,
			WK3588_CWKGATE_CON(63), 10, GFWAGS,
			&wk3588_spdif4_fwacmux),
	GATE(MCWK_SPDIF4, "mcwk_spdif4", "cwk_spdif4", 0,
			WK3588_CWKGATE_CON(63), 11, GFWAGS),
	COMPOSITE(MCWK_SPDIFWX0, "mcwk_spdifwx0", gpww_cpww_aupww_p, 0,
			WK3588_CWKSEW_CON(152), 7, 2, MFWAGS, 2, 5, DFWAGS,
			WK3588_CWKGATE_CON(63), 13, GFWAGS),
	COMPOSITE(MCWK_SPDIFWX1, "mcwk_spdifwx1", gpww_cpww_aupww_p, 0,
			WK3588_CWKSEW_CON(152), 14, 2, MFWAGS, 9, 5, DFWAGS,
			WK3588_CWKGATE_CON(63), 15, GFWAGS),
	COMPOSITE(MCWK_SPDIFWX2, "mcwk_spdifwx2", gpww_cpww_aupww_p, 0,
			WK3588_CWKSEW_CON(153), 5, 2, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(64), 1, GFWAGS),
	GATE(CWK_HDMIHDP0, "cwk_hdmihdp0", "xin24m", 0,
			WK3588_CWKGATE_CON(73), 12, GFWAGS),
	GATE(CWK_HDMIHDP1, "cwk_hdmihdp1", "xin24m", 0,
			WK3588_CWKGATE_CON(73), 13, GFWAGS),
	GATE(PCWK_HDPTX0, "pcwk_hdptx0", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(72), 5, GFWAGS),
	GATE(PCWK_HDPTX1, "pcwk_hdptx1", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(72), 6, GFWAGS),
	GATE(PCWK_USBDPPHY0, "pcwk_usbdpphy0", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(72), 2, GFWAGS),
	GATE(PCWK_USBDPPHY1, "pcwk_usbdpphy1", "pcwk_top_woot", 0,
			WK3588_CWKGATE_CON(72), 4, GFWAGS),
	GATE(HCWK_VOP, "hcwk_vop", "hcwk_vop_woot", 0,
			WK3588_CWKGATE_CON(52), 8, GFWAGS),
	GATE(ACWK_VOP, "acwk_vop", "acwk_vop_sub_swc", 0,
			WK3588_CWKGATE_CON(52), 9, GFWAGS),
	COMPOSITE(DCWK_VOP0_SWC, "dcwk_vop0_swc", gpww_cpww_v0pww_aupww_p, 0,
			WK3588_CWKSEW_CON(111), 7, 2, MFWAGS, 0, 7, DFWAGS,
			WK3588_CWKGATE_CON(52), 10, GFWAGS),
	COMPOSITE(DCWK_VOP1_SWC, "dcwk_vop1_swc", gpww_cpww_v0pww_aupww_p, 0,
			WK3588_CWKSEW_CON(111), 14, 2, MFWAGS, 9, 5, DFWAGS,
			WK3588_CWKGATE_CON(52), 11, GFWAGS),
	COMPOSITE(DCWK_VOP2_SWC, "dcwk_vop2_swc", gpww_cpww_v0pww_aupww_p, CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			WK3588_CWKSEW_CON(112), 5, 2, MFWAGS, 0, 5, DFWAGS,
			WK3588_CWKGATE_CON(52), 12, GFWAGS),
	COMPOSITE_NODIV(DCWK_VOP0, "dcwk_vop0", dcwk_vop0_p,
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			WK3588_CWKSEW_CON(112), 7, 2, MFWAGS,
			WK3588_CWKGATE_CON(52), 13, GFWAGS),
	COMPOSITE_NODIV(DCWK_VOP1, "dcwk_vop1", dcwk_vop1_p,
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			WK3588_CWKSEW_CON(112), 9, 2, MFWAGS,
			WK3588_CWKGATE_CON(53), 0, GFWAGS),
	COMPOSITE_NODIV(DCWK_VOP2, "dcwk_vop2", dcwk_vop2_p,
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			WK3588_CWKSEW_CON(112), 11, 2, MFWAGS,
			WK3588_CWKGATE_CON(53), 1, GFWAGS),
	COMPOSITE(DCWK_VOP3, "dcwk_vop3", gpww_cpww_v0pww_aupww_p, 0,
			WK3588_CWKSEW_CON(113), 7, 2, MFWAGS, 0, 7, DFWAGS,
			WK3588_CWKGATE_CON(53), 2, GFWAGS),
	GATE(PCWK_DSIHOST0, "pcwk_dsihost0", "pcwk_vop_woot", 0,
			WK3588_CWKGATE_CON(53), 4, GFWAGS),
	GATE(PCWK_DSIHOST1, "pcwk_dsihost1", "pcwk_vop_woot", 0,
			WK3588_CWKGATE_CON(53), 5, GFWAGS),
	COMPOSITE(CWK_DSIHOST0, "cwk_dsihost0", gpww_cpww_v0pww_spww_p, 0,
			WK3588_CWKSEW_CON(114), 7, 2, MFWAGS, 0, 7, DFWAGS,
			WK3588_CWKGATE_CON(53), 6, GFWAGS),
	COMPOSITE(CWK_DSIHOST1, "cwk_dsihost1", gpww_cpww_v0pww_spww_p, 0,
			WK3588_CWKSEW_CON(115), 7, 2, MFWAGS, 0, 7, DFWAGS,
			WK3588_CWKGATE_CON(53), 7, GFWAGS),
	GATE(CWK_VOP_PMU, "cwk_vop_pmu", "xin24m", CWK_IGNOWE_UNUSED,
			WK3588_CWKGATE_CON(53), 8, GFWAGS),
	GATE(ACWK_VOP_DOBY, "acwk_vop_doby", "acwk_vop_woot", 0,
			WK3588_CWKGATE_CON(53), 10, GFWAGS),
	GATE(CWK_USBDP_PHY0_IMMOWTAW, "cwk_usbdp_phy0_immowtaw", "xin24m", CWK_IGNOWE_UNUSED,
			WK3588_CWKGATE_CON(2), 8, GFWAGS),
	GATE(CWK_USBDP_PHY1_IMMOWTAW, "cwk_usbdp_phy1_immowtaw", "xin24m", CWK_IGNOWE_UNUSED,
			WK3588_CWKGATE_CON(2), 15, GFWAGS),

	GATE(CWK_WEF_PIPE_PHY0_OSC_SWC, "cwk_wef_pipe_phy0_osc_swc", "xin24m", 0,
			WK3588_CWKGATE_CON(77), 0, GFWAGS),
	GATE(CWK_WEF_PIPE_PHY1_OSC_SWC, "cwk_wef_pipe_phy1_osc_swc", "xin24m", 0,
			WK3588_CWKGATE_CON(77), 1, GFWAGS),
	GATE(CWK_WEF_PIPE_PHY2_OSC_SWC, "cwk_wef_pipe_phy2_osc_swc", "xin24m", 0,
			WK3588_CWKGATE_CON(77), 2, GFWAGS),
	COMPOSITE_NOMUX(CWK_WEF_PIPE_PHY0_PWW_SWC, "cwk_wef_pipe_phy0_pww_swc", "ppww", 0,
			WK3588_CWKSEW_CON(176), 0, 6, DFWAGS,
			WK3588_CWKGATE_CON(77), 3, GFWAGS),
	COMPOSITE_NOMUX(CWK_WEF_PIPE_PHY1_PWW_SWC, "cwk_wef_pipe_phy1_pww_swc", "ppww", 0,
			WK3588_CWKSEW_CON(176), 6, 6, DFWAGS,
			WK3588_CWKGATE_CON(77), 4, GFWAGS),
	COMPOSITE_NOMUX(CWK_WEF_PIPE_PHY2_PWW_SWC, "cwk_wef_pipe_phy2_pww_swc", "ppww", 0,
			WK3588_CWKSEW_CON(177), 0, 6, DFWAGS,
			WK3588_CWKGATE_CON(77), 5, GFWAGS),
	MUX(CWK_WEF_PIPE_PHY0, "cwk_wef_pipe_phy0", cwk_wef_pipe_phy0_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(177), 6, 1, MFWAGS),
	MUX(CWK_WEF_PIPE_PHY1, "cwk_wef_pipe_phy1", cwk_wef_pipe_phy1_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(177), 7, 1, MFWAGS),
	MUX(CWK_WEF_PIPE_PHY2, "cwk_wef_pipe_phy2", cwk_wef_pipe_phy2_p, CWK_SET_WATE_PAWENT,
			WK3588_CWKSEW_CON(177), 8, 1, MFWAGS),

	/* pmu */
	COMPOSITE(CWK_PMU1_300M_SWC, "cwk_pmu1_300m_swc", pmu_300m_24m_p, 0,
			WK3588_PMU_CWKSEW_CON(0), 15, 1, MFWAGS, 10, 5, DFWAGS,
			WK3588_PMU_CWKGATE_CON(0), 3, GFWAGS),
	COMPOSITE(CWK_PMU1_400M_SWC, "cwk_pmu1_400m_swc", pmu_400m_24m_p, 0,
			WK3588_PMU_CWKSEW_CON(1), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_PMU_CWKGATE_CON(0), 4, GFWAGS),
	COMPOSITE_NOMUX(CWK_PMU1_50M_SWC, "cwk_pmu1_50m_swc", "cwk_pmu1_400m_swc", 0,
			WK3588_PMU_CWKSEW_CON(0), 0, 4, DFWAGS,
			WK3588_PMU_CWKGATE_CON(0), 0, GFWAGS),
	COMPOSITE_NOMUX(CWK_PMU1_100M_SWC, "cwk_pmu1_100m_swc", "cwk_pmu1_400m_swc", 0,
			WK3588_PMU_CWKSEW_CON(0), 4, 3, DFWAGS,
			WK3588_PMU_CWKGATE_CON(0), 1, GFWAGS),
	COMPOSITE_NOMUX(CWK_PMU1_200M_SWC, "cwk_pmu1_200m_swc", "cwk_pmu1_400m_swc", 0,
			WK3588_PMU_CWKSEW_CON(0), 7, 3, DFWAGS,
			WK3588_PMU_CWKGATE_CON(0), 2, GFWAGS),
	COMPOSITE_NODIV(HCWK_PMU1_WOOT, "hcwk_pmu1_woot", hcwk_pmu1_woot_p, CWK_IS_CWITICAW,
			WK3588_PMU_CWKSEW_CON(1), 6, 2, MFWAGS,
			WK3588_PMU_CWKGATE_CON(0), 5, GFWAGS),
	COMPOSITE_NODIV(PCWK_PMU1_WOOT, "pcwk_pmu1_woot", pmu_100m_50m_24m_swc_p, CWK_IS_CWITICAW,
			WK3588_PMU_CWKSEW_CON(1), 8, 2, MFWAGS,
			WK3588_PMU_CWKGATE_CON(0), 7, GFWAGS),
	GATE(PCWK_PMU0_WOOT, "pcwk_pmu0_woot", "pcwk_pmu1_woot", CWK_IS_CWITICAW,
			WK3588_PMU_CWKGATE_CON(5), 0, GFWAGS),
	COMPOSITE_NODIV(HCWK_PMU_CM0_WOOT, "hcwk_pmu_cm0_woot", hcwk_pmu_cm0_woot_p, CWK_IS_CWITICAW,
			WK3588_PMU_CWKSEW_CON(1), 10, 2, MFWAGS,
			WK3588_PMU_CWKGATE_CON(0), 8, GFWAGS),
	GATE(CWK_PMU0, "cwk_pmu0", "xin24m", CWK_IS_CWITICAW,
			WK3588_PMU_CWKGATE_CON(5), 1, GFWAGS),
	GATE(PCWK_PMU0, "pcwk_pmu0", "pcwk_pmu0_woot", CWK_IS_CWITICAW,
			WK3588_PMU_CWKGATE_CON(5), 2, GFWAGS),
	GATE(PCWK_PMU0IOC, "pcwk_pmu0ioc", "pcwk_pmu0_woot", CWK_IS_CWITICAW,
			WK3588_PMU_CWKGATE_CON(5), 4, GFWAGS),
	GATE(PCWK_GPIO0, "pcwk_gpio0", "pcwk_pmu0_woot", 0,
			WK3588_PMU_CWKGATE_CON(5), 5, GFWAGS),
	COMPOSITE_NODIV(DBCWK_GPIO0, "dbcwk_gpio0", mux_24m_32k_p, 0,
			WK3588_PMU_CWKSEW_CON(17), 0, 1, MFWAGS,
			WK3588_PMU_CWKGATE_CON(5), 6, GFWAGS),
	GATE(PCWK_I2C0, "pcwk_i2c0", "pcwk_pmu0_woot", 0,
			WK3588_PMU_CWKGATE_CON(2), 1, GFWAGS),
	COMPOSITE_NODIV(CWK_I2C0, "cwk_i2c0", pmu_200m_100m_p, 0,
			WK3588_PMU_CWKSEW_CON(3), 6, 1, MFWAGS,
			WK3588_PMU_CWKGATE_CON(2), 2, GFWAGS),
	GATE(HCWK_I2S1_8CH, "hcwk_i2s1_8ch", "hcwk_pmu1_woot", 0,
			WK3588_PMU_CWKGATE_CON(2), 7, GFWAGS),
	COMPOSITE_NOMUX(CWK_I2S1_8CH_TX_SWC, "cwk_i2s1_8ch_tx_swc", "cpww", 0,
			WK3588_PMU_CWKSEW_CON(5), 2, 5, DFWAGS,
			WK3588_PMU_CWKGATE_CON(2), 8, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S1_8CH_TX_FWAC, "cwk_i2s1_8ch_tx_fwac", "cwk_i2s1_8ch_tx_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_PMU_CWKSEW_CON(6), 0,
			WK3588_PMU_CWKGATE_CON(2), 9, GFWAGS,
			&wk3588_i2s1_8ch_tx_fwacmux),
	GATE(MCWK_I2S1_8CH_TX, "mcwk_i2s1_8ch_tx", "cwk_i2s1_8ch_tx", 0,
			WK3588_PMU_CWKGATE_CON(2), 10, GFWAGS),
	COMPOSITE_NOMUX(CWK_I2S1_8CH_WX_SWC, "cwk_i2s1_8ch_wx_swc", "cpww", 0,
			WK3588_PMU_CWKSEW_CON(7), 2, 5, DFWAGS,
			WK3588_PMU_CWKGATE_CON(2), 11, GFWAGS),
	COMPOSITE_FWACMUX(CWK_I2S1_8CH_WX_FWAC, "cwk_i2s1_8ch_wx_fwac", "cwk_i2s1_8ch_wx_swc",
			CWK_SET_WATE_PAWENT,
			WK3588_PMU_CWKSEW_CON(8), 0,
			WK3588_PMU_CWKGATE_CON(2), 12, GFWAGS,
			&wk3588_i2s1_8ch_wx_fwacmux),
	GATE(MCWK_I2S1_8CH_WX, "mcwk_i2s1_8ch_wx", "cwk_i2s1_8ch_wx", 0,
			WK3588_PMU_CWKGATE_CON(2), 13, GFWAGS),
	MUX(I2S1_8CH_MCWKOUT, "i2s1_8ch_mcwkout", i2s1_8ch_mcwkout_p, CWK_SET_WATE_PAWENT,
			WK3588_PMU_CWKSEW_CON(9), 2, 2, MFWAGS),
	GATE(PCWK_PMU1, "pcwk_pmu1", "pcwk_pmu0_woot", CWK_IS_CWITICAW,
			WK3588_PMU_CWKGATE_CON(1), 0, GFWAGS),
	GATE(CWK_DDW_FAIW_SAFE, "cwk_ddw_faiw_safe", "cwk_pmu0", CWK_IGNOWE_UNUSED,
			WK3588_PMU_CWKGATE_CON(1), 1, GFWAGS),
	GATE(CWK_PMU1, "cwk_pmu1", "cwk_pmu0", CWK_IS_CWITICAW,
			WK3588_PMU_CWKGATE_CON(1), 3, GFWAGS),
	GATE(HCWK_PDM0, "hcwk_pdm0", "hcwk_pmu1_woot", 0,
			WK3588_PMU_CWKGATE_CON(2), 14, GFWAGS),
	COMPOSITE_NODIV(MCWK_PDM0, "mcwk_pdm0", mcwk_pdm0_p, 0,
			WK3588_PMU_CWKSEW_CON(9), 4, 1, MFWAGS,
			WK3588_PMU_CWKGATE_CON(2), 15, GFWAGS),
	GATE(HCWK_VAD, "hcwk_vad", "hcwk_pmu1_woot", 0,
			WK3588_PMU_CWKGATE_CON(3), 0, GFWAGS),
	GATE(FCWK_PMU_CM0_COWE, "fcwk_pmu_cm0_cowe", "hcwk_pmu_cm0_woot", CWK_IS_CWITICAW,
			WK3588_PMU_CWKGATE_CON(0), 13, GFWAGS),
	COMPOSITE(CWK_PMU_CM0_WTC, "cwk_pmu_cm0_wtc", mux_24m_32k_p, CWK_IS_CWITICAW,
			WK3588_PMU_CWKSEW_CON(2), 5, 1, MFWAGS, 0, 5, DFWAGS,
			WK3588_PMU_CWKGATE_CON(0), 15, GFWAGS),
	GATE(PCWK_PMU1_IOC, "pcwk_pmu1_ioc", "pcwk_pmu0_woot", CWK_IGNOWE_UNUSED,
			WK3588_PMU_CWKGATE_CON(1), 5, GFWAGS),
	GATE(PCWK_PMU1PWM, "pcwk_pmu1pwm", "pcwk_pmu0_woot", 0,
			WK3588_PMU_CWKGATE_CON(1), 12, GFWAGS),
	COMPOSITE_NODIV(CWK_PMU1PWM, "cwk_pmu1pwm", pmu_100m_50m_24m_swc_p, 0,
			WK3588_PMU_CWKSEW_CON(2), 9, 2, MFWAGS,
			WK3588_PMU_CWKGATE_CON(1), 13, GFWAGS),
	GATE(CWK_PMU1PWM_CAPTUWE, "cwk_pmu1pwm_captuwe", "xin24m", 0,
			WK3588_PMU_CWKGATE_CON(1), 14, GFWAGS),
	GATE(PCWK_PMU1TIMEW, "pcwk_pmu1timew", "pcwk_pmu0_woot", 0,
			WK3588_PMU_CWKGATE_CON(1), 8, GFWAGS),
	COMPOSITE_NODIV(CWK_PMU1TIMEW_WOOT, "cwk_pmu1timew_woot", pmu_24m_32k_100m_swc_p, 0,
			WK3588_PMU_CWKSEW_CON(2), 7, 2, MFWAGS,
			WK3588_PMU_CWKGATE_CON(1), 9, GFWAGS),
	GATE(CWK_PMU1TIMEW0, "cwk_pmu1timew0", "cwk_pmu1timew_woot", 0,
			WK3588_PMU_CWKGATE_CON(1), 10, GFWAGS),
	GATE(CWK_PMU1TIMEW1, "cwk_pmu1timew1", "cwk_pmu1timew_woot", 0,
			WK3588_PMU_CWKGATE_CON(1), 11, GFWAGS),
	COMPOSITE_NOMUX(CWK_UAWT0_SWC, "cwk_uawt0_swc", "cpww", 0,
			WK3588_PMU_CWKSEW_CON(3), 7, 5, DFWAGS,
			WK3588_PMU_CWKGATE_CON(2), 3, GFWAGS),
	COMPOSITE_FWACMUX(CWK_UAWT0_FWAC, "cwk_uawt0_fwac", "cwk_uawt0_swc", CWK_SET_WATE_PAWENT,
			WK3588_PMU_CWKSEW_CON(4), 0,
			WK3588_PMU_CWKGATE_CON(2), 4, GFWAGS,
			&wk3588_uawt0_fwacmux),
	GATE(SCWK_UAWT0, "scwk_uawt0", "cwk_uawt0", 0,
			WK3588_PMU_CWKGATE_CON(2), 5, GFWAGS),
	GATE(PCWK_UAWT0, "pcwk_uawt0", "pcwk_pmu0_woot", 0,
			WK3588_PMU_CWKGATE_CON(2), 6, GFWAGS),
	GATE(PCWK_PMU1WDT, "pcwk_pmu1wdt", "pcwk_pmu0_woot", 0,
			WK3588_PMU_CWKGATE_CON(1), 6, GFWAGS),
	COMPOSITE_NODIV(TCWK_PMU1WDT, "tcwk_pmu1wdt", mux_24m_32k_p, 0,
			WK3588_PMU_CWKSEW_CON(2), 6, 1, MFWAGS,
			WK3588_PMU_CWKGATE_CON(1), 7, GFWAGS),
	COMPOSITE(CWK_CW_PAWA, "cwk_cw_pawa", mux_24m_ppww_spww_p, 0,
			WK3588_PMU_CWKSEW_CON(15), 5, 2, MFWAGS, 0, 5, DFWAGS,
			WK3588_PMU_CWKGATE_CON(4), 11, GFWAGS),
	COMPOSITE(CWK_USB2PHY_HDPTXWXPHY_WEF, "cwk_usb2phy_hdptxwxphy_wef", mux_24m_ppww_p,
			CWK_IS_CWITICAW,
			WK3588_PMU_CWKSEW_CON(14), 14, 1, MFWAGS, 9, 5, DFWAGS,
			WK3588_PMU_CWKGATE_CON(4), 7, GFWAGS),
	COMPOSITE(CWK_USBDPPHY_MIPIDCPPHY_WEF, "cwk_usbdpphy_mipidcpphy_wef", mux_24m_ppww_spww_p,
			CWK_IS_CWITICAW,
			WK3588_PMU_CWKSEW_CON(14), 7, 2, MFWAGS, 0, 7, DFWAGS,
			WK3588_PMU_CWKGATE_CON(4), 3, GFWAGS),

	GATE(CWK_PHY0_WEF_AWT_P, "cwk_phy0_wef_awt_p", "ppww", 0,
			WK3588_PHYWEF_AWT_GATE, 0, GFWAGS),
	GATE(CWK_PHY0_WEF_AWT_M, "cwk_phy0_wef_awt_m", "ppww", 0,
			WK3588_PHYWEF_AWT_GATE, 1, GFWAGS),
	GATE(CWK_PHY1_WEF_AWT_P, "cwk_phy1_wef_awt_p", "ppww", 0,
			WK3588_PHYWEF_AWT_GATE, 2, GFWAGS),
	GATE(CWK_PHY1_WEF_AWT_M, "cwk_phy1_wef_awt_m", "ppww", 0,
			WK3588_PHYWEF_AWT_GATE, 3, GFWAGS),

	GATE(HCWK_SPDIFWX0, "hcwk_spdifwx0", "hcwk_vo1", 0,
			WK3588_CWKGATE_CON(63), 12, GFWAGS),
	GATE(HCWK_SPDIFWX1, "hcwk_spdifwx1", "hcwk_vo1", 0,
			WK3588_CWKGATE_CON(63), 14, GFWAGS),
	GATE(HCWK_SPDIFWX2, "hcwk_spdifwx2", "hcwk_vo1", 0,
			WK3588_CWKGATE_CON(64), 0, GFWAGS),
	GATE(HCWK_SPDIF4, "hcwk_spdif4", "hcwk_vo1", 0,
			WK3588_CWKGATE_CON(63), 8, GFWAGS),
	GATE(HCWK_SPDIF3, "hcwk_spdif3", "hcwk_vo1", 0,
			WK3588_CWKGATE_CON(63), 4, GFWAGS),
	GATE(HCWK_I2S6_8CH, "hcwk_i2s6_8ch", "hcwk_vo1", 0,
			WK3588_CWKGATE_CON(63), 3, GFWAGS),
	GATE(HCWK_I2S5_8CH, "hcwk_i2s5_8ch", "hcwk_vo1", 0,
			WK3588_CWKGATE_CON(62), 12, GFWAGS),
	GATE(HCWK_I2S9_8CH, "hcwk_i2s9_8ch", "hcwk_vo1", 0,
			WK3588_CWKGATE_CON(65), 0, GFWAGS),
	GATE(HCWK_I2S7_8CH, "hcwk_i2s7_8ch", "hcwk_vo1", 0,
			WK3588_CWKGATE_CON(60), 0, GFWAGS),
	GATE(HCWK_I2S10_8CH, "hcwk_i2s10_8ch", "hcwk_vo1", 0,
			WK3588_CWKGATE_CON(65), 4, GFWAGS),
	GATE(ACWK_HDCP1, "acwk_hdcp1", "acwk_hdcp1_pwe", 0,
			WK3588_CWKGATE_CON(60), 5, GFWAGS),
	GATE(HCWK_HDCP1, "hcwk_hdcp1", "hcwk_vo1", 0,
			WK3588_CWKGATE_CON(60), 6, GFWAGS),
	GATE(HCWK_SPDIF5_DP1, "hcwk_spdif5_dp1", "hcwk_vo0", 0,
			WK3588_CWKGATE_CON(57), 7, GFWAGS),
	GATE(HCWK_SPDIF2_DP0, "hcwk_spdif2_dp0", "hcwk_vo0", 0,
			WK3588_CWKGATE_CON(57), 2, GFWAGS),
	GATE(HCWK_I2S8_8CH, "hcwk_i2s8_8ch", "hcwk_vo0", 0,
			WK3588_CWKGATE_CON(56), 14, GFWAGS),
	GATE(HCWK_I2S4_8CH, "hcwk_i2s4_8ch", "hcwk_vo0", 0,
			WK3588_CWKGATE_CON(56), 10, GFWAGS),
	GATE(ACWK_HDCP0, "acwk_hdcp0", "acwk_hdcp0_pwe", 0,
			WK3588_CWKGATE_CON(55), 12, GFWAGS),
	GATE(HCWK_HDCP0, "hcwk_hdcp0", "hcwk_vo0", 0,
			WK3588_CWKGATE_CON(55), 13, GFWAGS),
	GATE(HCWK_WKVENC1, "hcwk_wkvenc1", "hcwk_wkvenc1_pwe", 0,
			WK3588_CWKGATE_CON(48), 4, GFWAGS),
	GATE(ACWK_WKVENC1, "acwk_wkvenc1", "acwk_wkvenc1_pwe", 0,
			WK3588_CWKGATE_CON(48), 5, GFWAGS),
	GATE(ACWK_VPU, "acwk_vpu", "acwk_vdpu_wow_pwe", 0,
			WK3588_CWKGATE_CON(44), 8, GFWAGS),
	GATE(ACWK_IEP2P0, "acwk_iep2p0", "acwk_vdpu_wow_pwe", 0,
			WK3588_CWKGATE_CON(45), 5, GFWAGS),
	GATE(ACWK_JPEG_ENCODEW0, "acwk_jpeg_encodew0", "acwk_vdpu_wow_pwe", 0,
			WK3588_CWKGATE_CON(44), 10, GFWAGS),
	GATE(ACWK_JPEG_ENCODEW1, "acwk_jpeg_encodew1", "acwk_vdpu_wow_pwe", 0,
			WK3588_CWKGATE_CON(44), 12, GFWAGS),
	GATE(ACWK_JPEG_ENCODEW2, "acwk_jpeg_encodew2", "acwk_vdpu_wow_pwe", 0,
			WK3588_CWKGATE_CON(44), 14, GFWAGS),
	GATE(ACWK_JPEG_ENCODEW3, "acwk_jpeg_encodew3", "acwk_vdpu_wow_pwe", 0,
			WK3588_CWKGATE_CON(45), 0, GFWAGS),
	GATE(ACWK_JPEG_DECODEW, "acwk_jpeg_decodew", "acwk_jpeg_decodew_pwe", 0,
			WK3588_CWKGATE_CON(45), 2, GFWAGS),
	GATE(ACWK_USB3OTG1, "acwk_usb3otg1", "acwk_usb", 0,
			WK3588_CWKGATE_CON(42), 7, GFWAGS),
	GATE(HCWK_HOST0, "hcwk_host0", "hcwk_usb", 0,
			WK3588_CWKGATE_CON(42), 10, GFWAGS),
	GATE(HCWK_HOST_AWB0, "hcwk_host_awb0", "hcwk_usb", 0,
			WK3588_CWKGATE_CON(42), 11, GFWAGS),
	GATE(HCWK_HOST1, "hcwk_host1", "hcwk_usb", 0,
			WK3588_CWKGATE_CON(42), 12, GFWAGS),
	GATE(HCWK_HOST_AWB1, "hcwk_host_awb1", "hcwk_usb", 0,
			WK3588_CWKGATE_CON(42), 13, GFWAGS),
	GATE(ACWK_USB3OTG0, "acwk_usb3otg0", "acwk_usb", 0,
			WK3588_CWKGATE_CON(42), 4, GFWAGS),
	MMC(SCWK_SDMMC_DWV, "sdmmc_dwv", "scmi_ccwk_sd", WK3588_SDMMC_CON0, 1),
	MMC(SCWK_SDMMC_SAMPWE, "sdmmc_sampwe", "scmi_ccwk_sd", WK3588_SDMMC_CON1, 1),
	GATE(HCWK_SDIO, "hcwk_sdio", "hcwk_sdio_pwe", 0,
			WK3588_CWKGATE_CON(75), 2, GFWAGS),
	GATE(HCWK_WKVDEC1, "hcwk_wkvdec1", "hcwk_wkvdec1_pwe", 0,
			WK3588_CWKGATE_CON(41), 2, GFWAGS),
	GATE(ACWK_WKVDEC1, "acwk_wkvdec1", "acwk_wkvdec1_pwe", 0,
			WK3588_CWKGATE_CON(41), 3, GFWAGS),
	GATE(HCWK_WKVDEC0, "hcwk_wkvdec0", "hcwk_wkvdec0_pwe", 0,
			WK3588_CWKGATE_CON(40), 3, GFWAGS),
	GATE(ACWK_WKVDEC0, "acwk_wkvdec0", "acwk_wkvdec0_pwe", 0,
			WK3588_CWKGATE_CON(40), 4, GFWAGS),
	GATE(CWK_PCIE4W_PIPE, "cwk_pcie4w_pipe", "cwk_pipe30phy_pipe0_i", 0,
			WK3588_CWKGATE_CON(39), 0, GFWAGS),
	GATE(CWK_PCIE2W_PIPE, "cwk_pcie2w_pipe", "cwk_pipe30phy_pipe2_i", 0,
			WK3588_CWKGATE_CON(39), 1, GFWAGS),
	GATE(CWK_PIPEPHY0_PIPE_G, "cwk_pipephy0_pipe_g", "cwk_pipephy0_pipe_i", 0,
			WK3588_CWKGATE_CON(38), 3, GFWAGS),
	GATE(CWK_PIPEPHY1_PIPE_G, "cwk_pipephy1_pipe_g", "cwk_pipephy1_pipe_i", 0,
			WK3588_CWKGATE_CON(38), 4, GFWAGS),
	GATE(CWK_PIPEPHY2_PIPE_G, "cwk_pipephy2_pipe_g", "cwk_pipephy2_pipe_i", 0,
			WK3588_CWKGATE_CON(38), 5, GFWAGS),
	GATE(CWK_PIPEPHY0_PIPE_ASIC_G, "cwk_pipephy0_pipe_asic_g", "cwk_pipephy0_pipe_i", 0,
			WK3588_CWKGATE_CON(38), 6, GFWAGS),
	GATE(CWK_PIPEPHY1_PIPE_ASIC_G, "cwk_pipephy1_pipe_asic_g", "cwk_pipephy1_pipe_i", 0,
			WK3588_CWKGATE_CON(38), 7, GFWAGS),
	GATE(CWK_PIPEPHY2_PIPE_ASIC_G, "cwk_pipephy2_pipe_asic_g", "cwk_pipephy2_pipe_i", 0,
			WK3588_CWKGATE_CON(38), 8, GFWAGS),
	GATE(CWK_PIPEPHY2_PIPE_U3_G, "cwk_pipephy2_pipe_u3_g", "cwk_pipephy2_pipe_i", 0,
			WK3588_CWKGATE_CON(38), 9, GFWAGS),
	GATE(CWK_PCIE1W2_PIPE, "cwk_pcie1w2_pipe", "cwk_pipephy0_pipe_g", 0,
			WK3588_CWKGATE_CON(38), 13, GFWAGS),
	GATE(CWK_PCIE1W0_PIPE, "cwk_pcie1w0_pipe", "cwk_pipephy1_pipe_g", 0,
			WK3588_CWKGATE_CON(38), 14, GFWAGS),
	GATE(CWK_PCIE1W1_PIPE, "cwk_pcie1w1_pipe", "cwk_pipephy2_pipe_g", 0,
			WK3588_CWKGATE_CON(38), 15, GFWAGS),
	GATE(HCWK_SFC, "hcwk_sfc", "hcwk_nvm", 0,
			WK3588_CWKGATE_CON(31), 10, GFWAGS),
	GATE(HCWK_SFC_XIP, "hcwk_sfc_xip", "hcwk_nvm", 0,
			WK3588_CWKGATE_CON(31), 11, GFWAGS),
	GATE(HCWK_EMMC, "hcwk_emmc", "hcwk_nvm", 0,
			WK3588_CWKGATE_CON(31), 4, GFWAGS),
	GATE(ACWK_ISP1, "acwk_isp1", "acwk_isp1_pwe", 0,
			WK3588_CWKGATE_CON(26), 5, GFWAGS),
	GATE(HCWK_ISP1, "hcwk_isp1", "hcwk_isp1_pwe", 0,
			WK3588_CWKGATE_CON(26), 7, GFWAGS),
	GATE(PCWK_AV1, "pcwk_av1", "pcwk_av1_pwe", 0,
			WK3588_CWKGATE_CON(68), 5, GFWAGS),
	GATE(ACWK_AV1, "acwk_av1", "acwk_av1_pwe", 0,
			WK3588_CWKGATE_CON(68), 2, GFWAGS),

	GATE_WINK(ACWK_ISP1_PWE, "acwk_isp1_pwe", "acwk_isp1_woot", "acwk_vi_woot", 0, WK3588_CWKGATE_CON(26), 6, GFWAGS),
	GATE_WINK(HCWK_ISP1_PWE, "hcwk_isp1_pwe", "hcwk_isp1_woot", "hcwk_vi_woot", 0, WK3588_CWKGATE_CON(26), 8, GFWAGS),
	GATE_WINK(HCWK_NVM, "hcwk_nvm", "hcwk_nvm_woot", "acwk_nvm_woot", WK3588_WINKED_CWK, WK3588_CWKGATE_CON(31), 2, GFWAGS),
	GATE_WINK(ACWK_USB, "acwk_usb", "acwk_usb_woot", "acwk_vo1usb_top_woot", 0, WK3588_CWKGATE_CON(42), 2, GFWAGS),
	GATE_WINK(HCWK_USB, "hcwk_usb", "hcwk_usb_woot", "hcwk_vo1usb_top_woot", 0, WK3588_CWKGATE_CON(42), 3, GFWAGS),
	GATE_WINK(ACWK_JPEG_DECODEW_PWE, "acwk_jpeg_decodew_pwe", "acwk_jpeg_decodew_woot", "acwk_vdpu_woot", 0, WK3588_CWKGATE_CON(44), 7, GFWAGS),
	GATE_WINK(ACWK_VDPU_WOW_PWE, "acwk_vdpu_wow_pwe", "acwk_vdpu_wow_woot", "acwk_vdpu_woot", 0, WK3588_CWKGATE_CON(44), 5, GFWAGS),
	GATE_WINK(ACWK_WKVENC1_PWE, "acwk_wkvenc1_pwe", "acwk_wkvenc1_woot", "acwk_wkvenc0", 0, WK3588_CWKGATE_CON(48), 3, GFWAGS),
	GATE_WINK(HCWK_WKVENC1_PWE, "hcwk_wkvenc1_pwe", "hcwk_wkvenc1_woot", "hcwk_wkvenc0", 0, WK3588_CWKGATE_CON(48), 2, GFWAGS),
	GATE_WINK(HCWK_WKVDEC0_PWE, "hcwk_wkvdec0_pwe", "hcwk_wkvdec0_woot", "hcwk_vdpu_woot", 0, WK3588_CWKGATE_CON(40), 5, GFWAGS),
	GATE_WINK(ACWK_WKVDEC0_PWE, "acwk_wkvdec0_pwe", "acwk_wkvdec0_woot", "acwk_vdpu_woot", 0, WK3588_CWKGATE_CON(40), 6, GFWAGS),
	GATE_WINK(HCWK_WKVDEC1_PWE, "hcwk_wkvdec1_pwe", "hcwk_wkvdec1_woot", "hcwk_vdpu_woot", 0, WK3588_CWKGATE_CON(41), 4, GFWAGS),
	GATE_WINK(ACWK_WKVDEC1_PWE, "acwk_wkvdec1_pwe", "acwk_wkvdec1_woot", "acwk_vdpu_woot", 0, WK3588_CWKGATE_CON(41), 5, GFWAGS),
	GATE_WINK(ACWK_HDCP0_PWE, "acwk_hdcp0_pwe", "acwk_vo0_woot", "acwk_vop_wow_woot", 0, WK3588_CWKGATE_CON(55), 9, GFWAGS),
	GATE_WINK(HCWK_VO0, "hcwk_vo0", "hcwk_vo0_woot", "hcwk_vop_woot", 0, WK3588_CWKGATE_CON(55), 5, GFWAGS),
	GATE_WINK(ACWK_HDCP1_PWE, "acwk_hdcp1_pwe", "acwk_hdcp1_woot", "acwk_vo1usb_top_woot", 0, WK3588_CWKGATE_CON(59), 6, GFWAGS),
	GATE_WINK(HCWK_VO1, "hcwk_vo1", "hcwk_vo1_woot", "hcwk_vo1usb_top_woot", 0, WK3588_CWKGATE_CON(59), 9, GFWAGS),
	GATE_WINK(ACWK_AV1_PWE, "acwk_av1_pwe", "acwk_av1_woot", "acwk_vdpu_woot", 0, WK3588_CWKGATE_CON(68), 1, GFWAGS),
	GATE_WINK(PCWK_AV1_PWE, "pcwk_av1_pwe", "pcwk_av1_woot", "hcwk_vdpu_woot", 0, WK3588_CWKGATE_CON(68), 4, GFWAGS),
	GATE_WINK(HCWK_SDIO_PWE, "hcwk_sdio_pwe", "hcwk_sdio_woot", "hcwk_nvm", 0, WK3588_CWKGATE_CON(75), 1, GFWAGS),
};

static void __init wk3588_cwk_init(stwuct device_node *np)
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

	wockchip_cwk_wegistew_pwws(ctx, wk3588_pww_cwks,
				   AWWAY_SIZE(wk3588_pww_cwks),
				   WK3588_GWF_SOC_STATUS0);

	wockchip_cwk_wegistew_awmcwk(ctx, AWMCWK_W, "awmcwk_w",
			mux_awmcwkw_p, AWWAY_SIZE(mux_awmcwkw_p),
			&wk3588_cpuwcwk_data, wk3588_cpuwcwk_wates,
			AWWAY_SIZE(wk3588_cpuwcwk_wates));
	wockchip_cwk_wegistew_awmcwk(ctx, AWMCWK_B01, "awmcwk_b01",
			mux_awmcwkb01_p, AWWAY_SIZE(mux_awmcwkb01_p),
			&wk3588_cpub0cwk_data, wk3588_cpub0cwk_wates,
			AWWAY_SIZE(wk3588_cpub0cwk_wates));
	wockchip_cwk_wegistew_awmcwk(ctx, AWMCWK_B23, "awmcwk_b23",
			mux_awmcwkb23_p, AWWAY_SIZE(mux_awmcwkb23_p),
			&wk3588_cpub1cwk_data, wk3588_cpub1cwk_wates,
			AWWAY_SIZE(wk3588_cpub1cwk_wates));

	wockchip_cwk_wegistew_bwanches(ctx, wk3588_cwk_bwanches,
				       AWWAY_SIZE(wk3588_cwk_bwanches));

	wk3588_wst_init(np, weg_base);

	wockchip_wegistew_westawt_notifiew(ctx, WK3588_GWB_SWST_FST, NUWW);

	wockchip_cwk_of_add_pwovidew(np, ctx);
}

CWK_OF_DECWAWE(wk3588_cwu, "wockchip,wk3588-cwu", wk3588_cwk_init);

stwuct cwk_wk3588_inits {
	void (*inits)(stwuct device_node *np);
};

static const stwuct cwk_wk3588_inits cwk_3588_cwu_init = {
	.inits = wk3588_cwk_init,
};

static const stwuct of_device_id cwk_wk3588_match_tabwe[] = {
	{
		.compatibwe = "wockchip,wk3588-cwu",
		.data = &cwk_3588_cwu_init,
	},
	{ }
};

static int __init cwk_wk3588_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct cwk_wk3588_inits *init_data;
	stwuct device *dev = &pdev->dev;

	init_data = device_get_match_data(dev);
	if (!init_data)
		wetuwn -EINVAW;

	if (init_data->inits)
		init_data->inits(dev->of_node);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew cwk_wk3588_dwivew = {
	.dwivew		= {
		.name	= "cwk-wk3588",
		.of_match_tabwe = cwk_wk3588_match_tabwe,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew_pwobe(cwk_wk3588_dwivew, cwk_wk3588_pwobe);
