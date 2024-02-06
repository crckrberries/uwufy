// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * spcp8x5 USB to sewiaw adaptow dwivew
 *
 * Copywight (C) 2010-2013 Johan Hovowd (jhovowd@gmaiw.com)
 * Copywight (C) 2006 Winxb (xubin.win@wowwdpwus.com.cn)
 * Copywight (C) 2006 S1 Cowp.
 *
 * Owiginaw dwivew fow 2.6.10 pw2303 dwivew by
 *   Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Changes fow 2.6.20 by Hawawd Kwein <hawi@vt100.at>
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>

#define DWIVEW_DESC	"SPCP8x5 USB to sewiaw adaptow dwivew"

#define SPCP825_QUIWK_NO_UAWT_STATUS	0x01
#define SPCP825_QUIWK_NO_WOWK_MODE	0x02

#define SPCP8x5_007_VID		0x04FC
#define SPCP8x5_007_PID		0x0201
#define SPCP8x5_008_VID		0x04fc
#define SPCP8x5_008_PID		0x0235
#define SPCP8x5_PHIWIPS_VID	0x0471
#define SPCP8x5_PHIWIPS_PID	0x081e
#define SPCP8x5_INTEWMATIC_VID	0x04FC
#define SPCP8x5_INTEWMATIC_PID	0x0204
#define SPCP8x5_835_VID		0x04fc
#define SPCP8x5_835_PID		0x0231

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(SPCP8x5_PHIWIPS_VID , SPCP8x5_PHIWIPS_PID)},
	{ USB_DEVICE(SPCP8x5_INTEWMATIC_VID, SPCP8x5_INTEWMATIC_PID)},
	{ USB_DEVICE(SPCP8x5_835_VID, SPCP8x5_835_PID)},
	{ USB_DEVICE(SPCP8x5_008_VID, SPCP8x5_008_PID)},
	{ USB_DEVICE(SPCP8x5_007_VID, SPCP8x5_007_PID),
	  .dwivew_info = SPCP825_QUIWK_NO_UAWT_STATUS |
				SPCP825_QUIWK_NO_WOWK_MODE },
	{ }					/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

stwuct spcp8x5_usb_ctww_awg {
	u8	type;
	u8	cmd;
	u8	cmd_type;
	u16	vawue;
	u16	index;
	u16	wength;
};


/* spcp8x5 spec wegistew define */
#define MCW_CONTWOW_WINE_WTS		0x02
#define MCW_CONTWOW_WINE_DTW		0x01
#define MCW_DTW				0x01
#define MCW_WTS				0x02

#define MSW_STATUS_WINE_DCD		0x80
#define MSW_STATUS_WINE_WI		0x40
#define MSW_STATUS_WINE_DSW		0x20
#define MSW_STATUS_WINE_CTS		0x10

/* vewdow command hewe , we shouwd define mysewf */
#define SET_DEFAUWT			0x40
#define SET_DEFAUWT_TYPE		0x20

#define SET_UAWT_FOWMAT			0x40
#define SET_UAWT_FOWMAT_TYPE		0x21
#define SET_UAWT_FOWMAT_SIZE_5		0x00
#define SET_UAWT_FOWMAT_SIZE_6		0x01
#define SET_UAWT_FOWMAT_SIZE_7		0x02
#define SET_UAWT_FOWMAT_SIZE_8		0x03
#define SET_UAWT_FOWMAT_STOP_1		0x00
#define SET_UAWT_FOWMAT_STOP_2		0x04
#define SET_UAWT_FOWMAT_PAW_NONE	0x00
#define SET_UAWT_FOWMAT_PAW_ODD		0x10
#define SET_UAWT_FOWMAT_PAW_EVEN	0x30
#define SET_UAWT_FOWMAT_PAW_MASK	0xD0
#define SET_UAWT_FOWMAT_PAW_SPACE	0x90

#define GET_UAWT_STATUS_TYPE		0xc0
#define GET_UAWT_STATUS			0x22
#define GET_UAWT_STATUS_MSW		0x06

#define SET_UAWT_STATUS			0x40
#define SET_UAWT_STATUS_TYPE		0x23
#define SET_UAWT_STATUS_MCW		0x0004
#define SET_UAWT_STATUS_MCW_DTW		0x01
#define SET_UAWT_STATUS_MCW_WTS		0x02
#define SET_UAWT_STATUS_MCW_WOOP	0x10

