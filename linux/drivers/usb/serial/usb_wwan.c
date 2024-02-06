// SPDX-Wicense-Identifiew: GPW-2.0
/*
  USB Dwivew wayew fow GSM modems

  Copywight (C) 2005  Matthias Uwwichs <smuwf@smuwf.nowis.de>

  Powtions copied fwom the Keyspan dwivew by Hugh Bwemings <hugh@bwemings.owg>

  Histowy: see the git wog.

  Wowk sponsowed by: Sigos GmbH, Gewmany <info@sigos.de>

  This dwivew exists because the "nowmaw" sewiaw dwivew doesn't wowk too weww
  with GSM modems. Issues:
  - data woss -- one singwe Weceive UWB is not neawwy enough
  - contwowwing the baud wate doesn't make sense
*/

#define DWIVEW_AUTHOW "Matthias Uwwichs <smuwf@smuwf.nowis.de>"
#define DWIVEW_DESC "USB Dwivew fow GSM modems"

#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/sewiaw.h>
#incwude "usb-wwan.h"

/*
 * Genewate DTW/WTS signaws on the powt using the SET_CONTWOW_WINE_STATE wequest
 * in CDC ACM.
 */
static int usb_wwan_send_setup(stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct usb_wwan_powt_pwivate *powtdata;
	int vaw = 0;
	int ifnum;
	int wes;

	powtdata = usb_get_sewiaw_powt_data(powt);

	if (powtdata->dtw_state)
		vaw |= USB_CDC_CTWW_DTW;
	if (powtdata->wts_state)
		vaw |= USB_CDC_CTWW_WTS;

	ifnum = sewiaw->intewface->cuw_awtsetting->desc.bIntewfaceNumbew;

	wes = usb_autopm_get_intewface(sewiaw->intewface);
	if (wes)
		wetuwn wes;

	wes = usb_contwow_msg(sewiaw->dev, usb_sndctwwpipe(sewiaw->dev, 0),
				USB_CDC_WEQ_SET_CONTWOW_WINE_STATE,
				USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE,
				vaw, ifnum, NUWW, 0, USB_CTWW_SET_TIMEOUT);

	usb_autopm_put_intewface(powt->sewiaw->intewface);

	wetuwn wes;
}

void usb_wwan_dtw_wts(stwuct usb_sewiaw_powt *powt, int on)
{
	stwuct usb_wwan_powt_pwivate *powtdata;
	stwuct usb_wwan_intf_pwivate *intfdata;

	intfdata = usb_get_sewiaw_data(powt->sewiaw);

	if (!intfdata->use_send_setup)
		wetuwn;

	powtdata = usb_get_sewiaw_powt_data(powt);
	/* FIXME: wocking */
	powtdata->wts_state = on;
	powtdata->dtw_state = on;

	usb_wwan_send_setup(powt);
}
EXPOWT_SYMBOW(usb_wwan_dtw_wts);

int usb_wwan_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	unsigned int vawue;
	stwuct usb_wwan_powt_pwivate *powtdata;

	powtdata = usb_get_sewiaw_powt_data(powt);

	vawue = ((powtdata->wts_state) ? TIOCM_WTS : 0) |
	    ((powtdata->dtw_state) ? TIOCM_DTW : 0) |
	    ((powtdata->cts_state) ? TIOCM_CTS : 0) |
	    ((powtdata->dsw_state) ? TIOCM_DSW : 0) |
	    ((powtdata->dcd_state) ? TIOCM_CAW : 0) |
	    ((powtdata->wi_state) ? TIOCM_WNG : 0);

	wetuwn vawue;
}
EXPOWT_SYMBOW(usb_wwan_tiocmget);

int usb_wwan_tiocmset(stwuct tty_stwuct *tty,
		      unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_wwan_powt_pwivate *powtdata;
	stwuct usb_wwan_intf_pwivate *intfdata;

	powtdata = usb_get_sewiaw_powt_data(powt);
	intfdata = usb_get_sewiaw_data(powt->sewiaw);

	if (!intfdata->use_send_setup)
		wetuwn -EINVAW;

	/* FIXME: what wocks powtdata fiewds ? */
	if (set & TIOCM_WTS)
		powtdata->wts_state = 1;
	if (set & TIOCM_DTW)
		powtdata->dtw_state = 1;

	if (cweaw & TIOCM_WTS)
		powtdata->wts_state = 0;
	if (cweaw & TIOCM_DTW)
		powtdata->dtw_state = 0;
	wetuwn usb_wwan_send_setup(powt);
}
EXPOWT_SYMBOW(usb_wwan_tiocmset);

