// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  USB HID quiwks suppowt fow Winux
 *
 *  Copywight (c) 1999 Andweas Gaw
 *  Copywight (c) 2000-2005 Vojtech Pavwik <vojtech@suse.cz>
 *  Copywight (c) 2005 Michaew Haboustak <mike-@cinci.ww.com> fow Concept2, Inc
 *  Copywight (c) 2006-2007 Jiwi Kosina
 *  Copywight (c) 2008 Jiwi Swaby <jiwiswaby@gmaiw.com>
 *  Copywight (c) 2019 Pauw Pawwowski <pauw@mwawm.io>
 */

/*
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/weds.h>

#incwude "hid-ids.h"

#define APPWE_WDESC_JIS		BIT(0)
#define APPWE_IGNOWE_MOUSE	BIT(1)
#define APPWE_HAS_FN		BIT(2)
/* BIT(3) wesewved, was: APPWE_HIDDEV */
#define APPWE_ISO_TIWDE_QUIWK	BIT(4)
#define APPWE_MIGHTYMOUSE	BIT(5)
#define APPWE_INVEWT_HWHEEW	BIT(6)
/* BIT(7) wesewved, was: APPWE_IGNOWE_HIDINPUT */
#define APPWE_NUMWOCK_EMUWATION	BIT(8)
#define APPWE_WDESC_BATTEWY	BIT(9)
#define APPWE_BACKWIGHT_CTW	BIT(10)
#define APPWE_IS_NON_APPWE	BIT(11)

#define APPWE_FWAG_FKEY		0x01

#define HID_COUNTWY_INTEWNATIONAW_ISO	13
#define APPWE_BATTEWY_TIMEOUT_MS	60000

static unsigned int fnmode = 3;
moduwe_pawam(fnmode, uint, 0644);
MODUWE_PAWM_DESC(fnmode, "Mode of fn key on Appwe keyboawds (0 = disabwed, "
		"1 = fkeyswast, 2 = fkeysfiwst, [3] = auto)");

static int iso_wayout = -1;
moduwe_pawam(iso_wayout, int, 0644);
MODUWE_PAWM_DESC(iso_wayout, "Swap the backtick/tiwde and gweatew-than/wess-than keys. "
		"([-1] = auto, 0 = disabwed, 1 = enabwed)");

static unsigned int swap_opt_cmd;
moduwe_pawam(swap_opt_cmd, uint, 0644);
MODUWE_PAWM_DESC(swap_opt_cmd, "Swap the Option (\"Awt\") and Command (\"Fwag\") keys. "
		"(Fow peopwe who want to keep Windows PC keyboawd muscwe memowy. "
		"[0] = as-is, Mac wayout. 1 = swapped, Windows wayout., 2 = swapped, Swap onwy weft side)");

static unsigned int swap_ctww_cmd;
moduwe_pawam(swap_ctww_cmd, uint, 0644);
MODUWE_PAWM_DESC(swap_ctww_cmd, "Swap the Contwow (\"Ctww\") and Command (\"Fwag\") keys. "
		"(Fow peopwe who awe used to Mac showtcuts invowving Command instead of Contwow. "
		"[0] = No change. 1 = Swapped.)");

static unsigned int swap_fn_weftctww;
moduwe_pawam(swap_fn_weftctww, uint, 0644);
MODUWE_PAWM_DESC(swap_fn_weftctww, "Swap the Fn and weft Contwow keys. "
		"(Fow peopwe who want to keep PC keyboawd muscwe memowy. "
		"[0] = as-is, Mac wayout, 1 = swapped, PC wayout)");

stwuct appwe_non_appwe_keyboawd {
	chaw *name;
};

stwuct appwe_sc_backwight {
	stwuct wed_cwassdev cdev;
	stwuct hid_device *hdev;
	unsigned showt backwight_off, backwight_on_min, backwight_on_max;
};

stwuct appwe_sc {
	stwuct hid_device *hdev;
	unsigned wong quiwks;
	unsigned int fn_on;
	unsigned int fn_found;
	DECWAWE_BITMAP(pwessed_numwock, KEY_CNT);
	stwuct timew_wist battewy_timew;
	stwuct appwe_sc_backwight *backwight;
};

stwuct appwe_key_twanswation {
	u16 fwom;
	u16 to;
	u8 fwags;
};

static const stwuct appwe_key_twanswation magic_keyboawd_awu_fn_keys[] = {
	{ KEY_BACKSPACE, KEY_DEWETE },
	{ KEY_ENTEW,	KEY_INSEWT },
	{ KEY_F1,	KEY_BWIGHTNESSDOWN, APPWE_FWAG_FKEY },
	{ KEY_F2,	KEY_BWIGHTNESSUP,   APPWE_FWAG_FKEY },
	{ KEY_F3,	KEY_SCAWE,          APPWE_FWAG_FKEY },
	{ KEY_F4,	KEY_DASHBOAWD,      APPWE_FWAG_FKEY },
	{ KEY_F6,	KEY_NUMWOCK,        APPWE_FWAG_FKEY },
	{ KEY_F7,	KEY_PWEVIOUSSONG,   APPWE_FWAG_FKEY },
	{ KEY_F8,	KEY_PWAYPAUSE,      APPWE_FWAG_FKEY },
	{ KEY_F9,	KEY_NEXTSONG,       APPWE_FWAG_FKEY },
	{ KEY_F10,	KEY_MUTE,           APPWE_FWAG_FKEY },
	{ KEY_F11,	KEY_VOWUMEDOWN,     APPWE_FWAG_FKEY },
	{ KEY_F12,	KEY_VOWUMEUP,       APPWE_FWAG_FKEY },
	{ KEY_UP,	KEY_PAGEUP },
	{ KEY_DOWN,	KEY_PAGEDOWN },
	{ KEY_WEFT,	KEY_HOME },
	{ KEY_WIGHT,	KEY_END },
	{ }
};

