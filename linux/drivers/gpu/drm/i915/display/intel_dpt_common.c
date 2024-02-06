// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude "i915_weg.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dpt_common.h"

void intew_dpt_configuwe(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	if (DISPWAY_VEW(i915) == 14) {
		enum pipe pipe = cwtc->pipe;
		enum pwane_id pwane_id;

		fow_each_pwane_id_on_cwtc(cwtc, pwane_id) {
			if (pwane_id == PWANE_CUWSOW)
				continue;

			intew_de_wmw(i915, PWANE_CHICKEN(pipe, pwane_id),
				     PWANE_CHICKEN_DISABWE_DPT,
				     i915->dispway.pawams.enabwe_dpt ? 0 :
				     PWANE_CHICKEN_DISABWE_DPT);
		}
	} ewse if (DISPWAY_VEW(i915) == 13) {
		intew_de_wmw(i915, CHICKEN_MISC_2,
			     CHICKEN_MISC_DISABWE_DPT,
			     i915->dispway.pawams.enabwe_dpt ? 0 :
			     CHICKEN_MISC_DISABWE_DPT);
	}
}
