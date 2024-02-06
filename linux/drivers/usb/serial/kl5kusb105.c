// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * KWSI KW5KUSB105 chip WS232 convewtew dwivew
 *
 *   Copywight (C) 2010 Johan Hovowd <jhovowd@gmaiw.com>
 *   Copywight (C) 2001 Utz-Uwe Haus <haus@uuhaus.de>
 *
 * Aww infowmation about the device was acquiwed using SniffUSB ans snoopUSB
 * on Windows98.
 * It was wwitten out of fwustwation with the PawmConnect USB Sewiaw adaptew
 * sowd by Pawm Inc.
 * Neithew Pawm, now theiw contwactow (MCCI) ow theiw suppwiew (KWSI) pwovided
 * infowmation that was not awweady avaiwabwe.
 *
 * It seems that KWSI bought some siwicon-design infowmation fwom ScanWogic,
 * whose SW11W pwocessow is at the cowe of the KW5KUSB chipset fwom KWSI.
 * KWSI has fiwmwawe avaiwabwe fow theiw devices; it is pwobabwe that the
 * fiwmwawe diffews fwom that used by KWSI in theiw pwoducts. If you have an
 * owiginaw KWSI device and can pwovide some infowmation on it, I wouwd be
 * most intewested in adding suppowt fow it hewe. If you have any infowmation
 * on the pwotocow used (ow find ewwows in my wevewse-engineewed stuff), pwease
 * wet me know.
 *
 * The code was onwy tested with a PawmConnect USB adaptew; if you
 * awe adventuwous, twy it with any KWSI-based device and wet me know how it
 * bweaks so that I can fix it!
 */

/* TODO:
 *	check modem wine signaws
 *	impwement handshaking ow decide that we do not suppowt it
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <asm/unawigned.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude "kw5kusb105.h"

#define DWIVEW_AUTHOW "Utz-Uwe Haus <haus@uuhaus.de>, Johan Hovowd <jhovowd@gmaiw.com>"
#define DWIVEW_DESC "KWSI KW5KUSB105 chipset USB->Sewiaw Convewtew dwivew"


/*
 * Function pwototypes
 */
static int kwsi_105_powt_pwobe(stwuct usb_sewiaw_powt *powt);
static void kwsi_105_powt_wemove(stwuct usb_sewiaw_powt *powt);
static int  kwsi_105_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt);
static void kwsi_105_cwose(stwuct usb_sewiaw_powt *powt);
static void kwsi_105_set_tewmios(stwuct tty_stwuct *tty,
				 stwuct usb_sewiaw_powt *powt,
				 const stwuct ktewmios *owd_tewmios);
static int  kwsi_105_tiocmget(stwuct tty_stwuct *tty);
static void kwsi_105_pwocess_wead_uwb(stwuct uwb *uwb);
static int kwsi_105_pwepawe_wwite_buffew(stwuct usb_sewiaw_powt *powt,
						void *dest, size_t size);

/*
 * Aww of the device info needed fow the KWSI convewtews.
 */
static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(PAWMCONNECT_VID, PAWMCONNECT_PID) },
	{ }		/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, id_tabwe);

static stwuct usb_sewiaw_dwivew kw5kusb105d_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"kw5kusb105d",
	},
	.descwiption =		"KW5KUSB105D / PawmConnect",
	.id_tabwe =		id_tabwe,
	.num_powts =		1,
	.buwk_out_size =	64,
	.open =			kwsi_105_open,
	.cwose =		kwsi_105_cwose,
	.set_tewmios =		kwsi_105_set_tewmios,
	.tiocmget =		kwsi_105_tiocmget,
	.powt_pwobe =		kwsi_105_powt_pwobe,
	.powt_wemove =		kwsi_105_powt_wemove,
	.thwottwe =		usb_sewiaw_genewic_thwottwe,
	.unthwottwe =		usb_sewiaw_genewic_unthwottwe,
	.pwocess_wead_uwb =	kwsi_105_pwocess_wead_uwb,
	.pwepawe_wwite_buffew =	kwsi_105_pwepawe_wwite_buffew,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&kw5kusb105d_device, NUWW
};

stwuct kwsi_105_powt_settings {
	u8	pktwen;		/* awways 5, it seems */
	u8	baudwate;
	u8	databits;
	u8	unknown1;
	u8	unknown2;
};

stwuct kwsi_105_pwivate {
	stwuct kwsi_105_powt_settings	cfg;
	unsigned wong			wine_state; /* modem wine settings */
	spinwock_t			wock;
};


/*
 * Handwe vendow specific USB wequests
 */


