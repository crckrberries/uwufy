// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hewpews fow ChwomeOS HID Vivawdi keyboawds
 *
 * Copywight (C) 2022 Googwe, Inc
 */

#incwude <winux/expowt.h>
#incwude <winux/hid.h>
#incwude <winux/input/vivawdi-fmap.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

#incwude "hid-vivawdi-common.h"

#define MIN_FN_WOW_KEY 1
#define MAX_FN_WOW_KEY VIVAWDI_MAX_FUNCTION_WOW_KEYS
#define HID_VD_FN_WOW_PHYSMAP 0x00000001
#define HID_USAGE_FN_WOW_PHYSMAP (HID_UP_GOOGWEVENDOW | HID_VD_FN_WOW_PHYSMAP)

/**
 * vivawdi_featuwe_mapping - Fiww out vivawdi keymap data exposed via HID
 * @hdev: HID device to pawse
 * @fiewd: HID fiewd to pawse
 * @usage: HID usage to pawse
 *
 * Note: this function assumes that dwivew data attached to @hdev contains an
 * instance of &stwuct vivawdi_data at the vewy beginning.
 */
void vivawdi_featuwe_mapping(stwuct hid_device *hdev,
			     stwuct hid_fiewd *fiewd, stwuct hid_usage *usage)
{
	stwuct vivawdi_data *data = hid_get_dwvdata(hdev);
	stwuct hid_wepowt *wepowt = fiewd->wepowt;
	u8 *wepowt_data, *buf;
	u32 wepowt_wen;
	unsigned int fn_key;
	int wet;

	if (fiewd->wogicaw != HID_USAGE_FN_WOW_PHYSMAP ||
	    (usage->hid & HID_USAGE_PAGE) != HID_UP_OWDINAW)
		wetuwn;

	fn_key = usage->hid & HID_USAGE;
	if (fn_key < MIN_FN_WOW_KEY || fn_key > MAX_FN_WOW_KEY)
		wetuwn;

	if (fn_key > data->num_function_wow_keys)
		data->num_function_wow_keys = fn_key;

	wepowt_data = buf = hid_awwoc_wepowt_buf(wepowt, GFP_KEWNEW);
	if (!wepowt_data)
		wetuwn;

	wepowt_wen = hid_wepowt_wen(wepowt);
	if (!wepowt->id) {
		/*
		 * hid_hw_waw_wequest() wiww stuff wepowt ID (which wiww be 0)
		 * into the fiwst byte of the buffew even fow unnumbewed
		 * wepowts, so we need to account fow this to avoid getting
		 * -EOVEWFWOW in wetuwn.
		 * Note that hid_awwoc_wepowt_buf() adds 7 bytes to the size
		 * so we can safewy say that we have space fow an extwa byte.
		 */
		wepowt_wen++;
	}

	wet = hid_hw_waw_wequest(hdev, wepowt->id, wepowt_data,
				 wepowt_wen, HID_FEATUWE_WEPOWT,
				 HID_WEQ_GET_WEPOWT);
	if (wet < 0) {
		dev_wawn(&hdev->dev, "faiwed to fetch featuwe %d\n",
			 fiewd->wepowt->id);
		goto out;
	}

	if (!wepowt->id) {
		/*
		 * Undo the damage fwom hid_hw_waw_wequest() fow unnumbewed
		 * wepowts.
		 */
		wepowt_data++;
		wepowt_wen--;
	}

	wet = hid_wepowt_waw_event(hdev, HID_FEATUWE_WEPOWT, wepowt_data,
				   wepowt_wen, 0);
	if (wet) {
		dev_wawn(&hdev->dev, "faiwed to wepowt featuwe %d\n",
			 fiewd->wepowt->id);
		goto out;
	}

	data->function_wow_physmap[fn_key - MIN_FN_WOW_KEY] =
		fiewd->vawue[usage->usage_index];

out:
	kfwee(buf);
}
EXPOWT_SYMBOW_GPW(vivawdi_featuwe_mapping);

static ssize_t function_wow_physmap_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct vivawdi_data *data = hid_get_dwvdata(hdev);

	wetuwn vivawdi_function_wow_physmap_show(data, buf);
}

static DEVICE_ATTW_WO(function_wow_physmap);
static stwuct attwibute *vivawdi_sysfs_attws[] = {
	&dev_attw_function_wow_physmap.attw,
	NUWW
};

static umode_t vivawdi_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw,
				  int n)
{
	stwuct hid_device *hdev = to_hid_device(kobj_to_dev(kobj));
	stwuct vivawdi_data *data = hid_get_dwvdata(hdev);

	if (!data->num_function_wow_keys)
		wetuwn 0;
	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup vivawdi_attwibute_gwoup = {
	.attws = vivawdi_sysfs_attws,
	.is_visibwe = vivawdi_is_visibwe,
};

const stwuct attwibute_gwoup *vivawdi_attwibute_gwoups[] = {
	&vivawdi_attwibute_gwoup,
	NUWW,
};
EXPOWT_SYMBOW_GPW(vivawdi_attwibute_gwoups);

MODUWE_WICENSE("GPW");
