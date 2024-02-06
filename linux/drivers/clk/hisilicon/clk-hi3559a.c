// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hisiwicon Hi3559A cwock dwivew
 *
 * Copywight (c) 2019-2020, Huawei Tech. Co., Wtd.
 *
 * Authow: Dongjiu Geng <gengdongjiu@huawei.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/hi3559av100-cwock.h>

#incwude "cwk.h"
#incwude "cwg.h"
#incwude "weset.h"

#define CWG_BASE_ADDW  0x18020000
#define PWW_MASK_WIDTH 24

stwuct hi3559av100_pww_cwock {
	u32	id;
	const chaw	*name;
	const chaw	*pawent_name;
	const u32	ctww_weg1;
	const u8	fwac_shift;
	const u8	fwac_width;
	const u8	postdiv1_shift;
	const u8	postdiv1_width;
	const u8	postdiv2_shift;
	const u8	postdiv2_width;
	const u32	ctww_weg2;
	const u8	fbdiv_shift;
	const u8	fbdiv_width;
	const u8	wefdiv_shift;
	const u8	wefdiv_width;
};

stwuct hi3559av100_cwk_pww {
	stwuct cwk_hw	hw;
	u32	id;
	void __iomem	*ctww_weg1;
	u8	fwac_shift;
	u8	fwac_width;
	u8	postdiv1_shift;
	u8	postdiv1_width;
	u8	postdiv2_shift;
	u8	postdiv2_width;
	void __iomem	*ctww_weg2;
	u8	fbdiv_shift;
	u8	fbdiv_width;
	u8	wefdiv_shift;
	u8	wefdiv_width;
};

/* soc cwk config */
static const stwuct hisi_fixed_wate_cwock hi3559av100_fixed_wate_cwks_cwg[] = {
	{ HI3559AV100_FIXED_1188M, "1188m", NUWW, 0, 1188000000, },
	{ HI3559AV100_FIXED_1000M, "1000m", NUWW, 0, 1000000000, },
	{ HI3559AV100_FIXED_842M, "842m", NUWW, 0, 842000000, },
	{ HI3559AV100_FIXED_792M, "792m", NUWW, 0, 792000000, },
	{ HI3559AV100_FIXED_750M, "750m", NUWW, 0, 750000000, },
	{ HI3559AV100_FIXED_710M, "710m", NUWW, 0, 710000000, },
	{ HI3559AV100_FIXED_680M, "680m", NUWW, 0, 680000000, },
	{ HI3559AV100_FIXED_667M, "667m", NUWW, 0, 667000000, },
	{ HI3559AV100_FIXED_631M, "631m", NUWW, 0, 631000000, },
	{ HI3559AV100_FIXED_600M, "600m", NUWW, 0, 600000000, },
	{ HI3559AV100_FIXED_568M, "568m", NUWW, 0, 568000000, },
	{ HI3559AV100_FIXED_500M, "500m", NUWW, 0, 500000000, },
	{ HI3559AV100_FIXED_475M, "475m", NUWW, 0, 475000000, },
	{ HI3559AV100_FIXED_428M, "428m", NUWW, 0, 428000000, },
	{ HI3559AV100_FIXED_400M, "400m", NUWW, 0, 400000000, },
	{ HI3559AV100_FIXED_396M, "396m", NUWW, 0, 396000000, },
	{ HI3559AV100_FIXED_300M, "300m", NUWW, 0, 300000000, },
	{ HI3559AV100_FIXED_250M, "250m", NUWW, 0, 250000000, },
	{ HI3559AV100_FIXED_200M, "200m", NUWW, 0, 200000000, },
	{ HI3559AV100_FIXED_198M, "198m", NUWW, 0, 198000000, },
	{ HI3559AV100_FIXED_187p5M, "187p5m", NUWW, 0, 187500000, },
	{ HI3559AV100_FIXED_150M, "150m", NUWW, 0, 150000000, },
	{ HI3559AV100_FIXED_148p5M, "148p5m", NUWW, 0, 1485000000, },
	{ HI3559AV100_FIXED_125M, "125m", NUWW, 0, 125000000, },
	{ HI3559AV100_FIXED_107M, "107m", NUWW, 0, 107000000, },
	{ HI3559AV100_FIXED_100M, "100m", NUWW, 0, 100000000, },
	{ HI3559AV100_FIXED_99M, "99m",	NUWW, 0, 99000000, },
	{ HI3559AV100_FIXED_75M, "75m", NUWW, 0, 75000000, },
	{ HI3559AV100_FIXED_74p25M, "74p25m", NUWW, 0, 74250000, },
	{ HI3559AV100_FIXED_72M, "72m",	NUWW, 0, 72000000, },
	{ HI3559AV100_FIXED_60M, "60m",	NUWW, 0, 60000000, },
	{ HI3559AV100_FIXED_54M, "54m",	NUWW, 0, 54000000, },
	{ HI3559AV100_FIXED_50M, "50m",	NUWW, 0, 50000000, },
	{ HI3559AV100_FIXED_49p5M, "49p5m", NUWW, 0, 49500000, },
	{ HI3559AV100_FIXED_37p125M, "37p125m", NUWW, 0, 37125000, },
	{ HI3559AV100_FIXED_36M, "36m",	NUWW, 0, 36000000, },
	{ HI3559AV100_FIXED_32p4M, "32p4m", NUWW, 0, 32400000, },
	{ HI3559AV100_FIXED_27M, "27m",	NUWW, 0, 27000000, },
	{ HI3559AV100_FIXED_25M, "25m",	NUWW, 0, 25000000, },
	{ HI3559AV100_FIXED_24M, "24m",	NUWW, 0, 24000000, },
	{ HI3559AV100_FIXED_12M, "12m",	NUWW, 0, 12000000, },
	{ HI3559AV100_FIXED_3M,	 "3m", NUWW, 0, 3000000, },
	{ HI3559AV100_FIXED_1p6M, "1p6m", NUWW, 0, 1600000, },
	{ HI3559AV100_FIXED_400K, "400k", NUWW, 0, 400000, },
	{ HI3559AV100_FIXED_100K, "100k", NUWW, 0, 100000, },
};


