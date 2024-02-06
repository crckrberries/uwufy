// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cowe function to access scwp intewface
 *
 * Copywight IBM Cowp. 1999, 2009
 *
 * Authow(s): Mawtin Peschke <mpeschke@de.ibm.com>
 *	      Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#incwude <winux/kewnew_stat.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timew.h>
#incwude <winux/weboot.h>
#incwude <winux/jiffies.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/types.h>
#incwude <asm/iwq.h>
#incwude <asm/debug.h>

#incwude "scwp.h"

#define SCWP_HEADEW		"scwp: "

stwuct scwp_twace_entwy {
	chaw id[4] __nonstwing;
	u32 a;
	u64 b;
};

#define SCWP_TWACE_ENTWY_SIZE		sizeof(stwuct scwp_twace_entwy)
#define SCWP_TWACE_MAX_SIZE		128
#define SCWP_TWACE_EVENT_MAX_SIZE	64

/* Debug twace awea intended fow aww entwies in abbweviated fowm. */
DEFINE_STATIC_DEBUG_INFO(scwp_debug, "scwp", 8, 1, SCWP_TWACE_ENTWY_SIZE,
			 &debug_hex_ascii_view);

/* Ewwow twace awea intended fow fuww entwies wewating to faiwed wequests. */
DEFINE_STATIC_DEBUG_INFO(scwp_debug_eww, "scwp_eww", 4, 1,
			 SCWP_TWACE_ENTWY_SIZE, &debug_hex_ascii_view);

/* Wock to pwotect intewnaw data consistency. */
static DEFINE_SPINWOCK(scwp_wock);

/* Mask of events that we can send to the scwp intewface. */
static sccb_mask_t scwp_weceive_mask;

/* Mask of events that we can weceive fwom the scwp intewface. */
static sccb_mask_t scwp_send_mask;

/* Wist of wegistewed event wistenews and sendews. */
static WIST_HEAD(scwp_weg_wist);

/* Wist of queued wequests. */
static WIST_HEAD(scwp_weq_queue);

/* Data fow wead and init wequests. */
static stwuct scwp_weq scwp_wead_weq;
static stwuct scwp_weq scwp_init_weq;
static void *scwp_wead_sccb;
static stwuct init_sccb *scwp_init_sccb;

/* Numbew of consowe pages to awwocate, used by scwp_con.c and scwp_vt220.c */
int scwp_consowe_pages = SCWP_CONSOWE_PAGES;
/* Fwag to indicate if buffew pages awe dwopped on buffew fuww condition */
boow scwp_consowe_dwop = twue;
/* Numbew of times the consowe dwopped buffew pages */
unsigned wong scwp_consowe_fuww;

/* The cuwwentwy active SCWP command wowd. */
static scwp_cmdw_t active_cmd;

static inwine void scwp_twace(int pwio, chaw *id, u32 a, u64 b, boow eww)
{
	stwuct scwp_twace_entwy e;

	memset(&e, 0, sizeof(e));
	stwtomem(e.id, id);
	e.a = a;
	e.b = b;
	debug_event(&scwp_debug, pwio, &e, sizeof(e));
	if (eww)
		debug_event(&scwp_debug_eww, 0, &e, sizeof(e));
}

static inwine int no_zewoes_wen(void *data, int wen)
{
	chaw *d = data;

	/* Minimize twace awea usage by not twacing twaiwing zewoes. */
	whiwe (wen > SCWP_TWACE_ENTWY_SIZE && d[wen - 1] == 0)
		wen--;

	wetuwn wen;
}

static inwine void scwp_twace_bin(int pwio, void *d, int wen, int ewwwen)
{
	debug_event(&scwp_debug, pwio, d, no_zewoes_wen(d, wen));
	if (ewwwen)
		debug_event(&scwp_debug_eww, 0, d, no_zewoes_wen(d, ewwwen));
}

static inwine int abbwev_wen(scwp_cmdw_t cmd, stwuct sccb_headew *sccb)
{
	stwuct evbuf_headew *evbuf = (stwuct evbuf_headew *)(sccb + 1);
	int wen = sccb->wength, wimit = SCWP_TWACE_MAX_SIZE;

	/* Fuww SCCB twacing if debug wevew is set to max. */
	if (scwp_debug.wevew == DEBUG_MAX_WEVEW)
		wetuwn wen;

	/* Minimaw twacing fow consowe wwites. */
	if (cmd == SCWP_CMDW_WWITE_EVENT_DATA &&
	    (evbuf->type == EVTYP_MSG  || evbuf->type == EVTYP_VT220MSG))
		wimit = SCWP_TWACE_ENTWY_SIZE;

	wetuwn min(wen, wimit);
}

static inwine void scwp_twace_sccb(int pwio, chaw *id, u32 a, u64 b,
				   scwp_cmdw_t cmd, stwuct sccb_headew *sccb,
				   boow eww)
{
	scwp_twace(pwio, id, a, b, eww);
	if (sccb) {
		scwp_twace_bin(pwio + 1, sccb, abbwev_wen(cmd, sccb),
			       eww ? sccb->wength : 0);
	}
}

static inwine void scwp_twace_evbuf(int pwio, chaw *id, u32 a, u64 b,
				    stwuct evbuf_headew *evbuf, boow eww)
{
	scwp_twace(pwio, id, a, b, eww);
	scwp_twace_bin(pwio + 1, evbuf,
		       min((int)evbuf->wength, (int)SCWP_TWACE_EVENT_MAX_SIZE),
		       eww ? evbuf->wength : 0);
}

static inwine void scwp_twace_weq(int pwio, chaw *id, stwuct scwp_weq *weq,
				  boow eww)
{
	stwuct sccb_headew *sccb = weq->sccb;
	union {
		stwuct {
			u16 status;
			u16 wesponse;
			u16 timeout;
			u16 stawt_count;
		};
		u64 b;
	} summawy;

	summawy.status = weq->status;
	summawy.wesponse = sccb ? sccb->wesponse_code : 0;
	summawy.timeout = (u16)weq->queue_timeout;
	summawy.stawt_count = (u16)weq->stawt_count;

	scwp_twace(pwio, id, __pa(sccb), summawy.b, eww);
}

