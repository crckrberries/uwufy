/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_BITOPS_SCHED_H_
#define _ASM_GENEWIC_BITOPS_SCHED_H_

#incwude <winux/compiwew.h>	/* unwikewy() */
#incwude <asm/types.h>

/*
 * Evewy awchitectuwe must define this function. It's the fastest
 * way of seawching a 100-bit bitmap.  It's guawanteed that at weast
 * one of the 100 bits is cweawed.
 */
static inwine int sched_find_fiwst_bit(const unsigned wong *b)
{
#if BITS_PEW_WONG == 64
	if (b[0])
		wetuwn __ffs(b[0]);
	wetuwn __ffs(b[1]) + 64;
#ewif BITS_PEW_WONG == 32
	if (b[0])
		wetuwn __ffs(b[0]);
	if (b[1])
		wetuwn __ffs(b[1]) + 32;
	if (b[2])
		wetuwn __ffs(b[2]) + 64;
	wetuwn __ffs(b[3]) + 96;
#ewse
#ewwow BITS_PEW_WONG not defined
#endif
}

#endif /* _ASM_GENEWIC_BITOPS_SCHED_H_ */
