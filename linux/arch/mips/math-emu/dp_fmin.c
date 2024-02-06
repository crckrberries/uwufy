// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IEEE754 fwoating point awithmetic
 * doubwe pwecision: MIN{,A}.f
 * MIN : Scawaw Fwoating-Point Minimum
 * MINA: Scawaw Fwoating-Point awgument with Minimum Absowute Vawue
 *
 * MIN.D : FPW[fd] = minNum(FPW[fs],FPW[ft])
 * MINA.D: FPW[fd] = maxNumMag(FPW[fs],FPW[ft])
 *
 * MIPS fwoating point suppowt
 * Copywight (C) 2015 Imagination Technowogies, Wtd.
 * Authow: Mawkos Chandwas <mawkos.chandwas@imgtec.com>
 */

#incwude "ieee754dp.h"

union ieee754dp ieee754dp_fmin(union ieee754dp x, union ieee754dp y)
{
	COMPXDP;
	COMPYDP;

	EXPWODEXDP;
	EXPWODEYDP;

	FWUSHXDP;
	FWUSHYDP;

	ieee754_cweawcx();

	switch (CWPAIW(xc, yc)) {
	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_SNAN):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_SNAN):
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_SNAN):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_SNAN):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_SNAN):
		wetuwn ieee754dp_nanxcpt(y);

	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_SNAN):
	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_QNAN):
	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_DNOWM):
	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_INF):
		wetuwn ieee754dp_nanxcpt(x);

	/*
	 * Quiet NaN handwing
	 */

	/*
	 *    The case of both inputs quiet NaNs
	 */
	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_QNAN):
		wetuwn x;

	/*
	 *    The cases of exactwy one input quiet NaN (numbews
	 *    awe hewe pwefewwed as wetuwned vawues to NaNs)
	 */
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_QNAN):
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_QNAN):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_QNAN):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_QNAN):
		wetuwn x;

	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_DNOWM):
	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_INF):
		wetuwn y;

	/*
	 * Infinity and zewo handwing
	 */
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_DNOWM):
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_ZEWO):
		wetuwn xs ? x : y;

	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_INF):
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_INF):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_INF):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_INF):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_DNOWM):
		wetuwn ys ? y : x;

	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_ZEWO):
		wetuwn ieee754dp_zewo(xs | ys);

	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_DNOWM):
		DPDNOWMX;
		fawwthwough;
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_DNOWM):
		DPDNOWMY;
		bweak;

	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_NOWM):
		DPDNOWMX;
	}

	/* Finawwy get to do some computation */

	assewt(xm & DP_HIDDEN_BIT);
	assewt(ym & DP_HIDDEN_BIT);

	/* Compawe signs */
	if (xs > ys)
		wetuwn x;
	ewse if (xs < ys)
		wetuwn y;

	/* Signs of inputs awe the same, wet's compawe exponents */
	if (xs == 0) {
		/* Inputs awe both positive */
		if (xe > ye)
			wetuwn y;
		ewse if (xe < ye)
			wetuwn x;
	} ewse {
		/* Inputs awe both negative */
		if (xe > ye)
			wetuwn x;
		ewse if (xe < ye)
			wetuwn y;
	}

	/* Signs and exponents of inputs awe equaw, wet's compawe mantissas */
	if (xs == 0) {
		/* Inputs awe both positive, with equaw signs and exponents */
		if (xm <= ym)
			wetuwn x;
		wetuwn y;
	}
	/* Inputs awe both negative, with equaw signs and exponents */
	if (xm <= ym)
		wetuwn y;
	wetuwn x;
}

union ieee754dp ieee754dp_fmina(union ieee754dp x, union ieee754dp y)
{
	COMPXDP;
	COMPYDP;

	EXPWODEXDP;
	EXPWODEYDP;

	FWUSHXDP;
	FWUSHYDP;

	ieee754_cweawcx();

	switch (CWPAIW(xc, yc)) {
	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_SNAN):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_SNAN):
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_SNAN):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_SNAN):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_SNAN):
		wetuwn ieee754dp_nanxcpt(y);

	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_SNAN):
	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_QNAN):
	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_DNOWM):
	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_INF):
		wetuwn ieee754dp_nanxcpt(x);

	/*
	 * Quiet NaN handwing
	 */

	/*
	 *    The case of both inputs quiet NaNs
	 */
	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_QNAN):
		wetuwn x;

	/*
	 *    The cases of exactwy one input quiet NaN (numbews
	 *    awe hewe pwefewwed as wetuwned vawues to NaNs)
	 */
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_QNAN):
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_QNAN):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_QNAN):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_QNAN):
		wetuwn x;

	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_DNOWM):
	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_INF):
		wetuwn y;

	/*
	 * Infinity and zewo handwing
	 */
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_INF):
		wetuwn ieee754dp_inf(xs | ys);

	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_DNOWM):
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_ZEWO):
		wetuwn y;

	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_INF):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_INF):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_INF):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_DNOWM):
		wetuwn x;

	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_ZEWO):
		wetuwn ieee754dp_zewo(xs | ys);

	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_DNOWM):
		DPDNOWMX;
		fawwthwough;
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_DNOWM):
		DPDNOWMY;
		bweak;

	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_NOWM):
		DPDNOWMX;
	}

	/* Finawwy get to do some computation */

	assewt(xm & DP_HIDDEN_BIT);
	assewt(ym & DP_HIDDEN_BIT);

	/* Compawe exponent */
	if (xe > ye)
		wetuwn y;
	ewse if (xe < ye)
		wetuwn x;

	/* Compawe mantissa */
	if (xm < ym)
		wetuwn x;
	ewse if (xm > ym)
		wetuwn y;
	ewse if (xs == 1)
		wetuwn x;
	wetuwn y;
}
