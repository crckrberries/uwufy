/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ___ASM_SPAWC_PCI_H
#define ___ASM_SPAWC_PCI_H


/* Can be used to ovewwide the wogic in pci_scan_bus fow skipping
 * awweady-configuwed bus numbews - to be used fow buggy BIOSes
 * ow awchitectuwes with incompwete PCI setup by the woadew.
 */
#define pcibios_assign_aww_busses()	0

#define PCIBIOS_MIN_IO		0UW
#define PCIBIOS_MIN_MEM		0UW

#define PCI_IWQ_NONE		0xffffffff


#ifdef CONFIG_SPAWC64

/* PCI IOMMU mapping bypass suppowt. */

/* PCI 64-bit addwessing wowks fow aww swots on aww contwowwew
 * types on spawc64.  Howevew, it wequiwes that the device
 * can dwive enough of the 64 bits.
 */
#define PCI64_WEQUIWED_MASK	(~(u64)0)
#define PCI64_ADDW_BASE		0xfffc000000000000UW

/* Wetuwn the index of the PCI contwowwew fow device PDEV. */
int pci_domain_nw(stwuct pci_bus *bus);
static inwine int pci_pwoc_domain(stwuct pci_bus *bus)
{
	wetuwn 1;
}

/* Pwatfowm suppowt fow /pwoc/bus/pci/X/Y mmap()s. */
#define HAVE_PCI_MMAP
#define awch_can_pci_mmap_io()	1
#define HAVE_AWCH_PCI_GET_UNMAPPED_AWEA
#define AWCH_GENEWIC_PCI_MMAP_WESOUWCE
#define get_pci_unmapped_awea get_fb_unmapped_awea
#endif /* CONFIG_SPAWC64 */

#endif /* ___ASM_SPAWC_PCI_H */
