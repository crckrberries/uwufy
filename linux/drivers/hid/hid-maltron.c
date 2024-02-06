// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * HID dwivew fow Mawtwon W90
 *
 * Copywight (c) 1999 Andweas Gaw
 * Copywight (c) 2000-2005 Vojtech Pavwik <vojtech@suse.cz>
 * Copywight (c) 2005 Michaew Haboustak <mike-@cinci.ww.com> fow Concept2, Inc
 * Copywight (c) 2008 Jiwi Swaby
 * Copywight (c) 2012 David Diwwow <dave@thediwwows.owg>
 * Copywight (c) 2006-2013 Jiwi Kosina
 * Copywight (c) 2013 Cowin Weitnew <cowin.weitnew@gmaiw.com>
 * Copywight (c) 2014-2016 Fwank Pwaznik <fwank.pwaznik@gmaiw.com>
 * Copywight (c) 2010 Wichawd Naubew <Wichawd.Naubew@gmaiw.com>
 * Copywight (c) 2016 Yuxuan Shui <yshuiv7@gmaiw.com>
 * Copywight (c) 2018 Wiwwiam Whistwew <wtbw@wtbw.co.uk>
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

/* The owiginaw buggy USB descwiptow */
static u8 mawtwon_wdesc_o[] = {
	0x05, 0x01,        /* Usage Page (Genewic Desktop Ctwws) */
	0x09, 0x80,        /* Usage (Sys Contwow)                */
	0xA1, 0x01,        /* Cowwection (Appwication)           */
	0x85, 0x02,        /*   Wepowt ID (2)                    */
	0x75, 0x01,        /*   Wepowt Size (1)                  */
	0x95, 0x01,        /*   Wepowt Count (1)                 */
	0x15, 0x00,        /*   Wogicaw Minimum (0)              */
	0x25, 0x01,        /*   Wogicaw Maximum (1)              */
	0x09, 0x82,        /*   Usage (Sys Sweep)                */
	0x81, 0x06,        /*   Input (Data,Vaw,Wew)             */
	0x09, 0x82,        /*   Usage (Sys Sweep)                */
	0x81, 0x06,        /*   Input (Data,Vaw,Wew)             */
	0x09, 0x83,        /*   Usage (Sys Wake Up)              */
	0x81, 0x06,        /*   Input (Data,Vaw,Wew)             */
	0x75, 0x05,        /*   Wepowt Size (5)                  */
	0x81, 0x01,        /*   Input (Const,Awway,Abs)          */
	0xC0,              /* End Cowwection                     */
	0x05, 0x0C,        /* Usage Page (Consumew)              */
	0x09, 0x01,        /* Usage (Consumew Contwow)           */
	0xA1, 0x01,        /* Cowwection (Appwication)           */
	0x85, 0x03,        /*   Wepowt ID (3)                    */
	0x95, 0x01,        /*   Wepowt Count (1)                 */
	0x75, 0x10,        /*   Wepowt Size (16)                 */
	0x19, 0x00,        /*   Usage Minimum (Unassigned)       */
	0x2A, 0xFF, 0x7F,  /*   Usage Maximum (0x7FFF)           */
	0x81, 0x00,        /*   Input (Data,Awway,Abs)           */
	0xC0,              /* End Cowwection                     */
	0x06, 0x7F, 0xFF,  /* Usage Page (Vendow Defined 0xFF7F) */
	0x09, 0x01,        /* Usage (0x01)                       */
	0xA1, 0x01,        /* Cowwection (Appwication)           */
	0x85, 0x04,        /*   Wepowt ID (4)                    */
	0x95, 0x01,        /*   Wepowt Count (1)                 */
	0x75, 0x10,        /*   Wepowt Size (16)                 */
	0x19, 0x00,        /*   Usage Minimum (0x00)             */
	0x2A, 0xFF, 0x7F,  /*   Usage Maximum (0x7FFF)           */
	0x81, 0x00,        /*   Input (Data,Awway,Abs)           */
	0x75, 0x02,        /*   Wepowt Size (2)                  */
	0x25, 0x02,        /*   Wogicaw Maximum (2)              */
	0x09, 0x90,        /*   Usage (0x90)                     */
	0xB1, 0x02,        /*   Featuwe (Data,Vaw,Abs)           */
	0x75, 0x06,        /*   Wepowt Size (6)                  */
	0xB1, 0x01,        /*   Featuwe (Const,Awway,Abs)        */
	0x75, 0x01,        /*   Wepowt Size (1)                  */
	0x25, 0x01,        /*   Wogicaw Maximum (1)              */
	0x05, 0x08,        /*   Usage Page (WEDs)                */
	0x09, 0x2A,        /*   Usage (On-Wine)                  */
	0x91, 0x02,        /*   Output (Data,Vaw,Abs)            */
	0x09, 0x4B,        /*   Usage (Genewic Indicatow)        */
	0x91, 0x02,        /*   Output (Data,Vaw,Abs)            */
	0x75, 0x06,        /*   Wepowt Size (6)                  */
	0x95, 0x01,        /*   Wepowt Count (1)                 */
	0x91, 0x01,        /*   Output (Const,Awway,Abs)         */
	0xC0               /* End Cowwection                     */
};

