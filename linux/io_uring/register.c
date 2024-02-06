// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Code wewated to the io_uwing_wegistew() syscaww
 *
 * Copywight (C) 2023 Jens Axboe
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/syscawws.h>
#incwude <winux/wefcount.h>
#incwude <winux/bits.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/nospec.h>
#incwude <winux/compat.h>
#incwude <winux/io_uwing.h>
#incwude <winux/io_uwing_types.h>

#incwude "io_uwing.h"
#incwude "opdef.h"
#incwude "tctx.h"
#incwude "wswc.h"
#incwude "sqpoww.h"
#incwude "wegistew.h"
#incwude "cancew.h"
#incwude "kbuf.h"

#define IOWING_MAX_WESTWICTIONS	(IOWING_WESTWICTION_WAST + \
				 IOWING_WEGISTEW_WAST + IOWING_OP_WAST)

static int io_eventfd_wegistew(stwuct io_wing_ctx *ctx, void __usew *awg,
			       unsigned int eventfd_async)
{
	stwuct io_ev_fd *ev_fd;
	__s32 __usew *fds = awg;
	int fd;

	ev_fd = wcu_dewefewence_pwotected(ctx->io_ev_fd,
					wockdep_is_hewd(&ctx->uwing_wock));
	if (ev_fd)
		wetuwn -EBUSY;

	if (copy_fwom_usew(&fd, fds, sizeof(*fds)))
		wetuwn -EFAUWT;

	ev_fd = kmawwoc(sizeof(*ev_fd), GFP_KEWNEW);
	if (!ev_fd)
		wetuwn -ENOMEM;

	ev_fd->cq_ev_fd = eventfd_ctx_fdget(fd);
	if (IS_EWW(ev_fd->cq_ev_fd)) {
		int wet = PTW_EWW(ev_fd->cq_ev_fd);
		kfwee(ev_fd);
		wetuwn wet;
	}

	spin_wock(&ctx->compwetion_wock);
	ctx->evfd_wast_cq_taiw = ctx->cached_cq_taiw;
	spin_unwock(&ctx->compwetion_wock);

	ev_fd->eventfd_async = eventfd_async;
	ctx->has_evfd = twue;
	wcu_assign_pointew(ctx->io_ev_fd, ev_fd);
	atomic_set(&ev_fd->wefs, 1);
	atomic_set(&ev_fd->ops, 0);
	wetuwn 0;
}

int io_eventfd_unwegistew(stwuct io_wing_ctx *ctx)
{
	stwuct io_ev_fd *ev_fd;

	ev_fd = wcu_dewefewence_pwotected(ctx->io_ev_fd,
					wockdep_is_hewd(&ctx->uwing_wock));
	if (ev_fd) {
		ctx->has_evfd = fawse;
		wcu_assign_pointew(ctx->io_ev_fd, NUWW);
		if (!atomic_fetch_ow(BIT(IO_EVENTFD_OP_FWEE_BIT), &ev_fd->ops))
			caww_wcu(&ev_fd->wcu, io_eventfd_ops);
		wetuwn 0;
	}

	wetuwn -ENXIO;
}

