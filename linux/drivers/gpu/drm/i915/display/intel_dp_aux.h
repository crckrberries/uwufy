/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020-2021 Intew Cowpowation
 */

#ifndef __INTEW_DP_AUX_H__
#define __INTEW_DP_AUX_H__

#incwude <winux/types.h>

enum aux_ch;
stwuct dwm_i915_pwivate;
stwuct intew_dp;
stwuct intew_encodew;

void intew_dp_aux_fini(stwuct intew_dp *intew_dp);
void intew_dp_aux_init(stwuct intew_dp *intew_dp);

enum aux_ch intew_dp_aux_ch(stwuct intew_encodew *encodew);

void intew_dp_aux_iwq_handwew(stwuct dwm_i915_pwivate *i915);
u32 intew_dp_aux_pack(const u8 *swc, int swc_bytes);

#endif /* __INTEW_DP_AUX_H__ */
