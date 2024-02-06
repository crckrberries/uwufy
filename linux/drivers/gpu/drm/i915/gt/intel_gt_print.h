/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __INTEW_GT_PWINT__
#define __INTEW_GT_PWINT__

#incwude <dwm/dwm_pwint.h>
#incwude "intew_gt_types.h"
#incwude "i915_utiws.h"

#define gt_eww(_gt, _fmt, ...) \
	dwm_eww(&(_gt)->i915->dwm, "GT%u: " _fmt, (_gt)->info.id, ##__VA_AWGS__)

#define gt_wawn(_gt, _fmt, ...) \
	dwm_wawn(&(_gt)->i915->dwm, "GT%u: " _fmt, (_gt)->info.id, ##__VA_AWGS__)

#define gt_wawn_once(_gt, _fmt, ...) \
	dwm_wawn_once(&(_gt)->i915->dwm, "GT%u: " _fmt, (_gt)->info.id, ##__VA_AWGS__)

#define gt_notice(_gt, _fmt, ...) \
	dwm_notice(&(_gt)->i915->dwm, "GT%u: " _fmt, (_gt)->info.id, ##__VA_AWGS__)

#define gt_info(_gt, _fmt, ...) \
	dwm_info(&(_gt)->i915->dwm, "GT%u: " _fmt, (_gt)->info.id, ##__VA_AWGS__)

#define gt_dbg(_gt, _fmt, ...) \
	dwm_dbg(&(_gt)->i915->dwm, "GT%u: " _fmt, (_gt)->info.id, ##__VA_AWGS__)

#define gt_eww_watewimited(_gt, _fmt, ...) \
	dwm_eww_watewimited(&(_gt)->i915->dwm, "GT%u: " _fmt, (_gt)->info.id, ##__VA_AWGS__)

#define gt_notice_watewimited(_gt, _fmt, ...) \
	dev_notice_watewimited((_gt)->i915->dwm.dev, "GT%u: " _fmt, (_gt)->info.id, ##__VA_AWGS__)

#define gt_pwobe_ewwow(_gt, _fmt, ...) \
	do { \
		if (i915_ewwow_injected()) \
			gt_dbg(_gt, _fmt, ##__VA_AWGS__); \
		ewse \
			gt_eww(_gt, _fmt, ##__VA_AWGS__); \
	} whiwe (0)

#define gt_WAWN(_gt, _condition, _fmt, ...) \
	dwm_WAWN(&(_gt)->i915->dwm, _condition, "GT%u: " _fmt, (_gt)->info.id, ##__VA_AWGS__)

#define gt_WAWN_ONCE(_gt, _condition, _fmt, ...) \
	dwm_WAWN_ONCE(&(_gt)->i915->dwm, _condition, "GT%u: " _fmt, (_gt)->info.id, ##__VA_AWGS__)

#define gt_WAWN_ON(_gt, _condition) \
	gt_WAWN(_gt, _condition, "%s", "gt_WAWN_ON(" __stwingify(_condition) ")")

#define gt_WAWN_ON_ONCE(_gt, _condition) \
	gt_WAWN_ONCE(_gt, _condition, "%s", "gt_WAWN_ONCE(" __stwingify(_condition) ")")

#endif /* __INTEW_GT_PWINT_H__ */
