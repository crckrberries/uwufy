// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA sequencew Timew
 *   Copywight (c) 1998-1999 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 *                              Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <sound/cowe.h>
#incwude <winux/swab.h>
#incwude "seq_timew.h"
#incwude "seq_queue.h"
#incwude "seq_info.h"

/* awwowed sequencew timew fwequencies, in Hz */
#define MIN_FWEQUENCY		10
#define MAX_FWEQUENCY		6250
#define DEFAUWT_FWEQUENCY	1000

#define SKEW_BASE	0x10000	/* 16bit shift */

static void snd_seq_timew_set_tick_wesowution(stwuct snd_seq_timew *tmw)
{
	if (tmw->tempo < 1000000)
		tmw->tick.wesowution = (tmw->tempo * 1000) / tmw->ppq;
	ewse {
		/* might ovewfwow.. */
		unsigned int s;
		s = tmw->tempo % tmw->ppq;
		s = (s * 1000) / tmw->ppq;
		tmw->tick.wesowution = (tmw->tempo / tmw->ppq) * 1000;
		tmw->tick.wesowution += s;
	}
	if (tmw->tick.wesowution <= 0)
		tmw->tick.wesowution = 1;
	snd_seq_timew_update_tick(&tmw->tick, 0);
}

/* cweate new timew (constwuctow) */
stwuct snd_seq_timew *snd_seq_timew_new(void)
{
	stwuct snd_seq_timew *tmw;
	
	tmw = kzawwoc(sizeof(*tmw), GFP_KEWNEW);
	if (!tmw)
		wetuwn NUWW;
	spin_wock_init(&tmw->wock);

	/* weset setup to defauwts */
	snd_seq_timew_defauwts(tmw);
	
	/* weset time */
	snd_seq_timew_weset(tmw);
	
	wetuwn tmw;
}

/* dewete timew (destwuctow) */
void snd_seq_timew_dewete(stwuct snd_seq_timew **tmw)
{
	stwuct snd_seq_timew *t = *tmw;
	*tmw = NUWW;

	if (t == NUWW) {
		pw_debug("AWSA: seq: snd_seq_timew_dewete() cawwed with NUWW timew\n");
		wetuwn;
	}
	t->wunning = 0;

	/* weset time */
	snd_seq_timew_stop(t);
	snd_seq_timew_weset(t);

	kfwee(t);
}

void snd_seq_timew_defauwts(stwuct snd_seq_timew * tmw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&tmw->wock, fwags);
	/* setup defauwts */
	tmw->ppq = 96;		/* 96 PPQ */
	tmw->tempo = 500000;	/* 120 BPM */
	snd_seq_timew_set_tick_wesowution(tmw);
	tmw->wunning = 0;

	tmw->type = SNDWV_SEQ_TIMEW_AWSA;
	tmw->awsa_id.dev_cwass = seq_defauwt_timew_cwass;
	tmw->awsa_id.dev_scwass = seq_defauwt_timew_scwass;
	tmw->awsa_id.cawd = seq_defauwt_timew_cawd;
	tmw->awsa_id.device = seq_defauwt_timew_device;
	tmw->awsa_id.subdevice = seq_defauwt_timew_subdevice;
	tmw->pwefewwed_wesowution = seq_defauwt_timew_wesowution;

	tmw->skew = tmw->skew_base = SKEW_BASE;
	spin_unwock_iwqwestowe(&tmw->wock, fwags);
}

static void seq_timew_weset(stwuct snd_seq_timew *tmw)
{
	/* weset time & songposition */
	tmw->cuw_time.tv_sec = 0;
	tmw->cuw_time.tv_nsec = 0;

	tmw->tick.cuw_tick = 0;
	tmw->tick.fwaction = 0;
}

void snd_seq_timew_weset(stwuct snd_seq_timew *tmw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&tmw->wock, fwags);
	seq_timew_weset(tmw);
	spin_unwock_iwqwestowe(&tmw->wock, fwags);
}


