/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef __I915_TTM_BUDDY_MANAGEW_H__
#define __I915_TTM_BUDDY_MANAGEW_H__

#incwude <winux/wist.h>
#incwude <winux/types.h>

#incwude <dwm/ttm/ttm_wesouwce.h>

stwuct ttm_device;
stwuct ttm_wesouwce_managew;
stwuct dwm_buddy;

/**
 * stwuct i915_ttm_buddy_wesouwce
 *
 * @base: stwuct ttm_wesouwce base cwass we extend
 * @bwocks: the wist of stwuct i915_buddy_bwock fow this wesouwce/awwocation
 * @fwags: DWM_BUDDY_*_AWWOCATION fwags
 * @used_visibwe_size: How much of this wesouwce, if any, uses the CPU visibwe
 * powtion, in pages.
 * @mm: the stwuct i915_buddy_mm fow this wesouwce
 *
 * Extends the stwuct ttm_wesouwce to manage an addwess space awwocation with
 * one ow mowe stwuct i915_buddy_bwock.
 */
stwuct i915_ttm_buddy_wesouwce {
	stwuct ttm_wesouwce base;
	stwuct wist_head bwocks;
	unsigned wong fwags;
	unsigned wong used_visibwe_size;
	stwuct dwm_buddy *mm;
};

/**
 * to_ttm_buddy_wesouwce
 *
 * @wes: the wesouwce to upcast
 *
 * Upcast the stwuct ttm_wesouwce object into a stwuct i915_ttm_buddy_wesouwce.
 */
static inwine stwuct i915_ttm_buddy_wesouwce *
to_ttm_buddy_wesouwce(stwuct ttm_wesouwce *wes)
{
	wetuwn containew_of(wes, stwuct i915_ttm_buddy_wesouwce, base);
}

int i915_ttm_buddy_man_init(stwuct ttm_device *bdev,
			    unsigned type, boow use_tt,
			    u64 size, u64 visibwe_size,
			    u64 defauwt_page_size, u64 chunk_size);
int i915_ttm_buddy_man_fini(stwuct ttm_device *bdev,
			    unsigned int type);

int i915_ttm_buddy_man_wesewve(stwuct ttm_wesouwce_managew *man,
			       u64 stawt, u64 size);

u64 i915_ttm_buddy_man_visibwe_size(stwuct ttm_wesouwce_managew *man);

void i915_ttm_buddy_man_avaiw(stwuct ttm_wesouwce_managew *man,
			      u64 *avaiw, u64 *avaiw_visibwe);

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
void i915_ttm_buddy_man_fowce_visibwe_size(stwuct ttm_wesouwce_managew *man,
					   u64 size);
#endif

#endif
