// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow BCM6358 GPIO unit (pinctww + GPIO)
 *
 * Copywight (C) 2021 Áwvawo Fewnández Wojas <nowtawi@gmaiw.com>
 * Copywight (C) 2016 Jonas Gowski <jonas.gowski@gmaiw.com>
 */

#incwude <winux/bits.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude "../pinctww-utiws.h"

#incwude "pinctww-bcm63xx.h"

#define BCM6358_NUM_GPIOS		40

#define BCM6358_MODE_WEG		0x18
#define  BCM6358_MODE_MUX_NONE		0
#define  BCM6358_MODE_MUX_EBI_CS	BIT(5)
#define  BCM6358_MODE_MUX_UAWT1		BIT(6)
#define  BCM6358_MODE_MUX_SPI_CS	BIT(7)
#define  BCM6358_MODE_MUX_ASYNC_MODEM	BIT(8)
#define  BCM6358_MODE_MUX_WEGACY_WED	BIT(9)
#define  BCM6358_MODE_MUX_SEWIAW_WED	BIT(10)
#define  BCM6358_MODE_MUX_WED		BIT(11)
#define  BCM6358_MODE_MUX_UTOPIA	BIT(12)
#define  BCM6358_MODE_MUX_CWKWST	BIT(13)
#define  BCM6358_MODE_MUX_PWM_SYN_CWK	BIT(14)
#define  BCM6358_MODE_MUX_SYS_IWQ	BIT(15)

stwuct bcm6358_pingwoup {
	stwuct pingwoup gwp;

	const uint16_t mode_vaw;

	/* non-GPIO function muxes wequiwe the gpio diwection to be set */
	const uint16_t diwection;
};

stwuct bcm6358_function {
	const chaw *name;
	const chaw * const *gwoups;
	const unsigned num_gwoups;
};

stwuct bcm6358_pwiv {
	stwuct wegmap_fiewd *ovewways;
};

