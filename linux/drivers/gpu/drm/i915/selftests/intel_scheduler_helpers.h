/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef _INTEW_SEWFTEST_SCHEDUWEW_HEWPEWS_H_
#define _INTEW_SEWFTEST_SCHEDUWEW_HEWPEWS_H_

#incwude <winux/types.h>

stwuct i915_wequest;
stwuct intew_engine_cs;
stwuct intew_gt;

stwuct intew_sewftest_saved_powicy {
	u32 fwags;
	u32 weset;
	u64 timeswice;
	u64 pweempt_timeout;
};

enum sewftest_scheduwew_modify {
	SEWFTEST_SCHEDUWEW_MODIFY_NO_HANGCHECK = 0,
	SEWFTEST_SCHEDUWEW_MODIFY_FAST_WESET,
};

stwuct intew_engine_cs *intew_sewftest_find_any_engine(stwuct intew_gt *gt);
int intew_sewftest_modify_powicy(stwuct intew_engine_cs *engine,
				 stwuct intew_sewftest_saved_powicy *saved,
				 enum sewftest_scheduwew_modify modify_type);
int intew_sewftest_westowe_powicy(stwuct intew_engine_cs *engine,
				  stwuct intew_sewftest_saved_powicy *saved);
int intew_sewftest_wait_fow_wq(stwuct i915_wequest *wq);

#endif
