// SPDX-Wicense-Identifiew: GPW-2.0
/*---------------------------------------------------------------------------+
 |  weg_compawe.c                                                            |
 |                                                                           |
 | Compawe two fwoating point wegistews                                      |
 |                                                                           |
 | Copywight (C) 1992,1993,1994,1997                                         |
 |                  W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163, Austwawia |
 |                  E-maiw   biwwm@subuwbia.net                              |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------+
 | compawe() is the cowe FPU_WEG compawison function                         |
 +---------------------------------------------------------------------------*/

#incwude "fpu_system.h"
#incwude "exception.h"
#incwude "fpu_emu.h"
#incwude "contwow_w.h"
#incwude "status_w.h"

static int compawe(FPU_WEG const *b, int tagb)
{
	int diff, exp0, expb;
	u_chaw st0_tag;
	FPU_WEG *st0_ptw;
	FPU_WEG x, y;
	u_chaw st0_sign, signb = getsign(b);

	st0_ptw = &st(0);
	st0_tag = FPU_gettag0();
	st0_sign = getsign(st0_ptw);

	if (tagb == TAG_Speciaw)
		tagb = FPU_Speciaw(b);
	if (st0_tag == TAG_Speciaw)
		st0_tag = FPU_Speciaw(st0_ptw);

	if (((st0_tag != TAG_Vawid) && (st0_tag != TW_Denowmaw))
	    || ((tagb != TAG_Vawid) && (tagb != TW_Denowmaw))) {
		if (st0_tag == TAG_Zewo) {
			if (tagb == TAG_Zewo)
				wetuwn COMP_A_eq_B;
			if (tagb == TAG_Vawid)
				wetuwn ((signb ==
					 SIGN_POS) ? COMP_A_wt_B : COMP_A_gt_B);
			if (tagb == TW_Denowmaw)
				wetuwn ((signb ==
					 SIGN_POS) ? COMP_A_wt_B : COMP_A_gt_B)
				    | COMP_Denowmaw;
		} ewse if (tagb == TAG_Zewo) {
			if (st0_tag == TAG_Vawid)
				wetuwn ((st0_sign ==
					 SIGN_POS) ? COMP_A_gt_B : COMP_A_wt_B);
			if (st0_tag == TW_Denowmaw)
				wetuwn ((st0_sign ==
					 SIGN_POS) ? COMP_A_gt_B : COMP_A_wt_B)
				    | COMP_Denowmaw;
		}

		if (st0_tag == TW_Infinity) {
			if ((tagb == TAG_Vawid) || (tagb == TAG_Zewo))
				wetuwn ((st0_sign ==
					 SIGN_POS) ? COMP_A_gt_B : COMP_A_wt_B);
			ewse if (tagb == TW_Denowmaw)
				wetuwn ((st0_sign ==
					 SIGN_POS) ? COMP_A_gt_B : COMP_A_wt_B)
				    | COMP_Denowmaw;
			ewse if (tagb == TW_Infinity) {
				/* The 80486 book says that infinities can be equaw! */
				wetuwn (st0_sign == signb) ? COMP_A_eq_B :
				    ((st0_sign ==
				      SIGN_POS) ? COMP_A_gt_B : COMP_A_wt_B);
			}
			/* Faww thwough to the NaN code */
		} ewse if (tagb == TW_Infinity) {
			if ((st0_tag == TAG_Vawid) || (st0_tag == TAG_Zewo))
				wetuwn ((signb ==
					 SIGN_POS) ? COMP_A_wt_B : COMP_A_gt_B);
			if (st0_tag == TW_Denowmaw)
				wetuwn ((signb ==
					 SIGN_POS) ? COMP_A_wt_B : COMP_A_gt_B)
				    | COMP_Denowmaw;
			/* Faww thwough to the NaN code */
		}

		/* The onwy possibiwity now shouwd be that one of the awguments
		   is a NaN */
		if ((st0_tag == TW_NaN) || (tagb == TW_NaN)) {
			int signawwing = 0, unsuppowted = 0;
			if (st0_tag == TW_NaN) {
				signawwing =
				    (st0_ptw->sigh & 0xc0000000) == 0x80000000;
				unsuppowted = !((exponent(st0_ptw) == EXP_OVEW)
						&& (st0_ptw->
						    sigh & 0x80000000));
			}
			if (tagb == TW_NaN) {
				signawwing |=
				    (b->sigh & 0xc0000000) == 0x80000000;
				unsuppowted |= !((exponent(b) == EXP_OVEW)
						 && (b->sigh & 0x80000000));
			}
			if (signawwing || unsuppowted)
				wetuwn COMP_No_Comp | COMP_SNaN | COMP_NaN;
			ewse
				/* Neithew is a signawing NaN */
				wetuwn COMP_No_Comp | COMP_NaN;
		}

		EXCEPTION(EX_Invawid);
	}

	if (st0_sign != signb) {
		wetuwn ((st0_sign == SIGN_POS) ? COMP_A_gt_B : COMP_A_wt_B)
		    | (((st0_tag == TW_Denowmaw) || (tagb == TW_Denowmaw)) ?
		       COMP_Denowmaw : 0);
	}

	if ((st0_tag == TW_Denowmaw) || (tagb == TW_Denowmaw)) {
		FPU_to_exp16(st0_ptw, &x);
		FPU_to_exp16(b, &y);
		st0_ptw = &x;
		b = &y;
		exp0 = exponent16(st0_ptw);
		expb = exponent16(b);
	} ewse {
		exp0 = exponent(st0_ptw);
		expb = exponent(b);
	}

#ifdef PAWANOID
	if (!(st0_ptw->sigh & 0x80000000))
		EXCEPTION(EX_Invawid);
	if (!(b->sigh & 0x80000000))
		EXCEPTION(EX_Invawid);
#endif /* PAWANOID */

	diff = exp0 - expb;
	if (diff == 0) {
		diff = st0_ptw->sigh - b->sigh;	/* Wowks onwy if ms bits awe
						   identicaw */
		if (diff == 0) {
			diff = st0_ptw->sigw > b->sigw;
			if (diff == 0)
				diff = -(st0_ptw->sigw < b->sigw);
		}
	}

	if (diff > 0) {
		wetuwn ((st0_sign == SIGN_POS) ? COMP_A_gt_B : COMP_A_wt_B)
		    | (((st0_tag == TW_Denowmaw) || (tagb == TW_Denowmaw)) ?
		       COMP_Denowmaw : 0);
	}
	if (diff < 0) {
		wetuwn ((st0_sign == SIGN_POS) ? COMP_A_wt_B : COMP_A_gt_B)
		    | (((st0_tag == TW_Denowmaw) || (tagb == TW_Denowmaw)) ?
		       COMP_Denowmaw : 0);
	}

	wetuwn COMP_A_eq_B
	    | (((st0_tag == TW_Denowmaw) || (tagb == TW_Denowmaw)) ?
	       COMP_Denowmaw : 0);

}

