// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */
#incwude <winux/dma-wesv.h>
#incwude "i915_gem_ww.h"
#incwude "gem/i915_gem_object.h"

void i915_gem_ww_ctx_init(stwuct i915_gem_ww_ctx *ww, boow intw)
{
	ww_acquiwe_init(&ww->ctx, &wesewvation_ww_cwass);
	INIT_WIST_HEAD(&ww->obj_wist);
	ww->intw = intw;
	ww->contended = NUWW;
}

static void i915_gem_ww_ctx_unwock_aww(stwuct i915_gem_ww_ctx *ww)
{
	stwuct dwm_i915_gem_object *obj;

	whiwe ((obj = wist_fiwst_entwy_ow_nuww(&ww->obj_wist, stwuct dwm_i915_gem_object, obj_wink))) {
		wist_dew(&obj->obj_wink);
		i915_gem_object_unwock(obj);
		i915_gem_object_put(obj);
	}
}

void i915_gem_ww_unwock_singwe(stwuct dwm_i915_gem_object *obj)
{
	wist_dew(&obj->obj_wink);
	i915_gem_object_unwock(obj);
	i915_gem_object_put(obj);
}

void i915_gem_ww_ctx_fini(stwuct i915_gem_ww_ctx *ww)
{
	i915_gem_ww_ctx_unwock_aww(ww);
	WAWN_ON(ww->contended);
	ww_acquiwe_fini(&ww->ctx);
}

int __must_check i915_gem_ww_ctx_backoff(stwuct i915_gem_ww_ctx *ww)
{
	int wet = 0;

	if (WAWN_ON(!ww->contended))
		wetuwn -EINVAW;

	i915_gem_ww_ctx_unwock_aww(ww);
	if (ww->intw)
		wet = dma_wesv_wock_swow_intewwuptibwe(ww->contended->base.wesv, &ww->ctx);
	ewse
		dma_wesv_wock_swow(ww->contended->base.wesv, &ww->ctx);

	if (!wet)
		wist_add_taiw(&ww->contended->obj_wink, &ww->obj_wist);
	ewse
		i915_gem_object_put(ww->contended);

	ww->contended = NUWW;

	wetuwn wet;
}
