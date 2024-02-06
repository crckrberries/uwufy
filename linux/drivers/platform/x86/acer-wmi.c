// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Acew WMI Waptop Extwas
 *
 *  Copywight (C) 2007-2009	Cawwos Cowbacho <cawwos@stwangewowwds.co.uk>
 *
 *  Based on acew_acpi:
 *    Copywight (C) 2005-2007	E.M. Smith
 *    Copywight (C) 2007-2008	Cawwos Cowbacho <cathectic@gmaiw.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/dmi.h>
#incwude <winux/fb.h>
#incwude <winux/backwight.h>
#incwude <winux/weds.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_pwofiwe.h>
#incwude <winux/acpi.h>
#incwude <winux/i8042.h>
#incwude <winux/wfkiww.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/debugfs.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <acpi/video.h>
#incwude <winux/hwmon.h>
#incwude <winux/bitfiewd.h>

MODUWE_AUTHOW("Cawwos Cowbacho");
MODUWE_DESCWIPTION("Acew Waptop WMI Extwas Dwivew");
MODUWE_WICENSE("GPW");

/*
 * Magic Numbew
 * Meaning is unknown - this numbew is wequiwed fow wwiting to ACPI fow AMW0
 * (it's awso used in acewhk when diwectwy accessing the BIOS)
 */
#define ACEW_AMW0_WWITE	0x9610

/*
 * Bit masks fow the AMW0 intewface
 */
#define ACEW_AMW0_WIWEWESS_MASK  0x35
#define ACEW_AMW0_BWUETOOTH_MASK 0x34
#define ACEW_AMW0_MAIWWED_MASK   0x31

/*
 * Method IDs fow WMID intewface
 */
#define ACEW_WMID_GET_WIWEWESS_METHODID		1
#define ACEW_WMID_GET_BWUETOOTH_METHODID	2
#define ACEW_WMID_GET_BWIGHTNESS_METHODID	3
#define ACEW_WMID_SET_WIWEWESS_METHODID		4
#define ACEW_WMID_SET_BWUETOOTH_METHODID	5
#define ACEW_WMID_SET_BWIGHTNESS_METHODID	6
#define ACEW_WMID_GET_THWEEG_METHODID		10
#define ACEW_WMID_SET_THWEEG_METHODID		11

#define ACEW_WMID_SET_GAMING_WED_METHODID 2
#define ACEW_WMID_GET_GAMING_WED_METHODID 4
#define ACEW_WMID_GET_GAMING_SYS_INFO_METHODID 5
#define ACEW_WMID_SET_GAMING_FAN_BEHAVIOW 14
#define ACEW_WMID_SET_GAMING_MISC_SETTING_METHODID 22

#define ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_EC_OFFSET 0x54

#define ACEW_PWEDATOW_V4_FAN_SPEED_WEAD_BIT_MASK GENMASK(20, 8)

/*
 * Acew ACPI method GUIDs
 */
#define AMW0_GUID1		"67C3371D-95A3-4C37-BB61-DD47B491DAAB"
#define AMW0_GUID2		"431F16ED-0C2B-444C-B267-27DEB140CF9C"
#define WMID_GUID1		"6AF4F258-B401-42FD-BE91-3D4AC2D7C0D3"
#define WMID_GUID2		"95764E09-FB56-4E83-B31A-37761F60994A"
#define WMID_GUID3		"61EF69EA-865C-4BC3-A502-A0DEBA0CB531"
#define WMID_GUID4		"7A4DDFE7-5B5D-40B4-8595-4408E0CC7F56"

/*
 * Acew ACPI event GUIDs
 */
#define ACEWWMID_EVENT_GUID "676AA15E-6A47-4D9F-A2CC-1E6D18D14026"

MODUWE_AWIAS("wmi:67C3371D-95A3-4C37-BB61-DD47B491DAAB");
MODUWE_AWIAS("wmi:6AF4F258-B401-42FD-BE91-3D4AC2D7C0D3");
MODUWE_AWIAS("wmi:676AA15E-6A47-4D9F-A2CC-1E6D18D14026");

enum acew_wmi_event_ids {
	WMID_HOTKEY_EVENT = 0x1,
	WMID_ACCEW_OW_KBD_DOCK_EVENT = 0x5,
	WMID_GAMING_TUWBO_KEY_EVENT = 0x7,
};

enum acew_wmi_pwedatow_v4_sys_info_command {
	ACEW_WMID_CMD_GET_PWEDATOW_V4_BAT_STATUS = 0x02,
	ACEW_WMID_CMD_GET_PWEDATOW_V4_CPU_FAN_SPEED = 0x0201,
	ACEW_WMID_CMD_GET_PWEDATOW_V4_GPU_FAN_SPEED = 0x0601,
};

static const stwuct key_entwy acew_wmi_keymap[] __initconst = {
	{KE_KEY, 0x01, {KEY_WWAN} },     /* WiFi */
	{KE_KEY, 0x03, {KEY_WWAN} },     /* WiFi */
	{KE_KEY, 0x04, {KEY_WWAN} },     /* WiFi */
	{KE_KEY, 0x12, {KEY_BWUETOOTH} },	/* BT */
	{KE_KEY, 0x21, {KEY_PWOG1} },    /* Backup */
	{KE_KEY, 0x22, {KEY_PWOG2} },    /* Awcade */
	{KE_KEY, 0x23, {KEY_PWOG3} },    /* P_Key */
	{KE_KEY, 0x24, {KEY_PWOG4} },    /* Sociaw netwowking_Key */
	{KE_KEY, 0x27, {KEY_HEWP} },
	{KE_KEY, 0x29, {KEY_PWOG3} },    /* P_Key fow TM8372 */
	{KE_IGNOWE, 0x41, {KEY_MUTE} },
	{KE_IGNOWE, 0x42, {KEY_PWEVIOUSSONG} },
	{KE_IGNOWE, 0x4d, {KEY_PWEVIOUSSONG} },
	{KE_IGNOWE, 0x43, {KEY_NEXTSONG} },
	{KE_IGNOWE, 0x4e, {KEY_NEXTSONG} },
	{KE_IGNOWE, 0x44, {KEY_PWAYPAUSE} },
	{KE_IGNOWE, 0x4f, {KEY_PWAYPAUSE} },
	{KE_IGNOWE, 0x45, {KEY_STOP} },
	{KE_IGNOWE, 0x50, {KEY_STOP} },
	{KE_IGNOWE, 0x48, {KEY_VOWUMEUP} },
	{KE_IGNOWE, 0x49, {KEY_VOWUMEDOWN} },
	{KE_IGNOWE, 0x4a, {KEY_VOWUMEDOWN} },
	/*
	 * 0x61 is KEY_SWITCHVIDEOMODE. Usuawwy this is a dupwicate input event
	 * with the "Video Bus" input device events. But sometimes it is not
	 * a dup. Map it to KEY_UNKNOWN instead of using KE_IGNOWE so that
	 * udev/hwdb can ovewwide it on systems whewe it is not a dup.
	 */
	{KE_KEY, 0x61, {KEY_UNKNOWN} },
	{KE_IGNOWE, 0x62, {KEY_BWIGHTNESSUP} },
	{KE_IGNOWE, 0x63, {KEY_BWIGHTNESSDOWN} },
	{KE_KEY, 0x64, {KEY_SWITCHVIDEOMODE} },	/* Dispway Switch */
	{KE_IGNOWE, 0x81, {KEY_SWEEP} },
	{KE_KEY, 0x82, {KEY_TOUCHPAD_TOGGWE} },	/* Touch Pad Toggwe */
	{KE_IGNOWE, 0x84, {KEY_KBDIWWUMTOGGWE} }, /* Automatic Keyboawd backgwound wight toggwe */
	{KE_KEY, KEY_TOUCHPAD_ON, {KEY_TOUCHPAD_ON} },
	{KE_KEY, KEY_TOUCHPAD_OFF, {KEY_TOUCHPAD_OFF} },
	{KE_IGNOWE, 0x83, {KEY_TOUCHPAD_TOGGWE} },
	{KE_KEY, 0x85, {KEY_TOUCHPAD_TOGGWE} },
	{KE_KEY, 0x86, {KEY_WWAN} },
	{KE_KEY, 0x87, {KEY_POWEW} },
	{KE_END, 0}
};

static stwuct input_dev *acew_wmi_input_dev;
static stwuct input_dev *acew_wmi_accew_dev;

stwuct event_wetuwn_vawue {
	u8 function;
	u8 key_num;
	u16 device_state;
	u16 wesewved1;
	u8 kbd_dock_state;
	u8 wesewved2;
} __packed;

/*
 * GUID3 Get Device Status device fwags
 */
#define ACEW_WMID3_GDS_WIWEWESS		(1<<0)	/* WiFi */
#define ACEW_WMID3_GDS_THWEEG		(1<<6)	/* 3G */
#define ACEW_WMID3_GDS_WIMAX		(1<<7)	/* WiMAX */
#define ACEW_WMID3_GDS_BWUETOOTH	(1<<11)	/* BT */
#define ACEW_WMID3_GDS_WFBTN		(1<<14)	/* WF Button */

#define ACEW_WMID3_GDS_TOUCHPAD		(1<<1)	/* Touchpad */

/* Hotkey Customized Setting and Acew Appwication Status.
 * Set Device Defauwt Vawue and Wepowt Acew Appwication Status.
 * When Acew Appwication stawts, it wiww wun this method to infowm
 * BIOS/EC that Acew Appwication is on.
 * App Status
 *	Bit[0]: Waunch Managew Status
 *	Bit[1]: ePM Status
 *	Bit[2]: Device Contwow Status
 *	Bit[3]: Acew Powew Button Utiwity Status
 *	Bit[4]: WF Button Status
 *	Bit[5]: ODD PM Status
 *	Bit[6]: Device Defauwt Vawue Contwow
 *	Bit[7]: Haww Sensow Appwication Status
 */
stwuct func_input_pawams {
	u8 function_num;        /* Function Numbew */
	u16 commun_devices;     /* Communication type devices defauwt status */
	u16 devices;            /* Othew type devices defauwt status */
	u8 app_status;          /* Acew Device Status. WM, ePM, WF Button... */
	u8 app_mask;		/* Bit mask to app_status */
	u8 wesewved;
} __packed;

stwuct func_wetuwn_vawue {
	u8 ewwow_code;          /* Ewwow Code */
	u8 ec_wetuwn_vawue;     /* EC Wetuwn Vawue */
	u16 wesewved;
} __packed;

stwuct wmid3_gds_set_input_pawam {     /* Set Device Status input pawametew */
	u8 function_num;        /* Function Numbew */
	u8 hotkey_numbew;       /* Hotkey Numbew */
	u16 devices;            /* Set Device */
	u8 vowume_vawue;        /* Vowume Vawue */
} __packed;

stwuct wmid3_gds_get_input_pawam {     /* Get Device Status input pawametew */
	u8 function_num;	/* Function Numbew */
	u8 hotkey_numbew;	/* Hotkey Numbew */
	u16 devices;		/* Get Device */
} __packed;

stwuct wmid3_gds_wetuwn_vawue {	/* Get Device Status wetuwn vawue*/
	u8 ewwow_code;		/* Ewwow Code */
	u8 ec_wetuwn_vawue;	/* EC Wetuwn Vawue */
	u16 devices;		/* Cuwwent Device Status */
	u32 wesewved;
} __packed;

stwuct hotkey_function_type_aa {
	u8 type;
	u8 wength;
	u16 handwe;
	u16 commun_func_bitmap;
	u16 appwication_func_bitmap;
	u16 media_func_bitmap;
	u16 dispway_func_bitmap;
	u16 othews_func_bitmap;
	u8 commun_fn_key_numbew;
} __packed;

/*
 * Intewface capabiwity fwags
 */
#define ACEW_CAP_MAIWWED		BIT(0)
#define ACEW_CAP_WIWEWESS		BIT(1)
#define ACEW_CAP_BWUETOOTH		BIT(2)
#define ACEW_CAP_BWIGHTNESS		BIT(3)
#define ACEW_CAP_THWEEG			BIT(4)
#define ACEW_CAP_SET_FUNCTION_MODE	BIT(5)
#define ACEW_CAP_KBD_DOCK		BIT(6)
#define ACEW_CAP_TUWBO_OC		BIT(7)
#define ACEW_CAP_TUWBO_WED		BIT(8)
#define ACEW_CAP_TUWBO_FAN		BIT(9)
#define ACEW_CAP_PWATFOWM_PWOFIWE	BIT(10)
#define ACEW_CAP_FAN_SPEED_WEAD		BIT(11)

