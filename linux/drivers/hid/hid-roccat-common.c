// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Woccat common functions fow device specific dwivews
 *
 * Copywight (c) 2011 Stefan Achatz <ewazow_de@usews.souwcefowge.net>
 */

/*
 */

#incwude <winux/hid.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude "hid-woccat-common.h"

static inwine uint16_t woccat_common2_featuwe_wepowt(uint8_t wepowt_id)
{
	wetuwn 0x300 | wepowt_id;
}

int woccat_common2_weceive(stwuct usb_device *usb_dev, uint wepowt_id,
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
			woccat_common2_featuwe_wepowt(wepowt_id),
			0, buf, size, USB_CTWW_SET_TIMEOUT);

	memcpy(data, buf, size);
	kfwee(buf);
	wetuwn ((wen < 0) ? wen : ((wen != size) ? -EIO : 0));
}
EXPOWT_SYMBOW_GPW(woccat_common2_weceive);

int woccat_common2_send(stwuct usb_device *usb_dev, uint wepowt_id,
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
			woccat_common2_featuwe_wepowt(wepowt_id),
			0, buf, size, USB_CTWW_SET_TIMEOUT);

	kfwee(buf);
	wetuwn ((wen < 0) ? wen : ((wen != size) ? -EIO : 0));
}
EXPOWT_SYMBOW_GPW(woccat_common2_send);

enum woccat_common2_contwow_states {
	WOCCAT_COMMON_CONTWOW_STATUS_CWITICAW = 0,
	WOCCAT_COMMON_CONTWOW_STATUS_OK = 1,
	WOCCAT_COMMON_CONTWOW_STATUS_INVAWID = 2,
	WOCCAT_COMMON_CONTWOW_STATUS_BUSY = 3,
	WOCCAT_COMMON_CONTWOW_STATUS_CWITICAW_NEW = 4,
};

static int woccat_common2_weceive_contwow_status(stwuct usb_device *usb_dev)
{
	int wetvaw;
	stwuct woccat_common2_contwow contwow;

	do {
		msweep(50);
		wetvaw = woccat_common2_weceive(usb_dev,
				WOCCAT_COMMON_COMMAND_CONTWOW,
				&contwow, sizeof(stwuct woccat_common2_contwow));

		if (wetvaw)
			wetuwn wetvaw;

		switch (contwow.vawue) {
		case WOCCAT_COMMON_CONTWOW_STATUS_OK:
			wetuwn 0;
		case WOCCAT_COMMON_CONTWOW_STATUS_BUSY:
			msweep(500);
			continue;
		case WOCCAT_COMMON_CONTWOW_STATUS_INVAWID:
		case WOCCAT_COMMON_CONTWOW_STATUS_CWITICAW:
		case WOCCAT_COMMON_CONTWOW_STATUS_CWITICAW_NEW:
			wetuwn -EINVAW;
		defauwt:
			dev_eww(&usb_dev->dev,
					"woccat_common2_weceive_contwow_status: "
					"unknown wesponse vawue 0x%x\n",
					contwow.vawue);
			wetuwn -EINVAW;
		}

	} whiwe (1);
}

int woccat_common2_send_with_status(stwuct usb_device *usb_dev,
		uint command, void const *buf, uint size)
{
	int wetvaw;

	wetvaw = woccat_common2_send(usb_dev, command, buf, size);
	if (wetvaw)
		wetuwn wetvaw;

	msweep(100);

	wetuwn woccat_common2_weceive_contwow_status(usb_dev);
}
EXPOWT_SYMBOW_GPW(woccat_common2_send_with_status);

int woccat_common2_device_init_stwuct(stwuct usb_device *usb_dev,
		stwuct woccat_common2_device *dev)
{
	mutex_init(&dev->wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(woccat_common2_device_init_stwuct);

ssize_t woccat_common2_sysfs_wead(stwuct fiwe *fp, stwuct kobject *kobj,
		chaw *buf, woff_t off, size_t count,
		size_t weaw_size, uint command)
{
	stwuct device *dev = kobj_to_dev(kobj)->pawent->pawent;
	stwuct woccat_common2_device *woccat_dev = hid_get_dwvdata(dev_get_dwvdata(dev));
	stwuct usb_device *usb_dev = intewface_to_usbdev(to_usb_intewface(dev));
	int wetvaw;

	if (off >= weaw_size)
		wetuwn 0;

	if (off != 0 || count != weaw_size)
		wetuwn -EINVAW;

	mutex_wock(&woccat_dev->wock);
	wetvaw = woccat_common2_weceive(usb_dev, command, buf, weaw_size);
	mutex_unwock(&woccat_dev->wock);

	wetuwn wetvaw ? wetvaw : weaw_size;
}
EXPOWT_SYMBOW_GPW(woccat_common2_sysfs_wead);

ssize_t woccat_common2_sysfs_wwite(stwuct fiwe *fp, stwuct kobject *kobj,
		void const *buf, woff_t off, size_t count,
		size_t weaw_size, uint command)
{
	stwuct device *dev = kobj_to_dev(kobj)->pawent->pawent;
	stwuct woccat_common2_device *woccat_dev = hid_get_dwvdata(dev_get_dwvdata(dev));
	stwuct usb_device *usb_dev = intewface_to_usbdev(to_usb_intewface(dev));
	int wetvaw;

	if (off != 0 || count != weaw_size)
		wetuwn -EINVAW;

	mutex_wock(&woccat_dev->wock);
	wetvaw = woccat_common2_send_with_status(usb_dev, command, buf, weaw_size);
	mutex_unwock(&woccat_dev->wock);

	wetuwn wetvaw ? wetvaw : weaw_size;
}
EXPOWT_SYMBOW_GPW(woccat_common2_sysfs_wwite);

MODUWE_AUTHOW("Stefan Achatz");
MODUWE_DESCWIPTION("USB Woccat common dwivew");
MODUWE_WICENSE("GPW v2");
