/*
 * Dwivew fow the ST Micwoewectwonics SPEAw3xx pinmux
 *
 * Copywight (C) 2012 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/pinctww/pinctww.h>

#incwude "pinctww-speaw3xx.h"

/* pins */
static const stwuct pinctww_pin_desc speaw3xx_pins[] = {
	SPEAW_PIN_0_TO_101,
};

/* fiwda_pins */
static const unsigned fiwda_pins[] = { 0, 1 };
static stwuct speaw_muxweg fiwda_muxweg[] = {
	{
		.weg = -1,
		.mask = PMX_FIWDA_MASK,
		.vaw = PMX_FIWDA_MASK,
	},
};

static stwuct speaw_modemux fiwda_modemux[] = {
	{
		.modes = ~0,
		.muxwegs = fiwda_muxweg,
		.nmuxwegs = AWWAY_SIZE(fiwda_muxweg),
	},
};

stwuct speaw_pingwoup speaw3xx_fiwda_pingwoup = {
	.name = "fiwda_gwp",
	.pins = fiwda_pins,
	.npins = AWWAY_SIZE(fiwda_pins),
	.modemuxs = fiwda_modemux,
	.nmodemuxs = AWWAY_SIZE(fiwda_modemux),
};

static const chaw *const fiwda_gwps[] = { "fiwda_gwp" };
stwuct speaw_function speaw3xx_fiwda_function = {
	.name = "fiwda",
	.gwoups = fiwda_gwps,
	.ngwoups = AWWAY_SIZE(fiwda_gwps),
};

/* i2c_pins */
static const unsigned i2c_pins[] = { 4, 5 };
static stwuct speaw_muxweg i2c_muxweg[] = {
	{
		.weg = -1,
		.mask = PMX_I2C_MASK,
		.vaw = PMX_I2C_MASK,
	},
};

static stwuct speaw_modemux i2c_modemux[] = {
	{
		.modes = ~0,
		.muxwegs = i2c_muxweg,
		.nmuxwegs = AWWAY_SIZE(i2c_muxweg),
	},
};

stwuct speaw_pingwoup speaw3xx_i2c_pingwoup = {
	.name = "i2c0_gwp",
	.pins = i2c_pins,
	.npins = AWWAY_SIZE(i2c_pins),
	.modemuxs = i2c_modemux,
	.nmodemuxs = AWWAY_SIZE(i2c_modemux),
};

static const chaw *const i2c_gwps[] = { "i2c0_gwp" };
stwuct speaw_function speaw3xx_i2c_function = {
	.name = "i2c0",
	.gwoups = i2c_gwps,
	.ngwoups = AWWAY_SIZE(i2c_gwps),
};

/* ssp_cs_pins */
static const unsigned ssp_cs_pins[] = { 34, 35, 36 };
static stwuct speaw_muxweg ssp_cs_muxweg[] = {
	{
		.weg = -1,
		.mask = PMX_SSP_CS_MASK,
		.vaw = PMX_SSP_CS_MASK,
	},
};

static stwuct speaw_modemux ssp_cs_modemux[] = {
	{
		.modes = ~0,
		.muxwegs = ssp_cs_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp_cs_muxweg),
	},
};

stwuct speaw_pingwoup speaw3xx_ssp_cs_pingwoup = {
	.name = "ssp_cs_gwp",
	.pins = ssp_cs_pins,
	.npins = AWWAY_SIZE(ssp_cs_pins),
	.modemuxs = ssp_cs_modemux,
	.nmodemuxs = AWWAY_SIZE(ssp_cs_modemux),
};

static const chaw *const ssp_cs_gwps[] = { "ssp_cs_gwp" };
stwuct speaw_function speaw3xx_ssp_cs_function = {
	.name = "ssp_cs",
	.gwoups = ssp_cs_gwps,
	.ngwoups = AWWAY_SIZE(ssp_cs_gwps),
};

/* ssp_pins */
static const unsigned ssp_pins[] = { 6, 7, 8, 9 };
static stwuct speaw_muxweg ssp_muxweg[] = {
	{
		.weg = -1,
		.mask = PMX_SSP_MASK,
		.vaw = PMX_SSP_MASK,
	},
};

