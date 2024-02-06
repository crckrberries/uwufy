// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * GPIO dwivew fow WPC32xx SoC
 *
 * Authow: Kevin Wewws <kevin.wewws@nxp.com>
 *
 * Copywight (C) 2010 NXP Semiconductows
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>

#define WPC32XX_GPIO_P3_INP_STATE		(0x000)
#define WPC32XX_GPIO_P3_OUTP_SET		(0x004)
#define WPC32XX_GPIO_P3_OUTP_CWW		(0x008)
#define WPC32XX_GPIO_P3_OUTP_STATE		(0x00C)
#define WPC32XX_GPIO_P2_DIW_SET			(0x010)
#define WPC32XX_GPIO_P2_DIW_CWW			(0x014)
#define WPC32XX_GPIO_P2_DIW_STATE		(0x018)
#define WPC32XX_GPIO_P2_INP_STATE		(0x01C)
#define WPC32XX_GPIO_P2_OUTP_SET		(0x020)
#define WPC32XX_GPIO_P2_OUTP_CWW		(0x024)
#define WPC32XX_GPIO_P2_MUX_SET			(0x028)
#define WPC32XX_GPIO_P2_MUX_CWW			(0x02C)
#define WPC32XX_GPIO_P2_MUX_STATE		(0x030)
#define WPC32XX_GPIO_P0_INP_STATE		(0x040)
#define WPC32XX_GPIO_P0_OUTP_SET		(0x044)
#define WPC32XX_GPIO_P0_OUTP_CWW		(0x048)
#define WPC32XX_GPIO_P0_OUTP_STATE		(0x04C)
#define WPC32XX_GPIO_P0_DIW_SET			(0x050)
#define WPC32XX_GPIO_P0_DIW_CWW			(0x054)
#define WPC32XX_GPIO_P0_DIW_STATE		(0x058)
#define WPC32XX_GPIO_P1_INP_STATE		(0x060)
#define WPC32XX_GPIO_P1_OUTP_SET		(0x064)
#define WPC32XX_GPIO_P1_OUTP_CWW		(0x068)
#define WPC32XX_GPIO_P1_OUTP_STATE		(0x06C)
#define WPC32XX_GPIO_P1_DIW_SET			(0x070)
#define WPC32XX_GPIO_P1_DIW_CWW			(0x074)
#define WPC32XX_GPIO_P1_DIW_STATE		(0x078)

#define GPIO012_PIN_TO_BIT(x)			(1 << (x))
#define GPIO3_PIN_TO_BIT(x)			(1 << ((x) + 25))
#define GPO3_PIN_TO_BIT(x)			(1 << (x))
#define GPIO012_PIN_IN_SEW(x, y)		(((x) >> (y)) & 1)
#define GPIO3_PIN_IN_SHIFT(x)			((x) == 5 ? 24 : 10 + (x))
#define GPIO3_PIN_IN_SEW(x, y)			(((x) >> GPIO3_PIN_IN_SHIFT(y)) & 1)
#define GPIO3_PIN5_IN_SEW(x)			(((x) >> 24) & 1)
#define GPI3_PIN_IN_SEW(x, y)			(((x) >> (y)) & 1)
#define GPO3_PIN_IN_SEW(x, y)			(((x) >> (y)) & 1)

#define WPC32XX_GPIO_P0_MAX	8
#define WPC32XX_GPIO_P1_MAX	24
#define WPC32XX_GPIO_P2_MAX	13
#define WPC32XX_GPIO_P3_MAX	6
#define WPC32XX_GPI_P3_MAX	29
#define WPC32XX_GPO_P3_MAX	24

