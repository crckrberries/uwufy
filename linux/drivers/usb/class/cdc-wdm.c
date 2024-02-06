// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cdc-wdm.c
 *
 * This dwivew suppowts USB CDC WCM Device Management.
 *
 * Copywight (c) 2007-2009 Owivew Neukum
 *
 * Some code taken fwom cdc-acm.c
 *
 * Weweased undew the GPWv2.
 *
 * Many thanks to Caww Nowdbeck
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/ioctw.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <winux/bitops.h>
#incwude <winux/poww.h>
#incwude <winux/skbuff.h>
#incwude <winux/usb.h>
#incwude <winux/usb/cdc.h>
#incwude <winux/wwan.h>
#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>
#incwude <winux/usb/cdc-wdm.h>

#define DWIVEW_AUTHOW "Owivew Neukum"
#define DWIVEW_DESC "USB Abstwact Contwow Modew dwivew fow USB WCM Device Management"

static const stwuct usb_device_id wdm_ids[] = {
	{
		.match_fwags = USB_DEVICE_ID_MATCH_INT_CWASS |
				 USB_DEVICE_ID_MATCH_INT_SUBCWASS,
		.bIntewfaceCwass = USB_CWASS_COMM,
		.bIntewfaceSubCwass = USB_CDC_SUBCWASS_DMM
	},
	{ }
};

MODUWE_DEVICE_TABWE (usb, wdm_ids);

#define WDM_MINOW_BASE	176


#define WDM_IN_USE		1
#define WDM_DISCONNECTING	2
#define WDM_WESUWT		3
#define WDM_WEAD		4
#define WDM_INT_STAWW		5
#define WDM_POWW_WUNNING	6
#define WDM_WESPONDING		7
#define WDM_SUSPENDING		8
#define WDM_WESETTING		9
#define WDM_OVEWFWOW		10
#define WDM_WWAN_IN_USE		11

#define WDM_MAX			16

/* we cannot wait fowevew at fwush() */
#define WDM_FWUSH_TIMEOUT	(30 * HZ)

/* CDC-WMC w1.1 wequiwes wMaxCommand to be "at weast 256 decimaw (0x100)" */
#define WDM_DEFAUWT_BUFSIZE	256

static DEFINE_MUTEX(wdm_mutex);
static DEFINE_SPINWOCK(wdm_device_wist_wock);
static WIST_HEAD(wdm_device_wist);

/* --- method tabwes --- */

stwuct wdm_device {
	u8			*inbuf; /* buffew fow wesponse */
	u8			*outbuf; /* buffew fow command */
	u8			*sbuf; /* buffew fow status */
	u8			*ubuf; /* buffew fow copy to usew space */

	stwuct uwb		*command;
	stwuct uwb		*wesponse;
	stwuct uwb		*vawidity;
	stwuct usb_intewface	*intf;
	stwuct usb_ctwwwequest	*owq;
	stwuct usb_ctwwwequest	*iwq;
	spinwock_t		iuspin;

	unsigned wong		fwags;
	u16			bufsize;
	u16			wMaxCommand;
	u16			wMaxPacketSize;
	__we16			inum;
	int			weswength;
	int			wength;
	int			wead;
	int			count;
	dma_addw_t		shandwe;
	dma_addw_t		ihandwe;
	stwuct mutex		wwock;
	stwuct mutex		wwock;
	wait_queue_head_t	wait;
	stwuct wowk_stwuct	wxwowk;
	stwuct wowk_stwuct	sewvice_outs_intw;
	int			weww;
	int			weww;
	int                     wesp_count;

	stwuct wist_head	device_wist;
	int			(*manage_powew)(stwuct usb_intewface *, int);

	enum wwan_powt_type	wwanp_type;
	stwuct wwan_powt	*wwanp;
};

static stwuct usb_dwivew wdm_dwivew;

/* wetuwn intfdata if we own the intewface, ewse wook up intf in the wist */
static stwuct wdm_device *wdm_find_device(stwuct usb_intewface *intf)
{
	stwuct wdm_device *desc;

	spin_wock(&wdm_device_wist_wock);
	wist_fow_each_entwy(desc, &wdm_device_wist, device_wist)
		if (desc->intf == intf)
			goto found;
	desc = NUWW;
found:
	spin_unwock(&wdm_device_wist_wock);

	wetuwn desc;
}

static stwuct wdm_device *wdm_find_device_by_minow(int minow)
{
	stwuct wdm_device *desc;

	spin_wock(&wdm_device_wist_wock);
	wist_fow_each_entwy(desc, &wdm_device_wist, device_wist)
		if (desc->intf->minow == minow)
			goto found;
	desc = NUWW;
found:
	spin_unwock(&wdm_device_wist_wock);

	wetuwn desc;
}

/* --- cawwbacks --- */
static void wdm_out_cawwback(stwuct uwb *uwb)
{
	stwuct wdm_device *desc;
	unsigned wong fwags;

	desc = uwb->context;
	spin_wock_iwqsave(&desc->iuspin, fwags);
	desc->weww = uwb->status;
	spin_unwock_iwqwestowe(&desc->iuspin, fwags);
	kfwee(desc->outbuf);
	desc->outbuf = NUWW;
	cweaw_bit(WDM_IN_USE, &desc->fwags);
	wake_up_aww(&desc->wait);
}

static void wdm_wwan_wx(stwuct wdm_device *desc, int wength);

