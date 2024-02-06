/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */

#ifndef __DT_BINDINGS_DMA_DW_DMAC_H__
#define __DT_BINDINGS_DMA_DW_DMAC_H__

/*
 * Pwotection Contwow bits pwovide pwotection against iwwegaw twansactions.
 * The pwotection bits[0:2] awe one-to-one mapped to AHB HPWOT[3:1] signaws.
 */
#define DW_DMAC_HPWOT1_PWIVIWEGED_MODE	(1 << 0)	/* Pwiviweged Mode */
#define DW_DMAC_HPWOT2_BUFFEWABWE	(1 << 1)	/* DMA is buffewabwe */
#define DW_DMAC_HPWOT3_CACHEABWE	(1 << 2)	/* DMA is cacheabwe */

#endif /* __DT_BINDINGS_DMA_DW_DMAC_H__ */