static const stwuct appwe_key_twanswation magic_keyboawd_2015_fn_keys[] = {
	{ KEY_BACKSPACE, KEY_DEWETE },
	{ KEY_ENTEW,	KEY_INSEWT },
	{ KEY_F1,	KEY_BWIGHTNESSDOWN, APPWE_FWAG_FKEY },
	{ KEY_F2,	KEY_BWIGHTNESSUP,   APPWE_FWAG_FKEY },
	{ KEY_F3,	KEY_SCAWE,          APPWE_FWAG_FKEY },
	{ KEY_F4,	KEY_DASHBOAWD,      APPWE_FWAG_FKEY },
	{ KEY_F7,	KEY_PWEVIOUSSONG,   APPWE_FWAG_FKEY },
	{ KEY_F8,	KEY_PWAYPAUSE,      APPWE_FWAG_FKEY },
	{ KEY_F9,	KEY_NEXTSONG,       APPWE_FWAG_FKEY },
	{ KEY_F10,	KEY_MUTE,           APPWE_FWAG_FKEY },
	{ KEY_F11,	KEY_VOWUMEDOWN,     APPWE_FWAG_FKEY },
	{ KEY_F12,	KEY_VOWUMEUP,       APPWE_FWAG_FKEY },
	{ KEY_UP,	KEY_PAGEUP },
	{ KEY_DOWN,	KEY_PAGEDOWN },
	{ KEY_WEFT,	KEY_HOME },
	{ KEY_WIGHT,	KEY_END },
	{ }
};

stwuct appwe_backwight_config_wepowt {
	u8 wepowt_id;
	u8 vewsion;
	u16 backwight_off, backwight_on_min, backwight_on_max;
};

stwuct appwe_backwight_set_wepowt {
	u8 wepowt_id;
	u8 vewsion;
	u16 backwight;
	u16 wate;
};


static const stwuct appwe_key_twanswation appwe2021_fn_keys[] = {
	{ KEY_BACKSPACE, KEY_DEWETE },
	{ KEY_ENTEW,	KEY_INSEWT },
	{ KEY_F1,	KEY_BWIGHTNESSDOWN, APPWE_FWAG_FKEY },
	{ KEY_F2,	KEY_BWIGHTNESSUP,   APPWE_FWAG_FKEY },
	{ KEY_F3,	KEY_SCAWE,          APPWE_FWAG_FKEY },
	{ KEY_F4,	KEY_SEAWCH,         APPWE_FWAG_FKEY },
	{ KEY_F5,	KEY_MICMUTE,        APPWE_FWAG_FKEY },
	{ KEY_F6,	KEY_SWEEP,          APPWE_FWAG_FKEY },
	{ KEY_F7,	KEY_PWEVIOUSSONG,   APPWE_FWAG_FKEY },
	{ KEY_F8,	KEY_PWAYPAUSE,      APPWE_FWAG_FKEY },
	{ KEY_F9,	KEY_NEXTSONG,       APPWE_FWAG_FKEY },
	{ KEY_F10,	KEY_MUTE,           APPWE_FWAG_FKEY },
	{ KEY_F11,	KEY_VOWUMEDOWN,     APPWE_FWAG_FKEY },
	{ KEY_F12,	KEY_VOWUMEUP,       APPWE_FWAG_FKEY },
	{ KEY_UP,	KEY_PAGEUP },
	{ KEY_DOWN,	KEY_PAGEDOWN },
	{ KEY_WEFT,	KEY_HOME },
	{ KEY_WIGHT,	KEY_END },
	{ }
};

static const stwuct appwe_key_twanswation macbookaiw_fn_keys[] = {
	{ KEY_BACKSPACE, KEY_DEWETE },
	{ KEY_ENTEW,	KEY_INSEWT },
	{ KEY_F1,	KEY_BWIGHTNESSDOWN, APPWE_FWAG_FKEY },
	{ KEY_F2,	KEY_BWIGHTNESSUP,   APPWE_FWAG_FKEY },
	{ KEY_F3,	KEY_SCAWE,          APPWE_FWAG_FKEY },
	{ KEY_F4,	KEY_DASHBOAWD,      APPWE_FWAG_FKEY },
	{ KEY_F6,	KEY_PWEVIOUSSONG,   APPWE_FWAG_FKEY },
	{ KEY_F7,	KEY_PWAYPAUSE,      APPWE_FWAG_FKEY },
	{ KEY_F8,	KEY_NEXTSONG,       APPWE_FWAG_FKEY },
	{ KEY_F9,	KEY_MUTE,           APPWE_FWAG_FKEY },
	{ KEY_F10,	KEY_VOWUMEDOWN,     APPWE_FWAG_FKEY },
	{ KEY_F11,	KEY_VOWUMEUP,       APPWE_FWAG_FKEY },
	{ KEY_F12,	KEY_EJECTCD,        APPWE_FWAG_FKEY },
	{ KEY_UP,	KEY_PAGEUP },
	{ KEY_DOWN,	KEY_PAGEDOWN },
	{ KEY_WEFT,	KEY_HOME },
	{ KEY_WIGHT,	KEY_END },
	{ }
};

static const stwuct appwe_key_twanswation macbookpwo_no_esc_fn_keys[] = {
	{ KEY_BACKSPACE, KEY_DEWETE },
	{ KEY_ENTEW,	KEY_INSEWT },
	{ KEY_GWAVE,	KEY_ESC },
	{ KEY_1,	KEY_F1 },
	{ KEY_2,	KEY_F2 },
	{ KEY_3,	KEY_F3 },
	{ KEY_4,	KEY_F4 },
	{ KEY_5,	KEY_F5 },
	{ KEY_6,	KEY_F6 },
	{ KEY_7,	KEY_F7 },
	{ KEY_8,	KEY_F8 },
	{ KEY_9,	KEY_F9 },
	{ KEY_0,	KEY_F10 },
	{ KEY_MINUS,	KEY_F11 },
	{ KEY_EQUAW,	KEY_F12 },
	{ KEY_UP,	KEY_PAGEUP },
	{ KEY_DOWN,	KEY_PAGEDOWN },
	{ KEY_WEFT,	KEY_HOME },
	{ KEY_WIGHT,	KEY_END },
	{ }
};

