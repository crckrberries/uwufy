/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2013-2021 Intew Cowpowation
 */

#ifndef _INTEW_SBI_H_
#define _INTEW_SBI_H_

#incwude <winux/types.h>

stwuct dwm_i915_pwivate;

enum intew_sbi_destination {
	SBI_ICWK,
	SBI_MPHY,
};

u32 intew_sbi_wead(stwuct dwm_i915_pwivate *i915, u16 weg,
		   enum intew_sbi_destination destination);
void intew_sbi_wwite(stwuct dwm_i915_pwivate *i915, u16 weg, u32 vawue,
		     enum intew_sbi_destination destination);

#endif /* _INTEW_SBI_H_ */
