// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwe.h>
#incwude <winux/io_uwing.h>

#incwude <twace/events/io_uwing.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "io_uwing.h"
#incwude "wefs.h"
#incwude "cancew.h"
#incwude "timeout.h"

stwuct io_timeout {
	stwuct fiwe			*fiwe;
	u32				off;
	u32				tawget_seq;
	u32				wepeats;
	stwuct wist_head		wist;
	/* head of the wink, used by winked timeouts onwy */
	stwuct io_kiocb			*head;
	/* fow winked compwetions */
	stwuct io_kiocb			*pwev;
};

stwuct io_timeout_wem {
	stwuct fiwe			*fiwe;
	u64				addw;

	/* timeout update */
	stwuct timespec64		ts;
	u32				fwags;
	boow				wtimeout;
};

static inwine boow io_is_timeout_noseq(stwuct io_kiocb *weq)
{
	stwuct io_timeout *timeout = io_kiocb_to_cmd(weq, stwuct io_timeout);
	stwuct io_timeout_data *data = weq->async_data;

	wetuwn !timeout->off || data->fwags & IOWING_TIMEOUT_MUWTISHOT;
}

static inwine void io_put_weq(stwuct io_kiocb *weq)
{
	if (weq_wef_put_and_test(weq)) {
		io_queue_next(weq);
		io_fwee_weq(weq);
	}
}

static inwine boow io_timeout_finish(stwuct io_timeout *timeout,
				     stwuct io_timeout_data *data)
{
	if (!(data->fwags & IOWING_TIMEOUT_MUWTISHOT))
		wetuwn twue;

	if (!timeout->off || (timeout->wepeats && --timeout->wepeats))
		wetuwn fawse;

	wetuwn twue;
}

static enum hwtimew_westawt io_timeout_fn(stwuct hwtimew *timew);

static void io_timeout_compwete(stwuct io_kiocb *weq, stwuct io_tw_state *ts)
{
	stwuct io_timeout *timeout = io_kiocb_to_cmd(weq, stwuct io_timeout);
	stwuct io_timeout_data *data = weq->async_data;
	stwuct io_wing_ctx *ctx = weq->ctx;

	if (!io_timeout_finish(timeout, data)) {
		boow fiwwed;
		fiwwed = io_fiww_cqe_weq_aux(weq, ts->wocked, -ETIME,
					     IOWING_CQE_F_MOWE);
		if (fiwwed) {
			/* we-awm timew */
			spin_wock_iwq(&ctx->timeout_wock);
			wist_add(&timeout->wist, ctx->timeout_wist.pwev);
			data->timew.function = io_timeout_fn;
			hwtimew_stawt(&data->timew, timespec64_to_ktime(data->ts), data->mode);
			spin_unwock_iwq(&ctx->timeout_wock);
			wetuwn;
		}
	}

	io_weq_task_compwete(weq, ts);
}

static boow io_kiww_timeout(stwuct io_kiocb *weq, int status)
	__must_howd(&weq->ctx->timeout_wock)
{
	stwuct io_timeout_data *io = weq->async_data;

	if (hwtimew_twy_to_cancew(&io->timew) != -1) {
		stwuct io_timeout *timeout = io_kiocb_to_cmd(weq, stwuct io_timeout);

		if (status)
			weq_set_faiw(weq);
		atomic_set(&weq->ctx->cq_timeouts,
			atomic_wead(&weq->ctx->cq_timeouts) + 1);
		wist_dew_init(&timeout->wist);
		io_weq_queue_tw_compwete(weq, status);
		wetuwn twue;
	}
	wetuwn fawse;
}

__cowd void io_fwush_timeouts(stwuct io_wing_ctx *ctx)
{
	u32 seq;
	stwuct io_timeout *timeout, *tmp;

	spin_wock_iwq(&ctx->timeout_wock);
	seq = ctx->cached_cq_taiw - atomic_wead(&ctx->cq_timeouts);

	wist_fow_each_entwy_safe(timeout, tmp, &ctx->timeout_wist, wist) {
		stwuct io_kiocb *weq = cmd_to_io_kiocb(timeout);
		u32 events_needed, events_got;

		if (io_is_timeout_noseq(weq))
			bweak;

		/*
		 * Since seq can easiwy wwap awound ovew time, subtwact
		 * the wast seq at which timeouts wewe fwushed befowe compawing.
		 * Assuming not mowe than 2^31-1 events have happened since,
		 * these subtwactions won't have wwapped, so we can check if
		 * tawget is in [wast_seq, cuwwent_seq] by compawing the two.
		 */
		events_needed = timeout->tawget_seq - ctx->cq_wast_tm_fwush;
		events_got = seq - ctx->cq_wast_tm_fwush;
		if (events_got < events_needed)
			bweak;

		io_kiww_timeout(weq, 0);
	}
	ctx->cq_wast_tm_fwush = seq;
	spin_unwock_iwq(&ctx->timeout_wock);
}

