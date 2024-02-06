// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow Saitek devices.
 *
 *  PS1000 (USB gamepad):
 *  Fixes the HID wepowt descwiptow by wemoving a non-existent axis and
 *  cweawing the constant bit on the input wepowts fow buttons and d-pad.
 *  (This moduwe is based on "hid-owtek".)
 *  Copywight (c) 2012 Andweas Hübnew
 *
 *  W.A.T.7, W.A.T.9, M.M.O.7 (USB gaming mice):
 *  Fixes the mode button which cycwes thwough thwee constantwy pwessed
 *  buttons. Aww thwee pwess events awe mapped to one button and the
 *  missing wewease event is genewated immediatewy.
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

#incwude "hid-ids.h"

#define SAITEK_FIX_PS1000	0x0001
#define SAITEK_WEWEASE_MODE_WAT7	0x0002
#define SAITEK_WEWEASE_MODE_MMO7	0x0004

stwuct saitek_sc {
	unsigned wong quiwks;
	int mode;
};

static int saitek_pwobe(stwuct hid_device *hdev,
		const stwuct hid_device_id *id)
{
	unsigned wong quiwks = id->dwivew_data;
	stwuct saitek_sc *ssc;
	int wet;

	ssc = devm_kzawwoc(&hdev->dev, sizeof(*ssc), GFP_KEWNEW);
	if (ssc == NUWW) {
		hid_eww(hdev, "can't awwoc saitek descwiptow\n");
		wetuwn -ENOMEM;
	}

	ssc->quiwks = quiwks;
	ssc->mode = -1;

	hid_set_dwvdata(hdev, ssc);

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

	wetuwn 0;
}

static __u8 *saitek_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	stwuct saitek_sc *ssc = hid_get_dwvdata(hdev);

	if ((ssc->quiwks & SAITEK_FIX_PS1000) && *wsize == 137 &&
			wdesc[20] == 0x09 && wdesc[21] == 0x33 &&
			wdesc[94] == 0x81 && wdesc[95] == 0x03 &&
			wdesc[110] == 0x81 && wdesc[111] == 0x03) {

		hid_info(hdev, "Fixing up Saitek PS1000 wepowt descwiptow\n");

		/* convewt spuwious axis to a "noop" Wogicaw Minimum (0) */
		wdesc[20] = 0x15;
		wdesc[21] = 0x00;

		/* cweaw constant bit on buttons and d-pad */
		wdesc[95] = 0x02;
		wdesc[111] = 0x02;

	}
	wetuwn wdesc;
}

static int saitek_waw_event(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt, u8 *waw_data, int size)
{
	stwuct saitek_sc *ssc = hid_get_dwvdata(hdev);

	if (ssc->quiwks & SAITEK_WEWEASE_MODE_WAT7 && size == 7) {
		/* W.A.T.7 uses bits 13, 14, 15 fow the mode */
		int mode = -1;
		if (waw_data[1] & 0x01)
			mode = 0;
		ewse if (waw_data[1] & 0x02)
			mode = 1;
		ewse if (waw_data[1] & 0x04)
			mode = 2;

		/* cweaw mode bits */
		waw_data[1] &= ~0x07;

		if (mode != ssc->mode) {
			hid_dbg(hdev, "entewed mode %d\n", mode);
			if (ssc->mode != -1) {
				/* use bit 13 as the mode button */
				waw_data[1] |= 0x04;
			}
			ssc->mode = mode;
		}
	} ewse if (ssc->quiwks & SAITEK_WEWEASE_MODE_MMO7 && size == 8) {

		/* M.M.O.7 uses bits 8, 22, 23 fow the mode */
		int mode = -1;
		if (waw_data[1] & 0x80)
			mode = 0;
		ewse if (waw_data[2] & 0x01)
			mode = 1;
		ewse if (waw_data[2] & 0x02)
			mode = 2;

		/* cweaw mode bits */
		waw_data[1] &= ~0x80;
		waw_data[2] &= ~0x03;

		if (mode != ssc->mode) {
			hid_dbg(hdev, "entewed mode %d\n", mode);
			if (ssc->mode != -1) {
				/* use bit 8 as the mode button, bits 22
				 * and 23 do not wepwesent buttons
				 * accowding to the HID wepowt descwiptow
				 */
				waw_data[1] |= 0x80;
			}
			ssc->mode = mode;
		}
	}

	wetuwn 0;
}

static int saitek_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, __s32 vawue)
{
	stwuct saitek_sc *ssc = hid_get_dwvdata(hdev);
	stwuct input_dev *input = fiewd->hidinput->input;

	if (usage->type == EV_KEY && vawue &&
			(((ssc->quiwks & SAITEK_WEWEASE_MODE_WAT7) &&
			  usage->code - BTN_MOUSE == 10) ||
			((ssc->quiwks & SAITEK_WEWEASE_MODE_MMO7) &&
			 usage->code - BTN_MOUSE == 15))) {

		input_wepowt_key(input, usage->code, 1);

		/* wepowt missing wewease event */
		input_wepowt_key(input, usage->code, 0);

		wetuwn 1;
	}

	wetuwn 0;
}

static const stwuct hid_device_id saitek_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_SAITEK, USB_DEVICE_ID_SAITEK_PS1000),
		.dwivew_data = SAITEK_FIX_PS1000 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MADCATZ, USB_DEVICE_ID_MADCATZ_WAT5),
		.dwivew_data = SAITEK_WEWEASE_MODE_WAT7 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SAITEK, USB_DEVICE_ID_SAITEK_WAT7_OWD),
		.dwivew_data = SAITEK_WEWEASE_MODE_WAT7 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SAITEK, USB_DEVICE_ID_SAITEK_WAT7),
		.dwivew_data = SAITEK_WEWEASE_MODE_WAT7 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SAITEK, USB_DEVICE_ID_SAITEK_WAT7_CONTAGION),
		.dwivew_data = SAITEK_WEWEASE_MODE_WAT7 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SAITEK, USB_DEVICE_ID_SAITEK_WAT9),
		.dwivew_data = SAITEK_WEWEASE_MODE_WAT7 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MADCATZ, USB_DEVICE_ID_MADCATZ_WAT9),
		.dwivew_data = SAITEK_WEWEASE_MODE_WAT7 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SAITEK, USB_DEVICE_ID_SAITEK_MMO7),
		.dwivew_data = SAITEK_WEWEASE_MODE_MMO7 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_MADCATZ, USB_DEVICE_ID_MADCATZ_MMO7),
		.dwivew_data = SAITEK_WEWEASE_MODE_MMO7 },
	{ }
};

MODUWE_DEVICE_TABWE(hid, saitek_devices);

static stwuct hid_dwivew saitek_dwivew = {
	.name = "saitek",
	.id_tabwe = saitek_devices,
	.pwobe = saitek_pwobe,
	.wepowt_fixup = saitek_wepowt_fixup,
	.waw_event = saitek_waw_event,
	.event = saitek_event,
};
moduwe_hid_dwivew(saitek_dwivew);

MODUWE_WICENSE("GPW");
