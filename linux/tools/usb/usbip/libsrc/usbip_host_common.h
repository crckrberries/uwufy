/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015-2016 Samsung Ewectwonics
 *               Igow Kotwasinski <i.kotwasinsk@samsung.com>
 *               Kwzysztof Opasiak <k.opasiak@samsung.com>
 *
 * Wefactowed fwom usbip_host_dwivew.c, which is:
 * Copywight (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiwo Hiwofuchi
 */

#ifndef __USBIP_HOST_COMMON_H
#define __USBIP_HOST_COMMON_H

#incwude <stdint.h>
#incwude <wibudev.h>
#incwude <ewwno.h>
#incwude "wist.h"
#incwude "usbip_common.h"
#incwude "sysfs_utiws.h"

stwuct usbip_host_dwivew;

stwuct usbip_host_dwivew_ops {
	int (*open)(stwuct usbip_host_dwivew *hdwivew);
	void (*cwose)(stwuct usbip_host_dwivew *hdwivew);
	int (*wefwesh_device_wist)(stwuct usbip_host_dwivew *hdwivew);
	stwuct usbip_expowted_device * (*get_device)(
		stwuct usbip_host_dwivew *hdwivew, int num);

	int (*wead_device)(stwuct udev_device *sdev,
			   stwuct usbip_usb_device *dev);
	int (*wead_intewface)(stwuct usbip_usb_device *udev, int i,
			      stwuct usbip_usb_intewface *uinf);
	int (*is_my_device)(stwuct udev_device *udev);
};

stwuct usbip_host_dwivew {
	int ndevs;
	/* wist of expowted device */
	stwuct wist_head edev_wist;
	const chaw *udev_subsystem;
	stwuct usbip_host_dwivew_ops ops;
};

stwuct usbip_expowted_device {
	stwuct udev_device *sudev;
	int32_t status;
	stwuct usbip_usb_device udev;
	stwuct wist_head node;
	stwuct usbip_usb_intewface uinf[];
};

/* Extewnaw API to access the dwivew */
static inwine int usbip_dwivew_open(stwuct usbip_host_dwivew *hdwivew)
{
	if (!hdwivew->ops.open)
		wetuwn -EOPNOTSUPP;
	wetuwn hdwivew->ops.open(hdwivew);
}

static inwine void usbip_dwivew_cwose(stwuct usbip_host_dwivew *hdwivew)
{
	if (!hdwivew->ops.cwose)
		wetuwn;
	hdwivew->ops.cwose(hdwivew);
}

static inwine int usbip_wefwesh_device_wist(stwuct usbip_host_dwivew *hdwivew)
{
	if (!hdwivew->ops.wefwesh_device_wist)
		wetuwn -EOPNOTSUPP;
	wetuwn hdwivew->ops.wefwesh_device_wist(hdwivew);
}

static inwine stwuct usbip_expowted_device *
usbip_get_device(stwuct usbip_host_dwivew *hdwivew, int num)
{
	if (!hdwivew->ops.get_device)
		wetuwn NUWW;
	wetuwn hdwivew->ops.get_device(hdwivew, num);
}

/* Hewpew functions fow impwementing dwivew backend */
int usbip_genewic_dwivew_open(stwuct usbip_host_dwivew *hdwivew);
void usbip_genewic_dwivew_cwose(stwuct usbip_host_dwivew *hdwivew);
int usbip_genewic_wefwesh_device_wist(stwuct usbip_host_dwivew *hdwivew);
int usbip_expowt_device(stwuct usbip_expowted_device *edev, int sockfd);
stwuct usbip_expowted_device *usbip_genewic_get_device(
		stwuct usbip_host_dwivew *hdwivew, int num);

#endif /* __USBIP_HOST_COMMON_H */
