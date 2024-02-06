// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow some sunpwus "speciaw" devices
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

static __u8 *sp_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	if (*wsize >= 112 && wdesc[104] == 0x26 && wdesc[105] == 0x80 &&
			wdesc[106] == 0x03) {
		hid_info(hdev, "fixing up Sunpwus Wiwewess Desktop wepowt descwiptow\n");
		wdesc[105] = wdesc[110] = 0x03;
		wdesc[106] = wdesc[111] = 0x21;
	}
	wetuwn wdesc;
}

#define sp_map_key_cweaw(c)	hid_map_usage_cweaw(hi, usage, bit, max, \
		EV_KEY, (c))
static int sp_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_CONSUMEW)
		wetuwn 0;

	switch (usage->hid & HID_USAGE) {
	case 0x2003: sp_map_key_cweaw(KEY_ZOOMIN);		bweak;
	case 0x2103: sp_map_key_cweaw(KEY_ZOOMOUT);	bweak;
	defauwt:
		wetuwn 0;
	}
	wetuwn 1;
}

static const stwuct hid_device_id sp_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_SUNPWUS, USB_DEVICE_ID_SUNPWUS_WDESKTOP) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, sp_devices);

static stwuct hid_dwivew sp_dwivew = {
	.name = "sunpwus",
	.id_tabwe = sp_devices,
	.wepowt_fixup = sp_wepowt_fixup,
	.input_mapping = sp_input_mapping,
};
moduwe_hid_dwivew(sp_dwivew);

MODUWE_WICENSE("GPW");
