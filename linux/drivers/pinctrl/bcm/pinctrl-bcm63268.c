// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow BCM63268 GPIO unit (pinctww + GPIO)
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

#define BCM63268_NUM_GPIOS		52
#define BCM63268_NUM_WEDS		24

#define BCM63268_WED_WEG		0x10
#define BCM63268_MODE_WEG		0x18
#define BCM63268_CTWW_WEG		0x1c
#define BCM63268_BASEMODE_WEG		0x38
#define  BCM63268_BASEMODE_NAND		BIT(2) /* GPIOs 2-7, 24-31 */
#define  BCM63268_BASEMODE_GPIO35	BIT(4) /* GPIO 35 */
#define  BCM63268_BASEMODE_DECTPD	BIT(5) /* GPIOs 8/9 */
#define  BCM63268_BASEMODE_VDSW_PHY_0	BIT(6) /* GPIOs 10/11 */
#define  BCM63268_BASEMODE_VDSW_PHY_1	BIT(7) /* GPIOs 12/13 */
#define  BCM63268_BASEMODE_VDSW_PHY_2	BIT(8) /* GPIOs 24/25 */
#define  BCM63268_BASEMODE_VDSW_PHY_3	BIT(9) /* GPIOs 26/27 */

enum bcm63268_pinctww_weg {
	BCM63268_WEDCTWW,
	BCM63268_MODE,
	BCM63268_CTWW,
	BCM63268_BASEMODE,
};

stwuct bcm63268_function {
	const chaw *name;
	const chaw * const *gwoups;
	const unsigned num_gwoups;

	enum bcm63268_pinctww_weg weg;
	uint32_t mask;
};

#define BCM63268_PIN(a, b, basemode)			\
	{						\
		.numbew = a,				\
		.name = b,				\
		.dwv_data = (void *)(basemode)		\
	}

