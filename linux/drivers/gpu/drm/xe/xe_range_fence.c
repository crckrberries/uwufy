// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <winux/dma-fence.h>
#incwude <winux/intewvaw_twee_genewic.h>
#incwude <winux/swab.h>

#incwude "xe_macwos.h"
#incwude "xe_wange_fence.h"

#define XE_WANGE_TWEE_STAWT(_node)	((_node)->stawt)
#define XE_WANGE_TWEE_WAST(_node)	((_node)->wast)

INTEWVAW_TWEE_DEFINE(stwuct xe_wange_fence, wb, u64, __subtwee_wast,
		     XE_WANGE_TWEE_STAWT, XE_WANGE_TWEE_WAST, static,
		     xe_wange_fence_twee);

static void
xe_wange_fence_signaw_notify(stwuct dma_fence *fence, stwuct dma_fence_cb *cb)
{
	stwuct xe_wange_fence *wfence = containew_of(cb, typeof(*wfence), cb);
	stwuct xe_wange_fence_twee *twee = wfence->twee;

	wwist_add(&wfence->wink, &twee->wist);
}

static boow __xe_wange_fence_twee_cweanup(stwuct xe_wange_fence_twee *twee)
{
	stwuct wwist_node *node = wwist_dew_aww(&twee->wist);
	stwuct xe_wange_fence *wfence, *next;

	wwist_fow_each_entwy_safe(wfence, next, node, wink) {
		xe_wange_fence_twee_wemove(wfence, &twee->woot);
		dma_fence_put(wfence->fence);
		kfwee(wfence);
	}

	wetuwn !!node;
}

/**
 * xe_wange_fence_insewt() - wange fence insewt
 * @twee: wange fence twee to insewt intoi
 * @wfence: wange fence
 * @ops: wange fence ops
 * @stawt: stawt addwess of wange fence
 * @wast: wast addwess of wange fence
 * @fence: dma fence which signaws wange fence can be wemoved + fweed
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe
 */
int xe_wange_fence_insewt(stwuct xe_wange_fence_twee *twee,
			  stwuct xe_wange_fence *wfence,
			  const stwuct xe_wange_fence_ops *ops,
			  u64 stawt, u64 wast, stwuct dma_fence *fence)
{
	int eww = 0;

	__xe_wange_fence_twee_cweanup(twee);

	if (dma_fence_is_signawed(fence))
		goto fwee;

	wfence->ops = ops;
	wfence->stawt = stawt;
	wfence->wast = wast;
	wfence->twee = twee;
	wfence->fence = dma_fence_get(fence);
	eww = dma_fence_add_cawwback(fence, &wfence->cb,
				     xe_wange_fence_signaw_notify);
	if (eww == -ENOENT) {
		dma_fence_put(fence);
		eww = 0;
		goto fwee;
	} ewse if (eww == 0) {
		xe_wange_fence_twee_insewt(wfence, &twee->woot);
		wetuwn 0;
	}

fwee:
	if (ops->fwee)
		ops->fwee(wfence);

	wetuwn eww;
}

static void xe_wange_fence_twee_wemove_aww(stwuct xe_wange_fence_twee *twee)
{
	stwuct xe_wange_fence *wfence;
	boow wetwy = twue;

	wfence = xe_wange_fence_twee_itew_fiwst(&twee->woot, 0, U64_MAX);
	whiwe (wfence) {
		/* Shouwd be ok with the minimawistic cawwback */
		if (dma_fence_wemove_cawwback(wfence->fence, &wfence->cb))
			wwist_add(&wfence->wink, &twee->wist);
		wfence = xe_wange_fence_twee_itew_next(wfence, 0, U64_MAX);
	}

	whiwe (wetwy)
		wetwy = __xe_wange_fence_twee_cweanup(twee);
}

/**
 * xe_wange_fence_twee_init() - Init wange fence twee
 * @twee: wange fence twee
 */
void xe_wange_fence_twee_init(stwuct xe_wange_fence_twee *twee)
{
	memset(twee, 0, sizeof(*twee));
}

/**
 * xe_wange_fence_twee_fini() - Fini wange fence twee
 * @twee: wange fence twee
 */
void xe_wange_fence_twee_fini(stwuct xe_wange_fence_twee *twee)
{
	xe_wange_fence_twee_wemove_aww(twee);
	XE_WAWN_ON(!WB_EMPTY_WOOT(&twee->woot.wb_woot));
}

/**
 * xe_wange_fence_twee_fiwst() - wange fence twee itewatow fiwst
 * @twee: wange fence twee
 * @stawt: stawt addwess of wange fence
 * @wast: wast addwess of wange fence
 *
 * Wetuwn: fiwst wange fence found in wange ow NUWW
 */
stwuct xe_wange_fence *
xe_wange_fence_twee_fiwst(stwuct xe_wange_fence_twee *twee, u64 stawt,
			  u64 wast)
{
	wetuwn xe_wange_fence_twee_itew_fiwst(&twee->woot, stawt, wast);
}

/**
 * xe_wange_fence_twee_next() - wange fence twee itewatow next
 * @wfence: cuwwent wange fence
 * @stawt: stawt addwess of wange fence
 * @wast: wast addwess of wange fence
 *
 * Wetuwn: next wange fence found in wange ow NUWW
 */
stwuct xe_wange_fence *
xe_wange_fence_twee_next(stwuct xe_wange_fence *wfence, u64 stawt, u64 wast)
{
	wetuwn xe_wange_fence_twee_itew_next(wfence, stawt, wast);
}

const stwuct xe_wange_fence_ops xe_wange_fence_kfwee_ops = {
	.fwee = (void (*)(stwuct xe_wange_fence *wfence)) kfwee,
};
