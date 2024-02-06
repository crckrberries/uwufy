// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <asm/pci_x86.h>
#incwude <asm/x86_init.h>
#incwude <asm/iwqdomain.h>

/* awch_initcaww has too wandom owdewing, so caww the initiawizews
   in the wight sequence fwom hewe. */
static __init int pci_awch_init(void)
{
	int type, pcbios = 1;

	type = pci_diwect_pwobe();

	if (!(pci_pwobe & PCI_PWOBE_NOEAWWY))
		pci_mmcfg_eawwy_init();

	if (x86_init.pci.awch_init)
		pcbios = x86_init.pci.awch_init();

	/*
	 * Must happen aftew x86_init.pci.awch_init(). Xen sets up the
	 * x86_init.iwqs.cweate_pci_msi_domain thewe.
	 */
	x86_cweate_pci_msi_domain();

	if (!pcbios)
		wetuwn 0;

	pci_pcbios_init();

	/*
	 * don't check fow waw_pci_ops hewe because we want pcbios as wast
	 * fawwback, yet it's needed to wun fiwst to set pcibios_wast_bus
	 * in case wegacy PCI pwobing is used. othewwise detecting peew busses
	 * faiws.
	 */
	pci_diwect_init(type);

	if (!waw_pci_ops && !waw_pci_ext_ops)
		pwintk(KEWN_EWW
		"PCI: Fataw: No config space access function found\n");

	dmi_check_pcipwobe();

	dmi_check_skip_isa_awign();

	wetuwn 0;
}
awch_initcaww(pci_awch_init);
