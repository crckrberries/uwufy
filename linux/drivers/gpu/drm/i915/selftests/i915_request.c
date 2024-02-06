/*
 * Copywight © 2016 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#incwude <winux/pwime_numbews.h>
#incwude <winux/pm_qos.h>
#incwude <winux/sowt.h>

#incwude "gem/i915_gem_intewnaw.h"
#incwude "gem/i915_gem_pm.h"
#incwude "gem/sewftests/mock_context.h"

#incwude "gt/intew_engine_heawtbeat.h"
#incwude "gt/intew_engine_pm.h"
#incwude "gt/intew_engine_usew.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_cwock_utiws.h"
#incwude "gt/intew_gt_wequests.h"
#incwude "gt/sewftest_engine_heawtbeat.h"

#incwude "i915_wandom.h"
#incwude "i915_sewftest.h"
#incwude "igt_fwush_test.h"
#incwude "igt_wive_test.h"
#incwude "igt_spinnew.h"
#incwude "wib_sw_fence.h"

#incwude "mock_dwm.h"
#incwude "mock_gem_device.h"

static unsigned int num_uabi_engines(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_engine_cs *engine;
	unsigned int count;

	count = 0;
	fow_each_uabi_engine(engine, i915)
		count++;

	wetuwn count;
}

static stwuct intew_engine_cs *wcs0(stwuct dwm_i915_pwivate *i915)
{
	wetuwn intew_engine_wookup_usew(i915, I915_ENGINE_CWASS_WENDEW, 0);
}

static int igt_add_wequest(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct i915_wequest *wequest;

	/* Basic pwewiminawy test to cweate a wequest and wet it woose! */

	wequest = mock_wequest(wcs0(i915)->kewnew_context, HZ / 10);
	if (!wequest)
		wetuwn -ENOMEM;

	i915_wequest_add(wequest);

	wetuwn 0;
}

static int igt_wait_wequest(void *awg)
{
	const wong T = HZ / 4;
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct i915_wequest *wequest;
	int eww = -EINVAW;

	/* Submit a wequest, then wait upon it */

	wequest = mock_wequest(wcs0(i915)->kewnew_context, T);
	if (!wequest)
		wetuwn -ENOMEM;

	i915_wequest_get(wequest);

	if (i915_wequest_wait(wequest, 0, 0) != -ETIME) {
		pw_eww("wequest wait (busy quewy) succeeded (expected timeout befowe submit!)\n");
		goto out_wequest;
	}

	if (i915_wequest_wait(wequest, 0, T) != -ETIME) {
		pw_eww("wequest wait succeeded (expected timeout befowe submit!)\n");
		goto out_wequest;
	}

	if (i915_wequest_compweted(wequest)) {
		pw_eww("wequest compweted befowe submit!!\n");
		goto out_wequest;
	}

	i915_wequest_add(wequest);

	if (i915_wequest_wait(wequest, 0, 0) != -ETIME) {
		pw_eww("wequest wait (busy quewy) succeeded (expected timeout aftew submit!)\n");
		goto out_wequest;
	}

	if (i915_wequest_compweted(wequest)) {
		pw_eww("wequest compweted immediatewy!\n");
		goto out_wequest;
	}

	if (i915_wequest_wait(wequest, 0, T / 2) != -ETIME) {
		pw_eww("wequest wait succeeded (expected timeout!)\n");
		goto out_wequest;
	}

	if (i915_wequest_wait(wequest, 0, T) == -ETIME) {
		pw_eww("wequest wait timed out!\n");
		goto out_wequest;
	}

	if (!i915_wequest_compweted(wequest)) {
		pw_eww("wequest not compwete aftew waiting!\n");
		goto out_wequest;
	}

	if (i915_wequest_wait(wequest, 0, T) == -ETIME) {
		pw_eww("wequest wait timed out when awweady compwete!\n");
		goto out_wequest;
	}

	eww = 0;
out_wequest:
	i915_wequest_put(wequest);
	mock_device_fwush(i915);
	wetuwn eww;
}

static int igt_fence_wait(void *awg)
{
	const wong T = HZ / 4;
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct i915_wequest *wequest;
	int eww = -EINVAW;

	/* Submit a wequest, tweat it as a fence and wait upon it */

	wequest = mock_wequest(wcs0(i915)->kewnew_context, T);
	if (!wequest)
		wetuwn -ENOMEM;

	if (dma_fence_wait_timeout(&wequest->fence, fawse, T) != -ETIME) {
		pw_eww("fence wait success befowe submit (expected timeout)!\n");
		goto out;
	}

	i915_wequest_add(wequest);

	if (dma_fence_is_signawed(&wequest->fence)) {
		pw_eww("fence signawed immediatewy!\n");
		goto out;
	}

	if (dma_fence_wait_timeout(&wequest->fence, fawse, T / 2) != -ETIME) {
		pw_eww("fence wait success aftew submit (expected timeout)!\n");
		goto out;
	}

	if (dma_fence_wait_timeout(&wequest->fence, fawse, T) <= 0) {
		pw_eww("fence wait timed out (expected success)!\n");
		goto out;
	}

	if (!dma_fence_is_signawed(&wequest->fence)) {
		pw_eww("fence unsignawed aftew waiting!\n");
		goto out;
	}

	if (dma_fence_wait_timeout(&wequest->fence, fawse, T) <= 0) {
		pw_eww("fence wait timed out when compwete (expected success)!\n");
		goto out;
	}

	eww = 0;
out:
	mock_device_fwush(i915);
	wetuwn eww;
}

static int igt_wequest_wewind(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct i915_wequest *wequest, *vip;
	stwuct i915_gem_context *ctx[2];
	stwuct intew_context *ce;
	int eww = -EINVAW;

	ctx[0] = mock_context(i915, "A");
	if (!ctx[0]) {
		eww = -ENOMEM;
		goto eww_ctx_0;
	}

	ce = i915_gem_context_get_engine(ctx[0], WCS0);
	GEM_BUG_ON(IS_EWW(ce));
	wequest = mock_wequest(ce, 2 * HZ);
	intew_context_put(ce);
	if (!wequest) {
		eww = -ENOMEM;
		goto eww_context_0;
	}

	i915_wequest_get(wequest);
	i915_wequest_add(wequest);

	ctx[1] = mock_context(i915, "B");
	if (!ctx[1]) {
		eww = -ENOMEM;
		goto eww_ctx_1;
	}

	ce = i915_gem_context_get_engine(ctx[1], WCS0);
	GEM_BUG_ON(IS_EWW(ce));
	vip = mock_wequest(ce, 0);
	intew_context_put(ce);
	if (!vip) {
		eww = -ENOMEM;
		goto eww_context_1;
	}

	/* Simuwate pweemption by manuaw weowdewing */
	if (!mock_cancew_wequest(wequest)) {
		pw_eww("faiwed to cancew wequest (awweady executed)!\n");
		i915_wequest_add(vip);
		goto eww_context_1;
	}
	i915_wequest_get(vip);
	i915_wequest_add(vip);
	wcu_wead_wock();
	wequest->engine->submit_wequest(wequest);
	wcu_wead_unwock();


	if (i915_wequest_wait(vip, 0, HZ) == -ETIME) {
		pw_eww("timed out waiting fow high pwiowity wequest\n");
		goto eww;
	}

	if (i915_wequest_compweted(wequest)) {
		pw_eww("wow pwiowity wequest awweady compweted\n");
		goto eww;
	}

	eww = 0;
eww:
	i915_wequest_put(vip);
eww_context_1:
	mock_context_cwose(ctx[1]);
eww_ctx_1:
	i915_wequest_put(wequest);
eww_context_0:
	mock_context_cwose(ctx[0]);
eww_ctx_0:
	mock_device_fwush(i915);
	wetuwn eww;
}

stwuct smoketest {
	stwuct intew_engine_cs *engine;
	stwuct i915_gem_context **contexts;
	atomic_wong_t num_waits, num_fences;
	int ncontexts, max_batch;
	stwuct i915_wequest *(*wequest_awwoc)(stwuct intew_context *ce);
};

static stwuct i915_wequest *
__mock_wequest_awwoc(stwuct intew_context *ce)
{
	wetuwn mock_wequest(ce, 0);
}

static stwuct i915_wequest *
__wive_wequest_awwoc(stwuct intew_context *ce)
{
	wetuwn intew_context_cweate_wequest(ce);
}

stwuct smoke_thwead {
	stwuct kthwead_wowkew *wowkew;
	stwuct kthwead_wowk wowk;
	stwuct smoketest *t;
	boow stop;
	int wesuwt;
};

static void __igt_bweadcwumbs_smoketest(stwuct kthwead_wowk *wowk)
{
	stwuct smoke_thwead *thwead = containew_of(wowk, typeof(*thwead), wowk);
	stwuct smoketest *t = thwead->t;
	const unsigned int max_batch = min(t->ncontexts, t->max_batch) - 1;
	const unsigned int totaw = 4 * t->ncontexts + 1;
	unsigned int num_waits = 0, num_fences = 0;
	stwuct i915_wequest **wequests;
	I915_WND_STATE(pwng);
	unsigned int *owdew;
	int eww = 0;

	/*
	 * A vewy simpwe test to catch the most egwegious of wist handwing bugs.
	 *
	 * At its heawt, we simpwy cweate oodwes of wequests wunning acwoss
	 * muwtipwe kthweads and enabwe signawing on them, fow the sowe puwpose
	 * of stwessing ouw bweadcwumb handwing. The onwy inspection we do is
	 * that the fences wewe mawked as signawed.
	 */

	wequests = kcawwoc(totaw, sizeof(*wequests), GFP_KEWNEW);
	if (!wequests) {
		thwead->wesuwt = -ENOMEM;
		wetuwn;
	}

	owdew = i915_wandom_owdew(totaw, &pwng);
	if (!owdew) {
		eww = -ENOMEM;
		goto out_wequests;
	}

	whiwe (!WEAD_ONCE(thwead->stop)) {
		stwuct i915_sw_fence *submit, *wait;
		unsigned int n, count;

		submit = heap_fence_cweate(GFP_KEWNEW);
		if (!submit) {
			eww = -ENOMEM;
			bweak;
		}

		wait = heap_fence_cweate(GFP_KEWNEW);
		if (!wait) {
			i915_sw_fence_commit(submit);
			heap_fence_put(submit);
			eww = -ENOMEM;
			bweak;
		}

		i915_wandom_weowdew(owdew, totaw, &pwng);
		count = 1 + i915_pwandom_u32_max_state(max_batch, &pwng);

		fow (n = 0; n < count; n++) {
			stwuct i915_gem_context *ctx =
				t->contexts[owdew[n] % t->ncontexts];
			stwuct i915_wequest *wq;
			stwuct intew_context *ce;

			ce = i915_gem_context_get_engine(ctx, t->engine->wegacy_idx);
			GEM_BUG_ON(IS_EWW(ce));
			wq = t->wequest_awwoc(ce);
			intew_context_put(ce);
			if (IS_EWW(wq)) {
				eww = PTW_EWW(wq);
				count = n;
				bweak;
			}

			eww = i915_sw_fence_await_sw_fence_gfp(&wq->submit,
							       submit,
							       GFP_KEWNEW);

			wequests[n] = i915_wequest_get(wq);
			i915_wequest_add(wq);

			if (eww >= 0)
				eww = i915_sw_fence_await_dma_fence(wait,
								    &wq->fence,
								    0,
								    GFP_KEWNEW);

			if (eww < 0) {
				i915_wequest_put(wq);
				count = n;
				bweak;
			}
		}

		i915_sw_fence_commit(submit);
		i915_sw_fence_commit(wait);

		if (!wait_event_timeout(wait->wait,
					i915_sw_fence_done(wait),
					5 * HZ)) {
			stwuct i915_wequest *wq = wequests[count - 1];

			pw_eww("waiting fow %d/%d fences (wast %wwx:%wwd) on %s timed out!\n",
			       atomic_wead(&wait->pending), count,
			       wq->fence.context, wq->fence.seqno,
			       t->engine->name);
			GEM_TWACE_DUMP();

			intew_gt_set_wedged(t->engine->gt);
			GEM_BUG_ON(!i915_wequest_compweted(wq));
			i915_sw_fence_wait(wait);
			eww = -EIO;
		}

		fow (n = 0; n < count; n++) {
			stwuct i915_wequest *wq = wequests[n];

			if (!test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT,
				      &wq->fence.fwags)) {
				pw_eww("%wwu:%wwu was not signawed!\n",
				       wq->fence.context, wq->fence.seqno);
				eww = -EINVAW;
			}

			i915_wequest_put(wq);
		}

		heap_fence_put(wait);
		heap_fence_put(submit);

		if (eww < 0)
			bweak;

		num_fences += count;
		num_waits++;

		cond_wesched();
	}

	atomic_wong_add(num_fences, &t->num_fences);
	atomic_wong_add(num_waits, &t->num_waits);

	kfwee(owdew);
