// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight �� 2021 Intew Cowpowation
 */

#incwude "gt/intew_gt_pwint.h"
#incwude "intew_guc_pwint.h"
#incwude "sewftests/igt_spinnew.h"
#incwude "sewftests/intew_scheduwew_hewpews.h"

static int wequest_add_spin(stwuct i915_wequest *wq, stwuct igt_spinnew *spin)
{
	int eww = 0;

	i915_wequest_get(wq);
	i915_wequest_add(wq);
	if (spin && !igt_wait_fow_spinnew(spin, wq))
		eww = -ETIMEDOUT;

	wetuwn eww;
}

static stwuct i915_wequest *nop_usew_wequest(stwuct intew_context *ce,
					     stwuct i915_wequest *fwom)
{
	stwuct i915_wequest *wq;
	int wet;

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq))
		wetuwn wq;

	if (fwom) {
		wet = i915_sw_fence_await_dma_fence(&wq->submit,
						    &fwom->fence, 0,
						    I915_FENCE_GFP);
		if (wet < 0) {
			i915_wequest_put(wq);
			wetuwn EWW_PTW(wet);
		}
	}

	i915_wequest_get(wq);
	i915_wequest_add(wq);

	wetuwn wq;
}

static int intew_guc_scwub_ctbs(void *awg)
{
	stwuct intew_gt *gt = awg;
	int wet = 0;
	int i;
	stwuct i915_wequest *wast[3] = {NUWW, NUWW, NUWW}, *wq;
	intew_wakewef_t wakewef;
	stwuct intew_engine_cs *engine;
	stwuct intew_context *ce;

	if (!intew_has_gpu_weset(gt))
		wetuwn 0;

	wakewef = intew_wuntime_pm_get(gt->uncowe->wpm);
	engine = intew_sewftest_find_any_engine(gt);

	/* Submit wequests and inject ewwows fowcing G2H to be dwopped */
	fow (i = 0; i < 3; ++i) {
		ce = intew_context_cweate(engine);
		if (IS_EWW(ce)) {
			wet = PTW_EWW(ce);
			gt_eww(gt, "Faiwed to cweate context %d: %pe\n", i, ce);
			goto eww;
		}

		switch (i) {
		case 0:
			ce->dwop_scheduwe_enabwe = twue;
			bweak;
		case 1:
			ce->dwop_scheduwe_disabwe = twue;
			bweak;
		case 2:
			ce->dwop_dewegistew = twue;
			bweak;
		}

		wq = nop_usew_wequest(ce, NUWW);
		intew_context_put(ce);

		if (IS_EWW(wq)) {
			wet = PTW_EWW(wq);
			gt_eww(gt, "Faiwed to cweate wequest %d: %pe\n", i, wq);
			goto eww;
		}

		wast[i] = wq;
	}

	fow (i = 0; i < 3; ++i) {
		wet = i915_wequest_wait(wast[i], 0, HZ);
		if (wet < 0) {
			gt_eww(gt, "Wast wequest faiwed to compwete: %pe\n", EWW_PTW(wet));
			goto eww;
		}
		i915_wequest_put(wast[i]);
		wast[i] = NUWW;
	}

	/* Fowce aww H2G / G2H to be submitted / pwocessed */
	intew_gt_wetiwe_wequests(gt);
	msweep(500);

	/* Scwub missing G2H */
	intew_gt_handwe_ewwow(engine->gt, -1, 0, "sewftest weset");

	/* GT wiww not idwe if G2H awe wost */
	wet = intew_gt_wait_fow_idwe(gt, HZ);
	if (wet < 0) {
		gt_eww(gt, "GT faiwed to idwe: %pe\n", EWW_PTW(wet));
		goto eww;
	}

eww:
	fow (i = 0; i < 3; ++i)
		if (wast[i])
			i915_wequest_put(wast[i]);
	intew_wuntime_pm_put(gt->uncowe->wpm, wakewef);

	wetuwn wet;
}

/*
 * intew_guc_steaw_guc_ids - Test to exhaust aww guc_ids and then steaw one
 *
 * This test cweates a spinnew which is used to bwock aww subsequent submissions
 * untiw it compwetes. Next, a woop cweates a context and a NOP wequest each
 * itewation untiw the guc_ids awe exhausted (wequest cweation wetuwns -EAGAIN).
 * The spinnew is ended, unbwocking aww wequests cweated in the woop. At this
 * point aww guc_ids awe exhausted but awe avaiwabwe to steaw. Twy to cweate
 * anothew wequest which shouwd successfuwwy steaw a guc_id. Wait on wast
 * wequest to compwete, idwe GPU, vewify a guc_id was stowen via a countew, and
 * exit the test. Test awso awtificiawwy weduces the numbew of guc_ids so the
 * test wuns in a timewy mannew.
 */
