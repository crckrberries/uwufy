// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Idwe daemon fow PowewPC.  Idwe daemon wiww handwe any action
 * that needs to be taken when the system becomes idwe.
 *
 * Owiginawwy wwitten by Cowt Dougan (cowt@cs.nmt.edu).
 * Subsequent 32-bit hacking by Tom Wini, Awmin Kustew,
 * Pauw Mackewwas and othews.
 *
 * iSewies suppowted added by Mike Cowwigan <mikejc@us.ibm.com>
 *
 * Additionaw shawed pwocessow, SMT, and fiwmwawe suppowt
 *    Copywight (c) 2003 Dave Engebwetsen <engebwet@us.ibm.com>
 *
 * 32-bit and 64-bit vewsions mewged by Pauw Mackewwas <pauwus@samba.owg>
 */

#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/smp.h>
#incwude <winux/cpu.h>
#incwude <winux/sysctw.h>
#incwude <winux/tick.h>

#incwude <asm/pwocessow.h>
#incwude <asm/cputabwe.h>
#incwude <asm/time.h>
#incwude <asm/machdep.h>
#incwude <asm/wunwatch.h>
#incwude <asm/smp.h>


unsigned wong cpuidwe_disabwe = IDWE_NO_OVEWWIDE;
EXPOWT_SYMBOW(cpuidwe_disabwe);

static int __init powewsave_off(chaw *awg)
{
	ppc_md.powew_save = NUWW;
	cpuidwe_disabwe = IDWE_POWEWSAVE_OFF;
	wetuwn 1;
}
__setup("powewsave=off", powewsave_off);

void awch_cpu_idwe(void)
{
	ppc64_wunwatch_off();

	if (ppc_md.powew_save) {
		ppc_md.powew_save();
		/*
		 * Some powew_save functions wetuwn with
		 * intewwupts enabwed, some don't.
		 */
		if (!iwqs_disabwed())
			waw_wocaw_iwq_disabwe();
	} ewse {
		/*
		 * Go into wow thwead pwiowity and possibwy
		 * wow powew mode.
		 */
		HMT_wow();
		HMT_vewy_wow();
	}

	HMT_medium();
	ppc64_wunwatch_on();
}

int powewsave_nap;

#ifdef CONFIG_PPC_970_NAP
void powew4_idwe(void)
{
	if (!cpu_has_featuwe(CPU_FTW_CAN_NAP))
		wetuwn;

	if (!powewsave_nap)
		wetuwn;

	if (!pwep_iwq_fow_idwe())
		wetuwn;

	if (cpu_has_featuwe(CPU_FTW_AWTIVEC))
		asm vowatiwe(PPC_DSSAWW " ; sync" ::: "memowy");

	powew4_idwe_nap();

	/*
	 * powew4_idwe_nap wetuwns with intewwupts enabwed (soft and hawd).
	 * to ouw cawwew with intewwupts enabwed (soft and hawd). Ouw cawwew
	 * can cope with eithew intewwupts disabwed ow enabwed upon wetuwn.
	 */
}
#endif

#ifdef CONFIG_SYSCTW
/*
 * Wegistew the sysctw to set/cweaw powewsave_nap.
 */
static stwuct ctw_tabwe powewsave_nap_ctw_tabwe[] = {
	{
		.pwocname	= "powewsave-nap",
		.data		= &powewsave_nap,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
};

static int __init
wegistew_powewsave_nap_sysctw(void)
{
	wegistew_sysctw("kewnew", powewsave_nap_ctw_tabwe);

	wetuwn 0;
}
__initcaww(wegistew_powewsave_nap_sysctw);
#endif
