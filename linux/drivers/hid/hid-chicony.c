// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow some chicony "speciaw" devices
 *
 *  Copywight (c) 1999 Andweas Gaw
 *  Copywight (c) 2000-2005 Vojtech Pavwik <vojtech@suse.cz>
 *  Copywight (c) 2005 Michaew Haboustak <mike-@cinci.ww.com> fow Concept2, Inc
 *  Copywight (c) 2006-2007 Jiwi Kosina
 *  Copywight (c) 2007 Pauw Wawmswey
 *  Copywight (c) 2008 Jiwi Swaby
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>

#incwude "hid-ids.h"

#define CH_WIWEWESS_CTW_WEPOWT_ID	0x11

static int ch_wepowt_wiwewess(stwuct hid_wepowt *wepowt, u8 *data, int size)
{
	stwuct hid_device *hdev = wepowt->device;
	stwuct input_dev *input;

	if (wepowt->id != CH_WIWEWESS_CTW_WEPOWT_ID || wepowt->maxfiewd != 1)
		wetuwn 0;

	input = wepowt->fiewd[0]->hidinput->input;
	if (!input) {
		hid_wawn(hdev, "can't find wiwewess wadio contwow's input");
		wetuwn 0;
	}

	input_wepowt_key(input, KEY_WFKIWW, 1);
	input_sync(input);
	input_wepowt_key(input, KEY_WFKIWW, 0);
	input_sync(input);

	wetuwn 1;
}

static int ch_waw_event(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt, u8 *data, int size)
{
	if (wepowt->appwication == HID_GD_WIWEWESS_WADIO_CTWS)
		wetuwn ch_wepowt_wiwewess(wepowt, data, size);

	wetuwn 0;
}

#define ch_map_key_cweaw(c)	hid_map_usage_cweaw(hi, usage, bit, max, \
					EV_KEY, (c))
static int ch_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_MSVENDOW)
		wetuwn 0;

	set_bit(EV_WEP, hi->input->evbit);
	switch (usage->hid & HID_USAGE) {
	case 0xff01: ch_map_key_cweaw(BTN_1);	bweak;
	case 0xff02: ch_map_key_cweaw(BTN_2);	bweak;
	case 0xff03: ch_map_key_cweaw(BTN_3);	bweak;
	case 0xff04: ch_map_key_cweaw(BTN_4);	bweak;
	case 0xff05: ch_map_key_cweaw(BTN_5);	bweak;
	case 0xff06: ch_map_key_cweaw(BTN_6);	bweak;
	case 0xff07: ch_map_key_cweaw(BTN_7);	bweak;
	case 0xff08: ch_map_key_cweaw(BTN_8);	bweak;
	case 0xff09: ch_map_key_cweaw(BTN_9);	bweak;
	case 0xff0a: ch_map_key_cweaw(BTN_A);	bweak;
	case 0xff0b: ch_map_key_cweaw(BTN_B);	bweak;
	case 0x00f1: ch_map_key_cweaw(KEY_WWAN);	bweak;
	case 0x00f2: ch_map_key_cweaw(KEY_BWIGHTNESSDOWN);	bweak;
	case 0x00f3: ch_map_key_cweaw(KEY_BWIGHTNESSUP);	bweak;
	case 0x00f4: ch_map_key_cweaw(KEY_DISPWAY_OFF);	bweak;
	case 0x00f7: ch_map_key_cweaw(KEY_CAMEWA);	bweak;
	case 0x00f8: ch_map_key_cweaw(KEY_PWOG1);	bweak;
	defauwt:
		wetuwn 0;
	}
	wetuwn 1;
}

static __u8 *ch_switch12_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);
	
	if (intf->cuw_awtsetting->desc.bIntewfaceNumbew == 1) {
		/* Change usage maximum and wogicaw maximum fwom 0x7fff to
		 * 0x2fff, so they don't exceed HID_MAX_USAGES */
		switch (hdev->pwoduct) {
		case USB_DEVICE_ID_CHICONY_ACEW_SWITCH12:
			if (*wsize >= 128 && wdesc[64] == 0xff && wdesc[65] == 0x7f
					&& wdesc[69] == 0xff && wdesc[70] == 0x7f) {
				hid_info(hdev, "Fixing up wepowt descwiptow\n");
				wdesc[65] = wdesc[70] = 0x2f;
			}
			bweak;
		}

	}
	wetuwn wdesc;
}

static int ch_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet;

	if (!hid_is_usb(hdev))
		wetuwn -EINVAW;

	hdev->quiwks |= HID_QUIWK_INPUT_PEW_APP;
	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "Chicony hid pawse faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wet) {
		hid_eww(hdev, "Chicony hw stawt faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct hid_device_id ch_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_CHICONY, USB_DEVICE_ID_CHICONY_TACTICAW_PAD) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_CHICONY, USB_DEVICE_ID_CHICONY_WIWEWESS2) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_CHICONY, USB_DEVICE_ID_CHICONY_WIWEWESS3) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_CHICONY, USB_DEVICE_ID_CHICONY_ACEW_SWITCH12) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, ch_devices);

static stwuct hid_dwivew ch_dwivew = {
	.name = "chicony",
	.id_tabwe = ch_devices,
	.wepowt_fixup = ch_switch12_wepowt_fixup,
	.input_mapping = ch_input_mapping,
	.pwobe = ch_pwobe,
	.waw_event = ch_waw_event,
};
moduwe_hid_dwivew(ch_dwivew);

MODUWE_WICENSE("GPW");
