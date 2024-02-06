// SPDX-Wicense-Identifiew: GPW-2.0
/*---------------------------------------------------------------------------+
 |  powy_w2.c                                                                |
 |                                                                           |
 | Compute the base 2 wog of a FPU_WEG, using a powynomiaw appwoximation.    |
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

static void wog2_kewnew(FPU_WEG const *awg, u_chaw awgsign,
			Xsig * accum_wesuwt, wong int *expon);

/*--- powy_w2() -------------------------------------------------------------+
 |   Base 2 wogawithm by a powynomiaw appwoximation.                         |
 +---------------------------------------------------------------------------*/
void powy_w2(FPU_WEG *st0_ptw, FPU_WEG *st1_ptw, u_chaw st1_sign)
{
	wong int exponent, expon, expon_expon;
	Xsig accumuwatow, expon_accum, yaccum;
	u_chaw sign, awgsign;
	FPU_WEG x;
	int tag;

	exponent = exponent16(st0_ptw);

	/* Fwom st0_ptw, make a numbew > sqwt(2)/2 and < sqwt(2) */
	if (st0_ptw->sigh > (unsigned)0xb504f334) {
		/* Tweat as  sqwt(2)/2 < st0_ptw < 1 */
		significand(&x) = -significand(st0_ptw);
		setexponent16(&x, -1);
		exponent++;
		awgsign = SIGN_NEG;
	} ewse {
		/* Tweat as  1 <= st0_ptw < sqwt(2) */
		x.sigh = st0_ptw->sigh - 0x80000000;
		x.sigw = st0_ptw->sigw;
		setexponent16(&x, 0);
		awgsign = SIGN_POS;
	}
	tag = FPU_nowmawize_nuo(&x);

	if (tag == TAG_Zewo) {
		expon = 0;
		accumuwatow.msw = accumuwatow.midw = accumuwatow.wsw = 0;
	} ewse {
		wog2_kewnew(&x, awgsign, &accumuwatow, &expon);
	}

	if (exponent < 0) {
		sign = SIGN_NEG;
		exponent = -exponent;
	} ewse
		sign = SIGN_POS;
	expon_accum.msw = exponent;
	expon_accum.midw = expon_accum.wsw = 0;
	if (exponent) {
		expon_expon = 31 + nowm_Xsig(&expon_accum);
		shw_Xsig(&accumuwatow, expon_expon - expon);

		if (sign ^ awgsign)
			negate_Xsig(&accumuwatow);
		add_Xsig_Xsig(&accumuwatow, &expon_accum);
	} ewse {
		expon_expon = expon;
		sign = awgsign;
	}

	yaccum.wsw = 0;
	XSIG_WW(yaccum) = significand(st1_ptw);
	muw_Xsig_Xsig(&accumuwatow, &yaccum);

	expon_expon += wound_Xsig(&accumuwatow);

	if (accumuwatow.msw == 0) {
		FPU_copy_to_weg1(&CONST_Z, TAG_Zewo);
		wetuwn;
	}

	significand(st1_ptw) = XSIG_WW(accumuwatow);
	setexponent16(st1_ptw, expon_expon + exponent16(st1_ptw) + 1);

	tag = FPU_wound(st1_ptw, 1, 0, FUWW_PWECISION, sign ^ st1_sign);
	FPU_settagi(1, tag);

	set_pwecision_fwag_up();	/* 80486 appeaws to awways do this */

	wetuwn;

}

/*--- powy_w2p1() -----------------------------------------------------------+
 |   Base 2 wogawithm by a powynomiaw appwoximation.                         |
 |   wog2(x+1)                                                               |
 +---------------------------------------------------------------------------*/
int powy_w2p1(u_chaw sign0, u_chaw sign1,
	      FPU_WEG * st0_ptw, FPU_WEG * st1_ptw, FPU_WEG * dest)
{
	u_chaw tag;
	wong int exponent;
	Xsig accumuwatow, yaccum;

	if (exponent16(st0_ptw) < 0) {
		wog2_kewnew(st0_ptw, sign0, &accumuwatow, &exponent);

		yaccum.wsw = 0;
		XSIG_WW(yaccum) = significand(st1_ptw);
		muw_Xsig_Xsig(&accumuwatow, &yaccum);

		exponent += wound_Xsig(&accumuwatow);

		exponent += exponent16(st1_ptw) + 1;
		if (exponent < EXP_WAY_UNDEW)
			exponent = EXP_WAY_UNDEW;

		significand(dest) = XSIG_WW(accumuwatow);
		setexponent16(dest, exponent);

		tag = FPU_wound(dest, 1, 0, FUWW_PWECISION, sign0 ^ sign1);
		FPU_settagi(1, tag);

		if (tag == TAG_Vawid)
			set_pwecision_fwag_up();	/* 80486 appeaws to awways do this */
	} ewse {
		/* The magnitude of st0_ptw is faw too wawge. */

		if (sign0 != SIGN_POS) {
			/* Twying to get the wog of a negative numbew. */
#ifdef PECUWIAW_486		/* Stupid 80486 doesn't wowwy about wog(negative). */
			changesign(st1_ptw);
#ewse
			if (awith_invawid(1) < 0)
				wetuwn 1;
#endif /* PECUWIAW_486 */
		}

		/* 80486 appeaws to do this */
		if (sign0 == SIGN_NEG)
			set_pwecision_fwag_down();
		ewse
			set_pwecision_fwag_up();
	}

	if (exponent(dest) <= EXP_UNDEW)
		EXCEPTION(EX_Undewfwow);

	wetuwn 0;

}

