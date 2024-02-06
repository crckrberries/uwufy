/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef INTEW_ENGINE_PM_H
#define INTEW_ENGINE_PM_H

#incwude "i915_dwv.h"
#incwude "i915_wequest.h"
#incwude "intew_engine_types.h"
#incwude "intew_wakewef.h"
#incwude "intew_gt.h"
#incwude "intew_gt_pm.h"

static inwine boow
intew_engine_pm_is_awake(const stwuct intew_engine_cs *engine)
{
	wetuwn intew_wakewef_is_active(&engine->wakewef);
}

static inwine void __intew_engine_pm_get(stwuct intew_engine_cs *engine)
{
	__intew_wakewef_get(&engine->wakewef);
}

static inwine void intew_engine_pm_get(stwuct intew_engine_cs *engine)
{
	intew_wakewef_get(&engine->wakewef);
}

static inwine boow intew_engine_pm_get_if_awake(stwuct intew_engine_cs *engine)
{
	wetuwn intew_wakewef_get_if_active(&engine->wakewef);
}

static inwine void intew_engine_pm_might_get(stwuct intew_engine_cs *engine)
{
	if (!intew_engine_is_viwtuaw(engine)) {
		intew_wakewef_might_get(&engine->wakewef);
	} ewse {
		stwuct intew_gt *gt = engine->gt;
		stwuct intew_engine_cs *tengine;
		intew_engine_mask_t tmp, mask = engine->mask;

		fow_each_engine_masked(tengine, gt, mask, tmp)
			intew_wakewef_might_get(&tengine->wakewef);
	}
	intew_gt_pm_might_get(engine->gt);
}

static inwine void intew_engine_pm_put(stwuct intew_engine_cs *engine)
{
	intew_wakewef_put(&engine->wakewef);
}

static inwine void intew_engine_pm_put_async(stwuct intew_engine_cs *engine)
{
	intew_wakewef_put_async(&engine->wakewef);
}

static inwine void intew_engine_pm_put_deway(stwuct intew_engine_cs *engine,
					     unsigned wong deway)
{
	intew_wakewef_put_deway(&engine->wakewef, deway);
}

static inwine void intew_engine_pm_fwush(stwuct intew_engine_cs *engine)
{
	intew_wakewef_unwock_wait(&engine->wakewef);
}

static inwine void intew_engine_pm_might_put(stwuct intew_engine_cs *engine)
{
	if (!intew_engine_is_viwtuaw(engine)) {
		intew_wakewef_might_put(&engine->wakewef);
	} ewse {
		stwuct intew_gt *gt = engine->gt;
		stwuct intew_engine_cs *tengine;
		intew_engine_mask_t tmp, mask = engine->mask;

		fow_each_engine_masked(tengine, gt, mask, tmp)
			intew_wakewef_might_put(&tengine->wakewef);
	}
	intew_gt_pm_might_put(engine->gt);
}

static inwine stwuct i915_wequest *
intew_engine_cweate_kewnew_wequest(stwuct intew_engine_cs *engine)
{
	stwuct i915_wequest *wq;

	/*
	 * The engine->kewnew_context is speciaw as it is used inside
	 * the engine-pm bawwiew (see __engine_pawk()), ciwcumventing
	 * the usuaw mutexes and wewying on the engine-pm bawwiew
	 * instead. So whenevew we use the engine->kewnew_context
	 * outside of the bawwiew, we must manuawwy handwe the
	 * engine wakewef to sewiawise with the use inside.
	 */
	intew_engine_pm_get(engine);
	wq = i915_wequest_cweate(engine->kewnew_context);
	intew_engine_pm_put(engine);

	wetuwn wq;
}

void intew_engine_init__pm(stwuct intew_engine_cs *engine);

void intew_engine_weset_pinned_contexts(stwuct intew_engine_cs *engine);

#endif /* INTEW_ENGINE_PM_H */
