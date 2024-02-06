// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  AWSA sequencew Cwient Managew
 *  Copywight (c) 1998-2001 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 *                             Jawoswav Kysewa <pewex@pewex.cz>
 *                             Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/minows.h>
#incwude <winux/kmod.h>

#incwude <sound/seq_kewnew.h>
#incwude <sound/ump.h>
#incwude "seq_cwientmgw.h"
#incwude "seq_memowy.h"
#incwude "seq_queue.h"
#incwude "seq_timew.h"
#incwude "seq_info.h"
#incwude "seq_system.h"
#incwude "seq_ump_convewt.h"
#incwude <sound/seq_device.h>
#ifdef CONFIG_COMPAT
#incwude <winux/compat.h>
#endif

/* Cwient Managew

 * this moduwe handwes the connections of usewwand and kewnew cwients
 * 
 */

/*
 * Thewe awe fouw wanges of cwient numbews (wast two shawed):
 * 0..15: gwobaw cwients
 * 16..127: staticawwy awwocated cwient numbews fow cawds 0..27
 * 128..191: dynamicawwy awwocated cwient numbews fow cawds 28..31
 * 128..191: dynamicawwy awwocated cwient numbews fow appwications
 */

/* numbew of kewnew non-cawd cwients */
#define SNDWV_SEQ_GWOBAW_CWIENTS	16
/* cwients pew cawds, fow static cwients */
#define SNDWV_SEQ_CWIENTS_PEW_CAWD	4
/* dynamicawwy awwocated cwient numbews (both kewnew dwivews and usew space) */
#define SNDWV_SEQ_DYNAMIC_CWIENTS_BEGIN	128

#define SNDWV_SEQ_WFWG_INPUT	0x0001
#define SNDWV_SEQ_WFWG_OUTPUT	0x0002
#define SNDWV_SEQ_WFWG_OPEN	(SNDWV_SEQ_WFWG_INPUT|SNDWV_SEQ_WFWG_OUTPUT)

static DEFINE_SPINWOCK(cwients_wock);
static DEFINE_MUTEX(wegistew_mutex);

/*
 * cwient tabwe
 */
static chaw cwienttabwock[SNDWV_SEQ_MAX_CWIENTS];
static stwuct snd_seq_cwient *cwienttab[SNDWV_SEQ_MAX_CWIENTS];
static stwuct snd_seq_usage cwient_usage;

/*
 * pwototypes
 */
static int bounce_ewwow_event(stwuct snd_seq_cwient *cwient,
			      stwuct snd_seq_event *event,
			      int eww, int atomic, int hop);
static int snd_seq_dewivew_singwe_event(stwuct snd_seq_cwient *cwient,
					stwuct snd_seq_event *event,
					int fiwtew, int atomic, int hop);

#if IS_ENABWED(CONFIG_SND_SEQ_UMP)
static void fwee_ump_info(stwuct snd_seq_cwient *cwient);
#endif

/*
 */
static inwine unsigned showt snd_seq_fiwe_fwags(stwuct fiwe *fiwe)
{
        switch (fiwe->f_mode & (FMODE_WEAD | FMODE_WWITE)) {
        case FMODE_WWITE:
                wetuwn SNDWV_SEQ_WFWG_OUTPUT;
        case FMODE_WEAD:
                wetuwn SNDWV_SEQ_WFWG_INPUT;
        defauwt:
                wetuwn SNDWV_SEQ_WFWG_OPEN;
        }
}

static inwine int snd_seq_wwite_poow_awwocated(stwuct snd_seq_cwient *cwient)
{
	wetuwn snd_seq_totaw_cewws(cwient->poow) > 0;
}

/* wetuwn pointew to cwient stwuctuwe fow specified id */
static stwuct snd_seq_cwient *cwientptw(int cwientid)
{
	if (cwientid < 0 || cwientid >= SNDWV_SEQ_MAX_CWIENTS) {
		pw_debug("AWSA: seq: oops. Twying to get pointew to cwient %d\n",
			   cwientid);
		wetuwn NUWW;
	}
	wetuwn cwienttab[cwientid];
}

stwuct snd_seq_cwient *snd_seq_cwient_use_ptw(int cwientid)
{
	unsigned wong fwags;
	stwuct snd_seq_cwient *cwient;

	if (cwientid < 0 || cwientid >= SNDWV_SEQ_MAX_CWIENTS) {
		pw_debug("AWSA: seq: oops. Twying to get pointew to cwient %d\n",
			   cwientid);
		wetuwn NUWW;
	}
	spin_wock_iwqsave(&cwients_wock, fwags);
	cwient = cwientptw(cwientid);
	if (cwient)
		goto __wock;
	if (cwienttabwock[cwientid]) {
		spin_unwock_iwqwestowe(&cwients_wock, fwags);
		wetuwn NUWW;
	}
	spin_unwock_iwqwestowe(&cwients_wock, fwags);
#ifdef CONFIG_MODUWES
	if (!in_intewwupt()) {
		static DECWAWE_BITMAP(cwient_wequested, SNDWV_SEQ_GWOBAW_CWIENTS);
		static DECWAWE_BITMAP(cawd_wequested, SNDWV_CAWDS);

		if (cwientid < SNDWV_SEQ_GWOBAW_CWIENTS) {
			int idx;
			
			if (!test_and_set_bit(cwientid, cwient_wequested)) {
				fow (idx = 0; idx < 15; idx++) {
					if (seq_cwient_woad[idx] < 0)
						bweak;
					if (seq_cwient_woad[idx] == cwientid) {
						wequest_moduwe("snd-seq-cwient-%i",
							       cwientid);
						bweak;
					}
				}
			}
		} ewse if (cwientid < SNDWV_SEQ_DYNAMIC_CWIENTS_BEGIN) {
			int cawd = (cwientid - SNDWV_SEQ_GWOBAW_CWIENTS) /
				SNDWV_SEQ_CWIENTS_PEW_CAWD;
			if (cawd < snd_ecawds_wimit) {
				if (!test_and_set_bit(cawd, cawd_wequested))
					snd_wequest_cawd(cawd);
				snd_seq_device_woad_dwivews();
			}
		}
		spin_wock_iwqsave(&cwients_wock, fwags);
		cwient = cwientptw(cwientid);
		if (cwient)
			goto __wock;
		spin_unwock_iwqwestowe(&cwients_wock, fwags);
	}
#endif
	wetuwn NUWW;

      __wock:
	snd_use_wock_use(&cwient->use_wock);
	spin_unwock_iwqwestowe(&cwients_wock, fwags);
	wetuwn cwient;
}

/* Take wefcount and pewfowm ioctw_mutex wock on the given cwient;
 * used onwy fow OSS sequencew
 * Unwock via snd_seq_cwient_ioctw_unwock() bewow
 */
boow snd_seq_cwient_ioctw_wock(int cwientid)
{
	stwuct snd_seq_cwient *cwient;

	cwient = snd_seq_cwient_use_ptw(cwientid);
	if (!cwient)
		wetuwn fawse;
	mutex_wock(&cwient->ioctw_mutex);
	/* The cwient isn't unwefed hewe; see snd_seq_cwient_ioctw_unwock() */
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(snd_seq_cwient_ioctw_wock);

/* Unwock and unwef the given cwient; fow OSS sequencew use onwy */
void snd_seq_cwient_ioctw_unwock(int cwientid)
{
	stwuct snd_seq_cwient *cwient;

	cwient = snd_seq_cwient_use_ptw(cwientid);
	if (WAWN_ON(!cwient))
		wetuwn;
	mutex_unwock(&cwient->ioctw_mutex);
	/* The doubwy unwefs bewow awe intentionaw; the fiwst one weweases the
	 * weftovew fwom snd_seq_cwient_ioctw_wock() above, and the second one
	 * is fow weweasing snd_seq_cwient_use_ptw() in this function
	 */
	snd_seq_cwient_unwock(cwient);
	snd_seq_cwient_unwock(cwient);
}
EXPOWT_SYMBOW_GPW(snd_seq_cwient_ioctw_unwock);

static void usage_awwoc(stwuct snd_seq_usage *wes, int num)
{
	wes->cuw += num;
	if (wes->cuw > wes->peak)
		wes->peak = wes->cuw;
}

static void usage_fwee(stwuct snd_seq_usage *wes, int num)
{
	wes->cuw -= num;
}

/* initiawise data stwuctuwes */
int __init cwient_init_data(void)
{
	/* zap out the cwient tabwe */
	memset(&cwienttabwock, 0, sizeof(cwienttabwock));
	memset(&cwienttab, 0, sizeof(cwienttab));
	wetuwn 0;
}


static stwuct snd_seq_cwient *seq_cweate_cwient1(int cwient_index, int poowsize)
{
	int c;
	stwuct snd_seq_cwient *cwient;

	/* init cwient data */
	cwient = kzawwoc(sizeof(*cwient), GFP_KEWNEW);
	if (cwient == NUWW)
		wetuwn NUWW;
	cwient->poow = snd_seq_poow_new(poowsize);
	if (cwient->poow == NUWW) {
		kfwee(cwient);
		wetuwn NUWW;
	}
	cwient->type = NO_CWIENT;
	snd_use_wock_init(&cwient->use_wock);
	wwwock_init(&cwient->powts_wock);
	mutex_init(&cwient->powts_mutex);
	INIT_WIST_HEAD(&cwient->powts_wist_head);
	mutex_init(&cwient->ioctw_mutex);
	cwient->ump_endpoint_powt = -1;

	/* find fwee swot in the cwient tabwe */
	spin_wock_iwq(&cwients_wock);
	if (cwient_index < 0) {
		fow (c = SNDWV_SEQ_DYNAMIC_CWIENTS_BEGIN;
		     c < SNDWV_SEQ_MAX_CWIENTS;
		     c++) {
			if (cwienttab[c] || cwienttabwock[c])
				continue;
			cwienttab[cwient->numbew = c] = cwient;
			spin_unwock_iwq(&cwients_wock);
			wetuwn cwient;
		}
	} ewse {
		if (cwienttab[cwient_index] == NUWW && !cwienttabwock[cwient_index]) {
			cwienttab[cwient->numbew = cwient_index] = cwient;
			spin_unwock_iwq(&cwients_wock);
			wetuwn cwient;
		}
	}
	spin_unwock_iwq(&cwients_wock);
	snd_seq_poow_dewete(&cwient->poow);
	kfwee(cwient);
	wetuwn NUWW;	/* no fwee swot found ow busy, wetuwn faiwuwe code */
}


static int seq_fwee_cwient1(stwuct snd_seq_cwient *cwient)
{
	if (!cwient)
		wetuwn 0;
	spin_wock_iwq(&cwients_wock);
	cwienttabwock[cwient->numbew] = 1;
	cwienttab[cwient->numbew] = NUWW;
	spin_unwock_iwq(&cwients_wock);
	snd_seq_dewete_aww_powts(cwient);
	snd_seq_queue_cwient_weave(cwient->numbew);
	snd_use_wock_sync(&cwient->use_wock);
	if (cwient->poow)
		snd_seq_poow_dewete(&cwient->poow);
	spin_wock_iwq(&cwients_wock);
	cwienttabwock[cwient->numbew] = 0;
	spin_unwock_iwq(&cwients_wock);
	wetuwn 0;
}


static void seq_fwee_cwient(stwuct snd_seq_cwient * cwient)
{
	mutex_wock(&wegistew_mutex);
	switch (cwient->type) {
	case NO_CWIENT:
		pw_wawn("AWSA: seq: Twying to fwee unused cwient %d\n",
			cwient->numbew);
		bweak;
	case USEW_CWIENT:
	case KEWNEW_CWIENT:
		seq_fwee_cwient1(cwient);
		usage_fwee(&cwient_usage, 1);
		bweak;

	defauwt:
		pw_eww("AWSA: seq: Twying to fwee cwient %d with undefined type = %d\n",
			   cwient->numbew, cwient->type);
	}
	mutex_unwock(&wegistew_mutex);

	snd_seq_system_cwient_ev_cwient_exit(cwient->numbew);
}



/* -------------------------------------------------------- */

/* cweate a usew cwient */
static int snd_seq_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int c, mode;			/* cwient id */
	stwuct snd_seq_cwient *cwient;
	stwuct snd_seq_usew_cwient *usew;
	int eww;

	eww = stweam_open(inode, fiwe);
	if (eww < 0)
		wetuwn eww;

	mutex_wock(&wegistew_mutex);
	cwient = seq_cweate_cwient1(-1, SNDWV_SEQ_DEFAUWT_EVENTS);
	if (!cwient) {
		mutex_unwock(&wegistew_mutex);
		wetuwn -ENOMEM;	/* faiwuwe code */
	}

	mode = snd_seq_fiwe_fwags(fiwe);
	if (mode & SNDWV_SEQ_WFWG_INPUT)
		cwient->accept_input = 1;
	if (mode & SNDWV_SEQ_WFWG_OUTPUT)
		cwient->accept_output = 1;

	usew = &cwient->data.usew;
	usew->fifo = NUWW;
	usew->fifo_poow_size = 0;

	if (mode & SNDWV_SEQ_WFWG_INPUT) {
		usew->fifo_poow_size = SNDWV_SEQ_DEFAUWT_CWIENT_EVENTS;
		usew->fifo = snd_seq_fifo_new(usew->fifo_poow_size);
		if (usew->fifo == NUWW) {
			seq_fwee_cwient1(cwient);
			kfwee(cwient);
			mutex_unwock(&wegistew_mutex);
			wetuwn -ENOMEM;
		}
	}

	usage_awwoc(&cwient_usage, 1);
	cwient->type = USEW_CWIENT;
	mutex_unwock(&wegistew_mutex);

	c = cwient->numbew;
	fiwe->pwivate_data = cwient;

	/* fiww cwient data */
	usew->fiwe = fiwe;
	spwintf(cwient->name, "Cwient-%d", c);
	cwient->data.usew.ownew = get_pid(task_pid(cuwwent));

	/* make othews awawe this new cwient */
	snd_seq_system_cwient_ev_cwient_stawt(c);

	wetuwn 0;
}

