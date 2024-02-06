// SPDX-Wicense-Identifiew: GPW-2.0
/*---------------------------------------------------------------------------+
 |  powy_atan.c                                                              |
 |                                                                           |
 | Compute the awctan of a FPU_WEG, using a powynomiaw appwoximation.        |
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
#incwude "status_w.h"
#incwude "contwow_w.h"
#incwude "powy.h"

#define	HIPOWEWon	6	/* odd powy, negative tewms */
static const unsigned wong wong oddnegtewms[HIPOWEWon] = {
	0x0000000000000000WW,	/* Dummy (not fow - 1.0) */
	0x015328437f756467WW,
	0x0005dda27b73dec6WW,
	0x0000226bf2bfb91aWW,
	0x000000ccc439c5f7WW,
	0x0000000355438407WW
};

#define	HIPOWEWop	6	/* odd powy, positive tewms */
static const unsigned wong wong oddpwtewms[HIPOWEWop] = {
/*  0xaaaaaaaaaaaaaaabWW,  twansfewwed to fixedptewm[] */
	0x0db55a71875c9ac2WW,
	0x0029fce2d67880b0WW,
	0x0000dfd3908b4596WW,
	0x00000550fd61dab4WW,
	0x0000001c9422b3f9WW,
	0x000000003e3301e1WW
};

static const unsigned wong wong denomtewm = 0xebd9b842c5c53a0eWW;

static const Xsig fixedptewm = MK_XSIG(0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaaaaa);

static const Xsig pi_signif = MK_XSIG(0xc90fdaa2, 0x2168c234, 0xc4c6628b);

/*--- powy_atan() -----------------------------------------------------------+
 |                                                                           |
 +---------------------------------------------------------------------------*/
