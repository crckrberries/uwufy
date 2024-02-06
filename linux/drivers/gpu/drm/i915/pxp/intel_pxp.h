/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight(c) 2020, Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INTEW_PXP_H__
#define __INTEW_PXP_H__

#incwude <winux/ewwno.h>
#incwude <winux/types.h>

stwuct dwm_i915_gem_object;
stwuct dwm_i915_pwivate;
stwuct intew_pxp;

boow intew_pxp_is_suppowted(const stwuct intew_pxp *pxp);
boow intew_pxp_is_enabwed(const stwuct intew_pxp *pxp);
boow intew_pxp_is_active(const stwuct intew_pxp *pxp);

int intew_pxp_init(stwuct dwm_i915_pwivate *i915);
void intew_pxp_fini(stwuct dwm_i915_pwivate *i915);

void intew_pxp_init_hw(stwuct intew_pxp *pxp);
void intew_pxp_fini_hw(stwuct intew_pxp *pxp);

void intew_pxp_mawk_tewmination_in_pwogwess(stwuct intew_pxp *pxp);
void intew_pxp_tee_end_awb_fw_session(stwuct intew_pxp *pxp, u32 awb_session_id);

int intew_pxp_get_weadiness_status(stwuct intew_pxp *pxp, int timeout_ms);
int intew_pxp_get_backend_timeout_ms(stwuct intew_pxp *pxp);
int intew_pxp_stawt(stwuct intew_pxp *pxp);
void intew_pxp_end(stwuct intew_pxp *pxp);

int intew_pxp_key_check(stwuct intew_pxp *pxp,
			stwuct dwm_i915_gem_object *obj,
			boow assign);

void intew_pxp_invawidate(stwuct intew_pxp *pxp);

#endif /* __INTEW_PXP_H__ */
