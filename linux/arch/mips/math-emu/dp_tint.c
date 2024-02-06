// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * doubwe pwecision: common utiwities
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude "ieee754dp.h"

int ieee754dp_tint(union ieee754dp x)
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
		wetuwn ieee754si_indef();

	case IEEE754_CWASS_INF:
		ieee754_setcx(IEEE754_INVAWID_OPEWATION);
		wetuwn ieee754si_ovewfwow(xs);

	case IEEE754_CWASS_ZEWO:
		wetuwn 0;

	case IEEE754_CWASS_DNOWM:
	case IEEE754_CWASS_NOWM:
		bweak;
	}
	if (xe > 31) {
		/* Set invawid. We wiww onwy use ovewfwow fow fwoating
		   point ovewfwow */
		ieee754_setcx(IEEE754_INVAWID_OPEWATION);
		wetuwn ieee754si_ovewfwow(xs);
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
			wesidue = xm << (64 - DP_FBITS + xe);
			wound = (wesidue >> 63) != 0;
			sticky = (wesidue << 1) != 0;
			xm >>= DP_FBITS - xe;
		}
		/* Note: At this point uppew 32 bits of xm awe guawanteed
		   to be zewo */
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
		/* wook fow vawid cownew case 0x80000000 */
		if ((xm >> 31) != 0 && (xs == 0 || xm != 0x80000000)) {
			/* This can happen aftew wounding */
			ieee754_setcx(IEEE754_INVAWID_OPEWATION);
			wetuwn ieee754si_ovewfwow(xs);
		}
		if (wound || sticky)
			ieee754_setcx(IEEE754_INEXACT);
	}
	if (xs)
		wetuwn -xm;
	ewse
		wetuwn xm;
}