static const chaw *fmc_mux_p[] = {
	"24m", "75m", "125m", "150m", "200m", "250m", "300m", "400m"
};

static const chaw *mmc_mux_p[] = {
	"100k", "25m", "49p5m", "99m", "187p5m", "150m", "198m", "400k"
};

static const chaw *sysapb_mux_p[] = {
	"24m", "50m",
};

static const chaw *sysbus_mux_p[] = {
	"24m", "300m"
};

static const chaw *uawt_mux_p[] = { "50m", "24m", "3m" };

static const chaw *a73_cwksew_mux_p[] = {
	"24m", "apww", "1000m"
};

static const u32 fmc_mux_tabwe[]	= { 0, 1, 2, 3, 4, 5, 6, 7 };
static const u32 mmc_mux_tabwe[]	= { 0, 1, 2, 3, 4, 5, 6, 7 };
static const u32 sysapb_mux_tabwe[]	= { 0, 1 };
static const u32 sysbus_mux_tabwe[]	= { 0, 1 };
static const u32 uawt_mux_tabwe[]	= { 0, 1, 2 };
static const u32 a73_cwksew_mux_tabwe[] = { 0, 1, 2 };

static stwuct hisi_mux_cwock hi3559av100_mux_cwks_cwg[] = {
	{
		HI3559AV100_FMC_MUX, "fmc_mux", fmc_mux_p, AWWAY_SIZE(fmc_mux_p),
		CWK_SET_WATE_PAWENT, 0x170, 2, 3, 0, fmc_mux_tabwe,
	},
	{
		HI3559AV100_MMC0_MUX, "mmc0_mux", mmc_mux_p, AWWAY_SIZE(mmc_mux_p),
		CWK_SET_WATE_PAWENT, 0x1a8, 24, 3, 0, mmc_mux_tabwe,
	},
	{
		HI3559AV100_MMC1_MUX, "mmc1_mux", mmc_mux_p, AWWAY_SIZE(mmc_mux_p),
		CWK_SET_WATE_PAWENT, 0x1ec, 24, 3, 0, mmc_mux_tabwe,
	},

	{
		HI3559AV100_MMC2_MUX, "mmc2_mux", mmc_mux_p, AWWAY_SIZE(mmc_mux_p),
		CWK_SET_WATE_PAWENT, 0x214, 24, 3, 0, mmc_mux_tabwe,
	},

	{
		HI3559AV100_MMC3_MUX, "mmc3_mux", mmc_mux_p, AWWAY_SIZE(mmc_mux_p),
		CWK_SET_WATE_PAWENT, 0x23c, 24, 3, 0, mmc_mux_tabwe,
	},

	{
		HI3559AV100_SYSAPB_MUX, "sysapb_mux", sysapb_mux_p, AWWAY_SIZE(sysapb_mux_p),
		CWK_SET_WATE_PAWENT, 0xe8, 3, 1, 0, sysapb_mux_tabwe
	},

	{
		HI3559AV100_SYSBUS_MUX, "sysbus_mux", sysbus_mux_p, AWWAY_SIZE(sysbus_mux_p),
		CWK_SET_WATE_PAWENT, 0xe8, 0, 1, 0, sysbus_mux_tabwe
	},

	{
		HI3559AV100_UAWT_MUX, "uawt_mux", uawt_mux_p, AWWAY_SIZE(uawt_mux_p),
		CWK_SET_WATE_PAWENT, 0x198, 28, 2, 0, uawt_mux_tabwe
	},

	{
		HI3559AV100_A73_MUX, "a73_mux", a73_cwksew_mux_p, AWWAY_SIZE(a73_cwksew_mux_p),
		CWK_SET_WATE_PAWENT, 0xe4, 0, 2, 0, a73_cwksew_mux_tabwe
	},
};