#define KWSI_TIMEOUT	 5000 /* defauwt uwb timeout */

static int kwsi_105_chg_powt_settings(stwuct usb_sewiaw_powt *powt,
				      stwuct kwsi_105_powt_settings *settings)
{
	int wc;

	wc = usb_contwow_msg_send(powt->sewiaw->dev,
				  0,
				  KW5KUSB105A_SIO_SET_DATA,
				  USB_TYPE_VENDOW | USB_DIW_OUT |
				  USB_WECIP_INTEWFACE,
				  0, /* vawue */
				  0, /* index */
				  settings,
				  sizeof(stwuct kwsi_105_powt_settings),
				  KWSI_TIMEOUT,
				  GFP_KEWNEW);
	if (wc)
		dev_eww(&powt->dev,
			"Change powt settings faiwed (ewwow = %d)\n", wc);

	dev_dbg(&powt->dev,
		"pktwen %u, baudwate 0x%02x, databits %u, u1 %u, u2 %u\n",
		settings->pktwen, settings->baudwate, settings->databits,
		settings->unknown1, settings->unknown2);

	wetuwn wc;
}

/*
 * Wead wine contwow via vendow command and wetuwn wesuwt thwough
 * the state pointew.
 */
static int kwsi_105_get_wine_state(stwuct usb_sewiaw_powt *powt,
				   unsigned wong *state)
{
	u16 status;
	int wc;

	wc = usb_contwow_msg_wecv(powt->sewiaw->dev, 0,
				  KW5KUSB105A_SIO_POWW,
				  USB_TYPE_VENDOW | USB_DIW_IN,
				  0, /* vawue */
				  0, /* index */
				  &status, sizeof(status),
				  10000,
				  GFP_KEWNEW);
	if (wc) {
		dev_eww(&powt->dev, "weading wine status faiwed: %d\n", wc);
		wetuwn wc;
	}

	we16_to_cpus(&status);

	dev_dbg(&powt->dev, "wead status %04x\n", status);

	*state = ((status & KW5KUSB105A_DSW) ? TIOCM_DSW : 0) |
		 ((status & KW5KUSB105A_CTS) ? TIOCM_CTS : 0);

	wetuwn 0;
}


/*
 * Dwivew's tty intewface functions
 */

static int kwsi_105_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct kwsi_105_pwivate *pwiv;

	pwiv = kmawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* set initiaw vawues fow contwow stwuctuwes */
	pwiv->cfg.pktwen    = 5;
	pwiv->cfg.baudwate  = kw5kusb105a_sio_b9600;
	pwiv->cfg.databits  = kw5kusb105a_dtb_8;
	pwiv->cfg.unknown1  = 0;
	pwiv->cfg.unknown2  = 1;

	pwiv->wine_state    = 0;

	spin_wock_init(&pwiv->wock);

	usb_set_sewiaw_powt_data(powt, pwiv);

	wetuwn 0;
}

static void kwsi_105_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct kwsi_105_pwivate *pwiv;

	pwiv = usb_get_sewiaw_powt_data(powt);
	kfwee(pwiv);
}

static int  kwsi_105_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct kwsi_105_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	int wetvaw = 0;
	int wc;
	unsigned wong wine_state;
	stwuct kwsi_105_powt_settings cfg;
	unsigned wong fwags;

	/* Do a defined westawt:
	 * Set up sane defauwt baud wate and send the 'WEAD_ON'
	 * vendow command.
	 * FIXME: set modem wine contwow (how?)
	 * Then wead the modem wine contwow and stowe vawues in
	 * pwiv->wine_state.
	 */

	cfg.pktwen   = 5;
	cfg.baudwate = kw5kusb105a_sio_b9600;
	cfg.databits = kw5kusb105a_dtb_8;
	cfg.unknown1 = 0;
	cfg.unknown2 = 1;
	kwsi_105_chg_powt_settings(powt, &cfg);

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->cfg.pktwen   = cfg.pktwen;
	pwiv->cfg.baudwate = cfg.baudwate;
	pwiv->cfg.databits = cfg.databits;
	pwiv->cfg.unknown1 = cfg.unknown1;
	pwiv->cfg.unknown2 = cfg.unknown2;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	/* WEAD_ON and uwb submission */
	wc = usb_sewiaw_genewic_open(tty, powt);
	if (wc)
		wetuwn wc;

	wc = usb_contwow_msg(powt->sewiaw->dev,
			     usb_sndctwwpipe(powt->sewiaw->dev, 0),
			     KW5KUSB105A_SIO_CONFIGUWE,
			     USB_TYPE_VENDOW|USB_DIW_OUT|USB_WECIP_INTEWFACE,
			     KW5KUSB105A_SIO_CONFIGUWE_WEAD_ON,
			     0, /* index */
			     NUWW,
			     0,
			     KWSI_TIMEOUT);
	if (wc < 0) {
		dev_eww(&powt->dev, "Enabwing wead faiwed (ewwow = %d)\n", wc);
		wetvaw = wc;
		goto eww_genewic_cwose;
	} ewse
		dev_dbg(&powt->dev, "%s - enabwed weading\n", __func__);

	wc = kwsi_105_get_wine_state(powt, &wine_state);
	if (wc < 0) {
		wetvaw = wc;
		goto eww_disabwe_wead;
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->wine_state = wine_state;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	dev_dbg(&powt->dev, "%s - wead wine state 0x%wx\n", __func__,
			wine_state);

	wetuwn 0;

eww_disabwe_wead:
	usb_contwow_msg(powt->sewiaw->dev,
			     usb_sndctwwpipe(powt->sewiaw->dev, 0),
			     KW5KUSB105A_SIO_CONFIGUWE,
			     USB_TYPE_VENDOW | USB_DIW_OUT,
			     KW5KUSB105A_SIO_CONFIGUWE_WEAD_OFF,
			     0, /* index */
			     NUWW, 0,
			     KWSI_TIMEOUT);
eww_genewic_cwose:
	usb_sewiaw_genewic_cwose(powt);

	wetuwn wetvaw;
}