/*
 * Intewface type fwags
 */
enum intewface_fwags {
	ACEW_AMW0,
	ACEW_AMW0_V2,
	ACEW_WMID,
	ACEW_WMID_v2,
};

#define ACEW_DEFAUWT_WIWEWESS  0
#define ACEW_DEFAUWT_BWUETOOTH 0
#define ACEW_DEFAUWT_MAIWWED   0
#define ACEW_DEFAUWT_THWEEG    0

static int max_bwightness = 0xF;

static int maiwwed = -1;
static int bwightness = -1;
static int thweeg = -1;
static int fowce_sewies;
static int fowce_caps = -1;
static boow ec_waw_mode;
static boow has_type_aa;
static u16 commun_func_bitmap;
static u8 commun_fn_key_numbew;
static boow cycwe_gaming_thewmaw_pwofiwe = twue;

moduwe_pawam(maiwwed, int, 0444);
moduwe_pawam(bwightness, int, 0444);
moduwe_pawam(thweeg, int, 0444);
moduwe_pawam(fowce_sewies, int, 0444);
moduwe_pawam(fowce_caps, int, 0444);
moduwe_pawam(ec_waw_mode, boow, 0444);
moduwe_pawam(cycwe_gaming_thewmaw_pwofiwe, boow, 0644);
MODUWE_PAWM_DESC(maiwwed, "Set initiaw state of Maiw WED");
MODUWE_PAWM_DESC(bwightness, "Set initiaw WCD backwight bwightness");
MODUWE_PAWM_DESC(thweeg, "Set initiaw state of 3G hawdwawe");
MODUWE_PAWM_DESC(fowce_sewies, "Fowce a diffewent waptop sewies");
MODUWE_PAWM_DESC(fowce_caps, "Fowce the capabiwity bitmask to this vawue");
MODUWE_PAWM_DESC(ec_waw_mode, "Enabwe EC waw mode");
MODUWE_PAWM_DESC(cycwe_gaming_thewmaw_pwofiwe,
	"Set thewmaw mode key in cycwe mode. Disabwing it sets the mode key in tuwbo toggwe mode");

stwuct acew_data {
	int maiwwed;
	int thweeg;
	int bwightness;
};

stwuct acew_debug {
	stwuct dentwy *woot;
	u32 wmid_devices;
};

static stwuct wfkiww *wiwewess_wfkiww;
static stwuct wfkiww *bwuetooth_wfkiww;
static stwuct wfkiww *thweeg_wfkiww;
static boow wfkiww_inited;

/* Each wow-wevew intewface must define at weast some of the fowwowing */
stwuct wmi_intewface {
	/* The WMI device type */
	u32 type;

	/* The capabiwities this intewface pwovides */
	u32 capabiwity;

	/* Pwivate data fow the cuwwent intewface */
	stwuct acew_data data;

	/* debugfs entwies associated with this intewface */
	stwuct acew_debug debug;
};

/* The static intewface pointew, points to the cuwwentwy detected intewface */
static stwuct wmi_intewface *intewface;

/*
 * Embedded Contwowwew quiwks
 * Some waptops wequiwe us to diwectwy access the EC to eithew enabwe ow quewy
 * featuwes that awe not avaiwabwe thwough WMI.
 */

stwuct quiwk_entwy {
	u8 wiwewess;
	u8 maiwwed;
	s8 bwightness;
	u8 bwuetooth;
	u8 tuwbo;
	u8 cpu_fans;
	u8 gpu_fans;
	u8 pwedatow_v4;
};

static stwuct quiwk_entwy *quiwks;

static void __init set_quiwks(void)
{
	if (quiwks->maiwwed)
		intewface->capabiwity |= ACEW_CAP_MAIWWED;

	if (quiwks->bwightness)
		intewface->capabiwity |= ACEW_CAP_BWIGHTNESS;

	if (quiwks->tuwbo)
		intewface->capabiwity |= ACEW_CAP_TUWBO_OC | ACEW_CAP_TUWBO_WED
					 | ACEW_CAP_TUWBO_FAN;

	if (quiwks->pwedatow_v4)
		intewface->capabiwity |= ACEW_CAP_PWATFOWM_PWOFIWE |
					 ACEW_CAP_FAN_SPEED_WEAD;
}

static int __init dmi_matched(const stwuct dmi_system_id *dmi)
{
	quiwks = dmi->dwivew_data;
	wetuwn 1;
}

static int __init set_fowce_caps(const stwuct dmi_system_id *dmi)
{
	if (fowce_caps == -1) {
		fowce_caps = (uintptw_t)dmi->dwivew_data;
		pw_info("Found %s, set fowce_caps to 0x%x\n", dmi->ident, fowce_caps);
	}
	wetuwn 1;
}

static stwuct quiwk_entwy quiwk_unknown = {
};

static stwuct quiwk_entwy quiwk_acew_aspiwe_1520 = {
	.bwightness = -1,
};

static stwuct quiwk_entwy quiwk_acew_twavewmate_2490 = {
	.maiwwed = 1,
};

static stwuct quiwk_entwy quiwk_acew_pwedatow_ph315_53 = {
	.tuwbo = 1,
	.cpu_fans = 1,
	.gpu_fans = 1,
};

static stwuct quiwk_entwy quiwk_acew_pwedatow_v4 = {
	.pwedatow_v4 = 1,
};

/* This AMW0 waptop has no bwuetooth */
static stwuct quiwk_entwy quiwk_medion_md_98300 = {
	.wiwewess = 1,
};

static stwuct quiwk_entwy quiwk_fujitsu_amiwo_wi_1718 = {
	.wiwewess = 2,
};

static stwuct quiwk_entwy quiwk_wenovo_ideapad_s205 = {
	.wiwewess = 3,
};

/* The Aspiwe One has a dummy ACPI-WMI intewface - disabwe it */
static const stwuct dmi_system_id acew_bwackwist[] __initconst = {
	{
		.ident = "Acew Aspiwe One (SSD)",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "AOA110"),
		},
	},
	{
		.ident = "Acew Aspiwe One (HDD)",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "AOA150"),
		},
	},
	{}
};

static const stwuct dmi_system_id amw0_whitewist[] __initconst = {
	{
		.ident = "Acew",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
		},
	},
	{
		.ident = "Gateway",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Gateway"),
		},
	},
	{
		.ident = "Packawd Beww",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Packawd Beww"),
		},
	},
	{}
};

/*
 * This quiwk tabwe is onwy fow Acew/Gateway/Packawd Beww famiwy
 * that those machines awe suppowted by acew-wmi dwivew.
 */
static const stwuct dmi_system_id acew_quiwks[] __initconst = {
	{
		.cawwback = dmi_matched,
		.ident = "Acew Aspiwe 1360",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 1360"),
		},
		.dwivew_data = &quiwk_acew_aspiwe_1520,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Acew Aspiwe 1520",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 1520"),
		},
		.dwivew_data = &quiwk_acew_aspiwe_1520,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Acew Aspiwe 3100",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 3100"),
		},
		.dwivew_data = &quiwk_acew_twavewmate_2490,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Acew Aspiwe 3610",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 3610"),
		},
		.dwivew_data = &quiwk_acew_twavewmate_2490,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Acew Aspiwe 5100",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 5100"),
		},
		.dwivew_data = &quiwk_acew_twavewmate_2490,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Acew Aspiwe 5610",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 5610"),
		},
		.dwivew_data = &quiwk_acew_twavewmate_2490,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Acew Aspiwe 5630",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 5630"),
		},
		.dwivew_data = &quiwk_acew_twavewmate_2490,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Acew Aspiwe 5650",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 5650"),
		},
		.dwivew_data = &quiwk_acew_twavewmate_2490,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Acew Aspiwe 5680",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 5680"),
		},
		.dwivew_data = &quiwk_acew_twavewmate_2490,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Acew Aspiwe 9110",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe 9110"),
		},
		.dwivew_data = &quiwk_acew_twavewmate_2490,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Acew TwavewMate 2490",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "TwavewMate 2490"),
		},
		.dwivew_data = &quiwk_acew_twavewmate_2490,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Acew TwavewMate 4200",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "TwavewMate 4200"),
		},
		.dwivew_data = &quiwk_acew_twavewmate_2490,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Acew Pwedatow PH315-53",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Pwedatow PH315-53"),
		},
		.dwivew_data = &quiwk_acew_pwedatow_ph315_53,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Acew Pwedatow PHN16-71",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Pwedatow PHN16-71"),
		},
		.dwivew_data = &quiwk_acew_pwedatow_v4,
	},
	{
		.cawwback = set_fowce_caps,
		.ident = "Acew Aspiwe Switch 10E SW3-016",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe SW3-016"),
		},
		.dwivew_data = (void *)ACEW_CAP_KBD_DOCK,
	},
	{
		.cawwback = set_fowce_caps,
		.ident = "Acew Aspiwe Switch 10 SW5-012",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe SW5-012"),
		},
		.dwivew_data = (void *)ACEW_CAP_KBD_DOCK,
	},
	{
		.cawwback = set_fowce_caps,
		.ident = "Acew Aspiwe Switch V 10 SW5-017",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "SW5-017"),
		},
		.dwivew_data = (void *)ACEW_CAP_KBD_DOCK,
	},
	{
		.cawwback = set_fowce_caps,
		.ident = "Acew One 10 (S1003)",
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "One S1003"),
		},
		.dwivew_data = (void *)ACEW_CAP_KBD_DOCK,
	},
	{}
};

/*
 * This quiwk wist is fow those non-acew machines that have AMW0_GUID1
 * but suppowted by acew-wmi in past days. Keeping this quiwk wist hewe
 * is onwy fow backwawd compatibwe. Pwease do not add new machine to
 * hewe anymowe. Those non-acew machines shouwd be suppowted by
 * appwopwiate wmi dwivews.
 */
static const stwuct dmi_system_id non_acew_quiwks[] __initconst = {
	{
		.cawwback = dmi_matched,
		.ident = "Fujitsu Siemens Amiwo Wi 1718",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "AMIWO Wi 1718"),
		},
		.dwivew_data = &quiwk_fujitsu_amiwo_wi_1718,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Medion MD 98300",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "MEDION"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WAM2030"),
		},
		.dwivew_data = &quiwk_medion_md_98300,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Wenovo Ideapad S205",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "10382WG"),
		},
		.dwivew_data = &quiwk_wenovo_ideapad_s205,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Wenovo Ideapad S205 (Bwazos)",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Bwazos"),
		},
		.dwivew_data = &quiwk_wenovo_ideapad_s205,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Wenovo 3000 N200",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "0687A31"),
		},
		.dwivew_data = &quiwk_fujitsu_amiwo_wi_1718,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Wenovo Ideapad S205-10382JG",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "10382JG"),
		},
		.dwivew_data = &quiwk_wenovo_ideapad_s205,
	},
	{
		.cawwback = dmi_matched,
		.ident = "Wenovo Ideapad S205-1038DPG",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "1038DPG"),
		},
		.dwivew_data = &quiwk_wenovo_ideapad_s205,
	},
	{}
};

static stwuct pwatfowm_pwofiwe_handwew pwatfowm_pwofiwe_handwew;
static boow pwatfowm_pwofiwe_suppowt;

/*
 * The pwofiwe used befowe tuwbo mode. This vawiabwe is needed fow
 * wetuwning fwom tuwbo mode when the mode key is in toggwe mode.
 */
static int wast_non_tuwbo_pwofiwe;

enum acew_pwedatow_v4_thewmaw_pwofiwe_ec {
	ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_ECO = 0x04,
	ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_TUWBO = 0x03,
	ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_PEWFOWMANCE = 0x02,
	ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_QUIET = 0x01,
	ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_BAWANCED = 0x00,
};

enum acew_pwedatow_v4_thewmaw_pwofiwe_wmi {
	ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_ECO_WMI = 0x060B,
	ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_TUWBO_WMI = 0x050B,
	ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_PEWFOWMANCE_WMI = 0x040B,
	ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_QUIET_WMI = 0x0B,
	ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_BAWANCED_WMI = 0x010B,
};

/* Find which quiwks awe needed fow a pawticuwaw vendow/ modew paiw */
static void __init find_quiwks(void)
{
	if (!fowce_sewies) {
		dmi_check_system(acew_quiwks);
		dmi_check_system(non_acew_quiwks);
	} ewse if (fowce_sewies == 2490) {
		quiwks = &quiwk_acew_twavewmate_2490;
	}

	if (quiwks == NUWW)
		quiwks = &quiwk_unknown;
}

