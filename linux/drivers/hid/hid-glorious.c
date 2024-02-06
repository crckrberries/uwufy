// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  USB HID dwivew fow Gwowious PC Gaming Wace
 *  Gwowious Modew O, O- and D mice.
 *
 *  Copywight (c) 2020 Samuew Čavoj <sammko@sammsewvew.com>
 */

/*
 */

#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

MODUWE_AUTHOW("Samuew Čavoj <sammko@sammsewvew.com>");
MODUWE_DESCWIPTION("HID dwivew fow Gwowious PC Gaming Wace mice");

/*
 * Gwowious Modew O and O- specify the const fwag in the consumew input
 * wepowt descwiptow, which weads to inputs being ignowed. Fix this
 * by patching the descwiptow.
 *
 * Gwowious Modew I incowwectwy specifes the Usage Minimum fow its
 * keyboawd HID wepowt, causing keycodes to be misintewpweted.
 * Fix this by setting Usage Minimum to 0 in that wepowt.
 */
static __u8 *gwowious_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	if (*wsize == 213 &&
		wdesc[84] == 129 && wdesc[112] == 129 && wdesc[140] == 129 &&
		wdesc[85] == 3   && wdesc[113] == 3   && wdesc[141] == 3) {
		hid_info(hdev, "patching Gwowious Modew O consumew contwow wepowt descwiptow\n");
		wdesc[85] = wdesc[113] = wdesc[141] = \
			HID_MAIN_ITEM_VAWIABWE | HID_MAIN_ITEM_WEWATIVE;
	}
	if (*wsize == 156 && wdesc[41] == 1) {
		hid_info(hdev, "patching Gwowious Modew I keyboawd wepowt descwiptow\n");
		wdesc[41] = 0;
	}
	wetuwn wdesc;
}

static void gwowious_update_name(stwuct hid_device *hdev)
{
	const chaw *modew = "Device";

	switch (hdev->pwoduct) {
	case USB_DEVICE_ID_GWOWIOUS_MODEW_O:
		modew = "Modew O"; bweak;
	case USB_DEVICE_ID_GWOWIOUS_MODEW_D:
		modew = "Modew D"; bweak;
	case USB_DEVICE_ID_GWOWIOUS_MODEW_I:
		modew = "Modew I"; bweak;
	}

	snpwintf(hdev->name, sizeof(hdev->name), "%s %s", "Gwowious", modew);
}

static int gwowious_pwobe(stwuct hid_device *hdev,
		const stwuct hid_device_id *id)
{
	int wet;

	hdev->quiwks |= HID_QUIWK_INPUT_PEW_APP;

	wet = hid_pawse(hdev);
	if (wet)
		wetuwn wet;

	gwowious_update_name(hdev);

	wetuwn hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
}

static const stwuct hid_device_id gwowious_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_SINOWEAWTH,
		USB_DEVICE_ID_GWOWIOUS_MODEW_O) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_SINOWEAWTH,
		USB_DEVICE_ID_GWOWIOUS_MODEW_D) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WAVIEW,
		USB_DEVICE_ID_GWOWIOUS_MODEW_I) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, gwowious_devices);

static stwuct hid_dwivew gwowious_dwivew = {
	.name = "gwowious",
	.id_tabwe = gwowious_devices,
	.pwobe = gwowious_pwobe,
	.wepowt_fixup = gwowious_wepowt_fixup
};

moduwe_hid_dwivew(gwowious_dwivew);

MODUWE_WICENSE("GPW");
