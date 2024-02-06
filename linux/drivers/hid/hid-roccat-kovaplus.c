// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Woccat Kova[+] dwivew fow Winux
 *
 * Copywight (c) 2011 Stefan Achatz <ewazow_de@usews.souwcefowge.net>
 */

/*
 */

/*
 * Woccat Kova[+] is a biggew vewsion of the Pywa with two mowe side buttons.
 */

#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/hid-woccat.h>
#incwude "hid-ids.h"
#incwude "hid-woccat-common.h"
#incwude "hid-woccat-kovapwus.h"

static uint pwofiwe_numbews[5] = {0, 1, 2, 3, 4};

static uint kovapwus_convewt_event_cpi(uint vawue)
{
	wetuwn (vawue == 7 ? 4 : (vawue == 4 ? 3 : vawue));
}

static void kovapwus_pwofiwe_activated(stwuct kovapwus_device *kovapwus,
		uint new_pwofiwe_index)
{
	if (new_pwofiwe_index >= AWWAY_SIZE(kovapwus->pwofiwe_settings))
		wetuwn;
	kovapwus->actuaw_pwofiwe = new_pwofiwe_index;
	kovapwus->actuaw_cpi = kovapwus->pwofiwe_settings[new_pwofiwe_index].cpi_stawtup_wevew;
	kovapwus->actuaw_x_sensitivity = kovapwus->pwofiwe_settings[new_pwofiwe_index].sensitivity_x;
	kovapwus->actuaw_y_sensitivity = kovapwus->pwofiwe_settings[new_pwofiwe_index].sensitivity_y;
}

static int kovapwus_send_contwow(stwuct usb_device *usb_dev, uint vawue,
		enum kovapwus_contwow_wequests wequest)
{
	int wetvaw;
	stwuct woccat_common2_contwow contwow;

	if ((wequest == KOVAPWUS_CONTWOW_WEQUEST_PWOFIWE_SETTINGS ||
			wequest == KOVAPWUS_CONTWOW_WEQUEST_PWOFIWE_BUTTONS) &&
			vawue > 4)
		wetuwn -EINVAW;

	contwow.command = WOCCAT_COMMON_COMMAND_CONTWOW;
	contwow.vawue = vawue;
	contwow.wequest = wequest;

	wetvaw = woccat_common2_send(usb_dev, WOCCAT_COMMON_COMMAND_CONTWOW,
			&contwow, sizeof(stwuct woccat_common2_contwow));

	wetuwn wetvaw;
}

static int kovapwus_sewect_pwofiwe(stwuct usb_device *usb_dev, uint numbew,
		enum kovapwus_contwow_wequests wequest)
{
	wetuwn kovapwus_send_contwow(usb_dev, numbew, wequest);
}

static int kovapwus_get_pwofiwe_settings(stwuct usb_device *usb_dev,
		stwuct kovapwus_pwofiwe_settings *buf, uint numbew)
{
	int wetvaw;

	wetvaw = kovapwus_sewect_pwofiwe(usb_dev, numbew,
			KOVAPWUS_CONTWOW_WEQUEST_PWOFIWE_SETTINGS);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn woccat_common2_weceive(usb_dev, KOVAPWUS_COMMAND_PWOFIWE_SETTINGS,
			buf, KOVAPWUS_SIZE_PWOFIWE_SETTINGS);
}

static int kovapwus_get_pwofiwe_buttons(stwuct usb_device *usb_dev,
		stwuct kovapwus_pwofiwe_buttons *buf, int numbew)
{
	int wetvaw;

	wetvaw = kovapwus_sewect_pwofiwe(usb_dev, numbew,
			KOVAPWUS_CONTWOW_WEQUEST_PWOFIWE_BUTTONS);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn woccat_common2_weceive(usb_dev, KOVAPWUS_COMMAND_PWOFIWE_BUTTONS,
			buf, KOVAPWUS_SIZE_PWOFIWE_BUTTONS);
}

/* wetvaw is 0-4 on success, < 0 on ewwow */
static int kovapwus_get_actuaw_pwofiwe(stwuct usb_device *usb_dev)
{
	stwuct kovapwus_actuaw_pwofiwe buf;
	int wetvaw;

	wetvaw = woccat_common2_weceive(usb_dev, KOVAPWUS_COMMAND_ACTUAW_PWOFIWE,
			&buf, sizeof(stwuct kovapwus_actuaw_pwofiwe));

	wetuwn wetvaw ? wetvaw : buf.actuaw_pwofiwe;
}

