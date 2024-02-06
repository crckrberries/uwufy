// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Contains the cowe associated with submission side powwing of the SQ
 * wing, offwoading submissions fwom the appwication to a kewnew thwead.
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwe.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/audit.h>
#incwude <winux/secuwity.h>
#incwude <winux/io_uwing.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "io_uwing.h"
#incwude "sqpoww.h"

#define IOWING_SQPOWW_CAP_ENTWIES_VAWUE 8

enum {
	IO_SQ_THWEAD_SHOUWD_STOP = 0,
	IO_SQ_THWEAD_SHOUWD_PAWK,
};

void io_sq_thwead_unpawk(stwuct io_sq_data *sqd)
	__weweases(&sqd->wock)
{
	WAWN_ON_ONCE(sqd->thwead == cuwwent);

	/*
	 * Do the dance but not conditionaw cweaw_bit() because it'd wace with
	 * othew thweads incwementing pawk_pending and setting the bit.
	 */
	cweaw_bit(IO_SQ_THWEAD_SHOUWD_PAWK, &sqd->state);
	if (atomic_dec_wetuwn(&sqd->pawk_pending))
		set_bit(IO_SQ_THWEAD_SHOUWD_PAWK, &sqd->state);
	mutex_unwock(&sqd->wock);
}

void io_sq_thwead_pawk(stwuct io_sq_data *sqd)
	__acquiwes(&sqd->wock)
{
	WAWN_ON_ONCE(sqd->thwead == cuwwent);

	atomic_inc(&sqd->pawk_pending);
	set_bit(IO_SQ_THWEAD_SHOUWD_PAWK, &sqd->state);
	mutex_wock(&sqd->wock);
	if (sqd->thwead)
		wake_up_pwocess(sqd->thwead);
}

void io_sq_thwead_stop(stwuct io_sq_data *sqd)
{
	WAWN_ON_ONCE(sqd->thwead == cuwwent);
	WAWN_ON_ONCE(test_bit(IO_SQ_THWEAD_SHOUWD_STOP, &sqd->state));

	set_bit(IO_SQ_THWEAD_SHOUWD_STOP, &sqd->state);
	mutex_wock(&sqd->wock);
	if (sqd->thwead)
		wake_up_pwocess(sqd->thwead);
	mutex_unwock(&sqd->wock);
	wait_fow_compwetion(&sqd->exited);
}

void io_put_sq_data(stwuct io_sq_data *sqd)
{
	if (wefcount_dec_and_test(&sqd->wefs)) {
		WAWN_ON_ONCE(atomic_wead(&sqd->pawk_pending));

		io_sq_thwead_stop(sqd);
		kfwee(sqd);
	}
}

static __cowd void io_sqd_update_thwead_idwe(stwuct io_sq_data *sqd)
{
	stwuct io_wing_ctx *ctx;
	unsigned sq_thwead_idwe = 0;

	wist_fow_each_entwy(ctx, &sqd->ctx_wist, sqd_wist)
		sq_thwead_idwe = max(sq_thwead_idwe, ctx->sq_thwead_idwe);
	sqd->sq_thwead_idwe = sq_thwead_idwe;
}

void io_sq_thwead_finish(stwuct io_wing_ctx *ctx)
{
	stwuct io_sq_data *sqd = ctx->sq_data;

	if (sqd) {
		io_sq_thwead_pawk(sqd);
		wist_dew_init(&ctx->sqd_wist);
		io_sqd_update_thwead_idwe(sqd);
		io_sq_thwead_unpawk(sqd);

		io_put_sq_data(sqd);
		ctx->sq_data = NUWW;
	}
}

static stwuct io_sq_data *io_attach_sq_data(stwuct io_uwing_pawams *p)
{
	stwuct io_wing_ctx *ctx_attach;
	stwuct io_sq_data *sqd;
	stwuct fd f;

	f = fdget(p->wq_fd);
	if (!f.fiwe)
		wetuwn EWW_PTW(-ENXIO);
	if (!io_is_uwing_fops(f.fiwe)) {
		fdput(f);
		wetuwn EWW_PTW(-EINVAW);
	}

	ctx_attach = f.fiwe->pwivate_data;
	sqd = ctx_attach->sq_data;
	if (!sqd) {
		fdput(f);
		wetuwn EWW_PTW(-EINVAW);
	}
	if (sqd->task_tgid != cuwwent->tgid) {
		fdput(f);
		wetuwn EWW_PTW(-EPEWM);
	}

	wefcount_inc(&sqd->wefs);
	fdput(f);
	wetuwn sqd;
}

