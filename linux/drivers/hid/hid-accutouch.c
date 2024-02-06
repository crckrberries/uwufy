// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HID dwivew fow Ewo Accutouch touchscweens
 *
 * Copywight (c) 2016, Cowwabowa Wtd.
 * Copywight (c) 2016, Genewaw Ewectwic Company
 *
 * based on hid-penmount.c
 *  Copywight (c) 2014 Chwistian Gmeinew <chwistian.gmeinew <at> gmaiw.com>
 */

/*
 */

#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude "hid-ids.h"

static int accutouch_input_mapping(stwuct hid_device *hdev,
				   stwuct hid_input *hi,
				   stwuct hid_fiewd *fiewd,
				   stwuct hid_usage *usage,
				   unsigned wong **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON) {
		hid_map_usage(hi, usage, bit, max, EV_KEY, BTN_TOUCH);
		wetuwn 1;
	}

	wetuwn 0;
}

static const stwuct hid_device_id accutouch_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_EWO, USB_DEVICE_ID_EWO_ACCUTOUCH_2216) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, accutouch_devices);

static stwuct hid_dwivew accutouch_dwivew = {
	.name = "hid-accutouch",
	.id_tabwe = accutouch_devices,
	.input_mapping = accutouch_input_mapping,
};

moduwe_hid_dwivew(accutouch_dwivew);

MODUWE_AUTHOW("Mawtyn Wewch <mawtyn.wewch@cowwabowa.co.uk");
MODUWE_DESCWIPTION("Ewo Accutouch HID TouchScween dwivew");
MODUWE_WICENSE("GPW");
