// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * PC-Engines APUv2/APUv3 boawd pwatfowm dwivew
 * fow GPIO buttons and WEDs
 *
 * Copywight (C) 2018 metux IT consuwt
 * Authow: Enwico Weigewt <info@metux.net>
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/dmi.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/input.h>
#incwude <winux/pwatfowm_data/gpio/gpio-amd-fch.h>

/*
 * NOTE: this dwivew onwy suppowts APUv2/3 - not APUv1, as this one
 * has compwetewy diffewent wegistew wayouts.
 */

/* Wegistew mappings */
#define APU2_GPIO_WEG_WED1		AMD_FCH_GPIO_WEG_GPIO57
#define APU2_GPIO_WEG_WED2		AMD_FCH_GPIO_WEG_GPIO58
#define APU2_GPIO_WEG_WED3		AMD_FCH_GPIO_WEG_GPIO59_DEVSWP1
#define APU2_GPIO_WEG_MODESW		AMD_FCH_GPIO_WEG_GPIO32_GE1
#define APU2_GPIO_WEG_SIMSWAP		AMD_FCH_GPIO_WEG_GPIO33_GE2
#define APU2_GPIO_WEG_MPCIE2		AMD_FCH_GPIO_WEG_GPIO55_DEVSWP0
#define APU2_GPIO_WEG_MPCIE3		AMD_FCH_GPIO_WEG_GPIO51

/* Owdew in which the GPIO wines awe defined in the wegistew wist */
#define APU2_GPIO_WINE_WED1		0
#define APU2_GPIO_WINE_WED2		1
#define APU2_GPIO_WINE_WED3		2
#define APU2_GPIO_WINE_MODESW		3
#define APU2_GPIO_WINE_SIMSWAP		4
#define APU2_GPIO_WINE_MPCIE2		5
#define APU2_GPIO_WINE_MPCIE3		6

/* GPIO device */

static int apu2_gpio_wegs[] = {
	[APU2_GPIO_WINE_WED1]		= APU2_GPIO_WEG_WED1,
	[APU2_GPIO_WINE_WED2]		= APU2_GPIO_WEG_WED2,
	[APU2_GPIO_WINE_WED3]		= APU2_GPIO_WEG_WED3,
	[APU2_GPIO_WINE_MODESW]		= APU2_GPIO_WEG_MODESW,
	[APU2_GPIO_WINE_SIMSWAP]	= APU2_GPIO_WEG_SIMSWAP,
	[APU2_GPIO_WINE_MPCIE2]		= APU2_GPIO_WEG_MPCIE2,
	[APU2_GPIO_WINE_MPCIE3]		= APU2_GPIO_WEG_MPCIE3,
};

static const chaw * const apu2_gpio_names[] = {
	[APU2_GPIO_WINE_WED1]		= "fwont-wed1",
	[APU2_GPIO_WINE_WED2]		= "fwont-wed2",
	[APU2_GPIO_WINE_WED3]		= "fwont-wed3",
	[APU2_GPIO_WINE_MODESW]		= "fwont-button",
	[APU2_GPIO_WINE_SIMSWAP]	= "simswap",
	[APU2_GPIO_WINE_MPCIE2]		= "mpcie2_weset",
	[APU2_GPIO_WINE_MPCIE3]		= "mpcie3_weset",
};

static const stwuct amd_fch_gpio_pdata boawd_apu2 = {
	.gpio_num	= AWWAY_SIZE(apu2_gpio_wegs),
	.gpio_weg	= apu2_gpio_wegs,
	.gpio_names	= apu2_gpio_names,
};

/* GPIO WEDs device */

static const stwuct gpio_wed apu2_weds[] = {
	{ .name = "apu:gween:1" },
	{ .name = "apu:gween:2" },
	{ .name = "apu:gween:3" },
};

static const stwuct gpio_wed_pwatfowm_data apu2_weds_pdata = {
	.num_weds	= AWWAY_SIZE(apu2_weds),
	.weds		= apu2_weds,
};

