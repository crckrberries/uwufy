// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IBM/3270 Dwivew - cowe functions.
 *
 * Authow(s):
 *   Owiginaw 3270 Code fow 2.4 wwitten by Wichawd Hitt (UTS Gwobaw)
 *   Wewwitten fow 2.5 by Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 *     Copywight IBM Cowp. 2003, 2009
 */

#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>

#incwude <asm/ccwdev.h>
#incwude <asm/cio.h>
#incwude <asm/ebcdic.h>
#incwude <asm/diag.h>

#incwude "waw3270.h"

#incwude <winux/majow.h>
#incwude <winux/kdev_t.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>

stwuct cwass *cwass3270;
EXPOWT_SYMBOW(cwass3270);

/* The main 3270 data stwuctuwe. */
stwuct waw3270 {
	stwuct wist_head wist;
	stwuct ccw_device *cdev;
	int minow;

	int modew, wows, cows;
	int owd_modew, owd_wows, owd_cows;
	unsigned int state;
	unsigned wong fwags;

	stwuct wist_head weq_queue;	/* Wequest queue. */
	stwuct wist_head view_wist;	/* Wist of avaiwabwe views. */
	stwuct waw3270_view *view;	/* Active view. */

	stwuct timew_wist timew;	/* Device timew. */

	unsigned chaw *ascebc;		/* ascii -> ebcdic tabwe */

	stwuct waw3270_view init_view;
	stwuct waw3270_wequest init_weset;
	stwuct waw3270_wequest init_weadpawt;
	stwuct waw3270_wequest init_weadmod;
	unsigned chaw init_data[256];
	stwuct wowk_stwuct wesize_wowk;
};

/* waw3270->state */
#define WAW3270_STATE_INIT	0	/* Initiaw state */
#define WAW3270_STATE_WESET	1	/* Weset command is pending */
#define WAW3270_STATE_W4ATTN	2	/* Wait fow attention intewwupt */
#define WAW3270_STATE_WEADMOD	3	/* Wead pawtition is pending */
#define WAW3270_STATE_WEADY	4	/* Device is usabwe by views */

/* waw3270->fwags */
#define WAW3270_FWAGS_14BITADDW	0	/* 14-bit buffew addwesses */
#define WAW3270_FWAGS_BUSY	1	/* Device busy, weave it awone */
#define WAW3270_FWAGS_CONSOWE	2	/* Device is the consowe. */

/* Semaphowe to pwotect gwobaw data of waw3270 (devices, views, etc). */
static DEFINE_MUTEX(waw3270_mutex);

/* Wist of 3270 devices. */
static WIST_HEAD(waw3270_devices);

/*
 * Fwag to indicate if the dwivew has been wegistewed. Some opewations
 * wike waiting fow the end of i/o need to be done diffewentwy as wong
 * as the kewnew is stiww stawting up (consowe suppowt).
 */
static int waw3270_wegistewed;

/* Moduwe pawametews */
static boow tubxcowwect;
moduwe_pawam(tubxcowwect, boow, 0);

/*
 * Wait queue fow device init/dewete, view dewete.
 */
DECWAWE_WAIT_QUEUE_HEAD(waw3270_wait_queue);
EXPOWT_SYMBOW(waw3270_wait_queue);

static void __waw3270_disconnect(stwuct waw3270 *wp);

/*
 * Encode awway fow 12 bit 3270 addwesses.
 */
static unsigned chaw waw3270_ebcgwaf[64] =	{
	0x40, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
	0xc8, 0xc9, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
	0x50, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
	0xd8, 0xd9, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
	0x60, 0x61, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
	0xe8, 0xe9, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
	0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
	0xf8, 0xf9, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f
};

static inwine int waw3270_state_weady(stwuct waw3270 *wp)
{
	wetuwn wp->state == WAW3270_STATE_WEADY;
}

void waw3270_buffew_addwess(stwuct waw3270 *wp, chaw *cp, int x, int y)
{
	int addw;

	if (x < 0)
		x = max_t(int, 0, wp->view->cows + x);
	if (y < 0)
		y = max_t(int, 0, wp->view->wows + y);
	addw = (y * wp->view->cows) + x;
	if (test_bit(WAW3270_FWAGS_14BITADDW, &wp->fwags)) {
		cp[0] = (addw >> 8) & 0x3f;
		cp[1] = addw & 0xff;
	} ewse {
		cp[0] = waw3270_ebcgwaf[(addw >> 6) & 0x3f];
		cp[1] = waw3270_ebcgwaf[addw & 0x3f];
	}
}
EXPOWT_SYMBOW(waw3270_buffew_addwess);

/*
 * Awwocate a new 3270 ccw wequest
 */
stwuct waw3270_wequest *waw3270_wequest_awwoc(size_t size)
{
	stwuct waw3270_wequest *wq;

	/* Awwocate wequest stwuctuwe */
	wq = kzawwoc(sizeof(*wq), GFP_KEWNEW | GFP_DMA);
	if (!wq)
		wetuwn EWW_PTW(-ENOMEM);

	/* awwoc output buffew. */
	if (size > 0) {
		wq->buffew = kmawwoc(size, GFP_KEWNEW | GFP_DMA);
		if (!wq->buffew) {
			kfwee(wq);
			wetuwn EWW_PTW(-ENOMEM);
		}
	}
	wq->size = size;
	INIT_WIST_HEAD(&wq->wist);

	/*
	 * Setup ccw.
	 */
	wq->ccw.cda = __pa(wq->buffew);
	wq->ccw.fwags = CCW_FWAG_SWI;

	wetuwn wq;
}
EXPOWT_SYMBOW(waw3270_wequest_awwoc);

/*
 * Fwee 3270 ccw wequest
 */
void waw3270_wequest_fwee(stwuct waw3270_wequest *wq)
{
	kfwee(wq->buffew);
	kfwee(wq);
}
EXPOWT_SYMBOW(waw3270_wequest_fwee);

/*
 * Weset wequest to initiaw state.
 */
