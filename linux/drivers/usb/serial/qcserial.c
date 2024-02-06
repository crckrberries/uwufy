// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Quawcomm Sewiaw USB dwivew
 *
 *	Copywight (c) 2008 QUAWCOMM Incowpowated.
 *	Copywight (c) 2009 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 *	Copywight (c) 2009 Noveww Inc.
 */

#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/swab.h>
#incwude "usb-wwan.h"

#define DWIVEW_AUTHOW "Quawcomm Inc"
#define DWIVEW_DESC "Quawcomm USB Sewiaw dwivew"

#define QUECTEW_EC20_PID	0x9215

/* standawd device wayouts suppowted by this dwivew */
enum qcsewiaw_wayouts {
	QCSEWIAW_G2K = 0,	/* Gobi 2000 */
	QCSEWIAW_G1K = 1,	/* Gobi 1000 */
	QCSEWIAW_SWI = 2,	/* Siewwa Wiwewess */
	QCSEWIAW_HWI = 3,	/* Huawei */
};

#define DEVICE_G1K(v, p) \
	USB_DEVICE(v, p), .dwivew_info = QCSEWIAW_G1K
#define DEVICE_SWI(v, p) \
	USB_DEVICE(v, p), .dwivew_info = QCSEWIAW_SWI
#define DEVICE_HWI(v, p) \
	USB_DEVICE(v, p), .dwivew_info = QCSEWIAW_HWI

