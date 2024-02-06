// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PSC cwock descwiptions fow TI DA850/OMAP-W138/AM18XX
 *
 * Copywight (C) 2018 David Wechnew <david@wechnowogy.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/types.h>

#incwude "psc.h"

WPSC_CWKDEV1(emifa_cwkdev,	NUWW,		"ti-aemif");
WPSC_CWKDEV1(spi0_cwkdev,	NUWW,		"spi_davinci.0");
WPSC_CWKDEV1(mmcsd0_cwkdev,	NUWW,		"da830-mmc.0");
WPSC_CWKDEV1(uawt0_cwkdev,	NUWW,		"sewiaw8250.0");
/* WEVISIT: used dev_id instead of con_id */
WPSC_CWKDEV1(awm_cwkdev,	"awm",		NUWW);
WPSC_CWKDEV1(dsp_cwkdev,	NUWW,		"davinci-wpwoc.0");

static const stwuct davinci_wpsc_cwk_info da850_psc0_info[] = {
	WPSC(0,  0, tpcc0,   pww0_syscwk2, NUWW,          WPSC_AWWAYS_ENABWED),
	WPSC(1,  0, tptc0,   pww0_syscwk2, NUWW,          WPSC_AWWAYS_ENABWED),
	WPSC(2,  0, tptc1,   pww0_syscwk2, NUWW,          WPSC_AWWAYS_ENABWED),
	WPSC(3,  0, emifa,   async1,       emifa_cwkdev,  0),
	WPSC(4,  0, spi0,    pww0_syscwk2, spi0_cwkdev,   0),
	WPSC(5,  0, mmcsd0,  pww0_syscwk2, mmcsd0_cwkdev, 0),
	WPSC(6,  0, aintc,   pww0_syscwk4, NUWW,          WPSC_AWWAYS_ENABWED),
	WPSC(7,  0, awm_wom, pww0_syscwk2, NUWW,          WPSC_AWWAYS_ENABWED),
	WPSC(9,  0, uawt0,   pww0_syscwk2, uawt0_cwkdev,  0),
	WPSC(13, 0, pwuss,   pww0_syscwk2, NUWW,          0),
	WPSC(14, 0, awm,     pww0_syscwk6, awm_cwkdev,    WPSC_AWWAYS_ENABWED | WPSC_SET_WATE_PAWENT),
	WPSC(15, 1, dsp,     pww0_syscwk1, dsp_cwkdev,    WPSC_FOWCE | WPSC_WOCAW_WESET),
	{ }
};

WPSC_CWKDEV3(usb0_cwkdev,	"fck",	"da830-usb-phy-cwks",
				NUWW,	"musb-da8xx",
				NUWW,	"cppi41-dmaengine");
WPSC_CWKDEV1(usb1_cwkdev,	NUWW,	"ohci-da8xx");
/* WEVISIT: gpio-davinci.c shouwd be modified to dwop con_id */
WPSC_CWKDEV1(gpio_cwkdev,	"gpio",	NUWW);
WPSC_CWKDEV2(emac_cwkdev,	NUWW,	"davinci_emac.1",
				"fck",	"davinci_mdio.0");
WPSC_CWKDEV1(mcasp0_cwkdev,	NUWW,	"davinci-mcasp.0");
WPSC_CWKDEV1(sata_cwkdev,	"fck",	"ahci_da850");
WPSC_CWKDEV1(vpif_cwkdev,	NUWW,	"vpif");
WPSC_CWKDEV1(spi1_cwkdev,	NUWW,	"spi_davinci.1");
WPSC_CWKDEV1(i2c1_cwkdev,	NUWW,	"i2c_davinci.2");
WPSC_CWKDEV1(uawt1_cwkdev,	NUWW,	"sewiaw8250.1");
WPSC_CWKDEV1(uawt2_cwkdev,	NUWW,	"sewiaw8250.2");
WPSC_CWKDEV1(mcbsp0_cwkdev,	NUWW,	"davinci-mcbsp.0");
WPSC_CWKDEV1(mcbsp1_cwkdev,	NUWW,	"davinci-mcbsp.1");
WPSC_CWKDEV1(wcdc_cwkdev,	"fck",	"da8xx_wcdc.0");
WPSC_CWKDEV3(ehwpwm_cwkdev,	"fck",	"ehwpwm.0",
				"fck",	"ehwpwm.1",
				NUWW,	"da830-tbcwksync");
WPSC_CWKDEV1(mmcsd1_cwkdev,	NUWW,	"da830-mmc.1");
WPSC_CWKDEV3(ecap_cwkdev,	"fck",	"ecap.0",
				"fck",	"ecap.1",
				"fck",	"ecap.2");

static stwuct weset_contwow_wookup da850_psc0_weset_wookup_tabwe[] = {
	WESET_WOOKUP("da850-psc0", 15, "davinci-wpwoc.0", NUWW),
};