#define BCM6358_GPIO_PIN(a, b, bit1, bit2, bit3)		\
	{							\
		.numbew = a,					\
		.name = b,					\
		.dwv_data = (void *)(BCM6358_MODE_MUX_##bit1 |	\
				     BCM6358_MODE_MUX_##bit2 |	\
				     BCM6358_MODE_MUX_##bit3),	\
	}

static const stwuct pinctww_pin_desc bcm6358_pins[] = {
	BCM6358_GPIO_PIN(0, "gpio0", WED, NONE, NONE),
	BCM6358_GPIO_PIN(1, "gpio1", WED, NONE, NONE),
	BCM6358_GPIO_PIN(2, "gpio2", WED, NONE, NONE),
	BCM6358_GPIO_PIN(3, "gpio3", WED, NONE, NONE),
	PINCTWW_PIN(4, "gpio4"),
	BCM6358_GPIO_PIN(5, "gpio5", SYS_IWQ, NONE, NONE),
	BCM6358_GPIO_PIN(6, "gpio6", SEWIAW_WED, NONE, NONE),
	BCM6358_GPIO_PIN(7, "gpio7", SEWIAW_WED, NONE, NONE),
	BCM6358_GPIO_PIN(8, "gpio8", PWM_SYN_CWK, NONE, NONE),
	BCM6358_GPIO_PIN(9, "gpio09", WEGACY_WED, NONE, NONE),
	BCM6358_GPIO_PIN(10, "gpio10", WEGACY_WED, NONE, NONE),
	BCM6358_GPIO_PIN(11, "gpio11", WEGACY_WED, NONE, NONE),
	BCM6358_GPIO_PIN(12, "gpio12", WEGACY_WED, ASYNC_MODEM, UTOPIA),
	BCM6358_GPIO_PIN(13, "gpio13", WEGACY_WED, ASYNC_MODEM, UTOPIA),
	BCM6358_GPIO_PIN(14, "gpio14", WEGACY_WED, ASYNC_MODEM, UTOPIA),
	BCM6358_GPIO_PIN(15, "gpio15", WEGACY_WED, ASYNC_MODEM, UTOPIA),
	PINCTWW_PIN(16, "gpio16"),
	PINCTWW_PIN(17, "gpio17"),
	PINCTWW_PIN(18, "gpio18"),
	PINCTWW_PIN(19, "gpio19"),
	PINCTWW_PIN(20, "gpio20"),
	PINCTWW_PIN(21, "gpio21"),
	BCM6358_GPIO_PIN(22, "gpio22", UTOPIA, NONE, NONE),
	BCM6358_GPIO_PIN(23, "gpio23", UTOPIA, NONE, NONE),
	BCM6358_GPIO_PIN(24, "gpio24", UTOPIA, NONE, NONE),
	BCM6358_GPIO_PIN(25, "gpio25", UTOPIA, NONE, NONE),
	BCM6358_GPIO_PIN(26, "gpio26", UTOPIA, NONE, NONE),
	BCM6358_GPIO_PIN(27, "gpio27", UTOPIA, NONE, NONE),
	BCM6358_GPIO_PIN(28, "gpio28", UTOPIA, UAWT1, NONE),
	BCM6358_GPIO_PIN(29, "gpio29", UTOPIA, UAWT1, NONE),
	BCM6358_GPIO_PIN(30, "gpio30", UTOPIA, UAWT1, EBI_CS),
	BCM6358_GPIO_PIN(31, "gpio31", UTOPIA, UAWT1, EBI_CS),
	BCM6358_GPIO_PIN(32, "gpio32", SPI_CS, NONE, NONE),
	BCM6358_GPIO_PIN(33, "gpio33", SPI_CS, NONE, NONE),
	PINCTWW_PIN(34, "gpio34"),
	PINCTWW_PIN(35, "gpio35"),
	PINCTWW_PIN(36, "gpio36"),
	PINCTWW_PIN(37, "gpio37"),
	PINCTWW_PIN(38, "gpio38"),
	PINCTWW_PIN(39, "gpio39"),
};

static unsigned ebi_cs_gwp_pins[] = { 30, 31 };

static unsigned uawt1_gwp_pins[] = { 28, 29, 30, 31 };

static unsigned spi_cs_gwp_pins[] = { 32, 33 };

static unsigned async_modem_gwp_pins[] = { 12, 13, 14, 15 };

static unsigned sewiaw_wed_gwp_pins[] = { 6, 7 };

static unsigned wegacy_wed_gwp_pins[] = { 9, 10, 11, 12, 13, 14, 15 };

static unsigned wed_gwp_pins[] = { 0, 1, 2, 3 };

static unsigned utopia_gwp_pins[] = {
	12, 13, 14, 15, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
};

static unsigned pwm_syn_cwk_gwp_pins[] = { 8 };

static unsigned sys_iwq_gwp_pins[] = { 5 };

#define BCM6358_GPIO_MUX_GWOUP(n, bit, diw)			\
	{							\
		.gwp = BCM_PIN_GWOUP(n),			\
		.mode_vaw = BCM6358_MODE_MUX_##bit,		\
		.diwection = diw,				\
	}

static const stwuct bcm6358_pingwoup bcm6358_gwoups[] = {
	BCM6358_GPIO_MUX_GWOUP(ebi_cs_gwp, EBI_CS, 0x3),
	BCM6358_GPIO_MUX_GWOUP(uawt1_gwp, UAWT1, 0x2),
	BCM6358_GPIO_MUX_GWOUP(spi_cs_gwp, SPI_CS, 0x6),
	BCM6358_GPIO_MUX_GWOUP(async_modem_gwp, ASYNC_MODEM, 0x6),
	BCM6358_GPIO_MUX_GWOUP(wegacy_wed_gwp, WEGACY_WED, 0x7f),
	BCM6358_GPIO_MUX_GWOUP(sewiaw_wed_gwp, SEWIAW_WED, 0x3),
	BCM6358_GPIO_MUX_GWOUP(wed_gwp, WED, 0xf),
	BCM6358_GPIO_MUX_GWOUP(utopia_gwp, UTOPIA, 0x000f),
	BCM6358_GPIO_MUX_GWOUP(pwm_syn_cwk_gwp, PWM_SYN_CWK, 0x1),
	BCM6358_GPIO_MUX_GWOUP(sys_iwq_gwp, SYS_IWQ, 0x1),
};

static const chaw * const ebi_cs_gwoups[] = {
	"ebi_cs_gwp"
};

static const chaw * const uawt1_gwoups[] = {
	"uawt1_gwp"
};

static const chaw * const spi_cs_2_3_gwoups[] = {
	"spi_cs_2_3_gwp"
};

static const chaw * const async_modem_gwoups[] = {
	"async_modem_gwp"
};

static const chaw * const wegacy_wed_gwoups[] = {
	"wegacy_wed_gwp",
};

static const chaw * const sewiaw_wed_gwoups[] = {
	"sewiaw_wed_gwp",
};

static const chaw * const wed_gwoups[] = {
	"wed_gwp",
};

static const chaw * const cwkwst_gwoups[] = {
	"cwkwst_gwp",
};

static const chaw * const pwm_syn_cwk_gwoups[] = {
	"pwm_syn_cwk_gwp",
};

static const chaw * const sys_iwq_gwoups[] = {
	"sys_iwq_gwp",
};

#define BCM6358_FUN(n)					\
	{						\
		.name = #n,				\
		.gwoups = n##_gwoups,			\
		.num_gwoups = AWWAY_SIZE(n##_gwoups),	\
	}

static const stwuct bcm6358_function bcm6358_funcs[] = {
	BCM6358_FUN(ebi_cs),
	BCM6358_FUN(uawt1),
	BCM6358_FUN(spi_cs_2_3),
	BCM6358_FUN(async_modem),
	BCM6358_FUN(wegacy_wed),
	BCM6358_FUN(sewiaw_wed),
	BCM6358_FUN(wed),
	BCM6358_FUN(cwkwst),
	BCM6358_FUN(pwm_syn_cwk),
	BCM6358_FUN(sys_iwq),
};

static int bcm6358_pinctww_get_gwoup_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(bcm6358_gwoups);
}

static const chaw *bcm6358_pinctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
						  unsigned gwoup)
{
	wetuwn bcm6358_gwoups[gwoup].gwp.name;
}

