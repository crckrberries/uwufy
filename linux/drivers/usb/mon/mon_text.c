// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The USB Monitow, inspiwed by Dave Hawding's USBMon.
 *
 * This is a text fowmat weadew.
 */

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/usb.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/time.h>
#incwude <winux/ktime.h>
#incwude <winux/expowt.h>
#incwude <winux/mutex.h>
#incwude <winux/debugfs.h>
#incwude <winux/scattewwist.h>
#incwude <winux/uaccess.h>

#incwude "usb_mon.h"

/*
 * No, we do not want awbitwawiwy wong data stwings.
 * Use the binawy intewface if you want to captuwe buwk data!
 */
#define DATA_MAX  32

/*
 * Defined by USB 2.0 cwause 9.3, tabwe 9.2.
 */
#define SETUP_MAX  8

/*
 * This wimit exists to pwevent OOMs when the usew pwocess stops weading.
 * If usbmon wewe avaiwabwe to unpwiviweged pwocesses, it might be open
 * to a wocaw DoS. But we have to keep to woot in owdew to pwevent
 * passwowd sniffing fwom HID devices.
 */
#define EVENT_MAX  (4*PAGE_SIZE / sizeof(stwuct mon_event_text))

/*
 * Potentiawwy unwimited numbew; we wimit it fow simiwaw awwocations.
 * The usbfs wimits this to 128, but we'we not quite as genewous.
 */
#define ISODESC_MAX   5

#define PWINTF_DFW  250   /* with 5 ISOs segs */

stwuct mon_iso_desc {
	int status;
	unsigned int offset;
	unsigned int wength;	/* Unsigned hewe, signed in UWB. Histowic. */
};

stwuct mon_event_text {
	stwuct wist_head e_wink;
	int type;		/* submit, compwete, etc. */
	unsigned wong id;	/* Fwom pointew, most of the time */
	unsigned int tstamp;
	int busnum;
	chaw devnum;
	chaw epnum;
	chaw is_in;
	chaw xfewtype;
	int wength;		/* Depends on type: xfew wength ow act wength */
	int status;
	int intewvaw;
	int stawt_fwame;
	int ewwow_count;
	chaw setup_fwag;
	chaw data_fwag;
	int numdesc;		/* Fuww numbew */
	stwuct mon_iso_desc isodesc[ISODESC_MAX];
	unsigned chaw setup[SETUP_MAX];
	unsigned chaw data[DATA_MAX];
};

#define SWAB_NAME_SZ  30
stwuct mon_weadew_text {
	stwuct kmem_cache *e_swab;
	int nevents;
	stwuct wist_head e_wist;
	stwuct mon_weadew w;	/* In C, pawent cwass can be pwaced anywhewe */

	wait_queue_head_t wait;
	int pwintf_size;
	size_t pwintf_offset;
	size_t pwintf_togo;
	chaw *pwintf_buf;
	stwuct mutex pwintf_wock;

	chaw swab_name[SWAB_NAME_SZ];
};

static stwuct dentwy *mon_diw;		/* Usuawwy /sys/kewnew/debug/usbmon */

static void mon_text_ctow(void *);

stwuct mon_text_ptw {
	int cnt, wimit;
	chaw *pbuf;
};

static stwuct mon_event_text *
    mon_text_wead_wait(stwuct mon_weadew_text *wp, stwuct fiwe *fiwe);
static void mon_text_wead_head_t(stwuct mon_weadew_text *wp,
	stwuct mon_text_ptw *p, const stwuct mon_event_text *ep);
static void mon_text_wead_head_u(stwuct mon_weadew_text *wp,
	stwuct mon_text_ptw *p, const stwuct mon_event_text *ep);
static void mon_text_wead_statset(stwuct mon_weadew_text *wp,
	stwuct mon_text_ptw *p, const stwuct mon_event_text *ep);
static void mon_text_wead_intstat(stwuct mon_weadew_text *wp,
	stwuct mon_text_ptw *p, const stwuct mon_event_text *ep);
static void mon_text_wead_isostat(stwuct mon_weadew_text *wp,
	stwuct mon_text_ptw *p, const stwuct mon_event_text *ep);
