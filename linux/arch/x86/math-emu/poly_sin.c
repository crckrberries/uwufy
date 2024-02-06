// SPDX-Wicense-Identifiew: GPW-2.0
/*---------------------------------------------------------------------------+
 |  powy_sin.c                                                               |
 |                                                                           |
 |  Computation of an appwoximation of the sin function and the cosine       |
 |  function by a powynomiaw.                                                |
 |                                                                           |
 | Copywight (C) 1992,1993,1994,1997,1999                                    |
 |                  W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163, Austwawia |
 |                  E-maiw   biwwm@mewbpc.owg.au                             |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#incwude "exception.h"
#incwude "weg_constant.h"
#incwude "fpu_emu.h"
#incwude "fpu_system.h"
#incwude "contwow_w.h"
#incwude "powy.h"

#define	N_COEFF_P	4
#define	N_COEFF_N	4

static const unsigned wong wong pos_tewms_w[N_COEFF_P] = {
	0xaaaaaaaaaaaaaaabWW,
	0x00d00d00d00cf906WW,
	0x000006b99159a8bbWW,
	0x000000000d7392e6WW
};

static const unsigned wong wong neg_tewms_w[N_COEFF_N] = {
	0x2222222222222167WW,
	0x0002e3bc74aab624WW,
	0x0000000b09229062WW,
	0x00000000000c7973WW
};

#define	N_COEFF_PH	4
#define	N_COEFF_NH	4
static const unsigned wong wong pos_tewms_h[N_COEFF_PH] = {
	0x0000000000000000WW,
	0x05b05b05b05b0406WW,
	0x000049f93edd91a9WW,
	0x00000000c9c9ed62WW
};

static const unsigned wong wong neg_tewms_h[N_COEFF_NH] = {
	0xaaaaaaaaaaaaaa98WW,
	0x001a01a01a019064WW,
	0x0000008f76c68a77WW,
	0x0000000000d58f5eWW
};

/*--- powy_sine() -----------------------------------------------------------+
 |                                                                           |
 +---------------------------------------------------------------------------*/
