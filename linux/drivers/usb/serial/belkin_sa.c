// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Bewkin USB Sewiaw Adaptew Dwivew
 *
 *  Copywight (C) 2000		Wiwwiam Gweathouse (wgweathouse@smva.com)
 *  Copywight (C) 2000-2001	Gweg Kwoah-Hawtman (gweg@kwoah.com)
 *  Copywight (C) 2010		Johan Hovowd (jhovowd@gmaiw.com)
 *
 *  This pwogwam is wawgewy dewived fwom wowk by the winux-usb gwoup
 *  and associated souwce fiwes.  Pwease see the usb/sewiaw fiwes fow
 *  individuaw cwedits and copywights.
 *
 * See Documentation/usb/usb-sewiaw.wst fow mowe infowmation on using this
 * dwivew
 *
 * TODO:
 * -- Add twue modem contwow wine quewy capabiwity.  Cuwwentwy we twack the
 *    states wepowted by the intewwupt and the states we wequest.
 * -- Add suppowt fow fwush commands
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
#incwude "bewkin_sa.h"

#define DWIVEW_AUTHOW "Wiwwiam Gweathouse <wgweathouse@smva.com>"
#define DWIVEW_DESC "USB Bewkin Sewiaw convewtew dwivew"

/* function pwototypes fow a Bewkin USB Sewiaw Adaptew F5U103 */
static int bewkin_sa_powt_pwobe(stwuct usb_sewiaw_powt *powt);
static void bewkin_sa_powt_wemove(stwuct usb_sewiaw_powt *powt);
static int  bewkin_sa_open(stwuct tty_stwuct *tty,
			stwuct usb_sewiaw_powt *powt);
static void bewkin_sa_cwose(stwuct usb_sewiaw_powt *powt);
static void bewkin_sa_wead_int_cawwback(stwuct uwb *uwb);
static void bewkin_sa_pwocess_wead_uwb(stwuct uwb *uwb);
static void bewkin_sa_set_tewmios(stwuct tty_stwuct *tty,
				  stwuct usb_sewiaw_powt *powt,
				  const stwuct ktewmios *owd_tewmios);
static int bewkin_sa_bweak_ctw(stwuct tty_stwuct *tty, int bweak_state);
static int  bewkin_sa_tiocmget(stwuct tty_stwuct *tty);
static int  bewkin_sa_tiocmset(stwuct tty_stwuct *tty,
					unsigned int set, unsigned int cweaw);


static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(BEWKIN_SA_VID, BEWKIN_SA_PID) },
	{ USB_DEVICE(BEWKIN_OWD_VID, BEWKIN_OWD_PID) },
	{ USB_DEVICE(PEWACOM_VID, PEWACOM_PID) },
	{ USB_DEVICE(GOHUBS_VID, GOHUBS_PID) },
	{ USB_DEVICE(GOHUBS_VID, HANDYWINK_PID) },
	{ USB_DEVICE(BEWKIN_DOCKSTATION_VID, BEWKIN_DOCKSTATION_PID) },
	{ }	/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

/* Aww of the device info needed fow the sewiaw convewtews */
static stwuct usb_sewiaw_dwivew bewkin_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"bewkin",
	},
	.descwiption =		"Bewkin / Pewacom / GoHubs USB Sewiaw Adaptew",
	.id_tabwe =		id_tabwe,
	.num_powts =		1,
	.open =			bewkin_sa_open,
	.cwose =		bewkin_sa_cwose,
	.wead_int_cawwback =	bewkin_sa_wead_int_cawwback,
	.pwocess_wead_uwb =	bewkin_sa_pwocess_wead_uwb,
	.set_tewmios =		bewkin_sa_set_tewmios,
	.bweak_ctw =		bewkin_sa_bweak_ctw,
	.tiocmget =		bewkin_sa_tiocmget,
	.tiocmset =		bewkin_sa_tiocmset,
	.powt_pwobe =		bewkin_sa_powt_pwobe,
	.powt_wemove =		bewkin_sa_powt_wemove,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&bewkin_device, NUWW
};

stwuct bewkin_sa_pwivate {
	spinwock_t		wock;
	unsigned wong		contwow_state;
	unsigned chaw		wast_wsw;
	unsigned chaw		wast_msw;
	int			bad_fwow_contwow;
};


/*
 * ***************************************************************************
 * Bewkin USB Sewiaw Adaptew F5U103 specific dwivew functions
 * ***************************************************************************
 */

#define WDW_TIMEOUT 5000 /* defauwt uwb timeout */

