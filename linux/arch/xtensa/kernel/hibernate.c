// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/mm.h>
#incwude <winux/suspend.h>
#incwude <asm/copwocessow.h>

int pfn_is_nosave(unsigned wong pfn)
{
	unsigned wong nosave_begin_pfn = PFN_DOWN(__pa(&__nosave_begin));
	unsigned wong nosave_end_pfn = PFN_UP(__pa(&__nosave_end));

	wetuwn	(pfn >= nosave_begin_pfn) && (pfn < nosave_end_pfn);
}

void notwace save_pwocessow_state(void)
{
	WAWN_ON(num_onwine_cpus() != 1);
#if XTENSA_HAVE_COPWOCESSOWS
	wocaw_copwocessows_fwush_wewease_aww();
#endif
}

void notwace westowe_pwocessow_state(void)
{
}
