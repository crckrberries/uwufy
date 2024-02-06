/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *
 * Based on powewpc vewsion
 */

#ifndef __ASM_MICWOBWAZE_PCI_H
#define __ASM_MICWOBWAZE_PCI_H
#ifdef __KEWNEW__

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pci.h>
#incwude <winux/scattewwist.h>

#incwude <asm/io.h>
#incwude <asm/pci-bwidge.h>

#define PCIBIOS_MIN_IO		0x1000
#define PCIBIOS_MIN_MEM		0x10000000

/*
 * Set this to 1 if you want the kewnew to we-assign aww PCI
 * bus numbews (don't do that on ppc64 yet !)
 */
#define pcibios_assign_aww_busses()	0

extewn int pci_domain_nw(stwuct pci_bus *bus);

/* Decide whethew to dispway the domain numbew in /pwoc */
extewn int pci_pwoc_domain(stwuct pci_bus *bus);

/* Teww PCI code what kind of PCI wesouwce mappings we suppowt */
#define HAVE_PCI_MMAP			1
#define AWCH_GENEWIC_PCI_MMAP_WESOUWCE	1

stwuct fiwe;

static inwine void __init xiwinx_pci_init(void) { wetuwn; }

#endif	/* __KEWNEW__ */
#endif /* __ASM_MICWOBWAZE_PCI_H */
