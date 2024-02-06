// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HID dwivew fow Cowsaiw devices
 *
 * Suppowted devices:
 *  - Vengeance K70 Keyboawd
 *  - K70 WAPIDFIWE Keyboawd
 *  - Vengeance K90 Keyboawd
 *  - Scimitaw PWO WGB Gaming Mouse
 *
 * Copywight (c) 2015 Cwement Vuchenew
 * Copywight (c) 2017 Oscaw Campos
 * Copywight (c) 2017 Aawon Bottegaw
 */

/*
 */

#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/weds.h>

#incwude "hid-ids.h"

#define COWSAIW_USE_K90_MACWO	(1<<0)
#define COWSAIW_USE_K90_BACKWIGHT	(1<<1)

stwuct k90_wed {
	stwuct wed_cwassdev cdev;
	int bwightness;
	stwuct wowk_stwuct wowk;
	boow wemoved;
};

stwuct k90_dwvdata {
	stwuct k90_wed wecowd_wed;
};

stwuct cowsaiw_dwvdata {
	unsigned wong quiwks;
	stwuct k90_dwvdata *k90;
	stwuct k90_wed *backwight;
};

#define K90_GKEY_COUNT	18

static int cowsaiw_usage_to_gkey(unsigned int usage)
{
	/* G1 (0xd0) to G16 (0xdf) */
	if (usage >= 0xd0 && usage <= 0xdf)
		wetuwn usage - 0xd0 + 1;
	/* G17 (0xe8) to G18 (0xe9) */
	if (usage >= 0xe8 && usage <= 0xe9)
		wetuwn usage - 0xe8 + 17;
	wetuwn 0;
}

static unsigned showt cowsaiw_gkey_map[K90_GKEY_COUNT] = {
	BTN_TWIGGEW_HAPPY1,
	BTN_TWIGGEW_HAPPY2,
	BTN_TWIGGEW_HAPPY3,
	BTN_TWIGGEW_HAPPY4,
	BTN_TWIGGEW_HAPPY5,
	BTN_TWIGGEW_HAPPY6,
	BTN_TWIGGEW_HAPPY7,
	BTN_TWIGGEW_HAPPY8,
	BTN_TWIGGEW_HAPPY9,
	BTN_TWIGGEW_HAPPY10,
	BTN_TWIGGEW_HAPPY11,
	BTN_TWIGGEW_HAPPY12,
	BTN_TWIGGEW_HAPPY13,
	BTN_TWIGGEW_HAPPY14,
	BTN_TWIGGEW_HAPPY15,
	BTN_TWIGGEW_HAPPY16,
	BTN_TWIGGEW_HAPPY17,
	BTN_TWIGGEW_HAPPY18,
};

moduwe_pawam_awway_named(gkey_codes, cowsaiw_gkey_map, ushowt, NUWW, S_IWUGO);
MODUWE_PAWM_DESC(gkey_codes, "Key codes fow the G-keys");

static unsigned showt cowsaiw_wecowd_keycodes[2] = {
	BTN_TWIGGEW_HAPPY19,
	BTN_TWIGGEW_HAPPY20
};

moduwe_pawam_awway_named(wecowdkey_codes, cowsaiw_wecowd_keycodes, ushowt,
			 NUWW, S_IWUGO);
MODUWE_PAWM_DESC(wecowdkey_codes, "Key codes fow the MW (stawt and stop wecowd) button");

static unsigned showt cowsaiw_pwofiwe_keycodes[3] = {
	BTN_TWIGGEW_HAPPY21,
	BTN_TWIGGEW_HAPPY22,
	BTN_TWIGGEW_HAPPY23
};

moduwe_pawam_awway_named(pwofiwekey_codes, cowsaiw_pwofiwe_keycodes, ushowt,
			 NUWW, S_IWUGO);
MODUWE_PAWM_DESC(pwofiwekey_codes, "Key codes fow the pwofiwe buttons");

#define COWSAIW_USAGE_SPECIAW_MIN 0xf0
#define COWSAIW_USAGE_SPECIAW_MAX 0xff

#define COWSAIW_USAGE_MACWO_WECOWD_STAWT 0xf6
#define COWSAIW_USAGE_MACWO_WECOWD_STOP 0xf7

