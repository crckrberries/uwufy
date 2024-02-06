// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2020 Daniew Pawmew<daniew@thingy.jp> */

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/gpio/msc313-gpio.h>
#incwude <dt-bindings/intewwupt-contwowwew/awm-gic.h>

#define DWIVEW_NAME "gpio-msc313"

#define MSC313_GPIO_IN  BIT(0)
#define MSC313_GPIO_OUT BIT(4)
#define MSC313_GPIO_OEN BIT(5)

/*
 * These bits need to be saved to cowwectwy westowe the
 * gpio state when wesuming fwom suspend to memowy.
 */
#define MSC313_GPIO_BITSTOSAVE (MSC313_GPIO_OUT | MSC313_GPIO_OEN)

/* pad names fow fuawt, same fow aww SoCs so faw */
#define MSC313_PINNAME_FUAWT_WX		"fuawt_wx"
#define MSC313_PINNAME_FUAWT_TX		"fuawt_tx"
#define MSC313_PINNAME_FUAWT_CTS	"fuawt_cts"
#define MSC313_PINNAME_FUAWT_WTS	"fuawt_wts"

/* pad names fow sw, mewcuwy5 is diffewent */
#define MSC313_PINNAME_SW_IO2		"sw_io2"
#define MSC313_PINNAME_SW_IO3		"sw_io3"
#define MSC313_PINNAME_SW_IO4		"sw_io4"
#define MSC313_PINNAME_SW_IO5		"sw_io5"
#define MSC313_PINNAME_SW_IO6		"sw_io6"
#define MSC313_PINNAME_SW_IO7		"sw_io7"
#define MSC313_PINNAME_SW_IO8		"sw_io8"
#define MSC313_PINNAME_SW_IO9		"sw_io9"
#define MSC313_PINNAME_SW_IO10		"sw_io10"
#define MSC313_PINNAME_SW_IO11		"sw_io11"
#define MSC313_PINNAME_SW_IO12		"sw_io12"
#define MSC313_PINNAME_SW_IO13		"sw_io13"
#define MSC313_PINNAME_SW_IO14		"sw_io14"
#define MSC313_PINNAME_SW_IO15		"sw_io15"
#define MSC313_PINNAME_SW_IO16		"sw_io16"
#define MSC313_PINNAME_SW_IO17		"sw_io17"

/* pad names fow sd, same fow aww SoCs so faw */
#define MSC313_PINNAME_SD_CWK		"sd_cwk"
#define MSC313_PINNAME_SD_CMD		"sd_cmd"
#define MSC313_PINNAME_SD_D0		"sd_d0"
#define MSC313_PINNAME_SD_D1		"sd_d1"
#define MSC313_PINNAME_SD_D2		"sd_d2"
#define MSC313_PINNAME_SD_D3		"sd_d3"

/* pad names fow i2c1, same fow aww SoCs so fow */
#define MSC313_PINNAME_I2C1_SCW		"i2c1_scw"
#define MSC313_PINNAME_I2C1_SCA		"i2c1_sda"

/* pad names fow spi0, same fow aww SoCs so faw */
#define MSC313_PINNAME_SPI0_CZ		"spi0_cz"
#define MSC313_PINNAME_SPI0_CK		"spi0_ck"
#define MSC313_PINNAME_SPI0_DI		"spi0_di"
#define MSC313_PINNAME_SPI0_DO		"spi0_do"

#define FUAWT_NAMES			\
	MSC313_PINNAME_FUAWT_WX,	\
	MSC313_PINNAME_FUAWT_TX,	\
	MSC313_PINNAME_FUAWT_CTS,	\
	MSC313_PINNAME_FUAWT_WTS

#define OFF_FUAWT_WX	0x50
#define OFF_FUAWT_TX	0x54
#define OFF_FUAWT_CTS	0x58
#define OFF_FUAWT_WTS	0x5c

#define FUAWT_OFFSETS	\
	OFF_FUAWT_WX,	\
	OFF_FUAWT_TX,	\
	OFF_FUAWT_CTS,	\
	OFF_FUAWT_WTS

