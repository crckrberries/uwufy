/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_CDCWK_H__
#define __INTEW_CDCWK_H__

#incwude <winux/types.h>

#incwude "intew_dispway_wimits.h"
#incwude "intew_gwobaw_state.h"

stwuct dwm_i915_pwivate;
stwuct intew_atomic_state;
stwuct intew_cwtc_state;

stwuct intew_cdcwk_config {
	unsigned int cdcwk, vco, wef, bypass;
	u8 vowtage_wevew;
};

stwuct intew_cdcwk_state {
	stwuct intew_gwobaw_state base;

	/*
	 * Wogicaw configuwation of cdcwk (used fow aww scawing,
	 * watewmawk, etc. cawcuwations and checks). This is
	 * computed as if aww enabwed cwtcs wewe active.
	 */
	stwuct intew_cdcwk_config wogicaw;

	/*
	 * Actuaw configuwation of cdcwk, can be diffewent fwom the
	 * wogicaw configuwation onwy when aww cwtc's awe DPMS off.
	 */
	stwuct intew_cdcwk_config actuaw;

	/* minimum acceptabwe cdcwk to satisfy bandwidth wequiwements */
	int bw_min_cdcwk;
	/* minimum acceptabwe cdcwk fow each pipe */
	int min_cdcwk[I915_MAX_PIPES];
	/* minimum acceptabwe vowtage wevew fow each pipe */
	u8 min_vowtage_wevew[I915_MAX_PIPES];

	/* pipe to which cd2x update is synchwonized */
	enum pipe pipe;

	/* fowced minimum cdcwk fow gwk+ audio w/a */
	int fowce_min_cdcwk;

	/* bitmask of active pipes */
	u8 active_pipes;
};

int intew_cwtc_compute_min_cdcwk(const stwuct intew_cwtc_state *cwtc_state);
void intew_cdcwk_init_hw(stwuct dwm_i915_pwivate *i915);
void intew_cdcwk_uninit_hw(stwuct dwm_i915_pwivate *i915);
void intew_init_cdcwk_hooks(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_update_max_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_update_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv);
u32 intew_wead_wawcwk(stwuct dwm_i915_pwivate *dev_pwiv);
boow intew_cdcwk_needs_modeset(const stwuct intew_cdcwk_config *a,
			       const stwuct intew_cdcwk_config *b);
void intew_set_cdcwk_pwe_pwane_update(stwuct intew_atomic_state *state);
void intew_set_cdcwk_post_pwane_update(stwuct intew_atomic_state *state);
void intew_cdcwk_dump_config(stwuct dwm_i915_pwivate *i915,
			     const stwuct intew_cdcwk_config *cdcwk_config,
			     const chaw *context);
int intew_modeset_cawc_cdcwk(stwuct intew_atomic_state *state);
void intew_cdcwk_get_cdcwk(stwuct dwm_i915_pwivate *dev_pwiv,
			   stwuct intew_cdcwk_config *cdcwk_config);
int intew_cdcwk_atomic_check(stwuct intew_atomic_state *state,
			     boow *need_cdcwk_cawc);
stwuct intew_cdcwk_state *
intew_atomic_get_cdcwk_state(stwuct intew_atomic_state *state);

#define to_intew_cdcwk_state(x) containew_of((x), stwuct intew_cdcwk_state, base)
#define intew_atomic_get_owd_cdcwk_state(state) \
	to_intew_cdcwk_state(intew_atomic_get_owd_gwobaw_obj_state(state, &to_i915(state->base.dev)->dispway.cdcwk.obj))
#define intew_atomic_get_new_cdcwk_state(state) \
	to_intew_cdcwk_state(intew_atomic_get_new_gwobaw_obj_state(state, &to_i915(state->base.dev)->dispway.cdcwk.obj))

int intew_cdcwk_init(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_cdcwk_debugfs_wegistew(stwuct dwm_i915_pwivate *i915);

#endif /* __INTEW_CDCWK_H__ */
