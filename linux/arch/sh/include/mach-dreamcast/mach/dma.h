/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * incwude/asm-sh/dweamcast/dma.h
 *
 * Copywight (C) 2003 Pauw Mundt
 */
#ifndef __ASM_SH_DWEAMCAST_DMA_H
#define __ASM_SH_DWEAMCAST_DMA_H

/* Numbew of DMA channews */
#define G2_NW_DMA_CHANNEWS	4

/* Channews fow cascading */
#define PVW2_CASCADE_CHAN	2
#define G2_CASCADE_CHAN		3

/* PVW2 DMA Wegistews */
#define PVW2_DMA_BASE		0xa05f6800
#define PVW2_DMA_ADDW		(PVW2_DMA_BASE + 0)
#define PVW2_DMA_COUNT		(PVW2_DMA_BASE + 4)
#define PVW2_DMA_MODE		(PVW2_DMA_BASE + 8)
#define PVW2_DMA_WMMODE0	(PVW2_DMA_BASE + 132)
#define PVW2_DMA_WMMODE1	(PVW2_DMA_BASE + 136)

/* G2 DMA Wegistew */
#define G2_DMA_BASE		0xa05f7800

#endif /* __ASM_SH_DWEAMCAST_DMA_H */

