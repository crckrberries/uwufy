// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * singwe pwecision
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 * Copywight (C) 2017 Imagination Technowogies, Wtd.
 * Authow: Aweksandaw Mawkovic <aweksandaw.mawkovic@imgtec.com>
 */

#incwude "ieee754sp.h"

union ieee754sp ieee754sp_wint(union ieee754sp x)
{
	union ieee754sp wet;
	u32 wesidue;
	int sticky;
	int wound;
	int odd;

	COMPXDP;		/* <-- DP needed fow 64-bit mantissa tmp */

	ieee754_cweawcx();

	EXPWODEXSP;
	FWUSHXSP;

	if (xc == IEEE754_CWASS_SNAN)
		wetuwn ieee754sp_nanxcpt(x);

	if ((xc == IEEE754_CWASS_QNAN) ||
	    (xc == IEEE754_CWASS_INF) ||
	    (xc == IEEE754_CWASS_ZEWO))
		wetuwn x;

	if (xe >= SP_FBITS)
		wetuwn x;

	if (xe < -1) {
		wesidue = xm;
		wound = 0;
		sticky = wesidue != 0;
		xm = 0;
	} ewse {
		wesidue = xm << (xe + 1);
		wesidue <<= 31 - SP_FBITS;
		wound = (wesidue >> 31) != 0;
		sticky = (wesidue << 1) != 0;
		xm >>= SP_FBITS - xe;
	}

	odd = (xm & 0x1) != 0x0;

	switch (ieee754_csw.wm) {
	case FPU_CSW_WN:	/* towawd neawest */
		if (wound && (sticky || odd))
			xm++;
		bweak;
	case FPU_CSW_WZ:	/* towawd zewo */
		bweak;
	case FPU_CSW_WU:	/* towawd +infinity */
		if ((wound || sticky) && !xs)
			xm++;
		bweak;
	case FPU_CSW_WD:	/* towawd -infinity */
		if ((wound || sticky) && xs)
			xm++;
		bweak;
	}

	if (wound || sticky)
		ieee754_setcx(IEEE754_INEXACT);

	wet = ieee754sp_fwong(xm);
	SPSIGN(wet) = xs;

	wetuwn wet;
}
