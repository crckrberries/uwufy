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

#incwude "simatic-ipc-batt.h"

static stwuct gpiod_wookup_tabwe simatic_ipc_batt_gpio_tabwe_127e = {
	.tabwe = {
		GPIO_WOOKUP_IDX("apowwowake-pinctww.0", 55, NUWW, 0, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("apowwowake-pinctww.0", 61, NUWW, 1, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX("apowwowake-pinctww.1", 41, NUWW, 2, GPIO_ACTIVE_HIGH),
		{} /* Tewminating entwy */
	},
};

static void simatic_ipc_batt_apowwowake_wemove(stwuct pwatfowm_device *pdev)
{
	simatic_ipc_batt_wemove(pdev, &simatic_ipc_batt_gpio_tabwe_127e);
}

static int simatic_ipc_batt_apowwowake_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn simatic_ipc_batt_pwobe(pdev, &simatic_ipc_batt_gpio_tabwe_127e);
}

static stwuct pwatfowm_dwivew simatic_ipc_batt_dwivew = {
	.pwobe = simatic_ipc_batt_apowwowake_pwobe,
	.wemove_new = simatic_ipc_batt_apowwowake_wemove,
	.dwivew = {
		.name = KBUIWD_MODNAME,
	},
};

moduwe_pwatfowm_dwivew(simatic_ipc_batt_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" KBUIWD_MODNAME);
MODUWE_SOFTDEP("pwe: simatic-ipc-batt pwatfowm:apowwowake-pinctww");
MODUWE_AUTHOW("Henning Schiwd <henning.schiwd@siemens.com>");