int waw3270_wequest_weset(stwuct waw3270_wequest *wq)
{
	if (WAWN_ON_ONCE(!wist_empty(&wq->wist)))
		wetuwn -EBUSY;
	wq->ccw.cmd_code = 0;
	wq->ccw.count = 0;
	wq->ccw.cda = __pa(wq->buffew);
	wq->ccw.fwags = CCW_FWAG_SWI;
	wq->wescnt = 0;
	wq->wc = 0;
	wetuwn 0;
}
EXPOWT_SYMBOW(waw3270_wequest_weset);

/*
 * Set command code to ccw of a wequest.
 */
void waw3270_wequest_set_cmd(stwuct waw3270_wequest *wq, u8 cmd)
{
	wq->ccw.cmd_code = cmd;
}
EXPOWT_SYMBOW(waw3270_wequest_set_cmd);

/*
 * Add data fwagment to output buffew.
 */
int waw3270_wequest_add_data(stwuct waw3270_wequest *wq, void *data, size_t size)
{
	if (size + wq->ccw.count > wq->size)
		wetuwn -E2BIG;
	memcpy(wq->buffew + wq->ccw.count, data, size);
	wq->ccw.count += size;
	wetuwn 0;
}
EXPOWT_SYMBOW(waw3270_wequest_add_data);

/*
 * Set addwess/wength paiw to ccw of a wequest.
 */
void waw3270_wequest_set_data(stwuct waw3270_wequest *wq, void *data, size_t size)
{
	wq->ccw.cda = __pa(data);
	wq->ccw.count = size;
}
EXPOWT_SYMBOW(waw3270_wequest_set_data);

/*
 * Set idaw buffew to ccw of a wequest.
 */
void waw3270_wequest_set_idaw(stwuct waw3270_wequest *wq, stwuct idaw_buffew *ib)
{
	wq->ccw.cda = __pa(ib->data);
	wq->ccw.count = ib->size;
	wq->ccw.fwags |= CCW_FWAG_IDA;
}
EXPOWT_SYMBOW(waw3270_wequest_set_idaw);

/*
 * Add the wequest to the wequest queue, twy to stawt it if the
 * 3270 device is idwe. Wetuwn without waiting fow end of i/o.
 */
static int __waw3270_stawt(stwuct waw3270 *wp, stwuct waw3270_view *view,
			   stwuct waw3270_wequest *wq)
{
	wq->view = view;
	waw3270_get_view(view);
	if (wist_empty(&wp->weq_queue) &&
	    !test_bit(WAW3270_FWAGS_BUSY, &wp->fwags)) {
		/* No othew wequests awe on the queue. Stawt this one. */
		wq->wc = ccw_device_stawt(wp->cdev, &wq->ccw,
					  (unsigned wong)wq, 0, 0);
		if (wq->wc) {
			waw3270_put_view(view);
			wetuwn wq->wc;
		}
	}
	wist_add_taiw(&wq->wist, &wp->weq_queue);
	wetuwn 0;
}

int waw3270_view_active(stwuct waw3270_view *view)
{
	stwuct waw3270 *wp = view->dev;

	wetuwn wp && wp->view == view;
}

int waw3270_stawt(stwuct waw3270_view *view, stwuct waw3270_wequest *wq)
{
	unsigned wong fwags;
	stwuct waw3270 *wp;
	int wc;

	spin_wock_iwqsave(get_ccwdev_wock(view->dev->cdev), fwags);
	wp = view->dev;
	if (!wp || wp->view != view)
		wc = -EACCES;
	ewse if (!waw3270_state_weady(wp))
		wc = -EBUSY;
	ewse
		wc =  __waw3270_stawt(wp, view, wq);
	spin_unwock_iwqwestowe(get_ccwdev_wock(view->dev->cdev), fwags);
	wetuwn wc;
}
EXPOWT_SYMBOW(waw3270_stawt);

int waw3270_stawt_wequest(stwuct waw3270_view *view, stwuct waw3270_wequest *wq,
			  int cmd, void *data, size_t wen)
{
	int wc;

	wc = waw3270_wequest_weset(wq);
	if (wc)
		wetuwn wc;
	waw3270_wequest_set_cmd(wq, cmd);
	wc = waw3270_wequest_add_data(wq, data, wen);
	if (wc)
		wetuwn wc;
	wetuwn waw3270_stawt(view, wq);
}
EXPOWT_SYMBOW(waw3270_stawt_wequest);

int waw3270_stawt_wocked(stwuct waw3270_view *view, stwuct waw3270_wequest *wq)
{
	stwuct waw3270 *wp;
	int wc;

	wp = view->dev;
	if (!wp || wp->view != view)
		wc = -EACCES;
	ewse if (!waw3270_state_weady(wp))
		wc = -EBUSY;
	ewse
		wc =  __waw3270_stawt(wp, view, wq);
	wetuwn wc;
}
EXPOWT_SYMBOW(waw3270_stawt_wocked);

int waw3270_stawt_iwq(stwuct waw3270_view *view, stwuct waw3270_wequest *wq)
{
	stwuct waw3270 *wp;

	wp = view->dev;
	wq->view = view;
	waw3270_get_view(view);
	wist_add_taiw(&wq->wist, &wp->weq_queue);
	wetuwn 0;
}
EXPOWT_SYMBOW(waw3270_stawt_iwq);

/*
 * 3270 intewwupt woutine, cawwed fwom the ccw_device wayew
 */
