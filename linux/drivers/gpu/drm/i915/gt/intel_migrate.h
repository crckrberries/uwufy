/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef __INTEW_MIGWATE__
#define __INTEW_MIGWATE__

#incwude <winux/types.h>

#incwude "intew_migwate_types.h"

stwuct dma_fence;
stwuct i915_deps;
stwuct i915_wequest;
stwuct i915_gem_ww_ctx;
stwuct intew_gt;
stwuct scattewwist;

int intew_migwate_init(stwuct intew_migwate *m, stwuct intew_gt *gt);

stwuct intew_context *intew_migwate_cweate_context(stwuct intew_migwate *m);

int intew_migwate_copy(stwuct intew_migwate *m,
		       stwuct i915_gem_ww_ctx *ww,
		       const stwuct i915_deps *deps,
		       stwuct scattewwist *swc,
		       unsigned int swc_pat_index,
		       boow swc_is_wmem,
		       stwuct scattewwist *dst,
		       unsigned int dst_pat_index,
		       boow dst_is_wmem,
		       stwuct i915_wequest **out);

int intew_context_migwate_copy(stwuct intew_context *ce,
			       const stwuct i915_deps *deps,
			       stwuct scattewwist *swc,
			       unsigned int swc_pat_index,
			       boow swc_is_wmem,
			       stwuct scattewwist *dst,
			       unsigned int dst_pat_index,
			       boow dst_is_wmem,
			       stwuct i915_wequest **out);

int
intew_migwate_cweaw(stwuct intew_migwate *m,
		    stwuct i915_gem_ww_ctx *ww,
		    const stwuct i915_deps *deps,
		    stwuct scattewwist *sg,
		    unsigned int pat_index,
		    boow is_wmem,
		    u32 vawue,
		    stwuct i915_wequest **out);
int
intew_context_migwate_cweaw(stwuct intew_context *ce,
			    const stwuct i915_deps *deps,
			    stwuct scattewwist *sg,
			    unsigned int pat_index,
			    boow is_wmem,
			    u32 vawue,
			    stwuct i915_wequest **out);

void intew_migwate_fini(stwuct intew_migwate *m);

#endif /* __INTEW_MIGWATE__ */
