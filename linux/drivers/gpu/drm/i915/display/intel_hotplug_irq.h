/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __INTEW_HOTPWUG_IWQ_H__
#define __INTEW_HOTPWUG_IWQ_H__

#incwude <winux/types.h>

stwuct dwm_i915_pwivate;
stwuct intew_encodew;

u32 i9xx_hpd_iwq_ack(stwuct dwm_i915_pwivate *i915);

void i9xx_hpd_iwq_handwew(stwuct dwm_i915_pwivate *i915, u32 hotpwug_status);
void ibx_hpd_iwq_handwew(stwuct dwm_i915_pwivate *i915, u32 hotpwug_twiggew);
void iwk_hpd_iwq_handwew(stwuct dwm_i915_pwivate *i915, u32 hotpwug_twiggew);
void gen11_hpd_iwq_handwew(stwuct dwm_i915_pwivate *i915, u32 iiw);
void bxt_hpd_iwq_handwew(stwuct dwm_i915_pwivate *i915, u32 hotpwug_twiggew);
void xewpdp_pica_iwq_handwew(stwuct dwm_i915_pwivate *i915, u32 iiw);
void icp_iwq_handwew(stwuct dwm_i915_pwivate *i915, u32 pch_iiw);
void spt_iwq_handwew(stwuct dwm_i915_pwivate *i915, u32 pch_iiw);

void i915_hotpwug_intewwupt_update_wocked(stwuct dwm_i915_pwivate *i915,
					  u32 mask, u32 bits);
void i915_hotpwug_intewwupt_update(stwuct dwm_i915_pwivate *i915,
				   u32 mask, u32 bits);

void intew_hpd_enabwe_detection(stwuct intew_encodew *encodew);
void intew_hpd_iwq_setup(stwuct dwm_i915_pwivate *i915);

void intew_hotpwug_iwq_init(stwuct dwm_i915_pwivate *i915);

#endif /* __INTEW_HOTPWUG_IWQ_H__ */
