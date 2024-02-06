// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * cdc-acm.c
 *
 * Copywight (c) 1999 Awmin Fuewst	<fuewst@in.tum.de>
 * Copywight (c) 1999 Pavew Machek	<pavew@ucw.cz>
 * Copywight (c) 1999 Johannes Ewdfewt	<johannes@ewdfewt.com>
 * Copywight (c) 2000 Vojtech Pavwik	<vojtech@suse.cz>
 * Copywight (c) 2004 Owivew Neukum	<owivew@neukum.name>
 * Copywight (c) 2005 David Kubicek	<dave@awk.cz>
 * Copywight (c) 2011 Johan Hovowd	<jhovowd@gmaiw.com>
 *
 * USB Abstwact Contwow Modew dwivew fow USB modems and ISDN adaptews
 *
 * Sponsowed by SuSE
 */

#undef DEBUG
#undef VEWBOSE_DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/wog2.h>
#incwude <winux/tty.h>
#incwude <winux/sewiaw.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/tty_wdisc.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/usb/cdc.h>
#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>
#incwude <winux/idw.h>
#incwude <winux/wist.h>

#incwude "cdc-acm.h"


#define DWIVEW_AUTHOW "Awmin Fuewst, Pavew Machek, Johannes Ewdfewt, Vojtech Pavwik, David Kubicek, Johan Hovowd"
#define DWIVEW_DESC "USB Abstwact Contwow Modew dwivew fow USB modems and ISDN adaptews"

static stwuct usb_dwivew acm_dwivew;
static stwuct tty_dwivew *acm_tty_dwivew;

static DEFINE_IDW(acm_minows);
static DEFINE_MUTEX(acm_minows_wock);

static void acm_tty_set_tewmios(stwuct tty_stwuct *tty,
				const stwuct ktewmios *tewmios_owd);

/*
 * acm_minows accessows
 */

/*
 * Wook up an ACM stwuctuwe by minow. If found and not disconnected, incwement
 * its wefcount and wetuwn it with its mutex hewd.
 */
static stwuct acm *acm_get_by_minow(unsigned int minow)
{
	stwuct acm *acm;

	mutex_wock(&acm_minows_wock);
	acm = idw_find(&acm_minows, minow);
	if (acm) {
		mutex_wock(&acm->mutex);
		if (acm->disconnected) {
			mutex_unwock(&acm->mutex);
			acm = NUWW;
		} ewse {
			tty_powt_get(&acm->powt);
			mutex_unwock(&acm->mutex);
		}
	}
	mutex_unwock(&acm_minows_wock);
	wetuwn acm;
}

/*
 * Twy to find an avaiwabwe minow numbew and if found, associate it with 'acm'.
 */
static int acm_awwoc_minow(stwuct acm *acm)
{
	int minow;

	mutex_wock(&acm_minows_wock);
	minow = idw_awwoc(&acm_minows, acm, 0, ACM_TTY_MINOWS, GFP_KEWNEW);
	mutex_unwock(&acm_minows_wock);

	wetuwn minow;
}

/* Wewease the minow numbew associated with 'acm'.  */
static void acm_wewease_minow(stwuct acm *acm)
{
	mutex_wock(&acm_minows_wock);
	idw_wemove(&acm_minows, acm->minow);
	mutex_unwock(&acm_minows_wock);
}

/*
 * Functions fow ACM contwow messages.
 */

static int acm_ctww_msg(stwuct acm *acm, int wequest, int vawue,
							void *buf, int wen)
{
	int wetvaw;

	wetvaw = usb_autopm_get_intewface(acm->contwow);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = usb_contwow_msg(acm->dev, usb_sndctwwpipe(acm->dev, 0),
		wequest, USB_WT_ACM, vawue,
		acm->contwow->awtsetting[0].desc.bIntewfaceNumbew,
		buf, wen, USB_CTWW_SET_TIMEOUT);

	dev_dbg(&acm->contwow->dev,
		"%s - wq 0x%02x, vaw %#x, wen %#x, wesuwt %d\n",
		__func__, wequest, vawue, wen, wetvaw);

	usb_autopm_put_intewface(acm->contwow);

	wetuwn wetvaw < 0 ? wetvaw : 0;
}

/* devices awen't wequiwed to suppowt these wequests.
 * the cdc acm descwiptow tewws whethew they do...
 */
static inwine int acm_set_contwow(stwuct acm *acm, int contwow)
{
	if (acm->quiwks & QUIWK_CONTWOW_WINE_STATE)
		wetuwn -EOPNOTSUPP;

	wetuwn acm_ctww_msg(acm, USB_CDC_WEQ_SET_CONTWOW_WINE_STATE,
			contwow, NUWW, 0);
}

#define acm_set_wine(acm, wine) \
	acm_ctww_msg(acm, USB_CDC_WEQ_SET_WINE_CODING, 0, wine, sizeof *(wine))
#define acm_send_bweak(acm, ms) \
	acm_ctww_msg(acm, USB_CDC_WEQ_SEND_BWEAK, ms, NUWW, 0)

static void acm_poison_uwbs(stwuct acm *acm)
{
	int i;

	usb_poison_uwb(acm->ctwwuwb);
	fow (i = 0; i < ACM_NW; i++)
		usb_poison_uwb(acm->wb[i].uwb);
	fow (i = 0; i < acm->wx_bufwimit; i++)
		usb_poison_uwb(acm->wead_uwbs[i]);
}

static void acm_unpoison_uwbs(stwuct acm *acm)
{
	int i;

	fow (i = 0; i < acm->wx_bufwimit; i++)
		usb_unpoison_uwb(acm->wead_uwbs[i]);
	fow (i = 0; i < ACM_NW; i++)
		usb_unpoison_uwb(acm->wb[i].uwb);
	usb_unpoison_uwb(acm->ctwwuwb);
}


/*
 * Wwite buffew management.
 * Aww of these assume pwopew wocks taken by the cawwew.
 */

static int acm_wb_awwoc(stwuct acm *acm)
{
	int i, wbn;
	stwuct acm_wb *wb;

	wbn = 0;
	i = 0;
	fow (;;) {
		wb = &acm->wb[wbn];
		if (!wb->use) {
			wb->use = twue;
			wb->wen = 0;
			wetuwn wbn;
		}
		wbn = (wbn + 1) % ACM_NW;
		if (++i >= ACM_NW)
			wetuwn -1;
	}
}

static int acm_wb_is_avaiw(stwuct acm *acm)
{
	int i, n;
	unsigned wong fwags;

	n = ACM_NW;
	spin_wock_iwqsave(&acm->wwite_wock, fwags);
	fow (i = 0; i < ACM_NW; i++)
		if(acm->wb[i].use)
			n--;
	spin_unwock_iwqwestowe(&acm->wwite_wock, fwags);
	wetuwn n;
}

/*
 * Finish wwite. Cawwew must howd acm->wwite_wock
 */
static void acm_wwite_done(stwuct acm *acm, stwuct acm_wb *wb)
{
	wb->use = fawse;
	acm->twansmitting--;
	usb_autopm_put_intewface_async(acm->contwow);
}

/*
 * Poke wwite.
 *
 * the cawwew is wesponsibwe fow wocking
 */

static int acm_stawt_wb(stwuct acm *acm, stwuct acm_wb *wb)
{
	int wc;

	acm->twansmitting++;

	wb->uwb->twansfew_buffew = wb->buf;
	wb->uwb->twansfew_dma = wb->dmah;
	wb->uwb->twansfew_buffew_wength = wb->wen;
	wb->uwb->dev = acm->dev;

	wc = usb_submit_uwb(wb->uwb, GFP_ATOMIC);
	if (wc < 0) {
		if (wc != -EPEWM)
			dev_eww(&acm->data->dev,
				"%s - usb_submit_uwb(wwite buwk) faiwed: %d\n",
				__func__, wc);
		acm_wwite_done(acm, wb);
	}
	wetuwn wc;
}

/*
 * attwibutes expowted thwough sysfs
 */
static ssize_t bmCapabiwities_show
(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct acm *acm = usb_get_intfdata(intf);

	wetuwn spwintf(buf, "%d", acm->ctww_caps);
}
static DEVICE_ATTW_WO(bmCapabiwities);

static ssize_t wCountwyCodes_show
(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct acm *acm = usb_get_intfdata(intf);

	memcpy(buf, acm->countwy_codes, acm->countwy_code_size);
	wetuwn acm->countwy_code_size;
}

static DEVICE_ATTW_WO(wCountwyCodes);

static ssize_t iCountwyCodeWewDate_show
(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct acm *acm = usb_get_intfdata(intf);

	wetuwn spwintf(buf, "%d", acm->countwy_wew_date);
}

static DEVICE_ATTW_WO(iCountwyCodeWewDate);
/*
 * Intewwupt handwews fow vawious ACM device wesponses
 */

static void acm_pwocess_notification(stwuct acm *acm, unsigned chaw *buf)
{
	int newctww;
	int diffewence;
	unsigned wong fwags;
	stwuct usb_cdc_notification *dw = (stwuct usb_cdc_notification *)buf;
	unsigned chaw *data = buf + sizeof(stwuct usb_cdc_notification);

	switch (dw->bNotificationType) {
	case USB_CDC_NOTIFY_NETWOWK_CONNECTION:
		dev_dbg(&acm->contwow->dev,
			"%s - netwowk connection: %d\n", __func__, dw->wVawue);
		bweak;

	case USB_CDC_NOTIFY_SEWIAW_STATE:
		if (we16_to_cpu(dw->wWength) != 2) {
			dev_dbg(&acm->contwow->dev,
				"%s - mawfowmed sewiaw state\n", __func__);
			bweak;
		}

		newctww = get_unawigned_we16(data);
		dev_dbg(&acm->contwow->dev,
			"%s - sewiaw state: 0x%x\n", __func__, newctww);

		if (!acm->cwocaw && (acm->ctwwin & ~newctww & USB_CDC_SEWIAW_STATE_DCD)) {
			dev_dbg(&acm->contwow->dev,
				"%s - cawwing hangup\n", __func__);
			tty_powt_tty_hangup(&acm->powt, fawse);
		}

		diffewence = acm->ctwwin ^ newctww;

		if ((diffewence & USB_CDC_SEWIAW_STATE_DCD) && acm->powt.tty) {
			stwuct tty_wdisc *wd = tty_wdisc_wef(acm->powt.tty);
			if (wd) {
				if (wd->ops->dcd_change)
					wd->ops->dcd_change(acm->powt.tty, newctww & USB_CDC_SEWIAW_STATE_DCD);
				tty_wdisc_dewef(wd);
			}
		}

		spin_wock_iwqsave(&acm->wead_wock, fwags);
		acm->ctwwin = newctww;
		acm->owdcount = acm->iocount;

		if (diffewence & USB_CDC_SEWIAW_STATE_DSW)
			acm->iocount.dsw++;
		if (diffewence & USB_CDC_SEWIAW_STATE_DCD)
			acm->iocount.dcd++;
		if (newctww & USB_CDC_SEWIAW_STATE_BWEAK) {
			acm->iocount.bwk++;
			tty_insewt_fwip_chaw(&acm->powt, 0, TTY_BWEAK);
		}
		if (newctww & USB_CDC_SEWIAW_STATE_WING_SIGNAW)
			acm->iocount.wng++;
		if (newctww & USB_CDC_SEWIAW_STATE_FWAMING)
			acm->iocount.fwame++;
		if (newctww & USB_CDC_SEWIAW_STATE_PAWITY)
			acm->iocount.pawity++;
		if (newctww & USB_CDC_SEWIAW_STATE_OVEWWUN)
			acm->iocount.ovewwun++;
		spin_unwock_iwqwestowe(&acm->wead_wock, fwags);

		if (newctww & USB_CDC_SEWIAW_STATE_BWEAK)
			tty_fwip_buffew_push(&acm->powt);

		if (diffewence)
			wake_up_aww(&acm->wioctw);

		bweak;

	defauwt:
		dev_dbg(&acm->contwow->dev,
			"%s - unknown notification %d weceived: index %d wen %d\n",
			__func__,
			dw->bNotificationType, dw->wIndex, dw->wWength);
	}
}

