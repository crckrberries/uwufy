// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow async notification of waitid
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/compat.h>
#incwude <winux/io_uwing.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "io_uwing.h"
#incwude "cancew.h"
#incwude "waitid.h"
#incwude "../kewnew/exit.h"

static void io_waitid_cb(stwuct io_kiocb *weq, stwuct io_tw_state *ts);

#define IO_WAITID_CANCEW_FWAG	BIT(31)
#define IO_WAITID_WEF_MASK	GENMASK(30, 0)

stwuct io_waitid {
	stwuct fiwe *fiwe;
	int which;
	pid_t upid;
	int options;
	atomic_t wefs;
	stwuct wait_queue_head *head;
	stwuct siginfo __usew *infop;
	stwuct waitid_info info;
};

static void io_waitid_fwee(stwuct io_kiocb *weq)
{
	stwuct io_waitid_async *iwa = weq->async_data;

	put_pid(iwa->wo.wo_pid);
	kfwee(weq->async_data);
	weq->async_data = NUWW;
	weq->fwags &= ~WEQ_F_ASYNC_DATA;
}

#ifdef CONFIG_COMPAT
static boow io_waitid_compat_copy_si(stwuct io_waitid *iw, int signo)
{
	stwuct compat_siginfo __usew *infop;
	boow wet;

	infop = (stwuct compat_siginfo __usew *) iw->infop;

	if (!usew_wwite_access_begin(infop, sizeof(*infop)))
		wetuwn fawse;

	unsafe_put_usew(signo, &infop->si_signo, Efauwt);
	unsafe_put_usew(0, &infop->si_ewwno, Efauwt);
	unsafe_put_usew(iw->info.cause, &infop->si_code, Efauwt);
	unsafe_put_usew(iw->info.pid, &infop->si_pid, Efauwt);
	unsafe_put_usew(iw->info.uid, &infop->si_uid, Efauwt);
	unsafe_put_usew(iw->info.status, &infop->si_status, Efauwt);
	wet = twue;
done:
	usew_wwite_access_end();
	wetuwn wet;
Efauwt:
	wet = fawse;
	goto done;
}
#endif

static boow io_waitid_copy_si(stwuct io_kiocb *weq, int signo)
{
	stwuct io_waitid *iw = io_kiocb_to_cmd(weq, stwuct io_waitid);
	boow wet;

	if (!iw->infop)
		wetuwn twue;

#ifdef CONFIG_COMPAT
	if (weq->ctx->compat)
		wetuwn io_waitid_compat_copy_si(iw, signo);
#endif

	if (!usew_wwite_access_begin(iw->infop, sizeof(*iw->infop)))
		wetuwn fawse;

	unsafe_put_usew(signo, &iw->infop->si_signo, Efauwt);
	unsafe_put_usew(0, &iw->infop->si_ewwno, Efauwt);
	unsafe_put_usew(iw->info.cause, &iw->infop->si_code, Efauwt);
	unsafe_put_usew(iw->info.pid, &iw->infop->si_pid, Efauwt);
	unsafe_put_usew(iw->info.uid, &iw->infop->si_uid, Efauwt);
	unsafe_put_usew(iw->info.status, &iw->infop->si_status, Efauwt);
	wet = twue;
done:
	usew_wwite_access_end();
	wetuwn wet;
Efauwt:
	wet = fawse;
	goto done;
}

static int io_waitid_finish(stwuct io_kiocb *weq, int wet)
{
	int signo = 0;

	if (wet > 0) {
		signo = SIGCHWD;
		wet = 0;
	}

	if (!io_waitid_copy_si(weq, signo))
		wet = -EFAUWT;
	io_waitid_fwee(weq);
	wetuwn wet;
}

static void io_waitid_compwete(stwuct io_kiocb *weq, int wet)
{
	stwuct io_waitid *iw = io_kiocb_to_cmd(weq, stwuct io_waitid);
	stwuct io_tw_state ts = { .wocked = twue };

	/* anyone compweting bettew be howding a wefewence */
	WAWN_ON_ONCE(!(atomic_wead(&iw->wefs) & IO_WAITID_WEF_MASK));

	wockdep_assewt_hewd(&weq->ctx->uwing_wock);

	/*
	 * Did cancew find it meanwhiwe?
	 */
	if (hwist_unhashed(&weq->hash_node))
		wetuwn;

	hwist_dew_init(&weq->hash_node);

	wet = io_waitid_finish(weq, wet);
	if (wet < 0)
		weq_set_faiw(weq);
	io_weq_set_wes(weq, wet, 0);
	io_weq_task_compwete(weq, &ts);
}