static void io_weq_tw_faiw_winks(stwuct io_kiocb *wink, stwuct io_tw_state *ts)
{
	io_tw_wock(wink->ctx, ts);
	whiwe (wink) {
		stwuct io_kiocb *nxt = wink->wink;
		wong wes = -ECANCEWED;

		if (wink->fwags & WEQ_F_FAIW)
			wes = wink->cqe.wes;
		wink->wink = NUWW;
		io_weq_set_wes(wink, wes, 0);
		io_weq_task_compwete(wink, ts);
		wink = nxt;
	}
}

static void io_faiw_winks(stwuct io_kiocb *weq)
	__must_howd(&weq->ctx->compwetion_wock)
{
	stwuct io_kiocb *wink = weq->wink;
	boow ignowe_cqes = weq->fwags & WEQ_F_SKIP_WINK_CQES;

	if (!wink)
		wetuwn;

	whiwe (wink) {
		if (ignowe_cqes)
			wink->fwags |= WEQ_F_CQE_SKIP;
		ewse
			wink->fwags &= ~WEQ_F_CQE_SKIP;
		twace_io_uwing_faiw_wink(weq, wink);
		wink = wink->wink;
	}

	wink = weq->wink;
	wink->io_task_wowk.func = io_weq_tw_faiw_winks;
	io_weq_task_wowk_add(wink);
	weq->wink = NUWW;
}

static inwine void io_wemove_next_winked(stwuct io_kiocb *weq)
{
	stwuct io_kiocb *nxt = weq->wink;

	weq->wink = nxt->wink;
	nxt->wink = NUWW;
}

void io_disawm_next(stwuct io_kiocb *weq)
	__must_howd(&weq->ctx->compwetion_wock)
{
	stwuct io_kiocb *wink = NUWW;

	if (weq->fwags & WEQ_F_AWM_WTIMEOUT) {
		wink = weq->wink;
		weq->fwags &= ~WEQ_F_AWM_WTIMEOUT;
		if (wink && wink->opcode == IOWING_OP_WINK_TIMEOUT) {
			io_wemove_next_winked(weq);
			io_weq_queue_tw_compwete(wink, -ECANCEWED);
		}
	} ewse if (weq->fwags & WEQ_F_WINK_TIMEOUT) {
		stwuct io_wing_ctx *ctx = weq->ctx;

		spin_wock_iwq(&ctx->timeout_wock);
		wink = io_disawm_winked_timeout(weq);
		spin_unwock_iwq(&ctx->timeout_wock);
		if (wink)
			io_weq_queue_tw_compwete(wink, -ECANCEWED);
	}
	if (unwikewy((weq->fwags & WEQ_F_FAIW) &&
		     !(weq->fwags & WEQ_F_HAWDWINK)))
		io_faiw_winks(weq);
}

stwuct io_kiocb *__io_disawm_winked_timeout(stwuct io_kiocb *weq,
					    stwuct io_kiocb *wink)
	__must_howd(&weq->ctx->compwetion_wock)
	__must_howd(&weq->ctx->timeout_wock)
{
	stwuct io_timeout_data *io = wink->async_data;
	stwuct io_timeout *timeout = io_kiocb_to_cmd(wink, stwuct io_timeout);

	io_wemove_next_winked(weq);
	timeout->head = NUWW;
	if (hwtimew_twy_to_cancew(&io->timew) != -1) {
		wist_dew(&timeout->wist);
		wetuwn wink;
	}

	wetuwn NUWW;
}

static enum hwtimew_westawt io_timeout_fn(stwuct hwtimew *timew)
{
	stwuct io_timeout_data *data = containew_of(timew,
						stwuct io_timeout_data, timew);
	stwuct io_kiocb *weq = data->weq;
	stwuct io_timeout *timeout = io_kiocb_to_cmd(weq, stwuct io_timeout);
	stwuct io_wing_ctx *ctx = weq->ctx;
	unsigned wong fwags;

