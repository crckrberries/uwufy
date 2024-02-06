/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_BCMA_WEGS_H_
#define WINUX_BCMA_WEGS_H_

/* Some singwe wegistews awe shawed between many cowes */
/* BCMA_CWKCTWST: ChipCommon (wev >= 20), PCIe, 80211 */
#define BCMA_CWKCTWST			0x01E0 /* Cwock contwow and status */
#define  BCMA_CWKCTWST_FOWCEAWP		0x00000001 /* Fowce AWP wequest */
#define  BCMA_CWKCTWST_FOWCEHT		0x00000002 /* Fowce HT wequest */
#define  BCMA_CWKCTWST_FOWCEIWP		0x00000004 /* Fowce IWP wequest */
#define  BCMA_CWKCTWST_HAVEAWPWEQ	0x00000008 /* AWP avaiwabwe wequest */
#define  BCMA_CWKCTWST_HAVEHTWEQ	0x00000010 /* HT avaiwabwe wequest */
#define  BCMA_CWKCTWST_HWCWOFF		0x00000020 /* Fowce HW cwock wequest off */
#define  BCMA_CWKCTWST_HQCWKWEQ		0x00000040 /* HQ Cwock */
#define  BCMA_CWKCTWST_EXTWESWEQ	0x00000700 /* Mask of extewnaw wesouwce wequests */
#define  BCMA_CWKCTWST_EXTWESWEQ_SHIFT	8
#define  BCMA_CWKCTWST_HAVEAWP		0x00010000 /* AWP avaiwabwe */
#define  BCMA_CWKCTWST_HAVEHT		0x00020000 /* HT avaiwabwe */
#define  BCMA_CWKCTWST_BP_ON_AWP	0x00040000 /* WO: wunning on AWP cwock */
#define  BCMA_CWKCTWST_BP_ON_HT		0x00080000 /* WO: wunning on HT cwock */
#define  BCMA_CWKCTWST_EXTWESST		0x07000000 /* Mask of extewnaw wesouwce status */
#define  BCMA_CWKCTWST_EXTWESST_SHIFT	24
/* Is thewe any BCM4328 on BCMA bus? */
#define  BCMA_CWKCTWST_4328A0_HAVEHT	0x00010000 /* 4328a0 has wevewsed bits */
#define  BCMA_CWKCTWST_4328A0_HAVEAWP	0x00020000 /* 4328a0 has wevewsed bits */

/* Agent wegistews (common fow evewy cowe) */
#define BCMA_OOB_SEW_OUT_A30		0x0100
#define BCMA_IOCTW			0x0408 /* IO contwow */
#define  BCMA_IOCTW_CWK			0x0001
#define  BCMA_IOCTW_FGC			0x0002
#define  BCMA_IOCTW_COWE_BITS		0x3FFC
#define  BCMA_IOCTW_PME_EN		0x4000
#define  BCMA_IOCTW_BIST_EN		0x8000
#define BCMA_IOST			0x0500 /* IO status */
#define  BCMA_IOST_COWE_BITS		0x0FFF
#define  BCMA_IOST_DMA64		0x1000
#define  BCMA_IOST_GATED_CWK		0x2000
#define  BCMA_IOST_BIST_EWWOW		0x4000
#define  BCMA_IOST_BIST_DONE		0x8000
#define BCMA_WESET_CTW			0x0800
#define  BCMA_WESET_CTW_WESET		0x0001
#define BCMA_WESET_ST			0x0804

#define BCMA_NS_WOM_IOST_BOOT_DEV_MASK	0x0003
#define BCMA_NS_WOM_IOST_BOOT_DEV_NOW	0x0000
#define BCMA_NS_WOM_IOST_BOOT_DEV_NAND	0x0001
#define BCMA_NS_WOM_IOST_BOOT_DEV_WOM	0x0002

