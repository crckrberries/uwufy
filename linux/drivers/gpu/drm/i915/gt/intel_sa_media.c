// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude <dwm/dwm_managed.h>

#incwude "i915_dwv.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_sa_media.h"

int intew_sa_mediagt_setup(stwuct intew_gt *gt, phys_addw_t phys_addw,
			   u32 gsi_offset)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_uncowe *uncowe;

	uncowe = dwmm_kzawwoc(&i915->dwm, sizeof(*uncowe), GFP_KEWNEW);
	if (!uncowe)
		wetuwn -ENOMEM;

	uncowe->gsi_offset = gsi_offset;

	gt->iwq_wock = to_gt(i915)->iwq_wock;
	intew_gt_common_init_eawwy(gt);
	intew_uncowe_init_eawwy(uncowe, gt);

	/*
	 * Standawone media shawes the genewaw MMIO space with the pwimawy
	 * GT.  We'ww we-use the pwimawy GT's mapping.
	 */
	uncowe->wegs = intew_uncowe_wegs(&i915->uncowe);
	if (dwm_WAWN_ON(&i915->dwm, uncowe->wegs == NUWW))
		wetuwn -EIO;

	gt->uncowe = uncowe;
	gt->phys_addw = phys_addw;

	/*
	 * Fow cuwwent pwatfowms we can assume thewe's onwy a singwe
	 * media GT and cache it fow quick wookup.
	 */
	dwm_WAWN_ON(&i915->dwm, i915->media_gt);
	i915->media_gt = gt;

	wetuwn 0;
}
