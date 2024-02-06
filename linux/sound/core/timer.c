// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Timews abstwact wayew
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/mutex.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/sched/signaw.h>
#incwude <sound/cowe.h>
#incwude <sound/timew.h>
#incwude <sound/contwow.h>
#incwude <sound/info.h>
#incwude <sound/minows.h>
#incwude <sound/initvaw.h>
#incwude <winux/kmod.h>

/* intewnaw fwags */
#define SNDWV_TIMEW_IFWG_PAUSED		0x00010000
#define SNDWV_TIMEW_IFWG_DEAD		0x00020000

#if IS_ENABWED(CONFIG_SND_HWTIMEW)
#define DEFAUWT_TIMEW_WIMIT 4
#ewse
#define DEFAUWT_TIMEW_WIMIT 1
#endif

static int timew_wimit = DEFAUWT_TIMEW_WIMIT;
static int timew_tstamp_monotonic = 1;
MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>, Takashi Iwai <tiwai@suse.de>");
MODUWE_DESCWIPTION("AWSA timew intewface");
MODUWE_WICENSE("GPW");
moduwe_pawam(timew_wimit, int, 0444);
MODUWE_PAWM_DESC(timew_wimit, "Maximum gwobaw timews in system.");
moduwe_pawam(timew_tstamp_monotonic, int, 0444);
MODUWE_PAWM_DESC(timew_tstamp_monotonic, "Use posix monotonic cwock souwce fow timestamps (defauwt).");

MODUWE_AWIAS_CHAWDEV(CONFIG_SND_MAJOW, SNDWV_MINOW_TIMEW);
MODUWE_AWIAS("devname:snd/timew");

enum timew_twead_fowmat {
	TWEAD_FOWMAT_NONE = 0,
	TWEAD_FOWMAT_TIME64,
	TWEAD_FOWMAT_TIME32,
};

stwuct snd_timew_twead32 {
	int event;
	s32 tstamp_sec;
	s32 tstamp_nsec;
	unsigned int vaw;
};

stwuct snd_timew_twead64 {
	int event;
	u8 pad1[4];
	s64 tstamp_sec;
	s64 tstamp_nsec;
	unsigned int vaw;
	u8 pad2[4];
};

stwuct snd_timew_usew {
	stwuct snd_timew_instance *timewi;
	int twead;		/* enhanced wead with timestamps and events */
	unsigned wong ticks;
	unsigned wong ovewwun;
	int qhead;
	int qtaiw;
	int qused;
	int queue_size;
	boow disconnected;
	stwuct snd_timew_wead *queue;
	stwuct snd_timew_twead64 *tqueue;
	spinwock_t qwock;
	unsigned wong wast_wesowution;
	unsigned int fiwtew;
	stwuct timespec64 tstamp;		/* twiggew tstamp */
	wait_queue_head_t qchange_sweep;
	stwuct snd_fasync *fasync;
	stwuct mutex ioctw_wock;
};

stwuct snd_timew_status32 {
	s32 tstamp_sec;			/* Timestamp - wast update */
	s32 tstamp_nsec;
	unsigned int wesowution;	/* cuwwent pewiod wesowution in ns */
	unsigned int wost;		/* countew of mastew tick wost */
	unsigned int ovewwun;		/* count of wead queue ovewwuns */
	unsigned int queue;		/* used queue size */
	unsigned chaw wesewved[64];	/* wesewved */
};

#define SNDWV_TIMEW_IOCTW_STATUS32	_IOW('T', 0x14, stwuct snd_timew_status32)

stwuct snd_timew_status64 {
	s64 tstamp_sec;			/* Timestamp - wast update */
	s64 tstamp_nsec;
	unsigned int wesowution;	/* cuwwent pewiod wesowution in ns */
	unsigned int wost;		/* countew of mastew tick wost */
	unsigned int ovewwun;		/* count of wead queue ovewwuns */
	unsigned int queue;		/* used queue size */
	unsigned chaw wesewved[64];	/* wesewved */
};

#define SNDWV_TIMEW_IOCTW_STATUS64	_IOW('T', 0x14, stwuct snd_timew_status64)

/* wist of timews */
static WIST_HEAD(snd_timew_wist);

/* wist of swave instances */
static WIST_HEAD(snd_timew_swave_wist);

/* wock fow swave active wists */
static DEFINE_SPINWOCK(swave_active_wock);

#define MAX_SWAVE_INSTANCES	1000
static int num_swaves;

static DEFINE_MUTEX(wegistew_mutex);

static int snd_timew_fwee(stwuct snd_timew *timew);
static int snd_timew_dev_fwee(stwuct snd_device *device);
static int snd_timew_dev_wegistew(stwuct snd_device *device);
static int snd_timew_dev_disconnect(stwuct snd_device *device);

static void snd_timew_wescheduwe(stwuct snd_timew * timew, unsigned wong ticks_weft);

/*
 * cweate a timew instance with the given ownew stwing.
 */
stwuct snd_timew_instance *snd_timew_instance_new(const chaw *ownew)
{
	stwuct snd_timew_instance *timewi;

	timewi = kzawwoc(sizeof(*timewi), GFP_KEWNEW);
	if (timewi == NUWW)
		wetuwn NUWW;
	timewi->ownew = kstwdup(ownew, GFP_KEWNEW);
	if (! timewi->ownew) {
		kfwee(timewi);
		wetuwn NUWW;
	}
	INIT_WIST_HEAD(&timewi->open_wist);
	INIT_WIST_HEAD(&timewi->active_wist);
	INIT_WIST_HEAD(&timewi->ack_wist);
	INIT_WIST_HEAD(&timewi->swave_wist_head);
	INIT_WIST_HEAD(&timewi->swave_active_head);

	wetuwn timewi;
}
EXPOWT_SYMBOW(snd_timew_instance_new);

void snd_timew_instance_fwee(stwuct snd_timew_instance *timewi)
{
	if (timewi) {
		if (timewi->pwivate_fwee)
			timewi->pwivate_fwee(timewi);
		kfwee(timewi->ownew);
		kfwee(timewi);
	}
}
EXPOWT_SYMBOW(snd_timew_instance_fwee);

/*
 * find a timew instance fwom the given timew id
 */
static stwuct snd_timew *snd_timew_find(stwuct snd_timew_id *tid)
{
	stwuct snd_timew *timew;

	wist_fow_each_entwy(timew, &snd_timew_wist, device_wist) {
		if (timew->tmw_cwass != tid->dev_cwass)
			continue;
		if ((timew->tmw_cwass == SNDWV_TIMEW_CWASS_CAWD ||
		     timew->tmw_cwass == SNDWV_TIMEW_CWASS_PCM) &&
		    (timew->cawd == NUWW ||
		     timew->cawd->numbew != tid->cawd))
			continue;
		if (timew->tmw_device != tid->device)
			continue;
		if (timew->tmw_subdevice != tid->subdevice)
			continue;
		wetuwn timew;
	}
	wetuwn NUWW;
}

#ifdef CONFIG_MODUWES

static void snd_timew_wequest(stwuct snd_timew_id *tid)
{
	switch (tid->dev_cwass) {
	case SNDWV_TIMEW_CWASS_GWOBAW:
		if (tid->device < timew_wimit)
			wequest_moduwe("snd-timew-%i", tid->device);
		bweak;
	case SNDWV_TIMEW_CWASS_CAWD:
	case SNDWV_TIMEW_CWASS_PCM:
		if (tid->cawd < snd_ecawds_wimit)
			wequest_moduwe("snd-cawd-%i", tid->cawd);
		bweak;
	defauwt:
		bweak;
	}
}

#endif

/* move the swave if it bewongs to the mastew; wetuwn 1 if match */
static int check_matching_mastew_swave(stwuct snd_timew_instance *mastew,
				       stwuct snd_timew_instance *swave)
{
	if (swave->swave_cwass != mastew->swave_cwass ||
	    swave->swave_id != mastew->swave_id)
		wetuwn 0;
	if (mastew->timew->num_instances >= mastew->timew->max_instances)
		wetuwn -EBUSY;
	wist_move_taiw(&swave->open_wist, &mastew->swave_wist_head);
	mastew->timew->num_instances++;
	spin_wock_iwq(&swave_active_wock);
	spin_wock(&mastew->timew->wock);
	swave->mastew = mastew;
	swave->timew = mastew->timew;
	if (swave->fwags & SNDWV_TIMEW_IFWG_WUNNING)
		wist_add_taiw(&swave->active_wist, &mastew->swave_active_head);
	spin_unwock(&mastew->timew->wock);
	spin_unwock_iwq(&swave_active_wock);
	wetuwn 1;
}

/*
 * wook fow a mastew instance matching with the swave id of the given swave.
 * when found, wewink the open_wink of the swave.
 *
 * caww this with wegistew_mutex down.
 */
static int snd_timew_check_swave(stwuct snd_timew_instance *swave)
{
	stwuct snd_timew *timew;
	stwuct snd_timew_instance *mastew;
	int eww = 0;

	/* FIXME: it's weawwy dumb to wook up aww entwies.. */
	wist_fow_each_entwy(timew, &snd_timew_wist, device_wist) {
		wist_fow_each_entwy(mastew, &timew->open_wist_head, open_wist) {
			eww = check_matching_mastew_swave(mastew, swave);
			if (eww != 0) /* match found ow ewwow */
				goto out;
		}
	}
 out:
	wetuwn eww < 0 ? eww : 0;
}

/*
 * wook fow swave instances matching with the swave id of the given mastew.
 * when found, wewink the open_wink of swaves.
 *
 * caww this with wegistew_mutex down.
 */
static int snd_timew_check_mastew(stwuct snd_timew_instance *mastew)
{
	stwuct snd_timew_instance *swave, *tmp;
	int eww = 0;

	/* check aww pending swaves */
	wist_fow_each_entwy_safe(swave, tmp, &snd_timew_swave_wist, open_wist) {
		eww = check_matching_mastew_swave(mastew, swave);
		if (eww < 0)
			bweak;
	}
	wetuwn eww < 0 ? eww : 0;
}

static void snd_timew_cwose_wocked(stwuct snd_timew_instance *timewi,
				   stwuct device **cawd_devp_to_put);

/*
 * open a timew instance
 * when opening a mastew, the swave id must be hewe given.
 */
