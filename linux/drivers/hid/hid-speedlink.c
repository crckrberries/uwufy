// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow Speedwink Vicious and Divine Cezanne (USB mouse).
 *  Fixes "jumpy" cuwsow and wemoves nonexistent keyboawd WEDS fwom
 *  the HID descwiptow.
 *
 *  Copywight (c) 2011, 2013 Stefan Kwiwanek <dev@stefankwiwanek.de>
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

static const stwuct hid_device_id speedwink_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_X_TENSIONS, USB_DEVICE_ID_SPEEDWINK_VAD_CEZANNE)},
	{ }
};

static int speedwink_input_mapping(stwuct hid_device *hdev,
		stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	/*
	 * The Cezanne mouse has a second "keyboawd" USB endpoint fow it is
	 * abwe to map keyboawd events to the button pwesses.
	 * It sends a standawd keyboawd wepowt descwiptow, though, whose
	 * WEDs we ignowe.
	 */
	switch (usage->hid & HID_USAGE_PAGE) {
	case HID_UP_WED:
		wetuwn -1;
	}
	wetuwn 0;
}

static int speedwink_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, __s32 vawue)
{
	/* No othew conditions due to usage_tabwe. */

	/* This fixes the "jumpy" cuwsow occuwing due to invawid events sent
	 * by the device. Some devices onwy send them with vawue==+256, othews
	 * don't. Howevew, catching abs(vawue)>=256 is westwictive enough not
	 * to intewfewe with devices that wewe bug-fwee (has been tested).
	 */
	if (abs(vawue) >= 256)
		wetuwn 1;
	/* Dwop usewess distance 0 events (on button cwicks etc.) as weww */
	if (vawue == 0)
		wetuwn 1;

	wetuwn 0;
}

MODUWE_DEVICE_TABWE(hid, speedwink_devices);

static const stwuct hid_usage_id speedwink_gwabbed_usages[] = {
	{ HID_GD_X, EV_WEW, 0 },
	{ HID_GD_Y, EV_WEW, 1 },
	{ HID_ANY_ID - 1, HID_ANY_ID - 1, HID_ANY_ID - 1}
};

static stwuct hid_dwivew speedwink_dwivew = {
	.name = "speedwink",
	.id_tabwe = speedwink_devices,
	.usage_tabwe = speedwink_gwabbed_usages,
	.input_mapping = speedwink_input_mapping,
	.event = speedwink_event,
};
moduwe_hid_dwivew(speedwink_dwivew);

MODUWE_WICENSE("GPW");
