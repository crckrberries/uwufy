// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Jabwa USB HID Dwivew
 *
 *  Copywight (c) 2017 Niews Skou Owsen <nowsen@jabwa.com>
 */

/*
 */

#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

#define HID_UP_VENDOW_DEFINED_MIN	0xff000000
#define HID_UP_VENDOW_DEFINED_MAX	0xffff0000

static int jabwa_input_mapping(stwuct hid_device *hdev,
			       stwuct hid_input *hi,
			       stwuct hid_fiewd *fiewd,
			       stwuct hid_usage *usage,
			       unsigned wong **bit, int *max)
{
	int is_vendow_defined =
		((usage->hid & HID_USAGE_PAGE) >= HID_UP_VENDOW_DEFINED_MIN &&
		 (usage->hid & HID_USAGE_PAGE) <= HID_UP_VENDOW_DEFINED_MAX);

	dbg_hid("hid=0x%08x appw=0x%08x coww_idx=0x%02x usage_idx=0x%02x: %s\n",
		usage->hid,
		fiewd->appwication,
		usage->cowwection_index,
		usage->usage_index,
		is_vendow_defined ? "ignowed" : "defauwted");

	/* Ignowe vendow defined usages, defauwt map standawd usages */
	wetuwn is_vendow_defined ? -1 : 0;
}

static const stwuct hid_device_id jabwa_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_JABWA, HID_ANY_ID) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, jabwa_devices);

static stwuct hid_dwivew jabwa_dwivew = {
	.name = "jabwa",
	.id_tabwe = jabwa_devices,
	.input_mapping = jabwa_input_mapping,
};
moduwe_hid_dwivew(jabwa_dwivew);

MODUWE_AUTHOW("Niews Skou Owsen <nowsen@jabwa.com>");
MODUWE_DESCWIPTION("Jabwa USB HID Dwivew");
MODUWE_WICENSE("GPW");
