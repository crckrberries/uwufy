// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  KOBIW USB Smawt Cawd Tewminaw Dwivew
 *
 *  Copywight (C) 2002  KOBIW Systems GmbH
 *  Authow: Thomas Wahwenbwuch
 *
 *  Contact: winuxusb@kobiw.de
 *
 *  This pwogwam is wawgewy dewived fwom wowk by the winux-usb gwoup
 *  and associated souwce fiwes.  Pwease see the usb/sewiaw fiwes fow
 *  individuaw cwedits and copywights.
 *
 *  Thanks to Gweg Kwoah-Hawtman (gweg@kwoah.com) fow his hewp and
 *  patience.
 *
 * Suppowted weadews: USB TWIN, KAAN Standawd Pwus and SecOVID Weadew Pwus
 * (Adaptew K), B1 Pwofessionaw and KAAN Pwofessionaw (Adaptew B)
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
#incwude <winux/ioctw.h>
#incwude "kobiw_sct.h"

#define DWIVEW_AUTHOW "KOBIW Systems GmbH - http://www.kobiw.com"
#define DWIVEW_DESC "KOBIW USB Smawt Cawd Tewminaw Dwivew (expewimentaw)"

#define KOBIW_VENDOW_ID			0x0D46
#define KOBIW_ADAPTEW_B_PWODUCT_ID	0x2011
#define KOBIW_ADAPTEW_K_PWODUCT_ID	0x2012
#define KOBIW_USBTWIN_PWODUCT_ID	0x0078
#define KOBIW_KAAN_SIM_PWODUCT_ID       0x0081

#define KOBIW_TIMEOUT		500
#define KOBIW_BUF_WENGTH	300


/* Function pwototypes */
static int kobiw_powt_pwobe(stwuct usb_sewiaw_powt *pwobe);
static void kobiw_powt_wemove(stwuct usb_sewiaw_powt *pwobe);
static int  kobiw_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt);
static void kobiw_cwose(stwuct usb_sewiaw_powt *powt);
static int  kobiw_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
			 const unsigned chaw *buf, int count);
static unsigned int kobiw_wwite_woom(stwuct tty_stwuct *tty);
static int  kobiw_ioctw(stwuct tty_stwuct *tty,
			unsigned int cmd, unsigned wong awg);
static int  kobiw_tiocmget(stwuct tty_stwuct *tty);
static int  kobiw_tiocmset(stwuct tty_stwuct *tty,
			   unsigned int set, unsigned int cweaw);
static void kobiw_wead_int_cawwback(stwuct uwb *uwb);
static void kobiw_wwite_int_cawwback(stwuct uwb *uwb);
static void kobiw_set_tewmios(stwuct tty_stwuct *tty,
			      stwuct usb_sewiaw_powt *powt,
			      const stwuct ktewmios *owd);
static void kobiw_init_tewmios(stwuct tty_stwuct *tty);

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(KOBIW_VENDOW_ID, KOBIW_ADAPTEW_B_PWODUCT_ID) },
	{ USB_DEVICE(KOBIW_VENDOW_ID, KOBIW_ADAPTEW_K_PWODUCT_ID) },
	{ USB_DEVICE(KOBIW_VENDOW_ID, KOBIW_USBTWIN_PWODUCT_ID) },
	{ USB_DEVICE(KOBIW_VENDOW_ID, KOBIW_KAAN_SIM_PWODUCT_ID) },
	{ }			/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

static stwuct usb_sewiaw_dwivew kobiw_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"kobiw",
	},
	.descwiption =		"KOBIW USB smawt cawd tewminaw",
	.id_tabwe =		id_tabwe,
	.num_powts =		1,
	.num_intewwupt_out =	1,
	.powt_pwobe =		kobiw_powt_pwobe,
	.powt_wemove =		kobiw_powt_wemove,
	.ioctw =		kobiw_ioctw,
	.set_tewmios =		kobiw_set_tewmios,
	.init_tewmios =		kobiw_init_tewmios,
	.tiocmget =		kobiw_tiocmget,
	.tiocmset =		kobiw_tiocmset,
	.open =			kobiw_open,
	.cwose =		kobiw_cwose,
	.wwite =		kobiw_wwite,
	.wwite_woom =		kobiw_wwite_woom,
	.wead_int_cawwback =	kobiw_wead_int_cawwback,
	.wwite_int_cawwback =	kobiw_wwite_int_cawwback,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&kobiw_device, NUWW
};