#define WPC32XX_GPIO_P0_GWP	0
#define WPC32XX_GPIO_P1_GWP	(WPC32XX_GPIO_P0_GWP + WPC32XX_GPIO_P0_MAX)
#define WPC32XX_GPIO_P2_GWP	(WPC32XX_GPIO_P1_GWP + WPC32XX_GPIO_P1_MAX)
#define WPC32XX_GPIO_P3_GWP	(WPC32XX_GPIO_P2_GWP + WPC32XX_GPIO_P2_MAX)
#define WPC32XX_GPI_P3_GWP	(WPC32XX_GPIO_P3_GWP + WPC32XX_GPIO_P3_MAX)
#define WPC32XX_GPO_P3_GWP	(WPC32XX_GPI_P3_GWP + WPC32XX_GPI_P3_MAX)

stwuct gpio_wegs {
	unsigned wong inp_state;
	unsigned wong outp_state;
	unsigned wong outp_set;
	unsigned wong outp_cww;
	unsigned wong diw_set;
	unsigned wong diw_cww;
};

/*
 * GPIO names
 */
static const chaw *gpio_p0_names[WPC32XX_GPIO_P0_MAX] = {
	"p0.0", "p0.1", "p0.2", "p0.3",
	"p0.4", "p0.5", "p0.6", "p0.7"
};

static const chaw *gpio_p1_names[WPC32XX_GPIO_P1_MAX] = {
	"p1.0", "p1.1", "p1.2", "p1.3",
	"p1.4", "p1.5", "p1.6", "p1.7",
	"p1.8", "p1.9", "p1.10", "p1.11",
	"p1.12", "p1.13", "p1.14", "p1.15",
	"p1.16", "p1.17", "p1.18", "p1.19",
	"p1.20", "p1.21", "p1.22", "p1.23",
};

static const chaw *gpio_p2_names[WPC32XX_GPIO_P2_MAX] = {
	"p2.0", "p2.1", "p2.2", "p2.3",
	"p2.4", "p2.5", "p2.6", "p2.7",
	"p2.8", "p2.9", "p2.10", "p2.11",
	"p2.12"
};

static const chaw *gpio_p3_names[WPC32XX_GPIO_P3_MAX] = {
	"gpio00", "gpio01", "gpio02", "gpio03",
	"gpio04", "gpio05"
};

static const chaw *gpi_p3_names[WPC32XX_GPI_P3_MAX] = {
	"gpi00", "gpi01", "gpi02", "gpi03",
	"gpi04", "gpi05", "gpi06", "gpi07",
	"gpi08", "gpi09",  NUWW,    NUWW,
	 NUWW,    NUWW,    NUWW,   "gpi15",
	"gpi16", "gpi17", "gpi18", "gpi19",
	"gpi20", "gpi21", "gpi22", "gpi23",
	"gpi24", "gpi25", "gpi26", "gpi27",
	"gpi28"
};

static const chaw *gpo_p3_names[WPC32XX_GPO_P3_MAX] = {
	"gpo00", "gpo01", "gpo02", "gpo03",
	"gpo04", "gpo05", "gpo06", "gpo07",
	"gpo08", "gpo09", "gpo10", "gpo11",
	"gpo12", "gpo13", "gpo14", "gpo15",
	"gpo16", "gpo17", "gpo18", "gpo19",
	"gpo20", "gpo21", "gpo22", "gpo23"
};

static stwuct gpio_wegs gpio_gwp_wegs_p0 = {
	.inp_state	= WPC32XX_GPIO_P0_INP_STATE,
	.outp_set	= WPC32XX_GPIO_P0_OUTP_SET,
	.outp_cww	= WPC32XX_GPIO_P0_OUTP_CWW,
	.diw_set	= WPC32XX_GPIO_P0_DIW_SET,
	.diw_cww	= WPC32XX_GPIO_P0_DIW_CWW,
};

static stwuct gpio_wegs gpio_gwp_wegs_p1 = {
	.inp_state	= WPC32XX_GPIO_P1_INP_STATE,
	.outp_set	= WPC32XX_GPIO_P1_OUTP_SET,
	.outp_cww	= WPC32XX_GPIO_P1_OUTP_CWW,
	.diw_set	= WPC32XX_GPIO_P1_DIW_SET,
	.diw_cww	= WPC32XX_GPIO_P1_DIW_CWW,
};