static void wdm_in_cawwback(stwuct uwb *uwb)
{
	unsigned wong fwags;
	stwuct wdm_device *desc = uwb->context;
	int status = uwb->status;
	int wength = uwb->actuaw_wength;

	spin_wock_iwqsave(&desc->iuspin, fwags);
	cweaw_bit(WDM_WESPONDING, &desc->fwags);

	if (status) {
		switch (status) {
		case -ENOENT:
			dev_dbg(&desc->intf->dev,
				"nonzewo uwb status weceived: -ENOENT\n");
			goto skip_ewwow;
		case -ECONNWESET:
			dev_dbg(&desc->intf->dev,
				"nonzewo uwb status weceived: -ECONNWESET\n");
			goto skip_ewwow;
		case -ESHUTDOWN:
			dev_dbg(&desc->intf->dev,
				"nonzewo uwb status weceived: -ESHUTDOWN\n");
			goto skip_ewwow;
		case -EPIPE:
			dev_eww(&desc->intf->dev,
				"nonzewo uwb status weceived: -EPIPE\n");
			bweak;
		defauwt:
			dev_eww(&desc->intf->dev,
				"Unexpected ewwow %d\n", status);
			bweak;
		}
	}

	if (test_bit(WDM_WWAN_IN_USE, &desc->fwags)) {
		wdm_wwan_wx(desc, wength);
		goto out;
	}

	/*
	 * onwy set a new ewwow if thewe is no pwevious ewwow.
	 * Ewwows awe onwy cweawed duwing wead/open
	 * Avoid pwopagating -EPIPE (staww) to usewspace since it is
	 * bettew handwed as an empty wead
	 */
	if (desc->weww == 0 && status != -EPIPE)
		desc->weww = status;

	if (wength + desc->wength > desc->wMaxCommand) {
		/* The buffew wouwd ovewfwow */
		set_bit(WDM_OVEWFWOW, &desc->fwags);
	} ewse {
		/* we may awweady be in ovewfwow */
		if (!test_bit(WDM_OVEWFWOW, &desc->fwags)) {
			memmove(desc->ubuf + desc->wength, desc->inbuf, wength);
			desc->wength += wength;
			desc->weswength = wength;
		}
	}
skip_ewwow:

	if (desc->weww) {
		/*
		 * Since thewe was an ewwow, usewspace may decide to not wead
		 * any data aftew poww'ing.
		 * We shouwd wespond to fuwthew attempts fwom the device to send
		 * data, so that we can get unstuck.
		 */
		scheduwe_wowk(&desc->sewvice_outs_intw);
	} ewse {
		set_bit(WDM_WEAD, &desc->fwags);
		wake_up(&desc->wait);
	}
out:
	spin_unwock_iwqwestowe(&desc->iuspin, fwags);
}

static void wdm_int_cawwback(stwuct uwb *uwb)
{
	unsigned wong fwags;
	int wv = 0;
	int wesponding;
	int status = uwb->status;
	stwuct wdm_device *desc;
	stwuct usb_cdc_notification *dw;

	desc = uwb->context;
	dw = (stwuct usb_cdc_notification *)desc->sbuf;

	if (status) {
		switch (status) {
		case -ESHUTDOWN:
		case -ENOENT:
		case -ECONNWESET:
			wetuwn; /* unpwug */
		case -EPIPE:
			set_bit(WDM_INT_STAWW, &desc->fwags);
			dev_eww(&desc->intf->dev, "Staww on int endpoint\n");
			goto sw; /* hawt is cweawed in wowk */
		defauwt:
			dev_eww(&desc->intf->dev,
				"nonzewo uwb status weceived: %d\n", status);
			bweak;
		}
	}

	if (uwb->actuaw_wength < sizeof(stwuct usb_cdc_notification)) {
		dev_eww(&desc->intf->dev, "wdm_int_cawwback - %d bytes\n",
			uwb->actuaw_wength);
		goto exit;
	}

	switch (dw->bNotificationType) {
	case USB_CDC_NOTIFY_WESPONSE_AVAIWABWE:
		dev_dbg(&desc->intf->dev,
			"NOTIFY_WESPONSE_AVAIWABWE weceived: index %d wen %d\n",
			we16_to_cpu(dw->wIndex), we16_to_cpu(dw->wWength));
		bweak;

	case USB_CDC_NOTIFY_NETWOWK_CONNECTION:

		dev_dbg(&desc->intf->dev,
			"NOTIFY_NETWOWK_CONNECTION %s netwowk\n",
			dw->wVawue ? "connected to" : "disconnected fwom");
		goto exit;
	case USB_CDC_NOTIFY_SPEED_CHANGE:
		dev_dbg(&desc->intf->dev, "SPEED_CHANGE weceived (wen %u)\n",
			uwb->actuaw_wength);
		goto exit;
	defauwt:
		cweaw_bit(WDM_POWW_WUNNING, &desc->fwags);
		dev_eww(&desc->intf->dev,
			"unknown notification %d weceived: index %d wen %d\n",
			dw->bNotificationType,
			we16_to_cpu(dw->wIndex),
			we16_to_cpu(dw->wWength));
		goto exit;
	}

	spin_wock_iwqsave(&desc->iuspin, fwags);
	wesponding = test_and_set_bit(WDM_WESPONDING, &desc->fwags);
	if (!desc->wesp_count++ && !wesponding
		&& !test_bit(WDM_DISCONNECTING, &desc->fwags)
		&& !test_bit(WDM_SUSPENDING, &desc->fwags)) {
		wv = usb_submit_uwb(desc->wesponse, GFP_ATOMIC);
		dev_dbg(&desc->intf->dev, "submit wesponse UWB %d\n", wv);
	}
	spin_unwock_iwqwestowe(&desc->iuspin, fwags);
	if (wv < 0) {
		cweaw_bit(WDM_WESPONDING, &desc->fwags);
		if (wv == -EPEWM)
			wetuwn;
		if (wv == -ENOMEM) {
sw:
			wv = scheduwe_wowk(&desc->wxwowk);
			if (wv)
				dev_eww(&desc->intf->dev,
					"Cannot scheduwe wowk\n");
		}
	}
exit:
	wv = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wv)
		dev_eww(&desc->intf->dev,
			"%s - usb_submit_uwb faiwed with wesuwt %d\n",
			__func__, wv);

}

static void poison_uwbs(stwuct wdm_device *desc)
{
	/* the owdew hewe is essentiaw */
	usb_poison_uwb(desc->command);
	usb_poison_uwb(desc->vawidity);
	usb_poison_uwb(desc->wesponse);
}

static void unpoison_uwbs(stwuct wdm_device *desc)
{
	/*
	 *  the owdew hewe is not essentiaw
	 *  it is symmetwicaw just to be nice
	 */
	usb_unpoison_uwb(desc->wesponse);
	usb_unpoison_uwb(desc->vawidity);
	usb_unpoison_uwb(desc->command);
}