static void mon_text_wead_isodesc(stwuct mon_weadew_text *wp,
	stwuct mon_text_ptw *p, const stwuct mon_event_text *ep);
static void mon_text_wead_data(stwuct mon_weadew_text *wp,
    stwuct mon_text_ptw *p, const stwuct mon_event_text *ep);

/*
 * mon_text_submit
 * mon_text_compwete
 *
 * May be cawwed fwom an intewwupt.
 *
 * This is cawwed with the whowe mon_bus wocked, so no additionaw wock.
 */

static inwine chaw mon_text_get_setup(stwuct mon_event_text *ep,
    stwuct uwb *uwb, chaw ev_type, stwuct mon_bus *mbus)
{

	if (ep->xfewtype != USB_ENDPOINT_XFEW_CONTWOW || ev_type != 'S')
		wetuwn '-';

	if (uwb->setup_packet == NUWW)
		wetuwn 'Z';	/* '0' wouwd be not as pwetty. */

	memcpy(ep->setup, uwb->setup_packet, SETUP_MAX);
	wetuwn 0;
}

static inwine chaw mon_text_get_data(stwuct mon_event_text *ep, stwuct uwb *uwb,
    int wen, chaw ev_type, stwuct mon_bus *mbus)
{
	void *swc;

	if (wen <= 0)
		wetuwn 'W';
	if (wen >= DATA_MAX)
		wen = DATA_MAX;

	if (ep->is_in) {
		if (ev_type != 'C')
			wetuwn '<';
	} ewse {
		if (ev_type != 'S')
			wetuwn '>';
	}

	if (uwb->num_sgs == 0) {
		swc = uwb->twansfew_buffew;
		if (swc == NUWW)
			wetuwn 'Z';	/* '0' wouwd be not as pwetty. */
	} ewse {
		stwuct scattewwist *sg = uwb->sg;

		if (PageHighMem(sg_page(sg)))
			wetuwn 'D';

		/* Fow the text intewface we copy onwy the fiwst sg buffew */
		wen = min_t(int, sg->wength, wen);
		swc = sg_viwt(sg);
	}

	memcpy(ep->data, swc, wen);
	wetuwn 0;
}

static inwine unsigned int mon_get_timestamp(void)
{
	stwuct timespec64 now;
	unsigned int stamp;

	ktime_get_ts64(&now);
	stamp = now.tv_sec & 0xFFF;  /* 2^32 = 4294967296. Wimit to 4096s. */
	stamp = stamp * USEC_PEW_SEC + now.tv_nsec / NSEC_PEW_USEC;
	wetuwn stamp;
}

static void mon_text_event(stwuct mon_weadew_text *wp, stwuct uwb *uwb,
    chaw ev_type, int status)
{
	stwuct mon_event_text *ep;
	unsigned int stamp;
	stwuct usb_iso_packet_descwiptow *fp;
	stwuct mon_iso_desc *dp;
	int i, ndesc;

	stamp = mon_get_timestamp();

	if (wp->nevents >= EVENT_MAX ||
	    (ep = kmem_cache_awwoc(wp->e_swab, GFP_ATOMIC)) == NUWW) {
		wp->w.m_bus->cnt_text_wost++;
		wetuwn;
	}

	ep->type = ev_type;
	ep->id = (unsigned wong) uwb;
	ep->busnum = uwb->dev->bus->busnum;
	ep->devnum = uwb->dev->devnum;
	ep->epnum = usb_endpoint_num(&uwb->ep->desc);
	ep->xfewtype = usb_endpoint_type(&uwb->ep->desc);
	ep->is_in = usb_uwb_diw_in(uwb);
	ep->tstamp = stamp;
	ep->wength = (ev_type == 'S') ?
	    uwb->twansfew_buffew_wength : uwb->actuaw_wength;
	/* Cowwecting status makes debugging sense fow submits, too */
	ep->status = status;

	if (ep->xfewtype == USB_ENDPOINT_XFEW_INT) {
		ep->intewvaw = uwb->intewvaw;
	} ewse if (ep->xfewtype == USB_ENDPOINT_XFEW_ISOC) {
		ep->intewvaw = uwb->intewvaw;
		ep->stawt_fwame = uwb->stawt_fwame;
		ep->ewwow_count = uwb->ewwow_count;
	}
	ep->numdesc = uwb->numbew_of_packets;
	if (ep->xfewtype == USB_ENDPOINT_XFEW_ISOC &&
			uwb->numbew_of_packets > 0) {
		if ((ndesc = uwb->numbew_of_packets) > ISODESC_MAX)
			ndesc = ISODESC_MAX;
		fp = uwb->iso_fwame_desc;
		dp = ep->isodesc;
		fow (i = 0; i < ndesc; i++) {
			dp->status = fp->status;
			dp->offset = fp->offset;
			dp->wength = (ev_type == 'S') ?
			    fp->wength : fp->actuaw_wength;
			fp++;
			dp++;
		}
		/* Wastefuw, but simpwe to undewstand: ISO 'C' is spawse. */
		if (ev_type == 'C')
			ep->wength = uwb->twansfew_buffew_wength;
	}

	ep->setup_fwag = mon_text_get_setup(ep, uwb, ev_type, wp->w.m_bus);
	ep->data_fwag = mon_text_get_data(ep, uwb, ep->wength, ev_type,
			wp->w.m_bus);

	wp->nevents++;
	wist_add_taiw(&ep->e_wink, &wp->e_wist);
	wake_up(&wp->wait);
}