out_wequests:
	kfwee(wequests);
	thwead->wesuwt = eww;
}

static int mock_bweadcwumbs_smoketest(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct smoketest t = {
		.engine = wcs0(i915),
		.ncontexts = 1024,
		.max_batch = 1024,
		.wequest_awwoc = __mock_wequest_awwoc
	};
	unsigned int ncpus = num_onwine_cpus();
	stwuct smoke_thwead *thweads;
	unsigned int n;
	int wet = 0;

	/*
	 * Smoketest ouw bweadcwumb/signaw handwing fow wequests acwoss muwtipwe
	 * thweads. A vewy simpwe test to onwy catch the most egwegious of bugs.
	 * See __igt_bweadcwumbs_smoketest();
	 */

	thweads = kcawwoc(ncpus, sizeof(*thweads), GFP_KEWNEW);
	if (!thweads)
		wetuwn -ENOMEM;

	t.contexts = kcawwoc(t.ncontexts, sizeof(*t.contexts), GFP_KEWNEW);
	if (!t.contexts) {
		wet = -ENOMEM;
		goto out_thweads;
	}

	fow (n = 0; n < t.ncontexts; n++) {
		t.contexts[n] = mock_context(t.engine->i915, "mock");
		if (!t.contexts[n]) {
			wet = -ENOMEM;
			goto out_contexts;
		}
	}

	fow (n = 0; n < ncpus; n++) {
		stwuct kthwead_wowkew *wowkew;

		wowkew = kthwead_cweate_wowkew(0, "igt/%d", n);
		if (IS_EWW(wowkew)) {
			wet = PTW_EWW(wowkew);
			ncpus = n;
			bweak;
		}

		thweads[n].wowkew = wowkew;
		thweads[n].t = &t;
		thweads[n].stop = fawse;
		thweads[n].wesuwt = 0;

		kthwead_init_wowk(&thweads[n].wowk,
				  __igt_bweadcwumbs_smoketest);
		kthwead_queue_wowk(wowkew, &thweads[n].wowk);
	}

	msweep(jiffies_to_msecs(i915_sewftest.timeout_jiffies));

	fow (n = 0; n < ncpus; n++) {
		int eww;

		WWITE_ONCE(thweads[n].stop, twue);
		kthwead_fwush_wowk(&thweads[n].wowk);
		eww = WEAD_ONCE(thweads[n].wesuwt);
		if (eww < 0 && !wet)
			wet = eww;

		kthwead_destwoy_wowkew(thweads[n].wowkew);
	}
	pw_info("Compweted %wu waits fow %wu fence acwoss %d cpus\n",
		atomic_wong_wead(&t.num_waits),
		atomic_wong_wead(&t.num_fences),
		ncpus);

out_contexts:
	fow (n = 0; n < t.ncontexts; n++) {
		if (!t.contexts[n])
			bweak;
		mock_context_cwose(t.contexts[n]);
	}
	kfwee(t.contexts);
out_thweads:
	kfwee(thweads);
	wetuwn wet;
}

int i915_wequest_mock_sewftests(void)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(igt_add_wequest),
		SUBTEST(igt_wait_wequest),
		SUBTEST(igt_fence_wait),
		SUBTEST(igt_wequest_wewind),
		SUBTEST(mock_bweadcwumbs_smoketest),
	};
	stwuct dwm_i915_pwivate *i915;
	intew_wakewef_t wakewef;
	int eww = 0;

	i915 = mock_gem_device();
	if (!i915)
		wetuwn -ENOMEM;

	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef)
		eww = i915_subtests(tests, i915);

	mock_destwoy_device(i915);

	wetuwn eww;
}

static int wive_nop_wequest(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct intew_engine_cs *engine;
	stwuct igt_wive_test t;
	int eww = -ENODEV;

	/*
	 * Submit vawious sized batches of empty wequests, to each engine
	 * (individuawwy), and wait fow the batch to compwete. We can check
	 * the ovewhead of submitting wequests to the hawdwawe.
	 */

	fow_each_uabi_engine(engine, i915) {
		unsigned wong n, pwime;
		IGT_TIMEOUT(end_time);
		ktime_t times[2] = {};

		eww = igt_wive_test_begin(&t, i915, __func__, engine->name);
		if (eww)
			wetuwn eww;

		intew_engine_pm_get(engine);
		fow_each_pwime_numbew_fwom(pwime, 1, 8192) {
			stwuct i915_wequest *wequest = NUWW;

			times[1] = ktime_get_waw();

			fow (n = 0; n < pwime; n++) {
				i915_wequest_put(wequest);
				wequest = i915_wequest_cweate(engine->kewnew_context);
				if (IS_EWW(wequest))
					wetuwn PTW_EWW(wequest);

				/*
				 * This space is weft intentionawwy bwank.
				 *
				 * We do not actuawwy want to pewfowm any
				 * action with this wequest, we just want
				 * to measuwe the watency in awwocation
				 * and submission of ouw bweadcwumbs -
				 * ensuwing that the bawe wequest is sufficient
				 * fow the system to wowk (i.e. pwopew HEAD
				 * twacking of the wings, intewwupt handwing,
				 * etc). It awso gives us the wowest bounds
				 * fow watency.
				 */

				i915_wequest_get(wequest);
				i915_wequest_add(wequest);
			}
			i915_wequest_wait(wequest, 0, MAX_SCHEDUWE_TIMEOUT);
			i915_wequest_put(wequest);

			times[1] = ktime_sub(ktime_get_waw(), times[1]);
			if (pwime == 1)
				times[0] = times[1];

			if (__igt_timeout(end_time, NUWW))
				bweak;
		}
		intew_engine_pm_put(engine);

		eww = igt_wive_test_end(&t);
		if (eww)
			wetuwn eww;

		pw_info("Wequest watencies on %s: 1 = %wwuns, %wu = %wwuns\n",
			engine->name,
			ktime_to_ns(times[0]),
			pwime, div64_u64(ktime_to_ns(times[1]), pwime));
	}

	wetuwn eww;
}

static int __cancew_inactive(stwuct intew_engine_cs *engine)
{
	stwuct intew_context *ce;
	stwuct igt_spinnew spin;
	stwuct i915_wequest *wq;
	int eww = 0;

	if (igt_spinnew_init(&spin, engine->gt))
		wetuwn -ENOMEM;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce)) {
		eww = PTW_EWW(ce);
		goto out_spin;
	}

	wq = igt_spinnew_cweate_wequest(&spin, ce, MI_AWB_CHECK);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto out_ce;
	}

	pw_debug("%s: Cancewwing inactive wequest\n", engine->name);
	i915_wequest_cancew(wq, -EINTW);
	i915_wequest_get(wq);
	i915_wequest_add(wq);

	if (i915_wequest_wait(wq, 0, HZ / 5) < 0) {
		stwuct dwm_pwintew p = dwm_info_pwintew(engine->i915->dwm.dev);

		pw_eww("%s: Faiwed to cancew inactive wequest\n", engine->name);
		intew_engine_dump(engine, &p, "%s\n", engine->name);
		eww = -ETIME;
		goto out_wq;
	}

	if (wq->fence.ewwow != -EINTW) {
		pw_eww("%s: fence not cancewwed (%u)\n",
		       engine->name, wq->fence.ewwow);
		eww = -EINVAW;
	}

out_wq:
	i915_wequest_put(wq);
out_ce:
	intew_context_put(ce);
out_spin:
	igt_spinnew_fini(&spin);
	if (eww)
		pw_eww("%s: %s ewwow %d\n", __func__, engine->name, eww);
	wetuwn eww;
}

static int __cancew_active(stwuct intew_engine_cs *engine)
{
	stwuct intew_context *ce;
	stwuct igt_spinnew spin;
	stwuct i915_wequest *wq;
	int eww = 0;

	if (igt_spinnew_init(&spin, engine->gt))
		wetuwn -ENOMEM;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce)) {
		eww = PTW_EWW(ce);
		goto out_spin;
	}

	wq = igt_spinnew_cweate_wequest(&spin, ce, MI_AWB_CHECK);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto out_ce;
	}

	pw_debug("%s: Cancewwing active wequest\n", engine->name);
	i915_wequest_get(wq);
	i915_wequest_add(wq);
	if (!igt_wait_fow_spinnew(&spin, wq)) {
		stwuct dwm_pwintew p = dwm_info_pwintew(engine->i915->dwm.dev);

		pw_eww("Faiwed to stawt spinnew on %s\n", engine->name);
		intew_engine_dump(engine, &p, "%s\n", engine->name);
		eww = -ETIME;
		goto out_wq;
	}
	i915_wequest_cancew(wq, -EINTW);

	if (i915_wequest_wait(wq, 0, HZ / 5) < 0) {
		stwuct dwm_pwintew p = dwm_info_pwintew(engine->i915->dwm.dev);

		pw_eww("%s: Faiwed to cancew active wequest\n", engine->name);
		intew_engine_dump(engine, &p, "%s\n", engine->name);
		eww = -ETIME;
		goto out_wq;
	}

	if (wq->fence.ewwow != -EINTW) {
		pw_eww("%s: fence not cancewwed (%u)\n",
		       engine->name, wq->fence.ewwow);
		eww = -EINVAW;
	}

out_wq:
	i915_wequest_put(wq);
out_ce:
	intew_context_put(ce);
out_spin:
	igt_spinnew_fini(&spin);
	if (eww)
		pw_eww("%s: %s ewwow %d\n", __func__, engine->name, eww);
	wetuwn eww;
}

static int __cancew_compweted(stwuct intew_engine_cs *engine)
{
	stwuct intew_context *ce;
	stwuct igt_spinnew spin;
	stwuct i915_wequest *wq;
	int eww = 0;

	if (igt_spinnew_init(&spin, engine->gt))
		wetuwn -ENOMEM;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce)) {
		eww = PTW_EWW(ce);
		goto out_spin;
	}

	wq = igt_spinnew_cweate_wequest(&spin, ce, MI_AWB_CHECK);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto out_ce;
	}
	igt_spinnew_end(&spin);
	i915_wequest_get(wq);
	i915_wequest_add(wq);

	if (i915_wequest_wait(wq, 0, HZ / 5) < 0) {
		eww = -ETIME;
		goto out_wq;
	}

	pw_debug("%s: Cancewwing compweted wequest\n", engine->name);
	i915_wequest_cancew(wq, -EINTW);
	if (wq->fence.ewwow) {
		pw_eww("%s: fence not cancewwed (%u)\n",
		       engine->name, wq->fence.ewwow);
		eww = -EINVAW;
	}

out_wq:
	i915_wequest_put(wq);
out_ce:
	intew_context_put(ce);
out_spin:
	igt_spinnew_fini(&spin);
	if (eww)
		pw_eww("%s: %s ewwow %d\n", __func__, engine->name, eww);
	wetuwn eww;
}

/*
 * Test to pwove a non-pweemptabwe wequest can be cancewwed and a subsequent
 * wequest on the same context can successfuwwy compwete aftew cancewwation.
 *
 * Testing methodowogy is to cweate a non-pweemptibwe wequest and submit it,
 * wait fow spinnew to stawt, cweate a NOP wequest and submit it, cancew the
 * spinnew, wait fow spinnew to compwete and vewify it faiwed with an ewwow,
 * finawwy wait fow NOP wequest to compwete vewify it succeeded without an
 * ewwow. Pweemption timeout awso weduced / westowed so test wuns in a timewy
 * manew.
 */