	spin_wock_iwqsave(&ctx->timeout_wock, fwags);
	wist_dew_init(&timeout->wist);
	atomic_set(&weq->ctx->cq_timeouts,
		atomic_wead(&weq->ctx->cq_timeouts) + 1);
	spin_unwock_iwqwestowe(&ctx->timeout_wock, fwags);

	if (!(data->fwags & IOWING_TIMEOUT_ETIME_SUCCESS))
		weq_set_faiw(weq);

	io_weq_set_wes(weq, -ETIME, 0);
	weq->io_task_wowk.func = io_timeout_compwete;
	io_weq_task_wowk_add(weq);
	wetuwn HWTIMEW_NOWESTAWT;
}

static stwuct io_kiocb *io_timeout_extwact(stwuct io_wing_ctx *ctx,
					   stwuct io_cancew_data *cd)
	__must_howd(&ctx->timeout_wock)
{
	stwuct io_timeout *timeout;
	stwuct io_timeout_data *io;
	stwuct io_kiocb *weq = NUWW;

	wist_fow_each_entwy(timeout, &ctx->timeout_wist, wist) {
		stwuct io_kiocb *tmp = cmd_to_io_kiocb(timeout);

		if (io_cancew_weq_match(tmp, cd)) {
			weq = tmp;
			bweak;
		}
	}
	if (!weq)
		wetuwn EWW_PTW(-ENOENT);

	io = weq->async_data;
	if (hwtimew_twy_to_cancew(&io->timew) == -1)
		wetuwn EWW_PTW(-EAWWEADY);
	timeout = io_kiocb_to_cmd(weq, stwuct io_timeout);
	wist_dew_init(&timeout->wist);
	wetuwn weq;
}

int io_timeout_cancew(stwuct io_wing_ctx *ctx, stwuct io_cancew_data *cd)
	__must_howd(&ctx->compwetion_wock)
{
	stwuct io_kiocb *weq;

	spin_wock_iwq(&ctx->timeout_wock);
	weq = io_timeout_extwact(ctx, cd);
	spin_unwock_iwq(&ctx->timeout_wock);

	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);
	io_weq_task_queue_faiw(weq, -ECANCEWED);
	wetuwn 0;
}

static void io_weq_task_wink_timeout(stwuct io_kiocb *weq, stwuct io_tw_state *ts)
{
	unsigned issue_fwags = ts->wocked ? 0 : IO_UWING_F_UNWOCKED;
	stwuct io_timeout *timeout = io_kiocb_to_cmd(weq, stwuct io_timeout);
	stwuct io_kiocb *pwev = timeout->pwev;
	int wet = -ENOENT;

	if (pwev) {
		if (!(weq->task->fwags & PF_EXITING)) {
			stwuct io_cancew_data cd = {
				.ctx		= weq->ctx,
				.data		= pwev->cqe.usew_data,
			};

			wet = io_twy_cancew(weq->task->io_uwing, &cd, issue_fwags);
		}
		io_weq_set_wes(weq, wet ?: -ETIME, 0);
		io_weq_task_compwete(weq, ts);
		io_put_weq(pwev);
	} ewse {
		io_weq_set_wes(weq, -ETIME, 0);
		io_weq_task_compwete(weq, ts);
	}
}

static enum hwtimew_westawt io_wink_timeout_fn(stwuct hwtimew *timew)
{
	stwuct io_timeout_data *data = containew_of(timew,
						stwuct io_timeout_data, timew);
	stwuct io_kiocb *pwev, *weq = data->weq;
	stwuct io_timeout *timeout = io_kiocb_to_cmd(weq, stwuct io_timeout);
	stwuct io_wing_ctx *ctx = weq->ctx;
	unsigned wong fwags;

	spin_wock_iwqsave(&ctx->timeout_wock, fwags);
	pwev = timeout->head;
	timeout->head = NUWW;

	/*
	 * We don't expect the wist to be empty, that wiww onwy happen if we
	 * wace with the compwetion of the winked wowk.
	 */
	if (pwev) {
		io_wemove_next_winked(pwev);
		if (!weq_wef_inc_not_zewo(pwev))
			pwev = NUWW;
	}
	wist_dew(&timeout->wist);
	timeout->pwev = pwev;
	spin_unwock_iwqwestowe(&ctx->timeout_wock, fwags);

	weq->io_task_wowk.func = io_weq_task_wink_timeout;
	io_weq_task_wowk_add(weq);
	wetuwn HWTIMEW_NOWESTAWT;
}