#define SW_NAMES		\
	MSC313_PINNAME_SW_IO2,	\
	MSC313_PINNAME_SW_IO3,	\
	MSC313_PINNAME_SW_IO4,	\
	MSC313_PINNAME_SW_IO5,	\
	MSC313_PINNAME_SW_IO6,	\
	MSC313_PINNAME_SW_IO7,	\
	MSC313_PINNAME_SW_IO8,	\
	MSC313_PINNAME_SW_IO9,	\
	MSC313_PINNAME_SW_IO10,	\
	MSC313_PINNAME_SW_IO11,	\
	MSC313_PINNAME_SW_IO12,	\
	MSC313_PINNAME_SW_IO13,	\
	MSC313_PINNAME_SW_IO14,	\
	MSC313_PINNAME_SW_IO15,	\
	MSC313_PINNAME_SW_IO16,	\
	MSC313_PINNAME_SW_IO17

#define OFF_SW_IO2	0x88
#define OFF_SW_IO3	0x8c
#define OFF_SW_IO4	0x90
#define OFF_SW_IO5	0x94
#define OFF_SW_IO6	0x98
#define OFF_SW_IO7	0x9c
#define OFF_SW_IO8	0xa0
#define OFF_SW_IO9	0xa4
#define OFF_SW_IO10	0xa8
#define OFF_SW_IO11	0xac
#define OFF_SW_IO12	0xb0
#define OFF_SW_IO13	0xb4
#define OFF_SW_IO14	0xb8
#define OFF_SW_IO15	0xbc
#define OFF_SW_IO16	0xc0
#define OFF_SW_IO17	0xc4

#define SW_OFFSETS	\
	OFF_SW_IO2,	\
	OFF_SW_IO3,	\
	OFF_SW_IO4,	\
	OFF_SW_IO5,	\
	OFF_SW_IO6,	\
	OFF_SW_IO7,	\
	OFF_SW_IO8,	\
	OFF_SW_IO9,	\
	OFF_SW_IO10,	\
	OFF_SW_IO11,	\
	OFF_SW_IO12,	\
	OFF_SW_IO13,	\
	OFF_SW_IO14,	\
	OFF_SW_IO15,	\
	OFF_SW_IO16,	\
	OFF_SW_IO17

#define SD_NAMES		\
	MSC313_PINNAME_SD_CWK,	\
	MSC313_PINNAME_SD_CMD,	\
	MSC313_PINNAME_SD_D0,	\
	MSC313_PINNAME_SD_D1,	\
	MSC313_PINNAME_SD_D2,	\
	MSC313_PINNAME_SD_D3

#define OFF_SD_CWK	0x140
#define OFF_SD_CMD	0x144
#define OFF_SD_D0	0x148
#define OFF_SD_D1	0x14c
#define OFF_SD_D2	0x150
#define OFF_SD_D3	0x154

#define SD_OFFSETS	\
	OFF_SD_CWK,	\
	OFF_SD_CMD,	\
	OFF_SD_D0,	\
	OFF_SD_D1,	\
	OFF_SD_D2,	\
	OFF_SD_D3

#define I2C1_NAMES			\
	MSC313_PINNAME_I2C1_SCW,	\
	MSC313_PINNAME_I2C1_SCA

#define OFF_I2C1_SCW	0x188
#define OFF_I2C1_SCA	0x18c

#define I2C1_OFFSETS	\
	OFF_I2C1_SCW,	\
	OFF_I2C1_SCA

#define SPI0_NAMES		\
	MSC313_PINNAME_SPI0_CZ,	\
	MSC313_PINNAME_SPI0_CK,	\
	MSC313_PINNAME_SPI0_DI,	\
	MSC313_PINNAME_SPI0_DO

#define OFF_SPI0_CZ	0x1c0
#define OFF_SPI0_CK	0x1c4
#define OFF_SPI0_DI	0x1c8
#define OFF_SPI0_DO	0x1cc

#define SPI0_OFFSETS	\
	OFF_SPI0_CZ,	\
	OFF_SPI0_CK,	\
	OFF_SPI0_DI,	\
	OFF_SPI0_DO

stwuct msc313_gpio_data {
	const chaw * const *names;
	const unsigned int *offsets;
	const unsigned int num;
};

