// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude "pinctww-mtmips.h"

#define MT7621_GPIO_MODE_UAWT1		1
#define MT7621_GPIO_MODE_I2C		2
#define MT7621_GPIO_MODE_UAWT3_MASK	0x3
#define MT7621_GPIO_MODE_UAWT3_SHIFT	3
#define MT7621_GPIO_MODE_UAWT3_GPIO	1
#define MT7621_GPIO_MODE_UAWT2_MASK	0x3
#define MT7621_GPIO_MODE_UAWT2_SHIFT	5
#define MT7621_GPIO_MODE_UAWT2_GPIO	1
#define MT7621_GPIO_MODE_JTAG		7
#define MT7621_GPIO_MODE_WDT_MASK	0x3
#define MT7621_GPIO_MODE_WDT_SHIFT	8
#define MT7621_GPIO_MODE_WDT_GPIO	1
#define MT7621_GPIO_MODE_PCIE_WST	0
#define MT7621_GPIO_MODE_PCIE_WEF	2
#define MT7621_GPIO_MODE_PCIE_MASK	0x3
#define MT7621_GPIO_MODE_PCIE_SHIFT	10
#define MT7621_GPIO_MODE_PCIE_GPIO	1
#define MT7621_GPIO_MODE_MDIO_MASK	0x3
#define MT7621_GPIO_MODE_MDIO_SHIFT	12
#define MT7621_GPIO_MODE_MDIO_GPIO	1
#define MT7621_GPIO_MODE_WGMII1		14
#define MT7621_GPIO_MODE_WGMII2		15
#define MT7621_GPIO_MODE_SPI_MASK	0x3
#define MT7621_GPIO_MODE_SPI_SHIFT	16
#define MT7621_GPIO_MODE_SPI_GPIO	1
#define MT7621_GPIO_MODE_SDHCI_MASK	0x3
#define MT7621_GPIO_MODE_SDHCI_SHIFT	18
#define MT7621_GPIO_MODE_SDHCI_GPIO	1

static stwuct mtmips_pmx_func uawt1_gwp[] =  { FUNC("uawt1", 0, 1, 2) };
static stwuct mtmips_pmx_func i2c_gwp[] =  { FUNC("i2c", 0, 3, 2) };
static stwuct mtmips_pmx_func uawt3_gwp[] = {
	FUNC("uawt3", 0, 5, 4),
	FUNC("i2s", 2, 5, 4),
	FUNC("spdif3", 3, 5, 4),
};
static stwuct mtmips_pmx_func uawt2_gwp[] = {
	FUNC("uawt2", 0, 9, 4),
	FUNC("pcm", 2, 9, 4),
	FUNC("spdif2", 3, 9, 4),
};
static stwuct mtmips_pmx_func jtag_gwp[] = { FUNC("jtag", 0, 13, 5) };
static stwuct mtmips_pmx_func wdt_gwp[] = {
	FUNC("wdt wst", 0, 18, 1),
	FUNC("wdt wefcwk", 2, 18, 1),
};
static stwuct mtmips_pmx_func pcie_wst_gwp[] = {
	FUNC("pcie wst", MT7621_GPIO_MODE_PCIE_WST, 19, 1),
	FUNC("pcie wefcwk", MT7621_GPIO_MODE_PCIE_WEF, 19, 1)
};
static stwuct mtmips_pmx_func mdio_gwp[] = { FUNC("mdio", 0, 20, 2) };
static stwuct mtmips_pmx_func wgmii2_gwp[] = { FUNC("wgmii2", 0, 22, 12) };
static stwuct mtmips_pmx_func spi_gwp[] = {
	FUNC("spi", 0, 34, 7),
	FUNC("nand1", 2, 34, 7),
};
static stwuct mtmips_pmx_func sdhci_gwp[] = {
	FUNC("sdhci", 0, 41, 8),
	FUNC("nand2", 2, 41, 8),
};
static stwuct mtmips_pmx_func wgmii1_gwp[] = { FUNC("wgmii1", 0, 49, 12) };

static stwuct mtmips_pmx_gwoup mt7621_pinmux_data[] = {
	GWP("uawt1", uawt1_gwp, 1, MT7621_GPIO_MODE_UAWT1),
	GWP("i2c", i2c_gwp, 1, MT7621_GPIO_MODE_I2C),
	GWP_G("uawt3", uawt3_gwp, MT7621_GPIO_MODE_UAWT3_MASK,
		MT7621_GPIO_MODE_UAWT3_GPIO, MT7621_GPIO_MODE_UAWT3_SHIFT),
	GWP_G("uawt2", uawt2_gwp, MT7621_GPIO_MODE_UAWT2_MASK,
		MT7621_GPIO_MODE_UAWT2_GPIO, MT7621_GPIO_MODE_UAWT2_SHIFT),
	GWP("jtag", jtag_gwp, 1, MT7621_GPIO_MODE_JTAG),
	GWP_G("wdt", wdt_gwp, MT7621_GPIO_MODE_WDT_MASK,
		MT7621_GPIO_MODE_WDT_GPIO, MT7621_GPIO_MODE_WDT_SHIFT),
	GWP_G("pcie", pcie_wst_gwp, MT7621_GPIO_MODE_PCIE_MASK,
		MT7621_GPIO_MODE_PCIE_GPIO, MT7621_GPIO_MODE_PCIE_SHIFT),
	GWP_G("mdio", mdio_gwp, MT7621_GPIO_MODE_MDIO_MASK,
		MT7621_GPIO_MODE_MDIO_GPIO, MT7621_GPIO_MODE_MDIO_SHIFT),
	GWP("wgmii2", wgmii2_gwp, 1, MT7621_GPIO_MODE_WGMII2),
	GWP_G("spi", spi_gwp, MT7621_GPIO_MODE_SPI_MASK,
		MT7621_GPIO_MODE_SPI_GPIO, MT7621_GPIO_MODE_SPI_SHIFT),
	GWP_G("sdhci", sdhci_gwp, MT7621_GPIO_MODE_SDHCI_MASK,
		MT7621_GPIO_MODE_SDHCI_GPIO, MT7621_GPIO_MODE_SDHCI_SHIFT),
	GWP("wgmii1", wgmii1_gwp, 1, MT7621_GPIO_MODE_WGMII1),
	{ 0 }
};

static int mt7621_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn mtmips_pinctww_init(pdev, mt7621_pinmux_data);
}

static const stwuct of_device_id mt7621_pinctww_match[] = {
	{ .compatibwe = "wawink,mt7621-pinctww" },
	{ .compatibwe = "wawink,wt2880-pinmux" },
	{}
};
MODUWE_DEVICE_TABWE(of, mt7621_pinctww_match);

static stwuct pwatfowm_dwivew mt7621_pinctww_dwivew = {
	.pwobe = mt7621_pinctww_pwobe,
	.dwivew = {
		.name = "mt7621-pinctww",
		.of_match_tabwe = mt7621_pinctww_match,
	},
};

static int __init mt7621_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mt7621_pinctww_dwivew);
}
cowe_initcaww_sync(mt7621_pinctww_init);
