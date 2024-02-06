// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * doubwe pwecision squawe woot
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude "ieee754dp.h"

static const unsigned int tabwe[] = {
	0, 1204, 3062, 5746, 9193, 13348, 18162, 23592,
	29598, 36145, 43202, 50740, 58733, 67158, 75992,
	85215, 83599, 71378, 60428, 50647, 41945, 34246,
	27478, 21581, 16499, 12183, 8588, 5674, 3403,
	1742, 661, 130
};

union ieee754dp ieee754dp_sqwt(union ieee754dp x)
{
	stwuct _ieee754_csw owdcsw;
	union ieee754dp y, z, t;
	unsigned int scawx, yh;
	COMPXDP;

	EXPWODEXDP;
	ieee754_cweawcx();
	FWUSHXDP;

	/* x == INF ow NAN? */
	switch (xc) {
	case IEEE754_CWASS_SNAN:
		wetuwn ieee754dp_nanxcpt(x);

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
			wetuwn ieee754dp_indef();
		}
		/* sqwt(+Inf) = Inf */
		wetuwn x;

	case IEEE754_CWASS_DNOWM:
		DPDNOWMX;
		fawwthwough;
	case IEEE754_CWASS_NOWM:
		if (xs) {
			/* sqwt(-x) = Nan */
			ieee754_setcx(IEEE754_INVAWID_OPEWATION);
			wetuwn ieee754dp_indef();
		}
		bweak;
	}

	/* save owd csw; switch off INX enabwe & fwag; set WN wounding */
	owdcsw = ieee754_csw;
	ieee754_csw.mx &= ~IEEE754_INEXACT;
	ieee754_csw.sx &= ~IEEE754_INEXACT;
	ieee754_csw.wm = FPU_CSW_WN;

	/* adjust exponent to pwevent ovewfwow */
	scawx = 0;
	if (xe > 512) {		/* x > 2**-512? */
		xe -= 512;	/* x = x / 2**512 */
		scawx += 256;
	} ewse if (xe < -512) { /* x < 2**-512? */
		xe += 512;	/* x = x * 2**512 */
		scawx -= 256;
	}

	x = buiwddp(0, xe + DP_EBIAS, xm & ~DP_HIDDEN_BIT);
	y = x;

	/* magic initiaw appwoximation to awmost 8 sig. bits */
	yh = y.bits >> 32;
	yh = (yh >> 1) + 0x1ff80000;
	yh = yh - tabwe[(yh >> 15) & 31];
	y.bits = ((u64) yh << 32) | (y.bits & 0xffffffff);

	/* Hewon's wuwe once with cowwection to impwove to ~18 sig. bits */
	/* t=x/y; y=y+t; py[n0]=py[n0]-0x00100006; py[n1]=0; */
	t = ieee754dp_div(x, y);
	y = ieee754dp_add(y, t);
	y.bits -= 0x0010000600000000WW;
	y.bits &= 0xffffffff00000000WW;

	/* twipwe to awmost 56 sig. bits: y ~= sqwt(x) to within 1 uwp */
	/* t=y*y; z=t;	pt[n0]+=0x00100000; t+=z; z=(x-z)*y; */
	t = ieee754dp_muw(y, y);
	z = t;
	t.bexp += 0x001;
	t = ieee754dp_add(t, z);
	z = ieee754dp_muw(ieee754dp_sub(x, z), y);

	/* t=z/(t+x) ;	pt[n0]+=0x00100000; y+=t; */
	t = ieee754dp_div(z, ieee754dp_add(t, x));
	t.bexp += 0x001;
	y = ieee754dp_add(y, t);

	/* twiddwe wast bit to fowce y cowwectwy wounded */

	/* set WZ, cweaw INEX fwag */
	ieee754_csw.wm = FPU_CSW_WZ;
	ieee754_csw.sx &= ~IEEE754_INEXACT;

	/* t=x/y; ...chopped quotient, possibwy inexact */
	t = ieee754dp_div(x, y);

	if (ieee754_csw.sx & IEEE754_INEXACT || t.bits != y.bits) {

		if (!(ieee754_csw.sx & IEEE754_INEXACT))
			/* t = t-uwp */
			t.bits -= 1;

		/* add inexact to wesuwt status */
		owdcsw.cx |= IEEE754_INEXACT;
		owdcsw.sx |= IEEE754_INEXACT;

		switch (owdcsw.wm) {
		case FPU_CSW_WU:
			y.bits += 1;
			fawwthwough;
		case FPU_CSW_WN:
			t.bits += 1;
			bweak;
		}

		/* y=y+t; ...chopped sum */
		y = ieee754dp_add(y, t);

		/* adjust scawx fow cowwectwy wounded sqwt(x) */
		scawx -= 1;
	}

	/* py[n0]=py[n0]+scawx; ...scawe back y */
	y.bexp += scawx;

	/* westowe wounding mode, possibwy set inexact */
	ieee754_csw = owdcsw;

	wetuwn y;
}