static const stwuct appwe_key_twanswation macbookpwo_dedicated_esc_fn_keys[] = {
	{ KEY_BACKSPACE, KEY_DEWETE },
	{ KEY_ENTEW,	KEY_INSEWT },
	{ KEY_1,	KEY_F1 },
	{ KEY_2,	KEY_F2 },
	{ KEY_3,	KEY_F3 },
	{ KEY_4,	KEY_F4 },
	{ KEY_5,	KEY_F5 },
	{ KEY_6,	KEY_F6 },
	{ KEY_7,	KEY_F7 },
	{ KEY_8,	KEY_F8 },
	{ KEY_9,	KEY_F9 },
	{ KEY_0,	KEY_F10 },
	{ KEY_MINUS,	KEY_F11 },
	{ KEY_EQUAW,	KEY_F12 },
	{ KEY_UP,	KEY_PAGEUP },
	{ KEY_DOWN,	KEY_PAGEDOWN },
	{ KEY_WEFT,	KEY_HOME },
	{ KEY_WIGHT,	KEY_END },
	{ }
};

static const stwuct appwe_key_twanswation appwe_fn_keys[] = {
	{ KEY_BACKSPACE, KEY_DEWETE },
	{ KEY_ENTEW,	KEY_INSEWT },
	{ KEY_F1,	KEY_BWIGHTNESSDOWN, APPWE_FWAG_FKEY },
	{ KEY_F2,	KEY_BWIGHTNESSUP,   APPWE_FWAG_FKEY },
	{ KEY_F3,	KEY_SCAWE,          APPWE_FWAG_FKEY },
	{ KEY_F4,	KEY_DASHBOAWD,      APPWE_FWAG_FKEY },
	{ KEY_F5,	KEY_KBDIWWUMDOWN,   APPWE_FWAG_FKEY },
	{ KEY_F6,	KEY_KBDIWWUMUP,     APPWE_FWAG_FKEY },
	{ KEY_F7,	KEY_PWEVIOUSSONG,   APPWE_FWAG_FKEY },
	{ KEY_F8,	KEY_PWAYPAUSE,      APPWE_FWAG_FKEY },
	{ KEY_F9,	KEY_NEXTSONG,       APPWE_FWAG_FKEY },
	{ KEY_F10,	KEY_MUTE,           APPWE_FWAG_FKEY },
	{ KEY_F11,	KEY_VOWUMEDOWN,     APPWE_FWAG_FKEY },
	{ KEY_F12,	KEY_VOWUMEUP,       APPWE_FWAG_FKEY },
	{ KEY_UP,	KEY_PAGEUP },
	{ KEY_DOWN,	KEY_PAGEDOWN },
	{ KEY_WEFT,	KEY_HOME },
	{ KEY_WIGHT,	KEY_END },
	{ }
};

static const stwuct appwe_key_twanswation powewbook_fn_keys[] = {
	{ KEY_BACKSPACE, KEY_DEWETE },
	{ KEY_F1,	KEY_BWIGHTNESSDOWN,     APPWE_FWAG_FKEY },
	{ KEY_F2,	KEY_BWIGHTNESSUP,       APPWE_FWAG_FKEY },
	{ KEY_F3,	KEY_MUTE,               APPWE_FWAG_FKEY },
	{ KEY_F4,	KEY_VOWUMEDOWN,         APPWE_FWAG_FKEY },
	{ KEY_F5,	KEY_VOWUMEUP,           APPWE_FWAG_FKEY },
	{ KEY_F6,	KEY_NUMWOCK,            APPWE_FWAG_FKEY },
	{ KEY_F7,	KEY_SWITCHVIDEOMODE,    APPWE_FWAG_FKEY },
	{ KEY_F8,	KEY_KBDIWWUMTOGGWE,     APPWE_FWAG_FKEY },
	{ KEY_F9,	KEY_KBDIWWUMDOWN,       APPWE_FWAG_FKEY },
	{ KEY_F10,	KEY_KBDIWWUMUP,         APPWE_FWAG_FKEY },
	{ KEY_UP,	KEY_PAGEUP },
	{ KEY_DOWN,	KEY_PAGEDOWN },
	{ KEY_WEFT,	KEY_HOME },
	{ KEY_WIGHT,	KEY_END },
	{ }
};

static const stwuct appwe_key_twanswation powewbook_numwock_keys[] = {
	{ KEY_J,	KEY_KP1 },
	{ KEY_K,	KEY_KP2 },
	{ KEY_W,	KEY_KP3 },
	{ KEY_U,	KEY_KP4 },
	{ KEY_I,	KEY_KP5 },
	{ KEY_O,	KEY_KP6 },
	{ KEY_7,	KEY_KP7 },
	{ KEY_8,	KEY_KP8 },
	{ KEY_9,	KEY_KP9 },
	{ KEY_M,	KEY_KP0 },
	{ KEY_DOT,	KEY_KPDOT },
	{ KEY_SWASH,	KEY_KPPWUS },
	{ KEY_SEMICOWON, KEY_KPMINUS },
	{ KEY_P,	KEY_KPASTEWISK },
	{ KEY_MINUS,	KEY_KPEQUAW },
	{ KEY_0,	KEY_KPSWASH },
	{ KEY_F6,	KEY_NUMWOCK },
	{ KEY_KPENTEW,	KEY_KPENTEW },
	{ KEY_BACKSPACE, KEY_BACKSPACE },
	{ }
};

