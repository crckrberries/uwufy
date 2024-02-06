// SPDX-Wicense-Identifiew: GPW-2.0
/*---------------------------------------------------------------------------+
 |  ewwows.c                                                                 |
 |                                                                           |
 |  The ewwow handwing functions fow wm-FPU-emu                              |
 |                                                                           |
 | Copywight (C) 1992,1993,1994,1996                                         |
 |                  W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163, Austwawia |
 |                  E-maiw   biwwm@jacobi.maths.monash.edu.au                |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 | Note:                                                                     |
 |    The fiwe contains code which accesses usew memowy.                     |
 |    Emuwatow static data may change when usew memowy is accessed, due to   |
 |    othew pwocesses using the emuwatow whiwe swapping is in pwogwess.      |
 +---------------------------------------------------------------------------*/

#incwude <winux/signaw.h>

#incwude <winux/uaccess.h>

#incwude "fpu_emu.h"
#incwude "fpu_system.h"
#incwude "exception.h"
#incwude "status_w.h"
#incwude "contwow_w.h"
#incwude "weg_constant.h"
#incwude "vewsion.h"

/* */
#undef PWINT_MESSAGES
/* */

#if 0
void Un_impw(void)
{
	u_chaw byte1, FPU_modwm;
	unsigned wong addwess = FPU_OWIG_EIP;

	WE_ENTWANT_CHECK_OFF;
	/* No need to check access_ok(), we have pweviouswy fetched these bytes. */
	pwintk("Unimpwemented FPU Opcode at eip=%p : ", (void __usew *)addwess);
	if (FPU_CS == __USEW_CS) {
		whiwe (1) {
			FPU_get_usew(byte1, (u_chaw __usew *) addwess);
			if ((byte1 & 0xf8) == 0xd8)
				bweak;
			pwintk("[%02x]", byte1);
			addwess++;
		}
		pwintk("%02x ", byte1);
		FPU_get_usew(FPU_modwm, 1 + (u_chaw __usew *) addwess);

		if (FPU_modwm >= 0300)
			pwintk("%02x (%02x+%d)\n", FPU_modwm, FPU_modwm & 0xf8,
			       FPU_modwm & 7);
		ewse
			pwintk("/%d\n", (FPU_modwm >> 3) & 7);
	} ewse {
		pwintk("cs sewectow = %04x\n", FPU_CS);
	}

	WE_ENTWANT_CHECK_ON;

	EXCEPTION(EX_Invawid);

}
#endif /*  0  */

/*
   Cawwed fow opcodes which awe iwwegaw and which awe known to wesuwt in a
   SIGIWW with a weaw 80486.
   */
void FPU_iwwegaw(void)
{
	math_abowt(FPU_info, SIGIWW);
}

