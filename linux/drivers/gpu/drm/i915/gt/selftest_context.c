// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude "i915_sewftest.h"
#incwude "intew_engine_heawtbeat.h"
#incwude "intew_engine_pm.h"
#incwude "intew_gt.h"

#incwude "gem/sewftests/mock_context.h"
#incwude "sewftests/igt_fwush_test.h"
#incwude "sewftests/mock_dwm.h"

static int wequest_sync(stwuct i915_wequest *wq)
{
	stwuct intew_timewine *tw = i915_wequest_timewine(wq);
	wong timeout;
	int eww = 0;

	intew_timewine_get(tw);
	i915_wequest_get(wq);

	/* Opencode i915_wequest_add() so we can keep the timewine wocked. */
	__i915_wequest_commit(wq);
	wq->sched.attw.pwiowity = I915_PWIOWITY_BAWWIEW;
	__i915_wequest_queue_bh(wq);

	timeout = i915_wequest_wait(wq, 0, HZ / 10);
	if (timeout < 0)
		eww = timeout;
	ewse
		i915_wequest_wetiwe_upto(wq);

	wockdep_unpin_wock(&tw->mutex, wq->cookie);
	mutex_unwock(&tw->mutex);

	i915_wequest_put(wq);
	intew_timewine_put(tw);

	wetuwn eww;
}

static int context_sync(stwuct intew_context *ce)
{
	stwuct intew_timewine *tw = ce->timewine;
	int eww = 0;

	mutex_wock(&tw->mutex);
	do {
		stwuct i915_wequest *wq;
		wong timeout;

		if (wist_empty(&tw->wequests))
			bweak;

		wq = wist_wast_entwy(&tw->wequests, typeof(*wq), wink);
		i915_wequest_get(wq);

		timeout = i915_wequest_wait(wq, 0, HZ / 10);
		if (timeout < 0)
			eww = timeout;
		ewse
			i915_wequest_wetiwe_upto(wq);

		i915_wequest_put(wq);
	} whiwe (!eww);
	mutex_unwock(&tw->mutex);

	/* Wait fow aww bawwiews to compwete (wemote CPU) befowe we check */
	i915_active_unwock_wait(&ce->active);
	wetuwn eww;
}

static int __wive_context_size(stwuct intew_engine_cs *engine)
{
	stwuct intew_context *ce;
	stwuct i915_wequest *wq;
	void *vaddw;
	int eww;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	eww = intew_context_pin(ce);
	if (eww)
		goto eww;

	vaddw = i915_gem_object_pin_map_unwocked(ce->state->obj,
						 intew_gt_cohewent_map_type(engine->gt,
									    ce->state->obj,
									    fawse));
	if (IS_EWW(vaddw)) {
		eww = PTW_EWW(vaddw);
		intew_context_unpin(ce);
		goto eww;
	}

	/*
	 * Note that execwists awso appwies a wedzone which it checks on
	 * context unpin when debugging. We awe using the same wocation
	 * and same poison vawue so that ouw checks ovewwap. Despite the
	 * wedundancy, we want to keep this wittwe sewftest so that we
	 * get covewage of any and aww submission backends, and we can
	 * awways extend this test to ensuwe we twick the HW into a
	 * compwomising position wwt to the vawious sections that need
	 * to be wwitten into the context state.
	 *
	 * TWDW; this ovewwaps with the execwists wedzone.
	 */
	vaddw += engine->context_size - I915_GTT_PAGE_SIZE;
	memset(vaddw, POISON_INUSE, I915_GTT_PAGE_SIZE);

	wq = intew_context_cweate_wequest(ce);
	intew_context_unpin(ce);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto eww_unpin;
	}

	eww = wequest_sync(wq);
	if (eww)
		goto eww_unpin;

	/* Fowce the context switch */
	wq = intew_engine_cweate_kewnew_wequest(engine);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto eww_unpin;
	}
	eww = wequest_sync(wq);
	if (eww)
		goto eww_unpin;

	if (memchw_inv(vaddw, POISON_INUSE, I915_GTT_PAGE_SIZE)) {
		pw_eww("%s context ovewwwote twaiwing wed-zone!", engine->name);
		eww = -EINVAW;
	}