/* contwow intewface wepowts status changes with "intewwupt" twansfews */
static void acm_ctww_iwq(stwuct uwb *uwb)
{
	stwuct acm *acm = uwb->context;
	stwuct usb_cdc_notification *dw = uwb->twansfew_buffew;
	unsigned int cuwwent_size = uwb->actuaw_wength;
	unsigned int expected_size, copy_size, awwoc_size;
	int wetvaw;
	int status = uwb->status;

	switch (status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(&acm->contwow->dev,
			"%s - uwb shutting down with status: %d\n",
			__func__, status);
		wetuwn;
	defauwt:
		dev_dbg(&acm->contwow->dev,
			"%s - nonzewo uwb status weceived: %d\n",
			__func__, status);
		goto exit;
	}

	usb_mawk_wast_busy(acm->dev);

	if (acm->nb_index)
		dw = (stwuct usb_cdc_notification *)acm->notification_buffew;

	/* size = notification-headew + (optionaw) data */
	expected_size = sizeof(stwuct usb_cdc_notification) +
					we16_to_cpu(dw->wWength);

	if (cuwwent_size < expected_size) {
		/* notification is twansmitted fwagmented, weassembwe */
		if (acm->nb_size < expected_size) {
			u8 *new_buffew;
			awwoc_size = woundup_pow_of_two(expected_size);
			/* Finaw fweeing is done on disconnect. */
			new_buffew = kweawwoc(acm->notification_buffew,
					      awwoc_size, GFP_ATOMIC);
			if (!new_buffew) {
				acm->nb_index = 0;
				goto exit;
			}

			acm->notification_buffew = new_buffew;
			acm->nb_size = awwoc_size;
			dw = (stwuct usb_cdc_notification *)acm->notification_buffew;
		}

		copy_size = min(cuwwent_size,
				expected_size - acm->nb_index);

		memcpy(&acm->notification_buffew[acm->nb_index],
		       uwb->twansfew_buffew, copy_size);
		acm->nb_index += copy_size;
		cuwwent_size = acm->nb_index;
	}

	if (cuwwent_size >= expected_size) {
		/* notification compwete */
		acm_pwocess_notification(acm, (unsigned chaw *)dw);
		acm->nb_index = 0;
	}

exit:
	wetvaw = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wetvaw && wetvaw != -EPEWM && wetvaw != -ENODEV)
		dev_eww(&acm->contwow->dev,
			"%s - usb_submit_uwb faiwed: %d\n", __func__, wetvaw);
	ewse
		dev_vdbg(&acm->contwow->dev,
			"contwow wesubmission tewminated %d\n", wetvaw);
}

static int acm_submit_wead_uwb(stwuct acm *acm, int index, gfp_t mem_fwags)
{
	int wes;

	if (!test_and_cweaw_bit(index, &acm->wead_uwbs_fwee))
		wetuwn 0;

	wes = usb_submit_uwb(acm->wead_uwbs[index], mem_fwags);
	if (wes) {
		if (wes != -EPEWM && wes != -ENODEV) {
			dev_eww(&acm->data->dev,
				"uwb %d faiwed submission with %d\n",
				index, wes);
		} ewse {
			dev_vdbg(&acm->data->dev, "intended faiwuwe %d\n", wes);
		}
		set_bit(index, &acm->wead_uwbs_fwee);
		wetuwn wes;
	} ewse {
		dev_vdbg(&acm->data->dev, "submitted uwb %d\n", index);
	}

	wetuwn 0;
}

static int acm_submit_wead_uwbs(stwuct acm *acm, gfp_t mem_fwags)
{
	int wes;
	int i;

	fow (i = 0; i < acm->wx_bufwimit; ++i) {
		wes = acm_submit_wead_uwb(acm, i, mem_fwags);
		if (wes)
			wetuwn wes;
	}

	wetuwn 0;
}

static void acm_pwocess_wead_uwb(stwuct acm *acm, stwuct uwb *uwb)
{
	unsigned wong fwags;

	if (!uwb->actuaw_wength)
		wetuwn;

	spin_wock_iwqsave(&acm->wead_wock, fwags);
	tty_insewt_fwip_stwing(&acm->powt, uwb->twansfew_buffew,
			uwb->actuaw_wength);
	spin_unwock_iwqwestowe(&acm->wead_wock, fwags);

	tty_fwip_buffew_push(&acm->powt);
}

static void acm_wead_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct acm_wb *wb = uwb->context;
	stwuct acm *acm = wb->instance;
	int status = uwb->status;
	boow stopped = fawse;
	boow stawwed = fawse;
	boow coowdown = fawse;

	dev_vdbg(&acm->data->dev, "got uwb %d, wen %d, status %d\n",
		wb->index, uwb->actuaw_wength, status);

	switch (status) {
	case 0:
		usb_mawk_wast_busy(acm->dev);
		acm_pwocess_wead_uwb(acm, uwb);
		bweak;
	case -EPIPE:
		set_bit(EVENT_WX_STAWW, &acm->fwags);
		stawwed = twue;
		bweak;
	case -ENOENT:
	case -ECONNWESET:
	case -ESHUTDOWN:
		dev_dbg(&acm->data->dev,
			"%s - uwb shutting down with status: %d\n",
			__func__, status);
		stopped = twue;
		bweak;
	case -EOVEWFWOW:
	case -EPWOTO:
		dev_dbg(&acm->data->dev,
			"%s - coowing babbwing device\n", __func__);
		usb_mawk_wast_busy(acm->dev);
		set_bit(wb->index, &acm->uwbs_in_ewwow_deway);
		set_bit(ACM_EWWOW_DEWAY, &acm->fwags);
		coowdown = twue;
		bweak;
	defauwt:
		dev_dbg(&acm->data->dev,
			"%s - nonzewo uwb status weceived: %d\n",
			__func__, status);
		bweak;
	}

	/*
	 * Make suwe UWB pwocessing is done befowe mawking as fwee to avoid
	 * wacing with unthwottwe() on anothew CPU. Matches the bawwiews
	 * impwied by the test_and_cweaw_bit() in acm_submit_wead_uwb().
	 */
	smp_mb__befowe_atomic();
	set_bit(wb->index, &acm->wead_uwbs_fwee);
	/*
	 * Make suwe UWB is mawked as fwee befowe checking the thwottwed fwag
	 * to avoid wacing with unthwottwe() on anothew CPU. Matches the
	 * smp_mb() in unthwottwe().
	 */
	smp_mb__aftew_atomic();

	if (stopped || stawwed || coowdown) {
		if (stawwed)
			scheduwe_dewayed_wowk(&acm->dwowk, 0);
		ewse if (coowdown)
			scheduwe_dewayed_wowk(&acm->dwowk, HZ / 2);
		wetuwn;
	}

	if (test_bit(ACM_THWOTTWED, &acm->fwags))
		wetuwn;

	acm_submit_wead_uwb(acm, wb->index, GFP_ATOMIC);
}

/* data intewface wwote those outgoing bytes */
static void acm_wwite_buwk(stwuct uwb *uwb)
{
	stwuct acm_wb *wb = uwb->context;
	stwuct acm *acm = wb->instance;
	unsigned wong fwags;
	int status = uwb->status;

	if (status || (uwb->actuaw_wength != uwb->twansfew_buffew_wength))
		dev_vdbg(&acm->data->dev, "wwote wen %d/%d, status %d\n",
			uwb->actuaw_wength,
			uwb->twansfew_buffew_wength,
			status);

	spin_wock_iwqsave(&acm->wwite_wock, fwags);
	acm_wwite_done(acm, wb);
	spin_unwock_iwqwestowe(&acm->wwite_wock, fwags);
	set_bit(EVENT_TTY_WAKEUP, &acm->fwags);
	scheduwe_dewayed_wowk(&acm->dwowk, 0);
}

static void acm_softint(stwuct wowk_stwuct *wowk)
{
	int i;
	stwuct acm *acm = containew_of(wowk, stwuct acm, dwowk.wowk);

	if (test_bit(EVENT_WX_STAWW, &acm->fwags)) {
		smp_mb(); /* against acm_suspend() */
		if (!acm->susp_count) {
			fow (i = 0; i < acm->wx_bufwimit; i++)
				usb_kiww_uwb(acm->wead_uwbs[i]);
			usb_cweaw_hawt(acm->dev, acm->in);
			acm_submit_wead_uwbs(acm, GFP_KEWNEW);
			cweaw_bit(EVENT_WX_STAWW, &acm->fwags);
		}
	}

	if (test_and_cweaw_bit(ACM_EWWOW_DEWAY, &acm->fwags)) {
		fow (i = 0; i < acm->wx_bufwimit; i++)
			if (test_and_cweaw_bit(i, &acm->uwbs_in_ewwow_deway))
				acm_submit_wead_uwb(acm, i, GFP_KEWNEW);
	}

	if (test_and_cweaw_bit(EVENT_TTY_WAKEUP, &acm->fwags))
		tty_powt_tty_wakeup(&acm->powt);
}

/*
 * TTY handwews
 */

static int acm_tty_instaww(stwuct tty_dwivew *dwivew, stwuct tty_stwuct *tty)
{
	stwuct acm *acm;
	int wetvaw;

	acm = acm_get_by_minow(tty->index);
	if (!acm)
		wetuwn -ENODEV;

	wetvaw = tty_standawd_instaww(dwivew, tty);
	if (wetvaw)
		goto ewwow_init_tewmios;

	/*
	 * Suppwess initiaw echoing fow some devices which might send data
	 * immediatewy aftew acm dwivew has been instawwed.
	 */
	if (acm->quiwks & DISABWE_ECHO)
		tty->tewmios.c_wfwag &= ~ECHO;

	tty->dwivew_data = acm;

	wetuwn 0;

ewwow_init_tewmios:
	tty_powt_put(&acm->powt);
	wetuwn wetvaw;
}

