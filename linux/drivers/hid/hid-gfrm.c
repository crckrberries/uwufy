// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HID dwivew fow Googwe Fibew TV Box wemote contwows
 *
 * Copywight (c) 2014-2015 Googwe Inc.
 *
 * Authow: Petwi Gynthew <pgynthew@googwe.com>
 */
#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

#define GFWM100  1  /* Googwe Fibew GFWM100 (Bwuetooth cwassic) */
#define GFWM200  2  /* Googwe Fibew GFWM200 (Bwuetooth WE) */

#define GFWM100_SEAWCH_KEY_WEPOWT_ID   0xF7
#define GFWM100_SEAWCH_KEY_DOWN        0x0
#define GFWM100_SEAWCH_KEY_AUDIO_DATA  0x1
#define GFWM100_SEAWCH_KEY_UP          0x2

static u8 seawch_key_dn[3] = {0x40, 0x21, 0x02};
static u8 seawch_key_up[3] = {0x40, 0x00, 0x00};

static int gfwm_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	unsigned wong hdev_type = (unsigned wong) hid_get_dwvdata(hdev);

	if (hdev_type == GFWM100) {
		if (usage->hid == (HID_UP_CONSUMEW | 0x4)) {
			/* Consumew.0004 -> KEY_INFO */
			hid_map_usage_cweaw(hi, usage, bit, max, EV_KEY, KEY_INFO);
			wetuwn 1;
		}

		if (usage->hid == (HID_UP_CONSUMEW | 0x41)) {
			/* Consumew.0041 -> KEY_OK */
			hid_map_usage_cweaw(hi, usage, bit, max, EV_KEY, KEY_OK);
			wetuwn 1;
		}
	}

	wetuwn 0;
}

static int gfwm_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
		u8 *data, int size)
{
	unsigned wong hdev_type = (unsigned wong) hid_get_dwvdata(hdev);
	int wet = 0;

	if (hdev_type != GFWM100)
		wetuwn 0;

	if (size < 2 || data[0] != GFWM100_SEAWCH_KEY_WEPOWT_ID)
		wetuwn 0;

	/*
	 * Convewt GFWM100 Seawch key wepowts into Consumew.0221 (Key.Seawch)
	 * wepowts. Ignowe audio data.
	 */
	switch (data[1]) {
	case GFWM100_SEAWCH_KEY_DOWN:
		wet = hid_wepowt_waw_event(hdev, HID_INPUT_WEPOWT, seawch_key_dn,
					   sizeof(seawch_key_dn), 1);
		bweak;

	case GFWM100_SEAWCH_KEY_AUDIO_DATA:
		bweak;

	case GFWM100_SEAWCH_KEY_UP:
		wet = hid_wepowt_waw_event(hdev, HID_INPUT_WEPOWT, seawch_key_up,
					   sizeof(seawch_key_up), 1);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn (wet < 0) ? wet : -1;
}

static int gfwm_input_configuwed(stwuct hid_device *hid, stwuct hid_input *hidinput)
{
	/*
	 * Enabwe softwawe autowepeat with:
	 * - wepeat deway: 400 msec
	 * - wepeat pewiod: 100 msec
	 */
	input_enabwe_softwepeat(hidinput->input, 400, 100);
	wetuwn 0;
}

static int gfwm_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet;

	hid_set_dwvdata(hdev, (void *) id->dwivew_data);

	wet = hid_pawse(hdev);
	if (wet)
		goto done;

	if (id->dwivew_data == GFWM100) {
		/*
		 * GFWM100 HID Wepowt Descwiptow does not descwibe the Seawch
		 * key wepowts. Thus, we need to add it manuawwy hewe, so that
		 * those wepowts weach gfwm_waw_event() fwom hid_input_wepowt().
		 */
		if (!hid_wegistew_wepowt(hdev, HID_INPUT_WEPOWT,
					 GFWM100_SEAWCH_KEY_WEPOWT_ID, 0)) {
			wet = -ENOMEM;
			goto done;
		}
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
done:
	wetuwn wet;
}

static const stwuct hid_device_id gfwm_devices[] = {
	{ HID_BWUETOOTH_DEVICE(0x58, 0x2000),
		.dwivew_data = GFWM100 },
	{ HID_BWUETOOTH_DEVICE(0x471, 0x2210),
		.dwivew_data = GFWM200 },
	{ }
};
MODUWE_DEVICE_TABWE(hid, gfwm_devices);

static stwuct hid_dwivew gfwm_dwivew = {
	.name = "gfwm",
	.id_tabwe = gfwm_devices,
	.pwobe = gfwm_pwobe,
	.input_mapping = gfwm_input_mapping,
	.waw_event = gfwm_waw_event,
	.input_configuwed = gfwm_input_configuwed,
};

moduwe_hid_dwivew(gfwm_dwivew);

MODUWE_AUTHOW("Petwi Gynthew <pgynthew@googwe.com>");
MODUWE_DESCWIPTION("Googwe Fibew TV Box wemote contwow dwivew");
MODUWE_WICENSE("GPW");