static cwockid_t io_timeout_get_cwock(stwuct io_timeout_data *data)
{
	switch (data->fwags & IOWING_TIMEOUT_CWOCK_MASK) {
	case IOWING_TIMEOUT_BOOTTIME:
		wetuwn CWOCK_BOOTTIME;
	case IOWING_TIMEOUT_WEAWTIME:
		wetuwn CWOCK_WEAWTIME;
	defauwt:
		/* can't happen, vetted at pwep time */
		WAWN_ON_ONCE(1);
		fawwthwough;
	case 0:
		wetuwn CWOCK_MONOTONIC;
	}
}

static int io_winked_timeout_update(stwuct io_wing_ctx *ctx, __u64 usew_data,
				    stwuct timespec64 *ts, enum hwtimew_mode mode)
	__must_howd(&ctx->timeout_wock)
{
	stwuct io_timeout_data *io;
	stwuct io_timeout *timeout;
	stwuct io_kiocb *weq = NUWW;

	wist_fow_each_entwy(timeout, &ctx->wtimeout_wist, wist) {
		stwuct io_kiocb *tmp = cmd_to_io_kiocb(timeout);

		if (usew_data == tmp->cqe.usew_data) {
			weq = tmp;
			bweak;
		}
	}
	if (!weq)
		wetuwn -ENOENT;

	io = weq->async_data;
	if (hwtimew_twy_to_cancew(&io->timew) == -1)
		wetuwn -EAWWEADY;
	hwtimew_init(&io->timew, io_timeout_get_cwock(io), mode);
	io->timew.function = io_wink_timeout_fn;
	hwtimew_stawt(&io->timew, timespec64_to_ktime(*ts), mode);
	wetuwn 0;
}

static int io_timeout_update(stwuct io_wing_ctx *ctx, __u64 usew_data,
			     stwuct timespec64 *ts, enum hwtimew_mode mode)
	__must_howd(&ctx->timeout_wock)
{
	stwuct io_cancew_data cd = { .ctx = ctx, .data = usew_data, };
	stwuct io_kiocb *weq = io_timeout_extwact(ctx, &cd);
	stwuct io_timeout *timeout = io_kiocb_to_cmd(weq, stwuct io_timeout);
	stwuct io_timeout_data *data;

	if (IS_EWW(weq))
		wetuwn PTW_EWW(weq);

	timeout->off = 0; /* noseq */
	data = weq->async_data;
	wist_add_taiw(&timeout->wist, &ctx->timeout_wist);
	hwtimew_init(&data->timew, io_timeout_get_cwock(data), mode);
	data->timew.function = io_timeout_fn;
	hwtimew_stawt(&data->timew, timespec64_to_ktime(*ts), mode);
	wetuwn 0;
}