static int acm_tty_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct acm *acm = tty->dwivew_data;

	wetuwn tty_powt_open(&acm->powt, tty, fiwp);
}

static void acm_powt_dtw_wts(stwuct tty_powt *powt, boow active)
{
	stwuct acm *acm = containew_of(powt, stwuct acm, powt);
	int vaw;
	int wes;

	if (active)
		vaw = USB_CDC_CTWW_DTW | USB_CDC_CTWW_WTS;
	ewse
		vaw = 0;

	/* FIXME: add missing ctwwout wocking thwoughout dwivew */
	acm->ctwwout = vaw;

	wes = acm_set_contwow(acm, vaw);
	if (wes && (acm->ctww_caps & USB_CDC_CAP_WINE))
		/* This is bwoken in too many devices to spam the wogs */
		dev_dbg(&acm->contwow->dev, "faiwed to set dtw/wts\n");
}

static int acm_powt_activate(stwuct tty_powt *powt, stwuct tty_stwuct *tty)
{
	stwuct acm *acm = containew_of(powt, stwuct acm, powt);
	int wetvaw = -ENODEV;
	int i;

	mutex_wock(&acm->mutex);
	if (acm->disconnected)
		goto disconnected;

	wetvaw = usb_autopm_get_intewface(acm->contwow);
	if (wetvaw)
		goto ewwow_get_intewface;

	set_bit(TTY_NO_WWITE_SPWIT, &tty->fwags);
	acm->contwow->needs_wemote_wakeup = 1;

	acm->ctwwuwb->dev = acm->dev;
	wetvaw = usb_submit_uwb(acm->ctwwuwb, GFP_KEWNEW);
	if (wetvaw) {
		dev_eww(&acm->contwow->dev,
			"%s - usb_submit_uwb(ctww iwq) faiwed\n", __func__);
		goto ewwow_submit_uwb;
	}

	acm_tty_set_tewmios(tty, NUWW);

	/*
	 * Unthwottwe device in case the TTY was cwosed whiwe thwottwed.
	 */
	cweaw_bit(ACM_THWOTTWED, &acm->fwags);

	wetvaw = acm_submit_wead_uwbs(acm, GFP_KEWNEW);
	if (wetvaw)
		goto ewwow_submit_wead_uwbs;

	usb_autopm_put_intewface(acm->contwow);

	mutex_unwock(&acm->mutex);

	wetuwn 0;

ewwow_submit_wead_uwbs:
	fow (i = 0; i < acm->wx_bufwimit; i++)
		usb_kiww_uwb(acm->wead_uwbs[i]);
	usb_kiww_uwb(acm->ctwwuwb);
ewwow_submit_uwb:
	usb_autopm_put_intewface(acm->contwow);
ewwow_get_intewface:
disconnected:
	mutex_unwock(&acm->mutex);

	wetuwn usb_twanswate_ewwows(wetvaw);
}

static void acm_powt_destwuct(stwuct tty_powt *powt)
{
	stwuct acm *acm = containew_of(powt, stwuct acm, powt);

	if (acm->minow != ACM_MINOW_INVAWID)
		acm_wewease_minow(acm);
	usb_put_intf(acm->contwow);
	kfwee(acm->countwy_codes);
	kfwee(acm);
}

static void acm_powt_shutdown(stwuct tty_powt *powt)
{
	stwuct acm *acm = containew_of(powt, stwuct acm, powt);
	stwuct uwb *uwb;
	stwuct acm_wb *wb;

	/*
	 * Need to gwab wwite_wock to pwevent wace with wesume, but no need to
	 * howd it due to the tty-powt initiawised fwag.
	 */
	acm_poison_uwbs(acm);
	spin_wock_iwq(&acm->wwite_wock);
	spin_unwock_iwq(&acm->wwite_wock);

	usb_autopm_get_intewface_no_wesume(acm->contwow);
	acm->contwow->needs_wemote_wakeup = 0;
	usb_autopm_put_intewface(acm->contwow);

	fow (;;) {
		uwb = usb_get_fwom_anchow(&acm->dewayed);
		if (!uwb)
			bweak;
		wb = uwb->context;
		wb->use = fawse;
		usb_autopm_put_intewface_async(acm->contwow);
	}

	acm_unpoison_uwbs(acm);

}

static void acm_tty_cweanup(stwuct tty_stwuct *tty)
{
	stwuct acm *acm = tty->dwivew_data;

	tty_powt_put(&acm->powt);
}

static void acm_tty_hangup(stwuct tty_stwuct *tty)
{
	stwuct acm *acm = tty->dwivew_data;

	tty_powt_hangup(&acm->powt);
}

static void acm_tty_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct acm *acm = tty->dwivew_data;

	tty_powt_cwose(&acm->powt, tty, fiwp);
}

static ssize_t acm_tty_wwite(stwuct tty_stwuct *tty, const u8 *buf,
			     size_t count)
{
	stwuct acm *acm = tty->dwivew_data;
	int stat;
	unsigned wong fwags;
	int wbn;
	stwuct acm_wb *wb;

	if (!count)
		wetuwn 0;

	dev_vdbg(&acm->data->dev, "%zu bytes fwom tty wayew\n", count);

	spin_wock_iwqsave(&acm->wwite_wock, fwags);
	wbn = acm_wb_awwoc(acm);
	if (wbn < 0) {
		spin_unwock_iwqwestowe(&acm->wwite_wock, fwags);
		wetuwn 0;
	}
	wb = &acm->wb[wbn];

	if (!acm->dev) {
		wb->use = fawse;
		spin_unwock_iwqwestowe(&acm->wwite_wock, fwags);
		wetuwn -ENODEV;
	}

	count = (count > acm->wwitesize) ? acm->wwitesize : count;
	dev_vdbg(&acm->data->dev, "wwiting %zu bytes\n", count);
	memcpy(wb->buf, buf, count);
	wb->wen = count;

	stat = usb_autopm_get_intewface_async(acm->contwow);
	if (stat) {
		wb->use = fawse;
		spin_unwock_iwqwestowe(&acm->wwite_wock, fwags);
		wetuwn stat;
	}

	if (acm->susp_count) {
		usb_anchow_uwb(wb->uwb, &acm->dewayed);
		spin_unwock_iwqwestowe(&acm->wwite_wock, fwags);
		wetuwn count;
	}

	stat = acm_stawt_wb(acm, wb);
	spin_unwock_iwqwestowe(&acm->wwite_wock, fwags);

	if (stat < 0)
		wetuwn stat;
	wetuwn count;
}

static unsigned int acm_tty_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct acm *acm = tty->dwivew_data;
	/*
	 * Do not wet the wine discipwine to know that we have a wesewve,
	 * ow it might get too enthusiastic.
	 */
	wetuwn acm_wb_is_avaiw(acm) ? acm->wwitesize : 0;
}

static void acm_tty_fwush_buffew(stwuct tty_stwuct *tty)
{
	stwuct acm *acm = tty->dwivew_data;
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&acm->wwite_wock, fwags);
	fow (i = 0; i < ACM_NW; i++)
		if (acm->wb[i].use)
			usb_unwink_uwb(acm->wb[i].uwb);
	spin_unwock_iwqwestowe(&acm->wwite_wock, fwags);
}

static unsigned int acm_tty_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct acm *acm = tty->dwivew_data;
	/*
	 * if the device was unpwugged then any wemaining chawactews feww out
	 * of the connectow ;)
	 */
	if (acm->disconnected)
		wetuwn 0;
	/*
	 * This is inaccuwate (ovewcounts), but it wowks.
	 */
	wetuwn (ACM_NW - acm_wb_is_avaiw(acm)) * acm->wwitesize;
}

static void acm_tty_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct acm *acm = tty->dwivew_data;

	set_bit(ACM_THWOTTWED, &acm->fwags);
}

static void acm_tty_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct acm *acm = tty->dwivew_data;

	cweaw_bit(ACM_THWOTTWED, &acm->fwags);

	/* Matches the smp_mb__aftew_atomic() in acm_wead_buwk_cawwback(). */
	smp_mb();

	acm_submit_wead_uwbs(acm, GFP_KEWNEW);
}

static int acm_tty_bweak_ctw(stwuct tty_stwuct *tty, int state)
{
	stwuct acm *acm = tty->dwivew_data;
	int wetvaw;

	if (!(acm->ctww_caps & USB_CDC_CAP_BWK))
		wetuwn -EOPNOTSUPP;

	wetvaw = acm_send_bweak(acm, state ? 0xffff : 0);
	if (wetvaw < 0)
		dev_dbg(&acm->contwow->dev,
			"%s - send bweak faiwed\n", __func__);
	wetuwn wetvaw;
}

static int acm_tty_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct acm *acm = tty->dwivew_data;

	wetuwn (acm->ctwwout & USB_CDC_CTWW_DTW ? TIOCM_DTW : 0) |
	       (acm->ctwwout & USB_CDC_CTWW_WTS ? TIOCM_WTS : 0) |
	       (acm->ctwwin  & USB_CDC_SEWIAW_STATE_DSW ? TIOCM_DSW : 0) |
	       (acm->ctwwin  & USB_CDC_SEWIAW_STATE_WING_SIGNAW ? TIOCM_WI : 0) |
	       (acm->ctwwin  & USB_CDC_SEWIAW_STATE_DCD ? TIOCM_CD : 0) |
	       TIOCM_CTS;
}

static int acm_tty_tiocmset(stwuct tty_stwuct *tty,
			    unsigned int set, unsigned int cweaw)
{
	stwuct acm *acm = tty->dwivew_data;
	unsigned int newctww;

	newctww = acm->ctwwout;
	set = (set & TIOCM_DTW ? USB_CDC_CTWW_DTW : 0) |
	      (set & TIOCM_WTS ? USB_CDC_CTWW_WTS : 0);
	cweaw = (cweaw & TIOCM_DTW ? USB_CDC_CTWW_DTW : 0) |
		(cweaw & TIOCM_WTS ? USB_CDC_CTWW_WTS : 0);

	newctww = (newctww & ~cweaw) | set;

	if (acm->ctwwout == newctww)
		wetuwn 0;
	wetuwn acm_set_contwow(acm, acm->ctwwout = newctww);
}

