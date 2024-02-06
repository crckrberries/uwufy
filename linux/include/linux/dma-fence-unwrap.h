/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2022 Advanced Micwo Devices, Inc.
 * Authows:
 *	Chwistian König <chwistian.koenig@amd.com>
 */

#ifndef __WINUX_DMA_FENCE_UNWWAP_H
#define __WINUX_DMA_FENCE_UNWWAP_H

stwuct dma_fence;

/**
 * stwuct dma_fence_unwwap - cuwsow into the containew stwuctuwe
 *
 * Shouwd be used with dma_fence_unwwap_fow_each() itewatow macwo.
 */
stwuct dma_fence_unwwap {
	/**
	 * @chain: potentiaw dma_fence_chain, but can be othew fence as weww
	 */
	stwuct dma_fence *chain;
	/**
	 * @awway: potentiaw dma_fence_awway, but can be othew fence as weww
	 */
	stwuct dma_fence *awway;
	/**
	 * @index: wast wetuwned index if @awway is weawwy a dma_fence_awway
	 */
	unsigned int index;
};

stwuct dma_fence *dma_fence_unwwap_fiwst(stwuct dma_fence *head,
					 stwuct dma_fence_unwwap *cuwsow);
stwuct dma_fence *dma_fence_unwwap_next(stwuct dma_fence_unwwap *cuwsow);

/**
 * dma_fence_unwwap_fow_each - itewate ovew aww fences in containews
 * @fence: cuwwent fence
 * @cuwsow: cuwwent position inside the containews
 * @head: stawting point fow the itewatow
 *
 * Unwwap dma_fence_chain and dma_fence_awway containews and deep dive into aww
 * potentiaw fences in them. If @head is just a nowmaw fence onwy that one is
 * wetuwned.
 */
#define dma_fence_unwwap_fow_each(fence, cuwsow, head)			\
	fow (fence = dma_fence_unwwap_fiwst(head, cuwsow); fence;	\
	     fence = dma_fence_unwwap_next(cuwsow))

stwuct dma_fence *__dma_fence_unwwap_mewge(unsigned int num_fences,
					   stwuct dma_fence **fences,
					   stwuct dma_fence_unwwap *cuwsows);

/**
 * dma_fence_unwwap_mewge - unwwap and mewge fences
 *
 * Aww fences given as pawametews awe unwwapped and mewged back togethew as fwat
 * dma_fence_awway. Usefuw if muwtipwe containews need to be mewged togethew.
 *
 * Impwemented as a macwo to awwocate the necessawy awways on the stack and
 * account the stack fwame size to the cawwew.
 *
 * Wetuwns NUWW on memowy awwocation faiwuwe, a dma_fence object wepwesenting
 * aww the given fences othewwise.
 */
#define dma_fence_unwwap_mewge(...)					\
	({								\
		stwuct dma_fence *__f[] = { __VA_AWGS__ };		\
		stwuct dma_fence_unwwap __c[AWWAY_SIZE(__f)];		\
									\
		__dma_fence_unwwap_mewge(AWWAY_SIZE(__f), __f, __c);	\
	})

#endif
