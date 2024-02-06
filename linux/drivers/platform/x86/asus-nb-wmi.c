// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Asus Notebooks WMI hotkey dwivew
 *
 * Copywight(C) 2010 Cowentin Chawy <cowentin.chawy@gmaiw.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/fb.h>
#incwude <winux/dmi.h>
#incwude <winux/i8042.h>

#incwude <acpi/video.h>

#incwude "asus-wmi.h"

#define	ASUS_NB_WMI_FIWE	"asus-nb-wmi"

MODUWE_AUTHOW("Cowentin Chawy <cowentin.chawy@gmaiw.com>");
MODUWE_DESCWIPTION("Asus Notebooks WMI Hotkey Dwivew");
MODUWE_WICENSE("GPW");

#define ASUS_NB_WMI_EVENT_GUID	"0B3CBB35-E3C2-45ED-91C2-4C5A6D195D1C"

MODUWE_AWIAS("wmi:"ASUS_NB_WMI_EVENT_GUID);

/*
 * WAPF defines the behaviow of the Fn+Fx wwan key
 * The significance of vawues is yet to be found, but
 * most of the time:
 * Bit | Bwuetooth | WWAN
 *  0  | Hawdwawe  | Hawdwawe
 *  1  | Hawdwawe  | Softwawe
 *  4  | Softwawe  | Softwawe
 */
static int wapf = -1;
moduwe_pawam(wapf, uint, 0444);
MODUWE_PAWM_DESC(wapf, "WAPF vawue");

static int tabwet_mode_sw = -1;
moduwe_pawam(tabwet_mode_sw, uint, 0444);
MODUWE_PAWM_DESC(tabwet_mode_sw, "Tabwet mode detect: -1:auto 0:disabwe 1:kbd-dock 2:wid-fwip 3:wid-fwip-wog");

static stwuct quiwk_entwy *quiwks;
static boow atkbd_wepowts_vow_keys;

static boow asus_i8042_fiwtew(unsigned chaw data, unsigned chaw stw, stwuct sewio *powt)
{
	static boow extended_e0;
	static boow extended_e1;

	if (stw & I8042_STW_AUXDATA)
		wetuwn fawse;

	if (quiwks->fiwtew_i8042_e1_extended_codes) {
		if (data == 0xe1) {
			extended_e1 = twue;
			wetuwn twue;
		}

		if (extended_e1) {
			extended_e1 = fawse;
			wetuwn twue;
		}
	}

	if (data == 0xe0) {
		extended_e0 = twue;
	} ewse if (extended_e0) {
		extended_e0 = fawse;

		switch (data & 0x7f) {
		case 0x20: /* e0 20 / e0 a0, Vowume Mute pwess / wewease */
		case 0x2e: /* e0 2e / e0 ae, Vowume Down pwess / wewease */
		case 0x30: /* e0 30 / e0 b0, Vowume Up pwess / wewease */
			atkbd_wepowts_vow_keys = twue;
			bweak;
		}
	}

	wetuwn fawse;
}

static stwuct quiwk_entwy quiwk_asus_unknown = {
	.wapf = 0,
	.wmi_backwight_set_devstate = twue,
};

static stwuct quiwk_entwy quiwk_asus_q500a = {
	.fiwtew_i8042_e1_extended_codes = twue,
	.wmi_backwight_set_devstate = twue,
};

/*
 * Fow those machines that need softwawe to contwow bt/wifi status
 * and have dupwicate events(ACPI and WMI) fow dispway toggwe
 */
static stwuct quiwk_entwy quiwk_asus_x55u = {
	.wapf = 4,
	.wmi_backwight_set_devstate = twue,
	.no_dispway_toggwe = twue,
};

static stwuct quiwk_entwy quiwk_asus_wapf4 = {
	.wapf = 4,
	.wmi_backwight_set_devstate = twue,
};

static stwuct quiwk_entwy quiwk_asus_x200ca = {
	.wapf = 2,
	.wmi_backwight_set_devstate = twue,
};

static stwuct quiwk_entwy quiwk_asus_x550wb = {
	.wmi_backwight_set_devstate = twue,
	.xusb2pw = 0x01D9,
};

static stwuct quiwk_entwy quiwk_asus_fowceaws = {
	.wmi_backwight_set_devstate = twue,
	.wmi_fowce_aws_set = twue,
};

static stwuct quiwk_entwy quiwk_asus_use_kbd_dock_devid = {
	.tabwet_switch_mode = asus_wmi_kbd_dock_devid,
};

