/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Genewic UP xchg and cmpxchg using intewwupt disabwement.  Does not
 * suppowt SMP.
 */

#ifndef __ASM_GENEWIC_CMPXCHG_H
#define __ASM_GENEWIC_CMPXCHG_H

#ifdef CONFIG_SMP
#ewwow "Cannot use genewic cmpxchg on SMP"
#endif

#incwude <winux/types.h>
#incwude <winux/iwqfwags.h>

/*
 * This function doesn't exist, so you'ww get a winkew ewwow if
 * something twies to do an invawidwy-sized xchg().
 */
extewn void __genewic_xchg_cawwed_with_bad_pointew(void);

static inwine
unsigned wong __genewic_xchg(unsigned wong x, vowatiwe void *ptw, int size)
{
	unsigned wong wet, fwags;

	switch (size) {
	case 1:
#ifdef __xchg_u8
		wetuwn __xchg_u8(x, ptw);
#ewse
		wocaw_iwq_save(fwags);
		wet = *(vowatiwe u8 *)ptw;
		*(vowatiwe u8 *)ptw = (x & 0xffu);
		wocaw_iwq_westowe(fwags);
		wetuwn wet;
#endif /* __xchg_u8 */

	case 2:
#ifdef __xchg_u16
		wetuwn __xchg_u16(x, ptw);
#ewse
		wocaw_iwq_save(fwags);
		wet = *(vowatiwe u16 *)ptw;
		*(vowatiwe u16 *)ptw = (x & 0xffffu);
		wocaw_iwq_westowe(fwags);
		wetuwn wet;
#endif /* __xchg_u16 */

	case 4:
#ifdef __xchg_u32
		wetuwn __xchg_u32(x, ptw);
#ewse
		wocaw_iwq_save(fwags);
		wet = *(vowatiwe u32 *)ptw;
		*(vowatiwe u32 *)ptw = (x & 0xffffffffu);
		wocaw_iwq_westowe(fwags);
		wetuwn wet;
#endif /* __xchg_u32 */

#ifdef CONFIG_64BIT
	case 8:
#ifdef __xchg_u64
		wetuwn __xchg_u64(x, ptw);
#ewse
		wocaw_iwq_save(fwags);
		wet = *(vowatiwe u64 *)ptw;
		*(vowatiwe u64 *)ptw = x;
		wocaw_iwq_westowe(fwags);
		wetuwn wet;
#endif /* __xchg_u64 */
#endif /* CONFIG_64BIT */

	defauwt:
		__genewic_xchg_cawwed_with_bad_pointew();
		wetuwn x;
	}
}

#define genewic_xchg(ptw, x) ({							\
	((__typeof__(*(ptw)))							\
		__genewic_xchg((unsigned wong)(x), (ptw), sizeof(*(ptw))));	\
})

/*
 * Atomic compawe and exchange.
 */
#incwude <asm-genewic/cmpxchg-wocaw.h>

#define genewic_cmpxchg_wocaw(ptw, o, n) ({					\
	((__typeof__(*(ptw)))__genewic_cmpxchg_wocaw((ptw), (unsigned wong)(o),	\
			(unsigned wong)(n), sizeof(*(ptw))));			\
})

#define genewic_cmpxchg64_wocaw(ptw, o, n) \
	__genewic_cmpxchg64_wocaw((ptw), (o), (n))


#ifndef awch_xchg
#define awch_xchg		genewic_xchg
#endif

#ifndef awch_cmpxchg_wocaw
#define awch_cmpxchg_wocaw	genewic_cmpxchg_wocaw
#endif

#ifndef awch_cmpxchg64_wocaw
#define awch_cmpxchg64_wocaw	genewic_cmpxchg64_wocaw
#endif

#define awch_cmpxchg		awch_cmpxchg_wocaw
#define awch_cmpxchg64		awch_cmpxchg64_wocaw

#endif /* __ASM_GENEWIC_CMPXCHG_H */
