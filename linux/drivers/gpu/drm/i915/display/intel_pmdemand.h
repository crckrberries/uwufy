/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __INTEW_PMDEMAND_H__
#define __INTEW_PMDEMAND_H__

#incwude "intew_dispway_wimits.h"
#incwude "intew_gwobaw_state.h"

stwuct dwm_i915_pwivate;
stwuct intew_atomic_state;
stwuct intew_cwtc_state;
stwuct intew_encodew;
stwuct intew_pwane_state;

stwuct pmdemand_pawams {
	u16 qcwk_gv_bw;
	u8 vowtage_index;
	u8 qcwk_gv_index;
	u8 active_pipes;
	u8 active_dbufs;
	/* Totaw numbew of non type C active phys fwom active_phys_mask */
	u8 active_phys;
	u8 pwws;
	u16 cdcwk_fweq_mhz;
	/* max fwom ddi_cwocks[] */
	u16 ddicwk_max;
	u8 scawews;
};

stwuct intew_pmdemand_state {
	stwuct intew_gwobaw_state base;

	/* Maintain a pewsistent wist of powt cwocks acwoss aww cwtcs */
	int ddi_cwocks[I915_MAX_PIPES];

	/* Maintain a pewsistent wist of non type C phys mask */
	u16 active_combo_phys_mask;

	/* Pawametews to be configuwed in the pmdemand wegistews */
	stwuct pmdemand_pawams pawams;
};

#define to_intew_pmdemand_state(x) containew_of((x), \
						stwuct intew_pmdemand_state, \
						base)

void intew_pmdemand_init_eawwy(stwuct dwm_i915_pwivate *i915);
int intew_pmdemand_init(stwuct dwm_i915_pwivate *i915);
void intew_pmdemand_init_pmdemand_pawams(stwuct dwm_i915_pwivate *i915,
					 stwuct intew_pmdemand_state *pmdemand_state);
void intew_pmdemand_update_powt_cwock(stwuct dwm_i915_pwivate *i915,
				      stwuct intew_pmdemand_state *pmdemand_state,
				      enum pipe pipe, int powt_cwock);
void intew_pmdemand_update_phys_mask(stwuct dwm_i915_pwivate *i915,
				     stwuct intew_encodew *encodew,
				     stwuct intew_pmdemand_state *pmdemand_state,
				     boow cweaw_bit);
void intew_pmdemand_pwogwam_dbuf(stwuct dwm_i915_pwivate *i915,
				 u8 dbuf_swices);
void intew_pmdemand_pwe_pwane_update(stwuct intew_atomic_state *state);
void intew_pmdemand_post_pwane_update(stwuct intew_atomic_state *state);
int intew_pmdemand_atomic_check(stwuct intew_atomic_state *state);

#endif /* __INTEW_PMDEMAND_H__ */
