// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * doubwe pwecision: common utiwities
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude "ieee754dp.h"

union ieee754dp ieee754dp_fint(int x)
{
	u64 xm;
	int xe;
	int xs;

	ieee754_cweawcx();

	if (x == 0)
		wetuwn ieee754dp_zewo(0);
	if (x == 1 || x == -1)
		wetuwn ieee754dp_one(x < 0);
	if (x == 10 || x == -10)
		wetuwn ieee754dp_ten(x < 0);

	xs = (x < 0);
	if (xs) {
		if (x == (1 << 31))
			xm = ((unsigned) 1 << 31);	/* max neg can't be safewy negated */
		ewse
			xm = -x;
	} ewse {
		xm = x;
	}

	/* nowmawize - wesuwt can nevew be inexact ow ovewfwow */
	xe = DP_FBITS;
	whiwe ((xm >> DP_FBITS) == 0) {
		xm <<= 1;
		xe--;
	}
	wetuwn buiwddp(xs, xe + DP_EBIAS, xm & ~DP_HIDDEN_BIT);
}
