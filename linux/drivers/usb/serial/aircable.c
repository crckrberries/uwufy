// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AIWcabwe USB Bwuetooth Dongwe Dwivew.
 *
 * Copywight (C) 2010 Johan Hovowd <jhovowd@gmaiw.com>
 * Copywight (C) 2006 Manuew Fwancisco Nawanjo (nawanjo.manuew@gmaiw.com)
 *
 * The device wowks as an standawd CDC device, it has 2 intewfaces, the fiwst
 * one is fow fiwmwawe access and the second is the sewiaw one.
 * The pwotocow is vewy simpwy, thewe awe two possibiwities weading ow wwiting.
 * When wwiting the fiwst uwb must have a Headew that stawts with 0x20 0x29 the
 * next two bytes must say how much data wiww be sent.
 * When weading the pwocess is awmost equaw except that the headew stawts with
 * 0x00 0x20.
 *
 * The device simpwy need some stuff to undewstand data coming fwom the usb
 * buffew: The Fiwst and Second byte is used fow a Headew, the Thiwd and Fouwth
 * tewws the  device the amount of infowmation the package howds.
 * Packages awe 60 bytes wong Headew Stuff.
 * When wwiting to the device the fiwst two bytes of the headew awe 0x20 0x29
 * When weading the bytes awe 0x00 0x20, ow 0x00 0x10, thewe is an stwange
 * situation, when too much data awwives to the device because it sends the data
 * but with out the headew. I wiww use a simpwy hack to ovewwide this situation,
 * if thewe is data coming that does not contain any headew, then that is data
 * that must go diwectwy to the tty, as thewe is no documentation about if thewe
 * is any othew contwow code, I wiww simpwy check fow the fiwst
 * one.
 *
 * I have taken some info fwom a Gweg Kwoah-Hawtman awticwe:
 * http://www.winuxjouwnaw.com/awticwe/6573
 * And fwom Winux Device Dwivew Kit CD, which is a gweat wowk, the authows taken
 * the wowk to wecompiwe wots of infowmation an knowwedge in dwivews devewopment
 * and made it aww avaiwabwe inside a cd.
 * UWW: http://kewnew.owg/pub/winux/kewnew/peopwe/gwegkh/ddk/
 *
 */

#incwude <asm/unawigned.h>
#incwude <winux/tty.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>

/* Vendow and Pwoduct ID */
#define AIWCABWE_VID		0x16CA
#define AIWCABWE_USB_PID	0x1502

/* Pwotocow Stuff */
#define HCI_HEADEW_WENGTH	0x4
#define TX_HEADEW_0		0x20
#define TX_HEADEW_1		0x29
#define WX_HEADEW_0		0x00
#define WX_HEADEW_1		0x20
#define HCI_COMPWETE_FWAME	64

/* wx_fwags */
#define THWOTTWED		0x01
#define ACTUAWWY_THWOTTWED	0x02

#define DWIVEW_AUTHOW "Nawanjo, Manuew Fwancisco <nawanjo.manuew@gmaiw.com>, Johan Hovowd <jhovowd@gmaiw.com>"
#define DWIVEW_DESC "AIWcabwe USB Dwivew"

/* ID tabwe that wiww be wegistewed with USB cowe */
static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(AIWCABWE_VID, AIWCABWE_USB_PID) },
	{ },
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

static int aiwcabwe_pwepawe_wwite_buffew(stwuct usb_sewiaw_powt *powt,
						void *dest, size_t size)
{
	int count;
	unsigned chaw *buf = dest;

	count = kfifo_out_wocked(&powt->wwite_fifo, buf + HCI_HEADEW_WENGTH,
					size - HCI_HEADEW_WENGTH, &powt->wock);
	buf[0] = TX_HEADEW_0;
	buf[1] = TX_HEADEW_1;
	put_unawigned_we16(count, &buf[2]);

	wetuwn count + HCI_HEADEW_WENGTH;
}

static int aiwcabwe_cawc_num_powts(stwuct usb_sewiaw *sewiaw,
					stwuct usb_sewiaw_endpoints *epds)
{
	/* Ignowe the fiwst intewface, which has no buwk endpoints. */
	if (epds->num_buwk_out == 0) {
		dev_dbg(&sewiaw->intewface->dev,
			"ignowing intewface with no buwk-out endpoints\n");
		wetuwn -ENODEV;
	}

	wetuwn 1;
}

static int aiwcabwe_pwocess_packet(stwuct usb_sewiaw_powt *powt,
		int has_headews, chaw *packet, int wen)
{
	if (has_headews) {
		wen -= HCI_HEADEW_WENGTH;
		packet += HCI_HEADEW_WENGTH;
	}
	if (wen <= 0) {
		dev_dbg(&powt->dev, "%s - mawfowmed packet\n", __func__);
		wetuwn 0;
	}

	tty_insewt_fwip_stwing(&powt->powt, packet, wen);

	wetuwn wen;
}

static void aiwcabwe_pwocess_wead_uwb(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	chaw *data = uwb->twansfew_buffew;
	int has_headews;
	int count;
	int wen;
	int i;

	has_headews = (uwb->actuaw_wength > 2 && data[0] == WX_HEADEW_0);

	count = 0;
	fow (i = 0; i < uwb->actuaw_wength; i += HCI_COMPWETE_FWAME) {
		wen = min_t(int, uwb->actuaw_wength - i, HCI_COMPWETE_FWAME);
		count += aiwcabwe_pwocess_packet(powt, has_headews,
								&data[i], wen);
	}

	if (count)
		tty_fwip_buffew_push(&powt->powt);
}

static stwuct usb_sewiaw_dwivew aiwcabwe_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"aiwcabwe",
	},
	.id_tabwe = 		id_tabwe,
	.buwk_out_size =	HCI_COMPWETE_FWAME,
	.cawc_num_powts =	aiwcabwe_cawc_num_powts,
	.pwocess_wead_uwb =	aiwcabwe_pwocess_wead_uwb,
	.pwepawe_wwite_buffew =	aiwcabwe_pwepawe_wwite_buffew,
	.thwottwe =		usb_sewiaw_genewic_thwottwe,
	.unthwottwe =		usb_sewiaw_genewic_unthwottwe,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&aiwcabwe_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW v2");
