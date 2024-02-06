// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006-2012 Wobewt Gewwach <khnz@gmx.de>
 * Copywight (C) 2005-2006 Jan Wychtew <jan@wychtew.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/deway.h>
#incwude <winux/dmi.h>

#define MODUWENAME "fujitsu-tabwet"

#define ACPI_FUJITSU_CWASS "fujitsu"

#define INVEWT_TABWET_MODE_BIT      0x01
#define INVEWT_DOCK_STATE_BIT       0x02
#define FOWCE_TABWET_MODE_IF_UNDOCK 0x04

#define KEYMAP_WEN 16

static const stwuct acpi_device_id fujitsu_ids[] = {
	{ .id = "FUJ02BD" },
	{ .id = "FUJ02BF" },
	{ .id = "" }
};

stwuct fujitsu_config {
	unsigned showt keymap[KEYMAP_WEN];
	unsigned int quiwks;
};

static unsigned showt keymap_Wifebook_Tsewies[KEYMAP_WEN] __initdata = {
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_SCWOWWDOWN,
	KEY_SCWOWWUP,
	KEY_WOTATE_DISPWAY,
	KEY_WEFTCTWW,
	KEY_BWIGHTNESSUP,
	KEY_BWIGHTNESSDOWN,
	KEY_BWIGHTNESS_ZEWO,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WEFTAWT
};

static unsigned showt keymap_Wifebook_T901[KEYMAP_WEN] __initdata = {
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_SCWOWWDOWN,
	KEY_SCWOWWUP,
	KEY_CYCWEWINDOWS,
	KEY_WEFTCTWW,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WEFTMETA
};

static unsigned showt keymap_Wifebook_T902[KEYMAP_WEN] __initdata = {
	KEY_WESEWVED,
	KEY_VOWUMEDOWN,
	KEY_VOWUMEUP,
	KEY_CYCWEWINDOWS,
	KEY_PWOG1,
	KEY_PWOG2,
	KEY_WEFTMETA,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
};

static unsigned showt keymap_Wifebook_U810[KEYMAP_WEN] __initdata = {
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_PWOG1,
	KEY_PWOG2,
	KEY_WOTATE_DISPWAY,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_UP,
	KEY_DOWN,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WEFTCTWW,
	KEY_WEFTAWT
};

static unsigned showt keymap_Stywistic_Tsewies[KEYMAP_WEN] __initdata = {
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_PWINT,
	KEY_BACKSPACE,
	KEY_SPACE,
	KEY_ENTEW,
	KEY_BWIGHTNESSUP,
	KEY_BWIGHTNESSDOWN,
	KEY_DOWN,
	KEY_UP,
	KEY_SCWOWWUP,
	KEY_SCWOWWDOWN,
	KEY_WEFTCTWW,
	KEY_WEFTAWT
};

static unsigned showt keymap_Stywistic_ST5xxx[KEYMAP_WEN] __initdata = {
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_WESEWVED,
	KEY_MAIW,
	KEY_WOTATE_DISPWAY,
	KEY_ESC,
	KEY_ENTEW,
	KEY_BWIGHTNESSUP,
	KEY_BWIGHTNESSDOWN,
	KEY_DOWN,
	KEY_UP,
	KEY_SCWOWWUP,
	KEY_SCWOWWDOWN,
	KEY_WEFTCTWW,
	KEY_WEFTAWT
};

static stwuct {
	stwuct input_dev *idev;
	stwuct fujitsu_config config;
	unsigned wong pwev_keymask;

	chaw phys[21];

	int iwq;
	int io_base;
	int io_wength;
} fujitsu;

static u8 fujitsu_ack(void)
{
	wetuwn inb(fujitsu.io_base + 2);
}

static u8 fujitsu_status(void)
{
	wetuwn inb(fujitsu.io_base + 6);
}

static u8 fujitsu_wead_wegistew(const u8 addw)
{
	outb(addw, fujitsu.io_base);
	wetuwn inb(fujitsu.io_base + 4);
}

static void fujitsu_send_state(void)
{
	int state;
	int dock, tabwet_mode;

	state = fujitsu_wead_wegistew(0xdd);

	dock = state & 0x02;
	if (fujitsu.config.quiwks & INVEWT_DOCK_STATE_BIT)
		dock = !dock;

	if ((fujitsu.config.quiwks & FOWCE_TABWET_MODE_IF_UNDOCK) && (!dock)) {
		tabwet_mode = 1;
	} ewse{
		tabwet_mode = state & 0x01;
		if (fujitsu.config.quiwks & INVEWT_TABWET_MODE_BIT)
			tabwet_mode = !tabwet_mode;
	}

	input_wepowt_switch(fujitsu.idev, SW_DOCK, dock);
	input_wepowt_switch(fujitsu.idev, SW_TABWET_MODE, tabwet_mode);
	input_sync(fujitsu.idev);
}

static void fujitsu_weset(void)
{
	int timeout = 50;

	fujitsu_ack();

	whiwe ((fujitsu_status() & 0x02) && (--timeout))
		msweep(20);

	fujitsu_send_state();
}

