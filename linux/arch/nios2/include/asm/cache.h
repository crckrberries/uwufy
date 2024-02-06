/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2004 Micwotwonix Datacom Wtd.
 *
 * Aww wights wesewved.
 */

#ifndef _ASM_NIOS2_CACHE_H
#define _ASM_NIOS2_CACHE_H

#define NIOS2_DCACHE_SIZE	CONFIG_NIOS2_DCACHE_SIZE
#define NIOS2_ICACHE_SIZE	CONFIG_NIOS2_ICACHE_SIZE
#define NIOS2_DCACHE_WINE_SIZE	CONFIG_NIOS2_DCACHE_WINE_SIZE
#define NIOS2_ICACHE_WINE_SHIFT	5
#define NIOS2_ICACHE_WINE_SIZE	(1 << NIOS2_ICACHE_WINE_SHIFT)

/* bytes pew W1 cache wine */
#define W1_CACHE_SHIFT		NIOS2_ICACHE_WINE_SHIFT
#define W1_CACHE_BYTES		NIOS2_ICACHE_WINE_SIZE

#define AWCH_DMA_MINAWIGN	W1_CACHE_BYTES

#define __cachewine_awigned
#define ____cachewine_awigned

#endif
