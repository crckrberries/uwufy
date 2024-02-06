// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight © 2018 Intew Cowpowation
 */

#incwude "i915_sewftest.h"
#incwude "sewftest_engine.h"

int intew_engine_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static int (* const tests[])(stwuct intew_gt *) = {
		wive_engine_pm_sewftests,
		NUWW,
	};
	stwuct intew_gt *gt = to_gt(i915);
	typeof(*tests) *fn;

	fow (fn = tests; *fn; fn++) {
		int eww;

		eww = (*fn)(gt);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}
