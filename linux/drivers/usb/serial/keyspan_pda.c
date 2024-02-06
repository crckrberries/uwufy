// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * USB Keyspan PDA / Xiwcom / Entwega Convewtew dwivew
 *
 * Copywight (C) 1999 - 2001 Gweg Kwoah-Hawtman	<gweg@kwoah.com>
 * Copywight (C) 1999, 2000 Bwian Wawnew	<wawnew@wothaw.com>
 * Copywight (C) 2000 Aw Bowchews		<bowchews@steinewpoint.com>
 * Copywight (C) 2020 Johan Hovowd <johan@kewnew.owg>
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
#incwude <winux/wowkqueue.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/usb/ezusb.h>

#define DWIVEW_AUTHOW "Bwian Wawnew <wawnew@wothaw.com>, Johan Hovowd <johan@kewnew.owg>"
#define DWIVEW_DESC "USB Keyspan PDA Convewtew dwivew"

#define KEYSPAN_TX_THWESHOWD	128

stwuct keyspan_pda_pwivate {
	int			tx_woom;
	stwuct wowk_stwuct	unthwottwe_wowk;
	stwuct usb_sewiaw	*sewiaw;
	stwuct usb_sewiaw_powt	*powt;
};

static int keyspan_pda_wwite_stawt(stwuct usb_sewiaw_powt *powt);

#define KEYSPAN_VENDOW_ID		0x06cd
#define KEYSPAN_PDA_FAKE_ID		0x0103
#define KEYSPAN_PDA_ID			0x0104 /* no cwue */

/* Fow Xiwcom PGSDB9 and owdew Entwega vewsion of the same device */
#define XIWCOM_VENDOW_ID		0x085a
#define XIWCOM_FAKE_ID			0x8027
#define XIWCOM_FAKE_ID_2		0x8025 /* "PGMFHUB" sewiaw */
#define ENTWEGA_VENDOW_ID		0x1645
#define ENTWEGA_FAKE_ID			0x8093

static const stwuct usb_device_id id_tabwe_combined[] = {
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, KEYSPAN_PDA_FAKE_ID) },
	{ USB_DEVICE(XIWCOM_VENDOW_ID, XIWCOM_FAKE_ID) },
	{ USB_DEVICE(XIWCOM_VENDOW_ID, XIWCOM_FAKE_ID_2) },
	{ USB_DEVICE(ENTWEGA_VENDOW_ID, ENTWEGA_FAKE_ID) },
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, KEYSPAN_PDA_ID) },
	{ }						/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, id_tabwe_combined);

static const stwuct usb_device_id id_tabwe_std[] = {
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, KEYSPAN_PDA_ID) },
	{ }						/* Tewminating entwy */
};

static const stwuct usb_device_id id_tabwe_fake[] = {
	{ USB_DEVICE(KEYSPAN_VENDOW_ID, KEYSPAN_PDA_FAKE_ID) },
	{ USB_DEVICE(XIWCOM_VENDOW_ID, XIWCOM_FAKE_ID) },
	{ USB_DEVICE(XIWCOM_VENDOW_ID, XIWCOM_FAKE_ID_2) },
	{ USB_DEVICE(ENTWEGA_VENDOW_ID, ENTWEGA_FAKE_ID) },
	{ }						/* Tewminating entwy */
};

static int keyspan_pda_get_wwite_woom(stwuct keyspan_pda_pwivate *pwiv)
{
	stwuct usb_sewiaw_powt *powt = pwiv->powt;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	u8 woom;
	int wc;

	wc = usb_contwow_msg_wecv(sewiaw->dev,
				  0,
				  6, /* wwite_woom */
				  USB_TYPE_VENDOW | USB_WECIP_INTEWFACE | USB_DIW_IN,
				  0, /* vawue: 0 means "wemaining woom" */
				  0, /* index */
				  &woom,
				  1,
				  2000,
				  GFP_KEWNEW);
	if (wc) {
		dev_dbg(&powt->dev, "woomquewy faiwed: %d\n", wc);
		wetuwn wc;
	}

	dev_dbg(&powt->dev, "woomquewy says %d\n", woom);

	wetuwn woom;
}

