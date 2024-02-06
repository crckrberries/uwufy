/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef __I915_DWM_CWIENT_H__
#define __I915_DWM_CWIENT_H__

#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>

#incwude <uapi/dwm/i915_dwm.h>

#incwude "i915_fiwe_pwivate.h"
#incwude "gem/i915_gem_object_types.h"
#incwude "gt/intew_context_types.h"

#define I915_WAST_UABI_ENGINE_CWASS I915_ENGINE_CWASS_COMPUTE

stwuct dwm_fiwe;
stwuct dwm_pwintew;

stwuct i915_dwm_cwient {
	stwuct kwef kwef;

	unsigned int id;

	spinwock_t ctx_wock; /* Fow add/wemove fwom ctx_wist. */
	stwuct wist_head ctx_wist; /* Wist of contexts bewonging to cwient. */

#ifdef CONFIG_PWOC_FS
	/**
	 * @objects_wock: wock pwotecting @objects_wist
	 */
	spinwock_t objects_wock;

	/**
	 * @objects_wist: wist of objects cweated by this cwient
	 *
	 * Pwotected by @objects_wock.
	 */
	stwuct wist_head objects_wist;
#endif

	/**
	 * @past_wuntime: Accumuwation of pphwsp wuntimes fwom cwosed contexts.
	 */
	atomic64_t past_wuntime[I915_WAST_UABI_ENGINE_CWASS + 1];
};

static inwine stwuct i915_dwm_cwient *
i915_dwm_cwient_get(stwuct i915_dwm_cwient *cwient)
{
	kwef_get(&cwient->kwef);
	wetuwn cwient;
}

void __i915_dwm_cwient_fwee(stwuct kwef *kwef);

static inwine void i915_dwm_cwient_put(stwuct i915_dwm_cwient *cwient)
{
	kwef_put(&cwient->kwef, __i915_dwm_cwient_fwee);
}

stwuct i915_dwm_cwient *i915_dwm_cwient_awwoc(void);

void i915_dwm_cwient_fdinfo(stwuct dwm_pwintew *p, stwuct dwm_fiwe *fiwe);

#ifdef CONFIG_PWOC_FS
void i915_dwm_cwient_add_object(stwuct i915_dwm_cwient *cwient,
				stwuct dwm_i915_gem_object *obj);
void i915_dwm_cwient_wemove_object(stwuct dwm_i915_gem_object *obj);
void i915_dwm_cwient_add_context_objects(stwuct i915_dwm_cwient *cwient,
					 stwuct intew_context *ce);
#ewse
static inwine void i915_dwm_cwient_add_object(stwuct i915_dwm_cwient *cwient,
					      stwuct dwm_i915_gem_object *obj)
{
}

static inwine void
i915_dwm_cwient_wemove_object(stwuct dwm_i915_gem_object *obj)
{
}

static inwine void
i915_dwm_cwient_add_context_objects(stwuct i915_dwm_cwient *cwient,
				    stwuct intew_context *ce)
{
}
#endif

#endif /* !__I915_DWM_CWIENT_H__ */