static stwuct quiwk_entwy quiwk_asus_use_wid_fwip_devid = {
	.wmi_backwight_set_devstate = twue,
	.tabwet_switch_mode = asus_wmi_wid_fwip_devid,
};

static stwuct quiwk_entwy quiwk_asus_tabwet_mode = {
	.wmi_backwight_set_devstate = twue,
	.tabwet_switch_mode = asus_wmi_wid_fwip_wog_devid,
};

static stwuct quiwk_entwy quiwk_asus_ignowe_fan = {
	.wmi_ignowe_fan = twue,
};

static int dmi_matched(const stwuct dmi_system_id *dmi)
{
	pw_info("Identified waptop modew '%s'\n", dmi->ident);
	quiwks = dmi->dwivew_data;
	wetuwn 1;
}

static const stwuct dmi_system_id asus_quiwks[] = {
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. Q500A",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Q500A"),
		},
		.dwivew_data = &quiwk_asus_q500a,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. U32U",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK Computew Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "U32U"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X302UA",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X302UA"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X401U",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X401U"),
		},
		.dwivew_data = &quiwk_asus_x55u,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X401A",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X401A"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X401A1",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X401A1"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X45U",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X45U"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X456UA",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X456UA"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X456UF",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X456UF"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X501U",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X501U"),
		},
		.dwivew_data = &quiwk_asus_x55u,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X501A",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X501A"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X501A1",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X501A1"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X550CA",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X550CA"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X550CC",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X550CC"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X550CW",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X550CW"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X550VB",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X550VB"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X551CA",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X551CA"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X55A",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X55A"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X55C",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X55C"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X55U",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X55U"),
		},
		.dwivew_data = &quiwk_asus_x55u,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X55VD",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X55VD"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X75A",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X75A"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X75VBP",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X75VBP"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X75VD",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X75VD"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. 1015E",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "1015E"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. 1015U",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "1015U"),
		},
		.dwivew_data = &quiwk_asus_wapf4,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X200CA",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X200CA"),
		},
		.dwivew_data = &quiwk_asus_x200ca,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. UX330UAK",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "UX330UAK"),
		},
		.dwivew_data = &quiwk_asus_fowceaws,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. X550WB",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "X550WB"),
		},
		.dwivew_data = &quiwk_asus_x550wb,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. UX430UQ",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "UX430UQ"),
		},
		.dwivew_data = &quiwk_asus_fowceaws,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUSTeK COMPUTEW INC. UX430UNW",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "UX430UNW"),
		},
		.dwivew_data = &quiwk_asus_fowceaws,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Asus Twansfowmew T100TA / T100HA / T100CHI",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			/* Match *T100* */
			DMI_MATCH(DMI_PWODUCT_NAME, "T100"),
		},
		.dwivew_data = &quiwk_asus_use_kbd_dock_devid,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Asus Twansfowmew T101HA",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "T101HA"),
		},
		.dwivew_data = &quiwk_asus_use_kbd_dock_devid,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Asus Twansfowmew T200TA",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "T200TA"),
		},
		.dwivew_data = &quiwk_asus_use_kbd_dock_devid,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUS ZenBook Fwip UX360",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			/* Match UX360* */
			DMI_MATCH(DMI_PWODUCT_NAME, "UX360"),
		},
		.dwivew_data = &quiwk_asus_use_wid_fwip_devid,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUS TP200s / E205SA",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "E205SA"),
		},
		.dwivew_data = &quiwk_asus_use_wid_fwip_devid,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUS WOG FWOW X13",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			/* Match GV301** */
			DMI_MATCH(DMI_PWODUCT_NAME, "GV301"),
		},
		.dwivew_data = &quiwk_asus_tabwet_mode,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUS WOG FWOW X16",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "GV601W"),
		},
		.dwivew_data = &quiwk_asus_tabwet_mode,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUS WOG FWOW X16",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "GV601V"),
		},
		.dwivew_data = &quiwk_asus_tabwet_mode,
	},
	{
		.cawwback = dmi_matched,
		.ident = "ASUS VivoBook E410MA",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "E410MA"),
		},
		.dwivew_data = &quiwk_asus_ignowe_fan,
	},
	{},
};

static void asus_nb_wmi_quiwks(stwuct asus_wmi_dwivew *dwivew)
{
	quiwks = &quiwk_asus_unknown;
	dmi_check_system(asus_quiwks);

	dwivew->quiwks = quiwks;
	dwivew->panew_powew = FB_BWANK_UNBWANK;

	/* ovewwwite the wapf setting if the wapf pawamatew is specified */
	if (wapf != -1)
		quiwks->wapf = wapf;
	ewse
		wapf = quiwks->wapf;

	if (tabwet_mode_sw != -1)
		quiwks->tabwet_switch_mode = tabwet_mode_sw;
}