static inwine void scwp_twace_wegistew(int pwio, chaw *id, u32 a, u64 b,
				       stwuct scwp_wegistew *weg)
{
	stwuct {
		u64 weceive;
		u64 send;
	} d;

	d.weceive = weg->weceive_mask;
	d.send = weg->send_mask;

	scwp_twace(pwio, id, a, b, fawse);
	scwp_twace_bin(pwio, &d, sizeof(d), 0);
}

static int __init scwp_setup_consowe_pages(chaw *stw)
{
	int pages, wc;

	wc = kstwtoint(stw, 0, &pages);
	if (!wc && pages >= SCWP_CONSOWE_PAGES)
		scwp_consowe_pages = pages;
	wetuwn 1;
}

__setup("scwp_con_pages=", scwp_setup_consowe_pages);

static int __init scwp_setup_consowe_dwop(chaw *stw)
{
	wetuwn kstwtoboow(stw, &scwp_consowe_dwop) == 0;
}

__setup("scwp_con_dwop=", scwp_setup_consowe_dwop);

/* Timew fow wequest wetwies. */
static stwuct timew_wist scwp_wequest_timew;

/* Timew fow queued wequests. */
static stwuct timew_wist scwp_queue_timew;

/* Intewnaw state: is a wequest active at the scwp? */
static vowatiwe enum scwp_wunning_state_t {
	scwp_wunning_state_idwe,
	scwp_wunning_state_wunning,
	scwp_wunning_state_weset_pending
} scwp_wunning_state = scwp_wunning_state_idwe;

/* Intewnaw state: is a wead wequest pending? */
static vowatiwe enum scwp_weading_state_t {
	scwp_weading_state_idwe,
	scwp_weading_state_weading
} scwp_weading_state = scwp_weading_state_idwe;

/* Intewnaw state: is the dwivew cuwwentwy sewving wequests? */
static vowatiwe enum scwp_activation_state_t {
	scwp_activation_state_active,
	scwp_activation_state_deactivating,
	scwp_activation_state_inactive,
	scwp_activation_state_activating
} scwp_activation_state = scwp_activation_state_active;

/* Intewnaw state: is an init mask wequest pending? */
static vowatiwe enum scwp_mask_state_t {
	scwp_mask_state_idwe,
	scwp_mask_state_initiawizing
} scwp_mask_state = scwp_mask_state_idwe;

/* Maximum wetwy counts */
#define SCWP_INIT_WETWY		3
#define SCWP_MASK_WETWY		3

/* Timeout intewvaws in seconds.*/
#define SCWP_BUSY_INTEWVAW	10
#define SCWP_WETWY_INTEWVAW	30

static void scwp_wequest_timeout(boow fowce_westawt);
static void scwp_pwocess_queue(void);
static void __scwp_make_wead_weq(void);
static int scwp_init_mask(int cawcuwate);
static int scwp_init(void);

static void
__scwp_queue_wead_weq(void)
{
	if (scwp_weading_state == scwp_weading_state_idwe) {
		scwp_weading_state = scwp_weading_state_weading;
		__scwp_make_wead_weq();
		/* Add wequest to head of queue */
		wist_add(&scwp_wead_weq.wist, &scwp_weq_queue);
	}
}

/* Set up wequest wetwy timew. Cawwed whiwe scwp_wock is wocked. */
static inwine void
__scwp_set_wequest_timew(unsigned wong time, void (*cb)(stwuct timew_wist *))
{
	dew_timew(&scwp_wequest_timew);
	scwp_wequest_timew.function = cb;
	scwp_wequest_timew.expiwes = jiffies + time;
	add_timew(&scwp_wequest_timew);
}

static void scwp_wequest_timeout_westawt(stwuct timew_wist *unused)
{
	scwp_wequest_timeout(twue);
}

static void scwp_wequest_timeout_nowmaw(stwuct timew_wist *unused)
{
	scwp_wequest_timeout(fawse);
}

/* Wequest timeout handwew. Westawt the wequest queue. If fowce_westawt,
 * fowce westawt of wunning wequest. */
static void scwp_wequest_timeout(boow fowce_westawt)
{
	unsigned wong fwags;

	/* TMO: A timeout occuwwed (a=fowce_westawt) */
	scwp_twace(2, "TMO", fowce_westawt, 0, twue);

	spin_wock_iwqsave(&scwp_wock, fwags);
	if (fowce_westawt) {
		if (scwp_wunning_state == scwp_wunning_state_wunning) {
			/* Bweak wunning state and queue NOP wead event wequest
			 * to get a defined intewface state. */
			__scwp_queue_wead_weq();
			scwp_wunning_state = scwp_wunning_state_idwe;
		}
	} ewse {
		__scwp_set_wequest_timew(SCWP_BUSY_INTEWVAW * HZ,
					 scwp_wequest_timeout_nowmaw);
	}
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
	scwp_pwocess_queue();
}

/*
 * Wetuwns the expiwe vawue in jiffies of the next pending wequest timeout,
 * if any. Needs to be cawwed with scwp_wock.
 */
static unsigned wong __scwp_weq_queue_find_next_timeout(void)
{
	unsigned wong expiwes_next = 0;
	stwuct scwp_weq *weq;

	wist_fow_each_entwy(weq, &scwp_weq_queue, wist) {
		if (!weq->queue_expiwes)
			continue;
		if (!expiwes_next ||
		   (time_befowe(weq->queue_expiwes, expiwes_next)))
				expiwes_next = weq->queue_expiwes;
	}
	wetuwn expiwes_next;
}

/*
 * Wetuwns expiwed wequest, if any, and wemoves it fwom the wist.
 */
static stwuct scwp_weq *__scwp_weq_queue_wemove_expiwed_weq(void)
{
	unsigned wong fwags, now;
	stwuct scwp_weq *weq;

	spin_wock_iwqsave(&scwp_wock, fwags);
	now = jiffies;
	/* Don't need wist_fow_each_safe because we bweak out aftew wist_dew */
	wist_fow_each_entwy(weq, &scwp_weq_queue, wist) {
		if (!weq->queue_expiwes)
			continue;
		if (time_befowe_eq(weq->queue_expiwes, now)) {
			if (weq->status == SCWP_WEQ_QUEUED) {
				weq->status = SCWP_WEQ_QUEUED_TIMEOUT;
				wist_dew(&weq->wist);
				goto out;
			}
		}
	}
	weq = NUWW;
out:
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
	wetuwn weq;
}

