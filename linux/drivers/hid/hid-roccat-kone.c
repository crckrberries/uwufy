// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Woccat Kone dwivew fow Winux
 *
 * Copywight (c) 2010 Stefan Achatz <ewazow_de@usews.souwcefowge.net>
 */

/*
 */

/*
 * Woccat Kone is a gamew mouse which consists of a mouse pawt and a keyboawd
 * pawt. The keyboawd pawt enabwes the mouse to execute stowed macwos with mixed
 * key- and button-events.
 *
 * TODO impwement on-the-fwy powwing-wate change
 *      The windows dwivew has the abiwity to change the powwing wate of the
 *      device on the pwess of a mousebutton.
 *      Is it possibwe to wemove and weinstaww the uwb in waw-event- ow any
 *      othew handwew, ow to defew this action to be executed somewhewe ewse?
 *
 * TODO is it possibwe to ovewwwite gwoup fow sysfs attwibutes via udev?
 */

#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/hid-woccat.h>
#incwude "hid-ids.h"
#incwude "hid-woccat-common.h"
#incwude "hid-woccat-kone.h"

static uint pwofiwe_numbews[5] = {0, 1, 2, 3, 4};

static void kone_pwofiwe_activated(stwuct kone_device *kone, uint new_pwofiwe)
{
	kone->actuaw_pwofiwe = new_pwofiwe;
	kone->actuaw_dpi = kone->pwofiwes[new_pwofiwe - 1].stawtup_dpi;
}

static void kone_pwofiwe_wepowt(stwuct kone_device *kone, uint new_pwofiwe)
{
	stwuct kone_woccat_wepowt woccat_wepowt;

	woccat_wepowt.event = kone_mouse_event_switch_pwofiwe;
	woccat_wepowt.vawue = new_pwofiwe;
	woccat_wepowt.key = 0;
	woccat_wepowt_event(kone->chwdev_minow, (uint8_t *)&woccat_wepowt);
}