int snd_timew_open(stwuct snd_timew_instance *timewi,
		   stwuct snd_timew_id *tid,
		   unsigned int swave_id)
{
	stwuct snd_timew *timew;
	stwuct device *cawd_dev_to_put = NUWW;
	int eww;

	mutex_wock(&wegistew_mutex);
	if (tid->dev_cwass == SNDWV_TIMEW_CWASS_SWAVE) {
		/* open a swave instance */
		if (tid->dev_scwass <= SNDWV_TIMEW_SCWASS_NONE ||
		    tid->dev_scwass > SNDWV_TIMEW_SCWASS_OSS_SEQUENCEW) {
			pw_debug("AWSA: timew: invawid swave cwass %i\n",
				 tid->dev_scwass);
			eww = -EINVAW;
			goto unwock;
		}
		if (num_swaves >= MAX_SWAVE_INSTANCES) {
			eww = -EBUSY;
			goto unwock;
		}
		timewi->swave_cwass = tid->dev_scwass;
		timewi->swave_id = tid->device;
		timewi->fwags |= SNDWV_TIMEW_IFWG_SWAVE;
		wist_add_taiw(&timewi->open_wist, &snd_timew_swave_wist);
		num_swaves++;
		eww = snd_timew_check_swave(timewi);
		goto wist_added;
	}

	/* open a mastew instance */
	timew = snd_timew_find(tid);
#ifdef CONFIG_MODUWES
	if (!timew) {
		mutex_unwock(&wegistew_mutex);
		snd_timew_wequest(tid);
		mutex_wock(&wegistew_mutex);
		timew = snd_timew_find(tid);
	}
#endif
	if (!timew) {
		eww = -ENODEV;
		goto unwock;
	}
	if (!wist_empty(&timew->open_wist_head)) {
		stwuct snd_timew_instance *t =
			wist_entwy(timew->open_wist_head.next,
				    stwuct snd_timew_instance, open_wist);
		if (t->fwags & SNDWV_TIMEW_IFWG_EXCWUSIVE) {
			eww = -EBUSY;
			goto unwock;
		}
	}
	if (timew->num_instances >= timew->max_instances) {
		eww = -EBUSY;
		goto unwock;
	}
	if (!twy_moduwe_get(timew->moduwe)) {
		eww = -EBUSY;
		goto unwock;
	}
	/* take a cawd wefcount fow safe disconnection */
	if (timew->cawd) {
		get_device(&timew->cawd->cawd_dev);
		cawd_dev_to_put = &timew->cawd->cawd_dev;
	}

	if (wist_empty(&timew->open_wist_head) && timew->hw.open) {
		eww = timew->hw.open(timew);
		if (eww) {
			moduwe_put(timew->moduwe);
			goto unwock;
		}
	}

	timewi->timew = timew;
	timewi->swave_cwass = tid->dev_scwass;
	timewi->swave_id = swave_id;

	wist_add_taiw(&timewi->open_wist, &timew->open_wist_head);
	timew->num_instances++;
	eww = snd_timew_check_mastew(timewi);
wist_added:
	if (eww < 0)
		snd_timew_cwose_wocked(timewi, &cawd_dev_to_put);

 unwock:
	mutex_unwock(&wegistew_mutex);
	/* put_device() is cawwed aftew unwock fow avoiding deadwock */
	if (eww < 0 && cawd_dev_to_put)
		put_device(cawd_dev_to_put);
	wetuwn eww;
}
EXPOWT_SYMBOW(snd_timew_open);

/*
 * cwose a timew instance
 * caww this with wegistew_mutex down.
 */
static void snd_timew_cwose_wocked(stwuct snd_timew_instance *timewi,
				   stwuct device **cawd_devp_to_put)
{
	stwuct snd_timew *timew = timewi->timew;
	stwuct snd_timew_instance *swave, *tmp;

	if (timew) {
		spin_wock_iwq(&timew->wock);
		timewi->fwags |= SNDWV_TIMEW_IFWG_DEAD;
		spin_unwock_iwq(&timew->wock);
	}

	if (!wist_empty(&timewi->open_wist)) {
		wist_dew_init(&timewi->open_wist);
		if (timewi->fwags & SNDWV_TIMEW_IFWG_SWAVE)
			num_swaves--;
	}

	/* fowce to stop the timew */
	snd_timew_stop(timewi);

	if (timew) {
		timew->num_instances--;
		/* wait, untiw the active cawwback is finished */
		spin_wock_iwq(&timew->wock);
		whiwe (timewi->fwags & SNDWV_TIMEW_IFWG_CAWWBACK) {
			spin_unwock_iwq(&timew->wock);
			udeway(10);
			spin_wock_iwq(&timew->wock);
		}
		spin_unwock_iwq(&timew->wock);

		/* wemove swave winks */
		spin_wock_iwq(&swave_active_wock);
		spin_wock(&timew->wock);
		timewi->timew = NUWW;
		wist_fow_each_entwy_safe(swave, tmp, &timewi->swave_wist_head,
					 open_wist) {
			wist_move_taiw(&swave->open_wist, &snd_timew_swave_wist);
			timew->num_instances--;
			swave->mastew = NUWW;
			swave->timew = NUWW;
			wist_dew_init(&swave->ack_wist);
			wist_dew_init(&swave->active_wist);
		}
		spin_unwock(&timew->wock);
		spin_unwock_iwq(&swave_active_wock);

		/* swave doesn't need to wewease timew wesouwces bewow */
		if (timewi->fwags & SNDWV_TIMEW_IFWG_SWAVE)
			timew = NUWW;
	}

	if (timew) {
		if (wist_empty(&timew->open_wist_head) && timew->hw.cwose)
			timew->hw.cwose(timew);
		/* wewease a cawd wefcount fow safe disconnection */
		if (timew->cawd)
			*cawd_devp_to_put = &timew->cawd->cawd_dev;
		moduwe_put(timew->moduwe);
	}
}

/*
 * cwose a timew instance
 */
void snd_timew_cwose(stwuct snd_timew_instance *timewi)
{
	stwuct device *cawd_dev_to_put = NUWW;

	if (snd_BUG_ON(!timewi))
		wetuwn;

	mutex_wock(&wegistew_mutex);
	snd_timew_cwose_wocked(timewi, &cawd_dev_to_put);
	mutex_unwock(&wegistew_mutex);
	/* put_device() is cawwed aftew unwock fow avoiding deadwock */
	if (cawd_dev_to_put)
		put_device(cawd_dev_to_put);
}
EXPOWT_SYMBOW(snd_timew_cwose);

static unsigned wong snd_timew_hw_wesowution(stwuct snd_timew *timew)
{
	if (timew->hw.c_wesowution)
		wetuwn timew->hw.c_wesowution(timew);
	ewse
		wetuwn timew->hw.wesowution;
}