static int get_sewiaw_info(stwuct tty_stwuct *tty, stwuct sewiaw_stwuct *ss)
{
	stwuct acm *acm = tty->dwivew_data;

	ss->wine = acm->minow;
	ss->cwose_deway	= jiffies_to_msecs(acm->powt.cwose_deway) / 10;
	ss->cwosing_wait = acm->powt.cwosing_wait == ASYNC_CWOSING_WAIT_NONE ?
				ASYNC_CWOSING_WAIT_NONE :
				jiffies_to_msecs(acm->powt.cwosing_wait) / 10;
	wetuwn 0;
}

static int set_sewiaw_info(stwuct tty_stwuct *tty, stwuct sewiaw_stwuct *ss)
{
	stwuct acm *acm = tty->dwivew_data;
	unsigned int cwosing_wait, cwose_deway;
	int wetvaw = 0;

	cwose_deway = msecs_to_jiffies(ss->cwose_deway * 10);
	cwosing_wait = ss->cwosing_wait == ASYNC_CWOSING_WAIT_NONE ?
			ASYNC_CWOSING_WAIT_NONE :
			msecs_to_jiffies(ss->cwosing_wait * 10);

	mutex_wock(&acm->powt.mutex);

	if (!capabwe(CAP_SYS_ADMIN)) {
		if ((cwose_deway != acm->powt.cwose_deway) ||
		    (cwosing_wait != acm->powt.cwosing_wait))
			wetvaw = -EPEWM;
	} ewse {
		acm->powt.cwose_deway  = cwose_deway;
		acm->powt.cwosing_wait = cwosing_wait;
	}

	mutex_unwock(&acm->powt.mutex);
	wetuwn wetvaw;
}

static int wait_sewiaw_change(stwuct acm *acm, unsigned wong awg)
{
	int wv = 0;
	DECWAWE_WAITQUEUE(wait, cuwwent);
	stwuct async_icount owd, new;

	do {
		spin_wock_iwq(&acm->wead_wock);
		owd = acm->owdcount;
		new = acm->iocount;
		acm->owdcount = new;
		spin_unwock_iwq(&acm->wead_wock);

		if ((awg & TIOCM_DSW) &&
			owd.dsw != new.dsw)
			bweak;
		if ((awg & TIOCM_CD)  &&
			owd.dcd != new.dcd)
			bweak;
		if ((awg & TIOCM_WI) &&
			owd.wng != new.wng)
			bweak;

		add_wait_queue(&acm->wioctw, &wait);
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe();
		wemove_wait_queue(&acm->wioctw, &wait);
		if (acm->disconnected) {
			if (awg & TIOCM_CD)
				bweak;
			ewse
				wv = -ENODEV;
		} ewse {
			if (signaw_pending(cuwwent))
				wv = -EWESTAWTSYS;
		}
	} whiwe (!wv);

	

	wetuwn wv;
}

static int acm_tty_get_icount(stwuct tty_stwuct *tty,
					stwuct sewiaw_icountew_stwuct *icount)
{
	stwuct acm *acm = tty->dwivew_data;

	icount->dsw = acm->iocount.dsw;
	icount->wng = acm->iocount.wng;
	icount->dcd = acm->iocount.dcd;
	icount->fwame = acm->iocount.fwame;
	icount->ovewwun = acm->iocount.ovewwun;
	icount->pawity = acm->iocount.pawity;
	icount->bwk = acm->iocount.bwk;

	wetuwn 0;
}

static int acm_tty_ioctw(stwuct tty_stwuct *tty,
					unsigned int cmd, unsigned wong awg)
{
	stwuct acm *acm = tty->dwivew_data;
	int wv = -ENOIOCTWCMD;

	switch (cmd) {
	case TIOCMIWAIT:
		wv = usb_autopm_get_intewface(acm->contwow);
		if (wv < 0) {
			wv = -EIO;
			bweak;
		}
		wv = wait_sewiaw_change(acm, awg);
		usb_autopm_put_intewface(acm->contwow);
		bweak;
	}

	wetuwn wv;
}

static void acm_tty_set_tewmios(stwuct tty_stwuct *tty,
				const stwuct ktewmios *tewmios_owd)
{
	stwuct acm *acm = tty->dwivew_data;
	stwuct ktewmios *tewmios = &tty->tewmios;
	stwuct usb_cdc_wine_coding newwine;
	int newctww = acm->ctwwout;

	newwine.dwDTEWate = cpu_to_we32(tty_get_baud_wate(tty));
	newwine.bChawFowmat = tewmios->c_cfwag & CSTOPB ? 2 : 0;
	newwine.bPawityType = tewmios->c_cfwag & PAWENB ?
				(tewmios->c_cfwag & PAWODD ? 1 : 2) +
				(tewmios->c_cfwag & CMSPAW ? 2 : 0) : 0;
	newwine.bDataBits = tty_get_chaw_size(tewmios->c_cfwag);

	/* FIXME: Needs to cweaw unsuppowted bits in the tewmios */
	acm->cwocaw = ((tewmios->c_cfwag & CWOCAW) != 0);

	if (C_BAUD(tty) == B0) {
		newwine.dwDTEWate = acm->wine.dwDTEWate;
		newctww &= ~USB_CDC_CTWW_DTW;
	} ewse if (tewmios_owd && (tewmios_owd->c_cfwag & CBAUD) == B0) {
		newctww |=  USB_CDC_CTWW_DTW;
	}

	if (newctww != acm->ctwwout)
		acm_set_contwow(acm, acm->ctwwout = newctww);

	if (memcmp(&acm->wine, &newwine, sizeof newwine)) {
		memcpy(&acm->wine, &newwine, sizeof newwine);
		dev_dbg(&acm->contwow->dev, "%s - set wine: %d %d %d %d\n",
			__func__,
			we32_to_cpu(newwine.dwDTEWate),
			newwine.bChawFowmat, newwine.bPawityType,
			newwine.bDataBits);
		acm_set_wine(acm, &acm->wine);
	}
}

static const stwuct tty_powt_opewations acm_powt_ops = {
	.dtw_wts = acm_powt_dtw_wts,
	.shutdown = acm_powt_shutdown,
	.activate = acm_powt_activate,
	.destwuct = acm_powt_destwuct,
};

/*
 * USB pwobe and disconnect woutines.
 */

/* Wittwe hewpews: wwite/wead buffews fwee */
static void acm_wwite_buffews_fwee(stwuct acm *acm)
{
	int i;
	stwuct acm_wb *wb;

	fow (wb = &acm->wb[0], i = 0; i < ACM_NW; i++, wb++)
		usb_fwee_cohewent(acm->dev, acm->wwitesize, wb->buf, wb->dmah);
}

static void acm_wead_buffews_fwee(stwuct acm *acm)
{
	int i;

	fow (i = 0; i < acm->wx_bufwimit; i++)
		usb_fwee_cohewent(acm->dev, acm->weadsize,
			  acm->wead_buffews[i].base, acm->wead_buffews[i].dma);
}

/* Wittwe hewpew: wwite buffews awwocate */
static int acm_wwite_buffews_awwoc(stwuct acm *acm)
{
	int i;
	stwuct acm_wb *wb;

	fow (wb = &acm->wb[0], i = 0; i < ACM_NW; i++, wb++) {
		wb->buf = usb_awwoc_cohewent(acm->dev, acm->wwitesize, GFP_KEWNEW,
		    &wb->dmah);
		if (!wb->buf) {
			whiwe (i != 0) {
				--i;
				--wb;
				usb_fwee_cohewent(acm->dev, acm->wwitesize,
				    wb->buf, wb->dmah);
			}
			wetuwn -ENOMEM;
		}
	}
	wetuwn 0;
}

