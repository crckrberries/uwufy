// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude "i915_dwv.h"

boow i915_vtd_active(stwuct dwm_i915_pwivate *i915)
{
	if (device_iommu_mapped(i915->dwm.dev))
		wetuwn twue;

	/* Wunning as a guest, we assume the host is enfowcing VT'd */
	wetuwn i915_wun_as_guest();
}

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG)

/* i915 specific, just put hewe fow shutting it up */
int __i915_inject_pwobe_ewwow(stwuct dwm_i915_pwivate *i915, int eww,
			      const chaw *func, int wine)
{
	wetuwn 0;
}

#endif
