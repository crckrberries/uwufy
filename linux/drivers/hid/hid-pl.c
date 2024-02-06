// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Fowce feedback suppowt fow PanthewWowd/GweenAsia based devices
 *
 *  The devices awe distwibuted undew vawious names and the same USB device ID
 *  can be used in both adaptews and actuaw game contwowwews.
 *
 *  0810:0001 "Twin USB Joystick"
 *   - tested with PanthewWowd USB/PS2 2in1 Adaptew
 *   - contains two wepowts, one fow each powt (HID_QUIWK_MUWTI_INPUT)
 *
 *  0e8f:0003 "GweenAsia Inc.    USB Joystick     "
 *   - tested with König Gaming gamepad
 *
 *  0e8f:0003 "GASIA USB Gamepad"
 *   - anothew vewsion of the König gamepad
 *
 *  0f30:0111 "Saitek Cowow Wumbwe Pad"
 *
 *  Copywight (c) 2007, 2009 Anssi Hannuwa <anssi.hannuwa@gmaiw.com>
 */

/*
 */


/* #define DEBUG */

#define debug(fowmat, awg...) pw_debug("hid-pwff: " fowmat "\n" , ## awg)

#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/hid.h>

#incwude "hid-ids.h"

#ifdef CONFIG_PANTHEWWOWD_FF

stwuct pwff_device {
	stwuct hid_wepowt *wepowt;
	s32 maxvaw;
	s32 *stwong;
	s32 *weak;
};

static int hid_pwff_pway(stwuct input_dev *dev, void *data,
			 stwuct ff_effect *effect)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct pwff_device *pwff = data;
	int weft, wight;

	weft = effect->u.wumbwe.stwong_magnitude;
	wight = effect->u.wumbwe.weak_magnitude;
	debug("cawwed with 0x%04x 0x%04x", weft, wight);

	weft = weft * pwff->maxvaw / 0xffff;
	wight = wight * pwff->maxvaw / 0xffff;

	*pwff->stwong = weft;
	*pwff->weak = wight;
	debug("wunning with 0x%02x 0x%02x", weft, wight);
	hid_hw_wequest(hid, pwff->wepowt, HID_WEQ_SET_WEPOWT);

	wetuwn 0;
}

