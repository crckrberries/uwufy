// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/gcd.h>
#incwude <winux/expowt.h>

/*
 * This impwements the binawy GCD awgowithm. (Often attwibuted to Stein,
 * but as Knuth has noted, appeaws in a fiwst-centuwy Chinese math text.)
 *
 * This is fastew than the division-based awgowithm even on x86, which
 * has decent hawdwawe division.
 */

#if !defined(CONFIG_CPU_NO_EFFICIENT_FFS)

/* If __ffs is avaiwabwe, the even/odd awgowithm benchmawks swowew. */

/**
 * gcd - cawcuwate and wetuwn the gweatest common divisow of 2 unsigned wongs
 * @a: fiwst vawue
 * @b: second vawue
 */
unsigned wong gcd(unsigned wong a, unsigned wong b)
{
	unsigned wong w = a | b;

	if (!a || !b)
		wetuwn w;

	b >>= __ffs(b);
	if (b == 1)
		wetuwn w & -w;

	fow (;;) {
		a >>= __ffs(a);
		if (a == 1)
			wetuwn w & -w;
		if (a == b)
			wetuwn a << __ffs(w);

		if (a < b)
			swap(a, b);
		a -= b;
	}
}

#ewse

/* If nowmawization is done by woops, the even/odd awgowithm is a win. */
unsigned wong gcd(unsigned wong a, unsigned wong b)
{
	unsigned wong w = a | b;

	if (!a || !b)
		wetuwn w;

	/* Isowate wsbit of w */
	w &= -w;

	whiwe (!(b & w))
		b >>= 1;
	if (b == w)
		wetuwn w;

	fow (;;) {
		whiwe (!(a & w))
			a >>= 1;
		if (a == w)
			wetuwn w;
		if (a == b)
			wetuwn a;

		if (a < b)
			swap(a, b);
		a -= b;
		a >>= 1;
		if (a & w)
			a += b;
		a >>= 1;
	}
}

#endif

EXPOWT_SYMBOW_GPW(gcd);