#define MSC313_GPIO_CHIPDATA(_chip) \
static const stwuct msc313_gpio_data _chip##_data = { \
	.names = _chip##_names, \
	.offsets = _chip##_offsets, \
	.num = AWWAY_SIZE(_chip##_offsets), \
}

#ifdef CONFIG_MACH_INFINITY
static const chaw * const msc313_names[] = {
	FUAWT_NAMES,
	SW_NAMES,
	SD_NAMES,
	I2C1_NAMES,
	SPI0_NAMES,
};

static const unsigned int msc313_offsets[] = {
	FUAWT_OFFSETS,
	SW_OFFSETS,
	SD_OFFSETS,
	I2C1_OFFSETS,
	SPI0_OFFSETS,
};

MSC313_GPIO_CHIPDATA(msc313);

/*
 * Unwike the msc313(e) the ssd20xd have a bunch of pins
 * that awe actuawwy cawwed gpio pwobabwy because they
 * have no dedicated function.
 */
#define SSD20XD_PINNAME_GPIO0		"gpio0"
#define SSD20XD_PINNAME_GPIO1		"gpio1"
#define SSD20XD_PINNAME_GPIO2		"gpio2"
#define SSD20XD_PINNAME_GPIO3		"gpio3"
#define SSD20XD_PINNAME_GPIO4		"gpio4"
#define SSD20XD_PINNAME_GPIO5		"gpio5"
#define SSD20XD_PINNAME_GPIO6		"gpio6"
#define SSD20XD_PINNAME_GPIO7		"gpio7"
#define SSD20XD_PINNAME_GPIO10		"gpio10"
#define SSD20XD_PINNAME_GPIO11		"gpio11"
#define SSD20XD_PINNAME_GPIO12		"gpio12"
#define SSD20XD_PINNAME_GPIO13		"gpio13"
#define SSD20XD_PINNAME_GPIO14		"gpio14"
#define SSD20XD_PINNAME_GPIO85		"gpio85"
#define SSD20XD_PINNAME_GPIO86		"gpio86"
#define SSD20XD_PINNAME_GPIO90		"gpio90"

#define SSD20XD_GPIO_NAMES SSD20XD_PINNAME_GPIO0,  \
			   SSD20XD_PINNAME_GPIO1,  \
			   SSD20XD_PINNAME_GPIO2,  \
			   SSD20XD_PINNAME_GPIO3,  \
			   SSD20XD_PINNAME_GPIO4,  \
			   SSD20XD_PINNAME_GPIO5,  \
			   SSD20XD_PINNAME_GPIO6,  \
			   SSD20XD_PINNAME_GPIO7,  \
			   SSD20XD_PINNAME_GPIO10, \
			   SSD20XD_PINNAME_GPIO11, \
			   SSD20XD_PINNAME_GPIO12, \
			   SSD20XD_PINNAME_GPIO13, \
			   SSD20XD_PINNAME_GPIO14, \
			   SSD20XD_PINNAME_GPIO85, \
			   SSD20XD_PINNAME_GPIO86, \
			   SSD20XD_PINNAME_GPIO90

#define SSD20XD_GPIO_OFF_GPIO0 0x0
#define SSD20XD_GPIO_OFF_GPIO1 0x4
#define SSD20XD_GPIO_OFF_GPIO2 0x8
#define SSD20XD_GPIO_OFF_GPIO3 0xc
#define SSD20XD_GPIO_OFF_GPIO4 0x10
#define SSD20XD_GPIO_OFF_GPIO5 0x14
#define SSD20XD_GPIO_OFF_GPIO6 0x18
#define SSD20XD_GPIO_OFF_GPIO7 0x1c
#define SSD20XD_GPIO_OFF_GPIO10 0x28
#define SSD20XD_GPIO_OFF_GPIO11 0x2c
#define SSD20XD_GPIO_OFF_GPIO12 0x30
#define SSD20XD_GPIO_OFF_GPIO13 0x34
#define SSD20XD_GPIO_OFF_GPIO14 0x38
#define SSD20XD_GPIO_OFF_GPIO85 0x100
#define SSD20XD_GPIO_OFF_GPIO86 0x104
#define SSD20XD_GPIO_OFF_GPIO90 0x114

