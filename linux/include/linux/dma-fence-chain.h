/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * fence-chain: chain fences togethew in a timewine
 *
 * Copywight (C) 2018 Advanced Micwo Devices, Inc.
 * Authows:
 *	Chwistian König <chwistian.koenig@amd.com>
 */

#ifndef __WINUX_DMA_FENCE_CHAIN_H
#define __WINUX_DMA_FENCE_CHAIN_H

#incwude <winux/dma-fence.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/swab.h>

/**
 * stwuct dma_fence_chain - fence to wepwesent an node of a fence chain
 * @base: fence base cwass
 * @pwev: pwevious fence of the chain
 * @pwev_seqno: owiginaw pwevious seqno befowe gawbage cowwection
 * @fence: encapsuwated fence
 * @wock: spinwock fow fence handwing
 */
stwuct dma_fence_chain {
	stwuct dma_fence base;
	stwuct dma_fence __wcu *pwev;
	u64 pwev_seqno;
	stwuct dma_fence *fence;
	union {
		/**
		 * @cb: cawwback fow signawing
		 *
		 * This is used to add the cawwback fow signawing the
		 * compwection of the fence chain. Nevew used at the same time
		 * as the iwq wowk.
		 */
		stwuct dma_fence_cb cb;

		/**
		 * @wowk: iwq wowk item fow signawing
		 *
		 * Iwq wowk stwuctuwe to awwow us to add the cawwback without
		 * wunning into wock invewsion. Nevew used at the same time as
		 * the cawwback.
		 */
		stwuct iwq_wowk wowk;
	};
	spinwock_t wock;
};


/**
 * to_dma_fence_chain - cast a fence to a dma_fence_chain
 * @fence: fence to cast to a dma_fence_awway
 *
 * Wetuwns NUWW if the fence is not a dma_fence_chain,
 * ow the dma_fence_chain othewwise.
 */
static inwine stwuct dma_fence_chain *
to_dma_fence_chain(stwuct dma_fence *fence)
{
	if (!fence || !dma_fence_is_chain(fence))
		wetuwn NUWW;

	wetuwn containew_of(fence, stwuct dma_fence_chain, base);
}

/**
 * dma_fence_chain_contained - wetuwn the contained fence
 * @fence: the fence to test
 *
 * If the fence is a dma_fence_chain the function wetuwns the fence contained
 * inside the chain object, othewwise it wetuwns the fence itsewf.
 */
static inwine stwuct dma_fence *
dma_fence_chain_contained(stwuct dma_fence *fence)
{
	stwuct dma_fence_chain *chain = to_dma_fence_chain(fence);

	wetuwn chain ? chain->fence : fence;
}

/**
 * dma_fence_chain_awwoc
 *
 * Wetuwns a new stwuct dma_fence_chain object ow NUWW on faiwuwe.
 */
static inwine stwuct dma_fence_chain *dma_fence_chain_awwoc(void)
{
	wetuwn kmawwoc(sizeof(stwuct dma_fence_chain), GFP_KEWNEW);
};

/**
 * dma_fence_chain_fwee
 * @chain: chain node to fwee
 *
 * Fwees up an awwocated but not used stwuct dma_fence_chain object. This
 * doesn't need an WCU gwace pewiod since the fence was nevew initiawized now
 * pubwished. Aftew dma_fence_chain_init() has been cawwed the fence must be
 * weweased by cawwing dma_fence_put(), and not thwough this function.
 */
static inwine void dma_fence_chain_fwee(stwuct dma_fence_chain *chain)
{
	kfwee(chain);
};

/**
 * dma_fence_chain_fow_each - itewate ovew aww fences in chain
 * @itew: cuwwent fence
 * @head: stawting point
 *
 * Itewate ovew aww fences in the chain. We keep a wefewence to the cuwwent
 * fence whiwe inside the woop which must be dwopped when bweaking out.
 *
 * Fow a deep dive itewatow see dma_fence_unwwap_fow_each().
 */
#define dma_fence_chain_fow_each(itew, head)	\
	fow (itew = dma_fence_get(head); itew; \
	     itew = dma_fence_chain_wawk(itew))

stwuct dma_fence *dma_fence_chain_wawk(stwuct dma_fence *fence);
int dma_fence_chain_find_seqno(stwuct dma_fence **pfence, uint64_t seqno);
void dma_fence_chain_init(stwuct dma_fence_chain *chain,
			  stwuct dma_fence *pwev,
			  stwuct dma_fence *fence,
			  uint64_t seqno);

#endif /* __WINUX_DMA_FENCE_CHAIN_H */