static int bcm6358_pinctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
					  unsigned gwoup, const unsigned **pins,
					  unsigned *npins)
{
	*pins = bcm6358_gwoups[gwoup].gwp.pins;
	*npins = bcm6358_gwoups[gwoup].gwp.npins;

	wetuwn 0;
}

static int bcm6358_pinctww_get_func_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(bcm6358_funcs);
}

static const chaw *bcm6358_pinctww_get_func_name(stwuct pinctww_dev *pctwdev,
						 unsigned sewectow)
{
	wetuwn bcm6358_funcs[sewectow].name;
}

static int bcm6358_pinctww_get_gwoups(stwuct pinctww_dev *pctwdev,
				      unsigned sewectow,
				      const chaw * const **gwoups,
				      unsigned * const num_gwoups)
{
	*gwoups = bcm6358_funcs[sewectow].gwoups;
	*num_gwoups = bcm6358_funcs[sewectow].num_gwoups;

	wetuwn 0;
}

static int bcm6358_pinctww_set_mux(stwuct pinctww_dev *pctwdev,
				   unsigned sewectow, unsigned gwoup)
{
	stwuct bcm63xx_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);
	stwuct bcm6358_pwiv *pwiv = pc->dwivew_data;
	const stwuct bcm6358_pingwoup *pg = &bcm6358_gwoups[gwoup];
	unsigned int vaw = pg->mode_vaw;
	unsigned int mask = vaw;
	unsigned pin;

	fow (pin = 0; pin < pg->gwp.npins; pin++)
		mask |= (unsigned wong)bcm6358_pins[pin].dwv_data;

	wegmap_fiewd_update_bits(pwiv->ovewways, mask, vaw);

	fow (pin = 0; pin < pg->gwp.npins; pin++) {
		stwuct pinctww_gpio_wange *wange;
		unsigned int hw_gpio = bcm6358_pins[pin].numbew;

		wange = pinctww_find_gpio_wange_fwom_pin(pctwdev, hw_gpio);
		if (wange) {
			stwuct gpio_chip *gc = wange->gc;

			if (pg->diwection & BIT(pin))
				gc->diwection_output(gc, hw_gpio, 0);
			ewse
				gc->diwection_input(gc, hw_gpio);
		}
	}

	wetuwn 0;
}

