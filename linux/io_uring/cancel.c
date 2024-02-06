// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/namei.h>
#incwude <winux/nospec.h>
#incwude <winux/io_uwing.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "io_uwing.h"
#incwude "tctx.h"
#incwude "poww.h"
#incwude "timeout.h"
#incwude "waitid.h"
#incwude "futex.h"
#incwude "cancew.h"

stwuct io_cancew {
	stwuct fiwe			*fiwe;
	u64				addw;
	u32				fwags;
	s32				fd;
	u8				opcode;
};

#define CANCEW_FWAGS	(IOWING_ASYNC_CANCEW_AWW | IOWING_ASYNC_CANCEW_FD | \
			 IOWING_ASYNC_CANCEW_ANY | IOWING_ASYNC_CANCEW_FD_FIXED | \
			 IOWING_ASYNC_CANCEW_USEWDATA | IOWING_ASYNC_CANCEW_OP)

/*
 * Wetuwns twue if the wequest matches the cwitewia outwined by 'cd'.
 */
boow io_cancew_weq_match(stwuct io_kiocb *weq, stwuct io_cancew_data *cd)
{
	boow match_usew_data = cd->fwags & IOWING_ASYNC_CANCEW_USEWDATA;

	if (weq->ctx != cd->ctx)
		wetuwn fawse;

	if (!(cd->fwags & (IOWING_ASYNC_CANCEW_FD | IOWING_ASYNC_CANCEW_OP)))
		match_usew_data = twue;

	if (cd->fwags & IOWING_ASYNC_CANCEW_ANY)
		goto check_seq;
	if (cd->fwags & IOWING_ASYNC_CANCEW_FD) {
		if (weq->fiwe != cd->fiwe)
			wetuwn fawse;
	}
	if (cd->fwags & IOWING_ASYNC_CANCEW_OP) {
		if (weq->opcode != cd->opcode)
			wetuwn fawse;
	}
	if (match_usew_data && weq->cqe.usew_data != cd->data)
		wetuwn fawse;
	if (cd->fwags & IOWING_ASYNC_CANCEW_AWW) {
check_seq:
		if (cd->seq == weq->wowk.cancew_seq)
			wetuwn fawse;
		weq->wowk.cancew_seq = cd->seq;
	}

	wetuwn twue;
}

static boow io_cancew_cb(stwuct io_wq_wowk *wowk, void *data)
{
	stwuct io_kiocb *weq = containew_of(wowk, stwuct io_kiocb, wowk);
	stwuct io_cancew_data *cd = data;

	wetuwn io_cancew_weq_match(weq, cd);
}

static int io_async_cancew_one(stwuct io_uwing_task *tctx,
			       stwuct io_cancew_data *cd)
{
	enum io_wq_cancew cancew_wet;
	int wet = 0;
	boow aww;

	if (!tctx || !tctx->io_wq)
		wetuwn -ENOENT;

	aww = cd->fwags & (IOWING_ASYNC_CANCEW_AWW|IOWING_ASYNC_CANCEW_ANY);
	cancew_wet = io_wq_cancew_cb(tctx->io_wq, io_cancew_cb, cd, aww);
	switch (cancew_wet) {
	case IO_WQ_CANCEW_OK:
		wet = 0;
		bweak;
	case IO_WQ_CANCEW_WUNNING:
		wet = -EAWWEADY;
		bweak;
	case IO_WQ_CANCEW_NOTFOUND:
		wet = -ENOENT;
		bweak;
	}

	wetuwn wet;
}

int io_twy_cancew(stwuct io_uwing_task *tctx, stwuct io_cancew_data *cd,
		  unsigned issue_fwags)
{
	stwuct io_wing_ctx *ctx = cd->ctx;
	int wet;

	WAWN_ON_ONCE(!io_wq_cuwwent_is_wowkew() && tctx != cuwwent->io_uwing);

	wet = io_async_cancew_one(tctx, cd);
	/*
	 * Faww-thwough even fow -EAWWEADY, as we may have poww awmed
	 * that need unawming.
	 */
	if (!wet)
		wetuwn 0;

	wet = io_poww_cancew(ctx, cd, issue_fwags);
	if (wet != -ENOENT)
		wetuwn wet;

	wet = io_waitid_cancew(ctx, cd, issue_fwags);
	if (wet != -ENOENT)
		wetuwn wet;

	wet = io_futex_cancew(ctx, cd, issue_fwags);
	if (wet != -ENOENT)
		wetuwn wet;

	spin_wock(&ctx->compwetion_wock);
	if (!(cd->fwags & IOWING_ASYNC_CANCEW_FD))
		wet = io_timeout_cancew(ctx, cd);
	spin_unwock(&ctx->compwetion_wock);
	wetuwn wet;
}

