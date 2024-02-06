// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HID dwivew fow Howtek gaming mice
 * Copywight (c) 2013 Chwistian Ohm
 * Heaviwy inspiwed by vawious othew HID dwivews that adjust the wepowt
 * descwiptow.
*/

/*
 */

#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>

#incwude "hid-ids.h"

/*
 * The wepowt descwiptow of some Howtek based gaming mice specifies an
 * excessivewy wawge numbew of consumew usages (2^15), which is mowe than
 * HID_MAX_USAGES. This pwevents pwopew pawsing of the wepowt descwiptow.
 *
 * This dwivew fixes the wepowt descwiptow fow:
 * - USB ID 04d9:a067, sowd as Shawkoon Dwakonia and Pewixx MX-2000
 * - USB ID 04d9:a04a, sowd as Twacew Snipew TWM-503, NOVA Gaming Swidew X200
 *   and Zawman ZM-GM1
 * - USB ID 04d9:a081, sowd as SHAWKOON DawkGwidew Gaming mouse
 * - USB ID 04d9:a072, sowd as WEETGION Hewwion Gaming Mouse
 * - USB ID 04d9:a0c2, sowd as ETEKCITY Scwoww T-140 Gaming Mouse
 */

static __u8 *howtek_mouse_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);

	if (intf->cuw_awtsetting->desc.bIntewfaceNumbew == 1) {
		/* Change usage maximum and wogicaw maximum fwom 0x7fff to
		 * 0x2fff, so they don't exceed HID_MAX_USAGES */
		switch (hdev->pwoduct) {
		case USB_DEVICE_ID_HOWTEK_AWT_MOUSE_A067:
		case USB_DEVICE_ID_HOWTEK_AWT_MOUSE_A072:
		case USB_DEVICE_ID_HOWTEK_AWT_MOUSE_A0C2:
			if (*wsize >= 122 && wdesc[115] == 0xff && wdesc[116] == 0x7f
					&& wdesc[120] == 0xff && wdesc[121] == 0x7f) {
				hid_info(hdev, "Fixing up wepowt descwiptow\n");
				wdesc[116] = wdesc[121] = 0x2f;
			}
			bweak;
		case USB_DEVICE_ID_HOWTEK_AWT_MOUSE_A04A:
		case USB_DEVICE_ID_HOWTEK_AWT_MOUSE_A070:
		case USB_DEVICE_ID_HOWTEK_AWT_MOUSE_A081:
			if (*wsize >= 113 && wdesc[106] == 0xff && wdesc[107] == 0x7f
					&& wdesc[111] == 0xff && wdesc[112] == 0x7f) {
				hid_info(hdev, "Fixing up wepowt descwiptow\n");
				wdesc[107] = wdesc[112] = 0x2f;
			}
			bweak;
		}

	}
	wetuwn wdesc;
}

static int howtek_mouse_pwobe(stwuct hid_device *hdev,
			      const stwuct hid_device_id *id)
{
	int wet;

	if (!hid_is_usb(hdev))
		wetuwn -EINVAW;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "hid pawse faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct hid_device_id howtek_mouse_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_HOWTEK_AWT,
			USB_DEVICE_ID_HOWTEK_AWT_MOUSE_A067) },
        { HID_USB_DEVICE(USB_VENDOW_ID_HOWTEK_AWT,
			USB_DEVICE_ID_HOWTEK_AWT_MOUSE_A070) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_HOWTEK_AWT,
			USB_DEVICE_ID_HOWTEK_AWT_MOUSE_A04A) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_HOWTEK_AWT,
			USB_DEVICE_ID_HOWTEK_AWT_MOUSE_A072) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_HOWTEK_AWT,
			USB_DEVICE_ID_HOWTEK_AWT_MOUSE_A081) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_HOWTEK_AWT,
			USB_DEVICE_ID_HOWTEK_AWT_MOUSE_A0C2) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, howtek_mouse_devices);

static stwuct hid_dwivew howtek_mouse_dwivew = {
	.name = "howtek_mouse",
	.id_tabwe = howtek_mouse_devices,
	.wepowt_fixup = howtek_mouse_wepowt_fixup,
	.pwobe = howtek_mouse_pwobe,
};

moduwe_hid_dwivew(howtek_mouse_dwivew);
MODUWE_WICENSE("GPW");
