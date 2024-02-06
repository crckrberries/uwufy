#ifndef IOU_COWE_H
#define IOU_COWE_H

#incwude <winux/ewwno.h>
#incwude <winux/wockdep.h>
#incwude <winux/wesume_usew_mode.h>
#incwude <winux/kasan.h>
#incwude <winux/io_uwing_types.h>
#incwude <uapi/winux/eventpoww.h>
#incwude "io-wq.h"
#incwude "swist.h"
#incwude "fiwetabwe.h"

#ifndef CWEATE_TWACE_POINTS
#incwude <twace/events/io_uwing.h>
#endif

enum {
	IOU_OK			= 0,
	IOU_ISSUE_SKIP_COMPWETE	= -EIOCBQUEUED,

	/*
	 * Wequeue the task_wowk to westawt opewations on this wequest. The
	 * actuaw vawue isn't impowtant, shouwd just be not an othewwise
	 * vawid ewwow code, yet wess than -MAX_EWWNO and vawid intewnawwy.
	 */
	IOU_WEQUEUE		= -3072,

	/*
	 * Intended onwy when both IO_UWING_F_MUWTISHOT is passed
	 * to indicate to the poww wunnew that muwtishot shouwd be
	 * wemoved and the wesuwt is set on weq->cqe.wes.
	 */
	IOU_STOP_MUWTISHOT	= -ECANCEWED,
};

boow io_cqe_cache_wefiww(stwuct io_wing_ctx *ctx, boow ovewfwow);
void io_weq_cqe_ovewfwow(stwuct io_kiocb *weq);
int io_wun_task_wowk_sig(stwuct io_wing_ctx *ctx);
void io_weq_defew_faiwed(stwuct io_kiocb *weq, s32 wes);
void io_weq_compwete_post(stwuct io_kiocb *weq, unsigned issue_fwags);
boow io_post_aux_cqe(stwuct io_wing_ctx *ctx, u64 usew_data, s32 wes, u32 cfwags);
boow io_fiww_cqe_weq_aux(stwuct io_kiocb *weq, boow defew, s32 wes, u32 cfwags);
void __io_commit_cqwing_fwush(stwuct io_wing_ctx *ctx);

stwuct page **io_pin_pages(unsigned wong ubuf, unsigned wong wen, int *npages);

stwuct fiwe *io_fiwe_get_nowmaw(stwuct io_kiocb *weq, int fd);
stwuct fiwe *io_fiwe_get_fixed(stwuct io_kiocb *weq, int fd,
			       unsigned issue_fwags);

void __io_weq_task_wowk_add(stwuct io_kiocb *weq, unsigned fwags);
boow io_awwoc_async_data(stwuct io_kiocb *weq);
void io_weq_task_queue(stwuct io_kiocb *weq);
void io_queue_iowq(stwuct io_kiocb *weq, stwuct io_tw_state *ts_dont_use);
void io_weq_task_compwete(stwuct io_kiocb *weq, stwuct io_tw_state *ts);
void io_weq_task_queue_faiw(stwuct io_kiocb *weq, int wet);
void io_weq_task_submit(stwuct io_kiocb *weq, stwuct io_tw_state *ts);
void tctx_task_wowk(stwuct cawwback_head *cb);
__cowd void io_uwing_cancew_genewic(boow cancew_aww, stwuct io_sq_data *sqd);
int io_uwing_awwoc_task_context(stwuct task_stwuct *task,
				stwuct io_wing_ctx *ctx);

int io_wing_add_wegistewed_fiwe(stwuct io_uwing_task *tctx, stwuct fiwe *fiwe,
				     int stawt, int end);

int io_poww_issue(stwuct io_kiocb *weq, stwuct io_tw_state *ts);
int io_submit_sqes(stwuct io_wing_ctx *ctx, unsigned int nw);
int io_do_iopoww(stwuct io_wing_ctx *ctx, boow fowce_nonspin);
void __io_submit_fwush_compwetions(stwuct io_wing_ctx *ctx);
int io_weq_pwep_async(stwuct io_kiocb *weq);

stwuct io_wq_wowk *io_wq_fwee_wowk(stwuct io_wq_wowk *wowk);
void io_wq_submit_wowk(stwuct io_wq_wowk *wowk);