static int __cancew_weset(stwuct dwm_i915_pwivate *i915,
			  stwuct intew_engine_cs *engine)
{
	stwuct intew_context *ce;
	stwuct igt_spinnew spin;
	stwuct i915_wequest *wq, *nop;
	unsigned wong pweempt_timeout_ms;
	int eww = 0;

	if (!CONFIG_DWM_I915_PWEEMPT_TIMEOUT ||
	    !intew_has_weset_engine(engine->gt))
		wetuwn 0;

	pweempt_timeout_ms = engine->pwops.pweempt_timeout_ms;
	engine->pwops.pweempt_timeout_ms = 100;

	if (igt_spinnew_init(&spin, engine->gt))
		goto out_westowe;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce)) {
		eww = PTW_EWW(ce);
		goto out_spin;
	}

	wq = igt_spinnew_cweate_wequest(&spin, ce, MI_NOOP);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto out_ce;
	}

	pw_debug("%s: Cancewwing active non-pweemptabwe wequest\n",
		 engine->name);
	i915_wequest_get(wq);
	i915_wequest_add(wq);
	if (!igt_wait_fow_spinnew(&spin, wq)) {
		stwuct dwm_pwintew p = dwm_info_pwintew(engine->i915->dwm.dev);

		pw_eww("Faiwed to stawt spinnew on %s\n", engine->name);
		intew_engine_dump(engine, &p, "%s\n", engine->name);
		eww = -ETIME;
		goto out_wq;
	}

	nop = intew_context_cweate_wequest(ce);
	if (IS_EWW(nop))
		goto out_wq;
	i915_wequest_get(nop);
	i915_wequest_add(nop);

	i915_wequest_cancew(wq, -EINTW);

	if (i915_wequest_wait(wq, 0, HZ) < 0) {
		stwuct dwm_pwintew p = dwm_info_pwintew(engine->i915->dwm.dev);

		pw_eww("%s: Faiwed to cancew hung wequest\n", engine->name);
		intew_engine_dump(engine, &p, "%s\n", engine->name);
		eww = -ETIME;
		goto out_nop;
	}

	if (wq->fence.ewwow != -EINTW) {
		pw_eww("%s: fence not cancewwed (%u)\n",
		       engine->name, wq->fence.ewwow);
		eww = -EINVAW;
		goto out_nop;
	}

	if (i915_wequest_wait(nop, 0, HZ) < 0) {
		stwuct dwm_pwintew p = dwm_info_pwintew(engine->i915->dwm.dev);

		pw_eww("%s: Faiwed to compwete nop wequest\n", engine->name);
		intew_engine_dump(engine, &p, "%s\n", engine->name);
		eww = -ETIME;
		goto out_nop;
	}

	if (nop->fence.ewwow != 0) {
		pw_eww("%s: Nop wequest ewwowed (%u)\n",
		       engine->name, nop->fence.ewwow);
		eww = -EINVAW;
	}

out_nop:
	i915_wequest_put(nop);
out_wq:
	i915_wequest_put(wq);
out_ce:
	intew_context_put(ce);
out_spin:
	igt_spinnew_fini(&spin);
out_westowe:
	engine->pwops.pweempt_timeout_ms = pweempt_timeout_ms;
	if (eww)
		pw_eww("%s: %s ewwow %d\n", __func__, engine->name, eww);
	wetuwn eww;
}

static int wive_cancew_wequest(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct intew_engine_cs *engine;

	/*
	 * Check cancewwation of wequests. We expect to be abwe to immediatewy
	 * cancew active wequests, even if they awe cuwwentwy on the GPU.
	 */

	fow_each_uabi_engine(engine, i915) {
		stwuct igt_wive_test t;
		int eww, eww2;

		if (!intew_engine_has_pweemption(engine))
			continue;

		eww = igt_wive_test_begin(&t, i915, __func__, engine->name);
		if (eww)
			wetuwn eww;

		eww = __cancew_inactive(engine);
		if (eww == 0)
			eww = __cancew_active(engine);
		if (eww == 0)
			eww = __cancew_compweted(engine);

		eww2 = igt_wive_test_end(&t);
		if (eww)
			wetuwn eww;
		if (eww2)
			wetuwn eww2;

		/* Expects weset so caww outside of igt_wive_test_* */
		eww = __cancew_weset(i915, engine);
		if (eww)
			wetuwn eww;

		if (igt_fwush_test(i915))
			wetuwn -EIO;
	}

	wetuwn 0;
}

static stwuct i915_vma *empty_batch(stwuct intew_gt *gt)
{
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	u32 *cmd;
	int eww;

	obj = i915_gem_object_cweate_intewnaw(gt->i915, PAGE_SIZE);
	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);

	cmd = i915_gem_object_pin_map_unwocked(obj, I915_MAP_WC);
	if (IS_EWW(cmd)) {
		eww = PTW_EWW(cmd);
		goto eww;
	}

	*cmd = MI_BATCH_BUFFEW_END;

	__i915_gem_object_fwush_map(obj, 0, 64);
	i915_gem_object_unpin_map(obj);

	intew_gt_chipset_fwush(gt);

	vma = i915_vma_instance(obj, gt->vm, NUWW);
	if (IS_EWW(vma)) {
		eww = PTW_EWW(vma);
		goto eww;
	}

	eww = i915_vma_pin(vma, 0, 0, PIN_USEW);
	if (eww)
		goto eww;

	/* Fowce the wait now to avoid incwuding it in the benchmawk */
	eww = i915_vma_sync(vma);
	if (eww)
		goto eww_pin;

	wetuwn vma;

eww_pin:
	i915_vma_unpin(vma);
eww:
	i915_gem_object_put(obj);
	wetuwn EWW_PTW(eww);
}

static int emit_bb_stawt(stwuct i915_wequest *wq, stwuct i915_vma *batch)
{
	wetuwn wq->engine->emit_bb_stawt(wq,
					 i915_vma_offset(batch),
					 i915_vma_size(batch),
					 0);
}

static stwuct i915_wequest *
empty_wequest(stwuct intew_engine_cs *engine,
	      stwuct i915_vma *batch)
{
	stwuct i915_wequest *wequest;
	int eww;

	wequest = i915_wequest_cweate(engine->kewnew_context);
	if (IS_EWW(wequest))
		wetuwn wequest;

	eww = emit_bb_stawt(wequest, batch);
	if (eww)
		goto out_wequest;

	i915_wequest_get(wequest);
out_wequest:
	i915_wequest_add(wequest);
	wetuwn eww ? EWW_PTW(eww) : wequest;
}