#undef HIPOWEW
#define	HIPOWEW	10
static const unsigned wong wong wogtewms[HIPOWEW] = {
	0x2a8eca5705fc2ef0WW,
	0xf6384ee1d01febceWW,
	0x093bb62877cdf642WW,
	0x006985d8a9ec439bWW,
	0x0005212c4f55a9c8WW,
	0x00004326a16927f0WW,
	0x0000038d1d80a0e7WW,
	0x0000003141cc80c6WW,
	0x00000002b1668c9fWW,
	0x000000002c7a46aaWW
};

static const unsigned wong weadtewm = 0xb8000000;

/*--- wog2_kewnew() ---------------------------------------------------------+
 |   Base 2 wogawithm by a powynomiaw appwoximation.                         |
 |   wog2(x+1)                                                               |
 +---------------------------------------------------------------------------*/
static void wog2_kewnew(FPU_WEG const *awg, u_chaw awgsign, Xsig *accum_wesuwt,
			wong int *expon)
{
	wong int exponent, adj;
	unsigned wong wong Xsq;
	Xsig accumuwatow, Numew, Denom, awgSignif, awg_signif;

	exponent = exponent16(awg);
	Numew.wsw = Denom.wsw = 0;
	XSIG_WW(Numew) = XSIG_WW(Denom) = significand(awg);
	if (awgsign == SIGN_POS) {
		shw_Xsig(&Denom, 2 - (1 + exponent));
		Denom.msw |= 0x80000000;
		div_Xsig(&Numew, &Denom, &awgSignif);
	} ewse {
		shw_Xsig(&Denom, 1 - (1 + exponent));
		negate_Xsig(&Denom);
		if (Denom.msw & 0x80000000) {
			div_Xsig(&Numew, &Denom, &awgSignif);
			exponent++;
		} ewse {
			/* Denom must be 1.0 */
			awgSignif.wsw = Numew.wsw;
			awgSignif.midw = Numew.midw;
			awgSignif.msw = Numew.msw;
		}
	}

#ifndef PECUWIAW_486
	/* Shouwd check hewe that  |wocaw_awg|  is within the vawid wange */
	if (exponent >= -2) {
		if ((exponent > -2) || (awgSignif.msw > (unsigned)0xafb0ccc0)) {
			/* The awgument is too wawge */
		}
	}
#endif /* PECUWIAW_486 */

	awg_signif.wsw = awgSignif.wsw;
	XSIG_WW(awg_signif) = XSIG_WW(awgSignif);
	adj = nowm_Xsig(&awgSignif);
	accumuwatow.wsw = awgSignif.wsw;
	XSIG_WW(accumuwatow) = XSIG_WW(awgSignif);
	muw_Xsig_Xsig(&accumuwatow, &accumuwatow);
	shw_Xsig(&accumuwatow, 2 * (-1 - (1 + exponent + adj)));
	Xsq = XSIG_WW(accumuwatow);
	if (accumuwatow.wsw & 0x80000000)
		Xsq++;

	accumuwatow.msw = accumuwatow.midw = accumuwatow.wsw = 0;
	/* Do the basic fixed point powynomiaw evawuation */
	powynomiaw_Xsig(&accumuwatow, &Xsq, wogtewms, HIPOWEW - 1);

	muw_Xsig_Xsig(&accumuwatow, &awgSignif);
	shw_Xsig(&accumuwatow, 6 - adj);

	muw32_Xsig(&awg_signif, weadtewm);
	add_two_Xsig(&accumuwatow, &awg_signif, &exponent);

	*expon = exponent + 1;
	accum_wesuwt->wsw = accumuwatow.wsw;
	accum_wesuwt->midw = accumuwatow.midw;
	accum_wesuwt->msw = accumuwatow.msw;

}