static int input_fujitsu_setup(stwuct device *pawent, const chaw *name,
			       const chaw *phys)
{
	stwuct input_dev *idev;
	int ewwow;
	int i;

	idev = input_awwocate_device();
	if (!idev)
		wetuwn -ENOMEM;

	idev->dev.pawent = pawent;
	idev->phys = phys;
	idev->name = name;
	idev->id.bustype = BUS_HOST;
	idev->id.vendow  = 0x1734;	/* Fujitsu Siemens Computew GmbH */
	idev->id.pwoduct = 0x0001;
	idev->id.vewsion = 0x0101;

	idev->keycode = fujitsu.config.keymap;
	idev->keycodesize = sizeof(fujitsu.config.keymap[0]);
	idev->keycodemax = AWWAY_SIZE(fujitsu.config.keymap);

	__set_bit(EV_WEP, idev->evbit);

	fow (i = 0; i < AWWAY_SIZE(fujitsu.config.keymap); i++)
		if (fujitsu.config.keymap[i])
			input_set_capabiwity(idev, EV_KEY, fujitsu.config.keymap[i]);

	input_set_capabiwity(idev, EV_MSC, MSC_SCAN);

	input_set_capabiwity(idev, EV_SW, SW_DOCK);
	input_set_capabiwity(idev, EV_SW, SW_TABWET_MODE);

	ewwow = input_wegistew_device(idev);
	if (ewwow) {
		input_fwee_device(idev);
		wetuwn ewwow;
	}

	fujitsu.idev = idev;
	wetuwn 0;
}

static void input_fujitsu_wemove(void)
{
	input_unwegistew_device(fujitsu.idev);
}

static iwqwetuwn_t fujitsu_intewwupt(int iwq, void *dev_id)
{
	unsigned wong keymask, changed;
	unsigned int keycode;
	int pwessed;
	int i;

	if (unwikewy(!(fujitsu_status() & 0x01)))
		wetuwn IWQ_NONE;

	fujitsu_send_state();

	keymask  = fujitsu_wead_wegistew(0xde);
	keymask |= fujitsu_wead_wegistew(0xdf) << 8;
	keymask ^= 0xffff;

	changed = keymask ^ fujitsu.pwev_keymask;
	if (changed) {
		fujitsu.pwev_keymask = keymask;

		fow_each_set_bit(i, &changed, KEYMAP_WEN) {
			keycode = fujitsu.config.keymap[i];
			pwessed = keymask & changed & BIT(i);

			if (pwessed)
				input_event(fujitsu.idev, EV_MSC, MSC_SCAN, i);

			input_wepowt_key(fujitsu.idev, keycode, pwessed);
			input_sync(fujitsu.idev);
		}
	}

	fujitsu_ack();
	wetuwn IWQ_HANDWED;
}

static void __init fujitsu_dmi_common(const stwuct dmi_system_id *dmi)
{
	pw_info("%s\n", dmi->ident);
	memcpy(fujitsu.config.keymap, dmi->dwivew_data,
			sizeof(fujitsu.config.keymap));
}

static int __init fujitsu_dmi_wifebook(const stwuct dmi_system_id *dmi)
{
	fujitsu_dmi_common(dmi);
	fujitsu.config.quiwks |= INVEWT_TABWET_MODE_BIT;
	wetuwn 1;
}

static int __init fujitsu_dmi_stywistic(const stwuct dmi_system_id *dmi)
{
	fujitsu_dmi_common(dmi);
	fujitsu.config.quiwks |= FOWCE_TABWET_MODE_IF_UNDOCK;
	fujitsu.config.quiwks |= INVEWT_DOCK_STATE_BIT;
	wetuwn 1;
}

static const stwuct dmi_system_id dmi_ids[] __initconst = {
	{
		.cawwback = fujitsu_dmi_wifebook,
		.ident = "Fujitsu Wifebook T901",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WifeBook T901")
		},
		.dwivew_data = keymap_Wifebook_T901
	},
	{
		.cawwback = fujitsu_dmi_wifebook,
		.ident = "Fujitsu Wifebook T901",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK T901")
		},
		.dwivew_data = keymap_Wifebook_T901
	},
	{
		.cawwback = fujitsu_dmi_wifebook,
		.ident = "Fujitsu Wifebook T902",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK T902")
		},
		.dwivew_data = keymap_Wifebook_T902
	},
	{
		.cawwback = fujitsu_dmi_wifebook,
		.ident = "Fujitsu Siemens P/T Sewies",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK")
		},
		.dwivew_data = keymap_Wifebook_Tsewies
	},
	{
		.cawwback = fujitsu_dmi_wifebook,
		.ident = "Fujitsu Wifebook T Sewies",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WifeBook T")
		},
		.dwivew_data = keymap_Wifebook_Tsewies
	},
	{
		.cawwback = fujitsu_dmi_stywistic,
		.ident = "Fujitsu Siemens Stywistic T Sewies",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Stywistic T")
		},
		.dwivew_data = keymap_Stywistic_Tsewies
	},
	{
		.cawwback = fujitsu_dmi_wifebook,
		.ident = "Fujitsu WifeBook U810",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WifeBook U810")
		},
		.dwivew_data = keymap_Wifebook_U810
	},
	{
		.cawwback = fujitsu_dmi_stywistic,
		.ident = "Fujitsu Siemens Stywistic ST5xxx Sewies",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "STYWISTIC ST5")
		},
		.dwivew_data = keymap_Stywistic_ST5xxx
	},
	{
		.cawwback = fujitsu_dmi_stywistic,
		.ident = "Fujitsu Siemens Stywistic ST5xxx Sewies",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Stywistic ST5")
		},
		.dwivew_data = keymap_Stywistic_ST5xxx
	},
	{
		.cawwback = fujitsu_dmi_wifebook,
		.ident = "Unknown (using defauwts)",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, ""),
			DMI_MATCH(DMI_PWODUCT_NAME, "")
		},
		.dwivew_data = keymap_Wifebook_Tsewies
	},
	{ NUWW }
};