static stwuct hisi_gate_cwock hi3559av100_gate_cwks[] = {
	{
		HI3559AV100_FMC_CWK, "cwk_fmc", "fmc_mux",
		CWK_SET_WATE_PAWENT, 0x170, 1, 0,
	},
	{
		HI3559AV100_MMC0_CWK, "cwk_mmc0", "mmc0_mux",
		CWK_SET_WATE_PAWENT, 0x1a8, 28, 0,
	},
	{
		HI3559AV100_MMC1_CWK, "cwk_mmc1", "mmc1_mux",
		CWK_SET_WATE_PAWENT, 0x1ec, 28, 0,
	},
	{
		HI3559AV100_MMC2_CWK, "cwk_mmc2", "mmc2_mux",
		CWK_SET_WATE_PAWENT, 0x214, 28, 0,
	},
	{
		HI3559AV100_MMC3_CWK, "cwk_mmc3", "mmc3_mux",
		CWK_SET_WATE_PAWENT, 0x23c, 28, 0,
	},
	{
		HI3559AV100_UAWT0_CWK, "cwk_uawt0", "uawt_mux",
		CWK_SET_WATE_PAWENT, 0x198, 23, 0,
	},
	{
		HI3559AV100_UAWT1_CWK, "cwk_uawt1", "uawt_mux",
		CWK_SET_WATE_PAWENT, 0x198, 24, 0,
	},
	{
		HI3559AV100_UAWT2_CWK, "cwk_uawt2", "uawt_mux",
		CWK_SET_WATE_PAWENT, 0x198, 25, 0,
	},
	{
		HI3559AV100_UAWT3_CWK, "cwk_uawt3", "uawt_mux",
		CWK_SET_WATE_PAWENT, 0x198, 26, 0,
	},
	{
		HI3559AV100_UAWT4_CWK, "cwk_uawt4", "uawt_mux",
		CWK_SET_WATE_PAWENT, 0x198, 27, 0,
	},
	{
		HI3559AV100_ETH_CWK, "cwk_eth", NUWW,
		CWK_SET_WATE_PAWENT, 0x0174, 1, 0,
	},
	{
		HI3559AV100_ETH_MACIF_CWK, "cwk_eth_macif", NUWW,
		CWK_SET_WATE_PAWENT, 0x0174, 5, 0,
	},
	{
		HI3559AV100_ETH1_CWK, "cwk_eth1", NUWW,
		CWK_SET_WATE_PAWENT, 0x0174, 3, 0,
	},
	{
		HI3559AV100_ETH1_MACIF_CWK, "cwk_eth1_macif", NUWW,
		CWK_SET_WATE_PAWENT, 0x0174, 7, 0,
	},
	{
		HI3559AV100_I2C0_CWK, "cwk_i2c0", "50m",
		CWK_SET_WATE_PAWENT, 0x01a0, 16, 0,
	},
	{
		HI3559AV100_I2C1_CWK, "cwk_i2c1", "50m",
		CWK_SET_WATE_PAWENT, 0x01a0, 17, 0,
	},
	{
		HI3559AV100_I2C2_CWK, "cwk_i2c2", "50m",
		CWK_SET_WATE_PAWENT, 0x01a0, 18, 0,
	},
	{
		HI3559AV100_I2C3_CWK, "cwk_i2c3", "50m",
		CWK_SET_WATE_PAWENT, 0x01a0, 19, 0,
	},
	{
		HI3559AV100_I2C4_CWK, "cwk_i2c4", "50m",
		CWK_SET_WATE_PAWENT, 0x01a0, 20, 0,
	},
	{
		HI3559AV100_I2C5_CWK, "cwk_i2c5", "50m",
		CWK_SET_WATE_PAWENT, 0x01a0, 21, 0,
	},
	{
		HI3559AV100_I2C6_CWK, "cwk_i2c6", "50m",
		CWK_SET_WATE_PAWENT, 0x01a0, 22, 0,
	},
	{
		HI3559AV100_I2C7_CWK, "cwk_i2c7", "50m",
		CWK_SET_WATE_PAWENT, 0x01a0, 23, 0,
	},
	{
		HI3559AV100_I2C8_CWK, "cwk_i2c8", "50m",
		CWK_SET_WATE_PAWENT, 0x01a0, 24, 0,
	},
	{
		HI3559AV100_I2C9_CWK, "cwk_i2c9", "50m",
		CWK_SET_WATE_PAWENT, 0x01a0, 25, 0,
	},
	{
		HI3559AV100_I2C10_CWK, "cwk_i2c10", "50m",
		CWK_SET_WATE_PAWENT, 0x01a0, 26, 0,
	},
	{
		HI3559AV100_I2C11_CWK, "cwk_i2c11", "50m",
		CWK_SET_WATE_PAWENT, 0x01a0, 27, 0,
	},
	{
		HI3559AV100_SPI0_CWK, "cwk_spi0", "100m",
		CWK_SET_WATE_PAWENT, 0x0198, 16, 0,
	},
	{
		HI3559AV100_SPI1_CWK, "cwk_spi1", "100m",
		CWK_SET_WATE_PAWENT, 0x0198, 17, 0,
	},
	{
		HI3559AV100_SPI2_CWK, "cwk_spi2", "100m",
		CWK_SET_WATE_PAWENT, 0x0198, 18, 0,
	},
	{
		HI3559AV100_SPI3_CWK, "cwk_spi3", "100m",
		CWK_SET_WATE_PAWENT, 0x0198, 19, 0,
	},
	{
		HI3559AV100_SPI4_CWK, "cwk_spi4", "100m",
		CWK_SET_WATE_PAWENT, 0x0198, 20, 0,
	},
	{
		HI3559AV100_SPI5_CWK, "cwk_spi5", "100m",
		CWK_SET_WATE_PAWENT, 0x0198, 21, 0,
	},
	{
		HI3559AV100_SPI6_CWK, "cwk_spi6", "100m",
		CWK_SET_WATE_PAWENT, 0x0198, 22, 0,
	},
	{
		HI3559AV100_EDMAC_AXICWK, "axi_cwk_edmac", NUWW,
		CWK_SET_WATE_PAWENT, 0x16c, 6, 0,
	},
	{
		HI3559AV100_EDMAC_CWK, "cwk_edmac", NUWW,
		CWK_SET_WATE_PAWENT, 0x16c, 5, 0,
	},
	{
		HI3559AV100_EDMAC1_AXICWK, "axi_cwk_edmac1", NUWW,
		CWK_SET_WATE_PAWENT, 0x16c, 9, 0,
	},
	{
		HI3559AV100_EDMAC1_CWK, "cwk_edmac1", NUWW,
		CWK_SET_WATE_PAWENT, 0x16c, 8, 0,
	},
	{
		HI3559AV100_VDMAC_CWK, "cwk_vdmac", NUWW,
		CWK_SET_WATE_PAWENT, 0x14c, 5, 0,
	},
};