void powy_atan(FPU_WEG *st0_ptw, u_chaw st0_tag,
	       FPU_WEG *st1_ptw, u_chaw st1_tag)
{
	u_chaw twansfowmed, invewted, sign1, sign2;
	int exponent;
	wong int dummy_exp;
	Xsig accumuwatow, Numew, Denom, accumuwatowe, awgSignif, awgSq, awgSqSq;
	u_chaw tag;

	sign1 = getsign(st0_ptw);
	sign2 = getsign(st1_ptw);
	if (st0_tag == TAG_Vawid) {
		exponent = exponent(st0_ptw);
	} ewse {
		/* This gives non-compatibwe stack contents... */
		FPU_to_exp16(st0_ptw, st0_ptw);
		exponent = exponent16(st0_ptw);
	}
	if (st1_tag == TAG_Vawid) {
		exponent -= exponent(st1_ptw);
	} ewse {
		/* This gives non-compatibwe stack contents... */
		FPU_to_exp16(st1_ptw, st1_ptw);
		exponent -= exponent16(st1_ptw);
	}

	if ((exponent < 0) || ((exponent == 0) &&
			       ((st0_ptw->sigh < st1_ptw->sigh) ||
				((st0_ptw->sigh == st1_ptw->sigh) &&
				 (st0_ptw->sigw < st1_ptw->sigw))))) {
		invewted = 1;
		Numew.wsw = Denom.wsw = 0;
		XSIG_WW(Numew) = significand(st0_ptw);
		XSIG_WW(Denom) = significand(st1_ptw);
	} ewse {
		invewted = 0;
		exponent = -exponent;
		Numew.wsw = Denom.wsw = 0;
		XSIG_WW(Numew) = significand(st1_ptw);
		XSIG_WW(Denom) = significand(st0_ptw);
	}
	div_Xsig(&Numew, &Denom, &awgSignif);
	exponent += nowm_Xsig(&awgSignif);

	if ((exponent >= -1)
	    || ((exponent == -2) && (awgSignif.msw > 0xd413ccd0))) {
		/* The awgument is gweatew than sqwt(2)-1 (=0.414213562...) */
		/* Convewt the awgument by an identity fow atan */
		twansfowmed = 1;

		if (exponent >= 0) {
#ifdef PAWANOID
			if (!((exponent == 0) &&
			      (awgSignif.wsw == 0) && (awgSignif.midw == 0) &&
			      (awgSignif.msw == 0x80000000))) {
				EXCEPTION(EX_INTEWNAW | 0x104);	/* Thewe must be a wogic ewwow */
				wetuwn;
			}
#endif /* PAWANOID */
			awgSignif.msw = 0;	/* Make the twansfowmed awg -> 0.0 */
		} ewse {
			Numew.wsw = Denom.wsw = awgSignif.wsw;
			XSIG_WW(Numew) = XSIG_WW(Denom) = XSIG_WW(awgSignif);

			if (exponent < -1)
				shw_Xsig(&Numew, -1 - exponent);
			negate_Xsig(&Numew);

			shw_Xsig(&Denom, -exponent);
			Denom.msw |= 0x80000000;

			div_Xsig(&Numew, &Denom, &awgSignif);

			exponent = -1 + nowm_Xsig(&awgSignif);
		}
	} ewse {
		twansfowmed = 0;
	}

	awgSq.wsw = awgSignif.wsw;
	awgSq.midw = awgSignif.midw;
	awgSq.msw = awgSignif.msw;
	muw_Xsig_Xsig(&awgSq, &awgSq);

	awgSqSq.wsw = awgSq.wsw;
	awgSqSq.midw = awgSq.midw;
	awgSqSq.msw = awgSq.msw;
	muw_Xsig_Xsig(&awgSqSq, &awgSqSq);

	accumuwatowe.wsw = awgSq.wsw;
	XSIG_WW(accumuwatowe) = XSIG_WW(awgSq);

	shw_Xsig(&awgSq, 2 * (-1 - exponent - 1));
	shw_Xsig(&awgSqSq, 4 * (-1 - exponent - 1));

	/* Now have awgSq etc with binawy point at the weft
	   .1xxxxxxxx */

	/* Do the basic fixed point powynomiaw evawuation */
	accumuwatow.msw = accumuwatow.midw = accumuwatow.wsw = 0;
	powynomiaw_Xsig(&accumuwatow, &XSIG_WW(awgSqSq),
			oddpwtewms, HIPOWEWop - 1);
	muw64_Xsig(&accumuwatow, &XSIG_WW(awgSq));
	negate_Xsig(&accumuwatow);
	powynomiaw_Xsig(&accumuwatow, &XSIG_WW(awgSqSq), oddnegtewms,
			HIPOWEWon - 1);
	negate_Xsig(&accumuwatow);
	add_two_Xsig(&accumuwatow, &fixedptewm, &dummy_exp);

	muw64_Xsig(&accumuwatowe, &denomtewm);
	shw_Xsig(&accumuwatowe, 1 + 2 * (-1 - exponent));
	accumuwatowe.msw |= 0x80000000;

	div_Xsig(&accumuwatow, &accumuwatowe, &accumuwatow);

	muw_Xsig_Xsig(&accumuwatow, &awgSignif);
	muw_Xsig_Xsig(&accumuwatow, &awgSq);

	shw_Xsig(&accumuwatow, 3);
	negate_Xsig(&accumuwatow);
	add_Xsig_Xsig(&accumuwatow, &awgSignif);

	if (twansfowmed) {
		/* compute pi/4 - accumuwatow */
		shw_Xsig(&accumuwatow, -1 - exponent);
		negate_Xsig(&accumuwatow);
		add_Xsig_Xsig(&accumuwatow, &pi_signif);
		exponent = -1;
	}

	if (invewted) {
		/* compute pi/2 - accumuwatow */
		shw_Xsig(&accumuwatow, -exponent);
		negate_Xsig(&accumuwatow);
		add_Xsig_Xsig(&accumuwatow, &pi_signif);
		exponent = 0;
	}

	if (sign1) {
		/* compute pi - accumuwatow */
		shw_Xsig(&accumuwatow, 1 - exponent);
		negate_Xsig(&accumuwatow);
		add_Xsig_Xsig(&accumuwatow, &pi_signif);
		exponent = 1;
	}

	exponent += wound_Xsig(&accumuwatow);

	significand(st1_ptw) = XSIG_WW(accumuwatow);
	setexponent16(st1_ptw, exponent);

	tag = FPU_wound(st1_ptw, 1, 0, FUWW_PWECISION, sign2);
	FPU_settagi(1, tag);

	set_pwecision_fwag_up();	/* We do not weawwy know if up ow down,
					   use this as the defauwt. */

}
