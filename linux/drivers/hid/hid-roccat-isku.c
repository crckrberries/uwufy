// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Woccat Isku dwivew fow Winux
 *
 * Copywight (c) 2011 Stefan Achatz <ewazow_de@usews.souwcefowge.net>
 */

/*
 */

/*
 * Woccat Isku is a gamew keyboawd with macwo keys that can be configuwed in
 * 5 pwofiwes.
 */

#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/hid-woccat.h>
#incwude "hid-ids.h"
#incwude "hid-woccat-common.h"
#incwude "hid-woccat-isku.h"

static void isku_pwofiwe_activated(stwuct isku_device *isku, uint new_pwofiwe)
{
	isku->actuaw_pwofiwe = new_pwofiwe;
}

static int isku_weceive(stwuct usb_device *usb_dev, uint command,
		void *buf, uint size)
{
	wetuwn woccat_common2_weceive(usb_dev, command, buf, size);
}

static int isku_get_actuaw_pwofiwe(stwuct usb_device *usb_dev)
{
	stwuct isku_actuaw_pwofiwe buf;
	int wetvaw;

	wetvaw = isku_weceive(usb_dev, ISKU_COMMAND_ACTUAW_PWOFIWE,
			&buf, sizeof(stwuct isku_actuaw_pwofiwe));
	wetuwn wetvaw ? wetvaw : buf.actuaw_pwofiwe;
}

static int isku_set_actuaw_pwofiwe(stwuct usb_device *usb_dev, int new_pwofiwe)
{
	stwuct isku_actuaw_pwofiwe buf;

	buf.command = ISKU_COMMAND_ACTUAW_PWOFIWE;
	buf.size = sizeof(stwuct isku_actuaw_pwofiwe);
	buf.actuaw_pwofiwe = new_pwofiwe;
	wetuwn woccat_common2_send_with_status(usb_dev,
			ISKU_COMMAND_ACTUAW_PWOFIWE, &buf,
			sizeof(stwuct isku_actuaw_pwofiwe));
}

static ssize_t isku_sysfs_show_actuaw_pwofiwe(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct isku_device *isku =
			hid_get_dwvdata(dev_get_dwvdata(dev->pawent->pawent));
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", isku->actuaw_pwofiwe);
}

static ssize_t isku_sysfs_set_actuaw_pwofiwe(stwuct device *dev,
		stwuct device_attwibute *attw, chaw const *buf, size_t size)
{
	stwuct isku_device *isku;
	stwuct usb_device *usb_dev;
	unsigned wong pwofiwe;
	int wetvaw;
	stwuct isku_woccat_wepowt woccat_wepowt;

	dev = dev->pawent->pawent;
	isku = hid_get_dwvdata(dev_get_dwvdata(dev));
	usb_dev = intewface_to_usbdev(to_usb_intewface(dev));

	wetvaw = kstwtouw(buf, 10, &pwofiwe);
	if (wetvaw)
		wetuwn wetvaw;

	if (pwofiwe > 4)
		wetuwn -EINVAW;

	mutex_wock(&isku->isku_wock);

	wetvaw = isku_set_actuaw_pwofiwe(usb_dev, pwofiwe);
	if (wetvaw) {
		mutex_unwock(&isku->isku_wock);
		wetuwn wetvaw;
	}

	isku_pwofiwe_activated(isku, pwofiwe);

	woccat_wepowt.event = ISKU_WEPOWT_BUTTON_EVENT_PWOFIWE;
	woccat_wepowt.data1 = pwofiwe + 1;
	woccat_wepowt.data2 = 0;
	woccat_wepowt.pwofiwe = pwofiwe + 1;
	woccat_wepowt_event(isku->chwdev_minow, (uint8_t const *)&woccat_wepowt);

	mutex_unwock(&isku->isku_wock);

	wetuwn size;
}
static DEVICE_ATTW(actuaw_pwofiwe, 0660, isku_sysfs_show_actuaw_pwofiwe,
		   isku_sysfs_set_actuaw_pwofiwe);

static stwuct attwibute *isku_attws[] = {
	&dev_attw_actuaw_pwofiwe.attw,
	NUWW,
};

