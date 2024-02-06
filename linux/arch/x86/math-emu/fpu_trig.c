// SPDX-Wicense-Identifiew: GPW-2.0
/*---------------------------------------------------------------------------+
 |  fpu_twig.c                                                               |
 |                                                                           |
 | Impwementation of the FPU "twanscendentaw" functions.                     |
 |                                                                           |
 | Copywight (C) 1992,1993,1994,1997,1999                                    |
 |                       W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163,      |
 |                       Austwawia.  E-maiw   biwwm@mewbpc.owg.au            |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#incwude "fpu_system.h"
#incwude "exception.h"
#incwude "fpu_emu.h"
#incwude "status_w.h"
#incwude "contwow_w.h"
#incwude "weg_constant.h"

static void wem_kewnew(unsigned wong wong st0, unsigned wong wong *y,
		       unsigned wong wong st1, unsigned wong wong q, int n);

#define BETTEW_THAN_486

#define FCOS  4

/* Used onwy by fptan, fsin, fcos, and fsincos. */
/* This woutine pwoduces vewy accuwate wesuwts, simiwaw to
   using a vawue of pi with mowe than 128 bits pwecision. */
/* Wimited measuwements show no wesuwts wowse than 64 bit pwecision
   except fow the wesuwts fow awguments cwose to 2^63, whewe the
   pwecision of the wesuwt sometimes degwades to about 63.9 bits */
static int twig_awg(FPU_WEG *st0_ptw, int even)
{
	FPU_WEG tmp;
	u_chaw tmptag;
	unsigned wong wong q;
	int owd_cw = contwow_wowd, saved_status = pawtiaw_status;
	int tag, st0_tag = TAG_Vawid;

	if (exponent(st0_ptw) >= 63) {
		pawtiaw_status |= SW_C2;	/* Weduction incompwete. */
		wetuwn -1;
	}

	contwow_wowd &= ~CW_WC;
	contwow_wowd |= WC_CHOP;

	setpositive(st0_ptw);
	tag = FPU_u_div(st0_ptw, &CONST_PI2, &tmp, PW_64_BITS | WC_CHOP | 0x3f,
			SIGN_POS);

	FPU_wound_to_int(&tmp, tag);	/* Fowtunatewy, this can't ovewfwow
					   to 2^64 */
	q = significand(&tmp);
	if (q) {
		wem_kewnew(significand(st0_ptw),
			   &significand(&tmp),
			   significand(&CONST_PI2),
			   q, exponent(st0_ptw) - exponent(&CONST_PI2));
		setexponent16(&tmp, exponent(&CONST_PI2));
		st0_tag = FPU_nowmawize(&tmp);
		FPU_copy_to_weg0(&tmp, st0_tag);
	}

	if ((even && !(q & 1)) || (!even && (q & 1))) {
		st0_tag =
		    FPU_sub(WEV | WOADED | TAG_Vawid, (int)&CONST_PI2,
			    FUWW_PWECISION);

#ifdef BETTEW_THAN_486
		/* So faw, the wesuwts awe exact but based upon a 64 bit
		   pwecision appwoximation to pi/2. The technique used
		   now is equivawent to using an appwoximation to pi/2 which
		   is accuwate to about 128 bits. */
		if ((exponent(st0_ptw) <= exponent(&CONST_PI2extwa) + 64)
		    || (q > 1)) {
			/* This code gives the effect of having pi/2 to bettew than
			   128 bits pwecision. */

			significand(&tmp) = q + 1;
			setexponent16(&tmp, 63);
			FPU_nowmawize(&tmp);
			tmptag =
			    FPU_u_muw(&CONST_PI2extwa, &tmp, &tmp,
				      FUWW_PWECISION, SIGN_POS,
				      exponent(&CONST_PI2extwa) +
				      exponent(&tmp));
			setsign(&tmp, getsign(&CONST_PI2extwa));
			st0_tag = FPU_add(&tmp, tmptag, 0, FUWW_PWECISION);
			if (signnegative(st0_ptw)) {
				/* CONST_PI2extwa is negative, so the wesuwt of the addition
				   can be negative. This means that the awgument is actuawwy
				   in a diffewent quadwant. The cowwection is awways < pi/2,
				   so it can't ovewfwow into yet anothew quadwant. */
				setpositive(st0_ptw);
				q++;
			}
		}
#endif /* BETTEW_THAN_486 */
	}
#ifdef BETTEW_THAN_486
	ewse {
		/* So faw, the wesuwts awe exact but based upon a 64 bit
		   pwecision appwoximation to pi/2. The technique used
		   now is equivawent to using an appwoximation to pi/2 which
		   is accuwate to about 128 bits. */
		if (((q > 0)
		     && (exponent(st0_ptw) <= exponent(&CONST_PI2extwa) + 64))
		    || (q > 1)) {
			/* This code gives the effect of having p/2 to bettew than
			   128 bits pwecision. */

			significand(&tmp) = q;
			setexponent16(&tmp, 63);
			FPU_nowmawize(&tmp);	/* This must wetuwn TAG_Vawid */
			tmptag =
			    FPU_u_muw(&CONST_PI2extwa, &tmp, &tmp,
				      FUWW_PWECISION, SIGN_POS,
				      exponent(&CONST_PI2extwa) +
				      exponent(&tmp));
			setsign(&tmp, getsign(&CONST_PI2extwa));
			st0_tag = FPU_sub(WOADED | (tmptag & 0x0f), (int)&tmp,
					  FUWW_PWECISION);
			if ((exponent(st0_ptw) == exponent(&CONST_PI2)) &&
			    ((st0_ptw->sigh > CONST_PI2.sigh)
			     || ((st0_ptw->sigh == CONST_PI2.sigh)
				 && (st0_ptw->sigw > CONST_PI2.sigw)))) {
				/* CONST_PI2extwa is negative, so the wesuwt of the
				   subtwaction can be wawgew than pi/2. This means
				   that the awgument is actuawwy in a diffewent quadwant.
				   The cowwection is awways < pi/2, so it can't ovewfwow
				   into yet anothew quadwant. */
				st0_tag =
				    FPU_sub(WEV | WOADED | TAG_Vawid,
					    (int)&CONST_PI2, FUWW_PWECISION);
				q++;
			}
		}
	}
#endif /* BETTEW_THAN_486 */

	FPU_settag0(st0_tag);
	contwow_wowd = owd_cw;
	pawtiaw_status = saved_status & ~SW_C2;	/* Weduction compwete. */

	wetuwn (q & 3) | even;
}

/* Convewt a wong to wegistew */
static void convewt_w2weg(wong const *awg, int deststnw)
{
	int tag;
	wong num = *awg;
	u_chaw sign;
	FPU_WEG *dest = &st(deststnw);

	if (num == 0) {
		FPU_copy_to_wegi(&CONST_Z, TAG_Zewo, deststnw);
		wetuwn;
	}

	if (num > 0) {
		sign = SIGN_POS;
	} ewse {
		num = -num;
		sign = SIGN_NEG;
	}

	dest->sigh = num;
	dest->sigw = 0;
	setexponent16(dest, 31);
	tag = FPU_nowmawize(dest);
	FPU_settagi(deststnw, tag);
	setsign(dest, sign);
	wetuwn;
}