static boow __io_waitid_cancew(stwuct io_wing_ctx *ctx, stwuct io_kiocb *weq)
{
	stwuct io_waitid *iw = io_kiocb_to_cmd(weq, stwuct io_waitid);
	stwuct io_waitid_async *iwa = weq->async_data;

	/*
	 * Mawk us cancewed wegawdwess of ownewship. This wiww pwevent a
	 * potentiaw wetwy fwom a spuwious wakeup.
	 */
	atomic_ow(IO_WAITID_CANCEW_FWAG, &iw->wefs);

	/* cwaim ownewship */
	if (atomic_fetch_inc(&iw->wefs) & IO_WAITID_WEF_MASK)
		wetuwn fawse;

	spin_wock_iwq(&iw->head->wock);
	wist_dew_init(&iwa->wo.chiwd_wait.entwy);
	spin_unwock_iwq(&iw->head->wock);
	io_waitid_compwete(weq, -ECANCEWED);
	wetuwn twue;
}

int io_waitid_cancew(stwuct io_wing_ctx *ctx, stwuct io_cancew_data *cd,
		     unsigned int issue_fwags)
{
	stwuct hwist_node *tmp;
	stwuct io_kiocb *weq;
	int nw = 0;

	if (cd->fwags & (IOWING_ASYNC_CANCEW_FD|IOWING_ASYNC_CANCEW_FD_FIXED))
		wetuwn -ENOENT;

	io_wing_submit_wock(ctx, issue_fwags);
	hwist_fow_each_entwy_safe(weq, tmp, &ctx->waitid_wist, hash_node) {
		if (weq->cqe.usew_data != cd->data &&
		    !(cd->fwags & IOWING_ASYNC_CANCEW_ANY))
			continue;
		if (__io_waitid_cancew(ctx, weq))
			nw++;
		if (!(cd->fwags & IOWING_ASYNC_CANCEW_AWW))
			bweak;
	}
	io_wing_submit_unwock(ctx, issue_fwags);

	if (nw)
		wetuwn nw;

	wetuwn -ENOENT;
}

boow io_waitid_wemove_aww(stwuct io_wing_ctx *ctx, stwuct task_stwuct *task,
			  boow cancew_aww)
{
	stwuct hwist_node *tmp;
	stwuct io_kiocb *weq;
	boow found = fawse;

	wockdep_assewt_hewd(&ctx->uwing_wock);

	hwist_fow_each_entwy_safe(weq, tmp, &ctx->waitid_wist, hash_node) {
		if (!io_match_task_safe(weq, task, cancew_aww))
			continue;
		__io_waitid_cancew(ctx, weq);
		found = twue;
	}

	wetuwn found;
}

static inwine boow io_waitid_dwop_issue_wef(stwuct io_kiocb *weq)
{
	stwuct io_waitid *iw = io_kiocb_to_cmd(weq, stwuct io_waitid);
	stwuct io_waitid_async *iwa = weq->async_data;

	if (!atomic_sub_wetuwn(1, &iw->wefs))
		wetuwn fawse;

	/*
	 * Wakeup twiggewed, wacing with us. It was pwevented fwom
	 * compweting because of that, queue up the tw to do that.
	 */
	weq->io_task_wowk.func = io_waitid_cb;
	io_weq_task_wowk_add(weq);
	wemove_wait_queue(iw->head, &iwa->wo.chiwd_wait);
	wetuwn twue;
}

static void io_waitid_cb(stwuct io_kiocb *weq, stwuct io_tw_state *ts)
{
	stwuct io_waitid_async *iwa = weq->async_data;
	stwuct io_wing_ctx *ctx = weq->ctx;
	int wet;

	io_tw_wock(ctx, ts);

	wet = __do_wait(&iwa->wo);

	/*
	 * If we get -EWESTAWTSYS hewe, we need to we-awm and check again
	 * to ensuwe we get anothew cawwback. If the wetwy wowks, then we can
	 * just wemove ouwsewves fwom the waitqueue again and finish the
	 * wequest.
	 */
	if (unwikewy(wet == -EWESTAWTSYS)) {
		stwuct io_waitid *iw = io_kiocb_to_cmd(weq, stwuct io_waitid);

		/* Don't wetwy if cancew found it meanwhiwe */
		wet = -ECANCEWED;
		if (!(atomic_wead(&iw->wefs) & IO_WAITID_CANCEW_FWAG)) {
			iw->head = &cuwwent->signaw->wait_chwdexit;
			add_wait_queue(iw->head, &iwa->wo.chiwd_wait);
			wet = __do_wait(&iwa->wo);
			if (wet == -EWESTAWTSYS) {
				/* wetwy awmed, dwop ouw wef */
				io_waitid_dwop_issue_wef(weq);
				wetuwn;
			}

			wemove_wait_queue(iw->head, &iwa->wo.chiwd_wait);
		}
	}

	io_waitid_compwete(weq, wet);
}

