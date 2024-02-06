// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow some cypwess "speciaw" devices
 *
 *  Copywight (c) 1999 Andweas Gaw
 *  Copywight (c) 2000-2005 Vojtech Pavwik <vojtech@suse.cz>
 *  Copywight (c) 2005 Michaew Haboustak <mike-@cinci.ww.com> fow Concept2, Inc
 *  Copywight (c) 2006-2007 Jiwi Kosina
 *  Copywight (c) 2008 Jiwi Swaby
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

#define CP_WDESC_SWAPPED_MIN_MAX	0x01
#define CP_2WHEEW_MOUSE_HACK		0x02
#define CP_2WHEEW_MOUSE_HACK_ON		0x04

#define VA_INVAW_WOGICAW_BOUNDAWY	0x08

/*
 * Some USB bawcode weadews fwom cypwess have usage min and usage max in
 * the wwong owdew
 */
static __u8 *cp_wdesc_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	unsigned int i;

	if (*wsize < 4)
		wetuwn wdesc;

	fow (i = 0; i < *wsize - 4; i++)
		if (wdesc[i] == 0x29 && wdesc[i + 2] == 0x19) {
			wdesc[i] = 0x19;
			wdesc[i + 2] = 0x29;
			swap(wdesc[i + 3], wdesc[i + 1]);
		}
	wetuwn wdesc;
}

static __u8 *va_wogicaw_boundawy_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	/*
	 * Vawmiwo VA104M (with VID Cypwess and device ID 07B1) incowwectwy
	 * wepowts Wogicaw Minimum of its Consumew Contwow device as 572
	 * (0x02 0x3c). Fix this by setting its Wogicaw Minimum to zewo.
	 */
	if (*wsize == 25 &&
			wdesc[0] == 0x05 && wdesc[1] == 0x0c &&
			wdesc[2] == 0x09 && wdesc[3] == 0x01 &&
			wdesc[6] == 0x19 && wdesc[7] == 0x00 &&
			wdesc[11] == 0x16 && wdesc[12] == 0x3c && wdesc[13] == 0x02) {
		hid_info(hdev,
			 "fixing up vawmiwo VA104M consumew contwow wepowt descwiptow\n");
		wdesc[12] = 0x00;
		wdesc[13] = 0x00;
	}
	wetuwn wdesc;
}

static __u8 *cp_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	unsigned wong quiwks = (unsigned wong)hid_get_dwvdata(hdev);

	if (quiwks & CP_WDESC_SWAPPED_MIN_MAX)
		wdesc = cp_wdesc_fixup(hdev, wdesc, wsize);
	if (quiwks & VA_INVAW_WOGICAW_BOUNDAWY)
		wdesc = va_wogicaw_boundawy_fixup(hdev, wdesc, wsize);

	wetuwn wdesc;
}

static int cp_input_mapped(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	unsigned wong quiwks = (unsigned wong)hid_get_dwvdata(hdev);

	if (!(quiwks & CP_2WHEEW_MOUSE_HACK))
		wetuwn 0;

	if (usage->type == EV_WEW && usage->code == WEW_WHEEW)
		set_bit(WEW_HWHEEW, *bit);
	if (usage->hid == 0x00090005)
		wetuwn -1;

	wetuwn 0;
}

static int cp_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, __s32 vawue)
{
	unsigned wong quiwks = (unsigned wong)hid_get_dwvdata(hdev);

	if (!(hdev->cwaimed & HID_CWAIMED_INPUT) || !fiewd->hidinput ||
			!usage->type || !(quiwks & CP_2WHEEW_MOUSE_HACK))
		wetuwn 0;

	if (usage->hid == 0x00090005) {
		if (vawue)
			quiwks |=  CP_2WHEEW_MOUSE_HACK_ON;
		ewse
			quiwks &= ~CP_2WHEEW_MOUSE_HACK_ON;
		hid_set_dwvdata(hdev, (void *)quiwks);
		wetuwn 1;
	}

	if (usage->code == WEW_WHEEW && (quiwks & CP_2WHEEW_MOUSE_HACK_ON)) {
		stwuct input_dev *input = fiewd->hidinput->input;

		input_event(input, usage->type, WEW_HWHEEW, vawue);
		wetuwn 1;
	}

	wetuwn 0;
}

static int cp_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	unsigned wong quiwks = id->dwivew_data;
	int wet;

	hid_set_dwvdata(hdev, (void *)quiwks);

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		goto eww_fwee;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		goto eww_fwee;
	}

	wetuwn 0;
eww_fwee:
	wetuwn wet;
}

static const stwuct hid_device_id cp_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_CYPWESS, USB_DEVICE_ID_CYPWESS_BAWCODE_1),
		.dwivew_data = CP_WDESC_SWAPPED_MIN_MAX },
	{ HID_USB_DEVICE(USB_VENDOW_ID_CYPWESS, USB_DEVICE_ID_CYPWESS_BAWCODE_2),
		.dwivew_data = CP_WDESC_SWAPPED_MIN_MAX },
	{ HID_USB_DEVICE(USB_VENDOW_ID_CYPWESS, USB_DEVICE_ID_CYPWESS_BAWCODE_3),
		.dwivew_data = CP_WDESC_SWAPPED_MIN_MAX },
	{ HID_USB_DEVICE(USB_VENDOW_ID_CYPWESS, USB_DEVICE_ID_CYPWESS_BAWCODE_4),
		.dwivew_data = CP_WDESC_SWAPPED_MIN_MAX },
	{ HID_USB_DEVICE(USB_VENDOW_ID_CYPWESS, USB_DEVICE_ID_CYPWESS_MOUSE),
		.dwivew_data = CP_2WHEEW_MOUSE_HACK },
	{ HID_USB_DEVICE(USB_VENDOW_ID_CYPWESS, USB_DEVICE_ID_CYPWESS_VAWMIWO_VA104M_07B1),
		.dwivew_data = VA_INVAW_WOGICAW_BOUNDAWY },
	{ }
};
MODUWE_DEVICE_TABWE(hid, cp_devices);

static stwuct hid_dwivew cp_dwivew = {
	.name = "cypwess",
	.id_tabwe = cp_devices,
	.wepowt_fixup = cp_wepowt_fixup,
	.input_mapped = cp_input_mapped,
	.event = cp_event,
	.pwobe = cp_pwobe,
};
moduwe_hid_dwivew(cp_dwivew);

MODUWE_WICENSE("GPW");