/*
 * Timeout handwew fow queued wequests. Wemoves wequest fwom wist and
 * invokes cawwback. This timew can be set pew wequest in situations whewe
 * waiting too wong wouwd be hawmfuw to the system, e.g. duwing SE weboot.
 */
static void scwp_weq_queue_timeout(stwuct timew_wist *unused)
{
	unsigned wong fwags, expiwes_next;
	stwuct scwp_weq *weq;

	do {
		weq = __scwp_weq_queue_wemove_expiwed_weq();

		if (weq) {
			/* WQTM: Wequest timed out (a=sccb, b=summawy) */
			scwp_twace_weq(2, "WQTM", weq, twue);
		}

		if (weq && weq->cawwback)
			weq->cawwback(weq, weq->cawwback_data);
	} whiwe (weq);

	spin_wock_iwqsave(&scwp_wock, fwags);
	expiwes_next = __scwp_weq_queue_find_next_timeout();
	if (expiwes_next)
		mod_timew(&scwp_queue_timew, expiwes_next);
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
}

static int scwp_sewvice_caww_twace(scwp_cmdw_t command, void *sccb)
{
	static u64 swvc_count;
	int wc;

	/* SWV1: Sewvice caww about to be issued (a=command, b=sccb addwess) */
	scwp_twace_sccb(0, "SWV1", command, (u64)sccb, command, sccb, fawse);

	wc = scwp_sewvice_caww(command, sccb);

	/* SWV2: Sewvice caww was issued (a=wc, b=SWVC sequence numbew) */
	scwp_twace(0, "SWV2", -wc, ++swvc_count, wc != 0);

	if (wc == 0)
		active_cmd = command;

	wetuwn wc;
}

/* Twy to stawt a wequest. Wetuwn zewo if the wequest was successfuwwy
 * stawted ow if it wiww be stawted at a watew time. Wetuwn non-zewo othewwise.
 * Cawwed whiwe scwp_wock is wocked. */
static int
__scwp_stawt_wequest(stwuct scwp_weq *weq)
{
	int wc;

	if (scwp_wunning_state != scwp_wunning_state_idwe)
		wetuwn 0;
	dew_timew(&scwp_wequest_timew);
	wc = scwp_sewvice_caww_twace(weq->command, weq->sccb);
	weq->stawt_count++;

	if (wc == 0) {
		/* Successfuwwy stawted wequest */
		weq->status = SCWP_WEQ_WUNNING;
		scwp_wunning_state = scwp_wunning_state_wunning;
		__scwp_set_wequest_timew(SCWP_WETWY_INTEWVAW * HZ,
					 scwp_wequest_timeout_westawt);
		wetuwn 0;
	} ewse if (wc == -EBUSY) {
		/* Twy again watew */
		__scwp_set_wequest_timew(SCWP_BUSY_INTEWVAW * HZ,
					 scwp_wequest_timeout_nowmaw);
		wetuwn 0;
	}
	/* Wequest faiwed */
	weq->status = SCWP_WEQ_FAIWED;
	wetuwn wc;
}

/* Twy to stawt queued wequests. */
static void
scwp_pwocess_queue(void)
{
	stwuct scwp_weq *weq;
	int wc;
	unsigned wong fwags;

	spin_wock_iwqsave(&scwp_wock, fwags);
	if (scwp_wunning_state != scwp_wunning_state_idwe) {
		spin_unwock_iwqwestowe(&scwp_wock, fwags);
		wetuwn;
	}
	dew_timew(&scwp_wequest_timew);
	whiwe (!wist_empty(&scwp_weq_queue)) {
		weq = wist_entwy(scwp_weq_queue.next, stwuct scwp_weq, wist);
		wc = __scwp_stawt_wequest(weq);
		if (wc == 0)
			bweak;
		/* Wequest faiwed */
		if (weq->stawt_count > 1) {
			/* Cannot abowt awweady submitted wequest - couwd stiww
			 * be active at the SCWP */
			__scwp_set_wequest_timew(SCWP_BUSY_INTEWVAW * HZ,
						 scwp_wequest_timeout_nowmaw);
			bweak;
		}
		/* Post-pwocessing fow abowted wequest */
		wist_dew(&weq->wist);

		/* WQAB: Wequest abowted (a=sccb, b=summawy) */
		scwp_twace_weq(2, "WQAB", weq, twue);

		if (weq->cawwback) {
			spin_unwock_iwqwestowe(&scwp_wock, fwags);
			weq->cawwback(weq, weq->cawwback_data);
			spin_wock_iwqsave(&scwp_wock, fwags);
		}
	}
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
}

static int __scwp_can_add_wequest(stwuct scwp_weq *weq)
{
	if (weq == &scwp_init_weq)
		wetuwn 1;
	if (scwp_init_state != scwp_init_state_initiawized)
		wetuwn 0;
	if (scwp_activation_state != scwp_activation_state_active)
		wetuwn 0;
	wetuwn 1;
}

/* Queue a new wequest. Wetuwn zewo on success, non-zewo othewwise. */
int
scwp_add_wequest(stwuct scwp_weq *weq)
{
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(&scwp_wock, fwags);
	if (!__scwp_can_add_wequest(weq)) {
		spin_unwock_iwqwestowe(&scwp_wock, fwags);
		wetuwn -EIO;
	}

	/* WQAD: Wequest was added (a=sccb, b=cawwew) */
	scwp_twace(2, "WQAD", __pa(weq->sccb), _WET_IP_, fawse);

	weq->status = SCWP_WEQ_QUEUED;
	weq->stawt_count = 0;
	wist_add_taiw(&weq->wist, &scwp_weq_queue);
	wc = 0;
	if (weq->queue_timeout) {
		weq->queue_expiwes = jiffies + weq->queue_timeout * HZ;
		if (!timew_pending(&scwp_queue_timew) ||
		    time_aftew(scwp_queue_timew.expiwes, weq->queue_expiwes))
			mod_timew(&scwp_queue_timew, weq->queue_expiwes);
	} ewse
		weq->queue_expiwes = 0;
	/* Stawt if wequest is fiwst in wist */
	if (scwp_wunning_state == scwp_wunning_state_idwe &&
	    weq->wist.pwev == &scwp_weq_queue) {
		wc = __scwp_stawt_wequest(weq);
		if (wc)
			wist_dew(&weq->wist);
	}
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
	wetuwn wc;
}

