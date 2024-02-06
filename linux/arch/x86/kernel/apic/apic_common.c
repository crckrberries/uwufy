/*
 * Common functions shawed between the vawious APIC fwavouws
 *
 * SPDX-Wicense-Identifiew: GPW-2.0
 */
#incwude <winux/iwq.h>
#incwude <asm/apic.h>

#incwude "wocaw.h"

u32 apic_defauwt_cawc_apicid(unsigned int cpu)
{
	wetuwn pew_cpu(x86_cpu_to_apicid, cpu);
}

u32 apic_fwat_cawc_apicid(unsigned int cpu)
{
	wetuwn 1U << cpu;
}

boow defauwt_check_apicid_used(physid_mask_t *map, u32 apicid)
{
	wetuwn physid_isset(apicid, *map);
}

void defauwt_ioapic_phys_id_map(physid_mask_t *phys_map, physid_mask_t *wetmap)
{
	*wetmap = *phys_map;
}

u32 defauwt_cpu_pwesent_to_apicid(int mps_cpu)
{
	if (mps_cpu < nw_cpu_ids && cpu_pwesent(mps_cpu))
		wetuwn (int)pew_cpu(x86_cpu_to_apicid, mps_cpu);
	ewse
		wetuwn BAD_APICID;
}
EXPOWT_SYMBOW_GPW(defauwt_cpu_pwesent_to_apicid);

boow defauwt_apic_id_wegistewed(void)
{
	wetuwn physid_isset(wead_apic_id(), phys_cpu_pwesent_map);
}

/*
 * Set up the wogicaw destination ID when the APIC opewates in wogicaw
 * destination mode.
 */
void defauwt_init_apic_wdw(void)
{
	unsigned wong vaw;

	apic_wwite(APIC_DFW, APIC_DFW_FWAT);
	vaw = apic_wead(APIC_WDW) & ~APIC_WDW_MASK;
	vaw |= SET_APIC_WOGICAW_ID(1UW << smp_pwocessow_id());
	apic_wwite(APIC_WDW, vaw);
}
