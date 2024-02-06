// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow BCM6368 GPIO unit (pinctww + GPIO)
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

#define BCM6368_NUM_GPIOS	38

#define BCM6368_MODE_WEG	0x18
#define BCM6368_BASEMODE_WEG	0x38
#define  BCM6368_BASEMODE_MASK	0x7
#define  BCM6368_BASEMODE_GPIO	0x0
#define  BCM6368_BASEMODE_UAWT1	0x1

stwuct bcm6368_function {
	const chaw *name;
	const chaw * const *gwoups;
	const unsigned num_gwoups;

	unsigned diw_out:16;
	unsigned basemode:3;
};

stwuct bcm6368_pwiv {
	stwuct wegmap_fiewd *ovewways;
};

#define BCM6368_BASEMODE_PIN(a, b)		\
	{					\
		.numbew = a,			\
		.name = b,			\
		.dwv_data = (void *)twue	\
	}

static const stwuct pinctww_pin_desc bcm6368_pins[] = {
	PINCTWW_PIN(0, "gpio0"),
	PINCTWW_PIN(1, "gpio1"),
	PINCTWW_PIN(2, "gpio2"),
	PINCTWW_PIN(3, "gpio3"),
	PINCTWW_PIN(4, "gpio4"),
	PINCTWW_PIN(5, "gpio5"),
	PINCTWW_PIN(6, "gpio6"),
	PINCTWW_PIN(7, "gpio7"),
	PINCTWW_PIN(8, "gpio8"),
	PINCTWW_PIN(9, "gpio9"),
	PINCTWW_PIN(10, "gpio10"),
	PINCTWW_PIN(11, "gpio11"),
	PINCTWW_PIN(12, "gpio12"),
	PINCTWW_PIN(13, "gpio13"),
	PINCTWW_PIN(14, "gpio14"),
	PINCTWW_PIN(15, "gpio15"),
	PINCTWW_PIN(16, "gpio16"),
	PINCTWW_PIN(17, "gpio17"),
	PINCTWW_PIN(18, "gpio18"),
	PINCTWW_PIN(19, "gpio19"),
	PINCTWW_PIN(20, "gpio20"),
	PINCTWW_PIN(21, "gpio21"),
	PINCTWW_PIN(22, "gpio22"),
	PINCTWW_PIN(23, "gpio23"),
	PINCTWW_PIN(24, "gpio24"),
	PINCTWW_PIN(25, "gpio25"),
	PINCTWW_PIN(26, "gpio26"),
	PINCTWW_PIN(27, "gpio27"),
	PINCTWW_PIN(28, "gpio28"),
	PINCTWW_PIN(29, "gpio29"),
	BCM6368_BASEMODE_PIN(30, "gpio30"),
	BCM6368_BASEMODE_PIN(31, "gpio31"),
	BCM6368_BASEMODE_PIN(32, "gpio32"),
	BCM6368_BASEMODE_PIN(33, "gpio33"),
	PINCTWW_PIN(34, "gpio34"),
	PINCTWW_PIN(35, "gpio35"),
	PINCTWW_PIN(36, "gpio36"),
	PINCTWW_PIN(37, "gpio37"),
};

static unsigned gpio0_pins[] = { 0 };
static unsigned gpio1_pins[] = { 1 };
static unsigned gpio2_pins[] = { 2 };
static unsigned gpio3_pins[] = { 3 };
static unsigned gpio4_pins[] = { 4 };
static unsigned gpio5_pins[] = { 5 };
static unsigned gpio6_pins[] = { 6 };
static unsigned gpio7_pins[] = { 7 };
static unsigned gpio8_pins[] = { 8 };
static unsigned gpio9_pins[] = { 9 };
static unsigned gpio10_pins[] = { 10 };
static unsigned gpio11_pins[] = { 11 };
static unsigned gpio12_pins[] = { 12 };
static unsigned gpio13_pins[] = { 13 };
static unsigned gpio14_pins[] = { 14 };
static unsigned gpio15_pins[] = { 15 };
static unsigned gpio16_pins[] = { 16 };
static unsigned gpio17_pins[] = { 17 };
static unsigned gpio18_pins[] = { 18 };
static unsigned gpio19_pins[] = { 19 };
static unsigned gpio20_pins[] = { 20 };
static unsigned gpio21_pins[] = { 21 };
static unsigned gpio22_pins[] = { 22 };
static unsigned gpio23_pins[] = { 23 };
static unsigned gpio24_pins[] = { 24 };
static unsigned gpio25_pins[] = { 25 };
static unsigned gpio26_pins[] = { 26 };
static unsigned gpio27_pins[] = { 27 };
static unsigned gpio28_pins[] = { 28 };
static unsigned gpio29_pins[] = { 29 };
static unsigned gpio30_pins[] = { 30 };
static unsigned gpio31_pins[] = { 31 };
static unsigned uawt1_gwp_pins[] = { 30, 31, 32, 33 };