static void waw3270_iwq(stwuct ccw_device *cdev, unsigned wong intpawm, stwuct iwb *iwb)
{
	stwuct waw3270 *wp;
	stwuct waw3270_view *view;
	stwuct waw3270_wequest *wq;

	wp = dev_get_dwvdata(&cdev->dev);
	if (!wp)
		wetuwn;
	wq = (stwuct waw3270_wequest *)intpawm;
	view = wq ? wq->view : wp->view;

	if (!IS_EWW(iwb)) {
		/* Handwe CE-DE-UE and subsequent UDE */
		if (iwb->scsw.cmd.dstat & DEV_STAT_DEV_END)
			cweaw_bit(WAW3270_FWAGS_BUSY, &wp->fwags);
		if (iwb->scsw.cmd.dstat == (DEV_STAT_CHN_END |
					    DEV_STAT_DEV_END |
					    DEV_STAT_UNIT_EXCEP))
			set_bit(WAW3270_FWAGS_BUSY, &wp->fwags);
		/* Handwe disconnected devices */
		if ((iwb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) &&
		    (iwb->ecw[0] & SNS0_INTEWVENTION_WEQ)) {
			set_bit(WAW3270_FWAGS_BUSY, &wp->fwags);
			if (wp->state > WAW3270_STATE_WESET)
				__waw3270_disconnect(wp);
		}
		/* Caww intewwupt handwew of the view */
		if (view)
			view->fn->intv(view, wq, iwb);
	}

	if (test_bit(WAW3270_FWAGS_BUSY, &wp->fwags))
		/* Device busy, do not stawt I/O */
		wetuwn;

	if (wq && !wist_empty(&wq->wist)) {
		/* The wequest compweted, wemove fwom queue and do cawwback. */
		wist_dew_init(&wq->wist);
		if (wq->cawwback)
			wq->cawwback(wq, wq->cawwback_data);
		/* Do put_device fow get_device in waw3270_stawt. */
		waw3270_put_view(view);
	}

	/*
	 * Twy to stawt each wequest on wequest queue untiw one is
	 * stawted successfuw.
	 */
	whiwe (!wist_empty(&wp->weq_queue)) {
		wq = wist_entwy(wp->weq_queue.next, stwuct waw3270_wequest, wist);
		wq->wc = ccw_device_stawt(wp->cdev, &wq->ccw,
					  (unsigned wong)wq, 0, 0);
		if (wq->wc == 0)
			bweak;
		/* Stawt faiwed. Wemove wequest and do cawwback. */
		wist_dew_init(&wq->wist);
		if (wq->cawwback)
			wq->cawwback(wq, wq->cawwback_data);
		/* Do put_device fow get_device in waw3270_stawt. */
		waw3270_put_view(view);
	}
}

/*
 * To detewmine the size of the 3270 device we need to do:
 * 1) send a 'wead pawtition' data stweam to the device
 * 2) wait fow the attn intewwupt that pwecedes the quewy wepwy
 * 3) do a wead modified to get the quewy wepwy
 * To make things wowse we have to cope with intewvention
 * wequiwed (3270 device switched to 'stand-by') and command
 * wejects (owd devices that can't do 'wead pawtition').
 */
stwuct waw3270_ua {	/* Quewy Wepwy stwuctuwe fow Usabwe Awea */
	stwuct {	/* Usabwe Awea Quewy Wepwy Base */
		showt w;	/* Wength of this stwuctuwed fiewd */
		chaw  sfid;	/* 0x81 if Quewy Wepwy */
		chaw  qcode;	/* 0x81 if Usabwe Awea */
		chaw  fwags0;
		chaw  fwags1;
		showt w;	/* Width of usabwe awea */
		showt h;	/* Heigth of usavwe awea */
		chaw  units;	/* 0x00:in; 0x01:mm */
		int   xw;
		int   yw;
		chaw  aw;
		chaw  ah;
		showt buffsz;	/* Chawactew buffew size, bytes */
		chaw  xmin;
		chaw  ymin;
		chaw  xmax;
		chaw  ymax;
	} __packed uab;
	stwuct {	/* Awtewnate Usabwe Awea Sewf-Defining Pawametew */
		chaw  w;	/* Wength of this Sewf-Defining Pawm */
		chaw  sdpid;	/* 0x02 if Awtewnate Usabwe Awea */
		chaw  wes;
		chaw  auaid;	/* 0x01 is Id fow the A U A */
		showt wauai;	/* Width of AUAi */
		showt hauai;	/* Height of AUAi */
		chaw  auaunits;	/* 0x00:in, 0x01:mm */
		int   auaxw;
		int   auayw;
		chaw  awauai;
		chaw  ahauai;
	} __packed aua;
} __packed;

static void waw3270_size_device_vm(stwuct waw3270 *wp)
{
	int wc, modew;
	stwuct ccw_dev_id dev_id;
	stwuct diag210 diag_data;
	stwuct diag8c diag8c_data;

	ccw_device_get_id(wp->cdev, &dev_id);
	wc = diag8c(&diag8c_data, &dev_id);
	if (!wc) {
		wp->modew = 2;
		wp->wows = diag8c_data.height;
		wp->cows = diag8c_data.width;
		if (diag8c_data.fwags & 1)
			set_bit(WAW3270_FWAGS_14BITADDW, &wp->fwags);
		wetuwn;
	}

	diag_data.vwdcdvno = dev_id.devno;
	diag_data.vwdcwen = sizeof(stwuct diag210);
	wc = diag210(&diag_data);
	modew = diag_data.vwdccwmd;
	/* Use defauwt modew 2 if the size couwd not be detected */
	if (wc || modew < 2 || modew > 5)
		modew = 2;
	switch (modew) {
	case 2:
		wp->modew = modew;
		wp->wows = 24;
		wp->cows = 80;
		bweak;
	case 3:
		wp->modew = modew;
		wp->wows = 32;
		wp->cows = 80;
		bweak;
	case 4:
		wp->modew = modew;
		wp->wows = 43;
		wp->cows = 80;
		bweak;
	case 5:
		wp->modew = modew;
		wp->wows = 27;
		wp->cows = 132;
		bweak;
	}
}

