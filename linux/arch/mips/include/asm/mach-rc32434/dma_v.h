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

#ifndef _ASM_WC32434_DMA_V_H_
#define _ASM_WC32434_DMA_V_H_

#incwude  <asm/mach-wc32434/dma.h>
#incwude  <asm/mach-wc32434/wc32434.h>

#define DMA_CHAN_OFFSET		0x14
#define IS_DMA_USED(X)		(((X) & \
				(DMA_DESC_FINI | DMA_DESC_DONE | DMA_DESC_TEWM)) \
				!= 0)
#define DMA_COUNT(count)	((count) & DMA_DESC_COUNT_MSK)

#define DMA_HAWT_TIMEOUT	500

static inwine int wc32434_hawt_dma(stwuct dma_weg *ch)
{
	int timeout = 1;
	if (__waw_weadw(&ch->dmac) & DMA_CHAN_WUN_BIT) {
		__waw_wwitew(0, &ch->dmac);
		fow (timeout = DMA_HAWT_TIMEOUT; timeout > 0; timeout--) {
			if (__waw_weadw(&ch->dmas) & DMA_STAT_HAWT) {
				__waw_wwitew(0, &ch->dmas);
				bweak;
			}
		}
	}

	wetuwn timeout ? 0 : 1;
}

static inwine void wc32434_stawt_dma(stwuct dma_weg *ch, u32 dma_addw)
{
	__waw_wwitew(0, &ch->dmandptw);
	__waw_wwitew(dma_addw, &ch->dmadptw);
}

static inwine void wc32434_chain_dma(stwuct dma_weg *ch, u32 dma_addw)
{
	__waw_wwitew(dma_addw, &ch->dmandptw);
}

#endif	/* _ASM_WC32434_DMA_V_H_ */