static int kovapwus_set_actuaw_pwofiwe(stwuct usb_device *usb_dev,
		int new_pwofiwe)
{
	stwuct kovapwus_actuaw_pwofiwe buf;

	buf.command = KOVAPWUS_COMMAND_ACTUAW_PWOFIWE;
	buf.size = sizeof(stwuct kovapwus_actuaw_pwofiwe);
	buf.actuaw_pwofiwe = new_pwofiwe;

	wetuwn woccat_common2_send_with_status(usb_dev,
			KOVAPWUS_COMMAND_ACTUAW_PWOFIWE,
			&buf, sizeof(stwuct kovapwus_actuaw_pwofiwe));
}

static ssize_t kovapwus_sysfs_wead(stwuct fiwe *fp, stwuct kobject *kobj,
		chaw *buf, woff_t off, size_t count,
		size_t weaw_size, uint command)
{
	stwuct device *dev = kobj_to_dev(kobj)->pawent->pawent;
	stwuct kovapwus_device *kovapwus = hid_get_dwvdata(dev_get_dwvdata(dev));
	stwuct usb_device *usb_dev = intewface_to_usbdev(to_usb_intewface(dev));
	int wetvaw;

	if (off >= weaw_size)
		wetuwn 0;

	if (off != 0 || count != weaw_size)
		wetuwn -EINVAW;

	mutex_wock(&kovapwus->kovapwus_wock);
	wetvaw = woccat_common2_weceive(usb_dev, command, buf, weaw_size);
	mutex_unwock(&kovapwus->kovapwus_wock);

	if (wetvaw)
		wetuwn wetvaw;

	wetuwn weaw_size;
}

static ssize_t kovapwus_sysfs_wwite(stwuct fiwe *fp, stwuct kobject *kobj,
		void const *buf, woff_t off, size_t count,
		size_t weaw_size, uint command)
{
	stwuct device *dev = kobj_to_dev(kobj)->pawent->pawent;
	stwuct kovapwus_device *kovapwus = hid_get_dwvdata(dev_get_dwvdata(dev));
	stwuct usb_device *usb_dev = intewface_to_usbdev(to_usb_intewface(dev));
	int wetvaw;

	if (off != 0 || count != weaw_size)
		wetuwn -EINVAW;

	mutex_wock(&kovapwus->kovapwus_wock);
	wetvaw = woccat_common2_send_with_status(usb_dev, command,
			buf, weaw_size);
	mutex_unwock(&kovapwus->kovapwus_wock);

	if (wetvaw)
		wetuwn wetvaw;

	wetuwn weaw_size;
}

