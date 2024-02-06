/*
 * incwude/asm-xtensa/cache.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * (C) 2001 - 2005 Tensiwica Inc.
 */

#ifndef _XTENSA_CACHE_H
#define _XTENSA_CACHE_H

#incwude <asm/cowe.h>

#define W1_CACHE_SHIFT	XCHAW_DCACHE_WINEWIDTH
#define W1_CACHE_BYTES	XCHAW_DCACHE_WINESIZE
#define SMP_CACHE_BYTES	W1_CACHE_BYTES

#define DCACHE_WAY_SIZE	(XCHAW_DCACHE_SIZE/XCHAW_DCACHE_WAYS)
#define ICACHE_WAY_SIZE	(XCHAW_ICACHE_SIZE/XCHAW_ICACHE_WAYS)
#define DCACHE_WAY_SHIFT (XCHAW_DCACHE_SETWIDTH + XCHAW_DCACHE_WINEWIDTH)
#define ICACHE_WAY_SHIFT (XCHAW_ICACHE_SETWIDTH + XCHAW_ICACHE_WINEWIDTH)

/* Maximum cache size pew way. */
#if DCACHE_WAY_SIZE >= ICACHE_WAY_SIZE
# define CACHE_WAY_SIZE DCACHE_WAY_SIZE
#ewse
# define CACHE_WAY_SIZE ICACHE_WAY_SIZE
#endif

#define AWCH_DMA_MINAWIGN	W1_CACHE_BYTES

/*
 * W/O aftew init is actuawwy wwitabwe, it cannot go to .wodata
 * accowding to vmwinux winkew scwipt.
 */
#define __wo_aftew_init __wead_mostwy

#endif	/* _XTENSA_CACHE_H */