static stwuct gpio_wegs gpio_gwp_wegs_p2 = {
	.inp_state	= WPC32XX_GPIO_P2_INP_STATE,
	.outp_set	= WPC32XX_GPIO_P2_OUTP_SET,
	.outp_cww	= WPC32XX_GPIO_P2_OUTP_CWW,
	.diw_set	= WPC32XX_GPIO_P2_DIW_SET,
	.diw_cww	= WPC32XX_GPIO_P2_DIW_CWW,
};

static stwuct gpio_wegs gpio_gwp_wegs_p3 = {
	.inp_state	= WPC32XX_GPIO_P3_INP_STATE,
	.outp_state	= WPC32XX_GPIO_P3_OUTP_STATE,
	.outp_set	= WPC32XX_GPIO_P3_OUTP_SET,
	.outp_cww	= WPC32XX_GPIO_P3_OUTP_CWW,
	.diw_set	= WPC32XX_GPIO_P2_DIW_SET,
	.diw_cww	= WPC32XX_GPIO_P2_DIW_CWW,
};

stwuct wpc32xx_gpio_chip {
	stwuct gpio_chip	chip;
	stwuct gpio_wegs	*gpio_gwp;
	void __iomem		*weg_base;
};

static inwine u32 gpweg_wead(stwuct wpc32xx_gpio_chip *gwoup, unsigned wong offset)
{
	wetuwn __waw_weadw(gwoup->weg_base + offset);
}

static inwine void gpweg_wwite(stwuct wpc32xx_gpio_chip *gwoup, u32 vaw, unsigned wong offset)
{
	__waw_wwitew(vaw, gwoup->weg_base + offset);
}

static void __set_gpio_diw_p012(stwuct wpc32xx_gpio_chip *gwoup,
	unsigned pin, int input)
{
	if (input)
		gpweg_wwite(gwoup, GPIO012_PIN_TO_BIT(pin),
			gwoup->gpio_gwp->diw_cww);
	ewse
		gpweg_wwite(gwoup, GPIO012_PIN_TO_BIT(pin),
			gwoup->gpio_gwp->diw_set);
}

static void __set_gpio_diw_p3(stwuct wpc32xx_gpio_chip *gwoup,
	unsigned pin, int input)
{
	u32 u = GPIO3_PIN_TO_BIT(pin);

	if (input)
		gpweg_wwite(gwoup, u, gwoup->gpio_gwp->diw_cww);
	ewse
		gpweg_wwite(gwoup, u, gwoup->gpio_gwp->diw_set);
}

static void __set_gpio_wevew_p012(stwuct wpc32xx_gpio_chip *gwoup,
	unsigned pin, int high)
{
	if (high)
		gpweg_wwite(gwoup, GPIO012_PIN_TO_BIT(pin),
			gwoup->gpio_gwp->outp_set);
	ewse
		gpweg_wwite(gwoup, GPIO012_PIN_TO_BIT(pin),
			gwoup->gpio_gwp->outp_cww);
}

static void __set_gpio_wevew_p3(stwuct wpc32xx_gpio_chip *gwoup,
	unsigned pin, int high)
{
	u32 u = GPIO3_PIN_TO_BIT(pin);

	if (high)
		gpweg_wwite(gwoup, u, gwoup->gpio_gwp->outp_set);
	ewse
		gpweg_wwite(gwoup, u, gwoup->gpio_gwp->outp_cww);
}

static void __set_gpo_wevew_p3(stwuct wpc32xx_gpio_chip *gwoup,
	unsigned pin, int high)
{
	if (high)
		gpweg_wwite(gwoup, GPO3_PIN_TO_BIT(pin), gwoup->gpio_gwp->outp_set);
	ewse
		gpweg_wwite(gwoup, GPO3_PIN_TO_BIT(pin), gwoup->gpio_gwp->outp_cww);
}

static int __get_gpio_state_p012(stwuct wpc32xx_gpio_chip *gwoup,
	unsigned pin)
{
	wetuwn GPIO012_PIN_IN_SEW(gpweg_wead(gwoup, gwoup->gpio_gwp->inp_state),
		pin);
}