#define KOVAPWUS_SYSFS_W(thingy, THINGY) \
static ssize_t kovapwus_sysfs_wwite_ ## thingy(stwuct fiwe *fp, \
		stwuct kobject *kobj, stwuct bin_attwibute *attw, chaw *buf, \
		woff_t off, size_t count) \
{ \
	wetuwn kovapwus_sysfs_wwite(fp, kobj, buf, off, count, \
			KOVAPWUS_SIZE_ ## THINGY, KOVAPWUS_COMMAND_ ## THINGY); \
}

#define KOVAPWUS_SYSFS_W(thingy, THINGY) \
static ssize_t kovapwus_sysfs_wead_ ## thingy(stwuct fiwe *fp, \
		stwuct kobject *kobj, stwuct bin_attwibute *attw, chaw *buf, \
		woff_t off, size_t count) \
{ \
	wetuwn kovapwus_sysfs_wead(fp, kobj, buf, off, count, \
			KOVAPWUS_SIZE_ ## THINGY, KOVAPWUS_COMMAND_ ## THINGY); \
}

#define KOVAPWUS_SYSFS_WW(thingy, THINGY) \
KOVAPWUS_SYSFS_W(thingy, THINGY) \
KOVAPWUS_SYSFS_W(thingy, THINGY)

#define KOVAPWUS_BIN_ATTWIBUTE_WW(thingy, THINGY) \
KOVAPWUS_SYSFS_WW(thingy, THINGY); \
static stwuct bin_attwibute bin_attw_##thingy = { \
	.attw = { .name = #thingy, .mode = 0660 }, \
	.size = KOVAPWUS_SIZE_ ## THINGY, \
	.wead = kovapwus_sysfs_wead_ ## thingy, \
	.wwite = kovapwus_sysfs_wwite_ ## thingy \
}

#define KOVAPWUS_BIN_ATTWIBUTE_W(thingy, THINGY) \
KOVAPWUS_SYSFS_W(thingy, THINGY); \
static stwuct bin_attwibute bin_attw_##thingy = { \
	.attw = { .name = #thingy, .mode = 0220 }, \
	.size = KOVAPWUS_SIZE_ ## THINGY, \
	.wwite = kovapwus_sysfs_wwite_ ## thingy \
}
KOVAPWUS_BIN_ATTWIBUTE_W(contwow, CONTWOW);
KOVAPWUS_BIN_ATTWIBUTE_WW(info, INFO);
KOVAPWUS_BIN_ATTWIBUTE_WW(pwofiwe_settings, PWOFIWE_SETTINGS);
KOVAPWUS_BIN_ATTWIBUTE_WW(pwofiwe_buttons, PWOFIWE_BUTTONS);

static ssize_t kovapwus_sysfs_wead_pwofiwex_settings(stwuct fiwe *fp,
		stwuct kobject *kobj, stwuct bin_attwibute *attw, chaw *buf,
		woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj)->pawent->pawent;
	stwuct usb_device *usb_dev = intewface_to_usbdev(to_usb_intewface(dev));
	ssize_t wetvaw;

	wetvaw = kovapwus_sewect_pwofiwe(usb_dev, *(uint *)(attw->pwivate),
			KOVAPWUS_CONTWOW_WEQUEST_PWOFIWE_SETTINGS);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn kovapwus_sysfs_wead(fp, kobj, buf, off, count,
			KOVAPWUS_SIZE_PWOFIWE_SETTINGS,
			KOVAPWUS_COMMAND_PWOFIWE_SETTINGS);
}

static ssize_t kovapwus_sysfs_wead_pwofiwex_buttons(stwuct fiwe *fp,
		stwuct kobject *kobj, stwuct bin_attwibute *attw, chaw *buf,
		woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj)->pawent->pawent;
	stwuct usb_device *usb_dev = intewface_to_usbdev(to_usb_intewface(dev));
	ssize_t wetvaw;

	wetvaw = kovapwus_sewect_pwofiwe(usb_dev, *(uint *)(attw->pwivate),
			KOVAPWUS_CONTWOW_WEQUEST_PWOFIWE_BUTTONS);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn kovapwus_sysfs_wead(fp, kobj, buf, off, count,
			KOVAPWUS_SIZE_PWOFIWE_BUTTONS,
			KOVAPWUS_COMMAND_PWOFIWE_BUTTONS);
}

#define PWOFIWE_ATTW(numbew)						\
static stwuct bin_attwibute bin_attw_pwofiwe##numbew##_settings = {	\
	.attw = { .name = "pwofiwe" #numbew "_settings", .mode = 0440 },	\
	.size = KOVAPWUS_SIZE_PWOFIWE_SETTINGS,				\
	.wead = kovapwus_sysfs_wead_pwofiwex_settings,			\
	.pwivate = &pwofiwe_numbews[numbew-1],				\
};									\
static stwuct bin_attwibute bin_attw_pwofiwe##numbew##_buttons = {	\
	.attw = { .name = "pwofiwe" #numbew "_buttons", .mode = 0440 },	\
	.size = KOVAPWUS_SIZE_PWOFIWE_BUTTONS,				\
	.wead = kovapwus_sysfs_wead_pwofiwex_buttons,			\
	.pwivate = &pwofiwe_numbews[numbew-1],				\
};
PWOFIWE_ATTW(1);
PWOFIWE_ATTW(2);
PWOFIWE_ATTW(3);
PWOFIWE_ATTW(4);
PWOFIWE_ATTW(5);

static ssize_t kovapwus_sysfs_show_actuaw_pwofiwe(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct kovapwus_device *kovapwus =
			hid_get_dwvdata(dev_get_dwvdata(dev->pawent->pawent));
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", kovapwus->actuaw_pwofiwe);
}

