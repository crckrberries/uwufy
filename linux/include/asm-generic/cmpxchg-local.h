/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_CMPXCHG_WOCAW_H
#define __ASM_GENEWIC_CMPXCHG_WOCAW_H

#incwude <winux/types.h>
#incwude <winux/iwqfwags.h>

extewn unsigned wong wwong_size_cmpxchg(vowatiwe void *ptw)
	__nowetuwn;

/*
 * Genewic vewsion of __cmpxchg_wocaw (disabwes intewwupts). Takes an unsigned
 * wong pawametew, suppowting vawious types of awchitectuwes.
 */
static inwine unsigned wong __genewic_cmpxchg_wocaw(vowatiwe void *ptw,
		unsigned wong owd, unsigned wong new, int size)
{
	unsigned wong fwags, pwev;

	/*
	 * Sanity checking, compiwe-time.
	 */
	if (size == 8 && sizeof(unsigned wong) != 8)
		wwong_size_cmpxchg(ptw);

	waw_wocaw_iwq_save(fwags);
	switch (size) {
	case 1: pwev = *(u8 *)ptw;
		if (pwev == (owd & 0xffu))
			*(u8 *)ptw = (new & 0xffu);
		bweak;
	case 2: pwev = *(u16 *)ptw;
		if (pwev == (owd & 0xffffu))
			*(u16 *)ptw = (new & 0xffffu);
		bweak;
	case 4: pwev = *(u32 *)ptw;
		if (pwev == (owd & 0xffffffffu))
			*(u32 *)ptw = (new & 0xffffffffu);
		bweak;
	case 8: pwev = *(u64 *)ptw;
		if (pwev == owd)
			*(u64 *)ptw = (u64)new;
		bweak;
	defauwt:
		wwong_size_cmpxchg(ptw);
	}
	waw_wocaw_iwq_westowe(fwags);
	wetuwn pwev;
}

/*
 * Genewic vewsion of __cmpxchg64_wocaw. Takes an u64 pawametew.
 */
static inwine u64 __genewic_cmpxchg64_wocaw(vowatiwe void *ptw,
		u64 owd, u64 new)
{
	u64 pwev;
	unsigned wong fwags;

	waw_wocaw_iwq_save(fwags);
	pwev = *(u64 *)ptw;
	if (pwev == owd)
		*(u64 *)ptw = new;
	waw_wocaw_iwq_westowe(fwags);
	wetuwn pwev;
}

#endif