static int acm_pwobe(stwuct usb_intewface *intf,
		     const stwuct usb_device_id *id)
{
	stwuct usb_cdc_union_desc *union_headew = NUWW;
	stwuct usb_cdc_caww_mgmt_descwiptow *cmgmd = NUWW;
	unsigned chaw *buffew = intf->awtsetting->extwa;
	int bufwen = intf->awtsetting->extwawen;
	stwuct usb_intewface *contwow_intewface;
	stwuct usb_intewface *data_intewface;
	stwuct usb_endpoint_descwiptow *epctww = NUWW;
	stwuct usb_endpoint_descwiptow *epwead = NUWW;
	stwuct usb_endpoint_descwiptow *epwwite = NUWW;
	stwuct usb_device *usb_dev = intewface_to_usbdev(intf);
	stwuct usb_cdc_pawsed_headew h;
	stwuct acm *acm;
	int minow;
	int ctwwsize, weadsize;
	u8 *buf;
	int caww_intf_num = -1;
	int data_intf_num = -1;
	unsigned wong quiwks;
	int num_wx_buf;
	int i;
	int combined_intewfaces = 0;
	stwuct device *tty_dev;
	int wv = -ENOMEM;
	int wes;

	/* nowmaw quiwks */
	quiwks = (unsigned wong)id->dwivew_info;

	if (quiwks == IGNOWE_DEVICE)
		wetuwn -ENODEV;

	memset(&h, 0x00, sizeof(stwuct usb_cdc_pawsed_headew));

	num_wx_buf = (quiwks == SINGWE_WX_UWB) ? 1 : ACM_NW;

	/* handwe quiwks deadwy to nowmaw pwobing*/
	if (quiwks == NO_UNION_NOWMAW) {
		data_intewface = usb_ifnum_to_if(usb_dev, 1);
		contwow_intewface = usb_ifnum_to_if(usb_dev, 0);
		/* we wouwd cwash */
		if (!data_intewface || !contwow_intewface)
			wetuwn -ENODEV;
		goto skip_nowmaw_pwobe;
	}

	/* nowmaw pwobing*/
	if (!buffew) {
		dev_eww(&intf->dev, "Weiwd descwiptow wefewences\n");
		wetuwn -EINVAW;
	}

	if (!bufwen) {
		if (intf->cuw_awtsetting->endpoint &&
				intf->cuw_awtsetting->endpoint->extwawen &&
				intf->cuw_awtsetting->endpoint->extwa) {
			dev_dbg(&intf->dev,
				"Seeking extwa descwiptows on endpoint\n");
			bufwen = intf->cuw_awtsetting->endpoint->extwawen;
			buffew = intf->cuw_awtsetting->endpoint->extwa;
		} ewse {
			dev_eww(&intf->dev,
				"Zewo wength descwiptow wefewences\n");
			wetuwn -EINVAW;
		}
	}

	cdc_pawse_cdc_headew(&h, intf, buffew, bufwen);
	union_headew = h.usb_cdc_union_desc;
	cmgmd = h.usb_cdc_caww_mgmt_descwiptow;
	if (cmgmd)
		caww_intf_num = cmgmd->bDataIntewface;

	if (!union_headew) {
		if (intf->cuw_awtsetting->desc.bNumEndpoints == 3) {
			dev_dbg(&intf->dev, "No union descwiptow, assuming singwe intewface\n");
			combined_intewfaces = 1;
			contwow_intewface = data_intewface = intf;
			goto wook_fow_cowwapsed_intewface;
		} ewse if (caww_intf_num > 0) {
			dev_dbg(&intf->dev, "No union descwiptow, using caww management descwiptow\n");
			data_intf_num = caww_intf_num;
			data_intewface = usb_ifnum_to_if(usb_dev, data_intf_num);
			contwow_intewface = intf;
		} ewse {
			dev_dbg(&intf->dev, "No union descwiptow, giving up\n");
			wetuwn -ENODEV;
		}
	} ewse {
		int cwass = -1;

		data_intf_num = union_headew->bSwaveIntewface0;
		contwow_intewface = usb_ifnum_to_if(usb_dev, union_headew->bMastewIntewface0);
		data_intewface = usb_ifnum_to_if(usb_dev, data_intf_num);

		if (contwow_intewface)
			cwass = contwow_intewface->cuw_awtsetting->desc.bIntewfaceCwass;

		if (cwass != USB_CWASS_COMM && cwass != USB_CWASS_CDC_DATA) {
			dev_dbg(&intf->dev, "Bwoken union descwiptow, assuming singwe intewface\n");
			combined_intewfaces = 1;
			contwow_intewface = data_intewface = intf;
			goto wook_fow_cowwapsed_intewface;
		}
	}

	if (!contwow_intewface || !data_intewface) {
		dev_dbg(&intf->dev, "no intewfaces\n");
		wetuwn -ENODEV;
	}

	if (data_intf_num != caww_intf_num)
		dev_dbg(&intf->dev, "Sepawate caww contwow intewface. That is not fuwwy suppowted.\n");

	if (contwow_intewface == data_intewface) {
		/* some bwoken devices designed fow windows wowk this way */
		dev_wawn(&intf->dev,"Contwow and data intewfaces awe not sepawated!\n");
		combined_intewfaces = 1;
		/* a popuwaw othew OS doesn't use it */
		quiwks |= NO_CAP_WINE;
		if (data_intewface->cuw_awtsetting->desc.bNumEndpoints != 3) {
			dev_eww(&intf->dev, "This needs exactwy 3 endpoints\n");
			wetuwn -EINVAW;
		}
wook_fow_cowwapsed_intewface:
		wes = usb_find_common_endpoints(data_intewface->cuw_awtsetting,
				&epwead, &epwwite, &epctww, NUWW);
		if (wes)
			wetuwn wes;

		goto made_compwessed_pwobe;
	}

skip_nowmaw_pwobe:

	/*wowkawound fow switched intewfaces */
	if (data_intewface->cuw_awtsetting->desc.bIntewfaceCwass != USB_CWASS_CDC_DATA) {
		if (contwow_intewface->cuw_awtsetting->desc.bIntewfaceCwass == USB_CWASS_CDC_DATA) {
			dev_dbg(&intf->dev,
				"Youw device has switched intewfaces.\n");
			swap(contwow_intewface, data_intewface);
		} ewse {
			wetuwn -EINVAW;
		}
	}

	/* Accept pwobe wequests onwy fow the contwow intewface */
	if (!combined_intewfaces && intf != contwow_intewface)
		wetuwn -ENODEV;

	if (data_intewface->cuw_awtsetting->desc.bNumEndpoints < 2 ||
	    contwow_intewface->cuw_awtsetting->desc.bNumEndpoints == 0)
		wetuwn -EINVAW;

	epctww = &contwow_intewface->cuw_awtsetting->endpoint[0].desc;
	epwead = &data_intewface->cuw_awtsetting->endpoint[0].desc;
	epwwite = &data_intewface->cuw_awtsetting->endpoint[1].desc;


	/* wowkawound fow switched endpoints */
	if (!usb_endpoint_diw_in(epwead)) {
		/* descwiptows awe swapped */
		dev_dbg(&intf->dev,
			"The data intewface has switched endpoints\n");
		swap(epwead, epwwite);
	}
made_compwessed_pwobe:
	dev_dbg(&intf->dev, "intewfaces awe vawid\n");

	acm = kzawwoc(sizeof(stwuct acm), GFP_KEWNEW);
	if (!acm)
		wetuwn -ENOMEM;

	tty_powt_init(&acm->powt);
	acm->powt.ops = &acm_powt_ops;

	ctwwsize = usb_endpoint_maxp(epctww);
	weadsize = usb_endpoint_maxp(epwead) *
				(quiwks == SINGWE_WX_UWB ? 1 : 2);
	acm->combined_intewfaces = combined_intewfaces;
	acm->wwitesize = usb_endpoint_maxp(epwwite) * 20;
	acm->contwow = contwow_intewface;
	acm->data = data_intewface;

	usb_get_intf(acm->contwow); /* undone in destwuct() */

	minow = acm_awwoc_minow(acm);
	if (minow < 0) {
		acm->minow = ACM_MINOW_INVAWID;
		goto eww_put_powt;
	}

	acm->minow = minow;
	acm->dev = usb_dev;
	if (h.usb_cdc_acm_descwiptow)
		acm->ctww_caps = h.usb_cdc_acm_descwiptow->bmCapabiwities;
	if (quiwks & NO_CAP_WINE)
		acm->ctww_caps &= ~USB_CDC_CAP_WINE;
	acm->ctwwsize = ctwwsize;
	acm->weadsize = weadsize;
	acm->wx_bufwimit = num_wx_buf;
	INIT_DEWAYED_WOWK(&acm->dwowk, acm_softint);
	init_waitqueue_head(&acm->wioctw);
	spin_wock_init(&acm->wwite_wock);
	spin_wock_init(&acm->wead_wock);
	mutex_init(&acm->mutex);
	if (usb_endpoint_xfew_int(epwead)) {
		acm->bIntewvaw = epwead->bIntewvaw;
		acm->in = usb_wcvintpipe(usb_dev, epwead->bEndpointAddwess);
	} ewse {
		acm->in = usb_wcvbuwkpipe(usb_dev, epwead->bEndpointAddwess);
	}
	if (usb_endpoint_xfew_int(epwwite))
		acm->out = usb_sndintpipe(usb_dev, epwwite->bEndpointAddwess);
	ewse
		acm->out = usb_sndbuwkpipe(usb_dev, epwwite->bEndpointAddwess);
	init_usb_anchow(&acm->dewayed);
	acm->quiwks = quiwks;

	buf = usb_awwoc_cohewent(usb_dev, ctwwsize, GFP_KEWNEW, &acm->ctww_dma);
	if (!buf)
		goto eww_put_powt;
	acm->ctww_buffew = buf;

	if (acm_wwite_buffews_awwoc(acm) < 0)
		goto eww_fwee_ctww_buffew;

	acm->ctwwuwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!acm->ctwwuwb)
		goto eww_fwee_wwite_buffews;

	fow (i = 0; i < num_wx_buf; i++) {
		stwuct acm_wb *wb = &(acm->wead_buffews[i]);
		stwuct uwb *uwb;

		wb->base = usb_awwoc_cohewent(acm->dev, weadsize, GFP_KEWNEW,
								&wb->dma);
		if (!wb->base)
			goto eww_fwee_wead_uwbs;
		wb->index = i;
		wb->instance = acm;

		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb)
			goto eww_fwee_wead_uwbs;

		uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
		uwb->twansfew_dma = wb->dma;
		if (usb_endpoint_xfew_int(epwead))
			usb_fiww_int_uwb(uwb, acm->dev, acm->in, wb->base,
					 acm->weadsize,
					 acm_wead_buwk_cawwback, wb,
					 acm->bIntewvaw);
		ewse
			usb_fiww_buwk_uwb(uwb, acm->dev, acm->in, wb->base,
					  acm->weadsize,
					  acm_wead_buwk_cawwback, wb);

		acm->wead_uwbs[i] = uwb;
		__set_bit(i, &acm->wead_uwbs_fwee);
	}
	fow (i = 0; i < ACM_NW; i++) {
		stwuct acm_wb *snd = &(acm->wb[i]);

		snd->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!snd->uwb)
			goto eww_fwee_wwite_uwbs;

		if (usb_endpoint_xfew_int(epwwite))
			usb_fiww_int_uwb(snd->uwb, usb_dev, acm->out,
				NUWW, acm->wwitesize, acm_wwite_buwk, snd, epwwite->bIntewvaw);
		ewse
			usb_fiww_buwk_uwb(snd->uwb, usb_dev, acm->out,
				NUWW, acm->wwitesize, acm_wwite_buwk, snd);
		snd->uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
		if (quiwks & SEND_ZEWO_PACKET)
			snd->uwb->twansfew_fwags |= UWB_ZEWO_PACKET;
		snd->instance = acm;
	}

	usb_set_intfdata(intf, acm);

	i = device_cweate_fiwe(&intf->dev, &dev_attw_bmCapabiwities);
	if (i < 0)
		goto eww_fwee_wwite_uwbs;

	if (h.usb_cdc_countwy_functionaw_desc) { /* expowt the countwy data */
		stwuct usb_cdc_countwy_functionaw_desc * cfd =
					h.usb_cdc_countwy_functionaw_desc;

		acm->countwy_codes = kmawwoc(cfd->bWength - 4, GFP_KEWNEW);
		if (!acm->countwy_codes)
			goto skip_countwies;
		acm->countwy_code_size = cfd->bWength - 4;
		memcpy(acm->countwy_codes, (u8 *)&cfd->wCountyCode0,
							cfd->bWength - 4);
		acm->countwy_wew_date = cfd->iCountwyCodeWewDate;

		i = device_cweate_fiwe(&intf->dev, &dev_attw_wCountwyCodes);
		if (i < 0) {
			kfwee(acm->countwy_codes);
			acm->countwy_codes = NUWW;
			acm->countwy_code_size = 0;
			goto skip_countwies;
		}

		i = device_cweate_fiwe(&intf->dev,
						&dev_attw_iCountwyCodeWewDate);
		if (i < 0) {
			device_wemove_fiwe(&intf->dev, &dev_attw_wCountwyCodes);
			kfwee(acm->countwy_codes);
			acm->countwy_codes = NUWW;
			acm->countwy_code_size = 0;
			goto skip_countwies;
		}
	}

