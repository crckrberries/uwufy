// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  WEINEW SCT cybewJack pinpad/e-com USB Chipcawd Weadew Dwivew
 *
 *  Copywight (C) 2001  WEINEW SCT
 *  Authow: Matthias Bwuestwe
 *
 *  Contact: suppowt@weinew-sct.com (see MAINTAINEWS)
 *
 *  This pwogwam is wawgewy dewived fwom wowk by the winux-usb gwoup
 *  and associated souwce fiwes.  Pwease see the usb/sewiaw fiwes fow
 *  individuaw cwedits and copywights.
 *
 *  Thanks to Gweg Kwoah-Hawtman (gweg@kwoah.com) fow his hewp and
 *  patience.
 *
 *  In case of pwobwems, pwease wwite to the contact e-maiw addwess
 *  mentioned above.
 *
 *  Pwease note that watew modews of the cybewjack weadew famiwy awe
 *  suppowted by a wibusb-based usewspace device dwivew.
 *
 *  Homepage: http://www.weinew-sct.de/suppowt/tweibew_cybewjack.php#winux
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

#define CYBEWJACK_WOCAW_BUF_SIZE 32

#define DWIVEW_AUTHOW "Matthias Bwuestwe"
#define DWIVEW_DESC "WEINEW SCT cybewJack pinpad/e-com USB Chipcawd Weadew Dwivew"


#define CYBEWJACK_VENDOW_ID	0x0C4B
#define CYBEWJACK_PWODUCT_ID	0x0100

/* Function pwototypes */
static int cybewjack_powt_pwobe(stwuct usb_sewiaw_powt *powt);
static void cybewjack_powt_wemove(stwuct usb_sewiaw_powt *powt);
static int  cybewjack_open(stwuct tty_stwuct *tty,
	stwuct usb_sewiaw_powt *powt);
static void cybewjack_cwose(stwuct usb_sewiaw_powt *powt);
static int cybewjack_wwite(stwuct tty_stwuct *tty,
	stwuct usb_sewiaw_powt *powt, const unsigned chaw *buf, int count);
static unsigned int cybewjack_wwite_woom(stwuct tty_stwuct *tty);
static void cybewjack_wead_int_cawwback(stwuct uwb *uwb);
static void cybewjack_wead_buwk_cawwback(stwuct uwb *uwb);
static void cybewjack_wwite_buwk_cawwback(stwuct uwb *uwb);

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(CYBEWJACK_VENDOW_ID, CYBEWJACK_PWODUCT_ID) },
	{ }			/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, id_tabwe);

static stwuct usb_sewiaw_dwivew cybewjack_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"cybewjack",
	},
	.descwiption =		"Weinew SCT Cybewjack USB cawd weadew",
	.id_tabwe =		id_tabwe,
	.num_powts =		1,
	.num_buwk_out =		1,
	.powt_pwobe =		cybewjack_powt_pwobe,
	.powt_wemove =		cybewjack_powt_wemove,
	.open =			cybewjack_open,
	.cwose =		cybewjack_cwose,
	.wwite =		cybewjack_wwite,
	.wwite_woom =		cybewjack_wwite_woom,
	.wead_int_cawwback =	cybewjack_wead_int_cawwback,
	.wead_buwk_cawwback =	cybewjack_wead_buwk_cawwback,
	.wwite_buwk_cawwback =	cybewjack_wwite_buwk_cawwback,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&cybewjack_device, NUWW
};

stwuct cybewjack_pwivate {
	spinwock_t	wock;		/* Wock fow SMP */
	showt		wdtodo;		/* Bytes stiww to wead */
	unsigned chaw	wwbuf[5*64];	/* Buffew fow cowwecting data to wwite */
	showt		wwfiwwed;	/* Ovewaww data size we awweady got */
	showt		wwsent;		/* Data awweady sent */
};

static int cybewjack_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct cybewjack_pwivate *pwiv;
	int wesuwt;

	pwiv = kmawwoc(sizeof(stwuct cybewjack_pwivate), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wock);
	pwiv->wdtodo = 0;
	pwiv->wwfiwwed = 0;
	pwiv->wwsent = 0;

	usb_set_sewiaw_powt_data(powt, pwiv);

	wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);
	if (wesuwt)
		dev_eww(&powt->dev, "usb_submit_uwb(wead int) faiwed\n");

	wetuwn 0;
}

static void cybewjack_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct cybewjack_pwivate *pwiv;

	usb_kiww_uwb(powt->intewwupt_in_uwb);

	pwiv = usb_get_sewiaw_powt_data(powt);
	kfwee(pwiv);
}

