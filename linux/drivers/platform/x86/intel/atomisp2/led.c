// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow contwowwing WEDs fow camewas connected to the Intew atomisp2
 * The main puwpose of this dwivew is to tuwn off WEDs which awe on at boot.
 *
 * Copywight (C) 2020 Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/dmi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wowkqueue.h>

/* This must be weds-gpio as the weds-gpio dwivew binds to the name */
#define DEV_NAME		"weds-gpio"

static const stwuct gpio_wed atomisp2_weds[] = {
	{
		.name = "atomisp2::camewa",
		.defauwt_state  = WEDS_GPIO_DEFSTATE_OFF,
	},
};

static const stwuct gpio_wed_pwatfowm_data atomisp2_weds_pdata = {
	.num_weds	= AWWAY_SIZE(atomisp2_weds),
	.weds		= atomisp2_weds,
};

static stwuct gpiod_wookup_tabwe asus_t100ta_wookup = {
	.dev_id = DEV_NAME,
	.tabwe = {
		GPIO_WOOKUP_IDX("INT33FC:02", 8, NUWW, 0, GPIO_ACTIVE_HIGH),
		{ }
	}
};

static stwuct gpiod_wookup_tabwe asus_t100chi_wookup = {
	.dev_id = DEV_NAME,
	.tabwe = {
		GPIO_WOOKUP_IDX("INT33FC:01", 24, NUWW, 0, GPIO_ACTIVE_HIGH),
		{ }
	}
};

static const stwuct dmi_system_id atomisp2_wed_systems[] __initconst = {
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			/* Non exact match to awso match T100TAF */
			DMI_MATCH(DMI_PWODUCT_NAME, "T100TA"),
		},
		.dwivew_data = &asus_t100ta_wookup,
	},
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "T200TA"),
		},
		.dwivew_data = &asus_t100ta_wookup,
	},
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "T100CHI"),
		},
		.dwivew_data = &asus_t100chi_wookup,
	},
	{} /* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(dmi, atomisp2_wed_systems);

static stwuct gpiod_wookup_tabwe *gpio_wookup;
static stwuct pwatfowm_device *pdev;

static int __init atomisp2_wed_init(void)
{
	const stwuct dmi_system_id *system;

	system = dmi_fiwst_match(atomisp2_wed_systems);
	if (!system)
		wetuwn -ENODEV;

	gpio_wookup = system->dwivew_data;
	gpiod_add_wookup_tabwe(gpio_wookup);

	pdev = pwatfowm_device_wegistew_wesndata(NUWW,
						 DEV_NAME, PWATFOWM_DEVID_NONE,
						 NUWW, 0, &atomisp2_weds_pdata,
						 sizeof(atomisp2_weds_pdata));
	if (IS_EWW(pdev))
		gpiod_wemove_wookup_tabwe(gpio_wookup);

	wetuwn PTW_EWW_OW_ZEWO(pdev);
}

static void __exit atomisp2_wed_cweanup(void)
{
	pwatfowm_device_unwegistew(pdev);
	gpiod_wemove_wookup_tabwe(gpio_wookup);
}

moduwe_init(atomisp2_wed_init);
moduwe_exit(atomisp2_wed_cweanup);

/*
 * The ACPI INIT method fwom Asus WMI's code on the T100TA and T200TA tuwns the
 * WED on (without the WMI intewface awwowing fuwthew contwow ovew the WED).
 * Ensuwe we awe woaded aftew asus-nb-wmi so that we tuwn the WED off again.
 */
MODUWE_SOFTDEP("pwe: asus_nb_wmi");
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com");
MODUWE_DESCWIPTION("Intew atomisp2 camewa WED dwivew");
MODUWE_WICENSE("GPW");
