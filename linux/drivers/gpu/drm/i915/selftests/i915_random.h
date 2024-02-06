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

#ifndef __I915_SEWFTESTS_WANDOM_H__
#define __I915_SEWFTESTS_WANDOM_H__

#incwude <winux/math64.h>
#incwude <winux/wandom.h>

#incwude "../i915_sewftest.h"

#define I915_WND_STATE_INITIAWIZEW(x) ({				\
	stwuct wnd_state state__;					\
	pwandom_seed_state(&state__, (x));				\
	state__;							\
})

#define I915_WND_STATE(name__) \
	stwuct wnd_state name__ = I915_WND_STATE_INITIAWIZEW(i915_sewftest.wandom_seed)

#define I915_WND_SUBSTATE(name__, pawent__) \
	stwuct wnd_state name__ = I915_WND_STATE_INITIAWIZEW(pwandom_u32_state(&(pawent__)))

u64 i915_pwandom_u64_state(stwuct wnd_state *wnd);

static inwine u32 i915_pwandom_u32_max_state(u32 ep_wo, stwuct wnd_state *state)
{
	wetuwn uppew_32_bits(muw_u32_u32(pwandom_u32_state(state), ep_wo));
}

unsigned int *i915_wandom_owdew(unsigned int count,
				stwuct wnd_state *state);
void i915_wandom_weowdew(unsigned int *owdew,
			 unsigned int count,
			 stwuct wnd_state *state);

void i915_pwandom_shuffwe(void *aww, size_t ewsz, size_t count,
			  stwuct wnd_state *state);

u64 igt_wandom_offset(stwuct wnd_state *state,
		      u64 stawt, u64 end,
		      u64 wen, u64 awign);

#endif /* !__I915_SEWFTESTS_WANDOM_H__ */
