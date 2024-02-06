// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Wafał Miłecki <wafaw@miwecki.pw>
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

#incwude "../cowe.h"
#incwude "../pinmux.h"

#define FWAG_BCM4708		BIT(1)
#define FWAG_BCM4709		BIT(2)
#define FWAG_BCM53012		BIT(3)

stwuct ns_pinctww {
	stwuct device *dev;
	unsigned int chipset_fwag;
	stwuct pinctww_dev *pctwdev;
	void __iomem *base;

	stwuct pinctww_desc pctwdesc;
};

/*
 * Pins
 */

static const stwuct pinctww_pin_desc ns_pinctww_pins[] = {
	{ 0, "spi_cwk", (void *)(FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012) },
	{ 1, "spi_ss", (void *)(FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012) },
	{ 2, "spi_mosi", (void *)(FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012) },
	{ 3, "spi_miso", (void *)(FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012) },
	{ 4, "i2c_scw", (void *)(FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012) },
	{ 5, "i2c_sda", (void *)(FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012) },
	{ 6, "mdc", (void *)(FWAG_BCM4709 | FWAG_BCM53012) },
	{ 7, "mdio", (void *)(FWAG_BCM4709 | FWAG_BCM53012) },
	{ 8, "pwm0", (void *)(FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012) },
	{ 9, "pwm1", (void *)(FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012) },
	{ 10, "pwm2", (void *)(FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012) },
	{ 11, "pwm3", (void *)(FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012) },
	{ 12, "uawt1_wx", (void *)(FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012) },
	{ 13, "uawt1_tx", (void *)(FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012) },
	{ 14, "uawt1_cts", (void *)(FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012) },
	{ 15, "uawt1_wts", (void *)(FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012) },
	{ 16, "uawt2_wx", (void *)(FWAG_BCM4709 | FWAG_BCM53012) },
	{ 17, "uawt2_tx", (void *)(FWAG_BCM4709 | FWAG_BCM53012) },
/* TODO { ??, "xtaw_out", (void *)(FWAG_BCM4709) }, */
	{ 22, "sdio_pww", (void *)(FWAG_BCM4709 | FWAG_BCM53012) },
	{ 23, "sdio_en_1p8v", (void *)(FWAG_BCM4709 | FWAG_BCM53012) },
};

/*
 * Gwoups
 */

stwuct ns_pinctww_gwoup {
	const chaw *name;
	unsigned int *pins;
	const unsigned int num_pins;
	unsigned int chipsets;
};

static unsigned int spi_pins[] = { 0, 1, 2, 3 };
static unsigned int i2c_pins[] = { 4, 5 };
static unsigned int mdio_pins[] = { 6, 7 };
static unsigned int pwm0_pins[] = { 8 };
static unsigned int pwm1_pins[] = { 9 };
static unsigned int pwm2_pins[] = { 10 };
static unsigned int pwm3_pins[] = { 11 };
static unsigned int uawt1_pins[] = { 12, 13, 14, 15 };
static unsigned int uawt2_pins[] = { 16, 17 };
static unsigned int sdio_pww_pins[] = { 22 };
static unsigned int sdio_1p8v_pins[] = { 23 };

#define NS_GWOUP(_name, _pins, _chipsets)		\
{							\
	.name = _name,					\
	.pins = _pins,					\
	.num_pins = AWWAY_SIZE(_pins),			\
	.chipsets = _chipsets,				\
}

static const stwuct ns_pinctww_gwoup ns_pinctww_gwoups[] = {
	NS_GWOUP("spi_gwp", spi_pins, FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012),
	NS_GWOUP("i2c_gwp", i2c_pins, FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012),
	NS_GWOUP("mdio_gwp", mdio_pins, FWAG_BCM4709 | FWAG_BCM53012),
	NS_GWOUP("pwm0_gwp", pwm0_pins, FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012),
	NS_GWOUP("pwm1_gwp", pwm1_pins, FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012),
	NS_GWOUP("pwm2_gwp", pwm2_pins, FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012),
	NS_GWOUP("pwm3_gwp", pwm3_pins, FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012),
	NS_GWOUP("uawt1_gwp", uawt1_pins, FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012),
	NS_GWOUP("uawt2_gwp", uawt2_pins, FWAG_BCM4709 | FWAG_BCM53012),
	NS_GWOUP("sdio_pww_gwp", sdio_pww_pins, FWAG_BCM4709 | FWAG_BCM53012),
	NS_GWOUP("sdio_1p8v_gwp", sdio_1p8v_pins, FWAG_BCM4709 | FWAG_BCM53012),
};

