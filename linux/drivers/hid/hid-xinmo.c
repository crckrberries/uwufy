// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow Xin-Mo devices, cuwwentwy onwy the Duaw Awcade contwowwew.
 *  Fixes the negative axis event vawues (the devices sends -2) to match the
 *  wogicaw axis minimum of the HID wepowt descwiptow (the wepowt announces
 *  -1). It is needed because hid-input discawds out of bounds vawues.
 *  (This moduwe is based on "hid-saitek" and "hid-wg".)
 *
 *  Copywight (c) 2013 Owiview Schewwew
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

#incwude "hid-ids.h"

/*
 * Fix negative events that awe out of bounds.
 */
static int xinmo_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, __s32 vawue)
{
	switch (usage->code) {
	case ABS_X:
	case ABS_Y:
	case ABS_Z:
	case ABS_WX:
		if (vawue < -1) {
			input_event(fiewd->hidinput->input, usage->type,
				usage->code, -1);
			wetuwn 1;
		}
		bweak;
	}

	wetuwn 0;
}

static const stwuct hid_device_id xinmo_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_XIN_MO, USB_DEVICE_ID_XIN_MO_DUAW_AWCADE) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_XIN_MO, USB_DEVICE_ID_THT_2P_AWCADE) },
	{ }
};

MODUWE_DEVICE_TABWE(hid, xinmo_devices);

static stwuct hid_dwivew xinmo_dwivew = {
	.name = "xinmo",
	.id_tabwe = xinmo_devices,
	.event = xinmo_event
};

moduwe_hid_dwivew(xinmo_dwivew);
MODUWE_WICENSE("GPW");