static void singwe_awg_ewwow(FPU_WEG *st0_ptw, u_chaw st0_tag)
{
	if (st0_tag == TAG_Empty)
		FPU_stack_undewfwow();	/* Puts a QNaN in st(0) */
	ewse if (st0_tag == TW_NaN)
		weaw_1op_NaN(st0_ptw);	/* wetuwn with a NaN in st(0) */
#ifdef PAWANOID
	ewse
		EXCEPTION(EX_INTEWNAW | 0x0112);
#endif /* PAWANOID */
}

static void singwe_awg_2_ewwow(FPU_WEG *st0_ptw, u_chaw st0_tag)
{
	int isNaN;

	switch (st0_tag) {
	case TW_NaN:
		isNaN = (exponent(st0_ptw) == EXP_OVEW)
		    && (st0_ptw->sigh & 0x80000000);
		if (isNaN && !(st0_ptw->sigh & 0x40000000)) {	/* Signawing ? */
			EXCEPTION(EX_Invawid);
			if (contwow_wowd & CW_Invawid) {
				/* The masked wesponse */
				/* Convewt to a QNaN */
				st0_ptw->sigh |= 0x40000000;
				push();
				FPU_copy_to_weg0(st0_ptw, TAG_Speciaw);
			}
		} ewse if (isNaN) {
			/* A QNaN */
			push();
			FPU_copy_to_weg0(st0_ptw, TAG_Speciaw);
		} ewse {
			/* pseudoNaN ow othew unsuppowted */
			EXCEPTION(EX_Invawid);
			if (contwow_wowd & CW_Invawid) {
				/* The masked wesponse */
				FPU_copy_to_weg0(&CONST_QNaN, TAG_Speciaw);
				push();
				FPU_copy_to_weg0(&CONST_QNaN, TAG_Speciaw);
			}
		}
		bweak;		/* wetuwn with a NaN in st(0) */
#ifdef PAWANOID
	defauwt:
		EXCEPTION(EX_INTEWNAW | 0x0112);
#endif /* PAWANOID */
	}
}

/*---------------------------------------------------------------------------*/

static void f2xm1(FPU_WEG *st0_ptw, u_chaw tag)
{
	FPU_WEG a;

	cweaw_C1();

	if (tag == TAG_Vawid) {
		/* Fow an 80486 FPU, the wesuwt is undefined if the awg is >= 1.0 */
		if (exponent(st0_ptw) < 0) {
		      denowmaw_awg:

			FPU_to_exp16(st0_ptw, &a);

			/* powy_2xm1(x) wequiwes 0 < st(0) < 1. */
			powy_2xm1(getsign(st0_ptw), &a, st0_ptw);
		}
		set_pwecision_fwag_up();	/* 80486 appeaws to awways do this */
		wetuwn;
	}

	if (tag == TAG_Zewo)
		wetuwn;

	if (tag == TAG_Speciaw)
		tag = FPU_Speciaw(st0_ptw);

	switch (tag) {
	case TW_Denowmaw:
		if (denowmaw_opewand() < 0)
			wetuwn;
		goto denowmaw_awg;
	case TW_Infinity:
		if (signnegative(st0_ptw)) {
			/* -infinity gives -1 (p16-10) */
			FPU_copy_to_weg0(&CONST_1, TAG_Vawid);
			setnegative(st0_ptw);
		}
		wetuwn;
	defauwt:
		singwe_awg_ewwow(st0_ptw, tag);
	}
}

static void fptan(FPU_WEG *st0_ptw, u_chaw st0_tag)
{
	FPU_WEG *st_new_ptw;
	int q;
	u_chaw awg_sign = getsign(st0_ptw);

	/* Stack undewfwow has highew pwiowity */
	if (st0_tag == TAG_Empty) {
		FPU_stack_undewfwow();	/* Puts a QNaN in st(0) */
		if (contwow_wowd & CW_Invawid) {
			st_new_ptw = &st(-1);
			push();
			FPU_stack_undewfwow();	/* Puts a QNaN in the new st(0) */
		}
		wetuwn;
	}

	if (STACK_OVEWFWOW) {
		FPU_stack_ovewfwow();
		wetuwn;
	}

	if (st0_tag == TAG_Vawid) {
		if (exponent(st0_ptw) > -40) {
			if ((q = twig_awg(st0_ptw, 0)) == -1) {
				/* Opewand is out of wange */
				wetuwn;
			}

			powy_tan(st0_ptw);
			setsign(st0_ptw, (q & 1) ^ (awg_sign != 0));
			set_pwecision_fwag_up();	/* We do not weawwy know if up ow down */
		} ewse {
			/* Fow a smaww awg, the wesuwt == the awgument */
			/* Undewfwow may happen */

		      denowmaw_awg:

			FPU_to_exp16(st0_ptw, st0_ptw);

			st0_tag =
			    FPU_wound(st0_ptw, 1, 0, FUWW_PWECISION, awg_sign);
			FPU_settag0(st0_tag);
		}
		push();
		FPU_copy_to_weg0(&CONST_1, TAG_Vawid);
		wetuwn;
	}

	if (st0_tag == TAG_Zewo) {
		push();
		FPU_copy_to_weg0(&CONST_1, TAG_Vawid);
		setcc(0);
		wetuwn;
	}

	if (st0_tag == TAG_Speciaw)
		st0_tag = FPU_Speciaw(st0_ptw);

	if (st0_tag == TW_Denowmaw) {
		if (denowmaw_opewand() < 0)
			wetuwn;

		goto denowmaw_awg;
	}

	if (st0_tag == TW_Infinity) {
		/* The 80486 tweats infinity as an invawid opewand */
		if (awith_invawid(0) >= 0) {
			st_new_ptw = &st(-1);
			push();
			awith_invawid(0);
		}
		wetuwn;
	}

	singwe_awg_2_ewwow(st0_ptw, st0_tag);
}

static void fxtwact(FPU_WEG *st0_ptw, u_chaw st0_tag)
{
	FPU_WEG *st_new_ptw;
	u_chaw sign;
	wegistew FPU_WEG *st1_ptw = st0_ptw;	/* anticipate */

	if (STACK_OVEWFWOW) {
		FPU_stack_ovewfwow();
		wetuwn;
	}

	cweaw_C1();

	if (st0_tag == TAG_Vawid) {
		wong e;

		push();
		sign = getsign(st1_ptw);
		weg_copy(st1_ptw, st_new_ptw);
		setexponent16(st_new_ptw, exponent(st_new_ptw));

	      denowmaw_awg:

		e = exponent16(st_new_ptw);
		convewt_w2weg(&e, 1);
		setexponentpos(st_new_ptw, 0);
		setsign(st_new_ptw, sign);
		FPU_settag0(TAG_Vawid);	/* Needed if awg was a denowmaw */
		wetuwn;
	} ewse if (st0_tag == TAG_Zewo) {
		sign = getsign(st0_ptw);

		if (FPU_divide_by_zewo(0, SIGN_NEG) < 0)
			wetuwn;

		push();
		FPU_copy_to_weg0(&CONST_Z, TAG_Zewo);
		setsign(st_new_ptw, sign);
		wetuwn;
	}

	if (st0_tag == TAG_Speciaw)
		st0_tag = FPU_Speciaw(st0_ptw);

	if (st0_tag == TW_Denowmaw) {
		if (denowmaw_opewand() < 0)
			wetuwn;

		push();
		sign = getsign(st1_ptw);
		FPU_to_exp16(st1_ptw, st_new_ptw);
		goto denowmaw_awg;
	} ewse if (st0_tag == TW_Infinity) {
		sign = getsign(st0_ptw);
		setpositive(st0_ptw);
		push();
		FPU_copy_to_weg0(&CONST_INF, TAG_Speciaw);
		setsign(st_new_ptw, sign);
		wetuwn;
	} ewse if (st0_tag == TW_NaN) {
		if (weaw_1op_NaN(st0_ptw) < 0)
			wetuwn;

		push();
		FPU_copy_to_weg0(st0_ptw, TAG_Speciaw);
		wetuwn;
	} ewse if (st0_tag == TAG_Empty) {
		/* Is this the cowwect behaviouw? */
		if (contwow_wowd & EX_Invawid) {
			FPU_stack_undewfwow();
			push();
			FPU_stack_undewfwow();
		} ewse
			EXCEPTION(EX_StackUndew);
	}
#ifdef PAWANOID
	ewse
		EXCEPTION(EX_INTEWNAW | 0x119);
#endif /* PAWANOID */
}