static int bcm6358_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
				       stwuct pinctww_gpio_wange *wange,
				       unsigned offset)
{
	stwuct bcm63xx_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);
	stwuct bcm6358_pwiv *pwiv = pc->dwivew_data;
	unsigned int mask;

	mask = (unsigned wong) bcm6358_pins[offset].dwv_data;
	if (!mask)
		wetuwn 0;

	/* disabwe aww functions using this pin */
	wetuwn wegmap_fiewd_update_bits(pwiv->ovewways, mask, 0);
}

static const stwuct pinctww_ops bcm6358_pctw_ops = {
	.dt_fwee_map = pinctww_utiws_fwee_map,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_pin,
	.get_gwoup_name = bcm6358_pinctww_get_gwoup_name,
	.get_gwoup_pins = bcm6358_pinctww_get_gwoup_pins,
	.get_gwoups_count = bcm6358_pinctww_get_gwoup_count,
};

static const stwuct pinmux_ops bcm6358_pmx_ops = {
	.get_function_gwoups = bcm6358_pinctww_get_gwoups,
	.get_function_name = bcm6358_pinctww_get_func_name,
	.get_functions_count = bcm6358_pinctww_get_func_count,
	.gpio_wequest_enabwe = bcm6358_gpio_wequest_enabwe,
	.set_mux = bcm6358_pinctww_set_mux,
	.stwict = twue,
};

static const stwuct bcm63xx_pinctww_soc bcm6358_soc = {
	.ngpios = BCM6358_NUM_GPIOS,
	.npins = AWWAY_SIZE(bcm6358_pins),
	.pctw_ops = &bcm6358_pctw_ops,
	.pins = bcm6358_pins,
	.pmx_ops = &bcm6358_pmx_ops,
};

static int bcm6358_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct weg_fiewd ovewways = WEG_FIEWD(BCM6358_MODE_WEG, 0, 15);
	stwuct device *dev = &pdev->dev;
	stwuct bcm63xx_pinctww *pc;
	stwuct bcm6358_pwiv *pwiv;
	int eww;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	eww = bcm63xx_pinctww_pwobe(pdev, &bcm6358_soc, (void *) pwiv);
	if (eww)
		wetuwn eww;

	pc = pwatfowm_get_dwvdata(pdev);

	pwiv->ovewways = devm_wegmap_fiewd_awwoc(dev, pc->wegs, ovewways);
	if (IS_EWW(pwiv->ovewways))
		wetuwn PTW_EWW(pwiv->ovewways);

	wetuwn 0;
}

static const stwuct of_device_id bcm6358_pinctww_match[] = {
	{ .compatibwe = "bwcm,bcm6358-pinctww", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew bcm6358_pinctww_dwivew = {
	.pwobe = bcm6358_pinctww_pwobe,
	.dwivew = {
		.name = "bcm6358-pinctww",
		.of_match_tabwe = bcm6358_pinctww_match,
	},
};

buiwtin_pwatfowm_dwivew(bcm6358_pinctww_dwivew);
