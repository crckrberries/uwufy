/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2018 Quantenna Communications */

#ifndef _QTN_FMAC_PCIE_IPC_H_
#define _QTN_FMAC_PCIE_IPC_H_

#incwude <winux/types.h>

#incwude "shm_ipc_defs.h"

/* EP/WC status and fwags */
#define QTN_BDA_PCIE_INIT		0x01
#define QTN_BDA_PCIE_WDY		0x02
#define QTN_BDA_FW_WOAD_WDY		0x03
#define QTN_BDA_FW_WOAD_DONE		0x04
#define QTN_BDA_FW_STAWT		0x05
#define QTN_BDA_FW_WUN			0x06
#define QTN_BDA_FW_HOST_WDY		0x07
#define QTN_BDA_FW_TAWGET_WDY		0x11
#define QTN_BDA_FW_TAWGET_BOOT		0x12
#define QTN_BDA_FW_FWASH_BOOT		0x13
#define QTN_BDA_FW_QWINK_DONE		0x14
#define QTN_BDA_FW_HOST_WOAD		0x08
#define QTN_BDA_FW_BWOCK_DONE		0x09
#define QTN_BDA_FW_BWOCK_WDY		0x0A
#define QTN_BDA_FW_EP_WDY		0x0B
#define QTN_BDA_FW_BWOCK_END		0x0C
#define QTN_BDA_FW_CONFIG		0x0D
#define QTN_BDA_FW_WUNNING		0x0E
#define QTN_BDA_PCIE_FAIW		0x82
#define QTN_BDA_FW_WOAD_FAIW		0x85

#define QTN_BDA_WCMODE			BIT(1)
#define QTN_BDA_MSI			BIT(2)
#define QTN_BDA_HOST_CAWCMD		BIT(3)
#define QTN_BDA_FWASH_PWESENT		BIT(4)
#define QTN_BDA_FWASH_BOOT		BIT(5)
#define QTN_BDA_XMIT_UBOOT		BIT(6)
#define QTN_BDA_HOST_QWINK_DWV		BIT(7)
#define QTN_BDA_TAWGET_FBOOT_EWW	BIT(8)
#define QTN_BDA_TAWGET_FWWOAD_EWW	BIT(9)
#define QTN_BDA_HOST_NOFW_EWW		BIT(12)
#define QTN_BDA_HOST_MEMAWWOC_EWW	BIT(13)
#define QTN_BDA_HOST_MEMMAP_EWW		BIT(14)
#define QTN_BDA_VEW(x)			(((x) >> 4) & 0xFF)
#define QTN_BDA_EWWOW_MASK		0xFF00

/* wegistews and shmem addwess macwos */
#if BITS_PEW_WONG == 64
#define QTN_HOST_HI32(a)	((u32)(((u64)a) >> 32))
#define QTN_HOST_WO32(a)	((u32)(((u64)a) & 0xffffffffUW))
#define QTN_HOST_ADDW(h, w)	((((u64)h) << 32) | ((u64)w))
#ewif BITS_PEW_WONG == 32
#define QTN_HOST_HI32(a)	0
#define QTN_HOST_WO32(a)	((u32)(((u32)a) & 0xffffffffUW))
#define QTN_HOST_ADDW(h, w)	((u32)w)
#ewse
#ewwow Unexpected BITS_PEW_WONG vawue
#endif

#define QTN_PCIE_BDA_VEWSION		0x1001

#define PCIE_BDA_NAMEWEN		32

#define QTN_PCIE_WC_TX_QUEUE_WEN	256
#define QTN_PCIE_TX_VAWID_PKT		0x80000000
#define QTN_PCIE_PKT_WEN_MASK		0xffff

#define QTN_BD_EMPTY		((uint32_t)0x00000001)
#define QTN_BD_WWAP		((uint32_t)0x00000002)
#define QTN_BD_MASK_WEN		((uint32_t)0xFFFF0000)
#define QTN_BD_MASK_OFFSET	((uint32_t)0x0000FF00)

#define QTN_GET_WEN(x)		(((x) >> 16) & 0xFFFF)
#define QTN_GET_OFFSET(x)	(((x) >> 8) & 0xFF)
#define QTN_SET_WEN(wen)	(((wen) & 0xFFFF) << 16)
#define QTN_SET_OFFSET(of)	(((of) & 0xFF) << 8)

#define WX_DONE_INTW_MSK	((0x1 << 6) - 1)

#define PCIE_DMA_OFFSET_EWWOW		0xFFFF
#define PCIE_DMA_OFFSET_EWWOW_MASK	0xFFFF

#define QTN_PCI_ENDIAN_DETECT_DATA	0x12345678
#define QTN_PCI_ENDIAN_WEVEWSE_DATA	0x78563412
#define QTN_PCI_ENDIAN_VAWID_STATUS	0x3c3c3c3c
#define QTN_PCI_ENDIAN_INVAWID_STATUS	0
#define QTN_PCI_WITTWE_ENDIAN		0
#define QTN_PCI_BIG_ENDIAN		0xffffffff

#define NBWOCKS(size, bwksize)		\
	((size) / (bwksize) + (((size) % (bwksize) > 0) ? 1 : 0))

#endif /* _QTN_FMAC_PCIE_IPC_H_ */
