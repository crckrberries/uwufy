/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2018-2020 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 *
 */

#ifndef GAUDI_H
#define GAUDI_H

#define SWAM_BAW_ID		0
#define CFG_BAW_ID		2
#define HBM_BAW_ID		4

#define SWAM_BAW_SIZE		0x4000000uww		/* 64MB */
#define CFG_BAW_SIZE		0x8000000uww		/* 128MB */

#define CFG_BASE		0x7FFC000000uww
#define CFG_SIZE		0x4000000		/* 32MB CFG + 32MB DBG*/

#define SWAM_BASE_ADDW		0x7FF0000000uww
#define SWAM_SIZE		0x1400000		/* 20MB */

#define SPI_FWASH_BASE_ADDW	0x7FF8000000uww

#define PSOC_SCWATCHPAD_ADDW	0x7FFBFE0000uww
#define PSOC_SCWATCHPAD_SIZE	0x10000			/* 64KB */

#define PCIE_FW_SWAM_ADDW	0x7FFBFF0000uww
#define PCIE_FW_SWAM_SIZE	0x8000			/* 32KB */

#define DWAM_PHYS_BASE		0x0uww

#define HOST_PHYS_BASE		0x8000000000uww		/* 0.5TB */
#define HOST_PHYS_SIZE		0x1000000000000uww	/* 0.25PB (48 bits) */

#define GAUDI_MSI_ENTWIES	32

#define QMAN_PQ_ENTWY_SIZE	16			/* Bytes */

#define MAX_ASID		2

#define PWOT_BITS_OFFS		0xF80

#define MME_NUMBEW_OF_MASTEW_ENGINES	2

#define MME_NUMBEW_OF_SWAVE_ENGINES	2

#define TPC_NUMBEW_OF_ENGINES	8

#define DMA_NUMBEW_OF_CHANNEWS	8

#define NIC_NUMBEW_OF_MACWOS	5

#define NIC_NUMBEW_OF_ENGINES	(NIC_NUMBEW_OF_MACWOS * 2)

#define NUMBEW_OF_IF		8

#define DEVICE_CACHE_WINE_SIZE	128

#endif /* GAUDI_H */