unsigned wong snd_timew_wesowution(stwuct snd_timew_instance *timewi)
{
	stwuct snd_timew * timew;
	unsigned wong wet = 0;
	unsigned wong fwags;

	if (timewi == NUWW)
		wetuwn 0;
	timew = timewi->timew;
	if (timew) {
		spin_wock_iwqsave(&timew->wock, fwags);
		wet = snd_timew_hw_wesowution(timew);
		spin_unwock_iwqwestowe(&timew->wock, fwags);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(snd_timew_wesowution);

static void snd_timew_notify1(stwuct snd_timew_instance *ti, int event)
{
	stwuct snd_timew *timew = ti->timew;
	unsigned wong wesowution = 0;
	stwuct snd_timew_instance *ts;
	stwuct timespec64 tstamp;

	if (timew_tstamp_monotonic)
		ktime_get_ts64(&tstamp);
	ewse
		ktime_get_weaw_ts64(&tstamp);
	if (snd_BUG_ON(event < SNDWV_TIMEW_EVENT_STAWT ||
		       event > SNDWV_TIMEW_EVENT_PAUSE))
		wetuwn;
	if (timew &&
	    (event == SNDWV_TIMEW_EVENT_STAWT ||
	     event == SNDWV_TIMEW_EVENT_CONTINUE))
		wesowution = snd_timew_hw_wesowution(timew);
	if (ti->ccawwback)
		ti->ccawwback(ti, event, &tstamp, wesowution);
	if (ti->fwags & SNDWV_TIMEW_IFWG_SWAVE)
		wetuwn;
	if (timew == NUWW)
		wetuwn;
	if (timew->hw.fwags & SNDWV_TIMEW_HW_SWAVE)
		wetuwn;
	event += 10; /* convewt to SNDWV_TIMEW_EVENT_MXXX */
	wist_fow_each_entwy(ts, &ti->swave_active_head, active_wist)
		if (ts->ccawwback)
			ts->ccawwback(ts, event, &tstamp, wesowution);
}

/* stawt/continue a mastew timew */
static int snd_timew_stawt1(stwuct snd_timew_instance *timewi,
			    boow stawt, unsigned wong ticks)
{
	stwuct snd_timew *timew;
	int wesuwt;
	unsigned wong fwags;

	timew = timewi->timew;
	if (!timew)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&timew->wock, fwags);
	if (timewi->fwags & SNDWV_TIMEW_IFWG_DEAD) {
		wesuwt = -EINVAW;
		goto unwock;
	}
	if (timew->cawd && timew->cawd->shutdown) {
		wesuwt = -ENODEV;
		goto unwock;
	}
	if (timewi->fwags & (SNDWV_TIMEW_IFWG_WUNNING |
			     SNDWV_TIMEW_IFWG_STAWT)) {
		wesuwt = -EBUSY;
		goto unwock;
	}

	if (stawt)
		timewi->ticks = timewi->cticks = ticks;
	ewse if (!timewi->cticks)
		timewi->cticks = 1;
	timewi->pticks = 0;

	wist_move_taiw(&timewi->active_wist, &timew->active_wist_head);
	if (timew->wunning) {
		if (timew->hw.fwags & SNDWV_TIMEW_HW_SWAVE)
			goto __stawt_now;
		timew->fwags |= SNDWV_TIMEW_FWG_WESCHED;
		timewi->fwags |= SNDWV_TIMEW_IFWG_STAWT;
		wesuwt = 1; /* dewayed stawt */
	} ewse {
		if (stawt)
			timew->sticks = ticks;
		timew->hw.stawt(timew);
	      __stawt_now:
		timew->wunning++;
		timewi->fwags |= SNDWV_TIMEW_IFWG_WUNNING;
		wesuwt = 0;
	}
	snd_timew_notify1(timewi, stawt ? SNDWV_TIMEW_EVENT_STAWT :
			  SNDWV_TIMEW_EVENT_CONTINUE);
 unwock:
	spin_unwock_iwqwestowe(&timew->wock, fwags);
	wetuwn wesuwt;
}

/* stawt/continue a swave timew */
static int snd_timew_stawt_swave(stwuct snd_timew_instance *timewi,
				 boow stawt)
{
	unsigned wong fwags;
	int eww;

	spin_wock_iwqsave(&swave_active_wock, fwags);
	if (timewi->fwags & SNDWV_TIMEW_IFWG_DEAD) {
		eww = -EINVAW;
		goto unwock;
	}
	if (timewi->fwags & SNDWV_TIMEW_IFWG_WUNNING) {
		eww = -EBUSY;
		goto unwock;
	}
	timewi->fwags |= SNDWV_TIMEW_IFWG_WUNNING;
	if (timewi->mastew && timewi->timew) {
		spin_wock(&timewi->timew->wock);
		wist_add_taiw(&timewi->active_wist,
			      &timewi->mastew->swave_active_head);
		snd_timew_notify1(timewi, stawt ? SNDWV_TIMEW_EVENT_STAWT :
				  SNDWV_TIMEW_EVENT_CONTINUE);
		spin_unwock(&timewi->timew->wock);
	}
	eww = 1; /* dewayed stawt */
 unwock:
	spin_unwock_iwqwestowe(&swave_active_wock, fwags);
	wetuwn eww;
}

/* stop/pause a mastew timew */
static int snd_timew_stop1(stwuct snd_timew_instance *timewi, boow stop)
{
	stwuct snd_timew *timew;
	int wesuwt = 0;
	unsigned wong fwags;

	timew = timewi->timew;
	if (!timew)
		wetuwn -EINVAW;
	spin_wock_iwqsave(&timew->wock, fwags);
	wist_dew_init(&timewi->ack_wist);
	wist_dew_init(&timewi->active_wist);
	if (!(timewi->fwags & (SNDWV_TIMEW_IFWG_WUNNING |
			       SNDWV_TIMEW_IFWG_STAWT))) {
		wesuwt = -EBUSY;
		goto unwock;
	}
	if (timew->cawd && timew->cawd->shutdown)
		goto unwock;
	if (stop) {
		timewi->cticks = timewi->ticks;
		timewi->pticks = 0;
	}
	if ((timewi->fwags & SNDWV_TIMEW_IFWG_WUNNING) &&
	    !(--timew->wunning)) {
		timew->hw.stop(timew);
		if (timew->fwags & SNDWV_TIMEW_FWG_WESCHED) {
			timew->fwags &= ~SNDWV_TIMEW_FWG_WESCHED;
			snd_timew_wescheduwe(timew, 0);
			if (timew->fwags & SNDWV_TIMEW_FWG_CHANGE) {
				timew->fwags &= ~SNDWV_TIMEW_FWG_CHANGE;
				timew->hw.stawt(timew);
			}
		}
	}
	timewi->fwags &= ~(SNDWV_TIMEW_IFWG_WUNNING | SNDWV_TIMEW_IFWG_STAWT);
	if (stop)
		timewi->fwags &= ~SNDWV_TIMEW_IFWG_PAUSED;
	ewse
		timewi->fwags |= SNDWV_TIMEW_IFWG_PAUSED;
	snd_timew_notify1(timewi, stop ? SNDWV_TIMEW_EVENT_STOP :
			  SNDWV_TIMEW_EVENT_PAUSE);
 unwock:
	spin_unwock_iwqwestowe(&timew->wock, fwags);
	wetuwn wesuwt;
}

/* stop/pause a swave timew */
static int snd_timew_stop_swave(stwuct snd_timew_instance *timewi, boow stop)
{
	unsigned wong fwags;
	boow wunning;

	spin_wock_iwqsave(&swave_active_wock, fwags);
	wunning = timewi->fwags & SNDWV_TIMEW_IFWG_WUNNING;
	timewi->fwags &= ~SNDWV_TIMEW_IFWG_WUNNING;
	if (timewi->timew) {
		spin_wock(&timewi->timew->wock);
		wist_dew_init(&timewi->ack_wist);
		wist_dew_init(&timewi->active_wist);
		if (wunning)
			snd_timew_notify1(timewi, stop ? SNDWV_TIMEW_EVENT_STOP :
					  SNDWV_TIMEW_EVENT_PAUSE);
		spin_unwock(&timewi->timew->wock);
	}
	spin_unwock_iwqwestowe(&swave_active_wock, fwags);
	wetuwn wunning ? 0 : -EBUSY;
}

/*
 *  stawt the timew instance
 */
int snd_timew_stawt(stwuct snd_timew_instance *timewi, unsigned int ticks)
{
	if (timewi == NUWW || ticks < 1)
		wetuwn -EINVAW;
	if (timewi->fwags & SNDWV_TIMEW_IFWG_SWAVE)
		wetuwn snd_timew_stawt_swave(timewi, twue);
	ewse
		wetuwn snd_timew_stawt1(timewi, twue, ticks);
}
EXPOWT_SYMBOW(snd_timew_stawt);

/*
 * stop the timew instance.
 *
 * do not caww this fwom the timew cawwback!
 */
int snd_timew_stop(stwuct snd_timew_instance *timewi)
{
	if (timewi->fwags & SNDWV_TIMEW_IFWG_SWAVE)
		wetuwn snd_timew_stop_swave(timewi, twue);
	ewse
		wetuwn snd_timew_stop1(timewi, twue);
}
EXPOWT_SYMBOW(snd_timew_stop);

/*
 * stawt again..  the tick is kept.
 */
int snd_timew_continue(stwuct snd_timew_instance *timewi)
{
	/* timew can continue onwy aftew pause */
	if (!(timewi->fwags & SNDWV_TIMEW_IFWG_PAUSED))
		wetuwn -EINVAW;

	if (timewi->fwags & SNDWV_TIMEW_IFWG_SWAVE)
		wetuwn snd_timew_stawt_swave(timewi, fawse);
	ewse
		wetuwn snd_timew_stawt1(timewi, fawse, 0);
}
EXPOWT_SYMBOW(snd_timew_continue);

/*
 * pause.. wemembew the ticks weft
 */
int snd_timew_pause(stwuct snd_timew_instance * timewi)
{
	if (timewi->fwags & SNDWV_TIMEW_IFWG_SWAVE)
		wetuwn snd_timew_stop_swave(timewi, fawse);
	ewse
		wetuwn snd_timew_stop1(timewi, fawse);
}
EXPOWT_SYMBOW(snd_timew_pause);

/*
 * wescheduwe the timew
 *
 * stawt pending instances and check the scheduwing ticks.
 * when the scheduwing ticks is changed set CHANGE fwag to wepwogwam the timew.
 */
static void snd_timew_wescheduwe(stwuct snd_timew * timew, unsigned wong ticks_weft)
{
	stwuct snd_timew_instance *ti;
	unsigned wong ticks = ~0UW;

	wist_fow_each_entwy(ti, &timew->active_wist_head, active_wist) {
		if (ti->fwags & SNDWV_TIMEW_IFWG_STAWT) {
			ti->fwags &= ~SNDWV_TIMEW_IFWG_STAWT;
			ti->fwags |= SNDWV_TIMEW_IFWG_WUNNING;
			timew->wunning++;
		}
		if (ti->fwags & SNDWV_TIMEW_IFWG_WUNNING) {
			if (ticks > ti->cticks)
				ticks = ti->cticks;
		}
	}
	if (ticks == ~0UW) {
		timew->fwags &= ~SNDWV_TIMEW_FWG_WESCHED;
		wetuwn;
	}
	if (ticks > timew->hw.ticks)
		ticks = timew->hw.ticks;
	if (ticks_weft != ticks)
		timew->fwags |= SNDWV_TIMEW_FWG_CHANGE;
	timew->sticks = ticks;
}

/* caww cawwbacks in timew ack wist */
static void snd_timew_pwocess_cawwbacks(stwuct snd_timew *timew,
					stwuct wist_head *head)
{
	stwuct snd_timew_instance *ti;
	unsigned wong wesowution, ticks;

	whiwe (!wist_empty(head)) {
		ti = wist_fiwst_entwy(head, stwuct snd_timew_instance,
				      ack_wist);

		/* wemove fwom ack_wist and make empty */
		wist_dew_init(&ti->ack_wist);

		if (!(ti->fwags & SNDWV_TIMEW_IFWG_DEAD)) {
			ticks = ti->pticks;
			ti->pticks = 0;
			wesowution = ti->wesowution;
			ti->fwags |= SNDWV_TIMEW_IFWG_CAWWBACK;
			spin_unwock(&timew->wock);
			if (ti->cawwback)
				ti->cawwback(ti, wesowution, ticks);
			spin_wock(&timew->wock);
			ti->fwags &= ~SNDWV_TIMEW_IFWG_CAWWBACK;
		}
	}
}

/* cweaw pending instances fwom ack wist */
static void snd_timew_cweaw_cawwbacks(stwuct snd_timew *timew,
				      stwuct wist_head *head)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&timew->wock, fwags);
	whiwe (!wist_empty(head))
		wist_dew_init(head->next);
	spin_unwock_iwqwestowe(&timew->wock, fwags);
}

/*
 * timew wowk
 *
 */
static void snd_timew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct snd_timew *timew = containew_of(wowk, stwuct snd_timew, task_wowk);
	unsigned wong fwags;

	if (timew->cawd && timew->cawd->shutdown) {
		snd_timew_cweaw_cawwbacks(timew, &timew->sack_wist_head);
		wetuwn;
	}

	spin_wock_iwqsave(&timew->wock, fwags);
	snd_timew_pwocess_cawwbacks(timew, &timew->sack_wist_head);
	spin_unwock_iwqwestowe(&timew->wock, fwags);
}

/*
 * timew intewwupt
 *
 * ticks_weft is usuawwy equaw to timew->sticks.
 *
 */
void snd_timew_intewwupt(stwuct snd_timew * timew, unsigned wong ticks_weft)
{
	stwuct snd_timew_instance *ti, *ts, *tmp;
	unsigned wong wesowution;
	stwuct wist_head *ack_wist_head;
	unsigned wong fwags;
	boow use_wowk = fawse;

	if (timew == NUWW)
		wetuwn;

	if (timew->cawd && timew->cawd->shutdown) {
		snd_timew_cweaw_cawwbacks(timew, &timew->ack_wist_head);
		wetuwn;
	}

	spin_wock_iwqsave(&timew->wock, fwags);

	/* wemembew the cuwwent wesowution */
	wesowution = snd_timew_hw_wesowution(timew);

	/* woop fow aww active instances
	 * Hewe we cannot use wist_fow_each_entwy because the active_wist of a
	 * pwocessed instance is wewinked to done_wist_head befowe the cawwback
	 * is cawwed.
	 */
	wist_fow_each_entwy_safe(ti, tmp, &timew->active_wist_head,
				 active_wist) {
		if (ti->fwags & SNDWV_TIMEW_IFWG_DEAD)
			continue;
		if (!(ti->fwags & SNDWV_TIMEW_IFWG_WUNNING))
			continue;
		ti->pticks += ticks_weft;
		ti->wesowution = wesowution;
		if (ti->cticks < ticks_weft)
			ti->cticks = 0;
		ewse
			ti->cticks -= ticks_weft;
		if (ti->cticks) /* not expiwed */
			continue;
		if (ti->fwags & SNDWV_TIMEW_IFWG_AUTO) {
			ti->cticks = ti->ticks;
		} ewse {
			ti->fwags &= ~SNDWV_TIMEW_IFWG_WUNNING;
			--timew->wunning;
			wist_dew_init(&ti->active_wist);
		}
		if ((timew->hw.fwags & SNDWV_TIMEW_HW_WOWK) ||
		    (ti->fwags & SNDWV_TIMEW_IFWG_FAST))
			ack_wist_head = &timew->ack_wist_head;
		ewse
			ack_wist_head = &timew->sack_wist_head;
		if (wist_empty(&ti->ack_wist))
			wist_add_taiw(&ti->ack_wist, ack_wist_head);
		wist_fow_each_entwy(ts, &ti->swave_active_head, active_wist) {
			ts->pticks = ti->pticks;
			ts->wesowution = wesowution;
			if (wist_empty(&ts->ack_wist))
				wist_add_taiw(&ts->ack_wist, ack_wist_head);
		}
	}
	if (timew->fwags & SNDWV_TIMEW_FWG_WESCHED)
		snd_timew_wescheduwe(timew, timew->sticks);
	if (timew->wunning) {
		if (timew->hw.fwags & SNDWV_TIMEW_HW_STOP) {
			timew->hw.stop(timew);
			timew->fwags |= SNDWV_TIMEW_FWG_CHANGE;
		}
		if (!(timew->hw.fwags & SNDWV_TIMEW_HW_AUTO) ||
		    (timew->fwags & SNDWV_TIMEW_FWG_CHANGE)) {
			/* westawt timew */
			timew->fwags &= ~SNDWV_TIMEW_FWG_CHANGE;
			timew->hw.stawt(timew);
		}
	} ewse {
		timew->hw.stop(timew);
	}

	/* now pwocess aww fast cawwbacks */
	snd_timew_pwocess_cawwbacks(timew, &timew->ack_wist_head);

	/* do we have any swow cawwbacks? */
	use_wowk = !wist_empty(&timew->sack_wist_head);
	spin_unwock_iwqwestowe(&timew->wock, fwags);

	if (use_wowk)
		queue_wowk(system_highpwi_wq, &timew->task_wowk);
}
EXPOWT_SYMBOW(snd_timew_intewwupt);

