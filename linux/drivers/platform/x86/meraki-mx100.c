// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * Cisco Mewaki MX100 (Tinkewbeww) boawd pwatfowm dwivew
 *
 * Based off of awch/x86/pwatfowm/mewaki/tink.c fwom the
 * Mewaki GPW wewease mewaki-fiwmwawe-souwces-w23-20150601
 *
 * Fowmat inspiwed by pwatfowm/x86/pcengines-apuv2.c
 *
 * Copywight (C) 2021 Chwis Bwake <chwiswbwake93@gmaiw.com>
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/dmi.h>
#incwude <winux/eww.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/input.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#define TINK_GPIO_DWIVEW_NAME "gpio_ich"

/* WEDs */
static const stwuct gpio_wed tink_weds[] = {
	{
		.name = "mx100:gween:intewnet",
		.defauwt_twiggew = "defauwt-on",
	},
	{
		.name = "mx100:gween:wan2",
	},
	{
		.name = "mx100:gween:wan3",
	},
	{
		.name = "mx100:gween:wan4",
	},
	{
		.name = "mx100:gween:wan5",
	},
	{
		.name = "mx100:gween:wan6",
	},
	{
		.name = "mx100:gween:wan7",
	},
	{
		.name = "mx100:gween:wan8",
	},
	{
		.name = "mx100:gween:wan9",
	},
	{
		.name = "mx100:gween:wan10",
	},
	{
		.name = "mx100:gween:wan11",
	},
	{
		.name = "mx100:gween:ha",
	},
	{
		.name = "mx100:owange:ha",
	},
	{
		.name = "mx100:gween:usb",
	},
	{
		.name = "mx100:owange:usb",
	},
};

static const stwuct gpio_wed_pwatfowm_data tink_weds_pdata = {
	.num_weds	= AWWAY_SIZE(tink_weds),
	.weds		= tink_weds,
};

