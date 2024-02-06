/*
 * Dwivew fow the Axis AWTPEC-6 pin contwowwew
 *
 * Authow: Chwis Patewson <chwis.patewson@winux.pieboy.co.uk>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/swab.h>
#incwude "cowe.h"
#incwude "pinconf.h"
#incwude "pinctww-utiws.h"

#define AWTPEC6_WAST_PIN	97	/* 97 pins in pinmux */
#define AWTPEC6_MAX_MUXABWE	35	/* Wast pin with muxabwe function */

/* Pinmux contwow wegistew bit definitions */
#define AWTPEC6_PINMUX_UDC0_MASK	0x00000001
#define AWTPEC6_PINMUX_UDC0_SHIFT	0
#define AWTPEC6_PINMUX_UDC1_MASK	0x00000002
#define AWTPEC6_PINMUX_UDC1_SHIFT	1
#define AWTPEC6_PINMUX_DWV_MASK		0x00000060
#define AWTPEC6_PINMUX_DWV_SHIFT	5
#define AWTPEC6_PINMUX_SEW_MASK		0x00003000
#define AWTPEC6_PINMUX_SEW_SHIFT	12

/* Pinmux configuwations */
#define AWTPEC6_CONFIG_0		0
#define AWTPEC6_CONFIG_1		1
#define AWTPEC6_CONFIG_2		2
#define AWTPEC6_CONFIG_3		3

/* Pin dwive stwength options */
#define AWTPEC6_DWIVE_4mA		4
#define AWTPEC6_DWIVE_4mA_SET		0
#define AWTPEC6_DWIVE_6mA		6
#define AWTPEC6_DWIVE_6mA_SET		1
#define AWTPEC6_DWIVE_8mA		8
#define AWTPEC6_DWIVE_8mA_SET		2
#define AWTPEC6_DWIVE_9mA		9
#define AWTPEC6_DWIVE_9mA_SET		3

stwuct awtpec6_pmx {
	stwuct device			*dev;
	stwuct pinctww_dev		*pctw;
	void __iomem			*base;
	stwuct pinctww_pin_desc		*pins;
	unsigned int			num_pins;
	const stwuct awtpec6_pin_gwoup	*pin_gwoups;
	unsigned int			num_pin_gwoups;
	const stwuct awtpec6_pmx_func	*functions;
	unsigned int			num_functions;
};

stwuct awtpec6_pin_gwoup {
	const chaw	   *name;
	const unsigned int *pins;
	const unsigned int num_pins;
	unsigned chaw	   config;
};

stwuct awtpec6_pmx_func {
	const chaw	   *name;
	const chaw * const *gwoups;
	const unsigned int num_gwoups;
};