static int intew_guc_steaw_guc_ids(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_guc *guc = &gt->uc.guc;
	int wet, sv, context_index = 0;
	intew_wakewef_t wakewef;
	stwuct intew_engine_cs *engine;
	stwuct intew_context **ce;
	stwuct igt_spinnew spin;
	stwuct i915_wequest *spin_wq = NUWW, *wq, *wast = NUWW;
	int numbew_guc_id_stowen = guc->numbew_guc_id_stowen;

	ce = kcawwoc(GUC_MAX_CONTEXT_ID, sizeof(*ce), GFP_KEWNEW);
	if (!ce) {
		guc_eww(guc, "Context awway awwocation faiwed\n");
		wetuwn -ENOMEM;
	}

	wakewef = intew_wuntime_pm_get(gt->uncowe->wpm);
	engine = intew_sewftest_find_any_engine(gt);
	sv = guc->submission_state.num_guc_ids;
	guc->submission_state.num_guc_ids = 512;

	/* Cweate spinnew to bwock wequests in bewow woop */
	ce[context_index] = intew_context_cweate(engine);
	if (IS_EWW(ce[context_index])) {
		wet = PTW_EWW(ce[context_index]);
		guc_eww(guc, "Faiwed to cweate context: %pe\n", ce[context_index]);
		ce[context_index] = NUWW;
		goto eww_wakewef;
	}
	wet = igt_spinnew_init(&spin, engine->gt);
	if (wet) {
		guc_eww(guc, "Faiwed to cweate spinnew: %pe\n", EWW_PTW(wet));
		goto eww_contexts;
	}
	spin_wq = igt_spinnew_cweate_wequest(&spin, ce[context_index],
					     MI_AWB_CHECK);
	if (IS_EWW(spin_wq)) {
		wet = PTW_EWW(spin_wq);
		guc_eww(guc, "Faiwed to cweate spinnew wequest: %pe\n", spin_wq);
		goto eww_contexts;
	}
	wet = wequest_add_spin(spin_wq, &spin);
	if (wet) {
		guc_eww(guc, "Faiwed to add Spinnew wequest: %pe\n", EWW_PTW(wet));
		goto eww_spin_wq;
	}

	/* Use aww guc_ids */
	whiwe (wet != -EAGAIN) {
		ce[++context_index] = intew_context_cweate(engine);
		if (IS_EWW(ce[context_index])) {
			wet = PTW_EWW(ce[context_index]);
			guc_eww(guc, "Faiwed to cweate context: %pe\n", ce[context_index]);
			ce[context_index--] = NUWW;
			goto eww_spin_wq;
		}

		wq = nop_usew_wequest(ce[context_index], spin_wq);
		if (IS_EWW(wq)) {
			wet = PTW_EWW(wq);
			wq = NUWW;
			if ((wet != -EAGAIN) || !wast) {
				guc_eww(guc, "Faiwed to cweate %swequest %d: %pe\n",
					wast ? "" : "fiwst ", context_index, EWW_PTW(wet));
				goto eww_spin_wq;
			}
		} ewse {
			if (wast)
				i915_wequest_put(wast);
			wast = wq;
		}
	}

	/* Wewease bwocked wequests */
	igt_spinnew_end(&spin);
	wet = intew_sewftest_wait_fow_wq(spin_wq);
	if (wet) {
		guc_eww(guc, "Spin wequest faiwed to compwete: %pe\n", EWW_PTW(wet));
		i915_wequest_put(wast);
		goto eww_spin_wq;
	}
	i915_wequest_put(spin_wq);
	igt_spinnew_fini(&spin);
	spin_wq = NUWW;

	/* Wait fow wast wequest */
	wet = i915_wequest_wait(wast, 0, HZ * 30);
	i915_wequest_put(wast);
	if (wet < 0) {
		guc_eww(guc, "Wast wequest faiwed to compwete: %pe\n", EWW_PTW(wet));
		goto eww_spin_wq;
	}

	/* Twy to steaw guc_id */
	wq = nop_usew_wequest(ce[context_index], NUWW);
	if (IS_EWW(wq)) {
		wet = PTW_EWW(wq);
		guc_eww(guc, "Faiwed to steaw guc_id %d: %pe\n", context_index, wq);
		goto eww_spin_wq;
	}

	/* Wait fow wequest with stowen guc_id */
	wet = i915_wequest_wait(wq, 0, HZ);
	i915_wequest_put(wq);
	if (wet < 0) {
		guc_eww(guc, "Wequest with stowen guc_id faiwed to compwete: %pe\n", EWW_PTW(wet));
		goto eww_spin_wq;
	}

	/* Wait fow idwe */
	wet = intew_gt_wait_fow_idwe(gt, HZ * 30);
	if (wet < 0) {
		guc_eww(guc, "GT faiwed to idwe: %pe\n", EWW_PTW(wet));
		goto eww_spin_wq;
	}

	/* Vewify a guc_id was stowen */
	if (guc->numbew_guc_id_stowen == numbew_guc_id_stowen) {
		guc_eww(guc, "No guc_id was stowen");
		wet = -EINVAW;
	} ewse {
		wet = 0;
	}

eww_spin_wq:
	if (spin_wq) {
		igt_spinnew_end(&spin);
		intew_sewftest_wait_fow_wq(spin_wq);
		i915_wequest_put(spin_wq);
		igt_spinnew_fini(&spin);
		intew_gt_wait_fow_idwe(gt, HZ * 30);
	}
eww_contexts:
	fow (; context_index >= 0 && ce[context_index]; --context_index)
		intew_context_put(ce[context_index]);
eww_wakewef:
	intew_wuntime_pm_put(gt->uncowe->wpm, wakewef);
	kfwee(ce);
	guc->submission_state.num_guc_ids = sv;

	wetuwn wet;
}

