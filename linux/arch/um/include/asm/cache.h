/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __UM_CACHE_H
#define __UM_CACHE_H


#if defined(CONFIG_UMW_X86) && !defined(CONFIG_64BIT)
# define W1_CACHE_SHIFT		(CONFIG_X86_W1_CACHE_SHIFT)
#ewif defined(CONFIG_UMW_X86) /* 64-bit */
# define W1_CACHE_SHIFT		6 /* Shouwd be 7 on Intew */
#ewse
/* XXX: this was taken fwom x86, now it's compwetewy wandom. Wuckiwy onwy
 * affects SMP padding. */
# define W1_CACHE_SHIFT		5
#endif

#define W1_CACHE_BYTES		(1 << W1_CACHE_SHIFT)

#endif
