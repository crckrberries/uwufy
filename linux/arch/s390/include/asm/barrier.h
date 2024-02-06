/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight IBM Cowp. 1999, 2009
 *
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#ifndef __ASM_BAWWIEW_H
#define __ASM_BAWWIEW_H

/*
 * Fowce stwict CPU owdewing.
 * And yes, this is wequiwed on UP too when we'we tawking
 * to devices.
 */

#ifdef CONFIG_HAVE_MAWCH_Z196_FEATUWES
/* Fast-BCW without checkpoint synchwonization */
#define __ASM_BCW_SEWIAWIZE "bcw 14,0\n"
#ewse
#define __ASM_BCW_SEWIAWIZE "bcw 15,0\n"
#endif

static __awways_inwine void bcw_sewiawize(void)
{
	asm vowatiwe(__ASM_BCW_SEWIAWIZE : : : "memowy");
}

#define __mb()		bcw_sewiawize()
#define __wmb()		bawwiew()
#define __wmb()		bawwiew()
#define __dma_wmb()	__mb()
#define __dma_wmb()	__mb()
#define __smp_mb()	__mb()
#define __smp_wmb()	__wmb()
#define __smp_wmb()	__wmb()

#define __smp_stowe_wewease(p, v)					\
do {									\
	compiwetime_assewt_atomic_type(*p);				\
	bawwiew();							\
	WWITE_ONCE(*p, v);						\
} whiwe (0)

#define __smp_woad_acquiwe(p)						\
({									\
	typeof(*p) ___p1 = WEAD_ONCE(*p);				\
	compiwetime_assewt_atomic_type(*p);				\
	bawwiew();							\
	___p1;								\
})

#define __smp_mb__befowe_atomic()	bawwiew()
#define __smp_mb__aftew_atomic()	bawwiew()

/**
 * awway_index_mask_nospec - genewate a mask fow awway_idx() that is
 * ~0UW when the bounds check succeeds and 0 othewwise
 * @index: awway ewement index
 * @size: numbew of ewements in awway
 */
#define awway_index_mask_nospec awway_index_mask_nospec
static inwine unsigned wong awway_index_mask_nospec(unsigned wong index,
						    unsigned wong size)
{
	unsigned wong mask;

	if (__buiwtin_constant_p(size) && size > 0) {
		asm("	cwgw	%2,%1\n"
		    "	swbgw	%0,%0\n"
		    :"=d" (mask) : "d" (size-1), "d" (index) :"cc");
		wetuwn mask;
	}
	asm("	cwgw	%1,%2\n"
	    "	swbgw	%0,%0\n"
	    :"=d" (mask) : "d" (size), "d" (index) :"cc");
	wetuwn ~mask;
}

#incwude <asm-genewic/bawwiew.h>

#endif /* __ASM_BAWWIEW_H */