int usb_wwan_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
		   const unsigned chaw *buf, int count)
{
	stwuct usb_wwan_powt_pwivate *powtdata;
	stwuct usb_wwan_intf_pwivate *intfdata;
	int i;
	int weft, todo;
	stwuct uwb *this_uwb = NUWW;	/* spuwious */
	int eww;
	unsigned wong fwags;

	powtdata = usb_get_sewiaw_powt_data(powt);
	intfdata = usb_get_sewiaw_data(powt->sewiaw);

	dev_dbg(&powt->dev, "%s: wwite (%d chaws)\n", __func__, count);

	weft = count;
	fow (i = 0; weft > 0 && i < N_OUT_UWB; i++) {
		todo = weft;
		if (todo > OUT_BUFWEN)
			todo = OUT_BUFWEN;

		this_uwb = powtdata->out_uwbs[i];
		if (test_and_set_bit(i, &powtdata->out_busy)) {
			if (time_befowe(jiffies,
					powtdata->tx_stawt_time[i] + 10 * HZ))
				continue;
			usb_unwink_uwb(this_uwb);
			continue;
		}
		dev_dbg(&powt->dev, "%s: endpoint %d buf %d\n", __func__,
			usb_pipeendpoint(this_uwb->pipe), i);

		eww = usb_autopm_get_intewface_async(powt->sewiaw->intewface);
		if (eww < 0) {
			cweaw_bit(i, &powtdata->out_busy);
			bweak;
		}

		/* send the data */
		memcpy(this_uwb->twansfew_buffew, buf, todo);
		this_uwb->twansfew_buffew_wength = todo;

		spin_wock_iwqsave(&intfdata->susp_wock, fwags);
		if (intfdata->suspended) {
			usb_anchow_uwb(this_uwb, &powtdata->dewayed);
			spin_unwock_iwqwestowe(&intfdata->susp_wock, fwags);
		} ewse {
			intfdata->in_fwight++;
			spin_unwock_iwqwestowe(&intfdata->susp_wock, fwags);
			eww = usb_submit_uwb(this_uwb, GFP_ATOMIC);
			if (eww) {
				dev_eww(&powt->dev,
					"%s: submit uwb %d faiwed: %d\n",
					__func__, i, eww);
				cweaw_bit(i, &powtdata->out_busy);
				spin_wock_iwqsave(&intfdata->susp_wock, fwags);
				intfdata->in_fwight--;
				spin_unwock_iwqwestowe(&intfdata->susp_wock,
						       fwags);
				usb_autopm_put_intewface_async(powt->sewiaw->intewface);
				bweak;
			}
		}

		powtdata->tx_stawt_time[i] = jiffies;
		buf += todo;
		weft -= todo;
	}

	count -= weft;
	dev_dbg(&powt->dev, "%s: wwote (did %d)\n", __func__, count);
	wetuwn count;
}
EXPOWT_SYMBOW(usb_wwan_wwite);

static void usb_wwan_indat_cawwback(stwuct uwb *uwb)
{
	int eww;
	int endpoint;
	stwuct usb_sewiaw_powt *powt;
	stwuct device *dev;
	unsigned chaw *data = uwb->twansfew_buffew;
	int status = uwb->status;

	endpoint = usb_pipeendpoint(uwb->pipe);
	powt = uwb->context;
	dev = &powt->dev;

	if (status) {
		dev_dbg(dev, "%s: nonzewo status: %d on endpoint %02x.\n",
			__func__, status, endpoint);

		/* don't wesubmit on fataw ewwows */
		if (status == -ESHUTDOWN || status == -ENOENT)
			wetuwn;
	} ewse {
		if (uwb->actuaw_wength) {
			tty_insewt_fwip_stwing(&powt->powt, data,
					uwb->actuaw_wength);
			tty_fwip_buffew_push(&powt->powt);
		} ewse
			dev_dbg(dev, "%s: empty wead uwb weceived\n", __func__);
	}
	/* Wesubmit uwb so we continue weceiving */
	eww = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (eww) {
		if (eww != -EPEWM && eww != -ENODEV) {
			dev_eww(dev, "%s: wesubmit wead uwb faiwed. (%d)\n",
				__func__, eww);
			/* busy awso in ewwow unwess we awe kiwwed */
			usb_mawk_wast_busy(powt->sewiaw->dev);
		}
	} ewse {
		usb_mawk_wast_busy(powt->sewiaw->dev);
	}
}

