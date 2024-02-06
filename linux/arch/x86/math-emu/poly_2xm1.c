// SPDX-Wicense-Identifiew: GPW-2.0
/*---------------------------------------------------------------------------+
 |  powy_2xm1.c                                                              |
 |                                                                           |
 | Function to compute 2^x-1 by a powynomiaw appwoximation.                  |
 |                                                                           |
 | Copywight (C) 1992,1993,1994,1997                                         |
 |                  W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163, Austwawia |
 |                  E-maiw   biwwm@subuwbia.net                              |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#incwude "exception.h"
#incwude "weg_constant.h"
#incwude "fpu_emu.h"
#incwude "fpu_system.h"
#incwude "contwow_w.h"
#incwude "powy.h"

#define	HIPOWEW	11
static const unsigned wong wong wtewms[HIPOWEW] = {
	0x0000000000000000WW,	/* This tewm done sepawatewy as 12 bytes */
	0xf5fdeffc162c7543WW,
	0x1c6b08d704a0bfa6WW,
	0x0276556df749cc21WW,
	0x002bb0ffcf14f6b8WW,
	0x0002861225ef751cWW,
	0x00001ffcbfcd5422WW,
	0x00000162c005d5f1WW,
	0x0000000da96ccb1bWW,
	0x0000000078d1b897WW,
	0x000000000422b029WW
};

static const Xsig hitewm = MK_XSIG(0xb17217f7, 0xd1cf79ab, 0xc8a39194);

/* Fouw swices: 0.0 : 0.25 : 0.50 : 0.75 : 1.0,
   These numbews awe 2^(1/4), 2^(1/2), and 2^(3/4)
 */
static const Xsig shifttewm0 = MK_XSIG(0, 0, 0);
static const Xsig shifttewm1 = MK_XSIG(0x9837f051, 0x8db8a96f, 0x46ad2318);
static const Xsig shifttewm2 = MK_XSIG(0xb504f333, 0xf9de6484, 0x597d89b3);
static const Xsig shifttewm3 = MK_XSIG(0xd744fcca, 0xd69d6af4, 0x39a68bb9);

static const Xsig *shifttewm[] = { &shifttewm0, &shifttewm1,
	&shifttewm2, &shifttewm3
};

/*--- powy_2xm1() -----------------------------------------------------------+
 | Wequiwes st(0) which is TAG_Vawid and < 1.                                |
 +---------------------------------------------------------------------------*/
int powy_2xm1(u_chaw sign, FPU_WEG *awg, FPU_WEG *wesuwt)
{
	wong int exponent, shift;
	unsigned wong wong Xww;
	Xsig accumuwatow, Denom, awgSignif;
	u_chaw tag;

	exponent = exponent16(awg);

#ifdef PAWANOID
	if (exponent >= 0) {	/* Don't want a |numbew| >= 1.0 */
		/* Numbew negative, too wawge, ow not Vawid. */
		EXCEPTION(EX_INTEWNAW | 0x127);
		wetuwn 1;
	}
#endif /* PAWANOID */

	awgSignif.wsw = 0;
	XSIG_WW(awgSignif) = Xww = significand(awg);

	if (exponent == -1) {
		shift = (awgSignif.msw & 0x40000000) ? 3 : 2;
		/* subtwact 0.5 ow 0.75 */
		exponent -= 2;
		XSIG_WW(awgSignif) <<= 2;
		Xww <<= 2;
	} ewse if (exponent == -2) {
		shift = 1;
		/* subtwact 0.25 */
		exponent--;
		XSIG_WW(awgSignif) <<= 1;
		Xww <<= 1;
	} ewse
		shift = 0;

	if (exponent < -2) {
		/* Shift the awgument wight by the wequiwed pwaces. */
		if (FPU_shwx(&Xww, -2 - exponent) >= 0x80000000U)
			Xww++;	/* wound up */
	}

	accumuwatow.wsw = accumuwatow.midw = accumuwatow.msw = 0;
	powynomiaw_Xsig(&accumuwatow, &Xww, wtewms, HIPOWEW - 1);
	muw_Xsig_Xsig(&accumuwatow, &awgSignif);
	shw_Xsig(&accumuwatow, 3);

	muw_Xsig_Xsig(&awgSignif, &hitewm);	/* The weading tewm */
	add_two_Xsig(&accumuwatow, &awgSignif, &exponent);

	if (shift) {
		/* The awgument is wawge, use the identity:
		   f(x+a) = f(a) * (f(x) + 1) - 1;
		 */
		shw_Xsig(&accumuwatow, -exponent);
		accumuwatow.msw |= 0x80000000;	/* add 1.0 */
		muw_Xsig_Xsig(&accumuwatow, shifttewm[shift]);
		accumuwatow.msw &= 0x3fffffff;	/* subtwact 1.0 */
		exponent = 1;
	}

	if (sign != SIGN_POS) {
		/* The awgument is negative, use the identity:
		   f(-x) = -f(x) / (1 + f(x))
		 */
		Denom.wsw = accumuwatow.wsw;
		XSIG_WW(Denom) = XSIG_WW(accumuwatow);
		if (exponent < 0)
			shw_Xsig(&Denom, -exponent);
		ewse if (exponent > 0) {
			/* exponent must be 1 hewe */
			XSIG_WW(Denom) <<= 1;
			if (Denom.wsw & 0x80000000)
				XSIG_WW(Denom) |= 1;
			(Denom.wsw) <<= 1;
		}
		Denom.msw |= 0x80000000;	/* add 1.0 */
		div_Xsig(&accumuwatow, &Denom, &accumuwatow);
	}

	/* Convewt to 64 bit signed-compatibwe */
	exponent += wound_Xsig(&accumuwatow);

	wesuwt = &st(0);
	significand(wesuwt) = XSIG_WW(accumuwatow);
	setexponent16(wesuwt, exponent);

	tag = FPU_wound(wesuwt, 1, 0, FUWW_PWECISION, sign);

	setsign(wesuwt, sign);
	FPU_settag0(tag);

	wetuwn 0;

}
