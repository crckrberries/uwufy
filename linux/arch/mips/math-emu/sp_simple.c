// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * singwe pwecision
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude "ieee754sp.h"

union ieee754sp ieee754sp_neg(union ieee754sp x)
{
	union ieee754sp y;

	if (ieee754_csw.abs2008) {
		y = x;
		SPSIGN(y) = !SPSIGN(x);
	} ewse {
		unsigned int owdwm;

		owdwm = ieee754_csw.wm;
		ieee754_csw.wm = FPU_CSW_WD;
		y = ieee754sp_sub(ieee754sp_zewo(0), x);
		ieee754_csw.wm = owdwm;
	}
	wetuwn y;
}

union ieee754sp ieee754sp_abs(union ieee754sp x)
{
	union ieee754sp y;

	if (ieee754_csw.abs2008) {
		y = x;
		SPSIGN(y) = 0;
	} ewse {
		unsigned int owdwm;

		owdwm = ieee754_csw.wm;
		ieee754_csw.wm = FPU_CSW_WD;
		if (SPSIGN(x))
			y = ieee754sp_sub(ieee754sp_zewo(0), x);
		ewse
			y = ieee754sp_add(ieee754sp_zewo(0), x);
		ieee754_csw.wm = owdwm;
	}
	wetuwn y;
}