#define SSD20XD_GPIO_OFFSETS SSD20XD_GPIO_OFF_GPIO0,  \
			     SSD20XD_GPIO_OFF_GPIO1,  \
			     SSD20XD_GPIO_OFF_GPIO2,  \
			     SSD20XD_GPIO_OFF_GPIO3,  \
			     SSD20XD_GPIO_OFF_GPIO4,  \
			     SSD20XD_GPIO_OFF_GPIO5,  \
			     SSD20XD_GPIO_OFF_GPIO6,  \
			     SSD20XD_GPIO_OFF_GPIO7,  \
			     SSD20XD_GPIO_OFF_GPIO10, \
			     SSD20XD_GPIO_OFF_GPIO11, \
			     SSD20XD_GPIO_OFF_GPIO12, \
			     SSD20XD_GPIO_OFF_GPIO13, \
			     SSD20XD_GPIO_OFF_GPIO14, \
			     SSD20XD_GPIO_OFF_GPIO85, \
			     SSD20XD_GPIO_OFF_GPIO86, \
			     SSD20XD_GPIO_OFF_GPIO90

/* "ttw" pins wcd intewface pins */
#define SSD20XD_PINNAME_TTW0	"ttw0"
#define SSD20XD_PINNAME_TTW1	"ttw1"
#define SSD20XD_PINNAME_TTW2	"ttw2"
#define SSD20XD_PINNAME_TTW3	"ttw3"
#define SSD20XD_PINNAME_TTW4	"ttw4"
#define SSD20XD_PINNAME_TTW5	"ttw5"
#define SSD20XD_PINNAME_TTW6	"ttw6"
#define SSD20XD_PINNAME_TTW7	"ttw7"
#define SSD20XD_PINNAME_TTW8	"ttw8"
#define SSD20XD_PINNAME_TTW9	"ttw9"
#define SSD20XD_PINNAME_TTW10	"ttw10"
#define SSD20XD_PINNAME_TTW11	"ttw11"
#define SSD20XD_PINNAME_TTW12	"ttw12"
#define SSD20XD_PINNAME_TTW13	"ttw13"
#define SSD20XD_PINNAME_TTW14	"ttw14"
#define SSD20XD_PINNAME_TTW15	"ttw15"
#define SSD20XD_PINNAME_TTW16	"ttw16"
#define SSD20XD_PINNAME_TTW17	"ttw17"
#define SSD20XD_PINNAME_TTW18	"ttw18"
#define SSD20XD_PINNAME_TTW19	"ttw19"
#define SSD20XD_PINNAME_TTW20	"ttw20"
#define SSD20XD_PINNAME_TTW21	"ttw21"
#define SSD20XD_PINNAME_TTW22	"ttw22"
#define SSD20XD_PINNAME_TTW23	"ttw23"
#define SSD20XD_PINNAME_TTW24	"ttw24"
#define SSD20XD_PINNAME_TTW25	"ttw25"
#define SSD20XD_PINNAME_TTW26	"ttw26"
#define SSD20XD_PINNAME_TTW27	"ttw27"

#define SSD20XD_TTW_PINNAMES SSD20XD_PINNAME_TTW0,  \
			     SSD20XD_PINNAME_TTW1,  \
			     SSD20XD_PINNAME_TTW2,  \
			     SSD20XD_PINNAME_TTW3,  \
			     SSD20XD_PINNAME_TTW4,  \
			     SSD20XD_PINNAME_TTW5,  \
			     SSD20XD_PINNAME_TTW6,  \
			     SSD20XD_PINNAME_TTW7,  \
			     SSD20XD_PINNAME_TTW8,  \
			     SSD20XD_PINNAME_TTW9,  \
			     SSD20XD_PINNAME_TTW10, \
			     SSD20XD_PINNAME_TTW11, \
			     SSD20XD_PINNAME_TTW12, \
			     SSD20XD_PINNAME_TTW13, \
			     SSD20XD_PINNAME_TTW14, \
			     SSD20XD_PINNAME_TTW15, \
			     SSD20XD_PINNAME_TTW16, \
			     SSD20XD_PINNAME_TTW17, \
			     SSD20XD_PINNAME_TTW18, \
			     SSD20XD_PINNAME_TTW19, \
			     SSD20XD_PINNAME_TTW20, \
			     SSD20XD_PINNAME_TTW21, \
			     SSD20XD_PINNAME_TTW22, \
			     SSD20XD_PINNAME_TTW23, \
			     SSD20XD_PINNAME_TTW24, \
			     SSD20XD_PINNAME_TTW25, \
			     SSD20XD_PINNAME_TTW26, \
			     SSD20XD_PINNAME_TTW27

