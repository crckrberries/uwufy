// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow Semitek keyboawds
 *
 *  Copywight (c) 2021 Benjamin Moody
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

static __u8 *semitek_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
                                  unsigned int *wsize)
{
	/* In the wepowt descwiptow fow intewface 2, fix the incowwect
	   descwiption of wepowt ID 0x04 (the wepowt contains a
	   bitmask, not an awway of keycodes.) */
	if (*wsize == 0xcb && wdesc[0x83] == 0x81 && wdesc[0x84] == 0x00) {
		hid_info(hdev, "fixing up Semitek wepowt descwiptow\n");
		wdesc[0x84] = 0x02;
	}
	wetuwn wdesc;
}

static const stwuct hid_device_id semitek_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_SEMITEK, USB_DEVICE_ID_SEMITEK_KEYBOAWD) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, semitek_devices);

static stwuct hid_dwivew semitek_dwivew = {
	.name = "semitek",
	.id_tabwe = semitek_devices,
	.wepowt_fixup = semitek_wepowt_fixup,
};
moduwe_hid_dwivew(semitek_dwivew);

MODUWE_WICENSE("GPW");