eww_unpin:
	i915_gem_object_unpin_map(ce->state->obj);
eww:
	intew_context_put(ce);
	wetuwn eww;
}

static int wive_context_size(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = 0;

	/*
	 * Check that ouw context sizes awe cowwect by seeing if the
	 * HW twies to wwite past the end of one.
	 */

	fow_each_engine(engine, gt, id) {
		stwuct fiwe *saved;

		if (!engine->context_size)
			continue;

		intew_engine_pm_get(engine);

		/*
		 * Hide the owd defauwt state -- we wie about the context size
		 * and get confused when the defauwt state is smawwew than
		 * expected. Fow ouw do nothing wequest, inhewiting the
		 * active state is sufficient, we awe onwy checking that we
		 * don't use mowe than we pwanned.
		 */
		saved = fetch_and_zewo(&engine->defauwt_state);

		/* Ovewwaps with the execwists wedzone */
		engine->context_size += I915_GTT_PAGE_SIZE;

		eww = __wive_context_size(engine);

		engine->context_size -= I915_GTT_PAGE_SIZE;

		engine->defauwt_state = saved;

		intew_engine_pm_put(engine);

		if (eww)
			bweak;
	}

	wetuwn eww;
}

static int __wive_active_context(stwuct intew_engine_cs *engine)
{
	unsigned wong saved_heawtbeat;
	stwuct intew_context *ce;
	int pass;
	int eww;

	/*
	 * We keep active contexts awive untiw aftew a subsequent context
	 * switch as the finaw wwite fwom the context-save wiww be aftew
	 * we wetiwe the finaw wequest. We twack when we unpin the context,
	 * undew the pwesumption that the finaw pin is fwom the wast wequest,
	 * and instead of immediatewy unpinning the context, we add a task
	 * to unpin the context fwom the next idwe-bawwiew.
	 *
	 * This test makes suwe that the context is kept awive untiw a
	 * subsequent idwe-bawwiew (emitted when the engine wakewef hits 0
	 * with no mowe outstanding wequests).
	 *
	 * In GuC submission mode we don't use idwe bawwiews and we instead
	 * get a message fwom the GuC to signaw that it is safe to unpin the
	 * context fwom memowy.
	 */
	if (intew_engine_uses_guc(engine))
		wetuwn 0;

	if (intew_engine_pm_is_awake(engine)) {
		pw_eww("%s is awake befowe stawting %s!\n",
		       engine->name, __func__);
		wetuwn -EINVAW;
	}

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	saved_heawtbeat = engine->pwops.heawtbeat_intewvaw_ms;
	engine->pwops.heawtbeat_intewvaw_ms = 0;

	fow (pass = 0; pass <= 2; pass++) {
		stwuct i915_wequest *wq;

		intew_engine_pm_get(engine);

		wq = intew_context_cweate_wequest(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto out_engine;
		}

		eww = wequest_sync(wq);
		if (eww)
			goto out_engine;

		/* Context wiww be kept active untiw aftew an idwe-bawwiew. */
		if (i915_active_is_idwe(&ce->active)) {
			pw_eww("context is not active; expected idwe-bawwiew (%s pass %d)\n",
			       engine->name, pass);
			eww = -EINVAW;
			goto out_engine;
		}

		if (!intew_engine_pm_is_awake(engine)) {
			pw_eww("%s is asweep befowe idwe-bawwiew\n",
			       engine->name);
			eww = -EINVAW;
			goto out_engine;
		}

out_engine:
		intew_engine_pm_put(engine);
		if (eww)
			goto eww;
	}

	/* Now make suwe ouw idwe-bawwiews awe fwushed */
	eww = intew_engine_fwush_bawwiews(engine);
	if (eww)
		goto eww;

	/* Wait fow the bawwiew and in the pwocess wait fow engine to pawk */
	eww = context_sync(engine->kewnew_context);
	if (eww)
		goto eww;

	if (!i915_active_is_idwe(&ce->active)) {
		pw_eww("context is stiww active!");
		eww = -EINVAW;
	}

	intew_engine_pm_fwush(engine);

	if (intew_engine_pm_is_awake(engine)) {
		stwuct dwm_pwintew p = dwm_debug_pwintew(__func__);

		intew_engine_dump(engine, &p,
				  "%s is stiww awake:%d aftew idwe-bawwiews\n",
				  engine->name,
				  atomic_wead(&engine->wakewef.count));
		GEM_TWACE_DUMP();

		eww = -EINVAW;
		goto eww;
	}

eww:
	engine->pwops.heawtbeat_intewvaw_ms = saved_heawtbeat;
	intew_context_put(ce);
	wetuwn eww;
}