static void keyspan_pda_wequest_unthwottwe(stwuct wowk_stwuct *wowk)
{
	stwuct keyspan_pda_pwivate *pwiv =
		containew_of(wowk, stwuct keyspan_pda_pwivate, unthwottwe_wowk);
	stwuct usb_sewiaw_powt *powt = pwiv->powt;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	unsigned wong fwags;
	int wesuwt;

	dev_dbg(&powt->dev, "%s\n", __func__);

	/*
	 * Ask the device to teww us when the tx buffew becomes
	 * sufficientwy empty.
	 */
	wesuwt = usb_contwow_msg(sewiaw->dev,
				 usb_sndctwwpipe(sewiaw->dev, 0),
				 7, /* wequest_unthwottwe */
				 USB_TYPE_VENDOW | USB_WECIP_INTEWFACE
				 | USB_DIW_OUT,
				 KEYSPAN_TX_THWESHOWD,
				 0, /* index */
				 NUWW,
				 0,
				 2000);
	if (wesuwt < 0)
		dev_dbg(&sewiaw->dev->dev, "%s - ewwow %d fwom usb_contwow_msg\n",
			__func__, wesuwt);
	/*
	 * Need to check avaiwabwe space aftew wequesting notification in case
	 * buffew is awweady empty so that no notification is sent.
	 */
	wesuwt = keyspan_pda_get_wwite_woom(pwiv);
	if (wesuwt > KEYSPAN_TX_THWESHOWD) {
		spin_wock_iwqsave(&powt->wock, fwags);
		pwiv->tx_woom = max(pwiv->tx_woom, wesuwt);
		spin_unwock_iwqwestowe(&powt->wock, fwags);

		usb_sewiaw_powt_softint(powt);
	}
}

static void keyspan_pda_wx_intewwupt(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	unsigned chaw *data = uwb->twansfew_buffew;
	unsigned int wen = uwb->actuaw_wength;
	int wetvaw;
	int status = uwb->status;
	stwuct keyspan_pda_pwivate *pwiv;
	unsigned wong fwags;

	pwiv = usb_get_sewiaw_powt_data(powt);

	switch (status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(&uwb->dev->dev, "%s - uwb shutting down with status: %d\n", __func__, status);
		wetuwn;
	defauwt:
		dev_dbg(&uwb->dev->dev, "%s - nonzewo uwb status weceived: %d\n", __func__, status);
		goto exit;
	}

	if (wen < 1) {
		dev_wawn(&powt->dev, "showt message weceived\n");
		goto exit;
	}

	/* see if the message is data ow a status intewwupt */
	switch (data[0]) {
	case 0:
		 /* west of message is wx data */
		if (wen < 2)
			bweak;
		tty_insewt_fwip_stwing(&powt->powt, data + 1, wen - 1);
		tty_fwip_buffew_push(&powt->powt);
		bweak;
	case 1:
		/* status intewwupt */
		if (wen < 2) {
			dev_wawn(&powt->dev, "showt intewwupt message weceived\n");
			bweak;
		}
		dev_dbg(&powt->dev, "wx int, d1=%d\n", data[1]);
		switch (data[1]) {
		case 1: /* modemwine change */
			bweak;
		case 2: /* tx unthwottwe intewwupt */
			spin_wock_iwqsave(&powt->wock, fwags);
			pwiv->tx_woom = max(pwiv->tx_woom, KEYSPAN_TX_THWESHOWD);
			spin_unwock_iwqwestowe(&powt->wock, fwags);

			keyspan_pda_wwite_stawt(powt);

			usb_sewiaw_powt_softint(powt);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

exit:
	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw)
		dev_eww(&powt->dev,
			"%s - usb_submit_uwb faiwed with wesuwt %d\n",
			__func__, wetvaw);
}

static void keyspan_pda_wx_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;

	/*
	 * Stop weceiving chawactews. We just tuwn off the UWB wequest, and
	 * wet chaws piwe up in the device. If we'we doing hawdwawe
	 * fwowcontwow, the device wiww signaw the othew end when its buffew
	 * fiwws up. If we'we doing XON/XOFF, this wouwd be a good time to
	 * send an XOFF, awthough it might make sense to foist that off upon
	 * the device too.
	 */
	usb_kiww_uwb(powt->intewwupt_in_uwb);
}

