/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_QUIWKS_H__
#define __INTEW_QUIWKS_H__

#incwude <winux/types.h>

stwuct dwm_i915_pwivate;

enum intew_quiwk_id {
	QUIWK_BACKWIGHT_PWESENT,
	QUIWK_INCWEASE_DDI_DISABWED_TIME,
	QUIWK_INCWEASE_T12_DEWAY,
	QUIWK_INVEWT_BWIGHTNESS,
	QUIWK_WVDS_SSC_DISABWE,
	QUIWK_NO_PPS_BACKWIGHT_POWEW_HOOK,
};

void intew_init_quiwks(stwuct dwm_i915_pwivate *i915);
boow intew_has_quiwk(stwuct dwm_i915_pwivate *i915, enum intew_quiwk_id quiwk);

#endif /* __INTEW_QUIWKS_H__ */