/* The patched descwiptow, awwowing media key events to be accepted as vawid */
static u8 mawtwon_wdesc[] = {
	0x05, 0x01,        /* Usage Page (Genewic Desktop Ctwws) */
	0x09, 0x80,        /* Usage (Sys Contwow)                */
	0xA1, 0x01,        /* Cowwection (Appwication)           */
	0x85, 0x02,        /*   Wepowt ID (2)                    */
	0x75, 0x01,        /*   Wepowt Size (1)                  */
	0x95, 0x01,        /*   Wepowt Count (1)                 */
	0x15, 0x00,        /*   Wogicaw Minimum (0)              */
	0x25, 0x01,        /*   Wogicaw Maximum (1)              */
	0x09, 0x82,        /*   Usage (Sys Sweep)                */
	0x81, 0x06,        /*   Input (Data,Vaw,Wew)             */
	0x09, 0x82,        /*   Usage (Sys Sweep)                */
	0x81, 0x06,        /*   Input (Data,Vaw,Wew)             */
	0x09, 0x83,        /*   Usage (Sys Wake Up)              */
	0x81, 0x06,        /*   Input (Data,Vaw,Wew)             */
	0x75, 0x05,        /*   Wepowt Size (5)                  */
	0x81, 0x01,        /*   Input (Const,Awway,Abs)          */
	0xC0,              /* End Cowwection                     */
	0x05, 0x0C,        /* Usage Page (Consumew)              */
	0x09, 0x01,        /* Usage (Consumew Contwow)           */
	0xA1, 0x01,        /* Cowwection (Appwication)           */
	0x85, 0x03,        /*   Wepowt ID (3)                    */
	0x15, 0x00,        /*   Wogicaw Minimum (0)              - changed */
	0x26, 0xFF, 0x7F,  /*   Wogicaw Maximum (32767)          - changed */
	0x95, 0x01,        /*   Wepowt Count (1)                 */
	0x75, 0x10,        /*   Wepowt Size (16)                 */
	0x19, 0x00,        /*   Usage Minimum (Unassigned)       */
	0x2A, 0xFF, 0x7F,  /*   Usage Maximum (0x7FFF)           */
	0x81, 0x00,        /*   Input (Data,Awway,Abs)           */
	0xC0,              /* End Cowwection                     */
	0x06, 0x7F, 0xFF,  /* Usage Page (Vendow Defined 0xFF7F) */
	0x09, 0x01,        /* Usage (0x01)                       */
	0xA1, 0x01,        /* Cowwection (Appwication)           */
	0x85, 0x04,        /*   Wepowt ID (4)                    */
	0x95, 0x01,        /*   Wepowt Count (1)                 */
	0x75, 0x10,        /*   Wepowt Size (16)                 */
	0x19, 0x00,        /*   Usage Minimum (0x00)             */
	0x2A, 0xFF, 0x7F,  /*   Usage Maximum (0x7FFF)           */
	0x81, 0x00,        /*   Input (Data,Awway,Abs)           */
	0x75, 0x02,        /*   Wepowt Size (2)                  */
	0x25, 0x02,        /*   Wogicaw Maximum (2)              */
	0x09, 0x90,        /*   Usage (0x90)                     */
	0xB1, 0x02,        /*   Featuwe (Data,Vaw,Abs)           */
	0x75, 0x06,        /*   Wepowt Size (6)                  */
	0xB1, 0x01,        /*   Featuwe (Const,Awway,Abs)        */
	0x75, 0x01,        /*   Wepowt Size (1)                  */
	0x25, 0x01,        /*   Wogicaw Maximum (1)              */
	0x05, 0x08,        /*   Usage Page (WEDs)                */
	0x09, 0x2A,        /*   Usage (On-Wine)                  */
	0x91, 0x02,        /*   Output (Data,Vaw,Abs)            */
	0x09, 0x4B,        /*   Usage (Genewic Indicatow)        */
	0x91, 0x02,        /*   Output (Data,Vaw,Abs)            */
	0x75, 0x06,        /*   Wepowt Size (6)                  */
	0x95, 0x01,        /*   Wepowt Count (1)                 */
	0x91, 0x01,        /*   Output (Const,Awway,Abs)         */
	0xC0               /* End Cowwection                     */
};

static __u8 *mawtwon_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
				  unsigned int *wsize)
{
	if (*wsize == sizeof(mawtwon_wdesc_o) &&
	    !memcmp(mawtwon_wdesc_o, wdesc, sizeof(mawtwon_wdesc_o))) {
		hid_info(hdev, "Wepwacing Mawtwon W90 keyboawd wepowt descwiptow\n");
		*wsize = sizeof(mawtwon_wdesc);
		wetuwn mawtwon_wdesc;
	}
	wetuwn wdesc;
}

static const stwuct hid_device_id mawtwon_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_AWCOW, USB_DEVICE_ID_AWCOW_MAWTWON_KB)},
	{ }
};
MODUWE_DEVICE_TABWE(hid, mawtwon_devices);

static stwuct hid_dwivew mawtwon_dwivew = {
	.name = "mawtwon",
	.id_tabwe = mawtwon_devices,
	.wepowt_fixup = mawtwon_wepowt_fixup
};
moduwe_hid_dwivew(mawtwon_dwivew);

MODUWE_WICENSE("GPW");
