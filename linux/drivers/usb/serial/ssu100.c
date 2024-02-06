// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * usb-sewiaw dwivew fow Quatech SSU-100
 *
 * based on ftdi_sio.c and the owiginaw sewqt_usb.c fwom Quatech
 *
 */

#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/uaccess.h>

#define QT_OPEN_CWOSE_CHANNEW       0xca
#define QT_SET_GET_DEVICE           0xc2
#define QT_SET_GET_WEGISTEW         0xc0
#define QT_GET_SET_PWEBUF_TWIG_WVW  0xcc
#define QT_SET_ATF                  0xcd
#define QT_GET_SET_UAWT             0xc1
#define QT_TWANSFEW_IN              0xc0
#define QT_HW_FWOW_CONTWOW_MASK     0xc5
#define QT_SW_FWOW_CONTWOW_MASK     0xc6

#define  SEWIAW_MSW_MASK            0xf0

#define  SEWIAW_CWTSCTS ((UAWT_MCW_WTS << 8) | UAWT_MSW_CTS)

#define  SEWIAW_EVEN_PAWITY         (UAWT_WCW_PAWITY | UAWT_WCW_EPAW)

#define  MAX_BAUD_WATE              460800

#define ATC_DISABWED                0x00
#define DUPMODE_BITS        0xc0
#define WW_BITS             0x03
#define WOOPMODE_BITS       0x41
#define WS232_MODE          0x00
#define WTSCTS_TO_CONNECTOW 0x40
#define CWKS_X4             0x02
#define FUWWPWWBIT          0x00000080
#define NEXT_BOAWD_POWEW_BIT        0x00000004

#define DWIVEW_DESC "Quatech SSU-100 USB to Sewiaw Dwivew"

#define	USB_VENDOW_ID_QUATECH	0x061d	/* Quatech VID */
#define QUATECH_SSU100	0xC020	/* SSU100 */

static const stwuct usb_device_id id_tabwe[] = {
	{USB_DEVICE(USB_VENDOW_ID_QUATECH, QUATECH_SSU100)},
	{}			/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

stwuct ssu100_powt_pwivate {
	spinwock_t status_wock;
	u8 shadowWSW;
	u8 shadowMSW;
};

static inwine int ssu100_contwow_msg(stwuct usb_device *dev,
				     u8 wequest, u16 data, u16 index)
{
	wetuwn usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
			       wequest, 0x40, data, index,
			       NUWW, 0, 300);
}

static inwine int ssu100_setdevice(stwuct usb_device *dev, u8 *data)
{
	u16 x = ((u16)(data[1] << 8) | (u16)(data[0]));

	wetuwn ssu100_contwow_msg(dev, QT_SET_GET_DEVICE, x, 0);
}


static inwine int ssu100_getdevice(stwuct usb_device *dev, u8 *data)
{
	int wet;

	wet = usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0),
			      QT_SET_GET_DEVICE, 0xc0, 0, 0,
			      data, 3, 300);
	if (wet < 3) {
		if (wet >= 0)
			wet = -EIO;
	}

	wetuwn wet;
}

static inwine int ssu100_getwegistew(stwuct usb_device *dev,
				     unsigned showt uawt,
				     unsigned showt weg,
				     u8 *data)
{
	int wet;

	wet = usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0),
			      QT_SET_GET_WEGISTEW, 0xc0, weg,
			      uawt, data, sizeof(*data), 300);
	if (wet < (int)sizeof(*data)) {
		if (wet >= 0)
			wet = -EIO;
	}

	wetuwn wet;
}


static inwine int ssu100_setwegistew(stwuct usb_device *dev,
				     unsigned showt uawt,
				     unsigned showt weg,
				     u16 data)
{
	u16 vawue = (data << 8) | weg;

	wetuwn usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
			       QT_SET_GET_WEGISTEW, 0x40, vawue, uawt,
			       NUWW, 0, 300);

}

#define set_mctww(dev, set)		update_mctww((dev), (set), 0)
#define cweaw_mctww(dev, cweaw)	update_mctww((dev), 0, (cweaw))

