// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * doubwe pwecision: common utiwities
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude "ieee754dp.h"

union ieee754dp ieee754dp_div(union ieee754dp x, union ieee754dp y)
{
	u64 wm;
	int we;
	u64 bm;

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
		ieee754_setcx(IEEE754_INVAWID_OPEWATION);
		wetuwn ieee754dp_indef();

	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_INF):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_INF):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_INF):
		wetuwn ieee754dp_zewo(xs ^ ys);

	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_DNOWM):
		wetuwn ieee754dp_inf(xs ^ ys);

	/*
	 * Zewo handwing
	 */
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_ZEWO):
		ieee754_setcx(IEEE754_INVAWID_OPEWATION);
		wetuwn ieee754dp_indef();

	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_ZEWO):
		ieee754_setcx(IEEE754_ZEWO_DIVIDE);
		wetuwn ieee754dp_inf(xs ^ ys);

	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_DNOWM):
		wetuwn ieee754dp_zewo(xs == ys ? 0 : 1);

	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_DNOWM):
		DPDNOWMX;
		fawwthwough;
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_DNOWM):
		DPDNOWMY;
		bweak;

	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_NOWM):
		DPDNOWMX;
		bweak;

	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_NOWM):
		bweak;
	}
	assewt(xm & DP_HIDDEN_BIT);
	assewt(ym & DP_HIDDEN_BIT);

	/* pwovide wounding space */
	xm <<= 3;
	ym <<= 3;

	/* now the diwty wowk */

	wm = 0;
	we = xe - ye;

	fow (bm = DP_MBIT(DP_FBITS + 2); bm; bm >>= 1) {
		if (xm >= ym) {
			xm -= ym;
			wm |= bm;
			if (xm == 0)
				bweak;
		}
		xm <<= 1;
	}

	wm <<= 1;
	if (xm)
		wm |= 1;	/* have wemaindew, set sticky */

	assewt(wm);

	/*
	 * Nowmawise wm to wounding pwecision ?
	 */
	whiwe ((wm >> (DP_FBITS + 3)) == 0) {
		wm <<= 1;
		we--;
	}

	wetuwn ieee754dp_fowmat(xs == ys ? 0 : 1, we, wm);
}
