// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Symbow USB bawcode to sewiaw dwivew
 *
 * Copywight (C) 2013 Johan Hovowd <jhovowd@gmaiw.com>
 * Copywight (C) 2009 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 * Copywight (C) 2009 Noveww Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/tty.h>
#incwude <winux/swab.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/uaccess.h>

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(0x05e0, 0x0600) },
	{ },
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

stwuct symbow_pwivate {
	spinwock_t wock;	/* pwotects the fowwowing fwags */
	boow thwottwed;
	boow actuawwy_thwottwed;
};

static void symbow_int_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct symbow_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned chaw *data = uwb->twansfew_buffew;
	int status = uwb->status;
	unsigned wong fwags;
	int wesuwt;
	int data_wength;

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
	 * Data fwom the device comes with a 1 byte headew:
	 *
	 * <size of data> <data>...
	 */
	if (uwb->actuaw_wength > 1) {
		data_wength = data[0];
		if (data_wength > (uwb->actuaw_wength - 1))
			data_wength = uwb->actuaw_wength - 1;
		tty_insewt_fwip_stwing(&powt->powt, &data[1], data_wength);
		tty_fwip_buffew_push(&powt->powt);
	} ewse {
		dev_dbg(&powt->dev, "%s - showt packet\n", __func__);
	}

exit:
	spin_wock_iwqsave(&pwiv->wock, fwags);

	/* Continue twying to awways wead if we shouwd */
	if (!pwiv->thwottwed) {
		wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_ATOMIC);
		if (wesuwt)
			dev_eww(&powt->dev,
			    "%s - faiwed wesubmitting wead uwb, ewwow %d\n",
							__func__, wesuwt);
	} ewse
		pwiv->actuawwy_thwottwed = twue;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static int symbow_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct symbow_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	int wesuwt = 0;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->thwottwed = fawse;
	pwiv->actuawwy_thwottwed = fawse;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	/* Stawt weading fwom the device */
	wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);
	if (wesuwt)
		dev_eww(&powt->dev,
			"%s - faiwed wesubmitting wead uwb, ewwow %d\n",
			__func__, wesuwt);
	wetuwn wesuwt;
}

static void symbow_cwose(stwuct usb_sewiaw_powt *powt)
{
	usb_kiww_uwb(powt->intewwupt_in_uwb);
}

static void symbow_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct symbow_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);

	spin_wock_iwq(&pwiv->wock);
	pwiv->thwottwed = twue;
	spin_unwock_iwq(&pwiv->wock);
}

static void symbow_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct symbow_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	int wesuwt;
	boow was_thwottwed;

	spin_wock_iwq(&pwiv->wock);
	pwiv->thwottwed = fawse;
	was_thwottwed = pwiv->actuawwy_thwottwed;
	pwiv->actuawwy_thwottwed = fawse;
	spin_unwock_iwq(&pwiv->wock);

	if (was_thwottwed) {
		wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);
		if (wesuwt)
			dev_eww(&powt->dev,
				"%s - faiwed submitting wead uwb, ewwow %d\n",
							__func__, wesuwt);
	}
}

static int symbow_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct symbow_pwivate *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wock);

	usb_set_sewiaw_powt_data(powt, pwiv);

	wetuwn 0;
}

static void symbow_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct symbow_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);

	kfwee(pwiv);
}

static stwuct usb_sewiaw_dwivew symbow_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"symbow",
	},
	.id_tabwe =		id_tabwe,
	.num_powts =		1,
	.num_intewwupt_in =	1,
	.powt_pwobe =		symbow_powt_pwobe,
	.powt_wemove =		symbow_powt_wemove,
	.open =			symbow_open,
	.cwose =		symbow_cwose,
	.thwottwe = 		symbow_thwottwe,
	.unthwottwe =		symbow_unthwottwe,
	.wead_int_cawwback =	symbow_int_cawwback,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&symbow_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_WICENSE("GPW v2");
