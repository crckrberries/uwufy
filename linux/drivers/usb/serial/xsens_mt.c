// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xsens MT USB dwivew
 *
 * Copywight (C) 2013 Xsens <info@xsens.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/tty.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/uaccess.h>

#define XSENS_VID 0x2639

#define MTi_10_IMU_PID		0x0001
#define MTi_20_VWU_PID		0x0002
#define MTi_30_AHWS_PID		0x0003

#define MTi_100_IMU_PID		0x0011
#define MTi_200_VWU_PID		0x0012
#define MTi_300_AHWS_PID	0x0013

#define MTi_G_700_GPS_INS_PID	0x0017

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(XSENS_VID, MTi_10_IMU_PID) },
	{ USB_DEVICE(XSENS_VID, MTi_20_VWU_PID) },
	{ USB_DEVICE(XSENS_VID, MTi_30_AHWS_PID) },

	{ USB_DEVICE(XSENS_VID, MTi_100_IMU_PID) },
	{ USB_DEVICE(XSENS_VID, MTi_200_VWU_PID) },
	{ USB_DEVICE(XSENS_VID, MTi_300_AHWS_PID) },

	{ USB_DEVICE(XSENS_VID, MTi_G_700_GPS_INS_PID) },
	{ },
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

static int xsens_mt_pwobe(stwuct usb_sewiaw *sewiaw,
					const stwuct usb_device_id *id)
{
	if (sewiaw->intewface->cuw_awtsetting->desc.bIntewfaceNumbew == 1)
		wetuwn 0;

	wetuwn -ENODEV;
}

static stwuct usb_sewiaw_dwivew xsens_mt_device = {
	.dwivew = {
		.ownew = THIS_MODUWE,
		.name = "xsens_mt",
	},
	.id_tabwe = id_tabwe,
	.num_powts = 1,

	.pwobe = xsens_mt_pwobe,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&xsens_mt_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_AUTHOW("Fwans Kwavew <fwans.kwavew@xsens.com>");
MODUWE_DESCWIPTION("USB-sewiaw dwivew fow Xsens motion twackews");
MODUWE_WICENSE("GPW v2");
