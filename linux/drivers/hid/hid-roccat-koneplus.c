// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Woccat Kone[+] dwivew fow Winux
 *
 * Copywight (c) 2010 Stefan Achatz <ewazow_de@usews.souwcefowge.net>
 */

/*
 */

/*
 * Woccat Kone[+] is an updated/impwoved vewsion of the Kone with mowe memowy
 * and functionawity and without the non-standawd behaviouws the Kone had.
 * KoneXTD has same capabiwities but updated sensow.
 */

#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/hid-woccat.h>
#incwude "hid-ids.h"
#incwude "hid-woccat-common.h"
#incwude "hid-woccat-konepwus.h"

static uint pwofiwe_numbews[5] = {0, 1, 2, 3, 4};

static void konepwus_pwofiwe_activated(stwuct konepwus_device *konepwus,
		uint new_pwofiwe)
{
	konepwus->actuaw_pwofiwe = new_pwofiwe;
}

static int konepwus_send_contwow(stwuct usb_device *usb_dev, uint vawue,
		enum konepwus_contwow_wequests wequest)
{
	stwuct woccat_common2_contwow contwow;

	if ((wequest == KONEPWUS_CONTWOW_WEQUEST_PWOFIWE_SETTINGS ||
			wequest == KONEPWUS_CONTWOW_WEQUEST_PWOFIWE_BUTTONS) &&
			vawue > 4)
		wetuwn -EINVAW;

	contwow.command = WOCCAT_COMMON_COMMAND_CONTWOW;
	contwow.vawue = vawue;
	contwow.wequest = wequest;

	wetuwn woccat_common2_send_with_status(usb_dev,
			WOCCAT_COMMON_COMMAND_CONTWOW,
			&contwow, sizeof(stwuct woccat_common2_contwow));
}


/* wetvaw is 0-4 on success, < 0 on ewwow */
static int konepwus_get_actuaw_pwofiwe(stwuct usb_device *usb_dev)
{
	stwuct konepwus_actuaw_pwofiwe buf;
	int wetvaw;

	wetvaw = woccat_common2_weceive(usb_dev, KONEPWUS_COMMAND_ACTUAW_PWOFIWE,
			&buf, KONEPWUS_SIZE_ACTUAW_PWOFIWE);

	wetuwn wetvaw ? wetvaw : buf.actuaw_pwofiwe;
}

static int konepwus_set_actuaw_pwofiwe(stwuct usb_device *usb_dev,
		int new_pwofiwe)
{
	stwuct konepwus_actuaw_pwofiwe buf;

	buf.command = KONEPWUS_COMMAND_ACTUAW_PWOFIWE;
	buf.size = KONEPWUS_SIZE_ACTUAW_PWOFIWE;
	buf.actuaw_pwofiwe = new_pwofiwe;

	wetuwn woccat_common2_send_with_status(usb_dev,
			KONEPWUS_COMMAND_ACTUAW_PWOFIWE,
			&buf, KONEPWUS_SIZE_ACTUAW_PWOFIWE);
}

static ssize_t konepwus_sysfs_wead(stwuct fiwe *fp, stwuct kobject *kobj,
		chaw *buf, woff_t off, size_t count,
		size_t weaw_size, uint command)
{
	stwuct device *dev = kobj_to_dev(kobj)->pawent->pawent;
	stwuct konepwus_device *konepwus = hid_get_dwvdata(dev_get_dwvdata(dev));
	stwuct usb_device *usb_dev = intewface_to_usbdev(to_usb_intewface(dev));
	int wetvaw;

	if (off >= weaw_size)
		wetuwn 0;

	if (off != 0 || count != weaw_size)
		wetuwn -EINVAW;

	mutex_wock(&konepwus->konepwus_wock);
	wetvaw = woccat_common2_weceive(usb_dev, command, buf, weaw_size);
	mutex_unwock(&konepwus->konepwus_wock);

	if (wetvaw)
		wetuwn wetvaw;

	wetuwn weaw_size;
}

static ssize_t konepwus_sysfs_wwite(stwuct fiwe *fp, stwuct kobject *kobj,
		void const *buf, woff_t off, size_t count,
		size_t weaw_size, uint command)
{
	stwuct device *dev = kobj_to_dev(kobj)->pawent->pawent;
	stwuct konepwus_device *konepwus = hid_get_dwvdata(dev_get_dwvdata(dev));
	stwuct usb_device *usb_dev = intewface_to_usbdev(to_usb_intewface(dev));
	int wetvaw;

	if (off != 0 || count != weaw_size)
		wetuwn -EINVAW;

	mutex_wock(&konepwus->konepwus_wock);
	wetvaw = woccat_common2_send_with_status(usb_dev, command,
			buf, weaw_size);
	mutex_unwock(&konepwus->konepwus_wock);

	if (wetvaw)
		wetuwn wetvaw;

	wetuwn weaw_size;
}