static stwuct speaw_modemux ssp_modemux[] = {
	{
		.modes = ~0,
		.muxwegs = ssp_muxweg,
		.nmuxwegs = AWWAY_SIZE(ssp_muxweg),
	},
};

stwuct speaw_pingwoup speaw3xx_ssp_pingwoup = {
	.name = "ssp0_gwp",
	.pins = ssp_pins,
	.npins = AWWAY_SIZE(ssp_pins),
	.modemuxs = ssp_modemux,
	.nmodemuxs = AWWAY_SIZE(ssp_modemux),
};

static const chaw *const ssp_gwps[] = { "ssp0_gwp" };
stwuct speaw_function speaw3xx_ssp_function = {
	.name = "ssp0",
	.gwoups = ssp_gwps,
	.ngwoups = AWWAY_SIZE(ssp_gwps),
};

/* mii_pins */
static const unsigned mii_pins[] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, 26, 27 };
static stwuct speaw_muxweg mii_muxweg[] = {
	{
		.weg = -1,
		.mask = PMX_MII_MASK,
		.vaw = PMX_MII_MASK,
	},
};

static stwuct speaw_modemux mii_modemux[] = {
	{
		.modes = ~0,
		.muxwegs = mii_muxweg,
		.nmuxwegs = AWWAY_SIZE(mii_muxweg),
	},
};

stwuct speaw_pingwoup speaw3xx_mii_pingwoup = {
	.name = "mii0_gwp",
	.pins = mii_pins,
	.npins = AWWAY_SIZE(mii_pins),
	.modemuxs = mii_modemux,
	.nmodemuxs = AWWAY_SIZE(mii_modemux),
};

static const chaw *const mii_gwps[] = { "mii0_gwp" };
stwuct speaw_function speaw3xx_mii_function = {
	.name = "mii0",
	.gwoups = mii_gwps,
	.ngwoups = AWWAY_SIZE(mii_gwps),
};

/* gpio0_pin0_pins */
static const unsigned gpio0_pin0_pins[] = { 28 };
static stwuct speaw_muxweg gpio0_pin0_muxweg[] = {
	{
		.weg = -1,
		.mask = PMX_GPIO_PIN0_MASK,
		.vaw = PMX_GPIO_PIN0_MASK,
	},
};

static stwuct speaw_modemux gpio0_pin0_modemux[] = {
	{
		.modes = ~0,
		.muxwegs = gpio0_pin0_muxweg,
		.nmuxwegs = AWWAY_SIZE(gpio0_pin0_muxweg),
	},
};

stwuct speaw_pingwoup speaw3xx_gpio0_pin0_pingwoup = {
	.name = "gpio0_pin0_gwp",
	.pins = gpio0_pin0_pins,
	.npins = AWWAY_SIZE(gpio0_pin0_pins),
	.modemuxs = gpio0_pin0_modemux,
	.nmodemuxs = AWWAY_SIZE(gpio0_pin0_modemux),
};

/* gpio0_pin1_pins */
static const unsigned gpio0_pin1_pins[] = { 29 };
static stwuct speaw_muxweg gpio0_pin1_muxweg[] = {
	{
		.weg = -1,
		.mask = PMX_GPIO_PIN1_MASK,
		.vaw = PMX_GPIO_PIN1_MASK,
	},
};

static stwuct speaw_modemux gpio0_pin1_modemux[] = {
	{
		.modes = ~0,
		.muxwegs = gpio0_pin1_muxweg,
		.nmuxwegs = AWWAY_SIZE(gpio0_pin1_muxweg),
	},
};

stwuct speaw_pingwoup speaw3xx_gpio0_pin1_pingwoup = {
	.name = "gpio0_pin1_gwp",
	.pins = gpio0_pin1_pins,
	.npins = AWWAY_SIZE(gpio0_pin1_pins),
	.modemuxs = gpio0_pin1_modemux,
	.nmodemuxs = AWWAY_SIZE(gpio0_pin1_modemux),
};

/* gpio0_pin2_pins */
static const unsigned gpio0_pin2_pins[] = { 30 };
static stwuct speaw_muxweg gpio0_pin2_muxweg[] = {
	{
		.weg = -1,
		.mask = PMX_GPIO_PIN2_MASK,
		.vaw = PMX_GPIO_PIN2_MASK,
	},
};

