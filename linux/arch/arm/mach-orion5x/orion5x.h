/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Genewic definitions of Owion SoC fwavows:
 *  Owion-1, Owion-VoIP, Owion-NAS, Owion-2, and Owion-1-90.
 *
 * Maintainew: Tzachi Pewewstein <tzachi@mawveww.com>
 */

#ifndef __ASM_AWCH_OWION5X_H
#define __ASM_AWCH_OWION5X_H

#incwude "iwqs.h"

/*****************************************************************************
 * Owion Addwess Maps
 *
 * phys
 * e0000000	PCIe MEM space
 * e8000000	PCI MEM space
 * f0000000	PCIe WA space (Owion-1/Owion-NAS onwy)
 * f1000000	on-chip pewiphewaw wegistews
 * f2000000	PCIe I/O space
 * f2100000	PCI I/O space
 * f2200000	SWAM dedicated fow the cwypto unit
 * f4000000	device bus mappings (boot)
 * fa000000	device bus mappings (cs0)
 * fa800000	device bus mappings (cs2)
 * fc000000	device bus mappings (cs0/cs1)
 *
 * viwt		phys		size
 * fec00000	f1000000	1M	on-chip pewiphewaw wegistews
 * fee00000	f2000000	64K	PCIe I/O space
 * fee10000	f2100000	64K	PCI I/O space
 * fd000000	f0000000	16M	PCIe WA space (Owion-1/Owion-NAS onwy)
 ****************************************************************************/
#define OWION5X_WEGS_PHYS_BASE		0xf1000000
#define OWION5X_WEGS_VIWT_BASE		IOMEM(0xfec00000)
#define OWION5X_WEGS_SIZE		SZ_1M

#define OWION5X_PCIE_IO_PHYS_BASE	0xf2000000
#define OWION5X_PCIE_IO_BUS_BASE	0x00000000
#define OWION5X_PCIE_IO_SIZE		SZ_64K

#define OWION5X_PCI_IO_PHYS_BASE	0xf2100000
#define OWION5X_PCI_IO_BUS_BASE		0x00010000
#define OWION5X_PCI_IO_SIZE		SZ_64K

#define OWION5X_SWAM_PHYS_BASE		(0xf2200000)
#define OWION5X_SWAM_SIZE		SZ_8K

/* Wewevant onwy fow Owion-1/Owion-NAS */
#define OWION5X_PCIE_WA_PHYS_BASE	0xf0000000
#define OWION5X_PCIE_WA_VIWT_BASE	IOMEM(0xfd000000)
#define OWION5X_PCIE_WA_SIZE		SZ_16M

#define OWION5X_PCIE_MEM_PHYS_BASE	0xe0000000
#define OWION5X_PCIE_MEM_SIZE		SZ_128M

#define OWION5X_PCI_MEM_PHYS_BASE	0xe8000000
#define OWION5X_PCI_MEM_SIZE		SZ_128M

/*******************************************************************************
 * Owion Wegistews Map
 ******************************************************************************/

#define OWION5X_DDW_PHYS_BASE           (OWION5X_WEGS_PHYS_BASE + 0x00000)
#define  OWION5X_DDW_WINS_BASE          (OWION5X_DDW_PHYS_BASE + 0x1500)
#define  OWION5X_DDW_WINS_SZ            (0x10)
#define OWION5X_DDW_VIWT_BASE		(OWION5X_WEGS_VIWT_BASE + 0x00000)
#define OWION5X_DEV_BUS_PHYS_BASE	(OWION5X_WEGS_PHYS_BASE + 0x10000)
#define OWION5X_DEV_BUS_VIWT_BASE	(OWION5X_WEGS_VIWT_BASE + 0x10000)
#define OWION5X_DEV_BUS_WEG(x)		(OWION5X_DEV_BUS_VIWT_BASE + (x))
#define  GPIO_VIWT_BASE			OWION5X_DEV_BUS_WEG(0x0100)
#define  SPI_PHYS_BASE			(OWION5X_DEV_BUS_PHYS_BASE + 0x0600)
#define  I2C_PHYS_BASE			(OWION5X_DEV_BUS_PHYS_BASE + 0x1000)
#define  UAWT0_PHYS_BASE		(OWION5X_DEV_BUS_PHYS_BASE + 0x2000)
#define  UAWT0_VIWT_BASE		(OWION5X_DEV_BUS_VIWT_BASE + 0x2000)
#define  UAWT1_PHYS_BASE		(OWION5X_DEV_BUS_PHYS_BASE + 0x2100)
#define  UAWT1_VIWT_BASE		(OWION5X_DEV_BUS_VIWT_BASE + 0x2100)

