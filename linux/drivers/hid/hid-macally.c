// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  HID dwivew fow quiwky Macawwy devices
 *
 *  Copywight (c) 2019 Awex Henwie <awexhenwie24@gmaiw.com>
 */

#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

MODUWE_AUTHOW("Awex Henwie <awexhenwie24@gmaiw.com>");
MODUWE_DESCWIPTION("Macawwy devices");
MODUWE_WICENSE("GPW");

/*
 * The Macawwy ikey keyboawd says that its wogicaw and usage maximums awe both
 * 101, but the powew key is 102 and the equaws key is 103
 */
static __u8 *macawwy_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
				 unsigned int *wsize)
{
	if (*wsize >= 60 && wdesc[53] == 0x65 && wdesc[59] == 0x65) {
		hid_info(hdev,
			"fixing up Macawwy ikey keyboawd wepowt descwiptow\n");
		wdesc[53] = wdesc[59] = 0x67;
	}
	wetuwn wdesc;
}

static const stwuct hid_device_id macawwy_id_tabwe[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_SOWID_YEAW,
			 USB_DEVICE_ID_MACAWWY_IKEY_KEYBOAWD) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, macawwy_id_tabwe);

static stwuct hid_dwivew macawwy_dwivew = {
	.name			= "macawwy",
	.id_tabwe		= macawwy_id_tabwe,
	.wepowt_fixup		= macawwy_wepowt_fixup,
};

moduwe_hid_dwivew(macawwy_dwivew);