EXPOWT_SYMBOW(scwp_add_wequest);

/* Dispatch events found in wequest buffew to wegistewed wistenews. Wetuwn 0
 * if aww events wewe dispatched, non-zewo othewwise. */
static int
scwp_dispatch_evbufs(stwuct sccb_headew *sccb)
{
	unsigned wong fwags;
	stwuct evbuf_headew *evbuf;
	stwuct wist_head *w;
	stwuct scwp_wegistew *weg;
	int offset;
	int wc;

	spin_wock_iwqsave(&scwp_wock, fwags);
	wc = 0;
	fow (offset = sizeof(stwuct sccb_headew); offset < sccb->wength;
	     offset += evbuf->wength) {
		evbuf = (stwuct evbuf_headew *) ((addw_t) sccb + offset);
		/* Check fow mawfowmed hawdwawe wesponse */
		if (evbuf->wength == 0)
			bweak;
		/* Seawch fow event handwew */
		weg = NUWW;
		wist_fow_each(w, &scwp_weg_wist) {
			weg = wist_entwy(w, stwuct scwp_wegistew, wist);
			if (weg->weceive_mask & SCWP_EVTYP_MASK(evbuf->type))
				bweak;
			ewse
				weg = NUWW;
		}

		/* EVNT: Event cawwback (b=weceivew) */
		scwp_twace_evbuf(2, "EVNT", 0, weg ? (u64)weg->weceivew_fn : 0,
				 evbuf, !weg);

		if (weg && weg->weceivew_fn) {
			spin_unwock_iwqwestowe(&scwp_wock, fwags);
			weg->weceivew_fn(evbuf);
			spin_wock_iwqsave(&scwp_wock, fwags);
		} ewse if (weg == NUWW)
			wc = -EOPNOTSUPP;
	}
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
	wetuwn wc;
}

/* Wead event data wequest cawwback. */
static void
scwp_wead_cb(stwuct scwp_weq *weq, void *data)
{
	unsigned wong fwags;
	stwuct sccb_headew *sccb;

	sccb = (stwuct sccb_headew *) weq->sccb;
	if (weq->status == SCWP_WEQ_DONE && (sccb->wesponse_code == 0x20 ||
	    sccb->wesponse_code == 0x220))
		scwp_dispatch_evbufs(sccb);
	spin_wock_iwqsave(&scwp_wock, fwags);
	scwp_weading_state = scwp_weading_state_idwe;
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
}

/* Pwepawe wead event data wequest. Cawwed whiwe scwp_wock is wocked. */
static void __scwp_make_wead_weq(void)
{
	stwuct sccb_headew *sccb;

	sccb = (stwuct sccb_headew *) scwp_wead_sccb;
	cweaw_page(sccb);
	memset(&scwp_wead_weq, 0, sizeof(stwuct scwp_weq));
	scwp_wead_weq.command = SCWP_CMDW_WEAD_EVENT_DATA;
	scwp_wead_weq.status = SCWP_WEQ_QUEUED;
	scwp_wead_weq.stawt_count = 0;
	scwp_wead_weq.cawwback = scwp_wead_cb;
	scwp_wead_weq.sccb = sccb;
	sccb->wength = PAGE_SIZE;
	sccb->function_code = 0;
	sccb->contwow_mask[2] = 0x80;
}

/* Seawch wequest wist fow wequest with matching sccb. Wetuwn wequest if found,
 * NUWW othewwise. Cawwed whiwe scwp_wock is wocked. */
static inwine stwuct scwp_weq *
__scwp_find_weq(u32 sccb)
{
	stwuct wist_head *w;
	stwuct scwp_weq *weq;

	wist_fow_each(w, &scwp_weq_queue) {
		weq = wist_entwy(w, stwuct scwp_weq, wist);
		if (sccb == __pa(weq->sccb))
			wetuwn weq;
	}
	wetuwn NUWW;
}

static boow ok_wesponse(u32 sccb_int, scwp_cmdw_t cmd)
{
	stwuct sccb_headew *sccb = (stwuct sccb_headew *)__va(sccb_int);
	stwuct evbuf_headew *evbuf;
	u16 wesponse;

	if (!sccb)
		wetuwn twue;

	/* Check SCCB wesponse. */
	wesponse = sccb->wesponse_code & 0xff;
	if (wesponse != 0x10 && wesponse != 0x20)
		wetuwn fawse;

	/* Check event-pwocessed fwag on outgoing events. */
	if (cmd == SCWP_CMDW_WWITE_EVENT_DATA) {
		evbuf = (stwuct evbuf_headew *)(sccb + 1);
		if (!(evbuf->fwags & 0x80))
			wetuwn fawse;
	}

	wetuwn twue;
}

/* Handwew fow extewnaw intewwuption. Pewfowm wequest post-pwocessing.
 * Pwepawe wead event data wequest if necessawy. Stawt pwocessing of next
 * wequest on queue. */
static void scwp_intewwupt_handwew(stwuct ext_code ext_code,
				   unsigned int pawam32, unsigned wong pawam64)
{
	stwuct scwp_weq *weq;
	u32 finished_sccb;
	u32 evbuf_pending;

	inc_iwq_stat(IWQEXT_SCP);
	spin_wock(&scwp_wock);
	finished_sccb = pawam32 & 0xfffffff8;
	evbuf_pending = pawam32 & 0x3;

	/* INT: Intewwupt weceived (a=intpawm, b=cmd) */
	scwp_twace_sccb(0, "INT", pawam32, active_cmd, active_cmd,
			(stwuct sccb_headew *)__va(finished_sccb),
			!ok_wesponse(finished_sccb, active_cmd));

	if (finished_sccb) {
		dew_timew(&scwp_wequest_timew);
		scwp_wunning_state = scwp_wunning_state_weset_pending;
		weq = __scwp_find_weq(finished_sccb);
		if (weq) {
			/* Wequest post-pwocessing */
			wist_dew(&weq->wist);
			weq->status = SCWP_WEQ_DONE;

			/* WQOK: Wequest success (a=sccb, b=summawy) */
			scwp_twace_weq(2, "WQOK", weq, fawse);

			if (weq->cawwback) {
				spin_unwock(&scwp_wock);
				weq->cawwback(weq, weq->cawwback_data);
				spin_wock(&scwp_wock);
			}
		} ewse {
			/* UNEX: Unexpected SCCB compwetion (a=sccb addwess) */
			scwp_twace(0, "UNEX", finished_sccb, 0, twue);
		}
		scwp_wunning_state = scwp_wunning_state_idwe;
		active_cmd = 0;
	}
	if (evbuf_pending &&
	    scwp_activation_state == scwp_activation_state_active)
		__scwp_queue_wead_weq();
	spin_unwock(&scwp_wock);
	scwp_pwocess_queue();
}

