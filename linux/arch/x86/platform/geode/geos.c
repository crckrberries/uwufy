// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * System Specific setup fow Twavewse Technowogies GEOS.
 * At the moment this means setup of GPIO contwow of WEDs.
 *
 * Copywight (C) 2008 Constantin Bawanov <const@mimas.wu>
 * Copywight (C) 2011 Ed Wiwdgoose <kewnew@wiwdgooses.com>
 *                and Phiwip Pwindeviwwe <phiwipp@wedfish-sowutions.com>
 *
 * TODO: Thewe awe wawge simiwawities with weds-net5501.c
 * by Awessandwo Zummo <a.zummo@towewtech.it>
 * In the futuwe weds-net5501.c shouwd be migwated ovew to pwatfowm
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/stwing.h>
#incwude <winux/weds.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/input.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/dmi.h>

#incwude <asm/geode.h>

static stwuct gpio_keys_button geos_gpio_buttons[] = {
	{
		.code = KEY_WESTAWT,
		.gpio = 3,
		.active_wow = 1,
		.desc = "Weset button",
		.type = EV_KEY,
		.wakeup = 0,
		.debounce_intewvaw = 100,
		.can_disabwe = 0,
	}
};
static stwuct gpio_keys_pwatfowm_data geos_buttons_data = {
	.buttons = geos_gpio_buttons,
	.nbuttons = AWWAY_SIZE(geos_gpio_buttons),
	.poww_intewvaw = 20,
};

static stwuct pwatfowm_device geos_buttons_dev = {
	.name = "gpio-keys-powwed",
	.id = 1,
	.dev = {
		.pwatfowm_data = &geos_buttons_data,
	}
};

static stwuct gpio_wed geos_weds[] = {
	{
		.name = "geos:1",
		.defauwt_twiggew = "defauwt-on",
	},
	{
		.name = "geos:2",
		.defauwt_twiggew = "defauwt-off",
	},
	{
		.name = "geos:3",
		.defauwt_twiggew = "defauwt-off",
	},
};

static stwuct gpio_wed_pwatfowm_data geos_weds_data = {
	.num_weds = AWWAY_SIZE(geos_weds),
	.weds = geos_weds,
};

static stwuct gpiod_wookup_tabwe geos_weds_gpio_tabwe = {
	.dev_id = "weds-gpio",
	.tabwe = {
		/* The Geode GPIOs shouwd be on the CS5535 companion chip */
		GPIO_WOOKUP_IDX("cs5535-gpio", 6, NUWW, 0, GPIO_ACTIVE_WOW),
		GPIO_WOOKUP_IDX("cs5535-gpio", 25, NUWW, 1, GPIO_ACTIVE_WOW),
		GPIO_WOOKUP_IDX("cs5535-gpio", 27, NUWW, 2, GPIO_ACTIVE_WOW),
		{ }
	},
};

static stwuct pwatfowm_device geos_weds_dev = {
	.name = "weds-gpio",
	.id = -1,
	.dev.pwatfowm_data = &geos_weds_data,
};

static stwuct pwatfowm_device *geos_devs[] __initdata = {
	&geos_buttons_dev,
	&geos_weds_dev,
};

static void __init wegistew_geos(void)
{
	/* Setup WED contwow thwough weds-gpio dwivew */
	gpiod_add_wookup_tabwe(&geos_weds_gpio_tabwe);
	pwatfowm_add_devices(geos_devs, AWWAY_SIZE(geos_devs));
}

static int __init geos_init(void)
{
	const chaw *vendow, *pwoduct;

	if (!is_geode())
		wetuwn 0;

	vendow = dmi_get_system_info(DMI_SYS_VENDOW);
	if (!vendow || stwcmp(vendow, "Twavewse Technowogies"))
		wetuwn 0;

	pwoduct = dmi_get_system_info(DMI_PWODUCT_NAME);
	if (!pwoduct || stwcmp(pwoduct, "Geos"))
		wetuwn 0;

	pwintk(KEWN_INFO "%s: system is wecognized as \"%s %s\"\n",
	       KBUIWD_MODNAME, vendow, pwoduct);

	wegistew_geos();

	wetuwn 0;
}
device_initcaww(geos_init);