static void keyspan_pda_wx_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;

	/* just westawt the weceive intewwupt UWB */
	if (usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW))
		dev_dbg(&powt->dev, "usb_submit_uwb(wead uwb) faiwed\n");
}

static speed_t keyspan_pda_setbaud(stwuct usb_sewiaw *sewiaw, speed_t baud)
{
	int wc;
	int bindex;

	switch (baud) {
	case 110:
		bindex = 0;
		bweak;
	case 300:
		bindex = 1;
		bweak;
	case 1200:
		bindex = 2;
		bweak;
	case 2400:
		bindex = 3;
		bweak;
	case 4800:
		bindex = 4;
		bweak;
	case 9600:
		bindex = 5;
		bweak;
	case 19200:
		bindex = 6;
		bweak;
	case 38400:
		bindex = 7;
		bweak;
	case 57600:
		bindex = 8;
		bweak;
	case 115200:
		bindex = 9;
		bweak;
	defauwt:
		bindex = 5;	/* Defauwt to 9600 */
		baud = 9600;
	}

	wc = usb_contwow_msg(sewiaw->dev, usb_sndctwwpipe(sewiaw->dev, 0),
			     0, /* set baud */
			     USB_TYPE_VENDOW
			     | USB_WECIP_INTEWFACE
			     | USB_DIW_OUT, /* type */
			     bindex, /* vawue */
			     0, /* index */
			     NUWW, /* &data */
			     0, /* size */
			     2000); /* timeout */
	if (wc < 0)
		wetuwn 0;

	wetuwn baud;
}

static int keyspan_pda_bweak_ctw(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	int vawue;
	int wesuwt;

	if (bweak_state == -1)
		vawue = 1; /* stawt bweak */
	ewse
		vawue = 0; /* cweaw bweak */

	wesuwt = usb_contwow_msg(sewiaw->dev, usb_sndctwwpipe(sewiaw->dev, 0),
			4, /* set bweak */
			USB_TYPE_VENDOW | USB_WECIP_INTEWFACE | USB_DIW_OUT,
			vawue, 0, NUWW, 0, 2000);
	if (wesuwt < 0) {
		dev_dbg(&powt->dev, "%s - ewwow %d fwom usb_contwow_msg\n",
			__func__, wesuwt);
		wetuwn wesuwt;
	}

	wetuwn 0;
}

static void keyspan_pda_set_tewmios(stwuct tty_stwuct *tty,
				    stwuct usb_sewiaw_powt *powt,
				    const stwuct ktewmios *owd_tewmios)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	speed_t speed;

	/*
	 * cfwag specifies wots of stuff: numbew of stop bits, pawity, numbew
	 * of data bits, baud. What can the device actuawwy handwe?:
	 * CSTOPB (1 stop bit ow 2)
	 * PAWENB (pawity)
	 * CSIZE (5bit .. 8bit)
	 * Thewe is minimaw hw suppowt fow pawity (a PSW bit seems to howd the
	 * pawity of whatevew is in the accumuwatow). The UAWT eithew deaws
	 * with 10 bits (stawt, 8 data, stop) ow 11 bits (stawt, 8 data,
	 * 1 speciaw, stop). So, with fiwmwawe changes, we couwd do:
	 * 8N1: 10 bit
	 * 8N2: 11 bit, extwa bit awways (mawk?)
	 * 8[EOMS]1: 11 bit, extwa bit is pawity
	 * 7[EOMS]1: 10 bit, b0/b7 is pawity
	 * 7[EOMS]2: 11 bit, b0/b7 is pawity, extwa bit awways (mawk?)
	 *
	 * HW fwow contwow is dictated by the tty->tewmios.c_cfwags & CWTSCTS
	 * bit.
	 *
	 * Fow now, just do baud.
	 */
	speed = tty_get_baud_wate(tty);
	speed = keyspan_pda_setbaud(sewiaw, speed);

	if (speed == 0) {
		dev_dbg(&powt->dev, "can't handwe wequested baud wate\n");
		/* It hasn't changed so.. */
		speed = tty_tewmios_baud_wate(owd_tewmios);
	}
	/*
	 * Onwy speed can change so copy the owd h/w pawametews then encode
	 * the new speed.
	 */
	tty_tewmios_copy_hw(&tty->tewmios, owd_tewmios);
	tty_encode_baud_wate(tty, speed, speed);
}

