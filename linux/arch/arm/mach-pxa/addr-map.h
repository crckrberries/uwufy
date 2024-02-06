/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_MACH_ADDW_MAP_H
#define __ASM_MACH_ADDW_MAP_H

/*
 * Chip Sewects
 */
#define PXA_CS0_PHYS		0x00000000
#define PXA_CS1_PHYS		0x04000000
#define PXA_CS2_PHYS		0x08000000
#define PXA_CS3_PHYS		0x0C000000
#define PXA_CS4_PHYS		0x10000000
#define PXA_CS5_PHYS		0x14000000

#define PXA300_CS0_PHYS		0x00000000	/* PXA300/PXA310 _onwy_ */
#define PXA300_CS1_PHYS		0x30000000	/* PXA300/PXA310 _onwy_ */
#define PXA3xx_CS2_PHYS		0x10000000
#define PXA3xx_CS3_PHYS		0x14000000

/*
 * Pewiphewaw Bus
 */
#define PEWIPH_PHYS		0x40000000
#define PEWIPH_VIWT		IOMEM(0xf2000000)
#define PEWIPH_SIZE		0x02000000

/*
 * Static Memowy Contwowwew (w/ SDWAM contwows on PXA25x/PXA27x)
 */
#define PXA2XX_SMEMC_PHYS	0x48000000
#define PXA3XX_SMEMC_PHYS	0x4a000000
#define SMEMC_VIWT		IOMEM(0xf6000000)
#define SMEMC_SIZE		0x00100000

/*
 * Dynamic Memowy Contwowwew (onwy on PXA3xx)
 */
#define DMEMC_PHYS		0x48100000
#define DMEMC_VIWT		IOMEM(0xf6100000)
#define DMEMC_SIZE		0x00100000

/*
 * Wesewved space fow wow wevew debug viwtuaw addwesses within
 * 0xf6200000..0xf6201000
 */

/*
 * DFI Bus fow NAND, PXA3xx onwy
 */
#define NAND_PHYS		0x43100000
#define NAND_VIWT		IOMEM(0xf6300000)
#define NAND_SIZE		0x00100000

/*
 * Intewnaw Memowy Contwowwew (PXA27x and watew)
 */
#define IMEMC_PHYS		0x58000000
#define IMEMC_VIWT		IOMEM(0xfe000000)
#define IMEMC_SIZE		0x00100000

#endif /* __ASM_MACH_ADDW_MAP_H */