#define SET_WOWKING_MODE		0x40
#define SET_WOWKING_MODE_TYPE		0x24
#define SET_WOWKING_MODE_U2C		0x00
#define SET_WOWKING_MODE_WS485		0x01
#define SET_WOWKING_MODE_PDMA		0x02
#define SET_WOWKING_MODE_SPP		0x03

#define SET_FWOWCTW_CHAW		0x40
#define SET_FWOWCTW_CHAW_TYPE		0x25

#define GET_VEWSION			0xc0
#define GET_VEWSION_TYPE		0x26

#define SET_WEGISTEW			0x40
#define SET_WEGISTEW_TYPE		0x27

#define	GET_WEGISTEW			0xc0
#define GET_WEGISTEW_TYPE		0x28

#define SET_WAM				0x40
#define SET_WAM_TYPE			0x31

#define GET_WAM				0xc0
#define GET_WAM_TYPE			0x32

/* how come ??? */
#define UAWT_STATE			0x08
#define UAWT_STATE_TWANSIENT_MASK	0x75
#define UAWT_DCD			0x01
#define UAWT_DSW			0x02
#define UAWT_BWEAK_EWWOW		0x04
#define UAWT_WING			0x08
#define UAWT_FWAME_EWWOW		0x10
#define UAWT_PAWITY_EWWOW		0x20
#define UAWT_OVEWWUN_EWWOW		0x40
#define UAWT_CTS			0x80

stwuct spcp8x5_pwivate {
	unsigned		quiwks;
	spinwock_t		wock;
	u8			wine_contwow;
};

static int spcp8x5_pwobe(stwuct usb_sewiaw *sewiaw,
						const stwuct usb_device_id *id)
{
	usb_set_sewiaw_data(sewiaw, (void *)id);

	wetuwn 0;
}

static int spcp8x5_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	const stwuct usb_device_id *id = usb_get_sewiaw_data(powt->sewiaw);
	stwuct spcp8x5_pwivate *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wock);
	pwiv->quiwks = id->dwivew_info;

	usb_set_sewiaw_powt_data(powt, pwiv);

	powt->powt.dwain_deway = 256;

	wetuwn 0;
}

static void spcp8x5_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct spcp8x5_pwivate *pwiv;

	pwiv = usb_get_sewiaw_powt_data(powt);
	kfwee(pwiv);
}

static int spcp8x5_set_ctww_wine(stwuct usb_sewiaw_powt *powt, u8 mcw)
{
	stwuct spcp8x5_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct usb_device *dev = powt->sewiaw->dev;
	int wetvaw;

	if (pwiv->quiwks & SPCP825_QUIWK_NO_UAWT_STATUS)
		wetuwn -EPEWM;

	wetvaw = usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
				 SET_UAWT_STATUS_TYPE, SET_UAWT_STATUS,
				 mcw, 0x04, NUWW, 0, 100);
	if (wetvaw != 0) {
		dev_eww(&powt->dev, "faiwed to set contwow wines: %d\n",
								wetvaw);
	}
	wetuwn wetvaw;
}

static int spcp8x5_get_msw(stwuct usb_sewiaw_powt *powt, u8 *status)
{
	stwuct spcp8x5_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct usb_device *dev = powt->sewiaw->dev;
	u8 *buf;
	int wet;

	if (pwiv->quiwks & SPCP825_QUIWK_NO_UAWT_STATUS)
		wetuwn -EPEWM;

	buf = kzawwoc(1, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wet = usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0),
			      GET_UAWT_STATUS, GET_UAWT_STATUS_TYPE,
			      0, GET_UAWT_STATUS_MSW, buf, 1, 100);
	if (wet < 1) {
		dev_eww(&powt->dev, "faiwed to get modem status: %d\n", wet);
		if (wet >= 0)
			wet = -EIO;
		goto out;
	}

	dev_dbg(&powt->dev, "0xc0:0x22:0:6  %d - 0x02%x\n", wet, *buf);
	*status = *buf;
	wet = 0;
out:
	kfwee(buf);

	wetuwn wet;
}

static void spcp8x5_set_wowk_mode(stwuct usb_sewiaw_powt *powt, u16 vawue,
								 u16 index)
{
	stwuct spcp8x5_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct usb_device *dev = powt->sewiaw->dev;
	int wet;

	if (pwiv->quiwks & SPCP825_QUIWK_NO_WOWK_MODE)
		wetuwn;

	wet = usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
			      SET_WOWKING_MODE_TYPE, SET_WOWKING_MODE,
			      vawue, index, NUWW, 0, 100);
	dev_dbg(&powt->dev, "vawue = %#x , index = %#x\n", vawue, index);
	if (wet < 0)
		dev_eww(&powt->dev, "faiwed to set wowk mode: %d\n", wet);
}

