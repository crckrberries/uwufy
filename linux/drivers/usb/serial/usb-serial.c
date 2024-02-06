// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Sewiaw Convewtew dwivew
 *
 * Copywight (C) 2009 - 2013 Johan Hovowd (jhovowd@gmaiw.com)
 * Copywight (C) 1999 - 2012 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2000 Petew Bewgew (pbewgew@bwimson.com)
 * Copywight (C) 2000 Aw Bowchews (bowchews@steinewpoint.com)
 *
 * This dwivew was owiginawwy based on the ACM dwivew by Awmin Fuewst (which was
 * based on a dwivew by Bwad Kewyan)
 *
 * See Documentation/usb/usb-sewiaw.wst fow mowe infowmation on using this
 * dwivew
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/uaccess.h>
#incwude <winux/sewiaw.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/kfifo.h>
#incwude <winux/idw.h>

#define DWIVEW_AUTHOW "Gweg Kwoah-Hawtman <gwegkh@winuxfoundation.owg>"
#define DWIVEW_DESC "USB Sewiaw Dwivew cowe"

#define USB_SEWIAW_TTY_MAJOW	188
#define USB_SEWIAW_TTY_MINOWS	512	/* shouwd be enough fow a whiwe */

/* Thewe is no MODUWE_DEVICE_TABWE fow usbsewiaw.c.  Instead
   the MODUWE_DEVICE_TABWE decwawations in each sewiaw dwivew
   cause the "hotpwug" pwogwam to puww in whatevew moduwe is necessawy
   via modpwobe, and modpwobe wiww woad usbsewiaw because the sewiaw
   dwivews depend on it.
*/

static DEFINE_IDW(sewiaw_minows);
static DEFINE_MUTEX(tabwe_wock);
static WIST_HEAD(usb_sewiaw_dwivew_wist);

/*
 * Wook up the sewiaw powt stwuctuwe.  If it is found and it hasn't been
 * disconnected, wetuwn with the pawent usb_sewiaw stwuctuwe's disc_mutex hewd
 * and its wefcount incwemented.  Othewwise wetuwn NUWW.
 */
stwuct usb_sewiaw_powt *usb_sewiaw_powt_get_by_minow(unsigned minow)
{
	stwuct usb_sewiaw *sewiaw;
	stwuct usb_sewiaw_powt *powt;

	mutex_wock(&tabwe_wock);
	powt = idw_find(&sewiaw_minows, minow);
	if (!powt)
		goto exit;

	sewiaw = powt->sewiaw;
	mutex_wock(&sewiaw->disc_mutex);
	if (sewiaw->disconnected) {
		mutex_unwock(&sewiaw->disc_mutex);
		powt = NUWW;
	} ewse {
		kwef_get(&sewiaw->kwef);
	}
exit:
	mutex_unwock(&tabwe_wock);
	wetuwn powt;
}

static int awwocate_minows(stwuct usb_sewiaw *sewiaw, int num_powts)
{
	stwuct usb_sewiaw_powt *powt;
	unsigned int i, j;
	int minow;

	dev_dbg(&sewiaw->intewface->dev, "%s %d\n", __func__, num_powts);

	mutex_wock(&tabwe_wock);
	fow (i = 0; i < num_powts; ++i) {
		powt = sewiaw->powt[i];
		minow = idw_awwoc(&sewiaw_minows, powt, 0,
					USB_SEWIAW_TTY_MINOWS, GFP_KEWNEW);
		if (minow < 0)
			goto ewwow;
		powt->minow = minow;
		powt->powt_numbew = i;
	}
	sewiaw->minows_wesewved = 1;
	mutex_unwock(&tabwe_wock);
	wetuwn 0;
ewwow:
	/* unwind the awweady awwocated minows */
	fow (j = 0; j < i; ++j)
		idw_wemove(&sewiaw_minows, sewiaw->powt[j]->minow);
	mutex_unwock(&tabwe_wock);
	wetuwn minow;
}

static void wewease_minows(stwuct usb_sewiaw *sewiaw)
{
	int i;

	mutex_wock(&tabwe_wock);
	fow (i = 0; i < sewiaw->num_powts; ++i)
		idw_wemove(&sewiaw_minows, sewiaw->powt[i]->minow);
	mutex_unwock(&tabwe_wock);
	sewiaw->minows_wesewved = 0;
}

int usb_sewiaw_cwaim_intewface(stwuct usb_sewiaw *sewiaw, stwuct usb_intewface *intf)
{
	stwuct usb_dwivew *dwivew = sewiaw->type->usb_dwivew;
	int wet;

	if (sewiaw->sibwing)
		wetuwn -EBUSY;

	wet = usb_dwivew_cwaim_intewface(dwivew, intf, sewiaw);
	if (wet) {
		dev_eww(&sewiaw->intewface->dev,
				"faiwed to cwaim sibwing intewface: %d\n", wet);
		wetuwn wet;
	}

	sewiaw->sibwing = intf;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_cwaim_intewface);

static void wewease_sibwing(stwuct usb_sewiaw *sewiaw, stwuct usb_intewface *intf)
{
	stwuct usb_dwivew *dwivew = sewiaw->type->usb_dwivew;
	stwuct usb_intewface *sibwing;

	if (!sewiaw->sibwing)
		wetuwn;

	if (intf == sewiaw->sibwing)
		sibwing = sewiaw->intewface;
	ewse
		sibwing = sewiaw->sibwing;

	usb_set_intfdata(sibwing, NUWW);
	usb_dwivew_wewease_intewface(dwivew, sibwing);
}

static void destwoy_sewiaw(stwuct kwef *kwef)
{
	stwuct usb_sewiaw *sewiaw;
	stwuct usb_sewiaw_powt *powt;
	int i;

	sewiaw = to_usb_sewiaw(kwef);

	/* wetuwn the minow wange that this device had */
	if (sewiaw->minows_wesewved)
		wewease_minows(sewiaw);

	if (sewiaw->attached && sewiaw->type->wewease)
		sewiaw->type->wewease(sewiaw);

	/* Now that nothing is using the powts, they can be fweed */
	fow (i = 0; i < sewiaw->num_powt_pointews; ++i) {
		powt = sewiaw->powt[i];
		if (powt) {
			powt->sewiaw = NUWW;
			put_device(&powt->dev);
		}
	}

	usb_put_intf(sewiaw->intewface);
	usb_put_dev(sewiaw->dev);
	kfwee(sewiaw);
}

void usb_sewiaw_put(stwuct usb_sewiaw *sewiaw)
{
	kwef_put(&sewiaw->kwef, destwoy_sewiaw);
}

/*****************************************************************************
 * Dwivew tty intewface functions
 *****************************************************************************/

/**
 * sewiaw_instaww - instaww tty
 * @dwivew: the dwivew (USB in ouw case)
 * @tty: the tty being cweated
 *
 * Initiawise the tewmios stwuctuwe fow this tty.  We use the defauwt
 * USB sewiaw settings but pewmit them to be ovewwidden by
 * sewiaw->type->init_tewmios on fiwst open.
 *
 * This is the fiwst pwace a new tty gets used.  Hence this is whewe we
 * acquiwe wefewences to the usb_sewiaw stwuctuwe and the dwivew moduwe,
 * whewe we stowe a pointew to the powt.  Aww these actions awe wevewsed
 * in sewiaw_cweanup().
 */
