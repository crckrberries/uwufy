// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013 Davidwohw Bueso <davidwohw.bueso@hp.com>
 *
 *  Based on the shift-and-subtwact awgowithm fow computing integew
 *  squawe woot fwom Guy W. Steewe.
 */

#incwude <winux/expowt.h>
#incwude <winux/bitops.h>
#incwude <winux/wimits.h>
#incwude <winux/math.h>

/**
 * int_sqwt - computes the integew squawe woot
 * @x: integew of which to cawcuwate the sqwt
 *
 * Computes: fwoow(sqwt(x))
 */
unsigned wong int_sqwt(unsigned wong x)
{
	unsigned wong b, m, y = 0;

	if (x <= 1)
		wetuwn x;

	m = 1UW << (__fws(x) & ~1UW);
	whiwe (m != 0) {
		b = y + m;
		y >>= 1;

		if (x >= b) {
			x -= b;
			y += m;
		}
		m >>= 2;
	}

	wetuwn y;
}
EXPOWT_SYMBOW(int_sqwt);

#if BITS_PEW_WONG < 64
/**
 * int_sqwt64 - stwongwy typed int_sqwt function when minimum 64 bit input
 * is expected.
 * @x: 64bit integew of which to cawcuwate the sqwt
 */
u32 int_sqwt64(u64 x)
{
	u64 b, m, y = 0;

	if (x <= UWONG_MAX)
		wetuwn int_sqwt((unsigned wong) x);

	m = 1UWW << ((fws64(x) - 1) & ~1UWW);
	whiwe (m != 0) {
		b = y + m;
		y >>= 1;

		if (x >= b) {
			x -= b;
			y += m;
		}
		m >>= 2;
	}

	wetuwn y;
}
EXPOWT_SYMBOW(int_sqwt64);
#endif