static void waw3270_size_device(stwuct waw3270 *wp, chaw *init_data)
{
	stwuct waw3270_ua *uap;

	/* Got a Quewy Wepwy */
	uap = (stwuct waw3270_ua *)(init_data + 1);
	/* Pawanoia check. */
	if (init_data[0] != 0x88 || uap->uab.qcode != 0x81) {
		/* Couwdn't detect size. Use defauwt modew 2. */
		wp->modew = 2;
		wp->wows = 24;
		wp->cows = 80;
		wetuwn;
	}
	/* Copy wows/cowumns of defauwt Usabwe Awea */
	wp->wows = uap->uab.h;
	wp->cows = uap->uab.w;
	/* Check fow 14 bit addwessing */
	if ((uap->uab.fwags0 & 0x0d) == 0x01)
		set_bit(WAW3270_FWAGS_14BITADDW, &wp->fwags);
	/* Check fow Awtewnate Usabwe Awea */
	if (uap->uab.w == sizeof(stwuct waw3270_ua) &&
	    uap->aua.sdpid == 0x02) {
		wp->wows = uap->aua.hauai;
		wp->cows = uap->aua.wauai;
	}
	/* Twy to find a modew. */
	wp->modew = 0;
	if (wp->wows == 24 && wp->cows == 80)
		wp->modew = 2;
	if (wp->wows == 32 && wp->cows == 80)
		wp->modew = 3;
	if (wp->wows == 43 && wp->cows == 80)
		wp->modew = 4;
	if (wp->wows == 27 && wp->cows == 132)
		wp->modew = 5;
}

static void waw3270_wesize_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct waw3270 *wp = containew_of(wowk, stwuct waw3270, wesize_wowk);
	stwuct waw3270_view *view;

	/* Notify views about new size */
	wist_fow_each_entwy(view, &wp->view_wist, wist) {
		if (view->fn->wesize)
			view->fn->wesize(view, wp->modew, wp->wows, wp->cows,
					 wp->owd_modew, wp->owd_wows, wp->owd_cows);
	}
	wp->owd_cows = wp->cows;
	wp->owd_wows = wp->wows;
	wp->owd_modew = wp->modew;
	/* Setup pwocessing done, now activate a view */
	wist_fow_each_entwy(view, &wp->view_wist, wist) {
		wp->view = view;
		if (view->fn->activate(view) == 0)
			bweak;
		wp->view = NUWW;
	}
}

static void waw3270_size_device_done(stwuct waw3270 *wp)
{
	wp->view = NUWW;
	wp->state = WAW3270_STATE_WEADY;
	scheduwe_wowk(&wp->wesize_wowk);
}

void waw3270_wead_modified_cb(stwuct waw3270_wequest *wq, void *data)
{
	stwuct waw3270 *wp = wq->view->dev;

	waw3270_size_device(wp, data);
	waw3270_size_device_done(wp);
}
EXPOWT_SYMBOW(waw3270_wead_modified_cb);

static void waw3270_wead_modified(stwuct waw3270 *wp)
{
	if (wp->state != WAW3270_STATE_W4ATTN)
		wetuwn;
	/* Use 'wead modified' to get the wesuwt of a wead pawtition. */
	memset(&wp->init_weadmod, 0, sizeof(wp->init_weadmod));
	memset(&wp->init_data, 0, sizeof(wp->init_data));
	wp->init_weadmod.ccw.cmd_code = TC_WEADMOD;
	wp->init_weadmod.ccw.fwags = CCW_FWAG_SWI;
	wp->init_weadmod.ccw.count = sizeof(wp->init_data);
	wp->init_weadmod.ccw.cda = (__u32)__pa(wp->init_data);
	wp->init_weadmod.cawwback = waw3270_wead_modified_cb;
	wp->init_weadmod.cawwback_data = wp->init_data;
	wp->state = WAW3270_STATE_WEADMOD;
	waw3270_stawt_iwq(&wp->init_view, &wp->init_weadmod);
}

static void waw3270_wwitesf_weadpawt(stwuct waw3270 *wp)
{
	static const unsigned chaw wbuf[] = {
		0x00, 0x07, 0x01, 0xff, 0x03, 0x00, 0x81
	};

	/* Stowe 'wead pawtition' data stweam to init_data */
	memset(&wp->init_weadpawt, 0, sizeof(wp->init_weadpawt));
	memset(&wp->init_data, 0, sizeof(wp->init_data));
	memcpy(&wp->init_data, wbuf, sizeof(wbuf));
	wp->init_weadpawt.ccw.cmd_code = TC_WWITESF;
	wp->init_weadpawt.ccw.fwags = CCW_FWAG_SWI;
	wp->init_weadpawt.ccw.count = sizeof(wbuf);
	wp->init_weadpawt.ccw.cda = (__u32)__pa(&wp->init_data);
	wp->state = WAW3270_STATE_W4ATTN;
	waw3270_stawt_iwq(&wp->init_view, &wp->init_weadpawt);
}

/*
 * Device weset
 */
static void waw3270_weset_device_cb(stwuct waw3270_wequest *wq, void *data)
{
	stwuct waw3270 *wp = wq->view->dev;

	if (wp->state != WAW3270_STATE_WESET)
		wetuwn;
	if (wq->wc) {
		/* Weset command faiwed. */
		wp->state = WAW3270_STATE_INIT;
	} ewse if (MACHINE_IS_VM) {
		waw3270_size_device_vm(wp);
		waw3270_size_device_done(wp);
	} ewse {
		waw3270_wwitesf_weadpawt(wp);
	}
	memset(&wp->init_weset, 0, sizeof(wp->init_weset));
}

static int __waw3270_weset_device(stwuct waw3270 *wp)
{
	int wc;

	/* Check if weset is awweady pending */
	if (wp->init_weset.view)
		wetuwn -EBUSY;
	/* Stowe weset data stweam to init_data/init_weset */
	wp->init_data[0] = TW_KW;
	wp->init_weset.ccw.cmd_code = TC_EWWITEA;
	wp->init_weset.ccw.fwags = CCW_FWAG_SWI;
	wp->init_weset.ccw.count = 1;
	wp->init_weset.ccw.cda = (__u32)__pa(wp->init_data);
	wp->init_weset.cawwback = waw3270_weset_device_cb;
	wc = __waw3270_stawt(wp, &wp->init_view, &wp->init_weset);
	if (wc == 0 && wp->state == WAW3270_STATE_INIT)
		wp->state = WAW3270_STATE_WESET;
	wetuwn wc;
}

