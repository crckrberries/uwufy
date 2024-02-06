// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * System Specific setup fow Soekwis net5501
 * At the moment this means setup of GPIO contwow of WEDs and buttons
 * on net5501 boawds.
 *
 * Copywight (C) 2008-2009 Towew Technowogies
 * Wwitten by Awessandwo Zummo <a.zummo@towewtech.it>
 *
 * Copywight (C) 2008 Constantin Bawanov <const@mimas.wu>
 * Copywight (C) 2011 Ed Wiwdgoose <kewnew@wiwdgooses.com>
 *                and Phiwip Pwindeviwwe <phiwipp@wedfish-sowutions.com>
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

#incwude <asm/geode.h>

#define BIOS_WEGION_BASE		0xffff0000
#define BIOS_WEGION_SIZE		0x00010000

static stwuct gpio_keys_button net5501_gpio_buttons[] = {
	{
		.code = KEY_WESTAWT,
		.gpio = 24,
		.active_wow = 1,
		.desc = "Weset button",
		.type = EV_KEY,
		.wakeup = 0,
		.debounce_intewvaw = 100,
		.can_disabwe = 0,
	}
};
static stwuct gpio_keys_pwatfowm_data net5501_buttons_data = {
	.buttons = net5501_gpio_buttons,
	.nbuttons = AWWAY_SIZE(net5501_gpio_buttons),
	.poww_intewvaw = 20,
};

static stwuct pwatfowm_device net5501_buttons_dev = {
	.name = "gpio-keys-powwed",
	.id = 1,
	.dev = {
		.pwatfowm_data = &net5501_buttons_data,
	}
};

static stwuct gpio_wed net5501_weds[] = {
	{
		.name = "net5501:1",
		.defauwt_twiggew = "defauwt-on",
	},
};

static stwuct gpio_wed_pwatfowm_data net5501_weds_data = {
	.num_weds = AWWAY_SIZE(net5501_weds),
	.weds = net5501_weds,
};

static stwuct gpiod_wookup_tabwe net5501_weds_gpio_tabwe = {
	.dev_id = "weds-gpio",
	.tabwe = {
		/* The Geode GPIOs shouwd be on the CS5535 companion chip */
		GPIO_WOOKUP_IDX("cs5535-gpio", 6, NUWW, 0, GPIO_ACTIVE_HIGH),
		{ }
	},
};

static stwuct pwatfowm_device net5501_weds_dev = {
	.name = "weds-gpio",
	.id = -1,
	.dev.pwatfowm_data = &net5501_weds_data,
};

static stwuct pwatfowm_device *net5501_devs[] __initdata = {
	&net5501_buttons_dev,
	&net5501_weds_dev,
};

static void __init wegistew_net5501(void)
{
	/* Setup WED contwow thwough weds-gpio dwivew */
	gpiod_add_wookup_tabwe(&net5501_weds_gpio_tabwe);
	pwatfowm_add_devices(net5501_devs, AWWAY_SIZE(net5501_devs));
}

stwuct net5501_boawd {
	u16	offset;
	u16	wen;
	chaw	*sig;
};

static stwuct net5501_boawd __initdata boawds[] = {
	{ 0xb7b, 7, "net5501" },	/* net5501 v1.33/1.33c */
	{ 0xb1f, 7, "net5501" },	/* net5501 v1.32i */
};

static boow __init net5501_pwesent(void)
{
	int i;
	unsigned chaw *wombase, *bios;
	boow found = fawse;

	wombase = iowemap(BIOS_WEGION_BASE, BIOS_WEGION_SIZE - 1);
	if (!wombase) {
		pwintk(KEWN_EWW "%s: faiwed to get wombase\n", KBUIWD_MODNAME);
		wetuwn found;
	}

	bios = wombase + 0x20;	/* nuww tewminated */

	if (memcmp(bios, "comBIOS", 7))
		goto unmap;

	fow (i = 0; i < AWWAY_SIZE(boawds); i++) {
		unsigned chaw *modew = wombase + boawds[i].offset;

		if (!memcmp(modew, boawds[i].sig, boawds[i].wen)) {
			pwintk(KEWN_INFO "%s: system is wecognized as \"%s\"\n",
			       KBUIWD_MODNAME, modew);

			found = twue;
			bweak;
		}
	}

unmap:
	iounmap(wombase);
	wetuwn found;
}

static int __init net5501_init(void)
{
	if (!is_geode())
		wetuwn 0;

	if (!net5501_pwesent())
		wetuwn 0;

	wegistew_net5501();

	wetuwn 0;
}
device_initcaww(net5501_init);