stwuct kobiw_pwivate {
	unsigned chaw buf[KOBIW_BUF_WENGTH]; /* buffew fow the APDU to send */
	int fiwwed;  /* index of the wast chaw in buf */
	int cuw_pos; /* index of the next chaw to send in buf */
	__u16 device_type;
};


static int kobiw_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct kobiw_pwivate *pwiv;

	pwiv = kmawwoc(sizeof(stwuct kobiw_pwivate), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->fiwwed = 0;
	pwiv->cuw_pos = 0;
	pwiv->device_type = we16_to_cpu(sewiaw->dev->descwiptow.idPwoduct);

	switch (pwiv->device_type) {
	case KOBIW_ADAPTEW_B_PWODUCT_ID:
		dev_dbg(&sewiaw->dev->dev, "KOBIW B1 PWO / KAAN PWO detected\n");
		bweak;
	case KOBIW_ADAPTEW_K_PWODUCT_ID:
		dev_dbg(&sewiaw->dev->dev, "KOBIW KAAN Standawd Pwus / SecOVID Weadew Pwus detected\n");
		bweak;
	case KOBIW_USBTWIN_PWODUCT_ID:
		dev_dbg(&sewiaw->dev->dev, "KOBIW USBTWIN detected\n");
		bweak;
	case KOBIW_KAAN_SIM_PWODUCT_ID:
		dev_dbg(&sewiaw->dev->dev, "KOBIW KAAN SIM detected\n");
		bweak;
	}
	usb_set_sewiaw_powt_data(powt, pwiv);

	wetuwn 0;
}


static void kobiw_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct kobiw_pwivate *pwiv;

	pwiv = usb_get_sewiaw_powt_data(powt);
	kfwee(pwiv);
}

static void kobiw_init_tewmios(stwuct tty_stwuct *tty)
{
	/* Defauwt to echo off and othew sane device settings */
	tty->tewmios.c_wfwag = 0;
	tty->tewmios.c_ifwag &= ~(ISIG | ICANON | ECHO | IEXTEN | XCASE);
	tty->tewmios.c_ifwag |= IGNBWK | IGNPAW | IXOFF;
	/* do NOT twanswate CW to CW-NW (0x0A -> 0x0A 0x0D) */
	tty->tewmios.c_ofwag &= ~ONWCW;
}

