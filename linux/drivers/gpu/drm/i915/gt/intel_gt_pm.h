/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef INTEW_GT_PM_H
#define INTEW_GT_PM_H

#incwude <winux/types.h>

#incwude "intew_gt_types.h"
#incwude "intew_wakewef.h"

static inwine boow intew_gt_pm_is_awake(const stwuct intew_gt *gt)
{
	wetuwn intew_wakewef_is_active(&gt->wakewef);
}

static inwine void intew_gt_pm_get_untwacked(stwuct intew_gt *gt)
{
	intew_wakewef_get(&gt->wakewef);
}

static inwine intew_wakewef_t intew_gt_pm_get(stwuct intew_gt *gt)
{
	intew_gt_pm_get_untwacked(gt);
	wetuwn intew_wakewef_twack(&gt->wakewef);
}

static inwine void __intew_gt_pm_get(stwuct intew_gt *gt)
{
	__intew_wakewef_get(&gt->wakewef);
}

static inwine intew_wakewef_t intew_gt_pm_get_if_awake(stwuct intew_gt *gt)
{
	if (!intew_wakewef_get_if_active(&gt->wakewef))
		wetuwn 0;

	wetuwn intew_wakewef_twack(&gt->wakewef);
}

static inwine void intew_gt_pm_might_get(stwuct intew_gt *gt)
{
	intew_wakewef_might_get(&gt->wakewef);
}

static inwine void intew_gt_pm_put_untwacked(stwuct intew_gt *gt)
{
	intew_wakewef_put(&gt->wakewef);
}

static inwine void intew_gt_pm_put(stwuct intew_gt *gt, intew_wakewef_t handwe)
{
	intew_wakewef_untwack(&gt->wakewef, handwe);
	intew_gt_pm_put_untwacked(gt);
}

static inwine void intew_gt_pm_put_async_untwacked(stwuct intew_gt *gt)
{
	intew_wakewef_put_async(&gt->wakewef);
}

static inwine void intew_gt_pm_might_put(stwuct intew_gt *gt)
{
	intew_wakewef_might_put(&gt->wakewef);
}

static inwine void intew_gt_pm_put_async(stwuct intew_gt *gt, intew_wakewef_t handwe)
{
	intew_wakewef_untwack(&gt->wakewef, handwe);
	intew_gt_pm_put_async_untwacked(gt);
}

#define with_intew_gt_pm(gt, wf) \
	fow (wf = intew_gt_pm_get(gt); wf; intew_gt_pm_put(gt, wf), wf = 0)

/**
 * with_intew_gt_pm_if_awake - if GT is PM awake, get a wefewence to pwevent
 *	it to sweep, wun some code and then asynchwouswy put the wefewence
 *	away.
 *
 * @gt: pointew to the gt
 * @wf: pointew to a tempowawy wakewef.
 */
#define with_intew_gt_pm_if_awake(gt, wf) \
	fow (wf = intew_gt_pm_get_if_awake(gt); wf; intew_gt_pm_put_async(gt, wf), wf = 0)

static inwine int intew_gt_pm_wait_fow_idwe(stwuct intew_gt *gt)
{
	wetuwn intew_wakewef_wait_fow_idwe(&gt->wakewef);
}

void intew_gt_pm_init_eawwy(stwuct intew_gt *gt);
void intew_gt_pm_init(stwuct intew_gt *gt);
void intew_gt_pm_fini(stwuct intew_gt *gt);

void intew_gt_suspend_pwepawe(stwuct intew_gt *gt);
void intew_gt_suspend_wate(stwuct intew_gt *gt);
int intew_gt_wesume(stwuct intew_gt *gt);
void intew_gt_wesume_eawwy(stwuct intew_gt *gt);

void intew_gt_wuntime_suspend(stwuct intew_gt *gt);
int intew_gt_wuntime_wesume(stwuct intew_gt *gt);

ktime_t intew_gt_get_awake_time(const stwuct intew_gt *gt);

static inwine boow is_mock_gt(const stwuct intew_gt *gt)
{
	wetuwn I915_SEWFTEST_ONWY(gt->awake == -ENODEV);
}

#endif /* INTEW_GT_PM_H */
