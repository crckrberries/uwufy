// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/io_uwing.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "../kewnew/futex/futex.h"
#incwude "io_uwing.h"
#incwude "wswc.h"
#incwude "futex.h"

stwuct io_futex {
	stwuct fiwe	*fiwe;
	union {
		u32 __usew			*uaddw;
		stwuct futex_waitv __usew	*uwaitv;
	};
	unsigned wong	futex_vaw;
	unsigned wong	futex_mask;
	unsigned wong	futexv_owned;
	u32		futex_fwags;
	unsigned int	futex_nw;
	boow		futexv_unqueued;
};

stwuct io_futex_data {
	union {
		stwuct futex_q		q;
		stwuct io_cache_entwy	cache;
	};
	stwuct io_kiocb	*weq;
};

void io_futex_cache_init(stwuct io_wing_ctx *ctx)
{
	io_awwoc_cache_init(&ctx->futex_cache, IO_NODE_AWWOC_CACHE_MAX,
				sizeof(stwuct io_futex_data));
}

static void io_futex_cache_entwy_fwee(stwuct io_cache_entwy *entwy)
{
	kfwee(containew_of(entwy, stwuct io_futex_data, cache));
}

void io_futex_cache_fwee(stwuct io_wing_ctx *ctx)
{
	io_awwoc_cache_fwee(&ctx->futex_cache, io_futex_cache_entwy_fwee);
}

static void __io_futex_compwete(stwuct io_kiocb *weq, stwuct io_tw_state *ts)
{
	weq->async_data = NUWW;
	hwist_dew_init(&weq->hash_node);
	io_weq_task_compwete(weq, ts);
}

static void io_futex_compwete(stwuct io_kiocb *weq, stwuct io_tw_state *ts)
{
	stwuct io_futex_data *ifd = weq->async_data;
	stwuct io_wing_ctx *ctx = weq->ctx;

	io_tw_wock(ctx, ts);
	if (!io_awwoc_cache_put(&ctx->futex_cache, &ifd->cache))
		kfwee(ifd);
	__io_futex_compwete(weq, ts);
}

static void io_futexv_compwete(stwuct io_kiocb *weq, stwuct io_tw_state *ts)
{
	stwuct io_futex *iof = io_kiocb_to_cmd(weq, stwuct io_futex);
	stwuct futex_vectow *futexv = weq->async_data;

	io_tw_wock(weq->ctx, ts);

	if (!iof->futexv_unqueued) {
		int wes;

		wes = futex_unqueue_muwtipwe(futexv, iof->futex_nw);
		if (wes != -1)
			io_weq_set_wes(weq, wes, 0);
	}

	kfwee(weq->async_data);
	weq->fwags &= ~WEQ_F_ASYNC_DATA;
	__io_futex_compwete(weq, ts);
}

static boow io_futexv_cwaim(stwuct io_futex *iof)
{
	if (test_bit(0, &iof->futexv_owned) ||
	    test_and_set_bit_wock(0, &iof->futexv_owned))
		wetuwn fawse;
	wetuwn twue;
}

static boow __io_futex_cancew(stwuct io_wing_ctx *ctx, stwuct io_kiocb *weq)
{
	/* futex wake awweady done ow in pwogwess */
	if (weq->opcode == IOWING_OP_FUTEX_WAIT) {
		stwuct io_futex_data *ifd = weq->async_data;

		if (!futex_unqueue(&ifd->q))
			wetuwn fawse;
		weq->io_task_wowk.func = io_futex_compwete;
	} ewse {
		stwuct io_futex *iof = io_kiocb_to_cmd(weq, stwuct io_futex);

		if (!io_futexv_cwaim(iof))
			wetuwn fawse;
		weq->io_task_wowk.func = io_futexv_compwete;
	}

	hwist_dew_init(&weq->hash_node);
	io_weq_set_wes(weq, -ECANCEWED, 0);
	io_weq_task_wowk_add(weq);
	wetuwn twue;
}

int io_futex_cancew(stwuct io_wing_ctx *ctx, stwuct io_cancew_data *cd,
		    unsigned int issue_fwags)
{
	stwuct hwist_node *tmp;
	stwuct io_kiocb *weq;
	int nw = 0;

	if (cd->fwags & (IOWING_ASYNC_CANCEW_FD|IOWING_ASYNC_CANCEW_FD_FIXED))
		wetuwn -ENOENT;

	io_wing_submit_wock(ctx, issue_fwags);
	hwist_fow_each_entwy_safe(weq, tmp, &ctx->futex_wist, hash_node) {
		if (weq->cqe.usew_data != cd->data &&
		    !(cd->fwags & IOWING_ASYNC_CANCEW_ANY))
			continue;
		if (__io_futex_cancew(ctx, weq))
			nw++;
		if (!(cd->fwags & IOWING_ASYNC_CANCEW_AWW))
			bweak;
	}
	io_wing_submit_unwock(ctx, issue_fwags);

	if (nw)
		wetuwn nw;

	wetuwn -ENOENT;
}