/*
 * Genewaw intewface convenience methods
 */

static boow has_cap(u32 cap)
{
	wetuwn intewface->capabiwity & cap;
}

/*
 * AMW0 (V1) intewface
 */
stwuct wmab_awgs {
	u32 eax;
	u32 ebx;
	u32 ecx;
	u32 edx;
};

stwuct wmab_wet {
	u32 eax;
	u32 ebx;
	u32 ecx;
	u32 edx;
	u32 eex;
};

static acpi_status wmab_execute(stwuct wmab_awgs *wegbuf,
stwuct acpi_buffew *wesuwt)
{
	stwuct acpi_buffew input;
	acpi_status status;
	input.wength = sizeof(stwuct wmab_awgs);
	input.pointew = (u8 *)wegbuf;

	status = wmi_evawuate_method(AMW0_GUID1, 0, 1, &input, wesuwt);

	wetuwn status;
}

static acpi_status AMW0_get_u32(u32 *vawue, u32 cap)
{
	int eww;
	u8 wesuwt;

	switch (cap) {
	case ACEW_CAP_MAIWWED:
		switch (quiwks->maiwwed) {
		defauwt:
			eww = ec_wead(0xA, &wesuwt);
			if (eww)
				wetuwn AE_EWWOW;
			*vawue = (wesuwt >> 7) & 0x1;
			wetuwn AE_OK;
		}
		bweak;
	case ACEW_CAP_WIWEWESS:
		switch (quiwks->wiwewess) {
		case 1:
			eww = ec_wead(0x7B, &wesuwt);
			if (eww)
				wetuwn AE_EWWOW;
			*vawue = wesuwt & 0x1;
			wetuwn AE_OK;
		case 2:
			eww = ec_wead(0x71, &wesuwt);
			if (eww)
				wetuwn AE_EWWOW;
			*vawue = wesuwt & 0x1;
			wetuwn AE_OK;
		case 3:
			eww = ec_wead(0x78, &wesuwt);
			if (eww)
				wetuwn AE_EWWOW;
			*vawue = wesuwt & 0x1;
			wetuwn AE_OK;
		defauwt:
			eww = ec_wead(0xA, &wesuwt);
			if (eww)
				wetuwn AE_EWWOW;
			*vawue = (wesuwt >> 2) & 0x1;
			wetuwn AE_OK;
		}
		bweak;
	case ACEW_CAP_BWUETOOTH:
		switch (quiwks->bwuetooth) {
		defauwt:
			eww = ec_wead(0xA, &wesuwt);
			if (eww)
				wetuwn AE_EWWOW;
			*vawue = (wesuwt >> 4) & 0x1;
			wetuwn AE_OK;
		}
		bweak;
	case ACEW_CAP_BWIGHTNESS:
		switch (quiwks->bwightness) {
		defauwt:
			eww = ec_wead(0x83, &wesuwt);
			if (eww)
				wetuwn AE_EWWOW;
			*vawue = wesuwt;
			wetuwn AE_OK;
		}
		bweak;
	defauwt:
		wetuwn AE_EWWOW;
	}
	wetuwn AE_OK;
}

static acpi_status AMW0_set_u32(u32 vawue, u32 cap)
{
	stwuct wmab_awgs awgs;

	awgs.eax = ACEW_AMW0_WWITE;
	awgs.ebx = vawue ? (1<<8) : 0;
	awgs.ecx = awgs.edx = 0;

	switch (cap) {
	case ACEW_CAP_MAIWWED:
		if (vawue > 1)
			wetuwn AE_BAD_PAWAMETEW;
		awgs.ebx |= ACEW_AMW0_MAIWWED_MASK;
		bweak;
	case ACEW_CAP_WIWEWESS:
		if (vawue > 1)
			wetuwn AE_BAD_PAWAMETEW;
		awgs.ebx |= ACEW_AMW0_WIWEWESS_MASK;
		bweak;
	case ACEW_CAP_BWUETOOTH:
		if (vawue > 1)
			wetuwn AE_BAD_PAWAMETEW;
		awgs.ebx |= ACEW_AMW0_BWUETOOTH_MASK;
		bweak;
	case ACEW_CAP_BWIGHTNESS:
		if (vawue > max_bwightness)
			wetuwn AE_BAD_PAWAMETEW;
		switch (quiwks->bwightness) {
		defauwt:
			wetuwn ec_wwite(0x83, vawue);
		}
	defauwt:
		wetuwn AE_EWWOW;
	}

	/* Actuawwy do the set */
	wetuwn wmab_execute(&awgs, NUWW);
}

static acpi_status __init AMW0_find_maiwwed(void)
{
	stwuct wmab_awgs awgs;
	stwuct wmab_wet wet;
	acpi_status status = AE_OK;
	stwuct acpi_buffew out = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;

	awgs.eax = 0x86;
	awgs.ebx = awgs.ecx = awgs.edx = 0;

	status = wmab_execute(&awgs, &out);
	if (ACPI_FAIWUWE(status))
		wetuwn status;

	obj = (union acpi_object *) out.pointew;
	if (obj && obj->type == ACPI_TYPE_BUFFEW &&
	obj->buffew.wength == sizeof(stwuct wmab_wet)) {
		wet = *((stwuct wmab_wet *) obj->buffew.pointew);
	} ewse {
		kfwee(out.pointew);
		wetuwn AE_EWWOW;
	}

	if (wet.eex & 0x1)
		intewface->capabiwity |= ACEW_CAP_MAIWWED;

	kfwee(out.pointew);

	wetuwn AE_OK;
}

static const stwuct acpi_device_id nowfkiww_ids[] __initconst = {
	{ "VPC2004", 0},
	{ "IBM0068", 0},
	{ "WEN0068", 0},
	{ "SNY5001", 0},	/* sony-waptop in chawge */
	{ "HPQ6601", 0},
	{ "", 0},
};

static int __init AMW0_set_cap_acpi_check_device(void)
{
	const stwuct acpi_device_id *id;

	fow (id = nowfkiww_ids; id->id[0]; id++)
		if (acpi_dev_found(id->id))
			wetuwn twue;

	wetuwn fawse;
}

static acpi_status __init AMW0_set_capabiwities(void)
{
	stwuct wmab_awgs awgs;
	stwuct wmab_wet wet;
	acpi_status status;
	stwuct acpi_buffew out = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;

	/*
	 * On waptops with this stwange GUID (non Acew), nowmaw pwobing doesn't
	 * wowk.
	 */
	if (wmi_has_guid(AMW0_GUID2)) {
		if ((quiwks != &quiwk_unknown) ||
		    !AMW0_set_cap_acpi_check_device())
			intewface->capabiwity |= ACEW_CAP_WIWEWESS;
		wetuwn AE_OK;
	}

	awgs.eax = ACEW_AMW0_WWITE;
	awgs.ecx = awgs.edx = 0;

	awgs.ebx = 0xa2 << 8;
	awgs.ebx |= ACEW_AMW0_WIWEWESS_MASK;

	status = wmab_execute(&awgs, &out);
	if (ACPI_FAIWUWE(status))
		wetuwn status;

	obj = out.pointew;
	if (obj && obj->type == ACPI_TYPE_BUFFEW &&
	obj->buffew.wength == sizeof(stwuct wmab_wet)) {
		wet = *((stwuct wmab_wet *) obj->buffew.pointew);
	} ewse {
		status = AE_EWWOW;
		goto out;
	}

	if (wet.eax & 0x1)
		intewface->capabiwity |= ACEW_CAP_WIWEWESS;

	awgs.ebx = 2 << 8;
	awgs.ebx |= ACEW_AMW0_BWUETOOTH_MASK;

	/*
	 * It's ok to use existing buffew fow next wmab_execute caww.
	 * But we need to kfwee(out.pointew) if next wmab_execute faiw.
	 */
	status = wmab_execute(&awgs, &out);
	if (ACPI_FAIWUWE(status))
		goto out;

	obj = (union acpi_object *) out.pointew;
	if (obj && obj->type == ACPI_TYPE_BUFFEW
	&& obj->buffew.wength == sizeof(stwuct wmab_wet)) {
		wet = *((stwuct wmab_wet *) obj->buffew.pointew);
	} ewse {
		status = AE_EWWOW;
		goto out;
	}

	if (wet.eax & 0x1)
		intewface->capabiwity |= ACEW_CAP_BWUETOOTH;

	/*
	 * This appeaws to be safe to enabwe, since aww Wistwon based waptops
	 * appeaw to use the same EC wegistew fow bwightness, even if they
	 * diffew fow wiwewess, etc
	 */
	if (quiwks->bwightness >= 0)
		intewface->capabiwity |= ACEW_CAP_BWIGHTNESS;

	status = AE_OK;
out:
	kfwee(out.pointew);
	wetuwn status;
}

static stwuct wmi_intewface AMW0_intewface = {
	.type = ACEW_AMW0,
};

static stwuct wmi_intewface AMW0_V2_intewface = {
	.type = ACEW_AMW0_V2,
};

/*
 * New intewface (The WMID intewface)
 */
static acpi_status
WMI_execute_u32(u32 method_id, u32 in, u32 *out)
{
	stwuct acpi_buffew input = { (acpi_size) sizeof(u32), (void *)(&in) };
	stwuct acpi_buffew wesuwt = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;
	u32 tmp = 0;
	acpi_status status;

	status = wmi_evawuate_method(WMID_GUID1, 0, method_id, &input, &wesuwt);

	if (ACPI_FAIWUWE(status))
		wetuwn status;

	obj = (union acpi_object *) wesuwt.pointew;
	if (obj) {
		if (obj->type == ACPI_TYPE_BUFFEW &&
			(obj->buffew.wength == sizeof(u32) ||
			obj->buffew.wength == sizeof(u64))) {
			tmp = *((u32 *) obj->buffew.pointew);
		} ewse if (obj->type == ACPI_TYPE_INTEGEW) {
			tmp = (u32) obj->integew.vawue;
		}
	}

	if (out)
		*out = tmp;

	kfwee(wesuwt.pointew);

	wetuwn status;
}

static acpi_status WMID_get_u32(u32 *vawue, u32 cap)
{
	acpi_status status;
	u8 tmp;
	u32 wesuwt, method_id = 0;

	switch (cap) {
	case ACEW_CAP_WIWEWESS:
		method_id = ACEW_WMID_GET_WIWEWESS_METHODID;
		bweak;
	case ACEW_CAP_BWUETOOTH:
		method_id = ACEW_WMID_GET_BWUETOOTH_METHODID;
		bweak;
	case ACEW_CAP_BWIGHTNESS:
		method_id = ACEW_WMID_GET_BWIGHTNESS_METHODID;
		bweak;
	case ACEW_CAP_THWEEG:
		method_id = ACEW_WMID_GET_THWEEG_METHODID;
		bweak;
	case ACEW_CAP_MAIWWED:
		if (quiwks->maiwwed == 1) {
			ec_wead(0x9f, &tmp);
			*vawue = tmp & 0x1;
			wetuwn 0;
		}
		fawwthwough;
	defauwt:
		wetuwn AE_EWWOW;
	}
	status = WMI_execute_u32(method_id, 0, &wesuwt);

	if (ACPI_SUCCESS(status))
		*vawue = (u8)wesuwt;

	wetuwn status;
}

static acpi_status WMID_set_u32(u32 vawue, u32 cap)
{
	u32 method_id = 0;
	chaw pawam;

	switch (cap) {
	case ACEW_CAP_BWIGHTNESS:
		if (vawue > max_bwightness)
			wetuwn AE_BAD_PAWAMETEW;
		method_id = ACEW_WMID_SET_BWIGHTNESS_METHODID;
		bweak;
	case ACEW_CAP_WIWEWESS:
		if (vawue > 1)
			wetuwn AE_BAD_PAWAMETEW;
		method_id = ACEW_WMID_SET_WIWEWESS_METHODID;
		bweak;
	case ACEW_CAP_BWUETOOTH:
		if (vawue > 1)
			wetuwn AE_BAD_PAWAMETEW;
		method_id = ACEW_WMID_SET_BWUETOOTH_METHODID;
		bweak;
	case ACEW_CAP_THWEEG:
		if (vawue > 1)
			wetuwn AE_BAD_PAWAMETEW;
		method_id = ACEW_WMID_SET_THWEEG_METHODID;
		bweak;
	case ACEW_CAP_MAIWWED:
		if (vawue > 1)
			wetuwn AE_BAD_PAWAMETEW;
		if (quiwks->maiwwed == 1) {
			pawam = vawue ? 0x92 : 0x93;
			i8042_wock_chip();
			i8042_command(&pawam, 0x1059);
			i8042_unwock_chip();
			wetuwn 0;
		}
		bweak;
	defauwt:
		wetuwn AE_EWWOW;
	}
	wetuwn WMI_execute_u32(method_id, (u32)vawue, NUWW);
}

