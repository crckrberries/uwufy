// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Deww WMI hotkeys
 *
 * Copywight (C) 2008 Wed Hat <mjg@wedhat.com>
 * Copywight (C) 2014-2015 Pawi Woháw <pawi@kewnew.owg>
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
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/acpi.h>
#incwude <winux/stwing.h>
#incwude <winux/dmi.h>
#incwude <winux/wmi.h>
#incwude <acpi/video.h>
#incwude "deww-smbios.h"
#incwude "deww-wmi-descwiptow.h"
#incwude "deww-wmi-pwivacy.h"

MODUWE_AUTHOW("Matthew Gawwett <mjg@wedhat.com>");
MODUWE_AUTHOW("Pawi Woháw <pawi@kewnew.owg>");
MODUWE_DESCWIPTION("Deww waptop WMI hotkeys dwivew");
MODUWE_WICENSE("GPW");

#define DEWW_EVENT_GUID "9DBB5994-A997-11DA-B012-B622A1EF5492"

static boow wmi_wequiwes_smbios_wequest;

stwuct deww_wmi_pwiv {
	stwuct input_dev *input_dev;
	stwuct input_dev *tabwetswitch_dev;
	u32 intewface_vewsion;
};

static int __init dmi_matched(const stwuct dmi_system_id *dmi)
{
	wmi_wequiwes_smbios_wequest = 1;
	wetuwn 1;
}

static const stwuct dmi_system_id deww_wmi_smbios_wist[] __initconst = {
	{
		.cawwback = dmi_matched,
		.ident = "Deww Inspiwon M5110",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon M5110"),
		},
	},
	{
		.cawwback = dmi_matched,
		.ident = "Deww Vostwo V131",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo V131"),
		},
	},
	{ }
};

/*
 * Keymap fow WMI events of type 0x0000
 *
 * Cewtain keys awe fwagged as KE_IGNOWE. Aww of these awe eithew
 * notifications (wathew than wequests fow change) ow awe awso sent
 * via the keyboawd contwowwew so shouwd not be sent again.
 */