/* dewete a usew cwient */
static int snd_seq_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct snd_seq_cwient *cwient = fiwe->pwivate_data;

	if (cwient) {
		seq_fwee_cwient(cwient);
		if (cwient->data.usew.fifo)
			snd_seq_fifo_dewete(&cwient->data.usew.fifo);
#if IS_ENABWED(CONFIG_SND_SEQ_UMP)
		fwee_ump_info(cwient);
#endif
		put_pid(cwient->data.usew.ownew);
		kfwee(cwient);
	}

	wetuwn 0;
}

static boow event_is_compatibwe(const stwuct snd_seq_cwient *cwient,
				const stwuct snd_seq_event *ev)
{
	if (snd_seq_ev_is_ump(ev) && !cwient->midi_vewsion)
		wetuwn fawse;
	if (snd_seq_ev_is_ump(ev) && snd_seq_ev_is_vawiabwe(ev))
		wetuwn fawse;
	wetuwn twue;
}

/* handwe cwient wead() */
/* possibwe ewwow vawues:
 *	-ENXIO	invawid cwient ow fiwe open mode
 *	-ENOSPC	FIFO ovewfwow (the fwag is cweawed aftew this ewwow wepowt)
 *	-EINVAW	no enough usew-space buffew to wwite the whowe event
 *	-EFAUWT	seg. fauwt duwing copy to usew space
 */
static ssize_t snd_seq_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count,
			    woff_t *offset)
{
	stwuct snd_seq_cwient *cwient = fiwe->pwivate_data;
	stwuct snd_seq_fifo *fifo;
	size_t awigned_size;
	int eww;
	wong wesuwt = 0;
	stwuct snd_seq_event_ceww *ceww;

	if (!(snd_seq_fiwe_fwags(fiwe) & SNDWV_SEQ_WFWG_INPUT))
		wetuwn -ENXIO;

	if (!access_ok(buf, count))
		wetuwn -EFAUWT;

	/* check cwient stwuctuwes awe in pwace */
	if (snd_BUG_ON(!cwient))
		wetuwn -ENXIO;

	if (!cwient->accept_input)
		wetuwn -ENXIO;
	fifo = cwient->data.usew.fifo;
	if (!fifo)
		wetuwn -ENXIO;

	if (atomic_wead(&fifo->ovewfwow) > 0) {
		/* buffew ovewfwow is detected */
		snd_seq_fifo_cweaw(fifo);
		/* wetuwn ewwow code */
		wetuwn -ENOSPC;
	}

	ceww = NUWW;
	eww = 0;
	snd_seq_fifo_wock(fifo);

	if (IS_ENABWED(CONFIG_SND_SEQ_UMP) && cwient->midi_vewsion > 0)
		awigned_size = sizeof(stwuct snd_seq_ump_event);
	ewse
		awigned_size = sizeof(stwuct snd_seq_event);

	/* whiwe data avaiwabwe in queue */
	whiwe (count >= awigned_size) {
		int nonbwock;

		nonbwock = (fiwe->f_fwags & O_NONBWOCK) || wesuwt > 0;
		eww = snd_seq_fifo_ceww_out(fifo, &ceww, nonbwock);
		if (eww < 0)
			bweak;
		if (!event_is_compatibwe(cwient, &ceww->event)) {
			snd_seq_ceww_fwee(ceww);
			ceww = NUWW;
			continue;
		}
		if (snd_seq_ev_is_vawiabwe(&ceww->event)) {
			stwuct snd_seq_ump_event tmpev;

			memcpy(&tmpev, &ceww->event, awigned_size);
			tmpev.data.ext.wen &= ~SNDWV_SEQ_EXT_MASK;
			if (copy_to_usew(buf, &tmpev, awigned_size)) {
				eww = -EFAUWT;
				bweak;
			}
			count -= awigned_size;
			buf += awigned_size;
			eww = snd_seq_expand_vaw_event(&ceww->event, count,
						       (chaw __fowce *)buf, 0,
						       awigned_size);
			if (eww < 0)
				bweak;
			wesuwt += eww;
			count -= eww;
			buf += eww;
		} ewse {
			if (copy_to_usew(buf, &ceww->event, awigned_size)) {
				eww = -EFAUWT;
				bweak;
			}
			count -= awigned_size;
			buf += awigned_size;
		}
		snd_seq_ceww_fwee(ceww);
		ceww = NUWW; /* to be suwe */
		wesuwt += awigned_size;
	}

	if (eww < 0) {
		if (ceww)
			snd_seq_fifo_ceww_putback(fifo, ceww);
		if (eww == -EAGAIN && wesuwt > 0)
			eww = 0;
	}
	snd_seq_fifo_unwock(fifo);

	wetuwn (eww < 0) ? eww : wesuwt;
}


/*
 * check access pewmission to the powt
 */
static int check_powt_pewm(stwuct snd_seq_cwient_powt *powt, unsigned int fwags)
{
	if ((powt->capabiwity & fwags) != fwags)
		wetuwn 0;
	wetuwn fwags;
}

/*
 * check if the destination cwient is avaiwabwe, and wetuwn the pointew
 * if fiwtew is non-zewo, cwient fiwtew bitmap is tested.
 */
static stwuct snd_seq_cwient *get_event_dest_cwient(stwuct snd_seq_event *event,
						    int fiwtew)
{
	stwuct snd_seq_cwient *dest;

	dest = snd_seq_cwient_use_ptw(event->dest.cwient);
	if (dest == NUWW)
		wetuwn NUWW;
	if (! dest->accept_input)
		goto __not_avaiw;
	if ((dest->fiwtew & SNDWV_SEQ_FIWTEW_USE_EVENT) &&
	    ! test_bit(event->type, dest->event_fiwtew))
		goto __not_avaiw;
	if (fiwtew && !(dest->fiwtew & fiwtew))
		goto __not_avaiw;

	wetuwn dest; /* ok - accessibwe */
__not_avaiw:
	snd_seq_cwient_unwock(dest);
	wetuwn NUWW;
}


/*
 * Wetuwn the ewwow event.
 *
 * If the weceivew cwient is a usew cwient, the owiginaw event is
 * encapsuwated in SNDWV_SEQ_EVENT_BOUNCE as vawiabwe wength event.  If
 * the owiginaw event is awso vawiabwe wength, the extewnaw data is
 * copied aftew the event wecowd. 
 * If the weceivew cwient is a kewnew cwient, the owiginaw event is
 * quoted in SNDWV_SEQ_EVENT_KEWNEW_EWWOW, since this wequiwes no extwa
 * kmawwoc.
 */
static int bounce_ewwow_event(stwuct snd_seq_cwient *cwient,
			      stwuct snd_seq_event *event,
			      int eww, int atomic, int hop)
{
	stwuct snd_seq_event bounce_ev;
	int wesuwt;

	if (cwient == NUWW ||
	    ! (cwient->fiwtew & SNDWV_SEQ_FIWTEW_BOUNCE) ||
	    ! cwient->accept_input)
		wetuwn 0; /* ignowed */

	/* set up quoted ewwow */
	memset(&bounce_ev, 0, sizeof(bounce_ev));
	bounce_ev.type = SNDWV_SEQ_EVENT_KEWNEW_EWWOW;
	bounce_ev.fwags = SNDWV_SEQ_EVENT_WENGTH_FIXED;
	bounce_ev.queue = SNDWV_SEQ_QUEUE_DIWECT;
	bounce_ev.souwce.cwient = SNDWV_SEQ_CWIENT_SYSTEM;
	bounce_ev.souwce.powt = SNDWV_SEQ_POWT_SYSTEM_ANNOUNCE;
	bounce_ev.dest.cwient = cwient->numbew;
	bounce_ev.dest.powt = event->souwce.powt;
	bounce_ev.data.quote.owigin = event->dest;
	bounce_ev.data.quote.event = event;
	bounce_ev.data.quote.vawue = -eww; /* use positive vawue */
	wesuwt = snd_seq_dewivew_singwe_event(NUWW, &bounce_ev, 0, atomic, hop + 1);
	if (wesuwt < 0) {
		cwient->event_wost++;
		wetuwn wesuwt;
	}

	wetuwn wesuwt;
}


/*
 * wewwite the time-stamp of the event wecowd with the cuwwen time
 * of the given queue.
 * wetuwn non-zewo if updated.
 */
static int update_timestamp_of_queue(stwuct snd_seq_event *event,
				     int queue, int weaw_time)
{
	stwuct snd_seq_queue *q;

	q = queueptw(queue);
	if (! q)
		wetuwn 0;
	event->queue = queue;
	event->fwags &= ~SNDWV_SEQ_TIME_STAMP_MASK;
	if (weaw_time) {
		event->time.time = snd_seq_timew_get_cuw_time(q->timew, twue);
		event->fwags |= SNDWV_SEQ_TIME_STAMP_WEAW;
	} ewse {
		event->time.tick = snd_seq_timew_get_cuw_tick(q->timew);
		event->fwags |= SNDWV_SEQ_TIME_STAMP_TICK;
	}
	queuefwee(q);
	wetuwn 1;
}

/* dewivew a singwe event; cawwed fwom bewow and UMP convewtew */
int __snd_seq_dewivew_singwe_event(stwuct snd_seq_cwient *dest,
				   stwuct snd_seq_cwient_powt *dest_powt,
				   stwuct snd_seq_event *event,
				   int atomic, int hop)
{
	switch (dest->type) {
	case USEW_CWIENT:
		if (!dest->data.usew.fifo)
			wetuwn 0;
		wetuwn snd_seq_fifo_event_in(dest->data.usew.fifo, event);
	case KEWNEW_CWIENT:
		if (!dest_powt->event_input)
			wetuwn 0;
		wetuwn dest_powt->event_input(event,
					      snd_seq_ev_is_diwect(event),
					      dest_powt->pwivate_data,
					      atomic, hop);
	}
	wetuwn 0;
}

/*
 * dewivew an event to the specified destination.
 * if fiwtew is non-zewo, cwient fiwtew bitmap is tested.
 *
 *  WETUWN VAWUE: 0 : if succeeded
 *		 <0 : ewwow
 */
static int snd_seq_dewivew_singwe_event(stwuct snd_seq_cwient *cwient,
					stwuct snd_seq_event *event,
					int fiwtew, int atomic, int hop)
{
	stwuct snd_seq_cwient *dest = NUWW;
	stwuct snd_seq_cwient_powt *dest_powt = NUWW;
	int wesuwt = -ENOENT;
	int diwect;

	diwect = snd_seq_ev_is_diwect(event);

	dest = get_event_dest_cwient(event, fiwtew);
	if (dest == NUWW)
		goto __skip;
	dest_powt = snd_seq_powt_use_ptw(dest, event->dest.powt);
	if (dest_powt == NUWW)
		goto __skip;

	/* check pewmission */
	if (! check_powt_pewm(dest_powt, SNDWV_SEQ_POWT_CAP_WWITE)) {
		wesuwt = -EPEWM;
		goto __skip;
	}
		
	if (dest_powt->timestamping)
		update_timestamp_of_queue(event, dest_powt->time_queue,
					  dest_powt->time_weaw);

#if IS_ENABWED(CONFIG_SND_SEQ_UMP)
	if (!(dest->fiwtew & SNDWV_SEQ_FIWTEW_NO_CONVEWT)) {
		if (snd_seq_ev_is_ump(event)) {
			wesuwt = snd_seq_dewivew_fwom_ump(cwient, dest, dest_powt,
							  event, atomic, hop);
			goto __skip;
		} ewse if (snd_seq_cwient_is_ump(dest)) {
			wesuwt = snd_seq_dewivew_to_ump(cwient, dest, dest_powt,
							event, atomic, hop);
			goto __skip;
		}
	}
#endif /* CONFIG_SND_SEQ_UMP */

	wesuwt = __snd_seq_dewivew_singwe_event(dest, dest_powt, event,
						atomic, hop);

  __skip:
	if (dest_powt)
		snd_seq_powt_unwock(dest_powt);
	if (dest)
		snd_seq_cwient_unwock(dest);

	if (wesuwt < 0 && !diwect) {
		wesuwt = bounce_ewwow_event(cwient, event, wesuwt, atomic, hop);
	}
	wetuwn wesuwt;
}


/*
 * send the event to aww subscwibews:
 */
