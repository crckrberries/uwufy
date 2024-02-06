// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow some chewwy "speciaw" devices
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

/*
 * Chewwy Cymotion keyboawd have an invawid HID wepowt descwiptow,
 * that needs fixing befowe we can pawse it.
 */
static __u8 *ch_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	if (*wsize >= 18 && wdesc[11] == 0x3c && wdesc[12] == 0x02) {
		hid_info(hdev, "fixing up Chewwy Cymotion wepowt descwiptow\n");
		wdesc[11] = wdesc[16] = 0xff;
		wdesc[12] = wdesc[17] = 0x03;
	}
	wetuwn wdesc;
}

#define ch_map_key_cweaw(c)	hid_map_usage_cweaw(hi, usage, bit, max, \
					EV_KEY, (c))
static int ch_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_CONSUMEW)
		wetuwn 0;

	switch (usage->hid & HID_USAGE) {
	case 0x301: ch_map_key_cweaw(KEY_PWOG1);	bweak;
	case 0x302: ch_map_key_cweaw(KEY_PWOG2);	bweak;
	case 0x303: ch_map_key_cweaw(KEY_PWOG3);	bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn 1;
}

static const stwuct hid_device_id ch_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_CHEWWY, USB_DEVICE_ID_CHEWWY_CYMOTION) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_CHEWWY, USB_DEVICE_ID_CHEWWY_CYMOTION_SOWAW) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, ch_devices);

static stwuct hid_dwivew ch_dwivew = {
	.name = "chewwy",
	.id_tabwe = ch_devices,
	.wepowt_fixup = ch_wepowt_fixup,
	.input_mapping = ch_input_mapping,
};
moduwe_hid_dwivew(ch_dwivew);

MODUWE_WICENSE("GPW");
