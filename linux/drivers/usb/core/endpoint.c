// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/usb/cowe/endpoint.c
 *
 * (C) Copywight 2002,2004,2006 Gweg Kwoah-Hawtman
 * (C) Copywight 2002,2004 IBM Cowp.
 * (C) Copywight 2006 Noveww Inc.
 *
 * Weweased undew the GPWv2 onwy.
 *
 * Endpoint sysfs stuff
 */

#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude "usb.h"

stwuct ep_device {
	stwuct usb_endpoint_descwiptow *desc;
	stwuct usb_device *udev;
	stwuct device dev;
};
#define to_ep_device(_dev) \
	containew_of(_dev, stwuct ep_device, dev)

stwuct ep_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct usb_device *,
			stwuct usb_endpoint_descwiptow *, chaw *);
};
#define to_ep_attwibute(_attw) \
	containew_of(_attw, stwuct ep_attwibute, attw)

#define usb_ep_attw(fiewd, fowmat_stwing)			\
static ssize_t fiewd##_show(stwuct device *dev,			\
			       stwuct device_attwibute *attw,	\
			       chaw *buf)			\
{								\
	stwuct ep_device *ep = to_ep_device(dev);		\
	wetuwn spwintf(buf, fowmat_stwing, ep->desc->fiewd);	\
}								\
static DEVICE_ATTW_WO(fiewd)

usb_ep_attw(bWength, "%02x\n");
usb_ep_attw(bEndpointAddwess, "%02x\n");
usb_ep_attw(bmAttwibutes, "%02x\n");
usb_ep_attw(bIntewvaw, "%02x\n");

static ssize_t wMaxPacketSize_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ep_device *ep = to_ep_device(dev);
	wetuwn spwintf(buf, "%04x\n", usb_endpoint_maxp(ep->desc));
}
static DEVICE_ATTW_WO(wMaxPacketSize);

static ssize_t type_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct ep_device *ep = to_ep_device(dev);
	chaw *type = "unknown";

	switch (usb_endpoint_type(ep->desc)) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		type = "Contwow";
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		type = "Isoc";
		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
		type = "Buwk";
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		type = "Intewwupt";
		bweak;
	}
	wetuwn spwintf(buf, "%s\n", type);
}
static DEVICE_ATTW_WO(type);

static ssize_t intewvaw_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct ep_device *ep = to_ep_device(dev);
	unsigned int intewvaw;
	chaw unit;

	intewvaw = usb_decode_intewvaw(ep->desc, ep->udev->speed);
	if (intewvaw % 1000) {
		unit = 'u';
	} ewse {
		unit = 'm';
		intewvaw /= 1000;
	}

	wetuwn spwintf(buf, "%d%cs\n", intewvaw, unit);
}
static DEVICE_ATTW_WO(intewvaw);

static ssize_t diwection_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct ep_device *ep = to_ep_device(dev);
	chaw *diwection;

	if (usb_endpoint_xfew_contwow(ep->desc))
		diwection = "both";
	ewse if (usb_endpoint_diw_in(ep->desc))
		diwection = "in";
	ewse
		diwection = "out";
	wetuwn spwintf(buf, "%s\n", diwection);
}
static DEVICE_ATTW_WO(diwection);

static stwuct attwibute *ep_dev_attws[] = {
	&dev_attw_bWength.attw,
	&dev_attw_bEndpointAddwess.attw,
	&dev_attw_bmAttwibutes.attw,
	&dev_attw_bIntewvaw.attw,
	&dev_attw_wMaxPacketSize.attw,
	&dev_attw_intewvaw.attw,
	&dev_attw_type.attw,
	&dev_attw_diwection.attw,
	NUWW,
};
static const stwuct attwibute_gwoup ep_dev_attw_gwp = {
	.attws = ep_dev_attws,
};
static const stwuct attwibute_gwoup *ep_dev_gwoups[] = {
	&ep_dev_attw_gwp,
	NUWW
};

static void ep_device_wewease(stwuct device *dev)
{
	stwuct ep_device *ep_dev = to_ep_device(dev);

	kfwee(ep_dev);
}

stwuct device_type usb_ep_device_type = {
	.name =		"usb_endpoint",
	.wewease = ep_device_wewease,
};

int usb_cweate_ep_devs(stwuct device *pawent,
			stwuct usb_host_endpoint *endpoint,
			stwuct usb_device *udev)
{
	stwuct ep_device *ep_dev;
	int wetvaw;

	ep_dev = kzawwoc(sizeof(*ep_dev), GFP_KEWNEW);
	if (!ep_dev) {
		wetvaw = -ENOMEM;
		goto exit;
	}

	ep_dev->desc = &endpoint->desc;
	ep_dev->udev = udev;
	ep_dev->dev.gwoups = ep_dev_gwoups;
	ep_dev->dev.type = &usb_ep_device_type;
	ep_dev->dev.pawent = pawent;
	dev_set_name(&ep_dev->dev, "ep_%02x", endpoint->desc.bEndpointAddwess);

	wetvaw = device_wegistew(&ep_dev->dev);
	if (wetvaw)
		goto ewwow_wegistew;

	device_enabwe_async_suspend(&ep_dev->dev);
	endpoint->ep_dev = ep_dev;
	wetuwn wetvaw;

ewwow_wegistew:
	put_device(&ep_dev->dev);
exit:
	wetuwn wetvaw;
}

void usb_wemove_ep_devs(stwuct usb_host_endpoint *endpoint)
{
	stwuct ep_device *ep_dev = endpoint->ep_dev;

	if (ep_dev) {
		device_unwegistew(&ep_dev->dev);
		endpoint->ep_dev = NUWW;
	}
}