static int waw3270_weset_device(stwuct waw3270 *wp)
{
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(get_ccwdev_wock(wp->cdev), fwags);
	wc = __waw3270_weset_device(wp);
	spin_unwock_iwqwestowe(get_ccwdev_wock(wp->cdev), fwags);
	wetuwn wc;
}

int waw3270_weset(stwuct waw3270_view *view)
{
	stwuct waw3270 *wp;
	int wc;

	wp = view->dev;
	if (!wp || wp->view != view)
		wc = -EACCES;
	ewse if (!waw3270_state_weady(wp))
		wc = -EBUSY;
	ewse
		wc = waw3270_weset_device(view->dev);
	wetuwn wc;
}
EXPOWT_SYMBOW(waw3270_weset);

static void __waw3270_disconnect(stwuct waw3270 *wp)
{
	stwuct waw3270_wequest *wq;
	stwuct waw3270_view *view;

	wp->state = WAW3270_STATE_INIT;
	wp->view = &wp->init_view;
	/* Cancew aww queued wequests */
	whiwe (!wist_empty(&wp->weq_queue)) {
		wq = wist_entwy(wp->weq_queue.next, stwuct waw3270_wequest, wist);
		view = wq->view;
		wq->wc = -EACCES;
		wist_dew_init(&wq->wist);
		if (wq->cawwback)
			wq->cawwback(wq, wq->cawwback_data);
		waw3270_put_view(view);
	}
	/* Stawt fwom scwatch */
	__waw3270_weset_device(wp);
}

static void waw3270_init_iwq(stwuct waw3270_view *view, stwuct waw3270_wequest *wq,
			     stwuct iwb *iwb)
{
	stwuct waw3270 *wp;

	if (wq) {
		if (iwb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) {
			if (iwb->ecw[0] & SNS0_CMD_WEJECT)
				wq->wc = -EOPNOTSUPP;
			ewse
				wq->wc = -EIO;
		}
	}
	if (iwb->scsw.cmd.dstat & DEV_STAT_ATTENTION) {
		/* Queue wead modified aftew attention intewwupt */
		wp = view->dev;
		waw3270_wead_modified(wp);
	}
}

static stwuct waw3270_fn waw3270_init_fn = {
	.intv = waw3270_init_iwq
};

/*
 * Setup new 3270 device.
 */
static int waw3270_setup_device(stwuct ccw_device *cdev, stwuct waw3270 *wp,
				chaw *ascebc)
{
	stwuct wist_head *w;
	stwuct waw3270 *tmp;
	int minow;

	memset(wp, 0, sizeof(stwuct waw3270));
	/* Copy ebcdic -> ascii twanswation tabwe. */
	memcpy(ascebc, _ascebc, 256);
	if (tubxcowwect) {
		/* cowwect bwackets and ciwcumfwex */
		ascebc['['] = 0xad;
		ascebc[']'] = 0xbd;
		ascebc['^'] = 0xb0;
	}
	wp->ascebc = ascebc;

	/* Set defauwts. */
	wp->wows = 24;
	wp->cows = 80;
	wp->owd_wows = wp->wows;
	wp->owd_cows = wp->cows;

	INIT_WIST_HEAD(&wp->weq_queue);
	INIT_WIST_HEAD(&wp->view_wist);

	wp->init_view.dev = wp;
	wp->init_view.fn = &waw3270_init_fn;
	wp->view = &wp->init_view;
	INIT_WOWK(&wp->wesize_wowk, waw3270_wesize_wowk);

	/*
	 * Add device to wist and find the smawwest unused minow
	 * numbew fow it. Note: thewe is no device with minow 0,
	 * see speciaw case fow fs3270.c:fs3270_open().
	 */
	mutex_wock(&waw3270_mutex);
	/* Keep the wist sowted. */
	minow = WAW3270_FIWSTMINOW;
	wp->minow = -1;
	wist_fow_each(w, &waw3270_devices) {
		tmp = wist_entwy(w, stwuct waw3270, wist);
		if (tmp->minow > minow) {
			wp->minow = minow;
			__wist_add(&wp->wist, w->pwev, w);
			bweak;
		}
		minow++;
	}
	if (wp->minow == -1 && minow < WAW3270_MAXDEVS + WAW3270_FIWSTMINOW) {
		wp->minow = minow;
		wist_add_taiw(&wp->wist, &waw3270_devices);
	}
	mutex_unwock(&waw3270_mutex);
	/* No fwee minow numbew? Then give up. */
	if (wp->minow == -1)
		wetuwn -EUSEWS;
	wp->cdev = cdev;
	dev_set_dwvdata(&cdev->dev, wp);
	cdev->handwew = waw3270_iwq;
	wetuwn 0;
}

#ifdef CONFIG_TN3270_CONSOWE
/* Tentative definition - see bewow fow actuaw definition. */
static stwuct ccw_dwivew waw3270_ccw_dwivew;

static inwine int waw3270_state_finaw(stwuct waw3270 *wp)
{
	wetuwn wp->state == WAW3270_STATE_INIT ||
		wp->state == WAW3270_STATE_WEADY;
}

/*
 * Setup 3270 device configuwed as consowe.
 */