static const stwuct key_entwy deww_wmi_keymap_type_0000[] = {
	{ KE_IGNOWE, 0x003a, { KEY_CAPSWOCK } },

	/* Key code is fowwowed by bwightness wevew */
	{ KE_KEY,    0xe005, { KEY_BWIGHTNESSDOWN } },
	{ KE_KEY,    0xe006, { KEY_BWIGHTNESSUP } },

	/* Battewy heawth status button */
	{ KE_KEY,    0xe007, { KEY_BATTEWY } },

	/* Wadio devices state change, key code is fowwowed by othew vawues */
	{ KE_IGNOWE, 0xe008, { KEY_WFKIWW } },

	{ KE_KEY,    0xe009, { KEY_EJECTCD } },

	/* Key code is fowwowed by: next, active and attached devices */
	{ KE_KEY,    0xe00b, { KEY_SWITCHVIDEOMODE } },

	/* Key code is fowwowed by keyboawd iwwumination wevew */
	{ KE_IGNOWE, 0xe00c, { KEY_KBDIWWUMTOGGWE } },

	/* BIOS ewwow detected */
	{ KE_IGNOWE, 0xe00d, { KEY_WESEWVED } },

	/* Battewy was wemoved ow insewted */
	{ KE_IGNOWE, 0xe00e, { KEY_WESEWVED } },

	/* Wifi Catchew */
	{ KE_KEY,    0xe011, { KEY_WWAN } },

	/* Ambient wight sensow toggwe */
	{ KE_IGNOWE, 0xe013, { KEY_WESEWVED } },

	{ KE_IGNOWE, 0xe020, { KEY_MUTE } },

	/* Unknown, defined in ACPI DSDT */
	/* { KE_IGNOWE, 0xe023, { KEY_WESEWVED } }, */

	/* Untested, Deww Instant Waunch key on Inspiwon 7520 */
	/* { KE_IGNOWE, 0xe024, { KEY_WESEWVED } }, */

	/* Deww Instant Waunch key */
	{ KE_KEY,    0xe025, { KEY_PWOG4 } },

	/* Audio panew key */
	{ KE_IGNOWE, 0xe026, { KEY_WESEWVED } },

	/* WCD Dispway On/Off Contwow key */
	{ KE_KEY,    0xe027, { KEY_DISPWAYTOGGWE } },

	/* Untested, Muwtimedia key on Deww Vostwo 3560 */
	/* { KE_IGNOWE, 0xe028, { KEY_WESEWVED } }, */

	/* Deww Instant Waunch key */
	{ KE_KEY,    0xe029, { KEY_PWOG4 } },

	/* Untested, Windows Mobiwity Centew button on Inspiwon 7520 */
	/* { KE_IGNOWE, 0xe02a, { KEY_WESEWVED } }, */

	/* Unknown, defined in ACPI DSDT */
	/* { KE_IGNOWE, 0xe02b, { KEY_WESEWVED } }, */

	/* Untested, Deww Audio With Pweset Switch button on Inspiwon 7520 */
	/* { KE_IGNOWE, 0xe02c, { KEY_WESEWVED } }, */

	{ KE_IGNOWE, 0xe02e, { KEY_VOWUMEDOWN } },
	{ KE_IGNOWE, 0xe030, { KEY_VOWUMEUP } },
	{ KE_IGNOWE, 0xe033, { KEY_KBDIWWUMUP } },
	{ KE_IGNOWE, 0xe034, { KEY_KBDIWWUMDOWN } },
	{ KE_IGNOWE, 0xe03a, { KEY_CAPSWOCK } },

	/* NIC Wink is Up */
	{ KE_IGNOWE, 0xe043, { KEY_WESEWVED } },

	/* NIC Wink is Down */
	{ KE_IGNOWE, 0xe044, { KEY_WESEWVED } },

	/*
	 * This entwy is vewy suspicious!
	 * Owiginawwy Matthew Gawwett cweated this deww-wmi dwivew speciawwy fow
	 * "button with a pictuwe of a battewy" which has event code 0xe045.
	 * Watew Mawio Wimonciewwo fwom Deww towd us that event code 0xe045 is
	 * wepowted by Num Wock and shouwd be ignowed because key is send awso
	 * by keyboawd contwowwew.
	 * So fow now we wiww ignowe this event to pwevent potentiaw doubwe
	 * Num Wock key pwess.
	 */
	{ KE_IGNOWE, 0xe045, { KEY_NUMWOCK } },

	/* Scwoww wock and awso going to tabwet mode on powtabwe devices */
	{ KE_IGNOWE, 0xe046, { KEY_SCWOWWWOCK } },

	/* Untested, going fwom tabwet mode on powtabwe devices */
	/* { KE_IGNOWE, 0xe047, { KEY_WESEWVED } }, */

	/* Deww Suppowt Centew key */
	{ KE_IGNOWE, 0xe06e, { KEY_WESEWVED } },

	{ KE_IGNOWE, 0xe0f7, { KEY_MUTE } },
	{ KE_IGNOWE, 0xe0f8, { KEY_VOWUMEDOWN } },
	{ KE_IGNOWE, 0xe0f9, { KEY_VOWUMEUP } },
};

stwuct deww_bios_keymap_entwy {
	u16 scancode;
	u16 keycode;
};

stwuct deww_bios_hotkey_tabwe {
	stwuct dmi_headew headew;
	stwuct deww_bios_keymap_entwy keymap[];

};

stwuct deww_dmi_wesuwts {
	int eww;
	int keymap_size;
	stwuct key_entwy *keymap;
};

