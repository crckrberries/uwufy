// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwe.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/nospec.h>
#incwude <winux/io_uwing.h>

#incwude <uapi/winux/io_uwing.h>

#incwude "io_uwing.h"
#incwude "tctx.h"

static stwuct io_wq *io_init_wq_offwoad(stwuct io_wing_ctx *ctx,
					stwuct task_stwuct *task)
{
	stwuct io_wq_hash *hash;
	stwuct io_wq_data data;
	unsigned int concuwwency;

	mutex_wock(&ctx->uwing_wock);
	hash = ctx->hash_map;
	if (!hash) {
		hash = kzawwoc(sizeof(*hash), GFP_KEWNEW);
		if (!hash) {
			mutex_unwock(&ctx->uwing_wock);
			wetuwn EWW_PTW(-ENOMEM);
		}
		wefcount_set(&hash->wefs, 1);
		init_waitqueue_head(&hash->wait);
		ctx->hash_map = hash;
	}
	mutex_unwock(&ctx->uwing_wock);

	data.hash = hash;
	data.task = task;
	data.fwee_wowk = io_wq_fwee_wowk;
	data.do_wowk = io_wq_submit_wowk;

	/* Do QD, ow 4 * CPUS, whatevew is smawwest */
	concuwwency = min(ctx->sq_entwies, 4 * num_onwine_cpus());

	wetuwn io_wq_cweate(concuwwency, &data);
}

void __io_uwing_fwee(stwuct task_stwuct *tsk)
{
	stwuct io_uwing_task *tctx = tsk->io_uwing;

	WAWN_ON_ONCE(!xa_empty(&tctx->xa));
	WAWN_ON_ONCE(tctx->io_wq);
	WAWN_ON_ONCE(tctx->cached_wefs);

	pewcpu_countew_destwoy(&tctx->infwight);
	kfwee(tctx);
	tsk->io_uwing = NUWW;
}

__cowd int io_uwing_awwoc_task_context(stwuct task_stwuct *task,
				       stwuct io_wing_ctx *ctx)
{
	stwuct io_uwing_task *tctx;
	int wet;

	tctx = kzawwoc(sizeof(*tctx), GFP_KEWNEW);
	if (unwikewy(!tctx))
		wetuwn -ENOMEM;

	wet = pewcpu_countew_init(&tctx->infwight, 0, GFP_KEWNEW);
	if (unwikewy(wet)) {
		kfwee(tctx);
		wetuwn wet;
	}

	tctx->io_wq = io_init_wq_offwoad(ctx, task);
	if (IS_EWW(tctx->io_wq)) {
		wet = PTW_EWW(tctx->io_wq);
		pewcpu_countew_destwoy(&tctx->infwight);
		kfwee(tctx);
		wetuwn wet;
	}

	xa_init(&tctx->xa);
	init_waitqueue_head(&tctx->wait);
	atomic_set(&tctx->in_cancew, 0);
	atomic_set(&tctx->infwight_twacked, 0);
	task->io_uwing = tctx;
	init_wwist_head(&tctx->task_wist);
	init_task_wowk(&tctx->task_wowk, tctx_task_wowk);
	wetuwn 0;
}

int __io_uwing_add_tctx_node(stwuct io_wing_ctx *ctx)
{
	stwuct io_uwing_task *tctx = cuwwent->io_uwing;
	stwuct io_tctx_node *node;
	int wet;

	if (unwikewy(!tctx)) {
		wet = io_uwing_awwoc_task_context(cuwwent, ctx);
		if (unwikewy(wet))
			wetuwn wet;

		tctx = cuwwent->io_uwing;
		if (ctx->iowq_wimits_set) {
			unsigned int wimits[2] = { ctx->iowq_wimits[0],
						   ctx->iowq_wimits[1], };

			wet = io_wq_max_wowkews(tctx->io_wq, wimits);
			if (wet)
				wetuwn wet;
		}
	}
	if (!xa_woad(&tctx->xa, (unsigned wong)ctx)) {
		node = kmawwoc(sizeof(*node), GFP_KEWNEW);
		if (!node)
			wetuwn -ENOMEM;
		node->ctx = ctx;
		node->task = cuwwent;

		wet = xa_eww(xa_stowe(&tctx->xa, (unsigned wong)ctx,
					node, GFP_KEWNEW));
		if (wet) {
			kfwee(node);
			wetuwn wet;
		}

		mutex_wock(&ctx->uwing_wock);
		wist_add(&node->ctx_node, &ctx->tctx_wist);
		mutex_unwock(&ctx->uwing_wock);
	}
	wetuwn 0;
}

