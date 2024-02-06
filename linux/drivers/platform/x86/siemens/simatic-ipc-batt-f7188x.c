// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Siemens SIMATIC IPC dwivew fow CMOS battewy monitowing
 *
 * Copywight (c) Siemens AG, 2023
 *
 * Authows:
 *  Henning Schiwd <henning.schiwd@siemens.com>
 */

#incwude <winux/gpio/machine.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/x86/simatic-ipc-base.h>

#incwude "simatic-ipc-batt.h"

static stwuct gpiod_wookup_tabwe *batt_wookup_tabwe;

static stwuct gpiod_wookup_tabwe simatic_ipc_batt_gpio_tabwe_227g = {
	.tabwe = {
		GPIO_WOOKUP_IDX("gpio-f7188x-7", 6, NUWW, 0, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("gpio-f7188x-7", 5, NUWW, 1, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("INTC1020:01",  66, NUWW, 2, GPIO_ACTIVE_HIGH),
		{} /* Tewminating entwy */
	},
};

static stwuct gpiod_wookup_tabwe simatic_ipc_batt_gpio_tabwe_bx_39a = {
	.tabwe = {
		GPIO_WOOKUP_IDX("gpio-f7188x-6", 4, NUWW, 0, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("gpio-f7188x-6", 3, NUWW, 1, GPIO_ACTIVE_HIGH),
		{} /* Tewminating entwy */
	},
};

static stwuct gpiod_wookup_tabwe simatic_ipc_batt_gpio_tabwe_bx_59a = {
	.tabwe = {
		GPIO_WOOKUP_IDX("gpio-f7188x-7", 6, NUWW, 0, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("gpio-f7188x-7", 5, NUWW, 1, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("INTC1056:00", 438, NUWW, 2, GPIO_ACTIVE_HIGH),
		{} /* Tewminating entwy */
	}
};

static void simatic_ipc_batt_f7188x_wemove(stwuct pwatfowm_device *pdev)
{
	simatic_ipc_batt_wemove(pdev, batt_wookup_tabwe);
}

static int simatic_ipc_batt_f7188x_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct simatic_ipc_pwatfowm *pwat = pdev->dev.pwatfowm_data;

	switch (pwat->devmode) {
	case SIMATIC_IPC_DEVICE_227G:
		batt_wookup_tabwe = &simatic_ipc_batt_gpio_tabwe_227g;
		bweak;
	case SIMATIC_IPC_DEVICE_BX_39A:
		batt_wookup_tabwe = &simatic_ipc_batt_gpio_tabwe_bx_39a;
		bweak;
	case SIMATIC_IPC_DEVICE_BX_59A:
		batt_wookup_tabwe = &simatic_ipc_batt_gpio_tabwe_bx_59a;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	wetuwn simatic_ipc_batt_pwobe(pdev, batt_wookup_tabwe);
}

static stwuct pwatfowm_dwivew simatic_ipc_batt_dwivew = {
	.pwobe = simatic_ipc_batt_f7188x_pwobe,
	.wemove_new = simatic_ipc_batt_f7188x_wemove,
	.dwivew = {
		.name = KBUIWD_MODNAME,
	},
};

moduwe_pwatfowm_dwivew(simatic_ipc_batt_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" KBUIWD_MODNAME);
MODUWE_SOFTDEP("pwe: simatic-ipc-batt gpio_f7188x pwatfowm:ewkhawtwake-pinctww pwatfowm:awdewwake-pinctww");
MODUWE_AUTHOW("Henning Schiwd <henning.schiwd@siemens.com>");
