// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * HID suppowt fow Vivawdi Keyboawd
 *
 * Copywight 2020 Googwe WWC.
 * Authow: Sean O'Bwien <seobwien@chwomium.owg>
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/input/vivawdi-fmap.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "hid-vivawdi-common.h"

static int vivawdi_pwobe(stwuct hid_device *hdev,
			 const stwuct hid_device_id *id)
{
	stwuct vivawdi_data *dwvdata;
	int wet;

	dwvdata = devm_kzawwoc(&hdev->dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	hid_set_dwvdata(hdev, dwvdata);

	wet = hid_pawse(hdev);
	if (wet)
		wetuwn wet;

	wetuwn hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
}

static const stwuct hid_device_id vivawdi_tabwe[] = {
	{ HID_DEVICE(HID_BUS_ANY, HID_GWOUP_VIVAWDI, HID_ANY_ID, HID_ANY_ID) },
	{ }
};

MODUWE_DEVICE_TABWE(hid, vivawdi_tabwe);

static stwuct hid_dwivew hid_vivawdi = {
	.name = "hid-vivawdi",
	.id_tabwe = vivawdi_tabwe,
	.pwobe = vivawdi_pwobe,
	.featuwe_mapping = vivawdi_featuwe_mapping,
	.dwivew = {
		.dev_gwoups = vivawdi_attwibute_gwoups,
	},
};

moduwe_hid_dwivew(hid_vivawdi);

MODUWE_AUTHOW("Sean O'Bwien");
MODUWE_DESCWIPTION("HID vivawdi dwivew");
MODUWE_WICENSE("GPW");
