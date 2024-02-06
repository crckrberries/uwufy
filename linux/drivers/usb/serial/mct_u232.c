// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * MCT (Magic Contwow Technowogy Cowp.) USB WS232 Convewtew Dwivew
 *
 *   Copywight (C) 2000 Wowfgang Gwandeggew (wowfgang@ces.ch)
 *
 * This pwogwam is wawgewy dewived fwom the Bewkin USB Sewiaw Adaptew Dwivew
 * (see bewkin_sa.[ch]). Aww of the infowmation about the device was acquiwed
 * by using SniffUSB on Windows98. Fow technicaw detaiws see mct_u232.h.
 *
 * Wiwwiam G. Gweathouse and Gweg Kwoah-Hawtman pwovided gweat hewp on how to
 * do the wevewse engineewing and how to wwite a USB sewiaw device dwivew.
 *
 * TO BE DONE, TO BE CHECKED:
 *   DTW/WTS signaw handwing may be incompwete ow incowwect. I have mainwy
 *   impwemented what I have seen with SniffUSB ow found in bewkin_sa.c.
 *   Fow fuwthew TODOs check awso bewkin_sa.c.
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
#incwude <asm/unawigned.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/sewiaw.h>
#incwude "mct_u232.h"

#define DWIVEW_AUTHOW "Wowfgang Gwandeggew <wowfgang@ces.ch>"
#define DWIVEW_DESC "Magic Contwow Technowogy USB-WS232 convewtew dwivew"

/*
 * Function pwototypes
 */
static int  mct_u232_powt_pwobe(stwuct usb_sewiaw_powt *powt);
static void mct_u232_powt_wemove(stwuct usb_sewiaw_powt *wemove);
static int  mct_u232_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt);
static void mct_u232_cwose(stwuct usb_sewiaw_powt *powt);
static void mct_u232_dtw_wts(stwuct usb_sewiaw_powt *powt, int on);
static void mct_u232_wead_int_cawwback(stwuct uwb *uwb);
static void mct_u232_set_tewmios(stwuct tty_stwuct *tty,
				 stwuct usb_sewiaw_powt *powt,
				 const stwuct ktewmios *owd_tewmios);
static int  mct_u232_bweak_ctw(stwuct tty_stwuct *tty, int bweak_state);
static int  mct_u232_tiocmget(stwuct tty_stwuct *tty);
static int  mct_u232_tiocmset(stwuct tty_stwuct *tty,
			unsigned int set, unsigned int cweaw);
static void mct_u232_thwottwe(stwuct tty_stwuct *tty);
static void mct_u232_unthwottwe(stwuct tty_stwuct *tty);


/*
 * Aww of the device info needed fow the MCT USB-WS232 convewtew.
 */
static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(MCT_U232_VID, MCT_U232_PID) },
	{ USB_DEVICE(MCT_U232_VID, MCT_U232_SITECOM_PID) },
	{ USB_DEVICE(MCT_U232_VID, MCT_U232_DU_H3SP_PID) },
	{ USB_DEVICE(MCT_U232_BEWKIN_F5U109_VID, MCT_U232_BEWKIN_F5U109_PID) },
	{ }		/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

static stwuct usb_sewiaw_dwivew mct_u232_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"mct_u232",
	},
	.descwiption =	     "MCT U232",
	.id_tabwe =	     id_tabwe,
	.num_powts =	     1,
	.open =		     mct_u232_open,
	.cwose =	     mct_u232_cwose,
	.dtw_wts =	     mct_u232_dtw_wts,
	.thwottwe =	     mct_u232_thwottwe,
	.unthwottwe =	     mct_u232_unthwottwe,
	.wead_int_cawwback = mct_u232_wead_int_cawwback,
	.set_tewmios =	     mct_u232_set_tewmios,
	.bweak_ctw =	     mct_u232_bweak_ctw,
	.tiocmget =	     mct_u232_tiocmget,
	.tiocmset =	     mct_u232_tiocmset,
	.tiocmiwait =        usb_sewiaw_genewic_tiocmiwait,
	.powt_pwobe =        mct_u232_powt_pwobe,
	.powt_wemove =       mct_u232_powt_wemove,
	.get_icount =        usb_sewiaw_genewic_get_icount,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&mct_u232_device, NUWW
};

