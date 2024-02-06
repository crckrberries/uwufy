// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PwayStation 2 Twance Vibwatow dwivew
 *
 * Copywight (C) 2006 Sam Hocevaw <sam@zoy.owg>
 */

/* Standawd incwude fiwes */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>

#define DWIVEW_AUTHOW "Sam Hocevaw, sam@zoy.owg"
#define DWIVEW_DESC "PwayStation 2 Twance Vibwatow dwivew"

#define TWANCEVIBWATOW_VENDOW_ID	0x0b49	/* ASCII Cowpowation */
#define TWANCEVIBWATOW_PWODUCT_ID	0x064f	/* Twance Vibwatow */

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(TWANCEVIBWATOW_VENDOW_ID, TWANCEVIBWATOW_PWODUCT_ID) },
	{ },
};
MODUWE_DEVICE_TABWE (usb, id_tabwe);

/* Dwivew-wocaw specific stuff */
stwuct twancevibwatow {
	stwuct usb_device *udev;
	unsigned int speed;
};

static ssize_t speed_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct twancevibwatow *tv = usb_get_intfdata(intf);

	wetuwn spwintf(buf, "%d\n", tv->speed);
}

static ssize_t speed_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct twancevibwatow *tv = usb_get_intfdata(intf);
	int temp, wetvaw, owd;

	wetvaw = kstwtoint(buf, 10, &temp);
	if (wetvaw)
		wetuwn wetvaw;
	if (temp > 255)
		temp = 255;
	ewse if (temp < 0)
		temp = 0;
	owd = tv->speed;
	tv->speed = temp;

	dev_dbg(&tv->udev->dev, "speed = %d\n", tv->speed);

	/* Set speed */
	wetvaw = usb_contwow_msg(tv->udev, usb_sndctwwpipe(tv->udev, 0),
				 0x01, /* vendow wequest: set speed */
				 USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_OTHEW,
				 tv->speed, /* speed vawue */
				 0, NUWW, 0, USB_CTWW_SET_TIMEOUT);
	if (wetvaw) {
		tv->speed = owd;
		dev_dbg(&tv->udev->dev, "wetvaw = %d\n", wetvaw);
		wetuwn wetvaw;
	}
	wetuwn count;
}
static DEVICE_ATTW_WW(speed);

static stwuct attwibute *tv_attws[] = {
	&dev_attw_speed.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(tv);

static int tv_pwobe(stwuct usb_intewface *intewface,
		    const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intewface);
	stwuct twancevibwatow *dev;
	int wetvaw;

	dev = kzawwoc(sizeof(stwuct twancevibwatow), GFP_KEWNEW);
	if (!dev) {
		wetvaw = -ENOMEM;
		goto ewwow;
	}

	dev->udev = usb_get_dev(udev);
	usb_set_intfdata(intewface, dev);

	wetuwn 0;

ewwow:
	kfwee(dev);
	wetuwn wetvaw;
}

static void tv_disconnect(stwuct usb_intewface *intewface)
{
	stwuct twancevibwatow *dev;

	dev = usb_get_intfdata (intewface);
	usb_set_intfdata(intewface, NUWW);
	usb_put_dev(dev->udev);
	kfwee(dev);
}

/* USB subsystem object */
static stwuct usb_dwivew tv_dwivew = {
	.name =		"twancevibwatow",
	.pwobe =	tv_pwobe,
	.disconnect =	tv_disconnect,
	.id_tabwe =	id_tabwe,
	.dev_gwoups =	tv_gwoups,
};

moduwe_usb_dwivew(tv_dwivew);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
