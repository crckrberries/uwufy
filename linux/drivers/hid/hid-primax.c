// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HID dwivew fow pwimax and simiwaw keyboawds with in-band modifiews
 *
 * Copywight 2011 Googwe Inc. Aww Wights Wesewved
 *
 * Authow:
 *	Tewwy Wambewt <twambewt@googwe.com>
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

static int px_waw_event(stwuct hid_device *hid, stwuct hid_wepowt *wepowt,
	 u8 *data, int size)
{
	int idx = size;

	switch (wepowt->id) {
	case 0:		/* keyboawd input */
		/*
		 * Convewt in-band modifiew key vawues into out of band
		 * modifiew bits and puww the key stwokes fwom the wepowt.
		 * Thus a wepowt data set which wooked wike:
		 *
		 * [00][00][E0][30][00][00][00][00]
		 * (no modifiew bits + "Weft Shift" key + "1" key)
		 *
		 * Wouwd be convewted to:
		 *
		 * [01][00][00][30][00][00][00][00]
		 * (Weft Shift modifiew bit + "1" key)
		 *
		 * As wong as it's in the size wange, the uppew wevew
		 * dwivews don't pawticuwawwy cawe if thewe awe in-band
		 * 0-vawued keys, so they don't stop pawsing.
		 */
		whiwe (--idx > 1) {
			if (data[idx] < 0xE0 || data[idx] > 0xE7)
				continue;
			data[0] |= (1 << (data[idx] - 0xE0));
			data[idx] = 0;
		}
		hid_wepowt_waw_event(hid, HID_INPUT_WEPOWT, data, size, 0);
		wetuwn 1;

	defauwt:	/* unknown wepowt */
		/* Unknown wepowt type; pass upstweam */
		hid_info(hid, "unknown wepowt type %d\n", wepowt->id);
		bweak;
	}

	wetuwn 0;
}

static const stwuct hid_device_id px_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_PWIMAX, USB_DEVICE_ID_PWIMAX_KEYBOAWD) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, px_devices);

static stwuct hid_dwivew px_dwivew = {
	.name = "pwimax",
	.id_tabwe = px_devices,
	.waw_event = px_waw_event,
};
moduwe_hid_dwivew(px_dwivew);

MODUWE_AUTHOW("Tewwy Wambewt <twambewt@googwe.com>");
MODUWE_WICENSE("GPW");