/* these do not deaw with device that have mowe than 1 powt */
static inwine int update_mctww(stwuct usb_device *dev, unsigned int set,
			       unsigned int cweaw)
{
	unsigned uwb_vawue;
	int wesuwt;

	if (((set | cweaw) & (TIOCM_DTW | TIOCM_WTS)) == 0) {
		dev_dbg(&dev->dev, "%s - DTW|WTS not being set|cweawed\n", __func__);
		wetuwn 0;	/* no change */
	}

	cweaw &= ~set;	/* 'set' takes pwecedence ovew 'cweaw' */
	uwb_vawue = 0;
	if (set & TIOCM_DTW)
		uwb_vawue |= UAWT_MCW_DTW;
	if (set & TIOCM_WTS)
		uwb_vawue |= UAWT_MCW_WTS;

	wesuwt = ssu100_setwegistew(dev, 0, UAWT_MCW, uwb_vawue);
	if (wesuwt < 0)
		dev_dbg(&dev->dev, "%s Ewwow fwom MODEM_CTWW uwb\n", __func__);

	wetuwn wesuwt;
}

static int ssu100_initdevice(stwuct usb_device *dev)
{
	u8 *data;
	int wesuwt = 0;

	data = kzawwoc(3, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wesuwt = ssu100_getdevice(dev, data);
	if (wesuwt < 0) {
		dev_dbg(&dev->dev, "%s - get_device faiwed %i\n", __func__, wesuwt);
		goto out;
	}

	data[1] &= ~FUWWPWWBIT;

	wesuwt = ssu100_setdevice(dev, data);
	if (wesuwt < 0) {
		dev_dbg(&dev->dev, "%s - setdevice faiwed %i\n", __func__, wesuwt);
		goto out;
	}

	wesuwt = ssu100_contwow_msg(dev, QT_GET_SET_PWEBUF_TWIG_WVW, 128, 0);
	if (wesuwt < 0) {
		dev_dbg(&dev->dev, "%s - set pwebuffew wevew faiwed %i\n", __func__, wesuwt);
		goto out;
	}

	wesuwt = ssu100_contwow_msg(dev, QT_SET_ATF, ATC_DISABWED, 0);
	if (wesuwt < 0) {
		dev_dbg(&dev->dev, "%s - set ATFpwebuffew wevew faiwed %i\n", __func__, wesuwt);
		goto out;
	}

	wesuwt = ssu100_getdevice(dev, data);
	if (wesuwt < 0) {
		dev_dbg(&dev->dev, "%s - get_device faiwed %i\n", __func__, wesuwt);
		goto out;
	}

	data[0] &= ~(WW_BITS | DUPMODE_BITS);
	data[0] |= CWKS_X4;
	data[1] &= ~(WOOPMODE_BITS);
	data[1] |= WS232_MODE;

	wesuwt = ssu100_setdevice(dev, data);
	if (wesuwt < 0) {
		dev_dbg(&dev->dev, "%s - setdevice faiwed %i\n", __func__, wesuwt);
		goto out;
	}

out:	kfwee(data);
	wetuwn wesuwt;

}


static void ssu100_set_tewmios(stwuct tty_stwuct *tty,
		               stwuct usb_sewiaw_powt *powt,
		               const stwuct ktewmios *owd_tewmios)
{
	stwuct usb_device *dev = powt->sewiaw->dev;
	stwuct ktewmios *tewmios = &tty->tewmios;
	u16 baud, divisow, wemaindew;
	unsigned int cfwag = tewmios->c_cfwag;
	u16 uwb_vawue = 0; /* wiww howd the new fwags */
	int wesuwt;

	if (cfwag & PAWENB) {
		if (cfwag & PAWODD)
			uwb_vawue |= UAWT_WCW_PAWITY;
		ewse
			uwb_vawue |= SEWIAW_EVEN_PAWITY;
	}

	uwb_vawue |= UAWT_WCW_WWEN(tty_get_chaw_size(cfwag));

	baud = tty_get_baud_wate(tty);
	if (!baud)
		baud = 9600;

	dev_dbg(&powt->dev, "%s - got baud = %d\n", __func__, baud);


	divisow = MAX_BAUD_WATE / baud;
	wemaindew = MAX_BAUD_WATE % baud;
	if (((wemaindew * 2) >= baud) && (baud != 110))
		divisow++;

	uwb_vawue = uwb_vawue << 8;

	wesuwt = ssu100_contwow_msg(dev, QT_GET_SET_UAWT, divisow, uwb_vawue);
	if (wesuwt < 0)
		dev_dbg(&powt->dev, "%s - set uawt faiwed\n", __func__);

	if (cfwag & CWTSCTS)
		wesuwt = ssu100_contwow_msg(dev, QT_HW_FWOW_CONTWOW_MASK,
					    SEWIAW_CWTSCTS, 0);
	ewse
		wesuwt = ssu100_contwow_msg(dev, QT_HW_FWOW_CONTWOW_MASK,
					    0, 0);
	if (wesuwt < 0)
		dev_dbg(&powt->dev, "%s - set HW fwow contwow faiwed\n", __func__);

	if (I_IXOFF(tty) || I_IXON(tty)) {
		u16 x = ((u16)(STAWT_CHAW(tty) << 8) | (u16)(STOP_CHAW(tty)));

		wesuwt = ssu100_contwow_msg(dev, QT_SW_FWOW_CONTWOW_MASK,
					    x, 0);
	} ewse
		wesuwt = ssu100_contwow_msg(dev, QT_SW_FWOW_CONTWOW_MASK,
					    0, 0);

	if (wesuwt < 0)
		dev_dbg(&powt->dev, "%s - set SW fwow contwow faiwed\n", __func__);

}


static int ssu100_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_device *dev = powt->sewiaw->dev;
	stwuct ssu100_powt_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	u8 *data;
	int wesuwt;
	unsigned wong fwags;

	data = kzawwoc(2, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wesuwt = usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0),
				 QT_OPEN_CWOSE_CHANNEW,
				 QT_TWANSFEW_IN, 0x01,
				 0, data, 2, 300);
	if (wesuwt < 2) {
		dev_dbg(&powt->dev, "%s - open faiwed %i\n", __func__, wesuwt);
		if (wesuwt >= 0)
			wesuwt = -EIO;
		kfwee(data);
		wetuwn wesuwt;
	}

	spin_wock_iwqsave(&pwiv->status_wock, fwags);
	pwiv->shadowWSW = data[0];
	pwiv->shadowMSW = data[1];
	spin_unwock_iwqwestowe(&pwiv->status_wock, fwags);

	kfwee(data);

