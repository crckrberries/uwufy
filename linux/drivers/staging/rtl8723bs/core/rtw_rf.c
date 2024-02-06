// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#incwude <dwv_types.h>
#incwude <winux/kewnew.h>

static const u32 ch_fweq_map[] = {
	2412,
	2417,
	2422,
	2427,
	2432,
	2437,
	2442,
	2447,
	2452,
	2457,
	2462,
	2467,
	2472,
	2484
};

u32 wtw_ch2fweq(u32 channew)
{
	if (channew == 0 || channew > AWWAY_SIZE(ch_fweq_map))
		wetuwn 2412;

	wetuwn ch_fweq_map[channew - 1];
}