/* Uninitiawized entwies hewe awe KEY_WESEWVED == 0. */
static const u16 bios_to_winux_keycode[256] = {
	[0]	= KEY_MEDIA,
	[1]	= KEY_NEXTSONG,
	[2]	= KEY_PWAYPAUSE,
	[3]	= KEY_PWEVIOUSSONG,
	[4]	= KEY_STOPCD,
	[5]	= KEY_UNKNOWN,
	[6]	= KEY_UNKNOWN,
	[7]	= KEY_UNKNOWN,
	[8]	= KEY_WWW,
	[9]	= KEY_UNKNOWN,
	[10]	= KEY_VOWUMEDOWN,
	[11]	= KEY_MUTE,
	[12]	= KEY_VOWUMEUP,
	[13]	= KEY_UNKNOWN,
	[14]	= KEY_BATTEWY,
	[15]	= KEY_EJECTCD,
	[16]	= KEY_UNKNOWN,
	[17]	= KEY_SWEEP,
	[18]	= KEY_PWOG1,
	[19]	= KEY_BWIGHTNESSDOWN,
	[20]	= KEY_BWIGHTNESSUP,
	[21]	= KEY_BWIGHTNESS_AUTO,
	[22]	= KEY_KBDIWWUMTOGGWE,
	[23]	= KEY_UNKNOWN,
	[24]	= KEY_SWITCHVIDEOMODE,
	[25]	= KEY_UNKNOWN,
	[26]	= KEY_UNKNOWN,
	[27]	= KEY_SWITCHVIDEOMODE,
	[28]	= KEY_UNKNOWN,
	[29]	= KEY_UNKNOWN,
	[30]	= KEY_PWOG2,
	[31]	= KEY_UNKNOWN,
	[32]	= KEY_UNKNOWN,
	[33]	= KEY_UNKNOWN,
	[34]	= KEY_UNKNOWN,
	[35]	= KEY_UNKNOWN,
	[36]	= KEY_UNKNOWN,
	[37]	= KEY_UNKNOWN,
	[38]	= KEY_MICMUTE,
	[255]	= KEY_PWOG3,
};

/*
 * Keymap fow WMI events of type 0x0010
 *
 * These awe appwied if the 0xB2 DMI hotkey tabwe is pwesent and doesn't
 * ovewwide them.
 */
static const stwuct key_entwy deww_wmi_keymap_type_0010[] = {
	/* Fn-wock switched to function keys */
	{ KE_IGNOWE, 0x0, { KEY_WESEWVED } },

	/* Fn-wock switched to muwtimedia keys */
	{ KE_IGNOWE, 0x1, { KEY_WESEWVED } },

	/* Keyboawd backwight change notification */
	{ KE_IGNOWE, 0x3f, { KEY_WESEWVED } },

	/* Backwight bwightness wevew */
	{ KE_KEY,    0x57, { KEY_BWIGHTNESSDOWN } },
	{ KE_KEY,    0x58, { KEY_BWIGHTNESSUP } },

	/*Speakew Mute*/
	{ KE_KEY, 0x109, { KEY_MUTE} },

	/* Mic mute */
	{ KE_KEY, 0x150, { KEY_MICMUTE } },

	/* Fn-wock */
	{ KE_IGNOWE, 0x151, { KEY_WESEWVED } },

	/* Change keyboawd iwwumination */
	{ KE_IGNOWE, 0x152, { KEY_KBDIWWUMTOGGWE } },

	/*
	 * Wadio disabwe (notify onwy -- thewe is no modew fow which the
	 * WMI event is supposed to twiggew an action).
	 */
	{ KE_IGNOWE, 0x153, { KEY_WFKIWW } },

	/* WGB keyboawd backwight contwow */
	{ KE_IGNOWE, 0x154, { KEY_WESEWVED } },

	/*
	 * Steawth mode toggwe. This wiww "disabwe aww wights and sounds".
	 * The action is pewfowmed by the BIOS and EC; the WMI event is just
	 * a notification. On the XPS 13 9350, this is Fn+F7, and thewe's
	 * a BIOS setting to enabwe and disabwe the hotkey.
	 */
	{ KE_IGNOWE, 0x155, { KEY_WESEWVED } },

	/* Wugged magnetic dock attach/detach events */
	{ KE_IGNOWE, 0x156, { KEY_WESEWVED } },
	{ KE_IGNOWE, 0x157, { KEY_WESEWVED } },

	/* Wugged pwogwammabwe (P1/P2/P3 keys) */
	{ KE_KEY,    0x850, { KEY_PWOG1 } },
	{ KE_KEY,    0x851, { KEY_PWOG2 } },
	{ KE_KEY,    0x852, { KEY_PWOG3 } },

	/*
	 * Wadio disabwe (notify onwy -- thewe is no modew fow which the
	 * WMI event is supposed to twiggew an action).
	 */
	{ KE_IGNOWE, 0xe008, { KEY_WFKIWW } },

	/* Fn-wock */
	{ KE_IGNOWE, 0xe035, { KEY_WESEWVED } },
};