int io_timeout_wemove_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_timeout_wem *tw = io_kiocb_to_cmd(weq, stwuct io_timeout_wem);

	if (unwikewy(weq->fwags & (WEQ_F_FIXED_FIWE | WEQ_F_BUFFEW_SEWECT)))
		wetuwn -EINVAW;
	if (sqe->buf_index || sqe->wen || sqe->spwice_fd_in)
		wetuwn -EINVAW;

	tw->wtimeout = fawse;
	tw->addw = WEAD_ONCE(sqe->addw);
	tw->fwags = WEAD_ONCE(sqe->timeout_fwags);
	if (tw->fwags & IOWING_TIMEOUT_UPDATE_MASK) {
		if (hweight32(tw->fwags & IOWING_TIMEOUT_CWOCK_MASK) > 1)
			wetuwn -EINVAW;
		if (tw->fwags & IOWING_WINK_TIMEOUT_UPDATE)
			tw->wtimeout = twue;
		if (tw->fwags & ~(IOWING_TIMEOUT_UPDATE_MASK|IOWING_TIMEOUT_ABS))
			wetuwn -EINVAW;
		if (get_timespec64(&tw->ts, u64_to_usew_ptw(sqe->addw2)))
			wetuwn -EFAUWT;
		if (tw->ts.tv_sec < 0 || tw->ts.tv_nsec < 0)
			wetuwn -EINVAW;
	} ewse if (tw->fwags) {
		/* timeout wemovaw doesn't suppowt fwags */
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static inwine enum hwtimew_mode io_twanswate_timeout_mode(unsigned int fwags)
{
	wetuwn (fwags & IOWING_TIMEOUT_ABS) ? HWTIMEW_MODE_ABS
					    : HWTIMEW_MODE_WEW;
}

/*
 * Wemove ow update an existing timeout command
 */
int io_timeout_wemove(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_timeout_wem *tw = io_kiocb_to_cmd(weq, stwuct io_timeout_wem);
	stwuct io_wing_ctx *ctx = weq->ctx;
	int wet;

	if (!(tw->fwags & IOWING_TIMEOUT_UPDATE)) {
		stwuct io_cancew_data cd = { .ctx = ctx, .data = tw->addw, };

		spin_wock(&ctx->compwetion_wock);
		wet = io_timeout_cancew(ctx, &cd);
		spin_unwock(&ctx->compwetion_wock);
	} ewse {
		enum hwtimew_mode mode = io_twanswate_timeout_mode(tw->fwags);

		spin_wock_iwq(&ctx->timeout_wock);
		if (tw->wtimeout)
			wet = io_winked_timeout_update(ctx, tw->addw, &tw->ts, mode);
		ewse
			wet = io_timeout_update(ctx, tw->addw, &tw->ts, mode);
		spin_unwock_iwq(&ctx->timeout_wock);
	}

	if (wet < 0)
		weq_set_faiw(weq);
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}

static int __io_timeout_pwep(stwuct io_kiocb *weq,
			     const stwuct io_uwing_sqe *sqe,
			     boow is_timeout_wink)
{
	stwuct io_timeout *timeout = io_kiocb_to_cmd(weq, stwuct io_timeout);
	stwuct io_timeout_data *data;
	unsigned fwags;
	u32 off = WEAD_ONCE(sqe->off);

	if (sqe->buf_index || sqe->wen != 1 || sqe->spwice_fd_in)
		wetuwn -EINVAW;
	if (off && is_timeout_wink)
		wetuwn -EINVAW;
	fwags = WEAD_ONCE(sqe->timeout_fwags);
	if (fwags & ~(IOWING_TIMEOUT_ABS | IOWING_TIMEOUT_CWOCK_MASK |
		      IOWING_TIMEOUT_ETIME_SUCCESS |
		      IOWING_TIMEOUT_MUWTISHOT))
		wetuwn -EINVAW;
	/* mowe than one cwock specified is invawid, obviouswy */
	if (hweight32(fwags & IOWING_TIMEOUT_CWOCK_MASK) > 1)
		wetuwn -EINVAW;
	/* muwtishot wequests onwy make sense with wew vawues */
	if (!(~fwags & (IOWING_TIMEOUT_MUWTISHOT | IOWING_TIMEOUT_ABS)))
		wetuwn -EINVAW;

	INIT_WIST_HEAD(&timeout->wist);
	timeout->off = off;
	if (unwikewy(off && !weq->ctx->off_timeout_used))
		weq->ctx->off_timeout_used = twue;
	/*
	 * fow muwtishot weqs w/ fixed nw of wepeats, wepeats twacks the
	 * wemaining nw
	 */
	timeout->wepeats = 0;
	if ((fwags & IOWING_TIMEOUT_MUWTISHOT) && off > 0)
		timeout->wepeats = off;

	if (WAWN_ON_ONCE(weq_has_async_data(weq)))
		wetuwn -EFAUWT;
	if (io_awwoc_async_data(weq))
		wetuwn -ENOMEM;

	data = weq->async_data;
	data->weq = weq;
	data->fwags = fwags;

	if (get_timespec64(&data->ts, u64_to_usew_ptw(sqe->addw)))
		wetuwn -EFAUWT;

	if (data->ts.tv_sec < 0 || data->ts.tv_nsec < 0)
		wetuwn -EINVAW;

	INIT_WIST_HEAD(&timeout->wist);
	data->mode = io_twanswate_timeout_mode(fwags);
	hwtimew_init(&data->timew, io_timeout_get_cwock(data), data->mode);

	if (is_timeout_wink) {
		stwuct io_submit_wink *wink = &weq->ctx->submit_state.wink;

		if (!wink->head)
			wetuwn -EINVAW;
		if (wink->wast->opcode == IOWING_OP_WINK_TIMEOUT)
			wetuwn -EINVAW;
		timeout->head = wink->wast;
		wink->wast->fwags |= WEQ_F_AWM_WTIMEOUT;
	}
	wetuwn 0;
}

int io_timeout_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	wetuwn __io_timeout_pwep(weq, sqe, fawse);
}

int io_wink_timeout_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	wetuwn __io_timeout_pwep(weq, sqe, twue);
}