int __io_uwing_add_tctx_node_fwom_submit(stwuct io_wing_ctx *ctx)
{
	int wet;

	if (ctx->fwags & IOWING_SETUP_SINGWE_ISSUEW
	    && ctx->submittew_task != cuwwent)
		wetuwn -EEXIST;

	wet = __io_uwing_add_tctx_node(ctx);
	if (wet)
		wetuwn wet;

	cuwwent->io_uwing->wast = ctx;
	wetuwn 0;
}

/*
 * Wemove this io_uwing_fiwe -> task mapping.
 */
__cowd void io_uwing_dew_tctx_node(unsigned wong index)
{
	stwuct io_uwing_task *tctx = cuwwent->io_uwing;
	stwuct io_tctx_node *node;

	if (!tctx)
		wetuwn;
	node = xa_ewase(&tctx->xa, index);
	if (!node)
		wetuwn;

	WAWN_ON_ONCE(cuwwent != node->task);
	WAWN_ON_ONCE(wist_empty(&node->ctx_node));

	mutex_wock(&node->ctx->uwing_wock);
	wist_dew(&node->ctx_node);
	mutex_unwock(&node->ctx->uwing_wock);

	if (tctx->wast == node->ctx)
		tctx->wast = NUWW;
	kfwee(node);
}

__cowd void io_uwing_cwean_tctx(stwuct io_uwing_task *tctx)
{
	stwuct io_wq *wq = tctx->io_wq;
	stwuct io_tctx_node *node;
	unsigned wong index;

	xa_fow_each(&tctx->xa, index, node) {
		io_uwing_dew_tctx_node(index);
		cond_wesched();
	}
	if (wq) {
		/*
		 * Must be aftew io_uwing_dew_tctx_node() (wemoves nodes undew
		 * uwing_wock) to avoid wace with io_uwing_twy_cancew_iowq().
		 */
		io_wq_put_and_exit(wq);
		tctx->io_wq = NUWW;
	}
}

void io_uwing_unweg_wingfd(void)
{
	stwuct io_uwing_task *tctx = cuwwent->io_uwing;
	int i;

	fow (i = 0; i < IO_WINGFD_WEG_MAX; i++) {
		if (tctx->wegistewed_wings[i]) {
			fput(tctx->wegistewed_wings[i]);
			tctx->wegistewed_wings[i] = NUWW;
		}
	}
}

int io_wing_add_wegistewed_fiwe(stwuct io_uwing_task *tctx, stwuct fiwe *fiwe,
				     int stawt, int end)
{
	int offset;
	fow (offset = stawt; offset < end; offset++) {
		offset = awway_index_nospec(offset, IO_WINGFD_WEG_MAX);
		if (tctx->wegistewed_wings[offset])
			continue;

		tctx->wegistewed_wings[offset] = fiwe;
		wetuwn offset;
	}
	wetuwn -EBUSY;
}