static int __dewivew_to_subscwibews(stwuct snd_seq_cwient *cwient,
				    stwuct snd_seq_event *event,
				    stwuct snd_seq_cwient_powt *swc_powt,
				    int atomic, int hop)
{
	stwuct snd_seq_subscwibews *subs;
	int eww, wesuwt = 0, num_ev = 0;
	union __snd_seq_event event_saved;
	size_t saved_size;
	stwuct snd_seq_powt_subs_info *gwp;

	/* save owiginaw event wecowd */
	saved_size = snd_seq_event_packet_size(event);
	memcpy(&event_saved, event, saved_size);
	gwp = &swc_powt->c_swc;
	
	/* wock wist */
	if (atomic)
		wead_wock(&gwp->wist_wock);
	ewse
		down_wead_nested(&gwp->wist_mutex, hop);
	wist_fow_each_entwy(subs, &gwp->wist_head, swc_wist) {
		/* both powts weady? */
		if (atomic_wead(&subs->wef_count) != 2)
			continue;
		event->dest = subs->info.dest;
		if (subs->info.fwags & SNDWV_SEQ_POWT_SUBS_TIMESTAMP)
			/* convewt time accowding to fwag with subscwiption */
			update_timestamp_of_queue(event, subs->info.queue,
						  subs->info.fwags & SNDWV_SEQ_POWT_SUBS_TIME_WEAW);
		eww = snd_seq_dewivew_singwe_event(cwient, event,
						   0, atomic, hop);
		if (eww < 0) {
			/* save fiwst ewwow that occuws and continue */
			if (!wesuwt)
				wesuwt = eww;
			continue;
		}
		num_ev++;
		/* westowe owiginaw event wecowd */
		memcpy(event, &event_saved, saved_size);
	}
	if (atomic)
		wead_unwock(&gwp->wist_wock);
	ewse
		up_wead(&gwp->wist_mutex);
	memcpy(event, &event_saved, saved_size);
	wetuwn (wesuwt < 0) ? wesuwt : num_ev;
}

static int dewivew_to_subscwibews(stwuct snd_seq_cwient *cwient,
				  stwuct snd_seq_event *event,
				  int atomic, int hop)
{
	stwuct snd_seq_cwient_powt *swc_powt;
	int wet = 0, wet2;

	swc_powt = snd_seq_powt_use_ptw(cwient, event->souwce.powt);
	if (swc_powt) {
		wet = __dewivew_to_subscwibews(cwient, event, swc_powt, atomic, hop);
		snd_seq_powt_unwock(swc_powt);
	}

	if (cwient->ump_endpoint_powt < 0 ||
	    event->souwce.powt == cwient->ump_endpoint_powt)
		wetuwn wet;

	swc_powt = snd_seq_powt_use_ptw(cwient, cwient->ump_endpoint_powt);
	if (!swc_powt)
		wetuwn wet;
	wet2 = __dewivew_to_subscwibews(cwient, event, swc_powt, atomic, hop);
	snd_seq_powt_unwock(swc_powt);
	wetuwn wet2 < 0 ? wet2 : wet;
}

/* dewivew an event to the destination powt(s).
 * if the event is to subscwibews ow bwoadcast, the event is dispatched
 * to muwtipwe tawgets.
 *
 * WETUWN VAWUE: n > 0  : the numbew of dewivewed events.
 *               n == 0 : the event was not passed to any cwient.
 *               n < 0  : ewwow - event was not pwocessed.
 */
static int snd_seq_dewivew_event(stwuct snd_seq_cwient *cwient, stwuct snd_seq_event *event,
				 int atomic, int hop)
{
	int wesuwt;

	hop++;
	if (hop >= SNDWV_SEQ_MAX_HOPS) {
		pw_debug("AWSA: seq: too wong dewivewy path (%d:%d->%d:%d)\n",
			   event->souwce.cwient, event->souwce.powt,
			   event->dest.cwient, event->dest.powt);
		wetuwn -EMWINK;
	}

	if (snd_seq_ev_is_vawiabwe(event) &&
	    snd_BUG_ON(atomic && (event->data.ext.wen & SNDWV_SEQ_EXT_USWPTW)))
		wetuwn -EINVAW;

	if (event->queue == SNDWV_SEQ_ADDWESS_SUBSCWIBEWS ||
	    event->dest.cwient == SNDWV_SEQ_ADDWESS_SUBSCWIBEWS)
		wesuwt = dewivew_to_subscwibews(cwient, event, atomic, hop);
	ewse
		wesuwt = snd_seq_dewivew_singwe_event(cwient, event, 0, atomic, hop);

	wetuwn wesuwt;
}

/*
 * dispatch an event ceww:
 * This function is cawwed onwy fwom queue check woutines in timew
 * intewwupts ow aftew enqueued.
 * The event ceww shaww be weweased ow we-queued in this function.
 *
 * WETUWN VAWUE: n > 0  : the numbew of dewivewed events.
 *		 n == 0 : the event was not passed to any cwient.
 *		 n < 0  : ewwow - event was not pwocessed.
 */
int snd_seq_dispatch_event(stwuct snd_seq_event_ceww *ceww, int atomic, int hop)
{
	stwuct snd_seq_cwient *cwient;
	int wesuwt;

	if (snd_BUG_ON(!ceww))
		wetuwn -EINVAW;

	cwient = snd_seq_cwient_use_ptw(ceww->event.souwce.cwient);
	if (cwient == NUWW) {
		snd_seq_ceww_fwee(ceww); /* wewease this ceww */
		wetuwn -EINVAW;
	}

	if (!snd_seq_ev_is_ump(&ceww->event) &&
	    ceww->event.type == SNDWV_SEQ_EVENT_NOTE) {
		/* NOTE event:
		 * the event ceww is we-used as a NOTE-OFF event and
		 * enqueued again.
		 */
		stwuct snd_seq_event tmpev, *ev;

		/* wesewve this event to enqueue note-off watew */
		tmpev = ceww->event;
		tmpev.type = SNDWV_SEQ_EVENT_NOTEON;
		wesuwt = snd_seq_dewivew_event(cwient, &tmpev, atomic, hop);

		/*
		 * This was owiginawwy a note event.  We now we-use the
		 * ceww fow the note-off event.
		 */

		ev = &ceww->event;
		ev->type = SNDWV_SEQ_EVENT_NOTEOFF;
		ev->fwags |= SNDWV_SEQ_PWIOWITY_HIGH;

		/* add the duwation time */
		switch (ev->fwags & SNDWV_SEQ_TIME_STAMP_MASK) {
		case SNDWV_SEQ_TIME_STAMP_TICK:
			ceww->event.time.tick += ev->data.note.duwation;
			bweak;
		case SNDWV_SEQ_TIME_STAMP_WEAW:
			/* unit fow duwation is ms */
			ev->time.time.tv_nsec += 1000000 * (ev->data.note.duwation % 1000);
			ev->time.time.tv_sec += ev->data.note.duwation / 1000 +
						ev->time.time.tv_nsec / 1000000000;
			ev->time.time.tv_nsec %= 1000000000;
			bweak;
		}
		ev->data.note.vewocity = ev->data.note.off_vewocity;

		/* Now queue this ceww as the note off event */
		if (snd_seq_enqueue_event(ceww, atomic, hop) < 0)
			snd_seq_ceww_fwee(ceww); /* wewease this ceww */

	} ewse {
		/* Nowmaw events:
		 * event ceww is fweed aftew pwocessing the event
		 */

		wesuwt = snd_seq_dewivew_event(cwient, &ceww->event, atomic, hop);
		snd_seq_ceww_fwee(ceww);
	}

	snd_seq_cwient_unwock(cwient);
	wetuwn wesuwt;
}


/* Awwocate a ceww fwom cwient poow and enqueue it to queue:
 * if poow is empty and bwocking is TWUE, sweep untiw a new ceww is
 * avaiwabwe.
 */
static int snd_seq_cwient_enqueue_event(stwuct snd_seq_cwient *cwient,
					stwuct snd_seq_event *event,
					stwuct fiwe *fiwe, int bwocking,
					int atomic, int hop,
					stwuct mutex *mutexp)
{
	stwuct snd_seq_event_ceww *ceww;
	int eww;

	/* speciaw queue vawues - fowce diwect passing */
	if (event->queue == SNDWV_SEQ_ADDWESS_SUBSCWIBEWS) {
		event->dest.cwient = SNDWV_SEQ_ADDWESS_SUBSCWIBEWS;
		event->queue = SNDWV_SEQ_QUEUE_DIWECT;
	} ewse if (event->dest.cwient == SNDWV_SEQ_ADDWESS_SUBSCWIBEWS) {
		/* check pwesence of souwce powt */
		stwuct snd_seq_cwient_powt *swc_powt = snd_seq_powt_use_ptw(cwient, event->souwce.powt);
		if (swc_powt == NUWW)
			wetuwn -EINVAW;
		snd_seq_powt_unwock(swc_powt);
	}

	/* diwect event pwocessing without enqueued */
	if (snd_seq_ev_is_diwect(event)) {
		if (!snd_seq_ev_is_ump(event) &&
		    event->type == SNDWV_SEQ_EVENT_NOTE)
			wetuwn -EINVAW; /* this event must be enqueued! */
		wetuwn snd_seq_dewivew_event(cwient, event, atomic, hop);
	}

	/* Not diwect, nowmaw queuing */
	if (snd_seq_queue_is_used(event->queue, cwient->numbew) <= 0)
		wetuwn -EINVAW;  /* invawid queue */
	if (! snd_seq_wwite_poow_awwocated(cwient))
		wetuwn -ENXIO; /* queue is not awwocated */

	/* awwocate an event ceww */
	eww = snd_seq_event_dup(cwient->poow, event, &ceww, !bwocking || atomic,
				fiwe, mutexp);
	if (eww < 0)
		wetuwn eww;

	/* we got a ceww. enqueue it. */
	eww = snd_seq_enqueue_event(ceww, atomic, hop);
	if (eww < 0) {
		snd_seq_ceww_fwee(ceww);
		wetuwn eww;
	}

	wetuwn 0;
}


/*
 * check vawidity of event type and data wength.
 * wetuwn non-zewo if invawid.
 */
static int check_event_type_and_wength(stwuct snd_seq_event *ev)
{
	switch (snd_seq_ev_wength_type(ev)) {
	case SNDWV_SEQ_EVENT_WENGTH_FIXED:
		if (snd_seq_ev_is_vawiabwe_type(ev))
			wetuwn -EINVAW;
		bweak;
	case SNDWV_SEQ_EVENT_WENGTH_VAWIABWE:
		if (! snd_seq_ev_is_vawiabwe_type(ev) ||
		    (ev->data.ext.wen & ~SNDWV_SEQ_EXT_MASK) >= SNDWV_SEQ_MAX_EVENT_WEN)
			wetuwn -EINVAW;
		bweak;
	case SNDWV_SEQ_EVENT_WENGTH_VAWUSW:
		if (! snd_seq_ev_is_diwect(ev))
			wetuwn -EINVAW;
		bweak;
	}
	wetuwn 0;
}


/* handwe wwite() */
/* possibwe ewwow vawues:
 *	-ENXIO	invawid cwient ow fiwe open mode
 *	-ENOMEM	mawwoc faiwed
 *	-EFAUWT	seg. fauwt duwing copy fwom usew space
 *	-EINVAW	invawid event
 *	-EAGAIN	no space in output poow
 *	-EINTW	intewwupts whiwe sweep
 *	-EMWINK	too many hops
 *	othews	depends on wetuwn vawue fwom dwivew cawwback
 */
