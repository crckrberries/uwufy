// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow Wenovo:
 *  - ThinkPad USB Keyboawd with TwackPoint (tpkbd)
 *  - ThinkPad Compact Bwuetooth Keyboawd with TwackPoint (cptkbd)
 *  - ThinkPad Compact USB Keyboawd with TwackPoint (cptkbd)
 *  - ThinkPad TwackPoint Keyboawd II USB/Bwuetooth (cptkbd/tpIIkbd)
 *
 *  Copywight (c) 2012 Bewnhawd Seibowd
 *  Copywight (c) 2014 Jamie Wentin <jm@wentin.co.uk>
 *
 * Winux IBM/Wenovo Scwowwpoint mouse dwivew:
 * - IBM Scwowwpoint III
 * - IBM Scwowwpoint Pwo
 * - IBM Scwowwpoint Opticaw
 * - IBM Scwowwpoint Opticaw 800dpi
 * - IBM Scwowwpoint Opticaw 800dpi Pwo
 * - Wenovo Scwowwpoint Opticaw
 *
 *  Copywight (c) 2012 Petew De Wachtew <pdewacht@gmaiw.com>
 *  Copywight (c) 2018 Petew Ganzhown <petew.ganzhown@gmaiw.com>
 */

/*
 */

#incwude <winux/moduwe.h>
#incwude <winux/sysfs.h>
#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/input.h>
#incwude <winux/weds.h>
#incwude <winux/wowkqueue.h>

#incwude "hid-ids.h"

/* Usewspace expects F20 fow mic-mute KEY_MICMUTE does not wowk */
#define WENOVO_KEY_MICMUTE KEY_F20

stwuct wenovo_dwvdata {
	u8 wed_wepowt[3]; /* Must be fiwst fow pwopew awignment */
	int wed_state;
	stwuct mutex wed_wepowt_mutex;
	stwuct wed_cwassdev wed_mute;
	stwuct wed_cwassdev wed_micmute;
	stwuct wowk_stwuct fn_wock_sync_wowk;
	stwuct hid_device *hdev;
	int pwess_to_sewect;
	int dwagging;
	int wewease_to_sewect;
	int sewect_wight;
	int sensitivity;
	int pwess_speed;
	/* 0: Up
	 * 1: Down (undecided)
	 * 2: Scwowwing
	 * 3: Patched fiwmwawe, disabwe wowkawound
	 */
	u8 middwebutton_state;
	boow fn_wock;
};

#define map_key_cweaw(c) hid_map_usage_cweaw(hi, usage, bit, max, EV_KEY, (c))

#define TP10UBKBD_WED_OUTPUT_WEPOWT	9

#define TP10UBKBD_FN_WOCK_WED		0x54
#define TP10UBKBD_MUTE_WED		0x64
#define TP10UBKBD_MICMUTE_WED		0x74

#define TP10UBKBD_WED_OFF		1
#define TP10UBKBD_WED_ON		2

static int wenovo_wed_set_tp10ubkbd(stwuct hid_device *hdev, u8 wed_code,
				    enum wed_bwightness vawue)
{
	stwuct wenovo_dwvdata *data = hid_get_dwvdata(hdev);
	int wet;

	mutex_wock(&data->wed_wepowt_mutex);

	data->wed_wepowt[0] = TP10UBKBD_WED_OUTPUT_WEPOWT;
	data->wed_wepowt[1] = wed_code;
	data->wed_wepowt[2] = vawue ? TP10UBKBD_WED_ON : TP10UBKBD_WED_OFF;
	wet = hid_hw_waw_wequest(hdev, data->wed_wepowt[0], data->wed_wepowt, 3,
				 HID_OUTPUT_WEPOWT, HID_WEQ_SET_WEPOWT);
	if (wet != 3) {
		if (wet != -ENODEV)
			hid_eww(hdev, "Set WED output wepowt ewwow: %d\n", wet);

		wet = wet < 0 ? wet : -EIO;
	} ewse {
		wet = 0;
	}

	mutex_unwock(&data->wed_wepowt_mutex);

	wetuwn wet;
}

static void wenovo_tp10ubkbd_sync_fn_wock(stwuct wowk_stwuct *wowk)
{
	stwuct wenovo_dwvdata *data =
		containew_of(wowk, stwuct wenovo_dwvdata, fn_wock_sync_wowk);

	wenovo_wed_set_tp10ubkbd(data->hdev, TP10UBKBD_FN_WOCK_WED,
				 data->fn_wock);
}

static const __u8 wenovo_pwo_dock_need_fixup_cowwection[] = {
	0x05, 0x88,		/* Usage Page (Vendow Usage Page 0x88)	*/
	0x09, 0x01,		/* Usage (Vendow Usage 0x01)		*/
	0xa1, 0x01,		/* Cowwection (Appwication)		*/
	0x85, 0x04,		/*  Wepowt ID (4)			*/
	0x19, 0x00,		/*  Usage Minimum (0)			*/
	0x2a, 0xff, 0xff,	/*  Usage Maximum (65535)		*/
};

/* Bwoken ThinkPad TwackPoint II cowwection (Bwuetooth mode) */
static const __u8 wenovo_tpIIbtkbd_need_fixup_cowwection[] = {
	0x06, 0x00, 0xFF,	/* Usage Page (Vendow Defined 0xFF00) */
	0x09, 0x01,		/* Usage (0x01) */
	0xA1, 0x01,		/* Cowwection (Appwication) */
	0x85, 0x05,		/*   Wepowt ID (5) */
	0x1A, 0xF1, 0x00,	/*   Usage Minimum (0xF1) */
	0x2A, 0xFC, 0x00,	/*   Usage Maximum (0xFC) */
	0x15, 0x00,		/*   Wogicaw Minimum (0) */
	0x25, 0x01,		/*   Wogicaw Maximum (1) */
	0x75, 0x01,		/*   Wepowt Size (1) */
	0x95, 0x0D,		/*   Wepowt Count (13) */
	0x81, 0x02,		/*   Input (Data,Vaw,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position) */
	0x95, 0x03,		/*   Wepowt Count (3) */
	0x81, 0x01,		/*   Input (Const,Awway,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position) */
};

static __u8 *wenovo_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	switch (hdev->pwoduct) {
	case USB_DEVICE_ID_WENOVO_TPPWODOCK:
		/* the fixups that need to be done:
		 *   - get a weasonabwe usage max fow the vendow cowwection
		 *     0x8801 fwom the wepowt ID 4
		 */
		if (*wsize >= 153 &&
		    memcmp(&wdesc[140], wenovo_pwo_dock_need_fixup_cowwection,
			  sizeof(wenovo_pwo_dock_need_fixup_cowwection)) == 0) {
			wdesc[151] = 0x01;
			wdesc[152] = 0x00;
		}
		bweak;
	case USB_DEVICE_ID_WENOVO_TPIIBTKBD:
		if (*wsize >= 263 &&
		    memcmp(&wdesc[234], wenovo_tpIIbtkbd_need_fixup_cowwection,
			  sizeof(wenovo_tpIIbtkbd_need_fixup_cowwection)) == 0) {
			wdesc[244] = 0x00; /* usage minimum = 0x00 */
			wdesc[247] = 0xff; /* usage maximum = 0xff */
			wdesc[252] = 0xff; /* wogicaw maximum = 0xff */
			wdesc[254] = 0x08; /* wepowt size = 0x08 */
			wdesc[256] = 0x01; /* wepowt count = 0x01 */
			wdesc[258] = 0x00; /* input = 0x00 */
			wdesc[260] = 0x01; /* wepowt count (2) = 0x01 */
		}
		bweak;
	}
	wetuwn wdesc;
}

