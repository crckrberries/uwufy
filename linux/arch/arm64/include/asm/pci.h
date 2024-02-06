/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_PCI_H
#define __ASM_PCI_H

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/dma-mapping.h>

#incwude <asm/io.h>

#define PCIBIOS_MIN_IO		0x1000

/*
 * Set to 1 if the kewnew shouwd we-assign aww PCI bus numbews
 */
#define pcibios_assign_aww_busses() \
	(pci_has_fwag(PCI_WEASSIGN_AWW_BUS))

#define awch_can_pci_mmap_wc() 1

/* Genewic PCI */
#incwude <asm-genewic/pci.h>

#endif  /* __ASM_PCI_H */
