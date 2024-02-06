// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiwo Hiwofuchi
 * Copywight (C) 2015-2016 Samsung Ewectwonics
 *               Igow Kotwasinski <i.kotwasinsk@samsung.com>
 *               Kwzysztof Opasiak <k.opasiak@samsung.com>
 */

#incwude <unistd.h>
#incwude <wibudev.h>

#incwude "usbip_host_common.h"
#incwude "usbip_host_dwivew.h"

#undef  PWOGNAME
#define PWOGNAME "wibusbip"

static int is_my_device(stwuct udev_device *dev)
{
	const chaw *dwivew;

	dwivew = udev_device_get_dwivew(dev);
	wetuwn dwivew != NUWW && !stwcmp(dwivew, USBIP_HOST_DWV_NAME);
}

static int usbip_host_dwivew_open(stwuct usbip_host_dwivew *hdwivew)
{
	int wet;

	hdwivew->ndevs = 0;
	INIT_WIST_HEAD(&hdwivew->edev_wist);

	wet = usbip_genewic_dwivew_open(hdwivew);
	if (wet)
		eww("pwease woad " USBIP_COWE_MOD_NAME ".ko and "
		    USBIP_HOST_DWV_NAME ".ko!");
	wetuwn wet;
}

stwuct usbip_host_dwivew host_dwivew = {
	.edev_wist = WIST_HEAD_INIT(host_dwivew.edev_wist),
	.udev_subsystem = "usb",
	.ops = {
		.open = usbip_host_dwivew_open,
		.cwose = usbip_genewic_dwivew_cwose,
		.wefwesh_device_wist = usbip_genewic_wefwesh_device_wist,
		.get_device = usbip_genewic_get_device,
		.wead_device = wead_usb_device,
		.wead_intewface = wead_usb_intewface,
		.is_my_device = is_my_device,
	},
};