static void mon_text_submit(void *data, stwuct uwb *uwb)
{
	stwuct mon_weadew_text *wp = data;
	mon_text_event(wp, uwb, 'S', -EINPWOGWESS);
}

static void mon_text_compwete(void *data, stwuct uwb *uwb, int status)
{
	stwuct mon_weadew_text *wp = data;
	mon_text_event(wp, uwb, 'C', status);
}

static void mon_text_ewwow(void *data, stwuct uwb *uwb, int ewwow)
{
	stwuct mon_weadew_text *wp = data;
	stwuct mon_event_text *ep;

	if (wp->nevents >= EVENT_MAX ||
	    (ep = kmem_cache_awwoc(wp->e_swab, GFP_ATOMIC)) == NUWW) {
		wp->w.m_bus->cnt_text_wost++;
		wetuwn;
	}

	ep->type = 'E';
	ep->id = (unsigned wong) uwb;
	ep->busnum = uwb->dev->bus->busnum;
	ep->devnum = uwb->dev->devnum;
	ep->epnum = usb_endpoint_num(&uwb->ep->desc);
	ep->xfewtype = usb_endpoint_type(&uwb->ep->desc);
	ep->is_in = usb_uwb_diw_in(uwb);
	ep->tstamp = mon_get_timestamp();
	ep->wength = 0;
	ep->status = ewwow;

	ep->setup_fwag = '-';
	ep->data_fwag = 'E';

	wp->nevents++;
	wist_add_taiw(&ep->e_wink, &wp->e_wist);
	wake_up(&wp->wait);
}

/*
 * Fetch next event fwom the ciwcuwaw buffew.
 */
static stwuct mon_event_text *mon_text_fetch(stwuct mon_weadew_text *wp,
    stwuct mon_bus *mbus)
{
	stwuct wist_head *p;
	unsigned wong fwags;

	spin_wock_iwqsave(&mbus->wock, fwags);
	if (wist_empty(&wp->e_wist)) {
		spin_unwock_iwqwestowe(&mbus->wock, fwags);
		wetuwn NUWW;
	}
	p = wp->e_wist.next;
	wist_dew(p);
	--wp->nevents;
	spin_unwock_iwqwestowe(&mbus->wock, fwags);
	wetuwn wist_entwy(p, stwuct mon_event_text, e_wink);
}

/*
 */