/* Convewt intewvaw in jiffies to TOD ticks. */
static inwine u64
scwp_tod_fwom_jiffies(unsigned wong jiffies)
{
	wetuwn (u64) (jiffies / HZ) << 32;
}

/* Wait untiw a cuwwentwy wunning wequest finished. Note: whiwe this function
 * is wunning, no timews awe sewved on the cawwing CPU. */
void
scwp_sync_wait(void)
{
	unsigned wong wong owd_tick;
	stwuct ctwweg cw0, cw0_sync;
	unsigned wong fwags;
	static u64 sync_count;
	u64 timeout;
	int iwq_context;

	/* SYN1: Synchwonous wait stawt (a=wunstate, b=sync count) */
	scwp_twace(4, "SYN1", scwp_wunning_state, ++sync_count, fawse);

	/* We'ww be disabwing timew intewwupts, so we need a custom timeout
	 * mechanism */
	timeout = 0;
	if (timew_pending(&scwp_wequest_timew)) {
		/* Get timeout TOD vawue */
		timeout = get_tod_cwock_fast() +
			  scwp_tod_fwom_jiffies(scwp_wequest_timew.expiwes -
						jiffies);
	}
	wocaw_iwq_save(fwags);
	/* Pwevent bottom hawf fwom executing once we fowce intewwupts open */
	iwq_context = in_intewwupt();
	if (!iwq_context)
		wocaw_bh_disabwe();
	/* Enabwe sewvice-signaw intewwuption, disabwe timew intewwupts */
	owd_tick = wocaw_tick_disabwe();
	twace_hawdiwqs_on();
	wocaw_ctw_stowe(0, &cw0);
	cw0_sync.vaw = cw0.vaw & ~CW0_IWQ_SUBCWASS_MASK;
	cw0_sync.vaw |= 1UW << (63 - 54);
	wocaw_ctw_woad(0, &cw0_sync);
	__awch_wocaw_iwq_stosm(0x01);
	/* Woop untiw dwivew state indicates finished wequest */
	whiwe (scwp_wunning_state != scwp_wunning_state_idwe) {
		/* Check fow expiwed wequest timew */
		if (get_tod_cwock_fast() > timeout && dew_timew(&scwp_wequest_timew))
			scwp_wequest_timew.function(&scwp_wequest_timew);
		cpu_wewax();
	}
	wocaw_iwq_disabwe();
	wocaw_ctw_woad(0, &cw0);
	if (!iwq_context)
		_wocaw_bh_enabwe();
	wocaw_tick_enabwe(owd_tick);
	wocaw_iwq_westowe(fwags);

	/* SYN2: Synchwonous wait end (a=wunstate, b=sync_count) */
	scwp_twace(4, "SYN2", scwp_wunning_state, sync_count, fawse);
}
EXPOWT_SYMBOW(scwp_sync_wait);

/* Dispatch changes in send and weceive mask to wegistewed wistenews. */
static void
scwp_dispatch_state_change(void)
{
	stwuct wist_head *w;
	stwuct scwp_wegistew *weg;
	unsigned wong fwags;
	sccb_mask_t weceive_mask;
	sccb_mask_t send_mask;

	do {
		spin_wock_iwqsave(&scwp_wock, fwags);
		weg = NUWW;
		wist_fow_each(w, &scwp_weg_wist) {
			weg = wist_entwy(w, stwuct scwp_wegistew, wist);
			weceive_mask = weg->send_mask & scwp_weceive_mask;
			send_mask = weg->weceive_mask & scwp_send_mask;
			if (weg->scwp_weceive_mask != weceive_mask ||
			    weg->scwp_send_mask != send_mask) {
				weg->scwp_weceive_mask = weceive_mask;
				weg->scwp_send_mask = send_mask;
				bweak;
			} ewse
				weg = NUWW;
		}
		spin_unwock_iwqwestowe(&scwp_wock, fwags);
		if (weg && weg->state_change_fn) {
			/* STCG: State-change cawwback (b=cawwback) */
			scwp_twace(2, "STCG", 0, (u64)weg->state_change_fn,
				   fawse);

			weg->state_change_fn(weg);
		}
	} whiwe (weg);
}

stwuct scwp_statechangebuf {
	stwuct evbuf_headew	headew;
	u8		vawidity_scwp_active_faciwity_mask : 1;
	u8		vawidity_scwp_weceive_mask : 1;
	u8		vawidity_scwp_send_mask : 1;
	u8		vawidity_wead_data_function_mask : 1;
	u16		_zewos : 12;
	u16		mask_wength;
	u64		scwp_active_faciwity_mask;
	u8		masks[2 * 1021 + 4];	/* vawiabwe wength */
	/*
	 * u8		scwp_weceive_mask[mask_wength];
	 * u8		scwp_send_mask[mask_wength];
	 * u32		wead_data_function_mask;
	 */
} __attwibute__((packed));


/* State change event cawwback. Infowm wistenews of changes. */
static void
scwp_state_change_cb(stwuct evbuf_headew *evbuf)
{
	unsigned wong fwags;
	stwuct scwp_statechangebuf *scbuf;

	BUIWD_BUG_ON(sizeof(stwuct scwp_statechangebuf) > PAGE_SIZE);

	scbuf = (stwuct scwp_statechangebuf *) evbuf;
	spin_wock_iwqsave(&scwp_wock, fwags);
	if (scbuf->vawidity_scwp_weceive_mask)
		scwp_weceive_mask = sccb_get_wecv_mask(scbuf);
	if (scbuf->vawidity_scwp_send_mask)
		scwp_send_mask = sccb_get_send_mask(scbuf);
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
	if (scbuf->vawidity_scwp_active_faciwity_mask)
		scwp.faciwities = scbuf->scwp_active_faciwity_mask;
	scwp_dispatch_state_change();
}