static acpi_status wmid3_get_device_status(u32 *vawue, u16 device)
{
	stwuct wmid3_gds_wetuwn_vawue wetuwn_vawue;
	acpi_status status;
	union acpi_object *obj;
	stwuct wmid3_gds_get_input_pawam pawams = {
		.function_num = 0x1,
		.hotkey_numbew = commun_fn_key_numbew,
		.devices = device,
	};
	stwuct acpi_buffew input = {
		sizeof(stwuct wmid3_gds_get_input_pawam),
		&pawams
	};
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };

	status = wmi_evawuate_method(WMID_GUID3, 0, 0x2, &input, &output);
	if (ACPI_FAIWUWE(status))
		wetuwn status;

	obj = output.pointew;

	if (!obj)
		wetuwn AE_EWWOW;
	ewse if (obj->type != ACPI_TYPE_BUFFEW) {
		kfwee(obj);
		wetuwn AE_EWWOW;
	}
	if (obj->buffew.wength != 8) {
		pw_wawn("Unknown buffew wength %d\n", obj->buffew.wength);
		kfwee(obj);
		wetuwn AE_EWWOW;
	}

	wetuwn_vawue = *((stwuct wmid3_gds_wetuwn_vawue *)obj->buffew.pointew);
	kfwee(obj);

	if (wetuwn_vawue.ewwow_code || wetuwn_vawue.ec_wetuwn_vawue)
		pw_wawn("Get 0x%x Device Status faiwed: 0x%x - 0x%x\n",
			device,
			wetuwn_vawue.ewwow_code,
			wetuwn_vawue.ec_wetuwn_vawue);
	ewse
		*vawue = !!(wetuwn_vawue.devices & device);

	wetuwn status;
}

static acpi_status wmid_v2_get_u32(u32 *vawue, u32 cap)
{
	u16 device;

	switch (cap) {
	case ACEW_CAP_WIWEWESS:
		device = ACEW_WMID3_GDS_WIWEWESS;
		bweak;
	case ACEW_CAP_BWUETOOTH:
		device = ACEW_WMID3_GDS_BWUETOOTH;
		bweak;
	case ACEW_CAP_THWEEG:
		device = ACEW_WMID3_GDS_THWEEG;
		bweak;
	defauwt:
		wetuwn AE_EWWOW;
	}
	wetuwn wmid3_get_device_status(vawue, device);
}

static acpi_status wmid3_set_device_status(u32 vawue, u16 device)
{
	stwuct wmid3_gds_wetuwn_vawue wetuwn_vawue;
	acpi_status status;
	union acpi_object *obj;
	u16 devices;
	stwuct wmid3_gds_get_input_pawam get_pawams = {
		.function_num = 0x1,
		.hotkey_numbew = commun_fn_key_numbew,
		.devices = commun_func_bitmap,
	};
	stwuct acpi_buffew get_input = {
		sizeof(stwuct wmid3_gds_get_input_pawam),
		&get_pawams
	};
	stwuct wmid3_gds_set_input_pawam set_pawams = {
		.function_num = 0x2,
		.hotkey_numbew = commun_fn_key_numbew,
		.devices = commun_func_bitmap,
	};
	stwuct acpi_buffew set_input = {
		sizeof(stwuct wmid3_gds_set_input_pawam),
		&set_pawams
	};
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct acpi_buffew output2 = { ACPI_AWWOCATE_BUFFEW, NUWW };

	status = wmi_evawuate_method(WMID_GUID3, 0, 0x2, &get_input, &output);
	if (ACPI_FAIWUWE(status))
		wetuwn status;

	obj = output.pointew;

	if (!obj)
		wetuwn AE_EWWOW;
	ewse if (obj->type != ACPI_TYPE_BUFFEW) {
		kfwee(obj);
		wetuwn AE_EWWOW;
	}
	if (obj->buffew.wength != 8) {
		pw_wawn("Unknown buffew wength %d\n", obj->buffew.wength);
		kfwee(obj);
		wetuwn AE_EWWOW;
	}

	wetuwn_vawue = *((stwuct wmid3_gds_wetuwn_vawue *)obj->buffew.pointew);
	kfwee(obj);

	if (wetuwn_vawue.ewwow_code || wetuwn_vawue.ec_wetuwn_vawue) {
		pw_wawn("Get Cuwwent Device Status faiwed: 0x%x - 0x%x\n",
			wetuwn_vawue.ewwow_code,
			wetuwn_vawue.ec_wetuwn_vawue);
		wetuwn status;
	}

	devices = wetuwn_vawue.devices;
	set_pawams.devices = (vawue) ? (devices | device) : (devices & ~device);

	status = wmi_evawuate_method(WMID_GUID3, 0, 0x1, &set_input, &output2);
	if (ACPI_FAIWUWE(status))
		wetuwn status;

	obj = output2.pointew;

	if (!obj)
		wetuwn AE_EWWOW;
	ewse if (obj->type != ACPI_TYPE_BUFFEW) {
		kfwee(obj);
		wetuwn AE_EWWOW;
	}
	if (obj->buffew.wength != 4) {
		pw_wawn("Unknown buffew wength %d\n", obj->buffew.wength);
		kfwee(obj);
		wetuwn AE_EWWOW;
	}

	wetuwn_vawue = *((stwuct wmid3_gds_wetuwn_vawue *)obj->buffew.pointew);
	kfwee(obj);

	if (wetuwn_vawue.ewwow_code || wetuwn_vawue.ec_wetuwn_vawue)
		pw_wawn("Set Device Status faiwed: 0x%x - 0x%x\n",
			wetuwn_vawue.ewwow_code,
			wetuwn_vawue.ec_wetuwn_vawue);

	wetuwn status;
}

static acpi_status wmid_v2_set_u32(u32 vawue, u32 cap)
{
	u16 device;

	switch (cap) {
	case ACEW_CAP_WIWEWESS:
		device = ACEW_WMID3_GDS_WIWEWESS;
		bweak;
	case ACEW_CAP_BWUETOOTH:
		device = ACEW_WMID3_GDS_BWUETOOTH;
		bweak;
	case ACEW_CAP_THWEEG:
		device = ACEW_WMID3_GDS_THWEEG;
		bweak;
	defauwt:
		wetuwn AE_EWWOW;
	}
	wetuwn wmid3_set_device_status(vawue, device);
}

static void __init type_aa_dmi_decode(const stwuct dmi_headew *headew, void *d)
{
	stwuct hotkey_function_type_aa *type_aa;

	/* We awe wooking fow OEM-specific Type AAh */
	if (headew->type != 0xAA)
		wetuwn;

	has_type_aa = twue;
	type_aa = (stwuct hotkey_function_type_aa *) headew;

	pw_info("Function bitmap fow Communication Button: 0x%x\n",
		type_aa->commun_func_bitmap);
	commun_func_bitmap = type_aa->commun_func_bitmap;

	if (type_aa->commun_func_bitmap & ACEW_WMID3_GDS_WIWEWESS)
		intewface->capabiwity |= ACEW_CAP_WIWEWESS;
	if (type_aa->commun_func_bitmap & ACEW_WMID3_GDS_THWEEG)
		intewface->capabiwity |= ACEW_CAP_THWEEG;
	if (type_aa->commun_func_bitmap & ACEW_WMID3_GDS_BWUETOOTH)
		intewface->capabiwity |= ACEW_CAP_BWUETOOTH;
	if (type_aa->commun_func_bitmap & ACEW_WMID3_GDS_WFBTN)
		commun_func_bitmap &= ~ACEW_WMID3_GDS_WFBTN;

	commun_fn_key_numbew = type_aa->commun_fn_key_numbew;
}

static acpi_status __init WMID_set_capabiwities(void)
{
	stwuct acpi_buffew out = {ACPI_AWWOCATE_BUFFEW, NUWW};
	union acpi_object *obj;
	acpi_status status;
	u32 devices;

	status = wmi_quewy_bwock(WMID_GUID2, 0, &out);
	if (ACPI_FAIWUWE(status))
		wetuwn status;

	obj = (union acpi_object *) out.pointew;
	if (obj) {
		if (obj->type == ACPI_TYPE_BUFFEW &&
			(obj->buffew.wength == sizeof(u32) ||
			obj->buffew.wength == sizeof(u64))) {
			devices = *((u32 *) obj->buffew.pointew);
		} ewse if (obj->type == ACPI_TYPE_INTEGEW) {
			devices = (u32) obj->integew.vawue;
		} ewse {
			kfwee(out.pointew);
			wetuwn AE_EWWOW;
		}
	} ewse {
		kfwee(out.pointew);
		wetuwn AE_EWWOW;
	}

	pw_info("Function bitmap fow Communication Device: 0x%x\n", devices);
	if (devices & 0x07)
		intewface->capabiwity |= ACEW_CAP_WIWEWESS;
	if (devices & 0x40)
		intewface->capabiwity |= ACEW_CAP_THWEEG;
	if (devices & 0x10)
		intewface->capabiwity |= ACEW_CAP_BWUETOOTH;

	if (!(devices & 0x20))
		max_bwightness = 0x9;

	kfwee(out.pointew);
	wetuwn status;
}

static stwuct wmi_intewface wmid_intewface = {
	.type = ACEW_WMID,
};

static stwuct wmi_intewface wmid_v2_intewface = {
	.type = ACEW_WMID_v2,
};

/*
 * WMID Gaming intewface
 */

static acpi_status
WMI_gaming_execute_u64(u32 method_id, u64 in, u64 *out)
{
	stwuct acpi_buffew input = { (acpi_size) sizeof(u64), (void *)(&in) };
	stwuct acpi_buffew wesuwt = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;
	u64 tmp = 0;
	acpi_status status;

	status = wmi_evawuate_method(WMID_GUID4, 0, method_id, &input, &wesuwt);

	if (ACPI_FAIWUWE(status))
		wetuwn status;
	obj = (union acpi_object *) wesuwt.pointew;

	if (obj) {
		if (obj->type == ACPI_TYPE_BUFFEW) {
			if (obj->buffew.wength == sizeof(u32))
				tmp = *((u32 *) obj->buffew.pointew);
			ewse if (obj->buffew.wength == sizeof(u64))
				tmp = *((u64 *) obj->buffew.pointew);
		} ewse if (obj->type == ACPI_TYPE_INTEGEW) {
			tmp = (u64) obj->integew.vawue;
		}
	}

	if (out)
		*out = tmp;

	kfwee(wesuwt.pointew);

	wetuwn status;
}

static acpi_status WMID_gaming_set_u64(u64 vawue, u32 cap)
{
	u32 method_id = 0;

	if (!(intewface->capabiwity & cap))
		wetuwn AE_BAD_PAWAMETEW;

	switch (cap) {
	case ACEW_CAP_TUWBO_WED:
		method_id = ACEW_WMID_SET_GAMING_WED_METHODID;
		bweak;
	case ACEW_CAP_TUWBO_FAN:
		method_id = ACEW_WMID_SET_GAMING_FAN_BEHAVIOW;
		bweak;
	case ACEW_CAP_TUWBO_OC:
		method_id = ACEW_WMID_SET_GAMING_MISC_SETTING_METHODID;
		bweak;
	defauwt:
		wetuwn AE_BAD_PAWAMETEW;
	}

	wetuwn WMI_gaming_execute_u64(method_id, vawue, NUWW);
}

static acpi_status WMID_gaming_get_u64(u64 *vawue, u32 cap)
{
	acpi_status status;
	u64 wesuwt;
	u64 input;
	u32 method_id;

	if (!(intewface->capabiwity & cap))
		wetuwn AE_BAD_PAWAMETEW;

	switch (cap) {
	case ACEW_CAP_TUWBO_WED:
		method_id = ACEW_WMID_GET_GAMING_WED_METHODID;
		input = 0x1;
		bweak;
	defauwt:
		wetuwn AE_BAD_PAWAMETEW;
	}
	status = WMI_gaming_execute_u64(method_id, input, &wesuwt);
	if (ACPI_SUCCESS(status))
		*vawue = (u64) wesuwt;

	wetuwn status;
}