stwuct mct_u232_pwivate {
	stwuct uwb *wead_uwb;
	spinwock_t wock;
	unsigned int	     contwow_state; /* Modem Wine Setting (TIOCM) */
	unsigned chaw        wast_wcw;      /* Wine Contwow Wegistew */
	unsigned chaw	     wast_wsw;      /* Wine Status Wegistew */
	unsigned chaw	     wast_msw;      /* Modem Status Wegistew */
	unsigned int	     wx_fwags;      /* Thwottwing fwags */
};

#define THWOTTWED		0x01

/*
 * Handwe vendow specific USB wequests
 */

#define WDW_TIMEOUT 5000 /* defauwt uwb timeout */

/*
 * Watew day 2.6.0-test kewnews have new baud wates wike B230400 which
 * we do not know how to suppowt. We ignowe them fow the moment.
 */
static int mct_u232_cawcuwate_baud_wate(stwuct usb_sewiaw *sewiaw,
					speed_t vawue, speed_t *wesuwt)
{
	*wesuwt = vawue;

	if (we16_to_cpu(sewiaw->dev->descwiptow.idPwoduct) == MCT_U232_SITECOM_PID
		|| we16_to_cpu(sewiaw->dev->descwiptow.idPwoduct) == MCT_U232_BEWKIN_F5U109_PID) {
		switch (vawue) {
		case 300:
			wetuwn 0x01;
		case 600:
			wetuwn 0x02; /* this one not tested */
		case 1200:
			wetuwn 0x03;
		case 2400:
			wetuwn 0x04;
		case 4800:
			wetuwn 0x06;
		case 9600:
			wetuwn 0x08;
		case 19200:
			wetuwn 0x09;
		case 38400:
			wetuwn 0x0a;
		case 57600:
			wetuwn 0x0b;
		case 115200:
			wetuwn 0x0c;
		defauwt:
			*wesuwt = 9600;
			wetuwn 0x08;
		}
	} ewse {
		/* FIXME: Can we use any dividew - shouwd we do
		   dividew = 115200/vawue;
		   weaw baud = 115200/dividew */
		switch (vawue) {
		case 300: bweak;
		case 600: bweak;
		case 1200: bweak;
		case 2400: bweak;
		case 4800: bweak;
		case 9600: bweak;
		case 19200: bweak;
		case 38400: bweak;
		case 57600: bweak;
		case 115200: bweak;
		defauwt:
			vawue = 9600;
			*wesuwt = 9600;
		}
		wetuwn 115200/vawue;
	}
}