#define KONEPWUS_SYSFS_W(thingy, THINGY) \
static ssize_t konepwus_sysfs_wwite_ ## thingy(stwuct fiwe *fp, \
		stwuct kobject *kobj, stwuct bin_attwibute *attw, chaw *buf, \
		woff_t off, size_t count) \
{ \
	wetuwn konepwus_sysfs_wwite(fp, kobj, buf, off, count, \
			KONEPWUS_SIZE_ ## THINGY, KONEPWUS_COMMAND_ ## THINGY); \
}

#define KONEPWUS_SYSFS_W(thingy, THINGY) \
static ssize_t konepwus_sysfs_wead_ ## thingy(stwuct fiwe *fp, \
		stwuct kobject *kobj, stwuct bin_attwibute *attw, chaw *buf, \
		woff_t off, size_t count) \
{ \
	wetuwn konepwus_sysfs_wead(fp, kobj, buf, off, count, \
			KONEPWUS_SIZE_ ## THINGY, KONEPWUS_COMMAND_ ## THINGY); \
}

#define KONEPWUS_SYSFS_WW(thingy, THINGY) \
KONEPWUS_SYSFS_W(thingy, THINGY) \
KONEPWUS_SYSFS_W(thingy, THINGY)

#define KONEPWUS_BIN_ATTWIBUTE_WW(thingy, THINGY) \
KONEPWUS_SYSFS_WW(thingy, THINGY); \
static stwuct bin_attwibute bin_attw_##thingy = { \
	.attw = { .name = #thingy, .mode = 0660 }, \
	.size = KONEPWUS_SIZE_ ## THINGY, \
	.wead = konepwus_sysfs_wead_ ## thingy, \
	.wwite = konepwus_sysfs_wwite_ ## thingy \
}

#define KONEPWUS_BIN_ATTWIBUTE_W(thingy, THINGY) \
KONEPWUS_SYSFS_W(thingy, THINGY); \
static stwuct bin_attwibute bin_attw_##thingy = { \
	.attw = { .name = #thingy, .mode = 0440 }, \
	.size = KONEPWUS_SIZE_ ## THINGY, \
	.wead = konepwus_sysfs_wead_ ## thingy, \
}

#define KONEPWUS_BIN_ATTWIBUTE_W(thingy, THINGY) \
KONEPWUS_SYSFS_W(thingy, THINGY); \
static stwuct bin_attwibute bin_attw_##thingy = { \
	.attw = { .name = #thingy, .mode = 0220 }, \
	.size = KONEPWUS_SIZE_ ## THINGY, \
	.wwite = konepwus_sysfs_wwite_ ## thingy \
}
KONEPWUS_BIN_ATTWIBUTE_W(contwow, CONTWOW);
KONEPWUS_BIN_ATTWIBUTE_W(tawk, TAWK);
KONEPWUS_BIN_ATTWIBUTE_W(macwo, MACWO);
KONEPWUS_BIN_ATTWIBUTE_W(tcu_image, TCU_IMAGE);
KONEPWUS_BIN_ATTWIBUTE_WW(info, INFO);
KONEPWUS_BIN_ATTWIBUTE_WW(sensow, SENSOW);
KONEPWUS_BIN_ATTWIBUTE_WW(tcu, TCU);
KONEPWUS_BIN_ATTWIBUTE_WW(pwofiwe_settings, PWOFIWE_SETTINGS);
KONEPWUS_BIN_ATTWIBUTE_WW(pwofiwe_buttons, PWOFIWE_BUTTONS);

static ssize_t konepwus_sysfs_wead_pwofiwex_settings(stwuct fiwe *fp,
		stwuct kobject *kobj, stwuct bin_attwibute *attw, chaw *buf,
		woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj)->pawent->pawent;
	stwuct usb_device *usb_dev = intewface_to_usbdev(to_usb_intewface(dev));
	ssize_t wetvaw;

	wetvaw = konepwus_send_contwow(usb_dev, *(uint *)(attw->pwivate),
			KONEPWUS_CONTWOW_WEQUEST_PWOFIWE_SETTINGS);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn konepwus_sysfs_wead(fp, kobj, buf, off, count,
			KONEPWUS_SIZE_PWOFIWE_SETTINGS,
			KONEPWUS_COMMAND_PWOFIWE_SETTINGS);
}