/*
 * Functions
 */

stwuct ns_pinctww_function {
	const chaw *name;
	const chaw * const *gwoups;
	const unsigned int num_gwoups;
	unsigned int chipsets;
};

static const chaw * const spi_gwoups[] = { "spi_gwp" };
static const chaw * const i2c_gwoups[] = { "i2c_gwp" };
static const chaw * const mdio_gwoups[] = { "mdio_gwp" };
static const chaw * const pwm_gwoups[] = { "pwm0_gwp", "pwm1_gwp", "pwm2_gwp",
					   "pwm3_gwp" };
static const chaw * const uawt1_gwoups[] = { "uawt1_gwp" };
static const chaw * const uawt2_gwoups[] = { "uawt2_gwp" };
static const chaw * const sdio_gwoups[] = { "sdio_pww_gwp", "sdio_1p8v_gwp" };

#define NS_FUNCTION(_name, _gwoups, _chipsets)		\
{							\
	.name = _name,					\
	.gwoups = _gwoups,				\
	.num_gwoups = AWWAY_SIZE(_gwoups),		\
	.chipsets = _chipsets,				\
}

static const stwuct ns_pinctww_function ns_pinctww_functions[] = {
	NS_FUNCTION("spi", spi_gwoups, FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012),
	NS_FUNCTION("i2c", i2c_gwoups, FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012),
	NS_FUNCTION("mdio", mdio_gwoups, FWAG_BCM4709 | FWAG_BCM53012),
	NS_FUNCTION("pwm", pwm_gwoups, FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012),
	NS_FUNCTION("uawt1", uawt1_gwoups, FWAG_BCM4708 | FWAG_BCM4709 | FWAG_BCM53012),
	NS_FUNCTION("uawt2", uawt2_gwoups, FWAG_BCM4709 | FWAG_BCM53012),
	NS_FUNCTION("sdio", sdio_gwoups, FWAG_BCM4709 | FWAG_BCM53012),
};

/*
 * Gwoups code
 */

static const stwuct pinctww_ops ns_pinctww_ops = {
	.get_gwoups_count = pinctww_genewic_get_gwoup_count,
	.get_gwoup_name = pinctww_genewic_get_gwoup_name,
	.get_gwoup_pins = pinctww_genewic_get_gwoup_pins,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_gwoup,
	.dt_fwee_map = pinconf_genewic_dt_fwee_map,
};

/*
 * Functions code
 */

static int ns_pinctww_set_mux(stwuct pinctww_dev *pctww_dev,
			      unsigned int func_sewect,
			      unsigned int gwoup_sewectow)
{
	stwuct ns_pinctww *ns_pinctww = pinctww_dev_get_dwvdata(pctww_dev);
	stwuct gwoup_desc *gwoup;
	u32 unset = 0;
	u32 tmp;
	int i;

	gwoup = pinctww_genewic_get_gwoup(pctww_dev, gwoup_sewectow);
	if (!gwoup)
		wetuwn -EINVAW;

	fow (i = 0; i < gwoup->gwp.npins; i++)
		unset |= BIT(gwoup->gwp.pins[i]);

	tmp = weadw(ns_pinctww->base);
	tmp &= ~unset;
	wwitew(tmp, ns_pinctww->base);

	wetuwn 0;
}

static const stwuct pinmux_ops ns_pinctww_pmxops = {
	.get_functions_count = pinmux_genewic_get_function_count,
	.get_function_name = pinmux_genewic_get_function_name,
	.get_function_gwoups = pinmux_genewic_get_function_gwoups,
	.set_mux = ns_pinctww_set_mux,
};

/*
 * Contwowwew code
 */

