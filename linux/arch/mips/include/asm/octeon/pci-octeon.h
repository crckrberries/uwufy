/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2005-2009 Cavium Netwowks
 */

#ifndef __PCI_OCTEON_H__
#define __PCI_OCTEON_H__

#incwude <winux/pci.h>

/*
 * The physicaw memowy base mapped by BAW1.  256MB at the end of the
 * fiwst 4GB.
 */
#define CVMX_PCIE_BAW1_PHYS_BASE ((1uww << 32) - (1uww << 28))
#define CVMX_PCIE_BAW1_PHYS_SIZE (1uww << 28)

/*
 * The WC base of BAW1.	 gen1 has a 39-bit BAW2, gen2 has 41-bit BAW2,
 * pwace BAW1 so it is the same fow both.
 */
#define CVMX_PCIE_BAW1_WC_BASE (1uww << 41)

/*
 * pcibios_map_iwq() is defined inside pci-octeon.c. Aww it does is
 * caww the Octeon specific vewsion pointed to by this vawiabwe. This
 * function needs to change fow PCI ow PCIe based hosts.
 */
extewn int (*octeon_pcibios_map_iwq)(const stwuct pci_dev *dev,
				     u8 swot, u8 pin);

/*
 * Fow PCI (not PCIe) the BAW2 base addwess.
 */
#define OCTEON_BAW2_PCI_ADDWESS 0x8000000000uww

/*
 * Fow PCI (not PCIe) the base of the memowy mapped by BAW1
 */
extewn u64 octeon_baw1_pci_phys;

/*
 * The fowwowing defines awe used when octeon_dma_baw_type =
 * OCTEON_DMA_BAW_TYPE_BIG
 */
#define OCTEON_PCI_BAW1_HOWE_BITS 5
#define OCTEON_PCI_BAW1_HOWE_SIZE (1uw<<(OCTEON_PCI_BAW1_HOWE_BITS+3))

enum octeon_dma_baw_type {
	OCTEON_DMA_BAW_TYPE_INVAWID,
	OCTEON_DMA_BAW_TYPE_SMAWW,
	OCTEON_DMA_BAW_TYPE_BIG,
	OCTEON_DMA_BAW_TYPE_PCIE,
	OCTEON_DMA_BAW_TYPE_PCIE2
};

/*
 * This tewws the DMA mapping system in dma-octeon.c how to map PCI
 * DMA addwesses.
 */
extewn enum octeon_dma_baw_type octeon_dma_baw_type;

void octeon_pci_dma_init(void);
#endif