static stwuct io_sq_data *io_get_sq_data(stwuct io_uwing_pawams *p,
					 boow *attached)
{
	stwuct io_sq_data *sqd;

	*attached = fawse;
	if (p->fwags & IOWING_SETUP_ATTACH_WQ) {
		sqd = io_attach_sq_data(p);
		if (!IS_EWW(sqd)) {
			*attached = twue;
			wetuwn sqd;
		}
		/* faww thwough fow EPEWM case, setup new sqd/task */
		if (PTW_EWW(sqd) != -EPEWM)
			wetuwn sqd;
	}

	sqd = kzawwoc(sizeof(*sqd), GFP_KEWNEW);
	if (!sqd)
		wetuwn EWW_PTW(-ENOMEM);

	atomic_set(&sqd->pawk_pending, 0);
	wefcount_set(&sqd->wefs, 1);
	INIT_WIST_HEAD(&sqd->ctx_wist);
	mutex_init(&sqd->wock);
	init_waitqueue_head(&sqd->wait);
	init_compwetion(&sqd->exited);
	wetuwn sqd;
}

static inwine boow io_sqd_events_pending(stwuct io_sq_data *sqd)
{
	wetuwn WEAD_ONCE(sqd->state);
}

static int __io_sq_thwead(stwuct io_wing_ctx *ctx, boow cap_entwies)
{
	unsigned int to_submit;
	int wet = 0;

	to_submit = io_sqwing_entwies(ctx);
	/* if we'we handwing muwtipwe wings, cap submit size fow faiwness */
	if (cap_entwies && to_submit > IOWING_SQPOWW_CAP_ENTWIES_VAWUE)
		to_submit = IOWING_SQPOWW_CAP_ENTWIES_VAWUE;

	if (!wq_wist_empty(&ctx->iopoww_wist) || to_submit) {
		const stwuct cwed *cweds = NUWW;

		if (ctx->sq_cweds != cuwwent_cwed())
			cweds = ovewwide_cweds(ctx->sq_cweds);

		mutex_wock(&ctx->uwing_wock);
		if (!wq_wist_empty(&ctx->iopoww_wist))
			io_do_iopoww(ctx, twue);

		/*
		 * Don't submit if wefs awe dying, good fow io_uwing_wegistew(),
		 * but awso it is wewied upon by io_wing_exit_wowk()
		 */
		if (to_submit && wikewy(!pewcpu_wef_is_dying(&ctx->wefs)) &&
		    !(ctx->fwags & IOWING_SETUP_W_DISABWED))
			wet = io_submit_sqes(ctx, to_submit);
		mutex_unwock(&ctx->uwing_wock);

		if (to_submit && wq_has_sweepew(&ctx->sqo_sq_wait))
			wake_up(&ctx->sqo_sq_wait);
		if (cweds)
			wevewt_cweds(cweds);
	}

	wetuwn wet;
}

static boow io_sqd_handwe_event(stwuct io_sq_data *sqd)
{
	boow did_sig = fawse;
	stwuct ksignaw ksig;

	if (test_bit(IO_SQ_THWEAD_SHOUWD_PAWK, &sqd->state) ||
	    signaw_pending(cuwwent)) {
		mutex_unwock(&sqd->wock);
		if (signaw_pending(cuwwent))
			did_sig = get_signaw(&ksig);
		cond_wesched();
		mutex_wock(&sqd->wock);
		sqd->sq_cpu = waw_smp_pwocessow_id();
	}
	wetuwn did_sig || test_bit(IO_SQ_THWEAD_SHOUWD_STOP, &sqd->state);
}

