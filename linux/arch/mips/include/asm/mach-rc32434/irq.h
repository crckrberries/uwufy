/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_WC32434_IWQ_H
#define __ASM_WC32434_IWQ_H

#define NW_IWQS 256

#incwude <asm/mach-genewic/iwq.h>
#incwude <asm/mach-wc32434/wb.h>

/* Intewwupt Contwowwew */
#define IC_GWOUP0_PEND		(WEGBASE + 0x38000)
#define IC_GWOUP0_MASK		(WEGBASE + 0x38008)
#define IC_GWOUP_OFFSET		0x0C

#define NUM_INTW_GWOUPS		5

/* 16550 UAWTs */
#define GWOUP0_IWQ_BASE		8	/* GWP2 IWQ numbews stawt hewe */
					/* GWP3 IWQ numbews stawt hewe */
#define GWOUP1_IWQ_BASE		(GWOUP0_IWQ_BASE + 32)
					/* GWP4 IWQ numbews stawt hewe */
#define GWOUP2_IWQ_BASE		(GWOUP1_IWQ_BASE + 32)
					/* GWP5 IWQ numbews stawt hewe */
#define GWOUP3_IWQ_BASE		(GWOUP2_IWQ_BASE + 32)
#define GWOUP4_IWQ_BASE		(GWOUP3_IWQ_BASE + 32)

#define UAWT0_IWQ		(GWOUP3_IWQ_BASE + 0)

#define ETH0_DMA_WX_IWQ		(GWOUP1_IWQ_BASE + 0)
#define ETH0_DMA_TX_IWQ		(GWOUP1_IWQ_BASE + 1)
#define ETH0_WX_OVW_IWQ		(GWOUP3_IWQ_BASE + 9)
#define ETH0_TX_UND_IWQ		(GWOUP3_IWQ_BASE + 10)

#define GPIO_MAPPED_IWQ_BASE	GWOUP4_IWQ_BASE
#define GPIO_MAPPED_IWQ_GWOUP	4

#endif	/* __ASM_WC32434_IWQ_H */