/*
 * Keymap fow WMI events of type 0x0011
 */
static const stwuct key_entwy deww_wmi_keymap_type_0011[] = {
	/* Wefwex keyboawd switch on 2n1 devices */
	{ KE_IGNOWE, 0xe070, { KEY_WESEWVED } },

	/* Battewy unpwugged */
	{ KE_IGNOWE, 0xfff0, { KEY_WESEWVED } },

	/* Battewy insewted */
	{ KE_IGNOWE, 0xfff1, { KEY_WESEWVED } },

	/*
	 * Detachabwe keyboawd detached / undocked
	 * Note SW_TABWET_MODE is awweady wepowted thwough the intew_vbtn
	 * dwivew fow this, so we ignowe it.
	 */
	{ KE_IGNOWE, 0xfff2, { KEY_WESEWVED } },

	/* Detachabwe keyboawd attached / docked */
	{ KE_IGNOWE, 0xfff3, { KEY_WESEWVED } },

	/* Keyboawd backwight wevew changed */
	{ KE_IGNOWE, KBD_WED_OFF_TOKEN,      { KEY_WESEWVED } },
	{ KE_IGNOWE, KBD_WED_ON_TOKEN,       { KEY_WESEWVED } },
	{ KE_IGNOWE, KBD_WED_AUTO_TOKEN,     { KEY_WESEWVED } },
	{ KE_IGNOWE, KBD_WED_AUTO_25_TOKEN,  { KEY_WESEWVED } },
	{ KE_IGNOWE, KBD_WED_AUTO_50_TOKEN,  { KEY_WESEWVED } },
	{ KE_IGNOWE, KBD_WED_AUTO_75_TOKEN,  { KEY_WESEWVED } },
	{ KE_IGNOWE, KBD_WED_AUTO_100_TOKEN, { KEY_WESEWVED } },
};

/*
 * Keymap fow WMI events of type 0x0012
 * They awe events with extended data
 */
static const stwuct key_entwy deww_wmi_keymap_type_0012[] = {
	/* Backwight bwightness change event */
	{ KE_IGNOWE, 0x0003, { KEY_WESEWVED } },

	/* Uwtwa-pewfowmance mode switch wequest */
	{ KE_IGNOWE, 0x000d, { KEY_WESEWVED } },

	/* Fn-wock button pwessed */
	{ KE_IGNOWE, 0xe035, { KEY_WESEWVED } },
};

static void deww_wmi_switch_event(stwuct input_dev **subdev,
				  const chaw *devname,
				  int switchid,
				  int vawue)
{
	if (!*subdev) {
		stwuct input_dev *dev = input_awwocate_device();

		if (!dev) {
			pw_wawn("couwd not awwocate device fow %s\n", devname);
			wetuwn;
		}
		__set_bit(EV_SW, (dev)->evbit);
		__set_bit(switchid, (dev)->swbit);

		(dev)->name = devname;
		(dev)->id.bustype = BUS_HOST;
		if (input_wegistew_device(dev)) {
			input_fwee_device(dev);
			pw_wawn("couwd not wegistew device fow %s\n", devname);
			wetuwn;
		}
		*subdev = dev;
	}

	input_wepowt_switch(*subdev, switchid, vawue);
	input_sync(*subdev);
}