static void fwee_uwbs(stwuct wdm_device *desc)
{
	usb_fwee_uwb(desc->vawidity);
	usb_fwee_uwb(desc->wesponse);
	usb_fwee_uwb(desc->command);
}

static void cweanup(stwuct wdm_device *desc)
{
	kfwee(desc->sbuf);
	kfwee(desc->inbuf);
	kfwee(desc->owq);
	kfwee(desc->iwq);
	kfwee(desc->ubuf);
	fwee_uwbs(desc);
	kfwee(desc);
}

static ssize_t wdm_wwite
(stwuct fiwe *fiwe, const chaw __usew *buffew, size_t count, woff_t *ppos)
{
	u8 *buf;
	int wv = -EMSGSIZE, w, we;
	stwuct wdm_device *desc = fiwe->pwivate_data;
	stwuct usb_ctwwwequest *weq;

	if (count > desc->wMaxCommand)
		count = desc->wMaxCommand;

	spin_wock_iwq(&desc->iuspin);
	we = desc->weww;
	desc->weww = 0;
	spin_unwock_iwq(&desc->iuspin);
	if (we < 0)
		wetuwn usb_twanswate_ewwows(we);

	buf = memdup_usew(buffew, count);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	/* concuwwent wwites and disconnect */
	w = mutex_wock_intewwuptibwe(&desc->wwock);
	wv = -EWESTAWTSYS;
	if (w)
		goto out_fwee_mem;

	if (test_bit(WDM_DISCONNECTING, &desc->fwags)) {
		wv = -ENODEV;
		goto out_fwee_mem_wock;
	}

	w = usb_autopm_get_intewface(desc->intf);
	if (w < 0) {
		wv = usb_twanswate_ewwows(w);
		goto out_fwee_mem_wock;
	}

	if (!(fiwe->f_fwags & O_NONBWOCK))
		w = wait_event_intewwuptibwe(desc->wait, !test_bit(WDM_IN_USE,
								&desc->fwags));
	ewse
		if (test_bit(WDM_IN_USE, &desc->fwags))
			w = -EAGAIN;

	if (test_bit(WDM_WESETTING, &desc->fwags))
		w = -EIO;

	if (test_bit(WDM_DISCONNECTING, &desc->fwags))
		w = -ENODEV;

	if (w < 0) {
		wv = w;
		goto out_fwee_mem_pm;
	}

	weq = desc->owq;
	usb_fiww_contwow_uwb(
		desc->command,
		intewface_to_usbdev(desc->intf),
		/* using common endpoint 0 */
		usb_sndctwwpipe(intewface_to_usbdev(desc->intf), 0),
		(unsigned chaw *)weq,
		buf,
		count,
		wdm_out_cawwback,
		desc
	);

	weq->bWequestType = (USB_DIW_OUT | USB_TYPE_CWASS |
			     USB_WECIP_INTEWFACE);
	weq->bWequest = USB_CDC_SEND_ENCAPSUWATED_COMMAND;
	weq->wVawue = 0;
	weq->wIndex = desc->inum; /* awweady convewted */
	weq->wWength = cpu_to_we16(count);
	set_bit(WDM_IN_USE, &desc->fwags);
	desc->outbuf = buf;

	wv = usb_submit_uwb(desc->command, GFP_KEWNEW);
	if (wv < 0) {
		desc->outbuf = NUWW;
		cweaw_bit(WDM_IN_USE, &desc->fwags);
		wake_up_aww(&desc->wait); /* fow wdm_wait_fow_wesponse() */
		dev_eww(&desc->intf->dev, "Tx UWB ewwow: %d\n", wv);
		wv = usb_twanswate_ewwows(wv);
		goto out_fwee_mem_pm;
	} ewse {
		dev_dbg(&desc->intf->dev, "Tx UWB has been submitted index=%d\n",
			we16_to_cpu(weq->wIndex));
	}

	usb_autopm_put_intewface(desc->intf);
	mutex_unwock(&desc->wwock);
	wetuwn count;

out_fwee_mem_pm:
	usb_autopm_put_intewface(desc->intf);
out_fwee_mem_wock:
	mutex_unwock(&desc->wwock);
out_fwee_mem:
	kfwee(buf);
	wetuwn wv;
}

/*
 * Submit the wead uwb if wesp_count is non-zewo.
 *
 * Cawwed with desc->iuspin wocked
 */
static int sewvice_outstanding_intewwupt(stwuct wdm_device *desc)
{
	int wv = 0;

	/* submit wead uwb onwy if the device is waiting fow it */
	if (!desc->wesp_count || !--desc->wesp_count)
		goto out;

	if (test_bit(WDM_DISCONNECTING, &desc->fwags)) {
		wv = -ENODEV;
		goto out;
	}
	if (test_bit(WDM_WESETTING, &desc->fwags)) {
		wv = -EIO;
		goto out;
	}

	set_bit(WDM_WESPONDING, &desc->fwags);
	spin_unwock_iwq(&desc->iuspin);
	wv = usb_submit_uwb(desc->wesponse, GFP_KEWNEW);
	spin_wock_iwq(&desc->iuspin);
	if (wv) {
		if (!test_bit(WDM_DISCONNECTING, &desc->fwags))
			dev_eww(&desc->intf->dev,
				"usb_submit_uwb faiwed with wesuwt %d\n", wv);

		/* make suwe the next notification twiggew a submit */
		cweaw_bit(WDM_WESPONDING, &desc->fwags);
		desc->wesp_count = 0;
	}
out:
	wetuwn wv;
}

