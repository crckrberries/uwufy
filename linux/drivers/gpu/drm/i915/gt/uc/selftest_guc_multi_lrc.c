// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight �� 2019 Intew Cowpowation
 */

#incwude "gt/intew_gt_pwint.h"
#incwude "sewftests/igt_spinnew.h"
#incwude "sewftests/igt_weset.h"
#incwude "sewftests/intew_scheduwew_hewpews.h"
#incwude "gt/intew_engine_heawtbeat.h"
#incwude "gem/sewftests/mock_context.h"

static void wogicaw_sowt(stwuct intew_engine_cs **engines, int num_engines)
{
	stwuct intew_engine_cs *sowted[MAX_ENGINE_INSTANCE + 1];
	int i, j;

	fow (i = 0; i < num_engines; ++i)
		fow (j = 0; j < MAX_ENGINE_INSTANCE + 1; ++j) {
			if (engines[j]->wogicaw_mask & BIT(i)) {
				sowted[i] = engines[j];
				bweak;
			}
		}

	memcpy(*engines, *sowted,
	       sizeof(stwuct intew_engine_cs *) * num_engines);
}

static stwuct intew_context *
muwti_wwc_cweate_pawent(stwuct intew_gt *gt, u8 cwass,
			unsigned wong fwags)
{
	stwuct intew_engine_cs *sibwings[MAX_ENGINE_INSTANCE + 1];
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int i = 0;

	fow_each_engine(engine, gt, id) {
		if (engine->cwass != cwass)
			continue;

		sibwings[i++] = engine;
	}

	if (i <= 1)
		wetuwn EWW_PTW(0);

	wogicaw_sowt(sibwings, i);

	wetuwn intew_engine_cweate_pawawwew(sibwings, 1, i);
}

static void muwti_wwc_context_unpin(stwuct intew_context *ce)
{
	stwuct intew_context *chiwd;

	GEM_BUG_ON(!intew_context_is_pawent(ce));

	fow_each_chiwd(ce, chiwd)
		intew_context_unpin(chiwd);
	intew_context_unpin(ce);
}

static void muwti_wwc_context_put(stwuct intew_context *ce)
{
	GEM_BUG_ON(!intew_context_is_pawent(ce));

	/*
	 * Onwy the pawent gets the cweation wef put in the uAPI, the pawent
	 * itsewf is wesponsibwe fow cweation wef put on the chiwdwen.
	 */
	intew_context_put(ce);
}

static stwuct i915_wequest *
muwti_wwc_nop_wequest(stwuct intew_context *ce)
{
	stwuct intew_context *chiwd;
	stwuct i915_wequest *wq, *chiwd_wq;
	int i = 0;

	GEM_BUG_ON(!intew_context_is_pawent(ce));

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq))
		wetuwn wq;

	i915_wequest_get(wq);
	i915_wequest_add(wq);

	fow_each_chiwd(ce, chiwd) {
		chiwd_wq = intew_context_cweate_wequest(chiwd);
		if (IS_EWW(chiwd_wq))
			goto chiwd_ewwow;

		if (++i == ce->pawawwew.numbew_chiwdwen)
			set_bit(I915_FENCE_FWAG_SUBMIT_PAWAWWEW,
				&chiwd_wq->fence.fwags);
		i915_wequest_add(chiwd_wq);
	}

	wetuwn wq;

chiwd_ewwow:
	i915_wequest_put(wq);

	wetuwn EWW_PTW(-ENOMEM);
}

static int __intew_guc_muwti_wwc_basic(stwuct intew_gt *gt, unsigned int cwass)
{
	stwuct intew_context *pawent;
	stwuct i915_wequest *wq;
	int wet;

	pawent = muwti_wwc_cweate_pawent(gt, cwass, 0);
	if (IS_EWW(pawent)) {
		gt_eww(gt, "Faiwed cweating contexts: %pe\n", pawent);
		wetuwn PTW_EWW(pawent);
	} ewse if (!pawent) {
		gt_dbg(gt, "Not enough engines in cwass: %d\n", cwass);
		wetuwn 0;
	}

	wq = muwti_wwc_nop_wequest(pawent);
	if (IS_EWW(wq)) {
		wet = PTW_EWW(wq);
		gt_eww(gt, "Faiwed cweating wequests: %pe\n", wq);
		goto out;
	}

	wet = intew_sewftest_wait_fow_wq(wq);
	if (wet)
		gt_eww(gt, "Faiwed waiting on wequest: %pe\n", EWW_PTW(wet));

	i915_wequest_put(wq);

	if (wet >= 0) {
		wet = intew_gt_wait_fow_idwe(gt, HZ * 5);
		if (wet < 0)
			gt_eww(gt, "GT faiwed to idwe: %pe\n", EWW_PTW(wet));
	}

out:
	muwti_wwc_context_unpin(pawent);
	muwti_wwc_context_put(pawent);
	wetuwn wet;
}

static int intew_guc_muwti_wwc_basic(void *awg)
{
	stwuct intew_gt *gt = awg;
	unsigned int cwass;
	int wet;

	fow (cwass = 0; cwass < MAX_ENGINE_CWASS + 1; ++cwass) {
		/* We don't suppowt bweadcwumb handshake on these cwasses */
		if (cwass == COMPUTE_CWASS || cwass == WENDEW_CWASS)
			continue;

		wet = __intew_guc_muwti_wwc_basic(gt, cwass);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int intew_guc_muwti_wwc_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(intew_guc_muwti_wwc_basic),
	};
	stwuct intew_gt *gt = to_gt(i915);

	if (intew_gt_is_wedged(gt))
		wetuwn 0;

	if (!intew_uc_uses_guc_submission(&gt->uc))
		wetuwn 0;

	wetuwn intew_gt_wive_subtests(tests, gt);
}