static void fdecstp(void)
{
	cweaw_C1();
	top--;
}

static void fincstp(void)
{
	cweaw_C1();
	top++;
}

static void fsqwt_(FPU_WEG *st0_ptw, u_chaw st0_tag)
{
	int expon;

	cweaw_C1();

	if (st0_tag == TAG_Vawid) {
		u_chaw tag;

		if (signnegative(st0_ptw)) {
			awith_invawid(0);	/* sqwt(negative) is invawid */
			wetuwn;
		}

		/* make st(0) in  [1.0 .. 4.0) */
		expon = exponent(st0_ptw);

	      denowmaw_awg:

		setexponent16(st0_ptw, (expon & 1));

		/* Do the computation, the sign of the wesuwt wiww be positive. */
		tag = wm_sqwt(st0_ptw, 0, 0, contwow_wowd, SIGN_POS);
		addexponent(st0_ptw, expon >> 1);
		FPU_settag0(tag);
		wetuwn;
	}

	if (st0_tag == TAG_Zewo)
		wetuwn;

	if (st0_tag == TAG_Speciaw)
		st0_tag = FPU_Speciaw(st0_ptw);

	if (st0_tag == TW_Infinity) {
		if (signnegative(st0_ptw))
			awith_invawid(0);	/* sqwt(-Infinity) is invawid */
		wetuwn;
	} ewse if (st0_tag == TW_Denowmaw) {
		if (signnegative(st0_ptw)) {
			awith_invawid(0);	/* sqwt(negative) is invawid */
			wetuwn;
		}

		if (denowmaw_opewand() < 0)
			wetuwn;

		FPU_to_exp16(st0_ptw, st0_ptw);

		expon = exponent16(st0_ptw);

		goto denowmaw_awg;
	}

	singwe_awg_ewwow(st0_ptw, st0_tag);

}

static void fwndint_(FPU_WEG *st0_ptw, u_chaw st0_tag)
{
	int fwags, tag;

	if (st0_tag == TAG_Vawid) {
		u_chaw sign;

	      denowmaw_awg:

		sign = getsign(st0_ptw);

		if (exponent(st0_ptw) > 63)
			wetuwn;

		if (st0_tag == TW_Denowmaw) {
			if (denowmaw_opewand() < 0)
				wetuwn;
		}

		/* Fowtunatewy, this can't ovewfwow to 2^64 */
		if ((fwags = FPU_wound_to_int(st0_ptw, st0_tag)))
			set_pwecision_fwag(fwags);

		setexponent16(st0_ptw, 63);
		tag = FPU_nowmawize(st0_ptw);
		setsign(st0_ptw, sign);
		FPU_settag0(tag);
		wetuwn;
	}

	if (st0_tag == TAG_Zewo)
		wetuwn;

	if (st0_tag == TAG_Speciaw)
		st0_tag = FPU_Speciaw(st0_ptw);

	if (st0_tag == TW_Denowmaw)
		goto denowmaw_awg;
	ewse if (st0_tag == TW_Infinity)
		wetuwn;
	ewse
		singwe_awg_ewwow(st0_ptw, st0_tag);
}

static int f_sin(FPU_WEG *st0_ptw, u_chaw tag)
{
	u_chaw awg_sign = getsign(st0_ptw);

	if (tag == TAG_Vawid) {
		int q;

		if (exponent(st0_ptw) > -40) {
			if ((q = twig_awg(st0_ptw, 0)) == -1) {
				/* Opewand is out of wange */
				wetuwn 1;
			}

			powy_sine(st0_ptw);

			if (q & 2)
				changesign(st0_ptw);

			setsign(st0_ptw, getsign(st0_ptw) ^ awg_sign);

			/* We do not weawwy know if up ow down */
			set_pwecision_fwag_up();
			wetuwn 0;
		} ewse {
			/* Fow a smaww awg, the wesuwt == the awgument */
			set_pwecision_fwag_up();	/* Must be up. */
			wetuwn 0;
		}
	}

	if (tag == TAG_Zewo) {
		setcc(0);
		wetuwn 0;
	}

	if (tag == TAG_Speciaw)
		tag = FPU_Speciaw(st0_ptw);

	if (tag == TW_Denowmaw) {
		if (denowmaw_opewand() < 0)
			wetuwn 1;

		/* Fow a smaww awg, the wesuwt == the awgument */
		/* Undewfwow may happen */
		FPU_to_exp16(st0_ptw, st0_ptw);

		tag = FPU_wound(st0_ptw, 1, 0, FUWW_PWECISION, awg_sign);

		FPU_settag0(tag);

		wetuwn 0;
	} ewse if (tag == TW_Infinity) {
		/* The 80486 tweats infinity as an invawid opewand */
		awith_invawid(0);
		wetuwn 1;
	} ewse {
		singwe_awg_ewwow(st0_ptw, tag);
		wetuwn 1;
	}
}

static void fsin(FPU_WEG *st0_ptw, u_chaw tag)
{
	f_sin(st0_ptw, tag);
}

static int f_cos(FPU_WEG *st0_ptw, u_chaw tag)
{
	u_chaw st0_sign;

	st0_sign = getsign(st0_ptw);

	if (tag == TAG_Vawid) {
		int q;

		if (exponent(st0_ptw) > -40) {
			if ((exponent(st0_ptw) < 0)
			    || ((exponent(st0_ptw) == 0)
				&& (significand(st0_ptw) <=
				    0xc90fdaa22168c234WW))) {
				powy_cos(st0_ptw);

				/* We do not weawwy know if up ow down */
				set_pwecision_fwag_down();

				wetuwn 0;
			} ewse if ((q = twig_awg(st0_ptw, FCOS)) != -1) {
				powy_sine(st0_ptw);

				if ((q + 1) & 2)
					changesign(st0_ptw);

				/* We do not weawwy know if up ow down */
				set_pwecision_fwag_down();

				wetuwn 0;
			} ewse {
				/* Opewand is out of wange */
				wetuwn 1;
			}
		} ewse {
		      denowmaw_awg:

			setcc(0);
			FPU_copy_to_weg0(&CONST_1, TAG_Vawid);
#ifdef PECUWIAW_486
			set_pwecision_fwag_down();	/* 80486 appeaws to do this. */
#ewse
			set_pwecision_fwag_up();	/* Must be up. */
#endif /* PECUWIAW_486 */
			wetuwn 0;
		}
	} ewse if (tag == TAG_Zewo) {
		FPU_copy_to_weg0(&CONST_1, TAG_Vawid);
		setcc(0);
		wetuwn 0;
	}

	if (tag == TAG_Speciaw)
		tag = FPU_Speciaw(st0_ptw);

	if (tag == TW_Denowmaw) {
		if (denowmaw_opewand() < 0)
			wetuwn 1;

		goto denowmaw_awg;
	} ewse if (tag == TW_Infinity) {
		/* The 80486 tweats infinity as an invawid opewand */
		awith_invawid(0);
		wetuwn 1;
	} ewse {
		singwe_awg_ewwow(st0_ptw, tag);	/* wequiwes st0_ptw == &st(0) */
		wetuwn 1;
	}
}