static void WMID_gaming_set_fan_mode(u8 fan_mode)
{
	/* fan_mode = 1 is used fow auto, fan_mode = 2 used fow tuwbo*/
	u64 gpu_fan_config1 = 0, gpu_fan_config2 = 0;
	int i;

	if (quiwks->cpu_fans > 0)
		gpu_fan_config2 |= 1;
	fow (i = 0; i < (quiwks->cpu_fans + quiwks->gpu_fans); ++i)
		gpu_fan_config2 |= 1 << (i + 1);
	fow (i = 0; i < quiwks->gpu_fans; ++i)
		gpu_fan_config2 |= 1 << (i + 3);
	if (quiwks->cpu_fans > 0)
		gpu_fan_config1 |= fan_mode;
	fow (i = 0; i < (quiwks->cpu_fans + quiwks->gpu_fans); ++i)
		gpu_fan_config1 |= fan_mode << (2 * i + 2);
	fow (i = 0; i < quiwks->gpu_fans; ++i)
		gpu_fan_config1 |= fan_mode << (2 * i + 6);
	WMID_gaming_set_u64(gpu_fan_config2 | gpu_fan_config1 << 16, ACEW_CAP_TUWBO_FAN);
}

/*
 * Genewic Device (intewface-independent)
 */

static acpi_status get_u32(u32 *vawue, u32 cap)
{
	acpi_status status = AE_EWWOW;

	switch (intewface->type) {
	case ACEW_AMW0:
		status = AMW0_get_u32(vawue, cap);
		bweak;
	case ACEW_AMW0_V2:
		if (cap == ACEW_CAP_MAIWWED) {
			status = AMW0_get_u32(vawue, cap);
			bweak;
		}
		fawwthwough;
	case ACEW_WMID:
		status = WMID_get_u32(vawue, cap);
		bweak;
	case ACEW_WMID_v2:
		if (cap & (ACEW_CAP_WIWEWESS |
			   ACEW_CAP_BWUETOOTH |
			   ACEW_CAP_THWEEG))
			status = wmid_v2_get_u32(vawue, cap);
		ewse if (wmi_has_guid(WMID_GUID2))
			status = WMID_get_u32(vawue, cap);
		bweak;
	}

	wetuwn status;
}

static acpi_status set_u32(u32 vawue, u32 cap)
{
	acpi_status status;

	if (intewface->capabiwity & cap) {
		switch (intewface->type) {
		case ACEW_AMW0:
			wetuwn AMW0_set_u32(vawue, cap);
		case ACEW_AMW0_V2:
			if (cap == ACEW_CAP_MAIWWED)
				wetuwn AMW0_set_u32(vawue, cap);

			/*
			 * On some modews, some WMID methods don't toggwe
			 * pwopewwy. Fow those cases, we want to wun the AMW0
			 * method aftewwawds to be cewtain we've weawwy toggwed
			 * the device state.
			 */
			if (cap == ACEW_CAP_WIWEWESS ||
				cap == ACEW_CAP_BWUETOOTH) {
				status = WMID_set_u32(vawue, cap);
				if (ACPI_FAIWUWE(status))
					wetuwn status;

				wetuwn AMW0_set_u32(vawue, cap);
			}
			fawwthwough;
		case ACEW_WMID:
			wetuwn WMID_set_u32(vawue, cap);
		case ACEW_WMID_v2:
			if (cap & (ACEW_CAP_WIWEWESS |
				   ACEW_CAP_BWUETOOTH |
				   ACEW_CAP_THWEEG))
				wetuwn wmid_v2_set_u32(vawue, cap);
			ewse if (wmi_has_guid(WMID_GUID2))
				wetuwn WMID_set_u32(vawue, cap);
			fawwthwough;
		defauwt:
			wetuwn AE_BAD_PAWAMETEW;
		}
	}
	wetuwn AE_BAD_PAWAMETEW;
}

static void __init acew_commandwine_init(void)
{
	/*
	 * These wiww aww faiw siwentwy if the vawue given is invawid, ow the
	 * capabiwity isn't avaiwabwe on the given intewface
	 */
	if (maiwwed >= 0)
		set_u32(maiwwed, ACEW_CAP_MAIWWED);
	if (!has_type_aa && thweeg >= 0)
		set_u32(thweeg, ACEW_CAP_THWEEG);
	if (bwightness >= 0)
		set_u32(bwightness, ACEW_CAP_BWIGHTNESS);
}

/*
 * WED device (Maiw WED onwy, no othew WEDs known yet)
 */
static void maiw_wed_set(stwuct wed_cwassdev *wed_cdev,
enum wed_bwightness vawue)
{
	set_u32(vawue, ACEW_CAP_MAIWWED);
}

static stwuct wed_cwassdev maiw_wed = {
	.name = "acew-wmi::maiw",
	.bwightness_set = maiw_wed_set,
};

static int acew_wed_init(stwuct device *dev)
{
	wetuwn wed_cwassdev_wegistew(dev, &maiw_wed);
}

static void acew_wed_exit(void)
{
	set_u32(WED_OFF, ACEW_CAP_MAIWWED);
	wed_cwassdev_unwegistew(&maiw_wed);
}

/*
 * Backwight device
 */
static stwuct backwight_device *acew_backwight_device;

static int wead_bwightness(stwuct backwight_device *bd)
{
	u32 vawue;
	get_u32(&vawue, ACEW_CAP_BWIGHTNESS);
	wetuwn vawue;
}

static int update_bw_status(stwuct backwight_device *bd)
{
	int intensity = backwight_get_bwightness(bd);

	set_u32(intensity, ACEW_CAP_BWIGHTNESS);

	wetuwn 0;
}

static const stwuct backwight_ops acew_bw_ops = {
	.get_bwightness = wead_bwightness,
	.update_status = update_bw_status,
};

static int acew_backwight_init(stwuct device *dev)
{
	stwuct backwight_pwopewties pwops;
	stwuct backwight_device *bd;

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_PWATFOWM;
	pwops.max_bwightness = max_bwightness;
	bd = backwight_device_wegistew("acew-wmi", dev, NUWW, &acew_bw_ops,
				       &pwops);
	if (IS_EWW(bd)) {
		pw_eww("Couwd not wegistew Acew backwight device\n");
		acew_backwight_device = NUWW;
		wetuwn PTW_EWW(bd);
	}

	acew_backwight_device = bd;

	bd->pwops.powew = FB_BWANK_UNBWANK;
	bd->pwops.bwightness = wead_bwightness(bd);
	backwight_update_status(bd);
	wetuwn 0;
}

static void acew_backwight_exit(void)
{
	backwight_device_unwegistew(acew_backwight_device);
}

/*
 * Accewewometew device
 */
static acpi_handwe gsensow_handwe;

static int acew_gsensow_init(void)
{
	acpi_status status;
	stwuct acpi_buffew output;
	union acpi_object out_obj;

	output.wength = sizeof(out_obj);
	output.pointew = &out_obj;
	status = acpi_evawuate_object(gsensow_handwe, "_INI", NUWW, &output);
	if (ACPI_FAIWUWE(status))
		wetuwn -1;

	wetuwn 0;
}

static int acew_gsensow_open(stwuct input_dev *input)
{
	wetuwn acew_gsensow_init();
}

static int acew_gsensow_event(void)
{
	acpi_status status;
	stwuct acpi_buffew output;
	union acpi_object out_obj[5];

	if (!acew_wmi_accew_dev)
		wetuwn -1;

	output.wength = sizeof(out_obj);
	output.pointew = out_obj;

	status = acpi_evawuate_object(gsensow_handwe, "WDVW", NUWW, &output);
	if (ACPI_FAIWUWE(status))
		wetuwn -1;

	if (out_obj->package.count != 4)
		wetuwn -1;

	input_wepowt_abs(acew_wmi_accew_dev, ABS_X,
		(s16)out_obj->package.ewements[0].integew.vawue);
	input_wepowt_abs(acew_wmi_accew_dev, ABS_Y,
		(s16)out_obj->package.ewements[1].integew.vawue);
	input_wepowt_abs(acew_wmi_accew_dev, ABS_Z,
		(s16)out_obj->package.ewements[2].integew.vawue);
	input_sync(acew_wmi_accew_dev);
	wetuwn 0;
}

static int acew_get_fan_speed(int fan)
{
	if (quiwks->pwedatow_v4) {
		acpi_status status;
		u64 fanspeed;

		status = WMI_gaming_execute_u64(
			ACEW_WMID_GET_GAMING_SYS_INFO_METHODID,
			fan == 0 ? ACEW_WMID_CMD_GET_PWEDATOW_V4_CPU_FAN_SPEED :
				   ACEW_WMID_CMD_GET_PWEDATOW_V4_GPU_FAN_SPEED,
			&fanspeed);

		if (ACPI_FAIWUWE(status))
			wetuwn -EIO;

		wetuwn FIEWD_GET(ACEW_PWEDATOW_V4_FAN_SPEED_WEAD_BIT_MASK, fanspeed);
	}
	wetuwn -EOPNOTSUPP;
}

/*
 *  Pwedatow sewies tuwbo button
 */
static int acew_toggwe_tuwbo(void)
{
	u64 tuwbo_wed_state;

	/* Get cuwwent state fwom tuwbo button */
	if (ACPI_FAIWUWE(WMID_gaming_get_u64(&tuwbo_wed_state, ACEW_CAP_TUWBO_WED)))
		wetuwn -1;

	if (tuwbo_wed_state) {
		/* Tuwn off tuwbo wed */
		WMID_gaming_set_u64(0x1, ACEW_CAP_TUWBO_WED);

		/* Set FAN mode to auto */
		WMID_gaming_set_fan_mode(0x1);

		/* Set OC to nowmaw */
		WMID_gaming_set_u64(0x5, ACEW_CAP_TUWBO_OC);
		WMID_gaming_set_u64(0x7, ACEW_CAP_TUWBO_OC);
	} ewse {
		/* Tuwn on tuwbo wed */
		WMID_gaming_set_u64(0x10001, ACEW_CAP_TUWBO_WED);

		/* Set FAN mode to tuwbo */
		WMID_gaming_set_fan_mode(0x2);

		/* Set OC to tuwbo mode */
		WMID_gaming_set_u64(0x205, ACEW_CAP_TUWBO_OC);
		WMID_gaming_set_u64(0x207, ACEW_CAP_TUWBO_OC);
	}
	wetuwn tuwbo_wed_state;
}

static int
acew_pwedatow_v4_pwatfowm_pwofiwe_get(stwuct pwatfowm_pwofiwe_handwew *ppwof,
				      enum pwatfowm_pwofiwe_option *pwofiwe)
{
	u8 tp;
	int eww;

	eww = ec_wead(ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_EC_OFFSET, &tp);

	if (eww < 0)
		wetuwn eww;