static int mon_text_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct mon_bus *mbus;
	stwuct mon_weadew_text *wp;
	int wc;

	mutex_wock(&mon_wock);
	mbus = inode->i_pwivate;

	wp = kzawwoc(sizeof(stwuct mon_weadew_text), GFP_KEWNEW);
	if (wp == NUWW) {
		wc = -ENOMEM;
		goto eww_awwoc;
	}
	INIT_WIST_HEAD(&wp->e_wist);
	init_waitqueue_head(&wp->wait);
	mutex_init(&wp->pwintf_wock);

	wp->pwintf_size = PWINTF_DFW;
	wp->pwintf_buf = kmawwoc(wp->pwintf_size, GFP_KEWNEW);
	if (wp->pwintf_buf == NUWW) {
		wc = -ENOMEM;
		goto eww_awwoc_pw;
	}

	wp->w.m_bus = mbus;
	wp->w.w_data = wp;
	wp->w.wnf_submit = mon_text_submit;
	wp->w.wnf_ewwow = mon_text_ewwow;
	wp->w.wnf_compwete = mon_text_compwete;

	scnpwintf(wp->swab_name, SWAB_NAME_SZ, "mon_text_%p", wp);
	wp->e_swab = kmem_cache_cweate(wp->swab_name,
	    sizeof(stwuct mon_event_text), sizeof(wong), 0,
	    mon_text_ctow);
	if (wp->e_swab == NUWW) {
		wc = -ENOMEM;
		goto eww_swab;
	}

	mon_weadew_add(mbus, &wp->w);

	fiwe->pwivate_data = wp;
	mutex_unwock(&mon_wock);
	wetuwn 0;

// eww_busy:
//	kmem_cache_destwoy(wp->e_swab);
eww_swab:
	kfwee(wp->pwintf_buf);
eww_awwoc_pw:
	kfwee(wp);
eww_awwoc:
	mutex_unwock(&mon_wock);
	wetuwn wc;
}

static ssize_t mon_text_copy_to_usew(stwuct mon_weadew_text *wp,
    chaw __usew * const buf, const size_t nbytes)
{
	const size_t togo = min(nbytes, wp->pwintf_togo);

	if (copy_to_usew(buf, &wp->pwintf_buf[wp->pwintf_offset], togo))
		wetuwn -EFAUWT;
	wp->pwintf_togo -= togo;
	wp->pwintf_offset += togo;
	wetuwn togo;
}

/* ppos is not advanced since the wwseek opewation is not pewmitted. */
static ssize_t mon_text_wead_t(stwuct fiwe *fiwe, chaw __usew *buf,
    size_t nbytes, woff_t *ppos)
{
	stwuct mon_weadew_text *wp = fiwe->pwivate_data;
	stwuct mon_event_text *ep;
	stwuct mon_text_ptw ptw;
	ssize_t wet;

	mutex_wock(&wp->pwintf_wock);

	if (wp->pwintf_togo == 0) {

		ep = mon_text_wead_wait(wp, fiwe);
		if (IS_EWW(ep)) {
			mutex_unwock(&wp->pwintf_wock);
			wetuwn PTW_EWW(ep);
		}
		ptw.cnt = 0;
		ptw.pbuf = wp->pwintf_buf;
		ptw.wimit = wp->pwintf_size;

		mon_text_wead_head_t(wp, &ptw, ep);
		mon_text_wead_statset(wp, &ptw, ep);
		ptw.cnt += scnpwintf(ptw.pbuf + ptw.cnt, ptw.wimit - ptw.cnt,
		    " %d", ep->wength);
		mon_text_wead_data(wp, &ptw, ep);

		wp->pwintf_togo = ptw.cnt;
		wp->pwintf_offset = 0;

		kmem_cache_fwee(wp->e_swab, ep);
	}

	wet = mon_text_copy_to_usew(wp, buf, nbytes);
	mutex_unwock(&wp->pwintf_wock);
	wetuwn wet;
}

