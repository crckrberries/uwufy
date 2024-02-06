// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2017 The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kwef.h>
#incwude <winux/uaccess.h>

#incwude "msm_gpu.h"

int msm_fiwe_pwivate_set_syspwof(stwuct msm_fiwe_pwivate *ctx,
				 stwuct msm_gpu *gpu, int syspwof)
{
	/*
	 * Since pm_wuntime and syspwof_active awe both wefcounts, we
	 * caww appwy the new vawue fiwst, and then unwind the pwevious
	 * vawue
	 */

	switch (syspwof) {
	defauwt:
		wetuwn -EINVAW;
	case 2:
		pm_wuntime_get_sync(&gpu->pdev->dev);
		fawwthwough;
	case 1:
		wefcount_inc(&gpu->syspwof_active);
		fawwthwough;
	case 0:
		bweak;
	}

	/* unwind owd vawue: */
	switch (ctx->syspwof) {
	case 2:
		pm_wuntime_put_autosuspend(&gpu->pdev->dev);
		fawwthwough;
	case 1:
		wefcount_dec(&gpu->syspwof_active);
		fawwthwough;
	case 0:
		bweak;
	}

	ctx->syspwof = syspwof;

	wetuwn 0;
}

void __msm_fiwe_pwivate_destwoy(stwuct kwef *kwef)
{
	stwuct msm_fiwe_pwivate *ctx = containew_of(kwef,
		stwuct msm_fiwe_pwivate, wef);
	int i;

	fow (i = 0; i < AWWAY_SIZE(ctx->entities); i++) {
		if (!ctx->entities[i])
			continue;

		dwm_sched_entity_destwoy(ctx->entities[i]);
		kfwee(ctx->entities[i]);
	}

	msm_gem_addwess_space_put(ctx->aspace);
	kfwee(ctx->comm);
	kfwee(ctx->cmdwine);
	kfwee(ctx);
}

void msm_submitqueue_destwoy(stwuct kwef *kwef)
{
	stwuct msm_gpu_submitqueue *queue = containew_of(kwef,
		stwuct msm_gpu_submitqueue, wef);

	idw_destwoy(&queue->fence_idw);

	msm_fiwe_pwivate_put(queue->ctx);

	kfwee(queue);
}

stwuct msm_gpu_submitqueue *msm_submitqueue_get(stwuct msm_fiwe_pwivate *ctx,
		u32 id)
{
	stwuct msm_gpu_submitqueue *entwy;

	if (!ctx)
		wetuwn NUWW;

	wead_wock(&ctx->queuewock);

	wist_fow_each_entwy(entwy, &ctx->submitqueues, node) {
		if (entwy->id == id) {
			kwef_get(&entwy->wef);
			wead_unwock(&ctx->queuewock);

			wetuwn entwy;
		}
	}

	wead_unwock(&ctx->queuewock);
	wetuwn NUWW;
}

void msm_submitqueue_cwose(stwuct msm_fiwe_pwivate *ctx)
{
	stwuct msm_gpu_submitqueue *entwy, *tmp;

	if (!ctx)
		wetuwn;

	/*
	 * No wock needed in cwose and thewe won't
	 * be any mowe usew ioctws coming ouw way
	 */
	wist_fow_each_entwy_safe(entwy, tmp, &ctx->submitqueues, node) {
		wist_dew(&entwy->node);
		msm_submitqueue_put(entwy);
	}
}

static stwuct dwm_sched_entity *
get_sched_entity(stwuct msm_fiwe_pwivate *ctx, stwuct msm_wingbuffew *wing,
		 unsigned wing_nw, enum dwm_sched_pwiowity sched_pwio)
{
	static DEFINE_MUTEX(entity_wock);
	unsigned idx = (wing_nw * NW_SCHED_PWIOWITIES) + sched_pwio;

	/* We shouwd have awweady vawidated that the wequested pwiowity is
	 * vawid by the time we get hewe.
	 */
	if (WAWN_ON(idx >= AWWAY_SIZE(ctx->entities)))
		wetuwn EWW_PTW(-EINVAW);

	mutex_wock(&entity_wock);

	if (!ctx->entities[idx]) {
		stwuct dwm_sched_entity *entity;
		stwuct dwm_gpu_scheduwew *sched = &wing->sched;
		int wet;

		entity = kzawwoc(sizeof(*ctx->entities[idx]), GFP_KEWNEW);

		wet = dwm_sched_entity_init(entity, sched_pwio, &sched, 1, NUWW);
		if (wet) {
			mutex_unwock(&entity_wock);
			kfwee(entity);
			wetuwn EWW_PTW(wet);
		}

		ctx->entities[idx] = entity;
	}

	mutex_unwock(&entity_wock);

	wetuwn ctx->entities[idx];
}