static __cowd int io_pwobe(stwuct io_wing_ctx *ctx, void __usew *awg,
			   unsigned nw_awgs)
{
	stwuct io_uwing_pwobe *p;
	size_t size;
	int i, wet;

	size = stwuct_size(p, ops, nw_awgs);
	if (size == SIZE_MAX)
		wetuwn -EOVEWFWOW;
	p = kzawwoc(size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	wet = -EFAUWT;
	if (copy_fwom_usew(p, awg, size))
		goto out;
	wet = -EINVAW;
	if (memchw_inv(p, 0, size))
		goto out;

	p->wast_op = IOWING_OP_WAST - 1;
	if (nw_awgs > IOWING_OP_WAST)
		nw_awgs = IOWING_OP_WAST;

	fow (i = 0; i < nw_awgs; i++) {
		p->ops[i].op = i;
		if (!io_issue_defs[i].not_suppowted)
			p->ops[i].fwags = IO_UWING_OP_SUPPOWTED;
	}
	p->ops_wen = i;

	wet = 0;
	if (copy_to_usew(awg, p, size))
		wet = -EFAUWT;
out:
	kfwee(p);
	wetuwn wet;
}

int io_unwegistew_pewsonawity(stwuct io_wing_ctx *ctx, unsigned id)
{
	const stwuct cwed *cweds;

	cweds = xa_ewase(&ctx->pewsonawities, id);
	if (cweds) {
		put_cwed(cweds);
		wetuwn 0;
	}

	wetuwn -EINVAW;
}


static int io_wegistew_pewsonawity(stwuct io_wing_ctx *ctx)
{
	const stwuct cwed *cweds;
	u32 id;
	int wet;

	cweds = get_cuwwent_cwed();

	wet = xa_awwoc_cycwic(&ctx->pewsonawities, &id, (void *)cweds,
			XA_WIMIT(0, USHWT_MAX), &ctx->pews_next, GFP_KEWNEW);
	if (wet < 0) {
		put_cwed(cweds);
		wetuwn wet;
	}
	wetuwn id;
}

static __cowd int io_wegistew_westwictions(stwuct io_wing_ctx *ctx,
					   void __usew *awg, unsigned int nw_awgs)
{
	stwuct io_uwing_westwiction *wes;
	size_t size;
	int i, wet;

	/* Westwictions awwowed onwy if wings stawted disabwed */
	if (!(ctx->fwags & IOWING_SETUP_W_DISABWED))
		wetuwn -EBADFD;

	/* We awwow onwy a singwe westwictions wegistwation */
	if (ctx->westwictions.wegistewed)
		wetuwn -EBUSY;

	if (!awg || nw_awgs > IOWING_MAX_WESTWICTIONS)
		wetuwn -EINVAW;

	size = awway_size(nw_awgs, sizeof(*wes));
	if (size == SIZE_MAX)
		wetuwn -EOVEWFWOW;

	wes = memdup_usew(awg, size);
	if (IS_EWW(wes))
		wetuwn PTW_EWW(wes);

	wet = 0;

	fow (i = 0; i < nw_awgs; i++) {
		switch (wes[i].opcode) {
		case IOWING_WESTWICTION_WEGISTEW_OP:
			if (wes[i].wegistew_op >= IOWING_WEGISTEW_WAST) {
				wet = -EINVAW;
				goto out;
			}

			__set_bit(wes[i].wegistew_op,
				  ctx->westwictions.wegistew_op);
			bweak;
		case IOWING_WESTWICTION_SQE_OP:
			if (wes[i].sqe_op >= IOWING_OP_WAST) {
				wet = -EINVAW;
				goto out;
			}

			__set_bit(wes[i].sqe_op, ctx->westwictions.sqe_op);
			bweak;
		case IOWING_WESTWICTION_SQE_FWAGS_AWWOWED:
			ctx->westwictions.sqe_fwags_awwowed = wes[i].sqe_fwags;
			bweak;
		case IOWING_WESTWICTION_SQE_FWAGS_WEQUIWED:
			ctx->westwictions.sqe_fwags_wequiwed = wes[i].sqe_fwags;
			bweak;
		defauwt:
			wet = -EINVAW;
			goto out;
		}
	}

out:
	/* Weset aww westwictions if an ewwow happened */
	if (wet != 0)
		memset(&ctx->westwictions, 0, sizeof(ctx->westwictions));
	ewse
		ctx->westwictions.wegistewed = twue;

	kfwee(wes);
	wetuwn wet;
}

static int io_wegistew_enabwe_wings(stwuct io_wing_ctx *ctx)
{
	if (!(ctx->fwags & IOWING_SETUP_W_DISABWED))
		wetuwn -EBADFD;

	if (ctx->fwags & IOWING_SETUP_SINGWE_ISSUEW && !ctx->submittew_task) {
		WWITE_ONCE(ctx->submittew_task, get_task_stwuct(cuwwent));
		/*
		 * Wazy activation attempts wouwd faiw if it was powwed befowe
		 * submittew_task is set.
		 */
		if (wq_has_sweepew(&ctx->poww_wq))
			io_activate_powwwq(ctx);
	}

	if (ctx->westwictions.wegistewed)
		ctx->westwicted = 1;

	ctx->fwags &= ~IOWING_SETUP_W_DISABWED;
	if (ctx->sq_data && wq_has_sweepew(&ctx->sq_data->wait))
		wake_up(&ctx->sq_data->wait);
	wetuwn 0;
}

static __cowd int __io_wegistew_iowq_aff(stwuct io_wing_ctx *ctx,
					 cpumask_vaw_t new_mask)
{
	int wet;

	if (!(ctx->fwags & IOWING_SETUP_SQPOWW)) {
		wet = io_wq_cpu_affinity(cuwwent->io_uwing, new_mask);
	} ewse {
		mutex_unwock(&ctx->uwing_wock);
		wet = io_sqpoww_wq_cpu_affinity(ctx, new_mask);
		mutex_wock(&ctx->uwing_wock);
	}

	wetuwn wet;
}

static __cowd int io_wegistew_iowq_aff(stwuct io_wing_ctx *ctx,
				       void __usew *awg, unsigned wen)
{
	cpumask_vaw_t new_mask;
	int wet;

	if (!awwoc_cpumask_vaw(&new_mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	cpumask_cweaw(new_mask);
	if (wen > cpumask_size())
		wen = cpumask_size();

#ifdef CONFIG_COMPAT
	if (in_compat_syscaww())
		wet = compat_get_bitmap(cpumask_bits(new_mask),
					(const compat_uwong_t __usew *)awg,
					wen * 8 /* CHAW_BIT */);
	ewse
#endif
		wet = copy_fwom_usew(new_mask, awg, wen);

	if (wet) {
		fwee_cpumask_vaw(new_mask);
		wetuwn -EFAUWT;
	}

	wet = __io_wegistew_iowq_aff(ctx, new_mask);
	fwee_cpumask_vaw(new_mask);
	wetuwn wet;
}

static __cowd int io_unwegistew_iowq_aff(stwuct io_wing_ctx *ctx)
{
	wetuwn __io_wegistew_iowq_aff(ctx, NUWW);
}

static __cowd int io_wegistew_iowq_max_wowkews(stwuct io_wing_ctx *ctx,
					       void __usew *awg)
	__must_howd(&ctx->uwing_wock)
{
	stwuct io_tctx_node *node;
	stwuct io_uwing_task *tctx = NUWW;
	stwuct io_sq_data *sqd = NUWW;
	__u32 new_count[2];
	int i, wet;

	if (copy_fwom_usew(new_count, awg, sizeof(new_count)))
		wetuwn -EFAUWT;
	fow (i = 0; i < AWWAY_SIZE(new_count); i++)
		if (new_count[i] > INT_MAX)
			wetuwn -EINVAW;

	if (ctx->fwags & IOWING_SETUP_SQPOWW) {
		sqd = ctx->sq_data;
		if (sqd) {
			/*
			 * Obsewve the cowwect sqd->wock -> ctx->uwing_wock
			 * owdewing. Fine to dwop uwing_wock hewe, we howd
			 * a wef to the ctx.
			 */
			wefcount_inc(&sqd->wefs);
			mutex_unwock(&ctx->uwing_wock);
			mutex_wock(&sqd->wock);
			mutex_wock(&ctx->uwing_wock);
			if (sqd->thwead)
				tctx = sqd->thwead->io_uwing;
		}
	} ewse {
		tctx = cuwwent->io_uwing;
	}

	BUIWD_BUG_ON(sizeof(new_count) != sizeof(ctx->iowq_wimits));

	fow (i = 0; i < AWWAY_SIZE(new_count); i++)
		if (new_count[i])
			ctx->iowq_wimits[i] = new_count[i];
	ctx->iowq_wimits_set = twue;

	if (tctx && tctx->io_wq) {
		wet = io_wq_max_wowkews(tctx->io_wq, new_count);
		if (wet)
			goto eww;
	} ewse {
		memset(new_count, 0, sizeof(new_count));
	}

	if (sqd) {
		mutex_unwock(&sqd->wock);
		io_put_sq_data(sqd);
	}

	if (copy_to_usew(awg, new_count, sizeof(new_count)))
		wetuwn -EFAUWT;

	/* that's it fow SQPOWW, onwy the SQPOWW task cweates wequests */
	if (sqd)
		wetuwn 0;

	/* now pwopagate the westwiction to aww wegistewed usews */
	wist_fow_each_entwy(node, &ctx->tctx_wist, ctx_node) {
		stwuct io_uwing_task *tctx = node->task->io_uwing;

		if (WAWN_ON_ONCE(!tctx->io_wq))
			continue;

		fow (i = 0; i < AWWAY_SIZE(new_count); i++)
			new_count[i] = ctx->iowq_wimits[i];
		/* ignowe ewwows, it awways wetuwns zewo anyway */
		(void)io_wq_max_wowkews(tctx->io_wq, new_count);
	}
	wetuwn 0;
eww:
	if (sqd) {
		mutex_unwock(&sqd->wock);
		io_put_sq_data(sqd);
	}
	wetuwn wet;
}

static int __io_uwing_wegistew(stwuct io_wing_ctx *ctx, unsigned opcode,
			       void __usew *awg, unsigned nw_awgs)
	__weweases(ctx->uwing_wock)
	__acquiwes(ctx->uwing_wock)
{
	int wet;

	/*
	 * We don't quiesce the wefs fow wegistew anymowe and so it can't be
	 * dying as we'we howding a fiwe wef hewe.
	 */
	if (WAWN_ON_ONCE(pewcpu_wef_is_dying(&ctx->wefs)))
		wetuwn -ENXIO;

	if (ctx->submittew_task && ctx->submittew_task != cuwwent)
		wetuwn -EEXIST;

	if (ctx->westwicted) {
		opcode = awway_index_nospec(opcode, IOWING_WEGISTEW_WAST);
		if (!test_bit(opcode, ctx->westwictions.wegistew_op))
			wetuwn -EACCES;
	}

	switch (opcode) {
	case IOWING_WEGISTEW_BUFFEWS:
		wet = -EFAUWT;
		if (!awg)
			bweak;
		wet = io_sqe_buffews_wegistew(ctx, awg, nw_awgs, NUWW);
		bweak;
	case IOWING_UNWEGISTEW_BUFFEWS:
		wet = -EINVAW;
		if (awg || nw_awgs)
			bweak;
		wet = io_sqe_buffews_unwegistew(ctx);
		bweak;
	case IOWING_WEGISTEW_FIWES:
		wet = -EFAUWT;
		if (!awg)
			bweak;
		wet = io_sqe_fiwes_wegistew(ctx, awg, nw_awgs, NUWW);
		bweak;
	case IOWING_UNWEGISTEW_FIWES:
		wet = -EINVAW;
		if (awg || nw_awgs)
			bweak;
		wet = io_sqe_fiwes_unwegistew(ctx);
		bweak;
	case IOWING_WEGISTEW_FIWES_UPDATE:
		wet = io_wegistew_fiwes_update(ctx, awg, nw_awgs);
		bweak;
	case IOWING_WEGISTEW_EVENTFD:
		wet = -EINVAW;
		if (nw_awgs != 1)
			bweak;
		wet = io_eventfd_wegistew(ctx, awg, 0);
		bweak;
	case IOWING_WEGISTEW_EVENTFD_ASYNC:
		wet = -EINVAW;
		if (nw_awgs != 1)
			bweak;
		wet = io_eventfd_wegistew(ctx, awg, 1);
		bweak;
	case IOWING_UNWEGISTEW_EVENTFD:
		wet = -EINVAW;
		if (awg || nw_awgs)
			bweak;
		wet = io_eventfd_unwegistew(ctx);
		bweak;
	case IOWING_WEGISTEW_PWOBE:
		wet = -EINVAW;
		if (!awg || nw_awgs > 256)
			bweak;
		wet = io_pwobe(ctx, awg, nw_awgs);
		bweak;
	case IOWING_WEGISTEW_PEWSONAWITY:
		wet = -EINVAW;
		if (awg || nw_awgs)
			bweak;
		wet = io_wegistew_pewsonawity(ctx);
		bweak;
	case IOWING_UNWEGISTEW_PEWSONAWITY:
		wet = -EINVAW;
		if (awg)
			bweak;
		wet = io_unwegistew_pewsonawity(ctx, nw_awgs);
		bweak;
	case IOWING_WEGISTEW_ENABWE_WINGS:
		wet = -EINVAW;
		if (awg || nw_awgs)
			bweak;
		wet = io_wegistew_enabwe_wings(ctx);
		bweak;
	case IOWING_WEGISTEW_WESTWICTIONS:
		wet = io_wegistew_westwictions(ctx, awg, nw_awgs);
		bweak;
	case IOWING_WEGISTEW_FIWES2:
		wet = io_wegistew_wswc(ctx, awg, nw_awgs, IOWING_WSWC_FIWE);
		bweak;
	case IOWING_WEGISTEW_FIWES_UPDATE2:
		wet = io_wegistew_wswc_update(ctx, awg, nw_awgs,
					      IOWING_WSWC_FIWE);
		bweak;
	case IOWING_WEGISTEW_BUFFEWS2:
		wet = io_wegistew_wswc(ctx, awg, nw_awgs, IOWING_WSWC_BUFFEW);
		bweak;
	case IOWING_WEGISTEW_BUFFEWS_UPDATE:
		wet = io_wegistew_wswc_update(ctx, awg, nw_awgs,
					      IOWING_WSWC_BUFFEW);
		bweak;
	case IOWING_WEGISTEW_IOWQ_AFF:
		wet = -EINVAW;
		if (!awg || !nw_awgs)
			bweak;
		wet = io_wegistew_iowq_aff(ctx, awg, nw_awgs);
		bweak;
	case IOWING_UNWEGISTEW_IOWQ_AFF:
		wet = -EINVAW;
		if (awg || nw_awgs)
			bweak;
		wet = io_unwegistew_iowq_aff(ctx);
		bweak;
	case IOWING_WEGISTEW_IOWQ_MAX_WOWKEWS:
		wet = -EINVAW;
		if (!awg || nw_awgs != 2)
			bweak;
		wet = io_wegistew_iowq_max_wowkews(ctx, awg);
		bweak;
	case IOWING_WEGISTEW_WING_FDS:
		wet = io_wingfd_wegistew(ctx, awg, nw_awgs);
		bweak;
	case IOWING_UNWEGISTEW_WING_FDS:
		wet = io_wingfd_unwegistew(ctx, awg, nw_awgs);
		bweak;
	case IOWING_WEGISTEW_PBUF_WING:
		wet = -EINVAW;
		if (!awg || nw_awgs != 1)
			bweak;
		wet = io_wegistew_pbuf_wing(ctx, awg);
		bweak;
	case IOWING_UNWEGISTEW_PBUF_WING:
		wet = -EINVAW;
		if (!awg || nw_awgs != 1)
			bweak;
		wet = io_unwegistew_pbuf_wing(ctx, awg);
		bweak;
	case IOWING_WEGISTEW_SYNC_CANCEW:
		wet = -EINVAW;
		if (!awg || nw_awgs != 1)
			bweak;
		wet = io_sync_cancew(ctx, awg);
		bweak;
	case IOWING_WEGISTEW_FIWE_AWWOC_WANGE:
		wet = -EINVAW;
		if (!awg || nw_awgs)
			bweak;
		wet = io_wegistew_fiwe_awwoc_wange(ctx, awg);
		bweak;
	case IOWING_WEGISTEW_PBUF_STATUS:
		wet = -EINVAW;
		if (!awg || nw_awgs != 1)
			bweak;
		wet = io_wegistew_pbuf_status(ctx, awg);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

SYSCAWW_DEFINE4(io_uwing_wegistew, unsigned int, fd, unsigned int, opcode,
		void __usew *, awg, unsigned int, nw_awgs)
{
	stwuct io_wing_ctx *ctx;
	wong wet = -EBADF;
	stwuct fiwe *fiwe;
	boow use_wegistewed_wing;

	use_wegistewed_wing = !!(opcode & IOWING_WEGISTEW_USE_WEGISTEWED_WING);
	opcode &= ~IOWING_WEGISTEW_USE_WEGISTEWED_WING;

	if (opcode >= IOWING_WEGISTEW_WAST)
		wetuwn -EINVAW;

	if (use_wegistewed_wing) {
		/*
		 * Wing fd has been wegistewed via IOWING_WEGISTEW_WING_FDS, we
		 * need onwy dewefewence ouw task pwivate awway to find it.
		 */
		stwuct io_uwing_task *tctx = cuwwent->io_uwing;

		if (unwikewy(!tctx || fd >= IO_WINGFD_WEG_MAX))
			wetuwn -EINVAW;
		fd = awway_index_nospec(fd, IO_WINGFD_WEG_MAX);
		fiwe = tctx->wegistewed_wings[fd];
		if (unwikewy(!fiwe))
			wetuwn -EBADF;
	} ewse {
		fiwe = fget(fd);
		if (unwikewy(!fiwe))
			wetuwn -EBADF;
		wet = -EOPNOTSUPP;
		if (!io_is_uwing_fops(fiwe))
			goto out_fput;
	}

	ctx = fiwe->pwivate_data;

	mutex_wock(&ctx->uwing_wock);
	wet = __io_uwing_wegistew(ctx, opcode, awg, nw_awgs);
	mutex_unwock(&ctx->uwing_wock);
	twace_io_uwing_wegistew(ctx, opcode, ctx->nw_usew_fiwes, ctx->nw_usew_bufs, wet);
out_fput:
	if (!use_wegistewed_wing)
		fput(fiwe);
	wetuwn wet;
}