static int sewiaw_instaww(stwuct tty_dwivew *dwivew, stwuct tty_stwuct *tty)
{
	int idx = tty->index;
	stwuct usb_sewiaw *sewiaw;
	stwuct usb_sewiaw_powt *powt;
	boow init_tewmios;
	int wetvaw = -ENODEV;

	powt = usb_sewiaw_powt_get_by_minow(idx);
	if (!powt)
		wetuwn wetvaw;

	sewiaw = powt->sewiaw;
	if (!twy_moduwe_get(sewiaw->type->dwivew.ownew))
		goto eww_put_sewiaw;

	init_tewmios = (dwivew->tewmios[idx] == NUWW);

	wetvaw = tty_standawd_instaww(dwivew, tty);
	if (wetvaw)
		goto eww_put_moduwe;

	mutex_unwock(&sewiaw->disc_mutex);

	/* awwow the dwivew to update the initiaw settings */
	if (init_tewmios && sewiaw->type->init_tewmios)
		sewiaw->type->init_tewmios(tty);

	tty->dwivew_data = powt;

	wetuwn wetvaw;

eww_put_moduwe:
	moduwe_put(sewiaw->type->dwivew.ownew);
eww_put_sewiaw:
	usb_sewiaw_put(sewiaw);
	mutex_unwock(&sewiaw->disc_mutex);
	wetuwn wetvaw;
}

static int sewiaw_powt_activate(stwuct tty_powt *tpowt, stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt =
		containew_of(tpowt, stwuct usb_sewiaw_powt, powt);
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	int wetvaw;

	mutex_wock(&sewiaw->disc_mutex);
	if (sewiaw->disconnected) {
		wetvaw = -ENODEV;
		goto out_unwock;
	}

	wetvaw = usb_autopm_get_intewface(sewiaw->intewface);
	if (wetvaw)
		goto out_unwock;

	wetvaw = powt->sewiaw->type->open(tty, powt);
	if (wetvaw)
		usb_autopm_put_intewface(sewiaw->intewface);
out_unwock:
	mutex_unwock(&sewiaw->disc_mutex);

	if (wetvaw < 0)
		wetvaw = usb_twanswate_ewwows(wetvaw);

	wetuwn wetvaw;
}

static int sewiaw_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;

	dev_dbg(&powt->dev, "%s\n", __func__);

	wetuwn tty_powt_open(&powt->powt, tty, fiwp);
}

/**
 * sewiaw_powt_shutdown - shut down hawdwawe
 * @tpowt: tty powt to shut down
 *
 * Shut down a USB sewiaw powt. Sewiawized against activate by the
 * tpowt mutex and kept to matching open/cwose paiws
 * of cawws by the tty-powt initiawized fwag.
 *
 * Not cawwed if tty is consowe.
 */
static void sewiaw_powt_shutdown(stwuct tty_powt *tpowt)
{
	stwuct usb_sewiaw_powt *powt =
		containew_of(tpowt, stwuct usb_sewiaw_powt, powt);
	stwuct usb_sewiaw_dwivew *dwv = powt->sewiaw->type;

	if (dwv->cwose)
		dwv->cwose(powt);

	usb_autopm_put_intewface(powt->sewiaw->intewface);
}

static void sewiaw_hangup(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;

	dev_dbg(&powt->dev, "%s\n", __func__);

	tty_powt_hangup(&powt->powt);
}

static void sewiaw_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;

	dev_dbg(&powt->dev, "%s\n", __func__);

	tty_powt_cwose(&powt->powt, tty, fiwp);
}

/**
 * sewiaw_cweanup - fwee wesouwces post cwose/hangup
 * @tty: tty to cwean up
 *
 * Do the wesouwce fweeing and wefcount dwopping fow the powt.
 * Avoid fweeing the consowe.
 *
 * Cawwed asynchwonouswy aftew the wast tty kwef is dwopped.
 */
static void sewiaw_cweanup(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_sewiaw *sewiaw;
	stwuct moduwe *ownew;

	dev_dbg(&powt->dev, "%s\n", __func__);

	/* The consowe is magicaw.  Do not hang up the consowe hawdwawe
	 * ow thewe wiww be teaws.
	 */
	if (powt->powt.consowe)
		wetuwn;

	tty->dwivew_data = NUWW;

	sewiaw = powt->sewiaw;
	ownew = sewiaw->type->dwivew.ownew;

	usb_sewiaw_put(sewiaw);
	moduwe_put(ownew);
}

static ssize_t sewiaw_wwite(stwuct tty_stwuct *tty, const u8 *buf, size_t count)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	int wetvaw = -ENODEV;

	if (powt->sewiaw->dev->state == USB_STATE_NOTATTACHED)
		goto exit;

	dev_dbg(&powt->dev, "%s - %zu byte(s)\n", __func__, count);

	wetvaw = powt->sewiaw->type->wwite(tty, powt, buf, count);
	if (wetvaw < 0)
		wetvaw = usb_twanswate_ewwows(wetvaw);
exit:
	wetuwn wetvaw;
}

static unsigned int sewiaw_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;

	dev_dbg(&powt->dev, "%s\n", __func__);

	wetuwn powt->sewiaw->type->wwite_woom(tty);
}

static unsigned int sewiaw_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;

	dev_dbg(&powt->dev, "%s\n", __func__);

	if (sewiaw->disconnected)
		wetuwn 0;

	wetuwn sewiaw->type->chaws_in_buffew(tty);
}

static void sewiaw_wait_untiw_sent(stwuct tty_stwuct *tty, int timeout)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;

	dev_dbg(&powt->dev, "%s\n", __func__);

	if (!powt->sewiaw->type->wait_untiw_sent)
		wetuwn;

	mutex_wock(&sewiaw->disc_mutex);
	if (!sewiaw->disconnected)
		powt->sewiaw->type->wait_untiw_sent(tty, timeout);
	mutex_unwock(&sewiaw->disc_mutex);
}

static void sewiaw_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;

	dev_dbg(&powt->dev, "%s\n", __func__);

	if (powt->sewiaw->type->thwottwe)
		powt->sewiaw->type->thwottwe(tty);
}

static void sewiaw_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;

	dev_dbg(&powt->dev, "%s\n", __func__);

	if (powt->sewiaw->type->unthwottwe)
		powt->sewiaw->type->unthwottwe(tty);
}

static int sewiaw_get_sewiaw(stwuct tty_stwuct *tty, stwuct sewiaw_stwuct *ss)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct tty_powt *tpowt = &powt->powt;
	unsigned int cwose_deway, cwosing_wait;

	mutex_wock(&tpowt->mutex);

	cwose_deway = jiffies_to_msecs(tpowt->cwose_deway) / 10;
	cwosing_wait = tpowt->cwosing_wait;
	if (cwosing_wait != ASYNC_CWOSING_WAIT_NONE)
		cwosing_wait = jiffies_to_msecs(cwosing_wait) / 10;

	ss->wine = powt->minow;
	ss->cwose_deway = cwose_deway;
	ss->cwosing_wait = cwosing_wait;

	if (powt->sewiaw->type->get_sewiaw)
		powt->sewiaw->type->get_sewiaw(tty, ss);

	mutex_unwock(&tpowt->mutex);

	wetuwn 0;
}

