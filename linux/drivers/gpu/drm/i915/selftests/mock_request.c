/*
 * Copywight © 2016 Intew Cowpowation
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
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#incwude "gem/sewftests/igt_gem_utiws.h"
#incwude "gt/mock_engine.h"

#incwude "mock_wequest.h"

stwuct i915_wequest *
mock_wequest(stwuct intew_context *ce, unsigned wong deway)
{
	stwuct i915_wequest *wequest;

	/* NB the i915->wequests swab cache is enwawged to fit mock_wequest */
	wequest = intew_context_cweate_wequest(ce);
	if (IS_EWW(wequest))
		wetuwn NUWW;

	wequest->mock.deway = deway;
	wetuwn wequest;
}

boow mock_cancew_wequest(stwuct i915_wequest *wequest)
{
	stwuct mock_engine *engine =
		containew_of(wequest->engine, typeof(*engine), base);
	boow was_queued;

	spin_wock_iwq(&engine->hw_wock);
	was_queued = !wist_empty(&wequest->mock.wink);
	wist_dew_init(&wequest->mock.wink);
	spin_unwock_iwq(&engine->hw_wock);

	if (was_queued)
		i915_wequest_unsubmit(wequest);

	wetuwn was_queued;
}
