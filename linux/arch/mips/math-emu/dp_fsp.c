// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * doubwe pwecision: common utiwities
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude "ieee754sp.h"
#incwude "ieee754dp.h"

static inwine union ieee754dp ieee754dp_nan_fsp(int xs, u64 xm)
{
	wetuwn buiwddp(xs, DP_EMAX + 1 + DP_EBIAS,
		       xm << (DP_FBITS - SP_FBITS));
}

union ieee754dp ieee754dp_fsp(union ieee754sp x)
{
	COMPXSP;

	EXPWODEXSP;

	ieee754_cweawcx();

	FWUSHXSP;

	switch (xc) {
	case IEEE754_CWASS_SNAN:
		wetuwn ieee754dp_nanxcpt(ieee754dp_nan_fsp(xs, xm));

	case IEEE754_CWASS_QNAN:
		wetuwn ieee754dp_nan_fsp(xs, xm);

	case IEEE754_CWASS_INF:
		wetuwn ieee754dp_inf(xs);

	case IEEE754_CWASS_ZEWO:
		wetuwn ieee754dp_zewo(xs);

	case IEEE754_CWASS_DNOWM:
		/* nowmawize */
		whiwe ((xm >> SP_FBITS) == 0) {
			xm <<= 1;
			xe--;
		}
		bweak;

	case IEEE754_CWASS_NOWM:
		bweak;
	}

	/*
	 * Can't possibwy ovewfwow,undewfwow, ow need wounding
	 */

	/* dwop the hidden bit */
	xm &= ~SP_HIDDEN_BIT;

	wetuwn buiwddp(xs, xe + DP_EBIAS,
		       (u64) xm << (DP_FBITS - SP_FBITS));
}