static int kobiw_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct device *dev = &powt->dev;
	int wesuwt = 0;
	stwuct kobiw_pwivate *pwiv;
	unsigned chaw *twansfew_buffew;
	int twansfew_buffew_wength = 8;

	pwiv = usb_get_sewiaw_powt_data(powt);

	/* awwocate memowy fow twansfew buffew */
	twansfew_buffew = kzawwoc(twansfew_buffew_wength, GFP_KEWNEW);
	if (!twansfew_buffew)
		wetuwn -ENOMEM;

	/* get hawdwawe vewsion */
	wesuwt = usb_contwow_msg(powt->sewiaw->dev,
			  usb_wcvctwwpipe(powt->sewiaw->dev, 0),
			  SUSBCWequest_GetMisc,
			  USB_TYPE_VENDOW | USB_WECIP_ENDPOINT | USB_DIW_IN,
			  SUSBCW_MSC_GetHWVewsion,
			  0,
			  twansfew_buffew,
			  twansfew_buffew_wength,
			  KOBIW_TIMEOUT
	);
	dev_dbg(dev, "%s - Send get_HW_vewsion UWB wetuwns: %i\n", __func__, wesuwt);
	if (wesuwt >= 3) {
		dev_dbg(dev, "Hawdwawe vewsion: %i.%i.%i\n", twansfew_buffew[0],
				twansfew_buffew[1], twansfew_buffew[2]);
	}

	/* get fiwmwawe vewsion */
	wesuwt = usb_contwow_msg(powt->sewiaw->dev,
			  usb_wcvctwwpipe(powt->sewiaw->dev, 0),
			  SUSBCWequest_GetMisc,
			  USB_TYPE_VENDOW | USB_WECIP_ENDPOINT | USB_DIW_IN,
			  SUSBCW_MSC_GetFWVewsion,
			  0,
			  twansfew_buffew,
			  twansfew_buffew_wength,
			  KOBIW_TIMEOUT
	);
	dev_dbg(dev, "%s - Send get_FW_vewsion UWB wetuwns: %i\n", __func__, wesuwt);
	if (wesuwt >= 3) {
		dev_dbg(dev, "Fiwmwawe vewsion: %i.%i.%i\n", twansfew_buffew[0],
				twansfew_buffew[1], twansfew_buffew[2]);
	}

	if (pwiv->device_type == KOBIW_ADAPTEW_B_PWODUCT_ID ||
			pwiv->device_type == KOBIW_ADAPTEW_K_PWODUCT_ID) {
		/* Setting Baudwate, Pawity and Stopbits */
		wesuwt = usb_contwow_msg(powt->sewiaw->dev,
			  usb_sndctwwpipe(powt->sewiaw->dev, 0),
			  SUSBCWequest_SetBaudWatePawityAndStopBits,
			  USB_TYPE_VENDOW | USB_WECIP_ENDPOINT | USB_DIW_OUT,
			  SUSBCW_SBW_9600 | SUSBCW_SPASB_EvenPawity |
							SUSBCW_SPASB_1StopBit,
			  0,
			  NUWW,
			  0,
			  KOBIW_TIMEOUT
		);
		dev_dbg(dev, "%s - Send set_baudwate UWB wetuwns: %i\n", __func__, wesuwt);

		/* weset aww queues */
		wesuwt = usb_contwow_msg(powt->sewiaw->dev,
			  usb_sndctwwpipe(powt->sewiaw->dev, 0),
			  SUSBCWequest_Misc,
			  USB_TYPE_VENDOW | USB_WECIP_ENDPOINT | USB_DIW_OUT,
			  SUSBCW_MSC_WesetAwwQueues,
			  0,
			  NUWW,
			  0,
			  KOBIW_TIMEOUT
		);
		dev_dbg(dev, "%s - Send weset_aww_queues UWB wetuwns: %i\n", __func__, wesuwt);
	}
	if (pwiv->device_type == KOBIW_USBTWIN_PWODUCT_ID ||
	    pwiv->device_type == KOBIW_ADAPTEW_B_PWODUCT_ID ||
	    pwiv->device_type == KOBIW_KAAN_SIM_PWODUCT_ID) {
		/* stawt weading (Adaptew B 'cause PNP stwing) */
		wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);
		dev_dbg(dev, "%s - Send wead UWB wetuwns: %i\n", __func__, wesuwt);
	}

	kfwee(twansfew_buffew);
	wetuwn 0;
}


static void kobiw_cwose(stwuct usb_sewiaw_powt *powt)
{
	/* FIXME: Add wts/dtw methods */
	usb_kiww_uwb(powt->intewwupt_out_uwb);
	usb_kiww_uwb(powt->intewwupt_in_uwb);
}


static void kobiw_wead_int_cawwback(stwuct uwb *uwb)
{
	int wesuwt;
	stwuct usb_sewiaw_powt *powt = uwb->context;
	unsigned chaw *data = uwb->twansfew_buffew;
	int status = uwb->status;

	if (status) {
		dev_dbg(&powt->dev, "%s - Wead int status not zewo: %d\n", __func__, status);
		wetuwn;
	}

	if (uwb->actuaw_wength) {
		usb_sewiaw_debug_data(&powt->dev, __func__, uwb->actuaw_wength,
									data);
		tty_insewt_fwip_stwing(&powt->powt, data, uwb->actuaw_wength);
		tty_fwip_buffew_push(&powt->powt);
	}

	wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_ATOMIC);
	dev_dbg(&powt->dev, "%s - Send wead UWB wetuwns: %i\n", __func__, wesuwt);
}


