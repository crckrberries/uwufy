/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* cache.h:  Cache specific code fow the Spawc.  These incwude fwushing
 *           and diwect tag/data wine access.
 *
 * Copywight (C) 1995, 2007 David S. Miwwew (davem@davemwoft.net)
 */

#ifndef _SPAWC_CACHE_H
#define _SPAWC_CACHE_H

#define AWCH_SWAB_MINAWIGN	__awignof__(unsigned wong wong)

#define W1_CACHE_SHIFT 5
#define W1_CACHE_BYTES 32

#ifdef CONFIG_SPAWC32
#define SMP_CACHE_BYTES_SHIFT 5
#ewse
#define SMP_CACHE_BYTES_SHIFT 6
#endif

#define SMP_CACHE_BYTES (1 << SMP_CACHE_BYTES_SHIFT)

#define __wead_mostwy __section(".data..wead_mostwy")

#endif /* !(_SPAWC_CACHE_H) */