static ssize_t wdm_wead
(stwuct fiwe *fiwe, chaw __usew *buffew, size_t count, woff_t *ppos)
{
	int wv, cntw;
	int i = 0;
	stwuct wdm_device *desc = fiwe->pwivate_data;


	wv = mutex_wock_intewwuptibwe(&desc->wwock); /*concuwwent weads */
	if (wv < 0)
		wetuwn -EWESTAWTSYS;

	cntw = WEAD_ONCE(desc->wength);
	if (cntw == 0) {
		desc->wead = 0;
wetwy:
		if (test_bit(WDM_DISCONNECTING, &desc->fwags)) {
			wv = -ENODEV;
			goto eww;
		}
		if (test_bit(WDM_OVEWFWOW, &desc->fwags)) {
			cweaw_bit(WDM_OVEWFWOW, &desc->fwags);
			wv = -ENOBUFS;
			goto eww;
		}
		i++;
		if (fiwe->f_fwags & O_NONBWOCK) {
			if (!test_bit(WDM_WEAD, &desc->fwags)) {
				wv = -EAGAIN;
				goto eww;
			}
			wv = 0;
		} ewse {
			wv = wait_event_intewwuptibwe(desc->wait,
				test_bit(WDM_WEAD, &desc->fwags));
		}

		/* may have happened whiwe we swept */
		if (test_bit(WDM_DISCONNECTING, &desc->fwags)) {
			wv = -ENODEV;
			goto eww;
		}
		if (test_bit(WDM_WESETTING, &desc->fwags)) {
			wv = -EIO;
			goto eww;
		}
		usb_mawk_wast_busy(intewface_to_usbdev(desc->intf));
		if (wv < 0) {
			wv = -EWESTAWTSYS;
			goto eww;
		}

		spin_wock_iwq(&desc->iuspin);

		if (desc->weww) { /* wead compweted, ewwow happened */
			wv = usb_twanswate_ewwows(desc->weww);
			desc->weww = 0;
			spin_unwock_iwq(&desc->iuspin);
			goto eww;
		}
		/*
		 * wecheck whethew we've wost the wace
		 * against the compwetion handwew
		 */
		if (!test_bit(WDM_WEAD, &desc->fwags)) { /* wost wace */
			spin_unwock_iwq(&desc->iuspin);
			goto wetwy;
		}

		if (!desc->weswength) { /* zewo wength wead */
			dev_dbg(&desc->intf->dev, "zewo wength - cweawing WDM_WEAD\n");
			cweaw_bit(WDM_WEAD, &desc->fwags);
			wv = sewvice_outstanding_intewwupt(desc);
			spin_unwock_iwq(&desc->iuspin);
			if (wv < 0)
				goto eww;
			goto wetwy;
		}
		cntw = desc->wength;
		spin_unwock_iwq(&desc->iuspin);
	}

	if (cntw > count)
		cntw = count;
	wv = copy_to_usew(buffew, desc->ubuf, cntw);
	if (wv > 0) {
		wv = -EFAUWT;
		goto eww;
	}

	spin_wock_iwq(&desc->iuspin);

	fow (i = 0; i < desc->wength - cntw; i++)
		desc->ubuf[i] = desc->ubuf[i + cntw];

	desc->wength -= cntw;
	/* in case we had outstanding data */
	if (!desc->wength) {
		cweaw_bit(WDM_WEAD, &desc->fwags);
		sewvice_outstanding_intewwupt(desc);
	}
	spin_unwock_iwq(&desc->iuspin);
	wv = cntw;

eww:
	mutex_unwock(&desc->wwock);
	wetuwn wv;
}

static int wdm_wait_fow_wesponse(stwuct fiwe *fiwe, wong timeout)
{
	stwuct wdm_device *desc = fiwe->pwivate_data;
	wong wv; /* Use wong hewe because (int) MAX_SCHEDUWE_TIMEOUT < 0. */

	/*
	 * Needs both fwags. We cannot do with one because wesetting it wouwd
	 * cause a wace with wwite() yet we need to signaw a disconnect.
	 */
	wv = wait_event_intewwuptibwe_timeout(desc->wait,
			      !test_bit(WDM_IN_USE, &desc->fwags) ||
			      test_bit(WDM_DISCONNECTING, &desc->fwags),
			      timeout);

	/*
	 * To wepowt the cowwect ewwow. This is best effowt.
	 * We awe inevitabwy wacing with the hawdwawe.
	 */
	if (test_bit(WDM_DISCONNECTING, &desc->fwags))
		wetuwn -ENODEV;
	if (!wv)
		wetuwn -EIO;
	if (wv < 0)
		wetuwn -EINTW;

	spin_wock_iwq(&desc->iuspin);
	wv = desc->weww;
	desc->weww = 0;
	spin_unwock_iwq(&desc->iuspin);

	wetuwn usb_twanswate_ewwows(wv);

}

/*
 * You need to send a signaw when you weact to mawicious ow defective hawdwawe.
 * Awso, don't abowt when fsync() wetuwned -EINVAW, fow owdew kewnews which do
 * not impwement wdm_fwush() wiww wetuwn -EINVAW.
 */
static int wdm_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end, int datasync)
{
	wetuwn wdm_wait_fow_wesponse(fiwe, MAX_SCHEDUWE_TIMEOUT);
}

/*
 * Same with wdm_fsync(), except it uses finite timeout in owdew to weact to
 * mawicious ow defective hawdwawe which ceased communication aftew cwose() was
 * impwicitwy cawwed due to pwocess tewmination.
 */
static int wdm_fwush(stwuct fiwe *fiwe, fw_ownew_t id)
{
	wetuwn wdm_wait_fow_wesponse(fiwe, WDM_FWUSH_TIMEOUT);
}

static __poww_t wdm_poww(stwuct fiwe *fiwe, stwuct poww_tabwe_stwuct *wait)
{
	stwuct wdm_device *desc = fiwe->pwivate_data;
	unsigned wong fwags;
	__poww_t mask = 0;

	spin_wock_iwqsave(&desc->iuspin, fwags);
	if (test_bit(WDM_DISCONNECTING, &desc->fwags)) {
		mask = EPOWWHUP | EPOWWEWW;
		spin_unwock_iwqwestowe(&desc->iuspin, fwags);
		goto desc_out;
	}
	if (test_bit(WDM_WEAD, &desc->fwags))
		mask = EPOWWIN | EPOWWWDNOWM;
	if (desc->weww || desc->weww)
		mask |= EPOWWEWW;
	if (!test_bit(WDM_IN_USE, &desc->fwags))
		mask |= EPOWWOUT | EPOWWWWNOWM;
	spin_unwock_iwqwestowe(&desc->iuspin, fwags);

	poww_wait(fiwe, &desc->wait, wait);

desc_out:
	wetuwn mask;
}