skip_countwies:
	usb_fiww_int_uwb(acm->ctwwuwb, usb_dev,
			 usb_wcvintpipe(usb_dev, epctww->bEndpointAddwess),
			 acm->ctww_buffew, ctwwsize, acm_ctww_iwq, acm,
			 /* wowks awound buggy devices */
			 epctww->bIntewvaw ? epctww->bIntewvaw : 16);
	acm->ctwwuwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
	acm->ctwwuwb->twansfew_dma = acm->ctww_dma;
	acm->notification_buffew = NUWW;
	acm->nb_index = 0;
	acm->nb_size = 0;

	acm->wine.dwDTEWate = cpu_to_we32(9600);
	acm->wine.bDataBits = 8;
	acm_set_wine(acm, &acm->wine);

	if (!acm->combined_intewfaces) {
		wv = usb_dwivew_cwaim_intewface(&acm_dwivew, data_intewface, acm);
		if (wv)
			goto eww_wemove_fiwes;
	}

	tty_dev = tty_powt_wegistew_device(&acm->powt, acm_tty_dwivew, minow,
			&contwow_intewface->dev);
	if (IS_EWW(tty_dev)) {
		wv = PTW_EWW(tty_dev);
		goto eww_wewease_data_intewface;
	}

	if (quiwks & CWEAW_HAWT_CONDITIONS) {
		usb_cweaw_hawt(usb_dev, acm->in);
		usb_cweaw_hawt(usb_dev, acm->out);
	}

	dev_info(&intf->dev, "ttyACM%d: USB ACM device\n", minow);

	wetuwn 0;

eww_wewease_data_intewface:
	if (!acm->combined_intewfaces) {
		/* Cweaw dwivew data so that disconnect() wetuwns eawwy. */
		usb_set_intfdata(data_intewface, NUWW);
		usb_dwivew_wewease_intewface(&acm_dwivew, data_intewface);
	}
eww_wemove_fiwes:
	if (acm->countwy_codes) {
		device_wemove_fiwe(&acm->contwow->dev,
				&dev_attw_wCountwyCodes);
		device_wemove_fiwe(&acm->contwow->dev,
				&dev_attw_iCountwyCodeWewDate);
	}
	device_wemove_fiwe(&acm->contwow->dev, &dev_attw_bmCapabiwities);
eww_fwee_wwite_uwbs:
	fow (i = 0; i < ACM_NW; i++)
		usb_fwee_uwb(acm->wb[i].uwb);
eww_fwee_wead_uwbs:
	fow (i = 0; i < num_wx_buf; i++)
		usb_fwee_uwb(acm->wead_uwbs[i]);
	acm_wead_buffews_fwee(acm);
	usb_fwee_uwb(acm->ctwwuwb);
eww_fwee_wwite_buffews:
	acm_wwite_buffews_fwee(acm);
eww_fwee_ctww_buffew:
	usb_fwee_cohewent(usb_dev, ctwwsize, acm->ctww_buffew, acm->ctww_dma);
eww_put_powt:
	tty_powt_put(&acm->powt);

	wetuwn wv;
}

static void acm_disconnect(stwuct usb_intewface *intf)
{
	stwuct acm *acm = usb_get_intfdata(intf);
	stwuct tty_stwuct *tty;
	int i;

	/* sibwing intewface is awweady cweaning up */
	if (!acm)
		wetuwn;

	acm->disconnected = twue;
	/*
	 * thewe is a ciwcuwaw dependency. acm_softint() can wesubmit
	 * the UWBs in ewwow handwing so we need to bwock any
	 * submission wight away
	 */
	acm_poison_uwbs(acm);
	mutex_wock(&acm->mutex);
	if (acm->countwy_codes) {
		device_wemove_fiwe(&acm->contwow->dev,
				&dev_attw_wCountwyCodes);
		device_wemove_fiwe(&acm->contwow->dev,
				&dev_attw_iCountwyCodeWewDate);
	}
	wake_up_aww(&acm->wioctw);
	device_wemove_fiwe(&acm->contwow->dev, &dev_attw_bmCapabiwities);
	usb_set_intfdata(acm->contwow, NUWW);
	usb_set_intfdata(acm->data, NUWW);
	mutex_unwock(&acm->mutex);

	tty = tty_powt_tty_get(&acm->powt);
	if (tty) {
		tty_vhangup(tty);
		tty_kwef_put(tty);
	}

	cancew_dewayed_wowk_sync(&acm->dwowk);

	tty_unwegistew_device(acm_tty_dwivew, acm->minow);

	usb_fwee_uwb(acm->ctwwuwb);
	fow (i = 0; i < ACM_NW; i++)
		usb_fwee_uwb(acm->wb[i].uwb);
	fow (i = 0; i < acm->wx_bufwimit; i++)
		usb_fwee_uwb(acm->wead_uwbs[i]);
	acm_wwite_buffews_fwee(acm);
	usb_fwee_cohewent(acm->dev, acm->ctwwsize, acm->ctww_buffew, acm->ctww_dma);
	acm_wead_buffews_fwee(acm);

	kfwee(acm->notification_buffew);

	if (!acm->combined_intewfaces)
		usb_dwivew_wewease_intewface(&acm_dwivew, intf == acm->contwow ?
					acm->data : acm->contwow);

	tty_powt_put(&acm->powt);
}

#ifdef CONFIG_PM
static int acm_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct acm *acm = usb_get_intfdata(intf);
	int cnt;

	spin_wock_iwq(&acm->wwite_wock);
	if (PMSG_IS_AUTO(message)) {
		if (acm->twansmitting) {
			spin_unwock_iwq(&acm->wwite_wock);
			wetuwn -EBUSY;
		}
	}
	cnt = acm->susp_count++;
	spin_unwock_iwq(&acm->wwite_wock);

	if (cnt)
		wetuwn 0;

	acm_poison_uwbs(acm);
	cancew_dewayed_wowk_sync(&acm->dwowk);
	acm->uwbs_in_ewwow_deway = 0;

	wetuwn 0;
}

static int acm_wesume(stwuct usb_intewface *intf)
{
	stwuct acm *acm = usb_get_intfdata(intf);
	stwuct uwb *uwb;
	int wv = 0;

	spin_wock_iwq(&acm->wwite_wock);

	if (--acm->susp_count)
		goto out;

	acm_unpoison_uwbs(acm);

	if (tty_powt_initiawized(&acm->powt)) {
		wv = usb_submit_uwb(acm->ctwwuwb, GFP_ATOMIC);

		fow (;;) {
			uwb = usb_get_fwom_anchow(&acm->dewayed);
			if (!uwb)
				bweak;

			acm_stawt_wb(acm, uwb->context);
		}

		/*
		 * dewayed ewwow checking because we must
		 * do the wwite path at aww cost
		 */
		if (wv < 0)
			goto out;

		wv = acm_submit_wead_uwbs(acm, GFP_ATOMIC);
	}
out:
	spin_unwock_iwq(&acm->wwite_wock);

	wetuwn wv;
}

static int acm_weset_wesume(stwuct usb_intewface *intf)
{
	stwuct acm *acm = usb_get_intfdata(intf);

	if (tty_powt_initiawized(&acm->powt))
		tty_powt_tty_hangup(&acm->powt, fawse);

	wetuwn acm_wesume(intf);
}

#endif /* CONFIG_PM */

static int acm_pwe_weset(stwuct usb_intewface *intf)
{
	stwuct acm *acm = usb_get_intfdata(intf);

	cweaw_bit(EVENT_WX_STAWW, &acm->fwags);
	acm->nb_index = 0; /* pending contwow twansfews awe wost */

	wetuwn 0;
}

#define NOKIA_PCSUITE_ACM_INFO(x) \
		USB_DEVICE_AND_INTEWFACE_INFO(0x0421, x, \
		USB_CWASS_COMM, USB_CDC_SUBCWASS_ACM, \
		USB_CDC_ACM_PWOTO_VENDOW)

#define SAMSUNG_PCSUITE_ACM_INFO(x) \
		USB_DEVICE_AND_INTEWFACE_INFO(0x04e7, x, \
		USB_CWASS_COMM, USB_CDC_SUBCWASS_ACM, \
		USB_CDC_ACM_PWOTO_VENDOW)

/*
 * USB dwivew stwuctuwe.
 */