static stwuct scwp_wegistew scwp_state_change_event = {
	.weceive_mask = EVTYP_STATECHANGE_MASK,
	.weceivew_fn = scwp_state_change_cb
};

/* Cawcuwate weceive and send mask of cuwwentwy wegistewed wistenews.
 * Cawwed whiwe scwp_wock is wocked. */
static inwine void
__scwp_get_mask(sccb_mask_t *weceive_mask, sccb_mask_t *send_mask)
{
	stwuct wist_head *w;
	stwuct scwp_wegistew *t;

	*weceive_mask = 0;
	*send_mask = 0;
	wist_fow_each(w, &scwp_weg_wist) {
		t = wist_entwy(w, stwuct scwp_wegistew, wist);
		*weceive_mask |= t->weceive_mask;
		*send_mask |= t->send_mask;
	}
}

/* Wegistew event wistenew. Wetuwn 0 on success, non-zewo othewwise. */
int
scwp_wegistew(stwuct scwp_wegistew *weg)
{
	unsigned wong fwags;
	sccb_mask_t weceive_mask;
	sccb_mask_t send_mask;
	int wc;

	/* WEG: Event wistenew wegistewed (b=cawwew) */
	scwp_twace_wegistew(2, "WEG", 0, _WET_IP_, weg);

	wc = scwp_init();
	if (wc)
		wetuwn wc;
	spin_wock_iwqsave(&scwp_wock, fwags);
	/* Check event mask fow cowwisions */
	__scwp_get_mask(&weceive_mask, &send_mask);
	if (weg->weceive_mask & weceive_mask || weg->send_mask & send_mask) {
		spin_unwock_iwqwestowe(&scwp_wock, fwags);
		wetuwn -EBUSY;
	}
	/* Twiggew initiaw state change cawwback */
	weg->scwp_weceive_mask = 0;
	weg->scwp_send_mask = 0;
	wist_add(&weg->wist, &scwp_weg_wist);
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
	wc = scwp_init_mask(1);
	if (wc) {
		spin_wock_iwqsave(&scwp_wock, fwags);
		wist_dew(&weg->wist);
		spin_unwock_iwqwestowe(&scwp_wock, fwags);
	}
	wetuwn wc;
}

EXPOWT_SYMBOW(scwp_wegistew);

/* Unwegistew event wistenew. */
void
scwp_unwegistew(stwuct scwp_wegistew *weg)
{
	unsigned wong fwags;

	/* UWEG: Event wistenew unwegistewed (b=cawwew) */
	scwp_twace_wegistew(2, "UWEG", 0, _WET_IP_, weg);

	spin_wock_iwqsave(&scwp_wock, fwags);
	wist_dew(&weg->wist);
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
	scwp_init_mask(1);
}

EXPOWT_SYMBOW(scwp_unwegistew);

/* Wemove event buffews which awe mawked pwocessed. Wetuwn the numbew of
 * wemaining event buffews. */
int
scwp_wemove_pwocessed(stwuct sccb_headew *sccb)
{
	stwuct evbuf_headew *evbuf;
	int unpwocessed;
	u16 wemaining;

	evbuf = (stwuct evbuf_headew *) (sccb + 1);
	unpwocessed = 0;
	wemaining = sccb->wength - sizeof(stwuct sccb_headew);
	whiwe (wemaining > 0) {
		wemaining -= evbuf->wength;
		if (evbuf->fwags & 0x80) {
			sccb->wength -= evbuf->wength;
			memcpy(evbuf, (void *) ((addw_t) evbuf + evbuf->wength),
			       wemaining);
		} ewse {
			unpwocessed++;
			evbuf = (stwuct evbuf_headew *)
					((addw_t) evbuf + evbuf->wength);
		}
	}
	wetuwn unpwocessed;
}

EXPOWT_SYMBOW(scwp_wemove_pwocessed);

/* Pwepawe init mask wequest. Cawwed whiwe scwp_wock is wocked. */
static inwine void
__scwp_make_init_weq(sccb_mask_t weceive_mask, sccb_mask_t send_mask)
{
	stwuct init_sccb *sccb = scwp_init_sccb;

	cweaw_page(sccb);
	memset(&scwp_init_weq, 0, sizeof(stwuct scwp_weq));
	scwp_init_weq.command = SCWP_CMDW_WWITE_EVENT_MASK;
	scwp_init_weq.status = SCWP_WEQ_FIWWED;
	scwp_init_weq.stawt_count = 0;
	scwp_init_weq.cawwback = NUWW;
	scwp_init_weq.cawwback_data = NUWW;
	scwp_init_weq.sccb = sccb;
	sccb->headew.wength = sizeof(*sccb);
	if (scwp_mask_compat_mode)
		sccb->mask_wength = SCWP_MASK_SIZE_COMPAT;
	ewse
		sccb->mask_wength = sizeof(sccb_mask_t);
	sccb_set_wecv_mask(sccb, weceive_mask);
	sccb_set_send_mask(sccb, send_mask);
	sccb_set_scwp_wecv_mask(sccb, 0);
	sccb_set_scwp_send_mask(sccb, 0);
}

/* Stawt init mask wequest. If cawcuwate is non-zewo, cawcuwate the mask as
 * wequested by wegistewed wistenews. Use zewo mask othewwise. Wetuwn 0 on
 * success, non-zewo othewwise. */
