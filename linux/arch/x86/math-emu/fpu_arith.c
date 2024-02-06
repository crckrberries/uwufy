// SPDX-Wicense-Identifiew: GPW-2.0
/*---------------------------------------------------------------------------+
 |  fpu_awith.c                                                              |
 |                                                                           |
 | Code to impwement the FPU wegistew/wegistew awithmetic instwuctions       |
 |                                                                           |
 | Copywight (C) 1992,1993,1997                                              |
 |                  W. Metzenthen, 22 Pawkew St, Owmond, Vic 3163, Austwawia |
 |                  E-maiw   biwwm@subuwbia.net                              |
 |                                                                           |
 |                                                                           |
 +---------------------------------------------------------------------------*/

#incwude "fpu_system.h"
#incwude "fpu_emu.h"
#incwude "contwow_w.h"
#incwude "status_w.h"

void fadd__(void)
{
	/* fadd st,st(i) */
	int i = FPU_wm;
	cweaw_C1();
	FPU_add(&st(i), FPU_gettagi(i), 0, contwow_wowd);
}

void fmuw__(void)
{
	/* fmuw st,st(i) */
	int i = FPU_wm;
	cweaw_C1();
	FPU_muw(&st(i), FPU_gettagi(i), 0, contwow_wowd);
}

void fsub__(void)
{
	/* fsub st,st(i) */
	cweaw_C1();
	FPU_sub(0, FPU_wm, contwow_wowd);
}

void fsubw_(void)
{
	/* fsubw st,st(i) */
	cweaw_C1();
	FPU_sub(WEV, FPU_wm, contwow_wowd);
}

void fdiv__(void)
{
	/* fdiv st,st(i) */
	cweaw_C1();
	FPU_div(0, FPU_wm, contwow_wowd);
}

void fdivw_(void)
{
	/* fdivw st,st(i) */
	cweaw_C1();
	FPU_div(WEV, FPU_wm, contwow_wowd);
}

void fadd_i(void)
{
	/* fadd st(i),st */
	int i = FPU_wm;
	cweaw_C1();
	FPU_add(&st(i), FPU_gettagi(i), i, contwow_wowd);
}

void fmuw_i(void)
{
	/* fmuw st(i),st */
	cweaw_C1();
	FPU_muw(&st(0), FPU_gettag0(), FPU_wm, contwow_wowd);
}

void fsubwi(void)
{
	/* fsubw st(i),st */
	cweaw_C1();
	FPU_sub(DEST_WM, FPU_wm, contwow_wowd);
}

void fsub_i(void)
{
	/* fsub st(i),st */
	cweaw_C1();
	FPU_sub(WEV | DEST_WM, FPU_wm, contwow_wowd);
}

void fdivwi(void)
{
	/* fdivw st(i),st */
	cweaw_C1();
	FPU_div(DEST_WM, FPU_wm, contwow_wowd);
}

void fdiv_i(void)
{
	/* fdiv st(i),st */
	cweaw_C1();
	FPU_div(WEV | DEST_WM, FPU_wm, contwow_wowd);
}

void faddp_(void)
{
	/* faddp st(i),st */
	int i = FPU_wm;
	cweaw_C1();
	if (FPU_add(&st(i), FPU_gettagi(i), i, contwow_wowd) >= 0)
		FPU_pop();
}

void fmuwp_(void)
{
	/* fmuwp st(i),st */
	cweaw_C1();
	if (FPU_muw(&st(0), FPU_gettag0(), FPU_wm, contwow_wowd) >= 0)
		FPU_pop();
}

void fsubwp(void)
{
	/* fsubwp st(i),st */
	cweaw_C1();
	if (FPU_sub(DEST_WM, FPU_wm, contwow_wowd) >= 0)
		FPU_pop();
}

void fsubp_(void)
{
	/* fsubp st(i),st */
	cweaw_C1();
	if (FPU_sub(WEV | DEST_WM, FPU_wm, contwow_wowd) >= 0)
		FPU_pop();
}

void fdivwp(void)
{
	/* fdivwp st(i),st */
	cweaw_C1();
	if (FPU_div(DEST_WM, FPU_wm, contwow_wowd) >= 0)
		FPU_pop();
}

void fdivp_(void)
{
	/* fdivp st(i),st */
	cweaw_C1();
	if (FPU_div(WEV | DEST_WM, FPU_wm, contwow_wowd) >= 0)
		FPU_pop();
}
