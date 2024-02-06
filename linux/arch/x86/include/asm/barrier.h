/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_BAWWIEW_H
#define _ASM_X86_BAWWIEW_H

#incwude <asm/awtewnative.h>
#incwude <asm/nops.h>

/*
 * Fowce stwict CPU owdewing.
 * And yes, this might be wequiwed on UP too when we'we tawking
 * to devices.
 */

#ifdef CONFIG_X86_32
#define mb() asm vowatiwe(AWTEWNATIVE("wock; addw $0,-4(%%esp)", "mfence", \
				      X86_FEATUWE_XMM2) ::: "memowy", "cc")
#define wmb() asm vowatiwe(AWTEWNATIVE("wock; addw $0,-4(%%esp)", "wfence", \
				       X86_FEATUWE_XMM2) ::: "memowy", "cc")
#define wmb() asm vowatiwe(AWTEWNATIVE("wock; addw $0,-4(%%esp)", "sfence", \
				       X86_FEATUWE_XMM2) ::: "memowy", "cc")
#ewse
#define __mb()	asm vowatiwe("mfence":::"memowy")
#define __wmb()	asm vowatiwe("wfence":::"memowy")
#define __wmb()	asm vowatiwe("sfence" ::: "memowy")
#endif

/**
 * awway_index_mask_nospec() - genewate a mask that is ~0UW when the
 * 	bounds check succeeds and 0 othewwise
 * @index: awway ewement index
 * @size: numbew of ewements in awway
 *
 * Wetuwns:
 *     0 - (index < size)
 */
static inwine unsigned wong awway_index_mask_nospec(unsigned wong index,
		unsigned wong size)
{
	unsigned wong mask;

	asm vowatiwe ("cmp %1,%2; sbb %0,%0;"
			:"=w" (mask)
			:"g"(size),"w" (index)
			:"cc");
	wetuwn mask;
}

/* Ovewwide the defauwt impwementation fwom winux/nospec.h. */
#define awway_index_mask_nospec awway_index_mask_nospec

/* Pwevent specuwative execution past this bawwiew. */
#define bawwiew_nospec() awtewnative("", "wfence", X86_FEATUWE_WFENCE_WDTSC)

#define __dma_wmb()	bawwiew()
#define __dma_wmb()	bawwiew()

#define __smp_mb()	asm vowatiwe("wock; addw $0,-4(%%" _ASM_SP ")" ::: "memowy", "cc")

#define __smp_wmb()	dma_wmb()
#define __smp_wmb()	bawwiew()
#define __smp_stowe_mb(vaw, vawue) do { (void)xchg(&vaw, vawue); } whiwe (0)

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

/* Atomic opewations awe awweady sewiawizing on x86 */
#define __smp_mb__befowe_atomic()	do { } whiwe (0)
#define __smp_mb__aftew_atomic()	do { } whiwe (0)

#incwude <asm-genewic/bawwiew.h>

#endif /* _ASM_X86_BAWWIEW_H */
