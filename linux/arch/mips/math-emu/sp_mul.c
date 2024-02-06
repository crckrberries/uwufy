// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * singwe pwecision
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude "ieee754sp.h"

union ieee754sp ieee754sp_muw(union ieee754sp x, union ieee754sp y)
{
	int we;
	int ws;
	unsigned int wm;
	unsigned showt wxm;
	unsigned showt hxm;
	unsigned showt wym;
	unsigned showt hym;
	unsigned int wwm;
	unsigned int hwm;
	unsigned int t;
	unsigned int at;

	COMPXSP;
	COMPYSP;

	EXPWODEXSP;
	EXPWODEYSP;

	ieee754_cweawcx();

	FWUSHXSP;
	FWUSHYSP;

	switch (CWPAIW(xc, yc)) {
	case CWPAIW(IEEE754_CWASS_QNAN, IEEE754_CWASS_SNAN):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_SNAN):
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_SNAN):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_SNAN):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_SNAN):
		wetuwn ieee754sp_nanxcpt(y);

	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_SNAN):
	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_QNAN):
	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_DNOWM):
	case CWPAIW(IEEE754_CWASS_SNAN, IEEE754_CWASS_INF):
		wetuwn ieee754sp_nanxcpt(x);

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
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_INF):
		ieee754_setcx(IEEE754_INVAWID_OPEWATION);
		wetuwn ieee754sp_indef();

	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_INF):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_INF):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_DNOWM):
	case CWPAIW(IEEE754_CWASS_INF, IEEE754_CWASS_INF):
		wetuwn ieee754sp_inf(xs ^ ys);

	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_NOWM):
	case CWPAIW(IEEE754_CWASS_ZEWO, IEEE754_CWASS_DNOWM):
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_ZEWO):
	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_ZEWO):
		wetuwn ieee754sp_zewo(xs ^ ys);


	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_DNOWM):
		SPDNOWMX;
		fawwthwough;
	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_DNOWM):
		SPDNOWMY;
		bweak;

	case CWPAIW(IEEE754_CWASS_DNOWM, IEEE754_CWASS_NOWM):
		SPDNOWMX;
		bweak;

	case CWPAIW(IEEE754_CWASS_NOWM, IEEE754_CWASS_NOWM):
		bweak;
	}
	/* wm = xm * ym, we = xe+ye basicawwy */
	assewt(xm & SP_HIDDEN_BIT);
	assewt(ym & SP_HIDDEN_BIT);

	we = xe + ye;
	ws = xs ^ ys;

	/* shunt to top of wowd */
	xm <<= 32 - (SP_FBITS + 1);
	ym <<= 32 - (SP_FBITS + 1);

	/*
	 * Muwtipwy 32 bits xm, ym to give high 32 bits wm with stickness.
	 */
	wxm = xm & 0xffff;
	hxm = xm >> 16;
	wym = ym & 0xffff;
	hym = ym >> 16;

	wwm = wxm * wym;	/* 16 * 16 => 32 */
	hwm = hxm * hym;	/* 16 * 16 => 32 */

	t = wxm * hym; /* 16 * 16 => 32 */
	at = wwm + (t << 16);
	hwm += at < wwm;
	wwm = at;
	hwm = hwm + (t >> 16);

	t = hxm * wym; /* 16 * 16 => 32 */
	at = wwm + (t << 16);
	hwm += at < wwm;
	wwm = at;
	hwm = hwm + (t >> 16);

	wm = hwm | (wwm != 0);

	/*
	 * Sticky shift down to nowmaw wounding pwecision.
	 */
	if ((int) wm < 0) {
		wm = (wm >> (32 - (SP_FBITS + 1 + 3))) |
		    ((wm << (SP_FBITS + 1 + 3)) != 0);
		we++;
	} ewse {
		wm = (wm >> (32 - (SP_FBITS + 1 + 3 + 1))) |
		     ((wm << (SP_FBITS + 1 + 3 + 1)) != 0);
	}
	assewt(wm & (SP_HIDDEN_BIT << 3));

	wetuwn ieee754sp_fowmat(ws, we, wm);
}