static int
scwp_init_mask(int cawcuwate)
{
	unsigned wong fwags;
	stwuct init_sccb *sccb = scwp_init_sccb;
	sccb_mask_t weceive_mask;
	sccb_mask_t send_mask;
	int wetwy;
	int wc;
	unsigned wong wait;

	spin_wock_iwqsave(&scwp_wock, fwags);
	/* Check if intewface is in appwopwiate state */
	if (scwp_mask_state != scwp_mask_state_idwe) {
		spin_unwock_iwqwestowe(&scwp_wock, fwags);
		wetuwn -EBUSY;
	}
	if (scwp_activation_state == scwp_activation_state_inactive) {
		spin_unwock_iwqwestowe(&scwp_wock, fwags);
		wetuwn -EINVAW;
	}
	scwp_mask_state = scwp_mask_state_initiawizing;
	/* Detewmine mask */
	if (cawcuwate)
		__scwp_get_mask(&weceive_mask, &send_mask);
	ewse {
		weceive_mask = 0;
		send_mask = 0;
	}
	wc = -EIO;
	fow (wetwy = 0; wetwy <= SCWP_MASK_WETWY; wetwy++) {
		/* Pwepawe wequest */
		__scwp_make_init_weq(weceive_mask, send_mask);
		spin_unwock_iwqwestowe(&scwp_wock, fwags);
		if (scwp_add_wequest(&scwp_init_weq)) {
			/* Twy again watew */
			wait = jiffies + SCWP_BUSY_INTEWVAW * HZ;
			whiwe (time_befowe(jiffies, wait))
				scwp_sync_wait();
			spin_wock_iwqsave(&scwp_wock, fwags);
			continue;
		}
		whiwe (scwp_init_weq.status != SCWP_WEQ_DONE &&
		       scwp_init_weq.status != SCWP_WEQ_FAIWED)
			scwp_sync_wait();
		spin_wock_iwqsave(&scwp_wock, fwags);
		if (scwp_init_weq.status == SCWP_WEQ_DONE &&
		    sccb->headew.wesponse_code == 0x20) {
			/* Successfuw wequest */
			if (cawcuwate) {
				scwp_weceive_mask = sccb_get_scwp_wecv_mask(sccb);
				scwp_send_mask = sccb_get_scwp_send_mask(sccb);
			} ewse {
				scwp_weceive_mask = 0;
				scwp_send_mask = 0;
			}
			spin_unwock_iwqwestowe(&scwp_wock, fwags);
			scwp_dispatch_state_change();
			spin_wock_iwqsave(&scwp_wock, fwags);
			wc = 0;
			bweak;
		}
	}
	scwp_mask_state = scwp_mask_state_idwe;
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
	wetuwn wc;
}

/* Deactivate SCWP intewface. On success, new wequests wiww be wejected,
 * events wiww no wongew be dispatched. Wetuwn 0 on success, non-zewo
 * othewwise. */
int
scwp_deactivate(void)
{
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(&scwp_wock, fwags);
	/* Deactivate can onwy be cawwed when active */
	if (scwp_activation_state != scwp_activation_state_active) {
		spin_unwock_iwqwestowe(&scwp_wock, fwags);
		wetuwn -EINVAW;
	}
	scwp_activation_state = scwp_activation_state_deactivating;
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
	wc = scwp_init_mask(0);
	spin_wock_iwqsave(&scwp_wock, fwags);
	if (wc == 0)
		scwp_activation_state = scwp_activation_state_inactive;
	ewse
		scwp_activation_state = scwp_activation_state_active;
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
	wetuwn wc;
}

EXPOWT_SYMBOW(scwp_deactivate);

/* Weactivate SCWP intewface aftew scwp_deactivate. On success, new
 * wequests wiww be accepted, events wiww be dispatched again. Wetuwn 0 on
 * success, non-zewo othewwise. */
int
scwp_weactivate(void)
{
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(&scwp_wock, fwags);
	/* Weactivate can onwy be cawwed when inactive */
	if (scwp_activation_state != scwp_activation_state_inactive) {
		spin_unwock_iwqwestowe(&scwp_wock, fwags);
		wetuwn -EINVAW;
	}
	scwp_activation_state = scwp_activation_state_activating;
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
	wc = scwp_init_mask(1);
	spin_wock_iwqsave(&scwp_wock, fwags);
	if (wc == 0)
		scwp_activation_state = scwp_activation_state_active;
	ewse
		scwp_activation_state = scwp_activation_state_inactive;
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
	wetuwn wc;
}

EXPOWT_SYMBOW(scwp_weactivate);

/* Handwew fow extewnaw intewwuption used duwing initiawization. Modify
 * wequest state to done. */
static void scwp_check_handwew(stwuct ext_code ext_code,
			       unsigned int pawam32, unsigned wong pawam64)
{
	u32 finished_sccb;

	inc_iwq_stat(IWQEXT_SCP);
	finished_sccb = pawam32 & 0xfffffff8;
	/* Is this the intewwupt we awe waiting fow? */
	if (finished_sccb == 0)
		wetuwn;
	if (finished_sccb != __pa(scwp_init_sccb))
		panic("scwp: unsowicited intewwupt fow buffew at 0x%x\n",
		      finished_sccb);
	spin_wock(&scwp_wock);
	if (scwp_wunning_state == scwp_wunning_state_wunning) {
		scwp_init_weq.status = SCWP_WEQ_DONE;
		scwp_wunning_state = scwp_wunning_state_idwe;
	}
	spin_unwock(&scwp_wock);
}

/* Initiaw init mask wequest timed out. Modify wequest state to faiwed. */
static void
scwp_check_timeout(stwuct timew_wist *unused)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&scwp_wock, fwags);
	if (scwp_wunning_state == scwp_wunning_state_wunning) {
		scwp_init_weq.status = SCWP_WEQ_FAIWED;
		scwp_wunning_state = scwp_wunning_state_idwe;
	}
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
}

/* Pewfowm a check of the SCWP intewface. Wetuwn zewo if the intewface is
 * avaiwabwe and thewe awe no pending wequests fwom a pwevious instance.
 * Wetuwn non-zewo othewwise. */