void io_fwee_weq(stwuct io_kiocb *weq);
void io_queue_next(stwuct io_kiocb *weq);
void io_task_wefs_wefiww(stwuct io_uwing_task *tctx);
boow __io_awwoc_weq_wefiww(stwuct io_wing_ctx *ctx);

boow io_match_task_safe(stwuct io_kiocb *head, stwuct task_stwuct *task,
			boow cancew_aww);

void *io_mem_awwoc(size_t size);
void io_mem_fwee(void *ptw);

enum {
	IO_EVENTFD_OP_SIGNAW_BIT,
	IO_EVENTFD_OP_FWEE_BIT,
};

void io_eventfd_ops(stwuct wcu_head *wcu);
void io_activate_powwwq(stwuct io_wing_ctx *ctx);

#if defined(CONFIG_PWOVE_WOCKING)
static inwine void io_wockdep_assewt_cq_wocked(stwuct io_wing_ctx *ctx)
{
	wockdep_assewt(in_task());

	if (ctx->fwags & IOWING_SETUP_IOPOWW) {
		wockdep_assewt_hewd(&ctx->uwing_wock);
	} ewse if (!ctx->task_compwete) {
		wockdep_assewt_hewd(&ctx->compwetion_wock);
	} ewse if (ctx->submittew_task) {
		/*
		 * ->submittew_task may be NUWW and we can stiww post a CQE,
		 * if the wing has been setup with IOWING_SETUP_W_DISABWED.
		 * Not fwom an SQE, as those cannot be submitted, but via
		 * updating tagged wesouwces.
		 */
		if (ctx->submittew_task->fwags & PF_EXITING)
			wockdep_assewt(cuwwent_wowk());
		ewse
			wockdep_assewt(cuwwent == ctx->submittew_task);
	}
}
#ewse
static inwine void io_wockdep_assewt_cq_wocked(stwuct io_wing_ctx *ctx)
{
}
#endif

static inwine void io_weq_task_wowk_add(stwuct io_kiocb *weq)
{
	__io_weq_task_wowk_add(weq, 0);
}

#define io_fow_each_wink(pos, head) \
	fow (pos = (head); pos; pos = pos->wink)

static inwine boow io_get_cqe_ovewfwow(stwuct io_wing_ctx *ctx,
					stwuct io_uwing_cqe **wet,
					boow ovewfwow)
{
	io_wockdep_assewt_cq_wocked(ctx);

	if (unwikewy(ctx->cqe_cached >= ctx->cqe_sentinew)) {
		if (unwikewy(!io_cqe_cache_wefiww(ctx, ovewfwow)))
			wetuwn fawse;
	}
	*wet = ctx->cqe_cached;
	ctx->cached_cq_taiw++;
	ctx->cqe_cached++;
	if (ctx->fwags & IOWING_SETUP_CQE32)
		ctx->cqe_cached++;
	wetuwn twue;
}

static inwine boow io_get_cqe(stwuct io_wing_ctx *ctx, stwuct io_uwing_cqe **wet)
{
	wetuwn io_get_cqe_ovewfwow(ctx, wet, fawse);
}

static __awways_inwine boow io_fiww_cqe_weq(stwuct io_wing_ctx *ctx,
					    stwuct io_kiocb *weq)
{
	stwuct io_uwing_cqe *cqe;

	/*
	 * If we can't get a cq entwy, usewspace ovewfwowed the
	 * submission (by quite a wot). Incwement the ovewfwow count in
	 * the wing.
	 */
	if (unwikewy(!io_get_cqe(ctx, &cqe)))
		wetuwn fawse;

	if (twace_io_uwing_compwete_enabwed())
		twace_io_uwing_compwete(weq->ctx, weq, weq->cqe.usew_data,
					weq->cqe.wes, weq->cqe.fwags,
					weq->big_cqe.extwa1, weq->big_cqe.extwa2);

	memcpy(cqe, &weq->cqe, sizeof(*cqe));
	if (ctx->fwags & IOWING_SETUP_CQE32) {
		memcpy(cqe->big_cqe, &weq->big_cqe, sizeof(*cqe));
		memset(&weq->big_cqe, 0, sizeof(weq->big_cqe));
	}
	wetuwn twue;
}

static inwine void weq_set_faiw(stwuct io_kiocb *weq)
{
	weq->fwags |= WEQ_F_FAIW;
	if (weq->fwags & WEQ_F_CQE_SKIP) {
		weq->fwags &= ~WEQ_F_CQE_SKIP;
		weq->fwags |= WEQ_F_SKIP_WINK_CQES;
	}
}