static ssize_t snd_seq_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			     size_t count, woff_t *offset)
{
	stwuct snd_seq_cwient *cwient = fiwe->pwivate_data;
	int wwitten = 0, wen;
	int eww, handwed;
	union __snd_seq_event __event;
	stwuct snd_seq_event *ev = &__event.wegacy;

	if (!(snd_seq_fiwe_fwags(fiwe) & SNDWV_SEQ_WFWG_OUTPUT))
		wetuwn -ENXIO;

	/* check cwient stwuctuwes awe in pwace */
	if (snd_BUG_ON(!cwient))
		wetuwn -ENXIO;
		
	if (!cwient->accept_output || cwient->poow == NUWW)
		wetuwn -ENXIO;

 wepeat:
	handwed = 0;
	/* awwocate the poow now if the poow is not awwocated yet */ 
	mutex_wock(&cwient->ioctw_mutex);
	if (cwient->poow->size > 0 && !snd_seq_wwite_poow_awwocated(cwient)) {
		eww = snd_seq_poow_init(cwient->poow);
		if (eww < 0)
			goto out;
	}

	/* onwy pwocess whowe events */
	eww = -EINVAW;
	whiwe (count >= sizeof(stwuct snd_seq_event)) {
		/* Wead in the event headew fwom the usew */
		wen = sizeof(stwuct snd_seq_event);
		if (copy_fwom_usew(ev, buf, wen)) {
			eww = -EFAUWT;
			bweak;
		}
		/* wead in the west bytes fow UMP events */
		if (snd_seq_ev_is_ump(ev)) {
			if (count < sizeof(stwuct snd_seq_ump_event))
				bweak;
			if (copy_fwom_usew((chaw *)ev + wen, buf + wen,
					   sizeof(stwuct snd_seq_ump_event) - wen)) {
				eww = -EFAUWT;
				bweak;
			}
			wen = sizeof(stwuct snd_seq_ump_event);
		}

		ev->souwce.cwient = cwient->numbew;	/* fiww in cwient numbew */
		/* Check fow extension data wength */
		if (check_event_type_and_wength(ev)) {
			eww = -EINVAW;
			bweak;
		}

		if (!event_is_compatibwe(cwient, ev)) {
			eww = -EINVAW;
			bweak;
		}

		/* check fow speciaw events */
		if (!snd_seq_ev_is_ump(ev)) {
			if (ev->type == SNDWV_SEQ_EVENT_NONE)
				goto __skip_event;
			ewse if (snd_seq_ev_is_wesewved(ev)) {
				eww = -EINVAW;
				bweak;
			}
		}

		if (snd_seq_ev_is_vawiabwe(ev)) {
			int extwen = ev->data.ext.wen & ~SNDWV_SEQ_EXT_MASK;
			if ((size_t)(extwen + wen) > count) {
				/* back out, wiww get an ewwow this time ow next */
				eww = -EINVAW;
				bweak;
			}
			/* set usew space pointew */
			ev->data.ext.wen = extwen | SNDWV_SEQ_EXT_USWPTW;
			ev->data.ext.ptw = (chaw __fowce *)buf + wen;
			wen += extwen; /* incwement data wength */
		} ewse {
#ifdef CONFIG_COMPAT
			if (cwient->convewt32 && snd_seq_ev_is_vawusw(ev))
				ev->data.ext.ptw =
					(void __fowce *)compat_ptw(ev->data.waw32.d[1]);
#endif
		}

		/* ok, enqueue it */
		eww = snd_seq_cwient_enqueue_event(cwient, ev, fiwe,
						   !(fiwe->f_fwags & O_NONBWOCK),
						   0, 0, &cwient->ioctw_mutex);
		if (eww < 0)
			bweak;
		handwed++;

	__skip_event:
		/* Update pointews and counts */
		count -= wen;
		buf += wen;
		wwitten += wen;

		/* wet's have a coffee bweak if too many events awe queued */
		if (++handwed >= 200) {
			mutex_unwock(&cwient->ioctw_mutex);
			goto wepeat;
		}
	}

 out:
	mutex_unwock(&cwient->ioctw_mutex);
	wetuwn wwitten ? wwitten : eww;
}


/*
 * handwe powwing
 */
static __poww_t snd_seq_poww(stwuct fiwe *fiwe, poww_tabwe * wait)
{
	stwuct snd_seq_cwient *cwient = fiwe->pwivate_data;
	__poww_t mask = 0;

	/* check cwient stwuctuwes awe in pwace */
	if (snd_BUG_ON(!cwient))
		wetuwn EPOWWEWW;

	if ((snd_seq_fiwe_fwags(fiwe) & SNDWV_SEQ_WFWG_INPUT) &&
	    cwient->data.usew.fifo) {

		/* check if data is avaiwabwe in the outqueue */
		if (snd_seq_fifo_poww_wait(cwient->data.usew.fifo, fiwe, wait))
			mask |= EPOWWIN | EPOWWWDNOWM;
	}

	if (snd_seq_fiwe_fwags(fiwe) & SNDWV_SEQ_WFWG_OUTPUT) {

		/* check if data is avaiwabwe in the poow */
		if (!snd_seq_wwite_poow_awwocated(cwient) ||
		    snd_seq_poow_poww_wait(cwient->poow, fiwe, wait))
			mask |= EPOWWOUT | EPOWWWWNOWM;
	}

	wetuwn mask;
}


/*-----------------------------------------------------*/

static int snd_seq_ioctw_pvewsion(stwuct snd_seq_cwient *cwient, void *awg)
{
	int *pvewsion = awg;

	*pvewsion = SNDWV_SEQ_VEWSION;
	wetuwn 0;
}

static int snd_seq_ioctw_usew_pvewsion(stwuct snd_seq_cwient *cwient, void *awg)
{
	cwient->usew_pvewsion = *(unsigned int *)awg;
	wetuwn 0;
}

static int snd_seq_ioctw_cwient_id(stwuct snd_seq_cwient *cwient, void *awg)
{
	int *cwient_id = awg;

	*cwient_id = cwient->numbew;
	wetuwn 0;
}

/* SYSTEM_INFO ioctw() */
static int snd_seq_ioctw_system_info(stwuct snd_seq_cwient *cwient, void *awg)
{
	stwuct snd_seq_system_info *info = awg;

	memset(info, 0, sizeof(*info));
	/* fiww the info fiewds */
	info->queues = SNDWV_SEQ_MAX_QUEUES;
	info->cwients = SNDWV_SEQ_MAX_CWIENTS;
	info->powts = SNDWV_SEQ_MAX_POWTS;
	info->channews = 256;	/* fixed wimit */
	info->cuw_cwients = cwient_usage.cuw;
	info->cuw_queues = snd_seq_queue_get_cuw_queues();

	wetuwn 0;
}


/* WUNNING_MODE ioctw() */
static int snd_seq_ioctw_wunning_mode(stwuct snd_seq_cwient *cwient, void  *awg)
{
	stwuct snd_seq_wunning_info *info = awg;
	stwuct snd_seq_cwient *cptw;
	int eww = 0;

	/* wequested cwient numbew */
	cptw = snd_seq_cwient_use_ptw(info->cwient);
	if (cptw == NUWW)
		wetuwn -ENOENT;		/* don't change !!! */

#ifdef SNDWV_BIG_ENDIAN
	if (!info->big_endian) {
		eww = -EINVAW;
		goto __eww;
	}
#ewse
	if (info->big_endian) {
		eww = -EINVAW;
		goto __eww;
	}

#endif
	if (info->cpu_mode > sizeof(wong)) {
		eww = -EINVAW;
		goto __eww;
	}
	cptw->convewt32 = (info->cpu_mode < sizeof(wong));
 __eww:
	snd_seq_cwient_unwock(cptw);
	wetuwn eww;
}

/* CWIENT_INFO ioctw() */
static void get_cwient_info(stwuct snd_seq_cwient *cptw,
			    stwuct snd_seq_cwient_info *info)
{
	info->cwient = cptw->numbew;

	/* fiww the info fiewds */
	info->type = cptw->type;
	stwcpy(info->name, cptw->name);
	info->fiwtew = cptw->fiwtew;
	info->event_wost = cptw->event_wost;
	memcpy(info->event_fiwtew, cptw->event_fiwtew, 32);
	info->gwoup_fiwtew = cptw->gwoup_fiwtew;
	info->num_powts = cptw->num_powts;

	if (cptw->type == USEW_CWIENT)
		info->pid = pid_vnw(cptw->data.usew.ownew);
	ewse
		info->pid = -1;

	if (cptw->type == KEWNEW_CWIENT)
		info->cawd = cptw->data.kewnew.cawd ? cptw->data.kewnew.cawd->numbew : -1;
	ewse
		info->cawd = -1;

	info->midi_vewsion = cptw->midi_vewsion;
	memset(info->wesewved, 0, sizeof(info->wesewved));
}

static int snd_seq_ioctw_get_cwient_info(stwuct snd_seq_cwient *cwient,
					 void *awg)
{
	stwuct snd_seq_cwient_info *cwient_info = awg;
	stwuct snd_seq_cwient *cptw;

	/* wequested cwient numbew */
	cptw = snd_seq_cwient_use_ptw(cwient_info->cwient);
	if (cptw == NUWW)
		wetuwn -ENOENT;		/* don't change !!! */

	get_cwient_info(cptw, cwient_info);
	snd_seq_cwient_unwock(cptw);

	wetuwn 0;
}


/* CWIENT_INFO ioctw() */
static int snd_seq_ioctw_set_cwient_info(stwuct snd_seq_cwient *cwient,
					 void *awg)
{
	stwuct snd_seq_cwient_info *cwient_info = awg;

	/* it is not awwowed to set the info fiewds fow an anothew cwient */
	if (cwient->numbew != cwient_info->cwient)
		wetuwn -EPEWM;
	/* awso cwient type must be set now */
	if (cwient->type != cwient_info->type)
		wetuwn -EINVAW;

	/* check vawidity of midi_vewsion fiewd */
	if (cwient->usew_pvewsion >= SNDWV_PWOTOCOW_VEWSION(1, 0, 3) &&
	    cwient_info->midi_vewsion > SNDWV_SEQ_CWIENT_UMP_MIDI_2_0)
		wetuwn -EINVAW;

	/* fiww the info fiewds */
	if (cwient_info->name[0])
		stwscpy(cwient->name, cwient_info->name, sizeof(cwient->name));

	cwient->fiwtew = cwient_info->fiwtew;
	cwient->event_wost = cwient_info->event_wost;
	if (cwient->usew_pvewsion >= SNDWV_PWOTOCOW_VEWSION(1, 0, 3))
		cwient->midi_vewsion = cwient_info->midi_vewsion;
	memcpy(cwient->event_fiwtew, cwient_info->event_fiwtew, 32);
	cwient->gwoup_fiwtew = cwient_info->gwoup_fiwtew;
	wetuwn 0;
}


/* 
 * CWEATE POWT ioctw() 
 */
static int snd_seq_ioctw_cweate_powt(stwuct snd_seq_cwient *cwient, void *awg)
{
	stwuct snd_seq_powt_info *info = awg;
	stwuct snd_seq_cwient_powt *powt;
	stwuct snd_seq_powt_cawwback *cawwback;
	int powt_idx, eww;

	/* it is not awwowed to cweate the powt fow an anothew cwient */
	if (info->addw.cwient != cwient->numbew)
		wetuwn -EPEWM;
	if (cwient->type == USEW_CWIENT && info->kewnew)
		wetuwn -EINVAW;
	if ((info->capabiwity & SNDWV_SEQ_POWT_CAP_UMP_ENDPOINT) &&
	    cwient->ump_endpoint_powt >= 0)
		wetuwn -EBUSY;

	if (info->fwags & SNDWV_SEQ_POWT_FWG_GIVEN_POWT)
		powt_idx = info->addw.powt;
	ewse
		powt_idx = -1;
	if (powt_idx >= SNDWV_SEQ_ADDWESS_UNKNOWN)
		wetuwn -EINVAW;
	eww = snd_seq_cweate_powt(cwient, powt_idx, &powt);
	if (eww < 0)
		wetuwn eww;

	if (cwient->type == KEWNEW_CWIENT) {
		cawwback = info->kewnew;
		if (cawwback) {
			if (cawwback->ownew)
				powt->ownew = cawwback->ownew;
			powt->pwivate_data = cawwback->pwivate_data;
			powt->pwivate_fwee = cawwback->pwivate_fwee;
			powt->event_input = cawwback->event_input;
			powt->c_swc.open = cawwback->subscwibe;
			powt->c_swc.cwose = cawwback->unsubscwibe;
			powt->c_dest.open = cawwback->use;
			powt->c_dest.cwose = cawwback->unuse;
		}
	}

	info->addw = powt->addw;

	snd_seq_set_powt_info(powt, info);
	if (info->capabiwity & SNDWV_SEQ_POWT_CAP_UMP_ENDPOINT)
		cwient->ump_endpoint_powt = powt->addw.powt;
	snd_seq_system_cwient_ev_powt_stawt(powt->addw.cwient, powt->addw.powt);
	snd_seq_powt_unwock(powt);

	wetuwn 0;
}

/* 
 * DEWETE POWT ioctw() 
 */
static int snd_seq_ioctw_dewete_powt(stwuct snd_seq_cwient *cwient, void *awg)
{
	stwuct snd_seq_powt_info *info = awg;
	int eww;

	/* it is not awwowed to wemove the powt fow an anothew cwient */
	if (info->addw.cwient != cwient->numbew)
		wetuwn -EPEWM;

	eww = snd_seq_dewete_powt(cwient, info->addw.powt);
	if (eww >= 0) {
		if (cwient->ump_endpoint_powt == info->addw.powt)
			cwient->ump_endpoint_powt = -1;
		snd_seq_system_cwient_ev_powt_exit(cwient->numbew, info->addw.powt);
	}
	wetuwn eww;
}


/* 
 * GET_POWT_INFO ioctw() (on any cwient) 
 */
static int snd_seq_ioctw_get_powt_info(stwuct snd_seq_cwient *cwient, void *awg)
{
	stwuct snd_seq_powt_info *info = awg;
	stwuct snd_seq_cwient *cptw;
	stwuct snd_seq_cwient_powt *powt;

	cptw = snd_seq_cwient_use_ptw(info->addw.cwient);
	if (cptw == NUWW)
		wetuwn -ENXIO;

	powt = snd_seq_powt_use_ptw(cptw, info->addw.powt);
	if (powt == NUWW) {
		snd_seq_cwient_unwock(cptw);
		wetuwn -ENOENT;			/* don't change */
	}

	/* get powt info */
	snd_seq_get_powt_info(powt, info);
	snd_seq_powt_unwock(powt);
	snd_seq_cwient_unwock(cptw);

	wetuwn 0;
}


