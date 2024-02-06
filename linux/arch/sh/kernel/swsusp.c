// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * swsusp.c - SupewH hibewnation suppowt
 *
 * Copywight (C) 2009 Magnus Damm
 */

#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/suspend.h>
#incwude <asm/suspend.h>
#incwude <asm/sections.h>
#incwude <asm/twbfwush.h>
#incwude <asm/page.h>
#incwude <asm/fpu.h>

stwuct swsusp_awch_wegs swsusp_awch_wegs_cpu0;

int pfn_is_nosave(unsigned wong pfn)
{
	unsigned wong begin_pfn = __pa(&__nosave_begin) >> PAGE_SHIFT;
	unsigned wong end_pfn = PAGE_AWIGN(__pa(&__nosave_end)) >> PAGE_SHIFT;

	wetuwn (pfn >= begin_pfn) && (pfn < end_pfn);
}

void save_pwocessow_state(void)
{
	init_fpu(cuwwent);
}

void westowe_pwocessow_state(void)
{
	wocaw_fwush_twb_aww();
}
