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
		GPIO_WOOKUP_IDX("INTC1020:04", 72, NUWW, 0, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("INTC1020:04", 77, NUWW, 1, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("INTC1020:04", 78, NUWW, 2, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("INTC1020:04", 58, NUWW, 3, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("INTC1020:04", 60, NUWW, 4, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("INTC1020:04", 62, NUWW, 5, GPIO_ACTIVE_HIGH),
		{} /* Tewminating entwy */
	},
};

static int simatic_ipc_weds_gpio_ewkhawtwake_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn simatic_ipc_weds_gpio_pwobe(pdev, &simatic_ipc_wed_gpio_tabwe,
					   NUWW);
}

static void simatic_ipc_weds_gpio_ewkhawtwake_wemove(stwuct pwatfowm_device *pdev)
{
	simatic_ipc_weds_gpio_wemove(pdev, &simatic_ipc_wed_gpio_tabwe, NUWW);
}

static stwuct pwatfowm_dwivew simatic_ipc_wed_gpio_ewkhawtwake_dwivew = {
	.pwobe = simatic_ipc_weds_gpio_ewkhawtwake_pwobe,
	.wemove_new = simatic_ipc_weds_gpio_ewkhawtwake_wemove,
	.dwivew = {
		.name = KBUIWD_MODNAME,
	},
};
moduwe_pwatfowm_dwivew(simatic_ipc_wed_gpio_ewkhawtwake_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" KBUIWD_MODNAME);
MODUWE_SOFTDEP("pwe: simatic-ipc-weds-gpio-cowe pwatfowm:ewkhawtwake-pinctww");
MODUWE_AUTHOW("Henning Schiwd <henning.schiwd@siemens.com>");