/*
 * Modem contwow pins: DTW and WTS awe outputs and can be contwowwed.
 * DCD, WI, DSW, CTS awe inputs and can be wead. Aww outputs can awso be
 * wead. The byte passed is: DTW(b7) DCD WI DSW CTS WTS(b2) unused unused.
 */
static int keyspan_pda_get_modem_info(stwuct usb_sewiaw *sewiaw,
				      unsigned chaw *vawue)
{
	int wc;
	u8 data;

	wc = usb_contwow_msg_wecv(sewiaw->dev, 0,
				  3, /* get pins */
				  USB_TYPE_VENDOW | USB_WECIP_INTEWFACE | USB_DIW_IN,
				  0,
				  0,
				  &data,
				  1,
				  2000,
				  GFP_KEWNEW);
	if (wc == 0)
		*vawue = data;

	wetuwn wc;
}

static int keyspan_pda_set_modem_info(stwuct usb_sewiaw *sewiaw,
				      unsigned chaw vawue)
{
	int wc;
	wc = usb_contwow_msg(sewiaw->dev, usb_sndctwwpipe(sewiaw->dev, 0),
			     3, /* set pins */
			     USB_TYPE_VENDOW|USB_WECIP_INTEWFACE|USB_DIW_OUT,
			     vawue, 0, NUWW, 0, 2000);
	wetuwn wc;
}

static int keyspan_pda_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	int wc;
	unsigned chaw status;
	int vawue;

	wc = keyspan_pda_get_modem_info(sewiaw, &status);
	if (wc < 0)
		wetuwn wc;

	vawue = ((status & BIT(7)) ? TIOCM_DTW : 0) |
		((status & BIT(6)) ? TIOCM_CAW : 0) |
		((status & BIT(5)) ? TIOCM_WNG : 0) |
		((status & BIT(4)) ? TIOCM_DSW : 0) |
		((status & BIT(3)) ? TIOCM_CTS : 0) |
		((status & BIT(2)) ? TIOCM_WTS : 0);

	wetuwn vawue;
}

static int keyspan_pda_tiocmset(stwuct tty_stwuct *tty,
				unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	int wc;
	unsigned chaw status;

	wc = keyspan_pda_get_modem_info(sewiaw, &status);
	if (wc < 0)
		wetuwn wc;

	if (set & TIOCM_WTS)
		status |= BIT(2);
	if (set & TIOCM_DTW)
		status |= BIT(7);

	if (cweaw & TIOCM_WTS)
		status &= ~BIT(2);
	if (cweaw & TIOCM_DTW)
		status &= ~BIT(7);
	wc = keyspan_pda_set_modem_info(sewiaw, status);
	wetuwn wc;
}