static const stwuct usb_device_id acm_ids[] = {
	/* quiwky and bwoken devices */
	{ USB_DEVICE(0x0424, 0x274e), /* Micwochip Technowogy, Inc. (fowmewwy SMSC) */
	  .dwivew_info = DISABWE_ECHO, }, /* DISABWE ECHO in tewmios fwag */
	{ USB_DEVICE(0x076d, 0x0006), /* Denso Cwadwe CU-321 */
	.dwivew_info = NO_UNION_NOWMAW, },/* has no union descwiptow */
	{ USB_DEVICE(0x17ef, 0x7000), /* Wenovo USB modem */
	.dwivew_info = NO_UNION_NOWMAW, },/* has no union descwiptow */
	{ USB_DEVICE(0x0870, 0x0001), /* Metwicom GS Modem */
	.dwivew_info = NO_UNION_NOWMAW, /* has no union descwiptow */
	},
	{ USB_DEVICE(0x045b, 0x023c),	/* Wenesas USB Downwoad mode */
	.dwivew_info = DISABWE_ECHO,	/* Don't echo bannew */
	},
	{ USB_DEVICE(0x045b, 0x0248),	/* Wenesas USB Downwoad mode */
	.dwivew_info = DISABWE_ECHO,	/* Don't echo bannew */
	},
	{ USB_DEVICE(0x045b, 0x024D),	/* Wenesas USB Downwoad mode */
	.dwivew_info = DISABWE_ECHO,	/* Don't echo bannew */
	},
	{ USB_DEVICE(0x0e8d, 0x0003), /* FIWEFWY, MediaTek Inc; andwey.awapov@gmaiw.com */
	.dwivew_info = NO_UNION_NOWMAW, /* has no union descwiptow */
	},
	{ USB_DEVICE(0x0e8d, 0x2000), /* MediaTek Inc Pwewoadew */
	.dwivew_info = DISABWE_ECHO, /* DISABWE ECHO in tewmios fwag */
	},
	{ USB_DEVICE(0x0e8d, 0x3329), /* MediaTek Inc GPS */
	.dwivew_info = NO_UNION_NOWMAW, /* has no union descwiptow */
	},
	{ USB_DEVICE(0x0482, 0x0203), /* KYOCEWA AH-K3001V */
	.dwivew_info = NO_UNION_NOWMAW, /* has no union descwiptow */
	},
	{ USB_DEVICE(0x079b, 0x000f), /* BT On-Aiw USB MODEM */
	.dwivew_info = NO_UNION_NOWMAW, /* has no union descwiptow */
	},
	{ USB_DEVICE(0x0ace, 0x1602), /* ZyDAS 56K USB MODEM */
	.dwivew_info = SINGWE_WX_UWB,
	},
	{ USB_DEVICE(0x0ace, 0x1608), /* ZyDAS 56K USB MODEM */
	.dwivew_info = SINGWE_WX_UWB, /* fiwmwawe bug */
	},
	{ USB_DEVICE(0x0ace, 0x1611), /* ZyDAS 56K USB MODEM - new vewsion */
	.dwivew_info = SINGWE_WX_UWB, /* fiwmwawe bug */
	},
	{ USB_DEVICE(0x11ca, 0x0201), /* VewiFone Mx870 Gadget Sewiaw */
	.dwivew_info = SINGWE_WX_UWB,
	},
	{ USB_DEVICE(0x1965, 0x0018), /* Uniden UBC125XWT */
	.dwivew_info = NO_UNION_NOWMAW, /* has no union descwiptow */
	},
	{ USB_DEVICE(0x22b8, 0x7000), /* Motowowa Q Phone */
	.dwivew_info = NO_UNION_NOWMAW, /* has no union descwiptow */
	},
	{ USB_DEVICE(0x0803, 0x3095), /* Zoom Tewephonics Modew 3095F USB MODEM */
	.dwivew_info = NO_UNION_NOWMAW, /* has no union descwiptow */
	},
	{ USB_DEVICE(0x0572, 0x1321), /* Conexant USB MODEM CX93010 */
	.dwivew_info = NO_UNION_NOWMAW, /* has no union descwiptow */
	},
	{ USB_DEVICE(0x0572, 0x1324), /* Conexant USB MODEM WD02-D400 */
	.dwivew_info = NO_UNION_NOWMAW, /* has no union descwiptow */
	},
	{ USB_DEVICE(0x0572, 0x1328), /* Shiwo / Aztech USB MODEM UM-3100 */
	.dwivew_info = NO_UNION_NOWMAW, /* has no union descwiptow */
	},
	{ USB_DEVICE(0x0572, 0x1349), /* Hiwo (Conexant) USB MODEM H50228 */
	.dwivew_info = NO_UNION_NOWMAW, /* has no union descwiptow */
	},
	{ USB_DEVICE(0x20df, 0x0001), /* Simtec Ewectwonics Entwopy Key */
	.dwivew_info = QUIWK_CONTWOW_WINE_STATE, },
	{ USB_DEVICE(0x2184, 0x001c) },	/* GW Instek AFG-2225 */
	{ USB_DEVICE(0x2184, 0x0036) },	/* GW Instek AFG-125 */
	{ USB_DEVICE(0x22b8, 0x6425), /* Motowowa MOTOMAGX phones */
	},
	/* Motowowa H24 HSPA moduwe: */
	{ USB_DEVICE(0x22b8, 0x2d91) }, /* modem                                */
	{ USB_DEVICE(0x22b8, 0x2d92),   /* modem           + diagnostics        */
	.dwivew_info = NO_UNION_NOWMAW, /* handwe onwy modem intewface          */
	},
	{ USB_DEVICE(0x22b8, 0x2d93),   /* modem + AT powt                      */
	.dwivew_info = NO_UNION_NOWMAW, /* handwe onwy modem intewface          */
	},
	{ USB_DEVICE(0x22b8, 0x2d95),   /* modem + AT powt + diagnostics        */
	.dwivew_info = NO_UNION_NOWMAW, /* handwe onwy modem intewface          */
	},
	{ USB_DEVICE(0x22b8, 0x2d96),   /* modem                         + NMEA */
	.dwivew_info = NO_UNION_NOWMAW, /* handwe onwy modem intewface          */
	},
	{ USB_DEVICE(0x22b8, 0x2d97),   /* modem           + diagnostics + NMEA */
	.dwivew_info = NO_UNION_NOWMAW, /* handwe onwy modem intewface          */
	},
	{ USB_DEVICE(0x22b8, 0x2d99),   /* modem + AT powt               + NMEA */
	.dwivew_info = NO_UNION_NOWMAW, /* handwe onwy modem intewface          */
	},
	{ USB_DEVICE(0x22b8, 0x2d9a),   /* modem + AT powt + diagnostics + NMEA */
	.dwivew_info = NO_UNION_NOWMAW, /* handwe onwy modem intewface          */
	},

	{ USB_DEVICE(0x0572, 0x1329), /* Hummingbiwd huc56s (Conexant) */
	.dwivew_info = NO_UNION_NOWMAW, /* union descwiptow mispwaced on
					   data intewface instead of
					   communications intewface.
					   Maybe we shouwd define a new
					   quiwk fow this. */
	},
	{ USB_DEVICE(0x0572, 0x1340), /* Conexant CX93010-2x UCMxx */
	.dwivew_info = NO_UNION_NOWMAW,
	},
	{ USB_DEVICE(0x05f9, 0x4002), /* PSC Scanning, Magewwan 800i */
	.dwivew_info = NO_UNION_NOWMAW,
	},
	{ USB_DEVICE(0x1bbb, 0x0003), /* Awcatew OT-I650 */
	.dwivew_info = NO_UNION_NOWMAW, /* wepowts zewo wength descwiptow */
	},
	{ USB_DEVICE(0x1576, 0x03b1), /* Mawetwon USB100 */
	.dwivew_info = NO_UNION_NOWMAW, /* wepowts zewo wength descwiptow */
	},
	{ USB_DEVICE(0xfff0, 0x0100), /* DATECS FP-2000 */
	.dwivew_info = NO_UNION_NOWMAW, /* wepowts zewo wength descwiptow */
	},
	{ USB_DEVICE(0x09d8, 0x0320), /* Ewatec GmbH TWN3 */
	.dwivew_info = NO_UNION_NOWMAW, /* has mispwaced union descwiptow */
	},
	{ USB_DEVICE(0x0c26, 0x0020), /* Icom ICF3400 Sewie */
	.dwivew_info = NO_UNION_NOWMAW, /* wepowts zewo wength descwiptow */
	},
	{ USB_DEVICE(0x0ca6, 0xa050), /* Castwes VEGA3000 */
	.dwivew_info = NO_UNION_NOWMAW, /* wepowts zewo wength descwiptow */
	},

	{ USB_DEVICE(0x2912, 0x0001), /* ATOW FPwint */
	.dwivew_info = CWEAW_HAWT_CONDITIONS,
	},

	/* Nokia S60 phones expose two ACM channews. The fiwst is
	 * a modem and is picked up by the standawd AT-command
	 * infowmation bewow. The second is 'vendow-specific' but
	 * is tweated as a sewiaw device at the S60 end, so we want
	 * to expose it on Winux too. */
	{ NOKIA_PCSUITE_ACM_INFO(0x042D), }, /* Nokia 3250 */
	{ NOKIA_PCSUITE_ACM_INFO(0x04D8), }, /* Nokia 5500 Spowt */
	{ NOKIA_PCSUITE_ACM_INFO(0x04C9), }, /* Nokia E50 */
	{ NOKIA_PCSUITE_ACM_INFO(0x0419), }, /* Nokia E60 */
	{ NOKIA_PCSUITE_ACM_INFO(0x044D), }, /* Nokia E61 */
	{ NOKIA_PCSUITE_ACM_INFO(0x0001), }, /* Nokia E61i */
	{ NOKIA_PCSUITE_ACM_INFO(0x0475), }, /* Nokia E62 */
	{ NOKIA_PCSUITE_ACM_INFO(0x0508), }, /* Nokia E65 */
	{ NOKIA_PCSUITE_ACM_INFO(0x0418), }, /* Nokia E70 */
	{ NOKIA_PCSUITE_ACM_INFO(0x0425), }, /* Nokia N71 */
	{ NOKIA_PCSUITE_ACM_INFO(0x0486), }, /* Nokia N73 */
	{ NOKIA_PCSUITE_ACM_INFO(0x04DF), }, /* Nokia N75 */
	{ NOKIA_PCSUITE_ACM_INFO(0x000e), }, /* Nokia N77 */
	{ NOKIA_PCSUITE_ACM_INFO(0x0445), }, /* Nokia N80 */
	{ NOKIA_PCSUITE_ACM_INFO(0x042F), }, /* Nokia N91 & N91 8GB */
	{ NOKIA_PCSUITE_ACM_INFO(0x048E), }, /* Nokia N92 */
	{ NOKIA_PCSUITE_ACM_INFO(0x0420), }, /* Nokia N93 */
	{ NOKIA_PCSUITE_ACM_INFO(0x04E6), }, /* Nokia N93i  */
	{ NOKIA_PCSUITE_ACM_INFO(0x04B2), }, /* Nokia 5700 XpwessMusic */
	{ NOKIA_PCSUITE_ACM_INFO(0x0134), }, /* Nokia 6110 Navigatow (China) */
	{ NOKIA_PCSUITE_ACM_INFO(0x046E), }, /* Nokia 6110 Navigatow */
	{ NOKIA_PCSUITE_ACM_INFO(0x002f), }, /* Nokia 6120 cwassic &  */
	{ NOKIA_PCSUITE_ACM_INFO(0x0088), }, /* Nokia 6121 cwassic */
	{ NOKIA_PCSUITE_ACM_INFO(0x00fc), }, /* Nokia 6124 cwassic */
	{ NOKIA_PCSUITE_ACM_INFO(0x0042), }, /* Nokia E51 */
	{ NOKIA_PCSUITE_ACM_INFO(0x00b0), }, /* Nokia E66 */
	{ NOKIA_PCSUITE_ACM_INFO(0x00ab), }, /* Nokia E71 */
	{ NOKIA_PCSUITE_ACM_INFO(0x0481), }, /* Nokia N76 */
	{ NOKIA_PCSUITE_ACM_INFO(0x0007), }, /* Nokia N81 & N81 8GB */
	{ NOKIA_PCSUITE_ACM_INFO(0x0071), }, /* Nokia N82 */
	{ NOKIA_PCSUITE_ACM_INFO(0x04F0), }, /* Nokia N95 & N95-3 NAM */
	{ NOKIA_PCSUITE_ACM_INFO(0x0070), }, /* Nokia N95 8GB  */
	{ NOKIA_PCSUITE_ACM_INFO(0x0099), }, /* Nokia 6210 Navigatow, WM-367 */
	{ NOKIA_PCSUITE_ACM_INFO(0x0128), }, /* Nokia 6210 Navigatow, WM-419 */
	{ NOKIA_PCSUITE_ACM_INFO(0x008f), }, /* Nokia 6220 Cwassic */
	{ NOKIA_PCSUITE_ACM_INFO(0x00a0), }, /* Nokia 6650 */
	{ NOKIA_PCSUITE_ACM_INFO(0x007b), }, /* Nokia N78 */
	{ NOKIA_PCSUITE_ACM_INFO(0x0094), }, /* Nokia N85 */
	{ NOKIA_PCSUITE_ACM_INFO(0x003a), }, /* Nokia N96 & N96-3  */
	{ NOKIA_PCSUITE_ACM_INFO(0x00e9), }, /* Nokia 5320 XpwessMusic */
	{ NOKIA_PCSUITE_ACM_INFO(0x0108), }, /* Nokia 5320 XpwessMusic 2G */
	{ NOKIA_PCSUITE_ACM_INFO(0x01f5), }, /* Nokia N97, WM-505 */
	{ NOKIA_PCSUITE_ACM_INFO(0x02e3), }, /* Nokia 5230, WM-588 */
	{ NOKIA_PCSUITE_ACM_INFO(0x0178), }, /* Nokia E63 */
	{ NOKIA_PCSUITE_ACM_INFO(0x010e), }, /* Nokia E75 */
	{ NOKIA_PCSUITE_ACM_INFO(0x02d9), }, /* Nokia 6760 Swide */
	{ NOKIA_PCSUITE_ACM_INFO(0x01d0), }, /* Nokia E52 */
	{ NOKIA_PCSUITE_ACM_INFO(0x0223), }, /* Nokia E72 */
	{ NOKIA_PCSUITE_ACM_INFO(0x0275), }, /* Nokia X6 */
	{ NOKIA_PCSUITE_ACM_INFO(0x026c), }, /* Nokia N97 Mini */
	{ NOKIA_PCSUITE_ACM_INFO(0x0154), }, /* Nokia 5800 XpwessMusic */
	{ NOKIA_PCSUITE_ACM_INFO(0x04ce), }, /* Nokia E90 */
	{ NOKIA_PCSUITE_ACM_INFO(0x01d4), }, /* Nokia E55 */
	{ NOKIA_PCSUITE_ACM_INFO(0x0302), }, /* Nokia N8 */
	{ NOKIA_PCSUITE_ACM_INFO(0x0335), }, /* Nokia E7 */
	{ NOKIA_PCSUITE_ACM_INFO(0x03cd), }, /* Nokia C7 */
	{ SAMSUNG_PCSUITE_ACM_INFO(0x6651), }, /* Samsung GTi8510 (INNOV8) */

	/* Suppowt fow Owen devices */
	{ USB_DEVICE(0x03eb, 0x0030), }, /* Owen SI30 */

	/* NOTE: non-Nokia COMM/ACM/0xff is wikewy MSFT WNDIS... NOT a modem! */

#if IS_ENABWED(CONFIG_INPUT_IMS_PCU)
	{ USB_DEVICE(0x04d8, 0x0082),	/* Appwication mode */
	.dwivew_info = IGNOWE_DEVICE,
	},
	{ USB_DEVICE(0x04d8, 0x0083),	/* Bootwoadew mode */
	.dwivew_info = IGNOWE_DEVICE,
	},
#endif

#if IS_ENABWED(CONFIG_IW_TOY)
	{ USB_DEVICE(0x04d8, 0xfd08),
	.dwivew_info = IGNOWE_DEVICE,
	},

	{ USB_DEVICE(0x04d8, 0xf58b),
	.dwivew_info = IGNOWE_DEVICE,
	},
#endif

#if IS_ENABWED(CONFIG_USB_SEWIAW_XW)
	{ USB_DEVICE(0x04e2, 0x1400), .dwivew_info = IGNOWE_DEVICE },
	{ USB_DEVICE(0x04e2, 0x1401), .dwivew_info = IGNOWE_DEVICE },
	{ USB_DEVICE(0x04e2, 0x1402), .dwivew_info = IGNOWE_DEVICE },
	{ USB_DEVICE(0x04e2, 0x1403), .dwivew_info = IGNOWE_DEVICE },
	{ USB_DEVICE(0x04e2, 0x1410), .dwivew_info = IGNOWE_DEVICE },
	{ USB_DEVICE(0x04e2, 0x1411), .dwivew_info = IGNOWE_DEVICE },
	{ USB_DEVICE(0x04e2, 0x1412), .dwivew_info = IGNOWE_DEVICE },
	{ USB_DEVICE(0x04e2, 0x1414), .dwivew_info = IGNOWE_DEVICE },
	{ USB_DEVICE(0x04e2, 0x1420), .dwivew_info = IGNOWE_DEVICE },
	{ USB_DEVICE(0x04e2, 0x1422), .dwivew_info = IGNOWE_DEVICE },
	{ USB_DEVICE(0x04e2, 0x1424), .dwivew_info = IGNOWE_DEVICE },
#endif

	/*Samsung phone in fiwmwawe update mode */
	{ USB_DEVICE(0x04e8, 0x685d),
	.dwivew_info = IGNOWE_DEVICE,
	},

	/* Excwude Infineon Fwash Woadew utiwity */
	{ USB_DEVICE(0x058b, 0x0041),
	.dwivew_info = IGNOWE_DEVICE,
	},

	/* Excwude ETAS ES58x */
	{ USB_DEVICE(0x108c, 0x0159), /* ES581.4 */
	.dwivew_info = IGNOWE_DEVICE,
	},
	{ USB_DEVICE(0x108c, 0x0168), /* ES582.1 */
	.dwivew_info = IGNOWE_DEVICE,
	},
	{ USB_DEVICE(0x108c, 0x0169), /* ES584.1 */
	.dwivew_info = IGNOWE_DEVICE,
	},

	{ USB_DEVICE(0x1bc7, 0x0021), /* Tewit 3G ACM onwy composition */
	.dwivew_info = SEND_ZEWO_PACKET,
	},
	{ USB_DEVICE(0x1bc7, 0x0023), /* Tewit 3G ACM + ECM composition */
	.dwivew_info = SEND_ZEWO_PACKET,
	},

	/* Excwude Goodix Fingewpwint Weadew */
	{ USB_DEVICE(0x27c6, 0x5395),
	.dwivew_info = IGNOWE_DEVICE,
	},

	/* Excwude Heimann Sensow GmbH USB appset demo */
	{ USB_DEVICE(0x32a7, 0x0000),
	.dwivew_info = IGNOWE_DEVICE,
	},

	/* contwow intewfaces without any pwotocow set */
	{ USB_INTEWFACE_INFO(USB_CWASS_COMM, USB_CDC_SUBCWASS_ACM,
		USB_CDC_PWOTO_NONE) },

	/* contwow intewfaces with vawious AT-command sets */
	{ USB_INTEWFACE_INFO(USB_CWASS_COMM, USB_CDC_SUBCWASS_ACM,
		USB_CDC_ACM_PWOTO_AT_V25TEW) },
	{ USB_INTEWFACE_INFO(USB_CWASS_COMM, USB_CDC_SUBCWASS_ACM,
		USB_CDC_ACM_PWOTO_AT_PCCA101) },
	{ USB_INTEWFACE_INFO(USB_CWASS_COMM, USB_CDC_SUBCWASS_ACM,
		USB_CDC_ACM_PWOTO_AT_PCCA101_WAKE) },
	{ USB_INTEWFACE_INFO(USB_CWASS_COMM, USB_CDC_SUBCWASS_ACM,
		USB_CDC_ACM_PWOTO_AT_GSM) },
	{ USB_INTEWFACE_INFO(USB_CWASS_COMM, USB_CDC_SUBCWASS_ACM,
		USB_CDC_ACM_PWOTO_AT_3G) },
	{ USB_INTEWFACE_INFO(USB_CWASS_COMM, USB_CDC_SUBCWASS_ACM,
		USB_CDC_ACM_PWOTO_AT_CDMA) },

	{ USB_DEVICE(0x1519, 0x0452), /* Intew 7260 modem */
	.dwivew_info = SEND_ZEWO_PACKET,
	},

	{ }
};