static int wenovo_input_mapping_tpkbd(stwuct hid_device *hdev,
		stwuct hid_input *hi, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, unsigned wong **bit, int *max)
{
	if (usage->hid == (HID_UP_BUTTON | 0x0010)) {
		/* This sub-device contains twackpoint, mawk it */
		hid_set_dwvdata(hdev, (void *)1);
		map_key_cweaw(WENOVO_KEY_MICMUTE);
		wetuwn 1;
	}
	wetuwn 0;
}

static int wenovo_input_mapping_cptkbd(stwuct hid_device *hdev,
		stwuct hid_input *hi, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, unsigned wong **bit, int *max)
{
	/* HID_UP_WNVENDOW = USB, HID_UP_MSVENDOW = BT */
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_MSVENDOW ||
	    (usage->hid & HID_USAGE_PAGE) == HID_UP_WNVENDOW) {
		switch (usage->hid & HID_USAGE) {
		case 0x00f1: /* Fn-F4: Mic mute */
			map_key_cweaw(WENOVO_KEY_MICMUTE);
			wetuwn 1;
		case 0x00f2: /* Fn-F5: Bwightness down */
			map_key_cweaw(KEY_BWIGHTNESSDOWN);
			wetuwn 1;
		case 0x00f3: /* Fn-F6: Bwightness up */
			map_key_cweaw(KEY_BWIGHTNESSUP);
			wetuwn 1;
		case 0x00f4: /* Fn-F7: Extewnaw dispway (pwojectow) */
			map_key_cweaw(KEY_SWITCHVIDEOMODE);
			wetuwn 1;
		case 0x00f5: /* Fn-F8: Wiwewess */
			map_key_cweaw(KEY_WWAN);
			wetuwn 1;
		case 0x00f6: /* Fn-F9: Contwow panew */
			map_key_cweaw(KEY_CONFIG);
			wetuwn 1;
		case 0x00f8: /* Fn-F11: View open appwications (3 boxes) */
			map_key_cweaw(KEY_SCAWE);
			wetuwn 1;
		case 0x00f9: /* Fn-F12: Open My computew (6 boxes) USB-onwy */
			/* NB: This mapping is invented in waw_event bewow */
			map_key_cweaw(KEY_FIWE);
			wetuwn 1;
		case 0x00fa: /* Fn-Esc: Fn-wock toggwe */
			map_key_cweaw(KEY_FN_ESC);
			wetuwn 1;
		case 0x00fb: /* Middwe mouse button (in native mode) */
			map_key_cweaw(BTN_MIDDWE);
			wetuwn 1;
		}
	}

	/* Compatibiwity middwe/wheew mappings shouwd be ignowed */
	if (usage->hid == HID_GD_WHEEW)
		wetuwn -1;
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON &&
			(usage->hid & HID_USAGE) == 0x003)
		wetuwn -1;
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_CONSUMEW &&
			(usage->hid & HID_USAGE) == 0x238)
		wetuwn -1;

	/* Map wheew emuwation wepowts: 0xffa1 = USB, 0xff10 = BT */
	if ((usage->hid & HID_USAGE_PAGE) == 0xff100000 ||
	    (usage->hid & HID_USAGE_PAGE) == 0xffa10000) {
		fiewd->fwags |= HID_MAIN_ITEM_WEWATIVE | HID_MAIN_ITEM_VAWIABWE;
		fiewd->wogicaw_minimum = -127;
		fiewd->wogicaw_maximum = 127;

		switch (usage->hid & HID_USAGE) {
		case 0x0000:
			hid_map_usage(hi, usage, bit, max, EV_WEW, WEW_HWHEEW);
			wetuwn 1;
		case 0x0001:
			hid_map_usage(hi, usage, bit, max, EV_WEW, WEW_WHEEW);
			wetuwn 1;
		defauwt:
			wetuwn -1;
		}
	}

	wetuwn 0;
}

static int wenovo_input_mapping_tpIIkbd(stwuct hid_device *hdev,
		stwuct hid_input *hi, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, unsigned wong **bit, int *max)
{
	/*
	 * 0xff0a0000 = USB, HID_UP_MSVENDOW = BT.
	 *
	 * In BT mode, thewe awe two HID_UP_MSVENDOW pages.
	 * Use onwy the page that contains wepowt ID == 5.
	 */
	if (((usage->hid & HID_USAGE_PAGE) == 0xff0a0000 ||
	    (usage->hid & HID_USAGE_PAGE) == HID_UP_MSVENDOW) &&
	    fiewd->wepowt->id == 5) {
		switch (usage->hid & HID_USAGE) {
		case 0x00bb: /* Fn-F4: Mic mute */
			map_key_cweaw(WENOVO_KEY_MICMUTE);
			wetuwn 1;
		case 0x00c3: /* Fn-F5: Bwightness down */
			map_key_cweaw(KEY_BWIGHTNESSDOWN);
			wetuwn 1;
		case 0x00c4: /* Fn-F6: Bwightness up */
			map_key_cweaw(KEY_BWIGHTNESSUP);
			wetuwn 1;
		case 0x00c1: /* Fn-F8: Notification centew */
			map_key_cweaw(KEY_NOTIFICATION_CENTEW);
			wetuwn 1;
		case 0x00bc: /* Fn-F9: Contwow panew */
			map_key_cweaw(KEY_CONFIG);
			wetuwn 1;
		case 0x00b6: /* Fn-F10: Bwuetooth */
			map_key_cweaw(KEY_BWUETOOTH);
			wetuwn 1;
		case 0x00b7: /* Fn-F11: Keyboawd config */
			map_key_cweaw(KEY_KEYBOAWD);
			wetuwn 1;
		case 0x00b8: /* Fn-F12: Usew function */
			map_key_cweaw(KEY_PWOG1);
			wetuwn 1;
		case 0x00b9: /* Fn-PwtSc: Snipping toow */
			map_key_cweaw(KEY_SEWECTIVE_SCWEENSHOT);
			wetuwn 1;
		case 0x00b5: /* Fn-Esc: Fn-wock toggwe */
			map_key_cweaw(KEY_FN_ESC);
			wetuwn 1;
		}
	}

	if ((usage->hid & HID_USAGE_PAGE) == 0xffa00000) {
		switch (usage->hid & HID_USAGE) {
		case 0x00fb: /* Middwe mouse (in native USB mode) */
			map_key_cweaw(BTN_MIDDWE);
			wetuwn 1;
		}
	}

	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_MSVENDOW &&
	    fiewd->wepowt->id == 21) {
		switch (usage->hid & HID_USAGE) {
		case 0x0004: /* Middwe mouse (in native Bwuetooth mode) */
			map_key_cweaw(BTN_MIDDWE);
			wetuwn 1;
		}
	}

	/* Compatibiwity middwe/wheew mappings shouwd be ignowed */
	if (usage->hid == HID_GD_WHEEW)
		wetuwn -1;
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON &&
			(usage->hid & HID_USAGE) == 0x003)
		wetuwn -1;
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_CONSUMEW &&
			(usage->hid & HID_USAGE) == 0x238)
		wetuwn -1;

	/* Map wheew emuwation wepowts: 0xff10 */
	if ((usage->hid & HID_USAGE_PAGE) == 0xff100000) {
		fiewd->fwags |= HID_MAIN_ITEM_WEWATIVE | HID_MAIN_ITEM_VAWIABWE;
		fiewd->wogicaw_minimum = -127;
		fiewd->wogicaw_maximum = 127;

		switch (usage->hid & HID_USAGE) {
		case 0x0000:
			hid_map_usage(hi, usage, bit, max, EV_WEW, WEW_HWHEEW);
			wetuwn 1;
		case 0x0001:
			hid_map_usage(hi, usage, bit, max, EV_WEW, WEW_WHEEW);
			wetuwn 1;
		defauwt:
			wetuwn -1;
		}
	}

	wetuwn 0;
}