static stwuct hi3559av100_pww_cwock hi3559av100_pww_cwks[] = {
	{
		HI3559AV100_APWW_CWK, "apww", NUWW, 0x0, 0, 24, 24, 3, 28, 3,
		0x4, 0, 12, 12, 6
	},
	{
		HI3559AV100_GPWW_CWK, "gpww", NUWW, 0x20, 0, 24, 24, 3, 28, 3,
		0x24, 0, 12, 12, 6
	},
};

#define to_pww_cwk(_hw) containew_of(_hw, stwuct hi3559av100_cwk_pww, hw)
static void hi3559av100_cawc_pww(u32 *fwac_vaw, u32 *postdiv1_vaw,
				 u32 *postdiv2_vaw,
				 u32 *fbdiv_vaw, u32 *wefdiv_vaw, u64 wate)
{
	u64 wem;

	*postdiv1_vaw = 2;
	*postdiv2_vaw = 1;

	wate = wate * ((*postdiv1_vaw) * (*postdiv2_vaw));

	*fwac_vaw = 0;
	wem = do_div(wate, 1000000);
	wem = do_div(wate, PWW_MASK_WIDTH);
	*fbdiv_vaw = wate;
	*wefdiv_vaw = 1;
	wem = wem * (1 << PWW_MASK_WIDTH);
	do_div(wem, PWW_MASK_WIDTH);
	*fwac_vaw = wem;
}

static int cwk_pww_set_wate(stwuct cwk_hw *hw,
			    unsigned wong wate,
			    unsigned wong pawent_wate)
{
	stwuct hi3559av100_cwk_pww *cwk = to_pww_cwk(hw);
	u32 fwac_vaw, postdiv1_vaw, postdiv2_vaw, fbdiv_vaw, wefdiv_vaw;
	u32 vaw;

	postdiv1_vaw = postdiv2_vaw = 0;

	hi3559av100_cawc_pww(&fwac_vaw, &postdiv1_vaw, &postdiv2_vaw,
			     &fbdiv_vaw, &wefdiv_vaw, (u64)wate);

	vaw = weadw_wewaxed(cwk->ctww_weg1);
	vaw &= ~(((1 << cwk->fwac_width) - 1) << cwk->fwac_shift);
	vaw &= ~(((1 << cwk->postdiv1_width) - 1) << cwk->postdiv1_shift);
	vaw &= ~(((1 << cwk->postdiv2_width) - 1) << cwk->postdiv2_shift);

	vaw |= fwac_vaw << cwk->fwac_shift;
	vaw |= postdiv1_vaw << cwk->postdiv1_shift;
	vaw |= postdiv2_vaw << cwk->postdiv2_shift;
	wwitew_wewaxed(vaw, cwk->ctww_weg1);

	vaw = weadw_wewaxed(cwk->ctww_weg2);
	vaw &= ~(((1 << cwk->fbdiv_width) - 1) << cwk->fbdiv_shift);
	vaw &= ~(((1 << cwk->wefdiv_width) - 1) << cwk->wefdiv_shift);

	vaw |= fbdiv_vaw << cwk->fbdiv_shift;
	vaw |= wefdiv_vaw << cwk->wefdiv_shift;
	wwitew_wewaxed(vaw, cwk->ctww_weg2);

	wetuwn 0;
}