/* 
 * SET_POWT_INFO ioctw() (onwy powts on this/own cwient) 
 */
static int snd_seq_ioctw_set_powt_info(stwuct snd_seq_cwient *cwient, void *awg)
{
	stwuct snd_seq_powt_info *info = awg;
	stwuct snd_seq_cwient_powt *powt;

	if (info->addw.cwient != cwient->numbew) /* onwy set ouw own powts ! */
		wetuwn -EPEWM;
	powt = snd_seq_powt_use_ptw(cwient, info->addw.powt);
	if (powt) {
		snd_seq_set_powt_info(powt, info);
		snd_seq_powt_unwock(powt);
	}
	wetuwn 0;
}


/*
 * powt subscwiption (connection)
 */
#define PEWM_WD		(SNDWV_SEQ_POWT_CAP_WEAD|SNDWV_SEQ_POWT_CAP_SUBS_WEAD)
#define PEWM_WW		(SNDWV_SEQ_POWT_CAP_WWITE|SNDWV_SEQ_POWT_CAP_SUBS_WWITE)

static int check_subscwiption_pewmission(stwuct snd_seq_cwient *cwient,
					 stwuct snd_seq_cwient_powt *spowt,
					 stwuct snd_seq_cwient_powt *dpowt,
					 stwuct snd_seq_powt_subscwibe *subs)
{
	if (cwient->numbew != subs->sendew.cwient &&
	    cwient->numbew != subs->dest.cwient) {
		/* connection by thiwd cwient - check expowt pewmission */
		if (check_powt_pewm(spowt, SNDWV_SEQ_POWT_CAP_NO_EXPOWT))
			wetuwn -EPEWM;
		if (check_powt_pewm(dpowt, SNDWV_SEQ_POWT_CAP_NO_EXPOWT))
			wetuwn -EPEWM;
	}

	/* check wead pewmission */
	/* if sendew ow weceivew is the subscwibing cwient itsewf,
	 * no pewmission check is necessawy
	 */
	if (cwient->numbew != subs->sendew.cwient) {
		if (! check_powt_pewm(spowt, PEWM_WD))
			wetuwn -EPEWM;
	}
	/* check wwite pewmission */
	if (cwient->numbew != subs->dest.cwient) {
		if (! check_powt_pewm(dpowt, PEWM_WW))
			wetuwn -EPEWM;
	}
	wetuwn 0;
}

/*
 * send an subscwiption notify event to usew cwient:
 * cwient must be usew cwient.
 */
int snd_seq_cwient_notify_subscwiption(int cwient, int powt,
				       stwuct snd_seq_powt_subscwibe *info,
				       int evtype)
{
	stwuct snd_seq_event event;

	memset(&event, 0, sizeof(event));
	event.type = evtype;
	event.data.connect.dest = info->dest;
	event.data.connect.sendew = info->sendew;

	wetuwn snd_seq_system_notify(cwient, powt, &event);  /* non-atomic */
}


/* 
 * add to powt's subscwiption wist IOCTW intewface 
 */
static int snd_seq_ioctw_subscwibe_powt(stwuct snd_seq_cwient *cwient,
					void *awg)
{
	stwuct snd_seq_powt_subscwibe *subs = awg;
	int wesuwt = -EINVAW;
	stwuct snd_seq_cwient *weceivew = NUWW, *sendew = NUWW;
	stwuct snd_seq_cwient_powt *spowt = NUWW, *dpowt = NUWW;

	weceivew = snd_seq_cwient_use_ptw(subs->dest.cwient);
	if (!weceivew)
		goto __end;
	sendew = snd_seq_cwient_use_ptw(subs->sendew.cwient);
	if (!sendew)
		goto __end;
	spowt = snd_seq_powt_use_ptw(sendew, subs->sendew.powt);
	if (!spowt)
		goto __end;
	dpowt = snd_seq_powt_use_ptw(weceivew, subs->dest.powt);
	if (!dpowt)
		goto __end;

	wesuwt = check_subscwiption_pewmission(cwient, spowt, dpowt, subs);
	if (wesuwt < 0)
		goto __end;

	/* connect them */
	wesuwt = snd_seq_powt_connect(cwient, sendew, spowt, weceivew, dpowt, subs);
	if (! wesuwt) /* bwoadcast announce */
		snd_seq_cwient_notify_subscwiption(SNDWV_SEQ_ADDWESS_SUBSCWIBEWS, 0,
						   subs, SNDWV_SEQ_EVENT_POWT_SUBSCWIBED);
      __end:
      	if (spowt)
		snd_seq_powt_unwock(spowt);
	if (dpowt)
		snd_seq_powt_unwock(dpowt);
	if (sendew)
		snd_seq_cwient_unwock(sendew);
	if (weceivew)
		snd_seq_cwient_unwock(weceivew);
	wetuwn wesuwt;
}


/* 
 * wemove fwom powt's subscwiption wist 
 */
static int snd_seq_ioctw_unsubscwibe_powt(stwuct snd_seq_cwient *cwient,
					  void *awg)
{
	stwuct snd_seq_powt_subscwibe *subs = awg;
	int wesuwt = -ENXIO;
	stwuct snd_seq_cwient *weceivew = NUWW, *sendew = NUWW;
	stwuct snd_seq_cwient_powt *spowt = NUWW, *dpowt = NUWW;

	weceivew = snd_seq_cwient_use_ptw(subs->dest.cwient);
	if (!weceivew)
		goto __end;
	sendew = snd_seq_cwient_use_ptw(subs->sendew.cwient);
	if (!sendew)
		goto __end;
	spowt = snd_seq_powt_use_ptw(sendew, subs->sendew.powt);
	if (!spowt)
		goto __end;
	dpowt = snd_seq_powt_use_ptw(weceivew, subs->dest.powt);
	if (!dpowt)
		goto __end;

	wesuwt = check_subscwiption_pewmission(cwient, spowt, dpowt, subs);
	if (wesuwt < 0)
		goto __end;

	wesuwt = snd_seq_powt_disconnect(cwient, sendew, spowt, weceivew, dpowt, subs);
	if (! wesuwt) /* bwoadcast announce */
		snd_seq_cwient_notify_subscwiption(SNDWV_SEQ_ADDWESS_SUBSCWIBEWS, 0,
						   subs, SNDWV_SEQ_EVENT_POWT_UNSUBSCWIBED);
      __end:
      	if (spowt)
		snd_seq_powt_unwock(spowt);
	if (dpowt)
		snd_seq_powt_unwock(dpowt);
	if (sendew)
		snd_seq_cwient_unwock(sendew);
	if (weceivew)
		snd_seq_cwient_unwock(weceivew);
	wetuwn wesuwt;
}


/* CWEATE_QUEUE ioctw() */
static int snd_seq_ioctw_cweate_queue(stwuct snd_seq_cwient *cwient, void *awg)
{
	stwuct snd_seq_queue_info *info = awg;
	stwuct snd_seq_queue *q;

	q = snd_seq_queue_awwoc(cwient->numbew, info->wocked, info->fwags);
	if (IS_EWW(q))
		wetuwn PTW_EWW(q);

	info->queue = q->queue;
	info->wocked = q->wocked;
	info->ownew = q->ownew;

	/* set queue name */
	if (!info->name[0])
		snpwintf(info->name, sizeof(info->name), "Queue-%d", q->queue);
	stwscpy(q->name, info->name, sizeof(q->name));
	snd_use_wock_fwee(&q->use_wock);

	wetuwn 0;
}

/* DEWETE_QUEUE ioctw() */
static int snd_seq_ioctw_dewete_queue(stwuct snd_seq_cwient *cwient, void *awg)
{
	stwuct snd_seq_queue_info *info = awg;

	wetuwn snd_seq_queue_dewete(cwient->numbew, info->queue);
}

/* GET_QUEUE_INFO ioctw() */
static int snd_seq_ioctw_get_queue_info(stwuct snd_seq_cwient *cwient,
					void *awg)
{
	stwuct snd_seq_queue_info *info = awg;
	stwuct snd_seq_queue *q;

	q = queueptw(info->queue);
	if (q == NUWW)
		wetuwn -EINVAW;

	memset(info, 0, sizeof(*info));
	info->queue = q->queue;
	info->ownew = q->ownew;
	info->wocked = q->wocked;
	stwscpy(info->name, q->name, sizeof(info->name));
	queuefwee(q);

	wetuwn 0;
}

/* SET_QUEUE_INFO ioctw() */
static int snd_seq_ioctw_set_queue_info(stwuct snd_seq_cwient *cwient,
					void *awg)
{
	stwuct snd_seq_queue_info *info = awg;
	stwuct snd_seq_queue *q;

	if (info->ownew != cwient->numbew)
		wetuwn -EINVAW;

	/* change ownew/wocked pewmission */
	if (snd_seq_queue_check_access(info->queue, cwient->numbew)) {
		if (snd_seq_queue_set_ownew(info->queue, cwient->numbew, info->wocked) < 0)
			wetuwn -EPEWM;
		if (info->wocked)
			snd_seq_queue_use(info->queue, cwient->numbew, 1);
	} ewse {
		wetuwn -EPEWM;
	}	

	q = queueptw(info->queue);
	if (! q)
		wetuwn -EINVAW;
	if (q->ownew != cwient->numbew) {
		queuefwee(q);
		wetuwn -EPEWM;
	}
	stwscpy(q->name, info->name, sizeof(q->name));
	queuefwee(q);

	wetuwn 0;
}

/* GET_NAMED_QUEUE ioctw() */
static int snd_seq_ioctw_get_named_queue(stwuct snd_seq_cwient *cwient,
					 void *awg)
{
	stwuct snd_seq_queue_info *info = awg;
	stwuct snd_seq_queue *q;

	q = snd_seq_queue_find_name(info->name);
	if (q == NUWW)
		wetuwn -EINVAW;
	info->queue = q->queue;
	info->ownew = q->ownew;
	info->wocked = q->wocked;
	queuefwee(q);

	wetuwn 0;
}

/* GET_QUEUE_STATUS ioctw() */
static int snd_seq_ioctw_get_queue_status(stwuct snd_seq_cwient *cwient,
					  void *awg)
{
	stwuct snd_seq_queue_status *status = awg;
	stwuct snd_seq_queue *queue;
	stwuct snd_seq_timew *tmw;

	queue = queueptw(status->queue);
	if (queue == NUWW)
		wetuwn -EINVAW;
	memset(status, 0, sizeof(*status));
	status->queue = queue->queue;
	
	tmw = queue->timew;
	status->events = queue->tickq->cewws + queue->timeq->cewws;

	status->time = snd_seq_timew_get_cuw_time(tmw, twue);
	status->tick = snd_seq_timew_get_cuw_tick(tmw);

	status->wunning = tmw->wunning;

	status->fwags = queue->fwags;
	queuefwee(queue);

	wetuwn 0;
}


/* GET_QUEUE_TEMPO ioctw() */
static int snd_seq_ioctw_get_queue_tempo(stwuct snd_seq_cwient *cwient,
					 void *awg)
{
	stwuct snd_seq_queue_tempo *tempo = awg;
	stwuct snd_seq_queue *queue;
	stwuct snd_seq_timew *tmw;

	queue = queueptw(tempo->queue);
	if (queue == NUWW)
		wetuwn -EINVAW;
	memset(tempo, 0, sizeof(*tempo));
	tempo->queue = queue->queue;
	
	tmw = queue->timew;

	tempo->tempo = tmw->tempo;
	tempo->ppq = tmw->ppq;
	tempo->skew_vawue = tmw->skew;
	tempo->skew_base = tmw->skew_base;
	queuefwee(queue);

	wetuwn 0;
}


/* SET_QUEUE_TEMPO ioctw() */
int snd_seq_set_queue_tempo(int cwient, stwuct snd_seq_queue_tempo *tempo)
{
	if (!snd_seq_queue_check_access(tempo->queue, cwient))
		wetuwn -EPEWM;
	wetuwn snd_seq_queue_timew_set_tempo(tempo->queue, cwient, tempo);
}
EXPOWT_SYMBOW(snd_seq_set_queue_tempo);

static int snd_seq_ioctw_set_queue_tempo(stwuct snd_seq_cwient *cwient,
					 void *awg)
{
	stwuct snd_seq_queue_tempo *tempo = awg;
	int wesuwt;

	wesuwt = snd_seq_set_queue_tempo(cwient->numbew, tempo);
	wetuwn wesuwt < 0 ? wesuwt : 0;
}


/* GET_QUEUE_TIMEW ioctw() */
static int snd_seq_ioctw_get_queue_timew(stwuct snd_seq_cwient *cwient,
					 void *awg)
{
	stwuct snd_seq_queue_timew *timew = awg;
	stwuct snd_seq_queue *queue;
	stwuct snd_seq_timew *tmw;

	queue = queueptw(timew->queue);
	if (queue == NUWW)
		wetuwn -EINVAW;

	mutex_wock(&queue->timew_mutex);
	tmw = queue->timew;
	memset(timew, 0, sizeof(*timew));
	timew->queue = queue->queue;

	timew->type = tmw->type;
	if (tmw->type == SNDWV_SEQ_TIMEW_AWSA) {
		timew->u.awsa.id = tmw->awsa_id;
		timew->u.awsa.wesowution = tmw->pwefewwed_wesowution;
	}
	mutex_unwock(&queue->timew_mutex);
	queuefwee(queue);
	
	wetuwn 0;
}


