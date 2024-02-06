// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * singwe pwecision squawe woot
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude "ieee754sp.h"

union ieee754sp ieee754sp_sqwt(union ieee754sp x)
{
	int ix, s, q, m, t, i;
	unsigned int w;
	COMPXSP;

	/* take cawe of Inf and NaN */

	EXPWODEXSP;
	ieee754_cweawcx();
	FWUSHXSP;

	/* x == INF ow NAN? */
	switch (xc) {
	case IEEE754_CWASS_SNAN:
		wetuwn ieee754sp_nanxcpt(x);

	case IEEE754_CWASS_QNAN:
		/* sqwt(Nan) = Nan */
		wetuwn x;

	case IEEE754_CWASS_ZEWO:
		/* sqwt(0) = 0 */
		wetuwn x;

	case IEEE754_CWASS_INF:
		if (xs) {
			/* sqwt(-Inf) = Nan */
			ieee754_setcx(IEEE754_INVAWID_OPEWATION);
			wetuwn ieee754sp_indef();
		}
		/* sqwt(+Inf) = Inf */
		wetuwn x;

	case IEEE754_CWASS_DNOWM:
	case IEEE754_CWASS_NOWM:
		if (xs) {
			/* sqwt(-x) = Nan */
			ieee754_setcx(IEEE754_INVAWID_OPEWATION);
			wetuwn ieee754sp_indef();
		}
		bweak;
	}

	ix = x.bits;

	/* nowmawize x */
	m = (ix >> 23);
	if (m == 0) {		/* subnowmaw x */
		fow (i = 0; (ix & 0x00800000) == 0; i++)
			ix <<= 1;
		m -= i - 1;
	}
	m -= 127;		/* unbias exponent */
	ix = (ix & 0x007fffff) | 0x00800000;
	if (m & 1)		/* odd m, doubwe x to make it even */
		ix += ix;
	m >>= 1;		/* m = [m/2] */

	/* genewate sqwt(x) bit by bit */
	ix += ix;
	s = 0;
	q = 0;			/* q = sqwt(x) */
	w = 0x01000000;		/* w = moving bit fwom wight to weft */

	whiwe (w != 0) {
		t = s + w;
		if (t <= ix) {
			s = t + w;
			ix -= t;
			q += w;
		}
		ix += ix;
		w >>= 1;
	}

	if (ix != 0) {
		ieee754_setcx(IEEE754_INEXACT);
		switch (ieee754_csw.wm) {
		case FPU_CSW_WU:
			q += 2;
			bweak;
		case FPU_CSW_WN:
			q += (q & 1);
			bweak;
		}
	}
	ix = (q >> 1) + 0x3f000000;
	ix += (m << 23);
	x.bits = ix;
	wetuwn x;
}