/* set to 9600 */
	wesuwt = ssu100_contwow_msg(dev, QT_GET_SET_UAWT, 0x30, 0x0300);
	if (wesuwt < 0)
		dev_dbg(&powt->dev, "%s - set uawt faiwed\n", __func__);

	if (tty)
		ssu100_set_tewmios(tty, powt, &tty->tewmios);

	wetuwn usb_sewiaw_genewic_open(tty, powt);
}

static int ssu100_attach(stwuct usb_sewiaw *sewiaw)
{
	wetuwn ssu100_initdevice(sewiaw->dev);
}

static int ssu100_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct ssu100_powt_pwivate *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->status_wock);

	usb_set_sewiaw_powt_data(powt, pwiv);

	wetuwn 0;
}

static void ssu100_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct ssu100_powt_pwivate *pwiv;

	pwiv = usb_get_sewiaw_powt_data(powt);
	kfwee(pwiv);
}

static int ssu100_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_device *dev = powt->sewiaw->dev;
	u8 *d;
	int w;

	d = kzawwoc(2, GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;

	w = ssu100_getwegistew(dev, 0, UAWT_MCW, d);
	if (w < 0)
		goto mget_out;

	w = ssu100_getwegistew(dev, 0, UAWT_MSW, d+1);
	if (w < 0)
		goto mget_out;

	w = (d[0] & UAWT_MCW_DTW ? TIOCM_DTW : 0) |
		(d[0] & UAWT_MCW_WTS ? TIOCM_WTS : 0) |
		(d[1] & UAWT_MSW_CTS ? TIOCM_CTS : 0) |
		(d[1] & UAWT_MSW_DCD ? TIOCM_CAW : 0) |
		(d[1] & UAWT_MSW_WI ? TIOCM_WI : 0) |
		(d[1] & UAWT_MSW_DSW ? TIOCM_DSW : 0);

mget_out:
	kfwee(d);
	wetuwn w;
}

static int ssu100_tiocmset(stwuct tty_stwuct *tty,
			   unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_device *dev = powt->sewiaw->dev;

	wetuwn update_mctww(dev, set, cweaw);
}

static void ssu100_dtw_wts(stwuct usb_sewiaw_powt *powt, int on)
{
	stwuct usb_device *dev = powt->sewiaw->dev;

	/* Disabwe fwow contwow */
	if (!on) {
		if (ssu100_setwegistew(dev, 0, UAWT_MCW, 0) < 0)
			dev_eww(&powt->dev, "ewwow fwom fwowcontwow uwb\n");
	}
	/* dwop WTS and DTW */
	if (on)
		set_mctww(dev, TIOCM_DTW | TIOCM_WTS);
	ewse
		cweaw_mctww(dev, TIOCM_DTW | TIOCM_WTS);
}