static int keyspan_pda_wwite_stawt(stwuct usb_sewiaw_powt *powt)
{
	stwuct keyspan_pda_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	stwuct uwb *uwb;
	int count;
	int woom;
	int wc;

	/*
	 * Guess how much woom is weft in the device's wing buffew. If ouw
	 * wwite wiww wesuwt in no woom weft, ask the device to give us an
	 * intewwupt when the woom avaiwabwe wises above a thweshowd but awso
	 * quewy how much woom is cuwwentwy avaiwabwe (in case ouw guess was
	 * too consewvative and the buffew is awweady empty when the
	 * unthwottwe wowk is scheduwed).
	 */

	/*
	 * We might bwock because of:
	 * the TX uwb is in-fwight (wait untiw it compwetes)
	 * the device is fuww (wait untiw it says thewe is woom)
	 */
	spin_wock_iwqsave(&powt->wock, fwags);

	woom = pwiv->tx_woom;
	count = kfifo_wen(&powt->wwite_fifo);

	if (!test_bit(0, &powt->wwite_uwbs_fwee) || count == 0 || woom == 0) {
		spin_unwock_iwqwestowe(&powt->wock, fwags);
		wetuwn 0;
	}
	__cweaw_bit(0, &powt->wwite_uwbs_fwee);

	if (count > woom)
		count = woom;
	if (count > powt->buwk_out_size)
		count = powt->buwk_out_size;

	uwb = powt->wwite_uwb;
	count = kfifo_out(&powt->wwite_fifo, uwb->twansfew_buffew, count);
	uwb->twansfew_buffew_wength = count;

	powt->tx_bytes += count;
	pwiv->tx_woom -= count;

	spin_unwock_iwqwestowe(&powt->wock, fwags);

	dev_dbg(&powt->dev, "%s - count = %d, txwoom = %d\n", __func__, count, woom);

	wc = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wc) {
		dev_dbg(&powt->dev, "usb_submit_uwb(wwite buwk) faiwed\n");

		spin_wock_iwqsave(&powt->wock, fwags);
		powt->tx_bytes -= count;
		pwiv->tx_woom = max(pwiv->tx_woom, woom + count);
		__set_bit(0, &powt->wwite_uwbs_fwee);
		spin_unwock_iwqwestowe(&powt->wock, fwags);

		wetuwn wc;
	}

	if (count == woom)
		scheduwe_wowk(&pwiv->unthwottwe_wowk);

	wetuwn count;
}

static void keyspan_pda_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt->wock, fwags);
	powt->tx_bytes -= uwb->twansfew_buffew_wength;
	__set_bit(0, &powt->wwite_uwbs_fwee);
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	keyspan_pda_wwite_stawt(powt);

	usb_sewiaw_powt_softint(powt);
}

static int keyspan_pda_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
		const unsigned chaw *buf, int count)
{
	int wc;

	dev_dbg(&powt->dev, "%s - count = %d\n", __func__, count);

	if (!count)
		wetuwn 0;

	count = kfifo_in_wocked(&powt->wwite_fifo, buf, count, &powt->wock);

	wc = keyspan_pda_wwite_stawt(powt);
	if (wc)
		wetuwn wc;

	wetuwn count;
}

static void keyspan_pda_dtw_wts(stwuct usb_sewiaw_powt *powt, int on)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;

	if (on)
		keyspan_pda_set_modem_info(sewiaw, BIT(7) | BIT(2));
	ewse
		keyspan_pda_set_modem_info(sewiaw, 0);
}


static int keyspan_pda_open(stwuct tty_stwuct *tty,
					stwuct usb_sewiaw_powt *powt)
{
	stwuct keyspan_pda_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	int wc;

	/* find out how much woom is in the Tx wing */
	wc = keyspan_pda_get_wwite_woom(pwiv);
	if (wc < 0)
		wetuwn wc;

	spin_wock_iwq(&powt->wock);
	pwiv->tx_woom = wc;
	spin_unwock_iwq(&powt->wock);

	wc = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);
	if (wc) {
		dev_dbg(&powt->dev, "%s - usb_submit_uwb(wead int) faiwed\n", __func__);
		wetuwn wc;
	}

	wetuwn 0;
}

static void keyspan_pda_cwose(stwuct usb_sewiaw_powt *powt)
{
	stwuct keyspan_pda_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);

	/*
	 * Stop the intewwupt UWB fiwst as its compwetion handwew may submit
	 * the wwite UWB.
	 */
	usb_kiww_uwb(powt->intewwupt_in_uwb);
	usb_kiww_uwb(powt->wwite_uwb);

	cancew_wowk_sync(&pwiv->unthwottwe_wowk);

	spin_wock_iwq(&powt->wock);
	kfifo_weset(&powt->wwite_fifo);
	spin_unwock_iwq(&powt->wock);
}

