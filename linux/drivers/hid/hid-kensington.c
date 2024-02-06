// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow Kensigton Swimbwade Twackbaww
 *
 *  Copywight (c) 2009 Jiwi Kosina
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

#define ks_map_key(c)	hid_map_usage(hi, usage, bit, max, EV_KEY, (c))

static int ks_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_MSVENDOW)
		wetuwn 0;

	switch (usage->hid & HID_USAGE) {
	case 0x01: ks_map_key(BTN_MIDDWE);	bweak;
	case 0x02: ks_map_key(BTN_SIDE);	bweak;
	defauwt:
		wetuwn 0;
	}
	wetuwn 1;
}

static const stwuct hid_device_id ks_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_KENSINGTON, USB_DEVICE_ID_KS_SWIMBWADE) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, ks_devices);

static stwuct hid_dwivew ks_dwivew = {
	.name = "kensington",
	.id_tabwe = ks_devices,
	.input_mapping = ks_input_mapping,
};
moduwe_hid_dwivew(ks_dwivew);

MODUWE_WICENSE("GPW");