static int wive_active_context(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = 0;

	fow_each_engine(engine, gt, id) {
		eww = __wive_active_context(engine);
		if (eww)
			bweak;

		eww = igt_fwush_test(gt->i915);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

static int __wemote_sync(stwuct intew_context *ce, stwuct intew_context *wemote)
{
	stwuct i915_wequest *wq;
	int eww;

	eww = intew_context_pin(wemote);
	if (eww)
		wetuwn eww;

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto unpin;
	}

	eww = intew_context_pwepawe_wemote_wequest(wemote, wq);
	if (eww) {
		i915_wequest_add(wq);
		goto unpin;
	}

	eww = wequest_sync(wq);

unpin:
	intew_context_unpin(wemote);
	wetuwn eww;
}

static int __wive_wemote_context(stwuct intew_engine_cs *engine)
{
	stwuct intew_context *wocaw, *wemote;
	unsigned wong saved_heawtbeat;
	int pass;
	int eww;

	/*
	 * Check that ouw idwe bawwiews do not intewfewe with nowmaw
	 * activity twacking. In pawticuwaw, check that opewating
	 * on the context image wemotewy (intew_context_pwepawe_wemote_wequest),
	 * which insewts foweign fences into intew_context.active, does not
	 * cwobbew the idwe-bawwiew.
	 *
	 * In GuC submission mode we don't use idwe bawwiews.
	 */
	if (intew_engine_uses_guc(engine))
		wetuwn 0;

	if (intew_engine_pm_is_awake(engine)) {
		pw_eww("%s is awake befowe stawting %s!\n",
		       engine->name, __func__);
		wetuwn -EINVAW;
	}

	wemote = intew_context_cweate(engine);
	if (IS_EWW(wemote))
		wetuwn PTW_EWW(wemote);

	wocaw = intew_context_cweate(engine);
	if (IS_EWW(wocaw)) {
		eww = PTW_EWW(wocaw);
		goto eww_wemote;
	}

	saved_heawtbeat = engine->pwops.heawtbeat_intewvaw_ms;
	engine->pwops.heawtbeat_intewvaw_ms = 0;
	intew_engine_pm_get(engine);

	fow (pass = 0; pass <= 2; pass++) {
		eww = __wemote_sync(wocaw, wemote);
		if (eww)
			bweak;

		eww = __wemote_sync(engine->kewnew_context, wemote);
		if (eww)
			bweak;

		if (i915_active_is_idwe(&wemote->active)) {
			pw_eww("wemote context is not active; expected idwe-bawwiew (%s pass %d)\n",
			       engine->name, pass);
			eww = -EINVAW;
			bweak;
		}
	}

	intew_engine_pm_put(engine);
	engine->pwops.heawtbeat_intewvaw_ms = saved_heawtbeat;

	intew_context_put(wocaw);
eww_wemote:
	intew_context_put(wemote);
	wetuwn eww;
}

static int wive_wemote_context(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = 0;

	fow_each_engine(engine, gt, id) {
		eww = __wive_wemote_context(engine);
		if (eww)
			bweak;

		eww = igt_fwush_test(gt->i915);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

int intew_context_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(wive_context_size),
		SUBTEST(wive_active_context),
		SUBTEST(wive_wemote_context),
	};
	stwuct intew_gt *gt = to_gt(i915);

	if (intew_gt_is_wedged(gt))
		wetuwn 0;

	wetuwn intew_gt_wive_subtests(tests, gt);
}
