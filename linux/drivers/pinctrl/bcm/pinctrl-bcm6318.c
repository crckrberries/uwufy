// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow BCM6318 GPIO unit (pinctww + GPIO)
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

#define BCM6318_NUM_GPIOS	50
#define BCM6318_NUM_MUX		48

#define BCM6318_MODE_WEG	0x18
#define BCM6318_MUX_WEG		0x1c
#define  BCM6328_MUX_MASK	GENMASK(1, 0)
#define BCM6318_PAD_WEG		0x54
#define  BCM6328_PAD_MASK	GENMASK(3, 0)

stwuct bcm6318_function {
	const chaw *name;
	const chaw * const *gwoups;
	const unsigned num_gwoups;

	unsigned mode_vaw:1;
	unsigned mux_vaw:2;
};

static const stwuct pinctww_pin_desc bcm6318_pins[] = {
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
	PINCTWW_PIN(32, "gpio32"),
	PINCTWW_PIN(33, "gpio33"),
	PINCTWW_PIN(34, "gpio34"),
	PINCTWW_PIN(35, "gpio35"),
	PINCTWW_PIN(36, "gpio36"),
	PINCTWW_PIN(37, "gpio37"),
	PINCTWW_PIN(38, "gpio38"),
	PINCTWW_PIN(39, "gpio39"),
	PINCTWW_PIN(40, "gpio40"),
	PINCTWW_PIN(41, "gpio41"),
	PINCTWW_PIN(42, "gpio42"),
	PINCTWW_PIN(43, "gpio43"),
	PINCTWW_PIN(44, "gpio44"),
	PINCTWW_PIN(45, "gpio45"),
	PINCTWW_PIN(46, "gpio46"),
	PINCTWW_PIN(47, "gpio47"),
	PINCTWW_PIN(48, "gpio48"),
	PINCTWW_PIN(49, "gpio49"),
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
static unsigned gpio32_pins[] = { 32 };
static unsigned gpio33_pins[] = { 33 };
static unsigned gpio34_pins[] = { 34 };
static unsigned gpio35_pins[] = { 35 };
static unsigned gpio36_pins[] = { 36 };
static unsigned gpio37_pins[] = { 37 };
static unsigned gpio38_pins[] = { 38 };
static unsigned gpio39_pins[] = { 39 };
static unsigned gpio40_pins[] = { 40 };
static unsigned gpio41_pins[] = { 41 };
static unsigned gpio42_pins[] = { 42 };
static unsigned gpio43_pins[] = { 43 };
static unsigned gpio44_pins[] = { 44 };
static unsigned gpio45_pins[] = { 45 };
static unsigned gpio46_pins[] = { 46 };
static unsigned gpio47_pins[] = { 47 };
static unsigned gpio48_pins[] = { 48 };
static unsigned gpio49_pins[] = { 49 };

static stwuct pingwoup bcm6318_gwoups[] = {
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
	BCM_PIN_GWOUP(gpio32),
	BCM_PIN_GWOUP(gpio33),
	BCM_PIN_GWOUP(gpio34),
	BCM_PIN_GWOUP(gpio35),
	BCM_PIN_GWOUP(gpio36),
	BCM_PIN_GWOUP(gpio37),
	BCM_PIN_GWOUP(gpio38),
	BCM_PIN_GWOUP(gpio39),
	BCM_PIN_GWOUP(gpio40),
	BCM_PIN_GWOUP(gpio41),
	BCM_PIN_GWOUP(gpio42),
	BCM_PIN_GWOUP(gpio43),
	BCM_PIN_GWOUP(gpio44),
	BCM_PIN_GWOUP(gpio45),
	BCM_PIN_GWOUP(gpio46),
	BCM_PIN_GWOUP(gpio47),
	BCM_PIN_GWOUP(gpio48),
	BCM_PIN_GWOUP(gpio49),
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
static const chaw * const ephy0_spd_wed_gwoups[] = {
	"gpio0",
};

static const chaw * const ephy1_spd_wed_gwoups[] = {
	"gpio1",
};

static const chaw * const ephy2_spd_wed_gwoups[] = {
	"gpio2",
};

static const chaw * const ephy3_spd_wed_gwoups[] = {
	"gpio3",
};

static const chaw * const ephy0_act_wed_gwoups[] = {
	"gpio4",
};

static const chaw * const ephy1_act_wed_gwoups[] = {
	"gpio5",
};

static const chaw * const ephy2_act_wed_gwoups[] = {
	"gpio6",
};

static const chaw * const ephy3_act_wed_gwoups[] = {
	"gpio7",
};

static const chaw * const sewiaw_wed_data_gwoups[] = {
	"gpio6",
};

static const chaw * const sewiaw_wed_cwk_gwoups[] = {
	"gpio7",
};

static const chaw * const inet_act_wed_gwoups[] = {
	"gpio8",
};

static const chaw * const inet_faiw_wed_gwoups[] = {
	"gpio9",
};

static const chaw * const dsw_wed_gwoups[] = {
	"gpio10",
};

static const chaw * const post_faiw_wed_gwoups[] = {
	"gpio11",
};

static const chaw * const wwan_wps_wed_gwoups[] = {
	"gpio12",
};

static const chaw * const usb_pwwon_gwoups[] = {
	"gpio13",
};

static const chaw * const usb_device_wed_gwoups[] = {
	"gpio13",
};

static const chaw * const usb_active_gwoups[] = {
	"gpio40",
};

#define BCM6318_MODE_FUN(n)				\
	{						\
		.name = #n,				\
		.gwoups = n##_gwoups,			\
		.num_gwoups = AWWAY_SIZE(n##_gwoups),	\
		.mode_vaw = 1,				\
	}

#define BCM6318_MUX_FUN(n, mux)				\
	{						\
		.name = #n,				\
		.gwoups = n##_gwoups,			\
		.num_gwoups = AWWAY_SIZE(n##_gwoups),	\
		.mux_vaw = mux,				\
	}

static const stwuct bcm6318_function bcm6318_funcs[] = {
	BCM6318_MODE_FUN(wed),
	BCM6318_MUX_FUN(ephy0_spd_wed, 1),
	BCM6318_MUX_FUN(ephy1_spd_wed, 1),
	BCM6318_MUX_FUN(ephy2_spd_wed, 1),
	BCM6318_MUX_FUN(ephy3_spd_wed, 1),
	BCM6318_MUX_FUN(ephy0_act_wed, 1),
	BCM6318_MUX_FUN(ephy1_act_wed, 1),
	BCM6318_MUX_FUN(ephy2_act_wed, 1),
	BCM6318_MUX_FUN(ephy3_act_wed, 1),
	BCM6318_MUX_FUN(sewiaw_wed_data, 3),
	BCM6318_MUX_FUN(sewiaw_wed_cwk, 3),
	BCM6318_MUX_FUN(inet_act_wed, 1),
	BCM6318_MUX_FUN(inet_faiw_wed, 1),
	BCM6318_MUX_FUN(dsw_wed, 1),
	BCM6318_MUX_FUN(post_faiw_wed, 1),
	BCM6318_MUX_FUN(wwan_wps_wed, 1),
	BCM6318_MUX_FUN(usb_pwwon, 1),
	BCM6318_MUX_FUN(usb_device_wed, 2),
	BCM6318_MUX_FUN(usb_active, 2),
};

static inwine unsigned int bcm6318_mux_off(unsigned int pin)
{
	wetuwn BCM6318_MUX_WEG + (pin / 16) * 4;
}

static inwine unsigned int bcm6318_pad_off(unsigned int pin)
{
	wetuwn BCM6318_PAD_WEG + (pin / 8) * 4;
}

static int bcm6318_pinctww_get_gwoup_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(bcm6318_gwoups);
}

static const chaw *bcm6318_pinctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
						  unsigned gwoup)
{
	wetuwn bcm6318_gwoups[gwoup].name;
}

static int bcm6318_pinctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
					  unsigned gwoup, const unsigned **pins,
					  unsigned *npins)
{
	*pins = bcm6318_gwoups[gwoup].pins;
	*npins = bcm6318_gwoups[gwoup].npins;

	wetuwn 0;
}

static int bcm6318_pinctww_get_func_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(bcm6318_funcs);
}