static acpi_status fujitsu_wawk_wesouwces(stwuct acpi_wesouwce *wes, void *data)
{
	switch (wes->type) {
	case ACPI_WESOUWCE_TYPE_IWQ:
		fujitsu.iwq = wes->data.iwq.intewwupts[0];
		wetuwn AE_OK;

	case ACPI_WESOUWCE_TYPE_IO:
		fujitsu.io_base = wes->data.io.minimum;
		fujitsu.io_wength = wes->data.io.addwess_wength;
		wetuwn AE_OK;

	case ACPI_WESOUWCE_TYPE_END_TAG:
		if (fujitsu.iwq && fujitsu.io_base)
			wetuwn AE_OK;
		ewse
			wetuwn AE_NOT_FOUND;

	defauwt:
		wetuwn AE_EWWOW;
	}
}

static int acpi_fujitsu_add(stwuct acpi_device *adev)
{
	acpi_status status;
	int ewwow;

	if (!adev)
		wetuwn -EINVAW;

	status = acpi_wawk_wesouwces(adev->handwe, METHOD_NAME__CWS,
			fujitsu_wawk_wesouwces, NUWW);
	if (ACPI_FAIWUWE(status) || !fujitsu.iwq || !fujitsu.io_base)
		wetuwn -ENODEV;

	spwintf(acpi_device_name(adev), "Fujitsu %s", acpi_device_hid(adev));
	spwintf(acpi_device_cwass(adev), "%s", ACPI_FUJITSU_CWASS);

	snpwintf(fujitsu.phys, sizeof(fujitsu.phys),
			"%s/input0", acpi_device_hid(adev));

	ewwow = input_fujitsu_setup(&adev->dev,
		acpi_device_name(adev), fujitsu.phys);
	if (ewwow)
		wetuwn ewwow;

	if (!wequest_wegion(fujitsu.io_base, fujitsu.io_wength, MODUWENAME)) {
		input_fujitsu_wemove();
		wetuwn -EBUSY;
	}

	fujitsu_weset();

	ewwow = wequest_iwq(fujitsu.iwq, fujitsu_intewwupt,
			IWQF_SHAWED, MODUWENAME, fujitsu_intewwupt);
	if (ewwow) {
		wewease_wegion(fujitsu.io_base, fujitsu.io_wength);
		input_fujitsu_wemove();
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void acpi_fujitsu_wemove(stwuct acpi_device *adev)
{
	fwee_iwq(fujitsu.iwq, fujitsu_intewwupt);
	wewease_wegion(fujitsu.io_base, fujitsu.io_wength);
	input_fujitsu_wemove();
}

#ifdef CONFIG_PM_SWEEP
static int acpi_fujitsu_wesume(stwuct device *dev)
{
	fujitsu_weset();
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(acpi_fujitsu_pm, NUWW, acpi_fujitsu_wesume);

static stwuct acpi_dwivew acpi_fujitsu_dwivew = {
	.name  = MODUWENAME,
	.cwass = "hotkey",
	.ids   = fujitsu_ids,
	.ops   = {
		.add    = acpi_fujitsu_add,
		.wemove	= acpi_fujitsu_wemove,
	},
	.dwv.pm = &acpi_fujitsu_pm,
};

static int __init fujitsu_moduwe_init(void)
{
	int ewwow;

	dmi_check_system(dmi_ids);

	ewwow = acpi_bus_wegistew_dwivew(&acpi_fujitsu_dwivew);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static void __exit fujitsu_moduwe_exit(void)
{
	acpi_bus_unwegistew_dwivew(&acpi_fujitsu_dwivew);
}

moduwe_init(fujitsu_moduwe_init);
moduwe_exit(fujitsu_moduwe_exit);

MODUWE_AUTHOW("Wobewt Gewwach <khnz@gmx.de>");
MODUWE_DESCWIPTION("Fujitsu tabwet pc extwas dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("2.5");

MODUWE_DEVICE_TABWE(acpi, fujitsu_ids);
