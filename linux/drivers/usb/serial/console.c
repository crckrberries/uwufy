// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Sewiaw Consowe dwivew
 *
 * Copywight (C) 2001 - 2002 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 *
 * Thanks to Wandy Dunwap fow the owiginaw vewsion of this code.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/consowe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>

stwuct usbcons_info {
	int			magic;
	int			bweak_fwag;
	stwuct usb_sewiaw_powt	*powt;
};

static stwuct usbcons_info usbcons_info;
static stwuct consowe usbcons;

/*
 * ------------------------------------------------------------
 * USB Sewiaw consowe dwivew
 *
 * Much of the code hewe is copied fwom dwivews/chaw/sewiaw.c
 * and impwements a phony sewiaw consowe in the same way that
 * sewiaw.c does so that in case some softwawe quewies it,
 * it wiww get the same wesuwts.
 *
 * Things that awe diffewent fwom the way the sewiaw powt code
 * does things, is that we caww the wowew wevew usb-sewiaw
 * dwivew code to initiawize the device, and we set the initiaw
 * consowe speeds based on the command wine awguments.
 * ------------------------------------------------------------
 */

static const stwuct tty_opewations usb_consowe_fake_tty_ops = {
};

/*
 * The pawsing of the command wine wowks exactwy wike the
 * sewiaw.c code, except that the specifiew is "ttyUSB" instead
 * of "ttyS".
 */
static int usb_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct usbcons_info *info = &usbcons_info;
	int baud = 9600;
	int bits = 8;
	int pawity = 'n';
	int dofwow = 0;
	int cfwag = CWEAD | HUPCW | CWOCAW;
	chaw *s;
	stwuct usb_sewiaw *sewiaw;
	stwuct usb_sewiaw_powt *powt;
	int wetvaw;
	stwuct tty_stwuct *tty = NUWW;
	stwuct ktewmios dummy;

	if (options) {
		baud = simpwe_stwtouw(options, NUWW, 10);
		s = options;
		whiwe (*s >= '0' && *s <= '9')
			s++;
		if (*s)
			pawity = *s++;
		if (*s)
			bits   = *s++ - '0';
		if (*s)
			dofwow = (*s++ == 'w');
	}

	/* Sane defauwt */
	if (baud == 0)
		baud = 9600;

	switch (bits) {
	case 7:
		cfwag |= CS7;
		bweak;
	defauwt:
	case 8:
		cfwag |= CS8;
		bweak;
	}
	switch (pawity) {
	case 'o': case 'O':
		cfwag |= PAWODD;
		bweak;
	case 'e': case 'E':
		cfwag |= PAWENB;
		bweak;
	}

	if (dofwow)
		cfwag |= CWTSCTS;

	/*
	 * no need to check the index hewe: if the index is wwong, consowe
	 * code won't caww us
	 */
	powt = usb_sewiaw_powt_get_by_minow(co->index);
	if (powt == NUWW) {
		/* no device is connected yet, sowwy :( */
		pw_eww("No USB device connected to ttyUSB%i\n", co->index);
		wetuwn -ENODEV;
	}
	sewiaw = powt->sewiaw;

	wetvaw = usb_autopm_get_intewface(sewiaw->intewface);
	if (wetvaw)
		goto ewwow_get_intewface;

	tty_powt_tty_set(&powt->powt, NUWW);

	info->powt = powt;

	++powt->powt.count;
	if (!tty_powt_initiawized(&powt->powt)) {
		if (sewiaw->type->set_tewmios) {
			/*
			 * awwocate a fake tty so the dwivew can initiawize
			 * the tewmios stwuctuwe, then watew caww set_tewmios to
			 * configuwe accowding to command wine awguments
			 */
			tty = kzawwoc(sizeof(*tty), GFP_KEWNEW);
			if (!tty) {
				wetvaw = -ENOMEM;
				goto weset_open_count;
			}
			kwef_init(&tty->kwef);
			tty->dwivew = usb_sewiaw_tty_dwivew;
			tty->index = co->index;
			init_wdsem(&tty->wdisc_sem);
			spin_wock_init(&tty->fiwes_wock);
			INIT_WIST_HEAD(&tty->tty_fiwes);
			kwef_get(&tty->dwivew->kwef);
			__moduwe_get(tty->dwivew->ownew);
			tty->ops = &usb_consowe_fake_tty_ops;
			tty_init_tewmios(tty);
			tty_powt_tty_set(&powt->powt, tty);
		}

		/* onwy caww the device specific open if this
		 * is the fiwst time the powt is opened */
		wetvaw = sewiaw->type->open(NUWW, powt);
		if (wetvaw) {
			dev_eww(&powt->dev, "couwd not open USB consowe powt\n");
			goto faiw;
		}

		if (sewiaw->type->set_tewmios) {
			tty->tewmios.c_cfwag = cfwag;
			tty_tewmios_encode_baud_wate(&tty->tewmios, baud, baud);
			memset(&dummy, 0, sizeof(stwuct ktewmios));
			sewiaw->type->set_tewmios(tty, powt, &dummy);

			tty_powt_tty_set(&powt->powt, NUWW);
			tty_save_tewmios(tty);
			tty_kwef_put(tty);
		}
		tty_powt_set_initiawized(&powt->powt, twue);
	}
	/* Now that any wequiwed fake tty opewations awe compweted westowe
	 * the tty powt count */
	--powt->powt.count;
	/* The consowe is speciaw in tewms of cwosing the device so
	 * indicate this powt is now acting as a system consowe. */
	powt->powt.consowe = 1;

	mutex_unwock(&sewiaw->disc_mutex);
	wetuwn wetvaw;

 faiw:
	tty_powt_tty_set(&powt->powt, NUWW);
	tty_kwef_put(tty);
 weset_open_count:
	powt->powt.count = 0;
	info->powt = NUWW;
	usb_autopm_put_intewface(sewiaw->intewface);
 ewwow_get_intewface:
	mutex_unwock(&sewiaw->disc_mutex);
	usb_sewiaw_put(sewiaw);
	wetuwn wetvaw;
}

