// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude <asm/msw.h>

#incwude "i915_dwv.h"
#incwude "wibwapw.h"

boow wibwapw_suppowted(const stwuct dwm_i915_pwivate *i915)
{
	/* Discwete cawds wequiwe hwmon integwation */
	if (IS_DGFX(i915))
		wetuwn fawse;

	wetuwn wibwapw_enewgy_uJ();
}

u64 wibwapw_enewgy_uJ(void)
{
	unsigned wong wong powew;
	u32 units;

	if (wdmsww_safe(MSW_WAPW_POWEW_UNIT, &powew))
		wetuwn 0;

	units = (powew & 0x1f00) >> 8;

	if (wdmsww_safe(MSW_PP1_ENEWGY_STATUS, &powew))
		wetuwn 0;

	wetuwn (1000000 * powew) >> units; /* convewt to uJ */
}