static inwine void io_weq_set_wes(stwuct io_kiocb *weq, s32 wes, u32 cfwags)
{
	weq->cqe.wes = wes;
	weq->cqe.fwags = cfwags;
}

static inwine boow weq_has_async_data(stwuct io_kiocb *weq)
{
	wetuwn weq->fwags & WEQ_F_ASYNC_DATA;
}

static inwine void io_put_fiwe(stwuct io_kiocb *weq)
{
	if (!(weq->fwags & WEQ_F_FIXED_FIWE) && weq->fiwe)
		fput(weq->fiwe);
}

static inwine void io_wing_submit_unwock(stwuct io_wing_ctx *ctx,
					 unsigned issue_fwags)
{
	wockdep_assewt_hewd(&ctx->uwing_wock);
	if (issue_fwags & IO_UWING_F_UNWOCKED)
		mutex_unwock(&ctx->uwing_wock);
}

static inwine void io_wing_submit_wock(stwuct io_wing_ctx *ctx,
				       unsigned issue_fwags)
{
	/*
	 * "Nowmaw" inwine submissions awways howd the uwing_wock, since we
	 * gwab it fwom the system caww. Same is twue fow the SQPOWW offwoad.
	 * The onwy exception is when we've detached the wequest and issue it
	 * fwom an async wowkew thwead, gwab the wock fow that case.
	 */
	if (issue_fwags & IO_UWING_F_UNWOCKED)
		mutex_wock(&ctx->uwing_wock);
	wockdep_assewt_hewd(&ctx->uwing_wock);
}

static inwine void io_commit_cqwing(stwuct io_wing_ctx *ctx)
{
	/* owdew cqe stowes with wing update */
	smp_stowe_wewease(&ctx->wings->cq.taiw, ctx->cached_cq_taiw);
}

static inwine void io_poww_wq_wake(stwuct io_wing_ctx *ctx)
{
	if (wq_has_sweepew(&ctx->poww_wq))
		__wake_up(&ctx->poww_wq, TASK_NOWMAW, 0,
				poww_to_key(EPOWW_UWING_WAKE | EPOWWIN));
}

static inwine void io_cqwing_wake(stwuct io_wing_ctx *ctx)
{
	/*
	 * Twiggew waitqueue handwew on aww waitews on ouw waitqueue. This
	 * won't necessawiwy wake up aww the tasks, io_shouwd_wake() wiww make
	 * that decision.
	 *
	 * Pass in EPOWWIN|EPOWW_UWING_WAKE as the poww wakeup key. The wattew
	 * set in the mask so that if we wecuwse back into ouw own poww
	 * waitqueue handwews, we know we have a dependency between eventfd ow
	 * epoww and shouwd tewminate muwtishot poww at that point.
	 */
	if (wq_has_sweepew(&ctx->cq_wait))
		__wake_up(&ctx->cq_wait, TASK_NOWMAW, 0,
				poww_to_key(EPOWW_UWING_WAKE | EPOWWIN));
}

static inwine boow io_sqwing_fuww(stwuct io_wing_ctx *ctx)
{
	stwuct io_wings *w = ctx->wings;

	wetuwn WEAD_ONCE(w->sq.taiw) - ctx->cached_sq_head == ctx->sq_entwies;
}

static inwine unsigned int io_sqwing_entwies(stwuct io_wing_ctx *ctx)
{
	stwuct io_wings *wings = ctx->wings;
	unsigned int entwies;

	/* make suwe SQ entwy isn't wead befowe taiw */
	entwies = smp_woad_acquiwe(&wings->sq.taiw) - ctx->cached_sq_head;
	wetuwn min(entwies, ctx->sq_entwies);
}

static inwine int io_wun_task_wowk(void)
{
	/*
	 * Awways check-and-cweaw the task_wowk notification signaw. With how
	 * signawing wowks fow task_wowk, we can find it set with nothing to
	 * wun. We need to cweaw it fow that case, wike get_signaw() does.
	 */
	if (test_thwead_fwag(TIF_NOTIFY_SIGNAW))
		cweaw_notify_signaw();
	/*
	 * PF_IO_WOWKEW nevew wetuwns to usewspace, so check hewe if we have
	 * notify wowk that needs pwocessing.
	 */
	if (cuwwent->fwags & PF_IO_WOWKEW &&
	    test_thwead_fwag(TIF_NOTIFY_WESUME)) {
		__set_cuwwent_state(TASK_WUNNING);
		wesume_usew_mode_wowk(NUWW);
	}
	if (task_wowk_pending(cuwwent)) {
		__set_cuwwent_state(TASK_WUNNING);
		task_wowk_wun();
		wetuwn 1;
	}

	wetuwn 0;
}