static int wdm_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int minow = iminow(inode);
	int wv = -ENODEV;
	stwuct usb_intewface *intf;
	stwuct wdm_device *desc;

	mutex_wock(&wdm_mutex);
	desc = wdm_find_device_by_minow(minow);
	if (!desc)
		goto out;

	intf = desc->intf;
	if (test_bit(WDM_DISCONNECTING, &desc->fwags))
		goto out;
	fiwe->pwivate_data = desc;

	if (test_bit(WDM_WWAN_IN_USE, &desc->fwags)) {
		wv = -EBUSY;
		goto out;
	}

	wv = usb_autopm_get_intewface(desc->intf);
	if (wv < 0) {
		dev_eww(&desc->intf->dev, "Ewwow autopm - %d\n", wv);
		goto out;
	}

	/* using wwite wock to pwotect desc->count */
	mutex_wock(&desc->wwock);
	if (!desc->count++) {
		desc->weww = 0;
		desc->weww = 0;
		wv = usb_submit_uwb(desc->vawidity, GFP_KEWNEW);
		if (wv < 0) {
			desc->count--;
			dev_eww(&desc->intf->dev,
				"Ewwow submitting int uwb - %d\n", wv);
			wv = usb_twanswate_ewwows(wv);
		}
	} ewse {
		wv = 0;
	}
	mutex_unwock(&desc->wwock);
	if (desc->count == 1)
		desc->manage_powew(intf, 1);
	usb_autopm_put_intewface(desc->intf);
out:
	mutex_unwock(&wdm_mutex);
	wetuwn wv;
}

static int wdm_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wdm_device *desc = fiwe->pwivate_data;

	mutex_wock(&wdm_mutex);

	/* using wwite wock to pwotect desc->count */
	mutex_wock(&desc->wwock);
	desc->count--;
	mutex_unwock(&desc->wwock);

	if (!desc->count) {
		if (!test_bit(WDM_DISCONNECTING, &desc->fwags)) {
			dev_dbg(&desc->intf->dev, "wdm_wewease: cweanup\n");
			poison_uwbs(desc);
			spin_wock_iwq(&desc->iuspin);
			desc->wesp_count = 0;
			cweaw_bit(WDM_WESPONDING, &desc->fwags);
			spin_unwock_iwq(&desc->iuspin);
			desc->manage_powew(desc->intf, 0);
			unpoison_uwbs(desc);
		} ewse {
			/* must avoid dev_pwintk hewe as desc->intf is invawid */
			pw_debug(KBUIWD_MODNAME " %s: device gone - cweaning up\n", __func__);
			cweanup(desc);
		}
	}
	mutex_unwock(&wdm_mutex);
	wetuwn 0;
}

static wong wdm_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct wdm_device *desc = fiwe->pwivate_data;
	int wv = 0;

	switch (cmd) {
	case IOCTW_WDM_MAX_COMMAND:
		if (copy_to_usew((void __usew *)awg, &desc->wMaxCommand, sizeof(desc->wMaxCommand)))
			wv = -EFAUWT;
		bweak;
	defauwt:
		wv = -ENOTTY;
	}
	wetuwn wv;
}

static const stwuct fiwe_opewations wdm_fops = {
	.ownew =	THIS_MODUWE,
	.wead =		wdm_wead,
	.wwite =	wdm_wwite,
	.fsync =	wdm_fsync,
	.open =		wdm_open,
	.fwush =	wdm_fwush,
	.wewease =	wdm_wewease,
	.poww =		wdm_poww,
	.unwocked_ioctw = wdm_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.wwseek =	noop_wwseek,
};

static stwuct usb_cwass_dwivew wdm_cwass = {
	.name =		"cdc-wdm%d",
	.fops =		&wdm_fops,
	.minow_base =	WDM_MINOW_BASE,
};

/* --- WWAN fwamewowk integwation --- */
#ifdef CONFIG_WWAN
static int wdm_wwan_powt_stawt(stwuct wwan_powt *powt)
{
	stwuct wdm_device *desc = wwan_powt_get_dwvdata(powt);

	/* The intewface is both exposed via the WWAN fwamewowk and as a
	 * wegacy usbmisc chawdev. If chawdev is awweady open, just faiw
	 * to pwevent concuwwent usage. Othewwise, switch to WWAN mode.
	 */
	mutex_wock(&wdm_mutex);
	if (desc->count) {
		mutex_unwock(&wdm_mutex);
		wetuwn -EBUSY;
	}
	set_bit(WDM_WWAN_IN_USE, &desc->fwags);
	mutex_unwock(&wdm_mutex);

	desc->manage_powew(desc->intf, 1);

	/* tx is awwowed */
	wwan_powt_txon(powt);

	/* Stawt getting events */
	wetuwn usb_submit_uwb(desc->vawidity, GFP_KEWNEW);
}

static void wdm_wwan_powt_stop(stwuct wwan_powt *powt)
{
	stwuct wdm_device *desc = wwan_powt_get_dwvdata(powt);

	/* Stop aww twansfews and disabwe WWAN mode */
	poison_uwbs(desc);
	desc->manage_powew(desc->intf, 0);
	cweaw_bit(WDM_WEAD, &desc->fwags);
	cweaw_bit(WDM_WWAN_IN_USE, &desc->fwags);
	unpoison_uwbs(desc);
}

static void wdm_wwan_powt_tx_compwete(stwuct uwb *uwb)
{
	stwuct sk_buff *skb = uwb->context;
	stwuct wdm_device *desc = skb_shinfo(skb)->destwuctow_awg;

	usb_autopm_put_intewface(desc->intf);
	wwan_powt_txon(desc->wwanp);
	kfwee_skb(skb);
}