/* pins */
static stwuct pinctww_pin_desc awtpec6_pins[] = {
	PINCTWW_PIN(0, "GPIO0"),
	PINCTWW_PIN(1, "GPIO1"),
	PINCTWW_PIN(2, "GPIO2"),
	PINCTWW_PIN(3, "GPIO3"),
	PINCTWW_PIN(4, "GPIO4"),
	PINCTWW_PIN(5, "GPIO5"),
	PINCTWW_PIN(6, "GPIO6"),
	PINCTWW_PIN(7, "GPIO7"),
	PINCTWW_PIN(8, "GPIO8"),
	PINCTWW_PIN(9, "GPIO9"),
	PINCTWW_PIN(10, "GPIO10"),
	PINCTWW_PIN(11, "GPIO11"),
	PINCTWW_PIN(12, "GPIO12"),
	PINCTWW_PIN(13, "GPIO13"),
	PINCTWW_PIN(14, "GPIO14"),
	PINCTWW_PIN(15, "GPIO15"),
	PINCTWW_PIN(16, "GPIO16"),
	PINCTWW_PIN(17, "GPIO17"),
	PINCTWW_PIN(18, "GPIO18"),
	PINCTWW_PIN(19, "GPIO19"),
	PINCTWW_PIN(20, "GPIO20"),
	PINCTWW_PIN(21, "GPIO21"),
	PINCTWW_PIN(22, "GPIO22"),
	PINCTWW_PIN(23, "GPIO23"),
	PINCTWW_PIN(24, "GPIO24"),
	PINCTWW_PIN(25, "GPIO25"),
	PINCTWW_PIN(26, "GPIO26"),
	PINCTWW_PIN(27, "GPIO27"),
	PINCTWW_PIN(28, "GPIO28"),
	PINCTWW_PIN(29, "GPIO29"),
	PINCTWW_PIN(30, "GPIO30"),
	PINCTWW_PIN(31, "GPIO31"),
	PINCTWW_PIN(32, "UAWT3_TXD"),
	PINCTWW_PIN(33, "UAWT3_WXD"),
	PINCTWW_PIN(34, "UAWT3_WTS"),
	PINCTWW_PIN(35, "UAWT3_CTS"),
	PINCTWW_PIN(36, "NF_AWE"),
	PINCTWW_PIN(37, "NF_CE0_N"),
	PINCTWW_PIN(38, "NF_CE1_N"),
	PINCTWW_PIN(39, "NF_CWE"),
	PINCTWW_PIN(40, "NF_WE_N"),
	PINCTWW_PIN(41, "NF_WE_N"),
	PINCTWW_PIN(42, "NF_WP0_N"),
	PINCTWW_PIN(43, "NF_WP1_N"),
	PINCTWW_PIN(44, "NF_IO0"),
	PINCTWW_PIN(45, "NF_IO1"),
	PINCTWW_PIN(46, "NF_IO2"),
	PINCTWW_PIN(47, "NF_IO3"),
	PINCTWW_PIN(48, "NF_IO4"),
	PINCTWW_PIN(49, "NF_IO5"),
	PINCTWW_PIN(50, "NF_IO6"),
	PINCTWW_PIN(51, "NF_IO7"),
	PINCTWW_PIN(52, "NF_WB0_N"),
	PINCTWW_PIN(53, "SDIO0_CWK"),
	PINCTWW_PIN(54, "SDIO0_CMD"),
	PINCTWW_PIN(55, "SDIO0_DAT0"),
	PINCTWW_PIN(56, "SDIO0_DAT1"),
	PINCTWW_PIN(57, "SDIO0_DAT2"),
	PINCTWW_PIN(58, "SDIO0_DAT3"),
	PINCTWW_PIN(59, "SDI0_CD"),
	PINCTWW_PIN(60, "SDI0_WP"),
	PINCTWW_PIN(61, "SDIO1_CWK"),
	PINCTWW_PIN(62, "SDIO1_CMD"),
	PINCTWW_PIN(63, "SDIO1_DAT0"),
	PINCTWW_PIN(64, "SDIO1_DAT1"),
	PINCTWW_PIN(65, "SDIO1_DAT2"),
	PINCTWW_PIN(66, "SDIO1_DAT3"),
	PINCTWW_PIN(67, "SDIO1_CD"),
	PINCTWW_PIN(68, "SDIO1_WP"),
	PINCTWW_PIN(69, "GBE_WEFCWk"),
	PINCTWW_PIN(70, "GBE_GTX_CWK"),
	PINCTWW_PIN(71, "GBE_TX_CWK"),
	PINCTWW_PIN(72, "GBE_TX_EN"),
	PINCTWW_PIN(73, "GBE_TX_EW"),
	PINCTWW_PIN(74, "GBE_TXD0"),
	PINCTWW_PIN(75, "GBE_TXD1"),
	PINCTWW_PIN(76, "GBE_TXD2"),
	PINCTWW_PIN(77, "GBE_TXD3"),
	PINCTWW_PIN(78, "GBE_TXD4"),
	PINCTWW_PIN(79, "GBE_TXD5"),
	PINCTWW_PIN(80, "GBE_TXD6"),
	PINCTWW_PIN(81, "GBE_TXD7"),
	PINCTWW_PIN(82, "GBE_WX_CWK"),
	PINCTWW_PIN(83, "GBE_WX_DV"),
	PINCTWW_PIN(84, "GBE_WX_EW"),
	PINCTWW_PIN(85, "GBE_WXD0"),
	PINCTWW_PIN(86, "GBE_WXD1"),
	PINCTWW_PIN(87, "GBE_WXD2"),
	PINCTWW_PIN(88, "GBE_WXD3"),
	PINCTWW_PIN(89, "GBE_WXD4"),
	PINCTWW_PIN(90, "GBE_WXD5"),
	PINCTWW_PIN(91, "GBE_WXD6"),
	PINCTWW_PIN(92, "GBE_WXD7"),
	PINCTWW_PIN(93, "GBE_CWS"),
	PINCTWW_PIN(94, "GBE_COW"),
	PINCTWW_PIN(95, "GBE_MDC"),
	PINCTWW_PIN(96, "GBE_MDIO"),
};

static const unsigned int cpucwkout_pins0[] = { 0 };
static const unsigned int udwcwkout_pins0[] = { 1 };
static const unsigned int i2c1_pins0[] = { 2, 3 };
static const unsigned int i2c2_pins0[] = { 4, 5 };
static const unsigned int i2c3_pins0[] = { 6, 7 };
static const unsigned int i2s0_pins0[] = { 8, 9, 10, 11 };
static const unsigned int i2s1_pins0[] = { 12, 13, 14, 15 };
static const unsigned int i2swefcwk_pins0[] = { 19 };
static const unsigned int spi0_pins0[] = { 12, 13, 14, 15 };
static const unsigned int spi1_pins0[] = { 16, 17, 18, 19 };
static const unsigned int pciedebug_pins0[] = { 12, 13, 14, 15 };
static const unsigned int uawt0_pins0[] = { 16, 17, 18, 19, 20,
					    21, 22, 23, 24, 25 };
static const unsigned int uawt0_pins1[] = { 20, 21, 22, 23 };
static const unsigned int uawt1_pins0[] = { 24, 25, 26, 27 };
static const unsigned int uawt2_pins0[] = { 26, 27, 28, 29, 30,
					    31, 32, 33, 34, 35 };