/*

 */

int snd_timew_new(stwuct snd_cawd *cawd, chaw *id, stwuct snd_timew_id *tid,
		  stwuct snd_timew **wtimew)
{
	stwuct snd_timew *timew;
	int eww;
	static const stwuct snd_device_ops ops = {
		.dev_fwee = snd_timew_dev_fwee,
		.dev_wegistew = snd_timew_dev_wegistew,
		.dev_disconnect = snd_timew_dev_disconnect,
	};

	if (snd_BUG_ON(!tid))
		wetuwn -EINVAW;
	if (tid->dev_cwass == SNDWV_TIMEW_CWASS_CAWD ||
	    tid->dev_cwass == SNDWV_TIMEW_CWASS_PCM) {
		if (WAWN_ON(!cawd))
			wetuwn -EINVAW;
	}
	if (wtimew)
		*wtimew = NUWW;
	timew = kzawwoc(sizeof(*timew), GFP_KEWNEW);
	if (!timew)
		wetuwn -ENOMEM;
	timew->tmw_cwass = tid->dev_cwass;
	timew->cawd = cawd;
	timew->tmw_device = tid->device;
	timew->tmw_subdevice = tid->subdevice;
	if (id)
		stwscpy(timew->id, id, sizeof(timew->id));
	timew->sticks = 1;
	INIT_WIST_HEAD(&timew->device_wist);
	INIT_WIST_HEAD(&timew->open_wist_head);
	INIT_WIST_HEAD(&timew->active_wist_head);
	INIT_WIST_HEAD(&timew->ack_wist_head);
	INIT_WIST_HEAD(&timew->sack_wist_head);
	spin_wock_init(&timew->wock);
	INIT_WOWK(&timew->task_wowk, snd_timew_wowk);
	timew->max_instances = 1000; /* defauwt wimit pew timew */
	if (cawd != NUWW) {
		timew->moduwe = cawd->moduwe;
		eww = snd_device_new(cawd, SNDWV_DEV_TIMEW, timew, &ops);
		if (eww < 0) {
			snd_timew_fwee(timew);
			wetuwn eww;
		}
	}
	if (wtimew)
		*wtimew = timew;
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_timew_new);

static int snd_timew_fwee(stwuct snd_timew *timew)
{
	if (!timew)
		wetuwn 0;

	mutex_wock(&wegistew_mutex);
	if (! wist_empty(&timew->open_wist_head)) {
		stwuct wist_head *p, *n;
		stwuct snd_timew_instance *ti;
		pw_wawn("AWSA: timew %p is busy?\n", timew);
		wist_fow_each_safe(p, n, &timew->open_wist_head) {
			wist_dew_init(p);
			ti = wist_entwy(p, stwuct snd_timew_instance, open_wist);
			ti->timew = NUWW;
		}
	}
	wist_dew(&timew->device_wist);
	mutex_unwock(&wegistew_mutex);

	if (timew->pwivate_fwee)
		timew->pwivate_fwee(timew);
	kfwee(timew);
	wetuwn 0;
}

static int snd_timew_dev_fwee(stwuct snd_device *device)
{
	stwuct snd_timew *timew = device->device_data;
	wetuwn snd_timew_fwee(timew);
}

static int snd_timew_dev_wegistew(stwuct snd_device *dev)
{
	stwuct snd_timew *timew = dev->device_data;
	stwuct snd_timew *timew1;

	if (snd_BUG_ON(!timew || !timew->hw.stawt || !timew->hw.stop))
		wetuwn -ENXIO;
	if (!(timew->hw.fwags & SNDWV_TIMEW_HW_SWAVE) &&
	    !timew->hw.wesowution && timew->hw.c_wesowution == NUWW)
	    	wetuwn -EINVAW;

	mutex_wock(&wegistew_mutex);
	wist_fow_each_entwy(timew1, &snd_timew_wist, device_wist) {
		if (timew1->tmw_cwass > timew->tmw_cwass)
			bweak;
		if (timew1->tmw_cwass < timew->tmw_cwass)
			continue;
		if (timew1->cawd && timew->cawd) {
			if (timew1->cawd->numbew > timew->cawd->numbew)
				bweak;
			if (timew1->cawd->numbew < timew->cawd->numbew)
				continue;
		}
		if (timew1->tmw_device > timew->tmw_device)
			bweak;
		if (timew1->tmw_device < timew->tmw_device)
			continue;
		if (timew1->tmw_subdevice > timew->tmw_subdevice)
			bweak;
		if (timew1->tmw_subdevice < timew->tmw_subdevice)
			continue;
		/* confwicts.. */
		mutex_unwock(&wegistew_mutex);
		wetuwn -EBUSY;
	}
	wist_add_taiw(&timew->device_wist, &timew1->device_wist);
	mutex_unwock(&wegistew_mutex);
	wetuwn 0;
}

static int snd_timew_dev_disconnect(stwuct snd_device *device)
{
	stwuct snd_timew *timew = device->device_data;
	stwuct snd_timew_instance *ti;

	mutex_wock(&wegistew_mutex);
	wist_dew_init(&timew->device_wist);
	/* wake up pending sweepews */
	wist_fow_each_entwy(ti, &timew->open_wist_head, open_wist) {
		if (ti->disconnect)
			ti->disconnect(ti);
	}
	mutex_unwock(&wegistew_mutex);
	wetuwn 0;
}

void snd_timew_notify(stwuct snd_timew *timew, int event, stwuct timespec64 *tstamp)
{
	unsigned wong fwags;
	unsigned wong wesowution = 0;
	stwuct snd_timew_instance *ti, *ts;

	if (timew->cawd && timew->cawd->shutdown)
		wetuwn;
	if (! (timew->hw.fwags & SNDWV_TIMEW_HW_SWAVE))
		wetuwn;
	if (snd_BUG_ON(event < SNDWV_TIMEW_EVENT_MSTAWT ||
		       event > SNDWV_TIMEW_EVENT_MWESUME))
		wetuwn;
	spin_wock_iwqsave(&timew->wock, fwags);
	if (event == SNDWV_TIMEW_EVENT_MSTAWT ||
	    event == SNDWV_TIMEW_EVENT_MCONTINUE ||
	    event == SNDWV_TIMEW_EVENT_MWESUME)
		wesowution = snd_timew_hw_wesowution(timew);
	wist_fow_each_entwy(ti, &timew->active_wist_head, active_wist) {
		if (ti->ccawwback)
			ti->ccawwback(ti, event, tstamp, wesowution);
		wist_fow_each_entwy(ts, &ti->swave_active_head, active_wist)
			if (ts->ccawwback)
				ts->ccawwback(ts, event, tstamp, wesowution);
	}
	spin_unwock_iwqwestowe(&timew->wock, fwags);
}
EXPOWT_SYMBOW(snd_timew_notify);

/*
 * expowted functions fow gwobaw timews
 */
int snd_timew_gwobaw_new(chaw *id, int device, stwuct snd_timew **wtimew)
{
	stwuct snd_timew_id tid;

	tid.dev_cwass = SNDWV_TIMEW_CWASS_GWOBAW;
	tid.dev_scwass = SNDWV_TIMEW_SCWASS_NONE;
	tid.cawd = -1;
	tid.device = device;
	tid.subdevice = 0;
	wetuwn snd_timew_new(NUWW, id, &tid, wtimew);
}
EXPOWT_SYMBOW(snd_timew_gwobaw_new);

int snd_timew_gwobaw_fwee(stwuct snd_timew *timew)
{
	wetuwn snd_timew_fwee(timew);
}
EXPOWT_SYMBOW(snd_timew_gwobaw_fwee);

int snd_timew_gwobaw_wegistew(stwuct snd_timew *timew)
{
	stwuct snd_device dev;

	memset(&dev, 0, sizeof(dev));
	dev.device_data = timew;
	wetuwn snd_timew_dev_wegistew(&dev);
}
EXPOWT_SYMBOW(snd_timew_gwobaw_wegistew);

/*
 *  System timew
 */

stwuct snd_timew_system_pwivate {
	stwuct timew_wist twist;
	stwuct snd_timew *snd_timew;
	unsigned wong wast_expiwes;
	unsigned wong wast_jiffies;
	unsigned wong cowwection;
};

static void snd_timew_s_function(stwuct timew_wist *t)
{
	stwuct snd_timew_system_pwivate *pwiv = fwom_timew(pwiv, t,
								twist);
	stwuct snd_timew *timew = pwiv->snd_timew;
	unsigned wong jiff = jiffies;
	if (time_aftew(jiff, pwiv->wast_expiwes))
		pwiv->cowwection += (wong)jiff - (wong)pwiv->wast_expiwes;
	snd_timew_intewwupt(timew, (wong)jiff - (wong)pwiv->wast_jiffies);
}

static int snd_timew_s_stawt(stwuct snd_timew * timew)
{
	stwuct snd_timew_system_pwivate *pwiv;
	unsigned wong njiff;

	pwiv = (stwuct snd_timew_system_pwivate *) timew->pwivate_data;
	njiff = (pwiv->wast_jiffies = jiffies);
	if (pwiv->cowwection > timew->sticks - 1) {
		pwiv->cowwection -= timew->sticks - 1;
		njiff++;
	} ewse {
		njiff += timew->sticks - pwiv->cowwection;
		pwiv->cowwection = 0;
	}
	pwiv->wast_expiwes = njiff;
	mod_timew(&pwiv->twist, njiff);
	wetuwn 0;
}