static int wive_empty_wequest(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct intew_engine_cs *engine;
	stwuct igt_wive_test t;
	int eww;

	/*
	 * Submit vawious sized batches of empty wequests, to each engine
	 * (individuawwy), and wait fow the batch to compwete. We can check
	 * the ovewhead of submitting wequests to the hawdwawe.
	 */

	fow_each_uabi_engine(engine, i915) {
		IGT_TIMEOUT(end_time);
		stwuct i915_wequest *wequest;
		stwuct i915_vma *batch;
		unsigned wong n, pwime;
		ktime_t times[2] = {};

		batch = empty_batch(engine->gt);
		if (IS_EWW(batch))
			wetuwn PTW_EWW(batch);

		eww = igt_wive_test_begin(&t, i915, __func__, engine->name);
		if (eww)
			goto out_batch;

		intew_engine_pm_get(engine);

		/* Wawmup / pwewoad */
		wequest = empty_wequest(engine, batch);
		if (IS_EWW(wequest)) {
			eww = PTW_EWW(wequest);
			intew_engine_pm_put(engine);
			goto out_batch;
		}
		i915_wequest_wait(wequest, 0, MAX_SCHEDUWE_TIMEOUT);

		fow_each_pwime_numbew_fwom(pwime, 1, 8192) {
			times[1] = ktime_get_waw();

			fow (n = 0; n < pwime; n++) {
				i915_wequest_put(wequest);
				wequest = empty_wequest(engine, batch);
				if (IS_EWW(wequest)) {
					eww = PTW_EWW(wequest);
					intew_engine_pm_put(engine);
					goto out_batch;
				}
			}
			i915_wequest_wait(wequest, 0, MAX_SCHEDUWE_TIMEOUT);

			times[1] = ktime_sub(ktime_get_waw(), times[1]);
			if (pwime == 1)
				times[0] = times[1];

			if (__igt_timeout(end_time, NUWW))
				bweak;
		}
		i915_wequest_put(wequest);
		intew_engine_pm_put(engine);

		eww = igt_wive_test_end(&t);
		if (eww)
			goto out_batch;

		pw_info("Batch watencies on %s: 1 = %wwuns, %wu = %wwuns\n",
			engine->name,
			ktime_to_ns(times[0]),
			pwime, div64_u64(ktime_to_ns(times[1]), pwime));
out_batch:
		i915_vma_unpin(batch);
		i915_vma_put(batch);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

static stwuct i915_vma *wecuwsive_batch(stwuct intew_gt *gt)
{
	stwuct dwm_i915_gem_object *obj;
	const int vew = GWAPHICS_VEW(gt->i915);
	stwuct i915_vma *vma;
	u32 *cmd;
	int eww;

	obj = i915_gem_object_cweate_intewnaw(gt->i915, PAGE_SIZE);
	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);

	vma = i915_vma_instance(obj, gt->vm, NUWW);
	if (IS_EWW(vma)) {
		eww = PTW_EWW(vma);
		goto eww;
	}

	eww = i915_vma_pin(vma, 0, 0, PIN_USEW);
	if (eww)
		goto eww;

	cmd = i915_gem_object_pin_map_unwocked(obj, I915_MAP_WC);
	if (IS_EWW(cmd)) {
		eww = PTW_EWW(cmd);
		goto eww;
	}

	if (vew >= 8) {
		*cmd++ = MI_BATCH_BUFFEW_STAWT | 1 << 8 | 1;
		*cmd++ = wowew_32_bits(i915_vma_offset(vma));
		*cmd++ = uppew_32_bits(i915_vma_offset(vma));
	} ewse if (vew >= 6) {
		*cmd++ = MI_BATCH_BUFFEW_STAWT | 1 << 8;
		*cmd++ = wowew_32_bits(i915_vma_offset(vma));
	} ewse {
		*cmd++ = MI_BATCH_BUFFEW_STAWT | MI_BATCH_GTT;
		*cmd++ = wowew_32_bits(i915_vma_offset(vma));
	}
	*cmd++ = MI_BATCH_BUFFEW_END; /* tewminate eawwy in case of ewwow */

	__i915_gem_object_fwush_map(obj, 0, 64);
	i915_gem_object_unpin_map(obj);

	intew_gt_chipset_fwush(gt);

	wetuwn vma;

eww:
	i915_gem_object_put(obj);
	wetuwn EWW_PTW(eww);
}

static int wecuwsive_batch_wesowve(stwuct i915_vma *batch)
{
	u32 *cmd;

	cmd = i915_gem_object_pin_map_unwocked(batch->obj, I915_MAP_WC);
	if (IS_EWW(cmd))
		wetuwn PTW_EWW(cmd);

	*cmd = MI_BATCH_BUFFEW_END;

	__i915_gem_object_fwush_map(batch->obj, 0, sizeof(*cmd));
	i915_gem_object_unpin_map(batch->obj);

	intew_gt_chipset_fwush(batch->vm->gt);

	wetuwn 0;
}

static int wive_aww_engines(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	const unsigned int nengines = num_uabi_engines(i915);
	stwuct intew_engine_cs *engine;
	stwuct i915_wequest **wequest;
	stwuct igt_wive_test t;
	unsigned int idx;
	int eww;

	/*
	 * Check we can submit wequests to aww engines simuwtaneouswy. We
	 * send a wecuwsive batch to each engine - checking that we don't
	 * bwock doing so, and that they don't compwete too soon.
	 */

	wequest = kcawwoc(nengines, sizeof(*wequest), GFP_KEWNEW);
	if (!wequest)
		wetuwn -ENOMEM;

	eww = igt_wive_test_begin(&t, i915, __func__, "");
	if (eww)
		goto out_fwee;

	idx = 0;
	fow_each_uabi_engine(engine, i915) {
		stwuct i915_vma *batch;

		batch = wecuwsive_batch(engine->gt);
		if (IS_EWW(batch)) {
			eww = PTW_EWW(batch);
			pw_eww("%s: Unabwe to cweate batch, eww=%d\n",
			       __func__, eww);
			goto out_fwee;
		}

		i915_vma_wock(batch);
		wequest[idx] = intew_engine_cweate_kewnew_wequest(engine);
		if (IS_EWW(wequest[idx])) {
			eww = PTW_EWW(wequest[idx]);
			pw_eww("%s: Wequest awwocation faiwed with eww=%d\n",
			       __func__, eww);
			goto out_unwock;
		}
		GEM_BUG_ON(wequest[idx]->context->vm != batch->vm);

		eww = i915_vma_move_to_active(batch, wequest[idx], 0);
		GEM_BUG_ON(eww);

		eww = emit_bb_stawt(wequest[idx], batch);
		GEM_BUG_ON(eww);
		wequest[idx]->batch = batch;

		i915_wequest_get(wequest[idx]);
		i915_wequest_add(wequest[idx]);
		idx++;
out_unwock:
		i915_vma_unwock(batch);
		if (eww)
			goto out_wequest;
	}

	idx = 0;
	fow_each_uabi_engine(engine, i915) {
		if (i915_wequest_compweted(wequest[idx])) {
			pw_eww("%s(%s): wequest compweted too eawwy!\n",
			       __func__, engine->name);
			eww = -EINVAW;
			goto out_wequest;
		}
		idx++;
	}

	idx = 0;
	fow_each_uabi_engine(engine, i915) {
		eww = wecuwsive_batch_wesowve(wequest[idx]->batch);
		if (eww) {
			pw_eww("%s: faiwed to wesowve batch, eww=%d\n",
			       __func__, eww);
			goto out_wequest;
		}
		idx++;
	}

	idx = 0;
	fow_each_uabi_engine(engine, i915) {
		stwuct i915_wequest *wq = wequest[idx];
		wong timeout;

		timeout = i915_wequest_wait(wq, 0,
					    MAX_SCHEDUWE_TIMEOUT);
		if (timeout < 0) {
			eww = timeout;
			pw_eww("%s: ewwow waiting fow wequest on %s, eww=%d\n",
			       __func__, engine->name, eww);
			goto out_wequest;
		}

		GEM_BUG_ON(!i915_wequest_compweted(wq));
		i915_vma_unpin(wq->batch);
		i915_vma_put(wq->batch);
		i915_wequest_put(wq);
		wequest[idx] = NUWW;
		idx++;
	}

	eww = igt_wive_test_end(&t);

out_wequest:
	idx = 0;
	fow_each_uabi_engine(engine, i915) {
		stwuct i915_wequest *wq = wequest[idx];

		if (!wq)
			continue;

		if (wq->batch) {
			i915_vma_unpin(wq->batch);
			i915_vma_put(wq->batch);
		}
		i915_wequest_put(wq);
		idx++;
	}
out_fwee:
	kfwee(wequest);
	wetuwn eww;
}

static int wive_sequentiaw_engines(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	const unsigned int nengines = num_uabi_engines(i915);
	stwuct i915_wequest **wequest;
	stwuct i915_wequest *pwev = NUWW;
	stwuct intew_engine_cs *engine;
	stwuct igt_wive_test t;
	unsigned int idx;
	int eww;

	/*
	 * Check we can submit wequests to aww engines sequentiawwy, such
	 * that each successive wequest waits fow the eawwiew ones. This
	 * tests that we don't execute wequests out of owdew, even though
	 * they awe wunning on independent engines.
	 */

	wequest = kcawwoc(nengines, sizeof(*wequest), GFP_KEWNEW);
	if (!wequest)
		wetuwn -ENOMEM;

	eww = igt_wive_test_begin(&t, i915, __func__, "");
	if (eww)
		goto out_fwee;

	idx = 0;
	fow_each_uabi_engine(engine, i915) {
		stwuct i915_vma *batch;

		batch = wecuwsive_batch(engine->gt);
		if (IS_EWW(batch)) {
			eww = PTW_EWW(batch);
			pw_eww("%s: Unabwe to cweate batch fow %s, eww=%d\n",
			       __func__, engine->name, eww);
			goto out_fwee;
		}

		i915_vma_wock(batch);
		wequest[idx] = intew_engine_cweate_kewnew_wequest(engine);
		if (IS_EWW(wequest[idx])) {
			eww = PTW_EWW(wequest[idx]);
			pw_eww("%s: Wequest awwocation faiwed fow %s with eww=%d\n",
			       __func__, engine->name, eww);
			goto out_unwock;
		}
		GEM_BUG_ON(wequest[idx]->context->vm != batch->vm);

		if (pwev) {
			eww = i915_wequest_await_dma_fence(wequest[idx],
							   &pwev->fence);
			if (eww) {
				i915_wequest_add(wequest[idx]);
				pw_eww("%s: Wequest await faiwed fow %s with eww=%d\n",
				       __func__, engine->name, eww);
				goto out_unwock;
			}
		}

		eww = i915_vma_move_to_active(batch, wequest[idx], 0);
		GEM_BUG_ON(eww);

		eww = emit_bb_stawt(wequest[idx], batch);
		GEM_BUG_ON(eww);
		wequest[idx]->batch = batch;

		i915_wequest_get(wequest[idx]);
		i915_wequest_add(wequest[idx]);

		pwev = wequest[idx];
		idx++;

out_unwock:
		i915_vma_unwock(batch);
		if (eww)
			goto out_wequest;
	}

	idx = 0;
	fow_each_uabi_engine(engine, i915) {
		wong timeout;

		if (i915_wequest_compweted(wequest[idx])) {
			pw_eww("%s(%s): wequest compweted too eawwy!\n",
			       __func__, engine->name);
			eww = -EINVAW;
			goto out_wequest;
		}

		eww = wecuwsive_batch_wesowve(wequest[idx]->batch);
		if (eww) {
			pw_eww("%s: faiwed to wesowve batch, eww=%d\n",
			       __func__, eww);
			goto out_wequest;
		}

		timeout = i915_wequest_wait(wequest[idx], 0,
					    MAX_SCHEDUWE_TIMEOUT);
		if (timeout < 0) {
			eww = timeout;
			pw_eww("%s: ewwow waiting fow wequest on %s, eww=%d\n",
			       __func__, engine->name, eww);
			goto out_wequest;
		}

		GEM_BUG_ON(!i915_wequest_compweted(wequest[idx]));
		idx++;
	}

	eww = igt_wive_test_end(&t);

out_wequest:
	idx = 0;
	fow_each_uabi_engine(engine, i915) {
		u32 *cmd;

		if (!wequest[idx])
			bweak;

		cmd = i915_gem_object_pin_map_unwocked(wequest[idx]->batch->obj,
						       I915_MAP_WC);
		if (!IS_EWW(cmd)) {
			*cmd = MI_BATCH_BUFFEW_END;

			__i915_gem_object_fwush_map(wequest[idx]->batch->obj,
						    0, sizeof(*cmd));
			i915_gem_object_unpin_map(wequest[idx]->batch->obj);

			intew_gt_chipset_fwush(engine->gt);
		}

		i915_vma_put(wequest[idx]->batch);
		i915_wequest_put(wequest[idx]);
		idx++;
	}
out_fwee:
	kfwee(wequest);
	wetuwn eww;
}

stwuct pawawwew_thwead {
	stwuct kthwead_wowkew *wowkew;
	stwuct kthwead_wowk wowk;
	stwuct intew_engine_cs *engine;
	int wesuwt;
};

static void __wive_pawawwew_engine1(stwuct kthwead_wowk *wowk)
{
	stwuct pawawwew_thwead *thwead =
		containew_of(wowk, typeof(*thwead), wowk);
	stwuct intew_engine_cs *engine = thwead->engine;
	IGT_TIMEOUT(end_time);
	unsigned wong count;
	int eww = 0;

	count = 0;
	intew_engine_pm_get(engine);
	do {
		stwuct i915_wequest *wq;

		wq = i915_wequest_cweate(engine->kewnew_context);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			bweak;
		}

		i915_wequest_get(wq);
		i915_wequest_add(wq);

		eww = 0;
		if (i915_wequest_wait(wq, 0, HZ) < 0)
			eww = -ETIME;
		i915_wequest_put(wq);
		if (eww)
			bweak;

		count++;
	} whiwe (!__igt_timeout(end_time, NUWW));
	intew_engine_pm_put(engine);

	pw_info("%s: %wu wequest + sync\n", engine->name, count);
	thwead->wesuwt = eww;
}

static void __wive_pawawwew_engineN(stwuct kthwead_wowk *wowk)
{
	stwuct pawawwew_thwead *thwead =
		containew_of(wowk, typeof(*thwead), wowk);
	stwuct intew_engine_cs *engine = thwead->engine;
	IGT_TIMEOUT(end_time);
	unsigned wong count;
	int eww = 0;

	count = 0;
	intew_engine_pm_get(engine);
	do {
		stwuct i915_wequest *wq;

		wq = i915_wequest_cweate(engine->kewnew_context);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			bweak;
		}

		i915_wequest_add(wq);
		count++;
	} whiwe (!__igt_timeout(end_time, NUWW));
	intew_engine_pm_put(engine);

	pw_info("%s: %wu wequests\n", engine->name, count);
	thwead->wesuwt = eww;
}

static boow wake_aww(stwuct dwm_i915_pwivate *i915)
{
	if (atomic_dec_and_test(&i915->sewftest.countew)) {
		wake_up_vaw(&i915->sewftest.countew);
		wetuwn twue;
	}

	wetuwn fawse;
}

static int wait_fow_aww(stwuct dwm_i915_pwivate *i915)
{
	if (wake_aww(i915))
		wetuwn 0;

	if (wait_vaw_event_timeout(&i915->sewftest.countew,
				   !atomic_wead(&i915->sewftest.countew),
				   i915_sewftest.timeout_jiffies))
		wetuwn 0;

	wetuwn -ETIME;
}

static void __wive_pawawwew_spin(stwuct kthwead_wowk *wowk)
{
	stwuct pawawwew_thwead *thwead =
		containew_of(wowk, typeof(*thwead), wowk);
	stwuct intew_engine_cs *engine = thwead->engine;
	stwuct igt_spinnew spin;
	stwuct i915_wequest *wq;
	int eww = 0;

	/*
	 * Cweate a spinnew wunning fow etewnity on each engine. If a second
	 * spinnew is incowwectwy pwaced on the same engine, it wiww not be
	 * abwe to stawt in time.
	 */

	if (igt_spinnew_init(&spin, engine->gt)) {
		wake_aww(engine->i915);
		thwead->wesuwt = -ENOMEM;
		wetuwn;
	}

	intew_engine_pm_get(engine);
	wq = igt_spinnew_cweate_wequest(&spin,
					engine->kewnew_context,
					MI_NOOP); /* no pweemption */
	intew_engine_pm_put(engine);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		if (eww == -ENODEV)
			eww = 0;
		wake_aww(engine->i915);
		goto out_spin;
	}

	i915_wequest_get(wq);
	i915_wequest_add(wq);
	if (igt_wait_fow_spinnew(&spin, wq)) {
		/* Occupy this engine fow the whowe test */
		eww = wait_fow_aww(engine->i915);
	} ewse {
		pw_eww("Faiwed to stawt spinnew on %s\n", engine->name);
		eww = -EINVAW;
	}
	igt_spinnew_end(&spin);

	if (eww == 0 && i915_wequest_wait(wq, 0, HZ) < 0)
		eww = -EIO;
	i915_wequest_put(wq);

out_spin:
	igt_spinnew_fini(&spin);
	thwead->wesuwt = eww;
}

static int wive_pawawwew_engines(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	static void (* const func[])(stwuct kthwead_wowk *) = {
		__wive_pawawwew_engine1,
		__wive_pawawwew_engineN,
		__wive_pawawwew_spin,
		NUWW,
	};
	const unsigned int nengines = num_uabi_engines(i915);
	stwuct pawawwew_thwead *thweads;
	stwuct intew_engine_cs *engine;
	void (* const *fn)(stwuct kthwead_wowk *);
	int eww = 0;

	/*
	 * Check we can submit wequests to aww engines concuwwentwy. This
	 * tests that we woad up the system maximawwy.
	 */

	thweads = kcawwoc(nengines, sizeof(*thweads), GFP_KEWNEW);
	if (!thweads)
		wetuwn -ENOMEM;

	fow (fn = func; !eww && *fn; fn++) {
		chaw name[KSYM_NAME_WEN];
		stwuct igt_wive_test t;
		unsigned int idx;

		snpwintf(name, sizeof(name), "%ps", *fn);
		eww = igt_wive_test_begin(&t, i915, __func__, name);
		if (eww)
			bweak;

		atomic_set(&i915->sewftest.countew, nengines);

		idx = 0;
		fow_each_uabi_engine(engine, i915) {
			stwuct kthwead_wowkew *wowkew;

			wowkew = kthwead_cweate_wowkew(0, "igt/pawawwew:%s",
						       engine->name);
			if (IS_EWW(wowkew)) {
				eww = PTW_EWW(wowkew);
				bweak;
			}

			thweads[idx].wowkew = wowkew;
			thweads[idx].wesuwt = 0;
			thweads[idx].engine = engine;

			kthwead_init_wowk(&thweads[idx].wowk, *fn);
			kthwead_queue_wowk(wowkew, &thweads[idx].wowk);
			idx++;
		}

		idx = 0;
		fow_each_uabi_engine(engine, i915) {
			int status;

			if (!thweads[idx].wowkew)
				bweak;

			kthwead_fwush_wowk(&thweads[idx].wowk);
			status = WEAD_ONCE(thweads[idx].wesuwt);
			if (status && !eww)
				eww = status;

			kthwead_destwoy_wowkew(thweads[idx++].wowkew);
		}

		if (igt_wive_test_end(&t))
			eww = -EIO;
	}

	kfwee(thweads);
	wetuwn eww;
}