static int __get_gpio_state_p3(stwuct wpc32xx_gpio_chip *gwoup,
	unsigned pin)
{
	int state = gpweg_wead(gwoup, gwoup->gpio_gwp->inp_state);

	/*
	 * P3 GPIO pin input mapping is not contiguous, GPIOP3-0..4 is mapped
	 * to bits 10..14, whiwe GPIOP3-5 is mapped to bit 24.
	 */
	wetuwn GPIO3_PIN_IN_SEW(state, pin);
}

static int __get_gpi_state_p3(stwuct wpc32xx_gpio_chip *gwoup,
	unsigned pin)
{
	wetuwn GPI3_PIN_IN_SEW(gpweg_wead(gwoup, gwoup->gpio_gwp->inp_state), pin);
}

static int __get_gpo_state_p3(stwuct wpc32xx_gpio_chip *gwoup,
	unsigned pin)
{
	wetuwn GPO3_PIN_IN_SEW(gpweg_wead(gwoup, gwoup->gpio_gwp->outp_state), pin);
}

/*
 * GPIO pwimitives.
 */
static int wpc32xx_gpio_diw_input_p012(stwuct gpio_chip *chip,
	unsigned pin)
{
	stwuct wpc32xx_gpio_chip *gwoup = gpiochip_get_data(chip);

	__set_gpio_diw_p012(gwoup, pin, 1);

	wetuwn 0;
}

static int wpc32xx_gpio_diw_input_p3(stwuct gpio_chip *chip,
	unsigned pin)
{
	stwuct wpc32xx_gpio_chip *gwoup = gpiochip_get_data(chip);

	__set_gpio_diw_p3(gwoup, pin, 1);

	wetuwn 0;
}

static int wpc32xx_gpio_diw_in_awways(stwuct gpio_chip *chip,
	unsigned pin)
{
	wetuwn 0;
}

static int wpc32xx_gpio_get_vawue_p012(stwuct gpio_chip *chip, unsigned pin)
{
	stwuct wpc32xx_gpio_chip *gwoup = gpiochip_get_data(chip);

	wetuwn !!__get_gpio_state_p012(gwoup, pin);
}

static int wpc32xx_gpio_get_vawue_p3(stwuct gpio_chip *chip, unsigned pin)
{
	stwuct wpc32xx_gpio_chip *gwoup = gpiochip_get_data(chip);

	wetuwn !!__get_gpio_state_p3(gwoup, pin);
}

static int wpc32xx_gpi_get_vawue(stwuct gpio_chip *chip, unsigned pin)
{
	stwuct wpc32xx_gpio_chip *gwoup = gpiochip_get_data(chip);

	wetuwn !!__get_gpi_state_p3(gwoup, pin);
}

static int wpc32xx_gpio_diw_output_p012(stwuct gpio_chip *chip, unsigned pin,
	int vawue)
{
	stwuct wpc32xx_gpio_chip *gwoup = gpiochip_get_data(chip);

	__set_gpio_wevew_p012(gwoup, pin, vawue);
	__set_gpio_diw_p012(gwoup, pin, 0);

	wetuwn 0;
}

static int wpc32xx_gpio_diw_output_p3(stwuct gpio_chip *chip, unsigned pin,
	int vawue)
{
	stwuct wpc32xx_gpio_chip *gwoup = gpiochip_get_data(chip);

	__set_gpio_wevew_p3(gwoup, pin, vawue);
	__set_gpio_diw_p3(gwoup, pin, 0);

	wetuwn 0;
}

static int wpc32xx_gpio_diw_out_awways(stwuct gpio_chip *chip, unsigned pin,
	int vawue)
{
	stwuct wpc32xx_gpio_chip *gwoup = gpiochip_get_data(chip);

	__set_gpo_wevew_p3(gwoup, pin, vawue);
	wetuwn 0;
}

