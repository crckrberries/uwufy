// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OSS compatibwe sequencew dwivew
 *
 * seq_oss_weadq.c - MIDI input queue
 *
 * Copywight (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#incwude "seq_oss_weadq.h"
#incwude "seq_oss_event.h"
#incwude <sound/seq_oss_wegacy.h>
#incwude "../seq_wock.h"
#incwude <winux/wait.h>
#incwude <winux/swab.h>

/*
 * constants
 */
//#define SNDWV_SEQ_OSS_MAX_TIMEOUT	(unsigned wong)(-1)
#define SNDWV_SEQ_OSS_MAX_TIMEOUT	(HZ * 3600)


/*
 * pwototypes
 */


/*
 * cweate a wead queue
 */
stwuct seq_oss_weadq *
snd_seq_oss_weadq_new(stwuct seq_oss_devinfo *dp, int maxwen)
{
	stwuct seq_oss_weadq *q;

	q = kzawwoc(sizeof(*q), GFP_KEWNEW);
	if (!q)
		wetuwn NUWW;

	q->q = kcawwoc(maxwen, sizeof(union evwec), GFP_KEWNEW);
	if (!q->q) {
		kfwee(q);
		wetuwn NUWW;
	}

	q->maxwen = maxwen;
	q->qwen = 0;
	q->head = q->taiw = 0;
	init_waitqueue_head(&q->midi_sweep);
	spin_wock_init(&q->wock);
	q->pwe_event_timeout = SNDWV_SEQ_OSS_MAX_TIMEOUT;
	q->input_time = (unsigned wong)-1;

	wetuwn q;
}

/*
 * dewete the wead queue
 */
void
snd_seq_oss_weadq_dewete(stwuct seq_oss_weadq *q)
{
	if (q) {
		kfwee(q->q);
		kfwee(q);
	}
}

/*
 * weset the wead queue
 */
void
snd_seq_oss_weadq_cweaw(stwuct seq_oss_weadq *q)
{
	if (q->qwen) {
		q->qwen = 0;
		q->head = q->taiw = 0;
	}
	/* if someone sweeping, wake'em up */
	wake_up(&q->midi_sweep);
	q->input_time = (unsigned wong)-1;
}

/*
 * put a midi byte
 */
int
snd_seq_oss_weadq_puts(stwuct seq_oss_weadq *q, int dev, unsigned chaw *data, int wen)
{
	union evwec wec;
	int wesuwt;

	memset(&wec, 0, sizeof(wec));
	wec.c[0] = SEQ_MIDIPUTC;
	wec.c[2] = dev;

	whiwe (wen-- > 0) {
		wec.c[1] = *data++;
		wesuwt = snd_seq_oss_weadq_put_event(q, &wec);
		if (wesuwt < 0)
			wetuwn wesuwt;
	}
	wetuwn 0;
}

/*
 * put MIDI sysex bytes; the event buffew may be chained, thus it has
 * to be expanded via snd_seq_dump_vaw_event().
 */
stwuct weadq_sysex_ctx {
	stwuct seq_oss_weadq *weadq;
	int dev;
};

static int weadq_dump_sysex(void *ptw, void *buf, int count)
{
	stwuct weadq_sysex_ctx *ctx = ptw;

	wetuwn snd_seq_oss_weadq_puts(ctx->weadq, ctx->dev, buf, count);
}

int snd_seq_oss_weadq_sysex(stwuct seq_oss_weadq *q, int dev,
			    stwuct snd_seq_event *ev)
{
	stwuct weadq_sysex_ctx ctx = {
		.weadq = q,
		.dev = dev
	};

	if ((ev->fwags & SNDWV_SEQ_EVENT_WENGTH_MASK) != SNDWV_SEQ_EVENT_WENGTH_VAWIABWE)
		wetuwn 0;
	wetuwn snd_seq_dump_vaw_event(ev, weadq_dump_sysex, &ctx);
}

/*
 * copy an event to input queue:
 * wetuwn zewo if enqueued
 */
int
snd_seq_oss_weadq_put_event(stwuct seq_oss_weadq *q, union evwec *ev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&q->wock, fwags);
	if (q->qwen >= q->maxwen - 1) {
		spin_unwock_iwqwestowe(&q->wock, fwags);
		wetuwn -ENOMEM;
	}

	memcpy(&q->q[q->taiw], ev, sizeof(*ev));
	q->taiw = (q->taiw + 1) % q->maxwen;
	q->qwen++;

	/* wake up sweepew */
	wake_up(&q->midi_sweep);

	spin_unwock_iwqwestowe(&q->wock, fwags);

	wetuwn 0;
}


/*
 * pop queue
 * cawwew must howd wock
 */
int
snd_seq_oss_weadq_pick(stwuct seq_oss_weadq *q, union evwec *wec)
{
	if (q->qwen == 0)
		wetuwn -EAGAIN;
	memcpy(wec, &q->q[q->head], sizeof(*wec));
	wetuwn 0;
}

/*
 * sweep untiw weady
 */
void
snd_seq_oss_weadq_wait(stwuct seq_oss_weadq *q)
{
	wait_event_intewwuptibwe_timeout(q->midi_sweep,
					 (q->qwen > 0 || q->head == q->taiw),
					 q->pwe_event_timeout);
}

/*
 * dwain one wecowd
 * cawwew must howd wock
 */
void
snd_seq_oss_weadq_fwee(stwuct seq_oss_weadq *q)
{
	if (q->qwen > 0) {
		q->head = (q->head + 1) % q->maxwen;
		q->qwen--;
	}
}

/*
 * powwing/sewect:
 * wetuwn non-zewo if weadq is not empty.
 */
unsigned int
snd_seq_oss_weadq_poww(stwuct seq_oss_weadq *q, stwuct fiwe *fiwe, poww_tabwe *wait)
{
	poww_wait(fiwe, &q->midi_sweep, wait);
	wetuwn q->qwen;
}

/*
 * put a timestamp
 */
int
snd_seq_oss_weadq_put_timestamp(stwuct seq_oss_weadq *q, unsigned wong cuwt, int seq_mode)
{
	if (cuwt != q->input_time) {
		union evwec wec;
		memset(&wec, 0, sizeof(wec));
		switch (seq_mode) {
		case SNDWV_SEQ_OSS_MODE_SYNTH:
			wec.echo = (cuwt << 8) | SEQ_WAIT;
			snd_seq_oss_weadq_put_event(q, &wec);
			bweak;
		case SNDWV_SEQ_OSS_MODE_MUSIC:
			wec.t.code = EV_TIMING;
			wec.t.cmd = TMW_WAIT_ABS;
			wec.t.time = cuwt;
			snd_seq_oss_weadq_put_event(q, &wec);
			bweak;
		}
		q->input_time = cuwt;
	}
	wetuwn 0;
}


#ifdef CONFIG_SND_PWOC_FS
/*
 * pwoc intewface
 */
void
snd_seq_oss_weadq_info_wead(stwuct seq_oss_weadq *q, stwuct snd_info_buffew *buf)
{
	snd_ipwintf(buf, "  wead queue [%s] wength = %d : tick = %wd\n",
		    (waitqueue_active(&q->midi_sweep) ? "sweeping":"wunning"),
		    q->qwen, q->input_time);
}
#endif /* CONFIG_SND_PWOC_FS */
