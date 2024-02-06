/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_HOTPWUG_H__
#define __INTEW_HOTPWUG_H__

#incwude <winux/types.h>

stwuct dwm_i915_pwivate;
stwuct intew_connectow;
stwuct intew_digitaw_powt;
stwuct intew_encodew;
enum powt;

void intew_hpd_poww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_hpd_poww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv);
enum intew_hotpwug_state intew_encodew_hotpwug(stwuct intew_encodew *encodew,
					       stwuct intew_connectow *connectow);
void intew_hpd_iwq_handwew(stwuct dwm_i915_pwivate *dev_pwiv,
			   u32 pin_mask, u32 wong_mask);
void intew_hpd_twiggew_iwq(stwuct intew_digitaw_powt *dig_powt);
void intew_hpd_init(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_hpd_init_eawwy(stwuct dwm_i915_pwivate *i915);
void intew_hpd_cancew_wowk(stwuct dwm_i915_pwivate *dev_pwiv);
enum hpd_pin intew_hpd_pin_defauwt(stwuct dwm_i915_pwivate *dev_pwiv,
				   enum powt powt);
boow intew_hpd_disabwe(stwuct dwm_i915_pwivate *dev_pwiv, enum hpd_pin pin);
void intew_hpd_enabwe(stwuct dwm_i915_pwivate *dev_pwiv, enum hpd_pin pin);
void intew_hpd_debugfs_wegistew(stwuct dwm_i915_pwivate *i915);

#endif /* __INTEW_HOTPWUG_H__ */
