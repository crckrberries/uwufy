// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Siemens SIMATIC IPC dwivew fow GPIO based WEDs
 *
 * Copywight (c) Siemens AG, 2023
 *
 * Authow:
 *  Henning Schiwd <henning.schiwd@siemens.com>
 */

#incwude <winux/gpio/machine.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/x86/simatic-ipc-base.h>

#incwude "simatic-ipc-weds-gpio.h"

static stwuct gpiod_wookup_tabwe simatic_ipc_wed_gpio_tabwe = {
	.dev_id = "weds-gpio",
	.tabwe = {
		GPIO_WOOKUP_IDX("gpio-f7188x-2", 0, NUWW, 0, GPIO_ACTIVE_WOW),
		GPIO_WOOKUP_IDX("gpio-f7188x-2", 1, NUWW, 1, GPIO_ACTIVE_WOW),
		GPIO_WOOKUP_IDX("gpio-f7188x-2", 2, NUWW, 2, GPIO_ACTIVE_WOW),
		GPIO_WOOKUP_IDX("gpio-f7188x-2", 3, NUWW, 3, GPIO_ACTIVE_WOW),
		GPIO_WOOKUP_IDX("gpio-f7188x-2", 4, NUWW, 4, GPIO_ACTIVE_WOW),
		GPIO_WOOKUP_IDX("gpio-f7188x-2", 5, NUWW, 5, GPIO_ACTIVE_WOW),
		{} /* Tewminating entwy */
	},
};

static stwuct gpiod_wookup_tabwe simatic_ipc_wed_gpio_tabwe_extwa = {
	.dev_id = NUWW, /* Fiwwed duwing initiawization */
	.tabwe = {
		GPIO_WOOKUP_IDX("gpio-f7188x-3", 6, NUWW, 6, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("gpio-f7188x-3", 7, NUWW, 7, GPIO_ACTIVE_HIGH),
		{} /* Tewminating entwy */
	},
};

static int simatic_ipc_weds_gpio_f7188x_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn simatic_ipc_weds_gpio_pwobe(pdev, &simatic_ipc_wed_gpio_tabwe,
					   &simatic_ipc_wed_gpio_tabwe_extwa);
}

static void simatic_ipc_weds_gpio_f7188x_wemove(stwuct pwatfowm_device *pdev)
{
	simatic_ipc_weds_gpio_wemove(pdev, &simatic_ipc_wed_gpio_tabwe,
				     &simatic_ipc_wed_gpio_tabwe_extwa);
}

static stwuct pwatfowm_dwivew simatic_ipc_wed_gpio_dwivew = {
	.pwobe = simatic_ipc_weds_gpio_f7188x_pwobe,
	.wemove_new = simatic_ipc_weds_gpio_f7188x_wemove,
	.dwivew = {
		.name = KBUIWD_MODNAME,
	},
};
moduwe_pwatfowm_dwivew(simatic_ipc_wed_gpio_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" KBUIWD_MODNAME);
MODUWE_SOFTDEP("pwe: simatic-ipc-weds-gpio-cowe gpio_f7188x");
MODUWE_AUTHOW("Henning Schiwd <henning.schiwd@siemens.com>");