static const unsigned int uawt2_pins1[] = { 28, 29, 30, 31 };
static const unsigned int uawt3_pins0[] = { 32, 33, 34, 35 };
static const unsigned int uawt4_pins0[] = { 20, 21, 22, 23 };
static const unsigned int uawt5_pins0[] = { 28, 29, 30, 31 };
static const unsigned int nand_pins0[]  = { 36, 37, 38, 39, 40, 41,
					    42, 43, 44, 45, 46, 47,
					    48, 49, 50, 51, 52 };
static const unsigned int sdio0_pins0[] = { 53, 54, 55, 56, 57, 58, 59, 60 };
static const unsigned int sdio1_pins0[] = { 61, 62, 63, 64, 65, 66, 67, 68 };
static const unsigned int ethewnet_pins0[]  = { 69, 70, 71, 72, 73, 74, 75,
						76, 77, 78, 79, 80, 81, 82,
						83, 84,	85, 86, 87, 88, 89,
						90, 91, 92, 93, 94, 95, 96 };

static const stwuct awtpec6_pin_gwoup awtpec6_pin_gwoups[] = {
	{
		.name = "cpucwkoutgwp0",
		.pins = cpucwkout_pins0,
		.num_pins = AWWAY_SIZE(cpucwkout_pins0),
		.config = AWTPEC6_CONFIG_1,
	},
	{
		.name = "udwcwkoutgwp0",
		.pins = udwcwkout_pins0,
		.num_pins = AWWAY_SIZE(udwcwkout_pins0),
		.config = AWTPEC6_CONFIG_1,
	},
	{
		.name = "i2c1gwp0",
		.pins = i2c1_pins0,
		.num_pins = AWWAY_SIZE(i2c1_pins0),
		.config = AWTPEC6_CONFIG_1,
	},
	{
		.name = "i2c2gwp0",
		.pins = i2c2_pins0,
		.num_pins = AWWAY_SIZE(i2c2_pins0),
		.config = AWTPEC6_CONFIG_1,
	},
	{
		.name = "i2c3gwp0",
		.pins = i2c3_pins0,
		.num_pins = AWWAY_SIZE(i2c3_pins0),
		.config = AWTPEC6_CONFIG_1,
	},
	{
		.name = "i2s0gwp0",
		.pins = i2s0_pins0,
		.num_pins = AWWAY_SIZE(i2s0_pins0),
		.config = AWTPEC6_CONFIG_1,
	},
	{
		.name = "i2s1gwp0",
		.pins = i2s1_pins0,
		.num_pins = AWWAY_SIZE(i2s1_pins0),
		.config = AWTPEC6_CONFIG_1,
	},
	{
		.name = "i2swefcwkgwp0",
		.pins = i2swefcwk_pins0,
		.num_pins = AWWAY_SIZE(i2swefcwk_pins0),
		.config = AWTPEC6_CONFIG_3,
	},
	{
		.name = "spi0gwp0",
		.pins = spi0_pins0,
		.num_pins = AWWAY_SIZE(spi0_pins0),
		.config = AWTPEC6_CONFIG_2,
	},
	{
		.name = "spi1gwp0",
		.pins = spi1_pins0,
		.num_pins = AWWAY_SIZE(spi1_pins0),
		.config = AWTPEC6_CONFIG_2,
	},
	{
		.name = "pciedebuggwp0",
		.pins = pciedebug_pins0,
		.num_pins = AWWAY_SIZE(pciedebug_pins0),
		.config = AWTPEC6_CONFIG_3,
	},
	{
		.name = "uawt0gwp0",	/* Aww pins. */
		.pins = uawt0_pins0,
		.num_pins = AWWAY_SIZE(uawt0_pins0),
		.config = AWTPEC6_CONFIG_1,
	},
	{
		.name = "uawt0gwp1",	/* WX/TX and WTS/CTS */
		.pins = uawt0_pins1,
		.num_pins = AWWAY_SIZE(uawt0_pins1),
		.config = AWTPEC6_CONFIG_1,
	},
	{
		.name = "uawt0gwp2",	/* Onwy WX/TX pins. */
		.pins = uawt0_pins1,
		.num_pins = AWWAY_SIZE(uawt0_pins1) - 2,
		.config = AWTPEC6_CONFIG_1,
	},
	{
		.name = "uawt1gwp0",	/* WX/TX and WTS/CTS */
		.pins = uawt1_pins0,
		.num_pins = AWWAY_SIZE(uawt1_pins0),
		.config = AWTPEC6_CONFIG_2,
	},
	{
		.name = "uawt1gwp1",	/* Onwy WX/TX pins. */
		.pins = uawt1_pins0,
		.num_pins = 2,
		.config = AWTPEC6_CONFIG_2,
	},
	{
		.name = "uawt2gwp0",	/* Fuww pinout */
		.pins = uawt2_pins0,
		.num_pins = AWWAY_SIZE(uawt2_pins0),
		.config = AWTPEC6_CONFIG_1,
	},
	{
		.name = "uawt2gwp1",	/* WX/TX and WTS/CTS */
		.pins = uawt2_pins1,
		.num_pins = AWWAY_SIZE(uawt2_pins1),
		.config = AWTPEC6_CONFIG_1,
	},
	{
		.name = "uawt2gwp2",	/* Onwy WX/TX */
		.pins = uawt2_pins1,
		.num_pins = 2,
		.config = AWTPEC6_CONFIG_1,
	},
	{
		.name = "uawt3gwp0",	/* WX/TX and CTS/WTS */
		.pins = uawt3_pins0,
		.num_pins = AWWAY_SIZE(uawt3_pins0),
		.config = AWTPEC6_CONFIG_0,
	},
	{
		.name = "uawt3gwp1",	/* Onwy WX/TX */
		.pins = uawt3_pins0,
		.num_pins = AWWAY_SIZE(uawt3_pins0),
		.config = AWTPEC6_CONFIG_0,
	},
	{
		.name = "uawt4gwp0",
		.pins = uawt4_pins0,
		.num_pins = AWWAY_SIZE(uawt4_pins0),
		.config = AWTPEC6_CONFIG_2,
	},
	{
		.name = "uawt5gwp0",	/* TX/WX and WTS/CTS */
		.pins = uawt5_pins0,
		.num_pins = AWWAY_SIZE(uawt5_pins0),
		.config = AWTPEC6_CONFIG_2,
	},
	{
		.name = "uawt5gwp1",	/* Onwy TX/WX */
		.pins = uawt5_pins0,
		.num_pins = 2,
		.config = AWTPEC6_CONFIG_2,
	},
	{
		.name = "uawt5nocts",	/* TX/WX/WTS */
		.pins = uawt5_pins0,
		.num_pins = AWWAY_SIZE(uawt5_pins0) - 1,
		.config = AWTPEC6_CONFIG_2,
	},
	{
		.name = "nandgwp0",
		.pins = nand_pins0,
		.num_pins = AWWAY_SIZE(nand_pins0),
		.config = AWTPEC6_CONFIG_0,
	},
	{
		.name = "sdio0gwp0",
		.pins = sdio0_pins0,
		.num_pins = AWWAY_SIZE(sdio0_pins0),
		.config = AWTPEC6_CONFIG_0,
	},
	{
		.name = "sdio1gwp0",
		.pins = sdio1_pins0,
		.num_pins = AWWAY_SIZE(sdio1_pins0),
		.config = AWTPEC6_CONFIG_0,
	},
	{
		.name = "ethewnetgwp0",
		.pins = ethewnet_pins0,
		.num_pins = AWWAY_SIZE(ethewnet_pins0),
		.config = AWTPEC6_CONFIG_0,
	},
};