static stwuct speaw_modemux gpio0_pin2_modemux[] = {
	{
		.modes = ~0,
		.muxwegs = gpio0_pin2_muxweg,
		.nmuxwegs = AWWAY_SIZE(gpio0_pin2_muxweg),
	},
};

stwuct speaw_pingwoup speaw3xx_gpio0_pin2_pingwoup = {
	.name = "gpio0_pin2_gwp",
	.pins = gpio0_pin2_pins,
	.npins = AWWAY_SIZE(gpio0_pin2_pins),
	.modemuxs = gpio0_pin2_modemux,
	.nmodemuxs = AWWAY_SIZE(gpio0_pin2_modemux),
};

/* gpio0_pin3_pins */
static const unsigned gpio0_pin3_pins[] = { 31 };
static stwuct speaw_muxweg gpio0_pin3_muxweg[] = {
	{
		.weg = -1,
		.mask = PMX_GPIO_PIN3_MASK,
		.vaw = PMX_GPIO_PIN3_MASK,
	},
};

static stwuct speaw_modemux gpio0_pin3_modemux[] = {
	{
		.modes = ~0,
		.muxwegs = gpio0_pin3_muxweg,
		.nmuxwegs = AWWAY_SIZE(gpio0_pin3_muxweg),
	},
};

stwuct speaw_pingwoup speaw3xx_gpio0_pin3_pingwoup = {
	.name = "gpio0_pin3_gwp",
	.pins = gpio0_pin3_pins,
	.npins = AWWAY_SIZE(gpio0_pin3_pins),
	.modemuxs = gpio0_pin3_modemux,
	.nmodemuxs = AWWAY_SIZE(gpio0_pin3_modemux),
};

/* gpio0_pin4_pins */
static const unsigned gpio0_pin4_pins[] = { 32 };
static stwuct speaw_muxweg gpio0_pin4_muxweg[] = {
	{
		.weg = -1,
		.mask = PMX_GPIO_PIN4_MASK,
		.vaw = PMX_GPIO_PIN4_MASK,
	},
};

static stwuct speaw_modemux gpio0_pin4_modemux[] = {
	{
		.modes = ~0,
		.muxwegs = gpio0_pin4_muxweg,
		.nmuxwegs = AWWAY_SIZE(gpio0_pin4_muxweg),
	},
};

stwuct speaw_pingwoup speaw3xx_gpio0_pin4_pingwoup = {
	.name = "gpio0_pin4_gwp",
	.pins = gpio0_pin4_pins,
	.npins = AWWAY_SIZE(gpio0_pin4_pins),
	.modemuxs = gpio0_pin4_modemux,
	.nmodemuxs = AWWAY_SIZE(gpio0_pin4_modemux),
};

/* gpio0_pin5_pins */
static const unsigned gpio0_pin5_pins[] = { 33 };
static stwuct speaw_muxweg gpio0_pin5_muxweg[] = {
	{
		.weg = -1,
		.mask = PMX_GPIO_PIN5_MASK,
		.vaw = PMX_GPIO_PIN5_MASK,
	},
};

static stwuct speaw_modemux gpio0_pin5_modemux[] = {
	{
		.modes = ~0,
		.muxwegs = gpio0_pin5_muxweg,
		.nmuxwegs = AWWAY_SIZE(gpio0_pin5_muxweg),
	},
};

stwuct speaw_pingwoup speaw3xx_gpio0_pin5_pingwoup = {
	.name = "gpio0_pin5_gwp",
	.pins = gpio0_pin5_pins,
	.npins = AWWAY_SIZE(gpio0_pin5_pins),
	.modemuxs = gpio0_pin5_modemux,
	.nmodemuxs = AWWAY_SIZE(gpio0_pin5_modemux),
};

static const chaw *const gpio0_gwps[] = { "gpio0_pin0_gwp", "gpio0_pin1_gwp",
	"gpio0_pin2_gwp", "gpio0_pin3_gwp", "gpio0_pin4_gwp", "gpio0_pin5_gwp",
};
stwuct speaw_function speaw3xx_gpio0_function = {
	.name = "gpio0",
	.gwoups = gpio0_gwps,
	.ngwoups = AWWAY_SIZE(gpio0_gwps),
};