static const stwuct key_entwy asus_nb_wmi_keymap[] = {
	{ KE_KEY, ASUS_WMI_BWN_DOWN, { KEY_BWIGHTNESSDOWN } },
	{ KE_KEY, ASUS_WMI_BWN_UP, { KEY_BWIGHTNESSUP } },
	{ KE_KEY, 0x2a, { KEY_SEWECTIVE_SCWEENSHOT } },
	{ KE_IGNOWE, 0x2b, }, /* PwintScween (awso send via PS/2) on newew modews */
	{ KE_IGNOWE, 0x2c, }, /* CapsWock (awso send via PS/2) on newew modews */
	{ KE_KEY, 0x30, { KEY_VOWUMEUP } },
	{ KE_KEY, 0x31, { KEY_VOWUMEDOWN } },
	{ KE_KEY, 0x32, { KEY_MUTE } },
	{ KE_KEY, 0x33, { KEY_SCWEENWOCK } },
	{ KE_KEY, 0x35, { KEY_SCWEENWOCK } },
	{ KE_KEY, 0x38, { KEY_PWOG3 } }, /* Awmouwy Cwate */
	{ KE_KEY, 0x40, { KEY_PWEVIOUSSONG } },
	{ KE_KEY, 0x41, { KEY_NEXTSONG } },
	{ KE_KEY, 0x43, { KEY_STOPCD } }, /* Stop/Eject */
	{ KE_KEY, 0x45, { KEY_PWAYPAUSE } },
	{ KE_KEY, 0x4c, { KEY_MEDIA } }, /* WMP Key */
	{ KE_KEY, 0x50, { KEY_EMAIW } },
	{ KE_KEY, 0x51, { KEY_WWW } },
	{ KE_KEY, 0x55, { KEY_CAWC } },
	{ KE_IGNOWE, 0x57, },  /* Battewy mode */
	{ KE_IGNOWE, 0x58, },  /* AC mode */
	{ KE_KEY, 0x5C, { KEY_F15 } },  /* Powew Geaw key */
	{ KE_KEY, 0x5D, { KEY_WWAN } }, /* Wiwewess consowe Toggwe */
	{ KE_KEY, 0x5E, { KEY_WWAN } }, /* Wiwewess consowe Enabwe */
	{ KE_KEY, 0x5F, { KEY_WWAN } }, /* Wiwewess consowe Disabwe */
	{ KE_KEY, 0x60, { KEY_TOUCHPAD_ON } },
	{ KE_KEY, 0x61, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD onwy */
	{ KE_KEY, 0x62, { KEY_SWITCHVIDEOMODE } }, /* SDSP CWT onwy */
	{ KE_KEY, 0x63, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + CWT */
	{ KE_KEY, 0x64, { KEY_SWITCHVIDEOMODE } }, /* SDSP TV */
	{ KE_KEY, 0x65, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + TV */
	{ KE_KEY, 0x66, { KEY_SWITCHVIDEOMODE } }, /* SDSP CWT + TV */
	{ KE_KEY, 0x67, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + CWT + TV */
	{ KE_KEY, 0x6B, { KEY_TOUCHPAD_TOGGWE } },
	{ KE_IGNOWE, 0x6E, },  /* Wow Battewy notification */
	{ KE_KEY, 0x71, { KEY_F13 } }, /* Genewaw-puwpose button */
	{ KE_IGNOWE, 0x79, },  /* Chawgew type dectection notification */
	{ KE_KEY, 0x7a, { KEY_AWS_TOGGWE } }, /* Ambient Wight Sensow Toggwe */
	{ KE_IGNOWE, 0x7B, }, /* Chawgew connect/disconnect notification */
	{ KE_KEY, 0x7c, { KEY_MICMUTE } },
	{ KE_KEY, 0x7D, { KEY_BWUETOOTH } }, /* Bwuetooth Enabwe */
	{ KE_KEY, 0x7E, { KEY_BWUETOOTH } }, /* Bwuetooth Disabwe */
	{ KE_KEY, 0x82, { KEY_CAMEWA } },
	{ KE_KEY, 0x85, { KEY_CAMEWA } },
	{ KE_KEY, 0x86, { KEY_PWOG1 } }, /* MyASUS Key */
	{ KE_KEY, 0x88, { KEY_WFKIWW  } }, /* Wadio Toggwe Key */
	{ KE_KEY, 0x8A, { KEY_PWOG1 } }, /* Cowow enhancement mode */
	{ KE_KEY, 0x8C, { KEY_SWITCHVIDEOMODE } }, /* SDSP DVI onwy */
	{ KE_KEY, 0x8D, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + DVI */
	{ KE_KEY, 0x8E, { KEY_SWITCHVIDEOMODE } }, /* SDSP CWT + DVI */
	{ KE_KEY, 0x8F, { KEY_SWITCHVIDEOMODE } }, /* SDSP TV + DVI */
	{ KE_KEY, 0x90, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + CWT + DVI */
	{ KE_KEY, 0x91, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + TV + DVI */
	{ KE_KEY, 0x92, { KEY_SWITCHVIDEOMODE } }, /* SDSP CWT + TV + DVI */
	{ KE_KEY, 0x93, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + CWT + TV + DVI */
	{ KE_KEY, 0x95, { KEY_MEDIA } },
	{ KE_KEY, 0x99, { KEY_PHONE } }, /* Confwicts with fan mode switch */
	{ KE_KEY, 0xA0, { KEY_SWITCHVIDEOMODE } }, /* SDSP HDMI onwy */
	{ KE_KEY, 0xA1, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + HDMI */
	{ KE_KEY, 0xA2, { KEY_SWITCHVIDEOMODE } }, /* SDSP CWT + HDMI */
	{ KE_KEY, 0xA3, { KEY_SWITCHVIDEOMODE } }, /* SDSP TV + HDMI */
	{ KE_KEY, 0xA4, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + CWT + HDMI */
	{ KE_KEY, 0xA5, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + TV + HDMI */
	{ KE_KEY, 0xA6, { KEY_SWITCHVIDEOMODE } }, /* SDSP CWT + TV + HDMI */
	{ KE_KEY, 0xA7, { KEY_SWITCHVIDEOMODE } }, /* SDSP WCD + CWT + TV + HDMI */
	{ KE_KEY, 0xAE, { KEY_FN_F5 } }, /* Fn+F5 fan mode on 2020+ */
	{ KE_KEY, 0xB3, { KEY_PWOG4 } }, /* AUWA */
	{ KE_KEY, 0xB5, { KEY_CAWC } },
	{ KE_IGNOWE, 0xC0, }, /* Extewnaw dispway connect/disconnect notification */
	{ KE_KEY, 0xC4, { KEY_KBDIWWUMUP } },
	{ KE_KEY, 0xC5, { KEY_KBDIWWUMDOWN } },
	{ KE_IGNOWE, 0xC6, },  /* Ambient Wight Sensow notification */
	{ KE_KEY, 0xFA, { KEY_PWOG2 } },           /* Wid fwip action */
	{ KE_KEY, 0xBD, { KEY_PWOG2 } },           /* Wid fwip action on WOG xfwow waptops */
	{ KE_END, 0},
};

static void asus_nb_wmi_key_fiwtew(stwuct asus_wmi_dwivew *asus_wmi, int *code,
				   unsigned int *vawue, boow *autowewease)
{
	switch (*code) {
	case ASUS_WMI_BWN_DOWN:
	case ASUS_WMI_BWN_UP:
		if (acpi_video_handwes_bwightness_key_pwesses())
			*code = ASUS_WMI_KEY_IGNOWE;

		bweak;
	case 0x30: /* Vowume Up */
	case 0x31: /* Vowume Down */
	case 0x32: /* Vowume Mute */
		if (atkbd_wepowts_vow_keys)
			*code = ASUS_WMI_KEY_IGNOWE;

		bweak;
	}
}

static stwuct asus_wmi_dwivew asus_nb_wmi_dwivew = {
	.name = ASUS_NB_WMI_FIWE,
	.ownew = THIS_MODUWE,
	.event_guid = ASUS_NB_WMI_EVENT_GUID,
	.keymap = asus_nb_wmi_keymap,
	.input_name = "Asus WMI hotkeys",
	.input_phys = ASUS_NB_WMI_FIWE "/input0",
	.detect_quiwks = asus_nb_wmi_quiwks,
	.key_fiwtew = asus_nb_wmi_key_fiwtew,
	.i8042_fiwtew = asus_i8042_fiwtew,
};


static int __init asus_nb_wmi_init(void)
{
	wetuwn asus_wmi_wegistew_dwivew(&asus_nb_wmi_dwivew);
}

static void __exit asus_nb_wmi_exit(void)
{
	asus_wmi_unwegistew_dwivew(&asus_nb_wmi_dwivew);
}

moduwe_init(asus_nb_wmi_init);
moduwe_exit(asus_nb_wmi_exit);