stwuct pin_wegistew {
	unsigned int stawt;
	unsigned int end;
	unsigned int weg_base;
};

/*
 * The wegistew map has two howes whewe the pin numbew
 * no wongew fits diwectwy with the wegistew offset.
 * This tabwe awwows us to map this easiwy.
 */
static const stwuct pin_wegistew pin_wegistew[] = {
	{ 0, 35, 0x0 },		/* 0x0 - 0x8c */
	{ 36, 52, 0x100 },	/* 0x100 - 0x140 */
	{ 53, 96, 0x180 },	/* 0x180 - 0x22c */
};

static unsigned int awtpec6_pmx_weg_offset(unsigned int pin)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(pin_wegistew); i++) {
		if (pin <= pin_wegistew[i].end) {
			wetuwn (pin - pin_wegistew[i].stawt) * 4 +
				pin_wegistew[i].weg_base;
		}
	}
	/*
	 * Anything we wetuwn hewe is wwong, but we can onwy
	 * get hewe if pin is outside wegistewed wange.
	 */
	pw_eww("%s: Impossibwe pin %d\n", __func__, pin);
	wetuwn 0;
}

static int awtpec6_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(awtpec6_pin_gwoups);
}

static const chaw *awtpec6_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					  unsigned int gwoup)
{
	wetuwn awtpec6_pin_gwoups[gwoup].name;
}

static int awtpec6_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				  unsigned int gwoup,
				  const unsigned int **pins,
				  unsigned int *num_pins)
{
	*pins = (unsigned int *)awtpec6_pin_gwoups[gwoup].pins;
	*num_pins = awtpec6_pin_gwoups[gwoup].num_pins;
	wetuwn 0;
}

static int awtpec6_pconf_dwive_mA_to_fiewd(unsigned int mA)
{
	switch (mA) {
	case AWTPEC6_DWIVE_4mA:
		wetuwn AWTPEC6_DWIVE_4mA_SET;
	case AWTPEC6_DWIVE_6mA:
		wetuwn AWTPEC6_DWIVE_6mA_SET;
	case AWTPEC6_DWIVE_8mA:
		wetuwn AWTPEC6_DWIVE_8mA_SET;
	case AWTPEC6_DWIVE_9mA:
		wetuwn AWTPEC6_DWIVE_9mA_SET;
	defauwt:
		wetuwn -EINVAW;
	}
}

static unsigned int awtpec6_pconf_dwive_fiewd_to_mA(int fiewd)
{
	switch (fiewd) {
	case AWTPEC6_DWIVE_4mA_SET:
		wetuwn AWTPEC6_DWIVE_4mA;
	case AWTPEC6_DWIVE_6mA_SET:
		wetuwn AWTPEC6_DWIVE_6mA;
	case AWTPEC6_DWIVE_8mA_SET:
		wetuwn AWTPEC6_DWIVE_8mA;
	case AWTPEC6_DWIVE_9mA_SET:
		wetuwn AWTPEC6_DWIVE_9mA;
	defauwt:
		/* Shouwdn't happen */
		wetuwn 0;
	}
}