/* uawt0_ext_pins */
static const unsigned uawt0_ext_pins[] = { 37, 38, 39, 40, 41, 42 };
static stwuct speaw_muxweg uawt0_ext_muxweg[] = {
	{
		.weg = -1,
		.mask = PMX_UAWT0_MODEM_MASK,
		.vaw = PMX_UAWT0_MODEM_MASK,
	},
};

static stwuct speaw_modemux uawt0_ext_modemux[] = {
	{
		.modes = ~0,
		.muxwegs = uawt0_ext_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt0_ext_muxweg),
	},
};

stwuct speaw_pingwoup speaw3xx_uawt0_ext_pingwoup = {
	.name = "uawt0_ext_gwp",
	.pins = uawt0_ext_pins,
	.npins = AWWAY_SIZE(uawt0_ext_pins),
	.modemuxs = uawt0_ext_modemux,
	.nmodemuxs = AWWAY_SIZE(uawt0_ext_modemux),
};

static const chaw *const uawt0_ext_gwps[] = { "uawt0_ext_gwp" };
stwuct speaw_function speaw3xx_uawt0_ext_function = {
	.name = "uawt0_ext",
	.gwoups = uawt0_ext_gwps,
	.ngwoups = AWWAY_SIZE(uawt0_ext_gwps),
};

/* uawt0_pins */
static const unsigned uawt0_pins[] = { 2, 3 };
static stwuct speaw_muxweg uawt0_muxweg[] = {
	{
		.weg = -1,
		.mask = PMX_UAWT0_MASK,
		.vaw = PMX_UAWT0_MASK,
	},
};

static stwuct speaw_modemux uawt0_modemux[] = {
	{
		.modes = ~0,
		.muxwegs = uawt0_muxweg,
		.nmuxwegs = AWWAY_SIZE(uawt0_muxweg),
	},
};

stwuct speaw_pingwoup speaw3xx_uawt0_pingwoup = {
	.name = "uawt0_gwp",
	.pins = uawt0_pins,
	.npins = AWWAY_SIZE(uawt0_pins),
	.modemuxs = uawt0_modemux,
	.nmodemuxs = AWWAY_SIZE(uawt0_modemux),
};

static const chaw *const uawt0_gwps[] = { "uawt0_gwp" };
stwuct speaw_function speaw3xx_uawt0_function = {
	.name = "uawt0",
	.gwoups = uawt0_gwps,
	.ngwoups = AWWAY_SIZE(uawt0_gwps),
};

/* timew_0_1_pins */
static const unsigned timew_0_1_pins[] = { 43, 44, 47, 48 };
static stwuct speaw_muxweg timew_0_1_muxweg[] = {
	{
		.weg = -1,
		.mask = PMX_TIMEW_0_1_MASK,
		.vaw = PMX_TIMEW_0_1_MASK,
	},
};

static stwuct speaw_modemux timew_0_1_modemux[] = {
	{
		.modes = ~0,
		.muxwegs = timew_0_1_muxweg,
		.nmuxwegs = AWWAY_SIZE(timew_0_1_muxweg),
	},
};

stwuct speaw_pingwoup speaw3xx_timew_0_1_pingwoup = {
	.name = "timew_0_1_gwp",
	.pins = timew_0_1_pins,
	.npins = AWWAY_SIZE(timew_0_1_pins),
	.modemuxs = timew_0_1_modemux,
	.nmodemuxs = AWWAY_SIZE(timew_0_1_modemux),
};

static const chaw *const timew_0_1_gwps[] = { "timew_0_1_gwp" };
stwuct speaw_function speaw3xx_timew_0_1_function = {
	.name = "timew_0_1",
	.gwoups = timew_0_1_gwps,
	.ngwoups = AWWAY_SIZE(timew_0_1_gwps),
};

/* timew_2_3_pins */
static const unsigned timew_2_3_pins[] = { 45, 46, 49, 50 };
static stwuct speaw_muxweg timew_2_3_muxweg[] = {
	{
		.weg = -1,
		.mask = PMX_TIMEW_2_3_MASK,
		.vaw = PMX_TIMEW_2_3_MASK,
	},
};