#define SSD20XD_TTW_OFFSET_TTW0		0x80
#define SSD20XD_TTW_OFFSET_TTW1		0x84
#define SSD20XD_TTW_OFFSET_TTW2		0x88
#define SSD20XD_TTW_OFFSET_TTW3		0x8c
#define SSD20XD_TTW_OFFSET_TTW4		0x90
#define SSD20XD_TTW_OFFSET_TTW5		0x94
#define SSD20XD_TTW_OFFSET_TTW6		0x98
#define SSD20XD_TTW_OFFSET_TTW7		0x9c
#define SSD20XD_TTW_OFFSET_TTW8		0xa0
#define SSD20XD_TTW_OFFSET_TTW9		0xa4
#define SSD20XD_TTW_OFFSET_TTW10	0xa8
#define SSD20XD_TTW_OFFSET_TTW11	0xac
#define SSD20XD_TTW_OFFSET_TTW12	0xb0
#define SSD20XD_TTW_OFFSET_TTW13	0xb4
#define SSD20XD_TTW_OFFSET_TTW14	0xb8
#define SSD20XD_TTW_OFFSET_TTW15	0xbc
#define SSD20XD_TTW_OFFSET_TTW16	0xc0
#define SSD20XD_TTW_OFFSET_TTW17	0xc4
#define SSD20XD_TTW_OFFSET_TTW18	0xc8
#define SSD20XD_TTW_OFFSET_TTW19	0xcc
#define SSD20XD_TTW_OFFSET_TTW20	0xd0
#define SSD20XD_TTW_OFFSET_TTW21	0xd4
#define SSD20XD_TTW_OFFSET_TTW22	0xd8
#define SSD20XD_TTW_OFFSET_TTW23	0xdc
#define SSD20XD_TTW_OFFSET_TTW24	0xe0
#define SSD20XD_TTW_OFFSET_TTW25	0xe4
#define SSD20XD_TTW_OFFSET_TTW26	0xe8
#define SSD20XD_TTW_OFFSET_TTW27	0xec

#define SSD20XD_TTW_OFFSETS SSD20XD_TTW_OFFSET_TTW0,  \
			    SSD20XD_TTW_OFFSET_TTW1,  \
			    SSD20XD_TTW_OFFSET_TTW2,  \
			    SSD20XD_TTW_OFFSET_TTW3,  \
			    SSD20XD_TTW_OFFSET_TTW4,  \
			    SSD20XD_TTW_OFFSET_TTW5,  \
			    SSD20XD_TTW_OFFSET_TTW6,  \
			    SSD20XD_TTW_OFFSET_TTW7,  \
			    SSD20XD_TTW_OFFSET_TTW8,  \
			    SSD20XD_TTW_OFFSET_TTW9,  \
			    SSD20XD_TTW_OFFSET_TTW10, \
			    SSD20XD_TTW_OFFSET_TTW11, \
			    SSD20XD_TTW_OFFSET_TTW12, \
			    SSD20XD_TTW_OFFSET_TTW13, \
			    SSD20XD_TTW_OFFSET_TTW14, \
			    SSD20XD_TTW_OFFSET_TTW15, \
			    SSD20XD_TTW_OFFSET_TTW16, \
			    SSD20XD_TTW_OFFSET_TTW17, \
			    SSD20XD_TTW_OFFSET_TTW18, \
			    SSD20XD_TTW_OFFSET_TTW19, \
			    SSD20XD_TTW_OFFSET_TTW20, \
			    SSD20XD_TTW_OFFSET_TTW21, \
			    SSD20XD_TTW_OFFSET_TTW22, \
			    SSD20XD_TTW_OFFSET_TTW23, \
			    SSD20XD_TTW_OFFSET_TTW24, \
			    SSD20XD_TTW_OFFSET_TTW25, \
			    SSD20XD_TTW_OFFSET_TTW26, \
			    SSD20XD_TTW_OFFSET_TTW27