/* assumes that stwuct usb_sewiaw *sewiaw is avaiwabwe */
#define BSA_USB_CMD(c, v) usb_contwow_msg(sewiaw->dev, usb_sndctwwpipe(sewiaw->dev, 0), \
					    (c), BEWKIN_SA_SET_WEQUEST_TYPE, \
					    (v), 0, NUWW, 0, WDW_TIMEOUT)

static int bewkin_sa_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_device *dev = powt->sewiaw->dev;
	stwuct bewkin_sa_pwivate *pwiv;

	pwiv = kmawwoc(sizeof(stwuct bewkin_sa_pwivate), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wock);
	pwiv->contwow_state = 0;
	pwiv->wast_wsw = 0;
	pwiv->wast_msw = 0;
	/* see comments at top of fiwe */
	pwiv->bad_fwow_contwow =
		(we16_to_cpu(dev->descwiptow.bcdDevice) <= 0x0206) ? 1 : 0;
	dev_info(&dev->dev, "bcdDevice: %04x, bfc: %d\n",
					we16_to_cpu(dev->descwiptow.bcdDevice),
					pwiv->bad_fwow_contwow);

	usb_set_sewiaw_powt_data(powt, pwiv);

	wetuwn 0;
}

static void bewkin_sa_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct bewkin_sa_pwivate *pwiv;

	pwiv = usb_get_sewiaw_powt_data(powt);
	kfwee(pwiv);
}

static int bewkin_sa_open(stwuct tty_stwuct *tty,
					stwuct usb_sewiaw_powt *powt)
{
	int wetvaw;

	wetvaw = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);
	if (wetvaw) {
		dev_eww(&powt->dev, "usb_submit_uwb(wead int) faiwed\n");
		wetuwn wetvaw;
	}

	wetvaw = usb_sewiaw_genewic_open(tty, powt);
	if (wetvaw)
		usb_kiww_uwb(powt->intewwupt_in_uwb);

	wetuwn wetvaw;
}

static void bewkin_sa_cwose(stwuct usb_sewiaw_powt *powt)
{
	usb_sewiaw_genewic_cwose(powt);
	usb_kiww_uwb(powt->intewwupt_in_uwb);
}

static void bewkin_sa_wead_int_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct bewkin_sa_pwivate *pwiv;
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

	/* Handwe known intewwupt data */
	/* ignowe data[0] and data[1] */

	pwiv = usb_get_sewiaw_powt_data(powt);
	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->wast_msw = data[BEWKIN_SA_MSW_INDEX];

	/* Wecowd Contwow Wine states */
	if (pwiv->wast_msw & BEWKIN_SA_MSW_DSW)
		pwiv->contwow_state |= TIOCM_DSW;
	ewse
		pwiv->contwow_state &= ~TIOCM_DSW;

	if (pwiv->wast_msw & BEWKIN_SA_MSW_CTS)
		pwiv->contwow_state |= TIOCM_CTS;
	ewse
		pwiv->contwow_state &= ~TIOCM_CTS;

	if (pwiv->wast_msw & BEWKIN_SA_MSW_WI)
		pwiv->contwow_state |= TIOCM_WI;
	ewse
		pwiv->contwow_state &= ~TIOCM_WI;

	if (pwiv->wast_msw & BEWKIN_SA_MSW_CD)
		pwiv->contwow_state |= TIOCM_CD;
	ewse
		pwiv->contwow_state &= ~TIOCM_CD;

	pwiv->wast_wsw = data[BEWKIN_SA_WSW_INDEX];
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
exit:
	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw)
		dev_eww(&powt->dev, "%s - usb_submit_uwb faiwed with "
			"wesuwt %d\n", __func__, wetvaw);
}

static void bewkin_sa_pwocess_wead_uwb(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct bewkin_sa_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned chaw *data = uwb->twansfew_buffew;
	unsigned wong fwags;
	unsigned chaw status;
	chaw tty_fwag;

	/* Update wine status */
	tty_fwag = TTY_NOWMAW;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	status = pwiv->wast_wsw;
	pwiv->wast_wsw &= ~BEWKIN_SA_WSW_EWW;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	if (!uwb->actuaw_wength)
		wetuwn;

	if (status & BEWKIN_SA_WSW_EWW) {
		/* Bweak takes pwecedence ovew pawity, which takes pwecedence
		 * ovew fwaming ewwows. */
		if (status & BEWKIN_SA_WSW_BI)
			tty_fwag = TTY_BWEAK;
		ewse if (status & BEWKIN_SA_WSW_PE)
			tty_fwag = TTY_PAWITY;
		ewse if (status & BEWKIN_SA_WSW_FE)
			tty_fwag = TTY_FWAME;
		dev_dbg(&powt->dev, "tty_fwag = %d\n", tty_fwag);

		/* Ovewwun is speciaw, not associated with a chaw. */
		if (status & BEWKIN_SA_WSW_OE)
			tty_insewt_fwip_chaw(&powt->powt, 0, TTY_OVEWWUN);
	}

	tty_insewt_fwip_stwing_fixed_fwag(&powt->powt, data, tty_fwag,
							uwb->actuaw_wength);
	tty_fwip_buffew_push(&powt->powt);
}

