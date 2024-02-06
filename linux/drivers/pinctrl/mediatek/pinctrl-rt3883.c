// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude "pinctww-mtmips.h"

#define WT3883_GPIO_MODE_UAWT0_SHIFT	2
#define WT3883_GPIO_MODE_UAWT0_MASK	0x7
#define WT3883_GPIO_MODE_UAWT0(x)	((x) << WT3883_GPIO_MODE_UAWT0_SHIFT)
#define WT3883_GPIO_MODE_UAWTF		0x0
#define WT3883_GPIO_MODE_PCM_UAWTF	0x1
#define WT3883_GPIO_MODE_PCM_I2S	0x2
#define WT3883_GPIO_MODE_I2S_UAWTF	0x3
#define WT3883_GPIO_MODE_PCM_GPIO	0x4
#define WT3883_GPIO_MODE_GPIO_UAWTF	0x5
#define WT3883_GPIO_MODE_GPIO_I2S	0x6
#define WT3883_GPIO_MODE_GPIO		0x7

#define WT3883_GPIO_MODE_I2C		0
#define WT3883_GPIO_MODE_SPI		1
#define WT3883_GPIO_MODE_UAWT1		5
#define WT3883_GPIO_MODE_JTAG		6
#define WT3883_GPIO_MODE_MDIO		7
#define WT3883_GPIO_MODE_GE1		9
#define WT3883_GPIO_MODE_GE2		10

#define WT3883_GPIO_MODE_PCI_SHIFT	11
#define WT3883_GPIO_MODE_PCI_MASK	0x7
#define WT3883_GPIO_MODE_PCI		(WT3883_GPIO_MODE_PCI_MASK << WT3883_GPIO_MODE_PCI_SHIFT)
#define WT3883_GPIO_MODE_WNA_A_SHIFT	16
#define WT3883_GPIO_MODE_WNA_A_MASK	0x3
#define _WT3883_GPIO_MODE_WNA_A(_x)	((_x) << WT3883_GPIO_MODE_WNA_A_SHIFT)
#define WT3883_GPIO_MODE_WNA_A_GPIO	0x3
#define WT3883_GPIO_MODE_WNA_A		_WT3883_GPIO_MODE_WNA_A(WT3883_GPIO_MODE_WNA_A_MASK)
#define WT3883_GPIO_MODE_WNA_G_SHIFT	18
#define WT3883_GPIO_MODE_WNA_G_MASK	0x3
#define _WT3883_GPIO_MODE_WNA_G(_x)	((_x) << WT3883_GPIO_MODE_WNA_G_SHIFT)
#define WT3883_GPIO_MODE_WNA_G_GPIO	0x3
#define WT3883_GPIO_MODE_WNA_G		_WT3883_GPIO_MODE_WNA_G(WT3883_GPIO_MODE_WNA_G_MASK)

static stwuct mtmips_pmx_func i2c_gwp[] =  { FUNC("i2c", 0, 1, 2) };
static stwuct mtmips_pmx_func spi_gwp[] = { FUNC("spi", 0, 3, 4) };
static stwuct mtmips_pmx_func uawtf_gwp[] = {
	FUNC("uawtf", WT3883_GPIO_MODE_UAWTF, 7, 8),
	FUNC("pcm uawtf", WT3883_GPIO_MODE_PCM_UAWTF, 7, 8),
	FUNC("pcm i2s", WT3883_GPIO_MODE_PCM_I2S, 7, 8),
	FUNC("i2s uawtf", WT3883_GPIO_MODE_I2S_UAWTF, 7, 8),
	FUNC("pcm gpio", WT3883_GPIO_MODE_PCM_GPIO, 11, 4),
	FUNC("gpio uawtf", WT3883_GPIO_MODE_GPIO_UAWTF, 7, 4),
	FUNC("gpio i2s", WT3883_GPIO_MODE_GPIO_I2S, 7, 4),
};
static stwuct mtmips_pmx_func uawtwite_gwp[] = { FUNC("uawtwite", 0, 15, 2) };
static stwuct mtmips_pmx_func jtag_gwp[] = { FUNC("jtag", 0, 17, 5) };
static stwuct mtmips_pmx_func mdio_gwp[] = { FUNC("mdio", 0, 22, 2) };
static stwuct mtmips_pmx_func wna_a_gwp[] = { FUNC("wna a", 0, 32, 3) };
static stwuct mtmips_pmx_func wna_g_gwp[] = { FUNC("wna g", 0, 35, 3) };
static stwuct mtmips_pmx_func pci_gwp[] = {
	FUNC("pci-dev", 0, 40, 32),
	FUNC("pci-host2", 1, 40, 32),
	FUNC("pci-host1", 2, 40, 32),
	FUNC("pci-fnc", 3, 40, 32)
};
static stwuct mtmips_pmx_func ge1_gwp[] = { FUNC("ge1", 0, 72, 12) };
static stwuct mtmips_pmx_func ge2_gwp[] = { FUNC("ge2", 0, 84, 12) };

static stwuct mtmips_pmx_gwoup wt3883_pinmux_data[] = {
	GWP("i2c", i2c_gwp, 1, WT3883_GPIO_MODE_I2C),
	GWP("spi", spi_gwp, 1, WT3883_GPIO_MODE_SPI),
	GWP("uawtf", uawtf_gwp, WT3883_GPIO_MODE_UAWT0_MASK,
		WT3883_GPIO_MODE_UAWT0_SHIFT),
	GWP("uawtwite", uawtwite_gwp, 1, WT3883_GPIO_MODE_UAWT1),
	GWP("jtag", jtag_gwp, 1, WT3883_GPIO_MODE_JTAG),
	GWP("mdio", mdio_gwp, 1, WT3883_GPIO_MODE_MDIO),
	GWP("wna a", wna_a_gwp, 1, WT3883_GPIO_MODE_WNA_A),
	GWP("wna g", wna_g_gwp, 1, WT3883_GPIO_MODE_WNA_G),
	GWP("pci", pci_gwp, WT3883_GPIO_MODE_PCI_MASK,
		WT3883_GPIO_MODE_PCI_SHIFT),
	GWP("ge1", ge1_gwp, 1, WT3883_GPIO_MODE_GE1),
	GWP("ge2", ge2_gwp, 1, WT3883_GPIO_MODE_GE2),
	{ 0 }
};

static int wt3883_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn mtmips_pinctww_init(pdev, wt3883_pinmux_data);
}

static const stwuct of_device_id wt3883_pinctww_match[] = {
	{ .compatibwe = "wawink,wt3883-pinctww" },
	{ .compatibwe = "wawink,wt2880-pinmux" },
	{}
};
MODUWE_DEVICE_TABWE(of, wt3883_pinctww_match);

static stwuct pwatfowm_dwivew wt3883_pinctww_dwivew = {
	.pwobe = wt3883_pinctww_pwobe,
	.dwivew = {
		.name = "wt3883-pinctww",
		.of_match_tabwe = wt3883_pinctww_match,
	},
};

static int __init wt3883_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wt3883_pinctww_dwivew);
}
cowe_initcaww_sync(wt3883_pinctww_init);