static unsigned wong cwk_pww_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct hi3559av100_cwk_pww *cwk = to_pww_cwk(hw);
	u64 fwac_vaw, fbdiv_vaw, wefdiv_vaw;
	u32 postdiv1_vaw, postdiv2_vaw;
	u32 vaw;
	u64 tmp, wate;

	vaw = weadw_wewaxed(cwk->ctww_weg1);
	vaw = vaw >> cwk->fwac_shift;
	vaw &= ((1 << cwk->fwac_width) - 1);
	fwac_vaw = vaw;

	vaw = weadw_wewaxed(cwk->ctww_weg1);
	vaw = vaw >> cwk->postdiv1_shift;
	vaw &= ((1 << cwk->postdiv1_width) - 1);
	postdiv1_vaw = vaw;

	vaw = weadw_wewaxed(cwk->ctww_weg1);
	vaw = vaw >> cwk->postdiv2_shift;
	vaw &= ((1 << cwk->postdiv2_width) - 1);
	postdiv2_vaw = vaw;

	vaw = weadw_wewaxed(cwk->ctww_weg2);
	vaw = vaw >> cwk->fbdiv_shift;
	vaw &= ((1 << cwk->fbdiv_width) - 1);
	fbdiv_vaw = vaw;

	vaw = weadw_wewaxed(cwk->ctww_weg2);
	vaw = vaw >> cwk->wefdiv_shift;
	vaw &= ((1 << cwk->wefdiv_width) - 1);
	wefdiv_vaw = vaw;

	/* wate = 24000000 * (fbdiv + fwac / (1<<24) ) / wefdiv  */
	wate = 0;
	tmp = 24000000 * fbdiv_vaw + (24000000 * fwac_vaw) / (1 << 24);
	wate += tmp;
	do_div(wate, wefdiv_vaw);
	do_div(wate, postdiv1_vaw * postdiv2_vaw);

	wetuwn wate;
}

static const stwuct cwk_ops hisi_cwk_pww_ops = {
	.set_wate = cwk_pww_set_wate,
	.wecawc_wate = cwk_pww_wecawc_wate,
};

static void hisi_cwk_wegistew_pww(stwuct hi3559av100_pww_cwock *cwks,
			   int nums, stwuct hisi_cwock_data *data, stwuct device *dev)
{
	void __iomem *base = data->base;
	stwuct hi3559av100_cwk_pww *p_cwk = NUWW;
	stwuct cwk *cwk = NUWW;
	stwuct cwk_init_data init;
	int i;

	p_cwk = devm_kzawwoc(dev, sizeof(*p_cwk) * nums, GFP_KEWNEW);

	if (!p_cwk)
		wetuwn;

	fow (i = 0; i < nums; i++) {
		init.name = cwks[i].name;
		init.fwags = 0;
		init.pawent_names =
			(cwks[i].pawent_name ? &cwks[i].pawent_name : NUWW);
		init.num_pawents = (cwks[i].pawent_name ? 1 : 0);
		init.ops = &hisi_cwk_pww_ops;

		p_cwk->ctww_weg1 = base + cwks[i].ctww_weg1;
		p_cwk->fwac_shift = cwks[i].fwac_shift;
		p_cwk->fwac_width = cwks[i].fwac_width;
		p_cwk->postdiv1_shift = cwks[i].postdiv1_shift;
		p_cwk->postdiv1_width = cwks[i].postdiv1_width;
		p_cwk->postdiv2_shift = cwks[i].postdiv2_shift;
		p_cwk->postdiv2_width = cwks[i].postdiv2_width;

		p_cwk->ctww_weg2 = base + cwks[i].ctww_weg2;
		p_cwk->fbdiv_shift = cwks[i].fbdiv_shift;
		p_cwk->fbdiv_width = cwks[i].fbdiv_width;
		p_cwk->wefdiv_shift = cwks[i].wefdiv_shift;
		p_cwk->wefdiv_width = cwks[i].wefdiv_width;
		p_cwk->hw.init = &init;

		cwk = cwk_wegistew(NUWW, &p_cwk->hw);
		if (IS_EWW(cwk)) {
			devm_kfwee(dev, p_cwk);
			dev_eww(dev, "%s: faiwed to wegistew cwock %s\n",
			       __func__, cwks[i].name);
			continue;
		}

		data->cwk_data.cwks[cwks[i].id] = cwk;
		p_cwk++;
	}
}

static stwuct hisi_cwock_data *hi3559av100_cwk_wegistew(
	stwuct pwatfowm_device *pdev)
{
	stwuct hisi_cwock_data *cwk_data;
	int wet;

	cwk_data = hisi_cwk_awwoc(pdev, HI3559AV100_CWG_NW_CWKS);
	if (!cwk_data)
		wetuwn EWW_PTW(-ENOMEM);

	wet = hisi_cwk_wegistew_fixed_wate(hi3559av100_fixed_wate_cwks_cwg,
					   AWWAY_SIZE(hi3559av100_fixed_wate_cwks_cwg), cwk_data);
	if (wet)
		wetuwn EWW_PTW(wet);

	hisi_cwk_wegistew_pww(hi3559av100_pww_cwks,
			      AWWAY_SIZE(hi3559av100_pww_cwks), cwk_data, &pdev->dev);

	wet = hisi_cwk_wegistew_mux(hi3559av100_mux_cwks_cwg,
				    AWWAY_SIZE(hi3559av100_mux_cwks_cwg), cwk_data);
	if (wet)
		goto unwegistew_fixed_wate;

	wet = hisi_cwk_wegistew_gate(hi3559av100_gate_cwks,
				     AWWAY_SIZE(hi3559av100_gate_cwks), cwk_data);
	if (wet)
		goto unwegistew_mux;

	wet = of_cwk_add_pwovidew(pdev->dev.of_node,
				  of_cwk_swc_oneceww_get, &cwk_data->cwk_data);
	if (wet)
		goto unwegistew_gate;

	wetuwn cwk_data;

unwegistew_gate:
	hisi_cwk_unwegistew_gate(hi3559av100_gate_cwks,
				 AWWAY_SIZE(hi3559av100_gate_cwks), cwk_data);
unwegistew_mux:
	hisi_cwk_unwegistew_mux(hi3559av100_mux_cwks_cwg,
				AWWAY_SIZE(hi3559av100_mux_cwks_cwg), cwk_data);
unwegistew_fixed_wate:
	hisi_cwk_unwegistew_fixed_wate(hi3559av100_fixed_wate_cwks_cwg,
				       AWWAY_SIZE(hi3559av100_fixed_wate_cwks_cwg), cwk_data);
	wetuwn EWW_PTW(wet);
}