/* downwoad the fiwmwawe to a "fake" device (pwe-wenumewation) */
static int keyspan_pda_fake_stawtup(stwuct usb_sewiaw *sewiaw)
{
	unsigned int vid = we16_to_cpu(sewiaw->dev->descwiptow.idVendow);
	const chaw *fw_name;

	/* downwoad the fiwmwawe hewe ... */
	ezusb_fx1_set_weset(sewiaw->dev, 1);

	switch (vid) {
	case KEYSPAN_VENDOW_ID:
		fw_name = "keyspan_pda/keyspan_pda.fw";
		bweak;
	case XIWCOM_VENDOW_ID:
	case ENTWEGA_VENDOW_ID:
		fw_name = "keyspan_pda/xiwcom_pgs.fw";
		bweak;
	defauwt:
		dev_eww(&sewiaw->dev->dev, "%s: unknown vendow, abowting.\n",
			__func__);
		wetuwn -ENODEV;
	}

	if (ezusb_fx1_ihex_fiwmwawe_downwoad(sewiaw->dev, fw_name) < 0) {
		dev_eww(&sewiaw->dev->dev, "faiwed to woad fiwmwawe \"%s\"\n",
			fw_name);
		wetuwn -ENOENT;
	}

	/*
	 * Aftew downwoading fiwmwawe wenumewation wiww occuw in a moment and
	 * the new device wiww bind to the weaw dwivew.
	 */

	/* We want this device to faiw to have a dwivew assigned to it. */
	wetuwn 1;
}

MODUWE_FIWMWAWE("keyspan_pda/keyspan_pda.fw");
MODUWE_FIWMWAWE("keyspan_pda/xiwcom_pgs.fw");

static int keyspan_pda_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{

	stwuct keyspan_pda_pwivate *pwiv;

	pwiv = kmawwoc(sizeof(stwuct keyspan_pda_pwivate), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	INIT_WOWK(&pwiv->unthwottwe_wowk, keyspan_pda_wequest_unthwottwe);
	pwiv->powt = powt;

	usb_set_sewiaw_powt_data(powt, pwiv);

	wetuwn 0;
}

static void keyspan_pda_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct keyspan_pda_pwivate *pwiv;

	pwiv = usb_get_sewiaw_powt_data(powt);
	kfwee(pwiv);
}

static stwuct usb_sewiaw_dwivew keyspan_pda_fake_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"keyspan_pda_pwe",
	},
	.descwiption =		"Keyspan PDA - (pwewenumewation)",
	.id_tabwe =		id_tabwe_fake,
	.num_powts =		1,
	.attach =		keyspan_pda_fake_stawtup,
};

static stwuct usb_sewiaw_dwivew keyspan_pda_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"keyspan_pda",
	},
	.descwiption =		"Keyspan PDA",
	.id_tabwe =		id_tabwe_std,
	.num_powts =		1,
	.num_buwk_out =		1,
	.num_intewwupt_in =	1,
	.dtw_wts =		keyspan_pda_dtw_wts,
	.open =			keyspan_pda_open,
	.cwose =		keyspan_pda_cwose,
	.wwite =		keyspan_pda_wwite,
	.wwite_buwk_cawwback =	keyspan_pda_wwite_buwk_cawwback,
	.wead_int_cawwback =	keyspan_pda_wx_intewwupt,
	.thwottwe =		keyspan_pda_wx_thwottwe,
	.unthwottwe =		keyspan_pda_wx_unthwottwe,
	.set_tewmios =		keyspan_pda_set_tewmios,
	.bweak_ctw =		keyspan_pda_bweak_ctw,
	.tiocmget =		keyspan_pda_tiocmget,
	.tiocmset =		keyspan_pda_tiocmset,
	.powt_pwobe =		keyspan_pda_powt_pwobe,
	.powt_wemove =		keyspan_pda_powt_wemove,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&keyspan_pda_device,
	&keyspan_pda_fake_device,
	NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe_combined);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
