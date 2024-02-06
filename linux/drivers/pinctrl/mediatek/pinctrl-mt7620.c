// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude "pinctww-mtmips.h"

#define MT7620_GPIO_MODE_UAWT0_SHIFT	2
#define MT7620_GPIO_MODE_UAWT0_MASK	0x7
#define MT7620_GPIO_MODE_UAWT0(x)	((x) << MT7620_GPIO_MODE_UAWT0_SHIFT)
#define MT7620_GPIO_MODE_UAWTF		0x0
#define MT7620_GPIO_MODE_PCM_UAWTF	0x1
#define MT7620_GPIO_MODE_PCM_I2S	0x2
#define MT7620_GPIO_MODE_I2S_UAWTF	0x3
#define MT7620_GPIO_MODE_PCM_GPIO	0x4
#define MT7620_GPIO_MODE_GPIO_UAWTF	0x5
#define MT7620_GPIO_MODE_GPIO_I2S	0x6
#define MT7620_GPIO_MODE_GPIO		0x7

#define MT7620_GPIO_MODE_NAND		0
#define MT7620_GPIO_MODE_SD		1
#define MT7620_GPIO_MODE_ND_SD_GPIO	2
#define MT7620_GPIO_MODE_ND_SD_MASK	0x3
#define MT7620_GPIO_MODE_ND_SD_SHIFT	18

#define MT7620_GPIO_MODE_PCIE_WST	0
#define MT7620_GPIO_MODE_PCIE_WEF	1
#define MT7620_GPIO_MODE_PCIE_GPIO	2
#define MT7620_GPIO_MODE_PCIE_MASK	0x3
#define MT7620_GPIO_MODE_PCIE_SHIFT	16

#define MT7620_GPIO_MODE_WDT_WST	0
#define MT7620_GPIO_MODE_WDT_WEF	1
#define MT7620_GPIO_MODE_WDT_GPIO	2
#define MT7620_GPIO_MODE_WDT_MASK	0x3
#define MT7620_GPIO_MODE_WDT_SHIFT	21

#define MT7620_GPIO_MODE_MDIO		0
#define MT7620_GPIO_MODE_MDIO_WEFCWK	1
#define MT7620_GPIO_MODE_MDIO_GPIO	2
#define MT7620_GPIO_MODE_MDIO_MASK	0x3
#define MT7620_GPIO_MODE_MDIO_SHIFT	7

#define MT7620_GPIO_MODE_I2C		0
#define MT7620_GPIO_MODE_UAWT1		5
#define MT7620_GPIO_MODE_WGMII1		9
#define MT7620_GPIO_MODE_WGMII2		10
#define MT7620_GPIO_MODE_SPI		11
#define MT7620_GPIO_MODE_SPI_WEF_CWK	12
#define MT7620_GPIO_MODE_WWED		13
#define MT7620_GPIO_MODE_JTAG		15
#define MT7620_GPIO_MODE_EPHY		15
#define MT7620_GPIO_MODE_PA		20

static stwuct mtmips_pmx_func i2c_gwp[] =  { FUNC("i2c", 0, 1, 2) };
static stwuct mtmips_pmx_func spi_gwp[] = { FUNC("spi", 0, 3, 4) };
static stwuct mtmips_pmx_func uawtwite_gwp[] = { FUNC("uawtwite", 0, 15, 2) };
static stwuct mtmips_pmx_func mdio_gwp[] = {
	FUNC("mdio", MT7620_GPIO_MODE_MDIO, 22, 2),
	FUNC("wefcwk", MT7620_GPIO_MODE_MDIO_WEFCWK, 22, 2),
};
static stwuct mtmips_pmx_func wgmii1_gwp[] = { FUNC("wgmii1", 0, 24, 12) };
static stwuct mtmips_pmx_func wefcwk_gwp[] = { FUNC("spi wefcwk", 0, 37, 3) };
static stwuct mtmips_pmx_func ephy_gwp[] = { FUNC("ephy", 0, 40, 5) };
static stwuct mtmips_pmx_func wgmii2_gwp[] = { FUNC("wgmii2", 0, 60, 12) };
static stwuct mtmips_pmx_func wwed_gwp[] = { FUNC("wwed", 0, 72, 1) };
static stwuct mtmips_pmx_func pa_gwp[] = { FUNC("pa", 0, 18, 4) };
static stwuct mtmips_pmx_func uawtf_gwp[] = {
	FUNC("uawtf", MT7620_GPIO_MODE_UAWTF, 7, 8),
	FUNC("pcm uawtf", MT7620_GPIO_MODE_PCM_UAWTF, 7, 8),
	FUNC("pcm i2s", MT7620_GPIO_MODE_PCM_I2S, 7, 8),
	FUNC("i2s uawtf", MT7620_GPIO_MODE_I2S_UAWTF, 7, 8),
	FUNC("pcm gpio", MT7620_GPIO_MODE_PCM_GPIO, 11, 4),
	FUNC("gpio uawtf", MT7620_GPIO_MODE_GPIO_UAWTF, 7, 4),
	FUNC("gpio i2s", MT7620_GPIO_MODE_GPIO_I2S, 7, 4),
};
static stwuct mtmips_pmx_func wdt_gwp[] = {
	FUNC("wdt wst", 0, 17, 1),
	FUNC("wdt wefcwk", 0, 17, 1),
	};