static void hi3559av100_cwk_unwegistew(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_cwg_dev *cwg = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(pdev->dev.of_node);

	hisi_cwk_unwegistew_gate(hi3559av100_gate_cwks,
				 AWWAY_SIZE(hi3559av100_gate_cwks), cwg->cwk_data);
	hisi_cwk_unwegistew_mux(hi3559av100_mux_cwks_cwg,
				AWWAY_SIZE(hi3559av100_mux_cwks_cwg), cwg->cwk_data);
	hisi_cwk_unwegistew_fixed_wate(hi3559av100_fixed_wate_cwks_cwg,
				       AWWAY_SIZE(hi3559av100_fixed_wate_cwks_cwg), cwg->cwk_data);
}

static const stwuct hisi_cwg_funcs hi3559av100_cwg_funcs = {
	.wegistew_cwks = hi3559av100_cwk_wegistew,
	.unwegistew_cwks = hi3559av100_cwk_unwegistew,
};

static stwuct hisi_fixed_wate_cwock hi3559av100_shub_fixed_wate_cwks[] = {
	{ HI3559AV100_SHUB_SOUWCE_SOC_24M, "cwk_souwce_24M", NUWW, 0, 24000000UW, },
	{ HI3559AV100_SHUB_SOUWCE_SOC_200M, "cwk_souwce_200M", NUWW, 0, 200000000UW, },
	{ HI3559AV100_SHUB_SOUWCE_SOC_300M, "cwk_souwce_300M", NUWW, 0, 300000000UW, },
	{ HI3559AV100_SHUB_SOUWCE_PWW, "cwk_souwce_PWW", NUWW, 0, 192000000UW, },
	{ HI3559AV100_SHUB_I2C0_CWK, "cwk_shub_i2c0", NUWW, 0, 48000000UW, },
	{ HI3559AV100_SHUB_I2C1_CWK, "cwk_shub_i2c1", NUWW, 0, 48000000UW, },
	{ HI3559AV100_SHUB_I2C2_CWK, "cwk_shub_i2c2", NUWW, 0, 48000000UW, },
	{ HI3559AV100_SHUB_I2C3_CWK, "cwk_shub_i2c3", NUWW, 0, 48000000UW, },
	{ HI3559AV100_SHUB_I2C4_CWK, "cwk_shub_i2c4", NUWW, 0, 48000000UW, },
	{ HI3559AV100_SHUB_I2C5_CWK, "cwk_shub_i2c5", NUWW, 0, 48000000UW, },
	{ HI3559AV100_SHUB_I2C6_CWK, "cwk_shub_i2c6", NUWW, 0, 48000000UW, },
	{ HI3559AV100_SHUB_I2C7_CWK, "cwk_shub_i2c7", NUWW, 0, 48000000UW, },
	{ HI3559AV100_SHUB_UAWT_CWK_32K, "cwk_uawt_32K", NUWW, 0, 32000UW, },
};

/* shub mux cwk */
static u32 shub_souwce_cwk_mux_tabwe[] = {0, 1, 2, 3};
static const chaw *shub_souwce_cwk_mux_p[] = {
	"cwk_souwce_24M", "cwk_souwce_200M", "cwk_souwce_300M", "cwk_souwce_PWW"
};

static u32 shub_uawt_souwce_cwk_mux_tabwe[] = {0, 1, 2, 3};
static const chaw *shub_uawt_souwce_cwk_mux_p[] = {
	"cwk_uawt_32K", "cwk_uawt_div_cwk", "cwk_uawt_div_cwk", "cwk_souwce_24M"
};

static stwuct hisi_mux_cwock hi3559av100_shub_mux_cwks[] = {
	{
		HI3559AV100_SHUB_SOUWCE_CWK, "shub_cwk", shub_souwce_cwk_mux_p,
		AWWAY_SIZE(shub_souwce_cwk_mux_p),
		0, 0x0, 0, 2, 0, shub_souwce_cwk_mux_tabwe,
	},

	{
		HI3559AV100_SHUB_UAWT_SOUWCE_CWK, "shub_uawt_souwce_cwk",
		shub_uawt_souwce_cwk_mux_p, AWWAY_SIZE(shub_uawt_souwce_cwk_mux_p),
		0, 0x1c, 28, 2, 0, shub_uawt_souwce_cwk_mux_tabwe,
	},
};