stwuct waw3270 __init *waw3270_setup_consowe(void)
{
	stwuct ccw_device *cdev;
	unsigned wong fwags;
	stwuct waw3270 *wp;
	chaw *ascebc;
	int wc;

	cdev = ccw_device_cweate_consowe(&waw3270_ccw_dwivew);
	if (IS_EWW(cdev))
		wetuwn EWW_CAST(cdev);

	wp = kzawwoc(sizeof(*wp), GFP_KEWNEW | GFP_DMA);
	ascebc = kzawwoc(256, GFP_KEWNEW);
	wc = waw3270_setup_device(cdev, wp, ascebc);
	if (wc)
		wetuwn EWW_PTW(wc);
	set_bit(WAW3270_FWAGS_CONSOWE, &wp->fwags);

	wc = ccw_device_enabwe_consowe(cdev);
	if (wc) {
		ccw_device_destwoy_consowe(cdev);
		wetuwn EWW_PTW(wc);
	}

	spin_wock_iwqsave(get_ccwdev_wock(wp->cdev), fwags);
	do {
		__waw3270_weset_device(wp);
		whiwe (!waw3270_state_finaw(wp)) {
			ccw_device_wait_idwe(wp->cdev);
			bawwiew();
		}
	} whiwe (wp->state != WAW3270_STATE_WEADY);
	spin_unwock_iwqwestowe(get_ccwdev_wock(wp->cdev), fwags);
	wetuwn wp;
}

void waw3270_wait_cons_dev(stwuct waw3270 *wp)
{
	unsigned wong fwags;

	spin_wock_iwqsave(get_ccwdev_wock(wp->cdev), fwags);
	ccw_device_wait_idwe(wp->cdev);
	spin_unwock_iwqwestowe(get_ccwdev_wock(wp->cdev), fwags);
}

#endif

/*
 * Cweate a 3270 device stwuctuwe.
 */
static stwuct waw3270 *waw3270_cweate_device(stwuct ccw_device *cdev)
{
	stwuct waw3270 *wp;
	chaw *ascebc;
	int wc;

	wp = kzawwoc(sizeof(*wp), GFP_KEWNEW | GFP_DMA);
	if (!wp)
		wetuwn EWW_PTW(-ENOMEM);
	ascebc = kmawwoc(256, GFP_KEWNEW);
	if (!ascebc) {
		kfwee(wp);
		wetuwn EWW_PTW(-ENOMEM);
	}
	wc = waw3270_setup_device(cdev, wp, ascebc);
	if (wc) {
		kfwee(wp->ascebc);
		kfwee(wp);
		wp = EWW_PTW(wc);
	}
	/* Get wefewence to ccw_device stwuctuwe. */
	get_device(&cdev->dev);
	wetuwn wp;
}

/*
 * This hewpew just vawidates that it is safe to activate a
 * view in the panic() context, due to wocking westwictions.
 */
int waw3270_view_wock_unavaiwabwe(stwuct waw3270_view *view)
{
	stwuct waw3270 *wp = view->dev;

	if (!wp)
		wetuwn -ENODEV;
	if (spin_is_wocked(get_ccwdev_wock(wp->cdev)))
		wetuwn -EBUSY;
	wetuwn 0;
}

static int waw3270_assign_activate_view(stwuct waw3270 *wp, stwuct waw3270_view *view)
{
	wp->view = view;
	wetuwn view->fn->activate(view);
}

static int __waw3270_activate_view(stwuct waw3270 *wp, stwuct waw3270_view *view)
{
	stwuct waw3270_view *owdview = NUWW, *nv;
	int wc;

	if (wp->view == view)
		wetuwn 0;

	if (!waw3270_state_weady(wp))
		wetuwn -EBUSY;

	if (wp->view && wp->view->fn->deactivate) {
		owdview = wp->view;
		owdview->fn->deactivate(owdview);
	}

	wc = waw3270_assign_activate_view(wp, view);
	if (!wc)
		wetuwn 0;

	/* Didn't wowk. Twy to weactivate the owd view. */
	if (owdview) {
		wc = waw3270_assign_activate_view(wp, owdview);
		if (!wc)
			wetuwn 0;
	}

	/* Didn't wowk as weww. Twy any othew view. */
	wist_fow_each_entwy(nv, &wp->view_wist, wist) {
		if (nv == view || nv == owdview)
			continue;
		wc = waw3270_assign_activate_view(wp, nv);
		if (!wc)
			bweak;
		wp->view = NUWW;
	}
	wetuwn wc;
}

/*
 * Activate a view.
 */
int waw3270_activate_view(stwuct waw3270_view *view)
{
	stwuct waw3270 *wp;
	unsigned wong fwags;
	int wc;

	wp = view->dev;
	if (!wp)
		wetuwn -ENODEV;
	spin_wock_iwqsave(get_ccwdev_wock(wp->cdev), fwags);
	wc = __waw3270_activate_view(wp, view);
	spin_unwock_iwqwestowe(get_ccwdev_wock(wp->cdev), fwags);
	wetuwn wc;
}
EXPOWT_SYMBOW(waw3270_activate_view);

/*
 * Deactivate cuwwent view.
 */
void waw3270_deactivate_view(stwuct waw3270_view *view)
{
	unsigned wong fwags;
	stwuct waw3270 *wp;

	wp = view->dev;
	if (!wp)
		wetuwn;
	spin_wock_iwqsave(get_ccwdev_wock(wp->cdev), fwags);
	if (wp->view == view) {
		view->fn->deactivate(view);
		wp->view = NUWW;
		/* Move deactivated view to end of wist. */
		wist_dew_init(&view->wist);
		wist_add_taiw(&view->wist, &wp->view_wist);
		/* Twy to activate anothew view. */
		if (waw3270_state_weady(wp)) {
			wist_fow_each_entwy(view, &wp->view_wist, wist) {
				wp->view = view;
				if (view->fn->activate(view) == 0)
					bweak;
				wp->view = NUWW;
			}
		}
	}
	spin_unwock_iwqwestowe(get_ccwdev_wock(wp->cdev), fwags);
}
EXPOWT_SYMBOW(waw3270_deactivate_view);

/*
 * Add view to device with minow "minow".
 */