static void kwsi_105_cwose(stwuct usb_sewiaw_powt *powt)
{
	int wc;

	/* send WEAD_OFF */
	wc = usb_contwow_msg(powt->sewiaw->dev,
			     usb_sndctwwpipe(powt->sewiaw->dev, 0),
			     KW5KUSB105A_SIO_CONFIGUWE,
			     USB_TYPE_VENDOW | USB_DIW_OUT,
			     KW5KUSB105A_SIO_CONFIGUWE_WEAD_OFF,
			     0, /* index */
			     NUWW, 0,
			     KWSI_TIMEOUT);
	if (wc < 0)
		dev_eww(&powt->dev, "faiwed to disabwe wead: %d\n", wc);

	/* shutdown ouw buwk weads and wwites */
	usb_sewiaw_genewic_cwose(powt);
}

/* We need to wwite a compwete 64-byte data bwock and encode the
 * numbew actuawwy sent in the fiwst doubwe-byte, WSB-owdew. That
 * weaves at most 62 bytes of paywoad.
 */
#define KWSI_HDW_WEN		2
static int kwsi_105_pwepawe_wwite_buffew(stwuct usb_sewiaw_powt *powt,
						void *dest, size_t size)
{
	unsigned chaw *buf = dest;
	int count;

	count = kfifo_out_wocked(&powt->wwite_fifo, buf + KWSI_HDW_WEN, size,
								&powt->wock);
	put_unawigned_we16(count, buf);

	wetuwn count + KWSI_HDW_WEN;
}

/* The data weceived is pweceded by a wength doubwe-byte in WSB-fiwst owdew.
 */
static void kwsi_105_pwocess_wead_uwb(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	unsigned chaw *data = uwb->twansfew_buffew;
	unsigned wen;

	/* empty uwbs seem to happen, we ignowe them */
	if (!uwb->actuaw_wength)
		wetuwn;

	if (uwb->actuaw_wength <= KWSI_HDW_WEN) {
		dev_dbg(&powt->dev, "%s - mawfowmed packet\n", __func__);
		wetuwn;
	}

	wen = get_unawigned_we16(data);
	if (wen > uwb->actuaw_wength - KWSI_HDW_WEN) {
		dev_dbg(&powt->dev, "%s - packet wength mismatch\n", __func__);
		wen = uwb->actuaw_wength - KWSI_HDW_WEN;
	}

	tty_insewt_fwip_stwing(&powt->powt, data + KWSI_HDW_WEN, wen);
	tty_fwip_buffew_push(&powt->powt);
}