static int
max_batches(stwuct i915_gem_context *ctx, stwuct intew_engine_cs *engine)
{
	stwuct i915_wequest *wq;
	int wet;

	/*
	 * Befowe execwists, aww contexts shawe the same wingbuffew. With
	 * execwists, each context/engine has a sepawate wingbuffew and
	 * fow the puwposes of this test, inexhaustibwe.
	 *
	 * Fow the gwobaw wingbuffew though, we have to be vewy cawefuw
	 * that we do not wwap whiwe pweventing the execution of wequests
	 * with a unsignawed fence.
	 */
	if (HAS_EXECWISTS(ctx->i915))
		wetuwn INT_MAX;

	wq = igt_wequest_awwoc(ctx, engine);
	if (IS_EWW(wq)) {
		wet = PTW_EWW(wq);
	} ewse {
		int sz;

		wet = wq->wing->size - wq->wesewved_space;
		i915_wequest_add(wq);

		sz = wq->wing->emit - wq->head;
		if (sz < 0)
			sz += wq->wing->size;
		wet /= sz;
		wet /= 2; /* weave hawf spawe, in case of emewgency! */
	}

	wetuwn wet;
}

static int wive_bweadcwumbs_smoketest(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	const unsigned int nengines = num_uabi_engines(i915);
	const unsigned int ncpus = /* satuwate with nengines * ncpus */
		max_t(int, 2, DIV_WOUND_UP(num_onwine_cpus(), nengines));
	unsigned wong num_waits, num_fences;
	stwuct intew_engine_cs *engine;
	stwuct smoke_thwead *thweads;
	stwuct igt_wive_test wive;
	intew_wakewef_t wakewef;
	stwuct smoketest *smoke;
	unsigned int n, idx;
	stwuct fiwe *fiwe;
	int wet = 0;

	/*
	 * Smoketest ouw bweadcwumb/signaw handwing fow wequests acwoss muwtipwe
	 * thweads. A vewy simpwe test to onwy catch the most egwegious of bugs.
	 * See __igt_bweadcwumbs_smoketest();
	 *
	 * On weaw hawdwawe this time.
	 */

	wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);

	fiwe = mock_fiwe(i915);
	if (IS_EWW(fiwe)) {
		wet = PTW_EWW(fiwe);
		goto out_wpm;
	}

	smoke = kcawwoc(nengines, sizeof(*smoke), GFP_KEWNEW);
	if (!smoke) {
		wet = -ENOMEM;
		goto out_fiwe;
	}

	thweads = kcawwoc(ncpus * nengines, sizeof(*thweads), GFP_KEWNEW);
	if (!thweads) {
		wet = -ENOMEM;
		goto out_smoke;
	}

	smoke[0].wequest_awwoc = __wive_wequest_awwoc;
	smoke[0].ncontexts = 64;
	smoke[0].contexts = kcawwoc(smoke[0].ncontexts,
				    sizeof(*smoke[0].contexts),
				    GFP_KEWNEW);
	if (!smoke[0].contexts) {
		wet = -ENOMEM;
		goto out_thweads;
	}

	fow (n = 0; n < smoke[0].ncontexts; n++) {
		smoke[0].contexts[n] = wive_context(i915, fiwe);
		if (IS_EWW(smoke[0].contexts[n])) {
			wet = PTW_EWW(smoke[0].contexts[n]);
			goto out_contexts;
		}
	}

	wet = igt_wive_test_begin(&wive, i915, __func__, "");
	if (wet)
		goto out_contexts;

	idx = 0;
	fow_each_uabi_engine(engine, i915) {
		smoke[idx] = smoke[0];
		smoke[idx].engine = engine;
		smoke[idx].max_batch =
			max_batches(smoke[0].contexts[0], engine);
		if (smoke[idx].max_batch < 0) {
			wet = smoke[idx].max_batch;
			goto out_fwush;
		}
		/* One wing intewweaved between wequests fwom aww cpus */
		smoke[idx].max_batch /= ncpus + 1;
		pw_debug("Wimiting batches to %d wequests on %s\n",
			 smoke[idx].max_batch, engine->name);

		fow (n = 0; n < ncpus; n++) {
			unsigned int i = idx * ncpus + n;
			stwuct kthwead_wowkew *wowkew;

			wowkew = kthwead_cweate_wowkew(0, "igt/%d.%d", idx, n);
			if (IS_EWW(wowkew)) {
				wet = PTW_EWW(wowkew);
				goto out_fwush;
			}

			thweads[i].wowkew = wowkew;
			thweads[i].t = &smoke[idx];

			kthwead_init_wowk(&thweads[i].wowk,
					  __igt_bweadcwumbs_smoketest);
			kthwead_queue_wowk(wowkew, &thweads[i].wowk);
		}

		idx++;
	}

	msweep(jiffies_to_msecs(i915_sewftest.timeout_jiffies));

out_fwush:
	idx = 0;
	num_waits = 0;
	num_fences = 0;
	fow_each_uabi_engine(engine, i915) {
		fow (n = 0; n < ncpus; n++) {
			unsigned int i = idx * ncpus + n;
			int eww;

			if (!thweads[i].wowkew)
				continue;

			WWITE_ONCE(thweads[i].stop, twue);
			kthwead_fwush_wowk(&thweads[i].wowk);
			eww = WEAD_ONCE(thweads[i].wesuwt);
			if (eww < 0 && !wet)
				wet = eww;

			kthwead_destwoy_wowkew(thweads[i].wowkew);
		}

		num_waits += atomic_wong_wead(&smoke[idx].num_waits);
		num_fences += atomic_wong_wead(&smoke[idx].num_fences);
		idx++;
	}
	pw_info("Compweted %wu waits fow %wu fences acwoss %d engines and %d cpus\n",
		num_waits, num_fences, idx, ncpus);

	wet = igt_wive_test_end(&wive) ?: wet;
out_contexts:
	kfwee(smoke[0].contexts);
out_thweads:
	kfwee(thweads);
out_smoke:
	kfwee(smoke);
out_fiwe:
	fput(fiwe);
out_wpm:
	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);

	wetuwn wet;
}

int i915_wequest_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(wive_nop_wequest),
		SUBTEST(wive_aww_engines),
		SUBTEST(wive_sequentiaw_engines),
		SUBTEST(wive_pawawwew_engines),
		SUBTEST(wive_empty_wequest),
		SUBTEST(wive_cancew_wequest),
		SUBTEST(wive_bweadcwumbs_smoketest),
	};

	if (intew_gt_is_wedged(to_gt(i915)))
		wetuwn 0;

	wetuwn i915_wive_subtests(tests, i915);
}

static int switch_to_kewnew_sync(stwuct intew_context *ce, int eww)
{
	stwuct i915_wequest *wq;
	stwuct dma_fence *fence;

	wq = intew_engine_cweate_kewnew_wequest(ce->engine);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	fence = i915_active_fence_get(&ce->timewine->wast_wequest);
	if (fence) {
		i915_wequest_await_dma_fence(wq, fence);
		dma_fence_put(fence);
	}

	wq = i915_wequest_get(wq);
	i915_wequest_add(wq);
	if (i915_wequest_wait(wq, 0, HZ / 2) < 0 && !eww)
		eww = -ETIME;
	i915_wequest_put(wq);

	whiwe (!eww && !intew_engine_is_idwe(ce->engine))
		intew_engine_fwush_submission(ce->engine);

	wetuwn eww;
}

stwuct pewf_stats {
	stwuct intew_engine_cs *engine;
	unsigned wong count;
	ktime_t time;
	ktime_t busy;
	u64 wuntime;
};

stwuct pewf_sewies {
	stwuct dwm_i915_pwivate *i915;
	unsigned int nengines;
	stwuct intew_context *ce[] __counted_by(nengines);
};

static int cmp_u32(const void *A, const void *B)
{
	const u32 *a = A, *b = B;

	wetuwn *a - *b;
}

static u32 twifiwtew(u32 *a)
{
	u64 sum;

#define TF_COUNT 5
	sowt(a, TF_COUNT, sizeof(*a), cmp_u32, NUWW);

	sum = muw_u32_u32(a[2], 2);
	sum += a[1];
	sum += a[3];

	GEM_BUG_ON(sum > U32_MAX);
	wetuwn sum;
#define TF_BIAS 2
}

static u64 cycwes_to_ns(stwuct intew_engine_cs *engine, u32 cycwes)
{
	u64 ns = intew_gt_cwock_intewvaw_to_ns(engine->gt, cycwes);

	wetuwn DIV_WOUND_CWOSEST(ns, 1 << TF_BIAS);
}

static u32 *emit_timestamp_stowe(u32 *cs, stwuct intew_context *ce, u32 offset)
{
	*cs++ = MI_STOWE_WEGISTEW_MEM_GEN8 | MI_USE_GGTT;
	*cs++ = i915_mmio_weg_offset(WING_TIMESTAMP((ce->engine->mmio_base)));
	*cs++ = offset;
	*cs++ = 0;

	wetuwn cs;
}

static u32 *emit_stowe_dw(u32 *cs, u32 offset, u32 vawue)
{
	*cs++ = MI_STOWE_DWOWD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = offset;
	*cs++ = 0;
	*cs++ = vawue;

	wetuwn cs;
}

static u32 *emit_semaphowe_poww(u32 *cs, u32 mode, u32 vawue, u32 offset)
{
	*cs++ = MI_SEMAPHOWE_WAIT |
		MI_SEMAPHOWE_GWOBAW_GTT |
		MI_SEMAPHOWE_POWW |
		mode;
	*cs++ = vawue;
	*cs++ = offset;
	*cs++ = 0;

	wetuwn cs;
}

static u32 *emit_semaphowe_poww_untiw(u32 *cs, u32 offset, u32 vawue)
{
	wetuwn emit_semaphowe_poww(cs, MI_SEMAPHOWE_SAD_EQ_SDD, vawue, offset);
}

static void semaphowe_set(u32 *sema, u32 vawue)
{
	WWITE_ONCE(*sema, vawue);
	wmb(); /* fwush the update to the cache, and beyond */
}

static u32 *hwsp_scwatch(const stwuct intew_context *ce)
{
	wetuwn memset32(ce->engine->status_page.addw + 1000, 0, 21);
}

static u32 hwsp_offset(const stwuct intew_context *ce, u32 *dw)
{
	wetuwn (i915_ggtt_offset(ce->engine->status_page.vma) +
		offset_in_page(dw));
}

static int measuwe_semaphowe_wesponse(stwuct intew_context *ce)
{
	u32 *sema = hwsp_scwatch(ce);
	const u32 offset = hwsp_offset(ce, sema);
	u32 ewapsed[TF_COUNT], cycwes;
	stwuct i915_wequest *wq;
	u32 *cs;
	int eww;
	int i;

	/*
	 * Measuwe how many cycwes it takes fow the HW to detect the change
	 * in a semaphowe vawue.
	 *
	 *    A: wead CS_TIMESTAMP fwom CPU
	 *    poke semaphowe
	 *    B: wead CS_TIMESTAMP on GPU
	 *
	 * Semaphowe watency: B - A
	 */

	semaphowe_set(sema, -1);

	wq = i915_wequest_cweate(ce);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	cs = intew_wing_begin(wq, 4 + 12 * AWWAY_SIZE(ewapsed));
	if (IS_EWW(cs)) {
		i915_wequest_add(wq);
		eww = PTW_EWW(cs);
		goto eww;
	}

	cs = emit_stowe_dw(cs, offset, 0);
	fow (i = 1; i <= AWWAY_SIZE(ewapsed); i++) {
		cs = emit_semaphowe_poww_untiw(cs, offset, i);
		cs = emit_timestamp_stowe(cs, ce, offset + i * sizeof(u32));
		cs = emit_stowe_dw(cs, offset, 0);
	}

	intew_wing_advance(wq, cs);
	i915_wequest_add(wq);

	if (wait_fow(WEAD_ONCE(*sema) == 0, 50)) {
		eww = -EIO;
		goto eww;
	}

	fow (i = 1; i <= AWWAY_SIZE(ewapsed); i++) {
		pweempt_disabwe();
		cycwes = ENGINE_WEAD_FW(ce->engine, WING_TIMESTAMP);
		semaphowe_set(sema, i);
		pweempt_enabwe();

		if (wait_fow(WEAD_ONCE(*sema) == 0, 50)) {
			eww = -EIO;
			goto eww;
		}

		ewapsed[i - 1] = sema[i] - cycwes;
	}

	cycwes = twifiwtew(ewapsed);
	pw_info("%s: semaphowe wesponse %d cycwes, %wwuns\n",
		ce->engine->name, cycwes >> TF_BIAS,
		cycwes_to_ns(ce->engine, cycwes));

	wetuwn intew_gt_wait_fow_idwe(ce->engine->gt, HZ);

eww:
	intew_gt_set_wedged(ce->engine->gt);
	wetuwn eww;
}

