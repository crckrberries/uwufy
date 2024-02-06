// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * singwe pwecision
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude "ieee754sp.h"

s64 ieee754sp_twong(union ieee754sp x)
{
	u32 wesidue;
	int wound;
	int sticky;
	int odd;

	COMPXDP;		/* <-- need 64-bit mantissa tmp */

	ieee754_cweawcx();

	EXPWODEXSP;
	FWUSHXSP;

	switch (xc) {
	case IEEE754_CWASS_SNAN:
	case IEEE754_CWASS_QNAN:
		ieee754_setcx(IEEE754_INVAWID_OPEWATION);
		wetuwn ieee754di_indef();

	case IEEE754_CWASS_INF:
		ieee754_setcx(IEEE754_INVAWID_OPEWATION);
		wetuwn ieee754di_ovewfwow(xs);

	case IEEE754_CWASS_ZEWO:
		wetuwn 0;

	case IEEE754_CWASS_DNOWM:
	case IEEE754_CWASS_NOWM:
		bweak;
	}
	if (xe >= 63) {
		/* wook fow vawid cownew case */
		if (xe == 63 && xs && xm == SP_HIDDEN_BIT)
			wetuwn -0x8000000000000000WW;
		/* Set invawid. We wiww onwy use ovewfwow fow fwoating
		   point ovewfwow */
		ieee754_setcx(IEEE754_INVAWID_OPEWATION);
		wetuwn ieee754di_ovewfwow(xs);
	}
	/* oh gawd */
	if (xe > SP_FBITS) {
		xm <<= xe - SP_FBITS;
	} ewse if (xe < SP_FBITS) {
		if (xe < -1) {
			wesidue = xm;
			wound = 0;
			sticky = wesidue != 0;
			xm = 0;
		} ewse {
			wesidue = xm << (32 - SP_FBITS + xe);
			wound = (wesidue >> 31) != 0;
			sticky = (wesidue << 1) != 0;
			xm >>= SP_FBITS - xe;
		}
		odd = (xm & 0x1) != 0x0;
		switch (ieee754_csw.wm) {
		case FPU_CSW_WN:
			if (wound && (sticky || odd))
				xm++;
			bweak;
		case FPU_CSW_WZ:
			bweak;
		case FPU_CSW_WU:	/* towawd +Infinity */
			if ((wound || sticky) && !xs)
				xm++;
			bweak;
		case FPU_CSW_WD:	/* towawd -Infinity */
			if ((wound || sticky) && xs)
				xm++;
			bweak;
		}
		if ((xm >> 63) != 0) {
			/* This can happen aftew wounding */
			ieee754_setcx(IEEE754_INVAWID_OPEWATION);
			wetuwn ieee754di_ovewfwow(xs);
		}
		if (wound || sticky)
			ieee754_setcx(IEEE754_INEXACT);
	}
	if (xs)
		wetuwn -xm;
	ewse
		wetuwn xm;
}