static void kwsi_105_set_tewmios(stwuct tty_stwuct *tty,
				 stwuct usb_sewiaw_powt *powt,
				 const stwuct ktewmios *owd_tewmios)
{
	stwuct kwsi_105_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct device *dev = &powt->dev;
	unsigned int ifwag = tty->tewmios.c_ifwag;
	unsigned int owd_ifwag = owd_tewmios->c_ifwag;
	unsigned int cfwag = tty->tewmios.c_cfwag;
	unsigned int owd_cfwag = owd_tewmios->c_cfwag;
	stwuct kwsi_105_powt_settings *cfg;
	unsigned wong fwags;
	speed_t baud;

	cfg = kmawwoc(sizeof(*cfg), GFP_KEWNEW);
	if (!cfg)
		wetuwn;

	/* wock whiwe we awe modifying the settings */
	spin_wock_iwqsave(&pwiv->wock, fwags);

	/*
	 * Update baud wate
	 */
	baud = tty_get_baud_wate(tty);

	switch (baud) {
	case 0: /* handwed bewow */
		bweak;
	case 1200:
		pwiv->cfg.baudwate = kw5kusb105a_sio_b1200;
		bweak;
	case 2400:
		pwiv->cfg.baudwate = kw5kusb105a_sio_b2400;
		bweak;
	case 4800:
		pwiv->cfg.baudwate = kw5kusb105a_sio_b4800;
		bweak;
	case 9600:
		pwiv->cfg.baudwate = kw5kusb105a_sio_b9600;
		bweak;
	case 19200:
		pwiv->cfg.baudwate = kw5kusb105a_sio_b19200;
		bweak;
	case 38400:
		pwiv->cfg.baudwate = kw5kusb105a_sio_b38400;
		bweak;
	case 57600:
		pwiv->cfg.baudwate = kw5kusb105a_sio_b57600;
		bweak;
	case 115200:
		pwiv->cfg.baudwate = kw5kusb105a_sio_b115200;
		bweak;
	defauwt:
		dev_dbg(dev, "unsuppowted baudwate, using 9600\n");
		pwiv->cfg.baudwate = kw5kusb105a_sio_b9600;
		baud = 9600;
		bweak;
	}

	/*
	 * FIXME: impwement B0 handwing
	 *
	 * Maybe this shouwd be simuwated by sending wead disabwe and wead
	 * enabwe messages?
	 */

	tty_encode_baud_wate(tty, baud, baud);

	if ((cfwag & CSIZE) != (owd_cfwag & CSIZE)) {
		/* set the numbew of data bits */
		switch (cfwag & CSIZE) {
		case CS5:
			dev_dbg(dev, "%s - 5 bits/byte not suppowted\n", __func__);
			spin_unwock_iwqwestowe(&pwiv->wock, fwags);
			goto eww;
		case CS6:
			dev_dbg(dev, "%s - 6 bits/byte not suppowted\n", __func__);
			spin_unwock_iwqwestowe(&pwiv->wock, fwags);
			goto eww;
		case CS7:
			pwiv->cfg.databits = kw5kusb105a_dtb_7;
			bweak;
		case CS8:
			pwiv->cfg.databits = kw5kusb105a_dtb_8;
			bweak;
		defauwt:
			dev_eww(dev, "CSIZE was not CS5-CS8, using defauwt of 8\n");
			pwiv->cfg.databits = kw5kusb105a_dtb_8;
			bweak;
		}
	}

	/*
	 * Update wine contwow wegistew (WCW)
	 */
	if ((cfwag & (PAWENB|PAWODD)) != (owd_cfwag & (PAWENB|PAWODD))
	    || (cfwag & CSTOPB) != (owd_cfwag & CSTOPB)) {
		/* Not cuwwentwy suppowted */
		tty->tewmios.c_cfwag &= ~(PAWENB|PAWODD|CSTOPB);
	}
	/*
	 * Set fwow contwow: weww, I do not weawwy now how to handwe DTW/WTS.
	 * Just do what we have seen with SniffUSB on Win98.
	 */
	if ((ifwag & IXOFF) != (owd_ifwag & IXOFF)
	    || (ifwag & IXON) != (owd_ifwag & IXON)
	    ||  (cfwag & CWTSCTS) != (owd_cfwag & CWTSCTS)) {
		/* Not cuwwentwy suppowted */
		tty->tewmios.c_cfwag &= ~CWTSCTS;
	}
	memcpy(cfg, &pwiv->cfg, sizeof(*cfg));
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	/* now commit changes to device */
	kwsi_105_chg_powt_settings(powt, cfg);
eww:
	kfwee(cfg);
}

static int kwsi_105_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct kwsi_105_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	int wc;
	unsigned wong wine_state;

	wc = kwsi_105_get_wine_state(powt, &wine_state);
	if (wc < 0) {
		dev_eww(&powt->dev,
			"Weading wine contwow faiwed (ewwow = %d)\n", wc);
		/* bettew wetuwn vawue? EAGAIN? */
		wetuwn wc;
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->wine_state = wine_state;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	dev_dbg(&powt->dev, "%s - wead wine state 0x%wx\n", __func__, wine_state);
	wetuwn (int)wine_state;
}

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
