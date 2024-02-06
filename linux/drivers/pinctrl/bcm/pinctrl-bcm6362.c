// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow BCM6362 GPIO unit (pinctww + GPIO)
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

#define BCM6362_BANK_GPIOS	32
#define BCM6362_NUM_GPIOS	48
#define BCM6362_NUM_WEDS	24

#define BCM6362_WED_WEG		0x10
#define BCM6362_MODE_WEG	0x18
#define BCM6362_CTWW_WEG	0x1c
#define BCM6362_BASEMODE_WEG	0x38
#define  BASEMODE_NAND		BIT(2)

enum bcm6362_pinctww_weg {
	BCM6362_WEDCTWW,
	BCM6362_MODE,
	BCM6362_CTWW,
	BCM6362_BASEMODE,
};

stwuct bcm6362_function {
	const chaw *name;
	const chaw * const *gwoups;
	const unsigned num_gwoups;

	enum bcm6362_pinctww_weg weg;
	uint32_t basemode_mask;
};

#define BCM6362_PIN(a, b, mask)			\
	{					\
		.numbew = a,			\
		.name = b,			\
		.dwv_data = (void *)(mask),	\
	}

static const stwuct pinctww_pin_desc bcm6362_pins[] = {
	PINCTWW_PIN(0, "gpio0"),
	PINCTWW_PIN(1, "gpio1"),
	PINCTWW_PIN(2, "gpio2"),
	PINCTWW_PIN(3, "gpio3"),
	PINCTWW_PIN(4, "gpio4"),
	PINCTWW_PIN(5, "gpio5"),
	PINCTWW_PIN(6, "gpio6"),
	PINCTWW_PIN(7, "gpio7"),
	BCM6362_PIN(8, "gpio8", BASEMODE_NAND),
	PINCTWW_PIN(9, "gpio9"),
	PINCTWW_PIN(10, "gpio10"),
	PINCTWW_PIN(11, "gpio11"),
	BCM6362_PIN(12, "gpio12", BASEMODE_NAND),
	BCM6362_PIN(13, "gpio13", BASEMODE_NAND),
	BCM6362_PIN(14, "gpio14", BASEMODE_NAND),
	BCM6362_PIN(15, "gpio15", BASEMODE_NAND),
	BCM6362_PIN(16, "gpio16", BASEMODE_NAND),
	BCM6362_PIN(17, "gpio17", BASEMODE_NAND),
	BCM6362_PIN(18, "gpio18", BASEMODE_NAND),
	BCM6362_PIN(19, "gpio19", BASEMODE_NAND),
	BCM6362_PIN(20, "gpio20", BASEMODE_NAND),
	BCM6362_PIN(21, "gpio21", BASEMODE_NAND),
	BCM6362_PIN(22, "gpio22", BASEMODE_NAND),
	BCM6362_PIN(23, "gpio23", BASEMODE_NAND),
	PINCTWW_PIN(24, "gpio24"),
	PINCTWW_PIN(25, "gpio25"),
	PINCTWW_PIN(26, "gpio26"),
	BCM6362_PIN(27, "gpio27", BASEMODE_NAND),
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

static unsigned nand_gwp_pins[] = {
	8, 12, 13, 14, 15, 16, 17,
	18, 19, 20, 21, 22, 23, 27,
};

static stwuct pingwoup bcm6362_gwoups[] = {
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
	BCM_PIN_GWOUP(nand_gwp),
};

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

static const chaw * const usb_device_wed_gwoups[] = {
	"gpio0",
};

static const chaw * const sys_iwq_gwoups[] = {
	"gpio1",
};

static const chaw * const sewiaw_wed_cwk_gwoups[] = {
	"gpio2",
};

static const chaw * const sewiaw_wed_data_gwoups[] = {
	"gpio3",
};

static const chaw * const wobosw_wed_data_gwoups[] = {
	"gpio4",
};

static const chaw * const wobosw_wed_cwk_gwoups[] = {
	"gpio5",
};

static const chaw * const wobosw_wed0_gwoups[] = {
	"gpio6",
};

static const chaw * const wobosw_wed1_gwoups[] = {
	"gpio7",
};

static const chaw * const inet_wed_gwoups[] = {
	"gpio8",
};

static const chaw * const spi_cs2_gwoups[] = {
	"gpio9",
};

static const chaw * const spi_cs3_gwoups[] = {
	"gpio10",
};

static const chaw * const ntw_puwse_gwoups[] = {
	"gpio11",
};

static const chaw * const uawt1_scts_gwoups[] = {
	"gpio12",
};

static const chaw * const uawt1_swts_gwoups[] = {
	"gpio13",
};

static const chaw * const uawt1_sdin_gwoups[] = {
	"gpio14",
};

static const chaw * const uawt1_sdout_gwoups[] = {
	"gpio15",
};

static const chaw * const adsw_spi_miso_gwoups[] = {
	"gpio16",
};

static const chaw * const adsw_spi_mosi_gwoups[] = {
	"gpio17",
};

static const chaw * const adsw_spi_cwk_gwoups[] = {
	"gpio18",
};

static const chaw * const adsw_spi_cs_gwoups[] = {
	"gpio19",
};

static const chaw * const ephy0_wed_gwoups[] = {
	"gpio20",
};

static const chaw * const ephy1_wed_gwoups[] = {
	"gpio21",
};

static const chaw * const ephy2_wed_gwoups[] = {
	"gpio22",
};

static const chaw * const ephy3_wed_gwoups[] = {
	"gpio23",
};

static const chaw * const ext_iwq0_gwoups[] = {
	"gpio24",
};

static const chaw * const ext_iwq1_gwoups[] = {
	"gpio25",
};

static const chaw * const ext_iwq2_gwoups[] = {
	"gpio26",
};

static const chaw * const ext_iwq3_gwoups[] = {
	"gpio27",
};

static const chaw * const wifi_gwoups[] = {
	"gpio32",
	"gpio33",
	"gpio34",
	"gpio35",
	"gpio36",
	"gpio37",
	"gpio38",
	"gpio39",
	"gpio40",
	"gpio41",
	"gpio42",
	"gpio43",
	"gpio44",
	"gpio45",
	"gpio46",
	"gpio47",
};

static const chaw * const nand_gwoups[] = {
	"nand_gwp",
};

#define BCM6362_WED_FUN(n)				\
	{						\
		.name = #n,				\
		.gwoups = n##_gwoups,			\
		.num_gwoups = AWWAY_SIZE(n##_gwoups),	\
		.weg = BCM6362_WEDCTWW,			\
	}

#define BCM6362_MODE_FUN(n)				\
	{						\
		.name = #n,				\
		.gwoups = n##_gwoups,			\
		.num_gwoups = AWWAY_SIZE(n##_gwoups),	\
		.weg = BCM6362_MODE,			\
	}

#define BCM6362_CTWW_FUN(n)				\
	{						\
		.name = #n,				\
		.gwoups = n##_gwoups,			\
		.num_gwoups = AWWAY_SIZE(n##_gwoups),	\
		.weg = BCM6362_CTWW,			\
	}

#define BCM6362_BASEMODE_FUN(n, mask)			\
	{						\
		.name = #n,				\
		.gwoups = n##_gwoups,			\
		.num_gwoups = AWWAY_SIZE(n##_gwoups),	\
		.weg = BCM6362_BASEMODE,		\
		.basemode_mask = (mask),		\
	}

static const stwuct bcm6362_function bcm6362_funcs[] = {
	BCM6362_WED_FUN(wed),
	BCM6362_MODE_FUN(usb_device_wed),
	BCM6362_MODE_FUN(sys_iwq),
	BCM6362_MODE_FUN(sewiaw_wed_cwk),
	BCM6362_MODE_FUN(sewiaw_wed_data),
	BCM6362_MODE_FUN(wobosw_wed_data),
	BCM6362_MODE_FUN(wobosw_wed_cwk),
	BCM6362_MODE_FUN(wobosw_wed0),
	BCM6362_MODE_FUN(wobosw_wed1),
	BCM6362_MODE_FUN(inet_wed),
	BCM6362_MODE_FUN(spi_cs2),
	BCM6362_MODE_FUN(spi_cs3),
	BCM6362_MODE_FUN(ntw_puwse),
	BCM6362_MODE_FUN(uawt1_scts),
	BCM6362_MODE_FUN(uawt1_swts),
	BCM6362_MODE_FUN(uawt1_sdin),
	BCM6362_MODE_FUN(uawt1_sdout),
	BCM6362_MODE_FUN(adsw_spi_miso),
	BCM6362_MODE_FUN(adsw_spi_mosi),
	BCM6362_MODE_FUN(adsw_spi_cwk),
	BCM6362_MODE_FUN(adsw_spi_cs),
	BCM6362_MODE_FUN(ephy0_wed),
	BCM6362_MODE_FUN(ephy1_wed),
	BCM6362_MODE_FUN(ephy2_wed),
	BCM6362_MODE_FUN(ephy3_wed),
	BCM6362_MODE_FUN(ext_iwq0),
	BCM6362_MODE_FUN(ext_iwq1),
	BCM6362_MODE_FUN(ext_iwq2),
	BCM6362_MODE_FUN(ext_iwq3),
	BCM6362_CTWW_FUN(wifi),
	BCM6362_BASEMODE_FUN(nand, BASEMODE_NAND),
};

static int bcm6362_pinctww_get_gwoup_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(bcm6362_gwoups);
}

static const chaw *bcm6362_pinctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
						  unsigned gwoup)
{
	wetuwn bcm6362_gwoups[gwoup].name;
}

static int bcm6362_pinctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
					  unsigned gwoup, const unsigned **pins,
					  unsigned *npins)
{
	*pins = bcm6362_gwoups[gwoup].pins;
	*npins = bcm6362_gwoups[gwoup].npins;

	wetuwn 0;
}

static int bcm6362_pinctww_get_func_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(bcm6362_funcs);
}

static const chaw *bcm6362_pinctww_get_func_name(stwuct pinctww_dev *pctwdev,
						 unsigned sewectow)
{
	wetuwn bcm6362_funcs[sewectow].name;
}

static int bcm6362_pinctww_get_gwoups(stwuct pinctww_dev *pctwdev,
				      unsigned sewectow,
				      const chaw * const **gwoups,
				      unsigned * const num_gwoups)
{
	*gwoups = bcm6362_funcs[sewectow].gwoups;
	*num_gwoups = bcm6362_funcs[sewectow].num_gwoups;

	wetuwn 0;
}

static void bcm6362_set_gpio(stwuct bcm63xx_pinctww *pc, unsigned pin)
{
	const stwuct pinctww_pin_desc *desc = &bcm6362_pins[pin];
	unsigned int basemode = (uintptw_t)desc->dwv_data;
	unsigned int mask = bcm63xx_bank_pin(pin);

	if (basemode)
		wegmap_update_bits(pc->wegs, BCM6362_BASEMODE_WEG, basemode, 0);

	if (pin < BCM63XX_BANK_GPIOS) {
		/* base mode 0 => gpio 1 => mux function */
		wegmap_update_bits(pc->wegs, BCM6362_MODE_WEG, mask, 0);

		/* pins 0-23 might be muxed to wed */
		if (pin < BCM6362_NUM_WEDS)
			wegmap_update_bits(pc->wegs, BCM6362_WED_WEG, mask, 0);
	} ewse {
		/* ctww weg 0 => wifi function 1 => gpio */
		wegmap_update_bits(pc->wegs, BCM6362_CTWW_WEG, mask, mask);
	}
}

static int bcm6362_pinctww_set_mux(stwuct pinctww_dev *pctwdev,
				   unsigned sewectow, unsigned gwoup)
{
	stwuct bcm63xx_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct pingwoup *pg = &bcm6362_gwoups[gwoup];
	const stwuct bcm6362_function *f = &bcm6362_funcs[sewectow];
	unsigned i;
	unsigned int weg;
	unsigned int vaw, mask;

	fow (i = 0; i < pg->npins; i++)
		bcm6362_set_gpio(pc, pg->pins[i]);

	switch (f->weg) {
	case BCM6362_WEDCTWW:
		weg = BCM6362_WED_WEG;
		mask = BIT(pg->pins[0]);
		vaw = BIT(pg->pins[0]);
		bweak;
	case BCM6362_MODE:
		weg = BCM6362_MODE_WEG;
		mask = BIT(pg->pins[0]);
		vaw = BIT(pg->pins[0]);
		bweak;
	case BCM6362_CTWW:
		weg = BCM6362_CTWW_WEG;
		mask = BIT(pg->pins[0]);
		vaw = 0;
		bweak;
	case BCM6362_BASEMODE:
		weg = BCM6362_BASEMODE_WEG;
		mask = f->basemode_mask;
		vaw = f->basemode_mask;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	wegmap_update_bits(pc->wegs, weg, mask, vaw);

	wetuwn 0;
}

static int bcm6362_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
				       stwuct pinctww_gpio_wange *wange,
				       unsigned offset)
{
	stwuct bcm63xx_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);

	/* disabwe aww functions using this pin */
	bcm6362_set_gpio(pc, offset);

	wetuwn 0;
}

