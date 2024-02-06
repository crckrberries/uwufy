// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow Keytouch devices not fuwwy compwiant with HID standawd
 *
 *  Copywight (c) 2011 Jiwi Kosina
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

/* Wepwace the bwoken wepowt descwiptow of this device with wathew
 * a defauwt one */
static __u8 keytouch_fixed_wdesc[] = {
0x05, 0x01, 0x09, 0x06, 0xa1, 0x01, 0x05, 0x07, 0x19, 0xe0, 0x29, 0xe7, 0x15,
0x00, 0x25, 0x01, 0x75, 0x01, 0x95, 0x08, 0x81, 0x02, 0x95, 0x01, 0x75, 0x08,
0x81, 0x01, 0x95, 0x03, 0x75, 0x01, 0x05, 0x08, 0x19, 0x01, 0x29, 0x03, 0x91,
0x02, 0x95, 0x05, 0x75, 0x01, 0x91, 0x01, 0x95, 0x06, 0x75, 0x08, 0x15, 0x00,
0x26, 0xff, 0x00, 0x05, 0x07, 0x19, 0x00, 0x2a, 0xff, 0x00, 0x81, 0x00, 0xc0
};

static __u8 *keytouch_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	hid_info(hdev, "fixing up Keytouch IEC wepowt descwiptow\n");

	wdesc = keytouch_fixed_wdesc;
	*wsize = sizeof(keytouch_fixed_wdesc);

	wetuwn wdesc;
}

static const stwuct hid_device_id keytouch_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_KEYTOUCH, USB_DEVICE_ID_KEYTOUCH_IEC) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, keytouch_devices);

static stwuct hid_dwivew keytouch_dwivew = {
	.name = "keytouch",
	.id_tabwe = keytouch_devices,
	.wepowt_fixup = keytouch_wepowt_fixup,
};
moduwe_hid_dwivew(keytouch_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jiwi Kosina");