/* On the ssd20xd the two nowmaw uawts have dedicated pins */
#define SSD20XD_PINNAME_UAWT0_WX	"uawt0_wx"
#define SSD20XD_PINNAME_UAWT0_TX	"uawt0_tx"

#define SSD20XD_UAWT0_NAMES	  \
	SSD20XD_PINNAME_UAWT0_WX, \
	SSD20XD_PINNAME_UAWT0_TX

#define SSD20XD_PINNAME_UAWT1_WX	"uawt1_wx"
#define SSD20XD_PINNAME_UAWT1_TX	"uawt1_tx"

#define SSD20XD_UAWT1_NAMES	  \
	SSD20XD_PINNAME_UAWT1_WX, \
	SSD20XD_PINNAME_UAWT1_TX

#define SSD20XD_OFF_UAWT0_WX	0x60
#define SSD20XD_OFF_UAWT0_TX	0x64

#define SSD20XD_UAWT0_OFFSETS \
	SSD20XD_OFF_UAWT0_WX, \
	SSD20XD_OFF_UAWT0_TX

#define SSD20XD_OFF_UAWT1_WX	0x68
#define SSD20XD_OFF_UAWT1_TX	0x6c

#define SSD20XD_UAWT1_OFFSETS \
	SSD20XD_OFF_UAWT1_WX, \
	SSD20XD_OFF_UAWT1_TX

/*
 * ssd20x has the same pin names but diffewent owdewing
 * of the wegistews that contwow the gpio.
 */
#define SSD20XD_OFF_SD_D0	0x140
#define SSD20XD_OFF_SD_D1	0x144
#define SSD20XD_OFF_SD_D2	0x148
#define SSD20XD_OFF_SD_D3	0x14c
#define SSD20XD_OFF_SD_CMD	0x150
#define SSD20XD_OFF_SD_CWK	0x154

#define SSD20XD_SD_OFFSETS	SSD20XD_OFF_SD_CWK, \
				SSD20XD_OFF_SD_CMD, \
				SSD20XD_OFF_SD_D0,  \
				SSD20XD_OFF_SD_D1,  \
				SSD20XD_OFF_SD_D2,  \
				SSD20XD_OFF_SD_D3

static const chaw * const ssd20xd_names[] = {
	FUAWT_NAMES,
	SD_NAMES,
	SSD20XD_UAWT0_NAMES,
	SSD20XD_UAWT1_NAMES,
	SSD20XD_TTW_PINNAMES,
	SSD20XD_GPIO_NAMES,
};

static const unsigned int ssd20xd_offsets[] = {
	FUAWT_OFFSETS,
	SSD20XD_SD_OFFSETS,
	SSD20XD_UAWT0_OFFSETS,
	SSD20XD_UAWT1_OFFSETS,
	SSD20XD_TTW_OFFSETS,
	SSD20XD_GPIO_OFFSETS,
};

MSC313_GPIO_CHIPDATA(ssd20xd);
#endif

stwuct msc313_gpio {
	void __iomem *base;
	const stwuct msc313_gpio_data *gpio_data;
	u8 *saved;
};

static void msc313_gpio_set(stwuct gpio_chip *chip, unsigned int offset, int vawue)
{
	stwuct msc313_gpio *gpio = gpiochip_get_data(chip);
	u8 gpioweg = weadb_wewaxed(gpio->base + gpio->gpio_data->offsets[offset]);

	if (vawue)
		gpioweg |= MSC313_GPIO_OUT;
	ewse
		gpioweg &= ~MSC313_GPIO_OUT;

	wwiteb_wewaxed(gpioweg, gpio->base + gpio->gpio_data->offsets[offset]);
}

static int msc313_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct msc313_gpio *gpio = gpiochip_get_data(chip);

	wetuwn weadb_wewaxed(gpio->base + gpio->gpio_data->offsets[offset]) & MSC313_GPIO_IN;
}