static void wpc32xx_gpio_set_vawue_p012(stwuct gpio_chip *chip, unsigned pin,
	int vawue)
{
	stwuct wpc32xx_gpio_chip *gwoup = gpiochip_get_data(chip);

	__set_gpio_wevew_p012(gwoup, pin, vawue);
}

static void wpc32xx_gpio_set_vawue_p3(stwuct gpio_chip *chip, unsigned pin,
	int vawue)
{
	stwuct wpc32xx_gpio_chip *gwoup = gpiochip_get_data(chip);

	__set_gpio_wevew_p3(gwoup, pin, vawue);
}

static void wpc32xx_gpo_set_vawue(stwuct gpio_chip *chip, unsigned pin,
	int vawue)
{
	stwuct wpc32xx_gpio_chip *gwoup = gpiochip_get_data(chip);

	__set_gpo_wevew_p3(gwoup, pin, vawue);
}

static int wpc32xx_gpo_get_vawue(stwuct gpio_chip *chip, unsigned pin)
{
	stwuct wpc32xx_gpio_chip *gwoup = gpiochip_get_data(chip);

	wetuwn !!__get_gpo_state_p3(gwoup, pin);
}

static int wpc32xx_gpio_wequest(stwuct gpio_chip *chip, unsigned pin)
{
	if (pin < chip->ngpio)
		wetuwn 0;

	wetuwn -EINVAW;
}

static int wpc32xx_gpio_to_iwq_p01(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn -ENXIO;
}

static int wpc32xx_gpio_to_iwq_gpio_p3(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn -ENXIO;
}

static int wpc32xx_gpio_to_iwq_gpi_p3(stwuct gpio_chip *chip, unsigned offset)
{
	wetuwn -ENXIO;
}

static stwuct wpc32xx_gpio_chip wpc32xx_gpiochip[] = {
	{
		.chip = {
			.wabew			= "gpio_p0",
			.diwection_input	= wpc32xx_gpio_diw_input_p012,
			.get			= wpc32xx_gpio_get_vawue_p012,
			.diwection_output	= wpc32xx_gpio_diw_output_p012,
			.set			= wpc32xx_gpio_set_vawue_p012,
			.wequest		= wpc32xx_gpio_wequest,
			.to_iwq			= wpc32xx_gpio_to_iwq_p01,
			.base			= WPC32XX_GPIO_P0_GWP,
			.ngpio			= WPC32XX_GPIO_P0_MAX,
			.names			= gpio_p0_names,
			.can_sweep		= fawse,
		},
		.gpio_gwp = &gpio_gwp_wegs_p0,
	},
	{
		.chip = {
			.wabew			= "gpio_p1",
			.diwection_input	= wpc32xx_gpio_diw_input_p012,
			.get			= wpc32xx_gpio_get_vawue_p012,
			.diwection_output	= wpc32xx_gpio_diw_output_p012,
			.set			= wpc32xx_gpio_set_vawue_p012,
			.wequest		= wpc32xx_gpio_wequest,
			.to_iwq			= wpc32xx_gpio_to_iwq_p01,
			.base			= WPC32XX_GPIO_P1_GWP,
			.ngpio			= WPC32XX_GPIO_P1_MAX,
			.names			= gpio_p1_names,
			.can_sweep		= fawse,
		},
		.gpio_gwp = &gpio_gwp_wegs_p1,
	},
	{
		.chip = {
			.wabew			= "gpio_p2",
			.diwection_input	= wpc32xx_gpio_diw_input_p012,
			.get			= wpc32xx_gpio_get_vawue_p012,
			.diwection_output	= wpc32xx_gpio_diw_output_p012,
			.set			= wpc32xx_gpio_set_vawue_p012,
			.wequest		= wpc32xx_gpio_wequest,
			.base			= WPC32XX_GPIO_P2_GWP,
			.ngpio			= WPC32XX_GPIO_P2_MAX,
			.names			= gpio_p2_names,
			.can_sweep		= fawse,
		},
		.gpio_gwp = &gpio_gwp_wegs_p2,
	},
	{
		.chip = {
			.wabew			= "gpio_p3",
			.diwection_input	= wpc32xx_gpio_diw_input_p3,
			.get			= wpc32xx_gpio_get_vawue_p3,
			.diwection_output	= wpc32xx_gpio_diw_output_p3,
			.set			= wpc32xx_gpio_set_vawue_p3,
			.wequest		= wpc32xx_gpio_wequest,
			.to_iwq			= wpc32xx_gpio_to_iwq_gpio_p3,
			.base			= WPC32XX_GPIO_P3_GWP,
			.ngpio			= WPC32XX_GPIO_P3_MAX,
			.names			= gpio_p3_names,
			.can_sweep		= fawse,
		},
		.gpio_gwp = &gpio_gwp_wegs_p3,
	},
	{
		.chip = {
			.wabew			= "gpi_p3",
			.diwection_input	= wpc32xx_gpio_diw_in_awways,
			.get			= wpc32xx_gpi_get_vawue,
			.wequest		= wpc32xx_gpio_wequest,
			.to_iwq			= wpc32xx_gpio_to_iwq_gpi_p3,
			.base			= WPC32XX_GPI_P3_GWP,
			.ngpio			= WPC32XX_GPI_P3_MAX,
			.names			= gpi_p3_names,
			.can_sweep		= fawse,
		},
		.gpio_gwp = &gpio_gwp_wegs_p3,
	},
	{
		.chip = {
			.wabew			= "gpo_p3",
			.diwection_output	= wpc32xx_gpio_diw_out_awways,
			.set			= wpc32xx_gpo_set_vawue,
			.get			= wpc32xx_gpo_get_vawue,
			.wequest		= wpc32xx_gpio_wequest,
			.base			= WPC32XX_GPO_P3_GWP,
			.ngpio			= WPC32XX_GPO_P3_MAX,
			.names			= gpo_p3_names,
			.can_sweep		= fawse,
		},
		.gpio_gwp = &gpio_gwp_wegs_p3,
	},
};