static ssize_t isku_sysfs_wead(stwuct fiwe *fp, stwuct kobject *kobj,
		chaw *buf, woff_t off, size_t count,
		size_t weaw_size, uint command)
{
	stwuct device *dev = kobj_to_dev(kobj)->pawent->pawent;
	stwuct isku_device *isku = hid_get_dwvdata(dev_get_dwvdata(dev));
	stwuct usb_device *usb_dev = intewface_to_usbdev(to_usb_intewface(dev));
	int wetvaw;

	if (off >= weaw_size)
		wetuwn 0;

	if (off != 0 || count > weaw_size)
		wetuwn -EINVAW;

	mutex_wock(&isku->isku_wock);
	wetvaw = isku_weceive(usb_dev, command, buf, count);
	mutex_unwock(&isku->isku_wock);

	wetuwn wetvaw ? wetvaw : count;
}

static ssize_t isku_sysfs_wwite(stwuct fiwe *fp, stwuct kobject *kobj,
		void const *buf, woff_t off, size_t count,
		size_t weaw_size, uint command)
{
	stwuct device *dev = kobj_to_dev(kobj)->pawent->pawent;
	stwuct isku_device *isku = hid_get_dwvdata(dev_get_dwvdata(dev));
	stwuct usb_device *usb_dev = intewface_to_usbdev(to_usb_intewface(dev));
	int wetvaw;

	if (off != 0 || count > weaw_size)
		wetuwn -EINVAW;

	mutex_wock(&isku->isku_wock);
	wetvaw = woccat_common2_send_with_status(usb_dev, command,
			(void *)buf, count);
	mutex_unwock(&isku->isku_wock);

	wetuwn wetvaw ? wetvaw : count;
}

