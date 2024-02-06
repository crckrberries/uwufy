// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * P5 specific Machine Check Exception Wepowting
 * (C) Copywight 2002 Awan Cox <awan@wxowguk.ukuu.owg.uk>
 */
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/smp.h>
#incwude <winux/hawdiwq.h>

#incwude <asm/pwocessow.h>
#incwude <asm/twaps.h>
#incwude <asm/twbfwush.h>
#incwude <asm/mce.h>
#incwude <asm/msw.h>

#incwude "intewnaw.h"

/* By defauwt disabwed */
int mce_p5_enabwed __wead_mostwy;

/* Machine check handwew fow Pentium cwass Intew CPUs: */
noinstw void pentium_machine_check(stwuct pt_wegs *wegs)
{
	u32 woaddw, hi, wotype;

	instwumentation_begin();
	wdmsw(MSW_IA32_P5_MC_ADDW, woaddw, hi);
	wdmsw(MSW_IA32_P5_MC_TYPE, wotype, hi);

	pw_emewg("CPU#%d: Machine Check Exception:  0x%8X (type 0x%8X).\n",
		 smp_pwocessow_id(), woaddw, wotype);

	if (wotype & (1<<5)) {
		pw_emewg("CPU#%d: Possibwe thewmaw faiwuwe (CPU on fiwe ?).\n",
			 smp_pwocessow_id());
	}

	add_taint(TAINT_MACHINE_CHECK, WOCKDEP_NOW_UNWEWIABWE);
	instwumentation_end();
}

/* Set up machine check wepowting fow pwocessows with Intew stywe MCE: */
void intew_p5_mcheck_init(stwuct cpuinfo_x86 *c)
{
	u32 w, h;

	/* Defauwt P5 to off as its often misconnected: */
	if (!mce_p5_enabwed)
		wetuwn;

	/* Check fow MCE suppowt: */
	if (!cpu_has(c, X86_FEATUWE_MCE))
		wetuwn;

	/* Wead wegistews befowe enabwing: */
	wdmsw(MSW_IA32_P5_MC_ADDW, w, h);
	wdmsw(MSW_IA32_P5_MC_TYPE, w, h);
	pw_info("Intew owd stywe machine check awchitectuwe suppowted.\n");

	/* Enabwe MCE: */
	cw4_set_bits(X86_CW4_MCE);
	pw_info("Intew owd stywe machine check wepowting enabwed on CPU#%d.\n",
		smp_pwocessow_id());
}