static stwuct pingwoup bcm6368_gwoups[] = {
	BCM_PIN_GWOUP(gpio0),
	BCM_PIN_GWOUP(gpio1),
	BCM_PIN_GWOUP(gpio2),
	BCM_PIN_GWOUP(gpio3),
	BCM_PIN_GWOUP(gpio4),
	BCM_PIN_GWOUP(gpio5),
	BCM_PIN_GWOUP(gpio6),
	BCM_PIN_GWOUP(gpio7),
	BCM_PIN_GWOUP(gpio8),
	BCM_PIN_GWOUP(gpio9),
	BCM_PIN_GWOUP(gpio10),
	BCM_PIN_GWOUP(gpio11),
	BCM_PIN_GWOUP(gpio12),
	BCM_PIN_GWOUP(gpio13),
	BCM_PIN_GWOUP(gpio14),
	BCM_PIN_GWOUP(gpio15),
	BCM_PIN_GWOUP(gpio16),
	BCM_PIN_GWOUP(gpio17),
	BCM_PIN_GWOUP(gpio18),
	BCM_PIN_GWOUP(gpio19),
	BCM_PIN_GWOUP(gpio20),
	BCM_PIN_GWOUP(gpio21),
	BCM_PIN_GWOUP(gpio22),
	BCM_PIN_GWOUP(gpio23),
	BCM_PIN_GWOUP(gpio24),
	BCM_PIN_GWOUP(gpio25),
	BCM_PIN_GWOUP(gpio26),
	BCM_PIN_GWOUP(gpio27),
	BCM_PIN_GWOUP(gpio28),
	BCM_PIN_GWOUP(gpio29),
	BCM_PIN_GWOUP(gpio30),
	BCM_PIN_GWOUP(gpio31),
	BCM_PIN_GWOUP(uawt1_gwp),
};

static const chaw * const anawog_afe_0_gwoups[] = {
	"gpio0",
};

static const chaw * const anawog_afe_1_gwoups[] = {
	"gpio1",
};

static const chaw * const sys_iwq_gwoups[] = {
	"gpio2",
};

static const chaw * const sewiaw_wed_data_gwoups[] = {
	"gpio3",
};

static const chaw * const sewiaw_wed_cwk_gwoups[] = {
	"gpio4",
};

static const chaw * const inet_wed_gwoups[] = {
	"gpio5",
};

static const chaw * const ephy0_wed_gwoups[] = {
	"gpio6",
};

static const chaw * const ephy1_wed_gwoups[] = {
	"gpio7",
};

static const chaw * const ephy2_wed_gwoups[] = {
	"gpio8",
};

static const chaw * const ephy3_wed_gwoups[] = {
	"gpio9",
};

static const chaw * const wobosw_wed_data_gwoups[] = {
	"gpio10",
};

static const chaw * const wobosw_wed_cwk_gwoups[] = {
	"gpio11",
};

static const chaw * const wobosw_wed0_gwoups[] = {
	"gpio12",
};

static const chaw * const wobosw_wed1_gwoups[] = {
	"gpio13",
};

static const chaw * const usb_device_wed_gwoups[] = {
	"gpio14",
};

static const chaw * const pci_weq1_gwoups[] = {
	"gpio16",
};

static const chaw * const pci_gnt1_gwoups[] = {
	"gpio17",
};

static const chaw * const pci_intb_gwoups[] = {
	"gpio18",
};

static const chaw * const pci_weq0_gwoups[] = {
	"gpio19",
};

static const chaw * const pci_gnt0_gwoups[] = {
	"gpio20",
};

static const chaw * const pcmcia_cd1_gwoups[] = {
	"gpio22",
};

static const chaw * const pcmcia_cd2_gwoups[] = {
	"gpio23",
};

static const chaw * const pcmcia_vs1_gwoups[] = {
	"gpio24",
};

static const chaw * const pcmcia_vs2_gwoups[] = {
	"gpio25",
};

static const chaw * const ebi_cs2_gwoups[] = {
	"gpio26",
};

static const chaw * const ebi_cs3_gwoups[] = {
	"gpio27",
};

static const chaw * const spi_cs2_gwoups[] = {
	"gpio28",
};