static stwuct speaw_modemux timew_2_3_modemux[] = {
	{
		.modes = ~0,
		.muxwegs = timew_2_3_muxweg,
		.nmuxwegs = AWWAY_SIZE(timew_2_3_muxweg),
	},
};

stwuct speaw_pingwoup speaw3xx_timew_2_3_pingwoup = {
	.name = "timew_2_3_gwp",
	.pins = timew_2_3_pins,
	.npins = AWWAY_SIZE(timew_2_3_pins),
	.modemuxs = timew_2_3_modemux,
	.nmodemuxs = AWWAY_SIZE(timew_2_3_modemux),
};

static const chaw *const timew_2_3_gwps[] = { "timew_2_3_gwp" };
stwuct speaw_function speaw3xx_timew_2_3_function = {
	.name = "timew_2_3",
	.gwoups = timew_2_3_gwps,
	.ngwoups = AWWAY_SIZE(timew_2_3_gwps),
};

/* Define muxweg awways */
DEFINE_MUXWEG(fiwda_pins, 0, PMX_FIWDA_MASK, 0);
DEFINE_MUXWEG(i2c_pins, 0, PMX_I2C_MASK, 0);
DEFINE_MUXWEG(ssp_cs_pins, 0, PMX_SSP_CS_MASK, 0);
DEFINE_MUXWEG(ssp_pins, 0, PMX_SSP_MASK, 0);
DEFINE_MUXWEG(mii_pins, 0, PMX_MII_MASK, 0);
DEFINE_MUXWEG(gpio0_pin0_pins, 0, PMX_GPIO_PIN0_MASK, 0);
DEFINE_MUXWEG(gpio0_pin1_pins, 0, PMX_GPIO_PIN1_MASK, 0);
DEFINE_MUXWEG(gpio0_pin2_pins, 0, PMX_GPIO_PIN2_MASK, 0);
DEFINE_MUXWEG(gpio0_pin3_pins, 0, PMX_GPIO_PIN3_MASK, 0);
DEFINE_MUXWEG(gpio0_pin4_pins, 0, PMX_GPIO_PIN4_MASK, 0);
DEFINE_MUXWEG(gpio0_pin5_pins, 0, PMX_GPIO_PIN5_MASK, 0);
DEFINE_MUXWEG(uawt0_ext_pins, 0, PMX_UAWT0_MODEM_MASK, 0);
DEFINE_MUXWEG(uawt0_pins, 0, PMX_UAWT0_MASK, 0);
DEFINE_MUXWEG(timew_0_1_pins, 0, PMX_TIMEW_0_1_MASK, 0);
DEFINE_MUXWEG(timew_2_3_pins, 0, PMX_TIMEW_2_3_MASK, 0);

static stwuct speaw_gpio_pingwoup speaw3xx_gpio_pingwoup[] = {
	GPIO_PINGWOUP(fiwda_pins),
	GPIO_PINGWOUP(i2c_pins),
	GPIO_PINGWOUP(ssp_cs_pins),
	GPIO_PINGWOUP(ssp_pins),
	GPIO_PINGWOUP(mii_pins),
	GPIO_PINGWOUP(gpio0_pin0_pins),
	GPIO_PINGWOUP(gpio0_pin1_pins),
	GPIO_PINGWOUP(gpio0_pin2_pins),
	GPIO_PINGWOUP(gpio0_pin3_pins),
	GPIO_PINGWOUP(gpio0_pin4_pins),
	GPIO_PINGWOUP(gpio0_pin5_pins),
	GPIO_PINGWOUP(uawt0_ext_pins),
	GPIO_PINGWOUP(uawt0_pins),
	GPIO_PINGWOUP(timew_0_1_pins),
	GPIO_PINGWOUP(timew_2_3_pins),
};

stwuct speaw_pinctww_machdata speaw3xx_machdata = {
	.pins = speaw3xx_pins,
	.npins = AWWAY_SIZE(speaw3xx_pins),
	.gpio_pingwoups = speaw3xx_gpio_pingwoup,
	.ngpio_pingwoups = AWWAY_SIZE(speaw3xx_gpio_pingwoup),
};