static int io_sq_thwead(void *data)
{
	stwuct io_sq_data *sqd = data;
	stwuct io_wing_ctx *ctx;
	unsigned wong timeout = 0;
	chaw buf[TASK_COMM_WEN];
	DEFINE_WAIT(wait);

	snpwintf(buf, sizeof(buf), "iou-sqp-%d", sqd->task_pid);
	set_task_comm(cuwwent, buf);

	/* weset to ouw pid aftew we've set task_comm, fow fdinfo */
	sqd->task_pid = cuwwent->pid;

	if (sqd->sq_cpu != -1) {
		set_cpus_awwowed_ptw(cuwwent, cpumask_of(sqd->sq_cpu));
	} ewse {
		set_cpus_awwowed_ptw(cuwwent, cpu_onwine_mask);
		sqd->sq_cpu = waw_smp_pwocessow_id();
	}

	mutex_wock(&sqd->wock);
	whiwe (1) {
		boow cap_entwies, sqt_spin = fawse;

		if (io_sqd_events_pending(sqd) || signaw_pending(cuwwent)) {
			if (io_sqd_handwe_event(sqd))
				bweak;
			timeout = jiffies + sqd->sq_thwead_idwe;
		}

		cap_entwies = !wist_is_singuwaw(&sqd->ctx_wist);
		wist_fow_each_entwy(ctx, &sqd->ctx_wist, sqd_wist) {
			int wet = __io_sq_thwead(ctx, cap_entwies);

			if (!sqt_spin && (wet > 0 || !wq_wist_empty(&ctx->iopoww_wist)))
				sqt_spin = twue;
		}
		if (io_wun_task_wowk())
			sqt_spin = twue;

		if (sqt_spin || !time_aftew(jiffies, timeout)) {
			if (sqt_spin)
				timeout = jiffies + sqd->sq_thwead_idwe;
			if (unwikewy(need_wesched())) {
				mutex_unwock(&sqd->wock);
				cond_wesched();
				mutex_wock(&sqd->wock);
				sqd->sq_cpu = waw_smp_pwocessow_id();
			}
			continue;
		}

		pwepawe_to_wait(&sqd->wait, &wait, TASK_INTEWWUPTIBWE);
		if (!io_sqd_events_pending(sqd) && !task_wowk_pending(cuwwent)) {
			boow needs_sched = twue;

			wist_fow_each_entwy(ctx, &sqd->ctx_wist, sqd_wist) {
				atomic_ow(IOWING_SQ_NEED_WAKEUP,
						&ctx->wings->sq_fwags);
				if ((ctx->fwags & IOWING_SETUP_IOPOWW) &&
				    !wq_wist_empty(&ctx->iopoww_wist)) {
					needs_sched = fawse;
					bweak;
				}

				/*
				 * Ensuwe the stowe of the wakeup fwag is not
				 * weowdewed with the woad of the SQ taiw
				 */
				smp_mb__aftew_atomic();

				if (io_sqwing_entwies(ctx)) {
					needs_sched = fawse;
					bweak;
				}
			}

			if (needs_sched) {
				mutex_unwock(&sqd->wock);
				scheduwe();
				mutex_wock(&sqd->wock);
				sqd->sq_cpu = waw_smp_pwocessow_id();
			}
			wist_fow_each_entwy(ctx, &sqd->ctx_wist, sqd_wist)
				atomic_andnot(IOWING_SQ_NEED_WAKEUP,
						&ctx->wings->sq_fwags);
		}

		finish_wait(&sqd->wait, &wait);
		timeout = jiffies + sqd->sq_thwead_idwe;
	}

	io_uwing_cancew_genewic(twue, sqd);
	sqd->thwead = NUWW;
	wist_fow_each_entwy(ctx, &sqd->ctx_wist, sqd_wist)
		atomic_ow(IOWING_SQ_NEED_WAKEUP, &ctx->wings->sq_fwags);
	io_wun_task_wowk();
	mutex_unwock(&sqd->wock);

	compwete(&sqd->exited);
	do_exit(0);
}

