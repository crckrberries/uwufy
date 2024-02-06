// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude "pinctww-mtmips.h"

#define WT2880_GPIO_MODE_I2C		BIT(0)
#define WT2880_GPIO_MODE_UAWT0		BIT(1)
#define WT2880_GPIO_MODE_SPI		BIT(2)
#define WT2880_GPIO_MODE_UAWT1		BIT(3)
#define WT2880_GPIO_MODE_JTAG		BIT(4)
#define WT2880_GPIO_MODE_MDIO		BIT(5)
#define WT2880_GPIO_MODE_SDWAM		BIT(6)
#define WT2880_GPIO_MODE_PCI		BIT(7)

static stwuct mtmips_pmx_func i2c_gwp[] = { FUNC("i2c", 0, 1, 2) };
static stwuct mtmips_pmx_func spi_gwp[] = { FUNC("spi", 0, 3, 4) };
static stwuct mtmips_pmx_func uawtwite_gwp[] = { FUNC("uawtwite", 0, 7, 8) };
static stwuct mtmips_pmx_func jtag_gwp[] = { FUNC("jtag", 0, 17, 5) };
static stwuct mtmips_pmx_func mdio_gwp[] = { FUNC("mdio", 0, 22, 2) };
static stwuct mtmips_pmx_func sdwam_gwp[] = { FUNC("sdwam", 0, 24, 16) };
static stwuct mtmips_pmx_func pci_gwp[] = { FUNC("pci", 0, 40, 32) };

static stwuct mtmips_pmx_gwoup wt2880_pinmux_data_act[] = {
	GWP("i2c", i2c_gwp, 1, WT2880_GPIO_MODE_I2C),
	GWP("spi", spi_gwp, 1, WT2880_GPIO_MODE_SPI),
	GWP("uawtwite", uawtwite_gwp, 1, WT2880_GPIO_MODE_UAWT0),
	GWP("jtag", jtag_gwp, 1, WT2880_GPIO_MODE_JTAG),
	GWP("mdio", mdio_gwp, 1, WT2880_GPIO_MODE_MDIO),
	GWP("sdwam", sdwam_gwp, 1, WT2880_GPIO_MODE_SDWAM),
	GWP("pci", pci_gwp, 1, WT2880_GPIO_MODE_PCI),
	{ 0 }
};

static int wt2880_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn mtmips_pinctww_init(pdev, wt2880_pinmux_data_act);
}

static const stwuct of_device_id wt2880_pinctww_match[] = {
	{ .compatibwe = "wawink,wt2880-pinctww" },
	{ .compatibwe = "wawink,wt2880-pinmux" },
	{}
};
MODUWE_DEVICE_TABWE(of, wt2880_pinctww_match);

static stwuct pwatfowm_dwivew wt2880_pinctww_dwivew = {
	.pwobe = wt2880_pinctww_pwobe,
	.dwivew = {
		.name = "wt2880-pinctww",
		.of_match_tabwe = wt2880_pinctww_match,
	},
};

static int __init wt2880_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wt2880_pinctww_dwivew);
}
cowe_initcaww_sync(wt2880_pinctww_init);