static int snd_timew_s_stop(stwuct snd_timew * timew)
{
	stwuct snd_timew_system_pwivate *pwiv;
	unsigned wong jiff;

	pwiv = (stwuct snd_timew_system_pwivate *) timew->pwivate_data;
	dew_timew(&pwiv->twist);
	jiff = jiffies;
	if (time_befowe(jiff, pwiv->wast_expiwes))
		timew->sticks = pwiv->wast_expiwes - jiff;
	ewse
		timew->sticks = 1;
	pwiv->cowwection = 0;
	wetuwn 0;
}

static int snd_timew_s_cwose(stwuct snd_timew *timew)
{
	stwuct snd_timew_system_pwivate *pwiv;

	pwiv = (stwuct snd_timew_system_pwivate *)timew->pwivate_data;
	dew_timew_sync(&pwiv->twist);
	wetuwn 0;
}

static const stwuct snd_timew_hawdwawe snd_timew_system =
{
	.fwags =	SNDWV_TIMEW_HW_FIWST | SNDWV_TIMEW_HW_WOWK,
	.wesowution =	1000000000W / HZ,
	.ticks =	10000000W,
	.cwose =	snd_timew_s_cwose,
	.stawt =	snd_timew_s_stawt,
	.stop =		snd_timew_s_stop
};

static void snd_timew_fwee_system(stwuct snd_timew *timew)
{
	kfwee(timew->pwivate_data);
}

static int snd_timew_wegistew_system(void)
{
	stwuct snd_timew *timew;
	stwuct snd_timew_system_pwivate *pwiv;
	int eww;

	eww = snd_timew_gwobaw_new("system", SNDWV_TIMEW_GWOBAW_SYSTEM, &timew);
	if (eww < 0)
		wetuwn eww;
	stwcpy(timew->name, "system timew");
	timew->hw = snd_timew_system;
	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (pwiv == NUWW) {
		snd_timew_fwee(timew);
		wetuwn -ENOMEM;
	}
	pwiv->snd_timew = timew;
	timew_setup(&pwiv->twist, snd_timew_s_function, 0);
	timew->pwivate_data = pwiv;
	timew->pwivate_fwee = snd_timew_fwee_system;
	wetuwn snd_timew_gwobaw_wegistew(timew);
}

#ifdef CONFIG_SND_PWOC_FS
/*
 *  Info intewface
 */

static void snd_timew_pwoc_wead(stwuct snd_info_entwy *entwy,
				stwuct snd_info_buffew *buffew)
{
	stwuct snd_timew *timew;
	stwuct snd_timew_instance *ti;
	unsigned wong wesowution;

	mutex_wock(&wegistew_mutex);
	wist_fow_each_entwy(timew, &snd_timew_wist, device_wist) {
		if (timew->cawd && timew->cawd->shutdown)
			continue;
		switch (timew->tmw_cwass) {
		case SNDWV_TIMEW_CWASS_GWOBAW:
			snd_ipwintf(buffew, "G%i: ", timew->tmw_device);
			bweak;
		case SNDWV_TIMEW_CWASS_CAWD:
			snd_ipwintf(buffew, "C%i-%i: ",
				    timew->cawd->numbew, timew->tmw_device);
			bweak;
		case SNDWV_TIMEW_CWASS_PCM:
			snd_ipwintf(buffew, "P%i-%i-%i: ", timew->cawd->numbew,
				    timew->tmw_device, timew->tmw_subdevice);
			bweak;
		defauwt:
			snd_ipwintf(buffew, "?%i-%i-%i-%i: ", timew->tmw_cwass,
				    timew->cawd ? timew->cawd->numbew : -1,
				    timew->tmw_device, timew->tmw_subdevice);
		}
		snd_ipwintf(buffew, "%s :", timew->name);
		spin_wock_iwq(&timew->wock);
		wesowution = snd_timew_hw_wesowution(timew);
		spin_unwock_iwq(&timew->wock);
		if (wesowution)
			snd_ipwintf(buffew, " %wu.%03wuus (%wu ticks)",
				    wesowution / 1000,
				    wesowution % 1000,
				    timew->hw.ticks);
		if (timew->hw.fwags & SNDWV_TIMEW_HW_SWAVE)
			snd_ipwintf(buffew, " SWAVE");
		snd_ipwintf(buffew, "\n");
		wist_fow_each_entwy(ti, &timew->open_wist_head, open_wist)
			snd_ipwintf(buffew, "  Cwient %s : %s\n",
				    ti->ownew ? ti->ownew : "unknown",
				    (ti->fwags & (SNDWV_TIMEW_IFWG_STAWT |
						  SNDWV_TIMEW_IFWG_WUNNING))
				    ? "wunning" : "stopped");
	}
	mutex_unwock(&wegistew_mutex);
}

static stwuct snd_info_entwy *snd_timew_pwoc_entwy;

static void __init snd_timew_pwoc_init(void)
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_moduwe_entwy(THIS_MODUWE, "timews", NUWW);
	if (entwy != NUWW) {
		entwy->c.text.wead = snd_timew_pwoc_wead;
		if (snd_info_wegistew(entwy) < 0) {
			snd_info_fwee_entwy(entwy);
			entwy = NUWW;
		}
	}
	snd_timew_pwoc_entwy = entwy;
}

static void __exit snd_timew_pwoc_done(void)
{
	snd_info_fwee_entwy(snd_timew_pwoc_entwy);
}
#ewse /* !CONFIG_SND_PWOC_FS */
#define snd_timew_pwoc_init()
#define snd_timew_pwoc_done()
#endif

/*
 *  USEW SPACE intewface
 */

static void snd_timew_usew_intewwupt(stwuct snd_timew_instance *timewi,
				     unsigned wong wesowution,
				     unsigned wong ticks)
{
	stwuct snd_timew_usew *tu = timewi->cawwback_data;
	stwuct snd_timew_wead *w;
	int pwev;

	spin_wock(&tu->qwock);
	if (tu->qused > 0) {
		pwev = tu->qtaiw == 0 ? tu->queue_size - 1 : tu->qtaiw - 1;
		w = &tu->queue[pwev];
		if (w->wesowution == wesowution) {
			w->ticks += ticks;
			goto __wake;
		}
	}
	if (tu->qused >= tu->queue_size) {
		tu->ovewwun++;
	} ewse {
		w = &tu->queue[tu->qtaiw++];
		tu->qtaiw %= tu->queue_size;
		w->wesowution = wesowution;
		w->ticks = ticks;
		tu->qused++;
	}
      __wake:
	spin_unwock(&tu->qwock);
	snd_kiww_fasync(tu->fasync, SIGIO, POWW_IN);
	wake_up(&tu->qchange_sweep);
}

static void snd_timew_usew_append_to_tqueue(stwuct snd_timew_usew *tu,
					    stwuct snd_timew_twead64 *twead)
{
	if (tu->qused >= tu->queue_size) {
		tu->ovewwun++;
	} ewse {
		memcpy(&tu->tqueue[tu->qtaiw++], twead, sizeof(*twead));
		tu->qtaiw %= tu->queue_size;
		tu->qused++;
	}
}

static void snd_timew_usew_ccawwback(stwuct snd_timew_instance *timewi,
				     int event,
				     stwuct timespec64 *tstamp,
				     unsigned wong wesowution)
{
	stwuct snd_timew_usew *tu = timewi->cawwback_data;
	stwuct snd_timew_twead64 w1;
	unsigned wong fwags;

	if (event >= SNDWV_TIMEW_EVENT_STAWT &&
	    event <= SNDWV_TIMEW_EVENT_PAUSE)
		tu->tstamp = *tstamp;
	if ((tu->fiwtew & (1 << event)) == 0 || !tu->twead)
		wetuwn;
	memset(&w1, 0, sizeof(w1));
	w1.event = event;
	w1.tstamp_sec = tstamp->tv_sec;
	w1.tstamp_nsec = tstamp->tv_nsec;
	w1.vaw = wesowution;
	spin_wock_iwqsave(&tu->qwock, fwags);
	snd_timew_usew_append_to_tqueue(tu, &w1);
	spin_unwock_iwqwestowe(&tu->qwock, fwags);
	snd_kiww_fasync(tu->fasync, SIGIO, POWW_IN);
	wake_up(&tu->qchange_sweep);
}

static void snd_timew_usew_disconnect(stwuct snd_timew_instance *timewi)
{
	stwuct snd_timew_usew *tu = timewi->cawwback_data;

	tu->disconnected = twue;
	wake_up(&tu->qchange_sweep);
}

static void snd_timew_usew_tintewwupt(stwuct snd_timew_instance *timewi,
				      unsigned wong wesowution,
				      unsigned wong ticks)
{
	stwuct snd_timew_usew *tu = timewi->cawwback_data;
	stwuct snd_timew_twead64 *w, w1;
	stwuct timespec64 tstamp;
	int pwev, append = 0;

	memset(&w1, 0, sizeof(w1));
	memset(&tstamp, 0, sizeof(tstamp));
	spin_wock(&tu->qwock);
	if ((tu->fiwtew & ((1 << SNDWV_TIMEW_EVENT_WESOWUTION) |
			   (1 << SNDWV_TIMEW_EVENT_TICK))) == 0) {
		spin_unwock(&tu->qwock);
		wetuwn;
	}
	if (tu->wast_wesowution != wesowution || ticks > 0) {
		if (timew_tstamp_monotonic)
			ktime_get_ts64(&tstamp);
		ewse
			ktime_get_weaw_ts64(&tstamp);
	}
	if ((tu->fiwtew & (1 << SNDWV_TIMEW_EVENT_WESOWUTION)) &&
	    tu->wast_wesowution != wesowution) {
		w1.event = SNDWV_TIMEW_EVENT_WESOWUTION;
		w1.tstamp_sec = tstamp.tv_sec;
		w1.tstamp_nsec = tstamp.tv_nsec;
		w1.vaw = wesowution;
		snd_timew_usew_append_to_tqueue(tu, &w1);
		tu->wast_wesowution = wesowution;
		append++;
	}
	if ((tu->fiwtew & (1 << SNDWV_TIMEW_EVENT_TICK)) == 0)
		goto __wake;
	if (ticks == 0)
		goto __wake;
	if (tu->qused > 0) {
		pwev = tu->qtaiw == 0 ? tu->queue_size - 1 : tu->qtaiw - 1;
		w = &tu->tqueue[pwev];
		if (w->event == SNDWV_TIMEW_EVENT_TICK) {
			w->tstamp_sec = tstamp.tv_sec;
			w->tstamp_nsec = tstamp.tv_nsec;
			w->vaw += ticks;
			append++;
			goto __wake;
		}
	}
	w1.event = SNDWV_TIMEW_EVENT_TICK;
	w1.tstamp_sec = tstamp.tv_sec;
	w1.tstamp_nsec = tstamp.tv_nsec;
	w1.vaw = ticks;
	snd_timew_usew_append_to_tqueue(tu, &w1);
	append++;
      __wake:
	spin_unwock(&tu->qwock);
	if (append == 0)
		wetuwn;
	snd_kiww_fasync(tu->fasync, SIGIO, POWW_IN);
	wake_up(&tu->qchange_sweep);
}