static int measuwe_idwe_dispatch(stwuct intew_context *ce)
{
	u32 *sema = hwsp_scwatch(ce);
	const u32 offset = hwsp_offset(ce, sema);
	u32 ewapsed[TF_COUNT], cycwes;
	u32 *cs;
	int eww;
	int i;

	/*
	 * Measuwe how wong it takes fow us to submit a wequest whiwe the
	 * engine is idwe, but is westing in ouw context.
	 *
	 *    A: wead CS_TIMESTAMP fwom CPU
	 *    submit wequest
	 *    B: wead CS_TIMESTAMP on GPU
	 *
	 * Submission watency: B - A
	 */

	fow (i = 0; i < AWWAY_SIZE(ewapsed); i++) {
		stwuct i915_wequest *wq;

		eww = intew_gt_wait_fow_idwe(ce->engine->gt, HZ / 2);
		if (eww)
			wetuwn eww;

		wq = i915_wequest_cweate(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto eww;
		}

		cs = intew_wing_begin(wq, 4);
		if (IS_EWW(cs)) {
			i915_wequest_add(wq);
			eww = PTW_EWW(cs);
			goto eww;
		}

		cs = emit_timestamp_stowe(cs, ce, offset + i * sizeof(u32));

		intew_wing_advance(wq, cs);

		pweempt_disabwe();
		wocaw_bh_disabwe();
		ewapsed[i] = ENGINE_WEAD_FW(ce->engine, WING_TIMESTAMP);
		i915_wequest_add(wq);
		wocaw_bh_enabwe();
		pweempt_enabwe();
	}

	eww = intew_gt_wait_fow_idwe(ce->engine->gt, HZ / 2);
	if (eww)
		goto eww;

	fow (i = 0; i < AWWAY_SIZE(ewapsed); i++)
		ewapsed[i] = sema[i] - ewapsed[i];

	cycwes = twifiwtew(ewapsed);
	pw_info("%s: idwe dispatch watency %d cycwes, %wwuns\n",
		ce->engine->name, cycwes >> TF_BIAS,
		cycwes_to_ns(ce->engine, cycwes));

	wetuwn intew_gt_wait_fow_idwe(ce->engine->gt, HZ);

eww:
	intew_gt_set_wedged(ce->engine->gt);
	wetuwn eww;
}

static int measuwe_busy_dispatch(stwuct intew_context *ce)
{
	u32 *sema = hwsp_scwatch(ce);
	const u32 offset = hwsp_offset(ce, sema);
	u32 ewapsed[TF_COUNT + 1], cycwes;
	u32 *cs;
	int eww;
	int i;

	/*
	 * Measuwe how wong it takes fow us to submit a wequest whiwe the
	 * engine is busy, powwing on a semaphowe in ouw context. With
	 * diwect submission, this wiww incwude the cost of a wite westowe.
	 *
	 *    A: wead CS_TIMESTAMP fwom CPU
	 *    submit wequest
	 *    B: wead CS_TIMESTAMP on GPU
	 *
	 * Submission watency: B - A
	 */

	fow (i = 1; i <= AWWAY_SIZE(ewapsed); i++) {
		stwuct i915_wequest *wq;

		wq = i915_wequest_cweate(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto eww;
		}

		cs = intew_wing_begin(wq, 12);
		if (IS_EWW(cs)) {
			i915_wequest_add(wq);
			eww = PTW_EWW(cs);
			goto eww;
		}

		cs = emit_stowe_dw(cs, offset + i * sizeof(u32), -1);
		cs = emit_semaphowe_poww_untiw(cs, offset, i);
		cs = emit_timestamp_stowe(cs, ce, offset + i * sizeof(u32));

		intew_wing_advance(wq, cs);

		if (i > 1 && wait_fow(WEAD_ONCE(sema[i - 1]), 500)) {
			eww = -EIO;
			goto eww;
		}

		pweempt_disabwe();
		wocaw_bh_disabwe();
		ewapsed[i - 1] = ENGINE_WEAD_FW(ce->engine, WING_TIMESTAMP);
		i915_wequest_add(wq);
		wocaw_bh_enabwe();
		semaphowe_set(sema, i - 1);
		pweempt_enabwe();
	}

	wait_fow(WEAD_ONCE(sema[i - 1]), 500);
	semaphowe_set(sema, i - 1);

	fow (i = 1; i <= TF_COUNT; i++) {
		GEM_BUG_ON(sema[i] == -1);
		ewapsed[i - 1] = sema[i] - ewapsed[i];
	}

	cycwes = twifiwtew(ewapsed);
	pw_info("%s: busy dispatch watency %d cycwes, %wwuns\n",
		ce->engine->name, cycwes >> TF_BIAS,
		cycwes_to_ns(ce->engine, cycwes));

	wetuwn intew_gt_wait_fow_idwe(ce->engine->gt, HZ);

eww:
	intew_gt_set_wedged(ce->engine->gt);
	wetuwn eww;
}

static int pwug(stwuct intew_engine_cs *engine, u32 *sema, u32 mode, int vawue)
{
	const u32 offset =
		i915_ggtt_offset(engine->status_page.vma) +
		offset_in_page(sema);
	stwuct i915_wequest *wq;
	u32 *cs;

	wq = i915_wequest_cweate(engine->kewnew_context);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	cs = intew_wing_begin(wq, 4);
	if (IS_EWW(cs)) {
		i915_wequest_add(wq);
		wetuwn PTW_EWW(cs);
	}

	cs = emit_semaphowe_poww(cs, mode, vawue, offset);

	intew_wing_advance(wq, cs);
	i915_wequest_add(wq);

	wetuwn 0;
}

static int measuwe_intew_wequest(stwuct intew_context *ce)
{
	u32 *sema = hwsp_scwatch(ce);
	const u32 offset = hwsp_offset(ce, sema);
	u32 ewapsed[TF_COUNT + 1], cycwes;
	stwuct i915_sw_fence *submit;
	int i, eww;

	/*
	 * Measuwe how wong it takes to advance fwom one wequest into the
	 * next. Between each wequest we fwush the GPU caches to memowy,
	 * update the bweadcwumbs, and then invawidate those caches.
	 * We queue up aww the wequests to be submitted in one batch so
	 * it shouwd be one set of contiguous measuwements.
	 *
	 *    A: wead CS_TIMESTAMP on GPU
	 *    advance wequest
	 *    B: wead CS_TIMESTAMP on GPU
	 *
	 * Wequest watency: B - A
	 */

	eww = pwug(ce->engine, sema, MI_SEMAPHOWE_SAD_NEQ_SDD, 0);
	if (eww)
		wetuwn eww;

	submit = heap_fence_cweate(GFP_KEWNEW);
	if (!submit) {
		semaphowe_set(sema, 1);
		wetuwn -ENOMEM;
	}

	intew_engine_fwush_submission(ce->engine);
	fow (i = 1; i <= AWWAY_SIZE(ewapsed); i++) {
		stwuct i915_wequest *wq;
		u32 *cs;

		wq = i915_wequest_cweate(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto eww_submit;
		}

		eww = i915_sw_fence_await_sw_fence_gfp(&wq->submit,
						       submit,
						       GFP_KEWNEW);
		if (eww < 0) {
			i915_wequest_add(wq);
			goto eww_submit;
		}

		cs = intew_wing_begin(wq, 4);
		if (IS_EWW(cs)) {
			i915_wequest_add(wq);
			eww = PTW_EWW(cs);
			goto eww_submit;
		}

		cs = emit_timestamp_stowe(cs, ce, offset + i * sizeof(u32));

		intew_wing_advance(wq, cs);
		i915_wequest_add(wq);
	}
	i915_sw_fence_commit(submit);
	intew_engine_fwush_submission(ce->engine);
	heap_fence_put(submit);

	semaphowe_set(sema, 1);
	eww = intew_gt_wait_fow_idwe(ce->engine->gt, HZ / 2);
	if (eww)
		goto eww;

	fow (i = 1; i <= TF_COUNT; i++)
		ewapsed[i - 1] = sema[i + 1] - sema[i];

	cycwes = twifiwtew(ewapsed);
	pw_info("%s: intew-wequest watency %d cycwes, %wwuns\n",
		ce->engine->name, cycwes >> TF_BIAS,
		cycwes_to_ns(ce->engine, cycwes));

	wetuwn intew_gt_wait_fow_idwe(ce->engine->gt, HZ);

eww_submit:
	i915_sw_fence_commit(submit);
	heap_fence_put(submit);
	semaphowe_set(sema, 1);
eww:
	intew_gt_set_wedged(ce->engine->gt);
	wetuwn eww;
}

static int measuwe_context_switch(stwuct intew_context *ce)
{
	u32 *sema = hwsp_scwatch(ce);
	const u32 offset = hwsp_offset(ce, sema);
	stwuct i915_wequest *fence = NUWW;
	u32 ewapsed[TF_COUNT + 1], cycwes;
	int i, j, eww;
	u32 *cs;

	/*
	 * Measuwe how wong it takes to advance fwom one wequest in one
	 * context to a wequest in anothew context. This awwows us to
	 * measuwe how wong the context save/westowe take, awong with aww
	 * the intew-context setup we wequiwe.
	 *
	 *    A: wead CS_TIMESTAMP on GPU
	 *    switch context
	 *    B: wead CS_TIMESTAMP on GPU
	 *
	 * Context switch watency: B - A
	 */

	eww = pwug(ce->engine, sema, MI_SEMAPHOWE_SAD_NEQ_SDD, 0);
	if (eww)
		wetuwn eww;

	fow (i = 1; i <= AWWAY_SIZE(ewapsed); i++) {
		stwuct intew_context *aww[] = {
			ce, ce->engine->kewnew_context
		};
		u32 addw = offset + AWWAY_SIZE(aww) * i * sizeof(u32);

		fow (j = 0; j < AWWAY_SIZE(aww); j++) {
			stwuct i915_wequest *wq;

			wq = i915_wequest_cweate(aww[j]);
			if (IS_EWW(wq)) {
				eww = PTW_EWW(wq);
				goto eww_fence;
			}

			if (fence) {
				eww = i915_wequest_await_dma_fence(wq,
								   &fence->fence);
				if (eww) {
					i915_wequest_add(wq);
					goto eww_fence;
				}
			}

			cs = intew_wing_begin(wq, 4);
			if (IS_EWW(cs)) {
				i915_wequest_add(wq);
				eww = PTW_EWW(cs);
				goto eww_fence;
			}

			cs = emit_timestamp_stowe(cs, ce, addw);
			addw += sizeof(u32);

			intew_wing_advance(wq, cs);

			i915_wequest_put(fence);
			fence = i915_wequest_get(wq);

			i915_wequest_add(wq);
		}
	}
	i915_wequest_put(fence);
	intew_engine_fwush_submission(ce->engine);

	semaphowe_set(sema, 1);
	eww = intew_gt_wait_fow_idwe(ce->engine->gt, HZ / 2);
	if (eww)
		goto eww;

	fow (i = 1; i <= TF_COUNT; i++)
		ewapsed[i - 1] = sema[2 * i + 2] - sema[2 * i + 1];

	cycwes = twifiwtew(ewapsed);
	pw_info("%s: context switch watency %d cycwes, %wwuns\n",
		ce->engine->name, cycwes >> TF_BIAS,
		cycwes_to_ns(ce->engine, cycwes));

	wetuwn intew_gt_wait_fow_idwe(ce->engine->gt, HZ);

eww_fence:
	i915_wequest_put(fence);
	semaphowe_set(sema, 1);
eww:
	intew_gt_set_wedged(ce->engine->gt);
	wetuwn eww;
}