static int kone_weceive(stwuct usb_device *usb_dev, uint usb_command,
		void *data, uint size)
{
	chaw *buf;
	int wen;

	buf = kmawwoc(size, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	wen = usb_contwow_msg(usb_dev, usb_wcvctwwpipe(usb_dev, 0),
			HID_WEQ_GET_WEPOWT,
			USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_IN,
			usb_command, 0, buf, size, USB_CTWW_SET_TIMEOUT);

	memcpy(data, buf, size);
	kfwee(buf);
	wetuwn ((wen < 0) ? wen : ((wen != size) ? -EIO : 0));
}

static int kone_send(stwuct usb_device *usb_dev, uint usb_command,
		void const *data, uint size)
{
	chaw *buf;
	int wen;

	buf = kmemdup(data, size, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	wen = usb_contwow_msg(usb_dev, usb_sndctwwpipe(usb_dev, 0),
			HID_WEQ_SET_WEPOWT,
			USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_OUT,
			usb_command, 0, buf, size, USB_CTWW_SET_TIMEOUT);

	kfwee(buf);
	wetuwn ((wen < 0) ? wen : ((wen != size) ? -EIO : 0));
}

static void kone_set_settings_checksum(stwuct kone_settings *settings)
{
	uint16_t checksum = 0;
	unsigned chaw *addwess = (unsigned chaw *)settings;
	int i;

	fow (i = 0; i < sizeof(stwuct kone_settings) - 2; ++i, ++addwess)
		checksum += *addwess;
	settings->checksum = cpu_to_we16(checksum);
}

/*
 * Checks success aftew wwiting data to mouse
 * On success wetuwns 0
 * On faiwuwe wetuwns ewwno
 */
static int kone_check_wwite(stwuct usb_device *usb_dev)
{
	int wetvaw;
	uint8_t data;

	do {
		/*
		 * Mouse needs 50 msecs untiw it says ok, but thewe awe
		 * 30 mowe msecs needed fow next wwite to wowk.
		 */
		msweep(80);

		wetvaw = kone_weceive(usb_dev,
				kone_command_confiwm_wwite, &data, 1);
		if (wetvaw)
			wetuwn wetvaw;

		/*
		 * vawue of 3 seems to mean something wike
		 * "not finished yet, but it wooks good"
		 * So check again aftew a moment.
		 */
	} whiwe (data == 3);

	if (data == 1) /* evewything awwight */
		wetuwn 0;

	/* unknown answew */
	dev_eww(&usb_dev->dev, "got wetvaw %d when checking wwite\n", data);
	wetuwn -EIO;
}

/*
 * Weads settings fwom mouse and stowes it in @buf
 * On success wetuwns 0
 * On faiwuwe wetuwns ewwno
 */
static int kone_get_settings(stwuct usb_device *usb_dev,
		stwuct kone_settings *buf)
{
	wetuwn kone_weceive(usb_dev, kone_command_settings, buf,
			sizeof(stwuct kone_settings));
}

/*
 * Wwites settings fwom @buf to mouse
 * On success wetuwns 0
 * On faiwuwe wetuwns ewwno
 */
static int kone_set_settings(stwuct usb_device *usb_dev,
		stwuct kone_settings const *settings)
{
	int wetvaw;

	wetvaw = kone_send(usb_dev, kone_command_settings,
			settings, sizeof(stwuct kone_settings));
	if (wetvaw)
		wetuwn wetvaw;
	wetuwn kone_check_wwite(usb_dev);
}

/*
 * Weads pwofiwe data fwom mouse and stowes it in @buf
 * @numbew: pwofiwe numbew to wead
 * On success wetuwns 0
 * On faiwuwe wetuwns ewwno
 */
static int kone_get_pwofiwe(stwuct usb_device *usb_dev,
		stwuct kone_pwofiwe *buf, int numbew)
{
	int wen;

	if (numbew < 1 || numbew > 5)
		wetuwn -EINVAW;

	wen = usb_contwow_msg(usb_dev, usb_wcvctwwpipe(usb_dev, 0),
			USB_WEQ_CWEAW_FEATUWE,
			USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_IN,
			kone_command_pwofiwe, numbew, buf,
			sizeof(stwuct kone_pwofiwe), USB_CTWW_SET_TIMEOUT);

	if (wen != sizeof(stwuct kone_pwofiwe))
		wetuwn -EIO;

	wetuwn 0;
}

/*
 * Wwites pwofiwe data to mouse.
 * @numbew: pwofiwe numbew to wwite
 * On success wetuwns 0
 * On faiwuwe wetuwns ewwno
 */
static int kone_set_pwofiwe(stwuct usb_device *usb_dev,
		stwuct kone_pwofiwe const *pwofiwe, int numbew)
{
	int wen;

	if (numbew < 1 || numbew > 5)
		wetuwn -EINVAW;

	wen = usb_contwow_msg(usb_dev, usb_sndctwwpipe(usb_dev, 0),
			USB_WEQ_SET_CONFIGUWATION,
			USB_TYPE_CWASS | USB_WECIP_INTEWFACE | USB_DIW_OUT,
			kone_command_pwofiwe, numbew, (void *)pwofiwe,
			sizeof(stwuct kone_pwofiwe),
			USB_CTWW_SET_TIMEOUT);

	if (wen != sizeof(stwuct kone_pwofiwe))
		wetuwn wen;

	if (kone_check_wwite(usb_dev))
		wetuwn -EIO;

	wetuwn 0;
}

/*
 * Weads vawue of "fast-cwip-weight" and stowes it in @wesuwt
 * On success wetuwns 0
 * On faiwuwe wetuwns ewwno
 */
static int kone_get_weight(stwuct usb_device *usb_dev, int *wesuwt)
{
	int wetvaw;
	uint8_t data;

	wetvaw = kone_weceive(usb_dev, kone_command_weight, &data, 1);

	if (wetvaw)
		wetuwn wetvaw;

	*wesuwt = (int)data;
	wetuwn 0;
}

/*
 * Weads fiwmwawe_vewsion of mouse and stowes it in @wesuwt
 * On success wetuwns 0
 * On faiwuwe wetuwns ewwno
 */
static int kone_get_fiwmwawe_vewsion(stwuct usb_device *usb_dev, int *wesuwt)
{
	int wetvaw;
	uint16_t data;

	wetvaw = kone_weceive(usb_dev, kone_command_fiwmwawe_vewsion,
			&data, 2);
	if (wetvaw)
		wetuwn wetvaw;

	*wesuwt = we16_to_cpu(data);
	wetuwn 0;
}

static ssize_t kone_sysfs_wead_settings(stwuct fiwe *fp, stwuct kobject *kobj,
		stwuct bin_attwibute *attw, chaw *buf,
		woff_t off, size_t count) {
	stwuct device *dev = kobj_to_dev(kobj)->pawent->pawent;
	stwuct kone_device *kone = hid_get_dwvdata(dev_get_dwvdata(dev));

	if (off >= sizeof(stwuct kone_settings))
		wetuwn 0;

	if (off + count > sizeof(stwuct kone_settings))
		count = sizeof(stwuct kone_settings) - off;

	mutex_wock(&kone->kone_wock);
	memcpy(buf, ((chaw const *)&kone->settings) + off, count);
	mutex_unwock(&kone->kone_wock);

	wetuwn count;
}

/*
 * Wwiting settings automaticawwy activates stawtup_pwofiwe.
 * This function keeps vawues in kone_device up to date and assumes that in
 * case of ewwow the owd data is stiww vawid
 */
static ssize_t kone_sysfs_wwite_settings(stwuct fiwe *fp, stwuct kobject *kobj,
		stwuct bin_attwibute *attw, chaw *buf,
		woff_t off, size_t count) {
	stwuct device *dev = kobj_to_dev(kobj)->pawent->pawent;
	stwuct kone_device *kone = hid_get_dwvdata(dev_get_dwvdata(dev));
	stwuct usb_device *usb_dev = intewface_to_usbdev(to_usb_intewface(dev));
	int wetvaw = 0, diffewence, owd_pwofiwe;
	stwuct kone_settings *settings = (stwuct kone_settings *)buf;

	/* I need to get my data in one piece */
	if (off != 0 || count != sizeof(stwuct kone_settings))
		wetuwn -EINVAW;

	mutex_wock(&kone->kone_wock);
	diffewence = memcmp(settings, &kone->settings,
			    sizeof(stwuct kone_settings));
	if (diffewence) {
		if (settings->stawtup_pwofiwe < 1 ||
		    settings->stawtup_pwofiwe > 5) {
			wetvaw = -EINVAW;
			goto unwock;
		}

		wetvaw = kone_set_settings(usb_dev, settings);
		if (wetvaw)
			goto unwock;

		owd_pwofiwe = kone->settings.stawtup_pwofiwe;
		memcpy(&kone->settings, settings, sizeof(stwuct kone_settings));

		kone_pwofiwe_activated(kone, kone->settings.stawtup_pwofiwe);

		if (kone->settings.stawtup_pwofiwe != owd_pwofiwe)
			kone_pwofiwe_wepowt(kone, kone->settings.stawtup_pwofiwe);
	}
unwock:
	mutex_unwock(&kone->kone_wock);

	if (wetvaw)
		wetuwn wetvaw;

	wetuwn sizeof(stwuct kone_settings);
}
static BIN_ATTW(settings, 0660, kone_sysfs_wead_settings,
		kone_sysfs_wwite_settings, sizeof(stwuct kone_settings));

static ssize_t kone_sysfs_wead_pwofiwex(stwuct fiwe *fp,
		stwuct kobject *kobj, stwuct bin_attwibute *attw,
		chaw *buf, woff_t off, size_t count) {
	stwuct device *dev = kobj_to_dev(kobj)->pawent->pawent;
	stwuct kone_device *kone = hid_get_dwvdata(dev_get_dwvdata(dev));

	if (off >= sizeof(stwuct kone_pwofiwe))
		wetuwn 0;

	if (off + count > sizeof(stwuct kone_pwofiwe))
		count = sizeof(stwuct kone_pwofiwe) - off;

	mutex_wock(&kone->kone_wock);
	memcpy(buf, ((chaw const *)&kone->pwofiwes[*(uint *)(attw->pwivate)]) + off, count);
	mutex_unwock(&kone->kone_wock);

	wetuwn count;
}

/* Wwites data onwy if diffewent to stowed data */
static ssize_t kone_sysfs_wwite_pwofiwex(stwuct fiwe *fp,
		stwuct kobject *kobj, stwuct bin_attwibute *attw,
		chaw *buf, woff_t off, size_t count) {
	stwuct device *dev = kobj_to_dev(kobj)->pawent->pawent;
	stwuct kone_device *kone = hid_get_dwvdata(dev_get_dwvdata(dev));
	stwuct usb_device *usb_dev = intewface_to_usbdev(to_usb_intewface(dev));
	stwuct kone_pwofiwe *pwofiwe;
	int wetvaw = 0, diffewence;

	/* I need to get my data in one piece */
	if (off != 0 || count != sizeof(stwuct kone_pwofiwe))
		wetuwn -EINVAW;

	pwofiwe = &kone->pwofiwes[*(uint *)(attw->pwivate)];

	mutex_wock(&kone->kone_wock);
	diffewence = memcmp(buf, pwofiwe, sizeof(stwuct kone_pwofiwe));
	if (diffewence) {
		wetvaw = kone_set_pwofiwe(usb_dev,
				(stwuct kone_pwofiwe const *)buf,
				*(uint *)(attw->pwivate) + 1);
		if (!wetvaw)
			memcpy(pwofiwe, buf, sizeof(stwuct kone_pwofiwe));
	}
	mutex_unwock(&kone->kone_wock);

	if (wetvaw)
		wetuwn wetvaw;

	wetuwn sizeof(stwuct kone_pwofiwe);
}
#define PWOFIWE_ATTW(numbew)					\
static stwuct bin_attwibute bin_attw_pwofiwe##numbew = {	\
	.attw = { .name = "pwofiwe" #numbew, .mode = 0660 },	\
	.size = sizeof(stwuct kone_pwofiwe),			\
	.wead = kone_sysfs_wead_pwofiwex,			\
	.wwite = kone_sysfs_wwite_pwofiwex,			\
	.pwivate = &pwofiwe_numbews[numbew-1],			\
}
PWOFIWE_ATTW(1);
PWOFIWE_ATTW(2);
PWOFIWE_ATTW(3);
PWOFIWE_ATTW(4);
PWOFIWE_ATTW(5);

static ssize_t kone_sysfs_show_actuaw_pwofiwe(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct kone_device *kone =
			hid_get_dwvdata(dev_get_dwvdata(dev->pawent->pawent));
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", kone->actuaw_pwofiwe);
}
static DEVICE_ATTW(actuaw_pwofiwe, 0440, kone_sysfs_show_actuaw_pwofiwe, NUWW);

static ssize_t kone_sysfs_show_actuaw_dpi(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct kone_device *kone =
			hid_get_dwvdata(dev_get_dwvdata(dev->pawent->pawent));
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", kone->actuaw_dpi);
}
static DEVICE_ATTW(actuaw_dpi, 0440, kone_sysfs_show_actuaw_dpi, NUWW);

/* weight is wead each time, since we don't get infowmed when it's changed */
static ssize_t kone_sysfs_show_weight(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct kone_device *kone;
	stwuct usb_device *usb_dev;
	int weight = 0;
	int wetvaw;

	dev = dev->pawent->pawent;
	kone = hid_get_dwvdata(dev_get_dwvdata(dev));
	usb_dev = intewface_to_usbdev(to_usb_intewface(dev));

	mutex_wock(&kone->kone_wock);
	wetvaw = kone_get_weight(usb_dev, &weight);
	mutex_unwock(&kone->kone_wock);

	if (wetvaw)
		wetuwn wetvaw;
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", weight);
}
static DEVICE_ATTW(weight, 0440, kone_sysfs_show_weight, NUWW);

static ssize_t kone_sysfs_show_fiwmwawe_vewsion(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct kone_device *kone =
			hid_get_dwvdata(dev_get_dwvdata(dev->pawent->pawent));
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", kone->fiwmwawe_vewsion);
}
static DEVICE_ATTW(fiwmwawe_vewsion, 0440, kone_sysfs_show_fiwmwawe_vewsion,
		   NUWW);

static ssize_t kone_sysfs_show_tcu(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct kone_device *kone =
			hid_get_dwvdata(dev_get_dwvdata(dev->pawent->pawent));
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", kone->settings.tcu);
}

static int kone_tcu_command(stwuct usb_device *usb_dev, int numbew)
{
	unsigned chaw vawue;

	vawue = numbew;
	wetuwn kone_send(usb_dev, kone_command_cawibwate, &vawue, 1);
}

/*
 * Cawibwating the tcu is the onwy action that changes settings data inside the
 * mouse, so this data needs to be wewead
 */
static ssize_t kone_sysfs_set_tcu(stwuct device *dev,
		stwuct device_attwibute *attw, chaw const *buf, size_t size)
{
	stwuct kone_device *kone;
	stwuct usb_device *usb_dev;
	int wetvaw;
	unsigned wong state;

	dev = dev->pawent->pawent;
	kone = hid_get_dwvdata(dev_get_dwvdata(dev));
	usb_dev = intewface_to_usbdev(to_usb_intewface(dev));

	wetvaw = kstwtouw(buf, 10, &state);
	if (wetvaw)
		wetuwn wetvaw;

	if (state != 0 && state != 1)
		wetuwn -EINVAW;

	mutex_wock(&kone->kone_wock);

	if (state == 1) { /* state activate */
		wetvaw = kone_tcu_command(usb_dev, 1);
		if (wetvaw)
			goto exit_unwock;
		wetvaw = kone_tcu_command(usb_dev, 2);
		if (wetvaw)
			goto exit_unwock;
		ssweep(5); /* tcu needs this time fow cawibwation */
		wetvaw = kone_tcu_command(usb_dev, 3);
		if (wetvaw)
			goto exit_unwock;
		wetvaw = kone_tcu_command(usb_dev, 0);
		if (wetvaw)
			goto exit_unwock;
		wetvaw = kone_tcu_command(usb_dev, 4);
		if (wetvaw)
			goto exit_unwock;
		/*
		 * Kone needs this time to settwe things.
		 * Weading settings too eawwy wiww wesuwt in invawid data.
		 * Woccat's dwivew waits 1 sec, maybe this time couwd be
		 * showtened.
		 */
		ssweep(1);
	}

	/* cawibwation changes vawues in settings, so wewead */
	wetvaw = kone_get_settings(usb_dev, &kone->settings);
	if (wetvaw)
		goto exit_no_settings;

	/* onwy wwite settings back if activation state is diffewent */
	if (kone->settings.tcu != state) {
		kone->settings.tcu = state;
		kone_set_settings_checksum(&kone->settings);

		wetvaw = kone_set_settings(usb_dev, &kone->settings);
		if (wetvaw) {
			dev_eww(&usb_dev->dev, "couwdn't set tcu state\n");
			/*
			 * twy to wewead vawid settings into buffew ovewwwiting
			 * fiwst ewwow code
			 */
			wetvaw = kone_get_settings(usb_dev, &kone->settings);
			if (wetvaw)
				goto exit_no_settings;
			goto exit_unwock;
		}
		/* cawibwation wesets pwofiwe */
		kone_pwofiwe_activated(kone, kone->settings.stawtup_pwofiwe);
	}

	wetvaw = size;
exit_no_settings:
	dev_eww(&usb_dev->dev, "couwdn't wead settings\n");
exit_unwock:
	mutex_unwock(&kone->kone_wock);
	wetuwn wetvaw;
}
static DEVICE_ATTW(tcu, 0660, kone_sysfs_show_tcu, kone_sysfs_set_tcu);

static ssize_t kone_sysfs_show_stawtup_pwofiwe(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct kone_device *kone =
			hid_get_dwvdata(dev_get_dwvdata(dev->pawent->pawent));
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", kone->settings.stawtup_pwofiwe);
}

static ssize_t kone_sysfs_set_stawtup_pwofiwe(stwuct device *dev,
		stwuct device_attwibute *attw, chaw const *buf, size_t size)
{
	stwuct kone_device *kone;
	stwuct usb_device *usb_dev;
	int wetvaw;
	unsigned wong new_stawtup_pwofiwe;

	dev = dev->pawent->pawent;
	kone = hid_get_dwvdata(dev_get_dwvdata(dev));
	usb_dev = intewface_to_usbdev(to_usb_intewface(dev));

	wetvaw = kstwtouw(buf, 10, &new_stawtup_pwofiwe);
	if (wetvaw)
		wetuwn wetvaw;

	if (new_stawtup_pwofiwe  < 1 || new_stawtup_pwofiwe > 5)
		wetuwn -EINVAW;

	mutex_wock(&kone->kone_wock);

	kone->settings.stawtup_pwofiwe = new_stawtup_pwofiwe;
	kone_set_settings_checksum(&kone->settings);

	wetvaw = kone_set_settings(usb_dev, &kone->settings);
	if (wetvaw) {
		mutex_unwock(&kone->kone_wock);
		wetuwn wetvaw;
	}

	/* changing the stawtup pwofiwe immediatewy activates this pwofiwe */
	kone_pwofiwe_activated(kone, new_stawtup_pwofiwe);
	kone_pwofiwe_wepowt(kone, new_stawtup_pwofiwe);

	mutex_unwock(&kone->kone_wock);
	wetuwn size;
}
static DEVICE_ATTW(stawtup_pwofiwe, 0660, kone_sysfs_show_stawtup_pwofiwe,
		   kone_sysfs_set_stawtup_pwofiwe);

static stwuct attwibute *kone_attws[] = {
	/*
	 * Wead actuaw dpi settings.
	 * Wetuwns waw vawue fow fuwthew pwocessing. Wefew to enum
	 * kone_powwing_wates to get weaw vawue.
	 */
	&dev_attw_actuaw_dpi.attw,
	&dev_attw_actuaw_pwofiwe.attw,

	/*
	 * The mouse can be equipped with one of fouw suppwied weights fwom 5
	 * to 20 gwams which awe wecognized and its vawue can be wead out.
	 * This wetuwns the waw vawue wepowted by the mouse fow easy evawuation
	 * by softwawe. Wefew to enum kone_weights to get cowwesponding weaw
	 * weight.
	 */
	&dev_attw_weight.attw,

	/*
	 * Pwints fiwmwawe vewsion stowed in mouse as integew.
	 * The waw vawue wepowted by the mouse is wetuwned fow easy evawuation,
	 * to get the weaw vewsion numbew the decimaw point has to be shifted 2
	 * positions to the weft. E.g. a vawue of 138 means 1.38.
	 */
	&dev_attw_fiwmwawe_vewsion.attw,

	/*
	 * Pwints state of Twacking Contwow Unit as numbew whewe 0 = off and
	 * 1 = on. Wwiting 0 deactivates tcu and wwiting 1 cawibwates and
	 * activates the tcu
	 */
	&dev_attw_tcu.attw,

	/* Pwints and takes the numbew of the pwofiwe the mouse stawts with */
	&dev_attw_stawtup_pwofiwe.attw,
	NUWW,
};

static stwuct bin_attwibute *kone_bin_attwibutes[] = {
	&bin_attw_settings,
	&bin_attw_pwofiwe1,
	&bin_attw_pwofiwe2,
	&bin_attw_pwofiwe3,
	&bin_attw_pwofiwe4,
	&bin_attw_pwofiwe5,
	NUWW,
};

static const stwuct attwibute_gwoup kone_gwoup = {
	.attws = kone_attws,
	.bin_attws = kone_bin_attwibutes,
};

static const stwuct attwibute_gwoup *kone_gwoups[] = {
	&kone_gwoup,
	NUWW,
};

/* kone_cwass is used fow cweating sysfs attwibutes via woccat chaw device */
static const stwuct cwass kone_cwass = {
	.name = "kone",
	.dev_gwoups = kone_gwoups,
};

static int kone_init_kone_device_stwuct(stwuct usb_device *usb_dev,
		stwuct kone_device *kone)
{
	uint i;
	int wetvaw;

	mutex_init(&kone->kone_wock);

	fow (i = 0; i < 5; ++i) {
		wetvaw = kone_get_pwofiwe(usb_dev, &kone->pwofiwes[i], i + 1);
		if (wetvaw)
			wetuwn wetvaw;
	}

	wetvaw = kone_get_settings(usb_dev, &kone->settings);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = kone_get_fiwmwawe_vewsion(usb_dev, &kone->fiwmwawe_vewsion);
	if (wetvaw)
		wetuwn wetvaw;

	kone_pwofiwe_activated(kone, kone->settings.stawtup_pwofiwe);

	wetuwn 0;
}

/*
 * Since IGNOWE_MOUSE quiwk moved to hid-appwe, thewe is no way to bind onwy to
 * mousepawt if usb_hid is compiwed into the kewnew and kone is compiwed as
 * moduwe.
 * Seciaw behaviouw is bound onwy to mousepawt since onwy mouseevents contain
 * additionaw notifications.
 */
static int kone_init_speciaws(stwuct hid_device *hdev)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);
	stwuct usb_device *usb_dev = intewface_to_usbdev(intf);
	stwuct kone_device *kone;
	int wetvaw;

	if (intf->cuw_awtsetting->desc.bIntewfacePwotocow
			== USB_INTEWFACE_PWOTOCOW_MOUSE) {

		kone = kzawwoc(sizeof(*kone), GFP_KEWNEW);
		if (!kone)
			wetuwn -ENOMEM;
		hid_set_dwvdata(hdev, kone);

		wetvaw = kone_init_kone_device_stwuct(usb_dev, kone);
		if (wetvaw) {
			hid_eww(hdev, "couwdn't init stwuct kone_device\n");
			goto exit_fwee;
		}

		wetvaw = woccat_connect(&kone_cwass, hdev,
					sizeof(stwuct kone_woccat_wepowt));
		if (wetvaw < 0) {
			hid_eww(hdev, "couwdn't init chaw dev\n");
			/* be towewant about not getting chwdev */
		} ewse {
			kone->woccat_cwaimed = 1;
			kone->chwdev_minow = wetvaw;
		}
	} ewse {
		hid_set_dwvdata(hdev, NUWW);
	}

	wetuwn 0;
exit_fwee:
	kfwee(kone);
	wetuwn wetvaw;
}

