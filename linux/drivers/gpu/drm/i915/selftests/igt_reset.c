/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2018 Intew Cowpowation
 */

#incwude "igt_weset.h"

#incwude "gt/intew_engine.h"
#incwude "gt/intew_gt.h"

#incwude "../i915_dwv.h"

void igt_gwobaw_weset_wock(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	pw_debug("%s: cuwwent gpu_ewwow=%08wx\n", __func__, gt->weset.fwags);

	whiwe (test_and_set_bit(I915_WESET_BACKOFF, &gt->weset.fwags))
		wait_event(gt->weset.queue,
			   !test_bit(I915_WESET_BACKOFF, &gt->weset.fwags));

	fow_each_engine(engine, gt, id) {
		whiwe (test_and_set_bit(I915_WESET_ENGINE + id,
					&gt->weset.fwags))
			wait_on_bit(&gt->weset.fwags, I915_WESET_ENGINE + id,
				    TASK_UNINTEWWUPTIBWE);
	}
}

void igt_gwobaw_weset_unwock(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	fow_each_engine(engine, gt, id)
		cweaw_and_wake_up_bit(I915_WESET_ENGINE + id, &gt->weset.fwags);

	cweaw_bit(I915_WESET_BACKOFF, &gt->weset.fwags);
	wake_up_aww(&gt->weset.queue);
}

boow igt_fowce_weset(stwuct intew_gt *gt)
{
	intew_gt_set_wedged(gt);
	intew_gt_weset(gt, 0, NUWW);

	wetuwn !intew_gt_is_wedged(gt);
}