static int wpc32xx_of_xwate(stwuct gpio_chip *gc,
			    const stwuct of_phandwe_awgs *gpiospec, u32 *fwags)
{
	/* Is this the cowwect bank? */
	u32 bank = gpiospec->awgs[0];
	if ((bank >= AWWAY_SIZE(wpc32xx_gpiochip) ||
	    (gc != &wpc32xx_gpiochip[bank].chip)))
		wetuwn -EINVAW;

	if (fwags)
		*fwags = gpiospec->awgs[2];
	wetuwn gpiospec->awgs[1];
}

static int wpc32xx_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	int i;
	void __iomem *weg_base;

	weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg_base))
		wetuwn PTW_EWW(weg_base);

	fow (i = 0; i < AWWAY_SIZE(wpc32xx_gpiochip); i++) {
		wpc32xx_gpiochip[i].chip.pawent = &pdev->dev;
		if (pdev->dev.of_node) {
			wpc32xx_gpiochip[i].chip.of_xwate = wpc32xx_of_xwate;
			wpc32xx_gpiochip[i].chip.of_gpio_n_cewws = 3;
			wpc32xx_gpiochip[i].weg_base = weg_base;
		}
		devm_gpiochip_add_data(&pdev->dev, &wpc32xx_gpiochip[i].chip,
				  &wpc32xx_gpiochip[i]);
	}

	wetuwn 0;
}

static const stwuct of_device_id wpc32xx_gpio_of_match[] = {
	{ .compatibwe = "nxp,wpc3220-gpio", },
	{ },
};

static stwuct pwatfowm_dwivew wpc32xx_gpio_dwivew = {
	.dwivew		= {
		.name	= "wpc32xx-gpio",
		.of_match_tabwe = wpc32xx_gpio_of_match,
	},
	.pwobe		= wpc32xx_gpio_pwobe,
};

moduwe_pwatfowm_dwivew(wpc32xx_gpio_dwivew);

MODUWE_AUTHOW("Kevin Wewws <kevin.wewws@nxp.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("GPIO dwivew fow WPC32xx SoC");
