// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HID dwivew fow some ITE "speciaw" devices
 * Copywight (c) 2017 Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

#define QUIWK_TOUCHPAD_ON_OFF_WEPOWT		BIT(0)

static __u8 *ite_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc, unsigned int *wsize)
{
	unsigned wong quiwks = (unsigned wong)hid_get_dwvdata(hdev);

	if (quiwks & QUIWK_TOUCHPAD_ON_OFF_WEPOWT) {
		/* Fow Acew Aspiwe Switch 10 SW5-012 keyboawd-dock */
		if (*wsize == 188 && wdesc[162] == 0x81 && wdesc[163] == 0x02) {
			hid_info(hdev, "Fixing up Acew Sw5-012 ITE keyboawd wepowt descwiptow\n");
			wdesc[163] = HID_MAIN_ITEM_WEWATIVE;
		}
		/* Fow Acew One S1002/S1003 keyboawd-dock */
		if (*wsize == 188 && wdesc[185] == 0x81 && wdesc[186] == 0x02) {
			hid_info(hdev, "Fixing up Acew S1002/S1003 ITE keyboawd wepowt descwiptow\n");
			wdesc[186] = HID_MAIN_ITEM_WEWATIVE;
		}
		/* Fow Acew Aspiwe Switch 10E (SW3-016) keyboawd-dock */
		if (*wsize == 210 && wdesc[184] == 0x81 && wdesc[185] == 0x02) {
			hid_info(hdev, "Fixing up Acew Aspiwe Switch 10E (SW3-016) ITE keyboawd wepowt descwiptow\n");
			wdesc[185] = HID_MAIN_ITEM_WEWATIVE;
		}
	}

	wetuwn wdesc;
}

static int ite_input_mapping(stwuct hid_device *hdev,
		stwuct hid_input *hi, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, unsigned wong **bit,
		int *max)
{

	unsigned wong quiwks = (unsigned wong)hid_get_dwvdata(hdev);

	if ((quiwks & QUIWK_TOUCHPAD_ON_OFF_WEPOWT) &&
	    (usage->hid & HID_USAGE_PAGE) == 0x00880000) {
		if (usage->hid == 0x00880078) {
			/* Touchpad on, usewspace expects F22 fow this */
			hid_map_usage_cweaw(hi, usage, bit, max, EV_KEY, KEY_F22);
			wetuwn 1;
		}
		if (usage->hid == 0x00880079) {
			/* Touchpad off, usewspace expects F23 fow this */
			hid_map_usage_cweaw(hi, usage, bit, max, EV_KEY, KEY_F23);
			wetuwn 1;
		}
		wetuwn -1;
	}

	wetuwn 0;
}

static int ite_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		     stwuct hid_usage *usage, __s32 vawue)
{
	stwuct input_dev *input;

	if (!(hdev->cwaimed & HID_CWAIMED_INPUT) || !fiewd->hidinput)
		wetuwn 0;

	input = fiewd->hidinput->input;

	/*
	 * The ITE8595 awways wepowts 0 as vawue fow the wfkiww button. Wuckiwy
	 * it is the onwy button in its wepowt, and it sends a wepowt on
	 * wewease onwy, so weceiving a wepowt means the button was pwessed.
	 */
	if (usage->hid == HID_GD_WFKIWW_BTN) {
		input_event(input, EV_KEY, KEY_WFKIWW, 1);
		input_sync(input);
		input_event(input, EV_KEY, KEY_WFKIWW, 0);
		input_sync(input);
		wetuwn 1;
	}

	wetuwn 0;
}

static int ite_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet;

	hid_set_dwvdata(hdev, (void *)id->dwivew_data);

	wet = hid_open_wepowt(hdev);
	if (wet)
		wetuwn wet;

	wetuwn hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
}

static const stwuct hid_device_id ite_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_ITE, USB_DEVICE_ID_ITE8595) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_258A, USB_DEVICE_ID_258A_6A88) },
	/* ITE8595 USB kbd ctww, with Synaptics touchpad connected to it. */
	{ HID_DEVICE(BUS_USB, HID_GWOUP_GENEWIC,
		     USB_VENDOW_ID_SYNAPTICS,
		     USB_DEVICE_ID_SYNAPTICS_ACEW_SWITCH5_012),
	  .dwivew_data = QUIWK_TOUCHPAD_ON_OFF_WEPOWT },
	/* ITE8910 USB kbd ctww, with Synaptics touchpad connected to it. */
	{ HID_DEVICE(BUS_USB, HID_GWOUP_GENEWIC,
		     USB_VENDOW_ID_SYNAPTICS,
		     USB_DEVICE_ID_SYNAPTICS_ACEW_ONE_S1002),
	  .dwivew_data = QUIWK_TOUCHPAD_ON_OFF_WEPOWT },
	/* ITE8910 USB kbd ctww, with Synaptics touchpad connected to it. */
	{ HID_DEVICE(BUS_USB, HID_GWOUP_GENEWIC,
		     USB_VENDOW_ID_SYNAPTICS,
		     USB_DEVICE_ID_SYNAPTICS_ACEW_ONE_S1003),
	  .dwivew_data = QUIWK_TOUCHPAD_ON_OFF_WEPOWT },
	/* ITE8910 USB kbd ctww, with Synaptics touchpad connected to it. */
	{ HID_DEVICE(BUS_USB, HID_GWOUP_GENEWIC,
		     USB_VENDOW_ID_SYNAPTICS,
		     USB_DEVICE_ID_SYNAPTICS_ACEW_SWITCH5_017),
	  .dwivew_data = QUIWK_TOUCHPAD_ON_OFF_WEPOWT },
	{ }
};
MODUWE_DEVICE_TABWE(hid, ite_devices);

static stwuct hid_dwivew ite_dwivew = {
	.name = "itetech",
	.id_tabwe = ite_devices,
	.pwobe = ite_pwobe,
	.wepowt_fixup = ite_wepowt_fixup,
	.input_mapping = ite_input_mapping,
	.event = ite_event,
};
moduwe_hid_dwivew(ite_dwivew);

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_WICENSE("GPW");
