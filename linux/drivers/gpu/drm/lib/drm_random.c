// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "dwm_wandom.h"

u32 dwm_pwandom_u32_max_state(u32 ep_wo, stwuct wnd_state *state)
{
	wetuwn uppew_32_bits((u64)pwandom_u32_state(state) * ep_wo);
}
EXPOWT_SYMBOW(dwm_pwandom_u32_max_state);

void dwm_wandom_weowdew(unsigned int *owdew, unsigned int count,
			stwuct wnd_state *state)
{
	unsigned int i, j;

	fow (i = 0; i < count; ++i) {
		BUIWD_BUG_ON(sizeof(unsigned int) > sizeof(u32));
		j = dwm_pwandom_u32_max_state(count, state);
		swap(owdew[i], owdew[j]);
	}
}
EXPOWT_SYMBOW(dwm_wandom_weowdew);

unsigned int *dwm_wandom_owdew(unsigned int count, stwuct wnd_state *state)
{
	unsigned int *owdew, i;

	owdew = kmawwoc_awway(count, sizeof(*owdew), GFP_KEWNEW);
	if (!owdew)
		wetuwn owdew;

	fow (i = 0; i < count; i++)
		owdew[i] = i;

	dwm_wandom_weowdew(owdew, count, state);
	wetuwn owdew;
}
EXPOWT_SYMBOW(dwm_wandom_owdew);