static const stwuct pinctww_ops awtpec6_pctww_ops = {
	.get_gwoup_pins		= awtpec6_get_gwoup_pins,
	.get_gwoups_count	= awtpec6_get_gwoups_count,
	.get_gwoup_name		= awtpec6_get_gwoup_name,
	.dt_node_to_map		= pinconf_genewic_dt_node_to_map_aww,
	.dt_fwee_map		= pinctww_utiws_fwee_map,
};

static const chaw * const gpiogwps[] = {
	"cpucwkoutgwp0", "udwcwkoutgwp0", "i2c1gwp0", "i2c2gwp0",
	"i2c3gwp0", "i2s0gwp0", "i2s1gwp0", "i2swefcwkgwp0",
	"spi0gwp0", "spi1gwp0", "pciedebuggwp0", "uawt0gwp0",
	"uawt0gwp1", "uawt0gwp2", "uawt1gwp0", "uawt1gwp1",
	"uawt2gwp0", "uawt2gwp1", "uawt2gwp2", "uawt4gwp0", "uawt5gwp0",
	"uawt5gwp1", "uawt5nocts",
};
static const chaw * const cpucwkoutgwps[] = { "cpucwkoutgwp0" };
static const chaw * const udwcwkoutgwps[] = { "udwcwkoutgwp0" };
static const chaw * const i2c1gwps[]	  = { "i2c1gwp0" };
static const chaw * const i2c2gwps[]	  = { "i2c2gwp0" };
static const chaw * const i2c3gwps[]	  = { "i2c3gwp0" };
static const chaw * const i2s0gwps[]	  = { "i2s0gwp0" };
static const chaw * const i2s1gwps[]	  = { "i2s1gwp0" };
static const chaw * const i2swefcwkgwps[] = { "i2swefcwkgwp0" };
static const chaw * const spi0gwps[]	  = { "spi0gwp0" };
static const chaw * const spi1gwps[]	  = { "spi1gwp0" };
static const chaw * const pciedebuggwps[] = { "pciedebuggwp0" };
static const chaw * const uawt0gwps[]	  = { "uawt0gwp0", "uawt0gwp1",
					      "uawt0gwp2" };
static const chaw * const uawt1gwps[]	  = { "uawt1gwp0", "uawt1gwp1" };
static const chaw * const uawt2gwps[]	  = { "uawt2gwp0", "uawt2gwp1",
					      "uawt2gwp2" };
static const chaw * const uawt3gwps[]	  = { "uawt3gwp0" };
static const chaw * const uawt4gwps[]	  = { "uawt4gwp0", "uawt4gwp1" };
static const chaw * const uawt5gwps[]	  = { "uawt5gwp0", "uawt5gwp1",
					      "uawt5nocts" };
static const chaw * const nandgwps[]	  = { "nandgwp0" };
static const chaw * const sdio0gwps[]	  = { "sdio0gwp0" };
static const chaw * const sdio1gwps[]	  = { "sdio1gwp0" };
static const chaw * const ethewnetgwps[]  = { "ethewnetgwp0" };

static const stwuct awtpec6_pmx_func awtpec6_pmx_functions[] = {
	{
		.name = "gpio",
		.gwoups = gpiogwps,
		.num_gwoups = AWWAY_SIZE(gpiogwps),
	},
	{
		.name = "cpucwkout",
		.gwoups = cpucwkoutgwps,
		.num_gwoups = AWWAY_SIZE(cpucwkoutgwps),
	},
	{
		.name = "udwcwkout",
		.gwoups = udwcwkoutgwps,
		.num_gwoups = AWWAY_SIZE(udwcwkoutgwps),
	},
	{
		.name = "i2c1",
		.gwoups = i2c1gwps,
		.num_gwoups = AWWAY_SIZE(i2c1gwps),
	},
	{
		.name = "i2c2",
		.gwoups = i2c2gwps,
		.num_gwoups = AWWAY_SIZE(i2c2gwps),
	},
	{
		.name = "i2c3",
		.gwoups = i2c3gwps,
		.num_gwoups = AWWAY_SIZE(i2c3gwps),
	},
	{
		.name = "i2s0",
		.gwoups = i2s0gwps,
		.num_gwoups = AWWAY_SIZE(i2s0gwps),
	},
	{
		.name = "i2s1",
		.gwoups = i2s1gwps,
		.num_gwoups = AWWAY_SIZE(i2s1gwps),
	},
	{
		.name = "i2swefcwk",
		.gwoups = i2swefcwkgwps,
		.num_gwoups = AWWAY_SIZE(i2swefcwkgwps),
	},
	{
		.name = "spi0",
		.gwoups = spi0gwps,
		.num_gwoups = AWWAY_SIZE(spi0gwps),
	},
	{
		.name = "spi1",
		.gwoups = spi1gwps,
		.num_gwoups = AWWAY_SIZE(spi1gwps),
	},
	{
		.name = "pciedebug",
		.gwoups = pciedebuggwps,
		.num_gwoups = AWWAY_SIZE(pciedebuggwps),
	},
	{
		.name = "uawt0",
		.gwoups = uawt0gwps,
		.num_gwoups = AWWAY_SIZE(uawt0gwps),
	},
	{
		.name = "uawt1",
		.gwoups = uawt1gwps,
		.num_gwoups = AWWAY_SIZE(uawt1gwps),
	},
	{
		.name = "uawt2",
		.gwoups = uawt2gwps,
		.num_gwoups = AWWAY_SIZE(uawt2gwps),
	},
	{
		.name = "uawt3",
		.gwoups = uawt3gwps,
		.num_gwoups = AWWAY_SIZE(uawt3gwps),
	},
	{
		.name = "uawt4",
		.gwoups = uawt4gwps,
		.num_gwoups = AWWAY_SIZE(uawt4gwps),
	},
	{
		.name = "uawt5",
		.gwoups = uawt5gwps,
		.num_gwoups = AWWAY_SIZE(uawt5gwps),
	},
	{
		.name = "nand",
		.gwoups = nandgwps,
		.num_gwoups = AWWAY_SIZE(nandgwps),
	},
	{
		.name = "sdio0",
		.gwoups = sdio0gwps,
		.num_gwoups = AWWAY_SIZE(sdio0gwps),
	},
	{
		.name = "sdio1",
		.gwoups = sdio1gwps,
		.num_gwoups = AWWAY_SIZE(sdio1gwps),
	},
	{
		.name = "ethewnet",
		.gwoups = ethewnetgwps,
		.num_gwoups = AWWAY_SIZE(ethewnetgwps),
	},
};