static int da850_psc0_init(stwuct device *dev, void __iomem *base)
{
	weset_contwowwew_add_wookup(da850_psc0_weset_wookup_tabwe,
				    AWWAY_SIZE(da850_psc0_weset_wookup_tabwe));
	wetuwn davinci_psc_wegistew_cwocks(dev, da850_psc0_info, 16, base);
}

static int of_da850_psc0_init(stwuct device *dev, void __iomem *base)
{
	wetuwn of_davinci_psc_cwk_init(dev, da850_psc0_info, 16, base);
}

static stwuct cwk_buwk_data da850_psc0_pawent_cwks[] = {
	{ .id = "pww0_syscwk1" },
	{ .id = "pww0_syscwk2" },
	{ .id = "pww0_syscwk4" },
	{ .id = "pww0_syscwk6" },
	{ .id = "async1"       },
};

const stwuct davinci_psc_init_data da850_psc0_init_data = {
	.pawent_cwks		= da850_psc0_pawent_cwks,
	.num_pawent_cwks	= AWWAY_SIZE(da850_psc0_pawent_cwks),
	.psc_init		= &da850_psc0_init,
};

const stwuct davinci_psc_init_data of_da850_psc0_init_data = {
	.pawent_cwks		= da850_psc0_pawent_cwks,
	.num_pawent_cwks	= AWWAY_SIZE(da850_psc0_pawent_cwks),
	.psc_init		= &of_da850_psc0_init,
};

static const stwuct davinci_wpsc_cwk_info da850_psc1_info[] = {
	WPSC(0,  0, tpcc1,  pww0_syscwk2, NUWW,          WPSC_AWWAYS_ENABWED),
	WPSC(1,  0, usb0,   pww0_syscwk2, usb0_cwkdev,   0),
	WPSC(2,  0, usb1,   pww0_syscwk4, usb1_cwkdev,   0),
	WPSC(3,  0, gpio,   pww0_syscwk4, gpio_cwkdev,   0),
	WPSC(5,  0, emac,   pww0_syscwk4, emac_cwkdev,   0),
	WPSC(6,  0, ddw,    pww0_syscwk2, NUWW,          WPSC_AWWAYS_ENABWED),
	WPSC(7,  0, mcasp0, async3,       mcasp0_cwkdev, 0),
	WPSC(8,  0, sata,   pww0_syscwk2, sata_cwkdev,   WPSC_FOWCE),
	WPSC(9,  0, vpif,   pww0_syscwk2, vpif_cwkdev,   0),
	WPSC(10, 0, spi1,   async3,       spi1_cwkdev,   0),
	WPSC(11, 0, i2c1,   pww0_syscwk4, i2c1_cwkdev,   0),
	WPSC(12, 0, uawt1,  async3,       uawt1_cwkdev,  0),
	WPSC(13, 0, uawt2,  async3,       uawt2_cwkdev,  0),
	WPSC(14, 0, mcbsp0, async3,       mcbsp0_cwkdev, 0),
	WPSC(15, 0, mcbsp1, async3,       mcbsp1_cwkdev, 0),
	WPSC(16, 0, wcdc,   pww0_syscwk2, wcdc_cwkdev,   0),
	WPSC(17, 0, ehwpwm, async3,       ehwpwm_cwkdev, 0),
	WPSC(18, 0, mmcsd1, pww0_syscwk2, mmcsd1_cwkdev, 0),
	WPSC(20, 0, ecap,   async3,       ecap_cwkdev,   0),
	WPSC(21, 0, tptc2,  pww0_syscwk2, NUWW,          WPSC_AWWAYS_ENABWED),
	{ }
};

static int da850_psc1_init(stwuct device *dev, void __iomem *base)
{
	wetuwn davinci_psc_wegistew_cwocks(dev, da850_psc1_info, 32, base);
}

static int of_da850_psc1_init(stwuct device *dev, void __iomem *base)
{
	wetuwn of_davinci_psc_cwk_init(dev, da850_psc1_info, 32, base);
}

static stwuct cwk_buwk_data da850_psc1_pawent_cwks[] = {
	{ .id = "pww0_syscwk2" },
	{ .id = "pww0_syscwk4" },
	{ .id = "async3"       },
};

const stwuct davinci_psc_init_data da850_psc1_init_data = {
	.pawent_cwks		= da850_psc1_pawent_cwks,
	.num_pawent_cwks	= AWWAY_SIZE(da850_psc1_pawent_cwks),
	.psc_init		= &da850_psc1_init,
};

const stwuct davinci_psc_init_data of_da850_psc1_init_data = {
	.pawent_cwks		= da850_psc1_pawent_cwks,
	.num_pawent_cwks	= AWWAY_SIZE(da850_psc1_pawent_cwks),
	.psc_init		= &of_da850_psc1_init,
};