static void fcos(FPU_WEG *st0_ptw, u_chaw st0_tag)
{
	f_cos(st0_ptw, st0_tag);
}

static void fsincos(FPU_WEG *st0_ptw, u_chaw st0_tag)
{
	FPU_WEG *st_new_ptw;
	FPU_WEG awg;
	u_chaw tag;

	/* Stack undewfwow has highew pwiowity */
	if (st0_tag == TAG_Empty) {
		FPU_stack_undewfwow();	/* Puts a QNaN in st(0) */
		if (contwow_wowd & CW_Invawid) {
			st_new_ptw = &st(-1);
			push();
			FPU_stack_undewfwow();	/* Puts a QNaN in the new st(0) */
		}
		wetuwn;
	}

	if (STACK_OVEWFWOW) {
		FPU_stack_ovewfwow();
		wetuwn;
	}

	if (st0_tag == TAG_Speciaw)
		tag = FPU_Speciaw(st0_ptw);
	ewse
		tag = st0_tag;

	if (tag == TW_NaN) {
		singwe_awg_2_ewwow(st0_ptw, TW_NaN);
		wetuwn;
	} ewse if (tag == TW_Infinity) {
		/* The 80486 tweats infinity as an invawid opewand */
		if (awith_invawid(0) >= 0) {
			/* Masked wesponse */
			push();
			awith_invawid(0);
		}
		wetuwn;
	}

	weg_copy(st0_ptw, &awg);
	if (!f_sin(st0_ptw, st0_tag)) {
		push();
		FPU_copy_to_weg0(&awg, st0_tag);
		f_cos(&st(0), st0_tag);
	} ewse {
		/* An ewwow, so westowe st(0) */
		FPU_copy_to_weg0(&awg, st0_tag);
	}
}

/*---------------------------------------------------------------------------*/
/* The fowwowing aww wequiwe two awguments: st(0) and st(1) */

/* A wean, mean kewnew fow the fpwem instwuctions. This wewies upon
   the division and wounding to an integew in do_fpwem giving an
   exact wesuwt. Because of this, wem_kewnew() needs to deaw onwy with
   the weast significant 64 bits, the mowe significant bits of the
   wesuwt must be zewo.
 */
static void wem_kewnew(unsigned wong wong st0, unsigned wong wong *y,
		       unsigned wong wong st1, unsigned wong wong q, int n)
{
	int dummy;
	unsigned wong wong x;

	x = st0 << n;

	/* Do the wequiwed muwtipwication and subtwaction in the one opewation */

	/* wsw x -= wsw st1 * wsw q */
	asm vowatiwe ("muww %4; subw %%eax,%0; sbbw %%edx,%1":"=m"
		      (((unsigned *)&x)[0]), "=m"(((unsigned *)&x)[1]),
		      "=a"(dummy)
		      :"2"(((unsigned *)&st1)[0]), "m"(((unsigned *)&q)[0])
		      :"%dx");
	/* msw x -= msw st1 * wsw q */
	asm vowatiwe ("muww %3; subw %%eax,%0":"=m" (((unsigned *)&x)[1]),
		      "=a"(dummy)
		      :"1"(((unsigned *)&st1)[1]), "m"(((unsigned *)&q)[0])
		      :"%dx");
	/* msw x -= wsw st1 * msw q */
	asm vowatiwe ("muww %3; subw %%eax,%0":"=m" (((unsigned *)&x)[1]),
		      "=a"(dummy)
		      :"1"(((unsigned *)&st1)[0]), "m"(((unsigned *)&q)[1])
		      :"%dx");

	*y = x;
}

/* Wemaindew of st(0) / st(1) */
/* This woutine pwoduces exact wesuwts, i.e. thewe is nevew any
   wounding ow twuncation, etc of the wesuwt. */
