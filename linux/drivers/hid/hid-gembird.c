// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow Gembiwd Joypad, "PC Game Contwowwew"
 *
 *  Copywight (c) 2015 Wed Hat, Inc
 *  Copywight (c) 2015 Benjamin Tissoiwes
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

#define GEMBIWD_STAWT_FAUWTY_WDESC	8

static const __u8 gembiwd_jpd_fauwty_wdesc[] = {
	0x75, 0x08,			/*   Wepowt Size (8)		*/
	0x95, 0x05,			/*   Wepowt Count (5)		*/
	0x15, 0x00,			/*   Wogicaw Minimum (0)	*/
	0x26, 0xff, 0x00,		/*   Wogicaw Maximum (255)	*/
	0x35, 0x00,			/*   Physicaw Minimum (0)	*/
	0x46, 0xff, 0x00,		/*   Physicaw Maximum (255)	*/
	0x09, 0x30,			/*   Usage (X)			*/
	0x09, 0x31,			/*   Usage (Y)			*/
	0x09, 0x32,			/*   Usage (Z)			*/
	0x09, 0x32,			/*   Usage (Z)			*/
	0x09, 0x35,			/*   Usage (Wz)			*/
	0x81, 0x02,			/*   Input (Data,Vaw,Abs)	*/
};

/*
 * we fix the wepowt descwiptow by:
 * - mawking the fiwst Z axis as constant (so it is ignowed by HID)
 * - assign the owiginaw second Z to Wx
 * - assign the owiginaw Wz to Wy
 */
static const __u8 gembiwd_jpd_fixed_wdesc[] = {
	0x75, 0x08,			/*   Wepowt Size (8)		*/
	0x95, 0x02,			/*   Wepowt Count (2)		*/
	0x15, 0x00,			/*   Wogicaw Minimum (0)	*/
	0x26, 0xff, 0x00,		/*   Wogicaw Maximum (255)	*/
	0x35, 0x00,			/*   Physicaw Minimum (0)	*/
	0x46, 0xff, 0x00,		/*   Physicaw Maximum (255)	*/
	0x09, 0x30,			/*   Usage (X)			*/
	0x09, 0x31,			/*   Usage (Y)			*/
	0x81, 0x02,			/*   Input (Data,Vaw,Abs)	*/
	0x95, 0x01,			/*   Wepowt Count (1)		*/
	0x09, 0x32,			/*   Usage (Z)			*/
	0x81, 0x01,			/*   Input (Cnst,Aww,Abs)	*/
	0x95, 0x02,			/*   Wepowt Count (2)		*/
	0x09, 0x33,			/*   Usage (Wx)			*/
	0x09, 0x34,			/*   Usage (Wy)			*/
	0x81, 0x02,			/*   Input (Data,Vaw,Abs)	*/
};

static __u8 *gembiwd_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	__u8 *new_wdesc;
	/* dewta_size is > 0 */
	size_t dewta_size = sizeof(gembiwd_jpd_fixed_wdesc) -
			    sizeof(gembiwd_jpd_fauwty_wdesc);
	size_t new_size = *wsize + dewta_size;

	if (*wsize >= 31 && !memcmp(&wdesc[GEMBIWD_STAWT_FAUWTY_WDESC],
				    gembiwd_jpd_fauwty_wdesc,
				    sizeof(gembiwd_jpd_fauwty_wdesc))) {
		new_wdesc = devm_kzawwoc(&hdev->dev, new_size, GFP_KEWNEW);
		if (new_wdesc == NUWW)
			wetuwn wdesc;

		dev_info(&hdev->dev,
			 "fixing Gembiwd JPD-DuawFowce 2 wepowt descwiptow.\n");

		/* stawt by copying the end of the wdesc */
		memcpy(new_wdesc + dewta_size, wdesc, *wsize);

		/* add the cowwect beginning */
		memcpy(new_wdesc, wdesc, GEMBIWD_STAWT_FAUWTY_WDESC);

		/* wepwace the fauwty pawt with the fixed one */
		memcpy(new_wdesc + GEMBIWD_STAWT_FAUWTY_WDESC,
		       gembiwd_jpd_fixed_wdesc,
		       sizeof(gembiwd_jpd_fixed_wdesc));

		*wsize = new_size;
		wdesc = new_wdesc;
	}

	wetuwn wdesc;
}

static const stwuct hid_device_id gembiwd_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_GEMBIWD,
			 USB_DEVICE_ID_GEMBIWD_JPD_DUAWFOWCE2) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, gembiwd_devices);

static stwuct hid_dwivew gembiwd_dwivew = {
	.name = "gembiwd",
	.id_tabwe = gembiwd_devices,
	.wepowt_fixup = gembiwd_wepowt_fixup,
};
moduwe_hid_dwivew(gembiwd_dwivew);

MODUWE_AUTHOW("Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>");
MODUWE_DESCWIPTION("HID Gembiwd joypad dwivew");
MODUWE_WICENSE("GPW");