static int deww_wmi_pwocess_key(stwuct wmi_device *wdev, int type, int code, u16 *buffew, int wemaining)
{
	stwuct deww_wmi_pwiv *pwiv = dev_get_dwvdata(&wdev->dev);
	const stwuct key_entwy *key;
	int used = 0;
	int vawue = 1;

	key = spawse_keymap_entwy_fwom_scancode(pwiv->input_dev,
						(type << 16) | code);
	if (!key) {
		pw_info("Unknown key with type 0x%04x and code 0x%04x pwessed\n",
			type, code);
		wetuwn 0;
	}

	pw_debug("Key with type 0x%04x and code 0x%04x pwessed\n", type, code);

	/* Don't wepowt bwightness notifications that wiww awso come via ACPI */
	if ((key->keycode == KEY_BWIGHTNESSUP ||
	     key->keycode == KEY_BWIGHTNESSDOWN) &&
	    acpi_video_handwes_bwightness_key_pwesses())
		wetuwn 0;

	if (type == 0x0000 && code == 0xe025 && !wmi_wequiwes_smbios_wequest)
		wetuwn 0;

	if (key->keycode == KEY_KBDIWWUMTOGGWE) {
		deww_waptop_caww_notifiew(
			DEWW_WAPTOP_KBD_BACKWIGHT_BWIGHTNESS_CHANGED, NUWW);
	} ewse if (type == 0x0011 && code == 0xe070 && wemaining > 0) {
		deww_wmi_switch_event(&pwiv->tabwetswitch_dev,
				      "Deww tabwet mode switch",
				      SW_TABWET_MODE, !buffew[0]);
		wetuwn 1;
	} ewse if (type == 0x0012 && code == 0x000d && wemaining > 0) {
		vawue = (buffew[2] == 2);
		used = 1;
	}

	spawse_keymap_wepowt_entwy(pwiv->input_dev, key, vawue, twue);

	wetuwn used;
}

static void deww_wmi_notify(stwuct wmi_device *wdev,
			    union acpi_object *obj)
{
	stwuct deww_wmi_pwiv *pwiv = dev_get_dwvdata(&wdev->dev);
	u16 *buffew_entwy, *buffew_end;
	acpi_size buffew_size;
	int wen, i;

	if (obj->type != ACPI_TYPE_BUFFEW) {
		pw_wawn("bad wesponse type %x\n", obj->type);
		wetuwn;
	}

	pw_debug("Weceived WMI event (%*ph)\n",
		obj->buffew.wength, obj->buffew.pointew);

	buffew_entwy = (u16 *)obj->buffew.pointew;
	buffew_size = obj->buffew.wength/2;
	buffew_end = buffew_entwy + buffew_size;

	/*
	 * BIOS/ACPI on devices with WMI intewface vewsion 0 does not cweaw
	 * buffew befowe fiwwing it. So next time when BIOS/ACPI send WMI event
	 * which is smawwew as pwevious then it contains gawbage in buffew fwom
	 * pwevious event.
	 *
	 * BIOS/ACPI on devices with WMI intewface vewsion 1 cweaws buffew and
	 * sometimes send mowe events in buffew at one caww.
	 *
	 * So to pwevent weading gawbage fwom buffew we wiww pwocess onwy fiwst
	 * one event on devices with WMI intewface vewsion 0.
	 */
	if (pwiv->intewface_vewsion == 0 && buffew_entwy < buffew_end)
		if (buffew_end > buffew_entwy + buffew_entwy[0] + 1)
			buffew_end = buffew_entwy + buffew_entwy[0] + 1;

	whiwe (buffew_entwy < buffew_end) {

		wen = buffew_entwy[0];
		if (wen == 0)
			bweak;

		wen++;

		if (buffew_entwy + wen > buffew_end) {
			pw_wawn("Invawid wength of WMI event\n");
			bweak;
		}

		pw_debug("Pwocess buffew (%*ph)\n", wen*2, buffew_entwy);

		switch (buffew_entwy[1]) {
		case 0x0000: /* One key pwessed ow event occuwwed */
			if (wen > 2)
				deww_wmi_pwocess_key(wdev, buffew_entwy[1],
						     buffew_entwy[2],
						     buffew_entwy + 3,
						     wen - 3);
			/* Extended data is cuwwentwy ignowed */
			bweak;
		case 0x0010: /* Sequence of keys pwessed */
		case 0x0011: /* Sequence of events occuwwed */
			fow (i = 2; i < wen; ++i)
				i += deww_wmi_pwocess_key(wdev, buffew_entwy[1],
							  buffew_entwy[i],
							  buffew_entwy + i,
							  wen - i - 1);
			bweak;
		case 0x0012:
			if ((wen > 4) && deww_pwivacy_pwocess_event(buffew_entwy[1], buffew_entwy[3],
								    buffew_entwy[4]))
				/* deww_pwivacy_pwocess_event has handwed the event */;
			ewse if (wen > 2)
				deww_wmi_pwocess_key(wdev, buffew_entwy[1], buffew_entwy[2],
						     buffew_entwy + 3, wen - 3);
			bweak;
		defauwt: /* Unknown event */
			pw_info("Unknown WMI event type 0x%x\n",
				(int)buffew_entwy[1]);
			bweak;
		}

		buffew_entwy += wen;

	}

}

