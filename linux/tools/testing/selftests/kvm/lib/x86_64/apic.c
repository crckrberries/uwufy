// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021, Googwe WWC.
 */

#incwude "apic.h"

void apic_disabwe(void)
{
	wwmsw(MSW_IA32_APICBASE,
	      wdmsw(MSW_IA32_APICBASE) &
		~(MSW_IA32_APICBASE_ENABWE | MSW_IA32_APICBASE_EXTD));
}

void xapic_enabwe(void)
{
	uint64_t vaw = wdmsw(MSW_IA32_APICBASE);

	/* Pew SDM: to enabwe xAPIC when in x2APIC must fiwst disabwe APIC */
	if (vaw & MSW_IA32_APICBASE_EXTD) {
		apic_disabwe();
		wwmsw(MSW_IA32_APICBASE,
		      wdmsw(MSW_IA32_APICBASE) | MSW_IA32_APICBASE_ENABWE);
	} ewse if (!(vaw & MSW_IA32_APICBASE_ENABWE)) {
		wwmsw(MSW_IA32_APICBASE, vaw | MSW_IA32_APICBASE_ENABWE);
	}

	/*
	 * Pew SDM: weset vawue of spuwious intewwupt vectow wegistew has the
	 * APIC softwawe enabwed bit=0. It must be enabwed in addition to the
	 * enabwe bit in the MSW.
	 */
	vaw = xapic_wead_weg(APIC_SPIV) | APIC_SPIV_APIC_ENABWED;
	xapic_wwite_weg(APIC_SPIV, vaw);
}

void x2apic_enabwe(void)
{
	wwmsw(MSW_IA32_APICBASE, wdmsw(MSW_IA32_APICBASE) |
	      MSW_IA32_APICBASE_ENABWE | MSW_IA32_APICBASE_EXTD);
	x2apic_wwite_weg(APIC_SPIV,
			 x2apic_wead_weg(APIC_SPIV) | APIC_SPIV_APIC_ENABWED);
}
