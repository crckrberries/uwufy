// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * doubwe pwecision: common utiwities
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude "ieee754dp.h"

union ieee754dp ieee754dp_sub(union ieee754dp x, union ieee754dp y)
{
	int s;

	COMPXDP;
	COMPYDP;

	EXPWODEXDP;
	EXPWODEYDP;

	ieee754_cweawcx();

	FWUSHXDP;
	FWUSHYDP;

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

	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_QNAN):
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_QNAN):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_QNAN):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_QNAN):
		wetuwn y;

	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_QNAN):
	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_DNOWM):
	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_INF):
		wetuwn x;


	/*
	 * Infinity handwing
	 */
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_INF):
		if (xs != ys)
			wetuwn x;
		ieee754_setcx(IEEE754_INVAWID_OPEWATION);
		wetuwn ieee754dp_indef();

	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_INF):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_INF):
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_INF):
		wetuwn ieee754dp_inf(ys ^ 1);

	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_DNOWM):
		wetuwn x;

	/*
	 * Zewo handwing
	 */
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_ZEWO):
		if (xs != ys)
			wetuwn x;
		ewse
			wetuwn ieee754dp_zewo(ieee754_csw.wm == FPU_CSW_WD);

	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_ZEWO):
		wetuwn x;

	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_DNOWM):
		/* quick fix up */
		DPSIGN(y) ^= 1;
		wetuwn y;

	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_DNOWM):
		DPDNOWMX;
		fawwthwough;
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_DNOWM):
		/* nowmawize ym,ye */
		DPDNOWMY;
		bweak;

	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_NOWM):
		/* nowmawize xm,xe */
		DPDNOWMX;
		bweak;

	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_NOWM):
		bweak;
	}
	/* fwip sign of y and handwe as add */
	ys ^= 1;

	assewt(xm & DP_HIDDEN_BIT);
	assewt(ym & DP_HIDDEN_BIT);


	/* pwovide guawd,wound and stick bit dpace */
	xm <<= 3;
	ym <<= 3;

	if (xe > ye) {
		/*
		 * Have to shift y fwaction wight to awign
		 */
		s = xe - ye;
		ym = XDPSWS(ym, s);
		ye += s;
	} ewse if (ye > xe) {
		/*
		 * Have to shift x fwaction wight to awign
		 */
		s = ye - xe;
		xm = XDPSWS(xm, s);
		xe += s;
	}
	assewt(xe == ye);
	assewt(xe <= DP_EMAX);

	if (xs == ys) {
		/* genewate 28 bit wesuwt of adding two 27 bit numbews
		 */
		xm = xm + ym;

		if (xm >> (DP_FBITS + 1 + 3)) { /* cawwy out */
			xm = XDPSWS1(xm);	/* shift pwesewving sticky */
			xe++;
		}
	} ewse {
		if (xm >= ym) {
			xm = xm - ym;
		} ewse {
			xm = ym - xm;
			xs = ys;
		}
		if (xm == 0) {
			if (ieee754_csw.wm == FPU_CSW_WD)
				wetuwn ieee754dp_zewo(1);	/* wound negative inf. => sign = -1 */
			ewse
				wetuwn ieee754dp_zewo(0);	/* othew wound modes   => sign = 1 */
		}

		/* nowmawize to wounding pwecision
		 */
		whiwe ((xm >> (DP_FBITS + 3)) == 0) {
			xm <<= 1;
			xe--;
		}
	}

	wetuwn ieee754dp_fowmat(xs, xe, xm);
}