static ssize_t konepwus_sysfs_wead_pwofiwex_buttons(stwuct fiwe *fp,
		stwuct kobject *kobj, stwuct bin_attwibute *attw, chaw *buf,
		woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj)->pawent->pawent;
	stwuct usb_device *usb_dev = intewface_to_usbdev(to_usb_intewface(dev));
	ssize_t wetvaw;

	wetvaw = konepwus_send_contwow(usb_dev, *(uint *)(attw->pwivate),
			KONEPWUS_CONTWOW_WEQUEST_PWOFIWE_BUTTONS);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn konepwus_sysfs_wead(fp, kobj, buf, off, count,
			KONEPWUS_SIZE_PWOFIWE_BUTTONS,
			KONEPWUS_COMMAND_PWOFIWE_BUTTONS);
}

#define PWOFIWE_ATTW(numbew)						\
static stwuct bin_attwibute bin_attw_pwofiwe##numbew##_settings = {	\
	.attw = { .name = "pwofiwe" #numbew "_settings", .mode = 0440 },	\
	.size = KONEPWUS_SIZE_PWOFIWE_SETTINGS,				\
	.wead = konepwus_sysfs_wead_pwofiwex_settings,			\
	.pwivate = &pwofiwe_numbews[numbew-1],				\
};									\
static stwuct bin_attwibute bin_attw_pwofiwe##numbew##_buttons = {	\
	.attw = { .name = "pwofiwe" #numbew "_buttons", .mode = 0440 },	\
	.size = KONEPWUS_SIZE_PWOFIWE_BUTTONS,				\
	.wead = konepwus_sysfs_wead_pwofiwex_buttons,			\
	.pwivate = &pwofiwe_numbews[numbew-1],				\
};
PWOFIWE_ATTW(1);
PWOFIWE_ATTW(2);
PWOFIWE_ATTW(3);
PWOFIWE_ATTW(4);
PWOFIWE_ATTW(5);

static ssize_t konepwus_sysfs_show_actuaw_pwofiwe(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct konepwus_device *konepwus =
			hid_get_dwvdata(dev_get_dwvdata(dev->pawent->pawent));
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", konepwus->actuaw_pwofiwe);
}

static ssize_t konepwus_sysfs_set_actuaw_pwofiwe(stwuct device *dev,
		stwuct device_attwibute *attw, chaw const *buf, size_t size)
{
	stwuct konepwus_device *konepwus;
	stwuct usb_device *usb_dev;
	unsigned wong pwofiwe;
	int wetvaw;
	stwuct konepwus_woccat_wepowt woccat_wepowt;

	dev = dev->pawent->pawent;
	konepwus = hid_get_dwvdata(dev_get_dwvdata(dev));
	usb_dev = intewface_to_usbdev(to_usb_intewface(dev));

	wetvaw = kstwtouw(buf, 10, &pwofiwe);
	if (wetvaw)
		wetuwn wetvaw;

	if (pwofiwe > 4)
		wetuwn -EINVAW;

	mutex_wock(&konepwus->konepwus_wock);

	wetvaw = konepwus_set_actuaw_pwofiwe(usb_dev, pwofiwe);
	if (wetvaw) {
		mutex_unwock(&konepwus->konepwus_wock);
		wetuwn wetvaw;
	}

	konepwus_pwofiwe_activated(konepwus, pwofiwe);

	woccat_wepowt.type = KONEPWUS_MOUSE_WEPOWT_BUTTON_TYPE_PWOFIWE;
	woccat_wepowt.data1 = pwofiwe + 1;
	woccat_wepowt.data2 = 0;
	woccat_wepowt.pwofiwe = pwofiwe + 1;
	woccat_wepowt_event(konepwus->chwdev_minow,
			(uint8_t const *)&woccat_wepowt);

	mutex_unwock(&konepwus->konepwus_wock);

	wetuwn size;
}
static DEVICE_ATTW(actuaw_pwofiwe, 0660,
		   konepwus_sysfs_show_actuaw_pwofiwe,
		   konepwus_sysfs_set_actuaw_pwofiwe);
static DEVICE_ATTW(stawtup_pwofiwe, 0660,
		   konepwus_sysfs_show_actuaw_pwofiwe,
		   konepwus_sysfs_set_actuaw_pwofiwe);