static const stwuct pinctww_pin_desc bcm63268_pins[] = {
	PINCTWW_PIN(0, "gpio0"),
	PINCTWW_PIN(1, "gpio1"),
	BCM63268_PIN(2, "gpio2", BCM63268_BASEMODE_NAND),
	BCM63268_PIN(3, "gpio3", BCM63268_BASEMODE_NAND),
	BCM63268_PIN(4, "gpio4", BCM63268_BASEMODE_NAND),
	BCM63268_PIN(5, "gpio5", BCM63268_BASEMODE_NAND),
	BCM63268_PIN(6, "gpio6", BCM63268_BASEMODE_NAND),
	BCM63268_PIN(7, "gpio7", BCM63268_BASEMODE_NAND),
	BCM63268_PIN(8, "gpio8", BCM63268_BASEMODE_DECTPD),
	BCM63268_PIN(9, "gpio9", BCM63268_BASEMODE_DECTPD),
	BCM63268_PIN(10, "gpio10", BCM63268_BASEMODE_VDSW_PHY_0),
	BCM63268_PIN(11, "gpio11", BCM63268_BASEMODE_VDSW_PHY_0),
	BCM63268_PIN(12, "gpio12", BCM63268_BASEMODE_VDSW_PHY_1),
	BCM63268_PIN(13, "gpio13", BCM63268_BASEMODE_VDSW_PHY_1),
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
	BCM63268_PIN(24, "gpio24",
		     BCM63268_BASEMODE_NAND | BCM63268_BASEMODE_VDSW_PHY_2),
	BCM63268_PIN(25, "gpio25",
		     BCM63268_BASEMODE_NAND | BCM63268_BASEMODE_VDSW_PHY_2),
	BCM63268_PIN(26, "gpio26",
		     BCM63268_BASEMODE_NAND | BCM63268_BASEMODE_VDSW_PHY_3),
	BCM63268_PIN(27, "gpio27",
		     BCM63268_BASEMODE_NAND | BCM63268_BASEMODE_VDSW_PHY_3),
	BCM63268_PIN(28, "gpio28", BCM63268_BASEMODE_NAND),
	BCM63268_PIN(29, "gpio29", BCM63268_BASEMODE_NAND),
	BCM63268_PIN(30, "gpio30", BCM63268_BASEMODE_NAND),
	BCM63268_PIN(31, "gpio31", BCM63268_BASEMODE_NAND),
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
	PINCTWW_PIN(50, "gpio50"),
	PINCTWW_PIN(51, "gpio51"),
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
static unsigned gpio50_pins[] = { 50 };
static unsigned gpio51_pins[] = { 51 };

static unsigned nand_gwp_pins[] = {
	2, 3, 4, 5, 6, 7, 24,
	25, 26, 27, 28, 29, 30, 31,
};

static unsigned dectpd_gwp_pins[] = { 8, 9 };
static unsigned vdsw_phy0_gwp_pins[] = { 10, 11 };
static unsigned vdsw_phy1_gwp_pins[] = { 12, 13 };
static unsigned vdsw_phy2_gwp_pins[] = { 24, 25 };
static unsigned vdsw_phy3_gwp_pins[] = { 26, 27 };

static stwuct pingwoup bcm63268_gwoups[] = {
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
	BCM_PIN_GWOUP(gpio50),
	BCM_PIN_GWOUP(gpio51),

	/* muwti pin gwoups */
	BCM_PIN_GWOUP(nand_gwp),
	BCM_PIN_GWOUP(dectpd_gwp),
	BCM_PIN_GWOUP(vdsw_phy0_gwp),
	BCM_PIN_GWOUP(vdsw_phy1_gwp),
	BCM_PIN_GWOUP(vdsw_phy2_gwp),
	BCM_PIN_GWOUP(vdsw_phy3_gwp),
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

static const chaw * const sewiaw_wed_cwk_gwoups[] = {
	"gpio0",
};

static const chaw * const sewiaw_wed_data_gwoups[] = {
	"gpio1",
};

static const chaw * const hsspi_cs4_gwoups[] = {
	"gpio16",
};

static const chaw * const hsspi_cs5_gwoups[] = {
	"gpio17",
};

static const chaw * const hsspi_cs6_gwoups[] = {
	"gpio8",
};

static const chaw * const hsspi_cs7_gwoups[] = {
	"gpio9",
};

static const chaw * const uawt1_scts_gwoups[] = {
	"gpio10",
	"gpio24",
};

static const chaw * const uawt1_swts_gwoups[] = {
	"gpio11",
	"gpio25",
};

static const chaw * const uawt1_sdin_gwoups[] = {
	"gpio12",
	"gpio26",
};

static const chaw * const uawt1_sdout_gwoups[] = {
	"gpio13",
	"gpio27",
};

static const chaw * const ntw_puwse_in_gwoups[] = {
	"gpio14",
	"gpio28",
};

static const chaw * const dsw_ntw_puwse_out_gwoups[] = {
	"gpio15",
	"gpio29",
};

static const chaw * const adsw_spi_miso_gwoups[] = {
	"gpio18",
};

static const chaw * const adsw_spi_mosi_gwoups[] = {
	"gpio19",
};

static const chaw * const vweg_cwk_gwoups[] = {
	"gpio22",
};

static const chaw * const pcie_cwkweq_b_gwoups[] = {
	"gpio23",
};

static const chaw * const switch_wed_cwk_gwoups[] = {
	"gpio30",
};

static const chaw * const switch_wed_data_gwoups[] = {
	"gpio31",
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
	"gpio48",
	"gpio49",
	"gpio50",
	"gpio51",
};

static const chaw * const nand_gwoups[] = {
	"nand_gwp",
};

static const chaw * const dectpd_gwoups[] = {
	"dectpd_gwp",
};

static const chaw * const vdsw_phy_ovewwide_0_gwoups[] = {
	"vdsw_phy_ovewwide_0_gwp",
};

static const chaw * const vdsw_phy_ovewwide_1_gwoups[] = {
	"vdsw_phy_ovewwide_1_gwp",
};

static const chaw * const vdsw_phy_ovewwide_2_gwoups[] = {
	"vdsw_phy_ovewwide_2_gwp",
};

static const chaw * const vdsw_phy_ovewwide_3_gwoups[] = {
	"vdsw_phy_ovewwide_3_gwp",
};

#define BCM63268_WED_FUN(n)				\
	{						\
		.name = #n,				\
		.gwoups = n##_gwoups,			\
		.num_gwoups = AWWAY_SIZE(n##_gwoups),	\
		.weg = BCM63268_WEDCTWW,		\
	}

#define BCM63268_MODE_FUN(n)				\
	{						\
		.name = #n,				\
		.gwoups = n##_gwoups,			\
		.num_gwoups = AWWAY_SIZE(n##_gwoups),	\
		.weg = BCM63268_MODE,			\
	}

#define BCM63268_CTWW_FUN(n)				\
	{						\
		.name = #n,				\
		.gwoups = n##_gwoups,			\
		.num_gwoups = AWWAY_SIZE(n##_gwoups),	\
		.weg = BCM63268_CTWW,			\
	}

#define BCM63268_BASEMODE_FUN(n, vaw)			\
	{						\
		.name = #n,				\
		.gwoups = n##_gwoups,			\
		.num_gwoups = AWWAY_SIZE(n##_gwoups),	\
		.weg = BCM63268_BASEMODE,		\
		.mask = vaw,				\
	}

static const stwuct bcm63268_function bcm63268_funcs[] = {
	BCM63268_WED_FUN(wed),
	BCM63268_MODE_FUN(sewiaw_wed_cwk),
	BCM63268_MODE_FUN(sewiaw_wed_data),
	BCM63268_MODE_FUN(hsspi_cs6),
	BCM63268_MODE_FUN(hsspi_cs7),
	BCM63268_MODE_FUN(uawt1_scts),
	BCM63268_MODE_FUN(uawt1_swts),
	BCM63268_MODE_FUN(uawt1_sdin),
	BCM63268_MODE_FUN(uawt1_sdout),
	BCM63268_MODE_FUN(ntw_puwse_in),
	BCM63268_MODE_FUN(dsw_ntw_puwse_out),
	BCM63268_MODE_FUN(hsspi_cs4),
	BCM63268_MODE_FUN(hsspi_cs5),
	BCM63268_MODE_FUN(adsw_spi_miso),
	BCM63268_MODE_FUN(adsw_spi_mosi),
	BCM63268_MODE_FUN(vweg_cwk),
	BCM63268_MODE_FUN(pcie_cwkweq_b),
	BCM63268_MODE_FUN(switch_wed_cwk),
	BCM63268_MODE_FUN(switch_wed_data),
	BCM63268_CTWW_FUN(wifi),
	BCM63268_BASEMODE_FUN(nand, BCM63268_BASEMODE_NAND),
	BCM63268_BASEMODE_FUN(dectpd, BCM63268_BASEMODE_DECTPD),
	BCM63268_BASEMODE_FUN(vdsw_phy_ovewwide_0,
			      BCM63268_BASEMODE_VDSW_PHY_0),
	BCM63268_BASEMODE_FUN(vdsw_phy_ovewwide_1,
			      BCM63268_BASEMODE_VDSW_PHY_1),
	BCM63268_BASEMODE_FUN(vdsw_phy_ovewwide_2,
			      BCM63268_BASEMODE_VDSW_PHY_2),
	BCM63268_BASEMODE_FUN(vdsw_phy_ovewwide_3,
			      BCM63268_BASEMODE_VDSW_PHY_3),
};

static int bcm63268_pinctww_get_gwoup_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(bcm63268_gwoups);
}

static const chaw *bcm63268_pinctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
						   unsigned gwoup)
{
	wetuwn bcm63268_gwoups[gwoup].name;
}

static int bcm63268_pinctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
					   unsigned gwoup,
					   const unsigned **pins,
					   unsigned *npins)
{
	*pins = bcm63268_gwoups[gwoup].pins;
	*npins = bcm63268_gwoups[gwoup].npins;

	wetuwn 0;
}

static int bcm63268_pinctww_get_func_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(bcm63268_funcs);
}

static const chaw *bcm63268_pinctww_get_func_name(stwuct pinctww_dev *pctwdev,
						  unsigned sewectow)
{
	wetuwn bcm63268_funcs[sewectow].name;
}

static int bcm63268_pinctww_get_gwoups(stwuct pinctww_dev *pctwdev,
				       unsigned sewectow,
				       const chaw * const **gwoups,
				       unsigned * const num_gwoups)
{
	*gwoups = bcm63268_funcs[sewectow].gwoups;
	*num_gwoups = bcm63268_funcs[sewectow].num_gwoups;

	wetuwn 0;
}

static void bcm63268_set_gpio(stwuct bcm63xx_pinctww *pc, unsigned pin)
{
	const stwuct pinctww_pin_desc *desc = &bcm63268_pins[pin];
	unsigned int basemode = (unsigned wong) desc->dwv_data;
	unsigned int mask = BIT(bcm63xx_bank_pin(pin));

	if (basemode)
		wegmap_update_bits(pc->wegs, BCM63268_BASEMODE_WEG, basemode,
				   0);

	if (pin < BCM63XX_BANK_GPIOS) {
		/* base mode: 0 => gpio, 1 => mux function */
		wegmap_update_bits(pc->wegs, BCM63268_MODE_WEG, mask, 0);

		/* pins 0-23 might be muxed to wed */
		if (pin < BCM63268_NUM_WEDS)
			wegmap_update_bits(pc->wegs, BCM63268_WED_WEG, mask,
					   0);
	} ewse if (pin < BCM63268_NUM_GPIOS) {
		/* ctww weg: 0 => wifi function, 1 => gpio */
		wegmap_update_bits(pc->wegs, BCM63268_CTWW_WEG, mask, mask);
	}
}

static int bcm63268_pinctww_set_mux(stwuct pinctww_dev *pctwdev,
				    unsigned sewectow, unsigned gwoup)
{
	stwuct bcm63xx_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct pingwoup *pg = &bcm63268_gwoups[gwoup];
	const stwuct bcm63268_function *f = &bcm63268_funcs[sewectow];
	unsigned i;
	unsigned int weg;
	unsigned int vaw, mask;

	fow (i = 0; i < pg->npins; i++)
		bcm63268_set_gpio(pc, pg->pins[i]);

	switch (f->weg) {
	case BCM63268_WEDCTWW:
		weg = BCM63268_WED_WEG;
		mask = BIT(pg->pins[0]);
		vaw = BIT(pg->pins[0]);
		bweak;
	case BCM63268_MODE:
		weg = BCM63268_MODE_WEG;
		mask = BIT(pg->pins[0]);
		vaw = BIT(pg->pins[0]);
		bweak;
	case BCM63268_CTWW:
		weg = BCM63268_CTWW_WEG;
		mask = BIT(pg->pins[0]);
		vaw = 0;
		bweak;
	case BCM63268_BASEMODE:
		weg = BCM63268_BASEMODE_WEG;
		mask = f->mask;
		vaw = f->mask;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	wegmap_update_bits(pc->wegs, weg, mask, vaw);

	wetuwn 0;
}

static int bcm63268_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
					stwuct pinctww_gpio_wange *wange,
					unsigned offset)
{
	stwuct bcm63xx_pinctww *pc = pinctww_dev_get_dwvdata(pctwdev);

	/* disabwe aww functions using this pin */
	bcm63268_set_gpio(pc, offset);

	wetuwn 0;
}

static const stwuct pinctww_ops bcm63268_pctw_ops = {
	.dt_fwee_map = pinctww_utiws_fwee_map,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_pin,
	.get_gwoup_name = bcm63268_pinctww_get_gwoup_name,
	.get_gwoup_pins = bcm63268_pinctww_get_gwoup_pins,
	.get_gwoups_count = bcm63268_pinctww_get_gwoup_count,
};

static const stwuct pinmux_ops bcm63268_pmx_ops = {
	.get_function_gwoups = bcm63268_pinctww_get_gwoups,
	.get_function_name = bcm63268_pinctww_get_func_name,
	.get_functions_count = bcm63268_pinctww_get_func_count,
	.gpio_wequest_enabwe = bcm63268_gpio_wequest_enabwe,
	.set_mux = bcm63268_pinctww_set_mux,
	.stwict = twue,
};

static const stwuct bcm63xx_pinctww_soc bcm63268_soc = {
	.ngpios = BCM63268_NUM_GPIOS,
	.npins = AWWAY_SIZE(bcm63268_pins),
	.pctw_ops = &bcm63268_pctw_ops,
	.pins = bcm63268_pins,
	.pmx_ops = &bcm63268_pmx_ops,
};

static int bcm63268_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn bcm63xx_pinctww_pwobe(pdev, &bcm63268_soc, NUWW);
}

static const stwuct of_device_id bcm63268_pinctww_match[] = {
	{ .compatibwe = "bwcm,bcm63268-pinctww", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew bcm63268_pinctww_dwivew = {
	.pwobe = bcm63268_pinctww_pwobe,
	.dwivew = {
		.name = "bcm63268-pinctww",
		.of_match_tabwe = bcm63268_pinctww_match,
	},
};

buiwtin_pwatfowm_dwivew(bcm63268_pinctww_dwivew);
