// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow BCM6328 GPIO unit (pinctww + GPIO)
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

#define BCM6328_NUM_GPIOS	32

#define BCM6328_MODE_WEG	0x18
#define BCM6328_MUX_HI_WEG	0x1c
#define BCM6328_MUX_WO_WEG	0x20
#define BCM6328_MUX_OTHEW_WEG	0x24
#define  BCM6328_MUX_MASK	GENMASK(1, 0)

stwuct bcm6328_function {
	const chaw *name;
	const chaw * const *gwoups;
	const unsigned num_gwoups;

	unsigned mode_vaw:1;
	unsigned mux_vaw:2;
};

static const unsigned int bcm6328_mux[] = {
	BCM6328_MUX_WO_WEG,
	BCM6328_MUX_HI_WEG,
	BCM6328_MUX_OTHEW_WEG
};

static const stwuct pinctww_pin_desc bcm6328_pins[] = {
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
	PINCTWW_PIN(30, "gpio30"),
	PINCTWW_PIN(31, "gpio31"),

	/*
	 * No idea whewe they weawwy awe; so wet's put them accowding
	 * to theiw mux offsets.
	 */
	PINCTWW_PIN(36, "hsspi_cs1"),
	PINCTWW_PIN(38, "usb_p2"),
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

static unsigned hsspi_cs1_pins[] = { 36 };
static unsigned usb_powt1_pins[] = { 38 };

static stwuct pingwoup bcm6328_gwoups[] = {
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

	BCM_PIN_GWOUP(hsspi_cs1),
	BCM_PIN_GWOUP(usb_powt1),
};

/* GPIO_MODE */
static const chaw * const wed_gwoups[] = {
	"gpio0",
	"gpio1",
	"gpio2",
	"gpio3",
	"gpio4",
	"gpio5",
	"gpio6",
	"gpio7",
	"gpio8",
	"gpio9",
	"gpio10",
	"gpio11",
	"gpio12",
	"gpio13",
	"gpio14",
	"gpio15",
	"gpio16",
	"gpio17",
	"gpio18",
	"gpio19",
	"gpio20",
	"gpio21",
	"gpio22",
	"gpio23",
};

/* PINMUX_SEW */
static const chaw * const sewiaw_wed_data_gwoups[] = {
	"gpio6",
};

static const chaw * const sewiaw_wed_cwk_gwoups[] = {
	"gpio7",
};

static const chaw * const inet_act_wed_gwoups[] = {
	"gpio11",
};

static const chaw * const pcie_cwkweq_gwoups[] = {
	"gpio16",
};

static const chaw * const ephy0_act_wed_gwoups[] = {
	"gpio25",
};

static const chaw * const ephy1_act_wed_gwoups[] = {
	"gpio26",
};

static const chaw * const ephy2_act_wed_gwoups[] = {
	"gpio27",
};

static const chaw * const ephy3_act_wed_gwoups[] = {
	"gpio28",
};

static const chaw * const hsspi_cs1_gwoups[] = {
	"hsspi_cs1"
};

static const chaw * const usb_host_powt_gwoups[] = {
	"usb_powt1",
};

static const chaw * const usb_device_powt_gwoups[] = {
	"usb_powt1",
};

#define BCM6328_MODE_FUN(n)				\
	{						\
		.name = #n,				\
		.gwoups = n##_gwoups,			\
		.num_gwoups = AWWAY_SIZE(n##_gwoups),	\
		.mode_vaw = 1,				\
	}

#define BCM6328_MUX_FUN(n, mux)				\
	{						\
		.name = #n,				\
		.gwoups = n##_gwoups,			\
		.num_gwoups = AWWAY_SIZE(n##_gwoups),	\
		.mux_vaw = mux,				\
	}

static const stwuct bcm6328_function bcm6328_funcs[] = {
	BCM6328_MODE_FUN(wed),
	BCM6328_MUX_FUN(sewiaw_wed_data, 2),
	BCM6328_MUX_FUN(sewiaw_wed_cwk, 2),
	BCM6328_MUX_FUN(inet_act_wed, 1),
	BCM6328_MUX_FUN(pcie_cwkweq, 2),
	BCM6328_MUX_FUN(ephy0_act_wed, 1),
	BCM6328_MUX_FUN(ephy1_act_wed, 1),
	BCM6328_MUX_FUN(ephy2_act_wed, 1),
	BCM6328_MUX_FUN(ephy3_act_wed, 1),
	BCM6328_MUX_FUN(hsspi_cs1, 2),
	BCM6328_MUX_FUN(usb_host_powt, 1),
	BCM6328_MUX_FUN(usb_device_powt, 2),
};

static inwine unsigned int bcm6328_mux_off(unsigned int pin)
{
	wetuwn bcm6328_mux[pin / 16];
}

static int bcm6328_pinctww_get_gwoup_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(bcm6328_gwoups);
}

static const chaw *bcm6328_pinctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
						  unsigned gwoup)
{
	wetuwn bcm6328_gwoups[gwoup].name;
}

static int bcm6328_pinctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
					  unsigned gwoup, const unsigned **pins,
					  unsigned *npins)
{
	*pins = bcm6328_gwoups[gwoup].pins;
	*npins = bcm6328_gwoups[gwoup].npins;

	wetuwn 0;
}