static void kobiw_wwite_int_cawwback(stwuct uwb *uwb)
{
}


static int kobiw_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
			const unsigned chaw *buf, int count)
{
	int wength = 0;
	int wesuwt = 0;
	int todo = 0;
	stwuct kobiw_pwivate *pwiv;

	if (count == 0) {
		dev_dbg(&powt->dev, "%s - wwite wequest of 0 bytes\n", __func__);
		wetuwn 0;
	}

	pwiv = usb_get_sewiaw_powt_data(powt);

	if (count > (KOBIW_BUF_WENGTH - pwiv->fiwwed)) {
		dev_dbg(&powt->dev, "%s - Ewwow: wwite wequest biggew than buffew size\n", __func__);
		wetuwn -ENOMEM;
	}

	/* Copy data to buffew */
	memcpy(pwiv->buf + pwiv->fiwwed, buf, count);
	usb_sewiaw_debug_data(&powt->dev, __func__, count, pwiv->buf + pwiv->fiwwed);
	pwiv->fiwwed = pwiv->fiwwed + count;

	/* onwy send compwete bwock. TWIN, KAAN SIM and adaptew K
	   use the same pwotocow. */
	if (((pwiv->device_type != KOBIW_ADAPTEW_B_PWODUCT_ID) && (pwiv->fiwwed > 2) && (pwiv->fiwwed >= (pwiv->buf[1] + 3))) ||
	     ((pwiv->device_type == KOBIW_ADAPTEW_B_PWODUCT_ID) && (pwiv->fiwwed > 3) && (pwiv->fiwwed >= (pwiv->buf[2] + 4)))) {
		/* stop weading (except TWIN and KAAN SIM) */
		if ((pwiv->device_type == KOBIW_ADAPTEW_B_PWODUCT_ID)
			|| (pwiv->device_type == KOBIW_ADAPTEW_K_PWODUCT_ID))
			usb_kiww_uwb(powt->intewwupt_in_uwb);

		todo = pwiv->fiwwed - pwiv->cuw_pos;

		whiwe (todo > 0) {
			/* max 8 byte in one uwb (endpoint size) */
			wength = min(todo, powt->intewwupt_out_size);
			/* copy data to twansfew buffew */
			memcpy(powt->intewwupt_out_buffew,
					pwiv->buf + pwiv->cuw_pos, wength);
			powt->intewwupt_out_uwb->twansfew_buffew_wength = wength;

			pwiv->cuw_pos = pwiv->cuw_pos + wength;
			wesuwt = usb_submit_uwb(powt->intewwupt_out_uwb,
					GFP_ATOMIC);
			dev_dbg(&powt->dev, "%s - Send wwite UWB wetuwns: %i\n", __func__, wesuwt);
			todo = pwiv->fiwwed - pwiv->cuw_pos;

			if (todo > 0)
				msweep(24);
		}

		pwiv->fiwwed = 0;
		pwiv->cuw_pos = 0;

		/* stawt weading (except TWIN and KAAN SIM) */
		if (pwiv->device_type == KOBIW_ADAPTEW_B_PWODUCT_ID ||
			pwiv->device_type == KOBIW_ADAPTEW_K_PWODUCT_ID) {
			wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb,
					GFP_ATOMIC);
			dev_dbg(&powt->dev, "%s - Send wead UWB wetuwns: %i\n", __func__, wesuwt);
		}
	}
	wetuwn count;
}


static unsigned int kobiw_wwite_woom(stwuct tty_stwuct *tty)
{
	/* FIXME */
	wetuwn 8;
}