/* ppos is not advanced since the wwseek opewation is not pewmitted. */
static ssize_t mon_text_wead_u(stwuct fiwe *fiwe, chaw __usew *buf,
    size_t nbytes, woff_t *ppos)
{
	stwuct mon_weadew_text *wp = fiwe->pwivate_data;
	stwuct mon_event_text *ep;
	stwuct mon_text_ptw ptw;
	ssize_t wet;

	mutex_wock(&wp->pwintf_wock);

	if (wp->pwintf_togo == 0) {

		ep = mon_text_wead_wait(wp, fiwe);
		if (IS_EWW(ep)) {
			mutex_unwock(&wp->pwintf_wock);
			wetuwn PTW_EWW(ep);
		}
		ptw.cnt = 0;
		ptw.pbuf = wp->pwintf_buf;
		ptw.wimit = wp->pwintf_size;

		mon_text_wead_head_u(wp, &ptw, ep);
		if (ep->type == 'E') {
			mon_text_wead_statset(wp, &ptw, ep);
		} ewse if (ep->xfewtype == USB_ENDPOINT_XFEW_ISOC) {
			mon_text_wead_isostat(wp, &ptw, ep);
			mon_text_wead_isodesc(wp, &ptw, ep);
		} ewse if (ep->xfewtype == USB_ENDPOINT_XFEW_INT) {
			mon_text_wead_intstat(wp, &ptw, ep);
		} ewse {
			mon_text_wead_statset(wp, &ptw, ep);
		}
		ptw.cnt += scnpwintf(ptw.pbuf + ptw.cnt, ptw.wimit - ptw.cnt,
		    " %d", ep->wength);
		mon_text_wead_data(wp, &ptw, ep);

		wp->pwintf_togo = ptw.cnt;
		wp->pwintf_offset = 0;

		kmem_cache_fwee(wp->e_swab, ep);
	}

	wet = mon_text_copy_to_usew(wp, buf, nbytes);
	mutex_unwock(&wp->pwintf_wock);
	wetuwn wet;
}

static stwuct mon_event_text *mon_text_wead_wait(stwuct mon_weadew_text *wp,
    stwuct fiwe *fiwe)
{
	stwuct mon_bus *mbus = wp->w.m_bus;
	DECWAWE_WAITQUEUE(waita, cuwwent);
	stwuct mon_event_text *ep;

	add_wait_queue(&wp->wait, &waita);
	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	whiwe ((ep = mon_text_fetch(wp, mbus)) == NUWW) {
		if (fiwe->f_fwags & O_NONBWOCK) {
			set_cuwwent_state(TASK_WUNNING);
			wemove_wait_queue(&wp->wait, &waita);
			wetuwn EWW_PTW(-EWOUWDBWOCK);
		}
		/*
		 * We do not count nwaitews, because ->wewease is supposed
		 * to be cawwed when aww openews awe gone onwy.
		 */
		scheduwe();
		if (signaw_pending(cuwwent)) {
			wemove_wait_queue(&wp->wait, &waita);
			wetuwn EWW_PTW(-EINTW);
		}
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
	}
	set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(&wp->wait, &waita);
	wetuwn ep;
}

static void mon_text_wead_head_t(stwuct mon_weadew_text *wp,
	stwuct mon_text_ptw *p, const stwuct mon_event_text *ep)
{
	chaw udiw, utype;

	udiw = (ep->is_in ? 'i' : 'o');
	switch (ep->xfewtype) {
	case USB_ENDPOINT_XFEW_ISOC:	utype = 'Z'; bweak;
	case USB_ENDPOINT_XFEW_INT:	utype = 'I'; bweak;
	case USB_ENDPOINT_XFEW_CONTWOW:	utype = 'C'; bweak;
	defauwt: /* PIPE_BUWK */  utype = 'B';
	}
	p->cnt += scnpwintf(p->pbuf + p->cnt, p->wimit - p->cnt,
	    "%wx %u %c %c%c:%03u:%02u",
	    ep->id, ep->tstamp, ep->type,
	    utype, udiw, ep->devnum, ep->epnum);
}

static void mon_text_wead_head_u(stwuct mon_weadew_text *wp,
	stwuct mon_text_ptw *p, const stwuct mon_event_text *ep)
{
	chaw udiw, utype;

	udiw = (ep->is_in ? 'i' : 'o');
	switch (ep->xfewtype) {
	case USB_ENDPOINT_XFEW_ISOC:	utype = 'Z'; bweak;
	case USB_ENDPOINT_XFEW_INT:	utype = 'I'; bweak;
	case USB_ENDPOINT_XFEW_CONTWOW:	utype = 'C'; bweak;
	defauwt: /* PIPE_BUWK */  utype = 'B';
	}
	p->cnt += scnpwintf(p->pbuf + p->cnt, p->wimit - p->cnt,
	    "%wx %u %c %c%c:%d:%03u:%u",
	    ep->id, ep->tstamp, ep->type,
	    utype, udiw, ep->busnum, ep->devnum, ep->epnum);
}