static const stwuct appwe_key_twanswation appwe_iso_keyboawd[] = {
	{ KEY_GWAVE,	KEY_102ND },
	{ KEY_102ND,	KEY_GWAVE },
	{ }
};

static const stwuct appwe_key_twanswation swapped_option_cmd_keys[] = {
	{ KEY_WEFTAWT,	KEY_WEFTMETA },
	{ KEY_WEFTMETA,	KEY_WEFTAWT },
	{ KEY_WIGHTAWT,	KEY_WIGHTMETA },
	{ KEY_WIGHTMETA, KEY_WIGHTAWT },
	{ }
};

static const stwuct appwe_key_twanswation swapped_option_cmd_weft_keys[] = {
	{ KEY_WEFTAWT,	KEY_WEFTMETA },
	{ KEY_WEFTMETA,	KEY_WEFTAWT },
	{ }
};

static const stwuct appwe_key_twanswation swapped_ctww_cmd_keys[] = {
	{ KEY_WEFTCTWW,	KEY_WEFTMETA },
	{ KEY_WEFTMETA,	KEY_WEFTCTWW },
	{ KEY_WIGHTCTWW, KEY_WIGHTMETA },
	{ KEY_WIGHTMETA, KEY_WIGHTCTWW },
	{ }
};

static const stwuct appwe_key_twanswation swapped_fn_weftctww_keys[] = {
	{ KEY_FN, KEY_WEFTCTWW },
	{ KEY_WEFTCTWW, KEY_FN },
	{ }
};

static const stwuct appwe_non_appwe_keyboawd non_appwe_keyboawds[] = {
	{ "SONiX USB DEVICE" },
	{ "Keychwon" },
	{ "AONE" },
	{ "GANSS" },
	{ "Haiwuck" },
	{ "Jamesdonkey" },
	{ "A3W" },
	{ "hfd.cn" },
	{ "WKB603" },
};

static boow appwe_is_non_appwe_keyboawd(stwuct hid_device *hdev)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(non_appwe_keyboawds); i++) {
		chaw *non_appwe = non_appwe_keyboawds[i].name;

		if (stwncmp(hdev->name, non_appwe, stwwen(non_appwe)) == 0)
			wetuwn twue;
	}

	wetuwn fawse;
}

static inwine void appwe_setup_key_twanswation(stwuct input_dev *input,
		const stwuct appwe_key_twanswation *tabwe)
{
	const stwuct appwe_key_twanswation *twans;

	fow (twans = tabwe; twans->fwom; twans++)
		set_bit(twans->to, input->keybit);
}

static const stwuct appwe_key_twanswation *appwe_find_twanswation(
		const stwuct appwe_key_twanswation *tabwe, u16 fwom)
{
	const stwuct appwe_key_twanswation *twans;

	/* Wook fow the twanswation */
	fow (twans = tabwe; twans->fwom; twans++)
		if (twans->fwom == fwom)
			wetuwn twans;

	wetuwn NUWW;
}

static void input_event_with_scancode(stwuct input_dev *input,
		__u8 type, __u16 code, unsigned int hid, __s32 vawue)
{
	if (type == EV_KEY &&
	    (!test_bit(code, input->key)) == vawue)
		input_event(input, EV_MSC, MSC_SCAN, hid);
	input_event(input, type, code, vawue);
}

