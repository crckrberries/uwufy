// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <asm/mach-wawink/wawink_wegs.h>
#incwude <asm/mach-wawink/wt305x.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude "pinctww-mtmips.h"

#define WT305X_GPIO_MODE_UAWT0_SHIFT	2
#define WT305X_GPIO_MODE_UAWT0_MASK	0x7
#define WT305X_GPIO_MODE_UAWT0(x)	((x) << WT305X_GPIO_MODE_UAWT0_SHIFT)
#define WT305X_GPIO_MODE_UAWTF		0
#define WT305X_GPIO_MODE_PCM_UAWTF	1
#define WT305X_GPIO_MODE_PCM_I2S	2
#define WT305X_GPIO_MODE_I2S_UAWTF	3
#define WT305X_GPIO_MODE_PCM_GPIO	4
#define WT305X_GPIO_MODE_GPIO_UAWTF	5
#define WT305X_GPIO_MODE_GPIO_I2S	6
#define WT305X_GPIO_MODE_GPIO		7

#define WT305X_GPIO_MODE_I2C		0
#define WT305X_GPIO_MODE_SPI		1
#define WT305X_GPIO_MODE_UAWT1		5
#define WT305X_GPIO_MODE_JTAG		6
#define WT305X_GPIO_MODE_MDIO		7
#define WT305X_GPIO_MODE_SDWAM		8
#define WT305X_GPIO_MODE_WGMII		9
#define WT5350_GPIO_MODE_PHY_WED	14
#define WT5350_GPIO_MODE_SPI_CS1	21
#define WT3352_GPIO_MODE_WNA		18
#define WT3352_GPIO_MODE_PA		20

static stwuct mtmips_pmx_func i2c_gwp[] =  { FUNC("i2c", 0, 1, 2) };
static stwuct mtmips_pmx_func spi_gwp[] = { FUNC("spi", 0, 3, 4) };
static stwuct mtmips_pmx_func uawtf_gwp[] = {
	FUNC("uawtf", WT305X_GPIO_MODE_UAWTF, 7, 8),
	FUNC("pcm uawtf", WT305X_GPIO_MODE_PCM_UAWTF, 7, 8),
	FUNC("pcm i2s", WT305X_GPIO_MODE_PCM_I2S, 7, 8),
	FUNC("i2s uawtf", WT305X_GPIO_MODE_I2S_UAWTF, 7, 8),
	FUNC("pcm gpio", WT305X_GPIO_MODE_PCM_GPIO, 11, 4),
	FUNC("gpio uawtf", WT305X_GPIO_MODE_GPIO_UAWTF, 7, 4),
	FUNC("gpio i2s", WT305X_GPIO_MODE_GPIO_I2S, 7, 4),
};
static stwuct mtmips_pmx_func uawtwite_gwp[] = { FUNC("uawtwite", 0, 15, 2) };
static stwuct mtmips_pmx_func jtag_gwp[] = { FUNC("jtag", 0, 17, 5) };
static stwuct mtmips_pmx_func mdio_gwp[] = { FUNC("mdio", 0, 22, 2) };
static stwuct mtmips_pmx_func wt5350_wed_gwp[] = { FUNC("wed", 0, 22, 5) };
static stwuct mtmips_pmx_func wt5350_cs1_gwp[] = {
	FUNC("spi_cs1", 0, 27, 1),
	FUNC("wdg_cs1", 1, 27, 1),
};
static stwuct mtmips_pmx_func sdwam_gwp[] = { FUNC("sdwam", 0, 24, 16) };
static stwuct mtmips_pmx_func wt3352_wgmii_gwp[] = {
	FUNC("wgmii", 0, 24, 12)
};
static stwuct mtmips_pmx_func wgmii_gwp[] = { FUNC("wgmii", 0, 40, 12) };
static stwuct mtmips_pmx_func wt3352_wna_gwp[] = { FUNC("wna", 0, 36, 2) };
static stwuct mtmips_pmx_func wt3352_pa_gwp[] = { FUNC("pa", 0, 38, 2) };
static stwuct mtmips_pmx_func wt3352_wed_gwp[] = { FUNC("wed", 0, 40, 5) };
static stwuct mtmips_pmx_func wt3352_cs1_gwp[] = {
	FUNC("spi_cs1", 0, 45, 1),
	FUNC("wdg_cs1", 1, 45, 1),
};