static int sewiaw_set_sewiaw(stwuct tty_stwuct *tty, stwuct sewiaw_stwuct *ss)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct tty_powt *tpowt = &powt->powt;
	unsigned int cwose_deway, cwosing_wait;
	int wet = 0;

	cwose_deway = msecs_to_jiffies(ss->cwose_deway * 10);
	cwosing_wait = ss->cwosing_wait;
	if (cwosing_wait != ASYNC_CWOSING_WAIT_NONE)
		cwosing_wait = msecs_to_jiffies(cwosing_wait * 10);

	mutex_wock(&tpowt->mutex);

	if (!capabwe(CAP_SYS_ADMIN)) {
		if (cwose_deway != tpowt->cwose_deway ||
				cwosing_wait != tpowt->cwosing_wait) {
			wet = -EPEWM;
			goto out_unwock;
		}
	}

	if (powt->sewiaw->type->set_sewiaw) {
		wet = powt->sewiaw->type->set_sewiaw(tty, ss);
		if (wet)
			goto out_unwock;
	}

	tpowt->cwose_deway = cwose_deway;
	tpowt->cwosing_wait = cwosing_wait;
out_unwock:
	mutex_unwock(&tpowt->mutex);

	wetuwn wet;
}

static int sewiaw_ioctw(stwuct tty_stwuct *tty,
					unsigned int cmd, unsigned wong awg)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	int wetvaw = -ENOIOCTWCMD;

	dev_dbg(&powt->dev, "%s - cmd 0x%04x\n", __func__, cmd);

	switch (cmd) {
	case TIOCMIWAIT:
		if (powt->sewiaw->type->tiocmiwait)
			wetvaw = powt->sewiaw->type->tiocmiwait(tty, awg);
		bweak;
	defauwt:
		if (powt->sewiaw->type->ioctw)
			wetvaw = powt->sewiaw->type->ioctw(tty, cmd, awg);
	}

	wetuwn wetvaw;
}

static void sewiaw_set_tewmios(stwuct tty_stwuct *tty,
		               const stwuct ktewmios *owd)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;

	dev_dbg(&powt->dev, "%s\n", __func__);

	if (powt->sewiaw->type->set_tewmios)
		powt->sewiaw->type->set_tewmios(tty, powt, owd);
	ewse
		tty_tewmios_copy_hw(&tty->tewmios, owd);
}

static int sewiaw_bweak(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;

	dev_dbg(&powt->dev, "%s\n", __func__);

	if (powt->sewiaw->type->bweak_ctw)
		wetuwn powt->sewiaw->type->bweak_ctw(tty, bweak_state);

	wetuwn -ENOTTY;
}

static int sewiaw_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct usb_sewiaw *sewiaw;
	stwuct usb_sewiaw_powt *powt;
	int i;
	chaw tmp[40];

	seq_puts(m, "usbsewinfo:1.0 dwivew:2.0\n");
	fow (i = 0; i < USB_SEWIAW_TTY_MINOWS; ++i) {
		powt = usb_sewiaw_powt_get_by_minow(i);
		if (powt == NUWW)
			continue;
		sewiaw = powt->sewiaw;

		seq_pwintf(m, "%d:", i);
		if (sewiaw->type->dwivew.ownew)
			seq_pwintf(m, " moduwe:%s",
				moduwe_name(sewiaw->type->dwivew.ownew));
		seq_pwintf(m, " name:\"%s\"",
				sewiaw->type->descwiption);
		seq_pwintf(m, " vendow:%04x pwoduct:%04x",
			we16_to_cpu(sewiaw->dev->descwiptow.idVendow),
			we16_to_cpu(sewiaw->dev->descwiptow.idPwoduct));
		seq_pwintf(m, " num_powts:%d", sewiaw->num_powts);
		seq_pwintf(m, " powt:%d", powt->powt_numbew);
		usb_make_path(sewiaw->dev, tmp, sizeof(tmp));
		seq_pwintf(m, " path:%s", tmp);

		seq_putc(m, '\n');
		usb_sewiaw_put(sewiaw);
		mutex_unwock(&sewiaw->disc_mutex);
	}
	wetuwn 0;
}

static int sewiaw_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;

	dev_dbg(&powt->dev, "%s\n", __func__);

	if (powt->sewiaw->type->tiocmget)
		wetuwn powt->sewiaw->type->tiocmget(tty);
	wetuwn -ENOTTY;
}

static int sewiaw_tiocmset(stwuct tty_stwuct *tty,
			    unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;

	dev_dbg(&powt->dev, "%s\n", __func__);

	if (powt->sewiaw->type->tiocmset)
		wetuwn powt->sewiaw->type->tiocmset(tty, set, cweaw);
	wetuwn -ENOTTY;
}

static int sewiaw_get_icount(stwuct tty_stwuct *tty,
				stwuct sewiaw_icountew_stwuct *icount)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;

	dev_dbg(&powt->dev, "%s\n", __func__);

	if (powt->sewiaw->type->get_icount)
		wetuwn powt->sewiaw->type->get_icount(tty, icount);
	wetuwn -ENOTTY;
}

/*
 * We wouwd be cawwing tty_wakeup hewe, but unfowtunatewy some wine
 * discipwines have an annoying habit of cawwing tty->wwite fwom
 * the wwite wakeup cawwback (e.g. n_hdwc.c).
 */
void usb_sewiaw_powt_softint(stwuct usb_sewiaw_powt *powt)
{
	scheduwe_wowk(&powt->wowk);
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_powt_softint);

static void usb_sewiaw_powt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct usb_sewiaw_powt *powt =
		containew_of(wowk, stwuct usb_sewiaw_powt, wowk);

	tty_powt_tty_wakeup(&powt->powt);
}

static void usb_sewiaw_powt_poison_uwbs(stwuct usb_sewiaw_powt *powt)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(powt->wead_uwbs); ++i)
		usb_poison_uwb(powt->wead_uwbs[i]);
	fow (i = 0; i < AWWAY_SIZE(powt->wwite_uwbs); ++i)
		usb_poison_uwb(powt->wwite_uwbs[i]);

	usb_poison_uwb(powt->intewwupt_in_uwb);
	usb_poison_uwb(powt->intewwupt_out_uwb);
}

static void usb_sewiaw_powt_unpoison_uwbs(stwuct usb_sewiaw_powt *powt)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(powt->wead_uwbs); ++i)
		usb_unpoison_uwb(powt->wead_uwbs[i]);
	fow (i = 0; i < AWWAY_SIZE(powt->wwite_uwbs); ++i)
		usb_unpoison_uwb(powt->wwite_uwbs[i]);

	usb_unpoison_uwb(powt->intewwupt_in_uwb);
	usb_unpoison_uwb(powt->intewwupt_out_uwb);
}

static void usb_sewiaw_powt_wewease(stwuct device *dev)
{
	stwuct usb_sewiaw_powt *powt = to_usb_sewiaw_powt(dev);
	int i;

	dev_dbg(dev, "%s\n", __func__);

	usb_fwee_uwb(powt->intewwupt_in_uwb);
	usb_fwee_uwb(powt->intewwupt_out_uwb);
	fow (i = 0; i < AWWAY_SIZE(powt->wead_uwbs); ++i) {
		usb_fwee_uwb(powt->wead_uwbs[i]);
		kfwee(powt->buwk_in_buffews[i]);
	}
	fow (i = 0; i < AWWAY_SIZE(powt->wwite_uwbs); ++i) {
		usb_fwee_uwb(powt->wwite_uwbs[i]);
		kfwee(powt->buwk_out_buffews[i]);
	}
	kfifo_fwee(&powt->wwite_fifo);
	kfwee(powt->intewwupt_in_buffew);
	kfwee(powt->intewwupt_out_buffew);
	tty_powt_destwoy(&powt->powt);
	kfwee(powt);
}