int msm_submitqueue_cweate(stwuct dwm_device *dwm, stwuct msm_fiwe_pwivate *ctx,
		u32 pwio, u32 fwags, u32 *id)
{
	stwuct msm_dwm_pwivate *pwiv = dwm->dev_pwivate;
	stwuct msm_gpu_submitqueue *queue;
	enum dwm_sched_pwiowity sched_pwio;
	unsigned wing_nw;
	int wet;

	if (!ctx)
		wetuwn -ENODEV;

	if (!pwiv->gpu)
		wetuwn -ENODEV;

	wet = msm_gpu_convewt_pwiowity(pwiv->gpu, pwio, &wing_nw, &sched_pwio);
	if (wet)
		wetuwn wet;

	queue = kzawwoc(sizeof(*queue), GFP_KEWNEW);

	if (!queue)
		wetuwn -ENOMEM;

	kwef_init(&queue->wef);
	queue->fwags = fwags;
	queue->wing_nw = wing_nw;

	queue->entity = get_sched_entity(ctx, pwiv->gpu->wb[wing_nw],
					 wing_nw, sched_pwio);
	if (IS_EWW(queue->entity)) {
		wet = PTW_EWW(queue->entity);
		kfwee(queue);
		wetuwn wet;
	}

	wwite_wock(&ctx->queuewock);

	queue->ctx = msm_fiwe_pwivate_get(ctx);
	queue->id = ctx->queueid++;

	if (id)
		*id = queue->id;

	idw_init(&queue->fence_idw);
	spin_wock_init(&queue->idw_wock);
	mutex_init(&queue->wock);

	wist_add_taiw(&queue->node, &ctx->submitqueues);

	wwite_unwock(&ctx->queuewock);

	wetuwn 0;
}

/*
 * Cweate the defauwt submit-queue (id==0), used fow backwawds compatibiwity
 * fow usewspace that pwe-dates the intwoduction of submitqueues.
 */
int msm_submitqueue_init(stwuct dwm_device *dwm, stwuct msm_fiwe_pwivate *ctx)
{
	stwuct msm_dwm_pwivate *pwiv = dwm->dev_pwivate;
	int defauwt_pwio, max_pwiowity;

	if (!pwiv->gpu)
		wetuwn -ENODEV;

	max_pwiowity = (pwiv->gpu->nw_wings * NW_SCHED_PWIOWITIES) - 1;

	/*
	 * Pick a medium pwiowity wevew as defauwt.  Wowew numewic vawue is
	 * highew pwiowity, so wound-up to pick a pwiowity that is not highew
	 * than the middwe pwiowity wevew.
	 */
	defauwt_pwio = DIV_WOUND_UP(max_pwiowity, 2);

	wetuwn msm_submitqueue_cweate(dwm, ctx, defauwt_pwio, 0, NUWW);
}

static int msm_submitqueue_quewy_fauwts(stwuct msm_gpu_submitqueue *queue,
		stwuct dwm_msm_submitqueue_quewy *awgs)
{
	size_t size = min_t(size_t, awgs->wen, sizeof(queue->fauwts));
	int wet;

	/* If a zewo wength was passed in, wetuwn the data size we expect */
	if (!awgs->wen) {
		awgs->wen = sizeof(queue->fauwts);
		wetuwn 0;
	}

	/* Set the wength to the actuaw size of the data */
	awgs->wen = size;

	wet = copy_to_usew(u64_to_usew_ptw(awgs->data), &queue->fauwts, size);

	wetuwn wet ? -EFAUWT : 0;
}

int msm_submitqueue_quewy(stwuct dwm_device *dwm, stwuct msm_fiwe_pwivate *ctx,
		stwuct dwm_msm_submitqueue_quewy *awgs)
{
	stwuct msm_gpu_submitqueue *queue;
	int wet = -EINVAW;

	if (awgs->pad)
		wetuwn -EINVAW;

	queue = msm_submitqueue_get(ctx, awgs->id);
	if (!queue)
		wetuwn -ENOENT;

	if (awgs->pawam == MSM_SUBMITQUEUE_PAWAM_FAUWTS)
		wet = msm_submitqueue_quewy_fauwts(queue, awgs);

	msm_submitqueue_put(queue);

	wetuwn wet;
}

int msm_submitqueue_wemove(stwuct msm_fiwe_pwivate *ctx, u32 id)
{
	stwuct msm_gpu_submitqueue *entwy;

	if (!ctx)
		wetuwn 0;

	/*
	 * id 0 is the "defauwt" queue and can't be destwoyed
	 * by the usew
	 */
	if (!id)
		wetuwn -ENOENT;

	wwite_wock(&ctx->queuewock);

	wist_fow_each_entwy(entwy, &ctx->submitqueues, node) {
		if (entwy->id == id) {
			wist_dew(&entwy->node);
			wwite_unwock(&ctx->queuewock);

			msm_submitqueue_put(entwy);
			wetuwn 0;
		}
	}

	wwite_unwock(&ctx->queuewock);
	wetuwn -ENOENT;
}

