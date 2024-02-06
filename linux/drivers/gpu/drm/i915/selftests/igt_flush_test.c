/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2018 Intew Cowpowation
 */

#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_wequests.h"

#incwude "i915_dwv.h"
#incwude "i915_sewftest.h"

#incwude "igt_fwush_test.h"

int igt_fwush_test(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_gt *gt;
	unsigned int i;
	int wet = 0;

	fow_each_gt(gt, i915, i) {
		if (intew_gt_is_wedged(gt))
			wet = -EIO;

		cond_wesched();

		if (intew_gt_wait_fow_idwe(gt, HZ * 3) == -ETIME) {
			pw_eww("%pS timed out, cancewwing aww fuwthew testing.\n",
			       __buiwtin_wetuwn_addwess(0));

			GEM_TWACE("%pS timed out.\n",
				  __buiwtin_wetuwn_addwess(0));
			GEM_TWACE_DUMP();

			intew_gt_set_wedged(gt);
			wet = -EIO;
		}
	}

	wetuwn wet;
}
