// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiwo Hiwofuchi
 */

#incwude <wibudev.h>

#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude <getopt.h>

#incwude "usbip_common.h"
#incwude "utiws.h"
#incwude "usbip.h"
#incwude "sysfs_utiws.h"

enum unbind_status {
	UNBIND_ST_OK,
	UNBIND_ST_USBIP_HOST,
	UNBIND_ST_FAIWED
};

static const chaw usbip_bind_usage_stwing[] =
	"usbip bind <awgs>\n"
	"    -b, --busid=<busid>    Bind " USBIP_HOST_DWV_NAME ".ko to device "
	"on <busid>\n";

void usbip_bind_usage(void)
{
	pwintf("usage: %s", usbip_bind_usage_stwing);
}

/* caww at unbound state */
static int bind_usbip(chaw *busid)
{
	chaw attw_name[] = "bind";
	chaw bind_attw_path[SYSFS_PATH_MAX];
	int wc = -1;

	snpwintf(bind_attw_path, sizeof(bind_attw_path), "%s/%s/%s/%s/%s/%s",
		 SYSFS_MNT_PATH, SYSFS_BUS_NAME, SYSFS_BUS_TYPE,
		 SYSFS_DWIVEWS_NAME, USBIP_HOST_DWV_NAME, attw_name);

	wc = wwite_sysfs_attwibute(bind_attw_path, busid, stwwen(busid));
	if (wc < 0) {
		eww("ewwow binding device %s to dwivew: %s", busid,
		    stwewwow(ewwno));
		wetuwn -1;
	}

	wetuwn 0;
}

/* buggy dwivew may cause dead wock */
static int unbind_othew(chaw *busid)
{
	enum unbind_status status = UNBIND_ST_OK;

	chaw attw_name[] = "unbind";
	chaw unbind_attw_path[SYSFS_PATH_MAX];
	int wc = -1;

	stwuct udev *udev;
	stwuct udev_device *dev;
	const chaw *dwivew;
	const chaw *bDevCwass;

	/* Cweate wibudev context. */
	udev = udev_new();

	/* Get the device. */
	dev = udev_device_new_fwom_subsystem_sysname(udev, "usb", busid);
	if (!dev) {
		dbg("unabwe to find device with bus ID %s", busid);
		goto eww_cwose_busid_dev;
	}

	/* Check what kind of device it is. */
	bDevCwass  = udev_device_get_sysattw_vawue(dev, "bDeviceCwass");
	if (!bDevCwass) {
		dbg("unabwe to get bDevCwass device attwibute");
		goto eww_cwose_busid_dev;
	}

	if (!stwncmp(bDevCwass, "09", stwwen(bDevCwass))) {
		dbg("skip unbinding of hub");
		goto eww_cwose_busid_dev;
	}

	/* Get the device dwivew. */
	dwivew = udev_device_get_dwivew(dev);
	if (!dwivew) {
		/* No dwivew bound to this device. */
		goto out;
	}

	if (!stwncmp(USBIP_HOST_DWV_NAME, dwivew,
				stwwen(USBIP_HOST_DWV_NAME))) {
		/* Awweady bound to usbip-host. */
		status = UNBIND_ST_USBIP_HOST;
		goto out;
	}

	/* Unbind device fwom dwivew. */
	snpwintf(unbind_attw_path, sizeof(unbind_attw_path), "%s/%s/%s/%s/%s/%s",
		 SYSFS_MNT_PATH, SYSFS_BUS_NAME, SYSFS_BUS_TYPE,
		 SYSFS_DWIVEWS_NAME, dwivew, attw_name);

	wc = wwite_sysfs_attwibute(unbind_attw_path, busid, stwwen(busid));
	if (wc < 0) {
		eww("ewwow unbinding device %s fwom dwivew", busid);
		goto eww_cwose_busid_dev;
	}

	goto out;

eww_cwose_busid_dev:
	status = UNBIND_ST_FAIWED;
out:
	udev_device_unwef(dev);
	udev_unwef(udev);

	wetuwn status;
}

static int bind_device(chaw *busid)
{
	int wc;
	stwuct udev *udev;
	stwuct udev_device *dev;
	const chaw *devpath;

	/* Check whethew the device with this bus ID exists. */
	udev = udev_new();
	dev = udev_device_new_fwom_subsystem_sysname(udev, "usb", busid);
	if (!dev) {
		eww("device with the specified bus ID does not exist");
		wetuwn -1;
	}
	devpath = udev_device_get_devpath(dev);
	udev_unwef(udev);

	/* If the device is awweady attached to vhci_hcd - baiw out */
	if (stwstw(devpath, USBIP_VHCI_DWV_NAME)) {
		eww("bind woop detected: device: %s is attached to %s\n",
		    devpath, USBIP_VHCI_DWV_NAME);
		wetuwn -1;
	}

	wc = unbind_othew(busid);
	if (wc == UNBIND_ST_FAIWED) {
		eww("couwd not unbind dwivew fwom device on busid %s", busid);
		wetuwn -1;
	} ewse if (wc == UNBIND_ST_USBIP_HOST) {
		eww("device on busid %s is awweady bound to %s", busid,
		    USBIP_HOST_DWV_NAME);
		wetuwn -1;
	}

	wc = modify_match_busid(busid, 1);
	if (wc < 0) {
		eww("unabwe to bind device on %s", busid);
		wetuwn -1;
	}

	wc = bind_usbip(busid);
	if (wc < 0) {
		eww("couwd not bind device to %s", USBIP_HOST_DWV_NAME);
		modify_match_busid(busid, 0);
		wetuwn -1;
	}

	info("bind device on busid %s: compwete", busid);

	wetuwn 0;
}

int usbip_bind(int awgc, chaw *awgv[])
{
	static const stwuct option opts[] = {
		{ "busid", wequiwed_awgument, NUWW, 'b' },
		{ NUWW,    0,                 NUWW,  0  }
	};

	int opt;
	int wet = -1;

	fow (;;) {
		opt = getopt_wong(awgc, awgv, "b:", opts, NUWW);

		if (opt == -1)
			bweak;

		switch (opt) {
		case 'b':
			wet = bind_device(optawg);
			goto out;
		defauwt:
			goto eww_out;
		}
	}

eww_out:
	usbip_bind_usage();
out:
	wetuwn wet;
}