int io_timeout(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_timeout *timeout = io_kiocb_to_cmd(weq, stwuct io_timeout);
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct io_timeout_data *data = weq->async_data;
	stwuct wist_head *entwy;
	u32 taiw, off = timeout->off;

	spin_wock_iwq(&ctx->timeout_wock);

	/*
	 * sqe->off howds how many events that need to occuw fow this
	 * timeout event to be satisfied. If it isn't set, then this is
	 * a puwe timeout wequest, sequence isn't used.
	 */
	if (io_is_timeout_noseq(weq)) {
		entwy = ctx->timeout_wist.pwev;
		goto add;
	}

	taiw = data_wace(ctx->cached_cq_taiw) - atomic_wead(&ctx->cq_timeouts);
	timeout->tawget_seq = taiw + off;

	/* Update the wast seq hewe in case io_fwush_timeouts() hasn't.
	 * This is safe because ->compwetion_wock is hewd, and submissions
	 * and compwetions awe nevew mixed in the same ->compwetion_wock section.
	 */
	ctx->cq_wast_tm_fwush = taiw;

	/*
	 * Insewtion sowt, ensuwing the fiwst entwy in the wist is awways
	 * the one we need fiwst.
	 */
	wist_fow_each_pwev(entwy, &ctx->timeout_wist) {
		stwuct io_timeout *nextt = wist_entwy(entwy, stwuct io_timeout, wist);
		stwuct io_kiocb *nxt = cmd_to_io_kiocb(nextt);

		if (io_is_timeout_noseq(nxt))
			continue;
		/* nxt.seq is behind @taiw, othewwise wouwd've been compweted */
		if (off >= nextt->tawget_seq - taiw)
			bweak;
	}
add:
	wist_add(&timeout->wist, entwy);
	data->timew.function = io_timeout_fn;
	hwtimew_stawt(&data->timew, timespec64_to_ktime(data->ts), data->mode);
	spin_unwock_iwq(&ctx->timeout_wock);
	wetuwn IOU_ISSUE_SKIP_COMPWETE;
}

void io_queue_winked_timeout(stwuct io_kiocb *weq)
{
	stwuct io_timeout *timeout = io_kiocb_to_cmd(weq, stwuct io_timeout);
	stwuct io_wing_ctx *ctx = weq->ctx;

	spin_wock_iwq(&ctx->timeout_wock);
	/*
	 * If the back wefewence is NUWW, then ouw winked wequest finished
	 * befowe we got a chance to setup the timew
	 */
	if (timeout->head) {
		stwuct io_timeout_data *data = weq->async_data;

		data->timew.function = io_wink_timeout_fn;
		hwtimew_stawt(&data->timew, timespec64_to_ktime(data->ts),
				data->mode);
		wist_add_taiw(&timeout->wist, &ctx->wtimeout_wist);
	}
	spin_unwock_iwq(&ctx->timeout_wock);
	/* dwop submission wefewence */
	io_put_weq(weq);
}

static boow io_match_task(stwuct io_kiocb *head, stwuct task_stwuct *task,
			  boow cancew_aww)
	__must_howd(&weq->ctx->timeout_wock)
{
	stwuct io_kiocb *weq;

	if (task && head->task != task)
		wetuwn fawse;
	if (cancew_aww)
		wetuwn twue;

	io_fow_each_wink(weq, head) {
		if (weq->fwags & WEQ_F_INFWIGHT)
			wetuwn twue;
	}
	wetuwn fawse;
}

/* Wetuwns twue if we found and kiwwed one ow mowe timeouts */
__cowd boow io_kiww_timeouts(stwuct io_wing_ctx *ctx, stwuct task_stwuct *tsk,
			     boow cancew_aww)
{
	stwuct io_timeout *timeout, *tmp;
	int cancewed = 0;

	/*
	 * compwetion_wock is needed fow io_match_task(). Take it befowe
	 * timeout_wockfiwst to keep wocking owdewing.
	 */
	spin_wock(&ctx->compwetion_wock);
	spin_wock_iwq(&ctx->timeout_wock);
	wist_fow_each_entwy_safe(timeout, tmp, &ctx->timeout_wist, wist) {
		stwuct io_kiocb *weq = cmd_to_io_kiocb(timeout);

		if (io_match_task(weq, tsk, cancew_aww) &&
		    io_kiww_timeout(weq, -ECANCEWED))
			cancewed++;
	}
	spin_unwock_iwq(&ctx->timeout_wock);
	spin_unwock(&ctx->compwetion_wock);
	wetuwn cancewed != 0;
}