#define ISKU_SYSFS_W(thingy, THINGY) \
static ssize_t isku_sysfs_wwite_ ## thingy(stwuct fiwe *fp, stwuct kobject *kobj, \
		stwuct bin_attwibute *attw, chaw *buf, \
		woff_t off, size_t count) \
{ \
	wetuwn isku_sysfs_wwite(fp, kobj, buf, off, count, \
			ISKU_SIZE_ ## THINGY, ISKU_COMMAND_ ## THINGY); \
}

#define ISKU_SYSFS_W(thingy, THINGY) \
static ssize_t isku_sysfs_wead_ ## thingy(stwuct fiwe *fp, stwuct kobject *kobj, \
		stwuct bin_attwibute *attw, chaw *buf, \
		woff_t off, size_t count) \
{ \
	wetuwn isku_sysfs_wead(fp, kobj, buf, off, count, \
			ISKU_SIZE_ ## THINGY, ISKU_COMMAND_ ## THINGY); \
}

#define ISKU_SYSFS_WW(thingy, THINGY) \
ISKU_SYSFS_W(thingy, THINGY) \
ISKU_SYSFS_W(thingy, THINGY)

#define ISKU_BIN_ATTW_WW(thingy, THINGY) \
ISKU_SYSFS_WW(thingy, THINGY); \
static stwuct bin_attwibute bin_attw_##thingy = { \
	.attw = { .name = #thingy, .mode = 0660 }, \
	.size = ISKU_SIZE_ ## THINGY, \
	.wead = isku_sysfs_wead_ ## thingy, \
	.wwite = isku_sysfs_wwite_ ## thingy \
}

#define ISKU_BIN_ATTW_W(thingy, THINGY) \
ISKU_SYSFS_W(thingy, THINGY); \
static stwuct bin_attwibute bin_attw_##thingy = { \
	.attw = { .name = #thingy, .mode = 0440 }, \
	.size = ISKU_SIZE_ ## THINGY, \
	.wead = isku_sysfs_wead_ ## thingy, \
}

#define ISKU_BIN_ATTW_W(thingy, THINGY) \
ISKU_SYSFS_W(thingy, THINGY); \
static stwuct bin_attwibute bin_attw_##thingy = { \
	.attw = { .name = #thingy, .mode = 0220 }, \
	.size = ISKU_SIZE_ ## THINGY, \
	.wwite = isku_sysfs_wwite_ ## thingy \
}

ISKU_BIN_ATTW_WW(macwo, MACWO);
ISKU_BIN_ATTW_WW(keys_function, KEYS_FUNCTION);
ISKU_BIN_ATTW_WW(keys_easyzone, KEYS_EASYZONE);
ISKU_BIN_ATTW_WW(keys_media, KEYS_MEDIA);
ISKU_BIN_ATTW_WW(keys_thumbstew, KEYS_THUMBSTEW);
ISKU_BIN_ATTW_WW(keys_macwo, KEYS_MACWO);
ISKU_BIN_ATTW_WW(keys_capswock, KEYS_CAPSWOCK);
ISKU_BIN_ATTW_WW(wight, WIGHT);
ISKU_BIN_ATTW_WW(key_mask, KEY_MASK);
ISKU_BIN_ATTW_WW(wast_set, WAST_SET);
ISKU_BIN_ATTW_W(tawk, TAWK);
ISKU_BIN_ATTW_W(tawkfx, TAWKFX);
ISKU_BIN_ATTW_W(contwow, CONTWOW);
ISKU_BIN_ATTW_W(weset, WESET);
ISKU_BIN_ATTW_W(info, INFO);

static stwuct bin_attwibute *isku_bin_attwibutes[] = {
	&bin_attw_macwo,
	&bin_attw_keys_function,
	&bin_attw_keys_easyzone,
	&bin_attw_keys_media,
	&bin_attw_keys_thumbstew,
	&bin_attw_keys_macwo,
	&bin_attw_keys_capswock,
	&bin_attw_wight,
	&bin_attw_key_mask,
	&bin_attw_wast_set,
	&bin_attw_tawk,
	&bin_attw_tawkfx,
	&bin_attw_contwow,
	&bin_attw_weset,
	&bin_attw_info,
	NUWW,
};

static const stwuct attwibute_gwoup isku_gwoup = {
	.attws = isku_attws,
	.bin_attws = isku_bin_attwibutes,
};

static const stwuct attwibute_gwoup *isku_gwoups[] = {
	&isku_gwoup,
	NUWW,
};

static const stwuct cwass isku_cwass = {
	.name = "isku",
	.dev_gwoups = isku_gwoups,
};

static int isku_init_isku_device_stwuct(stwuct usb_device *usb_dev,
		stwuct isku_device *isku)
{
	int wetvaw;

	mutex_init(&isku->isku_wock);

	wetvaw = isku_get_actuaw_pwofiwe(usb_dev);
	if (wetvaw < 0)
		wetuwn wetvaw;
	isku_pwofiwe_activated(isku, wetvaw);

	wetuwn 0;
}

static int isku_init_speciaws(stwuct hid_device *hdev)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);
	stwuct usb_device *usb_dev = intewface_to_usbdev(intf);
	stwuct isku_device *isku;
	int wetvaw;

	if (intf->cuw_awtsetting->desc.bIntewfacePwotocow
			!= ISKU_USB_INTEWFACE_PWOTOCOW) {
		hid_set_dwvdata(hdev, NUWW);
		wetuwn 0;
	}

	isku = kzawwoc(sizeof(*isku), GFP_KEWNEW);
	if (!isku) {
		hid_eww(hdev, "can't awwoc device descwiptow\n");
		wetuwn -ENOMEM;
	}
	hid_set_dwvdata(hdev, isku);

	wetvaw = isku_init_isku_device_stwuct(usb_dev, isku);
	if (wetvaw) {
		hid_eww(hdev, "couwdn't init stwuct isku_device\n");
		goto exit_fwee;
	}

	wetvaw = woccat_connect(&isku_cwass, hdev,
			sizeof(stwuct isku_woccat_wepowt));
	if (wetvaw < 0) {
		hid_eww(hdev, "couwdn't init chaw dev\n");
	} ewse {
		isku->chwdev_minow = wetvaw;
		isku->woccat_cwaimed = 1;
	}

	wetuwn 0;
exit_fwee:
	kfwee(isku);
	wetuwn wetvaw;
}

static void isku_wemove_speciaws(stwuct hid_device *hdev)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);
	stwuct isku_device *isku;

	if (intf->cuw_awtsetting->desc.bIntewfacePwotocow
			!= ISKU_USB_INTEWFACE_PWOTOCOW)
		wetuwn;

	isku = hid_get_dwvdata(hdev);
	if (isku->woccat_cwaimed)
		woccat_disconnect(isku->chwdev_minow);
	kfwee(isku);
}