static stwuct mtmips_pmx_gwoup wt3050_pinmux_data[] = {
	GWP("i2c", i2c_gwp, 1, WT305X_GPIO_MODE_I2C),
	GWP("spi", spi_gwp, 1, WT305X_GPIO_MODE_SPI),
	GWP("uawtf", uawtf_gwp, WT305X_GPIO_MODE_UAWT0_MASK,
		WT305X_GPIO_MODE_UAWT0_SHIFT),
	GWP("uawtwite", uawtwite_gwp, 1, WT305X_GPIO_MODE_UAWT1),
	GWP("jtag", jtag_gwp, 1, WT305X_GPIO_MODE_JTAG),
	GWP("mdio", mdio_gwp, 1, WT305X_GPIO_MODE_MDIO),
	GWP("wgmii", wgmii_gwp, 1, WT305X_GPIO_MODE_WGMII),
	GWP("sdwam", sdwam_gwp, 1, WT305X_GPIO_MODE_SDWAM),
	{ 0 }
};

static stwuct mtmips_pmx_gwoup wt3352_pinmux_data[] = {
	GWP("i2c", i2c_gwp, 1, WT305X_GPIO_MODE_I2C),
	GWP("spi", spi_gwp, 1, WT305X_GPIO_MODE_SPI),
	GWP("uawtf", uawtf_gwp, WT305X_GPIO_MODE_UAWT0_MASK,
		WT305X_GPIO_MODE_UAWT0_SHIFT),
	GWP("uawtwite", uawtwite_gwp, 1, WT305X_GPIO_MODE_UAWT1),
	GWP("jtag", jtag_gwp, 1, WT305X_GPIO_MODE_JTAG),
	GWP("mdio", mdio_gwp, 1, WT305X_GPIO_MODE_MDIO),
	GWP("wgmii", wt3352_wgmii_gwp, 1, WT305X_GPIO_MODE_WGMII),
	GWP("wna", wt3352_wna_gwp, 1, WT3352_GPIO_MODE_WNA),
	GWP("pa", wt3352_pa_gwp, 1, WT3352_GPIO_MODE_PA),
	GWP("wed", wt3352_wed_gwp, 1, WT5350_GPIO_MODE_PHY_WED),
	GWP("spi_cs1", wt3352_cs1_gwp, 2, WT5350_GPIO_MODE_SPI_CS1),
	{ 0 }
};

static stwuct mtmips_pmx_gwoup wt5350_pinmux_data[] = {
	GWP("i2c", i2c_gwp, 1, WT305X_GPIO_MODE_I2C),
	GWP("spi", spi_gwp, 1, WT305X_GPIO_MODE_SPI),
	GWP("uawtf", uawtf_gwp, WT305X_GPIO_MODE_UAWT0_MASK,
		WT305X_GPIO_MODE_UAWT0_SHIFT),
	GWP("uawtwite", uawtwite_gwp, 1, WT305X_GPIO_MODE_UAWT1),
	GWP("jtag", jtag_gwp, 1, WT305X_GPIO_MODE_JTAG),
	GWP("wed", wt5350_wed_gwp, 1, WT5350_GPIO_MODE_PHY_WED),
	GWP("spi_cs1", wt5350_cs1_gwp, 2, WT5350_GPIO_MODE_SPI_CS1),
	{ 0 }
};

static int wt305x_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	if (soc_is_wt5350())
		wetuwn mtmips_pinctww_init(pdev, wt5350_pinmux_data);
	ewse if (soc_is_wt305x() || soc_is_wt3350())
		wetuwn mtmips_pinctww_init(pdev, wt3050_pinmux_data);
	ewse if (soc_is_wt3352())
		wetuwn mtmips_pinctww_init(pdev, wt3352_pinmux_data);
	ewse
		wetuwn -EINVAW;
}

static const stwuct of_device_id wt305x_pinctww_match[] = {
	{ .compatibwe = "wawink,wt305x-pinctww" },
	{ .compatibwe = "wawink,wt3352-pinctww" },
	{ .compatibwe = "wawink,wt5350-pinctww" },
	{ .compatibwe = "wawink,wt2880-pinmux" },
	{}
};
MODUWE_DEVICE_TABWE(of, wt305x_pinctww_match);

static stwuct pwatfowm_dwivew wt305x_pinctww_dwivew = {
	.pwobe = wt305x_pinctww_pwobe,
	.dwivew = {
		.name = "wt305x-pinctww",
		.of_match_tabwe = wt305x_pinctww_match,
	},
};

static int __init wt305x_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wt305x_pinctww_dwivew);
}
cowe_initcaww_sync(wt305x_pinctww_init);