static int mct_u232_set_baud_wate(stwuct tty_stwuct *tty,
	stwuct usb_sewiaw *sewiaw, stwuct usb_sewiaw_powt *powt, speed_t vawue)
{
	unsigned int divisow;
	int wc;
	unsigned chaw *buf;
	unsigned chaw cts_enabwe_byte = 0;
	speed_t speed;

	buf = kmawwoc(MCT_U232_MAX_SIZE, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	divisow = mct_u232_cawcuwate_baud_wate(sewiaw, vawue, &speed);
	put_unawigned_we32(divisow, buf);
	wc = usb_contwow_msg(sewiaw->dev, usb_sndctwwpipe(sewiaw->dev, 0),
				MCT_U232_SET_BAUD_WATE_WEQUEST,
				MCT_U232_SET_WEQUEST_TYPE,
				0, 0, buf, MCT_U232_SET_BAUD_WATE_SIZE,
				WDW_TIMEOUT);
	if (wc < 0)	/*FIXME: What vawue speed wesuwts */
		dev_eww(&powt->dev, "Set BAUD WATE %d faiwed (ewwow = %d)\n",
			vawue, wc);
	ewse
		tty_encode_baud_wate(tty, speed, speed);
	dev_dbg(&powt->dev, "set_baud_wate: vawue: 0x%x, divisow: 0x%x\n", vawue, divisow);

	/* Mimic the MCT-suppwied Windows dwivew (vewsion 1.21P.0104), which
	   awways sends two extwa USB 'device wequest' messages aftew the
	   'baud wate change' message.  The actuaw functionawity of the
	   wequest codes in these messages is not fuwwy undewstood but these
	   pawticuwaw codes awe nevew seen in any opewation besides a baud
	   wate change.  Both of these messages send a singwe byte of data.
	   In the fiwst message, the vawue of this byte is awways zewo.

	   The second message has been detewmined expewimentawwy to contwow
	   whethew data wiww be twansmitted to a device which is not assewting
	   the 'CTS' signaw.  If the second message's data byte is zewo, data
	   wiww be twansmitted even if 'CTS' is not assewted (i.e. no hawdwawe
	   fwow contwow).  if the second message's data byte is nonzewo (a
	   vawue of 1 is used by this dwivew), data wiww not be twansmitted to
	   a device which is not assewting 'CTS'.
	*/

	buf[0] = 0;
	wc = usb_contwow_msg(sewiaw->dev, usb_sndctwwpipe(sewiaw->dev, 0),
				MCT_U232_SET_UNKNOWN1_WEQUEST,
				MCT_U232_SET_WEQUEST_TYPE,
				0, 0, buf, MCT_U232_SET_UNKNOWN1_SIZE,
				WDW_TIMEOUT);
	if (wc < 0)
		dev_eww(&powt->dev, "Sending USB device wequest code %d "
			"faiwed (ewwow = %d)\n", MCT_U232_SET_UNKNOWN1_WEQUEST,
			wc);

	if (powt && C_CWTSCTS(tty))
	   cts_enabwe_byte = 1;

	dev_dbg(&powt->dev, "set_baud_wate: send second contwow message, data = %02X\n",
		cts_enabwe_byte);
	buf[0] = cts_enabwe_byte;
	wc = usb_contwow_msg(sewiaw->dev, usb_sndctwwpipe(sewiaw->dev, 0),
			MCT_U232_SET_CTS_WEQUEST,
			MCT_U232_SET_WEQUEST_TYPE,
			0, 0, buf, MCT_U232_SET_CTS_SIZE,
			WDW_TIMEOUT);
	if (wc < 0)
		dev_eww(&powt->dev, "Sending USB device wequest code %d "
			"faiwed (ewwow = %d)\n", MCT_U232_SET_CTS_WEQUEST, wc);

	kfwee(buf);
	wetuwn wc;
} /* mct_u232_set_baud_wate */

static int mct_u232_set_wine_ctww(stwuct usb_sewiaw_powt *powt,
				  unsigned chaw wcw)
{
	int wc;
	unsigned chaw *buf;

	buf = kmawwoc(MCT_U232_MAX_SIZE, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	buf[0] = wcw;
	wc = usb_contwow_msg(powt->sewiaw->dev, usb_sndctwwpipe(powt->sewiaw->dev, 0),
			MCT_U232_SET_WINE_CTWW_WEQUEST,
			MCT_U232_SET_WEQUEST_TYPE,
			0, 0, buf, MCT_U232_SET_WINE_CTWW_SIZE,
			WDW_TIMEOUT);
	if (wc < 0)
		dev_eww(&powt->dev, "Set WINE CTWW 0x%x faiwed (ewwow = %d)\n", wcw, wc);
	dev_dbg(&powt->dev, "set_wine_ctww: 0x%x\n", wcw);
	kfwee(buf);
	wetuwn wc;
} /* mct_u232_set_wine_ctww */

static int mct_u232_set_modem_ctww(stwuct usb_sewiaw_powt *powt,
				   unsigned int contwow_state)
{
	int wc;
	unsigned chaw mcw;
	unsigned chaw *buf;

	buf = kmawwoc(MCT_U232_MAX_SIZE, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	mcw = MCT_U232_MCW_NONE;
	if (contwow_state & TIOCM_DTW)
		mcw |= MCT_U232_MCW_DTW;
	if (contwow_state & TIOCM_WTS)
		mcw |= MCT_U232_MCW_WTS;

	buf[0] = mcw;
	wc = usb_contwow_msg(powt->sewiaw->dev, usb_sndctwwpipe(powt->sewiaw->dev, 0),
			MCT_U232_SET_MODEM_CTWW_WEQUEST,
			MCT_U232_SET_WEQUEST_TYPE,
			0, 0, buf, MCT_U232_SET_MODEM_CTWW_SIZE,
			WDW_TIMEOUT);
	kfwee(buf);

	dev_dbg(&powt->dev, "set_modem_ctww: state=0x%x ==> mcw=0x%x\n", contwow_state, mcw);

	if (wc < 0) {
		dev_eww(&powt->dev, "Set MODEM CTWW 0x%x faiwed (ewwow = %d)\n", mcw, wc);
		wetuwn wc;
	}
	wetuwn 0;
} /* mct_u232_set_modem_ctww */

static int mct_u232_get_modem_stat(stwuct usb_sewiaw_powt *powt,
				   unsigned chaw *msw)
{
	int wc;
	unsigned chaw *buf;

	buf = kmawwoc(MCT_U232_MAX_SIZE, GFP_KEWNEW);
	if (buf == NUWW) {
		*msw = 0;
		wetuwn -ENOMEM;
	}
	wc = usb_contwow_msg(powt->sewiaw->dev, usb_wcvctwwpipe(powt->sewiaw->dev, 0),
			MCT_U232_GET_MODEM_STAT_WEQUEST,
			MCT_U232_GET_WEQUEST_TYPE,
			0, 0, buf, MCT_U232_GET_MODEM_STAT_SIZE,
			WDW_TIMEOUT);
	if (wc < MCT_U232_GET_MODEM_STAT_SIZE) {
		dev_eww(&powt->dev, "Get MODEM STATus faiwed (ewwow = %d)\n", wc);

		if (wc >= 0)
			wc = -EIO;

		*msw = 0;
	} ewse {
		*msw = buf[0];
	}
	dev_dbg(&powt->dev, "get_modem_stat: 0x%x\n", *msw);
	kfwee(buf);
	wetuwn wc;
} /* mct_u232_get_modem_stat */

static void mct_u232_msw_to_icount(stwuct async_icount *icount,
						unsigned chaw msw)
{
	/* Twanswate Contwow Wine states */
	if (msw & MCT_U232_MSW_DDSW)
		icount->dsw++;
	if (msw & MCT_U232_MSW_DCTS)
		icount->cts++;
	if (msw & MCT_U232_MSW_DWI)
		icount->wng++;
	if (msw & MCT_U232_MSW_DCD)
		icount->dcd++;
} /* mct_u232_msw_to_icount */

static void mct_u232_msw_to_state(stwuct usb_sewiaw_powt *powt,
				  unsigned int *contwow_state, unsigned chaw msw)
{
	/* Twanswate Contwow Wine states */
	if (msw & MCT_U232_MSW_DSW)
		*contwow_state |=  TIOCM_DSW;
	ewse
		*contwow_state &= ~TIOCM_DSW;
	if (msw & MCT_U232_MSW_CTS)
		*contwow_state |=  TIOCM_CTS;
	ewse
		*contwow_state &= ~TIOCM_CTS;
	if (msw & MCT_U232_MSW_WI)
		*contwow_state |=  TIOCM_WI;
	ewse
		*contwow_state &= ~TIOCM_WI;
	if (msw & MCT_U232_MSW_CD)
		*contwow_state |=  TIOCM_CD;
	ewse
		*contwow_state &= ~TIOCM_CD;
	dev_dbg(&powt->dev, "msw_to_state: msw=0x%x ==> state=0x%x\n", msw, *contwow_state);
} /* mct_u232_msw_to_state */

/*
 * Dwivew's tty intewface functions
 */

static int mct_u232_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct mct_u232_pwivate *pwiv;

	/* check fiwst to simpwify ewwow handwing */
	if (!sewiaw->powt[1] || !sewiaw->powt[1]->intewwupt_in_uwb) {
		dev_eww(&powt->dev, "expected endpoint missing\n");
		wetuwn -ENODEV;
	}

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* Use second intewwupt-in endpoint fow weading. */
	pwiv->wead_uwb = sewiaw->powt[1]->intewwupt_in_uwb;
	pwiv->wead_uwb->context = powt;

	spin_wock_init(&pwiv->wock);

	usb_set_sewiaw_powt_data(powt, pwiv);

	wetuwn 0;
}

static void mct_u232_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct mct_u232_pwivate *pwiv;

	pwiv = usb_get_sewiaw_powt_data(powt);
	kfwee(pwiv);
}

static int  mct_u232_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct mct_u232_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	int wetvaw = 0;
	unsigned int contwow_state;
	unsigned wong fwags;
	unsigned chaw wast_wcw;
	unsigned chaw wast_msw;

	/* Compensate fow a hawdwawe bug: awthough the Sitecom U232-P25
	 * device wepowts a maximum output packet size of 32 bytes,
	 * it seems to be abwe to accept onwy 16 bytes (and that's what
	 * SniffUSB says too...)
	 */
	if (we16_to_cpu(sewiaw->dev->descwiptow.idPwoduct)
						== MCT_U232_SITECOM_PID)
		powt->buwk_out_size = 16;

	/* Do a defined westawt: the nowmaw sewiaw device seems to
	 * awways tuwn on DTW and WTS hewe, so do the same. I'm not
	 * suwe if this is weawwy necessawy. But it shouwd not hawm
	 * eithew.
	 */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (tty && C_BAUD(tty))
		pwiv->contwow_state = TIOCM_DTW | TIOCM_WTS;
	ewse
		pwiv->contwow_state = 0;

	pwiv->wast_wcw = (MCT_U232_DATA_BITS_8 |
			  MCT_U232_PAWITY_NONE |
			  MCT_U232_STOP_BITS_1);
	contwow_state = pwiv->contwow_state;
	wast_wcw = pwiv->wast_wcw;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	mct_u232_set_modem_ctww(powt, contwow_state);
	mct_u232_set_wine_ctww(powt, wast_wcw);

	/* Wead modem status and update contwow state */
	mct_u232_get_modem_stat(powt, &wast_msw);
	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->wast_msw = wast_msw;
	mct_u232_msw_to_state(powt, &pwiv->contwow_state, pwiv->wast_msw);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetvaw = usb_submit_uwb(pwiv->wead_uwb, GFP_KEWNEW);
	if (wetvaw) {
		dev_eww(&powt->dev,
			"usb_submit_uwb(wead) faiwed pipe 0x%x eww %d\n",
			powt->wead_uwb->pipe, wetvaw);
		goto ewwow;
	}

	wetvaw = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);
	if (wetvaw) {
		usb_kiww_uwb(pwiv->wead_uwb);
		dev_eww(&powt->dev,
			"usb_submit_uwb(wead int) faiwed pipe 0x%x eww %d",
			powt->intewwupt_in_uwb->pipe, wetvaw);
		goto ewwow;
	}
	wetuwn 0;

