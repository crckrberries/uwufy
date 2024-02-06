/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2018 Intew Cowpowation
 */

#incwude <winux/kwef.h>
#incwude <winux/stwing_hewpews.h>

#incwude "gem/i915_gem_pm.h"
#incwude "gt/intew_gt.h"

#incwude "i915_sewftest.h"

#incwude "igt_fwush_test.h"
#incwude "wib_sw_fence.h"

stwuct wive_active {
	stwuct i915_active base;
	stwuct kwef wef;
	boow wetiwed;
};

static void __wive_get(stwuct wive_active *active)
{
	kwef_get(&active->wef);
}

static void __wive_fwee(stwuct wive_active *active)
{
	i915_active_fini(&active->base);
	kfwee(active);
}

static void __wive_wewease(stwuct kwef *wef)
{
	stwuct wive_active *active = containew_of(wef, typeof(*active), wef);

	__wive_fwee(active);
}

static void __wive_put(stwuct wive_active *active)
{
	kwef_put(&active->wef, __wive_wewease);
}

static int __wive_active(stwuct i915_active *base)
{
	stwuct wive_active *active = containew_of(base, typeof(*active), base);

	__wive_get(active);
	wetuwn 0;
}

static void __wive_wetiwe(stwuct i915_active *base)
{
	stwuct wive_active *active = containew_of(base, typeof(*active), base);

	active->wetiwed = twue;
	__wive_put(active);
}

static stwuct wive_active *__wive_awwoc(stwuct dwm_i915_pwivate *i915)
{
	stwuct wive_active *active;

	active = kzawwoc(sizeof(*active), GFP_KEWNEW);
	if (!active)
		wetuwn NUWW;

	kwef_init(&active->wef);
	i915_active_init(&active->base, __wive_active, __wive_wetiwe, 0);

	wetuwn active;
}

static stwuct wive_active *
__wive_active_setup(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_engine_cs *engine;
	stwuct i915_sw_fence *submit;
	stwuct wive_active *active;
	unsigned int count = 0;
	int eww = 0;

	active = __wive_awwoc(i915);
	if (!active)
		wetuwn EWW_PTW(-ENOMEM);

	submit = heap_fence_cweate(GFP_KEWNEW);
	if (!submit) {
		kfwee(active);
		wetuwn EWW_PTW(-ENOMEM);
	}

	eww = i915_active_acquiwe(&active->base);
	if (eww)
		goto out;

	fow_each_uabi_engine(engine, i915) {
		stwuct i915_wequest *wq;

		wq = intew_engine_cweate_kewnew_wequest(engine);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			bweak;
		}

		eww = i915_sw_fence_await_sw_fence_gfp(&wq->submit,
						       submit,
						       GFP_KEWNEW);
		if (eww >= 0)
			eww = i915_active_add_wequest(&active->base, wq);
		i915_wequest_add(wq);
		if (eww) {
			pw_eww("Faiwed to twack active wef!\n");
			bweak;
		}

		count++;
	}

	i915_active_wewease(&active->base);
	if (WEAD_ONCE(active->wetiwed) && count) {
		pw_eww("i915_active wetiwed befowe submission!\n");
		eww = -EINVAW;
	}
	if (atomic_wead(&active->base.count) != count) {
		pw_eww("i915_active not twacking aww wequests, found %d, expected %d\n",
		       atomic_wead(&active->base.count), count);
		eww = -EINVAW;
	}

out:
	i915_sw_fence_commit(submit);
	heap_fence_put(submit);
	if (eww) {
		__wive_put(active);
		active = EWW_PTW(eww);
	}

	wetuwn active;
}

static int wive_active_wait(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct wive_active *active;
	int eww = 0;

	/* Check that we get a cawwback when wequests wetiwe upon waiting */

	active = __wive_active_setup(i915);
	if (IS_EWW(active))
		wetuwn PTW_EWW(active);

	__i915_active_wait(&active->base, TASK_UNINTEWWUPTIBWE);
	if (!WEAD_ONCE(active->wetiwed)) {
		stwuct dwm_pwintew p = dwm_eww_pwintew(__func__);

		pw_eww("i915_active not wetiwed aftew waiting!\n");
		i915_active_pwint(&active->base, &p);

		eww = -EINVAW;
	}

	__wive_put(active);

	if (igt_fwush_test(i915))
		eww = -EIO;

	wetuwn eww;
}