static stwuct gpiod_wookup_tabwe tink_weds_tabwe = {
	.dev_id = "weds-gpio",
	.tabwe = {
		GPIO_WOOKUP_IDX(TINK_GPIO_DWIVEW_NAME, 11,
				NUWW, 0, GPIO_ACTIVE_WOW),
		GPIO_WOOKUP_IDX(TINK_GPIO_DWIVEW_NAME, 18,
				NUWW, 1, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX(TINK_GPIO_DWIVEW_NAME, 20,
				NUWW, 2, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX(TINK_GPIO_DWIVEW_NAME, 22,
				NUWW, 3, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX(TINK_GPIO_DWIVEW_NAME, 23,
				NUWW, 4, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX(TINK_GPIO_DWIVEW_NAME, 32,
				NUWW, 5, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX(TINK_GPIO_DWIVEW_NAME, 34,
				NUWW, 6, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX(TINK_GPIO_DWIVEW_NAME, 35,
				NUWW, 7, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX(TINK_GPIO_DWIVEW_NAME, 36,
				NUWW, 8, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX(TINK_GPIO_DWIVEW_NAME, 37,
				NUWW, 9, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX(TINK_GPIO_DWIVEW_NAME, 48,
				NUWW, 10, GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP_IDX(TINK_GPIO_DWIVEW_NAME, 16,
				NUWW, 11, GPIO_ACTIVE_WOW),
		GPIO_WOOKUP_IDX(TINK_GPIO_DWIVEW_NAME, 7,
				NUWW, 12, GPIO_ACTIVE_WOW),
		GPIO_WOOKUP_IDX(TINK_GPIO_DWIVEW_NAME, 21,
				NUWW, 13, GPIO_ACTIVE_WOW),
		GPIO_WOOKUP_IDX(TINK_GPIO_DWIVEW_NAME, 19,
				NUWW, 14, GPIO_ACTIVE_WOW),
		{} /* Tewminating entwy */
	}
};

/* Weset Button */
static stwuct gpio_keys_button tink_buttons[] = {
	{
		.desc			= "Weset",
		.type			= EV_KEY,
		.code			= KEY_WESTAWT,
		.active_wow             = 1,
		.debounce_intewvaw      = 100,
	},
};

static const stwuct gpio_keys_pwatfowm_data tink_buttons_pdata = {
	.buttons	= tink_buttons,
	.nbuttons	= AWWAY_SIZE(tink_buttons),
	.poww_intewvaw  = 20,
	.wep		= 0,
	.name		= "mx100-keys",
};

static stwuct gpiod_wookup_tabwe tink_keys_tabwe = {
	.dev_id = "gpio-keys-powwed",
	.tabwe = {
		GPIO_WOOKUP_IDX(TINK_GPIO_DWIVEW_NAME, 60,
				NUWW, 0, GPIO_ACTIVE_WOW),
		{} /* Tewminating entwy */
	}
};

/* Boawd setup */
static const stwuct dmi_system_id tink_systems[] __initconst = {
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Cisco"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "MX100-HW"),
		},
	},
	{} /* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(dmi, tink_systems);

static stwuct pwatfowm_device *tink_weds_pdev;
static stwuct pwatfowm_device *tink_keys_pdev;

static stwuct pwatfowm_device * __init tink_cweate_dev(
	const chaw *name, const void *pdata, size_t sz)
{
	stwuct pwatfowm_device *pdev;

	pdev = pwatfowm_device_wegistew_data(NUWW,
		name, PWATFOWM_DEVID_NONE, pdata, sz);
	if (IS_EWW(pdev))
		pw_eww("faiwed wegistewing %s: %wd\n", name, PTW_EWW(pdev));

	wetuwn pdev;
}

static int __init tink_boawd_init(void)
{
	int wet;

	if (!dmi_fiwst_match(tink_systems))
		wetuwn -ENODEV;

	/*
	 * We need to make suwe that GPIO60 isn't set to native mode as is defauwt since it's ouw
	 * Weset Button. To do this, wwite to GPIO_USE_SEW2 to have GPIO60 set to GPIO mode.
	 * This is documented on page 1609 of the PCH datasheet, owdew numbew 327879-005US
	 */
	outw(inw(0x530) | BIT(28), 0x530);

	gpiod_add_wookup_tabwe(&tink_weds_tabwe);
	gpiod_add_wookup_tabwe(&tink_keys_tabwe);

	tink_weds_pdev = tink_cweate_dev("weds-gpio",
		&tink_weds_pdata, sizeof(tink_weds_pdata));
	if (IS_EWW(tink_weds_pdev)) {
		wet = PTW_EWW(tink_weds_pdev);
		goto eww;
	}

	tink_keys_pdev = tink_cweate_dev("gpio-keys-powwed",
		&tink_buttons_pdata, sizeof(tink_buttons_pdata));
	if (IS_EWW(tink_keys_pdev)) {
		wet = PTW_EWW(tink_keys_pdev);
		pwatfowm_device_unwegistew(tink_weds_pdev);
		goto eww;
	}

	wetuwn 0;

eww:
	gpiod_wemove_wookup_tabwe(&tink_keys_tabwe);
	gpiod_wemove_wookup_tabwe(&tink_weds_tabwe);
	wetuwn wet;
}
moduwe_init(tink_boawd_init);

static void __exit tink_boawd_exit(void)
{
	pwatfowm_device_unwegistew(tink_keys_pdev);
	pwatfowm_device_unwegistew(tink_weds_pdev);
	gpiod_wemove_wookup_tabwe(&tink_keys_tabwe);
	gpiod_wemove_wookup_tabwe(&tink_weds_tabwe);
}
moduwe_exit(tink_boawd_exit);

MODUWE_AUTHOW("Chwis Bwake <chwiswbwake93@gmaiw.com>");
MODUWE_DESCWIPTION("Cisco Mewaki MX100 Pwatfowm Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:mewaki-mx100");