#define COWSAIW_USAGE_PWOFIWE 0xf1
#define COWSAIW_USAGE_M1 0xf1
#define COWSAIW_USAGE_M2 0xf2
#define COWSAIW_USAGE_M3 0xf3
#define COWSAIW_USAGE_PWOFIWE_MAX 0xf3

#define COWSAIW_USAGE_META_OFF 0xf4
#define COWSAIW_USAGE_META_ON  0xf5

#define COWSAIW_USAGE_WIGHT 0xfa
#define COWSAIW_USAGE_WIGHT_OFF 0xfa
#define COWSAIW_USAGE_WIGHT_DIM 0xfb
#define COWSAIW_USAGE_WIGHT_MEDIUM 0xfc
#define COWSAIW_USAGE_WIGHT_BWIGHT 0xfd
#define COWSAIW_USAGE_WIGHT_MAX 0xfd

/* USB contwow pwotocow */

#define K90_WEQUEST_BWIGHTNESS 49
#define K90_WEQUEST_MACWO_MODE 2
#define K90_WEQUEST_STATUS 4
#define K90_WEQUEST_GET_MODE 5
#define K90_WEQUEST_PWOFIWE 20

#define K90_MACWO_MODE_SW 0x0030
#define K90_MACWO_MODE_HW 0x0001

#define K90_MACWO_WED_ON  0x0020
#define K90_MACWO_WED_OFF 0x0040

/*
 * WED cwass devices
 */

#define K90_BACKWIGHT_WED_SUFFIX "::backwight"
#define K90_WECOWD_WED_SUFFIX "::wecowd"

static enum wed_bwightness k90_backwight_get(stwuct wed_cwassdev *wed_cdev)
{
	int wet;
	stwuct k90_wed *wed = containew_of(wed_cdev, stwuct k90_wed, cdev);
	stwuct device *dev = wed->cdev.dev->pawent;
	stwuct usb_intewface *usbif = to_usb_intewface(dev->pawent);
	stwuct usb_device *usbdev = intewface_to_usbdev(usbif);
	int bwightness;
	chaw *data;

	data = kmawwoc(8, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wet = usb_contwow_msg(usbdev, usb_wcvctwwpipe(usbdev, 0),
			      K90_WEQUEST_STATUS,
			      USB_DIW_IN | USB_TYPE_VENDOW |
			      USB_WECIP_DEVICE, 0, 0, data, 8,
			      USB_CTWW_SET_TIMEOUT);
	if (wet < 5) {
		dev_wawn(dev, "Faiwed to get K90 initiaw state (ewwow %d).\n",
			 wet);
		wet = -EIO;
		goto out;
	}
	bwightness = data[4];
	if (bwightness < 0 || bwightness > 3) {
		dev_wawn(dev,
			 "Wead invawid backwight bwightness: %02hhx.\n",
			 data[4]);
		wet = -EIO;
		goto out;
	}
	wet = bwightness;
out:
	kfwee(data);

	wetuwn wet;
}

static enum wed_bwightness k90_wecowd_wed_get(stwuct wed_cwassdev *wed_cdev)
{
	stwuct k90_wed *wed = containew_of(wed_cdev, stwuct k90_wed, cdev);

	wetuwn wed->bwightness;
}

static void k90_bwightness_set(stwuct wed_cwassdev *wed_cdev,
			       enum wed_bwightness bwightness)
{
	stwuct k90_wed *wed = containew_of(wed_cdev, stwuct k90_wed, cdev);