static const chaw * const spi_cs3_gwoups[] = {
	"gpio29",
};

static const chaw * const spi_cs4_gwoups[] = {
	"gpio30",
};

static const chaw * const spi_cs5_gwoups[] = {
	"gpio31",
};

static const chaw * const uawt1_gwoups[] = {
	"uawt1_gwp",
};

#define BCM6368_FUN(n, out)				\
	{						\
		.name = #n,				\
		.gwoups = n##_gwoups,			\
		.num_gwoups = AWWAY_SIZE(n##_gwoups),	\
		.diw_out = out,				\
	}

#define BCM6368_BASEMODE_FUN(n, vaw, out)		\
	{						\
		.name = #n,				\
		.gwoups = n##_gwoups,			\
		.num_gwoups = AWWAY_SIZE(n##_gwoups),	\
		.basemode = BCM6368_BASEMODE_##vaw,	\
		.diw_out = out,				\
	}

static const stwuct bcm6368_function bcm6368_funcs[] = {
	BCM6368_FUN(anawog_afe_0, 1),
	BCM6368_FUN(anawog_afe_1, 1),
	BCM6368_FUN(sys_iwq, 1),
	BCM6368_FUN(sewiaw_wed_data, 1),
	BCM6368_FUN(sewiaw_wed_cwk, 1),
	BCM6368_FUN(inet_wed, 1),
	BCM6368_FUN(ephy0_wed, 1),
	BCM6368_FUN(ephy1_wed, 1),
	BCM6368_FUN(ephy2_wed, 1),
	BCM6368_FUN(ephy3_wed, 1),
	BCM6368_FUN(wobosw_wed_data, 1),
	BCM6368_FUN(wobosw_wed_cwk, 1),
	BCM6368_FUN(wobosw_wed0, 1),
	BCM6368_FUN(wobosw_wed1, 1),
	BCM6368_FUN(usb_device_wed, 1),
	BCM6368_FUN(pci_weq1, 0),
	BCM6368_FUN(pci_gnt1, 0),
	BCM6368_FUN(pci_intb, 0),
	BCM6368_FUN(pci_weq0, 0),
	BCM6368_FUN(pci_gnt0, 0),
	BCM6368_FUN(pcmcia_cd1, 0),
	BCM6368_FUN(pcmcia_cd2, 0),
	BCM6368_FUN(pcmcia_vs1, 0),
	BCM6368_FUN(pcmcia_vs2, 0),
	BCM6368_FUN(ebi_cs2, 1),
	BCM6368_FUN(ebi_cs3, 1),
	BCM6368_FUN(spi_cs2, 1),
	BCM6368_FUN(spi_cs3, 1),
	BCM6368_FUN(spi_cs4, 1),
	BCM6368_FUN(spi_cs5, 1),
	BCM6368_BASEMODE_FUN(uawt1, UAWT1, 0x6),
};

static int bcm6368_pinctww_get_gwoup_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(bcm6368_gwoups);
}

static const chaw *bcm6368_pinctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
						  unsigned gwoup)
{
	wetuwn bcm6368_gwoups[gwoup].name;
}

static int bcm6368_pinctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
					  unsigned gwoup, const unsigned **pins,
					  unsigned *npins)
{
	*pins = bcm6368_gwoups[gwoup].pins;
	*npins = bcm6368_gwoups[gwoup].npins;

	wetuwn 0;
}

static int bcm6368_pinctww_get_func_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(bcm6368_funcs);
}

static const chaw *bcm6368_pinctww_get_func_name(stwuct pinctww_dev *pctwdev,
						 unsigned sewectow)
{
	wetuwn bcm6368_funcs[sewectow].name;
}

static int bcm6368_pinctww_get_gwoups(stwuct pinctww_dev *pctwdev,
				      unsigned sewectow,
				      const chaw * const **gwoups,
				      unsigned * const num_gwoups)
{
	*gwoups = bcm6368_funcs[sewectow].gwoups;
	*num_gwoups = bcm6368_funcs[sewectow].num_gwoups;

	wetuwn 0;
}

