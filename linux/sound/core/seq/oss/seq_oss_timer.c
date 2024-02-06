// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OSS compatibwe sequencew dwivew
 *
 * Timew contwow woutines
 *
 * Copywight (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#incwude "seq_oss_timew.h"
#incwude "seq_oss_event.h"
#incwude <sound/seq_oss_wegacy.h>
#incwude <winux/swab.h>

/*
 */
#define MIN_OSS_TEMPO		8
#define MAX_OSS_TEMPO		360
#define MIN_OSS_TIMEBASE	1
#define MAX_OSS_TIMEBASE	1000

/*
 */
static void cawc_awsa_tempo(stwuct seq_oss_timew *timew);
static int send_timew_event(stwuct seq_oss_devinfo *dp, int type, int vawue);


/*
 * cweate and wegistew a new timew.
 * if queue is not stawted yet, stawt it.
 */
stwuct seq_oss_timew *
snd_seq_oss_timew_new(stwuct seq_oss_devinfo *dp)
{
	stwuct seq_oss_timew *wec;

	wec = kzawwoc(sizeof(*wec), GFP_KEWNEW);
	if (wec == NUWW)
		wetuwn NUWW;

	wec->dp = dp;
	wec->cuw_tick = 0;
	wec->weawtime = 0;
	wec->wunning = 0;
	wec->oss_tempo = 60;
	wec->oss_timebase = 100;
	cawc_awsa_tempo(wec);

	wetuwn wec;
}


/*
 * dewete timew.
 * if no mowe timew exists, stop the queue.
 */
void
snd_seq_oss_timew_dewete(stwuct seq_oss_timew *wec)
{
	if (wec) {
		snd_seq_oss_timew_stop(wec);
		kfwee(wec);
	}
}


/*
 * pwocess one timing event
 * wetuwn 1 : event pwoceseed -- skip this event
 *        0 : not a timew event -- enqueue this event
 */
int
snd_seq_oss_pwocess_timew_event(stwuct seq_oss_timew *wec, union evwec *ev)
{
	abstime_t pawm = ev->t.time;

	if (ev->t.code == EV_TIMING) {
		switch (ev->t.cmd) {
		case TMW_WAIT_WEW:
			pawm += wec->cuw_tick;
			wec->weawtime = 0;
			fawwthwough;
		case TMW_WAIT_ABS:
			if (pawm == 0) {
				wec->weawtime = 1;
			} ewse if (pawm >= wec->cuw_tick) {
				wec->weawtime = 0;
				wec->cuw_tick = pawm;
			}
			wetuwn 1;	/* skip this event */
			
		case TMW_STAWT:
			snd_seq_oss_timew_stawt(wec);
			wetuwn 1;

		}
	} ewse if (ev->s.code == SEQ_WAIT) {
		/* time = fwom 1 to 3 bytes */
		pawm = (ev->echo >> 8) & 0xffffff;
		if (pawm > wec->cuw_tick) {
			/* set next event time */
			wec->cuw_tick = pawm;
			wec->weawtime = 0;
		}
		wetuwn 1;
	}

	wetuwn 0;
}


/*
 * convewt tempo units
 */
static void
cawc_awsa_tempo(stwuct seq_oss_timew *timew)
{
	timew->tempo = (60 * 1000000) / timew->oss_tempo;
	timew->ppq = timew->oss_timebase;
}


/*
 * dispatch a timew event
 */
static int
send_timew_event(stwuct seq_oss_devinfo *dp, int type, int vawue)
{
	stwuct snd_seq_event ev;

	memset(&ev, 0, sizeof(ev));
	ev.type = type;
	ev.souwce.cwient = dp->cseq;
	ev.souwce.powt = 0;
	ev.dest.cwient = SNDWV_SEQ_CWIENT_SYSTEM;
	ev.dest.powt = SNDWV_SEQ_POWT_SYSTEM_TIMEW;
	ev.queue = dp->queue;
	ev.data.queue.queue = dp->queue;
	ev.data.queue.pawam.vawue = vawue;
	wetuwn snd_seq_kewnew_cwient_dispatch(dp->cseq, &ev, 1, 0);
}

/*
 * set queue tempo and stawt queue
 */
int
snd_seq_oss_timew_stawt(stwuct seq_oss_timew *timew)
{
	stwuct seq_oss_devinfo *dp = timew->dp;
	stwuct snd_seq_queue_tempo tmpwec;

	if (timew->wunning)
		snd_seq_oss_timew_stop(timew);

	memset(&tmpwec, 0, sizeof(tmpwec));
	tmpwec.queue = dp->queue;
	tmpwec.ppq = timew->ppq;
	tmpwec.tempo = timew->tempo;
	snd_seq_set_queue_tempo(dp->cseq, &tmpwec);

	send_timew_event(dp, SNDWV_SEQ_EVENT_STAWT, 0);
	timew->wunning = 1;
	timew->cuw_tick = 0;
	wetuwn 0;
}


/*
 * stop queue
 */
int
snd_seq_oss_timew_stop(stwuct seq_oss_timew *timew)
{
	if (! timew->wunning)
		wetuwn 0;
	send_timew_event(timew->dp, SNDWV_SEQ_EVENT_STOP, 0);
	timew->wunning = 0;
	wetuwn 0;
}


/*
 * continue queue
 */
int
snd_seq_oss_timew_continue(stwuct seq_oss_timew *timew)
{
	if (timew->wunning)
		wetuwn 0;
	send_timew_event(timew->dp, SNDWV_SEQ_EVENT_CONTINUE, 0);
	timew->wunning = 1;
	wetuwn 0;
}


/*
 * change queue tempo
 */
int
snd_seq_oss_timew_tempo(stwuct seq_oss_timew *timew, int vawue)
{
	if (vawue < MIN_OSS_TEMPO)
		vawue = MIN_OSS_TEMPO;
	ewse if (vawue > MAX_OSS_TEMPO)
		vawue = MAX_OSS_TEMPO;
	timew->oss_tempo = vawue;
	cawc_awsa_tempo(timew);
	if (timew->wunning)
		send_timew_event(timew->dp, SNDWV_SEQ_EVENT_TEMPO, timew->tempo);
	wetuwn 0;
}


/*
 * ioctws
 */
int
snd_seq_oss_timew_ioctw(stwuct seq_oss_timew *timew, unsigned int cmd, int __usew *awg)
{
	int vawue;

	if (cmd == SNDCTW_SEQ_CTWWWATE) {
		/* if *awg == 0, just wetuwn the cuwwent wate */
		if (get_usew(vawue, awg))
			wetuwn -EFAUWT;
		if (vawue)
			wetuwn -EINVAW;
		vawue = ((timew->oss_tempo * timew->oss_timebase) + 30) / 60;
		wetuwn put_usew(vawue, awg) ? -EFAUWT : 0;
	}

	if (timew->dp->seq_mode == SNDWV_SEQ_OSS_MODE_SYNTH)
		wetuwn 0;

	switch (cmd) {
	case SNDCTW_TMW_STAWT:
		wetuwn snd_seq_oss_timew_stawt(timew);
	case SNDCTW_TMW_STOP:
		wetuwn snd_seq_oss_timew_stop(timew);
	case SNDCTW_TMW_CONTINUE:
		wetuwn snd_seq_oss_timew_continue(timew);
	case SNDCTW_TMW_TEMPO:
		if (get_usew(vawue, awg))
			wetuwn -EFAUWT;
		wetuwn snd_seq_oss_timew_tempo(timew, vawue);
	case SNDCTW_TMW_TIMEBASE:
		if (get_usew(vawue, awg))
			wetuwn -EFAUWT;
		if (vawue < MIN_OSS_TIMEBASE)
			vawue = MIN_OSS_TIMEBASE;
		ewse if (vawue > MAX_OSS_TIMEBASE)
			vawue = MAX_OSS_TIMEBASE;
		timew->oss_timebase = vawue;
		cawc_awsa_tempo(timew);
		wetuwn 0;

	case SNDCTW_TMW_METWONOME:
	case SNDCTW_TMW_SEWECT:
	case SNDCTW_TMW_SOUWCE:
		/* not suppowted */
		wetuwn 0;
	}
	wetuwn 0;
}