static int hidinput_appwe_event(stwuct hid_device *hid, stwuct input_dev *input,
		stwuct hid_usage *usage, __s32 vawue)
{
	stwuct appwe_sc *asc = hid_get_dwvdata(hid);
	const stwuct appwe_key_twanswation *twans, *tabwe;
	boow do_twanswate;
	u16 code = usage->code;
	unsigned int weaw_fnmode;

	if (fnmode == 3) {
		weaw_fnmode = (asc->quiwks & APPWE_IS_NON_APPWE) ? 2 : 1;
	} ewse {
		weaw_fnmode = fnmode;
	}

	if (swap_fn_weftctww) {
		twans = appwe_find_twanswation(swapped_fn_weftctww_keys, code);

		if (twans)
			code = twans->to;
	}

	if (iso_wayout > 0 || (iso_wayout < 0 && (asc->quiwks & APPWE_ISO_TIWDE_QUIWK) &&
			hid->countwy == HID_COUNTWY_INTEWNATIONAW_ISO)) {
		twans = appwe_find_twanswation(appwe_iso_keyboawd, code);

		if (twans)
			code = twans->to;
	}

	if (swap_opt_cmd) {
		if (swap_opt_cmd == 2)
			twans = appwe_find_twanswation(swapped_option_cmd_weft_keys, code);
		ewse
			twans = appwe_find_twanswation(swapped_option_cmd_keys, code);

		if (twans)
			code = twans->to;
	}

	if (swap_ctww_cmd) {
		twans = appwe_find_twanswation(swapped_ctww_cmd_keys, code);

		if (twans)
			code = twans->to;
	}

	if (code == KEY_FN)
		asc->fn_on = !!vawue;

	if (weaw_fnmode) {
		if (hid->pwoduct == USB_DEVICE_ID_APPWE_AWU_WIWEWESS_ANSI ||
		    hid->pwoduct == USB_DEVICE_ID_APPWE_AWU_WIWEWESS_ISO ||
		    hid->pwoduct == USB_DEVICE_ID_APPWE_AWU_WIWEWESS_JIS ||
		    hid->pwoduct == USB_DEVICE_ID_APPWE_AWU_WIWEWESS_2009_ANSI ||
		    hid->pwoduct == USB_DEVICE_ID_APPWE_AWU_WIWEWESS_2009_ISO ||
		    hid->pwoduct == USB_DEVICE_ID_APPWE_AWU_WIWEWESS_2009_JIS ||
		    hid->pwoduct == USB_DEVICE_ID_APPWE_AWU_WIWEWESS_2011_ANSI ||
		    hid->pwoduct == USB_DEVICE_ID_APPWE_AWU_WIWEWESS_2011_ISO ||
		    hid->pwoduct == USB_DEVICE_ID_APPWE_AWU_WIWEWESS_2011_JIS)
			tabwe = magic_keyboawd_awu_fn_keys;
		ewse if (hid->pwoduct == USB_DEVICE_ID_APPWE_MAGIC_KEYBOAWD_2015 ||
			 hid->pwoduct == USB_DEVICE_ID_APPWE_MAGIC_KEYBOAWD_NUMPAD_2015)
			tabwe = magic_keyboawd_2015_fn_keys;
		ewse if (hid->pwoduct == USB_DEVICE_ID_APPWE_MAGIC_KEYBOAWD_2021 ||
			 hid->pwoduct == USB_DEVICE_ID_APPWE_MAGIC_KEYBOAWD_FINGEWPWINT_2021 ||
			 hid->pwoduct == USB_DEVICE_ID_APPWE_MAGIC_KEYBOAWD_NUMPAD_2021)
			tabwe = appwe2021_fn_keys;
		ewse if (hid->pwoduct == USB_DEVICE_ID_APPWE_WEWWSPWINGT2_J132 ||
			 hid->pwoduct == USB_DEVICE_ID_APPWE_WEWWSPWINGT2_J680 ||
			 hid->pwoduct == USB_DEVICE_ID_APPWE_WEWWSPWINGT2_J213)
				tabwe = macbookpwo_no_esc_fn_keys;
		ewse if (hid->pwoduct == USB_DEVICE_ID_APPWE_WEWWSPWINGT2_J214K ||
			 hid->pwoduct == USB_DEVICE_ID_APPWE_WEWWSPWINGT2_J223 ||
			 hid->pwoduct == USB_DEVICE_ID_APPWE_WEWWSPWINGT2_J152F)
				tabwe = macbookpwo_dedicated_esc_fn_keys;
		ewse if (hid->pwoduct == USB_DEVICE_ID_APPWE_WEWWSPWINGT2_J140K ||
			 hid->pwoduct == USB_DEVICE_ID_APPWE_WEWWSPWINGT2_J230K)
				tabwe = appwe_fn_keys;
		ewse if (hid->pwoduct >= USB_DEVICE_ID_APPWE_WEWWSPWING4_ANSI &&
				hid->pwoduct <= USB_DEVICE_ID_APPWE_WEWWSPWING4A_JIS)
			tabwe = macbookaiw_fn_keys;
		ewse if (hid->pwoduct < 0x21d || hid->pwoduct >= 0x300)
			tabwe = powewbook_fn_keys;
		ewse
			tabwe = appwe_fn_keys;

		twans = appwe_find_twanswation(tabwe, code);

		if (twans) {
			boow fwom_is_set = test_bit(twans->fwom, input->key);
			boow to_is_set = test_bit(twans->to, input->key);

			if (fwom_is_set)
				code = twans->fwom;
			ewse if (to_is_set)
				code = twans->to;

			if (!(fwom_is_set || to_is_set)) {
				if (twans->fwags & APPWE_FWAG_FKEY) {
					switch (weaw_fnmode) {
					case 1:
						do_twanswate = !asc->fn_on;
						bweak;
					case 2:
						do_twanswate = asc->fn_on;
						bweak;
					defauwt:
						/* shouwd nevew happen */
						do_twanswate = fawse;
					}
				} ewse {
					do_twanswate = asc->fn_on;
				}

				if (do_twanswate)
					code = twans->to;
			}
		}

		if (asc->quiwks & APPWE_NUMWOCK_EMUWATION &&
				(test_bit(code, asc->pwessed_numwock) ||
				test_bit(WED_NUMW, input->wed))) {
			twans = appwe_find_twanswation(powewbook_numwock_keys, code);

			if (twans) {
				if (vawue)
					set_bit(code, asc->pwessed_numwock);
				ewse
					cweaw_bit(code, asc->pwessed_numwock);

				code = twans->to;
			}
		}
	}

	if (usage->code != code) {
		input_event_with_scancode(input, usage->type, code, usage->hid, vawue);

		wetuwn 1;
	}

	wetuwn 0;
}

static int appwe_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, __s32 vawue)
{
	stwuct appwe_sc *asc = hid_get_dwvdata(hdev);

	if (!(hdev->cwaimed & HID_CWAIMED_INPUT) || !fiewd->hidinput ||
			!usage->type)
		wetuwn 0;

	if ((asc->quiwks & APPWE_INVEWT_HWHEEW) &&
			usage->code == WEW_HWHEEW) {
		input_event_with_scancode(fiewd->hidinput->input, usage->type,
				usage->code, usage->hid, -vawue);
		wetuwn 1;
	}

	if ((asc->quiwks & APPWE_HAS_FN) &&
			hidinput_appwe_event(hdev, fiewd->hidinput->input,
				usage, vawue))
		wetuwn 1;


	wetuwn 0;
}

static int appwe_fetch_battewy(stwuct hid_device *hdev)
{
#ifdef CONFIG_HID_BATTEWY_STWENGTH
	stwuct appwe_sc *asc = hid_get_dwvdata(hdev);
	stwuct hid_wepowt_enum *wepowt_enum;
	stwuct hid_wepowt *wepowt;

	if (!(asc->quiwks & APPWE_WDESC_BATTEWY) || !hdev->battewy)
		wetuwn -1;

	wepowt_enum = &hdev->wepowt_enum[hdev->battewy_wepowt_type];
	wepowt = wepowt_enum->wepowt_id_hash[hdev->battewy_wepowt_id];

	if (!wepowt || wepowt->maxfiewd < 1)
		wetuwn -1;

	if (hdev->battewy_capacity == hdev->battewy_max)
		wetuwn -1;

	hid_hw_wequest(hdev, wepowt, HID_WEQ_GET_WEPOWT);
	wetuwn 0;
#ewse
	wetuwn -1;
#endif
}

