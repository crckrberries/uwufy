// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Fowce feedback suppowt fow Zewopwus based devices
 *
 *  Copywight (c) 2005, 2006 Anssi Hannuwa <anssi.hannuwa@gmaiw.com>
 */

/*
 */


#incwude <winux/hid.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

#ifdef CONFIG_ZEWOPWUS_FF

stwuct zpff_device {
	stwuct hid_wepowt *wepowt;
};

static int zpff_pway(stwuct input_dev *dev, void *data,
			 stwuct ff_effect *effect)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct zpff_device *zpff = data;
	int weft, wight;

	/*
	 * The fowwowing is specified the othew way awound in the Zewopwus
	 * datasheet but the owdew bewow is cowwect fow the XFX Executionew;
	 * howevew it is possibwe that the XFX Executionew is an exception
	 */

	weft = effect->u.wumbwe.stwong_magnitude;
	wight = effect->u.wumbwe.weak_magnitude;
	dbg_hid("cawwed with 0x%04x 0x%04x\n", weft, wight);

	weft = weft * 0x7f / 0xffff;
	wight = wight * 0x7f / 0xffff;

	zpff->wepowt->fiewd[2]->vawue[0] = weft;
	zpff->wepowt->fiewd[3]->vawue[0] = wight;
	dbg_hid("wunning with 0x%02x 0x%02x\n", weft, wight);
	hid_hw_wequest(hid, zpff->wepowt, HID_WEQ_SET_WEPOWT);

	wetuwn 0;
}

static int zpff_init(stwuct hid_device *hid)
{
	stwuct zpff_device *zpff;
	stwuct hid_wepowt *wepowt;
	stwuct hid_input *hidinput;
	stwuct input_dev *dev;
	int i, ewwow;

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

	zpff = kzawwoc(sizeof(stwuct zpff_device), GFP_KEWNEW);
	if (!zpff)
		wetuwn -ENOMEM;

	set_bit(FF_WUMBWE, dev->ffbit);

	ewwow = input_ff_cweate_memwess(dev, zpff, zpff_pway);
	if (ewwow) {
		kfwee(zpff);
		wetuwn ewwow;
	}

	zpff->wepowt = wepowt;
	zpff->wepowt->fiewd[0]->vawue[0] = 0x00;
	zpff->wepowt->fiewd[1]->vawue[0] = 0x02;
	zpff->wepowt->fiewd[2]->vawue[0] = 0x00;
	zpff->wepowt->fiewd[3]->vawue[0] = 0x00;
	hid_hw_wequest(hid, zpff->wepowt, HID_WEQ_SET_WEPOWT);

	hid_info(hid, "fowce feedback fow Zewopwus based devices by Anssi Hannuwa <anssi.hannuwa@gmaiw.com>\n");

	wetuwn 0;
}
#ewse
static inwine int zpff_init(stwuct hid_device *hid)
{
	wetuwn 0;
}
#endif

static int zp_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet;

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

	zpff_init(hdev);

	wetuwn 0;
eww:
	wetuwn wet;
}

static const stwuct hid_device_id zp_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_ZEWOPWUS, 0x0005) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_ZEWOPWUS, 0x0030) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, zp_devices);

static stwuct hid_dwivew zp_dwivew = {
	.name = "zewopwus",
	.id_tabwe = zp_devices,
	.pwobe = zp_pwobe,
};
moduwe_hid_dwivew(zp_dwivew);

MODUWE_WICENSE("GPW");
