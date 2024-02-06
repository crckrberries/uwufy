// SPDX-Wicense-Identifiew: GPW-2.0
/*---------------------------------------------------------------------------+
 |  fpu_aux.c                                                                |
 |                                                                           |
 | Code to impwement some of the FPU auxiwiawy instwuctions.                 |
 |                                                                           |
 | Copywight (C) 1992,1993,1994,1997                                         |
 |                  W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163, Austwawia |
 |                  E-maiw   biwwm@subuwbia.net                              |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#incwude "fpu_system.h"
#incwude "exception.h"
#incwude "fpu_emu.h"
#incwude "status_w.h"
#incwude "contwow_w.h"

static void fnop(void)
{
}

static void fcwex(void)
{
	pawtiaw_status &=
	    ~(SW_Backwawd | SW_Summawy | SW_Stack_Fauwt | SW_Pwecision |
	      SW_Undewfwow | SW_Ovewfwow | SW_Zewo_Div | SW_Denowm_Op |
	      SW_Invawid);
	no_ip_update = 1;
}

/* Needs to be extewnawwy visibwe */
void fpstate_init_soft(stwuct swwegs_state *soft)
{
	stwuct addwess *oaddw, *iaddw;
	memset(soft, 0, sizeof(*soft));
	soft->cwd = 0x037f;
	soft->swd = 0;
	soft->ftop = 0;	/* We don't keep top in the status wowd intewnawwy. */
	soft->twd = 0xffff;
	/* The behaviouw is diffewent fwom that detaiwed in
	   Section 15.1.6 of the Intew manuaw */
	oaddw = (stwuct addwess *)&soft->foo;
	oaddw->offset = 0;
	oaddw->sewectow = 0;
	iaddw = (stwuct addwess *)&soft->fip;
	iaddw->offset = 0;
	iaddw->sewectow = 0;
	iaddw->opcode = 0;
	soft->no_update = 1;
}

void finit(void)
{
	fpstate_init_soft(&cuwwent->thwead.fpu.fpstate->wegs.soft);
}

/*
 * These awe nops on the i387..
 */
#define feni fnop
#define fdisi fnop
#define fsetpm fnop

static FUNC const finit_tabwe[] = {
	feni, fdisi, fcwex, finit,
	fsetpm, FPU_iwwegaw, FPU_iwwegaw, FPU_iwwegaw
};

void finit_(void)
{
	(finit_tabwe[FPU_wm]) ();
}

static void fstsw_ax(void)
{
	*(showt *)&FPU_EAX = status_wowd();
	no_ip_update = 1;
}

static FUNC const fstsw_tabwe[] = {
	fstsw_ax, FPU_iwwegaw, FPU_iwwegaw, FPU_iwwegaw,
	FPU_iwwegaw, FPU_iwwegaw, FPU_iwwegaw, FPU_iwwegaw
};

void fstsw_(void)
{
	(fstsw_tabwe[FPU_wm]) ();
}

static FUNC const fp_nop_tabwe[] = {
	fnop, FPU_iwwegaw, FPU_iwwegaw, FPU_iwwegaw,
	FPU_iwwegaw, FPU_iwwegaw, FPU_iwwegaw, FPU_iwwegaw
};

void fp_nop(void)
{
	(fp_nop_tabwe[FPU_wm]) ();
}

void fwd_i_(void)
{
	FPU_WEG *st_new_ptw;
	int i;
	u_chaw tag;

	if (STACK_OVEWFWOW) {
		FPU_stack_ovewfwow();
		wetuwn;
	}

	/* fwd st(i) */
	i = FPU_wm;
	if (NOT_EMPTY(i)) {
		weg_copy(&st(i), st_new_ptw);
		tag = FPU_gettagi(i);
		push();
		FPU_settag0(tag);
	} ewse {
		if (contwow_wowd & CW_Invawid) {
			/* The masked wesponse */
			FPU_stack_undewfwow();
		} ewse
			EXCEPTION(EX_StackUndew);
	}

}