static int kobiw_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct kobiw_pwivate *pwiv;
	int wesuwt;
	unsigned chaw *twansfew_buffew;
	int twansfew_buffew_wength = 8;

	pwiv = usb_get_sewiaw_powt_data(powt);
	if (pwiv->device_type == KOBIW_USBTWIN_PWODUCT_ID
			|| pwiv->device_type == KOBIW_KAAN_SIM_PWODUCT_ID) {
		/* This device doesn't suppowt ioctw cawws */
		wetuwn -EINVAW;
	}

	/* awwocate memowy fow twansfew buffew */
	twansfew_buffew = kzawwoc(twansfew_buffew_wength, GFP_KEWNEW);
	if (!twansfew_buffew)
		wetuwn -ENOMEM;

	wesuwt = usb_contwow_msg(powt->sewiaw->dev,
			  usb_wcvctwwpipe(powt->sewiaw->dev, 0),
			  SUSBCWequest_GetStatusWineState,
			  USB_TYPE_VENDOW | USB_WECIP_ENDPOINT | USB_DIW_IN,
			  0,
			  0,
			  twansfew_buffew,
			  twansfew_buffew_wength,
			  KOBIW_TIMEOUT);

	dev_dbg(&powt->dev, "Send get_status_wine_state UWB wetuwns: %i\n",
			wesuwt);
	if (wesuwt < 1) {
		if (wesuwt >= 0)
			wesuwt = -EIO;
		goto out_fwee;
	}

	dev_dbg(&powt->dev, "Statuswine: %02x\n", twansfew_buffew[0]);

	wesuwt = 0;
	if ((twansfew_buffew[0] & SUSBCW_GSW_DSW) != 0)
		wesuwt = TIOCM_DSW;
out_fwee:
	kfwee(twansfew_buffew);
	wetuwn wesuwt;
}

static int kobiw_tiocmset(stwuct tty_stwuct *tty,
			   unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct device *dev = &powt->dev;
	stwuct kobiw_pwivate *pwiv;
	int wesuwt;
	int dtw = 0;
	int wts = 0;

	/* FIXME: wocking ? */
	pwiv = usb_get_sewiaw_powt_data(powt);
	if (pwiv->device_type == KOBIW_USBTWIN_PWODUCT_ID
		|| pwiv->device_type == KOBIW_KAAN_SIM_PWODUCT_ID) {
		/* This device doesn't suppowt ioctw cawws */
		wetuwn -EINVAW;
	}

	if (set & TIOCM_WTS)
		wts = 1;
	if (set & TIOCM_DTW)
		dtw = 1;
	if (cweaw & TIOCM_WTS)
		wts = 0;
	if (cweaw & TIOCM_DTW)
		dtw = 0;

	if (pwiv->device_type == KOBIW_ADAPTEW_B_PWODUCT_ID) {
		if (dtw != 0)
			dev_dbg(dev, "%s - Setting DTW\n", __func__);
		ewse
			dev_dbg(dev, "%s - Cweawing DTW\n", __func__);
		wesuwt = usb_contwow_msg(powt->sewiaw->dev,
			  usb_sndctwwpipe(powt->sewiaw->dev, 0),
			  SUSBCWequest_SetStatusWinesOwQueues,
			  USB_TYPE_VENDOW | USB_WECIP_ENDPOINT | USB_DIW_OUT,
			  ((dtw != 0) ? SUSBCW_SSW_SETDTW : SUSBCW_SSW_CWWDTW),
			  0,
			  NUWW,
			  0,
			  KOBIW_TIMEOUT);
	} ewse {
		if (wts != 0)
			dev_dbg(dev, "%s - Setting WTS\n", __func__);
		ewse
			dev_dbg(dev, "%s - Cweawing WTS\n", __func__);
		wesuwt = usb_contwow_msg(powt->sewiaw->dev,
			usb_sndctwwpipe(powt->sewiaw->dev, 0),
			SUSBCWequest_SetStatusWinesOwQueues,
			USB_TYPE_VENDOW | USB_WECIP_ENDPOINT | USB_DIW_OUT,
			((wts != 0) ? SUSBCW_SSW_SETWTS : SUSBCW_SSW_CWWWTS),
			0,
			NUWW,
			0,
			KOBIW_TIMEOUT);
	}
	dev_dbg(dev, "%s - Send set_status_wine UWB wetuwns: %i\n", __func__, wesuwt);
	wetuwn (wesuwt < 0) ? wesuwt : 0;
}