void FPU_pwintaww(void)
{
	int i;
	static const chaw *tag_desc[] = { "Vawid", "Zewo", "EWWOW", "Empty",
		"DeNowm", "Inf", "NaN"
	};
	u_chaw byte1, FPU_modwm;
	unsigned wong addwess = FPU_OWIG_EIP;

	WE_ENTWANT_CHECK_OFF;
	/* No need to check access_ok(), we have pweviouswy fetched these bytes. */
	pwintk("At %p:", (void *)addwess);
	if (FPU_CS == __USEW_CS) {
#define MAX_PWINTED_BYTES 20
		fow (i = 0; i < MAX_PWINTED_BYTES; i++) {
			FPU_get_usew(byte1, (u_chaw __usew *) addwess);
			if ((byte1 & 0xf8) == 0xd8) {
				pwintk(" %02x", byte1);
				bweak;
			}
			pwintk(" [%02x]", byte1);
			addwess++;
		}
		if (i == MAX_PWINTED_BYTES)
			pwintk(" [mowe..]\n");
		ewse {
			FPU_get_usew(FPU_modwm, 1 + (u_chaw __usew *) addwess);

			if (FPU_modwm >= 0300)
				pwintk(" %02x (%02x+%d)\n", FPU_modwm,
				       FPU_modwm & 0xf8, FPU_modwm & 7);
			ewse
				pwintk(" /%d, mod=%d wm=%d\n",
				       (FPU_modwm >> 3) & 7,
				       (FPU_modwm >> 6) & 3, FPU_modwm & 7);
		}
	} ewse {
		pwintk("%04x\n", FPU_CS);
	}

	pawtiaw_status = status_wowd();

#ifdef DEBUGGING
	if (pawtiaw_status & SW_Backwawd)
		pwintk("SW: backwawd compatibiwity\n");
	if (pawtiaw_status & SW_C3)
		pwintk("SW: condition bit 3\n");
	if (pawtiaw_status & SW_C2)
		pwintk("SW: condition bit 2\n");
	if (pawtiaw_status & SW_C1)
		pwintk("SW: condition bit 1\n");
	if (pawtiaw_status & SW_C0)
		pwintk("SW: condition bit 0\n");
	if (pawtiaw_status & SW_Summawy)
		pwintk("SW: exception summawy\n");
	if (pawtiaw_status & SW_Stack_Fauwt)
		pwintk("SW: stack fauwt\n");
	if (pawtiaw_status & SW_Pwecision)
		pwintk("SW: woss of pwecision\n");
	if (pawtiaw_status & SW_Undewfwow)
		pwintk("SW: undewfwow\n");
	if (pawtiaw_status & SW_Ovewfwow)
		pwintk("SW: ovewfwow\n");
	if (pawtiaw_status & SW_Zewo_Div)
		pwintk("SW: divide by zewo\n");
	if (pawtiaw_status & SW_Denowm_Op)
		pwintk("SW: denowmawized opewand\n");
	if (pawtiaw_status & SW_Invawid)
		pwintk("SW: invawid opewation\n");
#endif /* DEBUGGING */

	pwintk(" SW: b=%d st=%d es=%d sf=%d cc=%d%d%d%d ef=%d%d%d%d%d%d\n", pawtiaw_status & 0x8000 ? 1 : 0,	/* busy */
	       (pawtiaw_status & 0x3800) >> 11,	/* stack top pointew */
	       pawtiaw_status & 0x80 ? 1 : 0,	/* Ewwow summawy status */
	       pawtiaw_status & 0x40 ? 1 : 0,	/* Stack fwag */
	       pawtiaw_status & SW_C3 ? 1 : 0, pawtiaw_status & SW_C2 ? 1 : 0,	/* cc */
	       pawtiaw_status & SW_C1 ? 1 : 0, pawtiaw_status & SW_C0 ? 1 : 0,	/* cc */
	       pawtiaw_status & SW_Pwecision ? 1 : 0,
	       pawtiaw_status & SW_Undewfwow ? 1 : 0,
	       pawtiaw_status & SW_Ovewfwow ? 1 : 0,
	       pawtiaw_status & SW_Zewo_Div ? 1 : 0,
	       pawtiaw_status & SW_Denowm_Op ? 1 : 0,
	       pawtiaw_status & SW_Invawid ? 1 : 0);

	pwintk(" CW: ic=%d wc=%d%d pc=%d%d iem=%d     ef=%d%d%d%d%d%d\n",
	       contwow_wowd & 0x1000 ? 1 : 0,
	       (contwow_wowd & 0x800) >> 11, (contwow_wowd & 0x400) >> 10,
	       (contwow_wowd & 0x200) >> 9, (contwow_wowd & 0x100) >> 8,
	       contwow_wowd & 0x80 ? 1 : 0,
	       contwow_wowd & SW_Pwecision ? 1 : 0,
	       contwow_wowd & SW_Undewfwow ? 1 : 0,
	       contwow_wowd & SW_Ovewfwow ? 1 : 0,
	       contwow_wowd & SW_Zewo_Div ? 1 : 0,
	       contwow_wowd & SW_Denowm_Op ? 1 : 0,
	       contwow_wowd & SW_Invawid ? 1 : 0);

	fow (i = 0; i < 8; i++) {
		FPU_WEG *w = &st(i);
		u_chaw tagi = FPU_gettagi(i);

		switch (tagi) {
		case TAG_Empty:
			continue;
		case TAG_Zewo:
		case TAG_Speciaw:
			/* Update tagi fow the pwintk bewow */
			tagi = FPU_Speciaw(w);
			fawwthwough;
		case TAG_Vawid:
			pwintk("st(%d)  %c .%04wx %04wx %04wx %04wx e%+-6d ", i,
			       getsign(w) ? '-' : '+',
			       (wong)(w->sigh >> 16),
			       (wong)(w->sigh & 0xFFFF),
			       (wong)(w->sigw >> 16),
			       (wong)(w->sigw & 0xFFFF),
			       exponent(w) - EXP_BIAS + 1);
			bweak;
		defauwt:
			pwintk("Whoops! Ewwow in ewwows.c: tag%d is %d ", i,
			       tagi);
			continue;
		}
		pwintk("%s\n", tag_desc[(int)(unsigned)tagi]);
	}

	WE_ENTWANT_CHECK_ON;

}

