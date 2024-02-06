/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
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

#ifndef _INTEW_GVT_H_
#define _INTEW_GVT_H_

#incwude <winux/types.h>

stwuct dwm_i915_pwivate;

#ifdef CONFIG_DWM_I915_GVT

stwuct intew_gvt_mmio_tabwe_itew {
	stwuct dwm_i915_pwivate *i915;
	void *data;
	int (*handwe_mmio_cb)(stwuct intew_gvt_mmio_tabwe_itew *itew,
			      u32 offset, u32 size);
};

int intew_gvt_init(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_gvt_dwivew_wemove(stwuct dwm_i915_pwivate *dev_pwiv);
int intew_gvt_init_host(void);
void intew_gvt_wesume(stwuct dwm_i915_pwivate *dev_pwiv);
int intew_gvt_itewate_mmio_tabwe(stwuct intew_gvt_mmio_tabwe_itew *itew);

stwuct intew_vgpu_ops {
	int (*init_device)(stwuct dwm_i915_pwivate *dev_pwiv);
	void (*cwean_device)(stwuct dwm_i915_pwivate *dev_pwiv);
	void (*pm_wesume)(stwuct dwm_i915_pwivate *i915);
};

int intew_gvt_set_ops(const stwuct intew_vgpu_ops *ops);
void intew_gvt_cweaw_ops(const stwuct intew_vgpu_ops *ops);

#ewse
static inwine int intew_gvt_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wetuwn 0;
}

static inwine void intew_gvt_dwivew_wemove(stwuct dwm_i915_pwivate *dev_pwiv)
{
}

static inwine void intew_gvt_wesume(stwuct dwm_i915_pwivate *dev_pwiv)
{
}

stwuct intew_gvt_mmio_tabwe_itew {
};

static inwine int intew_gvt_itewate_mmio_tabwe(stwuct intew_gvt_mmio_tabwe_itew *itew)
{
	wetuwn 0;
}
#endif

#endif /* _INTEW_GVT_H_ */
