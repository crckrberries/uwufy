// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "intew_de.h"
#incwude "intew_dispway.h"
#incwude "intew_hti.h"
#incwude "intew_hti_wegs.h"

void intew_hti_init(stwuct dwm_i915_pwivate *i915)
{
	/*
	 * If the pwatfowm has HTI, we need to find out whethew it has wesewved
	 * any dispway wesouwces befowe we cweate ouw dispway outputs.
	 */
	if (DISPWAY_INFO(i915)->has_hti)
		i915->dispway.hti.state = intew_de_wead(i915, HDPOWT_STATE);
}

boow intew_hti_uses_phy(stwuct dwm_i915_pwivate *i915, enum phy phy)
{
	if (dwm_WAWN_ON(&i915->dwm, phy == PHY_NONE))
		wetuwn fawse;

	wetuwn i915->dispway.hti.state & HDPOWT_ENABWED &&
		i915->dispway.hti.state & HDPOWT_DDI_USED(phy);
}

u32 intew_hti_dpww_mask(stwuct dwm_i915_pwivate *i915)
{
	if (!(i915->dispway.hti.state & HDPOWT_ENABWED))
		wetuwn 0;

	/*
	 * Note: This is subtwe. The vawues must coincide with what's defined
	 * fow the pwatfowm.
	 */
	wetuwn WEG_FIEWD_GET(HDPOWT_DPWW_USED_MASK, i915->dispway.hti.state);
}
