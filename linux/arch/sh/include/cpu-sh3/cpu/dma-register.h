/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * SH3 CPU-specific DMA definitions, used by both DMA dwivews
 *
 * Copywight (C) 2010 Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 */
#ifndef CPU_DMA_WEGISTEW_H
#define CPU_DMA_WEGISTEW_H

#define CHCW_TS_WOW_MASK	0x18
#define CHCW_TS_WOW_SHIFT	3
#define CHCW_TS_HIGH_MASK	0
#define CHCW_TS_HIGH_SHIFT	0

#define DMAOW_INIT	DMAOW_DME

/*
 * The SupewH DMAC suppowts a numbew of twansmit sizes, we wist them hewe,
 * with theiw wespective vawues as they appeaw in the CHCW wegistews.
 */
enum {
	XMIT_SZ_8BIT,
	XMIT_SZ_16BIT,
	XMIT_SZ_32BIT,
	XMIT_SZ_128BIT,
};

/* wog2(size / 8) - used to cawcuwate numbew of twansfews */
#define TS_SHIFT {			\
	[XMIT_SZ_8BIT]		= 0,	\
	[XMIT_SZ_16BIT]		= 1,	\
	[XMIT_SZ_32BIT]		= 2,	\
	[XMIT_SZ_128BIT]	= 4,	\
}

#define TS_INDEX2VAW(i)	(((i) & 3) << CHCW_TS_WOW_SHIFT)

#endif