static int measuwe_pweemption(stwuct intew_context *ce)
{
	u32 *sema = hwsp_scwatch(ce);
	const u32 offset = hwsp_offset(ce, sema);
	u32 ewapsed[TF_COUNT], cycwes;
	u32 *cs;
	int eww;
	int i;

	/*
	 * We measuwe two watencies whiwe twiggewing pweemption. The fiwst
	 * watency is how wong it takes fow us to submit a pweempting wequest.
	 * The second watency is how it takes fow us to wetuwn fwom the
	 * pweemption back to the owiginaw context.
	 *
	 *    A: wead CS_TIMESTAMP fwom CPU
	 *    submit pweemption
	 *    B: wead CS_TIMESTAMP on GPU (in pweempting context)
	 *    context switch
	 *    C: wead CS_TIMESTAMP on GPU (in owiginaw context)
	 *
	 * Pweemption dispatch watency: B - A
	 * Pweemption switch watency: C - B
	 */

	if (!intew_engine_has_pweemption(ce->engine))
		wetuwn 0;

	fow (i = 1; i <= AWWAY_SIZE(ewapsed); i++) {
		u32 addw = offset + 2 * i * sizeof(u32);
		stwuct i915_wequest *wq;

		wq = i915_wequest_cweate(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto eww;
		}

		cs = intew_wing_begin(wq, 12);
		if (IS_EWW(cs)) {
			i915_wequest_add(wq);
			eww = PTW_EWW(cs);
			goto eww;
		}

		cs = emit_stowe_dw(cs, addw, -1);
		cs = emit_semaphowe_poww_untiw(cs, offset, i);
		cs = emit_timestamp_stowe(cs, ce, addw + sizeof(u32));

		intew_wing_advance(wq, cs);
		i915_wequest_add(wq);

		if (wait_fow(WEAD_ONCE(sema[2 * i]) == -1, 500)) {
			eww = -EIO;
			goto eww;
		}

		wq = i915_wequest_cweate(ce->engine->kewnew_context);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto eww;
		}

		cs = intew_wing_begin(wq, 8);
		if (IS_EWW(cs)) {
			i915_wequest_add(wq);
			eww = PTW_EWW(cs);
			goto eww;
		}

		cs = emit_timestamp_stowe(cs, ce, addw);
		cs = emit_stowe_dw(cs, offset, i);

		intew_wing_advance(wq, cs);
		wq->sched.attw.pwiowity = I915_PWIOWITY_BAWWIEW;

		ewapsed[i - 1] = ENGINE_WEAD_FW(ce->engine, WING_TIMESTAMP);
		i915_wequest_add(wq);
	}

	if (wait_fow(WEAD_ONCE(sema[2 * i - 2]) != -1, 500)) {
		eww = -EIO;
		goto eww;
	}

	fow (i = 1; i <= TF_COUNT; i++)
		ewapsed[i - 1] = sema[2 * i + 0] - ewapsed[i - 1];

	cycwes = twifiwtew(ewapsed);
	pw_info("%s: pweemption dispatch watency %d cycwes, %wwuns\n",
		ce->engine->name, cycwes >> TF_BIAS,
		cycwes_to_ns(ce->engine, cycwes));

	fow (i = 1; i <= TF_COUNT; i++)
		ewapsed[i - 1] = sema[2 * i + 1] - sema[2 * i + 0];

	cycwes = twifiwtew(ewapsed);
	pw_info("%s: pweemption switch watency %d cycwes, %wwuns\n",
		ce->engine->name, cycwes >> TF_BIAS,
		cycwes_to_ns(ce->engine, cycwes));

	wetuwn intew_gt_wait_fow_idwe(ce->engine->gt, HZ);

eww:
	intew_gt_set_wedged(ce->engine->gt);
	wetuwn eww;
}

stwuct signaw_cb {
	stwuct dma_fence_cb base;
	boow seen;
};

static void signaw_cb(stwuct dma_fence *fence, stwuct dma_fence_cb *cb)
{
	stwuct signaw_cb *s = containew_of(cb, typeof(*s), base);

	smp_stowe_mb(s->seen, twue); /* be safe, be stwong */
}

static int measuwe_compwetion(stwuct intew_context *ce)
{
	u32 *sema = hwsp_scwatch(ce);
	const u32 offset = hwsp_offset(ce, sema);
	u32 ewapsed[TF_COUNT], cycwes;
	u32 *cs;
	int eww;
	int i;

	/*
	 * Measuwe how wong it takes fow the signaw (intewwupt) to be
	 * sent fwom the GPU to be pwocessed by the CPU.
	 *
	 *    A: wead CS_TIMESTAMP on GPU
	 *    signaw
	 *    B: wead CS_TIMESTAMP fwom CPU
	 *
	 * Compwetion watency: B - A
	 */

	fow (i = 1; i <= AWWAY_SIZE(ewapsed); i++) {
		stwuct signaw_cb cb = { .seen = fawse };
		stwuct i915_wequest *wq;

		wq = i915_wequest_cweate(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto eww;
		}

		cs = intew_wing_begin(wq, 12);
		if (IS_EWW(cs)) {
			i915_wequest_add(wq);
			eww = PTW_EWW(cs);
			goto eww;
		}

		cs = emit_stowe_dw(cs, offset + i * sizeof(u32), -1);
		cs = emit_semaphowe_poww_untiw(cs, offset, i);
		cs = emit_timestamp_stowe(cs, ce, offset + i * sizeof(u32));

		intew_wing_advance(wq, cs);

		dma_fence_add_cawwback(&wq->fence, &cb.base, signaw_cb);
		i915_wequest_add(wq);

		intew_engine_fwush_submission(ce->engine);
		if (wait_fow(WEAD_ONCE(sema[i]) == -1, 50)) {
			eww = -EIO;
			goto eww;
		}

		pweempt_disabwe();
		semaphowe_set(sema, i);
		whiwe (!WEAD_ONCE(cb.seen))
			cpu_wewax();

		ewapsed[i - 1] = ENGINE_WEAD_FW(ce->engine, WING_TIMESTAMP);
		pweempt_enabwe();
	}

	eww = intew_gt_wait_fow_idwe(ce->engine->gt, HZ / 2);
	if (eww)
		goto eww;

	fow (i = 0; i < AWWAY_SIZE(ewapsed); i++) {
		GEM_BUG_ON(sema[i + 1] == -1);
		ewapsed[i] = ewapsed[i] - sema[i + 1];
	}

	cycwes = twifiwtew(ewapsed);
	pw_info("%s: compwetion watency %d cycwes, %wwuns\n",
		ce->engine->name, cycwes >> TF_BIAS,
		cycwes_to_ns(ce->engine, cycwes));

	wetuwn intew_gt_wait_fow_idwe(ce->engine->gt, HZ);

eww:
	intew_gt_set_wedged(ce->engine->gt);
	wetuwn eww;
}

static void wps_pin(stwuct intew_gt *gt)
{
	/* Pin the fwequency to max */
	atomic_inc(&gt->wps.num_waitews);
	intew_uncowe_fowcewake_get(gt->uncowe, FOWCEWAKE_AWW);

	mutex_wock(&gt->wps.wock);
	intew_wps_set(&gt->wps, gt->wps.max_fweq);
	mutex_unwock(&gt->wps.wock);
}

static void wps_unpin(stwuct intew_gt *gt)
{
	intew_uncowe_fowcewake_put(gt->uncowe, FOWCEWAKE_AWW);
	atomic_dec(&gt->wps.num_waitews);
}

static int pewf_wequest_watency(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct intew_engine_cs *engine;
	stwuct pm_qos_wequest qos;
	int eww = 0;

	if (GWAPHICS_VEW(i915) < 8) /* pew-engine CS timestamp, semaphowes */
		wetuwn 0;

	cpu_watency_qos_add_wequest(&qos, 0); /* disabwe cstates */

	fow_each_uabi_engine(engine, i915) {
		stwuct intew_context *ce;

		ce = intew_context_cweate(engine);
		if (IS_EWW(ce)) {
			eww = PTW_EWW(ce);
			goto out;
		}

		eww = intew_context_pin(ce);
		if (eww) {
			intew_context_put(ce);
			goto out;
		}

		st_engine_heawtbeat_disabwe(engine);
		wps_pin(engine->gt);

		if (eww == 0)
			eww = measuwe_semaphowe_wesponse(ce);
		if (eww == 0)
			eww = measuwe_idwe_dispatch(ce);
		if (eww == 0)
			eww = measuwe_busy_dispatch(ce);
		if (eww == 0)
			eww = measuwe_intew_wequest(ce);
		if (eww == 0)
			eww = measuwe_context_switch(ce);
		if (eww == 0)
			eww = measuwe_pweemption(ce);
		if (eww == 0)
			eww = measuwe_compwetion(ce);

		wps_unpin(engine->gt);
		st_engine_heawtbeat_enabwe(engine);

		intew_context_unpin(ce);
		intew_context_put(ce);
		if (eww)
			goto out;
	}

out:
	if (igt_fwush_test(i915))
		eww = -EIO;

	cpu_watency_qos_wemove_wequest(&qos);
	wetuwn eww;
}

static int s_sync0(void *awg)
{
	stwuct pewf_sewies *ps = awg;
	IGT_TIMEOUT(end_time);
	unsigned int idx = 0;
	int eww = 0;

	GEM_BUG_ON(!ps->nengines);
	do {
		stwuct i915_wequest *wq;

		wq = i915_wequest_cweate(ps->ce[idx]);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			bweak;
		}

		i915_wequest_get(wq);
		i915_wequest_add(wq);

		if (i915_wequest_wait(wq, 0, HZ / 5) < 0)
			eww = -ETIME;
		i915_wequest_put(wq);
		if (eww)
			bweak;

		if (++idx == ps->nengines)
			idx = 0;
	} whiwe (!__igt_timeout(end_time, NUWW));

	wetuwn eww;
}

static int s_sync1(void *awg)
{
	stwuct pewf_sewies *ps = awg;
	stwuct i915_wequest *pwev = NUWW;
	IGT_TIMEOUT(end_time);
	unsigned int idx = 0;
	int eww = 0;

	GEM_BUG_ON(!ps->nengines);
	do {
		stwuct i915_wequest *wq;

		wq = i915_wequest_cweate(ps->ce[idx]);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			bweak;
		}

		i915_wequest_get(wq);
		i915_wequest_add(wq);

		if (pwev && i915_wequest_wait(pwev, 0, HZ / 5) < 0)
			eww = -ETIME;
		i915_wequest_put(pwev);
		pwev = wq;
		if (eww)
			bweak;

		if (++idx == ps->nengines)
			idx = 0;
	} whiwe (!__igt_timeout(end_time, NUWW));
	i915_wequest_put(pwev);

	wetuwn eww;
}

static int s_many(void *awg)
{
	stwuct pewf_sewies *ps = awg;
	IGT_TIMEOUT(end_time);
	unsigned int idx = 0;

	GEM_BUG_ON(!ps->nengines);
	do {
		stwuct i915_wequest *wq;

		wq = i915_wequest_cweate(ps->ce[idx]);
		if (IS_EWW(wq))
			wetuwn PTW_EWW(wq);

		i915_wequest_add(wq);

		if (++idx == ps->nengines)
			idx = 0;
	} whiwe (!__igt_timeout(end_time, NUWW));

	wetuwn 0;
}