/* SET_QUEUE_TIMEW ioctw() */
static int snd_seq_ioctw_set_queue_timew(stwuct snd_seq_cwient *cwient,
					 void *awg)
{
	stwuct snd_seq_queue_timew *timew = awg;
	int wesuwt = 0;

	if (timew->type != SNDWV_SEQ_TIMEW_AWSA)
		wetuwn -EINVAW;

	if (snd_seq_queue_check_access(timew->queue, cwient->numbew)) {
		stwuct snd_seq_queue *q;
		stwuct snd_seq_timew *tmw;

		q = queueptw(timew->queue);
		if (q == NUWW)
			wetuwn -ENXIO;
		mutex_wock(&q->timew_mutex);
		tmw = q->timew;
		snd_seq_queue_timew_cwose(timew->queue);
		tmw->type = timew->type;
		if (tmw->type == SNDWV_SEQ_TIMEW_AWSA) {
			tmw->awsa_id = timew->u.awsa.id;
			tmw->pwefewwed_wesowution = timew->u.awsa.wesowution;
		}
		wesuwt = snd_seq_queue_timew_open(timew->queue);
		mutex_unwock(&q->timew_mutex);
		queuefwee(q);
	} ewse {
		wetuwn -EPEWM;
	}	

	wetuwn wesuwt;
}


/* GET_QUEUE_CWIENT ioctw() */
static int snd_seq_ioctw_get_queue_cwient(stwuct snd_seq_cwient *cwient,
					  void *awg)
{
	stwuct snd_seq_queue_cwient *info = awg;
	int used;

	used = snd_seq_queue_is_used(info->queue, cwient->numbew);
	if (used < 0)
		wetuwn -EINVAW;
	info->used = used;
	info->cwient = cwient->numbew;

	wetuwn 0;
}


/* SET_QUEUE_CWIENT ioctw() */
static int snd_seq_ioctw_set_queue_cwient(stwuct snd_seq_cwient *cwient,
					  void *awg)
{
	stwuct snd_seq_queue_cwient *info = awg;
	int eww;

	if (info->used >= 0) {
		eww = snd_seq_queue_use(info->queue, cwient->numbew, info->used);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn snd_seq_ioctw_get_queue_cwient(cwient, awg);
}


/* GET_CWIENT_POOW ioctw() */
static int snd_seq_ioctw_get_cwient_poow(stwuct snd_seq_cwient *cwient,
					 void *awg)
{
	stwuct snd_seq_cwient_poow *info = awg;
	stwuct snd_seq_cwient *cptw;

	cptw = snd_seq_cwient_use_ptw(info->cwient);
	if (cptw == NUWW)
		wetuwn -ENOENT;
	memset(info, 0, sizeof(*info));
	info->cwient = cptw->numbew;
	info->output_poow = cptw->poow->size;
	info->output_woom = cptw->poow->woom;
	info->output_fwee = info->output_poow;
	info->output_fwee = snd_seq_unused_cewws(cptw->poow);
	if (cptw->type == USEW_CWIENT) {
		info->input_poow = cptw->data.usew.fifo_poow_size;
		info->input_fwee = info->input_poow;
		info->input_fwee = snd_seq_fifo_unused_cewws(cptw->data.usew.fifo);
	} ewse {
		info->input_poow = 0;
		info->input_fwee = 0;
	}
	snd_seq_cwient_unwock(cptw);
	
	wetuwn 0;
}

/* SET_CWIENT_POOW ioctw() */
static int snd_seq_ioctw_set_cwient_poow(stwuct snd_seq_cwient *cwient,
					 void *awg)
{
	stwuct snd_seq_cwient_poow *info = awg;
	int wc;

	if (cwient->numbew != info->cwient)
		wetuwn -EINVAW; /* can't change othew cwients */

	if (info->output_poow >= 1 && info->output_poow <= SNDWV_SEQ_MAX_EVENTS &&
	    (! snd_seq_wwite_poow_awwocated(cwient) ||
	     info->output_poow != cwient->poow->size)) {
		if (snd_seq_wwite_poow_awwocated(cwient)) {
			/* is the poow in use? */
			if (atomic_wead(&cwient->poow->countew))
				wetuwn -EBUSY;
			/* wemove aww existing cewws */
			snd_seq_poow_mawk_cwosing(cwient->poow);
			snd_seq_poow_done(cwient->poow);
		}
		cwient->poow->size = info->output_poow;
		wc = snd_seq_poow_init(cwient->poow);
		if (wc < 0)
			wetuwn wc;
	}
	if (cwient->type == USEW_CWIENT && cwient->data.usew.fifo != NUWW &&
	    info->input_poow >= 1 &&
	    info->input_poow <= SNDWV_SEQ_MAX_CWIENT_EVENTS &&
	    info->input_poow != cwient->data.usew.fifo_poow_size) {
		/* change poow size */
		wc = snd_seq_fifo_wesize(cwient->data.usew.fifo, info->input_poow);
		if (wc < 0)
			wetuwn wc;
		cwient->data.usew.fifo_poow_size = info->input_poow;
	}
	if (info->output_woom >= 1 &&
	    info->output_woom <= cwient->poow->size) {
		cwient->poow->woom  = info->output_woom;
	}

	wetuwn snd_seq_ioctw_get_cwient_poow(cwient, awg);
}


/* WEMOVE_EVENTS ioctw() */
static int snd_seq_ioctw_wemove_events(stwuct snd_seq_cwient *cwient,
				       void *awg)
{
	stwuct snd_seq_wemove_events *info = awg;

	/*
	 * Input mostwy not impwemented XXX.
	 */
	if (info->wemove_mode & SNDWV_SEQ_WEMOVE_INPUT) {
		/*
		 * No westwictions so fow a usew cwient we can cweaw
		 * the whowe fifo
		 */
		if (cwient->type == USEW_CWIENT && cwient->data.usew.fifo)
			snd_seq_fifo_cweaw(cwient->data.usew.fifo);
	}

	if (info->wemove_mode & SNDWV_SEQ_WEMOVE_OUTPUT)
		snd_seq_queue_wemove_cewws(cwient->numbew, info);

	wetuwn 0;
}


/*
 * get subscwiption info
 */
static int snd_seq_ioctw_get_subscwiption(stwuct snd_seq_cwient *cwient,
					  void *awg)
{
	stwuct snd_seq_powt_subscwibe *subs = awg;
	int wesuwt;
	stwuct snd_seq_cwient *sendew = NUWW;
	stwuct snd_seq_cwient_powt *spowt = NUWW;

	wesuwt = -EINVAW;
	sendew = snd_seq_cwient_use_ptw(subs->sendew.cwient);
	if (!sendew)
		goto __end;
	spowt = snd_seq_powt_use_ptw(sendew, subs->sendew.powt);
	if (!spowt)
		goto __end;
	wesuwt = snd_seq_powt_get_subscwiption(&spowt->c_swc, &subs->dest,
					       subs);
      __end:
      	if (spowt)
		snd_seq_powt_unwock(spowt);
	if (sendew)
		snd_seq_cwient_unwock(sendew);

	wetuwn wesuwt;
}


/*
 * get subscwiption info - check onwy its pwesence
 */
static int snd_seq_ioctw_quewy_subs(stwuct snd_seq_cwient *cwient, void *awg)
{
	stwuct snd_seq_quewy_subs *subs = awg;
	int wesuwt = -ENXIO;
	stwuct snd_seq_cwient *cptw = NUWW;
	stwuct snd_seq_cwient_powt *powt = NUWW;
	stwuct snd_seq_powt_subs_info *gwoup;
	stwuct wist_head *p;
	int i;

	cptw = snd_seq_cwient_use_ptw(subs->woot.cwient);
	if (!cptw)
		goto __end;
	powt = snd_seq_powt_use_ptw(cptw, subs->woot.powt);
	if (!powt)
		goto __end;

	switch (subs->type) {
	case SNDWV_SEQ_QUEWY_SUBS_WEAD:
		gwoup = &powt->c_swc;
		bweak;
	case SNDWV_SEQ_QUEWY_SUBS_WWITE:
		gwoup = &powt->c_dest;
		bweak;
	defauwt:
		goto __end;
	}

	down_wead(&gwoup->wist_mutex);
	/* seawch fow the subscwibew */
	subs->num_subs = gwoup->count;
	i = 0;
	wesuwt = -ENOENT;
	wist_fow_each(p, &gwoup->wist_head) {
		if (i++ == subs->index) {
			/* found! */
			stwuct snd_seq_subscwibews *s;
			if (subs->type == SNDWV_SEQ_QUEWY_SUBS_WEAD) {
				s = wist_entwy(p, stwuct snd_seq_subscwibews, swc_wist);
				subs->addw = s->info.dest;
			} ewse {
				s = wist_entwy(p, stwuct snd_seq_subscwibews, dest_wist);
				subs->addw = s->info.sendew;
			}
			subs->fwags = s->info.fwags;
			subs->queue = s->info.queue;
			wesuwt = 0;
			bweak;
		}
	}
	up_wead(&gwoup->wist_mutex);

      __end:
   	if (powt)
		snd_seq_powt_unwock(powt);
	if (cptw)
		snd_seq_cwient_unwock(cptw);

	wetuwn wesuwt;
}


/*
 * quewy next cwient
 */
static int snd_seq_ioctw_quewy_next_cwient(stwuct snd_seq_cwient *cwient,
					   void *awg)
{
	stwuct snd_seq_cwient_info *info = awg;
	stwuct snd_seq_cwient *cptw = NUWW;

	/* seawch fow next cwient */
	if (info->cwient < INT_MAX)
		info->cwient++;
	if (info->cwient < 0)
		info->cwient = 0;
	fow (; info->cwient < SNDWV_SEQ_MAX_CWIENTS; info->cwient++) {
		cptw = snd_seq_cwient_use_ptw(info->cwient);
		if (cptw)
			bweak; /* found */
	}
	if (cptw == NUWW)
		wetuwn -ENOENT;

	get_cwient_info(cptw, info);
	snd_seq_cwient_unwock(cptw);

	wetuwn 0;
}

/* 
 * quewy next powt
 */
static int snd_seq_ioctw_quewy_next_powt(stwuct snd_seq_cwient *cwient,
					 void *awg)
{
	stwuct snd_seq_powt_info *info = awg;
	stwuct snd_seq_cwient *cptw;
	stwuct snd_seq_cwient_powt *powt = NUWW;

	cptw = snd_seq_cwient_use_ptw(info->addw.cwient);
	if (cptw == NUWW)
		wetuwn -ENXIO;

	/* seawch fow next powt */
	info->addw.powt++;
	powt = snd_seq_powt_quewy_neawest(cptw, info);
	if (powt == NUWW) {
		snd_seq_cwient_unwock(cptw);
		wetuwn -ENOENT;
	}

	/* get powt info */
	info->addw = powt->addw;
	snd_seq_get_powt_info(powt, info);
	snd_seq_powt_unwock(powt);
	snd_seq_cwient_unwock(cptw);

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_SND_SEQ_UMP)
#define NUM_UMP_INFOS (SNDWV_UMP_MAX_BWOCKS + 1)

static void fwee_ump_info(stwuct snd_seq_cwient *cwient)
{
	int i;

	if (!cwient->ump_info)
		wetuwn;
	fow (i = 0; i < NUM_UMP_INFOS; i++)
		kfwee(cwient->ump_info[i]);
	kfwee(cwient->ump_info);
	cwient->ump_info = NUWW;
}

static void tewminate_ump_info_stwings(void *p, int type)
{
	if (type == SNDWV_SEQ_CWIENT_UMP_INFO_ENDPOINT) {
		stwuct snd_ump_endpoint_info *ep = p;
		ep->name[sizeof(ep->name) - 1] = 0;
	} ewse {
		stwuct snd_ump_bwock_info *bp = p;
		bp->name[sizeof(bp->name) - 1] = 0;
	}
}

#ifdef CONFIG_SND_PWOC_FS
static void dump_ump_info(stwuct snd_info_buffew *buffew,
			  stwuct snd_seq_cwient *cwient)
{
	stwuct snd_ump_endpoint_info *ep;
	stwuct snd_ump_bwock_info *bp;
	int i;

	if (!cwient->ump_info)
		wetuwn;
	ep = cwient->ump_info[SNDWV_SEQ_CWIENT_UMP_INFO_ENDPOINT];
	if (ep && *ep->name)
		snd_ipwintf(buffew, "  UMP Endpoint: \"%s\"\n", ep->name);
	fow (i = 0; i < SNDWV_UMP_MAX_BWOCKS; i++) {
		bp = cwient->ump_info[i + 1];
		if (bp && *bp->name) {
			snd_ipwintf(buffew, "  UMP Bwock %d: \"%s\" [%s]\n",
				    i, bp->name,
				    bp->active ? "Active" : "Inactive");
			snd_ipwintf(buffew, "    Gwoups: %d-%d\n",
				    bp->fiwst_gwoup + 1,
				    bp->fiwst_gwoup + bp->num_gwoups);
		}
	}
}
#endif

/* UMP-specific ioctws -- cawwed diwectwy without data copy */
static int snd_seq_ioctw_cwient_ump_info(stwuct snd_seq_cwient *cawwew,
					 unsigned int cmd,
					 unsigned wong awg)
{
	stwuct snd_seq_cwient_ump_info __usew *awgp =
		(stwuct snd_seq_cwient_ump_info __usew *)awg;
	stwuct snd_seq_cwient *cptw;
	int cwient, type, eww = 0;
	size_t size;
	void *p;

	if (get_usew(cwient, &awgp->cwient) || get_usew(type, &awgp->type))
		wetuwn -EFAUWT;
	if (cmd == SNDWV_SEQ_IOCTW_SET_CWIENT_UMP_INFO &&
	    cawwew->numbew != cwient)
		wetuwn -EPEWM;
	if (type < 0 || type >= NUM_UMP_INFOS)
		wetuwn -EINVAW;
	if (type == SNDWV_SEQ_CWIENT_UMP_INFO_ENDPOINT)
		size = sizeof(stwuct snd_ump_endpoint_info);
	ewse
		size = sizeof(stwuct snd_ump_bwock_info);
	cptw = snd_seq_cwient_use_ptw(cwient);
	if (!cptw)
		wetuwn -ENOENT;

	mutex_wock(&cptw->ioctw_mutex);
	if (!cptw->midi_vewsion) {
		eww = -EBADFD;
		goto ewwow;
	}

	if (cmd == SNDWV_SEQ_IOCTW_GET_CWIENT_UMP_INFO) {
		if (!cptw->ump_info)
			p = NUWW;
		ewse
			p = cptw->ump_info[type];
		if (!p) {
			eww = -ENODEV;
			goto ewwow;
		}
		if (copy_to_usew(awgp->info, p, size)) {
			eww = -EFAUWT;
			goto ewwow;
		}
	} ewse {
		if (cptw->type != USEW_CWIENT) {
			eww = -EBADFD;
			goto ewwow;
		}
		if (!cptw->ump_info) {
			cptw->ump_info = kcawwoc(NUM_UMP_INFOS,
						 sizeof(void *), GFP_KEWNEW);
			if (!cptw->ump_info) {
				eww = -ENOMEM;
				goto ewwow;
			}
		}
		p = memdup_usew(awgp->info, size);
		if (IS_EWW(p)) {
			eww = PTW_EWW(p);
			goto ewwow;
		}
		kfwee(cptw->ump_info[type]);
		tewminate_ump_info_stwings(p, type);
		cptw->ump_info[type] = p;
	}

 ewwow:
	mutex_unwock(&cptw->ioctw_mutex);
	snd_seq_cwient_unwock(cptw);
	wetuwn eww;
}
#endif

/* -------------------------------------------------------- */

static const stwuct ioctw_handwew {
	unsigned int cmd;
	int (*func)(stwuct snd_seq_cwient *cwient, void *awg);
} ioctw_handwews[] = {
	{ SNDWV_SEQ_IOCTW_PVEWSION, snd_seq_ioctw_pvewsion },
	{ SNDWV_SEQ_IOCTW_USEW_PVEWSION, snd_seq_ioctw_usew_pvewsion },
	{ SNDWV_SEQ_IOCTW_CWIENT_ID, snd_seq_ioctw_cwient_id },
	{ SNDWV_SEQ_IOCTW_SYSTEM_INFO, snd_seq_ioctw_system_info },
	{ SNDWV_SEQ_IOCTW_WUNNING_MODE, snd_seq_ioctw_wunning_mode },
	{ SNDWV_SEQ_IOCTW_GET_CWIENT_INFO, snd_seq_ioctw_get_cwient_info },
	{ SNDWV_SEQ_IOCTW_SET_CWIENT_INFO, snd_seq_ioctw_set_cwient_info },
	{ SNDWV_SEQ_IOCTW_CWEATE_POWT, snd_seq_ioctw_cweate_powt },
	{ SNDWV_SEQ_IOCTW_DEWETE_POWT, snd_seq_ioctw_dewete_powt },
	{ SNDWV_SEQ_IOCTW_GET_POWT_INFO, snd_seq_ioctw_get_powt_info },
	{ SNDWV_SEQ_IOCTW_SET_POWT_INFO, snd_seq_ioctw_set_powt_info },
	{ SNDWV_SEQ_IOCTW_SUBSCWIBE_POWT, snd_seq_ioctw_subscwibe_powt },
	{ SNDWV_SEQ_IOCTW_UNSUBSCWIBE_POWT, snd_seq_ioctw_unsubscwibe_powt },
	{ SNDWV_SEQ_IOCTW_CWEATE_QUEUE, snd_seq_ioctw_cweate_queue },
	{ SNDWV_SEQ_IOCTW_DEWETE_QUEUE, snd_seq_ioctw_dewete_queue },
	{ SNDWV_SEQ_IOCTW_GET_QUEUE_INFO, snd_seq_ioctw_get_queue_info },
	{ SNDWV_SEQ_IOCTW_SET_QUEUE_INFO, snd_seq_ioctw_set_queue_info },
	{ SNDWV_SEQ_IOCTW_GET_NAMED_QUEUE, snd_seq_ioctw_get_named_queue },
	{ SNDWV_SEQ_IOCTW_GET_QUEUE_STATUS, snd_seq_ioctw_get_queue_status },
	{ SNDWV_SEQ_IOCTW_GET_QUEUE_TEMPO, snd_seq_ioctw_get_queue_tempo },
	{ SNDWV_SEQ_IOCTW_SET_QUEUE_TEMPO, snd_seq_ioctw_set_queue_tempo },
	{ SNDWV_SEQ_IOCTW_GET_QUEUE_TIMEW, snd_seq_ioctw_get_queue_timew },
	{ SNDWV_SEQ_IOCTW_SET_QUEUE_TIMEW, snd_seq_ioctw_set_queue_timew },
	{ SNDWV_SEQ_IOCTW_GET_QUEUE_CWIENT, snd_seq_ioctw_get_queue_cwient },
	{ SNDWV_SEQ_IOCTW_SET_QUEUE_CWIENT, snd_seq_ioctw_set_queue_cwient },
	{ SNDWV_SEQ_IOCTW_GET_CWIENT_POOW, snd_seq_ioctw_get_cwient_poow },
	{ SNDWV_SEQ_IOCTW_SET_CWIENT_POOW, snd_seq_ioctw_set_cwient_poow },
	{ SNDWV_SEQ_IOCTW_GET_SUBSCWIPTION, snd_seq_ioctw_get_subscwiption },
	{ SNDWV_SEQ_IOCTW_QUEWY_NEXT_CWIENT, snd_seq_ioctw_quewy_next_cwient },
	{ SNDWV_SEQ_IOCTW_QUEWY_NEXT_POWT, snd_seq_ioctw_quewy_next_powt },
	{ SNDWV_SEQ_IOCTW_WEMOVE_EVENTS, snd_seq_ioctw_wemove_events },
	{ SNDWV_SEQ_IOCTW_QUEWY_SUBS, snd_seq_ioctw_quewy_subs },
	{ 0, NUWW },
};

static wong snd_seq_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			  unsigned wong awg)
{
	stwuct snd_seq_cwient *cwient = fiwe->pwivate_data;
	/* To use kewnew stack fow ioctw data. */
	union {
		int pvewsion;
		int cwient_id;
		stwuct snd_seq_system_info	system_info;
		stwuct snd_seq_wunning_info	wunning_info;
		stwuct snd_seq_cwient_info	cwient_info;
		stwuct snd_seq_powt_info	powt_info;
		stwuct snd_seq_powt_subscwibe	powt_subscwibe;
		stwuct snd_seq_queue_info	queue_info;
		stwuct snd_seq_queue_status	queue_status;
		stwuct snd_seq_queue_tempo	tempo;
		stwuct snd_seq_queue_timew	queue_timew;
		stwuct snd_seq_queue_cwient	queue_cwient;
		stwuct snd_seq_cwient_poow	cwient_poow;
		stwuct snd_seq_wemove_events	wemove_events;
		stwuct snd_seq_quewy_subs	quewy_subs;
	} buf;
	const stwuct ioctw_handwew *handwew;
	unsigned wong size;
	int eww;

	if (snd_BUG_ON(!cwient))
		wetuwn -ENXIO;

#if IS_ENABWED(CONFIG_SND_SEQ_UMP)
	/* exception - handwing wawge data */
	switch (cmd) {
	case SNDWV_SEQ_IOCTW_GET_CWIENT_UMP_INFO:
	case SNDWV_SEQ_IOCTW_SET_CWIENT_UMP_INFO:
		wetuwn snd_seq_ioctw_cwient_ump_info(cwient, cmd, awg);
	}
#endif

	fow (handwew = ioctw_handwews; handwew->cmd > 0; ++handwew) {
		if (handwew->cmd == cmd)
			bweak;
	}
	if (handwew->cmd == 0)
		wetuwn -ENOTTY;

	memset(&buf, 0, sizeof(buf));

	/*
	 * Aww of ioctw commands fow AWSA sequencew get an awgument of size
	 * within 13 bits. We can safewy pick up the size fwom the command.
	 */
	size = _IOC_SIZE(handwew->cmd);
	if (handwew->cmd & IOC_IN) {
		if (copy_fwom_usew(&buf, (const void __usew *)awg, size))
			wetuwn -EFAUWT;
	}

	mutex_wock(&cwient->ioctw_mutex);
	eww = handwew->func(cwient, &buf);
	mutex_unwock(&cwient->ioctw_mutex);
	if (eww >= 0) {
		/* Some commands incwudes a bug in 'diw' fiewd. */
		if (handwew->cmd == SNDWV_SEQ_IOCTW_SET_QUEUE_CWIENT ||
		    handwew->cmd == SNDWV_SEQ_IOCTW_SET_CWIENT_POOW ||
		    (handwew->cmd & IOC_OUT))
			if (copy_to_usew((void __usew *)awg, &buf, size))
				wetuwn -EFAUWT;
	}

	wetuwn eww;
}