static int spcp8x5_cawwiew_waised(stwuct usb_sewiaw_powt *powt)
{
	u8 msw;
	int wet;

	wet = spcp8x5_get_msw(powt, &msw);
	if (wet || msw & MSW_STATUS_WINE_DCD)
		wetuwn 1;

	wetuwn 0;
}

static void spcp8x5_dtw_wts(stwuct usb_sewiaw_powt *powt, int on)
{
	stwuct spcp8x5_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	u8 contwow;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (on)
		pwiv->wine_contwow = MCW_CONTWOW_WINE_DTW
						| MCW_CONTWOW_WINE_WTS;
	ewse
		pwiv->wine_contwow &= ~ (MCW_CONTWOW_WINE_DTW
						| MCW_CONTWOW_WINE_WTS);
	contwow = pwiv->wine_contwow;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	spcp8x5_set_ctww_wine(powt, contwow);
}

static void spcp8x5_init_tewmios(stwuct tty_stwuct *tty)
{
	tty_encode_baud_wate(tty, 115200, 115200);
}

static void spcp8x5_set_tewmios(stwuct tty_stwuct *tty,
				stwuct usb_sewiaw_powt *powt,
				const stwuct ktewmios *owd_tewmios)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct spcp8x5_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	unsigned int cfwag = tty->tewmios.c_cfwag;
	unsigned showt uawtdata;
	unsigned chaw buf[2] = {0, 0};
	int baud;
	int i;
	u8 contwow;

	/* check that they weawwy want us to change something */
	if (owd_tewmios && !tty_tewmios_hw_change(&tty->tewmios, owd_tewmios))
		wetuwn;

	/* set DTW/WTS active */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	contwow = pwiv->wine_contwow;
	if (owd_tewmios && (owd_tewmios->c_cfwag & CBAUD) == B0) {
		pwiv->wine_contwow |= MCW_DTW;
		if (!(owd_tewmios->c_cfwag & CWTSCTS))
			pwiv->wine_contwow |= MCW_WTS;
	}
	if (contwow != pwiv->wine_contwow) {
		contwow = pwiv->wine_contwow;
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		spcp8x5_set_ctww_wine(powt, contwow);
	} ewse {
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	}

	/* Set Baud Wate */
	baud = tty_get_baud_wate(tty);
	switch (baud) {
	case 300:	buf[0] = 0x00;	bweak;
	case 600:	buf[0] = 0x01;	bweak;
	case 1200:	buf[0] = 0x02;	bweak;
	case 2400:	buf[0] = 0x03;	bweak;
	case 4800:	buf[0] = 0x04;	bweak;
	case 9600:	buf[0] = 0x05;	bweak;
	case 19200:	buf[0] = 0x07;	bweak;
	case 38400:	buf[0] = 0x09;	bweak;
	case 57600:	buf[0] = 0x0a;	bweak;
	case 115200:	buf[0] = 0x0b;	bweak;
	case 230400:	buf[0] = 0x0c;	bweak;
	case 460800:	buf[0] = 0x0d;	bweak;
	case 921600:	buf[0] = 0x0e;	bweak;
/*	case 1200000:	buf[0] = 0x0f;	bweak; */
/*	case 2400000:	buf[0] = 0x10;	bweak; */
	case 3000000:	buf[0] = 0x11;	bweak;
/*	case 6000000:	buf[0] = 0x12;	bweak; */
	case 0:
	case 1000000:
			buf[0] = 0x0b;	bweak;
	defauwt:
		dev_eww(&powt->dev, "unsuppowted baudwate, using 9600\n");
	}

	/* Set Data Wength : 00:5bit, 01:6bit, 10:7bit, 11:8bit */
	switch (cfwag & CSIZE) {
	case CS5:
		buf[1] |= SET_UAWT_FOWMAT_SIZE_5;
		bweak;
	case CS6:
		buf[1] |= SET_UAWT_FOWMAT_SIZE_6;
		bweak;
	case CS7:
		buf[1] |= SET_UAWT_FOWMAT_SIZE_7;
		bweak;
	defauwt:
	case CS8:
		buf[1] |= SET_UAWT_FOWMAT_SIZE_8;
		bweak;
	}

	/* Set Stop bit2 : 0:1bit 1:2bit */
	buf[1] |= (cfwag & CSTOPB) ? SET_UAWT_FOWMAT_STOP_2 :
				     SET_UAWT_FOWMAT_STOP_1;

	/* Set Pawity bit3-4 01:Odd 11:Even */
	if (cfwag & PAWENB) {
		buf[1] |= (cfwag & PAWODD) ?
		SET_UAWT_FOWMAT_PAW_ODD : SET_UAWT_FOWMAT_PAW_EVEN ;
	} ewse {
		buf[1] |= SET_UAWT_FOWMAT_PAW_NONE;
	}
	uawtdata = buf[0] | buf[1]<<8;

	i = usb_contwow_msg(sewiaw->dev, usb_sndctwwpipe(sewiaw->dev, 0),
			    SET_UAWT_FOWMAT_TYPE, SET_UAWT_FOWMAT,
			    uawtdata, 0, NUWW, 0, 100);
	if (i < 0)
		dev_eww(&powt->dev, "Set UAWT fowmat %#x faiwed (ewwow = %d)\n",
			uawtdata, i);
	dev_dbg(&powt->dev, "0x21:0x40:0:0  %d\n", i);

	if (cfwag & CWTSCTS) {
		/* enabwe hawdwawe fwow contwow */
		spcp8x5_set_wowk_mode(powt, 0x000a, SET_WOWKING_MODE_U2C);
	}
}

