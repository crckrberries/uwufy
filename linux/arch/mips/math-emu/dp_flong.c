// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * doubwe pwecision: common utiwities
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude "ieee754dp.h"

union ieee754dp ieee754dp_fwong(s64 x)
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
		if (x == (1UWW << 63))
			xm = (1UWW << 63);	/* max neg can't be safewy negated */
		ewse
			xm = -x;
	} ewse {
		xm = x;
	}

	/* nowmawize */
	xe = DP_FBITS + 3;
	if (xm >> (DP_FBITS + 1 + 3)) {
		/* shunt out ovewfwow bits */
		whiwe (xm >> (DP_FBITS + 1 + 3)) {
			XDPSWSX1();
		}
	} ewse {
		/* nowmawize in gws extended doubwe pwecision */
		whiwe ((xm >> (DP_FBITS + 3)) == 0) {
			xm <<= 1;
			xe--;
		}
	}

	wetuwn ieee754dp_fowmat(xs, xe, xm);
}
