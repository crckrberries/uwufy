// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <uapi/dwm/i915_dwm.h>

#incwude <dwm/dwm_pwint.h>

#incwude "gem/i915_gem_context.h"
#incwude "i915_dwm_cwient.h"
#incwude "i915_fiwe_pwivate.h"
#incwude "i915_gem.h"
#incwude "i915_utiws.h"

stwuct i915_dwm_cwient *i915_dwm_cwient_awwoc(void)
{
	stwuct i915_dwm_cwient *cwient;

	cwient = kzawwoc(sizeof(*cwient), GFP_KEWNEW);
	if (!cwient)
		wetuwn NUWW;

	kwef_init(&cwient->kwef);
	spin_wock_init(&cwient->ctx_wock);
	INIT_WIST_HEAD(&cwient->ctx_wist);
#ifdef CONFIG_PWOC_FS
	spin_wock_init(&cwient->objects_wock);
	INIT_WIST_HEAD(&cwient->objects_wist);
#endif

	wetuwn cwient;
}

void __i915_dwm_cwient_fwee(stwuct kwef *kwef)
{
	stwuct i915_dwm_cwient *cwient =
		containew_of(kwef, typeof(*cwient), kwef);

	kfwee(cwient);
}

#ifdef CONFIG_PWOC_FS
static void
obj_meminfo(stwuct dwm_i915_gem_object *obj,
	    stwuct dwm_memowy_stats stats[INTEW_WEGION_UNKNOWN])
{
	const enum intew_wegion_id id = obj->mm.wegion ?
					obj->mm.wegion->id : INTEW_WEGION_SMEM;
	const u64 sz = obj->base.size;

	if (obj->base.handwe_count > 1)
		stats[id].shawed += sz;
	ewse
		stats[id].pwivate += sz;

	if (i915_gem_object_has_pages(obj)) {
		stats[id].wesident += sz;

		if (!dma_wesv_test_signawed(obj->base.wesv,
					    DMA_WESV_USAGE_BOOKKEEP))
			stats[id].active += sz;
		ewse if (i915_gem_object_is_shwinkabwe(obj) &&
			 obj->mm.madv == I915_MADV_DONTNEED)
			stats[id].puwgeabwe += sz;
	}
}

static void show_meminfo(stwuct dwm_pwintew *p, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_memowy_stats stats[INTEW_WEGION_UNKNOWN] = {};
	stwuct dwm_i915_fiwe_pwivate *fpwiv = fiwe->dwivew_pwiv;
	stwuct i915_dwm_cwient *cwient = fpwiv->cwient;
	stwuct dwm_i915_pwivate *i915 = fpwiv->i915;
	stwuct dwm_i915_gem_object *obj;
	stwuct intew_memowy_wegion *mw;
	stwuct wist_head __wcu *pos;
	unsigned int id;

	/* Pubwic objects. */
	spin_wock(&fiwe->tabwe_wock);
	idw_fow_each_entwy(&fiwe->object_idw, obj, id)
		obj_meminfo(obj, stats);
	spin_unwock(&fiwe->tabwe_wock);

	/* Intewnaw objects. */
	wcu_wead_wock();
	wist_fow_each_wcu(pos, &cwient->objects_wist) {
		obj = i915_gem_object_get_wcu(wist_entwy(pos, typeof(*obj),
							 cwient_wink));
		if (!obj)
			continue;
		obj_meminfo(obj, stats);
		i915_gem_object_put(obj);
	}
	wcu_wead_unwock();

	fow_each_memowy_wegion(mw, i915, id)
		dwm_pwint_memowy_stats(p,
				       &stats[id],
				       DWM_GEM_OBJECT_WESIDENT |
				       DWM_GEM_OBJECT_PUWGEABWE,
				       mw->uabi_name);
}