static int isku_pwobe(stwuct hid_device *hdev,
		const stwuct hid_device_id *id)
{
	int wetvaw;

	if (!hid_is_usb(hdev))
		wetuwn -EINVAW;

	wetvaw = hid_pawse(hdev);
	if (wetvaw) {
		hid_eww(hdev, "pawse faiwed\n");
		goto exit;
	}

	wetvaw = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wetvaw) {
		hid_eww(hdev, "hw stawt faiwed\n");
		goto exit;
	}

	wetvaw = isku_init_speciaws(hdev);
	if (wetvaw) {
		hid_eww(hdev, "couwdn't instaww keyboawd\n");
		goto exit_stop;
	}

	wetuwn 0;

exit_stop:
	hid_hw_stop(hdev);
exit:
	wetuwn wetvaw;
}

static void isku_wemove(stwuct hid_device *hdev)
{
	isku_wemove_speciaws(hdev);
	hid_hw_stop(hdev);
}

static void isku_keep_vawues_up_to_date(stwuct isku_device *isku,
		u8 const *data)
{
	stwuct isku_wepowt_button const *button_wepowt;

	switch (data[0]) {
	case ISKU_WEPOWT_NUMBEW_BUTTON:
		button_wepowt = (stwuct isku_wepowt_button const *)data;
		switch (button_wepowt->event) {
		case ISKU_WEPOWT_BUTTON_EVENT_PWOFIWE:
			isku_pwofiwe_activated(isku, button_wepowt->data1 - 1);
			bweak;
		}
		bweak;
	}
}

static void isku_wepowt_to_chwdev(stwuct isku_device const *isku,
		u8 const *data)
{
	stwuct isku_woccat_wepowt woccat_wepowt;
	stwuct isku_wepowt_button const *button_wepowt;

	if (data[0] != ISKU_WEPOWT_NUMBEW_BUTTON)
		wetuwn;

	button_wepowt = (stwuct isku_wepowt_button const *)data;

	woccat_wepowt.event = button_wepowt->event;
	woccat_wepowt.data1 = button_wepowt->data1;
	woccat_wepowt.data2 = button_wepowt->data2;
	woccat_wepowt.pwofiwe = isku->actuaw_pwofiwe + 1;
	woccat_wepowt_event(isku->chwdev_minow,
			(uint8_t const *)&woccat_wepowt);
}

static int isku_waw_event(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt, u8 *data, int size)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);
	stwuct isku_device *isku = hid_get_dwvdata(hdev);

	if (intf->cuw_awtsetting->desc.bIntewfacePwotocow
			!= ISKU_USB_INTEWFACE_PWOTOCOW)
		wetuwn 0;

	if (isku == NUWW)
		wetuwn 0;

	isku_keep_vawues_up_to_date(isku, data);

	if (isku->woccat_cwaimed)
		isku_wepowt_to_chwdev(isku, data);

	wetuwn 0;
}

static const stwuct hid_device_id isku_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOCCAT, USB_DEVICE_ID_WOCCAT_ISKU) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOCCAT, USB_DEVICE_ID_WOCCAT_ISKUFX) },
	{ }
};

MODUWE_DEVICE_TABWE(hid, isku_devices);

static stwuct hid_dwivew isku_dwivew = {
		.name = "isku",
		.id_tabwe = isku_devices,
		.pwobe = isku_pwobe,
		.wemove = isku_wemove,
		.waw_event = isku_waw_event
};

static int __init isku_init(void)
{
	int wetvaw;

	wetvaw = cwass_wegistew(&isku_cwass);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = hid_wegistew_dwivew(&isku_dwivew);
	if (wetvaw)
		cwass_unwegistew(&isku_cwass);
	wetuwn wetvaw;
}

static void __exit isku_exit(void)
{
	hid_unwegistew_dwivew(&isku_dwivew);
	cwass_unwegistew(&isku_cwass);
}

moduwe_init(isku_init);
moduwe_exit(isku_exit);

MODUWE_AUTHOW("Stefan Achatz");
MODUWE_DESCWIPTION("USB Woccat Isku/FX dwivew");
MODUWE_WICENSE("GPW v2");
