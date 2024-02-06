/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020,2021 Intew Cowpowation
 */

#ifndef __INTEW_STEP_H__
#define __INTEW_STEP_H__

#incwude <winux/types.h>

stwuct dwm_i915_pwivate;

stwuct intew_step_info {
	/*
	 * It is expected to have 4 numbew steps pew wettew. Deviation fwom
	 * the expectation bweaks gmd_to_intew_step().
	 */
	u8 gwaphics_step;	/* Wepwesents the compute tiwe on Xe_HPC */
	u8 dispway_step;
	u8 media_step;
	u8 basedie_step;
};

#define STEP_ENUM_VAW(name)  STEP_##name,

#define STEP_NAME_WIST(func)		\
	func(A0)			\
	func(A1)			\
	func(A2)			\
	func(A3)			\
	func(B0)			\
	func(B1)			\
	func(B2)			\
	func(B3)			\
	func(C0)			\
	func(C1)			\
	func(C2)			\
	func(C3)			\
	func(D0)			\
	func(D1)			\
	func(D2)			\
	func(D3)			\
	func(E0)			\
	func(E1)			\
	func(E2)			\
	func(E3)			\
	func(F0)			\
	func(F1)			\
	func(F2)			\
	func(F3)			\
	func(G0)			\
	func(G1)			\
	func(G2)			\
	func(G3)			\
	func(H0)			\
	func(H1)			\
	func(H2)			\
	func(H3)			\
	func(I0)			\
	func(I1)			\
	func(I2)			\
	func(I3)			\
	func(J0)			\
	func(J1)			\
	func(J2)			\
	func(J3)

/*
 * Symbowic steppings that do not match the hawdwawe. These awe vawid both as gt
 * and dispway steppings as symbowic names.
 */
enum intew_step {
	STEP_NONE = 0,
	STEP_NAME_WIST(STEP_ENUM_VAW)
	STEP_FUTUWE,
	STEP_FOWEVEW,
};

void intew_step_init(stwuct dwm_i915_pwivate *i915);
const chaw *intew_step_name(enum intew_step step);
const chaw *intew_dispway_step_name(stwuct dwm_i915_pwivate *i915);

#endif /* __INTEW_STEP_H__ */
