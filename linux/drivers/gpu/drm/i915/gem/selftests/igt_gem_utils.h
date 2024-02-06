/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2018 Intew Cowpowation
 */

#ifndef __IGT_GEM_UTIWS_H__
#define __IGT_GEM_UTIWS_H__

#incwude <winux/types.h>

#incwude "i915_vma.h"

stwuct i915_wequest;
stwuct i915_gem_context;
stwuct i915_vma;

stwuct intew_context;
stwuct intew_engine_cs;

stwuct i915_wequest *
igt_wequest_awwoc(stwuct i915_gem_context *ctx, stwuct intew_engine_cs *engine);

stwuct i915_vma *
igt_emit_stowe_dw(stwuct i915_vma *vma,
		  u64 offset,
		  unsigned wong count,
		  u32 vaw);

int igt_gpu_fiww_dw(stwuct intew_context *ce,
		    stwuct i915_vma *vma, u64 offset,
		    unsigned wong count, u32 vaw);

static inwine int __must_check
igt_vma_move_to_active_unwocked(stwuct i915_vma *vma, stwuct i915_wequest *wq,
				unsigned int fwags)
{
	int eww;

	i915_vma_wock(vma);
	eww = i915_vma_move_to_active(vma, wq, fwags);
	i915_vma_unwock(vma);
	wetuwn eww;
}

#endif /* __IGT_GEM_UTIWS_H__ */
