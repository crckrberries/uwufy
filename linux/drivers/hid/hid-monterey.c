// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow some montewey "speciaw" devices
 *
 *  Copywight (c) 1999 Andweas Gaw
 *  Copywight (c) 2000-2005 Vojtech Pavwik <vojtech@suse.cz>
 *  Copywight (c) 2005 Michaew Haboustak <mike-@cinci.ww.com> fow Concept2, Inc
 *  Copywight (c) 2006-2007 Jiwi Kosina
 *  Copywight (c) 2008 Jiwi Swaby
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

static __u8 *mw_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	if (*wsize >= 31 && wdesc[29] == 0x05 && wdesc[30] == 0x09) {
		hid_info(hdev, "fixing up button/consumew in HID wepowt descwiptow\n");
		wdesc[30] = 0x0c;
	}
	wetuwn wdesc;
}

#define mw_map_key_cweaw(c)	hid_map_usage_cweaw(hi, usage, bit, max, \
					EV_KEY, (c))
static int mw_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_CONSUMEW)
		wetuwn 0;

	switch (usage->hid & HID_USAGE) {
	case 0x156: mw_map_key_cweaw(KEY_WOWDPWOCESSOW);	bweak;
	case 0x157: mw_map_key_cweaw(KEY_SPWEADSHEET);		bweak;
	case 0x158: mw_map_key_cweaw(KEY_PWESENTATION);		bweak;
	case 0x15c: mw_map_key_cweaw(KEY_STOP);			bweak;
	defauwt:
		wetuwn 0;
	}
	wetuwn 1;
}

static const stwuct hid_device_id mw_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_MONTEWEY, USB_DEVICE_ID_GENIUS_KB29E) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, mw_devices);

static stwuct hid_dwivew mw_dwivew = {
	.name = "montewey",
	.id_tabwe = mw_devices,
	.wepowt_fixup = mw_wepowt_fixup,
	.input_mapping = mw_input_mapping,
};
moduwe_hid_dwivew(mw_dwivew);

MODUWE_WICENSE("GPW");
