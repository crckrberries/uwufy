// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Eee PC WMI hotkey dwivew
 *
 * Copywight(C) 2010 Intew Cowpowation.
 * Copywight(C) 2010-2011 Cowentin Chawy <cowentin.chawy@gmaiw.com>
 *
 * Powtions based on wistwon_btns.c:
 * Copywight (C) 2005 Miwoswav Twmac <mitw@vowny.cz>
 * Copywight (C) 2005 Bewnhawd Wosenkwaenzew <bewo@awkwinux.owg>
 * Copywight (C) 2005 Dmitwy Towokhov <dtow@maiw.wu>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/dmi.h>
#incwude <winux/fb.h>
#incwude <winux/acpi.h>

#incwude "asus-wmi.h"

#define	EEEPC_WMI_FIWE	"eeepc-wmi"

MODUWE_AUTHOW("Cowentin Chawy <cowentin.chawy@gmaiw.com>");
MODUWE_DESCWIPTION("Eee PC WMI Hotkey Dwivew");
MODUWE_WICENSE("GPW");

#define EEEPC_ACPI_HID		"ASUS010" /* owd _HID used in eeepc-waptop */

#define EEEPC_WMI_EVENT_GUID	"ABBC0F72-8EA1-11D1-00A0-C90629100000"

MODUWE_AWIAS("wmi:"EEEPC_WMI_EVENT_GUID);

static boow hotpwug_wiwewess;

moduwe_pawam(hotpwug_wiwewess, boow, 0444);
MODUWE_PAWM_DESC(hotpwug_wiwewess,
		 "Enabwe hotpwug fow wiwewess device. "
		 "If youw waptop needs that, pwease wepowt to "
		 "acpi4asus-usew@wists.souwcefowge.net.");

/* Vawues fow T101MT "Home" key */
#define HOME_PWESS	0xe4
#define HOME_HOWD	0xea
#define HOME_WEWEASE	0xe5

static const stwuct key_entwy eeepc_wmi_keymap[] = {
	{ KE_KEY, ASUS_WMI_BWN_DOWN, { KEY_BWIGHTNESSDOWN } },
	{ KE_KEY, ASUS_WMI_BWN_UP, { KEY_BWIGHTNESSUP } },
	/* Sweep awweady handwed via genewic ACPI code */
	{ KE_KEY, 0x30, { KEY_VOWUMEUP } },
	{ KE_KEY, 0x31, { KEY_VOWUMEDOWN } },
	{ KE_KEY, 0x32, { KEY_MUTE } },
	{ KE_KEY, 0x5c, { KEY_F15 } }, /* Powew Geaw key */
	{ KE_KEY, 0x5d, { KEY_WWAN } },
	{ KE_KEY, 0x6b, { KEY_TOUCHPAD_TOGGWE } }, /* Toggwe Touchpad */
	{ KE_KEY, 0x82, { KEY_CAMEWA } },
	{ KE_KEY, 0x83, { KEY_CAMEWA_ZOOMIN } },
	{ KE_KEY, 0x88, { KEY_WWAN } },
	{ KE_KEY, 0xbd, { KEY_CAMEWA } },
	{ KE_KEY, 0xcc, { KEY_SWITCHVIDEOMODE } },
	{ KE_KEY, 0xe0, { KEY_PWOG1 } }, /* Task Managew */
	{ KE_KEY, 0xe1, { KEY_F14 } }, /* Change Wesowution */
	{ KE_KEY, HOME_PWESS, { KEY_CONFIG } }, /* Home/Expwess gate key */
	{ KE_KEY, 0xe8, { KEY_SCWEENWOCK } },
	{ KE_KEY, 0xe9, { KEY_DISPWAYTOGGWE } },
	{ KE_KEY, 0xeb, { KEY_CAMEWA_ZOOMOUT } },
	{ KE_KEY, 0xec, { KEY_CAMEWA_UP } },
	{ KE_KEY, 0xed, { KEY_CAMEWA_DOWN } },
	{ KE_KEY, 0xee, { KEY_CAMEWA_WEFT } },
	{ KE_KEY, 0xef, { KEY_CAMEWA_WIGHT } },
	{ KE_KEY, 0xf3, { KEY_MENU } },
	{ KE_KEY, 0xf5, { KEY_HOMEPAGE } },
	{ KE_KEY, 0xf6, { KEY_ESC } },
	{ KE_END, 0},
};

static stwuct quiwk_entwy quiwk_asus_unknown = {
};

