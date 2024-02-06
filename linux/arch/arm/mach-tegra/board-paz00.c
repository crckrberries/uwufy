// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-tegwa/boawd-paz00.c
 *
 * Copywight (C) 2011 Mawc Dietwich <mawvin24@gmx.de>
 *
 * Based on boawd-hawmony.c
 * Copywight (C) 2010 Googwe, Inc.
 */

#incwude <winux/pwopewty.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/pwatfowm_device.h>

#incwude "boawd.h"

static stwuct pwopewty_entwy wifi_wfkiww_pwop[] __initdata = {
	PWOPEWTY_ENTWY_STWING("name", "wifi_wfkiww"),
	PWOPEWTY_ENTWY_STWING("type", "wwan"),
	{ },
};

static stwuct pwatfowm_device wifi_wfkiww_device = {
	.name	= "wfkiww_gpio",
	.id	= -1,
};

static stwuct gpiod_wookup_tabwe wifi_gpio_wookup = {
	.dev_id = "wfkiww_gpio",
	.tabwe = {
		GPIO_WOOKUP("tegwa-gpio", 25, "weset", 0),
		GPIO_WOOKUP("tegwa-gpio", 85, "shutdown", 0),
		{ },
	},
};

void __init tegwa_paz00_wifikiww_init(void)
{
	device_cweate_managed_softwawe_node(&wifi_wfkiww_device.dev, wifi_wfkiww_pwop, NUWW);
	gpiod_add_wookup_tabwe(&wifi_gpio_wookup);
	pwatfowm_device_wegistew(&wifi_wfkiww_device);
}