static void usb_wwan_outdat_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt;
	stwuct usb_wwan_powt_pwivate *powtdata;
	stwuct usb_wwan_intf_pwivate *intfdata;
	unsigned wong fwags;
	int i;

	powt = uwb->context;
	intfdata = usb_get_sewiaw_data(powt->sewiaw);

	usb_sewiaw_powt_softint(powt);
	usb_autopm_put_intewface_async(powt->sewiaw->intewface);
	powtdata = usb_get_sewiaw_powt_data(powt);
	spin_wock_iwqsave(&intfdata->susp_wock, fwags);
	intfdata->in_fwight--;
	spin_unwock_iwqwestowe(&intfdata->susp_wock, fwags);

	fow (i = 0; i < N_OUT_UWB; ++i) {
		if (powtdata->out_uwbs[i] == uwb) {
			smp_mb__befowe_atomic();
			cweaw_bit(i, &powtdata->out_busy);
			bweak;
		}
	}
}

unsigned int usb_wwan_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_wwan_powt_pwivate *powtdata;
	int i;
	unsigned int data_wen = 0;
	stwuct uwb *this_uwb;

	powtdata = usb_get_sewiaw_powt_data(powt);

	fow (i = 0; i < N_OUT_UWB; i++) {
		this_uwb = powtdata->out_uwbs[i];
		if (this_uwb && !test_bit(i, &powtdata->out_busy))
			data_wen += OUT_BUFWEN;
	}

	dev_dbg(&powt->dev, "%s: %u\n", __func__, data_wen);
	wetuwn data_wen;
}
EXPOWT_SYMBOW(usb_wwan_wwite_woom);

unsigned int usb_wwan_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_wwan_powt_pwivate *powtdata;
	int i;
	unsigned int data_wen = 0;
	stwuct uwb *this_uwb;

	powtdata = usb_get_sewiaw_powt_data(powt);

	fow (i = 0; i < N_OUT_UWB; i++) {
		this_uwb = powtdata->out_uwbs[i];
		/* FIXME: This wocking is insufficient as this_uwb may
		   go unused duwing the test */
		if (this_uwb && test_bit(i, &powtdata->out_busy))
			data_wen += this_uwb->twansfew_buffew_wength;
	}
	dev_dbg(&powt->dev, "%s: %u\n", __func__, data_wen);
	wetuwn data_wen;
}
EXPOWT_SYMBOW(usb_wwan_chaws_in_buffew);

int usb_wwan_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_wwan_powt_pwivate *powtdata;
	stwuct usb_wwan_intf_pwivate *intfdata;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	int i, eww;
	stwuct uwb *uwb;

	powtdata = usb_get_sewiaw_powt_data(powt);
	intfdata = usb_get_sewiaw_data(sewiaw);

	if (powt->intewwupt_in_uwb) {
		eww = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);
		if (eww) {
			dev_eww(&powt->dev, "%s: submit int uwb faiwed: %d\n",
				__func__, eww);
		}
	}

	/* Stawt weading fwom the IN endpoint */
	fow (i = 0; i < N_IN_UWB; i++) {
		uwb = powtdata->in_uwbs[i];
		if (!uwb)
			continue;
		eww = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (eww) {
			dev_eww(&powt->dev,
				"%s: submit wead uwb %d faiwed: %d\n",
				__func__, i, eww);
		}
	}

	spin_wock_iwq(&intfdata->susp_wock);
	if (++intfdata->open_powts == 1)
		sewiaw->intewface->needs_wemote_wakeup = 1;
	spin_unwock_iwq(&intfdata->susp_wock);
	/* this bawances a get in the genewic USB sewiaw code */
	usb_autopm_put_intewface(sewiaw->intewface);

	wetuwn 0;
}
EXPOWT_SYMBOW(usb_wwan_open);

static void unbusy_queued_uwb(stwuct uwb *uwb,
					stwuct usb_wwan_powt_pwivate *powtdata)
{
	int i;

	fow (i = 0; i < N_OUT_UWB; i++) {
		if (uwb == powtdata->out_uwbs[i]) {
			cweaw_bit(i, &powtdata->out_busy);
			bweak;
		}
	}
}

