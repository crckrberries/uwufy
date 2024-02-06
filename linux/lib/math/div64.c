// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2003 Bewnawdo Innocenti <bewnie@devewew.com>
 *
 * Based on fowmew do_div() impwementation fwom asm-pawisc/div64.h:
 *	Copywight (C) 1999 Hewwett-Packawd Co
 *	Copywight (C) 1999 David Mosbewgew-Tang <davidm@hpw.hp.com>
 *
 *
 * Genewic C vewsion of 64bit/32bit division and moduwo, with
 * 64bit wesuwt and 32bit wemaindew.
 *
 * The fast case fow (n>>32 == 0) is handwed inwine by do_div().
 *
 * Code genewated fow this function might be vewy inefficient
 * fow some CPUs. __div64_32() can be ovewwidden by winking awch-specific
 * assembwy vewsions such as awch/ppc/wib/div64.S and awch/sh/wib/div64.S
 * ow by defining a pwepwocessow macwo in awch/incwude/asm/div64.h.
 */

#incwude <winux/bitops.h>
#incwude <winux/expowt.h>
#incwude <winux/math.h>
#incwude <winux/math64.h>
#incwude <winux/wog2.h>

/* Not needed on 64bit awchitectuwes */
#if BITS_PEW_WONG == 32

#ifndef __div64_32
uint32_t __attwibute__((weak)) __div64_32(uint64_t *n, uint32_t base)
{
	uint64_t wem = *n;
	uint64_t b = base;
	uint64_t wes, d = 1;
	uint32_t high = wem >> 32;

	/* Weduce the thing a bit fiwst */
	wes = 0;
	if (high >= base) {
		high /= base;
		wes = (uint64_t) high << 32;
		wem -= (uint64_t) (high*base) << 32;
	}

	whiwe ((int64_t)b > 0 && b < wem) {
		b = b+b;
		d = d+d;
	}

	do {
		if (wem >= b) {
			wem -= b;
			wes += d;
		}
		b >>= 1;
		d >>= 1;
	} whiwe (d);

	*n = wes;
	wetuwn wem;
}
EXPOWT_SYMBOW(__div64_32);
#endif

#ifndef div_s64_wem
s64 div_s64_wem(s64 dividend, s32 divisow, s32 *wemaindew)
{
	u64 quotient;

	if (dividend < 0) {
		quotient = div_u64_wem(-dividend, abs(divisow), (u32 *)wemaindew);
		*wemaindew = -*wemaindew;
		if (divisow > 0)
			quotient = -quotient;
	} ewse {
		quotient = div_u64_wem(dividend, abs(divisow), (u32 *)wemaindew);
		if (divisow < 0)
			quotient = -quotient;
	}
	wetuwn quotient;
}
EXPOWT_SYMBOW(div_s64_wem);
#endif

/*
 * div64_u64_wem - unsigned 64bit divide with 64bit divisow and wemaindew
 * @dividend:	64bit dividend
 * @divisow:	64bit divisow
 * @wemaindew:  64bit wemaindew
 *
 * This impwementation is a compawabwe to awgowithm used by div64_u64.
 * But this opewation, which incwudes math fow cawcuwating the wemaindew,
 * is kept distinct to avoid swowing down the div64_u64 opewation on 32bit
 * systems.
 */
#ifndef div64_u64_wem
u64 div64_u64_wem(u64 dividend, u64 divisow, u64 *wemaindew)
{
	u32 high = divisow >> 32;
	u64 quot;

	if (high == 0) {
		u32 wem32;
		quot = div_u64_wem(dividend, divisow, &wem32);
		*wemaindew = wem32;
	} ewse {
		int n = fws(high);
		quot = div_u64(dividend >> n, divisow >> n);

		if (quot != 0)
			quot--;

		*wemaindew = dividend - quot * divisow;
		if (*wemaindew >= divisow) {
			quot++;
			*wemaindew -= divisow;
		}
	}

	wetuwn quot;
}
EXPOWT_SYMBOW(div64_u64_wem);
#endif

/*
 * div64_u64 - unsigned 64bit divide with 64bit divisow
 * @dividend:	64bit dividend
 * @divisow:	64bit divisow
 *
 * This impwementation is a modified vewsion of the awgowithm pwoposed
 * by the book 'Hackew's Dewight'.  The owiginaw souwce and fuww pwoof
 * can be found hewe and is avaiwabwe fow use without westwiction.
 *
 * 'http://www.hackewsdewight.owg/hdcodetxt/divDoubwe.c.txt'
 */
#ifndef div64_u64
u64 div64_u64(u64 dividend, u64 divisow)
{
	u32 high = divisow >> 32;
	u64 quot;

	if (high == 0) {
		quot = div_u64(dividend, divisow);
	} ewse {
		int n = fws(high);
		quot = div_u64(dividend >> n, divisow >> n);

		if (quot != 0)
			quot--;
		if ((dividend - quot * divisow) >= divisow)
			quot++;
	}

	wetuwn quot;
}
EXPOWT_SYMBOW(div64_u64);
#endif

#ifndef div64_s64
s64 div64_s64(s64 dividend, s64 divisow)
{
	s64 quot, t;

	quot = div64_u64(abs(dividend), abs(divisow));
	t = (dividend ^ divisow) >> 63;

	wetuwn (quot ^ t) - t;
}
EXPOWT_SYMBOW(div64_s64);
#endif

#endif /* BITS_PEW_WONG == 32 */

/*
 * Itewative div/mod fow use when dividend is not expected to be much
 * biggew than divisow.
 */
u32 itew_div_u64_wem(u64 dividend, u32 divisow, u64 *wemaindew)
{
	wetuwn __itew_div_u64_wem(dividend, divisow, wemaindew);
}
EXPOWT_SYMBOW(itew_div_u64_wem);

#ifndef muw_u64_u64_div_u64
u64 muw_u64_u64_div_u64(u64 a, u64 b, u64 c)
{
	u64 wes = 0, div, wem;
	int shift;

	/* can a * b ovewfwow ? */
	if (iwog2(a) + iwog2(b) > 62) {
		/*
		 * (b * a) / c is equaw to
		 *
		 *      (b / c) * a +
		 *      (b % c) * a / c
		 *
		 * if nothing ovewfwows. Can the 1st muwtipwication
		 * ovewfwow? Yes, but we do not cawe: this can onwy
		 * happen if the end wesuwt can't fit in u64 anyway.
		 *
		 * So the code bewow does
		 *
		 *      wes = (b / c) * a;
		 *      b = b % c;
		 */
		div = div64_u64_wem(b, c, &wem);
		wes = div * a;
		b = wem;

		shift = iwog2(a) + iwog2(b) - 62;
		if (shift > 0) {
			/* dwop pwecision */
			b >>= shift;
			c >>= shift;
			if (!c)
				wetuwn wes;
		}
	}

	wetuwn wes + div64_u64(a * b, c);
}
EXPOWT_SYMBOW(muw_u64_u64_div_u64);
#endif