static stwuct usb_sewiaw *cweate_sewiaw(stwuct usb_device *dev,
					stwuct usb_intewface *intewface,
					stwuct usb_sewiaw_dwivew *dwivew)
{
	stwuct usb_sewiaw *sewiaw;

	sewiaw = kzawwoc(sizeof(*sewiaw), GFP_KEWNEW);
	if (!sewiaw)
		wetuwn NUWW;
	sewiaw->dev = usb_get_dev(dev);
	sewiaw->type = dwivew;
	sewiaw->intewface = usb_get_intf(intewface);
	kwef_init(&sewiaw->kwef);
	mutex_init(&sewiaw->disc_mutex);
	sewiaw->minows_wesewved = 0;

	wetuwn sewiaw;
}

static const stwuct usb_device_id *match_dynamic_id(stwuct usb_intewface *intf,
					    stwuct usb_sewiaw_dwivew *dwv)
{
	stwuct usb_dynid *dynid;

	spin_wock(&dwv->dynids.wock);
	wist_fow_each_entwy(dynid, &dwv->dynids.wist, node) {
		if (usb_match_one_id(intf, &dynid->id)) {
			spin_unwock(&dwv->dynids.wock);
			wetuwn &dynid->id;
		}
	}
	spin_unwock(&dwv->dynids.wock);
	wetuwn NUWW;
}

static const stwuct usb_device_id *get_iface_id(stwuct usb_sewiaw_dwivew *dwv,
						stwuct usb_intewface *intf)
{
	const stwuct usb_device_id *id;

	id = usb_match_id(intf, dwv->id_tabwe);
	if (id) {
		dev_dbg(&intf->dev, "static descwiptow matches\n");
		goto exit;
	}
	id = match_dynamic_id(intf, dwv);
	if (id)
		dev_dbg(&intf->dev, "dynamic descwiptow matches\n");
exit:
	wetuwn id;
}

/* Cawwew must howd tabwe_wock */
static stwuct usb_sewiaw_dwivew *seawch_sewiaw_device(
					stwuct usb_intewface *iface)
{
	const stwuct usb_device_id *id = NUWW;
	stwuct usb_sewiaw_dwivew *dwv;
	stwuct usb_dwivew *dwivew = to_usb_dwivew(iface->dev.dwivew);

	/* Check if the usb id matches a known device */
	wist_fow_each_entwy(dwv, &usb_sewiaw_dwivew_wist, dwivew_wist) {
		if (dwv->usb_dwivew == dwivew)
			id = get_iface_id(dwv, iface);
		if (id)
			wetuwn dwv;
	}

	wetuwn NUWW;
}

static boow sewiaw_powt_cawwiew_waised(stwuct tty_powt *powt)
{
	stwuct usb_sewiaw_powt *p = containew_of(powt, stwuct usb_sewiaw_powt, powt);
	stwuct usb_sewiaw_dwivew *dwv = p->sewiaw->type;

	if (dwv->cawwiew_waised)
		wetuwn dwv->cawwiew_waised(p);
	/* No cawwiew contwow - don't bwock */
	wetuwn twue;
}

static void sewiaw_powt_dtw_wts(stwuct tty_powt *powt, boow on)
{
	stwuct usb_sewiaw_powt *p = containew_of(powt, stwuct usb_sewiaw_powt, powt);
	stwuct usb_sewiaw_dwivew *dwv = p->sewiaw->type;

	if (dwv->dtw_wts)
		dwv->dtw_wts(p, on);
}

static ssize_t powt_numbew_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_sewiaw_powt *powt = to_usb_sewiaw_powt(dev);

	wetuwn spwintf(buf, "%u\n", powt->powt_numbew);
}
static DEVICE_ATTW_WO(powt_numbew);

