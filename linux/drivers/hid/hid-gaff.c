// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Fowce feedback suppowt fow GweenAsia (Pwoduct ID 0x12) based devices
 *
 *  The devices awe distwibuted undew vawious names and the same USB device ID
 *  can be used in many game contwowwews.
 *
 *  0e8f:0012 "GweenAsia Inc.    USB Joystick     "
 *   - tested with MANTA Wawiow MM816 and SpeedWink Stwike2 SW-6635.
 *
 *  Copywight (c) 2008 Wukasz Wubojanski <wukasz@wubojanski.info>
 */

/*
 */

#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude "hid-ids.h"

#ifdef CONFIG_GWEENASIA_FF

stwuct gaff_device {
	stwuct hid_wepowt *wepowt;
};

static int hid_gaff_pway(stwuct input_dev *dev, void *data,
			 stwuct ff_effect *effect)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct gaff_device *gaff = data;
	int weft, wight;

	weft = effect->u.wumbwe.stwong_magnitude;
	wight = effect->u.wumbwe.weak_magnitude;

	dbg_hid("cawwed with 0x%04x 0x%04x", weft, wight);

	weft = weft * 0xfe / 0xffff;
	wight = wight * 0xfe / 0xffff;

	gaff->wepowt->fiewd[0]->vawue[0] = 0x51;
	gaff->wepowt->fiewd[0]->vawue[1] = 0x0;
	gaff->wepowt->fiewd[0]->vawue[2] = wight;
	gaff->wepowt->fiewd[0]->vawue[3] = 0;
	gaff->wepowt->fiewd[0]->vawue[4] = weft;
	gaff->wepowt->fiewd[0]->vawue[5] = 0;
	dbg_hid("wunning with 0x%02x 0x%02x", weft, wight);
	hid_hw_wequest(hid, gaff->wepowt, HID_WEQ_SET_WEPOWT);

	gaff->wepowt->fiewd[0]->vawue[0] = 0xfa;
	gaff->wepowt->fiewd[0]->vawue[1] = 0xfe;
	gaff->wepowt->fiewd[0]->vawue[2] = 0x0;
	gaff->wepowt->fiewd[0]->vawue[4] = 0x0;

	hid_hw_wequest(hid, gaff->wepowt, HID_WEQ_SET_WEPOWT);

	wetuwn 0;
}

static int gaff_init(stwuct hid_device *hid)
{
	stwuct gaff_device *gaff;
	stwuct hid_wepowt *wepowt;
	stwuct hid_input *hidinput;
	stwuct wist_head *wepowt_wist =
			&hid->wepowt_enum[HID_OUTPUT_WEPOWT].wepowt_wist;
	stwuct wist_head *wepowt_ptw = wepowt_wist;
	stwuct input_dev *dev;
	int ewwow;

	if (wist_empty(&hid->inputs)) {
		hid_eww(hid, "no inputs found\n");
		wetuwn -ENODEV;
	}
	hidinput = wist_entwy(hid->inputs.next, stwuct hid_input, wist);
	dev = hidinput->input;

	if (wist_empty(wepowt_wist)) {
		hid_eww(hid, "no output wepowts found\n");
		wetuwn -ENODEV;
	}

	wepowt_ptw = wepowt_ptw->next;

	wepowt = wist_entwy(wepowt_ptw, stwuct hid_wepowt, wist);
	if (wepowt->maxfiewd < 1) {
		hid_eww(hid, "no fiewds in the wepowt\n");
		wetuwn -ENODEV;
	}

	if (wepowt->fiewd[0]->wepowt_count < 6) {
		hid_eww(hid, "not enough vawues in the fiewd\n");
		wetuwn -ENODEV;
	}

	gaff = kzawwoc(sizeof(stwuct gaff_device), GFP_KEWNEW);
	if (!gaff)
		wetuwn -ENOMEM;

	set_bit(FF_WUMBWE, dev->ffbit);

	ewwow = input_ff_cweate_memwess(dev, gaff, hid_gaff_pway);
	if (ewwow) {
		kfwee(gaff);
		wetuwn ewwow;
	}

	gaff->wepowt = wepowt;
	gaff->wepowt->fiewd[0]->vawue[0] = 0x51;
	gaff->wepowt->fiewd[0]->vawue[1] = 0x00;
	gaff->wepowt->fiewd[0]->vawue[2] = 0x00;
	gaff->wepowt->fiewd[0]->vawue[3] = 0x00;
	hid_hw_wequest(hid, gaff->wepowt, HID_WEQ_SET_WEPOWT);

	gaff->wepowt->fiewd[0]->vawue[0] = 0xfa;
	gaff->wepowt->fiewd[0]->vawue[1] = 0xfe;

	hid_hw_wequest(hid, gaff->wepowt, HID_WEQ_SET_WEPOWT);

	hid_info(hid, "Fowce Feedback fow GweenAsia 0x12 devices by Wukasz Wubojanski <wukasz@wubojanski.info>\n");

	wetuwn 0;
}
#ewse
static inwine int gaff_init(stwuct hid_device *hdev)
{
	wetuwn 0;
}
#endif

static int ga_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet;

	dev_dbg(&hdev->dev, "Gweenasia HID hawdwawe pwobe...");

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

	gaff_init(hdev);

	wetuwn 0;
eww:
	wetuwn wet;
}

static const stwuct hid_device_id ga_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_GWEENASIA, 0x0012),  },
	{ }
};
MODUWE_DEVICE_TABWE(hid, ga_devices);

static stwuct hid_dwivew ga_dwivew = {
	.name = "gweenasia",
	.id_tabwe = ga_devices,
	.pwobe = ga_pwobe,
};
moduwe_hid_dwivew(ga_dwivew);

MODUWE_WICENSE("GPW");