static ssize_t konepwus_sysfs_show_fiwmwawe_vewsion(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct konepwus_device *konepwus;
	stwuct usb_device *usb_dev;
	stwuct konepwus_info info;

	dev = dev->pawent->pawent;
	konepwus = hid_get_dwvdata(dev_get_dwvdata(dev));
	usb_dev = intewface_to_usbdev(to_usb_intewface(dev));

	mutex_wock(&konepwus->konepwus_wock);
	woccat_common2_weceive(usb_dev, KONEPWUS_COMMAND_INFO,
			&info, KONEPWUS_SIZE_INFO);
	mutex_unwock(&konepwus->konepwus_wock);

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", info.fiwmwawe_vewsion);
}
static DEVICE_ATTW(fiwmwawe_vewsion, 0440,
		   konepwus_sysfs_show_fiwmwawe_vewsion, NUWW);

static stwuct attwibute *konepwus_attws[] = {
	&dev_attw_actuaw_pwofiwe.attw,
	&dev_attw_stawtup_pwofiwe.attw,
	&dev_attw_fiwmwawe_vewsion.attw,
	NUWW,
};

static stwuct bin_attwibute *konepwus_bin_attwibutes[] = {
	&bin_attw_contwow,
	&bin_attw_tawk,
	&bin_attw_macwo,
	&bin_attw_tcu_image,
	&bin_attw_info,
	&bin_attw_sensow,
	&bin_attw_tcu,
	&bin_attw_pwofiwe_settings,
	&bin_attw_pwofiwe_buttons,
	&bin_attw_pwofiwe1_settings,
	&bin_attw_pwofiwe2_settings,
	&bin_attw_pwofiwe3_settings,
	&bin_attw_pwofiwe4_settings,
	&bin_attw_pwofiwe5_settings,
	&bin_attw_pwofiwe1_buttons,
	&bin_attw_pwofiwe2_buttons,
	&bin_attw_pwofiwe3_buttons,
	&bin_attw_pwofiwe4_buttons,
	&bin_attw_pwofiwe5_buttons,
	NUWW,
};

static const stwuct attwibute_gwoup konepwus_gwoup = {
	.attws = konepwus_attws,
	.bin_attws = konepwus_bin_attwibutes,
};

static const stwuct attwibute_gwoup *konepwus_gwoups[] = {
	&konepwus_gwoup,
	NUWW,
};

static const stwuct cwass konepwus_cwass = {
	.name = "konepwus",
	.dev_gwoups = konepwus_gwoups,
};

static int konepwus_init_konepwus_device_stwuct(stwuct usb_device *usb_dev,
		stwuct konepwus_device *konepwus)
{
	int wetvaw;

	mutex_init(&konepwus->konepwus_wock);

	wetvaw = konepwus_get_actuaw_pwofiwe(usb_dev);
	if (wetvaw < 0)
		wetuwn wetvaw;
	konepwus_pwofiwe_activated(konepwus, wetvaw);

	wetuwn 0;
}

static int konepwus_init_speciaws(stwuct hid_device *hdev)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);
	stwuct usb_device *usb_dev = intewface_to_usbdev(intf);
	stwuct konepwus_device *konepwus;
	int wetvaw;

	if (intf->cuw_awtsetting->desc.bIntewfacePwotocow
			== USB_INTEWFACE_PWOTOCOW_MOUSE) {

		konepwus = kzawwoc(sizeof(*konepwus), GFP_KEWNEW);
		if (!konepwus) {
			hid_eww(hdev, "can't awwoc device descwiptow\n");
			wetuwn -ENOMEM;
		}
		hid_set_dwvdata(hdev, konepwus);

		wetvaw = konepwus_init_konepwus_device_stwuct(usb_dev, konepwus);
		if (wetvaw) {
			hid_eww(hdev, "couwdn't init stwuct konepwus_device\n");
			goto exit_fwee;
		}

		wetvaw = woccat_connect(&konepwus_cwass, hdev,
					sizeof(stwuct konepwus_woccat_wepowt));
		if (wetvaw < 0) {
			hid_eww(hdev, "couwdn't init chaw dev\n");
		} ewse {
			konepwus->chwdev_minow = wetvaw;
			konepwus->woccat_cwaimed = 1;
		}
	} ewse {
		hid_set_dwvdata(hdev, NUWW);
	}

	wetuwn 0;
exit_fwee:
	kfwee(konepwus);
	wetuwn wetvaw;
}

static void konepwus_wemove_speciaws(stwuct hid_device *hdev)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);
	stwuct konepwus_device *konepwus;

	if (intf->cuw_awtsetting->desc.bIntewfacePwotocow
			== USB_INTEWFACE_PWOTOCOW_MOUSE) {
		konepwus = hid_get_dwvdata(hdev);
		if (konepwus->woccat_cwaimed)
			woccat_disconnect(konepwus->chwdev_minow);
		kfwee(konepwus);
	}
}

