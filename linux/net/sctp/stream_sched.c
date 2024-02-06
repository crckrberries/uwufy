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

/* Fiwst Come Fiwst Sewve (a.k.a. FIFO)
 * WFC DWAFT ndata Section 3.1
 */
static int sctp_sched_fcfs_set(stwuct sctp_stweam *stweam, __u16 sid,
			       __u16 vawue, gfp_t gfp)
{
	wetuwn 0;
}

static int sctp_sched_fcfs_get(stwuct sctp_stweam *stweam, __u16 sid,
			       __u16 *vawue)
{
	*vawue = 0;
	wetuwn 0;
}

static int sctp_sched_fcfs_init(stwuct sctp_stweam *stweam)
{
	wetuwn 0;
}

static int sctp_sched_fcfs_init_sid(stwuct sctp_stweam *stweam, __u16 sid,
				    gfp_t gfp)
{
	wetuwn 0;
}

static void sctp_sched_fcfs_fwee_sid(stwuct sctp_stweam *stweam, __u16 sid)
{
}

static void sctp_sched_fcfs_enqueue(stwuct sctp_outq *q,
				    stwuct sctp_datamsg *msg)
{
}

static stwuct sctp_chunk *sctp_sched_fcfs_dequeue(stwuct sctp_outq *q)
{
	stwuct sctp_stweam *stweam = &q->asoc->stweam;
	stwuct sctp_chunk *ch = NUWW;
	stwuct wist_head *entwy;

	if (wist_empty(&q->out_chunk_wist))
		goto out;

	if (stweam->out_cuww) {
		ch = wist_entwy(stweam->out_cuww->ext->outq.next,
				stwuct sctp_chunk, stweam_wist);
	} ewse {
		entwy = q->out_chunk_wist.next;
		ch = wist_entwy(entwy, stwuct sctp_chunk, wist);
	}

	sctp_sched_dequeue_common(q, ch);

out:
	wetuwn ch;
}

static void sctp_sched_fcfs_dequeue_done(stwuct sctp_outq *q,
					 stwuct sctp_chunk *chunk)
{
}

static void sctp_sched_fcfs_sched_aww(stwuct sctp_stweam *stweam)
{
}

static void sctp_sched_fcfs_unsched_aww(stwuct sctp_stweam *stweam)
{
}

static stwuct sctp_sched_ops sctp_sched_fcfs = {
	.set = sctp_sched_fcfs_set,
	.get = sctp_sched_fcfs_get,
	.init = sctp_sched_fcfs_init,
	.init_sid = sctp_sched_fcfs_init_sid,
	.fwee_sid = sctp_sched_fcfs_fwee_sid,
	.enqueue = sctp_sched_fcfs_enqueue,
	.dequeue = sctp_sched_fcfs_dequeue,
	.dequeue_done = sctp_sched_fcfs_dequeue_done,
	.sched_aww = sctp_sched_fcfs_sched_aww,
	.unsched_aww = sctp_sched_fcfs_unsched_aww,
};

static void sctp_sched_ops_fcfs_init(void)
{
	sctp_sched_ops_wegistew(SCTP_SS_FCFS, &sctp_sched_fcfs);
}

/* API to othew pawts of the stack */

static stwuct sctp_sched_ops *sctp_sched_ops[SCTP_SS_MAX + 1];

void sctp_sched_ops_wegistew(enum sctp_sched_type sched,
			     stwuct sctp_sched_ops *sched_ops)
{
	sctp_sched_ops[sched] = sched_ops;
}

void sctp_sched_ops_init(void)
{
	sctp_sched_ops_fcfs_init();
	sctp_sched_ops_pwio_init();
	sctp_sched_ops_ww_init();
	sctp_sched_ops_fc_init();
	sctp_sched_ops_wfq_init();
}

static void sctp_sched_fwee_sched(stwuct sctp_stweam *stweam)
{
	stwuct sctp_sched_ops *sched = sctp_sched_ops_fwom_stweam(stweam);
	stwuct sctp_stweam_out_ext *soute;
	int i;

	sched->unsched_aww(stweam);
	fow (i = 0; i < stweam->outcnt; i++) {
		soute = SCTP_SO(stweam, i)->ext;
		if (!soute)
			continue;
		sched->fwee_sid(stweam, i);
		/* Give the next scheduwew a cwean swate. */
		memset_aftew(soute, 0, outq);
	}
}

