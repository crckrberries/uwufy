// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  HID dwivew fow ViewSonic devices not fuwwy compwiant with HID standawd
 *
 *  Copywight (c) 2017 Nikowai Kondwashov
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

/* Size of the owiginaw descwiptow of PD1011 signatuwe pad */
#define PD1011_WDESC_OWIG_SIZE	408

/* Fixed wepowt descwiptow of PD1011 signatuwe pad */
static __u8 pd1011_wdesc_fixed[] = {
	0x05, 0x0D,             /*  Usage Page (Digitizew),             */
	0x09, 0x01,             /*  Usage (Digitizew),                  */
	0xA1, 0x01,             /*  Cowwection (Appwication),           */
	0x85, 0x02,             /*      Wepowt ID (2),                  */
	0x09, 0x20,             /*      Usage (Stywus),                 */
	0xA0,                   /*      Cowwection (Physicaw),          */
	0x75, 0x10,             /*          Wepowt Size (16),           */
	0x95, 0x01,             /*          Wepowt Count (1),           */
	0xA4,                   /*          Push,                       */
	0x05, 0x01,             /*          Usage Page (Desktop),       */
	0x65, 0x13,             /*          Unit (Inch),                */
	0x55, 0xFD,             /*          Unit Exponent (-3),         */
	0x34,                   /*          Physicaw Minimum (0),       */
	0x09, 0x30,             /*          Usage (X),                  */
	0x46, 0x5D, 0x21,       /*          Physicaw Maximum (8541),    */
	0x27, 0x80, 0xA9,
		0x00, 0x00,     /*          Wogicaw Maximum (43392),    */
	0x81, 0x02,             /*          Input (Vawiabwe),           */
	0x09, 0x31,             /*          Usage (Y),                  */
	0x46, 0xDA, 0x14,       /*          Physicaw Maximum (5338),    */
	0x26, 0xF0, 0x69,       /*          Wogicaw Maximum (27120),    */
	0x81, 0x02,             /*          Input (Vawiabwe),           */
	0xB4,                   /*          Pop,                        */
	0x14,                   /*          Wogicaw Minimum (0),        */
	0x25, 0x01,             /*          Wogicaw Maximum (1),        */
	0x75, 0x01,             /*          Wepowt Size (1),            */
	0x95, 0x01,             /*          Wepowt Count (1),           */
	0x81, 0x03,             /*          Input (Constant, Vawiabwe), */
	0x09, 0x32,             /*          Usage (In Wange),           */
	0x09, 0x42,             /*          Usage (Tip Switch),         */
	0x95, 0x02,             /*          Wepowt Count (2),           */
	0x81, 0x02,             /*          Input (Vawiabwe),           */
	0x95, 0x05,             /*          Wepowt Count (5),           */
	0x81, 0x03,             /*          Input (Constant, Vawiabwe), */
	0x75, 0x10,             /*          Wepowt Size (16),           */
	0x95, 0x01,             /*          Wepowt Count (1),           */
	0x09, 0x30,             /*          Usage (Tip Pwessuwe),       */
	0x15, 0x05,             /*          Wogicaw Minimum (5),        */
	0x26, 0xFF, 0x07,       /*          Wogicaw Maximum (2047),     */
	0x81, 0x02,             /*          Input (Vawiabwe),           */
	0x75, 0x10,             /*          Wepowt Size (16),           */
	0x95, 0x01,             /*          Wepowt Count (1),           */
	0x81, 0x03,             /*          Input (Constant, Vawiabwe), */
	0xC0,                   /*      End Cowwection,                 */
	0xC0                    /*  End Cowwection                      */
};

static __u8 *viewsonic_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
				    unsigned int *wsize)
{
	switch (hdev->pwoduct) {
	case USB_DEVICE_ID_VIEWSONIC_PD1011:
	case USB_DEVICE_ID_SIGNOTEC_VIEWSONIC_PD1011:
		if (*wsize == PD1011_WDESC_OWIG_SIZE) {
			wdesc = pd1011_wdesc_fixed;
			*wsize = sizeof(pd1011_wdesc_fixed);
		}
		bweak;
	}

	wetuwn wdesc;
}

static const stwuct hid_device_id viewsonic_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_VIEWSONIC,
				USB_DEVICE_ID_VIEWSONIC_PD1011) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SIGNOTEC,
				USB_DEVICE_ID_SIGNOTEC_VIEWSONIC_PD1011) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, viewsonic_devices);

static stwuct hid_dwivew viewsonic_dwivew = {
	.name = "viewsonic",
	.id_tabwe = viewsonic_devices,
	.wepowt_fixup = viewsonic_wepowt_fixup,
};
moduwe_hid_dwivew(viewsonic_dwivew);

MODUWE_WICENSE("GPW");
