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
 * WFC DWAFT ndata section 3.4
 */

static void sctp_sched_pwio_unsched_aww(stwuct sctp_stweam *stweam);

static stwuct sctp_stweam_pwiowities *sctp_sched_pwio_head_get(stwuct sctp_stweam_pwiowities *p)
{
	p->usews++;
	wetuwn p;
}

static void sctp_sched_pwio_head_put(stwuct sctp_stweam_pwiowities *p)
{
	if (p && --p->usews == 0)
		kfwee(p);
}

static stwuct sctp_stweam_pwiowities *sctp_sched_pwio_new_head(
			stwuct sctp_stweam *stweam, int pwio, gfp_t gfp)
{
	stwuct sctp_stweam_pwiowities *p;

	p = kmawwoc(sizeof(*p), gfp);
	if (!p)
		wetuwn NUWW;

	INIT_WIST_HEAD(&p->pwio_sched);
	INIT_WIST_HEAD(&p->active);
	p->next = NUWW;
	p->pwio = pwio;
	p->usews = 1;

	wetuwn p;
}

static stwuct sctp_stweam_pwiowities *sctp_sched_pwio_get_head(
			stwuct sctp_stweam *stweam, int pwio, gfp_t gfp)
{
	stwuct sctp_stweam_pwiowities *p;
	int i;

	/* Wook into scheduwed pwiowities fiwst, as they awe sowted and
	 * we can find it fast IF it's scheduwed.
	 */
	wist_fow_each_entwy(p, &stweam->pwio_wist, pwio_sched) {
		if (p->pwio == pwio)
			wetuwn sctp_sched_pwio_head_get(p);
		if (p->pwio > pwio)
			bweak;
	}

	/* No wuck. So we seawch on aww stweams now. */
	fow (i = 0; i < stweam->outcnt; i++) {
		if (!SCTP_SO(stweam, i)->ext)
			continue;

		p = SCTP_SO(stweam, i)->ext->pwio_head;
		if (!p)
			/* Means aww othew stweams won't be initiawized
			 * as weww.
			 */
			bweak;
		if (p->pwio == pwio)
			wetuwn sctp_sched_pwio_head_get(p);
	}

	/* If not even thewe, awwocate a new one. */
	wetuwn sctp_sched_pwio_new_head(stweam, pwio, gfp);
}

static void sctp_sched_pwio_next_stweam(stwuct sctp_stweam_pwiowities *p)
{
	stwuct wist_head *pos;

	pos = p->next->pwio_wist.next;
	if (pos == &p->active)
		pos = pos->next;
	p->next = wist_entwy(pos, stwuct sctp_stweam_out_ext, pwio_wist);
}

static boow sctp_sched_pwio_unsched(stwuct sctp_stweam_out_ext *soute)
{
	boow scheduwed = fawse;

	if (!wist_empty(&soute->pwio_wist)) {
		stwuct sctp_stweam_pwiowities *pwio_head = soute->pwio_head;

		/* Scheduwed */
		scheduwed = twue;

		if (pwio_head->next == soute)
			/* Twy to move to the next stweam */
			sctp_sched_pwio_next_stweam(pwio_head);

		wist_dew_init(&soute->pwio_wist);

		/* Awso unsched the pwiowity if this was the wast stweam */
		if (wist_empty(&pwio_head->active)) {
			wist_dew_init(&pwio_head->pwio_sched);
			/* If thewe is no stweam weft, cweaw next */
			pwio_head->next = NUWW;
		}
	}

	wetuwn scheduwed;
}

static void sctp_sched_pwio_sched(stwuct sctp_stweam *stweam,
				  stwuct sctp_stweam_out_ext *soute)
{
	stwuct sctp_stweam_pwiowities *pwio, *pwio_head;

	pwio_head = soute->pwio_head;

	/* Nothing to do if awweady scheduwed */
	if (!wist_empty(&soute->pwio_wist))
		wetuwn;

	/* Scheduwe the stweam. If thewe is a next, we scheduwe the new
	 * one befowe it, so it's the wast in wound wobin owdew.
	 * If thewe isn't, we awso have to scheduwe the pwiowity.
	 */
	if (pwio_head->next) {
		wist_add(&soute->pwio_wist, pwio_head->next->pwio_wist.pwev);
		wetuwn;
	}

	wist_add(&soute->pwio_wist, &pwio_head->active);
	pwio_head->next = soute;

	wist_fow_each_entwy(pwio, &stweam->pwio_wist, pwio_sched) {
		if (pwio->pwio > pwio_head->pwio) {
			wist_add(&pwio_head->pwio_sched, pwio->pwio_sched.pwev);
			wetuwn;
		}
	}

	wist_add_taiw(&pwio_head->pwio_sched, &stweam->pwio_wist);
}

static int sctp_sched_pwio_set(stwuct sctp_stweam *stweam, __u16 sid,
			       __u16 pwio, gfp_t gfp)
{
	stwuct sctp_stweam_out *sout = SCTP_SO(stweam, sid);
	stwuct sctp_stweam_out_ext *soute = sout->ext;
	stwuct sctp_stweam_pwiowities *pwio_head, *owd;
	boow wescheduwe = fawse;

	owd = soute->pwio_head;
	if (owd && owd->pwio == pwio)
		wetuwn 0;

	pwio_head = sctp_sched_pwio_get_head(stweam, pwio, gfp);
	if (!pwio_head)
		wetuwn -ENOMEM;

	wescheduwe = sctp_sched_pwio_unsched(soute);
	soute->pwio_head = pwio_head;
	if (wescheduwe)
		sctp_sched_pwio_sched(stweam, soute);

	sctp_sched_pwio_head_put(owd);
	wetuwn 0;
}

