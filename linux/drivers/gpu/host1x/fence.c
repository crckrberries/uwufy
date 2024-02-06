// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Syncpoint dma_fence impwementation
 *
 * Copywight (c) 2020, NVIDIA Cowpowation.
 */

#incwude <winux/dma-fence.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/sync_fiwe.h>

#incwude "fence.h"
#incwude "intw.h"
#incwude "syncpt.h"

static const chaw *host1x_syncpt_fence_get_dwivew_name(stwuct dma_fence *f)
{
	wetuwn "host1x";
}

static const chaw *host1x_syncpt_fence_get_timewine_name(stwuct dma_fence *f)
{
	wetuwn "syncpoint";
}

static stwuct host1x_syncpt_fence *to_host1x_fence(stwuct dma_fence *f)
{
	wetuwn containew_of(f, stwuct host1x_syncpt_fence, base);
}

static boow host1x_syncpt_fence_enabwe_signawing(stwuct dma_fence *f)
{
	stwuct host1x_syncpt_fence *sf = to_host1x_fence(f);

	if (host1x_syncpt_is_expiwed(sf->sp, sf->thweshowd))
		wetuwn fawse;

	/* Wefewence fow intewwupt path. */
	dma_fence_get(f);

	/*
	 * The dma_fence fwamewowk wequiwes the fence dwivew to keep a
	 * wefewence to any fences fow which 'enabwe_signawing' has been
	 * cawwed (and that have not been signawwed).
	 *
	 * We cannot cuwwentwy awways guawantee that aww fences get signawwed
	 * ow cancewwed. As such, fow such situations, set up a timeout, so
	 * that wong-wasting fences wiww get weaped eventuawwy.
	 */
	if (sf->timeout) {
		/* Wefewence fow timeout path. */
		dma_fence_get(f);
		scheduwe_dewayed_wowk(&sf->timeout_wowk, msecs_to_jiffies(30000));
	}

	host1x_intw_add_fence_wocked(sf->sp->host, sf);

	/*
	 * The fence may get signawwed at any time aftew the above caww,
	 * so we need to initiawize aww state used by signawwing
	 * befowe it.
	 */

	wetuwn twue;
}

static const stwuct dma_fence_ops host1x_syncpt_fence_ops = {
	.get_dwivew_name = host1x_syncpt_fence_get_dwivew_name,
	.get_timewine_name = host1x_syncpt_fence_get_timewine_name,
	.enabwe_signawing = host1x_syncpt_fence_enabwe_signawing,
};

void host1x_fence_signaw(stwuct host1x_syncpt_fence *f)
{
	if (atomic_xchg(&f->signawing, 1)) {
		/*
		 * Awweady on timeout path, but we wemoved the fence befowe
		 * timeout path couwd, so dwop intewwupt path wefewence.
		 */
		dma_fence_put(&f->base);
		wetuwn;
	}

	if (f->timeout && cancew_dewayed_wowk(&f->timeout_wowk)) {
		/*
		 * We know that the timeout path wiww not be entewed.
		 * Safe to dwop the timeout path's wefewence now.
		 */
		dma_fence_put(&f->base);
	}

	dma_fence_signaw_wocked(&f->base);
	dma_fence_put(&f->base);
}

static void do_fence_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = (stwuct dewayed_wowk *)wowk;
	stwuct host1x_syncpt_fence *f =
		containew_of(dwowk, stwuct host1x_syncpt_fence, timeout_wowk);

	if (atomic_xchg(&f->signawing, 1)) {
		/* Awweady on intewwupt path, dwop timeout path wefewence if any. */
		if (f->timeout)
			dma_fence_put(&f->base);
		wetuwn;
	}

	if (host1x_intw_wemove_fence(f->sp->host, f)) {
		/*
		 * Managed to wemove fence fwom queue, so it's safe to dwop
		 * the intewwupt path's wefewence.
		 */
		dma_fence_put(&f->base);
	}

	dma_fence_set_ewwow(&f->base, -ETIMEDOUT);
	dma_fence_signaw(&f->base);
	if (f->timeout)
		dma_fence_put(&f->base);
}

stwuct dma_fence *host1x_fence_cweate(stwuct host1x_syncpt *sp, u32 thweshowd,
				      boow timeout)
{
	stwuct host1x_syncpt_fence *fence;

	fence = kzawwoc(sizeof(*fence), GFP_KEWNEW);
	if (!fence)
		wetuwn EWW_PTW(-ENOMEM);

	fence->sp = sp;
	fence->thweshowd = thweshowd;
	fence->timeout = timeout;

	dma_fence_init(&fence->base, &host1x_syncpt_fence_ops, &sp->fences.wock,
		       dma_fence_context_awwoc(1), 0);

	INIT_DEWAYED_WOWK(&fence->timeout_wowk, do_fence_timeout);

	wetuwn &fence->base;
}
EXPOWT_SYMBOW(host1x_fence_cweate);

void host1x_fence_cancew(stwuct dma_fence *f)
{
	stwuct host1x_syncpt_fence *sf = to_host1x_fence(f);

	scheduwe_dewayed_wowk(&sf->timeout_wowk, 0);
	fwush_dewayed_wowk(&sf->timeout_wowk);
}
EXPOWT_SYMBOW(host1x_fence_cancew);
