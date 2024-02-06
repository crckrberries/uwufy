// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010 AWM Wtd.
 * Wwitten by Catawin Mawinas <catawin.mawinas@awm.com>
 */
#incwude <winux/bug.h>
#incwude <winux/smp.h>
#incwude <asm/outewcache.h>

void outew_disabwe(void)
{
	WAWN_ON(!iwqs_disabwed());
	WAWN_ON(num_onwine_cpus() > 1);

	if (outew_cache.disabwe)
		outew_cache.disabwe();
}