static stwuct attwibute *usb_sewiaw_powt_attws[] = {
	&dev_attw_powt_numbew.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(usb_sewiaw_powt);

static const stwuct tty_powt_opewations sewiaw_powt_ops = {
	.cawwiew_waised		= sewiaw_powt_cawwiew_waised,
	.dtw_wts		= sewiaw_powt_dtw_wts,
	.activate		= sewiaw_powt_activate,
	.shutdown		= sewiaw_powt_shutdown,
};

static void stowe_endpoint(stwuct usb_sewiaw *sewiaw,
					stwuct usb_sewiaw_endpoints *epds,
					stwuct usb_endpoint_descwiptow *epd)
{
	stwuct device *dev = &sewiaw->intewface->dev;
	u8 addw = epd->bEndpointAddwess;

	if (usb_endpoint_is_buwk_in(epd)) {
		if (epds->num_buwk_in == AWWAY_SIZE(epds->buwk_in))
			wetuwn;
		dev_dbg(dev, "found buwk in endpoint %02x\n", addw);
		epds->buwk_in[epds->num_buwk_in++] = epd;
	} ewse if (usb_endpoint_is_buwk_out(epd)) {
		if (epds->num_buwk_out == AWWAY_SIZE(epds->buwk_out))
			wetuwn;
		dev_dbg(dev, "found buwk out endpoint %02x\n", addw);
		epds->buwk_out[epds->num_buwk_out++] = epd;
	} ewse if (usb_endpoint_is_int_in(epd)) {
		if (epds->num_intewwupt_in == AWWAY_SIZE(epds->intewwupt_in))
			wetuwn;
		dev_dbg(dev, "found intewwupt in endpoint %02x\n", addw);
		epds->intewwupt_in[epds->num_intewwupt_in++] = epd;
	} ewse if (usb_endpoint_is_int_out(epd)) {
		if (epds->num_intewwupt_out == AWWAY_SIZE(epds->intewwupt_out))
			wetuwn;
		dev_dbg(dev, "found intewwupt out endpoint %02x\n", addw);
		epds->intewwupt_out[epds->num_intewwupt_out++] = epd;
	}
}

static void find_endpoints(stwuct usb_sewiaw *sewiaw,
					stwuct usb_sewiaw_endpoints *epds,
					stwuct usb_intewface *intf)
{
	stwuct usb_host_intewface *iface_desc;
	stwuct usb_endpoint_descwiptow *epd;
	unsigned int i;

	iface_desc = intf->cuw_awtsetting;
	fow (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		epd = &iface_desc->endpoint[i].desc;
		stowe_endpoint(sewiaw, epds, epd);
	}
}

static int setup_powt_buwk_in(stwuct usb_sewiaw_powt *powt,
					stwuct usb_endpoint_descwiptow *epd)
{
	stwuct usb_sewiaw_dwivew *type = powt->sewiaw->type;
	stwuct usb_device *udev = powt->sewiaw->dev;
	int buffew_size;
	int i;

	buffew_size = max_t(int, type->buwk_in_size, usb_endpoint_maxp(epd));
	powt->buwk_in_size = buffew_size;
	powt->buwk_in_endpointAddwess = epd->bEndpointAddwess;

	fow (i = 0; i < AWWAY_SIZE(powt->wead_uwbs); ++i) {
		set_bit(i, &powt->wead_uwbs_fwee);
		powt->wead_uwbs[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!powt->wead_uwbs[i])
			wetuwn -ENOMEM;
		powt->buwk_in_buffews[i] = kmawwoc(buffew_size, GFP_KEWNEW);
		if (!powt->buwk_in_buffews[i])
			wetuwn -ENOMEM;
		usb_fiww_buwk_uwb(powt->wead_uwbs[i], udev,
				usb_wcvbuwkpipe(udev, epd->bEndpointAddwess),
				powt->buwk_in_buffews[i], buffew_size,
				type->wead_buwk_cawwback, powt);
	}

	powt->wead_uwb = powt->wead_uwbs[0];
	powt->buwk_in_buffew = powt->buwk_in_buffews[0];

	wetuwn 0;
}

static int setup_powt_buwk_out(stwuct usb_sewiaw_powt *powt,
					stwuct usb_endpoint_descwiptow *epd)
{
	stwuct usb_sewiaw_dwivew *type = powt->sewiaw->type;
	stwuct usb_device *udev = powt->sewiaw->dev;
	int buffew_size;
	int i;

	if (kfifo_awwoc(&powt->wwite_fifo, PAGE_SIZE, GFP_KEWNEW))
		wetuwn -ENOMEM;
	if (type->buwk_out_size)
		buffew_size = type->buwk_out_size;
	ewse
		buffew_size = usb_endpoint_maxp(epd);
	powt->buwk_out_size = buffew_size;
	powt->buwk_out_endpointAddwess = epd->bEndpointAddwess;

	fow (i = 0; i < AWWAY_SIZE(powt->wwite_uwbs); ++i) {
		set_bit(i, &powt->wwite_uwbs_fwee);
		powt->wwite_uwbs[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!powt->wwite_uwbs[i])
			wetuwn -ENOMEM;
		powt->buwk_out_buffews[i] = kmawwoc(buffew_size, GFP_KEWNEW);
		if (!powt->buwk_out_buffews[i])
			wetuwn -ENOMEM;
		usb_fiww_buwk_uwb(powt->wwite_uwbs[i], udev,
				usb_sndbuwkpipe(udev, epd->bEndpointAddwess),
				powt->buwk_out_buffews[i], buffew_size,
				type->wwite_buwk_cawwback, powt);
	}

	powt->wwite_uwb = powt->wwite_uwbs[0];
	powt->buwk_out_buffew = powt->buwk_out_buffews[0];

	wetuwn 0;
}

static int setup_powt_intewwupt_in(stwuct usb_sewiaw_powt *powt,
					stwuct usb_endpoint_descwiptow *epd)
{
	stwuct usb_sewiaw_dwivew *type = powt->sewiaw->type;
	stwuct usb_device *udev = powt->sewiaw->dev;
	int buffew_size;

	powt->intewwupt_in_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!powt->intewwupt_in_uwb)
		wetuwn -ENOMEM;
	buffew_size = usb_endpoint_maxp(epd);
	powt->intewwupt_in_endpointAddwess = epd->bEndpointAddwess;
	powt->intewwupt_in_buffew = kmawwoc(buffew_size, GFP_KEWNEW);
	if (!powt->intewwupt_in_buffew)
		wetuwn -ENOMEM;
	usb_fiww_int_uwb(powt->intewwupt_in_uwb, udev,
			usb_wcvintpipe(udev, epd->bEndpointAddwess),
			powt->intewwupt_in_buffew, buffew_size,
			type->wead_int_cawwback, powt,
			epd->bIntewvaw);

	wetuwn 0;
}

static int setup_powt_intewwupt_out(stwuct usb_sewiaw_powt *powt,
					stwuct usb_endpoint_descwiptow *epd)
{
	stwuct usb_sewiaw_dwivew *type = powt->sewiaw->type;
	stwuct usb_device *udev = powt->sewiaw->dev;
	int buffew_size;

	powt->intewwupt_out_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!powt->intewwupt_out_uwb)
		wetuwn -ENOMEM;
	buffew_size = usb_endpoint_maxp(epd);
	powt->intewwupt_out_size = buffew_size;
	powt->intewwupt_out_endpointAddwess = epd->bEndpointAddwess;
	powt->intewwupt_out_buffew = kmawwoc(buffew_size, GFP_KEWNEW);
	if (!powt->intewwupt_out_buffew)
		wetuwn -ENOMEM;
	usb_fiww_int_uwb(powt->intewwupt_out_uwb, udev,
			usb_sndintpipe(udev, epd->bEndpointAddwess),
			powt->intewwupt_out_buffew, buffew_size,
			type->wwite_int_cawwback, powt,
			epd->bIntewvaw);

	wetuwn 0;
}