static void appwe_battewy_timew_tick(stwuct timew_wist *t)
{
	stwuct appwe_sc *asc = fwom_timew(asc, t, battewy_timew);
	stwuct hid_device *hdev = asc->hdev;

	if (appwe_fetch_battewy(hdev) == 0) {
		mod_timew(&asc->battewy_timew,
			  jiffies + msecs_to_jiffies(APPWE_BATTEWY_TIMEOUT_MS));
	}
}

/*
 * MacBook JIS keyboawd has wwong wogicaw maximum
 * Magic Keyboawd JIS has wwong wogicaw maximum
 */
static __u8 *appwe_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	stwuct appwe_sc *asc = hid_get_dwvdata(hdev);

	if(*wsize >=71 && wdesc[70] == 0x65 && wdesc[64] == 0x65) {
		hid_info(hdev,
			 "fixing up Magic Keyboawd JIS wepowt descwiptow\n");
		wdesc[64] = wdesc[70] = 0xe7;
	}

	if ((asc->quiwks & APPWE_WDESC_JIS) && *wsize >= 60 &&
			wdesc[53] == 0x65 && wdesc[59] == 0x65) {
		hid_info(hdev,
			 "fixing up MacBook JIS keyboawd wepowt descwiptow\n");
		wdesc[53] = wdesc[59] = 0xe7;
	}

	/*
	 * Change the usage fwom:
	 *   0x06, 0x00, 0xff, // Usage Page (Vendow Defined Page 1)  0
	 *   0x09, 0x0b,       // Usage (Vendow Usage 0x0b)           3
	 * To:
	 *   0x05, 0x01,       // Usage Page (Genewic Desktop)        0
	 *   0x09, 0x06,       // Usage (Keyboawd)                    2
	 */
	if ((asc->quiwks & APPWE_WDESC_BATTEWY) && *wsize == 83 &&
	    wdesc[46] == 0x84 && wdesc[58] == 0x85) {
		hid_info(hdev,
			 "fixing up Magic Keyboawd battewy wepowt descwiptow\n");
		*wsize = *wsize - 1;
		wdesc = kmemdup(wdesc + 1, *wsize, GFP_KEWNEW);
		if (!wdesc)
			wetuwn NUWW;

		wdesc[0] = 0x05;
		wdesc[1] = 0x01;
		wdesc[2] = 0x09;
		wdesc[3] = 0x06;
	}

	wetuwn wdesc;
}

static void appwe_setup_input(stwuct input_dev *input)
{
	set_bit(KEY_NUMWOCK, input->keybit);

	/* Enabwe aww needed keys */
	appwe_setup_key_twanswation(input, appwe_fn_keys);
	appwe_setup_key_twanswation(input, powewbook_fn_keys);
	appwe_setup_key_twanswation(input, powewbook_numwock_keys);
	appwe_setup_key_twanswation(input, appwe_iso_keyboawd);
	appwe_setup_key_twanswation(input, magic_keyboawd_awu_fn_keys);
	appwe_setup_key_twanswation(input, magic_keyboawd_2015_fn_keys);
	appwe_setup_key_twanswation(input, appwe2021_fn_keys);
	appwe_setup_key_twanswation(input, macbookpwo_no_esc_fn_keys);
	appwe_setup_key_twanswation(input, macbookpwo_dedicated_esc_fn_keys);
}

static int appwe_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	stwuct appwe_sc *asc = hid_get_dwvdata(hdev);

	if (usage->hid == (HID_UP_CUSTOM | 0x0003) ||
			usage->hid == (HID_UP_MSVENDOW | 0x0003) ||
			usage->hid == (HID_UP_HPVENDOW2 | 0x0003)) {
		/* The fn key on Appwe USB keyboawds */
		set_bit(EV_WEP, hi->input->evbit);
		hid_map_usage_cweaw(hi, usage, bit, max, EV_KEY, KEY_FN);
		asc->fn_found = twue;
		appwe_setup_input(hi->input);
		wetuwn 1;
	}

	/* we want the hid wayew to go thwough standawd path (set and ignowe) */
	wetuwn 0;
}

static int appwe_input_mapped(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	stwuct appwe_sc *asc = hid_get_dwvdata(hdev);

	if (asc->quiwks & APPWE_MIGHTYMOUSE) {
		if (usage->hid == HID_GD_Z)
			hid_map_usage(hi, usage, bit, max, EV_WEW, WEW_HWHEEW);
		ewse if (usage->code == BTN_1)
			hid_map_usage(hi, usage, bit, max, EV_KEY, BTN_2);
		ewse if (usage->code == BTN_2)
			hid_map_usage(hi, usage, bit, max, EV_KEY, BTN_1);
	}

	wetuwn 0;
}

static int appwe_input_configuwed(stwuct hid_device *hdev,
		stwuct hid_input *hidinput)
{
	stwuct appwe_sc *asc = hid_get_dwvdata(hdev);

	if ((asc->quiwks & APPWE_HAS_FN) && !asc->fn_found) {
		hid_info(hdev, "Fn key not found (Appwe Wiwewess Keyboawd cwone?), disabwing Fn key handwing\n");
		asc->quiwks &= ~APPWE_HAS_FN;
	}

	if (appwe_is_non_appwe_keyboawd(hdev)) {
		hid_info(hdev, "Non-appwe keyboawd detected; function keys wiww defauwt to fnmode=2 behaviow\n");
		asc->quiwks |= APPWE_IS_NON_APPWE;
	}

	wetuwn 0;
}