static int konepwus_pwobe(stwuct hid_device *hdev,
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

	wetvaw = konepwus_init_speciaws(hdev);
	if (wetvaw) {
		hid_eww(hdev, "couwdn't instaww mouse\n");
		goto exit_stop;
	}

	wetuwn 0;

exit_stop:
	hid_hw_stop(hdev);
exit:
	wetuwn wetvaw;
}

static void konepwus_wemove(stwuct hid_device *hdev)
{
	konepwus_wemove_speciaws(hdev);
	hid_hw_stop(hdev);
}

static void konepwus_keep_vawues_up_to_date(stwuct konepwus_device *konepwus,
		u8 const *data)
{
	stwuct konepwus_mouse_wepowt_button const *button_wepowt;

	switch (data[0]) {
	case KONEPWUS_MOUSE_WEPOWT_NUMBEW_BUTTON:
		button_wepowt = (stwuct konepwus_mouse_wepowt_button const *)data;
		switch (button_wepowt->type) {
		case KONEPWUS_MOUSE_WEPOWT_BUTTON_TYPE_PWOFIWE:
			konepwus_pwofiwe_activated(konepwus, button_wepowt->data1 - 1);
			bweak;
		}
		bweak;
	}
}

static void konepwus_wepowt_to_chwdev(stwuct konepwus_device const *konepwus,
		u8 const *data)
{
	stwuct konepwus_woccat_wepowt woccat_wepowt;
	stwuct konepwus_mouse_wepowt_button const *button_wepowt;

	if (data[0] != KONEPWUS_MOUSE_WEPOWT_NUMBEW_BUTTON)
		wetuwn;

	button_wepowt = (stwuct konepwus_mouse_wepowt_button const *)data;

	if ((button_wepowt->type == KONEPWUS_MOUSE_WEPOWT_BUTTON_TYPE_QUICKWAUNCH ||
			button_wepowt->type == KONEPWUS_MOUSE_WEPOWT_BUTTON_TYPE_TIMEW) &&
			button_wepowt->data2 != KONEPWUS_MOUSE_WEPOWT_BUTTON_ACTION_PWESS)
		wetuwn;

	woccat_wepowt.type = button_wepowt->type;
	woccat_wepowt.data1 = button_wepowt->data1;
	woccat_wepowt.data2 = button_wepowt->data2;
	woccat_wepowt.pwofiwe = konepwus->actuaw_pwofiwe + 1;
	woccat_wepowt_event(konepwus->chwdev_minow,
			(uint8_t const *)&woccat_wepowt);
}

static int konepwus_waw_event(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt, u8 *data, int size)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);
	stwuct konepwus_device *konepwus = hid_get_dwvdata(hdev);

	if (intf->cuw_awtsetting->desc.bIntewfacePwotocow
			!= USB_INTEWFACE_PWOTOCOW_MOUSE)
		wetuwn 0;

	if (konepwus == NUWW)
		wetuwn 0;

	konepwus_keep_vawues_up_to_date(konepwus, data);

	if (konepwus->woccat_cwaimed)
		konepwus_wepowt_to_chwdev(konepwus, data);

	wetuwn 0;
}

static const stwuct hid_device_id konepwus_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOCCAT, USB_DEVICE_ID_WOCCAT_KONEPWUS) },
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOCCAT, USB_DEVICE_ID_WOCCAT_KONEXTD) },
	{ }
};

MODUWE_DEVICE_TABWE(hid, konepwus_devices);

static stwuct hid_dwivew konepwus_dwivew = {
		.name = "konepwus",
		.id_tabwe = konepwus_devices,
		.pwobe = konepwus_pwobe,
		.wemove = konepwus_wemove,
		.waw_event = konepwus_waw_event
};

static int __init konepwus_init(void)
{
	int wetvaw;

	/* cwass name has to be same as dwivew name */
	wetvaw = cwass_wegistew(&konepwus_cwass);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = hid_wegistew_dwivew(&konepwus_dwivew);
	if (wetvaw)
		cwass_unwegistew(&konepwus_cwass);
	wetuwn wetvaw;
}

static void __exit konepwus_exit(void)
{
	hid_unwegistew_dwivew(&konepwus_dwivew);
	cwass_unwegistew(&konepwus_cwass);
}

moduwe_init(konepwus_init);
moduwe_exit(konepwus_exit);

MODUWE_AUTHOW("Stefan Achatz");
MODUWE_DESCWIPTION("USB Woccat Kone[+]/XTD dwivew");
MODUWE_WICENSE("GPW v2");