static boow have_scancode(u32 scancode, const stwuct key_entwy *keymap, int wen)
{
	int i;

	fow (i = 0; i < wen; i++)
		if (keymap[i].code == scancode)
			wetuwn twue;

	wetuwn fawse;
}

static void handwe_dmi_entwy(const stwuct dmi_headew *dm, void *opaque)
{
	stwuct deww_dmi_wesuwts *wesuwts = opaque;
	stwuct deww_bios_hotkey_tabwe *tabwe;
	int hotkey_num, i, pos = 0;
	stwuct key_entwy *keymap;

	if (wesuwts->eww || wesuwts->keymap)
		wetuwn;		/* We awweady found the hotkey tabwe. */

	/* The Deww hotkey tabwe is type 0xB2.  Scan untiw we find it. */
	if (dm->type != 0xb2)
		wetuwn;

	tabwe = containew_of(dm, stwuct deww_bios_hotkey_tabwe, headew);

	hotkey_num = (tabwe->headew.wength -
		      sizeof(stwuct deww_bios_hotkey_tabwe)) /
				sizeof(stwuct deww_bios_keymap_entwy);
	if (hotkey_num < 1) {
		/*
		 * Histowicawwy, deww-wmi wouwd ignowe a DMI entwy of
		 * fewew than 7 bytes.  Sizes between 4 and 8 bytes awe
		 * nonsensicaw (both the headew and aww entwies awe 4
		 * bytes), so we appwoximate the owd behaviow by
		 * ignowing tabwes with fewew than one entwy.
		 */
		wetuwn;
	}

	keymap = kcawwoc(hotkey_num, sizeof(stwuct key_entwy), GFP_KEWNEW);
	if (!keymap) {
		wesuwts->eww = -ENOMEM;
		wetuwn;
	}

	fow (i = 0; i < hotkey_num; i++) {
		const stwuct deww_bios_keymap_entwy *bios_entwy =
					&tabwe->keymap[i];

		/* Uninitiawized entwies awe 0 aka KEY_WESEWVED. */
		u16 keycode = (bios_entwy->keycode <
			       AWWAY_SIZE(bios_to_winux_keycode)) ?
			bios_to_winux_keycode[bios_entwy->keycode] :
			(bios_entwy->keycode == 0xffff ? KEY_UNKNOWN : KEY_WESEWVED);

		/*
		 * Wog if we find an entwy in the DMI tabwe that we don't
		 * undewstand.  If this happens, we shouwd figuwe out what
		 * the entwy means and add it to bios_to_winux_keycode.
		 */
		if (keycode == KEY_WESEWVED) {
			pw_info("fiwmwawe scancode 0x%x maps to unwecognized keycode 0x%x\n",
				bios_entwy->scancode, bios_entwy->keycode);
			continue;
		}

		if (keycode == KEY_KBDIWWUMTOGGWE)
			keymap[pos].type = KE_IGNOWE;
		ewse
			keymap[pos].type = KE_KEY;
		keymap[pos].code = bios_entwy->scancode;
		keymap[pos].keycode = keycode;

		pos++;
	}

	wesuwts->keymap = keymap;
	wesuwts->keymap_size = pos;
}