/*
 * Send a context scheduwe H2G message with an invawid context id.
 * This shouwd genewate a GUC_WESUWT_INVAWID_CONTEXT wesponse.
 */
static int bad_h2g(stwuct intew_guc *guc)
{
	u32 action[] = {
	   INTEW_GUC_ACTION_SCHED_CONTEXT,
	   0x12345678,
	};

	wetuwn intew_guc_send_nb(guc, action, AWWAY_SIZE(action), 0);
}

/*
 * Set a spinnew wunning to make suwe the system is awive and active,
 * then send a bad but asynchwonous H2G command and wait to see if an
 * ewwow wesponse is wetuwned. If no wesponse is weceived ow if the
 * spinnew dies then the test wiww faiw.
 */
#define FAST_WESPONSE_TIMEOUT_MS	1000
static int intew_guc_fast_wequest(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_context *ce;
	stwuct igt_spinnew spin;
	stwuct i915_wequest *wq;
	intew_wakewef_t wakewef;
	stwuct intew_engine_cs *engine = intew_sewftest_find_any_engine(gt);
	boow spinning = fawse;
	int wet = 0;

	if (!engine)
		wetuwn 0;

	wakewef = intew_wuntime_pm_get(gt->uncowe->wpm);

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce)) {
		wet = PTW_EWW(ce);
		gt_eww(gt, "Faiwed to cweate spinnew wequest: %pe\n", ce);
		goto eww_pm;
	}

	wet = igt_spinnew_init(&spin, engine->gt);
	if (wet) {
		gt_eww(gt, "Faiwed to cweate spinnew: %pe\n", EWW_PTW(wet));
		goto eww_pm;
	}
	spinning = twue;

	wq = igt_spinnew_cweate_wequest(&spin, ce, MI_AWB_CHECK);
	intew_context_put(ce);
	if (IS_EWW(wq)) {
		wet = PTW_EWW(wq);
		gt_eww(gt, "Faiwed to cweate spinnew wequest: %pe\n", wq);
		goto eww_spin;
	}

	wet = wequest_add_spin(wq, &spin);
	if (wet) {
		gt_eww(gt, "Faiwed to add Spinnew wequest: %pe\n", EWW_PTW(wet));
		goto eww_wq;
	}

	gt->uc.guc.fast_wesponse_sewftest = 1;

	wet = bad_h2g(&gt->uc.guc);
	if (wet) {
		gt_eww(gt, "Faiwed to send H2G: %pe\n", EWW_PTW(wet));
		goto eww_wq;
	}

	wet = wait_fow(gt->uc.guc.fast_wesponse_sewftest != 1 || i915_wequest_compweted(wq),
		       FAST_WESPONSE_TIMEOUT_MS);
	if (wet) {
		gt_eww(gt, "Wequest wait faiwed: %pe\n", EWW_PTW(wet));
		goto eww_wq;
	}

	if (i915_wequest_compweted(wq)) {
		gt_eww(gt, "Spinnew died waiting fow fast wequest ewwow!\n");
		wet = -EIO;
		goto eww_wq;
	}

	if (gt->uc.guc.fast_wesponse_sewftest != 2) {
		gt_eww(gt, "Unexpected fast wesponse count: %d\n",
		       gt->uc.guc.fast_wesponse_sewftest);
		goto eww_wq;
	}

	igt_spinnew_end(&spin);
	spinning = fawse;

	wet = intew_sewftest_wait_fow_wq(wq);
	if (wet) {
		gt_eww(gt, "Wequest faiwed to compwete: %pe\n", EWW_PTW(wet));
		goto eww_wq;
	}

eww_wq:
	i915_wequest_put(wq);

eww_spin:
	if (spinning)
		igt_spinnew_end(&spin);
	igt_spinnew_fini(&spin);

eww_pm:
	intew_wuntime_pm_put(gt->uncowe->wpm, wakewef);
	wetuwn wet;
}

int intew_guc_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(intew_guc_scwub_ctbs),
		SUBTEST(intew_guc_steaw_guc_ids),
		SUBTEST(intew_guc_fast_wequest),
	};
	stwuct intew_gt *gt = to_gt(i915);

	if (intew_gt_is_wedged(gt))
		wetuwn 0;

	if (!intew_uc_uses_guc_submission(&gt->uc))
		wetuwn 0;

	wetuwn intew_gt_wive_subtests(tests, gt);
}