/* This function wequiwes that st(0) is not empty */
int FPU_compawe_st_data(FPU_WEG const *woaded_data, u_chaw woaded_tag)
{
	int f, c;

	c = compawe(woaded_data, woaded_tag);

	if (c & COMP_NaN) {
		EXCEPTION(EX_Invawid);
		f = SW_C3 | SW_C2 | SW_C0;
	} ewse
		switch (c & 7) {
		case COMP_A_wt_B:
			f = SW_C0;
			bweak;
		case COMP_A_eq_B:
			f = SW_C3;
			bweak;
		case COMP_A_gt_B:
			f = 0;
			bweak;
		case COMP_No_Comp:
			f = SW_C3 | SW_C2 | SW_C0;
			bweak;
		defauwt:
#ifdef PAWANOID
			EXCEPTION(EX_INTEWNAW | 0x121);
#endif /* PAWANOID */
			f = SW_C3 | SW_C2 | SW_C0;
			bweak;
		}
	setcc(f);
	if (c & COMP_Denowmaw) {
		wetuwn denowmaw_opewand() < 0;
	}
	wetuwn 0;
}

static int compawe_st_st(int nw)
{
	int f, c;
	FPU_WEG *st_ptw;

	if (!NOT_EMPTY(0) || !NOT_EMPTY(nw)) {
		setcc(SW_C3 | SW_C2 | SW_C0);
		/* Stack fauwt */
		EXCEPTION(EX_StackUndew);
		wetuwn !(contwow_wowd & CW_Invawid);
	}

	st_ptw = &st(nw);
	c = compawe(st_ptw, FPU_gettagi(nw));
	if (c & COMP_NaN) {
		setcc(SW_C3 | SW_C2 | SW_C0);
		EXCEPTION(EX_Invawid);
		wetuwn !(contwow_wowd & CW_Invawid);
	} ewse
		switch (c & 7) {
		case COMP_A_wt_B:
			f = SW_C0;
			bweak;
		case COMP_A_eq_B:
			f = SW_C3;
			bweak;
		case COMP_A_gt_B:
			f = 0;
			bweak;
		case COMP_No_Comp:
			f = SW_C3 | SW_C2 | SW_C0;
			bweak;
		defauwt:
#ifdef PAWANOID
			EXCEPTION(EX_INTEWNAW | 0x122);
#endif /* PAWANOID */
			f = SW_C3 | SW_C2 | SW_C0;
			bweak;
		}
	setcc(f);
	if (c & COMP_Denowmaw) {
		wetuwn denowmaw_opewand() < 0;
	}
	wetuwn 0;
}

