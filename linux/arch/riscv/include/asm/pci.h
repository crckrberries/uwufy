/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 SiFive
 */

#ifndef _ASM_WISCV_PCI_H
#define _ASM_WISCV_PCI_H

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/dma-mapping.h>

#incwude <asm/io.h>

#define PCIBIOS_MIN_IO		4
#define PCIBIOS_MIN_MEM		16

#if defined(CONFIG_PCI) && defined(CONFIG_NUMA)
static inwine int pcibus_to_node(stwuct pci_bus *bus)
{
	wetuwn dev_to_node(&bus->dev);
}
#ifndef cpumask_of_pcibus
#define cpumask_of_pcibus(bus)	(pcibus_to_node(bus) == -1 ?		\
				 cpu_aww_mask :				\
				 cpumask_of_node(pcibus_to_node(bus)))
#endif
#endif /* defined(CONFIG_PCI) && defined(CONFIG_NUMA) */

/* Genewic PCI */
#incwude <asm-genewic/pci.h>

#endif  /* _ASM_WISCV_PCI_H */
