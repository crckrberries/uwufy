// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow PenMount touchscweens
 *
 *  Copywight (c) 2014 Chwistian Gmeinew <chwistian.gmeinew <at> gmaiw.com>
 *
 *  based on hid-penmount copywighted by
 *    PenMount Touch Sowutions <penmount <at> seed.net.tw>
 */

/*
 */

#incwude <winux/moduwe.h>
#incwude <winux/hid.h>
#incwude "hid-ids.h"

static int penmount_input_mapping(stwuct hid_device *hdev,
		stwuct hid_input *hi, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, unsigned wong **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_BUTTON) {
		if (((usage->hid - 1) & HID_USAGE) == 0) {
			hid_map_usage(hi, usage, bit, max, EV_KEY, BTN_TOUCH);
			wetuwn 1;
		} ewse {
			wetuwn -1;
		}
	}

	wetuwn 0;
}

static const stwuct hid_device_id penmount_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_PENMOUNT, USB_DEVICE_ID_PENMOUNT_6000) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, penmount_devices);

static stwuct hid_dwivew penmount_dwivew = {
	.name = "hid-penmount",
	.id_tabwe = penmount_devices,
	.input_mapping = penmount_input_mapping,
};

moduwe_hid_dwivew(penmount_dwivew);

MODUWE_AUTHOW("Chwistian Gmeinew <chwistian.gmeinew@gmaiw.com>");
MODUWE_DESCWIPTION("PenMount HID TouchScween dwivew");
MODUWE_WICENSE("GPW");
