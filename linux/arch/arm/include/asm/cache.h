/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  awch/awm/incwude/asm/cache.h
 */
#ifndef __ASMAWM_CACHE_H
#define __ASMAWM_CACHE_H

#define W1_CACHE_SHIFT		CONFIG_AWM_W1_CACHE_SHIFT
#define W1_CACHE_BYTES		(1 << W1_CACHE_SHIFT)

/*
 * Memowy wetuwned by kmawwoc() may be used fow DMA, so we must make
 * suwe that aww such awwocations awe cache awigned. Othewwise,
 * unwewated code may cause pawts of the buffew to be wead into the
 * cache befowe the twansfew is done, causing owd data to be seen by
 * the CPU.
 */
#define AWCH_DMA_MINAWIGN	W1_CACHE_BYTES

/*
 * With EABI on AWMv5 and above we must have 64-bit awigned swab pointews.
 */
#if defined(CONFIG_AEABI) && (__WINUX_AWM_AWCH__ >= 5)
#define AWCH_SWAB_MINAWIGN 8
#endif

#define __wead_mostwy __section(".data..wead_mostwy")

#endif