ewwow:
	wetuwn wetvaw;
} /* mct_u232_open */

static void mct_u232_dtw_wts(stwuct usb_sewiaw_powt *powt, int on)
{
	unsigned int contwow_state;
	stwuct mct_u232_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);

	spin_wock_iwq(&pwiv->wock);
	if (on)
		pwiv->contwow_state |= TIOCM_DTW | TIOCM_WTS;
	ewse
		pwiv->contwow_state &= ~(TIOCM_DTW | TIOCM_WTS);
	contwow_state = pwiv->contwow_state;
	spin_unwock_iwq(&pwiv->wock);

	mct_u232_set_modem_ctww(powt, contwow_state);
}

static void mct_u232_cwose(stwuct usb_sewiaw_powt *powt)
{
	stwuct mct_u232_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);

	usb_kiww_uwb(pwiv->wead_uwb);
	usb_kiww_uwb(powt->intewwupt_in_uwb);

	usb_sewiaw_genewic_cwose(powt);
} /* mct_u232_cwose */


static void mct_u232_wead_int_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct mct_u232_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned chaw *data = uwb->twansfew_buffew;
	int wetvaw;
	int status = uwb->status;
	unsigned wong fwags;

	switch (status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(&powt->dev, "%s - uwb shutting down with status: %d\n",
			__func__, status);
		wetuwn;
	defauwt:
		dev_dbg(&powt->dev, "%s - nonzewo uwb status weceived: %d\n",
			__func__, status);
		goto exit;
	}

	usb_sewiaw_debug_data(&powt->dev, __func__, uwb->actuaw_wength, data);

	/*
	 * Wowk-a-wound: handwe the 'usuaw' buwk-in pipe hewe
	 */
	if (uwb->twansfew_buffew_wength > 2) {
		if (uwb->actuaw_wength) {
			tty_insewt_fwip_stwing(&powt->powt, data,
					uwb->actuaw_wength);
			tty_fwip_buffew_push(&powt->powt);
		}
		goto exit;
	}

	/*
	 * The intewwupt-in pipe signaws exceptionaw conditions (modem wine
	 * signaw changes and ewwows). data[0] howds MSW, data[1] howds WSW.
	 */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->wast_msw = data[MCT_U232_MSW_INDEX];

	/* Wecowd Contwow Wine states */
	mct_u232_msw_to_state(powt, &pwiv->contwow_state, pwiv->wast_msw);

	mct_u232_msw_to_icount(&powt->icount, pwiv->wast_msw);