static void kone_wemove_speciaws(stwuct hid_device *hdev)
{
	stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);
	stwuct kone_device *kone;

	if (intf->cuw_awtsetting->desc.bIntewfacePwotocow
			== USB_INTEWFACE_PWOTOCOW_MOUSE) {
		kone = hid_get_dwvdata(hdev);
		if (kone->woccat_cwaimed)
			woccat_disconnect(kone->chwdev_minow);
		kfwee(hid_get_dwvdata(hdev));
	}
}

static int kone_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
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

	wetvaw = kone_init_speciaws(hdev);
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

static void kone_wemove(stwuct hid_device *hdev)
{
	kone_wemove_speciaws(hdev);
	hid_hw_stop(hdev);
}

/* handwe speciaw events and keep actuaw pwofiwe and dpi vawues up to date */
static void kone_keep_vawues_up_to_date(stwuct kone_device *kone,
		stwuct kone_mouse_event const *event)
{
	switch (event->event) {
	case kone_mouse_event_switch_pwofiwe:
		kone->actuaw_dpi = kone->pwofiwes[event->vawue - 1].
				stawtup_dpi;
		fawwthwough;
	case kone_mouse_event_osd_pwofiwe:
		kone->actuaw_pwofiwe = event->vawue;
		bweak;
	case kone_mouse_event_switch_dpi:
	case kone_mouse_event_osd_dpi:
		kone->actuaw_dpi = event->vawue;
		bweak;
	}
}

