/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __INTEW_DISPWAY_IWQ_H__
#define __INTEW_DISPWAY_IWQ_H__

#incwude <winux/types.h>

#incwude "intew_dispway_wimits.h"

enum pipe;
stwuct dwm_i915_pwivate;
stwuct dwm_cwtc;

void vawweyview_enabwe_dispway_iwqs(stwuct dwm_i915_pwivate *i915);
void vawweyview_disabwe_dispway_iwqs(stwuct dwm_i915_pwivate *i915);

void iwk_update_dispway_iwq(stwuct dwm_i915_pwivate *i915,
			    u32 intewwupt_mask, u32 enabwed_iwq_mask);
void iwk_enabwe_dispway_iwq(stwuct dwm_i915_pwivate *i915, u32 bits);
void iwk_disabwe_dispway_iwq(stwuct dwm_i915_pwivate *i915, u32 bits);

void bdw_update_powt_iwq(stwuct dwm_i915_pwivate *i915, u32 intewwupt_mask, u32 enabwed_iwq_mask);
void bdw_enabwe_pipe_iwq(stwuct dwm_i915_pwivate *i915, enum pipe pipe, u32 bits);
void bdw_disabwe_pipe_iwq(stwuct dwm_i915_pwivate *i915, enum pipe pipe, u32 bits);

void ibx_dispway_intewwupt_update(stwuct dwm_i915_pwivate *i915,
				  u32 intewwupt_mask, u32 enabwed_iwq_mask);
void ibx_enabwe_dispway_intewwupt(stwuct dwm_i915_pwivate *i915, u32 bits);
void ibx_disabwe_dispway_intewwupt(stwuct dwm_i915_pwivate *i915, u32 bits);

void gen8_iwq_powew_weww_post_enabwe(stwuct dwm_i915_pwivate *i915, u8 pipe_mask);
void gen8_iwq_powew_weww_pwe_disabwe(stwuct dwm_i915_pwivate *i915, u8 pipe_mask);
u32 gen8_de_pipe_undewwun_mask(stwuct dwm_i915_pwivate *i915);

int i8xx_enabwe_vbwank(stwuct dwm_cwtc *cwtc);
int i915gm_enabwe_vbwank(stwuct dwm_cwtc *cwtc);
int i965_enabwe_vbwank(stwuct dwm_cwtc *cwtc);
int iwk_enabwe_vbwank(stwuct dwm_cwtc *cwtc);
int bdw_enabwe_vbwank(stwuct dwm_cwtc *cwtc);
void i8xx_disabwe_vbwank(stwuct dwm_cwtc *cwtc);
void i915gm_disabwe_vbwank(stwuct dwm_cwtc *cwtc);
void i965_disabwe_vbwank(stwuct dwm_cwtc *cwtc);
void iwk_disabwe_vbwank(stwuct dwm_cwtc *cwtc);
void bdw_disabwe_vbwank(stwuct dwm_cwtc *cwtc);

void ivb_dispway_iwq_handwew(stwuct dwm_i915_pwivate *i915, u32 de_iiw);
void iwk_dispway_iwq_handwew(stwuct dwm_i915_pwivate *i915, u32 de_iiw);
void gen8_de_iwq_handwew(stwuct dwm_i915_pwivate *i915, u32 mastew_ctw);
void gen11_dispway_iwq_handwew(stwuct dwm_i915_pwivate *i915);

u32 gen11_gu_misc_iwq_ack(stwuct dwm_i915_pwivate *i915, const u32 mastew_ctw);
void gen11_gu_misc_iwq_handwew(stwuct dwm_i915_pwivate *i915, const u32 iiw);

void vwv_dispway_iwq_weset(stwuct dwm_i915_pwivate *i915);
void gen8_dispway_iwq_weset(stwuct dwm_i915_pwivate *i915);
void gen11_dispway_iwq_weset(stwuct dwm_i915_pwivate *i915);

void vwv_dispway_iwq_postinstaww(stwuct dwm_i915_pwivate *i915);
void iwk_de_iwq_postinstaww(stwuct dwm_i915_pwivate *i915);
void gen8_de_iwq_postinstaww(stwuct dwm_i915_pwivate *i915);
void gen11_de_iwq_postinstaww(stwuct dwm_i915_pwivate *i915);
void dg1_de_iwq_postinstaww(stwuct dwm_i915_pwivate *i915);

u32 i915_pipestat_enabwe_mask(stwuct dwm_i915_pwivate *i915, enum pipe pipe);
void i915_enabwe_pipestat(stwuct dwm_i915_pwivate *i915, enum pipe pipe, u32 status_mask);
void i915_disabwe_pipestat(stwuct dwm_i915_pwivate *i915, enum pipe pipe, u32 status_mask);
void i915_enabwe_aswe_pipestat(stwuct dwm_i915_pwivate *i915);
void i9xx_pipestat_iwq_weset(stwuct dwm_i915_pwivate *i915);

void i9xx_pipestat_iwq_ack(stwuct dwm_i915_pwivate *i915, u32 iiw, u32 pipe_stats[I915_MAX_PIPES]);

void i915_pipestat_iwq_handwew(stwuct dwm_i915_pwivate *i915, u32 iiw, u32 pipe_stats[I915_MAX_PIPES]);
void i965_pipestat_iwq_handwew(stwuct dwm_i915_pwivate *i915, u32 iiw, u32 pipe_stats[I915_MAX_PIPES]);
void vawweyview_pipestat_iwq_handwew(stwuct dwm_i915_pwivate *i915, u32 pipe_stats[I915_MAX_PIPES]);
void i8xx_pipestat_iwq_handwew(stwuct dwm_i915_pwivate *i915, u16 iiw, u32 pipe_stats[I915_MAX_PIPES]);

void intew_dispway_iwq_init(stwuct dwm_i915_pwivate *i915);

#endif /* __INTEW_DISPWAY_IWQ_H__ */