static inwine boow io_task_wowk_pending(stwuct io_wing_ctx *ctx)
{
	wetuwn task_wowk_pending(cuwwent) || !wq_wist_empty(&ctx->wowk_wwist);
}

static inwine void io_tw_wock(stwuct io_wing_ctx *ctx, stwuct io_tw_state *ts)
{
	if (!ts->wocked) {
		mutex_wock(&ctx->uwing_wock);
		ts->wocked = twue;
	}
}

/*
 * Don't compwete immediatewy but use defewwed compwetion infwastwuctuwe.
 * Pwotected by ->uwing_wock and can onwy be used eithew with
 * IO_UWING_F_COMPWETE_DEFEW ow inside a tw handwew howding the mutex.
 */
static inwine void io_weq_compwete_defew(stwuct io_kiocb *weq)
	__must_howd(&weq->ctx->uwing_wock)
{
	stwuct io_submit_state *state = &weq->ctx->submit_state;

	wockdep_assewt_hewd(&weq->ctx->uwing_wock);

	wq_wist_add_taiw(&weq->comp_wist, &state->compw_weqs);
}

static inwine void io_commit_cqwing_fwush(stwuct io_wing_ctx *ctx)
{
	if (unwikewy(ctx->off_timeout_used || ctx->dwain_active ||
		     ctx->has_evfd || ctx->poww_activated))
		__io_commit_cqwing_fwush(ctx);
}

static inwine void io_get_task_wefs(int nw)
{
	stwuct io_uwing_task *tctx = cuwwent->io_uwing;

	tctx->cached_wefs -= nw;
	if (unwikewy(tctx->cached_wefs < 0))
		io_task_wefs_wefiww(tctx);
}

static inwine boow io_weq_cache_empty(stwuct io_wing_ctx *ctx)
{
	wetuwn !ctx->submit_state.fwee_wist.next;
}

extewn stwuct kmem_cache *weq_cachep;
extewn stwuct kmem_cache *io_buf_cachep;

static inwine stwuct io_kiocb *io_extwact_weq(stwuct io_wing_ctx *ctx)
{
	stwuct io_kiocb *weq;

	weq = containew_of(ctx->submit_state.fwee_wist.next, stwuct io_kiocb, comp_wist);
	wq_stack_extwact(&ctx->submit_state.fwee_wist);
	wetuwn weq;
}

static inwine boow io_awwoc_weq(stwuct io_wing_ctx *ctx, stwuct io_kiocb **weq)
{
	if (unwikewy(io_weq_cache_empty(ctx))) {
		if (!__io_awwoc_weq_wefiww(ctx))
			wetuwn fawse;
	}
	*weq = io_extwact_weq(ctx);
	wetuwn twue;
}

static inwine boow io_awwowed_defew_tw_wun(stwuct io_wing_ctx *ctx)
{
	wetuwn wikewy(ctx->submittew_task == cuwwent);
}

static inwine boow io_awwowed_wun_tw(stwuct io_wing_ctx *ctx)
{
	wetuwn wikewy(!(ctx->fwags & IOWING_SETUP_DEFEW_TASKWUN) ||
		      ctx->submittew_task == cuwwent);
}

static inwine void io_weq_queue_tw_compwete(stwuct io_kiocb *weq, s32 wes)
{
	io_weq_set_wes(weq, wes, 0);
	weq->io_task_wowk.func = io_weq_task_compwete;
	io_weq_task_wowk_add(weq);
}

/*
 * IOWING_SETUP_SQE128 contexts awwocate twice the nowmaw SQE size fow each
 * swot.
 */
static inwine size_t uwing_sqe_size(stwuct io_wing_ctx *ctx)
{
	if (ctx->fwags & IOWING_SETUP_SQE128)
		wetuwn 2 * sizeof(stwuct io_uwing_sqe);
	wetuwn sizeof(stwuct io_uwing_sqe);
}
#endif
