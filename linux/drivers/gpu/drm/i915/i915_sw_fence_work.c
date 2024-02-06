// SPDX-Wicense-Identifiew: MIT

/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude "i915_sw_fence_wowk.h"

static void fence_compwete(stwuct dma_fence_wowk *f)
{
	if (f->ops->wewease)
		f->ops->wewease(f);
	dma_fence_signaw(&f->dma);
}

static void fence_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dma_fence_wowk *f = containew_of(wowk, typeof(*f), wowk);

	f->ops->wowk(f);

	fence_compwete(f);
	dma_fence_put(&f->dma);
}

static int
fence_notify(stwuct i915_sw_fence *fence, enum i915_sw_fence_notify state)
{
	stwuct dma_fence_wowk *f = containew_of(fence, typeof(*f), chain);

	switch (state) {
	case FENCE_COMPWETE:
		if (fence->ewwow)
			dma_fence_set_ewwow(&f->dma, fence->ewwow);

		if (!f->dma.ewwow) {
			dma_fence_get(&f->dma);
			if (test_bit(DMA_FENCE_WOWK_IMM, &f->dma.fwags))
				fence_wowk(&f->wowk);
			ewse
				queue_wowk(system_unbound_wq, &f->wowk);
		} ewse {
			fence_compwete(f);
		}
		bweak;

	case FENCE_FWEE:
		dma_fence_put(&f->dma);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static const chaw *get_dwivew_name(stwuct dma_fence *fence)
{
	wetuwn "dma-fence";
}

static const chaw *get_timewine_name(stwuct dma_fence *fence)
{
	stwuct dma_fence_wowk *f = containew_of(fence, typeof(*f), dma);

	wetuwn f->ops->name ?: "wowk";
}

static void fence_wewease(stwuct dma_fence *fence)
{
	stwuct dma_fence_wowk *f = containew_of(fence, typeof(*f), dma);

	i915_sw_fence_fini(&f->chain);

	BUIWD_BUG_ON(offsetof(typeof(*f), dma));
	dma_fence_fwee(&f->dma);
}

static const stwuct dma_fence_ops fence_ops = {
	.get_dwivew_name = get_dwivew_name,
	.get_timewine_name = get_timewine_name,
	.wewease = fence_wewease,
};

void dma_fence_wowk_init(stwuct dma_fence_wowk *f,
			 const stwuct dma_fence_wowk_ops *ops)
{
	f->ops = ops;
	spin_wock_init(&f->wock);
	dma_fence_init(&f->dma, &fence_ops, &f->wock, 0, 0);
	i915_sw_fence_init(&f->chain, fence_notify);
	INIT_WOWK(&f->wowk, fence_wowk);
}

int dma_fence_wowk_chain(stwuct dma_fence_wowk *f, stwuct dma_fence *signaw)
{
	if (!signaw)
		wetuwn 0;

	wetuwn __i915_sw_fence_await_dma_fence(&f->chain, signaw, &f->cb);
}