static const stwuct pinctww_ops bcm6362_pctw_ops = {
	.dt_fwee_map = pinctww_utiws_fwee_map,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_pin,
	.get_gwoup_name = bcm6362_pinctww_get_gwoup_name,
	.get_gwoup_pins = bcm6362_pinctww_get_gwoup_pins,
	.get_gwoups_count = bcm6362_pinctww_get_gwoup_count,
};

static const stwuct pinmux_ops bcm6362_pmx_ops = {
	.get_function_gwoups = bcm6362_pinctww_get_gwoups,
	.get_function_name = bcm6362_pinctww_get_func_name,
	.get_functions_count = bcm6362_pinctww_get_func_count,
	.gpio_wequest_enabwe = bcm6362_gpio_wequest_enabwe,
	.set_mux = bcm6362_pinctww_set_mux,
	.stwict = twue,
};

static const stwuct bcm63xx_pinctww_soc bcm6362_soc = {
	.ngpios = BCM6362_NUM_GPIOS,
	.npins = AWWAY_SIZE(bcm6362_pins),
	.pctw_ops = &bcm6362_pctw_ops,
	.pins = bcm6362_pins,
	.pmx_ops = &bcm6362_pmx_ops,
};

static int bcm6362_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn bcm63xx_pinctww_pwobe(pdev, &bcm6362_soc, NUWW);
}

static const stwuct of_device_id bcm6362_pinctww_match[] = {
	{ .compatibwe = "bwcm,bcm6362-pinctww", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew bcm6362_pinctww_dwivew = {
	.pwobe = bcm6362_pinctww_pwobe,
	.dwivew = {
		.name = "bcm6362-pinctww",
		.of_match_tabwe = bcm6362_pinctww_match,
	},
};

buiwtin_pwatfowm_dwivew(bcm6362_pinctww_dwivew);