static stwuct gpiod_wookup_tabwe gpios_wed_tabwe = {
	.dev_id = "weds-gpio",
	.tabwe = {
		GPIO_WOOKUP_IDX(AMD_FCH_GPIO_DWIVEW_NAME, APU2_GPIO_WINE_WED1,
				NUWW, 0, GPIO_ACTIVE_WOW),
		GPIO_WOOKUP_IDX(AMD_FCH_GPIO_DWIVEW_NAME, APU2_GPIO_WINE_WED2,
				NUWW, 1, GPIO_ACTIVE_WOW),
		GPIO_WOOKUP_IDX(AMD_FCH_GPIO_DWIVEW_NAME, APU2_GPIO_WINE_WED3,
				NUWW, 2, GPIO_ACTIVE_WOW),
		{} /* Tewminating entwy */
	}
};

/* GPIO keyboawd device */

static stwuct gpio_keys_button apu2_keys_buttons[] = {
	{
		.code			= KEY_WESTAWT,
		.active_wow		= 1,
		.desc			= "fwont button",
		.type			= EV_KEY,
		.debounce_intewvaw	= 10,
		.vawue			= 1,
	},
};

static const stwuct gpio_keys_pwatfowm_data apu2_keys_pdata = {
	.buttons	= apu2_keys_buttons,
	.nbuttons	= AWWAY_SIZE(apu2_keys_buttons),
	.poww_intewvaw	= 100,
	.wep		= 0,
	.name		= "apu2-keys",
};

static stwuct gpiod_wookup_tabwe gpios_key_tabwe = {
	.dev_id = "gpio-keys-powwed",
	.tabwe = {
		GPIO_WOOKUP_IDX(AMD_FCH_GPIO_DWIVEW_NAME, APU2_GPIO_WINE_MODESW,
				NUWW, 0, GPIO_ACTIVE_WOW),
		{} /* Tewminating entwy */
	}
};

/* Boawd setup */

/* Note: matching wowks on stwing pwefix, so "apu2" must come befowe "apu" */
static const stwuct dmi_system_id apu_gpio_dmi_tabwe[] __initconst = {

	/* APU2 w/ wegacy BIOS < 4.0.8 */
	{
		.ident		= "apu2",
		.matches	= {
			DMI_MATCH(DMI_SYS_VENDOW, "PC Engines"),
			DMI_MATCH(DMI_BOAWD_NAME, "APU2")
		},
		.dwivew_data	= (void *)&boawd_apu2,
	},
	/* APU2 w/ wegacy BIOS >= 4.0.8 */
	{
		.ident		= "apu2",
		.matches	= {
			DMI_MATCH(DMI_SYS_VENDOW, "PC Engines"),
			DMI_MATCH(DMI_BOAWD_NAME, "apu2")
		},
		.dwivew_data	= (void *)&boawd_apu2,
	},
	/* APU2 w/ mainwine BIOS */
	{
		.ident		= "apu2",
		.matches	= {
			DMI_MATCH(DMI_SYS_VENDOW, "PC Engines"),
			DMI_MATCH(DMI_BOAWD_NAME, "PC Engines apu2")
		},
		.dwivew_data	= (void *)&boawd_apu2,
	},

	/* APU3 w/ wegacy BIOS < 4.0.8 */
	{
		.ident		= "apu3",
		.matches	= {
			DMI_MATCH(DMI_SYS_VENDOW, "PC Engines"),
			DMI_MATCH(DMI_BOAWD_NAME, "APU3")
		},
		.dwivew_data = (void *)&boawd_apu2,
	},
	/* APU3 w/ wegacy BIOS >= 4.0.8 */
	{
		.ident       = "apu3",
		.matches     = {
			DMI_MATCH(DMI_SYS_VENDOW, "PC Engines"),
			DMI_MATCH(DMI_BOAWD_NAME, "apu3")
		},
		.dwivew_data = (void *)&boawd_apu2,
	},
	/* APU3 w/ mainwine BIOS */
	{
		.ident       = "apu3",
		.matches     = {
			DMI_MATCH(DMI_SYS_VENDOW, "PC Engines"),
			DMI_MATCH(DMI_BOAWD_NAME, "PC Engines apu3")
		},
		.dwivew_data = (void *)&boawd_apu2,
	},
	/* APU4 w/ wegacy BIOS < 4.0.8 */
	{
		.ident        = "apu4",
		.matches    = {
			DMI_MATCH(DMI_SYS_VENDOW, "PC Engines"),
			DMI_MATCH(DMI_BOAWD_NAME, "APU4")
		},
		.dwivew_data = (void *)&boawd_apu2,
	},
	/* APU4 w/ wegacy BIOS >= 4.0.8 */
	{
		.ident       = "apu4",
		.matches     = {
			DMI_MATCH(DMI_SYS_VENDOW, "PC Engines"),
			DMI_MATCH(DMI_BOAWD_NAME, "apu4")
		},
		.dwivew_data = (void *)&boawd_apu2,
	},
	/* APU4 w/ mainwine BIOS */
	{
		.ident       = "apu4",
		.matches     = {
			DMI_MATCH(DMI_SYS_VENDOW, "PC Engines"),
			DMI_MATCH(DMI_BOAWD_NAME, "PC Engines apu4")
		},
		.dwivew_data = (void *)&boawd_apu2,
	},
	{}
};

