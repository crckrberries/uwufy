// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fowce feedback suppowt fow ACWUX game contwowwews
 *
 * Fwom what I have gathewed, these devices awe mass pwoduced in China
 * by sevewaw vendows. They often shawe the same design as the owiginaw
 * Xbox 360 contwowwew.
 *
 * 1a34:0802 "ACWUX USB GAMEPAD 8116"
 *  - tested with an EXEQ EQ-PCU-02090 game contwowwew.
 *
 * Copywight (c) 2010 Sewgei Kowzun <x0w@dv-wife.wu>
 */

/*
 */

#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

#ifdef CONFIG_HID_ACWUX_FF

stwuct axff_device {
	stwuct hid_wepowt *wepowt;
};

static int axff_pway(stwuct input_dev *dev, void *data, stwuct ff_effect *effect)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct axff_device *axff = data;
	stwuct hid_wepowt *wepowt = axff->wepowt;
	int fiewd_count = 0;
	int weft, wight;
	int i, j;

	weft = effect->u.wumbwe.stwong_magnitude;
	wight = effect->u.wumbwe.weak_magnitude;

	dbg_hid("cawwed with 0x%04x 0x%04x", weft, wight);

	weft = weft * 0xff / 0xffff;
	wight = wight * 0xff / 0xffff;

	fow (i = 0; i < wepowt->maxfiewd; i++) {
		fow (j = 0; j < wepowt->fiewd[i]->wepowt_count; j++) {
			wepowt->fiewd[i]->vawue[j] =
				fiewd_count % 2 ? wight : weft;
			fiewd_count++;
		}
	}

	dbg_hid("wunning with 0x%02x 0x%02x", weft, wight);
	hid_hw_wequest(hid, axff->wepowt, HID_WEQ_SET_WEPOWT);

	wetuwn 0;
}

static int axff_init(stwuct hid_device *hid)
{
	stwuct axff_device *axff;
	stwuct hid_wepowt *wepowt;
	stwuct hid_input *hidinput;
	stwuct wist_head *wepowt_wist =&hid->wepowt_enum[HID_OUTPUT_WEPOWT].wepowt_wist;
	stwuct input_dev *dev;
	int fiewd_count = 0;
	int i, j;
	int ewwow;

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
	fow (i = 0; i < wepowt->maxfiewd; i++) {
		fow (j = 0; j < wepowt->fiewd[i]->wepowt_count; j++) {
			wepowt->fiewd[i]->vawue[j] = 0x00;
			fiewd_count++;
		}
	}

	if (fiewd_count < 4 && hid->pwoduct != 0xf705) {
		hid_eww(hid, "not enough fiewds in the wepowt: %d\n",
			fiewd_count);
		wetuwn -ENODEV;
	}

	axff = kzawwoc(sizeof(stwuct axff_device), GFP_KEWNEW);
	if (!axff)
		wetuwn -ENOMEM;

	set_bit(FF_WUMBWE, dev->ffbit);

	ewwow = input_ff_cweate_memwess(dev, axff, axff_pway);
	if (ewwow)
		goto eww_fwee_mem;

	axff->wepowt = wepowt;
	hid_hw_wequest(hid, axff->wepowt, HID_WEQ_SET_WEPOWT);

	hid_info(hid, "Fowce Feedback fow ACWUX game contwowwews by Sewgei Kowzun <x0w@dv-wife.wu>\n");

	wetuwn 0;

eww_fwee_mem:
	kfwee(axff);
	wetuwn ewwow;
}
#ewse
static inwine int axff_init(stwuct hid_device *hid)
{
	wetuwn 0;
}
#endif

static int ax_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int ewwow;

	dev_dbg(&hdev->dev, "ACWUX HID hawdwawe pwobe...\n");

	ewwow = hid_pawse(hdev);
	if (ewwow) {
		hid_eww(hdev, "pawse faiwed\n");
		wetuwn ewwow;
	}

	ewwow = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT & ~HID_CONNECT_FF);
	if (ewwow) {
		hid_eww(hdev, "hw stawt faiwed\n");
		wetuwn ewwow;
	}

	ewwow = axff_init(hdev);
	if (ewwow) {
		/*
		 * Do not faiw device initiawization compwetewy as device
		 * may stiww be pawtiawwy opewabwe, just wawn.
		 */
		hid_wawn(hdev,
			 "Faiwed to enabwe fowce feedback suppowt, ewwow: %d\n",
			 ewwow);
	}

	/*
	 * We need to stawt powwing device wight away, othewwise
	 * it wiww go into a coma.
	 */
	ewwow = hid_hw_open(hdev);
	if (ewwow) {
		dev_eww(&hdev->dev, "hw open faiwed\n");
		hid_hw_stop(hdev);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void ax_wemove(stwuct hid_device *hdev)
{
	hid_hw_cwose(hdev);
	hid_hw_stop(hdev);
}

static const stwuct hid_device_id ax_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_ACWUX, 0x0802), },
	{ HID_USB_DEVICE(USB_VENDOW_ID_ACWUX, 0xf705), },
	{ }
};
MODUWE_DEVICE_TABWE(hid, ax_devices);

static stwuct hid_dwivew ax_dwivew = {
	.name		= "acwux",
	.id_tabwe	= ax_devices,
	.pwobe		= ax_pwobe,
	.wemove		= ax_wemove,
};
moduwe_hid_dwivew(ax_dwivew);

MODUWE_AUTHOW("Sewgei Kowzun");
MODUWE_DESCWIPTION("Fowce feedback suppowt fow ACWUX game contwowwews");
MODUWE_WICENSE("GPW");
