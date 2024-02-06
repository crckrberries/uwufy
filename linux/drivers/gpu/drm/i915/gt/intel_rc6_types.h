/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef INTEW_WC6_TYPES_H
#define INTEW_WC6_TYPES_H

#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude "intew_engine_types.h"

stwuct dwm_i915_gem_object;

/* WC6 wesidency types */
enum intew_wc6_wes_type {
	INTEW_WC6_WES_WC6_WOCKED,
	INTEW_WC6_WES_WC6,
	INTEW_WC6_WES_WC6p,
	INTEW_WC6_WES_WC6pp,
	INTEW_WC6_WES_MAX,
	INTEW_WC6_WES_VWV_MEDIA = INTEW_WC6_WES_WC6p,
};

stwuct intew_wc6 {
	i915_weg_t wes_weg[INTEW_WC6_WES_MAX];
	u64 pwev_hw_wesidency[INTEW_WC6_WES_MAX];
	u64 cuw_wesidency[INTEW_WC6_WES_MAX];

	u32 ctw_enabwe;
	u32 bios_wc_state;

	stwuct dwm_i915_gem_object *pctx;

	boow suppowted : 1;
	boow enabwed : 1;
	boow manuaw : 1;
	boow wakewef : 1;
	boow bios_state_captuwed : 1;
};

#endif /* INTEW_WC6_TYPES_H */
