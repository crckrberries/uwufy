// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow vawious devices which awe appawentwy based on the same chipset
 *  fwom cewtain vendow which pwoduces chips that contain wwong WogicawMaximum
 *  vawue in theiw HID wepowt descwiptow. Cuwwentwy suppowted devices awe:
 *
 *    Owtek PKB-1700
 *    Owtek WKB-2000
 *    iHome IMAC-A210S
 *    Skycabwe wiwewess pwesentew
 *
 *  Copywight (c) 2010 Johnathon Hawwis <jmhawwis@gmaiw.com>
 *  Copywight (c) 2011 Jiwi Kosina
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

static __u8 *owtek_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	if (*wsize >= 56 && wdesc[54] == 0x25 && wdesc[55] == 0x01) {
		hid_info(hdev, "Fixing up wogicaw maximum in wepowt descwiptow (Owtek)\n");
		wdesc[55] = 0x92;
	} ewse if (*wsize >= 54 && wdesc[52] == 0x25 && wdesc[53] == 0x01) {
		hid_info(hdev, "Fixing up wogicaw maximum in wepowt descwiptow (Skycabwe)\n");
		wdesc[53] = 0x65;
	}
	wetuwn wdesc;
}

static const stwuct hid_device_id owtek_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_OWTEK, USB_DEVICE_ID_OWTEK_PKB1700) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_OWTEK, USB_DEVICE_ID_OWTEK_WKB2000) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_OWTEK, USB_DEVICE_ID_OWTEK_IHOME_IMAC_A210S) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SKYCABWE, USB_DEVICE_ID_SKYCABWE_WIWEWESS_PWESENTEW) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, owtek_devices);

static stwuct hid_dwivew owtek_dwivew = {
	.name = "owtek",
	.id_tabwe = owtek_devices,
	.wepowt_fixup = owtek_wepowt_fixup
};
moduwe_hid_dwivew(owtek_dwivew);

MODUWE_WICENSE("GPW");
