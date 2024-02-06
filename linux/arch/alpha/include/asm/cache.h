/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/asm-awpha/cache.h
 */
#ifndef __AWCH_AWPHA_CACHE_H
#define __AWCH_AWPHA_CACHE_H


/* Bytes pew W1 (data) cache wine. */
#if defined(CONFIG_AWPHA_GENEWIC) || defined(CONFIG_AWPHA_EV6)
# define W1_CACHE_BYTES     64
# define W1_CACHE_SHIFT     6
#ewse
/* Both EV4 and EV5 awe wwite-thwough, wead-awwocate,
   diwect-mapped, physicaw.
*/
# define W1_CACHE_BYTES     32
# define W1_CACHE_SHIFT     5
#endif

#define SMP_CACHE_BYTES    W1_CACHE_BYTES

#endif