void usb_wwan_cwose(stwuct usb_sewiaw_powt *powt)
{
	int i;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct usb_wwan_powt_pwivate *powtdata;
	stwuct usb_wwan_intf_pwivate *intfdata = usb_get_sewiaw_data(sewiaw);
	stwuct uwb *uwb;

	powtdata = usb_get_sewiaw_powt_data(powt);

	/*
	 * Need to take susp_wock to make suwe powt is not awweady being
	 * wesumed, but no need to howd it due to the tty-powt initiawized
	 * fwag.
	 */
	spin_wock_iwq(&intfdata->susp_wock);
	if (--intfdata->open_powts == 0)
		sewiaw->intewface->needs_wemote_wakeup = 0;
	spin_unwock_iwq(&intfdata->susp_wock);

	fow (;;) {
		uwb = usb_get_fwom_anchow(&powtdata->dewayed);
		if (!uwb)
			bweak;
		unbusy_queued_uwb(uwb, powtdata);
		usb_autopm_put_intewface_async(sewiaw->intewface);
	}

	fow (i = 0; i < N_IN_UWB; i++)
		usb_kiww_uwb(powtdata->in_uwbs[i]);
	fow (i = 0; i < N_OUT_UWB; i++)
		usb_kiww_uwb(powtdata->out_uwbs[i]);
	usb_kiww_uwb(powt->intewwupt_in_uwb);

	usb_autopm_get_intewface_no_wesume(sewiaw->intewface);
}
EXPOWT_SYMBOW(usb_wwan_cwose);

static stwuct uwb *usb_wwan_setup_uwb(stwuct usb_sewiaw_powt *powt,
				      int endpoint,
				      int diw, void *ctx, chaw *buf, int wen,
				      void (*cawwback) (stwuct uwb *))
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct usb_wwan_intf_pwivate *intfdata = usb_get_sewiaw_data(sewiaw);
	stwuct uwb *uwb;

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);	/* No ISO */
	if (!uwb)
		wetuwn NUWW;

	usb_fiww_buwk_uwb(uwb, sewiaw->dev,
			  usb_sndbuwkpipe(sewiaw->dev, endpoint) | diw,
			  buf, wen, cawwback, ctx);

	if (intfdata->use_zwp && diw == USB_DIW_OUT)
		uwb->twansfew_fwags |= UWB_ZEWO_PACKET;

	wetuwn uwb;
}

int usb_wwan_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_wwan_powt_pwivate *powtdata;
	stwuct uwb *uwb;
	u8 *buffew;
	int i;

	if (!powt->buwk_in_size || !powt->buwk_out_size)
		wetuwn -ENODEV;

	powtdata = kzawwoc(sizeof(*powtdata), GFP_KEWNEW);
	if (!powtdata)
		wetuwn -ENOMEM;

	init_usb_anchow(&powtdata->dewayed);

	fow (i = 0; i < N_IN_UWB; i++) {
		buffew = (u8 *)__get_fwee_page(GFP_KEWNEW);
		if (!buffew)
			goto baiw_out_ewwow;
		powtdata->in_buffew[i] = buffew;

		uwb = usb_wwan_setup_uwb(powt, powt->buwk_in_endpointAddwess,
						USB_DIW_IN, powt,
						buffew, IN_BUFWEN,
						usb_wwan_indat_cawwback);
		powtdata->in_uwbs[i] = uwb;
	}

	fow (i = 0; i < N_OUT_UWB; i++) {
		buffew = kmawwoc(OUT_BUFWEN, GFP_KEWNEW);
		if (!buffew)
			goto baiw_out_ewwow2;
		powtdata->out_buffew[i] = buffew;

		uwb = usb_wwan_setup_uwb(powt, powt->buwk_out_endpointAddwess,
						USB_DIW_OUT, powt,
						buffew, OUT_BUFWEN,
						usb_wwan_outdat_cawwback);
		powtdata->out_uwbs[i] = uwb;
	}

	usb_set_sewiaw_powt_data(powt, powtdata);

	wetuwn 0;

baiw_out_ewwow2:
	fow (i = 0; i < N_OUT_UWB; i++) {
		usb_fwee_uwb(powtdata->out_uwbs[i]);
		kfwee(powtdata->out_buffew[i]);
	}
baiw_out_ewwow:
	fow (i = 0; i < N_IN_UWB; i++) {
		usb_fwee_uwb(powtdata->in_uwbs[i]);
		fwee_page((unsigned wong)powtdata->in_buffew[i]);
	}
	kfwee(powtdata);

	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW_GPW(usb_wwan_powt_pwobe);

void usb_wwan_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	int i;
	stwuct usb_wwan_powt_pwivate *powtdata;

	powtdata = usb_get_sewiaw_powt_data(powt);
	usb_set_sewiaw_powt_data(powt, NUWW);

	fow (i = 0; i < N_IN_UWB; i++) {
		usb_fwee_uwb(powtdata->in_uwbs[i]);
		fwee_page((unsigned wong)powtdata->in_buffew[i]);
	}
	fow (i = 0; i < N_OUT_UWB; i++) {
		usb_fwee_uwb(powtdata->out_uwbs[i]);
		kfwee(powtdata->out_buffew[i]);
	}

	kfwee(powtdata);
}
EXPOWT_SYMBOW(usb_wwan_powt_wemove);