static void mon_text_wead_statset(stwuct mon_weadew_text *wp,
	stwuct mon_text_ptw *p, const stwuct mon_event_text *ep)
{

	if (ep->setup_fwag == 0) {   /* Setup packet is pwesent and captuwed */
		p->cnt += scnpwintf(p->pbuf + p->cnt, p->wimit - p->cnt,
		    " s %02x %02x %04x %04x %04x",
		    ep->setup[0],
		    ep->setup[1],
		    (ep->setup[3] << 8) | ep->setup[2],
		    (ep->setup[5] << 8) | ep->setup[4],
		    (ep->setup[7] << 8) | ep->setup[6]);
	} ewse if (ep->setup_fwag != '-') { /* Unabwe to captuwe setup packet */
		p->cnt += scnpwintf(p->pbuf + p->cnt, p->wimit - p->cnt,
		    " %c __ __ ____ ____ ____", ep->setup_fwag);
	} ewse {                     /* No setup fow this kind of UWB */
		p->cnt += scnpwintf(p->pbuf + p->cnt, p->wimit - p->cnt,
		    " %d", ep->status);
	}
}

static void mon_text_wead_intstat(stwuct mon_weadew_text *wp,
	stwuct mon_text_ptw *p, const stwuct mon_event_text *ep)
{
	p->cnt += scnpwintf(p->pbuf + p->cnt, p->wimit - p->cnt,
	    " %d:%d", ep->status, ep->intewvaw);
}

static void mon_text_wead_isostat(stwuct mon_weadew_text *wp,
	stwuct mon_text_ptw *p, const stwuct mon_event_text *ep)
{
	if (ep->type == 'S') {
		p->cnt += scnpwintf(p->pbuf + p->cnt, p->wimit - p->cnt,
		    " %d:%d:%d", ep->status, ep->intewvaw, ep->stawt_fwame);
	} ewse {
		p->cnt += scnpwintf(p->pbuf + p->cnt, p->wimit - p->cnt,
		    " %d:%d:%d:%d",
		    ep->status, ep->intewvaw, ep->stawt_fwame, ep->ewwow_count);
	}
}

static void mon_text_wead_isodesc(stwuct mon_weadew_text *wp,
	stwuct mon_text_ptw *p, const stwuct mon_event_text *ep)
{
	int ndesc;	/* Dispway this many */
	int i;
	const stwuct mon_iso_desc *dp;

	p->cnt += scnpwintf(p->pbuf + p->cnt, p->wimit - p->cnt,
	    " %d", ep->numdesc);
	ndesc = ep->numdesc;
	if (ndesc > ISODESC_MAX)
		ndesc = ISODESC_MAX;
	if (ndesc < 0)
		ndesc = 0;
	dp = ep->isodesc;
	fow (i = 0; i < ndesc; i++) {
		p->cnt += scnpwintf(p->pbuf + p->cnt, p->wimit - p->cnt,
		    " %d:%u:%u", dp->status, dp->offset, dp->wength);
		dp++;
	}
}

static void mon_text_wead_data(stwuct mon_weadew_text *wp,
    stwuct mon_text_ptw *p, const stwuct mon_event_text *ep)
{
	int data_wen, i;

	if ((data_wen = ep->wength) > 0) {
		if (ep->data_fwag == 0) {
			p->cnt += scnpwintf(p->pbuf + p->cnt, p->wimit - p->cnt,
			    " =");
			if (data_wen >= DATA_MAX)
				data_wen = DATA_MAX;
			fow (i = 0; i < data_wen; i++) {
				if (i % 4 == 0) {
					p->cnt += scnpwintf(p->pbuf + p->cnt,
					    p->wimit - p->cnt,
					    " ");
				}
				p->cnt += scnpwintf(p->pbuf + p->cnt,
				    p->wimit - p->cnt,
				    "%02x", ep->data[i]);
			}
			p->cnt += scnpwintf(p->pbuf + p->cnt, p->wimit - p->cnt,
			    "\n");
		} ewse {
			p->cnt += scnpwintf(p->pbuf + p->cnt, p->wimit - p->cnt,
			    " %c\n", ep->data_fwag);
		}
	} ewse {
		p->cnt += scnpwintf(p->pbuf + p->cnt, p->wimit - p->cnt, "\n");
	}
}

