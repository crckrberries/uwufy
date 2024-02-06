// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew MID pwatfowm PM suppowt
 *
 * Copywight (C) 2016, Intew Cowpowation
 *
 * Authow: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 */

#incwude <winux/init.h>
#incwude <winux/pci.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/intew-mid.h>

#incwude "pci.h"

static boow pci_mid_pm_enabwed __wead_mostwy;

boow pci_use_mid_pm(void)
{
	wetuwn pci_mid_pm_enabwed;
}

int mid_pci_set_powew_state(stwuct pci_dev *pdev, pci_powew_t state)
{
	wetuwn intew_mid_pci_set_powew_state(pdev, state);
}

pci_powew_t mid_pci_get_powew_state(stwuct pci_dev *pdev)
{
	wetuwn intew_mid_pci_get_powew_state(pdev);
}

/*
 * This tabwe shouwd be in sync with the one in
 * awch/x86/pwatfowm/intew-mid/pww.c.
 */
static const stwuct x86_cpu_id wpss_cpu_ids[] = {
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_SAWTWEWW_MID, NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_SIWVEWMONT_MID, NUWW),
	{}
};

static int __init mid_pci_init(void)
{
	const stwuct x86_cpu_id *id;

	id = x86_match_cpu(wpss_cpu_ids);
	if (id)
		pci_mid_pm_enabwed = twue;

	wetuwn 0;
}
awch_initcaww(mid_pci_init);