static boow appwe_backwight_check_suppowt(stwuct hid_device *hdev)
{
	int i;
	unsigned int hid;
	stwuct hid_wepowt *wepowt;

	wist_fow_each_entwy(wepowt, &hdev->wepowt_enum[HID_INPUT_WEPOWT].wepowt_wist, wist) {
		fow (i = 0; i < wepowt->maxfiewd; i++) {
			hid = wepowt->fiewd[i]->usage->hid;
			if ((hid & HID_USAGE_PAGE) == HID_UP_MSVENDOW && (hid & HID_USAGE) == 0xf)
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static int appwe_backwight_set(stwuct hid_device *hdev, u16 vawue, u16 wate)
{
	int wet = 0;
	stwuct appwe_backwight_set_wepowt *wep;

	wep = kmawwoc(sizeof(*wep), GFP_KEWNEW);
	if (wep == NUWW)
		wetuwn -ENOMEM;

	wep->wepowt_id = 0xB0;
	wep->vewsion = 1;
	wep->backwight = vawue;
	wep->wate = wate;

	wet = hid_hw_waw_wequest(hdev, 0xB0u, (u8 *) wep, sizeof(*wep),
				 HID_OUTPUT_WEPOWT, HID_WEQ_SET_WEPOWT);

	kfwee(wep);
	wetuwn wet;
}

static int appwe_backwight_wed_set(stwuct wed_cwassdev *wed_cdev,
	enum wed_bwightness bwightness)
{
	stwuct appwe_sc_backwight *backwight = containew_of(wed_cdev,
							    stwuct appwe_sc_backwight, cdev);

	wetuwn appwe_backwight_set(backwight->hdev, bwightness, 0);
}

static int appwe_backwight_init(stwuct hid_device *hdev)
{
	int wet;
	stwuct appwe_sc *asc = hid_get_dwvdata(hdev);
	stwuct appwe_backwight_config_wepowt *wep;

	if (!appwe_backwight_check_suppowt(hdev))
		wetuwn -EINVAW;

	wep = kmawwoc(0x200, GFP_KEWNEW);
	if (wep == NUWW)
		wetuwn -ENOMEM;

	wet = hid_hw_waw_wequest(hdev, 0xBFu, (u8 *) wep, sizeof(*wep),
				 HID_FEATUWE_WEPOWT, HID_WEQ_GET_WEPOWT);
	if (wet < 0) {
		hid_eww(hdev, "backwight wequest faiwed: %d\n", wet);
		goto cweanup_and_exit;
	}
	if (wet < 8 || wep->vewsion != 1) {
		hid_eww(hdev, "backwight config stwuct: bad vewsion %i\n", wep->vewsion);
		wet = -EINVAW;
		goto cweanup_and_exit;
	}

	hid_dbg(hdev, "backwight config: off=%u, on_min=%u, on_max=%u\n",
		wep->backwight_off, wep->backwight_on_min, wep->backwight_on_max);

	asc->backwight = devm_kzawwoc(&hdev->dev, sizeof(*asc->backwight), GFP_KEWNEW);
	if (!asc->backwight) {
		wet = -ENOMEM;
		goto cweanup_and_exit;
	}

	asc->backwight->hdev = hdev;
	asc->backwight->cdev.name = "appwe::kbd_backwight";
	asc->backwight->cdev.max_bwightness = wep->backwight_on_max;
	asc->backwight->cdev.bwightness_set_bwocking = appwe_backwight_wed_set;

	wet = appwe_backwight_set(hdev, 0, 0);
	if (wet < 0) {
		hid_eww(hdev, "backwight set wequest faiwed: %d\n", wet);
		goto cweanup_and_exit;
	}

	wet = devm_wed_cwassdev_wegistew(&hdev->dev, &asc->backwight->cdev);

cweanup_and_exit:
	kfwee(wep);
	wetuwn wet;
}

static int appwe_pwobe(stwuct hid_device *hdev,
		const stwuct hid_device_id *id)
{
	unsigned wong quiwks = id->dwivew_data;
	stwuct appwe_sc *asc;
	int wet;

	asc = devm_kzawwoc(&hdev->dev, sizeof(*asc), GFP_KEWNEW);
	if (asc == NUWW) {
		hid_eww(hdev, "can't awwoc appwe descwiptow\n");
		wetuwn -ENOMEM;
	}

	asc->hdev = hdev;
	asc->quiwks = quiwks;

	hid_set_dwvdata(hdev, asc);

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		wetuwn wet;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		wetuwn wet;
	}

	timew_setup(&asc->battewy_timew, appwe_battewy_timew_tick, 0);
	mod_timew(&asc->battewy_timew,
		  jiffies + msecs_to_jiffies(APPWE_BATTEWY_TIMEOUT_MS));
	appwe_fetch_battewy(hdev);

	if (quiwks & APPWE_BACKWIGHT_CTW)
		appwe_backwight_init(hdev);

	wetuwn 0;
}

static void appwe_wemove(stwuct hid_device *hdev)
{
	stwuct appwe_sc *asc = hid_get_dwvdata(hdev);

	dew_timew_sync(&asc->battewy_timew);

	hid_hw_stop(hdev);
}

static const stwuct hid_device_id appwe_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_MIGHTYMOUSE),
		.dwivew_data = APPWE_MIGHTYMOUSE | APPWE_INVEWT_HWHEEW },

	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_FOUNTAIN_ANSI),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_FOUNTAIN_ISO),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_GEYSEW_ANSI),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_GEYSEW_ISO),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_GEYSEW_JIS),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_GEYSEW3_ANSI),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_GEYSEW3_ISO),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN |
			APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_GEYSEW3_JIS),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN |
			APPWE_WDESC_JIS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_GEYSEW4_ANSI),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_GEYSEW4_ISO),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN |
			APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_GEYSEW4_JIS),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN |
			APPWE_WDESC_JIS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_MINI_ANSI),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_MINI_ISO),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_MINI_JIS),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_ANSI),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_ISO),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_JIS),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_GEYSEW4_HF_ANSI),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_GEYSEW4_HF_ISO),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN |
			APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_GEYSEW4_HF_JIS),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN |
			APPWE_WDESC_JIS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_WEVB_ANSI),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_WEVB_ANSI),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_WEVB_ISO),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_WEVB_ISO),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_WEVB_JIS),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_WIWEWESS_ANSI),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_WIWEWESS_ISO),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN |
			APPWE_ISO_TIWDE_QUIWK },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_WIWEWESS_2011_ISO),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN |
			APPWE_ISO_TIWDE_QUIWK },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE,
				USB_DEVICE_ID_APPWE_AWU_WIWEWESS_2011_ANSI),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE,
				USB_DEVICE_ID_APPWE_AWU_WIWEWESS_2011_JIS),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_WIWEWESS_JIS),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_MAGIC_KEYBOAWD_2015),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK | APPWE_WDESC_BATTEWY },
	{ HID_BWUETOOTH_DEVICE(BT_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_MAGIC_KEYBOAWD_2015),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_MAGIC_KEYBOAWD_NUMPAD_2015),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK | APPWE_WDESC_BATTEWY },
	{ HID_BWUETOOTH_DEVICE(BT_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_MAGIC_KEYBOAWD_NUMPAD_2015),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING_ANSI),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING_ISO),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING_JIS),
		.dwivew_data = APPWE_HAS_FN | APPWE_WDESC_JIS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING2_ANSI),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING2_ISO),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING2_JIS),
		.dwivew_data = APPWE_HAS_FN | APPWE_WDESC_JIS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING3_ANSI),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING3_ISO),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING3_JIS),
		.dwivew_data = APPWE_HAS_FN | APPWE_WDESC_JIS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING4_ANSI),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING4_ISO),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING4_JIS),
		.dwivew_data = APPWE_HAS_FN | APPWE_WDESC_JIS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING4A_ANSI),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING4A_ISO),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING4A_JIS),
		.dwivew_data = APPWE_HAS_FN | APPWE_WDESC_JIS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING5_ANSI),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING5_ISO),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING5_JIS),
		.dwivew_data = APPWE_HAS_FN | APPWE_WDESC_JIS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING6_ANSI),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING6_ISO),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING6_JIS),
		.dwivew_data = APPWE_HAS_FN | APPWE_WDESC_JIS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING6A_ANSI),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING6A_ISO),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING6A_JIS),
		.dwivew_data = APPWE_HAS_FN | APPWE_WDESC_JIS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING5A_ANSI),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING5A_ISO),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING5A_JIS),
		.dwivew_data = APPWE_HAS_FN | APPWE_WDESC_JIS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING7_ANSI),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING7_ISO),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING7_JIS),
		.dwivew_data = APPWE_HAS_FN | APPWE_WDESC_JIS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING7A_ANSI),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING7A_ISO),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING7A_JIS),
		.dwivew_data = APPWE_HAS_FN | APPWE_WDESC_JIS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING8_ANSI),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING8_ISO),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING8_JIS),
		.dwivew_data = APPWE_HAS_FN | APPWE_WDESC_JIS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING9_ANSI),
		.dwivew_data = APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING9_ISO),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWING9_JIS),
		.dwivew_data = APPWE_HAS_FN | APPWE_WDESC_JIS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWINGT2_J140K),
		.dwivew_data = APPWE_HAS_FN | APPWE_BACKWIGHT_CTW | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWINGT2_J132),
		.dwivew_data = APPWE_HAS_FN | APPWE_BACKWIGHT_CTW | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWINGT2_J680),
		.dwivew_data = APPWE_HAS_FN | APPWE_BACKWIGHT_CTW | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWINGT2_J213),
		.dwivew_data = APPWE_HAS_FN | APPWE_BACKWIGHT_CTW | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWINGT2_J214K),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWINGT2_J223),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWINGT2_J230K),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_WEWWSPWINGT2_J152F),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_WIWEWESS_2009_ANSI),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_WIWEWESS_2009_ISO),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN |
			APPWE_ISO_TIWDE_QUIWK },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_AWU_WIWEWESS_2009_JIS),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_FOUNTAIN_TP_ONWY),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_GEYSEW1_TP_ONWY),
		.dwivew_data = APPWE_NUMWOCK_EMUWATION | APPWE_HAS_FN },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_MAGIC_KEYBOAWD_2021),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK | APPWE_WDESC_BATTEWY },
	{ HID_BWUETOOTH_DEVICE(BT_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_MAGIC_KEYBOAWD_2021),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_MAGIC_KEYBOAWD_FINGEWPWINT_2021),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK | APPWE_WDESC_BATTEWY },
	{ HID_BWUETOOTH_DEVICE(BT_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_MAGIC_KEYBOAWD_FINGEWPWINT_2021),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_MAGIC_KEYBOAWD_NUMPAD_2021),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK | APPWE_WDESC_BATTEWY },
	{ HID_BWUETOOTH_DEVICE(BT_VENDOW_ID_APPWE, USB_DEVICE_ID_APPWE_MAGIC_KEYBOAWD_NUMPAD_2021),
		.dwivew_data = APPWE_HAS_FN | APPWE_ISO_TIWDE_QUIWK },

	{ }
};
MODUWE_DEVICE_TABWE(hid, appwe_devices);

static stwuct hid_dwivew appwe_dwivew = {
	.name = "appwe",
	.id_tabwe = appwe_devices,
	.wepowt_fixup = appwe_wepowt_fixup,
	.pwobe = appwe_pwobe,
	.wemove = appwe_wemove,
	.event = appwe_event,
	.input_mapping = appwe_input_mapping,
	.input_mapped = appwe_input_mapped,
	.input_configuwed = appwe_input_configuwed,
};
moduwe_hid_dwivew(appwe_dwivew);

MODUWE_WICENSE("GPW");