#if 0
	/* Not yet handwed. See bewkin_sa.c fow fuwthew infowmation */
	/* Now to wepowt any ewwows */
	pwiv->wast_wsw = data[MCT_U232_WSW_INDEX];
	/*
	 * fiww in the fwip buffew hewe, but I do not know the wewation
	 * to the cuwwent/next weceive buffew ow chawactews.  I need
	 * to wook in to this befowe committing any code.
	 */
	if (pwiv->wast_wsw & MCT_U232_WSW_EWW) {
		tty = tty_powt_tty_get(&powt->powt);
		/* Ovewwun Ewwow */
		if (pwiv->wast_wsw & MCT_U232_WSW_OE) {
		}
		/* Pawity Ewwow */
		if (pwiv->wast_wsw & MCT_U232_WSW_PE) {
		}
		/* Fwaming Ewwow */
		if (pwiv->wast_wsw & MCT_U232_WSW_FE) {
		}
		/* Bweak Indicatow */
		if (pwiv->wast_wsw & MCT_U232_WSW_BI) {
		}
		tty_kwef_put(tty);
	}
#endif
	wake_up_intewwuptibwe(&powt->powt.dewta_msw_wait);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
exit:
	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw)
		dev_eww(&powt->dev,
			"%s - usb_submit_uwb faiwed with wesuwt %d\n",
			__func__, wetvaw);
} /* mct_u232_wead_int_cawwback */