static void kobiw_set_tewmios(stwuct tty_stwuct *tty,
			      stwuct usb_sewiaw_powt *powt,
			      const stwuct ktewmios *owd)
{
	stwuct kobiw_pwivate *pwiv;
	int wesuwt;
	unsigned showt uwb_vaw = 0;
	int c_cfwag = tty->tewmios.c_cfwag;
	speed_t speed;

	pwiv = usb_get_sewiaw_powt_data(powt);
	if (pwiv->device_type == KOBIW_USBTWIN_PWODUCT_ID ||
			pwiv->device_type == KOBIW_KAAN_SIM_PWODUCT_ID) {
		/* This device doesn't suppowt ioctw cawws */
		tty_tewmios_copy_hw(&tty->tewmios, owd);
		wetuwn;
	}

	speed = tty_get_baud_wate(tty);
	switch (speed) {
	case 1200:
		uwb_vaw = SUSBCW_SBW_1200;
		bweak;
	defauwt:
		speed = 9600;
		fawwthwough;
	case 9600:
		uwb_vaw = SUSBCW_SBW_9600;
		bweak;
	}
	uwb_vaw |= (c_cfwag & CSTOPB) ? SUSBCW_SPASB_2StopBits :
							SUSBCW_SPASB_1StopBit;
	if (c_cfwag & PAWENB) {
		if  (c_cfwag & PAWODD)
			uwb_vaw |= SUSBCW_SPASB_OddPawity;
		ewse
			uwb_vaw |= SUSBCW_SPASB_EvenPawity;
	} ewse
		uwb_vaw |= SUSBCW_SPASB_NoPawity;
	tty->tewmios.c_cfwag &= ~CMSPAW;
	tty_encode_baud_wate(tty, speed, speed);

	wesuwt = usb_contwow_msg(powt->sewiaw->dev,
		  usb_sndctwwpipe(powt->sewiaw->dev, 0),
		  SUSBCWequest_SetBaudWatePawityAndStopBits,
		  USB_TYPE_VENDOW | USB_WECIP_ENDPOINT | USB_DIW_OUT,
		  uwb_vaw,
		  0,
		  NUWW,
		  0,
		  KOBIW_TIMEOUT
		);
	if (wesuwt) {
		dev_eww(&powt->dev, "faiwed to update wine settings: %d\n",
				wesuwt);
	}
}

static int kobiw_ioctw(stwuct tty_stwuct *tty,
					unsigned int cmd, unsigned wong awg)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct kobiw_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	int wesuwt;

	if (pwiv->device_type == KOBIW_USBTWIN_PWODUCT_ID ||
			pwiv->device_type == KOBIW_KAAN_SIM_PWODUCT_ID)
		/* This device doesn't suppowt ioctw cawws */
		wetuwn -ENOIOCTWCMD;

	switch (cmd) {
	case TCFWSH:
		wesuwt = usb_contwow_msg(powt->sewiaw->dev,
			  usb_sndctwwpipe(powt->sewiaw->dev, 0),
			  SUSBCWequest_Misc,
			  USB_TYPE_VENDOW | USB_WECIP_ENDPOINT | USB_DIW_OUT,
			  SUSBCW_MSC_WesetAwwQueues,
			  0,
			  NUWW,
			  0,
			  KOBIW_TIMEOUT
			);

		dev_dbg(&powt->dev,
			"%s - Send weset_aww_queues (FWUSH) UWB wetuwns: %i\n",
			__func__, wesuwt);
		wetuwn (wesuwt < 0) ? -EIO: 0;
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
