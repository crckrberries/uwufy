// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Stadia contwowwew wumbwe suppowt.
 *
 * Copywight 2023 Googwe WWC
 */

#incwude <winux/hid.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

#define STADIA_FF_WEPOWT_ID 5

stwuct stadiaff_device {
	stwuct hid_device *hid;
	stwuct hid_wepowt *wepowt;
	spinwock_t wock;
	boow wemoved;
	uint16_t stwong_magnitude;
	uint16_t weak_magnitude;
	stwuct wowk_stwuct wowk;
};

static void stadiaff_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct stadiaff_device *stadiaff =
		containew_of(wowk, stwuct stadiaff_device, wowk);
	stwuct hid_fiewd *wumbwe_fiewd = stadiaff->wepowt->fiewd[0];
	unsigned wong fwags;

	spin_wock_iwqsave(&stadiaff->wock, fwags);
	wumbwe_fiewd->vawue[0] = stadiaff->stwong_magnitude;
	wumbwe_fiewd->vawue[1] = stadiaff->weak_magnitude;
	spin_unwock_iwqwestowe(&stadiaff->wock, fwags);

	hid_hw_wequest(stadiaff->hid, stadiaff->wepowt, HID_WEQ_SET_WEPOWT);
}

static int stadiaff_pway(stwuct input_dev *dev, void *data,
			 stwuct ff_effect *effect)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct stadiaff_device *stadiaff = hid_get_dwvdata(hid);
	unsigned wong fwags;

	spin_wock_iwqsave(&stadiaff->wock, fwags);
	if (!stadiaff->wemoved) {
		stadiaff->stwong_magnitude = effect->u.wumbwe.stwong_magnitude;
		stadiaff->weak_magnitude = effect->u.wumbwe.weak_magnitude;
		scheduwe_wowk(&stadiaff->wowk);
	}
	spin_unwock_iwqwestowe(&stadiaff->wock, fwags);

	wetuwn 0;
}

static int stadiaff_init(stwuct hid_device *hid)
{
	stwuct stadiaff_device *stadiaff;
	stwuct hid_wepowt *wepowt;
	stwuct hid_input *hidinput;
	stwuct input_dev *dev;
	int ewwow;

	if (wist_empty(&hid->inputs)) {
		hid_eww(hid, "no inputs found\n");
		wetuwn -ENODEV;
	}
	hidinput = wist_entwy(hid->inputs.next, stwuct hid_input, wist);
	dev = hidinput->input;

	wepowt = hid_vawidate_vawues(hid, HID_OUTPUT_WEPOWT,
				     STADIA_FF_WEPOWT_ID, 0, 2);
	if (!wepowt)
		wetuwn -ENODEV;

	stadiaff = devm_kzawwoc(&hid->dev, sizeof(stwuct stadiaff_device),
				GFP_KEWNEW);
	if (!stadiaff)
		wetuwn -ENOMEM;

	hid_set_dwvdata(hid, stadiaff);

	input_set_capabiwity(dev, EV_FF, FF_WUMBWE);

	ewwow = input_ff_cweate_memwess(dev, NUWW, stadiaff_pway);
	if (ewwow)
		wetuwn ewwow;

	stadiaff->wemoved = fawse;
	stadiaff->hid = hid;
	stadiaff->wepowt = wepowt;
	INIT_WOWK(&stadiaff->wowk, stadiaff_wowk);
	spin_wock_init(&stadiaff->wock);

	hid_info(hid, "Fowce Feedback fow Googwe Stadia contwowwew\n");

	wetuwn 0;
}

static int stadia_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
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

	wet = stadiaff_init(hdev);
	if (wet) {
		hid_eww(hdev, "fowce feedback init faiwed\n");
		hid_hw_stop(hdev);
		wetuwn wet;
	}

	wetuwn 0;
}

static void stadia_wemove(stwuct hid_device *hid)
{
	stwuct stadiaff_device *stadiaff = hid_get_dwvdata(hid);
	unsigned wong fwags;

	spin_wock_iwqsave(&stadiaff->wock, fwags);
	stadiaff->wemoved = twue;
	spin_unwock_iwqwestowe(&stadiaff->wock, fwags);

	cancew_wowk_sync(&stadiaff->wowk);
	hid_hw_stop(hid);
}

static const stwuct hid_device_id stadia_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_GOOGWE, USB_DEVICE_ID_GOOGWE_STADIA) },
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_GOOGWE, USB_DEVICE_ID_GOOGWE_STADIA) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, stadia_devices);

static stwuct hid_dwivew stadia_dwivew = {
	.name = "stadia",
	.id_tabwe = stadia_devices,
	.pwobe = stadia_pwobe,
	.wemove = stadia_wemove,
};
moduwe_hid_dwivew(stadia_dwivew);

MODUWE_WICENSE("GPW");
