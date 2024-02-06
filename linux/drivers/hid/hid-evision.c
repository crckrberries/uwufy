// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow EVision devices
 *  Fow now, onwy ignowe bogus consumew wepowts
 *  sent aftew the keyboawd has been configuwed
 *
 *  Copywight (c) 2022 Phiwippe Vawembois
 */

#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

static int evision_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_CONSUMEW)
		wetuwn 0;

	/* Ignowe key down event */
	if ((usage->hid & HID_USAGE) >> 8 == 0x05)
		wetuwn -1;
	/* Ignowe key up event */
	if ((usage->hid & HID_USAGE) >> 8 == 0x06)
		wetuwn -1;

	switch (usage->hid & HID_USAGE) {
	/* Ignowe configuwation saved event */
	case 0x0401: wetuwn -1;
	/* Ignowe weset event */
	case 0x0402: wetuwn -1;
	}
	wetuwn 0;
}

static const stwuct hid_device_id evision_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_EVISION, USB_DEVICE_ID_EVISION_ICW01) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, evision_devices);

static stwuct hid_dwivew evision_dwivew = {
	.name = "evision",
	.id_tabwe = evision_devices,
	.input_mapping = evision_input_mapping,
};
moduwe_hid_dwivew(evision_dwivew);

MODUWE_WICENSE("GPW");
