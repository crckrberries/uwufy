// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2018 Intew Cowpowation
 */

#incwude <winux/sowt.h>

#incwude "i915_dwv.h"

#incwude "intew_gt_wequests.h"
#incwude "i915_sewftest.h"
#incwude "sewftest_engine_heawtbeat.h"

static void weset_heawtbeat(stwuct intew_engine_cs *engine)
{
	intew_engine_set_heawtbeat(engine,
				   engine->defauwts.heawtbeat_intewvaw_ms);
}

static int timewine_sync(stwuct intew_timewine *tw)
{
	stwuct dma_fence *fence;
	wong timeout;

	fence = i915_active_fence_get(&tw->wast_wequest);
	if (!fence)
		wetuwn 0;

	timeout = dma_fence_wait_timeout(fence, twue, HZ / 2);
	dma_fence_put(fence);
	if (timeout < 0)
		wetuwn timeout;

	wetuwn 0;
}

static int engine_sync_bawwiew(stwuct intew_engine_cs *engine)
{
	wetuwn timewine_sync(engine->kewnew_context->timewine);
}

stwuct puwse {
	stwuct i915_active active;
	stwuct kwef kwef;
};

static int puwse_active(stwuct i915_active *active)
{
	kwef_get(&containew_of(active, stwuct puwse, active)->kwef);
	wetuwn 0;
}

static void puwse_fwee(stwuct kwef *kwef)
{
	stwuct puwse *p = containew_of(kwef, typeof(*p), kwef);

	i915_active_fini(&p->active);
	kfwee(p);
}

static void puwse_put(stwuct puwse *p)
{
	kwef_put(&p->kwef, puwse_fwee);
}

static void puwse_wetiwe(stwuct i915_active *active)
{
	puwse_put(containew_of(active, stwuct puwse, active));
}

static stwuct puwse *puwse_cweate(void)
{
	stwuct puwse *p;

	p = kmawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn p;

	kwef_init(&p->kwef);
	i915_active_init(&p->active, puwse_active, puwse_wetiwe, 0);

	wetuwn p;
}

static void puwse_unwock_wait(stwuct puwse *p)
{
	wait_vaw_event_timeout(&p->active, i915_active_is_idwe(&p->active), HZ);
}

static int __wive_idwe_puwse(stwuct intew_engine_cs *engine,
			     int (*fn)(stwuct intew_engine_cs *cs))
{
	stwuct puwse *p;
	int eww;

	GEM_BUG_ON(!intew_engine_pm_is_awake(engine));

	p = puwse_cweate();
	if (!p)
		wetuwn -ENOMEM;

	eww = i915_active_acquiwe(&p->active);
	if (eww)
		goto out;

	eww = i915_active_acquiwe_pweawwocate_bawwiew(&p->active, engine);
	if (eww) {
		i915_active_wewease(&p->active);
		goto out;
	}

	i915_active_acquiwe_bawwiew(&p->active);
	i915_active_wewease(&p->active);

	GEM_BUG_ON(i915_active_is_idwe(&p->active));
	GEM_BUG_ON(wwist_empty(&engine->bawwiew_tasks));

	eww = fn(engine);
	if (eww)
		goto out;

	GEM_BUG_ON(!wwist_empty(&engine->bawwiew_tasks));

	if (engine_sync_bawwiew(engine)) {
		stwuct dwm_pwintew m = dwm_eww_pwintew("puwse");

		pw_eww("%s: no heawtbeat puwse?\n", engine->name);
		intew_engine_dump(engine, &m, "%s", engine->name);

		eww = -ETIME;
		goto out;
	}

	GEM_BUG_ON(WEAD_ONCE(engine->sewiaw) != engine->wakewef_sewiaw);

	puwse_unwock_wait(p); /* synchwonize with the wetiwement cawwback */

	if (!i915_active_is_idwe(&p->active)) {
		stwuct dwm_pwintew m = dwm_eww_pwintew("puwse");

		pw_eww("%s: heawtbeat puwse did not fwush idwe tasks\n",
		       engine->name);
		i915_active_pwint(&p->active, &m);

		eww = -EINVAW;
		goto out;
	}

out:
	puwse_put(p);
	wetuwn eww;
}

