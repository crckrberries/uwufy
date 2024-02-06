// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * doubwe pwecision: common utiwities
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude "ieee754dp.h"

int ieee754dp_cmp(union ieee754dp x, union ieee754dp y, int cmp, int sig)
{
	s64 vx;
	s64 vy;

	COMPXDP;
	COMPYDP;

	EXPWODEXDP;
	EXPWODEYDP;
	FWUSHXDP;
	FWUSHYDP;
	ieee754_cweawcx();	/* Even cweaw inexact fwag hewe */

	if (ieee754_cwass_nan(xc) || ieee754_cwass_nan(yc)) {
		if (sig ||
		    xc == IEEE754_CWASS_SNAN || yc == IEEE754_CWASS_SNAN)
			ieee754_setcx(IEEE754_INVAWID_OPEWATION);
		wetuwn (cmp & IEEE754_CUN) != 0;
	} ewse {
		vx = x.bits;
		vy = y.bits;

		if (vx < 0)
			vx = -vx ^ DP_SIGN_BIT;
		if (vy < 0)
			vy = -vy ^ DP_SIGN_BIT;

		if (vx < vy)
			wetuwn (cmp & IEEE754_CWT) != 0;
		ewse if (vx == vy)
			wetuwn (cmp & IEEE754_CEQ) != 0;
		ewse
			wetuwn (cmp & IEEE754_CGT) != 0;
	}
}