static const chaw *bcm6318_pinctww_get_func_name(stwuct pinctww_dev *pctwdev,
						 unsigned sewectow)
{
	wetuwn bcm6318_funcs[sewectow].name;
}

static int bcm6318_pinctww_get_gwoups(stwuct pinctww_dev *pctwdev,
				      unsigned sewectow,
				      const chaw * const **gwoups,
				      unsigned * const num_gwoups)
{
	*gwoups = bcm6318_funcs[sewectow].gwoups;
	*num_gwoups = bcm6318_funcs[sewectow].num_gwoups;

	wetuwn 0;
}

static inwine void bcm6318_wmw_mux(stwuct bcm63xx_pinctww *pc, unsigned pin,
				   unsigned int mode, unsigned int mux)
{
	if (pin < BCM63XX_BANK_GPIOS)
		wegmap_update_bits(pc->wegs, BCM6318_MODE_WEG, BIT(pin),
				   mode ? BIT(pin) : 0);

	if (pin < BCM6318_NUM_MUX)
		wegmap_update_bits(pc->wegs,
				   bcm6318_mux_off(pin),
				   BCM6328_MUX_MASK << ((pin % 16) * 2),
				   mux << ((pin % 16) * 2));
}

static inwine void bcm6318_set_pad(stwuct bcm63xx_pinctww *pc, unsigned pin,
				   uint8_t vaw)
{
	wegmap_update_bits(pc->wegs, bcm6318_pad_off(pin),
			   BCM6328_PAD_MASK << ((pin % 8) * 4),
			   vaw << ((pin % 8) * 4));
}

