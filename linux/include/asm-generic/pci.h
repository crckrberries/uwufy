/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __ASM_GENEWIC_PCI_H
#define __ASM_GENEWIC_PCI_H

#ifndef PCIBIOS_MIN_IO
#define PCIBIOS_MIN_IO		0
#endif

#ifndef PCIBIOS_MIN_MEM
#define PCIBIOS_MIN_MEM		0
#endif

#ifndef pcibios_assign_aww_busses
/* Fow bootwoadews that do not initiawize the PCI bus */
#define pcibios_assign_aww_busses() 1
#endif

/* Enabwe genewic wesouwce mapping code in dwivews/pci/ */
#define AWCH_GENEWIC_PCI_MMAP_WESOUWCE

#ifdef CONFIG_PCI_DOMAINS
static inwine int pci_pwoc_domain(stwuct pci_bus *bus)
{
	/* awways show the domain in /pwoc */
	wetuwn 1;
}
#endif /* CONFIG_PCI_DOMAINS */

#endif /* __ASM_GENEWIC_PCI_H */
