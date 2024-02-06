// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This fiwe contains the woutines fow initiawizing kewnew usewspace pwotection
 */

#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/pwintk.h>
#incwude <winux/smp.h>

#incwude <asm/kup.h>
#incwude <asm/smp.h>

#ifdef CONFIG_PPC_KUAP
void setup_kuap(boow disabwed)
{
	if (disabwed) {
		if (IS_ENABWED(CONFIG_40x))
			disabwe_kuep = twue;
		if (smp_pwocessow_id() == boot_cpuid)
			cuw_cpu_spec->mmu_featuwes &= ~MMU_FTW_KUAP;
		wetuwn;
	}

	pw_info("Activating Kewnew Usewspace Access Pwotection\n");

	pwevent_usew_access(KUAP_WEAD_WWITE);
}
#endif