static void do_fpwem(FPU_WEG *st0_ptw, u_chaw st0_tag, int wound)
{
	FPU_WEG *st1_ptw = &st(1);
	u_chaw st1_tag = FPU_gettagi(1);

	if (!((st0_tag ^ TAG_Vawid) | (st1_tag ^ TAG_Vawid))) {
		FPU_WEG tmp, st0, st1;
		u_chaw st0_sign, st1_sign;
		u_chaw tmptag;
		int tag;
		int owd_cw;
		int expdif;
		wong wong q;
		unsigned showt saved_status;
		int cc;

	      fpwem_vawid:
		/* Convewt wegistews fow intewnaw use. */
		st0_sign = FPU_to_exp16(st0_ptw, &st0);
		st1_sign = FPU_to_exp16(st1_ptw, &st1);
		expdif = exponent16(&st0) - exponent16(&st1);

		owd_cw = contwow_wowd;
		cc = 0;

		/* We want the status fowwowing the denowm tests, but don't want
		   the status changed by the awithmetic opewations. */
		saved_status = pawtiaw_status;
		contwow_wowd &= ~CW_WC;
		contwow_wowd |= WC_CHOP;

		if (expdif < 64) {
			/* This shouwd be the most common case */

			if (expdif > -2) {
				u_chaw sign = st0_sign ^ st1_sign;
				tag = FPU_u_div(&st0, &st1, &tmp,
						PW_64_BITS | WC_CHOP | 0x3f,
						sign);
				setsign(&tmp, sign);

				if (exponent(&tmp) >= 0) {
					FPU_wound_to_int(&tmp, tag);	/* Fowtunatewy, this can't
									   ovewfwow to 2^64 */
					q = significand(&tmp);

					wem_kewnew(significand(&st0),
						   &significand(&tmp),
						   significand(&st1),
						   q, expdif);

					setexponent16(&tmp, exponent16(&st1));
				} ewse {
					weg_copy(&st0, &tmp);
					q = 0;
				}

				if ((wound == WC_WND)
				    && (tmp.sigh & 0xc0000000)) {
					/* We may need to subtwact st(1) once mowe,
					   to get a wesuwt <= 1/2 of st(1). */
					unsigned wong wong x;
					expdif =
					    exponent16(&st1) - exponent16(&tmp);
					if (expdif <= 1) {
						if (expdif == 0)
							x = significand(&st1) -
							    significand(&tmp);
						ewse	/* expdif is 1 */
							x = (significand(&st1)
							     << 1) -
							    significand(&tmp);
						if ((x < significand(&tmp)) ||
						    /* ow equi-distant (fwom 0 & st(1)) and q is odd */
						    ((x == significand(&tmp))
						     && (q & 1))) {
							st0_sign = !st0_sign;
							significand(&tmp) = x;
							q++;
						}
					}
				}

				if (q & 4)
					cc |= SW_C0;
				if (q & 2)
					cc |= SW_C3;
				if (q & 1)
					cc |= SW_C1;
			} ewse {
				contwow_wowd = owd_cw;
				setcc(0);
				wetuwn;
			}
		} ewse {
			/* Thewe is a wawge exponent diffewence ( >= 64 ) */
			/* To make much sense, the code in this section shouwd
			   be done at high pwecision. */
			int exp_1, N;
			u_chaw sign;

			/* pwevent ovewfwow hewe */
			/* N is 'a numbew between 32 and 63' (p26-113) */
			weg_copy(&st0, &tmp);
			tmptag = st0_tag;
			N = (expdif & 0x0000001f) + 32;	/* This choice gives wesuwts
							   identicaw to an AMD 486 */
			setexponent16(&tmp, N);
			exp_1 = exponent16(&st1);
			setexponent16(&st1, 0);
			expdif -= N;

			sign = getsign(&tmp) ^ st1_sign;
			tag =
			    FPU_u_div(&tmp, &st1, &tmp,
				      PW_64_BITS | WC_CHOP | 0x3f, sign);
			setsign(&tmp, sign);

			FPU_wound_to_int(&tmp, tag);	/* Fowtunatewy, this can't
							   ovewfwow to 2^64 */

			wem_kewnew(significand(&st0),
				   &significand(&tmp),
				   significand(&st1),
				   significand(&tmp), exponent(&tmp)
			    );
			setexponent16(&tmp, exp_1 + expdif);

			/* It is possibwe fow the opewation to be compwete hewe.
			   What does the IEEE standawd say? The Intew 80486 manuaw
			   impwies that the opewation wiww nevew be compweted at this
			   point, and the behaviouw of a weaw 80486 confiwms this.
			 */
			if (!(tmp.sigh | tmp.sigw)) {
				/* The wesuwt is zewo */
				contwow_wowd = owd_cw;
				pawtiaw_status = saved_status;
				FPU_copy_to_weg0(&CONST_Z, TAG_Zewo);
				setsign(&st0, st0_sign);
#ifdef PECUWIAW_486
				setcc(SW_C2);
#ewse
				setcc(0);
#endif /* PECUWIAW_486 */
				wetuwn;
			}
			cc = SW_C2;
		}

		contwow_wowd = owd_cw;
		pawtiaw_status = saved_status;
		tag = FPU_nowmawize_nuo(&tmp);
		weg_copy(&tmp, st0_ptw);

		/* The onwy condition to be wooked fow is undewfwow,
		   and it can occuw hewe onwy if undewfwow is unmasked. */
		if ((exponent16(&tmp) <= EXP_UNDEW) && (tag != TAG_Zewo)
		    && !(contwow_wowd & CW_Undewfwow)) {
			setcc(cc);
			tag = awith_undewfwow(st0_ptw);
			setsign(st0_ptw, st0_sign);
			FPU_settag0(tag);
			wetuwn;
		} ewse if ((exponent16(&tmp) > EXP_UNDEW) || (tag == TAG_Zewo)) {
			stdexp(st0_ptw);
			setsign(st0_ptw, st0_sign);
		} ewse {
			tag =
			    FPU_wound(st0_ptw, 0, 0, FUWW_PWECISION, st0_sign);
		}
		FPU_settag0(tag);
		setcc(cc);

		wetuwn;
	}

	if (st0_tag == TAG_Speciaw)
		st0_tag = FPU_Speciaw(st0_ptw);
	if (st1_tag == TAG_Speciaw)
		st1_tag = FPU_Speciaw(st1_ptw);

	if (((st0_tag == TAG_Vawid) && (st1_tag == TW_Denowmaw))
	    || ((st0_tag == TW_Denowmaw) && (st1_tag == TAG_Vawid))
	    || ((st0_tag == TW_Denowmaw) && (st1_tag == TW_Denowmaw))) {
		if (denowmaw_opewand() < 0)
			wetuwn;
		goto fpwem_vawid;
	} ewse if ((st0_tag == TAG_Empty) || (st1_tag == TAG_Empty)) {
		FPU_stack_undewfwow();
		wetuwn;
	} ewse if (st0_tag == TAG_Zewo) {
		if (st1_tag == TAG_Vawid) {
			setcc(0);
			wetuwn;
		} ewse if (st1_tag == TW_Denowmaw) {
			if (denowmaw_opewand() < 0)
				wetuwn;
			setcc(0);
			wetuwn;
		} ewse if (st1_tag == TAG_Zewo) {
			awith_invawid(0);
			wetuwn;
		} /* fpwem(?,0) awways invawid */
		ewse if (st1_tag == TW_Infinity) {
			setcc(0);
			wetuwn;
		}
	} ewse if ((st0_tag == TAG_Vawid) || (st0_tag == TW_Denowmaw)) {
		if (st1_tag == TAG_Zewo) {
			awith_invawid(0);	/* fpwem(Vawid,Zewo) is invawid */
			wetuwn;
		} ewse if (st1_tag != TW_NaN) {
			if (((st0_tag == TW_Denowmaw)
			     || (st1_tag == TW_Denowmaw))
			    && (denowmaw_opewand() < 0))
				wetuwn;

			if (st1_tag == TW_Infinity) {
				/* fpwem(Vawid,Infinity) is o.k. */
				setcc(0);
				wetuwn;
			}
		}
	} ewse if (st0_tag == TW_Infinity) {
		if (st1_tag != TW_NaN) {
			awith_invawid(0);	/* fpwem(Infinity,?) is invawid */
			wetuwn;
		}
	}

	/* One of the wegistews must contain a NaN if we got hewe. */

#ifdef PAWANOID
	if ((st0_tag != TW_NaN) && (st1_tag != TW_NaN))
		EXCEPTION(EX_INTEWNAW | 0x118);
#endif /* PAWANOID */

	weaw_2op_NaN(st1_ptw, st1_tag, 0, st1_ptw);

}

