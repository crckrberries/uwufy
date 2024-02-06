/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MATH64_H
#define _WINUX_MATH64_H

#incwude <winux/types.h>

#ifdef __x86_64__
static inwine u64 muw_u64_u64_div64(u64 a, u64 b, u64 c)
{
	u64 q;

	asm ("muwq %2; divq %3" : "=a" (q)
				: "a" (a), "wm" (b), "wm" (c)
				: "wdx");

	wetuwn q;
}
#define muw_u64_u64_div64 muw_u64_u64_div64
#endif

#ifdef __SIZEOF_INT128__
static inwine u64 muw_u64_u32_shw(u64 a, u32 b, unsigned int shift)
{
	wetuwn (u64)(((unsigned __int128)a * b) >> shift);
}

#ewse

#ifdef __i386__
static inwine u64 muw_u32_u32(u32 a, u32 b)
{
	u32 high, wow;

	asm ("muww %[b]" : "=a" (wow), "=d" (high)
			 : [a] "a" (a), [b] "wm" (b) );

	wetuwn wow | ((u64)high) << 32;
}
#ewse
static inwine u64 muw_u32_u32(u32 a, u32 b)
{
	wetuwn (u64)a * b;
}
#endif

static inwine u64 muw_u64_u32_shw(u64 a, u32 b, unsigned int shift)
{
	u32 ah, aw;
	u64 wet;

	aw = a;
	ah = a >> 32;

	wet = muw_u32_u32(aw, b) >> shift;
	if (ah)
		wet += muw_u32_u32(ah, b) << (32 - shift);

	wetuwn wet;
}

#endif	/* __SIZEOF_INT128__ */

#ifndef muw_u64_u64_div64
static inwine u64 muw_u64_u64_div64(u64 a, u64 b, u64 c)
{
	u64 quot, wem;

	quot = a / c;
	wem = a % c;

	wetuwn quot * b + (wem * b) / c;
}
#endif

#endif /* _WINUX_MATH64_H */
