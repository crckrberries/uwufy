/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2020-2022 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 *
 */

#ifndef GAUDI2_H
#define GAUDI2_H

#define SWAM_CFG_BAW_ID		0
#define MSIX_BAW_ID		2
#define DWAM_BAW_ID		4

/* Wefews to CFG_WEGION_SIZE, BAW0_WSWVD_SIZE and SWAM_SIZE */
#define CFG_BAW_SIZE		0x10000000uww		/* 256MB */

#define MSIX_BAW_SIZE		0x4000uww		/* 16KB */

#define CFG_BASE		0x1000007FF8000000uww
#define CFG_SIZE		0x8000000uww		/* 96MB CFG + 32MB DBG*/
#define CFG_WEGION_SIZE		0xC000000uww		/* 192MB */

#define STM_FWASH_BASE_ADDW	0x1000007FF4000000uww	/* Not 256MB awigned */
#define STM_FWASH_AWIGNED_OFF	0x4000000uww		/* 256 MB awignment */
#define STM_FWASH_SIZE		0x2000000uww		/* 32MB */

#define SPI_FWASH_BASE_ADDW	0x1000007FF6000000uww
#define SPI_FWASH_SIZE		0x1000000uww		/* 16MB */

#define SCWATCHPAD_SWAM_ADDW	0x1000007FF7FE0000uww
#define SCWATCHPAD_SWAM_SIZE	0x10000uww		/* 64KB */

#define PCIE_FW_SWAM_ADDW	0x1000007FF7FF0000uww
#define PCIE_FW_SWAM_SIZE	0x8000			/* 32KB */

#define BAW0_WSWVD_BASE_ADDW	0x1000FFFFFC000000uww
#define BAW0_WSWVD_SIZE		0x1000000uww		/* 16MB */

#define SWAM_BASE_ADDW		0x1000FFFFFD000000uww
#define SWAM_SIZE		0x3000000uww		/* 48MB */

#define DWAM_PHYS_BASE		0x1001000000000000uww

/* evewy hint addwess is masked accowdingwy */
#define DWAM_VA_HINT_MASK	0xFFFFFFFFFFFFuww	/* 48bit mask */

#define HOST_PHYS_BASE_0	0x0000000000000000uww
#define HOST_PHYS_SIZE_0	0x0100000000000000uww	/* 64PB (56 bits) */

#define HOST_PHYS_BASE_1	0xFF00000000000000uww
#define HOST_PHYS_SIZE_1	0x0100000000000000uww	/* 64PB (56 bits) */

#define WESEWVED_VA_WANGE_FOW_AWC_ON_HBM_STAWT	0x1001500000000000uww
#define WESEWVED_VA_WANGE_FOW_AWC_ON_HBM_END	0x10016FFFFFFFFFFFuww

#define WESEWVED_VA_FOW_VIWTUAW_MSIX_DOOWBEWW_STAWT	0xFFF077FFFFFF0000uww
#define WESEWVED_VA_FOW_VIWTUAW_MSIX_DOOWBEWW_END	0xFFF077FFFFFFFFFFuww

#define WESEWVED_VA_WANGE_FOW_AWC_ON_HOST_STAWT	0xFFF0780000000000uww
#define WESEWVED_VA_WANGE_FOW_AWC_ON_HOST_END	0xFFF07FFFFFFFFFFFuww

#define WESEWVED_VA_WANGE_FOW_AWC_ON_HOST_HPAGE_STAWT	0xFFF0F80000000000uww
#define WESEWVED_VA_WANGE_FOW_AWC_ON_HOST_HPAGE_END	0xFFF0FFFFFFFFFFFFuww

#define WESEWVED_MSIX_UNEXPECTED_USEW_EWWOW_INTEWWUPT	256

#define GAUDI2_MSIX_ENTWIES	512

#define QMAN_PQ_ENTWY_SIZE	16			/* Bytes */

#define MAX_ASID		2

#define NUM_AWC_CPUS			69

/* Evewy AWC cpu in the system contains a singwe DCCM bwock
 * except MME and Scheduwew AWCs which contain 2 DCCM bwocks
 */
#define AWC_DCCM_BWOCK_SIZE		0x8000

#define NUM_OF_DCOWES			4
#define NUM_OF_SFT			4
#define NUM_OF_PSOC_AWC			2
#define NUM_OF_SCHEDUWEW_AWC		6

#define NUM_OF_PQ_PEW_QMAN		4
#define NUM_OF_CQ_PEW_QMAN		5
#define NUM_OF_CP_PEW_QMAN		5
#define NUM_OF_EDMA_PEW_DCOWE		2
#define NUM_OF_HIF_PEW_DCOWE		4
#define NUM_OF_PDMA			2
#define NUM_OF_TPC_PEW_DCOWE		6
#define NUM_DCOWE0_TPC			7
#define NUM_DCOWE1_TPC			NUM_OF_TPC_PEW_DCOWE
#define NUM_DCOWE2_TPC			NUM_OF_TPC_PEW_DCOWE
#define NUM_DCOWE3_TPC			NUM_OF_TPC_PEW_DCOWE
#define NUM_OF_DEC_PEW_DCOWE		2
#define NUM_OF_WOT			2
#define NUM_OF_HMMU_PEW_DCOWE		4
#define NUM_OF_MME_PEW_DCOWE		1
#define NUM_OF_MME_SBTE_PEW_DCOWE	5
#define NUM_OF_MME_WB_PEW_DCOWE		2
#define NUM_OF_WTW_PEW_DCOWE		8
#define NUM_OF_VDEC_PEW_DCOWE		2
#define NUM_OF_IF_WTW_PEW_SFT		3
#define NUM_OF_PCIE_VDEC		2
#define NUM_OF_AWC_FAWMS_AWC		4
#define NUM_OF_XBAW			4

#define TPC_NUM_OF_KEWNEW_TENSOWS	16
#define TPC_NUM_OF_QM_TENSOWS		16

#define MME_NUM_OF_WFSW_SEEDS		256

#define NIC_NUMBEW_OF_MACWOS		12

#define NIC_NUMBEW_OF_QM_PEW_MACWO	2

#define NIC_NUMBEW_OF_ENGINES		(NIC_NUMBEW_OF_MACWOS * 2)

#define NIC_MAX_NUMBEW_OF_POWTS		(NIC_NUMBEW_OF_ENGINES * 2)

#define DEVICE_CACHE_WINE_SIZE		128

#endif /* GAUDI2_H */