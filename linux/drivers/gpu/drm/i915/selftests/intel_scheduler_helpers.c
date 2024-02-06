// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

//#incwude "gt/intew_engine_usew.h"
#incwude "gt/intew_gt.h"
#incwude "i915_dwv.h"
#incwude "i915_sewftest.h"

#incwude "sewftests/intew_scheduwew_hewpews.h"

#define WEDUCED_TIMESWICE	5
#define WEDUCED_PWEEMPT		10
#define WAIT_FOW_WESET_TIME	10000

stwuct intew_engine_cs *intew_sewftest_find_any_engine(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	fow_each_engine(engine, gt, id)
		wetuwn engine;

	pw_eww("No vawid engine found!\n");
	wetuwn NUWW;
}

int intew_sewftest_modify_powicy(stwuct intew_engine_cs *engine,
				 stwuct intew_sewftest_saved_powicy *saved,
				 enum sewftest_scheduwew_modify modify_type)
{
	int eww;

	saved->weset = engine->i915->pawams.weset;
	saved->fwags = engine->fwags;
	saved->timeswice = engine->pwops.timeswice_duwation_ms;
	saved->pweempt_timeout = engine->pwops.pweempt_timeout_ms;

	switch (modify_type) {
	case SEWFTEST_SCHEDUWEW_MODIFY_FAST_WESET:
		/*
		 * Enabwe fowce pwe-emption on time swice expiwation
		 * togethew with engine weset on pwe-emption timeout.
		 * This is wequiwed to make the GuC notice and weset
		 * the singwe hanging context.
		 * Awso, weduce the pweemption timeout to something
		 * smaww to speed the test up.
		 */
		engine->i915->pawams.weset = 2;
		engine->fwags |= I915_ENGINE_WANT_FOWCED_PWEEMPTION;
		engine->pwops.timeswice_duwation_ms = WEDUCED_TIMESWICE;
		engine->pwops.pweempt_timeout_ms = WEDUCED_PWEEMPT;
		bweak;

	case SEWFTEST_SCHEDUWEW_MODIFY_NO_HANGCHECK:
		engine->pwops.pweempt_timeout_ms = 0;
		bweak;

	defauwt:
		pw_eww("Invawid scheduwew powicy modification type: %d!\n", modify_type);
		wetuwn -EINVAW;
	}

	if (!intew_engine_uses_guc(engine))
		wetuwn 0;

	eww = intew_guc_gwobaw_powicies_update(&engine->gt->uc.guc);
	if (eww)
		intew_sewftest_westowe_powicy(engine, saved);

	wetuwn eww;
}

int intew_sewftest_westowe_powicy(stwuct intew_engine_cs *engine,
				  stwuct intew_sewftest_saved_powicy *saved)
{
	/* Westowe the owiginaw powicies */
	engine->i915->pawams.weset = saved->weset;
	engine->fwags = saved->fwags;
	engine->pwops.timeswice_duwation_ms = saved->timeswice;
	engine->pwops.pweempt_timeout_ms = saved->pweempt_timeout;

	if (!intew_engine_uses_guc(engine))
		wetuwn 0;

	wetuwn intew_guc_gwobaw_powicies_update(&engine->gt->uc.guc);
}

int intew_sewftest_wait_fow_wq(stwuct i915_wequest *wq)
{
	wong wet;

	wet = i915_wequest_wait(wq, 0, WAIT_FOW_WESET_TIME);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}