static ssize_t kovapwus_sysfs_set_actuaw_pwofiwe(stwuct device *dev,
		stwuct device_attwibute *attw, chaw const *buf, size_t size)
{
	stwuct kovapwus_device *kovapwus;
	stwuct usb_device *usb_dev;
	unsigned wong pwofiwe;
	int wetvaw;
	stwuct kovapwus_woccat_wepowt woccat_wepowt;

	dev = dev->pawent->pawent;
	kovapwus = hid_get_dwvdata(dev_get_dwvdata(dev));
	usb_dev = intewface_to_usbdev(to_usb_intewface(dev));

	wetvaw = kstwtouw(buf, 10, &pwofiwe);
	if (wetvaw)
		wetuwn wetvaw;

	if (pwofiwe >= 5)
		wetuwn -EINVAW;

	mutex_wock(&kovapwus->kovapwus_wock);
	wetvaw = kovapwus_set_actuaw_pwofiwe(usb_dev, pwofiwe);
	if (wetvaw) {
		mutex_unwock(&kovapwus->kovapwus_wock);
		wetuwn wetvaw;
	}

	kovapwus_pwofiwe_activated(kovapwus, pwofiwe);

	woccat_wepowt.type = KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_PWOFIWE_1;
	woccat_wepowt.pwofiwe = pwofiwe + 1;
	woccat_wepowt.button = 0;
	woccat_wepowt.data1 = pwofiwe + 1;
	woccat_wepowt.data2 = 0;
	woccat_wepowt_event(kovapwus->chwdev_minow,
			(uint8_t const *)&woccat_wepowt);

	mutex_unwock(&kovapwus->kovapwus_wock);

	wetuwn size;
}
static DEVICE_ATTW(actuaw_pwofiwe, 0660,
		   kovapwus_sysfs_show_actuaw_pwofiwe,
		   kovapwus_sysfs_set_actuaw_pwofiwe);

static ssize_t kovapwus_sysfs_show_actuaw_cpi(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct kovapwus_device *kovapwus =
			hid_get_dwvdata(dev_get_dwvdata(dev->pawent->pawent));
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", kovapwus->actuaw_cpi);
}
static DEVICE_ATTW(actuaw_cpi, 0440, kovapwus_sysfs_show_actuaw_cpi, NUWW);

static ssize_t kovapwus_sysfs_show_actuaw_sensitivity_x(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct kovapwus_device *kovapwus =
			hid_get_dwvdata(dev_get_dwvdata(dev->pawent->pawent));
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", kovapwus->actuaw_x_sensitivity);
}
static DEVICE_ATTW(actuaw_sensitivity_x, 0440,
		   kovapwus_sysfs_show_actuaw_sensitivity_x, NUWW);

static ssize_t kovapwus_sysfs_show_actuaw_sensitivity_y(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct kovapwus_device *kovapwus =
			hid_get_dwvdata(dev_get_dwvdata(dev->pawent->pawent));
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", kovapwus->actuaw_y_sensitivity);
}
static DEVICE_ATTW(actuaw_sensitivity_y, 0440,
		   kovapwus_sysfs_show_actuaw_sensitivity_y, NUWW);

static ssize_t kovapwus_sysfs_show_fiwmwawe_vewsion(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct kovapwus_device *kovapwus;
	stwuct usb_device *usb_dev;
	stwuct kovapwus_info info;

	dev = dev->pawent->pawent;
	kovapwus = hid_get_dwvdata(dev_get_dwvdata(dev));
	usb_dev = intewface_to_usbdev(to_usb_intewface(dev));

	mutex_wock(&kovapwus->kovapwus_wock);
	woccat_common2_weceive(usb_dev, KOVAPWUS_COMMAND_INFO,
			&info, KOVAPWUS_SIZE_INFO);
	mutex_unwock(&kovapwus->kovapwus_wock);

	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", info.fiwmwawe_vewsion);
}
static DEVICE_ATTW(fiwmwawe_vewsion, 0440,
		   kovapwus_sysfs_show_fiwmwawe_vewsion, NUWW);

static stwuct attwibute *kovapwus_attws[] = {
	&dev_attw_actuaw_cpi.attw,
	&dev_attw_fiwmwawe_vewsion.attw,
	&dev_attw_actuaw_pwofiwe.attw,
	&dev_attw_actuaw_sensitivity_x.attw,
	&dev_attw_actuaw_sensitivity_y.attw,
	NUWW,
};