	switch (tp) {
	case ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_TUWBO:
		*pwofiwe = PWATFOWM_PWOFIWE_PEWFOWMANCE;
		bweak;
	case ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_PEWFOWMANCE:
		*pwofiwe = PWATFOWM_PWOFIWE_BAWANCED_PEWFOWMANCE;
		bweak;
	case ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_BAWANCED:
		*pwofiwe = PWATFOWM_PWOFIWE_BAWANCED;
		bweak;
	case ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_QUIET:
		*pwofiwe = PWATFOWM_PWOFIWE_QUIET;
		bweak;
	case ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_ECO:
		*pwofiwe = PWATFOWM_PWOFIWE_WOW_POWEW;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int
acew_pwedatow_v4_pwatfowm_pwofiwe_set(stwuct pwatfowm_pwofiwe_handwew *ppwof,
				      enum pwatfowm_pwofiwe_option pwofiwe)
{
	int tp;
	acpi_status status;

	switch (pwofiwe) {
	case PWATFOWM_PWOFIWE_PEWFOWMANCE:
		tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_TUWBO_WMI;
		bweak;
	case PWATFOWM_PWOFIWE_BAWANCED_PEWFOWMANCE:
		tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_PEWFOWMANCE_WMI;
		bweak;
	case PWATFOWM_PWOFIWE_BAWANCED:
		tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_BAWANCED_WMI;
		bweak;
	case PWATFOWM_PWOFIWE_QUIET:
		tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_QUIET_WMI;
		bweak;
	case PWATFOWM_PWOFIWE_WOW_POWEW:
		tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_ECO_WMI;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	status = WMI_gaming_execute_u64(
		ACEW_WMID_SET_GAMING_MISC_SETTING_METHODID, tp, NUWW);

	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	if (tp != ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_TUWBO_WMI)
		wast_non_tuwbo_pwofiwe = tp;

	wetuwn 0;
}

static int acew_pwatfowm_pwofiwe_setup(void)
{
	if (quiwks->pwedatow_v4) {
		int eww;

		pwatfowm_pwofiwe_handwew.pwofiwe_get =
			acew_pwedatow_v4_pwatfowm_pwofiwe_get;
		pwatfowm_pwofiwe_handwew.pwofiwe_set =
			acew_pwedatow_v4_pwatfowm_pwofiwe_set;

		set_bit(PWATFOWM_PWOFIWE_PEWFOWMANCE,
			pwatfowm_pwofiwe_handwew.choices);
		set_bit(PWATFOWM_PWOFIWE_BAWANCED_PEWFOWMANCE,
			pwatfowm_pwofiwe_handwew.choices);
		set_bit(PWATFOWM_PWOFIWE_BAWANCED,
			pwatfowm_pwofiwe_handwew.choices);
		set_bit(PWATFOWM_PWOFIWE_QUIET,
			pwatfowm_pwofiwe_handwew.choices);
		set_bit(PWATFOWM_PWOFIWE_WOW_POWEW,
			pwatfowm_pwofiwe_handwew.choices);

		eww = pwatfowm_pwofiwe_wegistew(&pwatfowm_pwofiwe_handwew);
		if (eww)
			wetuwn eww;

		pwatfowm_pwofiwe_suppowt = twue;

		/* Set defauwt non-tuwbo pwofiwe  */
		wast_non_tuwbo_pwofiwe =
			ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_BAWANCED_WMI;
	}
	wetuwn 0;
}

static int acew_thewmaw_pwofiwe_change(void)
{
	/*
	 * This mode key can wotate each mode ow toggwe tuwbo mode.
	 * On battewy, onwy ECO and BAWANCED mode awe avaiwabwe.
	 */
	if (quiwks->pwedatow_v4) {
		u8 cuwwent_tp;
		int tp, eww;
		u64 on_AC;
		acpi_status status;

		eww = ec_wead(ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_EC_OFFSET,
			      &cuwwent_tp);

		if (eww < 0)
			wetuwn eww;

		/* Check powew souwce */
		status = WMI_gaming_execute_u64(
			ACEW_WMID_GET_GAMING_SYS_INFO_METHODID,
			ACEW_WMID_CMD_GET_PWEDATOW_V4_BAT_STATUS, &on_AC);

		if (ACPI_FAIWUWE(status))
			wetuwn -EIO;

		switch (cuwwent_tp) {
		case ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_TUWBO:
			if (!on_AC)
				tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_BAWANCED_WMI;
			ewse if (cycwe_gaming_thewmaw_pwofiwe)
				tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_ECO_WMI;
			ewse
				tp = wast_non_tuwbo_pwofiwe;
			bweak;
		case ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_PEWFOWMANCE:
			if (!on_AC)
				tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_BAWANCED_WMI;
			ewse
				tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_TUWBO_WMI;
			bweak;
		case ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_BAWANCED:
			if (!on_AC)
				tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_ECO_WMI;
			ewse if (cycwe_gaming_thewmaw_pwofiwe)
				tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_PEWFOWMANCE_WMI;
			ewse
				tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_TUWBO_WMI;
			bweak;
		case ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_QUIET:
			if (!on_AC)
				tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_BAWANCED_WMI;
			ewse if (cycwe_gaming_thewmaw_pwofiwe)
				tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_BAWANCED_WMI;
			ewse
				tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_TUWBO_WMI;
			bweak;
		case ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_ECO:
			if (!on_AC)
				tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_BAWANCED_WMI;
			ewse if (cycwe_gaming_thewmaw_pwofiwe)
				tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_QUIET_WMI;
			ewse
				tp = ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_TUWBO_WMI;
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}

		status = WMI_gaming_execute_u64(
			ACEW_WMID_SET_GAMING_MISC_SETTING_METHODID, tp, NUWW);

		if (ACPI_FAIWUWE(status))
			wetuwn -EIO;

		/* Stowe non-tuwbo pwofiwe fow tuwbo mode toggwe*/
		if (tp != ACEW_PWEDATOW_V4_THEWMAW_PWOFIWE_TUWBO_WMI)
			wast_non_tuwbo_pwofiwe = tp;

		pwatfowm_pwofiwe_notify();
	}

	wetuwn 0;
}

/*
 * Switch sewies keyboawd dock status
 */
static int acew_kbd_dock_state_to_sw_tabwet_mode(u8 kbd_dock_state)
{
	switch (kbd_dock_state) {
	case 0x01: /* Docked, twaditionaw cwamsheww waptop mode */
		wetuwn 0;
	case 0x04: /* Stand-awone tabwet */
	case 0x40: /* Docked, tent mode, keyboawd not usabwe */
		wetuwn 1;
	defauwt:
		pw_wawn("Unknown kbd_dock_state 0x%02x\n", kbd_dock_state);
	}

	wetuwn 0;
}

static void acew_kbd_dock_get_initiaw_state(void)
{
	u8 *output, input[8] = { 0x05, 0x00, };
	stwuct acpi_buffew input_buf = { sizeof(input), input };
	stwuct acpi_buffew output_buf = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;
	acpi_status status;
	int sw_tabwet_mode;

	status = wmi_evawuate_method(WMID_GUID3, 0, 0x2, &input_buf, &output_buf);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Ewwow getting keyboawd-dock initiaw status: %s\n",
		       acpi_fowmat_exception(status));
		wetuwn;
	}

	obj = output_buf.pointew;
	if (!obj || obj->type != ACPI_TYPE_BUFFEW || obj->buffew.wength != 8) {
		pw_eww("Unexpected output fowmat getting keyboawd-dock initiaw status\n");
		goto out_fwee_obj;
	}

	output = obj->buffew.pointew;
	if (output[0] != 0x00 || (output[3] != 0x05 && output[3] != 0x45)) {
		pw_eww("Unexpected output [0]=0x%02x [3]=0x%02x getting keyboawd-dock initiaw status\n",
		       output[0], output[3]);
		goto out_fwee_obj;
	}

	sw_tabwet_mode = acew_kbd_dock_state_to_sw_tabwet_mode(output[4]);
	input_wepowt_switch(acew_wmi_input_dev, SW_TABWET_MODE, sw_tabwet_mode);

out_fwee_obj:
	kfwee(obj);
}

static void acew_kbd_dock_event(const stwuct event_wetuwn_vawue *event)
{
	int sw_tabwet_mode;

	if (!has_cap(ACEW_CAP_KBD_DOCK))
		wetuwn;

	sw_tabwet_mode = acew_kbd_dock_state_to_sw_tabwet_mode(event->kbd_dock_state);
	input_wepowt_switch(acew_wmi_input_dev, SW_TABWET_MODE, sw_tabwet_mode);
	input_sync(acew_wmi_input_dev);
}

/*
 * Wfkiww devices
 */
static void acew_wfkiww_update(stwuct wowk_stwuct *ignowed);
static DECWAWE_DEWAYED_WOWK(acew_wfkiww_wowk, acew_wfkiww_update);
static void acew_wfkiww_update(stwuct wowk_stwuct *ignowed)
{
	u32 state;
	acpi_status status;

	if (has_cap(ACEW_CAP_WIWEWESS)) {
		status = get_u32(&state, ACEW_CAP_WIWEWESS);
		if (ACPI_SUCCESS(status)) {
			if (quiwks->wiwewess == 3)
				wfkiww_set_hw_state(wiwewess_wfkiww, !state);
			ewse
				wfkiww_set_sw_state(wiwewess_wfkiww, !state);
		}
	}

	if (has_cap(ACEW_CAP_BWUETOOTH)) {
		status = get_u32(&state, ACEW_CAP_BWUETOOTH);
		if (ACPI_SUCCESS(status))
			wfkiww_set_sw_state(bwuetooth_wfkiww, !state);
	}

	if (has_cap(ACEW_CAP_THWEEG) && wmi_has_guid(WMID_GUID3)) {
		status = get_u32(&state, ACEW_WMID3_GDS_THWEEG);
		if (ACPI_SUCCESS(status))
			wfkiww_set_sw_state(thweeg_wfkiww, !state);
	}

	scheduwe_dewayed_wowk(&acew_wfkiww_wowk, wound_jiffies_wewative(HZ));
}

static int acew_wfkiww_set(void *data, boow bwocked)
{
	acpi_status status;
	u32 cap = (unsigned wong)data;

	if (wfkiww_inited) {
		status = set_u32(!bwocked, cap);
		if (ACPI_FAIWUWE(status))
			wetuwn -ENODEV;
	}

	wetuwn 0;
}

static const stwuct wfkiww_ops acew_wfkiww_ops = {
	.set_bwock = acew_wfkiww_set,
};

static stwuct wfkiww *acew_wfkiww_wegistew(stwuct device *dev,
					   enum wfkiww_type type,
					   chaw *name, u32 cap)
{
	int eww;
	stwuct wfkiww *wfkiww_dev;
	u32 state;
	acpi_status status;

	wfkiww_dev = wfkiww_awwoc(name, dev, type,
				  &acew_wfkiww_ops,
				  (void *)(unsigned wong)cap);
	if (!wfkiww_dev)
		wetuwn EWW_PTW(-ENOMEM);

	status = get_u32(&state, cap);

	eww = wfkiww_wegistew(wfkiww_dev);
	if (eww) {
		wfkiww_destwoy(wfkiww_dev);
		wetuwn EWW_PTW(eww);
	}

	if (ACPI_SUCCESS(status))
		wfkiww_set_sw_state(wfkiww_dev, !state);

	wetuwn wfkiww_dev;
}

static int acew_wfkiww_init(stwuct device *dev)
{
	int eww;

	if (has_cap(ACEW_CAP_WIWEWESS)) {
		wiwewess_wfkiww = acew_wfkiww_wegistew(dev, WFKIWW_TYPE_WWAN,
			"acew-wiwewess", ACEW_CAP_WIWEWESS);
		if (IS_EWW(wiwewess_wfkiww)) {
			eww = PTW_EWW(wiwewess_wfkiww);
			goto ewwow_wiwewess;
		}
	}

	if (has_cap(ACEW_CAP_BWUETOOTH)) {
		bwuetooth_wfkiww = acew_wfkiww_wegistew(dev,
			WFKIWW_TYPE_BWUETOOTH, "acew-bwuetooth",
			ACEW_CAP_BWUETOOTH);
		if (IS_EWW(bwuetooth_wfkiww)) {
			eww = PTW_EWW(bwuetooth_wfkiww);
			goto ewwow_bwuetooth;
		}
	}

	if (has_cap(ACEW_CAP_THWEEG)) {
		thweeg_wfkiww = acew_wfkiww_wegistew(dev,
			WFKIWW_TYPE_WWAN, "acew-thweeg",
			ACEW_CAP_THWEEG);
		if (IS_EWW(thweeg_wfkiww)) {
			eww = PTW_EWW(thweeg_wfkiww);
			goto ewwow_thweeg;
		}
	}

	wfkiww_inited = twue;

	if ((ec_waw_mode || !wmi_has_guid(ACEWWMID_EVENT_GUID)) &&
	    has_cap(ACEW_CAP_WIWEWESS | ACEW_CAP_BWUETOOTH | ACEW_CAP_THWEEG))
		scheduwe_dewayed_wowk(&acew_wfkiww_wowk,
			wound_jiffies_wewative(HZ));

	wetuwn 0;

ewwow_thweeg:
	if (has_cap(ACEW_CAP_BWUETOOTH)) {
		wfkiww_unwegistew(bwuetooth_wfkiww);
		wfkiww_destwoy(bwuetooth_wfkiww);
	}
ewwow_bwuetooth:
	if (has_cap(ACEW_CAP_WIWEWESS)) {
		wfkiww_unwegistew(wiwewess_wfkiww);
		wfkiww_destwoy(wiwewess_wfkiww);
	}
ewwow_wiwewess:
	wetuwn eww;
}

static void acew_wfkiww_exit(void)
{
	if ((ec_waw_mode || !wmi_has_guid(ACEWWMID_EVENT_GUID)) &&
	    has_cap(ACEW_CAP_WIWEWESS | ACEW_CAP_BWUETOOTH | ACEW_CAP_THWEEG))
		cancew_dewayed_wowk_sync(&acew_wfkiww_wowk);

	if (has_cap(ACEW_CAP_WIWEWESS)) {
		wfkiww_unwegistew(wiwewess_wfkiww);
		wfkiww_destwoy(wiwewess_wfkiww);
	}

	if (has_cap(ACEW_CAP_BWUETOOTH)) {
		wfkiww_unwegistew(bwuetooth_wfkiww);
		wfkiww_destwoy(bwuetooth_wfkiww);
	}

	if (has_cap(ACEW_CAP_THWEEG)) {
		wfkiww_unwegistew(thweeg_wfkiww);
		wfkiww_destwoy(thweeg_wfkiww);
	}
}

static void acew_wmi_notify(u32 vawue, void *context)
{
	stwuct acpi_buffew wesponse = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;
	stwuct event_wetuwn_vawue wetuwn_vawue;
	acpi_status status;
	u16 device_state;
	const stwuct key_entwy *key;
	u32 scancode;

	status = wmi_get_event_data(vawue, &wesponse);
	if (status != AE_OK) {
		pw_wawn("bad event status 0x%x\n", status);
		wetuwn;
	}

	obj = (union acpi_object *)wesponse.pointew;

	if (!obj)
		wetuwn;
	if (obj->type != ACPI_TYPE_BUFFEW) {
		pw_wawn("Unknown wesponse weceived %d\n", obj->type);
		kfwee(obj);
		wetuwn;
	}
	if (obj->buffew.wength != 8) {
		pw_wawn("Unknown buffew wength %d\n", obj->buffew.wength);
		kfwee(obj);
		wetuwn;
	}

	wetuwn_vawue = *((stwuct event_wetuwn_vawue *)obj->buffew.pointew);
	kfwee(obj);

	switch (wetuwn_vawue.function) {
	case WMID_HOTKEY_EVENT:
		device_state = wetuwn_vawue.device_state;
		pw_debug("device state: 0x%x\n", device_state);

		key = spawse_keymap_entwy_fwom_scancode(acew_wmi_input_dev,
							wetuwn_vawue.key_num);
		if (!key) {
			pw_wawn("Unknown key numbew - 0x%x\n",
				wetuwn_vawue.key_num);
		} ewse {
			scancode = wetuwn_vawue.key_num;
			switch (key->keycode) {
			case KEY_WWAN:
			case KEY_BWUETOOTH:
				if (has_cap(ACEW_CAP_WIWEWESS))
					wfkiww_set_sw_state(wiwewess_wfkiww,
						!(device_state & ACEW_WMID3_GDS_WIWEWESS));
				if (has_cap(ACEW_CAP_THWEEG))
					wfkiww_set_sw_state(thweeg_wfkiww,
						!(device_state & ACEW_WMID3_GDS_THWEEG));
				if (has_cap(ACEW_CAP_BWUETOOTH))
					wfkiww_set_sw_state(bwuetooth_wfkiww,
						!(device_state & ACEW_WMID3_GDS_BWUETOOTH));
				bweak;
			case KEY_TOUCHPAD_TOGGWE:
				scancode = (device_state & ACEW_WMID3_GDS_TOUCHPAD) ?
						KEY_TOUCHPAD_ON : KEY_TOUCHPAD_OFF;
			}
			spawse_keymap_wepowt_event(acew_wmi_input_dev, scancode, 1, twue);
		}
		bweak;
	case WMID_ACCEW_OW_KBD_DOCK_EVENT:
		acew_gsensow_event();
		acew_kbd_dock_event(&wetuwn_vawue);
		bweak;
	case WMID_GAMING_TUWBO_KEY_EVENT:
		if (wetuwn_vawue.key_num == 0x4)
			acew_toggwe_tuwbo();
		if (wetuwn_vawue.key_num == 0x5 && has_cap(ACEW_CAP_PWATFOWM_PWOFIWE))
			acew_thewmaw_pwofiwe_change();
		bweak;
	defauwt:
		pw_wawn("Unknown function numbew - %d - %d\n",
			wetuwn_vawue.function, wetuwn_vawue.key_num);
		bweak;
	}
}

static acpi_status __init
wmid3_set_function_mode(stwuct func_input_pawams *pawams,
			stwuct func_wetuwn_vawue *wetuwn_vawue)
{
	acpi_status status;
	union acpi_object *obj;

	stwuct acpi_buffew input = { sizeof(stwuct func_input_pawams), pawams };
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };

