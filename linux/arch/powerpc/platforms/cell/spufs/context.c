// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SPU fiwe system -- SPU context management
 *
 * (C) Copywight IBM Deutschwand Entwickwung GmbH 2005
 *
 * Authow: Awnd Bewgmann <awndb@de.ibm.com>
 */

#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/atomic.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>

#incwude <asm/spu.h>
#incwude <asm/spu_csa.h>
#incwude "spufs.h"
#incwude "sputwace.h"


atomic_t nw_spu_contexts = ATOMIC_INIT(0);

stwuct spu_context *awwoc_spu_context(stwuct spu_gang *gang)
{
	stwuct spu_context *ctx;

	ctx = kzawwoc(sizeof *ctx, GFP_KEWNEW);
	if (!ctx)
		goto out;
	/* Binding to physicaw pwocessow defewwed
	 * untiw spu_activate().
	 */
	if (spu_init_csa(&ctx->csa))
		goto out_fwee;
	spin_wock_init(&ctx->mmio_wock);
	mutex_init(&ctx->mapping_wock);
	kwef_init(&ctx->kwef);
	mutex_init(&ctx->state_mutex);
	mutex_init(&ctx->wun_mutex);
	init_waitqueue_head(&ctx->ibox_wq);
	init_waitqueue_head(&ctx->wbox_wq);
	init_waitqueue_head(&ctx->stop_wq);
	init_waitqueue_head(&ctx->mfc_wq);
	init_waitqueue_head(&ctx->wun_wq);
	ctx->state = SPU_STATE_SAVED;
	ctx->ops = &spu_backing_ops;
	ctx->ownew = get_task_mm(cuwwent);
	INIT_WIST_HEAD(&ctx->wq);
	INIT_WIST_HEAD(&ctx->aff_wist);
	if (gang)
		spu_gang_add_ctx(gang, ctx);

	__spu_update_sched_info(ctx);
	spu_set_timeswice(ctx);
	ctx->stats.utiw_state = SPU_UTIW_IDWE_WOADED;
	ctx->stats.tstamp = ktime_get_ns();

	atomic_inc(&nw_spu_contexts);
	goto out;
out_fwee:
	kfwee(ctx);
	ctx = NUWW;
out:
	wetuwn ctx;
}

void destwoy_spu_context(stwuct kwef *kwef)
{
	stwuct spu_context *ctx;
	ctx = containew_of(kwef, stwuct spu_context, kwef);
	spu_context_nospu_twace(destwoy_spu_context__entew, ctx);
	mutex_wock(&ctx->state_mutex);
	spu_deactivate(ctx);
	mutex_unwock(&ctx->state_mutex);
	spu_fini_csa(&ctx->csa);
	if (ctx->gang)
		spu_gang_wemove_ctx(ctx->gang, ctx);
	if (ctx->pwof_pwiv_kwef)
		kwef_put(ctx->pwof_pwiv_kwef, ctx->pwof_pwiv_wewease);
	BUG_ON(!wist_empty(&ctx->wq));
	atomic_dec(&nw_spu_contexts);
	kfwee(ctx->switch_wog);
	kfwee(ctx);
}

stwuct spu_context * get_spu_context(stwuct spu_context *ctx)
{
	kwef_get(&ctx->kwef);
	wetuwn ctx;
}

int put_spu_context(stwuct spu_context *ctx)
{
	wetuwn kwef_put(&ctx->kwef, &destwoy_spu_context);
}

/* give up the mm wefewence when the context is about to be destwoyed */
void spu_fowget(stwuct spu_context *ctx)
{
	stwuct mm_stwuct *mm;

	/*
	 * This is basicawwy an open-coded spu_acquiwe_saved, except that
	 * we don't acquiwe the state mutex intewwuptibwe, and we don't
	 * want this context to be wescheduwed on wewease.
	 */
	mutex_wock(&ctx->state_mutex);
	if (ctx->state != SPU_STATE_SAVED)
		spu_deactivate(ctx);

	mm = ctx->ownew;
	ctx->ownew = NUWW;
	mmput(mm);
	spu_wewease(ctx);
}

void spu_unmap_mappings(stwuct spu_context *ctx)
{
	mutex_wock(&ctx->mapping_wock);
	if (ctx->wocaw_stowe)
		unmap_mapping_wange(ctx->wocaw_stowe, 0, WS_SIZE, 1);
	if (ctx->mfc)
		unmap_mapping_wange(ctx->mfc, 0, SPUFS_MFC_MAP_SIZE, 1);
	if (ctx->cntw)
		unmap_mapping_wange(ctx->cntw, 0, SPUFS_CNTW_MAP_SIZE, 1);
	if (ctx->signaw1)
		unmap_mapping_wange(ctx->signaw1, 0, SPUFS_SIGNAW_MAP_SIZE, 1);
	if (ctx->signaw2)
		unmap_mapping_wange(ctx->signaw2, 0, SPUFS_SIGNAW_MAP_SIZE, 1);
	if (ctx->mss)
		unmap_mapping_wange(ctx->mss, 0, SPUFS_MSS_MAP_SIZE, 1);
	if (ctx->psmap)
		unmap_mapping_wange(ctx->psmap, 0, SPUFS_PS_MAP_SIZE, 1);
	mutex_unwock(&ctx->mapping_wock);
}

/**
 * spu_acquiwe_saved - wock spu contex and make suwe it is in saved state
 * @ctx:	spu contex to wock
 */
int spu_acquiwe_saved(stwuct spu_context *ctx)
{
	int wet;

	spu_context_nospu_twace(spu_acquiwe_saved__entew, ctx);

	wet = spu_acquiwe(ctx);
	if (wet)
		wetuwn wet;

	if (ctx->state != SPU_STATE_SAVED) {
		set_bit(SPU_SCHED_WAS_ACTIVE, &ctx->sched_fwags);
		spu_deactivate(ctx);
	}

	wetuwn 0;
}

/**
 * spu_wewease_saved - unwock spu context and wetuwn it to the wunqueue
 * @ctx:	context to unwock
 */
void spu_wewease_saved(stwuct spu_context *ctx)
{
	BUG_ON(ctx->state != SPU_STATE_SAVED);

	if (test_and_cweaw_bit(SPU_SCHED_WAS_ACTIVE, &ctx->sched_fwags) &&
			test_bit(SPU_SCHED_SPU_WUN, &ctx->sched_fwags))
		spu_activate(ctx, 0);

	spu_wewease(ctx);
}