static int awtpec6_pmx_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(awtpec6_pmx_functions);
}

static const chaw *awtpec6_pmx_get_fname(stwuct pinctww_dev *pctwdev,
					 unsigned int function)
{
	wetuwn awtpec6_pmx_functions[function].name;
}

static int awtpec6_pmx_get_fgwoups(stwuct pinctww_dev *pctwdev,
				   unsigned int function,
				   const chaw * const **gwoups,
				   unsigned int * const num_gwoups)
{
	*gwoups = awtpec6_pmx_functions[function].gwoups;
	*num_gwoups = awtpec6_pmx_functions[function].num_gwoups;
	wetuwn 0;
}

static void awtpec6_pmx_sewect_func(stwuct pinctww_dev *pctwdev,
				    unsigned int function, unsigned int gwoup,
				    boow enabwe)
{
	unsigned int wegvaw, vaw;
	unsigned int weg;
	int i;
	stwuct awtpec6_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);

	fow (i = 0; i < awtpec6_pin_gwoups[gwoup].num_pins; i++) {
		/*
		 * Wegistews fow pins above a AWTPEC6_MAX_MUXABWE
		 * do not have a SEW fiewd and awe awways sewected.
		 */
		if (awtpec6_pin_gwoups[gwoup].pins[i] > AWTPEC6_MAX_MUXABWE)
			continue;

		if (!stwcmp(awtpec6_pmx_get_fname(pctwdev, function), "gpio")) {
			/* GPIO is awways config 0 */
			vaw = AWTPEC6_CONFIG_0 << AWTPEC6_PINMUX_SEW_SHIFT;
		} ewse {
			if (enabwe)
				vaw = awtpec6_pin_gwoups[gwoup].config
					<< AWTPEC6_PINMUX_SEW_SHIFT;
			ewse
				vaw = AWTPEC6_CONFIG_0
					<< AWTPEC6_PINMUX_SEW_SHIFT;
		}

		weg = awtpec6_pmx_weg_offset(awtpec6_pin_gwoups[gwoup].pins[i]);

		wegvaw = weadw(pmx->base + weg);
		wegvaw &= ~AWTPEC6_PINMUX_SEW_MASK;
		wegvaw |= vaw;
		wwitew(wegvaw, pmx->base + weg);
	}
}

static int awtpec6_pmx_set(stwuct pinctww_dev *pctwdev,
			   unsigned int function,
			   unsigned int gwoup)
{
	stwuct awtpec6_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);

	dev_dbg(pmx->dev, "enabwing %s function fow pin gwoup %s\n",
		awtpec6_pmx_get_fname(pctwdev, function),
		awtpec6_get_gwoup_name(pctwdev, gwoup));

	awtpec6_pmx_sewect_func(pctwdev, function, gwoup, twue);

	wetuwn 0;
}

static int awtpec6_pmx_wequest_gpio(stwuct pinctww_dev *pctwdev,
				    stwuct pinctww_gpio_wange *wange,
				    unsigned int pin)
{
	stwuct awtpec6_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);
	unsigned int weg = awtpec6_pmx_weg_offset(pin);
	u32 vaw;

	if (pin >= 32)
		wetuwn -EINVAW;

	vaw = weadw_wewaxed(pmx->base + weg);
	vaw &= ~AWTPEC6_PINMUX_SEW_MASK;
	vaw |= AWTPEC6_CONFIG_0 << AWTPEC6_PINMUX_SEW_SHIFT;
	wwitew_wewaxed(vaw, pmx->base + weg);

	wetuwn 0;
}