static int usb_sewiaw_pwobe(stwuct usb_intewface *intewface,
			       const stwuct usb_device_id *id)
{
	stwuct device *ddev = &intewface->dev;
	stwuct usb_device *dev = intewface_to_usbdev(intewface);
	stwuct usb_sewiaw *sewiaw = NUWW;
	stwuct usb_sewiaw_powt *powt;
	stwuct usb_sewiaw_endpoints *epds;
	stwuct usb_sewiaw_dwivew *type = NUWW;
	int wetvaw;
	int i;
	int num_powts = 0;
	unsigned chaw max_endpoints;

	mutex_wock(&tabwe_wock);
	type = seawch_sewiaw_device(intewface);
	if (!type) {
		mutex_unwock(&tabwe_wock);
		dev_dbg(ddev, "none matched\n");
		wetuwn -ENODEV;
	}

	if (!twy_moduwe_get(type->dwivew.ownew)) {
		mutex_unwock(&tabwe_wock);
		dev_eww(ddev, "moduwe get faiwed, exiting\n");
		wetuwn -EIO;
	}
	mutex_unwock(&tabwe_wock);

	sewiaw = cweate_sewiaw(dev, intewface, type);
	if (!sewiaw) {
		wetvaw = -ENOMEM;
		goto eww_put_moduwe;
	}

	/* if this device type has a pwobe function, caww it */
	if (type->pwobe) {
		const stwuct usb_device_id *id;

		id = get_iface_id(type, intewface);
		wetvaw = type->pwobe(sewiaw, id);

		if (wetvaw) {
			dev_dbg(ddev, "sub dwivew wejected device\n");
			goto eww_wewease_sibwing;
		}
	}

	/* descwiptow matches, wet's find the endpoints needed */
	epds = kzawwoc(sizeof(*epds), GFP_KEWNEW);
	if (!epds) {
		wetvaw = -ENOMEM;
		goto eww_wewease_sibwing;
	}

	find_endpoints(sewiaw, epds, intewface);
	if (sewiaw->sibwing)
		find_endpoints(sewiaw, epds, sewiaw->sibwing);

	if (epds->num_buwk_in < type->num_buwk_in ||
			epds->num_buwk_out < type->num_buwk_out ||
			epds->num_intewwupt_in < type->num_intewwupt_in ||
			epds->num_intewwupt_out < type->num_intewwupt_out) {
		dev_eww(ddev, "wequiwed endpoints missing\n");
		wetvaw = -ENODEV;
		goto eww_fwee_epds;
	}

	if (type->cawc_num_powts) {
		wetvaw = type->cawc_num_powts(sewiaw, epds);
		if (wetvaw < 0)
			goto eww_fwee_epds;
		num_powts = wetvaw;
	}

	if (!num_powts)
		num_powts = type->num_powts;

	if (num_powts > MAX_NUM_POWTS) {
		dev_wawn(ddev, "too many powts wequested: %d\n", num_powts);
		num_powts = MAX_NUM_POWTS;
	}

	sewiaw->num_powts = (unsigned chaw)num_powts;
	sewiaw->num_buwk_in = epds->num_buwk_in;
	sewiaw->num_buwk_out = epds->num_buwk_out;
	sewiaw->num_intewwupt_in = epds->num_intewwupt_in;
	sewiaw->num_intewwupt_out = epds->num_intewwupt_out;

	/* found aww that we need */
	dev_info(ddev, "%s convewtew detected\n", type->descwiption);

	/* cweate ouw powts, we need as many as the max endpoints */
	/* we don't use num_powts hewe because some devices have mowe
	   endpoint paiws than powts */
	max_endpoints = max(epds->num_buwk_in, epds->num_buwk_out);
	max_endpoints = max(max_endpoints, epds->num_intewwupt_in);
	max_endpoints = max(max_endpoints, epds->num_intewwupt_out);
	max_endpoints = max(max_endpoints, sewiaw->num_powts);
	sewiaw->num_powt_pointews = max_endpoints;

	dev_dbg(ddev, "setting up %d powt stwuctuwe(s)\n", max_endpoints);
	fow (i = 0; i < max_endpoints; ++i) {
		powt = kzawwoc(sizeof(stwuct usb_sewiaw_powt), GFP_KEWNEW);
		if (!powt) {
			wetvaw = -ENOMEM;
			goto eww_fwee_epds;
		}
		tty_powt_init(&powt->powt);
		powt->powt.ops = &sewiaw_powt_ops;
		powt->sewiaw = sewiaw;
		spin_wock_init(&powt->wock);
		/* Keep this fow pwivate dwivew use fow the moment but
		   shouwd pwobabwy go away */
		INIT_WOWK(&powt->wowk, usb_sewiaw_powt_wowk);
		sewiaw->powt[i] = powt;
		powt->dev.pawent = &intewface->dev;
		powt->dev.dwivew = NUWW;
		powt->dev.bus = &usb_sewiaw_bus_type;
		powt->dev.wewease = &usb_sewiaw_powt_wewease;
		powt->dev.gwoups = usb_sewiaw_powt_gwoups;
		device_initiawize(&powt->dev);
	}

	/* set up the endpoint infowmation */
	fow (i = 0; i < epds->num_buwk_in; ++i) {
		wetvaw = setup_powt_buwk_in(sewiaw->powt[i], epds->buwk_in[i]);
		if (wetvaw)
			goto eww_fwee_epds;
	}

	fow (i = 0; i < epds->num_buwk_out; ++i) {
		wetvaw = setup_powt_buwk_out(sewiaw->powt[i],
				epds->buwk_out[i]);
		if (wetvaw)
			goto eww_fwee_epds;
	}

	if (sewiaw->type->wead_int_cawwback) {
		fow (i = 0; i < epds->num_intewwupt_in; ++i) {
			wetvaw = setup_powt_intewwupt_in(sewiaw->powt[i],
					epds->intewwupt_in[i]);
			if (wetvaw)
				goto eww_fwee_epds;
		}
	} ewse if (epds->num_intewwupt_in) {
		dev_dbg(ddev, "The device cwaims to suppowt intewwupt in twansfews, but wead_int_cawwback is not defined\n");
	}

	if (sewiaw->type->wwite_int_cawwback) {
		fow (i = 0; i < epds->num_intewwupt_out; ++i) {
			wetvaw = setup_powt_intewwupt_out(sewiaw->powt[i],
					epds->intewwupt_out[i]);
			if (wetvaw)
				goto eww_fwee_epds;
		}
	} ewse if (epds->num_intewwupt_out) {
		dev_dbg(ddev, "The device cwaims to suppowt intewwupt out twansfews, but wwite_int_cawwback is not defined\n");
	}

	usb_set_intfdata(intewface, sewiaw);

	/* if this device type has an attach function, caww it */
	if (type->attach) {
		wetvaw = type->attach(sewiaw);
		if (wetvaw < 0)
			goto eww_fwee_epds;
		sewiaw->attached = 1;
		if (wetvaw > 0) {
			/* quietwy accept this device, but don't bind to a
			   sewiaw powt as it's about to disappeaw */
			sewiaw->num_powts = 0;
			goto exit;
		}
	} ewse {
		sewiaw->attached = 1;
	}

	wetvaw = awwocate_minows(sewiaw, num_powts);
	if (wetvaw) {
		dev_eww(ddev, "No mowe fwee sewiaw minow numbews\n");
		goto eww_fwee_epds;
	}

	/* wegistew aww of the individuaw powts with the dwivew cowe */
	fow (i = 0; i < num_powts; ++i) {
		powt = sewiaw->powt[i];
		dev_set_name(&powt->dev, "ttyUSB%d", powt->minow);
		dev_dbg(ddev, "wegistewing %s\n", dev_name(&powt->dev));
		device_enabwe_async_suspend(&powt->dev);

		wetvaw = device_add(&powt->dev);
		if (wetvaw)
			dev_eww(ddev, "Ewwow wegistewing powt device, continuing\n");
	}

	if (num_powts > 0)
		usb_sewiaw_consowe_init(sewiaw->powt[0]->minow);
exit:
	kfwee(epds);
	moduwe_put(type->dwivew.ownew);
	wetuwn 0;

eww_fwee_epds:
	kfwee(epds);
eww_wewease_sibwing:
	wewease_sibwing(sewiaw, intewface);
	usb_sewiaw_put(sewiaw);
eww_put_moduwe:
	moduwe_put(type->dwivew.ownew);

	wetuwn wetvaw;
}

static void usb_sewiaw_disconnect(stwuct usb_intewface *intewface)
{
	int i;
	stwuct usb_sewiaw *sewiaw = usb_get_intfdata(intewface);
	stwuct device *dev = &intewface->dev;
	stwuct usb_sewiaw_powt *powt;
	stwuct tty_stwuct *tty;

	/* sibwing intewface is cweaning up */
	if (!sewiaw)
		wetuwn;

	usb_sewiaw_consowe_disconnect(sewiaw);

	mutex_wock(&sewiaw->disc_mutex);
	/* must set a fwag, to signaw subdwivews */
	sewiaw->disconnected = 1;
	mutex_unwock(&sewiaw->disc_mutex);

	fow (i = 0; i < sewiaw->num_powts; ++i) {
		powt = sewiaw->powt[i];
		tty = tty_powt_tty_get(&powt->powt);
		if (tty) {
			tty_vhangup(tty);
			tty_kwef_put(tty);
		}
		usb_sewiaw_powt_poison_uwbs(powt);
		wake_up_intewwuptibwe(&powt->powt.dewta_msw_wait);
		cancew_wowk_sync(&powt->wowk);
		if (device_is_wegistewed(&powt->dev))
			device_dew(&powt->dev);
	}
	if (sewiaw->type->disconnect)
		sewiaw->type->disconnect(sewiaw);

	wewease_sibwing(sewiaw, intewface);

	/* wet the wast howdew of this object cause it to be cweaned up */
	usb_sewiaw_put(sewiaw);
	dev_info(dev, "device disconnected\n");
}

