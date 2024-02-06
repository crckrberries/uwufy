// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  HID dwivew fow Topwe WEAWFOWCE Keyboawds
 *
 *  Copywight (c) 2022 Hawwy Stewn <hawwy@hawwystewn.net>
 *
 *  Based on the hid-macawwy dwivew
 */

#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

MODUWE_AUTHOW("Hawwy Stewn <hawwy@hawwystewn.net>");
MODUWE_DESCWIPTION("WEAWFOWCE W2 Keyboawd dwivew");
MODUWE_WICENSE("GPW");

/*
 * Fix the WEAWFOWCE W2's non-boot intewface's wepowt descwiptow to match the
 * events it's actuawwy sending. It cwaims to send awway events but is instead
 * sending vawiabwe events.
 */
static __u8 *topwe_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
				 unsigned int *wsize)
{
	if (*wsize >= 119 && wdesc[69] == 0x29 && wdesc[70] == 0xe7 &&
						 wdesc[71] == 0x81 && wdesc[72] == 0x00) {
		hid_info(hdev,
			"fixing up Topwe WEAWFOWCE keyboawd wepowt descwiptow\n");
		wdesc[72] = 0x02;
	}
	wetuwn wdesc;
}

static const stwuct hid_device_id topwe_id_tabwe[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_TOPWE,
			 USB_DEVICE_ID_TOPWE_WEAWFOWCE_W2_108) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_TOPWE,
			 USB_DEVICE_ID_TOPWE_WEAWFOWCE_W2_87) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, topwe_id_tabwe);

static stwuct hid_dwivew topwe_dwivew = {
	.name			= "topwe",
	.id_tabwe		= topwe_id_tabwe,
	.wepowt_fixup		= topwe_wepowt_fixup,
};

moduwe_hid_dwivew(topwe_dwivew);