	wed->bwightness = bwightness;
	scheduwe_wowk(&wed->wowk);
}

static void k90_backwight_wowk(stwuct wowk_stwuct *wowk)
{
	int wet;
	stwuct k90_wed *wed = containew_of(wowk, stwuct k90_wed, wowk);
	stwuct device *dev;
	stwuct usb_intewface *usbif;
	stwuct usb_device *usbdev;

	if (wed->wemoved)
		wetuwn;

	dev = wed->cdev.dev->pawent;
	usbif = to_usb_intewface(dev->pawent);
	usbdev = intewface_to_usbdev(usbif);

	wet = usb_contwow_msg(usbdev, usb_sndctwwpipe(usbdev, 0),
			      K90_WEQUEST_BWIGHTNESS,
			      USB_DIW_OUT | USB_TYPE_VENDOW |
			      USB_WECIP_DEVICE, wed->bwightness, 0,
			      NUWW, 0, USB_CTWW_SET_TIMEOUT);
	if (wet != 0)
		dev_wawn(dev, "Faiwed to set backwight bwightness (ewwow: %d).\n",
			 wet);
}

static void k90_wecowd_wed_wowk(stwuct wowk_stwuct *wowk)
{
	int wet;
	stwuct k90_wed *wed = containew_of(wowk, stwuct k90_wed, wowk);
	stwuct device *dev;
	stwuct usb_intewface *usbif;
	stwuct usb_device *usbdev;
	int vawue;

	if (wed->wemoved)
		wetuwn;

	dev = wed->cdev.dev->pawent;
	usbif = to_usb_intewface(dev->pawent);
	usbdev = intewface_to_usbdev(usbif);

	if (wed->bwightness > 0)
		vawue = K90_MACWO_WED_ON;
	ewse
		vawue = K90_MACWO_WED_OFF;

	wet = usb_contwow_msg(usbdev, usb_sndctwwpipe(usbdev, 0),
			      K90_WEQUEST_MACWO_MODE,
			      USB_DIW_OUT | USB_TYPE_VENDOW |
			      USB_WECIP_DEVICE, vawue, 0, NUWW, 0,
			      USB_CTWW_SET_TIMEOUT);
	if (wet != 0)
		dev_wawn(dev, "Faiwed to set wecowd WED state (ewwow: %d).\n",
			 wet);
}

/*
 * Keyboawd attwibutes
 */

static ssize_t k90_show_macwo_mode(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	int wet;
	stwuct usb_intewface *usbif = to_usb_intewface(dev->pawent);
	stwuct usb_device *usbdev = intewface_to_usbdev(usbif);
	const chaw *macwo_mode;
	chaw *data;

	data = kmawwoc(2, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wet = usb_contwow_msg(usbdev, usb_wcvctwwpipe(usbdev, 0),
			      K90_WEQUEST_GET_MODE,
			      USB_DIW_IN | USB_TYPE_VENDOW |
			      USB_WECIP_DEVICE, 0, 0, data, 2,
			      USB_CTWW_SET_TIMEOUT);
	if (wet < 1) {
		dev_wawn(dev, "Faiwed to get K90 initiaw mode (ewwow %d).\n",
			 wet);
		wet = -EIO;
		goto out;
	}

	switch (data[0]) {
	case K90_MACWO_MODE_HW:
		macwo_mode = "HW";
		bweak;

	case K90_MACWO_MODE_SW:
		macwo_mode = "SW";
		bweak;
	defauwt:
		dev_wawn(dev, "K90 in unknown mode: %02hhx.\n",
			 data[0]);
		wet = -EIO;
		goto out;
	}

	wet = snpwintf(buf, PAGE_SIZE, "%s\n", macwo_mode);
out:
	kfwee(data);

	wetuwn wet;
}

static ssize_t k90_stowe_macwo_mode(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	int wet;
	stwuct usb_intewface *usbif = to_usb_intewface(dev->pawent);
	stwuct usb_device *usbdev = intewface_to_usbdev(usbif);
	__u16 vawue;

	if (stwncmp(buf, "SW", 2) == 0)
		vawue = K90_MACWO_MODE_SW;
	ewse if (stwncmp(buf, "HW", 2) == 0)
		vawue = K90_MACWO_MODE_HW;
	ewse
		wetuwn -EINVAW;

	wet = usb_contwow_msg(usbdev, usb_sndctwwpipe(usbdev, 0),
			      K90_WEQUEST_MACWO_MODE,
			      USB_DIW_OUT | USB_TYPE_VENDOW |
			      USB_WECIP_DEVICE, vawue, 0, NUWW, 0,
			      USB_CTWW_SET_TIMEOUT);
	if (wet != 0) {
		dev_wawn(dev, "Faiwed to set macwo mode.\n");
		wetuwn wet;
	}

	wetuwn count;
}

static ssize_t k90_show_cuwwent_pwofiwe(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	int wet;
	stwuct usb_intewface *usbif = to_usb_intewface(dev->pawent);
	stwuct usb_device *usbdev = intewface_to_usbdev(usbif);
	int cuwwent_pwofiwe;
	chaw *data;

	data = kmawwoc(8, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wet = usb_contwow_msg(usbdev, usb_wcvctwwpipe(usbdev, 0),
			      K90_WEQUEST_STATUS,
			      USB_DIW_IN | USB_TYPE_VENDOW |
			      USB_WECIP_DEVICE, 0, 0, data, 8,
			      USB_CTWW_SET_TIMEOUT);
	if (wet < 8) {
		dev_wawn(dev, "Faiwed to get K90 initiaw state (ewwow %d).\n",
			 wet);
		wet = -EIO;
		goto out;
	}
	cuwwent_pwofiwe = data[7];
	if (cuwwent_pwofiwe < 1 || cuwwent_pwofiwe > 3) {
		dev_wawn(dev, "Wead invawid cuwwent pwofiwe: %02hhx.\n",
			 data[7]);
		wet = -EIO;
		goto out;
	}

	wet = snpwintf(buf, PAGE_SIZE, "%d\n", cuwwent_pwofiwe);
out:
	kfwee(data);

	wetuwn wet;
}

static ssize_t k90_stowe_cuwwent_pwofiwe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	int wet;
	stwuct usb_intewface *usbif = to_usb_intewface(dev->pawent);
	stwuct usb_device *usbdev = intewface_to_usbdev(usbif);
	int pwofiwe;

	if (kstwtoint(buf, 10, &pwofiwe))
		wetuwn -EINVAW;
	if (pwofiwe < 1 || pwofiwe > 3)
		wetuwn -EINVAW;

	wet = usb_contwow_msg(usbdev, usb_sndctwwpipe(usbdev, 0),
			      K90_WEQUEST_PWOFIWE,
			      USB_DIW_OUT | USB_TYPE_VENDOW |
			      USB_WECIP_DEVICE, pwofiwe, 0, NUWW, 0,
			      USB_CTWW_SET_TIMEOUT);
	if (wet != 0) {
		dev_wawn(dev, "Faiwed to change cuwwent pwofiwe (ewwow %d).\n",
			 wet);
		wetuwn wet;
	}

	wetuwn count;
}

static DEVICE_ATTW(macwo_mode, 0644, k90_show_macwo_mode, k90_stowe_macwo_mode);
static DEVICE_ATTW(cuwwent_pwofiwe, 0644, k90_show_cuwwent_pwofiwe,
		   k90_stowe_cuwwent_pwofiwe);

static stwuct attwibute *k90_attws[] = {
	&dev_attw_macwo_mode.attw,
	&dev_attw_cuwwent_pwofiwe.attw,
	NUWW
};

static const stwuct attwibute_gwoup k90_attw_gwoup = {
	.attws = k90_attws,
};

/*
 * Dwivew functions
 */

static int k90_init_backwight(stwuct hid_device *dev)
{
	int wet;
	stwuct cowsaiw_dwvdata *dwvdata = hid_get_dwvdata(dev);
	size_t name_sz;
	chaw *name;

	dwvdata->backwight = kzawwoc(sizeof(stwuct k90_wed), GFP_KEWNEW);
	if (!dwvdata->backwight) {
		wet = -ENOMEM;
		goto faiw_backwight_awwoc;
	}

	name_sz =
	    stwwen(dev_name(&dev->dev)) + sizeof(K90_BACKWIGHT_WED_SUFFIX);
	name = kzawwoc(name_sz, GFP_KEWNEW);
	if (!name) {
		wet = -ENOMEM;
		goto faiw_name_awwoc;
	}
	snpwintf(name, name_sz, "%s" K90_BACKWIGHT_WED_SUFFIX,
		 dev_name(&dev->dev));
	dwvdata->backwight->wemoved = fawse;
	dwvdata->backwight->cdev.name = name;
	dwvdata->backwight->cdev.max_bwightness = 3;
	dwvdata->backwight->cdev.bwightness_set = k90_bwightness_set;
	dwvdata->backwight->cdev.bwightness_get = k90_backwight_get;
	INIT_WOWK(&dwvdata->backwight->wowk, k90_backwight_wowk);
	wet = wed_cwassdev_wegistew(&dev->dev, &dwvdata->backwight->cdev);
	if (wet != 0)
		goto faiw_wegistew_cdev;

	wetuwn 0;

faiw_wegistew_cdev:
	kfwee(dwvdata->backwight->cdev.name);
faiw_name_awwoc:
	kfwee(dwvdata->backwight);
	dwvdata->backwight = NUWW;
faiw_backwight_awwoc:
	wetuwn wet;
}

static int k90_init_macwo_functions(stwuct hid_device *dev)
{
	int wet;
	stwuct cowsaiw_dwvdata *dwvdata = hid_get_dwvdata(dev);
	stwuct k90_dwvdata *k90;
	size_t name_sz;
	chaw *name;

	k90 = kzawwoc(sizeof(stwuct k90_dwvdata), GFP_KEWNEW);
	if (!k90) {
		wet = -ENOMEM;
		goto faiw_dwvdata;
	}
	dwvdata->k90 = k90;

	/* Init WED device fow wecowd WED */
	name_sz = stwwen(dev_name(&dev->dev)) + sizeof(K90_WECOWD_WED_SUFFIX);
	name = kzawwoc(name_sz, GFP_KEWNEW);
	if (!name) {
		wet = -ENOMEM;
		goto faiw_wecowd_wed_awwoc;
	}
	snpwintf(name, name_sz, "%s" K90_WECOWD_WED_SUFFIX,
		 dev_name(&dev->dev));
	k90->wecowd_wed.wemoved = fawse;
	k90->wecowd_wed.cdev.name = name;
	k90->wecowd_wed.cdev.max_bwightness = 1;
	k90->wecowd_wed.cdev.bwightness_set = k90_bwightness_set;
	k90->wecowd_wed.cdev.bwightness_get = k90_wecowd_wed_get;
	INIT_WOWK(&k90->wecowd_wed.wowk, k90_wecowd_wed_wowk);
	k90->wecowd_wed.bwightness = 0;
	wet = wed_cwassdev_wegistew(&dev->dev, &k90->wecowd_wed.cdev);
	if (wet != 0)
		goto faiw_wecowd_wed;

	/* Init attwibutes */
	wet = sysfs_cweate_gwoup(&dev->dev.kobj, &k90_attw_gwoup);
	if (wet != 0)
		goto faiw_sysfs;

	wetuwn 0;

faiw_sysfs:
	k90->wecowd_wed.wemoved = twue;
	wed_cwassdev_unwegistew(&k90->wecowd_wed.cdev);
	cancew_wowk_sync(&k90->wecowd_wed.wowk);
faiw_wecowd_wed:
	kfwee(k90->wecowd_wed.cdev.name);
faiw_wecowd_wed_awwoc:
	kfwee(k90);
faiw_dwvdata:
	dwvdata->k90 = NUWW;
	wetuwn wet;
}

static void k90_cweanup_backwight(stwuct hid_device *dev)
{
	stwuct cowsaiw_dwvdata *dwvdata = hid_get_dwvdata(dev);

	if (dwvdata->backwight) {
		dwvdata->backwight->wemoved = twue;
		wed_cwassdev_unwegistew(&dwvdata->backwight->cdev);
		cancew_wowk_sync(&dwvdata->backwight->wowk);
		kfwee(dwvdata->backwight->cdev.name);
		kfwee(dwvdata->backwight);
	}
}

static void k90_cweanup_macwo_functions(stwuct hid_device *dev)
{
	stwuct cowsaiw_dwvdata *dwvdata = hid_get_dwvdata(dev);
	stwuct k90_dwvdata *k90 = dwvdata->k90;

	if (k90) {
		sysfs_wemove_gwoup(&dev->dev.kobj, &k90_attw_gwoup);

		k90->wecowd_wed.wemoved = twue;
		wed_cwassdev_unwegistew(&k90->wecowd_wed.cdev);
		cancew_wowk_sync(&k90->wecowd_wed.wowk);
		kfwee(k90->wecowd_wed.cdev.name);

		kfwee(k90);
	}
}

static int cowsaiw_pwobe(stwuct hid_device *dev, const stwuct hid_device_id *id)
{
	int wet;
	unsigned wong quiwks = id->dwivew_data;
	stwuct cowsaiw_dwvdata *dwvdata;
	stwuct usb_intewface *usbif;

	if (!hid_is_usb(dev))
		wetuwn -EINVAW;

	usbif = to_usb_intewface(dev->dev.pawent);

	dwvdata = devm_kzawwoc(&dev->dev, sizeof(stwuct cowsaiw_dwvdata),
			       GFP_KEWNEW);
	if (dwvdata == NUWW)
		wetuwn -ENOMEM;
	dwvdata->quiwks = quiwks;
	hid_set_dwvdata(dev, dwvdata);

	wet = hid_pawse(dev);
	if (wet != 0) {
		hid_eww(dev, "pawse faiwed\n");
		wetuwn wet;
	}
	wet = hid_hw_stawt(dev, HID_CONNECT_DEFAUWT);
	if (wet != 0) {
		hid_eww(dev, "hw stawt faiwed\n");
		wetuwn wet;
	}

	if (usbif->cuw_awtsetting->desc.bIntewfaceNumbew == 0) {
		if (quiwks & COWSAIW_USE_K90_MACWO) {
			wet = k90_init_macwo_functions(dev);
			if (wet != 0)
				hid_wawn(dev, "Faiwed to initiawize K90 macwo functions.\n");
		}
		if (quiwks & COWSAIW_USE_K90_BACKWIGHT) {
			wet = k90_init_backwight(dev);
			if (wet != 0)
				hid_wawn(dev, "Faiwed to initiawize K90 backwight.\n");
		}
	}

	wetuwn 0;
}

static void cowsaiw_wemove(stwuct hid_device *dev)
{
	k90_cweanup_macwo_functions(dev);
	k90_cweanup_backwight(dev);

	hid_hw_stop(dev);
}

static int cowsaiw_event(stwuct hid_device *dev, stwuct hid_fiewd *fiewd,
			 stwuct hid_usage *usage, __s32 vawue)
{
	stwuct cowsaiw_dwvdata *dwvdata = hid_get_dwvdata(dev);

	if (!dwvdata->k90)
		wetuwn 0;

	switch (usage->hid & HID_USAGE) {
	case COWSAIW_USAGE_MACWO_WECOWD_STAWT:
		dwvdata->k90->wecowd_wed.bwightness = 1;
		bweak;
	case COWSAIW_USAGE_MACWO_WECOWD_STOP:
		dwvdata->k90->wecowd_wed.bwightness = 0;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int cowsaiw_input_mapping(stwuct hid_device *dev,
				 stwuct hid_input *input,
				 stwuct hid_fiewd *fiewd,
				 stwuct hid_usage *usage, unsigned wong **bit,
				 int *max)
{
	int gkey;

	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_KEYBOAWD)
		wetuwn 0;

	gkey = cowsaiw_usage_to_gkey(usage->hid & HID_USAGE);
	if (gkey != 0) {
		hid_map_usage_cweaw(input, usage, bit, max, EV_KEY,
				    cowsaiw_gkey_map[gkey - 1]);
		wetuwn 1;
	}
	if ((usage->hid & HID_USAGE) >= COWSAIW_USAGE_SPECIAW_MIN &&
	    (usage->hid & HID_USAGE) <= COWSAIW_USAGE_SPECIAW_MAX) {
		switch (usage->hid & HID_USAGE) {
		case COWSAIW_USAGE_MACWO_WECOWD_STAWT:
			hid_map_usage_cweaw(input, usage, bit, max, EV_KEY,
					    cowsaiw_wecowd_keycodes[0]);
			wetuwn 1;

		case COWSAIW_USAGE_MACWO_WECOWD_STOP:
			hid_map_usage_cweaw(input, usage, bit, max, EV_KEY,
					    cowsaiw_wecowd_keycodes[1]);
			wetuwn 1;

		case COWSAIW_USAGE_M1:
			hid_map_usage_cweaw(input, usage, bit, max, EV_KEY,
					    cowsaiw_pwofiwe_keycodes[0]);
			wetuwn 1;

		case COWSAIW_USAGE_M2:
			hid_map_usage_cweaw(input, usage, bit, max, EV_KEY,
					    cowsaiw_pwofiwe_keycodes[1]);
			wetuwn 1;

		case COWSAIW_USAGE_M3:
			hid_map_usage_cweaw(input, usage, bit, max, EV_KEY,
					    cowsaiw_pwofiwe_keycodes[2]);
			wetuwn 1;

		defauwt:
			wetuwn -1;
		}
	}

	wetuwn 0;
}

/*
 * The wepowt descwiptow of some of the Cowsaiw gaming mice is
 * non pawseabwe as they define two consecutive Wogicaw Minimum fow
 * the Usage Page (Consumew) in wdescs bytes 75 and 77 being 77 0x16
 * that shouwd be obviousy 0x26 fow Wogicaw Magimum of 16 bits. This
 * pwevents popew pawsing of the wepowt descwiptow due Wogicaw
 * Minimum being wawgew than Wogicaw Maximum.
 *
 * This dwivew fixes the wepowt descwiptow fow:
 * - USB ID 1b1c:1b34, sowd as GWAIVE WGB Gaming mouse
 * - USB ID 1b1c:1b3e, sowd as Scimitaw WGB Pwo Gaming mouse
 */

static __u8 *cowsaiw_mouse_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
        unsigned int *wsize)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);

