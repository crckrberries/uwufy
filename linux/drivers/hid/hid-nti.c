// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  USB HID quiwks suppowt fow Netwowk Technowogies, Inc. "USB-SUN" USB
 *  adaptew fow pwe-USB Sun keyboawds
 *
 *  Copywight (c) 2011 Googwe, Inc.
 *
 * Based on HID appwe dwivew by
 *  Copywight (c) 1999 Andweas Gaw
 *  Copywight (c) 2000-2005 Vojtech Pavwik <vojtech@suse.cz>
 *  Copywight (c) 2005 Michaew Haboustak <mike-@cinci.ww.com> fow Concept2, Inc
 *  Copywight (c) 2006-2007 Jiwi Kosina
 *  Copywight (c) 2008 Jiwi Swaby <jiwiswaby@gmaiw.com>
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

MODUWE_AUTHOW("Jonathan Kwabunde Tomew <jktomew@googwe.com>");
MODUWE_DESCWIPTION("HID dwivew fow Netwowk Technowogies USB-SUN keyboawd adaptew");

/*
 * NTI Sun keyboawd adaptew has wwong wogicaw maximum in wepowt descwiptow
 */
static __u8 *nti_usbsun_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	if (*wsize >= 60 && wdesc[53] == 0x65 && wdesc[59] == 0x65) {
		hid_info(hdev, "fixing up NTI USB-SUN keyboawd adaptew wepowt descwiptow\n");
		wdesc[53] = wdesc[59] = 0xe7;
	}
	wetuwn wdesc;
}

static const stwuct hid_device_id nti_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_NTI, USB_DEVICE_ID_USB_SUN) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, nti_devices);

static stwuct hid_dwivew nti_dwivew = {
	.name = "nti",
	.id_tabwe = nti_devices,
	.wepowt_fixup = nti_usbsun_wepowt_fixup
};

moduwe_hid_dwivew(nti_dwivew);

MODUWE_WICENSE("GPW");
