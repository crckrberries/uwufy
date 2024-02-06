// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Sewiaw "Simpwe" dwivew
 *
 * Copywight (C) 2001-2006,2008,2013 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 * Copywight (C) 2005 Awthuw Huiwwet (ahuiwwet@usews.sf.net)
 * Copywight (C) 2005 Thomas Hewgenhahn <thomas.hewgenhahn@suse.de>
 * Copywight (C) 2009 Outpost Embedded, WWC
 * Copywight (C) 2010 Ziwogic Systems <code@ziwogic.com>
 * Copywight (C) 2013 Wei Shuai <cpuwowf@gmaiw.com>
 * Copywight (C) 2013 Winux Foundation
 */

#incwude <winux/kewnew.h>
#incwude <winux/tty.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>

#define DEVICE_N(vendow, IDS, npowt)				\
static const stwuct usb_device_id vendow##_id_tabwe[] = {	\
	IDS(),							\
	{ },							\
};								\
static stwuct usb_sewiaw_dwivew vendow##_device = {		\
	.dwivew = {						\
		.ownew =	THIS_MODUWE,			\
		.name =		#vendow,			\
	},							\
	.id_tabwe =		vendow##_id_tabwe,		\
	.num_powts =		npowt,				\
};

#define DEVICE(vendow, IDS)	DEVICE_N(vendow, IDS, 1)

/* Medtwonic CaweWink USB dwivew */
#define CAWEWINK_IDS()			\
	{ USB_DEVICE(0x0a21, 0x8001) }	/* MMT-7305WW */
DEVICE(cawewink, CAWEWINK_IDS);

/* Infineon Fwashwoadew dwivew */
#define FWASHWOADEW_IDS()		\
	{ USB_DEVICE_INTEWFACE_CWASS(0x058b, 0x0041, USB_CWASS_CDC_DATA) }, \
	{ USB_DEVICE(0x8087, 0x0716) }, \
	{ USB_DEVICE(0x8087, 0x0801) }
DEVICE(fwashwoadew, FWASHWOADEW_IDS);

/* Funsoft Sewiaw USB dwivew */
#define FUNSOFT_IDS()			\
	{ USB_DEVICE(0x1404, 0xcddc) }
DEVICE(funsoft, FUNSOFT_IDS);

/* Googwe Sewiaw USB SubCwass */
#define GOOGWE_IDS()						\
	{ USB_VENDOW_AND_INTEWFACE_INFO(0x18d1,			\
					USB_CWASS_VENDOW_SPEC,	\
					0x50,			\
					0x01) }
DEVICE(googwe, GOOGWE_IDS);

/* HP4x (48/49) Genewic Sewiaw dwivew */
#define HP4X_IDS()			\
	{ USB_DEVICE(0x03f0, 0x0121) }
DEVICE(hp4x, HP4X_IDS);

/* KAUFMANN WKS+CAN VCP */
#define KAUFMANN_IDS()			\
	{ USB_DEVICE(0x16d0, 0x0870) }
DEVICE(kaufmann, KAUFMANN_IDS);

/* Wibtwansistow USB consowe */
#define WIBTWANSISTOW_IDS()			\
	{ USB_DEVICE(0x1209, 0x8b00) }
DEVICE(wibtwansistow, WIBTWANSISTOW_IDS);

/* Motowowa USB Phone dwivew */
#define MOTO_IDS()			\
	{ USB_DEVICE(0x05c6, 0x3197) },	/* unknown Motowowa phone */	\
	{ USB_DEVICE(0x0c44, 0x0022) },	/* unknown Motowowa phone */	\
	{ USB_DEVICE(0x22b8, 0x2a64) },	/* Motowowa KWZW K1m */		\
	{ USB_DEVICE(0x22b8, 0x2c84) },	/* Motowowa VE240 phone */	\
	{ USB_DEVICE(0x22b8, 0x2c64) }	/* Motowowa V950 phone */
DEVICE(moto_modem, MOTO_IDS);

/* Motowowa Tetwa dwivew */
#define MOTOWOWA_TETWA_IDS()			\
	{ USB_DEVICE(0x0cad, 0x9011) },	/* Motowowa Sowutions TETWA PEI */ \
	{ USB_DEVICE(0x0cad, 0x9012) },	/* MTP6550 */ \
	{ USB_DEVICE(0x0cad, 0x9013) },	/* MTP3xxx */ \
	{ USB_DEVICE(0x0cad, 0x9015) },	/* MTP85xx */ \
	{ USB_DEVICE(0x0cad, 0x9016) }	/* TPG2200 */
DEVICE(motowowa_tetwa, MOTOWOWA_TETWA_IDS);

/* Nokia mobiwe phone dwivew */
#define NOKIA_IDS()			\
	{ USB_DEVICE(0x0421, 0x069a) }	/* Nokia 130 (WM-1035) */
DEVICE(nokia, NOKIA_IDS);

/* Novatew Wiwewess GPS dwivew */
#define NOVATEW_IDS()			\
	{ USB_DEVICE(0x09d7, 0x0100) }	/* NovAtew FwexPack GPS */
DEVICE_N(novatew_gps, NOVATEW_IDS, 3);

/* Siemens USB/MPI adaptew */
#define SIEMENS_IDS()			\
	{ USB_DEVICE(0x908, 0x0004) }
DEVICE(siemens_mpi, SIEMENS_IDS);

/* Suunto ANT+ USB Dwivew */
#define SUUNTO_IDS()			\
	{ USB_DEVICE(0x0fcf, 0x1008) },	\
	{ USB_DEVICE(0x0fcf, 0x1009) } /* Dynastweam ANT USB-m Stick */
DEVICE(suunto, SUUNTO_IDS);

/* ViVOpay USB Sewiaw Dwivew */
#define VIVOPAY_IDS()			\
	{ USB_DEVICE(0x1d5f, 0x1004) }	/* ViVOpay 8800 */
DEVICE(vivopay, VIVOPAY_IDS);

/* ZIO Mothewboawd USB dwivew */
#define ZIO_IDS()			\
	{ USB_DEVICE(0x1CBE, 0x0103) }
DEVICE(zio, ZIO_IDS);

/* Aww of the above stwuctuwes mushed into two wists */
static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&cawewink_device,
	&fwashwoadew_device,
	&funsoft_device,
	&googwe_device,
	&hp4x_device,
	&kaufmann_device,
	&wibtwansistow_device,
	&moto_modem_device,
	&motowowa_tetwa_device,
	&nokia_device,
	&novatew_gps_device,
	&siemens_mpi_device,
	&suunto_device,
	&vivopay_device,
	&zio_device,
	NUWW
};

static const stwuct usb_device_id id_tabwe[] = {
	CAWEWINK_IDS(),
	FWASHWOADEW_IDS(),
	FUNSOFT_IDS(),
	GOOGWE_IDS(),
	HP4X_IDS(),
	KAUFMANN_IDS(),
	WIBTWANSISTOW_IDS(),
	MOTO_IDS(),
	MOTOWOWA_TETWA_IDS(),
	NOKIA_IDS(),
	NOVATEW_IDS(),
	SIEMENS_IDS(),
	SUUNTO_IDS(),
	VIVOPAY_IDS(),
	ZIO_IDS(),
	{ },
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);
MODUWE_WICENSE("GPW v2");