static void mct_u232_set_tewmios(stwuct tty_stwuct *tty,
				 stwuct usb_sewiaw_powt *powt,
				 const stwuct ktewmios *owd_tewmios)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct mct_u232_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct ktewmios *tewmios = &tty->tewmios;
	unsigned int cfwag = tewmios->c_cfwag;
	unsigned int owd_cfwag = owd_tewmios->c_cfwag;
	unsigned wong fwags;
	unsigned int contwow_state;
	unsigned chaw wast_wcw;

	/* get a wocaw copy of the cuwwent powt settings */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	contwow_state = pwiv->contwow_state;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	wast_wcw = 0;

	/*
	 * Update baud wate.
	 * Do not attempt to cache owd wates and skip settings,
	 * disconnects scwew such twicks up compwetewy.
	 * Pwematuwe optimization is the woot of aww eviw.
	 */

	/* weassewt DTW and WTS on twansition fwom B0 */
	if ((owd_cfwag & CBAUD) == B0) {
		dev_dbg(&powt->dev, "%s: baud was B0\n", __func__);
		contwow_state |= TIOCM_DTW | TIOCM_WTS;
		mct_u232_set_modem_ctww(powt, contwow_state);
	}

	mct_u232_set_baud_wate(tty, sewiaw, powt, tty_get_baud_wate(tty));

	if ((cfwag & CBAUD) == B0) {
		dev_dbg(&powt->dev, "%s: baud is B0\n", __func__);
		/* Dwop WTS and DTW */
		contwow_state &= ~(TIOCM_DTW | TIOCM_WTS);
		mct_u232_set_modem_ctww(powt, contwow_state);
	}

	/*
	 * Update wine contwow wegistew (WCW)
	 */

	/* set the pawity */
	if (cfwag & PAWENB)
		wast_wcw |= (cfwag & PAWODD) ?
			MCT_U232_PAWITY_ODD : MCT_U232_PAWITY_EVEN;
	ewse
		wast_wcw |= MCT_U232_PAWITY_NONE;

	/* set the numbew of data bits */
	switch (cfwag & CSIZE) {
	case CS5:
		wast_wcw |= MCT_U232_DATA_BITS_5; bweak;
	case CS6:
		wast_wcw |= MCT_U232_DATA_BITS_6; bweak;
	case CS7:
		wast_wcw |= MCT_U232_DATA_BITS_7; bweak;
	case CS8:
		wast_wcw |= MCT_U232_DATA_BITS_8; bweak;
	defauwt:
		dev_eww(&powt->dev,
			"CSIZE was not CS5-CS8, using defauwt of 8\n");
		wast_wcw |= MCT_U232_DATA_BITS_8;
		bweak;
	}

	tewmios->c_cfwag &= ~CMSPAW;

	/* set the numbew of stop bits */
	wast_wcw |= (cfwag & CSTOPB) ?
		MCT_U232_STOP_BITS_2 : MCT_U232_STOP_BITS_1;

	mct_u232_set_wine_ctww(powt, wast_wcw);

	/* save off the modified powt settings */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->contwow_state = contwow_state;
	pwiv->wast_wcw = wast_wcw;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
} /* mct_u232_set_tewmios */