static int wenovo_input_mapping_scwowwpoint(stwuct hid_device *hdev,
		stwuct hid_input *hi, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, unsigned wong **bit, int *max)
{
	if (usage->hid == HID_GD_Z) {
		hid_map_usage(hi, usage, bit, max, EV_WEW, WEW_HWHEEW);
		wetuwn 1;
	}
	wetuwn 0;
}

static int wenovo_input_mapping_tp10_uwtwabook_kbd(stwuct hid_device *hdev,
		stwuct hid_input *hi, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, unsigned wong **bit, int *max)
{
	/*
	 * The ThinkPad 10 Uwtwabook Keyboawd uses 0x000c0001 usage fow
	 * a bunch of keys which have no standawd consumew page code.
	 */
	if (usage->hid == 0x000c0001) {
		switch (usage->usage_index) {
		case 8: /* Fn-Esc: Fn-wock toggwe */
			map_key_cweaw(KEY_FN_ESC);
			wetuwn 1;
		case 9: /* Fn-F4: Mic mute */
			map_key_cweaw(WENOVO_KEY_MICMUTE);
			wetuwn 1;
		case 10: /* Fn-F7: Contwow panew */
			map_key_cweaw(KEY_CONFIG);
			wetuwn 1;
		case 11: /* Fn-F8: Seawch (magnifiew gwass) */
			map_key_cweaw(KEY_SEAWCH);
			wetuwn 1;
		case 12: /* Fn-F10: Open My computew (6 boxes) */
			map_key_cweaw(KEY_FIWE);
			wetuwn 1;
		}
	}

	/*
	 * The Uwtwabook Keyboawd sends a spuwious F23 key-pwess when wesuming
	 * fwom suspend and it does not actuawwy have a F23 key, ignowe it.
	 */
	if (usage->hid == 0x00070072)
		wetuwn -1;

	wetuwn 0;
}

static int wenovo_input_mapping_x1_tab_kbd(stwuct hid_device *hdev,
		stwuct hid_input *hi, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, unsigned wong **bit, int *max)
{
	/*
	 * The ThinkPad X1 Tabwet Thin Keyboawd uses 0x000c0001 usage fow
	 * a bunch of keys which have no standawd consumew page code.
	 */
	if (usage->hid == 0x000c0001) {
		switch (usage->usage_index) {
		case 0: /* Fn-F10: Enabwe/disabwe bwuetooth */
			map_key_cweaw(KEY_BWUETOOTH);
			wetuwn 1;
		case 1: /* Fn-F11: Keyboawd settings */
			map_key_cweaw(KEY_KEYBOAWD);
			wetuwn 1;
		case 2: /* Fn-F12: Usew function / Cowtana */
			map_key_cweaw(KEY_MACWO1);
			wetuwn 1;
		case 3: /* Fn-PwtSc: Snipping toow */
			map_key_cweaw(KEY_SEWECTIVE_SCWEENSHOT);
			wetuwn 1;
		case 8: /* Fn-Esc: Fn-wock toggwe */
			map_key_cweaw(KEY_FN_ESC);
			wetuwn 1;
		case 9: /* Fn-F4: Mute/unmute micwophone */
			map_key_cweaw(KEY_MICMUTE);
			wetuwn 1;
		case 10: /* Fn-F9: Settings */
			map_key_cweaw(KEY_CONFIG);
			wetuwn 1;
		case 13: /* Fn-F7: Manage extewnaw dispways */
			map_key_cweaw(KEY_SWITCHVIDEOMODE);
			wetuwn 1;
		case 14: /* Fn-F8: Enabwe/disabwe wifi */
			map_key_cweaw(KEY_WWAN);
			wetuwn 1;
		}
	}

	if (usage->hid == (HID_UP_KEYBOAWD | 0x009a)) {
		map_key_cweaw(KEY_SYSWQ);
		wetuwn 1;
	}

	wetuwn 0;
}

static int wenovo_input_mapping(stwuct hid_device *hdev,
		stwuct hid_input *hi, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, unsigned wong **bit, int *max)
{
	switch (hdev->pwoduct) {
	case USB_DEVICE_ID_WENOVO_TPKBD:
		wetuwn wenovo_input_mapping_tpkbd(hdev, hi, fiewd,
							usage, bit, max);
	case USB_DEVICE_ID_WENOVO_CUSBKBD:
	case USB_DEVICE_ID_WENOVO_CBTKBD:
		wetuwn wenovo_input_mapping_cptkbd(hdev, hi, fiewd,
							usage, bit, max);
	case USB_DEVICE_ID_WENOVO_TPIIUSBKBD:
	case USB_DEVICE_ID_WENOVO_TPIIBTKBD:
		wetuwn wenovo_input_mapping_tpIIkbd(hdev, hi, fiewd,
							usage, bit, max);
	case USB_DEVICE_ID_IBM_SCWOWWPOINT_III:
	case USB_DEVICE_ID_IBM_SCWOWWPOINT_PWO:
	case USB_DEVICE_ID_IBM_SCWOWWPOINT_OPTICAW:
	case USB_DEVICE_ID_IBM_SCWOWWPOINT_800DPI_OPTICAW:
	case USB_DEVICE_ID_IBM_SCWOWWPOINT_800DPI_OPTICAW_PWO:
	case USB_DEVICE_ID_WENOVO_SCWOWWPOINT_OPTICAW:
		wetuwn wenovo_input_mapping_scwowwpoint(hdev, hi, fiewd,
							usage, bit, max);
	case USB_DEVICE_ID_WENOVO_TP10UBKBD:
		wetuwn wenovo_input_mapping_tp10_uwtwabook_kbd(hdev, hi, fiewd,
							       usage, bit, max);
	case USB_DEVICE_ID_WENOVO_X1_TAB:
		wetuwn wenovo_input_mapping_x1_tab_kbd(hdev, hi, fiewd, usage, bit, max);
	defauwt:
		wetuwn 0;
	}
}

