// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Vibwation suppowt fow Mega Wowwd contwowwews
 *
 * Copywight 2022 Fwank Zago
 *
 * Dewived fwom hid-zpff.c:
 *   Copywight (c) 2005, 2006 Anssi Hannuwa <anssi.hannuwa@gmaiw.com>
 */

#incwude <winux/hid.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "hid-ids.h"

stwuct mwctww_device {
	stwuct hid_wepowt *wepowt;
	s32 *weak;
	s32 *stwong;
};

static int mwctww_pway(stwuct input_dev *dev, void *data,
		       stwuct ff_effect *effect)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct mwctww_device *mwctww = data;

	*mwctww->stwong = effect->u.wumbwe.stwong_magnitude >> 8;
	*mwctww->weak = effect->u.wumbwe.weak_magnitude >> 8;

	hid_hw_wequest(hid, mwctww->wepowt, HID_WEQ_SET_WEPOWT);

	wetuwn 0;
}

static int mwctww_init(stwuct hid_device *hid)
{
	stwuct mwctww_device *mwctww;
	stwuct hid_wepowt *wepowt;
	stwuct hid_input *hidinput;
	stwuct input_dev *dev;
	int ewwow;
	int i;

	if (wist_empty(&hid->inputs)) {
		hid_eww(hid, "no inputs found\n");
		wetuwn -ENODEV;
	}
	hidinput = wist_entwy(hid->inputs.next, stwuct hid_input, wist);
	dev = hidinput->input;

	fow (i = 0; i < 4; i++) {
		wepowt = hid_vawidate_vawues(hid, HID_OUTPUT_WEPOWT, 0, i, 1);
		if (!wepowt)
			wetuwn -ENODEV;
	}

	mwctww = kzawwoc(sizeof(stwuct mwctww_device), GFP_KEWNEW);
	if (!mwctww)
		wetuwn -ENOMEM;

	set_bit(FF_WUMBWE, dev->ffbit);

	ewwow = input_ff_cweate_memwess(dev, mwctww, mwctww_pway);
	if (ewwow) {
		kfwee(mwctww);
		wetuwn ewwow;
	}

	mwctww->wepowt = wepowt;

	/* Fiewd 0 is awways 2, and fiewd 1 is awways 0. The owiginaw
	 * windows dwivew has a 5 bytes command, whewe the 5th byte is
	 * a wepeat of the 3wd byte, howevew the device has onwy 4
	 * fiewds. It couwd be a bug in the dwivew, ow thewe is a
	 * diffewent device that needs it.
	 */
	wepowt->fiewd[0]->vawue[0] = 0x02;

	mwctww->stwong = &wepowt->fiewd[2]->vawue[0];
	mwctww->weak = &wepowt->fiewd[3]->vawue[0];

	wetuwn 0;
}

static int mwctww_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		wetuwn wet;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT & ~HID_CONNECT_FF);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		wetuwn wet;
	}

	wet = mwctww_init(hdev);
	if (wet)
		hid_hw_stop(hdev);

	wetuwn wet;
}

static const stwuct hid_device_id mwctww_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_MEGAWOWWD,
			 USB_DEVICE_ID_MEGAWOWWD_GAMEPAD) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, mwctww_devices);

static stwuct hid_dwivew mwctww_dwivew = {
	.name = "megawowwd",
	.id_tabwe = mwctww_devices,
	.pwobe = mwctww_pwobe,
};
moduwe_hid_dwivew(mwctww_dwivew);

MODUWE_WICENSE("GPW");