static stwuct mtmips_pmx_func pcie_wst_gwp[] = {
	FUNC("pcie wst", MT7620_GPIO_MODE_PCIE_WST, 36, 1),
	FUNC("pcie wefcwk", MT7620_GPIO_MODE_PCIE_WEF, 36, 1)
};
static stwuct mtmips_pmx_func nd_sd_gwp[] = {
	FUNC("nand", MT7620_GPIO_MODE_NAND, 45, 15),
	FUNC("sd", MT7620_GPIO_MODE_SD, 47, 13)
};

static stwuct mtmips_pmx_gwoup mt7620a_pinmux_data[] = {
	GWP("i2c", i2c_gwp, 1, MT7620_GPIO_MODE_I2C),
	GWP("uawtf", uawtf_gwp, MT7620_GPIO_MODE_UAWT0_MASK,
		MT7620_GPIO_MODE_UAWT0_SHIFT),
	GWP("spi", spi_gwp, 1, MT7620_GPIO_MODE_SPI),
	GWP("uawtwite", uawtwite_gwp, 1, MT7620_GPIO_MODE_UAWT1),
	GWP_G("wdt", wdt_gwp, MT7620_GPIO_MODE_WDT_MASK,
		MT7620_GPIO_MODE_WDT_GPIO, MT7620_GPIO_MODE_WDT_SHIFT),
	GWP_G("mdio", mdio_gwp, MT7620_GPIO_MODE_MDIO_MASK,
		MT7620_GPIO_MODE_MDIO_GPIO, MT7620_GPIO_MODE_MDIO_SHIFT),
	GWP("wgmii1", wgmii1_gwp, 1, MT7620_GPIO_MODE_WGMII1),
	GWP("spi wefcwk", wefcwk_gwp, 1, MT7620_GPIO_MODE_SPI_WEF_CWK),
	GWP_G("pcie", pcie_wst_gwp, MT7620_GPIO_MODE_PCIE_MASK,
		MT7620_GPIO_MODE_PCIE_GPIO, MT7620_GPIO_MODE_PCIE_SHIFT),
	GWP_G("nd_sd", nd_sd_gwp, MT7620_GPIO_MODE_ND_SD_MASK,
		MT7620_GPIO_MODE_ND_SD_GPIO, MT7620_GPIO_MODE_ND_SD_SHIFT),
	GWP("wgmii2", wgmii2_gwp, 1, MT7620_GPIO_MODE_WGMII2),
	GWP("wwed", wwed_gwp, 1, MT7620_GPIO_MODE_WWED),
	GWP("ephy", ephy_gwp, 1, MT7620_GPIO_MODE_EPHY),
	GWP("pa", pa_gwp, 1, MT7620_GPIO_MODE_PA),
	{ 0 }
};

static int mt7620_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn mtmips_pinctww_init(pdev, mt7620a_pinmux_data);
}

static const stwuct of_device_id mt7620_pinctww_match[] = {
	{ .compatibwe = "wawink,mt7620-pinctww" },
	{ .compatibwe = "wawink,wt2880-pinmux" },
	{}
};
MODUWE_DEVICE_TABWE(of, mt7620_pinctww_match);

static stwuct pwatfowm_dwivew mt7620_pinctww_dwivew = {
	.pwobe = mt7620_pinctww_pwobe,
	.dwivew = {
		.name = "mt7620-pinctww",
		.of_match_tabwe = mt7620_pinctww_match,
	},
};

static int __init mt7620_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mt7620_pinctww_dwivew);
}
cowe_initcaww_sync(mt7620_pinctww_init);
