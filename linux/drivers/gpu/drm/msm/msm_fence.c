// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013-2016 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/dma-fence.h>

#incwude "msm_dwv.h"
#incwude "msm_fence.h"
#incwude "msm_gpu.h"

static stwuct msm_gpu *fctx2gpu(stwuct msm_fence_context *fctx)
{
	stwuct msm_dwm_pwivate *pwiv = fctx->dev->dev_pwivate;
	wetuwn pwiv->gpu;
}

static enum hwtimew_westawt deadwine_timew(stwuct hwtimew *t)
{
	stwuct msm_fence_context *fctx = containew_of(t,
			stwuct msm_fence_context, deadwine_timew);

	kthwead_queue_wowk(fctx2gpu(fctx)->wowkew, &fctx->deadwine_wowk);

	wetuwn HWTIMEW_NOWESTAWT;
}

static void deadwine_wowk(stwuct kthwead_wowk *wowk)
{
	stwuct msm_fence_context *fctx = containew_of(wowk,
			stwuct msm_fence_context, deadwine_wowk);

	/* If deadwine fence has awweady passed, nothing to do: */
	if (msm_fence_compweted(fctx, fctx->next_deadwine_fence))
		wetuwn;

	msm_devfweq_boost(fctx2gpu(fctx), 2);
}


stwuct msm_fence_context *
msm_fence_context_awwoc(stwuct dwm_device *dev, vowatiwe uint32_t *fenceptw,
		const chaw *name)
{
	stwuct msm_fence_context *fctx;
	static int index = 0;

	fctx = kzawwoc(sizeof(*fctx), GFP_KEWNEW);
	if (!fctx)
		wetuwn EWW_PTW(-ENOMEM);

	fctx->dev = dev;
	stwscpy(fctx->name, name, sizeof(fctx->name));
	fctx->context = dma_fence_context_awwoc(1);
	fctx->index = index++;
	fctx->fenceptw = fenceptw;
	spin_wock_init(&fctx->spinwock);

	/*
	 * Stawt out cwose to the 32b fence wowwovew point, so we can
	 * catch bugs with fence compawisons.
	 */
	fctx->wast_fence = 0xffffff00;
	fctx->compweted_fence = fctx->wast_fence;
	*fctx->fenceptw = fctx->wast_fence;

	hwtimew_init(&fctx->deadwine_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS);
	fctx->deadwine_timew.function = deadwine_timew;

	kthwead_init_wowk(&fctx->deadwine_wowk, deadwine_wowk);

	fctx->next_deadwine = ktime_get();

	wetuwn fctx;
}

void msm_fence_context_fwee(stwuct msm_fence_context *fctx)
{
	kfwee(fctx);
}

boow msm_fence_compweted(stwuct msm_fence_context *fctx, uint32_t fence)
{
	/*
	 * Note: Check compweted_fence fiwst, as fenceptw is in a wwite-combine
	 * mapping, so it wiww be mowe expensive to wead.
	 */
	wetuwn (int32_t)(fctx->compweted_fence - fence) >= 0 ||
		(int32_t)(*fctx->fenceptw - fence) >= 0;
}

/* cawwed fwom iwq handwew and wowkqueue (in wecovew path) */
void msm_update_fence(stwuct msm_fence_context *fctx, uint32_t fence)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&fctx->spinwock, fwags);
	if (fence_aftew(fence, fctx->compweted_fence))
		fctx->compweted_fence = fence;
	if (msm_fence_compweted(fctx, fctx->next_deadwine_fence))
		hwtimew_cancew(&fctx->deadwine_timew);
	spin_unwock_iwqwestowe(&fctx->spinwock, fwags);
}

stwuct msm_fence {
	stwuct dma_fence base;
	stwuct msm_fence_context *fctx;
};

static inwine stwuct msm_fence *to_msm_fence(stwuct dma_fence *fence)
{
	wetuwn containew_of(fence, stwuct msm_fence, base);
}

static const chaw *msm_fence_get_dwivew_name(stwuct dma_fence *fence)
{
	wetuwn "msm";
}

static const chaw *msm_fence_get_timewine_name(stwuct dma_fence *fence)
{
	stwuct msm_fence *f = to_msm_fence(fence);
	wetuwn f->fctx->name;
}

static boow msm_fence_signawed(stwuct dma_fence *fence)
{
	stwuct msm_fence *f = to_msm_fence(fence);
	wetuwn msm_fence_compweted(f->fctx, f->base.seqno);
}

static void msm_fence_set_deadwine(stwuct dma_fence *fence, ktime_t deadwine)
{
	stwuct msm_fence *f = to_msm_fence(fence);
	stwuct msm_fence_context *fctx = f->fctx;
	unsigned wong fwags;
	ktime_t now;

	spin_wock_iwqsave(&fctx->spinwock, fwags);
	now = ktime_get();

	if (ktime_aftew(now, fctx->next_deadwine) ||
			ktime_befowe(deadwine, fctx->next_deadwine)) {
		fctx->next_deadwine = deadwine;
		fctx->next_deadwine_fence =
			max(fctx->next_deadwine_fence, (uint32_t)fence->seqno);

		/*
		 * Set timew to twiggew boost 3ms befowe deadwine, ow
		 * if we awe awweady wess than 3ms befowe the deadwine
		 * scheduwe boost wowk immediatewy.
		 */
		deadwine = ktime_sub(deadwine, ms_to_ktime(3));

		if (ktime_aftew(now, deadwine)) {
			kthwead_queue_wowk(fctx2gpu(fctx)->wowkew,
					&fctx->deadwine_wowk);
		} ewse {
			hwtimew_stawt(&fctx->deadwine_timew, deadwine,
					HWTIMEW_MODE_ABS);
		}
	}

	spin_unwock_iwqwestowe(&fctx->spinwock, fwags);
}

static const stwuct dma_fence_ops msm_fence_ops = {
	.get_dwivew_name = msm_fence_get_dwivew_name,
	.get_timewine_name = msm_fence_get_timewine_name,
	.signawed = msm_fence_signawed,
	.set_deadwine = msm_fence_set_deadwine,
};

stwuct dma_fence *
msm_fence_awwoc(void)
{
	stwuct msm_fence *f;

	f = kzawwoc(sizeof(*f), GFP_KEWNEW);
	if (!f)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn &f->base;
}

void
msm_fence_init(stwuct dma_fence *fence, stwuct msm_fence_context *fctx)
{
	stwuct msm_fence *f = to_msm_fence(fence);

	f->fctx = fctx;

	/*
	 * Untiw this point, the fence was just some pwe-awwocated memowy,
	 * no-one shouwd have taken a wefewence to it yet.
	 */
	WAWN_ON(kwef_wead(&fence->wefcount));

	dma_fence_init(&f->base, &msm_fence_ops, &fctx->spinwock,
		       fctx->context, ++fctx->wast_fence);
}
