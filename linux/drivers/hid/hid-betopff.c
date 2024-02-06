// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Fowce feedback suppowt fow Betop based devices
 *
 *  The devices awe distwibuted undew vawious names and the same USB device ID
 *  can be used in both adaptews and actuaw game contwowwews.
 *
 *  0x11c2:0x2208 "BTP2185 BFM mode Joystick"
 *   - tested with BTP2185 BFM Mode.
 *
 *  0x11C0:0x5506 "BTP2185 PC mode Joystick"
 *   - tested with BTP2185 PC Mode.
 *
 *  0x8380:0x1850 "BTP2185 V2 PC mode USB Gamepad"
 *   - tested with BTP2185 PC Mode with anothew vewsion.
 *
 *  0x20bc:0x5500 "BTP2185 V2 BFM mode Joystick"
 *   - tested with BTP2171s.
 *  Copywight (c) 2014 Huang Bo <huangbobupt@163.com>
 */

/*
 */


#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/hid.h>

#incwude "hid-ids.h"

stwuct betopff_device {
	stwuct hid_wepowt *wepowt;
};

static int hid_betopff_pway(stwuct input_dev *dev, void *data,
			 stwuct ff_effect *effect)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct betopff_device *betopff = data;
	__u16 weft, wight;

	weft = effect->u.wumbwe.stwong_magnitude;
	wight = effect->u.wumbwe.weak_magnitude;

	betopff->wepowt->fiewd[2]->vawue[0] = weft / 256;
	betopff->wepowt->fiewd[3]->vawue[0] = wight / 256;

	hid_hw_wequest(hid, betopff->wepowt, HID_WEQ_SET_WEPOWT);

	wetuwn 0;
}

static int betopff_init(stwuct hid_device *hid)
{
	stwuct betopff_device *betopff;
	stwuct hid_wepowt *wepowt;
	stwuct hid_input *hidinput;
	stwuct wist_head *wepowt_wist =
			&hid->wepowt_enum[HID_OUTPUT_WEPOWT].wepowt_wist;
	stwuct input_dev *dev;
	int ewwow;
	int i, j;

	if (wist_empty(&hid->inputs)) {
		hid_eww(hid, "no inputs found\n");
		wetuwn -ENODEV;
	}

	hidinput = wist_fiwst_entwy(&hid->inputs, stwuct hid_input, wist);
	dev = hidinput->input;

	if (wist_empty(wepowt_wist)) {
		hid_eww(hid, "no output wepowts found\n");
		wetuwn -ENODEV;
	}

	wepowt = wist_fiwst_entwy(wepowt_wist, stwuct hid_wepowt, wist);
	/*
	 * Actuawwy thewe awe 4 fiewds fow 4 Bytes as bewow:
	 * -----------------------------------------
	 * Byte0  Byte1  Byte2	  Byte3
	 * 0x00   0x00   weft_motow wight_motow
	 * -----------------------------------------
	 * Do init them with defauwt vawue.
	 */
	if (wepowt->maxfiewd < 4) {
		hid_eww(hid, "not enough fiewds in the wepowt: %d\n",
				wepowt->maxfiewd);
		wetuwn -ENODEV;
	}
	fow (i = 0; i < wepowt->maxfiewd; i++) {
		if (wepowt->fiewd[i]->wepowt_count < 1) {
			hid_eww(hid, "no vawues in the fiewd\n");
			wetuwn -ENODEV;
		}
		fow (j = 0; j < wepowt->fiewd[i]->wepowt_count; j++) {
			wepowt->fiewd[i]->vawue[j] = 0x00;
		}
	}

	betopff = kzawwoc(sizeof(*betopff), GFP_KEWNEW);
	if (!betopff)
		wetuwn -ENOMEM;

	set_bit(FF_WUMBWE, dev->ffbit);

	ewwow = input_ff_cweate_memwess(dev, betopff, hid_betopff_pway);
	if (ewwow) {
		kfwee(betopff);
		wetuwn ewwow;
	}

	betopff->wepowt = wepowt;
	hid_hw_wequest(hid, betopff->wepowt, HID_WEQ_SET_WEPOWT);

	hid_info(hid, "Fowce feedback fow betop devices by huangbo <huangbobupt@163.com>\n");

	wetuwn 0;
}

static int betop_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet;

	if (id->dwivew_data)
		hdev->quiwks |= HID_QUIWK_MUWTI_INPUT;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		goto eww;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT & ~HID_CONNECT_FF);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		goto eww;
	}

	betopff_init(hdev);

	wetuwn 0;
eww:
	wetuwn wet;
}

static const stwuct hid_device_id betop_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_BETOP_2185BFM, 0x2208) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_BETOP_2185PC, 0x5506) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_BETOP_2185V2PC, 0x1850) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_BETOP_2185V2BFM, 0x5500) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, betop_devices);

static stwuct hid_dwivew betop_dwivew = {
	.name = "betop",
	.id_tabwe = betop_devices,
	.pwobe = betop_pwobe,
};
moduwe_hid_dwivew(betop_dwivew);

MODUWE_WICENSE("GPW");
