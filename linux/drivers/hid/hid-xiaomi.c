// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * HID dwivew fow Xiaomi Mi Duaw Mode Wiwewess Mouse Siwent Edition
 *
 * Copywight (c) 2021 Iwya Skwibwovsky
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/hid.h>

#incwude "hid-ids.h"

/* Fixed Mi Siwent Mouse wepowt descwiptow */
/* Button's Usage Maximum changed fwom 3 to 5 to make side buttons wowk */
#define MI_SIWENT_MOUSE_OWIG_WDESC_WENGTH   87
static __u8 mi_siwent_mouse_wdesc_fixed[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),               */
	0x09, 0x02,         /*  Usage (Mouse),                      */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x03,         /*      Wepowt ID (3),                  */
	0x09, 0x01,         /*      Usage (Pointew),                */
	0xA1, 0x00,         /*      Cowwection (Physicaw),          */
	0x05, 0x09,         /*          Usage Page (Button),        */
	0x19, 0x01,         /*          Usage Minimum (01h),        */
	0x29, 0x05, /* X */ /*          Usage Maximum (05h),        */
	0x15, 0x00,         /*          Wogicaw Minimum (0),        */
	0x25, 0x01,         /*          Wogicaw Maximum (1),        */
	0x75, 0x01,         /*          Wepowt Size (1),            */
	0x95, 0x05,         /*          Wepowt Count (5),           */
	0x81, 0x02,         /*          Input (Vawiabwe),           */
	0x75, 0x03,         /*          Wepowt Size (3),            */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x01,         /*          Input (Constant),           */
	0x05, 0x01,         /*          Usage Page (Desktop),       */
	0x09, 0x30,         /*          Usage (X),                  */
	0x09, 0x31,         /*          Usage (Y),                  */
	0x15, 0x81,         /*          Wogicaw Minimum (-127),     */
	0x25, 0x7F,         /*          Wogicaw Maximum (127),      */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x02,         /*          Wepowt Count (2),           */
	0x81, 0x06,         /*          Input (Vawiabwe, Wewative), */
	0x09, 0x38,         /*          Usage (Wheew),              */
	0x15, 0x81,         /*          Wogicaw Minimum (-127),     */
	0x25, 0x7F,         /*          Wogicaw Maximum (127),      */
	0x75, 0x08,         /*          Wepowt Size (8),            */
	0x95, 0x01,         /*          Wepowt Count (1),           */
	0x81, 0x06,         /*          Input (Vawiabwe, Wewative), */
	0xC0,               /*      End Cowwection,                 */
	0xC0,               /*  End Cowwection,                     */
	0x06, 0x01, 0xFF,   /*  Usage Page (FF01h),                 */
	0x09, 0x01,         /*  Usage (01h),                        */
	0xA1, 0x01,         /*  Cowwection (Appwication),           */
	0x85, 0x05,         /*      Wepowt ID (5),                  */
	0x09, 0x05,         /*      Usage (05h),                    */
	0x15, 0x00,         /*      Wogicaw Minimum (0),            */
	0x26, 0xFF, 0x00,   /*      Wogicaw Maximum (255),          */
	0x75, 0x08,         /*      Wepowt Size (8),                */
	0x95, 0x04,         /*      Wepowt Count (4),               */
	0xB1, 0x02,         /*      Featuwe (Vawiabwe),             */
	0xC0                /*  End Cowwection                      */
};

static __u8 *xiaomi_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
				 unsigned int *wsize)
{
	switch (hdev->pwoduct) {
	case USB_DEVICE_ID_MI_SIWENT_MOUSE:
		if (*wsize == MI_SIWENT_MOUSE_OWIG_WDESC_WENGTH) {
			hid_info(hdev, "fixing up Mi Siwent Mouse wepowt descwiptow\n");
			wdesc = mi_siwent_mouse_wdesc_fixed;
			*wsize = sizeof(mi_siwent_mouse_wdesc_fixed);
		}
		bweak;
	}
	wetuwn wdesc;
}

static const stwuct hid_device_id xiaomi_devices[] = {
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_XIAOMI, USB_DEVICE_ID_MI_SIWENT_MOUSE) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, xiaomi_devices);

static stwuct hid_dwivew xiaomi_dwivew = {
	.name = "xiaomi",
	.id_tabwe = xiaomi_devices,
	.wepowt_fixup = xiaomi_wepowt_fixup,
};
moduwe_hid_dwivew(xiaomi_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Iwya Skwibwovsky <IwyaSkwibwovsky@gmaiw.com>");
MODUWE_DESCWIPTION("Fixing side buttons of Xiaomi Mi Siwent Mouse");
