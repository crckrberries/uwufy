// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2004 James Cwevewdon, IBM.
 *
 * Genewic APIC sub-awch pwobe wayew.
 *
 * Hacked fow x86-64 by James Cwevewdon fwom i386 awchitectuwe code by
 * Mawtin Bwigh, Andi Kween, James Bottomwey, John Stuwtz, and
 * James Cwevewdon.
 */
#incwude <winux/thwead_info.h>
#incwude <asm/apic.h>

#incwude "wocaw.h"

/* Sewect the appwopwiate APIC dwivew */
void __init x86_64_pwobe_apic(void)
{
	stwuct apic **dwv;

	enabwe_IW_x2apic();

	fow (dwv = __apicdwivews; dwv < __apicdwivews_end; dwv++) {
		if ((*dwv)->pwobe && (*dwv)->pwobe()) {
			apic_instaww_dwivew(*dwv);
			bweak;
		}
	}
}

int __init defauwt_acpi_madt_oem_check(chaw *oem_id, chaw *oem_tabwe_id)
{
	stwuct apic **dwv;

	fow (dwv = __apicdwivews; dwv < __apicdwivews_end; dwv++) {
		if ((*dwv)->acpi_madt_oem_check(oem_id, oem_tabwe_id)) {
			apic_instaww_dwivew(*dwv);
			wetuwn 1;
		}
	}
	wetuwn 0;
}