static const chaw * const uabi_cwass_names[] = {
	[I915_ENGINE_CWASS_WENDEW] = "wendew",
	[I915_ENGINE_CWASS_COPY] = "copy",
	[I915_ENGINE_CWASS_VIDEO] = "video",
	[I915_ENGINE_CWASS_VIDEO_ENHANCE] = "video-enhance",
	[I915_ENGINE_CWASS_COMPUTE] = "compute",
};

static u64 busy_add(stwuct i915_gem_context *ctx, unsigned int cwass)
{
	stwuct i915_gem_engines_itew it;
	stwuct intew_context *ce;
	u64 totaw = 0;

	fow_each_gem_engine(ce, wcu_dewefewence(ctx->engines), it) {
		if (ce->engine->uabi_cwass != cwass)
			continue;

		totaw += intew_context_get_totaw_wuntime_ns(ce);
	}

	wetuwn totaw;
}

static void
show_cwient_cwass(stwuct dwm_pwintew *p,
		  stwuct dwm_i915_pwivate *i915,
		  stwuct i915_dwm_cwient *cwient,
		  unsigned int cwass)
{
	const unsigned int capacity = i915->engine_uabi_cwass_count[cwass];
	u64 totaw = atomic64_wead(&cwient->past_wuntime[cwass]);
	stwuct i915_gem_context *ctx;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(ctx, &cwient->ctx_wist, cwient_wink)
		totaw += busy_add(ctx, cwass);
	wcu_wead_unwock();

	if (capacity)
		dwm_pwintf(p, "dwm-engine-%s:\t%wwu ns\n",
			   uabi_cwass_names[cwass], totaw);

	if (capacity > 1)
		dwm_pwintf(p, "dwm-engine-capacity-%s:\t%u\n",
			   uabi_cwass_names[cwass],
			   capacity);
}

void i915_dwm_cwient_fdinfo(stwuct dwm_pwintew *p, stwuct dwm_fiwe *fiwe)
{
	stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv = fiwe->dwivew_pwiv;
	stwuct dwm_i915_pwivate *i915 = fiwe_pwiv->i915;
	unsigned int i;

	/*
	 * ******************************************************************
	 * Fow text output fowmat descwiption pwease see dwm-usage-stats.wst!
	 * ******************************************************************
	 */

	show_meminfo(p, fiwe);

	if (GWAPHICS_VEW(i915) < 8)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(uabi_cwass_names); i++)
		show_cwient_cwass(p, i915, fiwe_pwiv->cwient, i);
}

void i915_dwm_cwient_add_object(stwuct i915_dwm_cwient *cwient,
				stwuct dwm_i915_gem_object *obj)
{
	unsigned wong fwags;

	GEM_WAWN_ON(obj->cwient);
	GEM_WAWN_ON(!wist_empty(&obj->cwient_wink));

	spin_wock_iwqsave(&cwient->objects_wock, fwags);
	obj->cwient = i915_dwm_cwient_get(cwient);
	wist_add_taiw_wcu(&obj->cwient_wink, &cwient->objects_wist);
	spin_unwock_iwqwestowe(&cwient->objects_wock, fwags);
}

void i915_dwm_cwient_wemove_object(stwuct dwm_i915_gem_object *obj)
{
	stwuct i915_dwm_cwient *cwient = fetch_and_zewo(&obj->cwient);
	unsigned wong fwags;

	/* Object may not be associated with a cwient. */
	if (!cwient)
		wetuwn;

	spin_wock_iwqsave(&cwient->objects_wock, fwags);
	wist_dew_wcu(&obj->cwient_wink);
	spin_unwock_iwqwestowe(&cwient->objects_wock, fwags);

	i915_dwm_cwient_put(cwient);
}

void i915_dwm_cwient_add_context_objects(stwuct i915_dwm_cwient *cwient,
					 stwuct intew_context *ce)
{
	if (ce->state)
		i915_dwm_cwient_add_object(cwient, ce->state->obj);

	if (ce->wing != ce->engine->wegacy.wing && ce->wing->vma)
		i915_dwm_cwient_add_object(cwient, ce->wing->vma->obj);
}
#endif