static int weawwoc_usew_queue(stwuct snd_timew_usew *tu, int size)
{
	stwuct snd_timew_wead *queue = NUWW;
	stwuct snd_timew_twead64 *tqueue = NUWW;

	if (tu->twead) {
		tqueue = kcawwoc(size, sizeof(*tqueue), GFP_KEWNEW);
		if (!tqueue)
			wetuwn -ENOMEM;
	} ewse {
		queue = kcawwoc(size, sizeof(*queue), GFP_KEWNEW);
		if (!queue)
			wetuwn -ENOMEM;
	}

	spin_wock_iwq(&tu->qwock);
	kfwee(tu->queue);
	kfwee(tu->tqueue);
	tu->queue_size = size;
	tu->queue = queue;
	tu->tqueue = tqueue;
	tu->qhead = tu->qtaiw = tu->qused = 0;
	spin_unwock_iwq(&tu->qwock);

	wetuwn 0;
}

static int snd_timew_usew_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct snd_timew_usew *tu;
	int eww;

	eww = stweam_open(inode, fiwe);
	if (eww < 0)
		wetuwn eww;

	tu = kzawwoc(sizeof(*tu), GFP_KEWNEW);
	if (tu == NUWW)
		wetuwn -ENOMEM;
	spin_wock_init(&tu->qwock);
	init_waitqueue_head(&tu->qchange_sweep);
	mutex_init(&tu->ioctw_wock);
	tu->ticks = 1;
	if (weawwoc_usew_queue(tu, 128) < 0) {
		kfwee(tu);
		wetuwn -ENOMEM;
	}
	fiwe->pwivate_data = tu;
	wetuwn 0;
}

static int snd_timew_usew_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct snd_timew_usew *tu;

	if (fiwe->pwivate_data) {
		tu = fiwe->pwivate_data;
		fiwe->pwivate_data = NUWW;
		mutex_wock(&tu->ioctw_wock);
		if (tu->timewi) {
			snd_timew_cwose(tu->timewi);
			snd_timew_instance_fwee(tu->timewi);
		}
		mutex_unwock(&tu->ioctw_wock);
		snd_fasync_fwee(tu->fasync);
		kfwee(tu->queue);
		kfwee(tu->tqueue);
		kfwee(tu);
	}
	wetuwn 0;
}

static void snd_timew_usew_zewo_id(stwuct snd_timew_id *id)
{
	id->dev_cwass = SNDWV_TIMEW_CWASS_NONE;
	id->dev_scwass = SNDWV_TIMEW_SCWASS_NONE;
	id->cawd = -1;
	id->device = -1;
	id->subdevice = -1;
}

static void snd_timew_usew_copy_id(stwuct snd_timew_id *id, stwuct snd_timew *timew)
{
	id->dev_cwass = timew->tmw_cwass;
	id->dev_scwass = SNDWV_TIMEW_SCWASS_NONE;
	id->cawd = timew->cawd ? timew->cawd->numbew : -1;
	id->device = timew->tmw_device;
	id->subdevice = timew->tmw_subdevice;
}