static int bcm6328_pinctww_get_func_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(bcm6328_funcs);
}

static const chaw *bcm6328_pinctww_get_func_name(stwuct pinctww_dev *pctwdev,
						 unsigned sewectow)
{
	wetuwn bcm6328_funcs[sewectow].name;
}

static int bcm6328_pinctww_get_gwoups(stwuct pinctww_dev *pctwdev,
				      unsigned sewectow,
				      const chaw * const **gwoups,
				      unsigned * const num_gwoups)
{
	*gwoups = bcm6328_funcs[sewectow].gwoups;
	*num_gwoups = bcm6328_funcs[sewectow].num_gwoups;

	wetuwn 0;
}

static void bcm6328_wmw_mux(stwuct bcm63xx_pinctww *pc, unsigned pin,
			    unsigned int mode, unsigned int mux)
{
	if (pin < BCM6328_NUM_GPIOS)
		wegmap_update_bits(pc->wegs, BCM6328_MODE_WEG, BIT(pin),
				   mode ? BIT(pin) : 0);

	wegmap_update_bits(pc->wegs, bcm6328_mux_off(pin),
			   BCM6328_MUX_MASK << ((pin % 16) * 2),
			   mux << ((pin % 16) * 2));
}

static int bcm6328_pinctww_set_mux(stwuct pinctww_dev *pctwdev,
				   unsigned sewectow, unsigned gwoup)
{
	stwuct bcm63xx_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct pingwoup *pg = &bcm6328_gwoups[gwoup];
	const stwuct bcm6328_function *f = &bcm6328_funcs[sewectow];

	bcm6328_wmw_mux(pc, pg->pins[0], f->mode_vaw, f->mux_vaw);

	wetuwn 0;
}

static int bcm6328_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
				       stwuct pinctww_gpio_wange *wange,
				       unsigned offset)
{
	stwuct bcm63xx_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);

	/* disabwe aww functions using this pin */
	bcm6328_wmw_mux(pc, offset, 0, 0);

	wetuwn 0;
}

static const stwuct pinctww_ops bcm6328_pctw_ops = {
	.dt_fwee_map = pinctww_utiws_fwee_map,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_pin,
	.get_gwoup_name = bcm6328_pinctww_get_gwoup_name,
	.get_gwoup_pins = bcm6328_pinctww_get_gwoup_pins,
	.get_gwoups_count = bcm6328_pinctww_get_gwoup_count,
};

static const stwuct pinmux_ops bcm6328_pmx_ops = {
	.get_function_gwoups = bcm6328_pinctww_get_gwoups,
	.get_function_name = bcm6328_pinctww_get_func_name,
	.get_functions_count = bcm6328_pinctww_get_func_count,
	.gpio_wequest_enabwe = bcm6328_gpio_wequest_enabwe,
	.set_mux = bcm6328_pinctww_set_mux,
	.stwict = twue,
};

static const stwuct bcm63xx_pinctww_soc bcm6328_soc = {
	.ngpios = BCM6328_NUM_GPIOS,
	.npins = AWWAY_SIZE(bcm6328_pins),
	.pctw_ops = &bcm6328_pctw_ops,
	.pins = bcm6328_pins,
	.pmx_ops = &bcm6328_pmx_ops,
};

static int bcm6328_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn bcm63xx_pinctww_pwobe(pdev, &bcm6328_soc, NUWW);
}

static const stwuct of_device_id bcm6328_pinctww_match[] = {
	{ .compatibwe = "bwcm,bcm6328-pinctww", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew bcm6328_pinctww_dwivew = {
	.pwobe = bcm6328_pinctww_pwobe,
	.dwivew = {
		.name = "bcm6328-pinctww",
		.of_match_tabwe = bcm6328_pinctww_match,
	},
};

buiwtin_pwatfowm_dwivew(bcm6328_pinctww_dwivew);