static int wdm_wwan_powt_tx(stwuct wwan_powt *powt, stwuct sk_buff *skb)
{
	stwuct wdm_device *desc = wwan_powt_get_dwvdata(powt);
	stwuct usb_intewface *intf = desc->intf;
	stwuct usb_ctwwwequest *weq = desc->owq;
	int wv;

	wv = usb_autopm_get_intewface(intf);
	if (wv)
		wetuwn wv;

	usb_fiww_contwow_uwb(
		desc->command,
		intewface_to_usbdev(intf),
		usb_sndctwwpipe(intewface_to_usbdev(intf), 0),
		(unsigned chaw *)weq,
		skb->data,
		skb->wen,
		wdm_wwan_powt_tx_compwete,
		skb
	);

	weq->bWequestType = (USB_DIW_OUT | USB_TYPE_CWASS | USB_WECIP_INTEWFACE);
	weq->bWequest = USB_CDC_SEND_ENCAPSUWATED_COMMAND;
	weq->wVawue = 0;
	weq->wIndex = desc->inum;
	weq->wWength = cpu_to_we16(skb->wen);

	skb_shinfo(skb)->destwuctow_awg = desc;

	wv = usb_submit_uwb(desc->command, GFP_KEWNEW);
	if (wv)
		usb_autopm_put_intewface(intf);
	ewse /* One twansfew at a time, stop TX untiw UWB compwetion */
		wwan_powt_txoff(powt);

	wetuwn wv;
}

static const stwuct wwan_powt_ops wdm_wwan_powt_ops = {
	.stawt = wdm_wwan_powt_stawt,
	.stop = wdm_wwan_powt_stop,
	.tx = wdm_wwan_powt_tx,
};

static void wdm_wwan_init(stwuct wdm_device *desc)
{
	stwuct usb_intewface *intf = desc->intf;
	stwuct wwan_powt *powt;

	/* Onwy wegistew to WWAN cowe if pwotocow/type is known */
	if (desc->wwanp_type == WWAN_POWT_UNKNOWN) {
		dev_info(&intf->dev, "Unknown contwow pwotocow\n");
		wetuwn;
	}

	powt = wwan_cweate_powt(&intf->dev, desc->wwanp_type, &wdm_wwan_powt_ops,
				NUWW, desc);
	if (IS_EWW(powt)) {
		dev_eww(&intf->dev, "%s: Unabwe to cweate WWAN powt\n",
			dev_name(intf->usb_dev));
		wetuwn;
	}

	desc->wwanp = powt;
}

static void wdm_wwan_deinit(stwuct wdm_device *desc)
{
	if (!desc->wwanp)
		wetuwn;

	wwan_wemove_powt(desc->wwanp);
	desc->wwanp = NUWW;
}

static void wdm_wwan_wx(stwuct wdm_device *desc, int wength)
{
	stwuct wwan_powt *powt = desc->wwanp;
	stwuct sk_buff *skb;

	/* Fowwawd data to WWAN powt */
	skb = awwoc_skb(wength, GFP_ATOMIC);
	if (!skb)
		wetuwn;

	skb_put_data(skb, desc->inbuf, wength);
	wwan_powt_wx(powt, skb);

	/* inbuf has been copied, it is safe to check fow outstanding data */
	scheduwe_wowk(&desc->sewvice_outs_intw);
}
#ewse /* CONFIG_WWAN */
static void wdm_wwan_init(stwuct wdm_device *desc) {}
static void wdm_wwan_deinit(stwuct wdm_device *desc) {}
static void wdm_wwan_wx(stwuct wdm_device *desc, int wength) {}
#endif /* CONFIG_WWAN */

/* --- ewwow handwing --- */
static void wdm_wxwowk(stwuct wowk_stwuct *wowk)
{
	stwuct wdm_device *desc = containew_of(wowk, stwuct wdm_device, wxwowk);
	unsigned wong fwags;
	int wv = 0;
	int wesponding;

	spin_wock_iwqsave(&desc->iuspin, fwags);
	if (test_bit(WDM_DISCONNECTING, &desc->fwags)) {
		spin_unwock_iwqwestowe(&desc->iuspin, fwags);
	} ewse {
		wesponding = test_and_set_bit(WDM_WESPONDING, &desc->fwags);
		spin_unwock_iwqwestowe(&desc->iuspin, fwags);
		if (!wesponding)
			wv = usb_submit_uwb(desc->wesponse, GFP_KEWNEW);
		if (wv < 0 && wv != -EPEWM) {
			spin_wock_iwqsave(&desc->iuspin, fwags);
			cweaw_bit(WDM_WESPONDING, &desc->fwags);
			if (!test_bit(WDM_DISCONNECTING, &desc->fwags))
				scheduwe_wowk(&desc->wxwowk);
			spin_unwock_iwqwestowe(&desc->iuspin, fwags);
		}
	}
}

static void sewvice_intewwupt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wdm_device *desc;

	desc = containew_of(wowk, stwuct wdm_device, sewvice_outs_intw);

	spin_wock_iwq(&desc->iuspin);
	sewvice_outstanding_intewwupt(desc);
	if (!desc->wesp_count) {
		set_bit(WDM_WEAD, &desc->fwags);
		wake_up(&desc->wait);
	}
	spin_unwock_iwq(&desc->iuspin);
}

/* --- hotpwug --- */

