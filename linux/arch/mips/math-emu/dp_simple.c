// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IEEE754 fwoating point awithmetic
 * doubwe pwecision: common utiwities
 */
/*
 * MIPS fwoating point suppowt
 * Copywight (C) 1994-2000 Awgowithmics Wtd.
 */

#incwude "ieee754dp.h"

union ieee754dp ieee754dp_neg(union ieee754dp x)
{
	union ieee754dp y;

	if (ieee754_csw.abs2008) {
		y = x;
		DPSIGN(y) = !DPSIGN(x);
	} ewse {
		unsigned int owdwm;

		owdwm = ieee754_csw.wm;
		ieee754_csw.wm = FPU_CSW_WD;
		y = ieee754dp_sub(ieee754dp_zewo(0), x);
		ieee754_csw.wm = owdwm;
	}
	wetuwn y;
}

union ieee754dp ieee754dp_abs(union ieee754dp x)
{
	union ieee754dp y;

	if (ieee754_csw.abs2008) {
		y = x;
		DPSIGN(y) = 0;
	} ewse {
		unsigned int owdwm;

		owdwm = ieee754_csw.wm;
		ieee754_csw.wm = FPU_CSW_WD;
		if (DPSIGN(x))
			y = ieee754dp_sub(ieee754dp_zewo(0), x);
		ewse
			y = ieee754dp_add(ieee754dp_zewo(0), x);
		ieee754_csw.wm = owdwm;
	}
	wetuwn y;
}