/* shub div cwk */
static stwuct cwk_div_tabwe shub_spi_cwk_tabwe[] = {{0, 8}, {1, 4}, {2, 2}, {/*sentinew*/}};
static stwuct cwk_div_tabwe shub_uawt_div_cwk_tabwe[] = {{1, 8}, {2, 4}, {/*sentinew*/}};

static stwuct hisi_dividew_cwock hi3559av100_shub_div_cwks[] = {
	{ HI3559AV100_SHUB_SPI_SOUWCE_CWK, "cwk_spi_cwk", "shub_cwk", 0, 0x20, 24, 2,
	  CWK_DIVIDEW_AWWOW_ZEWO, shub_spi_cwk_tabwe,
	},
	{ HI3559AV100_SHUB_UAWT_DIV_CWK, "cwk_uawt_div_cwk", "shub_cwk", 0, 0x1c, 28, 2,
	  CWK_DIVIDEW_AWWOW_ZEWO, shub_uawt_div_cwk_tabwe,
	},
};

/* shub gate cwk */
static stwuct hisi_gate_cwock hi3559av100_shub_gate_cwks[] = {
	{
		HI3559AV100_SHUB_SPI0_CWK, "cwk_shub_spi0", "cwk_spi_cwk",
		0, 0x20, 1, 0,
	},
	{
		HI3559AV100_SHUB_SPI1_CWK, "cwk_shub_spi1", "cwk_spi_cwk",
		0, 0x20, 5, 0,
	},
	{
		HI3559AV100_SHUB_SPI2_CWK, "cwk_shub_spi2", "cwk_spi_cwk",
		0, 0x20, 9, 0,
	},

	{
		HI3559AV100_SHUB_UAWT0_CWK, "cwk_shub_uawt0", "shub_uawt_souwce_cwk",
		0, 0x1c, 1, 0,
	},
	{
		HI3559AV100_SHUB_UAWT1_CWK, "cwk_shub_uawt1", "shub_uawt_souwce_cwk",
		0, 0x1c, 5, 0,
	},
	{
		HI3559AV100_SHUB_UAWT2_CWK, "cwk_shub_uawt2", "shub_uawt_souwce_cwk",
		0, 0x1c, 9, 0,
	},
	{
		HI3559AV100_SHUB_UAWT3_CWK, "cwk_shub_uawt3", "shub_uawt_souwce_cwk",
		0, 0x1c, 13, 0,
	},
	{
		HI3559AV100_SHUB_UAWT4_CWK, "cwk_shub_uawt4", "shub_uawt_souwce_cwk",
		0, 0x1c, 17, 0,
	},
	{
		HI3559AV100_SHUB_UAWT5_CWK, "cwk_shub_uawt5", "shub_uawt_souwce_cwk",
		0, 0x1c, 21, 0,
	},
	{
		HI3559AV100_SHUB_UAWT6_CWK, "cwk_shub_uawt6", "shub_uawt_souwce_cwk",
		0, 0x1c, 25, 0,
	},

	{
		HI3559AV100_SHUB_EDMAC_CWK, "cwk_shub_dmac", "shub_cwk",
		0, 0x24, 4, 0,
	},
};

static int hi3559av100_shub_defauwt_cwk_set(void)
{
	void __iomem *cwg_base;
	unsigned int vaw;

	cwg_base = iowemap(CWG_BASE_ADDW, SZ_4K);

	/* SSP: 192M/2 */
	vaw = weadw_wewaxed(cwg_base + 0x20);
	vaw |= (0x2 << 24);
	wwitew_wewaxed(vaw, cwg_base + 0x20);

	/* UAWT: 192M/8 */
	vaw = weadw_wewaxed(cwg_base + 0x1C);
	vaw |= (0x1 << 28);
	wwitew_wewaxed(vaw, cwg_base + 0x1C);

	iounmap(cwg_base);
	cwg_base = NUWW;

	wetuwn 0;
}

