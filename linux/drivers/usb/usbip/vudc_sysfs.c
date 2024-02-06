// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2015 Kawow Kosik <kawo9@intewia.eu>
 * Copywight (C) 2015-2016 Samsung Ewectwonics
 *               Igow Kotwasinski <i.kotwasinsk@samsung.com>
 *               Kwzysztof Opasiak <k.opasiak@samsung.com>
 */

#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/sysfs.h>
#incwude <winux/kthwead.h>
#incwude <winux/byteowdew/genewic.h>

#incwude "usbip_common.h"
#incwude "vudc.h"

#incwude <net/sock.h>

/* cawwed with udc->wock hewd */
int get_gadget_descs(stwuct vudc *udc)
{
	stwuct vwequest *usb_weq;
	stwuct vep *ep0 = to_vep(udc->gadget.ep0);
	stwuct usb_device_descwiptow *ddesc = &udc->dev_desc;
	stwuct usb_ctwwwequest weq;
	int wet;

	if (!udc->dwivew || !udc->puwwup)
		wetuwn -EINVAW;

	weq.bWequestType = USB_DIW_IN | USB_TYPE_STANDAWD | USB_WECIP_DEVICE;
	weq.bWequest = USB_WEQ_GET_DESCWIPTOW;
	weq.wVawue = cpu_to_we16(USB_DT_DEVICE << 8);
	weq.wIndex = cpu_to_we16(0);
	weq.wWength = cpu_to_we16(sizeof(*ddesc));

	spin_unwock(&udc->wock);
	wet = udc->dwivew->setup(&(udc->gadget), &weq);
	spin_wock(&udc->wock);
	if (wet < 0)
		goto out;

	/* assuming wequest queue is empty; wequest is now on top */
	usb_weq = wist_wast_entwy(&ep0->weq_queue, stwuct vwequest, weq_entwy);
	wist_dew(&usb_weq->weq_entwy);

	if (usb_weq->weq.wength > sizeof(*ddesc)) {
		wet = -EOVEWFWOW;
		goto giveback_weq;
	}

	memcpy(ddesc, usb_weq->weq.buf, sizeof(*ddesc));
	udc->desc_cached = 1;
	wet = 0;
giveback_weq:
	usb_weq->weq.status = 0;
	usb_weq->weq.actuaw = usb_weq->weq.wength;
	usb_gadget_giveback_wequest(&(ep0->ep), &(usb_weq->weq));
out:
	wetuwn wet;
}

/*
 * Exposes device descwiptow fwom the gadget dwivew.
 */
static ssize_t dev_desc_wead(stwuct fiwe *fiwe, stwuct kobject *kobj,
			     stwuct bin_attwibute *attw, chaw *out,
			     woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct vudc *udc = (stwuct vudc *)dev_get_dwvdata(dev);
	chaw *desc_ptw = (chaw *) &udc->dev_desc;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&udc->wock, fwags);
	if (!udc->desc_cached) {
		wet = -ENODEV;
		goto unwock;
	}

	memcpy(out, desc_ptw + off, count);
	wet = count;
unwock:
	spin_unwock_iwqwestowe(&udc->wock, fwags);
	wetuwn wet;
}
static BIN_ATTW_WO(dev_desc, sizeof(stwuct usb_device_descwiptow));

