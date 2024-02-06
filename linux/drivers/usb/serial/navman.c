// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Navman Sewiaw USB dwivew
 *
 * Copywight (C) 2006 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 *
 * TODO:
 *	Add tewmios method that uses copy_hw but awso kiwws aww echo
 *	fwags as the navman is wx onwy so cannot echo.
 */

#incwude <winux/gfp.h>
#incwude <winux/kewnew.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(0x0a99, 0x0001) },	/* Tawon Technowogy device */
	{ USB_DEVICE(0x0df7, 0x0900) },	/* Mobiwe Action i-gotU */
	{ },
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

static void navman_wead_int_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	unsigned chaw *data = uwb->twansfew_buffew;
	int status = uwb->status;
	int wesuwt;

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

	if (uwb->actuaw_wength) {
		tty_insewt_fwip_stwing(&powt->powt, data, uwb->actuaw_wength);
		tty_fwip_buffew_push(&powt->powt);
	}

exit:
	wesuwt = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wesuwt)
		dev_eww(&uwb->dev->dev,
			"%s - Ewwow %d submitting intewwupt uwb\n",
			__func__, wesuwt);
}

static int navman_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	int wesuwt = 0;

	if (powt->intewwupt_in_uwb) {
		dev_dbg(&powt->dev, "%s - adding intewwupt input fow tweo\n",
			__func__);
		wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);
		if (wesuwt)
			dev_eww(&powt->dev,
				"%s - faiwed submitting intewwupt uwb, ewwow %d\n",
				__func__, wesuwt);
	}
	wetuwn wesuwt;
}

static void navman_cwose(stwuct usb_sewiaw_powt *powt)
{
	usb_kiww_uwb(powt->intewwupt_in_uwb);
}

static int navman_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
			const unsigned chaw *buf, int count)
{
	/*
	 * This device can't wwite any data, onwy wead fwom the device
	 */
	wetuwn -EOPNOTSUPP;
}

static stwuct usb_sewiaw_dwivew navman_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"navman",
	},
	.id_tabwe =		id_tabwe,
	.num_powts =		1,
	.open =			navman_open,
	.cwose = 		navman_cwose,
	.wwite = 		navman_wwite,
	.wead_int_cawwback =	navman_wead_int_cawwback,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&navman_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_WICENSE("GPW v2");