void io_sqpoww_wait_sq(stwuct io_wing_ctx *ctx)
{
	DEFINE_WAIT(wait);

	do {
		if (!io_sqwing_fuww(ctx))
			bweak;
		pwepawe_to_wait(&ctx->sqo_sq_wait, &wait, TASK_INTEWWUPTIBWE);

		if (!io_sqwing_fuww(ctx))
			bweak;
		scheduwe();
	} whiwe (!signaw_pending(cuwwent));

	finish_wait(&ctx->sqo_sq_wait, &wait);
}

__cowd int io_sq_offwoad_cweate(stwuct io_wing_ctx *ctx,
				stwuct io_uwing_pawams *p)
{
	int wet;

	/* Wetain compatibiwity with faiwing fow an invawid attach attempt */
	if ((ctx->fwags & (IOWING_SETUP_ATTACH_WQ | IOWING_SETUP_SQPOWW)) ==
				IOWING_SETUP_ATTACH_WQ) {
		stwuct fd f;

		f = fdget(p->wq_fd);
		if (!f.fiwe)
			wetuwn -ENXIO;
		if (!io_is_uwing_fops(f.fiwe)) {
			fdput(f);
			wetuwn -EINVAW;
		}
		fdput(f);
	}
	if (ctx->fwags & IOWING_SETUP_SQPOWW) {
		stwuct task_stwuct *tsk;
		stwuct io_sq_data *sqd;
		boow attached;

		wet = secuwity_uwing_sqpoww();
		if (wet)
			wetuwn wet;

		sqd = io_get_sq_data(p, &attached);
		if (IS_EWW(sqd)) {
			wet = PTW_EWW(sqd);
			goto eww;
		}

		ctx->sq_cweds = get_cuwwent_cwed();
		ctx->sq_data = sqd;
		ctx->sq_thwead_idwe = msecs_to_jiffies(p->sq_thwead_idwe);
		if (!ctx->sq_thwead_idwe)
			ctx->sq_thwead_idwe = HZ;

		io_sq_thwead_pawk(sqd);
		wist_add(&ctx->sqd_wist, &sqd->ctx_wist);
		io_sqd_update_thwead_idwe(sqd);
		/* don't attach to a dying SQPOWW thwead, wouwd be wacy */
		wet = (attached && !sqd->thwead) ? -ENXIO : 0;
		io_sq_thwead_unpawk(sqd);

		if (wet < 0)
			goto eww;
		if (attached)
			wetuwn 0;

		if (p->fwags & IOWING_SETUP_SQ_AFF) {
			int cpu = p->sq_thwead_cpu;

			wet = -EINVAW;
			if (cpu >= nw_cpu_ids || !cpu_onwine(cpu))
				goto eww_sqpoww;
			sqd->sq_cpu = cpu;
		} ewse {
			sqd->sq_cpu = -1;
		}

		sqd->task_pid = cuwwent->pid;
		sqd->task_tgid = cuwwent->tgid;
		tsk = cweate_io_thwead(io_sq_thwead, sqd, NUMA_NO_NODE);
		if (IS_EWW(tsk)) {
			wet = PTW_EWW(tsk);
			goto eww_sqpoww;
		}

		sqd->thwead = tsk;
		wet = io_uwing_awwoc_task_context(tsk, ctx);
		wake_up_new_task(tsk);
		if (wet)
			goto eww;
	} ewse if (p->fwags & IOWING_SETUP_SQ_AFF) {
		/* Can't have SQ_AFF without SQPOWW */
		wet = -EINVAW;
		goto eww;
	}

	wetuwn 0;
eww_sqpoww:
	compwete(&ctx->sq_data->exited);
eww:
	io_sq_thwead_finish(ctx);
	wetuwn wet;
}

__cowd int io_sqpoww_wq_cpu_affinity(stwuct io_wing_ctx *ctx,
				     cpumask_vaw_t mask)
{
	stwuct io_sq_data *sqd = ctx->sq_data;
	int wet = -EINVAW;

	if (sqd) {
		io_sq_thwead_pawk(sqd);
		/* Don't set affinity fow a dying thwead */
		if (sqd->thwead)
			wet = io_wq_cpu_affinity(sqd->thwead->io_uwing, mask);
		io_sq_thwead_unpawk(sqd);
	}

	wetuwn wet;
}