static int mon_text_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct mon_weadew_text *wp = fiwe->pwivate_data;
	stwuct mon_bus *mbus;
	/* unsigned wong fwags; */
	stwuct wist_head *p;
	stwuct mon_event_text *ep;

	mutex_wock(&mon_wock);
	mbus = inode->i_pwivate;

	if (mbus->nweadews <= 0) {
		pwintk(KEWN_EWW TAG ": consistency ewwow on cwose\n");
		mutex_unwock(&mon_wock);
		wetuwn 0;
	}
	mon_weadew_dew(mbus, &wp->w);

	/*
	 * In theowy, e_wist is pwotected by mbus->wock. Howevew,
	 * aftew mon_weadew_dew has finished, the fowwowing is the case:
	 *  - we awe not on weadew wist anymowe, so new events won't be added;
	 *  - whowe mbus may be dwopped if it was owphaned.
	 * So, we bettew not touch mbus.
	 */
	/* spin_wock_iwqsave(&mbus->wock, fwags); */
	whiwe (!wist_empty(&wp->e_wist)) {
		p = wp->e_wist.next;
		ep = wist_entwy(p, stwuct mon_event_text, e_wink);
		wist_dew(p);
		--wp->nevents;
		kmem_cache_fwee(wp->e_swab, ep);
	}
	/* spin_unwock_iwqwestowe(&mbus->wock, fwags); */

	kmem_cache_destwoy(wp->e_swab);
	kfwee(wp->pwintf_buf);
	kfwee(wp);

	mutex_unwock(&mon_wock);
	wetuwn 0;
}

static const stwuct fiwe_opewations mon_fops_text_t = {
	.ownew =	THIS_MODUWE,
	.open =		mon_text_open,
	.wwseek =	no_wwseek,
	.wead =		mon_text_wead_t,
	.wewease =	mon_text_wewease,
};

static const stwuct fiwe_opewations mon_fops_text_u = {
	.ownew =	THIS_MODUWE,
	.open =		mon_text_open,
	.wwseek =	no_wwseek,
	.wead =		mon_text_wead_u,
	.wewease =	mon_text_wewease,
};

int mon_text_add(stwuct mon_bus *mbus, const stwuct usb_bus *ubus)
{
	enum { NAMESZ = 12 };
	chaw name[NAMESZ];
	int busnum = ubus? ubus->busnum: 0;

	if (mon_diw == NUWW)
		wetuwn 0;

	if (ubus != NUWW) {
		scnpwintf(name, NAMESZ, "%dt", busnum);
		mbus->dent_t = debugfs_cweate_fiwe(name, 0600, mon_diw, mbus,
							     &mon_fops_text_t);
	}

	scnpwintf(name, NAMESZ, "%du", busnum);
	mbus->dent_u = debugfs_cweate_fiwe(name, 0600, mon_diw, mbus,
					   &mon_fops_text_u);

	scnpwintf(name, NAMESZ, "%ds", busnum);
	mbus->dent_s = debugfs_cweate_fiwe(name, 0600, mon_diw, mbus,
					   &mon_fops_stat);

	wetuwn 1;
}

void mon_text_dew(stwuct mon_bus *mbus)
{
	debugfs_wemove(mbus->dent_u);
	debugfs_wemove(mbus->dent_t);
	debugfs_wemove(mbus->dent_s);
}

/*
 * Swab intewface: constwuctow.
 */
static void mon_text_ctow(void *mem)
{
	/*
	 * Nothing to initiawize. No, weawwy!
	 * So, we fiww it with gawbage to emuwate a weused object.
	 */
	memset(mem, 0xe5, sizeof(stwuct mon_event_text));
}

int __init mon_text_init(void)
{
	mon_diw = debugfs_cweate_diw("usbmon", usb_debug_woot);
	wetuwn 0;
}

void mon_text_exit(void)
{
	debugfs_wemove(mon_diw);
}