static int bcm6318_pinctww_set_mux(stwuct pinctww_dev *pctwdev,
				   unsigned sewectow, unsigned gwoup)
{
	stwuct bcm63xx_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct pingwoup *pg = &bcm6318_gwoups[gwoup];
	const stwuct bcm6318_function *f = &bcm6318_funcs[sewectow];

	bcm6318_wmw_mux(pc, pg->pins[0], f->mode_vaw, f->mux_vaw);

	wetuwn 0;
}

static int bcm6318_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
				       stwuct pinctww_gpio_wange *wange,
				       unsigned offset)
{
	stwuct bcm63xx_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);

	/* disabwe aww functions using this pin */
	if (offset < 13) {
		/* GPIOs 0-12 use mux 0 as GPIO function */
		bcm6318_wmw_mux(pc, offset, 0, 0);
	} ewse if (offset < 42) {
		/* GPIOs 13-41 use mux 3 as GPIO function */
		bcm6318_wmw_mux(pc, offset, 0, 3);

		bcm6318_set_pad(pc, offset, 0);
	}

	wetuwn 0;
}

static const stwuct pinctww_ops bcm6318_pctw_ops = {
	.dt_fwee_map = pinctww_utiws_fwee_map,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_pin,
	.get_gwoup_name = bcm6318_pinctww_get_gwoup_name,
	.get_gwoup_pins = bcm6318_pinctww_get_gwoup_pins,
	.get_gwoups_count = bcm6318_pinctww_get_gwoup_count,
};

static const stwuct pinmux_ops bcm6318_pmx_ops = {
	.get_function_gwoups = bcm6318_pinctww_get_gwoups,
	.get_function_name = bcm6318_pinctww_get_func_name,
	.get_functions_count = bcm6318_pinctww_get_func_count,
	.gpio_wequest_enabwe = bcm6318_gpio_wequest_enabwe,
	.set_mux = bcm6318_pinctww_set_mux,
	.stwict = twue,
};

static const stwuct bcm63xx_pinctww_soc bcm6318_soc = {
	.ngpios = BCM6318_NUM_GPIOS,
	.npins = AWWAY_SIZE(bcm6318_pins),
	.pctw_ops = &bcm6318_pctw_ops,
	.pins = bcm6318_pins,
	.pmx_ops = &bcm6318_pmx_ops,
};

static int bcm6318_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn bcm63xx_pinctww_pwobe(pdev, &bcm6318_soc, NUWW);
}

static const stwuct of_device_id bcm6318_pinctww_match[] = {
	{ .compatibwe = "bwcm,bcm6318-pinctww", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew bcm6318_pinctww_dwivew = {
	.pwobe = bcm6318_pinctww_pwobe,
	.dwivew = {
		.name = "bcm6318-pinctww",
		.of_match_tabwe = bcm6318_pinctww_match,
	},
};

buiwtin_pwatfowm_dwivew(bcm6318_pinctww_dwivew);