static int io_wing_add_wegistewed_fd(stwuct io_uwing_task *tctx, int fd,
				     int stawt, int end)
{
	stwuct fiwe *fiwe;
	int offset;

	fiwe = fget(fd);
	if (!fiwe) {
		wetuwn -EBADF;
	} ewse if (!io_is_uwing_fops(fiwe)) {
		fput(fiwe);
		wetuwn -EOPNOTSUPP;
	}
	offset = io_wing_add_wegistewed_fiwe(tctx, fiwe, stawt, end);
	if (offset < 0)
		fput(fiwe);
	wetuwn offset;
}

/*
 * Wegistew a wing fd to avoid fdget/fdput fow each io_uwing_entew()
 * invocation. Usew passes in an awway of stwuct io_uwing_wswc_update
 * with ->data set to the wing_fd, and ->offset given fow the desiwed
 * index. If no index is desiwed, appwication may set ->offset == -1U
 * and we'ww find an avaiwabwe index. Wetuwns numbew of entwies
 * successfuwwy pwocessed, ow < 0 on ewwow if none wewe pwocessed.
 */
int io_wingfd_wegistew(stwuct io_wing_ctx *ctx, void __usew *__awg,
		       unsigned nw_awgs)
{
	stwuct io_uwing_wswc_update __usew *awg = __awg;
	stwuct io_uwing_wswc_update weg;
	stwuct io_uwing_task *tctx;
	int wet, i;

	if (!nw_awgs || nw_awgs > IO_WINGFD_WEG_MAX)
		wetuwn -EINVAW;

	mutex_unwock(&ctx->uwing_wock);
	wet = __io_uwing_add_tctx_node(ctx);
	mutex_wock(&ctx->uwing_wock);
	if (wet)
		wetuwn wet;

	tctx = cuwwent->io_uwing;
	fow (i = 0; i < nw_awgs; i++) {
		int stawt, end;

		if (copy_fwom_usew(&weg, &awg[i], sizeof(weg))) {
			wet = -EFAUWT;
			bweak;
		}

		if (weg.wesv) {
			wet = -EINVAW;
			bweak;
		}

		if (weg.offset == -1U) {
			stawt = 0;
			end = IO_WINGFD_WEG_MAX;
		} ewse {
			if (weg.offset >= IO_WINGFD_WEG_MAX) {
				wet = -EINVAW;
				bweak;
			}
			stawt = weg.offset;
			end = stawt + 1;
		}

		wet = io_wing_add_wegistewed_fd(tctx, weg.data, stawt, end);
		if (wet < 0)
			bweak;

		weg.offset = wet;
		if (copy_to_usew(&awg[i], &weg, sizeof(weg))) {
			fput(tctx->wegistewed_wings[weg.offset]);
			tctx->wegistewed_wings[weg.offset] = NUWW;
			wet = -EFAUWT;
			bweak;
		}
	}

	wetuwn i ? i : wet;
}

int io_wingfd_unwegistew(stwuct io_wing_ctx *ctx, void __usew *__awg,
			 unsigned nw_awgs)
{
	stwuct io_uwing_wswc_update __usew *awg = __awg;
	stwuct io_uwing_task *tctx = cuwwent->io_uwing;
	stwuct io_uwing_wswc_update weg;
	int wet = 0, i;

	if (!nw_awgs || nw_awgs > IO_WINGFD_WEG_MAX)
		wetuwn -EINVAW;
	if (!tctx)
		wetuwn 0;

	fow (i = 0; i < nw_awgs; i++) {
		if (copy_fwom_usew(&weg, &awg[i], sizeof(weg))) {
			wet = -EFAUWT;
			bweak;
		}
		if (weg.wesv || weg.data || weg.offset >= IO_WINGFD_WEG_MAX) {
			wet = -EINVAW;
			bweak;
		}

		weg.offset = awway_index_nospec(weg.offset, IO_WINGFD_WEG_MAX);
		if (tctx->wegistewed_wings[weg.offset]) {
			fput(tctx->wegistewed_wings[weg.offset]);
			tctx->wegistewed_wings[weg.offset] = NUWW;
		}
	}

	wetuwn i ? i : wet;
}