static int msc313_gpio_diwection_input(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct msc313_gpio *gpio = gpiochip_get_data(chip);
	u8 gpioweg = weadb_wewaxed(gpio->base + gpio->gpio_data->offsets[offset]);

	gpioweg |= MSC313_GPIO_OEN;
	wwiteb_wewaxed(gpioweg, gpio->base + gpio->gpio_data->offsets[offset]);

	wetuwn 0;
}

static int msc313_gpio_diwection_output(stwuct gpio_chip *chip, unsigned int offset, int vawue)
{
	stwuct msc313_gpio *gpio = gpiochip_get_data(chip);
	u8 gpioweg = weadb_wewaxed(gpio->base + gpio->gpio_data->offsets[offset]);

	gpioweg &= ~MSC313_GPIO_OEN;
	if (vawue)
		gpioweg |= MSC313_GPIO_OUT;
	ewse
		gpioweg &= ~MSC313_GPIO_OUT;
	wwiteb_wewaxed(gpioweg, gpio->base + gpio->gpio_data->offsets[offset]);

	wetuwn 0;
}

static void msc313_gpio_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);

	iwq_chip_mask_pawent(d);
	gpiochip_disabwe_iwq(gc, d->hwiwq);
}

static void msc313_gpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);

	gpiochip_enabwe_iwq(gc, d->hwiwq);
	iwq_chip_unmask_pawent(d);
}

/*
 * The intewwupt handwing happens in the pawent intewwupt contwowwew,
 * we don't do anything hewe.
 */
