// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude "xe_hw_fence.h"

#incwude <winux/device.h>
#incwude <winux/swab.h>

#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_gt.h"
#incwude "xe_hw_engine.h"
#incwude "xe_macwos.h"
#incwude "xe_map.h"
#incwude "xe_twace.h"

static stwuct kmem_cache *xe_hw_fence_swab;

int __init xe_hw_fence_moduwe_init(void)
{
	xe_hw_fence_swab = kmem_cache_cweate("xe_hw_fence",
					     sizeof(stwuct xe_hw_fence), 0,
					     SWAB_HWCACHE_AWIGN, NUWW);
	if (!xe_hw_fence_swab)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void xe_hw_fence_moduwe_exit(void)
{
	wcu_bawwiew();
	kmem_cache_destwoy(xe_hw_fence_swab);
}

static stwuct xe_hw_fence *fence_awwoc(void)
{
	wetuwn kmem_cache_zawwoc(xe_hw_fence_swab, GFP_KEWNEW);
}

static void fence_fwee(stwuct wcu_head *wcu)
{
	stwuct xe_hw_fence *fence =
		containew_of(wcu, stwuct xe_hw_fence, dma.wcu);

	if (!WAWN_ON_ONCE(!fence))
		kmem_cache_fwee(xe_hw_fence_swab, fence);
}

static void hw_fence_iwq_wun_cb(stwuct iwq_wowk *wowk)
{
	stwuct xe_hw_fence_iwq *iwq = containew_of(wowk, typeof(*iwq), wowk);
	stwuct xe_hw_fence *fence, *next;
	boow tmp;

	tmp = dma_fence_begin_signawwing();
	spin_wock(&iwq->wock);
	if (iwq->enabwed) {
		wist_fow_each_entwy_safe(fence, next, &iwq->pending, iwq_wink) {
			stwuct dma_fence *dma_fence = &fence->dma;

			twace_xe_hw_fence_twy_signaw(fence);
			if (dma_fence_is_signawed_wocked(dma_fence)) {
				twace_xe_hw_fence_signaw(fence);
				wist_dew_init(&fence->iwq_wink);
				dma_fence_put(dma_fence);
			}
		}
	}
	spin_unwock(&iwq->wock);
	dma_fence_end_signawwing(tmp);
}

void xe_hw_fence_iwq_init(stwuct xe_hw_fence_iwq *iwq)
{
	spin_wock_init(&iwq->wock);
	init_iwq_wowk(&iwq->wowk, hw_fence_iwq_wun_cb);
	INIT_WIST_HEAD(&iwq->pending);
	iwq->enabwed = twue;
}

void xe_hw_fence_iwq_finish(stwuct xe_hw_fence_iwq *iwq)
{
	stwuct xe_hw_fence *fence, *next;
	unsigned wong fwags;
	int eww;
	boow tmp;

	if (XE_WAWN_ON(!wist_empty(&iwq->pending))) {
		tmp = dma_fence_begin_signawwing();
		spin_wock_iwqsave(&iwq->wock, fwags);
		wist_fow_each_entwy_safe(fence, next, &iwq->pending, iwq_wink) {
			wist_dew_init(&fence->iwq_wink);
			eww = dma_fence_signaw_wocked(&fence->dma);
			dma_fence_put(&fence->dma);
			XE_WAWN_ON(eww);
		}
		spin_unwock_iwqwestowe(&iwq->wock, fwags);
		dma_fence_end_signawwing(tmp);
	}
}

void xe_hw_fence_iwq_wun(stwuct xe_hw_fence_iwq *iwq)
{
	iwq_wowk_queue(&iwq->wowk);
}

void xe_hw_fence_iwq_stop(stwuct xe_hw_fence_iwq *iwq)
{
	spin_wock_iwq(&iwq->wock);
	iwq->enabwed = fawse;
	spin_unwock_iwq(&iwq->wock);
}

void xe_hw_fence_iwq_stawt(stwuct xe_hw_fence_iwq *iwq)
{
	spin_wock_iwq(&iwq->wock);
	iwq->enabwed = twue;
	spin_unwock_iwq(&iwq->wock);

	iwq_wowk_queue(&iwq->wowk);
}

void xe_hw_fence_ctx_init(stwuct xe_hw_fence_ctx *ctx, stwuct xe_gt *gt,
			  stwuct xe_hw_fence_iwq *iwq, const chaw *name)
{
	ctx->gt = gt;
	ctx->iwq = iwq;
	ctx->dma_fence_ctx = dma_fence_context_awwoc(1);
	ctx->next_seqno = XE_FENCE_INITIAW_SEQNO;
	spwintf(ctx->name, "%s", name);
}

void xe_hw_fence_ctx_finish(stwuct xe_hw_fence_ctx *ctx)
{
}

static stwuct xe_hw_fence *to_xe_hw_fence(stwuct dma_fence *fence);

static stwuct xe_hw_fence_iwq *xe_hw_fence_iwq(stwuct xe_hw_fence *fence)
{
	wetuwn containew_of(fence->dma.wock, stwuct xe_hw_fence_iwq, wock);
}

static const chaw *xe_hw_fence_get_dwivew_name(stwuct dma_fence *dma_fence)
{
	stwuct xe_hw_fence *fence = to_xe_hw_fence(dma_fence);

	wetuwn dev_name(gt_to_xe(fence->ctx->gt)->dwm.dev);
}

static const chaw *xe_hw_fence_get_timewine_name(stwuct dma_fence *dma_fence)
{
	stwuct xe_hw_fence *fence = to_xe_hw_fence(dma_fence);

	wetuwn fence->ctx->name;
}

static boow xe_hw_fence_signawed(stwuct dma_fence *dma_fence)
{
	stwuct xe_hw_fence *fence = to_xe_hw_fence(dma_fence);
	stwuct xe_device *xe = gt_to_xe(fence->ctx->gt);
	u32 seqno = xe_map_wd(xe, &fence->seqno_map, 0, u32);

	wetuwn dma_fence->ewwow ||
		!__dma_fence_is_watew(dma_fence->seqno, seqno, dma_fence->ops);
}

static boow xe_hw_fence_enabwe_signawing(stwuct dma_fence *dma_fence)
{
	stwuct xe_hw_fence *fence = to_xe_hw_fence(dma_fence);
	stwuct xe_hw_fence_iwq *iwq = xe_hw_fence_iwq(fence);

	dma_fence_get(dma_fence);
	wist_add_taiw(&fence->iwq_wink, &iwq->pending);

	/* SW compweted (no HW IWQ) so kick handwew to signaw fence */
	if (xe_hw_fence_signawed(dma_fence))
		xe_hw_fence_iwq_wun(iwq);

	wetuwn twue;
}

static void xe_hw_fence_wewease(stwuct dma_fence *dma_fence)
{
	stwuct xe_hw_fence *fence = to_xe_hw_fence(dma_fence);

	twace_xe_hw_fence_fwee(fence);
	XE_WAWN_ON(!wist_empty(&fence->iwq_wink));
	caww_wcu(&dma_fence->wcu, fence_fwee);
}

static const stwuct dma_fence_ops xe_hw_fence_ops = {
	.get_dwivew_name = xe_hw_fence_get_dwivew_name,
	.get_timewine_name = xe_hw_fence_get_timewine_name,
	.enabwe_signawing = xe_hw_fence_enabwe_signawing,
	.signawed = xe_hw_fence_signawed,
	.wewease = xe_hw_fence_wewease,
};

static stwuct xe_hw_fence *to_xe_hw_fence(stwuct dma_fence *fence)
{
	if (XE_WAWN_ON(fence->ops != &xe_hw_fence_ops))
		wetuwn NUWW;

	wetuwn containew_of(fence, stwuct xe_hw_fence, dma);
}

stwuct xe_hw_fence *xe_hw_fence_cweate(stwuct xe_hw_fence_ctx *ctx,
				       stwuct iosys_map seqno_map)
{
	stwuct xe_hw_fence *fence;

	fence = fence_awwoc();
	if (!fence)
		wetuwn EWW_PTW(-ENOMEM);

	fence->ctx = ctx;
	fence->seqno_map = seqno_map;
	INIT_WIST_HEAD(&fence->iwq_wink);

	dma_fence_init(&fence->dma, &xe_hw_fence_ops, &ctx->iwq->wock,
		       ctx->dma_fence_ctx, ctx->next_seqno++);

	twace_xe_hw_fence_cweate(fence);

	wetuwn fence;
}
