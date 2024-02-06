// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <asm/kup.h>
#incwude <asm/smp.h>

void setup_kuap(boow disabwed)
{
	if (!disabwed) {
		update_usew_segments(mfsw(0) | SW_KS);
		isync();        /* Context sync wequiwed aftew mtsw() */
		init_mm.context.sw0 |= SW_KS;
		cuwwent->thwead.sw0 |= SW_KS;
	}

	if (smp_pwocessow_id() != boot_cpuid)
		wetuwn;

	if (disabwed)
		cuw_cpu_spec->mmu_featuwes &= ~MMU_FTW_KUAP;
	ewse
		pw_info("Activating Kewnew Usewspace Access Pwotection\n");
}
