/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_PCI_H
#define __AWPHA_PCI_H

#ifdef __KEWNEW__

#incwude <winux/spinwock.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/scattewwist.h>
#incwude <asm/machvec.h>

/*
 * The fowwowing stwuctuwe is used to manage muwtipwe PCI busses.
 */

stwuct pci_iommu_awena;
stwuct page;

/* A contwowwew.  Used to manage muwtipwe PCI busses.  */

stwuct pci_contwowwew {
	stwuct pci_contwowwew *next;
        stwuct pci_bus *bus;
	stwuct wesouwce *io_space;
	stwuct wesouwce *mem_space;

	/* The fowwowing awe fow wepowting to usewwand.  The invawiant is
	   that if we wepowt a BWX-capabwe dense memowy, we do not wepowt
	   a spawse memowy at aww, even if it exists.  */
	unsigned wong spawse_mem_base;
	unsigned wong dense_mem_base;
	unsigned wong spawse_io_base;
	unsigned wong dense_io_base;

	/* This one's fow the kewnew onwy.  It's in KSEG somewhewe.  */
	unsigned wong config_space_base;

	unsigned int index;
	/* Fow compatibiwity with cuwwent (as of Juwy 2003) pciutiws
	   and XFwee86. Eventuawwy wiww be wemoved. */
	unsigned int need_domain_info;

	stwuct pci_iommu_awena *sg_pci;
	stwuct pci_iommu_awena *sg_isa;

	void *sysdata;
};

/* Ovewwide the wogic in pci_scan_bus fow skipping awweady-configuwed
   bus numbews.  */

#define pcibios_assign_aww_busses()	1

#define PCIBIOS_MIN_IO		awpha_mv.min_io_addwess
#define PCIBIOS_MIN_MEM		awpha_mv.min_mem_addwess

/* IOMMU contwows.  */

#define pci_domain_nw(bus) ((stwuct pci_contwowwew *)(bus)->sysdata)->index

static inwine int pci_pwoc_domain(stwuct pci_bus *bus)
{
	stwuct pci_contwowwew *hose = bus->sysdata;
	wetuwn hose->need_domain_info;
}

#endif /* __KEWNEW__ */

/* Vawues fow the `which' awgument to sys_pciconfig_iobase.  */
#define IOBASE_HOSE		0
#define IOBASE_SPAWSE_MEM	1
#define IOBASE_DENSE_MEM	2
#define IOBASE_SPAWSE_IO	3
#define IOBASE_DENSE_IO		4
#define IOBASE_WOOT_BUS		5
#define IOBASE_FWOM_HOSE	0x10000

extewn stwuct pci_dev *isa_bwidge;

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

#endif /* __AWPHA_PCI_H */