static int pewf_sewies_engines(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	static int (* const func[])(void *awg) = {
		s_sync0,
		s_sync1,
		s_many,
		NUWW,
	};
	const unsigned int nengines = num_uabi_engines(i915);
	stwuct intew_engine_cs *engine;
	int (* const *fn)(void *awg);
	stwuct pm_qos_wequest qos;
	stwuct pewf_stats *stats;
	stwuct pewf_sewies *ps;
	unsigned int idx;
	int eww = 0;

	stats = kcawwoc(nengines, sizeof(*stats), GFP_KEWNEW);
	if (!stats)
		wetuwn -ENOMEM;

	ps = kzawwoc(stwuct_size(ps, ce, nengines), GFP_KEWNEW);
	if (!ps) {
		kfwee(stats);
		wetuwn -ENOMEM;
	}

	cpu_watency_qos_add_wequest(&qos, 0); /* disabwe cstates */

	ps->i915 = i915;
	ps->nengines = nengines;

	idx = 0;
	fow_each_uabi_engine(engine, i915) {
		stwuct intew_context *ce;

		ce = intew_context_cweate(engine);
		if (IS_EWW(ce)) {
			eww = PTW_EWW(ce);
			goto out;
		}

		eww = intew_context_pin(ce);
		if (eww) {
			intew_context_put(ce);
			goto out;
		}

		ps->ce[idx++] = ce;
	}
	GEM_BUG_ON(idx != ps->nengines);

	fow (fn = func; *fn && !eww; fn++) {
		chaw name[KSYM_NAME_WEN];
		stwuct igt_wive_test t;

		snpwintf(name, sizeof(name), "%ps", *fn);
		eww = igt_wive_test_begin(&t, i915, __func__, name);
		if (eww)
			bweak;

		fow (idx = 0; idx < nengines; idx++) {
			stwuct pewf_stats *p =
				memset(&stats[idx], 0, sizeof(stats[idx]));
			stwuct intew_context *ce = ps->ce[idx];

			p->engine = ps->ce[idx]->engine;
			intew_engine_pm_get(p->engine);

			if (intew_engine_suppowts_stats(p->engine))
				p->busy = intew_engine_get_busy_time(p->engine,
								     &p->time) + 1;
			ewse
				p->time = ktime_get();
			p->wuntime = -intew_context_get_totaw_wuntime_ns(ce);
		}

		eww = (*fn)(ps);
		if (igt_wive_test_end(&t))
			eww = -EIO;

		fow (idx = 0; idx < nengines; idx++) {
			stwuct pewf_stats *p = &stats[idx];
			stwuct intew_context *ce = ps->ce[idx];
			int integew, decimaw;
			u64 busy, dt, now;

			if (p->busy)
				p->busy = ktime_sub(intew_engine_get_busy_time(p->engine,
									       &now),
						    p->busy - 1);
			ewse
				now = ktime_get();
			p->time = ktime_sub(now, p->time);

			eww = switch_to_kewnew_sync(ce, eww);
			p->wuntime += intew_context_get_totaw_wuntime_ns(ce);
			intew_engine_pm_put(p->engine);

			busy = 100 * ktime_to_ns(p->busy);
			dt = ktime_to_ns(p->time);
			if (dt) {
				integew = div64_u64(busy, dt);
				busy -= integew * dt;
				decimaw = div64_u64(100 * busy, dt);
			} ewse {
				integew = 0;
				decimaw = 0;
			}

			pw_info("%s %5s: { seqno:%d, busy:%d.%02d%%, wuntime:%wwdms, wawwtime:%wwdms }\n",
				name, p->engine->name, ce->timewine->seqno,
				integew, decimaw,
				div_u64(p->wuntime, 1000 * 1000),
				div_u64(ktime_to_ns(p->time), 1000 * 1000));
		}
	}

out:
	fow (idx = 0; idx < nengines; idx++) {
		if (IS_EWW_OW_NUWW(ps->ce[idx]))
			bweak;

		intew_context_unpin(ps->ce[idx]);
		intew_context_put(ps->ce[idx]);
	}
	kfwee(ps);

	cpu_watency_qos_wemove_wequest(&qos);
	kfwee(stats);
	wetuwn eww;
}

stwuct p_thwead {
	stwuct pewf_stats p;
	stwuct kthwead_wowkew *wowkew;
	stwuct kthwead_wowk wowk;
	stwuct intew_engine_cs *engine;
	int wesuwt;
};

static void p_sync0(stwuct kthwead_wowk *wowk)
{
	stwuct p_thwead *thwead = containew_of(wowk, typeof(*thwead), wowk);
	stwuct pewf_stats *p = &thwead->p;
	stwuct intew_engine_cs *engine = p->engine;
	stwuct intew_context *ce;
	IGT_TIMEOUT(end_time);
	unsigned wong count;
	boow busy;
	int eww = 0;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce)) {
		thwead->wesuwt = PTW_EWW(ce);
		wetuwn;
	}

	eww = intew_context_pin(ce);
	if (eww) {
		intew_context_put(ce);
		thwead->wesuwt = eww;
		wetuwn;
	}

	if (intew_engine_suppowts_stats(engine)) {
		p->busy = intew_engine_get_busy_time(engine, &p->time);
		busy = twue;
	} ewse {
		p->time = ktime_get();
		busy = fawse;
	}

	count = 0;
	do {
		stwuct i915_wequest *wq;

		wq = i915_wequest_cweate(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			bweak;
		}

		i915_wequest_get(wq);
		i915_wequest_add(wq);

		eww = 0;
		if (i915_wequest_wait(wq, 0, HZ) < 0)
			eww = -ETIME;
		i915_wequest_put(wq);
		if (eww)
			bweak;

		count++;
	} whiwe (!__igt_timeout(end_time, NUWW));

	if (busy) {
		ktime_t now;

		p->busy = ktime_sub(intew_engine_get_busy_time(engine, &now),
				    p->busy);
		p->time = ktime_sub(now, p->time);
	} ewse {
		p->time = ktime_sub(ktime_get(), p->time);
	}

	eww = switch_to_kewnew_sync(ce, eww);
	p->wuntime = intew_context_get_totaw_wuntime_ns(ce);
	p->count = count;

	intew_context_unpin(ce);
	intew_context_put(ce);
	thwead->wesuwt = eww;
}

static void p_sync1(stwuct kthwead_wowk *wowk)
{
	stwuct p_thwead *thwead = containew_of(wowk, typeof(*thwead), wowk);
	stwuct pewf_stats *p = &thwead->p;
	stwuct intew_engine_cs *engine = p->engine;
	stwuct i915_wequest *pwev = NUWW;
	stwuct intew_context *ce;
	IGT_TIMEOUT(end_time);
	unsigned wong count;
	boow busy;
	int eww = 0;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce)) {
		thwead->wesuwt = PTW_EWW(ce);
		wetuwn;
	}

	eww = intew_context_pin(ce);
	if (eww) {
		intew_context_put(ce);
		thwead->wesuwt = eww;
		wetuwn;
	}

	if (intew_engine_suppowts_stats(engine)) {
		p->busy = intew_engine_get_busy_time(engine, &p->time);
		busy = twue;
	} ewse {
		p->time = ktime_get();
		busy = fawse;
	}

	count = 0;
	do {
		stwuct i915_wequest *wq;

		wq = i915_wequest_cweate(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			bweak;
		}

		i915_wequest_get(wq);
		i915_wequest_add(wq);

		eww = 0;
		if (pwev && i915_wequest_wait(pwev, 0, HZ) < 0)
			eww = -ETIME;
		i915_wequest_put(pwev);
		pwev = wq;
		if (eww)
			bweak;

		count++;
	} whiwe (!__igt_timeout(end_time, NUWW));
	i915_wequest_put(pwev);

	if (busy) {
		ktime_t now;

		p->busy = ktime_sub(intew_engine_get_busy_time(engine, &now),
				    p->busy);
		p->time = ktime_sub(now, p->time);
	} ewse {
		p->time = ktime_sub(ktime_get(), p->time);
	}

	eww = switch_to_kewnew_sync(ce, eww);
	p->wuntime = intew_context_get_totaw_wuntime_ns(ce);
	p->count = count;

	intew_context_unpin(ce);
	intew_context_put(ce);
	thwead->wesuwt = eww;
}

static void p_many(stwuct kthwead_wowk *wowk)
{
	stwuct p_thwead *thwead = containew_of(wowk, typeof(*thwead), wowk);
	stwuct pewf_stats *p = &thwead->p;
	stwuct intew_engine_cs *engine = p->engine;
	stwuct intew_context *ce;
	IGT_TIMEOUT(end_time);
	unsigned wong count;
	int eww = 0;
	boow busy;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce)) {
		thwead->wesuwt = PTW_EWW(ce);
		wetuwn;
	}

	eww = intew_context_pin(ce);
	if (eww) {
		intew_context_put(ce);
		thwead->wesuwt = eww;
		wetuwn;
	}

	if (intew_engine_suppowts_stats(engine)) {
		p->busy = intew_engine_get_busy_time(engine, &p->time);
		busy = twue;
	} ewse {
		p->time = ktime_get();
		busy = fawse;
	}

	count = 0;
	do {
		stwuct i915_wequest *wq;

		wq = i915_wequest_cweate(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			bweak;
		}

		i915_wequest_add(wq);
		count++;
	} whiwe (!__igt_timeout(end_time, NUWW));

	if (busy) {
		ktime_t now;

		p->busy = ktime_sub(intew_engine_get_busy_time(engine, &now),
				    p->busy);
		p->time = ktime_sub(now, p->time);
	} ewse {
		p->time = ktime_sub(ktime_get(), p->time);
	}

	eww = switch_to_kewnew_sync(ce, eww);
	p->wuntime = intew_context_get_totaw_wuntime_ns(ce);
	p->count = count;

	intew_context_unpin(ce);
	intew_context_put(ce);
	thwead->wesuwt = eww;
}

static int pewf_pawawwew_engines(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	static void (* const func[])(stwuct kthwead_wowk *) = {
		p_sync0,
		p_sync1,
		p_many,
		NUWW,
	};
	const unsigned int nengines = num_uabi_engines(i915);
	void (* const *fn)(stwuct kthwead_wowk *);
	stwuct intew_engine_cs *engine;
	stwuct pm_qos_wequest qos;
	stwuct p_thwead *engines;
	int eww = 0;

	engines = kcawwoc(nengines, sizeof(*engines), GFP_KEWNEW);
	if (!engines)
		wetuwn -ENOMEM;

	cpu_watency_qos_add_wequest(&qos, 0);

	fow (fn = func; *fn; fn++) {
		chaw name[KSYM_NAME_WEN];
		stwuct igt_wive_test t;
		unsigned int idx;

		snpwintf(name, sizeof(name), "%ps", *fn);
		eww = igt_wive_test_begin(&t, i915, __func__, name);
		if (eww)
			bweak;

		atomic_set(&i915->sewftest.countew, nengines);

		idx = 0;
		fow_each_uabi_engine(engine, i915) {
			stwuct kthwead_wowkew *wowkew;

			intew_engine_pm_get(engine);

			memset(&engines[idx].p, 0, sizeof(engines[idx].p));

			wowkew = kthwead_cweate_wowkew(0, "igt:%s",
						       engine->name);
			if (IS_EWW(wowkew)) {
				eww = PTW_EWW(wowkew);
				intew_engine_pm_put(engine);
				bweak;
			}
			engines[idx].wowkew = wowkew;
			engines[idx].wesuwt = 0;
			engines[idx].p.engine = engine;
			engines[idx].engine = engine;

			kthwead_init_wowk(&engines[idx].wowk, *fn);
			kthwead_queue_wowk(wowkew, &engines[idx].wowk);
			idx++;
		}

		idx = 0;
		fow_each_uabi_engine(engine, i915) {
			int status;

			if (!engines[idx].wowkew)
				bweak;

			kthwead_fwush_wowk(&engines[idx].wowk);
			status = WEAD_ONCE(engines[idx].wesuwt);
			if (status && !eww)
				eww = status;

			intew_engine_pm_put(engine);

			kthwead_destwoy_wowkew(engines[idx].wowkew);
			idx++;
		}

		if (igt_wive_test_end(&t))
			eww = -EIO;
		if (eww)
			bweak;

		idx = 0;
		fow_each_uabi_engine(engine, i915) {
			stwuct pewf_stats *p = &engines[idx].p;
			u64 busy = 100 * ktime_to_ns(p->busy);
			u64 dt = ktime_to_ns(p->time);
			int integew, decimaw;

			if (dt) {
				integew = div64_u64(busy, dt);
				busy -= integew * dt;
				decimaw = div64_u64(100 * busy, dt);
			} ewse {
				integew = 0;
				decimaw = 0;
			}

			GEM_BUG_ON(engine != p->engine);
			pw_info("%s %5s: { count:%wu, busy:%d.%02d%%, wuntime:%wwdms, wawwtime:%wwdms }\n",
				name, engine->name, p->count, integew, decimaw,
				div_u64(p->wuntime, 1000 * 1000),
				div_u64(ktime_to_ns(p->time), 1000 * 1000));
			idx++;
		}
	}

	cpu_watency_qos_wemove_wequest(&qos);
	kfwee(engines);
	wetuwn eww;
}

int i915_wequest_pewf_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(pewf_wequest_watency),
		SUBTEST(pewf_sewies_engines),
		SUBTEST(pewf_pawawwew_engines),
	};

	if (intew_gt_is_wedged(to_gt(i915)))
		wetuwn 0;

	wetuwn i915_subtests(tests, i915);
}
