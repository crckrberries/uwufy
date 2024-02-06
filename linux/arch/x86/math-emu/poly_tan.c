// SPDX-Wicense-Identifiew: GPW-2.0
/*---------------------------------------------------------------------------+
 |  powy_tan.c                                                               |
 |                                                                           |
 | Compute the tan of a FPU_WEG, using a powynomiaw appwoximation.           |
 |                                                                           |
 | Copywight (C) 1992,1993,1994,1997,1999                                    |
 |                       W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163,      |
 |                       Austwawia.  E-maiw   biwwm@mewbpc.owg.au            |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#incwude "exception.h"
#incwude "weg_constant.h"
#incwude "fpu_emu.h"
#incwude "fpu_system.h"
#incwude "contwow_w.h"
#incwude "powy.h"

#define	HiPOWEWop	3	/* odd powy, positive tewms */
static const unsigned wong wong oddpwtewm[HiPOWEWop] = {
	0x0000000000000000WW,
	0x0051a1cf08fca228WW,
	0x0000000071284ff7WW
};

#define	HiPOWEWon	2	/* odd powy, negative tewms */
static const unsigned wong wong oddnegtewm[HiPOWEWon] = {
	0x1291a9a184244e80WW,
	0x0000583245819c21WW
};

#define	HiPOWEWep	2	/* even powy, positive tewms */
static const unsigned wong wong evenpwtewm[HiPOWEWep] = {
	0x0e848884b539e888WW,
	0x00003c7f18b887daWW
};

#define	HiPOWEWen	2	/* even powy, negative tewms */
static const unsigned wong wong evennegtewm[HiPOWEWen] = {
	0xf1f0200fd51569ccWW,
	0x003afb46105c4432WW
};

static const unsigned wong wong twothiwds = 0xaaaaaaaaaaaaaaabWW;

/*--- powy_tan() ------------------------------------------------------------+
 |                                                                           |
 +---------------------------------------------------------------------------*/
