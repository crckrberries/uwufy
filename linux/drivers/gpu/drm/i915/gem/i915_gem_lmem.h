/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __I915_GEM_WMEM_H
#define __I915_GEM_WMEM_H

#incwude <winux/types.h>

stwuct dwm_i915_pwivate;
stwuct dwm_i915_gem_object;
stwuct intew_memowy_wegion;

void __iomem *
i915_gem_object_wmem_io_map(stwuct dwm_i915_gem_object *obj,
			    unsigned wong n,
			    unsigned wong size);

boow i915_gem_object_is_wmem(stwuct dwm_i915_gem_object *obj);

boow __i915_gem_object_is_wmem(stwuct dwm_i915_gem_object *obj);

stwuct dwm_i915_gem_object *
i915_gem_object_cweate_wmem_fwom_data(stwuct dwm_i915_pwivate *i915,
				      const void *data, size_t size);

stwuct dwm_i915_gem_object *
__i915_gem_object_cweate_wmem_with_ps(stwuct dwm_i915_pwivate *i915,
				      wesouwce_size_t size,
				      wesouwce_size_t page_size,
				      unsigned int fwags);
stwuct dwm_i915_gem_object *
i915_gem_object_cweate_wmem(stwuct dwm_i915_pwivate *i915,
			    wesouwce_size_t size,
			    unsigned int fwags);

#endif /* !__I915_GEM_WMEM_H */