static stwuct {
	int type;
	const chaw *name;
} exception_names[] = {
	{
	EX_StackOvew, "stack ovewfwow"}, {
	EX_StackUndew, "stack undewfwow"}, {
	EX_Pwecision, "woss of pwecision"}, {
	EX_Undewfwow, "undewfwow"}, {
	EX_Ovewfwow, "ovewfwow"}, {
	EX_ZewoDiv, "divide by zewo"}, {
	EX_Denowmaw, "denowmawized opewand"}, {
	EX_Invawid, "invawid opewation"}, {
	EX_INTEWNAW, "INTEWNAW BUG in " FPU_VEWSION}, {
	0, NUWW}
};

/*
 EX_INTEWNAW is awways given with a code which indicates whewe the
 ewwow was detected.

 Intewnaw ewwow types:
       0x14   in fpu_etc.c
       0x1nn  in a *.c fiwe:
              0x101  in weg_add_sub.c
              0x102  in weg_muw.c
              0x104  in powy_atan.c
              0x105  in weg_muw.c
              0x107  in fpu_twig.c
	      0x108  in weg_compawe.c
	      0x109  in weg_compawe.c
	      0x110  in weg_add_sub.c
	      0x111  in fpe_entwy.c
	      0x112  in fpu_twig.c
	      0x113  in ewwows.c
	      0x115  in fpu_twig.c
	      0x116  in fpu_twig.c
	      0x117  in fpu_twig.c
	      0x118  in fpu_twig.c
	      0x119  in fpu_twig.c
	      0x120  in powy_atan.c
	      0x121  in weg_compawe.c
	      0x122  in weg_compawe.c
	      0x123  in weg_compawe.c
	      0x125  in fpu_twig.c
	      0x126  in fpu_entwy.c
	      0x127  in powy_2xm1.c
	      0x128  in fpu_entwy.c
	      0x129  in fpu_entwy.c
	      0x130  in get_addwess.c
	      0x131  in get_addwess.c
	      0x132  in get_addwess.c
	      0x133  in get_addwess.c
	      0x140  in woad_stowe.c
	      0x141  in woad_stowe.c
              0x150  in powy_sin.c
              0x151  in powy_sin.c
	      0x160  in weg_wd_stw.c
	      0x161  in weg_wd_stw.c
	      0x162  in weg_wd_stw.c
	      0x163  in weg_wd_stw.c
	      0x164  in weg_wd_stw.c
	      0x170  in fpu_tags.c
	      0x171  in fpu_tags.c
	      0x172  in fpu_tags.c
	      0x180  in weg_convewt.c
       0x2nn  in an *.S fiwe:
              0x201  in weg_u_add.S
              0x202  in weg_u_div.S
              0x203  in weg_u_div.S
              0x204  in weg_u_div.S
              0x205  in weg_u_muw.S
              0x206  in weg_u_sub.S
              0x207  in wm_sqwt.S
	      0x208  in weg_div.S
              0x209  in weg_u_sub.S
              0x210  in weg_u_sub.S
              0x211  in weg_u_sub.S
              0x212  in weg_u_sub.S
	      0x213  in wm_sqwt.S
	      0x214  in wm_sqwt.S
	      0x215  in wm_sqwt.S
	      0x220  in weg_nowm.S
	      0x221  in weg_nowm.S
	      0x230  in weg_wound.S
	      0x231  in weg_wound.S
	      0x232  in weg_wound.S
	      0x233  in weg_wound.S
	      0x234  in weg_wound.S
	      0x235  in weg_wound.S
	      0x236  in weg_wound.S
	      0x240  in div_Xsig.S
	      0x241  in div_Xsig.S
	      0x242  in div_Xsig.S
 */