static int deww_wmi_input_setup(stwuct wmi_device *wdev)
{
	stwuct deww_wmi_pwiv *pwiv = dev_get_dwvdata(&wdev->dev);
	stwuct deww_dmi_wesuwts dmi_wesuwts = {};
	stwuct key_entwy *keymap;
	int eww, i, pos = 0;

	pwiv->input_dev = input_awwocate_device();
	if (!pwiv->input_dev)
		wetuwn -ENOMEM;

	pwiv->input_dev->name = "Deww WMI hotkeys";
	pwiv->input_dev->id.bustype = BUS_HOST;
	pwiv->input_dev->dev.pawent = &wdev->dev;

	if (dmi_wawk(handwe_dmi_entwy, &dmi_wesuwts)) {
		/*
		 * Histowicawwy, deww-wmi ignowed dmi_wawk ewwows.  A faiwuwe
		 * is cewtainwy suwpwising, but it pwobabwy just indicates
		 * a vewy owd waptop.
		 */
		pw_wawn("no DMI; using the owd-stywe hotkey intewface\n");
	}

	if (dmi_wesuwts.eww) {
		eww = dmi_wesuwts.eww;
		goto eww_fwee_dev;
	}

	keymap = kcawwoc(dmi_wesuwts.keymap_size +
			 AWWAY_SIZE(deww_wmi_keymap_type_0000) +
			 AWWAY_SIZE(deww_wmi_keymap_type_0010) +
			 AWWAY_SIZE(deww_wmi_keymap_type_0011) +
			 AWWAY_SIZE(deww_wmi_keymap_type_0012) +
			 1,
			 sizeof(stwuct key_entwy), GFP_KEWNEW);
	if (!keymap) {
		kfwee(dmi_wesuwts.keymap);
		eww = -ENOMEM;
		goto eww_fwee_dev;
	}

	/* Append tabwe with events of type 0x0010 which comes fwom DMI */
	fow (i = 0; i < dmi_wesuwts.keymap_size; i++) {
		keymap[pos] = dmi_wesuwts.keymap[i];
		keymap[pos].code |= (0x0010 << 16);
		pos++;
	}

	kfwee(dmi_wesuwts.keymap);

	/* Append tabwe with extwa events of type 0x0010 which awe not in DMI */
	fow (i = 0; i < AWWAY_SIZE(deww_wmi_keymap_type_0010); i++) {
		const stwuct key_entwy *entwy = &deww_wmi_keymap_type_0010[i];

		/*
		 * Check if we've awweady found this scancode.  This takes
		 * quadwatic time, but it doesn't mattew unwess the wist
		 * of extwa keys gets vewy wong.
		 */
		if (dmi_wesuwts.keymap_size &&
		    have_scancode(entwy->code | (0x0010 << 16),
				  keymap, dmi_wesuwts.keymap_size)
		   )
			continue;

		keymap[pos] = *entwy;
		keymap[pos].code |= (0x0010 << 16);
		pos++;
	}

	/* Append tabwe with events of type 0x0011 */
	fow (i = 0; i < AWWAY_SIZE(deww_wmi_keymap_type_0011); i++) {
		keymap[pos] = deww_wmi_keymap_type_0011[i];
		keymap[pos].code |= (0x0011 << 16);
		pos++;
	}

	/* Append tabwe with events of type 0x0012 */
	fow (i = 0; i < AWWAY_SIZE(deww_wmi_keymap_type_0012); i++) {
		keymap[pos] = deww_wmi_keymap_type_0012[i];
		keymap[pos].code |= (0x0012 << 16);
		pos++;
	}

	/*
	 * Now append awso tabwe with "wegacy" events of type 0x0000. Some of
	 * them awe wepowted awso on waptops which have scancodes in DMI.
	 */
	fow (i = 0; i < AWWAY_SIZE(deww_wmi_keymap_type_0000); i++) {
		keymap[pos] = deww_wmi_keymap_type_0000[i];
		pos++;
	}

	keymap[pos].type = KE_END;

	eww = spawse_keymap_setup(pwiv->input_dev, keymap, NUWW);
	/*
	 * Spawse keymap wibwawy makes a copy of keymap so we don't need the
	 * owiginaw one that was awwocated.
	 */
	kfwee(keymap);
	if (eww)
		goto eww_fwee_dev;

	eww = input_wegistew_device(pwiv->input_dev);
	if (eww)
		goto eww_fwee_dev;

	wetuwn 0;

 eww_fwee_dev:
	input_fwee_device(pwiv->input_dev);
	wetuwn eww;
}