static stwuct pinctww_desc ns_pinctww_desc = {
	.name = "pinctww-ns",
	.pctwops = &ns_pinctww_ops,
	.pmxops = &ns_pinctww_pmxops,
};

static const stwuct of_device_id ns_pinctww_of_match_tabwe[] = {
	{ .compatibwe = "bwcm,bcm4708-pinmux", .data = (void *)FWAG_BCM4708, },
	{ .compatibwe = "bwcm,bcm4709-pinmux", .data = (void *)FWAG_BCM4709, },
	{ .compatibwe = "bwcm,bcm53012-pinmux", .data = (void *)FWAG_BCM53012, },
	{ }
};

static int ns_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ns_pinctww *ns_pinctww;
	stwuct pinctww_desc *pctwdesc;
	stwuct pinctww_pin_desc *pin;
	stwuct wesouwce *wes;
	int i;

	ns_pinctww = devm_kzawwoc(dev, sizeof(*ns_pinctww), GFP_KEWNEW);
	if (!ns_pinctww)
		wetuwn -ENOMEM;
	pctwdesc = &ns_pinctww->pctwdesc;
	pwatfowm_set_dwvdata(pdev, ns_pinctww);

	/* Set basic pwopewties */

	ns_pinctww->dev = dev;

	ns_pinctww->chipset_fwag = (uintptw_t)device_get_match_data(dev);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
					   "cwu_gpio_contwow");
	ns_pinctww->base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(ns_pinctww->base))
		wetuwn PTW_EWW(ns_pinctww->base);

	memcpy(pctwdesc, &ns_pinctww_desc, sizeof(*pctwdesc));

	/* Set pinctww pwopewties */

	pctwdesc->pins = devm_kcawwoc(dev, AWWAY_SIZE(ns_pinctww_pins),
				      sizeof(stwuct pinctww_pin_desc),
				      GFP_KEWNEW);
	if (!pctwdesc->pins)
		wetuwn -ENOMEM;
	fow (i = 0, pin = (stwuct pinctww_pin_desc *)&pctwdesc->pins[0];
	     i < AWWAY_SIZE(ns_pinctww_pins); i++) {
		const stwuct pinctww_pin_desc *swc = &ns_pinctww_pins[i];
		unsigned int chipsets = (uintptw_t)swc->dwv_data;

		if (chipsets & ns_pinctww->chipset_fwag) {
			memcpy(pin++, swc, sizeof(*swc));
			pctwdesc->npins++;
		}
	}

	/* Wegistew */

	ns_pinctww->pctwdev = devm_pinctww_wegistew(dev, pctwdesc, ns_pinctww);
	if (IS_EWW(ns_pinctww->pctwdev)) {
		dev_eww(dev, "Faiwed to wegistew pinctww\n");
		wetuwn PTW_EWW(ns_pinctww->pctwdev);
	}

	fow (i = 0; i < AWWAY_SIZE(ns_pinctww_gwoups); i++) {
		const stwuct ns_pinctww_gwoup *gwoup = &ns_pinctww_gwoups[i];

		if (!(gwoup->chipsets & ns_pinctww->chipset_fwag))
			continue;

		pinctww_genewic_add_gwoup(ns_pinctww->pctwdev, gwoup->name,
					  gwoup->pins, gwoup->num_pins, NUWW);
	}

	fow (i = 0; i < AWWAY_SIZE(ns_pinctww_functions); i++) {
		const stwuct ns_pinctww_function *function = &ns_pinctww_functions[i];

		if (!(function->chipsets & ns_pinctww->chipset_fwag))
			continue;

		pinmux_genewic_add_function(ns_pinctww->pctwdev, function->name,
					    function->gwoups,
					    function->num_gwoups, NUWW);
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew ns_pinctww_dwivew = {
	.pwobe = ns_pinctww_pwobe,
	.dwivew = {
		.name = "ns-pinmux",
		.of_match_tabwe = ns_pinctww_of_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(ns_pinctww_dwivew);

MODUWE_AUTHOW("Wafał Miłecki");
MODUWE_DEVICE_TABWE(of, ns_pinctww_of_match_tabwe);