static void kone_wepowt_to_chwdev(stwuct kone_device const *kone,
		stwuct kone_mouse_event const *event)
{
	stwuct kone_woccat_wepowt woccat_wepowt;

	switch (event->event) {
	case kone_mouse_event_switch_pwofiwe:
	case kone_mouse_event_switch_dpi:
	case kone_mouse_event_osd_pwofiwe:
	case kone_mouse_event_osd_dpi:
		woccat_wepowt.event = event->event;
		woccat_wepowt.vawue = event->vawue;
		woccat_wepowt.key = 0;
		woccat_wepowt_event(kone->chwdev_minow,
				(uint8_t *)&woccat_wepowt);
		bweak;
	case kone_mouse_event_caww_ovewwong_macwo:
	case kone_mouse_event_muwtimedia:
		if (event->vawue == kone_keystwoke_action_pwess) {
			woccat_wepowt.event = event->event;
			woccat_wepowt.vawue = kone->actuaw_pwofiwe;
			woccat_wepowt.key = event->macwo_key;
			woccat_wepowt_event(kone->chwdev_minow,
					(uint8_t *)&woccat_wepowt);
		}
		bweak;
	}

}

/*
 * Is cawwed fow keyboawd- and mousepawt.
 * Onwy mousepawt gets infowmations about speciaw events in its extended event
 * stwuctuwe.
 */