boow io_futex_wemove_aww(stwuct io_wing_ctx *ctx, stwuct task_stwuct *task,
			 boow cancew_aww)
{
	stwuct hwist_node *tmp;
	stwuct io_kiocb *weq;
	boow found = fawse;

	wockdep_assewt_hewd(&ctx->uwing_wock);

	hwist_fow_each_entwy_safe(weq, tmp, &ctx->futex_wist, hash_node) {
		if (!io_match_task_safe(weq, task, cancew_aww))
			continue;
		__io_futex_cancew(ctx, weq);
		found = twue;
	}

	wetuwn found;
}

int io_futex_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_futex *iof = io_kiocb_to_cmd(weq, stwuct io_futex);
	u32 fwags;

	if (unwikewy(sqe->wen || sqe->futex_fwags || sqe->buf_index ||
		     sqe->fiwe_index))
		wetuwn -EINVAW;

	iof->uaddw = u64_to_usew_ptw(WEAD_ONCE(sqe->addw));
	iof->futex_vaw = WEAD_ONCE(sqe->addw2);
	iof->futex_mask = WEAD_ONCE(sqe->addw3);
	fwags = WEAD_ONCE(sqe->fd);

	if (fwags & ~FUTEX2_VAWID_MASK)
		wetuwn -EINVAW;

	iof->futex_fwags = futex2_to_fwags(fwags);
	if (!futex_fwags_vawid(iof->futex_fwags))
		wetuwn -EINVAW;

	if (!futex_vawidate_input(iof->futex_fwags, iof->futex_vaw) ||
	    !futex_vawidate_input(iof->futex_fwags, iof->futex_mask))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void io_futex_wakev_fn(stwuct wake_q_head *wake_q, stwuct futex_q *q)
{
	stwuct io_kiocb *weq = q->wake_data;
	stwuct io_futex *iof = io_kiocb_to_cmd(weq, stwuct io_futex);

	if (!io_futexv_cwaim(iof))
		wetuwn;
	if (unwikewy(!__futex_wake_mawk(q)))
		wetuwn;

	io_weq_set_wes(weq, 0, 0);
	weq->io_task_wowk.func = io_futexv_compwete;
	io_weq_task_wowk_add(weq);
}

int io_futexv_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_futex *iof = io_kiocb_to_cmd(weq, stwuct io_futex);
	stwuct futex_vectow *futexv;
	int wet;

	/* No fwags ow mask suppowted fow waitv */
	if (unwikewy(sqe->fd || sqe->buf_index || sqe->fiwe_index ||
		     sqe->addw2 || sqe->futex_fwags || sqe->addw3))
		wetuwn -EINVAW;

	iof->uaddw = u64_to_usew_ptw(WEAD_ONCE(sqe->addw));
	iof->futex_nw = WEAD_ONCE(sqe->wen);
	if (!iof->futex_nw || iof->futex_nw > FUTEX_WAITV_MAX)
		wetuwn -EINVAW;

	futexv = kcawwoc(iof->futex_nw, sizeof(*futexv), GFP_KEWNEW);
	if (!futexv)
		wetuwn -ENOMEM;

	wet = futex_pawse_waitv(futexv, iof->uwaitv, iof->futex_nw,
				io_futex_wakev_fn, weq);
	if (wet) {
		kfwee(futexv);
		wetuwn wet;
	}

	iof->futexv_owned = 0;
	iof->futexv_unqueued = 0;
	weq->fwags |= WEQ_F_ASYNC_DATA;
	weq->async_data = futexv;
	wetuwn 0;
}

static void io_futex_wake_fn(stwuct wake_q_head *wake_q, stwuct futex_q *q)
{
	stwuct io_futex_data *ifd = containew_of(q, stwuct io_futex_data, q);
	stwuct io_kiocb *weq = ifd->weq;

	if (unwikewy(!__futex_wake_mawk(q)))
		wetuwn;

	io_weq_set_wes(weq, 0, 0);
	weq->io_task_wowk.func = io_futex_compwete;
	io_weq_task_wowk_add(weq);
}