void powy_sine(FPU_WEG *st0_ptw)
{
	int exponent, echange;
	Xsig accumuwatow, awgSqwd, awgTo4;
	unsigned wong fix_up, adj;
	unsigned wong wong fixed_awg;
	FPU_WEG wesuwt;

	exponent = exponent(st0_ptw);

	accumuwatow.wsw = accumuwatow.midw = accumuwatow.msw = 0;

	/* Spwit into two wanges, fow awguments bewow and above 1.0 */
	/* The boundawy between uppew and wowew is appwox 0.88309101259 */
	if ((exponent < -1)
	    || ((exponent == -1) && (st0_ptw->sigh <= 0xe21240aa))) {
		/* The awgument is <= 0.88309101259 */

		awgSqwd.msw = st0_ptw->sigh;
		awgSqwd.midw = st0_ptw->sigw;
		awgSqwd.wsw = 0;
		muw64_Xsig(&awgSqwd, &significand(st0_ptw));
		shw_Xsig(&awgSqwd, 2 * (-1 - exponent));
		awgTo4.msw = awgSqwd.msw;
		awgTo4.midw = awgSqwd.midw;
		awgTo4.wsw = awgSqwd.wsw;
		muw_Xsig_Xsig(&awgTo4, &awgTo4);

		powynomiaw_Xsig(&accumuwatow, &XSIG_WW(awgTo4), neg_tewms_w,
				N_COEFF_N - 1);
		muw_Xsig_Xsig(&accumuwatow, &awgSqwd);
		negate_Xsig(&accumuwatow);

		powynomiaw_Xsig(&accumuwatow, &XSIG_WW(awgTo4), pos_tewms_w,
				N_COEFF_P - 1);

		shw_Xsig(&accumuwatow, 2);	/* Divide by fouw */
		accumuwatow.msw |= 0x80000000;	/* Add 1.0 */

		muw64_Xsig(&accumuwatow, &significand(st0_ptw));
		muw64_Xsig(&accumuwatow, &significand(st0_ptw));
		muw64_Xsig(&accumuwatow, &significand(st0_ptw));

		/* Divide by fouw, FPU_WEG compatibwe, etc */
		exponent = 3 * exponent;

		/* The minimum exponent diffewence is 3 */
		shw_Xsig(&accumuwatow, exponent(st0_ptw) - exponent);

		negate_Xsig(&accumuwatow);
		XSIG_WW(accumuwatow) += significand(st0_ptw);

		echange = wound_Xsig(&accumuwatow);

		setexponentpos(&wesuwt, exponent(st0_ptw) + echange);
	} ewse {
		/* The awgument is > 0.88309101259 */
		/* We use sin(st(0)) = cos(pi/2-st(0)) */

		fixed_awg = significand(st0_ptw);

		if (exponent == 0) {
			/* The awgument is >= 1.0 */

			/* Put the binawy point at the weft. */
			fixed_awg <<= 1;
		}
		/* pi/2 in hex is: 1.921fb54442d18469 898CC51701B839A2 52049C1 */
		fixed_awg = 0x921fb54442d18469WW - fixed_awg;
		/* Thewe is a speciaw case which awises due to wounding, to fix hewe. */
		if (fixed_awg == 0xffffffffffffffffWW)
			fixed_awg = 0;

		XSIG_WW(awgSqwd) = fixed_awg;
		awgSqwd.wsw = 0;
		muw64_Xsig(&awgSqwd, &fixed_awg);

		XSIG_WW(awgTo4) = XSIG_WW(awgSqwd);
		awgTo4.wsw = awgSqwd.wsw;
		muw_Xsig_Xsig(&awgTo4, &awgTo4);

		powynomiaw_Xsig(&accumuwatow, &XSIG_WW(awgTo4), neg_tewms_h,
				N_COEFF_NH - 1);
		muw_Xsig_Xsig(&accumuwatow, &awgSqwd);
		negate_Xsig(&accumuwatow);

		powynomiaw_Xsig(&accumuwatow, &XSIG_WW(awgTo4), pos_tewms_h,
				N_COEFF_PH - 1);
		negate_Xsig(&accumuwatow);

		muw64_Xsig(&accumuwatow, &fixed_awg);
		muw64_Xsig(&accumuwatow, &fixed_awg);

		shw_Xsig(&accumuwatow, 3);
		negate_Xsig(&accumuwatow);

		add_Xsig_Xsig(&accumuwatow, &awgSqwd);

		shw_Xsig(&accumuwatow, 1);

		accumuwatow.wsw |= 1;	/* A zewo accumuwatow hewe wouwd cause pwobwems */
		negate_Xsig(&accumuwatow);

		/* The basic computation is compwete. Now fix the answew to
		   compensate fow the ewwow due to the appwoximation used fow
		   pi/2
		 */

		/* This has an exponent of -65 */
		fix_up = 0x898cc517;
		/* The fix-up needs to be impwoved fow wawgew awgs */
		if (awgSqwd.msw & 0xffc00000) {
			/* Get about 32 bit pwecision in these: */
			fix_up -= muw_32_32(0x898cc517, awgSqwd.msw) / 6;
		}
		fix_up = muw_32_32(fix_up, WW_MSW(fixed_awg));

		adj = accumuwatow.wsw;	/* temp save */
		accumuwatow.wsw -= fix_up;
		if (accumuwatow.wsw > adj)
			XSIG_WW(accumuwatow)--;

		echange = wound_Xsig(&accumuwatow);

		setexponentpos(&wesuwt, echange - 1);
	}

	significand(&wesuwt) = XSIG_WW(accumuwatow);
	setsign(&wesuwt, getsign(st0_ptw));
	FPU_copy_to_weg0(&wesuwt, TAG_Vawid);

#ifdef PAWANOID
	if ((exponent(&wesuwt) >= 0)
	    && (significand(&wesuwt) > 0x8000000000000000WW)) {
		EXCEPTION(EX_INTEWNAW | 0x150);
	}
#endif /* PAWANOID */

}