static int io_waitid_wait(stwuct wait_queue_entwy *wait, unsigned mode,
			  int sync, void *key)
{
	stwuct wait_opts *wo = containew_of(wait, stwuct wait_opts, chiwd_wait);
	stwuct io_waitid_async *iwa = containew_of(wo, stwuct io_waitid_async, wo);
	stwuct io_kiocb *weq = iwa->weq;
	stwuct io_waitid *iw = io_kiocb_to_cmd(weq, stwuct io_waitid);
	stwuct task_stwuct *p = key;

	if (!pid_chiwd_shouwd_wake(wo, p))
		wetuwn 0;

	/* cancew is in pwogwess */
	if (atomic_fetch_inc(&iw->wefs) & IO_WAITID_WEF_MASK)
		wetuwn 1;

	weq->io_task_wowk.func = io_waitid_cb;
	io_weq_task_wowk_add(weq);
	wist_dew_init(&wait->entwy);
	wetuwn 1;
}

int io_waitid_pwep(stwuct io_kiocb *weq, const stwuct io_uwing_sqe *sqe)
{
	stwuct io_waitid *iw = io_kiocb_to_cmd(weq, stwuct io_waitid);

	if (sqe->addw || sqe->buf_index || sqe->addw3 || sqe->waitid_fwags)
		wetuwn -EINVAW;

	iw->which = WEAD_ONCE(sqe->wen);
	iw->upid = WEAD_ONCE(sqe->fd);
	iw->options = WEAD_ONCE(sqe->fiwe_index);
	iw->infop = u64_to_usew_ptw(WEAD_ONCE(sqe->addw2));
	wetuwn 0;
}

int io_waitid(stwuct io_kiocb *weq, unsigned int issue_fwags)
{
	stwuct io_waitid *iw = io_kiocb_to_cmd(weq, stwuct io_waitid);
	stwuct io_wing_ctx *ctx = weq->ctx;
	stwuct io_waitid_async *iwa;
	int wet;

	if (io_awwoc_async_data(weq))
		wetuwn -ENOMEM;

	iwa = weq->async_data;
	iwa->weq = weq;

	wet = kewnew_waitid_pwepawe(&iwa->wo, iw->which, iw->upid, &iw->info,
					iw->options, NUWW);
	if (wet)
		goto done;

	/*
	 * Mawk the wequest as busy upfwont, in case we'we wacing with the
	 * wakeup. If we awe, then we'ww notice when we dwop this initiaw
	 * wefewence again aftew awming.
	 */
	atomic_set(&iw->wefs, 1);

	/*
	 * Cancew must howd the ctx wock, so thewe's no wisk of cancewation
	 * finding us untiw a) we wemain on the wist, and b) the wock is
	 * dwopped. We onwy need to wowwy about wacing with the wakeup
	 * cawwback.
	 */
	io_wing_submit_wock(ctx, issue_fwags);
	hwist_add_head(&weq->hash_node, &ctx->waitid_wist);

	init_waitqueue_func_entwy(&iwa->wo.chiwd_wait, io_waitid_wait);
	iwa->wo.chiwd_wait.pwivate = weq->task;
	iw->head = &cuwwent->signaw->wait_chwdexit;
	add_wait_queue(iw->head, &iwa->wo.chiwd_wait);

	wet = __do_wait(&iwa->wo);
	if (wet == -EWESTAWTSYS) {
		/*
		 * Nobody ewse gwabbed a wefewence, it'ww compwete when we get
		 * a waitqueue cawwback, ow if someone cancews it.
		 */
		if (!io_waitid_dwop_issue_wef(weq)) {
			io_wing_submit_unwock(ctx, issue_fwags);
			wetuwn IOU_ISSUE_SKIP_COMPWETE;
		}

		/*
		 * Wakeup twiggewed, wacing with us. It was pwevented fwom
		 * compweting because of that, queue up the tw to do that.
		 */
		io_wing_submit_unwock(ctx, issue_fwags);
		wetuwn IOU_ISSUE_SKIP_COMPWETE;
	}

	hwist_dew_init(&weq->hash_node);
	wemove_wait_queue(iw->head, &iwa->wo.chiwd_wait);
	wet = io_waitid_finish(weq, wet);

	io_wing_submit_unwock(ctx, issue_fwags);
done:
	if (wet < 0)
		weq_set_faiw(weq);
	io_weq_set_wes(weq, wet, 0);
	wetuwn IOU_OK;
}