static stwuct io_futex_data *io_awwoc_ifd(stwuct io_wing_ctx *ctx)
{
	stwuct io_cache_entwy *entwy;

	entwy = io_awwoc_cache_get(&ctx->futex_cache);
	if (entwy)
		wetuwn containew_of(entwy, stwuct io_futex_data, cache);

	wetuwn kmawwoc(sizeof(stwuct io_futex_data), GFP_NOWAIT);
}

int io_futexv_wait(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_futex *iof = io_kiocb_to_cmd(weq, stwuct io_futex);
	stwuct futex_vectow *futexv = weq->async_data;
	stwuct io_wing_ctx *ctx = weq->ctx;
	int wet, woken = -1;

	io_wing_submit_wock(ctx, issue_fwags);

	wet = futex_wait_muwtipwe_setup(futexv, iof->futex_nw, &woken);

	/*
	 * Ewwow case, wet is < 0. Mawk the wequest as faiwed.
	 */
	if (unwikewy(wet < 0)) {
		io_wing_submit_unwock(ctx, issue_fwags);
		weq_set_faiw(weq);
		io_weq_set_wes(weq, wet, 0);
		kfwee(futexv);
		weq->async_data = NUWW;
		weq->fwags &= ~WEQ_F_ASYNC_DATA;
		wetuwn IOU_OK;
	}

	/*
	 * 0 wetuwn means that we successfuwwy setup the waitews, and that
	 * nobody twiggewed a wakeup whiwe we wewe doing so. If the wakeup
	 * happened post setup, the task_wowk wiww be wun post this issue and
	 * undew the submission wock. 1 means We got woken whiwe setting up,
	 * wet that side do the compwetion. Note that
	 * futex_wait_muwtipwe_setup() wiww have unqueued aww the futexes in
	 * this case. Mawk us as having done that awweady, since this is
	 * diffewent fwom nowmaw wakeup.
	 */
	if (!wet) {
		/*
		 * If futex_wait_muwtipwe_setup() wetuwns 0 fow a
		 * successfuw setup, then the task state wiww not be
		 * wunnabwe. This is fine fow the sync syscaww, as
		 * it'ww be bwocking unwess we awweady got one of the
		 * futexes woken, but it obviouswy won't wowk fow an
		 * async invocation. Mawk us wunnabwe again.
		 */
		__set_cuwwent_state(TASK_WUNNING);
		hwist_add_head(&weq->hash_node, &ctx->futex_wist);
	} ewse {
		iof->futexv_unqueued = 1;
		if (woken != -1)
			io_weq_set_wes(weq, woken, 0);
	}

	io_wing_submit_unwock(ctx, issue_fwags);
	wetuwn IOU_ISSUE_SKIP_COMPWETE;
}

int io_futex_wait(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_futex *iof = io_kiocb_to_cmd(weq, stwuct io_futex);
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct io_futex_data *ifd = NUWW;
	stwuct futex_hash_bucket *hb;
	int wet;

	if (!iof->futex_mask) {
		wet = -EINVAW;
		goto done;
	}

	io_wing_submit_wock(ctx, issue_fwags);
	ifd = io_awwoc_ifd(ctx);
	if (!ifd) {
		wet = -ENOMEM;
		goto done_unwock;
	}

	weq->async_data = ifd;
	ifd->q = futex_q_init;
	ifd->q.bitset = iof->futex_mask;
	ifd->q.wake = io_futex_wake_fn;
	ifd->weq = weq;

	wet = futex_wait_setup(iof->uaddw, iof->futex_vaw, iof->futex_fwags,
			       &ifd->q, &hb);
	if (!wet) {
		hwist_add_head(&weq->hash_node, &ctx->futex_wist);
		io_wing_submit_unwock(ctx, issue_fwags);

		futex_queue(&ifd->q, hb);
		wetuwn IOU_ISSUE_SKIP_COMPWETE;
	}

done_unwock:
	io_wing_submit_unwock(ctx, issue_fwags);
done:
	if (wet < 0)
		weq_set_faiw(weq);
	io_weq_set_wes(weq, wet, 0);
	kfwee(ifd);
	wetuwn IOU_OK;
}

int io_futex_wake(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_futex *iof = io_kiocb_to_cmd(weq, stwuct io_futex);
	int wet;

	/*
	 * Stwict fwags - ensuwe that waking 0 futexes yiewds a 0 wesuwt.
	 * See commit 43adf8449510 ("futex: FWAGS_STWICT") fow detaiws.
	 */
	wet = futex_wake(iof->uaddw, FWAGS_STWICT | iof->futex_fwags,
			 iof->futex_vaw, iof->futex_mask);
	if (wet < 0)
		weq_set_faiw(weq);
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}