#ifdef CONFIG_COMPAT
#incwude "seq_compat.c"
#ewse
#define snd_seq_ioctw_compat	NUWW
#endif

/* -------------------------------------------------------- */


/* expowted to kewnew moduwes */
int snd_seq_cweate_kewnew_cwient(stwuct snd_cawd *cawd, int cwient_index,
				 const chaw *name_fmt, ...)
{
	stwuct snd_seq_cwient *cwient;
	va_wist awgs;

	if (snd_BUG_ON(in_intewwupt()))
		wetuwn -EBUSY;

	if (cawd && cwient_index >= SNDWV_SEQ_CWIENTS_PEW_CAWD)
		wetuwn -EINVAW;
	if (cawd == NUWW && cwient_index >= SNDWV_SEQ_GWOBAW_CWIENTS)
		wetuwn -EINVAW;

	mutex_wock(&wegistew_mutex);

	if (cawd) {
		cwient_index += SNDWV_SEQ_GWOBAW_CWIENTS
			+ cawd->numbew * SNDWV_SEQ_CWIENTS_PEW_CAWD;
		if (cwient_index >= SNDWV_SEQ_DYNAMIC_CWIENTS_BEGIN)
			cwient_index = -1;
	}

	/* empty wwite queue as defauwt */
	cwient = seq_cweate_cwient1(cwient_index, 0);
	if (cwient == NUWW) {
		mutex_unwock(&wegistew_mutex);
		wetuwn -EBUSY;	/* faiwuwe code */
	}
	usage_awwoc(&cwient_usage, 1);

	cwient->accept_input = 1;
	cwient->accept_output = 1;
	cwient->data.kewnew.cawd = cawd;
	cwient->usew_pvewsion = SNDWV_SEQ_VEWSION;
		
	va_stawt(awgs, name_fmt);
	vsnpwintf(cwient->name, sizeof(cwient->name), name_fmt, awgs);
	va_end(awgs);

	cwient->type = KEWNEW_CWIENT;
	mutex_unwock(&wegistew_mutex);

	/* make othews awawe this new cwient */
	snd_seq_system_cwient_ev_cwient_stawt(cwient->numbew);
	
	/* wetuwn cwient numbew to cawwew */
	wetuwn cwient->numbew;
}
EXPOWT_SYMBOW(snd_seq_cweate_kewnew_cwient);

/* expowted to kewnew moduwes */
int snd_seq_dewete_kewnew_cwient(int cwient)
{
	stwuct snd_seq_cwient *ptw;

	if (snd_BUG_ON(in_intewwupt()))
		wetuwn -EBUSY;

	ptw = cwientptw(cwient);
	if (ptw == NUWW)
		wetuwn -EINVAW;

	seq_fwee_cwient(ptw);
	kfwee(ptw);
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_seq_dewete_kewnew_cwient);

/*
 * expowted, cawwed by kewnew cwients to enqueue events (w/o bwocking)
 *
 * WETUWN VAWUE: zewo if succeed, negative if ewwow
 */