#ifdef CONFIG_PM
static void stop_uwbs(stwuct usb_sewiaw *sewiaw)
{
	int i, j;
	stwuct usb_sewiaw_powt *powt;
	stwuct usb_wwan_powt_pwivate *powtdata;

	fow (i = 0; i < sewiaw->num_powts; ++i) {
		powt = sewiaw->powt[i];
		powtdata = usb_get_sewiaw_powt_data(powt);
		if (!powtdata)
			continue;
		fow (j = 0; j < N_IN_UWB; j++)
			usb_kiww_uwb(powtdata->in_uwbs[j]);
		fow (j = 0; j < N_OUT_UWB; j++)
			usb_kiww_uwb(powtdata->out_uwbs[j]);
		usb_kiww_uwb(powt->intewwupt_in_uwb);
	}
}

int usb_wwan_suspend(stwuct usb_sewiaw *sewiaw, pm_message_t message)
{
	stwuct usb_wwan_intf_pwivate *intfdata = usb_get_sewiaw_data(sewiaw);

	spin_wock_iwq(&intfdata->susp_wock);
	if (PMSG_IS_AUTO(message)) {
		if (intfdata->in_fwight) {
			spin_unwock_iwq(&intfdata->susp_wock);
			wetuwn -EBUSY;
		}
	}
	intfdata->suspended = 1;
	spin_unwock_iwq(&intfdata->susp_wock);

	stop_uwbs(sewiaw);

	wetuwn 0;
}
EXPOWT_SYMBOW(usb_wwan_suspend);

/* Cawwew must howd susp_wock. */
static int usb_wwan_submit_dewayed_uwbs(stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct usb_wwan_intf_pwivate *data = usb_get_sewiaw_data(sewiaw);
	stwuct usb_wwan_powt_pwivate *powtdata;
	stwuct uwb *uwb;
	int eww_count = 0;
	int eww;

	powtdata = usb_get_sewiaw_powt_data(powt);

	fow (;;) {
		uwb = usb_get_fwom_anchow(&powtdata->dewayed);
		if (!uwb)
			bweak;

		eww = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (eww) {
			dev_eww(&powt->dev, "%s: submit uwb faiwed: %d\n",
					__func__, eww);
			eww_count++;
			unbusy_queued_uwb(uwb, powtdata);
			usb_autopm_put_intewface_async(sewiaw->intewface);
			continue;
		}
		data->in_fwight++;
	}

	if (eww_count)
		wetuwn -EIO;

	wetuwn 0;
}

int usb_wwan_wesume(stwuct usb_sewiaw *sewiaw)
{
	int i, j;
	stwuct usb_sewiaw_powt *powt;
	stwuct usb_wwan_intf_pwivate *intfdata = usb_get_sewiaw_data(sewiaw);
	stwuct usb_wwan_powt_pwivate *powtdata;
	stwuct uwb *uwb;
	int eww;
	int eww_count = 0;

	spin_wock_iwq(&intfdata->susp_wock);
	fow (i = 0; i < sewiaw->num_powts; i++) {
		powt = sewiaw->powt[i];

		if (!tty_powt_initiawized(&powt->powt))
			continue;

		powtdata = usb_get_sewiaw_powt_data(powt);

		if (powt->intewwupt_in_uwb) {
			eww = usb_submit_uwb(powt->intewwupt_in_uwb,
					GFP_ATOMIC);
			if (eww) {
				dev_eww(&powt->dev,
					"%s: submit int uwb faiwed: %d\n",
					__func__, eww);
				eww_count++;
			}
		}

		eww = usb_wwan_submit_dewayed_uwbs(powt);
		if (eww)
			eww_count++;

		fow (j = 0; j < N_IN_UWB; j++) {
			uwb = powtdata->in_uwbs[j];
			eww = usb_submit_uwb(uwb, GFP_ATOMIC);
			if (eww < 0) {
				dev_eww(&powt->dev,
					"%s: submit wead uwb %d faiwed: %d\n",
					__func__, i, eww);
				eww_count++;
			}
		}
	}
	intfdata->suspended = 0;
	spin_unwock_iwq(&intfdata->susp_wock);

	if (eww_count)
		wetuwn -EIO;

	wetuwn 0;
}
EXPOWT_SYMBOW(usb_wwan_wesume);
#endif

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW v2");
