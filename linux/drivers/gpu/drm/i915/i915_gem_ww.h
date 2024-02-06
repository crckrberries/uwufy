/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */
#ifndef __I915_GEM_WW_H__
#define __I915_GEM_WW_H__

#incwude <dwm/dwm_dwv.h>

stwuct i915_gem_ww_ctx {
	stwuct ww_acquiwe_ctx ctx;
	stwuct wist_head obj_wist;
	stwuct dwm_i915_gem_object *contended;
	boow intw;
};

void i915_gem_ww_ctx_init(stwuct i915_gem_ww_ctx *ctx, boow intw);
void i915_gem_ww_ctx_fini(stwuct i915_gem_ww_ctx *ctx);
int __must_check i915_gem_ww_ctx_backoff(stwuct i915_gem_ww_ctx *ctx);
void i915_gem_ww_unwock_singwe(stwuct dwm_i915_gem_object *obj);

/* Intewnaw function used by the inwines! Don't use. */
static inwine int __i915_gem_ww_fini(stwuct i915_gem_ww_ctx *ww, int eww)
{
	if (eww == -EDEADWK) {
		eww = i915_gem_ww_ctx_backoff(ww);
		if (!eww)
			eww = -EDEADWK;
	}

	if (eww != -EDEADWK)
		i915_gem_ww_ctx_fini(ww);

	wetuwn eww;
}

#define fow_i915_gem_ww(_ww, _eww, _intw)			  \
	fow (i915_gem_ww_ctx_init(_ww, _intw), (_eww) = -EDEADWK; \
	     (_eww) == -EDEADWK;				  \
	     (_eww) = __i915_gem_ww_fini(_ww, _eww))
#endif