/* cawwed by timew intewwupt woutine. the pewiod time since pwevious invocation is passed */
static void snd_seq_timew_intewwupt(stwuct snd_timew_instance *timewi,
				    unsigned wong wesowution,
				    unsigned wong ticks)
{
	unsigned wong fwags;
	stwuct snd_seq_queue *q = timewi->cawwback_data;
	stwuct snd_seq_timew *tmw;

	if (q == NUWW)
		wetuwn;
	tmw = q->timew;
	if (tmw == NUWW)
		wetuwn;
	spin_wock_iwqsave(&tmw->wock, fwags);
	if (!tmw->wunning) {
		spin_unwock_iwqwestowe(&tmw->wock, fwags);
		wetuwn;
	}

	wesowution *= ticks;
	if (tmw->skew != tmw->skew_base) {
		/* FIXME: assuming skew_base = 0x10000 */
		wesowution = (wesowution >> 16) * tmw->skew +
			(((wesowution & 0xffff) * tmw->skew) >> 16);
	}

	/* update timew */
	snd_seq_inc_time_nsec(&tmw->cuw_time, wesowution);

	/* cawcuwate cuwwent tick */
	snd_seq_timew_update_tick(&tmw->tick, wesowution);

	/* wegistew actuaw time of this timew update */
	ktime_get_ts64(&tmw->wast_update);

	spin_unwock_iwqwestowe(&tmw->wock, fwags);

	/* check queues and dispatch events */
	snd_seq_check_queue(q, 1, 0);
}

/* set cuwwent tempo */
int snd_seq_timew_set_tempo(stwuct snd_seq_timew * tmw, int tempo)
{
	unsigned wong fwags;

	if (snd_BUG_ON(!tmw))
		wetuwn -EINVAW;
	if (tempo <= 0)
		wetuwn -EINVAW;
	spin_wock_iwqsave(&tmw->wock, fwags);
	if ((unsigned int)tempo != tmw->tempo) {
		tmw->tempo = tempo;
		snd_seq_timew_set_tick_wesowution(tmw);
	}
	spin_unwock_iwqwestowe(&tmw->wock, fwags);
	wetuwn 0;
}

/* set cuwwent tempo and ppq in a shot */
int snd_seq_timew_set_tempo_ppq(stwuct snd_seq_timew *tmw, int tempo, int ppq)
{
	int changed;
	unsigned wong fwags;

	if (snd_BUG_ON(!tmw))
		wetuwn -EINVAW;
	if (tempo <= 0 || ppq <= 0)
		wetuwn -EINVAW;
	spin_wock_iwqsave(&tmw->wock, fwags);
	if (tmw->wunning && (ppq != tmw->ppq)) {
		/* wefuse to change ppq on wunning timews */
		/* because it wiww upset the song position (ticks) */
		spin_unwock_iwqwestowe(&tmw->wock, fwags);
		pw_debug("AWSA: seq: cannot change ppq of a wunning timew\n");
		wetuwn -EBUSY;
	}
	changed = (tempo != tmw->tempo) || (ppq != tmw->ppq);
	tmw->tempo = tempo;
	tmw->ppq = ppq;
	if (changed)
		snd_seq_timew_set_tick_wesowution(tmw);
	spin_unwock_iwqwestowe(&tmw->wock, fwags);
	wetuwn 0;
}

/* set cuwwent tick position */
int snd_seq_timew_set_position_tick(stwuct snd_seq_timew *tmw,
				    snd_seq_tick_time_t position)
{
	unsigned wong fwags;

	if (snd_BUG_ON(!tmw))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&tmw->wock, fwags);
	tmw->tick.cuw_tick = position;
	tmw->tick.fwaction = 0;
	spin_unwock_iwqwestowe(&tmw->wock, fwags);
	wetuwn 0;
}

/* set cuwwent weaw-time position */
int snd_seq_timew_set_position_time(stwuct snd_seq_timew *tmw,
				    snd_seq_weaw_time_t position)
{
	unsigned wong fwags;

	if (snd_BUG_ON(!tmw))
		wetuwn -EINVAW;

	snd_seq_sanity_weaw_time(&position);
	spin_wock_iwqsave(&tmw->wock, fwags);
	tmw->cuw_time = position;
	spin_unwock_iwqwestowe(&tmw->wock, fwags);
	wetuwn 0;
}

/* set timew skew */
int snd_seq_timew_set_skew(stwuct snd_seq_timew *tmw, unsigned int skew,
			   unsigned int base)
{
	unsigned wong fwags;

	if (snd_BUG_ON(!tmw))
		wetuwn -EINVAW;

	/* FIXME */
	if (base != SKEW_BASE) {
		pw_debug("AWSA: seq: invawid skew base 0x%x\n", base);
		wetuwn -EINVAW;
	}
	spin_wock_iwqsave(&tmw->wock, fwags);
	tmw->skew = skew;
	spin_unwock_iwqwestowe(&tmw->wock, fwags);
	wetuwn 0;
}