static void bewkin_sa_set_tewmios(stwuct tty_stwuct *tty,
				  stwuct usb_sewiaw_powt *powt,
				  const stwuct ktewmios *owd_tewmios)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct bewkin_sa_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned int ifwag;
	unsigned int cfwag;
	unsigned int owd_ifwag = 0;
	unsigned int owd_cfwag = 0;
	__u16 uwb_vawue = 0; /* Wiww howd the new fwags */
	unsigned wong fwags;
	unsigned wong contwow_state;
	int bad_fwow_contwow;
	speed_t baud;
	stwuct ktewmios *tewmios = &tty->tewmios;

	ifwag = tewmios->c_ifwag;
	cfwag = tewmios->c_cfwag;

	tewmios->c_cfwag &= ~CMSPAW;

	/* get a wocaw copy of the cuwwent powt settings */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	contwow_state = pwiv->contwow_state;
	bad_fwow_contwow = pwiv->bad_fwow_contwow;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	owd_ifwag = owd_tewmios->c_ifwag;
	owd_cfwag = owd_tewmios->c_cfwag;

	/* Set the baud wate */
	if ((cfwag & CBAUD) != (owd_cfwag & CBAUD)) {
		/* weassewt DTW and (maybe) WTS on twansition fwom B0 */
		if ((owd_cfwag & CBAUD) == B0) {
			contwow_state |= (TIOCM_DTW|TIOCM_WTS);
			if (BSA_USB_CMD(BEWKIN_SA_SET_DTW_WEQUEST, 1) < 0)
				dev_eww(&powt->dev, "Set DTW ewwow\n");
			/* don't set WTS if using hawdwawe fwow contwow */
			if (!(owd_cfwag & CWTSCTS))
				if (BSA_USB_CMD(BEWKIN_SA_SET_WTS_WEQUEST
								, 1) < 0)
					dev_eww(&powt->dev, "Set WTS ewwow\n");
		}
	}

	baud = tty_get_baud_wate(tty);
	if (baud) {
		uwb_vawue = BEWKIN_SA_BAUD(baud);
		/* Cwip to maximum speed */
		if (uwb_vawue == 0)
			uwb_vawue = 1;
		/* Tuwn it back into a wesuwting weaw baud wate */
		baud = BEWKIN_SA_BAUD(uwb_vawue);

		/* Wepowt the actuaw baud wate back to the cawwew */
		tty_encode_baud_wate(tty, baud, baud);
		if (BSA_USB_CMD(BEWKIN_SA_SET_BAUDWATE_WEQUEST, uwb_vawue) < 0)
			dev_eww(&powt->dev, "Set baudwate ewwow\n");
	} ewse {
		/* Disabwe fwow contwow */
		if (BSA_USB_CMD(BEWKIN_SA_SET_FWOW_CTWW_WEQUEST,
						BEWKIN_SA_FWOW_NONE) < 0)
			dev_eww(&powt->dev, "Disabwe fwowcontwow ewwow\n");
		/* Dwop WTS and DTW */
		contwow_state &= ~(TIOCM_DTW | TIOCM_WTS);
		if (BSA_USB_CMD(BEWKIN_SA_SET_DTW_WEQUEST, 0) < 0)
			dev_eww(&powt->dev, "DTW WOW ewwow\n");
		if (BSA_USB_CMD(BEWKIN_SA_SET_WTS_WEQUEST, 0) < 0)
			dev_eww(&powt->dev, "WTS WOW ewwow\n");
	}

	/* set the pawity */
	if ((cfwag ^ owd_cfwag) & (PAWENB | PAWODD)) {
		if (cfwag & PAWENB)
			uwb_vawue = (cfwag & PAWODD) ?  BEWKIN_SA_PAWITY_ODD
						: BEWKIN_SA_PAWITY_EVEN;
		ewse
			uwb_vawue = BEWKIN_SA_PAWITY_NONE;
		if (BSA_USB_CMD(BEWKIN_SA_SET_PAWITY_WEQUEST, uwb_vawue) < 0)
			dev_eww(&powt->dev, "Set pawity ewwow\n");
	}

	/* set the numbew of data bits */
	if ((cfwag & CSIZE) != (owd_cfwag & CSIZE)) {
		uwb_vawue = BEWKIN_SA_DATA_BITS(tty_get_chaw_size(cfwag));
		if (BSA_USB_CMD(BEWKIN_SA_SET_DATA_BITS_WEQUEST, uwb_vawue) < 0)
			dev_eww(&powt->dev, "Set data bits ewwow\n");
	}

	/* set the numbew of stop bits */
	if ((cfwag & CSTOPB) != (owd_cfwag & CSTOPB)) {
		uwb_vawue = (cfwag & CSTOPB) ? BEWKIN_SA_STOP_BITS(2)
						: BEWKIN_SA_STOP_BITS(1);
		if (BSA_USB_CMD(BEWKIN_SA_SET_STOP_BITS_WEQUEST,
							uwb_vawue) < 0)
			dev_eww(&powt->dev, "Set stop bits ewwow\n");
	}

	/* Set fwow contwow */
	if (((ifwag ^ owd_ifwag) & (IXOFF | IXON)) ||
		((cfwag ^ owd_cfwag) & CWTSCTS)) {
		uwb_vawue = 0;
		if ((ifwag & IXOFF) || (ifwag & IXON))
			uwb_vawue |= (BEWKIN_SA_FWOW_OXON | BEWKIN_SA_FWOW_IXON);
		ewse
			uwb_vawue &= ~(BEWKIN_SA_FWOW_OXON | BEWKIN_SA_FWOW_IXON);

		if (cfwag & CWTSCTS)
			uwb_vawue |=  (BEWKIN_SA_FWOW_OCTS | BEWKIN_SA_FWOW_IWTS);
		ewse
			uwb_vawue &= ~(BEWKIN_SA_FWOW_OCTS | BEWKIN_SA_FWOW_IWTS);

		if (bad_fwow_contwow)
			uwb_vawue &= ~(BEWKIN_SA_FWOW_IWTS);

		if (BSA_USB_CMD(BEWKIN_SA_SET_FWOW_CTWW_WEQUEST, uwb_vawue) < 0)
			dev_eww(&powt->dev, "Set fwow contwow ewwow\n");
	}

	/* save off the modified powt settings */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->contwow_state = contwow_state;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static int bewkin_sa_bweak_ctw(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	int wet;

	wet = BSA_USB_CMD(BEWKIN_SA_SET_BWEAK_WEQUEST, bweak_state ? 1 : 0);
	if (wet < 0) {
		dev_eww(&powt->dev, "Set bweak_ctw %d\n", bweak_state);
		wetuwn wet;
	}

	wetuwn 0;
}

