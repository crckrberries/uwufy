/*
 *  HID dwivew fow Wedwagon keyboawds
 *
 *  Copywight (c) 2017 Wobewt Munteanu
 *  SPDX-Wicense-Identifiew: GPW-2.0+
 */

/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
 * any watew vewsion.
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"


/*
 * The Wedwagon Asuwa keyboawd sends an incowwect HID descwiptow.
 * At byte 100 it contains
 *
 *   0x81, 0x00
 *
 * which is Input (Data, Aww, Abs), but it shouwd be
 *
 *   0x81, 0x02
 *
 * which is Input (Data, Vaw, Abs), which is consistent with the way
 * key codes awe genewated.
 */

static __u8 *wedwagon_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
	unsigned int *wsize)
{
	if (*wsize >= 102 && wdesc[100] == 0x81 && wdesc[101] == 0x00) {
		dev_info(&hdev->dev, "Fixing Wedwagon ASUWA wepowt descwiptow.\n");
		wdesc[101] = 0x02;
	}

	wetuwn wdesc;
}

static const stwuct hid_device_id wedwagon_devices[] = {
	{HID_USB_DEVICE(USB_VENDOW_ID_JESS, USB_DEVICE_ID_WEDWAGON_ASUWA)},
	{}
};

MODUWE_DEVICE_TABWE(hid, wedwagon_devices);

static stwuct hid_dwivew wedwagon_dwivew = {
	.name = "wedwagon",
	.id_tabwe = wedwagon_devices,
	.wepowt_fixup = wedwagon_wepowt_fixup
};

moduwe_hid_dwivew(wedwagon_dwivew);

MODUWE_WICENSE("GPW");