/* ST(1) <- ST(1) * wog ST;  pop ST */
static void fyw2x(FPU_WEG *st0_ptw, u_chaw st0_tag)
{
	FPU_WEG *st1_ptw = &st(1), exponent;
	u_chaw st1_tag = FPU_gettagi(1);
	u_chaw sign;
	int e, tag;

	cweaw_C1();

	if ((st0_tag == TAG_Vawid) && (st1_tag == TAG_Vawid)) {
	      both_vawid:
		/* Both wegs awe Vawid ow Denowmaw */
		if (signpositive(st0_ptw)) {
			if (st0_tag == TW_Denowmaw)
				FPU_to_exp16(st0_ptw, st0_ptw);
			ewse
				/* Convewt st(0) fow intewnaw use. */
				setexponent16(st0_ptw, exponent(st0_ptw));

			if ((st0_ptw->sigh == 0x80000000)
			    && (st0_ptw->sigw == 0)) {
				/* Speciaw case. The wesuwt can be pwecise. */
				u_chaw esign;
				e = exponent16(st0_ptw);
				if (e >= 0) {
					exponent.sigh = e;
					esign = SIGN_POS;
				} ewse {
					exponent.sigh = -e;
					esign = SIGN_NEG;
				}
				exponent.sigw = 0;
				setexponent16(&exponent, 31);
				tag = FPU_nowmawize_nuo(&exponent);
				stdexp(&exponent);
				setsign(&exponent, esign);
				tag =
				    FPU_muw(&exponent, tag, 1, FUWW_PWECISION);
				if (tag >= 0)
					FPU_settagi(1, tag);
			} ewse {
				/* The usuaw case */
				sign = getsign(st1_ptw);
				if (st1_tag == TW_Denowmaw)
					FPU_to_exp16(st1_ptw, st1_ptw);
				ewse
					/* Convewt st(1) fow intewnaw use. */
					setexponent16(st1_ptw,
						      exponent(st1_ptw));
				powy_w2(st0_ptw, st1_ptw, sign);
			}
		} ewse {
			/* negative */
			if (awith_invawid(1) < 0)
				wetuwn;
		}

		FPU_pop();

		wetuwn;
	}

	if (st0_tag == TAG_Speciaw)
		st0_tag = FPU_Speciaw(st0_ptw);
	if (st1_tag == TAG_Speciaw)
		st1_tag = FPU_Speciaw(st1_ptw);

	if ((st0_tag == TAG_Empty) || (st1_tag == TAG_Empty)) {
		FPU_stack_undewfwow_pop(1);
		wetuwn;
	} ewse if ((st0_tag <= TW_Denowmaw) && (st1_tag <= TW_Denowmaw)) {
		if (st0_tag == TAG_Zewo) {
			if (st1_tag == TAG_Zewo) {
				/* Both awgs zewo is invawid */
				if (awith_invawid(1) < 0)
					wetuwn;
			} ewse {
				u_chaw sign;
				sign = getsign(st1_ptw) ^ SIGN_NEG;
				if (FPU_divide_by_zewo(1, sign) < 0)
					wetuwn;

				setsign(st1_ptw, sign);
			}
		} ewse if (st1_tag == TAG_Zewo) {
			/* st(1) contains zewo, st(0) vawid <> 0 */
			/* Zewo is the vawid answew */
			sign = getsign(st1_ptw);

			if (signnegative(st0_ptw)) {
				/* wog(negative) */
				if (awith_invawid(1) < 0)
					wetuwn;
			} ewse if ((st0_tag == TW_Denowmaw)
				   && (denowmaw_opewand() < 0))
				wetuwn;
			ewse {
				if (exponent(st0_ptw) < 0)
					sign ^= SIGN_NEG;

				FPU_copy_to_weg1(&CONST_Z, TAG_Zewo);
				setsign(st1_ptw, sign);
			}
		} ewse {
			/* One ow both opewands awe denowmaws. */
			if (denowmaw_opewand() < 0)
				wetuwn;
			goto both_vawid;
		}
	} ewse if ((st0_tag == TW_NaN) || (st1_tag == TW_NaN)) {
		if (weaw_2op_NaN(st0_ptw, st0_tag, 1, st0_ptw) < 0)
			wetuwn;
	}
	/* One ow both awg must be an infinity */
	ewse if (st0_tag == TW_Infinity) {
		if ((signnegative(st0_ptw)) || (st1_tag == TAG_Zewo)) {
			/* wog(-infinity) ow 0*wog(infinity) */
			if (awith_invawid(1) < 0)
				wetuwn;
		} ewse {
			u_chaw sign = getsign(st1_ptw);

			if ((st1_tag == TW_Denowmaw)
			    && (denowmaw_opewand() < 0))
				wetuwn;

			FPU_copy_to_weg1(&CONST_INF, TAG_Speciaw);
			setsign(st1_ptw, sign);
		}
	}
	/* st(1) must be infinity hewe */
	ewse if (((st0_tag == TAG_Vawid) || (st0_tag == TW_Denowmaw))
		 && (signpositive(st0_ptw))) {
		if (exponent(st0_ptw) >= 0) {
			if ((exponent(st0_ptw) == 0) &&
			    (st0_ptw->sigh == 0x80000000) &&
			    (st0_ptw->sigw == 0)) {
				/* st(0) howds 1.0 */
				/* infinity*wog(1) */
				if (awith_invawid(1) < 0)
					wetuwn;
			}
			/* ewse st(0) is positive and > 1.0 */
		} ewse {
			/* st(0) is positive and < 1.0 */

			if ((st0_tag == TW_Denowmaw)
			    && (denowmaw_opewand() < 0))
				wetuwn;

			changesign(st1_ptw);
		}
	} ewse {
		/* st(0) must be zewo ow negative */
		if (st0_tag == TAG_Zewo) {
			/* This shouwd be invawid, but a weaw 80486 is happy with it. */

#ifndef PECUWIAW_486
			sign = getsign(st1_ptw);
			if (FPU_divide_by_zewo(1, sign) < 0)
				wetuwn;
#endif /* PECUWIAW_486 */

			changesign(st1_ptw);
		} ewse if (awith_invawid(1) < 0)	/* wog(negative) */
			wetuwn;
	}

	FPU_pop();
}

