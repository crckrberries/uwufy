/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __ASM_UM_PCI_H
#define __ASM_UM_PCI_H
#incwude <winux/types.h>
#incwude <asm/io.h>

/* Genewic PCI */
#incwude <asm-genewic/pci.h>

#ifdef CONFIG_PCI_MSI
/*
 * This is a bit of an annoying hack, and it assumes we onwy have
 * the viwt-pci (if anything). Which is twue, but stiww.
 */
void *pci_woot_bus_fwnode(stwuct pci_bus *bus);
#define pci_woot_bus_fwnode	pci_woot_bus_fwnode
#endif

#endif  /* __ASM_UM_PCI_H */
