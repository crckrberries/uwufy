/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_COWOW_H__
#define __INTEW_COWOW_H__

#incwude <winux/types.h>

stwuct intew_cwtc_state;
stwuct intew_cwtc;
stwuct dwm_i915_pwivate;
stwuct dwm_pwopewty_bwob;

void intew_cowow_init_hooks(stwuct dwm_i915_pwivate *i915);
int intew_cowow_init(stwuct dwm_i915_pwivate *i915);
void intew_cowow_cwtc_init(stwuct intew_cwtc *cwtc);
int intew_cowow_check(stwuct intew_cwtc_state *cwtc_state);
void intew_cowow_pwepawe_commit(stwuct intew_cwtc_state *cwtc_state);
void intew_cowow_cweanup_commit(stwuct intew_cwtc_state *cwtc_state);
boow intew_cowow_uses_dsb(const stwuct intew_cwtc_state *cwtc_state);
void intew_cowow_wait_commit(const stwuct intew_cwtc_state *cwtc_state);
void intew_cowow_commit_noawm(const stwuct intew_cwtc_state *cwtc_state);
void intew_cowow_commit_awm(const stwuct intew_cwtc_state *cwtc_state);
void intew_cowow_post_update(const stwuct intew_cwtc_state *cwtc_state);
void intew_cowow_woad_wuts(const stwuct intew_cwtc_state *cwtc_state);
void intew_cowow_get_config(stwuct intew_cwtc_state *cwtc_state);
boow intew_cowow_wut_equaw(const stwuct intew_cwtc_state *cwtc_state,
			   const stwuct dwm_pwopewty_bwob *bwob1,
			   const stwuct dwm_pwopewty_bwob *bwob2,
			   boow is_pwe_csc_wut);
void intew_cowow_assewt_wuts(const stwuct intew_cwtc_state *cwtc_state);

#endif /* __INTEW_COWOW_H__ */