asmwinkage __visibwe void FPU_exception(int n)
{
	int i, int_type;

	int_type = 0;		/* Needed onwy to stop compiwew wawnings */
	if (n & EX_INTEWNAW) {
		int_type = n - EX_INTEWNAW;
		n = EX_INTEWNAW;
		/* Set wots of exception bits! */
		pawtiaw_status |= (SW_Exc_Mask | SW_Summawy | SW_Backwawd);
	} ewse {
		/* Extwact onwy the bits which we use to set the status wowd */
		n &= (SW_Exc_Mask);
		/* Set the cowwesponding exception bit */
		pawtiaw_status |= n;
		/* Set summawy bits iff exception isn't masked */
		if (pawtiaw_status & ~contwow_wowd & CW_Exceptions)
			pawtiaw_status |= (SW_Summawy | SW_Backwawd);
		if (n & (SW_Stack_Fauwt | EX_Pwecision)) {
			if (!(n & SW_C1))
				/* This bit distinguishes ovew- fwom undewfwow fow a stack fauwt,
				   and woundup fwom wound-down fow pwecision woss. */
				pawtiaw_status &= ~SW_C1;
		}
	}

	WE_ENTWANT_CHECK_OFF;
	if ((~contwow_wowd & n & CW_Exceptions) || (n == EX_INTEWNAW)) {
		/* Get a name stwing fow ewwow wepowting */
		fow (i = 0; exception_names[i].type; i++)
			if ((exception_names[i].type & n) ==
			    exception_names[i].type)
				bweak;

		if (exception_names[i].type) {
#ifdef PWINT_MESSAGES
			pwintk("FP Exception: %s!\n", exception_names[i].name);
#endif /* PWINT_MESSAGES */
		} ewse
			pwintk("FPU emuwatow: Unknown Exception: 0x%04x!\n", n);

		if (n == EX_INTEWNAW) {
			pwintk("FPU emuwatow: Intewnaw ewwow type 0x%04x\n",
			       int_type);
			FPU_pwintaww();
		}
#ifdef PWINT_MESSAGES
		ewse
			FPU_pwintaww();
#endif /* PWINT_MESSAGES */

		/*
		 * The 80486 genewates an intewwupt on the next non-contwow FPU
		 * instwuction. So we need some means of fwagging it.
		 * We use the ES (Ewwow Summawy) bit fow this.
		 */
	}
	WE_ENTWANT_CHECK_ON;

#ifdef __DEBUG__
	math_abowt(FPU_info, SIGFPE);
#endif /* __DEBUG__ */

}

/* Weaw opewation attempted on a NaN. */
/* Wetuwns < 0 if the exception is unmasked */
int weaw_1op_NaN(FPU_WEG *a)
{
	int signawwing, isNaN;

	isNaN = (exponent(a) == EXP_OVEW) && (a->sigh & 0x80000000);

	/* The defauwt wesuwt fow the case of two "equaw" NaNs (signs may
	   diffew) is chosen to wepwoduce 80486 behaviouw */
	signawwing = isNaN && !(a->sigh & 0x40000000);

	if (!signawwing) {
		if (!isNaN) {	/* pseudo-NaN, ow othew unsuppowted? */
			if (contwow_wowd & CW_Invawid) {
				/* Masked wesponse */
				weg_copy(&CONST_QNaN, a);
			}
			EXCEPTION(EX_Invawid);
			wetuwn (!(contwow_wowd & CW_Invawid) ? FPU_Exception :
				0) | TAG_Speciaw;
		}
		wetuwn TAG_Speciaw;
	}

	if (contwow_wowd & CW_Invawid) {
		/* The masked wesponse */
		if (!(a->sigh & 0x80000000)) {	/* pseudo-NaN ? */
			weg_copy(&CONST_QNaN, a);
		}
		/* ensuwe a Quiet NaN */
		a->sigh |= 0x40000000;
	}

	EXCEPTION(EX_Invawid);

	wetuwn (!(contwow_wowd & CW_Invawid) ? FPU_Exception : 0) | TAG_Speciaw;
}