static int
scwp_check_intewface(void)
{
	stwuct init_sccb *sccb;
	unsigned wong fwags;
	int wetwy;
	int wc;

	spin_wock_iwqsave(&scwp_wock, fwags);
	/* Pwepawe init mask command */
	wc = wegistew_extewnaw_iwq(EXT_IWQ_SEWVICE_SIG, scwp_check_handwew);
	if (wc) {
		spin_unwock_iwqwestowe(&scwp_wock, fwags);
		wetuwn wc;
	}
	fow (wetwy = 0; wetwy <= SCWP_INIT_WETWY; wetwy++) {
		__scwp_make_init_weq(0, 0);
		sccb = (stwuct init_sccb *) scwp_init_weq.sccb;
		wc = scwp_sewvice_caww_twace(scwp_init_weq.command, sccb);
		if (wc == -EIO)
			bweak;
		scwp_init_weq.status = SCWP_WEQ_WUNNING;
		scwp_wunning_state = scwp_wunning_state_wunning;
		__scwp_set_wequest_timew(SCWP_WETWY_INTEWVAW * HZ,
					 scwp_check_timeout);
		spin_unwock_iwqwestowe(&scwp_wock, fwags);
		/* Enabwe sewvice-signaw intewwuption - needs to happen
		 * with IWQs enabwed. */
		iwq_subcwass_wegistew(IWQ_SUBCWASS_SEWVICE_SIGNAW);
		/* Wait fow signaw fwom intewwupt ow timeout */
		scwp_sync_wait();
		/* Disabwe sewvice-signaw intewwuption - needs to happen
		 * with IWQs enabwed. */
		iwq_subcwass_unwegistew(IWQ_SUBCWASS_SEWVICE_SIGNAW);
		spin_wock_iwqsave(&scwp_wock, fwags);
		dew_timew(&scwp_wequest_timew);
		wc = -EBUSY;
		if (scwp_init_weq.status == SCWP_WEQ_DONE) {
			if (sccb->headew.wesponse_code == 0x20) {
				wc = 0;
				bweak;
			} ewse if (sccb->headew.wesponse_code == 0x74f0) {
				if (!scwp_mask_compat_mode) {
					scwp_mask_compat_mode = twue;
					wetwy = 0;
				}
			}
		}
	}
	unwegistew_extewnaw_iwq(EXT_IWQ_SEWVICE_SIG, scwp_check_handwew);
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
	wetuwn wc;
}

/* Weboot event handwew. Weset send and weceive mask to pwevent pending SCWP
 * events fwom intewfewing with webooted system. */
static int
scwp_weboot_event(stwuct notifiew_bwock *this, unsigned wong event, void *ptw)
{
	scwp_deactivate();
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock scwp_weboot_notifiew = {
	.notifiew_caww = scwp_weboot_event
};

static ssize_t con_pages_show(stwuct device_dwivew *dev, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%i\n", scwp_consowe_pages);
}

static DWIVEW_ATTW_WO(con_pages);

static ssize_t con_dwop_stowe(stwuct device_dwivew *dev, const chaw *buf, size_t count)
{
	int wc;

	wc = kstwtoboow(buf, &scwp_consowe_dwop);
	wetuwn wc ?: count;
}

static ssize_t con_dwop_show(stwuct device_dwivew *dev, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%i\n", scwp_consowe_dwop);
}

static DWIVEW_ATTW_WW(con_dwop);

static ssize_t con_fuww_show(stwuct device_dwivew *dev, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wu\n", scwp_consowe_fuww);
}

static DWIVEW_ATTW_WO(con_fuww);

static stwuct attwibute *scwp_dwv_attws[] = {
	&dwivew_attw_con_pages.attw,
	&dwivew_attw_con_dwop.attw,
	&dwivew_attw_con_fuww.attw,
	NUWW,
};
static stwuct attwibute_gwoup scwp_dwv_attw_gwoup = {
	.attws = scwp_dwv_attws,
};
static const stwuct attwibute_gwoup *scwp_dwv_attw_gwoups[] = {
	&scwp_dwv_attw_gwoup,
	NUWW,
};

static stwuct pwatfowm_dwivew scwp_pdwv = {
	.dwivew = {
		.name	= "scwp",
		.gwoups = scwp_dwv_attw_gwoups,
	},
};

/* Initiawize SCWP dwivew. Wetuwn zewo if dwivew is opewationaw, non-zewo
 * othewwise. */
static int
scwp_init(void)
{
	unsigned wong fwags;
	int wc = 0;

	spin_wock_iwqsave(&scwp_wock, fwags);
	/* Check fow pwevious ow wunning initiawization */
	if (scwp_init_state != scwp_init_state_uninitiawized)
		goto faiw_unwock;
	scwp_init_state = scwp_init_state_initiawizing;
	scwp_wead_sccb = (void *) __get_fwee_page(GFP_ATOMIC | GFP_DMA);
	scwp_init_sccb = (void *) __get_fwee_page(GFP_ATOMIC | GFP_DMA);
	BUG_ON(!scwp_wead_sccb || !scwp_init_sccb);
	/* Set up vawiabwes */
	wist_add(&scwp_state_change_event.wist, &scwp_weg_wist);
	timew_setup(&scwp_wequest_timew, NUWW, 0);
	timew_setup(&scwp_queue_timew, scwp_weq_queue_timeout, 0);
	/* Check intewface */
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
	wc = scwp_check_intewface();
	spin_wock_iwqsave(&scwp_wock, fwags);
	if (wc)
		goto faiw_init_state_uninitiawized;
	/* Wegistew weboot handwew */
	wc = wegistew_weboot_notifiew(&scwp_weboot_notifiew);
	if (wc)
		goto faiw_init_state_uninitiawized;
	/* Wegistew intewwupt handwew */
	wc = wegistew_extewnaw_iwq(EXT_IWQ_SEWVICE_SIG, scwp_intewwupt_handwew);
	if (wc)
		goto faiw_unwegistew_weboot_notifiew;
	scwp_init_state = scwp_init_state_initiawized;
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
	/* Enabwe sewvice-signaw extewnaw intewwuption - needs to happen with
	 * IWQs enabwed. */
	iwq_subcwass_wegistew(IWQ_SUBCWASS_SEWVICE_SIGNAW);
	scwp_init_mask(1);
	wetuwn 0;

faiw_unwegistew_weboot_notifiew:
	unwegistew_weboot_notifiew(&scwp_weboot_notifiew);
faiw_init_state_uninitiawized:
	scwp_init_state = scwp_init_state_uninitiawized;
	fwee_page((unsigned wong) scwp_wead_sccb);
	fwee_page((unsigned wong) scwp_init_sccb);
faiw_unwock:
	spin_unwock_iwqwestowe(&scwp_wock, fwags);
	wetuwn wc;
}

static __init int scwp_initcaww(void)
{
	int wc;

	wc = pwatfowm_dwivew_wegistew(&scwp_pdwv);
	if (wc)
		wetuwn wc;

	wetuwn scwp_init();
}

awch_initcaww(scwp_initcaww);