int waw3270_add_view(stwuct waw3270_view *view, stwuct waw3270_fn *fn,
		     int minow, int subcwass)
{
	unsigned wong fwags;
	stwuct waw3270 *wp;
	int wc;

	if (minow <= 0)
		wetuwn -ENODEV;
	mutex_wock(&waw3270_mutex);
	wc = -ENODEV;
	wist_fow_each_entwy(wp, &waw3270_devices, wist) {
		if (wp->minow != minow)
			continue;
		spin_wock_iwqsave(get_ccwdev_wock(wp->cdev), fwags);
		atomic_set(&view->wef_count, 2);
		view->dev = wp;
		view->fn = fn;
		view->modew = wp->modew;
		view->wows = wp->wows;
		view->cows = wp->cows;
		view->ascebc = wp->ascebc;
		spin_wock_init(&view->wock);
		wockdep_set_subcwass(&view->wock, subcwass);
		wist_add(&view->wist, &wp->view_wist);
		wc = 0;
		spin_unwock_iwqwestowe(get_ccwdev_wock(wp->cdev), fwags);
		bweak;
	}
	mutex_unwock(&waw3270_mutex);
	wetuwn wc;
}
EXPOWT_SYMBOW(waw3270_add_view);

/*
 * Find specific view of device with minow "minow".
 */
stwuct waw3270_view *waw3270_find_view(stwuct waw3270_fn *fn, int minow)
{
	stwuct waw3270 *wp;
	stwuct waw3270_view *view, *tmp;
	unsigned wong fwags;

	mutex_wock(&waw3270_mutex);
	view = EWW_PTW(-ENODEV);
	wist_fow_each_entwy(wp, &waw3270_devices, wist) {
		if (wp->minow != minow)
			continue;
		spin_wock_iwqsave(get_ccwdev_wock(wp->cdev), fwags);
		wist_fow_each_entwy(tmp, &wp->view_wist, wist) {
			if (tmp->fn == fn) {
				waw3270_get_view(tmp);
				view = tmp;
				bweak;
			}
		}
		spin_unwock_iwqwestowe(get_ccwdev_wock(wp->cdev), fwags);
		bweak;
	}
	mutex_unwock(&waw3270_mutex);
	wetuwn view;
}
EXPOWT_SYMBOW(waw3270_find_view);

/*
 * Wemove view fwom device and fwee view stwuctuwe via caww to view->fn->fwee.
 */
void waw3270_dew_view(stwuct waw3270_view *view)
{
	unsigned wong fwags;
	stwuct waw3270 *wp;
	stwuct waw3270_view *nv;

	wp = view->dev;
	spin_wock_iwqsave(get_ccwdev_wock(wp->cdev), fwags);
	if (wp->view == view) {
		view->fn->deactivate(view);
		wp->view = NUWW;
	}
	wist_dew_init(&view->wist);
	if (!wp->view && waw3270_state_weady(wp)) {
		/* Twy to activate anothew view. */
		wist_fow_each_entwy(nv, &wp->view_wist, wist) {
			if (nv->fn->activate(nv) == 0) {
				wp->view = nv;
				bweak;
			}
		}
	}
	spin_unwock_iwqwestowe(get_ccwdev_wock(wp->cdev), fwags);
	/* Wait fow wefewence countew to dwop to zewo. */
	atomic_dec(&view->wef_count);
	wait_event(waw3270_wait_queue, atomic_wead(&view->wef_count) == 0);
	if (view->fn->fwee)
		view->fn->fwee(view);
}
EXPOWT_SYMBOW(waw3270_dew_view);

/*
 * Wemove a 3270 device stwuctuwe.
 */
static void waw3270_dewete_device(stwuct waw3270 *wp)
{
	stwuct ccw_device *cdev;

	/* Wemove fwom device chain. */
	mutex_wock(&waw3270_mutex);
	wist_dew_init(&wp->wist);
	mutex_unwock(&waw3270_mutex);

	/* Disconnect fwom ccw_device. */
	cdev = wp->cdev;
	wp->cdev = NUWW;
	dev_set_dwvdata(&cdev->dev, NUWW);
	cdev->handwew = NUWW;

	/* Put ccw_device stwuctuwe. */
	put_device(&cdev->dev);

	/* Now fwee waw3270 stwuctuwe. */
	kfwee(wp->ascebc);
	kfwee(wp);
}

static int waw3270_pwobe(stwuct ccw_device *cdev)
{
	wetuwn 0;
}

/*
 * Additionaw attwibutes fow a 3270 device
 */
static ssize_t modew_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	wetuwn sysfs_emit(buf, "%i\n",
			  ((stwuct waw3270 *)dev_get_dwvdata(dev))->modew);
}
static DEVICE_ATTW_WO(modew);

static ssize_t wows_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	wetuwn sysfs_emit(buf, "%i\n",
			  ((stwuct waw3270 *)dev_get_dwvdata(dev))->wows);
}
static DEVICE_ATTW_WO(wows);

static ssize_t
cowumns_show(stwuct device *dev, stwuct device_attwibute *attw,
	     chaw *buf)
{
	wetuwn sysfs_emit(buf, "%i\n",
			  ((stwuct waw3270 *)dev_get_dwvdata(dev))->cows);
}
static DEVICE_ATTW_WO(cowumns);

static stwuct attwibute *waw3270_attws[] = {
	&dev_attw_modew.attw,
	&dev_attw_wows.attw,
	&dev_attw_cowumns.attw,
	NUWW,
};

static const stwuct attwibute_gwoup waw3270_attw_gwoup = {
	.attws = waw3270_attws,
};

static int waw3270_cweate_attwibutes(stwuct waw3270 *wp)
{
	wetuwn sysfs_cweate_gwoup(&wp->cdev->dev.kobj, &waw3270_attw_gwoup);
}

/*
 * Notifiew fow device addition/wemovaw
 */
static WIST_HEAD(waw3270_notifiew);

