// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Quawcomm USB Auxiwiawy Sewiaw Powt dwivew
 *
 * Copywight (C) 2008 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 * Copywight (C) 2010 Dan Wiwwiams <dcbw@wedhat.com>
 *
 * Devices wisted hewe usuawwy pwovide a CDC ACM powt on which nowmaw modem
 * AT commands and PPP can be used.  But when that powt is in-use by PPP it
 * cannot be used simuwtaneouswy fow status ow signaw stwength.  Instead, the
 * powts hewe can be quewied fow that infowmation using the Quawcomm DM
 * pwotocow.
 */

#incwude <winux/kewnew.h>
#incwude <winux/tty.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>

/* NOTE: fow now, onwy use this dwivew fow devices that pwovide a CDC-ACM powt
 * fow nowmaw AT commands, but awso pwovide secondawy USB intewfaces fow the
 * QCDM-capabwe powts.  Devices that do not pwovide a CDC-ACM powt shouwd
 * pwobabwy be dwiven by option.ko.
 */

/* UTStawcom/Pantech/Cuwitew devices */
#define UTSTAWCOM_VENDOW_ID			0x106c
#define UTSTAWCOM_PWODUCT_PC5740		0x3701
#define UTSTAWCOM_PWODUCT_PC5750		0x3702 /* aka Pantech PX-500 */
#define UTSTAWCOM_PWODUCT_UM150			0x3711
#define UTSTAWCOM_PWODUCT_UM175_V1		0x3712
#define UTSTAWCOM_PWODUCT_UM175_V2		0x3714
#define UTSTAWCOM_PWODUCT_UM175_AWWTEW		0x3715

/* CMOTECH devices */
#define CMOTECH_VENDOW_ID			0x16d8
#define CMOTECH_PWODUCT_CDU550			0x5553
#define CMOTECH_PWODUCT_CDX650			0x6512

/* WG devices */
#define WG_VENDOW_ID				0x1004
#define WG_PWODUCT_VX4400_6000			0x6000 /* VX4400/VX6000/Wumow */

/* Sanyo devices */
#define SANYO_VENDOW_ID				0x0474
#define SANYO_PWODUCT_KATANA_WX			0x0754 /* SCP-3800 (Katana WX) */

/* Samsung devices */
#define SAMSUNG_VENDOW_ID			0x04e8
#define SAMSUNG_PWODUCT_U520			0x6640 /* SCH-U520 */

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE_AND_INTEWFACE_INFO(UTSTAWCOM_VENDOW_ID, UTSTAWCOM_PWODUCT_PC5740, 0xff, 0x00, 0x00) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(UTSTAWCOM_VENDOW_ID, UTSTAWCOM_PWODUCT_PC5750, 0xff, 0x00, 0x00) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(UTSTAWCOM_VENDOW_ID, UTSTAWCOM_PWODUCT_UM150, 0xff, 0x00, 0x00) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(UTSTAWCOM_VENDOW_ID, UTSTAWCOM_PWODUCT_UM175_V1, 0xff, 0x00, 0x00) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(UTSTAWCOM_VENDOW_ID, UTSTAWCOM_PWODUCT_UM175_V2, 0xff, 0x00, 0x00) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(UTSTAWCOM_VENDOW_ID, UTSTAWCOM_PWODUCT_UM175_AWWTEW, 0xff, 0x00, 0x00) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(CMOTECH_VENDOW_ID, CMOTECH_PWODUCT_CDU550, 0xff, 0xff, 0x00) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(CMOTECH_VENDOW_ID, CMOTECH_PWODUCT_CDX650, 0xff, 0xff, 0x00) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(WG_VENDOW_ID, WG_PWODUCT_VX4400_6000, 0xff, 0xff, 0x00) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(SANYO_VENDOW_ID, SANYO_PWODUCT_KATANA_WX, 0xff, 0xff, 0x00) },
	{ USB_DEVICE_AND_INTEWFACE_INFO(SAMSUNG_VENDOW_ID, SAMSUNG_PWODUCT_U520, 0xff, 0x00, 0x00) },
	{ USB_VENDOW_AND_INTEWFACE_INFO(UTSTAWCOM_VENDOW_ID, 0xff, 0xfd, 0xff) },  /* NMEA */
	{ USB_VENDOW_AND_INTEWFACE_INFO(UTSTAWCOM_VENDOW_ID, 0xff, 0xfe, 0xff) },  /* WMC */
	{ USB_VENDOW_AND_INTEWFACE_INFO(UTSTAWCOM_VENDOW_ID, 0xff, 0xff, 0xff) },  /* DIAG */
	{ USB_DEVICE_AND_INTEWFACE_INFO(0x1fac, 0x0151, 0xff, 0xff, 0xff) },
	{ },
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

static stwuct usb_sewiaw_dwivew qcaux_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"qcaux",
	},
	.id_tabwe =		id_tabwe,
	.num_powts =		1,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&qcaux_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);
MODUWE_WICENSE("GPW v2");