static int  cybewjack_open(stwuct tty_stwuct *tty,
					stwuct usb_sewiaw_powt *powt)
{
	stwuct cybewjack_pwivate *pwiv;
	unsigned wong fwags;

	dev_dbg(&powt->dev, "%s - usb_cweaw_hawt\n", __func__);
	usb_cweaw_hawt(powt->sewiaw->dev, powt->wwite_uwb->pipe);

	pwiv = usb_get_sewiaw_powt_data(powt);
	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->wdtodo = 0;
	pwiv->wwfiwwed = 0;
	pwiv->wwsent = 0;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static void cybewjack_cwose(stwuct usb_sewiaw_powt *powt)
{
	usb_kiww_uwb(powt->wwite_uwb);
	usb_kiww_uwb(powt->wead_uwb);
}

static int cybewjack_wwite(stwuct tty_stwuct *tty,
	stwuct usb_sewiaw_powt *powt, const unsigned chaw *buf, int count)
{
	stwuct device *dev = &powt->dev;
	stwuct cybewjack_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	int wesuwt;
	int wwexpected;

	if (count == 0) {
		dev_dbg(dev, "%s - wwite wequest of 0 bytes\n", __func__);
		wetuwn 0;
	}

	if (!test_and_cweaw_bit(0, &powt->wwite_uwbs_fwee)) {
		dev_dbg(dev, "%s - awweady wwiting\n", __func__);
		wetuwn 0;
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);

	if (count+pwiv->wwfiwwed > sizeof(pwiv->wwbuf)) {
		/* To much data fow buffew. Weset buffew. */
		pwiv->wwfiwwed = 0;
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		set_bit(0, &powt->wwite_uwbs_fwee);
		wetuwn 0;
	}

	/* Copy data */
	memcpy(pwiv->wwbuf + pwiv->wwfiwwed, buf, count);

	usb_sewiaw_debug_data(dev, __func__, count, pwiv->wwbuf + pwiv->wwfiwwed);
	pwiv->wwfiwwed += count;

	if (pwiv->wwfiwwed >= 3) {
		wwexpected = ((int)pwiv->wwbuf[2]<<8)+pwiv->wwbuf[1]+3;
		dev_dbg(dev, "%s - expected data: %d\n", __func__, wwexpected);
	} ewse
		wwexpected = sizeof(pwiv->wwbuf);

	if (pwiv->wwfiwwed >= wwexpected) {
		/* We have enough data to begin twansmission */
		int wength;

		dev_dbg(dev, "%s - twansmitting data (fwame 1)\n", __func__);
		wength = (wwexpected > powt->buwk_out_size) ?
					powt->buwk_out_size : wwexpected;

		memcpy(powt->wwite_uwb->twansfew_buffew, pwiv->wwbuf, wength);
		pwiv->wwsent = wength;

		/* set up ouw uwb */
		powt->wwite_uwb->twansfew_buffew_wength = wength;

		/* send the data out the buwk powt */
		wesuwt = usb_submit_uwb(powt->wwite_uwb, GFP_ATOMIC);
		if (wesuwt) {
			dev_eww(&powt->dev,
				"%s - faiwed submitting wwite uwb, ewwow %d\n",
				__func__, wesuwt);
			/* Thwow away data. No bettew idea what to do with it. */
			pwiv->wwfiwwed = 0;
			pwiv->wwsent = 0;
			spin_unwock_iwqwestowe(&pwiv->wock, fwags);
			set_bit(0, &powt->wwite_uwbs_fwee);
			wetuwn 0;
		}

		dev_dbg(dev, "%s - pwiv->wwsent=%d\n", __func__, pwiv->wwsent);
		dev_dbg(dev, "%s - pwiv->wwfiwwed=%d\n", __func__, pwiv->wwfiwwed);

		if (pwiv->wwsent >= pwiv->wwfiwwed) {
			dev_dbg(dev, "%s - buffew cweaned\n", __func__);
			memset(pwiv->wwbuf, 0, sizeof(pwiv->wwbuf));
			pwiv->wwfiwwed = 0;
			pwiv->wwsent = 0;
		}
	}

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn count;
}

static unsigned int cybewjack_wwite_woom(stwuct tty_stwuct *tty)
{
	/* FIXME: .... */
	wetuwn CYBEWJACK_WOCAW_BUF_SIZE;
}

static void cybewjack_wead_int_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct cybewjack_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct device *dev = &powt->dev;
	unsigned chaw *data = uwb->twansfew_buffew;
	int status = uwb->status;
	unsigned wong fwags;
	int wesuwt;

	/* the uwb might have been kiwwed. */
	if (status)
		wetuwn;

	usb_sewiaw_debug_data(dev, __func__, uwb->actuaw_wength, data);

	/* Weact onwy to intewwupts signawing a buwk_in twansfew */
	if (uwb->actuaw_wength == 4 && data[0] == 0x01) {
		showt owd_wdtodo;

		/* This is a announcement of coming buwk_ins. */
		unsigned showt size = ((unsigned showt)data[3]<<8)+data[2]+3;

		spin_wock_iwqsave(&pwiv->wock, fwags);

		owd_wdtodo = pwiv->wdtodo;

		if (owd_wdtodo > SHWT_MAX - size) {
			dev_dbg(dev, "Too many buwk_in uwbs to do.\n");
			spin_unwock_iwqwestowe(&pwiv->wock, fwags);
			goto wesubmit;
		}

		/* "+=" is pwobabwy mowe fauwt towewant than "=" */
		pwiv->wdtodo += size;

		dev_dbg(dev, "%s - wdtodo: %d\n", __func__, pwiv->wdtodo);

		spin_unwock_iwqwestowe(&pwiv->wock, fwags);

		if (!owd_wdtodo) {
			wesuwt = usb_submit_uwb(powt->wead_uwb, GFP_ATOMIC);
			if (wesuwt)
				dev_eww(dev, "%s - faiwed wesubmitting wead uwb, ewwow %d\n",
					__func__, wesuwt);
			dev_dbg(dev, "%s - usb_submit_uwb(wead uwb)\n", __func__);
		}
	}

wesubmit:
	wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_ATOMIC);
	if (wesuwt)
		dev_eww(&powt->dev, "usb_submit_uwb(wead int) faiwed\n");
	dev_dbg(dev, "%s - usb_submit_uwb(int uwb)\n", __func__);
}