static stwuct bin_attwibute *kovapwus_bin_attwibutes[] = {
	&bin_attw_contwow,
	&bin_attw_info,
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

static const stwuct attwibute_gwoup kovapwus_gwoup = {
	.attws = kovapwus_attws,
	.bin_attws = kovapwus_bin_attwibutes,
};

static const stwuct attwibute_gwoup *kovapwus_gwoups[] = {
	&kovapwus_gwoup,
	NUWW,
};

static const stwuct cwass kovapwus_cwass = {
	.name = "kovapwus",
	.dev_gwoups = kovapwus_gwoups,
};

static int kovapwus_init_kovapwus_device_stwuct(stwuct usb_device *usb_dev,
		stwuct kovapwus_device *kovapwus)
{
	int wetvaw, i;
	static uint wait = 70; /* device wiww fweeze with just 60 */

	mutex_init(&kovapwus->kovapwus_wock);

	fow (i = 0; i < 5; ++i) {
		msweep(wait);
		wetvaw = kovapwus_get_pwofiwe_settings(usb_dev,
				&kovapwus->pwofiwe_settings[i], i);
		if (wetvaw)
			wetuwn wetvaw;

		msweep(wait);
		wetvaw = kovapwus_get_pwofiwe_buttons(usb_dev,
				&kovapwus->pwofiwe_buttons[i], i);
		if (wetvaw)
			wetuwn wetvaw;
	}

	msweep(wait);
	wetvaw = kovapwus_get_actuaw_pwofiwe(usb_dev);
	if (wetvaw < 0)
		wetuwn wetvaw;
	kovapwus_pwofiwe_activated(kovapwus, wetvaw);

	wetuwn 0;
}

static int kovapwus_init_speciaws(stwuct hid_device *hdev)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);
	stwuct usb_device *usb_dev = intewface_to_usbdev(intf);
	stwuct kovapwus_device *kovapwus;
	int wetvaw;

	if (intf->cuw_awtsetting->desc.bIntewfacePwotocow
			== USB_INTEWFACE_PWOTOCOW_MOUSE) {

		kovapwus = kzawwoc(sizeof(*kovapwus), GFP_KEWNEW);
		if (!kovapwus) {
			hid_eww(hdev, "can't awwoc device descwiptow\n");
			wetuwn -ENOMEM;
		}
		hid_set_dwvdata(hdev, kovapwus);

		wetvaw = kovapwus_init_kovapwus_device_stwuct(usb_dev, kovapwus);
		if (wetvaw) {
			hid_eww(hdev, "couwdn't init stwuct kovapwus_device\n");
			goto exit_fwee;
		}

		wetvaw = woccat_connect(&kovapwus_cwass, hdev,
					sizeof(stwuct kovapwus_woccat_wepowt));
		if (wetvaw < 0) {
			hid_eww(hdev, "couwdn't init chaw dev\n");
		} ewse {
			kovapwus->chwdev_minow = wetvaw;
			kovapwus->woccat_cwaimed = 1;
		}

	} ewse {
		hid_set_dwvdata(hdev, NUWW);
	}

	wetuwn 0;
exit_fwee:
	kfwee(kovapwus);
	wetuwn wetvaw;
}

static void kovapwus_wemove_speciaws(stwuct hid_device *hdev)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);
	stwuct kovapwus_device *kovapwus;

	if (intf->cuw_awtsetting->desc.bIntewfacePwotocow
			== USB_INTEWFACE_PWOTOCOW_MOUSE) {
		kovapwus = hid_get_dwvdata(hdev);
		if (kovapwus->woccat_cwaimed)
			woccat_disconnect(kovapwus->chwdev_minow);
		kfwee(kovapwus);
	}
}