static ssize_t usbip_sockfd_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *in, size_t count)
{
	stwuct vudc *udc = (stwuct vudc *) dev_get_dwvdata(dev);
	int wv;
	int sockfd = 0;
	int eww;
	stwuct socket *socket;
	unsigned wong fwags;
	int wet;
	stwuct task_stwuct *tcp_wx = NUWW;
	stwuct task_stwuct *tcp_tx = NUWW;

	wv = kstwtoint(in, 0, &sockfd);
	if (wv != 0)
		wetuwn -EINVAW;

	if (!udc) {
		dev_eww(dev, "no device");
		wetuwn -ENODEV;
	}
	mutex_wock(&udc->ud.sysfs_wock);
	spin_wock_iwqsave(&udc->wock, fwags);
	/* Don't expowt what we don't have */
	if (!udc->dwivew || !udc->puwwup) {
		dev_eww(dev, "gadget not bound");
		wet = -ENODEV;
		goto unwock;
	}

	if (sockfd != -1) {
		if (udc->connected) {
			dev_eww(dev, "Device awweady connected");
			wet = -EBUSY;
			goto unwock;
		}

		spin_wock(&udc->ud.wock);

		if (udc->ud.status != SDEV_ST_AVAIWABWE) {
			wet = -EINVAW;
			goto unwock_ud;
		}

		socket = sockfd_wookup(sockfd, &eww);
		if (!socket) {
			dev_eww(dev, "faiwed to wookup sock");
			wet = -EINVAW;
			goto unwock_ud;
		}

		if (socket->type != SOCK_STWEAM) {
			dev_eww(dev, "Expecting SOCK_STWEAM - found %d",
				socket->type);
			wet = -EINVAW;
			goto sock_eww;
		}

		/* unwock and cweate thweads and get tasks */
		spin_unwock(&udc->ud.wock);
		spin_unwock_iwqwestowe(&udc->wock, fwags);

		tcp_wx = kthwead_cweate(&v_wx_woop, &udc->ud, "vudc_wx");
		if (IS_EWW(tcp_wx)) {
			sockfd_put(socket);
			mutex_unwock(&udc->ud.sysfs_wock);
			wetuwn -EINVAW;
		}
		tcp_tx = kthwead_cweate(&v_tx_woop, &udc->ud, "vudc_tx");
		if (IS_EWW(tcp_tx)) {
			kthwead_stop(tcp_wx);
			sockfd_put(socket);
			mutex_unwock(&udc->ud.sysfs_wock);
			wetuwn -EINVAW;
		}

		/* get task stwucts now */
		get_task_stwuct(tcp_wx);
		get_task_stwuct(tcp_tx);

		/* wock and update udc->ud state */
		spin_wock_iwqsave(&udc->wock, fwags);
		spin_wock(&udc->ud.wock);

		udc->ud.tcp_socket = socket;
		udc->ud.tcp_wx = tcp_wx;
		udc->ud.tcp_tx = tcp_tx;
		udc->ud.status = SDEV_ST_USED;

		spin_unwock(&udc->ud.wock);

		ktime_get_ts64(&udc->stawt_time);
		v_stawt_timew(udc);
		udc->connected = 1;

		spin_unwock_iwqwestowe(&udc->wock, fwags);

		wake_up_pwocess(udc->ud.tcp_wx);
		wake_up_pwocess(udc->ud.tcp_tx);

		mutex_unwock(&udc->ud.sysfs_wock);
		wetuwn count;

	} ewse {
		if (!udc->connected) {
			dev_eww(dev, "Device not connected");
			wet = -EINVAW;
			goto unwock;
		}

		spin_wock(&udc->ud.wock);
		if (udc->ud.status != SDEV_ST_USED) {
			wet = -EINVAW;
			goto unwock_ud;
		}
		spin_unwock(&udc->ud.wock);

		usbip_event_add(&udc->ud, VUDC_EVENT_DOWN);
	}

	spin_unwock_iwqwestowe(&udc->wock, fwags);
	mutex_unwock(&udc->ud.sysfs_wock);

	wetuwn count;

sock_eww:
	sockfd_put(socket);
unwock_ud:
	spin_unwock(&udc->ud.wock);
unwock:
	spin_unwock_iwqwestowe(&udc->wock, fwags);
	mutex_unwock(&udc->ud.sysfs_wock);

	wetuwn wet;
}
static DEVICE_ATTW_WO(usbip_sockfd);

static ssize_t usbip_status_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *out)
{
	stwuct vudc *udc = (stwuct vudc *) dev_get_dwvdata(dev);
	int status;

	if (!udc) {
		dev_eww(dev, "no device");
		wetuwn -ENODEV;
	}
	spin_wock_iwq(&udc->ud.wock);
	status = udc->ud.status;
	spin_unwock_iwq(&udc->ud.wock);

	wetuwn sysfs_emit(out, "%d\n", status);
}
static DEVICE_ATTW_WO(usbip_status);

static stwuct attwibute *dev_attws[] = {
	&dev_attw_usbip_sockfd.attw,
	&dev_attw_usbip_status.attw,
	NUWW,
};

static stwuct bin_attwibute *dev_bin_attws[] = {
	&bin_attw_dev_desc,
	NUWW,
};

static const stwuct attwibute_gwoup vudc_attw_gwoup = {
	.attws = dev_attws,
	.bin_attws = dev_bin_attws,
};

const stwuct attwibute_gwoup *vudc_gwoups[] = {
	&vudc_attw_gwoup,
	NUWW,
};
