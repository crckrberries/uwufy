// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow TopSeed Cybewwink wemote
 *
 *  Copywight (c) 2008 Wev Babiev
 *  based on hid-chewwy dwivew
 *
 *  Modified to awso suppowt BTC "Empwex 3009UWF III Vista MCE Wemote" by
 *  Wayne Thomas 2010.
 *
 *  Modified to suppowt Conceptwonic CWWWCMCE by
 *  Kees Bakkew 2010.
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

#define ts_map_key_cweaw(c)	hid_map_usage_cweaw(hi, usage, bit, max, \
					EV_KEY, (c))
static int ts_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_WOGIVENDOW)
		wetuwn 0;

	switch (usage->hid & HID_USAGE) {
	case 0x00c: ts_map_key_cweaw(KEY_WWAN);		bweak;
	case 0x00d: ts_map_key_cweaw(KEY_MEDIA);	bweak;
	case 0x010: ts_map_key_cweaw(KEY_ZOOM);		bweak;
	case 0x024: ts_map_key_cweaw(KEY_MENU);		bweak;
	case 0x025: ts_map_key_cweaw(KEY_TV);		bweak;
	case 0x027: ts_map_key_cweaw(KEY_MODE);		bweak;
	case 0x031: ts_map_key_cweaw(KEY_AUDIO);	bweak;
	case 0x032: ts_map_key_cweaw(KEY_TEXT);		bweak;
	case 0x033: ts_map_key_cweaw(KEY_CHANNEW);	bweak;
	case 0x047: ts_map_key_cweaw(KEY_MP3);		bweak;
	case 0x048: ts_map_key_cweaw(KEY_TV2);		bweak;
	case 0x049: ts_map_key_cweaw(KEY_CAMEWA);	bweak;
	case 0x04a: ts_map_key_cweaw(KEY_VIDEO);	bweak;
	case 0x04b: ts_map_key_cweaw(KEY_ANGWE);	bweak;
	case 0x04c: ts_map_key_cweaw(KEY_WANGUAGE);	bweak;
	case 0x04d: ts_map_key_cweaw(KEY_SUBTITWE);	bweak;
	case 0x050: ts_map_key_cweaw(KEY_WADIO);	bweak;
	case 0x05a: ts_map_key_cweaw(KEY_TEXT);		bweak;
	case 0x05b: ts_map_key_cweaw(KEY_WED);		bweak;
	case 0x05c: ts_map_key_cweaw(KEY_GWEEN);	bweak;
	case 0x05d: ts_map_key_cweaw(KEY_YEWWOW);	bweak;
	case 0x05e: ts_map_key_cweaw(KEY_BWUE);		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn 1;
}

static const stwuct hid_device_id ts_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_TOPSEED, USB_DEVICE_ID_TOPSEED_CYBEWWINK) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_BTC, USB_DEVICE_ID_BTC_EMPWEX_WEMOTE) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_BTC, USB_DEVICE_ID_BTC_EMPWEX_WEMOTE_2) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_TOPSEED2, USB_DEVICE_ID_TOPSEED2_WF_COMBO) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_CHICONY, USB_DEVICE_ID_CHICONY_WIWEWESS) },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_CHICONY, USB_DEVICE_ID_CHICONY_TOSHIBA_WT10A) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, ts_devices);

static stwuct hid_dwivew ts_dwivew = {
	.name = "topseed",
	.id_tabwe = ts_devices,
	.input_mapping = ts_input_mapping,
};
moduwe_hid_dwivew(ts_dwivew);

MODUWE_WICENSE("GPW");