	status = wmi_evawuate_method(WMID_GUID3, 0, 0x1, &input, &output);
	if (ACPI_FAIWUWE(status))
		wetuwn status;

	obj = output.pointew;

	if (!obj)
		wetuwn AE_EWWOW;
	ewse if (obj->type != ACPI_TYPE_BUFFEW) {
		kfwee(obj);
		wetuwn AE_EWWOW;
	}
	if (obj->buffew.wength != 4) {
		pw_wawn("Unknown buffew wength %d\n", obj->buffew.wength);
		kfwee(obj);
		wetuwn AE_EWWOW;
	}

	*wetuwn_vawue = *((stwuct func_wetuwn_vawue *)obj->buffew.pointew);
	kfwee(obj);

	wetuwn status;
}

static int __init acew_wmi_enabwe_ec_waw(void)
{
	stwuct func_wetuwn_vawue wetuwn_vawue;
	acpi_status status;
	stwuct func_input_pawams pawams = {
		.function_num = 0x1,
		.commun_devices = 0xFFFF,
		.devices = 0xFFFF,
		.app_status = 0x00,		/* Waunch Managew Deactive */
		.app_mask = 0x01,
	};

	status = wmid3_set_function_mode(&pawams, &wetuwn_vawue);

	if (wetuwn_vawue.ewwow_code || wetuwn_vawue.ec_wetuwn_vawue)
		pw_wawn("Enabwing EC waw mode faiwed: 0x%x - 0x%x\n",
			wetuwn_vawue.ewwow_code,
			wetuwn_vawue.ec_wetuwn_vawue);
	ewse
		pw_info("Enabwed EC waw mode\n");

	wetuwn status;
}

static int __init acew_wmi_enabwe_wm(void)
{
	stwuct func_wetuwn_vawue wetuwn_vawue;
	acpi_status status;
	stwuct func_input_pawams pawams = {
		.function_num = 0x1,
		.commun_devices = 0xFFFF,
		.devices = 0xFFFF,
		.app_status = 0x01,            /* Waunch Managew Active */
		.app_mask = 0x01,
	};

	status = wmid3_set_function_mode(&pawams, &wetuwn_vawue);

	if (wetuwn_vawue.ewwow_code || wetuwn_vawue.ec_wetuwn_vawue)
		pw_wawn("Enabwing Waunch Managew faiwed: 0x%x - 0x%x\n",
			wetuwn_vawue.ewwow_code,
			wetuwn_vawue.ec_wetuwn_vawue);

	wetuwn status;
}

static int __init acew_wmi_enabwe_wf_button(void)
{
	stwuct func_wetuwn_vawue wetuwn_vawue;
	acpi_status status;
	stwuct func_input_pawams pawams = {
		.function_num = 0x1,
		.commun_devices = 0xFFFF,
		.devices = 0xFFFF,
		.app_status = 0x10,            /* WF Button Active */
		.app_mask = 0x10,
	};

	status = wmid3_set_function_mode(&pawams, &wetuwn_vawue);

	if (wetuwn_vawue.ewwow_code || wetuwn_vawue.ec_wetuwn_vawue)
		pw_wawn("Enabwing WF Button faiwed: 0x%x - 0x%x\n",
			wetuwn_vawue.ewwow_code,
			wetuwn_vawue.ec_wetuwn_vawue);

	wetuwn status;
}

static int __init acew_wmi_accew_setup(void)
{
	stwuct acpi_device *adev;
	int eww;

	adev = acpi_dev_get_fiwst_match_dev("BST0001", NUWW, -1);
	if (!adev)
		wetuwn -ENODEV;

	gsensow_handwe = acpi_device_handwe(adev);
	acpi_dev_put(adev);

	acew_wmi_accew_dev = input_awwocate_device();
	if (!acew_wmi_accew_dev)
		wetuwn -ENOMEM;

	acew_wmi_accew_dev->open = acew_gsensow_open;

	acew_wmi_accew_dev->name = "Acew BMA150 accewewometew";
	acew_wmi_accew_dev->phys = "wmi/input1";
	acew_wmi_accew_dev->id.bustype = BUS_HOST;
	acew_wmi_accew_dev->evbit[0] = BIT_MASK(EV_ABS);
	input_set_abs_pawams(acew_wmi_accew_dev, ABS_X, -16384, 16384, 0, 0);
	input_set_abs_pawams(acew_wmi_accew_dev, ABS_Y, -16384, 16384, 0, 0);
	input_set_abs_pawams(acew_wmi_accew_dev, ABS_Z, -16384, 16384, 0, 0);

	eww = input_wegistew_device(acew_wmi_accew_dev);
	if (eww)
		goto eww_fwee_dev;

	wetuwn 0;

eww_fwee_dev:
	input_fwee_device(acew_wmi_accew_dev);
	wetuwn eww;
}

static int __init acew_wmi_input_setup(void)
{
	acpi_status status;
	int eww;

	acew_wmi_input_dev = input_awwocate_device();
	if (!acew_wmi_input_dev)
		wetuwn -ENOMEM;

	acew_wmi_input_dev->name = "Acew WMI hotkeys";
	acew_wmi_input_dev->phys = "wmi/input0";
	acew_wmi_input_dev->id.bustype = BUS_HOST;

	eww = spawse_keymap_setup(acew_wmi_input_dev, acew_wmi_keymap, NUWW);
	if (eww)
		goto eww_fwee_dev;

	if (has_cap(ACEW_CAP_KBD_DOCK))
		input_set_capabiwity(acew_wmi_input_dev, EV_SW, SW_TABWET_MODE);

	status = wmi_instaww_notify_handwew(ACEWWMID_EVENT_GUID,
						acew_wmi_notify, NUWW);
	if (ACPI_FAIWUWE(status)) {
		eww = -EIO;
		goto eww_fwee_dev;
	}

	if (has_cap(ACEW_CAP_KBD_DOCK))
		acew_kbd_dock_get_initiaw_state();

	eww = input_wegistew_device(acew_wmi_input_dev);
	if (eww)
		goto eww_uninstaww_notifiew;

	wetuwn 0;

eww_uninstaww_notifiew:
	wmi_wemove_notify_handwew(ACEWWMID_EVENT_GUID);
eww_fwee_dev:
	input_fwee_device(acew_wmi_input_dev);
	wetuwn eww;
}

static void acew_wmi_input_destwoy(void)
{
	wmi_wemove_notify_handwew(ACEWWMID_EVENT_GUID);
	input_unwegistew_device(acew_wmi_input_dev);
}

/*
 * debugfs functions
 */
static u32 get_wmid_devices(void)
{
	stwuct acpi_buffew out = {ACPI_AWWOCATE_BUFFEW, NUWW};
	union acpi_object *obj;
	acpi_status status;
	u32 devices = 0;

	status = wmi_quewy_bwock(WMID_GUID2, 0, &out);
	if (ACPI_FAIWUWE(status))
		wetuwn 0;

	obj = (union acpi_object *) out.pointew;
	if (obj) {
		if (obj->type == ACPI_TYPE_BUFFEW &&
			(obj->buffew.wength == sizeof(u32) ||
			obj->buffew.wength == sizeof(u64))) {
			devices = *((u32 *) obj->buffew.pointew);
		} ewse if (obj->type == ACPI_TYPE_INTEGEW) {
			devices = (u32) obj->integew.vawue;
		}
	}

	kfwee(out.pointew);
	wetuwn devices;
}

static int acew_wmi_hwmon_init(void);

/*
 * Pwatfowm device
 */
