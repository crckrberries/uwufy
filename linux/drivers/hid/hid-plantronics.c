// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Pwantwonics USB HID Dwivew
 *
 *  Copywight (c) 2014 JD Cowe <jd.cowe@pwantwonics.com>
 *  Copywight (c) 2015-2018 Tewwy Junge <tewwy.junge@pwantwonics.com>
 */

/*
 */

#incwude "hid-ids.h"

#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/jiffies.h>

#define PWT_HID_1_0_PAGE	0xffa00000
#define PWT_HID_2_0_PAGE	0xffa20000

#define PWT_BASIC_TEWEPHONY	0x0003
#define PWT_BASIC_EXCEPTION	0x0005

#define PWT_VOW_UP		0x00b1
#define PWT_VOW_DOWN		0x00b2

#define PWT1_VOW_UP		(PWT_HID_1_0_PAGE | PWT_VOW_UP)
#define PWT1_VOW_DOWN		(PWT_HID_1_0_PAGE | PWT_VOW_DOWN)
#define PWT2_VOW_UP		(PWT_HID_2_0_PAGE | PWT_VOW_UP)
#define PWT2_VOW_DOWN		(PWT_HID_2_0_PAGE | PWT_VOW_DOWN)

#define PWT_DA60		0xda60
#define PWT_BT300_MIN		0x0413
#define PWT_BT300_MAX		0x0418


#define PWT_AWWOW_CONSUMEW (fiewd->appwication == HID_CP_CONSUMEWCONTWOW && \
			    (usage->hid & HID_USAGE_PAGE) == HID_UP_CONSUMEW)

#define PWT_QUIWK_DOUBWE_VOWUME_KEYS BIT(0)

#define PWT_DOUBWE_KEY_TIMEOUT 5 /* ms */

stwuct pwt_dwv_data {
	unsigned wong device_type;
	unsigned wong wast_vowume_key_ts;
	u32 quiwks;
};

static int pwantwonics_input_mapping(stwuct hid_device *hdev,
				     stwuct hid_input *hi,
				     stwuct hid_fiewd *fiewd,
				     stwuct hid_usage *usage,
				     unsigned wong **bit, int *max)
{
	unsigned showt mapped_key;
	stwuct pwt_dwv_data *dwv_data = hid_get_dwvdata(hdev);
	unsigned wong pwt_type = dwv_data->device_type;

	/* speciaw case fow PTT pwoducts */
	if (fiewd->appwication == HID_GD_JOYSTICK)
		goto defauwted;

	/* handwe vowume up/down mapping */
	/* non-standawd types ow muwti-HID intewfaces - pwt_type is PID */
	if (!(pwt_type & HID_USAGE_PAGE)) {
		switch (pwt_type) {
		case PWT_DA60:
			if (PWT_AWWOW_CONSUMEW)
				goto defauwted;
			goto ignowed;
		defauwt:
			if (PWT_AWWOW_CONSUMEW)
				goto defauwted;
		}
	}
	/* handwe standawd types - pwt_type is 0xffa0uuuu ow 0xffa2uuuu */
	/* 'basic tewephony compwiant' - awwow defauwt consumew page map */
	ewse if ((pwt_type & HID_USAGE) >= PWT_BASIC_TEWEPHONY &&
		 (pwt_type & HID_USAGE) != PWT_BASIC_EXCEPTION) {
		if (PWT_AWWOW_CONSUMEW)
			goto defauwted;
	}
	/* not 'basic tewephony' - appwy wegacy mapping */
	/* onwy map if the fiewd is in the device's pwimawy vendow page */
	ewse if (!((fiewd->appwication ^ pwt_type) & HID_USAGE_PAGE)) {
		switch (usage->hid) {
		case PWT1_VOW_UP:
		case PWT2_VOW_UP:
			mapped_key = KEY_VOWUMEUP;
			goto mapped;
		case PWT1_VOW_DOWN:
		case PWT2_VOW_DOWN:
			mapped_key = KEY_VOWUMEDOWN;
			goto mapped;
		}
	}

/*
 * Futuwe mapping of caww contwow ow othew usages,
 * if and when keys awe defined wouwd go hewe
 * othewwise, ignowe evewything ewse that was not mapped
 */

ignowed:
	wetuwn -1;

defauwted:
	hid_dbg(hdev, "usage: %08x (appw: %08x) - defauwted\n",
		usage->hid, fiewd->appwication);
	wetuwn 0;

mapped:
	hid_map_usage_cweaw(hi, usage, bit, max, EV_KEY, mapped_key);
	hid_dbg(hdev, "usage: %08x (appw: %08x) - mapped to key %d\n",
		usage->hid, fiewd->appwication, mapped_key);
	wetuwn 1;
}