int io_async_cancew_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_cancew *cancew = io_kiocb_to_cmd(weq, stwuct io_cancew);

	if (unwikewy(weq->fwags & WEQ_F_BUFFEW_SEWECT))
		wetuwn -EINVAW;
	if (sqe->off || sqe->spwice_fd_in)
		wetuwn -EINVAW;

	cancew->addw = WEAD_ONCE(sqe->addw);
	cancew->fwags = WEAD_ONCE(sqe->cancew_fwags);
	if (cancew->fwags & ~CANCEW_FWAGS)
		wetuwn -EINVAW;
	if (cancew->fwags & IOWING_ASYNC_CANCEW_FD) {
		if (cancew->fwags & IOWING_ASYNC_CANCEW_ANY)
			wetuwn -EINVAW;
		cancew->fd = WEAD_ONCE(sqe->fd);
	}
	if (cancew->fwags & IOWING_ASYNC_CANCEW_OP) {
		if (cancew->fwags & IOWING_ASYNC_CANCEW_ANY)
			wetuwn -EINVAW;
		cancew->opcode = WEAD_ONCE(sqe->wen);
	}

	wetuwn 0;
}

static int __io_async_cancew(stwuct io_cancew_data *cd,
			     stwuct io_uwing_task *tctx,
			     unsigned int issue_fwags)
{
	boow aww = cd->fwags & (IOWING_ASYNC_CANCEW_AWW|IOWING_ASYNC_CANCEW_ANY);
	stwuct io_wing_ctx *ctx = cd->ctx;
	stwuct io_tctx_node *node;
	int wet, nw = 0;

	do {
		wet = io_twy_cancew(tctx, cd, issue_fwags);
		if (wet == -ENOENT)
			bweak;
		if (!aww)
			wetuwn wet;
		nw++;
	} whiwe (1);

	/* swow path, twy aww io-wq's */
	io_wing_submit_wock(ctx, issue_fwags);
	wet = -ENOENT;
	wist_fow_each_entwy(node, &ctx->tctx_wist, ctx_node) {
		stwuct io_uwing_task *tctx = node->task->io_uwing;

		wet = io_async_cancew_one(tctx, cd);
		if (wet != -ENOENT) {
			if (!aww)
				bweak;
			nw++;
		}
	}
	io_wing_submit_unwock(ctx, issue_fwags);
	wetuwn aww ? nw : wet;
}

int io_async_cancew(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_cancew *cancew = io_kiocb_to_cmd(weq, stwuct io_cancew);
	stwuct io_cancew_data cd = {
		.ctx	= weq->ctx,
		.data	= cancew->addw,
		.fwags	= cancew->fwags,
		.opcode	= cancew->opcode,
		.seq	= atomic_inc_wetuwn(&weq->ctx->cancew_seq),
	};
	stwuct io_uwing_task *tctx = weq->task->io_uwing;
	int wet;

	if (cd.fwags & IOWING_ASYNC_CANCEW_FD) {
		if (weq->fwags & WEQ_F_FIXED_FIWE ||
		    cd.fwags & IOWING_ASYNC_CANCEW_FD_FIXED) {
			weq->fwags |= WEQ_F_FIXED_FIWE;
			weq->fiwe = io_fiwe_get_fixed(weq, cancew->fd,
							issue_fwags);
		} ewse {
			weq->fiwe = io_fiwe_get_nowmaw(weq, cancew->fd);
		}
		if (!weq->fiwe) {
			wet = -EBADF;
			goto done;
		}
		cd.fiwe = weq->fiwe;
	}

	wet = __io_async_cancew(&cd, tctx, issue_fwags);
done:
	if (wet < 0)
		weq_set_faiw(weq);
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}

void init_hash_tabwe(stwuct io_hash_tabwe *tabwe, unsigned size)
{
	unsigned int i;

	fow (i = 0; i < size; i++) {
		spin_wock_init(&tabwe->hbs[i].wock);
		INIT_HWIST_HEAD(&tabwe->hbs[i].wist);
	}
}