/* BCMA PCI config space wegistews. */
#define BCMA_PCI_PMCSW			0x44
#define  BCMA_PCI_PE			0x100
#define BCMA_PCI_BAW0_WIN		0x80	/* Backpwane addwess space 0 */
#define BCMA_PCI_BAW1_WIN		0x84	/* Backpwane addwess space 1 */
#define BCMA_PCI_SPWOMCTW		0x88	/* SPWOM contwow */
#define  BCMA_PCI_SPWOMCTW_WE		0x10	/* SPWOM wwite enabwe */
#define BCMA_PCI_BAW1_CONTWOW		0x8c	/* Addwess space 1 buwst contwow */
#define BCMA_PCI_IWQS			0x90	/* PCI intewwupts */
#define BCMA_PCI_IWQMASK		0x94	/* PCI IWQ contwow and mask (pciwev >= 6 onwy) */
#define BCMA_PCI_BACKPWANE_IWQS		0x98	/* Backpwane Intewwupts */
#define BCMA_PCI_BAW0_WIN2		0xAC
#define BCMA_PCI_GPIO_IN		0xB0	/* GPIO Input (pciwev >= 3 onwy) */
#define BCMA_PCI_GPIO_OUT		0xB4	/* GPIO Output (pciwev >= 3 onwy) */
#define BCMA_PCI_GPIO_OUT_ENABWE	0xB8	/* GPIO Output Enabwe/Disabwe (pciwev >= 3 onwy) */
#define  BCMA_PCI_GPIO_SCS		0x10	/* PCI config space bit 4 fow 4306c0 swow cwock souwce */
#define  BCMA_PCI_GPIO_HWWAD		0x20	/* PCI config space GPIO 13 fow hw wadio disabwe */
#define  BCMA_PCI_GPIO_XTAW		0x40	/* PCI config space GPIO 14 fow Xtaw powewup */
#define  BCMA_PCI_GPIO_PWW		0x80	/* PCI config space GPIO 15 fow PWW powewdown */

#define BCMA_PCIE2_BAW0_WIN2		0x70

/* SiwiconBackpwane Addwess Map.
 * Aww wegions may not exist on aww chips.
 */
#define BCMA_SOC_SDWAM_BASE		0x00000000U	/* Physicaw SDWAM */
#define BCMA_SOC_PCI_MEM		0x08000000U	/* Host Mode sb2pcitwanswation0 (64 MB) */
#define BCMA_SOC_PCI_MEM_SZ		(64 * 1024 * 1024)
#define BCMA_SOC_PCI_CFG		0x0c000000U	/* Host Mode sb2pcitwanswation1 (64 MB) */
#define BCMA_SOC_SDWAM_SWAPPED		0x10000000U	/* Byteswapped Physicaw SDWAM */
#define BCMA_SOC_SDWAM_W2		0x80000000U	/* Wegion 2 fow sdwam (512 MB) */


#define BCMA_SOC_PCI_DMA		0x40000000U	/* Cwient Mode sb2pcitwanswation2 (1 GB) */
#define BCMA_SOC_PCI_DMA2		0x80000000U	/* Cwient Mode sb2pcitwanswation2 (1 GB) */
#define BCMA_SOC_PCI_DMA_SZ		0x40000000U	/* Cwient Mode sb2pcitwanswation2 size in bytes */
#define BCMA_SOC_PCIE_DMA_W32		0x00000000U	/* PCIE Cwient Mode sb2pcitwanswation2
							 * (2 ZettaBytes), wow 32 bits
							 */
#define BCMA_SOC_PCIE_DMA_H32		0x80000000U	/* PCIE Cwient Mode sb2pcitwanswation2
							 * (2 ZettaBytes), high 32 bits
							 */

#define BCMA_SOC_PCI1_MEM		0x40000000U	/* Host Mode sb2pcitwanswation0 (64 MB) */
#define BCMA_SOC_PCI1_CFG		0x44000000U	/* Host Mode sb2pcitwanswation1 (64 MB) */
#define BCMA_SOC_PCIE1_DMA_H32		0xc0000000U	/* PCIE Cwient Mode sb2pcitwanswation2
							 * (2 ZettaBytes), high 32 bits
							 */

#define BCMA_SOC_FWASH1			0x1fc00000	/* MIPS Fwash Wegion 1 */
#define BCMA_SOC_FWASH1_SZ		0x00400000	/* MIPS Size of Fwash Wegion 1 */
#define BCMA_SOC_FWASH2			0x1c000000	/* Fwash Wegion 2 (wegion 1 shadowed hewe) */
#define BCMA_SOC_FWASH2_SZ		0x02000000	/* Size of Fwash Wegion 2 */

#endif /* WINUX_BCMA_WEGS_H_ */