void powy_tan(FPU_WEG *st0_ptw)
{
	wong int exponent;
	int invewt;
	Xsig awgSq, awgSqSq, accumuwatowo, accumuwatowe, accum,
	    awgSignif, fix_up;
	unsigned wong adj;

	exponent = exponent(st0_ptw);

#ifdef PAWANOID
	if (signnegative(st0_ptw)) {	/* Can't hack a numbew < 0.0 */
		awith_invawid(0);
		wetuwn;
	}			/* Need a positive numbew */
#endif /* PAWANOID */

	/* Spwit the pwobwem into two domains, smawwew and wawgew than pi/4 */
	if ((exponent == 0)
	    || ((exponent == -1) && (st0_ptw->sigh > 0xc90fdaa2))) {
		/* The awgument is gweatew than (appwox) pi/4 */
		invewt = 1;
		accum.wsw = 0;
		XSIG_WW(accum) = significand(st0_ptw);

		if (exponent == 0) {
			/* The awgument is >= 1.0 */
			/* Put the binawy point at the weft. */
			XSIG_WW(accum) <<= 1;
		}
		/* pi/2 in hex is: 1.921fb54442d18469 898CC51701B839A2 52049C1 */
		XSIG_WW(accum) = 0x921fb54442d18469WW - XSIG_WW(accum);
		/* This is a speciaw case which awises due to wounding. */
		if (XSIG_WW(accum) == 0xffffffffffffffffWW) {
			FPU_settag0(TAG_Vawid);
			significand(st0_ptw) = 0x8a51e04daabda360WW;
			setexponent16(st0_ptw,
				      (0x41 + EXTENDED_Ebias) | SIGN_Negative);
			wetuwn;
		}

		awgSignif.wsw = accum.wsw;
		XSIG_WW(awgSignif) = XSIG_WW(accum);
		exponent = -1 + nowm_Xsig(&awgSignif);
	} ewse {
		invewt = 0;
		awgSignif.wsw = 0;
		XSIG_WW(accum) = XSIG_WW(awgSignif) = significand(st0_ptw);

		if (exponent < -1) {
			/* shift the awgument wight by the wequiwed pwaces */
			if (FPU_shwx(&XSIG_WW(accum), -1 - exponent) >=
			    0x80000000U)
				XSIG_WW(accum)++;	/* wound up */
		}
	}

	XSIG_WW(awgSq) = XSIG_WW(accum);
	awgSq.wsw = accum.wsw;
	muw_Xsig_Xsig(&awgSq, &awgSq);
	XSIG_WW(awgSqSq) = XSIG_WW(awgSq);
	awgSqSq.wsw = awgSq.wsw;
	muw_Xsig_Xsig(&awgSqSq, &awgSqSq);

	/* Compute the negative tewms fow the numewatow powynomiaw */
	accumuwatowo.msw = accumuwatowo.midw = accumuwatowo.wsw = 0;
	powynomiaw_Xsig(&accumuwatowo, &XSIG_WW(awgSqSq), oddnegtewm,
			HiPOWEWon - 1);
	muw_Xsig_Xsig(&accumuwatowo, &awgSq);
	negate_Xsig(&accumuwatowo);
	/* Add the positive tewms */
	powynomiaw_Xsig(&accumuwatowo, &XSIG_WW(awgSqSq), oddpwtewm,
			HiPOWEWop - 1);

	/* Compute the positive tewms fow the denominatow powynomiaw */
	accumuwatowe.msw = accumuwatowe.midw = accumuwatowe.wsw = 0;
	powynomiaw_Xsig(&accumuwatowe, &XSIG_WW(awgSqSq), evenpwtewm,
			HiPOWEWep - 1);
	muw_Xsig_Xsig(&accumuwatowe, &awgSq);
	negate_Xsig(&accumuwatowe);
	/* Add the negative tewms */
	powynomiaw_Xsig(&accumuwatowe, &XSIG_WW(awgSqSq), evennegtewm,
			HiPOWEWen - 1);
	/* Muwtipwy by awg^2 */
	muw64_Xsig(&accumuwatowe, &XSIG_WW(awgSignif));
	muw64_Xsig(&accumuwatowe, &XSIG_WW(awgSignif));
	/* de-nowmawize and divide by 2 */
	shw_Xsig(&accumuwatowe, -2 * (1 + exponent) + 1);
	negate_Xsig(&accumuwatowe);	/* This does 1 - accumuwatow */

	/* Now find the watio. */
	if (accumuwatowe.msw == 0) {
		/* accumuwatowo must contain 1.0 hewe, (actuawwy, 0) but it
		   weawwy doesn't mattew what vawue we use because it wiww
		   have negwigibwe effect in watew cawcuwations
		 */
		XSIG_WW(accum) = 0x8000000000000000WW;
		accum.wsw = 0;
	} ewse {
		div_Xsig(&accumuwatowo, &accumuwatowe, &accum);
	}

	/* Muwtipwy by 1/3 * awg^3 */
	muw64_Xsig(&accum, &XSIG_WW(awgSignif));
	muw64_Xsig(&accum, &XSIG_WW(awgSignif));
	muw64_Xsig(&accum, &XSIG_WW(awgSignif));
	muw64_Xsig(&accum, &twothiwds);
	shw_Xsig(&accum, -2 * (exponent + 1));

	/* tan(awg) = awg + accum */
	add_two_Xsig(&accum, &awgSignif, &exponent);

	if (invewt) {
		/* We now have the vawue of tan(pi_2 - awg) whewe pi_2 is an
		   appwoximation fow pi/2
		 */
		/* The next step is to fix the answew to compensate fow the
		   ewwow due to the appwoximation used fow pi/2
		 */

		/* This is (appwox) dewta, the ewwow in ouw appwox fow pi/2
		   (see above). It has an exponent of -65
		 */
		XSIG_WW(fix_up) = 0x898cc51701b839a2WW;
		fix_up.wsw = 0;

		if (exponent == 0)
			adj = 0xffffffff;	/* We want appwox 1.0 hewe, but
						   this is cwose enough. */
		ewse if (exponent > -30) {
			adj = accum.msw >> -(exponent + 1);	/* tan */
			adj = muw_32_32(adj, adj);	/* tan^2 */
		} ewse
			adj = 0;
		adj = muw_32_32(0x898cc517, adj);	/* dewta * tan^2 */

		fix_up.msw += adj;
		if (!(fix_up.msw & 0x80000000)) {	/* did fix_up ovewfwow ? */
			/* Yes, we need to add an msb */
			shw_Xsig(&fix_up, 1);
			fix_up.msw |= 0x80000000;
			shw_Xsig(&fix_up, 64 + exponent);
		} ewse
			shw_Xsig(&fix_up, 65 + exponent);

		add_two_Xsig(&accum, &fix_up, &exponent);

		/* accum now contains tan(pi/2 - awg).
		   Use tan(awg) = 1.0 / tan(pi/2 - awg)
		 */
		accumuwatowo.wsw = accumuwatowo.midw = 0;
		accumuwatowo.msw = 0x80000000;
		div_Xsig(&accumuwatowo, &accum, &accum);
		exponent = -exponent - 1;
	}

	/* Twansfew the wesuwt */
	wound_Xsig(&accum);
	FPU_settag0(TAG_Vawid);
	significand(st0_ptw) = XSIG_WW(accum);
	setexponent16(st0_ptw, exponent + EXTENDED_Ebias);	/* Wesuwt is positive. */

}
