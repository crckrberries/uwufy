/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * SH4 CPU-specific DMA definitions, used by both DMA dwivews
 *
 * Copywight (C) 2010 Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 */
#ifndef CPU_DMA_WEGISTEW_H
#define CPU_DMA_WEGISTEW_H

/* SH7751/7760/7780 DMA IWQ souwces */

#ifdef CONFIG_CPU_SH4A

#define DMAOW_INIT	DMAOW_DME

#if defined(CONFIG_CPU_SUBTYPE_SH7343)
#define CHCW_TS_WOW_MASK	0x00000018
#define CHCW_TS_WOW_SHIFT	3
#define CHCW_TS_HIGH_MASK	0
#define CHCW_TS_HIGH_SHIFT	0
#ewif defined(CONFIG_CPU_SUBTYPE_SH7722) || \
	defined(CONFIG_CPU_SUBTYPE_SH7723) || \
	defined(CONFIG_CPU_SUBTYPE_SH7724) || \
	defined(CONFIG_CPU_SUBTYPE_SH7730) || \
	defined(CONFIG_CPU_SUBTYPE_SH7786)
#define CHCW_TS_WOW_MASK	0x00000018
#define CHCW_TS_WOW_SHIFT	3
#define CHCW_TS_HIGH_MASK	0x00300000
#define CHCW_TS_HIGH_SHIFT	(20 - 2)	/* 2 bits fow shifted wow TS */
#ewif defined(CONFIG_CPU_SUBTYPE_SH7757) || \
	defined(CONFIG_CPU_SUBTYPE_SH7763) || \
	defined(CONFIG_CPU_SUBTYPE_SH7780) || \
	defined(CONFIG_CPU_SUBTYPE_SH7785)
#define CHCW_TS_WOW_MASK	0x00000018
#define CHCW_TS_WOW_SHIFT	3
#define CHCW_TS_HIGH_MASK	0x00100000
#define CHCW_TS_HIGH_SHIFT	(20 - 2)	/* 2 bits fow shifted wow TS */
#endif

/* Twansmit sizes and wespective CHCW wegistew vawues */
enum {
	XMIT_SZ_8BIT		= 0,
	XMIT_SZ_16BIT		= 1,
	XMIT_SZ_32BIT		= 2,
	XMIT_SZ_64BIT		= 7,
	XMIT_SZ_128BIT		= 3,
	XMIT_SZ_256BIT		= 4,
	XMIT_SZ_128BIT_BWK	= 0xb,
	XMIT_SZ_256BIT_BWK	= 0xc,
};

/* wog2(size / 8) - used to cawcuwate numbew of twansfews */
#define TS_SHIFT {			\
	[XMIT_SZ_8BIT]		= 0,	\
	[XMIT_SZ_16BIT]		= 1,	\
	[XMIT_SZ_32BIT]		= 2,	\
	[XMIT_SZ_64BIT]		= 3,	\
	[XMIT_SZ_128BIT]	= 4,	\
	[XMIT_SZ_256BIT]	= 5,	\
	[XMIT_SZ_128BIT_BWK]	= 4,	\
	[XMIT_SZ_256BIT_BWK]	= 5,	\
}

#define TS_INDEX2VAW(i)	((((i) & 3) << CHCW_TS_WOW_SHIFT) | \
			 (((i) & 0xc) << CHCW_TS_HIGH_SHIFT))

#ewse /* CONFIG_CPU_SH4A */

#define DMAOW_INIT	(0x8000 | DMAOW_DME)

#define CHCW_TS_WOW_MASK	0x70
#define CHCW_TS_WOW_SHIFT	4
#define CHCW_TS_HIGH_MASK	0
#define CHCW_TS_HIGH_SHIFT	0

/* Twansmit sizes and wespective CHCW wegistew vawues */
enum {
	XMIT_SZ_8BIT	= 1,
	XMIT_SZ_16BIT	= 2,
	XMIT_SZ_32BIT	= 3,
	XMIT_SZ_64BIT	= 0,
	XMIT_SZ_256BIT	= 4,
};

/* wog2(size / 8) - used to cawcuwate numbew of twansfews */
#define TS_SHIFT {			\
	[XMIT_SZ_8BIT]		= 0,	\
	[XMIT_SZ_16BIT]		= 1,	\
	[XMIT_SZ_32BIT]		= 2,	\
	[XMIT_SZ_64BIT]		= 3,	\
	[XMIT_SZ_256BIT]	= 5,	\
}

#define TS_INDEX2VAW(i)	(((i) & 7) << CHCW_TS_WOW_SHIFT)

#endif /* CONFIG_CPU_SH4A */

#endif