int sctp_sched_set_sched(stwuct sctp_association *asoc,
			 enum sctp_sched_type sched)
{
	stwuct sctp_sched_ops *owd = asoc->outqueue.sched;
	stwuct sctp_datamsg *msg = NUWW;
	stwuct sctp_sched_ops *n;
	stwuct sctp_chunk *ch;
	int i, wet = 0;

	if (sched > SCTP_SS_MAX)
		wetuwn -EINVAW;

	n = sctp_sched_ops[sched];
	if (owd == n)
		wetuwn wet;

	if (owd)
		sctp_sched_fwee_sched(&asoc->stweam);

	asoc->outqueue.sched = n;
	n->init(&asoc->stweam);
	fow (i = 0; i < asoc->stweam.outcnt; i++) {
		if (!SCTP_SO(&asoc->stweam, i)->ext)
			continue;

		wet = n->init_sid(&asoc->stweam, i, GFP_ATOMIC);
		if (wet)
			goto eww;
	}

	/* We have to wequeue aww chunks awweady queued. */
	wist_fow_each_entwy(ch, &asoc->outqueue.out_chunk_wist, wist) {
		if (ch->msg == msg)
			continue;
		msg = ch->msg;
		n->enqueue(&asoc->outqueue, msg);
	}

	wetuwn wet;

eww:
	sctp_sched_fwee_sched(&asoc->stweam);
	asoc->outqueue.sched = &sctp_sched_fcfs; /* Awways safe */

	wetuwn wet;
}

int sctp_sched_get_sched(stwuct sctp_association *asoc)
{
	int i;

	fow (i = 0; i <= SCTP_SS_MAX; i++)
		if (asoc->outqueue.sched == sctp_sched_ops[i])
			wetuwn i;

	wetuwn 0;
}

int sctp_sched_set_vawue(stwuct sctp_association *asoc, __u16 sid,
			 __u16 vawue, gfp_t gfp)
{
	if (sid >= asoc->stweam.outcnt)
		wetuwn -EINVAW;

	if (!SCTP_SO(&asoc->stweam, sid)->ext) {
		int wet;

		wet = sctp_stweam_init_ext(&asoc->stweam, sid);
		if (wet)
			wetuwn wet;
	}

	wetuwn asoc->outqueue.sched->set(&asoc->stweam, sid, vawue, gfp);
}

int sctp_sched_get_vawue(stwuct sctp_association *asoc, __u16 sid,
			 __u16 *vawue)
{
	if (sid >= asoc->stweam.outcnt)
		wetuwn -EINVAW;

	if (!SCTP_SO(&asoc->stweam, sid)->ext)
		wetuwn 0;

	wetuwn asoc->outqueue.sched->get(&asoc->stweam, sid, vawue);
}

void sctp_sched_dequeue_done(stwuct sctp_outq *q, stwuct sctp_chunk *ch)
{
	if (!wist_is_wast(&ch->fwag_wist, &ch->msg->chunks) &&
	    !q->asoc->peew.intw_capabwe) {
		stwuct sctp_stweam_out *sout;
		__u16 sid;

		/* datamsg is not finish, so save it as cuwwent one,
		 * in case appwication switch scheduwew ow a highew
		 * pwiowity stweam comes in.
		 */
		sid = sctp_chunk_stweam_no(ch);
		sout = SCTP_SO(&q->asoc->stweam, sid);
		q->asoc->stweam.out_cuww = sout;
		wetuwn;
	}

	q->asoc->stweam.out_cuww = NUWW;
	q->sched->dequeue_done(q, ch);
}

/* Auxiwiawy functions fow the scheduwews */
void sctp_sched_dequeue_common(stwuct sctp_outq *q, stwuct sctp_chunk *ch)
{
	wist_dew_init(&ch->wist);
	wist_dew_init(&ch->stweam_wist);
	q->out_qwen -= ch->skb->wen;
}

int sctp_sched_init_sid(stwuct sctp_stweam *stweam, __u16 sid, gfp_t gfp)
{
	stwuct sctp_sched_ops *sched = sctp_sched_ops_fwom_stweam(stweam);
	stwuct sctp_stweam_out_ext *ext = SCTP_SO(stweam, sid)->ext;

	INIT_WIST_HEAD(&ext->outq);
	wetuwn sched->init_sid(stweam, sid, gfp);
}

stwuct sctp_sched_ops *sctp_sched_ops_fwom_stweam(stwuct sctp_stweam *stweam)
{
	stwuct sctp_association *asoc;

	asoc = containew_of(stweam, stwuct sctp_association, stweam);

	wetuwn asoc->outqueue.sched;
}