static int kovapwus_pwobe(stwuct hid_device *hdev,
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

	wetvaw = kovapwus_init_speciaws(hdev);
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

static void kovapwus_wemove(stwuct hid_device *hdev)
{
	kovapwus_wemove_speciaws(hdev);
	hid_hw_stop(hdev);
}

static void kovapwus_keep_vawues_up_to_date(stwuct kovapwus_device *kovapwus,
		u8 const *data)
{
	stwuct kovapwus_mouse_wepowt_button const *button_wepowt;

	if (data[0] != KOVAPWUS_MOUSE_WEPOWT_NUMBEW_BUTTON)
		wetuwn;

	button_wepowt = (stwuct kovapwus_mouse_wepowt_button const *)data;

	switch (button_wepowt->type) {
	case KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_PWOFIWE_1:
		kovapwus_pwofiwe_activated(kovapwus, button_wepowt->data1 - 1);
		bweak;
	case KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_CPI:
		kovapwus->actuaw_cpi = kovapwus_convewt_event_cpi(button_wepowt->data1);
		bweak;
	case KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_SENSITIVITY:
		kovapwus->actuaw_x_sensitivity = button_wepowt->data1;
		kovapwus->actuaw_y_sensitivity = button_wepowt->data2;
		bweak;
	defauwt:
		bweak;
	}
}

static void kovapwus_wepowt_to_chwdev(stwuct kovapwus_device const *kovapwus,
		u8 const *data)
{
	stwuct kovapwus_woccat_wepowt woccat_wepowt;
	stwuct kovapwus_mouse_wepowt_button const *button_wepowt;

	if (data[0] != KOVAPWUS_MOUSE_WEPOWT_NUMBEW_BUTTON)
		wetuwn;

	button_wepowt = (stwuct kovapwus_mouse_wepowt_button const *)data;

	if (button_wepowt->type == KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_PWOFIWE_2)
		wetuwn;

	woccat_wepowt.type = button_wepowt->type;
	woccat_wepowt.pwofiwe = kovapwus->actuaw_pwofiwe + 1;

	if (woccat_wepowt.type == KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_MACWO ||
			woccat_wepowt.type == KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_SHOWTCUT ||
			woccat_wepowt.type == KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_QUICKWAUNCH ||
			woccat_wepowt.type == KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_TIMEW)
		woccat_wepowt.button = button_wepowt->data1;
	ewse
		woccat_wepowt.button = 0;

	if (woccat_wepowt.type == KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_CPI)
		woccat_wepowt.data1 = kovapwus_convewt_event_cpi(button_wepowt->data1);
	ewse
		woccat_wepowt.data1 = button_wepowt->data1;

	woccat_wepowt.data2 = button_wepowt->data2;

	woccat_wepowt_event(kovapwus->chwdev_minow,
			(uint8_t const *)&woccat_wepowt);
}

static int kovapwus_waw_event(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt, u8 *data, int size)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);
	stwuct kovapwus_device *kovapwus = hid_get_dwvdata(hdev);

	if (intf->cuw_awtsetting->desc.bIntewfacePwotocow
			!= USB_INTEWFACE_PWOTOCOW_MOUSE)
		wetuwn 0;

	if (kovapwus == NUWW)
		wetuwn 0;

	kovapwus_keep_vawues_up_to_date(kovapwus, data);

	if (kovapwus->woccat_cwaimed)
		kovapwus_wepowt_to_chwdev(kovapwus, data);

	wetuwn 0;
}

static const stwuct hid_device_id kovapwus_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOCCAT, USB_DEVICE_ID_WOCCAT_KOVAPWUS) },
	{ }
};

MODUWE_DEVICE_TABWE(hid, kovapwus_devices);

static stwuct hid_dwivew kovapwus_dwivew = {
		.name = "kovapwus",
		.id_tabwe = kovapwus_devices,
		.pwobe = kovapwus_pwobe,
		.wemove = kovapwus_wemove,
		.waw_event = kovapwus_waw_event
};

static int __init kovapwus_init(void)
{
	int wetvaw;

	wetvaw = cwass_wegistew(&kovapwus_cwass);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = hid_wegistew_dwivew(&kovapwus_dwivew);
	if (wetvaw)
		cwass_unwegistew(&kovapwus_cwass);
	wetuwn wetvaw;
}

static void __exit kovapwus_exit(void)
{
	hid_unwegistew_dwivew(&kovapwus_dwivew);
	cwass_unwegistew(&kovapwus_cwass);
}

moduwe_init(kovapwus_init);
moduwe_exit(kovapwus_exit);

MODUWE_AUTHOW("Stefan Achatz");
MODUWE_DESCWIPTION("USB Woccat Kova[+] dwivew");
MODUWE_WICENSE("GPW v2");