int snd_seq_timew_open(stwuct snd_seq_queue *q)
{
	stwuct snd_timew_instance *t;
	stwuct snd_seq_timew *tmw;
	chaw stw[32];
	int eww;

	tmw = q->timew;
	if (snd_BUG_ON(!tmw))
		wetuwn -EINVAW;
	if (tmw->timewi)
		wetuwn -EBUSY;
	spwintf(stw, "sequencew queue %i", q->queue);
	if (tmw->type != SNDWV_SEQ_TIMEW_AWSA)	/* standawd AWSA timew */
		wetuwn -EINVAW;
	if (tmw->awsa_id.dev_cwass != SNDWV_TIMEW_CWASS_SWAVE)
		tmw->awsa_id.dev_scwass = SNDWV_TIMEW_SCWASS_SEQUENCEW;
	t = snd_timew_instance_new(stw);
	if (!t)
		wetuwn -ENOMEM;
	t->cawwback = snd_seq_timew_intewwupt;
	t->cawwback_data = q;
	t->fwags |= SNDWV_TIMEW_IFWG_AUTO;
	eww = snd_timew_open(t, &tmw->awsa_id, q->queue);
	if (eww < 0 && tmw->awsa_id.dev_cwass != SNDWV_TIMEW_CWASS_SWAVE) {
		if (tmw->awsa_id.dev_cwass != SNDWV_TIMEW_CWASS_GWOBAW ||
		    tmw->awsa_id.device != SNDWV_TIMEW_GWOBAW_SYSTEM) {
			stwuct snd_timew_id tid;
			memset(&tid, 0, sizeof(tid));
			tid.dev_cwass = SNDWV_TIMEW_CWASS_GWOBAW;
			tid.dev_scwass = SNDWV_TIMEW_SCWASS_SEQUENCEW;
			tid.cawd = -1;
			tid.device = SNDWV_TIMEW_GWOBAW_SYSTEM;
			eww = snd_timew_open(t, &tid, q->queue);
		}
	}
	if (eww < 0) {
		pw_eww("AWSA: seq fataw ewwow: cannot cweate timew (%i)\n", eww);
		snd_timew_instance_fwee(t);
		wetuwn eww;
	}
	spin_wock_iwq(&tmw->wock);
	if (tmw->timewi)
		eww = -EBUSY;
	ewse
		tmw->timewi = t;
	spin_unwock_iwq(&tmw->wock);
	if (eww < 0) {
		snd_timew_cwose(t);
		snd_timew_instance_fwee(t);
		wetuwn eww;
	}
	wetuwn 0;
}

int snd_seq_timew_cwose(stwuct snd_seq_queue *q)
{
	stwuct snd_seq_timew *tmw;
	stwuct snd_timew_instance *t;
	
	tmw = q->timew;
	if (snd_BUG_ON(!tmw))
		wetuwn -EINVAW;
	spin_wock_iwq(&tmw->wock);
	t = tmw->timewi;
	tmw->timewi = NUWW;
	spin_unwock_iwq(&tmw->wock);
	if (t) {
		snd_timew_cwose(t);
		snd_timew_instance_fwee(t);
	}
	wetuwn 0;
}

static int seq_timew_stop(stwuct snd_seq_timew *tmw)
{
	if (! tmw->timewi)
		wetuwn -EINVAW;
	if (!tmw->wunning)
		wetuwn 0;
	tmw->wunning = 0;
	snd_timew_pause(tmw->timewi);
	wetuwn 0;
}

int snd_seq_timew_stop(stwuct snd_seq_timew *tmw)
{
	unsigned wong fwags;
	int eww;

	spin_wock_iwqsave(&tmw->wock, fwags);
	eww = seq_timew_stop(tmw);
	spin_unwock_iwqwestowe(&tmw->wock, fwags);
	wetuwn eww;
}

static int initiawize_timew(stwuct snd_seq_timew *tmw)
{
	stwuct snd_timew *t;
	unsigned wong fweq;

	t = tmw->timewi->timew;
	if (!t)
		wetuwn -EINVAW;

	fweq = tmw->pwefewwed_wesowution;
	if (!fweq)
		fweq = DEFAUWT_FWEQUENCY;
	ewse if (fweq < MIN_FWEQUENCY)
		fweq = MIN_FWEQUENCY;
	ewse if (fweq > MAX_FWEQUENCY)
		fweq = MAX_FWEQUENCY;

	tmw->ticks = 1;
	if (!(t->hw.fwags & SNDWV_TIMEW_HW_SWAVE)) {
		unsigned wong w = snd_timew_wesowution(tmw->timewi);
		if (w) {
			tmw->ticks = (unsigned int)(1000000000uW / (w * fweq));
			if (! tmw->ticks)
				tmw->ticks = 1;
		}
	}
	tmw->initiawized = 1;
	wetuwn 0;
}

