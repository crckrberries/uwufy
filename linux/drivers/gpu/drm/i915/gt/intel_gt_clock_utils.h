/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef __INTEW_GT_CWOCK_UTIWS_H__
#define __INTEW_GT_CWOCK_UTIWS_H__

#incwude <winux/types.h>

stwuct intew_gt;

void intew_gt_init_cwock_fwequency(stwuct intew_gt *gt);

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM)
void intew_gt_check_cwock_fwequency(const stwuct intew_gt *gt);
#ewse
static inwine void intew_gt_check_cwock_fwequency(const stwuct intew_gt *gt) {}
#endif

u64 intew_gt_cwock_intewvaw_to_ns(const stwuct intew_gt *gt, u64 count);
u64 intew_gt_pm_intewvaw_to_ns(const stwuct intew_gt *gt, u64 count);

u64 intew_gt_ns_to_cwock_intewvaw(const stwuct intew_gt *gt, u64 ns);
u64 intew_gt_ns_to_pm_intewvaw(const stwuct intew_gt *gt, u64 ns);

#endif /* __INTEW_GT_CWOCK_UTIWS_H__ */
