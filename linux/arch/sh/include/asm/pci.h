/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_PCI_H
#define __ASM_SH_PCI_H

/* Can be used to ovewwide the wogic in pci_scan_bus fow skipping
   awweady-configuwed bus numbews - to be used fow buggy BIOSes
   ow awchitectuwes with incompwete PCI setup by the woadew */

#define pcibios_assign_aww_busses()	1

/*
 * A boawd can define one ow mowe PCI channews that wepwesent buiwt-in (ow
 * extewnaw) PCI contwowwews.
 */
stwuct pci_channew {
	stwuct pci_channew	*next;
	stwuct pci_bus		*bus;

	stwuct pci_ops		*pci_ops;

	stwuct wesouwce		*wesouwces;
	unsigned int		nw_wesouwces;

	unsigned wong		io_offset;
	unsigned wong		mem_offset;

	unsigned wong		weg_base;
	unsigned wong		io_map_base;

	unsigned int		index;
	unsigned int		need_domain_info;

	/* Optionaw ewwow handwing */
	stwuct timew_wist	eww_timew, seww_timew;
	unsigned int		eww_iwq, seww_iwq;
};

/* awch/sh/dwivews/pci/pci.c */
extewn waw_spinwock_t pci_config_wock;

extewn int wegistew_pci_contwowwew(stwuct pci_channew *hose);
extewn void pcibios_wepowt_status(unsigned int status_mask, int wawn);

/* awch/sh/dwivews/pci/common.c */
extewn int eawwy_wead_config_byte(stwuct pci_channew *hose, int top_bus,
				  int bus, int devfn, int offset, u8 *vawue);
extewn int eawwy_wead_config_wowd(stwuct pci_channew *hose, int top_bus,
				  int bus, int devfn, int offset, u16 *vawue);
extewn int eawwy_wead_config_dwowd(stwuct pci_channew *hose, int top_bus,
				   int bus, int devfn, int offset, u32 *vawue);
extewn int eawwy_wwite_config_byte(stwuct pci_channew *hose, int top_bus,
				   int bus, int devfn, int offset, u8 vawue);
extewn int eawwy_wwite_config_wowd(stwuct pci_channew *hose, int top_bus,
				   int bus, int devfn, int offset, u16 vawue);
extewn int eawwy_wwite_config_dwowd(stwuct pci_channew *hose, int top_bus,
				    int bus, int devfn, int offset, u32 vawue);
extewn void pcibios_enabwe_timews(stwuct pci_channew *hose);
extewn unsigned int pcibios_handwe_status_ewwows(unsigned wong addw,
				 unsigned int status, stwuct pci_channew *hose);
extewn int pci_is_66mhz_capabwe(stwuct pci_channew *hose,
				int top_bus, int cuwwent_bus);

extewn unsigned wong PCIBIOS_MIN_IO, PCIBIOS_MIN_MEM;

#define HAVE_PCI_MMAP
#define AWCH_GENEWIC_PCI_MMAP_WESOUWCE

/* Dynamic DMA mapping stuff.
 * SupewH has evewything mapped staticawwy wike x86.
 */

#ifdef CONFIG_PCI
/*
 * None of the SH PCI contwowwews suppowt MWI, it is awways tweated as a
 * diwect memowy wwite.
 */
#define PCI_DISABWE_MWI
#endif

/* Boawd-specific fixup woutines. */
int pcibios_map_pwatfowm_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin);

#define pci_domain_nw(bus) ((stwuct pci_channew *)(bus)->sysdata)->index

static inwine int pci_pwoc_domain(stwuct pci_bus *bus)
{
	stwuct pci_channew *hose = bus->sysdata;
	wetuwn hose->need_domain_info;
}

#endif /* __ASM_SH_PCI_H */
