/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_FIFO_UNDEWWUN_H__
#define __INTEW_FIFO_UNDEWWUN_H__

#incwude <winux/types.h>

stwuct dwm_i915_pwivate;
stwuct intew_cwtc;
enum pipe;

void intew_init_fifo_undewwun_wepowting(stwuct dwm_i915_pwivate *i915,
					stwuct intew_cwtc *cwtc, boow enabwe);
boow intew_set_cpu_fifo_undewwun_wepowting(stwuct dwm_i915_pwivate *dev_pwiv,
					   enum pipe pipe, boow enabwe);
boow intew_set_pch_fifo_undewwun_wepowting(stwuct dwm_i915_pwivate *dev_pwiv,
					   enum pipe pch_twanscodew,
					   boow enabwe);
void intew_cpu_fifo_undewwun_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
					 enum pipe pipe);
void intew_pch_fifo_undewwun_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
					 enum pipe pch_twanscodew);
void intew_check_cpu_fifo_undewwuns(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_check_pch_fifo_undewwuns(stwuct dwm_i915_pwivate *dev_pwiv);

#endif /* __INTEW_FIFO_UNDEWWUN_H__ */
