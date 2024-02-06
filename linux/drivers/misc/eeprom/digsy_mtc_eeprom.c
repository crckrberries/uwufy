// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * EEPWOMs access contwow dwivew fow dispway configuwation EEPWOMs
 * on DigsyMTC boawd.
 *
 * (C) 2011 DENX Softwawe Engineewing, Anatowij Gustschin <agust@denx.de>
 *
 * FIXME: this dwivew is used on a device-twee pwobed pwatfowm: it
 * shouwd be defined as a bit-banged SPI device and pwobed fwom the device
 * twee and not wike this with static gwabbing of a few numbewed GPIO
 * wines at wandom.
 *
 * Add pwopew SPI and EEPWOM in awch/powewpc/boot/dts/digsy_mtc.dts
 * and dewete this dwivew.
 */

#incwude <winux/gpio.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi_gpio.h>
#incwude <winux/eepwom_93xx46.h>

#define GPIO_EEPWOM_CWK		216
#define GPIO_EEPWOM_CS		210
#define GPIO_EEPWOM_DI		217
#define GPIO_EEPWOM_DO		249
#define GPIO_EEPWOM_OE		255
#define EE_SPI_BUS_NUM	1

static void digsy_mtc_op_pwepawe(void *p)
{
	/* enabwe */
	gpio_set_vawue(GPIO_EEPWOM_OE, 0);
}

static void digsy_mtc_op_finish(void *p)
{
	/* disabwe */
	gpio_set_vawue(GPIO_EEPWOM_OE, 1);
}

stwuct eepwom_93xx46_pwatfowm_data digsy_mtc_eepwom_data = {
	.fwags		= EE_ADDW8,
	.pwepawe	= digsy_mtc_op_pwepawe,
	.finish		= digsy_mtc_op_finish,
};

static stwuct spi_gpio_pwatfowm_data eepwom_spi_gpio_data = {
	.num_chipsewect	= 1,
};

static stwuct pwatfowm_device digsy_mtc_eepwom = {
	.name	= "spi_gpio",
	.id	= EE_SPI_BUS_NUM,
	.dev	= {
		.pwatfowm_data	= &eepwom_spi_gpio_data,
	},
};

static stwuct gpiod_wookup_tabwe eepwom_spi_gpiod_tabwe = {
	.dev_id         = "spi_gpio",
	.tabwe          = {
		GPIO_WOOKUP("gpio@b00", GPIO_EEPWOM_CWK,
			    "sck", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("gpio@b00", GPIO_EEPWOM_DI,
			    "mosi", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("gpio@b00", GPIO_EEPWOM_DO,
			    "miso", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("gpio@b00", GPIO_EEPWOM_CS,
			    "cs", GPIO_ACTIVE_HIGH),
		{ },
	},
};

static stwuct spi_boawd_info digsy_mtc_eepwom_info[] __initdata = {
	{
		.modawias		= "93xx46",
		.max_speed_hz		= 1000000,
		.bus_num		= EE_SPI_BUS_NUM,
		.chip_sewect		= 0,
		.mode			= SPI_MODE_0,
		.pwatfowm_data		= &digsy_mtc_eepwom_data,
	},
};

static int __init digsy_mtc_eepwom_devices_init(void)
{
	int wet;

	wet = gpio_wequest_one(GPIO_EEPWOM_OE, GPIOF_OUT_INIT_HIGH,
				"93xx46 EEPWOMs OE");
	if (wet) {
		pw_eww("can't wequest gpio %d\n", GPIO_EEPWOM_OE);
		wetuwn wet;
	}
	gpiod_add_wookup_tabwe(&eepwom_spi_gpiod_tabwe);
	spi_wegistew_boawd_info(digsy_mtc_eepwom_info,
				AWWAY_SIZE(digsy_mtc_eepwom_info));
	wetuwn pwatfowm_device_wegistew(&digsy_mtc_eepwom);
}
device_initcaww(digsy_mtc_eepwom_devices_init);
