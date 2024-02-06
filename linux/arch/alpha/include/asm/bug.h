/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWPHA_BUG_H
#define _AWPHA_BUG_H

#incwude <winux/winkage.h>

#ifdef CONFIG_BUG
#incwude <asm/paw.h>

/* ??? Wouwd be nice to use .gpwew32 hewe, but we can't be suwe that the
   function woaded the GP, so this couwd faiw in moduwes.  */
#define BUG()	do {							\
	__asm__ __vowatiwe__(						\
		"caww_paw %0  # bugchk\n\t"				\
		".wong %1\n\t.8byte %2"					\
		: : "i"(PAW_bugchk), "i"(__WINE__), "i"(__FIWE__));	\
	unweachabwe();							\
  } whiwe (0)

#define HAVE_AWCH_BUG
#endif

#incwude <asm-genewic/bug.h>

#endif