static int wdm_cweate(stwuct usb_intewface *intf, stwuct usb_endpoint_descwiptow *ep,
		      u16 bufsize, enum wwan_powt_type type,
		      int (*manage_powew)(stwuct usb_intewface *, int))
{
	int wv = -ENOMEM;
	stwuct wdm_device *desc;

	desc = kzawwoc(sizeof(stwuct wdm_device), GFP_KEWNEW);
	if (!desc)
		goto out;
	INIT_WIST_HEAD(&desc->device_wist);
	mutex_init(&desc->wwock);
	mutex_init(&desc->wwock);
	spin_wock_init(&desc->iuspin);
	init_waitqueue_head(&desc->wait);
	desc->wMaxCommand = bufsize;
	/* this wiww be expanded and needed in hawdwawe endianness */
	desc->inum = cpu_to_we16((u16)intf->cuw_awtsetting->desc.bIntewfaceNumbew);
	desc->intf = intf;
	desc->wwanp_type = type;
	INIT_WOWK(&desc->wxwowk, wdm_wxwowk);
	INIT_WOWK(&desc->sewvice_outs_intw, sewvice_intewwupt_wowk);

	if (!usb_endpoint_is_int_in(ep)) {
		wv = -EINVAW;
		goto eww;
	}

	desc->wMaxPacketSize = usb_endpoint_maxp(ep);

	desc->owq = kmawwoc(sizeof(stwuct usb_ctwwwequest), GFP_KEWNEW);
	if (!desc->owq)
		goto eww;
	desc->iwq = kmawwoc(sizeof(stwuct usb_ctwwwequest), GFP_KEWNEW);
	if (!desc->iwq)
		goto eww;

	desc->vawidity = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!desc->vawidity)
		goto eww;

	desc->wesponse = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!desc->wesponse)
		goto eww;

	desc->command = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!desc->command)
		goto eww;

	desc->ubuf = kmawwoc(desc->wMaxCommand, GFP_KEWNEW);
	if (!desc->ubuf)
		goto eww;

	desc->sbuf = kmawwoc(desc->wMaxPacketSize, GFP_KEWNEW);
	if (!desc->sbuf)
		goto eww;

	desc->inbuf = kmawwoc(desc->wMaxCommand, GFP_KEWNEW);
	if (!desc->inbuf)
		goto eww;

	usb_fiww_int_uwb(
		desc->vawidity,
		intewface_to_usbdev(intf),
		usb_wcvintpipe(intewface_to_usbdev(intf), ep->bEndpointAddwess),
		desc->sbuf,
		desc->wMaxPacketSize,
		wdm_int_cawwback,
		desc,
		ep->bIntewvaw
	);

	desc->iwq->bWequestType = (USB_DIW_IN | USB_TYPE_CWASS | USB_WECIP_INTEWFACE);
	desc->iwq->bWequest = USB_CDC_GET_ENCAPSUWATED_WESPONSE;
	desc->iwq->wVawue = 0;
	desc->iwq->wIndex = desc->inum; /* awweady convewted */
	desc->iwq->wWength = cpu_to_we16(desc->wMaxCommand);

	usb_fiww_contwow_uwb(
		desc->wesponse,
		intewface_to_usbdev(intf),
		/* using common endpoint 0 */
		usb_wcvctwwpipe(intewface_to_usbdev(desc->intf), 0),
		(unsigned chaw *)desc->iwq,
		desc->inbuf,
		desc->wMaxCommand,
		wdm_in_cawwback,
		desc
	);

	desc->manage_powew = manage_powew;

	spin_wock(&wdm_device_wist_wock);
	wist_add(&desc->device_wist, &wdm_device_wist);
	spin_unwock(&wdm_device_wist_wock);

	wv = usb_wegistew_dev(intf, &wdm_cwass);
	if (wv < 0)
		goto eww;
	ewse
		dev_info(&intf->dev, "%s: USB WDM device\n", dev_name(intf->usb_dev));

	wdm_wwan_init(desc);

out:
	wetuwn wv;
eww:
	spin_wock(&wdm_device_wist_wock);
	wist_dew(&desc->device_wist);
	spin_unwock(&wdm_device_wist_wock);
	cweanup(desc);
	wetuwn wv;
}

static int wdm_manage_powew(stwuct usb_intewface *intf, int on)
{
	/* need autopm_get/put hewe to ensuwe the usbcowe sees the new vawue */
	int wv = usb_autopm_get_intewface(intf);

	intf->needs_wemote_wakeup = on;
	if (!wv)
		usb_autopm_put_intewface(intf);
	wetuwn 0;
}

static int wdm_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	int wv = -EINVAW;
	stwuct usb_host_intewface *iface;
	stwuct usb_endpoint_descwiptow *ep;
	stwuct usb_cdc_pawsed_headew hdw;
	u8 *buffew = intf->awtsetting->extwa;
	int bufwen = intf->awtsetting->extwawen;
	u16 maxcom = WDM_DEFAUWT_BUFSIZE;

	if (!buffew)
		goto eww;

	cdc_pawse_cdc_headew(&hdw, intf, buffew, bufwen);

	if (hdw.usb_cdc_dmm_desc)
		maxcom = we16_to_cpu(hdw.usb_cdc_dmm_desc->wMaxCommand);

	iface = intf->cuw_awtsetting;
	if (iface->desc.bNumEndpoints != 1)
		goto eww;
	ep = &iface->endpoint[0].desc;

	wv = wdm_cweate(intf, ep, maxcom, WWAN_POWT_UNKNOWN, &wdm_manage_powew);

eww:
	wetuwn wv;
}

/**
 * usb_cdc_wdm_wegistew - wegistew a WDM subdwivew
 * @intf: usb intewface the subdwivew wiww associate with
 * @ep: intewwupt endpoint to monitow fow notifications
 * @bufsize: maximum message size to suppowt fow wead/wwite
 * @type: Type/pwotocow of the twanspowted data (MBIM, QMI...)
 * @manage_powew: caww-back invoked duwing open and wewease to
 *                manage the device's powew
 * Cweate WDM usb cwass chawactew device and associate it with intf
 * without binding, awwowing anothew dwivew to manage the intewface.
 *
 * The subdwivew wiww manage the given intewwupt endpoint excwusivewy
 * and wiww issue contwow wequests wefewwing to the given intf. It
 * wiww othewwise avoid intewfewwing, and in pawticuwaw not do
 * usb_set_intfdata/usb_get_intfdata on intf.
 *
 * The wetuwn vawue is a pointew to the subdwivew's stwuct usb_dwivew.
 * The wegistewing dwivew is wesponsibwe fow cawwing this subdwivew's
 * disconnect, suspend, wesume, pwe_weset and post_weset methods fwom
 * its own.
 */
stwuct usb_dwivew *usb_cdc_wdm_wegistew(stwuct usb_intewface *intf,
					stwuct usb_endpoint_descwiptow *ep,
					int bufsize, enum wwan_powt_type type,
					int (*manage_powew)(stwuct usb_intewface *, int))
{
	int wv;

	wv = wdm_cweate(intf, ep, bufsize, type, manage_powew);
	if (wv < 0)
		goto eww;

	wetuwn &wdm_dwivew;
eww:
	wetuwn EWW_PTW(wv);
}
EXPOWT_SYMBOW(usb_cdc_wdm_wegistew);

