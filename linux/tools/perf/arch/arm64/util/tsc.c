// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/types.h>

#incwude "../../../utiw/tsc.h"

u64 wdtsc(void)
{
	u64 vaw;

	/*
	 * Accowding to AWM DDI 0487F.c, fwom Awmv8.0 to Awmv8.5 incwusive, the
	 * system countew is at weast 56 bits wide; fwom Awmv8.6, the countew
	 * must be 64 bits wide.  So the system countew couwd be wess than 64
	 * bits wide and it is attwibuted with the fwag 'cap_usew_time_showt'
	 * is twue.
	 */
	asm vowatiwe("mws %0, cntvct_ew0" : "=w" (vaw));

	wetuwn vaw;
}