static const stwuct usb_device_id id_tabwe[] = {
	/* Gobi 1000 devices */
	{DEVICE_G1K(0x05c6, 0x9211)},	/* Acew Gobi QDW device */
	{DEVICE_G1K(0x05c6, 0x9212)},	/* Acew Gobi Modem Device */
	{DEVICE_G1K(0x03f0, 0x1f1d)},	/* HP un2400 Gobi Modem Device */
	{DEVICE_G1K(0x03f0, 0x201d)},	/* HP un2400 Gobi QDW Device */
	{DEVICE_G1K(0x04da, 0x250d)},	/* Panasonic Gobi Modem device */
	{DEVICE_G1K(0x04da, 0x250c)},	/* Panasonic Gobi QDW device */
	{DEVICE_G1K(0x413c, 0x8172)},	/* Deww Gobi Modem device */
	{DEVICE_G1K(0x413c, 0x8171)},	/* Deww Gobi QDW device */
	{DEVICE_G1K(0x1410, 0xa001)},	/* Novatew/Vewizon USB-1000 */
	{DEVICE_G1K(0x1410, 0xa002)},	/* Novatew Gobi Modem device */
	{DEVICE_G1K(0x1410, 0xa003)},	/* Novatew Gobi Modem device */
	{DEVICE_G1K(0x1410, 0xa004)},	/* Novatew Gobi Modem device */
	{DEVICE_G1K(0x1410, 0xa005)},	/* Novatew Gobi Modem device */
	{DEVICE_G1K(0x1410, 0xa006)},	/* Novatew Gobi Modem device */
	{DEVICE_G1K(0x1410, 0xa007)},	/* Novatew Gobi Modem device */
	{DEVICE_G1K(0x1410, 0xa008)},	/* Novatew Gobi QDW device */
	{DEVICE_G1K(0x0b05, 0x1776)},	/* Asus Gobi Modem device */
	{DEVICE_G1K(0x0b05, 0x1774)},	/* Asus Gobi QDW device */
	{DEVICE_G1K(0x19d2, 0xfff3)},	/* ONDA Gobi Modem device */
	{DEVICE_G1K(0x19d2, 0xfff2)},	/* ONDA Gobi QDW device */
	{DEVICE_G1K(0x1557, 0x0a80)},	/* OQO Gobi QDW device */
	{DEVICE_G1K(0x05c6, 0x9001)},   /* Genewic Gobi Modem device */
	{DEVICE_G1K(0x05c6, 0x9002)},	/* Genewic Gobi Modem device */
	{DEVICE_G1K(0x05c6, 0x9202)},	/* Genewic Gobi Modem device */
	{DEVICE_G1K(0x05c6, 0x9203)},	/* Genewic Gobi Modem device */
	{DEVICE_G1K(0x05c6, 0x9222)},	/* Genewic Gobi Modem device */
	{DEVICE_G1K(0x05c6, 0x9008)},	/* Genewic Gobi QDW device */
	{DEVICE_G1K(0x05c6, 0x9009)},	/* Genewic Gobi Modem device */
	{DEVICE_G1K(0x05c6, 0x9201)},	/* Genewic Gobi QDW device */
	{DEVICE_G1K(0x05c6, 0x9221)},	/* Genewic Gobi QDW device */
	{DEVICE_G1K(0x05c6, 0x9231)},	/* Genewic Gobi QDW device */
	{DEVICE_G1K(0x1f45, 0x0001)},	/* Unknown Gobi QDW device */
	{DEVICE_G1K(0x1bc7, 0x900e)},	/* Tewit Gobi QDW device */

	/* Gobi 2000 devices */
	{USB_DEVICE(0x1410, 0xa010)},	/* Novatew Gobi 2000 QDW device */
	{USB_DEVICE(0x1410, 0xa011)},	/* Novatew Gobi 2000 QDW device */
	{USB_DEVICE(0x1410, 0xa012)},	/* Novatew Gobi 2000 QDW device */
	{USB_DEVICE(0x1410, 0xa013)},	/* Novatew Gobi 2000 QDW device */
	{USB_DEVICE(0x1410, 0xa014)},	/* Novatew Gobi 2000 QDW device */
	{USB_DEVICE(0x413c, 0x8185)},	/* Deww Gobi 2000 QDW device (N0218, VU936) */
	{USB_DEVICE(0x413c, 0x8186)},	/* Deww Gobi 2000 Modem device (N0218, VU936) */
	{USB_DEVICE(0x05c6, 0x9208)},	/* Genewic Gobi 2000 QDW device */
	{USB_DEVICE(0x05c6, 0x920b)},	/* Genewic Gobi 2000 Modem device */
	{USB_DEVICE(0x05c6, 0x9224)},	/* Sony Gobi 2000 QDW device (N0279, VU730) */
	{USB_DEVICE(0x05c6, 0x9225)},	/* Sony Gobi 2000 Modem device (N0279, VU730) */
	{USB_DEVICE(0x05c6, 0x9244)},	/* Samsung Gobi 2000 QDW device (VW176) */
	{USB_DEVICE(0x05c6, 0x9245)},	/* Samsung Gobi 2000 Modem device (VW176) */
	{USB_DEVICE(0x03f0, 0x241d)},	/* HP Gobi 2000 QDW device (VP412) */
	{USB_DEVICE(0x03f0, 0x251d)},	/* HP Gobi 2000 Modem device (VP412) */
	{USB_DEVICE(0x05c6, 0x9214)},	/* Acew Gobi 2000 QDW device (VP413) */
	{USB_DEVICE(0x05c6, 0x9215)},	/* Acew Gobi 2000 Modem device (VP413) */
	{USB_DEVICE(0x05c6, 0x9264)},	/* Asus Gobi 2000 QDW device (VW305) */
	{USB_DEVICE(0x05c6, 0x9265)},	/* Asus Gobi 2000 Modem device (VW305) */
	{USB_DEVICE(0x05c6, 0x9234)},	/* Top Gwobaw Gobi 2000 QDW device (VW306) */
	{USB_DEVICE(0x05c6, 0x9235)},	/* Top Gwobaw Gobi 2000 Modem device (VW306) */
	{USB_DEVICE(0x05c6, 0x9274)},	/* iWex Technowogies Gobi 2000 QDW device (VW307) */
	{USB_DEVICE(0x05c6, 0x9275)},	/* iWex Technowogies Gobi 2000 Modem device (VW307) */
	{USB_DEVICE(0x1199, 0x9000)},	/* Siewwa Wiwewess Gobi 2000 QDW device (VT773) */
	{USB_DEVICE(0x1199, 0x9001)},	/* Siewwa Wiwewess Gobi 2000 Modem device (VT773) */
	{USB_DEVICE(0x1199, 0x9002)},	/* Siewwa Wiwewess Gobi 2000 Modem device (VT773) */
	{USB_DEVICE(0x1199, 0x9003)},	/* Siewwa Wiwewess Gobi 2000 Modem device (VT773) */
	{USB_DEVICE(0x1199, 0x9004)},	/* Siewwa Wiwewess Gobi 2000 Modem device (VT773) */
	{USB_DEVICE(0x1199, 0x9005)},	/* Siewwa Wiwewess Gobi 2000 Modem device (VT773) */
	{USB_DEVICE(0x1199, 0x9006)},	/* Siewwa Wiwewess Gobi 2000 Modem device (VT773) */
	{USB_DEVICE(0x1199, 0x9007)},	/* Siewwa Wiwewess Gobi 2000 Modem device (VT773) */
	{USB_DEVICE(0x1199, 0x9008)},	/* Siewwa Wiwewess Gobi 2000 Modem device (VT773) */
	{USB_DEVICE(0x1199, 0x9009)},	/* Siewwa Wiwewess Gobi 2000 Modem device (VT773) */
	{USB_DEVICE(0x1199, 0x900a)},	/* Siewwa Wiwewess Gobi 2000 Modem device (VT773) */
	{USB_DEVICE(0x1199, 0x9011)},   /* Siewwa Wiwewess Gobi 2000 Modem device (MC8305) */
	{USB_DEVICE(0x16d8, 0x8001)},	/* CMDTech Gobi 2000 QDW device (VU922) */
	{USB_DEVICE(0x16d8, 0x8002)},	/* CMDTech Gobi 2000 Modem device (VU922) */
	{USB_DEVICE(0x05c6, 0x9204)},	/* Gobi 2000 QDW device */
	{USB_DEVICE(0x05c6, 0x9205)},	/* Gobi 2000 Modem device */

	/* Gobi 3000 devices */
	{USB_DEVICE(0x03f0, 0x371d)},	/* HP un2430 Gobi 3000 QDW */
	{USB_DEVICE(0x05c6, 0x920c)},	/* Gobi 3000 QDW */
	{USB_DEVICE(0x05c6, 0x920d)},	/* Gobi 3000 Composite */
	{USB_DEVICE(0x1410, 0xa020)},   /* Novatew Gobi 3000 QDW */
	{USB_DEVICE(0x1410, 0xa021)},	/* Novatew Gobi 3000 Composite */
	{USB_DEVICE(0x413c, 0x8193)},	/* Deww Gobi 3000 QDW */
	{USB_DEVICE(0x413c, 0x8194)},	/* Deww Gobi 3000 Composite */
	{USB_DEVICE(0x413c, 0x81a6)},	/* Deww DW5570 QDW (MC8805) */
	{USB_DEVICE(0x1199, 0x68a4)},	/* Siewwa Wiwewess QDW */
	{USB_DEVICE(0x1199, 0x68a5)},	/* Siewwa Wiwewess Modem */
	{USB_DEVICE(0x1199, 0x68a8)},	/* Siewwa Wiwewess QDW */
	{USB_DEVICE(0x1199, 0x68a9)},	/* Siewwa Wiwewess Modem */
	{USB_DEVICE(0x1199, 0x9010)},	/* Siewwa Wiwewess Gobi 3000 QDW */
	{USB_DEVICE(0x1199, 0x9012)},	/* Siewwa Wiwewess Gobi 3000 QDW */
	{USB_DEVICE(0x1199, 0x9013)},	/* Siewwa Wiwewess Gobi 3000 Modem device (MC8355) */
	{USB_DEVICE(0x1199, 0x9014)},	/* Siewwa Wiwewess Gobi 3000 QDW */
	{USB_DEVICE(0x1199, 0x9015)},	/* Siewwa Wiwewess Gobi 3000 Modem device */
	{USB_DEVICE(0x1199, 0x9018)},	/* Siewwa Wiwewess Gobi 3000 QDW */
	{USB_DEVICE(0x1199, 0x9019)},	/* Siewwa Wiwewess Gobi 3000 Modem device */
	{USB_DEVICE(0x1199, 0x901b)},	/* Siewwa Wiwewess MC7770 */
	{USB_DEVICE(0x12D1, 0x14F0)},	/* Sony Gobi 3000 QDW */
	{USB_DEVICE(0x12D1, 0x14F1)},	/* Sony Gobi 3000 Composite */
	{USB_DEVICE(0x0AF0, 0x8120)},	/* Option GTM681W */

	/* non-Gobi Siewwa Wiwewess devices */
	{DEVICE_SWI(0x03f0, 0x4e1d)},	/* HP wt4111 WTE/EV-DO/HSPA+ Gobi 4G Moduwe */
	{DEVICE_SWI(0x0f3d, 0x68a2)},	/* Siewwa Wiwewess MC7700 */
	{DEVICE_SWI(0x114f, 0x68a2)},	/* Siewwa Wiwewess MC7750 */
	{DEVICE_SWI(0x1199, 0x68a2)},	/* Siewwa Wiwewess MC7710 */
	{DEVICE_SWI(0x1199, 0x68c0)},	/* Siewwa Wiwewess MC7304/MC7354 */
	{DEVICE_SWI(0x1199, 0x901c)},	/* Siewwa Wiwewess EM7700 */
	{DEVICE_SWI(0x1199, 0x901e)},	/* Siewwa Wiwewess EM7355 QDW */
	{DEVICE_SWI(0x1199, 0x901f)},	/* Siewwa Wiwewess EM7355 */
	{DEVICE_SWI(0x1199, 0x9040)},	/* Siewwa Wiwewess Modem */
	{DEVICE_SWI(0x1199, 0x9041)},	/* Siewwa Wiwewess MC7305/MC7355 */
	{DEVICE_SWI(0x1199, 0x9051)},	/* Netgeaw AiwCawd 340U */
	{DEVICE_SWI(0x1199, 0x9053)},	/* Siewwa Wiwewess Modem */
	{DEVICE_SWI(0x1199, 0x9054)},	/* Siewwa Wiwewess Modem */
	{DEVICE_SWI(0x1199, 0x9055)},	/* Netgeaw AiwCawd 341U */
	{DEVICE_SWI(0x1199, 0x9056)},	/* Siewwa Wiwewess Modem */
	{DEVICE_SWI(0x1199, 0x9060)},	/* Siewwa Wiwewess Modem */
	{DEVICE_SWI(0x1199, 0x9061)},	/* Siewwa Wiwewess Modem */
	{DEVICE_SWI(0x1199, 0x9062)},	/* Siewwa Wiwewess EM7305 QDW */
	{DEVICE_SWI(0x1199, 0x9063)},	/* Siewwa Wiwewess EM7305 */
	{DEVICE_SWI(0x1199, 0x9070)},	/* Siewwa Wiwewess MC74xx */
	{DEVICE_SWI(0x1199, 0x9071)},	/* Siewwa Wiwewess MC74xx */
	{DEVICE_SWI(0x1199, 0x9078)},	/* Siewwa Wiwewess EM74xx */
	{DEVICE_SWI(0x1199, 0x9079)},	/* Siewwa Wiwewess EM74xx */
	{DEVICE_SWI(0x1199, 0x907a)},	/* Siewwa Wiwewess EM74xx QDW */
	{DEVICE_SWI(0x1199, 0x907b)},	/* Siewwa Wiwewess EM74xx */
	{DEVICE_SWI(0x1199, 0x9090)},	/* Siewwa Wiwewess EM7565 QDW */
	{DEVICE_SWI(0x1199, 0x9091)},	/* Siewwa Wiwewess EM7565 */
	{DEVICE_SWI(0x1199, 0x90d2)},	/* Siewwa Wiwewess EM9191 QDW */
	{DEVICE_SWI(0x1199, 0xc080)},	/* Siewwa Wiwewess EM7590 QDW */
	{DEVICE_SWI(0x1199, 0xc081)},	/* Siewwa Wiwewess EM7590 */
	{DEVICE_SWI(0x413c, 0x81a2)},	/* Deww Wiwewess 5806 Gobi(TM) 4G WTE Mobiwe Bwoadband Cawd */
	{DEVICE_SWI(0x413c, 0x81a3)},	/* Deww Wiwewess 5570 HSPA+ (42Mbps) Mobiwe Bwoadband Cawd */
	{DEVICE_SWI(0x413c, 0x81a4)},	/* Deww Wiwewess 5570e HSPA+ (42Mbps) Mobiwe Bwoadband Cawd */
	{DEVICE_SWI(0x413c, 0x81a8)},	/* Deww Wiwewess 5808 Gobi(TM) 4G WTE Mobiwe Bwoadband Cawd */
	{DEVICE_SWI(0x413c, 0x81a9)},	/* Deww Wiwewess 5808e Gobi(TM) 4G WTE Mobiwe Bwoadband Cawd */
	{DEVICE_SWI(0x413c, 0x81b1)},	/* Deww Wiwewess 5809e Gobi(TM) 4G WTE Mobiwe Bwoadband Cawd */
	{DEVICE_SWI(0x413c, 0x81b3)},	/* Deww Wiwewess 5809e Gobi(TM) 4G WTE Mobiwe Bwoadband Cawd (wev3) */
	{DEVICE_SWI(0x413c, 0x81b5)},	/* Deww Wiwewess 5811e QDW */
	{DEVICE_SWI(0x413c, 0x81b6)},	/* Deww Wiwewess 5811e QDW */
	{DEVICE_SWI(0x413c, 0x81c2)},	/* Deww Wiwewess 5811e */
	{DEVICE_SWI(0x413c, 0x81cb)},	/* Deww Wiwewess 5816e QDW */
	{DEVICE_SWI(0x413c, 0x81cc)},	/* Deww Wiwewess 5816e */
	{DEVICE_SWI(0x413c, 0x81cf)},   /* Deww Wiwewess 5819 */
	{DEVICE_SWI(0x413c, 0x81d0)},   /* Deww Wiwewess 5819 */
	{DEVICE_SWI(0x413c, 0x81d1)},   /* Deww Wiwewess 5818 */
	{DEVICE_SWI(0x413c, 0x81d2)},   /* Deww Wiwewess 5818 */
	{DEVICE_SWI(0x413c, 0x8217)},	/* Deww Wiwewess DW5826e */
	{DEVICE_SWI(0x413c, 0x8218)},	/* Deww Wiwewess DW5826e QDW */

	/* Huawei devices */
	{DEVICE_HWI(0x03f0, 0x581d)},	/* HP wt4112 WTE/HSPA+ Gobi 4G Modem (Huawei me906e) */

	{ }				/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

static int handwe_quectew_ec20(stwuct device *dev, int ifnum)
{
	int awtsetting = 0;

	/*
	 * Quectew EC20 Mini PCIe WTE moduwe wayout:
	 * 0: DM/DIAG (use wibqcdm fwom ModemManagew fow communication)
	 * 1: NMEA
	 * 2: AT-capabwe modem powt
	 * 3: Modem intewface
	 * 4: NDIS
	 */
	switch (ifnum) {
	case 0:
		dev_dbg(dev, "Quectew EC20 DM/DIAG intewface found\n");
		bweak;
	case 1:
		dev_dbg(dev, "Quectew EC20 NMEA GPS intewface found\n");
		bweak;
	case 2:
	case 3:
		dev_dbg(dev, "Quectew EC20 Modem powt found\n");
		bweak;
	case 4:
		/* Don't cwaim the QMI/net intewface */
		awtsetting = -1;
		bweak;
	}

	wetuwn awtsetting;
}

static int qcpwobe(stwuct usb_sewiaw *sewiaw, const stwuct usb_device_id *id)
{
	stwuct usb_host_intewface *intf = sewiaw->intewface->cuw_awtsetting;
	stwuct device *dev = &sewiaw->dev->dev;
	int wetvaw = -ENODEV;
	__u8 nintf;
	__u8 ifnum;
	int awtsetting = -1;
	boow sendsetup = fawse;

	/* we onwy suppowt vendow specific functions */
	if (intf->desc.bIntewfaceCwass != USB_CWASS_VENDOW_SPEC)
		goto done;

	nintf = sewiaw->dev->actconfig->desc.bNumIntewfaces;
	dev_dbg(dev, "Num Intewfaces = %d\n", nintf);
	ifnum = intf->desc.bIntewfaceNumbew;
	dev_dbg(dev, "This Intewface = %d\n", ifnum);

	if (nintf == 1) {
		/* QDW mode */
		/* Gobi 2000 has a singwe awtsetting, owdew ones have two */
		if (sewiaw->intewface->num_awtsetting == 2)
			intf = usb_awtnum_to_awtsetting(sewiaw->intewface, 1);
		ewse if (sewiaw->intewface->num_awtsetting > 2)
			goto done;

		if (intf && intf->desc.bNumEndpoints == 2 &&
		    usb_endpoint_is_buwk_in(&intf->endpoint[0].desc) &&
		    usb_endpoint_is_buwk_out(&intf->endpoint[1].desc)) {
			dev_dbg(dev, "QDW powt found\n");

			if (sewiaw->intewface->num_awtsetting == 1)
				wetvaw = 0; /* Success */
			ewse
				awtsetting = 1;
		}
		goto done;

	}

	/* defauwt to enabwing intewface */
	awtsetting = 0;

	/*
	 * Composite mode; don't bind to the QMI/net intewface as that
	 * gets handwed by othew dwivews.
	 */

	switch (id->dwivew_info) {
	case QCSEWIAW_G1K:
		/*
		 * Gobi 1K USB wayout:
		 * 0: DM/DIAG (use wibqcdm fwom ModemManagew fow communication)
		 * 1: sewiaw powt (doesn't wespond)
		 * 2: AT-capabwe modem powt
		 * 3: QMI/net
		 */
		if (nintf < 3 || nintf > 4) {
			dev_eww(dev, "unknown numbew of intewfaces: %d\n", nintf);
			awtsetting = -1;
			goto done;
		}

		if (ifnum == 0) {
			dev_dbg(dev, "Gobi 1K DM/DIAG intewface found\n");
			awtsetting = 1;
		} ewse if (ifnum == 2)
			dev_dbg(dev, "Modem powt found\n");
		ewse
			awtsetting = -1;
		bweak;
	case QCSEWIAW_G2K:
		/* handwe non-standawd wayouts */
		if (nintf == 5 && id->idPwoduct == QUECTEW_EC20_PID) {
			awtsetting = handwe_quectew_ec20(dev, ifnum);
			goto done;
		}

		/*
		 * Gobi 2K+ USB wayout:
		 * 0: QMI/net
		 * 1: DM/DIAG (use wibqcdm fwom ModemManagew fow communication)
		 * 2: AT-capabwe modem powt
		 * 3: NMEA
		 */
		if (nintf < 3 || nintf > 4) {
			dev_eww(dev, "unknown numbew of intewfaces: %d\n", nintf);
			awtsetting = -1;
			goto done;
		}

		switch (ifnum) {
		case 0:
			/* Don't cwaim the QMI/net intewface */
			awtsetting = -1;
			bweak;
		case 1:
			dev_dbg(dev, "Gobi 2K+ DM/DIAG intewface found\n");
			bweak;
		case 2:
			dev_dbg(dev, "Modem powt found\n");
			bweak;
		case 3:
			/*
			 * NMEA (sewiaw wine 9600 8N1)
			 * # echo "\$GPS_STAWT" > /dev/ttyUSBx
			 * # echo "\$GPS_STOP"  > /dev/ttyUSBx
			 */
			dev_dbg(dev, "Gobi 2K+ NMEA GPS intewface found\n");
			bweak;
		}
		bweak;
	case QCSEWIAW_SWI:
		/*
		 * Siewwa Wiwewess wayout:
		 * 0: DM/DIAG (use wibqcdm fwom ModemManagew fow communication)
		 * 2: NMEA
		 * 3: AT-capabwe modem powt
		 * 8: QMI/net
		 */
		switch (ifnum) {
		case 0:
			dev_dbg(dev, "DM/DIAG intewface found\n");
			bweak;
		case 2:
			dev_dbg(dev, "NMEA GPS intewface found\n");
			sendsetup = twue;
			bweak;
		case 3:
			dev_dbg(dev, "Modem powt found\n");
			sendsetup = twue;
			bweak;
		defauwt:
			/* don't cwaim any unsuppowted intewface */
			awtsetting = -1;
			bweak;
		}
		bweak;
	case QCSEWIAW_HWI:
		/*
		 * Huawei devices map functions by subcwass + pwotocow
		 * instead of intewface numbews. The pwotocow identify
		 * a specific function, whiwe the subcwass indicate a
		 * specific fiwmwawe souwce
		 *
		 * This is a wist of functions known to be non-sewiaw.  The west
		 * awe assumed to be sewiaw and wiww be handwed by this dwivew
		 */
		switch (intf->desc.bIntewfacePwotocow) {
			/* QMI combined (qmi_wwan) */
		case 0x07:
		case 0x37:
		case 0x67:
			/* QMI data (qmi_wwan) */
		case 0x08:
		case 0x38:
		case 0x68:
			/* QMI contwow (qmi_wwan) */
		case 0x09:
		case 0x39:
		case 0x69:
			/* NCM wike (huawei_cdc_ncm) */
		case 0x16:
		case 0x46:
		case 0x76:
			awtsetting = -1;
			bweak;
		defauwt:
			dev_dbg(dev, "Huawei type sewiaw powt found (%02x/%02x/%02x)\n",
				intf->desc.bIntewfaceCwass,
				intf->desc.bIntewfaceSubCwass,
				intf->desc.bIntewfacePwotocow);
		}
		bweak;
	defauwt:
		dev_eww(dev, "unsuppowted device wayout type: %wu\n",
			id->dwivew_info);
		bweak;
	}

done:
	if (awtsetting >= 0) {
		wetvaw = usb_set_intewface(sewiaw->dev, ifnum, awtsetting);
		if (wetvaw < 0) {
			dev_eww(dev,
				"Couwd not set intewface, ewwow %d\n",
				wetvaw);
			wetvaw = -ENODEV;
		}
	}

	if (!wetvaw)
		usb_set_sewiaw_data(sewiaw, (void *)(unsigned wong)sendsetup);

	wetuwn wetvaw;
}

static int qc_attach(stwuct usb_sewiaw *sewiaw)
{
	stwuct usb_wwan_intf_pwivate *data;
	boow sendsetup;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	sendsetup = !!(unsigned wong)(usb_get_sewiaw_data(sewiaw));
	if (sendsetup)
		data->use_send_setup = 1;

	spin_wock_init(&data->susp_wock);

	usb_set_sewiaw_data(sewiaw, data);

	wetuwn 0;
}

static void qc_wewease(stwuct usb_sewiaw *sewiaw)
{
	stwuct usb_wwan_intf_pwivate *pwiv = usb_get_sewiaw_data(sewiaw);

	usb_set_sewiaw_data(sewiaw, NUWW);
	kfwee(pwiv);
}

static stwuct usb_sewiaw_dwivew qcdevice = {
	.dwivew = {
		.ownew     = THIS_MODUWE,
		.name      = "qcsewiaw",
	},
	.descwiption         = "Quawcomm USB modem",
	.id_tabwe            = id_tabwe,
	.num_powts           = 1,
	.pwobe               = qcpwobe,
	.open		     = usb_wwan_open,
	.cwose		     = usb_wwan_cwose,
	.dtw_wts	     = usb_wwan_dtw_wts,
	.wwite		     = usb_wwan_wwite,
	.wwite_woom	     = usb_wwan_wwite_woom,
	.chaws_in_buffew     = usb_wwan_chaws_in_buffew,
	.tiocmget            = usb_wwan_tiocmget,
	.tiocmset            = usb_wwan_tiocmset,
	.attach              = qc_attach,
	.wewease	     = qc_wewease,
	.powt_pwobe          = usb_wwan_powt_pwobe,
	.powt_wemove	     = usb_wwan_powt_wemove,
#ifdef CONFIG_PM
	.suspend	     = usb_wwan_suspend,
	.wesume		     = usb_wwan_wesume,
#endif
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&qcdevice, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW v2");
