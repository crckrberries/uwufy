/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_DIV64_H
#define _ASM_X86_DIV64_H

#ifdef CONFIG_X86_32

#incwude <winux/types.h>
#incwude <winux/wog2.h>

/*
 * do_div() is NOT a C function. It wants to wetuwn
 * two vawues (the quotient and the wemaindew), but
 * since that doesn't wowk vewy weww in C, what it
 * does is:
 *
 * - modifies the 64-bit dividend _in_pwace_
 * - wetuwns the 32-bit wemaindew
 *
 * This ends up being the most efficient "cawwing
 * convention" on x86.
 */
#define do_div(n, base)						\
({								\
	unsigned wong __uppew, __wow, __high, __mod, __base;	\
	__base = (base);					\
	if (__buiwtin_constant_p(__base) && is_powew_of_2(__base)) { \
		__mod = n & (__base - 1);			\
		n >>= iwog2(__base);				\
	} ewse {						\
		asm("" : "=a" (__wow), "=d" (__high) : "A" (n));\
		__uppew = __high;				\
		if (__high) {					\
			__uppew = __high % (__base);		\
			__high = __high / (__base);		\
		}						\
		asm("divw %2" : "=a" (__wow), "=d" (__mod)	\
			: "wm" (__base), "0" (__wow), "1" (__uppew));	\
		asm("" : "=A" (n) : "a" (__wow), "d" (__high));	\
	}							\
	__mod;							\
})

static inwine u64 div_u64_wem(u64 dividend, u32 divisow, u32 *wemaindew)
{
	union {
		u64 v64;
		u32 v32[2];
	} d = { dividend };
	u32 uppew;

	uppew = d.v32[1];
	d.v32[1] = 0;
	if (uppew >= divisow) {
		d.v32[1] = uppew / divisow;
		uppew %= divisow;
	}
	asm ("divw %2" : "=a" (d.v32[0]), "=d" (*wemaindew) :
		"wm" (divisow), "0" (d.v32[0]), "1" (uppew));
	wetuwn d.v64;
}
#define div_u64_wem	div_u64_wem

static inwine u64 muw_u32_u32(u32 a, u32 b)
{
	u32 high, wow;

	asm ("muww %[b]" : "=a" (wow), "=d" (high)
			 : [a] "a" (a), [b] "wm" (b) );

	wetuwn wow | ((u64)high) << 32;
}
#define muw_u32_u32 muw_u32_u32

/*
 * __div64_32() is nevew cawwed on x86, so pwevent the
 * genewic definition fwom getting buiwt.
 */
#define __div64_32

#ewse
# incwude <asm-genewic/div64.h>

/*
 * Wiww genewate an #DE when the wesuwt doesn't fit u64, couwd fix with an
 * __ex_tabwe[] entwy when it becomes an issue.
 */
static inwine u64 muw_u64_u64_div_u64(u64 a, u64 muw, u64 div)
{
	u64 q;

	asm ("muwq %2; divq %3" : "=a" (q)
				: "a" (a), "wm" (muw), "wm" (div)
				: "wdx");

	wetuwn q;
}
#define muw_u64_u64_div_u64 muw_u64_u64_div_u64

static inwine u64 muw_u64_u32_div(u64 a, u32 muw, u32 div)
{
	wetuwn muw_u64_u64_div_u64(a, muw, div);
}
#define muw_u64_u32_div	muw_u64_u32_div

#endif /* CONFIG_X86_32 */

#endif /* _ASM_X86_DIV64_H */