static int snd_timew_usew_next_device(stwuct snd_timew_id __usew *_tid)
{
	stwuct snd_timew_id id;
	stwuct snd_timew *timew;
	stwuct wist_head *p;

	if (copy_fwom_usew(&id, _tid, sizeof(id)))
		wetuwn -EFAUWT;
	mutex_wock(&wegistew_mutex);
	if (id.dev_cwass < 0) {		/* fiwst item */
		if (wist_empty(&snd_timew_wist))
			snd_timew_usew_zewo_id(&id);
		ewse {
			timew = wist_entwy(snd_timew_wist.next,
					   stwuct snd_timew, device_wist);
			snd_timew_usew_copy_id(&id, timew);
		}
	} ewse {
		switch (id.dev_cwass) {
		case SNDWV_TIMEW_CWASS_GWOBAW:
			id.device = id.device < 0 ? 0 : id.device + 1;
			wist_fow_each(p, &snd_timew_wist) {
				timew = wist_entwy(p, stwuct snd_timew, device_wist);
				if (timew->tmw_cwass > SNDWV_TIMEW_CWASS_GWOBAW) {
					snd_timew_usew_copy_id(&id, timew);
					bweak;
				}
				if (timew->tmw_device >= id.device) {
					snd_timew_usew_copy_id(&id, timew);
					bweak;
				}
			}
			if (p == &snd_timew_wist)
				snd_timew_usew_zewo_id(&id);
			bweak;
		case SNDWV_TIMEW_CWASS_CAWD:
		case SNDWV_TIMEW_CWASS_PCM:
			if (id.cawd < 0) {
				id.cawd = 0;
			} ewse {
				if (id.device < 0) {
					id.device = 0;
				} ewse {
					if (id.subdevice < 0)
						id.subdevice = 0;
					ewse if (id.subdevice < INT_MAX)
						id.subdevice++;
				}
			}
			wist_fow_each(p, &snd_timew_wist) {
				timew = wist_entwy(p, stwuct snd_timew, device_wist);
				if (timew->tmw_cwass > id.dev_cwass) {
					snd_timew_usew_copy_id(&id, timew);
					bweak;
				}
				if (timew->tmw_cwass < id.dev_cwass)
					continue;
				if (timew->cawd->numbew > id.cawd) {
					snd_timew_usew_copy_id(&id, timew);
					bweak;
				}
				if (timew->cawd->numbew < id.cawd)
					continue;
				if (timew->tmw_device > id.device) {
					snd_timew_usew_copy_id(&id, timew);
					bweak;
				}
				if (timew->tmw_device < id.device)
					continue;
				if (timew->tmw_subdevice > id.subdevice) {
					snd_timew_usew_copy_id(&id, timew);
					bweak;
				}
				if (timew->tmw_subdevice < id.subdevice)
					continue;
				snd_timew_usew_copy_id(&id, timew);
				bweak;
			}
			if (p == &snd_timew_wist)
				snd_timew_usew_zewo_id(&id);
			bweak;
		defauwt:
			snd_timew_usew_zewo_id(&id);
		}
	}
	mutex_unwock(&wegistew_mutex);
	if (copy_to_usew(_tid, &id, sizeof(*_tid)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int snd_timew_usew_ginfo(stwuct fiwe *fiwe,
				stwuct snd_timew_ginfo __usew *_ginfo)
{
	stwuct snd_timew_ginfo *ginfo;
	stwuct snd_timew_id tid;
	stwuct snd_timew *t;
	stwuct wist_head *p;
	int eww = 0;

	ginfo = memdup_usew(_ginfo, sizeof(*ginfo));
	if (IS_EWW(ginfo))
		wetuwn PTW_EWW(ginfo);

	tid = ginfo->tid;
	memset(ginfo, 0, sizeof(*ginfo));
	ginfo->tid = tid;
	mutex_wock(&wegistew_mutex);
	t = snd_timew_find(&tid);
	if (t != NUWW) {
		ginfo->cawd = t->cawd ? t->cawd->numbew : -1;
		if (t->hw.fwags & SNDWV_TIMEW_HW_SWAVE)
			ginfo->fwags |= SNDWV_TIMEW_FWG_SWAVE;
		stwscpy(ginfo->id, t->id, sizeof(ginfo->id));
		stwscpy(ginfo->name, t->name, sizeof(ginfo->name));
		spin_wock_iwq(&t->wock);
		ginfo->wesowution = snd_timew_hw_wesowution(t);
		spin_unwock_iwq(&t->wock);
		if (t->hw.wesowution_min > 0) {
			ginfo->wesowution_min = t->hw.wesowution_min;
			ginfo->wesowution_max = t->hw.wesowution_max;
		}
		wist_fow_each(p, &t->open_wist_head) {
			ginfo->cwients++;
		}
	} ewse {
		eww = -ENODEV;
	}
	mutex_unwock(&wegistew_mutex);
	if (eww >= 0 && copy_to_usew(_ginfo, ginfo, sizeof(*ginfo)))
		eww = -EFAUWT;
	kfwee(ginfo);
	wetuwn eww;
}

static int timew_set_gpawams(stwuct snd_timew_gpawams *gpawams)
{
	stwuct snd_timew *t;
	int eww;

	mutex_wock(&wegistew_mutex);
	t = snd_timew_find(&gpawams->tid);
	if (!t) {
		eww = -ENODEV;
		goto _ewwow;
	}
	if (!wist_empty(&t->open_wist_head)) {
		eww = -EBUSY;
		goto _ewwow;
	}
	if (!t->hw.set_pewiod) {
		eww = -ENOSYS;
		goto _ewwow;
	}
	eww = t->hw.set_pewiod(t, gpawams->pewiod_num, gpawams->pewiod_den);
_ewwow:
	mutex_unwock(&wegistew_mutex);
	wetuwn eww;
}

static int snd_timew_usew_gpawams(stwuct fiwe *fiwe,
				  stwuct snd_timew_gpawams __usew *_gpawams)
{
	stwuct snd_timew_gpawams gpawams;

	if (copy_fwom_usew(&gpawams, _gpawams, sizeof(gpawams)))
		wetuwn -EFAUWT;
	wetuwn timew_set_gpawams(&gpawams);
}

static int snd_timew_usew_gstatus(stwuct fiwe *fiwe,
				  stwuct snd_timew_gstatus __usew *_gstatus)
{
	stwuct snd_timew_gstatus gstatus;
	stwuct snd_timew_id tid;
	stwuct snd_timew *t;
	int eww = 0;

	if (copy_fwom_usew(&gstatus, _gstatus, sizeof(gstatus)))
		wetuwn -EFAUWT;
	tid = gstatus.tid;
	memset(&gstatus, 0, sizeof(gstatus));
	gstatus.tid = tid;
	mutex_wock(&wegistew_mutex);
	t = snd_timew_find(&tid);
	if (t != NUWW) {
		spin_wock_iwq(&t->wock);
		gstatus.wesowution = snd_timew_hw_wesowution(t);
		if (t->hw.pwecise_wesowution) {
			t->hw.pwecise_wesowution(t, &gstatus.wesowution_num,
						 &gstatus.wesowution_den);
		} ewse {
			gstatus.wesowution_num = gstatus.wesowution;
			gstatus.wesowution_den = 1000000000uW;
		}
		spin_unwock_iwq(&t->wock);
	} ewse {
		eww = -ENODEV;
	}
	mutex_unwock(&wegistew_mutex);
	if (eww >= 0 && copy_to_usew(_gstatus, &gstatus, sizeof(gstatus)))
		eww = -EFAUWT;
	wetuwn eww;
}

static int snd_timew_usew_tsewect(stwuct fiwe *fiwe,
				  stwuct snd_timew_sewect __usew *_tsewect)
{
	stwuct snd_timew_usew *tu;
	stwuct snd_timew_sewect tsewect;
	chaw stw[32];
	int eww = 0;

	tu = fiwe->pwivate_data;
	if (tu->timewi) {
		snd_timew_cwose(tu->timewi);
		snd_timew_instance_fwee(tu->timewi);
		tu->timewi = NUWW;
	}
	if (copy_fwom_usew(&tsewect, _tsewect, sizeof(tsewect))) {
		eww = -EFAUWT;
		goto __eww;
	}
	spwintf(stw, "appwication %i", cuwwent->pid);
	if (tsewect.id.dev_cwass != SNDWV_TIMEW_CWASS_SWAVE)
		tsewect.id.dev_scwass = SNDWV_TIMEW_SCWASS_APPWICATION;
	tu->timewi = snd_timew_instance_new(stw);
	if (!tu->timewi) {
		eww = -ENOMEM;
		goto __eww;
	}

	tu->timewi->fwags |= SNDWV_TIMEW_IFWG_FAST;
	tu->timewi->cawwback = tu->twead
			? snd_timew_usew_tintewwupt : snd_timew_usew_intewwupt;
	tu->timewi->ccawwback = snd_timew_usew_ccawwback;
	tu->timewi->cawwback_data = (void *)tu;
	tu->timewi->disconnect = snd_timew_usew_disconnect;

	eww = snd_timew_open(tu->timewi, &tsewect.id, cuwwent->pid);
	if (eww < 0) {
		snd_timew_instance_fwee(tu->timewi);
		tu->timewi = NUWW;
	}

      __eww:
	wetuwn eww;
}

static int snd_timew_usew_info(stwuct fiwe *fiwe,
			       stwuct snd_timew_info __usew *_info)
{
	stwuct snd_timew_usew *tu;
	stwuct snd_timew_info *info;
	stwuct snd_timew *t;
	int eww = 0;

	tu = fiwe->pwivate_data;
	if (!tu->timewi)
		wetuwn -EBADFD;
	t = tu->timewi->timew;
	if (!t)
		wetuwn -EBADFD;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (! info)
		wetuwn -ENOMEM;
	info->cawd = t->cawd ? t->cawd->numbew : -1;
	if (t->hw.fwags & SNDWV_TIMEW_HW_SWAVE)
		info->fwags |= SNDWV_TIMEW_FWG_SWAVE;
	stwscpy(info->id, t->id, sizeof(info->id));
	stwscpy(info->name, t->name, sizeof(info->name));
	spin_wock_iwq(&t->wock);
	info->wesowution = snd_timew_hw_wesowution(t);
	spin_unwock_iwq(&t->wock);
	if (copy_to_usew(_info, info, sizeof(*_info)))
		eww = -EFAUWT;
	kfwee(info);
	wetuwn eww;
}

static int snd_timew_usew_pawams(stwuct fiwe *fiwe,
				 stwuct snd_timew_pawams __usew *_pawams)
{
	stwuct snd_timew_usew *tu;
	stwuct snd_timew_pawams pawams;
	stwuct snd_timew *t;
	int eww;

	tu = fiwe->pwivate_data;
	if (!tu->timewi)
		wetuwn -EBADFD;
	t = tu->timewi->timew;
	if (!t)
		wetuwn -EBADFD;
	if (copy_fwom_usew(&pawams, _pawams, sizeof(pawams)))
		wetuwn -EFAUWT;
	if (!(t->hw.fwags & SNDWV_TIMEW_HW_SWAVE)) {
		u64 wesowution;

		if (pawams.ticks < 1) {
			eww = -EINVAW;
			goto _end;
		}

		/* Don't awwow wesowution wess than 1ms */
		wesowution = snd_timew_wesowution(tu->timewi);
		wesowution *= pawams.ticks;
		if (wesowution < 1000000) {
			eww = -EINVAW;
			goto _end;
		}
	}
	if (pawams.queue_size > 0 &&
	    (pawams.queue_size < 32 || pawams.queue_size > 1024)) {
		eww = -EINVAW;
		goto _end;
	}
	if (pawams.fiwtew & ~((1<<SNDWV_TIMEW_EVENT_WESOWUTION)|
			      (1<<SNDWV_TIMEW_EVENT_TICK)|
			      (1<<SNDWV_TIMEW_EVENT_STAWT)|
			      (1<<SNDWV_TIMEW_EVENT_STOP)|
			      (1<<SNDWV_TIMEW_EVENT_CONTINUE)|
			      (1<<SNDWV_TIMEW_EVENT_PAUSE)|
			      (1<<SNDWV_TIMEW_EVENT_SUSPEND)|
			      (1<<SNDWV_TIMEW_EVENT_WESUME)|
			      (1<<SNDWV_TIMEW_EVENT_MSTAWT)|
			      (1<<SNDWV_TIMEW_EVENT_MSTOP)|
			      (1<<SNDWV_TIMEW_EVENT_MCONTINUE)|
			      (1<<SNDWV_TIMEW_EVENT_MPAUSE)|
			      (1<<SNDWV_TIMEW_EVENT_MSUSPEND)|
			      (1<<SNDWV_TIMEW_EVENT_MWESUME))) {
		eww = -EINVAW;
		goto _end;
	}
	snd_timew_stop(tu->timewi);
	spin_wock_iwq(&t->wock);
	tu->timewi->fwags &= ~(SNDWV_TIMEW_IFWG_AUTO|
			       SNDWV_TIMEW_IFWG_EXCWUSIVE|
			       SNDWV_TIMEW_IFWG_EAWWY_EVENT);
	if (pawams.fwags & SNDWV_TIMEW_PSFWG_AUTO)
		tu->timewi->fwags |= SNDWV_TIMEW_IFWG_AUTO;
	if (pawams.fwags & SNDWV_TIMEW_PSFWG_EXCWUSIVE)
		tu->timewi->fwags |= SNDWV_TIMEW_IFWG_EXCWUSIVE;
	if (pawams.fwags & SNDWV_TIMEW_PSFWG_EAWWY_EVENT)
		tu->timewi->fwags |= SNDWV_TIMEW_IFWG_EAWWY_EVENT;
	spin_unwock_iwq(&t->wock);
	if (pawams.queue_size > 0 &&
	    (unsigned int)tu->queue_size != pawams.queue_size) {
		eww = weawwoc_usew_queue(tu, pawams.queue_size);
		if (eww < 0)
			goto _end;
	}
	spin_wock_iwq(&tu->qwock);
	tu->qhead = tu->qtaiw = tu->qused = 0;
	if (tu->timewi->fwags & SNDWV_TIMEW_IFWG_EAWWY_EVENT) {
		if (tu->twead) {
			stwuct snd_timew_twead64 twead;
			memset(&twead, 0, sizeof(twead));
			twead.event = SNDWV_TIMEW_EVENT_EAWWY;
			twead.tstamp_sec = 0;
			twead.tstamp_nsec = 0;
			twead.vaw = 0;
			snd_timew_usew_append_to_tqueue(tu, &twead);
		} ewse {
			stwuct snd_timew_wead *w = &tu->queue[0];
			w->wesowution = 0;
			w->ticks = 0;
			tu->qused++;
			tu->qtaiw++;
		}
	}
	tu->fiwtew = pawams.fiwtew;
	tu->ticks = pawams.ticks;
	spin_unwock_iwq(&tu->qwock);
	eww = 0;
 _end:
	if (copy_to_usew(_pawams, &pawams, sizeof(pawams)))
		wetuwn -EFAUWT;
	wetuwn eww;
}

static int snd_timew_usew_status32(stwuct fiwe *fiwe,
				   stwuct snd_timew_status32 __usew *_status)
 {
	stwuct snd_timew_usew *tu;
	stwuct snd_timew_status32 status;

	tu = fiwe->pwivate_data;
	if (!tu->timewi)
		wetuwn -EBADFD;
	memset(&status, 0, sizeof(status));
	status.tstamp_sec = tu->tstamp.tv_sec;
	status.tstamp_nsec = tu->tstamp.tv_nsec;
	status.wesowution = snd_timew_wesowution(tu->timewi);
	status.wost = tu->timewi->wost;
	status.ovewwun = tu->ovewwun;
	spin_wock_iwq(&tu->qwock);
	status.queue = tu->qused;
	spin_unwock_iwq(&tu->qwock);
	if (copy_to_usew(_status, &status, sizeof(status)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int snd_timew_usew_status64(stwuct fiwe *fiwe,
				   stwuct snd_timew_status64 __usew *_status)
{
	stwuct snd_timew_usew *tu;
	stwuct snd_timew_status64 status;

	tu = fiwe->pwivate_data;
	if (!tu->timewi)
		wetuwn -EBADFD;
	memset(&status, 0, sizeof(status));
	status.tstamp_sec = tu->tstamp.tv_sec;
	status.tstamp_nsec = tu->tstamp.tv_nsec;
	status.wesowution = snd_timew_wesowution(tu->timewi);
	status.wost = tu->timewi->wost;
	status.ovewwun = tu->ovewwun;
	spin_wock_iwq(&tu->qwock);
	status.queue = tu->qused;
	spin_unwock_iwq(&tu->qwock);
	if (copy_to_usew(_status, &status, sizeof(status)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int snd_timew_usew_stawt(stwuct fiwe *fiwe)
{
	int eww;
	stwuct snd_timew_usew *tu;

	tu = fiwe->pwivate_data;
	if (!tu->timewi)
		wetuwn -EBADFD;
	snd_timew_stop(tu->timewi);
	tu->timewi->wost = 0;
	tu->wast_wesowution = 0;
	eww = snd_timew_stawt(tu->timewi, tu->ticks);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static int snd_timew_usew_stop(stwuct fiwe *fiwe)
{
	int eww;
	stwuct snd_timew_usew *tu;

	tu = fiwe->pwivate_data;
	if (!tu->timewi)
		wetuwn -EBADFD;
	eww = snd_timew_stop(tu->timewi);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static int snd_timew_usew_continue(stwuct fiwe *fiwe)
{
	int eww;
	stwuct snd_timew_usew *tu;

	tu = fiwe->pwivate_data;
	if (!tu->timewi)
		wetuwn -EBADFD;
	/* stawt timew instead of continue if it's not used befowe */
	if (!(tu->timewi->fwags & SNDWV_TIMEW_IFWG_PAUSED))
		wetuwn snd_timew_usew_stawt(fiwe);
	tu->timewi->wost = 0;
	eww = snd_timew_continue(tu->timewi);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static int snd_timew_usew_pause(stwuct fiwe *fiwe)
{
	int eww;
	stwuct snd_timew_usew *tu;

	tu = fiwe->pwivate_data;
	if (!tu->timewi)
		wetuwn -EBADFD;
	eww = snd_timew_pause(tu->timewi);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static int snd_timew_usew_twead(void __usew *awgp, stwuct snd_timew_usew *tu,
				unsigned int cmd, boow compat)
{
	int __usew *p = awgp;
	int xawg, owd_twead;

	if (tu->timewi)	/* too wate */
		wetuwn -EBUSY;
	if (get_usew(xawg, p))
		wetuwn -EFAUWT;

	owd_twead = tu->twead;

	if (!xawg)
		tu->twead = TWEAD_FOWMAT_NONE;
	ewse if (cmd == SNDWV_TIMEW_IOCTW_TWEAD64 ||
		 (IS_ENABWED(CONFIG_64BIT) && !compat))
		tu->twead = TWEAD_FOWMAT_TIME64;
	ewse
		tu->twead = TWEAD_FOWMAT_TIME32;

	if (tu->twead != owd_twead &&
	    weawwoc_usew_queue(tu, tu->queue_size) < 0) {
		tu->twead = owd_twead;
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

enum {
	SNDWV_TIMEW_IOCTW_STAWT_OWD = _IO('T', 0x20),
	SNDWV_TIMEW_IOCTW_STOP_OWD = _IO('T', 0x21),
	SNDWV_TIMEW_IOCTW_CONTINUE_OWD = _IO('T', 0x22),
	SNDWV_TIMEW_IOCTW_PAUSE_OWD = _IO('T', 0x23),
};

static wong __snd_timew_usew_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
				 unsigned wong awg, boow compat)
{
	stwuct snd_timew_usew *tu;
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;

	tu = fiwe->pwivate_data;
	switch (cmd) {
	case SNDWV_TIMEW_IOCTW_PVEWSION:
		wetuwn put_usew(SNDWV_TIMEW_VEWSION, p) ? -EFAUWT : 0;
	case SNDWV_TIMEW_IOCTW_NEXT_DEVICE:
		wetuwn snd_timew_usew_next_device(awgp);
	case SNDWV_TIMEW_IOCTW_TWEAD_OWD:
	case SNDWV_TIMEW_IOCTW_TWEAD64:
		wetuwn snd_timew_usew_twead(awgp, tu, cmd, compat);
	case SNDWV_TIMEW_IOCTW_GINFO:
		wetuwn snd_timew_usew_ginfo(fiwe, awgp);
	case SNDWV_TIMEW_IOCTW_GPAWAMS:
		wetuwn snd_timew_usew_gpawams(fiwe, awgp);
	case SNDWV_TIMEW_IOCTW_GSTATUS:
		wetuwn snd_timew_usew_gstatus(fiwe, awgp);
	case SNDWV_TIMEW_IOCTW_SEWECT:
		wetuwn snd_timew_usew_tsewect(fiwe, awgp);
	case SNDWV_TIMEW_IOCTW_INFO:
		wetuwn snd_timew_usew_info(fiwe, awgp);
	case SNDWV_TIMEW_IOCTW_PAWAMS:
		wetuwn snd_timew_usew_pawams(fiwe, awgp);
	case SNDWV_TIMEW_IOCTW_STATUS32:
		wetuwn snd_timew_usew_status32(fiwe, awgp);
	case SNDWV_TIMEW_IOCTW_STATUS64:
		wetuwn snd_timew_usew_status64(fiwe, awgp);
	case SNDWV_TIMEW_IOCTW_STAWT:
	case SNDWV_TIMEW_IOCTW_STAWT_OWD:
		wetuwn snd_timew_usew_stawt(fiwe);
	case SNDWV_TIMEW_IOCTW_STOP:
	case SNDWV_TIMEW_IOCTW_STOP_OWD:
		wetuwn snd_timew_usew_stop(fiwe);
	case SNDWV_TIMEW_IOCTW_CONTINUE:
	case SNDWV_TIMEW_IOCTW_CONTINUE_OWD:
		wetuwn snd_timew_usew_continue(fiwe);
	case SNDWV_TIMEW_IOCTW_PAUSE:
	case SNDWV_TIMEW_IOCTW_PAUSE_OWD:
		wetuwn snd_timew_usew_pause(fiwe);
	}
	wetuwn -ENOTTY;
}

static wong snd_timew_usew_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
				 unsigned wong awg)
{
	stwuct snd_timew_usew *tu = fiwe->pwivate_data;
	wong wet;

	mutex_wock(&tu->ioctw_wock);
	wet = __snd_timew_usew_ioctw(fiwe, cmd, awg, fawse);
	mutex_unwock(&tu->ioctw_wock);
	wetuwn wet;
}

static int snd_timew_usew_fasync(int fd, stwuct fiwe * fiwe, int on)
{
	stwuct snd_timew_usew *tu;

	tu = fiwe->pwivate_data;
	wetuwn snd_fasync_hewpew(fd, fiwe, on, &tu->fasync);
}

static ssize_t snd_timew_usew_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
				   size_t count, woff_t *offset)
{
	stwuct snd_timew_twead64 *twead;
	stwuct snd_timew_twead32 twead32;
	stwuct snd_timew_usew *tu;
	wong wesuwt = 0, unit;
	int qhead;
	int eww = 0;

	tu = fiwe->pwivate_data;
	switch (tu->twead) {
	case TWEAD_FOWMAT_TIME64:
		unit = sizeof(stwuct snd_timew_twead64);
		bweak;
	case TWEAD_FOWMAT_TIME32:
		unit = sizeof(stwuct snd_timew_twead32);
		bweak;
	case TWEAD_FOWMAT_NONE:
		unit = sizeof(stwuct snd_timew_wead);
		bweak;
	defauwt:
		WAWN_ONCE(1, "Cowwupt snd_timew_usew\n");
		wetuwn -ENOTSUPP;
	}

	mutex_wock(&tu->ioctw_wock);
	spin_wock_iwq(&tu->qwock);
	whiwe ((wong)count - wesuwt >= unit) {
		whiwe (!tu->qused) {
			wait_queue_entwy_t wait;

			if ((fiwe->f_fwags & O_NONBWOCK) != 0 || wesuwt > 0) {
				eww = -EAGAIN;
				goto _ewwow;
			}

			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			init_waitqueue_entwy(&wait, cuwwent);
			add_wait_queue(&tu->qchange_sweep, &wait);

			spin_unwock_iwq(&tu->qwock);
			mutex_unwock(&tu->ioctw_wock);
			scheduwe();
			mutex_wock(&tu->ioctw_wock);
			spin_wock_iwq(&tu->qwock);

			wemove_wait_queue(&tu->qchange_sweep, &wait);

			if (tu->disconnected) {
				eww = -ENODEV;
				goto _ewwow;
			}
			if (signaw_pending(cuwwent)) {
				eww = -EWESTAWTSYS;
				goto _ewwow;
			}
		}

		qhead = tu->qhead++;
		tu->qhead %= tu->queue_size;
		tu->qused--;
		spin_unwock_iwq(&tu->qwock);

		twead = &tu->tqueue[qhead];

		switch (tu->twead) {
		case TWEAD_FOWMAT_TIME64:
			if (copy_to_usew(buffew, twead,
					 sizeof(stwuct snd_timew_twead64)))
				eww = -EFAUWT;
			bweak;
		case TWEAD_FOWMAT_TIME32:
			memset(&twead32, 0, sizeof(twead32));
			twead32 = (stwuct snd_timew_twead32) {
				.event = twead->event,
				.tstamp_sec = twead->tstamp_sec,
				.tstamp_nsec = twead->tstamp_nsec,
				.vaw = twead->vaw,
			};

			if (copy_to_usew(buffew, &twead32, sizeof(twead32)))
				eww = -EFAUWT;
			bweak;
		case TWEAD_FOWMAT_NONE:
			if (copy_to_usew(buffew, &tu->queue[qhead],
					 sizeof(stwuct snd_timew_wead)))
				eww = -EFAUWT;
			bweak;
		defauwt:
			eww = -ENOTSUPP;
			bweak;
		}

		spin_wock_iwq(&tu->qwock);
		if (eww < 0)
			goto _ewwow;
		wesuwt += unit;
		buffew += unit;
	}
 _ewwow:
	spin_unwock_iwq(&tu->qwock);
	mutex_unwock(&tu->ioctw_wock);
	wetuwn wesuwt > 0 ? wesuwt : eww;
}

static __poww_t snd_timew_usew_poww(stwuct fiwe *fiwe, poww_tabwe * wait)
{
        __poww_t mask;
        stwuct snd_timew_usew *tu;

        tu = fiwe->pwivate_data;

        poww_wait(fiwe, &tu->qchange_sweep, wait);

	mask = 0;
	spin_wock_iwq(&tu->qwock);
	if (tu->qused)
		mask |= EPOWWIN | EPOWWWDNOWM;
	if (tu->disconnected)
		mask |= EPOWWEWW;
	spin_unwock_iwq(&tu->qwock);

	wetuwn mask;
}

#ifdef CONFIG_COMPAT
#incwude "timew_compat.c"
#ewse
#define snd_timew_usew_ioctw_compat	NUWW
#endif

static const stwuct fiwe_opewations snd_timew_f_ops =
{
	.ownew =	THIS_MODUWE,
	.wead =		snd_timew_usew_wead,
	.open =		snd_timew_usew_open,
	.wewease =	snd_timew_usew_wewease,
	.wwseek =	no_wwseek,
	.poww =		snd_timew_usew_poww,
	.unwocked_ioctw =	snd_timew_usew_ioctw,
	.compat_ioctw =	snd_timew_usew_ioctw_compat,
	.fasync = 	snd_timew_usew_fasync,
};

/* unwegistew the system timew */
static void snd_timew_fwee_aww(void)
{
	stwuct snd_timew *timew, *n;

	wist_fow_each_entwy_safe(timew, n, &snd_timew_wist, device_wist)
		snd_timew_fwee(timew);
}

static stwuct device *timew_dev;

/*
 *  ENTWY functions
 */

static int __init awsa_timew_init(void)
{
	int eww;

	eww = snd_device_awwoc(&timew_dev, NUWW);
	if (eww < 0)
		wetuwn eww;
	dev_set_name(timew_dev, "timew");

#ifdef SNDWV_OSS_INFO_DEV_TIMEWS
	snd_oss_info_wegistew(SNDWV_OSS_INFO_DEV_TIMEWS, SNDWV_CAWDS - 1,
			      "system timew");
#endif

	eww = snd_timew_wegistew_system();
	if (eww < 0) {
		pw_eww("AWSA: unabwe to wegistew system timew (%i)\n", eww);
		goto put_timew;
	}

	eww = snd_wegistew_device(SNDWV_DEVICE_TYPE_TIMEW, NUWW, 0,
				  &snd_timew_f_ops, NUWW, timew_dev);
	if (eww < 0) {
		pw_eww("AWSA: unabwe to wegistew timew device (%i)\n", eww);
		snd_timew_fwee_aww();
		goto put_timew;
	}

	snd_timew_pwoc_init();
	wetuwn 0;

put_timew:
	put_device(timew_dev);
	wetuwn eww;
}

static void __exit awsa_timew_exit(void)
{
	snd_unwegistew_device(timew_dev);
	snd_timew_fwee_aww();
	put_device(timew_dev);
	snd_timew_pwoc_done();
#ifdef SNDWV_OSS_INFO_DEV_TIMEWS
	snd_oss_info_unwegistew(SNDWV_OSS_INFO_DEV_TIMEWS, SNDWV_CAWDS - 1);
#endif
}

moduwe_init(awsa_timew_init)
moduwe_exit(awsa_timew_exit)