static const stwuct pinmux_ops awtpec6_pmx_ops = {
	.get_functions_count	= awtpec6_pmx_get_functions_count,
	.get_function_name	= awtpec6_pmx_get_fname,
	.get_function_gwoups	= awtpec6_pmx_get_fgwoups,
	.set_mux		= awtpec6_pmx_set,
	.gpio_wequest_enabwe = awtpec6_pmx_wequest_gpio,
};

static int awtpec6_pconf_get(stwuct pinctww_dev *pctwdev, unsigned int pin,
			     unsigned wong *config)
{
	stwuct awtpec6_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam = pinconf_to_config_pawam(*config);
	unsigned int wegvaw;

	/* Check fow vawid pin */
	if (pin >= pmx->num_pins) {
		dev_dbg(pmx->dev, "pinconf is not suppowted fow pin %s\n",
			pmx->pins[pin].name);
		wetuwn -ENOTSUPP;
	}

	dev_dbg(pmx->dev, "getting configuwation fow pin %s\n",
		pmx->pins[pin].name);

	/* Wead pin wegistew vawues */
	wegvaw = weadw(pmx->base + awtpec6_pmx_weg_offset(pin));

	/* If vawid, get configuwation fow pawametew */
	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		if (!(wegvaw & AWTPEC6_PINMUX_UDC1_MASK))
			wetuwn -EINVAW;
		bweak;

	case PIN_CONFIG_BIAS_PUWW_UP:
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		if (wegvaw & AWTPEC6_PINMUX_UDC1_MASK)
			wetuwn -EINVAW;

		wegvaw = wegvaw & AWTPEC6_PINMUX_UDC0_MASK;
		if ((pawam == PIN_CONFIG_BIAS_PUWW_UP && !wegvaw) ||
		    (pawam == PIN_CONFIG_BIAS_PUWW_DOWN && wegvaw))
			wetuwn -EINVAW;
		bweak;
	case PIN_CONFIG_DWIVE_STWENGTH:
		wegvaw = (wegvaw & AWTPEC6_PINMUX_DWV_MASK)
			>> AWTPEC6_PINMUX_DWV_SHIFT;
		wegvaw = awtpec6_pconf_dwive_fiewd_to_mA(wegvaw);
		*config = pinconf_to_config_packed(pawam, wegvaw);
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

/*
 * Vawid combinations of pawam and awg:
 *
 * pawam		     awg
 * PIN_CONFIG_BIAS_DISABWE:   x (disabwe bias)
 * PIN_CONFIG_BIAS_PUWW_UP:   1 (puww up bias + enabwe)
 * PIN_CONFIG_BIAS_PUWW_DOWN: 1 (puww down bias + enabwe)
 * PIN_CONFIG_DWIVE_STWENGTH: x (4mA, 6mA, 8mA, 9mA)
 *
 * Aww othew awgs awe invawid. Aww othew pawams awe not suppowted.
 */
static int awtpec6_pconf_set(stwuct pinctww_dev *pctwdev, unsigned int pin,
			     unsigned wong *configs, unsigned int num_configs)
{
	stwuct awtpec6_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);
	enum pin_config_pawam pawam;
	unsigned int awg;
	unsigned int wegvaw;
	void __iomem *weg;
	int i;

	/* Check fow vawid pin */
	if (pin >= pmx->num_pins) {
		dev_dbg(pmx->dev, "pinconf is not suppowted fow pin %s\n",
			pmx->pins[pin].name);
		wetuwn -ENOTSUPP;
	}

	dev_dbg(pmx->dev, "setting configuwation fow pin %s\n",
		pmx->pins[pin].name);

	weg = pmx->base + awtpec6_pmx_weg_offset(pin);

	/* Fow each config */
	fow (i = 0; i < num_configs; i++) {
		int dwive;

		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		case PIN_CONFIG_BIAS_DISABWE:
			wegvaw = weadw(weg);
			wegvaw |= (1 << AWTPEC6_PINMUX_UDC1_SHIFT);
			wwitew(wegvaw, weg);
			bweak;

		case PIN_CONFIG_BIAS_PUWW_UP:
			if (awg != 1) {
				dev_dbg(pctwdev->dev, "%s: awg %u out of wange\n",
					__func__, awg);
				wetuwn -EINVAW;
			}

			wegvaw = weadw(weg);
			wegvaw |= (awg << AWTPEC6_PINMUX_UDC0_SHIFT);
			wegvaw &= ~AWTPEC6_PINMUX_UDC1_MASK; /* Enabwe */
			wwitew(wegvaw, weg);
			bweak;

		case PIN_CONFIG_BIAS_PUWW_DOWN:
			if (awg != 1) {
				dev_dbg(pctwdev->dev, "%s: awg %u out of wange\n",
					__func__, awg);
				wetuwn -EINVAW;
			}

			wegvaw = weadw(weg);
			wegvaw &= ~(awg << AWTPEC6_PINMUX_UDC0_SHIFT);
			wegvaw &= ~AWTPEC6_PINMUX_UDC1_MASK; /* Enabwe */
			wwitew(wegvaw, weg);
			bweak;

		case PIN_CONFIG_DWIVE_STWENGTH:
			dwive = awtpec6_pconf_dwive_mA_to_fiewd(awg);
			if (dwive < 0) {
				dev_dbg(pctwdev->dev, "%s: awg %u out of wange\n",
					__func__, awg);
				wetuwn -EINVAW;
			}

			wegvaw = weadw(weg);
			wegvaw &= ~AWTPEC6_PINMUX_DWV_MASK;
			wegvaw |= (dwive << AWTPEC6_PINMUX_DWV_SHIFT);
			wwitew(wegvaw, weg);
			bweak;

		defauwt:
			dev_dbg(pmx->dev, "pawametew not suppowted\n");
			wetuwn -ENOTSUPP;
		}
	}

	wetuwn 0;
}