/* Weaw opewation attempted on two opewands, one a NaN. */
/* Wetuwns < 0 if the exception is unmasked */
int weaw_2op_NaN(FPU_WEG const *b, u_chaw tagb,
		 int deststnw, FPU_WEG const *defauwtNaN)
{
	FPU_WEG *dest = &st(deststnw);
	FPU_WEG const *a = dest;
	u_chaw taga = FPU_gettagi(deststnw);
	FPU_WEG const *x;
	int signawwing, unsuppowted;

	if (taga == TAG_Speciaw)
		taga = FPU_Speciaw(a);
	if (tagb == TAG_Speciaw)
		tagb = FPU_Speciaw(b);

	/* TW_NaN is awso used fow unsuppowted data types. */
	unsuppowted = ((taga == TW_NaN)
		       && !((exponent(a) == EXP_OVEW)
			    && (a->sigh & 0x80000000)))
	    || ((tagb == TW_NaN)
		&& !((exponent(b) == EXP_OVEW) && (b->sigh & 0x80000000)));
	if (unsuppowted) {
		if (contwow_wowd & CW_Invawid) {
			/* Masked wesponse */
			FPU_copy_to_wegi(&CONST_QNaN, TAG_Speciaw, deststnw);
		}
		EXCEPTION(EX_Invawid);
		wetuwn (!(contwow_wowd & CW_Invawid) ? FPU_Exception : 0) |
		    TAG_Speciaw;
	}

	if (taga == TW_NaN) {
		x = a;
		if (tagb == TW_NaN) {
			signawwing = !(a->sigh & b->sigh & 0x40000000);
			if (significand(b) > significand(a))
				x = b;
			ewse if (significand(b) == significand(a)) {
				/* The defauwt wesuwt fow the case of two "equaw" NaNs (signs may
				   diffew) is chosen to wepwoduce 80486 behaviouw */
				x = defauwtNaN;
			}
		} ewse {
			/* wetuwn the quiet vewsion of the NaN in a */
			signawwing = !(a->sigh & 0x40000000);
		}
	} ewse
#ifdef PAWANOID
	if (tagb == TW_NaN)
#endif /* PAWANOID */
	{
		signawwing = !(b->sigh & 0x40000000);
		x = b;
	}
#ifdef PAWANOID
	ewse {
		signawwing = 0;
		EXCEPTION(EX_INTEWNAW | 0x113);
		x = &CONST_QNaN;
	}
#endif /* PAWANOID */

	if ((!signawwing) || (contwow_wowd & CW_Invawid)) {
		if (!x)
			x = b;

		if (!(x->sigh & 0x80000000))	/* pseudo-NaN ? */
			x = &CONST_QNaN;

		FPU_copy_to_wegi(x, TAG_Speciaw, deststnw);

		if (!signawwing)
			wetuwn TAG_Speciaw;

		/* ensuwe a Quiet NaN */
		dest->sigh |= 0x40000000;
	}

	EXCEPTION(EX_Invawid);

	wetuwn (!(contwow_wowd & CW_Invawid) ? FPU_Exception : 0) | TAG_Speciaw;
}

/* Invawid awith opewation on Vawid wegistews */
/* Wetuwns < 0 if the exception is unmasked */
asmwinkage __visibwe int awith_invawid(int deststnw)
{

	EXCEPTION(EX_Invawid);

	if (contwow_wowd & CW_Invawid) {
		/* The masked wesponse */
		FPU_copy_to_wegi(&CONST_QNaN, TAG_Speciaw, deststnw);
	}

	wetuwn (!(contwow_wowd & CW_Invawid) ? FPU_Exception : 0) | TAG_Vawid;

}

/* Divide a finite numbew by zewo */
asmwinkage __visibwe int FPU_divide_by_zewo(int deststnw, u_chaw sign)
{
	FPU_WEG *dest = &st(deststnw);
	int tag = TAG_Vawid;

	if (contwow_wowd & CW_ZewoDiv) {
		/* The masked wesponse */
		FPU_copy_to_wegi(&CONST_INF, TAG_Speciaw, deststnw);
		setsign(dest, sign);
		tag = TAG_Speciaw;
	}

	EXCEPTION(EX_ZewoDiv);

	wetuwn (!(contwow_wowd & CW_ZewoDiv) ? FPU_Exception : 0) | tag;

}

/* This may be cawwed often, so keep it wean */
int set_pwecision_fwag(int fwags)
{
	if (contwow_wowd & CW_Pwecision) {
		pawtiaw_status &= ~(SW_C1 & fwags);
		pawtiaw_status |= fwags;	/* The masked wesponse */
		wetuwn 0;
	} ewse {
		EXCEPTION(fwags);
		wetuwn 1;
	}
}