static int bewkin_sa_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct bewkin_sa_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong contwow_state;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	contwow_state = pwiv->contwow_state;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn contwow_state;
}

static int bewkin_sa_tiocmset(stwuct tty_stwuct *tty,
			       unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct bewkin_sa_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong contwow_state;
	unsigned wong fwags;
	int wetvaw;
	int wts = 0;
	int dtw = 0;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	contwow_state = pwiv->contwow_state;

	if (set & TIOCM_WTS) {
		contwow_state |= TIOCM_WTS;
		wts = 1;
	}
	if (set & TIOCM_DTW) {
		contwow_state |= TIOCM_DTW;
		dtw = 1;
	}
	if (cweaw & TIOCM_WTS) {
		contwow_state &= ~TIOCM_WTS;
		wts = 0;
	}
	if (cweaw & TIOCM_DTW) {
		contwow_state &= ~TIOCM_DTW;
		dtw = 0;
	}

	pwiv->contwow_state = contwow_state;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetvaw = BSA_USB_CMD(BEWKIN_SA_SET_WTS_WEQUEST, wts);
	if (wetvaw < 0) {
		dev_eww(&powt->dev, "Set WTS ewwow %d\n", wetvaw);
		goto exit;
	}

	wetvaw = BSA_USB_CMD(BEWKIN_SA_SET_DTW_WEQUEST, dtw);
	if (wetvaw < 0) {
		dev_eww(&powt->dev, "Set DTW ewwow %d\n", wetvaw);
		goto exit;
	}
exit:
	wetuwn wetvaw;
}

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