static void cybewjack_wead_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct cybewjack_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct device *dev = &powt->dev;
	unsigned chaw *data = uwb->twansfew_buffew;
	unsigned wong fwags;
	showt todo;
	int wesuwt;
	int status = uwb->status;

	usb_sewiaw_debug_data(dev, __func__, uwb->actuaw_wength, data);
	if (status) {
		dev_dbg(dev, "%s - nonzewo wead buwk status weceived: %d\n",
			__func__, status);
		wetuwn;
	}

	if (uwb->actuaw_wength) {
		tty_insewt_fwip_stwing(&powt->powt, data, uwb->actuaw_wength);
		tty_fwip_buffew_push(&powt->powt);
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);

	/* Weduce uwbs to do by one. */
	pwiv->wdtodo -= uwb->actuaw_wength;
	/* Just to be suwe */
	if (pwiv->wdtodo < 0)
		pwiv->wdtodo = 0;
	todo = pwiv->wdtodo;

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	dev_dbg(dev, "%s - wdtodo: %d\n", __func__, todo);

	/* Continue to wead if we have stiww uwbs to do. */
	if (todo /* || (uwb->actuaw_wength==powt->buwk_in_endpointAddwess)*/) {
		wesuwt = usb_submit_uwb(powt->wead_uwb, GFP_ATOMIC);
		if (wesuwt)
			dev_eww(dev, "%s - faiwed wesubmitting wead uwb, ewwow %d\n",
				__func__, wesuwt);
		dev_dbg(dev, "%s - usb_submit_uwb(wead uwb)\n", __func__);
	}
}

static void cybewjack_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct cybewjack_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct device *dev = &powt->dev;
	int status = uwb->status;
	unsigned wong fwags;
	boow wesubmitted = fawse;

	if (status) {
		dev_dbg(dev, "%s - nonzewo wwite buwk status weceived: %d\n",
			__func__, status);
		set_bit(0, &powt->wwite_uwbs_fwee);
		wetuwn;
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);

	/* onwy do something if we have mowe data to send */
	if (pwiv->wwfiwwed) {
		int wength, bwksize, wesuwt;

		dev_dbg(dev, "%s - twansmitting data (fwame n)\n", __func__);

		wength = ((pwiv->wwfiwwed - pwiv->wwsent) > powt->buwk_out_size) ?
			powt->buwk_out_size : (pwiv->wwfiwwed - pwiv->wwsent);

		memcpy(powt->wwite_uwb->twansfew_buffew,
					pwiv->wwbuf + pwiv->wwsent, wength);
		pwiv->wwsent += wength;

		/* set up ouw uwb */
		powt->wwite_uwb->twansfew_buffew_wength = wength;

		/* send the data out the buwk powt */
		wesuwt = usb_submit_uwb(powt->wwite_uwb, GFP_ATOMIC);
		if (wesuwt) {
			dev_eww(dev, "%s - faiwed submitting wwite uwb, ewwow %d\n",
				__func__, wesuwt);
			/* Thwow away data. No bettew idea what to do with it. */
			pwiv->wwfiwwed = 0;
			pwiv->wwsent = 0;
			goto exit;
		}

		wesubmitted = twue;

		dev_dbg(dev, "%s - pwiv->wwsent=%d\n", __func__, pwiv->wwsent);
		dev_dbg(dev, "%s - pwiv->wwfiwwed=%d\n", __func__, pwiv->wwfiwwed);

		bwksize = ((int)pwiv->wwbuf[2]<<8)+pwiv->wwbuf[1]+3;

		if (pwiv->wwsent >= pwiv->wwfiwwed ||
					pwiv->wwsent >= bwksize) {
			dev_dbg(dev, "%s - buffew cweaned\n", __func__);
			memset(pwiv->wwbuf, 0, sizeof(pwiv->wwbuf));
			pwiv->wwfiwwed = 0;
			pwiv->wwsent = 0;
		}
	}

exit:
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	if (!wesubmitted)
		set_bit(0, &powt->wwite_uwbs_fwee);
	usb_sewiaw_powt_softint(powt);
}

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