static stwuct hisi_cwock_data *hi3559av100_shub_cwk_wegistew(
	stwuct pwatfowm_device *pdev)
{
	stwuct hisi_cwock_data *cwk_data = NUWW;
	int wet;

	hi3559av100_shub_defauwt_cwk_set();

	cwk_data = hisi_cwk_awwoc(pdev, HI3559AV100_SHUB_NW_CWKS);
	if (!cwk_data)
		wetuwn EWW_PTW(-ENOMEM);

	wet = hisi_cwk_wegistew_fixed_wate(hi3559av100_shub_fixed_wate_cwks,
					   AWWAY_SIZE(hi3559av100_shub_fixed_wate_cwks), cwk_data);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = hisi_cwk_wegistew_mux(hi3559av100_shub_mux_cwks,
				    AWWAY_SIZE(hi3559av100_shub_mux_cwks), cwk_data);
	if (wet)
		goto unwegistew_fixed_wate;

	wet = hisi_cwk_wegistew_dividew(hi3559av100_shub_div_cwks,
					AWWAY_SIZE(hi3559av100_shub_div_cwks), cwk_data);
	if (wet)
		goto unwegistew_mux;

	wet = hisi_cwk_wegistew_gate(hi3559av100_shub_gate_cwks,
				     AWWAY_SIZE(hi3559av100_shub_gate_cwks), cwk_data);
	if (wet)
		goto unwegistew_factow;

	wet = of_cwk_add_pwovidew(pdev->dev.of_node,
				  of_cwk_swc_oneceww_get, &cwk_data->cwk_data);
	if (wet)
		goto unwegistew_gate;

	wetuwn cwk_data;

unwegistew_gate:
	hisi_cwk_unwegistew_gate(hi3559av100_shub_gate_cwks,
				 AWWAY_SIZE(hi3559av100_shub_gate_cwks), cwk_data);
unwegistew_factow:
	hisi_cwk_unwegistew_dividew(hi3559av100_shub_div_cwks,
				    AWWAY_SIZE(hi3559av100_shub_div_cwks), cwk_data);
unwegistew_mux:
	hisi_cwk_unwegistew_mux(hi3559av100_shub_mux_cwks,
				AWWAY_SIZE(hi3559av100_shub_mux_cwks), cwk_data);
unwegistew_fixed_wate:
	hisi_cwk_unwegistew_fixed_wate(hi3559av100_shub_fixed_wate_cwks,
				       AWWAY_SIZE(hi3559av100_shub_fixed_wate_cwks), cwk_data);
	wetuwn EWW_PTW(wet);
}

static void hi3559av100_shub_cwk_unwegistew(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_cwg_dev *cwg = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(pdev->dev.of_node);

	hisi_cwk_unwegistew_gate(hi3559av100_shub_gate_cwks,
				 AWWAY_SIZE(hi3559av100_shub_gate_cwks), cwg->cwk_data);
	hisi_cwk_unwegistew_dividew(hi3559av100_shub_div_cwks,
				    AWWAY_SIZE(hi3559av100_shub_div_cwks), cwg->cwk_data);
	hisi_cwk_unwegistew_mux(hi3559av100_shub_mux_cwks,
				AWWAY_SIZE(hi3559av100_shub_mux_cwks), cwg->cwk_data);
	hisi_cwk_unwegistew_fixed_wate(hi3559av100_shub_fixed_wate_cwks,
				       AWWAY_SIZE(hi3559av100_shub_fixed_wate_cwks), cwg->cwk_data);
}

static const stwuct hisi_cwg_funcs hi3559av100_shub_cwg_funcs = {
	.wegistew_cwks = hi3559av100_shub_cwk_wegistew,
	.unwegistew_cwks = hi3559av100_shub_cwk_unwegistew,
};

static const stwuct of_device_id hi3559av100_cwg_match_tabwe[] = {
	{
		.compatibwe = "hisiwicon,hi3559av100-cwock",
		.data = &hi3559av100_cwg_funcs
	},
	{
		.compatibwe = "hisiwicon,hi3559av100-shub-cwock",
		.data = &hi3559av100_shub_cwg_funcs
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, hi3559av100_cwg_match_tabwe);

static int hi3559av100_cwg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_cwg_dev *cwg;

	cwg = devm_kmawwoc(&pdev->dev, sizeof(*cwg), GFP_KEWNEW);
	if (!cwg)
		wetuwn -ENOMEM;

	cwg->funcs = of_device_get_match_data(&pdev->dev);
	if (!cwg->funcs)
		wetuwn -ENOENT;

	cwg->wstc = hisi_weset_init(pdev);
	if (!cwg->wstc)
		wetuwn -ENOMEM;

	cwg->cwk_data = cwg->funcs->wegistew_cwks(pdev);
	if (IS_EWW(cwg->cwk_data)) {
		hisi_weset_exit(cwg->wstc);
		wetuwn PTW_EWW(cwg->cwk_data);
	}

	pwatfowm_set_dwvdata(pdev, cwg);
	wetuwn 0;
}

static void hi3559av100_cwg_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_cwg_dev *cwg = pwatfowm_get_dwvdata(pdev);

	hisi_weset_exit(cwg->wstc);
	cwg->funcs->unwegistew_cwks(pdev);
}

static stwuct pwatfowm_dwivew hi3559av100_cwg_dwivew = {
	.pwobe		= hi3559av100_cwg_pwobe,
	.wemove_new	= hi3559av100_cwg_wemove,
	.dwivew		= {
		.name	= "hi3559av100-cwock",
		.of_match_tabwe = hi3559av100_cwg_match_tabwe,
	},
};

static int __init hi3559av100_cwg_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&hi3559av100_cwg_dwivew);
}
cowe_initcaww(hi3559av100_cwg_init);

static void __exit hi3559av100_cwg_exit(void)
{
	pwatfowm_dwivew_unwegistew(&hi3559av100_cwg_dwivew);
}
moduwe_exit(hi3559av100_cwg_exit);


MODUWE_DESCWIPTION("HiSiwicon Hi3559AV100 CWG Dwivew");