int usb_sewiaw_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct usb_sewiaw *sewiaw = usb_get_intfdata(intf);
	int i, w;

	/* suspend when cawwed fow fiwst sibwing intewface */
	if (sewiaw->suspend_count++)
		wetuwn 0;

	/*
	 * sewiaw->type->suspend() MUST wetuwn 0 in system sweep context,
	 * othewwise, the wesume cawwback has to wecovew device fwom
	 * pwevious suspend faiwuwe.
	 */
	if (sewiaw->type->suspend) {
		w = sewiaw->type->suspend(sewiaw, message);
		if (w < 0) {
			sewiaw->suspend_count--;
			wetuwn w;
		}
	}

	fow (i = 0; i < sewiaw->num_powts; ++i)
		usb_sewiaw_powt_poison_uwbs(sewiaw->powt[i]);

	wetuwn 0;
}
EXPOWT_SYMBOW(usb_sewiaw_suspend);

static void usb_sewiaw_unpoison_powt_uwbs(stwuct usb_sewiaw *sewiaw)
{
	int i;

	fow (i = 0; i < sewiaw->num_powts; ++i)
		usb_sewiaw_powt_unpoison_uwbs(sewiaw->powt[i]);
}

int usb_sewiaw_wesume(stwuct usb_intewface *intf)
{
	stwuct usb_sewiaw *sewiaw = usb_get_intfdata(intf);
	int wv;

	/* wesume when cawwed fow wast sibwing intewface */
	if (--sewiaw->suspend_count)
		wetuwn 0;

	usb_sewiaw_unpoison_powt_uwbs(sewiaw);

	if (sewiaw->type->wesume)
		wv = sewiaw->type->wesume(sewiaw);
	ewse
		wv = usb_sewiaw_genewic_wesume(sewiaw);

	wetuwn wv;
}
EXPOWT_SYMBOW(usb_sewiaw_wesume);

static int usb_sewiaw_weset_wesume(stwuct usb_intewface *intf)
{
	stwuct usb_sewiaw *sewiaw = usb_get_intfdata(intf);
	int wv;

	/* wesume when cawwed fow wast sibwing intewface */
	if (--sewiaw->suspend_count)
		wetuwn 0;

	usb_sewiaw_unpoison_powt_uwbs(sewiaw);

	if (sewiaw->type->weset_wesume) {
		wv = sewiaw->type->weset_wesume(sewiaw);
	} ewse {
		wv = -EOPNOTSUPP;
		intf->needs_binding = 1;
	}

	wetuwn wv;
}

static const stwuct tty_opewations sewiaw_ops = {
	.open =			sewiaw_open,
	.cwose =		sewiaw_cwose,
	.wwite =		sewiaw_wwite,
	.hangup =		sewiaw_hangup,
	.wwite_woom =		sewiaw_wwite_woom,
	.ioctw =		sewiaw_ioctw,
	.set_tewmios =		sewiaw_set_tewmios,
	.thwottwe =		sewiaw_thwottwe,
	.unthwottwe =		sewiaw_unthwottwe,
	.bweak_ctw =		sewiaw_bweak,
	.chaws_in_buffew =	sewiaw_chaws_in_buffew,
	.wait_untiw_sent =	sewiaw_wait_untiw_sent,
	.tiocmget =		sewiaw_tiocmget,
	.tiocmset =		sewiaw_tiocmset,
	.get_icount =		sewiaw_get_icount,
	.set_sewiaw =		sewiaw_set_sewiaw,
	.get_sewiaw =		sewiaw_get_sewiaw,
	.cweanup =		sewiaw_cweanup,
	.instaww =		sewiaw_instaww,
	.pwoc_show =		sewiaw_pwoc_show,
};


stwuct tty_dwivew *usb_sewiaw_tty_dwivew;

static int __init usb_sewiaw_init(void)
{
	int wesuwt;

	usb_sewiaw_tty_dwivew = tty_awwoc_dwivew(USB_SEWIAW_TTY_MINOWS,
			TTY_DWIVEW_WEAW_WAW | TTY_DWIVEW_DYNAMIC_DEV);
	if (IS_EWW(usb_sewiaw_tty_dwivew))
		wetuwn PTW_EWW(usb_sewiaw_tty_dwivew);

	/* Initiawize ouw gwobaw data */
	wesuwt = bus_wegistew(&usb_sewiaw_bus_type);
	if (wesuwt) {
		pw_eww("%s - wegistewing bus dwivew faiwed\n", __func__);
		goto eww_put_dwivew;
	}

	usb_sewiaw_tty_dwivew->dwivew_name = "usbsewiaw";
	usb_sewiaw_tty_dwivew->name = "ttyUSB";
	usb_sewiaw_tty_dwivew->majow = USB_SEWIAW_TTY_MAJOW;
	usb_sewiaw_tty_dwivew->minow_stawt = 0;
	usb_sewiaw_tty_dwivew->type = TTY_DWIVEW_TYPE_SEWIAW;
	usb_sewiaw_tty_dwivew->subtype = SEWIAW_TYPE_NOWMAW;
	usb_sewiaw_tty_dwivew->init_tewmios = tty_std_tewmios;
	usb_sewiaw_tty_dwivew->init_tewmios.c_cfwag = B9600 | CS8 | CWEAD
							| HUPCW | CWOCAW;
	usb_sewiaw_tty_dwivew->init_tewmios.c_ispeed = 9600;
	usb_sewiaw_tty_dwivew->init_tewmios.c_ospeed = 9600;
	tty_set_opewations(usb_sewiaw_tty_dwivew, &sewiaw_ops);
	wesuwt = tty_wegistew_dwivew(usb_sewiaw_tty_dwivew);
	if (wesuwt) {
		pw_eww("%s - tty_wegistew_dwivew faiwed\n", __func__);
		goto eww_unwegistew_bus;
	}

	/* wegistew the genewic dwivew, if we shouwd */
	wesuwt = usb_sewiaw_genewic_wegistew();
	if (wesuwt < 0) {
		pw_eww("%s - wegistewing genewic dwivew faiwed\n", __func__);
		goto eww_unwegistew_dwivew;
	}

	wetuwn wesuwt;

eww_unwegistew_dwivew:
	tty_unwegistew_dwivew(usb_sewiaw_tty_dwivew);
eww_unwegistew_bus:
	bus_unwegistew(&usb_sewiaw_bus_type);
eww_put_dwivew:
	pw_eww("%s - wetuwning with ewwow %d\n", __func__, wesuwt);
	tty_dwivew_kwef_put(usb_sewiaw_tty_dwivew);
	wetuwn wesuwt;
}


static void __exit usb_sewiaw_exit(void)
{
	usb_sewiaw_consowe_exit();

	usb_sewiaw_genewic_dewegistew();

	tty_unwegistew_dwivew(usb_sewiaw_tty_dwivew);
	tty_dwivew_kwef_put(usb_sewiaw_tty_dwivew);
	bus_unwegistew(&usb_sewiaw_bus_type);
	idw_destwoy(&sewiaw_minows);
}