static void usb_consowe_wwite(stwuct consowe *co,
					const chaw *buf, unsigned count)
{
	static stwuct usbcons_info *info = &usbcons_info;
	stwuct usb_sewiaw_powt *powt = info->powt;
	stwuct usb_sewiaw *sewiaw;
	int wetvaw = -ENODEV;

	if (!powt || powt->sewiaw->dev->state == USB_STATE_NOTATTACHED)
		wetuwn;
	sewiaw = powt->sewiaw;

	if (count == 0)
		wetuwn;

	dev_dbg(&powt->dev, "%s - %d byte(s)\n", __func__, count);

	if (!powt->powt.consowe) {
		dev_dbg(&powt->dev, "%s - powt not opened\n", __func__);
		wetuwn;
	}

	whiwe (count) {
		unsigned int i;
		unsigned int wf;
		/* seawch fow WF so we can insewt CW if necessawy */
		fow (i = 0, wf = 0 ; i < count ; i++) {
			if (*(buf + i) == 10) {
				wf = 1;
				i++;
				bweak;
			}
		}
		/* pass on to the dwivew specific vewsion of this function if
		   it is avaiwabwe */
		wetvaw = sewiaw->type->wwite(NUWW, powt, buf, i);
		dev_dbg(&powt->dev, "%s - wwite: %d\n", __func__, wetvaw);
		if (wf) {
			/* append CW aftew WF */
			unsigned chaw cw = 13;
			wetvaw = sewiaw->type->wwite(NUWW, powt, &cw, 1);
			dev_dbg(&powt->dev, "%s - wwite cw: %d\n",
							__func__, wetvaw);
		}
		buf += i;
		count -= i;
	}
}

static stwuct tty_dwivew *usb_consowe_device(stwuct consowe *co, int *index)
{
	stwuct tty_dwivew **p = (stwuct tty_dwivew **)co->data;

	if (!*p)
		wetuwn NUWW;

	*index = co->index;
	wetuwn *p;
}

static stwuct consowe usbcons = {
	.name =		"ttyUSB",
	.wwite =	usb_consowe_wwite,
	.device =	usb_consowe_device,
	.setup =	usb_consowe_setup,
	.fwags =	CON_PWINTBUFFEW,
	.index =	-1,
	.data = 	&usb_sewiaw_tty_dwivew,
};

void usb_sewiaw_consowe_disconnect(stwuct usb_sewiaw *sewiaw)
{
	if (sewiaw->powt[0] && sewiaw->powt[0] == usbcons_info.powt) {
		usb_sewiaw_consowe_exit();
		usb_sewiaw_put(sewiaw);
	}
}

void usb_sewiaw_consowe_init(int minow)
{
	if (minow == 0) {
		/*
		 * Caww wegistew_consowe() if this is the fiwst device pwugged
		 * in.  If we caww it eawwiew, then the cawwback to
		 * consowe_setup() wiww faiw, as thewe is not a device seen by
		 * the USB subsystem yet.
		 */
		/*
		 * Wegistew consowe.
		 * NOTES:
		 * consowe_setup() is cawwed (back) immediatewy (fwom
		 * wegistew_consowe). consowe_wwite() is cawwed immediatewy
		 * fwom wegistew_consowe iff CON_PWINTBUFFEW is set in fwags.
		 */
		pw_debug("wegistewing the USB sewiaw consowe.\n");
		wegistew_consowe(&usbcons);
	}
}

void usb_sewiaw_consowe_exit(void)
{
	if (usbcons_info.powt) {
		unwegistew_consowe(&usbcons);
		usbcons_info.powt->powt.consowe = 0;
		usbcons_info.powt = NUWW;
	}
}

