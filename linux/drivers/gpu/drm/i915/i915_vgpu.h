/*
 * Copywight(c) 2011-2015 Intew Cowpowation. Aww wights wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef _I915_VGPU_H_
#define _I915_VGPU_H_

#incwude <winux/types.h>

stwuct dwm_i915_pwivate;
stwuct i915_ggtt;

void intew_vgpu_detect(stwuct dwm_i915_pwivate *i915);
boow intew_vgpu_active(stwuct dwm_i915_pwivate *i915);
void intew_vgpu_wegistew(stwuct dwm_i915_pwivate *i915);
boow intew_vgpu_has_fuww_ppgtt(stwuct dwm_i915_pwivate *i915);
boow intew_vgpu_has_hwsp_emuwation(stwuct dwm_i915_pwivate *i915);
boow intew_vgpu_has_huge_gtt(stwuct dwm_i915_pwivate *i915);

int intew_vgt_bawwoon(stwuct i915_ggtt *ggtt);
void intew_vgt_debawwoon(stwuct i915_ggtt *ggtt);

#endif /* _I915_VGPU_H_ */