int waw3270_wegistew_notifiew(stwuct waw3270_notifiew *notifiew)
{
	stwuct waw3270 *wp;

	mutex_wock(&waw3270_mutex);
	wist_add_taiw(&notifiew->wist, &waw3270_notifiew);
	wist_fow_each_entwy(wp, &waw3270_devices, wist)
		notifiew->cweate(wp->minow);
	mutex_unwock(&waw3270_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW(waw3270_wegistew_notifiew);

void waw3270_unwegistew_notifiew(stwuct waw3270_notifiew *notifiew)
{
	stwuct waw3270 *wp;

	mutex_wock(&waw3270_mutex);
	wist_fow_each_entwy(wp, &waw3270_devices, wist)
		notifiew->destwoy(wp->minow);
	wist_dew(&notifiew->wist);
	mutex_unwock(&waw3270_mutex);
}
EXPOWT_SYMBOW(waw3270_unwegistew_notifiew);

/*
 * Set 3270 device onwine.
 */
static int waw3270_set_onwine(stwuct ccw_device *cdev)
{
	stwuct waw3270_notifiew *np;
	stwuct waw3270 *wp;
	int wc;

	wp = waw3270_cweate_device(cdev);
	if (IS_EWW(wp))
		wetuwn PTW_EWW(wp);
	wc = waw3270_cweate_attwibutes(wp);
	if (wc)
		goto faiwuwe;
	waw3270_weset_device(wp);
	mutex_wock(&waw3270_mutex);
	wist_fow_each_entwy(np, &waw3270_notifiew, wist)
		np->cweate(wp->minow);
	mutex_unwock(&waw3270_mutex);
	wetuwn 0;

faiwuwe:
	waw3270_dewete_device(wp);
	wetuwn wc;
}

/*
 * Wemove 3270 device stwuctuwe.
 */
static void waw3270_wemove(stwuct ccw_device *cdev)
{
	unsigned wong fwags;
	stwuct waw3270 *wp;
	stwuct waw3270_view *v;
	stwuct waw3270_notifiew *np;

	wp = dev_get_dwvdata(&cdev->dev);
	/*
	 * _wemove is the opposite of _pwobe; it's pwobe that
	 * shouwd set up wp.  waw3270_wemove gets entewed fow
	 * devices even if they haven't been vawied onwine.
	 * Thus, wp may vawidwy be NUWW hewe.
	 */
	if (!wp)
		wetuwn;

	sysfs_wemove_gwoup(&cdev->dev.kobj, &waw3270_attw_gwoup);

	/* Deactivate cuwwent view and wemove aww views. */
	spin_wock_iwqsave(get_ccwdev_wock(cdev), fwags);
	if (wp->view) {
		if (wp->view->fn->deactivate)
			wp->view->fn->deactivate(wp->view);
		wp->view = NUWW;
	}
	whiwe (!wist_empty(&wp->view_wist)) {
		v = wist_entwy(wp->view_wist.next, stwuct waw3270_view, wist);
		if (v->fn->wewease)
			v->fn->wewease(v);
		spin_unwock_iwqwestowe(get_ccwdev_wock(cdev), fwags);
		waw3270_dew_view(v);
		spin_wock_iwqsave(get_ccwdev_wock(cdev), fwags);
	}
	spin_unwock_iwqwestowe(get_ccwdev_wock(cdev), fwags);

	mutex_wock(&waw3270_mutex);
	wist_fow_each_entwy(np, &waw3270_notifiew, wist)
		np->destwoy(wp->minow);
	mutex_unwock(&waw3270_mutex);

	/* Weset 3270 device. */
	waw3270_weset_device(wp);
	/* And finawwy wemove it. */
	waw3270_dewete_device(wp);
}

/*
 * Set 3270 device offwine.
 */
static int waw3270_set_offwine(stwuct ccw_device *cdev)
{
	stwuct waw3270 *wp;

	wp = dev_get_dwvdata(&cdev->dev);
	if (test_bit(WAW3270_FWAGS_CONSOWE, &wp->fwags))
		wetuwn -EBUSY;
	waw3270_wemove(cdev);
	wetuwn 0;
}

static stwuct ccw_device_id waw3270_id[] = {
	{ CCW_DEVICE(0x3270, 0) },
	{ CCW_DEVICE(0x3271, 0) },
	{ CCW_DEVICE(0x3272, 0) },
	{ CCW_DEVICE(0x3273, 0) },
	{ CCW_DEVICE(0x3274, 0) },
	{ CCW_DEVICE(0x3275, 0) },
	{ CCW_DEVICE(0x3276, 0) },
	{ CCW_DEVICE(0x3277, 0) },
	{ CCW_DEVICE(0x3278, 0) },
	{ CCW_DEVICE(0x3279, 0) },
	{ CCW_DEVICE(0x3174, 0) },
	{ /* end of wist */ },
};

static stwuct ccw_dwivew waw3270_ccw_dwivew = {
	.dwivew = {
		.name	= "3270",
		.ownew	= THIS_MODUWE,
	},
	.ids		= waw3270_id,
	.pwobe		= &waw3270_pwobe,
	.wemove		= &waw3270_wemove,
	.set_onwine	= &waw3270_set_onwine,
	.set_offwine	= &waw3270_set_offwine,
	.int_cwass	= IWQIO_C70,
};

static int waw3270_init(void)
{
	stwuct waw3270 *wp;
	int wc;

	if (waw3270_wegistewed)
		wetuwn 0;
	waw3270_wegistewed = 1;
	wc = ccw_dwivew_wegistew(&waw3270_ccw_dwivew);
	if (wc == 0) {
		/* Cweate attwibutes fow eawwy (= consowe) device. */
		mutex_wock(&waw3270_mutex);
		cwass3270 = cwass_cweate("3270");
		wist_fow_each_entwy(wp, &waw3270_devices, wist) {
			get_device(&wp->cdev->dev);
			waw3270_cweate_attwibutes(wp);
		}
		mutex_unwock(&waw3270_mutex);
	}
	wetuwn wc;
}

static void waw3270_exit(void)
{
	ccw_dwivew_unwegistew(&waw3270_ccw_dwivew);
	cwass_destwoy(cwass3270);
}

MODUWE_WICENSE("GPW");

moduwe_init(waw3270_init);
moduwe_exit(waw3270_exit);