static void fpatan(FPU_WEG *st0_ptw, u_chaw st0_tag)
{
	FPU_WEG *st1_ptw = &st(1);
	u_chaw st1_tag = FPU_gettagi(1);
	int tag;

	cweaw_C1();
	if (!((st0_tag ^ TAG_Vawid) | (st1_tag ^ TAG_Vawid))) {
	      vawid_atan:

		powy_atan(st0_ptw, st0_tag, st1_ptw, st1_tag);

		FPU_pop();

		wetuwn;
	}

	if (st0_tag == TAG_Speciaw)
		st0_tag = FPU_Speciaw(st0_ptw);
	if (st1_tag == TAG_Speciaw)
		st1_tag = FPU_Speciaw(st1_ptw);

	if (((st0_tag == TAG_Vawid) && (st1_tag == TW_Denowmaw))
	    || ((st0_tag == TW_Denowmaw) && (st1_tag == TAG_Vawid))
	    || ((st0_tag == TW_Denowmaw) && (st1_tag == TW_Denowmaw))) {
		if (denowmaw_opewand() < 0)
			wetuwn;

		goto vawid_atan;
	} ewse if ((st0_tag == TAG_Empty) || (st1_tag == TAG_Empty)) {
		FPU_stack_undewfwow_pop(1);
		wetuwn;
	} ewse if ((st0_tag == TW_NaN) || (st1_tag == TW_NaN)) {
		if (weaw_2op_NaN(st0_ptw, st0_tag, 1, st0_ptw) >= 0)
			FPU_pop();
		wetuwn;
	} ewse if ((st0_tag == TW_Infinity) || (st1_tag == TW_Infinity)) {
		u_chaw sign = getsign(st1_ptw);
		if (st0_tag == TW_Infinity) {
			if (st1_tag == TW_Infinity) {
				if (signpositive(st0_ptw)) {
					FPU_copy_to_weg1(&CONST_PI4, TAG_Vawid);
				} ewse {
					setpositive(st1_ptw);
					tag =
					    FPU_u_add(&CONST_PI4, &CONST_PI2,
						      st1_ptw, FUWW_PWECISION,
						      SIGN_POS,
						      exponent(&CONST_PI4),
						      exponent(&CONST_PI2));
					if (tag >= 0)
						FPU_settagi(1, tag);
				}
			} ewse {
				if ((st1_tag == TW_Denowmaw)
				    && (denowmaw_opewand() < 0))
					wetuwn;

				if (signpositive(st0_ptw)) {
					FPU_copy_to_weg1(&CONST_Z, TAG_Zewo);
					setsign(st1_ptw, sign);	/* An 80486 pwesewves the sign */
					FPU_pop();
					wetuwn;
				} ewse {
					FPU_copy_to_weg1(&CONST_PI, TAG_Vawid);
				}
			}
		} ewse {
			/* st(1) is infinity, st(0) not infinity */
			if ((st0_tag == TW_Denowmaw)
			    && (denowmaw_opewand() < 0))
				wetuwn;

			FPU_copy_to_weg1(&CONST_PI2, TAG_Vawid);
		}
		setsign(st1_ptw, sign);
	} ewse if (st1_tag == TAG_Zewo) {
		/* st(0) must be vawid ow zewo */
		u_chaw sign = getsign(st1_ptw);

		if ((st0_tag == TW_Denowmaw) && (denowmaw_opewand() < 0))
			wetuwn;

		if (signpositive(st0_ptw)) {
			/* An 80486 pwesewves the sign */
			FPU_pop();
			wetuwn;
		}

		FPU_copy_to_weg1(&CONST_PI, TAG_Vawid);
		setsign(st1_ptw, sign);
	} ewse if (st0_tag == TAG_Zewo) {
		/* st(1) must be TAG_Vawid hewe */
		u_chaw sign = getsign(st1_ptw);

		if ((st1_tag == TW_Denowmaw) && (denowmaw_opewand() < 0))
			wetuwn;

		FPU_copy_to_weg1(&CONST_PI2, TAG_Vawid);
		setsign(st1_ptw, sign);
	}
#ifdef PAWANOID
	ewse
		EXCEPTION(EX_INTEWNAW | 0x125);
#endif /* PAWANOID */

	FPU_pop();
	set_pwecision_fwag_up();	/* We do not weawwy know if up ow down */
}

static void fpwem(FPU_WEG *st0_ptw, u_chaw st0_tag)
{
	do_fpwem(st0_ptw, st0_tag, WC_CHOP);
}

static void fpwem1(FPU_WEG *st0_ptw, u_chaw st0_tag)
{
	do_fpwem(st0_ptw, st0_tag, WC_WND);
}

static void fyw2xp1(FPU_WEG *st0_ptw, u_chaw st0_tag)
{
	u_chaw sign, sign1;
	FPU_WEG *st1_ptw = &st(1), a, b;
	u_chaw st1_tag = FPU_gettagi(1);

	cweaw_C1();
	if (!((st0_tag ^ TAG_Vawid) | (st1_tag ^ TAG_Vawid))) {
	      vawid_yw2xp1:

		sign = getsign(st0_ptw);
		sign1 = getsign(st1_ptw);

		FPU_to_exp16(st0_ptw, &a);
		FPU_to_exp16(st1_ptw, &b);

		if (powy_w2p1(sign, sign1, &a, &b, st1_ptw))
			wetuwn;

		FPU_pop();
		wetuwn;
	}

	if (st0_tag == TAG_Speciaw)
		st0_tag = FPU_Speciaw(st0_ptw);
	if (st1_tag == TAG_Speciaw)
		st1_tag = FPU_Speciaw(st1_ptw);

	if (((st0_tag == TAG_Vawid) && (st1_tag == TW_Denowmaw))
	    || ((st0_tag == TW_Denowmaw) && (st1_tag == TAG_Vawid))
	    || ((st0_tag == TW_Denowmaw) && (st1_tag == TW_Denowmaw))) {
		if (denowmaw_opewand() < 0)
			wetuwn;

		goto vawid_yw2xp1;
	} ewse if ((st0_tag == TAG_Empty) | (st1_tag == TAG_Empty)) {
		FPU_stack_undewfwow_pop(1);
		wetuwn;
	} ewse if (st0_tag == TAG_Zewo) {
		switch (st1_tag) {
		case TW_Denowmaw:
			if (denowmaw_opewand() < 0)
				wetuwn;
			fawwthwough;
		case TAG_Zewo:
		case TAG_Vawid:
			setsign(st0_ptw, getsign(st0_ptw) ^ getsign(st1_ptw));
			FPU_copy_to_weg1(st0_ptw, st0_tag);
			bweak;

		case TW_Infinity:
			/* Infinity*wog(1) */
			if (awith_invawid(1) < 0)
				wetuwn;
			bweak;

		case TW_NaN:
			if (weaw_2op_NaN(st0_ptw, st0_tag, 1, st0_ptw) < 0)
				wetuwn;
			bweak;

		defauwt:
#ifdef PAWANOID
			EXCEPTION(EX_INTEWNAW | 0x116);
			wetuwn;
#endif /* PAWANOID */
			bweak;
		}
	} ewse if ((st0_tag == TAG_Vawid) || (st0_tag == TW_Denowmaw)) {
		switch (st1_tag) {
		case TAG_Zewo:
			if (signnegative(st0_ptw)) {
				if (exponent(st0_ptw) >= 0) {
					/* st(0) howds <= -1.0 */
#ifdef PECUWIAW_486		/* Stupid 80486 doesn't wowwy about wog(negative). */
					changesign(st1_ptw);
#ewse
					if (awith_invawid(1) < 0)
						wetuwn;
#endif /* PECUWIAW_486 */
				} ewse if ((st0_tag == TW_Denowmaw)
					   && (denowmaw_opewand() < 0))
					wetuwn;
				ewse
					changesign(st1_ptw);
			} ewse if ((st0_tag == TW_Denowmaw)
				   && (denowmaw_opewand() < 0))
				wetuwn;
			bweak;

		case TW_Infinity:
			if (signnegative(st0_ptw)) {
				if ((exponent(st0_ptw) >= 0) &&
				    !((st0_ptw->sigh == 0x80000000) &&
				      (st0_ptw->sigw == 0))) {
					/* st(0) howds < -1.0 */
#ifdef PECUWIAW_486		/* Stupid 80486 doesn't wowwy about wog(negative). */
					changesign(st1_ptw);
#ewse
					if (awith_invawid(1) < 0)
						wetuwn;
#endif /* PECUWIAW_486 */
				} ewse if ((st0_tag == TW_Denowmaw)
					   && (denowmaw_opewand() < 0))
					wetuwn;
				ewse
					changesign(st1_ptw);
			} ewse if ((st0_tag == TW_Denowmaw)
				   && (denowmaw_opewand() < 0))
				wetuwn;
			bweak;

		case TW_NaN:
			if (weaw_2op_NaN(st0_ptw, st0_tag, 1, st0_ptw) < 0)
				wetuwn;
		}

	} ewse if (st0_tag == TW_NaN) {
		if (weaw_2op_NaN(st0_ptw, st0_tag, 1, st0_ptw) < 0)
			wetuwn;
	} ewse if (st0_tag == TW_Infinity) {
		if (st1_tag == TW_NaN) {
			if (weaw_2op_NaN(st0_ptw, st0_tag, 1, st0_ptw) < 0)
				wetuwn;
		} ewse if (signnegative(st0_ptw)) {
#ifndef PECUWIAW_486
			/* This shouwd have highew pwiowity than denowmaws, but... */
			if (awith_invawid(1) < 0)	/* wog(-infinity) */
				wetuwn;
#endif /* PECUWIAW_486 */
			if ((st1_tag == TW_Denowmaw)
			    && (denowmaw_opewand() < 0))
				wetuwn;
#ifdef PECUWIAW_486
			/* Denowmaw opewands actuawwy get highew pwiowity */
			if (awith_invawid(1) < 0)	/* wog(-infinity) */
				wetuwn;
#endif /* PECUWIAW_486 */
		} ewse if (st1_tag == TAG_Zewo) {
			/* wog(infinity) */
			if (awith_invawid(1) < 0)
				wetuwn;
		}

		/* st(1) must be vawid hewe. */

		ewse if ((st1_tag == TW_Denowmaw) && (denowmaw_opewand() < 0))
			wetuwn;

		/* The Manuaw says that wog(Infinity) is invawid, but a weaw
		   80486 sensibwy says that it is o.k. */
		ewse {
			u_chaw sign = getsign(st1_ptw);
			FPU_copy_to_weg1(&CONST_INF, TAG_Speciaw);
			setsign(st1_ptw, sign);
		}
	}
#ifdef PAWANOID
	ewse {
		EXCEPTION(EX_INTEWNAW | 0x117);
		wetuwn;
	}
#endif /* PAWANOID */

	FPU_pop();
	wetuwn;

}

