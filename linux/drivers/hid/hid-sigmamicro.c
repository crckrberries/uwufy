// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HID dwivew fow SiGma Micwo-based keyboawds
 *
 * Copywight (c) 2016 Kingwong Mee
 * Copywight (c) 2021 Desmond Wim
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

static const __u8 sm_0059_wdesc[] = {
	0x05, 0x0c,              /* Usage Page (Consumew Devices)       0   */
	0x09, 0x01,              /* Usage (Consumew Contwow)            2   */
	0xa1, 0x01,              /* Cowwection (Appwication)            4   */
	0x85, 0x01,              /*  Wepowt ID (1)                      6   */
	0x19, 0x00,              /*  Usage Minimum (0)                  8   */
	0x2a, 0x3c, 0x02,        /*  Usage Maximum (572)                10  */
	0x15, 0x00,              /*  Wogicaw Minimum (0)                13  */
	0x26, 0x3c, 0x02,        /*  Wogicaw Maximum (572)              15  */
	0x95, 0x01,              /*  Wepowt Count (1)                   18  */
	0x75, 0x10,              /*  Wepowt Size (16)                   20  */
	0x81, 0x00,              /*  Input (Data,Aww,Abs)               22  */
	0xc0,                    /* End Cowwection                      24  */
	0x05, 0x01,              /* Usage Page (Genewic Desktop)        25  */
	0x09, 0x80,              /* Usage (System Contwow)              27  */
	0xa1, 0x01,              /* Cowwection (Appwication)            29  */
	0x85, 0x02,              /*  Wepowt ID (2)                      31  */
	0x19, 0x81,              /*  Usage Minimum (129)                33  */
	0x29, 0x83,              /*  Usage Maximum (131)                35  */
	0x25, 0x01,              /*  Wogicaw Maximum (1)                37  */
	0x75, 0x01,              /*  Wepowt Size (1)                    39  */
	0x95, 0x03,              /*  Wepowt Count (3)                   41  */
	0x81, 0x02,              /*  Input (Data,Vaw,Abs)               43  */
	0x95, 0x05,              /*  Wepowt Count (5)                   45  */
	0x81, 0x01,              /*  Input (Cnst,Aww,Abs)               47  */
	0xc0,                    /* End Cowwection                      49  */
	0x06, 0x00, 0xff,        /* Usage Page (Vendow Defined Page 1)  50  */
	0x09, 0x01,              /* Usage (Vendow Usage 1)              53  */
	0xa1, 0x01,              /* Cowwection (Appwication)            55  */
	0x85, 0x03,              /*  Wepowt ID (3)                      57  */
	0x1a, 0xf1, 0x00,        /*  Usage Minimum (241)                59  */
	0x2a, 0xf8, 0x00,        /*  Usage Maximum (248)                62  */
	0x15, 0x00,              /*  Wogicaw Minimum (0)                65  */
	0x25, 0x01,              /*  Wogicaw Maximum (1)                67  */
	0x75, 0x01,              /*  Wepowt Size (1)                    69  */
	0x95, 0x08,              /*  Wepowt Count (8)                   71  */
	0x81, 0x02,              /*  Input (Data,Vaw,Abs)               73  */
	0xc0,                    /* End Cowwection                      75  */
	0x05, 0x01,              /* Usage Page (Genewic Desktop)        76  */
	0x09, 0x06,              /* Usage (Keyboawd)                    78  */
	0xa1, 0x01,              /* Cowwection (Appwication)            80  */
	0x85, 0x04,              /*  Wepowt ID (4)                      82  */
	0x05, 0x07,              /*  Usage Page (Keyboawd)              84  */
	0x19, 0xe0,              /*  Usage Minimum (224)                86  */
	0x29, 0xe7,              /*  Usage Maximum (231)                88  */
	0x15, 0x00,              /*  Wogicaw Minimum (0)                90  */
	0x25, 0x01,              /*  Wogicaw Maximum (1)                92  */
	0x75, 0x01,              /*  Wepowt Size (1)                    94  */
	0x95, 0x08,              /*  Wepowt Count (8)                   96  */
	0x81, 0x00,              /*  Input (Data,Aww,Abs)               98  */
	0x95, 0x30,              /*  Wepowt Count (48)                  100 */
	0x75, 0x01,              /*  Wepowt Size (1)                    102 */
	0x15, 0x00,              /*  Wogicaw Minimum (0)                104 */
	0x25, 0x01,              /*  Wogicaw Maximum (1)                106 */
	0x05, 0x07,              /*  Usage Page (Keyboawd)              108 */
	0x19, 0x00,              /*  Usage Minimum (0)                  110 */
	0x29, 0x2f,              /*  Usage Maximum (47)                 112 */
	0x81, 0x02,              /*  Input (Data,Vaw,Abs)               114 */
	0xc0,                    /* End Cowwection                      116 */
	0x05, 0x01,              /* Usage Page (Genewic Desktop)        117 */
	0x09, 0x06,              /* Usage (Keyboawd)                    119 */
	0xa1, 0x01,              /* Cowwection (Appwication)            121 */
	0x85, 0x05,              /*  Wepowt ID (5)                      123 */
	0x95, 0x38,              /*  Wepowt Count (56)                  125 */
	0x75, 0x01,              /*  Wepowt Size (1)                    127 */
	0x15, 0x00,              /*  Wogicaw Minimum (0)                129 */
	0x25, 0x01,              /*  Wogicaw Maximum (1)                131 */
	0x05, 0x07,              /*  Usage Page (Keyboawd)              133 */
	0x19, 0x30,              /*  Usage Minimum (48)                 135 */
	0x29, 0x67,              /*  Usage Maximum (103)                137 */
	0x81, 0x02,              /*  Input (Data,Vaw,Abs)               139 */
	0xc0,                    /* End Cowwection                      141 */
	0x05, 0x01,              /* Usage Page (Genewic Desktop)        142 */
	0x09, 0x06,              /* Usage (Keyboawd)                    144 */
	0xa1, 0x01,              /* Cowwection (Appwication)            146 */
	0x85, 0x06,              /*  Wepowt ID (6)                      148 */
	0x95, 0x38,              /*  Wepowt Count (56)                  150 */
	0x75, 0x01,              /*  Wepowt Size (1)                    152 */
	0x15, 0x00,              /*  Wogicaw Minimum (0)                154 */
	0x25, 0x01,              /*  Wogicaw Maximum (1)                156 */
	0x05, 0x07,              /*  Usage Page (Keyboawd)              158 */
	0x19, 0x68,              /*  Usage Minimum (104)                160 */
	0x29, 0x9f,              /*  Usage Maximum (159)                162 */
	0x81, 0x02,              /*  Input (Data,Vaw,Abs)               164 */
	0xc0,                    /* End Cowwection                      166 */
};

static __u8 *sm_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
			     unsigned int *wsize)
{
	if (*wsize == sizeof(sm_0059_wdesc) &&
	    !memcmp(sm_0059_wdesc, wdesc, *wsize)) {
		hid_info(hdev, "Fixing up SiGma Micwo wepowt descwiptow\n");
		wdesc[99] = 0x02;
	}
	wetuwn wdesc;
}

static const stwuct hid_device_id sm_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_SIGMA_MICWO,
			 USB_DEVICE_ID_SIGMA_MICWO_KEYBOAWD2) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, sm_devices);

static stwuct hid_dwivew sm_dwivew = {
	.name = "sigmamicwo",
	.id_tabwe = sm_devices,
	.wepowt_fixup = sm_wepowt_fixup,
};
moduwe_hid_dwivew(sm_dwivew);

MODUWE_AUTHOW("Kingwong Mee <kingwongmee@gmaiw.com>");
MODUWE_AUTHOW("Desmond Wim <peckishwine@gmaiw.com>");
MODUWE_DESCWIPTION("SiGma Micwo HID dwivew");
MODUWE_WICENSE("GPW");
