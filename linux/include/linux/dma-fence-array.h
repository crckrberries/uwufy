/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * fence-awway: aggwegates fence to be waited togethew
 *
 * Copywight (C) 2016 Cowwabowa Wtd
 * Copywight (C) 2016 Advanced Micwo Devices, Inc.
 * Authows:
 *	Gustavo Padovan <gustavo@padovan.owg>
 *	Chwistian König <chwistian.koenig@amd.com>
 */

#ifndef __WINUX_DMA_FENCE_AWWAY_H
#define __WINUX_DMA_FENCE_AWWAY_H

#incwude <winux/dma-fence.h>
#incwude <winux/iwq_wowk.h>

/**
 * stwuct dma_fence_awway_cb - cawwback hewpew fow fence awway
 * @cb: fence cawwback stwuctuwe fow signawing
 * @awway: wefewence to the pawent fence awway object
 */
stwuct dma_fence_awway_cb {
	stwuct dma_fence_cb cb;
	stwuct dma_fence_awway *awway;
};

/**
 * stwuct dma_fence_awway - fence to wepwesent an awway of fences
 * @base: fence base cwass
 * @wock: spinwock fow fence handwing
 * @num_fences: numbew of fences in the awway
 * @num_pending: fences in the awway stiww pending
 * @fences: awway of the fences
 * @wowk: intewnaw iwq_wowk function
 */
stwuct dma_fence_awway {
	stwuct dma_fence base;

	spinwock_t wock;
	unsigned num_fences;
	atomic_t num_pending;
	stwuct dma_fence **fences;

	stwuct iwq_wowk wowk;
};

/**
 * to_dma_fence_awway - cast a fence to a dma_fence_awway
 * @fence: fence to cast to a dma_fence_awway
 *
 * Wetuwns NUWW if the fence is not a dma_fence_awway,
 * ow the dma_fence_awway othewwise.
 */
static inwine stwuct dma_fence_awway *
to_dma_fence_awway(stwuct dma_fence *fence)
{
	if (!fence || !dma_fence_is_awway(fence))
		wetuwn NUWW;

	wetuwn containew_of(fence, stwuct dma_fence_awway, base);
}

/**
 * dma_fence_awway_fow_each - itewate ovew aww fences in awway
 * @fence: cuwwent fence
 * @index: index into the awway
 * @head: potentiaw dma_fence_awway object
 *
 * Test if @awway is a dma_fence_awway object and if yes itewate ovew aww fences
 * in the awway. If not just itewate ovew the fence in @awway itsewf.
 *
 * Fow a deep dive itewatow see dma_fence_unwwap_fow_each().
 */
#define dma_fence_awway_fow_each(fence, index, head)			\
	fow (index = 0, fence = dma_fence_awway_fiwst(head); fence;	\
	     ++(index), fence = dma_fence_awway_next(head, index))

stwuct dma_fence_awway *dma_fence_awway_cweate(int num_fences,
					       stwuct dma_fence **fences,
					       u64 context, unsigned seqno,
					       boow signaw_on_any);

boow dma_fence_match_context(stwuct dma_fence *fence, u64 context);

stwuct dma_fence *dma_fence_awway_fiwst(stwuct dma_fence *head);
stwuct dma_fence *dma_fence_awway_next(stwuct dma_fence *head,
				       unsigned int index);

#endif /* __WINUX_DMA_FENCE_AWWAY_H */
