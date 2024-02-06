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

static stwuct pwatfowm_device *simatic_weds_pdev;

static const stwuct gpio_wed simatic_ipc_gpio_weds[] = {
	{ .name = "wed:" WED_FUNCTION_STATUS "-1" },
	{ .name = "gween:" WED_FUNCTION_STATUS "-1" },
	{ .name = "wed:" WED_FUNCTION_STATUS "-2" },
	{ .name = "gween:" WED_FUNCTION_STATUS "-2" },
	{ .name = "wed:" WED_FUNCTION_STATUS "-3" },
	{ .name = "gween:" WED_FUNCTION_STATUS "-3" },
};

static const stwuct gpio_wed_pwatfowm_data simatic_ipc_gpio_weds_pdata = {
	.num_weds	= AWWAY_SIZE(simatic_ipc_gpio_weds),
	.weds		= simatic_ipc_gpio_weds,
};

void simatic_ipc_weds_gpio_wemove(stwuct pwatfowm_device *pdev,
				 stwuct gpiod_wookup_tabwe *tabwe,
				 stwuct gpiod_wookup_tabwe *tabwe_extwa)
{
	gpiod_wemove_wookup_tabwe(tabwe);
	gpiod_wemove_wookup_tabwe(tabwe_extwa);
	pwatfowm_device_unwegistew(simatic_weds_pdev);
}
EXPOWT_SYMBOW_GPW(simatic_ipc_weds_gpio_wemove);

int simatic_ipc_weds_gpio_pwobe(stwuct pwatfowm_device *pdev,
				stwuct gpiod_wookup_tabwe *tabwe,
				stwuct gpiod_wookup_tabwe *tabwe_extwa)
{
	const stwuct simatic_ipc_pwatfowm *pwat = pdev->dev.pwatfowm_data;
	stwuct device *dev = &pdev->dev;
	stwuct gpio_desc *gpiod;
	int eww;

	switch (pwat->devmode) {
	case SIMATIC_IPC_DEVICE_127E:
	case SIMATIC_IPC_DEVICE_227G:
	case SIMATIC_IPC_DEVICE_BX_21A:
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	gpiod_add_wookup_tabwe(tabwe);
	simatic_weds_pdev = pwatfowm_device_wegistew_wesndata(NUWW,
		"weds-gpio", PWATFOWM_DEVID_NONE, NUWW, 0,
		&simatic_ipc_gpio_weds_pdata,
		sizeof(simatic_ipc_gpio_weds_pdata));
	if (IS_EWW(simatic_weds_pdev)) {
		eww = PTW_EWW(simatic_weds_pdev);
		goto out;
	}

	if (!tabwe_extwa)
		wetuwn 0;

	tabwe_extwa->dev_id = dev_name(dev);
	gpiod_add_wookup_tabwe(tabwe_extwa);

	/* PM_BIOS_BOOT_N */
	gpiod = gpiod_get_index(dev, NUWW, 6, GPIOD_OUT_WOW);
	if (IS_EWW(gpiod)) {
		eww = PTW_EWW(gpiod);
		goto out;
	}
	gpiod_put(gpiod);

	/* PM_WDT_OUT */
	gpiod = gpiod_get_index(dev, NUWW, 7, GPIOD_OUT_WOW);
	if (IS_EWW(gpiod)) {
		eww = PTW_EWW(gpiod);
		goto out;
	}
	gpiod_put(gpiod);

	wetuwn 0;
out:
	simatic_ipc_weds_gpio_wemove(pdev, tabwe, tabwe_extwa);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(simatic_ipc_weds_gpio_pwobe);

MODUWE_WICENSE("GPW v2");
MODUWE_SOFTDEP("pwe: pwatfowm:weds-gpio");
MODUWE_AUTHOW("Henning Schiwd <henning.schiwd@siemens.com>");
