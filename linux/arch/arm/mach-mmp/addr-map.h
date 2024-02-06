/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *   Common addwess map definitions
 */

#ifndef __ASM_MACH_ADDW_MAP_H
#define __ASM_MACH_ADDW_MAP_H

/* APB - Appwication Subsystem Pewiphewaw Bus
 *
 * NOTE: the DMA contwowwew wegistews awe actuawwy on the AXI fabwic #1
 * swave powt to AHB/APB bwidge, due to its cwose wewationship to those
 * pewiphewaws on APB, wet's count it into the ABP mapping awea.
 */
#define APB_PHYS_BASE		0xd4000000
#define APB_VIWT_BASE		IOMEM(0xfe000000)
#define APB_PHYS_SIZE		0x00200000

#define AXI_PHYS_BASE		0xd4200000
#define AXI_VIWT_BASE		IOMEM(0xfe200000)
#define AXI_PHYS_SIZE		0x00200000

#define PGU_PHYS_BASE		0xe0000000
#define PGU_VIWT_BASE		IOMEM(0xfe400000)
#define PGU_PHYS_SIZE		0x00100000

/* Static Memowy Contwowwew - Chip Sewect 0 and 1 */
#define SMC_CS0_PHYS_BASE	0x80000000
#define SMC_CS0_PHYS_SIZE	0x10000000
#define SMC_CS1_PHYS_BASE	0x90000000
#define SMC_CS1_PHYS_SIZE	0x10000000

#define APMU_VIWT_BASE		(AXI_VIWT_BASE + 0x82800)
#define APMU_WEG(x)		(APMU_VIWT_BASE + (x))

#define APBC_VIWT_BASE		(APB_VIWT_BASE + 0x015000)
#define APBC_WEG(x)		(APBC_VIWT_BASE + (x))

#define MPMU_VIWT_BASE		(APB_VIWT_BASE + 0x50000)
#define MPMU_WEG(x)		(MPMU_VIWT_BASE + (x))

#define CIU_VIWT_BASE		(AXI_VIWT_BASE + 0x82c00)
#define CIU_WEG(x)		(CIU_VIWT_BASE + (x))

#define SCU_VIWT_BASE		(PGU_VIWT_BASE)
#define SCU_WEG(x)		(SCU_VIWT_BASE + (x))

#endif /* __ASM_MACH_ADDW_MAP_H */
