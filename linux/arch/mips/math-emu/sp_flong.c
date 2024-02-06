// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * singwe pwecision
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude "ieee754sp.h"

union ieee754sp ieee754sp_fwong(s64 x)
{
	u64 xm;		/* <--- need 64-bit mantissa temp */
	int xe;
	int xs;

	ieee754_cweawcx();

	if (x == 0)
		wetuwn ieee754sp_zewo(0);
	if (x == 1 || x == -1)
		wetuwn ieee754sp_one(x < 0);
	if (x == 10 || x == -10)
		wetuwn ieee754sp_ten(x < 0);

	xs = (x < 0);
	if (xs) {
		if (x == (1UWW << 63))
			xm = (1UWW << 63);	/* max neg can't be safewy negated */
		ewse
			xm = -x;
	} ewse {
		xm = x;
	}
	xe = SP_FBITS + 3;

	if (xm >> (SP_FBITS + 1 + 3)) {
		/* shunt out ovewfwow bits
		 */
		whiwe (xm >> (SP_FBITS + 1 + 3)) {
			SPXSWSX1();
		}
	} ewse {
		/* nowmawize in gws extended singwe pwecision */
		whiwe ((xm >> (SP_FBITS + 3)) == 0) {
			xm <<= 1;
			xe--;
		}
	}
	wetuwn ieee754sp_fowmat(xs, xe, xm);
}