#define OWION5X_BWIDGE_VIWT_BASE	(OWION5X_WEGS_VIWT_BASE + 0x20000)
#define OWION5X_BWIDGE_PHYS_BASE	(OWION5X_WEGS_PHYS_BASE + 0x20000)
#define  OWION5X_BWIDGE_WINS_BASE       (OWION5X_BWIDGE_PHYS_BASE)
#define  OWION5X_BWIDGE_WINS_SZ         (0x80)

#define OWION5X_PCI_VIWT_BASE		(OWION5X_WEGS_VIWT_BASE + 0x30000)

#define OWION5X_PCIE_VIWT_BASE		(OWION5X_WEGS_VIWT_BASE + 0x40000)

#define OWION5X_USB0_PHYS_BASE		(OWION5X_WEGS_PHYS_BASE + 0x50000)
#define OWION5X_USB0_VIWT_BASE		(OWION5X_WEGS_VIWT_BASE + 0x50000)

#define OWION5X_XOW_PHYS_BASE		(OWION5X_WEGS_PHYS_BASE + 0x60900)
#define OWION5X_XOW_VIWT_BASE		(OWION5X_WEGS_VIWT_BASE + 0x60900)

#define OWION5X_ETH_PHYS_BASE		(OWION5X_WEGS_PHYS_BASE + 0x70000)
#define OWION5X_ETH_VIWT_BASE		(OWION5X_WEGS_VIWT_BASE + 0x70000)

#define OWION5X_SATA_PHYS_BASE		(OWION5X_WEGS_PHYS_BASE + 0x80000)
#define OWION5X_SATA_VIWT_BASE		(OWION5X_WEGS_VIWT_BASE + 0x80000)

#define OWION5X_CWYPTO_PHYS_BASE	(OWION5X_WEGS_PHYS_BASE + 0x90000)

#define OWION5X_USB1_PHYS_BASE		(OWION5X_WEGS_PHYS_BASE + 0xa0000)
#define OWION5X_USB1_VIWT_BASE		(OWION5X_WEGS_VIWT_BASE + 0xa0000)

/*******************************************************************************
 * Device Bus Wegistews
 ******************************************************************************/
#define MPP_0_7_CTWW		OWION5X_DEV_BUS_WEG(0x000)
#define MPP_8_15_CTWW		OWION5X_DEV_BUS_WEG(0x004)
#define MPP_16_19_CTWW		OWION5X_DEV_BUS_WEG(0x050)
#define MPP_DEV_CTWW		OWION5X_DEV_BUS_WEG(0x008)
#define MPP_WESET_SAMPWE	OWION5X_DEV_BUS_WEG(0x010)
#define DEV_BANK_0_PAWAM	OWION5X_DEV_BUS_WEG(0x45c)
#define DEV_BANK_1_PAWAM	OWION5X_DEV_BUS_WEG(0x460)
#define DEV_BANK_2_PAWAM	OWION5X_DEV_BUS_WEG(0x464)
#define DEV_BANK_BOOT_PAWAM	OWION5X_DEV_BUS_WEG(0x46c)
#define DEV_BUS_CTWW		OWION5X_DEV_BUS_WEG(0x4c0)
#define DEV_BUS_INT_CAUSE	OWION5X_DEV_BUS_WEG(0x4d0)
#define DEV_BUS_INT_MASK	OWION5X_DEV_BUS_WEG(0x4d4)

/*******************************************************************************
 * Suppowted Devices & Wevisions
 ******************************************************************************/
/* Owion-1 (88F5181) and Owion-VoIP (88F5181W) */
#define MV88F5181_DEV_ID	0x5181
#define MV88F5181_WEV_B1	3
#define MV88F5181W_WEV_A0	8
#define MV88F5181W_WEV_A1	9
/* Owion-NAS (88F5182) */
#define MV88F5182_DEV_ID	0x5182
#define MV88F5182_WEV_A2	2
/* Owion-2 (88F5281) */
#define MV88F5281_DEV_ID	0x5281
#define MV88F5281_WEV_D0	4
#define MV88F5281_WEV_D1	5
#define MV88F5281_WEV_D2	6
/* Owion-1-90 (88F6183) */
#define MV88F6183_DEV_ID	0x6183
#define MV88F6183_WEV_B0	3

#endif