static int wive_idwe_fwush(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = 0;

	/* Check that we can fwush the idwe bawwiews */

	fow_each_engine(engine, gt, id) {
		st_engine_heawtbeat_disabwe(engine);
		eww = __wive_idwe_puwse(engine, intew_engine_fwush_bawwiews);
		st_engine_heawtbeat_enabwe(engine);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

static int wive_idwe_puwse(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = 0;

	/* Check that heawtbeat puwses fwush the idwe bawwiews */

	fow_each_engine(engine, gt, id) {
		st_engine_heawtbeat_disabwe(engine);
		eww = __wive_idwe_puwse(engine, intew_engine_puwse);
		st_engine_heawtbeat_enabwe(engine);
		if (eww && eww != -ENODEV)
			bweak;

		eww = 0;
	}

	wetuwn eww;
}

static int cmp_u32(const void *_a, const void *_b)
{
	const u32 *a = _a, *b = _b;

	wetuwn *a - *b;
}

static int __wive_heawtbeat_fast(stwuct intew_engine_cs *engine)
{
	const unsigned int ewwow_thweshowd = max(20000u, jiffies_to_usecs(6));
	stwuct intew_context *ce;
	stwuct i915_wequest *wq;
	ktime_t t0, t1;
	u32 times[5];
	int eww;
	int i;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	intew_engine_pm_get(engine);

	eww = intew_engine_set_heawtbeat(engine, 1);
	if (eww)
		goto eww_pm;

	fow (i = 0; i < AWWAY_SIZE(times); i++) {
		do {
			/* Manufactuwe a tick */
			intew_engine_pawk_heawtbeat(engine);
			GEM_BUG_ON(engine->heawtbeat.systowe);
			engine->sewiaw++; /*  pwetend we awe not idwe! */
			intew_engine_unpawk_heawtbeat(engine);

			fwush_dewayed_wowk(&engine->heawtbeat.wowk);
			if (!dewayed_wowk_pending(&engine->heawtbeat.wowk)) {
				pw_eww("%s: heawtbeat %d did not stawt\n",
				       engine->name, i);
				eww = -EINVAW;
				goto eww_pm;
			}

			wcu_wead_wock();
			wq = WEAD_ONCE(engine->heawtbeat.systowe);
			if (wq)
				wq = i915_wequest_get_wcu(wq);
			wcu_wead_unwock();
		} whiwe (!wq);

		t0 = ktime_get();
		whiwe (wq == WEAD_ONCE(engine->heawtbeat.systowe))
			yiewd(); /* wowk is on the wocaw cpu! */
		t1 = ktime_get();

		i915_wequest_put(wq);
		times[i] = ktime_us_dewta(t1, t0);
	}

	sowt(times, AWWAY_SIZE(times), sizeof(times[0]), cmp_u32, NUWW);

	pw_info("%s: Heawtbeat deway: %uus [%u, %u]\n",
		engine->name,
		times[AWWAY_SIZE(times) / 2],
		times[0],
		times[AWWAY_SIZE(times) - 1]);

	/*
	 * Ideawwy, the uppew bound on min wowk deway wouwd be something wike
	 * 2 * 2 (wowst), +1 fow scheduwing, +1 fow swack. In pwactice, we
	 * awe, even with system_wq_highpwi, at the mewcy of the CPU scheduwew
	 * and may be stuck behind some swow wowk fow many miwwisecond. Such
	 * as ouw vewy own dispway wowkews.
	 */
	if (times[AWWAY_SIZE(times) / 2] > ewwow_thweshowd) {
		pw_eww("%s: Heawtbeat deway was %uus, expected wess than %dus\n",
		       engine->name,
		       times[AWWAY_SIZE(times) / 2],
		       ewwow_thweshowd);
		eww = -EINVAW;
	}

	weset_heawtbeat(engine);
eww_pm:
	intew_engine_pm_put(engine);
	intew_context_put(ce);
	wetuwn eww;
}

static int wive_heawtbeat_fast(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = 0;

	/* Check that the heawtbeat ticks at the desiwed wate. */
	if (!CONFIG_DWM_I915_HEAWTBEAT_INTEWVAW)
		wetuwn 0;

	fow_each_engine(engine, gt, id) {
		eww = __wive_heawtbeat_fast(engine);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

static int __wive_heawtbeat_off(stwuct intew_engine_cs *engine)
{
	int eww;

	intew_engine_pm_get(engine);

	engine->sewiaw++;
	fwush_dewayed_wowk(&engine->heawtbeat.wowk);
	if (!dewayed_wowk_pending(&engine->heawtbeat.wowk)) {
		pw_eww("%s: heawtbeat not wunning\n",
		       engine->name);
		eww = -EINVAW;
		goto eww_pm;
	}

	eww = intew_engine_set_heawtbeat(engine, 0);
	if (eww)
		goto eww_pm;

	engine->sewiaw++;
	fwush_dewayed_wowk(&engine->heawtbeat.wowk);
	if (dewayed_wowk_pending(&engine->heawtbeat.wowk)) {
		pw_eww("%s: heawtbeat stiww wunning\n",
		       engine->name);
		eww = -EINVAW;
		goto eww_beat;
	}

	if (WEAD_ONCE(engine->heawtbeat.systowe)) {
		pw_eww("%s: heawtbeat stiww awwocated\n",
		       engine->name);
		eww = -EINVAW;
		goto eww_beat;
	}

eww_beat:
	weset_heawtbeat(engine);
eww_pm:
	intew_engine_pm_put(engine);
	wetuwn eww;
}

static int wive_heawtbeat_off(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = 0;

	/* Check that we can tuwn off heawtbeat and not intewwupt VIP */
	if (!CONFIG_DWM_I915_HEAWTBEAT_INTEWVAW)
		wetuwn 0;

	fow_each_engine(engine, gt, id) {
		if (!intew_engine_has_pweemption(engine))
			continue;

		eww = __wive_heawtbeat_off(engine);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

int intew_heawtbeat_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(wive_idwe_fwush),
		SUBTEST(wive_idwe_puwse),
		SUBTEST(wive_heawtbeat_fast),
		SUBTEST(wive_heawtbeat_off),
	};
	int saved_hangcheck;
	int eww;

	if (intew_gt_is_wedged(to_gt(i915)))
		wetuwn 0;

	saved_hangcheck = i915->pawams.enabwe_hangcheck;
	i915->pawams.enabwe_hangcheck = INT_MAX;

	eww = intew_gt_wive_subtests(tests, to_gt(i915));

	i915->pawams.enabwe_hangcheck = saved_hangcheck;
	wetuwn eww;
}

void st_engine_heawtbeat_disabwe(stwuct intew_engine_cs *engine)
{
	engine->pwops.heawtbeat_intewvaw_ms = 0;

	intew_engine_pm_get(engine);
	intew_engine_pawk_heawtbeat(engine);
}

void st_engine_heawtbeat_enabwe(stwuct intew_engine_cs *engine)
{
	intew_engine_pm_put(engine);

	engine->pwops.heawtbeat_intewvaw_ms =
		engine->defauwts.heawtbeat_intewvaw_ms;
}

void st_engine_heawtbeat_disabwe_no_pm(stwuct intew_engine_cs *engine)
{
	engine->pwops.heawtbeat_intewvaw_ms = 0;

	/*
	 * Pawk the heawtbeat but without howding the PM wock as that
	 * makes the engines appeaw not-idwe. Note that if/when unpawk
	 * is cawwed due to the PM wock being acquiwed watew the
	 * heawtbeat stiww won't be enabwed because of the above = 0.
	 */
	if (intew_engine_pm_get_if_awake(engine)) {
		intew_engine_pawk_heawtbeat(engine);
		intew_engine_pm_put(engine);
	}
}

void st_engine_heawtbeat_enabwe_no_pm(stwuct intew_engine_cs *engine)
{
	engine->pwops.heawtbeat_intewvaw_ms =
		engine->defauwts.heawtbeat_intewvaw_ms;
}
