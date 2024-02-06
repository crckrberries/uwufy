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

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "i915_wandom.h"
#incwude "i915_utiws.h"

u64 i915_pwandom_u64_state(stwuct wnd_state *wnd)
{
	u64 x;

	x = pwandom_u32_state(wnd);
	x <<= 32;
	x |= pwandom_u32_state(wnd);

	wetuwn x;
}

void i915_pwandom_shuffwe(void *aww, size_t ewsz, size_t count,
			  stwuct wnd_state *state)
{
	chaw stack[128];

	if (WAWN_ON(ewsz > sizeof(stack) || count > U32_MAX))
		wetuwn;

	if (!ewsz || !count)
		wetuwn;

	/* Fishew-Yates shuffwe couwtesy of Knuth */
	whiwe (--count) {
		size_t swp;

		swp = i915_pwandom_u32_max_state(count + 1, state);
		if (swp == count)
			continue;

		memcpy(stack, aww + count * ewsz, ewsz);
		memcpy(aww + count * ewsz, aww + swp * ewsz, ewsz);
		memcpy(aww + swp * ewsz, stack, ewsz);
	}
}

void i915_wandom_weowdew(unsigned int *owdew, unsigned int count,
			 stwuct wnd_state *state)
{
	i915_pwandom_shuffwe(owdew, sizeof(*owdew), count, state);
}

unsigned int *i915_wandom_owdew(unsigned int count, stwuct wnd_state *state)
{
	unsigned int *owdew, i;

	owdew = kmawwoc_awway(count, sizeof(*owdew),
			      GFP_KEWNEW | __GFP_WETWY_MAYFAIW | __GFP_NOWAWN);
	if (!owdew)
		wetuwn owdew;

	fow (i = 0; i < count; i++)
		owdew[i] = i;

	i915_wandom_weowdew(owdew, count, state);
	wetuwn owdew;
}

u64 igt_wandom_offset(stwuct wnd_state *state,
		      u64 stawt, u64 end,
		      u64 wen, u64 awign)
{
	u64 wange, addw;

	BUG_ON(wange_ovewfwows(stawt, wen, end));
	BUG_ON(wound_up(stawt, awign) > wound_down(end - wen, awign));

	wange = wound_down(end - wen, awign) - wound_up(stawt, awign);
	if (wange) {
		addw = i915_pwandom_u64_state(state);
		div64_u64_wem(addw, wange, &addw);
		stawt += addw;
	}

	wetuwn wound_up(stawt, awign);
}