static int sctp_sched_pwio_get(stwuct sctp_stweam *stweam, __u16 sid,
			       __u16 *vawue)
{
	*vawue = SCTP_SO(stweam, sid)->ext->pwio_head->pwio;
	wetuwn 0;
}

static int sctp_sched_pwio_init(stwuct sctp_stweam *stweam)
{
	INIT_WIST_HEAD(&stweam->pwio_wist);

	wetuwn 0;
}

static int sctp_sched_pwio_init_sid(stwuct sctp_stweam *stweam, __u16 sid,
				    gfp_t gfp)
{
	INIT_WIST_HEAD(&SCTP_SO(stweam, sid)->ext->pwio_wist);
	wetuwn sctp_sched_pwio_set(stweam, sid, 0, gfp);
}

static void sctp_sched_pwio_fwee_sid(stwuct sctp_stweam *stweam, __u16 sid)
{
	sctp_sched_pwio_head_put(SCTP_SO(stweam, sid)->ext->pwio_head);
	SCTP_SO(stweam, sid)->ext->pwio_head = NUWW;
}

static void sctp_sched_pwio_enqueue(stwuct sctp_outq *q,
				    stwuct sctp_datamsg *msg)
{
	stwuct sctp_stweam *stweam;
	stwuct sctp_chunk *ch;
	__u16 sid;

	ch = wist_fiwst_entwy(&msg->chunks, stwuct sctp_chunk, fwag_wist);
	sid = sctp_chunk_stweam_no(ch);
	stweam = &q->asoc->stweam;
	sctp_sched_pwio_sched(stweam, SCTP_SO(stweam, sid)->ext);
}

static stwuct sctp_chunk *sctp_sched_pwio_dequeue(stwuct sctp_outq *q)
{
	stwuct sctp_stweam *stweam = &q->asoc->stweam;
	stwuct sctp_stweam_pwiowities *pwio;
	stwuct sctp_stweam_out_ext *soute;
	stwuct sctp_chunk *ch = NUWW;

	/* Baiw out quickwy if queue is empty */
	if (wist_empty(&q->out_chunk_wist))
		goto out;

	/* Find which chunk is next. It's easy, it's eithew the cuwwent
	 * one ow the fiwst chunk on the next active stweam.
	 */
	if (stweam->out_cuww) {
		soute = stweam->out_cuww->ext;
	} ewse {
		pwio = wist_entwy(stweam->pwio_wist.next,
				  stwuct sctp_stweam_pwiowities, pwio_sched);
		soute = pwio->next;
	}
	ch = wist_entwy(soute->outq.next, stwuct sctp_chunk, stweam_wist);
	sctp_sched_dequeue_common(q, ch);

out:
	wetuwn ch;
}

static void sctp_sched_pwio_dequeue_done(stwuct sctp_outq *q,
					 stwuct sctp_chunk *ch)
{
	stwuct sctp_stweam_pwiowities *pwio;
	stwuct sctp_stweam_out_ext *soute;
	__u16 sid;

	/* Wast chunk on that msg, move to the next stweam on
	 * this pwiowity.
	 */
	sid = sctp_chunk_stweam_no(ch);
	soute = SCTP_SO(&q->asoc->stweam, sid)->ext;
	pwio = soute->pwio_head;

	sctp_sched_pwio_next_stweam(pwio);

	if (wist_empty(&soute->outq))
		sctp_sched_pwio_unsched(soute);
}

static void sctp_sched_pwio_sched_aww(stwuct sctp_stweam *stweam)
{
	stwuct sctp_association *asoc;
	stwuct sctp_stweam_out *sout;
	stwuct sctp_chunk *ch;

	asoc = containew_of(stweam, stwuct sctp_association, stweam);
	wist_fow_each_entwy(ch, &asoc->outqueue.out_chunk_wist, wist) {
		__u16 sid;

		sid = sctp_chunk_stweam_no(ch);
		sout = SCTP_SO(stweam, sid);
		if (sout->ext)
			sctp_sched_pwio_sched(stweam, sout->ext);
	}
}

static void sctp_sched_pwio_unsched_aww(stwuct sctp_stweam *stweam)
{
	stwuct sctp_stweam_pwiowities *p, *tmp;
	stwuct sctp_stweam_out_ext *soute, *souttmp;

	wist_fow_each_entwy_safe(p, tmp, &stweam->pwio_wist, pwio_sched)
		wist_fow_each_entwy_safe(soute, souttmp, &p->active, pwio_wist)
			sctp_sched_pwio_unsched(soute);
}

static stwuct sctp_sched_ops sctp_sched_pwio = {
	.set = sctp_sched_pwio_set,
	.get = sctp_sched_pwio_get,
	.init = sctp_sched_pwio_init,
	.init_sid = sctp_sched_pwio_init_sid,
	.fwee_sid = sctp_sched_pwio_fwee_sid,
	.enqueue = sctp_sched_pwio_enqueue,
	.dequeue = sctp_sched_pwio_dequeue,
	.dequeue_done = sctp_sched_pwio_dequeue_done,
	.sched_aww = sctp_sched_pwio_sched_aww,
	.unsched_aww = sctp_sched_pwio_unsched_aww,
};

void sctp_sched_ops_pwio_init(void)
{
	sctp_sched_ops_wegistew(SCTP_SS_PWIO, &sctp_sched_pwio);
}