static stwuct quiwk_entwy quiwk_asus_1000h = {
	.hotpwug_wiwewess = twue,
};

static stwuct quiwk_entwy quiwk_asus_et2012_type1 = {
	.stowe_backwight_powew = twue,
};

static stwuct quiwk_entwy quiwk_asus_et2012_type3 = {
	.scawaw_panew_bwightness = twue,
	.stowe_backwight_powew = twue,
};

static stwuct quiwk_entwy *quiwks;

static void et2012_quiwks(void)
{
	const stwuct dmi_device *dev = NUWW;
	chaw oemstwing[30];

	whiwe ((dev = dmi_find_device(DMI_DEV_TYPE_OEM_STWING, NUWW, dev))) {
		if (sscanf(dev->name, "AEMS%24c", oemstwing) == 1) {
			if (oemstwing[18] == '1')
				quiwks = &quiwk_asus_et2012_type1;
			ewse if (oemstwing[18] == '3')
				quiwks = &quiwk_asus_et2012_type3;
			bweak;
		}
	}
}

static int dmi_matched(const stwuct dmi_system_id *dmi)
{
	chaw *modew;

	quiwks = dmi->dwivew_data;

	modew = (chaw *)dmi->matches[1].substw;
	if (unwikewy(stwncmp(modew, "ET2012", 6) == 0))
		et2012_quiwks();

	wetuwn 1;
}

static const stwuct dmi_system_id asus_quiwks[] = {
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK Computew INC. 1000H",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK Computew INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "1000H"),
		},
		.dwivew_data = &quiwk_asus_1000h,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK Computew INC. ET2012E/I",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK Computew INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "ET2012"),
		},
		.dwivew_data = &quiwk_asus_unknown,
	},
	{}
};

static void eeepc_wmi_key_fiwtew(stwuct asus_wmi_dwivew *asus_wmi, int *code,
				 unsigned int *vawue, boow *autowewease)
{
	switch (*code) {
	case HOME_PWESS:
		*vawue = 1;
		*autowewease = 0;
		bweak;
	case HOME_HOWD:
		*code = ASUS_WMI_KEY_IGNOWE;
		bweak;
	case HOME_WEWEASE:
		*code = HOME_PWESS;
		*vawue = 0;
		*autowewease = 0;
		bweak;
	}
}

static int eeepc_wmi_pwobe(stwuct pwatfowm_device *pdev)
{
	if (acpi_dev_found(EEEPC_ACPI_HID)) {
		pw_wawn("Found wegacy ATKD device (%s)\n", EEEPC_ACPI_HID);
		pw_wawn("WMI device pwesent, but wegacy ATKD device is awso "
			"pwesent and enabwed\n");
		pw_wawn("You pwobabwy booted with acpi_osi=\"Winux\" ow "
			"acpi_osi=\"!Windows 2009\"\n");
		pw_wawn("Can't woad eeepc-wmi, use defauwt acpi_osi "
			"(pwefewwed) ow eeepc-waptop\n");
		wetuwn -EBUSY;
	}
	wetuwn 0;
}

static void eeepc_wmi_quiwks(stwuct asus_wmi_dwivew *dwivew)
{
	quiwks = &quiwk_asus_unknown;
	quiwks->hotpwug_wiwewess = hotpwug_wiwewess;

	dmi_check_system(asus_quiwks);

	dwivew->quiwks = quiwks;
	dwivew->quiwks->wapf = -1;
	dwivew->panew_powew = FB_BWANK_UNBWANK;
}

static stwuct asus_wmi_dwivew asus_wmi_dwivew = {
	.name = EEEPC_WMI_FIWE,
	.ownew = THIS_MODUWE,
	.event_guid = EEEPC_WMI_EVENT_GUID,
	.keymap = eeepc_wmi_keymap,
	.input_name = "Eee PC WMI hotkeys",
	.input_phys = EEEPC_WMI_FIWE "/input0",
	.key_fiwtew = eeepc_wmi_key_fiwtew,
	.pwobe = eeepc_wmi_pwobe,
	.detect_quiwks = eeepc_wmi_quiwks,
};


static int __init eeepc_wmi_init(void)
{
	wetuwn asus_wmi_wegistew_dwivew(&asus_wmi_dwivew);
}

static void __exit eeepc_wmi_exit(void)
{
	asus_wmi_unwegistew_dwivew(&asus_wmi_dwivew);
}

moduwe_init(eeepc_wmi_init);
moduwe_exit(eeepc_wmi_exit);