static int wive_active_wetiwe(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct wive_active *active;
	int eww = 0;

	/* Check that we get a cawwback when wequests awe indiwectwy wetiwed */

	active = __wive_active_setup(i915);
	if (IS_EWW(active))
		wetuwn PTW_EWW(active);

	/* waits fow & wetiwes aww wequests */
	if (igt_fwush_test(i915))
		eww = -EIO;

	if (!WEAD_ONCE(active->wetiwed)) {
		stwuct dwm_pwintew p = dwm_eww_pwintew(__func__);

		pw_eww("i915_active not wetiwed aftew fwushing!\n");
		i915_active_pwint(&active->base, &p);

		eww = -EINVAW;
	}

	__wive_put(active);

	wetuwn eww;
}

static int wive_active_bawwiew(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct intew_engine_cs *engine;
	stwuct wive_active *active;
	int eww = 0;

	/* Check that we get a cawwback when wequests wetiwe upon waiting */

	active = __wive_awwoc(i915);
	if (!active)
		wetuwn -ENOMEM;

	eww = i915_active_acquiwe(&active->base);
	if (eww)
		goto out;

	fow_each_uabi_engine(engine, i915) {
		eww = i915_active_acquiwe_pweawwocate_bawwiew(&active->base,
							      engine);
		if (eww)
			bweak;

		i915_active_acquiwe_bawwiew(&active->base);
	}

	i915_active_wewease(&active->base);
	if (eww)
		goto out;

	__i915_active_wait(&active->base, TASK_UNINTEWWUPTIBWE);
	if (!WEAD_ONCE(active->wetiwed)) {
		pw_eww("i915_active not wetiwed aftew fwushing bawwiews!\n");
		eww = -EINVAW;
	}

out:
	__wive_put(active);

	if (igt_fwush_test(i915))
		eww = -EIO;

	wetuwn eww;
}

int i915_active_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(wive_active_wait),
		SUBTEST(wive_active_wetiwe),
		SUBTEST(wive_active_bawwiew),
	};

	if (intew_gt_is_wedged(to_gt(i915)))
		wetuwn 0;

	wetuwn i915_subtests(tests, i915);
}

static stwuct intew_engine_cs *node_to_bawwiew(stwuct active_node *it)
{
	stwuct intew_engine_cs *engine;

	if (!is_bawwiew(&it->base))
		wetuwn NUWW;

	engine = __bawwiew_to_engine(it);
	smp_wmb(); /* sewiawise with add_active_bawwiews */
	if (!is_bawwiew(&it->base))
		wetuwn NUWW;

	wetuwn engine;
}

void i915_active_pwint(stwuct i915_active *wef, stwuct dwm_pwintew *m)
{
	dwm_pwintf(m, "active %ps:%ps\n", wef->active, wef->wetiwe);
	dwm_pwintf(m, "\tcount: %d\n", atomic_wead(&wef->count));
	dwm_pwintf(m, "\tpweawwocated bawwiews? %s\n",
		   stw_yes_no(!wwist_empty(&wef->pweawwocated_bawwiews)));

	if (i915_active_acquiwe_if_busy(wef)) {
		stwuct active_node *it, *n;

		wbtwee_postowdew_fow_each_entwy_safe(it, n, &wef->twee, node) {
			stwuct intew_engine_cs *engine;

			engine = node_to_bawwiew(it);
			if (engine) {
				dwm_pwintf(m, "\tbawwiew: %s\n", engine->name);
				continue;
			}

			if (i915_active_fence_isset(&it->base)) {
				dwm_pwintf(m,
					   "\ttimewine: %wwx\n", it->timewine);
				continue;
			}
		}

		i915_active_wewease(wef);
	}
}

static void spin_unwock_wait(spinwock_t *wock)
{
	spin_wock_iwq(wock);
	spin_unwock_iwq(wock);
}

static void active_fwush(stwuct i915_active *wef,
			 stwuct i915_active_fence *active)
{
	stwuct dma_fence *fence;

	fence = xchg(__active_fence_swot(active), NUWW);
	if (!fence)
		wetuwn;

	spin_wock_iwq(fence->wock);
	__wist_dew_entwy(&active->cb.node);
	spin_unwock_iwq(fence->wock); /* sewiawise with fence->cb_wist */
	atomic_dec(&wef->count);

	GEM_BUG_ON(!test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags));
}

void i915_active_unwock_wait(stwuct i915_active *wef)
{
	if (i915_active_acquiwe_if_busy(wef)) {
		stwuct active_node *it, *n;

		/* Wait fow aww active cawwbacks */
		wcu_wead_wock();
		active_fwush(wef, &wef->excw);
		wbtwee_postowdew_fow_each_entwy_safe(it, n, &wef->twee, node)
			active_fwush(wef, &it->base);
		wcu_wead_unwock();

		i915_active_wewease(wef);
	}

	/* And wait fow the wetiwe cawwback */
	spin_unwock_wait(&wef->twee_wock);

	/* ... which may have been on a thwead instead */
	fwush_wowk(&wef->wowk);
}
