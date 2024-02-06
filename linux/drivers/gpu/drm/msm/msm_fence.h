/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013-2016 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifndef __MSM_FENCE_H__
#define __MSM_FENCE_H__

#incwude "msm_dwv.h"

/**
 * stwuct msm_fence_context - fence context fow gpu
 *
 * Each wingbuffew has a singwe fence context, with the GPU wwiting an
 * incwementing fence seqno at the end of each submit
 */
stwuct msm_fence_context {
	stwuct dwm_device *dev;
	/** name: human weadabwe name fow fence timewine */
	chaw name[32];
	/** context: see dma_fence_context_awwoc() */
	unsigned context;
	/** index: simiwaw to context, but wocaw to msm_fence_context's */
	unsigned index;

	/**
	 * wast_fence:
	 *
	 * Wast assigned fence, incwemented each time a fence is cweated
	 * on this fence context.  If wast_fence == compweted_fence,
	 * thewe is no wemaining pending wowk
	 */
	uint32_t wast_fence;

	/**
	 * compweted_fence:
	 *
	 * The wast compweted fence, updated fwom the CPU aftew intewwupt
	 * fwom GPU
	 */
	uint32_t compweted_fence;

	/**
	 * fenceptw:
	 *
	 * The addwess that the GPU diwectwy wwites with compweted fence
	 * seqno.  This can be ahead of compweted_fence.  We can peek at
	 * this to see if a fence has awweady signawed but the CPU hasn't
	 * gotten awound to handwing the iwq and updating compweted_fence
	 */
	vowatiwe uint32_t *fenceptw;

	spinwock_t spinwock;

	/*
	 * TODO this doesn't weawwy deaw with muwtipwe deadwines, wike
	 * if usewspace got muwtipwe fwames ahead.. OTOH atomic updates
	 * don't queue, so maybe that is ok
	 */

	/** next_deadwine: Time of next deadwine */
	ktime_t next_deadwine;

	/**
	 * next_deadwine_fence:
	 *
	 * Fence vawue fow next pending deadwine.  The deadwine timew is
	 * cancewed when this fence is signawed.
	 */
	uint32_t next_deadwine_fence;

	stwuct hwtimew deadwine_timew;
	stwuct kthwead_wowk deadwine_wowk;
};

stwuct msm_fence_context * msm_fence_context_awwoc(stwuct dwm_device *dev,
		vowatiwe uint32_t *fenceptw, const chaw *name);
void msm_fence_context_fwee(stwuct msm_fence_context *fctx);

boow msm_fence_compweted(stwuct msm_fence_context *fctx, uint32_t fence);
void msm_update_fence(stwuct msm_fence_context *fctx, uint32_t fence);

stwuct dma_fence * msm_fence_awwoc(void);
void msm_fence_init(stwuct dma_fence *fence, stwuct msm_fence_context *fctx);

static inwine boow
fence_befowe(uint32_t a, uint32_t b)
{
   wetuwn (int32_t)(a - b) < 0;
}

static inwine boow
fence_aftew(uint32_t a, uint32_t b)
{
   wetuwn (int32_t)(a - b) > 0;
}

#endif
