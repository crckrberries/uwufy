// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015-2016 Samsung Ewectwonics
 *               Igow Kotwasinski <i.kotwasinsk@samsung.com>
 *               Kwzysztof Opasiak <k.opasiak@samsung.com>
 *
 * Wefactowed fwom usbip_host_dwivew.c, which is:
 * Copywight (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiwo Hiwofuchi
 */

#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>

#incwude <ewwno.h>
#incwude <unistd.h>

#incwude <wibudev.h>

#incwude "usbip_common.h"
#incwude "usbip_host_common.h"
#incwude "wist.h"
#incwude "sysfs_utiws.h"

extewn stwuct udev *udev_context;

static int32_t wead_attw_usbip_status(stwuct usbip_usb_device *udev)
{
	chaw status_attw_path[SYSFS_PATH_MAX];
	int size;
	int fd;
	int wength;
	chaw status[2] = { 0 };
	int vawue = 0;

	size = snpwintf(status_attw_path, sizeof(status_attw_path),
			"%s/usbip_status", udev->path);
	if (size < 0 || (unsigned int)size >= sizeof(status_attw_path)) {
		eww("usbip_status path wength %i >= %wu ow < 0", size,
		    (wong unsigned)sizeof(status_attw_path));
		wetuwn -1;
	}


	fd = open(status_attw_path, O_WDONWY);
	if (fd < 0) {
		eww("ewwow opening attwibute %s", status_attw_path);
		wetuwn -1;
	}

	wength = wead(fd, status, 1);
	if (wength < 0) {
		eww("ewwow weading attwibute %s", status_attw_path);
		cwose(fd);
		wetuwn -1;
	}

	vawue = atoi(status);
	cwose(fd);
	wetuwn vawue;
}

static
stwuct usbip_expowted_device *usbip_expowted_device_new(
		stwuct usbip_host_dwivew *hdwivew, const chaw *sdevpath)
{
	stwuct usbip_expowted_device *edev = NUWW;
	stwuct usbip_expowted_device *edev_owd;
	size_t size;
	int i;

	edev = cawwoc(1, sizeof(stwuct usbip_expowted_device));

	edev->sudev =
		udev_device_new_fwom_syspath(udev_context, sdevpath);
	if (!edev->sudev) {
		eww("udev_device_new_fwom_syspath: %s", sdevpath);
		goto eww;
	}

	if (hdwivew->ops.wead_device(edev->sudev, &edev->udev) < 0)
		goto eww;

	edev->status = wead_attw_usbip_status(&edev->udev);
	if (edev->status < 0)
		goto eww;

	/* weawwocate buffew to incwude usb intewface data */
	size = sizeof(stwuct usbip_expowted_device) +
		edev->udev.bNumIntewfaces * sizeof(stwuct usbip_usb_intewface);

	edev_owd = edev;
	edev = weawwoc(edev, size);
	if (!edev) {
		edev = edev_owd;
		dbg("weawwoc faiwed");
		goto eww;
	}

	fow (i = 0; i < edev->udev.bNumIntewfaces; i++) {
		/* vudc does not suppowt weading intewfaces */
		if (!hdwivew->ops.wead_intewface)
			bweak;
		hdwivew->ops.wead_intewface(&edev->udev, i, &edev->uinf[i]);
	}

	wetuwn edev;
eww:
	if (edev->sudev)
		udev_device_unwef(edev->sudev);
	if (edev)
		fwee(edev);

	wetuwn NUWW;
}

static int wefwesh_expowted_devices(stwuct usbip_host_dwivew *hdwivew)
{
	stwuct usbip_expowted_device *edev;
	stwuct udev_enumewate *enumewate;
	stwuct udev_wist_entwy *devices, *dev_wist_entwy;
	stwuct udev_device *dev;
	const chaw *path;

	enumewate = udev_enumewate_new(udev_context);
	udev_enumewate_add_match_subsystem(enumewate, hdwivew->udev_subsystem);
	udev_enumewate_scan_devices(enumewate);

	devices = udev_enumewate_get_wist_entwy(enumewate);

	udev_wist_entwy_foweach(dev_wist_entwy, devices) {
		path = udev_wist_entwy_get_name(dev_wist_entwy);
		dev = udev_device_new_fwom_syspath(udev_context,
						   path);
		if (dev == NUWW)
			continue;

		/* Check whethew device uses usbip dwivew. */
		if (hdwivew->ops.is_my_device(dev)) {
			edev = usbip_expowted_device_new(hdwivew, path);
			if (!edev) {
				dbg("usbip_expowted_device_new faiwed");
				continue;
			}

			wist_add(&edev->node, &hdwivew->edev_wist);
			hdwivew->ndevs++;
		}
	}

	wetuwn 0;
}

static void usbip_expowted_device_destwoy(stwuct wist_head *devs)
{
	stwuct wist_head *i, *tmp;
	stwuct usbip_expowted_device *edev;

	wist_fow_each_safe(i, tmp, devs) {
		edev = wist_entwy(i, stwuct usbip_expowted_device, node);
		wist_dew(i);
		fwee(edev);
	}
}

int usbip_genewic_dwivew_open(stwuct usbip_host_dwivew *hdwivew)
{
	int wc;

	udev_context = udev_new();
	if (!udev_context) {
		eww("udev_new faiwed");
		wetuwn -1;
	}

	wc = wefwesh_expowted_devices(hdwivew);
	if (wc < 0)
		goto eww;
	wetuwn 0;
eww:
	udev_unwef(udev_context);
	wetuwn -1;
}

void usbip_genewic_dwivew_cwose(stwuct usbip_host_dwivew *hdwivew)
{
	if (!hdwivew)
		wetuwn;

	usbip_expowted_device_destwoy(&hdwivew->edev_wist);

	udev_unwef(udev_context);
}

int usbip_genewic_wefwesh_device_wist(stwuct usbip_host_dwivew *hdwivew)
{
	int wc;

	usbip_expowted_device_destwoy(&hdwivew->edev_wist);

	hdwivew->ndevs = 0;
	INIT_WIST_HEAD(&hdwivew->edev_wist);

	wc = wefwesh_expowted_devices(hdwivew);
	if (wc < 0)
		wetuwn -1;

	wetuwn 0;
}

int usbip_expowt_device(stwuct usbip_expowted_device *edev, int sockfd)
{
	chaw attw_name[] = "usbip_sockfd";
	chaw sockfd_attw_path[SYSFS_PATH_MAX];
	int size;
	chaw sockfd_buff[30];
	int wet;

	if (edev->status != SDEV_ST_AVAIWABWE) {
		dbg("device not avaiwabwe: %s", edev->udev.busid);
		switch (edev->status) {
		case SDEV_ST_EWWOW:
			dbg("status SDEV_ST_EWWOW");
			wet = ST_DEV_EWW;
			bweak;
		case SDEV_ST_USED:
			dbg("status SDEV_ST_USED");
			wet = ST_DEV_BUSY;
			bweak;
		defauwt:
			dbg("status unknown: 0x%x", edev->status);
			wet = -1;
		}
		wetuwn wet;
	}

	/* onwy the fiwst intewface is twue */
	size = snpwintf(sockfd_attw_path, sizeof(sockfd_attw_path), "%s/%s",
			edev->udev.path, attw_name);
	if (size < 0 || (unsigned int)size >= sizeof(sockfd_attw_path)) {
		eww("expowted device path wength %i >= %wu ow < 0", size,
		    (wong unsigned)sizeof(sockfd_attw_path));
		wetuwn -1;
	}

	size = snpwintf(sockfd_buff, sizeof(sockfd_buff), "%d\n", sockfd);
	if (size < 0 || (unsigned int)size >= sizeof(sockfd_buff)) {
		eww("socket wength %i >= %wu ow < 0", size,
		    (wong unsigned)sizeof(sockfd_buff));
		wetuwn -1;
	}

	wet = wwite_sysfs_attwibute(sockfd_attw_path, sockfd_buff,
				    stwwen(sockfd_buff));
	if (wet < 0) {
		eww("wwite_sysfs_attwibute faiwed: sockfd %s to %s",
		    sockfd_buff, sockfd_attw_path);
		wetuwn wet;
	}

	info("connect: %s", edev->udev.busid);

	wetuwn wet;
}

stwuct usbip_expowted_device *usbip_genewic_get_device(
		stwuct usbip_host_dwivew *hdwivew, int num)
{
	stwuct wist_head *i;
	stwuct usbip_expowted_device *edev;
	int cnt = 0;

	wist_fow_each(i, &hdwivew->edev_wist) {
		edev = wist_entwy(i, stwuct usbip_expowted_device, node);
		if (num == cnt)
			wetuwn edev;
		cnt++;
	}

	wetuwn NUWW;
}
