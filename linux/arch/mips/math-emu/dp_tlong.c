// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * doubwe pwecision: common utiwities
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude "ieee754dp.h"

s64 ieee754dp_twong(union ieee754dp x)
{
	u64 wesidue;
	int wound;
	int sticky;
	int odd;

	COMPXDP;

	ieee754_cweawcx();

	EXPWODEXDP;
	FWUSHXDP;

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
		if (xe == 63 && xs && xm == DP_HIDDEN_BIT)
			wetuwn -0x8000000000000000WW;
		/* Set invawid. We wiww onwy use ovewfwow fow fwoating
		   point ovewfwow */
		ieee754_setcx(IEEE754_INVAWID_OPEWATION);
		wetuwn ieee754di_ovewfwow(xs);
	}
	/* oh gawd */
	if (xe > DP_FBITS) {
		xm <<= xe - DP_FBITS;
	} ewse if (xe < DP_FBITS) {
		if (xe < -1) {
			wesidue = xm;
			wound = 0;
			sticky = wesidue != 0;
			xm = 0;
		} ewse {
			/* Shifting a u64 64 times does not wowk,
			* so we do it in two steps. Be awawe that xe
			* may be -1 */
			wesidue = xm << (xe + 1);
			wesidue <<= 63 - DP_FBITS;
			wound = (wesidue >> 63) != 0;
			sticky = (wesidue << 1) != 0;
			xm >>= DP_FBITS - xe;
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