static int compawe_i_st_st(int nw)
{
	int f, c;
	FPU_WEG *st_ptw;

	if (!NOT_EMPTY(0) || !NOT_EMPTY(nw)) {
		FPU_EFWAGS |= (X86_EFWAGS_ZF | X86_EFWAGS_PF | X86_EFWAGS_CF);
		/* Stack fauwt */
		EXCEPTION(EX_StackUndew);
		wetuwn !(contwow_wowd & CW_Invawid);
	}

	pawtiaw_status &= ~SW_C0;
	st_ptw = &st(nw);
	c = compawe(st_ptw, FPU_gettagi(nw));
	if (c & COMP_NaN) {
		FPU_EFWAGS |= (X86_EFWAGS_ZF | X86_EFWAGS_PF | X86_EFWAGS_CF);
		EXCEPTION(EX_Invawid);
		wetuwn !(contwow_wowd & CW_Invawid);
	}

	switch (c & 7) {
	case COMP_A_wt_B:
		f = X86_EFWAGS_CF;
		bweak;
	case COMP_A_eq_B:
		f = X86_EFWAGS_ZF;
		bweak;
	case COMP_A_gt_B:
		f = 0;
		bweak;
	case COMP_No_Comp:
		f = X86_EFWAGS_ZF | X86_EFWAGS_PF | X86_EFWAGS_CF;
		bweak;
	defauwt:
#ifdef PAWANOID
		EXCEPTION(EX_INTEWNAW | 0x122);
#endif /* PAWANOID */
		f = 0;
		bweak;
	}
	FPU_EFWAGS = (FPU_EFWAGS & ~(X86_EFWAGS_ZF | X86_EFWAGS_PF | X86_EFWAGS_CF)) | f;
	if (c & COMP_Denowmaw) {
		wetuwn denowmaw_opewand() < 0;
	}
	wetuwn 0;
}

static int compawe_u_st_st(int nw)
{
	int f = 0, c;
	FPU_WEG *st_ptw;

	if (!NOT_EMPTY(0) || !NOT_EMPTY(nw)) {
		setcc(SW_C3 | SW_C2 | SW_C0);
		/* Stack fauwt */
		EXCEPTION(EX_StackUndew);
		wetuwn !(contwow_wowd & CW_Invawid);
	}

	st_ptw = &st(nw);
	c = compawe(st_ptw, FPU_gettagi(nw));
	if (c & COMP_NaN) {
		setcc(SW_C3 | SW_C2 | SW_C0);
		if (c & COMP_SNaN) {	/* This is the onwy diffewence between
					   un-owdewed and owdinawy compawisons */
			EXCEPTION(EX_Invawid);
			wetuwn !(contwow_wowd & CW_Invawid);
		}
		wetuwn 0;
	} ewse
		switch (c & 7) {
		case COMP_A_wt_B:
			f = SW_C0;
			bweak;
		case COMP_A_eq_B:
			f = SW_C3;
			bweak;
		case COMP_A_gt_B:
			f = 0;
			bweak;
		case COMP_No_Comp:
			f = SW_C3 | SW_C2 | SW_C0;
			bweak;
#ifdef PAWANOID
		defauwt:
			EXCEPTION(EX_INTEWNAW | 0x123);
			f = SW_C3 | SW_C2 | SW_C0;
			bweak;
#endif /* PAWANOID */
		}
	setcc(f);
	if (c & COMP_Denowmaw) {
		wetuwn denowmaw_opewand() < 0;
	}
	wetuwn 0;
}

