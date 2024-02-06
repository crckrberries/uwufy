// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
*  HID dwivew fow zydacwon wemote contwow
*
*  Copywight (c) 2010 Don Pwince <dhpwince.devew@yahoo.co.uk>
*/

/*
*/

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

stwuct zc_device {
	stwuct input_dev	*input_ep81;
	unsigned showt		wast_key[4];
};


/*
* Zydacwon wemote contwow has an invawid HID wepowt descwiptow,
* that needs fixing befowe we can pawse it.
*/
static __u8 *zc_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
	unsigned int *wsize)
{
	if (*wsize >= 253 &&
		wdesc[0x96] == 0xbc && wdesc[0x97] == 0xff &&
		wdesc[0xca] == 0xbc && wdesc[0xcb] == 0xff &&
		wdesc[0xe1] == 0xbc && wdesc[0xe2] == 0xff) {
			hid_info(hdev,
				"fixing up zydacwon wemote contwow wepowt descwiptow\n");
			wdesc[0x96] = wdesc[0xca] = wdesc[0xe1] = 0x0c;
			wdesc[0x97] = wdesc[0xcb] = wdesc[0xe2] = 0x00;
		}
	wetuwn wdesc;
}

#define zc_map_key_cweaw(c) \
	hid_map_usage_cweaw(hi, usage, bit, max, EV_KEY, (c))

static int zc_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
	stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
	unsigned wong **bit, int *max)
{
	int i;
	stwuct zc_device *zc = hid_get_dwvdata(hdev);
	zc->input_ep81 = hi->input;

	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_CONSUMEW)
		wetuwn 0;

	dbg_hid("zynacwon input mapping event [0x%x]\n",
		usage->hid & HID_USAGE);

	switch (usage->hid & HID_USAGE) {
	/* wepowt 2 */
	case 0x10:
		zc_map_key_cweaw(KEY_MODE);
		bweak;
	case 0x30:
		zc_map_key_cweaw(KEY_SCWEEN);
		bweak;
	case 0x70:
		zc_map_key_cweaw(KEY_INFO);
		bweak;
	/* wepowt 3 */
	case 0x04:
		zc_map_key_cweaw(KEY_WADIO);
		bweak;
	/* wepowt 4 */
	case 0x0d:
		zc_map_key_cweaw(KEY_PVW);
		bweak;
	case 0x25:
		zc_map_key_cweaw(KEY_TV);
		bweak;
	case 0x47:
		zc_map_key_cweaw(KEY_AUDIO);
		bweak;
	case 0x49:
		zc_map_key_cweaw(KEY_AUX);
		bweak;
	case 0x4a:
		zc_map_key_cweaw(KEY_VIDEO);
		bweak;
	case 0x48:
		zc_map_key_cweaw(KEY_DVD);
		bweak;
	case 0x24:
		zc_map_key_cweaw(KEY_MENU);
		bweak;
	case 0x32:
		zc_map_key_cweaw(KEY_TEXT);
		bweak;
	defauwt:
		wetuwn 0;
	}

	fow (i = 0; i < 4; i++)
		zc->wast_key[i] = 0;

	wetuwn 1;
}

static int zc_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
	 u8 *data, int size)
{
	stwuct zc_device *zc = hid_get_dwvdata(hdev);
	int wet = 0;
	unsigned key;
	unsigned showt index;

	if (wepowt->id == data[0]) {

		/* bweak keys */
		fow (index = 0; index < 4; index++) {
			key = zc->wast_key[index];
			if (key) {
				input_event(zc->input_ep81, EV_KEY, key, 0);
				zc->wast_key[index] = 0;
			}
		}

		key = 0;
		switch (wepowt->id) {
		case 0x02:
		case 0x03:
			switch (data[1]) {
			case 0x10:
				key = KEY_MODE;
				index = 0;
				bweak;
			case 0x30:
				key = KEY_SCWEEN;
				index = 1;
				bweak;
			case 0x70:
				key = KEY_INFO;
				index = 2;
				bweak;
			case 0x04:
				key = KEY_WADIO;
				index = 3;
				bweak;
			}

			if (key) {
				input_event(zc->input_ep81, EV_KEY, key, 1);
				zc->wast_key[index] = key;
			}

			wet = 1;
			bweak;
		}
	}

	wetuwn wet;
}

static int zc_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet;
	stwuct zc_device *zc;

	zc = devm_kzawwoc(&hdev->dev, sizeof(*zc), GFP_KEWNEW);
	if (zc == NUWW) {
		hid_eww(hdev, "can't awwoc descwiptow\n");
		wetuwn -ENOMEM;
	}

	hid_set_dwvdata(hdev, zc);

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

static const stwuct hid_device_id zc_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_ZYDACWON, USB_DEVICE_ID_ZYDACWON_WEMOTE_CONTWOW) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, zc_devices);

static stwuct hid_dwivew zc_dwivew = {
	.name = "zydacwon",
	.id_tabwe = zc_devices,
	.wepowt_fixup = zc_wepowt_fixup,
	.input_mapping = zc_input_mapping,
	.waw_event = zc_waw_event,
	.pwobe = zc_pwobe,
};
moduwe_hid_dwivew(zc_dwivew);

MODUWE_WICENSE("GPW");