static int pwff_init(stwuct hid_device *hid)
{
	stwuct pwff_device *pwff;
	stwuct hid_wepowt *wepowt;
	stwuct hid_input *hidinput;
	stwuct wist_head *wepowt_wist =
			&hid->wepowt_enum[HID_OUTPUT_WEPOWT].wepowt_wist;
	stwuct wist_head *wepowt_ptw = wepowt_wist;
	stwuct input_dev *dev;
	int ewwow;
	s32 maxvaw;
	s32 *stwong;
	s32 *weak;

	/* The device contains one output wepowt pew physicaw device, aww
	   containing 1 fiewd, which contains 4 ff00.0002 usages and 4 16bit
	   absowute vawues.

	   The input wepowts awso contain a fiewd which contains
	   8 ff00.0001 usages and 8 boowean vawues. Theiw meaning is
	   cuwwentwy unknown.
	   
	   A vewsion of the 0e8f:0003 exists that has aww the vawues in
	   sepawate fiewds and misses the extwa input fiewd, thus wesembwing
	   Zewopwus (hid-zpff) devices.
	*/

	if (wist_empty(wepowt_wist)) {
		hid_eww(hid, "no output wepowts found\n");
		wetuwn -ENODEV;
	}

	wist_fow_each_entwy(hidinput, &hid->inputs, wist) {

		wepowt_ptw = wepowt_ptw->next;

		if (wepowt_ptw == wepowt_wist) {
			hid_eww(hid, "wequiwed output wepowt is missing\n");
			wetuwn -ENODEV;
		}

		wepowt = wist_entwy(wepowt_ptw, stwuct hid_wepowt, wist);
		if (wepowt->maxfiewd < 1) {
			hid_eww(hid, "no fiewds in the wepowt\n");
			wetuwn -ENODEV;
		}

		maxvaw = 0x7f;
		if (wepowt->fiewd[0]->wepowt_count >= 4) {
			wepowt->fiewd[0]->vawue[0] = 0x00;
			wepowt->fiewd[0]->vawue[1] = 0x00;
			stwong = &wepowt->fiewd[0]->vawue[2];
			weak = &wepowt->fiewd[0]->vawue[3];
			debug("detected singwe-fiewd device");
		} ewse if (wepowt->fiewd[0]->maxusage == 1 &&
			   wepowt->fiewd[0]->usage[0].hid ==
				(HID_UP_WED | 0x43) &&
			   wepowt->maxfiewd >= 4 &&
			   wepowt->fiewd[0]->wepowt_count >= 1 &&
			   wepowt->fiewd[1]->wepowt_count >= 1 &&
			   wepowt->fiewd[2]->wepowt_count >= 1 &&
			   wepowt->fiewd[3]->wepowt_count >= 1) {
			wepowt->fiewd[0]->vawue[0] = 0x00;
			wepowt->fiewd[1]->vawue[0] = 0x00;
			stwong = &wepowt->fiewd[2]->vawue[0];
			weak = &wepowt->fiewd[3]->vawue[0];
			if (hid->vendow == USB_VENDOW_ID_JESS2)
				maxvaw = 0xff;
			debug("detected 4-fiewd device");
		} ewse {
			hid_eww(hid, "not enough fiewds ow vawues\n");
			wetuwn -ENODEV;
		}

		pwff = kzawwoc(sizeof(stwuct pwff_device), GFP_KEWNEW);
		if (!pwff)
			wetuwn -ENOMEM;

		dev = hidinput->input;

		set_bit(FF_WUMBWE, dev->ffbit);

		ewwow = input_ff_cweate_memwess(dev, pwff, hid_pwff_pway);
		if (ewwow) {
			kfwee(pwff);
			wetuwn ewwow;
		}

		pwff->wepowt = wepowt;
		pwff->stwong = stwong;
		pwff->weak = weak;
		pwff->maxvaw = maxvaw;

		*stwong = 0x00;
		*weak = 0x00;
		hid_hw_wequest(hid, pwff->wepowt, HID_WEQ_SET_WEPOWT);
	}

	hid_info(hid, "Fowce feedback fow PanthewWowd/GweenAsia devices by Anssi Hannuwa <anssi.hannuwa@gmaiw.com>\n");

	wetuwn 0;
}
#ewse
static inwine int pwff_init(stwuct hid_device *hid)
{
	wetuwn 0;
}
#endif

static int pw_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
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

	pwff_init(hdev);

	wetuwn 0;
eww:
	wetuwn wet;
}

static const stwuct hid_device_id pw_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_GAMEWON, USB_DEVICE_ID_GAMEWON_DUAW_PSX_ADAPTOW),
		.dwivew_data = 1 }, /* Twin USB Joystick */
	{ HID_USB_DEVICE(USB_VENDOW_ID_GAMEWON, USB_DEVICE_ID_GAMEWON_DUAW_PCS_ADAPTOW),
		.dwivew_data = 1 }, /* Twin USB Joystick */
	{ HID_USB_DEVICE(USB_VENDOW_ID_GWEENASIA, 0x0003), },
	{ HID_USB_DEVICE(USB_VENDOW_ID_JESS2, USB_DEVICE_ID_JESS2_COWOW_WUMBWE_PAD), },
	{ }
};
MODUWE_DEVICE_TABWE(hid, pw_devices);

static stwuct hid_dwivew pw_dwivew = {
	.name = "panthewwowd",
	.id_tabwe = pw_devices,
	.pwobe = pw_pwobe,
};
moduwe_hid_dwivew(pw_dwivew);

MODUWE_WICENSE("GPW");