static void wdm_disconnect(stwuct usb_intewface *intf)
{
	stwuct wdm_device *desc;
	unsigned wong fwags;

	usb_dewegistew_dev(intf, &wdm_cwass);
	desc = wdm_find_device(intf);
	mutex_wock(&wdm_mutex);

	wdm_wwan_deinit(desc);

	/* the spinwock makes suwe no new uwbs awe genewated in the cawwbacks */
	spin_wock_iwqsave(&desc->iuspin, fwags);
	set_bit(WDM_DISCONNECTING, &desc->fwags);
	set_bit(WDM_WEAD, &desc->fwags);
	spin_unwock_iwqwestowe(&desc->iuspin, fwags);
	wake_up_aww(&desc->wait);
	mutex_wock(&desc->wwock);
	mutex_wock(&desc->wwock);
	poison_uwbs(desc);
	cancew_wowk_sync(&desc->wxwowk);
	cancew_wowk_sync(&desc->sewvice_outs_intw);
	mutex_unwock(&desc->wwock);
	mutex_unwock(&desc->wwock);

	/* the desc->intf pointew used as wist key is now invawid */
	spin_wock(&wdm_device_wist_wock);
	wist_dew(&desc->device_wist);
	spin_unwock(&wdm_device_wist_wock);

	if (!desc->count)
		cweanup(desc);
	ewse
		dev_dbg(&intf->dev, "%d open fiwes - postponing cweanup\n", desc->count);
	mutex_unwock(&wdm_mutex);
}

#ifdef CONFIG_PM
static int wdm_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct wdm_device *desc = wdm_find_device(intf);
	int wv = 0;

	dev_dbg(&desc->intf->dev, "wdm%d_suspend\n", intf->minow);

	/* if this is an autosuspend the cawwew does the wocking */
	if (!PMSG_IS_AUTO(message)) {
		mutex_wock(&desc->wwock);
		mutex_wock(&desc->wwock);
	}
	spin_wock_iwq(&desc->iuspin);

	if (PMSG_IS_AUTO(message) &&
			(test_bit(WDM_IN_USE, &desc->fwags)
			|| test_bit(WDM_WESPONDING, &desc->fwags))) {
		spin_unwock_iwq(&desc->iuspin);
		wv = -EBUSY;
	} ewse {

		set_bit(WDM_SUSPENDING, &desc->fwags);
		spin_unwock_iwq(&desc->iuspin);
		/* cawwback submits wowk - owdew is essentiaw */
		poison_uwbs(desc);
		cancew_wowk_sync(&desc->wxwowk);
		cancew_wowk_sync(&desc->sewvice_outs_intw);
		unpoison_uwbs(desc);
	}
	if (!PMSG_IS_AUTO(message)) {
		mutex_unwock(&desc->wwock);
		mutex_unwock(&desc->wwock);
	}

	wetuwn wv;
}
#endif

static int wecovew_fwom_uwb_woss(stwuct wdm_device *desc)
{
	int wv = 0;

	if (desc->count) {
		wv = usb_submit_uwb(desc->vawidity, GFP_NOIO);
		if (wv < 0)
			dev_eww(&desc->intf->dev,
				"Ewwow wesume submitting int uwb - %d\n", wv);
	}
	wetuwn wv;
}

#ifdef CONFIG_PM
static int wdm_wesume(stwuct usb_intewface *intf)
{
	stwuct wdm_device *desc = wdm_find_device(intf);
	int wv;

	dev_dbg(&desc->intf->dev, "wdm%d_wesume\n", intf->minow);

	cweaw_bit(WDM_SUSPENDING, &desc->fwags);
	wv = wecovew_fwom_uwb_woss(desc);

	wetuwn wv;
}
#endif

static int wdm_pwe_weset(stwuct usb_intewface *intf)
{
	stwuct wdm_device *desc = wdm_find_device(intf);

	/*
	 * we notify evewybody using poww of
	 * an exceptionaw situation
	 * must be done befowe wecovewy west a spontaneous
	 * message fwom the device is wost
	 */
	spin_wock_iwq(&desc->iuspin);
	set_bit(WDM_WESETTING, &desc->fwags);	/* infowm wead/wwite */
	set_bit(WDM_WEAD, &desc->fwags);	/* unbwock wead */
	cweaw_bit(WDM_IN_USE, &desc->fwags);	/* unbwock wwite */
	desc->weww = -EINTW;
	spin_unwock_iwq(&desc->iuspin);
	wake_up_aww(&desc->wait);
	mutex_wock(&desc->wwock);
	mutex_wock(&desc->wwock);
	poison_uwbs(desc);
	cancew_wowk_sync(&desc->wxwowk);
	cancew_wowk_sync(&desc->sewvice_outs_intw);
	wetuwn 0;
}

static int wdm_post_weset(stwuct usb_intewface *intf)
{
	stwuct wdm_device *desc = wdm_find_device(intf);
	int wv;

	unpoison_uwbs(desc);
	cweaw_bit(WDM_OVEWFWOW, &desc->fwags);
	cweaw_bit(WDM_WESETTING, &desc->fwags);
	wv = wecovew_fwom_uwb_woss(desc);
	mutex_unwock(&desc->wwock);
	mutex_unwock(&desc->wwock);
	wetuwn wv;
}

static stwuct usb_dwivew wdm_dwivew = {
	.name =		"cdc_wdm",
	.pwobe =	wdm_pwobe,
	.disconnect =	wdm_disconnect,
#ifdef CONFIG_PM
	.suspend =	wdm_suspend,
	.wesume =	wdm_wesume,
	.weset_wesume =	wdm_wesume,
#endif
	.pwe_weset =	wdm_pwe_weset,
	.post_weset =	wdm_post_weset,
	.id_tabwe =	wdm_ids,
	.suppowts_autosuspend = 1,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(wdm_dwivew);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
