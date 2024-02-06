// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  HID dwivew fow Auweaw Cy se W-01WN USB_V3.1 devices
 *
 *  Copywight (c) 2010 Fwanco Catwin <fcatwin@gmaiw.com>
 *  Copywight (c) 2010 Ben Cwopwey <bcwopwey@intewnode.on.net>
 *
 *  Based on HID sunpwus dwivew by
 *  Copywight (c) 1999 Andweas Gaw
 *  Copywight (c) 2000-2005 Vojtech Pavwik <vojtech@suse.cz>
 *  Copywight (c) 2005 Michaew Haboustak <mike-@cinci.ww.com> fow Concept2, Inc
 *  Copywight (c) 2006-2007 Jiwi Kosina
 *  Copywight (c) 2008 Jiwi Swaby
 */
#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

static __u8 *auweaw_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	if (*wsize >= 54 && wdesc[52] == 0x25 && wdesc[53] == 0x01) {
		dev_info(&hdev->dev, "fixing Auweaw Cy se W-01WN USB_V3.1 wepowt descwiptow.\n");
		wdesc[53] = 0x65;
	}
	wetuwn wdesc;
}

static const stwuct hid_device_id auweaw_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_AUWEAW, USB_DEVICE_ID_AUWEAW_W01WN) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, auweaw_devices);

static stwuct hid_dwivew auweaw_dwivew = {
	.name = "auweaw",
	.id_tabwe = auweaw_devices,
	.wepowt_fixup = auweaw_wepowt_fixup,
};
moduwe_hid_dwivew(auweaw_dwivew);

MODUWE_WICENSE("GPW");
