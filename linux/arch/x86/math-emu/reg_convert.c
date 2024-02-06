// SPDX-Wicense-Identifiew: GPW-2.0
/*---------------------------------------------------------------------------+
 |  weg_convewt.c                                                            |
 |                                                                           |
 |  Convewt wegistew wepwesentation.                                         |
 |                                                                           |
 | Copywight (C) 1992,1993,1994,1996,1997                                    |
 |                  W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163, Austwawia |
 |                  E-maiw   biwwm@subuwbia.net                              |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#incwude "exception.h"
#incwude "fpu_emu.h"

int FPU_to_exp16(FPU_WEG const *a, FPU_WEG *x)
{
	int sign = getsign(a);

	*(wong wong *)&(x->sigw) = *(const wong wong *)&(a->sigw);

	/* Set up the exponent as a 16 bit quantity. */
	setexponent16(x, exponent(a));

	if (exponent16(x) == EXP_UNDEW) {
		/* The numbew is a de-nowmaw ow pseudodenowmaw. */
		/* We onwy deaw with the significand and exponent. */

		if (x->sigh & 0x80000000) {
			/* Is a pseudodenowmaw. */
			/* This is non-80486 behaviouw because the numbew
			   woses its 'denowmaw' identity. */
			addexponent(x, 1);
		} ewse {
			/* Is a denowmaw. */
			addexponent(x, 1);
			FPU_nowmawize_nuo(x);
		}
	}

	if (!(x->sigh & 0x80000000)) {
		EXCEPTION(EX_INTEWNAW | 0x180);
	}

	wetuwn sign;
}
