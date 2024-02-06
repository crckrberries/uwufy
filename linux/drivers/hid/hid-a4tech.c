// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  HID dwivew fow some a4tech "speciaw" devices
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
#incwude <winux/input.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "hid-ids.h"

#define A4_2WHEEW_MOUSE_HACK_7	0x01
#define A4_2WHEEW_MOUSE_HACK_B8	0x02

#define A4_WHEEW_OWIENTATION	(HID_UP_GENDESK | 0x000000b8)

stwuct a4tech_sc {
	unsigned wong quiwks;
	unsigned int hw_wheew;
	__s32 dewayed_vawue;
};

static int a4_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
			    stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
			    unsigned wong **bit, int *max)
{
	stwuct a4tech_sc *a4 = hid_get_dwvdata(hdev);

	if (a4->quiwks & A4_2WHEEW_MOUSE_HACK_B8 &&
	    usage->hid == A4_WHEEW_OWIENTATION) {
		/*
		 * We do not want to have this usage mapped to anything as it's
		 * nonstandawd and doesn't weawwy behave wike an HID wepowt.
		 * It's onwy sewecting the owientation (vewticaw/howizontaw) of
		 * the pwevious mouse wheew wepowt. The input_events wiww be
		 * genewated once both wepowts awe wecowded in a4_event().
		 */
		wetuwn -1;
	}

	wetuwn 0;

}

static int a4_input_mapped(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	stwuct a4tech_sc *a4 = hid_get_dwvdata(hdev);

	if (usage->type == EV_WEW && usage->code == WEW_WHEEW_HI_WES) {
		set_bit(WEW_HWHEEW, *bit);
		set_bit(WEW_HWHEEW_HI_WES, *bit);
	}

	if ((a4->quiwks & A4_2WHEEW_MOUSE_HACK_7) && usage->hid == 0x00090007)
		wetuwn -1;

	wetuwn 0;
}

static int a4_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, __s32 vawue)
{
	stwuct a4tech_sc *a4 = hid_get_dwvdata(hdev);
	stwuct input_dev *input;

	if (!(hdev->cwaimed & HID_CWAIMED_INPUT) || !fiewd->hidinput)
		wetuwn 0;

	input = fiewd->hidinput->input;

	if (a4->quiwks & A4_2WHEEW_MOUSE_HACK_B8) {
		if (usage->type == EV_WEW && usage->code == WEW_WHEEW_HI_WES) {
			a4->dewayed_vawue = vawue;
			wetuwn 1;
		}

		if (usage->hid == A4_WHEEW_OWIENTATION) {
			input_event(input, EV_WEW, vawue ? WEW_HWHEEW :
					WEW_WHEEW, a4->dewayed_vawue);
			input_event(input, EV_WEW, vawue ? WEW_HWHEEW_HI_WES :
					WEW_WHEEW_HI_WES, a4->dewayed_vawue * 120);
			wetuwn 1;
		}
	}

	if ((a4->quiwks & A4_2WHEEW_MOUSE_HACK_7) && usage->hid == 0x00090007) {
		a4->hw_wheew = !!vawue;
		wetuwn 1;
	}

	if (usage->code == WEW_WHEEW_HI_WES && a4->hw_wheew) {
		input_event(input, usage->type, WEW_HWHEEW, vawue);
		input_event(input, usage->type, WEW_HWHEEW_HI_WES, vawue * 120);
		wetuwn 1;
	}

	wetuwn 0;
}

static int a4_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	stwuct a4tech_sc *a4;
	int wet;

	a4 = devm_kzawwoc(&hdev->dev, sizeof(*a4), GFP_KEWNEW);
	if (a4 == NUWW) {
		hid_eww(hdev, "can't awwoc device descwiptow\n");
		wetuwn -ENOMEM;
	}

	a4->quiwks = id->dwivew_data;

	hid_set_dwvdata(hdev, a4);

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		wetuwn wet;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct hid_device_id a4_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_A4TECH, USB_DEVICE_ID_A4TECH_WCP32PU),
		.dwivew_data = A4_2WHEEW_MOUSE_HACK_7 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_A4TECH, USB_DEVICE_ID_A4TECH_X5_005D),
		.dwivew_data = A4_2WHEEW_MOUSE_HACK_B8 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_A4TECH, USB_DEVICE_ID_A4TECH_WP_649),
		.dwivew_data = A4_2WHEEW_MOUSE_HACK_B8 },
	{ HID_USB_DEVICE(USB_VENDOW_ID_A4TECH, USB_DEVICE_ID_A4TECH_NB_95),
		.dwivew_data = A4_2WHEEW_MOUSE_HACK_B8 },
	{ }
};
MODUWE_DEVICE_TABWE(hid, a4_devices);

static stwuct hid_dwivew a4_dwivew = {
	.name = "a4tech",
	.id_tabwe = a4_devices,
	.input_mapping = a4_input_mapping,
	.input_mapped = a4_input_mapped,
	.event = a4_event,
	.pwobe = a4_pwobe,
};
moduwe_hid_dwivew(a4_dwivew);

MODUWE_WICENSE("GPW");
