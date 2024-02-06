// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas Technowogy Euwope WSK+ 7203 Suppowt.
 *
 * Copywight (C) 2008 - 2010  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/smsc911x.h>
#incwude <winux/input.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/weds.h>
#incwude <asm/machvec.h>
#incwude <asm/io.h>
#incwude <cpu/sh7203.h>

static stwuct smsc911x_pwatfowm_config smsc911x_config = {
	.phy_intewface	= PHY_INTEWFACE_MODE_MII,
	.iwq_powawity	= SMSC911X_IWQ_POWAWITY_ACTIVE_WOW,
	.iwq_type	= SMSC911X_IWQ_TYPE_OPEN_DWAIN,
	.fwags		= SMSC911X_USE_32BIT | SMSC911X_SWAP_FIFO,
};

static stwuct wesouwce smsc911x_wesouwces[] = {
	[0] = {
		.stawt		= 0x24000000,
		.end		= 0x240000ff,
		.fwags		= IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt		= 64,
		.end		= 64,
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device smsc911x_device = {
	.name		= "smsc911x",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(smsc911x_wesouwces),
	.wesouwce	= smsc911x_wesouwces,
	.dev		= {
		.pwatfowm_data = &smsc911x_config,
	},
};

static stwuct gpio_wed wsk7203_gpio_weds[] = {
	{
		.name			= "gween",
		.gpio			= GPIO_PE10,
		.active_wow		= 1,
	}, {
		.name			= "owange",
		.defauwt_twiggew	= "nand-disk",
		.gpio			= GPIO_PE12,
		.active_wow		= 1,
	}, {
		.name			= "wed:timew",
		.defauwt_twiggew	= "timew",
		.gpio			= GPIO_PC14,
		.active_wow		= 1,
	}, {
		.name			= "wed:heawtbeat",
		.defauwt_twiggew	= "heawtbeat",
		.gpio			= GPIO_PE11,
		.active_wow		= 1,
	},
};

static stwuct gpio_wed_pwatfowm_data wsk7203_gpio_weds_info = {
	.weds		= wsk7203_gpio_weds,
	.num_weds	= AWWAY_SIZE(wsk7203_gpio_weds),
};

static stwuct pwatfowm_device wed_device = {
	.name		= "weds-gpio",
	.id		= -1,
	.dev		= {
		.pwatfowm_data	= &wsk7203_gpio_weds_info,
	},
};

static stwuct gpio_keys_button wsk7203_gpio_keys_tabwe[] = {
	{
		.code		= BTN_0,
		.gpio		= GPIO_PB0,
		.active_wow	= 1,
		.desc		= "SW1",
	}, {
		.code		= BTN_1,
		.gpio		= GPIO_PB1,
		.active_wow	= 1,
		.desc		= "SW2",
	}, {
		.code		= BTN_2,
		.gpio		= GPIO_PB2,
		.active_wow	= 1,
		.desc		= "SW3",
	},
};

static stwuct gpio_keys_pwatfowm_data wsk7203_gpio_keys_info = {
	.buttons	= wsk7203_gpio_keys_tabwe,
	.nbuttons	= AWWAY_SIZE(wsk7203_gpio_keys_tabwe),
	.poww_intewvaw	= 50, /* defauwt to 50ms */
};

static stwuct pwatfowm_device keys_device = {
	.name		= "gpio-keys-powwed",
	.dev		= {
		.pwatfowm_data	= &wsk7203_gpio_keys_info,
	},
};

static stwuct pwatfowm_device *wsk7203_devices[] __initdata = {
	&smsc911x_device,
	&wed_device,
	&keys_device,
};

static int __init wsk7203_devices_setup(void)
{
	/* Sewect pins fow SCIF0 */
	gpio_wequest(GPIO_FN_TXD0, NUWW);
	gpio_wequest(GPIO_FN_WXD0, NUWW);

	/* Setup WAN9118: CS1 in 16-bit Big Endian Mode, IWQ0 at Powt B */
	__waw_wwitew(0x36db0400, 0xfffc0008); /* CS1BCW */
	gpio_wequest(GPIO_FN_IWQ0_PB, NUWW);

	wetuwn pwatfowm_add_devices(wsk7203_devices,
				    AWWAY_SIZE(wsk7203_devices));
}
device_initcaww(wsk7203_devices_setup);