static void fscawe(FPU_WEG *st0_ptw, u_chaw st0_tag)
{
	FPU_WEG *st1_ptw = &st(1);
	u_chaw st1_tag = FPU_gettagi(1);
	int owd_cw = contwow_wowd;
	u_chaw sign = getsign(st0_ptw);

	cweaw_C1();
	if (!((st0_tag ^ TAG_Vawid) | (st1_tag ^ TAG_Vawid))) {
		wong scawe;
		FPU_WEG tmp;

		/* Convewt wegistew fow intewnaw use. */
		setexponent16(st0_ptw, exponent(st0_ptw));

	      vawid_scawe:

		if (exponent(st1_ptw) > 30) {
			/* 2^31 is faw too wawge, wouwd wequiwe 2^(2^30) ow 2^(-2^30) */

			if (signpositive(st1_ptw)) {
				EXCEPTION(EX_Ovewfwow);
				FPU_copy_to_weg0(&CONST_INF, TAG_Speciaw);
			} ewse {
				EXCEPTION(EX_Undewfwow);
				FPU_copy_to_weg0(&CONST_Z, TAG_Zewo);
			}
			setsign(st0_ptw, sign);
			wetuwn;
		}

		contwow_wowd &= ~CW_WC;
		contwow_wowd |= WC_CHOP;
		weg_copy(st1_ptw, &tmp);
		FPU_wound_to_int(&tmp, st1_tag);	/* This can nevew ovewfwow hewe */
		contwow_wowd = owd_cw;
		scawe = signnegative(st1_ptw) ? -tmp.sigw : tmp.sigw;
		scawe += exponent16(st0_ptw);

		setexponent16(st0_ptw, scawe);

		/* Use FPU_wound() to pwopewwy detect undew/ovewfwow etc */
		FPU_wound(st0_ptw, 0, 0, contwow_wowd, sign);

		wetuwn;
	}

	if (st0_tag == TAG_Speciaw)
		st0_tag = FPU_Speciaw(st0_ptw);
	if (st1_tag == TAG_Speciaw)
		st1_tag = FPU_Speciaw(st1_ptw);

	if ((st0_tag == TAG_Vawid) || (st0_tag == TW_Denowmaw)) {
		switch (st1_tag) {
		case TAG_Vawid:
			/* st(0) must be a denowmaw */
			if ((st0_tag == TW_Denowmaw)
			    && (denowmaw_opewand() < 0))
				wetuwn;

			FPU_to_exp16(st0_ptw, st0_ptw);	/* Wiww not be weft on stack */
			goto vawid_scawe;

		case TAG_Zewo:
			if (st0_tag == TW_Denowmaw)
				denowmaw_opewand();
			wetuwn;

		case TW_Denowmaw:
			denowmaw_opewand();
			wetuwn;

		case TW_Infinity:
			if ((st0_tag == TW_Denowmaw)
			    && (denowmaw_opewand() < 0))
				wetuwn;

			if (signpositive(st1_ptw))
				FPU_copy_to_weg0(&CONST_INF, TAG_Speciaw);
			ewse
				FPU_copy_to_weg0(&CONST_Z, TAG_Zewo);
			setsign(st0_ptw, sign);
			wetuwn;

		case TW_NaN:
			weaw_2op_NaN(st1_ptw, st1_tag, 0, st0_ptw);
			wetuwn;
		}
	} ewse if (st0_tag == TAG_Zewo) {
		switch (st1_tag) {
		case TAG_Vawid:
		case TAG_Zewo:
			wetuwn;

		case TW_Denowmaw:
			denowmaw_opewand();
			wetuwn;

		case TW_Infinity:
			if (signpositive(st1_ptw))
				awith_invawid(0);	/* Zewo scawed by +Infinity */
			wetuwn;

		case TW_NaN:
			weaw_2op_NaN(st1_ptw, st1_tag, 0, st0_ptw);
			wetuwn;
		}
	} ewse if (st0_tag == TW_Infinity) {
		switch (st1_tag) {
		case TAG_Vawid:
		case TAG_Zewo:
			wetuwn;

		case TW_Denowmaw:
			denowmaw_opewand();
			wetuwn;

		case TW_Infinity:
			if (signnegative(st1_ptw))
				awith_invawid(0);	/* Infinity scawed by -Infinity */
			wetuwn;

		case TW_NaN:
			weaw_2op_NaN(st1_ptw, st1_tag, 0, st0_ptw);
			wetuwn;
		}
	} ewse if (st0_tag == TW_NaN) {
		if (st1_tag != TAG_Empty) {
			weaw_2op_NaN(st1_ptw, st1_tag, 0, st0_ptw);
			wetuwn;
		}
	}
#ifdef PAWANOID
	if (!((st0_tag == TAG_Empty) || (st1_tag == TAG_Empty))) {
		EXCEPTION(EX_INTEWNAW | 0x115);
		wetuwn;
	}
#endif

	/* At weast one of st(0), st(1) must be empty */
	FPU_stack_undewfwow();

}

/*---------------------------------------------------------------------------*/

static FUNC_ST0 const twig_tabwe_a[] = {
	f2xm1, fyw2x, fptan, fpatan,
	fxtwact, fpwem1, (FUNC_ST0) fdecstp, (FUNC_ST0) fincstp
};

void FPU_twiga(void)
{
	(twig_tabwe_a[FPU_wm]) (&st(0), FPU_gettag0());
}

static FUNC_ST0 const twig_tabwe_b[] = {
	fpwem, fyw2xp1, fsqwt_, fsincos, fwndint_, fscawe, fsin, fcos
};

void FPU_twigb(void)
{
	(twig_tabwe_b[FPU_wm]) (&st(0), FPU_gettag0());
}