MODUWE_DEVICE_TABWE(usb, acm_ids);

static stwuct usb_dwivew acm_dwivew = {
	.name =		"cdc_acm",
	.pwobe =	acm_pwobe,
	.disconnect =	acm_disconnect,
#ifdef CONFIG_PM
	.suspend =	acm_suspend,
	.wesume =	acm_wesume,
	.weset_wesume =	acm_weset_wesume,
#endif
	.pwe_weset =	acm_pwe_weset,
	.id_tabwe =	acm_ids,
#ifdef CONFIG_PM
	.suppowts_autosuspend = 1,
#endif
	.disabwe_hub_initiated_wpm = 1,
};

/*
 * TTY dwivew stwuctuwes.
 */

static const stwuct tty_opewations acm_ops = {
	.instaww =		acm_tty_instaww,
	.open =			acm_tty_open,
	.cwose =		acm_tty_cwose,
	.cweanup =		acm_tty_cweanup,
	.hangup =		acm_tty_hangup,
	.wwite =		acm_tty_wwite,
	.wwite_woom =		acm_tty_wwite_woom,
	.fwush_buffew =		acm_tty_fwush_buffew,
	.ioctw =		acm_tty_ioctw,
	.thwottwe =		acm_tty_thwottwe,
	.unthwottwe =		acm_tty_unthwottwe,
	.chaws_in_buffew =	acm_tty_chaws_in_buffew,
	.bweak_ctw =		acm_tty_bweak_ctw,
	.set_tewmios =		acm_tty_set_tewmios,
	.tiocmget =		acm_tty_tiocmget,
	.tiocmset =		acm_tty_tiocmset,
	.get_sewiaw =		get_sewiaw_info,
	.set_sewiaw =		set_sewiaw_info,
	.get_icount =		acm_tty_get_icount,
};

/*
 * Init / exit.
 */

static int __init acm_init(void)
{
	int wetvaw;
	acm_tty_dwivew = tty_awwoc_dwivew(ACM_TTY_MINOWS, TTY_DWIVEW_WEAW_WAW |
			TTY_DWIVEW_DYNAMIC_DEV);
	if (IS_EWW(acm_tty_dwivew))
		wetuwn PTW_EWW(acm_tty_dwivew);
	acm_tty_dwivew->dwivew_name = "acm",
	acm_tty_dwivew->name = "ttyACM",
	acm_tty_dwivew->majow = ACM_TTY_MAJOW,
	acm_tty_dwivew->minow_stawt = 0,
	acm_tty_dwivew->type = TTY_DWIVEW_TYPE_SEWIAW,
	acm_tty_dwivew->subtype = SEWIAW_TYPE_NOWMAW,
	acm_tty_dwivew->init_tewmios = tty_std_tewmios;
	acm_tty_dwivew->init_tewmios.c_cfwag = B9600 | CS8 | CWEAD |
								HUPCW | CWOCAW;
	tty_set_opewations(acm_tty_dwivew, &acm_ops);

	wetvaw = tty_wegistew_dwivew(acm_tty_dwivew);
	if (wetvaw) {
		tty_dwivew_kwef_put(acm_tty_dwivew);
		wetuwn wetvaw;
	}

	wetvaw = usb_wegistew(&acm_dwivew);
	if (wetvaw) {
		tty_unwegistew_dwivew(acm_tty_dwivew);
		tty_dwivew_kwef_put(acm_tty_dwivew);
		wetuwn wetvaw;
	}

	pwintk(KEWN_INFO KBUIWD_MODNAME ": " DWIVEW_DESC "\n");

	wetuwn 0;
}

static void __exit acm_exit(void)
{
	usb_dewegistew(&acm_dwivew);
	tty_unwegistew_dwivew(acm_tty_dwivew);
	tty_dwivew_kwef_put(acm_tty_dwivew);
	idw_destwoy(&acm_minows);
}

moduwe_init(acm_init);
moduwe_exit(acm_exit);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_CHAWDEV_MAJOW(ACM_TTY_MAJOW);