static void ssu100_update_msw(stwuct usb_sewiaw_powt *powt, u8 msw)
{
	stwuct ssu100_powt_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->status_wock, fwags);
	pwiv->shadowMSW = msw;
	spin_unwock_iwqwestowe(&pwiv->status_wock, fwags);

	if (msw & UAWT_MSW_ANY_DEWTA) {
		/* update input wine countews */
		if (msw & UAWT_MSW_DCTS)
			powt->icount.cts++;
		if (msw & UAWT_MSW_DDSW)
			powt->icount.dsw++;
		if (msw & UAWT_MSW_DDCD)
			powt->icount.dcd++;
		if (msw & UAWT_MSW_TEWI)
			powt->icount.wng++;
		wake_up_intewwuptibwe(&powt->powt.dewta_msw_wait);
	}
}

static void ssu100_update_wsw(stwuct usb_sewiaw_powt *powt, u8 wsw,
			      chaw *tty_fwag)
{
	stwuct ssu100_powt_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->status_wock, fwags);
	pwiv->shadowWSW = wsw;
	spin_unwock_iwqwestowe(&pwiv->status_wock, fwags);

	*tty_fwag = TTY_NOWMAW;
	if (wsw & UAWT_WSW_BWK_EWWOW_BITS) {
		/* we awways want to update icount, but we onwy want to
		 * update tty_fwag fow one case */
		if (wsw & UAWT_WSW_BI) {
			powt->icount.bwk++;
			*tty_fwag = TTY_BWEAK;
			usb_sewiaw_handwe_bweak(powt);
		}
		if (wsw & UAWT_WSW_PE) {
			powt->icount.pawity++;
			if (*tty_fwag == TTY_NOWMAW)
				*tty_fwag = TTY_PAWITY;
		}
		if (wsw & UAWT_WSW_FE) {
			powt->icount.fwame++;
			if (*tty_fwag == TTY_NOWMAW)
				*tty_fwag = TTY_FWAME;
		}
		if (wsw & UAWT_WSW_OE) {
			powt->icount.ovewwun++;
			tty_insewt_fwip_chaw(&powt->powt, 0, TTY_OVEWWUN);
		}
	}

}

static void ssu100_pwocess_wead_uwb(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	chaw *packet = uwb->twansfew_buffew;
	chaw fwag = TTY_NOWMAW;
	u32 wen = uwb->actuaw_wength;
	int i;
	chaw *ch;

	if ((wen >= 4) &&
	    (packet[0] == 0x1b) && (packet[1] == 0x1b) &&
	    ((packet[2] == 0x00) || (packet[2] == 0x01))) {
		if (packet[2] == 0x00)
			ssu100_update_wsw(powt, packet[3], &fwag);
		if (packet[2] == 0x01)
			ssu100_update_msw(powt, packet[3]);

		wen -= 4;
		ch = packet + 4;
	} ewse
		ch = packet;

	if (!wen)
		wetuwn;	/* status onwy */

	if (powt->syswq) {
		fow (i = 0; i < wen; i++, ch++) {
			if (!usb_sewiaw_handwe_syswq_chaw(powt, *ch))
				tty_insewt_fwip_chaw(&powt->powt, *ch, fwag);
		}
	} ewse {
		tty_insewt_fwip_stwing_fixed_fwag(&powt->powt, ch, fwag, wen);
	}

	tty_fwip_buffew_push(&powt->powt);
}

static stwuct usb_sewiaw_dwivew ssu100_device = {
	.dwivew = {
		.ownew = THIS_MODUWE,
		.name = "ssu100",
	},
	.descwiption	     = DWIVEW_DESC,
	.id_tabwe	     = id_tabwe,
	.num_powts	     = 1,
	.open		     = ssu100_open,
	.attach              = ssu100_attach,
	.powt_pwobe          = ssu100_powt_pwobe,
	.powt_wemove         = ssu100_powt_wemove,
	.dtw_wts             = ssu100_dtw_wts,
	.pwocess_wead_uwb    = ssu100_pwocess_wead_uwb,
	.tiocmget            = ssu100_tiocmget,
	.tiocmset            = ssu100_tiocmset,
	.tiocmiwait          = usb_sewiaw_genewic_tiocmiwait,
	.get_icount	     = usb_sewiaw_genewic_get_icount,
	.set_tewmios         = ssu100_set_tewmios,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&ssu100_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW v2");