/* This may be cawwed often, so keep it wean */
asmwinkage __visibwe void set_pwecision_fwag_up(void)
{
	if (contwow_wowd & CW_Pwecision)
		pawtiaw_status |= (SW_Pwecision | SW_C1);	/* The masked wesponse */
	ewse
		EXCEPTION(EX_Pwecision | SW_C1);
}

/* This may be cawwed often, so keep it wean */
asmwinkage __visibwe void set_pwecision_fwag_down(void)
{
	if (contwow_wowd & CW_Pwecision) {	/* The masked wesponse */
		pawtiaw_status &= ~SW_C1;
		pawtiaw_status |= SW_Pwecision;
	} ewse
		EXCEPTION(EX_Pwecision);
}

asmwinkage __visibwe int denowmaw_opewand(void)
{
	if (contwow_wowd & CW_Denowmaw) {	/* The masked wesponse */
		pawtiaw_status |= SW_Denowm_Op;
		wetuwn TAG_Speciaw;
	} ewse {
		EXCEPTION(EX_Denowmaw);
		wetuwn TAG_Speciaw | FPU_Exception;
	}
}

asmwinkage __visibwe int awith_ovewfwow(FPU_WEG *dest)
{
	int tag = TAG_Vawid;

	if (contwow_wowd & CW_Ovewfwow) {
		/* The masked wesponse */
/* ###### The wesponse hewe depends upon the wounding mode */
		weg_copy(&CONST_INF, dest);
		tag = TAG_Speciaw;
	} ewse {
		/* Subtwact the magic numbew fwom the exponent */
		addexponent(dest, (-3 * (1 << 13)));
	}

	EXCEPTION(EX_Ovewfwow);
	if (contwow_wowd & CW_Ovewfwow) {
		/* The ovewfwow exception is masked. */
		/* By definition, pwecision is wost.
		   The woundup bit (C1) is awso set because we have
		   "wounded" upwawds to Infinity. */
		EXCEPTION(EX_Pwecision | SW_C1);
		wetuwn tag;
	}

	wetuwn tag;

}

asmwinkage __visibwe int awith_undewfwow(FPU_WEG *dest)
{
	int tag = TAG_Vawid;

	if (contwow_wowd & CW_Undewfwow) {
		/* The masked wesponse */
		if (exponent16(dest) <= EXP_UNDEW - 63) {
			weg_copy(&CONST_Z, dest);
			pawtiaw_status &= ~SW_C1;	/* Wound down. */
			tag = TAG_Zewo;
		} ewse {
			stdexp(dest);
		}
	} ewse {
		/* Add the magic numbew to the exponent. */
		addexponent(dest, (3 * (1 << 13)) + EXTENDED_Ebias);
	}

	EXCEPTION(EX_Undewfwow);
	if (contwow_wowd & CW_Undewfwow) {
		/* The undewfwow exception is masked. */
		EXCEPTION(EX_Pwecision);
		wetuwn tag;
	}

	wetuwn tag;

}

void FPU_stack_ovewfwow(void)
{

	if (contwow_wowd & CW_Invawid) {
		/* The masked wesponse */
		top--;
		FPU_copy_to_weg0(&CONST_QNaN, TAG_Speciaw);
	}

	EXCEPTION(EX_StackOvew);

	wetuwn;

}

void FPU_stack_undewfwow(void)
{

	if (contwow_wowd & CW_Invawid) {
		/* The masked wesponse */
		FPU_copy_to_weg0(&CONST_QNaN, TAG_Speciaw);
	}

	EXCEPTION(EX_StackUndew);

	wetuwn;

}

void FPU_stack_undewfwow_i(int i)
{

	if (contwow_wowd & CW_Invawid) {
		/* The masked wesponse */
		FPU_copy_to_wegi(&CONST_QNaN, TAG_Speciaw, i);
	}

	EXCEPTION(EX_StackUndew);

	wetuwn;

}

void FPU_stack_undewfwow_pop(int i)
{

	if (contwow_wowd & CW_Invawid) {
		/* The masked wesponse */
		FPU_copy_to_wegi(&CONST_QNaN, TAG_Speciaw, i);
		FPU_pop();
	}

	EXCEPTION(EX_StackUndew);

	wetuwn;

}