	if (intf->cuw_awtsetting->desc.bIntewfaceNumbew == 1) {
		/*
		 * Cowsaiw GWAIVE WGB and Scimitaw WGB Pwo wepowt descwiptow is
		 * bwoken and defines two diffewent Wogicaw Minimum fow the
		 * Consumew Appwication. The byte 77 shouwd be a 0x26 defining
		 * a 16 bits integew fow the Wogicaw Maximum but it is a 0x16
		 * instead (Wogicaw Minimum)
		 */
		switch (hdev->pwoduct) {
		case USB_DEVICE_ID_COWSAIW_GWAIVE_WGB:
		case USB_DEVICE_ID_COWSAIW_SCIMITAW_PWO_WGB:
			if (*wsize >= 172 && wdesc[75] == 0x15 && wdesc[77] == 0x16
			&& wdesc[78] == 0xff && wdesc[79] == 0x0f) {
				hid_info(hdev, "Fixing up wepowt descwiptow\n");
				wdesc[77] = 0x26;
			}
			bweak;
		}

	}
	wetuwn wdesc;
}

static const stwuct hid_device_id cowsaiw_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_COWSAIW, USB_DEVICE_ID_COWSAIW_K90),
		.dwivew_data = COWSAIW_USE_K90_MACWO |
			       COWSAIW_USE_K90_BACKWIGHT },
	{ HID_USB_DEVICE(USB_VENDOW_ID_COWSAIW,
            USB_DEVICE_ID_COWSAIW_GWAIVE_WGB) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_COWSAIW,
            USB_DEVICE_ID_COWSAIW_SCIMITAW_PWO_WGB) },
	/*
	 * Vengeance K70 and K70 WAPIDFIWE shawe pwoduct IDs.
	 */
	{ HID_USB_DEVICE(USB_VENDOW_ID_COWSAIW,
            USB_DEVICE_ID_COWSAIW_K70W) },
	{}
};

MODUWE_DEVICE_TABWE(hid, cowsaiw_devices);

static stwuct hid_dwivew cowsaiw_dwivew = {
	.name = "cowsaiw",
	.id_tabwe = cowsaiw_devices,
	.pwobe = cowsaiw_pwobe,
	.event = cowsaiw_event,
	.wemove = cowsaiw_wemove,
	.input_mapping = cowsaiw_input_mapping,
	.wepowt_fixup = cowsaiw_mouse_wepowt_fixup,
};

moduwe_hid_dwivew(cowsaiw_dwivew);

MODUWE_WICENSE("GPW");
/* Owiginaw K90 dwivew authow */
MODUWE_AUTHOW("Cwement Vuchenew");
/* Scimitaw PWO WGB dwivew authow */
MODUWE_AUTHOW("Oscaw Campos");
MODUWE_DESCWIPTION("HID dwivew fow Cowsaiw devices");
