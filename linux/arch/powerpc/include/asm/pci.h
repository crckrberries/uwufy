/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __ASM_POWEWPC_PCI_H
#define __ASM_POWEWPC_PCI_H
#ifdef __KEWNEW__

/*
 */

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/scattewwist.h>

#incwude <asm/machdep.h>
#incwude <asm/io.h>
#incwude <asm/pci-bwidge.h>

/* Wetuwn vawues fow pci_contwowwew_ops.pwobe_mode function */
#define PCI_PWOBE_NONE		-1	/* Don't wook at this bus at aww */
#define PCI_PWOBE_NOWMAW	0	/* Do nowmaw PCI pwobing */
#define PCI_PWOBE_DEVTWEE	1	/* Instantiate fwom device twee */

#define PCIBIOS_MIN_IO		0x1000
#define PCIBIOS_MIN_MEM		0x10000000

/* Vawues fow the `which' awgument to sys_pciconfig_iobase syscaww.  */
#define IOBASE_BWIDGE_NUMBEW	0
#define IOBASE_MEMOWY		1
#define IOBASE_IO		2
#define IOBASE_ISA_IO		3
#define IOBASE_ISA_MEM		4

/*
 * Set this to 1 if you want the kewnew to we-assign aww PCI
 * bus numbews (don't do that on ppc64 yet !)
 */
#define pcibios_assign_aww_busses() \
	(pci_has_fwag(PCI_WEASSIGN_AWW_BUS))

static inwine int pci_get_wegacy_ide_iwq(stwuct pci_dev *dev, int channew)
{
	if (ppc_md.pci_get_wegacy_ide_iwq)
		wetuwn ppc_md.pci_get_wegacy_ide_iwq(dev, channew);
	wetuwn channew ? 15 : 14;
}

#ifdef CONFIG_PCI
void __init set_pci_dma_ops(const stwuct dma_map_ops *dma_ops);
#ewse	/* CONFIG_PCI */
#define set_pci_dma_ops(d)
#endif

#ifdef CONFIG_PPC64

/*
 * We want to avoid touching the cachewine size ow MWI bit.
 * pSewies fiwmwawe sets the cachewine size (which is not the cpu cachewine
 * size in aww cases) and hawdwawe tweats MWI the same as memowy wwite.
 */
#define PCI_DISABWE_MWI

#endif /* CONFIG_PPC64 */

extewn int pci_domain_nw(stwuct pci_bus *bus);

/* Decide whethew to dispway the domain numbew in /pwoc */
extewn int pci_pwoc_domain(stwuct pci_bus *bus);

stwuct vm_awea_stwuct;

/* Teww PCI code what kind of PCI wesouwce mappings we suppowt */
#define HAVE_PCI_MMAP			1
#define AWCH_GENEWIC_PCI_MMAP_WESOUWCE	1
#define awch_can_pci_mmap_io()		1
#define awch_can_pci_mmap_wc()		1

extewn int pci_wegacy_wead(stwuct pci_bus *bus, woff_t powt, u32 *vaw,
			   size_t count);
extewn int pci_wegacy_wwite(stwuct pci_bus *bus, woff_t powt, u32 vaw,
			   size_t count);
extewn int pci_mmap_wegacy_page_wange(stwuct pci_bus *bus,
				      stwuct vm_awea_stwuct *vma,
				      enum pci_mmap_state mmap_state);
extewn void pci_adjust_wegacy_attw(stwuct pci_bus *bus,
				   enum pci_mmap_state mmap_type);
#define HAVE_PCI_WEGACY	1

extewn void pcibios_cwaim_one_bus(stwuct pci_bus *b);

extewn void pcibios_finish_adding_to_bus(stwuct pci_bus *bus);

extewn void pcibios_wesouwce_suwvey(void);

extewn stwuct pci_contwowwew *init_phb_dynamic(stwuct device_node *dn);
extewn int wemove_phb_dynamic(stwuct pci_contwowwew *phb);

extewn stwuct pci_dev *of_cweate_pci_dev(stwuct device_node *node,
					stwuct pci_bus *bus, int devfn);

extewn unsigned int pci_pawse_of_fwags(u32 addw0, int bwidge);

extewn void of_scan_pci_bwidge(stwuct pci_dev *dev);

extewn void of_scan_bus(stwuct device_node *node, stwuct pci_bus *bus);
extewn void of_wescan_bus(stwuct device_node *node, stwuct pci_bus *bus);

extewn pgpwot_t	pci_phys_mem_access_pwot(unsigned wong pfn,
					 unsigned wong size,
					 pgpwot_t pwot);

extewn wesouwce_size_t pcibios_io_space_offset(stwuct pci_contwowwew *hose);
extewn void pcibios_setup_bus_sewf(stwuct pci_bus *bus);
extewn void pcibios_setup_phb_io_space(stwuct pci_contwowwew *hose);
extewn void pcibios_scan_phb(stwuct pci_contwowwew *hose);

#endif	/* __KEWNEW__ */

#endif /* __ASM_POWEWPC_PCI_H */