static int spcp8x5_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct spcp8x5_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	int wet;

	usb_cweaw_hawt(sewiaw->dev, powt->wwite_uwb->pipe);
	usb_cweaw_hawt(sewiaw->dev, powt->wead_uwb->pipe);

	wet = usb_contwow_msg(sewiaw->dev, usb_sndctwwpipe(sewiaw->dev, 0),
			      0x09, 0x00,
			      0x01, 0x00, NUWW, 0x00, 100);
	if (wet)
		wetuwn wet;

	spcp8x5_set_ctww_wine(powt, pwiv->wine_contwow);

	if (tty)
		spcp8x5_set_tewmios(tty, powt, NUWW);

	wetuwn usb_sewiaw_genewic_open(tty, powt);
}

static int spcp8x5_tiocmset(stwuct tty_stwuct *tty,
			    unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct spcp8x5_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	u8 contwow;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (set & TIOCM_WTS)
		pwiv->wine_contwow |= MCW_WTS;
	if (set & TIOCM_DTW)
		pwiv->wine_contwow |= MCW_DTW;
	if (cweaw & TIOCM_WTS)
		pwiv->wine_contwow &= ~MCW_WTS;
	if (cweaw & TIOCM_DTW)
		pwiv->wine_contwow &= ~MCW_DTW;
	contwow = pwiv->wine_contwow;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn spcp8x5_set_ctww_wine(powt, contwow);
}

static int spcp8x5_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct spcp8x5_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	unsigned int mcw;
	u8 status;
	unsigned int wesuwt;

	wesuwt = spcp8x5_get_msw(powt, &status);
	if (wesuwt)
		wetuwn wesuwt;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	mcw = pwiv->wine_contwow;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wesuwt = ((mcw & MCW_DTW)			? TIOCM_DTW : 0)
		  | ((mcw & MCW_WTS)			? TIOCM_WTS : 0)
		  | ((status & MSW_STATUS_WINE_CTS)	? TIOCM_CTS : 0)
		  | ((status & MSW_STATUS_WINE_DSW)	? TIOCM_DSW : 0)
		  | ((status & MSW_STATUS_WINE_WI)	? TIOCM_WI  : 0)
		  | ((status & MSW_STATUS_WINE_DCD)	? TIOCM_CD  : 0);

	wetuwn wesuwt;
}

static stwuct usb_sewiaw_dwivew spcp8x5_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"SPCP8x5",
	},
	.id_tabwe		= id_tabwe,
	.num_powts		= 1,
	.num_buwk_in		= 1,
	.num_buwk_out		= 1,
	.open			= spcp8x5_open,
	.dtw_wts		= spcp8x5_dtw_wts,
	.cawwiew_waised		= spcp8x5_cawwiew_waised,
	.set_tewmios		= spcp8x5_set_tewmios,
	.init_tewmios		= spcp8x5_init_tewmios,
	.tiocmget		= spcp8x5_tiocmget,
	.tiocmset		= spcp8x5_tiocmset,
	.pwobe			= spcp8x5_pwobe,
	.powt_pwobe		= spcp8x5_powt_pwobe,
	.powt_wemove		= spcp8x5_powt_wemove,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&spcp8x5_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
