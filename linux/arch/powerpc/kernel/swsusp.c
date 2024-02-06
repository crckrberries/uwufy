// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Common powewpc suspend code fow 32 and 64 bits
 *
 * Copywight 2007	Johannes Bewg <johannes@sipsowutions.net>
 */

#incwude <winux/sched.h>
#incwude <winux/suspend.h>
#incwude <asm/cuwwent.h>
#incwude <asm/mmu_context.h>
#incwude <asm/switch_to.h>

void save_pwocessow_state(void)
{
	/*
	 * fwush out aww the speciaw wegistews so we don't need
	 * to save them in the snapshot
	 */
	fwush_aww_to_thwead(cuwwent);

#ifdef CONFIG_PPC64
	hawd_iwq_disabwe();
#endif

}

void westowe_pwocessow_state(void)
{
#ifdef CONFIG_PPC32
	switch_mmu_context(cuwwent->active_mm, cuwwent->active_mm, NUWW);
#endif
}
