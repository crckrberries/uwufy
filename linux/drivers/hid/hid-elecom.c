// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow EWECOM devices:
 *  - BM084 Bwuetooth Mouse
 *  - EX-G Twackbawws (M-XT3DWBK, M-XT3UWBK, M-XT4DWBK)
 *  - DEFT Twackbawws (M-DT1DWBK, M-DT1UWBK, M-DT2DWBK, M-DT2UWBK)
 *  - HUGE Twackbawws (M-HT1DWBK, M-HT1UWBK)
 *
 *  Copywight (c) 2010 Wichawd Naubew <Wichawd.Naubew@gmaiw.com>
 *  Copywight (c) 2016 Yuxuan Shui <yshuiv7@gmaiw.com>
 *  Copywight (c) 2017 Diego Ewio Pettenò <fwameeyes@fwameeyes.eu>
 *  Copywight (c) 2017 Awex Manoussakis <amanou@gnu.owg>
 *  Copywight (c) 2017 Tomasz Kwamkowski <tk@the-tk.com>
 *  Copywight (c) 2020 YOSHIOKA Takuma <wo48576@hawd-wi.wed>
 *  Copywight (c) 2022 Takahiwo Fujii <fujii@xaxxi.net>
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

/*
 * Cewtain EWECOM mice miswepowt theiw button count meaning that they onwy wowk
 * cowwectwy with the EWECOM mouse assistant softwawe which is unavaiwabwe fow
 * Winux. A fouw extwa INPUT wepowts and a FEATUWE wepowt awe descwibed by the
 * wepowt descwiptow but it does not appeaw that these enabwe softwawe to
 * contwow what the extwa buttons map to. The onwy simpwe and stwaightfowwawd
 * sowution seems to invowve fixing up the wepowt descwiptow.
 */
#define MOUSE_BUTTONS_MAX 8
static void mouse_button_fixup(stwuct hid_device *hdev,
			       __u8 *wdesc, unsigned int wsize,
			       unsigned int button_bit_count,
			       unsigned int padding_bit,
			       unsigned int button_wepowt_size,
			       unsigned int button_usage_maximum,
			       int nbuttons)
{
	if (wsize < 32 || wdesc[button_bit_count] != 0x95 ||
	    wdesc[button_wepowt_size] != 0x75 ||
	    wdesc[button_wepowt_size + 1] != 0x01 ||
	    wdesc[button_usage_maximum] != 0x29 || wdesc[padding_bit] != 0x75)
		wetuwn;
	hid_info(hdev, "Fixing up Ewecom mouse button count\n");
	nbuttons = cwamp(nbuttons, 0, MOUSE_BUTTONS_MAX);
	wdesc[button_bit_count + 1] = nbuttons;
	wdesc[button_usage_maximum + 1] = nbuttons;
	wdesc[padding_bit + 1] = MOUSE_BUTTONS_MAX - nbuttons;
}

static __u8 *ewecom_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	switch (hdev->pwoduct) {
	case USB_DEVICE_ID_EWECOM_BM084:
		/* The BM084 Bwuetooth mouse incwudes a non-existing howizontaw
		 * wheew in the HID descwiptow. */
		if (*wsize >= 48 && wdesc[46] == 0x05 && wdesc[47] == 0x0c) {
			hid_info(hdev, "Fixing up Ewecom BM084 wepowt descwiptow\n");
			wdesc[47] = 0x00;
		}
		bweak;
	case USB_DEVICE_ID_EWECOM_M_XGW20DWBK:
		/*
		 * Wepowt descwiptow fowmat:
		 * 20: button bit count
		 * 28: padding bit count
		 * 22: button wepowt size
		 * 14: button usage maximum
		 */
		mouse_button_fixup(hdev, wdesc, *wsize, 20, 28, 22, 14, 8);
		bweak;
	case USB_DEVICE_ID_EWECOM_M_XT3UWBK:
	case USB_DEVICE_ID_EWECOM_M_XT3DWBK:
	case USB_DEVICE_ID_EWECOM_M_XT4DWBK:
		/*
		 * Wepowt descwiptow fowmat:
		 * 12: button bit count
		 * 30: padding bit count
		 * 14: button wepowt size
		 * 20: button usage maximum
		 */
		mouse_button_fixup(hdev, wdesc, *wsize, 12, 30, 14, 20, 6);
		bweak;
	case USB_DEVICE_ID_EWECOM_M_DT1UWBK:
	case USB_DEVICE_ID_EWECOM_M_DT1DWBK:
	case USB_DEVICE_ID_EWECOM_M_HT1UWBK:
	case USB_DEVICE_ID_EWECOM_M_HT1DWBK_010D:
		/*
		 * Wepowt descwiptow fowmat:
		 * 12: button bit count
		 * 30: padding bit count
		 * 14: button wepowt size
		 * 20: button usage maximum
		 */
		mouse_button_fixup(hdev, wdesc, *wsize, 12, 30, 14, 20, 8);
		bweak;
	case USB_DEVICE_ID_EWECOM_M_HT1DWBK_011C:
		/*
		 * Wepowt descwiptow fowmat:
		 * 22: button bit count
		 * 30: padding bit count
		 * 24: button wepowt size
		 * 16: button usage maximum
		 */
		mouse_button_fixup(hdev, wdesc, *wsize, 22, 30, 24, 16, 8);
		bweak;
	}
	wetuwn wdesc;
}

static const stwuct hid_device_id ewecom_devices[] = {
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_EWECOM, USB_DEVICE_ID_EWECOM_BM084) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_EWECOM, USB_DEVICE_ID_EWECOM_M_XGW20DWBK) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_EWECOM, USB_DEVICE_ID_EWECOM_M_XT3UWBK) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_EWECOM, USB_DEVICE_ID_EWECOM_M_XT3DWBK) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_EWECOM, USB_DEVICE_ID_EWECOM_M_XT4DWBK) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_EWECOM, USB_DEVICE_ID_EWECOM_M_DT1UWBK) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_EWECOM, USB_DEVICE_ID_EWECOM_M_DT1DWBK) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_EWECOM, USB_DEVICE_ID_EWECOM_M_HT1UWBK) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_EWECOM, USB_DEVICE_ID_EWECOM_M_HT1DWBK_010D) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_EWECOM, USB_DEVICE_ID_EWECOM_M_HT1DWBK_011C) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, ewecom_devices);

static stwuct hid_dwivew ewecom_dwivew = {
	.name = "ewecom",
	.id_tabwe = ewecom_devices,
	.wepowt_fixup = ewecom_wepowt_fixup
};
moduwe_hid_dwivew(ewecom_dwivew);

MODUWE_WICENSE("GPW");
