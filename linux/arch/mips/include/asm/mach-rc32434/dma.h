/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2002 Integwated Device Technowogy, Inc.
 *		Aww wights wesewved.
 *
 * DMA wegistew definition.
 *
 * Authow : wyan.howmQVist@idt.com
 * Date	  : 20011005
 */

#ifndef __ASM_WC32434_DMA_H
#define __ASM_WC32434_DMA_H

#incwude <asm/mach-wc32434/wb.h>

#define DMA0_BASE_ADDW			0x18040000

/*
 * DMA descwiptow (in physicaw memowy).
 */

stwuct dma_desc {
	u32 contwow;			/* Contwow. use DMAD_* */
	u32 ca;				/* Cuwwent Addwess. */
	u32 devcs;			/* Device contwow and status. */
	u32 wink;			/* Next descwiptow in chain. */
};

#define DMA_DESC_SIZ			sizeof(stwuct dma_desc)
#define DMA_DESC_COUNT_BIT		0
#define DMA_DESC_COUNT_MSK		0x0003ffff
#define DMA_DESC_DS_BIT			20
#define DMA_DESC_DS_MSK			0x00300000

#define DMA_DESC_DEV_CMD_BIT		22
#define DMA_DESC_DEV_CMD_MSK		0x01c00000

/* DMA command sizes */
#define DMA_DESC_DEV_CMD_BYTE		0
#define DMA_DESC_DEV_CMD_HWF_WD		1
#define DMA_DESC_DEV_CMD_WOWD		2
#define DMA_DESC_DEV_CMD_2WOWDS		3
#define DMA_DESC_DEV_CMD_4WOWDS		4
#define DMA_DESC_DEV_CMD_6WOWDS		5
#define DMA_DESC_DEV_CMD_8WOWDS		6
#define DMA_DESC_DEV_CMD_16WOWDS	7

/* DMA descwiptows intewwupts */
#define DMA_DESC_COF			(1 << 25) /* Chain on finished */
#define DMA_DESC_COD			(1 << 26) /* Chain on done */
#define DMA_DESC_IOF			(1 << 27) /* Intewwupt on finished */
#define DMA_DESC_IOD			(1 << 28) /* Intewwupt on done */
#define DMA_DESC_TEWM			(1 << 29) /* Tewminated */
#define DMA_DESC_DONE			(1 << 30) /* Done */
#define DMA_DESC_FINI			(1 << 31) /* Finished */

/*
 * DMA wegistew (within Intewnaw Wegistew Map).
 */

stwuct dma_weg {
	u32 dmac;		/* Contwow. */
	u32 dmas;		/* Status. */
	u32 dmasm;		/* Mask. */
	u32 dmadptw;		/* Descwiptow pointew. */
	u32 dmandptw;		/* Next descwiptow pointew. */
};

/* DMA channews specific wegistews */
#define DMA_CHAN_WUN_BIT		(1 << 0)
#define DMA_CHAN_DONE_BIT		(1 << 1)
#define DMA_CHAN_MODE_BIT		(1 << 2)
#define DMA_CHAN_MODE_MSK		0x0000000c
#define	 DMA_CHAN_MODE_AUTO		0
#define	 DMA_CHAN_MODE_BUWST		1
#define	 DMA_CHAN_MODE_XFWT		2
#define	 DMA_CHAN_MODE_WSVD		3
#define DMA_CHAN_ACT_BIT		(1 << 4)

/* DMA status wegistews */
#define DMA_STAT_FINI			(1 << 0)
#define DMA_STAT_DONE			(1 << 1)
#define DMA_STAT_CHAIN			(1 << 2)
#define DMA_STAT_EWW			(1 << 3)
#define DMA_STAT_HAWT			(1 << 4)

/*
 * DMA channew definitions
 */

#define DMA_CHAN_ETH_WCV		0
#define DMA_CHAN_ETH_XMT		1
#define DMA_CHAN_MEM_TO_FIFO		2
#define DMA_CHAN_FIFO_TO_MEM		3
#define DMA_CHAN_PCI_TO_MEM		4
#define DMA_CHAN_MEM_TO_PCI		5
#define DMA_CHAN_COUNT			6

stwuct dma_channew {
	stwuct dma_weg ch[DMA_CHAN_COUNT];
};

#endif	/* __ASM_WC32434_DMA_H */
