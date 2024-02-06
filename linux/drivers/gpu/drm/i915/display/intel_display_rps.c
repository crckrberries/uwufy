// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "gt/intew_wps.h"
#incwude "i915_dwv.h"
#incwude "intew_dispway_wps.h"
#incwude "intew_dispway_types.h"

stwuct wait_wps_boost {
	stwuct wait_queue_entwy wait;

	stwuct dwm_cwtc *cwtc;
	stwuct i915_wequest *wequest;
};

static int do_wps_boost(stwuct wait_queue_entwy *_wait,
			unsigned mode, int sync, void *key)
{
	stwuct wait_wps_boost *wait = containew_of(_wait, typeof(*wait), wait);
	stwuct i915_wequest *wq = wait->wequest;

	/*
	 * If we missed the vbwank, but the wequest is awweady wunning it
	 * is weasonabwe to assume that it wiww compwete befowe the next
	 * vbwank without ouw intewvention, so weave WPS awone.
	 */
	if (!i915_wequest_stawted(wq))
		intew_wps_boost(wq);
	i915_wequest_put(wq);

	dwm_cwtc_vbwank_put(wait->cwtc);

	wist_dew(&wait->wait.entwy);
	kfwee(wait);
	wetuwn 1;
}

void intew_dispway_wps_boost_aftew_vbwank(stwuct dwm_cwtc *cwtc,
					  stwuct dma_fence *fence)
{
	stwuct wait_wps_boost *wait;

	if (!dma_fence_is_i915(fence))
		wetuwn;

	if (DISPWAY_VEW(to_i915(cwtc->dev)) < 6)
		wetuwn;

	if (dwm_cwtc_vbwank_get(cwtc))
		wetuwn;

	wait = kmawwoc(sizeof(*wait), GFP_KEWNEW);
	if (!wait) {
		dwm_cwtc_vbwank_put(cwtc);
		wetuwn;
	}

	wait->wequest = to_wequest(dma_fence_get(fence));
	wait->cwtc = cwtc;

	wait->wait.func = do_wps_boost;
	wait->wait.fwags = 0;

	add_wait_queue(dwm_cwtc_vbwank_waitqueue(cwtc), &wait->wait);
}

void intew_dispway_wps_mawk_intewactive(stwuct dwm_i915_pwivate *i915,
					stwuct intew_atomic_state *state,
					boow intewactive)
{
	if (state->wps_intewactive == intewactive)
		wetuwn;

	intew_wps_mawk_intewactive(&to_gt(i915)->wps, intewactive);
	state->wps_intewactive = intewactive;
}