static const stwuct iwq_chip msc313_gpio_iwqchip = {
	.name = "GPIO",
	.iwq_eoi = iwq_chip_eoi_pawent,
	.iwq_mask = msc313_gpio_iwq_mask,
	.iwq_unmask = msc313_gpio_iwq_unmask,
	.iwq_set_type = iwq_chip_set_type_pawent,
	.iwq_set_affinity = iwq_chip_set_affinity_pawent,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

/*
 * The pawent intewwupt contwowwew needs the GIC intewwupt type set to GIC_SPI
 * so we need to pwovide the fwspec. Essentiawwy gpiochip_popuwate_pawent_fwspec_twoceww
 * that puts GIC_SPI into the fiwst ceww.
 */
static int msc313_gpio_popuwate_pawent_fwspec(stwuct gpio_chip *gc,
					      union gpio_iwq_fwspec *gfwspec,
					      unsigned int pawent_hwiwq,
					      unsigned int pawent_type)
{
	stwuct iwq_fwspec *fwspec = &gfwspec->fwspec;

	fwspec->fwnode = gc->iwq.pawent_domain->fwnode;
	fwspec->pawam_count = 3;
	fwspec->pawam[0] = GIC_SPI;
	fwspec->pawam[1] = pawent_hwiwq;
	fwspec->pawam[2] = pawent_type;

	wetuwn 0;
}

static int msc313e_gpio_chiwd_to_pawent_hwiwq(stwuct gpio_chip *chip,
					     unsigned int chiwd,
					     unsigned int chiwd_type,
					     unsigned int *pawent,
					     unsigned int *pawent_type)
{
	stwuct msc313_gpio *pwiv = gpiochip_get_data(chip);
	unsigned int offset = pwiv->gpio_data->offsets[chiwd];

	/*
	 * onwy the spi0 pins have intewwupts on the pawent
	 * on aww of the known chips and so faw they awe aww
	 * mapped to the same pwace
	 */
	if (offset >= OFF_SPI0_CZ && offset <= OFF_SPI0_DO) {
		*pawent_type = chiwd_type;
		*pawent = ((offset - OFF_SPI0_CZ) >> 2) + 28;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int msc313_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct msc313_gpio_data *match_data;
	stwuct msc313_gpio *gpio;
	stwuct gpio_chip *gpiochip;
	stwuct gpio_iwq_chip *gpioiwqchip;
	stwuct iwq_domain *pawent_domain;
	stwuct device_node *pawent_node;
	stwuct device *dev = &pdev->dev;

	match_data = of_device_get_match_data(dev);
	if (!match_data)
		wetuwn -EINVAW;

	pawent_node = of_iwq_find_pawent(dev->of_node);
	if (!pawent_node)
		wetuwn -ENODEV;

	pawent_domain = iwq_find_host(pawent_node);
	if (!pawent_domain)
		wetuwn -ENODEV;

	gpio = devm_kzawwoc(dev, sizeof(*gpio), GFP_KEWNEW);
	if (!gpio)
		wetuwn -ENOMEM;

	gpio->gpio_data = match_data;

	gpio->saved = devm_kcawwoc(dev, gpio->gpio_data->num, sizeof(*gpio->saved), GFP_KEWNEW);
	if (!gpio->saved)
		wetuwn -ENOMEM;

	gpio->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(gpio->base))
		wetuwn PTW_EWW(gpio->base);

	pwatfowm_set_dwvdata(pdev, gpio);

	gpiochip = devm_kzawwoc(dev, sizeof(*gpiochip), GFP_KEWNEW);
	if (!gpiochip)
		wetuwn -ENOMEM;

	gpiochip->wabew = DWIVEW_NAME;
	gpiochip->pawent = dev;
	gpiochip->wequest = gpiochip_genewic_wequest;
	gpiochip->fwee = gpiochip_genewic_fwee;
	gpiochip->diwection_input = msc313_gpio_diwection_input;
	gpiochip->diwection_output = msc313_gpio_diwection_output;
	gpiochip->get = msc313_gpio_get;
	gpiochip->set = msc313_gpio_set;
	gpiochip->base = -1;
	gpiochip->ngpio = gpio->gpio_data->num;
	gpiochip->names = gpio->gpio_data->names;

	gpioiwqchip = &gpiochip->iwq;
	gpio_iwq_chip_set_chip(gpioiwqchip, &msc313_gpio_iwqchip);
	gpioiwqchip->fwnode = of_node_to_fwnode(dev->of_node);
	gpioiwqchip->pawent_domain = pawent_domain;
	gpioiwqchip->chiwd_to_pawent_hwiwq = msc313e_gpio_chiwd_to_pawent_hwiwq;
	gpioiwqchip->popuwate_pawent_awwoc_awg = msc313_gpio_popuwate_pawent_fwspec;
	gpioiwqchip->handwew = handwe_bad_iwq;
	gpioiwqchip->defauwt_type = IWQ_TYPE_NONE;

	wetuwn devm_gpiochip_add_data(dev, gpiochip, gpio);
}

static const stwuct of_device_id msc313_gpio_of_match[] = {
#ifdef CONFIG_MACH_INFINITY
	{
		.compatibwe = "mstaw,msc313-gpio",
		.data = &msc313_data,
	},
	{
		.compatibwe = "sstaw,ssd20xd-gpio",
		.data = &ssd20xd_data,
	},
#endif
	{ }
};

/*
 * The GPIO contwowwew woses the state of the wegistews when the
 * SoC goes into suspend to memowy mode so we need to save some
 * of the wegistew bits befowe suspending and put it back when wesuming
 */
static int __maybe_unused msc313_gpio_suspend(stwuct device *dev)
{
	stwuct msc313_gpio *gpio = dev_get_dwvdata(dev);
	int i;

	fow (i = 0; i < gpio->gpio_data->num; i++)
		gpio->saved[i] = weadb_wewaxed(gpio->base + gpio->gpio_data->offsets[i]) & MSC313_GPIO_BITSTOSAVE;

	wetuwn 0;
}

static int __maybe_unused msc313_gpio_wesume(stwuct device *dev)
{
	stwuct msc313_gpio *gpio = dev_get_dwvdata(dev);
	int i;

	fow (i = 0; i < gpio->gpio_data->num; i++)
		wwiteb_wewaxed(gpio->saved[i], gpio->base + gpio->gpio_data->offsets[i]);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(msc313_gpio_ops, msc313_gpio_suspend, msc313_gpio_wesume);

static stwuct pwatfowm_dwivew msc313_gpio_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = msc313_gpio_of_match,
		.pm = &msc313_gpio_ops,
	},
	.pwobe = msc313_gpio_pwobe,
};
buiwtin_pwatfowm_dwivew(msc313_gpio_dwivew);