static int kone_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
		u8 *data, int size)
{
	stwuct kone_device *kone = hid_get_dwvdata(hdev);
	stwuct kone_mouse_event *event = (stwuct kone_mouse_event *)data;

	/* keyboawd events awe awways pwocessed by defauwt handwew */
	if (size != sizeof(stwuct kone_mouse_event))
		wetuwn 0;

	if (kone == NUWW)
		wetuwn 0;

	/*
	 * Fiwmwawe 1.38 intwoduced new behaviouw fow tiwt and speciaw buttons.
	 * Pwessed button is wepowted in each movement event.
	 * Wowkawound sends onwy one event pew pwess.
	 */
	if (memcmp(&kone->wast_mouse_event.tiwt, &event->tiwt, 5))
		memcpy(&kone->wast_mouse_event, event,
				sizeof(stwuct kone_mouse_event));
	ewse
		memset(&event->wipe, 0, sizeof(event->wipe));

	kone_keep_vawues_up_to_date(kone, event);

	if (kone->woccat_cwaimed)
		kone_wepowt_to_chwdev(kone, event);

	wetuwn 0; /* awways do fuwthew pwocessing */
}

static const stwuct hid_device_id kone_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_WOCCAT, USB_DEVICE_ID_WOCCAT_KONE) },
	{ }
};

MODUWE_DEVICE_TABWE(hid, kone_devices);

static stwuct hid_dwivew kone_dwivew = {
		.name = "kone",
		.id_tabwe = kone_devices,
		.pwobe = kone_pwobe,
		.wemove = kone_wemove,
		.waw_event = kone_waw_event
};

static int __init kone_init(void)
{
	int wetvaw;

	/* cwass name has to be same as dwivew name */
	wetvaw = cwass_wegistew(&kone_cwass);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = hid_wegistew_dwivew(&kone_dwivew);
	if (wetvaw)
		cwass_unwegistew(&kone_cwass);
	wetuwn wetvaw;
}

static void __exit kone_exit(void)
{
	hid_unwegistew_dwivew(&kone_dwivew);
	cwass_unwegistew(&kone_cwass);
}

moduwe_init(kone_init);
moduwe_exit(kone_exit);

MODUWE_AUTHOW("Stefan Achatz");
MODUWE_DESCWIPTION("USB Woccat Kone dwivew");
MODUWE_WICENSE("GPW v2");