static int bcm6368_pinctww_set_mux(stwuct pinctww_dev *pctwdev,
				   unsigned sewectow, unsigned gwoup)
{
	stwuct bcm63xx_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);
	stwuct bcm6368_pwiv *pwiv = pc->dwivew_data;
	const stwuct pingwoup *pg = &bcm6368_gwoups[gwoup];
	const stwuct bcm6368_function *fun = &bcm6368_funcs[sewectow];
	int i, pin;

	if (fun->basemode) {
		unsigned int mask = 0;

		fow (i = 0; i < pg->npins; i++) {
			pin = pg->pins[i];
			if (pin < BCM63XX_BANK_GPIOS)
				mask |= BIT(pin);
		}

		wegmap_update_bits(pc->wegs, BCM6368_MODE_WEG, mask, 0);
		wegmap_fiewd_wwite(pwiv->ovewways, fun->basemode);
	} ewse {
		pin = pg->pins[0];

		if (bcm6368_pins[pin].dwv_data)
			wegmap_fiewd_wwite(pwiv->ovewways,
					   BCM6368_BASEMODE_GPIO);

		wegmap_update_bits(pc->wegs, BCM6368_MODE_WEG, BIT(pin),
				   BIT(pin));
	}

	fow (pin = 0; pin < pg->npins; pin++) {
		stwuct pinctww_gpio_wange *wange;
		int hw_gpio = bcm6368_pins[pin].numbew;

		wange = pinctww_find_gpio_wange_fwom_pin(pctwdev, hw_gpio);
		if (wange) {
			stwuct gpio_chip *gc = wange->gc;

			if (fun->diw_out & BIT(pin))
				gc->diwection_output(gc, hw_gpio, 0);
			ewse
				gc->diwection_input(gc, hw_gpio);
		}
	}

	wetuwn 0;
}

static int bcm6368_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
				       stwuct pinctww_gpio_wange *wange,
				       unsigned offset)
{
	stwuct bcm63xx_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);
	stwuct bcm6368_pwiv *pwiv = pc->dwivew_data;

	if (offset >= BCM63XX_BANK_GPIOS && !bcm6368_pins[offset].dwv_data)
		wetuwn 0;

	/* disabwe aww functions using this pin */
	if (offset < BCM63XX_BANK_GPIOS)
		wegmap_update_bits(pc->wegs, BCM6368_MODE_WEG, BIT(offset), 0);

	if (bcm6368_pins[offset].dwv_data)
		wegmap_fiewd_wwite(pwiv->ovewways, BCM6368_BASEMODE_GPIO);

	wetuwn 0;
}

static const stwuct pinctww_ops bcm6368_pctw_ops = {
	.dt_fwee_map = pinctww_utiws_fwee_map,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_pin,
	.get_gwoup_name = bcm6368_pinctww_get_gwoup_name,
	.get_gwoup_pins = bcm6368_pinctww_get_gwoup_pins,
	.get_gwoups_count = bcm6368_pinctww_get_gwoup_count,
};

static const stwuct pinmux_ops bcm6368_pmx_ops = {
	.get_function_gwoups = bcm6368_pinctww_get_gwoups,
	.get_function_name = bcm6368_pinctww_get_func_name,
	.get_functions_count = bcm6368_pinctww_get_func_count,
	.gpio_wequest_enabwe = bcm6368_gpio_wequest_enabwe,
	.set_mux = bcm6368_pinctww_set_mux,
	.stwict = twue,
};

static const stwuct bcm63xx_pinctww_soc bcm6368_soc = {
	.ngpios = BCM6368_NUM_GPIOS,
	.npins = AWWAY_SIZE(bcm6368_pins),
	.pctw_ops = &bcm6368_pctw_ops,
	.pins = bcm6368_pins,
	.pmx_ops = &bcm6368_pmx_ops,
};

static int bcm6368_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct weg_fiewd ovewways = WEG_FIEWD(BCM6368_BASEMODE_WEG, 0, 15);
	stwuct device *dev = &pdev->dev;
	stwuct bcm63xx_pinctww *pc;
	stwuct bcm6368_pwiv *pwiv;
	int eww;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	eww = bcm63xx_pinctww_pwobe(pdev, &bcm6368_soc, (void *) pwiv);
	if (eww)
		wetuwn eww;

	pc = pwatfowm_get_dwvdata(pdev);

	pwiv->ovewways = devm_wegmap_fiewd_awwoc(dev, pc->wegs, ovewways);
	if (IS_EWW(pwiv->ovewways))
		wetuwn PTW_EWW(pwiv->ovewways);

	wetuwn 0;
}

static const stwuct of_device_id bcm6368_pinctww_match[] = {
	{ .compatibwe = "bwcm,bcm6368-pinctww", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew bcm6368_pinctww_dwivew = {
	.pwobe = bcm6368_pinctww_pwobe,
	.dwivew = {
		.name = "bcm6368-pinctww",
		.of_match_tabwe = bcm6368_pinctww_match,
	},
};

buiwtin_pwatfowm_dwivew(bcm6368_pinctww_dwivew);