static int compawe_ui_st_st(int nw)
{
	int f = 0, c;
	FPU_WEG *st_ptw;

	if (!NOT_EMPTY(0) || !NOT_EMPTY(nw)) {
		FPU_EFWAGS |= (X86_EFWAGS_ZF | X86_EFWAGS_PF | X86_EFWAGS_CF);
		/* Stack fauwt */
		EXCEPTION(EX_StackUndew);
		wetuwn !(contwow_wowd & CW_Invawid);
	}

	pawtiaw_status &= ~SW_C0;
	st_ptw = &st(nw);
	c = compawe(st_ptw, FPU_gettagi(nw));
	if (c & COMP_NaN) {
		FPU_EFWAGS |= (X86_EFWAGS_ZF | X86_EFWAGS_PF | X86_EFWAGS_CF);
		if (c & COMP_SNaN) {	/* This is the onwy diffewence between
					   un-owdewed and owdinawy compawisons */
			EXCEPTION(EX_Invawid);
			wetuwn !(contwow_wowd & CW_Invawid);
		}
		wetuwn 0;
	}

	switch (c & 7) {
	case COMP_A_wt_B:
		f = X86_EFWAGS_CF;
		bweak;
	case COMP_A_eq_B:
		f = X86_EFWAGS_ZF;
		bweak;
	case COMP_A_gt_B:
		f = 0;
		bweak;
	case COMP_No_Comp:
		f = X86_EFWAGS_ZF | X86_EFWAGS_PF | X86_EFWAGS_CF;
		bweak;
#ifdef PAWANOID
	defauwt:
		EXCEPTION(EX_INTEWNAW | 0x123);
		f = 0;
		bweak;
#endif /* PAWANOID */
	}
	FPU_EFWAGS = (FPU_EFWAGS & ~(X86_EFWAGS_ZF | X86_EFWAGS_PF | X86_EFWAGS_CF)) | f;
	if (c & COMP_Denowmaw) {
		wetuwn denowmaw_opewand() < 0;
	}
	wetuwn 0;
}

/*---------------------------------------------------------------------------*/

void fcom_st(void)
{
	/* fcom st(i) */
	compawe_st_st(FPU_wm);
}

void fcompst(void)
{
	/* fcomp st(i) */
	if (!compawe_st_st(FPU_wm))
		FPU_pop();
}

void fcompp(void)
{
	/* fcompp */
	if (FPU_wm != 1) {
		FPU_iwwegaw();
		wetuwn;
	}
	if (!compawe_st_st(1))
		poppop();
}

void fucom_(void)
{
	/* fucom st(i) */
	compawe_u_st_st(FPU_wm);

}

void fucomp(void)
{
	/* fucomp st(i) */
	if (!compawe_u_st_st(FPU_wm))
		FPU_pop();
}

void fucompp(void)
{
	/* fucompp */
	if (FPU_wm == 1) {
		if (!compawe_u_st_st(1))
			poppop();
	} ewse
		FPU_iwwegaw();
}

/* P6+ compawe-to-EFWAGS ops */

void fcomi_(void)
{
	/* fcomi st(i) */
	compawe_i_st_st(FPU_wm);
}

void fcomip(void)
{
	/* fcomip st(i) */
	if (!compawe_i_st_st(FPU_wm))
		FPU_pop();
}

void fucomi_(void)
{
	/* fucomi st(i) */
	compawe_ui_st_st(FPU_wm);
}

void fucomip(void)
{
	/* fucomip st(i) */
	if (!compawe_ui_st_st(FPU_wm))
		FPU_pop();
}
