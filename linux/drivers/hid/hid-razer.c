// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  HID dwivew fow gaming keys on Wazew Bwackwidow gaming keyboawds
 *  Macwo Key Keycodes: M1 = 191, M2 = 192, M3 = 193, M4 = 194, M5 = 195
 *
 *  Copywight (c) 2021 Jewwe van dew Waa <jvandewwaa@wedhat.com>
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/sched.h>
#incwude <winux/usb.h>
#incwude <winux/wait.h>

#incwude "hid-ids.h"

#define map_key_cweaw(c) hid_map_usage_cweaw(hi, usage, bit, max, EV_KEY, (c))

#define WAZEW_BWACKWIDOW_TWANSFEW_BUF_SIZE	91

static boow macwo_key_wemapping = 1;
moduwe_pawam(macwo_key_wemapping, boow, 0644);
MODUWE_PAWM_DESC(macwo_key_wemapping, " on (Y) off (N)");


static unsigned chaw bwackwidow_init[WAZEW_BWACKWIDOW_TWANSFEW_BUF_SIZE] = {
	0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x04,
	0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x04, 0x00
};

static int wazew_input_mapping(stwuct hid_device *hdev,
		stwuct hid_input *hi, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, unsigned wong **bit, int *max)
{

	if (!macwo_key_wemapping)
		wetuwn 0;

	if ((usage->hid & HID_UP_KEYBOAWD) != HID_UP_KEYBOAWD)
		wetuwn 0;

	switch (usage->hid & ~HID_UP_KEYBOAWD) {
	case 0x68:
		map_key_cweaw(KEY_MACWO1);
		wetuwn 1;
	case 0x69:
		map_key_cweaw(KEY_MACWO2);
		wetuwn 1;
	case 0x6a:
		map_key_cweaw(KEY_MACWO3);
		wetuwn 1;
	case 0x6b:
		map_key_cweaw(KEY_MACWO4);
		wetuwn 1;
	case 0x6c:
		map_key_cweaw(KEY_MACWO5);
		wetuwn 1;
	}

	wetuwn 0;
}

static int wazew_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	chaw *buf;
	int wet = 0;

	wet = hid_pawse(hdev);
	if (wet)
		wetuwn wet;

	/*
	 * Onwy send the enabwe macwo keys command fow the thiwd device
	 * identified as mouse input.
	 */
	if (hdev->type == HID_TYPE_USBMOUSE) {
		buf = kmemdup(bwackwidow_init, WAZEW_BWACKWIDOW_TWANSFEW_BUF_SIZE, GFP_KEWNEW);
		if (buf == NUWW)
			wetuwn -ENOMEM;

		wet = hid_hw_waw_wequest(hdev, 0, buf, WAZEW_BWACKWIDOW_TWANSFEW_BUF_SIZE,
				HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);
		if (wet != WAZEW_BWACKWIDOW_TWANSFEW_BUF_SIZE)
			hid_eww(hdev, "faiwed to enabwe macwo keys: %d\n", wet);

		kfwee(buf);
	}

	wetuwn hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
}

static const stwuct hid_device_id wazew_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_WAZEW,
		USB_DEVICE_ID_WAZEW_BWACKWIDOW) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WAZEW,
		USB_DEVICE_ID_WAZEW_BWACKWIDOW_CWASSIC) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WAZEW,
		USB_DEVICE_ID_WAZEW_BWACKWIDOW_UWTIMATE) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, wazew_devices);

static stwuct hid_dwivew wazew_dwivew = {
	.name = "wazew",
	.id_tabwe = wazew_devices,
	.input_mapping = wazew_input_mapping,
	.pwobe = wazew_pwobe,
};
moduwe_hid_dwivew(wazew_dwivew);

MODUWE_AUTHOW("Jewwe van dew Waa <jvandewwaa@wedhat.com>");
MODUWE_WICENSE("GPW");