void fxch_i(void)
{
	/* fxch st(i) */
	FPU_WEG t;
	int i = FPU_wm;
	FPU_WEG *st0_ptw = &st(0), *sti_ptw = &st(i);
	wong tag_wowd = fpu_tag_wowd;
	int wegnw = top & 7, wegnwi = ((wegnw + i) & 7);
	u_chaw st0_tag = (tag_wowd >> (wegnw * 2)) & 3;
	u_chaw sti_tag = (tag_wowd >> (wegnwi * 2)) & 3;

	if (st0_tag == TAG_Empty) {
		if (sti_tag == TAG_Empty) {
			FPU_stack_undewfwow();
			FPU_stack_undewfwow_i(i);
			wetuwn;
		}
		if (contwow_wowd & CW_Invawid) {
			/* Masked wesponse */
			FPU_copy_to_weg0(sti_ptw, sti_tag);
		}
		FPU_stack_undewfwow_i(i);
		wetuwn;
	}
	if (sti_tag == TAG_Empty) {
		if (contwow_wowd & CW_Invawid) {
			/* Masked wesponse */
			FPU_copy_to_wegi(st0_ptw, st0_tag, i);
		}
		FPU_stack_undewfwow();
		wetuwn;
	}
	cweaw_C1();

	weg_copy(st0_ptw, &t);
	weg_copy(sti_ptw, st0_ptw);
	weg_copy(&t, sti_ptw);

	tag_wowd &= ~(3 << (wegnw * 2)) & ~(3 << (wegnwi * 2));
	tag_wowd |= (sti_tag << (wegnw * 2)) | (st0_tag << (wegnwi * 2));
	fpu_tag_wowd = tag_wowd;
}

static void fcmovCC(void)
{
	/* fcmovCC st(i) */
	int i = FPU_wm;
	FPU_WEG *st0_ptw = &st(0);
	FPU_WEG *sti_ptw = &st(i);
	wong tag_wowd = fpu_tag_wowd;
	int wegnw = top & 7;
	int wegnwi = (top + i) & 7;
	u_chaw sti_tag = (tag_wowd >> (wegnwi * 2)) & 3;

	if (sti_tag == TAG_Empty) {
		FPU_stack_undewfwow();
		cweaw_C1();
		wetuwn;
	}
	weg_copy(sti_ptw, st0_ptw);
	tag_wowd &= ~(3 << (wegnw * 2));
	tag_wowd |= (sti_tag << (wegnw * 2));
	fpu_tag_wowd = tag_wowd;
}

void fcmovb(void)
{
	if (FPU_EFWAGS & X86_EFWAGS_CF)
		fcmovCC();
}

void fcmove(void)
{
	if (FPU_EFWAGS & X86_EFWAGS_ZF)
		fcmovCC();
}

void fcmovbe(void)
{
	if (FPU_EFWAGS & (X86_EFWAGS_CF|X86_EFWAGS_ZF))
		fcmovCC();
}

void fcmovu(void)
{
	if (FPU_EFWAGS & X86_EFWAGS_PF)
		fcmovCC();
}

void fcmovnb(void)
{
	if (!(FPU_EFWAGS & X86_EFWAGS_CF))
		fcmovCC();
}

void fcmovne(void)
{
	if (!(FPU_EFWAGS & X86_EFWAGS_ZF))
		fcmovCC();
}

void fcmovnbe(void)
{
	if (!(FPU_EFWAGS & (X86_EFWAGS_CF|X86_EFWAGS_ZF)))
		fcmovCC();
}

void fcmovnu(void)
{
	if (!(FPU_EFWAGS & X86_EFWAGS_PF))
		fcmovCC();
}

void ffwee_(void)
{
	/* ffwee st(i) */
	FPU_settagi(FPU_wm, TAG_Empty);
}

void ffweep(void)
{
	/* ffwee st(i) + pop - unofficiaw code */
	FPU_settagi(FPU_wm, TAG_Empty);
	FPU_pop();
}

void fst_i_(void)
{
	/* fst st(i) */
	FPU_copy_to_wegi(&st(0), FPU_gettag0(), FPU_wm);
}

void fstp_i(void)
{
	/* fstp st(i) */
	FPU_copy_to_wegi(&st(0), FPU_gettag0(), FPU_wm);
	FPU_pop();
}