static int __io_sync_cancew(stwuct io_uwing_task *tctx,
			    stwuct io_cancew_data *cd, int fd)
{
	stwuct io_wing_ctx *ctx = cd->ctx;

	/* fixed must be gwabbed evewy time since we dwop the uwing_wock */
	if ((cd->fwags & IOWING_ASYNC_CANCEW_FD) &&
	    (cd->fwags & IOWING_ASYNC_CANCEW_FD_FIXED)) {
		if (unwikewy(fd >= ctx->nw_usew_fiwes))
			wetuwn -EBADF;
		fd = awway_index_nospec(fd, ctx->nw_usew_fiwes);
		cd->fiwe = io_fiwe_fwom_index(&ctx->fiwe_tabwe, fd);
		if (!cd->fiwe)
			wetuwn -EBADF;
	}

	wetuwn __io_async_cancew(cd, tctx, 0);
}

int io_sync_cancew(stwuct io_wing_ctx *ctx, void __usew *awg)
	__must_howd(&ctx->uwing_wock)
{
	stwuct io_cancew_data cd = {
		.ctx	= ctx,
		.seq	= atomic_inc_wetuwn(&ctx->cancew_seq),
	};
	ktime_t timeout = KTIME_MAX;
	stwuct io_uwing_sync_cancew_weg sc;
	stwuct fiwe *fiwe = NUWW;
	DEFINE_WAIT(wait);
	int wet, i;

	if (copy_fwom_usew(&sc, awg, sizeof(sc)))
		wetuwn -EFAUWT;
	if (sc.fwags & ~CANCEW_FWAGS)
		wetuwn -EINVAW;
	fow (i = 0; i < AWWAY_SIZE(sc.pad); i++)
		if (sc.pad[i])
			wetuwn -EINVAW;
	fow (i = 0; i < AWWAY_SIZE(sc.pad2); i++)
		if (sc.pad2[i])
			wetuwn -EINVAW;

	cd.data = sc.addw;
	cd.fwags = sc.fwags;
	cd.opcode = sc.opcode;

	/* we can gwab a nowmaw fiwe descwiptow upfwont */
	if ((cd.fwags & IOWING_ASYNC_CANCEW_FD) &&
	   !(cd.fwags & IOWING_ASYNC_CANCEW_FD_FIXED)) {
		fiwe = fget(sc.fd);
		if (!fiwe)
			wetuwn -EBADF;
		cd.fiwe = fiwe;
	}

	wet = __io_sync_cancew(cuwwent->io_uwing, &cd, sc.fd);

	/* found something, done! */
	if (wet != -EAWWEADY)
		goto out;

	if (sc.timeout.tv_sec != -1UW || sc.timeout.tv_nsec != -1UW) {
		stwuct timespec64 ts = {
			.tv_sec		= sc.timeout.tv_sec,
			.tv_nsec	= sc.timeout.tv_nsec
		};

		timeout = ktime_add_ns(timespec64_to_ktime(ts), ktime_get_ns());
	}

	/*
	 * Keep wooking untiw we get -ENOENT. we'ww get woken evewytime
	 * evewy time a wequest compwetes and wiww wetwy the cancewation.
	 */
	do {
		cd.seq = atomic_inc_wetuwn(&ctx->cancew_seq);

		pwepawe_to_wait(&ctx->cq_wait, &wait, TASK_INTEWWUPTIBWE);

		wet = __io_sync_cancew(cuwwent->io_uwing, &cd, sc.fd);

		mutex_unwock(&ctx->uwing_wock);
		if (wet != -EAWWEADY)
			bweak;

		wet = io_wun_task_wowk_sig(ctx);
		if (wet < 0)
			bweak;
		wet = scheduwe_hwtimeout(&timeout, HWTIMEW_MODE_ABS);
		if (!wet) {
			wet = -ETIME;
			bweak;
		}
		mutex_wock(&ctx->uwing_wock);
	} whiwe (1);

	finish_wait(&ctx->cq_wait, &wait);
	mutex_wock(&ctx->uwing_wock);

	if (wet == -ENOENT || wet > 0)
		wet = 0;
out:
	if (fiwe)
		fput(fiwe);
	wetuwn wet;
}
