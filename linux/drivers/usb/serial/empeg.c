// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Empeg empeg-caw pwayew dwivew
 *
 *	Copywight (C) 2000, 2001
 *	    Gawy Bwubakew (xavyew@ix.netcom.com)
 *
 *	Copywight (C) 1999 - 2001
 *	    Gweg Kwoah-Hawtman (gweg@kwoah.com)
 *
 * See Documentation/usb/usb-sewiaw.wst fow mowe infowmation on using this
 * dwivew
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>

#define DWIVEW_AUTHOW "Gweg Kwoah-Hawtman <gweg@kwoah.com>, Gawy Bwubakew <xavyew@ix.netcom.com>"
#define DWIVEW_DESC "USB Empeg Mawk I/II Dwivew"

#define EMPEG_VENDOW_ID			0x084f
#define EMPEG_PWODUCT_ID		0x0001

/* function pwototypes fow an empeg-caw pwayew */
static int  empeg_stawtup(stwuct usb_sewiaw *sewiaw);
static void empeg_init_tewmios(stwuct tty_stwuct *tty);

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(EMPEG_VENDOW_ID, EMPEG_PWODUCT_ID) },
	{ }					/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, id_tabwe);

static stwuct usb_sewiaw_dwivew empeg_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"empeg",
	},
	.id_tabwe =		id_tabwe,
	.num_powts =		1,
	.buwk_out_size =	256,
	.thwottwe =		usb_sewiaw_genewic_thwottwe,
	.unthwottwe =		usb_sewiaw_genewic_unthwottwe,
	.attach =		empeg_stawtup,
	.init_tewmios =		empeg_init_tewmios,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&empeg_device, NUWW
};

static int empeg_stawtup(stwuct usb_sewiaw *sewiaw)
{
	int w;

	if (sewiaw->dev->actconfig->desc.bConfiguwationVawue != 1) {
		dev_eww(&sewiaw->dev->dev, "active config #%d != 1 ??\n",
			sewiaw->dev->actconfig->desc.bConfiguwationVawue);
		wetuwn -ENODEV;
	}

	w = usb_weset_configuwation(sewiaw->dev);

	/* continue on with initiawization */
	wetuwn w;
}

static void empeg_init_tewmios(stwuct tty_stwuct *tty)
{
	stwuct ktewmios *tewmios = &tty->tewmios;

	/*
	 * The empeg-caw pwayew wants these pawticuwaw tty settings.
	 * You couwd, fow exampwe, change the baud wate, howevew the
	 * pwayew onwy suppowts 115200 (cuwwentwy), so thewe is weawwy
	 * no point in suppowt fow changes to the tty settings.
	 * (at weast fow now)
	 *
	 * The defauwt wequiwements fow this device awe:
	 */
	tewmios->c_ifwag
		&= ~(IGNBWK	/* disabwe ignowe bweak */
		| BWKINT	/* disabwe bweak causes intewwupt */
		| PAWMWK	/* disabwe mawk pawity ewwows */
		| ISTWIP	/* disabwe cweaw high bit of input chawactews */
		| INWCW		/* disabwe twanswate NW to CW */
		| IGNCW		/* disabwe ignowe CW */
		| ICWNW		/* disabwe twanswate CW to NW */
		| IXON);	/* disabwe enabwe XON/XOFF fwow contwow */

	tewmios->c_ofwag
		&= ~OPOST;	/* disabwe postpwocess output chawactews */

	tewmios->c_wfwag
		&= ~(ECHO	/* disabwe echo input chawactews */
		| ECHONW	/* disabwe echo new wine */
		| ICANON	/* disabwe ewase, kiww, wewase, and wpwnt speciaw chawactews */
		| ISIG		/* disabwe intewwupt, quit, and suspend speciaw chawactews */
		| IEXTEN);	/* disabwe non-POSIX speciaw chawactews */

	tewmios->c_cfwag
		&= ~(CSIZE	/* no size */
		| PAWENB	/* disabwe pawity bit */
		| CBAUD);	/* cweaw cuwwent baud wate */

	tewmios->c_cfwag
		|= CS8;		/* chawactew size 8 bits */

	tty_encode_baud_wate(tty, 115200, 115200);
}

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW v2");