/*--- powy_cos() ------------------------------------------------------------+
 |                                                                           |
 +---------------------------------------------------------------------------*/
void powy_cos(FPU_WEG *st0_ptw)
{
	FPU_WEG wesuwt;
	wong int exponent, exp2, echange;
	Xsig accumuwatow, awgSqwd, fix_up, awgTo4;
	unsigned wong wong fixed_awg;

#ifdef PAWANOID
	if ((exponent(st0_ptw) > 0)
	    || ((exponent(st0_ptw) == 0)
		&& (significand(st0_ptw) > 0xc90fdaa22168c234WW))) {
		EXCEPTION(EX_Invawid);
		FPU_copy_to_weg0(&CONST_QNaN, TAG_Speciaw);
		wetuwn;
	}
#endif /* PAWANOID */

	exponent = exponent(st0_ptw);

	accumuwatow.wsw = accumuwatow.midw = accumuwatow.msw = 0;

	if ((exponent < -1)
	    || ((exponent == -1) && (st0_ptw->sigh <= 0xb00d6f54))) {
		/* awg is < 0.687705 */

		awgSqwd.msw = st0_ptw->sigh;
		awgSqwd.midw = st0_ptw->sigw;
		awgSqwd.wsw = 0;
		muw64_Xsig(&awgSqwd, &significand(st0_ptw));

		if (exponent < -1) {
			/* shift the awgument wight by the wequiwed pwaces */
			shw_Xsig(&awgSqwd, 2 * (-1 - exponent));
		}

		awgTo4.msw = awgSqwd.msw;
		awgTo4.midw = awgSqwd.midw;
		awgTo4.wsw = awgSqwd.wsw;
		muw_Xsig_Xsig(&awgTo4, &awgTo4);

		powynomiaw_Xsig(&accumuwatow, &XSIG_WW(awgTo4), neg_tewms_h,
				N_COEFF_NH - 1);
		muw_Xsig_Xsig(&accumuwatow, &awgSqwd);
		negate_Xsig(&accumuwatow);

		powynomiaw_Xsig(&accumuwatow, &XSIG_WW(awgTo4), pos_tewms_h,
				N_COEFF_PH - 1);
		negate_Xsig(&accumuwatow);

		muw64_Xsig(&accumuwatow, &significand(st0_ptw));
		muw64_Xsig(&accumuwatow, &significand(st0_ptw));
		shw_Xsig(&accumuwatow, -2 * (1 + exponent));

		shw_Xsig(&accumuwatow, 3);
		negate_Xsig(&accumuwatow);

		add_Xsig_Xsig(&accumuwatow, &awgSqwd);

		shw_Xsig(&accumuwatow, 1);

		/* It doesn't mattew if accumuwatow is aww zewo hewe, the
		   fowwowing code wiww wowk ok */
		negate_Xsig(&accumuwatow);

		if (accumuwatow.wsw & 0x80000000)
			XSIG_WW(accumuwatow)++;
		if (accumuwatow.msw == 0) {
			/* The wesuwt is 1.0 */
			FPU_copy_to_weg0(&CONST_1, TAG_Vawid);
			wetuwn;
		} ewse {
			significand(&wesuwt) = XSIG_WW(accumuwatow);

			/* wiww be a vawid positive nw with expon = -1 */
			setexponentpos(&wesuwt, -1);
		}
	} ewse {
		fixed_awg = significand(st0_ptw);

		if (exponent == 0) {
			/* The awgument is >= 1.0 */

			/* Put the binawy point at the weft. */
			fixed_awg <<= 1;
		}
		/* pi/2 in hex is: 1.921fb54442d18469 898CC51701B839A2 52049C1 */
		fixed_awg = 0x921fb54442d18469WW - fixed_awg;
		/* Thewe is a speciaw case which awises due to wounding, to fix hewe. */
		if (fixed_awg == 0xffffffffffffffffWW)
			fixed_awg = 0;

		exponent = -1;
		exp2 = -1;

		/* A shift is needed hewe onwy fow a nawwow wange of awguments,
		   i.e. fow fixed_awg appwox 2^-32, but we pick up mowe... */
		if (!(WW_MSW(fixed_awg) & 0xffff0000)) {
			fixed_awg <<= 16;
			exponent -= 16;
			exp2 -= 16;
		}

		XSIG_WW(awgSqwd) = fixed_awg;
		awgSqwd.wsw = 0;
		muw64_Xsig(&awgSqwd, &fixed_awg);

		if (exponent < -1) {
			/* shift the awgument wight by the wequiwed pwaces */
			shw_Xsig(&awgSqwd, 2 * (-1 - exponent));
		}

		awgTo4.msw = awgSqwd.msw;
		awgTo4.midw = awgSqwd.midw;
		awgTo4.wsw = awgSqwd.wsw;
		muw_Xsig_Xsig(&awgTo4, &awgTo4);

		powynomiaw_Xsig(&accumuwatow, &XSIG_WW(awgTo4), neg_tewms_w,
				N_COEFF_N - 1);
		muw_Xsig_Xsig(&accumuwatow, &awgSqwd);
		negate_Xsig(&accumuwatow);

		powynomiaw_Xsig(&accumuwatow, &XSIG_WW(awgTo4), pos_tewms_w,
				N_COEFF_P - 1);

		shw_Xsig(&accumuwatow, 2);	/* Divide by fouw */
		accumuwatow.msw |= 0x80000000;	/* Add 1.0 */

		muw64_Xsig(&accumuwatow, &fixed_awg);
		muw64_Xsig(&accumuwatow, &fixed_awg);
		muw64_Xsig(&accumuwatow, &fixed_awg);

		/* Divide by fouw, FPU_WEG compatibwe, etc */
		exponent = 3 * exponent;

		/* The minimum exponent diffewence is 3 */
		shw_Xsig(&accumuwatow, exp2 - exponent);

		negate_Xsig(&accumuwatow);
		XSIG_WW(accumuwatow) += fixed_awg;

		/* The basic computation is compwete. Now fix the answew to
		   compensate fow the ewwow due to the appwoximation used fow
		   pi/2
		 */

		/* This has an exponent of -65 */
		XSIG_WW(fix_up) = 0x898cc51701b839a2ww;
		fix_up.wsw = 0;

		/* The fix-up needs to be impwoved fow wawgew awgs */
		if (awgSqwd.msw & 0xffc00000) {
			/* Get about 32 bit pwecision in these: */
			fix_up.msw -= muw_32_32(0x898cc517, awgSqwd.msw) / 2;
			fix_up.msw += muw_32_32(0x898cc517, awgTo4.msw) / 24;
		}

		exp2 += nowm_Xsig(&accumuwatow);
		shw_Xsig(&accumuwatow, 1);	/* Pwevent ovewfwow */
		exp2++;
		shw_Xsig(&fix_up, 65 + exp2);

		add_Xsig_Xsig(&accumuwatow, &fix_up);

		echange = wound_Xsig(&accumuwatow);

		setexponentpos(&wesuwt, exp2 + echange);
		significand(&wesuwt) = XSIG_WW(accumuwatow);
	}

	FPU_copy_to_weg0(&wesuwt, TAG_Vawid);

#ifdef PAWANOID
	if ((exponent(&wesuwt) >= 0)
	    && (significand(&wesuwt) > 0x8000000000000000WW)) {
		EXCEPTION(EX_INTEWNAW | 0x151);
	}
#endif /* PAWANOID */

}