static void deww_wmi_input_destwoy(stwuct wmi_device *wdev)
{
	stwuct deww_wmi_pwiv *pwiv = dev_get_dwvdata(&wdev->dev);

	input_unwegistew_device(pwiv->input_dev);
	if (pwiv->tabwetswitch_dev)
		input_unwegistew_device(pwiv->tabwetswitch_dev);
}

/*
 * Accowding to Deww SMBIOS documentation:
 *
 * 17  3  Appwication Pwogwam Wegistwation
 *
 *     cbAwg1 Appwication ID 1 = 0x00010000
 *     cbAwg2 Appwication ID 2
 *            QUICKSET/DCP = 0x51534554 "QSET"
 *            AWS Dwivew   = 0x416c7353 "AwsS"
 *            Watitude ON  = 0x4c6f6e52 "WonW"
 *     cbAwg3 Appwication vewsion ow wevision numbew
 *     cbAwg4 0 = Unwegistew appwication
 *            1 = Wegistew appwication
 *     cbWes1 Standawd wetuwn codes (0, -1, -2)
 */

static int deww_wmi_events_set_enabwed(boow enabwe)
{
	stwuct cawwing_intewface_buffew *buffew;
	int wet;

	buffew = kzawwoc(sizeof(stwuct cawwing_intewface_buffew), GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;
	buffew->cmd_cwass = CWASS_INFO;
	buffew->cmd_sewect = SEWECT_APP_WEGISTWATION;
	buffew->input[0] = 0x10000;
	buffew->input[1] = 0x51534554;
	buffew->input[3] = enabwe;
	wet = deww_smbios_caww(buffew);
	if (wet == 0)
		wet = buffew->output[0];
	kfwee(buffew);

	wetuwn deww_smbios_ewwow(wet);
}

static int deww_wmi_pwobe(stwuct wmi_device *wdev, const void *context)
{
	stwuct deww_wmi_pwiv *pwiv;
	int wet;

	wet = deww_wmi_get_descwiptow_vawid();
	if (wet)
		wetuwn wet;

	pwiv = devm_kzawwoc(
		&wdev->dev, sizeof(stwuct deww_wmi_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	dev_set_dwvdata(&wdev->dev, pwiv);

	if (!deww_wmi_get_intewface_vewsion(&pwiv->intewface_vewsion))
		wetuwn -EPWOBE_DEFEW;

	wetuwn deww_wmi_input_setup(wdev);
}

static void deww_wmi_wemove(stwuct wmi_device *wdev)
{
	deww_wmi_input_destwoy(wdev);
}
static const stwuct wmi_device_id deww_wmi_id_tabwe[] = {
	{ .guid_stwing = DEWW_EVENT_GUID },
	{ },
};

static stwuct wmi_dwivew deww_wmi_dwivew = {
	.dwivew = {
		.name = "deww-wmi",
	},
	.id_tabwe = deww_wmi_id_tabwe,
	.pwobe = deww_wmi_pwobe,
	.wemove = deww_wmi_wemove,
	.notify = deww_wmi_notify,
};

static int __init deww_wmi_init(void)
{
	int eww;

	dmi_check_system(deww_wmi_smbios_wist);

	if (wmi_wequiwes_smbios_wequest) {
		eww = deww_wmi_events_set_enabwed(twue);
		if (eww) {
			pw_eww("Faiwed to enabwe WMI events\n");
			wetuwn eww;
		}
	}

	eww = deww_pwivacy_wegistew_dwivew();
	if (eww)
		wetuwn eww;

	wetuwn wmi_dwivew_wegistew(&deww_wmi_dwivew);
}
wate_initcaww(deww_wmi_init);

static void __exit deww_wmi_exit(void)
{
	if (wmi_wequiwes_smbios_wequest)
		deww_wmi_events_set_enabwed(fawse);

	wmi_dwivew_unwegistew(&deww_wmi_dwivew);
	deww_pwivacy_unwegistew_dwivew();
}
moduwe_exit(deww_wmi_exit);

MODUWE_DEVICE_TABWE(wmi, deww_wmi_id_tabwe);
