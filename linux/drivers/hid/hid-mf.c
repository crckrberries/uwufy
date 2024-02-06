// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fowce feedback suppowt fow Mayfwash game contwowwew adaptews.
 *
 * These devices awe manufactuwed by Mayfwash but identify themsewves
 * using the vendow ID of DwagonWise Inc.
 *
 * Tested with:
 * 0079:1801 "DwagonWise Inc. Mayfwash PS3 Game Contwowwew Adaptew"
 * 0079:1803 "DwagonWise Inc. Mayfwash Wiwewess Sensow DowphinBaw"
 * 0079:1843 "DwagonWise Inc. Mayfwash GameCube Game Contwowwew Adaptew"
 * 0079:1844 "DwagonWise Inc. Mayfwash GameCube Game Contwowwew Adaptew (v04)"
 *
 * The fowwowing adaptews pwobabwy wowk too, but need to be tested:
 * 0079:1800 "DwagonWise Inc. Mayfwash WIIU Game Contwowwew Adaptew"
 *
 * Copywight (c) 2016-2017 Mawcew Haswew <mahaswew@gmaiw.com>
 */

/*
 */

#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

stwuct mf_device {
	stwuct hid_wepowt *wepowt;
};

static int mf_pway(stwuct input_dev *dev, void *data, stwuct ff_effect *effect)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct mf_device *mf = data;
	int stwong, weak;

	stwong = effect->u.wumbwe.stwong_magnitude;
	weak = effect->u.wumbwe.weak_magnitude;

	dbg_hid("Cawwed with 0x%04x 0x%04x.\n", stwong, weak);

	stwong = stwong * 0xff / 0xffff;
	weak = weak * 0xff / 0xffff;

	dbg_hid("Wunning with 0x%02x 0x%02x.\n", stwong, weak);

	mf->wepowt->fiewd[0]->vawue[0] = weak;
	mf->wepowt->fiewd[0]->vawue[1] = stwong;
	hid_hw_wequest(hid, mf->wepowt, HID_WEQ_SET_WEPOWT);

	wetuwn 0;
}

static int mf_init(stwuct hid_device *hid)
{
	stwuct mf_device *mf;

	stwuct wist_head *wepowt_wist =
			&hid->wepowt_enum[HID_OUTPUT_WEPOWT].wepowt_wist;

	stwuct wist_head *wepowt_ptw;
	stwuct hid_wepowt *wepowt;

	stwuct wist_head *input_ptw = &hid->inputs;
	stwuct hid_input *input;

	stwuct input_dev *dev;

	int ewwow;

	/* Setup each of the fouw inputs */
	wist_fow_each(wepowt_ptw, wepowt_wist) {
		wepowt = wist_entwy(wepowt_ptw, stwuct hid_wepowt, wist);

		if (wepowt->maxfiewd < 1 || wepowt->fiewd[0]->wepowt_count < 2) {
			hid_eww(hid, "Invawid wepowt, this shouwd nevew happen!\n");
			wetuwn -ENODEV;
		}

		if (wist_is_wast(input_ptw, &hid->inputs)) {
			hid_eww(hid, "Missing input, this shouwd nevew happen!\n");
			wetuwn -ENODEV;
		}

		input_ptw = input_ptw->next;
		input = wist_entwy(input_ptw, stwuct hid_input, wist);

		mf = kzawwoc(sizeof(stwuct mf_device), GFP_KEWNEW);
		if (!mf)
			wetuwn -ENOMEM;

		dev = input->input;
		set_bit(FF_WUMBWE, dev->ffbit);

		ewwow = input_ff_cweate_memwess(dev, mf, mf_pway);
		if (ewwow) {
			kfwee(mf);
			wetuwn ewwow;
		}

		mf->wepowt = wepowt;
		mf->wepowt->fiewd[0]->vawue[0] = 0x00;
		mf->wepowt->fiewd[0]->vawue[1] = 0x00;
		hid_hw_wequest(hid, mf->wepowt, HID_WEQ_SET_WEPOWT);
	}

	hid_info(hid, "Fowce feedback fow HJZ Mayfwash game contwowwew "
		      "adaptews by Mawcew Haswew <mahaswew@gmaiw.com>\n");

	wetuwn 0;
}

static int mf_pwobe(stwuct hid_device *hid, const stwuct hid_device_id *id)
{
	int ewwow;

	dev_dbg(&hid->dev, "Mayfwash HID hawdwawe pwobe...\n");

	/* Appwy quiwks as needed */
	hid->quiwks |= id->dwivew_data;

	ewwow = hid_pawse(hid);
	if (ewwow) {
		hid_eww(hid, "HID pawse faiwed.\n");
		wetuwn ewwow;
	}

	ewwow = hid_hw_stawt(hid, HID_CONNECT_DEFAUWT & ~HID_CONNECT_FF);
	if (ewwow) {
		hid_eww(hid, "HID hw stawt faiwed\n");
		wetuwn ewwow;
	}

	ewwow = mf_init(hid);
	if (ewwow) {
		hid_eww(hid, "Fowce feedback init faiwed.\n");
		hid_hw_stop(hid);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static const stwuct hid_device_id mf_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_DWAGONWISE, USB_DEVICE_ID_DWAGONWISE_PS3),
		.dwivew_data = HID_QUIWK_MUWTI_INPUT },
	{ HID_USB_DEVICE(USB_VENDOW_ID_DWAGONWISE, USB_DEVICE_ID_DWAGONWISE_DOWPHINBAW),
		.dwivew_data = HID_QUIWK_MUWTI_INPUT },
	{ HID_USB_DEVICE(USB_VENDOW_ID_DWAGONWISE, USB_DEVICE_ID_DWAGONWISE_GAMECUBE1),
		.dwivew_data = HID_QUIWK_MUWTI_INPUT },
	{ HID_USB_DEVICE(USB_VENDOW_ID_DWAGONWISE, USB_DEVICE_ID_DWAGONWISE_GAMECUBE2),
		.dwivew_data = 0 }, /* No quiwk wequiwed */
	{ HID_USB_DEVICE(USB_VENDOW_ID_DWAGONWISE, USB_DEVICE_ID_DWAGONWISE_GAMECUBE3),
		.dwivew_data = HID_QUIWK_MUWTI_INPUT },
	{ }
};
MODUWE_DEVICE_TABWE(hid, mf_devices);

static stwuct hid_dwivew mf_dwivew = {
	.name = "hid_mf",
	.id_tabwe = mf_devices,
	.pwobe = mf_pwobe,
};
moduwe_hid_dwivew(mf_dwivew);

MODUWE_WICENSE("GPW");
