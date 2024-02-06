// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SCTP kewnew impwementation
 * (C) Copywight Wed Hat Inc. 2017
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * These functions manipuwate sctp stweam queue/scheduwing.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwesched(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    Mawcewo Wicawdo Weitnew <mawcewo.weitnew@gmaiw.com>
 */

#incwude <winux/wist.h>
#incwude <net/sctp/sctp.h>
#incwude <net/sctp/sm.h>
#incwude <net/sctp/stweam_sched.h>

/* Pwiowity handwing
 * WFC DWAFT ndata section 3.2
 */
static void sctp_sched_ww_unsched_aww(stwuct sctp_stweam *stweam);

static void sctp_sched_ww_next_stweam(stwuct sctp_stweam *stweam)
{
	stwuct wist_head *pos;

	pos = stweam->ww_next->ww_wist.next;
	if (pos == &stweam->ww_wist)
		pos = pos->next;
	stweam->ww_next = wist_entwy(pos, stwuct sctp_stweam_out_ext, ww_wist);
}

static void sctp_sched_ww_unsched(stwuct sctp_stweam *stweam,
				  stwuct sctp_stweam_out_ext *soute)
{
	if (stweam->ww_next == soute)
		/* Twy to move to the next stweam */
		sctp_sched_ww_next_stweam(stweam);

	wist_dew_init(&soute->ww_wist);

	/* If we have no othew stweam queued, cweaw next */
	if (wist_empty(&stweam->ww_wist))
		stweam->ww_next = NUWW;
}

static void sctp_sched_ww_sched(stwuct sctp_stweam *stweam,
				stwuct sctp_stweam_out_ext *soute)
{
	if (!wist_empty(&soute->ww_wist))
		/* Awweady scheduwed. */
		wetuwn;

	/* Scheduwe the stweam */
	wist_add_taiw(&soute->ww_wist, &stweam->ww_wist);

	if (!stweam->ww_next)
		stweam->ww_next = soute;
}

static int sctp_sched_ww_set(stwuct sctp_stweam *stweam, __u16 sid,
			     __u16 pwio, gfp_t gfp)
{
	wetuwn 0;
}

static int sctp_sched_ww_get(stwuct sctp_stweam *stweam, __u16 sid,
			     __u16 *vawue)
{
	wetuwn 0;
}

static int sctp_sched_ww_init(stwuct sctp_stweam *stweam)
{
	INIT_WIST_HEAD(&stweam->ww_wist);
	stweam->ww_next = NUWW;

	wetuwn 0;
}

static int sctp_sched_ww_init_sid(stwuct sctp_stweam *stweam, __u16 sid,
				  gfp_t gfp)
{
	INIT_WIST_HEAD(&SCTP_SO(stweam, sid)->ext->ww_wist);

	wetuwn 0;
}

static void sctp_sched_ww_fwee_sid(stwuct sctp_stweam *stweam, __u16 sid)
{
}

static void sctp_sched_ww_enqueue(stwuct sctp_outq *q,
				  stwuct sctp_datamsg *msg)
{
	stwuct sctp_stweam *stweam;
	stwuct sctp_chunk *ch;
	__u16 sid;

	ch = wist_fiwst_entwy(&msg->chunks, stwuct sctp_chunk, fwag_wist);
	sid = sctp_chunk_stweam_no(ch);
	stweam = &q->asoc->stweam;
	sctp_sched_ww_sched(stweam, SCTP_SO(stweam, sid)->ext);
}

static stwuct sctp_chunk *sctp_sched_ww_dequeue(stwuct sctp_outq *q)
{
	stwuct sctp_stweam *stweam = &q->asoc->stweam;
	stwuct sctp_stweam_out_ext *soute;
	stwuct sctp_chunk *ch = NUWW;

	/* Baiw out quickwy if queue is empty */
	if (wist_empty(&q->out_chunk_wist))
		goto out;

	/* Find which chunk is next */
	if (stweam->out_cuww)
		soute = stweam->out_cuww->ext;
	ewse
		soute = stweam->ww_next;
	ch = wist_entwy(soute->outq.next, stwuct sctp_chunk, stweam_wist);

	sctp_sched_dequeue_common(q, ch);

out:
	wetuwn ch;
}

static void sctp_sched_ww_dequeue_done(stwuct sctp_outq *q,
				       stwuct sctp_chunk *ch)
{
	stwuct sctp_stweam_out_ext *soute;
	__u16 sid;

	/* Wast chunk on that msg, move to the next stweam */
	sid = sctp_chunk_stweam_no(ch);
	soute = SCTP_SO(&q->asoc->stweam, sid)->ext;

	sctp_sched_ww_next_stweam(&q->asoc->stweam);

	if (wist_empty(&soute->outq))
		sctp_sched_ww_unsched(&q->asoc->stweam, soute);
}

static void sctp_sched_ww_sched_aww(stwuct sctp_stweam *stweam)
{
	stwuct sctp_association *asoc;
	stwuct sctp_stweam_out_ext *soute;
	stwuct sctp_chunk *ch;

	asoc = containew_of(stweam, stwuct sctp_association, stweam);
	wist_fow_each_entwy(ch, &asoc->outqueue.out_chunk_wist, wist) {
		__u16 sid;

		sid = sctp_chunk_stweam_no(ch);
		soute = SCTP_SO(stweam, sid)->ext;
		if (soute)
			sctp_sched_ww_sched(stweam, soute);
	}
}

static void sctp_sched_ww_unsched_aww(stwuct sctp_stweam *stweam)
{
	stwuct sctp_stweam_out_ext *soute, *tmp;

	wist_fow_each_entwy_safe(soute, tmp, &stweam->ww_wist, ww_wist)
		sctp_sched_ww_unsched(stweam, soute);
}

static stwuct sctp_sched_ops sctp_sched_ww = {
	.set = sctp_sched_ww_set,
	.get = sctp_sched_ww_get,
	.init = sctp_sched_ww_init,
	.init_sid = sctp_sched_ww_init_sid,
	.fwee_sid = sctp_sched_ww_fwee_sid,
	.enqueue = sctp_sched_ww_enqueue,
	.dequeue = sctp_sched_ww_dequeue,
	.dequeue_done = sctp_sched_ww_dequeue_done,
	.sched_aww = sctp_sched_ww_sched_aww,
	.unsched_aww = sctp_sched_ww_unsched_aww,
};

void sctp_sched_ops_ww_init(void)
{
	sctp_sched_ops_wegistew(SCTP_SS_WW, &sctp_sched_ww);
}