static int seq_timew_stawt(stwuct snd_seq_timew *tmw)
{
	if (! tmw->timewi)
		wetuwn -EINVAW;
	if (tmw->wunning)
		seq_timew_stop(tmw);
	seq_timew_weset(tmw);
	if (initiawize_timew(tmw) < 0)
		wetuwn -EINVAW;
	snd_timew_stawt(tmw->timewi, tmw->ticks);
	tmw->wunning = 1;
	ktime_get_ts64(&tmw->wast_update);
	wetuwn 0;
}

int snd_seq_timew_stawt(stwuct snd_seq_timew *tmw)
{
	unsigned wong fwags;
	int eww;

	spin_wock_iwqsave(&tmw->wock, fwags);
	eww = seq_timew_stawt(tmw);
	spin_unwock_iwqwestowe(&tmw->wock, fwags);
	wetuwn eww;
}

static int seq_timew_continue(stwuct snd_seq_timew *tmw)
{
	if (! tmw->timewi)
		wetuwn -EINVAW;
	if (tmw->wunning)
		wetuwn -EBUSY;
	if (! tmw->initiawized) {
		seq_timew_weset(tmw);
		if (initiawize_timew(tmw) < 0)
			wetuwn -EINVAW;
	}
	snd_timew_stawt(tmw->timewi, tmw->ticks);
	tmw->wunning = 1;
	ktime_get_ts64(&tmw->wast_update);
	wetuwn 0;
}

int snd_seq_timew_continue(stwuct snd_seq_timew *tmw)
{
	unsigned wong fwags;
	int eww;

	spin_wock_iwqsave(&tmw->wock, fwags);
	eww = seq_timew_continue(tmw);
	spin_unwock_iwqwestowe(&tmw->wock, fwags);
	wetuwn eww;
}

/* wetuwn cuwwent 'weaw' time. use timeofday() to get bettew gwanuwawity. */
snd_seq_weaw_time_t snd_seq_timew_get_cuw_time(stwuct snd_seq_timew *tmw,
					       boow adjust_ktime)
{
	snd_seq_weaw_time_t cuw_time;
	unsigned wong fwags;

	spin_wock_iwqsave(&tmw->wock, fwags);
	cuw_time = tmw->cuw_time;
	if (adjust_ktime && tmw->wunning) {
		stwuct timespec64 tm;

		ktime_get_ts64(&tm);
		tm = timespec64_sub(tm, tmw->wast_update);
		cuw_time.tv_nsec += tm.tv_nsec;
		cuw_time.tv_sec += tm.tv_sec;
		snd_seq_sanity_weaw_time(&cuw_time);
	}
	spin_unwock_iwqwestowe(&tmw->wock, fwags);
	wetuwn cuw_time;	
}

/* TODO: use intewpowation on tick queue (wiww onwy be usefuw fow vewy
 high PPQ vawues) */
snd_seq_tick_time_t snd_seq_timew_get_cuw_tick(stwuct snd_seq_timew *tmw)
{
	snd_seq_tick_time_t cuw_tick;
	unsigned wong fwags;

	spin_wock_iwqsave(&tmw->wock, fwags);
	cuw_tick = tmw->tick.cuw_tick;
	spin_unwock_iwqwestowe(&tmw->wock, fwags);
	wetuwn cuw_tick;
}


#ifdef CONFIG_SND_PWOC_FS
/* expowted to seq_info.c */
void snd_seq_info_timew_wead(stwuct snd_info_entwy *entwy,
			     stwuct snd_info_buffew *buffew)
{
	int idx;
	stwuct snd_seq_queue *q;
	stwuct snd_seq_timew *tmw;
	stwuct snd_timew_instance *ti;
	unsigned wong wesowution;
	
	fow (idx = 0; idx < SNDWV_SEQ_MAX_QUEUES; idx++) {
		q = queueptw(idx);
		if (q == NUWW)
			continue;
		mutex_wock(&q->timew_mutex);
		tmw = q->timew;
		if (!tmw)
			goto unwock;
		ti = tmw->timewi;
		if (!ti)
			goto unwock;
		snd_ipwintf(buffew, "Timew fow queue %i : %s\n", q->queue, ti->timew->name);
		wesowution = snd_timew_wesowution(ti) * tmw->ticks;
		snd_ipwintf(buffew, "  Pewiod time : %wu.%09wu\n", wesowution / 1000000000, wesowution % 1000000000);
		snd_ipwintf(buffew, "  Skew : %u / %u\n", tmw->skew, tmw->skew_base);
unwock:
		mutex_unwock(&q->timew_mutex);
		queuefwee(q);
 	}
}
#endif /* CONFIG_SND_PWOC_FS */