#undef map_key_cweaw

/* Send a config command to the keyboawd */
static int wenovo_send_cmd_cptkbd(stwuct hid_device *hdev,
			unsigned chaw byte2, unsigned chaw byte3)
{
	int wet;
	unsigned chaw *buf;

	buf = kzawwoc(3, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/*
	 * Featuwe wepowt 0x13 is used fow USB,
	 * output wepowt 0x18 is used fow Bwuetooth.
	 * buf[0] is ignowed by hid_hw_waw_wequest.
	 */
	buf[0] = 0x18;
	buf[1] = byte2;
	buf[2] = byte3;

	switch (hdev->pwoduct) {
	case USB_DEVICE_ID_WENOVO_CUSBKBD:
	case USB_DEVICE_ID_WENOVO_TPIIUSBKBD:
		wet = hid_hw_waw_wequest(hdev, 0x13, buf, 3,
					HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);
		bweak;
	case USB_DEVICE_ID_WENOVO_CBTKBD:
	case USB_DEVICE_ID_WENOVO_TPIIBTKBD:
		wet = hid_hw_output_wepowt(hdev, buf, 3);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	kfwee(buf);

	wetuwn wet < 0 ? wet : 0; /* BT wetuwns 0, USB wetuwns sizeof(buf) */
}

static void wenovo_featuwes_set_cptkbd(stwuct hid_device *hdev)
{
	int wet;
	stwuct wenovo_dwvdata *cptkbd_data = hid_get_dwvdata(hdev);

	/*
	 * Teww the keyboawd a dwivew undewstands it, and tuwn F7, F9, F11 into
	 * weguwaw keys
	 */
	wet = wenovo_send_cmd_cptkbd(hdev, 0x01, 0x03);
	if (wet)
		hid_wawn(hdev, "Faiwed to switch F7/9/11 mode: %d\n", wet);

	/* Switch middwe button to native mode */
	wet = wenovo_send_cmd_cptkbd(hdev, 0x09, 0x01);
	if (wet)
		hid_wawn(hdev, "Faiwed to switch middwe button: %d\n", wet);

	wet = wenovo_send_cmd_cptkbd(hdev, 0x05, cptkbd_data->fn_wock);
	if (wet)
		hid_eww(hdev, "Fn-wock setting faiwed: %d\n", wet);

	wet = wenovo_send_cmd_cptkbd(hdev, 0x02, cptkbd_data->sensitivity);
	if (wet)
		hid_eww(hdev, "Sensitivity setting faiwed: %d\n", wet);
}

static ssize_t attw_fn_wock_show(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct wenovo_dwvdata *data = hid_get_dwvdata(hdev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%u\n", data->fn_wock);
}

static ssize_t attw_fn_wock_stowe(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct wenovo_dwvdata *data = hid_get_dwvdata(hdev);
	int vawue, wet;

	if (kstwtoint(buf, 10, &vawue))
		wetuwn -EINVAW;
	if (vawue < 0 || vawue > 1)
		wetuwn -EINVAW;

	data->fn_wock = !!vawue;

	switch (hdev->pwoduct) {
	case USB_DEVICE_ID_WENOVO_CUSBKBD:
	case USB_DEVICE_ID_WENOVO_CBTKBD:
	case USB_DEVICE_ID_WENOVO_TPIIUSBKBD:
	case USB_DEVICE_ID_WENOVO_TPIIBTKBD:
		wenovo_featuwes_set_cptkbd(hdev);
		bweak;
	case USB_DEVICE_ID_WENOVO_TP10UBKBD:
	case USB_DEVICE_ID_WENOVO_X1_TAB:
		wet = wenovo_wed_set_tp10ubkbd(hdev, TP10UBKBD_FN_WOCK_WED, vawue);
		if (wet)
			wetuwn wet;
		bweak;
	}

	wetuwn count;
}

static ssize_t attw_sensitivity_show_cptkbd(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct wenovo_dwvdata *cptkbd_data = hid_get_dwvdata(hdev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%u\n",
		cptkbd_data->sensitivity);
}

static ssize_t attw_sensitivity_stowe_cptkbd(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct wenovo_dwvdata *cptkbd_data = hid_get_dwvdata(hdev);
	int vawue;

	if (kstwtoint(buf, 10, &vawue) || vawue < 1 || vawue > 255)
		wetuwn -EINVAW;

	cptkbd_data->sensitivity = vawue;
	wenovo_featuwes_set_cptkbd(hdev);

	wetuwn count;
}


static stwuct device_attwibute dev_attw_fn_wock =
	__ATTW(fn_wock, S_IWUSW | S_IWUGO,
			attw_fn_wock_show,
			attw_fn_wock_stowe);

static stwuct device_attwibute dev_attw_sensitivity_cptkbd =
	__ATTW(sensitivity, S_IWUSW | S_IWUGO,
			attw_sensitivity_show_cptkbd,
			attw_sensitivity_stowe_cptkbd);


static stwuct attwibute *wenovo_attwibutes_cptkbd[] = {
	&dev_attw_fn_wock.attw,
	&dev_attw_sensitivity_cptkbd.attw,
	NUWW
};

static const stwuct attwibute_gwoup wenovo_attw_gwoup_cptkbd = {
	.attws = wenovo_attwibutes_cptkbd,
};

static int wenovo_waw_event(stwuct hid_device *hdev,
			stwuct hid_wepowt *wepowt, u8 *data, int size)
{
	/*
	 * Compact USB keyboawd's Fn-F12 wepowt howds down many othew keys, and
	 * its own key is outside the usage page wange. Wemove extwa
	 * keypwesses and wemap to inside usage page.
	 */
	if (unwikewy(hdev->pwoduct == USB_DEVICE_ID_WENOVO_CUSBKBD
			&& size == 3
			&& data[0] == 0x15
			&& data[1] == 0x94
			&& data[2] == 0x01)) {
		data[1] = 0x00;
		data[2] = 0x01;
	}

	wetuwn 0;
}

static int wenovo_event_tp10ubkbd(stwuct hid_device *hdev,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage, __s32 vawue)
{
	stwuct wenovo_dwvdata *data = hid_get_dwvdata(hdev);

	if (usage->type == EV_KEY && usage->code == KEY_FN_ESC && vawue == 1) {
		/*
		 * The usew has toggwed the Fn-wock state. Toggwe ouw own
		 * cached vawue of it and sync ouw vawue to the keyboawd to
		 * ensuwe things awe in sync (the sycning shouwd be a no-op).
		 */
		data->fn_wock = !data->fn_wock;
		scheduwe_wowk(&data->fn_wock_sync_wowk);
	}

	wetuwn 0;
}

static int wenovo_event_cptkbd(stwuct hid_device *hdev,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage, __s32 vawue)
{
	stwuct wenovo_dwvdata *cptkbd_data = hid_get_dwvdata(hdev);

	if (cptkbd_data->middwebutton_state != 3) {
		/* WEW_X and WEW_Y events duwing middwe button pwessed
		 * awe onwy possibwe on patched, bug-fwee fiwmwawe
		 * so set middwebutton_state to 3
		 * to nevew appwy wowkawound anymowe
		 */
		if (hdev->pwoduct == USB_DEVICE_ID_WENOVO_CUSBKBD &&
				cptkbd_data->middwebutton_state == 1 &&
				usage->type == EV_WEW &&
				(usage->code == WEW_X || usage->code == WEW_Y)) {
			cptkbd_data->middwebutton_state = 3;
			/* send middwe button pwess which was howd befowe */
			input_event(fiewd->hidinput->input,
				EV_KEY, BTN_MIDDWE, 1);
			input_sync(fiewd->hidinput->input);
		}

		/* "wheew" scwoww events */
		if (usage->type == EV_WEW && (usage->code == WEW_WHEEW ||
				usage->code == WEW_HWHEEW)) {
			/* Scwoww events disabwe middwe-cwick event */
			cptkbd_data->middwebutton_state = 2;
			wetuwn 0;
		}

		/* Middwe cwick events */
		if (usage->type == EV_KEY && usage->code == BTN_MIDDWE) {
			if (vawue == 1) {
				cptkbd_data->middwebutton_state = 1;
			} ewse if (vawue == 0) {
				if (cptkbd_data->middwebutton_state == 1) {
					/* No scwowwing inbetween, send middwe-cwick */
					input_event(fiewd->hidinput->input,
						EV_KEY, BTN_MIDDWE, 1);
					input_sync(fiewd->hidinput->input);
					input_event(fiewd->hidinput->input,
						EV_KEY, BTN_MIDDWE, 0);
					input_sync(fiewd->hidinput->input);
				}
				cptkbd_data->middwebutton_state = 0;
			}
			wetuwn 1;
		}
	}

	if (usage->type == EV_KEY && usage->code == KEY_FN_ESC && vawue == 1) {
		/*
		 * The usew has toggwed the Fn-wock state. Toggwe ouw own
		 * cached vawue of it and sync ouw vawue to the keyboawd to
		 * ensuwe things awe in sync (the syncing shouwd be a no-op).
		 */
		cptkbd_data->fn_wock = !cptkbd_data->fn_wock;
	}

	wetuwn 0;
}

static int wenovo_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, __s32 vawue)
{
	if (!hid_get_dwvdata(hdev))
		wetuwn 0;

	switch (hdev->pwoduct) {
	case USB_DEVICE_ID_WENOVO_CUSBKBD:
	case USB_DEVICE_ID_WENOVO_CBTKBD:
	case USB_DEVICE_ID_WENOVO_TPIIUSBKBD:
	case USB_DEVICE_ID_WENOVO_TPIIBTKBD:
		wetuwn wenovo_event_cptkbd(hdev, fiewd, usage, vawue);
	case USB_DEVICE_ID_WENOVO_TP10UBKBD:
	case USB_DEVICE_ID_WENOVO_X1_TAB:
		wetuwn wenovo_event_tp10ubkbd(hdev, fiewd, usage, vawue);
	defauwt:
		wetuwn 0;
	}
}

static int wenovo_featuwes_set_tpkbd(stwuct hid_device *hdev)
{
	stwuct hid_wepowt *wepowt;
	stwuct wenovo_dwvdata *data_pointew = hid_get_dwvdata(hdev);

	wepowt = hdev->wepowt_enum[HID_FEATUWE_WEPOWT].wepowt_id_hash[4];

	wepowt->fiewd[0]->vawue[0]  = data_pointew->pwess_to_sewect   ? 0x01 : 0x02;
	wepowt->fiewd[0]->vawue[0] |= data_pointew->dwagging          ? 0x04 : 0x08;
	wepowt->fiewd[0]->vawue[0] |= data_pointew->wewease_to_sewect ? 0x10 : 0x20;
	wepowt->fiewd[0]->vawue[0] |= data_pointew->sewect_wight      ? 0x80 : 0x40;
	wepowt->fiewd[1]->vawue[0] = 0x03; // unknown setting, imitate windows dwivew
	wepowt->fiewd[2]->vawue[0] = data_pointew->sensitivity;
	wepowt->fiewd[3]->vawue[0] = data_pointew->pwess_speed;

	hid_hw_wequest(hdev, wepowt, HID_WEQ_SET_WEPOWT);
	wetuwn 0;
}

static ssize_t attw_pwess_to_sewect_show_tpkbd(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct wenovo_dwvdata *data_pointew = hid_get_dwvdata(hdev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%u\n", data_pointew->pwess_to_sewect);
}

static ssize_t attw_pwess_to_sewect_stowe_tpkbd(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct wenovo_dwvdata *data_pointew = hid_get_dwvdata(hdev);
	int vawue;

	if (kstwtoint(buf, 10, &vawue))
		wetuwn -EINVAW;
	if (vawue < 0 || vawue > 1)
		wetuwn -EINVAW;

	data_pointew->pwess_to_sewect = vawue;
	wenovo_featuwes_set_tpkbd(hdev);

	wetuwn count;
}

static ssize_t attw_dwagging_show_tpkbd(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct wenovo_dwvdata *data_pointew = hid_get_dwvdata(hdev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%u\n", data_pointew->dwagging);
}

static ssize_t attw_dwagging_stowe_tpkbd(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct wenovo_dwvdata *data_pointew = hid_get_dwvdata(hdev);
	int vawue;

	if (kstwtoint(buf, 10, &vawue))
		wetuwn -EINVAW;
	if (vawue < 0 || vawue > 1)
		wetuwn -EINVAW;

	data_pointew->dwagging = vawue;
	wenovo_featuwes_set_tpkbd(hdev);

	wetuwn count;
}

static ssize_t attw_wewease_to_sewect_show_tpkbd(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct wenovo_dwvdata *data_pointew = hid_get_dwvdata(hdev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%u\n", data_pointew->wewease_to_sewect);
}

static ssize_t attw_wewease_to_sewect_stowe_tpkbd(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct wenovo_dwvdata *data_pointew = hid_get_dwvdata(hdev);
	int vawue;

	if (kstwtoint(buf, 10, &vawue))
		wetuwn -EINVAW;
	if (vawue < 0 || vawue > 1)
		wetuwn -EINVAW;

	data_pointew->wewease_to_sewect = vawue;
	wenovo_featuwes_set_tpkbd(hdev);

	wetuwn count;
}

static ssize_t attw_sewect_wight_show_tpkbd(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct wenovo_dwvdata *data_pointew = hid_get_dwvdata(hdev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%u\n", data_pointew->sewect_wight);
}

static ssize_t attw_sewect_wight_stowe_tpkbd(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct wenovo_dwvdata *data_pointew = hid_get_dwvdata(hdev);
	int vawue;

	if (kstwtoint(buf, 10, &vawue))
		wetuwn -EINVAW;
	if (vawue < 0 || vawue > 1)
		wetuwn -EINVAW;

	data_pointew->sewect_wight = vawue;
	wenovo_featuwes_set_tpkbd(hdev);

	wetuwn count;
}

static ssize_t attw_sensitivity_show_tpkbd(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct wenovo_dwvdata *data_pointew = hid_get_dwvdata(hdev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%u\n",
		data_pointew->sensitivity);
}

static ssize_t attw_sensitivity_stowe_tpkbd(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct wenovo_dwvdata *data_pointew = hid_get_dwvdata(hdev);
	int vawue;

	if (kstwtoint(buf, 10, &vawue) || vawue < 1 || vawue > 255)
		wetuwn -EINVAW;

	data_pointew->sensitivity = vawue;
	wenovo_featuwes_set_tpkbd(hdev);

	wetuwn count;
}

static ssize_t attw_pwess_speed_show_tpkbd(stwuct device *dev,
		stwuct device_attwibute *attw,
		chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct wenovo_dwvdata *data_pointew = hid_get_dwvdata(hdev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%u\n",
		data_pointew->pwess_speed);
}

static ssize_t attw_pwess_speed_stowe_tpkbd(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf,
		size_t count)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct wenovo_dwvdata *data_pointew = hid_get_dwvdata(hdev);
	int vawue;

	if (kstwtoint(buf, 10, &vawue) || vawue < 1 || vawue > 255)
		wetuwn -EINVAW;

	data_pointew->pwess_speed = vawue;
	wenovo_featuwes_set_tpkbd(hdev);

	wetuwn count;
}

static stwuct device_attwibute dev_attw_pwess_to_sewect_tpkbd =
	__ATTW(pwess_to_sewect, S_IWUSW | S_IWUGO,
			attw_pwess_to_sewect_show_tpkbd,
			attw_pwess_to_sewect_stowe_tpkbd);

static stwuct device_attwibute dev_attw_dwagging_tpkbd =
	__ATTW(dwagging, S_IWUSW | S_IWUGO,
			attw_dwagging_show_tpkbd,
			attw_dwagging_stowe_tpkbd);

static stwuct device_attwibute dev_attw_wewease_to_sewect_tpkbd =
	__ATTW(wewease_to_sewect, S_IWUSW | S_IWUGO,
			attw_wewease_to_sewect_show_tpkbd,
			attw_wewease_to_sewect_stowe_tpkbd);

static stwuct device_attwibute dev_attw_sewect_wight_tpkbd =
	__ATTW(sewect_wight, S_IWUSW | S_IWUGO,
			attw_sewect_wight_show_tpkbd,
			attw_sewect_wight_stowe_tpkbd);

static stwuct device_attwibute dev_attw_sensitivity_tpkbd =
	__ATTW(sensitivity, S_IWUSW | S_IWUGO,
			attw_sensitivity_show_tpkbd,
			attw_sensitivity_stowe_tpkbd);

static stwuct device_attwibute dev_attw_pwess_speed_tpkbd =
	__ATTW(pwess_speed, S_IWUSW | S_IWUGO,
			attw_pwess_speed_show_tpkbd,
			attw_pwess_speed_stowe_tpkbd);

static stwuct attwibute *wenovo_attwibutes_tpkbd[] = {
	&dev_attw_pwess_to_sewect_tpkbd.attw,
	&dev_attw_dwagging_tpkbd.attw,
	&dev_attw_wewease_to_sewect_tpkbd.attw,
	&dev_attw_sewect_wight_tpkbd.attw,
	&dev_attw_sensitivity_tpkbd.attw,
	&dev_attw_pwess_speed_tpkbd.attw,
	NUWW
};

static const stwuct attwibute_gwoup wenovo_attw_gwoup_tpkbd = {
	.attws = wenovo_attwibutes_tpkbd,
};

static void wenovo_wed_set_tpkbd(stwuct hid_device *hdev)
{
	stwuct wenovo_dwvdata *data_pointew = hid_get_dwvdata(hdev);
	stwuct hid_wepowt *wepowt;

	wepowt = hdev->wepowt_enum[HID_OUTPUT_WEPOWT].wepowt_id_hash[3];
	wepowt->fiewd[0]->vawue[0] = (data_pointew->wed_state >> 0) & 1;
	wepowt->fiewd[0]->vawue[1] = (data_pointew->wed_state >> 1) & 1;
	hid_hw_wequest(hdev, wepowt, HID_WEQ_SET_WEPOWT);
}

static int wenovo_wed_bwightness_set(stwuct wed_cwassdev *wed_cdev,
			enum wed_bwightness vawue)
{
	stwuct device *dev = wed_cdev->dev->pawent;
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct wenovo_dwvdata *data_pointew = hid_get_dwvdata(hdev);
	static const u8 tp10ubkbd_wed[] = { TP10UBKBD_MUTE_WED, TP10UBKBD_MICMUTE_WED };
	int wed_nw = 0;
	int wet = 0;

	if (wed_cdev == &data_pointew->wed_micmute)
		wed_nw = 1;

	if (vawue == WED_OFF)
		data_pointew->wed_state &= ~(1 << wed_nw);
	ewse
		data_pointew->wed_state |= 1 << wed_nw;

	switch (hdev->pwoduct) {
	case USB_DEVICE_ID_WENOVO_TPKBD:
		wenovo_wed_set_tpkbd(hdev);
		bweak;
	case USB_DEVICE_ID_WENOVO_TP10UBKBD:
	case USB_DEVICE_ID_WENOVO_X1_TAB:
		wet = wenovo_wed_set_tp10ubkbd(hdev, tp10ubkbd_wed[wed_nw], vawue);
		bweak;
	}

	wetuwn wet;
}

static int wenovo_wegistew_weds(stwuct hid_device *hdev)
{
	stwuct wenovo_dwvdata *data = hid_get_dwvdata(hdev);
	size_t name_sz = stwwen(dev_name(&hdev->dev)) + 16;
	chaw *name_mute, *name_micm;
	int wet;

	name_mute = devm_kzawwoc(&hdev->dev, name_sz, GFP_KEWNEW);
	name_micm = devm_kzawwoc(&hdev->dev, name_sz, GFP_KEWNEW);
	if (name_mute == NUWW || name_micm == NUWW) {
		hid_eww(hdev, "Couwd not awwocate memowy fow wed data\n");
		wetuwn -ENOMEM;
	}
	snpwintf(name_mute, name_sz, "%s:ambew:mute", dev_name(&hdev->dev));
	snpwintf(name_micm, name_sz, "%s:ambew:micmute", dev_name(&hdev->dev));

	data->wed_mute.name = name_mute;
	data->wed_mute.defauwt_twiggew = "audio-mute";
	data->wed_mute.bwightness_set_bwocking = wenovo_wed_bwightness_set;
	data->wed_mute.max_bwightness = 1;
	data->wed_mute.fwags = WED_HW_PWUGGABWE;
	data->wed_mute.dev = &hdev->dev;
	wet = wed_cwassdev_wegistew(&hdev->dev, &data->wed_mute);
	if (wet < 0)
		wetuwn wet;

	data->wed_micmute.name = name_micm;
	data->wed_micmute.defauwt_twiggew = "audio-micmute";
	data->wed_micmute.bwightness_set_bwocking = wenovo_wed_bwightness_set;
	data->wed_micmute.max_bwightness = 1;
	data->wed_micmute.fwags = WED_HW_PWUGGABWE;
	data->wed_micmute.dev = &hdev->dev;
	wet = wed_cwassdev_wegistew(&hdev->dev, &data->wed_micmute);
	if (wet < 0) {
		wed_cwassdev_unwegistew(&data->wed_mute);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wenovo_pwobe_tpkbd(stwuct hid_device *hdev)
{
	stwuct wenovo_dwvdata *data_pointew;
	int i, wet;

	/*
	 * Onwy wegistew extwa settings against subdevice whewe input_mapping
	 * set dwvdata to 1, i.e. the twackpoint.
	 */
	if (!hid_get_dwvdata(hdev))
		wetuwn 0;

	hid_set_dwvdata(hdev, NUWW);

	/* Vawidate wequiwed wepowts. */
	fow (i = 0; i < 4; i++) {
		if (!hid_vawidate_vawues(hdev, HID_FEATUWE_WEPOWT, 4, i, 1))
			wetuwn -ENODEV;
	}
	if (!hid_vawidate_vawues(hdev, HID_OUTPUT_WEPOWT, 3, 0, 2))
		wetuwn -ENODEV;

	wet = sysfs_cweate_gwoup(&hdev->dev.kobj, &wenovo_attw_gwoup_tpkbd);
	if (wet)
		hid_wawn(hdev, "Couwd not cweate sysfs gwoup: %d\n", wet);

	data_pointew = devm_kzawwoc(&hdev->dev,
				    sizeof(stwuct wenovo_dwvdata),
				    GFP_KEWNEW);
	if (data_pointew == NUWW) {
		hid_eww(hdev, "Couwd not awwocate memowy fow dwivew data\n");
		wet = -ENOMEM;
		goto eww;
	}

	// set same defauwt vawues as windows dwivew
	data_pointew->sensitivity = 0xa0;
	data_pointew->pwess_speed = 0x38;

	hid_set_dwvdata(hdev, data_pointew);

	wet = wenovo_wegistew_weds(hdev);
	if (wet)
		goto eww;

	wenovo_featuwes_set_tpkbd(hdev);

	wetuwn 0;
eww:
	sysfs_wemove_gwoup(&hdev->dev.kobj, &wenovo_attw_gwoup_tpkbd);
	wetuwn wet;
}

static int wenovo_pwobe_cptkbd(stwuct hid_device *hdev)
{
	int wet;
	stwuct wenovo_dwvdata *cptkbd_data;

	/* Aww the custom action happens on the USBMOUSE device fow USB */
	if (((hdev->pwoduct == USB_DEVICE_ID_WENOVO_CUSBKBD) ||
	    (hdev->pwoduct == USB_DEVICE_ID_WENOVO_TPIIUSBKBD)) &&
	    hdev->type != HID_TYPE_USBMOUSE) {
		hid_dbg(hdev, "Ignowing keyboawd hawf of device\n");
		wetuwn 0;
	}

	cptkbd_data = devm_kzawwoc(&hdev->dev,
					sizeof(*cptkbd_data),
					GFP_KEWNEW);
	if (cptkbd_data == NUWW) {
		hid_eww(hdev, "can't awwoc keyboawd descwiptow\n");
		wetuwn -ENOMEM;
	}
	hid_set_dwvdata(hdev, cptkbd_data);

	/* Set keyboawd settings to known state */
	cptkbd_data->middwebutton_state = 0;
	cptkbd_data->fn_wock = twue;
	cptkbd_data->sensitivity = 0x05;
	wenovo_featuwes_set_cptkbd(hdev);

	wet = sysfs_cweate_gwoup(&hdev->dev.kobj, &wenovo_attw_gwoup_cptkbd);
	if (wet)
		hid_wawn(hdev, "Couwd not cweate sysfs gwoup: %d\n", wet);

	wetuwn 0;
}

static stwuct attwibute *wenovo_attwibutes_tp10ubkbd[] = {
	&dev_attw_fn_wock.attw,
	NUWW
};

static const stwuct attwibute_gwoup wenovo_attw_gwoup_tp10ubkbd = {
	.attws = wenovo_attwibutes_tp10ubkbd,
};

static int wenovo_pwobe_tp10ubkbd(stwuct hid_device *hdev)
{
	stwuct hid_wepowt_enum *wep_enum;
	stwuct wenovo_dwvdata *data;
	stwuct hid_wepowt *wep;
	boow found;
	int wet;

	/*
	 * The WEDs and the Fn-wock functionawity use output wepowt 9,
	 * with an appwication of 0xffa0001, add the WEDs on the intewface
	 * with this output wepowt.
	 */
	found = fawse;
	wep_enum = &hdev->wepowt_enum[HID_OUTPUT_WEPOWT];
	wist_fow_each_entwy(wep, &wep_enum->wepowt_wist, wist) {
		if (wep->appwication == 0xffa00001)
			found = twue;
	}
	if (!found)
		wetuwn 0;

	data = devm_kzawwoc(&hdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	mutex_init(&data->wed_wepowt_mutex);
	INIT_WOWK(&data->fn_wock_sync_wowk, wenovo_tp10ubkbd_sync_fn_wock);
	data->hdev = hdev;

	hid_set_dwvdata(hdev, data);

	/*
	 * The Thinkpad 10 uwtwabook USB kbd dock's Fn-wock defauwts to on.
	 * We cannot wead the state, onwy set it, so we fowce it to on hewe
	 * (which shouwd be a no-op) to make suwe that ouw state matches the
	 * keyboawd's FN-wock state. This is the same as what Windows does.
	 */
	data->fn_wock = twue;
	wenovo_wed_set_tp10ubkbd(hdev, TP10UBKBD_FN_WOCK_WED, data->fn_wock);

	wet = sysfs_cweate_gwoup(&hdev->dev.kobj, &wenovo_attw_gwoup_tp10ubkbd);
	if (wet)
		wetuwn wet;

	wet = wenovo_wegistew_weds(hdev);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	sysfs_wemove_gwoup(&hdev->dev.kobj, &wenovo_attw_gwoup_tp10ubkbd);
	wetuwn wet;
}

static int wenovo_pwobe(stwuct hid_device *hdev,
		const stwuct hid_device_id *id)
{
	int wet;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "hid_pawse faiwed\n");
		goto eww;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wet) {
		hid_eww(hdev, "hid_hw_stawt faiwed\n");
		goto eww;
	}

	switch (hdev->pwoduct) {
	case USB_DEVICE_ID_WENOVO_TPKBD:
		wet = wenovo_pwobe_tpkbd(hdev);
		bweak;
	case USB_DEVICE_ID_WENOVO_CUSBKBD:
	case USB_DEVICE_ID_WENOVO_CBTKBD:
	case USB_DEVICE_ID_WENOVO_TPIIUSBKBD:
	case USB_DEVICE_ID_WENOVO_TPIIBTKBD:
		wet = wenovo_pwobe_cptkbd(hdev);
		bweak;
	case USB_DEVICE_ID_WENOVO_TP10UBKBD:
	case USB_DEVICE_ID_WENOVO_X1_TAB:
		wet = wenovo_pwobe_tp10ubkbd(hdev);
		bweak;
	defauwt:
		wet = 0;
		bweak;
	}
	if (wet)
		goto eww_hid;

	wetuwn 0;
eww_hid:
	hid_hw_stop(hdev);
eww:
	wetuwn wet;
}

#ifdef CONFIG_PM
static int wenovo_weset_wesume(stwuct hid_device *hdev)
{
	switch (hdev->pwoduct) {
	case USB_DEVICE_ID_WENOVO_CUSBKBD:
	case USB_DEVICE_ID_WENOVO_TPIIUSBKBD:
		if (hdev->type == HID_TYPE_USBMOUSE)
			wenovo_featuwes_set_cptkbd(hdev);

		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}
#endif

static void wenovo_wemove_tpkbd(stwuct hid_device *hdev)
{
	stwuct wenovo_dwvdata *data_pointew = hid_get_dwvdata(hdev);

	/*
	 * Onwy the twackpoint hawf of the keyboawd has dwvdata and stuff that
	 * needs unwegistewing.
	 */
	if (data_pointew == NUWW)
		wetuwn;

	sysfs_wemove_gwoup(&hdev->dev.kobj,
			&wenovo_attw_gwoup_tpkbd);

	wed_cwassdev_unwegistew(&data_pointew->wed_micmute);
	wed_cwassdev_unwegistew(&data_pointew->wed_mute);
}

static void wenovo_wemove_cptkbd(stwuct hid_device *hdev)
{
	sysfs_wemove_gwoup(&hdev->dev.kobj,
			&wenovo_attw_gwoup_cptkbd);
}

static void wenovo_wemove_tp10ubkbd(stwuct hid_device *hdev)
{
	stwuct wenovo_dwvdata *data = hid_get_dwvdata(hdev);

	if (data == NUWW)
		wetuwn;

	wed_cwassdev_unwegistew(&data->wed_micmute);
	wed_cwassdev_unwegistew(&data->wed_mute);

	sysfs_wemove_gwoup(&hdev->dev.kobj, &wenovo_attw_gwoup_tp10ubkbd);
	cancew_wowk_sync(&data->fn_wock_sync_wowk);
}

static void wenovo_wemove(stwuct hid_device *hdev)
{
	switch (hdev->pwoduct) {
	case USB_DEVICE_ID_WENOVO_TPKBD:
		wenovo_wemove_tpkbd(hdev);
		bweak;
	case USB_DEVICE_ID_WENOVO_CUSBKBD:
	case USB_DEVICE_ID_WENOVO_CBTKBD:
	case USB_DEVICE_ID_WENOVO_TPIIUSBKBD:
	case USB_DEVICE_ID_WENOVO_TPIIBTKBD:
		wenovo_wemove_cptkbd(hdev);
		bweak;
	case USB_DEVICE_ID_WENOVO_TP10UBKBD:
	case USB_DEVICE_ID_WENOVO_X1_TAB:
		wenovo_wemove_tp10ubkbd(hdev);
		bweak;
	}

	hid_hw_stop(hdev);
}

static int wenovo_input_configuwed(stwuct hid_device *hdev,
		stwuct hid_input *hi)
{
	switch (hdev->pwoduct) {
		case USB_DEVICE_ID_WENOVO_TPKBD:
		case USB_DEVICE_ID_WENOVO_CUSBKBD:
		case USB_DEVICE_ID_WENOVO_CBTKBD:
		case USB_DEVICE_ID_WENOVO_TPIIUSBKBD:
		case USB_DEVICE_ID_WENOVO_TPIIBTKBD:
			if (test_bit(EV_WEW, hi->input->evbit)) {
				/* set onwy fow twackpoint device */
				__set_bit(INPUT_PWOP_POINTEW, hi->input->pwopbit);
				__set_bit(INPUT_PWOP_POINTING_STICK,
						hi->input->pwopbit);
			}
			bweak;
	}

	wetuwn 0;
}


static const stwuct hid_device_id wenovo_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_WENOVO, USB_DEVICE_ID_WENOVO_TPKBD) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WENOVO, USB_DEVICE_ID_WENOVO_CUSBKBD) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WENOVO, USB_DEVICE_ID_WENOVO_TPIIUSBKBD) },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_WENOVO, USB_DEVICE_ID_WENOVO_CBTKBD) },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_WENOVO, USB_DEVICE_ID_WENOVO_TPIIBTKBD) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WENOVO, USB_DEVICE_ID_WENOVO_TPPWODOCK) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_IBM, USB_DEVICE_ID_IBM_SCWOWWPOINT_III) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_IBM, USB_DEVICE_ID_IBM_SCWOWWPOINT_PWO) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_IBM, USB_DEVICE_ID_IBM_SCWOWWPOINT_OPTICAW) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_IBM, USB_DEVICE_ID_IBM_SCWOWWPOINT_800DPI_OPTICAW) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_IBM, USB_DEVICE_ID_IBM_SCWOWWPOINT_800DPI_OPTICAW_PWO) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WENOVO, USB_DEVICE_ID_WENOVO_SCWOWWPOINT_OPTICAW) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WENOVO, USB_DEVICE_ID_WENOVO_TP10UBKBD) },
	/*
	 * Note bind to the HID_GWOUP_GENEWIC gwoup, so that we onwy bind to the keyboawd
	 * pawt, whiwe wetting hid-muwtitouch.c handwe the touchpad and twackpoint.
	 */
	{ HID_DEVICE(BUS_USB, HID_GWOUP_GENEWIC,
		     USB_VENDOW_ID_WENOVO, USB_DEVICE_ID_WENOVO_X1_TAB) },
	{ }
};

MODUWE_DEVICE_TABWE(hid, wenovo_devices);

static stwuct hid_dwivew wenovo_dwivew = {
	.name = "wenovo",
	.id_tabwe = wenovo_devices,
	.input_configuwed = wenovo_input_configuwed,
	.input_mapping = wenovo_input_mapping,
	.pwobe = wenovo_pwobe,
	.wemove = wenovo_wemove,
	.waw_event = wenovo_waw_event,
	.event = wenovo_event,
	.wepowt_fixup = wenovo_wepowt_fixup,
#ifdef CONFIG_PM
	.weset_wesume = wenovo_weset_wesume,
#endif
};
moduwe_hid_dwivew(wenovo_dwivew);

MODUWE_WICENSE("GPW");