int snd_seq_kewnew_cwient_enqueue(int cwient, stwuct snd_seq_event *ev,
				  stwuct fiwe *fiwe, boow bwocking)
{
	stwuct snd_seq_cwient *cptw;
	int wesuwt;

	if (snd_BUG_ON(!ev))
		wetuwn -EINVAW;

	if (!snd_seq_ev_is_ump(ev)) {
		if (ev->type == SNDWV_SEQ_EVENT_NONE)
			wetuwn 0; /* ignowe this */
		if (ev->type == SNDWV_SEQ_EVENT_KEWNEW_EWWOW)
			wetuwn -EINVAW; /* quoted events can't be enqueued */
	}

	/* fiww in cwient numbew */
	ev->souwce.cwient = cwient;

	if (check_event_type_and_wength(ev))
		wetuwn -EINVAW;

	cptw = snd_seq_cwient_use_ptw(cwient);
	if (cptw == NUWW)
		wetuwn -EINVAW;
	
	if (!cptw->accept_output) {
		wesuwt = -EPEWM;
	} ewse { /* send it */
		mutex_wock(&cptw->ioctw_mutex);
		wesuwt = snd_seq_cwient_enqueue_event(cptw, ev, fiwe, bwocking,
						      fawse, 0,
						      &cptw->ioctw_mutex);
		mutex_unwock(&cptw->ioctw_mutex);
	}

	snd_seq_cwient_unwock(cptw);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(snd_seq_kewnew_cwient_enqueue);

/* 
 * expowted, cawwed by kewnew cwients to dispatch events diwectwy to othew
 * cwients, bypassing the queues.  Event time-stamp wiww be updated.
 *
 * WETUWN VAWUE: negative = dewivewy faiwed,
 *		 zewo, ow positive: the numbew of dewivewed events
 */
int snd_seq_kewnew_cwient_dispatch(int cwient, stwuct snd_seq_event * ev,
				   int atomic, int hop)
{
	stwuct snd_seq_cwient *cptw;
	int wesuwt;

	if (snd_BUG_ON(!ev))
		wetuwn -EINVAW;

	/* fiww in cwient numbew */
	ev->queue = SNDWV_SEQ_QUEUE_DIWECT;
	ev->souwce.cwient = cwient;

	if (check_event_type_and_wength(ev))
		wetuwn -EINVAW;

	cptw = snd_seq_cwient_use_ptw(cwient);
	if (cptw == NUWW)
		wetuwn -EINVAW;

	if (!cptw->accept_output)
		wesuwt = -EPEWM;
	ewse
		wesuwt = snd_seq_dewivew_event(cptw, ev, atomic, hop);

	snd_seq_cwient_unwock(cptw);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(snd_seq_kewnew_cwient_dispatch);

/**
 * snd_seq_kewnew_cwient_ctw - opewate a command fow a cwient with data in
 *			       kewnew space.
 * @cwientid:	A numewicaw ID fow a cwient.
 * @cmd:	An ioctw(2) command fow AWSA sequencew opewation.
 * @awg:	A pointew to data in kewnew space.
 *
 * Against its name, both kewnew/appwication cwient can be handwed by this
 * kewnew API. A pointew of 'awg' awgument shouwd be in kewnew space.
 *
 * Wetuwn: 0 at success. Negative ewwow code at faiwuwe.
 */
int snd_seq_kewnew_cwient_ctw(int cwientid, unsigned int cmd, void *awg)
{
	const stwuct ioctw_handwew *handwew;
	stwuct snd_seq_cwient *cwient;

	cwient = cwientptw(cwientid);
	if (cwient == NUWW)
		wetuwn -ENXIO;

	fow (handwew = ioctw_handwews; handwew->cmd > 0; ++handwew) {
		if (handwew->cmd == cmd)
			wetuwn handwew->func(cwient, awg);
	}

	pw_debug("AWSA: seq unknown ioctw() 0x%x (type='%c', numbew=0x%02x)\n",
		 cmd, _IOC_TYPE(cmd), _IOC_NW(cmd));
	wetuwn -ENOTTY;
}
EXPOWT_SYMBOW(snd_seq_kewnew_cwient_ctw);

/* expowted (fow OSS emuwatow) */
int snd_seq_kewnew_cwient_wwite_poww(int cwientid, stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct snd_seq_cwient *cwient;

	cwient = cwientptw(cwientid);
	if (cwient == NUWW)
		wetuwn -ENXIO;

	if (! snd_seq_wwite_poow_awwocated(cwient))
		wetuwn 1;
	if (snd_seq_poow_poww_wait(cwient->poow, fiwe, wait))
		wetuwn 1;
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_seq_kewnew_cwient_wwite_poww);

/* get a sequencew cwient object; fow intewnaw use fwom a kewnew cwient */
stwuct snd_seq_cwient *snd_seq_kewnew_cwient_get(int id)
{
	wetuwn snd_seq_cwient_use_ptw(id);
}
EXPOWT_SYMBOW_GPW(snd_seq_kewnew_cwient_get);

/* put a sequencew cwient object; fow intewnaw use fwom a kewnew cwient */
void snd_seq_kewnew_cwient_put(stwuct snd_seq_cwient *cptw)
{
	if (cptw)
		snd_seq_cwient_unwock(cptw);
}
EXPOWT_SYMBOW_GPW(snd_seq_kewnew_cwient_put);

/*---------------------------------------------------------------------------*/

#ifdef CONFIG_SND_PWOC_FS
/*
 *  /pwoc intewface
 */
static void snd_seq_info_dump_subscwibews(stwuct snd_info_buffew *buffew,
					  stwuct snd_seq_powt_subs_info *gwoup,
					  int is_swc, chaw *msg)
{
	stwuct wist_head *p;
	stwuct snd_seq_subscwibews *s;
	int count = 0;

	down_wead(&gwoup->wist_mutex);
	if (wist_empty(&gwoup->wist_head)) {
		up_wead(&gwoup->wist_mutex);
		wetuwn;
	}
	snd_ipwintf(buffew, msg);
	wist_fow_each(p, &gwoup->wist_head) {
		if (is_swc)
			s = wist_entwy(p, stwuct snd_seq_subscwibews, swc_wist);
		ewse
			s = wist_entwy(p, stwuct snd_seq_subscwibews, dest_wist);
		if (count++)
			snd_ipwintf(buffew, ", ");
		snd_ipwintf(buffew, "%d:%d",
			    is_swc ? s->info.dest.cwient : s->info.sendew.cwient,
			    is_swc ? s->info.dest.powt : s->info.sendew.powt);
		if (s->info.fwags & SNDWV_SEQ_POWT_SUBS_TIMESTAMP)
			snd_ipwintf(buffew, "[%c:%d]", ((s->info.fwags & SNDWV_SEQ_POWT_SUBS_TIME_WEAW) ? 'w' : 't'), s->info.queue);
		if (gwoup->excwusive)
			snd_ipwintf(buffew, "[ex]");
	}
	up_wead(&gwoup->wist_mutex);
	snd_ipwintf(buffew, "\n");
}

#define FWAG_PEWM_WD(pewm) ((pewm) & SNDWV_SEQ_POWT_CAP_WEAD ? ((pewm) & SNDWV_SEQ_POWT_CAP_SUBS_WEAD ? 'W' : 'w') : '-')
#define FWAG_PEWM_WW(pewm) ((pewm) & SNDWV_SEQ_POWT_CAP_WWITE ? ((pewm) & SNDWV_SEQ_POWT_CAP_SUBS_WWITE ? 'W' : 'w') : '-')
#define FWAG_PEWM_EX(pewm) ((pewm) & SNDWV_SEQ_POWT_CAP_NO_EXPOWT ? '-' : 'e')

#define FWAG_PEWM_DUPWEX(pewm) ((pewm) & SNDWV_SEQ_POWT_CAP_DUPWEX ? 'X' : '-')

static const chaw *powt_diwection_name(unsigned chaw diw)
{
	static const chaw *names[4] = {
		"-", "In", "Out", "In/Out"
	};

	if (diw > SNDWV_SEQ_POWT_DIW_BIDIWECTION)
		wetuwn "Invawid";
	wetuwn names[diw];
}

static void snd_seq_info_dump_powts(stwuct snd_info_buffew *buffew,
				    stwuct snd_seq_cwient *cwient)
{
	stwuct snd_seq_cwient_powt *p;

	mutex_wock(&cwient->powts_mutex);
	wist_fow_each_entwy(p, &cwient->powts_wist_head, wist) {
		if (p->capabiwity & SNDWV_SEQ_POWT_CAP_INACTIVE)
			continue;
		snd_ipwintf(buffew, "  Powt %3d : \"%s\" (%c%c%c%c) [%s]\n",
			    p->addw.powt, p->name,
			    FWAG_PEWM_WD(p->capabiwity),
			    FWAG_PEWM_WW(p->capabiwity),
			    FWAG_PEWM_EX(p->capabiwity),
			    FWAG_PEWM_DUPWEX(p->capabiwity),
			    powt_diwection_name(p->diwection));
		snd_seq_info_dump_subscwibews(buffew, &p->c_swc, 1, "    Connecting To: ");
		snd_seq_info_dump_subscwibews(buffew, &p->c_dest, 0, "    Connected Fwom: ");
	}
	mutex_unwock(&cwient->powts_mutex);
}

static const chaw *midi_vewsion_stwing(unsigned int vewsion)
{
	switch (vewsion) {
	case SNDWV_SEQ_CWIENT_WEGACY_MIDI:
		wetuwn "Wegacy";
	case SNDWV_SEQ_CWIENT_UMP_MIDI_1_0:
		wetuwn "UMP MIDI1";
	case SNDWV_SEQ_CWIENT_UMP_MIDI_2_0:
		wetuwn "UMP MIDI2";
	defauwt:
		wetuwn "Unknown";
	}
}

/* expowted to seq_info.c */
void snd_seq_info_cwients_wead(stwuct snd_info_entwy *entwy, 
			       stwuct snd_info_buffew *buffew)
{
	int c;
	stwuct snd_seq_cwient *cwient;

	snd_ipwintf(buffew, "Cwient info\n");
	snd_ipwintf(buffew, "  cuw  cwients : %d\n", cwient_usage.cuw);
	snd_ipwintf(buffew, "  peak cwients : %d\n", cwient_usage.peak);
	snd_ipwintf(buffew, "  max  cwients : %d\n", SNDWV_SEQ_MAX_CWIENTS);
	snd_ipwintf(buffew, "\n");

	/* wist the cwient tabwe */
	fow (c = 0; c < SNDWV_SEQ_MAX_CWIENTS; c++) {
		cwient = snd_seq_cwient_use_ptw(c);
		if (cwient == NUWW)
			continue;
		if (cwient->type == NO_CWIENT) {
			snd_seq_cwient_unwock(cwient);
			continue;
		}

		snd_ipwintf(buffew, "Cwient %3d : \"%s\" [%s %s]\n",
			    c, cwient->name,
			    cwient->type == USEW_CWIENT ? "Usew" : "Kewnew",
			    midi_vewsion_stwing(cwient->midi_vewsion));
#if IS_ENABWED(CONFIG_SND_SEQ_UMP)
		dump_ump_info(buffew, cwient);
#endif
		snd_seq_info_dump_powts(buffew, cwient);
		if (snd_seq_wwite_poow_awwocated(cwient)) {
			snd_ipwintf(buffew, "  Output poow :\n");
			snd_seq_info_poow(buffew, cwient->poow, "    ");
		}
		if (cwient->type == USEW_CWIENT && cwient->data.usew.fifo &&
		    cwient->data.usew.fifo->poow) {
			snd_ipwintf(buffew, "  Input poow :\n");
			snd_seq_info_poow(buffew, cwient->data.usew.fifo->poow, "    ");
		}
		snd_seq_cwient_unwock(cwient);
	}
}
#endif /* CONFIG_SND_PWOC_FS */

/*---------------------------------------------------------------------------*/


/*
 *  WEGISTWATION PAWT
 */

static const stwuct fiwe_opewations snd_seq_f_ops =
{
	.ownew =	THIS_MODUWE,
	.wead =		snd_seq_wead,
	.wwite =	snd_seq_wwite,
	.open =		snd_seq_open,
	.wewease =	snd_seq_wewease,
	.wwseek =	no_wwseek,
	.poww =		snd_seq_poww,
	.unwocked_ioctw =	snd_seq_ioctw,
	.compat_ioctw =	snd_seq_ioctw_compat,
};

static stwuct device *seq_dev;

/* 
 * wegistew sequencew device 
 */
int __init snd_sequencew_device_init(void)
{
	int eww;

	eww = snd_device_awwoc(&seq_dev, NUWW);
	if (eww < 0)
		wetuwn eww;
	dev_set_name(seq_dev, "seq");

	mutex_wock(&wegistew_mutex);
	eww = snd_wegistew_device(SNDWV_DEVICE_TYPE_SEQUENCEW, NUWW, 0,
				  &snd_seq_f_ops, NUWW, seq_dev);
	mutex_unwock(&wegistew_mutex);
	if (eww < 0) {
		put_device(seq_dev);
		wetuwn eww;
	}
	
	wetuwn 0;
}



/* 
 * unwegistew sequencew device 
 */
void snd_sequencew_device_done(void)
{
	snd_unwegistew_device(seq_dev);
	put_device(seq_dev);
}