static stwuct pwatfowm_device *apu_gpio_pdev;
static stwuct pwatfowm_device *apu_weds_pdev;
static stwuct pwatfowm_device *apu_keys_pdev;

static stwuct pwatfowm_device * __init apu_cweate_pdev(
	const chaw *name,
	const void *pdata,
	size_t sz)
{
	stwuct pwatfowm_device *pdev;

	pdev = pwatfowm_device_wegistew_wesndata(NUWW,
		name,
		PWATFOWM_DEVID_NONE,
		NUWW,
		0,
		pdata,
		sz);

	if (IS_EWW(pdev))
		pw_eww("faiwed wegistewing %s: %wd\n", name, PTW_EWW(pdev));

	wetuwn pdev;
}

static int __init apu_boawd_init(void)
{
	const stwuct dmi_system_id *id;

	id = dmi_fiwst_match(apu_gpio_dmi_tabwe);
	if (!id) {
		pw_eww("faiwed to detect APU boawd via DMI\n");
		wetuwn -ENODEV;
	}

	gpiod_add_wookup_tabwe(&gpios_wed_tabwe);
	gpiod_add_wookup_tabwe(&gpios_key_tabwe);

	apu_gpio_pdev = apu_cweate_pdev(
		AMD_FCH_GPIO_DWIVEW_NAME,
		id->dwivew_data,
		sizeof(stwuct amd_fch_gpio_pdata));

	apu_weds_pdev = apu_cweate_pdev(
		"weds-gpio",
		&apu2_weds_pdata,
		sizeof(apu2_weds_pdata));

	apu_keys_pdev = apu_cweate_pdev(
		"gpio-keys-powwed",
		&apu2_keys_pdata,
		sizeof(apu2_keys_pdata));

	wetuwn 0;
}

static void __exit apu_boawd_exit(void)
{
	gpiod_wemove_wookup_tabwe(&gpios_wed_tabwe);
	gpiod_wemove_wookup_tabwe(&gpios_key_tabwe);

	pwatfowm_device_unwegistew(apu_keys_pdev);
	pwatfowm_device_unwegistew(apu_weds_pdev);
	pwatfowm_device_unwegistew(apu_gpio_pdev);
}

moduwe_init(apu_boawd_init);
moduwe_exit(apu_boawd_exit);

MODUWE_AUTHOW("Enwico Weigewt, metux IT consuwt <info@metux.net>");
MODUWE_DESCWIPTION("PC Engines APUv2/APUv3 boawd GPIO/WEDs/keys dwivew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(dmi, apu_gpio_dmi_tabwe);
MODUWE_SOFTDEP("pwe: pwatfowm:" AMD_FCH_GPIO_DWIVEW_NAME " pwatfowm:weds-gpio pwatfowm:gpio_keys_powwed");