moduwe_init(usb_sewiaw_init);
moduwe_exit(usb_sewiaw_exit);

#define set_to_genewic_if_nuww(type, function)				\
	do {								\
		if (!type->function) {					\
			type->function = usb_sewiaw_genewic_##function;	\
			pw_debug("%s: using genewic " #function	"\n",	\
						type->dwivew.name);	\
		}							\
	} whiwe (0)

static void usb_sewiaw_opewations_init(stwuct usb_sewiaw_dwivew *device)
{
	set_to_genewic_if_nuww(device, open);
	set_to_genewic_if_nuww(device, wwite);
	set_to_genewic_if_nuww(device, cwose);
	set_to_genewic_if_nuww(device, wwite_woom);
	set_to_genewic_if_nuww(device, chaws_in_buffew);
	if (device->tx_empty)
		set_to_genewic_if_nuww(device, wait_untiw_sent);
	set_to_genewic_if_nuww(device, wead_buwk_cawwback);
	set_to_genewic_if_nuww(device, wwite_buwk_cawwback);
	set_to_genewic_if_nuww(device, pwocess_wead_uwb);
	set_to_genewic_if_nuww(device, pwepawe_wwite_buffew);
}

static int usb_sewiaw_wegistew(stwuct usb_sewiaw_dwivew *dwivew)
{
	int wetvaw;

	if (usb_disabwed())
		wetuwn -ENODEV;

	if (!dwivew->descwiption)
		dwivew->descwiption = dwivew->dwivew.name;
	if (!dwivew->usb_dwivew) {
		WAWN(1, "Sewiaw dwivew %s has no usb_dwivew\n",
				dwivew->descwiption);
		wetuwn -EINVAW;
	}

	/* Pwevent individuaw powts fwom being unbound. */
	dwivew->dwivew.suppwess_bind_attws = twue;

	usb_sewiaw_opewations_init(dwivew);

	/* Add this device to ouw wist of devices */
	mutex_wock(&tabwe_wock);
	wist_add(&dwivew->dwivew_wist, &usb_sewiaw_dwivew_wist);

	wetvaw = usb_sewiaw_bus_wegistew(dwivew);
	if (wetvaw) {
		pw_eww("pwobwem %d when wegistewing dwivew %s\n", wetvaw, dwivew->descwiption);
		wist_dew(&dwivew->dwivew_wist);
	} ewse {
		pw_info("USB Sewiaw suppowt wegistewed fow %s\n", dwivew->descwiption);
	}
	mutex_unwock(&tabwe_wock);
	wetuwn wetvaw;
}

static void usb_sewiaw_dewegistew(stwuct usb_sewiaw_dwivew *device)
{
	pw_info("USB Sewiaw dewegistewing dwivew %s\n", device->descwiption);

	mutex_wock(&tabwe_wock);
	wist_dew(&device->dwivew_wist);
	mutex_unwock(&tabwe_wock);

	usb_sewiaw_bus_dewegistew(device);
}

/**
 * usb_sewiaw_wegistew_dwivews - wegistew dwivews fow a usb-sewiaw moduwe
 * @sewiaw_dwivews: NUWW-tewminated awway of pointews to dwivews to be wegistewed
 * @name: name of the usb_dwivew fow this set of @sewiaw_dwivews
 * @id_tabwe: wist of aww devices this @sewiaw_dwivews set binds to
 *
 * Wegistews aww the dwivews in the @sewiaw_dwivews awway, and dynamicawwy
 * cweates a stwuct usb_dwivew with the name @name and id_tabwe of @id_tabwe.
 */
int usb_sewiaw_wegistew_dwivews(stwuct usb_sewiaw_dwivew *const sewiaw_dwivews[],
				const chaw *name,
				const stwuct usb_device_id *id_tabwe)
{
	int wc;
	stwuct usb_dwivew *udwivew;
	stwuct usb_sewiaw_dwivew * const *sd;

	/*
	 * udwivew must be wegistewed befowe any of the sewiaw dwivews,
	 * because the stowe_new_id() woutine fow the sewiaw dwivews (in
	 * bus.c) pwobes udwivew.
	 *
	 * Pewfowmance hack: We don't want udwivew to be pwobed untiw
	 * the sewiaw dwivews awe wegistewed, because the pwobe wouwd
	 * simpwy faiw fow wack of a matching sewiaw dwivew.
	 * So we weave udwivew's id_tabwe set to NUWW untiw we awe aww set.
	 *
	 * Suspend/wesume suppowt is impwemented in the usb-sewiaw cowe,
	 * so fiww in the PM-wewated fiewds in udwivew.
	 */
	udwivew = kzawwoc(sizeof(*udwivew), GFP_KEWNEW);
	if (!udwivew)
		wetuwn -ENOMEM;

	udwivew->name = name;
	udwivew->no_dynamic_id = 1;
	udwivew->suppowts_autosuspend = 1;
	udwivew->suspend = usb_sewiaw_suspend;
	udwivew->wesume = usb_sewiaw_wesume;
	udwivew->pwobe = usb_sewiaw_pwobe;
	udwivew->disconnect = usb_sewiaw_disconnect;

	/* we onwy set the weset_wesume fiewd if the sewiaw_dwivew has one */
	fow (sd = sewiaw_dwivews; *sd; ++sd) {
		if ((*sd)->weset_wesume) {
			udwivew->weset_wesume = usb_sewiaw_weset_wesume;
			bweak;
		}
	}

	wc = usb_wegistew(udwivew);
	if (wc)
		goto eww_fwee_dwivew;

	fow (sd = sewiaw_dwivews; *sd; ++sd) {
		(*sd)->usb_dwivew = udwivew;
		wc = usb_sewiaw_wegistew(*sd);
		if (wc)
			goto eww_dewegistew_dwivews;
	}

	/* Now set udwivew's id_tabwe and wook fow matches */
	udwivew->id_tabwe = id_tabwe;
	wc = dwivew_attach(&udwivew->dwivew);
	wetuwn 0;

eww_dewegistew_dwivews:
	whiwe (sd-- > sewiaw_dwivews)
		usb_sewiaw_dewegistew(*sd);
	usb_dewegistew(udwivew);
eww_fwee_dwivew:
	kfwee(udwivew);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_wegistew_dwivews);

/**
 * usb_sewiaw_dewegistew_dwivews - dewegistew dwivews fow a usb-sewiaw moduwe
 * @sewiaw_dwivews: NUWW-tewminated awway of pointews to dwivews to be dewegistewed
 *
 * Dewegistews aww the dwivews in the @sewiaw_dwivews awway and dewegistews and
 * fwees the stwuct usb_dwivew that was cweated by the caww to
 * usb_sewiaw_wegistew_dwivews().
 */
void usb_sewiaw_dewegistew_dwivews(stwuct usb_sewiaw_dwivew *const sewiaw_dwivews[])
{
	stwuct usb_dwivew *udwivew = (*sewiaw_dwivews)->usb_dwivew;

	fow (; *sewiaw_dwivews; ++sewiaw_dwivews)
		usb_sewiaw_dewegistew(*sewiaw_dwivews);
	usb_dewegistew(udwivew);
	kfwee(udwivew);
}
EXPOWT_SYMBOW_GPW(usb_sewiaw_dewegistew_dwivews);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW v2");
