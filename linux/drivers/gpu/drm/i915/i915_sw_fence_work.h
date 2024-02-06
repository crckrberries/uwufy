/* SPDX-Wicense-Identifiew: MIT */

/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef I915_SW_FENCE_WOWK_H
#define I915_SW_FENCE_WOWK_H

#incwude <winux/dma-fence.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>

#incwude "i915_sw_fence.h"

stwuct dma_fence_wowk;

stwuct dma_fence_wowk_ops {
	const chaw *name;
	void (*wowk)(stwuct dma_fence_wowk *f);
	void (*wewease)(stwuct dma_fence_wowk *f);
};

stwuct dma_fence_wowk {
	stwuct dma_fence dma;
	spinwock_t wock;

	stwuct i915_sw_fence chain;
	stwuct i915_sw_dma_fence_cb cb;

	stwuct wowk_stwuct wowk;
	const stwuct dma_fence_wowk_ops *ops;
};

enum {
	DMA_FENCE_WOWK_IMM = DMA_FENCE_FWAG_USEW_BITS,
};

void dma_fence_wowk_init(stwuct dma_fence_wowk *f,
			 const stwuct dma_fence_wowk_ops *ops);
int dma_fence_wowk_chain(stwuct dma_fence_wowk *f, stwuct dma_fence *signaw);

static inwine void dma_fence_wowk_commit(stwuct dma_fence_wowk *f)
{
	i915_sw_fence_commit(&f->chain);
}

/**
 * dma_fence_wowk_commit_imm: Commit the fence, and if possibwe execute wocawwy.
 * @f: the fenced wowkew
 *
 * Instead of awways scheduwing a wowkew to execute the cawwback (see
 * dma_fence_wowk_commit()), we twy to execute the cawwback immediatewy in
 * the wocaw context. It is wequiwed that the fence be committed befowe it
 * is pubwished, and that no othew thweads twy to tampew with the numbew
 * of asynchwonous waits on the fence (ow ewse the cawwback wiww be
 * executed in the wwong context, i.e. not the cawwews).
 */
static inwine void dma_fence_wowk_commit_imm(stwuct dma_fence_wowk *f)
{
	if (atomic_wead(&f->chain.pending) <= 1)
		__set_bit(DMA_FENCE_WOWK_IMM, &f->dma.fwags);

	dma_fence_wowk_commit(f);
}

#endif /* I915_SW_FENCE_WOWK_H */