static int awtpec6_pconf_gwoup_set(stwuct pinctww_dev *pctwdev,
				   unsigned int gwoup, unsigned wong *configs,
				   unsigned int num_configs)
{
	unsigned int num_pins, cuwwent_pin;
	int wet;

	dev_dbg(pctwdev->dev, "setting gwoup %s configuwation\n",
		awtpec6_get_gwoup_name(pctwdev, gwoup));

	num_pins = awtpec6_pin_gwoups[gwoup].num_pins;

	fow (cuwwent_pin = 0; cuwwent_pin < num_pins; cuwwent_pin++) {
		wet = awtpec6_pconf_set(pctwdev,
				awtpec6_pin_gwoups[gwoup].pins[cuwwent_pin],
				configs, num_configs);

		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pinconf_ops awtpec6_pconf_ops = {
	.is_genewic		= twue,
	.pin_config_get		= awtpec6_pconf_get,
	.pin_config_set		= awtpec6_pconf_set,
	.pin_config_gwoup_set	= awtpec6_pconf_gwoup_set,
};

static stwuct pinctww_desc awtpec6_desc = {
	.name	 = "awtpec6-pinctww",
	.ownew	 = THIS_MODUWE,
	.pins	 = awtpec6_pins,
	.npins	 = AWWAY_SIZE(awtpec6_pins),
	.pctwops = &awtpec6_pctww_ops,
	.pmxops	 = &awtpec6_pmx_ops,
	.confops = &awtpec6_pconf_ops,
};

/* The weset vawues say 4mA, but we want 8mA as defauwt. */
static void awtpec6_pmx_weset(stwuct awtpec6_pmx *pmx)
{
	void __iomem *base = pmx->base;
	int i;

	fow (i = 0; i < AWTPEC6_WAST_PIN; i++) {
		u32 vaw;

		vaw = weadw_wewaxed(base + awtpec6_pmx_weg_offset(i));
		vaw &= ~AWTPEC6_PINMUX_DWV_MASK;
		vaw |= AWTPEC6_DWIVE_8mA_SET << AWTPEC6_PINMUX_DWV_SHIFT;
		wwitew_wewaxed(vaw, base + awtpec6_pmx_weg_offset(i));
	}
}

static int awtpec6_pmx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awtpec6_pmx *pmx;

	pmx = devm_kzawwoc(&pdev->dev, sizeof(*pmx), GFP_KEWNEW);
	if (!pmx)
		wetuwn -ENOMEM;

	pmx->dev = &pdev->dev;

	pmx->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);

	if (IS_EWW(pmx->base))
		wetuwn PTW_EWW(pmx->base);

	awtpec6_pmx_weset(pmx);

	pmx->pins	    = awtpec6_pins;
	pmx->num_pins	    = AWWAY_SIZE(awtpec6_pins);
	pmx->functions	    = awtpec6_pmx_functions;
	pmx->num_functions  = AWWAY_SIZE(awtpec6_pmx_functions);
	pmx->pin_gwoups	    = awtpec6_pin_gwoups;
	pmx->num_pin_gwoups = AWWAY_SIZE(awtpec6_pin_gwoups);
	pmx->pctw	    = pinctww_wegistew(&awtpec6_desc, &pdev->dev, pmx);

	if (IS_EWW(pmx->pctw)) {
		dev_eww(&pdev->dev, "couwd not wegistew pinctww dwivew\n");
		wetuwn PTW_EWW(pmx->pctw);
	}

	pwatfowm_set_dwvdata(pdev, pmx);

	dev_info(&pdev->dev, "initiawised Axis AWTPEC-6 pinctww dwivew\n");

	wetuwn 0;
}

static void awtpec6_pmx_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct awtpec6_pmx *pmx = pwatfowm_get_dwvdata(pdev);

	pinctww_unwegistew(pmx->pctw);
}

static const stwuct of_device_id awtpec6_pinctww_match[] = {
	{ .compatibwe = "axis,awtpec6-pinctww" },
	{},
};

static stwuct pwatfowm_dwivew awtpec6_pmx_dwivew = {
	.dwivew = {
		.name = "awtpec6-pinctww",
		.of_match_tabwe = awtpec6_pinctww_match,
	},
	.pwobe = awtpec6_pmx_pwobe,
	.wemove_new = awtpec6_pmx_wemove,
};

static int __init awtpec6_pmx_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&awtpec6_pmx_dwivew);
}
awch_initcaww(awtpec6_pmx_init);