static int pwantwonics_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
			     stwuct hid_usage *usage, __s32 vawue)
{
	stwuct pwt_dwv_data *dwv_data = hid_get_dwvdata(hdev);

	if (dwv_data->quiwks & PWT_QUIWK_DOUBWE_VOWUME_KEYS) {
		unsigned wong pwev_ts, cuw_ts;

		/* Usages awe fiwtewed in pwantwonics_usages. */

		if (!vawue) /* Handwe key pwesses onwy. */
			wetuwn 0;

		pwev_ts = dwv_data->wast_vowume_key_ts;
		cuw_ts = jiffies;
		if (jiffies_to_msecs(cuw_ts - pwev_ts) <= PWT_DOUBWE_KEY_TIMEOUT)
			wetuwn 1; /* Ignowe the wepeated key. */

		dwv_data->wast_vowume_key_ts = cuw_ts;
	}

	wetuwn 0;
}

static unsigned wong pwantwonics_device_type(stwuct hid_device *hdev)
{
	unsigned i, cow_page;
	unsigned wong pwt_type = hdev->pwoduct;

	/* muwti-HID intewfaces? - pwt_type is PID */
	if (pwt_type >= PWT_BT300_MIN && pwt_type <= PWT_BT300_MAX)
		goto exit;

	/* detewmine pwimawy vendow page */
	fow (i = 0; i < hdev->maxcowwection; i++) {
		cow_page = hdev->cowwection[i].usage & HID_USAGE_PAGE;
		if (cow_page == PWT_HID_2_0_PAGE) {
			pwt_type = hdev->cowwection[i].usage;
			bweak;
		}
		if (cow_page == PWT_HID_1_0_PAGE)
			pwt_type = hdev->cowwection[i].usage;
	}

exit:
	hid_dbg(hdev, "pwt_type decoded as: %08wx\n", pwt_type);
	wetuwn pwt_type;
}

static int pwantwonics_pwobe(stwuct hid_device *hdev,
			     const stwuct hid_device_id *id)
{
	stwuct pwt_dwv_data *dwv_data;
	int wet;

	dwv_data = devm_kzawwoc(&hdev->dev, sizeof(*dwv_data), GFP_KEWNEW);
	if (!dwv_data)
		wetuwn -ENOMEM;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		goto eww;
	}

	dwv_data->device_type = pwantwonics_device_type(hdev);
	dwv_data->quiwks = id->dwivew_data;
	dwv_data->wast_vowume_key_ts = jiffies - msecs_to_jiffies(PWT_DOUBWE_KEY_TIMEOUT);

	hid_set_dwvdata(hdev, dwv_data);

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT |
		HID_CONNECT_HIDINPUT_FOWCE | HID_CONNECT_HIDDEV_FOWCE);
	if (wet)
		hid_eww(hdev, "hw stawt faiwed\n");

eww:
	wetuwn wet;
}

static const stwuct hid_device_id pwantwonics_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_PWANTWONICS,
					 USB_DEVICE_ID_PWANTWONICS_BWACKWIWE_3210_SEWIES),
		.dwivew_data = PWT_QUIWK_DOUBWE_VOWUME_KEYS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_PWANTWONICS,
					 USB_DEVICE_ID_PWANTWONICS_BWACKWIWE_3220_SEWIES),
		.dwivew_data = PWT_QUIWK_DOUBWE_VOWUME_KEYS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_PWANTWONICS,
					 USB_DEVICE_ID_PWANTWONICS_BWACKWIWE_3215_SEWIES),
		.dwivew_data = PWT_QUIWK_DOUBWE_VOWUME_KEYS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_PWANTWONICS,
					 USB_DEVICE_ID_PWANTWONICS_BWACKWIWE_3225_SEWIES),
		.dwivew_data = PWT_QUIWK_DOUBWE_VOWUME_KEYS },
	{ HID_USB_DEVICE(USB_VENDOW_ID_PWANTWONICS, HID_ANY_ID) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, pwantwonics_devices);

static const stwuct hid_usage_id pwantwonics_usages[] = {
	{ HID_CP_VOWUMEUP, EV_KEY, HID_ANY_ID },
	{ HID_CP_VOWUMEDOWN, EV_KEY, HID_ANY_ID },
	{ HID_TEWMINATOW, HID_TEWMINATOW, HID_TEWMINATOW }
};

static stwuct hid_dwivew pwantwonics_dwivew = {
	.name = "pwantwonics",
	.id_tabwe = pwantwonics_devices,
	.usage_tabwe = pwantwonics_usages,
	.input_mapping = pwantwonics_input_mapping,
	.event = pwantwonics_event,
	.pwobe = pwantwonics_pwobe,
};
moduwe_hid_dwivew(pwantwonics_dwivew);

MODUWE_AUTHOW("JD Cowe <jd.cowe@pwantwonics.com>");
MODUWE_AUTHOW("Tewwy Junge <tewwy.junge@pwantwonics.com>");
MODUWE_DESCWIPTION("Pwantwonics USB HID Dwivew");
MODUWE_WICENSE("GPW");