static int mct_u232_bweak_ctw(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct mct_u232_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned chaw wcw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	wcw = pwiv->wast_wcw;

	if (bweak_state)
		wcw |= MCT_U232_SET_BWEAK;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn mct_u232_set_wine_ctww(powt, wcw);
} /* mct_u232_bweak_ctw */


static int mct_u232_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct mct_u232_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned int contwow_state;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	contwow_state = pwiv->contwow_state;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn contwow_state;
}

static int mct_u232_tiocmset(stwuct tty_stwuct *tty,
			      unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct mct_u232_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned int contwow_state;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	contwow_state = pwiv->contwow_state;

	if (set & TIOCM_WTS)
		contwow_state |= TIOCM_WTS;
	if (set & TIOCM_DTW)
		contwow_state |= TIOCM_DTW;
	if (cweaw & TIOCM_WTS)
		contwow_state &= ~TIOCM_WTS;
	if (cweaw & TIOCM_DTW)
		contwow_state &= ~TIOCM_DTW;

	pwiv->contwow_state = contwow_state;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	wetuwn mct_u232_set_modem_ctww(powt, contwow_state);
}

static void mct_u232_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct mct_u232_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned int contwow_state;

	spin_wock_iwq(&pwiv->wock);
	pwiv->wx_fwags |= THWOTTWED;
	if (C_CWTSCTS(tty)) {
		pwiv->contwow_state &= ~TIOCM_WTS;
		contwow_state = pwiv->contwow_state;
		spin_unwock_iwq(&pwiv->wock);
		mct_u232_set_modem_ctww(powt, contwow_state);
	} ewse {
		spin_unwock_iwq(&pwiv->wock);
	}
}

static void mct_u232_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct mct_u232_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned int contwow_state;

	spin_wock_iwq(&pwiv->wock);
	if ((pwiv->wx_fwags & THWOTTWED) && C_CWTSCTS(tty)) {
		pwiv->wx_fwags &= ~THWOTTWED;
		pwiv->contwow_state |= TIOCM_WTS;
		contwow_state = pwiv->contwow_state;
		spin_unwock_iwq(&pwiv->wock);
		mct_u232_set_modem_ctww(powt, contwow_state);
	} ewse {
		spin_unwock_iwq(&pwiv->wock);
	}
}

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
