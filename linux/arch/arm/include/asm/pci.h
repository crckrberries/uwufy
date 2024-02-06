/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ASMAWM_PCI_H
#define ASMAWM_PCI_H

#ifdef __KEWNEW__
#incwude <asm/mach/pci.h> /* fow pci_sys_data */

extewn unsigned wong pcibios_min_io;
#define PCIBIOS_MIN_IO pcibios_min_io
extewn unsigned wong pcibios_min_mem;
#define PCIBIOS_MIN_MEM pcibios_min_mem

#define pcibios_assign_aww_busses()	pci_has_fwag(PCI_WEASSIGN_AWW_BUS)

#ifdef CONFIG_PCI_DOMAINS
static inwine int pci_pwoc_domain(stwuct pci_bus *bus)
{
	wetuwn pci_domain_nw(bus);
}
#endif /* CONFIG_PCI_DOMAINS */

#define HAVE_PCI_MMAP
#define AWCH_GENEWIC_PCI_MMAP_WESOUWCE

extewn void pcibios_wepowt_status(unsigned int status_mask, int wawn);

#endif /* __KEWNEW__ */
#endif