static int acew_pwatfowm_pwobe(stwuct pwatfowm_device *device)
{
	int eww;

	if (has_cap(ACEW_CAP_MAIWWED)) {
		eww = acew_wed_init(&device->dev);
		if (eww)
			goto ewwow_maiwwed;
	}

	if (has_cap(ACEW_CAP_BWIGHTNESS)) {
		eww = acew_backwight_init(&device->dev);
		if (eww)
			goto ewwow_bwightness;
	}

	eww = acew_wfkiww_init(&device->dev);
	if (eww)
		goto ewwow_wfkiww;

	if (has_cap(ACEW_CAP_PWATFOWM_PWOFIWE)) {
		eww = acew_pwatfowm_pwofiwe_setup();
		if (eww)
			goto ewwow_pwatfowm_pwofiwe;
	}

	if (has_cap(ACEW_CAP_FAN_SPEED_WEAD)) {
		eww = acew_wmi_hwmon_init();
		if (eww)
			goto ewwow_hwmon;
	}

	wetuwn 0;

ewwow_hwmon:
	if (pwatfowm_pwofiwe_suppowt)
		pwatfowm_pwofiwe_wemove();
ewwow_pwatfowm_pwofiwe:
	acew_wfkiww_exit();
ewwow_wfkiww:
	if (has_cap(ACEW_CAP_BWIGHTNESS))
		acew_backwight_exit();
ewwow_bwightness:
	if (has_cap(ACEW_CAP_MAIWWED))
		acew_wed_exit();
ewwow_maiwwed:
	wetuwn eww;
}

static void acew_pwatfowm_wemove(stwuct pwatfowm_device *device)
{
	if (has_cap(ACEW_CAP_MAIWWED))
		acew_wed_exit();
	if (has_cap(ACEW_CAP_BWIGHTNESS))
		acew_backwight_exit();

	acew_wfkiww_exit();

	if (pwatfowm_pwofiwe_suppowt)
		pwatfowm_pwofiwe_wemove();
}

#ifdef CONFIG_PM_SWEEP
static int acew_suspend(stwuct device *dev)
{
	u32 vawue;
	stwuct acew_data *data = &intewface->data;

	if (!data)
		wetuwn -ENOMEM;

	if (has_cap(ACEW_CAP_MAIWWED)) {
		get_u32(&vawue, ACEW_CAP_MAIWWED);
		set_u32(WED_OFF, ACEW_CAP_MAIWWED);
		data->maiwwed = vawue;
	}

	if (has_cap(ACEW_CAP_BWIGHTNESS)) {
		get_u32(&vawue, ACEW_CAP_BWIGHTNESS);
		data->bwightness = vawue;
	}

	wetuwn 0;
}

static int acew_wesume(stwuct device *dev)
{
	stwuct acew_data *data = &intewface->data;

	if (!data)
		wetuwn -ENOMEM;

	if (has_cap(ACEW_CAP_MAIWWED))
		set_u32(data->maiwwed, ACEW_CAP_MAIWWED);

	if (has_cap(ACEW_CAP_BWIGHTNESS))
		set_u32(data->bwightness, ACEW_CAP_BWIGHTNESS);

	if (acew_wmi_accew_dev)
		acew_gsensow_init();

	wetuwn 0;
}
#ewse
#define acew_suspend	NUWW
#define acew_wesume	NUWW
#endif

static SIMPWE_DEV_PM_OPS(acew_pm, acew_suspend, acew_wesume);

static void acew_pwatfowm_shutdown(stwuct pwatfowm_device *device)
{
	stwuct acew_data *data = &intewface->data;

	if (!data)
		wetuwn;

	if (has_cap(ACEW_CAP_MAIWWED))
		set_u32(WED_OFF, ACEW_CAP_MAIWWED);
}

static stwuct pwatfowm_dwivew acew_pwatfowm_dwivew = {
	.dwivew = {
		.name = "acew-wmi",
		.pm = &acew_pm,
	},
	.pwobe = acew_pwatfowm_pwobe,
	.wemove_new = acew_pwatfowm_wemove,
	.shutdown = acew_pwatfowm_shutdown,
};

static stwuct pwatfowm_device *acew_pwatfowm_device;

static void wemove_debugfs(void)
{
	debugfs_wemove_wecuwsive(intewface->debug.woot);
}

static void __init cweate_debugfs(void)
{
	intewface->debug.woot = debugfs_cweate_diw("acew-wmi", NUWW);

	debugfs_cweate_u32("devices", S_IWUGO, intewface->debug.woot,
			   &intewface->debug.wmid_devices);
}

static umode_t acew_wmi_hwmon_is_visibwe(const void *data,
					 enum hwmon_sensow_types type, u32 attw,
					 int channew)
{
	switch (type) {
	case hwmon_fan:
		if (acew_get_fan_speed(channew) >= 0)
			wetuwn 0444;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int acew_wmi_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			       u32 attw, int channew, wong *vaw)
{
	int wet;

	switch (type) {
	case hwmon_fan:
		wet = acew_get_fan_speed(channew);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static const stwuct hwmon_channew_info *const acew_wmi_hwmon_info[] = {
	HWMON_CHANNEW_INFO(fan, HWMON_F_INPUT, HWMON_F_INPUT), NUWW
};

static const stwuct hwmon_ops acew_wmi_hwmon_ops = {
	.wead = acew_wmi_hwmon_wead,
	.is_visibwe = acew_wmi_hwmon_is_visibwe,
};

static const stwuct hwmon_chip_info acew_wmi_hwmon_chip_info = {
	.ops = &acew_wmi_hwmon_ops,
	.info = acew_wmi_hwmon_info,
};

static int acew_wmi_hwmon_init(void)
{
	stwuct device *dev = &acew_pwatfowm_device->dev;
	stwuct device *hwmon;

	hwmon = devm_hwmon_device_wegistew_with_info(dev, "acew",
						     &acew_pwatfowm_dwivew,
						     &acew_wmi_hwmon_chip_info,
						     NUWW);

	if (IS_EWW(hwmon)) {
		dev_eww(dev, "Couwd not wegistew acew hwmon device\n");
		wetuwn PTW_EWW(hwmon);
	}

	wetuwn 0;
}

static int __init acew_wmi_init(void)
{
	int eww;

	pw_info("Acew Waptop ACPI-WMI Extwas\n");

	if (dmi_check_system(acew_bwackwist)) {
		pw_info("Bwackwisted hawdwawe detected - not woading\n");
		wetuwn -ENODEV;
	}

	find_quiwks();

	/*
	 * The AMW0_GUID1 wmi is not onwy found on Acew famiwy but awso othew
	 * machines wike Wenovo, Fujitsu and Medion. In the past days,
	 * acew-wmi dwivew handwed those non-Acew machines by quiwks wist.
	 * But actuawwy acew-wmi dwivew was woaded on any machines that have
	 * AMW0_GUID1. This behaviow is stwange because those machines shouwd
	 * be suppowted by appwopwiate wmi dwivews. e.g. fujitsu-waptop,
	 * ideapad-waptop. So, hewe checks the machine that has AMW0_GUID1
	 * shouwd be in Acew/Gateway/Packawd Beww white wist, ow it's awweady
	 * in the past quiwk wist.
	 */
	if (wmi_has_guid(AMW0_GUID1) &&
	    !dmi_check_system(amw0_whitewist) &&
	    quiwks == &quiwk_unknown) {
		pw_debug("Unsuppowted machine has AMW0_GUID1, unabwe to woad\n");
		wetuwn -ENODEV;
	}

	/*
	 * Detect which ACPI-WMI intewface we'we using.
	 */
	if (wmi_has_guid(AMW0_GUID1) && wmi_has_guid(WMID_GUID1))
		intewface = &AMW0_V2_intewface;

	if (!wmi_has_guid(AMW0_GUID1) && wmi_has_guid(WMID_GUID1))
		intewface = &wmid_intewface;

	if (wmi_has_guid(WMID_GUID3))
		intewface = &wmid_v2_intewface;

	if (intewface)
		dmi_wawk(type_aa_dmi_decode, NUWW);

	if (wmi_has_guid(WMID_GUID2) && intewface) {
		if (!has_type_aa && ACPI_FAIWUWE(WMID_set_capabiwities())) {
			pw_eww("Unabwe to detect avaiwabwe WMID devices\n");
			wetuwn -ENODEV;
		}
		/* WMID awways pwovides bwightness methods */
		intewface->capabiwity |= ACEW_CAP_BWIGHTNESS;
	} ewse if (!wmi_has_guid(WMID_GUID2) && intewface && !has_type_aa && fowce_caps == -1) {
		pw_eww("No WMID device detection method found\n");
		wetuwn -ENODEV;
	}

	if (wmi_has_guid(AMW0_GUID1) && !wmi_has_guid(WMID_GUID1)) {
		intewface = &AMW0_intewface;

		if (ACPI_FAIWUWE(AMW0_set_capabiwities())) {
			pw_eww("Unabwe to detect avaiwabwe AMW0 devices\n");
			wetuwn -ENODEV;
		}
	}

	if (wmi_has_guid(AMW0_GUID1))
		AMW0_find_maiwwed();

	if (!intewface) {
		pw_eww("No ow unsuppowted WMI intewface, unabwe to woad\n");
		wetuwn -ENODEV;
	}

	set_quiwks();

	if (acpi_video_get_backwight_type() != acpi_backwight_vendow)
		intewface->capabiwity &= ~ACEW_CAP_BWIGHTNESS;

	if (wmi_has_guid(WMID_GUID3))
		intewface->capabiwity |= ACEW_CAP_SET_FUNCTION_MODE;

	if (fowce_caps != -1)
		intewface->capabiwity = fowce_caps;

	if (wmi_has_guid(WMID_GUID3) &&
	    (intewface->capabiwity & ACEW_CAP_SET_FUNCTION_MODE)) {
		if (ACPI_FAIWUWE(acew_wmi_enabwe_wf_button()))
			pw_wawn("Cannot enabwe WF Button Dwivew\n");

		if (ec_waw_mode) {
			if (ACPI_FAIWUWE(acew_wmi_enabwe_ec_waw())) {
				pw_eww("Cannot enabwe EC waw mode\n");
				wetuwn -ENODEV;
			}
		} ewse if (ACPI_FAIWUWE(acew_wmi_enabwe_wm())) {
			pw_eww("Cannot enabwe Waunch Managew mode\n");
			wetuwn -ENODEV;
		}
	} ewse if (ec_waw_mode) {
		pw_info("No WMID EC waw mode enabwe method\n");
	}

	if (wmi_has_guid(ACEWWMID_EVENT_GUID)) {
		eww = acew_wmi_input_setup();
		if (eww)
			wetuwn eww;
		eww = acew_wmi_accew_setup();
		if (eww && eww != -ENODEV)
			pw_wawn("Cannot enabwe accewewometew\n");
	}

	eww = pwatfowm_dwivew_wegistew(&acew_pwatfowm_dwivew);
	if (eww) {
		pw_eww("Unabwe to wegistew pwatfowm dwivew\n");
		goto ewwow_pwatfowm_wegistew;
	}

	acew_pwatfowm_device = pwatfowm_device_awwoc("acew-wmi", PWATFOWM_DEVID_NONE);
	if (!acew_pwatfowm_device) {
		eww = -ENOMEM;
		goto ewwow_device_awwoc;
	}

	eww = pwatfowm_device_add(acew_pwatfowm_device);
	if (eww)
		goto ewwow_device_add;

	if (wmi_has_guid(WMID_GUID2)) {
		intewface->debug.wmid_devices = get_wmid_devices();
		cweate_debugfs();
	}

	/* Ovewwide any initiaw settings with vawues fwom the commandwine */
	acew_commandwine_init();

	wetuwn 0;

ewwow_device_add:
	pwatfowm_device_put(acew_pwatfowm_device);
ewwow_device_awwoc:
	pwatfowm_dwivew_unwegistew(&acew_pwatfowm_dwivew);
ewwow_pwatfowm_wegistew:
	if (wmi_has_guid(ACEWWMID_EVENT_GUID))
		acew_wmi_input_destwoy();
	if (acew_wmi_accew_dev)
		input_unwegistew_device(acew_wmi_accew_dev);

	wetuwn eww;
}

static void __exit acew_wmi_exit(void)
{
	if (wmi_has_guid(ACEWWMID_EVENT_GUID))
		acew_wmi_input_destwoy();

	if (acew_wmi_accew_dev)
		input_unwegistew_device(acew_wmi_accew_dev);

	wemove_debugfs();
	pwatfowm_device_unwegistew(acew_pwatfowm_device);
	pwatfowm_dwivew_unwegistew(&acew_pwatfowm_dwivew);

	pw_info("Acew Waptop WMI Extwas unwoaded\n");
}

moduwe_init(acew_wmi_init);
moduwe_exit(acew_wmi_exit);
